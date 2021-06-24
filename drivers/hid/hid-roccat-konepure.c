<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Roccat KonePure driver क्रम Linux
 *
 * Copyright (c) 2012 Stefan Achatz <erazor_de@users.sourceक्रमge.net>
 */

/*
 */

/*
 * Roccat KonePure is a smaller version of KoneXTD with less buttons and lights.
 */

#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/hid-roccat.h>
#समावेश "hid-ids.h"
#समावेश "hid-roccat-common.h"

क्रमागत अणु
	KONEPURE_MOUSE_REPORT_NUMBER_BUTTON = 3,
पूर्ण;

काष्ठा konepure_mouse_report_button अणु
	uपूर्णांक8_t report_number; /* always KONEPURE_MOUSE_REPORT_NUMBER_BUTTON */
	uपूर्णांक8_t zero;
	uपूर्णांक8_t type;
	uपूर्णांक8_t data1;
	uपूर्णांक8_t data2;
	uपूर्णांक8_t zero2;
	uपूर्णांक8_t unknown[2];
पूर्ण __packed;

अटल काष्ठा class *konepure_class;

ROCCAT_COMMON2_BIN_ATTRIBUTE_W(control, 0x04, 0x03);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(actual_profile, 0x05, 0x03);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(profile_settings, 0x06, 0x1f);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(profile_buttons, 0x07, 0x3b);
ROCCAT_COMMON2_BIN_ATTRIBUTE_W(macro, 0x08, 0x0822);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(info, 0x09, 0x06);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(tcu, 0x0c, 0x04);
ROCCAT_COMMON2_BIN_ATTRIBUTE_R(tcu_image, 0x0c, 0x0404);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(sensor, 0x0f, 0x06);
ROCCAT_COMMON2_BIN_ATTRIBUTE_W(talk, 0x10, 0x10);

अटल काष्ठा bin_attribute *konepure_bin_attrs[] = अणु
	&bin_attr_actual_profile,
	&bin_attr_control,
	&bin_attr_info,
	&bin_attr_talk,
	&bin_attr_macro,
	&bin_attr_sensor,
	&bin_attr_tcu,
	&bin_attr_tcu_image,
	&bin_attr_profile_settings,
	&bin_attr_profile_buttons,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group konepure_group = अणु
	.bin_attrs = konepure_bin_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *konepure_groups[] = अणु
	&konepure_group,
	शून्य,
पूर्ण;

अटल पूर्णांक konepure_init_specials(काष्ठा hid_device *hdev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा roccat_common2_device *konepure;
	पूर्णांक retval;

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			!= USB_INTERFACE_PROTOCOL_MOUSE) अणु
		hid_set_drvdata(hdev, शून्य);
		वापस 0;
	पूर्ण

	konepure = kzalloc(माप(*konepure), GFP_KERNEL);
	अगर (!konepure) अणु
		hid_err(hdev, "can't alloc device descriptor\n");
		वापस -ENOMEM;
	पूर्ण
	hid_set_drvdata(hdev, konepure);

	retval = roccat_common2_device_init_काष्ठा(usb_dev, konepure);
	अगर (retval) अणु
		hid_err(hdev, "couldn't init KonePure device\n");
		जाओ निकास_मुक्त;
	पूर्ण

	retval = roccat_connect(konepure_class, hdev,
			माप(काष्ठा konepure_mouse_report_button));
	अगर (retval < 0) अणु
		hid_err(hdev, "couldn't init char dev\n");
	पूर्ण अन्यथा अणु
		konepure->chrdev_minor = retval;
		konepure->roccat_claimed = 1;
	पूर्ण

	वापस 0;
निकास_मुक्त:
	kमुक्त(konepure);
	वापस retval;
पूर्ण

अटल व्योम konepure_हटाओ_specials(काष्ठा hid_device *hdev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा roccat_common2_device *konepure;

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			!= USB_INTERFACE_PROTOCOL_MOUSE)
		वापस;

	konepure = hid_get_drvdata(hdev);
	अगर (konepure->roccat_claimed)
		roccat_disconnect(konepure->chrdev_minor);
	kमुक्त(konepure);
पूर्ण

अटल पूर्णांक konepure_probe(काष्ठा hid_device *hdev,
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

	retval = konepure_init_specials(hdev);
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

अटल व्योम konepure_हटाओ(काष्ठा hid_device *hdev)
अणु
	konepure_हटाओ_specials(hdev);
	hid_hw_stop(hdev);
पूर्ण

अटल पूर्णांक konepure_raw_event(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report, u8 *data, पूर्णांक size)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा roccat_common2_device *konepure = hid_get_drvdata(hdev);

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			!= USB_INTERFACE_PROTOCOL_MOUSE)
		वापस 0;

	अगर (data[0] != KONEPURE_MOUSE_REPORT_NUMBER_BUTTON)
		वापस 0;

	अगर (konepure != शून्य && konepure->roccat_claimed)
		roccat_report_event(konepure->chrdev_minor, data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id konepure_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ROCCAT, USB_DEVICE_ID_ROCCAT_KONEPURE) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ROCCAT, USB_DEVICE_ID_ROCCAT_KONEPURE_OPTICAL) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, konepure_devices);

अटल काष्ठा hid_driver konepure_driver = अणु
		.name = "konepure",
		.id_table = konepure_devices,
		.probe = konepure_probe,
		.हटाओ = konepure_हटाओ,
		.raw_event = konepure_raw_event
पूर्ण;

अटल पूर्णांक __init konepure_init(व्योम)
अणु
	पूर्णांक retval;

	konepure_class = class_create(THIS_MODULE, "konepure");
	अगर (IS_ERR(konepure_class))
		वापस PTR_ERR(konepure_class);
	konepure_class->dev_groups = konepure_groups;

	retval = hid_रेजिस्टर_driver(&konepure_driver);
	अगर (retval)
		class_destroy(konepure_class);
	वापस retval;
पूर्ण

अटल व्योम __निकास konepure_निकास(व्योम)
अणु
	hid_unरेजिस्टर_driver(&konepure_driver);
	class_destroy(konepure_class);
पूर्ण

module_init(konepure_init);
module_निकास(konepure_निकास);

MODULE_AUTHOR("Stefan Achatz");
MODULE_DESCRIPTION("USB Roccat KonePure/Optical driver");
MODULE_LICENSE("GPL v2");
