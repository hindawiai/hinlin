<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Keytable क्रम remote controller of HiSilicon tv demo board.
 *
 * Copyright (c) 2017 HiSilicon Technologies Co., Ltd.
 */

#समावेश <linux/module.h>
#समावेश <media/rc-map.h>

अटल काष्ठा rc_map_table hisi_tv_demo_keymap[] = अणु
	अणु 0x00000092, KEY_NUMERIC_1पूर्ण,
	अणु 0x00000093, KEY_NUMERIC_2पूर्ण,
	अणु 0x000000cc, KEY_NUMERIC_3पूर्ण,
	अणु 0x0000009f, KEY_NUMERIC_4पूर्ण,
	अणु 0x0000008e, KEY_NUMERIC_5पूर्ण,
	अणु 0x0000008f, KEY_NUMERIC_6पूर्ण,
	अणु 0x000000c8, KEY_NUMERIC_7पूर्ण,
	अणु 0x00000094, KEY_NUMERIC_8पूर्ण,
	अणु 0x0000008a, KEY_NUMERIC_9पूर्ण,
	अणु 0x0000008b, KEY_NUMERIC_0पूर्ण,
	अणु 0x000000ce, KEY_ENTERपूर्ण,
	अणु 0x000000ca, KEY_UPपूर्ण,
	अणु 0x00000099, KEY_LEFTपूर्ण,
	अणु 0x00000084, KEY_PAGEUPपूर्ण,
	अणु 0x000000c1, KEY_RIGHTपूर्ण,
	अणु 0x000000d2, KEY_DOWNपूर्ण,
	अणु 0x00000089, KEY_PAGEDOWNपूर्ण,
	अणु 0x000000d1, KEY_MUTEपूर्ण,
	अणु 0x00000098, KEY_VOLUMEDOWNपूर्ण,
	अणु 0x00000090, KEY_VOLUMEUPपूर्ण,
	अणु 0x0000009c, KEY_POWERपूर्ण,
	अणु 0x000000d6, KEY_STOPपूर्ण,
	अणु 0x00000097, KEY_MENUपूर्ण,
	अणु 0x000000cb, KEY_BACKपूर्ण,
	अणु 0x000000da, KEY_PLAYPAUSEपूर्ण,
	अणु 0x00000080, KEY_INFOपूर्ण,
	अणु 0x000000c3, KEY_REWINDपूर्ण,
	अणु 0x00000087, KEY_HOMEPAGEपूर्ण,
	अणु 0x000000d0, KEY_FASTFORWARDपूर्ण,
	अणु 0x000000c4, KEY_SOUNDपूर्ण,
	अणु 0x00000082, BTN_1पूर्ण,
	अणु 0x000000c7, BTN_2पूर्ण,
	अणु 0x00000086, KEY_PROGRAMपूर्ण,
	अणु 0x000000d9, KEY_SUBTITLEपूर्ण,
	अणु 0x00000085, KEY_ZOOMपूर्ण,
	अणु 0x0000009b, KEY_REDपूर्ण,
	अणु 0x0000009a, KEY_GREENपूर्ण,
	अणु 0x000000c0, KEY_YELLOWपूर्ण,
	अणु 0x000000c2, KEY_BLUEपूर्ण,
	अणु 0x0000009d, KEY_CHANNELDOWNपूर्ण,
	अणु 0x000000cf, KEY_CHANNELUPपूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list hisi_tv_demo_map = अणु
	.map = अणु
		.scan	  = hisi_tv_demo_keymap,
		.size	  = ARRAY_SIZE(hisi_tv_demo_keymap),
		.rc_proto = RC_PROTO_NEC,
		.name	  = RC_MAP_HISI_TV_DEMO,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_hisi_tv_demo(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&hisi_tv_demo_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_hisi_tv_demo(व्योम)
अणु
	rc_map_unरेजिस्टर(&hisi_tv_demo_map);
पूर्ण

module_init(init_rc_map_hisi_tv_demo)
module_निकास(निकास_rc_map_hisi_tv_demo)

MODULE_LICENSE("GPL v2");
