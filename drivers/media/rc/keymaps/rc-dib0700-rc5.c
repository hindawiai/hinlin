<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// rc-dvb0700-big.c - Keytable क्रम devices in dvb0700
//
// Copyright (c) 2010 by Mauro Carvalho Chehab
//
// TODO: This table is a real mess, as it merges RC codes from several
// devices पूर्णांकo a big table. It also has both RC-5 and NEC codes inside.
// It should be broken पूर्णांकo small tables, and the protocols should properly
// be identअगरicated.
//
// The table were imported from dib0700_devices.c.

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table dib0700_rc5_table[] = अणु
	/* Key codes क्रम the tiny Pinnacle remote*/
	अणु 0x0700, KEY_MUTE पूर्ण,
	अणु 0x0701, KEY_MENU पूर्ण, /* Pinnacle logo */
	अणु 0x0739, KEY_POWER पूर्ण,
	अणु 0x0703, KEY_VOLUMEUP पूर्ण,
	अणु 0x0709, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x0706, KEY_CHANNELUP पूर्ण,
	अणु 0x070c, KEY_CHANNELDOWN पूर्ण,
	अणु 0x070f, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0715, KEY_NUMERIC_2 पूर्ण,
	अणु 0x0710, KEY_NUMERIC_3 पूर्ण,
	अणु 0x0718, KEY_NUMERIC_4 पूर्ण,
	अणु 0x071b, KEY_NUMERIC_5 पूर्ण,
	अणु 0x071e, KEY_NUMERIC_6 पूर्ण,
	अणु 0x0711, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0721, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0712, KEY_NUMERIC_9 पूर्ण,
	अणु 0x0727, KEY_NUMERIC_0 पूर्ण,
	अणु 0x0724, KEY_SCREEN पूर्ण, /* 'Square' key */
	अणु 0x072a, KEY_TEXT पूर्ण,   /* 'T' key */
	अणु 0x072d, KEY_REWIND पूर्ण,
	अणु 0x0730, KEY_PLAY पूर्ण,
	अणु 0x0733, KEY_FASTFORWARD पूर्ण,
	अणु 0x0736, KEY_RECORD पूर्ण,
	अणु 0x073c, KEY_STOP पूर्ण,
	अणु 0x073f, KEY_CANCEL पूर्ण, /* '?' key */

	/* Key codes क्रम the Terratec Cinergy DT XS Diversity, similar to cinergyT2.c */
	अणु 0xeb01, KEY_POWER पूर्ण,
	अणु 0xeb02, KEY_NUMERIC_1 पूर्ण,
	अणु 0xeb03, KEY_NUMERIC_2 पूर्ण,
	अणु 0xeb04, KEY_NUMERIC_3 पूर्ण,
	अणु 0xeb05, KEY_NUMERIC_4 पूर्ण,
	अणु 0xeb06, KEY_NUMERIC_5 पूर्ण,
	अणु 0xeb07, KEY_NUMERIC_6 पूर्ण,
	अणु 0xeb08, KEY_NUMERIC_7 पूर्ण,
	अणु 0xeb09, KEY_NUMERIC_8 पूर्ण,
	अणु 0xeb0a, KEY_NUMERIC_9 पूर्ण,
	अणु 0xeb0b, KEY_VIDEO पूर्ण,
	अणु 0xeb0c, KEY_NUMERIC_0 पूर्ण,
	अणु 0xeb0d, KEY_REFRESH पूर्ण,
	अणु 0xeb0f, KEY_EPG पूर्ण,
	अणु 0xeb10, KEY_UP पूर्ण,
	अणु 0xeb11, KEY_LEFT पूर्ण,
	अणु 0xeb12, KEY_OK पूर्ण,
	अणु 0xeb13, KEY_RIGHT पूर्ण,
	अणु 0xeb14, KEY_DOWN पूर्ण,
	अणु 0xeb16, KEY_INFO पूर्ण,
	अणु 0xeb17, KEY_RED पूर्ण,
	अणु 0xeb18, KEY_GREEN पूर्ण,
	अणु 0xeb19, KEY_YELLOW पूर्ण,
	अणु 0xeb1a, KEY_BLUE पूर्ण,
	अणु 0xeb1b, KEY_CHANNELUP पूर्ण,
	अणु 0xeb1c, KEY_VOLUMEUP पूर्ण,
	अणु 0xeb1d, KEY_MUTE पूर्ण,
	अणु 0xeb1e, KEY_VOLUMEDOWN पूर्ण,
	अणु 0xeb1f, KEY_CHANNELDOWN पूर्ण,
	अणु 0xeb40, KEY_PAUSE पूर्ण,
	अणु 0xeb41, KEY_HOME पूर्ण,
	अणु 0xeb42, KEY_MENU पूर्ण, /* DVD Menu */
	अणु 0xeb43, KEY_SUBTITLE पूर्ण,
	अणु 0xeb44, KEY_TEXT पूर्ण, /* Teletext */
	अणु 0xeb45, KEY_DELETE पूर्ण,
	अणु 0xeb46, KEY_TV पूर्ण,
	अणु 0xeb47, KEY_DVD पूर्ण,
	अणु 0xeb48, KEY_STOP पूर्ण,
	अणु 0xeb49, KEY_VIDEO पूर्ण,
	अणु 0xeb4a, KEY_AUDIO पूर्ण, /* Music */
	अणु 0xeb4b, KEY_SCREEN पूर्ण, /* Pic */
	अणु 0xeb4c, KEY_PLAY पूर्ण,
	अणु 0xeb4d, KEY_BACK पूर्ण,
	अणु 0xeb4e, KEY_REWIND पूर्ण,
	अणु 0xeb4f, KEY_FASTFORWARD पूर्ण,
	अणु 0xeb54, KEY_PREVIOUS पूर्ण,
	अणु 0xeb58, KEY_RECORD पूर्ण,
	अणु 0xeb5c, KEY_NEXT पूर्ण,

	/* Key codes क्रम the Haupauge WinTV Nova-TD, copied from nova-t-usb2.c (Nova-T USB2) */
	अणु 0x1e00, KEY_NUMERIC_0 पूर्ण,
	अणु 0x1e01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x1e02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x1e03, KEY_NUMERIC_3 पूर्ण,
	अणु 0x1e04, KEY_NUMERIC_4 पूर्ण,
	अणु 0x1e05, KEY_NUMERIC_5 पूर्ण,
	अणु 0x1e06, KEY_NUMERIC_6 पूर्ण,
	अणु 0x1e07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x1e08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x1e09, KEY_NUMERIC_9 पूर्ण,
	अणु 0x1e0a, KEY_KPASTERISK पूर्ण,
	अणु 0x1e0b, KEY_RED पूर्ण,
	अणु 0x1e0c, KEY_RADIO पूर्ण,
	अणु 0x1e0d, KEY_MENU पूर्ण,
	अणु 0x1e0e, KEY_GRAVE पूर्ण, /* # */
	अणु 0x1e0f, KEY_MUTE पूर्ण,
	अणु 0x1e10, KEY_VOLUMEUP पूर्ण,
	अणु 0x1e11, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x1e12, KEY_CHANNEL पूर्ण,
	अणु 0x1e14, KEY_UP पूर्ण,
	अणु 0x1e15, KEY_DOWN पूर्ण,
	अणु 0x1e16, KEY_LEFT पूर्ण,
	अणु 0x1e17, KEY_RIGHT पूर्ण,
	अणु 0x1e18, KEY_VIDEO पूर्ण,
	अणु 0x1e19, KEY_AUDIO पूर्ण,
	अणु 0x1e1a, KEY_MEDIA पूर्ण,
	अणु 0x1e1b, KEY_EPG पूर्ण,
	अणु 0x1e1c, KEY_TV पूर्ण,
	अणु 0x1e1e, KEY_NEXT पूर्ण,
	अणु 0x1e1f, KEY_BACK पूर्ण,
	अणु 0x1e20, KEY_CHANNELUP पूर्ण,
	अणु 0x1e21, KEY_CHANNELDOWN पूर्ण,
	अणु 0x1e24, KEY_LAST पूर्ण, /* Skip backwards */
	अणु 0x1e25, KEY_OK पूर्ण,
	अणु 0x1e29, KEY_BLUEपूर्ण,
	अणु 0x1e2e, KEY_GREEN पूर्ण,
	अणु 0x1e30, KEY_PAUSE पूर्ण,
	अणु 0x1e32, KEY_REWIND पूर्ण,
	अणु 0x1e34, KEY_FASTFORWARD पूर्ण,
	अणु 0x1e35, KEY_PLAY पूर्ण,
	अणु 0x1e36, KEY_STOP पूर्ण,
	अणु 0x1e37, KEY_RECORD पूर्ण,
	अणु 0x1e38, KEY_YELLOW पूर्ण,
	अणु 0x1e3b, KEY_GOTO पूर्ण,
	अणु 0x1e3d, KEY_POWER पूर्ण,

	/* Key codes क्रम the Leadtek Winfast DTV Dongle */
	अणु 0x0042, KEY_POWER पूर्ण,
	अणु 0x077c, KEY_TUNER पूर्ण,
	अणु 0x0f4e, KEY_PRINT पूर्ण, /* PREVIEW */
	अणु 0x0840, KEY_SCREEN पूर्ण, /* full screen toggle*/
	अणु 0x0f71, KEY_DOT पूर्ण, /* frequency */
	अणु 0x0743, KEY_NUMERIC_0 पूर्ण,
	अणु 0x0c41, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0443, KEY_NUMERIC_2 पूर्ण,
	अणु 0x0b7f, KEY_NUMERIC_3 पूर्ण,
	अणु 0x0e41, KEY_NUMERIC_4 पूर्ण,
	अणु 0x0643, KEY_NUMERIC_5 पूर्ण,
	अणु 0x097f, KEY_NUMERIC_6 पूर्ण,
	अणु 0x0d7e, KEY_NUMERIC_7 पूर्ण,
	अणु 0x057c, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0a40, KEY_NUMERIC_9 पूर्ण,
	अणु 0x0e4e, KEY_CLEAR पूर्ण,
	अणु 0x047c, KEY_CHANNEL पूर्ण, /* show channel number */
	अणु 0x0f41, KEY_LAST पूर्ण, /* recall */
	अणु 0x0342, KEY_MUTE पूर्ण,
	अणु 0x064c, KEY_RESERVED पूर्ण, /* PIP button*/
	अणु 0x0172, KEY_SHUFFLE पूर्ण, /* SNAPSHOT */
	अणु 0x0c4e, KEY_PLAYPAUSE पूर्ण, /* TIMESHIFT */
	अणु 0x0b70, KEY_RECORD पूर्ण,
	अणु 0x037d, KEY_VOLUMEUP पूर्ण,
	अणु 0x017d, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x0242, KEY_CHANNELUP पूर्ण,
	अणु 0x007d, KEY_CHANNELDOWN पूर्ण,

	/* Key codes क्रम Nova-TD "credit card" remote control. */
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
	अणु 0x1d12, KEY_CHANNEL पूर्ण,
	अणु 0x1d14, KEY_UP पूर्ण,
	अणु 0x1d15, KEY_DOWN पूर्ण,
	अणु 0x1d16, KEY_LEFT पूर्ण,
	अणु 0x1d17, KEY_RIGHT पूर्ण,
	अणु 0x1d1c, KEY_TV पूर्ण,
	अणु 0x1d1e, KEY_NEXT पूर्ण,
	अणु 0x1d1f, KEY_BACK पूर्ण,
	अणु 0x1d20, KEY_CHANNELUP पूर्ण,
	अणु 0x1d21, KEY_CHANNELDOWN पूर्ण,
	अणु 0x1d24, KEY_LAST पूर्ण,
	अणु 0x1d25, KEY_OK पूर्ण,
	अणु 0x1d30, KEY_PAUSE पूर्ण,
	अणु 0x1d32, KEY_REWIND पूर्ण,
	अणु 0x1d34, KEY_FASTFORWARD पूर्ण,
	अणु 0x1d35, KEY_PLAY पूर्ण,
	अणु 0x1d36, KEY_STOP पूर्ण,
	अणु 0x1d37, KEY_RECORD पूर्ण,
	अणु 0x1d3b, KEY_GOTO पूर्ण,
	अणु 0x1d3d, KEY_POWER पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list dib0700_rc5_map = अणु
	.map = अणु
		.scan     = dib0700_rc5_table,
		.size     = ARRAY_SIZE(dib0700_rc5_table),
		.rc_proto = RC_PROTO_RC5,
		.name     = RC_MAP_DIB0700_RC5_TABLE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&dib0700_rc5_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map(व्योम)
अणु
	rc_map_unरेजिस्टर(&dib0700_rc5_map);
पूर्ण

module_init(init_rc_map)
module_निकास(निकास_rc_map)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
