<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* DVB USB compliant Linux driver क्रम the Afatech 9005
 * USB1.1 DVB-T receiver.
 *
 * Standard remote decode function
 *
 * Copyright (C) 2007 Luca Olivetti (luca@ventoso.org)
 *
 * Thanks to Afatech who kindly provided inक्रमmation.
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#समावेश "af9005.h"
/* debug */
अटल पूर्णांक dvb_usb_af9005_remote_debug;
module_param_named(debug, dvb_usb_af9005_remote_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug,
		 "enable (1) or disable (0) debug messages."
		 DVB_USB_DEBUG_STATUS);

#घोषणा deb_decode(args...)   dprपूर्णांकk(dvb_usb_af9005_remote_debug,0x01,args)

काष्ठा rc_map_table rc_map_af9005_table[] = अणु

	अणु0x01b7, KEY_POWERपूर्ण,
	अणु0x01a7, KEY_VOLUMEUPपूर्ण,
	अणु0x0187, KEY_CHANNELUPपूर्ण,
	अणु0x017f, KEY_MUTEपूर्ण,
	अणु0x01bf, KEY_VOLUMEDOWNपूर्ण,
	अणु0x013f, KEY_CHANNELDOWNपूर्ण,
	अणु0x01df, KEY_1पूर्ण,
	अणु0x015f, KEY_2पूर्ण,
	अणु0x019f, KEY_3पूर्ण,
	अणु0x011f, KEY_4पूर्ण,
	अणु0x01ef, KEY_5पूर्ण,
	अणु0x016f, KEY_6पूर्ण,
	अणु0x01af, KEY_7पूर्ण,
	अणु0x0127, KEY_8पूर्ण,
	अणु0x0107, KEY_9पूर्ण,
	अणु0x01cf, KEY_ZOOMपूर्ण,
	अणु0x014f, KEY_0पूर्ण,
	अणु0x018f, KEY_GOTOपूर्ण,	/* marked jump on the remote */

	अणु0x00bd, KEY_POWERपूर्ण,
	अणु0x007d, KEY_VOLUMEUPपूर्ण,
	अणु0x00fd, KEY_CHANNELUPपूर्ण,
	अणु0x009d, KEY_MUTEपूर्ण,
	अणु0x005d, KEY_VOLUMEDOWNपूर्ण,
	अणु0x00dd, KEY_CHANNELDOWNपूर्ण,
	अणु0x00ad, KEY_1पूर्ण,
	अणु0x006d, KEY_2पूर्ण,
	अणु0x00ed, KEY_3पूर्ण,
	अणु0x008d, KEY_4पूर्ण,
	अणु0x004d, KEY_5पूर्ण,
	अणु0x00cd, KEY_6पूर्ण,
	अणु0x00b5, KEY_7पूर्ण,
	अणु0x0075, KEY_8पूर्ण,
	अणु0x00f5, KEY_9पूर्ण,
	अणु0x0095, KEY_ZOOMपूर्ण,
	अणु0x0055, KEY_0पूर्ण,
	अणु0x00d5, KEY_GOTOपूर्ण,	/* marked jump on the remote */
पूर्ण;

पूर्णांक rc_map_af9005_table_size = ARRAY_SIZE(rc_map_af9005_table);

अटल पूर्णांक repeatable_keys[] = अणु
	KEY_VOLUMEUP,
	KEY_VOLUMEDOWN,
	KEY_CHANNELUP,
	KEY_CHANNELDOWN
पूर्ण;

पूर्णांक af9005_rc_decode(काष्ठा dvb_usb_device *d, u8 * data, पूर्णांक len, u32 * event,
		     पूर्णांक *state)
अणु
	u16 mark, space;
	u32 result;
	u8 cust, dat, invdat;
	पूर्णांक i;

	अगर (len >= 6) अणु
		mark = (u16) (data[0] << 8) + data[1];
		space = (u16) (data[2] << 8) + data[3];
		अगर (space * 3 < mark) अणु
			क्रम (i = 0; i < ARRAY_SIZE(repeatable_keys); i++) अणु
				अगर (d->last_event == repeatable_keys[i]) अणु
					*state = REMOTE_KEY_REPEAT;
					*event = d->last_event;
					deb_decode("repeat key, event %x\n",
						   *event);
					वापस 0;
				पूर्ण
			पूर्ण
			deb_decode("repeated key ignored (non repeatable)\n");
			वापस 0;
		पूर्ण अन्यथा अगर (len >= 33 * 4) अणु	/*32 bits + start code */
			result = 0;
			क्रम (i = 4; i < 4 + 32 * 4; i += 4) अणु
				result <<= 1;
				mark = (u16) (data[i] << 8) + data[i + 1];
				mark >>= 1;
				space = (u16) (data[i + 2] << 8) + data[i + 3];
				space >>= 1;
				अगर (mark * 2 > space)
					result += 1;
			पूर्ण
			deb_decode("key pressed, raw value %x\n", result);
			अगर ((result & 0xff000000) != 0xfe000000) अणु
				deb_decode
				    ("doesn't start with 0xfe, ignored\n");
				वापस 0;
			पूर्ण
			cust = (result >> 16) & 0xff;
			dat = (result >> 8) & 0xff;
			invdat = (~result) & 0xff;
			अगर (dat != invdat) अणु
				deb_decode("code != inverted code\n");
				वापस 0;
			पूर्ण
			क्रम (i = 0; i < rc_map_af9005_table_size; i++) अणु
				अगर (rc5_custom(&rc_map_af9005_table[i]) == cust
				    && rc5_data(&rc_map_af9005_table[i]) == dat) अणु
					*event = rc_map_af9005_table[i].keycode;
					*state = REMOTE_KEY_PRESSED;
					deb_decode
					    ("key pressed, event %x\n", *event);
					वापस 0;
				पूर्ण
			पूर्ण
			deb_decode("not found in table\n");
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

EXPORT_SYMBOL(rc_map_af9005_table);
EXPORT_SYMBOL(rc_map_af9005_table_size);
EXPORT_SYMBOL(af9005_rc_decode);

MODULE_AUTHOR("Luca Olivetti <luca@ventoso.org>");
MODULE_DESCRIPTION
    ("Standard remote control decoder for Afatech 9005 DVB-T USB1.1 stick");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
