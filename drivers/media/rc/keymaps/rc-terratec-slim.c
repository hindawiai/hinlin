<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TerraTec remote controller keytable
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* TerraTec slim remote, 7 rows, 4 columns. */
/* Uses NEC extended 0x02bd. */
अटल काष्ठा rc_map_table terratec_slim[] = अणु
	अणु 0x02bd00, KEY_NUMERIC_1 पूर्ण,
	अणु 0x02bd01, KEY_NUMERIC_2 पूर्ण,
	अणु 0x02bd02, KEY_NUMERIC_3 पूर्ण,
	अणु 0x02bd03, KEY_NUMERIC_4 पूर्ण,
	अणु 0x02bd04, KEY_NUMERIC_5 पूर्ण,
	अणु 0x02bd05, KEY_NUMERIC_6 पूर्ण,
	अणु 0x02bd06, KEY_NUMERIC_7 पूर्ण,
	अणु 0x02bd07, KEY_NUMERIC_8 पूर्ण,
	अणु 0x02bd08, KEY_NUMERIC_9 पूर्ण,
	अणु 0x02bd09, KEY_NUMERIC_0 पूर्ण,
	अणु 0x02bd0a, KEY_MUTE पूर्ण,
	अणु 0x02bd0b, KEY_NEW पूर्ण,             /* symbol: PIP */
	अणु 0x02bd0e, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x02bd0f, KEY_PLAYPAUSE पूर्ण,
	अणु 0x02bd10, KEY_RIGHT पूर्ण,
	अणु 0x02bd11, KEY_LEFT पूर्ण,
	अणु 0x02bd12, KEY_UP पूर्ण,
	अणु 0x02bd13, KEY_DOWN पूर्ण,
	अणु 0x02bd15, KEY_OK पूर्ण,
	अणु 0x02bd16, KEY_STOP पूर्ण,
	अणु 0x02bd17, KEY_CAMERA पूर्ण,          /* snapshot */
	अणु 0x02bd18, KEY_CHANNELUP पूर्ण,
	अणु 0x02bd19, KEY_RECORD पूर्ण,
	अणु 0x02bd1a, KEY_CHANNELDOWN पूर्ण,
	अणु 0x02bd1c, KEY_ESC पूर्ण,
	अणु 0x02bd1f, KEY_VOLUMEUP पूर्ण,
	अणु 0x02bd44, KEY_EPG पूर्ण,
	अणु 0x02bd45, KEY_POWER2 पूर्ण,          /* [red घातer button] */
पूर्ण;

अटल काष्ठा rc_map_list terratec_slim_map = अणु
	.map = अणु
		.scan     = terratec_slim,
		.size     = ARRAY_SIZE(terratec_slim),
		.rc_proto = RC_PROTO_NECX,
		.name     = RC_MAP_TERRATEC_SLIM,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_terratec_slim(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&terratec_slim_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_terratec_slim(व्योम)
अणु
	rc_map_unरेजिस्टर(&terratec_slim_map);
पूर्ण

module_init(init_rc_map_terratec_slim)
module_निकास(निकास_rc_map_terratec_slim)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
