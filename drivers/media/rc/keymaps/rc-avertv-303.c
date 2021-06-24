<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// avertv-303.h - Keytable क्रम avertv_303 Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* AVERTV STUDIO 303 Remote */

अटल काष्ठा rc_map_table avertv_303[] = अणु
	अणु 0x2a, KEY_NUMERIC_1 पूर्ण,
	अणु 0x32, KEY_NUMERIC_2 पूर्ण,
	अणु 0x3a, KEY_NUMERIC_3 पूर्ण,
	अणु 0x4a, KEY_NUMERIC_4 पूर्ण,
	अणु 0x52, KEY_NUMERIC_5 पूर्ण,
	अणु 0x5a, KEY_NUMERIC_6 पूर्ण,
	अणु 0x6a, KEY_NUMERIC_7 पूर्ण,
	अणु 0x72, KEY_NUMERIC_8 पूर्ण,
	अणु 0x7a, KEY_NUMERIC_9 पूर्ण,
	अणु 0x0e, KEY_NUMERIC_0 पूर्ण,

	अणु 0x02, KEY_POWER पूर्ण,
	अणु 0x22, KEY_VIDEO पूर्ण,
	अणु 0x42, KEY_AUDIO पूर्ण,
	अणु 0x62, KEY_ZOOM पूर्ण,
	अणु 0x0a, KEY_TV पूर्ण,
	अणु 0x12, KEY_CD पूर्ण,
	अणु 0x1a, KEY_TEXT पूर्ण,

	अणु 0x16, KEY_SUBTITLE पूर्ण,
	अणु 0x1e, KEY_REWIND पूर्ण,
	अणु 0x06, KEY_PRINT पूर्ण,

	अणु 0x2e, KEY_SEARCH पूर्ण,
	अणु 0x36, KEY_SLEEP पूर्ण,
	अणु 0x3e, KEY_SHUFFLE पूर्ण,
	अणु 0x26, KEY_MUTE पूर्ण,

	अणु 0x4e, KEY_RECORD पूर्ण,
	अणु 0x56, KEY_PAUSE पूर्ण,
	अणु 0x5e, KEY_STOP पूर्ण,
	अणु 0x46, KEY_PLAY पूर्ण,

	अणु 0x6e, KEY_RED पूर्ण,
	अणु 0x0b, KEY_GREEN पूर्ण,
	अणु 0x66, KEY_YELLOW पूर्ण,
	अणु 0x03, KEY_BLUE पूर्ण,

	अणु 0x76, KEY_LEFT पूर्ण,
	अणु 0x7e, KEY_RIGHT पूर्ण,
	अणु 0x13, KEY_DOWN पूर्ण,
	अणु 0x1b, KEY_UP पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list avertv_303_map = अणु
	.map = अणु
		.scan     = avertv_303,
		.size     = ARRAY_SIZE(avertv_303),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_AVERTV_303,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_avertv_303(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&avertv_303_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_avertv_303(व्योम)
अणु
	rc_map_unरेजिस्टर(&avertv_303_map);
पूर्ण

module_init(init_rc_map_avertv_303)
module_निकास(निकास_rc_map_avertv_303)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
