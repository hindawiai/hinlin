<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* ITE Generic remotes Version 2
 *
 * Copyright (C) 2012 Malcolm Priestley (tvboxspy@gmail.com)
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>


अटल काष्ठा rc_map_table it913x_v2_rc[] = अणु
	/* Type 1 */
	/* 9005 remote */
	अणु 0x807f12, KEY_POWER2 पूर्ण,	/* Power (RED POWER BUTTON)*/
	अणु 0x807f1a, KEY_VIDEO पूर्ण,	/* Source */
	अणु 0x807f1e, KEY_MUTE पूर्ण,		/* Mute */
	अणु 0x807f01, KEY_RECORD पूर्ण,	/* Record */
	अणु 0x807f02, KEY_CHANNELUP पूर्ण,	/* Channel+ */
	अणु 0x807f03, KEY_TIME पूर्ण,		/* TimeShअगरt */
	अणु 0x807f04, KEY_VOLUMEUP पूर्ण,	/* Volume- */
	अणु 0x807f05, KEY_SCREEN पूर्ण,	/* FullScreen */
	अणु 0x807f06, KEY_VOLUMEDOWN पूर्ण,	/* Volume- */
	अणु 0x807f07, KEY_NUMERIC_0 पूर्ण,	/* 0 */
	अणु 0x807f08, KEY_CHANNELDOWN पूर्ण,	/* Channel- */
	अणु 0x807f09, KEY_PREVIOUS पूर्ण,	/* Recall */
	अणु 0x807f0a, KEY_NUMERIC_1 पूर्ण,	/* 1 */
	अणु 0x807f1b, KEY_NUMERIC_2 पूर्ण,	/* 2 */
	अणु 0x807f1f, KEY_NUMERIC_3 पूर्ण,	/* 3 */
	अणु 0x807f0c, KEY_NUMERIC_4 पूर्ण,	/* 4 */
	अणु 0x807f0d, KEY_NUMERIC_5 पूर्ण,	/* 5 */
	अणु 0x807f0e, KEY_NUMERIC_6 पूर्ण,	/* 6 */
	अणु 0x807f00, KEY_NUMERIC_7 पूर्ण,	/* 7 */
	अणु 0x807f0f, KEY_NUMERIC_8 पूर्ण,	/* 8 */
	अणु 0x807f19, KEY_NUMERIC_9 पूर्ण,	/* 9 */

	/* Type 2 */
	/* keys stereo, snapshot unasचिन्हित */
	अणु 0x866b00, KEY_NUMERIC_0 पूर्ण,
	अणु 0x866b01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x866b02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x866b03, KEY_NUMERIC_3 पूर्ण,
	अणु 0x866b04, KEY_NUMERIC_4 पूर्ण,
	अणु 0x866b05, KEY_NUMERIC_5 पूर्ण,
	अणु 0x866b06, KEY_NUMERIC_6 पूर्ण,
	अणु 0x866b07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x866b08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x866b09, KEY_NUMERIC_9 पूर्ण,
	अणु 0x866b12, KEY_POWER पूर्ण,
	अणु 0x866b13, KEY_MUTE पूर्ण,
	अणु 0x866b0a, KEY_PREVIOUS पूर्ण, /* Recall */
	अणु 0x866b1e, KEY_PAUSE पूर्ण,
	अणु 0x866b0c, KEY_VOLUMEUP पूर्ण,
	अणु 0x866b18, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x866b0b, KEY_CHANNELUP पूर्ण,
	अणु 0x866b18, KEY_CHANNELDOWN पूर्ण,
	अणु 0x866b10, KEY_ZOOM पूर्ण,
	अणु 0x866b1d, KEY_RECORD पूर्ण,
	अणु 0x866b0e, KEY_STOP पूर्ण,
	अणु 0x866b11, KEY_EPGपूर्ण,
	अणु 0x866b1a, KEY_FASTFORWARD पूर्ण,
	अणु 0x866b0f, KEY_REWIND पूर्ण,
	अणु 0x866b1c, KEY_TV पूर्ण,
	अणु 0x866b1b, KEY_TEXT पूर्ण,

पूर्ण;

अटल काष्ठा rc_map_list it913x_v2_map = अणु
	.map = अणु
		.scan     = it913x_v2_rc,
		.size     = ARRAY_SIZE(it913x_v2_rc),
		.rc_proto = RC_PROTO_NECX,
		.name     = RC_MAP_IT913X_V2,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_it913x_v2_map(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&it913x_v2_map);
पूर्ण

अटल व्योम __निकास निकास_rc_it913x_v2_map(व्योम)
अणु
	rc_map_unरेजिस्टर(&it913x_v2_map);
पूर्ण

module_init(init_rc_it913x_v2_map)
module_निकास(निकास_rc_it913x_v2_map)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Malcolm Priestley tvboxspy@gmail.com");
