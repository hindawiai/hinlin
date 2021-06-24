<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// videomate-s350.h - Keytable क्रम videomate_s350 Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table videomate_s350[] = अणु
	अणु 0x00, KEY_TVपूर्ण,
	अणु 0x01, KEY_DVDपूर्ण,
	अणु 0x04, KEY_RECORDपूर्ण,
	अणु 0x05, KEY_VIDEOपूर्ण,	/* TV/Video */
	अणु 0x07, KEY_STOPपूर्ण,
	अणु 0x08, KEY_PLAYPAUSEपूर्ण,
	अणु 0x0a, KEY_REWINDपूर्ण,
	अणु 0x0f, KEY_FASTFORWARDपूर्ण,
	अणु 0x10, KEY_CHANNELUPपूर्ण,
	अणु 0x12, KEY_VOLUMEUPपूर्ण,
	अणु 0x13, KEY_CHANNELDOWNपूर्ण,
	अणु 0x14, KEY_MUTEपूर्ण,
	अणु 0x15, KEY_VOLUMEDOWNपूर्ण,
	अणु 0x16, KEY_NUMERIC_1पूर्ण,
	अणु 0x17, KEY_NUMERIC_2पूर्ण,
	अणु 0x18, KEY_NUMERIC_3पूर्ण,
	अणु 0x19, KEY_NUMERIC_4पूर्ण,
	अणु 0x1a, KEY_NUMERIC_5पूर्ण,
	अणु 0x1b, KEY_NUMERIC_6पूर्ण,
	अणु 0x1c, KEY_NUMERIC_7पूर्ण,
	अणु 0x1d, KEY_NUMERIC_8पूर्ण,
	अणु 0x1e, KEY_NUMERIC_9पूर्ण,
	अणु 0x1f, KEY_NUMERIC_0पूर्ण,
	अणु 0x21, KEY_SLEEPपूर्ण,
	अणु 0x24, KEY_ZOOMपूर्ण,
	अणु 0x25, KEY_LASTपूर्ण,	/* Recall */
	अणु 0x26, KEY_SUBTITLEपूर्ण,	/* CC */
	अणु 0x27, KEY_LANGUAGEपूर्ण,	/* MTS */
	अणु 0x29, KEY_CHANNELपूर्ण,	/* SURF */
	अणु 0x2b, KEY_Aपूर्ण,
	अणु 0x2c, KEY_Bपूर्ण,
	अणु 0x2f, KEY_CAMERAपूर्ण,	/* Snapshot */
	अणु 0x23, KEY_RADIOपूर्ण,
	अणु 0x02, KEY_PREVIOUSSONGपूर्ण,
	अणु 0x06, KEY_NEXTSONGपूर्ण,
	अणु 0x03, KEY_EPGपूर्ण,
	अणु 0x09, KEY_SETUPपूर्ण,
	अणु 0x22, KEY_BACKSPACEपूर्ण,
	अणु 0x0c, KEY_UPपूर्ण,
	अणु 0x0e, KEY_DOWNपूर्ण,
	अणु 0x0b, KEY_LEFTपूर्ण,
	अणु 0x0d, KEY_RIGHTपूर्ण,
	अणु 0x11, KEY_ENTERपूर्ण,
	अणु 0x20, KEY_TEXTपूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list videomate_s350_map = अणु
	.map = अणु
		.scan     = videomate_s350,
		.size     = ARRAY_SIZE(videomate_s350),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_VIDEOMATE_S350,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_videomate_s350(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&videomate_s350_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_videomate_s350(व्योम)
अणु
	rc_map_unरेजिस्टर(&videomate_s350_map);
पूर्ण

module_init(init_rc_map_videomate_s350)
module_निकास(निकास_rc_map_videomate_s350)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
