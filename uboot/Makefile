export OUT=$(PWD)/out
export BOOT=$(OUT)/boot.img
export BOOTBUSTER=$(OUT)/bootbuster.img
export ARCH=arm64
export CROSS_COMPILE=/usr/local/gcc-linaro-7.5.0-2019.12-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-

u-boot: builduboot

builduboot:
	cd u-boot; \
	make clean; \
	make ARCH=arm64 rpi_4_defconfig; \
	make -j6

boot:
	mkimage -A arm64 -O linux -T script -C none -d boot_cmd.txt $(OUT)/boot.scr.uimg; \
	\rm -f $(BOOT); \
	mkfs.vfat -n "boot" -S 512 -C ${BOOT} 65536; \
	mmd -i ${BOOT} ::/overlays; \
	mcopy -i ${BOOT} -s $(OUT)/boot.scr.uimg ::; \
	mcopy -i ${BOOT} -s ./config.txt ::; \
	mcopy -i ${BOOT} -s ./cmdline.txt ::; \
	mcopy -i ${BOOT} -s ./u-boot/u-boot.bin ::; \
	mcopy -i ${BOOT} -s ./firmware/boot/fixup4.dat ::; \
	mcopy -i ${BOOT} -s ./firmware/boot/start4.elf ::; \
	mcopy -i ${BOOT} -s ../linux/linux/arch/arm64/boot/Image ::; \
	mcopy -i ${BOOT} -s ../linux/linux/arch/arm64/boot/dts/broadcom/bcm2711-rpi-4-b.dtb ::; \
	mcopy -i ${BOOT} -s ../linux/linux/arch/arm64/boot/dts/overlays/*.dtb* ::/overlays
