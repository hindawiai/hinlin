<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// npgtech.h - Keytable क्रम npgtech Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table npgtech[] = अणु
	अणु 0x1d, KEY_SWITCHVIDEOMODE पूर्ण,	/* चयन inमाला_दो */
	अणु 0x2a, KEY_FRONT पूर्ण,

	अणु 0x3e, KEY_NUMERIC_1 पूर्ण,
	अणु 0x02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x06, KEY_NUMERIC_3 पूर्ण,
	अणु 0x0a, KEY_NUMERIC_4 पूर्ण,
	अणु 0x0e, KEY_NUMERIC_5 पूर्ण,
	अणु 0x12, KEY_NUMERIC_6 पूर्ण,
	अणु 0x16, KEY_NUMERIC_7 पूर्ण,
	अणु 0x1a, KEY_NUMERIC_8 पूर्ण,
	अणु 0x1e, KEY_NUMERIC_9 पूर्ण,
	अणु 0x3a, KEY_NUMERIC_0 पूर्ण,
	अणु 0x22, KEY_NUMLOCK पूर्ण,		/* -/-- */
	अणु 0x20, KEY_REFRESH पूर्ण,

	अणु 0x03, KEY_BRIGHTNESSDOWN पूर्ण,
	अणु 0x28, KEY_AUDIO पूर्ण,
	अणु 0x3c, KEY_CHANNELUP पूर्ण,
	अणु 0x3f, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x2e, KEY_MUTE पूर्ण,
	अणु 0x3b, KEY_VOLUMEUP पूर्ण,
	अणु 0x00, KEY_CHANNELDOWN पूर्ण,
	अणु 0x07, KEY_BRIGHTNESSUP पूर्ण,
	अणु 0x2c, KEY_TEXT पूर्ण,

	अणु 0x37, KEY_RECORD पूर्ण,
	अणु 0x17, KEY_PLAY पूर्ण,
	अणु 0x13, KEY_PAUSE पूर्ण,
	अणु 0x26, KEY_STOP पूर्ण,
	अणु 0x18, KEY_FASTFORWARD पूर्ण,
	अणु 0x14, KEY_REWIND पूर्ण,
	अणु 0x33, KEY_ZOOM पूर्ण,
	अणु 0x32, KEY_KEYBOARD पूर्ण,
	अणु 0x30, KEY_GOTO पूर्ण,		/* Poपूर्णांकing arrow */
	अणु 0x36, KEY_MACRO पूर्ण,		/* Maximize/Minimize (yellow) */
	अणु 0x0b, KEY_RADIO पूर्ण,
	अणु 0x10, KEY_POWER पूर्ण,

पूर्ण;

अटल काष्ठा rc_map_list npgtech_map = अणु
	.map = अणु
		.scan     = npgtech,
		.size     = ARRAY_SIZE(npgtech),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_NPGTECH,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_npgtech(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&npgtech_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_npgtech(व्योम)
अणु
	rc_map_unरेजिस्टर(&npgtech_map);
पूर्ण

module_init(init_rc_map_npgtech)
module_निकास(निकास_rc_map_npgtech)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
