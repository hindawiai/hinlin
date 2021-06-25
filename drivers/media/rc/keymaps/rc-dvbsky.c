<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* rc-dvbsky.c - Keytable क्रम DVBSky Remote Controllers
 *
 * keymap imported from ir-keymaps.c
 *
 * Copyright (c) 2010-2012 by Nibble Max <nibble.max@gmail.com>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>
/*
 * This table contains the complete RC5 code, instead of just the data part
 */

अटल काष्ठा rc_map_table rc5_dvbsky[] = अणु
	अणु 0x0000, KEY_NUMERIC_0 पूर्ण,
	अणु 0x0001, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0002, KEY_NUMERIC_2 पूर्ण,
	अणु 0x0003, KEY_NUMERIC_3 पूर्ण,
	अणु 0x0004, KEY_NUMERIC_4 पूर्ण,
	अणु 0x0005, KEY_NUMERIC_5 पूर्ण,
	अणु 0x0006, KEY_NUMERIC_6 पूर्ण,
	अणु 0x0007, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0008, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0009, KEY_NUMERIC_9 पूर्ण,
	अणु 0x000a, KEY_MUTE पूर्ण,
	अणु 0x000d, KEY_OK पूर्ण,
	अणु 0x000b, KEY_STOP पूर्ण,
	अणु 0x000c, KEY_EXIT पूर्ण,
	अणु 0x000e, KEY_CAMERA पूर्ण, /*Snap shot*/
	अणु 0x000f, KEY_SUBTITLE पूर्ण, /*PIP*/
	अणु 0x0010, KEY_VOLUMEUP पूर्ण,
	अणु 0x0011, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x0012, KEY_FAVORITES पूर्ण,
	अणु 0x0013, KEY_LIST पूर्ण, /*Info*/
	अणु 0x0016, KEY_PAUSE पूर्ण,
	अणु 0x0017, KEY_PLAY पूर्ण,
	अणु 0x001f, KEY_RECORD पूर्ण,
	अणु 0x0020, KEY_CHANNELDOWN पूर्ण,
	अणु 0x0021, KEY_CHANNELUP पूर्ण,
	अणु 0x0025, KEY_POWER2 पूर्ण,
	अणु 0x0026, KEY_REWIND पूर्ण,
	अणु 0x0027, KEY_FASTFORWARD पूर्ण,
	अणु 0x0029, KEY_LAST पूर्ण,
	अणु 0x002b, KEY_MENU पूर्ण,
	अणु 0x002c, KEY_EPG पूर्ण,
	अणु 0x002d, KEY_ZOOM पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list rc5_dvbsky_map = अणु
	.map = अणु
		.scan     = rc5_dvbsky,
		.size     = ARRAY_SIZE(rc5_dvbsky),
		.rc_proto = RC_PROTO_RC5,
		.name     = RC_MAP_DVBSKY,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_rc5_dvbsky(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&rc5_dvbsky_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_rc5_dvbsky(व्योम)
अणु
	rc_map_unरेजिस्टर(&rc5_dvbsky_map);
पूर्ण

module_init(init_rc_map_rc5_dvbsky)
module_निकास(निकास_rc_map_rc5_dvbsky)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nibble Max <nibble.max@gmail.com>");
