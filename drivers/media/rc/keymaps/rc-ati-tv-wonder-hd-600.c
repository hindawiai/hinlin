<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// ati-tv-wonder-hd-600.h - Keytable क्रम ati_tv_wonder_hd_600 Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* ATI TV Wonder HD 600 USB
   Devin Heiपंचांगueller <devin.heiपंचांगueller@gmail.com>
 */

अटल काष्ठा rc_map_table ati_tv_wonder_hd_600[] = अणु
	अणु 0x00, KEY_RECORDपूर्ण,		/* Row 1 */
	अणु 0x01, KEY_PLAYPAUSEपूर्ण,
	अणु 0x02, KEY_STOPपूर्ण,
	अणु 0x03, KEY_POWERपूर्ण,
	अणु 0x04, KEY_PREVIOUSपूर्ण,	/* Row 2 */
	अणु 0x05, KEY_REWINDपूर्ण,
	अणु 0x06, KEY_FORWARDपूर्ण,
	अणु 0x07, KEY_NEXTपूर्ण,
	अणु 0x08, KEY_EPGपूर्ण,		/* Row 3 */
	अणु 0x09, KEY_HOMEपूर्ण,
	अणु 0x0a, KEY_MENUपूर्ण,
	अणु 0x0b, KEY_CHANNELUPपूर्ण,
	अणु 0x0c, KEY_BACKपूर्ण,		/* Row 4 */
	अणु 0x0d, KEY_UPपूर्ण,
	अणु 0x0e, KEY_INFOपूर्ण,
	अणु 0x0f, KEY_CHANNELDOWNपूर्ण,
	अणु 0x10, KEY_LEFTपूर्ण,		/* Row 5 */
	अणु 0x11, KEY_SELECTपूर्ण,
	अणु 0x12, KEY_RIGHTपूर्ण,
	अणु 0x13, KEY_VOLUMEUPपूर्ण,
	अणु 0x14, KEY_LASTपूर्ण,		/* Row 6 */
	अणु 0x15, KEY_DOWNपूर्ण,
	अणु 0x16, KEY_MUTEपूर्ण,
	अणु 0x17, KEY_VOLUMEDOWNपूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list ati_tv_wonder_hd_600_map = अणु
	.map = अणु
		.scan     = ati_tv_wonder_hd_600,
		.size     = ARRAY_SIZE(ati_tv_wonder_hd_600),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_ATI_TV_WONDER_HD_600,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_ati_tv_wonder_hd_600(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&ati_tv_wonder_hd_600_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_ati_tv_wonder_hd_600(व्योम)
अणु
	rc_map_unरेजिस्टर(&ati_tv_wonder_hd_600_map);
पूर्ण

module_init(init_rc_map_ati_tv_wonder_hd_600)
module_निकास(निकास_rc_map_ati_tv_wonder_hd_600)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
