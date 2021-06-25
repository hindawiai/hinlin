<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// genius-tvgo-a11mce.h - Keytable क्रम genius_tvgo_a11mce Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/*
 * Remote control क्रम the Genius TVGO A11MCE
 * Adrian Pardini <parकरो.bsso@gmail.com>
 */

अटल काष्ठा rc_map_table genius_tvgo_a11mce[] = अणु
	/* Keys 0 to 9 */
	अणु 0x48, KEY_NUMERIC_0 पूर्ण,
	अणु 0x09, KEY_NUMERIC_1 पूर्ण,
	अणु 0x1d, KEY_NUMERIC_2 पूर्ण,
	अणु 0x1f, KEY_NUMERIC_3 पूर्ण,
	अणु 0x19, KEY_NUMERIC_4 पूर्ण,
	अणु 0x1b, KEY_NUMERIC_5 पूर्ण,
	अणु 0x11, KEY_NUMERIC_6 पूर्ण,
	अणु 0x17, KEY_NUMERIC_7 पूर्ण,
	अणु 0x12, KEY_NUMERIC_8 पूर्ण,
	अणु 0x16, KEY_NUMERIC_9 पूर्ण,

	अणु 0x54, KEY_RECORD पूर्ण,		/* recording */
	अणु 0x06, KEY_MUTE पूर्ण,		/* mute */
	अणु 0x10, KEY_POWER पूर्ण,
	अणु 0x40, KEY_LAST पूर्ण,		/* recall */
	अणु 0x4c, KEY_CHANNELUP पूर्ण,	/* channel / program + */
	अणु 0x00, KEY_CHANNELDOWN पूर्ण,	/* channel / program - */
	अणु 0x0d, KEY_VOLUMEUP पूर्ण,
	अणु 0x15, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x4d, KEY_OK पूर्ण,		/* also labeled as Pause */
	अणु 0x1c, KEY_ZOOM पूर्ण,		/* full screen and Stop*/
	अणु 0x02, KEY_MODE पूर्ण,		/* AV Source or Rewind*/
	अणु 0x04, KEY_LIST पूर्ण,		/* -/-- */
	/* small arrows above numbers */
	अणु 0x1a, KEY_NEXT पूर्ण,		/* also Fast Forward */
	अणु 0x0e, KEY_PREVIOUS पूर्ण,		/* also Rewind */
	/* these are in a rather non standard layout and have
	an alternate name written */
	अणु 0x1e, KEY_UP पूर्ण,		/* Video Setting */
	अणु 0x0a, KEY_DOWN पूर्ण,		/* Video Default */
	अणु 0x05, KEY_CAMERA पूर्ण,		/* Snapshot */
	अणु 0x0c, KEY_RIGHT पूर्ण,		/* Hide Panel */
	/* Four buttons without label */
	अणु 0x49, KEY_RED पूर्ण,
	अणु 0x0b, KEY_GREEN पूर्ण,
	अणु 0x13, KEY_YELLOW पूर्ण,
	अणु 0x50, KEY_BLUE पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list genius_tvgo_a11mce_map = अणु
	.map = अणु
		.scan     = genius_tvgo_a11mce,
		.size     = ARRAY_SIZE(genius_tvgo_a11mce),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_GENIUS_TVGO_A11MCE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_genius_tvgo_a11mce(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&genius_tvgo_a11mce_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_genius_tvgo_a11mce(व्योम)
अणु
	rc_map_unरेजिस्टर(&genius_tvgo_a11mce_map);
पूर्ण

module_init(init_rc_map_genius_tvgo_a11mce)
module_निकास(निकास_rc_map_genius_tvgo_a11mce)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
