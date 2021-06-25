<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2001-2005 Eकरोuard TISSERANT   <eकरोuard.tisserant@wanaकरोo.fr>
 *  Copyright (c) 2004-2005 Stephane VOLTZ      <svoltz@numericable.fr>
 *
 *  USB Acecad "Acecad Flair" tablet support
 *
 *  Changelog:
 *      v3.2 - Added sysfs support
 */

/*
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/usb/input.h>

MODULE_AUTHOR("Edouard TISSERANT <edouard.tisserant@wanadoo.fr>");
MODULE_DESCRIPTION("USB Acecad Flair tablet driver");
MODULE_LICENSE("GPL");

#घोषणा USB_VENDOR_ID_ACECAD	0x0460
#घोषणा USB_DEVICE_ID_FLAIR	0x0004
#घोषणा USB_DEVICE_ID_302	0x0008

काष्ठा usb_acecad अणु
	अक्षर name[128];
	अक्षर phys[64];
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा input_dev *input;
	काष्ठा urb *irq;

	अचिन्हित अक्षर *data;
	dma_addr_t data_dma;
पूर्ण;

अटल व्योम usb_acecad_irq(काष्ठा urb *urb)
अणु
	काष्ठा usb_acecad *acecad = urb->context;
	अचिन्हित अक्षर *data = acecad->data;
	काष्ठा input_dev *dev = acecad->input;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = acecad->पूर्णांकf;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	पूर्णांक prox, status;

	चयन (urb->status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(&पूर्णांकf->dev, "%s - urb shutting down with status: %d\n",
			__func__, urb->status);
		वापस;
	शेष:
		dev_dbg(&पूर्णांकf->dev, "%s - nonzero urb status received: %d\n",
			__func__, urb->status);
		जाओ resubmit;
	पूर्ण

	prox = (data[0] & 0x04) >> 2;
	input_report_key(dev, BTN_TOOL_PEN, prox);

	अगर (prox) अणु
		पूर्णांक x = data[1] | (data[2] << 8);
		पूर्णांक y = data[3] | (data[4] << 8);
		/* Pressure should compute the same way क्रम flair and 302 */
		पूर्णांक pressure = data[5] | (data[6] << 8);
		पूर्णांक touch = data[0] & 0x01;
		पूर्णांक stylus = (data[0] & 0x10) >> 4;
		पूर्णांक stylus2 = (data[0] & 0x20) >> 5;
		input_report_असल(dev, ABS_X, x);
		input_report_असल(dev, ABS_Y, y);
		input_report_असल(dev, ABS_PRESSURE, pressure);
		input_report_key(dev, BTN_TOUCH, touch);
		input_report_key(dev, BTN_STYLUS, stylus);
		input_report_key(dev, BTN_STYLUS2, stylus2);
	पूर्ण

	/* event termination */
	input_sync(dev);

resubmit:
	status = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (status)
		dev_err(&पूर्णांकf->dev,
			"can't resubmit intr, %s-%s/input0, status %d\n",
			udev->bus->bus_name,
			udev->devpath, status);
पूर्ण

अटल पूर्णांक usb_acecad_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा usb_acecad *acecad = input_get_drvdata(dev);

	acecad->irq->dev = पूर्णांकerface_to_usbdev(acecad->पूर्णांकf);
	अगर (usb_submit_urb(acecad->irq, GFP_KERNEL))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम usb_acecad_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा usb_acecad *acecad = input_get_drvdata(dev);

	usb_समाप्त_urb(acecad->irq);
पूर्ण

अटल पूर्णांक usb_acecad_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकerface = पूर्णांकf->cur_altsetting;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा usb_acecad *acecad;
	काष्ठा input_dev *input_dev;
	पूर्णांक pipe, maxp;
	पूर्णांक err;

	अगर (पूर्णांकerface->desc.bNumEndpoपूर्णांकs != 1)
		वापस -ENODEV;

	endpoपूर्णांक = &पूर्णांकerface->endpoपूर्णांक[0].desc;

	अगर (!usb_endpoपूर्णांक_is_पूर्णांक_in(endpoपूर्णांक))
		वापस -ENODEV;

	pipe = usb_rcvपूर्णांकpipe(dev, endpoपूर्णांक->bEndpoपूर्णांकAddress);
	maxp = usb_maxpacket(dev, pipe, usb_pipeout(pipe));

	acecad = kzalloc(माप(काष्ठा usb_acecad), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!acecad || !input_dev) अणु
		err = -ENOMEM;
		जाओ fail1;
	पूर्ण

	acecad->data = usb_alloc_coherent(dev, 8, GFP_KERNEL, &acecad->data_dma);
	अगर (!acecad->data) अणु
		err= -ENOMEM;
		जाओ fail1;
	पूर्ण

	acecad->irq = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!acecad->irq) अणु
		err = -ENOMEM;
		जाओ fail2;
	पूर्ण

	acecad->पूर्णांकf = पूर्णांकf;
	acecad->input = input_dev;

	अगर (dev->manufacturer)
		strlcpy(acecad->name, dev->manufacturer, माप(acecad->name));

	अगर (dev->product) अणु
		अगर (dev->manufacturer)
			strlcat(acecad->name, " ", माप(acecad->name));
		strlcat(acecad->name, dev->product, माप(acecad->name));
	पूर्ण

	usb_make_path(dev, acecad->phys, माप(acecad->phys));
	strlcat(acecad->phys, "/input0", माप(acecad->phys));

	input_dev->name = acecad->name;
	input_dev->phys = acecad->phys;
	usb_to_input_id(dev, &input_dev->id);
	input_dev->dev.parent = &पूर्णांकf->dev;

	input_set_drvdata(input_dev, acecad);

	input_dev->खोलो = usb_acecad_खोलो;
	input_dev->बंद = usb_acecad_बंद;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_DIGI)] = BIT_MASK(BTN_TOOL_PEN) |
		BIT_MASK(BTN_TOUCH) | BIT_MASK(BTN_STYLUS) |
		BIT_MASK(BTN_STYLUS2);

	चयन (id->driver_info) अणु
	हाल 0:
		input_set_असल_params(input_dev, ABS_X, 0, 5000, 4, 0);
		input_set_असल_params(input_dev, ABS_Y, 0, 3750, 4, 0);
		input_set_असल_params(input_dev, ABS_PRESSURE, 0, 512, 0, 0);
		अगर (!म_माप(acecad->name))
			snम_लिखो(acecad->name, माप(acecad->name),
				"USB Acecad Flair Tablet %04x:%04x",
				le16_to_cpu(dev->descriptor.idVenकरोr),
				le16_to_cpu(dev->descriptor.idProduct));
		अवरोध;

	हाल 1:
		input_set_असल_params(input_dev, ABS_X, 0, 53000, 4, 0);
		input_set_असल_params(input_dev, ABS_Y, 0, 2250, 4, 0);
		input_set_असल_params(input_dev, ABS_PRESSURE, 0, 1024, 0, 0);
		अगर (!म_माप(acecad->name))
			snम_लिखो(acecad->name, माप(acecad->name),
				"USB Acecad 302 Tablet %04x:%04x",
				le16_to_cpu(dev->descriptor.idVenकरोr),
				le16_to_cpu(dev->descriptor.idProduct));
		अवरोध;
	पूर्ण

	usb_fill_पूर्णांक_urb(acecad->irq, dev, pipe,
			acecad->data, maxp > 8 ? 8 : maxp,
			usb_acecad_irq, acecad, endpoपूर्णांक->bInterval);
	acecad->irq->transfer_dma = acecad->data_dma;
	acecad->irq->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	err = input_रेजिस्टर_device(acecad->input);
	अगर (err)
		जाओ fail3;

	usb_set_पूर्णांकfdata(पूर्णांकf, acecad);

	वापस 0;

 fail3:	usb_मुक्त_urb(acecad->irq);
 fail2:	usb_मुक्त_coherent(dev, 8, acecad->data, acecad->data_dma);
 fail1: input_मुक्त_device(input_dev);
	kमुक्त(acecad);
	वापस err;
पूर्ण

अटल व्योम usb_acecad_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_acecad *acecad = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	input_unरेजिस्टर_device(acecad->input);
	usb_मुक्त_urb(acecad->irq);
	usb_मुक्त_coherent(udev, 8, acecad->data, acecad->data_dma);
	kमुक्त(acecad);
पूर्ण

अटल स्थिर काष्ठा usb_device_id usb_acecad_id_table[] = अणु
	अणु USB_DEVICE(USB_VENDOR_ID_ACECAD, USB_DEVICE_ID_FLAIR), .driver_info = 0 पूर्ण,
	अणु USB_DEVICE(USB_VENDOR_ID_ACECAD, USB_DEVICE_ID_302),	 .driver_info = 1 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, usb_acecad_id_table);

अटल काष्ठा usb_driver usb_acecad_driver = अणु
	.name =		"usb_acecad",
	.probe =	usb_acecad_probe,
	.disconnect =	usb_acecad_disconnect,
	.id_table =	usb_acecad_id_table,
पूर्ण;

module_usb_driver(usb_acecad_driver);
