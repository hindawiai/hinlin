<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// gotview7135.h - Keytable क्रम gotview7135 Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Mike Baikov <mike@baikov.com> */

अटल काष्ठा rc_map_table gotview7135[] = अणु

	अणु 0x11, KEY_POWER पूर्ण,
	अणु 0x35, KEY_TV पूर्ण,
	अणु 0x1b, KEY_NUMERIC_0 पूर्ण,
	अणु 0x29, KEY_NUMERIC_1 पूर्ण,
	अणु 0x19, KEY_NUMERIC_2 पूर्ण,
	अणु 0x39, KEY_NUMERIC_3 पूर्ण,
	अणु 0x1f, KEY_NUMERIC_4 पूर्ण,
	अणु 0x2c, KEY_NUMERIC_5 पूर्ण,
	अणु 0x21, KEY_NUMERIC_6 पूर्ण,
	अणु 0x24, KEY_NUMERIC_7 पूर्ण,
	अणु 0x18, KEY_NUMERIC_8 पूर्ण,
	अणु 0x2b, KEY_NUMERIC_9 पूर्ण,
	अणु 0x3b, KEY_AGAIN पूर्ण,	/* LOOP */
	अणु 0x06, KEY_AUDIO पूर्ण,
	अणु 0x31, KEY_PRINT पूर्ण,	/* PREVIEW */
	अणु 0x3e, KEY_VIDEO पूर्ण,
	अणु 0x10, KEY_CHANNELUP पूर्ण,
	अणु 0x20, KEY_CHANNELDOWN पूर्ण,
	अणु 0x0c, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x28, KEY_VOLUMEUP पूर्ण,
	अणु 0x08, KEY_MUTE पूर्ण,
	अणु 0x26, KEY_SEARCH पूर्ण,	/* SCAN */
	अणु 0x3f, KEY_CAMERA पूर्ण,	/* SNAPSHOT */
	अणु 0x12, KEY_RECORD पूर्ण,
	अणु 0x32, KEY_STOP पूर्ण,
	अणु 0x3c, KEY_PLAY पूर्ण,
	अणु 0x1d, KEY_REWIND पूर्ण,
	अणु 0x2d, KEY_PAUSE पूर्ण,
	अणु 0x0d, KEY_FORWARD पूर्ण,
	अणु 0x05, KEY_ZOOM पूर्ण,	/*FULL*/

	अणु 0x2a, KEY_F21 पूर्ण,	/* LIVE TIMESHIFT */
	अणु 0x0e, KEY_F22 पूर्ण,	/* MIN TIMESHIFT */
	अणु 0x1e, KEY_TIME पूर्ण,	/* TIMESHIFT */
	अणु 0x38, KEY_F24 पूर्ण,	/* NORMAL TIMESHIFT */
पूर्ण;

अटल काष्ठा rc_map_list gotview7135_map = अणु
	.map = अणु
		.scan     = gotview7135,
		.size     = ARRAY_SIZE(gotview7135),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_GOTVIEW7135,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_gotview7135(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&gotview7135_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_gotview7135(व्योम)
अणु
	rc_map_unरेजिस्टर(&gotview7135_map);
पूर्ण

module_init(init_rc_map_gotview7135)
module_निकास(निकास_rc_map_gotview7135)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
