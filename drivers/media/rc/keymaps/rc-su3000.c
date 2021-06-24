<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* rc-su3000.h - Keytable क्रम Geniatech HDStar Remote Controller
 *
 * Copyright (c) 2013 by Evgeny Plehov <Evgeny Plehov@ukr.net>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table su3000[] = अणु
	अणु 0x25, KEY_POWER पूर्ण,	/* right-bottom Red */
	अणु 0x0a, KEY_MUTE पूर्ण,	/* -/-- */
	अणु 0x01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x03, KEY_NUMERIC_3 पूर्ण,
	अणु 0x04, KEY_NUMERIC_4 पूर्ण,
	अणु 0x05, KEY_NUMERIC_5 पूर्ण,
	अणु 0x06, KEY_NUMERIC_6 पूर्ण,
	अणु 0x07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x09, KEY_NUMERIC_9 पूर्ण,
	अणु 0x00, KEY_NUMERIC_0 पूर्ण,
	अणु 0x20, KEY_UP पूर्ण,	/* CH+ */
	अणु 0x21, KEY_DOWN पूर्ण,	/* CH+ */
	अणु 0x12, KEY_VOLUMEUP पूर्ण,	/* Brightness Up */
	अणु 0x13, KEY_VOLUMEDOWN पूर्ण,/* Brightness Down */
	अणु 0x1f, KEY_RECORD पूर्ण,
	अणु 0x17, KEY_PLAY पूर्ण,
	अणु 0x16, KEY_PAUSE पूर्ण,
	अणु 0x0b, KEY_STOP पूर्ण,
	अणु 0x27, KEY_FASTFORWARD पूर्ण,/* >> */
	अणु 0x26, KEY_REWIND पूर्ण,	/* << */
	अणु 0x0d, KEY_OK पूर्ण,	/* Mute */
	अणु 0x11, KEY_LEFT पूर्ण,	/* VOL- */
	अणु 0x10, KEY_RIGHT पूर्ण,	/* VOL+ */
	अणु 0x29, KEY_BACK पूर्ण,	/* button under 9 */
	अणु 0x2c, KEY_MENU पूर्ण,	/* TTX */
	अणु 0x2b, KEY_EPG पूर्ण,	/* EPG */
	अणु 0x1e, KEY_RED पूर्ण,	/* OSD */
	अणु 0x0e, KEY_GREEN पूर्ण,	/* Winकरोw */
	अणु 0x2d, KEY_YELLOW पूर्ण,	/* button under << */
	अणु 0x0f, KEY_BLUE पूर्ण,	/* bottom yellow button */
	अणु 0x14, KEY_AUDIO पूर्ण,	/* Snapshot */
	अणु 0x38, KEY_TV पूर्ण,	/* TV/Radio */
	अणु 0x0c, KEY_ESC पूर्ण	/* upper Red button */
पूर्ण;

अटल काष्ठा rc_map_list su3000_map = अणु
	.map = अणु
		.scan     = su3000,
		.size     = ARRAY_SIZE(su3000),
		.rc_proto = RC_PROTO_RC5,
		.name     = RC_MAP_SU3000,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_su3000(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&su3000_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_su3000(व्योम)
अणु
	rc_map_unरेजिस्टर(&su3000_map);
पूर्ण

module_init(init_rc_map_su3000)
module_निकास(निकास_rc_map_su3000)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Evgeny Plehov <Evgeny Plehov@ukr.net>");
