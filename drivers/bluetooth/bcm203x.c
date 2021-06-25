<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Broadcom Blutonium firmware driver
 *
 *  Copyright (C) 2003  Maxim Krasnyansky <maxk@qualcomm.com>
 *  Copyright (C) 2003  Marcel Holपंचांगann <marcel@holपंचांगann.org>
 */

#समावेश <linux/module.h>

#समावेश <linux/atomic.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश <linux/device.h>
#समावेश <linux/firmware.h>

#समावेश <linux/usb.h>

#समावेश <net/bluetooth/bluetooth.h>

#घोषणा VERSION "1.2"

अटल स्थिर काष्ठा usb_device_id bcm203x_table[] = अणु
	/* Broadcom Blutonium (BCM2033) */
	अणु USB_DEVICE(0x0a5c, 0x2033) पूर्ण,

	अणु पूर्ण	/* Terminating entry */
पूर्ण;

MODULE_DEVICE_TABLE(usb, bcm203x_table);

#घोषणा BCM203X_ERROR		0
#घोषणा BCM203X_RESET		1
#घोषणा BCM203X_LOAD_MINIDRV	2
#घोषणा BCM203X_SELECT_MEMORY	3
#घोषणा BCM203X_CHECK_MEMORY	4
#घोषणा BCM203X_LOAD_FIRMWARE	5
#घोषणा BCM203X_CHECK_FIRMWARE	6

#घोषणा BCM203X_IN_EP		0x81
#घोषणा BCM203X_OUT_EP		0x02

काष्ठा bcm203x_data अणु
	काष्ठा usb_device	*udev;

	अचिन्हित दीर्घ		state;

	काष्ठा work_काष्ठा	work;
	atomic_t		shutकरोwn;

	काष्ठा urb		*urb;
	अचिन्हित अक्षर		*buffer;

	अचिन्हित अक्षर		*fw_data;
	अचिन्हित पूर्णांक		fw_size;
	अचिन्हित पूर्णांक		fw_sent;
पूर्ण;

अटल व्योम bcm203x_complete(काष्ठा urb *urb)
अणु
	काष्ठा bcm203x_data *data = urb->context;
	काष्ठा usb_device *udev = urb->dev;
	पूर्णांक len;

	BT_DBG("udev %p urb %p", udev, urb);

	अगर (urb->status) अणु
		BT_ERR("URB failed with status %d", urb->status);
		data->state = BCM203X_ERROR;
		वापस;
	पूर्ण

	चयन (data->state) अणु
	हाल BCM203X_LOAD_MINIDRV:
		स_नकल(data->buffer, "#", 1);

		usb_fill_bulk_urb(urb, udev, usb_sndbulkpipe(udev, BCM203X_OUT_EP),
				data->buffer, 1, bcm203x_complete, data);

		data->state = BCM203X_SELECT_MEMORY;

		/* use workqueue to have a small delay */
		schedule_work(&data->work);
		अवरोध;

	हाल BCM203X_SELECT_MEMORY:
		usb_fill_पूर्णांक_urb(urb, udev, usb_rcvपूर्णांकpipe(udev, BCM203X_IN_EP),
				data->buffer, 32, bcm203x_complete, data, 1);

		data->state = BCM203X_CHECK_MEMORY;

		अगर (usb_submit_urb(data->urb, GFP_ATOMIC) < 0)
			BT_ERR("Can't submit URB");
		अवरोध;

	हाल BCM203X_CHECK_MEMORY:
		अगर (data->buffer[0] != '#') अणु
			BT_ERR("Memory select failed");
			data->state = BCM203X_ERROR;
			अवरोध;
		पूर्ण

		data->state = BCM203X_LOAD_FIRMWARE;
		fallthrough;
	हाल BCM203X_LOAD_FIRMWARE:
		अगर (data->fw_sent == data->fw_size) अणु
			usb_fill_पूर्णांक_urb(urb, udev, usb_rcvपूर्णांकpipe(udev, BCM203X_IN_EP),
				data->buffer, 32, bcm203x_complete, data, 1);

			data->state = BCM203X_CHECK_FIRMWARE;
		पूर्ण अन्यथा अणु
			len = min_t(uपूर्णांक, data->fw_size - data->fw_sent, 4096);

			usb_fill_bulk_urb(urb, udev, usb_sndbulkpipe(udev, BCM203X_OUT_EP),
				data->fw_data + data->fw_sent, len, bcm203x_complete, data);

			data->fw_sent += len;
		पूर्ण

		अगर (usb_submit_urb(data->urb, GFP_ATOMIC) < 0)
			BT_ERR("Can't submit URB");
		अवरोध;

	हाल BCM203X_CHECK_FIRMWARE:
		अगर (data->buffer[0] != '.') अणु
			BT_ERR("Firmware loading failed");
			data->state = BCM203X_ERROR;
			अवरोध;
		पूर्ण

		data->state = BCM203X_RESET;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bcm203x_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bcm203x_data *data =
		container_of(work, काष्ठा bcm203x_data, work);

	अगर (atomic_पढ़ो(&data->shutकरोwn))
		वापस;

	अगर (usb_submit_urb(data->urb, GFP_KERNEL) < 0)
		BT_ERR("Can't submit URB");
पूर्ण

अटल पूर्णांक bcm203x_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf, स्थिर काष्ठा usb_device_id *id)
अणु
	स्थिर काष्ठा firmware *firmware;
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा bcm203x_data *data;
	पूर्णांक size;

	BT_DBG("intf %p id %p", पूर्णांकf, id);

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceNumber != 0)
		वापस -ENODEV;

	data = devm_kzalloc(&पूर्णांकf->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->udev  = udev;
	data->state = BCM203X_LOAD_MINIDRV;

	data->urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!data->urb)
		वापस -ENOMEM;

	अगर (request_firmware(&firmware, "BCM2033-MD.hex", &udev->dev) < 0) अणु
		BT_ERR("Mini driver request failed");
		usb_मुक्त_urb(data->urb);
		वापस -EIO;
	पूर्ण

	BT_DBG("minidrv data %p size %zu", firmware->data, firmware->size);

	size = max_t(uपूर्णांक, firmware->size, 4096);

	data->buffer = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!data->buffer) अणु
		BT_ERR("Can't allocate memory for mini driver");
		release_firmware(firmware);
		usb_मुक्त_urb(data->urb);
		वापस -ENOMEM;
	पूर्ण

	स_नकल(data->buffer, firmware->data, firmware->size);

	usb_fill_bulk_urb(data->urb, udev, usb_sndbulkpipe(udev, BCM203X_OUT_EP),
			data->buffer, firmware->size, bcm203x_complete, data);

	release_firmware(firmware);

	अगर (request_firmware(&firmware, "BCM2033-FW.bin", &udev->dev) < 0) अणु
		BT_ERR("Firmware request failed");
		usb_मुक्त_urb(data->urb);
		kमुक्त(data->buffer);
		वापस -EIO;
	पूर्ण

	BT_DBG("firmware data %p size %zu", firmware->data, firmware->size);

	data->fw_data = kmemdup(firmware->data, firmware->size, GFP_KERNEL);
	अगर (!data->fw_data) अणु
		BT_ERR("Can't allocate memory for firmware image");
		release_firmware(firmware);
		usb_मुक्त_urb(data->urb);
		kमुक्त(data->buffer);
		वापस -ENOMEM;
	पूर्ण

	data->fw_size = firmware->size;
	data->fw_sent = 0;

	release_firmware(firmware);

	INIT_WORK(&data->work, bcm203x_work);

	usb_set_पूर्णांकfdata(पूर्णांकf, data);

	/* use workqueue to have a small delay */
	schedule_work(&data->work);

	वापस 0;
पूर्ण

अटल व्योम bcm203x_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा bcm203x_data *data = usb_get_पूर्णांकfdata(पूर्णांकf);

	BT_DBG("intf %p", पूर्णांकf);

	atomic_inc(&data->shutकरोwn);
	cancel_work_sync(&data->work);

	usb_समाप्त_urb(data->urb);

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);

	usb_मुक्त_urb(data->urb);
	kमुक्त(data->fw_data);
	kमुक्त(data->buffer);
पूर्ण

अटल काष्ठा usb_driver bcm203x_driver = अणु
	.name		= "bcm203x",
	.probe		= bcm203x_probe,
	.disconnect	= bcm203x_disconnect,
	.id_table	= bcm203x_table,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(bcm203x_driver);

MODULE_AUTHOR("Marcel Holtmann <marcel@holtmann.org>");
MODULE_DESCRIPTION("Broadcom Blutonium firmware driver ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("BCM2033-MD.hex");
MODULE_FIRMWARE("BCM2033-FW.bin");
