<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// kworld-315u.h - Keytable क्रम kworld_315u Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Kworld 315U
 */

अटल काष्ठा rc_map_table kworld_315u[] = अणु
	अणु 0x6143, KEY_POWER पूर्ण,
	अणु 0x6101, KEY_VIDEO पूर्ण,		/* source */
	अणु 0x610b, KEY_ZOOM पूर्ण,
	अणु 0x6103, KEY_POWER2 पूर्ण,		/* shutकरोwn */

	अणु 0x6104, KEY_NUMERIC_1 पूर्ण,
	अणु 0x6108, KEY_NUMERIC_2 पूर्ण,
	अणु 0x6102, KEY_NUMERIC_3 पूर्ण,
	अणु 0x6109, KEY_CHANNELUP पूर्ण,

	अणु 0x610f, KEY_NUMERIC_4 पूर्ण,
	अणु 0x6105, KEY_NUMERIC_5 पूर्ण,
	अणु 0x6106, KEY_NUMERIC_6 पूर्ण,
	अणु 0x6107, KEY_CHANNELDOWN पूर्ण,

	अणु 0x610c, KEY_NUMERIC_7 पूर्ण,
	अणु 0x610d, KEY_NUMERIC_8 पूर्ण,
	अणु 0x610a, KEY_NUMERIC_9 पूर्ण,
	अणु 0x610e, KEY_VOLUMEUP पूर्ण,

	अणु 0x6110, KEY_LAST पूर्ण,
	अणु 0x6111, KEY_NUMERIC_0 पूर्ण,
	अणु 0x6112, KEY_ENTER पूर्ण,
	अणु 0x6113, KEY_VOLUMEDOWN पूर्ण,

	अणु 0x6114, KEY_RECORD पूर्ण,
	अणु 0x6115, KEY_STOP पूर्ण,
	अणु 0x6116, KEY_PLAY पूर्ण,
	अणु 0x6117, KEY_MUTE पूर्ण,

	अणु 0x6118, KEY_UP पूर्ण,
	अणु 0x6119, KEY_DOWN पूर्ण,
	अणु 0x611a, KEY_LEFT पूर्ण,
	अणु 0x611b, KEY_RIGHT पूर्ण,

	अणु 0x611c, KEY_RED पूर्ण,
	अणु 0x611d, KEY_GREEN पूर्ण,
	अणु 0x611e, KEY_YELLOW पूर्ण,
	अणु 0x611f, KEY_BLUE पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list kworld_315u_map = अणु
	.map = अणु
		.scan     = kworld_315u,
		.size     = ARRAY_SIZE(kworld_315u),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_KWORLD_315U,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_kworld_315u(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&kworld_315u_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_kworld_315u(व्योम)
अणु
	rc_map_unरेजिस्टर(&kworld_315u_map);
पूर्ण

module_init(init_rc_map_kworld_315u)
module_निकास(निकास_rc_map_kworld_315u)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
