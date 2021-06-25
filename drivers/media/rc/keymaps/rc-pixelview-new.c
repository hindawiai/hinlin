<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// pixelview-new.h - Keytable क्रम pixelview_new Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/*
   Mauro Carvalho Chehab <mchehab@kernel.org>
   present on PV MPEG 8000GT
 */

अटल काष्ठा rc_map_table pixelview_new[] = अणु
	अणु 0x3c, KEY_TIME पूर्ण,		/* Timeshअगरt */
	अणु 0x12, KEY_POWER पूर्ण,

	अणु 0x3d, KEY_NUMERIC_1 पूर्ण,
	अणु 0x38, KEY_NUMERIC_2 पूर्ण,
	अणु 0x18, KEY_NUMERIC_3 पूर्ण,
	अणु 0x35, KEY_NUMERIC_4 पूर्ण,
	अणु 0x39, KEY_NUMERIC_5 पूर्ण,
	अणु 0x15, KEY_NUMERIC_6 पूर्ण,
	अणु 0x36, KEY_NUMERIC_7 पूर्ण,
	अणु 0x3a, KEY_NUMERIC_8 पूर्ण,
	अणु 0x1e, KEY_NUMERIC_9 पूर्ण,
	अणु 0x3e, KEY_NUMERIC_0 पूर्ण,

	अणु 0x1c, KEY_AGAIN पूर्ण,		/* LOOP	*/
	अणु 0x3f, KEY_VIDEO पूर्ण,		/* Source */
	अणु 0x1f, KEY_LAST पूर्ण,		/* +100 */
	अणु 0x1b, KEY_MUTE पूर्ण,

	अणु 0x17, KEY_CHANNELDOWN पूर्ण,
	अणु 0x16, KEY_CHANNELUP पूर्ण,
	अणु 0x10, KEY_VOLUMEUP पूर्ण,
	अणु 0x14, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x13, KEY_ZOOM पूर्ण,

	अणु 0x19, KEY_CAMERA पूर्ण,		/* SNAPSHOT */
	अणु 0x1a, KEY_SEARCH पूर्ण,		/* scan */

	अणु 0x37, KEY_REWIND पूर्ण,		/* << */
	अणु 0x32, KEY_RECORD पूर्ण,		/* o (red) */
	अणु 0x33, KEY_FORWARD पूर्ण,		/* >> */
	अणु 0x11, KEY_STOP पूर्ण,		/* square */
	अणु 0x3b, KEY_PLAY पूर्ण,		/* > */
	अणु 0x30, KEY_PLAYPAUSE पूर्ण,	/* || */

	अणु 0x31, KEY_TV पूर्ण,
	अणु 0x34, KEY_RADIO पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list pixelview_new_map = अणु
	.map = अणु
		.scan     = pixelview_new,
		.size     = ARRAY_SIZE(pixelview_new),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_PIXELVIEW_NEW,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_pixelview_new(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&pixelview_new_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_pixelview_new(व्योम)
अणु
	rc_map_unरेजिस्टर(&pixelview_new_map);
पूर्ण

module_init(init_rc_map_pixelview_new)
module_निकास(निकास_rc_map_pixelview_new)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
