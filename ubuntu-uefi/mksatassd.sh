#!/bin/sh
BOOT=/dev/sda
parted -s ${BOOT} mklabel gpt
parted -s ${BOOT} -- unit s mkpart boot2 ext4 32768 -34s
