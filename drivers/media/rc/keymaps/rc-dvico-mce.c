<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * keymap imported from cxusb.c
 *
 * Copyright (C) 2016 Sean Young
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table rc_map_dvico_mce_table[] = अणु
	अणु 0x0102, KEY_TV पूर्ण,
	अणु 0x010e, KEY_MP3 पूर्ण,
	अणु 0x011a, KEY_DVD पूर्ण,
	अणु 0x011e, KEY_FAVORITES पूर्ण,
	अणु 0x0116, KEY_SETUP पूर्ण,
	अणु 0x0146, KEY_POWER2 पूर्ण,
	अणु 0x010a, KEY_EPG पूर्ण,
	अणु 0x0149, KEY_BACK पूर्ण,
	अणु 0x014d, KEY_MENU पूर्ण,
	अणु 0x0151, KEY_UP पूर्ण,
	अणु 0x015b, KEY_LEFT पूर्ण,
	अणु 0x015f, KEY_RIGHT पूर्ण,
	अणु 0x0153, KEY_DOWN पूर्ण,
	अणु 0x015e, KEY_OK पूर्ण,
	अणु 0x0159, KEY_INFO पूर्ण,
	अणु 0x0155, KEY_TAB पूर्ण,
	अणु 0x010f, KEY_PREVIOUSSONG पूर्ण,/* Replay */
	अणु 0x0112, KEY_NEXTSONG पूर्ण,	/* Skip */
	अणु 0x0142, KEY_ENTER	 पूर्ण,	/* Winकरोws/Start */
	अणु 0x0115, KEY_VOLUMEUP पूर्ण,
	अणु 0x0105, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x0111, KEY_CHANNELUP पूर्ण,
	अणु 0x0109, KEY_CHANNELDOWN पूर्ण,
	अणु 0x0152, KEY_CAMERA पूर्ण,
	अणु 0x015a, KEY_TUNER पूर्ण,	/* Live */
	अणु 0x0119, KEY_OPEN पूर्ण,
	अणु 0x010b, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0117, KEY_NUMERIC_2 पूर्ण,
	अणु 0x011b, KEY_NUMERIC_3 पूर्ण,
	अणु 0x0107, KEY_NUMERIC_4 पूर्ण,
	अणु 0x0150, KEY_NUMERIC_5 पूर्ण,
	अणु 0x0154, KEY_NUMERIC_6 पूर्ण,
	अणु 0x0148, KEY_NUMERIC_7 पूर्ण,
	अणु 0x014c, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0158, KEY_NUMERIC_9 पूर्ण,
	अणु 0x0113, KEY_ANGLE पूर्ण,	/* Aspect */
	अणु 0x0103, KEY_NUMERIC_0 पूर्ण,
	अणु 0x011f, KEY_ZOOM पूर्ण,
	अणु 0x0143, KEY_REWIND पूर्ण,
	अणु 0x0147, KEY_PLAYPAUSE पूर्ण,
	अणु 0x014f, KEY_FASTFORWARD पूर्ण,
	अणु 0x0157, KEY_MUTE पूर्ण,
	अणु 0x010d, KEY_STOP पूर्ण,
	अणु 0x0101, KEY_RECORD पूर्ण,
	अणु 0x014e, KEY_POWER पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list dvico_mce_map = अणु
	.map = अणु
		.scan     = rc_map_dvico_mce_table,
		.size     = ARRAY_SIZE(rc_map_dvico_mce_table),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_DVICO_MCE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_dvico_mce(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&dvico_mce_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_dvico_mce(व्योम)
अणु
	rc_map_unरेजिस्टर(&dvico_mce_map);
पूर्ण

module_init(init_rc_map_dvico_mce)
module_निकास(निकास_rc_map_dvico_mce)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
