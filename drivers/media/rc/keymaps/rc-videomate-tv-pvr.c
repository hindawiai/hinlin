<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// videomate-tv-pvr.h - Keytable क्रम videomate_tv_pvr Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table videomate_tv_pvr[] = अणु
	अणु 0x14, KEY_MUTE पूर्ण,
	अणु 0x24, KEY_ZOOM पूर्ण,

	अणु 0x01, KEY_DVD पूर्ण,
	अणु 0x23, KEY_RADIO पूर्ण,
	अणु 0x00, KEY_TV पूर्ण,

	अणु 0x0a, KEY_REWIND पूर्ण,
	अणु 0x08, KEY_PLAYPAUSE पूर्ण,
	अणु 0x0f, KEY_FORWARD पूर्ण,

	अणु 0x02, KEY_PREVIOUS पूर्ण,
	अणु 0x07, KEY_STOP पूर्ण,
	अणु 0x06, KEY_NEXT पूर्ण,

	अणु 0x0c, KEY_UP पूर्ण,
	अणु 0x0e, KEY_DOWN पूर्ण,
	अणु 0x0b, KEY_LEFT पूर्ण,
	अणु 0x0d, KEY_RIGHT पूर्ण,
	अणु 0x11, KEY_OK पूर्ण,

	अणु 0x03, KEY_MENU पूर्ण,
	अणु 0x09, KEY_SETUP पूर्ण,
	अणु 0x05, KEY_VIDEO पूर्ण,
	अणु 0x22, KEY_CHANNEL पूर्ण,

	अणु 0x12, KEY_VOLUMEUP पूर्ण,
	अणु 0x15, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x10, KEY_CHANNELUP पूर्ण,
	अणु 0x13, KEY_CHANNELDOWN पूर्ण,

	अणु 0x04, KEY_RECORD पूर्ण,

	अणु 0x16, KEY_NUMERIC_1 पूर्ण,
	अणु 0x17, KEY_NUMERIC_2 पूर्ण,
	अणु 0x18, KEY_NUMERIC_3 पूर्ण,
	अणु 0x19, KEY_NUMERIC_4 पूर्ण,
	अणु 0x1a, KEY_NUMERIC_5 पूर्ण,
	अणु 0x1b, KEY_NUMERIC_6 पूर्ण,
	अणु 0x1c, KEY_NUMERIC_7 पूर्ण,
	अणु 0x1d, KEY_NUMERIC_8 पूर्ण,
	अणु 0x1e, KEY_NUMERIC_9 पूर्ण,
	अणु 0x1f, KEY_NUMERIC_0 पूर्ण,

	अणु 0x20, KEY_LANGUAGE पूर्ण,
	अणु 0x21, KEY_SLEEP पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list videomate_tv_pvr_map = अणु
	.map = अणु
		.scan     = videomate_tv_pvr,
		.size     = ARRAY_SIZE(videomate_tv_pvr),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_VIDEOMATE_TV_PVR,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_videomate_tv_pvr(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&videomate_tv_pvr_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_videomate_tv_pvr(व्योम)
अणु
	rc_map_unरेजिस्टर(&videomate_tv_pvr_map);
पूर्ण

module_init(init_rc_map_videomate_tv_pvr)
module_निकास(निकास_rc_map_videomate_tv_pvr)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
