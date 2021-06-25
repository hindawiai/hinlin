<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (C) 2019 Christian Hewitt <christianshewitt@gmail.com>

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

//
// Keytable क्रम the WeTek Play 2 STB remote control
//

अटल काष्ठा rc_map_table wetek_play2[] = अणु
	अणु 0x5e5f02, KEY_POWER पूर्ण,
	अणु 0x5e5f46, KEY_SLEEP पूर्ण, // tv
	अणु 0x5e5f10, KEY_MUTE पूर्ण,

	अणु 0x5e5f22, KEY_1 पूर्ण,
	अणु 0x5e5f23, KEY_2 पूर्ण,
	अणु 0x5e5f24, KEY_3 पूर्ण,

	अणु 0x5e5f25, KEY_4 पूर्ण,
	अणु 0x5e5f26, KEY_5 पूर्ण,
	अणु 0x5e5f27, KEY_6 पूर्ण,

	अणु 0x5e5f28, KEY_7 पूर्ण,
	अणु 0x5e5f29, KEY_8 पूर्ण,
	अणु 0x5e5f30, KEY_9 पूर्ण,

	अणु 0x5e5f71, KEY_BACK पूर्ण,
	अणु 0x5e5f21, KEY_0 पूर्ण,
	अणु 0x5e5f72, KEY_CAPSLOCK पूर्ण,

	// outer ring घड़ीwide from top
	अणु 0x5e5f03, KEY_HOME पूर्ण,
	अणु 0x5e5f61, KEY_BACK पूर्ण,
	अणु 0x5e5f77, KEY_CONFIG पूर्ण, // mouse
	अणु 0x5e5f83, KEY_EPG पूर्ण,
	अणु 0x5e5f84, KEY_SCREEN पूर्ण, // square
	अणु 0x5e5f48, KEY_MENU पूर्ण,

	// inner ring
	अणु 0x5e5f50, KEY_UP पूर्ण,
	अणु 0x5e5f4b, KEY_DOWN पूर्ण,
	अणु 0x5e5f4c, KEY_LEFT पूर्ण,
	अणु 0x5e5f4d, KEY_RIGHT पूर्ण,
	अणु 0x5e5f47, KEY_OK पूर्ण,

	अणु 0x5e5f44, KEY_VOLUMEUP पूर्ण,
	अणु 0x5e5f43, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x5e5f4f, KEY_FAVORITES पूर्ण,
	अणु 0x5e5f82, KEY_SUBTITLE पूर्ण, // txt
	अणु 0x5e5f41, KEY_PAGEUP पूर्ण,
	अणु 0x5e5f42, KEY_PAGEDOWN पूर्ण,

	अणु 0x5e5f73, KEY_RED पूर्ण,
	अणु 0x5e5f74, KEY_GREEN पूर्ण,
	अणु 0x5e5f75, KEY_YELLOW पूर्ण,
	अणु 0x5e5f76, KEY_BLUE पूर्ण,

	अणु 0x5e5f67, KEY_PREVIOUSSONG पूर्ण,
	अणु 0x5e5f79, KEY_REWIND पूर्ण,
	अणु 0x5e5f80, KEY_FASTFORWARD पूर्ण,
	अणु 0x5e5f81, KEY_NEXTSONG पूर्ण,

	अणु 0x5e5f04, KEY_RECORD पूर्ण,
	अणु 0x5e5f2c, KEY_PLAYPAUSE पूर्ण,
	अणु 0x5e5f2b, KEY_STOP पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list wetek_play2_map = अणु
	.map = अणु
		.scan     = wetek_play2,
		.size     = ARRAY_SIZE(wetek_play2),
		.rc_proto = RC_PROTO_NECX,
		.name     = RC_MAP_WETEK_PLAY2,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_wetek_play2(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&wetek_play2_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_wetek_play2(व्योम)
अणु
	rc_map_unरेजिस्टर(&wetek_play2_map);
पूर्ण

module_init(init_rc_map_wetek_play2)
module_निकास(निकास_rc_map_wetek_play2)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Hewitt <christianshewitt@gmail.com");
