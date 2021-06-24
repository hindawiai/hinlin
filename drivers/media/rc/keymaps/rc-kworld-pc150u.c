<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* kworld-pc150u.c - Keytable क्रम kworld_pc150u Remote Controller
 *
 * keymap imported from ir-keymaps.c
 *
 * Copyright (c) 2010 by Kyle Strickland
 *   (based on kworld-plus-tv-analog.c by
 *    Mauro Carvalho Chehab)
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Kworld PC150-U
   Kyle Strickland <kyle@kyle.strickland.name>
 */

अटल काष्ठा rc_map_table kworld_pc150u[] = अणु
	अणु 0x0c, KEY_MEDIA पूर्ण,		/* Kworld key */
	अणु 0x16, KEY_EJECTCLOSECD पूर्ण,	/* -> ) */
	अणु 0x1d, KEY_POWER2 पूर्ण,

	अणु 0x00, KEY_NUMERIC_1 पूर्ण,
	अणु 0x01, KEY_NUMERIC_2 पूर्ण,
	अणु 0x02, KEY_NUMERIC_3 पूर्ण,
	अणु 0x03, KEY_NUMERIC_4 पूर्ण,
	अणु 0x04, KEY_NUMERIC_5 पूर्ण,
	अणु 0x05, KEY_NUMERIC_6 पूर्ण,
	अणु 0x06, KEY_NUMERIC_7 पूर्ण,
	अणु 0x07, KEY_NUMERIC_8 पूर्ण,
	अणु 0x08, KEY_NUMERIC_9 पूर्ण,
	अणु 0x0a, KEY_NUMERIC_0 पूर्ण,

	अणु 0x09, KEY_AGAIN पूर्ण,
	अणु 0x14, KEY_MUTE पूर्ण,

	अणु 0x1e, KEY_LAST पूर्ण,
	अणु 0x17, KEY_ZOOM पूर्ण,
	अणु 0x1f, KEY_HOMEPAGE पूर्ण,
	अणु 0x0e, KEY_ESC पूर्ण,

	अणु 0x20, KEY_UP पूर्ण,
	अणु 0x21, KEY_DOWN पूर्ण,
	अणु 0x42, KEY_LEFT पूर्ण,
	अणु 0x43, KEY_RIGHT पूर्ण,
	अणु 0x0b, KEY_ENTER पूर्ण,

	अणु 0x10, KEY_CHANNELUP पूर्ण,
	अणु 0x11, KEY_CHANNELDOWN पूर्ण,

	अणु 0x13, KEY_VOLUMEUP पूर्ण,
	अणु 0x12, KEY_VOLUMEDOWN पूर्ण,

	अणु 0x19, KEY_TIMEपूर्ण,		/* Timeshअगरt */
	अणु 0x1a, KEY_STOPपूर्ण,
	अणु 0x1b, KEY_RECORDपूर्ण,
	अणु 0x4b, KEY_EMAILपूर्ण,

	अणु 0x40, KEY_REWINDपूर्ण,
	अणु 0x44, KEY_PLAYPAUSEपूर्ण,
	अणु 0x41, KEY_FORWARDपूर्ण,
	अणु 0x22, KEY_TEXTपूर्ण,

	अणु 0x15, KEY_AUDIOपूर्ण,		/* ((*)) */
	अणु 0x0f, KEY_MODEपूर्ण,		/* display ratio */
	अणु 0x1c, KEY_SYSRQपूर्ण,		/* snapshot */
	अणु 0x4a, KEY_SLEEPपूर्ण,		/* sleep समयr */

	अणु 0x48, KEY_SOUNDपूर्ण,		/* चयन theater mode */
	अणु 0x49, KEY_BLUEपूर्ण,		/* A */
	अणु 0x18, KEY_REDपूर्ण,		/* B */
	अणु 0x23, KEY_GREENपूर्ण,		/* C */
पूर्ण;

अटल काष्ठा rc_map_list kworld_pc150u_map = अणु
	.map = अणु
		.scan     = kworld_pc150u,
		.size     = ARRAY_SIZE(kworld_pc150u),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_KWORLD_PC150U,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_kworld_pc150u(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&kworld_pc150u_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_kworld_pc150u(व्योम)
अणु
	rc_map_unरेजिस्टर(&kworld_pc150u_map);
पूर्ण

module_init(init_rc_map_kworld_pc150u)
module_निकास(निकास_rc_map_kworld_pc150u)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kyle Strickland <kyle@kyle.strickland.name>");
