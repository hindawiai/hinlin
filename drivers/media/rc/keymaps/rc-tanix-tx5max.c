<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright (c) 2018 Christian Hewitt

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/*
 * Keymap क्रम the Tanix TX5 max STB remote control
 */

अटल काष्ठा rc_map_table tanix_tx5max[] = अणु
	अणु 0x40404d, KEY_POWER पूर्ण,
	अणु 0x404043, KEY_MUTE पूर्ण,

	अणु 0x404017, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x404018, KEY_VOLUMEUP पूर्ण,

	अणु 0x40400b, KEY_UP पूर्ण,
	अणु 0x404010, KEY_LEFT पूर्ण,
	अणु 0x404011, KEY_RIGHT पूर्ण,
	अणु 0x40400e, KEY_DOWN पूर्ण,
	अणु 0x40400d, KEY_OK पूर्ण,

	अणु 0x40401a, KEY_HOME पूर्ण,
	अणु 0x404045, KEY_MENU पूर्ण,
	अणु 0x404042, KEY_BACK पूर्ण,

	अणु 0x404001, KEY_1 पूर्ण,
	अणु 0x404002, KEY_2 पूर्ण,
	अणु 0x404003, KEY_3 पूर्ण,

	अणु 0x404004, KEY_4 पूर्ण,
	अणु 0x404005, KEY_5 पूर्ण,
	अणु 0x404006, KEY_6 पूर्ण,

	अणु 0x404007, KEY_7 पूर्ण,
	अणु 0x404008, KEY_8 पूर्ण,
	अणु 0x404009, KEY_9 पूर्ण,

	अणु 0x404047, KEY_SUBTITLE पूर्ण, // mouse
	अणु 0x404000, KEY_0 पूर्ण,
	अणु 0x40400c, KEY_DELETE पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list tanix_tx5max_map = अणु
	.map = अणु
		.scan     = tanix_tx5max,
		.size     = ARRAY_SIZE(tanix_tx5max),
		.rc_proto = RC_PROTO_NECX,
		.name     = RC_MAP_TANIX_TX5MAX,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_tanix_tx5max(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&tanix_tx5max_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_tanix_tx5max(व्योम)
अणु
	rc_map_unरेजिस्टर(&tanix_tx5max_map);
पूर्ण

module_init(init_rc_map_tanix_tx5max)
module_निकास(निकास_rc_map_tanix_tx5max)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Hewitt <christianshewitt@gmail.com>");
