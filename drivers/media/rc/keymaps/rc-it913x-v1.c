<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* ITE Generic remotes Version 1
 *
 * Copyright (C) 2012 Malcolm Priestley (tvboxspy@gmail.com)
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>


अटल काष्ठा rc_map_table it913x_v1_rc[] = अणु
	/* Type 1 */
	अणु 0x61d601, KEY_VIDEO पूर्ण,           /* Source */
	अणु 0x61d602, KEY_NUMERIC_3 पूर्ण,
	अणु 0x61d603, KEY_POWER पूर्ण,           /* ShutDown */
	अणु 0x61d604, KEY_NUMERIC_1 पूर्ण,
	अणु 0x61d605, KEY_NUMERIC_5 पूर्ण,
	अणु 0x61d606, KEY_NUMERIC_6 पूर्ण,
	अणु 0x61d607, KEY_CHANNELDOWN पूर्ण,     /* CH- */
	अणु 0x61d608, KEY_NUMERIC_2 पूर्ण,
	अणु 0x61d609, KEY_CHANNELUP पूर्ण,       /* CH+ */
	अणु 0x61d60a, KEY_NUMERIC_9 पूर्ण,
	अणु 0x61d60b, KEY_ZOOM पूर्ण,            /* Zoom */
	अणु 0x61d60c, KEY_NUMERIC_7 पूर्ण,
	अणु 0x61d60d, KEY_NUMERIC_8 पूर्ण,
	अणु 0x61d60e, KEY_VOLUMEUP पूर्ण,        /* Vol+ */
	अणु 0x61d60f, KEY_NUMERIC_4 पूर्ण,
	अणु 0x61d610, KEY_ESC पूर्ण,             /* [back up arrow] */
	अणु 0x61d611, KEY_NUMERIC_0 पूर्ण,
	अणु 0x61d612, KEY_OK पूर्ण,              /* [enter arrow] */
	अणु 0x61d613, KEY_VOLUMEDOWN पूर्ण,      /* Vol- */
	अणु 0x61d614, KEY_RECORD पूर्ण,          /* Rec */
	अणु 0x61d615, KEY_STOP पूर्ण,            /* Stop */
	अणु 0x61d616, KEY_PLAY पूर्ण,            /* Play */
	अणु 0x61d617, KEY_MUTE पूर्ण,            /* Mute */
	अणु 0x61d618, KEY_UP पूर्ण,
	अणु 0x61d619, KEY_DOWN पूर्ण,
	अणु 0x61d61a, KEY_LEFT पूर्ण,
	अणु 0x61d61b, KEY_RIGHT पूर्ण,
	अणु 0x61d61c, KEY_RED पूर्ण,
	अणु 0x61d61d, KEY_GREEN पूर्ण,
	अणु 0x61d61e, KEY_YELLOW पूर्ण,
	अणु 0x61d61f, KEY_BLUE पूर्ण,
	अणु 0x61d643, KEY_POWER2 पूर्ण,          /* [red घातer button] */
	/* Type 2 - 20 buttons */
	अणु 0x807f0d, KEY_NUMERIC_0 पूर्ण,
	अणु 0x807f04, KEY_NUMERIC_1 पूर्ण,
	अणु 0x807f05, KEY_NUMERIC_2 पूर्ण,
	अणु 0x807f06, KEY_NUMERIC_3 पूर्ण,
	अणु 0x807f07, KEY_NUMERIC_4 पूर्ण,
	अणु 0x807f08, KEY_NUMERIC_5 पूर्ण,
	अणु 0x807f09, KEY_NUMERIC_6 पूर्ण,
	अणु 0x807f0a, KEY_NUMERIC_7 पूर्ण,
	अणु 0x807f1b, KEY_NUMERIC_8 पूर्ण,
	अणु 0x807f1f, KEY_NUMERIC_9 पूर्ण,
	अणु 0x807f12, KEY_POWER पूर्ण,
	अणु 0x807f01, KEY_MEDIA_REPEATपूर्ण, /* Recall */
	अणु 0x807f19, KEY_PAUSE पूर्ण, /* Timeshअगरt */
	अणु 0x807f1e, KEY_VOLUMEUP पूर्ण, /* 2 x -/+ Keys not marked */
	अणु 0x807f03, KEY_VOLUMEDOWN पूर्ण, /* Volume defined as right hand*/
	अणु 0x807f1a, KEY_CHANNELUP पूर्ण,
	अणु 0x807f02, KEY_CHANNELDOWN पूर्ण,
	अणु 0x807f0c, KEY_ZOOM पूर्ण,
	अणु 0x807f00, KEY_RECORD पूर्ण,
	अणु 0x807f0e, KEY_STOP पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list it913x_v1_map = अणु
	.map = अणु
		.scan     = it913x_v1_rc,
		.size     = ARRAY_SIZE(it913x_v1_rc),
		.rc_proto = RC_PROTO_NECX,
		.name     = RC_MAP_IT913X_V1,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_it913x_v1_map(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&it913x_v1_map);
पूर्ण

अटल व्योम __निकास निकास_rc_it913x_v1_map(व्योम)
अणु
	rc_map_unरेजिस्टर(&it913x_v1_map);
पूर्ण

module_init(init_rc_it913x_v1_map)
module_निकास(निकास_rc_it913x_v1_map)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Malcolm Priestley tvboxspy@gmail.com");
