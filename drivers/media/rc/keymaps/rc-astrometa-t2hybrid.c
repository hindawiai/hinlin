<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Keytable क्रम the Astrometa T2hybrid remote controller
 *
 * Copyright (C) 2017 Oleh Kravchenko <oleg@kaa.org.ua>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table t2hybrid[] = अणु
	अणु 0x4d, KEY_POWER2 पूर्ण,
	अणु 0x54, KEY_VIDEO पूर्ण, /* Source */
	अणु 0x16, KEY_MUTE पूर्ण,

	अणु 0x4c, KEY_RECORD पूर्ण,
	अणु 0x05, KEY_CHANNELUP पूर्ण,
	अणु 0x0c, KEY_TIMEपूर्ण, /* Timeshअगरt */

	अणु 0x0a, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x40, KEY_ZOOM पूर्ण, /* Fullscreen */
	अणु 0x1e, KEY_VOLUMEUP पूर्ण,

	अणु 0x12, KEY_NUMERIC_0 पूर्ण,
	अणु 0x02, KEY_CHANNELDOWN पूर्ण,
	अणु 0x1c, KEY_AGAIN पूर्ण, /* Recall */

	अणु 0x09, KEY_NUMERIC_1 पूर्ण,
	अणु 0x1d, KEY_NUMERIC_2 पूर्ण,
	अणु 0x1f, KEY_NUMERIC_3 पूर्ण,

	अणु 0x0d, KEY_NUMERIC_4 पूर्ण,
	अणु 0x19, KEY_NUMERIC_5 पूर्ण,
	अणु 0x1b, KEY_NUMERIC_6 पूर्ण,

	अणु 0x11, KEY_NUMERIC_7 पूर्ण,
	अणु 0x15, KEY_NUMERIC_8 पूर्ण,
	अणु 0x17, KEY_NUMERIC_9 पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list t2hybrid_map = अणु
	.map = अणु
		.scan     = t2hybrid,
		.size     = ARRAY_SIZE(t2hybrid),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_ASTROMETA_T2HYBRID,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_t2hybrid(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&t2hybrid_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_t2hybrid(व्योम)
अणु
	rc_map_unरेजिस्टर(&t2hybrid_map);
पूर्ण

module_init(init_rc_map_t2hybrid)
module_निकास(निकास_rc_map_t2hybrid)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Oleh Kravchenko <oleg@kaa.org.ua>");
