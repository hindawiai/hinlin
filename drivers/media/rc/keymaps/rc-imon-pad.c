<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* rc5-imon-pad.c - Keytable क्रम SoundGraph iMON PAD and Antec Veris
 * RM-200 Remote Control
 *
 * Copyright (c) 2010 by Jarod Wilson <jarod@redhat.com>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/*
 * standard imon remote key table, which isn't really entirely
 * "standard", as dअगरferent receivers decode the same key on the
 * same remote to dअगरferent hex codes, and the silkscreened names
 * vary a bit between the SoundGraph and Antec remotes... ugh.
 */
अटल काष्ठा rc_map_table imon_pad[] = अणु
	/* keys sorted mostly by frequency of use to optimize lookups */
	अणु 0x2a8195b7, KEY_REWIND पूर्ण,
	अणु 0x298315b7, KEY_REWIND पूर्ण,
	अणु 0x2b8115b7, KEY_FASTFORWARD पूर्ण,
	अणु 0x2b8315b7, KEY_FASTFORWARD पूर्ण,
	अणु 0x2b9115b7, KEY_PREVIOUS पूर्ण,
	अणु 0x298195b7, KEY_NEXT पूर्ण,

	अणु 0x2a8115b7, KEY_PLAY पूर्ण,
	अणु 0x2a8315b7, KEY_PLAY पूर्ण,
	अणु 0x2a9115b7, KEY_PAUSE पूर्ण,
	अणु 0x2b9715b7, KEY_STOP पूर्ण,
	अणु 0x298115b7, KEY_RECORD पूर्ण,

	अणु 0x01008000, KEY_UP पूर्ण,
	अणु 0x01007f00, KEY_DOWN पूर्ण,
	अणु 0x01000080, KEY_LEFT पूर्ण,
	अणु 0x0100007f, KEY_RIGHT पूर्ण,

	अणु 0x2aa515b7, KEY_UP पूर्ण,
	अणु 0x289515b7, KEY_DOWN पूर्ण,
	अणु 0x29a515b7, KEY_LEFT पूर्ण,
	अणु 0x2ba515b7, KEY_RIGHT पूर्ण,

	अणु 0x0200002c, KEY_SPACE पूर्ण, /* Select/Space */
	अणु 0x2a9315b7, KEY_SPACE पूर्ण, /* Select/Space */
	अणु 0x02000028, KEY_ENTER पूर्ण,
	अणु 0x28a195b7, KEY_ENTER पूर्ण,
	अणु 0x288195b7, KEY_EXIT पूर्ण,
	अणु 0x02000029, KEY_ESC पूर्ण,
	अणु 0x2bb715b7, KEY_ESC पूर्ण,
	अणु 0x0200002a, KEY_BACKSPACE पूर्ण,
	अणु 0x28a115b7, KEY_BACKSPACE पूर्ण,

	अणु 0x2b9595b7, KEY_MUTE पूर्ण,
	अणु 0x28a395b7, KEY_VOLUMEUP पूर्ण,
	अणु 0x28a595b7, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x289395b7, KEY_CHANNELUP पूर्ण,
	अणु 0x288795b7, KEY_CHANNELDOWN पूर्ण,

	अणु 0x0200001e, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0200001f, KEY_NUMERIC_2 पूर्ण,
	अणु 0x02000020, KEY_NUMERIC_3 पूर्ण,
	अणु 0x02000021, KEY_NUMERIC_4 पूर्ण,
	अणु 0x02000022, KEY_NUMERIC_5 पूर्ण,
	अणु 0x02000023, KEY_NUMERIC_6 पूर्ण,
	अणु 0x02000024, KEY_NUMERIC_7 पूर्ण,
	अणु 0x02000025, KEY_NUMERIC_8 पूर्ण,
	अणु 0x02000026, KEY_NUMERIC_9 पूर्ण,
	अणु 0x02000027, KEY_NUMERIC_0 पूर्ण,

	अणु 0x28b595b7, KEY_NUMERIC_1 पूर्ण,
	अणु 0x2bb195b7, KEY_NUMERIC_2 पूर्ण,
	अणु 0x28b195b7, KEY_NUMERIC_3 पूर्ण,
	अणु 0x2a8595b7, KEY_NUMERIC_4 पूर्ण,
	अणु 0x299595b7, KEY_NUMERIC_5 पूर्ण,
	अणु 0x2aa595b7, KEY_NUMERIC_6 पूर्ण,
	अणु 0x2b9395b7, KEY_NUMERIC_7 पूर्ण,
	अणु 0x2a8515b7, KEY_NUMERIC_8 पूर्ण,
	अणु 0x2aa115b7, KEY_NUMERIC_9 पूर्ण,
	अणु 0x2ba595b7, KEY_NUMERIC_0 पूर्ण,

	अणु 0x02200025, KEY_NUMERIC_STAR पूर्ण,
	अणु 0x28b515b7, KEY_NUMERIC_STAR पूर्ण,
	अणु 0x02200020, KEY_NUMERIC_POUND पूर्ण,
	अणु 0x29a115b7, KEY_NUMERIC_POUND पूर्ण,

	अणु 0x2b8515b7, KEY_VIDEO पूर्ण,
	अणु 0x299195b7, KEY_AUDIO पूर्ण,
	अणु 0x2ba115b7, KEY_IMAGES पूर्ण,
	अणु 0x28a515b7, KEY_TV पूर्ण,
	अणु 0x29a395b7, KEY_DVD पूर्ण,
	अणु 0x29a295b7, KEY_DVD पूर्ण,

	/* the Menu key between DVD and Subtitle on the RM-200... */
	अणु 0x2ba385b7, KEY_MENU पूर्ण,
	अणु 0x2ba395b7, KEY_MENU पूर्ण,

	अणु 0x288515b7, KEY_BOOKMARKS पूर्ण,
	अणु 0x2ab715b7, KEY_CAMERA पूर्ण, /* Thumbnail */
	अणु 0x298595b7, KEY_SUBTITLE पूर्ण,
	अणु 0x2b8595b7, KEY_LANGUAGE पूर्ण,

	अणु 0x29a595b7, KEY_ZOOM पूर्ण,
	अणु 0x2aa395b7, KEY_SCREEN पूर्ण, /* FullScreen */

	अणु 0x299115b7, KEY_KEYBOARD पूर्ण,
	अणु 0x299135b7, KEY_KEYBOARD पूर्ण,

	अणु 0x01010000, BTN_LEFT पूर्ण,
	अणु 0x01020000, BTN_RIGHT पूर्ण,
	अणु 0x01010080, BTN_LEFT पूर्ण,
	अणु 0x01020080, BTN_RIGHT पूर्ण,
	अणु 0x688301b7, BTN_LEFT पूर्ण,
	अणु 0x688481b7, BTN_RIGHT पूर्ण,

	अणु 0x2a9395b7, KEY_CYCLEWINDOWS पूर्ण, /* TaskSwitcher */
	अणु 0x2b8395b7, KEY_TIME पूर्ण, /* Timer */

	अणु 0x289115b7, KEY_POWER पूर्ण,
	अणु 0x29b195b7, KEY_EJECTCD पूर्ण, /* the one next to play */
	अणु 0x299395b7, KEY_EJECTCLOSECD पूर्ण, /* eject (by TaskSw) */

	अणु 0x02800000, KEY_CONTEXT_MENU पूर्ण, /* Left Menu */
	अणु 0x2b8195b7, KEY_CONTEXT_MENU पूर्ण, /* Left Menu*/
	अणु 0x02000065, KEY_COMPOSE पूर्ण, /* RightMenu */
	अणु 0x28b715b7, KEY_COMPOSE पूर्ण, /* RightMenu */
	अणु 0x2ab195b7, KEY_MEDIA पूर्ण, /* Go or MultiMon */
	अणु 0x29b715b7, KEY_DASHBOARD पूर्ण, /* AppLauncher */
पूर्ण;

अटल काष्ठा rc_map_list imon_pad_map = अणु
	.map = अणु
		.scan     = imon_pad,
		.size     = ARRAY_SIZE(imon_pad),
		.rc_proto = RC_PROTO_IMON,
		.name     = RC_MAP_IMON_PAD,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_imon_pad(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&imon_pad_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_imon_pad(व्योम)
अणु
	rc_map_unरेजिस्टर(&imon_pad_map);
पूर्ण

module_init(init_rc_map_imon_pad)
module_निकास(निकास_rc_map_imon_pad)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jarod Wilson <jarod@redhat.com>");
