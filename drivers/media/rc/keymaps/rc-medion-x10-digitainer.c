<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Medion X10 RF remote keytable (Digitainer variant)
 *
 * Copyright (C) 2012 Anssi Hannula <anssi.hannula@iki.fi>
 *
 * This keymap is क्रम a variant that has a distinctive scrollwheel instead of
 * up/करोwn buttons (tested with P/N 40009936 / 20018268), reportedly
 * originally shipped with Medion Digitainer but now sold separately simply as
 * an "X10" remote.
 */

#समावेश <linux/module.h>
#समावेश <media/rc-map.h>

अटल काष्ठा rc_map_table medion_x10_digitainer[] = अणु
	अणु 0x02, KEY_POWER पूर्ण,

	अणु 0x2c, KEY_TV पूर्ण,
	अणु 0x2d, KEY_VIDEO पूर्ण,
	अणु 0x04, KEY_DVD पूर्ण,    /* CD/DVD */
	अणु 0x16, KEY_TEXT पूर्ण,   /* "teletext" icon, i.e. a screen with lines */
	अणु 0x06, KEY_AUDIO पूर्ण,
	अणु 0x2e, KEY_RADIO पूर्ण,
	अणु 0x31, KEY_EPG पूर्ण,    /* a screen with an खोलो book */
	अणु 0x05, KEY_IMAGES पूर्ण, /* Photo */
	अणु 0x2f, KEY_INFO पूर्ण,

	अणु 0x78, KEY_UP पूर्ण,     /* scrollwheel up 1 notch */
	/* 0x79..0x7f: 2-8 notches, driver repeats 0x78 entry */

	अणु 0x70, KEY_DOWN पूर्ण,   /* scrollwheel करोwn 1 notch */
	/* 0x71..0x77: 2-8 notches, driver repeats 0x70 entry */

	अणु 0x19, KEY_MENU पूर्ण,
	अणु 0x1d, KEY_LEFT पूर्ण,
	अणु 0x1e, KEY_OK पूर्ण,     /* scrollwheel press */
	अणु 0x1f, KEY_RIGHT पूर्ण,
	अणु 0x20, KEY_BACK पूर्ण,

	अणु 0x09, KEY_VOLUMEUP पूर्ण,
	अणु 0x08, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x00, KEY_MUTE पूर्ण,

	अणु 0x1b, KEY_SELECT पूर्ण, /* also has "U" rotated 90 degrees CCW */

	अणु 0x0b, KEY_CHANNELUP पूर्ण,
	अणु 0x0c, KEY_CHANNELDOWN पूर्ण,
	अणु 0x1c, KEY_LAST पूर्ण,

	अणु 0x32, KEY_RED पूर्ण,    /* also Audio */
	अणु 0x33, KEY_GREEN पूर्ण,  /* also Subtitle */
	अणु 0x34, KEY_YELLOW पूर्ण, /* also Angle */
	अणु 0x35, KEY_BLUE पूर्ण,   /* also Title */

	अणु 0x28, KEY_STOP पूर्ण,
	अणु 0x29, KEY_PAUSE पूर्ण,
	अणु 0x25, KEY_PLAY पूर्ण,
	अणु 0x21, KEY_PREVIOUS पूर्ण,
	अणु 0x18, KEY_CAMERA पूर्ण,
	अणु 0x23, KEY_NEXT पूर्ण,
	अणु 0x24, KEY_REWIND पूर्ण,
	अणु 0x27, KEY_RECORD पूर्ण,
	अणु 0x26, KEY_FORWARD पूर्ण,

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

	/* these करो not actually exist on this remote, but these scancodes
	 * exist on all other Medion X10 remotes and adding them here allows
	 * such remotes to be adequately usable with this keymap in हाल
	 * this keymap is wrongly used with them (which is quite possible as
	 * there are lots of dअगरferent Medion X10 remotes): */
	अणु 0x1a, KEY_UP पूर्ण,
	अणु 0x22, KEY_DOWN पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list medion_x10_digitainer_map = अणु
	.map = अणु
		.scan     = medion_x10_digitainer,
		.size     = ARRAY_SIZE(medion_x10_digitainer),
		.rc_proto = RC_PROTO_OTHER,
		.name     = RC_MAP_MEDION_X10_DIGITAINER,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_medion_x10_digitainer(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&medion_x10_digitainer_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_medion_x10_digitainer(व्योम)
अणु
	rc_map_unरेजिस्टर(&medion_x10_digitainer_map);
पूर्ण

module_init(init_rc_map_medion_x10_digitainer)
module_निकास(निकास_rc_map_medion_x10_digitainer)

MODULE_DESCRIPTION("Medion X10 RF remote keytable (Digitainer variant)");
MODULE_AUTHOR("Anssi Hannula <anssi.hannula@iki.fi>");
MODULE_LICENSE("GPL");
