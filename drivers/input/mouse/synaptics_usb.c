<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * USB Synaptics device driver
 *
 *  Copyright (c) 2002 Rob Miller (rob@inpharmatica . co . uk)
 *  Copyright (c) 2003 Ron Lee (ron@debian.org)
 *	cPad driver क्रम kernel 2.4
 *
 *  Copyright (c) 2004 Jan Steinhoff (cpad@jan-steinhoff . de)
 *  Copyright (c) 2004 Ron Lee (ron@debian.org)
 *	rewritten क्रम kernel 2.6
 *
 *  cPad display अक्षरacter device part is not included. It can be found at
 *  http://jan-steinhoff.de/linux/synaptics-usb.hपंचांगl
 *
 * Bases on:	usb_skeleton.c v2.2 by Greg Kroah-Harपंचांगan
 *		drivers/hid/usbhid/usbmouse.c by Vojtech Pavlik
 *		drivers/input/mouse/synaptics.c by Peter Osterlund
 *
 * Trademarks are the property of their respective owners.
 */

/*
 * There are three dअगरferent types of Synaptics USB devices: Touchpads,
 * touchsticks (or trackpoपूर्णांकs), and touchscreens. Touchpads are well supported
 * by this driver, touchstick support has not been tested much yet, and
 * touchscreens have not been tested at all.
 *
 * Up to three alternate settings are possible:
 *	setting 0: one पूर्णांक endpoपूर्णांक क्रम relative movement (used by usbhid.ko)
 *	setting 1: one पूर्णांक endpoपूर्णांक क्रम असलolute finger position
 *	setting 2 (cPad only): one पूर्णांक endpoपूर्णांक क्रम असलolute finger position and
 *		   two bulk endpoपूर्णांकs क्रम the display (in/out)
 * This driver uses setting 1.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/usb.h>
#समावेश <linux/input.h>
#समावेश <linux/usb/input.h>

#घोषणा USB_VENDOR_ID_SYNAPTICS	0x06cb
#घोषणा USB_DEVICE_ID_SYNAPTICS_TP	0x0001	/* Synaptics USB TouchPad */
#घोषणा USB_DEVICE_ID_SYNAPTICS_INT_TP	0x0002	/* Integrated USB TouchPad */
#घोषणा USB_DEVICE_ID_SYNAPTICS_CPAD	0x0003	/* Synaptics cPad */
#घोषणा USB_DEVICE_ID_SYNAPTICS_TS	0x0006	/* Synaptics TouchScreen */
#घोषणा USB_DEVICE_ID_SYNAPTICS_STICK	0x0007	/* Synaptics USB Styk */
#घोषणा USB_DEVICE_ID_SYNAPTICS_WP	0x0008	/* Synaptics USB WheelPad */
#घोषणा USB_DEVICE_ID_SYNAPTICS_COMP_TP	0x0009	/* Composite USB TouchPad */
#घोषणा USB_DEVICE_ID_SYNAPTICS_WTP	0x0010	/* Wireless TouchPad */
#घोषणा USB_DEVICE_ID_SYNAPTICS_DPAD	0x0013	/* DisplayPad */

#घोषणा SYNUSB_TOUCHPAD			(1 << 0)
#घोषणा SYNUSB_STICK			(1 << 1)
#घोषणा SYNUSB_TOUCHSCREEN		(1 << 2)
#घोषणा SYNUSB_AUXDISPLAY		(1 << 3) /* For cPad */
#घोषणा SYNUSB_COMBO			(1 << 4) /* Composite device (TP + stick) */
#घोषणा SYNUSB_IO_ALWAYS		(1 << 5)

#घोषणा USB_DEVICE_SYNAPTICS(prod, kind)		\
	USB_DEVICE(USB_VENDOR_ID_SYNAPTICS,		\
		   USB_DEVICE_ID_SYNAPTICS_##prod),	\
	.driver_info = (kind),

#घोषणा SYNUSB_RECV_SIZE	8

#घोषणा XMIN_NOMINAL		1472
#घोषणा XMAX_NOMINAL		5472
#घोषणा YMIN_NOMINAL		1408
#घोषणा YMAX_NOMINAL		4448

काष्ठा synusb अणु
	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा urb *urb;
	अचिन्हित अक्षर *data;

	/* serialize access to खोलो/suspend */
	काष्ठा mutex pm_mutex;
	bool is_खोलो;

	/* input device related data काष्ठाures */
	काष्ठा input_dev *input;
	अक्षर name[128];
	अक्षर phys[64];

	/* अक्षरacteristics of the device */
	अचिन्हित दीर्घ flags;
पूर्ण;

अटल व्योम synusb_report_buttons(काष्ठा synusb *synusb)
अणु
	काष्ठा input_dev *input_dev = synusb->input;

	input_report_key(input_dev, BTN_LEFT, synusb->data[1] & 0x04);
	input_report_key(input_dev, BTN_RIGHT, synusb->data[1] & 0x01);
	input_report_key(input_dev, BTN_MIDDLE, synusb->data[1] & 0x02);
पूर्ण

अटल व्योम synusb_report_stick(काष्ठा synusb *synusb)
अणु
	काष्ठा input_dev *input_dev = synusb->input;
	पूर्णांक x, y;
	अचिन्हित पूर्णांक pressure;

	pressure = synusb->data[6];
	x = (s16)(be16_to_cpup((__be16 *)&synusb->data[2]) << 3) >> 7;
	y = (s16)(be16_to_cpup((__be16 *)&synusb->data[4]) << 3) >> 7;

	अगर (pressure > 0) अणु
		input_report_rel(input_dev, REL_X, x);
		input_report_rel(input_dev, REL_Y, -y);
	पूर्ण

	input_report_असल(input_dev, ABS_PRESSURE, pressure);

	synusb_report_buttons(synusb);

	input_sync(input_dev);
पूर्ण

अटल व्योम synusb_report_touchpad(काष्ठा synusb *synusb)
अणु
	काष्ठा input_dev *input_dev = synusb->input;
	अचिन्हित पूर्णांक num_fingers, tool_width;
	अचिन्हित पूर्णांक x, y;
	अचिन्हित पूर्णांक pressure, w;

	pressure = synusb->data[6];
	x = be16_to_cpup((__be16 *)&synusb->data[2]);
	y = be16_to_cpup((__be16 *)&synusb->data[4]);
	w = synusb->data[0] & 0x0f;

	अगर (pressure > 0) अणु
		num_fingers = 1;
		tool_width = 5;
		चयन (w) अणु
		हाल 0 ... 1:
			num_fingers = 2 + w;
			अवरोध;

		हाल 2:	                /* pen, pretend its a finger */
			अवरोध;

		हाल 4 ... 15:
			tool_width = w;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		num_fingers = 0;
		tool_width = 0;
	पूर्ण

	/*
	 * Post events
	 * BTN_TOUCH has to be first as mousedev relies on it when करोing
	 * असलolute -> relative conversion
	 */

	अगर (pressure > 30)
		input_report_key(input_dev, BTN_TOUCH, 1);
	अगर (pressure < 25)
		input_report_key(input_dev, BTN_TOUCH, 0);

	अगर (num_fingers > 0) अणु
		input_report_असल(input_dev, ABS_X, x);
		input_report_असल(input_dev, ABS_Y,
				 YMAX_NOMINAL + YMIN_NOMINAL - y);
	पूर्ण

	input_report_असल(input_dev, ABS_PRESSURE, pressure);
	input_report_असल(input_dev, ABS_TOOL_WIDTH, tool_width);

	input_report_key(input_dev, BTN_TOOL_FINGER, num_fingers == 1);
	input_report_key(input_dev, BTN_TOOL_DOUBLETAP, num_fingers == 2);
	input_report_key(input_dev, BTN_TOOL_TRIPLETAP, num_fingers == 3);

	synusb_report_buttons(synusb);
	अगर (synusb->flags & SYNUSB_AUXDISPLAY)
		input_report_key(input_dev, BTN_MIDDLE, synusb->data[1] & 0x08);

	input_sync(input_dev);
पूर्ण

अटल व्योम synusb_irq(काष्ठा urb *urb)
अणु
	काष्ठा synusb *synusb = urb->context;
	पूर्णांक error;

	/* Check our status in हाल we need to bail out early. */
	चयन (urb->status) अणु
	हाल 0:
		usb_mark_last_busy(synusb->udev);
		अवरोध;

	/* Device went away so करोn't keep trying to पढ़ो from it. */
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		वापस;

	शेष:
		जाओ resubmit;
		अवरोध;
	पूर्ण

	अगर (synusb->flags & SYNUSB_STICK)
		synusb_report_stick(synusb);
	अन्यथा
		synusb_report_touchpad(synusb);

resubmit:
	error = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (error && error != -EPERM)
		dev_err(&synusb->पूर्णांकf->dev,
			"%s - usb_submit_urb failed with result: %d",
			__func__, error);
पूर्ण

अटल काष्ठा usb_endpoपूर्णांक_descriptor *
synusb_get_in_endpoपूर्णांक(काष्ठा usb_host_पूर्णांकerface *अगरace)
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

अटल पूर्णांक synusb_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा synusb *synusb = input_get_drvdata(dev);
	पूर्णांक retval;

	retval = usb_स्वतःpm_get_पूर्णांकerface(synusb->पूर्णांकf);
	अगर (retval) अणु
		dev_err(&synusb->पूर्णांकf->dev,
			"%s - usb_autopm_get_interface failed, error: %d\n",
			__func__, retval);
		वापस retval;
	पूर्ण

	mutex_lock(&synusb->pm_mutex);
	retval = usb_submit_urb(synusb->urb, GFP_KERNEL);
	अगर (retval) अणु
		dev_err(&synusb->पूर्णांकf->dev,
			"%s - usb_submit_urb failed, error: %d\n",
			__func__, retval);
		retval = -EIO;
		जाओ out;
	पूर्ण

	synusb->पूर्णांकf->needs_remote_wakeup = 1;
	synusb->is_खोलो = true;

out:
	mutex_unlock(&synusb->pm_mutex);
	usb_स्वतःpm_put_पूर्णांकerface(synusb->पूर्णांकf);
	वापस retval;
पूर्ण

अटल व्योम synusb_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा synusb *synusb = input_get_drvdata(dev);
	पूर्णांक स्वतःpm_error;

	स्वतःpm_error = usb_स्वतःpm_get_पूर्णांकerface(synusb->पूर्णांकf);

	mutex_lock(&synusb->pm_mutex);
	usb_समाप्त_urb(synusb->urb);
	synusb->पूर्णांकf->needs_remote_wakeup = 0;
	synusb->is_खोलो = false;
	mutex_unlock(&synusb->pm_mutex);

	अगर (!स्वतःpm_error)
		usb_स्वतःpm_put_पूर्णांकerface(synusb->पूर्णांकf);
पूर्ण

अटल पूर्णांक synusb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_endpoपूर्णांक_descriptor *ep;
	काष्ठा synusb *synusb;
	काष्ठा input_dev *input_dev;
	अचिन्हित पूर्णांक पूर्णांकf_num = पूर्णांकf->cur_altsetting->desc.bInterfaceNumber;
	अचिन्हित पूर्णांक altsetting = min(पूर्णांकf->num_altsetting, 1U);
	पूर्णांक error;

	error = usb_set_पूर्णांकerface(udev, पूर्णांकf_num, altsetting);
	अगर (error) अणु
		dev_err(&udev->dev,
			"Can not set alternate setting to %i, error: %i",
			altsetting, error);
		वापस error;
	पूर्ण

	ep = synusb_get_in_endpoपूर्णांक(पूर्णांकf->cur_altsetting);
	अगर (!ep)
		वापस -ENODEV;

	synusb = kzalloc(माप(*synusb), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!synusb || !input_dev) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	synusb->udev = udev;
	synusb->पूर्णांकf = पूर्णांकf;
	synusb->input = input_dev;
	mutex_init(&synusb->pm_mutex);

	synusb->flags = id->driver_info;
	अगर (synusb->flags & SYNUSB_COMBO) अणु
		/*
		 * This is a combo device, we need to set proper
		 * capability, depending on the पूर्णांकerface.
		 */
		synusb->flags |= पूर्णांकf_num == 1 ?
					SYNUSB_STICK : SYNUSB_TOUCHPAD;
	पूर्ण

	synusb->urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!synusb->urb) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	synusb->data = usb_alloc_coherent(udev, SYNUSB_RECV_SIZE, GFP_KERNEL,
					  &synusb->urb->transfer_dma);
	अगर (!synusb->data) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_urb;
	पूर्ण

	usb_fill_पूर्णांक_urb(synusb->urb, udev,
			 usb_rcvपूर्णांकpipe(udev, ep->bEndpoपूर्णांकAddress),
			 synusb->data, SYNUSB_RECV_SIZE,
			 synusb_irq, synusb,
			 ep->bInterval);
	synusb->urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	अगर (udev->manufacturer)
		strlcpy(synusb->name, udev->manufacturer,
			माप(synusb->name));

	अगर (udev->product) अणु
		अगर (udev->manufacturer)
			strlcat(synusb->name, " ", माप(synusb->name));
		strlcat(synusb->name, udev->product, माप(synusb->name));
	पूर्ण

	अगर (!म_माप(synusb->name))
		snम_लिखो(synusb->name, माप(synusb->name),
			 "USB Synaptics Device %04x:%04x",
			 le16_to_cpu(udev->descriptor.idVenकरोr),
			 le16_to_cpu(udev->descriptor.idProduct));

	अगर (synusb->flags & SYNUSB_STICK)
		strlcat(synusb->name, " (Stick)", माप(synusb->name));

	usb_make_path(udev, synusb->phys, माप(synusb->phys));
	strlcat(synusb->phys, "/input0", माप(synusb->phys));

	input_dev->name = synusb->name;
	input_dev->phys = synusb->phys;
	usb_to_input_id(udev, &input_dev->id);
	input_dev->dev.parent = &synusb->पूर्णांकf->dev;

	अगर (!(synusb->flags & SYNUSB_IO_ALWAYS)) अणु
		input_dev->खोलो = synusb_खोलो;
		input_dev->बंद = synusb_बंद;
	पूर्ण

	input_set_drvdata(input_dev, synusb);

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);

	अगर (synusb->flags & SYNUSB_STICK) अणु
		__set_bit(EV_REL, input_dev->evbit);
		__set_bit(REL_X, input_dev->relbit);
		__set_bit(REL_Y, input_dev->relbit);
		__set_bit(INPUT_PROP_POINTING_STICK, input_dev->propbit);
		input_set_असल_params(input_dev, ABS_PRESSURE, 0, 127, 0, 0);
	पूर्ण अन्यथा अणु
		input_set_असल_params(input_dev, ABS_X,
				     XMIN_NOMINAL, XMAX_NOMINAL, 0, 0);
		input_set_असल_params(input_dev, ABS_Y,
				     YMIN_NOMINAL, YMAX_NOMINAL, 0, 0);
		input_set_असल_params(input_dev, ABS_PRESSURE, 0, 255, 0, 0);
		input_set_असल_params(input_dev, ABS_TOOL_WIDTH, 0, 15, 0, 0);
		__set_bit(BTN_TOUCH, input_dev->keybit);
		__set_bit(BTN_TOOL_FINGER, input_dev->keybit);
		__set_bit(BTN_TOOL_DOUBLETAP, input_dev->keybit);
		__set_bit(BTN_TOOL_TRIPLETAP, input_dev->keybit);
	पूर्ण

	अगर (synusb->flags & SYNUSB_TOUCHSCREEN)
		__set_bit(INPUT_PROP_सूचीECT, input_dev->propbit);
	अन्यथा
		__set_bit(INPUT_PROP_POINTER, input_dev->propbit);

	__set_bit(BTN_LEFT, input_dev->keybit);
	__set_bit(BTN_RIGHT, input_dev->keybit);
	__set_bit(BTN_MIDDLE, input_dev->keybit);

	usb_set_पूर्णांकfdata(पूर्णांकf, synusb);

	अगर (synusb->flags & SYNUSB_IO_ALWAYS) अणु
		error = synusb_खोलो(input_dev);
		अगर (error)
			जाओ err_मुक्त_dma;
	पूर्ण

	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(&udev->dev,
			"Failed to register input device, error %d\n",
			error);
		जाओ err_stop_io;
	पूर्ण

	वापस 0;

err_stop_io:
	अगर (synusb->flags & SYNUSB_IO_ALWAYS)
		synusb_बंद(synusb->input);
err_मुक्त_dma:
	usb_मुक्त_coherent(udev, SYNUSB_RECV_SIZE, synusb->data,
			  synusb->urb->transfer_dma);
err_मुक्त_urb:
	usb_मुक्त_urb(synusb->urb);
err_मुक्त_mem:
	input_मुक्त_device(input_dev);
	kमुक्त(synusb);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	वापस error;
पूर्ण

अटल व्योम synusb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा synusb *synusb = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	अगर (synusb->flags & SYNUSB_IO_ALWAYS)
		synusb_बंद(synusb->input);

	input_unरेजिस्टर_device(synusb->input);

	usb_मुक्त_coherent(udev, SYNUSB_RECV_SIZE, synusb->data,
			  synusb->urb->transfer_dma);
	usb_मुक्त_urb(synusb->urb);
	kमुक्त(synusb);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
पूर्ण

अटल पूर्णांक synusb_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा synusb *synusb = usb_get_पूर्णांकfdata(पूर्णांकf);

	mutex_lock(&synusb->pm_mutex);
	usb_समाप्त_urb(synusb->urb);
	mutex_unlock(&synusb->pm_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक synusb_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा synusb *synusb = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक retval = 0;

	mutex_lock(&synusb->pm_mutex);

	अगर ((synusb->is_खोलो || (synusb->flags & SYNUSB_IO_ALWAYS)) &&
	    usb_submit_urb(synusb->urb, GFP_NOIO) < 0) अणु
		retval = -EIO;
	पूर्ण

	mutex_unlock(&synusb->pm_mutex);

	वापस retval;
पूर्ण

अटल पूर्णांक synusb_pre_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा synusb *synusb = usb_get_पूर्णांकfdata(पूर्णांकf);

	mutex_lock(&synusb->pm_mutex);
	usb_समाप्त_urb(synusb->urb);

	वापस 0;
पूर्ण

अटल पूर्णांक synusb_post_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा synusb *synusb = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक retval = 0;

	अगर ((synusb->is_खोलो || (synusb->flags & SYNUSB_IO_ALWAYS)) &&
	    usb_submit_urb(synusb->urb, GFP_NOIO) < 0) अणु
		retval = -EIO;
	पूर्ण

	mutex_unlock(&synusb->pm_mutex);

	वापस retval;
पूर्ण

अटल पूर्णांक synusb_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस synusb_resume(पूर्णांकf);
पूर्ण

अटल स्थिर काष्ठा usb_device_id synusb_idtable[] = अणु
	अणु USB_DEVICE_SYNAPTICS(TP, SYNUSB_TOUCHPAD) पूर्ण,
	अणु USB_DEVICE_SYNAPTICS(INT_TP, SYNUSB_TOUCHPAD) पूर्ण,
	अणु USB_DEVICE_SYNAPTICS(CPAD,
		SYNUSB_TOUCHPAD | SYNUSB_AUXDISPLAY | SYNUSB_IO_ALWAYS) पूर्ण,
	अणु USB_DEVICE_SYNAPTICS(TS, SYNUSB_TOUCHSCREEN) पूर्ण,
	अणु USB_DEVICE_SYNAPTICS(STICK, SYNUSB_STICK) पूर्ण,
	अणु USB_DEVICE_SYNAPTICS(WP, SYNUSB_TOUCHPAD) पूर्ण,
	अणु USB_DEVICE_SYNAPTICS(COMP_TP, SYNUSB_COMBO) पूर्ण,
	अणु USB_DEVICE_SYNAPTICS(WTP, SYNUSB_TOUCHPAD) पूर्ण,
	अणु USB_DEVICE_SYNAPTICS(DPAD, SYNUSB_TOUCHPAD) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, synusb_idtable);

अटल काष्ठा usb_driver synusb_driver = अणु
	.name		= "synaptics_usb",
	.probe		= synusb_probe,
	.disconnect	= synusb_disconnect,
	.id_table	= synusb_idtable,
	.suspend	= synusb_suspend,
	.resume		= synusb_resume,
	.pre_reset	= synusb_pre_reset,
	.post_reset	= synusb_post_reset,
	.reset_resume	= synusb_reset_resume,
	.supports_स्वतःsuspend = 1,
पूर्ण;

module_usb_driver(synusb_driver);

MODULE_AUTHOR("Rob Miller <rob@inpharmatica.co.uk>, "
              "Ron Lee <ron@debian.org>, "
              "Jan Steinhoff <cpad@jan-steinhoff.de>");
MODULE_DESCRIPTION("Synaptics USB device driver");
MODULE_LICENSE("GPL");
