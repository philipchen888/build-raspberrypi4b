export BOARD=rpi4b
export LB_BOOTSTRAP_INCLUDE="apt-transport-https gnupg"
export ARCH=arm
export CROSS_COMPILE=/usr/local/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-

rootfs: clean prebuild buildrootfs postbuild mkimage
basicrootfs: clean prebuild buildbasicrootfs postbuild mkbasicimage

clean:
	sudo lb clean --purge
	\rm -rf config .build rootfs

cleanall:
	sudo lb clean --purge
	\rm -rf config .build rootfs
	\rm -rf linaro-rootfs.img linaro-basicrootfs.img

prebuild:
	lb config \
	--apt-indices false \
	--apt-recommends false \
	--apt-secure false \
	--architectures armhf \
	--archive-areas 'main contrib non-free' \
	--backports false \
	--binary-filesystem ext4 \
	--binary-images tar \
	--bootappend-live "hostname=linaro-alip username=linaro" \
	--bootstrap-qemu-arch armhf \
	--bootstrap-qemu-static /usr/bin/qemu-arm-static \
	--cache false \
	--chroot-filesystem none \
	--compression gzip \
	--debootstrap-options "--variant=minbase --include=apt-transport-https,gnupg" \
	--distribution bullseye \
	--gzip-options '-9 --rsyncable' \
	--iso-publisher 'Linaro; http://www.linaro.org/; linaro-dev@lists.linaro.org' \
	--iso-volume 'Linaro Bullseye $(date +%Y%m%d-%H:%M)' \
	--linux-flavours none \
	--linux-packages none \
	--mode debian \
	--security true \
	--system normal \
	--updates true

buildrootfs:
	\cp -rf $(PWD)/../customization/* config/
	cp linaro.list.chroot config/package-lists/linaro.list.chroot
	sudo lb build

buildbasicrootfs:
	\cp -rf $(PWD)/../customization/* config/
	cp linaro.list.chroot.basic config/package-lists/linaro.list.chroot
	sudo lb build

postbuild:
	ARCH=armhf $(PWD)/../mk-rootfs-bullseye.sh

mkimage:
	$(PWD)/../mk-image.sh

mkbasicimage:
	$(PWD)/../mk-basicimage.sh
