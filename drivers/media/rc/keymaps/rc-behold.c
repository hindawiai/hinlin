<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// behold.h - Keytable क्रम behold Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/*
 * Igor Kuznetsov <igk72@ya.ru>
 * Andrey J. Melnikov <temnota@kmv.ru>
 *
 * Keytable is used by BeholdTV 60x series, M6 series at
 * least, and probably other cards too.
 * The "ascii-art picture" below (in comments, first row
 * is the keycode in hex, and subsequent row(s) shows
 * the button labels (several variants when appropriate)
 * helps to decide which keycodes to assign to the buttons.
 */

अटल काष्ठा rc_map_table behold[] = अणु

	/*  0x1c            0x12  *
	 *  TV/FM          POWER  *
	 *                        */
	अणु 0x866b1c, KEY_TUNER पूर्ण,	/* XXX KEY_TV / KEY_RADIO */
	अणु 0x866b12, KEY_POWER पूर्ण,

	/*  0x01    0x02    0x03  *
	 *   1       2       3    *
	 *                        *
	 *  0x04    0x05    0x06  *
	 *   4       5       6    *
	 *                        *
	 *  0x07    0x08    0x09  *
	 *   7       8       9    *
	 *                        */
	अणु 0x866b01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x866b02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x866b03, KEY_NUMERIC_3 पूर्ण,
	अणु 0x866b04, KEY_NUMERIC_4 पूर्ण,
	अणु 0x866b05, KEY_NUMERIC_5 पूर्ण,
	अणु 0x866b06, KEY_NUMERIC_6 पूर्ण,
	अणु 0x866b07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x866b08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x866b09, KEY_NUMERIC_9 पूर्ण,

	/*  0x0a    0x00    0x17  *
	 * RECALL    0      MODE  *
	 *                        */
	अणु 0x866b0a, KEY_AGAIN पूर्ण,
	अणु 0x866b00, KEY_NUMERIC_0 पूर्ण,
	अणु 0x866b17, KEY_MODE पूर्ण,

	/*  0x14          0x10    *
	 * ASPECT      FULLSCREEN *
	 *                        */
	अणु 0x866b14, KEY_SCREEN पूर्ण,
	अणु 0x866b10, KEY_ZOOM पूर्ण,

	/*          0x0b          *
	 *           Up           *
	 *                        *
	 *  0x18    0x16    0x0c  *
	 *  Left     Ok     Right *
	 *                        *
	 *         0x015          *
	 *         Down           *
	 *                        */
	अणु 0x866b0b, KEY_CHANNELUP पूर्ण,
	अणु 0x866b18, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x866b16, KEY_OK पूर्ण,		/* XXX KEY_ENTER */
	अणु 0x866b0c, KEY_VOLUMEUP पूर्ण,
	अणु 0x866b15, KEY_CHANNELDOWN पूर्ण,

	/*  0x11            0x0d  *
	 *  MUTE            INFO  *
	 *                        */
	अणु 0x866b11, KEY_MUTE पूर्ण,
	अणु 0x866b0d, KEY_INFO पूर्ण,

	/*  0x0f    0x1b    0x1a  *
	 * RECORD PLAY/PAUSE STOP *
	 *                        *
	 *  0x0e    0x1f    0x1e  *
	 *TELETEXT  AUDIO  SOURCE *
	 *           RED   YELLOW *
	 *                        */
	अणु 0x866b0f, KEY_RECORD पूर्ण,
	अणु 0x866b1b, KEY_PLAYPAUSE पूर्ण,
	अणु 0x866b1a, KEY_STOP पूर्ण,
	अणु 0x866b0e, KEY_TEXT पूर्ण,
	अणु 0x866b1f, KEY_RED पूर्ण,	/*XXX KEY_AUDIO	*/
	अणु 0x866b1e, KEY_VIDEO पूर्ण,

	/*  0x1d   0x13     0x19  *
	 * SLEEP  PREVIEW   DVB   *
	 *         GREEN    BLUE  *
	 *                        */
	अणु 0x866b1d, KEY_SLEEP पूर्ण,
	अणु 0x866b13, KEY_GREEN पूर्ण,
	अणु 0x866b19, KEY_BLUE पूर्ण,	/* XXX KEY_SAT	*/

	/*  0x58           0x5c   *
	 * FREEZE        SNAPSHOT *
	 *                        */
	अणु 0x866b58, KEY_SLOW पूर्ण,
	अणु 0x866b5c, KEY_CAMERA पूर्ण,

पूर्ण;

अटल काष्ठा rc_map_list behold_map = अणु
	.map = अणु
		.scan     = behold,
		.size     = ARRAY_SIZE(behold),
		.rc_proto = RC_PROTO_NECX,
		.name     = RC_MAP_BEHOLD,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_behold(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&behold_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_behold(व्योम)
अणु
	rc_map_unरेजिस्टर(&behold_map);
पूर्ण

module_init(init_rc_map_behold)
module_निकास(निकास_rc_map_behold)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
