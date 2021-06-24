<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Keytable क्रम the CEC remote control
 *
 * This keymap is unusual in that it can't be built as a module,
 * instead it is रेजिस्टरed directly in rc-मुख्य.c अगर CONFIG_MEDIA_CEC_RC
 * is set. This is because it can be called from drm_dp_cec_set_edid() via
 * cec_रेजिस्टर_adapter() in an asynchronous context, and it is not
 * allowed to use request_module() to load rc-cec.ko in that हाल.
 *
 * Since this keymap is only used अगर CONFIG_MEDIA_CEC_RC is set, we
 * just compile this keymap पूर्णांकo the rc-core module and never as a
 * separate module.
 *
 * Copyright (c) 2015 by Kamil Debski
 */

#समावेश <media/rc-map.h>
#समावेश <linux/module.h>

/*
 * CEC Spec "High-Definition Multimedia Interface Specification" can be obtained
 * here: http://xtreamerdev.googlecode.com/files/CEC_Specs.pdf
 * The list of control codes is listed in Table 27: User Control Codes p. 95
 */

अटल काष्ठा rc_map_table cec[] = अणु
	अणु 0x00, KEY_OK पूर्ण,
	अणु 0x01, KEY_UP पूर्ण,
	अणु 0x02, KEY_DOWN पूर्ण,
	अणु 0x03, KEY_LEFT पूर्ण,
	अणु 0x04, KEY_RIGHT पूर्ण,
	अणु 0x05, KEY_RIGHT_UP पूर्ण,
	अणु 0x06, KEY_RIGHT_DOWN पूर्ण,
	अणु 0x07, KEY_LEFT_UP पूर्ण,
	अणु 0x08, KEY_LEFT_DOWN पूर्ण,
	अणु 0x09, KEY_ROOT_MENU पूर्ण, /* CEC Spec: Device Root Menu - see Note 2 */
	/*
	 * Note 2: This is the initial display that a device shows. It is
	 * device-dependent and can be, क्रम example, a contents menu, setup
	 * menu, favorite menu or other menu. The actual menu displayed
	 * may also depend on the device's current state.
	 */
	अणु 0x0a, KEY_SETUP पूर्ण,
	अणु 0x0b, KEY_MENU पूर्ण, /* CEC Spec: Contents Menu */
	अणु 0x0c, KEY_FAVORITES पूर्ण, /* CEC Spec: Favorite Menu */
	अणु 0x0d, KEY_EXIT पूर्ण,
	/* 0x0e-0x0f: Reserved */
	अणु 0x10, KEY_MEDIA_TOP_MENU पूर्ण,
	अणु 0x11, KEY_CONTEXT_MENU पूर्ण,
	/* 0x12-0x1c: Reserved */
	अणु 0x1d, KEY_DIGITS पूर्ण, /* CEC Spec: select/toggle a Number Entry Mode */
	अणु 0x1e, KEY_NUMERIC_11 पूर्ण,
	अणु 0x1f, KEY_NUMERIC_12 पूर्ण,
	/* 0x20-0x29: Keys 0 to 9 */
	अणु 0x20, KEY_NUMERIC_0 पूर्ण,
	अणु 0x21, KEY_NUMERIC_1 पूर्ण,
	अणु 0x22, KEY_NUMERIC_2 पूर्ण,
	अणु 0x23, KEY_NUMERIC_3 पूर्ण,
	अणु 0x24, KEY_NUMERIC_4 पूर्ण,
	अणु 0x25, KEY_NUMERIC_5 पूर्ण,
	अणु 0x26, KEY_NUMERIC_6 पूर्ण,
	अणु 0x27, KEY_NUMERIC_7 पूर्ण,
	अणु 0x28, KEY_NUMERIC_8 पूर्ण,
	अणु 0x29, KEY_NUMERIC_9 पूर्ण,
	अणु 0x2a, KEY_DOT पूर्ण,
	अणु 0x2b, KEY_ENTER पूर्ण,
	अणु 0x2c, KEY_CLEAR पूर्ण,
	/* 0x2d-0x2e: Reserved */
	अणु 0x2f, KEY_NEXT_FAVORITE पूर्ण, /* CEC Spec: Next Favorite */
	अणु 0x30, KEY_CHANNELUP पूर्ण,
	अणु 0x31, KEY_CHANNELDOWN पूर्ण,
	अणु 0x32, KEY_PREVIOUS पूर्ण, /* CEC Spec: Previous Channel */
	अणु 0x33, KEY_SOUND पूर्ण, /* CEC Spec: Sound Select */
	अणु 0x34, KEY_VIDEO पूर्ण, /* 0x34: CEC Spec: Input Select */
	अणु 0x35, KEY_INFO पूर्ण, /* CEC Spec: Display Inक्रमmation */
	अणु 0x36, KEY_HELP पूर्ण,
	अणु 0x37, KEY_PAGEUP पूर्ण,
	अणु 0x38, KEY_PAGEDOWN पूर्ण,
	/* 0x39-0x3f: Reserved */
	अणु 0x40, KEY_POWER पूर्ण,
	अणु 0x41, KEY_VOLUMEUP पूर्ण,
	अणु 0x42, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x43, KEY_MUTE पूर्ण,
	अणु 0x44, KEY_PLAYCD पूर्ण,
	अणु 0x45, KEY_STOPCD पूर्ण,
	अणु 0x46, KEY_PAUSECD पूर्ण,
	अणु 0x47, KEY_RECORD पूर्ण,
	अणु 0x48, KEY_REWIND पूर्ण,
	अणु 0x49, KEY_FASTFORWARD पूर्ण,
	अणु 0x4a, KEY_EJECTCD पूर्ण, /* CEC Spec: Eject */
	अणु 0x4b, KEY_FORWARD पूर्ण,
	अणु 0x4c, KEY_BACK पूर्ण,
	अणु 0x4d, KEY_STOP_RECORD पूर्ण, /* CEC Spec: Stop-Record */
	अणु 0x4e, KEY_PAUSE_RECORD पूर्ण, /* CEC Spec: Pause-Record */
	/* 0x4f: Reserved */
	अणु 0x50, KEY_ANGLE पूर्ण,
	अणु 0x51, KEY_TV2 पूर्ण,
	अणु 0x52, KEY_VOD पूर्ण, /* CEC Spec: Video on Demand */
	अणु 0x53, KEY_EPG पूर्ण,
	अणु 0x54, KEY_TIME पूर्ण, /* CEC Spec: Timer */
	अणु 0x55, KEY_CONFIG पूर्ण,
	/*
	 * The following codes are hard to implement at this moment, as they
	 * carry an additional additional argument. Most likely changes to RC
	 * framework are necessary.
	 * For now they are पूर्णांकerpreted by the CEC framework as non keycodes
	 * and are passed as messages enabling user application to parse them.
	 */
	/* 0x56: CEC Spec: Select Broadcast Type */
	/* 0x57: CEC Spec: Select Sound presentation */
	अणु 0x58, KEY_AUDIO_DESC पूर्ण, /* CEC 2.0 and up */
	अणु 0x59, KEY_WWW पूर्ण, /* CEC 2.0 and up */
	अणु 0x5a, KEY_3D_MODE पूर्ण, /* CEC 2.0 and up */
	/* 0x5b-0x5f: Reserved */
	अणु 0x60, KEY_PLAYCD पूर्ण, /* CEC Spec: Play Function */
	अणु 0x6005, KEY_FASTFORWARD पूर्ण,
	अणु 0x6006, KEY_FASTFORWARD पूर्ण,
	अणु 0x6007, KEY_FASTFORWARD पूर्ण,
	अणु 0x6015, KEY_SLOW पूर्ण,
	अणु 0x6016, KEY_SLOW पूर्ण,
	अणु 0x6017, KEY_SLOW पूर्ण,
	अणु 0x6009, KEY_FASTREVERSE पूर्ण,
	अणु 0x600a, KEY_FASTREVERSE पूर्ण,
	अणु 0x600b, KEY_FASTREVERSE पूर्ण,
	अणु 0x6019, KEY_SLOWREVERSE पूर्ण,
	अणु 0x601a, KEY_SLOWREVERSE पूर्ण,
	अणु 0x601b, KEY_SLOWREVERSE पूर्ण,
	अणु 0x6020, KEY_REWIND पूर्ण,
	अणु 0x6024, KEY_PLAYCD पूर्ण,
	अणु 0x6025, KEY_PAUSECD पूर्ण,
	अणु 0x61, KEY_PLAYPAUSE पूर्ण, /* CEC Spec: Pause-Play Function */
	अणु 0x62, KEY_RECORD पूर्ण, /* Spec: Record Function */
	अणु 0x63, KEY_PAUSE_RECORD पूर्ण, /* CEC Spec: Pause-Record Function */
	अणु 0x64, KEY_STOPCD पूर्ण, /* CEC Spec: Stop Function */
	अणु 0x65, KEY_MUTE पूर्ण, /* CEC Spec: Mute Function */
	अणु 0x66, KEY_UNMUTE पूर्ण, /* CEC Spec: Restore the volume */
	/*
	 * The following codes are hard to implement at this moment, as they
	 * carry an additional additional argument. Most likely changes to RC
	 * framework are necessary.
	 * For now they are पूर्णांकerpreted by the CEC framework as non keycodes
	 * and are passed as messages enabling user application to parse them.
	 */
	/* 0x67: CEC Spec: Tune Function */
	/* 0x68: CEC Spec: Seleect Media Function */
	/* 0x69: CEC Spec: Select A/V Input Function */
	/* 0x6a: CEC Spec: Select Audio Input Function */
	अणु 0x6b, KEY_POWER पूर्ण, /* CEC Spec: Power Toggle Function */
	अणु 0x6c, KEY_SLEEP पूर्ण, /* CEC Spec: Power Off Function */
	अणु 0x6d, KEY_WAKEUP पूर्ण, /* CEC Spec: Power On Function */
	/* 0x6e-0x70: Reserved */
	अणु 0x71, KEY_BLUE पूर्ण, /* CEC Spec: F1 (Blue) */
	अणु 0x72, KEY_RED पूर्ण, /* CEC Spec: F2 (Red) */
	अणु 0x73, KEY_GREEN पूर्ण, /* CEC Spec: F3 (Green) */
	अणु 0x74, KEY_YELLOW पूर्ण, /* CEC Spec: F4 (Yellow) */
	अणु 0x75, KEY_F5 पूर्ण,
	अणु 0x76, KEY_DATA पूर्ण, /* CEC Spec: Data - see Note 3 */
	/*
	 * Note 3: This is used, क्रम example, to enter or leave a digital TV
	 * data broadcast application.
	 */
	/* 0x77-0xff: Reserved */
पूर्ण;

काष्ठा rc_map_list cec_map = अणु
	.map = अणु
		.scan		= cec,
		.size		= ARRAY_SIZE(cec),
		.rc_proto	= RC_PROTO_CEC,
		.name		= RC_MAP_CEC,
	पूर्ण
पूर्ण;
