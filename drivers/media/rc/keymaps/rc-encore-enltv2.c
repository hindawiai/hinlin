<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// encore-enltv2.h - Keytable क्रम encore_enltv2 Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Encore ENLTV2-FM  - silver plastic - "Wand Media" written at the botton
    Mauro Carvalho Chehab <mchehab@kernel.org> */

अटल काष्ठा rc_map_table encore_enltv2[] = अणु
	अणु 0x4c, KEY_POWER2 पूर्ण,
	अणु 0x4a, KEY_TUNER पूर्ण,
	अणु 0x40, KEY_NUMERIC_1 पूर्ण,
	अणु 0x60, KEY_NUMERIC_2 पूर्ण,
	अणु 0x50, KEY_NUMERIC_3 पूर्ण,
	अणु 0x70, KEY_NUMERIC_4 पूर्ण,
	अणु 0x48, KEY_NUMERIC_5 पूर्ण,
	अणु 0x68, KEY_NUMERIC_6 पूर्ण,
	अणु 0x58, KEY_NUMERIC_7 पूर्ण,
	अणु 0x78, KEY_NUMERIC_8 पूर्ण,
	अणु 0x44, KEY_NUMERIC_9 पूर्ण,
	अणु 0x54, KEY_NUMERIC_0 पूर्ण,

	अणु 0x64, KEY_LAST पूर्ण,		/* +100 */
	अणु 0x4e, KEY_AGAIN पूर्ण,		/* Recall */

	अणु 0x6c, KEY_VIDEO पूर्ण,		/* Video Source */
	अणु 0x5e, KEY_MENU पूर्ण,
	अणु 0x56, KEY_SCREEN पूर्ण,
	अणु 0x7a, KEY_SETUP पूर्ण,

	अणु 0x46, KEY_MUTE पूर्ण,
	अणु 0x5c, KEY_MODE पूर्ण,		/* Stereo */
	अणु 0x74, KEY_INFO पूर्ण,
	अणु 0x7c, KEY_CLEAR पूर्ण,

	अणु 0x55, KEY_UP पूर्ण,
	अणु 0x49, KEY_DOWN पूर्ण,
	अणु 0x7e, KEY_LEFT पूर्ण,
	अणु 0x59, KEY_RIGHT पूर्ण,
	अणु 0x6a, KEY_ENTER पूर्ण,

	अणु 0x42, KEY_VOLUMEUP पूर्ण,
	अणु 0x62, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x52, KEY_CHANNELUP पूर्ण,
	अणु 0x72, KEY_CHANNELDOWN पूर्ण,

	अणु 0x41, KEY_RECORD पूर्ण,
	अणु 0x51, KEY_CAMERA पूर्ण,		/* Snapshot */
	अणु 0x75, KEY_TIME पूर्ण,		/* Timeshअगरt */
	अणु 0x71, KEY_TV2 पूर्ण,		/* PIP */

	अणु 0x45, KEY_REWIND पूर्ण,
	अणु 0x6f, KEY_PAUSE पूर्ण,
	अणु 0x7d, KEY_FORWARD पूर्ण,
	अणु 0x79, KEY_STOP पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list encore_enltv2_map = अणु
	.map = अणु
		.scan     = encore_enltv2,
		.size     = ARRAY_SIZE(encore_enltv2),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_ENCORE_ENLTV2,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_encore_enltv2(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&encore_enltv2_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_encore_enltv2(व्योम)
अणु
	rc_map_unरेजिस्टर(&encore_enltv2_map);
पूर्ण

module_init(init_rc_map_encore_enltv2)
module_निकास(निकास_rc_map_encore_enltv2)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
