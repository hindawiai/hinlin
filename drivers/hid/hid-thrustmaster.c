<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * When connected to the machine, the Thrusपंचांगaster wheels appear as
 * a त+genericतझ hid gamepad called "Thrustmaster FFB Wheel".
 *
 * When in this mode not every functionality of the wheel, like the क्रमce feedback,
 * are available. To enable all functionalities of a Thrusपंचांगaster wheel we have to send
 * to it a specअगरic USB CONTROL request with a code dअगरferent क्रम each wheel.
 *
 * This driver tries to understand which model of Thrusपंचांगaster wheel the generic
 * "Thrustmaster FFB Wheel" really is and then sends the appropriate control code.
 *
 * Copyright (c) 2020-2021 Dario Pagani <dario.pagani.146+linuxk@gmail.com>
 * Copyright (c) 2020-2021 Kim Kuparinen <kimi.h.kuparinen@gmail.com>
 */
#समावेश <linux/hid.h>
#समावेश <linux/usb.h>
#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

/*
 * These पूर्णांकerrupts are used to prevent a nasty crash when initializing the
 * T300RS. Used in thrusपंचांगaster_पूर्णांकerrupts().
 */
अटल स्थिर u8 setup_0[] = अणु 0x42, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
अटल स्थिर u8 setup_1[] = अणु 0x0a, 0x04, 0x90, 0x03, 0x00, 0x00, 0x00, 0x00 पूर्ण;
अटल स्थिर u8 setup_2[] = अणु 0x0a, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00 पूर्ण;
अटल स्थिर u8 setup_3[] = अणु 0x0a, 0x04, 0x12, 0x10, 0x00, 0x00, 0x00, 0x00 पूर्ण;
अटल स्थिर u8 setup_4[] = अणु 0x0a, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00 पूर्ण;
अटल स्थिर u8 *स्थिर setup_arr[] = अणु setup_0, setup_1, setup_2, setup_3, setup_4 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक setup_arr_sizes[] = अणु
	ARRAY_SIZE(setup_0),
	ARRAY_SIZE(setup_1),
	ARRAY_SIZE(setup_2),
	ARRAY_SIZE(setup_3),
	ARRAY_SIZE(setup_4)
पूर्ण;
/*
 * This काष्ठा contains क्रम each type of
 * Thrusपंचांगaster wheel
 *
 * Note: The values are stored in the CPU
 * endianness, the USB protocols always use
 * little endian; the macro cpu_to_le[BIT]()
 * must be used when preparing USB packets
 * and vice-versa
 */
काष्ठा पंचांग_wheel_info अणु
	uपूर्णांक16_t wheel_type;

	/*
	 * See when the USB control out packet is prepared...
	 * @TODO The TMX seems to require multiple control codes to चयन.
	 */
	uपूर्णांक16_t चयन_value;

	अक्षर स्थिर *स्थिर wheel_name;
पूर्ण;

/*
 * Known wheels.
 * Note: TMX करोes not work as it requires 2 control packets
 */
अटल स्थिर काष्ठा पंचांग_wheel_info पंचांग_wheels_infos[] = अणु
	अणु0x0306, 0x0006, "Thrustmaster T150RS"पूर्ण,
	अणु0x0206, 0x0005, "Thrustmaster T300RS"पूर्ण,
	अणु0x0204, 0x0005, "Thrustmaster T300 Ferrari Alcantara Edition"पूर्ण,
	अणु0x0002, 0x0002, "Thrustmaster T500RS"पूर्ण
	//अणु0x0407, 0x0001, "Thrustmaster TMX"पूर्ण
पूर्ण;

अटल स्थिर uपूर्णांक8_t पंचांग_wheels_infos_length = 4;

/*
 * This काष्ठाs contains (in little endian) the response data
 * of the wheel to the request 73
 *
 * A sufficient research to understand what each field करोes is not
 * beign conducted yet. The position and meaning of fields are a
 * just a very optimistic guess based on instinct....
 */
काष्ठा __packed पंचांग_wheel_response
अणु
	/*
	 * Seems to be the type of packet
	 * - 0x0049 अगर is data.a (15 bytes)
	 * - 0x0047 अगर is data.b (7 bytes)
	 */
	uपूर्णांक16_t type;

	जोड़ अणु
		काष्ठा __packed अणु
			uपूर्णांक16_t field0;
			uपूर्णांक16_t field1;
			/*
			 * Seems to be the model code of the wheel
			 * Read table thrusपंचांगaster_wheels to values
			 */
			uपूर्णांक16_t model;

			uपूर्णांक16_t field2;
			uपूर्णांक16_t field3;
			uपूर्णांक16_t field4;
			uपूर्णांक16_t field5;
		पूर्ण a;
		काष्ठा __packed अणु
			uपूर्णांक16_t field0;
			uपूर्णांक16_t field1;
			uपूर्णांक16_t model;
		पूर्ण b;
	पूर्ण data;
पूर्ण;

काष्ठा पंचांग_wheel अणु
	काष्ठा usb_device *usb_dev;
	काष्ठा urb *urb;

	काष्ठा usb_ctrlrequest *model_request;
	काष्ठा पंचांग_wheel_response *response;

	काष्ठा usb_ctrlrequest *change_request;
पूर्ण;

/* The control packet to send to wheel */
अटल स्थिर काष्ठा usb_ctrlrequest model_request = अणु
	.bRequestType = 0xc1,
	.bRequest = 73,
	.wValue = 0,
	.wIndex = 0,
	.wLength = cpu_to_le16(0x0010)
पूर्ण;

अटल स्थिर काष्ठा usb_ctrlrequest change_request = अणु
	.bRequestType = 0x41,
	.bRequest = 83,
	.wValue = 0, // Will be filled by the driver
	.wIndex = 0,
	.wLength = 0
पूर्ण;

/*
 * On some setups initializing the T300RS crashes the kernel,
 * these पूर्णांकerrupts fix that particular issue. So far they haven't caused any
 * adverse effects in other wheels.
 */
अटल व्योम thrusपंचांगaster_पूर्णांकerrupts(काष्ठा hid_device *hdev)
अणु
	पूर्णांक ret, trans, i, b_ep;
	u8 *send_buf = kदो_स्मृति(256, GFP_KERNEL);
	काष्ठा usb_host_endpoपूर्णांक *ep;
	काष्ठा device *dev = &hdev->dev;
	काष्ठा usb_पूर्णांकerface *usbअगर = to_usb_पूर्णांकerface(dev->parent);
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(usbअगर);

	अगर (!send_buf) अणु
		hid_err(hdev, "failed allocating send buffer\n");
		वापस;
	पूर्ण

	ep = &usbअगर->cur_altsetting->endpoपूर्णांक[1];
	b_ep = ep->desc.bEndpoपूर्णांकAddress;

	क्रम (i = 0; i < ARRAY_SIZE(setup_arr); ++i) अणु
		स_नकल(send_buf, setup_arr[i], setup_arr_sizes[i]);

		ret = usb_पूर्णांकerrupt_msg(usbdev,
			usb_sndपूर्णांकpipe(usbdev, b_ep),
			send_buf,
			setup_arr_sizes[i],
			&trans,
			USB_CTRL_SET_TIMEOUT);

		अगर (ret) अणु
			hid_err(hdev, "setup data couldn't be sent\n");
			वापस;
		पूर्ण
	पूर्ण

	kमुक्त(send_buf);
पूर्ण

अटल व्योम thrusपंचांगaster_change_handler(काष्ठा urb *urb)
अणु
	काष्ठा hid_device *hdev = urb->context;

	// The wheel seems to समाप्त himself beक्रमe answering the host and thereक्रमe is violating the USB protocol...
	अगर (urb->status == 0 || urb->status == -EPROTO || urb->status == -EPIPE)
		hid_info(hdev, "Success?! The wheel should have been initialized!\n");
	अन्यथा
		hid_warn(hdev, "URB to change wheel mode seems to have failed with error %d\n", urb->status);
पूर्ण

/*
 * Called by the USB subप्रणाली when the wheel responses to our request
 * to get [what it seems to be] the wheel's model.
 *
 * If the model id is recognized then we send an opportune USB CONTROL REQUEST
 * to चयन the wheel to its full capabilities
 */
अटल व्योम thrusपंचांगaster_model_handler(काष्ठा urb *urb)
अणु
	काष्ठा hid_device *hdev = urb->context;
	काष्ठा पंचांग_wheel *पंचांग_wheel = hid_get_drvdata(hdev);
	uपूर्णांक16_t model = 0;
	पूर्णांक i, ret;
	स्थिर काष्ठा पंचांग_wheel_info *twi = 0;

	अगर (urb->status) अणु
		hid_err(hdev, "URB to get model id failed with error %d\n", urb->status);
		वापस;
	पूर्ण

	अगर (पंचांग_wheel->response->type == cpu_to_le16(0x49))
		model = le16_to_cpu(पंचांग_wheel->response->data.a.model);
	अन्यथा अगर (पंचांग_wheel->response->type == cpu_to_le16(0x47))
		model = le16_to_cpu(पंचांग_wheel->response->data.b.model);
	अन्यथा अणु
		hid_err(hdev, "Unknown packet type 0x%x, unable to proceed further with wheel init\n", पंचांग_wheel->response->type);
		वापस;
	पूर्ण

	क्रम (i = 0; i < पंचांग_wheels_infos_length && !twi; i++)
		अगर (पंचांग_wheels_infos[i].wheel_type == model)
			twi = पंचांग_wheels_infos + i;

	अगर (twi)
		hid_info(hdev, "Wheel with model id 0x%x is a %s\n", model, twi->wheel_name);
	अन्यथा अणु
		hid_err(hdev, "Unknown wheel's model id 0x%x, unable to proceed further with wheel init\n", model);
		वापस;
	पूर्ण

	पंचांग_wheel->change_request->wValue = cpu_to_le16(twi->चयन_value);
	usb_fill_control_urb(
		पंचांग_wheel->urb,
		पंचांग_wheel->usb_dev,
		usb_sndctrlpipe(पंचांग_wheel->usb_dev, 0),
		(अक्षर *)पंचांग_wheel->change_request,
		0, 0, // We करो not expect any response from the wheel
		thrusपंचांगaster_change_handler,
		hdev
	);

	ret = usb_submit_urb(पंचांग_wheel->urb, GFP_ATOMIC);
	अगर (ret)
		hid_err(hdev, "Error %d while submitting the change URB. I am unable to initialize this wheel...\n", ret);
पूर्ण

अटल व्योम thrusपंचांगaster_हटाओ(काष्ठा hid_device *hdev)
अणु
	काष्ठा पंचांग_wheel *पंचांग_wheel = hid_get_drvdata(hdev);

	usb_समाप्त_urb(पंचांग_wheel->urb);

	kमुक्त(पंचांग_wheel->response);
	kमुक्त(पंचांग_wheel->model_request);
	usb_मुक्त_urb(पंचांग_wheel->urb);
	kमुक्त(पंचांग_wheel);

	hid_hw_stop(hdev);
पूर्ण

/*
 * Function called by HID when a hid Thrusपंचांगaster FFB wheel is connected to the host.
 * This function starts the hid dev, tries to allocate the पंचांग_wheel data काष्ठाure and
 * finally send an USB CONTROL REQUEST to the wheel to get [what it seems to be] its
 * model type.
 */
अटल पूर्णांक thrusपंचांगaster_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक ret = 0;
	काष्ठा पंचांग_wheel *पंचांग_wheel = 0;

	ret = hid_parse(hdev);
	अगर (ret) अणु
		hid_err(hdev, "parse failed with error %d\n", ret);
		जाओ error0;
	पूर्ण

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT & ~HID_CONNECT_FF);
	अगर (ret) अणु
		hid_err(hdev, "hw start failed with error %d\n", ret);
		जाओ error0;
	पूर्ण

	// Now we allocate the पंचांग_wheel
	पंचांग_wheel = kzalloc(माप(काष्ठा पंचांग_wheel), GFP_KERNEL);
	अगर (!पंचांग_wheel) अणु
		ret = -ENOMEM;
		जाओ error1;
	पूर्ण

	पंचांग_wheel->urb = usb_alloc_urb(0, GFP_ATOMIC);
	अगर (!पंचांग_wheel->urb) अणु
		ret = -ENOMEM;
		जाओ error2;
	पूर्ण

	पंचांग_wheel->model_request = kmemdup(&model_request,
					  माप(काष्ठा usb_ctrlrequest),
					  GFP_KERNEL);
	अगर (!पंचांग_wheel->model_request) अणु
		ret = -ENOMEM;
		जाओ error3;
	पूर्ण

	पंचांग_wheel->response = kzalloc(माप(काष्ठा पंचांग_wheel_response), GFP_KERNEL);
	अगर (!पंचांग_wheel->response) अणु
		ret = -ENOMEM;
		जाओ error4;
	पूर्ण

	पंचांग_wheel->change_request = kzalloc(माप(काष्ठा usb_ctrlrequest), GFP_KERNEL);
	अगर (!पंचांग_wheel->change_request) अणु
		ret = -ENOMEM;
		जाओ error5;
	पूर्ण
	स_नकल(पंचांग_wheel->change_request, &change_request, माप(काष्ठा usb_ctrlrequest));

	पंचांग_wheel->usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(hdev->dev.parent));
	hid_set_drvdata(hdev, पंचांग_wheel);

	thrusपंचांगaster_पूर्णांकerrupts(hdev);

	usb_fill_control_urb(
		पंचांग_wheel->urb,
		पंचांग_wheel->usb_dev,
		usb_rcvctrlpipe(पंचांग_wheel->usb_dev, 0),
		(अक्षर *)पंचांग_wheel->model_request,
		पंचांग_wheel->response,
		माप(काष्ठा पंचांग_wheel_response),
		thrusपंचांगaster_model_handler,
		hdev
	);

	ret = usb_submit_urb(पंचांग_wheel->urb, GFP_ATOMIC);
	अगर (ret)
		hid_err(hdev, "Error %d while submitting the URB. I am unable to initialize this wheel...\n", ret);

	वापस ret;

error5: kमुक्त(पंचांग_wheel->response);
error4: kमुक्त(पंचांग_wheel->model_request);
error3: usb_मुक्त_urb(पंचांग_wheel->urb);
error2: kमुक्त(पंचांग_wheel);
error1: hid_hw_stop(hdev);
error0:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hid_device_id thrusपंचांगaster_devices[] = अणु
	अणु HID_USB_DEVICE(0x044f, 0xb65d)पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, thrusपंचांगaster_devices);

अटल काष्ठा hid_driver thrusपंचांगaster_driver = अणु
	.name = "hid-thrustmaster",
	.id_table = thrusपंचांगaster_devices,
	.probe = thrusपंचांगaster_probe,
	.हटाओ = thrusपंचांगaster_हटाओ,
पूर्ण;

module_hid_driver(thrusपंचांगaster_driver);

MODULE_AUTHOR("Dario Pagani <dario.pagani.146+linuxk@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Driver to initialize some steering wheel joysticks from Thrustmaster");

