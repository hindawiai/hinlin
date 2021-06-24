<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// pinnacle-color.h - Keytable क्रम pinnacle_color Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table pinnacle_color[] = अणु
	अणु 0x59, KEY_MUTE पूर्ण,
	अणु 0x4a, KEY_POWER पूर्ण,

	अणु 0x18, KEY_TEXT पूर्ण,
	अणु 0x26, KEY_TV पूर्ण,
	अणु 0x3d, KEY_PRINT पूर्ण,

	अणु 0x48, KEY_RED पूर्ण,
	अणु 0x04, KEY_GREEN पूर्ण,
	अणु 0x11, KEY_YELLOW पूर्ण,
	अणु 0x00, KEY_BLUE पूर्ण,

	अणु 0x2d, KEY_VOLUMEUP पूर्ण,
	अणु 0x1e, KEY_VOLUMEDOWN पूर्ण,

	अणु 0x49, KEY_MENU पूर्ण,

	अणु 0x16, KEY_CHANNELUP पूर्ण,
	अणु 0x17, KEY_CHANNELDOWN पूर्ण,

	अणु 0x20, KEY_UP पूर्ण,
	अणु 0x21, KEY_DOWN पूर्ण,
	अणु 0x22, KEY_LEFT पूर्ण,
	अणु 0x23, KEY_RIGHT पूर्ण,
	अणु 0x0d, KEY_SELECT पूर्ण,

	अणु 0x08, KEY_BACK पूर्ण,
	अणु 0x07, KEY_REFRESH पूर्ण,

	अणु 0x2f, KEY_ZOOM पूर्ण,
	अणु 0x29, KEY_RECORD पूर्ण,

	अणु 0x4b, KEY_PAUSE पूर्ण,
	अणु 0x4d, KEY_REWIND पूर्ण,
	अणु 0x2e, KEY_PLAY पूर्ण,
	अणु 0x4e, KEY_FORWARD पूर्ण,
	अणु 0x53, KEY_PREVIOUS पूर्ण,
	अणु 0x4c, KEY_STOP पूर्ण,
	अणु 0x54, KEY_NEXT पूर्ण,

	अणु 0x69, KEY_NUMERIC_0 पूर्ण,
	अणु 0x6a, KEY_NUMERIC_1 पूर्ण,
	अणु 0x6b, KEY_NUMERIC_2 पूर्ण,
	अणु 0x6c, KEY_NUMERIC_3 पूर्ण,
	अणु 0x6d, KEY_NUMERIC_4 पूर्ण,
	अणु 0x6e, KEY_NUMERIC_5 पूर्ण,
	अणु 0x6f, KEY_NUMERIC_6 पूर्ण,
	अणु 0x70, KEY_NUMERIC_7 पूर्ण,
	अणु 0x71, KEY_NUMERIC_8 पूर्ण,
	अणु 0x72, KEY_NUMERIC_9 पूर्ण,

	अणु 0x74, KEY_CHANNEL पूर्ण,
	अणु 0x0a, KEY_BACKSPACE पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list pinnacle_color_map = अणु
	.map = अणु
		.scan     = pinnacle_color,
		.size     = ARRAY_SIZE(pinnacle_color),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_PINNACLE_COLOR,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_pinnacle_color(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&pinnacle_color_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_pinnacle_color(व्योम)
अणु
	rc_map_unरेजिस्टर(&pinnacle_color_map);
पूर्ण

module_init(init_rc_map_pinnacle_color)
module_निकास(निकास_rc_map_pinnacle_color)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
