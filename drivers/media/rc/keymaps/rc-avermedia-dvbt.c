<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// avermedia-dvbt.h - Keytable क्रम avermedia_dvbt Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Matt Jesson <dvb@jesson.eclipse.co.uk */

अटल काष्ठा rc_map_table avermedia_dvbt[] = अणु
	अणु 0x28, KEY_NUMERIC_0 पूर्ण,	/* '0' / 'enter' */
	अणु 0x22, KEY_NUMERIC_1 पूर्ण,	/* '1' */
	अणु 0x12, KEY_NUMERIC_2 पूर्ण,	/* '2' / 'up arrow' */
	अणु 0x32, KEY_NUMERIC_3 पूर्ण,	/* '3' */
	अणु 0x24, KEY_NUMERIC_4 पूर्ण,	/* '4' / 'left arrow' */
	अणु 0x14, KEY_NUMERIC_5 पूर्ण,	/* '5' */
	अणु 0x34, KEY_NUMERIC_6 पूर्ण,	/* '6' / 'right arrow' */
	अणु 0x26, KEY_NUMERIC_7 पूर्ण,	/* '7' */
	अणु 0x16, KEY_NUMERIC_8 पूर्ण,	/* '8' / 'down arrow' */
	अणु 0x36, KEY_NUMERIC_9 पूर्ण,	/* '9' */

	अणु 0x20, KEY_VIDEO पूर्ण,		/* 'source' */
	अणु 0x10, KEY_TEXT पूर्ण,		/* 'teletext' */
	अणु 0x00, KEY_POWER पूर्ण,		/* 'power' */
	अणु 0x04, KEY_AUDIO पूर्ण,		/* 'audio' */
	अणु 0x06, KEY_ZOOM पूर्ण,		/* 'full screen' */
	अणु 0x18, KEY_SWITCHVIDEOMODE पूर्ण,	/* 'display' */
	अणु 0x38, KEY_SEARCH पूर्ण,		/* 'loop' */
	अणु 0x08, KEY_INFO पूर्ण,		/* 'preview' */
	अणु 0x2a, KEY_REWIND पूर्ण,		/* 'backward <<' */
	अणु 0x1a, KEY_FASTFORWARD पूर्ण,	/* 'forward >>' */
	अणु 0x3a, KEY_RECORD पूर्ण,		/* 'capture' */
	अणु 0x0a, KEY_MUTE पूर्ण,		/* 'mute' */
	अणु 0x2c, KEY_RECORD पूर्ण,		/* 'record' */
	अणु 0x1c, KEY_PAUSE पूर्ण,		/* 'pause' */
	अणु 0x3c, KEY_STOP पूर्ण,		/* 'stop' */
	अणु 0x0c, KEY_PLAY पूर्ण,		/* 'play' */
	अणु 0x2e, KEY_RED पूर्ण,		/* 'red' */
	अणु 0x01, KEY_BLUE पूर्ण,		/* 'blue' / 'cancel' */
	अणु 0x0e, KEY_YELLOW पूर्ण,		/* 'yellow' / 'ok' */
	अणु 0x21, KEY_GREEN पूर्ण,		/* 'green' */
	अणु 0x11, KEY_CHANNELDOWN पूर्ण,	/* 'channel -' */
	अणु 0x31, KEY_CHANNELUP पूर्ण,	/* 'channel +' */
	अणु 0x1e, KEY_VOLUMEDOWN पूर्ण,	/* 'volume -' */
	अणु 0x3e, KEY_VOLUMEUP पूर्ण,		/* 'volume +' */
पूर्ण;

अटल काष्ठा rc_map_list avermedia_dvbt_map = अणु
	.map = अणु
		.scan     = avermedia_dvbt,
		.size     = ARRAY_SIZE(avermedia_dvbt),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_AVERMEDIA_DVBT,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_avermedia_dvbt(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&avermedia_dvbt_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_avermedia_dvbt(व्योम)
अणु
	rc_map_unरेजिस्टर(&avermedia_dvbt_map);
पूर्ण

module_init(init_rc_map_avermedia_dvbt)
module_निकास(निकास_rc_map_avermedia_dvbt)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
