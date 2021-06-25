<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * FireDTV driver (क्रमmerly known as FireSAT)
 *
 * Copyright (C) 2004 Andreas Monitzer <andy@monitzer.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#समावेश "firedtv.h"

/* fixed table with older keycodes, geared towards MythTV */
अटल स्थिर u16 oldtable[] = अणु

	/* code from device: 0x4501...0x451f */

	KEY_ESC,
	KEY_F9,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_I,
	KEY_0,
	KEY_ENTER,
	KEY_RED,
	KEY_UP,
	KEY_GREEN,
	KEY_F10,
	KEY_SPACE,
	KEY_F11,
	KEY_YELLOW,
	KEY_DOWN,
	KEY_BLUE,
	KEY_Z,
	KEY_P,
	KEY_PAGEDOWN,
	KEY_LEFT,
	KEY_W,
	KEY_RIGHT,
	KEY_P,
	KEY_M,

	/* code from device: 0x4540...0x4542 */

	KEY_R,
	KEY_V,
	KEY_C,
पूर्ण;

/* user-modअगरiable table क्रम a remote as sold in 2008 */
अटल स्थिर u16 keytable[] = अणु

	/* code from device: 0x0300...0x031f */

	[0x00] = KEY_POWER,
	[0x01] = KEY_SLEEP,
	[0x02] = KEY_STOP,
	[0x03] = KEY_OK,
	[0x04] = KEY_RIGHT,
	[0x05] = KEY_1,
	[0x06] = KEY_2,
	[0x07] = KEY_3,
	[0x08] = KEY_LEFT,
	[0x09] = KEY_4,
	[0x0a] = KEY_5,
	[0x0b] = KEY_6,
	[0x0c] = KEY_UP,
	[0x0d] = KEY_7,
	[0x0e] = KEY_8,
	[0x0f] = KEY_9,
	[0x10] = KEY_DOWN,
	[0x11] = KEY_TITLE,	/* "OSD" - fixme */
	[0x12] = KEY_0,
	[0x13] = KEY_F20,	/* "16:9" - fixme */
	[0x14] = KEY_SCREEN,	/* "FULL" - fixme */
	[0x15] = KEY_MUTE,
	[0x16] = KEY_SUBTITLE,
	[0x17] = KEY_RECORD,
	[0x18] = KEY_TEXT,
	[0x19] = KEY_AUDIO,
	[0x1a] = KEY_RED,
	[0x1b] = KEY_PREVIOUS,
	[0x1c] = KEY_REWIND,
	[0x1d] = KEY_PLAYPAUSE,
	[0x1e] = KEY_NEXT,
	[0x1f] = KEY_VOLUMEUP,

	/* code from device: 0x0340...0x0354 */

	[0x20] = KEY_CHANNELUP,
	[0x21] = KEY_F21,	/* "4:3" - fixme */
	[0x22] = KEY_TV,
	[0x23] = KEY_DVD,
	[0x24] = KEY_VCR,
	[0x25] = KEY_AUX,
	[0x26] = KEY_GREEN,
	[0x27] = KEY_YELLOW,
	[0x28] = KEY_BLUE,
	[0x29] = KEY_CHANNEL,	/* "CH.LIST" */
	[0x2a] = KEY_VENDOR,	/* "CI" - fixme */
	[0x2b] = KEY_VOLUMEDOWN,
	[0x2c] = KEY_CHANNELDOWN,
	[0x2d] = KEY_LAST,
	[0x2e] = KEY_INFO,
	[0x2f] = KEY_FORWARD,
	[0x30] = KEY_LIST,
	[0x31] = KEY_FAVORITES,
	[0x32] = KEY_MENU,
	[0x33] = KEY_EPG,
	[0x34] = KEY_EXIT,
पूर्ण;

पूर्णांक fdtv_रेजिस्टर_rc(काष्ठा firedtv *fdtv, काष्ठा device *dev)
अणु
	काष्ठा input_dev *idev;
	पूर्णांक i, err;

	idev = input_allocate_device();
	अगर (!idev)
		वापस -ENOMEM;

	fdtv->remote_ctrl_dev = idev;
	idev->name = "FireDTV remote control";
	idev->dev.parent = dev;
	idev->evbit[0] = BIT_MASK(EV_KEY);
	idev->keycode = kmemdup(keytable, माप(keytable), GFP_KERNEL);
	अगर (!idev->keycode) अणु
		err = -ENOMEM;
		जाओ fail;
	पूर्ण
	idev->keycodesize = माप(keytable[0]);
	idev->keycodemax = ARRAY_SIZE(keytable);

	क्रम (i = 0; i < ARRAY_SIZE(keytable); i++)
		set_bit(keytable[i], idev->keybit);

	err = input_रेजिस्टर_device(idev);
	अगर (err)
		जाओ fail_मुक्त_keymap;

	वापस 0;

fail_मुक्त_keymap:
	kमुक्त(idev->keycode);
fail:
	input_मुक्त_device(idev);
	वापस err;
पूर्ण

व्योम fdtv_unरेजिस्टर_rc(काष्ठा firedtv *fdtv)
अणु
	cancel_work_sync(&fdtv->remote_ctrl_work);
	kमुक्त(fdtv->remote_ctrl_dev->keycode);
	input_unरेजिस्टर_device(fdtv->remote_ctrl_dev);
पूर्ण

व्योम fdtv_handle_rc(काष्ठा firedtv *fdtv, अचिन्हित पूर्णांक code)
अणु
	काष्ठा input_dev *idev = fdtv->remote_ctrl_dev;
	u16 *keycode = idev->keycode;

	अगर (code >= 0x0300 && code <= 0x031f)
		code = keycode[code - 0x0300];
	अन्यथा अगर (code >= 0x0340 && code <= 0x0354)
		code = keycode[code - 0x0320];
	अन्यथा अगर (code >= 0x4501 && code <= 0x451f)
		code = oldtable[code - 0x4501];
	अन्यथा अगर (code >= 0x4540 && code <= 0x4542)
		code = oldtable[code - 0x4521];
	अन्यथा अणु
		dev_dbg(fdtv->device,
			"invalid key code 0x%04x from remote control\n",
			code);
		वापस;
	पूर्ण

	input_report_key(idev, code, 1);
	input_sync(idev);
	input_report_key(idev, code, 0);
	input_sync(idev);
पूर्ण
