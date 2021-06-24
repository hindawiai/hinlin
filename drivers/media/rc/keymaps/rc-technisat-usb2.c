<शैली गुरु>
/* rc-technisat-usb2.c - Keytable क्रम SkyStar HD USB
 *
 * Copyright (C) 2010 Patrick Boettcher,
 *                    Kernel Lअसल Inc. PO Box 745, St James, NY 11780
 *
 * Development was sponsored by Technisat Digital UK Limited, whose
 * रेजिस्टरed office is Witan Gate House 500 - 600 Witan Gate West,
 * Milton Keynes, MK9 1SH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 *
 * THIS PROGRAM IS PROVIDED "AS IS" AND BOTH THE COPYRIGHT HOLDER AND
 * TECHNISAT DIGITAL UK LTD DISCLAIM ALL WARRANTIES WITH REGARD TO
 * THIS PROGRAM INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  NEITHER THE COPYRIGHT HOLDER
 * NOR TECHNISAT DIGITAL UK LIMITED SHALL BE LIABLE FOR ANY SPECIAL,
 * सूचीECT, INसूचीECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR
 * IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS PROGRAM. See the
 * GNU General Public License क्रम more details.
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table technisat_usb2[] = अणु
	अणु0x0a0c, KEY_POWERपूर्ण,
	अणु0x0a01, KEY_NUMERIC_1पूर्ण,
	अणु0x0a02, KEY_NUMERIC_2पूर्ण,
	अणु0x0a03, KEY_NUMERIC_3पूर्ण,
	अणु0x0a0d, KEY_MUTEपूर्ण,
	अणु0x0a04, KEY_NUMERIC_4पूर्ण,
	अणु0x0a05, KEY_NUMERIC_5पूर्ण,
	अणु0x0a06, KEY_NUMERIC_6पूर्ण,
	अणु0x0a38, KEY_VIDEOपूर्ण, /* EXT */
	अणु0x0a07, KEY_NUMERIC_7पूर्ण,
	अणु0x0a08, KEY_NUMERIC_8पूर्ण,
	अणु0x0a09, KEY_NUMERIC_9पूर्ण,
	अणु0x0a00, KEY_NUMERIC_0पूर्ण,
	अणु0x0a4f, KEY_INFOपूर्ण,
	अणु0x0a20, KEY_CHANNELUPपूर्ण,
	अणु0x0a52, KEY_MENUपूर्ण,
	अणु0x0a11, KEY_VOLUMEUPपूर्ण,
	अणु0x0a57, KEY_OKपूर्ण,
	अणु0x0a10, KEY_VOLUMEDOWNपूर्ण,
	अणु0x0a2f, KEY_EPGपूर्ण,
	अणु0x0a21, KEY_CHANNELDOWNपूर्ण,
	अणु0x0a22, KEY_REFRESHपूर्ण,
	अणु0x0a3c, KEY_TEXTपूर्ण,
	अणु0x0a76, KEY_ENTERपूर्ण, /* HOOK */
	अणु0x0a0f, KEY_HELPपूर्ण,
	अणु0x0a6b, KEY_REDपूर्ण,
	अणु0x0a6c, KEY_GREENपूर्ण,
	अणु0x0a6d, KEY_YELLOWपूर्ण,
	अणु0x0a6e, KEY_BLUEपूर्ण,
	अणु0x0a29, KEY_STOPपूर्ण,
	अणु0x0a23, KEY_LANGUAGEपूर्ण,
	अणु0x0a53, KEY_TVपूर्ण,
	अणु0x0a0a, KEY_PROGRAMपूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list technisat_usb2_map = अणु
	.map = अणु
		.scan     = technisat_usb2,
		.size     = ARRAY_SIZE(technisat_usb2),
		.rc_proto = RC_PROTO_RC5,
		.name     = RC_MAP_TECHNISAT_USB2,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&technisat_usb2_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map(व्योम)
अणु
	rc_map_unरेजिस्टर(&technisat_usb2_map);
पूर्ण

module_init(init_rc_map)
module_निकास(निकास_rc_map)

MODULE_AUTHOR("Patrick Boettcher <pboettcher@kernellabs.com>");
MODULE_LICENSE("GPL");
