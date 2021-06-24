<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright (c) 2018 Christian Hewitt

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/*
 * This keymap is used with the WeTek Hub STB.
 */

अटल काष्ठा rc_map_table wetek_hub[] = अणु
	अणु 0x77f1, KEY_POWER पूर्ण,

	अणु 0x77f2, KEY_HOME पूर्ण,
	अणु 0x77f3, KEY_MUTE पूर्ण, // mouse

	अणु 0x77f4, KEY_UP पूर्ण,
	अणु 0x77f5, KEY_DOWN पूर्ण,
	अणु 0x77f6, KEY_LEFT पूर्ण,
	अणु 0x77f7, KEY_RIGHT पूर्ण,
	अणु 0x77f8, KEY_OK पूर्ण,

	अणु 0x77f9, KEY_BACK पूर्ण,
	अणु 0x77fa, KEY_MENU पूर्ण,

	अणु 0x77fb, KEY_VOLUMEUP पूर्ण,
	अणु 0x77fc, KEY_VOLUMEDOWN पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list wetek_hub_map = अणु
	.map = अणु
		.scan     = wetek_hub,
		.size     = ARRAY_SIZE(wetek_hub),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_WETEK_HUB,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_wetek_hub(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&wetek_hub_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_wetek_hub(व्योम)
अणु
	rc_map_unरेजिस्टर(&wetek_hub_map);
पूर्ण

module_init(init_rc_map_wetek_hub)
module_निकास(निकास_rc_map_wetek_hub)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Hewitt <christianshewitt@gmail.com>");
