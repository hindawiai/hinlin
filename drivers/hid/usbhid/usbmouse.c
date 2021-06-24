<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 1999-2001 Vojtech Pavlik
 *
 *  USB HIDBP Mouse support
 */

/*
 *
 * Should you need to contact me, the author, you can करो so either by
 * e-mail - mail your message to <vojtech@ucw.cz>, or by paper mail:
 * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Reखुला
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/usb/input.h>
#समावेश <linux/hid.h>

/* क्रम apple IDs */
#अगर_घोषित CONFIG_USB_HID_MODULE
#समावेश "../hid-ids.h"
#पूर्ण_अगर

/*
 * Version Inक्रमmation
 */
#घोषणा DRIVER_VERSION "v1.6"
#घोषणा DRIVER_AUTHOR "Vojtech Pavlik <vojtech@ucw.cz>"
#घोषणा DRIVER_DESC "USB HID Boot Protocol mouse driver"

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

काष्ठा usb_mouse अणु
	अक्षर name[128];
	अक्षर phys[64];
	काष्ठा usb_device *usbdev;
	काष्ठा input_dev *dev;
	काष्ठा urb *irq;

	चिन्हित अक्षर *data;
	dma_addr_t data_dma;
पूर्ण;

अटल व्योम usb_mouse_irq(काष्ठा urb *urb)
अणु
	काष्ठा usb_mouse *mouse = urb->context;
	चिन्हित अक्षर *data = mouse->data;
	काष्ठा input_dev *dev = mouse->dev;
	पूर्णांक status;

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

	input_report_key(dev, BTN_LEFT,   data[0] & 0x01);
	input_report_key(dev, BTN_RIGHT,  data[0] & 0x02);
	input_report_key(dev, BTN_MIDDLE, data[0] & 0x04);
	input_report_key(dev, BTN_SIDE,   data[0] & 0x08);
	input_report_key(dev, BTN_EXTRA,  data[0] & 0x10);

	input_report_rel(dev, REL_X,     data[1]);
	input_report_rel(dev, REL_Y,     data[2]);
	input_report_rel(dev, REL_WHEEL, data[3]);

	input_sync(dev);
resubmit:
	status = usb_submit_urb (urb, GFP_ATOMIC);
	अगर (status)
		dev_err(&mouse->usbdev->dev,
			"can't resubmit intr, %s-%s/input0, status %d\n",
			mouse->usbdev->bus->bus_name,
			mouse->usbdev->devpath, status);
पूर्ण

अटल पूर्णांक usb_mouse_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा usb_mouse *mouse = input_get_drvdata(dev);

	mouse->irq->dev = mouse->usbdev;
	अगर (usb_submit_urb(mouse->irq, GFP_KERNEL))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम usb_mouse_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा usb_mouse *mouse = input_get_drvdata(dev);

	usb_समाप्त_urb(mouse->irq);
पूर्ण

अटल पूर्णांक usb_mouse_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकerface;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा usb_mouse *mouse;
	काष्ठा input_dev *input_dev;
	पूर्णांक pipe, maxp;
	पूर्णांक error = -ENOMEM;

	पूर्णांकerface = पूर्णांकf->cur_altsetting;

	अगर (पूर्णांकerface->desc.bNumEndpoपूर्णांकs != 1)
		वापस -ENODEV;

	endpoपूर्णांक = &पूर्णांकerface->endpoपूर्णांक[0].desc;
	अगर (!usb_endpoपूर्णांक_is_पूर्णांक_in(endpoपूर्णांक))
		वापस -ENODEV;

	pipe = usb_rcvपूर्णांकpipe(dev, endpoपूर्णांक->bEndpoपूर्णांकAddress);
	maxp = usb_maxpacket(dev, pipe, usb_pipeout(pipe));

	mouse = kzalloc(माप(काष्ठा usb_mouse), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!mouse || !input_dev)
		जाओ fail1;

	mouse->data = usb_alloc_coherent(dev, 8, GFP_ATOMIC, &mouse->data_dma);
	अगर (!mouse->data)
		जाओ fail1;

	mouse->irq = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!mouse->irq)
		जाओ fail2;

	mouse->usbdev = dev;
	mouse->dev = input_dev;

	अगर (dev->manufacturer)
		strlcpy(mouse->name, dev->manufacturer, माप(mouse->name));

	अगर (dev->product) अणु
		अगर (dev->manufacturer)
			strlcat(mouse->name, " ", माप(mouse->name));
		strlcat(mouse->name, dev->product, माप(mouse->name));
	पूर्ण

	अगर (!म_माप(mouse->name))
		snम_लिखो(mouse->name, माप(mouse->name),
			 "USB HIDBP Mouse %04x:%04x",
			 le16_to_cpu(dev->descriptor.idVenकरोr),
			 le16_to_cpu(dev->descriptor.idProduct));

	usb_make_path(dev, mouse->phys, माप(mouse->phys));
	strlcat(mouse->phys, "/input0", माप(mouse->phys));

	input_dev->name = mouse->name;
	input_dev->phys = mouse->phys;
	usb_to_input_id(dev, &input_dev->id);
	input_dev->dev.parent = &पूर्णांकf->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REL);
	input_dev->keybit[BIT_WORD(BTN_MOUSE)] = BIT_MASK(BTN_LEFT) |
		BIT_MASK(BTN_RIGHT) | BIT_MASK(BTN_MIDDLE);
	input_dev->relbit[0] = BIT_MASK(REL_X) | BIT_MASK(REL_Y);
	input_dev->keybit[BIT_WORD(BTN_MOUSE)] |= BIT_MASK(BTN_SIDE) |
		BIT_MASK(BTN_EXTRA);
	input_dev->relbit[0] |= BIT_MASK(REL_WHEEL);

	input_set_drvdata(input_dev, mouse);

	input_dev->खोलो = usb_mouse_खोलो;
	input_dev->बंद = usb_mouse_बंद;

	usb_fill_पूर्णांक_urb(mouse->irq, dev, pipe, mouse->data,
			 (maxp > 8 ? 8 : maxp),
			 usb_mouse_irq, mouse, endpoपूर्णांक->bInterval);
	mouse->irq->transfer_dma = mouse->data_dma;
	mouse->irq->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	error = input_रेजिस्टर_device(mouse->dev);
	अगर (error)
		जाओ fail3;

	usb_set_पूर्णांकfdata(पूर्णांकf, mouse);
	वापस 0;

fail3:	
	usb_मुक्त_urb(mouse->irq);
fail2:	
	usb_मुक्त_coherent(dev, 8, mouse->data, mouse->data_dma);
fail1:	
	input_मुक्त_device(input_dev);
	kमुक्त(mouse);
	वापस error;
पूर्ण

अटल व्योम usb_mouse_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_mouse *mouse = usb_get_पूर्णांकfdata (पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	अगर (mouse) अणु
		usb_समाप्त_urb(mouse->irq);
		input_unरेजिस्टर_device(mouse->dev);
		usb_मुक्त_urb(mouse->irq);
		usb_मुक्त_coherent(पूर्णांकerface_to_usbdev(पूर्णांकf), 8, mouse->data, mouse->data_dma);
		kमुक्त(mouse);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा usb_device_id usb_mouse_id_table[] = अणु
	अणु USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID, USB_INTERFACE_SUBCLASS_BOOT,
		USB_INTERFACE_PROTOCOL_MOUSE) पूर्ण,
	अणु पूर्ण	/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE (usb, usb_mouse_id_table);

अटल काष्ठा usb_driver usb_mouse_driver = अणु
	.name		= "usbmouse",
	.probe		= usb_mouse_probe,
	.disconnect	= usb_mouse_disconnect,
	.id_table	= usb_mouse_id_table,
पूर्ण;

module_usb_driver(usb_mouse_driver);
