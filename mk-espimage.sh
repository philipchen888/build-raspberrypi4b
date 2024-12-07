#!/bin/bash -e

BOOTIMAGE="linaro-esp.img"
BOOT_UUID=95E46EA5

echo Making esp!

if [ -e ${BOOTIMAGE} ]; then
	rm ${BOOTIMAGE}
fi

echo Format boot to vfat
mkfs.vfat -n "boot" -i ${BOOT_UUID} -S 512 -C ${BOOTIMAGE} 512000

mmd -i ${BOOTIMAGE} ::/EFI
mmd -i ${BOOTIMAGE} ::/EFI/boot
mmd -i ${BOOTIMAGE} ::/EFI/debian
mmd -i ${BOOTIMAGE} ::/overlays
mcopy -i ${BOOTIMAGE} -s ../linux/patches/debian/grubaa64.efi ::/EFI/boot/bootaa64.efi
mcopy -i ${BOOTIMAGE} -s ../linux/patches/debian/grubaa64.efi ::/EFI/debian
mcopy -i ${BOOTIMAGE} -s ../linux/patches/debian/grub.cfg ::/EFI/debian
mcopy -i ${BOOTIMAGE} -s ../linux/patches/debian/bcm2711-rpi-400.dtb ::
mcopy -i ${BOOTIMAGE} -s ../linux/patches/debian/bcm2711-rpi-4-b.dtb ::
mcopy -i ${BOOTIMAGE} -s ../linux/patches/debian/bcm2711-rpi-cm4.dtb ::
mcopy -i ${BOOTIMAGE} -s ../linux/patches/debian/config.txt ::
mcopy -i ${BOOTIMAGE} -s ../linux/patches/debian/fixup4.dat ::
mcopy -i ${BOOTIMAGE} -s ../linux/patches/debian/RPI_EFI.fd ::
mcopy -i ${BOOTIMAGE} -s ../linux/patches/debian/start4.elf ::
mcopy -i ${BOOTIMAGE} -s ../linux/patches/debian/overlays/miniuart-bt.dtbo ::/overlays/miniuart-bt.dtbo
mcopy -i ${BOOTIMAGE} -s ../linux/patches/debian/overlays/upstream-pi4.dtbo ::/overlays/upstream-pi4.dtbo

echo Boot Image: ${BOOTIMAGE}
