<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008 Sensoray Company Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/firmware.h>
#समावेश <cypress_firmware.h>

काष्ठा fw_config अणु
	u16 venकरोr;
	u16 product;
	स्थिर अक्षर * स्थिर fw_name1;
	स्थिर अक्षर * स्थिर fw_name2;
पूर्ण;

अटल काष्ठा fw_config fw_configs[] = अणु
	अणु 0x1943, 0xa250, "go7007/s2250-1.fw", "go7007/s2250-2.fw" पूर्ण,
	अणु 0x093b, 0xa002, "go7007/px-m402u.fw", शून्य पूर्ण,
	अणु 0x093b, 0xa004, "go7007/px-tv402u.fw", शून्य पूर्ण,
	अणु 0x0eb1, 0x6666, "go7007/lr192.fw", शून्य पूर्ण,
	अणु 0x0eb1, 0x6668, "go7007/wis-startrek.fw", शून्य पूर्ण,
	अणु 0, 0, शून्य, शून्य पूर्ण
पूर्ण;
MODULE_FIRMWARE("go7007/s2250-1.fw");
MODULE_FIRMWARE("go7007/s2250-2.fw");
MODULE_FIRMWARE("go7007/px-m402u.fw");
MODULE_FIRMWARE("go7007/px-tv402u.fw");
MODULE_FIRMWARE("go7007/lr192.fw");
MODULE_FIRMWARE("go7007/wis-startrek.fw");

अटल पूर्णांक go7007_loader_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
				स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *usbdev;
	स्थिर काष्ठा firmware *fw;
	u16 venकरोr, product;
	स्थिर अक्षर *fw1, *fw2;
	पूर्णांक ret;
	पूर्णांक i;

	usbdev = usb_get_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));
	अगर (!usbdev)
		जाओ failed2;

	अगर (usbdev->descriptor.bNumConfigurations != 1) अणु
		dev_err(&पूर्णांकerface->dev, "can't handle multiple config\n");
		जाओ failed2;
	पूर्ण

	venकरोr = le16_to_cpu(usbdev->descriptor.idVenकरोr);
	product = le16_to_cpu(usbdev->descriptor.idProduct);

	क्रम (i = 0; fw_configs[i].fw_name1; i++)
		अगर (fw_configs[i].venकरोr == venकरोr &&
		    fw_configs[i].product == product)
			अवरोध;

	/* Should never happen */
	अगर (fw_configs[i].fw_name1 == शून्य)
		जाओ failed2;

	fw1 = fw_configs[i].fw_name1;
	fw2 = fw_configs[i].fw_name2;

	dev_info(&पूर्णांकerface->dev, "loading firmware %s\n", fw1);

	अगर (request_firmware(&fw, fw1, &usbdev->dev)) अणु
		dev_err(&पूर्णांकerface->dev,
			"unable to load firmware from file \"%s\"\n", fw1);
		जाओ failed2;
	पूर्ण
	ret = cypress_load_firmware(usbdev, fw, CYPRESS_FX2);
	release_firmware(fw);
	अगर (0 != ret) अणु
		dev_err(&पूर्णांकerface->dev, "loader download failed\n");
		जाओ failed2;
	पूर्ण

	अगर (fw2 == शून्य)
		वापस 0;

	अगर (request_firmware(&fw, fw2, &usbdev->dev)) अणु
		dev_err(&पूर्णांकerface->dev,
			"unable to load firmware from file \"%s\"\n", fw2);
		जाओ failed2;
	पूर्ण
	ret = cypress_load_firmware(usbdev, fw, CYPRESS_FX2);
	release_firmware(fw);
	अगर (0 != ret) अणु
		dev_err(&पूर्णांकerface->dev, "firmware download failed\n");
		जाओ failed2;
	पूर्ण
	वापस 0;

failed2:
	usb_put_dev(usbdev);
	dev_err(&पूर्णांकerface->dev, "probe failed\n");
	वापस -ENODEV;
पूर्ण

अटल व्योम go7007_loader_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	dev_info(&पूर्णांकerface->dev, "disconnect\n");
	usb_put_dev(पूर्णांकerface_to_usbdev(पूर्णांकerface));
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
पूर्ण

अटल स्थिर काष्ठा usb_device_id go7007_loader_ids[] = अणु
	अणु USB_DEVICE(0x1943, 0xa250) पूर्ण,
	अणु USB_DEVICE(0x093b, 0xa002) पूर्ण,
	अणु USB_DEVICE(0x093b, 0xa004) पूर्ण,
	अणु USB_DEVICE(0x0eb1, 0x6666) पूर्ण,
	अणु USB_DEVICE(0x0eb1, 0x6668) पूर्ण,
	अणुपूर्ण                          /* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, go7007_loader_ids);

अटल काष्ठा usb_driver go7007_loader_driver = अणु
	.name		= "go7007-loader",
	.probe		= go7007_loader_probe,
	.disconnect	= go7007_loader_disconnect,
	.id_table	= go7007_loader_ids,
पूर्ण;

module_usb_driver(go7007_loader_driver);

MODULE_AUTHOR("");
MODULE_DESCRIPTION("firmware loader for go7007-usb");
MODULE_LICENSE("GPL v2");
