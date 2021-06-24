<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// rc-pixelview-mk12.h - Keytable क्रम pixelview Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/*
 * Keytable क्रम MK-F12 IR remote provided together with Pixelview
 * Ultra Pro Remote Controller. Uses NEC extended क्रमmat.
 */
अटल काष्ठा rc_map_table pixelview_mk12[] = अणु
	अणु 0x866b03, KEY_TUNER पूर्ण,	/* Timeshअगरt */
	अणु 0x866b1e, KEY_POWER2 पूर्ण,	/* घातer */

	अणु 0x866b01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x866b0b, KEY_NUMERIC_2 पूर्ण,
	अणु 0x866b1b, KEY_NUMERIC_3 पूर्ण,
	अणु 0x866b05, KEY_NUMERIC_4 पूर्ण,
	अणु 0x866b09, KEY_NUMERIC_5 पूर्ण,
	अणु 0x866b15, KEY_NUMERIC_6 पूर्ण,
	अणु 0x866b06, KEY_NUMERIC_7 पूर्ण,
	अणु 0x866b0a, KEY_NUMERIC_8 पूर्ण,
	अणु 0x866b12, KEY_NUMERIC_9 पूर्ण,
	अणु 0x866b02, KEY_NUMERIC_0 पूर्ण,

	अणु 0x866b13, KEY_AGAIN पूर्ण,	/* loop */
	अणु 0x866b10, KEY_DIGITS पूर्ण,	/* +100 */

	अणु 0x866b00, KEY_VIDEO पूर्ण,		/* source */
	अणु 0x866b18, KEY_MUTE पूर्ण,		/* mute */
	अणु 0x866b19, KEY_CAMERA पूर्ण,	/* snapshot */
	अणु 0x866b1a, KEY_SEARCH पूर्ण,	/* scan */

	अणु 0x866b16, KEY_CHANNELUP पूर्ण,	/* chn + */
	अणु 0x866b14, KEY_CHANNELDOWN पूर्ण,	/* chn - */
	अणु 0x866b1f, KEY_VOLUMEUP पूर्ण,	/* vol + */
	अणु 0x866b17, KEY_VOLUMEDOWN पूर्ण,	/* vol - */
	अणु 0x866b1c, KEY_ZOOM पूर्ण,		/* zoom */

	अणु 0x866b04, KEY_REWIND पूर्ण,
	अणु 0x866b0e, KEY_RECORD पूर्ण,
	अणु 0x866b0c, KEY_FORWARD पूर्ण,

	अणु 0x866b1d, KEY_STOP पूर्ण,
	अणु 0x866b08, KEY_PLAY पूर्ण,
	अणु 0x866b0f, KEY_PAUSE पूर्ण,

	अणु 0x866b0d, KEY_TV पूर्ण,
	अणु 0x866b07, KEY_RADIO पूर्ण,	/* FM */
पूर्ण;

अटल काष्ठा rc_map_list pixelview_map = अणु
	.map = अणु
		.scan     = pixelview_mk12,
		.size     = ARRAY_SIZE(pixelview_mk12),
		.rc_proto = RC_PROTO_NECX,
		.name     = RC_MAP_PIXELVIEW_MK12,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_pixelview(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&pixelview_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_pixelview(व्योम)
अणु
	rc_map_unरेजिस्टर(&pixelview_map);
पूर्ण

module_init(init_rc_map_pixelview)
module_निकास(निकास_rc_map_pixelview)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
