<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * A-Link DTU(m) remote controller keytable
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* A-Link DTU(m) slim remote, 6 rows, 3 columns. */
अटल काष्ठा rc_map_table alink_dtu_m[] = अणु
	अणु 0x0800, KEY_VOLUMEUP पूर्ण,
	अणु 0x0801, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0802, KEY_NUMERIC_3 पूर्ण,
	अणु 0x0803, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0804, KEY_NUMERIC_9 पूर्ण,
	अणु 0x0805, KEY_NEW पूर्ण,             /* symbol: PIP */
	अणु 0x0806, KEY_NUMERIC_0 पूर्ण,
	अणु 0x0807, KEY_CHANNEL पूर्ण,         /* JUMP */
	अणु 0x080d, KEY_NUMERIC_5 पूर्ण,
	अणु 0x080f, KEY_NUMERIC_2 पूर्ण,
	अणु 0x0812, KEY_POWER2 पूर्ण,
	अणु 0x0814, KEY_CHANNELUP पूर्ण,
	अणु 0x0816, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x0818, KEY_NUMERIC_6 पूर्ण,
	अणु 0x081a, KEY_MUTE पूर्ण,
	अणु 0x081b, KEY_NUMERIC_8 पूर्ण,
	अणु 0x081c, KEY_NUMERIC_4 पूर्ण,
	अणु 0x081d, KEY_CHANNELDOWN पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list alink_dtu_m_map = अणु
	.map = अणु
		.scan     = alink_dtu_m,
		.size     = ARRAY_SIZE(alink_dtu_m),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_ALINK_DTU_M,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_alink_dtu_m(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&alink_dtu_m_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_alink_dtu_m(व्योम)
अणु
	rc_map_unरेजिस्टर(&alink_dtu_m_map);
पूर्ण

module_init(init_rc_map_alink_dtu_m)
module_निकास(निकास_rc_map_alink_dtu_m)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
