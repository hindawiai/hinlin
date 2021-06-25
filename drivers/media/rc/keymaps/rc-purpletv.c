<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// purpletv.h - Keytable क्रम purpletv Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table purpletv[] = अणु
	अणु 0x03, KEY_POWER पूर्ण,
	अणु 0x6f, KEY_MUTE पूर्ण,
	अणु 0x10, KEY_BACKSPACE पूर्ण,	/* Recall */

	अणु 0x11, KEY_NUMERIC_0 पूर्ण,
	अणु 0x04, KEY_NUMERIC_1 पूर्ण,
	अणु 0x05, KEY_NUMERIC_2 पूर्ण,
	अणु 0x06, KEY_NUMERIC_3 पूर्ण,
	अणु 0x08, KEY_NUMERIC_4 पूर्ण,
	अणु 0x09, KEY_NUMERIC_5 पूर्ण,
	अणु 0x0a, KEY_NUMERIC_6 पूर्ण,
	अणु 0x0c, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0d, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0e, KEY_NUMERIC_9 पूर्ण,
	अणु 0x12, KEY_DOT पूर्ण,	/* 100+ */

	अणु 0x07, KEY_VOLUMEUP पूर्ण,
	अणु 0x0b, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x1a, KEY_KPPLUS पूर्ण,
	अणु 0x18, KEY_KPMINUS पूर्ण,
	अणु 0x15, KEY_UP पूर्ण,
	अणु 0x1d, KEY_DOWN पूर्ण,
	अणु 0x0f, KEY_CHANNELUP पूर्ण,
	अणु 0x13, KEY_CHANNELDOWN पूर्ण,
	अणु 0x48, KEY_ZOOM पूर्ण,

	अणु 0x1b, KEY_VIDEO पूर्ण,	/* Video source */
	अणु 0x1f, KEY_CAMERA पूर्ण,	/* Snapshot */
	अणु 0x49, KEY_LANGUAGE पूर्ण,	/* MTS Select */
	अणु 0x19, KEY_SEARCH पूर्ण,	/* Auto Scan */

	अणु 0x4b, KEY_RECORD पूर्ण,
	अणु 0x46, KEY_PLAY पूर्ण,
	अणु 0x45, KEY_PAUSE पूर्ण,	/* Pause */
	अणु 0x44, KEY_STOP पूर्ण,
	अणु 0x43, KEY_TIME पूर्ण,	/* Time Shअगरt */
	अणु 0x17, KEY_CHANNEL पूर्ण,	/* SURF CH */
	अणु 0x40, KEY_FORWARD पूर्ण,	/* Forward ? */
	अणु 0x42, KEY_REWIND पूर्ण,	/* Backward ? */

पूर्ण;

अटल काष्ठा rc_map_list purpletv_map = अणु
	.map = अणु
		.scan     = purpletv,
		.size     = ARRAY_SIZE(purpletv),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_PURPLETV,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_purpletv(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&purpletv_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_purpletv(व्योम)
अणु
	rc_map_unरेजिस्टर(&purpletv_map);
पूर्ण

module_init(init_rc_map_purpletv)
module_निकास(निकास_rc_map_purpletv)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
