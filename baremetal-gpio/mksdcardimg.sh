#!/bin/sh
export BOOTIMG=./boot.img
\rm ${BOOTIMG}
mkfs.vfat -n "boot" -S 512 -C ${BOOTIMG} 256000
mmd -i ${BOOTIMG} ::/overlays
mcopy -i ${BOOTIMG} -s ./firmware/boot/fixup4.dat ::
mcopy -i ${BOOTIMG} -s ./firmware/boot/start4.elf ::
mcopy -i ${BOOTIMG} -s ./firmware/boot/bootcode.bin ::
mcopy -i ${BOOTIMG} -s ./firmware/boot/bcm2711-rpi-4-b.dtb ::
mcopy -i ${BOOTIMG} -s ./firmware/boot/overlays/*.dtb* ::/overlays
mcopy -i ${BOOTIMG} -s ./firmware/boot/overlays/README ::/overlays
mcopy -i ${BOOTIMG} -s ./kernel8.img ::
mcopy -i ${BOOTIMG} -s ./cmdline.txt ::
mcopy -i ${BOOTIMG} -s ./config.txt ::
export BOOT=./sdcard.img
\rm ${BOOT}
dd if=/dev/zero of=${BOOT} bs=1M count=0 seek=300
fdisk ${BOOT} <<EOF
o
n
p
1
8192
532479
n
p
2
532480

t
1
c
t
2
83
a
1
w
q
EOF
dd if=./boot.img of=${BOOT} seek=8192 conv=notrunc,fsync
