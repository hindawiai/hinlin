<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

// Keytable क्रम the Pine64 IR Remote Controller
// Copyright (c) 2017 Jonas Karlman

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table pine64[] = अणु
	अणु 0x40404d, KEY_POWER पूर्ण,
	अणु 0x40401f, KEY_WWW पूर्ण,
	अणु 0x40400a, KEY_MUTE पूर्ण,

	अणु 0x404017, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x404018, KEY_VOLUMEUP पूर्ण,

	अणु 0x404010, KEY_LEFT पूर्ण,
	अणु 0x404011, KEY_RIGHT पूर्ण,
	अणु 0x40400b, KEY_UP पूर्ण,
	अणु 0x40400e, KEY_DOWN पूर्ण,
	अणु 0x40400d, KEY_OK पूर्ण,

	अणु 0x40401d, KEY_MENU पूर्ण,
	अणु 0x40401a, KEY_HOME पूर्ण,

	अणु 0x404045, KEY_BACK पूर्ण,

	अणु 0x404001, KEY_NUMERIC_1 पूर्ण,
	अणु 0x404002, KEY_NUMERIC_2 पूर्ण,
	अणु 0x404003, KEY_NUMERIC_3 पूर्ण,
	अणु 0x404004, KEY_NUMERIC_4 पूर्ण,
	अणु 0x404005, KEY_NUMERIC_5 पूर्ण,
	अणु 0x404006, KEY_NUMERIC_6 पूर्ण,
	अणु 0x404007, KEY_NUMERIC_7 पूर्ण,
	अणु 0x404008, KEY_NUMERIC_8 पूर्ण,
	अणु 0x404009, KEY_NUMERIC_9 पूर्ण,
	अणु 0x40400c, KEY_BACKSPACE पूर्ण,
	अणु 0x404000, KEY_NUMERIC_0 पूर्ण,
	अणु 0x404047, KEY_EPG पूर्ण, // mouse
पूर्ण;

अटल काष्ठा rc_map_list pine64_map = अणु
	.map = अणु
		.scan     = pine64,
		.size     = ARRAY_SIZE(pine64),
		.rc_proto = RC_PROTO_NECX,
		.name     = RC_MAP_PINE64,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_pine64(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&pine64_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_pine64(व्योम)
अणु
	rc_map_unरेजिस्टर(&pine64_map);
पूर्ण

module_init(init_rc_map_pine64)
module_निकास(निकास_rc_map_pine64)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jonas Karlman");
