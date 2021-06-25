<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// kworld-plus-tv-analog.h - Keytable क्रम kworld_plus_tv_analog Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Kworld Plus TV Analog Lite PCI IR
   Mauro Carvalho Chehab <mchehab@kernel.org>
 */

अटल काष्ठा rc_map_table kworld_plus_tv_analog[] = अणु
	अणु 0x0c, KEY_MEDIA पूर्ण,		/* Kworld key */
	अणु 0x16, KEY_CLOSECD पूर्ण,		/* -> ) */
	अणु 0x1d, KEY_POWER2 पूर्ण,

	अणु 0x00, KEY_NUMERIC_1 पूर्ण,
	अणु 0x01, KEY_NUMERIC_2 पूर्ण,

	/* Two keys have the same code: 3 and left */
	अणु 0x02, KEY_NUMERIC_3 पूर्ण,

	/* Two keys have the same code: 4 and right */
	अणु 0x03, KEY_NUMERIC_4 पूर्ण,
	अणु 0x04, KEY_NUMERIC_5 पूर्ण,
	अणु 0x05, KEY_NUMERIC_6 पूर्ण,
	अणु 0x06, KEY_NUMERIC_7 पूर्ण,
	अणु 0x07, KEY_NUMERIC_8 पूर्ण,
	अणु 0x08, KEY_NUMERIC_9 पूर्ण,
	अणु 0x0a, KEY_NUMERIC_0 पूर्ण,

	अणु 0x09, KEY_AGAIN पूर्ण,
	अणु 0x14, KEY_MUTE पूर्ण,

	अणु 0x20, KEY_UP पूर्ण,
	अणु 0x21, KEY_DOWN पूर्ण,
	अणु 0x0b, KEY_ENTER पूर्ण,

	अणु 0x10, KEY_CHANNELUP पूर्ण,
	अणु 0x11, KEY_CHANNELDOWN पूर्ण,

	/* Couldn't map key left/key right since those
	   conflict with '3' and '4' scancodes
	   I dunno what the original driver करोes
	 */

	अणु 0x13, KEY_VOLUMEUP पूर्ण,
	अणु 0x12, KEY_VOLUMEDOWN पूर्ण,

	/* The lower part of the IR
	   There are several duplicated keycodes there.
	   Most of them conflict with digits.
	   Add mappings just to the unused scancodes.
	   Somehow, the original driver has a way to know,
	   but this करोesn't seem to be on some GPIO.
	   Also, it is not related to the समय between keyup
	   and keyकरोwn.
	 */
	अणु 0x19, KEY_TIMEपूर्ण,		/* Timeshअगरt */
	अणु 0x1a, KEY_STOPपूर्ण,
	अणु 0x1b, KEY_RECORDपूर्ण,

	अणु 0x22, KEY_TEXTपूर्ण,

	अणु 0x15, KEY_AUDIOपूर्ण,		/* ((*)) */
	अणु 0x0f, KEY_ZOOMपूर्ण,
	अणु 0x1c, KEY_CAMERAपूर्ण,		/* snapshot */

	अणु 0x18, KEY_REDपूर्ण,		/* B */
	अणु 0x23, KEY_GREENपूर्ण,		/* C */
पूर्ण;

अटल काष्ठा rc_map_list kworld_plus_tv_analog_map = अणु
	.map = अणु
		.scan     = kworld_plus_tv_analog,
		.size     = ARRAY_SIZE(kworld_plus_tv_analog),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_KWORLD_PLUS_TV_ANALOG,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_kworld_plus_tv_analog(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&kworld_plus_tv_analog_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_kworld_plus_tv_analog(व्योम)
अणु
	rc_map_unरेजिस्टर(&kworld_plus_tv_analog_map);
पूर्ण

module_init(init_rc_map_kworld_plus_tv_analog)
module_निकास(निकास_rc_map_kworld_plus_tv_analog)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
