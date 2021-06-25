<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2003-2008 Takahiro Hirofuchi
 */

#समावेश <linux/device.h>
#समावेश <linux/file.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>

#समावेश "usbip_common.h"
#समावेश "stub.h"

/*
 * usbip_status shows the status of usbip-host as दीर्घ as this driver is bound
 * to the target device.
 */
अटल sमाप_प्रकार usbip_status_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा stub_device *sdev = dev_get_drvdata(dev);
	पूर्णांक status;

	अगर (!sdev) अणु
		dev_err(dev, "sdev is null\n");
		वापस -ENODEV;
	पूर्ण

	spin_lock_irq(&sdev->ud.lock);
	status = sdev->ud.status;
	spin_unlock_irq(&sdev->ud.lock);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", status);
पूर्ण
अटल DEVICE_ATTR_RO(usbip_status);

/*
 * usbip_sockfd माला_लो a socket descriptor of an established TCP connection that
 * is used to transfer usbip requests by kernel thपढ़ोs. -1 is a magic number
 * by which usbip connection is finished.
 */
अटल sमाप_प्रकार usbip_sockfd_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा stub_device *sdev = dev_get_drvdata(dev);
	पूर्णांक sockfd = 0;
	काष्ठा socket *socket;
	पूर्णांक rv;
	काष्ठा task_काष्ठा *tcp_rx = शून्य;
	काष्ठा task_काष्ठा *tcp_tx = शून्य;

	अगर (!sdev) अणु
		dev_err(dev, "sdev is null\n");
		वापस -ENODEV;
	पूर्ण

	rv = माला_पूछो(buf, "%d", &sockfd);
	अगर (rv != 1)
		वापस -EINVAL;

	अगर (sockfd != -1) अणु
		पूर्णांक err;

		dev_info(dev, "stub up\n");

		mutex_lock(&sdev->ud.sysfs_lock);
		spin_lock_irq(&sdev->ud.lock);

		अगर (sdev->ud.status != SDEV_ST_AVAILABLE) अणु
			dev_err(dev, "not ready\n");
			जाओ err;
		पूर्ण

		socket = sockfd_lookup(sockfd, &err);
		अगर (!socket) अणु
			dev_err(dev, "failed to lookup sock");
			जाओ err;
		पूर्ण

		अगर (socket->type != SOCK_STREAM) अणु
			dev_err(dev, "Expecting SOCK_STREAM - found %d",
				socket->type);
			जाओ sock_err;
		पूर्ण

		/* unlock and create thपढ़ोs and get tasks */
		spin_unlock_irq(&sdev->ud.lock);
		tcp_rx = kthपढ़ो_create(stub_rx_loop, &sdev->ud, "stub_rx");
		अगर (IS_ERR(tcp_rx)) अणु
			sockfd_put(socket);
			जाओ unlock_mutex;
		पूर्ण
		tcp_tx = kthपढ़ो_create(stub_tx_loop, &sdev->ud, "stub_tx");
		अगर (IS_ERR(tcp_tx)) अणु
			kthपढ़ो_stop(tcp_rx);
			sockfd_put(socket);
			जाओ unlock_mutex;
		पूर्ण

		/* get task काष्ठाs now */
		get_task_काष्ठा(tcp_rx);
		get_task_काष्ठा(tcp_tx);

		/* lock and update sdev->ud state */
		spin_lock_irq(&sdev->ud.lock);
		sdev->ud.tcp_socket = socket;
		sdev->ud.sockfd = sockfd;
		sdev->ud.tcp_rx = tcp_rx;
		sdev->ud.tcp_tx = tcp_tx;
		sdev->ud.status = SDEV_ST_USED;
		spin_unlock_irq(&sdev->ud.lock);

		wake_up_process(sdev->ud.tcp_rx);
		wake_up_process(sdev->ud.tcp_tx);

		mutex_unlock(&sdev->ud.sysfs_lock);

	पूर्ण अन्यथा अणु
		dev_info(dev, "stub down\n");

		spin_lock_irq(&sdev->ud.lock);
		अगर (sdev->ud.status != SDEV_ST_USED)
			जाओ err;

		spin_unlock_irq(&sdev->ud.lock);

		usbip_event_add(&sdev->ud, SDEV_EVENT_DOWN);
		mutex_unlock(&sdev->ud.sysfs_lock);
	पूर्ण

	वापस count;

sock_err:
	sockfd_put(socket);
err:
	spin_unlock_irq(&sdev->ud.lock);
unlock_mutex:
	mutex_unlock(&sdev->ud.sysfs_lock);
	वापस -EINVAL;
पूर्ण
अटल DEVICE_ATTR_WO(usbip_sockfd);

अटल काष्ठा attribute *usbip_attrs[] = अणु
	&dev_attr_usbip_status.attr,
	&dev_attr_usbip_sockfd.attr,
	&dev_attr_usbip_debug.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(usbip);

अटल व्योम stub_shutकरोwn_connection(काष्ठा usbip_device *ud)
अणु
	काष्ठा stub_device *sdev = container_of(ud, काष्ठा stub_device, ud);

	/*
	 * When removing an exported device, kernel panic someबार occurred
	 * and then EIP was sk_रुको_data of stub_rx thपढ़ो. Is this because
	 * sk_रुको_data वापसed though stub_rx thपढ़ो was alपढ़ोy finished by
	 * step 1?
	 */
	अगर (ud->tcp_socket) अणु
		dev_dbg(&sdev->udev->dev, "shutdown sockfd %d\n", ud->sockfd);
		kernel_sock_shutकरोwn(ud->tcp_socket, SHUT_RDWR);
	पूर्ण

	/* 1. stop thपढ़ोs */
	अगर (ud->tcp_rx) अणु
		kthपढ़ो_stop_put(ud->tcp_rx);
		ud->tcp_rx = शून्य;
	पूर्ण
	अगर (ud->tcp_tx) अणु
		kthपढ़ो_stop_put(ud->tcp_tx);
		ud->tcp_tx = शून्य;
	पूर्ण

	/*
	 * 2. बंद the socket
	 *
	 * tcp_socket is मुक्तd after thपढ़ोs are समाप्तed so that usbip_xmit करोes
	 * not touch शून्य socket.
	 */
	अगर (ud->tcp_socket) अणु
		sockfd_put(ud->tcp_socket);
		ud->tcp_socket = शून्य;
		ud->sockfd = -1;
	पूर्ण

	/* 3. मुक्त used data */
	stub_device_cleanup_urbs(sdev);

	/* 4. मुक्त stub_unlink */
	अणु
		अचिन्हित दीर्घ flags;
		काष्ठा stub_unlink *unlink, *पंचांगp;

		spin_lock_irqsave(&sdev->priv_lock, flags);
		list_क्रम_each_entry_safe(unlink, पंचांगp, &sdev->unlink_tx, list) अणु
			list_del(&unlink->list);
			kमुक्त(unlink);
		पूर्ण
		list_क्रम_each_entry_safe(unlink, पंचांगp, &sdev->unlink_मुक्त,
					 list) अणु
			list_del(&unlink->list);
			kमुक्त(unlink);
		पूर्ण
		spin_unlock_irqrestore(&sdev->priv_lock, flags);
	पूर्ण
पूर्ण

अटल व्योम stub_device_reset(काष्ठा usbip_device *ud)
अणु
	काष्ठा stub_device *sdev = container_of(ud, काष्ठा stub_device, ud);
	काष्ठा usb_device *udev = sdev->udev;
	पूर्णांक ret;

	dev_dbg(&udev->dev, "device reset");

	ret = usb_lock_device_क्रम_reset(udev, शून्य);
	अगर (ret < 0) अणु
		dev_err(&udev->dev, "lock for reset\n");
		spin_lock_irq(&ud->lock);
		ud->status = SDEV_ST_ERROR;
		spin_unlock_irq(&ud->lock);
		वापस;
	पूर्ण

	/* try to reset the device */
	ret = usb_reset_device(udev);
	usb_unlock_device(udev);

	spin_lock_irq(&ud->lock);
	अगर (ret) अणु
		dev_err(&udev->dev, "device reset\n");
		ud->status = SDEV_ST_ERROR;
	पूर्ण अन्यथा अणु
		dev_info(&udev->dev, "device reset\n");
		ud->status = SDEV_ST_AVAILABLE;
	पूर्ण
	spin_unlock_irq(&ud->lock);
पूर्ण

अटल व्योम stub_device_unusable(काष्ठा usbip_device *ud)
अणु
	spin_lock_irq(&ud->lock);
	ud->status = SDEV_ST_ERROR;
	spin_unlock_irq(&ud->lock);
पूर्ण

/**
 * stub_device_alloc - allocate a new stub_device काष्ठा
 * @udev: usb_device of a new device
 *
 * Allocates and initializes a new stub_device काष्ठा.
 */
अटल काष्ठा stub_device *stub_device_alloc(काष्ठा usb_device *udev)
अणु
	काष्ठा stub_device *sdev;
	पूर्णांक busnum = udev->bus->busnum;
	पूर्णांक devnum = udev->devnum;

	dev_dbg(&udev->dev, "allocating stub device");

	/* yes, it's a new device */
	sdev = kzalloc(माप(काष्ठा stub_device), GFP_KERNEL);
	अगर (!sdev)
		वापस शून्य;

	sdev->udev = usb_get_dev(udev);

	/*
	 * devid is defined with devnum when this driver is first allocated.
	 * devnum may change later अगर a device is reset. However, devid never
	 * changes during a usbip connection.
	 */
	sdev->devid		= (busnum << 16) | devnum;
	sdev->ud.side		= USBIP_STUB;
	sdev->ud.status		= SDEV_ST_AVAILABLE;
	spin_lock_init(&sdev->ud.lock);
	mutex_init(&sdev->ud.sysfs_lock);
	sdev->ud.tcp_socket	= शून्य;
	sdev->ud.sockfd		= -1;

	INIT_LIST_HEAD(&sdev->priv_init);
	INIT_LIST_HEAD(&sdev->priv_tx);
	INIT_LIST_HEAD(&sdev->priv_मुक्त);
	INIT_LIST_HEAD(&sdev->unlink_मुक्त);
	INIT_LIST_HEAD(&sdev->unlink_tx);
	spin_lock_init(&sdev->priv_lock);

	init_रुकोqueue_head(&sdev->tx_रुकोq);

	sdev->ud.eh_ops.shutकरोwn = stub_shutकरोwn_connection;
	sdev->ud.eh_ops.reset    = stub_device_reset;
	sdev->ud.eh_ops.unusable = stub_device_unusable;

	usbip_start_eh(&sdev->ud);

	dev_dbg(&udev->dev, "register new device\n");

	वापस sdev;
पूर्ण

अटल व्योम stub_device_मुक्त(काष्ठा stub_device *sdev)
अणु
	kमुक्त(sdev);
पूर्ण

अटल पूर्णांक stub_probe(काष्ठा usb_device *udev)
अणु
	काष्ठा stub_device *sdev = शून्य;
	स्थिर अक्षर *udev_busid = dev_name(&udev->dev);
	काष्ठा bus_id_priv *busid_priv;
	पूर्णांक rc = 0;
	अक्षर save_status;

	dev_dbg(&udev->dev, "Enter probe\n");

	/* Not sure अगर this is our device. Allocate here to aव्योम
	 * calling alloc जबतक holding busid_table lock.
	 */
	sdev = stub_device_alloc(udev);
	अगर (!sdev)
		वापस -ENOMEM;

	/* check we should claim or not by busid_table */
	busid_priv = get_busid_priv(udev_busid);
	अगर (!busid_priv || (busid_priv->status == STUB_BUSID_REMOV) ||
	    (busid_priv->status == STUB_BUSID_OTHER)) अणु
		dev_info(&udev->dev,
			"%s is not in match_busid table... skip!\n",
			udev_busid);

		/*
		 * Return value should be ENODEV or ENOXIO to जारी trying
		 * other matched drivers by the driver core.
		 * See driver_probe_device() in driver/base/dd.c
		 */
		rc = -ENODEV;
		अगर (!busid_priv)
			जाओ sdev_मुक्त;

		जाओ call_put_busid_priv;
	पूर्ण

	अगर (udev->descriptor.bDeviceClass == USB_CLASS_HUB) अणु
		dev_dbg(&udev->dev, "%s is a usb hub device... skip!\n",
			 udev_busid);
		rc = -ENODEV;
		जाओ call_put_busid_priv;
	पूर्ण

	अगर (!म_भेद(udev->bus->bus_name, "vhci_hcd")) अणु
		dev_dbg(&udev->dev,
			"%s is attached on vhci_hcd... skip!\n",
			udev_busid);

		rc = -ENODEV;
		जाओ call_put_busid_priv;
	पूर्ण


	dev_info(&udev->dev,
		"usbip-host: register new device (bus %u dev %u)\n",
		udev->bus->busnum, udev->devnum);

	busid_priv->shutकरोwn_busid = 0;

	/* set निजी data to usb_device */
	dev_set_drvdata(&udev->dev, sdev);

	busid_priv->sdev = sdev;
	busid_priv->udev = udev;

	save_status = busid_priv->status;
	busid_priv->status = STUB_BUSID_ALLOC;

	/* release the busid_lock */
	put_busid_priv(busid_priv);

	/*
	 * Claim this hub port.
	 * It करोesn't matter what value we pass as owner
	 * (काष्ठा dev_state) as दीर्घ as it is unique.
	 */
	rc = usb_hub_claim_port(udev->parent, udev->portnum,
			(काष्ठा usb_dev_state *) udev);
	अगर (rc) अणु
		dev_dbg(&udev->dev, "unable to claim port\n");
		जाओ err_port;
	पूर्ण

	वापस 0;

err_port:
	dev_set_drvdata(&udev->dev, शून्य);
	usb_put_dev(udev);

	/* we alपढ़ोy have busid_priv, just lock busid_lock */
	spin_lock(&busid_priv->busid_lock);
	busid_priv->sdev = शून्य;
	busid_priv->status = save_status;
	spin_unlock(&busid_priv->busid_lock);
	/* lock is released - go to मुक्त */
	जाओ sdev_मुक्त;

call_put_busid_priv:
	/* release the busid_lock */
	put_busid_priv(busid_priv);

sdev_मुक्त:
	stub_device_मुक्त(sdev);

	वापस rc;
पूर्ण

अटल व्योम shutकरोwn_busid(काष्ठा bus_id_priv *busid_priv)
अणु
	usbip_event_add(&busid_priv->sdev->ud, SDEV_EVENT_REMOVED);

	/* रुको क्रम the stop of the event handler */
	usbip_stop_eh(&busid_priv->sdev->ud);
पूर्ण

/*
 * called in usb_disconnect() or usb_deरेजिस्टर()
 * but only अगर actconfig(active configuration) exists
 */
अटल व्योम stub_disconnect(काष्ठा usb_device *udev)
अणु
	काष्ठा stub_device *sdev;
	स्थिर अक्षर *udev_busid = dev_name(&udev->dev);
	काष्ठा bus_id_priv *busid_priv;
	पूर्णांक rc;

	dev_dbg(&udev->dev, "Enter disconnect\n");

	busid_priv = get_busid_priv(udev_busid);
	अगर (!busid_priv) अणु
		BUG();
		वापस;
	पूर्ण

	sdev = dev_get_drvdata(&udev->dev);

	/* get stub_device */
	अगर (!sdev) अणु
		dev_err(&udev->dev, "could not get device");
		/* release busid_lock */
		put_busid_priv(busid_priv);
		वापस;
	पूर्ण

	dev_set_drvdata(&udev->dev, शून्य);

	/* release busid_lock beक्रमe call to हटाओ device files */
	put_busid_priv(busid_priv);

	/*
	 * NOTE: rx/tx thपढ़ोs are invoked क्रम each usb_device.
	 */

	/* release port */
	rc = usb_hub_release_port(udev->parent, udev->portnum,
				  (काष्ठा usb_dev_state *) udev);
	अगर (rc) अणु
		dev_dbg(&udev->dev, "unable to release port\n");
		वापस;
	पूर्ण

	/* If usb reset is called from event handler */
	अगर (usbip_in_eh(current))
		वापस;

	/* we alपढ़ोy have busid_priv, just lock busid_lock */
	spin_lock(&busid_priv->busid_lock);
	अगर (!busid_priv->shutकरोwn_busid)
		busid_priv->shutकरोwn_busid = 1;
	/* release busid_lock */
	spin_unlock(&busid_priv->busid_lock);

	/* shutकरोwn the current connection */
	shutकरोwn_busid(busid_priv);

	usb_put_dev(sdev->udev);

	/* we alपढ़ोy have busid_priv, just lock busid_lock */
	spin_lock(&busid_priv->busid_lock);
	/* मुक्त sdev */
	busid_priv->sdev = शून्य;
	stub_device_मुक्त(sdev);

	अगर (busid_priv->status == STUB_BUSID_ALLOC)
		busid_priv->status = STUB_BUSID_ADDED;
	/* release busid_lock */
	spin_unlock(&busid_priv->busid_lock);
	वापस;
पूर्ण

#अगर_घोषित CONFIG_PM

/* These functions need usb_port_suspend and usb_port_resume,
 * which reside in drivers/usb/core/usb.h. Skip क्रम now. */

अटल पूर्णांक stub_suspend(काष्ठा usb_device *udev, pm_message_t message)
अणु
	dev_dbg(&udev->dev, "stub_suspend\n");

	वापस 0;
पूर्ण

अटल पूर्णांक stub_resume(काष्ठा usb_device *udev, pm_message_t message)
अणु
	dev_dbg(&udev->dev, "stub_resume\n");

	वापस 0;
पूर्ण

#पूर्ण_अगर	/* CONFIG_PM */

काष्ठा usb_device_driver stub_driver = अणु
	.name		= "usbip-host",
	.probe		= stub_probe,
	.disconnect	= stub_disconnect,
#अगर_घोषित CONFIG_PM
	.suspend	= stub_suspend,
	.resume		= stub_resume,
#पूर्ण_अगर
	.supports_स्वतःsuspend	=	0,
	.dev_groups	= usbip_groups,
पूर्ण;
