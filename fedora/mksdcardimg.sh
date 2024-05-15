#!/bin/sh
BOOT=/dev/sda
parted ${BOOT} mklabel gpt
parted ${BOOT} unit s mkpart boot fat32 2048  1230847
parted ${BOOT} set 1 boot on
parted ${BOOT} unit s mkpart boot2 ext4 1230848  3327999
parted ${BOOT} unit s mkpart rootfs ext4 3328000 33554431
