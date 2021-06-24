<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2010-2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/ch11.h>

#घोषणा TEST_SE0_NAK_PID			0x0101
#घोषणा TEST_J_PID				0x0102
#घोषणा TEST_K_PID				0x0103
#घोषणा TEST_PACKET_PID				0x0104
#घोषणा TEST_HS_HOST_PORT_SUSPEND_RESUME	0x0106
#घोषणा TEST_SINGLE_STEP_GET_DEV_DESC		0x0107
#घोषणा TEST_SINGLE_STEP_SET_FEATURE		0x0108

अटल पूर्णांक ehset_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		       स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_device *hub_udev = dev->parent;
	काष्ठा usb_device_descriptor buf;
	u8 portnum = dev->portnum;
	u16 test_pid = le16_to_cpu(dev->descriptor.idProduct);

	चयन (test_pid) अणु
	हाल TEST_SE0_NAK_PID:
		ret = usb_control_msg_send(hub_udev, 0, USB_REQ_SET_FEATURE,
					   USB_RT_PORT, USB_PORT_FEAT_TEST,
					   (USB_TEST_SE0_NAK << 8) | portnum,
					   शून्य, 0, 1000, GFP_KERNEL);
		अवरोध;
	हाल TEST_J_PID:
		ret = usb_control_msg_send(hub_udev, 0, USB_REQ_SET_FEATURE,
					   USB_RT_PORT, USB_PORT_FEAT_TEST,
					   (USB_TEST_J << 8) | portnum, शून्य, 0,
					   1000, GFP_KERNEL);
		अवरोध;
	हाल TEST_K_PID:
		ret = usb_control_msg_send(hub_udev, 0, USB_REQ_SET_FEATURE,
					   USB_RT_PORT, USB_PORT_FEAT_TEST,
					   (USB_TEST_K << 8) | portnum, शून्य, 0,
					   1000, GFP_KERNEL);
		अवरोध;
	हाल TEST_PACKET_PID:
		ret = usb_control_msg_send(hub_udev, 0, USB_REQ_SET_FEATURE,
					   USB_RT_PORT, USB_PORT_FEAT_TEST,
					   (USB_TEST_PACKET << 8) | portnum,
					   शून्य, 0, 1000, GFP_KERNEL);
		अवरोध;
	हाल TEST_HS_HOST_PORT_SUSPEND_RESUME:
		/* Test: रुको क्रम 15secs -> suspend -> 15secs delay -> resume */
		msleep(15 * 1000);
		ret = usb_control_msg_send(hub_udev, 0, USB_REQ_SET_FEATURE,
					   USB_RT_PORT, USB_PORT_FEAT_SUSPEND,
					   portnum, शून्य, 0, 1000, GFP_KERNEL);
		अगर (ret < 0)
			अवरोध;

		msleep(15 * 1000);
		ret = usb_control_msg_send(hub_udev, 0, USB_REQ_CLEAR_FEATURE,
					   USB_RT_PORT, USB_PORT_FEAT_SUSPEND,
					   portnum, शून्य, 0, 1000, GFP_KERNEL);
		अवरोध;
	हाल TEST_SINGLE_STEP_GET_DEV_DESC:
		/* Test: रुको क्रम 15secs -> GetDescriptor request */
		msleep(15 * 1000);

		ret = usb_control_msg_recv(dev, 0, USB_REQ_GET_DESCRIPTOR,
					   USB_सूची_IN, USB_DT_DEVICE << 8, 0,
					   &buf, USB_DT_DEVICE_SIZE,
					   USB_CTRL_GET_TIMEOUT, GFP_KERNEL);
		अवरोध;
	हाल TEST_SINGLE_STEP_SET_FEATURE:
		/*
		 * GetDescriptor SETUP request -> 15secs delay -> IN & STATUS
		 *
		 * Note, this test is only supported on root hubs since the
		 * SetPortFeature handling can only be करोne inside the HCD's
		 * hub_control callback function.
		 */
		अगर (hub_udev != dev->bus->root_hub) अणु
			dev_err(&पूर्णांकf->dev, "SINGLE_STEP_SET_FEATURE test only supported on root hub\n");
			अवरोध;
		पूर्ण

		ret = usb_control_msg_send(hub_udev, 0, USB_REQ_SET_FEATURE,
					   USB_RT_PORT, USB_PORT_FEAT_TEST,
					   (6 << 8) | portnum, शून्य, 0,
					   60 * 1000, GFP_KERNEL);

		अवरोध;
	शेष:
		dev_err(&पूर्णांकf->dev, "%s: unsupported PID: 0x%x\n",
			__func__, test_pid);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ehset_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
पूर्ण

अटल स्थिर काष्ठा usb_device_id ehset_id_table[] = अणु
	अणु USB_DEVICE(0x1a0a, TEST_SE0_NAK_PID) पूर्ण,
	अणु USB_DEVICE(0x1a0a, TEST_J_PID) पूर्ण,
	अणु USB_DEVICE(0x1a0a, TEST_K_PID) पूर्ण,
	अणु USB_DEVICE(0x1a0a, TEST_PACKET_PID) पूर्ण,
	अणु USB_DEVICE(0x1a0a, TEST_HS_HOST_PORT_SUSPEND_RESUME) पूर्ण,
	अणु USB_DEVICE(0x1a0a, TEST_SINGLE_STEP_GET_DEV_DESC) पूर्ण,
	अणु USB_DEVICE(0x1a0a, TEST_SINGLE_STEP_SET_FEATURE) पूर्ण,
	अणु पूर्ण			/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(usb, ehset_id_table);

अटल काष्ठा usb_driver ehset_driver = अणु
	.name =		"usb_ehset_test",
	.probe =	ehset_probe,
	.disconnect =	ehset_disconnect,
	.id_table =	ehset_id_table,
पूर्ण;

module_usb_driver(ehset_driver);

MODULE_DESCRIPTION("USB Driver for EHSET Test Fixture");
MODULE_LICENSE("GPL v2");
