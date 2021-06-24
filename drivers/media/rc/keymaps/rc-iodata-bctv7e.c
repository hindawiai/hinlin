<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// iodata-bctv7e.h - Keytable क्रम iodata_bctv7e Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* IO-DATA BCTV7E Remote */

अटल काष्ठा rc_map_table iodata_bctv7e[] = अणु
	अणु 0x40, KEY_TV पूर्ण,
	अणु 0x20, KEY_RADIO पूर्ण,		/* FM */
	अणु 0x60, KEY_EPG पूर्ण,
	अणु 0x00, KEY_POWER पूर्ण,

	/* Keys 0 to 9 */
	अणु 0x44, KEY_NUMERIC_0 पूर्ण,		/* 10 */
	अणु 0x50, KEY_NUMERIC_1 पूर्ण,
	अणु 0x30, KEY_NUMERIC_2 पूर्ण,
	अणु 0x70, KEY_NUMERIC_3 पूर्ण,
	अणु 0x48, KEY_NUMERIC_4 पूर्ण,
	अणु 0x28, KEY_NUMERIC_5 पूर्ण,
	अणु 0x68, KEY_NUMERIC_6 पूर्ण,
	अणु 0x58, KEY_NUMERIC_7 पूर्ण,
	अणु 0x38, KEY_NUMERIC_8 पूर्ण,
	अणु 0x78, KEY_NUMERIC_9 पूर्ण,

	अणु 0x10, KEY_L पूर्ण,		/* Live */
	अणु 0x08, KEY_TIME पूर्ण,		/* Time Shअगरt */

	अणु 0x18, KEY_PLAYPAUSE पूर्ण,	/* Play */

	अणु 0x24, KEY_ENTER पूर्ण,		/* 11 */
	अणु 0x64, KEY_ESC पूर्ण,		/* 12 */
	अणु 0x04, KEY_M पूर्ण,		/* Multi */

	अणु 0x54, KEY_VIDEO पूर्ण,
	अणु 0x34, KEY_CHANNELUP पूर्ण,
	अणु 0x74, KEY_VOLUMEUP पूर्ण,
	अणु 0x14, KEY_MUTE पूर्ण,

	अणु 0x4c, KEY_VCR पूर्ण,		/* SVIDEO */
	अणु 0x2c, KEY_CHANNELDOWN पूर्ण,
	अणु 0x6c, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x0c, KEY_ZOOM पूर्ण,

	अणु 0x5c, KEY_PAUSE पूर्ण,
	अणु 0x3c, KEY_RED पूर्ण,		/* || (red) */
	अणु 0x7c, KEY_RECORD पूर्ण,		/* recording */
	अणु 0x1c, KEY_STOP पूर्ण,

	अणु 0x41, KEY_REWIND पूर्ण,		/* backward << */
	अणु 0x21, KEY_PLAY पूर्ण,
	अणु 0x61, KEY_FASTFORWARD पूर्ण,	/* क्रमward >> */
	अणु 0x01, KEY_NEXT पूर्ण,		/* skip >| */
पूर्ण;

अटल काष्ठा rc_map_list iodata_bctv7e_map = अणु
	.map = अणु
		.scan     = iodata_bctv7e,
		.size     = ARRAY_SIZE(iodata_bctv7e),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_IODATA_BCTV7E,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_iodata_bctv7e(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&iodata_bctv7e_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_iodata_bctv7e(व्योम)
अणु
	rc_map_unरेजिस्टर(&iodata_bctv7e_map);
पूर्ण

module_init(init_rc_map_iodata_bctv7e)
module_निकास(निकास_rc_map_iodata_bctv7e)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
