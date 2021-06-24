<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * keymap imported from cxusb.c
 *
 * Copyright (C) 2016 Sean Young
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table rc_map_dvico_portable_table[] = अणु
	अणु 0x0302, KEY_SETUP पूर्ण,       /* Profile */
	अणु 0x0343, KEY_POWER2 पूर्ण,
	अणु 0x0306, KEY_EPG पूर्ण,
	अणु 0x035a, KEY_BACK पूर्ण,
	अणु 0x0305, KEY_MENU पूर्ण,
	अणु 0x0347, KEY_INFO पूर्ण,
	अणु 0x0301, KEY_TAB पूर्ण,
	अणु 0x0342, KEY_PREVIOUSSONG पूर्ण,/* Replay */
	अणु 0x0349, KEY_VOLUMEUP पूर्ण,
	अणु 0x0309, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x0354, KEY_CHANNELUP पूर्ण,
	अणु 0x030b, KEY_CHANNELDOWN पूर्ण,
	अणु 0x0316, KEY_CAMERA पूर्ण,
	अणु 0x0340, KEY_TUNER पूर्ण,	/* ATV/DTV */
	अणु 0x0345, KEY_OPEN पूर्ण,
	अणु 0x0319, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0318, KEY_NUMERIC_2 पूर्ण,
	अणु 0x031b, KEY_NUMERIC_3 पूर्ण,
	अणु 0x031a, KEY_NUMERIC_4 पूर्ण,
	अणु 0x0358, KEY_NUMERIC_5 पूर्ण,
	अणु 0x0359, KEY_NUMERIC_6 पूर्ण,
	अणु 0x0315, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0314, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0317, KEY_NUMERIC_9 पूर्ण,
	अणु 0x0344, KEY_ANGLE पूर्ण,	/* Aspect */
	अणु 0x0355, KEY_NUMERIC_0 पूर्ण,
	अणु 0x0307, KEY_ZOOM पूर्ण,
	अणु 0x030a, KEY_REWIND पूर्ण,
	अणु 0x0308, KEY_PLAYPAUSE पूर्ण,
	अणु 0x034b, KEY_FASTFORWARD पूर्ण,
	अणु 0x035b, KEY_MUTE पूर्ण,
	अणु 0x0304, KEY_STOP पूर्ण,
	अणु 0x0356, KEY_RECORD पूर्ण,
	अणु 0x0357, KEY_POWER पूर्ण,
	अणु 0x0341, KEY_UNKNOWN पूर्ण,    /* INPUT */
	अणु 0x0300, KEY_UNKNOWN पूर्ण,    /* HD */
पूर्ण;

अटल काष्ठा rc_map_list dvico_portable_map = अणु
	.map = अणु
		.scan     = rc_map_dvico_portable_table,
		.size     = ARRAY_SIZE(rc_map_dvico_portable_table),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_DVICO_PORTABLE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_dvico_portable(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&dvico_portable_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_dvico_portable(व्योम)
अणु
	rc_map_unरेजिस्टर(&dvico_portable_map);
पूर्ण

module_init(init_rc_map_dvico_portable)
module_निकास(निकास_rc_map_dvico_portable)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
