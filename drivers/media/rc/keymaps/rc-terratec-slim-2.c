<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TerraTec remote controller keytable
 *
 * Copyright (C) 2011 Martin Groszhauser <mgroszhauser@gmail.com>
 * Copyright (C) 2011 Antti Palosaari <crope@iki.fi>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/*
 * TerraTec slim remote, 6 rows, 3 columns.
 * Keytable from Martin Groszhauser <mgroszhauser@gmail.com>
 */
अटल काष्ठा rc_map_table terratec_slim_2[] = अणु
	अणु 0x8001, KEY_MUTE पूर्ण,            /* MUTE */
	अणु 0x8002, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x8003, KEY_CHANNELDOWN पूर्ण,
	अणु 0x8004, KEY_NUMERIC_1 पूर्ण,
	अणु 0x8005, KEY_NUMERIC_2 पूर्ण,
	अणु 0x8006, KEY_NUMERIC_3 पूर्ण,
	अणु 0x8007, KEY_NUMERIC_4 पूर्ण,
	अणु 0x8008, KEY_NUMERIC_5 पूर्ण,
	अणु 0x8009, KEY_NUMERIC_6 पूर्ण,
	अणु 0x800a, KEY_NUMERIC_7 पूर्ण,
	अणु 0x800c, KEY_ZOOM पूर्ण,            /* [fullscreen] */
	अणु 0x800d, KEY_NUMERIC_0 पूर्ण,
	अणु 0x800e, KEY_AGAIN पूर्ण,           /* [two arrows क्रमming a circle] */
	अणु 0x8012, KEY_POWER2 पूर्ण,          /* [red घातer button] */
	अणु 0x801a, KEY_VOLUMEUP पूर्ण,
	अणु 0x801b, KEY_NUMERIC_8 पूर्ण,
	अणु 0x801e, KEY_CHANNELUP पूर्ण,
	अणु 0x801f, KEY_NUMERIC_9 पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list terratec_slim_2_map = अणु
	.map = अणु
		.scan     = terratec_slim_2,
		.size     = ARRAY_SIZE(terratec_slim_2),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_TERRATEC_SLIM_2,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_terratec_slim_2(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&terratec_slim_2_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_terratec_slim_2(व्योम)
अणु
	rc_map_unरेजिस्टर(&terratec_slim_2_map);
पूर्ण

module_init(init_rc_map_terratec_slim_2)
module_निकास(निकास_rc_map_terratec_slim_2)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
