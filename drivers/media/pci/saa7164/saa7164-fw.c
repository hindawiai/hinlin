<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the NXP SAA7164 PCIe bridge
 *
 *  Copyright (c) 2010-2015 Steven Toth <stoth@kernelद_असल.com>
 */

#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>

#समावेश "saa7164.h"

#घोषणा SAA7164_REV2_FIRMWARE		"NXP7164-2010-03-10.1.fw"
#घोषणा SAA7164_REV2_FIRMWARE_SIZE	4019072

#घोषणा SAA7164_REV3_FIRMWARE		"NXP7164-2010-03-10.1.fw"
#घोषणा SAA7164_REV3_FIRMWARE_SIZE	4019072

काष्ठा fw_header अणु
	u32	firmwaresize;
	u32	bslsize;
	u32	reserved;
	u32	version;
पूर्ण;

अटल पूर्णांक saa7164_dl_रुको_ack(काष्ठा saa7164_dev *dev, u32 reg)
अणु
	u32 समयout = SAA_DEVICE_TIMEOUT;
	जबतक ((saa7164_पढ़ोl(reg) & 0x01) == 0) अणु
		समयout -= 10;
		अगर (समयout == 0) अणु
			prपूर्णांकk(KERN_ERR "%s() timeout (no d/l ack)\n",
				__func__);
			वापस -EBUSY;
		पूर्ण
		msleep(100);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक saa7164_dl_रुको_clr(काष्ठा saa7164_dev *dev, u32 reg)
अणु
	u32 समयout = SAA_DEVICE_TIMEOUT;
	जबतक (saa7164_पढ़ोl(reg) & 0x01) अणु
		समयout -= 10;
		अगर (समयout == 0) अणु
			prपूर्णांकk(KERN_ERR "%s() timeout (no d/l clr)\n",
				__func__);
			वापस -EBUSY;
		पूर्ण
		msleep(100);
	पूर्ण

	वापस 0;
पूर्ण

/* TODO: move dlflags पूर्णांकo dev-> and change to ग_लिखो/पढ़ोl/b */
/* TODO: Excessive levels of debug */
अटल पूर्णांक saa7164_करोwnloadimage(काष्ठा saa7164_dev *dev, u8 *src, u32 srcsize,
				 u32 dlflags, u8 __iomem *dst, u32 dstsize)
अणु
	u32 reg, समयout, offset;
	u8 *srcbuf = शून्य;
	पूर्णांक ret;

	u32 dlflag = dlflags;
	u32 dlflag_ack = dlflag + 4;
	u32 drflag = dlflag_ack + 4;
	u32 drflag_ack = drflag + 4;
	u32 bleflag = drflag_ack + 4;

	dprपूर्णांकk(DBGLVL_FW,
		"%s(image=%p, size=%d, flags=0x%x, dst=%p, dstsize=0x%x)\n",
		__func__, src, srcsize, dlflags, dst, dstsize);

	अगर ((src == शून्य) || (dst == शून्य)) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	srcbuf = kzalloc(4 * 1048576, GFP_KERNEL);
	अगर (शून्य == srcbuf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (srcsize > (4*1048576)) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	स_नकल(srcbuf, src, srcsize);

	dprपूर्णांकk(DBGLVL_FW, "%s() dlflag = 0x%x\n", __func__, dlflag);
	dprपूर्णांकk(DBGLVL_FW, "%s() dlflag_ack = 0x%x\n", __func__, dlflag_ack);
	dprपूर्णांकk(DBGLVL_FW, "%s() drflag = 0x%x\n", __func__, drflag);
	dprपूर्णांकk(DBGLVL_FW, "%s() drflag_ack = 0x%x\n", __func__, drflag_ack);
	dprपूर्णांकk(DBGLVL_FW, "%s() bleflag = 0x%x\n", __func__, bleflag);

	reg = saa7164_पढ़ोl(dlflag);
	dprपूर्णांकk(DBGLVL_FW, "%s() dlflag (0x%x)= 0x%x\n", __func__, dlflag, reg);
	अगर (reg == 1)
		dprपूर्णांकk(DBGLVL_FW,
			"%s() Download flag already set, please reboot\n",
			__func__);

	/* Indicate करोwnload start */
	saa7164_ग_लिखोl(dlflag, 1);
	ret = saa7164_dl_रुको_ack(dev, dlflag_ack);
	अगर (ret < 0)
		जाओ out;

	/* Ack करोwnload start, then रुको क्रम रुको */
	saa7164_ग_लिखोl(dlflag, 0);
	ret = saa7164_dl_रुको_clr(dev, dlflag_ack);
	अगर (ret < 0)
		जाओ out;

	/* Deal with the raw firmware, in the appropriate chunk size */
	क्रम (offset = 0; srcsize > dstsize;
		srcsize -= dstsize, offset += dstsize) अणु

		dprपूर्णांकk(DBGLVL_FW, "%s() memcpy %d\n", __func__, dstsize);
		स_नकल_toio(dst, srcbuf + offset, dstsize);

		/* Flag the data as पढ़ोy */
		saa7164_ग_लिखोl(drflag, 1);
		ret = saa7164_dl_रुको_ack(dev, drflag_ack);
		अगर (ret < 0)
			जाओ out;

		/* Wait क्रम indication data was received */
		saa7164_ग_लिखोl(drflag, 0);
		ret = saa7164_dl_रुको_clr(dev, drflag_ack);
		अगर (ret < 0)
			जाओ out;

	पूर्ण

	dprपूर्णांकk(DBGLVL_FW, "%s() memcpy(l) %d\n", __func__, dstsize);
	/* Write last block to the device */
	स_नकल_toio(dst, srcbuf+offset, srcsize);

	/* Flag the data as पढ़ोy */
	saa7164_ग_लिखोl(drflag, 1);
	ret = saa7164_dl_रुको_ack(dev, drflag_ack);
	अगर (ret < 0)
		जाओ out;

	saa7164_ग_लिखोl(drflag, 0);
	समयout = 0;
	जबतक (saa7164_पढ़ोl(bleflag) != SAA_DEVICE_IMAGE_BOOTING) अणु
		अगर (saa7164_पढ़ोl(bleflag) & SAA_DEVICE_IMAGE_CORRUPT) अणु
			prपूर्णांकk(KERN_ERR "%s() image corrupt\n", __func__);
			ret = -EBUSY;
			जाओ out;
		पूर्ण

		अगर (saa7164_पढ़ोl(bleflag) & SAA_DEVICE_MEMORY_CORRUPT) अणु
			prपूर्णांकk(KERN_ERR "%s() device memory corrupt\n",
				__func__);
			ret = -EBUSY;
			जाओ out;
		पूर्ण

		msleep(10); /* Checkpatch throws a < 20ms warning */
		अगर (समयout++ > 60)
			अवरोध;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s() Image downloaded, booting...\n", __func__);

	ret = saa7164_dl_रुको_clr(dev, drflag_ack);
	अगर (ret < 0)
		जाओ out;

	prपूर्णांकk(KERN_INFO "%s() Image booted successfully.\n", __func__);
	ret = 0;

out:
	kमुक्त(srcbuf);
	वापस ret;
पूर्ण

/* TODO: Excessive debug */
/* Load the firmware. Optionally it can be in ROM or newer versions
 * can be on disk, saving the expense of the ROM hardware. */
पूर्णांक saa7164_करोwnloadfirmware(काष्ठा saa7164_dev *dev)
अणु
	/* u32 second_समयout = 60 * SAA_DEVICE_TIMEOUT; */
	u32 पंचांगp, filesize, version, err_flags, first_समयout, fwlength;
	u32 second_समयout, updatebootloader = 1, bootloadersize = 0;
	स्थिर काष्ठा firmware *fw = शून्य;
	काष्ठा fw_header *hdr, *boothdr = शून्य, *fwhdr;
	u32 bootloaderversion = 0, fwloadersize;
	u8 *bootloaderoffset = शून्य, *fwloaderoffset;
	अक्षर *fwname;
	पूर्णांक ret;

	dprपूर्णांकk(DBGLVL_FW, "%s()\n", __func__);

	अगर (saa7164_boards[dev->board].chiprev == SAA7164_CHIP_REV2) अणु
		fwname = SAA7164_REV2_FIRMWARE;
		fwlength = SAA7164_REV2_FIRMWARE_SIZE;
	पूर्ण अन्यथा अणु
		fwname = SAA7164_REV3_FIRMWARE;
		fwlength = SAA7164_REV3_FIRMWARE_SIZE;
	पूर्ण

	version = saa7164_अ_लोurrentfirmwareversion(dev);

	अगर (version == 0x00) अणु

		second_समयout = 100;
		first_समयout = 100;
		err_flags = saa7164_पढ़ोl(SAA_BOOTLOADERERROR_FLAGS);
		dprपूर्णांकk(DBGLVL_FW, "%s() err_flags = %x\n",
			__func__, err_flags);

		जबतक (err_flags != SAA_DEVICE_IMAGE_BOOTING) अणु
			dprपूर्णांकk(DBGLVL_FW, "%s() err_flags = %x\n",
				__func__, err_flags);
			msleep(10); /* Checkpatch throws a < 20ms warning */

			अगर (err_flags & SAA_DEVICE_IMAGE_CORRUPT) अणु
				prपूर्णांकk(KERN_ERR "%s() firmware corrupt\n",
					__func__);
				अवरोध;
			पूर्ण
			अगर (err_flags & SAA_DEVICE_MEMORY_CORRUPT) अणु
				prपूर्णांकk(KERN_ERR "%s() device memory corrupt\n",
					__func__);
				अवरोध;
			पूर्ण
			अगर (err_flags & SAA_DEVICE_NO_IMAGE) अणु
				prपूर्णांकk(KERN_ERR "%s() no first image\n",
				__func__);
				अवरोध;
			पूर्ण
			अगर (err_flags & SAA_DEVICE_IMAGE_SEARCHING) अणु
				first_समयout -= 10;
				अगर (first_समयout == 0) अणु
					prपूर्णांकk(KERN_ERR
						"%s() no first image\n",
						__func__);
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अगर (err_flags & SAA_DEVICE_IMAGE_LOADING) अणु
				second_समयout -= 10;
				अगर (second_समयout == 0) अणु
					prपूर्णांकk(KERN_ERR
					"%s() FW load time exceeded\n",
						__func__);
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				second_समयout -= 10;
				अगर (second_समयout == 0) अणु
					prपूर्णांकk(KERN_ERR
					"%s() Unknown bootloader flags 0x%x\n",
						__func__, err_flags);
					अवरोध;
				पूर्ण
			पूर्ण

			err_flags = saa7164_पढ़ोl(SAA_BOOTLOADERERROR_FLAGS);
		पूर्ण /* While != Booting */

		अगर (err_flags == SAA_DEVICE_IMAGE_BOOTING) अणु
			dprपूर्णांकk(DBGLVL_FW, "%s() Loader 1 has loaded.\n",
				__func__);
			first_समयout = SAA_DEVICE_TIMEOUT;
			second_समयout = 60 * SAA_DEVICE_TIMEOUT;
			second_समयout = 100;

			err_flags = saa7164_पढ़ोl(SAA_SECONDSTAGEERROR_FLAGS);
			dprपूर्णांकk(DBGLVL_FW, "%s() err_flags2 = %x\n",
				__func__, err_flags);
			जबतक (err_flags != SAA_DEVICE_IMAGE_BOOTING) अणु
				dprपूर्णांकk(DBGLVL_FW, "%s() err_flags2 = %x\n",
					__func__, err_flags);
				msleep(10); /* Checkpatch throws a < 20ms warning */

				अगर (err_flags & SAA_DEVICE_IMAGE_CORRUPT) अणु
					prपूर्णांकk(KERN_ERR
						"%s() firmware corrupt\n",
						__func__);
					अवरोध;
				पूर्ण
				अगर (err_flags & SAA_DEVICE_MEMORY_CORRUPT) अणु
					prपूर्णांकk(KERN_ERR
						"%s() device memory corrupt\n",
						__func__);
					अवरोध;
				पूर्ण
				अगर (err_flags & SAA_DEVICE_NO_IMAGE) अणु
					prपूर्णांकk(KERN_ERR "%s() no second image\n",
						__func__);
					अवरोध;
				पूर्ण
				अगर (err_flags & SAA_DEVICE_IMAGE_SEARCHING) अणु
					first_समयout -= 10;
					अगर (first_समयout == 0) अणु
						prपूर्णांकk(KERN_ERR
						"%s() no second image\n",
							__func__);
						अवरोध;
					पूर्ण
				पूर्ण अन्यथा अगर (err_flags &
					SAA_DEVICE_IMAGE_LOADING) अणु
					second_समयout -= 10;
					अगर (second_समयout == 0) अणु
						prपूर्णांकk(KERN_ERR
						"%s() FW load time exceeded\n",
							__func__);
						अवरोध;
					पूर्ण
				पूर्ण अन्यथा अणु
					second_समयout -= 10;
					अगर (second_समयout == 0) अणु
						prपूर्णांकk(KERN_ERR
					"%s() Unknown bootloader flags 0x%x\n",
							__func__, err_flags);
						अवरोध;
					पूर्ण
				पूर्ण

				err_flags =
				saa7164_पढ़ोl(SAA_SECONDSTAGEERROR_FLAGS);
			पूर्ण /* err_flags != SAA_DEVICE_IMAGE_BOOTING */

			dprपूर्णांकk(DBGLVL_FW, "%s() Loader flags 1:0x%x 2:0x%x.\n",
				__func__,
				saa7164_पढ़ोl(SAA_BOOTLOADERERROR_FLAGS),
				saa7164_पढ़ोl(SAA_SECONDSTAGEERROR_FLAGS));

		पूर्ण /* err_flags == SAA_DEVICE_IMAGE_BOOTING */

		/* It's possible क्रम both firmwares to have booted,
		 * but that करोesn't mean they've finished booting yet.
		 */
		अगर ((saa7164_पढ़ोl(SAA_BOOTLOADERERROR_FLAGS) ==
			SAA_DEVICE_IMAGE_BOOTING) &&
			(saa7164_पढ़ोl(SAA_SECONDSTAGEERROR_FLAGS) ==
			SAA_DEVICE_IMAGE_BOOTING)) अणु


			dprपूर्णांकk(DBGLVL_FW, "%s() Loader 2 has loaded.\n",
				__func__);

			first_समयout = SAA_DEVICE_TIMEOUT;
			जबतक (first_समयout) अणु
				msleep(10); /* Checkpatch throws a < 20ms warning */

				version =
					saa7164_अ_लोurrentfirmwareversion(dev);
				अगर (version) अणु
					dprपूर्णांकk(DBGLVL_FW,
					"%s() All f/w loaded successfully\n",
						__func__);
					अवरोध;
				पूर्ण अन्यथा अणु
					first_समयout -= 10;
					अगर (first_समयout == 0) अणु
						prपूर्णांकk(KERN_ERR
						"%s() FW did not boot\n",
							__func__);
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		version = saa7164_अ_लोurrentfirmwareversion(dev);
	पूर्ण /* version == 0 */

	/* Has the firmware really booted? */
	अगर ((saa7164_पढ़ोl(SAA_BOOTLOADERERROR_FLAGS) ==
		SAA_DEVICE_IMAGE_BOOTING) &&
		(saa7164_पढ़ोl(SAA_SECONDSTAGEERROR_FLAGS) ==
		SAA_DEVICE_IMAGE_BOOTING) && (version == 0)) अणु

		prपूर्णांकk(KERN_ERR
			"%s() The firmware hung, probably bad firmware\n",
			__func__);

		/* Tell the second stage loader we have a deadlock */
		saa7164_ग_लिखोl(SAA_DEVICE_DEADLOCK_DETECTED_OFFSET,
			SAA_DEVICE_DEADLOCK_DETECTED);

		saa7164_getfirmwarestatus(dev);

		वापस -ENOMEM;
	पूर्ण

	dprपूर्णांकk(DBGLVL_FW, "Device has Firmware Version %d.%d.%d.%d\n",
		(version & 0x0000fc00) >> 10,
		(version & 0x000003e0) >> 5,
		(version & 0x0000001f),
		(version & 0xffff0000) >> 16);

	/* Load the firmware from the disk अगर required */
	अगर (version == 0) अणु

		prपूर्णांकk(KERN_INFO "%s() Waiting for firmware upload (%s)\n",
			__func__, fwname);

		ret = request_firmware(&fw, fwname, &dev->pci->dev);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "%s() Upload failed. (file not found?)\n",
			       __func__);
			वापस -ENOMEM;
		पूर्ण

		prपूर्णांकk(KERN_INFO "%s() firmware read %zu bytes.\n",
			__func__, fw->size);

		अगर (fw->size != fwlength) अणु
			prपूर्णांकk(KERN_ERR "saa7164: firmware incorrect size %zu != %u\n",
				fw->size, fwlength);
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		prपूर्णांकk(KERN_INFO "%s() firmware loaded.\n", __func__);

		hdr = (काष्ठा fw_header *)fw->data;
		prपूर्णांकk(KERN_INFO "Firmware file header part 1:\n");
		prपूर्णांकk(KERN_INFO " .FirmwareSize = 0x%x\n", hdr->firmwaresize);
		prपूर्णांकk(KERN_INFO " .BSLSize = 0x%x\n", hdr->bslsize);
		prपूर्णांकk(KERN_INFO " .Reserved = 0x%x\n", hdr->reserved);
		prपूर्णांकk(KERN_INFO " .Version = 0x%x\n", hdr->version);

		/* Retrieve bootloader अगर reqd */
		अगर ((hdr->firmwaresize == 0) && (hdr->bslsize == 0))
			/* Second bootloader in the firmware file */
			filesize = hdr->reserved * 16;
		अन्यथा
			filesize = (hdr->firmwaresize + hdr->bslsize) *
				16 + माप(काष्ठा fw_header);

		prपूर्णांकk(KERN_INFO "%s() SecBootLoader.FileSize = %d\n",
			__func__, filesize);

		/* Get bootloader (अगर reqd) and firmware header */
		अगर ((hdr->firmwaresize == 0) && (hdr->bslsize == 0)) अणु
			/* Second boot loader is required */

			/* Get the loader header */
			boothdr = (काष्ठा fw_header *)(fw->data +
				माप(काष्ठा fw_header));

			bootloaderversion =
				saa7164_पढ़ोl(SAA_DEVICE_2ND_VERSION);
			dprपूर्णांकk(DBGLVL_FW, "Onboard BootLoader:\n");
			dprपूर्णांकk(DBGLVL_FW, "->Flag 0x%x\n",
				saa7164_पढ़ोl(SAA_BOOTLOADERERROR_FLAGS));
			dprपूर्णांकk(DBGLVL_FW, "->Ack 0x%x\n",
				saa7164_पढ़ोl(SAA_DATAREADY_FLAG_ACK));
			dprपूर्णांकk(DBGLVL_FW, "->FW Version 0x%x\n", version);
			dprपूर्णांकk(DBGLVL_FW, "->Loader Version 0x%x\n",
				bootloaderversion);

			अगर ((saa7164_पढ़ोl(SAA_BOOTLOADERERROR_FLAGS) ==
				0x03) && (saa7164_पढ़ोl(SAA_DATAREADY_FLAG_ACK)
				== 0x00) && (version == 0x00)) अणु

				dprपूर्णांकk(DBGLVL_FW, "BootLoader version in  rom %d.%d.%d.%d\n",
					(bootloaderversion & 0x0000fc00) >> 10,
					(bootloaderversion & 0x000003e0) >> 5,
					(bootloaderversion & 0x0000001f),
					(bootloaderversion & 0xffff0000) >> 16
					);
				dprपूर्णांकk(DBGLVL_FW, "BootLoader version in file %d.%d.%d.%d\n",
					(boothdr->version & 0x0000fc00) >> 10,
					(boothdr->version & 0x000003e0) >> 5,
					(boothdr->version & 0x0000001f),
					(boothdr->version & 0xffff0000) >> 16
					);

				अगर (bootloaderversion == boothdr->version)
					updatebootloader = 0;
			पूर्ण

			/* Calculate offset to firmware header */
			पंचांगp = (boothdr->firmwaresize + boothdr->bslsize) * 16 +
				(माप(काष्ठा fw_header) +
				माप(काष्ठा fw_header));

			fwhdr = (काष्ठा fw_header *)(fw->data+पंचांगp);
		पूर्ण अन्यथा अणु
			/* No second boot loader */
			fwhdr = hdr;
		पूर्ण

		dprपूर्णांकk(DBGLVL_FW, "Firmware version in file %d.%d.%d.%d\n",
			(fwhdr->version & 0x0000fc00) >> 10,
			(fwhdr->version & 0x000003e0) >> 5,
			(fwhdr->version & 0x0000001f),
			(fwhdr->version & 0xffff0000) >> 16
			);

		अगर (version == fwhdr->version) अणु
			/* No करोwnload, firmware alपढ़ोy on board */
			ret = 0;
			जाओ out;
		पूर्ण

		अगर ((hdr->firmwaresize == 0) && (hdr->bslsize == 0)) अणु
			अगर (updatebootloader) अणु
				/* Get पढ़ोy to upload the bootloader */
				bootloadersize = (boothdr->firmwaresize +
					boothdr->bslsize) * 16 +
					माप(काष्ठा fw_header);

				bootloaderoffset = (u8 *)(fw->data +
					माप(काष्ठा fw_header));

				dprपूर्णांकk(DBGLVL_FW, "bootloader d/l starts.\n");
				prपूर्णांकk(KERN_INFO "%s() FirmwareSize = 0x%x\n",
					__func__, boothdr->firmwaresize);
				prपूर्णांकk(KERN_INFO "%s() BSLSize = 0x%x\n",
					__func__, boothdr->bslsize);
				prपूर्णांकk(KERN_INFO "%s() Reserved = 0x%x\n",
					__func__, boothdr->reserved);
				prपूर्णांकk(KERN_INFO "%s() Version = 0x%x\n",
					__func__, boothdr->version);
				ret = saa7164_करोwnloadimage(
					dev,
					bootloaderoffset,
					bootloadersize,
					SAA_DOWNLOAD_FLAGS,
					dev->bmmio + SAA_DEVICE_DOWNLOAD_OFFSET,
					SAA_DEVICE_BUFFERBLOCKSIZE);
				अगर (ret < 0) अणु
					prपूर्णांकk(KERN_ERR
						"bootloader d/l has failed\n");
					जाओ out;
				पूर्ण
				dprपूर्णांकk(DBGLVL_FW,
					"bootloader download complete.\n");

			पूर्ण

			prपूर्णांकk(KERN_ERR "starting firmware download(2)\n");
			bootloadersize = (boothdr->firmwaresize +
				boothdr->bslsize) * 16 +
				माप(काष्ठा fw_header);

			bootloaderoffset =
				(u8 *)(fw->data + माप(काष्ठा fw_header));

			fwloaderoffset = bootloaderoffset + bootloadersize;

			/* TODO: fix this bounds overrun here with old f/ws */
			fwloadersize = (fwhdr->firmwaresize + fwhdr->bslsize) *
				16 + माप(काष्ठा fw_header);

			ret = saa7164_करोwnloadimage(
				dev,
				fwloaderoffset,
				fwloadersize,
				SAA_DEVICE_2ND_DOWNLOADFLAG_OFFSET,
				dev->bmmio + SAA_DEVICE_2ND_DOWNLOAD_OFFSET,
				SAA_DEVICE_2ND_BUFFERBLOCKSIZE);
			अगर (ret < 0) अणु
				prपूर्णांकk(KERN_ERR "firmware download failed\n");
				जाओ out;
			पूर्ण
			prपूर्णांकk(KERN_ERR "firmware download complete.\n");

		पूर्ण अन्यथा अणु

			/* No bootloader update reqd, करोwnload firmware only */
			prपूर्णांकk(KERN_ERR "starting firmware download(3)\n");

			ret = saa7164_करोwnloadimage(
				dev,
				(u8 *)fw->data,
				fw->size,
				SAA_DOWNLOAD_FLAGS,
				dev->bmmio + SAA_DEVICE_DOWNLOAD_OFFSET,
				SAA_DEVICE_BUFFERBLOCKSIZE);
			अगर (ret < 0) अणु
				prपूर्णांकk(KERN_ERR "firmware download failed\n");
				जाओ out;
			पूर्ण
			prपूर्णांकk(KERN_ERR "firmware download complete.\n");
		पूर्ण
	पूर्ण

	dev->firmwareloaded = 1;
	ret = 0;

out:
	release_firmware(fw);
	वापस ret;
पूर्ण
