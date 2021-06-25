<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (C) 2021 Christian Hewitt <christianshewitt@gmail.com>

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

//
// Keytable क्रम the Minix NEO remote control
//

अटल काष्ठा rc_map_table minix_neo[] = अणु

	अणु 0x118, KEY_POWER पूर्ण,

	अणु 0x146, KEY_UP पूर्ण,
	अणु 0x116, KEY_DOWN पूर्ण,
	अणु 0x147, KEY_LEFT पूर्ण,
	अणु 0x115, KEY_RIGHT पूर्ण,
	अणु 0x155, KEY_ENTER पूर्ण,

	अणु 0x110, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x140, KEY_BACK पूर्ण,
	अणु 0x114, KEY_VOLUMEUP पूर्ण,

	अणु 0x10d, KEY_HOME पूर्ण,
	अणु 0x104, KEY_MENU पूर्ण,
	अणु 0x112, KEY_CONFIG पूर्ण,

पूर्ण;

अटल काष्ठा rc_map_list minix_neo_map = अणु
	.map = अणु
		.scan     = minix_neo,
		.size     = ARRAY_SIZE(minix_neo),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_MINIX_NEO,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_minix_neo(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&minix_neo_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_minix_neo(व्योम)
अणु
	rc_map_unरेजिस्टर(&minix_neo_map);
पूर्ण

module_init(init_rc_map_minix_neo)
module_निकास(निकास_rc_map_minix_neo)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Hewitt <christianshewitt@gmail.com");
