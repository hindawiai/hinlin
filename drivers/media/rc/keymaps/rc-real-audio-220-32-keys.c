<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// real-audio-220-32-keys.h - Keytable क्रम real_audio_220_32_keys Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Zogis Real Audio 220 - 32 keys IR */

अटल काष्ठा rc_map_table real_audio_220_32_keys[] = अणु
	अणु 0x1c, KEY_RADIOपूर्ण,
	अणु 0x12, KEY_POWER2पूर्ण,

	अणु 0x01, KEY_NUMERIC_1पूर्ण,
	अणु 0x02, KEY_NUMERIC_2पूर्ण,
	अणु 0x03, KEY_NUMERIC_3पूर्ण,
	अणु 0x04, KEY_NUMERIC_4पूर्ण,
	अणु 0x05, KEY_NUMERIC_5पूर्ण,
	अणु 0x06, KEY_NUMERIC_6पूर्ण,
	अणु 0x07, KEY_NUMERIC_7पूर्ण,
	अणु 0x08, KEY_NUMERIC_8पूर्ण,
	अणु 0x09, KEY_NUMERIC_9पूर्ण,
	अणु 0x00, KEY_NUMERIC_0पूर्ण,

	अणु 0x0c, KEY_VOLUMEUPपूर्ण,
	अणु 0x18, KEY_VOLUMEDOWNपूर्ण,
	अणु 0x0b, KEY_CHANNELUPपूर्ण,
	अणु 0x15, KEY_CHANNELDOWNपूर्ण,
	अणु 0x16, KEY_ENTERपूर्ण,

	अणु 0x11, KEY_VIDEOपूर्ण,		/* Source */
	अणु 0x0d, KEY_AUDIOपूर्ण,		/* stereo */

	अणु 0x0f, KEY_PREVIOUSपूर्ण,		/* Prev */
	अणु 0x1b, KEY_TIMEपूर्ण,		/* Timeshअगरt */
	अणु 0x1a, KEY_NEXTपूर्ण,		/* Next */

	अणु 0x0e, KEY_STOPपूर्ण,
	अणु 0x1f, KEY_PLAYपूर्ण,
	अणु 0x1e, KEY_PLAYPAUSEपूर्ण,		/* Pause */

	अणु 0x1d, KEY_RECORDपूर्ण,
	अणु 0x13, KEY_MUTEपूर्ण,
	अणु 0x19, KEY_CAMERAपूर्ण,		/* Snapshot */

पूर्ण;

अटल काष्ठा rc_map_list real_audio_220_32_keys_map = अणु
	.map = अणु
		.scan     = real_audio_220_32_keys,
		.size     = ARRAY_SIZE(real_audio_220_32_keys),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_REAL_AUDIO_220_32_KEYS,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_real_audio_220_32_keys(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&real_audio_220_32_keys_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_real_audio_220_32_keys(व्योम)
अणु
	rc_map_unरेजिस्टर(&real_audio_220_32_keys_map);
पूर्ण

module_init(init_rc_map_real_audio_220_32_keys)
module_निकास(निकास_rc_map_real_audio_220_32_keys)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
