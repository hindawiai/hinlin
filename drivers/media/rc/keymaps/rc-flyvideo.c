<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// flyvideo.h - Keytable क्रम flyvideo Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table flyvideo[] = अणु
	अणु 0x0f, KEY_NUMERIC_0 पूर्ण,
	अणु 0x03, KEY_NUMERIC_1 पूर्ण,
	अणु 0x04, KEY_NUMERIC_2 पूर्ण,
	अणु 0x05, KEY_NUMERIC_3 पूर्ण,
	अणु 0x07, KEY_NUMERIC_4 पूर्ण,
	अणु 0x08, KEY_NUMERIC_5 पूर्ण,
	अणु 0x09, KEY_NUMERIC_6 पूर्ण,
	अणु 0x0b, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0c, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0d, KEY_NUMERIC_9 पूर्ण,

	अणु 0x0e, KEY_MODE पूर्ण,	/* Air/Cable */
	अणु 0x11, KEY_VIDEO पूर्ण,	/* Video */
	अणु 0x15, KEY_AUDIO पूर्ण,	/* Audio */
	अणु 0x00, KEY_POWER पूर्ण,	/* Power */
	अणु 0x18, KEY_TUNER पूर्ण,	/* AV Source */
	अणु 0x02, KEY_ZOOM पूर्ण,	/* Fullscreen */
	अणु 0x1a, KEY_LANGUAGE पूर्ण,	/* Stereo */
	अणु 0x1b, KEY_MUTE पूर्ण,	/* Mute */
	अणु 0x14, KEY_VOLUMEUP पूर्ण,	/* Volume + */
	अणु 0x17, KEY_VOLUMEDOWN पूर्ण,/* Volume - */
	अणु 0x12, KEY_CHANNELUP पूर्ण,/* Channel + */
	अणु 0x13, KEY_CHANNELDOWN पूर्ण,/* Channel - */
	अणु 0x06, KEY_AGAIN पूर्ण,	/* Recall */
	अणु 0x10, KEY_ENTER पूर्ण,	/* Enter */

	अणु 0x19, KEY_BACK पूर्ण,	/* Rewind  ( <<< ) */
	अणु 0x1f, KEY_FORWARD पूर्ण,	/* Forward ( >>> ) */
	अणु 0x0a, KEY_ANGLE पूर्ण,	/* no label, may be used as the PAUSE button */
पूर्ण;

अटल काष्ठा rc_map_list flyvideo_map = अणु
	.map = अणु
		.scan     = flyvideo,
		.size     = ARRAY_SIZE(flyvideo),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_FLYVIDEO,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_flyvideo(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&flyvideo_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_flyvideo(व्योम)
अणु
	rc_map_unरेजिस्टर(&flyvideo_map);
पूर्ण

module_init(init_rc_map_flyvideo)
module_निकास(निकास_rc_map_flyvideo)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
