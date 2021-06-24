<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// msi-tvanywhere.h - Keytable क्रम msi_tvanywhere Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* MSI TV@nywhere MASTER remote */

अटल काष्ठा rc_map_table msi_tvanywhere[] = अणु
	/* Keys 0 to 9 */
	अणु 0x00, KEY_NUMERIC_0 पूर्ण,
	अणु 0x01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x03, KEY_NUMERIC_3 पूर्ण,
	अणु 0x04, KEY_NUMERIC_4 पूर्ण,
	अणु 0x05, KEY_NUMERIC_5 पूर्ण,
	अणु 0x06, KEY_NUMERIC_6 पूर्ण,
	अणु 0x07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x09, KEY_NUMERIC_9 पूर्ण,

	अणु 0x0c, KEY_MUTE पूर्ण,
	अणु 0x0f, KEY_SCREEN पूर्ण,		/* Full Screen */
	अणु 0x10, KEY_FN पूर्ण,		/* Function */
	अणु 0x11, KEY_TIME पूर्ण,		/* Time shअगरt */
	अणु 0x12, KEY_POWER पूर्ण,
	अणु 0x13, KEY_MEDIA पूर्ण,		/* MTS */
	अणु 0x14, KEY_SLOW पूर्ण,
	अणु 0x16, KEY_REWIND पूर्ण,		/* backward << */
	अणु 0x17, KEY_ENTER पूर्ण,		/* Return */
	अणु 0x18, KEY_FASTFORWARD पूर्ण,	/* क्रमward >> */
	अणु 0x1a, KEY_CHANNELUP पूर्ण,
	अणु 0x1b, KEY_VOLUMEUP पूर्ण,
	अणु 0x1e, KEY_CHANNELDOWN पूर्ण,
	अणु 0x1f, KEY_VOLUMEDOWN पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list msi_tvanywhere_map = अणु
	.map = अणु
		.scan     = msi_tvanywhere,
		.size     = ARRAY_SIZE(msi_tvanywhere),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_MSI_TVANYWHERE,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_msi_tvanywhere(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&msi_tvanywhere_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_msi_tvanywhere(व्योम)
अणु
	rc_map_unरेजिस्टर(&msi_tvanywhere_map);
पूर्ण

module_init(init_rc_map_msi_tvanywhere)
module_निकास(निकास_rc_map_msi_tvanywhere)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
