apply_patches:
	cd poky/build; \
	cp ../../patches/rpi-cmdline.bb ../meta-raspberrypi/recipes-bsp/bootfiles/; \
	cp ../../patches/sdimage-raspberrypi-gpt.wks ../meta-raspberrypi/wic/; \
	cp -rf ../../patches/resize-helper ../meta-raspberrypi/recipes-bsp/; \
	cp ../../patches/xfce-desktop-image.bb ../meta/recipes-graphics/images/; \
	cp ../../patches/rpi-base.inc ../meta-raspberrypi/conf/machine/include/; \
	cp ../../patches/bblayers.conf ./conf/; \
	cp ../../patches/local.conf ./conf/
