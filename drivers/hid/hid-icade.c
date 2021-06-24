<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ION iCade input driver
 *
 *  Copyright (c) 2012 Bastien Nocera <hadess@hadess.net>
 *  Copyright (c) 2012 Benjamin Tissoires <benjamin.tissoires@gmail.com>
 */

/*
 */

#समावेश <linux/device.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>

#समावेश "hid-ids.h"

/*
 *   ै      A C Y L
 *  ै ै
 *   ै      B X Z R
 *
 *
 *  UP ON,OFF  = w,e
 *  RT ON,OFF  = d,c
 *  DN ON,OFF  = x,z
 *  LT ON,OFF  = a,q
 *  A  ON,OFF  = y,t
 *  B  ON,OFF  = h,r
 *  C  ON,OFF  = u,f
 *  X  ON,OFF  = j,n
 *  Y  ON,OFF  = i,m
 *  Z  ON,OFF  = k,p
 *  L  ON,OFF  = o,g
 *  R  ON,OFF  = l,v
 */

/* The translation code uses HID usage instead of input layer
 * keys. This code generates a lookup table that makes
 * translation quick.
 *
 * #समावेश <linux/input.h>
 * #समावेश <मानकपन.स>
 * #समावेश <निश्चित.स>
 *
 * #घोषणा unk     KEY_UNKNOWN
 *
 * < copy of hid_keyboard[] from hid-input.c >
 *
 * काष्ठा icade_key_translation अणु
 *     पूर्णांक         from;
 *     स्थिर अक्षर *to;
 *     पूर्णांक         press;
 * पूर्ण;
 *
 * अटल स्थिर काष्ठा icade_key_translation icade_keys[] = अणु
 *    अणु KEY_W,        "KEY_UP",         1 पूर्ण,
 *    अणु KEY_E,        "KEY_UP",         0 पूर्ण,
 *    अणु KEY_D,        "KEY_RIGHT",      1 पूर्ण,
 *    अणु KEY_C,        "KEY_RIGHT",      0 पूर्ण,
 *    अणु KEY_X,        "KEY_DOWN",       1 पूर्ण,
 *    अणु KEY_Z,        "KEY_DOWN",       0 पूर्ण,
 *    अणु KEY_A,        "KEY_LEFT",       1 पूर्ण,
 *    अणु KEY_Q,        "KEY_LEFT",       0 पूर्ण,
 *    अणु KEY_Y,        "BTN_A",          1 पूर्ण,
 *    अणु KEY_T,        "BTN_A",          0 पूर्ण,
 *    अणु KEY_H,        "BTN_B",          1 पूर्ण,
 *    अणु KEY_R,        "BTN_B",          0 पूर्ण,
 *    अणु KEY_U,        "BTN_C",          1 पूर्ण,
 *    अणु KEY_F,        "BTN_C",          0 पूर्ण,
 *    अणु KEY_J,        "BTN_X",          1 पूर्ण,
 *    अणु KEY_N,        "BTN_X",          0 पूर्ण,
 *    अणु KEY_I,        "BTN_Y",          1 पूर्ण,
 *    अणु KEY_M,        "BTN_Y",          0 पूर्ण,
 *    अणु KEY_K,        "BTN_Z",          1 पूर्ण,
 *    अणु KEY_P,        "BTN_Z",          0 पूर्ण,
 *    अणु KEY_O,        "BTN_THUMBL",     1 पूर्ण,
 *    अणु KEY_G,        "BTN_THUMBL",     0 पूर्ण,
 *    अणु KEY_L,        "BTN_THUMBR",     1 पूर्ण,
 *    अणु KEY_V,        "BTN_THUMBR",     0 पूर्ण,
 *
 *    अणु पूर्ण
 * पूर्ण;
 *
 * अटल पूर्णांक
 * usage_क्रम_key (पूर्णांक key)
 * अणु
 *     पूर्णांक i;
 *     क्रम (i = 0; i < 256; i++) अणु
 *     अगर (hid_keyboard[i] == key)
 *         वापस i;
 *     पूर्ण
 *     निश्चित(0);
 * पूर्ण
 *
 * पूर्णांक मुख्य (पूर्णांक argc, अक्षर **argv)
 * अणु
 *     स्थिर काष्ठा icade_key_translation *trans;
 *     पूर्णांक max_usage = 0;
 *
 *     क्रम (trans = icade_keys; trans->from; trans++) अणु
 *         पूर्णांक usage = usage_क्रम_key (trans->from);
 *         max_usage = usage > max_usage ? usage : max_usage;
 *     पूर्ण
 *
 *     म_लिखो ("#define ICADE_MAX_USAGE %d\n\n", max_usage);
 *     म_लिखो ("struct icade_key {\n");
 *     म_लिखो ("\tu16 to;\n");
 *     म_लिखो ("\tu8 press:1;\n");
 *     म_लिखो ("};\n\n");
 *     म_लिखो ("static const struct icade_key "
 *             "icade_usage_table[%d] = {\n", max_usage + 1);
 *     क्रम (trans = icade_keys; trans->from; trans++) अणु
 *         म_लिखो ("\t[%d] = { %s, %d },\n",
 *                 usage_क्रम_key (trans->from), trans->to, trans->press);
 *     पूर्ण
 *     म_लिखो ("};\n");
 *
 *     वापस 0;
 * पूर्ण
 */

#घोषणा ICADE_MAX_USAGE 29

काष्ठा icade_key अणु
	u16 to;
	u8 press:1;
पूर्ण;

अटल स्थिर काष्ठा icade_key icade_usage_table[30] = अणु
	[26] = अणु KEY_UP, 1 पूर्ण,
	[8] = अणु KEY_UP, 0 पूर्ण,
	[7] = अणु KEY_RIGHT, 1 पूर्ण,
	[6] = अणु KEY_RIGHT, 0 पूर्ण,
	[27] = अणु KEY_DOWN, 1 पूर्ण,
	[29] = अणु KEY_DOWN, 0 पूर्ण,
	[4] = अणु KEY_LEFT, 1 पूर्ण,
	[20] = अणु KEY_LEFT, 0 पूर्ण,
	[28] = अणु BTN_A, 1 पूर्ण,
	[23] = अणु BTN_A, 0 पूर्ण,
	[11] = अणु BTN_B, 1 पूर्ण,
	[21] = अणु BTN_B, 0 पूर्ण,
	[24] = अणु BTN_C, 1 पूर्ण,
	[9] = अणु BTN_C, 0 पूर्ण,
	[13] = अणु BTN_X, 1 पूर्ण,
	[17] = अणु BTN_X, 0 पूर्ण,
	[12] = अणु BTN_Y, 1 पूर्ण,
	[16] = अणु BTN_Y, 0 पूर्ण,
	[14] = अणु BTN_Z, 1 पूर्ण,
	[19] = अणु BTN_Z, 0 पूर्ण,
	[18] = अणु BTN_THUMBL, 1 पूर्ण,
	[10] = अणु BTN_THUMBL, 0 पूर्ण,
	[15] = अणु BTN_THUMBR, 1 पूर्ण,
	[25] = अणु BTN_THUMBR, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा icade_key *icade_find_translation(u16 from)
अणु
	अगर (from > ICADE_MAX_USAGE)
		वापस शून्य;
	वापस &icade_usage_table[from];
पूर्ण

अटल पूर्णांक icade_event(काष्ठा hid_device *hdev, काष्ठा hid_field *field,
		काष्ठा hid_usage *usage, __s32 value)
अणु
	स्थिर काष्ठा icade_key *trans;

	अगर (!(hdev->claimed & HID_CLAIMED_INPUT) || !field->hidinput ||
			!usage->type)
		वापस 0;

	/* We ignore the fake key up, and act only on key करोwn */
	अगर (!value)
		वापस 1;

	trans = icade_find_translation(usage->hid & HID_USAGE);

	अगर (!trans)
		वापस 1;

	input_event(field->hidinput->input, usage->type,
			trans->to, trans->press);

	वापस 1;
पूर्ण

अटल पूर्णांक icade_input_mapping(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	स्थिर काष्ठा icade_key *trans;

	अगर ((usage->hid & HID_USAGE_PAGE) == HID_UP_KEYBOARD) अणु
		trans = icade_find_translation(usage->hid & HID_USAGE);

		अगर (!trans)
			वापस -1;

		hid_map_usage(hi, usage, bit, max, EV_KEY, trans->to);
		set_bit(trans->to, hi->input->keybit);

		वापस 1;
	पूर्ण

	/* ignore others */
	वापस -1;

पूर्ण

अटल पूर्णांक icade_input_mapped(काष्ठा hid_device *hdev, काष्ठा hid_input *hi,
		काष्ठा hid_field *field, काष्ठा hid_usage *usage,
		अचिन्हित दीर्घ **bit, पूर्णांक *max)
अणु
	अगर (usage->type == EV_KEY)
		set_bit(usage->type, hi->input->evbit);

	वापस -1;
पूर्ण

अटल स्थिर काष्ठा hid_device_id icade_devices[] = अणु
	अणु HID_BLUETOOTH_DEVICE(USB_VENDOR_ID_ION, USB_DEVICE_ID_ICADE) पूर्ण,

	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, icade_devices);

अटल काष्ठा hid_driver icade_driver = अणु
	.name = "icade",
	.id_table = icade_devices,
	.event = icade_event,
	.input_mapped = icade_input_mapped,
	.input_mapping = icade_input_mapping,
पूर्ण;
module_hid_driver(icade_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bastien Nocera <hadess@hadess.net>");
MODULE_DESCRIPTION("ION iCade input driver");
