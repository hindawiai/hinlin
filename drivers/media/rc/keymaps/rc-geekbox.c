<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Keytable क्रम the GeekBox remote controller
 *
 * Copyright (C) 2017 Martin Blumenstingl <martin.blumenstingl@googlemail.com>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table geekbox[] = अणु
	अणु 0x01, KEY_BACK पूर्ण,
	अणु 0x02, KEY_DOWN पूर्ण,
	अणु 0x03, KEY_UP पूर्ण,
	अणु 0x07, KEY_OK पूर्ण,
	अणु 0x0b, KEY_VOLUMEUP पूर्ण,
	अणु 0x0e, KEY_LEFT पूर्ण,
	अणु 0x13, KEY_MENU पूर्ण,
	अणु 0x14, KEY_POWER पूर्ण,
	अणु 0x1a, KEY_RIGHT पूर्ण,
	अणु 0x48, KEY_HOME पूर्ण,
	अणु 0x58, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x5c, KEY_SCREEN पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list geekbox_map = अणु
	.map = अणु
		.scan     = geekbox,
		.size     = ARRAY_SIZE(geekbox),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_GEEKBOX,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_geekbox(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&geekbox_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_geekbox(व्योम)
अणु
	rc_map_unरेजिस्टर(&geekbox_map);
पूर्ण

module_init(init_rc_map_geekbox)
module_निकास(निकास_rc_map_geekbox)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Martin Blumenstingl <martin.blumenstingl@googlemail.com>");
