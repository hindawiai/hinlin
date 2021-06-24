<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// घातercolor-real-angel.h - Keytable क्रम घातercolor_real_angel Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/*
 * Remote control क्रम Powercolor Real Angel 330
 * Daniel Fraga <fragabr@gmail.com>
 */

अटल काष्ठा rc_map_table घातercolor_real_angel[] = अणु
	अणु 0x38, KEY_SWITCHVIDEOMODE पूर्ण,	/* चयन inमाला_दो */
	अणु 0x0c, KEY_MEDIA पूर्ण,		/* Turn ON/OFF App */
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
	अणु 0x0a, KEY_DIGITS पूर्ण,		/* single, द्विगुन, triple digit */
	अणु 0x29, KEY_PREVIOUS पूर्ण,		/* previous channel */
	अणु 0x12, KEY_BRIGHTNESSUP पूर्ण,
	अणु 0x13, KEY_BRIGHTNESSDOWN पूर्ण,
	अणु 0x2b, KEY_MODE पूर्ण,		/* stereo/mono */
	अणु 0x2c, KEY_TEXT पूर्ण,		/* teletext */
	अणु 0x20, KEY_CHANNELUP पूर्ण,	/* channel up */
	अणु 0x21, KEY_CHANNELDOWN पूर्ण,	/* channel करोwn */
	अणु 0x10, KEY_VOLUMEUP पूर्ण,		/* volume up */
	अणु 0x11, KEY_VOLUMEDOWN पूर्ण,	/* volume करोwn */
	अणु 0x0d, KEY_MUTE पूर्ण,
	अणु 0x1f, KEY_RECORD पूर्ण,
	अणु 0x17, KEY_PLAY पूर्ण,
	अणु 0x16, KEY_PAUSE पूर्ण,
	अणु 0x0b, KEY_STOP पूर्ण,
	अणु 0x27, KEY_FASTFORWARD पूर्ण,
	अणु 0x26, KEY_REWIND पूर्ण,
	अणु 0x1e, KEY_SEARCH पूर्ण,		/* स्वतःscan */
	अणु 0x0e, KEY_CAMERA पूर्ण,		/* snapshot */
	अणु 0x2d, KEY_SETUP पूर्ण,
	अणु 0x0f, KEY_SCREEN पूर्ण,		/* full screen */
	अणु 0x14, KEY_RADIO पूर्ण,		/* FM radio */
	अणु 0x25, KEY_POWER पूर्ण,		/* घातer */
पूर्ण;

अटल काष्ठा rc_map_list घातercolor_real_angel_map = अणु
	.map = अणु
		.scan     = घातercolor_real_angel,
		.size     = ARRAY_SIZE(घातercolor_real_angel),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_POWERCOLOR_REAL_ANGEL,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_घातercolor_real_angel(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&घातercolor_real_angel_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_घातercolor_real_angel(व्योम)
अणु
	rc_map_unरेजिस्टर(&घातercolor_real_angel_map);
पूर्ण

module_init(init_rc_map_घातercolor_real_angel)
module_निकास(निकास_rc_map_घातercolor_real_angel)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
