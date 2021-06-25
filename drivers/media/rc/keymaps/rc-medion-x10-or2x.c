<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Medion X10 OR22/OR24 RF remote keytable
 *
 * Copyright (C) 2012 Anssi Hannula <anssi.hannula@iki.fi>
 *
 * This keymap is क्रम several Medion X10 remotes that have the Winकरोws MCE
 * button. This has been tested with a "RF VISTA Remote Control", OR24V,
 * P/N 20035335, but should work with other variants that have the same
 * buttons, such as OR22V and OR24E.
 */

#समावेश <linux/module.h>
#समावेश <media/rc-map.h>

अटल काष्ठा rc_map_table medion_x10_or2x[] = अणु
	अणु 0x02, KEY_POWER पूर्ण,
	अणु 0x16, KEY_TEXT पूर्ण,   /* "T" in a box, क्रम teletext */

	अणु 0x09, KEY_VOLUMEUP पूर्ण,
	अणु 0x08, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x00, KEY_MUTE पूर्ण,
	अणु 0x0b, KEY_CHANNELUP पूर्ण,
	अणु 0x0c, KEY_CHANNELDOWN पूर्ण,

	अणु 0x32, KEY_RED पूर्ण,
	अणु 0x33, KEY_GREEN पूर्ण,
	अणु 0x34, KEY_YELLOW पूर्ण,
	अणु 0x35, KEY_BLUE पूर्ण,

	अणु 0x18, KEY_PVR पूर्ण,    /* record symbol inside a tv symbol */
	अणु 0x04, KEY_DVD पूर्ण,    /* disc symbol */
	अणु 0x31, KEY_EPG पूर्ण,    /* a tv schedule symbol */
	अणु 0x1c, KEY_TV पूर्ण,     /* play symbol inside a tv symbol */
	अणु 0x20, KEY_BACK पूर्ण,
	अणु 0x2f, KEY_INFO पूर्ण,

	अणु 0x1a, KEY_UP पूर्ण,
	अणु 0x22, KEY_DOWN पूर्ण,
	अणु 0x1d, KEY_LEFT पूर्ण,
	अणु 0x1f, KEY_RIGHT पूर्ण,
	अणु 0x1e, KEY_OK पूर्ण,

	अणु 0x1b, KEY_MEDIA पूर्ण,  /* Winकरोws MCE button */

	अणु 0x21, KEY_PREVIOUS पूर्ण,
	अणु 0x23, KEY_NEXT पूर्ण,
	अणु 0x24, KEY_REWIND पूर्ण,
	अणु 0x26, KEY_FORWARD पूर्ण,
	अणु 0x25, KEY_PLAY पूर्ण,
	अणु 0x28, KEY_STOP पूर्ण,
	अणु 0x29, KEY_PAUSE पूर्ण,
	अणु 0x27, KEY_RECORD पूर्ण,

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
	अणु 0x30, KEY_CLEAR पूर्ण,
	अणु 0x36, KEY_ENTER पूर्ण,
	अणु 0x37, KEY_NUMERIC_STAR पूर्ण,
	अणु 0x38, KEY_NUMERIC_POUND पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list medion_x10_or2x_map = अणु
	.map = अणु
		.scan     = medion_x10_or2x,
		.size     = ARRAY_SIZE(medion_x10_or2x),
		.rc_proto = RC_PROTO_OTHER,
		.name     = RC_MAP_MEDION_X10_OR2X,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_medion_x10_or2x(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&medion_x10_or2x_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_medion_x10_or2x(व्योम)
अणु
	rc_map_unरेजिस्टर(&medion_x10_or2x_map);
पूर्ण

module_init(init_rc_map_medion_x10_or2x)
module_निकास(निकास_rc_map_medion_x10_or2x)

MODULE_DESCRIPTION("Medion X10 OR22/OR24 RF remote keytable");
MODULE_AUTHOR("Anssi Hannula <anssi.hannula@iki.fi>");
MODULE_LICENSE("GPL");
