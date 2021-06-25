<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम Speedlink Vicious and Divine Cezanne (USB mouse).
 *  Fixes "jumpy" cursor and हटाओs nonexistent keyboard LEDS from
 *  the HID descriptor.
 *
 *  Copyright (c) 2011, 2013 Stefan Kriwanek <dev@stefankriwanek.de>
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

अटल स्थिर काष्ठा hid_device_id speedlink_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_X_TENSIONS, USB_DEVICE_ID_SPEEDLINK_VAD_CEZANNE)पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक speedlink_input_mapping(काष्ठा hid_device *hdev,
		काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	/*
	 * The Cezanne mouse has a second "keyboard" USB endpoपूर्णांक क्रम it is
	 * able to map keyboard events to the button presses.
	 * It sends a standard keyboard report descriptor, though, whose
	 * LEDs we ignore.
	 */
	चयन (usage->hid & HID_USAGE_PAGE) अणु
	हाल HID_UP_LED:
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक speedlink_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, __s32 value)
अणु
	/* No other conditions due to usage_table. */

	/* This fixes the "jumpy" cursor occuring due to invalid events sent
	 * by the device. Some devices only send them with value==+256, others
	 * करोn't. However, catching असल(value)>=256 is restrictive enough not
	 * to पूर्णांकerfere with devices that were bug-मुक्त (has been tested).
	 */
	अगर (असल(value) >= 256)
		वापस 1;
	/* Drop useless distance 0 events (on button clicks etc.) as well */
	अगर (value == 0)
		वापस 1;

	वापस 0;
पूर्ण

MODULE_DEVICE_TABLE(hid, speedlink_devices);

अटल स्थिर काष्ठा hid_usage_id speedlink_grabbed_usages[] = अणु
	अणु HID_GD_X, EV_REL, 0 पूर्ण,
	अणु HID_GD_Y, EV_REL, 1 पूर्ण,
	अणु HID_ANY_ID - 1, HID_ANY_ID - 1, HID_ANY_ID - 1पूर्ण
पूर्ण;

अटल काष्ठा hid_driver speedlink_driver = अणु
	.name = "speedlink",
	.id_table = speedlink_devices,
	.usage_table = speedlink_grabbed_usages,
	.input_mapping = speedlink_input_mapping,
	.event = speedlink_event,
पूर्ण;
module_hid_driver(speedlink_driver);

MODULE_LICENSE("GPL");
