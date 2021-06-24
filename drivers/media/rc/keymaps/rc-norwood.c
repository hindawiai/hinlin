<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// norwood.h - Keytable क्रम norwood Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Norwood Micro (non-Pro) TV Tuner
   By Peter Naulls <peter@chocky.org>
   Key comments are the functions given in the manual */

अटल काष्ठा rc_map_table norwood[] = अणु
	/* Keys 0 to 9 */
	अणु 0x20, KEY_NUMERIC_0 पूर्ण,
	अणु 0x21, KEY_NUMERIC_1 पूर्ण,
	अणु 0x22, KEY_NUMERIC_2 पूर्ण,
	अणु 0x23, KEY_NUMERIC_3 पूर्ण,
	अणु 0x24, KEY_NUMERIC_4 पूर्ण,
	अणु 0x25, KEY_NUMERIC_5 पूर्ण,
	अणु 0x26, KEY_NUMERIC_6 पूर्ण,
	अणु 0x27, KEY_NUMERIC_7 पूर्ण,
	अणु 0x28, KEY_NUMERIC_8 पूर्ण,
	अणु 0x29, KEY_NUMERIC_9 पूर्ण,

	अणु 0x78, KEY_VIDEO पूर्ण,		/* Video Source        */
	अणु 0x2c, KEY_EXIT पूर्ण,		/* Open/Close software */
	अणु 0x2a, KEY_SELECT पूर्ण,		/* 2 Digit Select      */
	अणु 0x69, KEY_AGAIN पूर्ण,		/* Recall              */

	अणु 0x32, KEY_BRIGHTNESSUP पूर्ण,	/* Brightness increase */
	अणु 0x33, KEY_BRIGHTNESSDOWN पूर्ण,	/* Brightness decrease */
	अणु 0x6b, KEY_KPPLUS पूर्ण,		/* (not named >>>>>)   */
	अणु 0x6c, KEY_KPMINUS पूर्ण,		/* (not named <<<<<)   */

	अणु 0x2d, KEY_MUTE पूर्ण,		/* Mute                */
	अणु 0x30, KEY_VOLUMEUP पूर्ण,		/* Volume up           */
	अणु 0x31, KEY_VOLUMEDOWN पूर्ण,	/* Volume करोwn         */
	अणु 0x60, KEY_CHANNELUP पूर्ण,	/* Channel up          */
	अणु 0x61, KEY_CHANNELDOWN पूर्ण,	/* Channel करोwn        */

	अणु 0x3f, KEY_RECORD पूर्ण,		/* Record              */
	अणु 0x37, KEY_PLAY पूर्ण,		/* Play                */
	अणु 0x36, KEY_PAUSE पूर्ण,		/* Pause               */
	अणु 0x2b, KEY_STOP पूर्ण,		/* Stop                */
	अणु 0x67, KEY_FASTFORWARD पूर्ण,	/* Forward              */
	अणु 0x66, KEY_REWIND पूर्ण,		/* Rewind              */
	अणु 0x3e, KEY_SEARCH पूर्ण,		/* Auto Scan           */
	अणु 0x2e, KEY_CAMERA पूर्ण,		/* Capture Video       */
	अणु 0x6d, KEY_MENU पूर्ण,		/* Show/Hide Control   */
	अणु 0x2f, KEY_ZOOM पूर्ण,		/* Full Screen         */
	अणु 0x34, KEY_RADIO पूर्ण,		/* FM                  */
	अणु 0x65, KEY_POWER पूर्ण,		/* Computer घातer      */
पूर्ण;

अटल काष्ठा rc_map_list norwood_map = अणु
	.map = अणु
		.scan     = norwood,
		.size     = ARRAY_SIZE(norwood),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_NORWOOD,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_norwood(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&norwood_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_norwood(व्योम)
अणु
	rc_map_unरेजिस्टर(&norwood_map);
पूर्ण

module_init(init_rc_map_norwood)
module_निकास(निकास_rc_map_norwood)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
