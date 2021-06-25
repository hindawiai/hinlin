<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// winfast-usbii-deluxe.h - Keytable क्रम winfast_usbii_deluxe Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Leadtek Winfast TV USB II Deluxe remote
   Magnus Alm <magnus.alm@gmail.com>
 */

अटल काष्ठा rc_map_table winfast_usbii_deluxe[] = अणु
	अणु 0x62, KEY_NUMERIC_0पूर्ण,
	अणु 0x75, KEY_NUMERIC_1पूर्ण,
	अणु 0x76, KEY_NUMERIC_2पूर्ण,
	अणु 0x77, KEY_NUMERIC_3पूर्ण,
	अणु 0x79, KEY_NUMERIC_4पूर्ण,
	अणु 0x7a, KEY_NUMERIC_5पूर्ण,
	अणु 0x7b, KEY_NUMERIC_6पूर्ण,
	अणु 0x7d, KEY_NUMERIC_7पूर्ण,
	अणु 0x7e, KEY_NUMERIC_8पूर्ण,
	अणु 0x7f, KEY_NUMERIC_9पूर्ण,

	अणु 0x38, KEY_CAMERAपूर्ण,		/* SNAPSHOT */
	अणु 0x37, KEY_RECORDपूर्ण,		/* RECORD */
	अणु 0x35, KEY_TIMEपूर्ण,		/* TIMESHIFT */

	अणु 0x74, KEY_VOLUMEUPपूर्ण,		/* VOLUMEUP */
	अणु 0x78, KEY_VOLUMEDOWNपूर्ण,	/* VOLUMEDOWN */
	अणु 0x64, KEY_MUTEपूर्ण,		/* MUTE */

	अणु 0x21, KEY_CHANNELपूर्ण,		/* SURF */
	अणु 0x7c, KEY_CHANNELUPपूर्ण,		/* CHANNELUP */
	अणु 0x60, KEY_CHANNELDOWNपूर्ण,	/* CHANNELDOWN */
	अणु 0x61, KEY_LASTपूर्ण,		/* LAST CHANNEL (RECALL) */

	अणु 0x72, KEY_VIDEOपूर्ण,		/* INPUT MODES (TV/FM) */

	अणु 0x70, KEY_POWER2पूर्ण,		/* TV ON/OFF */

	अणु 0x39, KEY_CYCLEWINDOWSपूर्ण,	/* MINIMIZE (BOSS) */
	अणु 0x3a, KEY_NEWपूर्ण,		/* PIP */
	अणु 0x73, KEY_ZOOMपूर्ण,		/* FULLSECREEN */

	अणु 0x66, KEY_INFOपूर्ण,		/* OSD (DISPLAY) */

	अणु 0x31, KEY_DOTपूर्ण,		/* '.' */
	अणु 0x63, KEY_ENTERपूर्ण,		/* ENTER */

पूर्ण;

अटल काष्ठा rc_map_list winfast_usbii_deluxe_map = अणु
	.map = अणु
		.scan     = winfast_usbii_deluxe,
		.size     = ARRAY_SIZE(winfast_usbii_deluxe),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_WINFAST_USBII_DELUXE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_winfast_usbii_deluxe(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&winfast_usbii_deluxe_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_winfast_usbii_deluxe(व्योम)
अणु
	rc_map_unरेजिस्टर(&winfast_usbii_deluxe_map);
पूर्ण

module_init(init_rc_map_winfast_usbii_deluxe)
module_निकास(निकास_rc_map_winfast_usbii_deluxe)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
