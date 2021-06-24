<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// avermedia-a16d.h - Keytable क्रम avermedia_a16d Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table avermedia_a16d[] = अणु
	अणु 0x20, KEY_LISTपूर्ण,
	अणु 0x00, KEY_POWERपूर्ण,
	अणु 0x28, KEY_NUMERIC_1पूर्ण,
	अणु 0x18, KEY_NUMERIC_2पूर्ण,
	अणु 0x38, KEY_NUMERIC_3पूर्ण,
	अणु 0x24, KEY_NUMERIC_4पूर्ण,
	अणु 0x14, KEY_NUMERIC_5पूर्ण,
	अणु 0x34, KEY_NUMERIC_6पूर्ण,
	अणु 0x2c, KEY_NUMERIC_7पूर्ण,
	अणु 0x1c, KEY_NUMERIC_8पूर्ण,
	अणु 0x3c, KEY_NUMERIC_9पूर्ण,
	अणु 0x12, KEY_SUBTITLEपूर्ण,
	अणु 0x22, KEY_NUMERIC_0पूर्ण,
	अणु 0x32, KEY_REWINDपूर्ण,
	अणु 0x3a, KEY_SHUFFLEपूर्ण,
	अणु 0x02, KEY_PRINTपूर्ण,
	अणु 0x11, KEY_CHANNELDOWNपूर्ण,
	अणु 0x31, KEY_CHANNELUPपूर्ण,
	अणु 0x0c, KEY_ZOOMपूर्ण,
	अणु 0x1e, KEY_VOLUMEDOWNपूर्ण,
	अणु 0x3e, KEY_VOLUMEUPपूर्ण,
	अणु 0x0a, KEY_MUTEपूर्ण,
	अणु 0x04, KEY_AUDIOपूर्ण,
	अणु 0x26, KEY_RECORDपूर्ण,
	अणु 0x06, KEY_PLAYपूर्ण,
	अणु 0x36, KEY_STOPपूर्ण,
	अणु 0x16, KEY_PAUSEपूर्ण,
	अणु 0x2e, KEY_REWINDपूर्ण,
	अणु 0x0e, KEY_FASTFORWARDपूर्ण,
	अणु 0x30, KEY_TEXTपूर्ण,
	अणु 0x21, KEY_GREENपूर्ण,
	अणु 0x01, KEY_BLUEपूर्ण,
	अणु 0x08, KEY_EPGपूर्ण,
	अणु 0x2a, KEY_MENUपूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list avermedia_a16d_map = अणु
	.map = अणु
		.scan     = avermedia_a16d,
		.size     = ARRAY_SIZE(avermedia_a16d),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_AVERMEDIA_A16D,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_avermedia_a16d(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&avermedia_a16d_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_avermedia_a16d(व्योम)
अणु
	rc_map_unरेजिस्टर(&avermedia_a16d_map);
पूर्ण

module_init(init_rc_map_avermedia_a16d)
module_निकास(निकास_rc_map_avermedia_a16d)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
