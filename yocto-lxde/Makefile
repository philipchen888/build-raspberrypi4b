apply_patches:
	cd poky/build; \
	cp ../../patches/linux-raspberrypi.inc ../meta-raspberrypi/recipes-kernel/linux/; \
	cp ../../patches/sdimage-raspberrypi-gpt.wks ../meta-raspberrypi/wic/; \
	cp ../../patches/sdcard_image-rpi.bbclass ../meta-raspberrypi/classes/; \
	cp -rf ../../patches/resize-helper ../meta-raspberrypi/recipes-bsp/; \
	cp ../../patches/rpi-base.inc ../meta-raspberrypi/conf/machine/include/; \
	cp ../../patches/lxsession_0.5.4.bb ../meta-lxde/recipes-lxde/lxsession/; \
	cp ../../patches/bblayers.conf ./conf/; \
	cp ../../patches/local.conf ./conf/
