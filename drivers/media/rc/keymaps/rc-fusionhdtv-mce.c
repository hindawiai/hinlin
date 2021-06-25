<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// fusionhdtv-mce.h - Keytable क्रम fusionhdtv_mce Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* DViCO FUSION HDTV MCE remote */

अटल काष्ठा rc_map_table fusionhdtv_mce[] = अणु

	अणु 0x0b, KEY_NUMERIC_1 पूर्ण,
	अणु 0x17, KEY_NUMERIC_2 पूर्ण,
	अणु 0x1b, KEY_NUMERIC_3 पूर्ण,
	अणु 0x07, KEY_NUMERIC_4 पूर्ण,
	अणु 0x50, KEY_NUMERIC_5 पूर्ण,
	अणु 0x54, KEY_NUMERIC_6 पूर्ण,
	अणु 0x48, KEY_NUMERIC_7 पूर्ण,
	अणु 0x4c, KEY_NUMERIC_8 पूर्ण,
	अणु 0x58, KEY_NUMERIC_9 पूर्ण,
	अणु 0x03, KEY_NUMERIC_0 पूर्ण,

	अणु 0x5e, KEY_OK पूर्ण,
	अणु 0x51, KEY_UP पूर्ण,
	अणु 0x53, KEY_DOWN पूर्ण,
	अणु 0x5b, KEY_LEFT पूर्ण,
	अणु 0x5f, KEY_RIGHT पूर्ण,

	अणु 0x02, KEY_TV पूर्ण,		/* Labeled DTV on remote */
	अणु 0x0e, KEY_MP3 पूर्ण,
	अणु 0x1a, KEY_DVD पूर्ण,
	अणु 0x1e, KEY_FAVORITES पूर्ण,	/* Labeled CPF on remote */
	अणु 0x16, KEY_SETUP पूर्ण,
	अणु 0x46, KEY_POWER2 पूर्ण,		/* TV On/Off button on remote */
	अणु 0x0a, KEY_EPG पूर्ण,		/* Labeled Guide on remote */

	अणु 0x49, KEY_BACK पूर्ण,
	अणु 0x59, KEY_INFO पूर्ण,		/* Labeled MORE on remote */
	अणु 0x4d, KEY_MENU पूर्ण,		/* Labeled DVDMENU on remote */
	अणु 0x55, KEY_CYCLEWINDOWS पूर्ण,	/* Labeled ALT-TAB on remote */

	अणु 0x0f, KEY_PREVIOUSSONG पूर्ण,	/* Labeled |<< REPLAY on remote */
	अणु 0x12, KEY_NEXTSONG पूर्ण,		/* Labeled >>| SKIP on remote */
	अणु 0x42, KEY_ENTER पूर्ण,		/* Labeled START with a green
					   MS winकरोws logo on remote */

	अणु 0x15, KEY_VOLUMEUP पूर्ण,
	अणु 0x05, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x11, KEY_CHANNELUP पूर्ण,
	अणु 0x09, KEY_CHANNELDOWN पूर्ण,

	अणु 0x52, KEY_CAMERA पूर्ण,
	अणु 0x5a, KEY_TUNER पूर्ण,
	अणु 0x19, KEY_OPEN पूर्ण,

	अणु 0x13, KEY_MODE पूर्ण,		/* 4:3 16:9 select */
	अणु 0x1f, KEY_ZOOM पूर्ण,

	अणु 0x43, KEY_REWIND पूर्ण,
	अणु 0x47, KEY_PLAYPAUSE पूर्ण,
	अणु 0x4f, KEY_FASTFORWARD पूर्ण,
	अणु 0x57, KEY_MUTE पूर्ण,
	अणु 0x0d, KEY_STOP पूर्ण,
	अणु 0x01, KEY_RECORD पूर्ण,
	अणु 0x4e, KEY_POWER पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list fusionhdtv_mce_map = अणु
	.map = अणु
		.scan     = fusionhdtv_mce,
		.size     = ARRAY_SIZE(fusionhdtv_mce),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_FUSIONHDTV_MCE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_fusionhdtv_mce(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&fusionhdtv_mce_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_fusionhdtv_mce(व्योम)
अणु
	rc_map_unरेजिस्टर(&fusionhdtv_mce_map);
पूर्ण

module_init(init_rc_map_fusionhdtv_mce)
module_निकास(निकास_rc_map_fusionhdtv_mce)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
