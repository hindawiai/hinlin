<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * HID driver क्रम the Creative SB0540 receiver
 *
 * Copyright (C) 2019 Red Hat Inc. All Rights Reserved
 *
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश "hid-ids.h"

MODULE_AUTHOR("Bastien Nocera <hadess@hadess.net>");
MODULE_DESCRIPTION("HID Creative SB0540 receiver");
MODULE_LICENSE("GPL");

अटल स्थिर अचिन्हित लघु creative_sb0540_key_table[] = अणु
	KEY_POWER,
	KEY_RESERVED,		/* text: 24bit */
	KEY_RESERVED,		/* 24bit wheel up */
	KEY_RESERVED,		/* 24bit wheel करोwn */
	KEY_RESERVED,		/* text: CMSS */
	KEY_RESERVED,		/* CMSS wheel Up */
	KEY_RESERVED,		/* CMSS wheel Down */
	KEY_RESERVED,		/* text: EAX */
	KEY_RESERVED,		/* EAX wheel up */
	KEY_RESERVED,		/* EAX wheel करोwn */
	KEY_RESERVED,		/* text: 3D Midi */
	KEY_RESERVED,		/* 3D Midi wheel up */
	KEY_RESERVED,		/* 3D Midi wheel करोwn */
	KEY_MUTE,
	KEY_VOLUMEUP,
	KEY_VOLUMEDOWN,
	KEY_UP,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_REWIND,
	KEY_OK,
	KEY_FASTFORWARD,
	KEY_DOWN,
	KEY_AGAIN,		/* text: Return, symbol: Jump to */
	KEY_PLAY,		/* text: Start */
	KEY_ESC,		/* text: Cancel */
	KEY_RECORD,
	KEY_OPTION,
	KEY_MENU,		/* text: Display */
	KEY_PREVIOUS,
	KEY_PLAYPAUSE,
	KEY_NEXT,
	KEY_SLOW,
	KEY_STOP,
	KEY_NUMERIC_1,
	KEY_NUMERIC_2,
	KEY_NUMERIC_3,
	KEY_NUMERIC_4,
	KEY_NUMERIC_5,
	KEY_NUMERIC_6,
	KEY_NUMERIC_7,
	KEY_NUMERIC_8,
	KEY_NUMERIC_9,
	KEY_NUMERIC_0
पूर्ण;

/*
 * Codes and keys from lirc's
 * remotes/creative/lircd.conf.alsa_usb
 * order and size must match creative_sb0540_key_table[] above
 */
अटल स्थिर अचिन्हित लघु creative_sb0540_codes[] = अणु
	0x619E,
	0x916E,
	0x926D,
	0x936C,
	0x718E,
	0x946B,
	0x956A,
	0x8C73,
	0x9669,
	0x9768,
	0x9867,
	0x9966,
	0x9A65,
	0x6E91,
	0x629D,
	0x639C,
	0x7B84,
	0x6B94,
	0x728D,
	0x8778,
	0x817E,
	0x758A,
	0x8D72,
	0x8E71,
	0x8877,
	0x7C83,
	0x738C,
	0x827D,
	0x7689,
	0x7F80,
	0x7986,
	0x7A85,
	0x7D82,
	0x857A,
	0x8B74,
	0x8F70,
	0x906F,
	0x8A75,
	0x847B,
	0x7887,
	0x8976,
	0x837C,
	0x7788,
	0x807F
पूर्ण;

काष्ठा creative_sb0540 अणु
	काष्ठा input_dev *input_dev;
	काष्ठा hid_device *hid;
	अचिन्हित लघु keymap[ARRAY_SIZE(creative_sb0540_key_table)];
पूर्ण;

अटल अंतरभूत u64 reverse(u64 data, पूर्णांक bits)
अणु
	पूर्णांक i;
	u64 c;

	c = 0;
	क्रम (i = 0; i < bits; i++) अणु
		c |= (u64) (((data & (((u64) 1) << i)) ? 1 : 0))
			<< (bits - 1 - i);
	पूर्ण
	वापस (c);
पूर्ण

अटल पूर्णांक get_key(काष्ठा creative_sb0540 *creative_sb0540, u64 keycode)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(creative_sb0540_codes); i++) अणु
		अगर (creative_sb0540_codes[i] == keycode)
			वापस creative_sb0540->keymap[i];
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक creative_sb0540_raw_event(काष्ठा hid_device *hid,
	काष्ठा hid_report *report, u8 *data, पूर्णांक len)
अणु
	काष्ठा creative_sb0540 *creative_sb0540 = hid_get_drvdata(hid);
	u64 code, मुख्य_code;
	पूर्णांक key;

	अगर (len != 6)
		वापस 0;

	/* From daemons/hw_hiddev.c sb0540_rec() in lirc */
	code = reverse(data[5], 8);
	मुख्य_code = (code << 8) + ((~code) & 0xff);

	/*
	 * Flip to get values in the same क्रमmat as
	 * remotes/creative/lircd.conf.alsa_usb in lirc
	 */
	मुख्य_code = ((मुख्य_code & 0xff) << 8) +
		((मुख्य_code & 0xff00) >> 8);

	key = get_key(creative_sb0540, मुख्य_code);
	अगर (key == 0 || key == KEY_RESERVED) अणु
		hid_err(hid, "Could not get a key for main_code %llX\n",
			मुख्य_code);
		वापस 0;
	पूर्ण

	input_report_key(creative_sb0540->input_dev, key, 1);
	input_report_key(creative_sb0540->input_dev, key, 0);
	input_sync(creative_sb0540->input_dev);

	/* let hidraw and hiddev handle the report */
	वापस 0;
पूर्ण

अटल पूर्णांक creative_sb0540_input_configured(काष्ठा hid_device *hid,
		काष्ठा hid_input *hidinput)
अणु
	काष्ठा input_dev *input_dev = hidinput->input;
	काष्ठा creative_sb0540 *creative_sb0540 = hid_get_drvdata(hid);
	पूर्णांक i;

	creative_sb0540->input_dev = input_dev;

	input_dev->keycode = creative_sb0540->keymap;
	input_dev->keycodesize = माप(अचिन्हित लघु);
	input_dev->keycodemax = ARRAY_SIZE(creative_sb0540->keymap);

	input_dev->evbit[0] = BIT(EV_KEY) | BIT(EV_REP);

	स_नकल(creative_sb0540->keymap, creative_sb0540_key_table,
		माप(creative_sb0540->keymap));
	क्रम (i = 0; i < ARRAY_SIZE(creative_sb0540_key_table); i++)
		set_bit(creative_sb0540->keymap[i], input_dev->keybit);
	clear_bit(KEY_RESERVED, input_dev->keybit);

	वापस 0;
पूर्ण

अटल पूर्णांक creative_sb0540_input_mapping(काष्ठा hid_device *hid,
		काष्ठा hid_input *hi, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	/*
	 * We are remapping the keys ourselves, so ignore the hid-input
	 * keymap processing.
	 */
	वापस -1;
पूर्ण

अटल पूर्णांक creative_sb0540_probe(काष्ठा hid_device *hid,
		स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा creative_sb0540 *creative_sb0540;

	creative_sb0540 = devm_kzalloc(&hid->dev,
		माप(काष्ठा creative_sb0540), GFP_KERNEL);

	अगर (!creative_sb0540)
		वापस -ENOMEM;

	creative_sb0540->hid = hid;

	/* क्रमce input as some remotes bypass the input registration */
	hid->quirks |= HID_QUIRK_HIDINPUT_FORCE;

	hid_set_drvdata(hid, creative_sb0540);

	ret = hid_parse(hid);
	अगर (ret) अणु
		hid_err(hid, "parse failed\n");
		वापस ret;
	पूर्ण

	ret = hid_hw_start(hid, HID_CONNECT_DEFAULT);
	अगर (ret) अणु
		hid_err(hid, "hw start failed\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hid_device_id creative_sb0540_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_CREATIVELABS, USB_DEVICE_ID_CREATIVE_SB0540) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, creative_sb0540_devices);

अटल काष्ठा hid_driver creative_sb0540_driver = अणु
	.name = "creative-sb0540",
	.id_table = creative_sb0540_devices,
	.raw_event = creative_sb0540_raw_event,
	.input_configured = creative_sb0540_input_configured,
	.probe = creative_sb0540_probe,
	.input_mapping = creative_sb0540_input_mapping,
पूर्ण;
module_hid_driver(creative_sb0540_driver);
