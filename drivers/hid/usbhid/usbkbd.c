<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1999-2001 Vojtech Pavlik
 *
 *  USB HIDBP Keyboard support
 */

/*
 *
 * Should you need to contact me, the author, you can करो so either by
 * e-mail - mail your message to <vojtech@ucw.cz>, or by paper mail:
 * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Reखुला
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/usb/input.h>
#समावेश <linux/hid.h>

/*
 * Version Inक्रमmation
 */
#घोषणा DRIVER_VERSION ""
#घोषणा DRIVER_AUTHOR "Vojtech Pavlik <vojtech@ucw.cz>"
#घोषणा DRIVER_DESC "USB HID Boot Protocol keyboard driver"

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

अटल स्थिर अचिन्हित अक्षर usb_kbd_keycode[256] = अणु
	  0,  0,  0,  0, 30, 48, 46, 32, 18, 33, 34, 35, 23, 36, 37, 38,
	 50, 49, 24, 25, 16, 19, 31, 20, 22, 47, 17, 45, 21, 44,  2,  3,
	  4,  5,  6,  7,  8,  9, 10, 11, 28,  1, 14, 15, 57, 12, 13, 26,
	 27, 43, 43, 39, 40, 41, 51, 52, 53, 58, 59, 60, 61, 62, 63, 64,
	 65, 66, 67, 68, 87, 88, 99, 70,119,110,102,104,111,107,109,106,
	105,108,103, 69, 98, 55, 74, 78, 96, 79, 80, 81, 75, 76, 77, 71,
	 72, 73, 82, 83, 86,127,116,117,183,184,185,186,187,188,189,190,
	191,192,193,194,134,138,130,132,128,129,131,137,133,135,136,113,
	115,114,  0,  0,  0,121,  0, 89, 93,124, 92, 94, 95,  0,  0,  0,
	122,123, 90, 91, 85,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 29, 42, 56,125, 97, 54,100,126,164,166,165,163,161,115,114,113,
	150,158,159,128,136,177,178,176,142,152,173,140
पूर्ण;


/**
 * काष्ठा usb_kbd - state of each attached keyboard
 * @dev:	input device associated with this keyboard
 * @usbdev:	usb device associated with this keyboard
 * @old:	data received in the past from the @irq URB representing which
 *		keys were pressed. By comparing with the current list of keys
 *		that are pressed, we are able to see key releases.
 * @irq:	URB क्रम receiving a list of keys that are pressed when a
 *		new key is pressed or a key that was pressed is released.
 * @led:	URB क्रम sending LEDs (e.g. numlock, ...)
 * @newleds:	data that will be sent with the @led URB representing which LEDs
 *		should be on
 * @name:	Name of the keyboard. @dev's name field poपूर्णांकs to this buffer
 * @phys:	Physical path of the keyboard. @dev's phys field poपूर्णांकs to this
 *		buffer
 * @new:	Buffer क्रम the @irq URB
 * @cr:		Control request क्रम @led URB
 * @leds:	Buffer क्रम the @led URB
 * @new_dma:	DMA address क्रम @irq URB
 * @leds_dma:	DMA address क्रम @led URB
 * @leds_lock:	spinlock that protects @leds, @newleds, and @led_urb_submitted
 * @led_urb_submitted: indicates whether @led is in progress, i.e. it has been
 *		submitted and its completion handler has not वापसed yet
 *		without	resubmitting @led
 */
काष्ठा usb_kbd अणु
	काष्ठा input_dev *dev;
	काष्ठा usb_device *usbdev;
	अचिन्हित अक्षर old[8];
	काष्ठा urb *irq, *led;
	अचिन्हित अक्षर newleds;
	अक्षर name[128];
	अक्षर phys[64];

	अचिन्हित अक्षर *new;
	काष्ठा usb_ctrlrequest *cr;
	अचिन्हित अक्षर *leds;
	dma_addr_t new_dma;
	dma_addr_t leds_dma;

	spinlock_t leds_lock;
	bool led_urb_submitted;

पूर्ण;

अटल व्योम usb_kbd_irq(काष्ठा urb *urb)
अणु
	काष्ठा usb_kbd *kbd = urb->context;
	पूर्णांक i;

	चयन (urb->status) अणु
	हाल 0:			/* success */
		अवरोध;
	हाल -ECONNRESET:	/* unlink */
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;
	/* -EPIPE:  should clear the halt */
	शेष:		/* error */
		जाओ resubmit;
	पूर्ण

	क्रम (i = 0; i < 8; i++)
		input_report_key(kbd->dev, usb_kbd_keycode[i + 224], (kbd->new[0] >> i) & 1);

	क्रम (i = 2; i < 8; i++) अणु

		अगर (kbd->old[i] > 3 && memscan(kbd->new + 2, kbd->old[i], 6) == kbd->new + 8) अणु
			अगर (usb_kbd_keycode[kbd->old[i]])
				input_report_key(kbd->dev, usb_kbd_keycode[kbd->old[i]], 0);
			अन्यथा
				hid_info(urb->dev,
					 "Unknown key (scancode %#x) released.\n",
					 kbd->old[i]);
		पूर्ण

		अगर (kbd->new[i] > 3 && memscan(kbd->old + 2, kbd->new[i], 6) == kbd->old + 8) अणु
			अगर (usb_kbd_keycode[kbd->new[i]])
				input_report_key(kbd->dev, usb_kbd_keycode[kbd->new[i]], 1);
			अन्यथा
				hid_info(urb->dev,
					 "Unknown key (scancode %#x) pressed.\n",
					 kbd->new[i]);
		पूर्ण
	पूर्ण

	input_sync(kbd->dev);

	स_नकल(kbd->old, kbd->new, 8);

resubmit:
	i = usb_submit_urb (urb, GFP_ATOMIC);
	अगर (i)
		hid_err(urb->dev, "can't resubmit intr, %s-%s/input0, status %d",
			kbd->usbdev->bus->bus_name,
			kbd->usbdev->devpath, i);
पूर्ण

अटल पूर्णांक usb_kbd_event(काष्ठा input_dev *dev, अचिन्हित पूर्णांक type,
			 अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा usb_kbd *kbd = input_get_drvdata(dev);

	अगर (type != EV_LED)
		वापस -1;

	spin_lock_irqsave(&kbd->leds_lock, flags);
	kbd->newleds = (!!test_bit(LED_KANA,    dev->led) << 3) | (!!test_bit(LED_COMPOSE, dev->led) << 3) |
		       (!!test_bit(LED_SCROLLL, dev->led) << 2) | (!!test_bit(LED_CAPSL,   dev->led) << 1) |
		       (!!test_bit(LED_NUML,    dev->led));

	अगर (kbd->led_urb_submitted)अणु
		spin_unlock_irqrestore(&kbd->leds_lock, flags);
		वापस 0;
	पूर्ण

	अगर (*(kbd->leds) == kbd->newleds)अणु
		spin_unlock_irqrestore(&kbd->leds_lock, flags);
		वापस 0;
	पूर्ण

	*(kbd->leds) = kbd->newleds;

	kbd->led->dev = kbd->usbdev;
	अगर (usb_submit_urb(kbd->led, GFP_ATOMIC))
		pr_err("usb_submit_urb(leds) failed\n");
	अन्यथा
		kbd->led_urb_submitted = true;

	spin_unlock_irqrestore(&kbd->leds_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम usb_kbd_led(काष्ठा urb *urb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा usb_kbd *kbd = urb->context;

	अगर (urb->status)
		hid_warn(urb->dev, "led urb status %d received\n",
			 urb->status);

	spin_lock_irqsave(&kbd->leds_lock, flags);

	अगर (*(kbd->leds) == kbd->newleds)अणु
		kbd->led_urb_submitted = false;
		spin_unlock_irqrestore(&kbd->leds_lock, flags);
		वापस;
	पूर्ण

	*(kbd->leds) = kbd->newleds;

	kbd->led->dev = kbd->usbdev;
	अगर (usb_submit_urb(kbd->led, GFP_ATOMIC))अणु
		hid_err(urb->dev, "usb_submit_urb(leds) failed\n");
		kbd->led_urb_submitted = false;
	पूर्ण
	spin_unlock_irqrestore(&kbd->leds_lock, flags);

पूर्ण

अटल पूर्णांक usb_kbd_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा usb_kbd *kbd = input_get_drvdata(dev);

	kbd->irq->dev = kbd->usbdev;
	अगर (usb_submit_urb(kbd->irq, GFP_KERNEL))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम usb_kbd_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा usb_kbd *kbd = input_get_drvdata(dev);

	usb_समाप्त_urb(kbd->irq);
पूर्ण

अटल पूर्णांक usb_kbd_alloc_mem(काष्ठा usb_device *dev, काष्ठा usb_kbd *kbd)
अणु
	अगर (!(kbd->irq = usb_alloc_urb(0, GFP_KERNEL)))
		वापस -1;
	अगर (!(kbd->led = usb_alloc_urb(0, GFP_KERNEL)))
		वापस -1;
	अगर (!(kbd->new = usb_alloc_coherent(dev, 8, GFP_ATOMIC, &kbd->new_dma)))
		वापस -1;
	अगर (!(kbd->cr = kदो_स्मृति(माप(काष्ठा usb_ctrlrequest), GFP_KERNEL)))
		वापस -1;
	अगर (!(kbd->leds = usb_alloc_coherent(dev, 1, GFP_ATOMIC, &kbd->leds_dma)))
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम usb_kbd_मुक्त_mem(काष्ठा usb_device *dev, काष्ठा usb_kbd *kbd)
अणु
	usb_मुक्त_urb(kbd->irq);
	usb_मुक्त_urb(kbd->led);
	usb_मुक्त_coherent(dev, 8, kbd->new, kbd->new_dma);
	kमुक्त(kbd->cr);
	usb_मुक्त_coherent(dev, 1, kbd->leds, kbd->leds_dma);
पूर्ण

अटल पूर्णांक usb_kbd_probe(काष्ठा usb_पूर्णांकerface *अगरace,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(अगरace);
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकerface;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा usb_kbd *kbd;
	काष्ठा input_dev *input_dev;
	पूर्णांक i, pipe, maxp;
	पूर्णांक error = -ENOMEM;

	पूर्णांकerface = अगरace->cur_altsetting;

	अगर (पूर्णांकerface->desc.bNumEndpoपूर्णांकs != 1)
		वापस -ENODEV;

	endpoपूर्णांक = &पूर्णांकerface->endpoपूर्णांक[0].desc;
	अगर (!usb_endpoपूर्णांक_is_पूर्णांक_in(endpoपूर्णांक))
		वापस -ENODEV;

	pipe = usb_rcvपूर्णांकpipe(dev, endpoपूर्णांक->bEndpoपूर्णांकAddress);
	maxp = usb_maxpacket(dev, pipe, usb_pipeout(pipe));

	kbd = kzalloc(माप(काष्ठा usb_kbd), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!kbd || !input_dev)
		जाओ fail1;

	अगर (usb_kbd_alloc_mem(dev, kbd))
		जाओ fail2;

	kbd->usbdev = dev;
	kbd->dev = input_dev;
	spin_lock_init(&kbd->leds_lock);

	अगर (dev->manufacturer)
		strlcpy(kbd->name, dev->manufacturer, माप(kbd->name));

	अगर (dev->product) अणु
		अगर (dev->manufacturer)
			strlcat(kbd->name, " ", माप(kbd->name));
		strlcat(kbd->name, dev->product, माप(kbd->name));
	पूर्ण

	अगर (!म_माप(kbd->name))
		snम_लिखो(kbd->name, माप(kbd->name),
			 "USB HIDBP Keyboard %04x:%04x",
			 le16_to_cpu(dev->descriptor.idVenकरोr),
			 le16_to_cpu(dev->descriptor.idProduct));

	usb_make_path(dev, kbd->phys, माप(kbd->phys));
	strlcat(kbd->phys, "/input0", माप(kbd->phys));

	input_dev->name = kbd->name;
	input_dev->phys = kbd->phys;
	usb_to_input_id(dev, &input_dev->id);
	input_dev->dev.parent = &अगरace->dev;

	input_set_drvdata(input_dev, kbd);

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_LED) |
		BIT_MASK(EV_REP);
	input_dev->ledbit[0] = BIT_MASK(LED_NUML) | BIT_MASK(LED_CAPSL) |
		BIT_MASK(LED_SCROLLL) | BIT_MASK(LED_COMPOSE) |
		BIT_MASK(LED_KANA);

	क्रम (i = 0; i < 255; i++)
		set_bit(usb_kbd_keycode[i], input_dev->keybit);
	clear_bit(0, input_dev->keybit);

	input_dev->event = usb_kbd_event;
	input_dev->खोलो = usb_kbd_खोलो;
	input_dev->बंद = usb_kbd_बंद;

	usb_fill_पूर्णांक_urb(kbd->irq, dev, pipe,
			 kbd->new, (maxp > 8 ? 8 : maxp),
			 usb_kbd_irq, kbd, endpoपूर्णांक->bInterval);
	kbd->irq->transfer_dma = kbd->new_dma;
	kbd->irq->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	kbd->cr->bRequestType = USB_TYPE_CLASS | USB_RECIP_INTERFACE;
	kbd->cr->bRequest = 0x09;
	kbd->cr->wValue = cpu_to_le16(0x200);
	kbd->cr->wIndex = cpu_to_le16(पूर्णांकerface->desc.bInterfaceNumber);
	kbd->cr->wLength = cpu_to_le16(1);

	usb_fill_control_urb(kbd->led, dev, usb_sndctrlpipe(dev, 0),
			     (व्योम *) kbd->cr, kbd->leds, 1,
			     usb_kbd_led, kbd);
	kbd->led->transfer_dma = kbd->leds_dma;
	kbd->led->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	error = input_रेजिस्टर_device(kbd->dev);
	अगर (error)
		जाओ fail2;

	usb_set_पूर्णांकfdata(अगरace, kbd);
	device_set_wakeup_enable(&dev->dev, 1);
	वापस 0;

fail2:
	usb_kbd_मुक्त_mem(dev, kbd);
fail1:
	input_मुक्त_device(input_dev);
	kमुक्त(kbd);
	वापस error;
पूर्ण

अटल व्योम usb_kbd_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_kbd *kbd = usb_get_पूर्णांकfdata (पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	अगर (kbd) अणु
		usb_समाप्त_urb(kbd->irq);
		input_unरेजिस्टर_device(kbd->dev);
		usb_समाप्त_urb(kbd->led);
		usb_kbd_मुक्त_mem(पूर्णांकerface_to_usbdev(पूर्णांकf), kbd);
		kमुक्त(kbd);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा usb_device_id usb_kbd_id_table[] = अणु
	अणु USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID, USB_INTERFACE_SUBCLASS_BOOT,
		USB_INTERFACE_PROTOCOL_KEYBOARD) पूर्ण,
	अणु पूर्ण						/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE (usb, usb_kbd_id_table);

अटल काष्ठा usb_driver usb_kbd_driver = अणु
	.name =		"usbkbd",
	.probe =	usb_kbd_probe,
	.disconnect =	usb_kbd_disconnect,
	.id_table =	usb_kbd_id_table,
पूर्ण;

module_usb_driver(usb_kbd_driver);
