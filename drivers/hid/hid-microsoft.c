<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम some microsoft "special" devices
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

#समावेश "hid-ids.h"

#घोषणा MS_HIDINPUT		BIT(0)
#घोषणा MS_ERGONOMY		BIT(1)
#घोषणा MS_PRESENTER		BIT(2)
#घोषणा MS_RDESC		BIT(3)
#घोषणा MS_NOGET		BIT(4)
#घोषणा MS_DUPLICATE_USAGES	BIT(5)
#घोषणा MS_SURFACE_DIAL		BIT(6)
#घोषणा MS_QUIRK_FF		BIT(7)

काष्ठा ms_data अणु
	अचिन्हित दीर्घ quirks;
	काष्ठा hid_device *hdev;
	काष्ठा work_काष्ठा ff_worker;
	__u8 strong;
	__u8 weak;
	व्योम *output_report_dmabuf;
पूर्ण;

#घोषणा XB1S_FF_REPORT		3
#घोषणा ENABLE_WEAK		BIT(0)
#घोषणा ENABLE_STRONG		BIT(1)

क्रमागत अणु
	MAGNITUDE_STRONG = 2,
	MAGNITUDE_WEAK,
	MAGNITUDE_NUM
पूर्ण;

काष्ठा xb1s_ff_report अणु
	__u8	report_id;
	__u8	enable;
	__u8	magnitude[MAGNITUDE_NUM];
	__u8	duration_10ms;
	__u8	start_delay_10ms;
	__u8	loop_count;
पूर्ण __packed;

अटल __u8 *ms_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	काष्ठा ms_data *ms = hid_get_drvdata(hdev);
	अचिन्हित दीर्घ quirks = ms->quirks;

	/*
	 * Microsoft Wireless Desktop Receiver (Model 1028) has
	 * 'Usage Min/Max' where it ought to have 'Physical Min/Max'
	 */
	अगर ((quirks & MS_RDESC) && *rsize == 571 && rdesc[557] == 0x19 &&
			rdesc[559] == 0x29) अणु
		hid_info(hdev, "fixing up Microsoft Wireless Receiver Model 1028 report descriptor\n");
		rdesc[557] = 0x35;
		rdesc[559] = 0x45;
	पूर्ण
	वापस rdesc;
पूर्ण

#घोषणा ms_map_key_clear(c)	hid_map_usage_clear(hi, usage, bit, max, \
					EV_KEY, (c))
अटल पूर्णांक ms_ergonomy_kb_quirk(काष्ठा hid_input *hi, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	काष्ठा input_dev *input = hi->input;

	अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_CONSUMER) अणु
		चयन (usage->hid & HID_USAGE) अणु
		/*
		 * Microsoft uses these 2 reserved usage ids क्रम 2 keys on
		 * the MS office kb labelled "Office Home" and "Task Pane".
		 */
		हाल 0x29d:
			ms_map_key_clear(KEY_PROG1);
			वापस 1;
		हाल 0x29e:
			ms_map_key_clear(KEY_PROG2);
			वापस 1;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर ((usage->hid & HID_USAGE_PAGE) != HID_UP_MSVENDOR)
		वापस 0;

	चयन (usage->hid & HID_USAGE) अणु
	हाल 0xfd06: ms_map_key_clear(KEY_CHAT);	अवरोध;
	हाल 0xfd07: ms_map_key_clear(KEY_PHONE);	अवरोध;
	हाल 0xff00:
		/* Special keypad keys */
		ms_map_key_clear(KEY_KPEQUAL);
		set_bit(KEY_KPLEFTPAREN, input->keybit);
		set_bit(KEY_KPRIGHTPAREN, input->keybit);
		अवरोध;
	हाल 0xff01:
		/* Scroll wheel */
		hid_map_usage_clear(hi, usage, bit, max, EV_REL, REL_WHEEL);
		अवरोध;
	हाल 0xff02:
		/*
		 * This byte contains a copy of the modअगरier keys byte of a
		 * standard hid keyboard report, as send by पूर्णांकerface 0
		 * (this usage is found on पूर्णांकerface 1).
		 *
		 * This byte only माला_लो send when another key in the same report
		 * changes state, and as such is useless, ignore it.
		 */
		वापस -1;
	हाल 0xff05:
		set_bit(EV_REP, input->evbit);
		ms_map_key_clear(KEY_F13);
		set_bit(KEY_F14, input->keybit);
		set_bit(KEY_F15, input->keybit);
		set_bit(KEY_F16, input->keybit);
		set_bit(KEY_F17, input->keybit);
		set_bit(KEY_F18, input->keybit);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक ms_presenter_8k_quirk(काष्ठा hid_input *hi, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर ((usage->hid & HID_USAGE_PAGE) != HID_UP_MSVENDOR)
		वापस 0;

	set_bit(EV_REP, hi->input->evbit);
	चयन (usage->hid & HID_USAGE) अणु
	हाल 0xfd08: ms_map_key_clear(KEY_FORWARD);	अवरोध;
	हाल 0xfd09: ms_map_key_clear(KEY_BACK);	अवरोध;
	हाल 0xfd0b: ms_map_key_clear(KEY_PLAYPAUSE);	अवरोध;
	हाल 0xfd0e: ms_map_key_clear(KEY_CLOSE);	अवरोध;
	हाल 0xfd0f: ms_map_key_clear(KEY_PLAY);	अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक ms_surface_dial_quirk(काष्ठा hid_input *hi, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	चयन (usage->hid & HID_USAGE_PAGE) अणु
	हाल 0xff070000:
	हाल HID_UP_DIGITIZER:
		/* ignore those axis */
		वापस -1;
	हाल HID_UP_GENDESK:
		चयन (usage->hid) अणु
		हाल HID_GD_X:
		हाल HID_GD_Y:
		हाल HID_GD_RFKILL_BTN:
			/* ignore those axis */
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ms_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	काष्ठा ms_data *ms = hid_get_drvdata(hdev);
	अचिन्हित दीर्घ quirks = ms->quirks;

	अगर (quirks & MS_ERGONOMY) अणु
		पूर्णांक ret = ms_ergonomy_kb_quirk(hi, usage, bit, max);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर ((quirks & MS_PRESENTER) &&
			ms_presenter_8k_quirk(hi, usage, bit, max))
		वापस 1;

	अगर (quirks & MS_SURFACE_DIAL) अणु
		पूर्णांक ret = ms_surface_dial_quirk(hi, field, usage, bit, max);

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ms_input_mapped(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	काष्ठा ms_data *ms = hid_get_drvdata(hdev);
	अचिन्हित दीर्घ quirks = ms->quirks;

	अगर (quirks & MS_DUPLICATE_USAGES)
		clear_bit(usage->code, *bit);

	वापस 0;
पूर्ण

अटल पूर्णांक ms_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा ms_data *ms = hid_get_drvdata(hdev);
	अचिन्हित दीर्घ quirks = ms->quirks;
	काष्ठा input_dev *input;

	अगर (!(hdev->claimed & HID_CLAIMED_INPUT) || !field->hidinput ||
			!usage->type)
		वापस 0;

	input = field->hidinput->input;

	/* Handling MS keyboards special buttons */
	अगर (quirks & MS_ERGONOMY && usage->hid == (HID_UP_MSVENDOR | 0xff00)) अणु
		/* Special keypad keys */
		input_report_key(input, KEY_KPEQUAL, value & 0x01);
		input_report_key(input, KEY_KPLEFTPAREN, value & 0x02);
		input_report_key(input, KEY_KPRIGHTPAREN, value & 0x04);
		वापस 1;
	पूर्ण

	अगर (quirks & MS_ERGONOMY && usage->hid == (HID_UP_MSVENDOR | 0xff01)) अणु
		/* Scroll wheel */
		पूर्णांक step = ((value & 0x60) >> 5) + 1;

		चयन (value & 0x1f) अणु
		हाल 0x01:
			input_report_rel(input, REL_WHEEL, step);
			अवरोध;
		हाल 0x1f:
			input_report_rel(input, REL_WHEEL, -step);
			अवरोध;
		पूर्ण
		वापस 1;
	पूर्ण

	अगर (quirks & MS_ERGONOMY && usage->hid == (HID_UP_MSVENDOR | 0xff05)) अणु
		अटल अचिन्हित पूर्णांक last_key = 0;
		अचिन्हित पूर्णांक key = 0;
		चयन (value) अणु
		हाल 0x01: key = KEY_F14; अवरोध;
		हाल 0x02: key = KEY_F15; अवरोध;
		हाल 0x04: key = KEY_F16; अवरोध;
		हाल 0x08: key = KEY_F17; अवरोध;
		हाल 0x10: key = KEY_F18; अवरोध;
		पूर्ण
		अगर (key) अणु
			input_event(input, usage->type, key, 1);
			last_key = key;
		पूर्ण अन्यथा
			input_event(input, usage->type, last_key, 0);

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ms_ff_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ms_data *ms = container_of(work, काष्ठा ms_data, ff_worker);
	काष्ठा hid_device *hdev = ms->hdev;
	काष्ठा xb1s_ff_report *r = ms->output_report_dmabuf;
	पूर्णांक ret;

	स_रखो(r, 0, माप(*r));

	r->report_id = XB1S_FF_REPORT;
	r->enable = ENABLE_WEAK | ENABLE_STRONG;
	/*
	 * Specअगरying maximum duration and maximum loop count should
	 * cover maximum duration of a single effect, which is 65536
	 * ms
	 */
	r->duration_10ms = U8_MAX;
	r->loop_count = U8_MAX;
	r->magnitude[MAGNITUDE_STRONG] = ms->strong; /* left actuator */
	r->magnitude[MAGNITUDE_WEAK] = ms->weak;     /* right actuator */

	ret = hid_hw_output_report(hdev, (__u8 *)r, माप(*r));
	अगर (ret < 0)
		hid_warn(hdev, "failed to send FF report\n");
पूर्ण

अटल पूर्णांक ms_play_effect(काष्ठा input_dev *dev, व्योम *data,
			  काष्ठा ff_effect *effect)
अणु
	काष्ठा hid_device *hid = input_get_drvdata(dev);
	काष्ठा ms_data *ms = hid_get_drvdata(hid);

	अगर (effect->type != FF_RUMBLE)
		वापस 0;

	/*
	 * Magnitude is 0..100 so scale the 16-bit input here
	 */
	ms->strong = ((u32) effect->u.rumble.strong_magnitude * 100) / U16_MAX;
	ms->weak = ((u32) effect->u.rumble.weak_magnitude * 100) / U16_MAX;

	schedule_work(&ms->ff_worker);
	वापस 0;
पूर्ण

अटल पूर्णांक ms_init_ff(काष्ठा hid_device *hdev)
अणु
	काष्ठा hid_input *hidinput;
	काष्ठा input_dev *input_dev;
	काष्ठा ms_data *ms = hid_get_drvdata(hdev);

	अगर (list_empty(&hdev->inमाला_दो)) अणु
		hid_err(hdev, "no inputs found\n");
		वापस -ENODEV;
	पूर्ण
	hidinput = list_entry(hdev->inमाला_दो.next, काष्ठा hid_input, list);
	input_dev = hidinput->input;

	अगर (!(ms->quirks & MS_QUIRK_FF))
		वापस 0;

	ms->hdev = hdev;
	INIT_WORK(&ms->ff_worker, ms_ff_worker);

	ms->output_report_dmabuf = devm_kzalloc(&hdev->dev,
						माप(काष्ठा xb1s_ff_report),
						GFP_KERNEL);
	अगर (ms->output_report_dmabuf == शून्य)
		वापस -ENOMEM;

	input_set_capability(input_dev, EV_FF, FF_RUMBLE);
	वापस input_ff_create_memless(input_dev, शून्य, ms_play_effect);
पूर्ण

अटल व्योम ms_हटाओ_ff(काष्ठा hid_device *hdev)
अणु
	काष्ठा ms_data *ms = hid_get_drvdata(hdev);

	अगर (!(ms->quirks & MS_QUIRK_FF))
		वापस;

	cancel_work_sync(&ms->ff_worker);
पूर्ण

अटल पूर्णांक ms_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	अचिन्हित दीर्घ quirks = id->driver_data;
	काष्ठा ms_data *ms;
	पूर्णांक ret;

	ms = devm_kzalloc(&hdev->dev, माप(*ms), GFP_KERNEL);
	अगर (ms == शून्य)
		वापस -ENOMEM;

	ms->quirks = quirks;

	hid_set_drvdata(hdev, ms);

	अगर (quirks & MS_NOGET)
		hdev->quirks |= HID_QUIRK_NOGET;

	अगर (quirks & MS_SURFACE_DIAL)
		hdev->quirks |= HID_QUIRK_INPUT_PER_APP;

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		जाओ err_मुक्त;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT | ((quirks & MS_HIDINPUT) ?
				HID_CONNECT_HIDINPUT_FORCE : 0));
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		जाओ err_मुक्त;
	पूर्ण

	ret = ms_init_ff(hdev);
	अगर (ret)
		hid_err(hdev, "could not initialize ff, continuing anyway");

	वापस 0;
err_मुक्त:
	वापस ret;
पूर्ण

अटल व्योम ms_हटाओ(काष्ठा hid_device *hdev)
अणु
	hid_hw_stop(hdev);
	ms_हटाओ_ff(hdev);
पूर्ण

अटल स्थिर काष्ठा hid_device_id ms_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MICROSOFT, USB_DEVICE_ID_SIDEWINDER_GV),
		.driver_data = MS_HIDINPUT पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MICROSOFT, USB_DEVICE_ID_MS_OFFICE_KB),
		.driver_data = MS_ERGONOMY पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MICROSOFT, USB_DEVICE_ID_MS_NE4K),
		.driver_data = MS_ERGONOMY पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MICROSOFT, USB_DEVICE_ID_MS_NE4K_JP),
		.driver_data = MS_ERGONOMY पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MICROSOFT, USB_DEVICE_ID_MS_NE7K),
		.driver_data = MS_ERGONOMY पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MICROSOFT, USB_DEVICE_ID_MS_LK6K),
		.driver_data = MS_ERGONOMY | MS_RDESC पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MICROSOFT, USB_DEVICE_ID_MS_PRESENTER_8K_USB),
		.driver_data = MS_PRESENTER पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MICROSOFT, USB_DEVICE_ID_MS_DIGITAL_MEDIA_3K),
		.driver_data = MS_ERGONOMY पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MICROSOFT, USB_DEVICE_ID_MS_DIGITAL_MEDIA_7K),
		.driver_data = MS_ERGONOMY पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MICROSOFT, USB_DEVICE_ID_MS_DIGITAL_MEDIA_600),
		.driver_data = MS_ERGONOMY पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MICROSOFT, USB_DEVICE_ID_MS_DIGITAL_MEDIA_3KV1),
		.driver_data = MS_ERGONOMY पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MICROSOFT, USB_DEVICE_ID_WIRELESS_OPTICAL_DESKTOP_3_0),
		.driver_data = MS_NOGET पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MICROSOFT, USB_DEVICE_ID_MS_COMFORT_MOUSE_4500),
		.driver_data = MS_DUPLICATE_USAGES पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MICROSOFT, USB_DEVICE_ID_MS_POWER_COVER),
		.driver_data = MS_HIDINPUT पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_MICROSOFT, USB_DEVICE_ID_MS_COMFORT_KEYBOARD),
		.driver_data = MS_ERGONOMYपूर्ण,

	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_MICROSOFT, USB_DEVICE_ID_MS_PRESENTER_8K_BT),
		.driver_data = MS_PRESENTER पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_MICROSOFT, 0x091B),
		.driver_data = MS_SURFACE_DIAL पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_MICROSOFT, USB_DEVICE_ID_MS_XBOX_ONE_S_CONTROLLER),
		.driver_data = MS_QUIRK_FF पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_MICROSOFT, USB_DEVICE_ID_8BITDO_SN30_PRO_PLUS),
		.driver_data = MS_QUIRK_FF पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, ms_devices);

अटल काष्ठा hid_driver ms_driver = अणु
	.name = "microsoft",
	.id_table = ms_devices,
	.report_fixup = ms_report_fixup,
	.input_mapping = ms_input_mapping,
	.input_mapped = ms_input_mapped,
	.event = ms_event,
	.probe = ms_probe,
	.हटाओ = ms_हटाओ,
पूर्ण;
module_hid_driver(ms_driver);

MODULE_LICENSE("GPL");
