<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the VoIP USB phones with CM109 chipsets.
 *
 * Copyright (C) 2007 - 2008 Alfred E. Heggestad <aeh@db.org>
 */

/*
 *   Tested devices:
 *	- Komunikate KIP1000
 *	- Genius G-talk
 *	- Allied-Telesis Corega USBPH01
 *	- ...
 *
 * This driver is based on the yealink.c driver
 *
 * Thanks to:
 *   - Authors of yealink.c
 *   - Thomas Reiपंचांगayr
 *   - Oliver Neukum क्रम good review comments and code
 *   - Shaun Jackman <sjackman@gmail.com> क्रम Genius G-talk keymap
 *   - Dmitry Torokhov क्रम valuable input and review
 *
 * Toकरो:
 *   - Read/ग_लिखो EEPROM
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/usb/input.h>

#घोषणा DRIVER_VERSION "20080805"
#घोषणा DRIVER_AUTHOR  "Alfred E. Heggestad"
#घोषणा DRIVER_DESC    "CM109 phone driver"

अटल अक्षर *phone = "kip1000";
module_param(phone, अक्षरp, S_IRUSR);
MODULE_PARM_DESC(phone, "Phone name {kip1000, gtalk, usbph01, atcom}");

क्रमागत अणु
	/* HID Registers */
	HID_IR0 = 0x00, /* Record/Playback-mute button, Volume up/करोwn  */
	HID_IR1 = 0x01, /* GPI, generic रेजिस्टरs or EEPROM_DATA0       */
	HID_IR2 = 0x02, /* Generic रेजिस्टरs or EEPROM_DATA1            */
	HID_IR3 = 0x03, /* Generic रेजिस्टरs or EEPROM_CTRL             */
	HID_OR0 = 0x00, /* Mapping control, buzzer, SPDIF (offset 0x04) */
	HID_OR1 = 0x01, /* GPO - General Purpose Output                 */
	HID_OR2 = 0x02, /* Set GPIO to input/output mode                */
	HID_OR3 = 0x03, /* SPDIF status channel or EEPROM_CTRL          */

	/* HID_IR0 */
	RECORD_MUTE   = 1 << 3,
	PLAYBACK_MUTE = 1 << 2,
	VOLUME_DOWN   = 1 << 1,
	VOLUME_UP     = 1 << 0,

	/* HID_OR0 */
	/* bits 7-6
	   0: HID_OR1-2 are used क्रम GPO; HID_OR0, 3 are used क्रम buzzer
	      and SPDIF
	   1: HID_OR0-3 are used as generic HID रेजिस्टरs
	   2: Values written to HID_OR0-3 are also mapped to MCU_CTRL,
	      EEPROM_DATA0-1, EEPROM_CTRL (see Note)
	   3: Reserved
	 */
	HID_OR_GPO_BUZ_SPDIF   = 0 << 6,
	HID_OR_GENERIC_HID_REG = 1 << 6,
	HID_OR_MAP_MCU_EEPROM  = 2 << 6,

	BUZZER_ON = 1 << 5,

	/* up to 256 normal keys, up to 15 special key combinations */
	KEYMAP_SIZE = 256 + 15,
पूर्ण;

/* CM109 protocol packet */
काष्ठा cm109_ctl_packet अणु
	u8 byte[4];
पूर्ण __attribute__ ((packed));

क्रमागत अणु USB_PKT_LEN = माप(काष्ठा cm109_ctl_packet) पूर्ण;

/* CM109 device काष्ठाure */
काष्ठा cm109_dev अणु
	काष्ठा input_dev *idev;	 /* input device */
	काष्ठा usb_device *udev; /* usb device */
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;

	/* irq input channel */
	काष्ठा cm109_ctl_packet *irq_data;
	dma_addr_t irq_dma;
	काष्ठा urb *urb_irq;

	/* control output channel */
	काष्ठा cm109_ctl_packet *ctl_data;
	dma_addr_t ctl_dma;
	काष्ठा usb_ctrlrequest *ctl_req;
	काष्ठा urb *urb_ctl;
	/*
	 * The 3 bitfields below are रक्षित by ctl_submit_lock.
	 * They have to be separate since they are accessed from IRQ
	 * context.
	 */
	अचिन्हित irq_urb_pending:1;	/* irq_urb is in flight */
	अचिन्हित ctl_urb_pending:1;	/* ctl_urb is in flight */
	अचिन्हित buzzer_pending:1;	/* need to issue buzz command */
	spinlock_t ctl_submit_lock;

	अचिन्हित अक्षर buzzer_state;	/* on/off */

	/* flags */
	अचिन्हित खोलो:1;
	अचिन्हित resetting:1;
	अचिन्हित shutकरोwn:1;

	/* This mutex protects ग_लिखोs to the above flags */
	काष्ठा mutex pm_mutex;

	अचिन्हित लघु keymap[KEYMAP_SIZE];

	अक्षर phys[64];		/* physical device path */
	पूर्णांक key_code;		/* last reported key */
	पूर्णांक keybit;		/* 0=new scan  1,2,4,8=scan columns  */
	u8 gpi;			/* Cached value of GPI (high nibble) */
पूर्ण;

/******************************************************************************
 * CM109 key पूर्णांकerface
 *****************************************************************************/

अटल अचिन्हित लघु special_keymap(पूर्णांक code)
अणु
	अगर (code > 0xff) अणु
		चयन (code - 0xff) अणु
		हाल RECORD_MUTE:	वापस KEY_MICMUTE;
		हाल PLAYBACK_MUTE:	वापस KEY_MUTE;
		हाल VOLUME_DOWN:	वापस KEY_VOLUMEDOWN;
		हाल VOLUME_UP:		वापस KEY_VOLUMEUP;
		पूर्ण
	पूर्ण
	वापस KEY_RESERVED;
पूर्ण

/* Map device buttons to पूर्णांकernal key events.
 *
 * The "up" and "down" keys, are symbolised by arrows on the button.
 * The "pickup" and "hangup" keys are symbolised by a green and red phone
 * on the button.

 Komunikate KIP1000 Keyboard Matrix

     -> -- 1 -- 2 -- 3  --> GPI pin 4 (0x10)
      |    |    |    |
     <- -- 4 -- 5 -- 6  --> GPI pin 5 (0x20)
      |    |    |    |
     END - 7 -- 8 -- 9  --> GPI pin 6 (0x40)
      |    |    |    |
     OK -- * -- 0 -- #  --> GPI pin 7 (0x80)
      |    |    |    |

     /|\  /|\  /|\  /|\
      |    |    |    |
GPO
pin:  3    2    1    0
     0x8  0x4  0x2  0x1

 */
अटल अचिन्हित लघु keymap_kip1000(पूर्णांक scancode)
अणु
	चयन (scancode) अणु				/* phone key:   */
	हाल 0x82: वापस KEY_NUMERIC_0;		/*   0          */
	हाल 0x14: वापस KEY_NUMERIC_1;		/*   1          */
	हाल 0x12: वापस KEY_NUMERIC_2;		/*   2          */
	हाल 0x11: वापस KEY_NUMERIC_3;		/*   3          */
	हाल 0x24: वापस KEY_NUMERIC_4;		/*   4          */
	हाल 0x22: वापस KEY_NUMERIC_5;		/*   5          */
	हाल 0x21: वापस KEY_NUMERIC_6;		/*   6          */
	हाल 0x44: वापस KEY_NUMERIC_7;		/*   7          */
	हाल 0x42: वापस KEY_NUMERIC_8;		/*   8          */
	हाल 0x41: वापस KEY_NUMERIC_9;		/*   9          */
	हाल 0x81: वापस KEY_NUMERIC_POUND;		/*   #          */
	हाल 0x84: वापस KEY_NUMERIC_STAR;		/*   *          */
	हाल 0x88: वापस KEY_ENTER;			/*   pickup     */
	हाल 0x48: वापस KEY_ESC;			/*   hangup     */
	हाल 0x28: वापस KEY_LEFT;			/*   IN         */
	हाल 0x18: वापस KEY_RIGHT;			/*   OUT        */
	शेष:   वापस special_keymap(scancode);
	पूर्ण
पूर्ण

/*
  Contributed by Shaun Jackman <sjackman@gmail.com>

  Genius G-Talk keyboard matrix
     0 1 2 3
  4: 0 4 8 Talk
  5: 1 5 9 End
  6: 2 6 # Up
  7: 3 7 * Down
*/
अटल अचिन्हित लघु keymap_gtalk(पूर्णांक scancode)
अणु
	चयन (scancode) अणु
	हाल 0x11: वापस KEY_NUMERIC_0;
	हाल 0x21: वापस KEY_NUMERIC_1;
	हाल 0x41: वापस KEY_NUMERIC_2;
	हाल 0x81: वापस KEY_NUMERIC_3;
	हाल 0x12: वापस KEY_NUMERIC_4;
	हाल 0x22: वापस KEY_NUMERIC_5;
	हाल 0x42: वापस KEY_NUMERIC_6;
	हाल 0x82: वापस KEY_NUMERIC_7;
	हाल 0x14: वापस KEY_NUMERIC_8;
	हाल 0x24: वापस KEY_NUMERIC_9;
	हाल 0x44: वापस KEY_NUMERIC_POUND;	/* # */
	हाल 0x84: वापस KEY_NUMERIC_STAR;	/* * */
	हाल 0x18: वापस KEY_ENTER;		/* Talk (green handset) */
	हाल 0x28: वापस KEY_ESC;		/* End (red handset) */
	हाल 0x48: वापस KEY_UP;		/* Menu up (rocker चयन) */
	हाल 0x88: वापस KEY_DOWN;		/* Menu करोwn (rocker चयन) */
	शेष:   वापस special_keymap(scancode);
	पूर्ण
पूर्ण

/*
 * Keymap क्रम Allied-Telesis Corega USBPH01
 * http://www.alliedtelesis-corega.com/2/1344/1437/1360/chprd.hपंचांगl
 *
 * Contributed by july@nat.bg
 */
अटल अचिन्हित लघु keymap_usbph01(पूर्णांक scancode)
अणु
	चयन (scancode) अणु
	हाल 0x11: वापस KEY_NUMERIC_0;		/*   0          */
	हाल 0x21: वापस KEY_NUMERIC_1;		/*   1          */
	हाल 0x41: वापस KEY_NUMERIC_2;		/*   2          */
	हाल 0x81: वापस KEY_NUMERIC_3;		/*   3          */
	हाल 0x12: वापस KEY_NUMERIC_4;		/*   4          */
	हाल 0x22: वापस KEY_NUMERIC_5;		/*   5          */
	हाल 0x42: वापस KEY_NUMERIC_6;		/*   6          */
	हाल 0x82: वापस KEY_NUMERIC_7;		/*   7          */
	हाल 0x14: वापस KEY_NUMERIC_8;		/*   8          */
	हाल 0x24: वापस KEY_NUMERIC_9;		/*   9          */
	हाल 0x44: वापस KEY_NUMERIC_POUND;		/*   #          */
	हाल 0x84: वापस KEY_NUMERIC_STAR;		/*   *          */
	हाल 0x18: वापस KEY_ENTER;			/*   pickup     */
	हाल 0x28: वापस KEY_ESC;			/*   hangup     */
	हाल 0x48: वापस KEY_LEFT;			/*   IN         */
	हाल 0x88: वापस KEY_RIGHT;			/*   OUT        */
	शेष:   वापस special_keymap(scancode);
	पूर्ण
पूर्ण

/*
 * Keymap क्रम ATCom AU-100
 * http://www.atcom.cn/products.hपंचांगl 
 * http://www.packetizer.com/products/au100/
 * http://www.voip-info.org/wiki/view/AU-100
 *
 * Contributed by daniel@gimpelevich.san-francisco.ca.us
 */
अटल अचिन्हित लघु keymap_atcom(पूर्णांक scancode)
अणु
	चयन (scancode) अणु				/* phone key:   */
	हाल 0x82: वापस KEY_NUMERIC_0;		/*   0          */
	हाल 0x11: वापस KEY_NUMERIC_1;		/*   1          */
	हाल 0x12: वापस KEY_NUMERIC_2;		/*   2          */
	हाल 0x14: वापस KEY_NUMERIC_3;		/*   3          */
	हाल 0x21: वापस KEY_NUMERIC_4;		/*   4          */
	हाल 0x22: वापस KEY_NUMERIC_5;		/*   5          */
	हाल 0x24: वापस KEY_NUMERIC_6;		/*   6          */
	हाल 0x41: वापस KEY_NUMERIC_7;		/*   7          */
	हाल 0x42: वापस KEY_NUMERIC_8;		/*   8          */
	हाल 0x44: वापस KEY_NUMERIC_9;		/*   9          */
	हाल 0x84: वापस KEY_NUMERIC_POUND;		/*   #          */
	हाल 0x81: वापस KEY_NUMERIC_STAR;		/*   *          */
	हाल 0x18: वापस KEY_ENTER;			/*   pickup     */
	हाल 0x28: वापस KEY_ESC;			/*   hangup     */
	हाल 0x48: वापस KEY_LEFT;			/* left arrow   */
	हाल 0x88: वापस KEY_RIGHT;			/* right arrow  */
	शेष:   वापस special_keymap(scancode);
	पूर्ण
पूर्ण

अटल अचिन्हित लघु (*keymap)(पूर्णांक) = keymap_kip1000;

/*
 * Completes a request by converting the data पूर्णांकo events क्रम the
 * input subप्रणाली.
 */
अटल व्योम report_key(काष्ठा cm109_dev *dev, पूर्णांक key)
अणु
	काष्ठा input_dev *idev = dev->idev;

	अगर (dev->key_code >= 0) अणु
		/* old key up */
		input_report_key(idev, dev->key_code, 0);
	पूर्ण

	dev->key_code = key;
	अगर (key >= 0) अणु
		/* new valid key */
		input_report_key(idev, key, 1);
	पूर्ण

	input_sync(idev);
पूर्ण

/*
 * Converts data of special key presses (volume, mute) पूर्णांकo events
 * क्रम the input subप्रणाली, sends press-n-release क्रम mute keys.
 */
अटल व्योम cm109_report_special(काष्ठा cm109_dev *dev)
अणु
	अटल स्थिर u8 स्वतःrelease = RECORD_MUTE | PLAYBACK_MUTE;
	काष्ठा input_dev *idev = dev->idev;
	u8 data = dev->irq_data->byte[HID_IR0];
	अचिन्हित लघु keycode;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		keycode = dev->keymap[0xff + BIT(i)];
		अगर (keycode == KEY_RESERVED)
			जारी;

		input_report_key(idev, keycode, data & BIT(i));
		अगर (data & स्वतःrelease & BIT(i)) अणु
			input_sync(idev);
			input_report_key(idev, keycode, 0);
		पूर्ण
	पूर्ण
	input_sync(idev);
पूर्ण

/******************************************************************************
 * CM109 usb communication पूर्णांकerface
 *****************************************************************************/

अटल व्योम cm109_submit_buzz_toggle(काष्ठा cm109_dev *dev)
अणु
	पूर्णांक error;

	अगर (dev->buzzer_state)
		dev->ctl_data->byte[HID_OR0] |= BUZZER_ON;
	अन्यथा
		dev->ctl_data->byte[HID_OR0] &= ~BUZZER_ON;

	error = usb_submit_urb(dev->urb_ctl, GFP_ATOMIC);
	अगर (error)
		dev_err(&dev->पूर्णांकf->dev,
			"%s: usb_submit_urb (urb_ctl) failed %d\n",
			__func__, error);
पूर्ण

/*
 * IRQ handler
 */
अटल व्योम cm109_urb_irq_callback(काष्ठा urb *urb)
अणु
	काष्ठा cm109_dev *dev = urb->context;
	स्थिर पूर्णांक status = urb->status;
	पूर्णांक error;
	अचिन्हित दीर्घ flags;

	dev_dbg(&dev->पूर्णांकf->dev, "### URB IRQ: [0x%02x 0x%02x 0x%02x 0x%02x] keybit=0x%02x\n",
	     dev->irq_data->byte[0],
	     dev->irq_data->byte[1],
	     dev->irq_data->byte[2],
	     dev->irq_data->byte[3],
	     dev->keybit);

	अगर (status) अणु
		अगर (status == -ESHUTDOWN)
			वापस;
		dev_err_ratelimited(&dev->पूर्णांकf->dev, "%s: urb status %d\n",
				    __func__, status);
		जाओ out;
	पूर्ण

	/* Special keys */
	cm109_report_special(dev);

	/* Scan key column */
	अगर (dev->keybit == 0xf) अणु

		/* Any changes ? */
		अगर ((dev->gpi & 0xf0) == (dev->irq_data->byte[HID_IR1] & 0xf0))
			जाओ out;

		dev->gpi = dev->irq_data->byte[HID_IR1] & 0xf0;
		dev->keybit = 0x1;
	पूर्ण अन्यथा अणु
		report_key(dev, dev->keymap[dev->irq_data->byte[HID_IR1]]);

		dev->keybit <<= 1;
		अगर (dev->keybit > 0x8)
			dev->keybit = 0xf;
	पूर्ण

 out:

	spin_lock_irqsave(&dev->ctl_submit_lock, flags);

	dev->irq_urb_pending = 0;

	अगर (likely(!dev->shutकरोwn)) अणु

		अगर (dev->buzzer_state)
			dev->ctl_data->byte[HID_OR0] |= BUZZER_ON;
		अन्यथा
			dev->ctl_data->byte[HID_OR0] &= ~BUZZER_ON;

		dev->ctl_data->byte[HID_OR1] = dev->keybit;
		dev->ctl_data->byte[HID_OR2] = dev->keybit;

		dev->buzzer_pending = 0;
		dev->ctl_urb_pending = 1;

		error = usb_submit_urb(dev->urb_ctl, GFP_ATOMIC);
		अगर (error)
			dev_err(&dev->पूर्णांकf->dev,
				"%s: usb_submit_urb (urb_ctl) failed %d\n",
				__func__, error);
	पूर्ण

	spin_unlock_irqrestore(&dev->ctl_submit_lock, flags);
पूर्ण

अटल व्योम cm109_urb_ctl_callback(काष्ठा urb *urb)
अणु
	काष्ठा cm109_dev *dev = urb->context;
	स्थिर पूर्णांक status = urb->status;
	पूर्णांक error;
	अचिन्हित दीर्घ flags;

	dev_dbg(&dev->पूर्णांकf->dev, "### URB CTL: [0x%02x 0x%02x 0x%02x 0x%02x]\n",
	     dev->ctl_data->byte[0],
	     dev->ctl_data->byte[1],
	     dev->ctl_data->byte[2],
	     dev->ctl_data->byte[3]);

	अगर (status) अणु
		अगर (status == -ESHUTDOWN)
			वापस;
		dev_err_ratelimited(&dev->पूर्णांकf->dev, "%s: urb status %d\n",
				    __func__, status);
	पूर्ण

	spin_lock_irqsave(&dev->ctl_submit_lock, flags);

	dev->ctl_urb_pending = 0;

	अगर (likely(!dev->shutकरोwn)) अणु

		अगर (dev->buzzer_pending || status) अणु
			dev->buzzer_pending = 0;
			dev->ctl_urb_pending = 1;
			cm109_submit_buzz_toggle(dev);
		पूर्ण अन्यथा अगर (likely(!dev->irq_urb_pending)) अणु
			/* ask क्रम key data */
			dev->irq_urb_pending = 1;
			error = usb_submit_urb(dev->urb_irq, GFP_ATOMIC);
			अगर (error)
				dev_err(&dev->पूर्णांकf->dev,
					"%s: usb_submit_urb (urb_irq) failed %d\n",
					__func__, error);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&dev->ctl_submit_lock, flags);
पूर्ण

अटल व्योम cm109_toggle_buzzer_async(काष्ठा cm109_dev *dev)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->ctl_submit_lock, flags);

	अगर (dev->ctl_urb_pending) अणु
		/* URB completion will resubmit */
		dev->buzzer_pending = 1;
	पूर्ण अन्यथा अणु
		dev->ctl_urb_pending = 1;
		cm109_submit_buzz_toggle(dev);
	पूर्ण

	spin_unlock_irqrestore(&dev->ctl_submit_lock, flags);
पूर्ण

अटल व्योम cm109_toggle_buzzer_sync(काष्ठा cm109_dev *dev, पूर्णांक on)
अणु
	पूर्णांक error;

	अगर (on)
		dev->ctl_data->byte[HID_OR0] |= BUZZER_ON;
	अन्यथा
		dev->ctl_data->byte[HID_OR0] &= ~BUZZER_ON;

	error = usb_control_msg(dev->udev,
				usb_sndctrlpipe(dev->udev, 0),
				dev->ctl_req->bRequest,
				dev->ctl_req->bRequestType,
				le16_to_cpu(dev->ctl_req->wValue),
				le16_to_cpu(dev->ctl_req->wIndex),
				dev->ctl_data,
				USB_PKT_LEN, USB_CTRL_SET_TIMEOUT);
	अगर (error < 0 && error != -EINTR)
		dev_err(&dev->पूर्णांकf->dev, "%s: usb_control_msg() failed %d\n",
			__func__, error);
पूर्ण

अटल व्योम cm109_stop_traffic(काष्ठा cm109_dev *dev)
अणु
	dev->shutकरोwn = 1;
	/*
	 * Make sure other CPUs see this
	 */
	smp_wmb();

	usb_समाप्त_urb(dev->urb_ctl);
	usb_समाप्त_urb(dev->urb_irq);

	cm109_toggle_buzzer_sync(dev, 0);

	dev->shutकरोwn = 0;
	smp_wmb();
पूर्ण

अटल व्योम cm109_restore_state(काष्ठा cm109_dev *dev)
अणु
	अगर (dev->खोलो) अणु
		/*
		 * Restore buzzer state.
		 * This will also kick regular URB submission
		 */
		cm109_toggle_buzzer_async(dev);
	पूर्ण
पूर्ण

/******************************************************************************
 * input event पूर्णांकerface
 *****************************************************************************/

अटल पूर्णांक cm109_input_खोलो(काष्ठा input_dev *idev)
अणु
	काष्ठा cm109_dev *dev = input_get_drvdata(idev);
	पूर्णांक error;

	error = usb_स्वतःpm_get_पूर्णांकerface(dev->पूर्णांकf);
	अगर (error < 0) अणु
		dev_err(&idev->dev, "%s - cannot autoresume, result %d\n",
			__func__, error);
		वापस error;
	पूर्ण

	mutex_lock(&dev->pm_mutex);

	dev->buzzer_state = 0;
	dev->key_code = -1;	/* no keys pressed */
	dev->keybit = 0xf;

	/* issue INIT */
	dev->ctl_data->byte[HID_OR0] = HID_OR_GPO_BUZ_SPDIF;
	dev->ctl_data->byte[HID_OR1] = dev->keybit;
	dev->ctl_data->byte[HID_OR2] = dev->keybit;
	dev->ctl_data->byte[HID_OR3] = 0x00;

	dev->ctl_urb_pending = 1;
	error = usb_submit_urb(dev->urb_ctl, GFP_KERNEL);
	अगर (error) अणु
		dev->ctl_urb_pending = 0;
		dev_err(&dev->पूर्णांकf->dev, "%s: usb_submit_urb (urb_ctl) failed %d\n",
			__func__, error);
	पूर्ण अन्यथा अणु
		dev->खोलो = 1;
	पूर्ण

	mutex_unlock(&dev->pm_mutex);

	अगर (error)
		usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);

	वापस error;
पूर्ण

अटल व्योम cm109_input_बंद(काष्ठा input_dev *idev)
अणु
	काष्ठा cm109_dev *dev = input_get_drvdata(idev);

	mutex_lock(&dev->pm_mutex);

	/*
	 * Once we are here event delivery is stopped so we
	 * करोn't need to worry about someone starting buzzer
	 * again
	 */
	cm109_stop_traffic(dev);
	dev->खोलो = 0;

	mutex_unlock(&dev->pm_mutex);

	usb_स्वतःpm_put_पूर्णांकerface(dev->पूर्णांकf);
पूर्ण

अटल पूर्णांक cm109_input_ev(काष्ठा input_dev *idev, अचिन्हित पूर्णांक type,
			  अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	काष्ठा cm109_dev *dev = input_get_drvdata(idev);

	dev_dbg(&dev->पूर्णांकf->dev,
		"input_ev: type=%u code=%u value=%d\n", type, code, value);

	अगर (type != EV_SND)
		वापस -EINVAL;

	चयन (code) अणु
	हाल SND_TONE:
	हाल SND_BELL:
		dev->buzzer_state = !!value;
		अगर (!dev->resetting)
			cm109_toggle_buzzer_async(dev);
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण


/******************************************************************************
 * Linux पूर्णांकerface and usb initialisation
 *****************************************************************************/

काष्ठा driver_info अणु
	अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा driver_info info_cm109 = अणु
	.name = "CM109 USB driver",
पूर्ण;

क्रमागत अणु
	VENDOR_ID        = 0x0d8c, /* C-Media Electronics */
	PRODUCT_ID_CM109 = 0x000e, /* CM109 defines range 0x0008 - 0x000f */
पूर्ण;

/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id cm109_usb_table[] = अणु
	अणु
		.match_flags = USB_DEVICE_ID_MATCH_DEVICE |
				USB_DEVICE_ID_MATCH_INT_INFO,
		.idVenकरोr = VENDOR_ID,
		.idProduct = PRODUCT_ID_CM109,
		.bInterfaceClass = USB_CLASS_HID,
		.bInterfaceSubClass = 0,
		.bInterfaceProtocol = 0,
		.driver_info = (kernel_uदीर्घ_t) &info_cm109
	पूर्ण,
	/* you can add more devices here with product ID 0x0008 - 0x000f */
	अणु पूर्ण
पूर्ण;

अटल व्योम cm109_usb_cleanup(काष्ठा cm109_dev *dev)
अणु
	kमुक्त(dev->ctl_req);
	usb_मुक्त_coherent(dev->udev, USB_PKT_LEN, dev->ctl_data, dev->ctl_dma);
	usb_मुक्त_coherent(dev->udev, USB_PKT_LEN, dev->irq_data, dev->irq_dma);

	usb_मुक्त_urb(dev->urb_irq);	/* parameter validation in core/urb */
	usb_मुक्त_urb(dev->urb_ctl);	/* parameter validation in core/urb */
	kमुक्त(dev);
पूर्ण

अटल व्योम cm109_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा cm109_dev *dev = usb_get_पूर्णांकfdata(पूर्णांकerface);

	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
	input_unरेजिस्टर_device(dev->idev);
	cm109_usb_cleanup(dev);
पूर्ण

अटल पूर्णांक cm109_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			   स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा driver_info *nfo = (काष्ठा driver_info *)id->driver_info;
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकerface;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा cm109_dev *dev;
	काष्ठा input_dev *input_dev = शून्य;
	पूर्णांक ret, pipe, i;
	पूर्णांक error = -ENOMEM;

	पूर्णांकerface = पूर्णांकf->cur_altsetting;

	अगर (पूर्णांकerface->desc.bNumEndpoपूर्णांकs < 1)
		वापस -ENODEV;

	endpoपूर्णांक = &पूर्णांकerface->endpoपूर्णांक[0].desc;

	अगर (!usb_endpoपूर्णांक_is_पूर्णांक_in(endpoपूर्णांक))
		वापस -ENODEV;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	spin_lock_init(&dev->ctl_submit_lock);
	mutex_init(&dev->pm_mutex);

	dev->udev = udev;
	dev->पूर्णांकf = पूर्णांकf;

	dev->idev = input_dev = input_allocate_device();
	अगर (!input_dev)
		जाओ err_out;

	/* allocate usb buffers */
	dev->irq_data = usb_alloc_coherent(udev, USB_PKT_LEN,
					   GFP_KERNEL, &dev->irq_dma);
	अगर (!dev->irq_data)
		जाओ err_out;

	dev->ctl_data = usb_alloc_coherent(udev, USB_PKT_LEN,
					   GFP_KERNEL, &dev->ctl_dma);
	अगर (!dev->ctl_data)
		जाओ err_out;

	dev->ctl_req = kदो_स्मृति(माप(*(dev->ctl_req)), GFP_KERNEL);
	अगर (!dev->ctl_req)
		जाओ err_out;

	/* allocate urb काष्ठाures */
	dev->urb_irq = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dev->urb_irq)
		जाओ err_out;

	dev->urb_ctl = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!dev->urb_ctl)
		जाओ err_out;

	/* get a handle to the पूर्णांकerrupt data pipe */
	pipe = usb_rcvपूर्णांकpipe(udev, endpoपूर्णांक->bEndpoपूर्णांकAddress);
	ret = usb_maxpacket(udev, pipe, usb_pipeout(pipe));
	अगर (ret != USB_PKT_LEN)
		dev_err(&पूर्णांकf->dev, "invalid payload size %d, expected %d\n",
			ret, USB_PKT_LEN);

	/* initialise irq urb */
	usb_fill_पूर्णांक_urb(dev->urb_irq, udev, pipe, dev->irq_data,
			 USB_PKT_LEN,
			 cm109_urb_irq_callback, dev, endpoपूर्णांक->bInterval);
	dev->urb_irq->transfer_dma = dev->irq_dma;
	dev->urb_irq->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	dev->urb_irq->dev = udev;

	/* initialise ctl urb */
	dev->ctl_req->bRequestType = USB_TYPE_CLASS | USB_RECIP_INTERFACE |
					USB_सूची_OUT;
	dev->ctl_req->bRequest = USB_REQ_SET_CONFIGURATION;
	dev->ctl_req->wValue = cpu_to_le16(0x200);
	dev->ctl_req->wIndex = cpu_to_le16(पूर्णांकerface->desc.bInterfaceNumber);
	dev->ctl_req->wLength = cpu_to_le16(USB_PKT_LEN);

	usb_fill_control_urb(dev->urb_ctl, udev, usb_sndctrlpipe(udev, 0),
			     (व्योम *)dev->ctl_req, dev->ctl_data, USB_PKT_LEN,
			     cm109_urb_ctl_callback, dev);
	dev->urb_ctl->transfer_dma = dev->ctl_dma;
	dev->urb_ctl->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	dev->urb_ctl->dev = udev;

	/* find out the physical bus location */
	usb_make_path(udev, dev->phys, माप(dev->phys));
	strlcat(dev->phys, "/input0", माप(dev->phys));

	/* रेजिस्टर settings क्रम the input device */
	input_dev->name = nfo->name;
	input_dev->phys = dev->phys;
	usb_to_input_id(udev, &input_dev->id);
	input_dev->dev.parent = &पूर्णांकf->dev;

	input_set_drvdata(input_dev, dev);
	input_dev->खोलो = cm109_input_खोलो;
	input_dev->बंद = cm109_input_बंद;
	input_dev->event = cm109_input_ev;

	input_dev->keycode = dev->keymap;
	input_dev->keycodesize = माप(अचिन्हित अक्षर);
	input_dev->keycodemax = ARRAY_SIZE(dev->keymap);

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_SND);
	input_dev->sndbit[0] = BIT_MASK(SND_BELL) | BIT_MASK(SND_TONE);

	/* रेजिस्टर available key events */
	क्रम (i = 0; i < KEYMAP_SIZE; i++) अणु
		अचिन्हित लघु k = keymap(i);
		dev->keymap[i] = k;
		__set_bit(k, input_dev->keybit);
	पूर्ण
	__clear_bit(KEY_RESERVED, input_dev->keybit);

	error = input_रेजिस्टर_device(dev->idev);
	अगर (error)
		जाओ err_out;

	usb_set_पूर्णांकfdata(पूर्णांकf, dev);

	वापस 0;

 err_out:
	input_मुक्त_device(input_dev);
	cm109_usb_cleanup(dev);
	वापस error;
पूर्ण

अटल पूर्णांक cm109_usb_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा cm109_dev *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	dev_info(&पूर्णांकf->dev, "cm109: usb_suspend (event=%d)\n", message.event);

	mutex_lock(&dev->pm_mutex);
	cm109_stop_traffic(dev);
	mutex_unlock(&dev->pm_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक cm109_usb_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा cm109_dev *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	dev_info(&पूर्णांकf->dev, "cm109: usb_resume\n");

	mutex_lock(&dev->pm_mutex);
	cm109_restore_state(dev);
	mutex_unlock(&dev->pm_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक cm109_usb_pre_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा cm109_dev *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	mutex_lock(&dev->pm_mutex);

	/*
	 * Make sure input events करोn't try to toggle buzzer
	 * जबतक we are resetting
	 */
	dev->resetting = 1;
	smp_wmb();

	cm109_stop_traffic(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक cm109_usb_post_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा cm109_dev *dev = usb_get_पूर्णांकfdata(पूर्णांकf);

	dev->resetting = 0;
	smp_wmb();

	cm109_restore_state(dev);

	mutex_unlock(&dev->pm_mutex);

	वापस 0;
पूर्ण

अटल काष्ठा usb_driver cm109_driver = अणु
	.name		= "cm109",
	.probe		= cm109_usb_probe,
	.disconnect	= cm109_usb_disconnect,
	.suspend	= cm109_usb_suspend,
	.resume		= cm109_usb_resume,
	.reset_resume	= cm109_usb_resume,
	.pre_reset	= cm109_usb_pre_reset,
	.post_reset	= cm109_usb_post_reset,
	.id_table	= cm109_usb_table,
	.supports_स्वतःsuspend = 1,
पूर्ण;

अटल पूर्णांक __init cm109_select_keymap(व्योम)
अणु
	/* Load the phone keymap */
	अगर (!strहालcmp(phone, "kip1000")) अणु
		keymap = keymap_kip1000;
		prपूर्णांकk(KERN_INFO KBUILD_MODNAME ": "
			"Keymap for Komunikate KIP1000 phone loaded\n");
	पूर्ण अन्यथा अगर (!strहालcmp(phone, "gtalk")) अणु
		keymap = keymap_gtalk;
		prपूर्णांकk(KERN_INFO KBUILD_MODNAME ": "
			"Keymap for Genius G-talk phone loaded\n");
	पूर्ण अन्यथा अगर (!strहालcmp(phone, "usbph01")) अणु
		keymap = keymap_usbph01;
		prपूर्णांकk(KERN_INFO KBUILD_MODNAME ": "
			"Keymap for Allied-Telesis Corega USBPH01 phone loaded\n");
	पूर्ण अन्यथा अगर (!strहालcmp(phone, "atcom")) अणु
		keymap = keymap_atcom;
		prपूर्णांकk(KERN_INFO KBUILD_MODNAME ": "
			"Keymap for ATCom AU-100 phone loaded\n");
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR KBUILD_MODNAME ": "
			"Unsupported phone: %s\n", phone);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init cm109_init(व्योम)
अणु
	पूर्णांक err;

	err = cm109_select_keymap();
	अगर (err)
		वापस err;

	err = usb_रेजिस्टर(&cm109_driver);
	अगर (err)
		वापस err;

	prपूर्णांकk(KERN_INFO KBUILD_MODNAME ": "
		DRIVER_DESC ": " DRIVER_VERSION " (C) " DRIVER_AUTHOR "\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास cm109_निकास(व्योम)
अणु
	usb_deरेजिस्टर(&cm109_driver);
पूर्ण

module_init(cm109_init);
module_निकास(cm109_निकास);

MODULE_DEVICE_TABLE(usb, cm109_usb_table);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
