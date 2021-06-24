<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// flydvb.h - Keytable क्रम flydvb Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table flydvb[] = अणु
	अणु 0x01, KEY_ZOOM पूर्ण,		/* Full Screen */
	अणु 0x00, KEY_POWER पूर्ण,		/* Power */

	अणु 0x03, KEY_NUMERIC_1 पूर्ण,
	अणु 0x04, KEY_NUMERIC_2 पूर्ण,
	अणु 0x05, KEY_NUMERIC_3 पूर्ण,
	अणु 0x07, KEY_NUMERIC_4 पूर्ण,
	अणु 0x08, KEY_NUMERIC_5 पूर्ण,
	अणु 0x09, KEY_NUMERIC_6 पूर्ण,
	अणु 0x0b, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0c, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0d, KEY_NUMERIC_9 पूर्ण,
	अणु 0x06, KEY_AGAIN पूर्ण,		/* Recall */
	अणु 0x0f, KEY_NUMERIC_0 पूर्ण,
	अणु 0x10, KEY_MUTE पूर्ण,		/* Mute */
	अणु 0x02, KEY_RADIO पूर्ण,		/* TV/Radio */
	अणु 0x1b, KEY_LANGUAGE पूर्ण,		/* SAP (Second Audio Program) */

	अणु 0x14, KEY_VOLUMEUP पूर्ण,		/* VOL+ */
	अणु 0x17, KEY_VOLUMEDOWN पूर्ण,	/* VOL- */
	अणु 0x12, KEY_CHANNELUP पूर्ण,	/* CH+ */
	अणु 0x13, KEY_CHANNELDOWN पूर्ण,	/* CH- */
	अणु 0x1d, KEY_ENTER पूर्ण,		/* Enter */

	अणु 0x1a, KEY_TV2 पूर्ण,		/* PIP */
	अणु 0x18, KEY_VIDEO पूर्ण,		/* Source */

	अणु 0x1e, KEY_RECORD पूर्ण,		/* Record/Pause */
	अणु 0x15, KEY_ANGLE पूर्ण,		/* Swap (no label on key) */
	अणु 0x1c, KEY_PAUSE पूर्ण,		/* Timeshअगरt/Pause */
	अणु 0x19, KEY_BACK पूर्ण,		/* Rewind << */
	अणु 0x0a, KEY_PLAYPAUSE पूर्ण,	/* Play/Pause */
	अणु 0x1f, KEY_FORWARD पूर्ण,		/* Forward >> */
	अणु 0x16, KEY_PREVIOUS पूर्ण,		/* Back |<< */
	अणु 0x11, KEY_STOP पूर्ण,		/* Stop */
	अणु 0x0e, KEY_NEXT पूर्ण,		/* End >>| */
पूर्ण;

अटल काष्ठा rc_map_list flydvb_map = अणु
	.map = अणु
		.scan     = flydvb,
		.size     = ARRAY_SIZE(flydvb),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_FLYDVB,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_flydvb(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&flydvb_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_flydvb(व्योम)
अणु
	rc_map_unरेजिस्टर(&flydvb_map);
पूर्ण

module_init(init_rc_map_flydvb)
module_निकास(निकास_rc_map_flydvb)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
