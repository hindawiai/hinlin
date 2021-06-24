<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Phoenix RC Flight Controller Adapter
 *
 * Copyright (C) 2018 Marcus Folkesson <marcus.folkesson@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/input.h>
#समावेश <linux/mutex.h>
#समावेश <linux/input.h>

#घोषणा PXRC_VENDOR_ID		0x1781
#घोषणा PXRC_PRODUCT_ID		0x0898

काष्ठा pxrc अणु
	काष्ठा input_dev	*input;
	काष्ठा usb_पूर्णांकerface	*पूर्णांकf;
	काष्ठा urb		*urb;
	काष्ठा mutex		pm_mutex;
	bool			is_खोलो;
	अक्षर			phys[64];
पूर्ण;

अटल व्योम pxrc_usb_irq(काष्ठा urb *urb)
अणु
	काष्ठा pxrc *pxrc = urb->context;
	u8 *data = urb->transfer_buffer;
	पूर्णांक error;

	चयन (urb->status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ETIME:
		/* this urb is timing out */
		dev_dbg(&pxrc->पूर्णांकf->dev,
			"%s - urb timed out - was the device unplugged?\n",
			__func__);
		वापस;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
	हाल -EPIPE:
		/* this urb is terminated, clean up */
		dev_dbg(&pxrc->पूर्णांकf->dev, "%s - urb shutting down with status: %d\n",
			__func__, urb->status);
		वापस;
	शेष:
		dev_dbg(&pxrc->पूर्णांकf->dev, "%s - nonzero urb status received: %d\n",
			__func__, urb->status);
		जाओ निकास;
	पूर्ण

	अगर (urb->actual_length == 8) अणु
		input_report_असल(pxrc->input, ABS_X, data[0]);
		input_report_असल(pxrc->input, ABS_Y, data[2]);
		input_report_असल(pxrc->input, ABS_RX, data[3]);
		input_report_असल(pxrc->input, ABS_RY, data[4]);
		input_report_असल(pxrc->input, ABS_RUDDER, data[5]);
		input_report_असल(pxrc->input, ABS_THROTTLE, data[6]);
		input_report_असल(pxrc->input, ABS_MISC, data[7]);

		input_report_key(pxrc->input, BTN_A, data[1]);
	पूर्ण

निकास:
	/* Resubmit to fetch new fresh URBs */
	error = usb_submit_urb(urb, GFP_ATOMIC);
	अगर (error && error != -EPERM)
		dev_err(&pxrc->पूर्णांकf->dev,
			"%s - usb_submit_urb failed with result: %d",
			__func__, error);
पूर्ण

अटल पूर्णांक pxrc_खोलो(काष्ठा input_dev *input)
अणु
	काष्ठा pxrc *pxrc = input_get_drvdata(input);
	पूर्णांक retval;

	mutex_lock(&pxrc->pm_mutex);
	retval = usb_submit_urb(pxrc->urb, GFP_KERNEL);
	अगर (retval) अणु
		dev_err(&pxrc->पूर्णांकf->dev,
			"%s - usb_submit_urb failed, error: %d\n",
			__func__, retval);
		retval = -EIO;
		जाओ out;
	पूर्ण

	pxrc->is_खोलो = true;

out:
	mutex_unlock(&pxrc->pm_mutex);
	वापस retval;
पूर्ण

अटल व्योम pxrc_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा pxrc *pxrc = input_get_drvdata(input);

	mutex_lock(&pxrc->pm_mutex);
	usb_समाप्त_urb(pxrc->urb);
	pxrc->is_खोलो = false;
	mutex_unlock(&pxrc->pm_mutex);
पूर्ण

अटल व्योम pxrc_मुक्त_urb(व्योम *_pxrc)
अणु
	काष्ठा pxrc *pxrc = _pxrc;

	usb_मुक्त_urb(pxrc->urb);
पूर्ण

अटल पूर्णांक pxrc_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		      स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा pxrc *pxrc;
	काष्ठा usb_endpoपूर्णांक_descriptor *epirq;
	माप_प्रकार xfer_size;
	व्योम *xfer_buf;
	पूर्णांक error;

	/*
	 * Locate the endpoपूर्णांक inक्रमmation. This device only has an
	 * पूर्णांकerrupt endpoपूर्णांक.
	 */
	error = usb_find_common_endpoपूर्णांकs(पूर्णांकf->cur_altsetting,
					  शून्य, शून्य, &epirq, शून्य);
	अगर (error) अणु
		dev_err(&पूर्णांकf->dev, "Could not find endpoint\n");
		वापस error;
	पूर्ण

	pxrc = devm_kzalloc(&पूर्णांकf->dev, माप(*pxrc), GFP_KERNEL);
	अगर (!pxrc)
		वापस -ENOMEM;

	mutex_init(&pxrc->pm_mutex);
	pxrc->पूर्णांकf = पूर्णांकf;

	usb_set_पूर्णांकfdata(pxrc->पूर्णांकf, pxrc);

	xfer_size = usb_endpoपूर्णांक_maxp(epirq);
	xfer_buf = devm_kदो_स्मृति(&पूर्णांकf->dev, xfer_size, GFP_KERNEL);
	अगर (!xfer_buf)
		वापस -ENOMEM;

	pxrc->urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!pxrc->urb)
		वापस -ENOMEM;

	error = devm_add_action_or_reset(&पूर्णांकf->dev, pxrc_मुक्त_urb, pxrc);
	अगर (error)
		वापस error;

	usb_fill_पूर्णांक_urb(pxrc->urb, udev,
			 usb_rcvपूर्णांकpipe(udev, epirq->bEndpoपूर्णांकAddress),
			 xfer_buf, xfer_size, pxrc_usb_irq, pxrc, 1);

	pxrc->input = devm_input_allocate_device(&पूर्णांकf->dev);
	अगर (!pxrc->input) अणु
		dev_err(&पूर्णांकf->dev, "couldn't allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	pxrc->input->name = "PXRC Flight Controller Adapter";

	usb_make_path(udev, pxrc->phys, माप(pxrc->phys));
	strlcat(pxrc->phys, "/input0", माप(pxrc->phys));
	pxrc->input->phys = pxrc->phys;

	usb_to_input_id(udev, &pxrc->input->id);

	pxrc->input->खोलो = pxrc_खोलो;
	pxrc->input->बंद = pxrc_बंद;

	input_set_capability(pxrc->input, EV_KEY, BTN_A);
	input_set_असल_params(pxrc->input, ABS_X, 0, 255, 0, 0);
	input_set_असल_params(pxrc->input, ABS_Y, 0, 255, 0, 0);
	input_set_असल_params(pxrc->input, ABS_RX, 0, 255, 0, 0);
	input_set_असल_params(pxrc->input, ABS_RY, 0, 255, 0, 0);
	input_set_असल_params(pxrc->input, ABS_RUDDER, 0, 255, 0, 0);
	input_set_असल_params(pxrc->input, ABS_THROTTLE, 0, 255, 0, 0);
	input_set_असल_params(pxrc->input, ABS_MISC, 0, 255, 0, 0);

	input_set_drvdata(pxrc->input, pxrc);

	error = input_रेजिस्टर_device(pxrc->input);
	अगर (error)
		वापस error;

	वापस 0;
पूर्ण

अटल व्योम pxrc_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	/* All driver resources are devm-managed. */
पूर्ण

अटल पूर्णांक pxrc_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा pxrc *pxrc = usb_get_पूर्णांकfdata(पूर्णांकf);

	mutex_lock(&pxrc->pm_mutex);
	अगर (pxrc->is_खोलो)
		usb_समाप्त_urb(pxrc->urb);
	mutex_unlock(&pxrc->pm_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक pxrc_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा pxrc *pxrc = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक retval = 0;

	mutex_lock(&pxrc->pm_mutex);
	अगर (pxrc->is_खोलो && usb_submit_urb(pxrc->urb, GFP_KERNEL) < 0)
		retval = -EIO;

	mutex_unlock(&pxrc->pm_mutex);
	वापस retval;
पूर्ण

अटल पूर्णांक pxrc_pre_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा pxrc *pxrc = usb_get_पूर्णांकfdata(पूर्णांकf);

	mutex_lock(&pxrc->pm_mutex);
	usb_समाप्त_urb(pxrc->urb);
	वापस 0;
पूर्ण

अटल पूर्णांक pxrc_post_reset(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा pxrc *pxrc = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक retval = 0;

	अगर (pxrc->is_खोलो && usb_submit_urb(pxrc->urb, GFP_KERNEL) < 0)
		retval = -EIO;

	mutex_unlock(&pxrc->pm_mutex);

	वापस retval;
पूर्ण

अटल पूर्णांक pxrc_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस pxrc_resume(पूर्णांकf);
पूर्ण

अटल स्थिर काष्ठा usb_device_id pxrc_table[] = अणु
	अणु USB_DEVICE(PXRC_VENDOR_ID, PXRC_PRODUCT_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, pxrc_table);

अटल काष्ठा usb_driver pxrc_driver = अणु
	.name =		"pxrc",
	.probe =	pxrc_probe,
	.disconnect =	pxrc_disconnect,
	.id_table =	pxrc_table,
	.suspend	= pxrc_suspend,
	.resume		= pxrc_resume,
	.pre_reset	= pxrc_pre_reset,
	.post_reset	= pxrc_post_reset,
	.reset_resume	= pxrc_reset_resume,
पूर्ण;

module_usb_driver(pxrc_driver);

MODULE_AUTHOR("Marcus Folkesson <marcus.folkesson@gmail.com>");
MODULE_DESCRIPTION("PhoenixRC Flight Controller Adapter");
MODULE_LICENSE("GPL v2");
