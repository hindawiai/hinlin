<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright (c) 2018 Christian Hewitt

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/*
 * Keymap क्रम the Tanix TX3 mini STB remote control
 */

अटल काष्ठा rc_map_table tanix_tx3mini[] = अणु
	अणु 0x8051, KEY_POWER पूर्ण,
	अणु 0x804d, KEY_MUTE पूर्ण,

	अणु 0x8009, KEY_RED पूर्ण,
	अणु 0x8011, KEY_GREEN पूर्ण,
	अणु 0x8054, KEY_YELLOW पूर्ण,
	अणु 0x804f, KEY_BLUE पूर्ण,

	अणु 0x8056, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x80bd, KEY_PREVIOUS पूर्ण,
	अणु 0x80bb, KEY_NEXT पूर्ण,
	अणु 0x804e, KEY_VOLUMEUP पूर्ण,

	अणु 0x8053, KEY_HOME पूर्ण,
	अणु 0x801b, KEY_BACK पूर्ण,

	अणु 0x8026, KEY_UP पूर्ण,
	अणु 0x8028, KEY_DOWN पूर्ण,
	अणु 0x8025, KEY_LEFT पूर्ण,
	अणु 0x8027, KEY_RIGHT पूर्ण,
	अणु 0x800d, KEY_OK पूर्ण,

	अणु 0x8049, KEY_MENU पूर्ण,
	अणु 0x8052, KEY_EPG पूर्ण, // mouse

	अणु 0x8031, KEY_1 पूर्ण,
	अणु 0x8032, KEY_2 पूर्ण,
	अणु 0x8033, KEY_3 पूर्ण,

	अणु 0x8034, KEY_4 पूर्ण,
	अणु 0x8035, KEY_5 पूर्ण,
	अणु 0x8036, KEY_6 पूर्ण,

	अणु 0x8037, KEY_7 पूर्ण,
	अणु 0x8038, KEY_8 पूर्ण,
	अणु 0x8039, KEY_9 पूर्ण,

	अणु 0x8058, KEY_SUBTITLE पूर्ण, // 1/a
	अणु 0x8030, KEY_0 पूर्ण,
	अणु 0x8044, KEY_DELETE पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list tanix_tx3mini_map = अणु
	.map = अणु
		.scan     = tanix_tx3mini,
		.size     = ARRAY_SIZE(tanix_tx3mini),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_TANIX_TX3MINI,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_tanix_tx3mini(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&tanix_tx3mini_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_tanix_tx3mini(व्योम)
अणु
	rc_map_unरेजिस्टर(&tanix_tx3mini_map);
पूर्ण

module_init(init_rc_map_tanix_tx3mini)
module_निकास(निकास_rc_map_tanix_tx3mini)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Hewitt <christianshewitt@gmail.com>");
