<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// dntv-live-dvb-t.h - Keytable क्रम dntv_live_dvb_t Remote Controller
//
// keymap imported from ir-keymaps.c
//
// Copyright (c) 2010 by Mauro Carvalho Chehab

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/* DigitalNow DNTV Live DVB-T Remote */

अटल काष्ठा rc_map_table dntv_live_dvb_t[] = अणु
	अणु 0x00, KEY_ESC पूर्ण,		/* 'go up a level?' */
	/* Keys 0 to 9 */
	अणु 0x0a, KEY_NUMERIC_0 पूर्ण,
	अणु 0x01, KEY_NUMERIC_1 पूर्ण,
	अणु 0x02, KEY_NUMERIC_2 पूर्ण,
	अणु 0x03, KEY_NUMERIC_3 पूर्ण,
	अणु 0x04, KEY_NUMERIC_4 पूर्ण,
	अणु 0x05, KEY_NUMERIC_5 पूर्ण,
	अणु 0x06, KEY_NUMERIC_6 पूर्ण,
	अणु 0x07, KEY_NUMERIC_7 पूर्ण,
	अणु 0x08, KEY_NUMERIC_8 पूर्ण,
	अणु 0x09, KEY_NUMERIC_9 पूर्ण,

	अणु 0x0b, KEY_TUNER पूर्ण,		/* tv/fm */
	अणु 0x0c, KEY_SEARCH पूर्ण,		/* scan */
	अणु 0x0d, KEY_STOP पूर्ण,
	अणु 0x0e, KEY_PAUSE पूर्ण,
	अणु 0x0f, KEY_VIDEO पूर्ण,		/* source */

	अणु 0x10, KEY_MUTE पूर्ण,
	अणु 0x11, KEY_REWIND पूर्ण,		/* backward << */
	अणु 0x12, KEY_POWER पूर्ण,
	अणु 0x13, KEY_CAMERA पूर्ण,		/* snap */
	अणु 0x14, KEY_AUDIO पूर्ण,		/* stereo */
	अणु 0x15, KEY_CLEAR पूर्ण,		/* reset */
	अणु 0x16, KEY_PLAY पूर्ण,
	अणु 0x17, KEY_ENTER पूर्ण,
	अणु 0x18, KEY_ZOOM पूर्ण,		/* full screen */
	अणु 0x19, KEY_FASTFORWARD पूर्ण,	/* क्रमward >> */
	अणु 0x1a, KEY_CHANNELUP पूर्ण,
	अणु 0x1b, KEY_VOLUMEUP पूर्ण,
	अणु 0x1c, KEY_INFO पूर्ण,		/* preview */
	अणु 0x1d, KEY_RECORD पूर्ण,		/* record */
	अणु 0x1e, KEY_CHANNELDOWN पूर्ण,
	अणु 0x1f, KEY_VOLUMEDOWN पूर्ण,
पूर्ण;

अटल काष्ठा rc_map_list dntv_live_dvb_t_map = अणु
	.map = अणु
		.scan     = dntv_live_dvb_t,
		.size     = ARRAY_SIZE(dntv_live_dvb_t),
		.rc_proto = RC_PROTO_UNKNOWN,	/* Legacy IR type */
		.name     = RC_MAP_DNTV_LIVE_DVB_T,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_dntv_live_dvb_t(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&dntv_live_dvb_t_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_dntv_live_dvb_t(व्योम)
अणु
	rc_map_unरेजिस्टर(&dntv_live_dvb_t_map);
पूर्ण

module_init(init_rc_map_dntv_live_dvb_t)
module_निकास(निकास_rc_map_dntv_live_dvb_t)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mauro Carvalho Chehab");
