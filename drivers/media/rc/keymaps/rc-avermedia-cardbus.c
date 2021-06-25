<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// avermedia-cardbus.h - Keytable क्रम avermedia_cardbus Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Oldrich Jedlicka <oldium.pro@seznam.cz> */

अटल काष्ठा rc_map_table avermedia_cardbus[] = अणु
	अणु 0x00, KEY_POWER पूर्ण,
	अणु 0x01, KEY_TUNER पूर्ण,		/* TV/FM */
	अणु 0x03, KEY_TEXT पूर्ण,		/* Teletext */
	अणु 0x04, KEY_EPG पूर्ण,
	अणु 0x05, KEY_NUMERIC_1 पूर्ण,
	अणु 0x06, KEY_NUMERIC_2 पूर्ण,
	अणु 0x07, KEY_NUMERIC_3 पूर्ण,
	अणु 0x08, KEY_AUDIO पूर्ण,
	अणु 0x09, KEY_NUMERIC_4 पूर्ण,
	अणु 0x0a, KEY_NUMERIC_5 पूर्ण,
	अणु 0x0b, KEY_NUMERIC_6 पूर्ण,
	अणु 0x0c, KEY_ZOOM पूर्ण,		/* Full screen */
	अणु 0x0d, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0e, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0f, KEY_NUMERIC_9 पूर्ण,
	अणु 0x10, KEY_PAGEUP पूर्ण,		/* 16-CH PREV */
	अणु 0x11, KEY_NUMERIC_0 पूर्ण,
	अणु 0x12, KEY_INFO पूर्ण,
	अणु 0x13, KEY_AGAIN पूर्ण,		/* CH RTN - channel वापस */
	अणु 0x14, KEY_MUTE पूर्ण,
	अणु 0x15, KEY_EDIT पूर्ण,		/* Autoscan */
	अणु 0x17, KEY_SAVE पूर्ण,		/* Screenshot */
	अणु 0x18, KEY_PLAYPAUSE पूर्ण,
	अणु 0x19, KEY_RECORD पूर्ण,
	अणु 0x1a, KEY_PLAY पूर्ण,
	अणु 0x1b, KEY_STOP पूर्ण,
	अणु 0x1c, KEY_FASTFORWARD पूर्ण,
	अणु 0x1d, KEY_REWIND पूर्ण,
	अणु 0x1e, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x1f, KEY_VOLUMEUP पूर्ण,
	अणु 0x22, KEY_SLEEP पूर्ण,		/* Sleep */
	अणु 0x23, KEY_ZOOM पूर्ण,		/* Aspect */
	अणु 0x26, KEY_SCREEN पूर्ण,		/* Pos */
	अणु 0x27, KEY_ANGLE पूर्ण,		/* Size */
	अणु 0x28, KEY_SELECT पूर्ण,		/* Select */
	अणु 0x29, KEY_BLUE पूर्ण,		/* Blue/Picture */
	अणु 0x2a, KEY_BACKSPACE पूर्ण,	/* Back */
	अणु 0x2b, KEY_VIDEO पूर्ण,		/* PIP (Picture-in-picture) */
	अणु 0x2c, KEY_DOWN पूर्ण,
	अणु 0x2e, KEY_DOT पूर्ण,
	अणु 0x2f, KEY_TV पूर्ण,		/* Live TV */
	अणु 0x32, KEY_LEFT पूर्ण,
	अणु 0x33, KEY_CLEAR पूर्ण,		/* Clear */
	अणु 0x35, KEY_RED पूर्ण,		/* Red/TV */
	अणु 0x36, KEY_UP पूर्ण,
	अणु 0x37, KEY_HOME पूर्ण,		/* Home */
	अणु 0x39, KEY_GREEN पूर्ण,		/* Green/Video */
	अणु 0x3d, KEY_YELLOW पूर्ण,		/* Yellow/Music */
	अणु 0x3e, KEY_OK पूर्ण,		/* Ok */
	अणु 0x3f, KEY_RIGHT पूर्ण,
	अणु 0x40, KEY_NEXT पूर्ण,		/* Next */
	अणु 0x41, KEY_PREVIOUS पूर्ण,		/* Previous */
	अणु 0x42, KEY_CHANNELDOWN पूर्ण,	/* Channel करोwn */
	अणु 0x43, KEY_CHANNELUP पूर्ण,	/* Channel up */
पूर्ण;

अटल काष्ठा rc_map_list avermedia_cardbus_map = अणु
	.map = अणु
		.scan     = avermedia_cardbus,
		.size     = ARRAY_SIZE(avermedia_cardbus),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_AVERMEDIA_CARDBUS,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_avermedia_cardbus(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&avermedia_cardbus_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_avermedia_cardbus(व्योम)
अणु
	rc_map_unरेजिस्टर(&avermedia_cardbus_map);
पूर्ण

module_init(init_rc_map_avermedia_cardbus)
module_निकास(निकास_rc_map_avermedia_cardbus)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
