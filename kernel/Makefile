export KERNEL=kernel8
export ARCH=arm64
export CROSS_COMPILE=/usr/bin/aarch64-linux-gnu-

clean:
	cd linux; \
	sudo make mrproper

kernel: buildkernel

buildkernel:
	cd linux; \
	sudo \rm -rf tmp; mkdir tmp; mkdir -p tmp/lib; \
	sudo make mrproper; \
	make ARCH=arm64 bcm2711_defconfig; \
	make ARCH=arm64 all -j8; \
	KVER=$$(make ARCH=arm64 -s kernelrelease); \
	sudo make ARCH=arm64 INSTALL_MOD_PATH=./tmp modules_install; \
	sudo make ARCH=arm64 INSTALL_DTBS_PATH=./tmp/boot/dtb dtbs_install; \
	sudo cp System.map ./tmp/boot/System.map-$$KVER; \
	sudo cp .config ./tmp/boot/config-$$KVER; \
	gzip -c arch/arm64/boot/Image | sudo tee ./tmp/boot/vmlinuz-$$KVER > /dev/null; \
	file ./tmp/boot/vmlinuz-$$KVER
	
