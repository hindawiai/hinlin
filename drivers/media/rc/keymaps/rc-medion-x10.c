<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Medion X10 RF remote keytable
 *
 * Copyright (C) 2011 Anssi Hannula <anssi.hannula@?ki.fi>
 *
 * This file is based on a keytable provided by
 * Jan Losinski <losinski@wh2.tu-dresden.de>
 */

#समावेश <linux/module.h>
#समावेश <media/rc-map.h>

अटल काष्ठा rc_map_table medion_x10[] = अणु
	अणु 0x2c, KEY_TV पूर्ण,    /* TV */
	अणु 0x2d, KEY_VCR पूर्ण,   /* VCR */
	अणु 0x04, KEY_DVD पूर्ण,   /* DVD */
	अणु 0x06, KEY_AUDIO पूर्ण, /* MUSIC */

	अणु 0x2e, KEY_RADIO पूर्ण,     /* RADIO */
	अणु 0x05, KEY_सूचीECTORY पूर्ण, /* PHOTO */
	अणु 0x2f, KEY_INFO पूर्ण,      /* TV-PREVIEW */
	अणु 0x30, KEY_LIST पूर्ण,      /* CHANNEL-LST */

	अणु 0x1b, KEY_SETUP पूर्ण, /* SETUP */
	अणु 0x31, KEY_VIDEO पूर्ण, /* VIDEO DESKTOP */

	अणु 0x08, KEY_VOLUMEDOWN पूर्ण,  /* VOL - */
	अणु 0x09, KEY_VOLUMEUP पूर्ण,    /* VOL + */
	अणु 0x0b, KEY_CHANNELUP पूर्ण,   /* CHAN + */
	अणु 0x0c, KEY_CHANNELDOWN पूर्ण, /* CHAN - */
	अणु 0x00, KEY_MUTE पूर्ण,        /* MUTE */

	अणु 0x32, KEY_RED पूर्ण, /* red */
	अणु 0x33, KEY_GREEN पूर्ण, /* green */
	अणु 0x34, KEY_YELLOW पूर्ण, /* yellow */
	अणु 0x35, KEY_BLUE पूर्ण, /* blue */
	अणु 0x16, KEY_TEXT पूर्ण, /* TXT */

	अणु 0x0d, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0e, KEY_NUMERIC_2 पूर्ण,
	अणु 0x0f, KEY_NUMERIC_3 पूर्ण,
	अणु 0x10, KEY_NUMERIC_4 पूर्ण,
	अणु 0x11, KEY_NUMERIC_5 पूर्ण,
	अणु 0x12, KEY_NUMERIC_6 पूर्ण,
	अणु 0x13, KEY_NUMERIC_7 पूर्ण,
	अणु 0x14, KEY_NUMERIC_8 पूर्ण,
	अणु 0x15, KEY_NUMERIC_9 पूर्ण,
	अणु 0x17, KEY_NUMERIC_0 पूर्ण,
	अणु 0x1c, KEY_SEARCH पूर्ण, /* TV/RAD, CH SRC */
	अणु 0x20, KEY_DELETE पूर्ण, /* DELETE */

	अणु 0x36, KEY_KEYBOARD पूर्ण, /* RENAME */
	अणु 0x18, KEY_SCREEN पूर्ण,   /* SNAPSHOT */

	अणु 0x1a, KEY_UP पूर्ण,    /* up */
	अणु 0x22, KEY_DOWN पूर्ण,  /* करोwn */
	अणु 0x1d, KEY_LEFT पूर्ण,  /* left */
	अणु 0x1f, KEY_RIGHT पूर्ण, /* right */
	अणु 0x1e, KEY_OK पूर्ण,    /* OK */

	अणु 0x37, KEY_SELECT पूर्ण, /* ACQUIRE IMAGE */
	अणु 0x38, KEY_EDIT पूर्ण,   /* EDIT IMAGE */

	अणु 0x24, KEY_REWIND पूर्ण,   /* शुरुआत  (<<) */
	अणु 0x25, KEY_PLAY पूर्ण,     /* play    ( >) */
	अणु 0x26, KEY_FORWARD पूर्ण,  /* क्रमward (>>) */
	अणु 0x27, KEY_RECORD पूर्ण,   /* record  ( o) */
	अणु 0x28, KEY_STOP पूर्ण,     /* stop    ([]) */
	अणु 0x29, KEY_PAUSE पूर्ण,    /* छोड़ो   ('') */

	अणु 0x21, KEY_PREVIOUS पूर्ण,        /* prev */
	अणु 0x39, KEY_SWITCHVIDEOMODE पूर्ण, /* F SCR */
	अणु 0x23, KEY_NEXT पूर्ण,            /* next */
	अणु 0x19, KEY_MENU पूर्ण,            /* MENU */
	अणु 0x3a, KEY_LANGUAGE पूर्ण,        /* AUDIO */

	अणु 0x02, KEY_POWER पूर्ण, /* POWER */
पूर्ण;

अटल काष्ठा rc_map_list medion_x10_map = अणु
	.map = अणु
		.scan     = medion_x10,
		.size     = ARRAY_SIZE(medion_x10),
		.rc_proto = RC_PROTO_OTHER,
		.name     = RC_MAP_MEDION_X10,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_medion_x10(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&medion_x10_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_medion_x10(व्योम)
अणु
	rc_map_unरेजिस्टर(&medion_x10_map);
पूर्ण

module_init(init_rc_map_medion_x10)
module_निकास(निकास_rc_map_medion_x10)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anssi Hannula <anssi.hannula@iki.fi>");
