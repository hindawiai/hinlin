<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// asus-ps3-100.h - Keytable क्रम asus_ps3_100 Remote Controller
//
// Copyright (c) 2012 by Mauro Carvalho Chehab
//
// Based on a previous patch from Remi Schwartz <remi.schwartz@gmail.com>

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table asus_ps3_100[] = अणु
	अणु 0x081c, KEY_HOME पूर्ण,             /* home */
	अणु 0x081e, KEY_TV पूर्ण,               /* tv */
	अणु 0x0803, KEY_TEXT पूर्ण,             /* teletext */
	अणु 0x0829, KEY_POWER पूर्ण,            /* बंद */

	अणु 0x080b, KEY_RED पूर्ण,              /* red */
	अणु 0x080d, KEY_YELLOW पूर्ण,           /* yellow */
	अणु 0x0806, KEY_BLUE पूर्ण,             /* blue */
	अणु 0x0807, KEY_GREEN पूर्ण,            /* green */

	/* Keys 0 to 9 */
	अणु 0x082a, KEY_NUMERIC_0 पूर्ण,
	अणु 0x0816, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0812, KEY_NUMERIC_2 पूर्ण,
	अणु 0x0814, KEY_NUMERIC_3 पूर्ण,
	अणु 0x0836, KEY_NUMERIC_4 पूर्ण,
	अणु 0x0832, KEY_NUMERIC_5 पूर्ण,
	अणु 0x0834, KEY_NUMERIC_6 पूर्ण,
	अणु 0x080e, KEY_NUMERIC_7 पूर्ण,
	अणु 0x080a, KEY_NUMERIC_8 पूर्ण,
	अणु 0x080c, KEY_NUMERIC_9 पूर्ण,

	अणु 0x0815, KEY_VOLUMEUP पूर्ण,
	अणु 0x0826, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x0835, KEY_CHANNELUP पूर्ण,        /* channel / program + */
	अणु 0x0824, KEY_CHANNELDOWN पूर्ण,      /* channel / program - */

	अणु 0x0808, KEY_UP पूर्ण,
	अणु 0x0804, KEY_DOWN पूर्ण,
	अणु 0x0818, KEY_LEFT पूर्ण,
	अणु 0x0810, KEY_RIGHT पूर्ण,
	अणु 0x0825, KEY_ENTER पूर्ण,            /* enter */

	अणु 0x0822, KEY_EXIT पूर्ण,             /* back */
	अणु 0x082c, KEY_AB पूर्ण,               /* recall */

	अणु 0x0820, KEY_AUDIO पूर्ण,            /* TV audio */
	अणु 0x0837, KEY_SCREEN पूर्ण,           /* snapshot */
	अणु 0x082e, KEY_ZOOM पूर्ण,             /* full screen */
	अणु 0x0802, KEY_MUTE पूर्ण,             /* mute */

	अणु 0x0831, KEY_REWIND पूर्ण,           /* backward << */
	अणु 0x0811, KEY_RECORD पूर्ण,           /* recording */
	अणु 0x0809, KEY_STOP पूर्ण,
	अणु 0x0805, KEY_FASTFORWARD पूर्ण,      /* क्रमward >> */
	अणु 0x0821, KEY_PREVIOUS पूर्ण,         /* rew */
	अणु 0x081a, KEY_PAUSE पूर्ण,            /* छोड़ो */
	अणु 0x0839, KEY_PLAY पूर्ण,             /* play */
	अणु 0x0819, KEY_NEXT पूर्ण,             /* क्रमward */
पूर्ण;

अटल काष्ठा rc_map_list asus_ps3_100_map = अणु
.map = अणु
	.scan     = asus_ps3_100,
	.size     = ARRAY_SIZE(asus_ps3_100),
	.rc_proto = RC_PROTO_RC5,
	.name     = RC_MAP_ASUS_PS3_100,
पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_asus_ps3_100(व्योम)
अणु
वापस rc_map_रेजिस्टर(&asus_ps3_100_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_asus_ps3_100(व्योम)
अणु
rc_map_unरेजिस्टर(&asus_ps3_100_map);
पूर्ण

module_init(init_rc_map_asus_ps3_100)
module_निकास(निकास_rc_map_asus_ps3_100)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
