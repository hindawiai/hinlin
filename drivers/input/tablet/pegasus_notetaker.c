<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pegasus Mobile Notetaker Pen input tablet driver
 *
 * Copyright (c) 2016 Martin Kepplinger <martink@posteo.de>
 */

/*
 * request packet (control endpoपूर्णांक):
 * |-------------------------------------|
 * | Report ID | Nr of bytes | command   |
 * | (1 byte)  | (1 byte)    | (n bytes) |
 * |-------------------------------------|
 * | 0x02      | n           |           |
 * |-------------------------------------|
 *
 * data packet after set xy mode command, 0x80 0xb5 0x02 0x01
 * and pen is in range:
 *
 * byte	byte name		value (bits)
 * --------------------------------------------
 * 0	status			0 1 0 0 0 0 X X
 * 1	color			0 0 0 0 H 0 S T
 * 2	X low
 * 3	X high
 * 4	Y low
 * 5	Y high
 *
 * X X	battery state:
 *	no state reported	0x00
 *	battery low		0x01
 *	battery good		0x02
 *
 * H	Hovering
 * S	Switch 1 (pen button)
 * T	Tip
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/usb/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>

/* USB HID defines */
#घोषणा USB_REQ_GET_REPORT		0x01
#घोषणा USB_REQ_SET_REPORT		0x09

#घोषणा USB_VENDOR_ID_PEGASUSTECH	0x0e20
#घोषणा USB_DEVICE_ID_PEGASUS_NOTETAKER_EN100	0x0101

/* device specअगरic defines */
#घोषणा NOTETAKER_REPORT_ID		0x02
#घोषणा NOTETAKER_SET_CMD		0x80
#घोषणा NOTETAKER_SET_MODE		0xb5

#घोषणा NOTETAKER_LED_MOUSE		0x02
#घोषणा PEN_MODE_XY			0x01

#घोषणा SPECIAL_COMMAND			0x80
#घोषणा BUTTON_PRESSED			0xb5
#घोषणा COMMAND_VERSION			0xa9

/* in xy data packet */
#घोषणा BATTERY_NO_REPORT		0x40
#घोषणा BATTERY_LOW			0x41
#घोषणा BATTERY_GOOD			0x42
#घोषणा PEN_BUTTON_PRESSED		BIT(1)
#घोषणा PEN_TIP				BIT(0)

काष्ठा pegasus अणु
	अचिन्हित अक्षर *data;
	u8 data_len;
	dma_addr_t data_dma;
	काष्ठा input_dev *dev;
	काष्ठा usb_device *usbdev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	काष्ठा urb *irq;

	/* serialize access to खोलो/suspend */
	काष्ठा mutex pm_mutex;
	bool is_खोलो;

	अक्षर name[128];
	अक्षर phys[64];
	काष्ठा work_काष्ठा init;
पूर्ण;

अटल पूर्णांक pegasus_control_msg(काष्ठा pegasus *pegasus, u8 *data, पूर्णांक len)
अणु
	स्थिर पूर्णांक माप_buf = len + 2;
	पूर्णांक result;
	पूर्णांक error;
	u8 *cmd_buf;

	cmd_buf = kदो_स्मृति(माप_buf, GFP_KERNEL);
	अगर (!cmd_buf)
		वापस -ENOMEM;

	cmd_buf[0] = NOTETAKER_REPORT_ID;
	cmd_buf[1] = len;
	स_नकल(cmd_buf + 2, data, len);

	result = usb_control_msg(pegasus->usbdev,
				 usb_sndctrlpipe(pegasus->usbdev, 0),
				 USB_REQ_SET_REPORT,
				 USB_TYPE_VENDOR | USB_सूची_OUT,
				 0, 0, cmd_buf, माप_buf,
				 USB_CTRL_SET_TIMEOUT);

	kमुक्त(cmd_buf);

	अगर (unlikely(result != माप_buf)) अणु
		error = result < 0 ? result : -EIO;
		dev_err(&pegasus->usbdev->dev, "control msg error: %d\n",
			error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pegasus_set_mode(काष्ठा pegasus *pegasus, u8 mode, u8 led)
अणु
	u8 cmd[] = अणु NOTETAKER_SET_CMD, NOTETAKER_SET_MODE, led, mode पूर्ण;

	वापस pegasus_control_msg(pegasus, cmd, माप(cmd));
पूर्ण

अटल व्योम pegasus_parse_packet(काष्ठा pegasus *pegasus)
अणु
	अचिन्हित अक्षर *data = pegasus->data;
	काष्ठा input_dev *dev = pegasus->dev;
	u16 x, y;

	चयन (data[0]) अणु
	हाल SPECIAL_COMMAND:
		/* device button pressed */
		अगर (data[1] == BUTTON_PRESSED)
			schedule_work(&pegasus->init);

		अवरोध;

	/* xy data */
	हाल BATTERY_LOW:
		dev_warn_once(&dev->dev, "Pen battery low\n");
		fallthrough;

	हाल BATTERY_NO_REPORT:
	हाल BATTERY_GOOD:
		x = le16_to_cpup((__le16 *)&data[2]);
		y = le16_to_cpup((__le16 *)&data[4]);

		/* pen-up event */
		अगर (x == 0 && y == 0)
			अवरोध;

		input_report_key(dev, BTN_TOUCH, data[1] & PEN_TIP);
		input_report_key(dev, BTN_RIGHT, data[1] & PEN_BUTTON_PRESSED);
		input_report_key(dev, BTN_TOOL_PEN, 1);
		input_report_असल(dev, ABS_X, (s16)x);
		input_report_असल(dev, ABS_Y, y);

		input_sync(dev);
		अवरोध;

	शेष:
		dev_warn_once(&pegasus->usbdev->dev,
			      "unknown answer from device\n");
	पूर्ण
पूर्ण

अटल व्योम pegasus_irq(काष्ठा urb *urb)
अणु
	काष्ठा pegasus *pegasus = urb->context;
	काष्ठा usb_device *dev = pegasus->usbdev;
	पूर्णांक retval;

	चयन (urb->status) अणु
	हाल 0:
		pegasus_parse_packet(pegasus);
		usb_mark_last_busy(pegasus->usbdev);
		अवरोध;

	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		dev_err(&dev->dev, "%s - urb shutting down with status: %d",
			__func__, urb->status);
		वापस;

	शेष:
		dev_err(&dev->dev, "%s - nonzero urb status received: %d",
			__func__, urb->status);
		अवरोध;
	पूर्ण

	retval = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (retval)
		dev_err(&dev->dev, "%s - usb_submit_urb failed with result %d",
			__func__, retval);
पूर्ण

अटल व्योम pegasus_init(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pegasus *pegasus = container_of(work, काष्ठा pegasus, init);
	पूर्णांक error;

	error = pegasus_set_mode(pegasus, PEN_MODE_XY, NOTETAKER_LED_MOUSE);
	अगर (error)
		dev_err(&pegasus->usbdev->dev, "pegasus_set_mode error: %d\n",
			error);
पूर्ण

अटल पूर्णांक pegasus_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा pegasus *pegasus = input_get_drvdata(dev);
	पूर्णांक error;

	error = usb_स्वतःpm_get_पूर्णांकerface(pegasus->पूर्णांकf);
	अगर (error)
		वापस error;

	mutex_lock(&pegasus->pm_mutex);
	pegasus->irq->dev = pegasus->usbdev;
	अगर (usb_submit_urb(pegasus->irq, GFP_KERNEL)) अणु
		error = -EIO;
		जाओ err_स्वतःpm_put;
	पूर्ण

	error = pegasus_set_mode(pegasus, PEN_MODE_XY, NOTETAKER_LED_MOUSE);
	अगर (error)
		जाओ err_समाप्त_urb;

	pegasus->is_खोलो = true;
	mutex_unlock(&pegasus->pm_mutex);
	वापस 0;

err_समाप्त_urb:
	usb_समाप्त_urb(pegasus->irq);
	cancel_work_sync(&pegasus->init);
err_स्वतःpm_put:
	mutex_unlock(&pegasus->pm_mutex);
	usb_स्वतःpm_put_पूर्णांकerface(pegasus->पूर्णांकf);
	वापस error;
पूर्ण

अटल व्योम pegasus_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा pegasus *pegasus = input_get_drvdata(dev);

	mutex_lock(&pegasus->pm_mutex);
	usb_समाप्त_urb(pegasus->irq);
	cancel_work_sync(&pegasus->init);
	pegasus->is_खोलो = false;
	mutex_unlock(&pegasus->pm_mutex);

	usb_स्वतःpm_put_पूर्णांकerface(pegasus->पूर्णांकf);
पूर्ण

अटल पूर्णांक pegasus_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा pegasus *pegasus;
	काष्ठा input_dev *input_dev;
	पूर्णांक error;
	पूर्णांक pipe;

	/* We control पूर्णांकerface 0 */
	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceNumber >= 1)
		वापस -ENODEV;

	/* Sanity check that the device has an endpoपूर्णांक */
	अगर (पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs < 1) अणु
		dev_err(&पूर्णांकf->dev, "Invalid number of endpoints\n");
		वापस -EINVAL;
	पूर्ण

	endpoपूर्णांक = &पूर्णांकf->cur_altsetting->endpoपूर्णांक[0].desc;

	pegasus = kzalloc(माप(*pegasus), GFP_KERNEL);
	input_dev = input_allocate_device();
	अगर (!pegasus || !input_dev) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	mutex_init(&pegasus->pm_mutex);

	pegasus->usbdev = dev;
	pegasus->dev = input_dev;
	pegasus->पूर्णांकf = पूर्णांकf;

	pipe = usb_rcvपूर्णांकpipe(dev, endpoपूर्णांक->bEndpoपूर्णांकAddress);
	pegasus->data_len = usb_maxpacket(dev, pipe, usb_pipeout(pipe));

	pegasus->data = usb_alloc_coherent(dev, pegasus->data_len, GFP_KERNEL,
					   &pegasus->data_dma);
	अगर (!pegasus->data) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	pegasus->irq = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!pegasus->irq) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_dma;
	पूर्ण

	usb_fill_पूर्णांक_urb(pegasus->irq, dev, pipe,
			 pegasus->data, pegasus->data_len,
			 pegasus_irq, pegasus, endpoपूर्णांक->bInterval);

	pegasus->irq->transfer_dma = pegasus->data_dma;
	pegasus->irq->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	अगर (dev->manufacturer)
		strlcpy(pegasus->name, dev->manufacturer,
			माप(pegasus->name));

	अगर (dev->product) अणु
		अगर (dev->manufacturer)
			strlcat(pegasus->name, " ", माप(pegasus->name));
		strlcat(pegasus->name, dev->product, माप(pegasus->name));
	पूर्ण

	अगर (!म_माप(pegasus->name))
		snम_लिखो(pegasus->name, माप(pegasus->name),
			 "USB Pegasus Device %04x:%04x",
			 le16_to_cpu(dev->descriptor.idVenकरोr),
			 le16_to_cpu(dev->descriptor.idProduct));

	usb_make_path(dev, pegasus->phys, माप(pegasus->phys));
	strlcat(pegasus->phys, "/input0", माप(pegasus->phys));

	INIT_WORK(&pegasus->init, pegasus_init);

	usb_set_पूर्णांकfdata(पूर्णांकf, pegasus);

	input_dev->name = pegasus->name;
	input_dev->phys = pegasus->phys;
	usb_to_input_id(dev, &input_dev->id);
	input_dev->dev.parent = &पूर्णांकf->dev;

	input_set_drvdata(input_dev, pegasus);

	input_dev->खोलो = pegasus_खोलो;
	input_dev->बंद = pegasus_बंद;

	__set_bit(EV_ABS, input_dev->evbit);
	__set_bit(EV_KEY, input_dev->evbit);

	__set_bit(ABS_X, input_dev->असलbit);
	__set_bit(ABS_Y, input_dev->असलbit);

	__set_bit(BTN_TOUCH, input_dev->keybit);
	__set_bit(BTN_RIGHT, input_dev->keybit);
	__set_bit(BTN_TOOL_PEN, input_dev->keybit);

	__set_bit(INPUT_PROP_सूचीECT, input_dev->propbit);
	__set_bit(INPUT_PROP_POINTER, input_dev->propbit);

	input_set_असल_params(input_dev, ABS_X, -1500, 1500, 8, 0);
	input_set_असल_params(input_dev, ABS_Y, 1600, 3000, 8, 0);

	error = input_रेजिस्टर_device(pegasus->dev);
	अगर (error)
		जाओ err_मुक्त_urb;

	वापस 0;

err_मुक्त_urb:
	usb_मुक्त_urb(pegasus->irq);
err_मुक्त_dma:
	usb_मुक्त_coherent(dev, pegasus->data_len,
			  pegasus->data, pegasus->data_dma);
err_मुक्त_mem:
	input_मुक्त_device(input_dev);
	kमुक्त(pegasus);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	वापस error;
पूर्ण

अटल व्योम pegasus_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा pegasus *pegasus = usb_get_पूर्णांकfdata(पूर्णांकf);

	input_unरेजिस्टर_device(pegasus->dev);

	usb_मुक्त_urb(pegasus->irq);
	usb_मुक्त_coherent(पूर्णांकerface_to_usbdev(पूर्णांकf),
			  pegasus->data_len, pegasus->data,
			  pegasus->data_dma);

	kमुक्त(pegasus);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
पूर्ण

अटल पूर्णांक pegasus_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा pegasus *pegasus = usb_get_पूर्णांकfdata(पूर्णांकf);

	mutex_lock(&pegasus->pm_mutex);
	usb_समाप्त_urb(pegasus->irq);
	cancel_work_sync(&pegasus->init);
	mutex_unlock(&pegasus->pm_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक pegasus_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा pegasus *pegasus = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक retval = 0;

	mutex_lock(&pegasus->pm_mutex);
	अगर (pegasus->is_खोलो && usb_submit_urb(pegasus->irq, GFP_NOIO) < 0)
		retval = -EIO;
	mutex_unlock(&pegasus->pm_mutex);

	वापस retval;
पूर्ण

अटल पूर्णांक pegasus_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा pegasus *pegasus = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक retval = 0;

	mutex_lock(&pegasus->pm_mutex);
	अगर (pegasus->is_खोलो) अणु
		retval = pegasus_set_mode(pegasus, PEN_MODE_XY,
					  NOTETAKER_LED_MOUSE);
		अगर (!retval && usb_submit_urb(pegasus->irq, GFP_NOIO) < 0)
			retval = -EIO;
	पूर्ण
	mutex_unlock(&pegasus->pm_mutex);

	वापस retval;
पूर्ण

अटल स्थिर काष्ठा usb_device_id pegasus_ids[] = अणु
	अणु USB_DEVICE(USB_VENDOR_ID_PEGASUSTECH,
		     USB_DEVICE_ID_PEGASUS_NOTETAKER_EN100) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, pegasus_ids);

अटल काष्ठा usb_driver pegasus_driver = अणु
	.name		= "pegasus_notetaker",
	.probe		= pegasus_probe,
	.disconnect	= pegasus_disconnect,
	.suspend	= pegasus_suspend,
	.resume		= pegasus_resume,
	.reset_resume	= pegasus_reset_resume,
	.id_table	= pegasus_ids,
	.supports_स्वतःsuspend = 1,
पूर्ण;

module_usb_driver(pegasus_driver);

MODULE_AUTHOR("Martin Kepplinger <martink@posteo.de>");
MODULE_DESCRIPTION("Pegasus Mobile Notetaker Pen tablet driver");
MODULE_LICENSE("GPL");
