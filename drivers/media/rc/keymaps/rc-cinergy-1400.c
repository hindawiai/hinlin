<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// cinergy-1400.h - Keytable क्रम cinergy_1400 Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Cinergy 1400 DVB-T */

अटल काष्ठा rc_map_table cinergy_1400[] = अणु
	अणु 0x01, KEY_POWER पूर्ण,
	अणु 0x02, KEY_NUMERIC_1 पूर्ण,
	अणु 0x03, KEY_NUMERIC_2 पूर्ण,
	अणु 0x04, KEY_NUMERIC_3 पूर्ण,
	अणु 0x05, KEY_NUMERIC_4 पूर्ण,
	अणु 0x06, KEY_NUMERIC_5 पूर्ण,
	अणु 0x07, KEY_NUMERIC_6 पूर्ण,
	अणु 0x08, KEY_NUMERIC_7 पूर्ण,
	अणु 0x09, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0a, KEY_NUMERIC_9 पूर्ण,
	अणु 0x0c, KEY_NUMERIC_0 पूर्ण,

	अणु 0x0b, KEY_VIDEO पूर्ण,
	अणु 0x0d, KEY_REFRESH पूर्ण,
	अणु 0x0e, KEY_SELECT पूर्ण,
	अणु 0x0f, KEY_EPG पूर्ण,
	अणु 0x10, KEY_UP पूर्ण,
	अणु 0x11, KEY_LEFT पूर्ण,
	अणु 0x12, KEY_OK पूर्ण,
	अणु 0x13, KEY_RIGHT पूर्ण,
	अणु 0x14, KEY_DOWN पूर्ण,
	अणु 0x15, KEY_TEXT पूर्ण,
	अणु 0x16, KEY_INFO पूर्ण,

	अणु 0x17, KEY_RED पूर्ण,
	अणु 0x18, KEY_GREEN पूर्ण,
	अणु 0x19, KEY_YELLOW पूर्ण,
	अणु 0x1a, KEY_BLUE पूर्ण,

	अणु 0x1b, KEY_CHANNELUP पूर्ण,
	अणु 0x1c, KEY_VOLUMEUP पूर्ण,
	अणु 0x1d, KEY_MUTE पूर्ण,
	अणु 0x1e, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x1f, KEY_CHANNELDOWN पूर्ण,

	अणु 0x40, KEY_PAUSE पूर्ण,
	अणु 0x4c, KEY_PLAY पूर्ण,
	अणु 0x58, KEY_RECORD पूर्ण,
	अणु 0x54, KEY_PREVIOUS पूर्ण,
	अणु 0x48, KEY_STOP पूर्ण,
	अणु 0x5c, KEY_NEXT पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list cinergy_1400_map = अणु
	.map = अणु
		.scan     = cinergy_1400,
		.size     = ARRAY_SIZE(cinergy_1400),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_CINERGY_1400,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_cinergy_1400(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&cinergy_1400_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_cinergy_1400(व्योम)
अणु
	rc_map_unरेजिस्टर(&cinergy_1400_map);
पूर्ण

module_init(init_rc_map_cinergy_1400)
module_निकास(निकास_rc_map_cinergy_1400)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
