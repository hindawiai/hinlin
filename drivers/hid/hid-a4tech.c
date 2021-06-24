<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम some a4tech "special" devices
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
#समावेश <linux/input.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "hid-ids.h"

#घोषणा A4_2WHEEL_MOUSE_HACK_7	0x01
#घोषणा A4_2WHEEL_MOUSE_HACK_B8	0x02

#घोषणा A4_WHEEL_ORIENTATION	(HID_UP_GENDESK | 0x000000b8)

काष्ठा a4tech_sc अणु
	अचिन्हित दीर्घ quirks;
	अचिन्हित पूर्णांक hw_wheel;
	__s32 delayed_value;
पूर्ण;

अटल पूर्णांक a4_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
			    काष्ठा hid_field *field, काष्ठा hid_usage *usage,
			    अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	काष्ठा a4tech_sc *a4 = hid_get_drvdata(hdev);

	अगर (a4->quirks & A4_2WHEEL_MOUSE_HACK_B8 &&
	    usage->hid == A4_WHEEL_ORIENTATION) अणु
		/*
		 * We करो not want to have this usage mapped to anything as it's
		 * nonstandard and करोesn't really behave like an HID report.
		 * It's only selecting the orientation (vertical/horizontal) of
		 * the previous mouse wheel report. The input_events will be
		 * generated once both reports are recorded in a4_event().
		 */
		वापस -1;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक a4_input_mapped(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	काष्ठा a4tech_sc *a4 = hid_get_drvdata(hdev);

	अगर (usage->type == EV_REL && usage->code == REL_WHEEL_HI_RES) अणु
		set_bit(REL_HWHEEL, *bit);
		set_bit(REL_HWHEEL_HI_RES, *bit);
	पूर्ण

	अगर ((a4->quirks & A4_2WHEEL_MOUSE_HACK_7) && usage->hid == 0x00090007)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक a4_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा a4tech_sc *a4 = hid_get_drvdata(hdev);
	काष्ठा input_dev *input;

	अगर (!(hdev->claimed & HID_CLAIMED_INPUT) || !field->hidinput)
		वापस 0;

	input = field->hidinput->input;

	अगर (a4->quirks & A4_2WHEEL_MOUSE_HACK_B8) अणु
		अगर (usage->type == EV_REL && usage->code == REL_WHEEL_HI_RES) अणु
			a4->delayed_value = value;
			वापस 1;
		पूर्ण

		अगर (usage->hid == A4_WHEEL_ORIENTATION) अणु
			input_event(input, EV_REL, value ? REL_HWHEEL :
					REL_WHEEL, a4->delayed_value);
			input_event(input, EV_REL, value ? REL_HWHEEL_HI_RES :
					REL_WHEEL_HI_RES, a4->delayed_value * 120);
			वापस 1;
		पूर्ण
	पूर्ण

	अगर ((a4->quirks & A4_2WHEEL_MOUSE_HACK_7) && usage->hid == 0x00090007) अणु
		a4->hw_wheel = !!value;
		वापस 1;
	पूर्ण

	अगर (usage->code == REL_WHEEL_HI_RES && a4->hw_wheel) अणु
		input_event(input, usage->type, REL_HWHEEL, value);
		input_event(input, usage->type, REL_HWHEEL_HI_RES, value * 120);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक a4_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा a4tech_sc *a4;
	पूर्णांक ret;

	a4 = devm_kzalloc(&hdev->dev, माप(*a4), GFP_KERNEL);
	अगर (a4 == शून्य) अणु
		hid_err(hdev, "can't alloc device descriptor\n");
		वापस -ENOMEM;
	पूर्ण

	a4->quirks = id->driver_data;

	hid_set_drvdata(hdev, a4);

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		वापस ret;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id a4_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_A4TECH, USB_DEVICE_ID_A4TECH_WCP32PU),
		.driver_data = A4_2WHEEL_MOUSE_HACK_7 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_A4TECH, USB_DEVICE_ID_A4TECH_X5_005D),
		.driver_data = A4_2WHEEL_MOUSE_HACK_B8 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_A4TECH, USB_DEVICE_ID_A4TECH_RP_649),
		.driver_data = A4_2WHEEL_MOUSE_HACK_B8 पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_A4TECH, USB_DEVICE_ID_A4TECH_NB_95),
		.driver_data = A4_2WHEEL_MOUSE_HACK_B8 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, a4_devices);

अटल काष्ठा hid_driver a4_driver = अणु
	.name = "a4tech",
	.id_table = a4_devices,
	.input_mapping = a4_input_mapping,
	.input_mapped = a4_input_mapped,
	.event = a4_event,
	.probe = a4_probe,
पूर्ण;
module_hid_driver(a4_driver);

MODULE_LICENSE("GPL");
