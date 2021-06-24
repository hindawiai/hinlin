<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SnapStream Firefly X10 RF remote keytable
 *
 * Copyright (C) 2011 Anssi Hannula <anssi.hannula@?ki.fi>
 */

#समावेश <linux/module.h>
#समावेश <media/rc-map.h>

अटल काष्ठा rc_map_table snapstream_firefly[] = अणु
	अणु 0x2c, KEY_ZOOM पूर्ण,       /* Maximize */
	अणु 0x02, KEY_CLOSE पूर्ण,

	अणु 0x0d, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0e, KEY_NUMERIC_2 पूर्ण,
	अणु 0x0f, KEY_NUMERIC_3 पूर्ण,
	अणु 0x10, KEY_NUMERIC_4 पूर्ण,
	अणु 0x11, KEY_NUMERIC_5 पूर्ण,
	अणु 0x12, KEY_NUMERIC_6 पूर्ण,
	अणु 0x13, KEY_NUMERIC_7 पूर्ण,
	अणु 0x14, KEY_NUMERIC_8 पूर्ण,
	अणु 0x15, KEY_NUMERIC_9 पूर्ण,
	अणु 0x17, KEY_NUMERIC_0 पूर्ण,
	अणु 0x16, KEY_BACK पूर्ण,
	अणु 0x18, KEY_KPENTER पूर्ण,    /* ent */

	अणु 0x09, KEY_VOLUMEUP पूर्ण,
	अणु 0x08, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x0a, KEY_MUTE पूर्ण,
	अणु 0x0b, KEY_CHANNELUP पूर्ण,
	अणु 0x0c, KEY_CHANNELDOWN पूर्ण,
	अणु 0x00, KEY_VENDOR पूर्ण,     /* firefly */

	अणु 0x2e, KEY_INFO पूर्ण,
	अणु 0x2f, KEY_OPTION पूर्ण,

	अणु 0x1d, KEY_LEFT पूर्ण,
	अणु 0x1f, KEY_RIGHT पूर्ण,
	अणु 0x22, KEY_DOWN पूर्ण,
	अणु 0x1a, KEY_UP पूर्ण,
	अणु 0x1e, KEY_OK पूर्ण,

	अणु 0x1c, KEY_MENU पूर्ण,
	अणु 0x20, KEY_EXIT पूर्ण,

	अणु 0x27, KEY_RECORD पूर्ण,
	अणु 0x25, KEY_PLAY पूर्ण,
	अणु 0x28, KEY_STOP पूर्ण,
	अणु 0x24, KEY_REWIND पूर्ण,
	अणु 0x26, KEY_FORWARD पूर्ण,
	अणु 0x29, KEY_PAUSE पूर्ण,
	अणु 0x2b, KEY_PREVIOUS पूर्ण,
	अणु 0x2a, KEY_NEXT पूर्ण,

	अणु 0x06, KEY_AUDIO पूर्ण,      /* Music */
	अणु 0x05, KEY_IMAGES पूर्ण,     /* Photos */
	अणु 0x04, KEY_DVD पूर्ण,
	अणु 0x03, KEY_TV पूर्ण,
	अणु 0x07, KEY_VIDEO पूर्ण,

	अणु 0x01, KEY_HELP पूर्ण,
	अणु 0x2d, KEY_MODE पूर्ण,       /* Mouse */

	अणु 0x19, KEY_A पूर्ण,
	अणु 0x1b, KEY_B पूर्ण,
	अणु 0x21, KEY_C पूर्ण,
	अणु 0x23, KEY_D पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list snapstream_firefly_map = अणु
	.map = अणु
		.scan     = snapstream_firefly,
		.size     = ARRAY_SIZE(snapstream_firefly),
		.rc_proto = RC_PROTO_OTHER,
		.name     = RC_MAP_SNAPSTREAM_FIREFLY,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_snapstream_firefly(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&snapstream_firefly_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_snapstream_firefly(व्योम)
अणु
	rc_map_unरेजिस्टर(&snapstream_firefly_map);
पूर्ण

module_init(init_rc_map_snapstream_firefly)
module_निकास(निकास_rc_map_snapstream_firefly)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anssi Hannula <anssi.hannula@iki.fi>");
