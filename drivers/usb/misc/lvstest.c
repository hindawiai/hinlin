<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/usb/misc/lvstest.c
 *
 * Test pattern generation क्रम Link Layer Validation System Tests
 *
 * Copyright (C) 2014 ST Microelectronics
 * Pratyush Anand <pratyush.anand@gmail.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/ch11.h>
#समावेश <linux/usb/hcd.h>
#समावेश <linux/usb/phy.h>

काष्ठा lvs_rh अणु
	/* root hub पूर्णांकerface */
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;
	/* अगर lvs device connected */
	bool present;
	/* port no at which lvs device is present */
	पूर्णांक portnum;
	/* urb buffer */
	u8 buffer[8];
	/* class descriptor */
	काष्ठा usb_hub_descriptor descriptor;
	/* urb क्रम polling पूर्णांकerrupt pipe */
	काष्ठा urb *urb;
	/* LVH RH work */
	काष्ठा work_काष्ठा	rh_work;
	/* RH port status */
	काष्ठा usb_port_status port_status;
पूर्ण;

अटल काष्ठा usb_device *create_lvs_device(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_device *udev, *hdev;
	काष्ठा usb_hcd *hcd;
	काष्ठा lvs_rh *lvs = usb_get_पूर्णांकfdata(पूर्णांकf);

	अगर (!lvs->present) अणु
		dev_err(&पूर्णांकf->dev, "No LVS device is present\n");
		वापस शून्य;
	पूर्ण

	hdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	hcd = bus_to_hcd(hdev->bus);

	udev = usb_alloc_dev(hdev, hdev->bus, lvs->portnum);
	अगर (!udev) अणु
		dev_err(&पूर्णांकf->dev, "Could not allocate lvs udev\n");
		वापस शून्य;
	पूर्ण
	udev->speed = USB_SPEED_SUPER;
	udev->ep0.desc.wMaxPacketSize = cpu_to_le16(512);
	usb_set_device_state(udev, USB_STATE_DEFAULT);

	अगर (hcd->driver->enable_device) अणु
		अगर (hcd->driver->enable_device(hcd, udev) < 0) अणु
			dev_err(&पूर्णांकf->dev, "Failed to enable\n");
			usb_put_dev(udev);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस udev;
पूर्ण

अटल व्योम destroy_lvs_device(काष्ठा usb_device *udev)
अणु
	काष्ठा usb_device *hdev = udev->parent;
	काष्ठा usb_hcd *hcd = bus_to_hcd(hdev->bus);

	अगर (hcd->driver->मुक्त_dev)
		hcd->driver->मुक्त_dev(hcd, udev);

	usb_put_dev(udev);
पूर्ण

अटल पूर्णांक lvs_rh_clear_port_feature(काष्ठा usb_device *hdev,
		पूर्णांक port1, पूर्णांक feature)
अणु
	वापस usb_control_msg(hdev, usb_sndctrlpipe(hdev, 0),
		USB_REQ_CLEAR_FEATURE, USB_RT_PORT, feature, port1,
		शून्य, 0, 1000);
पूर्ण

अटल पूर्णांक lvs_rh_set_port_feature(काष्ठा usb_device *hdev,
		पूर्णांक port1, पूर्णांक feature)
अणु
	वापस usb_control_msg(hdev, usb_sndctrlpipe(hdev, 0),
		USB_REQ_SET_FEATURE, USB_RT_PORT, feature, port1,
		शून्य, 0, 1000);
पूर्ण

अटल sमाप_प्रकार u3_entry_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_device *hdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा lvs_rh *lvs = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा usb_device *udev;
	पूर्णांक ret;

	udev = create_lvs_device(पूर्णांकf);
	अगर (!udev) अणु
		dev_err(dev, "failed to create lvs device\n");
		वापस -ENOMEM;
	पूर्ण

	ret = lvs_rh_set_port_feature(hdev, lvs->portnum,
			USB_PORT_FEAT_SUSPEND);
	अगर (ret < 0)
		dev_err(dev, "can't issue U3 entry %d\n", ret);

	destroy_lvs_device(udev);

	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(u3_entry);

अटल sमाप_प्रकार u3_निकास_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_device *hdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा lvs_rh *lvs = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा usb_device *udev;
	पूर्णांक ret;

	udev = create_lvs_device(पूर्णांकf);
	अगर (!udev) अणु
		dev_err(dev, "failed to create lvs device\n");
		वापस -ENOMEM;
	पूर्ण

	ret = lvs_rh_clear_port_feature(hdev, lvs->portnum,
			USB_PORT_FEAT_SUSPEND);
	अगर (ret < 0)
		dev_err(dev, "can't issue U3 exit %d\n", ret);

	destroy_lvs_device(udev);

	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(u3_निकास);

अटल sमाप_प्रकार hot_reset_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_device *hdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा lvs_rh *lvs = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक ret;

	ret = lvs_rh_set_port_feature(hdev, lvs->portnum,
			USB_PORT_FEAT_RESET);
	अगर (ret < 0) अणु
		dev_err(dev, "can't issue hot reset %d\n", ret);
		वापस ret;
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(hot_reset);

अटल sमाप_प्रकार warm_reset_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_device *hdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा lvs_rh *lvs = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक ret;

	ret = lvs_rh_set_port_feature(hdev, lvs->portnum,
			USB_PORT_FEAT_BH_PORT_RESET);
	अगर (ret < 0) अणु
		dev_err(dev, "can't issue warm reset %d\n", ret);
		वापस ret;
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(warm_reset);

अटल sमाप_प्रकार u2_समयout_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_device *hdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा lvs_rh *lvs = usb_get_पूर्णांकfdata(पूर्णांकf);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret < 0) अणु
		dev_err(dev, "couldn't parse string %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (val > 127)
		वापस -EINVAL;

	ret = lvs_rh_set_port_feature(hdev, lvs->portnum | (val << 8),
			USB_PORT_FEAT_U2_TIMEOUT);
	अगर (ret < 0) अणु
		dev_err(dev, "Error %d while setting U2 timeout %ld\n", ret, val);
		वापस ret;
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(u2_समयout);

अटल sमाप_प्रकार u1_समयout_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_device *hdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा lvs_rh *lvs = usb_get_पूर्णांकfdata(पूर्णांकf);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret < 0) अणु
		dev_err(dev, "couldn't parse string %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (val > 127)
		वापस -EINVAL;

	ret = lvs_rh_set_port_feature(hdev, lvs->portnum | (val << 8),
			USB_PORT_FEAT_U1_TIMEOUT);
	अगर (ret < 0) अणु
		dev_err(dev, "Error %d while setting U1 timeout %ld\n", ret, val);
		वापस ret;
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(u1_समयout);

अटल sमाप_प्रकार get_dev_desc_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_device *udev;
	काष्ठा usb_device_descriptor *descriptor;
	पूर्णांक ret;

	descriptor = kदो_स्मृति(माप(*descriptor), GFP_KERNEL);
	अगर (!descriptor)
		वापस -ENOMEM;

	udev = create_lvs_device(पूर्णांकf);
	अगर (!udev) अणु
		dev_err(dev, "failed to create lvs device\n");
		ret = -ENOMEM;
		जाओ मुक्त_desc;
	पूर्ण

	ret = usb_control_msg(udev, (PIPE_CONTROL << 30) | USB_सूची_IN,
			USB_REQ_GET_DESCRIPTOR, USB_सूची_IN, USB_DT_DEVICE << 8,
			0, descriptor, माप(*descriptor),
			USB_CTRL_GET_TIMEOUT);
	अगर (ret < 0)
		dev_err(dev, "can't read device descriptor %d\n", ret);

	destroy_lvs_device(udev);

मुक्त_desc:
	kमुक्त(descriptor);

	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(get_dev_desc);

अटल sमाप_प्रकार enable_compliance_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_device *hdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा lvs_rh *lvs = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक ret;

	ret = lvs_rh_set_port_feature(hdev,
			lvs->portnum | USB_SS_PORT_LS_COMP_MOD << 3,
			USB_PORT_FEAT_LINK_STATE);
	अगर (ret < 0) अणु
		dev_err(dev, "can't enable compliance mode %d\n", ret);
		वापस ret;
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR_WO(enable_compliance);

अटल काष्ठा attribute *lvs_attrs[] = अणु
	&dev_attr_get_dev_desc.attr,
	&dev_attr_u1_समयout.attr,
	&dev_attr_u2_समयout.attr,
	&dev_attr_hot_reset.attr,
	&dev_attr_warm_reset.attr,
	&dev_attr_u3_entry.attr,
	&dev_attr_u3_निकास.attr,
	&dev_attr_enable_compliance.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(lvs);

अटल व्योम lvs_rh_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lvs_rh *lvs = container_of(work, काष्ठा lvs_rh, rh_work);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = lvs->पूर्णांकf;
	काष्ठा usb_device *hdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा usb_hcd *hcd = bus_to_hcd(hdev->bus);
	काष्ठा usb_hub_descriptor *descriptor = &lvs->descriptor;
	काष्ठा usb_port_status *port_status = &lvs->port_status;
	पूर्णांक i, ret = 0;
	u16 portchange;

	/* Examine each root port */
	क्रम (i = 1; i <= descriptor->bNbrPorts; i++) अणु
		ret = usb_control_msg(hdev, usb_rcvctrlpipe(hdev, 0),
			USB_REQ_GET_STATUS, USB_सूची_IN | USB_RT_PORT, 0, i,
			port_status, माप(*port_status), 1000);
		अगर (ret < 4)
			जारी;

		portchange = le16_to_cpu(port_status->wPortChange);

		अगर (portchange & USB_PORT_STAT_C_LINK_STATE)
			lvs_rh_clear_port_feature(hdev, i,
					USB_PORT_FEAT_C_PORT_LINK_STATE);
		अगर (portchange & USB_PORT_STAT_C_ENABLE)
			lvs_rh_clear_port_feature(hdev, i,
					USB_PORT_FEAT_C_ENABLE);
		अगर (portchange & USB_PORT_STAT_C_RESET)
			lvs_rh_clear_port_feature(hdev, i,
					USB_PORT_FEAT_C_RESET);
		अगर (portchange & USB_PORT_STAT_C_BH_RESET)
			lvs_rh_clear_port_feature(hdev, i,
					USB_PORT_FEAT_C_BH_PORT_RESET);
		अगर (portchange & USB_PORT_STAT_C_CONNECTION) अणु
			lvs_rh_clear_port_feature(hdev, i,
					USB_PORT_FEAT_C_CONNECTION);

			अगर (le16_to_cpu(port_status->wPortStatus) &
					USB_PORT_STAT_CONNECTION) अणु
				lvs->present = true;
				lvs->portnum = i;
				अगर (hcd->usb_phy)
					usb_phy_notअगरy_connect(hcd->usb_phy,
							USB_SPEED_SUPER);
			पूर्ण अन्यथा अणु
				lvs->present = false;
				अगर (hcd->usb_phy)
					usb_phy_notअगरy_disconnect(hcd->usb_phy,
							USB_SPEED_SUPER);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	ret = usb_submit_urb(lvs->urb, GFP_KERNEL);
	अगर (ret != 0 && ret != -ENODEV && ret != -EPERM)
		dev_err(&पूर्णांकf->dev, "urb resubmit error %d\n", ret);
पूर्ण

अटल व्योम lvs_rh_irq(काष्ठा urb *urb)
अणु
	काष्ठा lvs_rh *lvs = urb->context;

	schedule_work(&lvs->rh_work);
पूर्ण

अटल पूर्णांक lvs_rh_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *hdev;
	काष्ठा usb_host_पूर्णांकerface *desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	काष्ठा lvs_rh *lvs;
	अचिन्हित पूर्णांक pipe;
	पूर्णांक ret, maxp;

	hdev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	desc = पूर्णांकf->cur_altsetting;

	ret = usb_find_पूर्णांक_in_endpoपूर्णांक(desc, &endpoपूर्णांक);
	अगर (ret)
		वापस ret;

	/* valid only क्रम SS root hub */
	अगर (hdev->descriptor.bDeviceProtocol != USB_HUB_PR_SS || hdev->parent) अणु
		dev_err(&पूर्णांकf->dev, "Bind LVS driver with SS root Hub only\n");
		वापस -EINVAL;
	पूर्ण

	lvs = devm_kzalloc(&पूर्णांकf->dev, माप(*lvs), GFP_KERNEL);
	अगर (!lvs)
		वापस -ENOMEM;

	lvs->पूर्णांकf = पूर्णांकf;
	usb_set_पूर्णांकfdata(पूर्णांकf, lvs);

	/* how many number of ports this root hub has */
	ret = usb_control_msg(hdev, usb_rcvctrlpipe(hdev, 0),
			USB_REQ_GET_DESCRIPTOR, USB_सूची_IN | USB_RT_HUB,
			USB_DT_SS_HUB << 8, 0, &lvs->descriptor,
			USB_DT_SS_HUB_SIZE, USB_CTRL_GET_TIMEOUT);
	अगर (ret < (USB_DT_HUB_NONVAR_SIZE + 2)) अणु
		dev_err(&hdev->dev, "wrong root hub descriptor read %d\n", ret);
		वापस ret < 0 ? ret : -EINVAL;
	पूर्ण

	/* submit urb to poll पूर्णांकerrupt endpoपूर्णांक */
	lvs->urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!lvs->urb)
		वापस -ENOMEM;

	INIT_WORK(&lvs->rh_work, lvs_rh_work);

	pipe = usb_rcvपूर्णांकpipe(hdev, endpoपूर्णांक->bEndpoपूर्णांकAddress);
	maxp = usb_maxpacket(hdev, pipe, usb_pipeout(pipe));
	usb_fill_पूर्णांक_urb(lvs->urb, hdev, pipe, &lvs->buffer[0], maxp,
			lvs_rh_irq, lvs, endpoपूर्णांक->bInterval);

	ret = usb_submit_urb(lvs->urb, GFP_KERNEL);
	अगर (ret < 0) अणु
		dev_err(&पूर्णांकf->dev, "couldn't submit lvs urb %d\n", ret);
		जाओ मुक्त_urb;
	पूर्ण

	वापस ret;

मुक्त_urb:
	usb_मुक्त_urb(lvs->urb);
	वापस ret;
पूर्ण

अटल व्योम lvs_rh_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा lvs_rh *lvs = usb_get_पूर्णांकfdata(पूर्णांकf);

	usb_poison_urb(lvs->urb); /* used in scheduled work */
	flush_work(&lvs->rh_work);
	usb_मुक्त_urb(lvs->urb);
पूर्ण

अटल काष्ठा usb_driver lvs_driver = अणु
	.name =		"lvs",
	.probe =	lvs_rh_probe,
	.disconnect =	lvs_rh_disconnect,
	.dev_groups =	lvs_groups,
पूर्ण;

module_usb_driver(lvs_driver);

MODULE_DESCRIPTION("Link Layer Validation System Driver");
MODULE_LICENSE("GPL");
