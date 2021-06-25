<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम some belkin "special" devices
 *
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2005 Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2005 Michael Haboustak <mike-@cinci.rr.com> क्रम Concept2, Inc
 *  Copyright (c) 2006-2007 Jiri Kosina
 *  Copyright (c) 2008 Jiri Slaby
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

#घोषणा BELKIN_HIDDEV	0x01
#घोषणा BELKIN_WKBD	0x02

#घोषणा belkin_map_key_clear(c)	hid_map_usage_clear(hi, usage, bit, max, \
					EV_KEY, (c))
अटल पूर्णांक belkin_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अचिन्हित दीर्घ quirks = (अचिन्हित दीर्घ)hid_get_drvdata(hdev);

	अगर ((usage->hid & HID_USAGE_PAGE) != HID_UP_CONSUMER ||
			!(quirks & BELKIN_WKBD))
		वापस 0;

	चयन (usage->hid & HID_USAGE) अणु
	हाल 0x03a: belkin_map_key_clear(KEY_SOUND);		अवरोध;
	हाल 0x03b: belkin_map_key_clear(KEY_CAMERA);		अवरोध;
	हाल 0x03c: belkin_map_key_clear(KEY_DOCUMENTS);	अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक belkin_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	अचिन्हित दीर्घ quirks = id->driver_data;
	पूर्णांक ret;

	hid_set_drvdata(hdev, (व्योम *)quirks);

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		जाओ err_मुक्त;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT |
		((quirks & BELKIN_HIDDEV) ? HID_CONNECT_HIDDEV_FORCE : 0));
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		जाओ err_मुक्त;
	पूर्ण

	वापस 0;
err_मुक्त:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hid_device_id belkin_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_BELKIN, USB_DEVICE_ID_FLIP_KVM),
		.driver_data = BELKIN_HIDDEV पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_LABTEC, USB_DEVICE_ID_LABTEC_WIRELESS_KEYBOARD),
		.driver_data = BELKIN_WKBD पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, belkin_devices);

अटल काष्ठा hid_driver belkin_driver = अणु
	.name = "belkin",
	.id_table = belkin_devices,
	.input_mapping = belkin_input_mapping,
	.probe = belkin_probe,
पूर्ण;
module_hid_driver(belkin_driver);

MODULE_LICENSE("GPL");
