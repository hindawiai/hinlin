<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ati_remote2 - ATI/Philips USB RF remote driver
 *
 * Copyright (C) 2005-2008 Ville Syrjala <syrjala@sci.fi>
 * Copyright (C) 2007-2008 Peter Stokes <linux@dadeos.co.uk>
 */

#समावेश <linux/usb/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#घोषणा DRIVER_DESC    "ATI/Philips USB RF remote driver"

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR("Ville Syrjala <syrjala@sci.fi>");
MODULE_LICENSE("GPL");

/*
 * ATI Remote Wonder II Channel Configuration
 *
 * The remote control can be asचिन्हित one of sixteen "channels" in order to facilitate
 * the use of multiple remote controls within range of each other.
 * A remote's "channel" may be altered by pressing and holding the "PC" button क्रम
 * approximately 3 seconds, after which the button will slowly flash the count of the
 * currently configured "channel", using the numeric keypad enter a number between 1 and
 * 16 and then press the "PC" button again, the button will slowly flash the count of the
 * newly configured "channel".
 */

क्रमागत अणु
	ATI_REMOTE2_MAX_CHANNEL_MASK = 0xFFFF,
	ATI_REMOTE2_MAX_MODE_MASK = 0x1F,
पूर्ण;

अटल पूर्णांक ati_remote2_set_mask(स्थिर अक्षर *val,
				स्थिर काष्ठा kernel_param *kp,
				अचिन्हित पूर्णांक max)
अणु
	अचिन्हित पूर्णांक mask;
	पूर्णांक ret;

	अगर (!val)
		वापस -EINVAL;

	ret = kstrtouपूर्णांक(val, 0, &mask);
	अगर (ret)
		वापस ret;

	अगर (mask & ~max)
		वापस -EINVAL;

	*(अचिन्हित पूर्णांक *)kp->arg = mask;

	वापस 0;
पूर्ण

अटल पूर्णांक ati_remote2_set_channel_mask(स्थिर अक्षर *val,
					स्थिर काष्ठा kernel_param *kp)
अणु
	pr_debug("%s()\n", __func__);

	वापस ati_remote2_set_mask(val, kp, ATI_REMOTE2_MAX_CHANNEL_MASK);
पूर्ण

अटल पूर्णांक ati_remote2_get_channel_mask(अक्षर *buffer,
					स्थिर काष्ठा kernel_param *kp)
अणु
	pr_debug("%s()\n", __func__);

	वापस प्र_लिखो(buffer, "0x%04x\n", *(अचिन्हित पूर्णांक *)kp->arg);
पूर्ण

अटल पूर्णांक ati_remote2_set_mode_mask(स्थिर अक्षर *val,
				     स्थिर काष्ठा kernel_param *kp)
अणु
	pr_debug("%s()\n", __func__);

	वापस ati_remote2_set_mask(val, kp, ATI_REMOTE2_MAX_MODE_MASK);
पूर्ण

अटल पूर्णांक ati_remote2_get_mode_mask(अक्षर *buffer,
				     स्थिर काष्ठा kernel_param *kp)
अणु
	pr_debug("%s()\n", __func__);

	वापस प्र_लिखो(buffer, "0x%02x\n", *(अचिन्हित पूर्णांक *)kp->arg);
पूर्ण

अटल अचिन्हित पूर्णांक channel_mask = ATI_REMOTE2_MAX_CHANNEL_MASK;
#घोषणा param_check_channel_mask(name, p) __param_check(name, p, अचिन्हित पूर्णांक)
अटल स्थिर काष्ठा kernel_param_ops param_ops_channel_mask = अणु
	.set = ati_remote2_set_channel_mask,
	.get = ati_remote2_get_channel_mask,
पूर्ण;
module_param(channel_mask, channel_mask, 0644);
MODULE_PARM_DESC(channel_mask, "Bitmask of channels to accept <15:Channel16>...<1:Channel2><0:Channel1>");

अटल अचिन्हित पूर्णांक mode_mask = ATI_REMOTE2_MAX_MODE_MASK;
#घोषणा param_check_mode_mask(name, p) __param_check(name, p, अचिन्हित पूर्णांक)
अटल स्थिर काष्ठा kernel_param_ops param_ops_mode_mask = अणु
	.set = ati_remote2_set_mode_mask,
	.get = ati_remote2_get_mode_mask,
पूर्ण;
module_param(mode_mask, mode_mask, 0644);
MODULE_PARM_DESC(mode_mask, "Bitmask of modes to accept <4:PC><3:AUX4><2:AUX3><1:AUX2><0:AUX1>");

अटल स्थिर काष्ठा usb_device_id ati_remote2_id_table[] = अणु
	अणु USB_DEVICE(0x0471, 0x0602) पूर्ण,	/* ATI Remote Wonder II */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, ati_remote2_id_table);

अटल DEFINE_MUTEX(ati_remote2_mutex);

क्रमागत अणु
	ATI_REMOTE2_OPENED = 0x1,
	ATI_REMOTE2_SUSPENDED = 0x2,
पूर्ण;

क्रमागत अणु
	ATI_REMOTE2_AUX1,
	ATI_REMOTE2_AUX2,
	ATI_REMOTE2_AUX3,
	ATI_REMOTE2_AUX4,
	ATI_REMOTE2_PC,
	ATI_REMOTE2_MODES,
पूर्ण;

अटल स्थिर काष्ठा अणु
	u8  hw_code;
	u16 keycode;
पूर्ण ati_remote2_key_table[] = अणु
	अणु 0x00, KEY_0 पूर्ण,
	अणु 0x01, KEY_1 पूर्ण,
	अणु 0x02, KEY_2 पूर्ण,
	अणु 0x03, KEY_3 पूर्ण,
	अणु 0x04, KEY_4 पूर्ण,
	अणु 0x05, KEY_5 पूर्ण,
	अणु 0x06, KEY_6 पूर्ण,
	अणु 0x07, KEY_7 पूर्ण,
	अणु 0x08, KEY_8 पूर्ण,
	अणु 0x09, KEY_9 पूर्ण,
	अणु 0x0c, KEY_POWER पूर्ण,
	अणु 0x0d, KEY_MUTE पूर्ण,
	अणु 0x10, KEY_VOLUMEUP पूर्ण,
	अणु 0x11, KEY_VOLUMEDOWN पूर्ण,
	अणु 0x20, KEY_CHANNELUP पूर्ण,
	अणु 0x21, KEY_CHANNELDOWN पूर्ण,
	अणु 0x28, KEY_FORWARD पूर्ण,
	अणु 0x29, KEY_REWIND पूर्ण,
	अणु 0x2c, KEY_PLAY पूर्ण,
	अणु 0x30, KEY_PAUSE पूर्ण,
	अणु 0x31, KEY_STOP पूर्ण,
	अणु 0x37, KEY_RECORD पूर्ण,
	अणु 0x38, KEY_DVD पूर्ण,
	अणु 0x39, KEY_TV पूर्ण,
	अणु 0x3f, KEY_PROG1 पूर्ण, /* AUX1-AUX4 and PC */
	अणु 0x54, KEY_MENU पूर्ण,
	अणु 0x58, KEY_UP पूर्ण,
	अणु 0x59, KEY_DOWN पूर्ण,
	अणु 0x5a, KEY_LEFT पूर्ण,
	अणु 0x5b, KEY_RIGHT पूर्ण,
	अणु 0x5c, KEY_OK पूर्ण,
	अणु 0x78, KEY_A पूर्ण,
	अणु 0x79, KEY_B पूर्ण,
	अणु 0x7a, KEY_C पूर्ण,
	अणु 0x7b, KEY_D पूर्ण,
	अणु 0x7c, KEY_E पूर्ण,
	अणु 0x7d, KEY_F पूर्ण,
	अणु 0x82, KEY_ENTER पूर्ण,
	अणु 0x8e, KEY_VENDOR पूर्ण,
	अणु 0x96, KEY_COFFEE पूर्ण,
	अणु 0xa9, BTN_LEFT पूर्ण,
	अणु 0xaa, BTN_RIGHT पूर्ण,
	अणु 0xbe, KEY_QUESTION पूर्ण,
	अणु 0xd0, KEY_EDIT पूर्ण,
	अणु 0xd5, KEY_FRONT पूर्ण,
	अणु 0xf9, KEY_INFO पूर्ण,
पूर्ण;

काष्ठा ati_remote2 अणु
	काष्ठा input_dev *idev;
	काष्ठा usb_device *udev;

	काष्ठा usb_पूर्णांकerface *पूर्णांकf[2];
	काष्ठा usb_endpoपूर्णांक_descriptor *ep[2];
	काष्ठा urb *urb[2];
	व्योम *buf[2];
	dma_addr_t buf_dma[2];

	अचिन्हित दीर्घ jअगरfies;
	पूर्णांक mode;

	अक्षर name[64];
	अक्षर phys[64];

	/* Each mode (AUX1-AUX4 and PC) can have an independent keymap. */
	u16 keycode[ATI_REMOTE2_MODES][ARRAY_SIZE(ati_remote2_key_table)];

	अचिन्हित पूर्णांक flags;

	अचिन्हित पूर्णांक channel_mask;
	अचिन्हित पूर्णांक mode_mask;
पूर्ण;

अटल पूर्णांक ati_remote2_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface, स्थिर काष्ठा usb_device_id *id);
अटल व्योम ati_remote2_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface);
अटल पूर्णांक ati_remote2_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकerface, pm_message_t message);
अटल पूर्णांक ati_remote2_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकerface);
अटल पूर्णांक ati_remote2_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकerface);
अटल पूर्णांक ati_remote2_pre_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकerface);
अटल पूर्णांक ati_remote2_post_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकerface);

अटल काष्ठा usb_driver ati_remote2_driver = अणु
	.name       = "ati_remote2",
	.probe      = ati_remote2_probe,
	.disconnect = ati_remote2_disconnect,
	.id_table   = ati_remote2_id_table,
	.suspend    = ati_remote2_suspend,
	.resume     = ati_remote2_resume,
	.reset_resume = ati_remote2_reset_resume,
	.pre_reset  = ati_remote2_pre_reset,
	.post_reset = ati_remote2_post_reset,
	.supports_स्वतःsuspend = 1,
पूर्ण;

अटल पूर्णांक ati_remote2_submit_urbs(काष्ठा ati_remote2 *ar2)
अणु
	पूर्णांक r;

	r = usb_submit_urb(ar2->urb[0], GFP_KERNEL);
	अगर (r) अणु
		dev_err(&ar2->पूर्णांकf[0]->dev,
			"%s(): usb_submit_urb() = %d\n", __func__, r);
		वापस r;
	पूर्ण
	r = usb_submit_urb(ar2->urb[1], GFP_KERNEL);
	अगर (r) अणु
		usb_समाप्त_urb(ar2->urb[0]);
		dev_err(&ar2->पूर्णांकf[1]->dev,
			"%s(): usb_submit_urb() = %d\n", __func__, r);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ati_remote2_समाप्त_urbs(काष्ठा ati_remote2 *ar2)
अणु
	usb_समाप्त_urb(ar2->urb[1]);
	usb_समाप्त_urb(ar2->urb[0]);
पूर्ण

अटल पूर्णांक ati_remote2_खोलो(काष्ठा input_dev *idev)
अणु
	काष्ठा ati_remote2 *ar2 = input_get_drvdata(idev);
	पूर्णांक r;

	dev_dbg(&ar2->पूर्णांकf[0]->dev, "%s()\n", __func__);

	r = usb_स्वतःpm_get_पूर्णांकerface(ar2->पूर्णांकf[0]);
	अगर (r) अणु
		dev_err(&ar2->पूर्णांकf[0]->dev,
			"%s(): usb_autopm_get_interface() = %d\n", __func__, r);
		जाओ fail1;
	पूर्ण

	mutex_lock(&ati_remote2_mutex);

	अगर (!(ar2->flags & ATI_REMOTE2_SUSPENDED)) अणु
		r = ati_remote2_submit_urbs(ar2);
		अगर (r)
			जाओ fail2;
	पूर्ण

	ar2->flags |= ATI_REMOTE2_OPENED;

	mutex_unlock(&ati_remote2_mutex);

	usb_स्वतःpm_put_पूर्णांकerface(ar2->पूर्णांकf[0]);

	वापस 0;

 fail2:
	mutex_unlock(&ati_remote2_mutex);
	usb_स्वतःpm_put_पूर्णांकerface(ar2->पूर्णांकf[0]);
 fail1:
	वापस r;
पूर्ण

अटल व्योम ati_remote2_बंद(काष्ठा input_dev *idev)
अणु
	काष्ठा ati_remote2 *ar2 = input_get_drvdata(idev);

	dev_dbg(&ar2->पूर्णांकf[0]->dev, "%s()\n", __func__);

	mutex_lock(&ati_remote2_mutex);

	अगर (!(ar2->flags & ATI_REMOTE2_SUSPENDED))
		ati_remote2_समाप्त_urbs(ar2);

	ar2->flags &= ~ATI_REMOTE2_OPENED;

	mutex_unlock(&ati_remote2_mutex);
पूर्ण

अटल व्योम ati_remote2_input_mouse(काष्ठा ati_remote2 *ar2)
अणु
	काष्ठा input_dev *idev = ar2->idev;
	u8 *data = ar2->buf[0];
	पूर्णांक channel, mode;

	channel = data[0] >> 4;

	अगर (!((1 << channel) & ar2->channel_mask))
		वापस;

	mode = data[0] & 0x0F;

	अगर (mode > ATI_REMOTE2_PC) अणु
		dev_err(&ar2->पूर्णांकf[0]->dev,
			"Unknown mode byte (%02x %02x %02x %02x)\n",
			data[3], data[2], data[1], data[0]);
		वापस;
	पूर्ण

	अगर (!((1 << mode) & ar2->mode_mask))
		वापस;

	input_event(idev, EV_REL, REL_X, (s8) data[1]);
	input_event(idev, EV_REL, REL_Y, (s8) data[2]);
	input_sync(idev);
पूर्ण

अटल पूर्णांक ati_remote2_lookup(अचिन्हित पूर्णांक hw_code)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ati_remote2_key_table); i++)
		अगर (ati_remote2_key_table[i].hw_code == hw_code)
			वापस i;

	वापस -1;
पूर्ण

अटल व्योम ati_remote2_input_key(काष्ठा ati_remote2 *ar2)
अणु
	काष्ठा input_dev *idev = ar2->idev;
	u8 *data = ar2->buf[1];
	पूर्णांक channel, mode, hw_code, index;

	channel = data[0] >> 4;

	अगर (!((1 << channel) & ar2->channel_mask))
		वापस;

	mode = data[0] & 0x0F;

	अगर (mode > ATI_REMOTE2_PC) अणु
		dev_err(&ar2->पूर्णांकf[1]->dev,
			"Unknown mode byte (%02x %02x %02x %02x)\n",
			data[3], data[2], data[1], data[0]);
		वापस;
	पूर्ण

	hw_code = data[2];
	अगर (hw_code == 0x3f) अणु
		/*
		 * For some incomprehensible reason the mouse pad generates
		 * events which look identical to the events from the last
		 * pressed mode key. Naturally we करोn't want to generate key
		 * events क्रम the mouse pad so we filter out any subsequent
		 * events from the same mode key.
		 */
		अगर (ar2->mode == mode)
			वापस;

		अगर (data[1] == 0)
			ar2->mode = mode;
	पूर्ण

	अगर (!((1 << mode) & ar2->mode_mask))
		वापस;

	index = ati_remote2_lookup(hw_code);
	अगर (index < 0) अणु
		dev_err(&ar2->पूर्णांकf[1]->dev,
			"Unknown code byte (%02x %02x %02x %02x)\n",
			data[3], data[2], data[1], data[0]);
		वापस;
	पूर्ण

	चयन (data[1]) अणु
	हाल 0:	/* release */
		अवरोध;
	हाल 1:	/* press */
		ar2->jअगरfies = jअगरfies + msecs_to_jअगरfies(idev->rep[REP_DELAY]);
		अवरोध;
	हाल 2:	/* repeat */

		/* No repeat क्रम mouse buttons. */
		अगर (ar2->keycode[mode][index] == BTN_LEFT ||
		    ar2->keycode[mode][index] == BTN_RIGHT)
			वापस;

		अगर (!समय_after_eq(jअगरfies, ar2->jअगरfies))
			वापस;

		ar2->jअगरfies = jअगरfies + msecs_to_jअगरfies(idev->rep[REP_PERIOD]);
		अवरोध;
	शेष:
		dev_err(&ar2->पूर्णांकf[1]->dev,
			"Unknown state byte (%02x %02x %02x %02x)\n",
			data[3], data[2], data[1], data[0]);
		वापस;
	पूर्ण

	input_event(idev, EV_KEY, ar2->keycode[mode][index], data[1]);
	input_sync(idev);
पूर्ण

अटल व्योम ati_remote2_complete_mouse(काष्ठा urb *urb)
अणु
	काष्ठा ati_remote2 *ar2 = urb->context;
	पूर्णांक r;

	चयन (urb->status) अणु
	हाल 0:
		usb_mark_last_busy(ar2->udev);
		ati_remote2_input_mouse(ar2);
		अवरोध;
	हाल -ENOENT:
	हाल -EILSEQ:
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
		dev_dbg(&ar2->पूर्णांकf[0]->dev,
			"%s(): urb status = %d\n", __func__, urb->status);
		वापस;
	शेष:
		usb_mark_last_busy(ar2->udev);
		dev_err(&ar2->पूर्णांकf[0]->dev,
			"%s(): urb status = %d\n", __func__, urb->status);
	पूर्ण

	r = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (r)
		dev_err(&ar2->पूर्णांकf[0]->dev,
			"%s(): usb_submit_urb() = %d\n", __func__, r);
पूर्ण

अटल व्योम ati_remote2_complete_key(काष्ठा urb *urb)
अणु
	काष्ठा ati_remote2 *ar2 = urb->context;
	पूर्णांक r;

	चयन (urb->status) अणु
	हाल 0:
		usb_mark_last_busy(ar2->udev);
		ati_remote2_input_key(ar2);
		अवरोध;
	हाल -ENOENT:
	हाल -EILSEQ:
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
		dev_dbg(&ar2->पूर्णांकf[1]->dev,
			"%s(): urb status = %d\n", __func__, urb->status);
		वापस;
	शेष:
		usb_mark_last_busy(ar2->udev);
		dev_err(&ar2->पूर्णांकf[1]->dev,
			"%s(): urb status = %d\n", __func__, urb->status);
	पूर्ण

	r = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (r)
		dev_err(&ar2->पूर्णांकf[1]->dev,
			"%s(): usb_submit_urb() = %d\n", __func__, r);
पूर्ण

अटल पूर्णांक ati_remote2_getkeycode(काष्ठा input_dev *idev,
				  काष्ठा input_keymap_entry *ke)
अणु
	काष्ठा ati_remote2 *ar2 = input_get_drvdata(idev);
	अचिन्हित पूर्णांक mode;
	पूर्णांक offset;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक scancode;

	अगर (ke->flags & INPUT_KEYMAP_BY_INDEX) अणु
		index = ke->index;
		अगर (index >= ATI_REMOTE2_MODES *
				ARRAY_SIZE(ati_remote2_key_table))
			वापस -EINVAL;

		mode = ke->index / ARRAY_SIZE(ati_remote2_key_table);
		offset = ke->index % ARRAY_SIZE(ati_remote2_key_table);
		scancode = (mode << 8) + ati_remote2_key_table[offset].hw_code;
	पूर्ण अन्यथा अणु
		अगर (input_scancode_to_scalar(ke, &scancode))
			वापस -EINVAL;

		mode = scancode >> 8;
		अगर (mode > ATI_REMOTE2_PC)
			वापस -EINVAL;

		offset = ati_remote2_lookup(scancode & 0xff);
		अगर (offset < 0)
			वापस -EINVAL;

		index = mode * ARRAY_SIZE(ati_remote2_key_table) + offset;
	पूर्ण

	ke->keycode = ar2->keycode[mode][offset];
	ke->len = माप(scancode);
	स_नकल(&ke->scancode, &scancode, माप(scancode));
	ke->index = index;

	वापस 0;
पूर्ण

अटल पूर्णांक ati_remote2_setkeycode(काष्ठा input_dev *idev,
				  स्थिर काष्ठा input_keymap_entry *ke,
				  अचिन्हित पूर्णांक *old_keycode)
अणु
	काष्ठा ati_remote2 *ar2 = input_get_drvdata(idev);
	अचिन्हित पूर्णांक mode;
	पूर्णांक offset;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक scancode;

	अगर (ke->flags & INPUT_KEYMAP_BY_INDEX) अणु
		अगर (ke->index >= ATI_REMOTE2_MODES *
				ARRAY_SIZE(ati_remote2_key_table))
			वापस -EINVAL;

		mode = ke->index / ARRAY_SIZE(ati_remote2_key_table);
		offset = ke->index % ARRAY_SIZE(ati_remote2_key_table);
	पूर्ण अन्यथा अणु
		अगर (input_scancode_to_scalar(ke, &scancode))
			वापस -EINVAL;

		mode = scancode >> 8;
		अगर (mode > ATI_REMOTE2_PC)
			वापस -EINVAL;

		offset = ati_remote2_lookup(scancode & 0xff);
		अगर (offset < 0)
			वापस -EINVAL;
	पूर्ण

	*old_keycode = ar2->keycode[mode][offset];
	ar2->keycode[mode][offset] = ke->keycode;
	__set_bit(ke->keycode, idev->keybit);

	क्रम (mode = 0; mode < ATI_REMOTE2_MODES; mode++) अणु
		क्रम (index = 0; index < ARRAY_SIZE(ati_remote2_key_table); index++) अणु
			अगर (ar2->keycode[mode][index] == *old_keycode)
				वापस 0;
		पूर्ण
	पूर्ण

	__clear_bit(*old_keycode, idev->keybit);

	वापस 0;
पूर्ण

अटल पूर्णांक ati_remote2_input_init(काष्ठा ati_remote2 *ar2)
अणु
	काष्ठा input_dev *idev;
	पूर्णांक index, mode, retval;

	idev = input_allocate_device();
	अगर (!idev)
		वापस -ENOMEM;

	ar2->idev = idev;
	input_set_drvdata(idev, ar2);

	idev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP) | BIT_MASK(EV_REL);
	idev->keybit[BIT_WORD(BTN_MOUSE)] = BIT_MASK(BTN_LEFT) |
		BIT_MASK(BTN_RIGHT);
	idev->relbit[0] = BIT_MASK(REL_X) | BIT_MASK(REL_Y);

	क्रम (mode = 0; mode < ATI_REMOTE2_MODES; mode++) अणु
		क्रम (index = 0; index < ARRAY_SIZE(ati_remote2_key_table); index++) अणु
			ar2->keycode[mode][index] = ati_remote2_key_table[index].keycode;
			__set_bit(ar2->keycode[mode][index], idev->keybit);
		पूर्ण
	पूर्ण

	/* AUX1-AUX4 and PC generate the same scancode. */
	index = ati_remote2_lookup(0x3f);
	ar2->keycode[ATI_REMOTE2_AUX1][index] = KEY_PROG1;
	ar2->keycode[ATI_REMOTE2_AUX2][index] = KEY_PROG2;
	ar2->keycode[ATI_REMOTE2_AUX3][index] = KEY_PROG3;
	ar2->keycode[ATI_REMOTE2_AUX4][index] = KEY_PROG4;
	ar2->keycode[ATI_REMOTE2_PC][index] = KEY_PC;
	__set_bit(KEY_PROG1, idev->keybit);
	__set_bit(KEY_PROG2, idev->keybit);
	__set_bit(KEY_PROG3, idev->keybit);
	__set_bit(KEY_PROG4, idev->keybit);
	__set_bit(KEY_PC, idev->keybit);

	idev->rep[REP_DELAY]  = 250;
	idev->rep[REP_PERIOD] = 33;

	idev->खोलो = ati_remote2_खोलो;
	idev->बंद = ati_remote2_बंद;

	idev->getkeycode = ati_remote2_getkeycode;
	idev->setkeycode = ati_remote2_setkeycode;

	idev->name = ar2->name;
	idev->phys = ar2->phys;

	usb_to_input_id(ar2->udev, &idev->id);
	idev->dev.parent = &ar2->udev->dev;

	retval = input_रेजिस्टर_device(idev);
	अगर (retval)
		input_मुक्त_device(idev);

	वापस retval;
पूर्ण

अटल पूर्णांक ati_remote2_urb_init(काष्ठा ati_remote2 *ar2)
अणु
	काष्ठा usb_device *udev = ar2->udev;
	पूर्णांक i, pipe, maxp;

	क्रम (i = 0; i < 2; i++) अणु
		ar2->buf[i] = usb_alloc_coherent(udev, 4, GFP_KERNEL, &ar2->buf_dma[i]);
		अगर (!ar2->buf[i])
			वापस -ENOMEM;

		ar2->urb[i] = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!ar2->urb[i])
			वापस -ENOMEM;

		pipe = usb_rcvपूर्णांकpipe(udev, ar2->ep[i]->bEndpoपूर्णांकAddress);
		maxp = usb_maxpacket(udev, pipe, usb_pipeout(pipe));
		maxp = maxp > 4 ? 4 : maxp;

		usb_fill_पूर्णांक_urb(ar2->urb[i], udev, pipe, ar2->buf[i], maxp,
				 i ? ati_remote2_complete_key : ati_remote2_complete_mouse,
				 ar2, ar2->ep[i]->bInterval);
		ar2->urb[i]->transfer_dma = ar2->buf_dma[i];
		ar2->urb[i]->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ati_remote2_urb_cleanup(काष्ठा ati_remote2 *ar2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		usb_मुक्त_urb(ar2->urb[i]);
		usb_मुक्त_coherent(ar2->udev, 4, ar2->buf[i], ar2->buf_dma[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक ati_remote2_setup(काष्ठा ati_remote2 *ar2, अचिन्हित पूर्णांक ch_mask)
अणु
	पूर्णांक r, i, channel;

	/*
	 * Configure receiver to only accept input from remote "channel"
	 *  channel == 0  -> Accept input from any remote channel
	 *  channel == 1  -> Only accept input from remote channel 1
	 *  channel == 2  -> Only accept input from remote channel 2
	 *  ...
	 *  channel == 16 -> Only accept input from remote channel 16
	 */

	channel = 0;
	क्रम (i = 0; i < 16; i++) अणु
		अगर ((1 << i) & ch_mask) अणु
			अगर (!(~(1 << i) & ch_mask))
				channel = i + 1;
			अवरोध;
		पूर्ण
	पूर्ण

	r = usb_control_msg(ar2->udev, usb_sndctrlpipe(ar2->udev, 0),
			    0x20,
			    USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_INTERFACE,
			    channel, 0x0, शून्य, 0, USB_CTRL_SET_TIMEOUT);
	अगर (r) अणु
		dev_err(&ar2->udev->dev, "%s - failed to set channel due to error: %d\n",
			__func__, r);
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ati_remote2_show_channel_mask(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = usb_अगरnum_to_अगर(udev, 0);
	काष्ठा ati_remote2 *ar2 = usb_get_पूर्णांकfdata(पूर्णांकf);

	वापस प्र_लिखो(buf, "0x%04x\n", ar2->channel_mask);
पूर्ण

अटल sमाप_प्रकार ati_remote2_store_channel_mask(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = usb_अगरnum_to_अगर(udev, 0);
	काष्ठा ati_remote2 *ar2 = usb_get_पूर्णांकfdata(पूर्णांकf);
	अचिन्हित पूर्णांक mask;
	पूर्णांक r;

	r = kstrtouपूर्णांक(buf, 0, &mask);
	अगर (r)
		वापस r;

	अगर (mask & ~ATI_REMOTE2_MAX_CHANNEL_MASK)
		वापस -EINVAL;

	r = usb_स्वतःpm_get_पूर्णांकerface(ar2->पूर्णांकf[0]);
	अगर (r) अणु
		dev_err(&ar2->पूर्णांकf[0]->dev,
			"%s(): usb_autopm_get_interface() = %d\n", __func__, r);
		वापस r;
	पूर्ण

	mutex_lock(&ati_remote2_mutex);

	अगर (mask != ar2->channel_mask) अणु
		r = ati_remote2_setup(ar2, mask);
		अगर (!r)
			ar2->channel_mask = mask;
	पूर्ण

	mutex_unlock(&ati_remote2_mutex);

	usb_स्वतःpm_put_पूर्णांकerface(ar2->पूर्णांकf[0]);

	वापस r ? r : count;
पूर्ण

अटल sमाप_प्रकार ati_remote2_show_mode_mask(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = usb_अगरnum_to_अगर(udev, 0);
	काष्ठा ati_remote2 *ar2 = usb_get_पूर्णांकfdata(पूर्णांकf);

	वापस प्र_लिखो(buf, "0x%02x\n", ar2->mode_mask);
पूर्ण

अटल sमाप_प्रकार ati_remote2_store_mode_mask(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_device *udev = to_usb_device(dev);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = usb_अगरnum_to_अगर(udev, 0);
	काष्ठा ati_remote2 *ar2 = usb_get_पूर्णांकfdata(पूर्णांकf);
	अचिन्हित पूर्णांक mask;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 0, &mask);
	अगर (err)
		वापस err;

	अगर (mask & ~ATI_REMOTE2_MAX_MODE_MASK)
		वापस -EINVAL;

	ar2->mode_mask = mask;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(channel_mask, 0644, ati_remote2_show_channel_mask,
		   ati_remote2_store_channel_mask);

अटल DEVICE_ATTR(mode_mask, 0644, ati_remote2_show_mode_mask,
		   ati_remote2_store_mode_mask);

अटल काष्ठा attribute *ati_remote2_attrs[] = अणु
	&dev_attr_channel_mask.attr,
	&dev_attr_mode_mask.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group ati_remote2_attr_group = अणु
	.attrs = ati_remote2_attrs,
पूर्ण;

अटल पूर्णांक ati_remote2_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा usb_host_पूर्णांकerface *alt = पूर्णांकerface->cur_altsetting;
	काष्ठा ati_remote2 *ar2;
	पूर्णांक r;

	अगर (alt->desc.bInterfaceNumber)
		वापस -ENODEV;

	ar2 = kzalloc(माप (काष्ठा ati_remote2), GFP_KERNEL);
	अगर (!ar2)
		वापस -ENOMEM;

	ar2->udev = udev;

	/* Sanity check, first पूर्णांकerface must have an endpoपूर्णांक */
	अगर (alt->desc.bNumEndpoपूर्णांकs < 1 || !alt->endpoपूर्णांक) अणु
		dev_err(&पूर्णांकerface->dev,
			"%s(): interface 0 must have an endpoint\n", __func__);
		r = -ENODEV;
		जाओ fail1;
	पूर्ण
	ar2->पूर्णांकf[0] = पूर्णांकerface;
	ar2->ep[0] = &alt->endpoपूर्णांक[0].desc;

	/* Sanity check, the device must have two पूर्णांकerfaces */
	ar2->पूर्णांकf[1] = usb_अगरnum_to_अगर(udev, 1);
	अगर ((udev->actconfig->desc.bNumInterfaces < 2) || !ar2->पूर्णांकf[1]) अणु
		dev_err(&पूर्णांकerface->dev, "%s(): need 2 interfaces, found %d\n",
			__func__, udev->actconfig->desc.bNumInterfaces);
		r = -ENODEV;
		जाओ fail1;
	पूर्ण

	r = usb_driver_claim_पूर्णांकerface(&ati_remote2_driver, ar2->पूर्णांकf[1], ar2);
	अगर (r)
		जाओ fail1;

	/* Sanity check, second पूर्णांकerface must have an endpoपूर्णांक */
	alt = ar2->पूर्णांकf[1]->cur_altsetting;
	अगर (alt->desc.bNumEndpoपूर्णांकs < 1 || !alt->endpoपूर्णांक) अणु
		dev_err(&पूर्णांकerface->dev,
			"%s(): interface 1 must have an endpoint\n", __func__);
		r = -ENODEV;
		जाओ fail2;
	पूर्ण
	ar2->ep[1] = &alt->endpoपूर्णांक[0].desc;

	r = ati_remote2_urb_init(ar2);
	अगर (r)
		जाओ fail3;

	ar2->channel_mask = channel_mask;
	ar2->mode_mask = mode_mask;

	r = ati_remote2_setup(ar2, ar2->channel_mask);
	अगर (r)
		जाओ fail3;

	usb_make_path(udev, ar2->phys, माप(ar2->phys));
	strlcat(ar2->phys, "/input0", माप(ar2->phys));

	strlcat(ar2->name, "ATI Remote Wonder II", माप(ar2->name));

	r = sysfs_create_group(&udev->dev.kobj, &ati_remote2_attr_group);
	अगर (r)
		जाओ fail3;

	r = ati_remote2_input_init(ar2);
	अगर (r)
		जाओ fail4;

	usb_set_पूर्णांकfdata(पूर्णांकerface, ar2);

	पूर्णांकerface->needs_remote_wakeup = 1;

	वापस 0;

 fail4:
	sysfs_हटाओ_group(&udev->dev.kobj, &ati_remote2_attr_group);
 fail3:
	ati_remote2_urb_cleanup(ar2);
 fail2:
	usb_driver_release_पूर्णांकerface(&ati_remote2_driver, ar2->पूर्णांकf[1]);
 fail1:
	kमुक्त(ar2);

	वापस r;
पूर्ण

अटल व्योम ati_remote2_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा ati_remote2 *ar2;
	काष्ठा usb_host_पूर्णांकerface *alt = पूर्णांकerface->cur_altsetting;

	अगर (alt->desc.bInterfaceNumber)
		वापस;

	ar2 = usb_get_पूर्णांकfdata(पूर्णांकerface);
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	input_unरेजिस्टर_device(ar2->idev);

	sysfs_हटाओ_group(&ar2->udev->dev.kobj, &ati_remote2_attr_group);

	ati_remote2_urb_cleanup(ar2);

	usb_driver_release_पूर्णांकerface(&ati_remote2_driver, ar2->पूर्णांकf[1]);

	kमुक्त(ar2);
पूर्ण

अटल पूर्णांक ati_remote2_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
			       pm_message_t message)
अणु
	काष्ठा ati_remote2 *ar2;
	काष्ठा usb_host_पूर्णांकerface *alt = पूर्णांकerface->cur_altsetting;

	अगर (alt->desc.bInterfaceNumber)
		वापस 0;

	ar2 = usb_get_पूर्णांकfdata(पूर्णांकerface);

	dev_dbg(&ar2->पूर्णांकf[0]->dev, "%s()\n", __func__);

	mutex_lock(&ati_remote2_mutex);

	अगर (ar2->flags & ATI_REMOTE2_OPENED)
		ati_remote2_समाप्त_urbs(ar2);

	ar2->flags |= ATI_REMOTE2_SUSPENDED;

	mutex_unlock(&ati_remote2_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ati_remote2_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा ati_remote2 *ar2;
	काष्ठा usb_host_पूर्णांकerface *alt = पूर्णांकerface->cur_altsetting;
	पूर्णांक r = 0;

	अगर (alt->desc.bInterfaceNumber)
		वापस 0;

	ar2 = usb_get_पूर्णांकfdata(पूर्णांकerface);

	dev_dbg(&ar2->पूर्णांकf[0]->dev, "%s()\n", __func__);

	mutex_lock(&ati_remote2_mutex);

	अगर (ar2->flags & ATI_REMOTE2_OPENED)
		r = ati_remote2_submit_urbs(ar2);

	अगर (!r)
		ar2->flags &= ~ATI_REMOTE2_SUSPENDED;

	mutex_unlock(&ati_remote2_mutex);

	वापस r;
पूर्ण

अटल पूर्णांक ati_remote2_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा ati_remote2 *ar2;
	काष्ठा usb_host_पूर्णांकerface *alt = पूर्णांकerface->cur_altsetting;
	पूर्णांक r = 0;

	अगर (alt->desc.bInterfaceNumber)
		वापस 0;

	ar2 = usb_get_पूर्णांकfdata(पूर्णांकerface);

	dev_dbg(&ar2->पूर्णांकf[0]->dev, "%s()\n", __func__);

	mutex_lock(&ati_remote2_mutex);

	r = ati_remote2_setup(ar2, ar2->channel_mask);
	अगर (r)
		जाओ out;

	अगर (ar2->flags & ATI_REMOTE2_OPENED)
		r = ati_remote2_submit_urbs(ar2);

	अगर (!r)
		ar2->flags &= ~ATI_REMOTE2_SUSPENDED;

 out:
	mutex_unlock(&ati_remote2_mutex);

	वापस r;
पूर्ण

अटल पूर्णांक ati_remote2_pre_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा ati_remote2 *ar2;
	काष्ठा usb_host_पूर्णांकerface *alt = पूर्णांकerface->cur_altsetting;

	अगर (alt->desc.bInterfaceNumber)
		वापस 0;

	ar2 = usb_get_पूर्णांकfdata(पूर्णांकerface);

	dev_dbg(&ar2->पूर्णांकf[0]->dev, "%s()\n", __func__);

	mutex_lock(&ati_remote2_mutex);

	अगर (ar2->flags == ATI_REMOTE2_OPENED)
		ati_remote2_समाप्त_urbs(ar2);

	वापस 0;
पूर्ण

अटल पूर्णांक ati_remote2_post_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा ati_remote2 *ar2;
	काष्ठा usb_host_पूर्णांकerface *alt = पूर्णांकerface->cur_altsetting;
	पूर्णांक r = 0;

	अगर (alt->desc.bInterfaceNumber)
		वापस 0;

	ar2 = usb_get_पूर्णांकfdata(पूर्णांकerface);

	dev_dbg(&ar2->पूर्णांकf[0]->dev, "%s()\n", __func__);

	अगर (ar2->flags == ATI_REMOTE2_OPENED)
		r = ati_remote2_submit_urbs(ar2);

	mutex_unlock(&ati_remote2_mutex);

	वापस r;
पूर्ण

module_usb_driver(ati_remote2_driver);
