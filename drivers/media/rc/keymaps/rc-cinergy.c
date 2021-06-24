<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// cinergy.h - Keytable क्रम cinergy Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table cinergy[] = अणु
	अणु 0x00, KEY_NUMERIC_0 पूर्ण,
	अणु 0x01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x03, KEY_NUMERIC_3 पूर्ण,
	अणु 0x04, KEY_NUMERIC_4 पूर्ण,
	अणु 0x05, KEY_NUMERIC_5 पूर्ण,
	अणु 0x06, KEY_NUMERIC_6 पूर्ण,
	अणु 0x07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x09, KEY_NUMERIC_9 पूर्ण,

	अणु 0x0a, KEY_POWER पूर्ण,
	अणु 0x0b, KEY_MEDIA पूर्ण,		/* app */
	अणु 0x0c, KEY_ZOOM पूर्ण,		/* zoom/fullscreen */
	अणु 0x0d, KEY_CHANNELUP पूर्ण,	/* channel */
	अणु 0x0e, KEY_CHANNELDOWN पूर्ण,	/* channel- */
	अणु 0x0f, KEY_VOLUMEUP पूर्ण,
	अणु 0x10, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x11, KEY_TUNER पूर्ण,		/* AV */
	अणु 0x12, KEY_NUMLOCK पूर्ण,		/* -/-- */
	अणु 0x13, KEY_AUDIO पूर्ण,		/* audio */
	अणु 0x14, KEY_MUTE पूर्ण,
	अणु 0x15, KEY_UP पूर्ण,
	अणु 0x16, KEY_DOWN पूर्ण,
	अणु 0x17, KEY_LEFT पूर्ण,
	अणु 0x18, KEY_RIGHT पूर्ण,
	अणु 0x19, BTN_LEFT, पूर्ण,
	अणु 0x1a, BTN_RIGHT, पूर्ण,
	अणु 0x1b, KEY_WWW पूर्ण,		/* text */
	अणु 0x1c, KEY_REWIND पूर्ण,
	अणु 0x1d, KEY_FORWARD पूर्ण,
	अणु 0x1e, KEY_RECORD पूर्ण,
	अणु 0x1f, KEY_PLAY पूर्ण,
	अणु 0x20, KEY_PREVIOUSSONG पूर्ण,
	अणु 0x21, KEY_NEXTSONG पूर्ण,
	अणु 0x22, KEY_PAUSE पूर्ण,
	अणु 0x23, KEY_STOP पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list cinergy_map = अणु
	.map = अणु
		.scan     = cinergy,
		.size     = ARRAY_SIZE(cinergy),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_CINERGY,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_cinergy(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&cinergy_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_cinergy(व्योम)
अणु
	rc_map_unरेजिस्टर(&cinergy_map);
पूर्ण

module_init(init_rc_map_cinergy)
module_निकास(निकास_rc_map_cinergy)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
