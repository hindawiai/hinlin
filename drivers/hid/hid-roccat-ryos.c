<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Roccat Ryos driver क्रम Linux
 *
 * Copyright (c) 2013 Stefan Achatz <erazor_de@users.sourceक्रमge.net>
 */

/*
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
	RYOS_REPORT_NUMBER_SPECIAL = 3,
	RYOS_USB_INTERFACE_PROTOCOL = 0,
पूर्ण;

काष्ठा ryos_report_special अणु
	uपूर्णांक8_t number; /* RYOS_REPORT_NUMBER_SPECIAL */
	uपूर्णांक8_t data[4];
पूर्ण __packed;

अटल काष्ठा class *ryos_class;

ROCCAT_COMMON2_BIN_ATTRIBUTE_W(control, 0x04, 0x03);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(profile, 0x05, 0x03);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(keys_primary, 0x06, 0x7d);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(keys_function, 0x07, 0x5f);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(keys_macro, 0x08, 0x23);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(keys_thumbster, 0x09, 0x17);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(keys_extra, 0x0a, 0x08);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(keys_easyzone, 0x0b, 0x126);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(key_mask, 0x0c, 0x06);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(light, 0x0d, 0x10);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(macro, 0x0e, 0x7d2);
ROCCAT_COMMON2_BIN_ATTRIBUTE_R(info, 0x0f, 0x08);
ROCCAT_COMMON2_BIN_ATTRIBUTE_W(reset, 0x11, 0x03);
ROCCAT_COMMON2_BIN_ATTRIBUTE_W(light_control, 0x13, 0x08);
ROCCAT_COMMON2_BIN_ATTRIBUTE_W(talk, 0x16, 0x10);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(stored_lights, 0x17, 0x0566);
ROCCAT_COMMON2_BIN_ATTRIBUTE_W(custom_lights, 0x18, 0x14);
ROCCAT_COMMON2_BIN_ATTRIBUTE_RW(light_macro, 0x19, 0x07d2);

अटल काष्ठा bin_attribute *ryos_bin_attrs[] = अणु
	&bin_attr_control,
	&bin_attr_profile,
	&bin_attr_keys_primary,
	&bin_attr_keys_function,
	&bin_attr_keys_macro,
	&bin_attr_keys_thumbster,
	&bin_attr_keys_extra,
	&bin_attr_keys_easyzone,
	&bin_attr_key_mask,
	&bin_attr_light,
	&bin_attr_macro,
	&bin_attr_info,
	&bin_attr_reset,
	&bin_attr_light_control,
	&bin_attr_talk,
	&bin_attr_stored_lights,
	&bin_attr_custom_lights,
	&bin_attr_light_macro,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ryos_group = अणु
	.bin_attrs = ryos_bin_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *ryos_groups[] = अणु
	&ryos_group,
	शून्य,
पूर्ण;

अटल पूर्णांक ryos_init_specials(काष्ठा hid_device *hdev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा roccat_common2_device *ryos;
	पूर्णांक retval;

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			!= RYOS_USB_INTERFACE_PROTOCOL) अणु
		hid_set_drvdata(hdev, शून्य);
		वापस 0;
	पूर्ण

	ryos = kzalloc(माप(*ryos), GFP_KERNEL);
	अगर (!ryos) अणु
		hid_err(hdev, "can't alloc device descriptor\n");
		वापस -ENOMEM;
	पूर्ण
	hid_set_drvdata(hdev, ryos);

	retval = roccat_common2_device_init_काष्ठा(usb_dev, ryos);
	अगर (retval) अणु
		hid_err(hdev, "couldn't init Ryos device\n");
		जाओ निकास_मुक्त;
	पूर्ण

	retval = roccat_connect(ryos_class, hdev,
			माप(काष्ठा ryos_report_special));
	अगर (retval < 0) अणु
		hid_err(hdev, "couldn't init char dev\n");
	पूर्ण अन्यथा अणु
		ryos->chrdev_minor = retval;
		ryos->roccat_claimed = 1;
	पूर्ण

	वापस 0;
निकास_मुक्त:
	kमुक्त(ryos);
	वापस retval;
पूर्ण

अटल व्योम ryos_हटाओ_specials(काष्ठा hid_device *hdev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा roccat_common2_device *ryos;

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			!= RYOS_USB_INTERFACE_PROTOCOL)
		वापस;

	ryos = hid_get_drvdata(hdev);
	अगर (ryos->roccat_claimed)
		roccat_disconnect(ryos->chrdev_minor);
	kमुक्त(ryos);
पूर्ण

अटल पूर्णांक ryos_probe(काष्ठा hid_device *hdev,
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

	retval = ryos_init_specials(hdev);
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

अटल व्योम ryos_हटाओ(काष्ठा hid_device *hdev)
अणु
	ryos_हटाओ_specials(hdev);
	hid_hw_stop(hdev);
पूर्ण

अटल पूर्णांक ryos_raw_event(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report, u8 *data, पूर्णांक size)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा roccat_common2_device *ryos = hid_get_drvdata(hdev);

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			!= RYOS_USB_INTERFACE_PROTOCOL)
		वापस 0;

	अगर (data[0] != RYOS_REPORT_NUMBER_SPECIAL)
		वापस 0;

	अगर (ryos != शून्य && ryos->roccat_claimed)
		roccat_report_event(ryos->chrdev_minor, data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id ryos_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ROCCAT, USB_DEVICE_ID_ROCCAT_RYOS_MK) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ROCCAT, USB_DEVICE_ID_ROCCAT_RYOS_MK_GLOW) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ROCCAT, USB_DEVICE_ID_ROCCAT_RYOS_MK_PRO) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, ryos_devices);

अटल काष्ठा hid_driver ryos_driver = अणु
		.name = "ryos",
		.id_table = ryos_devices,
		.probe = ryos_probe,
		.हटाओ = ryos_हटाओ,
		.raw_event = ryos_raw_event
पूर्ण;

अटल पूर्णांक __init ryos_init(व्योम)
अणु
	पूर्णांक retval;

	ryos_class = class_create(THIS_MODULE, "ryos");
	अगर (IS_ERR(ryos_class))
		वापस PTR_ERR(ryos_class);
	ryos_class->dev_groups = ryos_groups;

	retval = hid_रेजिस्टर_driver(&ryos_driver);
	अगर (retval)
		class_destroy(ryos_class);
	वापस retval;
पूर्ण

अटल व्योम __निकास ryos_निकास(व्योम)
अणु
	hid_unरेजिस्टर_driver(&ryos_driver);
	class_destroy(ryos_class);
पूर्ण

module_init(ryos_init);
module_निकास(ryos_निकास);

MODULE_AUTHOR("Stefan Achatz");
MODULE_DESCRIPTION("USB Roccat Ryos MK/Glow/Pro driver");
MODULE_LICENSE("GPL v2");
