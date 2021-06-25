<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* avermedia-m733a-rm-k6.h - Keytable क्रम avermedia_m733a_rm_k6 Remote Controller
 *
 * Copyright (c) 2010 by Herton Ronalकरो Krzesinski <herton@mandriva.com.br>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/*
 * Avermedia M733A with IR model RM-K6
 * This is the stock remote controller used with Positivo machines with M733A
 * Herton Ronalकरो Krzesinski <herton@mandriva.com.br>
 */

अटल काष्ठा rc_map_table avermedia_m733a_rm_k6[] = अणु
	अणु 0x0401, KEY_POWER2 पूर्ण,
	अणु 0x0406, KEY_MUTE पूर्ण,
	अणु 0x0408, KEY_MODE पूर्ण,     /* TV/FM */

	अणु 0x0409, KEY_NUMERIC_1 पूर्ण,
	अणु 0x040a, KEY_NUMERIC_2 पूर्ण,
	अणु 0x040b, KEY_NUMERIC_3 पूर्ण,
	अणु 0x040c, KEY_NUMERIC_4 पूर्ण,
	अणु 0x040d, KEY_NUMERIC_5 पूर्ण,
	अणु 0x040e, KEY_NUMERIC_6 पूर्ण,
	अणु 0x040f, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0410, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0411, KEY_NUMERIC_9 पूर्ण,
	अणु 0x044c, KEY_DOT पूर्ण,      /* '.' */
	अणु 0x0412, KEY_NUMERIC_0 पूर्ण,
	अणु 0x0407, KEY_REFRESH पूर्ण,  /* Refresh/Reload */

	अणु 0x0413, KEY_AUDIO पूर्ण,
	अणु 0x0440, KEY_SCREEN पूर्ण,   /* Full Screen toggle */
	अणु 0x0441, KEY_HOME पूर्ण,
	अणु 0x0442, KEY_BACK पूर्ण,
	अणु 0x0447, KEY_UP पूर्ण,
	अणु 0x0448, KEY_DOWN पूर्ण,
	अणु 0x0449, KEY_LEFT पूर्ण,
	अणु 0x044a, KEY_RIGHT पूर्ण,
	अणु 0x044b, KEY_OK पूर्ण,
	अणु 0x0404, KEY_VOLUMEUP पूर्ण,
	अणु 0x0405, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x0402, KEY_CHANNELUP पूर्ण,
	अणु 0x0403, KEY_CHANNELDOWN पूर्ण,

	अणु 0x0443, KEY_RED पूर्ण,
	अणु 0x0444, KEY_GREEN पूर्ण,
	अणु 0x0445, KEY_YELLOW पूर्ण,
	अणु 0x0446, KEY_BLUE पूर्ण,

	अणु 0x0414, KEY_TEXT पूर्ण,
	अणु 0x0415, KEY_EPG पूर्ण,
	अणु 0x041a, KEY_TV2 पूर्ण,      /* PIP */
	अणु 0x041b, KEY_CAMERA पूर्ण,      /* Snapshot */

	अणु 0x0417, KEY_RECORD पूर्ण,
	अणु 0x0416, KEY_PLAYPAUSE पूर्ण,
	अणु 0x0418, KEY_STOP पूर्ण,
	अणु 0x0419, KEY_PAUSE पूर्ण,

	अणु 0x041f, KEY_PREVIOUS पूर्ण,
	अणु 0x041c, KEY_REWIND पूर्ण,
	अणु 0x041d, KEY_FORWARD पूर्ण,
	अणु 0x041e, KEY_NEXT पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list avermedia_m733a_rm_k6_map = अणु
	.map = अणु
		.scan     = avermedia_m733a_rm_k6,
		.size     = ARRAY_SIZE(avermedia_m733a_rm_k6),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_AVERMEDIA_M733A_RM_K6,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_avermedia_m733a_rm_k6(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&avermedia_m733a_rm_k6_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_avermedia_m733a_rm_k6(व्योम)
अणु
	rc_map_unरेजिस्टर(&avermedia_m733a_rm_k6_map);
पूर्ण

module_init(init_rc_map_avermedia_m733a_rm_k6)
module_निकास(निकास_rc_map_avermedia_m733a_rm_k6)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
