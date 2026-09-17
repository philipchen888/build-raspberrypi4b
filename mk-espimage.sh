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

if [ "$DISTRIBUTION" == "bookworm" ]; then
	mmd -i ${BOOTIMAGE} ::/EFI/debian
	mcopy -i ${BOOTIMAGE} -s ../kernel/patches/debian/grubaa64.efi ::/EFI/boot/bootaa64.efi
	mcopy -i ${BOOTIMAGE} -s ../kernel/patches/debian/grubaa64.efi ::/EFI/debian
	mcopy -i ${BOOTIMAGE} -s ../kernel/patches/debian/grub.cfg ::/EFI/debian
elif [ "$DISTRIBUTION" == "trixie" ]; then
	mmd -i ${BOOTIMAGE} ::/EFI/debian
	mcopy -i ${BOOTIMAGE} -s ../kernel/patches/trixie/grubaa64.efi ::/EFI/boot/bootaa64.efi
	mcopy -i ${BOOTIMAGE} -s ../kernel/patches/trixie/grubaa64.efi ::/EFI/debian
	mcopy -i ${BOOTIMAGE} -s ../kernel/patches/trixie/grub.cfg ::/EFI/debian
elif [ "$DISTRIBUTION" == "forky" ]; then
	mmd -i ${BOOTIMAGE} ::/EFI/debian
	mcopy -i ${BOOTIMAGE} -s ../kernel/patches/forky/grubaa64.efi ::/EFI/boot/bootaa64.efi
	mcopy -i ${BOOTIMAGE} -s ../kernel/patches/forky/grubaa64.efi ::/EFI/debian
	mcopy -i ${BOOTIMAGE} -s ../kernel/patches/forky/grub.cfg ::/EFI/debian
elif [ "$DISTRIBUTION" == "noble" ]; then
	mmd -i ${BOOTIMAGE} ::/EFI/ubuntu
	mcopy -i ${BOOTIMAGE} -s ../kernel/patches/ubuntu-noble/grubaa64.efi ::/EFI/boot/bootaa64.efi
	mcopy -i ${BOOTIMAGE} -s ../kernel/patches/ubuntu-noble/grubaa64.efi ::/EFI/ubuntu
	mcopy -i ${BOOTIMAGE} -s ../kernel/patches/ubuntu-noble/grub.cfg ::/EFI/ubuntu
elif [ "$DISTRIBUTION" == "questing" ]; then
	mmd -i ${BOOTIMAGE} ::/EFI/ubuntu
	mcopy -i ${BOOTIMAGE} -s ../kernel/patches/ubuntu-questing/grubaa64.efi ::/EFI/boot/bootaa64.efi
	mcopy -i ${BOOTIMAGE} -s ../kernel/patches/ubuntu-questing/grubaa64.efi ::/EFI/ubuntu
	mcopy -i ${BOOTIMAGE} -s ../kernel/patches/ubuntu-questing/grub.cfg ::/EFI/ubuntu
elif [ "$DISTRIBUTION" == "resolute" ]; then
	mmd -i ${BOOTIMAGE} ::/EFI/ubuntu
	mcopy -i ${BOOTIMAGE} -s ../kernel/patches/ubuntu-resolute/grubaa64.efi ::/EFI/boot/bootaa64.efi
	mcopy -i ${BOOTIMAGE} -s ../kernel/patches/ubuntu-resolute/grubaa64.efi ::/EFI/ubuntu
	mcopy -i ${BOOTIMAGE} -s ../kernel/patches/ubuntu-resolute/grub.cfg ::/EFI/ubuntu
fi

echo Boot Image: ${BOOTIMAGE}
