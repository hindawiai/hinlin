<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

अटल काष्ठा rc_map_table twinhan_vp1027[] = अणु
	अणु 0x16, KEY_POWER2 पूर्ण,
	अणु 0x17, KEY_FAVORITES पूर्ण,
	अणु 0x0f, KEY_TEXT पूर्ण,
	अणु 0x48, KEY_INFOपूर्ण,
	अणु 0x1c, KEY_EPG पूर्ण,
	अणु 0x04, KEY_LIST पूर्ण,

	अणु 0x03, KEY_NUMERIC_1 पूर्ण,
	अणु 0x01, KEY_NUMERIC_2 पूर्ण,
	अणु 0x06, KEY_NUMERIC_3 पूर्ण,
	अणु 0x09, KEY_NUMERIC_4 पूर्ण,
	अणु 0x1d, KEY_NUMERIC_5 पूर्ण,
	अणु 0x1f, KEY_NUMERIC_6 पूर्ण,
	अणु 0x0d, KEY_NUMERIC_7 पूर्ण,
	अणु 0x19, KEY_NUMERIC_8 पूर्ण,
	अणु 0x1b, KEY_NUMERIC_9 पूर्ण,
	अणु 0x15, KEY_NUMERIC_0 पूर्ण,

	अणु 0x0c, KEY_CANCEL पूर्ण,
	अणु 0x4a, KEY_CLEAR पूर्ण,
	अणु 0x13, KEY_BACKSPACE पूर्ण,
	अणु 0x00, KEY_TAB पूर्ण,

	अणु 0x4b, KEY_UP पूर्ण,
	अणु 0x51, KEY_DOWN पूर्ण,
	अणु 0x4e, KEY_LEFT पूर्ण,
	अणु 0x52, KEY_RIGHT पूर्ण,
	अणु 0x4f, KEY_ENTER पूर्ण,

	अणु 0x1e, KEY_VOLUMEUP पूर्ण,
	अणु 0x0a, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x02, KEY_CHANNELDOWN पूर्ण,
	अणु 0x05, KEY_CHANNELUP पूर्ण,
	अणु 0x11, KEY_RECORD पूर्ण,

	अणु 0x14, KEY_PLAY पूर्ण,
	अणु 0x4c, KEY_PAUSE पूर्ण,
	अणु 0x1a, KEY_STOP पूर्ण,
	अणु 0x40, KEY_REWIND पूर्ण,
	अणु 0x12, KEY_FASTFORWARD पूर्ण,
	अणु 0x41, KEY_PREVIOUSSONG पूर्ण,
	अणु 0x42, KEY_NEXTSONG पूर्ण,
	अणु 0x54, KEY_SAVE पूर्ण,
	अणु 0x50, KEY_LANGUAGE पूर्ण,
	अणु 0x47, KEY_MEDIA पूर्ण,
	अणु 0x4d, KEY_SCREEN पूर्ण,
	अणु 0x43, KEY_SUBTITLE पूर्ण,
	अणु 0x10, KEY_MUTE पूर्ण,
	अणु 0x49, KEY_AUDIO पूर्ण,
	अणु 0x07, KEY_SLEEP पूर्ण,
	अणु 0x08, KEY_VIDEO पूर्ण,
	अणु 0x0e, KEY_AGAIN पूर्ण,
	अणु 0x45, KEY_EQUAL पूर्ण,
	अणु 0x46, KEY_MINUS पूर्ण,
	अणु 0x18, KEY_RED पूर्ण,
	अणु 0x53, KEY_GREEN पूर्ण,
	अणु 0x5e, KEY_YELLOW पूर्ण,
	अणु 0x5f, KEY_BLUE पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list twinhan_vp1027_map = अणु
	.map = अणु
		.scan     = twinhan_vp1027,
		.size     = ARRAY_SIZE(twinhan_vp1027),
		.rc_proto = RC_PROTO_NEC,
		.name     = RC_MAP_TWINHAN_VP1027_DVBS,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_twinhan_vp1027(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&twinhan_vp1027_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_twinhan_vp1027(व्योम)
अणु
	rc_map_unरेजिस्टर(&twinhan_vp1027_map);
पूर्ण

module_init(init_rc_map_twinhan_vp1027)
module_निकास(निकास_rc_map_twinhan_vp1027)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sergey Ivanov <123kash@gmail.com>");
