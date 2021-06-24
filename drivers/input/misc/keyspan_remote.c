<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * keyspan_remote: USB driver क्रम the Keyspan DMR
 *
 * Copyright (C) 2005 Zymeta Corporation - Michael Downey (करोwney@zymeta.com)
 *
 * This driver has been put together with the support of Innosys, Inc.
 * and Keyspan, Inc the manufacturers of the Keyspan USB DMR product.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/usb/input.h>

/* Parameters that can be passed to the driver. */
अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0444);
MODULE_PARM_DESC(debug, "Enable extra debug messages and information");

/* Venकरोr and product ids */
#घोषणा USB_KEYSPAN_VENDOR_ID		0x06CD
#घोषणा USB_KEYSPAN_PRODUCT_UIA11	0x0202

/* Defines क्रम converting the data from the remote. */
#घोषणा ZERO		0x18
#घोषणा ZERO_MASK	0x1F	/* 5 bits क्रम a 0 */
#घोषणा ONE		0x3C
#घोषणा ONE_MASK	0x3F	/* 6 bits क्रम a 1 */
#घोषणा SYNC		0x3F80
#घोषणा SYNC_MASK	0x3FFF	/* 14 bits क्रम a SYNC sequence */
#घोषणा STOP		0x00
#घोषणा STOP_MASK	0x1F	/* 5 bits क्रम the STOP sequence */
#घोषणा GAP		0xFF

#घोषणा RECV_SIZE	8	/* The UIA-11 type have a 8 byte limit. */

/*
 * Table that maps the 31 possible keycodes to input keys.
 * Currently there are 15 and 17 button models so RESERVED codes
 * are blank areas in the mapping.
 */
अटल स्थिर अचिन्हित लघु keyspan_key_table[] = अणु
	KEY_RESERVED,		/* 0 is just a place holder. */
	KEY_RESERVED,
	KEY_STOP,
	KEY_PLAYCD,
	KEY_RESERVED,
	KEY_PREVIOUSSONG,
	KEY_REWIND,
	KEY_FORWARD,
	KEY_NEXTSONG,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_PAUSE,
	KEY_VOLUMEUP,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_VOLUMEDOWN,
	KEY_RESERVED,
	KEY_UP,
	KEY_RESERVED,
	KEY_MUTE,
	KEY_LEFT,
	KEY_ENTER,
	KEY_RIGHT,
	KEY_RESERVED,
	KEY_RESERVED,
	KEY_DOWN,
	KEY_RESERVED,
	KEY_KPASTERISK,
	KEY_RESERVED,
	KEY_MENU
पूर्ण;

/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id keyspan_table[] = अणु
	अणु USB_DEVICE(USB_KEYSPAN_VENDOR_ID, USB_KEYSPAN_PRODUCT_UIA11) पूर्ण,
	अणु पूर्ण					/* Terminating entry */
पूर्ण;

/* Structure to store all the real stuff that a remote sends to us. */
काष्ठा keyspan_message अणु
	u16	प्रणाली;
	u8	button;
	u8	toggle;
पूर्ण;

/* Structure used क्रम all the bit testing magic needed to be करोne. */
काष्ठा bit_tester अणु
	u32	tester;
	पूर्णांक	len;
	पूर्णांक	pos;
	पूर्णांक	bits_left;
	u8	buffer[32];
पूर्ण;

/* Structure to hold all of our driver specअगरic stuff */
काष्ठा usb_keyspan अणु
	अक्षर				name[128];
	अक्षर				phys[64];
	अचिन्हित लघु			keymap[ARRAY_SIZE(keyspan_key_table)];
	काष्ठा usb_device		*udev;
	काष्ठा input_dev		*input;
	काष्ठा usb_पूर्णांकerface		*पूर्णांकerface;
	काष्ठा usb_endpoपूर्णांक_descriptor	*in_endpoपूर्णांक;
	काष्ठा urb*			irq_urb;
	पूर्णांक				खोलो;
	dma_addr_t			in_dma;
	अचिन्हित अक्षर			*in_buffer;

	/* variables used to parse messages from remote. */
	काष्ठा bit_tester		data;
	पूर्णांक				stage;
	पूर्णांक				toggle;
पूर्ण;

अटल काष्ठा usb_driver keyspan_driver;

/*
 * Debug routine that prपूर्णांकs out what we've received from the remote.
 */
अटल व्योम keyspan_prपूर्णांक(काष्ठा usb_keyspan* dev) /*अचिन्हित अक्षर* data)*/
अणु
	अक्षर codes[4 * RECV_SIZE];
	पूर्णांक i;

	क्रम (i = 0; i < RECV_SIZE; i++)
		snम_लिखो(codes + i * 3, 4, "%02x ", dev->in_buffer[i]);

	dev_info(&dev->udev->dev, "%s\n", codes);
पूर्ण

/*
 * Routine that manages the bit_tester काष्ठाure.  It makes sure that there are
 * at least bits_needed bits loaded पूर्णांकo the tester.
 */
अटल पूर्णांक keyspan_load_tester(काष्ठा usb_keyspan* dev, पूर्णांक bits_needed)
अणु
	अगर (dev->data.bits_left >= bits_needed)
		वापस 0;

	/*
	 * Somehow we've missed the last message. The message will be repeated
	 * though so it's not too big a deal
	 */
	अगर (dev->data.pos >= dev->data.len) अणु
		dev_dbg(&dev->पूर्णांकerface->dev,
			"%s - Error ran out of data. pos: %d, len: %d\n",
			__func__, dev->data.pos, dev->data.len);
		वापस -1;
	पूर्ण

	/* Load as much as we can पूर्णांकo the tester. */
	जबतक ((dev->data.bits_left + 7 < (माप(dev->data.tester) * 8)) &&
	       (dev->data.pos < dev->data.len)) अणु
		dev->data.tester += (dev->data.buffer[dev->data.pos++] << dev->data.bits_left);
		dev->data.bits_left += 8;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम keyspan_report_button(काष्ठा usb_keyspan *remote, पूर्णांक button, पूर्णांक press)
अणु
	काष्ठा input_dev *input = remote->input;

	input_event(input, EV_MSC, MSC_SCAN, button);
	input_report_key(input, remote->keymap[button], press);
	input_sync(input);
पूर्ण

/*
 * Routine that handles all the logic needed to parse out the message from the remote.
 */
अटल व्योम keyspan_check_data(काष्ठा usb_keyspan *remote)
अणु
	पूर्णांक i;
	पूर्णांक found = 0;
	काष्ठा keyspan_message message;

	चयन(remote->stage) अणु
	हाल 0:
		/*
		 * In stage 0 we want to find the start of a message.  The remote sends a 0xFF as filler.
		 * So the first byte that isn't a FF should be the start of a new message.
		 */
		क्रम (i = 0; i < RECV_SIZE && remote->in_buffer[i] == GAP; ++i);

		अगर (i < RECV_SIZE) अणु
			स_नकल(remote->data.buffer, remote->in_buffer, RECV_SIZE);
			remote->data.len = RECV_SIZE;
			remote->data.pos = 0;
			remote->data.tester = 0;
			remote->data.bits_left = 0;
			remote->stage = 1;
		पूर्ण
		अवरोध;

	हाल 1:
		/*
		 * Stage 1 we should have 16 bytes and should be able to detect a
		 * SYNC.  The SYNC is 14 bits, 7 0's and then 7 1's.
		 */
		स_नकल(remote->data.buffer + remote->data.len, remote->in_buffer, RECV_SIZE);
		remote->data.len += RECV_SIZE;

		found = 0;
		जबतक ((remote->data.bits_left >= 14 || remote->data.pos < remote->data.len) && !found) अणु
			क्रम (i = 0; i < 8; ++i) अणु
				अगर (keyspan_load_tester(remote, 14) != 0) अणु
					remote->stage = 0;
					वापस;
				पूर्ण

				अगर ((remote->data.tester & SYNC_MASK) == SYNC) अणु
					remote->data.tester = remote->data.tester >> 14;
					remote->data.bits_left -= 14;
					found = 1;
					अवरोध;
				पूर्ण अन्यथा अणु
					remote->data.tester = remote->data.tester >> 1;
					--remote->data.bits_left;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (!found) अणु
			remote->stage = 0;
			remote->data.len = 0;
		पूर्ण अन्यथा अणु
			remote->stage = 2;
		पूर्ण
		अवरोध;

	हाल 2:
		/*
		 * Stage 2 we should have 24 bytes which will be enough क्रम a full
		 * message.  We need to parse out the प्रणाली code, button code,
		 * toggle code, and stop.
		 */
		स_नकल(remote->data.buffer + remote->data.len, remote->in_buffer, RECV_SIZE);
		remote->data.len += RECV_SIZE;

		message.प्रणाली = 0;
		क्रम (i = 0; i < 9; i++) अणु
			keyspan_load_tester(remote, 6);

			अगर ((remote->data.tester & ZERO_MASK) == ZERO) अणु
				message.प्रणाली = message.प्रणाली << 1;
				remote->data.tester = remote->data.tester >> 5;
				remote->data.bits_left -= 5;
			पूर्ण अन्यथा अगर ((remote->data.tester & ONE_MASK) == ONE) अणु
				message.प्रणाली = (message.प्रणाली << 1) + 1;
				remote->data.tester = remote->data.tester >> 6;
				remote->data.bits_left -= 6;
			पूर्ण अन्यथा अणु
				dev_err(&remote->पूर्णांकerface->dev,
					"%s - Unknown sequence found in system data.\n",
					__func__);
				remote->stage = 0;
				वापस;
			पूर्ण
		पूर्ण

		message.button = 0;
		क्रम (i = 0; i < 5; i++) अणु
			keyspan_load_tester(remote, 6);

			अगर ((remote->data.tester & ZERO_MASK) == ZERO) अणु
				message.button = message.button << 1;
				remote->data.tester = remote->data.tester >> 5;
				remote->data.bits_left -= 5;
			पूर्ण अन्यथा अगर ((remote->data.tester & ONE_MASK) == ONE) अणु
				message.button = (message.button << 1) + 1;
				remote->data.tester = remote->data.tester >> 6;
				remote->data.bits_left -= 6;
			पूर्ण अन्यथा अणु
				dev_err(&remote->पूर्णांकerface->dev,
					"%s - Unknown sequence found in button data.\n",
					__func__);
				remote->stage = 0;
				वापस;
			पूर्ण
		पूर्ण

		keyspan_load_tester(remote, 6);
		अगर ((remote->data.tester & ZERO_MASK) == ZERO) अणु
			message.toggle = 0;
			remote->data.tester = remote->data.tester >> 5;
			remote->data.bits_left -= 5;
		पूर्ण अन्यथा अगर ((remote->data.tester & ONE_MASK) == ONE) अणु
			message.toggle = 1;
			remote->data.tester = remote->data.tester >> 6;
			remote->data.bits_left -= 6;
		पूर्ण अन्यथा अणु
			dev_err(&remote->पूर्णांकerface->dev,
				"%s - Error in message, invalid toggle.\n",
				__func__);
			remote->stage = 0;
			वापस;
		पूर्ण

		keyspan_load_tester(remote, 5);
		अगर ((remote->data.tester & STOP_MASK) == STOP) अणु
			remote->data.tester = remote->data.tester >> 5;
			remote->data.bits_left -= 5;
		पूर्ण अन्यथा अणु
			dev_err(&remote->पूर्णांकerface->dev,
				"Bad message received, no stop bit found.\n");
		पूर्ण

		dev_dbg(&remote->पूर्णांकerface->dev,
			"%s found valid message: system: %d, button: %d, toggle: %d\n",
			__func__, message.प्रणाली, message.button, message.toggle);

		अगर (message.toggle != remote->toggle) अणु
			keyspan_report_button(remote, message.button, 1);
			keyspan_report_button(remote, message.button, 0);
			remote->toggle = message.toggle;
		पूर्ण

		remote->stage = 0;
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Routine क्रम sending all the initialization messages to the remote.
 */
अटल पूर्णांक keyspan_setup(काष्ठा usb_device* dev)
अणु
	पूर्णांक retval = 0;

	retval = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
				 0x11, 0x40, 0x5601, 0x0, शून्य, 0,
				 USB_CTRL_SET_TIMEOUT);
	अगर (retval) अणु
		dev_dbg(&dev->dev, "%s - failed to set bit rate due to error: %d\n",
			__func__, retval);
		वापस(retval);
	पूर्ण

	retval = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
				 0x44, 0x40, 0x0, 0x0, शून्य, 0,
				 USB_CTRL_SET_TIMEOUT);
	अगर (retval) अणु
		dev_dbg(&dev->dev, "%s - failed to set resume sensitivity due to error: %d\n",
			__func__, retval);
		वापस(retval);
	पूर्ण

	retval = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
				 0x22, 0x40, 0x0, 0x0, शून्य, 0,
				 USB_CTRL_SET_TIMEOUT);
	अगर (retval) अणु
		dev_dbg(&dev->dev, "%s - failed to turn receive on due to error: %d\n",
			__func__, retval);
		वापस(retval);
	पूर्ण

	dev_dbg(&dev->dev, "%s - Setup complete.\n", __func__);
	वापस(retval);
पूर्ण

/*
 * Routine used to handle a new message that has come in.
 */
अटल व्योम keyspan_irq_recv(काष्ठा urb *urb)
अणु
	काष्ठा usb_keyspan *dev = urb->context;
	पूर्णांक retval;

	/* Check our status in हाल we need to bail out early. */
	चयन (urb->status) अणु
	हाल 0:
		अवरोध;

	/* Device went away so करोn't keep trying to पढ़ो from it. */
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;

	शेष:
		जाओ resubmit;
	पूर्ण

	अगर (debug)
		keyspan_prपूर्णांक(dev);

	keyspan_check_data(dev);

resubmit:
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(&dev->पूर्णांकerface->dev,
			"%s - usb_submit_urb failed with result: %d\n",
			__func__, retval);
पूर्ण

अटल पूर्णांक keyspan_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा usb_keyspan *remote = input_get_drvdata(dev);

	remote->irq_urb->dev = remote->udev;
	अगर (usb_submit_urb(remote->irq_urb, GFP_KERNEL))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम keyspan_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा usb_keyspan *remote = input_get_drvdata(dev);

	usb_समाप्त_urb(remote->irq_urb);
पूर्ण

अटल काष्ठा usb_endpoपूर्णांक_descriptor *keyspan_get_in_endpoपूर्णांक(काष्ठा usb_host_पूर्णांकerface *अगरace)
अणु

	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	पूर्णांक i;

	क्रम (i = 0; i < अगरace->desc.bNumEndpoपूर्णांकs; ++i) अणु
		endpoपूर्णांक = &अगरace->endpoपूर्णांक[i].desc;

		अगर (usb_endpoपूर्णांक_is_पूर्णांक_in(endpoपूर्णांक)) अणु
			/* we found our पूर्णांकerrupt in endpoपूर्णांक */
			वापस endpoपूर्णांक;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Routine that sets up the driver to handle a specअगरic USB device detected on the bus.
 */
अटल पूर्णांक keyspan_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा usb_keyspan *remote;
	काष्ठा input_dev *input_dev;
	पूर्णांक i, error;

	endpoपूर्णांक = keyspan_get_in_endpoपूर्णांक(पूर्णांकerface->cur_altsetting);
	अगर (!endpoपूर्णांक)
		वापस -ENODEV;

	remote = kzalloc(माप(*remote), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!remote || !input_dev) अणु
		error = -ENOMEM;
		जाओ fail1;
	पूर्ण

	remote->udev = udev;
	remote->input = input_dev;
	remote->पूर्णांकerface = पूर्णांकerface;
	remote->in_endpoपूर्णांक = endpoपूर्णांक;
	remote->toggle = -1;	/* Set to -1 so we will always not match the toggle from the first remote message. */

	remote->in_buffer = usb_alloc_coherent(udev, RECV_SIZE, GFP_KERNEL, &remote->in_dma);
	अगर (!remote->in_buffer) अणु
		error = -ENOMEM;
		जाओ fail1;
	पूर्ण

	remote->irq_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!remote->irq_urb) अणु
		error = -ENOMEM;
		जाओ fail2;
	पूर्ण

	error = keyspan_setup(udev);
	अगर (error) अणु
		error = -ENODEV;
		जाओ fail3;
	पूर्ण

	अगर (udev->manufacturer)
		strlcpy(remote->name, udev->manufacturer, माप(remote->name));

	अगर (udev->product) अणु
		अगर (udev->manufacturer)
			strlcat(remote->name, " ", माप(remote->name));
		strlcat(remote->name, udev->product, माप(remote->name));
	पूर्ण

	अगर (!म_माप(remote->name))
		snम_लिखो(remote->name, माप(remote->name),
			 "USB Keyspan Remote %04x:%04x",
			 le16_to_cpu(udev->descriptor.idVenकरोr),
			 le16_to_cpu(udev->descriptor.idProduct));

	usb_make_path(udev, remote->phys, माप(remote->phys));
	strlcat(remote->phys, "/input0", माप(remote->phys));
	स_नकल(remote->keymap, keyspan_key_table, माप(remote->keymap));

	input_dev->name = remote->name;
	input_dev->phys = remote->phys;
	usb_to_input_id(udev, &input_dev->id);
	input_dev->dev.parent = &पूर्णांकerface->dev;
	input_dev->keycode = remote->keymap;
	input_dev->keycodesize = माप(अचिन्हित लघु);
	input_dev->keycodemax = ARRAY_SIZE(remote->keymap);

	input_set_capability(input_dev, EV_MSC, MSC_SCAN);
	__set_bit(EV_KEY, input_dev->evbit);
	क्रम (i = 0; i < ARRAY_SIZE(keyspan_key_table); i++)
		__set_bit(keyspan_key_table[i], input_dev->keybit);
	__clear_bit(KEY_RESERVED, input_dev->keybit);

	input_set_drvdata(input_dev, remote);

	input_dev->खोलो = keyspan_खोलो;
	input_dev->बंद = keyspan_बंद;

	/*
	 * Initialize the URB to access the device.
	 * The urb माला_लो sent to the device in keyspan_खोलो()
	 */
	usb_fill_पूर्णांक_urb(remote->irq_urb,
			 remote->udev,
			 usb_rcvपूर्णांकpipe(remote->udev, endpoपूर्णांक->bEndpoपूर्णांकAddress),
			 remote->in_buffer, RECV_SIZE, keyspan_irq_recv, remote,
			 endpoपूर्णांक->bInterval);
	remote->irq_urb->transfer_dma = remote->in_dma;
	remote->irq_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	/* we can रेजिस्टर the device now, as it is पढ़ोy */
	error = input_रेजिस्टर_device(remote->input);
	अगर (error)
		जाओ fail3;

	/* save our data poपूर्णांकer in this पूर्णांकerface device */
	usb_set_पूर्णांकfdata(पूर्णांकerface, remote);

	वापस 0;

 fail3:	usb_मुक्त_urb(remote->irq_urb);
 fail2:	usb_मुक्त_coherent(udev, RECV_SIZE, remote->in_buffer, remote->in_dma);
 fail1:	kमुक्त(remote);
	input_मुक्त_device(input_dev);

	वापस error;
पूर्ण

/*
 * Routine called when a device is disconnected from the USB.
 */
अटल व्योम keyspan_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_keyspan *remote;

	remote = usb_get_पूर्णांकfdata(पूर्णांकerface);
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);

	अगर (remote) अणु	/* We have a valid driver काष्ठाure so clean up everything we allocated. */
		input_unरेजिस्टर_device(remote->input);
		usb_समाप्त_urb(remote->irq_urb);
		usb_मुक्त_urb(remote->irq_urb);
		usb_मुक्त_coherent(remote->udev, RECV_SIZE, remote->in_buffer, remote->in_dma);
		kमुक्त(remote);
	पूर्ण
पूर्ण

/*
 * Standard driver set up sections
 */
अटल काष्ठा usb_driver keyspan_driver =
अणु
	.name =		"keyspan_remote",
	.probe =	keyspan_probe,
	.disconnect =	keyspan_disconnect,
	.id_table =	keyspan_table
पूर्ण;

module_usb_driver(keyspan_driver);

MODULE_DEVICE_TABLE(usb, keyspan_table);
MODULE_AUTHOR("Michael Downey <downey@zymeta.com>");
MODULE_DESCRIPTION("Driver for the USB Keyspan remote control.");
MODULE_LICENSE("GPL");
