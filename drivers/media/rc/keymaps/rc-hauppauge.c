<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// rc-hauppauge.c - Keytable क्रम Hauppauge Remote Controllers
//
// keymap imported from ir-keymaps.c
//
// This map currently contains the code क्रम four dअगरferent RCs:
//	- New Hauppauge Gray;
//	- Old Hauppauge Gray (with a golden screen क्रम media keys);
//	- Hauppauge Black;
//	- DSR-0112 remote bundled with Haupauge MiniStick.
//
// Copyright (c) 2010-2011 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/*
 * Hauppauge:the newer, gray remotes (seems there are multiple
 * slightly dअगरferent versions), shipped with cx88+ivtv cards.
 *
 * This table contains the complete RC5 code, instead of just the data part
 */

अटल काष्ठा rc_map_table rc5_hauppauge_new[] = अणु
	/*
	 * Remote Controller Hauppauge Gray found on modern devices
	 * Keycodes start with address = 0x1e
	 */

	अणु 0x1e3b, KEY_SELECT पूर्ण,		/* GO / house symbol */
	अणु 0x1e3d, KEY_POWER2 पूर्ण,		/* प्रणाली घातer (green button) */

	अणु 0x1e1c, KEY_TV पूर्ण,
	अणु 0x1e18, KEY_VIDEO पूर्ण,		/* Videos */
	अणु 0x1e19, KEY_AUDIO पूर्ण,		/* Music */
	अणु 0x1e1a, KEY_CAMERA पूर्ण,		/* Pictures */

	अणु 0x1e1b, KEY_EPG पूर्ण,		/* Guide */
	अणु 0x1e0c, KEY_RADIO पूर्ण,

	अणु 0x1e14, KEY_UP पूर्ण,
	अणु 0x1e15, KEY_DOWN पूर्ण,
	अणु 0x1e16, KEY_LEFT पूर्ण,
	अणु 0x1e17, KEY_RIGHT पूर्ण,
	अणु 0x1e25, KEY_OK पूर्ण,		/* OK */

	अणु 0x1e1f, KEY_EXIT पूर्ण,		/* back/निकास */
	अणु 0x1e0d, KEY_MENU पूर्ण,

	अणु 0x1e10, KEY_VOLUMEUP पूर्ण,
	अणु 0x1e11, KEY_VOLUMEDOWN पूर्ण,

	अणु 0x1e12, KEY_PREVIOUS पूर्ण,	/* previous channel */
	अणु 0x1e0f, KEY_MUTE पूर्ण,

	अणु 0x1e20, KEY_CHANNELUP पूर्ण,	/* channel / program + */
	अणु 0x1e21, KEY_CHANNELDOWN पूर्ण,	/* channel / program - */

	अणु 0x1e37, KEY_RECORD पूर्ण,		/* recording */
	अणु 0x1e36, KEY_STOP पूर्ण,

	अणु 0x1e32, KEY_REWIND पूर्ण,		/* backward << */
	अणु 0x1e35, KEY_PLAY पूर्ण,
	अणु 0x1e34, KEY_FASTFORWARD पूर्ण,	/* क्रमward >> */

	अणु 0x1e24, KEY_PREVIOUSSONG पूर्ण,	/* replay |< */
	अणु 0x1e30, KEY_PAUSE पूर्ण,		/* छोड़ो */
	अणु 0x1e1e, KEY_NEXTSONG पूर्ण,	/* skip >| */

	अणु 0x1e01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x1e02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x1e03, KEY_NUMERIC_3 पूर्ण,

	अणु 0x1e04, KEY_NUMERIC_4 पूर्ण,
	अणु 0x1e05, KEY_NUMERIC_5 पूर्ण,
	अणु 0x1e06, KEY_NUMERIC_6 पूर्ण,

	अणु 0x1e07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x1e08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x1e09, KEY_NUMERIC_9 पूर्ण,

	अणु 0x1e0a, KEY_TEXT पूर्ण,		/* keypad asterisk as well */
	अणु 0x1e00, KEY_NUMERIC_0 पूर्ण,
	अणु 0x1e0e, KEY_SUBTITLE पूर्ण,	/* also the Pound key (#) */

	अणु 0x1e0b, KEY_RED पूर्ण,		/* red button */
	अणु 0x1e2e, KEY_GREEN पूर्ण,		/* green button */
	अणु 0x1e38, KEY_YELLOW पूर्ण,		/* yellow key */
	अणु 0x1e29, KEY_BLUE पूर्ण,		/* blue key */

	/*
	 * Old Remote Controller Hauppauge Gray with a golden screen
	 * Keycodes start with address = 0x1f
	 */
	अणु 0x1f3d, KEY_POWER2 पूर्ण,		/* प्रणाली घातer (green button) */
	अणु 0x1f3b, KEY_SELECT पूर्ण,		/* GO */

	/* Keys 0 to 9 */
	अणु 0x1f00, KEY_NUMERIC_0 पूर्ण,
	अणु 0x1f01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x1f02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x1f03, KEY_NUMERIC_3 पूर्ण,
	अणु 0x1f04, KEY_NUMERIC_4 पूर्ण,
	अणु 0x1f05, KEY_NUMERIC_5 पूर्ण,
	अणु 0x1f06, KEY_NUMERIC_6 पूर्ण,
	अणु 0x1f07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x1f08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x1f09, KEY_NUMERIC_9 पूर्ण,

	अणु 0x1f1f, KEY_EXIT पूर्ण,		/* back/निकास */
	अणु 0x1f0d, KEY_MENU पूर्ण,

	अणु 0x1f10, KEY_VOLUMEUP पूर्ण,
	अणु 0x1f11, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x1f20, KEY_CHANNELUP पूर्ण,	/* channel / program + */
	अणु 0x1f21, KEY_CHANNELDOWN पूर्ण,	/* channel / program - */
	अणु 0x1f25, KEY_ENTER पूर्ण,		/* OK */

	अणु 0x1f0b, KEY_RED पूर्ण,		/* red button */
	अणु 0x1f2e, KEY_GREEN पूर्ण,		/* green button */
	अणु 0x1f38, KEY_YELLOW पूर्ण,		/* yellow key */
	अणु 0x1f29, KEY_BLUE पूर्ण,		/* blue key */

	अणु 0x1f0f, KEY_MUTE पूर्ण,
	अणु 0x1f0c, KEY_RADIO पूर्ण,		/* There's no indicator on this key */
	अणु 0x1f3c, KEY_ZOOM पूर्ण,		/* full */

	अणु 0x1f32, KEY_REWIND पूर्ण,		/* backward << */
	अणु 0x1f35, KEY_PLAY पूर्ण,
	अणु 0x1f34, KEY_FASTFORWARD पूर्ण,	/* क्रमward >> */

	अणु 0x1f37, KEY_RECORD पूर्ण,		/* recording */
	अणु 0x1f36, KEY_STOP पूर्ण,
	अणु 0x1f30, KEY_PAUSE पूर्ण,		/* छोड़ो */

	अणु 0x1f24, KEY_PREVIOUSSONG पूर्ण,	/* replay |< */
	अणु 0x1f1e, KEY_NEXTSONG पूर्ण,	/* skip >| */

	/*
	 * Keycodes क्रम DSR-0112 remote bundled with Haupauge MiniStick
	 * Keycodes start with address = 0x1d
	 */
	अणु 0x1d00, KEY_NUMERIC_0 पूर्ण,
	अणु 0x1d01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x1d02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x1d03, KEY_NUMERIC_3 पूर्ण,
	अणु 0x1d04, KEY_NUMERIC_4 पूर्ण,
	अणु 0x1d05, KEY_NUMERIC_5 पूर्ण,
	अणु 0x1d06, KEY_NUMERIC_6 पूर्ण,
	अणु 0x1d07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x1d08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x1d09, KEY_NUMERIC_9 पूर्ण,
	अणु 0x1d0a, KEY_TEXT पूर्ण,
	अणु 0x1d0d, KEY_MENU पूर्ण,
	अणु 0x1d0f, KEY_MUTE पूर्ण,
	अणु 0x1d10, KEY_VOLUMEUP पूर्ण,
	अणु 0x1d11, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x1d12, KEY_PREVIOUS पूर्ण,        /* Prev.Ch .. ??? */
	अणु 0x1d14, KEY_UP पूर्ण,
	अणु 0x1d15, KEY_DOWN पूर्ण,
	अणु 0x1d16, KEY_LEFT पूर्ण,
	अणु 0x1d17, KEY_RIGHT पूर्ण,
	अणु 0x1d1c, KEY_TV पूर्ण,
	अणु 0x1d1e, KEY_NEXT पूर्ण,           /* >|             */
	अणु 0x1d1f, KEY_EXIT पूर्ण,
	अणु 0x1d20, KEY_CHANNELUP पूर्ण,
	अणु 0x1d21, KEY_CHANNELDOWN पूर्ण,
	अणु 0x1d24, KEY_LAST पूर्ण,           /* <|             */
	अणु 0x1d25, KEY_OK पूर्ण,
	अणु 0x1d30, KEY_PAUSE पूर्ण,
	अणु 0x1d32, KEY_REWIND पूर्ण,
	अणु 0x1d34, KEY_FASTFORWARD पूर्ण,
	अणु 0x1d35, KEY_PLAY पूर्ण,
	अणु 0x1d36, KEY_STOP पूर्ण,
	अणु 0x1d37, KEY_RECORD पूर्ण,
	अणु 0x1d3b, KEY_GOTO पूर्ण,
	अणु 0x1d3d, KEY_POWER पूर्ण,
	अणु 0x1d3f, KEY_HOME पूर्ण,

	/*
	 * Keycodes क्रम PT# R-005 remote bundled with Haupauge HVR-930C
	 * Keycodes start with address = 0x1c
	 */
	अणु 0x1c3b, KEY_GOTO पूर्ण,
	अणु 0x1c3d, KEY_POWER पूर्ण,

	अणु 0x1c14, KEY_UP पूर्ण,
	अणु 0x1c15, KEY_DOWN पूर्ण,
	अणु 0x1c16, KEY_LEFT पूर्ण,
	अणु 0x1c17, KEY_RIGHT पूर्ण,
	अणु 0x1c25, KEY_OK पूर्ण,

	अणु 0x1c00, KEY_NUMERIC_0 पूर्ण,
	अणु 0x1c01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x1c02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x1c03, KEY_NUMERIC_3 पूर्ण,
	अणु 0x1c04, KEY_NUMERIC_4 पूर्ण,
	अणु 0x1c05, KEY_NUMERIC_5 पूर्ण,
	अणु 0x1c06, KEY_NUMERIC_6 पूर्ण,
	अणु 0x1c07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x1c08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x1c09, KEY_NUMERIC_9 पूर्ण,

	अणु 0x1c1f, KEY_EXIT पूर्ण,	/* BACK */
	अणु 0x1c0d, KEY_MENU पूर्ण,
	अणु 0x1c1c, KEY_TV पूर्ण,

	अणु 0x1c10, KEY_VOLUMEUP पूर्ण,
	अणु 0x1c11, KEY_VOLUMEDOWN पूर्ण,

	अणु 0x1c20, KEY_CHANNELUP पूर्ण,
	अणु 0x1c21, KEY_CHANNELDOWN पूर्ण,

	अणु 0x1c0f, KEY_MUTE पूर्ण,
	अणु 0x1c12, KEY_PREVIOUS पूर्ण, /* Prev */

	अणु 0x1c36, KEY_STOP पूर्ण,
	अणु 0x1c37, KEY_RECORD पूर्ण,

	अणु 0x1c24, KEY_LAST पूर्ण,           /* <|             */
	अणु 0x1c1e, KEY_NEXT पूर्ण,           /* >|             */

	अणु 0x1c0a, KEY_TEXT पूर्ण,
	अणु 0x1c0e, KEY_SUBTITLE पूर्ण,	/* CC */

	अणु 0x1c32, KEY_REWIND पूर्ण,
	अणु 0x1c30, KEY_PAUSE पूर्ण,
	अणु 0x1c35, KEY_PLAY पूर्ण,
	अणु 0x1c34, KEY_FASTFORWARD पूर्ण,

	/*
	 * Keycodes क्रम the old Black Remote Controller
	 * This one also uses RC-5 protocol
	 * Keycodes start with address = 0x00
	 */
	अणु 0x000f, KEY_TV पूर्ण,
	अणु 0x001f, KEY_TV पूर्ण,
	अणु 0x0020, KEY_CHANNELUP पूर्ण,
	अणु 0x000c, KEY_RADIO पूर्ण,

	अणु 0x0011, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x002e, KEY_ZOOM पूर्ण,		/* full screen */
	अणु 0x0010, KEY_VOLUMEUP पूर्ण,

	अणु 0x000d, KEY_MUTE पूर्ण,
	अणु 0x0021, KEY_CHANNELDOWN पूर्ण,
	अणु 0x0022, KEY_VIDEO पूर्ण,		/* source */

	अणु 0x0001, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0002, KEY_NUMERIC_2 पूर्ण,
	अणु 0x0003, KEY_NUMERIC_3 पूर्ण,

	अणु 0x0004, KEY_NUMERIC_4 पूर्ण,
	अणु 0x0005, KEY_NUMERIC_5 पूर्ण,
	अणु 0x0006, KEY_NUMERIC_6 पूर्ण,

	अणु 0x0007, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0008, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0009, KEY_NUMERIC_9 पूर्ण,

	अणु 0x001e, KEY_RED पूर्ण,	/* Reserved */
	अणु 0x0000, KEY_NUMERIC_0 पूर्ण,
	अणु 0x0026, KEY_SLEEP पूर्ण,	/* Minimize */
पूर्ण;

अटल काष्ठा rc_map_list rc5_hauppauge_new_map = अणु
	.map = अणु
		.scan     = rc5_hauppauge_new,
		.size     = ARRAY_SIZE(rc5_hauppauge_new),
		.rc_proto = RC_PROTO_RC5,
		.name     = RC_MAP_HAUPPAUGE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_rc5_hauppauge_new(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&rc5_hauppauge_new_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_rc5_hauppauge_new(व्योम)
अणु
	rc_map_unरेजिस्टर(&rc5_hauppauge_new_map);
पूर्ण

module_init(init_rc_map_rc5_hauppauge_new)
module_निकास(निकास_rc_map_rc5_hauppauge_new)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
