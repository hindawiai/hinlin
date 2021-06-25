<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2003-2008 Takahiro Hirofuchi
 * Copyright (C) 2015-2016 Nobuo Iwata
 */

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/file.h>
#समावेश <linux/net.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

/* Hardening क्रम Spectre-v1 */
#समावेश <linux/nospec.h>

#समावेश "usbip_common.h"
#समावेश "vhci.h"

/* TODO: refine locking ?*/

/*
 * output example:
 * hub port sta spd dev       sockfd local_busid
 * hs  0000 004 000 00000000  000003 1-2.3
 * ................................................
 * ss  0008 004 000 00000000  000004 2-3.4
 * ................................................
 *
 * Output includes socket fd instead of socket poपूर्णांकer address to aव्योम
 * leaking kernel memory address in:
 *	/sys/devices/platक्रमm/vhci_hcd.0/status and in debug output.
 * The socket poपूर्णांकer address is not used at the moment and it was made
 * visible as a convenient way to find IP address from socket poपूर्णांकer
 * address by looking up /proc/net/अणुtcp,tcp6पूर्ण. As this खोलोs a security
 * hole, the change is made to use sockfd instead.
 *
 */
अटल व्योम port_show_vhci(अक्षर **out, पूर्णांक hub, पूर्णांक port, काष्ठा vhci_device *vdev)
अणु
	अगर (hub == HUB_SPEED_HIGH)
		*out += प्र_लिखो(*out, "hs  %04u %03u ",
				      port, vdev->ud.status);
	अन्यथा /* hub == HUB_SPEED_SUPER */
		*out += प्र_लिखो(*out, "ss  %04u %03u ",
				      port, vdev->ud.status);

	अगर (vdev->ud.status == VDEV_ST_USED) अणु
		*out += प्र_लिखो(*out, "%03u %08x ",
				      vdev->speed, vdev->devid);
		*out += प्र_लिखो(*out, "%06u %s",
				      vdev->ud.sockfd,
				      dev_name(&vdev->udev->dev));

	पूर्ण अन्यथा अणु
		*out += प्र_लिखो(*out, "000 00000000 ");
		*out += प्र_लिखो(*out, "000000 0-0");
	पूर्ण

	*out += प्र_लिखो(*out, "\n");
पूर्ण

/* Sysfs entry to show port status */
अटल sमाप_प्रकार status_show_vhci(पूर्णांक pdev_nr, अक्षर *out)
अणु
	काष्ठा platक्रमm_device *pdev = vhcis[pdev_nr].pdev;
	काष्ठा vhci *vhci;
	काष्ठा usb_hcd *hcd;
	काष्ठा vhci_hcd *vhci_hcd;
	अक्षर *s = out;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	अगर (!pdev || !out) अणु
		usbip_dbg_vhci_sysfs("show status error\n");
		वापस 0;
	पूर्ण

	hcd = platक्रमm_get_drvdata(pdev);
	vhci_hcd = hcd_to_vhci_hcd(hcd);
	vhci = vhci_hcd->vhci;

	spin_lock_irqsave(&vhci->lock, flags);

	क्रम (i = 0; i < VHCI_HC_PORTS; i++) अणु
		काष्ठा vhci_device *vdev = &vhci->vhci_hcd_hs->vdev[i];

		spin_lock(&vdev->ud.lock);
		port_show_vhci(&out, HUB_SPEED_HIGH,
			       pdev_nr * VHCI_PORTS + i, vdev);
		spin_unlock(&vdev->ud.lock);
	पूर्ण

	क्रम (i = 0; i < VHCI_HC_PORTS; i++) अणु
		काष्ठा vhci_device *vdev = &vhci->vhci_hcd_ss->vdev[i];

		spin_lock(&vdev->ud.lock);
		port_show_vhci(&out, HUB_SPEED_SUPER,
			       pdev_nr * VHCI_PORTS + VHCI_HC_PORTS + i, vdev);
		spin_unlock(&vdev->ud.lock);
	पूर्ण

	spin_unlock_irqrestore(&vhci->lock, flags);

	वापस out - s;
पूर्ण

अटल sमाप_प्रकार status_show_not_पढ़ोy(पूर्णांक pdev_nr, अक्षर *out)
अणु
	अक्षर *s = out;
	पूर्णांक i = 0;

	क्रम (i = 0; i < VHCI_HC_PORTS; i++) अणु
		out += प्र_लिखो(out, "hs  %04u %03u ",
				    (pdev_nr * VHCI_PORTS) + i,
				    VDEV_ST_NOTASSIGNED);
		out += प्र_लिखो(out, "000 00000000 0000000000000000 0-0");
		out += प्र_लिखो(out, "\n");
	पूर्ण

	क्रम (i = 0; i < VHCI_HC_PORTS; i++) अणु
		out += प्र_लिखो(out, "ss  %04u %03u ",
				    (pdev_nr * VHCI_PORTS) + VHCI_HC_PORTS + i,
				    VDEV_ST_NOTASSIGNED);
		out += प्र_लिखो(out, "000 00000000 0000000000000000 0-0");
		out += प्र_लिखो(out, "\n");
	पूर्ण
	वापस out - s;
पूर्ण

अटल पूर्णांक status_name_to_id(स्थिर अक्षर *name)
अणु
	अक्षर *c;
	दीर्घ val;
	पूर्णांक ret;

	c = म_अक्षर(name, '.');
	अगर (c == शून्य)
		वापस 0;

	ret = kम_से_दीर्घ(c+1, 10, &val);
	अगर (ret < 0)
		वापस ret;

	वापस val;
पूर्ण

अटल sमाप_प्रकार status_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *out)
अणु
	अक्षर *s = out;
	पूर्णांक pdev_nr;

	out += प्र_लिखो(out,
		       "hub port sta spd dev      sockfd local_busid\n");

	pdev_nr = status_name_to_id(attr->attr.name);
	अगर (pdev_nr < 0)
		out += status_show_not_पढ़ोy(pdev_nr, out);
	अन्यथा
		out += status_show_vhci(pdev_nr, out);

	वापस out - s;
पूर्ण

अटल sमाप_प्रकार nports_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *out)
अणु
	अक्षर *s = out;

	/*
	 * Half the ports are क्रम SPEED_HIGH and half क्रम SPEED_SUPER,
	 * thus the * 2.
	 */
	out += प्र_लिखो(out, "%d\n", VHCI_PORTS * vhci_num_controllers);
	वापस out - s;
पूर्ण
अटल DEVICE_ATTR_RO(nports);

/* Sysfs entry to shutकरोwn a भव connection */
अटल पूर्णांक vhci_port_disconnect(काष्ठा vhci_hcd *vhci_hcd, __u32 rhport)
अणु
	काष्ठा vhci_device *vdev = &vhci_hcd->vdev[rhport];
	काष्ठा vhci *vhci = vhci_hcd->vhci;
	अचिन्हित दीर्घ flags;

	usbip_dbg_vhci_sysfs("enter\n");

	mutex_lock(&vdev->ud.sysfs_lock);

	/* lock */
	spin_lock_irqsave(&vhci->lock, flags);
	spin_lock(&vdev->ud.lock);

	अगर (vdev->ud.status == VDEV_ST_शून्य) अणु
		pr_err("not connected %d\n", vdev->ud.status);

		/* unlock */
		spin_unlock(&vdev->ud.lock);
		spin_unlock_irqrestore(&vhci->lock, flags);
		mutex_unlock(&vdev->ud.sysfs_lock);

		वापस -EINVAL;
	पूर्ण

	/* unlock */
	spin_unlock(&vdev->ud.lock);
	spin_unlock_irqrestore(&vhci->lock, flags);

	usbip_event_add(&vdev->ud, VDEV_EVENT_DOWN);

	mutex_unlock(&vdev->ud.sysfs_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक valid_port(__u32 *pdev_nr, __u32 *rhport)
अणु
	अगर (*pdev_nr >= vhci_num_controllers) अणु
		pr_err("pdev %u\n", *pdev_nr);
		वापस 0;
	पूर्ण
	*pdev_nr = array_index_nospec(*pdev_nr, vhci_num_controllers);

	अगर (*rhport >= VHCI_HC_PORTS) अणु
		pr_err("rhport %u\n", *rhport);
		वापस 0;
	पूर्ण
	*rhport = array_index_nospec(*rhport, VHCI_HC_PORTS);

	वापस 1;
पूर्ण

अटल sमाप_प्रकार detach_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	__u32 port = 0, pdev_nr = 0, rhport = 0;
	काष्ठा usb_hcd *hcd;
	काष्ठा vhci_hcd *vhci_hcd;
	पूर्णांक ret;

	अगर (kstrtoपूर्णांक(buf, 10, &port) < 0)
		वापस -EINVAL;

	pdev_nr = port_to_pdev_nr(port);
	rhport = port_to_rhport(port);

	अगर (!valid_port(&pdev_nr, &rhport))
		वापस -EINVAL;

	hcd = platक्रमm_get_drvdata(vhcis[pdev_nr].pdev);
	अगर (hcd == शून्य) अणु
		dev_err(dev, "port is not ready %u\n", port);
		वापस -EAGAIN;
	पूर्ण

	usbip_dbg_vhci_sysfs("rhport %d\n", rhport);

	अगर ((port / VHCI_HC_PORTS) % 2)
		vhci_hcd = hcd_to_vhci_hcd(hcd)->vhci->vhci_hcd_ss;
	अन्यथा
		vhci_hcd = hcd_to_vhci_hcd(hcd)->vhci->vhci_hcd_hs;

	ret = vhci_port_disconnect(vhci_hcd, rhport);
	अगर (ret < 0)
		वापस -EINVAL;

	usbip_dbg_vhci_sysfs("Leave\n");

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(detach);

अटल पूर्णांक valid_args(__u32 *pdev_nr, __u32 *rhport,
		      क्रमागत usb_device_speed speed)
अणु
	अगर (!valid_port(pdev_nr, rhport)) अणु
		वापस 0;
	पूर्ण

	चयन (speed) अणु
	हाल USB_SPEED_LOW:
	हाल USB_SPEED_FULL:
	हाल USB_SPEED_HIGH:
	हाल USB_SPEED_WIRELESS:
	हाल USB_SPEED_SUPER:
		अवरोध;
	शेष:
		pr_err("Failed attach request for unsupported USB speed: %s\n",
			usb_speed_string(speed));
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* Sysfs entry to establish a भव connection */
/*
 * To start a new USB/IP attachment, a userland program needs to setup a TCP
 * connection and then ग_लिखो its socket descriptor with remote device
 * inक्रमmation पूर्णांकo this sysfs file.
 *
 * A remote device is भवly attached to the root-hub port of @rhport with
 * @speed. @devid is embedded पूर्णांकo a request to specअगरy the remote device in a
 * server host.
 *
 * ग_लिखो() वापसs 0 on success, अन्यथा negative त्रुटि_सं.
 */
अटल sमाप_प्रकार attach_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा socket *socket;
	पूर्णांक sockfd = 0;
	__u32 port = 0, pdev_nr = 0, rhport = 0, devid = 0, speed = 0;
	काष्ठा usb_hcd *hcd;
	काष्ठा vhci_hcd *vhci_hcd;
	काष्ठा vhci_device *vdev;
	काष्ठा vhci *vhci;
	पूर्णांक err;
	अचिन्हित दीर्घ flags;
	काष्ठा task_काष्ठा *tcp_rx = शून्य;
	काष्ठा task_काष्ठा *tcp_tx = शून्य;

	/*
	 * @rhport: port number of vhci_hcd
	 * @sockfd: socket descriptor of an established TCP connection
	 * @devid: unique device identअगरier in a remote host
	 * @speed: usb device speed in a remote host
	 */
	अगर (माला_पूछो(buf, "%u %u %u %u", &port, &sockfd, &devid, &speed) != 4)
		वापस -EINVAL;
	pdev_nr = port_to_pdev_nr(port);
	rhport = port_to_rhport(port);

	usbip_dbg_vhci_sysfs("port(%u) pdev(%d) rhport(%u)\n",
			     port, pdev_nr, rhport);
	usbip_dbg_vhci_sysfs("sockfd(%u) devid(%u) speed(%u)\n",
			     sockfd, devid, speed);

	/* check received parameters */
	अगर (!valid_args(&pdev_nr, &rhport, speed))
		वापस -EINVAL;

	hcd = platक्रमm_get_drvdata(vhcis[pdev_nr].pdev);
	अगर (hcd == शून्य) अणु
		dev_err(dev, "port %d is not ready\n", port);
		वापस -EAGAIN;
	पूर्ण

	vhci_hcd = hcd_to_vhci_hcd(hcd);
	vhci = vhci_hcd->vhci;

	अगर (speed == USB_SPEED_SUPER)
		vdev = &vhci->vhci_hcd_ss->vdev[rhport];
	अन्यथा
		vdev = &vhci->vhci_hcd_hs->vdev[rhport];

	mutex_lock(&vdev->ud.sysfs_lock);

	/* Extract socket from fd. */
	socket = sockfd_lookup(sockfd, &err);
	अगर (!socket) अणु
		dev_err(dev, "failed to lookup sock");
		err = -EINVAL;
		जाओ unlock_mutex;
	पूर्ण
	अगर (socket->type != SOCK_STREAM) अणु
		dev_err(dev, "Expecting SOCK_STREAM - found %d",
			socket->type);
		sockfd_put(socket);
		err = -EINVAL;
		जाओ unlock_mutex;
	पूर्ण

	/* create thपढ़ोs beक्रमe locking */
	tcp_rx = kthपढ़ो_create(vhci_rx_loop, &vdev->ud, "vhci_rx");
	अगर (IS_ERR(tcp_rx)) अणु
		sockfd_put(socket);
		err = -EINVAL;
		जाओ unlock_mutex;
	पूर्ण
	tcp_tx = kthपढ़ो_create(vhci_tx_loop, &vdev->ud, "vhci_tx");
	अगर (IS_ERR(tcp_tx)) अणु
		kthपढ़ो_stop(tcp_rx);
		sockfd_put(socket);
		err = -EINVAL;
		जाओ unlock_mutex;
	पूर्ण

	/* get task काष्ठाs now */
	get_task_काष्ठा(tcp_rx);
	get_task_काष्ठा(tcp_tx);

	/* now begin lock until setting vdev status set */
	spin_lock_irqsave(&vhci->lock, flags);
	spin_lock(&vdev->ud.lock);

	अगर (vdev->ud.status != VDEV_ST_शून्य) अणु
		/* end of the lock */
		spin_unlock(&vdev->ud.lock);
		spin_unlock_irqrestore(&vhci->lock, flags);

		sockfd_put(socket);
		kthपढ़ो_stop_put(tcp_rx);
		kthपढ़ो_stop_put(tcp_tx);

		dev_err(dev, "port %d already used\n", rhport);
		/*
		 * Will be retried from userspace
		 * अगर there's another मुक्त port.
		 */
		err = -EBUSY;
		जाओ unlock_mutex;
	पूर्ण

	dev_info(dev, "pdev(%u) rhport(%u) sockfd(%d)\n",
		 pdev_nr, rhport, sockfd);
	dev_info(dev, "devid(%u) speed(%u) speed_str(%s)\n",
		 devid, speed, usb_speed_string(speed));

	vdev->devid         = devid;
	vdev->speed         = speed;
	vdev->ud.sockfd     = sockfd;
	vdev->ud.tcp_socket = socket;
	vdev->ud.tcp_rx     = tcp_rx;
	vdev->ud.tcp_tx     = tcp_tx;
	vdev->ud.status     = VDEV_ST_NOTASSIGNED;
	usbip_kcov_handle_init(&vdev->ud);

	spin_unlock(&vdev->ud.lock);
	spin_unlock_irqrestore(&vhci->lock, flags);
	/* end the lock */

	wake_up_process(vdev->ud.tcp_rx);
	wake_up_process(vdev->ud.tcp_tx);

	rh_port_connect(vdev, speed);

	dev_info(dev, "Device attached\n");

	mutex_unlock(&vdev->ud.sysfs_lock);

	वापस count;

unlock_mutex:
	mutex_unlock(&vdev->ud.sysfs_lock);
	वापस err;
पूर्ण
अटल DEVICE_ATTR_WO(attach);

#घोषणा MAX_STATUS_NAME 16

काष्ठा status_attr अणु
	काष्ठा device_attribute attr;
	अक्षर name[MAX_STATUS_NAME+1];
पूर्ण;

अटल काष्ठा status_attr *status_attrs;

अटल व्योम set_status_attr(पूर्णांक id)
अणु
	काष्ठा status_attr *status;

	status = status_attrs + id;
	अगर (id == 0)
		म_नकल(status->name, "status");
	अन्यथा
		snम_लिखो(status->name, MAX_STATUS_NAME+1, "status.%d", id);
	status->attr.attr.name = status->name;
	status->attr.attr.mode = S_IRUGO;
	status->attr.show = status_show;
	sysfs_attr_init(&status->attr.attr);
पूर्ण

अटल पूर्णांक init_status_attrs(व्योम)
अणु
	पूर्णांक id;

	status_attrs = kसुस्मृति(vhci_num_controllers, माप(काष्ठा status_attr),
			       GFP_KERNEL);
	अगर (status_attrs == शून्य)
		वापस -ENOMEM;

	क्रम (id = 0; id < vhci_num_controllers; id++)
		set_status_attr(id);

	वापस 0;
पूर्ण

अटल व्योम finish_status_attrs(व्योम)
अणु
	kमुक्त(status_attrs);
पूर्ण

काष्ठा attribute_group vhci_attr_group = अणु
	.attrs = शून्य,
पूर्ण;

पूर्णांक vhci_init_attr_group(व्योम)
अणु
	काष्ठा attribute **attrs;
	पूर्णांक ret, i;

	attrs = kसुस्मृति((vhci_num_controllers + 5), माप(काष्ठा attribute *),
			GFP_KERNEL);
	अगर (attrs == शून्य)
		वापस -ENOMEM;

	ret = init_status_attrs();
	अगर (ret) अणु
		kमुक्त(attrs);
		वापस ret;
	पूर्ण
	*attrs = &dev_attr_nports.attr;
	*(attrs + 1) = &dev_attr_detach.attr;
	*(attrs + 2) = &dev_attr_attach.attr;
	*(attrs + 3) = &dev_attr_usbip_debug.attr;
	क्रम (i = 0; i < vhci_num_controllers; i++)
		*(attrs + i + 4) = &((status_attrs + i)->attr.attr);
	vhci_attr_group.attrs = attrs;
	वापस 0;
पूर्ण

व्योम vhci_finish_attr_group(व्योम)
अणु
	finish_status_attrs();
	kमुक्त(vhci_attr_group.attrs);
पूर्ण
