#!/bin/sh

set -u
set -e

install -m 0644 -D $BUILD_DIR/linux-rpi-6.1.y/arch/arm/boot/dts/bcm2711-rpi-4-b.dtb $BINARIES_DIR/bcm2711-rpi-4-b.dtb

# Add a console on tty1
if [ -e ${TARGET_DIR}/etc/inittab ]; then
    grep -qE '^tty1::' ${TARGET_DIR}/etc/inittab || \
	sed -i '/GENERIC_SERIAL/a\
tty1::respawn:/sbin/getty -L  tty1 0 vt100 # HDMI console' ${TARGET_DIR}/etc/inittab
fi
