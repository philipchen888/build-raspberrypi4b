#!/bin/bash -e

BOOTIMAGE0="linaro-jammyesp.img"
BOOTIMAGE="linaro-esp.img"
BOOT_UUID0=95E46EA5
BOOT_UUID=95E46EA5

echo Making esp!

if [ -e ${BOOTIMAGE} ]; then
	rm ${BOOTIMAGE}
fi
if [ -e ${BOOTIMAGE0} ]; then
        rm ${BOOTIMAGE0}
fi

echo Format boot to vfat
mkfs.vfat -n "boot0" -i ${BOOT_UUID0} -S 512 -C ${BOOTIMAGE0} 512000
mkfs.vfat -n "boot" -i ${BOOT_UUID} -S 512 -C ${BOOTIMAGE} 512000

mmd -i ${BOOTIMAGE} ::/EFI
mmd -i ${BOOTIMAGE} ::/EFI/boot
mmd -i ${BOOTIMAGE} ::/EFI/ubuntu
mcopy -i ${BOOTIMAGE} -s ../linux/patches/ubuntu-noble/grubaa64.efi ::/EFI/boot/bootaa64.efi
mcopy -i ${BOOTIMAGE} -s ../linux/patches/ubuntu-noble/grubaa64.efi ::/EFI/ubuntu
mcopy -i ${BOOTIMAGE} -s ../linux/patches/ubuntu-noble/grub.cfg ::/EFI/ubuntu

mmd -i ${BOOTIMAGE0} ::/EFI
mmd -i ${BOOTIMAGE0} ::/EFI/boot
mmd -i ${BOOTIMAGE0} ::/EFI/ubuntu
mcopy -i ${BOOTIMAGE0} -s ../linux/patches/ubuntu-jammy/grubaa64.efi ::/EFI/boot/bootaa64.efi
mcopy -i ${BOOTIMAGE0} -s ../linux/patches/ubuntu-jammy/grubaa64.efi ::/EFI/ubuntu
mcopy -i ${BOOTIMAGE0} -s ../linux/patches/ubuntu-jammy/grub.cfg ::/EFI/ubuntu

echo Boot Image: ${BOOTIMAGE} ${BOOTIMAGE0}
