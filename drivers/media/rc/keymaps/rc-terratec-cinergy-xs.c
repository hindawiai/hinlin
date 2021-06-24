<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// terratec-cinergy-xs.h - Keytable क्रम terratec_cinergy_xs Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Terratec Cinergy Hybrid T USB XS
   Devin Heiपंचांगueller <dheiपंचांगueller@linuxtv.org>
 */

अटल काष्ठा rc_map_table terratec_cinergy_xs[] = अणु
	अणु 0x41, KEY_HOMEपूर्ण,
	अणु 0x01, KEY_POWERपूर्ण,
	अणु 0x42, KEY_MENUपूर्ण,
	अणु 0x02, KEY_NUMERIC_1पूर्ण,
	अणु 0x03, KEY_NUMERIC_2पूर्ण,
	अणु 0x04, KEY_NUMERIC_3पूर्ण,
	अणु 0x43, KEY_SUBTITLEपूर्ण,
	अणु 0x05, KEY_NUMERIC_4पूर्ण,
	अणु 0x06, KEY_NUMERIC_5पूर्ण,
	अणु 0x07, KEY_NUMERIC_6पूर्ण,
	अणु 0x44, KEY_TEXTपूर्ण,
	अणु 0x08, KEY_NUMERIC_7पूर्ण,
	अणु 0x09, KEY_NUMERIC_8पूर्ण,
	अणु 0x0a, KEY_NUMERIC_9पूर्ण,
	अणु 0x45, KEY_DELETEपूर्ण,
	अणु 0x0b, KEY_TUNERपूर्ण,
	अणु 0x0c, KEY_NUMERIC_0पूर्ण,
	अणु 0x0d, KEY_MODEपूर्ण,
	अणु 0x46, KEY_TVपूर्ण,
	अणु 0x47, KEY_DVDपूर्ण,
	अणु 0x49, KEY_VIDEOपूर्ण,
	अणु 0x4b, KEY_AUXपूर्ण,
	अणु 0x10, KEY_UPपूर्ण,
	अणु 0x11, KEY_LEFTपूर्ण,
	अणु 0x12, KEY_OKपूर्ण,
	अणु 0x13, KEY_RIGHTपूर्ण,
	अणु 0x14, KEY_DOWNपूर्ण,
	अणु 0x0f, KEY_EPGपूर्ण,
	अणु 0x16, KEY_INFOपूर्ण,
	अणु 0x4d, KEY_BACKSPACEपूर्ण,
	अणु 0x1c, KEY_VOLUMEUPपूर्ण,
	अणु 0x4c, KEY_PLAYपूर्ण,
	अणु 0x1b, KEY_CHANNELUPपूर्ण,
	अणु 0x1e, KEY_VOLUMEDOWNपूर्ण,
	अणु 0x1d, KEY_MUTEपूर्ण,
	अणु 0x1f, KEY_CHANNELDOWNपूर्ण,
	अणु 0x17, KEY_REDपूर्ण,
	अणु 0x18, KEY_GREENपूर्ण,
	अणु 0x19, KEY_YELLOWपूर्ण,
	अणु 0x1a, KEY_BLUEपूर्ण,
	अणु 0x58, KEY_RECORDपूर्ण,
	अणु 0x48, KEY_STOPपूर्ण,
	अणु 0x40, KEY_PAUSEपूर्ण,
	अणु 0x54, KEY_LASTपूर्ण,
	अणु 0x4e, KEY_REWINDपूर्ण,
	अणु 0x4f, KEY_FASTFORWARDपूर्ण,
	अणु 0x5c, KEY_NEXTपूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list terratec_cinergy_xs_map = अणु
	.map = अणु
		.scan     = terratec_cinergy_xs,
		.size     = ARRAY_SIZE(terratec_cinergy_xs),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_TERRATEC_CINERGY_XS,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_terratec_cinergy_xs(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&terratec_cinergy_xs_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_terratec_cinergy_xs(व्योम)
अणु
	rc_map_unरेजिस्टर(&terratec_cinergy_xs_map);
पूर्ण

module_init(init_rc_map_terratec_cinergy_xs)
module_निकास(निकास_rc_map_terratec_cinergy_xs)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
