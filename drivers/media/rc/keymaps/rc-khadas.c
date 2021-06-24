<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (C) 2019 Christian Hewitt <christianshewitt@gmail.com>

/*
 * Keytable क्रम the Khadas VIM/EDGE SBC remote control
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table khadas[] = अणु
	अणु 0x14, KEY_POWER पूर्ण,

	अणु 0x03, KEY_UP पूर्ण,
	अणु 0x02, KEY_DOWN पूर्ण,
	अणु 0x0e, KEY_LEFT पूर्ण,
	अणु 0x1a, KEY_RIGHT पूर्ण,
	अणु 0x07, KEY_OK पूर्ण,

	अणु 0x01, KEY_BACK पूर्ण,
	अणु 0x5b, KEY_MUTE पूर्ण, // mouse
	अणु 0x13, KEY_MENU पूर्ण,

	अणु 0x58, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x0b, KEY_VOLUMEUP पूर्ण,

	अणु 0x48, KEY_HOME पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list khadas_map = अणु
	.map = अणु
		.scan     = khadas,
		.size     = ARRAY_SIZE(khadas),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_KHADAS,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_khadas(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&khadas_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_khadas(व्योम)
अणु
	rc_map_unरेजिस्टर(&khadas_map);
पूर्ण

module_init(init_rc_map_khadas)
module_निकास(निकास_rc_map_khadas)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Hewitt <christianshewitt@gmail.com>");
