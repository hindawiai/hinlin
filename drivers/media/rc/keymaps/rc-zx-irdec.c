<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Sanechips Technology Co., Ltd.
 * Copyright 2017 Linaro Ltd.
 */

#समावेश <linux/module.h>
#समावेश <media/rc-map.h>

अटल काष्ठा rc_map_table zx_irdec_table[] = अणु
	अणु 0x01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x03, KEY_NUMERIC_3 पूर्ण,
	अणु 0x04, KEY_NUMERIC_4 पूर्ण,
	अणु 0x05, KEY_NUMERIC_5 पूर्ण,
	अणु 0x06, KEY_NUMERIC_6 पूर्ण,
	अणु 0x07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x09, KEY_NUMERIC_9 पूर्ण,
	अणु 0x31, KEY_NUMERIC_0 पूर्ण,
	अणु 0x16, KEY_DELETE पूर्ण,
	अणु 0x0a, KEY_MODE पूर्ण,		/* Input method */
	अणु 0x0c, KEY_VOLUMEUP पूर्ण,
	अणु 0x18, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x0b, KEY_CHANNELUP पूर्ण,
	अणु 0x15, KEY_CHANNELDOWN पूर्ण,
	अणु 0x0d, KEY_PAGEUP पूर्ण,
	अणु 0x13, KEY_PAGEDOWN पूर्ण,
	अणु 0x46, KEY_FASTFORWARD पूर्ण,
	अणु 0x43, KEY_REWIND पूर्ण,
	अणु 0x44, KEY_PLAYPAUSE पूर्ण,
	अणु 0x45, KEY_STOP पूर्ण,
	अणु 0x49, KEY_OK पूर्ण,
	अणु 0x47, KEY_UP पूर्ण,
	अणु 0x4b, KEY_DOWN पूर्ण,
	अणु 0x48, KEY_LEFT पूर्ण,
	अणु 0x4a, KEY_RIGHT पूर्ण,
	अणु 0x4d, KEY_MENU पूर्ण,
	अणु 0x56, KEY_APPSELECT पूर्ण,	/* Application */
	अणु 0x4c, KEY_BACK पूर्ण,
	अणु 0x1e, KEY_INFO पूर्ण,
	अणु 0x4e, KEY_F1 पूर्ण,
	अणु 0x4f, KEY_F2 पूर्ण,
	अणु 0x50, KEY_F3 पूर्ण,
	अणु 0x51, KEY_F4 पूर्ण,
	अणु 0x1c, KEY_AUDIO पूर्ण,
	अणु 0x12, KEY_MUTE पूर्ण,
	अणु 0x11, KEY_DOT पूर्ण,		/* Location */
	अणु 0x1d, KEY_SETUP पूर्ण,
	अणु 0x40, KEY_POWER पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list zx_irdec_map = अणु
	.map = अणु
		.scan = zx_irdec_table,
		.size = ARRAY_SIZE(zx_irdec_table),
		.rc_proto = RC_PROTO_NEC,
		.name = RC_MAP_ZX_IRDEC,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_zx_irdec(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&zx_irdec_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_zx_irdec(व्योम)
अणु
	rc_map_unरेजिस्टर(&zx_irdec_map);
पूर्ण

module_init(init_rc_map_zx_irdec)
module_निकास(निकास_rc_map_zx_irdec)

MODULE_AUTHOR("Shawn Guo <shawn.guo@linaro.org>");
MODULE_LICENSE("GPL v2");
