<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// tevii-nec.h - Keytable क्रम tevii_nec Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table tevii_nec[] = अणु
	अणु 0x0a, KEY_POWER2पूर्ण,
	अणु 0x0c, KEY_MUTEपूर्ण,
	अणु 0x11, KEY_NUMERIC_1पूर्ण,
	अणु 0x12, KEY_NUMERIC_2पूर्ण,
	अणु 0x13, KEY_NUMERIC_3पूर्ण,
	अणु 0x14, KEY_NUMERIC_4पूर्ण,
	अणु 0x15, KEY_NUMERIC_5पूर्ण,
	अणु 0x16, KEY_NUMERIC_6पूर्ण,
	अणु 0x17, KEY_NUMERIC_7पूर्ण,
	अणु 0x18, KEY_NUMERIC_8पूर्ण,
	अणु 0x19, KEY_NUMERIC_9पूर्ण,
	अणु 0x10, KEY_NUMERIC_0पूर्ण,
	अणु 0x1c, KEY_MENUपूर्ण,
	अणु 0x0f, KEY_VOLUMEDOWNपूर्ण,
	अणु 0x1a, KEY_LASTपूर्ण,
	अणु 0x0e, KEY_OPENपूर्ण,
	अणु 0x04, KEY_RECORDपूर्ण,
	अणु 0x09, KEY_VOLUMEUPपूर्ण,
	अणु 0x08, KEY_CHANNELUPपूर्ण,
	अणु 0x07, KEY_PVRपूर्ण,
	अणु 0x0b, KEY_TIMEपूर्ण,
	अणु 0x02, KEY_RIGHTपूर्ण,
	अणु 0x03, KEY_LEFTपूर्ण,
	अणु 0x00, KEY_UPपूर्ण,
	अणु 0x1f, KEY_OKपूर्ण,
	अणु 0x01, KEY_DOWNपूर्ण,
	अणु 0x05, KEY_TUNERपूर्ण,
	अणु 0x06, KEY_CHANNELDOWNपूर्ण,
	अणु 0x40, KEY_PLAYPAUSEपूर्ण,
	अणु 0x1e, KEY_REWINDपूर्ण,
	अणु 0x1b, KEY_FAVORITESपूर्ण,
	अणु 0x1d, KEY_BACKपूर्ण,
	अणु 0x4d, KEY_FASTFORWARDपूर्ण,
	अणु 0x44, KEY_EPGपूर्ण,
	अणु 0x4c, KEY_INFOपूर्ण,
	अणु 0x41, KEY_ABपूर्ण,
	अणु 0x43, KEY_AUDIOपूर्ण,
	अणु 0x45, KEY_SUBTITLEपूर्ण,
	अणु 0x4a, KEY_LISTपूर्ण,
	अणु 0x46, KEY_F1पूर्ण,
	अणु 0x47, KEY_F2पूर्ण,
	अणु 0x5e, KEY_F3पूर्ण,
	अणु 0x5c, KEY_F4पूर्ण,
	अणु 0x52, KEY_F5पूर्ण,
	अणु 0x5a, KEY_F6पूर्ण,
	अणु 0x56, KEY_MODEपूर्ण,
	अणु 0x58, KEY_SWITCHVIDEOMODEपूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list tevii_nec_map = अणु
	.map = अणु
		.scan     = tevii_nec,
		.size     = ARRAY_SIZE(tevii_nec),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_TEVII_NEC,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_tevii_nec(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&tevii_nec_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_tevii_nec(व्योम)
अणु
	rc_map_unरेजिस्टर(&tevii_nec_map);
पूर्ण

module_init(init_rc_map_tevii_nec)
module_निकास(निकास_rc_map_tevii_nec)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
