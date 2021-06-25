<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MSI DIGIVOX mini II remote controller keytable
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table msi_digivox_ii[] = अणु
	अणु 0x0302, KEY_NUMERIC_2 पूर्ण,
	अणु 0x0303, KEY_UP पूर्ण,              /* up */
	अणु 0x0304, KEY_NUMERIC_3 पूर्ण,
	अणु 0x0305, KEY_CHANNELDOWN पूर्ण,
	अणु 0x0308, KEY_NUMERIC_5 पूर्ण,
	अणु 0x0309, KEY_NUMERIC_0 पूर्ण,
	अणु 0x030b, KEY_NUMERIC_8 पूर्ण,
	अणु 0x030d, KEY_DOWN पूर्ण,            /* करोwn */
	अणु 0x0310, KEY_NUMERIC_9 पूर्ण,
	अणु 0x0311, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0314, KEY_VOLUMEUP पूर्ण,
	अणु 0x0315, KEY_CHANNELUP पूर्ण,
	अणु 0x0316, KEY_OK पूर्ण,
	अणु 0x0317, KEY_POWER2 पूर्ण,
	अणु 0x031a, KEY_NUMERIC_1 पूर्ण,
	अणु 0x031c, KEY_NUMERIC_4 पूर्ण,
	अणु 0x031d, KEY_NUMERIC_6 पूर्ण,
	अणु 0x031f, KEY_VOLUMEDOWN पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list msi_digivox_ii_map = अणु
	.map = अणु
		.scan     = msi_digivox_ii,
		.size     = ARRAY_SIZE(msi_digivox_ii),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_MSI_DIGIVOX_II,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_msi_digivox_ii(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&msi_digivox_ii_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_msi_digivox_ii(व्योम)
अणु
	rc_map_unरेजिस्टर(&msi_digivox_ii_map);
पूर्ण

module_init(init_rc_map_msi_digivox_ii)
module_निकास(निकास_rc_map_msi_digivox_ii)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
