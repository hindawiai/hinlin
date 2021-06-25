<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ATI X10 RF remote keytable
 *
 * Copyright (C) 2011 Anssi Hannula <anssi.hannula@?ki.fi>
 *
 * This file is based on the अटल generic keytable previously found in
 * ati_remote.c, which is
 * Copyright (c) 2004 Torrey Hoffman <thoffman@arnor.net>
 * Copyright (c) 2002 Vladimir Dergachev
 */

#समावेश <linux/module.h>
#समावेश <media/rc-map.h>

/*
 * Intended usage comments below are from venकरोr-supplied
 * Source: ATI REMOTE WONDERैं Installation Guide
 * http://www2.ati.com/manuals/remctrl.pdf
 *
 * Scancodes were in strict left-right, top-bottom order on the
 * original ATI Remote Wonder, but were moved on later models.
 *
 * Keys A-F are पूर्णांकended to be user-programmable.
 */

अटल काष्ठा rc_map_table ati_x10[] = अणु
	/* keyboard - Above the cursor pad */
	अणु 0x00, KEY_A पूर्ण,
	अणु 0x01, KEY_B पूर्ण,
	अणु 0x02, KEY_POWER पूर्ण,      /* Power */

	अणु 0x03, KEY_TV पूर्ण,         /* TV */
	अणु 0x04, KEY_DVD पूर्ण,        /* DVD */
	अणु 0x05, KEY_WWW पूर्ण,        /* WEB */
	अणु 0x06, KEY_BOOKMARKS पूर्ण,  /* "book": Open Media Library */
	अणु 0x07, KEY_EDIT पूर्ण,       /* "hand": Toggle left mouse button (grab) */

	/* Mouse emulation pad goes here, handled by driver separately */

	अणु 0x09, KEY_VOLUMEDOWN पूर्ण, /* VOL + */
	अणु 0x08, KEY_VOLUMEUP पूर्ण,   /* VOL - */
	अणु 0x0a, KEY_MUTE पूर्ण,       /* MUTE  */
	अणु 0x0b, KEY_CHANNELUP पूर्ण,  /* CH + */
	अणु 0x0c, KEY_CHANNELDOWN पूर्ण,/* CH - */

	/*
	 * We could use KEY_NUMERIC_x क्रम these, but the X11 protocol
	 * has problems with keycodes greater than 255, so aव्योम those high
	 * keycodes in शेष maps.
	 */
	अणु 0x0d, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0e, KEY_NUMERIC_2 पूर्ण,
	अणु 0x0f, KEY_NUMERIC_3 पूर्ण,
	अणु 0x10, KEY_NUMERIC_4 पूर्ण,
	अणु 0x11, KEY_NUMERIC_5 पूर्ण,
	अणु 0x12, KEY_NUMERIC_6 पूर्ण,
	अणु 0x13, KEY_NUMERIC_7 पूर्ण,
	अणु 0x14, KEY_NUMERIC_8 पूर्ण,
	अणु 0x15, KEY_NUMERIC_9 पूर्ण,
	अणु 0x16, KEY_MENU पूर्ण,       /* "menu": DVD root menu */
				  /* KEY_NUMERIC_STAR? */
	अणु 0x17, KEY_NUMERIC_0 पूर्ण,
	अणु 0x18, KEY_SETUP पूर्ण,      /* "check": DVD setup menu */
				  /* KEY_NUMERIC_POUND? */

	/* DVD navigation buttons */
	अणु 0x19, KEY_C पूर्ण,
	अणु 0x1a, KEY_UP पूर्ण,         /* up */
	अणु 0x1b, KEY_D पूर्ण,

	अणु 0x1c, KEY_PROPS पूर्ण,      /* "timer" Should be Data On Screen */
				  /* Symbol is "circle nailed to box" */
	अणु 0x1d, KEY_LEFT पूर्ण,       /* left */
	अणु 0x1e, KEY_OK पूर्ण,         /* "OK" */
	अणु 0x1f, KEY_RIGHT पूर्ण,      /* right */
	अणु 0x20, KEY_SCREEN पूर्ण,     /* "max" (X11 warning: 0x177) */
				  /* Should be AC View Toggle, but
				     that's not in <input/input.h>.
				     KEY_ZOOM (0x174)? */
	अणु 0x21, KEY_E पूर्ण,
	अणु 0x22, KEY_DOWN पूर्ण,       /* करोwn */
	अणु 0x23, KEY_F पूर्ण,
	/* Play/stop/छोड़ो buttons */
	अणु 0x24, KEY_REWIND पूर्ण,     /* (<<) Rewind */
	अणु 0x25, KEY_PLAY पूर्ण,       /* ( >) Play (KEY_PLAYCD?) */
	अणु 0x26, KEY_FASTFORWARD पूर्ण, /* (>>) Fast क्रमward */

	अणु 0x27, KEY_RECORD पूर्ण,     /* ( o) red */
	अणु 0x28, KEY_STOPCD पूर्ण,     /* ([]) Stop  (KEY_STOP is something अन्यथा!) */
	अणु 0x29, KEY_PAUSE पूर्ण,      /* ('') Pause (KEY_PAUSECD?) */

	/* Extra keys, not on the original ATI remote */
	अणु 0x2a, KEY_NEXT पूर्ण,       /* (>+) */
	अणु 0x2b, KEY_PREVIOUS पूर्ण,   /* (<-) */
	अणु 0x2d, KEY_INFO पूर्ण,       /* PLAYING  (X11 warning: 0x166) */
	अणु 0x2e, KEY_HOME पूर्ण,       /* TOP */
	अणु 0x2f, KEY_END पूर्ण,        /* END */
	अणु 0x30, KEY_SELECT पूर्ण,     /* SELECT  (X11 warning: 0x161) */
पूर्ण;

अटल काष्ठा rc_map_list ati_x10_map = अणु
	.map = अणु
		.scan     = ati_x10,
		.size     = ARRAY_SIZE(ati_x10),
		.rc_proto = RC_PROTO_OTHER,
		.name     = RC_MAP_ATI_X10,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_ati_x10(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&ati_x10_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_ati_x10(व्योम)
अणु
	rc_map_unरेजिस्टर(&ati_x10_map);
पूर्ण

module_init(init_rc_map_ati_x10)
module_निकास(निकास_rc_map_ati_x10)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anssi Hannula <anssi.hannula@iki.fi>");
