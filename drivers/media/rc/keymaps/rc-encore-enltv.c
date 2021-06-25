<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// encore-enltv.h - Keytable क्रम encore_enltv Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Encore ENLTV-FM  - black plastic, white front cover with white glowing buttons
    Juan Pablo Sormani <sorman@gmail.com> */

अटल काष्ठा rc_map_table encore_enltv[] = अणु

	/* Power button करोes nothing, neither in Winकरोws app,
	 although it sends data (used क्रम BIOS wakeup?) */
	अणु 0x0d, KEY_MUTE पूर्ण,

	अणु 0x1e, KEY_TV पूर्ण,
	अणु 0x00, KEY_VIDEO पूर्ण,
	अणु 0x01, KEY_AUDIO पूर्ण,		/* music */
	अणु 0x02, KEY_CAMERA पूर्ण,		/* picture */

	अणु 0x1f, KEY_NUMERIC_1 पूर्ण,
	अणु 0x03, KEY_NUMERIC_2 पूर्ण,
	अणु 0x04, KEY_NUMERIC_3 पूर्ण,
	अणु 0x05, KEY_NUMERIC_4 पूर्ण,
	अणु 0x1c, KEY_NUMERIC_5 पूर्ण,
	अणु 0x06, KEY_NUMERIC_6 पूर्ण,
	अणु 0x07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x1d, KEY_NUMERIC_9 पूर्ण,
	अणु 0x0a, KEY_NUMERIC_0 पूर्ण,

	अणु 0x09, KEY_LIST पूर्ण,		/* -/-- */
	अणु 0x0b, KEY_LAST पूर्ण,		/* recall */

	अणु 0x14, KEY_HOME पूर्ण,		/* win start menu */
	अणु 0x15, KEY_EXIT पूर्ण,		/* निकास */
	अणु 0x16, KEY_CHANNELUP पूर्ण,	/* UP */
	अणु 0x12, KEY_CHANNELDOWN पूर्ण,	/* DOWN */
	अणु 0x0c, KEY_VOLUMEUP पूर्ण,		/* RIGHT */
	अणु 0x17, KEY_VOLUMEDOWN पूर्ण,	/* LEFT */

	अणु 0x18, KEY_ENTER पूर्ण,		/* OK */

	अणु 0x0e, KEY_ESC पूर्ण,
	अणु 0x13, KEY_CYCLEWINDOWS पूर्ण,	/* desktop */
	अणु 0x11, KEY_TAB पूर्ण,
	अणु 0x19, KEY_SWITCHVIDEOMODE पूर्ण,	/* चयन */

	अणु 0x1a, KEY_MENU पूर्ण,
	अणु 0x1b, KEY_ZOOM पूर्ण,		/* fullscreen */
	अणु 0x44, KEY_TIME पूर्ण,		/* समय shअगरt */
	अणु 0x40, KEY_MODE पूर्ण,		/* source */

	अणु 0x5a, KEY_RECORD पूर्ण,
	अणु 0x42, KEY_PLAY पूर्ण,		/* play/छोड़ो */
	अणु 0x45, KEY_STOP पूर्ण,
	अणु 0x43, KEY_CAMERA पूर्ण,		/* camera icon */

	अणु 0x48, KEY_REWIND पूर्ण,
	अणु 0x4a, KEY_FASTFORWARD पूर्ण,
	अणु 0x49, KEY_PREVIOUS पूर्ण,
	अणु 0x4b, KEY_NEXT पूर्ण,

	अणु 0x4c, KEY_FAVORITES पूर्ण,	/* tv wall */
	अणु 0x4d, KEY_SOUND पूर्ण,		/* DVD sound */
	अणु 0x4e, KEY_LANGUAGE पूर्ण,		/* DVD lang */
	अणु 0x4f, KEY_TEXT पूर्ण,		/* DVD text */

	अणु 0x50, KEY_SLEEP पूर्ण,		/* shutकरोwn */
	अणु 0x51, KEY_MODE पूर्ण,		/* stereo > मुख्य */
	अणु 0x52, KEY_SELECT पूर्ण,		/* stereo > sap */
	अणु 0x53, KEY_TEXT पूर्ण,		/* teletext */


	अणु 0x59, KEY_RED पूर्ण,		/* AP1 */
	अणु 0x41, KEY_GREEN पूर्ण,		/* AP2 */
	अणु 0x47, KEY_YELLOW पूर्ण,		/* AP3 */
	अणु 0x57, KEY_BLUE पूर्ण,		/* AP4 */
पूर्ण;

अटल काष्ठा rc_map_list encore_enltv_map = अणु
	.map = अणु
		.scan     = encore_enltv,
		.size     = ARRAY_SIZE(encore_enltv),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_ENCORE_ENLTV,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_encore_enltv(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&encore_enltv_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_encore_enltv(व्योम)
अणु
	rc_map_unरेजिस्टर(&encore_enltv_map);
पूर्ण

module_init(init_rc_map_encore_enltv)
module_निकास(निकास_rc_map_encore_enltv)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
