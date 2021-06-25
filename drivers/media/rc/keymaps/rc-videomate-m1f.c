<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* videomate-k100.h - Keytable क्रम videomate_k100 Remote Controller
 *
 * keymap imported from ir-keymaps.c
 *
 * Copyright (c) 2010 by Pavel Osnova <pvosnova@gmail.com>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table videomate_k100[] = अणु
	अणु 0x01, KEY_POWER पूर्ण,
	अणु 0x31, KEY_TUNER पूर्ण,
	अणु 0x33, KEY_VIDEO पूर्ण,
	अणु 0x2f, KEY_RADIO पूर्ण,
	अणु 0x30, KEY_CAMERA पूर्ण,
	अणु 0x2d, KEY_NEW पूर्ण, /* TV record button */
	अणु 0x17, KEY_CYCLEWINDOWS पूर्ण,
	अणु 0x2c, KEY_ANGLE पूर्ण,
	अणु 0x2b, KEY_LANGUAGE पूर्ण,
	अणु 0x32, KEY_SEARCH पूर्ण, /* '...' button */
	अणु 0x11, KEY_UP पूर्ण,
	अणु 0x13, KEY_LEFT पूर्ण,
	अणु 0x15, KEY_OK पूर्ण,
	अणु 0x14, KEY_RIGHT पूर्ण,
	अणु 0x12, KEY_DOWN पूर्ण,
	अणु 0x16, KEY_BACKSPACE पूर्ण,
	अणु 0x02, KEY_ZOOM पूर्ण, /* WIN key */
	अणु 0x04, KEY_INFO पूर्ण,
	अणु 0x05, KEY_VOLUMEUP पूर्ण,
	अणु 0x03, KEY_MUTE पूर्ण,
	अणु 0x07, KEY_CHANNELUP पूर्ण,
	अणु 0x06, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x08, KEY_CHANNELDOWN पूर्ण,
	अणु 0x0c, KEY_RECORD पूर्ण,
	अणु 0x0e, KEY_STOP पूर्ण,
	अणु 0x0a, KEY_BACK पूर्ण,
	अणु 0x0b, KEY_PLAY पूर्ण,
	अणु 0x09, KEY_FORWARD पूर्ण,
	अणु 0x10, KEY_PREVIOUS पूर्ण,
	अणु 0x0d, KEY_PAUSE पूर्ण,
	अणु 0x0f, KEY_NEXT पूर्ण,
	अणु 0x1e, KEY_NUMERIC_1 पूर्ण,
	अणु 0x1f, KEY_NUMERIC_2 पूर्ण,
	अणु 0x20, KEY_NUMERIC_3 पूर्ण,
	अणु 0x21, KEY_NUMERIC_4 पूर्ण,
	अणु 0x22, KEY_NUMERIC_5 पूर्ण,
	अणु 0x23, KEY_NUMERIC_6 पूर्ण,
	अणु 0x24, KEY_NUMERIC_7 पूर्ण,
	अणु 0x25, KEY_NUMERIC_8 पूर्ण,
	अणु 0x26, KEY_NUMERIC_9 पूर्ण,
	अणु 0x2a, KEY_NUMERIC_STAR पूर्ण, /* * key */
	अणु 0x1d, KEY_NUMERIC_0 पूर्ण,
	अणु 0x29, KEY_SUBTITLE पूर्ण, /* # key */
	अणु 0x27, KEY_CLEAR पूर्ण,
	अणु 0x34, KEY_SCREEN पूर्ण,
	अणु 0x28, KEY_ENTER पूर्ण,
	अणु 0x19, KEY_RED पूर्ण,
	अणु 0x1a, KEY_GREEN पूर्ण,
	अणु 0x1b, KEY_YELLOW पूर्ण,
	अणु 0x1c, KEY_BLUE पूर्ण,
	अणु 0x18, KEY_TEXT पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list videomate_k100_map = अणु
	.map = अणु
		.scan     = videomate_k100,
		.size     = ARRAY_SIZE(videomate_k100),
		.rc_proto = RC_PROTO_UNKNOWN,     /* Legacy IR type */
		.name     = RC_MAP_VIDEOMATE_K100,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_videomate_k100(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&videomate_k100_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_videomate_k100(व्योम)
अणु
	rc_map_unरेजिस्टर(&videomate_k100_map);
पूर्ण

module_init(init_rc_map_videomate_k100)
module_निकास(निकास_rc_map_videomate_k100)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pavel Osnova <pvosnova@gmail.com>");
