<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// tt-1500.h - Keytable क्रम tt_1500 Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* क्रम the Technotrend 1500 bundled remotes (grey and black): */

अटल काष्ठा rc_map_table tt_1500[] = अणु
	अणु 0x1501, KEY_POWER पूर्ण,
	अणु 0x1502, KEY_SHUFFLE पूर्ण,		/* ? द्विगुन-arrow key */
	अणु 0x1503, KEY_NUMERIC_1 पूर्ण,
	अणु 0x1504, KEY_NUMERIC_2 पूर्ण,
	अणु 0x1505, KEY_NUMERIC_3 पूर्ण,
	अणु 0x1506, KEY_NUMERIC_4 पूर्ण,
	अणु 0x1507, KEY_NUMERIC_5 पूर्ण,
	अणु 0x1508, KEY_NUMERIC_6 पूर्ण,
	अणु 0x1509, KEY_NUMERIC_7 पूर्ण,
	अणु 0x150a, KEY_NUMERIC_8 पूर्ण,
	अणु 0x150b, KEY_NUMERIC_9 पूर्ण,
	अणु 0x150c, KEY_NUMERIC_0 पूर्ण,
	अणु 0x150d, KEY_UP पूर्ण,
	अणु 0x150e, KEY_LEFT पूर्ण,
	अणु 0x150f, KEY_OK पूर्ण,
	अणु 0x1510, KEY_RIGHT पूर्ण,
	अणु 0x1511, KEY_DOWN पूर्ण,
	अणु 0x1512, KEY_INFO पूर्ण,
	अणु 0x1513, KEY_EXIT पूर्ण,
	अणु 0x1514, KEY_RED पूर्ण,
	अणु 0x1515, KEY_GREEN पूर्ण,
	अणु 0x1516, KEY_YELLOW पूर्ण,
	अणु 0x1517, KEY_BLUE पूर्ण,
	अणु 0x1518, KEY_MUTE पूर्ण,
	अणु 0x1519, KEY_TEXT पूर्ण,
	अणु 0x151a, KEY_MODE पूर्ण,		/* ? TV/Radio */
	अणु 0x1521, KEY_OPTION पूर्ण,
	अणु 0x1522, KEY_EPG पूर्ण,
	अणु 0x1523, KEY_CHANNELUP पूर्ण,
	अणु 0x1524, KEY_CHANNELDOWN पूर्ण,
	अणु 0x1525, KEY_VOLUMEUP पूर्ण,
	अणु 0x1526, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x1527, KEY_SETUP पूर्ण,
	अणु 0x153a, KEY_RECORD पूर्ण,		/* these keys are only in the black remote */
	अणु 0x153b, KEY_PLAY पूर्ण,
	अणु 0x153c, KEY_STOP पूर्ण,
	अणु 0x153d, KEY_REWIND पूर्ण,
	अणु 0x153e, KEY_PAUSE पूर्ण,
	अणु 0x153f, KEY_FORWARD पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list tt_1500_map = अणु
	.map = अणु
		.scan     = tt_1500,
		.size     = ARRAY_SIZE(tt_1500),
		.rc_proto = RC_PROTO_RC5,
		.name     = RC_MAP_TT_1500,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_tt_1500(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&tt_1500_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_tt_1500(व्योम)
अणु
	rc_map_unरेजिस्टर(&tt_1500_map);
पूर्ण

module_init(init_rc_map_tt_1500)
module_निकास(निकास_rc_map_tt_1500)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
