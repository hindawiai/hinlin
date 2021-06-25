<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (C) 2018 Sean Young <sean@mess.org>

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

//
// Note that this remote has a stick which its own IR protocol,
// with 16 directions. This is supported by the imon_rsc BPF decoder
// in v4l-utils.
//
अटल काष्ठा rc_map_table imon_rsc[] = अणु
	अणु 0x801010, KEY_EXIT पूर्ण,
	अणु 0x80102f, KEY_POWER पूर्ण,
	अणु 0x80104a, KEY_SCREENSAVER पूर्ण,	/* Screensaver */
	अणु 0x801049, KEY_TIME पूर्ण,		/* Timer */
	अणु 0x801054, KEY_NUMERIC_1 पूर्ण,
	अणु 0x801055, KEY_NUMERIC_2 पूर्ण,
	अणु 0x801056, KEY_NUMERIC_3 पूर्ण,
	अणु 0x801057, KEY_NUMERIC_4 पूर्ण,
	अणु 0x801058, KEY_NUMERIC_5 पूर्ण,
	अणु 0x801059, KEY_NUMERIC_6 पूर्ण,
	अणु 0x80105a, KEY_NUMERIC_7 पूर्ण,
	अणु 0x80105b, KEY_NUMERIC_8 पूर्ण,
	अणु 0x80105c, KEY_NUMERIC_9 पूर्ण,
	अणु 0x801081, KEY_SCREEN पूर्ण,	/* Desktop */
	अणु 0x80105d, KEY_NUMERIC_0 पूर्ण,
	अणु 0x801082, KEY_ZOOM पूर्ण,		/* Maximise */
	अणु 0x801048, KEY_ESC पूर्ण,
	अणु 0x80104b, KEY_MEDIA पूर्ण,	/* Winकरोws key */
	अणु 0x801083, KEY_MENU पूर्ण,
	अणु 0x801045, KEY_APPSELECT पूर्ण,	/* app launcher */
	अणु 0x801084, KEY_STOP पूर्ण,
	अणु 0x801046, KEY_CYCLEWINDOWS पूर्ण,
	अणु 0x801085, KEY_BACKSPACE पूर्ण,
	अणु 0x801086, KEY_KEYBOARD पूर्ण,
	अणु 0x801087, KEY_SPACE पूर्ण,
	अणु 0x80101e, KEY_RESERVED पूर्ण,	/* shअगरt tab */
	अणु 0x801098, BTN_0 पूर्ण,
	अणु 0x80101f, KEY_TAB पूर्ण,
	अणु 0x80101b, BTN_LEFT पूर्ण,
	अणु 0x80101d, BTN_RIGHT पूर्ण,
	अणु 0x801016, BTN_MIDDLE पूर्ण,	/* drag and drop */
	अणु 0x801088, KEY_MUTE पूर्ण,
	अणु 0x80105e, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x80105f, KEY_VOLUMEUP पूर्ण,
	अणु 0x80104c, KEY_PLAY पूर्ण,
	अणु 0x80104d, KEY_PAUSE पूर्ण,
	अणु 0x80104f, KEY_EJECTCD पूर्ण,
	अणु 0x801050, KEY_PREVIOUS पूर्ण,
	अणु 0x801051, KEY_NEXT पूर्ण,
	अणु 0x80104e, KEY_STOP पूर्ण,
	अणु 0x801052, KEY_REWIND पूर्ण,
	अणु 0x801053, KEY_FASTFORWARD पूर्ण,
	अणु 0x801089, KEY_FULL_SCREEN पूर्ण	/* full screen */
पूर्ण;

अटल काष्ठा rc_map_list imon_rsc_map = अणु
	.map = अणु
		.scan     = imon_rsc,
		.size     = ARRAY_SIZE(imon_rsc),
		.rc_proto = RC_PROTO_NECX,
		.name     = RC_MAP_IMON_RSC,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init init_rc_map_imon_rsc(व्योम)
अणु
	वापस rc_map_रेजिस्टर(&imon_rsc_map);
पूर्ण

अटल व्योम __निकास निकास_rc_map_imon_rsc(व्योम)
अणु
	rc_map_unरेजिस्टर(&imon_rsc_map);
पूर्ण

module_init(init_rc_map_imon_rsc)
module_निकास(निकास_rc_map_imon_rsc)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sean Young <sean@mess.org>");
