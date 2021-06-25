<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/usb/input.h>
#समावेश <यंत्र/unaligned.h>

/*
 * Pressure-threshold modules param code from Alex Perry <alex.perry@ieee.org>
 */

MODULE_AUTHOR("Josh Myer <josh@joshisanerd.com>");
MODULE_DESCRIPTION("USB KB Gear JamStudio Tablet driver");
MODULE_LICENSE("GPL");

#घोषणा USB_VENDOR_ID_KBGEAR	0x084e

अटल पूर्णांक kb_pressure_click = 0x10;
module_param(kb_pressure_click, पूर्णांक, 0);
MODULE_PARM_DESC(kb_pressure_click, "pressure threshold for clicks");

काष्ठा kbtab अणु
	अचिन्हित अक्षर *data;
	dma_addr_t data_dma;
	काष्ठा input_dev *dev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा urb *irq;
	अक्षर phys[32];
पूर्ण;

अटल व्योम kbtab_irq(काष्ठा urb *urb)
अणु
	काष्ठा kbtab *kbtab = urb->context;
	अचिन्हित अक्षर *data = kbtab->data;
	काष्ठा input_dev *dev = kbtab->dev;
	पूर्णांक pressure;
	पूर्णांक retval;

	चयन (urb->status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* this urb is terminated, clean up */
		dev_dbg(&kbtab->पूर्णांकf->dev,
			"%s - urb shutting down with status: %d\n",
			__func__, urb->status);
		वापस;
	शेष:
		dev_dbg(&kbtab->पूर्णांकf->dev,
			"%s - nonzero urb status received: %d\n",
			__func__, urb->status);
		जाओ निकास;
	पूर्ण


	input_report_key(dev, BTN_TOOL_PEN, 1);

	input_report_असल(dev, ABS_X, get_unaligned_le16(&data[1]));
	input_report_असल(dev, ABS_Y, get_unaligned_le16(&data[3]));

	/*input_report_key(dev, BTN_TOUCH , data[0] & 0x01);*/
	input_report_key(dev, BTN_RIGHT, data[0] & 0x02);

	pressure = data[5];
	अगर (kb_pressure_click == -1)
		input_report_असल(dev, ABS_PRESSURE, pressure);
	अन्यथा
		input_report_key(dev, BTN_LEFT, pressure > kb_pressure_click ? 1 : 0);

	input_sync(dev);

 निकास:
	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(&kbtab->पूर्णांकf->dev,
			"%s - usb_submit_urb failed with result %d\n",
			__func__, retval);
पूर्ण

अटल स्थिर काष्ठा usb_device_id kbtab_ids[] = अणु
	अणु USB_DEVICE(USB_VENDOR_ID_KBGEAR, 0x1001), .driver_info = 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(usb, kbtab_ids);

अटल पूर्णांक kbtab_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा kbtab *kbtab = input_get_drvdata(dev);
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(kbtab->पूर्णांकf);

	kbtab->irq->dev = udev;
	अगर (usb_submit_urb(kbtab->irq, GFP_KERNEL))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल व्योम kbtab_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा kbtab *kbtab = input_get_drvdata(dev);

	usb_समाप्त_urb(kbtab->irq);
पूर्ण

अटल पूर्णांक kbtab_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा kbtab *kbtab;
	काष्ठा input_dev *input_dev;
	पूर्णांक error = -ENOMEM;

	अगर (पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs < 1)
		वापस -ENODEV;

	endpoपूर्णांक = &पूर्णांकf->cur_altsetting->endpoपूर्णांक[0].desc;
	अगर (!usb_endpoपूर्णांक_is_पूर्णांक_in(endpoपूर्णांक))
		वापस -ENODEV;

	kbtab = kzalloc(माप(काष्ठा kbtab), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!kbtab || !input_dev)
		जाओ fail1;

	kbtab->data = usb_alloc_coherent(dev, 8, GFP_KERNEL, &kbtab->data_dma);
	अगर (!kbtab->data)
		जाओ fail1;

	kbtab->irq = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!kbtab->irq)
		जाओ fail2;

	kbtab->पूर्णांकf = पूर्णांकf;
	kbtab->dev = input_dev;

	usb_make_path(dev, kbtab->phys, माप(kbtab->phys));
	strlcat(kbtab->phys, "/input0", माप(kbtab->phys));

	input_dev->name = "KB Gear Tablet";
	input_dev->phys = kbtab->phys;
	usb_to_input_id(dev, &input_dev->id);
	input_dev->dev.parent = &पूर्णांकf->dev;

	input_set_drvdata(input_dev, kbtab);

	input_dev->खोलो = kbtab_खोलो;
	input_dev->बंद = kbtab_बंद;

	input_dev->evbit[0] |= BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_LEFT)] |=
		BIT_MASK(BTN_LEFT) | BIT_MASK(BTN_RIGHT);
	input_dev->keybit[BIT_WORD(BTN_DIGI)] |=
		BIT_MASK(BTN_TOOL_PEN) | BIT_MASK(BTN_TOUCH);
	input_set_असल_params(input_dev, ABS_X, 0, 0x2000, 4, 0);
	input_set_असल_params(input_dev, ABS_Y, 0, 0x1750, 4, 0);
	input_set_असल_params(input_dev, ABS_PRESSURE, 0, 0xff, 0, 0);

	usb_fill_पूर्णांक_urb(kbtab->irq, dev,
			 usb_rcvपूर्णांकpipe(dev, endpoपूर्णांक->bEndpoपूर्णांकAddress),
			 kbtab->data, 8,
			 kbtab_irq, kbtab, endpoपूर्णांक->bInterval);
	kbtab->irq->transfer_dma = kbtab->data_dma;
	kbtab->irq->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	error = input_रेजिस्टर_device(kbtab->dev);
	अगर (error)
		जाओ fail3;

	usb_set_पूर्णांकfdata(पूर्णांकf, kbtab);

	वापस 0;

 fail3:	usb_मुक्त_urb(kbtab->irq);
 fail2:	usb_मुक्त_coherent(dev, 8, kbtab->data, kbtab->data_dma);
 fail1:	input_मुक्त_device(input_dev);
	kमुक्त(kbtab);
	वापस error;
पूर्ण

अटल व्योम kbtab_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा kbtab *kbtab = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	input_unरेजिस्टर_device(kbtab->dev);
	usb_मुक्त_urb(kbtab->irq);
	usb_मुक्त_coherent(udev, 8, kbtab->data, kbtab->data_dma);
	kमुक्त(kbtab);
पूर्ण

अटल काष्ठा usb_driver kbtab_driver = अणु
	.name =		"kbtab",
	.probe =	kbtab_probe,
	.disconnect =	kbtab_disconnect,
	.id_table =	kbtab_ids,
पूर्ण;

module_usb_driver(kbtab_driver);
