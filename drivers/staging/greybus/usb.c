<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB host driver क्रम the Greybus "generic" USB module.
 *
 * Copyright 2014 Google Inc.
 * Copyright 2014 Linaro Ltd.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/greybus.h>

#समावेश "gbphy.h"

/* Greybus USB request types */
#घोषणा GB_USB_TYPE_HCD_START		0x02
#घोषणा GB_USB_TYPE_HCD_STOP		0x03
#घोषणा GB_USB_TYPE_HUB_CONTROL		0x04

काष्ठा gb_usb_hub_control_request अणु
	__le16 typeReq;
	__le16 wValue;
	__le16 wIndex;
	__le16 wLength;
पूर्ण;

काष्ठा gb_usb_hub_control_response अणु
	u8 buf[0];
पूर्ण;

काष्ठा gb_usb_device अणु
	काष्ठा gb_connection *connection;
	काष्ठा gbphy_device *gbphy_dev;
पूर्ण;

अटल अंतरभूत काष्ठा gb_usb_device *to_gb_usb_device(काष्ठा usb_hcd *hcd)
अणु
	वापस (काष्ठा gb_usb_device *)hcd->hcd_priv;
पूर्ण

अटल अंतरभूत काष्ठा usb_hcd *gb_usb_device_to_hcd(काष्ठा gb_usb_device *dev)
अणु
	वापस container_of((व्योम *)dev, काष्ठा usb_hcd, hcd_priv);
पूर्ण

अटल व्योम hcd_stop(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा gb_usb_device *dev = to_gb_usb_device(hcd);
	पूर्णांक ret;

	ret = gb_operation_sync(dev->connection, GB_USB_TYPE_HCD_STOP,
				शून्य, 0, शून्य, 0);
	अगर (ret)
		dev_err(&dev->gbphy_dev->dev, "HCD stop failed '%d'\n", ret);
पूर्ण

अटल पूर्णांक hcd_start(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा usb_bus *bus = hcd_to_bus(hcd);
	काष्ठा gb_usb_device *dev = to_gb_usb_device(hcd);
	पूर्णांक ret;

	ret = gb_operation_sync(dev->connection, GB_USB_TYPE_HCD_START,
				शून्य, 0, शून्य, 0);
	अगर (ret) अणु
		dev_err(&dev->gbphy_dev->dev, "HCD start failed '%d'\n", ret);
		वापस ret;
	पूर्ण

	hcd->state = HC_STATE_RUNNING;
	अगर (bus->root_hub)
		usb_hcd_resume_root_hub(hcd);
	वापस 0;
पूर्ण

अटल पूर्णांक urb_enqueue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, gfp_t mem_flags)
अणु
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक urb_dequeue(काष्ठा usb_hcd *hcd, काष्ठा urb *urb, पूर्णांक status)
अणु
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक get_frame_number(काष्ठा usb_hcd *hcd)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक hub_status_data(काष्ठा usb_hcd *hcd, अक्षर *buf)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक hub_control(काष्ठा usb_hcd *hcd, u16 typeReq, u16 wValue, u16 wIndex,
		       अक्षर *buf, u16 wLength)
अणु
	काष्ठा gb_usb_device *dev = to_gb_usb_device(hcd);
	काष्ठा gb_operation *operation;
	काष्ठा gb_usb_hub_control_request *request;
	काष्ठा gb_usb_hub_control_response *response;
	माप_प्रकार response_size;
	पूर्णांक ret;

	/* FIXME: handle unspecअगरied lengths */
	response_size = माप(*response) + wLength;

	operation = gb_operation_create(dev->connection,
					GB_USB_TYPE_HUB_CONTROL,
					माप(*request),
					response_size,
					GFP_KERNEL);
	अगर (!operation)
		वापस -ENOMEM;

	request = operation->request->payload;
	request->typeReq = cpu_to_le16(typeReq);
	request->wValue = cpu_to_le16(wValue);
	request->wIndex = cpu_to_le16(wIndex);
	request->wLength = cpu_to_le16(wLength);

	ret = gb_operation_request_send_sync(operation);
	अगर (ret)
		जाओ out;

	अगर (wLength) अणु
		/* Greybus core has verअगरied response size */
		response = operation->response->payload;
		स_नकल(buf, response->buf, wLength);
	पूर्ण
out:
	gb_operation_put(operation);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा hc_driver usb_gb_hc_driver = अणु
	.description = "greybus-hcd",
	.product_desc = "Greybus USB Host Controller",
	.hcd_priv_size = माप(काष्ठा gb_usb_device),

	.flags = HCD_USB2,

	.start = hcd_start,
	.stop = hcd_stop,

	.urb_enqueue = urb_enqueue,
	.urb_dequeue = urb_dequeue,

	.get_frame_number = get_frame_number,
	.hub_status_data = hub_status_data,
	.hub_control = hub_control,
पूर्ण;

अटल पूर्णांक gb_usb_probe(काष्ठा gbphy_device *gbphy_dev,
			स्थिर काष्ठा gbphy_device_id *id)
अणु
	काष्ठा gb_connection *connection;
	काष्ठा device *dev = &gbphy_dev->dev;
	काष्ठा gb_usb_device *gb_usb_dev;
	काष्ठा usb_hcd *hcd;
	पूर्णांक retval;

	hcd = usb_create_hcd(&usb_gb_hc_driver, dev, dev_name(dev));
	अगर (!hcd)
		वापस -ENOMEM;

	connection = gb_connection_create(gbphy_dev->bundle,
					  le16_to_cpu(gbphy_dev->cport_desc->id),
					  शून्य);
	अगर (IS_ERR(connection)) अणु
		retval = PTR_ERR(connection);
		जाओ निकास_usb_put;
	पूर्ण

	gb_usb_dev = to_gb_usb_device(hcd);
	gb_usb_dev->connection = connection;
	gb_connection_set_data(connection, gb_usb_dev);
	gb_usb_dev->gbphy_dev = gbphy_dev;
	gb_gbphy_set_data(gbphy_dev, gb_usb_dev);

	hcd->has_tt = 1;

	retval = gb_connection_enable(connection);
	अगर (retval)
		जाओ निकास_connection_destroy;

	/*
	 * FIXME: The USB bridged-PHY protocol driver depends on changes to
	 *        USB core which are not yet upstream.
	 *
	 *        Disable क्रम now.
	 */
	अगर (1) अणु
		dev_warn(dev, "USB protocol disabled\n");
		retval = -EPROTONOSUPPORT;
		जाओ निकास_connection_disable;
	पूर्ण

	retval = usb_add_hcd(hcd, 0, 0);
	अगर (retval)
		जाओ निकास_connection_disable;

	वापस 0;

निकास_connection_disable:
	gb_connection_disable(connection);
निकास_connection_destroy:
	gb_connection_destroy(connection);
निकास_usb_put:
	usb_put_hcd(hcd);

	वापस retval;
पूर्ण

अटल व्योम gb_usb_हटाओ(काष्ठा gbphy_device *gbphy_dev)
अणु
	काष्ठा gb_usb_device *gb_usb_dev = gb_gbphy_get_data(gbphy_dev);
	काष्ठा gb_connection *connection = gb_usb_dev->connection;
	काष्ठा usb_hcd *hcd = gb_usb_device_to_hcd(gb_usb_dev);

	usb_हटाओ_hcd(hcd);
	gb_connection_disable(connection);
	gb_connection_destroy(connection);
	usb_put_hcd(hcd);
पूर्ण

अटल स्थिर काष्ठा gbphy_device_id gb_usb_id_table[] = अणु
	अणु GBPHY_PROTOCOL(GREYBUS_PROTOCOL_USB) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(gbphy, gb_usb_id_table);

अटल काष्ठा gbphy_driver usb_driver = अणु
	.name		= "usb",
	.probe		= gb_usb_probe,
	.हटाओ		= gb_usb_हटाओ,
	.id_table	= gb_usb_id_table,
पूर्ण;

module_gbphy_driver(usb_driver);
MODULE_LICENSE("GPL v2");
