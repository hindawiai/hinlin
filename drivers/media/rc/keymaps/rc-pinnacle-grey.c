<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// pinnacle-grey.h - Keytable क्रम pinnacle_grey Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table pinnacle_grey[] = अणु
	अणु 0x3a, KEY_NUMERIC_0 पूर्ण,
	अणु 0x31, KEY_NUMERIC_1 पूर्ण,
	अणु 0x32, KEY_NUMERIC_2 पूर्ण,
	अणु 0x33, KEY_NUMERIC_3 पूर्ण,
	अणु 0x34, KEY_NUMERIC_4 पूर्ण,
	अणु 0x35, KEY_NUMERIC_5 पूर्ण,
	अणु 0x36, KEY_NUMERIC_6 पूर्ण,
	अणु 0x37, KEY_NUMERIC_7 पूर्ण,
	अणु 0x38, KEY_NUMERIC_8 पूर्ण,
	अणु 0x39, KEY_NUMERIC_9 पूर्ण,

	अणु 0x2f, KEY_POWER पूर्ण,

	अणु 0x2e, KEY_P पूर्ण,
	अणु 0x1f, KEY_L पूर्ण,
	अणु 0x2b, KEY_I पूर्ण,

	अणु 0x2d, KEY_SCREEN पूर्ण,
	अणु 0x1e, KEY_ZOOM पूर्ण,
	अणु 0x1b, KEY_VOLUMEUP पूर्ण,
	अणु 0x0f, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x17, KEY_CHANNELUP पूर्ण,
	अणु 0x1c, KEY_CHANNELDOWN पूर्ण,
	अणु 0x25, KEY_INFO पूर्ण,

	अणु 0x3c, KEY_MUTE पूर्ण,

	अणु 0x3d, KEY_LEFT पूर्ण,
	अणु 0x3b, KEY_RIGHT पूर्ण,

	अणु 0x3f, KEY_UP पूर्ण,
	अणु 0x3e, KEY_DOWN पूर्ण,
	अणु 0x1a, KEY_ENTER पूर्ण,

	अणु 0x1d, KEY_MENU पूर्ण,
	अणु 0x19, KEY_AGAIN पूर्ण,
	अणु 0x16, KEY_PREVIOUSSONG पूर्ण,
	अणु 0x13, KEY_NEXTSONG पूर्ण,
	अणु 0x15, KEY_PAUSE पूर्ण,
	अणु 0x0e, KEY_REWIND पूर्ण,
	अणु 0x0d, KEY_PLAY पूर्ण,
	अणु 0x0b, KEY_STOP पूर्ण,
	अणु 0x07, KEY_FORWARD पूर्ण,
	अणु 0x27, KEY_RECORD पूर्ण,
	अणु 0x26, KEY_TUNER पूर्ण,
	अणु 0x29, KEY_TEXT पूर्ण,
	अणु 0x2a, KEY_MEDIA पूर्ण,
	अणु 0x18, KEY_EPG पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list pinnacle_grey_map = अणु
	.map = अणु
		.scan     = pinnacle_grey,
		.size     = ARRAY_SIZE(pinnacle_grey),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_PINNACLE_GREY,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_pinnacle_grey(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&pinnacle_grey_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_pinnacle_grey(व्योम)
अणु
	rc_map_unरेजिस्टर(&pinnacle_grey_map);
पूर्ण

module_init(init_rc_map_pinnacle_grey)
module_निकास(निकास_rc_map_pinnacle_grey)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
