<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// tbs-nec.h - Keytable क्रम tbs_nec Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table tbs_nec[] = अणु
	अणु 0x84, KEY_POWER2पूर्ण,		/* घातer */
	अणु 0x94, KEY_MUTEपूर्ण,		/* mute */
	अणु 0x87, KEY_NUMERIC_1पूर्ण,
	अणु 0x86, KEY_NUMERIC_2पूर्ण,
	अणु 0x85, KEY_NUMERIC_3पूर्ण,
	अणु 0x8b, KEY_NUMERIC_4पूर्ण,
	अणु 0x8a, KEY_NUMERIC_5पूर्ण,
	अणु 0x89, KEY_NUMERIC_6पूर्ण,
	अणु 0x8f, KEY_NUMERIC_7पूर्ण,
	अणु 0x8e, KEY_NUMERIC_8पूर्ण,
	अणु 0x8d, KEY_NUMERIC_9पूर्ण,
	अणु 0x92, KEY_NUMERIC_0पूर्ण,
	अणु 0xc0, KEY_10CHANNELSUPपूर्ण,	/* 10+ */
	अणु 0xd0, KEY_10CHANNELSDOWNपूर्ण,	/* 10- */
	अणु 0x96, KEY_CHANNELUPपूर्ण,		/* ch+ */
	अणु 0x91, KEY_CHANNELDOWNपूर्ण,	/* ch- */
	अणु 0x93, KEY_VOLUMEUPपूर्ण,		/* vol+ */
	अणु 0x8c, KEY_VOLUMEDOWNपूर्ण,	/* vol- */
	अणु 0x83, KEY_RECORDपूर्ण,		/* rec */
	अणु 0x98, KEY_PAUSEपूर्ण,		/* छोड़ो, yellow */
	अणु 0x99, KEY_OKपूर्ण,		/* ok */
	अणु 0x9a, KEY_CAMERAपूर्ण,		/* snapshot */
	अणु 0x81, KEY_UPपूर्ण,
	अणु 0x90, KEY_LEFTपूर्ण,
	अणु 0x82, KEY_RIGHTपूर्ण,
	अणु 0x88, KEY_DOWNपूर्ण,
	अणु 0x95, KEY_FAVORITESपूर्ण,		/* blue */
	अणु 0x97, KEY_SUBTITLEपूर्ण,		/* green */
	अणु 0x9d, KEY_ZOOMपूर्ण,
	अणु 0x9f, KEY_EXITपूर्ण,
	अणु 0x9e, KEY_MENUपूर्ण,
	अणु 0x9c, KEY_EPGपूर्ण,
	अणु 0x80, KEY_PREVIOUSपूर्ण,		/* red */
	अणु 0x9b, KEY_MODEपूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list tbs_nec_map = अणु
	.map = अणु
		.scan     = tbs_nec,
		.size     = ARRAY_SIZE(tbs_nec),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_TBS_NEC,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_tbs_nec(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&tbs_nec_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_tbs_nec(व्योम)
अणु
	rc_map_unरेजिस्टर(&tbs_nec_map);
पूर्ण

module_init(init_rc_map_tbs_nec)
module_निकास(निकास_rc_map_tbs_nec)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
