<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* 
 * Emagic EMI 2|6 usb audio पूर्णांकerface firmware loader.
 * Copyright (C) 2002
 * 	Tapio Laxstrथघm (tapio.laxstrom@ipसमय.fi)
 *
 * emi26.c,v 1.13 2002/03/08 13:10:26 tapio Exp
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/ihex.h>

#घोषणा EMI26_VENDOR_ID 		0x086a  /* Emagic Soft-und Hardware GmBH */
#घोषणा EMI26_PRODUCT_ID		0x0100	/* EMI 2|6 without firmware */
#घोषणा EMI26B_PRODUCT_ID		0x0102	/* EMI 2|6 without firmware */

#घोषणा ANCHOR_LOAD_INTERNAL	0xA0	/* Venकरोr specअगरic request code क्रम Anchor Upload/Download (This one is implemented in the core) */
#घोषणा ANCHOR_LOAD_EXTERNAL	0xA3	/* This command is not implemented in the core. Requires firmware */
#घोषणा ANCHOR_LOAD_FPGA	0xA5	/* This command is not implemented in the core. Requires firmware. Emagic extension */
#घोषणा MAX_INTERNAL_ADDRESS	0x1B3F	/* This is the highest पूर्णांकernal RAM address क्रम the AN2131Q */
#घोषणा CPUCS_REG		0x7F92  /* EZ-USB Control and Status Register.  Bit 0 controls 8051 reset */ 
#घोषणा INTERNAL_RAM(address)   (address <= MAX_INTERNAL_ADDRESS)

अटल पूर्णांक emi26_ग_लिखोmemory( काष्ठा usb_device *dev, पूर्णांक address,
			      स्थिर अचिन्हित अक्षर *data, पूर्णांक length,
			      __u8 bRequest);
अटल पूर्णांक emi26_set_reset(काष्ठा usb_device *dev, अचिन्हित अक्षर reset_bit);
अटल पूर्णांक emi26_load_firmware (काष्ठा usb_device *dev);
अटल पूर्णांक emi26_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id);
अटल व्योम emi26_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf);

/* thanks to drivers/usb/serial/keyspan_pda.c code */
अटल पूर्णांक emi26_ग_लिखोmemory (काष्ठा usb_device *dev, पूर्णांक address,
			      स्थिर अचिन्हित अक्षर *data, पूर्णांक length,
			      __u8 request)
अणु
	पूर्णांक result;
	अचिन्हित अक्षर *buffer =  kmemdup(data, length, GFP_KERNEL);

	अगर (!buffer) अणु
		dev_err(&dev->dev, "kmalloc(%d) failed.\n", length);
		वापस -ENOMEM;
	पूर्ण
	/* Note: usb_control_msg वापसs negative value on error or length of the
	 * 		 data that was written! */
	result = usb_control_msg (dev, usb_sndctrlpipe(dev, 0), request, 0x40, address, 0, buffer, length, 300);
	kमुक्त (buffer);
	वापस result;
पूर्ण

/* thanks to drivers/usb/serial/keyspan_pda.c code */
अटल पूर्णांक emi26_set_reset (काष्ठा usb_device *dev, अचिन्हित अक्षर reset_bit)
अणु
	पूर्णांक response;
	dev_info(&dev->dev, "%s - %d\n", __func__, reset_bit);
	/* prपूर्णांकk(KERN_DEBUG "%s - %d", __func__, reset_bit); */
	response = emi26_ग_लिखोmemory (dev, CPUCS_REG, &reset_bit, 1, 0xa0);
	अगर (response < 0) अणु
		dev_err(&dev->dev, "set_reset (%d) failed\n", reset_bit);
	पूर्ण
	वापस response;
पूर्ण

#घोषणा FW_LOAD_SIZE		1023

अटल पूर्णांक emi26_load_firmware (काष्ठा usb_device *dev)
अणु
	स्थिर काष्ठा firmware *loader_fw = शून्य;
	स्थिर काष्ठा firmware *bitstream_fw = शून्य;
	स्थिर काष्ठा firmware *firmware_fw = शून्य;
	स्थिर काष्ठा ihex_binrec *rec;
	पूर्णांक err = -ENOMEM;
	पूर्णांक i;
	__u32 addr;	/* Address to ग_लिखो */
	__u8 *buf;

	buf = kदो_स्मृति(FW_LOAD_SIZE, GFP_KERNEL);
	अगर (!buf)
		जाओ wraperr;

	err = request_ihex_firmware(&loader_fw, "emi26/loader.fw", &dev->dev);
	अगर (err)
		जाओ nofw;

	err = request_ihex_firmware(&bitstream_fw, "emi26/bitstream.fw",
				    &dev->dev);
	अगर (err)
		जाओ nofw;

	err = request_ihex_firmware(&firmware_fw, "emi26/firmware.fw",
				    &dev->dev);
	अगर (err) अणु
	nofw:
		dev_err(&dev->dev, "%s - request_firmware() failed\n",
			__func__);
		जाओ wraperr;
	पूर्ण

	/* Assert reset (stop the CPU in the EMI) */
	err = emi26_set_reset(dev,1);
	अगर (err < 0)
		जाओ wraperr;

	rec = (स्थिर काष्ठा ihex_binrec *)loader_fw->data;
	/* 1. We need to put the loader क्रम the FPGA पूर्णांकo the EZ-USB */
	जबतक (rec) अणु
		err = emi26_ग_लिखोmemory(dev, be32_to_cpu(rec->addr),
					rec->data, be16_to_cpu(rec->len),
					ANCHOR_LOAD_INTERNAL);
		अगर (err < 0)
			जाओ wraperr;
		rec = ihex_next_binrec(rec);
	पूर्ण

	/* De-निश्चित reset (let the CPU run) */
	err = emi26_set_reset(dev,0);
	अगर (err < 0)
		जाओ wraperr;
	msleep(250);	/* let device settle */

	/* 2. We upload the FPGA firmware पूर्णांकo the EMI
	 * Note: collect up to 1023 (yes!) bytes and send them with
	 * a single request. This is _much_ faster! */
	rec = (स्थिर काष्ठा ihex_binrec *)bitstream_fw->data;
	करो अणु
		i = 0;
		addr = be32_to_cpu(rec->addr);

		/* पूर्णांकel hex records are terminated with type 0 element */
		जबतक (rec && (i + be16_to_cpu(rec->len) < FW_LOAD_SIZE)) अणु
			स_नकल(buf + i, rec->data, be16_to_cpu(rec->len));
			i += be16_to_cpu(rec->len);
			rec = ihex_next_binrec(rec);
		पूर्ण
		err = emi26_ग_लिखोmemory(dev, addr, buf, i, ANCHOR_LOAD_FPGA);
		अगर (err < 0)
			जाओ wraperr;
	पूर्ण जबतक (rec);

	/* Assert reset (stop the CPU in the EMI) */
	err = emi26_set_reset(dev,1);
	अगर (err < 0)
		जाओ wraperr;

	/* 3. We need to put the loader क्रम the firmware पूर्णांकo the EZ-USB (again...) */
	क्रम (rec = (स्थिर काष्ठा ihex_binrec *)loader_fw->data;
	     rec; rec = ihex_next_binrec(rec)) अणु
		err = emi26_ग_लिखोmemory(dev, be32_to_cpu(rec->addr),
					rec->data, be16_to_cpu(rec->len),
					ANCHOR_LOAD_INTERNAL);
		अगर (err < 0)
			जाओ wraperr;
	पूर्ण
	msleep(250);	/* let device settle */

	/* De-निश्चित reset (let the CPU run) */
	err = emi26_set_reset(dev,0);
	अगर (err < 0)
		जाओ wraperr;

	/* 4. We put the part of the firmware that lies in the बाह्यal RAM पूर्णांकo the EZ-USB */

	क्रम (rec = (स्थिर काष्ठा ihex_binrec *)firmware_fw->data;
	     rec; rec = ihex_next_binrec(rec)) अणु
		अगर (!INTERNAL_RAM(be32_to_cpu(rec->addr))) अणु
			err = emi26_ग_लिखोmemory(dev, be32_to_cpu(rec->addr),
						rec->data, be16_to_cpu(rec->len),
						ANCHOR_LOAD_EXTERNAL);
			अगर (err < 0)
				जाओ wraperr;
		पूर्ण
	पूर्ण

	/* Assert reset (stop the CPU in the EMI) */
	err = emi26_set_reset(dev,1);
	अगर (err < 0)
		जाओ wraperr;

	क्रम (rec = (स्थिर काष्ठा ihex_binrec *)firmware_fw->data;
	     rec; rec = ihex_next_binrec(rec)) अणु
		अगर (INTERNAL_RAM(be32_to_cpu(rec->addr))) अणु
			err = emi26_ग_लिखोmemory(dev, be32_to_cpu(rec->addr),
						rec->data, be16_to_cpu(rec->len),
						ANCHOR_LOAD_INTERNAL);
			अगर (err < 0)
				जाओ wraperr;
		पूर्ण
	पूर्ण

	/* De-निश्चित reset (let the CPU run) */
	err = emi26_set_reset(dev,0);
	अगर (err < 0)
		जाओ wraperr;
	msleep(250);	/* let device settle */

	/* वापस 1 to fail the driver inialization
	 * and give real driver change to load */
	err = 1;

wraperr:
	अगर (err < 0)
		dev_err(&dev->dev,"%s - error loading firmware: error = %d\n",
			__func__, err);

	release_firmware(loader_fw);
	release_firmware(bitstream_fw);
	release_firmware(firmware_fw);

	kमुक्त(buf);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(EMI26_VENDOR_ID, EMI26_PRODUCT_ID) पूर्ण,
	अणु USB_DEVICE(EMI26_VENDOR_ID, EMI26B_PRODUCT_ID) पूर्ण,
	अणु पूर्ण                                             /* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE (usb, id_table);

अटल पूर्णांक emi26_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	dev_info(&पूर्णांकf->dev, "%s start\n", __func__);

	emi26_load_firmware(dev);

	/* करो not वापस the driver context, let real audio driver करो that */
	वापस -EIO;
पूर्ण

अटल व्योम emi26_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
पूर्ण

अटल काष्ठा usb_driver emi26_driver = अणु
	.name		= "emi26 - firmware loader",
	.probe		= emi26_probe,
	.disconnect	= emi26_disconnect,
	.id_table	= id_table,
पूर्ण;

module_usb_driver(emi26_driver);

MODULE_AUTHOR("Tapio Laxstrथघm");
MODULE_DESCRIPTION("Emagic EMI 2|6 firmware loader.");
MODULE_LICENSE("GPL");

MODULE_FIRMWARE("emi26/loader.fw");
MODULE_FIRMWARE("emi26/bitstream.fw");
MODULE_FIRMWARE("emi26/firmware.fw");
/* vi:ai:syntax=c:sw=8:ts=8:tw=80
 */
