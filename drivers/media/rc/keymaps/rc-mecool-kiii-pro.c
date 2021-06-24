<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (C) 2021 Christian Hewitt <christianshewitt@gmail.com>

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

//
// Keytable क्रम the Mecool Kiii Pro remote control
//

अटल काष्ठा rc_map_table mecool_kiii_pro[] = अणु
	अणु 0x59, KEY_POWER पूर्ण,

	अणु 0x52, KEY_1 पूर्ण,
	अणु 0x50, KEY_2 पूर्ण,
	अणु 0x10, KEY_3 पूर्ण,
	अणु 0x56, KEY_4 पूर्ण,
	अणु 0x54, KEY_5 पूर्ण,
	अणु 0x14, KEY_6 पूर्ण,
	अणु 0x4e, KEY_7 पूर्ण,
	अणु 0x4c, KEY_8 पूर्ण,
	अणु 0x0c, KEY_9 पूर्ण,
	अणु 0x02, KEY_INFO पूर्ण,
	अणु 0x0f, KEY_0 पूर्ण,
	अणु 0x51, KEY_DELETE पूर्ण,
	अणु 0x1f, KEY_FAVORITESपूर्ण,
	अणु 0x09, KEY_SUBTITLE पूर्ण,
	अणु 0x01, KEY_LANGUAGE पूर्ण, // AUDIO

	अणु 0x42, KEY_RED पूर्ण,
	अणु 0x40, KEY_GREEN पूर्ण,
	अणु 0x00, KEY_YELLOWपूर्ण,
	अणु 0x03, KEY_BLUE पूर्ण, // RADIO

	अणु 0x0d, KEY_HOME पूर्ण,
	अणु 0x4d, KEY_EPG पूर्ण,
	अणु 0x45, KEY_MENU पूर्ण,
	अणु 0x05, KEY_EXIT पूर्ण,

	अणु 0x5a, KEY_LEFT पूर्ण,
	अणु 0x1b, KEY_RIGHT पूर्ण,
	अणु 0x06, KEY_UP पूर्ण,
	अणु 0x16, KEY_DOWN पूर्ण,
	अणु 0x1a, KEY_OK पूर्ण,

	अणु 0x13, KEY_VOLUMEUP पूर्ण,
	अणु 0x17, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x19, KEY_MUTE पूर्ण,
	अणु 0x12, KEY_CONTEXT_MENU पूर्ण, // MOUSE
	अणु 0x55, KEY_CHANNELUP पूर्ण, // PAGE_UP
	अणु 0x15, KEY_CHANNELDOWN पूर्ण, // PAGE_DOWN

	अणु 0x4a, KEY_REWIND पूर्ण,
	अणु 0x48, KEY_FORWARD पूर्ण,
	अणु 0x46, KEY_PLAYPAUSE पूर्ण,
	अणु 0x44, KEY_STOP पूर्ण,

	अणु 0x08, KEY_PREVIOUSSONGपूर्ण,
	अणु 0x0b, KEY_NEXTSONGपूर्ण,
	अणु 0x04, KEY_PVR पूर्ण,
	अणु 0x64, KEY_RECORD पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list mecool_kiii_pro_map = अणु
	.map = अणु
		.scan     = mecool_kiii_pro,
		.size     = ARRAY_SIZE(mecool_kiii_pro),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_MECOOL_KIII_PRO,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_mecool_kiii_pro(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&mecool_kiii_pro_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_mecool_kiii_pro(व्योम)
अणु
	rc_map_unरेजिस्टर(&mecool_kiii_pro_map);
पूर्ण

module_init(init_rc_map_mecool_kiii_pro)
module_निकास(निकास_rc_map_mecool_kiii_pro)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Hewitt <christianshewitt@gmail.com");
