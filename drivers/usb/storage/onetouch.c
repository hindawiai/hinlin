<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Support क्रम the Maxtor OneTouch USB hard drive's button
 *
 * Current development and मुख्यtenance by:
 *	Copyright (c) 2005 Nick Sillik <n.sillik@temple.edu>
 *
 * Initial work by:
 *	Copyright (c) 2003 Erik Thyren <erth7411@student.uu.se>
 *
 * Based on usbmouse.c (Vojtech Pavlik) and xpad.c (Marko Friedemann)
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/usb/input.h>
#समावेश "usb.h"
#समावेश "debug.h"
#समावेश "scsiglue.h"

#घोषणा DRV_NAME "ums-onetouch"

MODULE_DESCRIPTION("Maxtor USB OneTouch hard drive button driver");
MODULE_AUTHOR("Nick Sillik <n.sillik@temple.edu>");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(USB_STORAGE);

#घोषणा ONETOUCH_PKT_LEN        0x02
#घोषणा ONETOUCH_BUTTON         KEY_PROG1

अटल पूर्णांक onetouch_connect_input(काष्ठा us_data *ss);
अटल व्योम onetouch_release_input(व्योम *onetouch_);

काष्ठा usb_onetouch अणु
	अक्षर name[128];
	अक्षर phys[64];
	काष्ठा input_dev *dev;	/* input device पूर्णांकerface */
	काष्ठा usb_device *udev;	/* usb device */

	काष्ठा urb *irq;	/* urb क्रम पूर्णांकerrupt in report */
	अचिन्हित अक्षर *data;	/* input data */
	dma_addr_t data_dma;
	अचिन्हित पूर्णांक is_खोलो:1;
पूर्ण;


/*
 * The table of devices
 */
#घोषणा UNUSUAL_DEV(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax, \
		    venकरोrName, productName, useProtocol, useTransport, \
		    initFunction, flags) \
अणु USB_DEVICE_VER(id_venकरोr, id_product, bcdDeviceMin, bcdDeviceMax), \
  .driver_info = (flags) पूर्ण

अटल काष्ठा usb_device_id onetouch_usb_ids[] = अणु
#	include "unusual_onetouch.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, onetouch_usb_ids);

#अघोषित UNUSUAL_DEV

/*
 * The flags table
 */
#घोषणा UNUSUAL_DEV(idVenकरोr, idProduct, bcdDeviceMin, bcdDeviceMax, \
		    venकरोr_name, product_name, use_protocol, use_transport, \
		    init_function, Flags) \
अणु \
	.venकरोrName = venकरोr_name,	\
	.productName = product_name,	\
	.useProtocol = use_protocol,	\
	.useTransport = use_transport,	\
	.initFunction = init_function,	\
पूर्ण

अटल काष्ठा us_unusual_dev onetouch_unusual_dev_list[] = अणु
#	include "unusual_onetouch.h"
	अणु पूर्ण		/* Terminating entry */
पूर्ण;

#अघोषित UNUSUAL_DEV


अटल व्योम usb_onetouch_irq(काष्ठा urb *urb)
अणु
	काष्ठा usb_onetouch *onetouch = urb->context;
	चिन्हित अक्षर *data = onetouch->data;
	काष्ठा input_dev *dev = onetouch->dev;
	पूर्णांक status = urb->status;
	पूर्णांक retval;

	चयन (status) अणु
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

	input_report_key(dev, ONETOUCH_BUTTON, data[0] & 0x02);
	input_sync(dev);

resubmit:
	retval = usb_submit_urb (urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(&dev->dev, "can't resubmit intr, %s-%s/input0, "
			"retval %d\n", onetouch->udev->bus->bus_name,
			onetouch->udev->devpath, retval);
पूर्ण

अटल पूर्णांक usb_onetouch_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा usb_onetouch *onetouch = input_get_drvdata(dev);

	onetouch->is_खोलो = 1;
	onetouch->irq->dev = onetouch->udev;
	अगर (usb_submit_urb(onetouch->irq, GFP_KERNEL)) अणु
		dev_err(&dev->dev, "usb_submit_urb failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम usb_onetouch_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा usb_onetouch *onetouch = input_get_drvdata(dev);

	usb_समाप्त_urb(onetouch->irq);
	onetouch->is_खोलो = 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम usb_onetouch_pm_hook(काष्ठा us_data *us, पूर्णांक action)
अणु
	काष्ठा usb_onetouch *onetouch = (काष्ठा usb_onetouch *) us->extra;

	अगर (onetouch->is_खोलो) अणु
		चयन (action) अणु
		हाल US_SUSPEND:
			usb_समाप्त_urb(onetouch->irq);
			अवरोध;
		हाल US_RESUME:
			अगर (usb_submit_urb(onetouch->irq, GFP_NOIO) != 0)
				dev_err(&onetouch->irq->dev->dev,
					"usb_submit_urb failed\n");
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल पूर्णांक onetouch_connect_input(काष्ठा us_data *ss)
अणु
	काष्ठा usb_device *udev = ss->pusb_dev;
	काष्ठा usb_host_पूर्णांकerface *पूर्णांकerface;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा usb_onetouch *onetouch;
	काष्ठा input_dev *input_dev;
	पूर्णांक pipe, maxp;
	पूर्णांक error = -ENOMEM;

	पूर्णांकerface = ss->pusb_पूर्णांकf->cur_altsetting;

	अगर (पूर्णांकerface->desc.bNumEndpoपूर्णांकs != 3)
		वापस -ENODEV;

	endpoपूर्णांक = &पूर्णांकerface->endpoपूर्णांक[2].desc;
	अगर (!usb_endpoपूर्णांक_is_पूर्णांक_in(endpoपूर्णांक))
		वापस -ENODEV;

	pipe = usb_rcvपूर्णांकpipe(udev, endpoपूर्णांक->bEndpoपूर्णांकAddress);
	maxp = usb_maxpacket(udev, pipe, usb_pipeout(pipe));
	maxp = min(maxp, ONETOUCH_PKT_LEN);

	onetouch = kzalloc(माप(काष्ठा usb_onetouch), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!onetouch || !input_dev)
		जाओ fail1;

	onetouch->data = usb_alloc_coherent(udev, ONETOUCH_PKT_LEN,
					    GFP_KERNEL, &onetouch->data_dma);
	अगर (!onetouch->data)
		जाओ fail1;

	onetouch->irq = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!onetouch->irq)
		जाओ fail2;

	onetouch->udev = udev;
	onetouch->dev = input_dev;

	अगर (udev->manufacturer)
		strlcpy(onetouch->name, udev->manufacturer,
			माप(onetouch->name));
	अगर (udev->product) अणु
		अगर (udev->manufacturer)
			strlcat(onetouch->name, " ", माप(onetouch->name));
		strlcat(onetouch->name, udev->product, माप(onetouch->name));
	पूर्ण

	अगर (!म_माप(onetouch->name))
		snम_लिखो(onetouch->name, माप(onetouch->name),
			 "Maxtor Onetouch %04x:%04x",
			 le16_to_cpu(udev->descriptor.idVenकरोr),
			 le16_to_cpu(udev->descriptor.idProduct));

	usb_make_path(udev, onetouch->phys, माप(onetouch->phys));
	strlcat(onetouch->phys, "/input0", माप(onetouch->phys));

	input_dev->name = onetouch->name;
	input_dev->phys = onetouch->phys;
	usb_to_input_id(udev, &input_dev->id);
	input_dev->dev.parent = &udev->dev;

	set_bit(EV_KEY, input_dev->evbit);
	set_bit(ONETOUCH_BUTTON, input_dev->keybit);
	clear_bit(0, input_dev->keybit);

	input_set_drvdata(input_dev, onetouch);

	input_dev->खोलो = usb_onetouch_खोलो;
	input_dev->बंद = usb_onetouch_बंद;

	usb_fill_पूर्णांक_urb(onetouch->irq, udev, pipe, onetouch->data, maxp,
			 usb_onetouch_irq, onetouch, endpoपूर्णांक->bInterval);
	onetouch->irq->transfer_dma = onetouch->data_dma;
	onetouch->irq->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	ss->extra_deकाष्ठाor = onetouch_release_input;
	ss->extra = onetouch;
#अगर_घोषित CONFIG_PM
	ss->suspend_resume_hook = usb_onetouch_pm_hook;
#पूर्ण_अगर

	error = input_रेजिस्टर_device(onetouch->dev);
	अगर (error)
		जाओ fail3;

	वापस 0;

 fail3:	usb_मुक्त_urb(onetouch->irq);
 fail2:	usb_मुक्त_coherent(udev, ONETOUCH_PKT_LEN,
			  onetouch->data, onetouch->data_dma);
 fail1:	kमुक्त(onetouch);
	input_मुक्त_device(input_dev);
	वापस error;
पूर्ण

अटल व्योम onetouch_release_input(व्योम *onetouch_)
अणु
	काष्ठा usb_onetouch *onetouch = (काष्ठा usb_onetouch *) onetouch_;

	अगर (onetouch) अणु
		usb_समाप्त_urb(onetouch->irq);
		input_unरेजिस्टर_device(onetouch->dev);
		usb_मुक्त_urb(onetouch->irq);
		usb_मुक्त_coherent(onetouch->udev, ONETOUCH_PKT_LEN,
				  onetouch->data, onetouch->data_dma);
	पूर्ण
पूर्ण

अटल काष्ठा scsi_host_ढाँचा onetouch_host_ढाँचा;

अटल पूर्णांक onetouch_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा us_data *us;
	पूर्णांक result;

	result = usb_stor_probe1(&us, पूर्णांकf, id,
			(id - onetouch_usb_ids) + onetouch_unusual_dev_list,
			&onetouch_host_ढाँचा);
	अगर (result)
		वापस result;

	/* Use शेष transport and protocol */

	result = usb_stor_probe2(us);
	वापस result;
पूर्ण

अटल काष्ठा usb_driver onetouch_driver = अणु
	.name =		DRV_NAME,
	.probe =	onetouch_probe,
	.disconnect =	usb_stor_disconnect,
	.suspend =	usb_stor_suspend,
	.resume =	usb_stor_resume,
	.reset_resume =	usb_stor_reset_resume,
	.pre_reset =	usb_stor_pre_reset,
	.post_reset =	usb_stor_post_reset,
	.id_table =	onetouch_usb_ids,
	.soft_unbind =	1,
	.no_dynamic_id = 1,
पूर्ण;

module_usb_stor_driver(onetouch_driver, onetouch_host_ढाँचा, DRV_NAME);
