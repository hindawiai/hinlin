<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// em-terratec.h - Keytable क्रम em_terratec Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table em_terratec[] = अणु
	अणु 0x01, KEY_CHANNEL पूर्ण,
	अणु 0x02, KEY_SELECT पूर्ण,
	अणु 0x03, KEY_MUTE पूर्ण,
	अणु 0x04, KEY_POWER पूर्ण,
	अणु 0x05, KEY_NUMERIC_1 पूर्ण,
	अणु 0x06, KEY_NUMERIC_2 पूर्ण,
	अणु 0x07, KEY_NUMERIC_3 पूर्ण,
	अणु 0x08, KEY_CHANNELUP पूर्ण,
	अणु 0x09, KEY_NUMERIC_4 पूर्ण,
	अणु 0x0a, KEY_NUMERIC_5 पूर्ण,
	अणु 0x0b, KEY_NUMERIC_6 पूर्ण,
	अणु 0x0c, KEY_CHANNELDOWN पूर्ण,
	अणु 0x0d, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0e, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0f, KEY_NUMERIC_9 पूर्ण,
	अणु 0x10, KEY_VOLUMEUP पूर्ण,
	अणु 0x11, KEY_NUMERIC_0 पूर्ण,
	अणु 0x12, KEY_MENU पूर्ण,
	अणु 0x13, KEY_PRINT पूर्ण,
	अणु 0x14, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x16, KEY_PAUSE पूर्ण,
	अणु 0x18, KEY_RECORD पूर्ण,
	अणु 0x19, KEY_REWIND पूर्ण,
	अणु 0x1a, KEY_PLAY पूर्ण,
	अणु 0x1b, KEY_FORWARD पूर्ण,
	अणु 0x1c, KEY_BACKSPACE पूर्ण,
	अणु 0x1e, KEY_STOP पूर्ण,
	अणु 0x40, KEY_ZOOM पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list em_terratec_map = अणु
	.map = अणु
		.scan     = em_terratec,
		.size     = ARRAY_SIZE(em_terratec),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_EM_TERRATEC,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_em_terratec(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&em_terratec_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_em_terratec(व्योम)
अणु
	rc_map_unरेजिस्टर(&em_terratec_map);
पूर्ण

module_init(init_rc_map_em_terratec)
module_निकास(निकास_rc_map_em_terratec)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
