<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// gadmei-rm008z.h - Keytable क्रम gadmei_rm008z Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* GADMEI UTV330+ RM008Z remote
   Shine Liu <shinel@foxmail.com>
 */

अटल काष्ठा rc_map_table gadmei_rm008z[] = अणु
	अणु 0x14, KEY_POWER2पूर्ण,		/* POWER OFF */
	अणु 0x0c, KEY_MUTEपूर्ण,		/* MUTE */

	अणु 0x18, KEY_TVपूर्ण,		/* TV */
	अणु 0x0e, KEY_VIDEOपूर्ण,		/* AV */
	अणु 0x0b, KEY_AUDIOपूर्ण,		/* SV */
	अणु 0x0f, KEY_RADIOपूर्ण,		/* FM */

	अणु 0x00, KEY_NUMERIC_1पूर्ण,
	अणु 0x01, KEY_NUMERIC_2पूर्ण,
	अणु 0x02, KEY_NUMERIC_3पूर्ण,
	अणु 0x03, KEY_NUMERIC_4पूर्ण,
	अणु 0x04, KEY_NUMERIC_5पूर्ण,
	अणु 0x05, KEY_NUMERIC_6पूर्ण,
	अणु 0x06, KEY_NUMERIC_7पूर्ण,
	अणु 0x07, KEY_NUMERIC_8पूर्ण,
	अणु 0x08, KEY_NUMERIC_9पूर्ण,
	अणु 0x09, KEY_NUMERIC_0पूर्ण,
	अणु 0x0a, KEY_INFOपूर्ण,		/* OSD */
	अणु 0x1c, KEY_BACKSPACEपूर्ण,		/* LAST */

	अणु 0x0d, KEY_PLAYपूर्ण,		/* PLAY */
	अणु 0x1e, KEY_CAMERAपूर्ण,		/* SNAPSHOT */
	अणु 0x1a, KEY_RECORDपूर्ण,		/* RECORD */
	अणु 0x17, KEY_STOPपूर्ण,		/* STOP */

	अणु 0x1f, KEY_UPपूर्ण,		/* UP */
	अणु 0x44, KEY_DOWNपूर्ण,		/* DOWN */
	अणु 0x46, KEY_TABपूर्ण,		/* BACK */
	अणु 0x4a, KEY_ZOOMपूर्ण,		/* FULLSECREEN */

	अणु 0x10, KEY_VOLUMEUPपूर्ण,		/* VOLUMEUP */
	अणु 0x11, KEY_VOLUMEDOWNपूर्ण,	/* VOLUMEDOWN */
	अणु 0x12, KEY_CHANNELUPपूर्ण,		/* CHANNELUP */
	अणु 0x13, KEY_CHANNELDOWNपूर्ण,	/* CHANNELDOWN */
	अणु 0x15, KEY_ENTERपूर्ण,		/* OK */
पूर्ण;

अटल काष्ठा rc_map_list gadmei_rm008z_map = अणु
	.map = अणु
		.scan     = gadmei_rm008z,
		.size     = ARRAY_SIZE(gadmei_rm008z),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_GADMEI_RM008Z,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_gadmei_rm008z(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&gadmei_rm008z_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_gadmei_rm008z(व्योम)
अणु
	rc_map_unरेजिस्टर(&gadmei_rm008z_map);
पूर्ण

module_init(init_rc_map_gadmei_rm008z)
module_निकास(निकास_rc_map_gadmei_rm008z)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
