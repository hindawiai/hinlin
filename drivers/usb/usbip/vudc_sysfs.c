<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2015 Karol Kosik <karo9@पूर्णांकeria.eu>
 * Copyright (C) 2015-2016 Samsung Electronics
 *               Igor Kotrasinski <i.kotrasinsk@samsung.com>
 *               Krzysztof Opasiak <k.opasiak@samsung.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/usb/gadget.h>
#समावेश <linux/usb/ch9.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/byteorder/generic.h>

#समावेश "usbip_common.h"
#समावेश "vudc.h"

#समावेश <net/sock.h>

/* called with udc->lock held */
पूर्णांक get_gadget_descs(काष्ठा vudc *udc)
अणु
	काष्ठा vrequest *usb_req;
	काष्ठा vep *ep0 = to_vep(udc->gadget.ep0);
	काष्ठा usb_device_descriptor *ddesc = &udc->dev_desc;
	काष्ठा usb_ctrlrequest req;
	पूर्णांक ret;

	अगर (!udc->driver || !udc->pullup)
		वापस -EINVAL;

	req.bRequestType = USB_सूची_IN | USB_TYPE_STANDARD | USB_RECIP_DEVICE;
	req.bRequest = USB_REQ_GET_DESCRIPTOR;
	req.wValue = cpu_to_le16(USB_DT_DEVICE << 8);
	req.wIndex = cpu_to_le16(0);
	req.wLength = cpu_to_le16(माप(*ddesc));

	spin_unlock(&udc->lock);
	ret = udc->driver->setup(&(udc->gadget), &req);
	spin_lock(&udc->lock);
	अगर (ret < 0)
		जाओ out;

	/* assuming request queue is empty; request is now on top */
	usb_req = list_last_entry(&ep0->req_queue, काष्ठा vrequest, req_entry);
	list_del(&usb_req->req_entry);

	अगर (usb_req->req.length > माप(*ddesc)) अणु
		ret = -EOVERFLOW;
		जाओ giveback_req;
	पूर्ण

	स_नकल(ddesc, usb_req->req.buf, माप(*ddesc));
	udc->desc_cached = 1;
	ret = 0;
giveback_req:
	usb_req->req.status = 0;
	usb_req->req.actual = usb_req->req.length;
	usb_gadget_giveback_request(&(ep0->ep), &(usb_req->req));
out:
	वापस ret;
पूर्ण

/*
 * Exposes device descriptor from the gadget driver.
 */
अटल sमाप_प्रकार dev_desc_पढ़ो(काष्ठा file *file, काष्ठा kobject *kobj,
			     काष्ठा bin_attribute *attr, अक्षर *out,
			     loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा vudc *udc = (काष्ठा vudc *)dev_get_drvdata(dev);
	अक्षर *desc_ptr = (अक्षर *) &udc->dev_desc;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&udc->lock, flags);
	अगर (!udc->desc_cached) अणु
		ret = -ENODEV;
		जाओ unlock;
	पूर्ण

	स_नकल(out, desc_ptr + off, count);
	ret = count;
unlock:
	spin_unlock_irqrestore(&udc->lock, flags);
	वापस ret;
पूर्ण
अटल BIN_ATTR_RO(dev_desc, माप(काष्ठा usb_device_descriptor));

अटल sमाप_प्रकार usbip_sockfd_store(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *in, माप_प्रकार count)
अणु
	काष्ठा vudc *udc = (काष्ठा vudc *) dev_get_drvdata(dev);
	पूर्णांक rv;
	पूर्णांक sockfd = 0;
	पूर्णांक err;
	काष्ठा socket *socket;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	काष्ठा task_काष्ठा *tcp_rx = शून्य;
	काष्ठा task_काष्ठा *tcp_tx = शून्य;

	rv = kstrtoपूर्णांक(in, 0, &sockfd);
	अगर (rv != 0)
		वापस -EINVAL;

	अगर (!udc) अणु
		dev_err(dev, "no device");
		वापस -ENODEV;
	पूर्ण
	mutex_lock(&udc->ud.sysfs_lock);
	spin_lock_irqsave(&udc->lock, flags);
	/* Don't export what we don't have */
	अगर (!udc->driver || !udc->pullup) अणु
		dev_err(dev, "gadget not bound");
		ret = -ENODEV;
		जाओ unlock;
	पूर्ण

	अगर (sockfd != -1) अणु
		अगर (udc->connected) अणु
			dev_err(dev, "Device already connected");
			ret = -EBUSY;
			जाओ unlock;
		पूर्ण

		spin_lock_irq(&udc->ud.lock);

		अगर (udc->ud.status != SDEV_ST_AVAILABLE) अणु
			ret = -EINVAL;
			जाओ unlock_ud;
		पूर्ण

		socket = sockfd_lookup(sockfd, &err);
		अगर (!socket) अणु
			dev_err(dev, "failed to lookup sock");
			ret = -EINVAL;
			जाओ unlock_ud;
		पूर्ण

		अगर (socket->type != SOCK_STREAM) अणु
			dev_err(dev, "Expecting SOCK_STREAM - found %d",
				socket->type);
			ret = -EINVAL;
			जाओ sock_err;
		पूर्ण

		/* unlock and create thपढ़ोs and get tasks */
		spin_unlock_irq(&udc->ud.lock);
		spin_unlock_irqrestore(&udc->lock, flags);

		tcp_rx = kthपढ़ो_create(&v_rx_loop, &udc->ud, "vudc_rx");
		अगर (IS_ERR(tcp_rx)) अणु
			sockfd_put(socket);
			mutex_unlock(&udc->ud.sysfs_lock);
			वापस -EINVAL;
		पूर्ण
		tcp_tx = kthपढ़ो_create(&v_tx_loop, &udc->ud, "vudc_tx");
		अगर (IS_ERR(tcp_tx)) अणु
			kthपढ़ो_stop(tcp_rx);
			sockfd_put(socket);
			mutex_unlock(&udc->ud.sysfs_lock);
			वापस -EINVAL;
		पूर्ण

		/* get task काष्ठाs now */
		get_task_काष्ठा(tcp_rx);
		get_task_काष्ठा(tcp_tx);

		/* lock and update udc->ud state */
		spin_lock_irqsave(&udc->lock, flags);
		spin_lock_irq(&udc->ud.lock);

		udc->ud.tcp_socket = socket;
		udc->ud.tcp_rx = tcp_rx;
		udc->ud.tcp_tx = tcp_tx;
		udc->ud.status = SDEV_ST_USED;

		spin_unlock_irq(&udc->ud.lock);

		kसमय_get_ts64(&udc->start_समय);
		v_start_समयr(udc);
		udc->connected = 1;

		spin_unlock_irqrestore(&udc->lock, flags);

		wake_up_process(udc->ud.tcp_rx);
		wake_up_process(udc->ud.tcp_tx);

		mutex_unlock(&udc->ud.sysfs_lock);
		वापस count;

	पूर्ण अन्यथा अणु
		अगर (!udc->connected) अणु
			dev_err(dev, "Device not connected");
			ret = -EINVAL;
			जाओ unlock;
		पूर्ण

		spin_lock_irq(&udc->ud.lock);
		अगर (udc->ud.status != SDEV_ST_USED) अणु
			ret = -EINVAL;
			जाओ unlock_ud;
		पूर्ण
		spin_unlock_irq(&udc->ud.lock);

		usbip_event_add(&udc->ud, VUDC_EVENT_DOWN);
	पूर्ण

	spin_unlock_irqrestore(&udc->lock, flags);
	mutex_unlock(&udc->ud.sysfs_lock);

	वापस count;

sock_err:
	sockfd_put(socket);
unlock_ud:
	spin_unlock_irq(&udc->ud.lock);
unlock:
	spin_unlock_irqrestore(&udc->lock, flags);
	mutex_unlock(&udc->ud.sysfs_lock);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_WO(usbip_sockfd);

अटल sमाप_प्रकार usbip_status_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *out)
अणु
	काष्ठा vudc *udc = (काष्ठा vudc *) dev_get_drvdata(dev);
	पूर्णांक status;

	अगर (!udc) अणु
		dev_err(dev, "no device");
		वापस -ENODEV;
	पूर्ण
	spin_lock_irq(&udc->ud.lock);
	status = udc->ud.status;
	spin_unlock_irq(&udc->ud.lock);

	वापस snम_लिखो(out, PAGE_SIZE, "%d\n", status);
पूर्ण
अटल DEVICE_ATTR_RO(usbip_status);

अटल काष्ठा attribute *dev_attrs[] = अणु
	&dev_attr_usbip_sockfd.attr,
	&dev_attr_usbip_status.attr,
	शून्य,
पूर्ण;

अटल काष्ठा bin_attribute *dev_bin_attrs[] = अणु
	&bin_attr_dev_desc,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group vudc_attr_group = अणु
	.attrs = dev_attrs,
	.bin_attrs = dev_bin_attrs,
पूर्ण;

स्थिर काष्ठा attribute_group *vudc_groups[] = अणु
	&vudc_attr_group,
	शून्य,
पूर्ण;
