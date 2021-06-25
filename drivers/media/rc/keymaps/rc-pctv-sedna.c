<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// pctv-sedna.h - Keytable क्रम pctv_sedna Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Mapping क्रम the 28 key remote control as seen at
   http://www.sednacomputer.com/photo/cardbus-tv.jpg
   Pavel Mihaylov <bin@bash.info>
   Also क्रम the remote bundled with Kozumi KTV-01C card */

अटल काष्ठा rc_map_table pctv_sedna[] = अणु
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

	अणु 0x0a, KEY_AGAIN पूर्ण,	/* Recall */
	अणु 0x0b, KEY_CHANNELUP पूर्ण,
	अणु 0x0c, KEY_VOLUMEUP पूर्ण,
	अणु 0x0d, KEY_MODE पूर्ण,	/* Stereo */
	अणु 0x0e, KEY_STOP पूर्ण,
	अणु 0x0f, KEY_PREVIOUSSONG पूर्ण,
	अणु 0x10, KEY_ZOOM पूर्ण,
	अणु 0x11, KEY_VIDEO पूर्ण,	/* Source */
	अणु 0x12, KEY_POWER पूर्ण,
	अणु 0x13, KEY_MUTE पूर्ण,
	अणु 0x15, KEY_CHANNELDOWN पूर्ण,
	अणु 0x18, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x19, KEY_CAMERA पूर्ण,	/* Snapshot */
	अणु 0x1a, KEY_NEXTSONG पूर्ण,
	अणु 0x1b, KEY_TIME पूर्ण,	/* Time Shअगरt */
	अणु 0x1c, KEY_RADIO पूर्ण,	/* FM Radio */
	अणु 0x1d, KEY_RECORD पूर्ण,
	अणु 0x1e, KEY_PAUSE पूर्ण,
	/* additional codes क्रम Kozumi's remote */
	अणु 0x14, KEY_INFO पूर्ण,	/* OSD */
	अणु 0x16, KEY_OK पूर्ण,	/* OK */
	अणु 0x17, KEY_DIGITS पूर्ण,	/* Plus */
	अणु 0x1f, KEY_PLAY पूर्ण,	/* Play */
पूर्ण;

अटल काष्ठा rc_map_list pctv_sedna_map = अणु
	.map = अणु
		.scan     = pctv_sedna,
		.size     = ARRAY_SIZE(pctv_sedna),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_PCTV_SEDNA,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_pctv_sedna(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&pctv_sedna_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_pctv_sedna(व्योम)
अणु
	rc_map_unरेजिस्टर(&pctv_sedna_map);
पूर्ण

module_init(init_rc_map_pctv_sedna)
module_निकास(निकास_rc_map_pctv_sedna)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
