#!/bin/sh
BOOT=/dev/sda
dd if=/dev/zero of=${BOOT} bs=1M count=0 seek=8192
parted -s ${BOOT} mklabel gpt
parted -s ${BOOT} unit s mkpart boot 32768 1081343
parted -s ${BOOT} set 1 boot on
parted -s ${BOOT} -- unit s mkpart rootfs 1081344 -34s
ROOT_UUID="B921B045-1DF0-41C3-AF44-4C6F280D3FAE"
gdisk ${BOOT} <<EOF
x
c
2
${ROOT_UUID}
w
y
EOF
dd if=../uboot/out/bootusb.img of=${BOOT} bs=4096 seek=4096 conv=notrunc,fsync
dd if=../rootfs-ubuntu-oracular/linaro-rootfs.img of=${BOOT} bs=4096 seek=135168 conv=notrunc,fsync
