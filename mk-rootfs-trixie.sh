#!/bin/bash -e

# Directory contains the target rootfs
TARGET_ROOTFS_DIR="binary"

if [ -e $TARGET_ROOTFS_DIR ]; then
	sudo rm -rf $TARGET_ROOTFS_DIR
fi

if [ "$ARCH" == "armhf" ]; then
	ARCH='armhf'
elif [ "$ARCH" == "arm64" ]; then
	ARCH='arm64'
else
    echo -e "\033[36m please input is: armhf or arm64...... \033[0m"
fi

if [ ! $VERSION ]; then
	VERSION="release"
fi

if [ ! -e live-image-$ARCH.tar.tar.gz ]; then
	echo "\033[36m Run sudo lb build first \033[0m"
fi

finish() {
	sudo umount -lf $TARGET_ROOTFS_DIR/proc || true
	sudo umount -lf $TARGET_ROOTFS_DIR/sys || true
	sudo umount -lf $TARGET_ROOTFS_DIR/dev/pts || true
	sudo umount -lf $TARGET_ROOTFS_DIR/dev || true
	exit -1
}
trap finish ERR

echo -e "\033[36m Extract image \033[0m"
sudo tar -xpf live-image-$ARCH.tar.tar.gz

sudo cp -rf ../kernel/linux/tmp/lib/modules $TARGET_ROOTFS_DIR/lib

# packages folder
sudo mkdir -p $TARGET_ROOTFS_DIR/packages
sudo cp -rf ../packages/$ARCH/* $TARGET_ROOTFS_DIR/packages
sudo cp -rf ../kernel/linux/tmp/boot/* $TARGET_ROOTFS_DIR/boot
sudo mkdir -p $TARGET_ROOTFS_DIR/boot/firmware
export KERNEL_VERSION=$(ls $TARGET_ROOTFS_DIR/boot/vmlinuz-* 2>/dev/null | sed 's|.*/vmlinuz-||' | sort -V | tail -n 1)
echo $KERNEL_VERSION
sudo sed -e "s/6.16.0-rc7-v8-16k+/$KERNEL_VERSION/g" < ../kernel/patches/40_custom_uuid | sudo tee $TARGET_ROOTFS_DIR/boot/40_custom_uuid > /dev/null
cat $TARGET_ROOTFS_DIR/boot/40_custom_uuid
wget https://archive.raspberrypi.org/debian/raspberrypi.gpg.key -O - | gpg --dearmor | sudo tee $TARGET_ROOTFS_DIR/etc/apt/trusted.gpg.d/raspberrypi4-keys.gpg > /dev/null

# overlay folder
sudo cp -rf ../overlay/* $TARGET_ROOTFS_DIR/

echo -e "\033[36m Change root.....................\033[0m"
if [ "$ARCH" == "armhf" ]; then
	sudo cp /usr/bin/qemu-arm-static $TARGET_ROOTFS_DIR/usr/bin/
elif [ "$ARCH" == "arm64"  ]; then
	sudo cp /usr/bin/qemu-aarch64-static $TARGET_ROOTFS_DIR/usr/bin/
fi
sudo mount -o bind /proc $TARGET_ROOTFS_DIR/proc
sudo mount -o bind /sys $TARGET_ROOTFS_DIR/sys
sudo mount -o bind /dev $TARGET_ROOTFS_DIR/dev
sudo mount -o bind /dev/pts $TARGET_ROOTFS_DIR/dev/pts

cat << EOF | sudo chroot $TARGET_ROOTFS_DIR

rm -rf /etc/resolv.conf
echo -e "nameserver 8.8.8.8\nnameserver 8.8.4.4" > /etc/resolv.conf
resolvconf -u

# Install mesa 25
echo -e "deb http://archive.raspberrypi.org/debian trixie main" >> /etc/apt/sources.list
apt-get update
apt-get upgrade -y
apt-get install -y build-essential git wget grub-efi-arm64 e2fsprogs zstd initramfs-tools mesa-vulkan-drivers gdm3

ls -la /boot/firmware
rm -rf /boot/firmware
mkdir -p /boot/firmware
grub-install --target=arm64-efi --efi-directory=/boot/firmware --bootloader-id=GRUB
update-grub

cp /boot/40_custom_uuid /etc/grub.d/
chmod +x /etc/grub.d/40_custom_uuid
rm -rf /boot/40_custom_uuid

# Fix mouse lagging issue
cat << MOUSE_EOF >> /etc/environment
MUTTER_DEBUG_ENABLE_ATOMIC_KMS=0
MUTTER_DEBUG_FORCE_KMS_MODE=simple
CLUTTER_PAINT=disable-dynamic-max-render-time
MOUSE_EOF

cat << GRUB_EOF > /etc/default/grub
GRUB_DEFAULT="Boot from UUID"
GRUB_TIMEOUT=5
GRUB_CMDLINE_LINUX_DEFAULT="quiet"
GRUB_CMDLINE_LINUX=""
GRUB_EOF

cat << FSTAB_EOF > /etc/fstab
UUID=B921B045-1DF0-41C3-AF44-4C6F280D3FAE /  ext4    errors=remount-ro   0   1
UUID=95E4-6EA5  /boot/firmware  vfat    umask=0077      0       1
FSTAB_EOF

update-grub

chmod o+x /usr/lib/dbus-1.0/dbus-daemon-launch-helper
chmod +x /etc/rc.local

cp /packages/rpiwifi/brcmfmac43455-sdio.txt /lib/firmware/brcm/
cp /packages/rpiwifi/BCM4345C0.hcd /lib/firmware/brcm/
cp /packages/rtlbt/rtl8761bu* /lib/firmware/rtl_bt/
apt-get install -f -y

# Turn off speech dispatcher
apt remove orca -y

systemctl enable rc-local
systemctl enable resize-helper
chsh -s /bin/bash linaro
update-initramfs -c -k $KERNEL_VERSION
sync

#---------------Clean--------------
rm -rf /var/lib/apt/lists/*
rm -rf /boot/firmware/*
sync
EOF

sudo umount -lf $TARGET_ROOTFS_DIR/proc || true
sudo umount -lf $TARGET_ROOTFS_DIR/sys || true
sudo umount -lf $TARGET_ROOTFS_DIR/dev/pts || true
sudo umount -lf $TARGET_ROOTFS_DIR/dev || true
sync
