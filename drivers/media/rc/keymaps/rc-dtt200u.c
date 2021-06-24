<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Keytable क्रम Wideview WT-220U.
 *
 * Copyright (c) 2016 Jonathan McDowell <noodles@earth.li>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* key list क्रम the tiny remote control (Yakumo, करोn't know about the others) */
अटल काष्ठा rc_map_table dtt200u_table[] = अणु
	अणु 0x8001, KEY_MUTE पूर्ण,
	अणु 0x8002, KEY_CHANNELDOWN पूर्ण,
	अणु 0x8003, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x8004, KEY_NUMERIC_1 पूर्ण,
	अणु 0x8005, KEY_NUMERIC_2 पूर्ण,
	अणु 0x8006, KEY_NUMERIC_3 पूर्ण,
	अणु 0x8007, KEY_NUMERIC_4 पूर्ण,
	अणु 0x8008, KEY_NUMERIC_5 पूर्ण,
	अणु 0x8009, KEY_NUMERIC_6 पूर्ण,
	अणु 0x800a, KEY_NUMERIC_7 पूर्ण,
	अणु 0x800c, KEY_ZOOM पूर्ण,
	अणु 0x800d, KEY_NUMERIC_0 पूर्ण,
	अणु 0x800e, KEY_SELECT पूर्ण,
	अणु 0x8012, KEY_POWER पूर्ण,
	अणु 0x801a, KEY_CHANNELUP पूर्ण,
	अणु 0x801b, KEY_NUMERIC_8 पूर्ण,
	अणु 0x801e, KEY_VOLUMEUP पूर्ण,
	अणु 0x801f, KEY_NUMERIC_9 पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list dtt200u_map = अणु
	.map = अणु
		.scan     = dtt200u_table,
		.size     = ARRAY_SIZE(dtt200u_table),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_DTT200U,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_dtt200u(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&dtt200u_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_dtt200u(व्योम)
अणु
	rc_map_unरेजिस्टर(&dtt200u_map);
पूर्ण

module_init(init_rc_map_dtt200u)
module_निकास(निकास_rc_map_dtt200u)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jonathan McDowell <noodles@earth.li>");
