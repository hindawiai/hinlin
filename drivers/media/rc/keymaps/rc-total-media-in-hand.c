<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Total Media In Hand remote controller keytable
 *
 * Copyright (C) 2010 Antti Palosaari <crope@iki.fi>
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* Uses NEC extended 0x02bd */
अटल काष्ठा rc_map_table total_media_in_hand[] = अणु
	अणु 0x02bd00, KEY_NUMERIC_1 पूर्ण,
	अणु 0x02bd01, KEY_NUMERIC_2 पूर्ण,
	अणु 0x02bd02, KEY_NUMERIC_3 पूर्ण,
	अणु 0x02bd03, KEY_NUMERIC_4 पूर्ण,
	अणु 0x02bd04, KEY_NUMERIC_5 पूर्ण,
	अणु 0x02bd05, KEY_NUMERIC_6 पूर्ण,
	अणु 0x02bd06, KEY_NUMERIC_7 पूर्ण,
	अणु 0x02bd07, KEY_NUMERIC_8 पूर्ण,
	अणु 0x02bd08, KEY_NUMERIC_9 पूर्ण,
	अणु 0x02bd09, KEY_NUMERIC_0 पूर्ण,
	अणु 0x02bd0a, KEY_MUTE पूर्ण,
	अणु 0x02bd0b, KEY_CYCLEWINDOWS पूर्ण,    /* yellow, [min / max] */
	अणु 0x02bd0c, KEY_VIDEO पूर्ण,           /* TV / AV */
	अणु 0x02bd0e, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x02bd0f, KEY_TIME पूर्ण,            /* TimeShअगरt */
	अणु 0x02bd10, KEY_RIGHT पूर्ण,           /* right arrow */
	अणु 0x02bd11, KEY_LEFT पूर्ण,            /* left arrow */
	अणु 0x02bd12, KEY_UP पूर्ण,              /* up arrow */
	अणु 0x02bd13, KEY_DOWN पूर्ण,            /* करोwn arrow */
	अणु 0x02bd14, KEY_POWER2 पूर्ण,          /* [red] */
	अणु 0x02bd15, KEY_OK पूर्ण,              /* OK */
	अणु 0x02bd16, KEY_STOP पूर्ण,
	अणु 0x02bd17, KEY_CAMERA पूर्ण,          /* Snapshot */
	अणु 0x02bd18, KEY_CHANNELUP पूर्ण,
	अणु 0x02bd19, KEY_RECORD पूर्ण,
	अणु 0x02bd1a, KEY_CHANNELDOWN पूर्ण,
	अणु 0x02bd1c, KEY_ESC पूर्ण,             /* Esc */
	अणु 0x02bd1e, KEY_PLAY पूर्ण,
	अणु 0x02bd1f, KEY_VOLUMEUP पूर्ण,
	अणु 0x02bd40, KEY_PAUSE पूर्ण,
	अणु 0x02bd41, KEY_FASTFORWARD पूर्ण,     /* FF >> */
	अणु 0x02bd42, KEY_REWIND पूर्ण,          /* FR << */
	अणु 0x02bd43, KEY_ZOOM पूर्ण,            /* [winकरोw + mouse poपूर्णांकer] */
	अणु 0x02bd44, KEY_SHUFFLE पूर्ण,         /* Shuffle */
	अणु 0x02bd45, KEY_INFO पूर्ण,            /* [red (I)] */
पूर्ण;

अटल काष्ठा rc_map_list total_media_in_hand_map = अणु
	.map = अणु
		.scan     = total_media_in_hand,
		.size     = ARRAY_SIZE(total_media_in_hand),
		.rc_proto = RC_PROTO_NECX,
		.name     = RC_MAP_TOTAL_MEDIA_IN_HAND,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_total_media_in_hand(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&total_media_in_hand_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_total_media_in_hand(व्योम)
अणु
	rc_map_unरेजिस्टर(&total_media_in_hand_map);
पूर्ण

module_init(init_rc_map_total_media_in_hand)
module_निकास(निकास_rc_map_total_media_in_hand)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
