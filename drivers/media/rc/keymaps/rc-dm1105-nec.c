<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// dm1105-nec.h - Keytable क्रम dm1105_nec Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* DVBWorld remotes
   Igor M. Liplianin <liplianin@me.by>
 */

अटल काष्ठा rc_map_table dm1105_nec[] = अणु
	अणु 0x0a, KEY_POWER2पूर्ण,		/* घातer */
	अणु 0x0c, KEY_MUTEपूर्ण,		/* mute */
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
	अणु 0x1c, KEY_CHANNELUPपूर्ण,		/* ch+ */
	अणु 0x0f, KEY_CHANNELDOWNपूर्ण,	/* ch- */
	अणु 0x1a, KEY_VOLUMEUPपूर्ण,		/* vol+ */
	अणु 0x0e, KEY_VOLUMEDOWNपूर्ण,	/* vol- */
	अणु 0x04, KEY_RECORDपूर्ण,		/* rec */
	अणु 0x09, KEY_CHANNELपूर्ण,		/* fav */
	अणु 0x08, KEY_BACKSPACEपूर्ण,		/* शुरुआत */
	अणु 0x07, KEY_FASTFORWARDपूर्ण,	/* fast */
	अणु 0x0b, KEY_PAUSEपूर्ण,		/* छोड़ो */
	अणु 0x02, KEY_ESCपूर्ण,		/* cancel */
	अणु 0x03, KEY_TABपूर्ण,		/* tab */
	अणु 0x00, KEY_UPपूर्ण,		/* up */
	अणु 0x1f, KEY_ENTERपूर्ण,		/* ok */
	अणु 0x01, KEY_DOWNपूर्ण,		/* करोwn */
	अणु 0x05, KEY_RECORDपूर्ण,		/* cap */
	अणु 0x06, KEY_STOPपूर्ण,		/* stop */
	अणु 0x40, KEY_ZOOMपूर्ण,		/* full */
	अणु 0x1e, KEY_TVपूर्ण,		/* tvmode */
	अणु 0x1b, KEY_Bपूर्ण,			/* recall */
पूर्ण;

अटल काष्ठा rc_map_list dm1105_nec_map = अणु
	.map = अणु
		.scan     = dm1105_nec,
		.size     = ARRAY_SIZE(dm1105_nec),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_DM1105_NEC,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_dm1105_nec(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&dm1105_nec_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_dm1105_nec(व्योम)
अणु
	rc_map_unरेजिस्टर(&dm1105_nec_map);
पूर्ण

module_init(init_rc_map_dm1105_nec)
module_निकास(निकास_rc_map_dm1105_nec)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
