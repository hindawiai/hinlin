<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB port LED trigger
 *
 * Copyright (C) 2016 Rafaध Miधecki <rafal@milecki.pl>
 */

#समावेश <linux/device.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/of.h>

काष्ठा usbport_trig_data अणु
	काष्ठा led_classdev *led_cdev;
	काष्ठा list_head ports;
	काष्ठा notअगरier_block nb;
	पूर्णांक count; /* Amount of connected matching devices */
पूर्ण;

काष्ठा usbport_trig_port अणु
	काष्ठा usbport_trig_data *data;
	काष्ठा usb_device *hub;
	पूर्णांक portnum;
	अक्षर *port_name;
	bool observed;
	काष्ठा device_attribute attr;
	काष्ठा list_head list;
पूर्ण;

/***************************************
 * Helpers
 ***************************************/

/*
 * usbport_trig_usb_dev_observed - Check अगर dev is connected to observed port
 */
अटल bool usbport_trig_usb_dev_observed(काष्ठा usbport_trig_data *usbport_data,
					  काष्ठा usb_device *usb_dev)
अणु
	काष्ठा usbport_trig_port *port;

	अगर (!usb_dev->parent)
		वापस false;

	list_क्रम_each_entry(port, &usbport_data->ports, list) अणु
		अगर (usb_dev->parent == port->hub &&
		    usb_dev->portnum == port->portnum)
			वापस port->observed;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक usbport_trig_usb_dev_check(काष्ठा usb_device *usb_dev, व्योम *data)
अणु
	काष्ठा usbport_trig_data *usbport_data = data;

	अगर (usbport_trig_usb_dev_observed(usbport_data, usb_dev))
		usbport_data->count++;

	वापस 0;
पूर्ण

/*
 * usbport_trig_update_count - Recalculate amount of connected matching devices
 */
अटल व्योम usbport_trig_update_count(काष्ठा usbport_trig_data *usbport_data)
अणु
	काष्ठा led_classdev *led_cdev = usbport_data->led_cdev;

	usbport_data->count = 0;
	usb_क्रम_each_dev(usbport_data, usbport_trig_usb_dev_check);
	led_set_brightness(led_cdev, usbport_data->count ? LED_FULL : LED_OFF);
पूर्ण

/***************************************
 * Device attr
 ***************************************/

अटल sमाप_प्रकार usbport_trig_port_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usbport_trig_port *port = container_of(attr,
						      काष्ठा usbport_trig_port,
						      attr);

	वापस प्र_लिखो(buf, "%d\n", port->observed) + 1;
पूर्ण

अटल sमाप_प्रकार usbport_trig_port_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा usbport_trig_port *port = container_of(attr,
						      काष्ठा usbport_trig_port,
						      attr);

	अगर (!म_भेद(buf, "0") || !म_भेद(buf, "0\n"))
		port->observed = 0;
	अन्यथा अगर (!म_भेद(buf, "1") || !म_भेद(buf, "1\n"))
		port->observed = 1;
	अन्यथा
		वापस -EINVAL;

	usbport_trig_update_count(port->data);

	वापस size;
पूर्ण

अटल काष्ठा attribute *ports_attrs[] = अणु
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ports_group = अणु
	.name = "ports",
	.attrs = ports_attrs,
पूर्ण;

/***************************************
 * Adding & removing ports
 ***************************************/

/*
 * usbport_trig_port_observed - Check अगर port should be observed
 */
अटल bool usbport_trig_port_observed(काष्ठा usbport_trig_data *usbport_data,
				       काष्ठा usb_device *usb_dev, पूर्णांक port1)
अणु
	काष्ठा device *dev = usbport_data->led_cdev->dev;
	काष्ठा device_node *led_np = dev->of_node;
	काष्ठा of_phandle_args args;
	काष्ठा device_node *port_np;
	पूर्णांक count, i;

	अगर (!led_np)
		वापस false;

	/*
	 * Get node of port being added
	 *
	 * FIXME: This is really the device node of the connected device
	 */
	port_np = usb_of_get_device_node(usb_dev, port1);
	अगर (!port_np)
		वापस false;

	of_node_put(port_np);

	/* Amount of trigger sources क्रम this LED */
	count = of_count_phandle_with_args(led_np, "trigger-sources",
					   "#trigger-source-cells");
	अगर (count < 0) अणु
		dev_warn(dev, "Failed to get trigger sources for %pOF\n",
			 led_np);
		वापस false;
	पूर्ण

	/* Check list of sources क्रम this specअगरic port */
	क्रम (i = 0; i < count; i++) अणु
		पूर्णांक err;

		err = of_parse_phandle_with_args(led_np, "trigger-sources",
						 "#trigger-source-cells", i,
						 &args);
		अगर (err) अणु
			dev_err(dev, "Failed to get trigger source phandle at index %d: %d\n",
				i, err);
			जारी;
		पूर्ण

		of_node_put(args.np);

		अगर (args.np == port_np)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक usbport_trig_add_port(काष्ठा usbport_trig_data *usbport_data,
				 काष्ठा usb_device *usb_dev,
				 स्थिर अक्षर *hub_name, पूर्णांक portnum)
अणु
	काष्ठा led_classdev *led_cdev = usbport_data->led_cdev;
	काष्ठा usbport_trig_port *port;
	माप_प्रकार len;
	पूर्णांक err;

	port = kzalloc(माप(*port), GFP_KERNEL);
	अगर (!port) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	port->data = usbport_data;
	port->hub = usb_dev;
	port->portnum = portnum;
	port->observed = usbport_trig_port_observed(usbport_data, usb_dev,
						    portnum);

	len = म_माप(hub_name) + 8;
	port->port_name = kzalloc(len, GFP_KERNEL);
	अगर (!port->port_name) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_port;
	पूर्ण
	snम_लिखो(port->port_name, len, "%s-port%d", hub_name, portnum);

	sysfs_attr_init(&port->attr.attr);
	port->attr.attr.name = port->port_name;
	port->attr.attr.mode = S_IRUSR | S_IWUSR;
	port->attr.show = usbport_trig_port_show;
	port->attr.store = usbport_trig_port_store;

	err = sysfs_add_file_to_group(&led_cdev->dev->kobj, &port->attr.attr,
				      ports_group.name);
	अगर (err)
		जाओ err_मुक्त_port_name;

	list_add_tail(&port->list, &usbport_data->ports);

	वापस 0;

err_मुक्त_port_name:
	kमुक्त(port->port_name);
err_मुक्त_port:
	kमुक्त(port);
err_out:
	वापस err;
पूर्ण

अटल पूर्णांक usbport_trig_add_usb_dev_ports(काष्ठा usb_device *usb_dev,
					  व्योम *data)
अणु
	काष्ठा usbport_trig_data *usbport_data = data;
	पूर्णांक i;

	क्रम (i = 1; i <= usb_dev->maxchild; i++)
		usbport_trig_add_port(usbport_data, usb_dev,
				      dev_name(&usb_dev->dev), i);

	वापस 0;
पूर्ण

अटल व्योम usbport_trig_हटाओ_port(काष्ठा usbport_trig_data *usbport_data,
				     काष्ठा usbport_trig_port *port)
अणु
	काष्ठा led_classdev *led_cdev = usbport_data->led_cdev;

	list_del(&port->list);
	sysfs_हटाओ_file_from_group(&led_cdev->dev->kobj, &port->attr.attr,
				     ports_group.name);
	kमुक्त(port->port_name);
	kमुक्त(port);
पूर्ण

अटल व्योम usbport_trig_हटाओ_usb_dev_ports(काष्ठा usbport_trig_data *usbport_data,
					      काष्ठा usb_device *usb_dev)
अणु
	काष्ठा usbport_trig_port *port, *पंचांगp;

	list_क्रम_each_entry_safe(port, पंचांगp, &usbport_data->ports, list) अणु
		अगर (port->hub == usb_dev)
			usbport_trig_हटाओ_port(usbport_data, port);
	पूर्ण
पूर्ण

/***************************************
 * Init, निकास, etc.
 ***************************************/

अटल पूर्णांक usbport_trig_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
			       व्योम *data)
अणु
	काष्ठा usbport_trig_data *usbport_data =
		container_of(nb, काष्ठा usbport_trig_data, nb);
	काष्ठा led_classdev *led_cdev = usbport_data->led_cdev;
	काष्ठा usb_device *usb_dev = data;
	bool observed;

	observed = usbport_trig_usb_dev_observed(usbport_data, usb_dev);

	चयन (action) अणु
	हाल USB_DEVICE_ADD:
		usbport_trig_add_usb_dev_ports(usb_dev, usbport_data);
		अगर (observed && usbport_data->count++ == 0)
			led_set_brightness(led_cdev, LED_FULL);
		वापस NOTIFY_OK;
	हाल USB_DEVICE_REMOVE:
		usbport_trig_हटाओ_usb_dev_ports(usbport_data, usb_dev);
		अगर (observed && --usbport_data->count == 0)
			led_set_brightness(led_cdev, LED_OFF);
		वापस NOTIFY_OK;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक usbport_trig_activate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा usbport_trig_data *usbport_data;
	पूर्णांक err;

	usbport_data = kzalloc(माप(*usbport_data), GFP_KERNEL);
	अगर (!usbport_data)
		वापस -ENOMEM;
	usbport_data->led_cdev = led_cdev;

	/* List of ports */
	INIT_LIST_HEAD(&usbport_data->ports);
	err = sysfs_create_group(&led_cdev->dev->kobj, &ports_group);
	अगर (err)
		जाओ err_मुक्त;
	usb_क्रम_each_dev(usbport_data, usbport_trig_add_usb_dev_ports);
	usbport_trig_update_count(usbport_data);

	/* Notअगरications */
	usbport_data->nb.notअगरier_call = usbport_trig_notअगरy;
	led_set_trigger_data(led_cdev, usbport_data);
	usb_रेजिस्टर_notअगरy(&usbport_data->nb);
	वापस 0;

err_मुक्त:
	kमुक्त(usbport_data);
	वापस err;
पूर्ण

अटल व्योम usbport_trig_deactivate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा usbport_trig_data *usbport_data = led_get_trigger_data(led_cdev);
	काष्ठा usbport_trig_port *port, *पंचांगp;

	list_क्रम_each_entry_safe(port, पंचांगp, &usbport_data->ports, list) अणु
		usbport_trig_हटाओ_port(usbport_data, port);
	पूर्ण

	sysfs_हटाओ_group(&led_cdev->dev->kobj, &ports_group);

	usb_unरेजिस्टर_notअगरy(&usbport_data->nb);

	kमुक्त(usbport_data);
पूर्ण

अटल काष्ठा led_trigger usbport_led_trigger = अणु
	.name     = "usbport",
	.activate = usbport_trig_activate,
	.deactivate = usbport_trig_deactivate,
पूर्ण;

अटल पूर्णांक __init usbport_trig_init(व्योम)
अणु
	वापस led_trigger_रेजिस्टर(&usbport_led_trigger);
पूर्ण

अटल व्योम __निकास usbport_trig_निकास(व्योम)
अणु
	led_trigger_unरेजिस्टर(&usbport_led_trigger);
पूर्ण

module_init(usbport_trig_init);
module_निकास(usbport_trig_निकास);

MODULE_AUTHOR("Rafaध Miधecki <rafal@milecki.pl>");
MODULE_DESCRIPTION("USB port trigger");
MODULE_LICENSE("GPL v2");
