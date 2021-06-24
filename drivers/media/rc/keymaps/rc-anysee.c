<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Anysee remote controller keytable
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table anysee[] = अणु
	अणु 0x0800, KEY_NUMERIC_0 पूर्ण,
	अणु 0x0801, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0802, KEY_NUMERIC_2 पूर्ण,
	अणु 0x0803, KEY_NUMERIC_3 पूर्ण,
	अणु 0x0804, KEY_NUMERIC_4 पूर्ण,
	अणु 0x0805, KEY_NUMERIC_5 पूर्ण,
	अणु 0x0806, KEY_NUMERIC_6 पूर्ण,
	अणु 0x0807, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0808, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0809, KEY_NUMERIC_9 पूर्ण,
	अणु 0x080a, KEY_POWER2 पूर्ण,          /* [red घातer button] */
	अणु 0x080b, KEY_VIDEO पूर्ण,           /* [*] MODE */
	अणु 0x080c, KEY_CHANNEL पूर्ण,         /* [symbol counterघड़ीwise arrow] */
	अणु 0x080d, KEY_NEXT पूर्ण,            /* [>>|] */
	अणु 0x080e, KEY_MENU पूर्ण,            /* MENU */
	अणु 0x080f, KEY_EPG पूर्ण,             /* [EPG] */
	अणु 0x0810, KEY_CLEAR पूर्ण,           /* EXIT */
	अणु 0x0811, KEY_CHANNELUP पूर्ण,
	अणु 0x0812, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x0813, KEY_VOLUMEUP पूर्ण,
	अणु 0x0814, KEY_CHANNELDOWN पूर्ण,
	अणु 0x0815, KEY_OK पूर्ण,
	अणु 0x0816, KEY_RADIO पूर्ण,           /* [symbol TV/radio] */
	अणु 0x0817, KEY_INFO पूर्ण,            /* [i] */
	अणु 0x0818, KEY_PREVIOUS पूर्ण,        /* [|<<] */
	अणु 0x0819, KEY_FAVORITES पूर्ण,       /* FAV. */
	अणु 0x081a, KEY_SUBTITLE पूर्ण,        /* Subtitle */
	अणु 0x081b, KEY_CAMERA पूर्ण,          /* [symbol camera] */
	अणु 0x081c, KEY_YELLOW पूर्ण,
	अणु 0x081d, KEY_RED पूर्ण,
	अणु 0x081e, KEY_LANGUAGE पूर्ण,        /* [symbol Second Audio Program] */
	अणु 0x081f, KEY_GREEN पूर्ण,
	अणु 0x0820, KEY_SLEEP पूर्ण,           /* Sleep */
	अणु 0x0821, KEY_SCREEN पूर्ण,          /* 16:9 / 4:3 */
	अणु 0x0822, KEY_ZOOM पूर्ण,            /* SIZE */
	अणु 0x0824, KEY_FN पूर्ण,              /* [F1] */
	अणु 0x0825, KEY_FN पूर्ण,              /* [F2] */
	अणु 0x0842, KEY_MUTE पूर्ण,            /* symbol mute */
	अणु 0x0844, KEY_BLUE पूर्ण,
	अणु 0x0847, KEY_TEXT पूर्ण,            /* TEXT */
	अणु 0x0848, KEY_STOP पूर्ण,
	अणु 0x0849, KEY_RECORD पूर्ण,
	अणु 0x0850, KEY_PLAY पूर्ण,
	अणु 0x0851, KEY_PAUSE पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list anysee_map = अणु
	.map = अणु
		.scan     = anysee,
		.size     = ARRAY_SIZE(anysee),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_ANYSEE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_anysee(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&anysee_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_anysee(व्योम)
अणु
	rc_map_unरेजिस्टर(&anysee_map);
पूर्ण

module_init(init_rc_map_anysee)
module_निकास(निकास_rc_map_anysee)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
