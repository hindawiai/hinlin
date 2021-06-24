<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// dntv-live-dvbt-pro.h - Keytable क्रम dntv_live_dvbt_pro Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* DigitalNow DNTV Live! DVB-T Pro Remote */

अटल काष्ठा rc_map_table dntv_live_dvbt_pro[] = अणु
	अणु 0x16, KEY_POWER पूर्ण,
	अणु 0x5b, KEY_HOME पूर्ण,

	अणु 0x55, KEY_TV पूर्ण,		/* live tv */
	अणु 0x58, KEY_TUNER पूर्ण,		/* digital Radio */
	अणु 0x5a, KEY_RADIO पूर्ण,		/* FM radio */
	अणु 0x59, KEY_DVD पूर्ण,		/* dvd menu */
	अणु 0x03, KEY_NUMERIC_1 पूर्ण,
	अणु 0x01, KEY_NUMERIC_2 पूर्ण,
	अणु 0x06, KEY_NUMERIC_3 पूर्ण,
	अणु 0x09, KEY_NUMERIC_4 पूर्ण,
	अणु 0x1d, KEY_NUMERIC_5 पूर्ण,
	अणु 0x1f, KEY_NUMERIC_6 पूर्ण,
	अणु 0x0d, KEY_NUMERIC_7 पूर्ण,
	अणु 0x19, KEY_NUMERIC_8 पूर्ण,
	अणु 0x1b, KEY_NUMERIC_9 पूर्ण,
	अणु 0x0c, KEY_CANCEL पूर्ण,
	अणु 0x15, KEY_NUMERIC_0 पूर्ण,
	अणु 0x4a, KEY_CLEAR पूर्ण,
	अणु 0x13, KEY_BACK पूर्ण,
	अणु 0x00, KEY_TAB पूर्ण,
	अणु 0x4b, KEY_UP पूर्ण,
	अणु 0x4e, KEY_LEFT पूर्ण,
	अणु 0x4f, KEY_OK पूर्ण,
	अणु 0x52, KEY_RIGHT पूर्ण,
	अणु 0x51, KEY_DOWN पूर्ण,
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
	अणु 0x41, KEY_PREVIOUSSONG पूर्ण,	/* replay |< */
	अणु 0x42, KEY_NEXTSONG पूर्ण,		/* skip >| */
	अणु 0x54, KEY_CAMERA पूर्ण,		/* capture */
	अणु 0x50, KEY_LANGUAGE पूर्ण,		/* sap */
	अणु 0x47, KEY_TV2 पूर्ण,		/* pip */
	अणु 0x4d, KEY_SCREEN पूर्ण,
	अणु 0x43, KEY_SUBTITLE पूर्ण,
	अणु 0x10, KEY_MUTE पूर्ण,
	अणु 0x49, KEY_AUDIO पूर्ण,		/* l/r */
	अणु 0x07, KEY_SLEEP पूर्ण,
	अणु 0x08, KEY_VIDEO पूर्ण,		/* a/v */
	अणु 0x0e, KEY_PREVIOUS पूर्ण,		/* recall */
	अणु 0x45, KEY_ZOOM पूर्ण,		/* zoom + */
	अणु 0x46, KEY_ANGLE पूर्ण,		/* zoom - */
	अणु 0x56, KEY_RED पूर्ण,
	अणु 0x57, KEY_GREEN पूर्ण,
	अणु 0x5c, KEY_YELLOW पूर्ण,
	अणु 0x5d, KEY_BLUE पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list dntv_live_dvbt_pro_map = अणु
	.map = अणु
		.scan     = dntv_live_dvbt_pro,
		.size     = ARRAY_SIZE(dntv_live_dvbt_pro),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_DNTV_LIVE_DVBT_PRO,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_dntv_live_dvbt_pro(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&dntv_live_dvbt_pro_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_dntv_live_dvbt_pro(व्योम)
अणु
	rc_map_unरेजिस्टर(&dntv_live_dvbt_pro_map);
पूर्ण

module_init(init_rc_map_dntv_live_dvbt_pro)
module_निकास(निकास_rc_map_dntv_live_dvbt_pro)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
