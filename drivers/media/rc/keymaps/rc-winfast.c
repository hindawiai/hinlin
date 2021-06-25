<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// winfast.h - Keytable क्रम winfast Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Table क्रम Leadtek Winfast Remote Controls - used by both bttv and cx88 */

अटल काष्ठा rc_map_table winfast[] = अणु
	/* Keys 0 to 9 */
	अणु 0x12, KEY_NUMERIC_0 पूर्ण,
	अणु 0x05, KEY_NUMERIC_1 पूर्ण,
	अणु 0x06, KEY_NUMERIC_2 पूर्ण,
	अणु 0x07, KEY_NUMERIC_3 पूर्ण,
	अणु 0x09, KEY_NUMERIC_4 पूर्ण,
	अणु 0x0a, KEY_NUMERIC_5 पूर्ण,
	अणु 0x0b, KEY_NUMERIC_6 पूर्ण,
	अणु 0x0d, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0e, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0f, KEY_NUMERIC_9 पूर्ण,

	अणु 0x00, KEY_POWER2 पूर्ण,
	अणु 0x1b, KEY_AUDIO पूर्ण,		/* Audio Source */
	अणु 0x02, KEY_TUNER पूर्ण,		/* TV/FM, not on Y0400052 */
	अणु 0x1e, KEY_VIDEO पूर्ण,		/* Video Source */
	अणु 0x16, KEY_INFO पूर्ण,		/* Display inक्रमmation */
	अणु 0x04, KEY_RIGHT पूर्ण,
	अणु 0x08, KEY_LEFT पूर्ण,
	अणु 0x0c, KEY_UP पूर्ण,
	अणु 0x10, KEY_DOWN पूर्ण,
	अणु 0x03, KEY_ZOOM पूर्ण,		/* fullscreen */
	अणु 0x1f, KEY_TEXT पूर्ण,		/* बंदd caption/teletext */
	अणु 0x20, KEY_SLEEP पूर्ण,
	अणु 0x29, KEY_CLEAR पूर्ण,		/* boss key */
	अणु 0x14, KEY_MUTE पूर्ण,
	अणु 0x2b, KEY_RED पूर्ण,
	अणु 0x2c, KEY_GREEN पूर्ण,
	अणु 0x2d, KEY_YELLOW पूर्ण,
	अणु 0x2e, KEY_BLUE पूर्ण,
	अणु 0x18, KEY_KPPLUS पूर्ण,		/* fine tune + , not on Y040052 */
	अणु 0x19, KEY_KPMINUS पूर्ण,		/* fine tune - , not on Y040052 */
	अणु 0x2a, KEY_TV2 पूर्ण,		/* PIP (Picture in picture */
	अणु 0x21, KEY_DOT पूर्ण,
	अणु 0x13, KEY_ENTER पूर्ण,
	अणु 0x11, KEY_LAST पूर्ण,		/* Recall (last channel */
	अणु 0x22, KEY_PREVIOUS पूर्ण,
	अणु 0x23, KEY_PLAYPAUSE पूर्ण,
	अणु 0x24, KEY_NEXT पूर्ण,
	अणु 0x25, KEY_TIME पूर्ण,		/* Time Shअगरting */
	अणु 0x26, KEY_STOP पूर्ण,
	अणु 0x27, KEY_RECORD पूर्ण,
	अणु 0x28, KEY_CAMERA पूर्ण,		/* Screenshot */
	अणु 0x2f, KEY_MENU पूर्ण,
	अणु 0x30, KEY_CANCEL पूर्ण,
	अणु 0x31, KEY_CHANNEL पूर्ण,		/* Channel Surf */
	अणु 0x32, KEY_SUBTITLE पूर्ण,
	अणु 0x33, KEY_LANGUAGE पूर्ण,
	अणु 0x34, KEY_REWIND पूर्ण,
	अणु 0x35, KEY_FASTFORWARD पूर्ण,
	अणु 0x36, KEY_TV पूर्ण,
	अणु 0x37, KEY_RADIO पूर्ण,		/* FM */
	अणु 0x38, KEY_DVD पूर्ण,

	अणु 0x1a, KEY_MODEपूर्ण,		/* change to MCE mode on Y04G0051 */
	अणु 0x3e, KEY_VOLUMEUP पूर्ण,		/* MCE +VOL, on Y04G0033 */
	अणु 0x3a, KEY_VOLUMEDOWN पूर्ण,	/* MCE -VOL, on Y04G0033 */
	अणु 0x3b, KEY_CHANNELUP पूर्ण,	/* MCE +CH,  on Y04G0033 */
	अणु 0x3f, KEY_CHANNELDOWN पूर्ण	/* MCE -CH,  on Y04G0033 */
पूर्ण;

अटल काष्ठा rc_map_list winfast_map = अणु
	.map = अणु
		.scan     = winfast,
		.size     = ARRAY_SIZE(winfast),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_WINFAST,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_winfast(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&winfast_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_winfast(व्योम)
अणु
	rc_map_unरेजिस्टर(&winfast_map);
पूर्ण

module_init(init_rc_map_winfast)
module_निकास(निकास_rc_map_winfast)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
