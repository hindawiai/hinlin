<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// pv951.h - Keytable क्रम pv951 Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Mark Phalan <phalanm@o2.ie> */

अटल काष्ठा rc_map_table pv951[] = अणु
	अणु 0x00, KEY_NUMERIC_0 पूर्ण,
	अणु 0x01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x03, KEY_NUMERIC_3 पूर्ण,
	अणु 0x04, KEY_NUMERIC_4 पूर्ण,
	अणु 0x05, KEY_NUMERIC_5 पूर्ण,
	अणु 0x06, KEY_NUMERIC_6 पूर्ण,
	अणु 0x07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x09, KEY_NUMERIC_9 पूर्ण,

	अणु 0x12, KEY_POWER पूर्ण,
	अणु 0x10, KEY_MUTE पूर्ण,
	अणु 0x1f, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x1b, KEY_VOLUMEUP पूर्ण,
	अणु 0x1a, KEY_CHANNELUP पूर्ण,
	अणु 0x1e, KEY_CHANNELDOWN पूर्ण,
	अणु 0x0e, KEY_PAGEUP पूर्ण,
	अणु 0x1d, KEY_PAGEDOWN पूर्ण,
	अणु 0x13, KEY_SOUND पूर्ण,

	अणु 0x18, KEY_KPPLUSMINUS पूर्ण,	/* CH +/- */
	अणु 0x16, KEY_SUBTITLE पूर्ण,		/* CC */
	अणु 0x0d, KEY_TEXT पूर्ण,		/* TTX */
	अणु 0x0b, KEY_TV पूर्ण,		/* AIR/CBL */
	अणु 0x11, KEY_PC पूर्ण,		/* PC/TV */
	अणु 0x17, KEY_OK पूर्ण,		/* CH RTN */
	अणु 0x19, KEY_MODE पूर्ण,		/* FUNC */
	अणु 0x0c, KEY_SEARCH पूर्ण,		/* AUTOSCAN */

	/* Not sure what to करो with these ones! */
	अणु 0x0f, KEY_VIDEO पूर्ण,		/* SOURCE */
	अणु 0x0a, KEY_KPPLUS पूर्ण,		/* +100 */
	अणु 0x14, KEY_EQUAL पूर्ण,		/* SYNC */
	अणु 0x1c, KEY_TV पूर्ण,		/* PC/TV */
पूर्ण;

अटल काष्ठा rc_map_list pv951_map = अणु
	.map = अणु
		.scan     = pv951,
		.size     = ARRAY_SIZE(pv951),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_PV951,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_pv951(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&pv951_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_pv951(व्योम)
अणु
	rc_map_unरेजिस्टर(&pv951_map);
पूर्ण

module_init(init_rc_map_pv951)
module_निकास(निकास_rc_map_pv951)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
