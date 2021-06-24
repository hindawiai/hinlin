<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// kaiomy.h - Keytable क्रम kaiomy Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Kaiomy TVnPC U2
   Mauro Carvalho Chehab <mchehab@kernel.org>
 */

अटल काष्ठा rc_map_table kaiomy[] = अणु
	अणु 0x43, KEY_POWER2पूर्ण,
	अणु 0x01, KEY_LISTपूर्ण,
	अणु 0x0b, KEY_ZOOMपूर्ण,
	अणु 0x03, KEY_POWERपूर्ण,

	अणु 0x04, KEY_NUMERIC_1पूर्ण,
	अणु 0x08, KEY_NUMERIC_2पूर्ण,
	अणु 0x02, KEY_NUMERIC_3पूर्ण,

	अणु 0x0f, KEY_NUMERIC_4पूर्ण,
	अणु 0x05, KEY_NUMERIC_5पूर्ण,
	अणु 0x06, KEY_NUMERIC_6पूर्ण,

	अणु 0x0c, KEY_NUMERIC_7पूर्ण,
	अणु 0x0d, KEY_NUMERIC_8पूर्ण,
	अणु 0x0a, KEY_NUMERIC_9पूर्ण,

	अणु 0x11, KEY_NUMERIC_0पूर्ण,

	अणु 0x09, KEY_CHANNELUPपूर्ण,
	अणु 0x07, KEY_CHANNELDOWNपूर्ण,

	अणु 0x0e, KEY_VOLUMEUPपूर्ण,
	अणु 0x13, KEY_VOLUMEDOWNपूर्ण,

	अणु 0x10, KEY_HOMEपूर्ण,
	अणु 0x12, KEY_ENTERपूर्ण,

	अणु 0x14, KEY_RECORDपूर्ण,
	अणु 0x15, KEY_STOPपूर्ण,
	अणु 0x16, KEY_PLAYपूर्ण,
	अणु 0x17, KEY_MUTEपूर्ण,

	अणु 0x18, KEY_UPपूर्ण,
	अणु 0x19, KEY_DOWNपूर्ण,
	अणु 0x1a, KEY_LEFTपूर्ण,
	अणु 0x1b, KEY_RIGHTपूर्ण,

	अणु 0x1c, KEY_REDपूर्ण,
	अणु 0x1d, KEY_GREENपूर्ण,
	अणु 0x1e, KEY_YELLOWपूर्ण,
	अणु 0x1f, KEY_BLUEपूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list kaiomy_map = अणु
	.map = अणु
		.scan     = kaiomy,
		.size     = ARRAY_SIZE(kaiomy),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_KAIOMY,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_kaiomy(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&kaiomy_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_kaiomy(व्योम)
अणु
	rc_map_unरेजिस्टर(&kaiomy_map);
पूर्ण

module_init(init_rc_map_kaiomy)
module_निकास(निकास_rc_map_kaiomy)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
