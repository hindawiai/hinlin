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
 * Keytable क्रम 002-T IR remote provided together with Pixelview
 * SBTVD Hybrid Remote Controller. Uses NEC extended क्रमmat.
 */
अटल काष्ठा rc_map_table pixelview_002t[] = अणु
	अणु 0x866b13, KEY_MUTE पूर्ण,
	अणु 0x866b12, KEY_POWER2 पूर्ण,	/* घातer */

	अणु 0x866b01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x866b02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x866b03, KEY_NUMERIC_3 पूर्ण,
	अणु 0x866b04, KEY_NUMERIC_4 पूर्ण,
	अणु 0x866b05, KEY_NUMERIC_5 पूर्ण,
	अणु 0x866b06, KEY_NUMERIC_6 पूर्ण,
	अणु 0x866b07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x866b08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x866b09, KEY_NUMERIC_9 पूर्ण,
	अणु 0x866b00, KEY_NUMERIC_0 पूर्ण,

	अणु 0x866b0d, KEY_CHANNELUP पूर्ण,
	अणु 0x866b19, KEY_CHANNELDOWN पूर्ण,
	अणु 0x866b10, KEY_VOLUMEUP पूर्ण,	/* vol + */
	अणु 0x866b0c, KEY_VOLUMEDOWN पूर्ण,	/* vol - */

	अणु 0x866b0a, KEY_CAMERA पूर्ण,	/* snapshot */
	अणु 0x866b0b, KEY_ZOOM पूर्ण,		/* zoom */

	अणु 0x866b1b, KEY_BACKSPACE पूर्ण,
	अणु 0x866b15, KEY_ENTER पूर्ण,

	अणु 0x866b1d, KEY_UP पूर्ण,
	अणु 0x866b1e, KEY_DOWN पूर्ण,
	अणु 0x866b0e, KEY_LEFT पूर्ण,
	अणु 0x866b0f, KEY_RIGHT पूर्ण,

	अणु 0x866b18, KEY_RECORD पूर्ण,
	अणु 0x866b1a, KEY_STOP पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list pixelview_map = अणु
	.map = अणु
		.scan     = pixelview_002t,
		.size     = ARRAY_SIZE(pixelview_002t),
		.rc_proto = RC_PROTO_NECX,
		.name     = RC_MAP_PIXELVIEW_002T,
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
