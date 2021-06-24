<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  USB HID quirks support क्रम Linux
 *
 *  Copyright (c) 1999 Andreas Gal
 *  Copyright (c) 2000-2005 Vojtech Pavlik <vojtech@suse.cz>
 *  Copyright (c) 2005 Michael Haboustak <mike-@cinci.rr.com> क्रम Concept2, Inc
 *  Copyright (c) 2006-2007 Jiri Kosina
 *  Copyright (c) 2008 Jiri Slaby <jirislaby@gmail.com>
 */

/*
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "hid-ids.h"

#घोषणा APPLE_RDESC_JIS		0x0001
#घोषणा APPLE_IGNORE_MOUSE	0x0002
#घोषणा APPLE_HAS_FN		0x0004
#घोषणा APPLE_HIDDEV		0x0008
/* 0x0010 reserved, was: APPLE_ISO_KEYBOARD */
#घोषणा APPLE_MIGHTYMOUSE	0x0020
#घोषणा APPLE_INVERT_HWHEEL	0x0040
#घोषणा APPLE_IGNORE_HIDINPUT	0x0080
#घोषणा APPLE_NUMLOCK_EMULATION	0x0100

#घोषणा APPLE_FLAG_FKEY		0x01

#घोषणा HID_COUNTRY_INTERNATIONAL_ISO	13

अटल अचिन्हित पूर्णांक fnmode = 1;
module_param(fnmode, uपूर्णांक, 0644);
MODULE_PARM_DESC(fnmode, "Mode of fn key on Apple keyboards (0 = disabled, "
		"[1] = fkeyslast, 2 = fkeysfirst)");

अटल अचिन्हित पूर्णांक iso_layout = 1;
module_param(iso_layout, uपूर्णांक, 0644);
MODULE_PARM_DESC(iso_layout, "Enable/Disable hardcoded ISO-layout of the keyboard. "
		"(0 = disabled, [1] = enabled)");

अटल अचिन्हित पूर्णांक swap_opt_cmd;
module_param(swap_opt_cmd, uपूर्णांक, 0644);
MODULE_PARM_DESC(swap_opt_cmd, "Swap the Option (\"Alt\") and Command (\"Flag\") keys. "
		"(For people who want to keep Windows PC keyboard muscle memory. "
		"[0] = as-is, Mac layout. 1 = swapped, Windows layout.)");

अटल अचिन्हित पूर्णांक swap_fn_leftctrl;
module_param(swap_fn_leftctrl, uपूर्णांक, 0644);
MODULE_PARM_DESC(swap_fn_leftctrl, "Swap the Fn and left Control keys. "
		"(For people who want to keep PC keyboard muscle memory. "
		"[0] = as-is, Mac layout, 1 = swapped, PC layout)");

काष्ठा apple_sc अणु
	अचिन्हित दीर्घ quirks;
	अचिन्हित पूर्णांक fn_on;
	अचिन्हित पूर्णांक fn_found;
	DECLARE_BITMAP(pressed_numlock, KEY_CNT);
पूर्ण;

काष्ठा apple_key_translation अणु
	u16 from;
	u16 to;
	u8 flags;
पूर्ण;

अटल स्थिर काष्ठा apple_key_translation macbookair_fn_keys[] = अणु
	अणु KEY_BACKSPACE, KEY_DELETE पूर्ण,
	अणु KEY_ENTER,	KEY_INSERT पूर्ण,
	अणु KEY_F1,	KEY_BRIGHTNESSDOWN, APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F2,	KEY_BRIGHTNESSUP,   APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F3,	KEY_SCALE,          APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F4,	KEY_DASHBOARD,      APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F6,	KEY_PREVIOUSSONG,   APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F7,	KEY_PLAYPAUSE,      APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F8,	KEY_NEXTSONG,       APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F9,	KEY_MUTE,           APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F10,	KEY_VOLUMEDOWN,     APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F11,	KEY_VOLUMEUP,       APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F12,	KEY_EJECTCD,        APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_UP,	KEY_PAGEUP पूर्ण,
	अणु KEY_DOWN,	KEY_PAGEDOWN पूर्ण,
	अणु KEY_LEFT,	KEY_HOME पूर्ण,
	अणु KEY_RIGHT,	KEY_END पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा apple_key_translation apple_fn_keys[] = अणु
	अणु KEY_BACKSPACE, KEY_DELETE पूर्ण,
	अणु KEY_ENTER,	KEY_INSERT पूर्ण,
	अणु KEY_F1,	KEY_BRIGHTNESSDOWN, APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F2,	KEY_BRIGHTNESSUP,   APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F3,	KEY_SCALE,          APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F4,	KEY_DASHBOARD,      APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F5,	KEY_KBDILLUMDOWN,   APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F6,	KEY_KBDILLUMUP,     APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F7,	KEY_PREVIOUSSONG,   APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F8,	KEY_PLAYPAUSE,      APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F9,	KEY_NEXTSONG,       APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F10,	KEY_MUTE,           APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F11,	KEY_VOLUMEDOWN,     APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F12,	KEY_VOLUMEUP,       APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_UP,	KEY_PAGEUP पूर्ण,
	अणु KEY_DOWN,	KEY_PAGEDOWN पूर्ण,
	अणु KEY_LEFT,	KEY_HOME पूर्ण,
	अणु KEY_RIGHT,	KEY_END पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा apple_key_translation घातerbook_fn_keys[] = अणु
	अणु KEY_BACKSPACE, KEY_DELETE पूर्ण,
	अणु KEY_F1,	KEY_BRIGHTNESSDOWN,     APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F2,	KEY_BRIGHTNESSUP,       APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F3,	KEY_MUTE,               APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F4,	KEY_VOLUMEDOWN,         APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F5,	KEY_VOLUMEUP,           APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F6,	KEY_NUMLOCK,            APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F7,	KEY_SWITCHVIDEOMODE,    APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F8,	KEY_KBDILLUMTOGGLE,     APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F9,	KEY_KBDILLUMDOWN,       APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_F10,	KEY_KBDILLUMUP,         APPLE_FLAG_FKEY पूर्ण,
	अणु KEY_UP,	KEY_PAGEUP पूर्ण,
	अणु KEY_DOWN,	KEY_PAGEDOWN पूर्ण,
	अणु KEY_LEFT,	KEY_HOME पूर्ण,
	अणु KEY_RIGHT,	KEY_END पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा apple_key_translation घातerbook_numlock_keys[] = अणु
	अणु KEY_J,	KEY_KP1 पूर्ण,
	अणु KEY_K,	KEY_KP2 पूर्ण,
	अणु KEY_L,	KEY_KP3 पूर्ण,
	अणु KEY_U,	KEY_KP4 पूर्ण,
	अणु KEY_I,	KEY_KP5 पूर्ण,
	अणु KEY_O,	KEY_KP6 पूर्ण,
	अणु KEY_7,	KEY_KP7 पूर्ण,
	अणु KEY_8,	KEY_KP8 पूर्ण,
	अणु KEY_9,	KEY_KP9 पूर्ण,
	अणु KEY_M,	KEY_KP0 पूर्ण,
	अणु KEY_DOT,	KEY_KPDOT पूर्ण,
	अणु KEY_SLASH,	KEY_KPPLUS पूर्ण,
	अणु KEY_SEMICOLON, KEY_KPMINUS पूर्ण,
	अणु KEY_P,	KEY_KPASTERISK पूर्ण,
	अणु KEY_MINUS,	KEY_KPEQUAL पूर्ण,
	अणु KEY_0,	KEY_KPSLASH पूर्ण,
	अणु KEY_F6,	KEY_NUMLOCK पूर्ण,
	अणु KEY_KPENTER,	KEY_KPENTER पूर्ण,
	अणु KEY_BACKSPACE, KEY_BACKSPACE पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा apple_key_translation apple_iso_keyboard[] = अणु
	अणु KEY_GRAVE,	KEY_102ND पूर्ण,
	अणु KEY_102ND,	KEY_GRAVE पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा apple_key_translation swapped_option_cmd_keys[] = अणु
	अणु KEY_LEFTALT,	KEY_LEFTMETA पूर्ण,
	अणु KEY_LEFTMETA,	KEY_LEFTALT पूर्ण,
	अणु KEY_RIGHTALT,	KEY_RIGHTMETA पूर्ण,
	अणु KEY_RIGHTMETA,KEY_RIGHTALT पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा apple_key_translation swapped_fn_leftctrl_keys[] = अणु
	अणु KEY_FN, KEY_LEFTCTRL पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा apple_key_translation *apple_find_translation(
		स्थिर काष्ठा apple_key_translation *table, u16 from)
अणु
	स्थिर काष्ठा apple_key_translation *trans;

	/* Look क्रम the translation */
	क्रम (trans = table; trans->from; trans++)
		अगर (trans->from == from)
			वापस trans;

	वापस शून्य;
पूर्ण

अटल पूर्णांक hidinput_apple_event(काष्ठा hid_device *hid, काष्ठा input_dev *input,
		काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा apple_sc *asc = hid_get_drvdata(hid);
	स्थिर काष्ठा apple_key_translation *trans, *table;
	bool करो_translate;
	u16 code = 0;

	u16 fn_keycode = (swap_fn_leftctrl) ? (KEY_LEFTCTRL) : (KEY_FN);

	अगर (usage->code == fn_keycode) अणु
		asc->fn_on = !!value;
		input_event(input, usage->type, KEY_FN, value);
		वापस 1;
	पूर्ण

	अगर (fnmode) अणु
		अगर (hid->product >= USB_DEVICE_ID_APPLE_WELLSPRING4_ANSI &&
				hid->product <= USB_DEVICE_ID_APPLE_WELLSPRING4A_JIS)
			table = macbookair_fn_keys;
		अन्यथा अगर (hid->product < 0x21d || hid->product >= 0x300)
			table = घातerbook_fn_keys;
		अन्यथा
			table = apple_fn_keys;

		trans = apple_find_translation (table, usage->code);

		अगर (trans) अणु
			अगर (test_bit(trans->from, input->key))
				code = trans->from;
			अन्यथा अगर (test_bit(trans->to, input->key))
				code = trans->to;

			अगर (!code) अणु
				अगर (trans->flags & APPLE_FLAG_FKEY) अणु
					चयन (fnmode) अणु
					हाल 1:
						करो_translate = !asc->fn_on;
						अवरोध;
					हाल 2:
						करो_translate = asc->fn_on;
						अवरोध;
					शेष:
						/* should never happen */
						करो_translate = false;
					पूर्ण
				पूर्ण अन्यथा अणु
					करो_translate = asc->fn_on;
				पूर्ण

				code = करो_translate ? trans->to : trans->from;
			पूर्ण

			input_event(input, usage->type, code, value);
			वापस 1;
		पूर्ण

		अगर (asc->quirks & APPLE_NUMLOCK_EMULATION &&
				(test_bit(usage->code, asc->pressed_numlock) ||
				test_bit(LED_NUML, input->led))) अणु
			trans = apple_find_translation(घातerbook_numlock_keys,
					usage->code);

			अगर (trans) अणु
				अगर (value)
					set_bit(usage->code,
							asc->pressed_numlock);
				अन्यथा
					clear_bit(usage->code,
							asc->pressed_numlock);

				input_event(input, usage->type, trans->to,
						value);
			पूर्ण

			वापस 1;
		पूर्ण
	पूर्ण

	अगर (iso_layout) अणु
		अगर (hid->country == HID_COUNTRY_INTERNATIONAL_ISO) अणु
			trans = apple_find_translation(apple_iso_keyboard, usage->code);
			अगर (trans) अणु
				input_event(input, usage->type, trans->to, value);
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (swap_opt_cmd) अणु
		trans = apple_find_translation(swapped_option_cmd_keys, usage->code);
		अगर (trans) अणु
			input_event(input, usage->type, trans->to, value);
			वापस 1;
		पूर्ण
	पूर्ण

	अगर (swap_fn_leftctrl) अणु
		trans = apple_find_translation(swapped_fn_leftctrl_keys, usage->code);
		अगर (trans) अणु
			input_event(input, usage->type, trans->to, value);
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक apple_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, __s32 value)
अणु
	काष्ठा apple_sc *asc = hid_get_drvdata(hdev);

	अगर (!(hdev->claimed & HID_CLAIMED_INPUT) || !field->hidinput ||
			!usage->type)
		वापस 0;

	अगर ((asc->quirks & APPLE_INVERT_HWHEEL) &&
			usage->code == REL_HWHEEL) अणु
		input_event(field->hidinput->input, usage->type, usage->code,
				-value);
		वापस 1;
	पूर्ण

	अगर ((asc->quirks & APPLE_HAS_FN) &&
			hidinput_apple_event(hdev, field->hidinput->input,
				usage, value))
		वापस 1;


	वापस 0;
पूर्ण

/*
 * MacBook JIS keyboard has wrong logical maximum
 */
अटल __u8 *apple_report_fixup(काष्ठा hid_device *hdev, __u8 *rdesc,
		अचिन्हित पूर्णांक *rsize)
अणु
	काष्ठा apple_sc *asc = hid_get_drvdata(hdev);

	अगर ((asc->quirks & APPLE_RDESC_JIS) && *rsize >= 60 &&
			rdesc[53] == 0x65 && rdesc[59] == 0x65) अणु
		hid_info(hdev,
			 "fixing up MacBook JIS keyboard report descriptor\n");
		rdesc[53] = rdesc[59] = 0xe7;
	पूर्ण
	वापस rdesc;
पूर्ण

अटल व्योम apple_setup_input(काष्ठा input_dev *input)
अणु
	स्थिर काष्ठा apple_key_translation *trans;

	set_bit(KEY_NUMLOCK, input->keybit);

	/* Enable all needed keys */
	क्रम (trans = apple_fn_keys; trans->from; trans++)
		set_bit(trans->to, input->keybit);

	क्रम (trans = घातerbook_fn_keys; trans->from; trans++)
		set_bit(trans->to, input->keybit);

	क्रम (trans = घातerbook_numlock_keys; trans->from; trans++)
		set_bit(trans->to, input->keybit);

	क्रम (trans = apple_iso_keyboard; trans->from; trans++)
		set_bit(trans->to, input->keybit);

	अगर (swap_fn_leftctrl) अणु
		क्रम (trans = swapped_fn_leftctrl_keys; trans->from; trans++)
			set_bit(trans->to, input->keybit);
	पूर्ण
पूर्ण

अटल पूर्णांक apple_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	काष्ठा apple_sc *asc = hid_get_drvdata(hdev);

	अगर (usage->hid == (HID_UP_CUSTOM | 0x0003) ||
			usage->hid == (HID_UP_MSVENDOR | 0x0003) ||
			usage->hid == (HID_UP_HPVENDOR2 | 0x0003)) अणु
		/* The fn key on Apple USB keyboards */
		set_bit(EV_REP, hi->input->evbit);
		hid_map_usage_clear(hi, usage, bit, max, EV_KEY, KEY_FN);
		asc->fn_found = true;
		apple_setup_input(hi->input);
		वापस 1;
	पूर्ण

	/* we want the hid layer to go through standard path (set and ignore) */
	वापस 0;
पूर्ण

अटल पूर्णांक apple_input_mapped(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	काष्ठा apple_sc *asc = hid_get_drvdata(hdev);

	अगर (asc->quirks & APPLE_MIGHTYMOUSE) अणु
		अगर (usage->hid == HID_GD_Z)
			hid_map_usage(hi, usage, bit, max, EV_REL, REL_HWHEEL);
		अन्यथा अगर (usage->code == BTN_1)
			hid_map_usage(hi, usage, bit, max, EV_KEY, BTN_2);
		अन्यथा अगर (usage->code == BTN_2)
			hid_map_usage(hi, usage, bit, max, EV_KEY, BTN_1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक apple_input_configured(काष्ठा hid_device *hdev,
		काष्ठा hid_input *hidinput)
अणु
	काष्ठा apple_sc *asc = hid_get_drvdata(hdev);

	अगर ((asc->quirks & APPLE_HAS_FN) && !asc->fn_found) अणु
		hid_info(hdev, "Fn key not found (Apple Wireless Keyboard clone?), disabling Fn key handling\n");
		asc->quirks = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक apple_probe(काष्ठा hid_device *hdev,
		स्थिर काष्ठा hid_device_id *id)
अणु
	अचिन्हित दीर्घ quirks = id->driver_data;
	काष्ठा apple_sc *asc;
	अचिन्हित पूर्णांक connect_mask = HID_CONNECT_DEFAULT;
	पूर्णांक ret;

	asc = devm_kzalloc(&hdev->dev, माप(*asc), GFP_KERNEL);
	अगर (asc == शून्य) अणु
		hid_err(hdev, "can't alloc apple descriptor\n");
		वापस -ENOMEM;
	पूर्ण

	asc->quirks = quirks;

	hid_set_drvdata(hdev, asc);

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		वापस ret;
	पूर्ण

	अगर (quirks & APPLE_HIDDEV)
		connect_mask |= HID_CONNECT_HIDDEV_FORCE;
	अगर (quirks & APPLE_IGNORE_HIDINPUT)
		connect_mask &= ~HID_CONNECT_HIDINPUT;

	ret = hid_hw_start(hdev, connect_mask);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id apple_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_MIGHTYMOUSE),
		.driver_data = APPLE_MIGHTYMOUSE | APPLE_INVERT_HWHEEL पूर्ण,

	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_FOUNTAIN_ANSI),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_FOUNTAIN_ISO),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_GEYSER_ANSI),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_GEYSER_ISO),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_GEYSER_JIS),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_GEYSER3_ANSI),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_GEYSER3_ISO),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_GEYSER3_JIS),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN |
			APPLE_RDESC_JIS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_GEYSER4_ANSI),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_GEYSER4_ISO),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_GEYSER4_JIS),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN |
			APPLE_RDESC_JIS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_ALU_MINI_ANSI),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_ALU_MINI_ISO),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_ALU_MINI_JIS),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_ALU_ANSI),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_ALU_ISO),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_ALU_JIS),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_GEYSER4_HF_ANSI),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_GEYSER4_HF_ISO),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_GEYSER4_HF_JIS),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN |
			APPLE_RDESC_JIS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_ALU_REVB_ANSI),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_ALU_REVB_ISO),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_ALU_REVB_ISO),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_ALU_REVB_JIS),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_ALU_WIRELESS_ANSI),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_ALU_WIRELESS_ISO),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_ALU_WIRELESS_2011_ISO),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_APPLE,
				USB_DEVICE_ID_APPLE_ALU_WIRELESS_2011_ANSI),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_APPLE,
				USB_DEVICE_ID_APPLE_ALU_WIRELESS_2011_JIS),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_ALU_WIRELESS_JIS),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_MAGIC_KEYBOARD_ANSI),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(BT_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_MAGIC_KEYBOARD_ANSI),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_MAGIC_KEYBOARD_NUMPAD_ANSI),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(BT_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_MAGIC_KEYBOARD_NUMPAD_ANSI),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING_ANSI),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING_ISO),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING_JIS),
		.driver_data = APPLE_HAS_FN | APPLE_RDESC_JIS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING2_ANSI),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING2_ISO),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING2_JIS),
		.driver_data = APPLE_HAS_FN | APPLE_RDESC_JIS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING3_ANSI),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING3_ISO),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING3_JIS),
		.driver_data = APPLE_HAS_FN | APPLE_RDESC_JIS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING4_ANSI),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING4_ISO),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING4_JIS),
		.driver_data = APPLE_HAS_FN | APPLE_RDESC_JIS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING4A_ANSI),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING4A_ISO),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING4A_JIS),
		.driver_data = APPLE_HAS_FN | APPLE_RDESC_JIS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING5_ANSI),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING5_ISO),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING5_JIS),
		.driver_data = APPLE_HAS_FN | APPLE_RDESC_JIS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING6_ANSI),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING6_ISO),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING6_JIS),
		.driver_data = APPLE_HAS_FN | APPLE_RDESC_JIS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING6A_ANSI),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING6A_ISO),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING6A_JIS),
		.driver_data = APPLE_HAS_FN | APPLE_RDESC_JIS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING5A_ANSI),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING5A_ISO),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING5A_JIS),
		.driver_data = APPLE_HAS_FN | APPLE_RDESC_JIS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING7_ANSI),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING7_ISO),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING7_JIS),
		.driver_data = APPLE_HAS_FN | APPLE_RDESC_JIS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING7A_ANSI),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING7A_ISO),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING7A_JIS),
		.driver_data = APPLE_HAS_FN | APPLE_RDESC_JIS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING8_ANSI),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING8_ISO),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING8_JIS),
		.driver_data = APPLE_HAS_FN | APPLE_RDESC_JIS पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING9_ANSI),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING9_ISO),
		.driver_data = APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_WELLSPRING9_JIS),
		.driver_data = APPLE_HAS_FN | APPLE_RDESC_JIS पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_ALU_WIRELESS_2009_ANSI),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_ALU_WIRELESS_2009_ISO),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_ALU_WIRELESS_2009_JIS),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_FOUNTAIN_TP_ONLY),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_APPLE, USB_DEVICE_ID_APPLE_GEYSER1_TP_ONLY),
		.driver_data = APPLE_NUMLOCK_EMULATION | APPLE_HAS_FN पूर्ण,

	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, apple_devices);

अटल काष्ठा hid_driver apple_driver = अणु
	.name = "apple",
	.id_table = apple_devices,
	.report_fixup = apple_report_fixup,
	.probe = apple_probe,
	.event = apple_event,
	.input_mapping = apple_input_mapping,
	.input_mapped = apple_input_mapped,
	.input_configured = apple_input_configured,
पूर्ण;
module_hid_driver(apple_driver);

MODULE_LICENSE("GPL");
