<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// nebula.h - Keytable क्रम nebula Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table nebula[] = अणु
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
	अणु 0x000a, KEY_TV पूर्ण,
	अणु 0x000b, KEY_AUX पूर्ण,
	अणु 0x000c, KEY_DVD पूर्ण,
	अणु 0x000d, KEY_POWER पूर्ण,
	अणु 0x000e, KEY_CAMERA पूर्ण,	/* labelled 'Picture' */
	अणु 0x000f, KEY_AUDIO पूर्ण,
	अणु 0x0010, KEY_INFO पूर्ण,
	अणु 0x0011, KEY_F13 पूर्ण,	/* 16:9 */
	अणु 0x0012, KEY_F14 पूर्ण,	/* 14:9 */
	अणु 0x0013, KEY_EPG पूर्ण,
	अणु 0x0014, KEY_EXIT पूर्ण,
	अणु 0x0015, KEY_MENU पूर्ण,
	अणु 0x0016, KEY_UP पूर्ण,
	अणु 0x0017, KEY_DOWN पूर्ण,
	अणु 0x0018, KEY_LEFT पूर्ण,
	अणु 0x0019, KEY_RIGHT पूर्ण,
	अणु 0x001a, KEY_ENTER पूर्ण,
	अणु 0x001b, KEY_CHANNELUP पूर्ण,
	अणु 0x001c, KEY_CHANNELDOWN पूर्ण,
	अणु 0x001d, KEY_VOLUMEUP पूर्ण,
	अणु 0x001e, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x001f, KEY_RED पूर्ण,
	अणु 0x0020, KEY_GREEN पूर्ण,
	अणु 0x0021, KEY_YELLOW पूर्ण,
	अणु 0x0022, KEY_BLUE पूर्ण,
	अणु 0x0023, KEY_SUBTITLE पूर्ण,
	अणु 0x0024, KEY_F15 पूर्ण,	/* AD */
	अणु 0x0025, KEY_TEXT पूर्ण,
	अणु 0x0026, KEY_MUTE पूर्ण,
	अणु 0x0027, KEY_REWIND पूर्ण,
	अणु 0x0028, KEY_STOP पूर्ण,
	अणु 0x0029, KEY_PLAY पूर्ण,
	अणु 0x002a, KEY_FASTFORWARD पूर्ण,
	अणु 0x002b, KEY_F16 पूर्ण,	/* chapter */
	अणु 0x002c, KEY_PAUSE पूर्ण,
	अणु 0x002d, KEY_PLAY पूर्ण,
	अणु 0x002e, KEY_RECORD पूर्ण,
	अणु 0x002f, KEY_F17 पूर्ण,	/* picture in picture */
	अणु 0x0030, KEY_KPPLUS पूर्ण,	/* zoom in */
	अणु 0x0031, KEY_KPMINUS पूर्ण,	/* zoom out */
	अणु 0x0032, KEY_F18 पूर्ण,	/* capture */
	अणु 0x0033, KEY_F19 पूर्ण,	/* web */
	अणु 0x0034, KEY_EMAIL पूर्ण,
	अणु 0x0035, KEY_PHONE पूर्ण,
	अणु 0x0036, KEY_PC पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list nebula_map = अणु
	.map = अणु
		.scan     = nebula,
		.size     = ARRAY_SIZE(nebula),
		.rc_proto = RC_PROTO_RC5,
		.name     = RC_MAP_NEBULA,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_nebula(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&nebula_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_nebula(व्योम)
अणु
	rc_map_unरेजिस्टर(&nebula_map);
पूर्ण

module_init(init_rc_map_nebula)
module_निकास(निकास_rc_map_nebula)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
