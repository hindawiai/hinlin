<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Keytable क्रम remote controller of HiSilicon poplar board.
 *
 * Copyright (c) 2017 HiSilicon Technologies Co., Ltd.
 */

#समावेश <linux/module.h>
#समावेश <media/rc-map.h>

अटल काष्ठा rc_map_table hisi_poplar_keymap[] = अणु
	अणु 0x0000b292, KEY_NUMERIC_1पूर्ण,
	अणु 0x0000b293, KEY_NUMERIC_2पूर्ण,
	अणु 0x0000b2cc, KEY_NUMERIC_3पूर्ण,
	अणु 0x0000b28e, KEY_NUMERIC_4पूर्ण,
	अणु 0x0000b28f, KEY_NUMERIC_5पूर्ण,
	अणु 0x0000b2c8, KEY_NUMERIC_6पूर्ण,
	अणु 0x0000b28a, KEY_NUMERIC_7पूर्ण,
	अणु 0x0000b28b, KEY_NUMERIC_8पूर्ण,
	अणु 0x0000b2c4, KEY_NUMERIC_9पूर्ण,
	अणु 0x0000b287, KEY_NUMERIC_0पूर्ण,
	अणु 0x0000b282, KEY_HOMEPAGEपूर्ण,
	अणु 0x0000b2ca, KEY_UPपूर्ण,
	अणु 0x0000b299, KEY_LEFTपूर्ण,
	अणु 0x0000b2c1, KEY_RIGHTपूर्ण,
	अणु 0x0000b2d2, KEY_DOWNपूर्ण,
	अणु 0x0000b2c5, KEY_DELETEपूर्ण,
	अणु 0x0000b29c, KEY_MUTEपूर्ण,
	अणु 0x0000b281, KEY_VOLUMEDOWNपूर्ण,
	अणु 0x0000b280, KEY_VOLUMEUPपूर्ण,
	अणु 0x0000b2dc, KEY_POWERपूर्ण,
	अणु 0x0000b29a, KEY_MENUपूर्ण,
	अणु 0x0000b28d, KEY_SETUPपूर्ण,
	अणु 0x0000b2c5, KEY_BACKपूर्ण,
	अणु 0x0000b295, KEY_PLAYPAUSEपूर्ण,
	अणु 0x0000b2ce, KEY_ENTERपूर्ण,
	अणु 0x0000b285, KEY_CHANNELUPपूर्ण,
	अणु 0x0000b286, KEY_CHANNELDOWNपूर्ण,
	अणु 0x0000b2da, KEY_NUMERIC_STARपूर्ण,
	अणु 0x0000b2d0, KEY_NUMERIC_POUNDपूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list hisi_poplar_map = अणु
	.map = अणु
		.scan	  = hisi_poplar_keymap,
		.size	  = ARRAY_SIZE(hisi_poplar_keymap),
		.rc_proto = RC_PROTO_NEC,
		.name	  = RC_MAP_HISI_POPLAR,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_hisi_poplar(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&hisi_poplar_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_hisi_poplar(व्योम)
अणु
	rc_map_unरेजिस्टर(&hisi_poplar_map);
पूर्ण

module_init(init_rc_map_hisi_poplar)
module_निकास(निकास_rc_map_hisi_poplar)

MODULE_LICENSE("GPL v2");
