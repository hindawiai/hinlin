<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// pinnacle-pctv-hd.h - Keytable क्रम pinnacle_pctv_hd Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Pinnacle PCTV HD 800i mini remote */

अटल काष्ठा rc_map_table pinnacle_pctv_hd[] = अणु
	/* Key codes क्रम the tiny Pinnacle remote*/
	अणु 0x0700, KEY_MUTE पूर्ण,
	अणु 0x0701, KEY_MENU पूर्ण, /* Pinnacle logo */
	अणु 0x0739, KEY_POWER पूर्ण,
	अणु 0x0703, KEY_VOLUMEUP पूर्ण,
	अणु 0x0705, KEY_OK पूर्ण,
	अणु 0x0709, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x0706, KEY_CHANNELUP पूर्ण,
	अणु 0x070c, KEY_CHANNELDOWN पूर्ण,
	अणु 0x070f, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0715, KEY_NUMERIC_2 पूर्ण,
	अणु 0x0710, KEY_NUMERIC_3 पूर्ण,
	अणु 0x0718, KEY_NUMERIC_4 पूर्ण,
	अणु 0x071b, KEY_NUMERIC_5 पूर्ण,
	अणु 0x071e, KEY_NUMERIC_6 पूर्ण,
	अणु 0x0711, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0721, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0712, KEY_NUMERIC_9 पूर्ण,
	अणु 0x0727, KEY_NUMERIC_0 पूर्ण,
	अणु 0x0724, KEY_ZOOM पूर्ण, /* 'Square' key */
	अणु 0x072a, KEY_SUBTITLE पूर्ण,   /* 'T' key */
	अणु 0x072d, KEY_REWIND पूर्ण,
	अणु 0x0730, KEY_PLAYPAUSE पूर्ण,
	अणु 0x0733, KEY_FASTFORWARD पूर्ण,
	अणु 0x0736, KEY_RECORD पूर्ण,
	अणु 0x073c, KEY_STOP पूर्ण,
	अणु 0x073f, KEY_HELP पूर्ण, /* '?' key */
पूर्ण;

अटल काष्ठा rc_map_list pinnacle_pctv_hd_map = अणु
	.map = अणु
		.scan     = pinnacle_pctv_hd,
		.size     = ARRAY_SIZE(pinnacle_pctv_hd),
		.rc_proto = RC_PROTO_RC5,
		.name     = RC_MAP_PINNACLE_PCTV_HD,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_pinnacle_pctv_hd(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&pinnacle_pctv_hd_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_pinnacle_pctv_hd(व्योम)
अणु
	rc_map_unरेजिस्टर(&pinnacle_pctv_hd_map);
पूर्ण

module_init(init_rc_map_pinnacle_pctv_hd)
module_निकास(निकास_rc_map_pinnacle_pctv_hd)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
