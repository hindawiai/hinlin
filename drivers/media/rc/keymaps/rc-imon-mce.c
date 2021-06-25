<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* rc5-imon-mce.c - Keytable क्रम Winकरोws Media Center RC-6 remotes क्रम use
 * with the SoundGraph iMON/Antec Veris hardware IR decoder
 *
 * Copyright (c) 2010 by Jarod Wilson <jarod@redhat.com>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* mce-mode imon mce remote key table */
अटल काष्ठा rc_map_table imon_mce[] = अणु
	/* keys sorted mostly by frequency of use to optimize lookups */
	अणु 0x800ff415, KEY_REWIND पूर्ण,
	अणु 0x800ff414, KEY_FASTFORWARD पूर्ण,
	अणु 0x800ff41b, KEY_PREVIOUS पूर्ण,
	अणु 0x800ff41a, KEY_NEXT पूर्ण,

	अणु 0x800ff416, KEY_PLAY पूर्ण,
	अणु 0x800ff418, KEY_PAUSE पूर्ण,
	अणु 0x800ff419, KEY_STOP पूर्ण,
	अणु 0x800ff417, KEY_RECORD पूर्ण,

	अणु 0x02000052, KEY_UP पूर्ण,
	अणु 0x02000051, KEY_DOWN पूर्ण,
	अणु 0x02000050, KEY_LEFT पूर्ण,
	अणु 0x0200004f, KEY_RIGHT पूर्ण,

	अणु 0x800ff41e, KEY_UP पूर्ण,
	अणु 0x800ff41f, KEY_DOWN पूर्ण,
	अणु 0x800ff420, KEY_LEFT पूर्ण,
	अणु 0x800ff421, KEY_RIGHT पूर्ण,

	/* 0x800ff40b also KEY_NUMERIC_POUND on some receivers */
	अणु 0x800ff40b, KEY_ENTER पूर्ण,
	अणु 0x02000028, KEY_ENTER पूर्ण,
/* the OK and Enter buttons decode to the same value on some remotes
	अणु 0x02000028, KEY_OK पूर्ण, */
	अणु 0x800ff422, KEY_OK पूर्ण,
	अणु 0x0200002a, KEY_EXIT पूर्ण,
	अणु 0x800ff423, KEY_EXIT पूर्ण,
	अणु 0x02000029, KEY_DELETE पूर्ण,
	/* 0x800ff40a also KEY_NUMERIC_STAR on some receivers */
	अणु 0x800ff40a, KEY_DELETE पूर्ण,

	अणु 0x800ff40e, KEY_MUTE पूर्ण,
	अणु 0x800ff410, KEY_VOLUMEUP पूर्ण,
	अणु 0x800ff411, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x800ff412, KEY_CHANNELUP पूर्ण,
	अणु 0x800ff413, KEY_CHANNELDOWN पूर्ण,

	अणु 0x0200001e, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0200001f, KEY_NUMERIC_2 पूर्ण,
	अणु 0x02000020, KEY_NUMERIC_3 पूर्ण,
	अणु 0x02000021, KEY_NUMERIC_4 पूर्ण,
	अणु 0x02000022, KEY_NUMERIC_5 पूर्ण,
	अणु 0x02000023, KEY_NUMERIC_6 पूर्ण,
	अणु 0x02000024, KEY_NUMERIC_7 पूर्ण,
	अणु 0x02000025, KEY_NUMERIC_8 पूर्ण,
	अणु 0x02000026, KEY_NUMERIC_9 पूर्ण,
	अणु 0x02000027, KEY_NUMERIC_0 पूर्ण,

	अणु 0x800ff401, KEY_NUMERIC_1 पूर्ण,
	अणु 0x800ff402, KEY_NUMERIC_2 पूर्ण,
	अणु 0x800ff403, KEY_NUMERIC_3 पूर्ण,
	अणु 0x800ff404, KEY_NUMERIC_4 पूर्ण,
	अणु 0x800ff405, KEY_NUMERIC_5 पूर्ण,
	अणु 0x800ff406, KEY_NUMERIC_6 पूर्ण,
	अणु 0x800ff407, KEY_NUMERIC_7 पूर्ण,
	अणु 0x800ff408, KEY_NUMERIC_8 पूर्ण,
	अणु 0x800ff409, KEY_NUMERIC_9 पूर्ण,
	अणु 0x800ff400, KEY_NUMERIC_0 पूर्ण,

	अणु 0x02200025, KEY_NUMERIC_STAR पूर्ण,
	अणु 0x02200020, KEY_NUMERIC_POUND पूर्ण,
	/* 0x800ff41d also KEY_BLUE on some receivers */
	अणु 0x800ff41d, KEY_NUMERIC_STAR पूर्ण,
	/* 0x800ff41c also KEY_PREVIOUS on some receivers */
	अणु 0x800ff41c, KEY_NUMERIC_POUND पूर्ण,

	अणु 0x800ff446, KEY_TV पूर्ण,
	अणु 0x800ff447, KEY_AUDIO पूर्ण, /* My Music */
	अणु 0x800ff448, KEY_PVR पूर्ण, /* RecordedTV */
	अणु 0x800ff449, KEY_CAMERA पूर्ण,
	अणु 0x800ff44a, KEY_VIDEO पूर्ण,
	/* 0x800ff424 also KEY_MENU on some receivers */
	अणु 0x800ff424, KEY_DVD पूर्ण,
	/* 0x800ff425 also KEY_GREEN on some receivers */
	अणु 0x800ff425, KEY_TUNER पूर्ण, /* LiveTV */
	अणु 0x800ff450, KEY_RADIO पूर्ण,

	अणु 0x800ff44c, KEY_LANGUAGE पूर्ण,
	अणु 0x800ff427, KEY_ZOOM पूर्ण, /* Aspect */

	अणु 0x800ff45b, KEY_RED पूर्ण,
	अणु 0x800ff45c, KEY_GREEN पूर्ण,
	अणु 0x800ff45d, KEY_YELLOW पूर्ण,
	अणु 0x800ff45e, KEY_BLUE पूर्ण,

	अणु 0x800ff466, KEY_RED पूर्ण,
	/* अणु 0x800ff425, KEY_GREEN पूर्ण, */
	अणु 0x800ff468, KEY_YELLOW पूर्ण,
	/* अणु 0x800ff41d, KEY_BLUE पूर्ण, */

	अणु 0x800ff40f, KEY_INFO पूर्ण,
	अणु 0x800ff426, KEY_EPG पूर्ण, /* Guide */
	अणु 0x800ff45a, KEY_SUBTITLE पूर्ण, /* Caption/Teletext */
	अणु 0x800ff44d, KEY_TITLE पूर्ण,

	अणु 0x800ff40c, KEY_POWER पूर्ण,
	अणु 0x800ff40d, KEY_MEDIA पूर्ण, /* Winकरोws MCE button */

पूर्ण;

अटल काष्ठा rc_map_list imon_mce_map = अणु
	.map = अणु
		.scan     = imon_mce,
		.size     = ARRAY_SIZE(imon_mce),
		/* its RC6, but w/a hardware decoder */
		.rc_proto = RC_PROTO_RC6_MCE,
		.name     = RC_MAP_IMON_MCE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_imon_mce(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&imon_mce_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_imon_mce(व्योम)
अणु
	rc_map_unरेजिस्टर(&imon_mce_map);
पूर्ण

module_init(init_rc_map_imon_mce)
module_निकास(निकास_rc_map_imon_mce)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jarod Wilson <jarod@redhat.com>");
