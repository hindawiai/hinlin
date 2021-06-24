<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* rc-streamzap.c - Keytable क्रम Streamzap PC Remote, क्रम use
 * with the Streamzap PC Remote IR Receiver.
 *
 * Copyright (c) 2010 by Jarod Wilson <jarod@redhat.com>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table streamzap[] = अणु
/*
 * The Streamzap remote is almost, but not quite, RC-5, as it has an extra
 * bit in it.
 */
	अणु 0x28c0, KEY_NUMERIC_0 पूर्ण,
	अणु 0x28c1, KEY_NUMERIC_1 पूर्ण,
	अणु 0x28c2, KEY_NUMERIC_2 पूर्ण,
	अणु 0x28c3, KEY_NUMERIC_3 पूर्ण,
	अणु 0x28c4, KEY_NUMERIC_4 पूर्ण,
	अणु 0x28c5, KEY_NUMERIC_5 पूर्ण,
	अणु 0x28c6, KEY_NUMERIC_6 पूर्ण,
	अणु 0x28c7, KEY_NUMERIC_7 पूर्ण,
	अणु 0x28c8, KEY_NUMERIC_8 पूर्ण,
	अणु 0x28c9, KEY_NUMERIC_9 पूर्ण,
	अणु 0x28ca, KEY_POWER पूर्ण,
	अणु 0x28cb, KEY_MUTE पूर्ण,
	अणु 0x28cc, KEY_CHANNELUP पूर्ण,
	अणु 0x28cd, KEY_VOLUMEUP पूर्ण,
	अणु 0x28ce, KEY_CHANNELDOWN पूर्ण,
	अणु 0x28cf, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x28d0, KEY_UP पूर्ण,
	अणु 0x28d1, KEY_LEFT पूर्ण,
	अणु 0x28d2, KEY_OK पूर्ण,
	अणु 0x28d3, KEY_RIGHT पूर्ण,
	अणु 0x28d4, KEY_DOWN पूर्ण,
	अणु 0x28d5, KEY_MENU पूर्ण,
	अणु 0x28d6, KEY_EXIT पूर्ण,
	अणु 0x28d7, KEY_PLAY पूर्ण,
	अणु 0x28d8, KEY_PAUSE पूर्ण,
	अणु 0x28d9, KEY_STOP पूर्ण,
	अणु 0x28da, KEY_BACK पूर्ण,
	अणु 0x28db, KEY_FORWARD पूर्ण,
	अणु 0x28dc, KEY_RECORD पूर्ण,
	अणु 0x28dd, KEY_REWIND पूर्ण,
	अणु 0x28de, KEY_FASTFORWARD पूर्ण,
	अणु 0x28e0, KEY_RED पूर्ण,
	अणु 0x28e1, KEY_GREEN पूर्ण,
	अणु 0x28e2, KEY_YELLOW पूर्ण,
	अणु 0x28e3, KEY_BLUE पूर्ण,

पूर्ण;

अटल काष्ठा rc_map_list streamzap_map = अणु
	.map = अणु
		.scan     = streamzap,
		.size     = ARRAY_SIZE(streamzap),
		.rc_proto = RC_PROTO_RC5_SZ,
		.name     = RC_MAP_STREAMZAP,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_streamzap(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&streamzap_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_streamzap(व्योम)
अणु
	rc_map_unरेजिस्टर(&streamzap_map);
पूर्ण

module_init(init_rc_map_streamzap)
module_निकास(निकास_rc_map_streamzap)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jarod Wilson <jarod@redhat.com>");
