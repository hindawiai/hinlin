<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम loading USB isight firmware
 *
 * Copyright (C) 2008 Matthew Garrett <mjg@redhat.com>
 *
 * The USB isight cameras in recent Apples are roughly compatible with the USB
 * video class specअगरication, and can be driven by uvcvideo. However, they
 * need firmware to be loaded beक्रमehand. After firmware loading, the device
 * detaches from the USB bus and reattaches with a new device ID. It can then
 * be claimed by the uvc driver.
 *
 * The firmware is non-मुक्त and must be extracted by the user. Tools to करो this
 * are available at http://bersace03.मुक्त.fr/अगरt/
 *
 * The isight firmware loading was reverse engineered by Johannes Berg
 * <johannes@sipsolutions.de>, and this driver is based on code by Ronald
 * Bultje <rbultje@ronald.bitfreak.net>
 */

#समावेश <linux/usb.h>
#समावेश <linux/firmware.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणुUSB_DEVICE(0x05ac, 0x8300)पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(usb, id_table);

अटल पूर्णांक isight_firmware_load(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	पूर्णांक llen, len, req, ret = 0;
	स्थिर काष्ठा firmware *firmware;
	अचिन्हित अक्षर *buf = kदो_स्मृति(50, GFP_KERNEL);
	अचिन्हित अक्षर data[4];
	स्थिर u8 *ptr;

	अगर (!buf)
		वापस -ENOMEM;

	अगर (request_firmware(&firmware, "isight.fw", &dev->dev) != 0) अणु
		prपूर्णांकk(KERN_ERR "Unable to load isight firmware\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	ptr = firmware->data;

	buf[0] = 0x01;
	अगर (usb_control_msg
	    (dev, usb_sndctrlpipe(dev, 0), 0xa0, 0x40, 0xe600, 0, buf, 1,
	     300) != 1) अणु
		prपूर्णांकk(KERN_ERR
		       "Failed to initialise isight firmware loader\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	जबतक (ptr+4 <= firmware->data+firmware->size) अणु
		स_नकल(data, ptr, 4);
		len = (data[0] << 8 | data[1]);
		req = (data[2] << 8 | data[3]);
		ptr += 4;

		अगर (len == 0x8001)
			अवरोध;	/* success */
		अन्यथा अगर (len == 0)
			जारी;

		क्रम (; len > 0; req += 50) अणु
			llen = min(len, 50);
			len -= llen;
			अगर (ptr+llen > firmware->data+firmware->size) अणु
				prपूर्णांकk(KERN_ERR
				       "Malformed isight firmware");
				ret = -ENODEV;
				जाओ out;
			पूर्ण
			स_नकल(buf, ptr, llen);

			ptr += llen;

			अगर (usb_control_msg
			    (dev, usb_sndctrlpipe(dev, 0), 0xa0, 0x40, req, 0,
			     buf, llen, 300) != llen) अणु
				prपूर्णांकk(KERN_ERR
				       "Failed to load isight firmware\n");
				ret = -ENODEV;
				जाओ out;
			पूर्ण

		पूर्ण
	पूर्ण

	buf[0] = 0x00;
	अगर (usb_control_msg
	    (dev, usb_sndctrlpipe(dev, 0), 0xa0, 0x40, 0xe600, 0, buf, 1,
	     300) != 1) अणु
		prपूर्णांकk(KERN_ERR "isight firmware loading completion failed\n");
		ret = -ENODEV;
	पूर्ण

out:
	kमुक्त(buf);
	release_firmware(firmware);
	वापस ret;
पूर्ण

MODULE_FIRMWARE("isight.fw");

अटल व्योम isight_firmware_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
पूर्ण

अटल काष्ठा usb_driver isight_firmware_driver = अणु
	.name = "isight_firmware",
	.probe = isight_firmware_load,
	.disconnect = isight_firmware_disconnect,
	.id_table = id_table,
पूर्ण;

module_usb_driver(isight_firmware_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Matthew Garrett <mjg@redhat.com>");
