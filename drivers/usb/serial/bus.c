<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB Serial Converter Bus specअगरic functions
 *
 * Copyright (C) 2002 Greg Kroah-Harपंचांगan (greg@kroah.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/tty.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/serial.h>

अटल पूर्णांक usb_serial_device_match(काष्ठा device *dev,
						काष्ठा device_driver *drv)
अणु
	स्थिर काष्ठा usb_serial_port *port = to_usb_serial_port(dev);
	काष्ठा usb_serial_driver *driver = to_usb_serial_driver(drv);

	/*
	 * drivers are alपढ़ोy asचिन्हित to ports in serial_probe so it's
	 * a simple check here.
	 */
	अगर (driver == port->serial->type)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक usb_serial_device_probe(काष्ठा device *dev)
अणु
	काष्ठा usb_serial_port *port = to_usb_serial_port(dev);
	काष्ठा usb_serial_driver *driver;
	काष्ठा device *tty_dev;
	पूर्णांक retval = 0;
	पूर्णांक minor;

	/* make sure suspend/resume करोesn't race against port_probe */
	retval = usb_स्वतःpm_get_पूर्णांकerface(port->serial->पूर्णांकerface);
	अगर (retval)
		वापस retval;

	driver = port->serial->type;
	अगर (driver->port_probe) अणु
		retval = driver->port_probe(port);
		अगर (retval)
			जाओ err_स्वतःpm_put;
	पूर्ण

	minor = port->minor;
	tty_dev = tty_port_रेजिस्टर_device(&port->port, usb_serial_tty_driver,
					   minor, dev);
	अगर (IS_ERR(tty_dev)) अणु
		retval = PTR_ERR(tty_dev);
		जाओ err_port_हटाओ;
	पूर्ण

	usb_स्वतःpm_put_पूर्णांकerface(port->serial->पूर्णांकerface);

	dev_info(&port->serial->dev->dev,
		 "%s converter now attached to ttyUSB%d\n",
		 driver->description, minor);

	वापस 0;

err_port_हटाओ:
	अगर (driver->port_हटाओ)
		driver->port_हटाओ(port);
err_स्वतःpm_put:
	usb_स्वतःpm_put_पूर्णांकerface(port->serial->पूर्णांकerface);

	वापस retval;
पूर्ण

अटल पूर्णांक usb_serial_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा usb_serial_port *port = to_usb_serial_port(dev);
	काष्ठा usb_serial_driver *driver;
	पूर्णांक minor;
	पूर्णांक स्वतःpm_err;

	/*
	 * Make sure suspend/resume करोesn't race against port_हटाओ.
	 *
	 * Note that no further runसमय PM callbacks will be made अगर
	 * स्वतःpm_get fails.
	 */
	स्वतःpm_err = usb_स्वतःpm_get_पूर्णांकerface(port->serial->पूर्णांकerface);

	minor = port->minor;
	tty_unरेजिस्टर_device(usb_serial_tty_driver, minor);

	driver = port->serial->type;
	अगर (driver->port_हटाओ)
		driver->port_हटाओ(port);

	dev_info(dev, "%s converter now disconnected from ttyUSB%d\n",
		 driver->description, minor);

	अगर (!स्वतःpm_err)
		usb_स्वतःpm_put_पूर्णांकerface(port->serial->पूर्णांकerface);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार new_id_store(काष्ठा device_driver *driver,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_serial_driver *usb_drv = to_usb_serial_driver(driver);
	sमाप_प्रकार retval = usb_store_new_id(&usb_drv->dynids, usb_drv->id_table,
					 driver, buf, count);

	अगर (retval >= 0 && usb_drv->usb_driver != शून्य)
		retval = usb_store_new_id(&usb_drv->usb_driver->dynids,
					  usb_drv->usb_driver->id_table,
					  &usb_drv->usb_driver->drvwrap.driver,
					  buf, count);
	वापस retval;
पूर्ण

अटल sमाप_प्रकार new_id_show(काष्ठा device_driver *driver, अक्षर *buf)
अणु
	काष्ठा usb_serial_driver *usb_drv = to_usb_serial_driver(driver);

	वापस usb_show_dynids(&usb_drv->dynids, buf);
पूर्ण
अटल DRIVER_ATTR_RW(new_id);

अटल काष्ठा attribute *usb_serial_drv_attrs[] = अणु
	&driver_attr_new_id.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(usb_serial_drv);

अटल व्योम मुक्त_dynids(काष्ठा usb_serial_driver *drv)
अणु
	काष्ठा usb_dynid *dynid, *n;

	spin_lock(&drv->dynids.lock);
	list_क्रम_each_entry_safe(dynid, n, &drv->dynids.list, node) अणु
		list_del(&dynid->node);
		kमुक्त(dynid);
	पूर्ण
	spin_unlock(&drv->dynids.lock);
पूर्ण

काष्ठा bus_type usb_serial_bus_type = अणु
	.name =		"usb-serial",
	.match =	usb_serial_device_match,
	.probe =	usb_serial_device_probe,
	.हटाओ =	usb_serial_device_हटाओ,
	.drv_groups = 	usb_serial_drv_groups,
पूर्ण;

पूर्णांक usb_serial_bus_रेजिस्टर(काष्ठा usb_serial_driver *driver)
अणु
	पूर्णांक retval;

	driver->driver.bus = &usb_serial_bus_type;
	spin_lock_init(&driver->dynids.lock);
	INIT_LIST_HEAD(&driver->dynids.list);

	retval = driver_रेजिस्टर(&driver->driver);

	वापस retval;
पूर्ण

व्योम usb_serial_bus_deरेजिस्टर(काष्ठा usb_serial_driver *driver)
अणु
	मुक्त_dynids(driver);
	driver_unरेजिस्टर(&driver->driver);
पूर्ण

