<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// proteus-2309.h - Keytable क्रम proteus_2309 Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Michal Majchrowicz <mmajchrowicz@gmail.com> */

अटल काष्ठा rc_map_table proteus_2309[] = अणु
	/* numeric */
	अणु 0x00, KEY_NUMERIC_0 पूर्ण,
	अणु 0x01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x03, KEY_NUMERIC_3 पूर्ण,
	अणु 0x04, KEY_NUMERIC_4 पूर्ण,
	अणु 0x05, KEY_NUMERIC_5 पूर्ण,
	अणु 0x06, KEY_NUMERIC_6 पूर्ण,
	अणु 0x07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x09, KEY_NUMERIC_9 पूर्ण,

	अणु 0x5c, KEY_POWER पूर्ण,		/* घातer       */
	अणु 0x20, KEY_ZOOM पूर्ण,		/* full screen */
	अणु 0x0f, KEY_BACKSPACE पूर्ण,	/* recall      */
	अणु 0x1b, KEY_ENTER पूर्ण,		/* mute        */
	अणु 0x41, KEY_RECORD पूर्ण,		/* record      */
	अणु 0x43, KEY_STOP पूर्ण,		/* stop        */
	अणु 0x16, KEY_S पूर्ण,
	अणु 0x1a, KEY_POWER2 पूर्ण,		/* off         */
	अणु 0x2e, KEY_RED पूर्ण,
	अणु 0x1f, KEY_CHANNELDOWN पूर्ण,	/* channel -   */
	अणु 0x1c, KEY_CHANNELUP पूर्ण,	/* channel +   */
	अणु 0x10, KEY_VOLUMEDOWN पूर्ण,	/* volume -    */
	अणु 0x1e, KEY_VOLUMEUP पूर्ण,		/* volume +    */
	अणु 0x14, KEY_F1 पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list proteus_2309_map = अणु
	.map = अणु
		.scan     = proteus_2309,
		.size     = ARRAY_SIZE(proteus_2309),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_PROTEUS_2309,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_proteus_2309(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&proteus_2309_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_proteus_2309(व्योम)
अणु
	rc_map_unरेजिस्टर(&proteus_2309_map);
पूर्ण

module_init(init_rc_map_proteus_2309)
module_निकास(निकास_rc_map_proteus_2309)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
