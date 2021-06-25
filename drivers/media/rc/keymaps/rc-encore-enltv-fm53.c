<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// encore-enltv-fm53.h - Keytable क्रम encore_enltv_fm53 Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Encore ENLTV-FM v5.3
   Mauro Carvalho Chehab <mchehab@kernel.org>
 */

अटल काष्ठा rc_map_table encore_enltv_fm53[] = अणु
	अणु 0x10, KEY_POWER2पूर्ण,
	अणु 0x06, KEY_MUTEपूर्ण,

	अणु 0x09, KEY_NUMERIC_1पूर्ण,
	अणु 0x1d, KEY_NUMERIC_2पूर्ण,
	अणु 0x1f, KEY_NUMERIC_3पूर्ण,
	अणु 0x19, KEY_NUMERIC_4पूर्ण,
	अणु 0x1b, KEY_NUMERIC_5पूर्ण,
	अणु 0x11, KEY_NUMERIC_6पूर्ण,
	अणु 0x17, KEY_NUMERIC_7पूर्ण,
	अणु 0x12, KEY_NUMERIC_8पूर्ण,
	अणु 0x16, KEY_NUMERIC_9पूर्ण,
	अणु 0x48, KEY_NUMERIC_0पूर्ण,

	अणु 0x04, KEY_LISTपूर्ण,		/* -/-- */
	अणु 0x40, KEY_LASTपूर्ण,		/* recall */

	अणु 0x02, KEY_MODEपूर्ण,		/* TV/AV */
	अणु 0x05, KEY_CAMERAपूर्ण,		/* SNAPSHOT */

	अणु 0x4c, KEY_CHANNELUPपूर्ण,		/* UP */
	अणु 0x00, KEY_CHANNELDOWNपूर्ण,	/* DOWN */
	अणु 0x0d, KEY_VOLUMEUPपूर्ण,		/* RIGHT */
	अणु 0x15, KEY_VOLUMEDOWNपूर्ण,	/* LEFT */
	अणु 0x49, KEY_ENTERपूर्ण,		/* OK */

	अणु 0x54, KEY_RECORDपूर्ण,
	अणु 0x4d, KEY_PLAYपूर्ण,		/* छोड़ो */

	अणु 0x1e, KEY_MENUपूर्ण,		/* video setting */
	अणु 0x0e, KEY_RIGHTपूर्ण,		/* <- */
	अणु 0x1a, KEY_LEFTपूर्ण,		/* -> */

	अणु 0x0a, KEY_CLEARपूर्ण,		/* video शेष */
	अणु 0x0c, KEY_ZOOMपूर्ण,		/* hide pannel */
	अणु 0x47, KEY_SLEEPपूर्ण,		/* shutकरोwn */
पूर्ण;

अटल काष्ठा rc_map_list encore_enltv_fm53_map = अणु
	.map = अणु
		.scan     = encore_enltv_fm53,
		.size     = ARRAY_SIZE(encore_enltv_fm53),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_ENCORE_ENLTV_FM53,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_encore_enltv_fm53(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&encore_enltv_fm53_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_encore_enltv_fm53(व्योम)
अणु
	rc_map_unरेजिस्टर(&encore_enltv_fm53_map);
पूर्ण

module_init(init_rc_map_encore_enltv_fm53)
module_निकास(निकास_rc_map_encore_enltv_fm53)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
