<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// eztv.h - Keytable क्रम eztv Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Alfons Geser <a.geser@cox.net>
 * updates from Job D. R. Borges <jobdrb@ig.com.br> */

अटल काष्ठा rc_map_table eztv[] = अणु
	अणु 0x12, KEY_POWER पूर्ण,
	अणु 0x01, KEY_TV पूर्ण,	/* DVR */
	अणु 0x15, KEY_DVD पूर्ण,	/* DVD */
	अणु 0x17, KEY_AUDIO पूर्ण,	/* music */
				/* DVR mode / DVD mode / music mode */

	अणु 0x1b, KEY_MUTE पूर्ण,	/* mute */
	अणु 0x02, KEY_LANGUAGE पूर्ण,	/* MTS/SAP / audio / स्वतःseek */
	अणु 0x1e, KEY_SUBTITLE पूर्ण,	/* बंदd captioning / subtitle / seek */
	अणु 0x16, KEY_ZOOM पूर्ण,	/* full screen */
	अणु 0x1c, KEY_VIDEO पूर्ण,	/* video source / eject / delall */
	अणु 0x1d, KEY_RESTART पूर्ण,	/* playback / angle / del */
	अणु 0x2f, KEY_SEARCH पूर्ण,	/* scan / menu / playlist */
	अणु 0x30, KEY_CHANNEL पूर्ण,	/* CH surfing / bookmark / memo */

	अणु 0x31, KEY_HELP पूर्ण,	/* help */
	अणु 0x32, KEY_MODE पूर्ण,	/* num/memo */
	अणु 0x33, KEY_ESC पूर्ण,	/* cancel */

	अणु 0x0c, KEY_UP पूर्ण,	/* up */
	अणु 0x10, KEY_DOWN पूर्ण,	/* करोwn */
	अणु 0x08, KEY_LEFT पूर्ण,	/* left */
	अणु 0x04, KEY_RIGHT पूर्ण,	/* right */
	अणु 0x03, KEY_SELECT पूर्ण,	/* select */

	अणु 0x1f, KEY_REWIND पूर्ण,	/* शुरुआत */
	अणु 0x20, KEY_PLAYPAUSE पूर्ण,/* play/छोड़ो */
	अणु 0x29, KEY_FORWARD पूर्ण,	/* क्रमward */
	अणु 0x14, KEY_AGAIN पूर्ण,	/* repeat */
	अणु 0x2b, KEY_RECORD पूर्ण,	/* recording */
	अणु 0x2c, KEY_STOP पूर्ण,	/* stop */
	अणु 0x2d, KEY_PLAY पूर्ण,	/* play */
	अणु 0x2e, KEY_CAMERA पूर्ण,	/* snapshot / shuffle */

	अणु 0x00, KEY_NUMERIC_0 पूर्ण,
	अणु 0x05, KEY_NUMERIC_1 पूर्ण,
	अणु 0x06, KEY_NUMERIC_2 पूर्ण,
	अणु 0x07, KEY_NUMERIC_3 पूर्ण,
	अणु 0x09, KEY_NUMERIC_4 पूर्ण,
	अणु 0x0a, KEY_NUMERIC_5 पूर्ण,
	अणु 0x0b, KEY_NUMERIC_6 पूर्ण,
	अणु 0x0d, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0e, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0f, KEY_NUMERIC_9 पूर्ण,

	अणु 0x2a, KEY_VOLUMEUP पूर्ण,
	अणु 0x11, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x18, KEY_CHANNELUP पूर्ण,/* CH.tracking up */
	अणु 0x19, KEY_CHANNELDOWN पूर्ण,/* CH.tracking करोwn */

	अणु 0x13, KEY_ENTER पूर्ण,	/* enter */
	अणु 0x21, KEY_DOT पूर्ण,	/* . (decimal करोt) */
पूर्ण;

अटल काष्ठा rc_map_list eztv_map = अणु
	.map = अणु
		.scan     = eztv,
		.size     = ARRAY_SIZE(eztv),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_EZTV,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_eztv(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&eztv_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_eztv(व्योम)
अणु
	rc_map_unरेजिस्टर(&eztv_map);
पूर्ण

module_init(init_rc_map_eztv)
module_निकास(निकास_rc_map_eztv)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
