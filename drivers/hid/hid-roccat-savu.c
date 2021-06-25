<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Roccat Savu driver क्रम Linux
 *
 * Copyright (c) 2012 Stefan Achatz <erazor_de@users.sourceक्रमge.net>
 */

/*
 */

/* Roccat Savu is a gamer mouse with macro keys that can be configured in
 * 5 profiles.
 */

#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/hid-roccat.h>
#समावेश "hid-ids.h"
#समावेश "hid-roccat-common.h"
#समावेश "hid-roccat-savu.h"

अटल काष्ठा class *savu_class;

ROCCAT_COMMON2_BIN_ATTRIBUTE_W(control, 0x4, 0x03);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(profile, 0x5, 0x03);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(general, 0x6, 0x10);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(buttons, 0x7, 0x2f);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(macro, 0x8, 0x0823);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(info, 0x9, 0x08);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(sensor, 0xc, 0x04);

अटल काष्ठा bin_attribute *savu_bin_attrs[] = अणु
	&bin_attr_control,
	&bin_attr_profile,
	&bin_attr_general,
	&bin_attr_buttons,
	&bin_attr_macro,
	&bin_attr_info,
	&bin_attr_sensor,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group savu_group = अणु
	.bin_attrs = savu_bin_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *savu_groups[] = अणु
	&savu_group,
	शून्य,
पूर्ण;

अटल पूर्णांक savu_init_specials(काष्ठा hid_device *hdev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा roccat_common2_device *savu;
	पूर्णांक retval;

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			!= USB_INTERFACE_PROTOCOL_MOUSE) अणु
		hid_set_drvdata(hdev, शून्य);
		वापस 0;
	पूर्ण

	savu = kzalloc(माप(*savu), GFP_KERNEL);
	अगर (!savu) अणु
		hid_err(hdev, "can't alloc device descriptor\n");
		वापस -ENOMEM;
	पूर्ण
	hid_set_drvdata(hdev, savu);

	retval = roccat_common2_device_init_काष्ठा(usb_dev, savu);
	अगर (retval) अणु
		hid_err(hdev, "couldn't init Savu device\n");
		जाओ निकास_मुक्त;
	पूर्ण

	retval = roccat_connect(savu_class, hdev,
			माप(काष्ठा savu_roccat_report));
	अगर (retval < 0) अणु
		hid_err(hdev, "couldn't init char dev\n");
	पूर्ण अन्यथा अणु
		savu->chrdev_minor = retval;
		savu->roccat_claimed = 1;
	पूर्ण

	वापस 0;
निकास_मुक्त:
	kमुक्त(savu);
	वापस retval;
पूर्ण

अटल व्योम savu_हटाओ_specials(काष्ठा hid_device *hdev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा roccat_common2_device *savu;

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			!= USB_INTERFACE_PROTOCOL_MOUSE)
		वापस;

	savu = hid_get_drvdata(hdev);
	अगर (savu->roccat_claimed)
		roccat_disconnect(savu->chrdev_minor);
	kमुक्त(savu);
पूर्ण

अटल पूर्णांक savu_probe(काष्ठा hid_device *hdev,
		स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक retval;

	retval = hid_parse(hdev);
	अगर (retval) अणु
		hid_err(hdev, "parse failed\n");
		जाओ निकास;
	पूर्ण

	retval = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (retval) अणु
		hid_err(hdev, "hw start failed\n");
		जाओ निकास;
	पूर्ण

	retval = savu_init_specials(hdev);
	अगर (retval) अणु
		hid_err(hdev, "couldn't install mouse\n");
		जाओ निकास_stop;
	पूर्ण

	वापस 0;

निकास_stop:
	hid_hw_stop(hdev);
निकास:
	वापस retval;
पूर्ण

अटल व्योम savu_हटाओ(काष्ठा hid_device *hdev)
अणु
	savu_हटाओ_specials(hdev);
	hid_hw_stop(hdev);
पूर्ण

अटल व्योम savu_report_to_chrdev(काष्ठा roccat_common2_device स्थिर *savu,
		u8 स्थिर *data)
अणु
	काष्ठा savu_roccat_report roccat_report;
	काष्ठा savu_mouse_report_special स्थिर *special_report;

	अगर (data[0] != SAVU_MOUSE_REPORT_NUMBER_SPECIAL)
		वापस;

	special_report = (काष्ठा savu_mouse_report_special स्थिर *)data;

	roccat_report.type = special_report->type;
	roccat_report.data[0] = special_report->data[0];
	roccat_report.data[1] = special_report->data[1];
	roccat_report_event(savu->chrdev_minor,
			(uपूर्णांक8_t स्थिर *)&roccat_report);
पूर्ण

अटल पूर्णांक savu_raw_event(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report, u8 *data, पूर्णांक size)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा roccat_common2_device *savu = hid_get_drvdata(hdev);

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			!= USB_INTERFACE_PROTOCOL_MOUSE)
		वापस 0;

	अगर (savu == शून्य)
		वापस 0;

	अगर (savu->roccat_claimed)
		savu_report_to_chrdev(savu, data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id savu_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ROCCAT, USB_DEVICE_ID_ROCCAT_SAVU) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, savu_devices);

अटल काष्ठा hid_driver savu_driver = अणु
		.name = "savu",
		.id_table = savu_devices,
		.probe = savu_probe,
		.हटाओ = savu_हटाओ,
		.raw_event = savu_raw_event
पूर्ण;

अटल पूर्णांक __init savu_init(व्योम)
अणु
	पूर्णांक retval;

	savu_class = class_create(THIS_MODULE, "savu");
	अगर (IS_ERR(savu_class))
		वापस PTR_ERR(savu_class);
	savu_class->dev_groups = savu_groups;

	retval = hid_रेजिस्टर_driver(&savu_driver);
	अगर (retval)
		class_destroy(savu_class);
	वापस retval;
पूर्ण

अटल व्योम __निकास savu_निकास(व्योम)
अणु
	hid_unरेजिस्टर_driver(&savu_driver);
	class_destroy(savu_class);
पूर्ण

module_init(savu_init);
module_निकास(savu_निकास);

MODULE_AUTHOR("Stefan Achatz");
MODULE_DESCRIPTION("USB Roccat Savu driver");
MODULE_LICENSE("GPL v2");
