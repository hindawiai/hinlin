<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// avermedia.h - Keytable क्रम avermedia Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Alex Hermann <gaaf@gmx.net> */

अटल काष्ठा rc_map_table avermedia[] = अणु
	अणु 0x28, KEY_NUMERIC_1 पूर्ण,
	अणु 0x18, KEY_NUMERIC_2 पूर्ण,
	अणु 0x38, KEY_NUMERIC_3 पूर्ण,
	अणु 0x24, KEY_NUMERIC_4 पूर्ण,
	अणु 0x14, KEY_NUMERIC_5 पूर्ण,
	अणु 0x34, KEY_NUMERIC_6 पूर्ण,
	अणु 0x2c, KEY_NUMERIC_7 पूर्ण,
	अणु 0x1c, KEY_NUMERIC_8 पूर्ण,
	अणु 0x3c, KEY_NUMERIC_9 पूर्ण,
	अणु 0x22, KEY_NUMERIC_0 पूर्ण,

	अणु 0x20, KEY_TV पूर्ण,		/* TV/FM */
	अणु 0x10, KEY_CD पूर्ण,		/* CD */
	अणु 0x30, KEY_TEXT पूर्ण,		/* TELETEXT */
	अणु 0x00, KEY_POWER पूर्ण,		/* POWER */

	अणु 0x08, KEY_VIDEO पूर्ण,		/* VIDEO */
	अणु 0x04, KEY_AUDIO पूर्ण,		/* AUDIO */
	अणु 0x0c, KEY_ZOOM पूर्ण,		/* FULL SCREEN */

	अणु 0x12, KEY_SUBTITLE पूर्ण,		/* DISPLAY */
	अणु 0x32, KEY_REWIND पूर्ण,		/* LOOP	*/
	अणु 0x02, KEY_PRINT पूर्ण,		/* PREVIEW */

	अणु 0x2a, KEY_SEARCH पूर्ण,		/* AUTOSCAN */
	अणु 0x1a, KEY_SLEEP पूर्ण,		/* FREEZE */
	अणु 0x3a, KEY_CAMERA पूर्ण,		/* SNAPSHOT */
	अणु 0x0a, KEY_MUTE पूर्ण,		/* MUTE */

	अणु 0x26, KEY_RECORD पूर्ण,		/* RECORD */
	अणु 0x16, KEY_PAUSE पूर्ण,		/* PAUSE */
	अणु 0x36, KEY_STOP पूर्ण,		/* STOP */
	अणु 0x06, KEY_PLAY पूर्ण,		/* PLAY */

	अणु 0x2e, KEY_RED पूर्ण,		/* RED */
	अणु 0x21, KEY_GREEN पूर्ण,		/* GREEN */
	अणु 0x0e, KEY_YELLOW पूर्ण,		/* YELLOW */
	अणु 0x01, KEY_BLUE पूर्ण,		/* BLUE */

	अणु 0x1e, KEY_VOLUMEDOWN पूर्ण,	/* VOLUME- */
	अणु 0x3e, KEY_VOLUMEUP पूर्ण,		/* VOLUME+ */
	अणु 0x11, KEY_CHANNELDOWN पूर्ण,	/* CHANNEL/PAGE- */
	अणु 0x31, KEY_CHANNELUP पूर्ण		/* CHANNEL/PAGE+ */
पूर्ण;

अटल काष्ठा rc_map_list avermedia_map = अणु
	.map = अणु
		.scan     = avermedia,
		.size     = ARRAY_SIZE(avermedia),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_AVERMEDIA,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_avermedia(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&avermedia_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_avermedia(व्योम)
अणु
	rc_map_unरेजिस्टर(&avermedia_map);
पूर्ण

module_init(init_rc_map_avermedia)
module_निकास(निकास_rc_map_avermedia)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
