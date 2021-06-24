<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HID driver क्रम ELO usb touchscreen 4000/4500
 *
 * Copyright (c) 2013 Jiri Slaby
 *
 * Data parsing taken from elousb driver by Vojtech Pavlik.
 */

#समावेश <linux/hid.h>
#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/workqueue.h>

#समावेश "hid-ids.h"

#घोषणा ELO_PERIODIC_READ_INTERVAL	HZ
#घोषणा ELO_SMARTSET_CMD_TIMEOUT	2000 /* msec */

/* Elo SmartSet commands */
#घोषणा ELO_FLUSH_SMARTSET_RESPONSES	0x02 /* Flush all pending smartset responses */
#घोषणा ELO_SEND_SMARTSET_COMMAND	0x05 /* Send a smartset command */
#घोषणा ELO_GET_SMARTSET_RESPONSE	0x06 /* Get a smartset response */
#घोषणा ELO_DIAG			0x64 /* Diagnostics command */
#घोषणा ELO_SMARTSET_PACKET_SIZE	8

काष्ठा elo_priv अणु
	काष्ठा usb_device *usbdev;
	काष्ठा delayed_work work;
	अचिन्हित अक्षर buffer[ELO_SMARTSET_PACKET_SIZE];
पूर्ण;

अटल काष्ठा workqueue_काष्ठा *wq;
अटल bool use_fw_quirk = true;
module_param(use_fw_quirk, bool, S_IRUGO);
MODULE_PARM_DESC(use_fw_quirk, "Do periodic pokes for broken M firmwares (default = true)");

अटल पूर्णांक elo_input_configured(काष्ठा hid_device *hdev,
		काष्ठा hid_input *hidinput)
अणु
	काष्ठा input_dev *input = hidinput->input;

	/*
	 * ELO devices have one Button usage in GenDesk field, which makes
	 * hid-input map it to BTN_LEFT; that confuses userspace, which then
	 * considers the device to be a mouse/touchpad instead of touchscreen.
	 */
	clear_bit(BTN_LEFT, input->keybit);
	set_bit(BTN_TOUCH, input->keybit);
	set_bit(ABS_PRESSURE, input->असलbit);
	input_set_असल_params(input, ABS_PRESSURE, 0, 256, 0, 0);

	वापस 0;
पूर्ण

अटल व्योम elo_process_data(काष्ठा input_dev *input, स्थिर u8 *data, पूर्णांक size)
अणु
	पूर्णांक press;

	input_report_असल(input, ABS_X, (data[3] << 8) | data[2]);
	input_report_असल(input, ABS_Y, (data[5] << 8) | data[4]);

	press = 0;
	अगर (data[1] & 0x80)
		press = (data[7] << 8) | data[6];
	input_report_असल(input, ABS_PRESSURE, press);

	अगर (data[1] & 0x03) अणु
		input_report_key(input, BTN_TOUCH, 1);
		input_sync(input);
	पूर्ण

	अगर (data[1] & 0x04)
		input_report_key(input, BTN_TOUCH, 0);

	input_sync(input);
पूर्ण

अटल पूर्णांक elo_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
	 u8 *data, पूर्णांक size)
अणु
	काष्ठा hid_input *hidinput;

	अगर (!(hdev->claimed & HID_CLAIMED_INPUT) || list_empty(&hdev->inमाला_दो))
		वापस 0;

	hidinput = list_first_entry(&hdev->inमाला_दो, काष्ठा hid_input, list);

	चयन (report->id) अणु
	हाल 0:
		अगर (data[0] == 'T') अणु	/* Mandatory ELO packet marker */
			elo_process_data(hidinput->input, data, size);
			वापस 1;
		पूर्ण
		अवरोध;
	शेष:	/* unknown report */
		/* Unknown report type; pass upstream */
		hid_info(hdev, "unknown report type %d\n", report->id);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक elo_smartset_send_get(काष्ठा usb_device *dev, u8 command,
		व्योम *data)
अणु
	अचिन्हित पूर्णांक pipe;
	u8 dir;

	अगर (command == ELO_SEND_SMARTSET_COMMAND) अणु
		pipe = usb_sndctrlpipe(dev, 0);
		dir = USB_सूची_OUT;
	पूर्ण अन्यथा अगर (command == ELO_GET_SMARTSET_RESPONSE) अणु
		pipe = usb_rcvctrlpipe(dev, 0);
		dir = USB_सूची_IN;
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस usb_control_msg(dev, pipe, command,
			dir | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0, 0, data, ELO_SMARTSET_PACKET_SIZE,
			ELO_SMARTSET_CMD_TIMEOUT);
पूर्ण

अटल पूर्णांक elo_flush_smartset_responses(काष्ठा usb_device *dev)
अणु
	वापस usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			ELO_FLUSH_SMARTSET_RESPONSES,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0, 0, शून्य, 0, USB_CTRL_SET_TIMEOUT);
पूर्ण

अटल व्योम elo_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा elo_priv *priv = container_of(work, काष्ठा elo_priv, work.work);
	काष्ठा usb_device *dev = priv->usbdev;
	अचिन्हित अक्षर *buffer = priv->buffer;
	पूर्णांक ret;

	ret = elo_flush_smartset_responses(dev);
	अगर (ret < 0) अणु
		dev_err(&dev->dev, "initial FLUSH_SMARTSET_RESPONSES failed, error %d\n",
				ret);
		जाओ fail;
	पूर्ण

	/* send Diagnostics command */
	*buffer = ELO_DIAG;
	ret = elo_smartset_send_get(dev, ELO_SEND_SMARTSET_COMMAND, buffer);
	अगर (ret < 0) अणु
		dev_err(&dev->dev, "send Diagnostics Command failed, error %d\n",
				ret);
		जाओ fail;
	पूर्ण

	/* get the result */
	ret = elo_smartset_send_get(dev, ELO_GET_SMARTSET_RESPONSE, buffer);
	अगर (ret < 0) अणु
		dev_err(&dev->dev, "get Diagnostics Command response failed, error %d\n",
				ret);
		जाओ fail;
	पूर्ण

	/* पढ़ो the ack */
	अगर (*buffer != 'A') अणु
		ret = elo_smartset_send_get(dev, ELO_GET_SMARTSET_RESPONSE,
				buffer);
		अगर (ret < 0) अणु
			dev_err(&dev->dev, "get acknowledge response failed, error %d\n",
					ret);
			जाओ fail;
		पूर्ण
	पूर्ण

fail:
	ret = elo_flush_smartset_responses(dev);
	अगर (ret < 0)
		dev_err(&dev->dev, "final FLUSH_SMARTSET_RESPONSES failed, error %d\n",
				ret);
	queue_delayed_work(wq, &priv->work, ELO_PERIODIC_READ_INTERVAL);
पूर्ण

/*
 * Not all Elo devices need the periodic HID descriptor पढ़ोs.
 * Only firmware version M needs this.
 */
अटल bool elo_broken_firmware(काष्ठा usb_device *dev)
अणु
	काष्ठा usb_device *hub = dev->parent;
	काष्ठा usb_device *child = शून्य;
	u16 fw_lvl = le16_to_cpu(dev->descriptor.bcdDevice);
	u16 child_vid, child_pid;
	पूर्णांक i;
    
	अगर (!use_fw_quirk)
		वापस false;
	अगर (fw_lvl != 0x10d)
		वापस false;

	/* iterate sibling devices of the touch controller */
	usb_hub_क्रम_each_child(hub, i, child) अणु
		child_vid = le16_to_cpu(child->descriptor.idVenकरोr);
		child_pid = le16_to_cpu(child->descriptor.idProduct);

		/*
		 * If one of the devices below is present attached as a sibling of 
		 * the touch controller then  this is a newer IBM 4820 monitor that 
		 * करोes not need the IBM-requested workaround अगर fw level is
		 * 0x010d - aka 'M'.
		 * No other HW can have this combination.
		 */
		अगर (child_vid==0x04b3) अणु
			चयन (child_pid) अणु
			हाल 0x4676: /* 4820 21x Video */
			हाल 0x4677: /* 4820 51x Video */
			हाल 0x4678: /* 4820 2Lx Video */
			हाल 0x4679: /* 4820 5Lx Video */
				वापस false;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक elo_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	काष्ठा elo_priv *priv;
	पूर्णांक ret;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	INIT_DELAYED_WORK(&priv->work, elo_work);
	priv->usbdev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(hdev->dev.parent));

	hid_set_drvdata(hdev, priv);

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed\n");
		जाओ err_मुक्त;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed\n");
		जाओ err_मुक्त;
	पूर्ण

	अगर (elo_broken_firmware(priv->usbdev)) अणु
		hid_info(hdev, "broken firmware found, installing workaround\n");
		queue_delayed_work(wq, &priv->work, ELO_PERIODIC_READ_INTERVAL);
	पूर्ण

	वापस 0;
err_मुक्त:
	kमुक्त(priv);
	वापस ret;
पूर्ण

अटल व्योम elo_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा elo_priv *priv = hid_get_drvdata(hdev);

	hid_hw_stop(hdev);
	cancel_delayed_work_sync(&priv->work);
	kमुक्त(priv);
पूर्ण

अटल स्थिर काष्ठा hid_device_id elo_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ELO, 0x0009), पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ELO, 0x0030), पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, elo_devices);

अटल काष्ठा hid_driver elo_driver = अणु
	.name = "elo",
	.id_table = elo_devices,
	.probe = elo_probe,
	.हटाओ = elo_हटाओ,
	.raw_event = elo_raw_event,
	.input_configured = elo_input_configured,
पूर्ण;

अटल पूर्णांक __init elo_driver_init(व्योम)
अणु
	पूर्णांक ret;

	wq = create_singlethपढ़ो_workqueue("elousb");
	अगर (!wq)
		वापस -ENOMEM;

	ret = hid_रेजिस्टर_driver(&elo_driver);
	अगर (ret)
		destroy_workqueue(wq);

	वापस ret;
पूर्ण
module_init(elo_driver_init);

अटल व्योम __निकास elo_driver_निकास(व्योम)
अणु
	hid_unरेजिस्टर_driver(&elo_driver);
	destroy_workqueue(wq);
पूर्ण
module_निकास(elo_driver_निकास);

MODULE_AUTHOR("Jiri Slaby <jslaby@suse.cz>");
MODULE_LICENSE("GPL");
