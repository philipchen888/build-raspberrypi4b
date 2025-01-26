export OUT=$(PWD)/out
export BOOT=$(OUT)/boot.img
export BOOT_UUID=95E46EA5
export BOOTUSB=$(OUT)/bootusb.img
export ARCH=arm64
export CROSS_COMPILE=/usr/bin/aarch64-linux-gnu-

u-boot: builduboot

builduboot:
	cd u-boot; \
	make clean; \
	make ARCH=arm64 rpi_4_defconfig; \
	make -j6

boot:
	mkimage -A arm64 -O linux -T script -C none -d boot_cmd.txt $(OUT)/boot.scr.uimg; \
	\rm -f $(BOOT); \
	mkfs.vfat -n "boot" -i ${BOOT_UUID} -S 512 -C ${BOOT} 512000; \
	mmd -i ${BOOT} ::/overlays; \
	mcopy -i ${BOOT} -s $(OUT)/boot.scr.uimg ::; \
	mcopy -i ${BOOT} -s ./config.txt ::; \
	mcopy -i ${BOOT} -s ./cmdline.txt ::; \
	mcopy -i ${BOOT} -s ./u-boot/u-boot.bin ::; \
	mcopy -i ${BOOT} -s ./firmware/boot/fixup4.dat ::; \
	mcopy -i ${BOOT} -s ./firmware/boot/start4.elf ::; \
	mcopy -i ${BOOT} -s ../kernel/linux/arch/arm64/boot/Image ::; \
	mcopy -i ${BOOT} -s ../kernel/linux/arch/arm64/boot/dts/broadcom/bcm2711-rpi-4-b.dtb ::; \
	mcopy -i ${BOOT} -s ../kernel/linux/arch/arm64/boot/dts/overlays/*.dtb* ::/overlays
	mkimage -A arm64 -O linux -T script -C none -d boot_usbcmd.txt $(OUT)/bootusb.scr.uimg; \
	\rm -f $(BOOTUSB); \
	mkfs.vfat -n "boot" -i ${BOOT_UUID} -S 512 -C ${BOOTUSB} 512000; \
	mmd -i ${BOOTUSB} ::/overlays; \
	mcopy -i ${BOOTUSB} -s $(OUT)/bootusb.scr.uimg ::boot.scr.uimg; \
	mcopy -i ${BOOTUSB} -s ./config.txt ::; \
	mcopy -i ${BOOTUSB} -s ./cmdline.txt ::; \
	mcopy -i ${BOOTUSB} -s ./u-boot/u-boot.bin ::; \
	mcopy -i ${BOOTUSB} -s ./firmware/boot/fixup4.dat ::; \
	mcopy -i ${BOOTUSB} -s ./firmware/boot/start4.elf ::; \
	mcopy -i ${BOOTUSB} -s ../kernel/linux/arch/arm64/boot/Image ::; \
	mcopy -i ${BOOTUSB} -s ../kernel/linux/arch/arm64/boot/dts/broadcom/bcm2711-rpi-4-b.dtb ::; \
	mcopy -i ${BOOTUSB} -s ../kernel/linux/arch/arm64/boot/dts/overlays/*.dtb* ::/overlays
