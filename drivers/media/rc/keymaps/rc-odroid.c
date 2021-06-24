<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (C) 2019 Christian Hewitt <christianshewitt@gmail.com>

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

//
// Keytable क्रम the HardKernel ODROID remote control
//

अटल काष्ठा rc_map_table odroid[] = अणु
	अणु 0xb2dc, KEY_POWER पूर्ण,

	अणु 0xb288, KEY_MUTE पूर्ण,
	अणु 0xb282, KEY_HOME पूर्ण,

	अणु 0xb2ca, KEY_UP पूर्ण,
	अणु 0xb299, KEY_LEFT पूर्ण,
	अणु 0xb2ce, KEY_OK पूर्ण,
	अणु 0xb2c1, KEY_RIGHT पूर्ण,
	अणु 0xb2d2, KEY_DOWN पूर्ण,

	अणु 0xb2c5, KEY_MENU पूर्ण,
	अणु 0xb29a, KEY_BACK पूर्ण,

	अणु 0xb281, KEY_VOLUMEDOWN पूर्ण,
	अणु 0xb280, KEY_VOLUMEUP पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list odroid_map = अणु
	.map = अणु
		.scan     = odroid,
		.size     = ARRAY_SIZE(odroid),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_ODROID,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_odroid(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&odroid_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_odroid(व्योम)
अणु
	rc_map_unरेजिस्टर(&odroid_map);
पूर्ण

module_init(init_rc_map_odroid)
module_निकास(निकास_rc_map_odroid)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Hewitt <christianshewitt@gmail.com");
