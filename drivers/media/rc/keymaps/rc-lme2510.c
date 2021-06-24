<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* LME2510 remote control
 *
 * Copyright (C) 2010 Malcolm Priestley (tvboxspy@gmail.com)
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>


अटल काष्ठा rc_map_table lme2510_rc[] = अणु
	/* Type 1 - 26 buttons */
	अणु 0xef12ba45, KEY_NUMERIC_0 पूर्ण,
	अणु 0xef12a05f, KEY_NUMERIC_1 पूर्ण,
	अणु 0xef12af50, KEY_NUMERIC_2 पूर्ण,
	अणु 0xef12a25d, KEY_NUMERIC_3 पूर्ण,
	अणु 0xef12be41, KEY_NUMERIC_4 पूर्ण,
	अणु 0xef12f50a, KEY_NUMERIC_5 पूर्ण,
	अणु 0xef12bd42, KEY_NUMERIC_6 पूर्ण,
	अणु 0xef12b847, KEY_NUMERIC_7 पूर्ण,
	अणु 0xef12b649, KEY_NUMERIC_8 पूर्ण,
	अणु 0xef12fa05, KEY_NUMERIC_9 पूर्ण,
	अणु 0xef12bc43, KEY_POWER पूर्ण,
	अणु 0xef12b946, KEY_SUBTITLE पूर्ण,
	अणु 0xef12f906, KEY_PAUSE पूर्ण,
	अणु 0xef12fc03, KEY_MEDIA_REPEATपूर्ण,
	अणु 0xef12fd02, KEY_PAUSE पूर्ण,
	अणु 0xef12a15e, KEY_VOLUMEUP पूर्ण,
	अणु 0xef12a35c, KEY_VOLUMEDOWN पूर्ण,
	अणु 0xef12f609, KEY_CHANNELUP पूर्ण,
	अणु 0xef12e51a, KEY_CHANNELDOWN पूर्ण,
	अणु 0xef12e11e, KEY_PLAY पूर्ण,
	अणु 0xef12e41b, KEY_ZOOM पूर्ण,
	अणु 0xef12a659, KEY_MUTE पूर्ण,
	अणु 0xef12a55a, KEY_TV पूर्ण,
	अणु 0xef12e718, KEY_RECORD पूर्ण,
	अणु 0xef12f807, KEY_EPG पूर्ण,
	अणु 0xef12fe01, KEY_STOP पूर्ण,
	/* Type 2 - 20 buttons */
	अणु 0xff40ea15, KEY_NUMERIC_0 पूर्ण,
	अणु 0xff40f708, KEY_NUMERIC_1 पूर्ण,
	अणु 0xff40f609, KEY_NUMERIC_2 पूर्ण,
	अणु 0xff40f50a, KEY_NUMERIC_3 पूर्ण,
	अणु 0xff40f30c, KEY_NUMERIC_4 पूर्ण,
	अणु 0xff40f20d, KEY_NUMERIC_5 पूर्ण,
	अणु 0xff40f10e, KEY_NUMERIC_6 पूर्ण,
	अणु 0xff40ef10, KEY_NUMERIC_7 पूर्ण,
	अणु 0xff40ee11, KEY_NUMERIC_8 पूर्ण,
	अणु 0xff40ed12, KEY_NUMERIC_9 पूर्ण,
	अणु 0xff40ff00, KEY_POWER पूर्ण,
	अणु 0xff40fb04, KEY_MEDIA_REPEATपूर्ण, /* Recall */
	अणु 0xff40e51a, KEY_PAUSE पूर्ण, /* Timeshअगरt */
	अणु 0xff40fd02, KEY_VOLUMEUP पूर्ण, /* 2 x -/+ Keys not marked */
	अणु 0xff40f906, KEY_VOLUMEDOWN पूर्ण, /* Volume defined as right hand*/
	अणु 0xff40fe01, KEY_CHANNELUP पूर्ण,
	अणु 0xff40fa05, KEY_CHANNELDOWN पूर्ण,
	अणु 0xff40eb14, KEY_ZOOM पूर्ण,
	अणु 0xff40e718, KEY_RECORD पूर्ण,
	अणु 0xff40e916, KEY_STOP पूर्ण,
	/* Type 3 - 20 buttons */
	अणु 0xff00e31c, KEY_NUMERIC_0 पूर्ण,
	अणु 0xff00f807, KEY_NUMERIC_1 पूर्ण,
	अणु 0xff00ea15, KEY_NUMERIC_2 पूर्ण,
	अणु 0xff00f609, KEY_NUMERIC_3 पूर्ण,
	अणु 0xff00e916, KEY_NUMERIC_4 पूर्ण,
	अणु 0xff00e619, KEY_NUMERIC_5 पूर्ण,
	अणु 0xff00f20d, KEY_NUMERIC_6 पूर्ण,
	अणु 0xff00f30c, KEY_NUMERIC_7 पूर्ण,
	अणु 0xff00e718, KEY_NUMERIC_8 पूर्ण,
	अणु 0xff00a15e, KEY_NUMERIC_9 पूर्ण,
	अणु 0xff00ba45, KEY_POWER पूर्ण,
	अणु 0xff00bb44, KEY_MEDIA_REPEATपूर्ण, /* Recall */
	अणु 0xff00b54a, KEY_PAUSE पूर्ण, /* Timeshअगरt */
	अणु 0xff00b847, KEY_VOLUMEUP पूर्ण, /* 2 x -/+ Keys not marked */
	अणु 0xff00bc43, KEY_VOLUMEDOWN पूर्ण, /* Volume defined as right hand*/
	अणु 0xff00b946, KEY_CHANNELUP पूर्ण,
	अणु 0xff00bf40, KEY_CHANNELDOWN पूर्ण,
	अणु 0xff00f708, KEY_ZOOM पूर्ण,
	अणु 0xff00bd42, KEY_RECORD पूर्ण,
	अणु 0xff00a55a, KEY_STOP पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list lme2510_map = अणु
	.map = अणु
		.scan     = lme2510_rc,
		.size     = ARRAY_SIZE(lme2510_rc),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_LME2510,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_lme2510_map(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&lme2510_map);
पूर्ण

अटल व्योम __निकास निकास_rc_lme2510_map(व्योम)
अणु
	rc_map_unरेजिस्टर(&lme2510_map);
पूर्ण

module_init(init_rc_lme2510_map)
module_निकास(निकास_rc_lme2510_map)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Malcolm Priestley tvboxspy@gmail.com");
