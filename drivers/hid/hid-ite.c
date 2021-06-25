<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HID driver क्रम some ITE "special" devices
 * Copyright (c) 2017 Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

#घोषणा QUIRK_TOUCHPAD_ON_OFF_REPORT		BIT(0)

अटल __u8 *ite_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc, अचिन्हित पूर्णांक *rsize)
अणु
	अचिन्हित दीर्घ quirks = (अचिन्हित दीर्घ)hid_get_drvdata(hdev);

	अगर (quirks & QUIRK_TOUCHPAD_ON_OFF_REPORT) अणु
		/* For Acer Aspire Switch 10 SW5-012 keyboard-करोck */
		अगर (*rsize == 188 && rdesc[162] == 0x81 && rdesc[163] == 0x02) अणु
			hid_info(hdev, "Fixing up Acer Sw5-012 ITE keyboard report descriptor\n");
			rdesc[163] = HID_MAIN_ITEM_RELATIVE;
		पूर्ण
		/* For Acer One S1002/S1003 keyboard-करोck */
		अगर (*rsize == 188 && rdesc[185] == 0x81 && rdesc[186] == 0x02) अणु
			hid_info(hdev, "Fixing up Acer S1002/S1003 ITE keyboard report descriptor\n");
			rdesc[186] = HID_MAIN_ITEM_RELATIVE;
		पूर्ण
		/* For Acer Aspire Switch 10E (SW3-016) keyboard-करोck */
		अगर (*rsize == 210 && rdesc[184] == 0x81 && rdesc[185] == 0x02) अणु
			hid_info(hdev, "Fixing up Acer Aspire Switch 10E (SW3-016) ITE keyboard report descriptor\n");
			rdesc[185] = HID_MAIN_ITEM_RELATIVE;
		पूर्ण
	पूर्ण

	वापस rdesc;
पूर्ण

अटल पूर्णांक ite_input_mapping(काष्ठा hid_device *hdev,
		काष्ठा hid_input *hi, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit,
		पूर्णांक *max)
अणु

	अचिन्हित दीर्घ quirks = (अचिन्हित दीर्घ)hid_get_drvdata(hdev);

	अगर ((quirks & QUIRK_TOUCHPAD_ON_OFF_REPORT) &&
	    (usage->hid & HID_USAGE_PAGE) == 0x00880000) अणु
		अगर (usage->hid == 0x00880078) अणु
			/* Touchpad on, userspace expects F22 क्रम this */
			hid_map_usage_clear(hi, usage, bit, max, EV_KEY, KEY_F22);
			वापस 1;
		पूर्ण
		अगर (usage->hid == 0x00880079) अणु
			/* Touchpad off, userspace expects F23 क्रम this */
			hid_map_usage_clear(hi, usage, bit, max, EV_KEY, KEY_F23);
			वापस 1;
		पूर्ण
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ite_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
		     काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा input_dev *input;

	अगर (!(hdev->claimed & HID_CLAIMED_INPUT) || !field->hidinput)
		वापस 0;

	input = field->hidinput->input;

	/*
	 * The ITE8595 always reports 0 as value क्रम the rfसमाप्त button. Luckily
	 * it is the only button in its report, and it sends a report on
	 * release only, so receiving a report means the button was pressed.
	 */
	अगर (usage->hid == HID_GD_RFKILL_BTN) अणु
		input_event(input, EV_KEY, KEY_RFKILL, 1);
		input_sync(input);
		input_event(input, EV_KEY, KEY_RFKILL, 0);
		input_sync(input);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ite_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;

	hid_set_drvdata(hdev, (व्योम *)id->driver_data);

	ret = hid_खोलो_report(hdev);
	अगर (ret)
		वापस ret;

	वापस hid_hw_start(hdev, HID_CONNECT_DEFAULT);
पूर्ण

अटल स्थिर काष्ठा hid_device_id ite_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ITE, USB_DEVICE_ID_ITE8595) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_258A, USB_DEVICE_ID_258A_6A88) पूर्ण,
	/* ITE8595 USB kbd ctlr, with Synaptics touchpad connected to it. */
	अणु HID_DEVICE(BUS_USB, HID_GROUP_GENERIC,
		     USB_VENDOR_ID_SYNAPTICS,
		     USB_DEVICE_ID_SYNAPTICS_ACER_SWITCH5_012),
	  .driver_data = QUIRK_TOUCHPAD_ON_OFF_REPORT पूर्ण,
	/* ITE8910 USB kbd ctlr, with Synaptics touchpad connected to it. */
	अणु HID_DEVICE(BUS_USB, HID_GROUP_GENERIC,
		     USB_VENDOR_ID_SYNAPTICS,
		     USB_DEVICE_ID_SYNAPTICS_ACER_ONE_S1002),
	  .driver_data = QUIRK_TOUCHPAD_ON_OFF_REPORT पूर्ण,
	/* ITE8910 USB kbd ctlr, with Synaptics touchpad connected to it. */
	अणु HID_DEVICE(BUS_USB, HID_GROUP_GENERIC,
		     USB_VENDOR_ID_SYNAPTICS,
		     USB_DEVICE_ID_SYNAPTICS_ACER_ONE_S1003),
	  .driver_data = QUIRK_TOUCHPAD_ON_OFF_REPORT पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, ite_devices);

अटल काष्ठा hid_driver ite_driver = अणु
	.name = "itetech",
	.id_table = ite_devices,
	.probe = ite_probe,
	.report_fixup = ite_report_fixup,
	.input_mapping = ite_input_mapping,
	.event = ite_event,
पूर्ण;
module_hid_driver(ite_driver);

MODULE_LICENSE("GPL");
