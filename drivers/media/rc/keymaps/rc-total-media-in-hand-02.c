<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Total Media In Hand_02 remote controller keytable क्रम Mygica X8507
 *
 * Copyright (C) 2012 Alfreकरो J. Delaiti <alfreकरोdelaiti@netscape.net>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>


अटल काष्ठा rc_map_table total_media_in_hand_02[] = अणु
	अणु 0x0000, KEY_NUMERIC_0 पूर्ण,
	अणु 0x0001, KEY_NUMERIC_1 पूर्ण,
	अणु 0x0002, KEY_NUMERIC_2 पूर्ण,
	अणु 0x0003, KEY_NUMERIC_3 पूर्ण,
	अणु 0x0004, KEY_NUMERIC_4 पूर्ण,
	अणु 0x0005, KEY_NUMERIC_5 पूर्ण,
	अणु 0x0006, KEY_NUMERIC_6 पूर्ण,
	अणु 0x0007, KEY_NUMERIC_7 पूर्ण,
	अणु 0x0008, KEY_NUMERIC_8 पूर्ण,
	अणु 0x0009, KEY_NUMERIC_9 पूर्ण,
	अणु 0x000a, KEY_MUTE पूर्ण,
	अणु 0x000b, KEY_STOP पूर्ण,                   /* Stop */
	अणु 0x000c, KEY_POWER2 पूर्ण,                 /* Turn on/off application */
	अणु 0x000d, KEY_OK पूर्ण,                     /* OK */
	अणु 0x000e, KEY_CAMERA पूर्ण,                 /* Snapshot */
	अणु 0x000f, KEY_ZOOM पूर्ण,                   /* Full Screen/Restore */
	अणु 0x0010, KEY_RIGHT पूर्ण,                  /* Right arrow */
	अणु 0x0011, KEY_LEFT पूर्ण,                   /* Left arrow */
	अणु 0x0012, KEY_CHANNELUP पूर्ण,
	अणु 0x0013, KEY_CHANNELDOWN पूर्ण,
	अणु 0x0014, KEY_SHUFFLE पूर्ण,
	अणु 0x0016, KEY_PAUSE पूर्ण,
	अणु 0x0017, KEY_PLAY पूर्ण,                   /* Play */
	अणु 0x001e, KEY_TIME पूर्ण,                   /* Time Shअगरt */
	अणु 0x001f, KEY_RECORD पूर्ण,
	अणु 0x0020, KEY_UP पूर्ण,
	अणु 0x0021, KEY_DOWN पूर्ण,
	अणु 0x0025, KEY_POWER पूर्ण,                  /* Turn off computer */
	अणु 0x0026, KEY_REWIND पूर्ण,                 /* FR << */
	अणु 0x0027, KEY_FASTFORWARD पूर्ण,            /* FF >> */
	अणु 0x0029, KEY_ESC पूर्ण,
	अणु 0x002b, KEY_VOLUMEUP पूर्ण,
	अणु 0x002c, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x002d, KEY_CHANNEL पूर्ण,                /* CH Surfing */
	अणु 0x0038, KEY_VIDEO पूर्ण,                  /* TV/AV/S-Video/YPbPr */
पूर्ण;

अटल काष्ठा rc_map_list total_media_in_hand_02_map = अणु
	.map = अणु
		.scan     = total_media_in_hand_02,
		.size     = ARRAY_SIZE(total_media_in_hand_02),
		.rc_proto = RC_PROTO_RC5,
		.name     = RC_MAP_TOTAL_MEDIA_IN_HAND_02,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_total_media_in_hand_02(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&total_media_in_hand_02_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_total_media_in_hand_02(व्योम)
अणु
	rc_map_unरेजिस्टर(&total_media_in_hand_02_map);
पूर्ण

module_init(init_rc_map_total_media_in_hand_02)
module_निकास(निकास_rc_map_total_media_in_hand_02)

MODULE_LICENSE("GPL");
MODULE_AUTHOR(" Alfredo J. Delaiti <alfredodelaiti@netscape.net>");
