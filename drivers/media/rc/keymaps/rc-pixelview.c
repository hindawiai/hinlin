<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// pixelview.h - Keytable क्रम pixelview Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table pixelview[] = अणु

	अणु 0x1e, KEY_POWER पूर्ण,	/* घातer */
	अणु 0x07, KEY_VIDEO पूर्ण,	/* source */
	अणु 0x1c, KEY_SEARCH पूर्ण,	/* scan */


	अणु 0x03, KEY_TUNER पूर्ण,		/* TV/FM */

	अणु 0x00, KEY_RECORD पूर्ण,
	अणु 0x08, KEY_STOP पूर्ण,
	अणु 0x11, KEY_PLAY पूर्ण,

	अणु 0x1a, KEY_PLAYPAUSE पूर्ण,	/* मुक्तze */
	अणु 0x19, KEY_ZOOM पूर्ण,		/* zoom */
	अणु 0x0f, KEY_TEXT पूर्ण,		/* min */

	अणु 0x01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0b, KEY_NUMERIC_2 पूर्ण,
	अणु 0x1b, KEY_NUMERIC_3 पूर्ण,
	अणु 0x05, KEY_NUMERIC_4 पूर्ण,
	अणु 0x09, KEY_NUMERIC_5 पूर्ण,
	अणु 0x15, KEY_NUMERIC_6 पूर्ण,
	अणु 0x06, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0a, KEY_NUMERIC_8 पूर्ण,
	अणु 0x12, KEY_NUMERIC_9 पूर्ण,
	अणु 0x02, KEY_NUMERIC_0 पूर्ण,
	अणु 0x10, KEY_LAST पूर्ण,		/* +100 */
	अणु 0x13, KEY_LIST पूर्ण,		/* recall */

	अणु 0x1f, KEY_CHANNELUP पूर्ण,	/* chn करोwn */
	अणु 0x17, KEY_CHANNELDOWN पूर्ण,	/* chn up */
	अणु 0x16, KEY_VOLUMEUP पूर्ण,		/* vol करोwn */
	अणु 0x14, KEY_VOLUMEDOWN पूर्ण,	/* vol up */

	अणु 0x04, KEY_KPMINUS पूर्ण,		/* <<< */
	अणु 0x0e, KEY_SETUP पूर्ण,		/* function */
	अणु 0x0c, KEY_KPPLUS पूर्ण,		/* >>> */

	अणु 0x0d, KEY_GOTO पूर्ण,		/* mts */
	अणु 0x1d, KEY_REFRESH पूर्ण,		/* reset */
	अणु 0x18, KEY_MUTE पूर्ण,		/* mute/unmute */
पूर्ण;

अटल काष्ठा rc_map_list pixelview_map = अणु
	.map = अणु
		.scan     = pixelview,
		.size     = ARRAY_SIZE(pixelview),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_PIXELVIEW,
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
