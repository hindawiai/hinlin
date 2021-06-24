<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम some chicony "special" devices
 *
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2005 Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2005 Michael Haboustak <mike-@cinci.rr.com> क्रम Concept2, Inc
 *  Copyright (c) 2006-2007 Jiri Kosina
 *  Copyright (c) 2007 Paul Walmsley
 *  Copyright (c) 2008 Jiri Slaby
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>

#समावेश "hid-ids.h"

#घोषणा CH_WIRELESS_CTL_REPORT_ID	0x11

अटल पूर्णांक ch_report_wireless(काष्ठा hid_report *report, u8 *data, पूर्णांक size)
अणु
	काष्ठा hid_device *hdev = report->device;
	काष्ठा input_dev *input;

	अगर (report->id != CH_WIRELESS_CTL_REPORT_ID || report->maxfield != 1)
		वापस 0;

	input = report->field[0]->hidinput->input;
	अगर (!input) अणु
		hid_warn(hdev, "can't find wireless radio control's input");
		वापस 0;
	पूर्ण

	input_report_key(input, KEY_RFKILL, 1);
	input_sync(input);
	input_report_key(input, KEY_RFKILL, 0);
	input_sync(input);

	वापस 1;
पूर्ण

अटल पूर्णांक ch_raw_event(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report, u8 *data, पूर्णांक size)
अणु
	अगर (report->application == HID_GD_WIRELESS_RADIO_CTLS)
		वापस ch_report_wireless(report, data, size);

	वापस 0;
पूर्ण

#घोषणा ch_map_key_clear(c)	hid_map_usage_clear(hi, usage, bit, max, \
					EV_KEY, (c))
अटल पूर्णांक ch_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर ((usage->hid & HID_USAGE_PAGE) != HID_UP_MSVENDOR)
		वापस 0;

	set_bit(EV_REP, hi->input->evbit);
	चयन (usage->hid & HID_USAGE) अणु
	हाल 0xff01: ch_map_key_clear(BTN_1);	अवरोध;
	हाल 0xff02: ch_map_key_clear(BTN_2);	अवरोध;
	हाल 0xff03: ch_map_key_clear(BTN_3);	अवरोध;
	हाल 0xff04: ch_map_key_clear(BTN_4);	अवरोध;
	हाल 0xff05: ch_map_key_clear(BTN_5);	अवरोध;
	हाल 0xff06: ch_map_key_clear(BTN_6);	अवरोध;
	हाल 0xff07: ch_map_key_clear(BTN_7);	अवरोध;
	हाल 0xff08: ch_map_key_clear(BTN_8);	अवरोध;
	हाल 0xff09: ch_map_key_clear(BTN_9);	अवरोध;
	हाल 0xff0a: ch_map_key_clear(BTN_A);	अवरोध;
	हाल 0xff0b: ch_map_key_clear(BTN_B);	अवरोध;
	हाल 0x00f1: ch_map_key_clear(KEY_WLAN);	अवरोध;
	हाल 0x00f2: ch_map_key_clear(KEY_BRIGHTNESSDOWN);	अवरोध;
	हाल 0x00f3: ch_map_key_clear(KEY_BRIGHTNESSUP);	अवरोध;
	हाल 0x00f4: ch_map_key_clear(KEY_DISPLAY_OFF);	अवरोध;
	हाल 0x00f7: ch_map_key_clear(KEY_CAMERA);	अवरोध;
	हाल 0x00f8: ch_map_key_clear(KEY_PROG1);	अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल __u8 *ch_चयन12_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	
	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceNumber == 1) अणु
		/* Change usage maximum and logical maximum from 0x7fff to
		 * 0x2fff, so they करोn't exceed HID_MAX_USAGES */
		चयन (hdev->product) अणु
		हाल USB_DEVICE_ID_CHICONY_ACER_SWITCH12:
			अगर (*rsize >= 128 && rdesc[64] == 0xff && rdesc[65] == 0x7f
					&& rdesc[69] == 0xff && rdesc[70] == 0x7f) अणु
				hid_info(hdev, "Fixing up report descriptor\n");
				rdesc[65] = rdesc[70] = 0x2f;
			पूर्ण
			अवरोध;
		पूर्ण

	पूर्ण
	वापस rdesc;
पूर्ण

अटल पूर्णांक ch_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;

	hdev->quirks |= HID_QUIRK_INPUT_PER_APP;
	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "Chicony hid parse failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (ret) अणु
		hid_err(hdev, "Chicony hw start failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id ch_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CHICONY, USB_DEVICE_ID_CHICONY_TACTICAL_PAD) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CHICONY, USB_DEVICE_ID_CHICONY_WIRELESS2) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CHICONY, USB_DEVICE_ID_CHICONY_WIRELESS3) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CHICONY, USB_DEVICE_ID_CHICONY_ACER_SWITCH12) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, ch_devices);

अटल काष्ठा hid_driver ch_driver = अणु
	.name = "chicony",
	.id_table = ch_devices,
	.report_fixup = ch_चयन12_report_fixup,
	.input_mapping = ch_input_mapping,
	.probe = ch_probe,
	.raw_event = ch_raw_event,
पूर्ण;
module_hid_driver(ch_driver);

MODULE_LICENSE("GPL");
