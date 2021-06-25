<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * usb port device code
 *
 * Copyright (C) 2012 Intel Corp
 *
 * Author: Lan Tianyu <tianyu.lan@पूर्णांकel.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/pm_qos.h>

#समावेश "hub.h"

अटल पूर्णांक usb_port_block_घातer_off;

अटल स्थिर काष्ठा attribute_group *port_dev_group[];

अटल sमाप_प्रकार location_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_port *port_dev = to_usb_port(dev);

	वापस प्र_लिखो(buf, "0x%08x\n", port_dev->location);
पूर्ण
अटल DEVICE_ATTR_RO(location);

अटल sमाप_प्रकार connect_type_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_port *port_dev = to_usb_port(dev);
	अक्षर *result;

	चयन (port_dev->connect_type) अणु
	हाल USB_PORT_CONNECT_TYPE_HOT_PLUG:
		result = "hotplug";
		अवरोध;
	हाल USB_PORT_CONNECT_TYPE_HARD_WIRED:
		result = "hardwired";
		अवरोध;
	हाल USB_PORT_NOT_USED:
		result = "not used";
		अवरोध;
	शेष:
		result = "unknown";
		अवरोध;
	पूर्ण

	वापस प्र_लिखो(buf, "%s\n", result);
पूर्ण
अटल DEVICE_ATTR_RO(connect_type);

अटल sमाप_प्रकार over_current_count_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_port *port_dev = to_usb_port(dev);

	वापस प्र_लिखो(buf, "%u\n", port_dev->over_current_count);
पूर्ण
अटल DEVICE_ATTR_RO(over_current_count);

अटल sमाप_प्रकार quirks_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_port *port_dev = to_usb_port(dev);

	वापस प्र_लिखो(buf, "%08x\n", port_dev->quirks);
पूर्ण

अटल sमाप_प्रकार quirks_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_port *port_dev = to_usb_port(dev);
	u32 value;

	अगर (kstrtou32(buf, 16, &value))
		वापस -EINVAL;

	port_dev->quirks = value;
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(quirks);

अटल sमाप_प्रकार usb3_lpm_permit_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_port *port_dev = to_usb_port(dev);
	स्थिर अक्षर *p;

	अगर (port_dev->usb3_lpm_u1_permit) अणु
		अगर (port_dev->usb3_lpm_u2_permit)
			p = "u1_u2";
		अन्यथा
			p = "u1";
	पूर्ण अन्यथा अणु
		अगर (port_dev->usb3_lpm_u2_permit)
			p = "u2";
		अन्यथा
			p = "0";
	पूर्ण

	वापस प्र_लिखो(buf, "%s\n", p);
पूर्ण

अटल sमाप_प्रकार usb3_lpm_permit_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_port *port_dev = to_usb_port(dev);
	काष्ठा usb_device *udev = port_dev->child;
	काष्ठा usb_hcd *hcd;

	अगर (!म_भेदन(buf, "u1_u2", 5)) अणु
		port_dev->usb3_lpm_u1_permit = 1;
		port_dev->usb3_lpm_u2_permit = 1;

	पूर्ण अन्यथा अगर (!म_भेदन(buf, "u1", 2)) अणु
		port_dev->usb3_lpm_u1_permit = 1;
		port_dev->usb3_lpm_u2_permit = 0;

	पूर्ण अन्यथा अगर (!म_भेदन(buf, "u2", 2)) अणु
		port_dev->usb3_lpm_u1_permit = 0;
		port_dev->usb3_lpm_u2_permit = 1;

	पूर्ण अन्यथा अगर (!म_भेदन(buf, "0", 1)) अणु
		port_dev->usb3_lpm_u1_permit = 0;
		port_dev->usb3_lpm_u2_permit = 0;
	पूर्ण अन्यथा
		वापस -EINVAL;

	/* If device is connected to the port, disable or enable lpm
	 * to make new u1 u2 setting take effect immediately.
	 */
	अगर (udev) अणु
		hcd = bus_to_hcd(udev->bus);
		अगर (!hcd)
			वापस -EINVAL;
		usb_lock_device(udev);
		mutex_lock(hcd->bandwidth_mutex);
		अगर (!usb_disable_lpm(udev))
			usb_enable_lpm(udev);
		mutex_unlock(hcd->bandwidth_mutex);
		usb_unlock_device(udev);
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(usb3_lpm_permit);

अटल काष्ठा attribute *port_dev_attrs[] = अणु
	&dev_attr_connect_type.attr,
	&dev_attr_location.attr,
	&dev_attr_quirks.attr,
	&dev_attr_over_current_count.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group port_dev_attr_grp = अणु
	.attrs = port_dev_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *port_dev_group[] = अणु
	&port_dev_attr_grp,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *port_dev_usb3_attrs[] = अणु
	&dev_attr_usb3_lpm_permit.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group port_dev_usb3_attr_grp = अणु
	.attrs = port_dev_usb3_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *port_dev_usb3_group[] = अणु
	&port_dev_attr_grp,
	&port_dev_usb3_attr_grp,
	शून्य,
पूर्ण;

अटल व्योम usb_port_device_release(काष्ठा device *dev)
अणु
	काष्ठा usb_port *port_dev = to_usb_port(dev);

	kमुक्त(port_dev->req);
	kमुक्त(port_dev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक usb_port_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_port *port_dev = to_usb_port(dev);
	काष्ठा usb_device *hdev = to_usb_device(dev->parent->parent);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev->parent);
	काष्ठा usb_hub *hub = usb_hub_to_काष्ठा_hub(hdev);
	काष्ठा usb_device *udev = port_dev->child;
	काष्ठा usb_port *peer = port_dev->peer;
	पूर्णांक port1 = port_dev->portnum;
	पूर्णांक retval;

	अगर (!hub)
		वापस -EINVAL;
	अगर (hub->in_reset) अणु
		set_bit(port1, hub->घातer_bits);
		वापस 0;
	पूर्ण

	/*
	 * Power on our usb3 peer beक्रमe this usb2 port to prevent a usb3
	 * device from degrading to its usb2 connection
	 */
	अगर (!port_dev->is_superspeed && peer)
		pm_runसमय_get_sync(&peer->dev);

	retval = usb_स्वतःpm_get_पूर्णांकerface(पूर्णांकf);
	अगर (retval < 0)
		वापस retval;

	retval = usb_hub_set_port_घातer(hdev, hub, port1, true);
	msleep(hub_घातer_on_good_delay(hub));
	अगर (udev && !retval) अणु
		/*
		 * Our preference is to simply रुको क्रम the port to reconnect,
		 * as that is the lowest latency method to restart the port.
		 * However, there are हालs where toggling port घातer results in
		 * the host port and the device port getting out of sync causing
		 * a link training live lock.  Upon समयout, flag the port as
		 * needing warm reset recovery (to be perक्रमmed later by
		 * usb_port_resume() as requested via usb_wakeup_notअगरication())
		 */
		अगर (hub_port_debounce_be_connected(hub, port1) < 0) अणु
			dev_dbg(&port_dev->dev, "reconnect timeout\n");
			अगर (hub_is_superspeed(hdev))
				set_bit(port1, hub->warm_reset_bits);
		पूर्ण

		/* Force the child awake to revalidate after the घातer loss. */
		अगर (!test_and_set_bit(port1, hub->child_usage_bits)) अणु
			pm_runसमय_get_noresume(&port_dev->dev);
			pm_request_resume(&udev->dev);
		पूर्ण
	पूर्ण

	usb_स्वतःpm_put_पूर्णांकerface(पूर्णांकf);

	वापस retval;
पूर्ण

अटल पूर्णांक usb_port_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb_port *port_dev = to_usb_port(dev);
	काष्ठा usb_device *hdev = to_usb_device(dev->parent->parent);
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev->parent);
	काष्ठा usb_hub *hub = usb_hub_to_काष्ठा_hub(hdev);
	काष्ठा usb_port *peer = port_dev->peer;
	पूर्णांक port1 = port_dev->portnum;
	पूर्णांक retval;

	अगर (!hub)
		वापस -EINVAL;
	अगर (hub->in_reset)
		वापस -EBUSY;

	अगर (dev_pm_qos_flags(&port_dev->dev, PM_QOS_FLAG_NO_POWER_OFF)
			== PM_QOS_FLAGS_ALL)
		वापस -EAGAIN;

	अगर (usb_port_block_घातer_off)
		वापस -EBUSY;

	retval = usb_स्वतःpm_get_पूर्णांकerface(पूर्णांकf);
	अगर (retval < 0)
		वापस retval;

	retval = usb_hub_set_port_घातer(hdev, hub, port1, false);
	usb_clear_port_feature(hdev, port1, USB_PORT_FEAT_C_CONNECTION);
	अगर (!port_dev->is_superspeed)
		usb_clear_port_feature(hdev, port1, USB_PORT_FEAT_C_ENABLE);
	usb_स्वतःpm_put_पूर्णांकerface(पूर्णांकf);

	/*
	 * Our peer usb3 port may now be able to suspend, so
	 * asynchronously queue a suspend request to observe that this
	 * usb2 port is now off.
	 */
	अगर (!port_dev->is_superspeed && peer)
		pm_runसमय_put(&peer->dev);

	वापस retval;
पूर्ण
#पूर्ण_अगर

अटल व्योम usb_port_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा usb_port *port_dev = to_usb_port(dev);

	अगर (port_dev->child)
		usb_disable_usb2_hardware_lpm(port_dev->child);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops usb_port_pm_ops = अणु
#अगर_घोषित CONFIG_PM
	.runसमय_suspend =	usb_port_runसमय_suspend,
	.runसमय_resume =	usb_port_runसमय_resume,
#पूर्ण_अगर
पूर्ण;

काष्ठा device_type usb_port_device_type = अणु
	.name =		"usb_port",
	.release =	usb_port_device_release,
	.pm =		&usb_port_pm_ops,
पूर्ण;

अटल काष्ठा device_driver usb_port_driver = अणु
	.name = "usb",
	.owner = THIS_MODULE,
	.shutकरोwn = usb_port_shutकरोwn,
पूर्ण;

अटल पूर्णांक link_peers(काष्ठा usb_port *left, काष्ठा usb_port *right)
अणु
	काष्ठा usb_port *ss_port, *hs_port;
	पूर्णांक rc;

	अगर (left->peer == right && right->peer == left)
		वापस 0;

	अगर (left->peer || right->peer) अणु
		काष्ठा usb_port *lpeer = left->peer;
		काष्ठा usb_port *rpeer = right->peer;
		अक्षर *method;

		अगर (left->location && left->location == right->location)
			method = "location";
		अन्यथा
			method = "default";

		pr_debug("usb: failed to peer %s and %s by %s (%s:%s) (%s:%s)\n",
			dev_name(&left->dev), dev_name(&right->dev), method,
			dev_name(&left->dev),
			lpeer ? dev_name(&lpeer->dev) : "none",
			dev_name(&right->dev),
			rpeer ? dev_name(&rpeer->dev) : "none");
		वापस -EBUSY;
	पूर्ण

	rc = sysfs_create_link(&left->dev.kobj, &right->dev.kobj, "peer");
	अगर (rc)
		वापस rc;
	rc = sysfs_create_link(&right->dev.kobj, &left->dev.kobj, "peer");
	अगर (rc) अणु
		sysfs_हटाओ_link(&left->dev.kobj, "peer");
		वापस rc;
	पूर्ण

	/*
	 * We need to wake the HiSpeed port to make sure we करोn't race
	 * setting ->peer with usb_port_runसमय_suspend().  Otherwise we
	 * may miss a suspend event क्रम the SuperSpeed port.
	 */
	अगर (left->is_superspeed) अणु
		ss_port = left;
		WARN_ON(right->is_superspeed);
		hs_port = right;
	पूर्ण अन्यथा अणु
		ss_port = right;
		WARN_ON(!right->is_superspeed);
		hs_port = left;
	पूर्ण
	pm_runसमय_get_sync(&hs_port->dev);

	left->peer = right;
	right->peer = left;

	/*
	 * The SuperSpeed reference is dropped when the HiSpeed port in
	 * this relationship suspends, i.e. when it is safe to allow a
	 * SuperSpeed connection to drop since there is no risk of a
	 * device degrading to its घातered-off HiSpeed connection.
	 *
	 * Also, drop the HiSpeed ref taken above.
	 */
	pm_runसमय_get_sync(&ss_port->dev);
	pm_runसमय_put(&hs_port->dev);

	वापस 0;
पूर्ण

अटल व्योम link_peers_report(काष्ठा usb_port *left, काष्ठा usb_port *right)
अणु
	पूर्णांक rc;

	rc = link_peers(left, right);
	अगर (rc == 0) अणु
		dev_dbg(&left->dev, "peered to %s\n", dev_name(&right->dev));
	पूर्ण अन्यथा अणु
		dev_dbg(&left->dev, "failed to peer to %s (%d)\n",
				dev_name(&right->dev), rc);
		pr_warn_once("usb: port power management may be unreliable\n");
		usb_port_block_घातer_off = 1;
	पूर्ण
पूर्ण

अटल व्योम unlink_peers(काष्ठा usb_port *left, काष्ठा usb_port *right)
अणु
	काष्ठा usb_port *ss_port, *hs_port;

	WARN(right->peer != left || left->peer != right,
			"%s and %s are not peers?\n",
			dev_name(&left->dev), dev_name(&right->dev));

	/*
	 * We wake the HiSpeed port to make sure we करोn't race its
	 * usb_port_runसमय_resume() event which takes a SuperSpeed ref
	 * when ->peer is !शून्य.
	 */
	अगर (left->is_superspeed) अणु
		ss_port = left;
		hs_port = right;
	पूर्ण अन्यथा अणु
		ss_port = right;
		hs_port = left;
	पूर्ण

	pm_runसमय_get_sync(&hs_port->dev);

	sysfs_हटाओ_link(&left->dev.kobj, "peer");
	right->peer = शून्य;
	sysfs_हटाओ_link(&right->dev.kobj, "peer");
	left->peer = शून्य;

	/* Drop the SuperSpeed ref held on behalf of the active HiSpeed port */
	pm_runसमय_put(&ss_port->dev);

	/* Drop the ref taken above */
	pm_runसमय_put(&hs_port->dev);
पूर्ण

/*
 * For each usb hub device in the प्रणाली check to see अगर it is in the
 * peer करोमुख्य of the given port_dev, and अगर it is check to see अगर it
 * has a port that matches the given port by location
 */
अटल पूर्णांक match_location(काष्ठा usb_device *peer_hdev, व्योम *p)
अणु
	पूर्णांक port1;
	काष्ठा usb_hcd *hcd, *peer_hcd;
	काष्ठा usb_port *port_dev = p, *peer;
	काष्ठा usb_hub *peer_hub = usb_hub_to_काष्ठा_hub(peer_hdev);
	काष्ठा usb_device *hdev = to_usb_device(port_dev->dev.parent->parent);

	अगर (!peer_hub)
		वापस 0;

	hcd = bus_to_hcd(hdev->bus);
	peer_hcd = bus_to_hcd(peer_hdev->bus);
	/* peer_hcd is provisional until we verअगरy it against the known peer */
	अगर (peer_hcd != hcd->shared_hcd)
		वापस 0;

	क्रम (port1 = 1; port1 <= peer_hdev->maxchild; port1++) अणु
		peer = peer_hub->ports[port1 - 1];
		अगर (peer && peer->location == port_dev->location) अणु
			link_peers_report(port_dev, peer);
			वापस 1; /* करोne */
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Find the peer port either via explicit platक्रमm firmware "location"
 * data, the peer hcd क्रम root hubs, or the upstream peer relationship
 * क्रम all other hubs.
 */
अटल व्योम find_and_link_peer(काष्ठा usb_hub *hub, पूर्णांक port1)
अणु
	काष्ठा usb_port *port_dev = hub->ports[port1 - 1], *peer;
	काष्ठा usb_device *hdev = hub->hdev;
	काष्ठा usb_device *peer_hdev;
	काष्ठा usb_hub *peer_hub;

	/*
	 * If location data is available then we can only peer this port
	 * by a location match, not the शेष peer (lest we create a
	 * situation where we need to go back and unकरो a शेष peering
	 * when the port is later peered by location data)
	 */
	अगर (port_dev->location) अणु
		/* we link the peer in match_location() अगर found */
		usb_क्रम_each_dev(port_dev, match_location);
		वापस;
	पूर्ण अन्यथा अगर (!hdev->parent) अणु
		काष्ठा usb_hcd *hcd = bus_to_hcd(hdev->bus);
		काष्ठा usb_hcd *peer_hcd = hcd->shared_hcd;

		अगर (!peer_hcd)
			वापस;

		peer_hdev = peer_hcd->self.root_hub;
	पूर्ण अन्यथा अणु
		काष्ठा usb_port *upstream;
		काष्ठा usb_device *parent = hdev->parent;
		काष्ठा usb_hub *parent_hub = usb_hub_to_काष्ठा_hub(parent);

		अगर (!parent_hub)
			वापस;

		upstream = parent_hub->ports[hdev->portnum - 1];
		अगर (!upstream || !upstream->peer)
			वापस;

		peer_hdev = upstream->peer->child;
	पूर्ण

	peer_hub = usb_hub_to_काष्ठा_hub(peer_hdev);
	अगर (!peer_hub || port1 > peer_hdev->maxchild)
		वापस;

	/*
	 * we found a valid शेष peer, last check is to make sure it
	 * करोes not have location data
	 */
	peer = peer_hub->ports[port1 - 1];
	अगर (peer && peer->location == 0)
		link_peers_report(port_dev, peer);
पूर्ण

पूर्णांक usb_hub_create_port_device(काष्ठा usb_hub *hub, पूर्णांक port1)
अणु
	काष्ठा usb_port *port_dev;
	काष्ठा usb_device *hdev = hub->hdev;
	पूर्णांक retval;

	port_dev = kzalloc(माप(*port_dev), GFP_KERNEL);
	अगर (!port_dev)
		वापस -ENOMEM;

	port_dev->req = kzalloc(माप(*(port_dev->req)), GFP_KERNEL);
	अगर (!port_dev->req) अणु
		kमुक्त(port_dev);
		वापस -ENOMEM;
	पूर्ण

	hub->ports[port1 - 1] = port_dev;
	port_dev->portnum = port1;
	set_bit(port1, hub->घातer_bits);
	port_dev->dev.parent = hub->पूर्णांकfdev;
	अगर (hub_is_superspeed(hdev)) अणु
		port_dev->usb3_lpm_u1_permit = 1;
		port_dev->usb3_lpm_u2_permit = 1;
		port_dev->dev.groups = port_dev_usb3_group;
	पूर्ण अन्यथा
		port_dev->dev.groups = port_dev_group;
	port_dev->dev.type = &usb_port_device_type;
	port_dev->dev.driver = &usb_port_driver;
	अगर (hub_is_superspeed(hub->hdev))
		port_dev->is_superspeed = 1;
	dev_set_name(&port_dev->dev, "%s-port%d", dev_name(&hub->hdev->dev),
			port1);
	mutex_init(&port_dev->status_lock);
	retval = device_रेजिस्टर(&port_dev->dev);
	अगर (retval) अणु
		put_device(&port_dev->dev);
		वापस retval;
	पूर्ण

	/* Set शेष policy of port-घातeroff disabled. */
	retval = dev_pm_qos_add_request(&port_dev->dev, port_dev->req,
			DEV_PM_QOS_FLAGS, PM_QOS_FLAG_NO_POWER_OFF);
	अगर (retval < 0) अणु
		device_unरेजिस्टर(&port_dev->dev);
		वापस retval;
	पूर्ण

	find_and_link_peer(hub, port1);

	/*
	 * Enable runसमय pm and hold a refernce that hub_configure()
	 * will drop once the PM_QOS_NO_POWER_OFF flag state has been set
	 * and the hub has been fully रेजिस्टरed (hdev->maxchild set).
	 */
	pm_runसमय_set_active(&port_dev->dev);
	pm_runसमय_get_noresume(&port_dev->dev);
	pm_runसमय_enable(&port_dev->dev);
	device_enable_async_suspend(&port_dev->dev);

	/*
	 * Keep hidden the ability to enable port-घातeroff अगर the hub
	 * करोes not support घातer चयनing.
	 */
	अगर (!hub_is_port_घातer_चयनable(hub))
		वापस 0;

	/* Attempt to let userspace take over the policy. */
	retval = dev_pm_qos_expose_flags(&port_dev->dev,
			PM_QOS_FLAG_NO_POWER_OFF);
	अगर (retval < 0) अणु
		dev_warn(&port_dev->dev, "failed to expose pm_qos_no_poweroff\n");
		वापस 0;
	पूर्ण

	/* Userspace owns the policy, drop the kernel 'no_poweroff' request. */
	retval = dev_pm_qos_हटाओ_request(port_dev->req);
	अगर (retval >= 0) अणु
		kमुक्त(port_dev->req);
		port_dev->req = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

व्योम usb_hub_हटाओ_port_device(काष्ठा usb_hub *hub, पूर्णांक port1)
अणु
	काष्ठा usb_port *port_dev = hub->ports[port1 - 1];
	काष्ठा usb_port *peer;

	peer = port_dev->peer;
	अगर (peer)
		unlink_peers(port_dev, peer);
	device_unरेजिस्टर(&port_dev->dev);
पूर्ण
