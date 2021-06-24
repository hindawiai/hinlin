<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AverMedia RM-KS remote controller keytable
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Initial keytable is from Jose Alberto Reguero <jareguero@telefonica.net>
   and Felipe Morales Moreno <felipe.morales.moreno@gmail.com> */
/* Keytable fixed by Philippe Valembois <lephilousophe@users.sourceक्रमge.net> */
अटल काष्ठा rc_map_table avermedia_rm_ks[] = अणु
	अणु 0x0501, KEY_POWER2 पूर्ण, /* Power (RED POWER BUTTON) */
	अणु 0x0502, KEY_CHANNELUP पूर्ण, /* Channel+ */
	अणु 0x0503, KEY_CHANNELDOWN पूर्ण, /* Channel- */
	अणु 0x0504, KEY_VOLUMEUP पूर्ण, /* Volume+ */
	अणु 0x0505, KEY_VOLUMEDOWN पूर्ण, /* Volume- */
	अणु 0x0506, KEY_MUTE पूर्ण, /* Mute */
	अणु 0x0507, KEY_AGAIN पूर्ण, /* Recall */
	अणु 0x0508, KEY_VIDEO पूर्ण, /* Source */
	अणु 0x0509, KEY_NUMERIC_1 पूर्ण, /* 1 */
	अणु 0x050a, KEY_NUMERIC_2 पूर्ण, /* 2 */
	अणु 0x050b, KEY_NUMERIC_3 पूर्ण, /* 3 */
	अणु 0x050c, KEY_NUMERIC_4 पूर्ण, /* 4 */
	अणु 0x050d, KEY_NUMERIC_5 पूर्ण, /* 5 */
	अणु 0x050e, KEY_NUMERIC_6 पूर्ण, /* 6 */
	अणु 0x050f, KEY_NUMERIC_7 पूर्ण, /* 7 */
	अणु 0x0510, KEY_NUMERIC_8 पूर्ण, /* 8 */
	अणु 0x0511, KEY_NUMERIC_9 पूर्ण, /* 9 */
	अणु 0x0512, KEY_NUMERIC_0 पूर्ण, /* 0 */
	अणु 0x0513, KEY_AUDIO पूर्ण, /* Audio */
	अणु 0x0515, KEY_EPG पूर्ण, /* EPG */
	अणु 0x0516, KEY_PLAYPAUSE पूर्ण, /* Play/Pause */
	अणु 0x0517, KEY_RECORD पूर्ण, /* Record */
	अणु 0x0518, KEY_STOP पूर्ण, /* Stop */
	अणु 0x051c, KEY_BACK पूर्ण, /* << */
	अणु 0x051d, KEY_FORWARD पूर्ण, /* >> */
	अणु 0x054d, KEY_INFO पूर्ण, /* Display inक्रमmation */
	अणु 0x0556, KEY_ZOOM पूर्ण, /* Fullscreen */
पूर्ण;

अटल काष्ठा rc_map_list avermedia_rm_ks_map = अणु
	.map = अणु
		.scan     = avermedia_rm_ks,
		.size     = ARRAY_SIZE(avermedia_rm_ks),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_AVERMEDIA_RM_KS,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_avermedia_rm_ks(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&avermedia_rm_ks_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_avermedia_rm_ks(व्योम)
अणु
	rc_map_unरेजिस्टर(&avermedia_rm_ks_map);
पूर्ण

module_init(init_rc_map_avermedia_rm_ks)
module_निकास(निकास_rc_map_avermedia_rm_ks)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
