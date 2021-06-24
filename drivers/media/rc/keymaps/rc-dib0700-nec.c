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

अटल काष्ठा rc_map_table dib0700_nec_table[] = अणु
	/* Key codes क्रम the Pixelview SBTVD remote */
	अणु 0x866b13, KEY_MUTE पूर्ण,
	अणु 0x866b12, KEY_POWER पूर्ण,
	अणु 0x866b01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x866b02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x866b03, KEY_NUMERIC_3 पूर्ण,
	अणु 0x866b04, KEY_NUMERIC_4 पूर्ण,
	अणु 0x866b05, KEY_NUMERIC_5 पूर्ण,
	अणु 0x866b06, KEY_NUMERIC_6 पूर्ण,
	अणु 0x866b07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x866b08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x866b09, KEY_NUMERIC_9 पूर्ण,
	अणु 0x866b00, KEY_NUMERIC_0 पूर्ण,
	अणु 0x866b0d, KEY_CHANNELUP पूर्ण,
	अणु 0x866b19, KEY_CHANNELDOWN पूर्ण,
	अणु 0x866b10, KEY_VOLUMEUP पूर्ण,
	अणु 0x866b0c, KEY_VOLUMEDOWN पूर्ण,

	अणु 0x866b0a, KEY_CAMERA पूर्ण,
	अणु 0x866b0b, KEY_ZOOM पूर्ण,
	अणु 0x866b1b, KEY_BACKSPACE पूर्ण,
	अणु 0x866b15, KEY_ENTER पूर्ण,

	अणु 0x866b1d, KEY_UP पूर्ण,
	अणु 0x866b1e, KEY_DOWN पूर्ण,
	अणु 0x866b0e, KEY_LEFT पूर्ण,
	अणु 0x866b0f, KEY_RIGHT पूर्ण,

	अणु 0x866b18, KEY_RECORD पूर्ण,
	अणु 0x866b1a, KEY_STOP पूर्ण,

	/* Key codes क्रम the EvolutePC TVWay+ remote */
	अणु 0x7a00, KEY_MENU पूर्ण,
	अणु 0x7a01, KEY_RECORD पूर्ण,
	अणु 0x7a02, KEY_PLAY पूर्ण,
	अणु 0x7a03, KEY_STOP पूर्ण,
	अणु 0x7a10, KEY_CHANNELUP पूर्ण,
	अणु 0x7a11, KEY_CHANNELDOWN पूर्ण,
	अणु 0x7a12, KEY_VOLUMEUP पूर्ण,
	अणु 0x7a13, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x7a40, KEY_POWER पूर्ण,
	अणु 0x7a41, KEY_MUTE पूर्ण,

	/* Key codes क्रम the Elgato EyeTV Diversity silver remote */
	अणु 0x4501, KEY_POWER पूर्ण,
	अणु 0x4502, KEY_MUTE पूर्ण,
	अणु 0x4503, KEY_NUMERIC_1 पूर्ण,
	अणु 0x4504, KEY_NUMERIC_2 पूर्ण,
	अणु 0x4505, KEY_NUMERIC_3 पूर्ण,
	अणु 0x4506, KEY_NUMERIC_4 पूर्ण,
	अणु 0x4507, KEY_NUMERIC_5 पूर्ण,
	अणु 0x4508, KEY_NUMERIC_6 पूर्ण,
	अणु 0x4509, KEY_NUMERIC_7 पूर्ण,
	अणु 0x450a, KEY_NUMERIC_8 पूर्ण,
	अणु 0x450b, KEY_NUMERIC_9 पूर्ण,
	अणु 0x450c, KEY_LAST पूर्ण,
	अणु 0x450d, KEY_NUMERIC_0 पूर्ण,
	अणु 0x450e, KEY_ENTER पूर्ण,
	अणु 0x450f, KEY_RED पूर्ण,
	अणु 0x4510, KEY_CHANNELUP पूर्ण,
	अणु 0x4511, KEY_GREEN पूर्ण,
	अणु 0x4512, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x4513, KEY_OK पूर्ण,
	अणु 0x4514, KEY_VOLUMEUP पूर्ण,
	अणु 0x4515, KEY_YELLOW पूर्ण,
	अणु 0x4516, KEY_CHANNELDOWN पूर्ण,
	अणु 0x4517, KEY_BLUE पूर्ण,
	अणु 0x4518, KEY_LEFT पूर्ण, /* Skip backwards */
	अणु 0x4519, KEY_PLAYPAUSE पूर्ण,
	अणु 0x451a, KEY_RIGHT पूर्ण, /* Skip क्रमward */
	अणु 0x451b, KEY_REWIND पूर्ण,
	अणु 0x451c, KEY_L पूर्ण, /* Live */
	अणु 0x451d, KEY_FASTFORWARD पूर्ण,
	अणु 0x451e, KEY_STOP पूर्ण, /* 'Reveal' क्रम Teletext */
	अणु 0x451f, KEY_MENU पूर्ण, /* KEY_TEXT क्रम Teletext */
	अणु 0x4540, KEY_RECORD पूर्ण, /* Font 'Size' क्रम Teletext */
	अणु 0x4541, KEY_SCREEN पूर्ण, /*  Full screen toggle, 'Hold' क्रम Teletext */
	अणु 0x4542, KEY_SELECT पूर्ण, /* Select video input, 'Select' क्रम Teletext */
पूर्ण;

अटल काष्ठा rc_map_list dib0700_nec_map = अणु
	.map = अणु
		.scan     = dib0700_nec_table,
		.size     = ARRAY_SIZE(dib0700_nec_table),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_DIB0700_NEC_TABLE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&dib0700_nec_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map(व्योम)
अणु
	rc_map_unरेजिस्टर(&dib0700_nec_map);
पूर्ण

module_init(init_rc_map)
module_निकास(निकास_rc_map)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
