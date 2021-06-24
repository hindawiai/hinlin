<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * LeadTek Y04G0051 remote controller keytable
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table leadtek_y04g0051[] = अणु
	अणु 0x0300, KEY_POWER2 पूर्ण,
	अणु 0x0303, KEY_SCREEN पूर्ण,
	अणु 0x0304, KEY_RIGHT पूर्ण,
	अणु 0x0305, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0306, KEY_NUMERIC_2 पूर्ण,
	अणु 0x0307, KEY_NUMERIC_3 पूर्ण,
	अणु 0x0308, KEY_LEFT पूर्ण,
	अणु 0x0309, KEY_NUMERIC_4 पूर्ण,
	अणु 0x030a, KEY_NUMERIC_5 पूर्ण,
	अणु 0x030b, KEY_NUMERIC_6 पूर्ण,
	अणु 0x030c, KEY_UP पूर्ण,
	अणु 0x030d, KEY_NUMERIC_7 पूर्ण,
	अणु 0x030e, KEY_NUMERIC_8 पूर्ण,
	अणु 0x030f, KEY_NUMERIC_9 पूर्ण,
	अणु 0x0310, KEY_DOWN पूर्ण,
	अणु 0x0311, KEY_AGAIN पूर्ण,
	अणु 0x0312, KEY_NUMERIC_0 पूर्ण,
	अणु 0x0313, KEY_OK पूर्ण,              /* 1st ok */
	अणु 0x0314, KEY_MUTE पूर्ण,
	अणु 0x0316, KEY_OK पूर्ण,              /* 2nd ok */
	अणु 0x031e, KEY_VIDEO पूर्ण,           /* 2nd video */
	अणु 0x031b, KEY_AUDIO पूर्ण,
	अणु 0x031f, KEY_TEXT पूर्ण,
	अणु 0x0340, KEY_SLEEP पूर्ण,
	अणु 0x0341, KEY_DOT पूर्ण,
	अणु 0x0342, KEY_REWIND पूर्ण,
	अणु 0x0343, KEY_PLAY पूर्ण,
	अणु 0x0344, KEY_FASTFORWARD पूर्ण,
	अणु 0x0345, KEY_TIME पूर्ण,
	अणु 0x0346, KEY_STOP पूर्ण,            /* 2nd stop */
	अणु 0x0347, KEY_RECORD पूर्ण,
	अणु 0x0348, KEY_CAMERA पूर्ण,
	अणु 0x0349, KEY_ESC पूर्ण,
	अणु 0x034a, KEY_NEW पूर्ण,
	अणु 0x034b, KEY_RED पूर्ण,
	अणु 0x034c, KEY_GREEN पूर्ण,
	अणु 0x034d, KEY_YELLOW पूर्ण,
	अणु 0x034e, KEY_BLUE पूर्ण,
	अणु 0x034f, KEY_MENU पूर्ण,
	अणु 0x0350, KEY_STOP पूर्ण,            /* 1st stop */
	अणु 0x0351, KEY_CHANNEL पूर्ण,
	अणु 0x0352, KEY_VIDEO पूर्ण,           /* 1st video */
	अणु 0x0353, KEY_EPG पूर्ण,
	अणु 0x0354, KEY_PREVIOUS पूर्ण,
	अणु 0x0355, KEY_NEXT पूर्ण,
	अणु 0x0356, KEY_TV पूर्ण,
	अणु 0x035a, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x035b, KEY_CHANNELUP पूर्ण,
	अणु 0x035e, KEY_VOLUMEUP पूर्ण,
	अणु 0x035f, KEY_CHANNELDOWN पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list leadtek_y04g0051_map = अणु
	.map = अणु
		.scan     = leadtek_y04g0051,
		.size     = ARRAY_SIZE(leadtek_y04g0051),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_LEADTEK_Y04G0051,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_leadtek_y04g0051(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&leadtek_y04g0051_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_leadtek_y04g0051(व्योम)
अणु
	rc_map_unरेजिस्टर(&leadtek_y04g0051_map);
पूर्ण

module_init(init_rc_map_leadtek_y04g0051)
module_निकास(निकास_rc_map_leadtek_y04g0051)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
