<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * A driver क्रम the Grअगरfin Technology, Inc. "PowerMate" USB controller dial.
 *
 * v1.1, (c)2002 William R Sowerbutts <will@sowerbutts.com>
 *
 * This device is a anodised aluminium knob which connects over USB. It can measure
 * घड़ीwise and antiघड़ीwise rotation. The dial also acts as a pushbutton with
 * a spring क्रम स्वतःmatic release. The base contains a pair of LEDs which illuminate
 * the translucent base. It rotates without limit and reports its relative rotation
 * back to the host when polled by the USB controller.
 *
 * Testing with the knob I have has shown that it measures approximately 94 "clicks"
 * क्रम one full rotation. Testing with my High Speed Rotation Actuator (ok, it was
 * a variable speed cordless electric drill) has shown that the device can measure
 * speeds of up to 7 clicks either घड़ीwise or antiघड़ीwise between pollings from
 * the host. If it counts more than 7 clicks beक्रमe it is polled, it will wrap back
 * to zero and start counting again. This was at quite high speed, however, almost
 * certainly faster than the human hand could turn it. Grअगरfin say that it loses a
 * pulse or two on a direction change; the granularity is so fine that I never
 * noticed this in practice.
 *
 * The device's microcontroller can be programmed to set the LED to either a स्थिरant
 * पूर्णांकensity, or to a rhythmic pulsing. Several patterns and speeds are available.
 *
 * Grअगरfin were very happy to provide करोcumentation and मुक्त hardware क्रम development.
 *
 * Some userspace tools are available on the web: http://sowerbutts.com/घातermate/
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/usb/input.h>

#घोषणा POWERMATE_VENDOR	0x077d	/* Grअगरfin Technology, Inc. */
#घोषणा POWERMATE_PRODUCT_NEW	0x0410	/* Grअगरfin PowerMate */
#घोषणा POWERMATE_PRODUCT_OLD	0x04AA	/* Grअगरfin soundKnob */

#घोषणा CONTOUR_VENDOR		0x05f3	/* Contour Design, Inc. */
#घोषणा CONTOUR_JOG		0x0240	/* Jog and Shuttle */

/* these are the command codes we send to the device */
#घोषणा SET_STATIC_BRIGHTNESS  0x01
#घोषणा SET_PULSE_ASLEEP       0x02
#घोषणा SET_PULSE_AWAKE        0x03
#घोषणा SET_PULSE_MODE         0x04

/* these refer to bits in the घातermate_device's requires_update field. */
#घोषणा UPDATE_STATIC_BRIGHTNESS (1<<0)
#घोषणा UPDATE_PULSE_ASLEEP      (1<<1)
#घोषणा UPDATE_PULSE_AWAKE       (1<<2)
#घोषणा UPDATE_PULSE_MODE        (1<<3)

/* at least two versions of the hardware exist, with dअगरfering payload
   sizes. the first three bytes always contain the "interesting" data in
   the relevant क्रमmat. */
#घोषणा POWERMATE_PAYLOAD_SIZE_MAX 6
#घोषणा POWERMATE_PAYLOAD_SIZE_MIN 3
काष्ठा घातermate_device अणु
	चिन्हित अक्षर *data;
	dma_addr_t data_dma;
	काष्ठा urb *irq, *config;
	काष्ठा usb_ctrlrequest *configcr;
	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा input_dev *input;
	spinlock_t lock;
	पूर्णांक अटल_brightness;
	पूर्णांक pulse_speed;
	पूर्णांक pulse_table;
	पूर्णांक pulse_asleep;
	पूर्णांक pulse_awake;
	पूर्णांक requires_update; // physical settings which are out of sync
	अक्षर phys[64];
पूर्ण;

अटल अक्षर pm_name_घातermate[] = "Griffin PowerMate";
अटल अक्षर pm_name_soundknob[] = "Griffin SoundKnob";

अटल व्योम घातermate_config_complete(काष्ठा urb *urb);

/* Callback क्रम data arriving from the PowerMate over the USB पूर्णांकerrupt pipe */
अटल व्योम घातermate_irq(काष्ठा urb *urb)
अणु
	काष्ठा घातermate_device *pm = urb->context;
	काष्ठा device *dev = &pm->पूर्णांकf->dev;
	पूर्णांक retval;

	चयन (urb->status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(dev, "%s - urb shutting down with status: %d\n",
			__func__, urb->status);
		वापस;
	शेष:
		dev_dbg(dev, "%s - nonzero urb status received: %d\n",
			__func__, urb->status);
		जाओ निकास;
	पूर्ण

	/* handle updates to device state */
	input_report_key(pm->input, BTN_0, pm->data[0] & 0x01);
	input_report_rel(pm->input, REL_DIAL, pm->data[1]);
	input_sync(pm->input);

निकास:
	retval = usb_submit_urb (urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(dev, "%s - usb_submit_urb failed with result: %d\n",
			__func__, retval);
पूर्ण

/* Decide अगर we need to issue a control message and करो so. Must be called with pm->lock taken */
अटल व्योम घातermate_sync_state(काष्ठा घातermate_device *pm)
अणु
	अगर (pm->requires_update == 0)
		वापस; /* no updates are required */
	अगर (pm->config->status == -EINPROGRESS)
		वापस; /* an update is alपढ़ोy in progress; it'll issue this update when it completes */

	अगर (pm->requires_update & UPDATE_PULSE_ASLEEP)अणु
		pm->configcr->wValue = cpu_to_le16( SET_PULSE_ASLEEP );
		pm->configcr->wIndex = cpu_to_le16( pm->pulse_asleep ? 1 : 0 );
		pm->requires_update &= ~UPDATE_PULSE_ASLEEP;
	पूर्णअन्यथा अगर (pm->requires_update & UPDATE_PULSE_AWAKE)अणु
		pm->configcr->wValue = cpu_to_le16( SET_PULSE_AWAKE );
		pm->configcr->wIndex = cpu_to_le16( pm->pulse_awake ? 1 : 0 );
		pm->requires_update &= ~UPDATE_PULSE_AWAKE;
	पूर्णअन्यथा अगर (pm->requires_update & UPDATE_PULSE_MODE)अणु
		पूर्णांक op, arg;
		/* the घातermate takes an operation and an argument क्रम its pulse algorithm.
		   the operation can be:
		   0: भागide the speed
		   1: pulse at normal speed
		   2: multiply the speed
		   the argument only has an effect क्रम operations 0 and 2, and ranges between
		   1 (least effect) to 255 (maximum effect).

		   thus, several states are equivalent and are coalesced पूर्णांकo one state.

		   we map this onto a range from 0 to 510, with:
		   0 -- 254    -- use भागide (0 = slowest)
		   255         -- use normal speed
		   256 -- 510  -- use multiple (510 = fastest).

		   Only values of 'arg' quite बंद to 255 are particularly useful/spectacular.
		*/
		अगर (pm->pulse_speed < 255) अणु
			op = 0;                   // भागide
			arg = 255 - pm->pulse_speed;
		पूर्ण अन्यथा अगर (pm->pulse_speed > 255) अणु
			op = 2;                   // multiply
			arg = pm->pulse_speed - 255;
		पूर्ण अन्यथा अणु
			op = 1;                   // normal speed
			arg = 0;                  // can be any value
		पूर्ण
		pm->configcr->wValue = cpu_to_le16( (pm->pulse_table << 8) | SET_PULSE_MODE );
		pm->configcr->wIndex = cpu_to_le16( (arg << 8) | op );
		pm->requires_update &= ~UPDATE_PULSE_MODE;
	पूर्ण अन्यथा अगर (pm->requires_update & UPDATE_STATIC_BRIGHTNESS) अणु
		pm->configcr->wValue = cpu_to_le16( SET_STATIC_BRIGHTNESS );
		pm->configcr->wIndex = cpu_to_le16( pm->अटल_brightness );
		pm->requires_update &= ~UPDATE_STATIC_BRIGHTNESS;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "powermate: unknown update required");
		pm->requires_update = 0; /* fudge the bug */
		वापस;
	पूर्ण

/*	prपूर्णांकk("powermate: %04x %04x\n", pm->configcr->wValue, pm->configcr->wIndex); */

	pm->configcr->bRequestType = 0x41; /* venकरोr request */
	pm->configcr->bRequest = 0x01;
	pm->configcr->wLength = 0;

	usb_fill_control_urb(pm->config, pm->udev, usb_sndctrlpipe(pm->udev, 0),
			     (व्योम *) pm->configcr, शून्य, 0,
			     घातermate_config_complete, pm);

	अगर (usb_submit_urb(pm->config, GFP_ATOMIC))
		prपूर्णांकk(KERN_ERR "powermate: usb_submit_urb(config) failed");
पूर्ण

/* Called when our asynchronous control message completes. We may need to issue another immediately */
अटल व्योम घातermate_config_complete(काष्ठा urb *urb)
अणु
	काष्ठा घातermate_device *pm = urb->context;
	अचिन्हित दीर्घ flags;

	अगर (urb->status)
		prपूर्णांकk(KERN_ERR "powermate: config urb returned %d\n", urb->status);

	spin_lock_irqsave(&pm->lock, flags);
	घातermate_sync_state(pm);
	spin_unlock_irqrestore(&pm->lock, flags);
पूर्ण

/* Set the LED up as described and begin the sync with the hardware अगर required */
अटल व्योम घातermate_pulse_led(काष्ठा घातermate_device *pm, पूर्णांक अटल_brightness, पूर्णांक pulse_speed,
				पूर्णांक pulse_table, पूर्णांक pulse_asleep, पूर्णांक pulse_awake)
अणु
	अचिन्हित दीर्घ flags;

	अगर (pulse_speed < 0)
		pulse_speed = 0;
	अगर (pulse_table < 0)
		pulse_table = 0;
	अगर (pulse_speed > 510)
		pulse_speed = 510;
	अगर (pulse_table > 2)
		pulse_table = 2;

	pulse_asleep = !!pulse_asleep;
	pulse_awake = !!pulse_awake;


	spin_lock_irqsave(&pm->lock, flags);

	/* mark state updates which are required */
	अगर (अटल_brightness != pm->अटल_brightness) अणु
		pm->अटल_brightness = अटल_brightness;
		pm->requires_update |= UPDATE_STATIC_BRIGHTNESS;
	पूर्ण
	अगर (pulse_asleep != pm->pulse_asleep) अणु
		pm->pulse_asleep = pulse_asleep;
		pm->requires_update |= (UPDATE_PULSE_ASLEEP | UPDATE_STATIC_BRIGHTNESS);
	पूर्ण
	अगर (pulse_awake != pm->pulse_awake) अणु
		pm->pulse_awake = pulse_awake;
		pm->requires_update |= (UPDATE_PULSE_AWAKE | UPDATE_STATIC_BRIGHTNESS);
	पूर्ण
	अगर (pulse_speed != pm->pulse_speed || pulse_table != pm->pulse_table) अणु
		pm->pulse_speed = pulse_speed;
		pm->pulse_table = pulse_table;
		pm->requires_update |= UPDATE_PULSE_MODE;
	पूर्ण

	घातermate_sync_state(pm);

	spin_unlock_irqrestore(&pm->lock, flags);
पूर्ण

/* Callback from the Input layer when an event arrives from userspace to configure the LED */
अटल पूर्णांक घातermate_input_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code, पूर्णांक _value)
अणु
	अचिन्हित पूर्णांक command = (अचिन्हित पूर्णांक)_value;
	काष्ठा घातermate_device *pm = input_get_drvdata(dev);

	अगर (type == EV_MSC && code == MSC_PULSELED)अणु
		/*
		    bits  0- 7: 8 bits: LED brightness
		    bits  8-16: 9 bits: pulsing speed modअगरier (0 ... 510); 0-254 = slower, 255 = standard, 256-510 = faster.
		    bits 17-18: 2 bits: pulse table (0, 1, 2 valid)
		    bit     19: 1 bit : pulse whilst asleep?
		    bit     20: 1 bit : pulse स्थिरantly?
		*/
		पूर्णांक अटल_brightness = command & 0xFF;   // bits 0-7
		पूर्णांक pulse_speed = (command >> 8) & 0x1FF; // bits 8-16
		पूर्णांक pulse_table = (command >> 17) & 0x3;  // bits 17-18
		पूर्णांक pulse_asleep = (command >> 19) & 0x1; // bit 19
		पूर्णांक pulse_awake  = (command >> 20) & 0x1; // bit 20

		घातermate_pulse_led(pm, अटल_brightness, pulse_speed, pulse_table, pulse_asleep, pulse_awake);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक घातermate_alloc_buffers(काष्ठा usb_device *udev, काष्ठा घातermate_device *pm)
अणु
	pm->data = usb_alloc_coherent(udev, POWERMATE_PAYLOAD_SIZE_MAX,
				      GFP_KERNEL, &pm->data_dma);
	अगर (!pm->data)
		वापस -1;

	pm->configcr = kदो_स्मृति(माप(*(pm->configcr)), GFP_KERNEL);
	अगर (!pm->configcr)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम घातermate_मुक्त_buffers(काष्ठा usb_device *udev, काष्ठा घातermate_device *pm)
अणु
	usb_मुक्त_coherent(udev, POWERMATE_PAYLOAD_SIZE_MAX,
			  pm->data, pm->data_dma);
	kमुक्त(pm->configcr);
पूर्ण

/* Called whenever a USB device matching one in our supported devices table is connected */
अटल पूर्णांक घातermate_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev (पूर्णांकf);
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकerface;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा घातermate_device *pm;
	काष्ठा input_dev *input_dev;
	पूर्णांक pipe, maxp;
	पूर्णांक error = -ENOMEM;

	पूर्णांकerface = पूर्णांकf->cur_altsetting;
	अगर (पूर्णांकerface->desc.bNumEndpoपूर्णांकs < 1)
		वापस -EINVAL;

	endpoपूर्णांक = &पूर्णांकerface->endpoपूर्णांक[0].desc;
	अगर (!usb_endpoपूर्णांक_is_पूर्णांक_in(endpoपूर्णांक))
		वापस -EIO;

	usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
		0x0a, USB_TYPE_CLASS | USB_RECIP_INTERFACE,
		0, पूर्णांकerface->desc.bInterfaceNumber, शून्य, 0,
		USB_CTRL_SET_TIMEOUT);

	pm = kzalloc(माप(काष्ठा घातermate_device), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!pm || !input_dev)
		जाओ fail1;

	अगर (घातermate_alloc_buffers(udev, pm))
		जाओ fail2;

	pm->irq = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!pm->irq)
		जाओ fail2;

	pm->config = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!pm->config)
		जाओ fail3;

	pm->udev = udev;
	pm->पूर्णांकf = पूर्णांकf;
	pm->input = input_dev;

	usb_make_path(udev, pm->phys, माप(pm->phys));
	strlcat(pm->phys, "/input0", माप(pm->phys));

	spin_lock_init(&pm->lock);

	चयन (le16_to_cpu(udev->descriptor.idProduct)) अणु
	हाल POWERMATE_PRODUCT_NEW:
		input_dev->name = pm_name_घातermate;
		अवरोध;
	हाल POWERMATE_PRODUCT_OLD:
		input_dev->name = pm_name_soundknob;
		अवरोध;
	शेष:
		input_dev->name = pm_name_soundknob;
		prपूर्णांकk(KERN_WARNING "powermate: unknown product id %04x\n",
		       le16_to_cpu(udev->descriptor.idProduct));
	पूर्ण

	input_dev->phys = pm->phys;
	usb_to_input_id(udev, &input_dev->id);
	input_dev->dev.parent = &पूर्णांकf->dev;

	input_set_drvdata(input_dev, pm);

	input_dev->event = घातermate_input_event;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REL) |
		BIT_MASK(EV_MSC);
	input_dev->keybit[BIT_WORD(BTN_0)] = BIT_MASK(BTN_0);
	input_dev->relbit[BIT_WORD(REL_DIAL)] = BIT_MASK(REL_DIAL);
	input_dev->mscbit[BIT_WORD(MSC_PULSELED)] = BIT_MASK(MSC_PULSELED);

	/* get a handle to the पूर्णांकerrupt data pipe */
	pipe = usb_rcvपूर्णांकpipe(udev, endpoपूर्णांक->bEndpoपूर्णांकAddress);
	maxp = usb_maxpacket(udev, pipe, usb_pipeout(pipe));

	अगर (maxp < POWERMATE_PAYLOAD_SIZE_MIN || maxp > POWERMATE_PAYLOAD_SIZE_MAX) अणु
		prपूर्णांकk(KERN_WARNING "powermate: Expected payload of %d--%d bytes, found %d bytes!\n",
			POWERMATE_PAYLOAD_SIZE_MIN, POWERMATE_PAYLOAD_SIZE_MAX, maxp);
		maxp = POWERMATE_PAYLOAD_SIZE_MAX;
	पूर्ण

	usb_fill_पूर्णांक_urb(pm->irq, udev, pipe, pm->data,
			 maxp, घातermate_irq,
			 pm, endpoपूर्णांक->bInterval);
	pm->irq->transfer_dma = pm->data_dma;
	pm->irq->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	/* रेजिस्टर our पूर्णांकerrupt URB with the USB प्रणाली */
	अगर (usb_submit_urb(pm->irq, GFP_KERNEL)) अणु
		error = -EIO;
		जाओ fail4;
	पूर्ण

	error = input_रेजिस्टर_device(pm->input);
	अगर (error)
		जाओ fail5;


	/* क्रमce an update of everything */
	pm->requires_update = UPDATE_PULSE_ASLEEP | UPDATE_PULSE_AWAKE | UPDATE_PULSE_MODE | UPDATE_STATIC_BRIGHTNESS;
	घातermate_pulse_led(pm, 0x80, 255, 0, 1, 0); // set शेष pulse parameters

	usb_set_पूर्णांकfdata(पूर्णांकf, pm);
	वापस 0;

 fail5:	usb_समाप्त_urb(pm->irq);
 fail4:	usb_मुक्त_urb(pm->config);
 fail3:	usb_मुक्त_urb(pm->irq);
 fail2:	घातermate_मुक्त_buffers(udev, pm);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(pm);
	वापस error;
पूर्ण

/* Called when a USB device we've accepted ownership of is हटाओd */
अटल व्योम घातermate_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा घातermate_device *pm = usb_get_पूर्णांकfdata (पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	अगर (pm) अणु
		pm->requires_update = 0;
		usb_समाप्त_urb(pm->irq);
		input_unरेजिस्टर_device(pm->input);
		usb_मुक्त_urb(pm->irq);
		usb_मुक्त_urb(pm->config);
		घातermate_मुक्त_buffers(पूर्णांकerface_to_usbdev(पूर्णांकf), pm);

		kमुक्त(pm);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा usb_device_id घातermate_devices[] = अणु
	अणु USB_DEVICE(POWERMATE_VENDOR, POWERMATE_PRODUCT_NEW) पूर्ण,
	अणु USB_DEVICE(POWERMATE_VENDOR, POWERMATE_PRODUCT_OLD) पूर्ण,
	अणु USB_DEVICE(CONTOUR_VENDOR, CONTOUR_JOG) पूर्ण,
	अणु पूर्ण /* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE (usb, घातermate_devices);

अटल काष्ठा usb_driver घातermate_driver = अणु
        .name =         "powermate",
        .probe =        घातermate_probe,
        .disconnect =   घातermate_disconnect,
        .id_table =     घातermate_devices,
पूर्ण;

module_usb_driver(घातermate_driver);

MODULE_AUTHOR( "William R Sowerbutts" );
MODULE_DESCRIPTION( "Griffin Technology, Inc PowerMate driver" );
MODULE_LICENSE("GPL");
