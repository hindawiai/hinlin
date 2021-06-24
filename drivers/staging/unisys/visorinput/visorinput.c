<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2011 - 2015 UNISYS CORPORATION
 * All rights reserved.
 */

/*
 * This driver lives in a generic guest Linux partition, and रेजिस्टरs to
 * receive keyboard and mouse channels from the visorbus driver.  It पढ़ोs
 * inमाला_दो from such channels, and delivers it to the Linux OS in the
 * standard way the Linux expects क्रम input drivers.
 */

#समावेश <linux/fb.h>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/uuid.h>
#समावेश <linux/visorbus.h>

/* These defines identअगरy mouse and keyboard activity which is specअगरied by the
 * firmware to the host using the cmsimpleinput protocol.  @ingroup coretypes
 */
/* only motion; arg1=x, arg2=y */
#घोषणा INPUTACTION_XY_MOTION 1

/* arg1: 1=left,2=center,3=right */
#घोषणा INPUTACTION_MOUSE_BUTTON_DOWN 2
#घोषणा INPUTACTION_MOUSE_BUTTON_UP 3
#घोषणा INPUTACTION_MOUSE_BUTTON_CLICK 4
#घोषणा INPUTACTION_MOUSE_BUTTON_DCLICK 5

/* arg1: wheel rotation away from/toward user */
#घोषणा INPUTACTION_WHEEL_ROTATE_AWAY 6
#घोषणा INPUTACTION_WHEEL_ROTATE_TOWARD 7

/* arg1: scancode, as follows: If arg1 <= 0xff, it's a 1-byte scancode and arg1
 *	 is that scancode. If arg1 > 0xff, it's a 2-byte scanecode, with the 1st
 *	 byte in the low 8 bits, and the 2nd byte in the high 8 bits.
 *	 E.g., the right ALT key would appear as x'38e0'.
 */
#घोषणा INPUTACTION_KEY_DOWN 64
#घोषणा INPUTACTION_KEY_UP 65
#घोषणा INPUTACTION_KEY_DOWN_UP 67

/* arg1: scancode (in same क्रमmat as inputaction_keyDown); MUST refer to one of
 *	 the locking keys, like capslock, numlock, or scrolllock.
 * arg2: 1 अगरf locking key should be in the LOCKED position (e.g., light is ON)
 */
#घोषणा INPUTACTION_SET_LOCKING_KEY_STATE 66

/* Keyboard channel अणुc73416d0-b0b8-44af-b304-9d2ae99f1b3dपूर्ण */
#घोषणा VISOR_KEYBOARD_CHANNEL_GUID \
	GUID_INIT(0xc73416d0, 0xb0b8, 0x44af, \
		  0xb3, 0x4, 0x9d, 0x2a, 0xe9, 0x9f, 0x1b, 0x3d)
#घोषणा VISOR_KEYBOARD_CHANNEL_GUID_STR "c73416d0-b0b8-44af-b304-9d2ae99f1b3d"

/* Mouse channel अणुaddf07d4-94a9-46e2-81c3-61abcdbdbd87पूर्ण */
#घोषणा VISOR_MOUSE_CHANNEL_GUID \
	GUID_INIT(0xaddf07d4, 0x94a9, 0x46e2, \
		  0x81, 0xc3, 0x61, 0xab, 0xcd, 0xbd, 0xbd, 0x87)
#घोषणा VISOR_MOUSE_CHANNEL_GUID_STR "addf07d4-94a9-46e2-81c3-61abcdbdbd87"

#घोषणा PIXELS_ACROSS_DEFAULT 1024
#घोषणा PIXELS_DOWN_DEFAULT   768
#घोषणा KEYCODE_TABLE_BYTES   256

काष्ठा visor_inputactivity अणु
	u16 action;
	u16 arg1;
	u16 arg2;
	u16 arg3;
पूर्ण __packed;

काष्ठा visor_inputreport अणु
	u64 seq_no;
	काष्ठा visor_inputactivity activity;
पूर्ण __packed;

/* header of keyboard/mouse channels */
काष्ठा visor_input_channel_data अणु
	u32 n_input_reports;
	जोड़ अणु
		काष्ठा अणु
			u16 x_res;
			u16 y_res;
		पूर्ण mouse;
		काष्ठा अणु
			u32 flags;
		पूर्ण keyboard;
	पूर्ण;
पूर्ण __packed;

क्रमागत visorinput_dev_type अणु
	visorinput_keyboard,
	visorinput_mouse,
पूर्ण;

/*
 * This is the निजी data that we store क्रम each device. A poपूर्णांकer to this
 * काष्ठा is मुख्यtained via dev_get_drvdata() / dev_set_drvdata() क्रम each
 * काष्ठा device.
 */
काष्ठा visorinput_devdata अणु
	काष्ठा visor_device *dev;
	/* lock क्रम dev */
	काष्ठा mutex lock_visor_dev;
	काष्ठा input_dev *visorinput_dev;
	bool छोड़ोd;
	bool पूर्णांकerrupts_enabled;
	/* size of following array */
	अचिन्हित पूर्णांक keycode_table_bytes;
	/* क्रम keyboard devices: visorkbd_keycode[] + visorkbd_ext_keycode[] */
	अचिन्हित अक्षर keycode_table[];
पूर्ण;

अटल स्थिर guid_t visor_keyboard_channel_guid = VISOR_KEYBOARD_CHANNEL_GUID;
अटल स्थिर guid_t visor_mouse_channel_guid = VISOR_MOUSE_CHANNEL_GUID;

/*
 * Borrowed from drivers/input/keyboard/atakbd.c
 * This maps 1-byte scancodes to keycodes.
 */
अटल स्थिर अचिन्हित अक्षर visorkbd_keycode[KEYCODE_TABLE_BYTES] = अणु
	/* American layout */
	[0] = KEY_GRAVE,
	[1] = KEY_ESC,
	[2] = KEY_1,
	[3] = KEY_2,
	[4] = KEY_3,
	[5] = KEY_4,
	[6] = KEY_5,
	[7] = KEY_6,
	[8] = KEY_7,
	[9] = KEY_8,
	[10] = KEY_9,
	[11] = KEY_0,
	[12] = KEY_MINUS,
	[13] = KEY_EQUAL,
	[14] = KEY_BACKSPACE,
	[15] = KEY_TAB,
	[16] = KEY_Q,
	[17] = KEY_W,
	[18] = KEY_E,
	[19] = KEY_R,
	[20] = KEY_T,
	[21] = KEY_Y,
	[22] = KEY_U,
	[23] = KEY_I,
	[24] = KEY_O,
	[25] = KEY_P,
	[26] = KEY_LEFTBRACE,
	[27] = KEY_RIGHTBRACE,
	[28] = KEY_ENTER,
	[29] = KEY_LEFTCTRL,
	[30] = KEY_A,
	[31] = KEY_S,
	[32] = KEY_D,
	[33] = KEY_F,
	[34] = KEY_G,
	[35] = KEY_H,
	[36] = KEY_J,
	[37] = KEY_K,
	[38] = KEY_L,
	[39] = KEY_SEMICOLON,
	[40] = KEY_APOSTROPHE,
	[41] = KEY_GRAVE,
	[42] = KEY_LEFTSHIFT,
	[43] = KEY_BACKSLASH,
	[44] = KEY_Z,
	[45] = KEY_X,
	[46] = KEY_C,
	[47] = KEY_V,
	[48] = KEY_B,
	[49] = KEY_N,
	[50] = KEY_M,
	[51] = KEY_COMMA,
	[52] = KEY_DOT,
	[53] = KEY_SLASH,
	[54] = KEY_RIGHTSHIFT,
	[55] = KEY_KPASTERISK,
	[56] = KEY_LEFTALT,
	[57] = KEY_SPACE,
	[58] = KEY_CAPSLOCK,
	[59] = KEY_F1,
	[60] = KEY_F2,
	[61] = KEY_F3,
	[62] = KEY_F4,
	[63] = KEY_F5,
	[64] = KEY_F6,
	[65] = KEY_F7,
	[66] = KEY_F8,
	[67] = KEY_F9,
	[68] = KEY_F10,
	[69] = KEY_NUMLOCK,
	[70] = KEY_SCROLLLOCK,
	[71] = KEY_KP7,
	[72] = KEY_KP8,
	[73] = KEY_KP9,
	[74] = KEY_KPMINUS,
	[75] = KEY_KP4,
	[76] = KEY_KP5,
	[77] = KEY_KP6,
	[78] = KEY_KPPLUS,
	[79] = KEY_KP1,
	[80] = KEY_KP2,
	[81] = KEY_KP3,
	[82] = KEY_KP0,
	[83] = KEY_KPDOT,
	/* enables UK backslash+pipe key and FR lessthan+greaterthan key */
	[86] = KEY_102ND,
	[87] = KEY_F11,
	[88] = KEY_F12,
	[90] = KEY_KPLEFTPAREN,
	[91] = KEY_KPRIGHTPAREN,
	[92] = KEY_KPASTERISK,
	[93] = KEY_KPASTERISK,
	[94] = KEY_KPPLUS,
	[95] = KEY_HELP,
	[96] = KEY_KPENTER,
	[97] = KEY_RIGHTCTRL,
	[98] = KEY_KPSLASH,
	[99] = KEY_KPLEFTPAREN,
	[100] = KEY_KPRIGHTPAREN,
	[101] = KEY_KPSLASH,
	[102] = KEY_HOME,
	[103] = KEY_UP,
	[104] = KEY_PAGEUP,
	[105] = KEY_LEFT,
	[106] = KEY_RIGHT,
	[107] = KEY_END,
	[108] = KEY_DOWN,
	[109] = KEY_PAGEDOWN,
	[110] = KEY_INSERT,
	[111] = KEY_DELETE,
	[112] = KEY_MACRO,
	[113] = KEY_MUTE
पूर्ण;

/*
 * This maps the <xx> in extended scancodes of the क्रमm "0xE0 <xx>" पूर्णांकo
 * keycodes.
 */
अटल स्थिर अचिन्हित अक्षर visorkbd_ext_keycode[KEYCODE_TABLE_BYTES] = अणु
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,		    /* 0x00 */
	0, 0, 0, 0, 0, 0, 0, 0,					    /* 0x10 */
	0, 0, 0, 0, KEY_KPENTER, KEY_RIGHTCTRL, 0, 0,		    /* 0x18 */
	0, 0, 0, 0, 0, 0, 0, 0,					    /* 0x20 */
	KEY_RIGHTALT, 0, 0, 0, 0, 0, 0, 0,			    /* 0x28 */
	0, 0, 0, 0, 0, 0, 0, 0,					    /* 0x30 */
	KEY_RIGHTALT /* AltGr */, 0, 0, 0, 0, 0, 0, 0,		    /* 0x38 */
	0, 0, 0, 0, 0, 0, 0, KEY_HOME,				    /* 0x40 */
	KEY_UP, KEY_PAGEUP, 0, KEY_LEFT, 0, KEY_RIGHT, 0, KEY_END,  /* 0x48 */
	KEY_DOWN, KEY_PAGEDOWN, KEY_INSERT, KEY_DELETE, 0, 0, 0, 0, /* 0x50 */
	0, 0, 0, 0, 0, 0, 0, 0,					    /* 0x58 */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,		    /* 0x60 */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,		    /* 0x70 */
पूर्ण;

अटल पूर्णांक visorinput_खोलो(काष्ठा input_dev *visorinput_dev)
अणु
	काष्ठा visorinput_devdata *devdata = input_get_drvdata(visorinput_dev);

	अगर (!devdata) अणु
		dev_err(&visorinput_dev->dev,
			"%s input_get_drvdata(%p) returned NULL\n",
			__func__, visorinput_dev);
		वापस -EINVAL;
	पूर्ण
	dev_dbg(&visorinput_dev->dev, "%s opened\n", __func__);

	/*
	 * If we're not छोड़ोd, really enable पूर्णांकerrupts. Regardless of whether
	 * we are छोड़ोd, set a flag indicating पूर्णांकerrupts should be enabled so
	 * when we resume, पूर्णांकerrupts will really be enabled.
	 */
	mutex_lock(&devdata->lock_visor_dev);
	devdata->पूर्णांकerrupts_enabled = true;
	अगर (devdata->छोड़ोd)
		जाओ out_unlock;
	visorbus_enable_channel_पूर्णांकerrupts(devdata->dev);

out_unlock:
	mutex_unlock(&devdata->lock_visor_dev);
	वापस 0;
पूर्ण

अटल व्योम visorinput_बंद(काष्ठा input_dev *visorinput_dev)
अणु
	काष्ठा visorinput_devdata *devdata = input_get_drvdata(visorinput_dev);

	अगर (!devdata) अणु
		dev_err(&visorinput_dev->dev,
			"%s input_get_drvdata(%p) returned NULL\n",
			__func__, visorinput_dev);
		वापस;
	पूर्ण
	dev_dbg(&visorinput_dev->dev, "%s closed\n", __func__);

	/*
	 * If we're not छोड़ोd, really disable पूर्णांकerrupts. Regardless of
	 * whether we are छोड़ोd, set a flag indicating पूर्णांकerrupts should be
	 * disabled so when we resume we will not re-enable them.
	 */
	mutex_lock(&devdata->lock_visor_dev);
	devdata->पूर्णांकerrupts_enabled = false;
	अगर (devdata->छोड़ोd)
		जाओ out_unlock;
	visorbus_disable_channel_पूर्णांकerrupts(devdata->dev);

out_unlock:
	mutex_unlock(&devdata->lock_visor_dev);
पूर्ण

/*
 * setup_client_keyboard() initializes and वापसs a Linux input node that we
 * can use to deliver keyboard inमाला_दो to Linux.  We of course करो this when we
 * see keyboard inमाला_दो coming in on a keyboard channel.
 */
अटल काष्ठा input_dev *setup_client_keyboard(व्योम *devdata,
					       अचिन्हित अक्षर *keycode_table)

अणु
	पूर्णांक i;
	काष्ठा input_dev *visorinput_dev = input_allocate_device();

	अगर (!visorinput_dev)
		वापस शून्य;

	visorinput_dev->name = "visor Keyboard";
	visorinput_dev->phys = "visorkbd:input0";
	visorinput_dev->id.bustype = BUS_VIRTUAL;
	visorinput_dev->id.venकरोr = 0x0001;
	visorinput_dev->id.product = 0x0001;
	visorinput_dev->id.version = 0x0100;

	visorinput_dev->evbit[0] = BIT_MASK(EV_KEY) |
				   BIT_MASK(EV_REP) |
				   BIT_MASK(EV_LED);
	visorinput_dev->ledbit[0] = BIT_MASK(LED_CAPSL) |
				    BIT_MASK(LED_SCROLLL) |
				    BIT_MASK(LED_NUML);
	visorinput_dev->keycode = keycode_table;
	/* माप(अचिन्हित अक्षर) */
	visorinput_dev->keycodesize = 1;
	visorinput_dev->keycodemax = KEYCODE_TABLE_BYTES;

	क्रम (i = 1; i < visorinput_dev->keycodemax; i++)
		set_bit(keycode_table[i], visorinput_dev->keybit);
	क्रम (i = 1; i < visorinput_dev->keycodemax; i++)
		set_bit(keycode_table[i + KEYCODE_TABLE_BYTES],
			visorinput_dev->keybit);

	visorinput_dev->खोलो = visorinput_खोलो;
	visorinput_dev->बंद = visorinput_बंद;
	/* pre input_रेजिस्टर! */
	input_set_drvdata(visorinput_dev, devdata);

	वापस visorinput_dev;
पूर्ण

अटल काष्ठा input_dev *setup_client_mouse(व्योम *devdata, अचिन्हित पूर्णांक xres,
					    अचिन्हित पूर्णांक yres)
अणु
	काष्ठा input_dev *visorinput_dev = input_allocate_device();

	अगर (!visorinput_dev)
		वापस शून्य;

	visorinput_dev->name = "visor Mouse";
	visorinput_dev->phys = "visormou:input0";
	visorinput_dev->id.bustype = BUS_VIRTUAL;
	visorinput_dev->id.venकरोr = 0x0001;
	visorinput_dev->id.product = 0x0002;
	visorinput_dev->id.version = 0x0100;

	visorinput_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	set_bit(BTN_LEFT, visorinput_dev->keybit);
	set_bit(BTN_RIGHT, visorinput_dev->keybit);
	set_bit(BTN_MIDDLE, visorinput_dev->keybit);

	अगर (xres == 0)
		xres = PIXELS_ACROSS_DEFAULT;
	अगर (yres == 0)
		yres = PIXELS_DOWN_DEFAULT;
	input_set_असल_params(visorinput_dev, ABS_X, 0, xres, 0, 0);
	input_set_असल_params(visorinput_dev, ABS_Y, 0, yres, 0, 0);

	visorinput_dev->खोलो = visorinput_खोलो;
	visorinput_dev->बंद = visorinput_बंद;
	/* pre input_रेजिस्टर! */
	input_set_drvdata(visorinput_dev, devdata);
	input_set_capability(visorinput_dev, EV_REL, REL_WHEEL);

	वापस visorinput_dev;
पूर्ण

अटल काष्ठा visorinput_devdata *devdata_create(काष्ठा visor_device *dev,
						 क्रमागत visorinput_dev_type dtype)
अणु
	काष्ठा visorinput_devdata *devdata = शून्य;
	अचिन्हित पूर्णांक extra_bytes = 0;
	अचिन्हित पूर्णांक size, xres, yres, err;
	काष्ठा visor_input_channel_data data;

	अगर (dtype == visorinput_keyboard)
		/* allocate room क्रम devdata->keycode_table, filled in below */
		extra_bytes = KEYCODE_TABLE_BYTES * 2;
	devdata = kzalloc(माप(*devdata) + extra_bytes, GFP_KERNEL);
	अगर (!devdata)
		वापस शून्य;
	mutex_init(&devdata->lock_visor_dev);
	mutex_lock(&devdata->lock_visor_dev);
	devdata->dev = dev;

	/*
	 * visorinput_खोलो() can be called as soon as input_रेजिस्टर_device()
	 * happens, and that will enable channel पूर्णांकerrupts.  Setting छोड़ोd
	 * prevents us from getting पूर्णांकo visorinput_channel_पूर्णांकerrupt() prior
	 * to the device काष्ठाure being totally initialized.
	 */
	devdata->छोड़ोd = true;

	/*
	 * This is an input device in a client guest partition, so we need to
	 * create whatever input nodes are necessary to deliver our inमाला_दो to
	 * the guest OS.
	 */
	चयन (dtype) अणु
	हाल visorinput_keyboard:
		devdata->keycode_table_bytes = extra_bytes;
		स_नकल(devdata->keycode_table, visorkbd_keycode,
		       KEYCODE_TABLE_BYTES);
		स_नकल(devdata->keycode_table + KEYCODE_TABLE_BYTES,
		       visorkbd_ext_keycode, KEYCODE_TABLE_BYTES);
		devdata->visorinput_dev = setup_client_keyboard
			(devdata, devdata->keycode_table);
		अगर (!devdata->visorinput_dev)
			जाओ cleanups_रेजिस्टर;
		अवरोध;
	हाल visorinput_mouse:
		size = माप(काष्ठा visor_input_channel_data);
		err = visorbus_पढ़ो_channel(dev, माप(काष्ठा channel_header),
					    &data, size);
		अगर (err)
			जाओ cleanups_रेजिस्टर;
		xres = data.mouse.x_res;
		yres = data.mouse.y_res;
		devdata->visorinput_dev = setup_client_mouse(devdata, xres,
							     yres);
		अगर (!devdata->visorinput_dev)
			जाओ cleanups_रेजिस्टर;
		अवरोध;
	शेष:
		/* No other input devices supported */
		अवरोध;
	पूर्ण

	dev_set_drvdata(&dev->device, devdata);
	mutex_unlock(&devdata->lock_visor_dev);

	/*
	 * Device काष्ठा is completely set up now, with the exception of
	 * visorinput_dev being रेजिस्टरed. We need to unlock beक्रमe we
	 * रेजिस्टर the device, because this can cause an on-stack call of
	 * visorinput_खोलो(), which would deadlock अगर we had the lock.
	 */
	अगर (input_रेजिस्टर_device(devdata->visorinput_dev)) अणु
		input_मुक्त_device(devdata->visorinput_dev);
		जाओ err_kमुक्त_devdata;
	पूर्ण

	mutex_lock(&devdata->lock_visor_dev);
	/*
	 * Establish calls to visorinput_channel_पूर्णांकerrupt() अगर that is the
	 * desired state that we've kept track of in पूर्णांकerrupts_enabled जबतक
	 * the device was being created.
	 */
	devdata->छोड़ोd = false;
	अगर (devdata->पूर्णांकerrupts_enabled)
		visorbus_enable_channel_पूर्णांकerrupts(dev);
	mutex_unlock(&devdata->lock_visor_dev);

	वापस devdata;

cleanups_रेजिस्टर:
	mutex_unlock(&devdata->lock_visor_dev);
err_kमुक्त_devdata:
	kमुक्त(devdata);
	वापस शून्य;
पूर्ण

अटल पूर्णांक visorinput_probe(काष्ठा visor_device *dev)
अणु
	स्थिर guid_t *guid;
	क्रमागत visorinput_dev_type dtype;

	guid = visorchannel_get_guid(dev->visorchannel);
	अगर (guid_equal(guid, &visor_mouse_channel_guid))
		dtype = visorinput_mouse;
	अन्यथा अगर (guid_equal(guid, &visor_keyboard_channel_guid))
		dtype = visorinput_keyboard;
	अन्यथा
		वापस -ENODEV;
	visorbus_disable_channel_पूर्णांकerrupts(dev);
	अगर (!devdata_create(dev, dtype))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम unरेजिस्टर_client_input(काष्ठा input_dev *visorinput_dev)
अणु
	अगर (visorinput_dev)
		input_unरेजिस्टर_device(visorinput_dev);
पूर्ण

अटल व्योम visorinput_हटाओ(काष्ठा visor_device *dev)
अणु
	काष्ठा visorinput_devdata *devdata = dev_get_drvdata(&dev->device);

	अगर (!devdata)
		वापस;

	mutex_lock(&devdata->lock_visor_dev);
	visorbus_disable_channel_पूर्णांकerrupts(dev);

	/*
	 * due to above, at this समय no thपढ़ो of execution will be in
	 * visorinput_channel_पूर्णांकerrupt()
	 */

	dev_set_drvdata(&dev->device, शून्य);
	mutex_unlock(&devdata->lock_visor_dev);

	unरेजिस्टर_client_input(devdata->visorinput_dev);
	kमुक्त(devdata);
पूर्ण

/*
 * Make it so the current locking state of the locking key indicated by
 * <keycode> is as indicated by <desired_state> (1=locked, 0=unlocked).
 */
अटल व्योम handle_locking_key(काष्ठा input_dev *visorinput_dev, पूर्णांक keycode,
			       पूर्णांक desired_state)
अणु
	पूर्णांक led;

	चयन (keycode) अणु
	हाल KEY_CAPSLOCK:
		led = LED_CAPSL;
		अवरोध;
	हाल KEY_SCROLLLOCK:
		led = LED_SCROLLL;
		अवरोध;
	हाल KEY_NUMLOCK:
		led = LED_NUML;
		अवरोध;
	शेष:
		led = -1;
		वापस;
	पूर्ण
	अगर (test_bit(led, visorinput_dev->led) != desired_state) अणु
		input_report_key(visorinput_dev, keycode, 1);
		input_sync(visorinput_dev);
		input_report_key(visorinput_dev, keycode, 0);
		input_sync(visorinput_dev);
		__change_bit(led, visorinput_dev->led);
	पूर्ण
पूर्ण

/*
 * <scancode> is either a 1-byte scancode, or an extended 16-bit scancode with
 * 0xE0 in the low byte and the extended scancode value in the next higher byte.
 */
अटल पूर्णांक scancode_to_keycode(पूर्णांक scancode)
अणु
	अगर (scancode > 0xff)
		वापस visorkbd_ext_keycode[(scancode >> 8) & 0xff];

	वापस visorkbd_keycode[scancode];
पूर्ण

अटल पूर्णांक calc_button(पूर्णांक x)
अणु
	चयन (x) अणु
	हाल 1:
		वापस BTN_LEFT;
	हाल 2:
		वापस BTN_MIDDLE;
	हाल 3:
		वापस BTN_RIGHT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * This is used only when this driver is active as an input driver in the
 * client guest partition.  It is called periodically so we can obtain inमाला_दो
 * from the channel, and deliver them to the guest OS.
 */
अटल व्योम visorinput_channel_पूर्णांकerrupt(काष्ठा visor_device *dev)
अणु
	काष्ठा visor_inputreport r;
	पूर्णांक scancode, keycode;
	काष्ठा input_dev *visorinput_dev;
	पूर्णांक xmotion, ymotion, button;
	पूर्णांक i;
	काष्ठा visorinput_devdata *devdata = dev_get_drvdata(&dev->device);

	अगर (!devdata)
		वापस;

	visorinput_dev = devdata->visorinput_dev;

	जबतक (!visorchannel_संकेतहटाओ(dev->visorchannel, 0, &r)) अणु
		scancode = r.activity.arg1;
		keycode = scancode_to_keycode(scancode);
		चयन (r.activity.action) अणु
		हाल INPUTACTION_KEY_DOWN:
			input_report_key(visorinput_dev, keycode, 1);
			input_sync(visorinput_dev);
			अवरोध;
		हाल INPUTACTION_KEY_UP:
			input_report_key(visorinput_dev, keycode, 0);
			input_sync(visorinput_dev);
			अवरोध;
		हाल INPUTACTION_KEY_DOWN_UP:
			input_report_key(visorinput_dev, keycode, 1);
			input_sync(visorinput_dev);
			input_report_key(visorinput_dev, keycode, 0);
			input_sync(visorinput_dev);
			अवरोध;
		हाल INPUTACTION_SET_LOCKING_KEY_STATE:
			handle_locking_key(visorinput_dev, keycode,
					   r.activity.arg2);
			अवरोध;
		हाल INPUTACTION_XY_MOTION:
			xmotion = r.activity.arg1;
			ymotion = r.activity.arg2;
			input_report_असल(visorinput_dev, ABS_X, xmotion);
			input_report_असल(visorinput_dev, ABS_Y, ymotion);
			input_sync(visorinput_dev);
			अवरोध;
		हाल INPUTACTION_MOUSE_BUTTON_DOWN:
			button = calc_button(r.activity.arg1);
			अगर (button < 0)
				अवरोध;
			input_report_key(visorinput_dev, button, 1);
			input_sync(visorinput_dev);
			अवरोध;
		हाल INPUTACTION_MOUSE_BUTTON_UP:
			button = calc_button(r.activity.arg1);
			अगर (button < 0)
				अवरोध;
			input_report_key(visorinput_dev, button, 0);
			input_sync(visorinput_dev);
			अवरोध;
		हाल INPUTACTION_MOUSE_BUTTON_CLICK:
			button = calc_button(r.activity.arg1);
			अगर (button < 0)
				अवरोध;
			input_report_key(visorinput_dev, button, 1);
			input_sync(visorinput_dev);
			input_report_key(visorinput_dev, button, 0);
			input_sync(visorinput_dev);
			अवरोध;
		हाल INPUTACTION_MOUSE_BUTTON_DCLICK:
			button = calc_button(r.activity.arg1);
			अगर (button < 0)
				अवरोध;
			क्रम (i = 0; i < 2; i++) अणु
				input_report_key(visorinput_dev, button, 1);
				input_sync(visorinput_dev);
				input_report_key(visorinput_dev, button, 0);
				input_sync(visorinput_dev);
			पूर्ण
			अवरोध;
		हाल INPUTACTION_WHEEL_ROTATE_AWAY:
			input_report_rel(visorinput_dev, REL_WHEEL, 1);
			input_sync(visorinput_dev);
			अवरोध;
		हाल INPUTACTION_WHEEL_ROTATE_TOWARD:
			input_report_rel(visorinput_dev, REL_WHEEL, -1);
			input_sync(visorinput_dev);
			अवरोध;
		शेष:
			/* Unsupported input action */
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक visorinput_छोड़ो(काष्ठा visor_device *dev,
			    visorbus_state_complete_func complete_func)
अणु
	पूर्णांक rc;
	काष्ठा visorinput_devdata *devdata = dev_get_drvdata(&dev->device);

	अगर (!devdata) अणु
		rc = -ENODEV;
		जाओ out;
	पूर्ण

	mutex_lock(&devdata->lock_visor_dev);
	अगर (devdata->छोड़ोd) अणु
		rc = -EBUSY;
		जाओ out_locked;
	पूर्ण
	अगर (devdata->पूर्णांकerrupts_enabled)
		visorbus_disable_channel_पूर्णांकerrupts(dev);

	/*
	 * due to above, at this समय no thपढ़ो of execution will be in
	 * visorinput_channel_पूर्णांकerrupt()
	 */
	devdata->छोड़ोd = true;
	complete_func(dev, 0);
	rc = 0;
out_locked:
	mutex_unlock(&devdata->lock_visor_dev);
out:
	वापस rc;
पूर्ण

अटल पूर्णांक visorinput_resume(काष्ठा visor_device *dev,
			     visorbus_state_complete_func complete_func)
अणु
	पूर्णांक rc;
	काष्ठा visorinput_devdata *devdata = dev_get_drvdata(&dev->device);

	अगर (!devdata) अणु
		rc = -ENODEV;
		जाओ out;
	पूर्ण
	mutex_lock(&devdata->lock_visor_dev);
	अगर (!devdata->छोड़ोd) अणु
		rc = -EBUSY;
		जाओ out_locked;
	पूर्ण
	devdata->छोड़ोd = false;
	complete_func(dev, 0);

	/*
	 * Re-establish calls to visorinput_channel_पूर्णांकerrupt() अगर that is the
	 * desired state that we've kept track of in पूर्णांकerrupts_enabled जबतक
	 * the device was छोड़ोd.
	 */
	अगर (devdata->पूर्णांकerrupts_enabled)
		visorbus_enable_channel_पूर्णांकerrupts(dev);

	rc = 0;
out_locked:
	mutex_unlock(&devdata->lock_visor_dev);
out:
	वापस rc;
पूर्ण

/* GUIDS क्रम all channel types supported by this driver. */
अटल काष्ठा visor_channeltype_descriptor visorinput_channel_types[] = अणु
	अणु VISOR_KEYBOARD_CHANNEL_GUID, "keyboard",
	  माप(काष्ठा channel_header), 0 पूर्ण,
	अणु VISOR_MOUSE_CHANNEL_GUID, "mouse", माप(काष्ठा channel_header), 0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा visor_driver visorinput_driver = अणु
	.name = "visorinput",
	.owner = THIS_MODULE,
	.channel_types = visorinput_channel_types,
	.probe = visorinput_probe,
	.हटाओ = visorinput_हटाओ,
	.channel_पूर्णांकerrupt = visorinput_channel_पूर्णांकerrupt,
	.छोड़ो = visorinput_छोड़ो,
	.resume = visorinput_resume,
पूर्ण;

module_driver(visorinput_driver, visorbus_रेजिस्टर_visor_driver,
	      visorbus_unरेजिस्टर_visor_driver);

MODULE_DEVICE_TABLE(visorbus, visorinput_channel_types);

MODULE_AUTHOR("Unisys");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("s-Par human input driver for virtual keyboard/mouse");

MODULE_ALIAS("visorbus:" VISOR_MOUSE_CHANNEL_GUID_STR);
MODULE_ALIAS("visorbus:" VISOR_KEYBOARD_CHANNEL_GUID_STR);
