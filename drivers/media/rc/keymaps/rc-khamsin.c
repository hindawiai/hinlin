<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright (c) 2020 Christian Hewitt

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/*
 * KHAMSIN is an IR/Bluetooth RCU supplied with the SmartLअसल
 * SML-5442TW DVB-S/VOD box. The RCU has separate IR (TV) and
 * BT (STB) modes. This keymap suppors the IR controls.
 */

अटल काष्ठा rc_map_table khamsin[] = अणु
	अणु 0x70702, KEY_POWERपूर्ण,

	अणु 0x70701, KEY_VIDEOपूर्ण, // source

	अणु 0x7076c, KEY_REDपूर्ण,
	अणु 0x70714, KEY_GREENपूर्ण,
	अणु 0x70715, KEY_YELLOWपूर्ण,
	अणु 0x70716, KEY_BLUEपूर्ण,

	अणु 0x7071a, KEY_MENUपूर्ण,
	अणु 0x7074f, KEY_EPGपूर्ण,

	अणु 0x70760, KEY_UP पूर्ण,
	अणु 0x70761, KEY_DOWN पूर्ण,
	अणु 0x70765, KEY_LEFT पूर्ण,
	अणु 0x70762, KEY_RIGHT पूर्ण,
	अणु 0x70768, KEY_ENTER पूर्ण,

	अणु 0x7072d, KEY_ESC पूर्ण, // back

	अणु 0x70707, KEY_VOLUMEUP पूर्ण,
	अणु 0x7070b, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x7070f, KEY_MUTE पूर्ण,
	अणु 0x70712, KEY_CHANNELUP पूर्ण,
	अणु 0x70710, KEY_CHANNELDOWN पूर्ण,

	अणु 0x70704, KEY_1 पूर्ण,
	अणु 0x70705, KEY_2 पूर्ण,
	अणु 0x70706, KEY_3 पूर्ण,
	अणु 0x70708, KEY_4 पूर्ण,
	अणु 0x70709, KEY_5 पूर्ण,
	अणु 0x7070a, KEY_6 पूर्ण,
	अणु 0x7070c, KEY_7 पूर्ण,
	अणु 0x7070d, KEY_8 पूर्ण,
	अणु 0x7070e, KEY_9 पूर्ण,
	अणु 0x70711, KEY_0 पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list khamsin_map = अणु
	.map = अणु
		.scan     = khamsin,
		.size     = ARRAY_SIZE(khamsin),
		.rc_proto = RC_PROTO_NECX,
		.name     = RC_MAP_KHAMSIN,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_khamsin(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&khamsin_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_khamsin(व्योम)
अणु
	rc_map_unरेजिस्टर(&khamsin_map);
पूर्ण

module_init(init_rc_map_khamsin)
module_निकास(निकास_rc_map_khamsin)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Hewitt <christianshewitt@gmail.com>");
