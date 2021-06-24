<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (C) 2019 Christian Hewitt <christianshewitt@gmail.com>

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

//
// Keytable क्रम the X96-max STB remote control
//

अटल काष्ठा rc_map_table x96max[] = अणु
	अणु 0x140, KEY_POWER पूर्ण,

	// ** TV CONTROL **
	// SET
	// AV/TV
	// POWER
	// VOLUME UP
	// VOLUME DOWN

	अणु 0x118, KEY_VOLUMEUP पूर्ण,
	अणु 0x110, KEY_VOLUMEDOWN पूर्ण,

	अणु 0x143, KEY_MUTE पूर्ण, // config

	अणु 0x100, KEY_EPG पूर्ण, // mouse
	अणु 0x119, KEY_BACK पूर्ण,

	अणु 0x116, KEY_UP पूर्ण,
	अणु 0x151, KEY_LEFT पूर्ण,
	अणु 0x150, KEY_RIGHT पूर्ण,
	अणु 0x11a, KEY_DOWN पूर्ण,
	अणु 0x113, KEY_OK पूर्ण,

	अणु 0x111, KEY_HOME पूर्ण,
	अणु 0x14c, KEY_CONTEXT_MENU पूर्ण,

	अणु 0x159, KEY_PREVIOUS पूर्ण,
	अणु 0x15a, KEY_PLAYPAUSE पूर्ण,
	अणु 0x158, KEY_NEXT पूर्ण,

	अणु 0x147, KEY_MENU पूर्ण, // @ key
	अणु 0x101, KEY_NUMERIC_0 पूर्ण,
	अणु 0x142, KEY_BACKSPACE पूर्ण,

	अणु 0x14e, KEY_NUMERIC_1 पूर्ण,
	अणु 0x10d, KEY_NUMERIC_2 पूर्ण,
	अणु 0x10c, KEY_NUMERIC_3 पूर्ण,

	अणु 0x14a, KEY_NUMERIC_4 पूर्ण,
	अणु 0x109, KEY_NUMERIC_5 पूर्ण,
	अणु 0x108, KEY_NUMERIC_6 पूर्ण,

	अणु 0x146, KEY_NUMERIC_7 पूर्ण,
	अणु 0x105, KEY_NUMERIC_8 पूर्ण,
	अणु 0x104, KEY_NUMERIC_9 पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list x96max_map = अणु
	.map = अणु
		.scan     = x96max,
		.size     = ARRAY_SIZE(x96max),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_X96MAX,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_x96max(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&x96max_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_x96max(व्योम)
अणु
	rc_map_unरेजिस्टर(&x96max_map);
पूर्ण

module_init(init_rc_map_x96max)
module_निकास(निकास_rc_map_x96max)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Hewitt <christianshewitt@gmail.com");
