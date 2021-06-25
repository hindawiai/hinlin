<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Framework क्रम MDIO devices, other than PHYs.
 *
 * Copyright (c) 2016 Andrew Lunn <andrew@lunn.ch>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/mii.h>
#समावेश <linux/module.h>
#समावेश <linux/phy.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/unistd.h>

व्योम mdio_device_मुक्त(काष्ठा mdio_device *mdiodev)
अणु
	put_device(&mdiodev->dev);
पूर्ण
EXPORT_SYMBOL(mdio_device_मुक्त);

अटल व्योम mdio_device_release(काष्ठा device *dev)
अणु
	kमुक्त(to_mdio_device(dev));
पूर्ण

पूर्णांक mdio_device_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा mdio_device *mdiodev = to_mdio_device(dev);
	काष्ठा mdio_driver *mdiodrv = to_mdio_driver(drv);

	अगर (mdiodrv->mdiodrv.flags & MDIO_DEVICE_IS_PHY)
		वापस 0;

	वापस म_भेद(mdiodev->modalias, drv->name) == 0;
पूर्ण

काष्ठा mdio_device *mdio_device_create(काष्ठा mii_bus *bus, पूर्णांक addr)
अणु
	काष्ठा mdio_device *mdiodev;

	/* We allocate the device, and initialize the शेष values */
	mdiodev = kzalloc(माप(*mdiodev), GFP_KERNEL);
	अगर (!mdiodev)
		वापस ERR_PTR(-ENOMEM);

	mdiodev->dev.release = mdio_device_release;
	mdiodev->dev.parent = &bus->dev;
	mdiodev->dev.bus = &mdio_bus_type;
	mdiodev->device_मुक्त = mdio_device_मुक्त;
	mdiodev->device_हटाओ = mdio_device_हटाओ;
	mdiodev->bus = bus;
	mdiodev->addr = addr;

	dev_set_name(&mdiodev->dev, PHY_ID_FMT, bus->id, addr);

	device_initialize(&mdiodev->dev);

	वापस mdiodev;
पूर्ण
EXPORT_SYMBOL(mdio_device_create);

/**
 * mdio_device_रेजिस्टर - Register the mdio device on the MDIO bus
 * @mdiodev: mdio_device काष्ठाure to be added to the MDIO bus
 */
पूर्णांक mdio_device_रेजिस्टर(काष्ठा mdio_device *mdiodev)
अणु
	पूर्णांक err;

	dev_dbg(&mdiodev->dev, "mdio_device_register\n");

	err = mdiobus_रेजिस्टर_device(mdiodev);
	अगर (err)
		वापस err;

	err = device_add(&mdiodev->dev);
	अगर (err) अणु
		pr_err("MDIO %d failed to add\n", mdiodev->addr);
		जाओ out;
	पूर्ण

	वापस 0;

 out:
	mdiobus_unरेजिस्टर_device(mdiodev);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mdio_device_रेजिस्टर);

/**
 * mdio_device_हटाओ - Remove a previously रेजिस्टरed mdio device from the
 *			MDIO bus
 * @mdiodev: mdio_device काष्ठाure to हटाओ
 *
 * This करोesn't मुक्त the mdio_device itself, it merely reverses the effects
 * of mdio_device_रेजिस्टर(). Use mdio_device_मुक्त() to मुक्त the device
 * after calling this function.
 */
व्योम mdio_device_हटाओ(काष्ठा mdio_device *mdiodev)
अणु
	device_del(&mdiodev->dev);
	mdiobus_unरेजिस्टर_device(mdiodev);
पूर्ण
EXPORT_SYMBOL(mdio_device_हटाओ);

व्योम mdio_device_reset(काष्ठा mdio_device *mdiodev, पूर्णांक value)
अणु
	अचिन्हित पूर्णांक d;

	अगर (!mdiodev->reset_gpio && !mdiodev->reset_ctrl)
		वापस;

	अगर (mdiodev->reset_gpio)
		gpiod_set_value_cansleep(mdiodev->reset_gpio, value);

	अगर (mdiodev->reset_ctrl) अणु
		अगर (value)
			reset_control_निश्चित(mdiodev->reset_ctrl);
		अन्यथा
			reset_control_deनिश्चित(mdiodev->reset_ctrl);
	पूर्ण

	d = value ? mdiodev->reset_निश्चित_delay : mdiodev->reset_deनिश्चित_delay;
	अगर (d)
		fsleep(d);
पूर्ण
EXPORT_SYMBOL(mdio_device_reset);

/**
 * mdio_probe - probe an MDIO device
 * @dev: device to probe
 *
 * Description: Take care of setting up the mdio_device काष्ठाure
 * and calling the driver to probe the device.
 */
अटल पूर्णांक mdio_probe(काष्ठा device *dev)
अणु
	काष्ठा mdio_device *mdiodev = to_mdio_device(dev);
	काष्ठा device_driver *drv = mdiodev->dev.driver;
	काष्ठा mdio_driver *mdiodrv = to_mdio_driver(drv);
	पूर्णांक err = 0;

	/* Deनिश्चित the reset संकेत */
	mdio_device_reset(mdiodev, 0);

	अगर (mdiodrv->probe) अणु
		err = mdiodrv->probe(mdiodev);
		अगर (err) अणु
			/* Assert the reset संकेत */
			mdio_device_reset(mdiodev, 1);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mdio_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा mdio_device *mdiodev = to_mdio_device(dev);
	काष्ठा device_driver *drv = mdiodev->dev.driver;
	काष्ठा mdio_driver *mdiodrv = to_mdio_driver(drv);

	अगर (mdiodrv->हटाओ)
		mdiodrv->हटाओ(mdiodev);

	/* Assert the reset संकेत */
	mdio_device_reset(mdiodev, 1);

	वापस 0;
पूर्ण

/**
 * mdio_driver_रेजिस्टर - रेजिस्टर an mdio_driver with the MDIO layer
 * @drv: new mdio_driver to रेजिस्टर
 */
पूर्णांक mdio_driver_रेजिस्टर(काष्ठा mdio_driver *drv)
अणु
	काष्ठा mdio_driver_common *mdiodrv = &drv->mdiodrv;
	पूर्णांक retval;

	pr_debug("mdio_driver_register: %s\n", mdiodrv->driver.name);

	mdiodrv->driver.bus = &mdio_bus_type;
	mdiodrv->driver.probe = mdio_probe;
	mdiodrv->driver.हटाओ = mdio_हटाओ;

	retval = driver_रेजिस्टर(&mdiodrv->driver);
	अगर (retval) अणु
		pr_err("%s: Error %d in registering driver\n",
		       mdiodrv->driver.name, retval);

		वापस retval;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mdio_driver_रेजिस्टर);

व्योम mdio_driver_unरेजिस्टर(काष्ठा mdio_driver *drv)
अणु
	काष्ठा mdio_driver_common *mdiodrv = &drv->mdiodrv;

	driver_unरेजिस्टर(&mdiodrv->driver);
पूर्ण
EXPORT_SYMBOL(mdio_driver_unरेजिस्टर);
