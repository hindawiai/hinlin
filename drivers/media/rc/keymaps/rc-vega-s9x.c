<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (C) 2019 Christian Hewitt <christianshewitt@gmail.com>

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

//
// Keytable क्रम the Tronsmart Vega S9x remote control
//

अटल काष्ठा rc_map_table vega_s9x[] = अणु
	अणु 0x18, KEY_POWER पूर्ण,
	अणु 0x17, KEY_MUTE पूर्ण, // mouse

	अणु 0x46, KEY_UP पूर्ण,
	अणु 0x47, KEY_LEFT पूर्ण,
	अणु 0x55, KEY_OK पूर्ण,
	अणु 0x15, KEY_RIGHT पूर्ण,
	अणु 0x16, KEY_DOWN पूर्ण,

	अणु 0x06, KEY_HOME पूर्ण,
	अणु 0x42, KEY_PLAYPAUSEपूर्ण,
	अणु 0x40, KEY_BACK पूर्ण,

	अणु 0x14, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x04, KEY_MENU पूर्ण,
	अणु 0x10, KEY_VOLUMEUP पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list vega_s9x_map = अणु
	.map = अणु
		.scan     = vega_s9x,
		.size     = ARRAY_SIZE(vega_s9x),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_VEGA_S9X,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_vega_s9x(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&vega_s9x_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_vega_s9x(व्योम)
अणु
	rc_map_unरेजिस्टर(&vega_s9x_map);
पूर्ण

module_init(init_rc_map_vega_s9x)
module_निकास(निकास_rc_map_vega_s9x)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Hewitt <christianshewitt@gmail.com");
