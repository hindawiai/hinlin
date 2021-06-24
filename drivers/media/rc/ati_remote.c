<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  USB ATI Remote support
 *
 *                Copyright (c) 2011, 2012 Anssi Hannula <anssi.hannula@iki.fi>
 *  Version 2.2.0 Copyright (c) 2004 Torrey Hoffman <thoffman@arnor.net>
 *  Version 2.1.1 Copyright (c) 2002 Vladimir Dergachev
 *
 *  This 2.2.0 version is a reग_लिखो / cleanup of the 2.1.1 driver, including
 *  porting to the 2.6 kernel पूर्णांकerfaces, aदीर्घ with other modअगरication
 *  to better match the style of the existing usb/input drivers.  However, the
 *  protocol and hardware handling is essentially unchanged from 2.1.1.
 *
 *  The 2.1.1 driver was derived from the usbati_remote and usbkbd drivers by
 *  Vojtech Pavlik.
 *
 *  Changes:
 *
 *  Feb 2004: Torrey Hoffman <thoffman@arnor.net>
 *            Version 2.2.0
 *  Jun 2004: Torrey Hoffman <thoffman@arnor.net>
 *            Version 2.2.1
 *            Added key repeat support contributed by:
 *                Vincent Vanackere <vanackere@lअगर.univ-mrs.fr>
 *            Added support क्रम the "Lola" remote contributed by:
 *                Seth Cohn <sethcohn@yahoo.com>
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Hardware & software notes
 *
 * These remote controls are distributed by ATI as part of their
 * "All-In-Wonder" video card packages.  The receiver self-identअगरies as a
 * "USB Receiver" with manufacturer "X10 Wireless Technology Inc".
 *
 * The "Lola" remote is available from X10.  See:
 *    http://www.x10.com/products/lola_sg1.hपंचांग
 * The Lola is similar to the ATI remote but has no mouse support, and slightly
 * dअगरferent keys.
 *
 * It is possible to use multiple receivers and remotes on multiple computers
 * simultaneously by configuring them to use specअगरic channels.
 *
 * The RF protocol used by the remote supports 16 distinct channels, 1 to 16.
 * Actually, it may even support more, at least in some revisions of the
 * hardware.
 *
 * Each remote can be configured to transmit on one channel as follows:
 *   - Press and hold the "hand icon" button.
 *   - When the red LED starts to blink, let go of the "hand icon" button.
 *   - When it stops blinking, input the channel code as two digits, from 01
 *     to 16, and press the hand icon again.
 *
 * The timing can be a little tricky.  Try loading the module with debug=1
 * to have the kernel prपूर्णांक out messages about the remote control number
 * and mask.  Note: debugging prपूर्णांकs remote numbers as zero-based hexadecimal.
 *
 * The driver has a "channel_mask" parameter. This biपंचांगask specअगरies which
 * channels will be ignored by the module.  To mask out channels, just add
 * all the 2^channel_number values together.
 *
 * For instance, set channel_mask = 2^4 = 16 (binary 10000) to make ati_remote
 * ignore संकेतs coming from remote controls transmitting on channel 4, but
 * accept all other channels.
 *
 * Or, set channel_mask = 65533, (0xFFFD), and all channels except 1 will be
 * ignored.
 *
 * The शेष is 0 (respond to all channels). Bit 0 and bits 17-32 of this
 * parameter are unused.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/usb/input.h>
#समावेश <linux/रुको.h>
#समावेश <linux/jअगरfies.h>
#समावेश <media/rc-core.h>

/*
 * Module and Version Inक्रमmation, Module Parameters
 */

#घोषणा ATI_REMOTE_VENDOR_ID		0x0bc7
#घोषणा LOLA_REMOTE_PRODUCT_ID		0x0002
#घोषणा LOLA2_REMOTE_PRODUCT_ID		0x0003
#घोषणा ATI_REMOTE_PRODUCT_ID		0x0004
#घोषणा NVIDIA_REMOTE_PRODUCT_ID	0x0005
#घोषणा MEDION_REMOTE_PRODUCT_ID	0x0006
#घोषणा FIREFLY_REMOTE_PRODUCT_ID	0x0008

#घोषणा DRIVER_VERSION		"2.2.1"
#घोषणा DRIVER_AUTHOR           "Torrey Hoffman <thoffman@arnor.net>"
#घोषणा DRIVER_DESC             "ATI/X10 RF USB Remote Control"

#घोषणा NAME_बफ_मानE      80    /* size of product name, path buffers */
#घोषणा DATA_बफ_मानE      63    /* size of URB data buffers */

/*
 * Duplicate event filtering समय.
 * Sequential, identical KIND_FILTERED inमाला_दो with less than
 * FILTER_TIME milliseconds between them are considered as repeat
 * events. The hardware generates 5 events क्रम the first keypress
 * and we have to take this पूर्णांकo account क्रम an accurate repeat
 * behaviour.
 */
#घोषणा FILTER_TIME	60 /* msec */
#घोषणा REPEAT_DELAY	500 /* msec */

अटल अचिन्हित दीर्घ channel_mask;
module_param(channel_mask, uदीर्घ, 0644);
MODULE_PARM_DESC(channel_mask, "Bitmask of remote control channels to ignore");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Enable extra debug messages and information");

अटल पूर्णांक repeat_filter = FILTER_TIME;
module_param(repeat_filter, पूर्णांक, 0644);
MODULE_PARM_DESC(repeat_filter, "Repeat filter time, default = 60 msec");

अटल पूर्णांक repeat_delay = REPEAT_DELAY;
module_param(repeat_delay, पूर्णांक, 0644);
MODULE_PARM_DESC(repeat_delay, "Delay before sending repeats, default = 500 msec");

अटल bool mouse = true;
module_param(mouse, bool, 0444);
MODULE_PARM_DESC(mouse, "Enable mouse device, default = yes");

#घोषणा dbginfo(dev, क्रमmat, arg...) \
	करो अणु अगर (debug) dev_info(dev , क्रमmat , ## arg); पूर्ण जबतक (0)
#अघोषित err
#घोषणा err(क्रमmat, arg...) prपूर्णांकk(KERN_ERR क्रमmat , ## arg)

काष्ठा ati_receiver_type अणु
	/* either शेष_keymap or get_शेष_keymap should be set */
	स्थिर अक्षर *शेष_keymap;
	स्थिर अक्षर *(*get_शेष_keymap)(काष्ठा usb_पूर्णांकerface *पूर्णांकerface);
पूर्ण;

अटल स्थिर अक्षर *get_medion_keymap(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);

	/*
	 * There are many dअगरferent Medion remotes shipped with a receiver
	 * with the same usb id, but the receivers have subtle dअगरferences
	 * in the USB descriptors allowing us to detect them.
	 */

	अगर (udev->manufacturer && udev->product) अणु
		अगर (udev->actconfig->desc.bmAttributes & USB_CONFIG_ATT_WAKEUP) अणु

			अगर (!म_भेद(udev->manufacturer, "X10 Wireless Technology Inc")
			    && !म_भेद(udev->product, "USB Receiver"))
				वापस RC_MAP_MEDION_X10_DIGITAINER;

			अगर (!म_भेद(udev->manufacturer, "X10 WTI")
			    && !म_भेद(udev->product, "RF receiver"))
				वापस RC_MAP_MEDION_X10_OR2X;
		पूर्ण अन्यथा अणु

			 अगर (!म_भेद(udev->manufacturer, "X10 Wireless Technology Inc")
			    && !म_भेद(udev->product, "USB Receiver"))
				वापस RC_MAP_MEDION_X10;
		पूर्ण
	पूर्ण

	dev_info(&पूर्णांकerface->dev,
		 "Unknown Medion X10 receiver, using default ati_remote Medion keymap\n");

	वापस RC_MAP_MEDION_X10;
पूर्ण

अटल स्थिर काष्ठा ati_receiver_type type_ati		= अणु
	.शेष_keymap = RC_MAP_ATI_X10
पूर्ण;
अटल स्थिर काष्ठा ati_receiver_type type_medion	= अणु
	.get_शेष_keymap = get_medion_keymap
पूर्ण;
अटल स्थिर काष्ठा ati_receiver_type type_firefly	= अणु
	.शेष_keymap = RC_MAP_SNAPSTREAM_FIREFLY
पूर्ण;

अटल स्थिर काष्ठा usb_device_id ati_remote_table[] = अणु
	अणु
		USB_DEVICE(ATI_REMOTE_VENDOR_ID, LOLA_REMOTE_PRODUCT_ID),
		.driver_info = (अचिन्हित दीर्घ)&type_ati
	पूर्ण,
	अणु
		USB_DEVICE(ATI_REMOTE_VENDOR_ID, LOLA2_REMOTE_PRODUCT_ID),
		.driver_info = (अचिन्हित दीर्घ)&type_ati
	पूर्ण,
	अणु
		USB_DEVICE(ATI_REMOTE_VENDOR_ID, ATI_REMOTE_PRODUCT_ID),
		.driver_info = (अचिन्हित दीर्घ)&type_ati
	पूर्ण,
	अणु
		USB_DEVICE(ATI_REMOTE_VENDOR_ID, NVIDIA_REMOTE_PRODUCT_ID),
		.driver_info = (अचिन्हित दीर्घ)&type_ati
	पूर्ण,
	अणु
		USB_DEVICE(ATI_REMOTE_VENDOR_ID, MEDION_REMOTE_PRODUCT_ID),
		.driver_info = (अचिन्हित दीर्घ)&type_medion
	पूर्ण,
	अणु
		USB_DEVICE(ATI_REMOTE_VENDOR_ID, FIREFLY_REMOTE_PRODUCT_ID),
		.driver_info = (अचिन्हित दीर्घ)&type_firefly
	पूर्ण,
	अणुपूर्ण	/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, ati_remote_table);

/* Get hi and low bytes of a 16-bits पूर्णांक */
#घोषणा HI(a)	((अचिन्हित अक्षर)((a) >> 8))
#घोषणा LO(a)	((अचिन्हित अक्षर)((a) & 0xff))

#घोषणा SEND_FLAG_IN_PROGRESS	1
#घोषणा SEND_FLAG_COMPLETE	2

/* Device initialization strings */
अटल अक्षर init1[] = अणु 0x01, 0x00, 0x20, 0x14 पूर्ण;
अटल अक्षर init2[] = अणु 0x01, 0x00, 0x20, 0x14, 0x20, 0x20, 0x20 पूर्ण;

काष्ठा ati_remote अणु
	काष्ठा input_dev *idev;
	काष्ठा rc_dev *rdev;
	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;

	काष्ठा urb *irq_urb;
	काष्ठा urb *out_urb;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक_in;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक_out;
	अचिन्हित अक्षर *inbuf;
	अचिन्हित अक्षर *outbuf;
	dma_addr_t inbuf_dma;
	dma_addr_t outbuf_dma;

	अचिन्हित अक्षर old_data;     /* Detect duplicate events */
	अचिन्हित दीर्घ old_jअगरfies;
	अचिन्हित दीर्घ acc_jअगरfies;  /* handle acceleration */
	अचिन्हित दीर्घ first_jअगरfies;

	अचिन्हित पूर्णांक repeat_count;

	अक्षर rc_name[NAME_बफ_मानE];
	अक्षर rc_phys[NAME_बफ_मानE];
	अक्षर mouse_name[NAME_बफ_मानE];
	अक्षर mouse_phys[NAME_बफ_मानE];

	रुको_queue_head_t रुको;
	पूर्णांक send_flags;

	पूर्णांक users; /* 0-2, users are rc and input */
	काष्ठा mutex खोलो_mutex;
पूर्ण;

/* "Kinds" of messages sent from the hardware to the driver. */
#घोषणा KIND_END        0
#घोषणा KIND_LITERAL    1   /* Simply pass to input प्रणाली as EV_KEY */
#घोषणा KIND_FILTERED   2   /* Add artअगरicial key-up events, drop keyrepeats */
#घोषणा KIND_ACCEL      3   /* Translate to EV_REL mouse-move events */

/* Translation table from hardware messages to input events. */
अटल स्थिर काष्ठा अणु
	अचिन्हित अक्षर kind;
	अचिन्हित अक्षर data;	/* Raw key code from remote */
	अचिन्हित लघु code;	/* Input layer translation */
पूर्ण  ati_remote_tbl[] = अणु
	/* Directional control pad axes.  Code is xxyy */
	अणुKIND_ACCEL,    0x70, 0xff00पूर्ण,	/* left */
	अणुKIND_ACCEL,    0x71, 0x0100पूर्ण,	/* right */
	अणुKIND_ACCEL,    0x72, 0x00ffपूर्ण,	/* up */
	अणुKIND_ACCEL,    0x73, 0x0001पूर्ण,	/* करोwn */

	/* Directional control pad diagonals */
	अणुKIND_ACCEL,    0x74, 0xffffपूर्ण,	/* left up */
	अणुKIND_ACCEL,    0x75, 0x01ffपूर्ण,	/* right up */
	अणुKIND_ACCEL,    0x77, 0xff01पूर्ण,	/* left करोwn */
	अणुKIND_ACCEL,    0x76, 0x0101पूर्ण,	/* right करोwn */

	/* "Mouse button" buttons.  The code below uses the fact that the
	 * lsbit of the raw code is a करोwn/up indicator. */
	अणुKIND_LITERAL,  0x78, BTN_LEFTपूर्ण, /* left btn करोwn */
	अणुKIND_LITERAL,  0x79, BTN_LEFTपूर्ण, /* left btn up */
	अणुKIND_LITERAL,  0x7c, BTN_RIGHTपूर्ण,/* right btn करोwn */
	अणुKIND_LITERAL,  0x7d, BTN_RIGHTपूर्ण,/* right btn up */

	/* Artअगरicial "double-click" events are generated by the hardware.
	 * They are mapped to the "side" and "extra" mouse buttons here. */
	अणुKIND_FILTERED, 0x7a, BTN_SIDEपूर्ण, /* left dblclick */
	अणुKIND_FILTERED, 0x7e, BTN_EXTRAपूर्ण,/* right dblclick */

	/* Non-mouse events are handled by rc-core */
	अणुKIND_END, 0x00, 0पूर्ण
पूर्ण;

/*
 * ati_remote_dump_input
 */
अटल व्योम ati_remote_dump(काष्ठा device *dev, अचिन्हित अक्षर *data,
			    अचिन्हित पूर्णांक len)
अणु
	अगर (len == 1) अणु
		अगर (data[0] != (अचिन्हित अक्षर)0xff && data[0] != 0x00)
			dev_warn(dev, "Weird byte 0x%02x\n", data[0]);
	पूर्ण अन्यथा अगर (len == 4)
		dev_warn(dev, "Weird key %*ph\n", 4, data);
	अन्यथा
		dev_warn(dev, "Weird data, len=%d %*ph ...\n", len, 6, data);
पूर्ण

/*
 * ati_remote_खोलो
 */
अटल पूर्णांक ati_remote_खोलो(काष्ठा ati_remote *ati_remote)
अणु
	पूर्णांक err = 0;

	mutex_lock(&ati_remote->खोलो_mutex);

	अगर (ati_remote->users++ != 0)
		जाओ out; /* one was alपढ़ोy active */

	/* On first खोलो, submit the पढ़ो urb which was set up previously. */
	ati_remote->irq_urb->dev = ati_remote->udev;
	अगर (usb_submit_urb(ati_remote->irq_urb, GFP_KERNEL)) अणु
		dev_err(&ati_remote->पूर्णांकerface->dev,
			"%s: usb_submit_urb failed!\n", __func__);
		err = -EIO;
	पूर्ण

out:	mutex_unlock(&ati_remote->खोलो_mutex);
	वापस err;
पूर्ण

/*
 * ati_remote_बंद
 */
अटल व्योम ati_remote_बंद(काष्ठा ati_remote *ati_remote)
अणु
	mutex_lock(&ati_remote->खोलो_mutex);
	अगर (--ati_remote->users == 0)
		usb_समाप्त_urb(ati_remote->irq_urb);
	mutex_unlock(&ati_remote->खोलो_mutex);
पूर्ण

अटल पूर्णांक ati_remote_input_खोलो(काष्ठा input_dev *inputdev)
अणु
	काष्ठा ati_remote *ati_remote = input_get_drvdata(inputdev);
	वापस ati_remote_खोलो(ati_remote);
पूर्ण

अटल व्योम ati_remote_input_बंद(काष्ठा input_dev *inputdev)
अणु
	काष्ठा ati_remote *ati_remote = input_get_drvdata(inputdev);
	ati_remote_बंद(ati_remote);
पूर्ण

अटल पूर्णांक ati_remote_rc_खोलो(काष्ठा rc_dev *rdev)
अणु
	काष्ठा ati_remote *ati_remote = rdev->priv;
	वापस ati_remote_खोलो(ati_remote);
पूर्ण

अटल व्योम ati_remote_rc_बंद(काष्ठा rc_dev *rdev)
अणु
	काष्ठा ati_remote *ati_remote = rdev->priv;
	ati_remote_बंद(ati_remote);
पूर्ण

/*
 * ati_remote_irq_out
 */
अटल व्योम ati_remote_irq_out(काष्ठा urb *urb)
अणु
	काष्ठा ati_remote *ati_remote = urb->context;

	अगर (urb->status) अणु
		dev_dbg(&ati_remote->पूर्णांकerface->dev, "%s: status %d\n",
			__func__, urb->status);
		वापस;
	पूर्ण

	ati_remote->send_flags |= SEND_FLAG_COMPLETE;
	wmb();
	wake_up(&ati_remote->रुको);
पूर्ण

/*
 * ati_remote_sendpacket
 *
 * Used to send device initialization strings
 */
अटल पूर्णांक ati_remote_sendpacket(काष्ठा ati_remote *ati_remote, u16 cmd,
	अचिन्हित अक्षर *data)
अणु
	पूर्णांक retval = 0;

	/* Set up out_urb */
	स_नकल(ati_remote->out_urb->transfer_buffer + 1, data, LO(cmd));
	((अक्षर *) ati_remote->out_urb->transfer_buffer)[0] = HI(cmd);

	ati_remote->out_urb->transfer_buffer_length = LO(cmd) + 1;
	ati_remote->out_urb->dev = ati_remote->udev;
	ati_remote->send_flags = SEND_FLAG_IN_PROGRESS;

	retval = usb_submit_urb(ati_remote->out_urb, GFP_ATOMIC);
	अगर (retval) अणु
		dev_dbg(&ati_remote->पूर्णांकerface->dev,
			 "sendpacket: usb_submit_urb failed: %d\n", retval);
		वापस retval;
	पूर्ण

	रुको_event_समयout(ati_remote->रुको,
		((ati_remote->out_urb->status != -EINPROGRESS) ||
			(ati_remote->send_flags & SEND_FLAG_COMPLETE)),
		HZ);
	usb_समाप्त_urb(ati_remote->out_urb);

	वापस retval;
पूर्ण

काष्ठा accel_बार अणु
	स्थिर अक्षर	value;
	अचिन्हित पूर्णांक	msecs;
पूर्ण;

अटल स्थिर काष्ठा accel_बार accel[] = अणु
	अणु  1,  125 पूर्ण,
	अणु  2,  250 पूर्ण,
	अणु  4,  500 पूर्ण,
	अणु  6, 1000 पूर्ण,
	अणु  9, 1500 पूर्ण,
	अणु 13, 2000 पूर्ण,
	अणु 20,    0 पूर्ण,
पूर्ण;

/*
 * ati_remote_compute_accel
 *
 * Implements acceleration curve क्रम directional control pad
 * If elapsed समय since last event is > 1/4 second, user "stopped",
 * so reset acceleration. Otherwise, user is probably holding the control
 * pad करोwn, so we increase acceleration, ramping up over two seconds to
 * a maximum speed.
 */
अटल पूर्णांक ati_remote_compute_accel(काष्ठा ati_remote *ati_remote)
अणु
	अचिन्हित दीर्घ now = jअगरfies, reset_समय;
	पूर्णांक i;

	reset_समय = msecs_to_jअगरfies(250);

	अगर (समय_after(now, ati_remote->old_jअगरfies + reset_समय)) अणु
		ati_remote->acc_jअगरfies = now;
		वापस 1;
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(accel) - 1; i++) अणु
		अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(accel[i].msecs);

		अगर (समय_beक्रमe(now, ati_remote->acc_jअगरfies + समयout))
			वापस accel[i].value;
	पूर्ण
	वापस accel[i].value;
पूर्ण

/*
 * ati_remote_report_input
 */
अटल व्योम ati_remote_input_report(काष्ठा urb *urb)
अणु
	काष्ठा ati_remote *ati_remote = urb->context;
	अचिन्हित अक्षर *data= ati_remote->inbuf;
	काष्ठा input_dev *dev = ati_remote->idev;
	पूर्णांक index = -1;
	पूर्णांक remote_num;
	अचिन्हित अक्षर scancode;
	u32 wheel_keycode = KEY_RESERVED;
	पूर्णांक i;

	/*
	 * data[0] = 0x14
	 * data[1] = data[2] + data[3] + 0xd5 (a checksum byte)
	 * data[2] = the key code (with toggle bit in MSB with some models)
	 * data[3] = channel << 4 (the low 4 bits must be zero)
	 */

	/* Deal with strange looking inमाला_दो */
	अगर ( urb->actual_length != 4 || data[0] != 0x14 ||
	     data[1] != (अचिन्हित अक्षर)(data[2] + data[3] + 0xD5) ||
	     (data[3] & 0x0f) != 0x00) अणु
		ati_remote_dump(&urb->dev->dev, data, urb->actual_length);
		वापस;
	पूर्ण

	अगर (data[1] != ((data[2] + data[3] + 0xd5) & 0xff)) अणु
		dbginfo(&ati_remote->पूर्णांकerface->dev,
			"wrong checksum in input: %*ph\n", 4, data);
		वापस;
	पूर्ण

	/* Mask unwanted remote channels.  */
	/* note: remote_num is 0-based, channel 1 on remote == 0 here */
	remote_num = (data[3] >> 4) & 0x0f;
	अगर (channel_mask & (1 << (remote_num + 1))) अणु
		dbginfo(&ati_remote->पूर्णांकerface->dev,
			"Masked input from channel 0x%02x: data %02x, mask= 0x%02lx\n",
			remote_num, data[2], channel_mask);
		वापस;
	पूर्ण

	/*
	 * MSB is a toggle code, though only used by some devices
	 * (e.g. SnapStream Firefly)
	 */
	scancode = data[2] & 0x7f;

	dbginfo(&ati_remote->पूर्णांकerface->dev,
		"channel 0x%02x; key data %02x, scancode %02x\n",
		remote_num, data[2], scancode);

	अगर (scancode >= 0x70) अणु
		/*
		 * This is either a mouse or scrollwheel event, depending on
		 * the remote/keymap.
		 * Get the keycode asचिन्हित to scancode 0x78/0x70. If it is
		 * set, assume this is a scrollwheel up/करोwn event.
		 */
		wheel_keycode = rc_g_keycode_from_table(ati_remote->rdev,
							scancode & 0x78);

		अगर (wheel_keycode == KEY_RESERVED) अणु
			/* scrollwheel was not mapped, assume mouse */

			/* Look up event code index in the mouse translation
			 * table.
			 */
			क्रम (i = 0; ati_remote_tbl[i].kind != KIND_END; i++) अणु
				अगर (scancode == ati_remote_tbl[i].data) अणु
					index = i;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (index >= 0 && ati_remote_tbl[index].kind == KIND_LITERAL) अणु
		/*
		 * The lsbit of the raw key code is a करोwn/up flag.
		 * Invert it to match the input layer's conventions.
		 */
		input_event(dev, EV_KEY, ati_remote_tbl[index].code,
			!(data[2] & 1));

		ati_remote->old_jअगरfies = jअगरfies;

	पूर्ण अन्यथा अगर (index < 0 || ati_remote_tbl[index].kind == KIND_FILTERED) अणु
		अचिन्हित दीर्घ now = jअगरfies;

		/* Filter duplicate events which happen "too close" together. */
		अगर (ati_remote->old_data == data[2] &&
		    समय_beक्रमe(now, ati_remote->old_jअगरfies +
				     msecs_to_jअगरfies(repeat_filter))) अणु
			ati_remote->repeat_count++;
		पूर्ण अन्यथा अणु
			ati_remote->repeat_count = 0;
			ati_remote->first_jअगरfies = now;
		पूर्ण

		ati_remote->old_jअगरfies = now;

		/* Ensure we skip at least the 4 first duplicate events
		 * (generated by a single keypress), and जारी skipping
		 * until repeat_delay msecs have passed.
		 */
		अगर (ati_remote->repeat_count > 0 &&
		    (ati_remote->repeat_count < 5 ||
		     समय_beक्रमe(now, ati_remote->first_jअगरfies +
				      msecs_to_jअगरfies(repeat_delay))))
			वापस;

		अगर (index >= 0) अणु
			input_event(dev, EV_KEY, ati_remote_tbl[index].code, 1);
			input_event(dev, EV_KEY, ati_remote_tbl[index].code, 0);
		पूर्ण अन्यथा अणु
			/* Not a mouse event, hand it to rc-core. */
			पूर्णांक count = 1;

			अगर (wheel_keycode != KEY_RESERVED) अणु
				/*
				 * This is a scrollwheel event, send the
				 * scroll up (0x78) / करोwn (0x70) scancode
				 * repeatedly as many बार as indicated by
				 * rest of the scancode.
				 */
				count = (scancode & 0x07) + 1;
				scancode &= 0x78;
			पूर्ण

			जबतक (count--) अणु
				/*
				* We करोn't use the rc-core repeat handling yet as
				* it would cause ghost repeats which would be a
				* regression क्रम this driver.
				*/
				rc_keyकरोwn_noसमयout(ati_remote->rdev,
						     RC_PROTO_OTHER,
						     scancode, data[2]);
				rc_keyup(ati_remote->rdev);
			पूर्ण
			जाओ nosync;
		पूर्ण

	पूर्ण अन्यथा अगर (ati_remote_tbl[index].kind == KIND_ACCEL) अणु
		चिन्हित अक्षर dx = ati_remote_tbl[index].code >> 8;
		चिन्हित अक्षर dy = ati_remote_tbl[index].code & 255;

		/*
		 * Other event kinds are from the directional control pad, and
		 * have an acceleration factor applied to them.  Without this
		 * acceleration, the control pad is mostly unusable.
		 */
		पूर्णांक acc = ati_remote_compute_accel(ati_remote);
		अगर (dx)
			input_report_rel(dev, REL_X, dx * acc);
		अगर (dy)
			input_report_rel(dev, REL_Y, dy * acc);
		ati_remote->old_jअगरfies = jअगरfies;

	पूर्ण अन्यथा अणु
		dev_dbg(&ati_remote->पूर्णांकerface->dev, "ati_remote kind=%d\n",
			ati_remote_tbl[index].kind);
		वापस;
	पूर्ण
	input_sync(dev);
nosync:
	ati_remote->old_data = data[2];
पूर्ण

/*
 * ati_remote_irq_in
 */
अटल व्योम ati_remote_irq_in(काष्ठा urb *urb)
अणु
	काष्ठा ati_remote *ati_remote = urb->context;
	पूर्णांक retval;

	चयन (urb->status) अणु
	हाल 0:			/* success */
		ati_remote_input_report(urb);
		अवरोध;
	हाल -ECONNRESET:	/* unlink */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		dev_dbg(&ati_remote->पूर्णांकerface->dev,
			"%s: urb error status, unlink?\n",
			__func__);
		वापस;
	शेष:		/* error */
		dev_dbg(&ati_remote->पूर्णांकerface->dev,
			"%s: Nonzero urb status %d\n",
			__func__, urb->status);
	पूर्ण

	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(&ati_remote->पूर्णांकerface->dev,
			"%s: usb_submit_urb()=%d\n",
			__func__, retval);
पूर्ण

/*
 * ati_remote_alloc_buffers
 */
अटल पूर्णांक ati_remote_alloc_buffers(काष्ठा usb_device *udev,
				    काष्ठा ati_remote *ati_remote)
अणु
	ati_remote->inbuf = usb_alloc_coherent(udev, DATA_बफ_मानE, GFP_ATOMIC,
					       &ati_remote->inbuf_dma);
	अगर (!ati_remote->inbuf)
		वापस -1;

	ati_remote->outbuf = usb_alloc_coherent(udev, DATA_बफ_मानE, GFP_ATOMIC,
						&ati_remote->outbuf_dma);
	अगर (!ati_remote->outbuf)
		वापस -1;

	ati_remote->irq_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!ati_remote->irq_urb)
		वापस -1;

	ati_remote->out_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!ati_remote->out_urb)
		वापस -1;

	वापस 0;
पूर्ण

/*
 * ati_remote_मुक्त_buffers
 */
अटल व्योम ati_remote_मुक्त_buffers(काष्ठा ati_remote *ati_remote)
अणु
	usb_मुक्त_urb(ati_remote->irq_urb);
	usb_मुक्त_urb(ati_remote->out_urb);

	usb_मुक्त_coherent(ati_remote->udev, DATA_बफ_मानE,
		ati_remote->inbuf, ati_remote->inbuf_dma);

	usb_मुक्त_coherent(ati_remote->udev, DATA_बफ_मानE,
		ati_remote->outbuf, ati_remote->outbuf_dma);
पूर्ण

अटल व्योम ati_remote_input_init(काष्ठा ati_remote *ati_remote)
अणु
	काष्ठा input_dev *idev = ati_remote->idev;
	पूर्णांक i;

	idev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REL);
	idev->keybit[BIT_WORD(BTN_MOUSE)] = BIT_MASK(BTN_LEFT) |
		BIT_MASK(BTN_RIGHT) | BIT_MASK(BTN_SIDE) | BIT_MASK(BTN_EXTRA);
	idev->relbit[0] = BIT_MASK(REL_X) | BIT_MASK(REL_Y);
	क्रम (i = 0; ati_remote_tbl[i].kind != KIND_END; i++)
		अगर (ati_remote_tbl[i].kind == KIND_LITERAL ||
		    ati_remote_tbl[i].kind == KIND_FILTERED)
			__set_bit(ati_remote_tbl[i].code, idev->keybit);

	input_set_drvdata(idev, ati_remote);

	idev->खोलो = ati_remote_input_खोलो;
	idev->बंद = ati_remote_input_बंद;

	idev->name = ati_remote->mouse_name;
	idev->phys = ati_remote->mouse_phys;

	usb_to_input_id(ati_remote->udev, &idev->id);
	idev->dev.parent = &ati_remote->पूर्णांकerface->dev;
पूर्ण

अटल व्योम ati_remote_rc_init(काष्ठा ati_remote *ati_remote)
अणु
	काष्ठा rc_dev *rdev = ati_remote->rdev;

	rdev->priv = ati_remote;
	rdev->allowed_protocols = RC_PROTO_BIT_OTHER;
	rdev->driver_name = "ati_remote";

	rdev->खोलो = ati_remote_rc_खोलो;
	rdev->बंद = ati_remote_rc_बंद;

	rdev->device_name = ati_remote->rc_name;
	rdev->input_phys = ati_remote->rc_phys;

	usb_to_input_id(ati_remote->udev, &rdev->input_id);
	rdev->dev.parent = &ati_remote->पूर्णांकerface->dev;
पूर्ण

अटल पूर्णांक ati_remote_initialize(काष्ठा ati_remote *ati_remote)
अणु
	काष्ठा usb_device *udev = ati_remote->udev;
	पूर्णांक pipe, maxp;

	init_रुकोqueue_head(&ati_remote->रुको);

	/* Set up irq_urb */
	pipe = usb_rcvपूर्णांकpipe(udev, ati_remote->endpoपूर्णांक_in->bEndpoपूर्णांकAddress);
	maxp = usb_maxpacket(udev, pipe, usb_pipeout(pipe));
	maxp = (maxp > DATA_बफ_मानE) ? DATA_बफ_मानE : maxp;

	usb_fill_पूर्णांक_urb(ati_remote->irq_urb, udev, pipe, ati_remote->inbuf,
			 maxp, ati_remote_irq_in, ati_remote,
			 ati_remote->endpoपूर्णांक_in->bInterval);
	ati_remote->irq_urb->transfer_dma = ati_remote->inbuf_dma;
	ati_remote->irq_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	/* Set up out_urb */
	pipe = usb_sndपूर्णांकpipe(udev, ati_remote->endpoपूर्णांक_out->bEndpoपूर्णांकAddress);
	maxp = usb_maxpacket(udev, pipe, usb_pipeout(pipe));
	maxp = (maxp > DATA_बफ_मानE) ? DATA_बफ_मानE : maxp;

	usb_fill_पूर्णांक_urb(ati_remote->out_urb, udev, pipe, ati_remote->outbuf,
			 maxp, ati_remote_irq_out, ati_remote,
			 ati_remote->endpoपूर्णांक_out->bInterval);
	ati_remote->out_urb->transfer_dma = ati_remote->outbuf_dma;
	ati_remote->out_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	/* send initialization strings */
	अगर ((ati_remote_sendpacket(ati_remote, 0x8004, init1)) ||
	    (ati_remote_sendpacket(ati_remote, 0x8007, init2))) अणु
		dev_err(&ati_remote->पूर्णांकerface->dev,
			 "Initializing ati_remote hardware failed.\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * ati_remote_probe
 */
अटल पूर्णांक ati_remote_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
	स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा usb_host_पूर्णांकerface *अगरace_host = पूर्णांकerface->cur_altsetting;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक_in, *endpoपूर्णांक_out;
	काष्ठा ati_receiver_type *type = (काष्ठा ati_receiver_type *)id->driver_info;
	काष्ठा ati_remote *ati_remote;
	काष्ठा input_dev *input_dev;
	काष्ठा rc_dev *rc_dev;
	पूर्णांक err = -ENOMEM;

	अगर (अगरace_host->desc.bNumEndpoपूर्णांकs != 2) अणु
		err("%s: Unexpected desc.bNumEndpoints\n", __func__);
		वापस -ENODEV;
	पूर्ण

	endpoपूर्णांक_in = &अगरace_host->endpoपूर्णांक[0].desc;
	endpoपूर्णांक_out = &अगरace_host->endpoपूर्णांक[1].desc;

	अगर (!usb_endpoपूर्णांक_is_पूर्णांक_in(endpoपूर्णांक_in)) अणु
		err("%s: Unexpected endpoint_in\n", __func__);
		वापस -ENODEV;
	पूर्ण
	अगर (le16_to_cpu(endpoपूर्णांक_in->wMaxPacketSize) == 0) अणु
		err("%s: endpoint_in message size==0? \n", __func__);
		वापस -ENODEV;
	पूर्ण
	अगर (!usb_endpoपूर्णांक_is_पूर्णांक_out(endpoपूर्णांक_out)) अणु
		err("%s: Unexpected endpoint_out\n", __func__);
		वापस -ENODEV;
	पूर्ण

	ati_remote = kzalloc(माप (काष्ठा ati_remote), GFP_KERNEL);
	rc_dev = rc_allocate_device(RC_DRIVER_SCANCODE);
	अगर (!ati_remote || !rc_dev)
		जाओ निकास_मुक्त_dev_rdev;

	/* Allocate URB buffers, URBs */
	अगर (ati_remote_alloc_buffers(udev, ati_remote))
		जाओ निकास_मुक्त_buffers;

	ati_remote->endpoपूर्णांक_in = endpoपूर्णांक_in;
	ati_remote->endpoपूर्णांक_out = endpoपूर्णांक_out;
	ati_remote->udev = udev;
	ati_remote->rdev = rc_dev;
	ati_remote->पूर्णांकerface = पूर्णांकerface;

	usb_make_path(udev, ati_remote->rc_phys, माप(ati_remote->rc_phys));
	strscpy(ati_remote->mouse_phys, ati_remote->rc_phys,
		माप(ati_remote->mouse_phys));

	strlcat(ati_remote->rc_phys, "/input0", माप(ati_remote->rc_phys));
	strlcat(ati_remote->mouse_phys, "/input1", माप(ati_remote->mouse_phys));

	snम_लिखो(ati_remote->rc_name, माप(ati_remote->rc_name), "%s%s%s",
		udev->manufacturer ?: "",
		udev->manufacturer && udev->product ? " " : "",
		udev->product ?: "");

	अगर (!म_माप(ati_remote->rc_name))
		snम_लिखो(ati_remote->rc_name, माप(ati_remote->rc_name),
			DRIVER_DESC "(%04x,%04x)",
			le16_to_cpu(ati_remote->udev->descriptor.idVenकरोr),
			le16_to_cpu(ati_remote->udev->descriptor.idProduct));

	snम_लिखो(ati_remote->mouse_name, माप(ati_remote->mouse_name),
		 "%s mouse", ati_remote->rc_name);

	rc_dev->map_name = RC_MAP_ATI_X10; /* शेष map */

	/* set शेष keymap according to receiver model */
	अगर (type) अणु
		अगर (type->शेष_keymap)
			rc_dev->map_name = type->शेष_keymap;
		अन्यथा अगर (type->get_शेष_keymap)
			rc_dev->map_name = type->get_शेष_keymap(पूर्णांकerface);
	पूर्ण

	ati_remote_rc_init(ati_remote);
	mutex_init(&ati_remote->खोलो_mutex);

	/* Device Hardware Initialization - fills in ati_remote->idev from udev. */
	err = ati_remote_initialize(ati_remote);
	अगर (err)
		जाओ निकास_समाप्त_urbs;

	/* Set up and रेजिस्टर rc device */
	err = rc_रेजिस्टर_device(ati_remote->rdev);
	अगर (err)
		जाओ निकास_समाप्त_urbs;

	/* Set up and रेजिस्टर mouse input device */
	अगर (mouse) अणु
		input_dev = input_allocate_device();
		अगर (!input_dev) अणु
			err = -ENOMEM;
			जाओ निकास_unरेजिस्टर_device;
		पूर्ण

		ati_remote->idev = input_dev;
		ati_remote_input_init(ati_remote);
		err = input_रेजिस्टर_device(input_dev);

		अगर (err)
			जाओ निकास_मुक्त_input_device;
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकerface, ati_remote);
	वापस 0;

 निकास_मुक्त_input_device:
	input_मुक्त_device(input_dev);
 निकास_unरेजिस्टर_device:
	rc_unरेजिस्टर_device(rc_dev);
	rc_dev = शून्य;
 निकास_समाप्त_urbs:
	usb_समाप्त_urb(ati_remote->irq_urb);
	usb_समाप्त_urb(ati_remote->out_urb);
 निकास_मुक्त_buffers:
	ati_remote_मुक्त_buffers(ati_remote);
 निकास_मुक्त_dev_rdev:
	 rc_मुक्त_device(rc_dev);
	kमुक्त(ati_remote);
	वापस err;
पूर्ण

/*
 * ati_remote_disconnect
 */
अटल व्योम ati_remote_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा ati_remote *ati_remote;

	ati_remote = usb_get_पूर्णांकfdata(पूर्णांकerface);
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
	अगर (!ati_remote) अणु
		dev_warn(&पूर्णांकerface->dev, "%s - null device?\n", __func__);
		वापस;
	पूर्ण

	usb_समाप्त_urb(ati_remote->irq_urb);
	usb_समाप्त_urb(ati_remote->out_urb);
	अगर (ati_remote->idev)
		input_unरेजिस्टर_device(ati_remote->idev);
	rc_unरेजिस्टर_device(ati_remote->rdev);
	ati_remote_मुक्त_buffers(ati_remote);
	kमुक्त(ati_remote);
पूर्ण

/* usb specअगरic object to रेजिस्टर with the usb subप्रणाली */
अटल काष्ठा usb_driver ati_remote_driver = अणु
	.name         = "ati_remote",
	.probe        = ati_remote_probe,
	.disconnect   = ati_remote_disconnect,
	.id_table     = ati_remote_table,
पूर्ण;

module_usb_driver(ati_remote_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
