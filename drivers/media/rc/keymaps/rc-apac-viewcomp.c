<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// apac-viewcomp.h - Keytable क्रम apac_viewcomp Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Attila Konकरोros <attila.konकरोros@chello.hu> */

अटल काष्ठा rc_map_table apac_viewcomp[] = अणु

	अणु 0x01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x03, KEY_NUMERIC_3 पूर्ण,
	अणु 0x04, KEY_NUMERIC_4 पूर्ण,
	अणु 0x05, KEY_NUMERIC_5 पूर्ण,
	अणु 0x06, KEY_NUMERIC_6 पूर्ण,
	अणु 0x07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x09, KEY_NUMERIC_9 पूर्ण,
	अणु 0x00, KEY_NUMERIC_0 पूर्ण,
	अणु 0x17, KEY_LAST पूर्ण,		/* +100 */
	अणु 0x0a, KEY_LIST पूर्ण,		/* recall */


	अणु 0x1c, KEY_TUNER पूर्ण,		/* TV/FM */
	अणु 0x15, KEY_SEARCH पूर्ण,		/* scan */
	अणु 0x12, KEY_POWER पूर्ण,		/* घातer */
	अणु 0x1f, KEY_VOLUMEDOWN पूर्ण,	/* vol up */
	अणु 0x1b, KEY_VOLUMEUP पूर्ण,		/* vol करोwn */
	अणु 0x1e, KEY_CHANNELDOWN पूर्ण,	/* chn up */
	अणु 0x1a, KEY_CHANNELUP पूर्ण,	/* chn करोwn */

	अणु 0x11, KEY_VIDEO पूर्ण,		/* video */
	अणु 0x0f, KEY_ZOOM पूर्ण,		/* full screen */
	अणु 0x13, KEY_MUTE पूर्ण,		/* mute/unmute */
	अणु 0x10, KEY_TEXT पूर्ण,		/* min */

	अणु 0x0d, KEY_STOP पूर्ण,		/* मुक्तze */
	अणु 0x0e, KEY_RECORD पूर्ण,		/* record */
	अणु 0x1d, KEY_PLAYPAUSE पूर्ण,	/* stop */
	अणु 0x19, KEY_PLAY पूर्ण,		/* play */

	अणु 0x16, KEY_GOTO पूर्ण,		/* osd */
	अणु 0x14, KEY_REFRESH पूर्ण,		/* शेष */
	अणु 0x0c, KEY_KPPLUS पूर्ण,		/* fine tune >>>> */
	अणु 0x18, KEY_KPMINUS पूर्ण,		/* fine tune <<<< */
पूर्ण;

अटल काष्ठा rc_map_list apac_viewcomp_map = अणु
	.map = अणु
		.scan     = apac_viewcomp,
		.size     = ARRAY_SIZE(apac_viewcomp),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_APAC_VIEWCOMP,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_apac_viewcomp(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&apac_viewcomp_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_apac_viewcomp(व्योम)
अणु
	rc_map_unरेजिस्टर(&apac_viewcomp_map);
पूर्ण

module_init(init_rc_map_apac_viewcomp)
module_निकास(निकास_rc_map_apac_viewcomp)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
