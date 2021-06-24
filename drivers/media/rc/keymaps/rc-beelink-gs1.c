<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright (c) 2019 Clथऊment Pथऊron

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/*
 * Keymap क्रम the Beelink GS1 remote control
 */

अटल काष्ठा rc_map_table beelink_gs1_table[] = अणु
	/*
	 * TV Keys (Power, Learn and Volume)
	 * अणु 0x40400d, KEY_TV पूर्ण,
	 * अणु 0x80f1, KEY_TV पूर्ण,
	 * अणु 0x80f3, KEY_TV पूर्ण,
	 * अणु 0x80f4, KEY_TV पूर्ण,
	 */

	अणु 0x8051, KEY_POWER पूर्ण,
	अणु 0x804d, KEY_MUTE पूर्ण,
	अणु 0x8040, KEY_CONFIG पूर्ण,

	अणु 0x8026, KEY_UP पूर्ण,
	अणु 0x8028, KEY_DOWN पूर्ण,
	अणु 0x8025, KEY_LEFT पूर्ण,
	अणु 0x8027, KEY_RIGHT पूर्ण,
	अणु 0x800d, KEY_OK पूर्ण,

	अणु 0x8053, KEY_HOME पूर्ण,
	अणु 0x80bc, KEY_MEDIA पूर्ण,
	अणु 0x801b, KEY_BACK पूर्ण,
	अणु 0x8049, KEY_MENU पूर्ण,

	अणु 0x804e, KEY_VOLUMEUP पूर्ण,
	अणु 0x8056, KEY_VOLUMEDOWN पूर्ण,

	अणु 0x8054, KEY_SUBTITLE पूर्ण, /* Web */
	अणु 0x8052, KEY_EPG पूर्ण, /* Media */

	अणु 0x8041, KEY_CHANNELUP पूर्ण,
	अणु 0x8042, KEY_CHANNELDOWN पूर्ण,

	अणु 0x8031, KEY_1 पूर्ण,
	अणु 0x8032, KEY_2 पूर्ण,
	अणु 0x8033, KEY_3 पूर्ण,

	अणु 0x8034, KEY_4 पूर्ण,
	अणु 0x8035, KEY_5 पूर्ण,
	अणु 0x8036, KEY_6 पूर्ण,

	अणु 0x8037, KEY_7 पूर्ण,
	अणु 0x8038, KEY_8 पूर्ण,
	अणु 0x8039, KEY_9 पूर्ण,

	अणु 0x8044, KEY_DELETE पूर्ण,
	अणु 0x8030, KEY_0 पूर्ण,
	अणु 0x8058, KEY_MODE पूर्ण, /* # Input Method */
पूर्ण;

अटल काष्ठा rc_map_list beelink_gs1_map = अणु
	.map = अणु
		.scan     = beelink_gs1_table,
		.size     = ARRAY_SIZE(beelink_gs1_table),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_BEELINK_GS1,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_beelink_gs1(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&beelink_gs1_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_beelink_gs1(व्योम)
अणु
	rc_map_unरेजिस्टर(&beelink_gs1_map);
पूर्ण

module_init(init_rc_map_beelink_gs1)
module_निकास(निकास_rc_map_beelink_gs1)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Clथऊment Pथऊron <peron.clem@gmail.com>");
