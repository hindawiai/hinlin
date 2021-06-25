<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ulpi.c - USB ULPI PHY bus
 *
 * Copyright (C) 2015 Intel Corporation
 *
 * Author: Heikki Krogerus <heikki.krogerus@linux.पूर्णांकel.com>
 */

#समावेश <linux/ulpi/पूर्णांकerface.h>
#समावेश <linux/ulpi/driver.h>
#समावेश <linux/ulpi/regs.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/clk/clk-conf.h>

/* -------------------------------------------------------------------------- */

पूर्णांक ulpi_पढ़ो(काष्ठा ulpi *ulpi, u8 addr)
अणु
	वापस ulpi->ops->पढ़ो(ulpi->dev.parent, addr);
पूर्ण
EXPORT_SYMBOL_GPL(ulpi_पढ़ो);

पूर्णांक ulpi_ग_लिखो(काष्ठा ulpi *ulpi, u8 addr, u8 val)
अणु
	वापस ulpi->ops->ग_लिखो(ulpi->dev.parent, addr, val);
पूर्ण
EXPORT_SYMBOL_GPL(ulpi_ग_लिखो);

/* -------------------------------------------------------------------------- */

अटल पूर्णांक ulpi_match(काष्ठा device *dev, काष्ठा device_driver *driver)
अणु
	काष्ठा ulpi_driver *drv = to_ulpi_driver(driver);
	काष्ठा ulpi *ulpi = to_ulpi_dev(dev);
	स्थिर काष्ठा ulpi_device_id *id;

	/* Some ULPI devices करोn't have a venकरोr id so rely on OF match */
	अगर (ulpi->id.venकरोr == 0)
		वापस of_driver_match_device(dev, driver);

	क्रम (id = drv->id_table; id->venकरोr; id++)
		अगर (id->venकरोr == ulpi->id.venकरोr &&
		    id->product == ulpi->id.product)
			वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ulpi_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा ulpi *ulpi = to_ulpi_dev(dev);
	पूर्णांक ret;

	ret = of_device_uevent_modalias(dev, env);
	अगर (ret != -ENODEV)
		वापस ret;

	अगर (add_uevent_var(env, "MODALIAS=ulpi:v%04xp%04x",
			   ulpi->id.venकरोr, ulpi->id.product))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक ulpi_probe(काष्ठा device *dev)
अणु
	काष्ठा ulpi_driver *drv = to_ulpi_driver(dev->driver);
	पूर्णांक ret;

	ret = of_clk_set_शेषs(dev->of_node, false);
	अगर (ret < 0)
		वापस ret;

	वापस drv->probe(to_ulpi_dev(dev));
पूर्ण

अटल पूर्णांक ulpi_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा ulpi_driver *drv = to_ulpi_driver(dev->driver);

	अगर (drv->हटाओ)
		drv->हटाओ(to_ulpi_dev(dev));

	वापस 0;
पूर्ण

अटल काष्ठा bus_type ulpi_bus = अणु
	.name = "ulpi",
	.match = ulpi_match,
	.uevent = ulpi_uevent,
	.probe = ulpi_probe,
	.हटाओ = ulpi_हटाओ,
पूर्ण;

/* -------------------------------------------------------------------------- */

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	पूर्णांक len;
	काष्ठा ulpi *ulpi = to_ulpi_dev(dev);

	len = of_device_modalias(dev, buf, PAGE_SIZE);
	अगर (len != -ENODEV)
		वापस len;

	वापस प्र_लिखो(buf, "ulpi:v%04xp%04x\n",
		       ulpi->id.venकरोr, ulpi->id.product);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल काष्ठा attribute *ulpi_dev_attrs[] = अणु
	&dev_attr_modalias.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ulpi_dev_attr_group = अणु
	.attrs = ulpi_dev_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *ulpi_dev_attr_groups[] = अणु
	&ulpi_dev_attr_group,
	शून्य
पूर्ण;

अटल व्योम ulpi_dev_release(काष्ठा device *dev)
अणु
	kमुक्त(to_ulpi_dev(dev));
पूर्ण

अटल स्थिर काष्ठा device_type ulpi_dev_type = अणु
	.name = "ulpi_device",
	.groups = ulpi_dev_attr_groups,
	.release = ulpi_dev_release,
पूर्ण;

/* -------------------------------------------------------------------------- */

/**
 * ulpi_रेजिस्टर_driver - रेजिस्टर a driver with the ULPI bus
 * @drv: driver being रेजिस्टरed
 * @module: ends up being THIS_MODULE
 *
 * Registers a driver with the ULPI bus.
 */
पूर्णांक __ulpi_रेजिस्टर_driver(काष्ठा ulpi_driver *drv, काष्ठा module *module)
अणु
	अगर (!drv->probe)
		वापस -EINVAL;

	drv->driver.owner = module;
	drv->driver.bus = &ulpi_bus;

	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(__ulpi_रेजिस्टर_driver);

/**
 * ulpi_unरेजिस्टर_driver - unरेजिस्टर a driver with the ULPI bus
 * @drv: driver to unरेजिस्टर
 *
 * Unरेजिस्टरs a driver with the ULPI bus.
 */
व्योम ulpi_unरेजिस्टर_driver(काष्ठा ulpi_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(ulpi_unरेजिस्टर_driver);

/* -------------------------------------------------------------------------- */

अटल पूर्णांक ulpi_of_रेजिस्टर(काष्ठा ulpi *ulpi)
अणु
	काष्ठा device_node *np = शून्य, *child;
	काष्ठा device *parent;

	/* Find a ulpi bus underneath the parent or the gअक्रमparent */
	parent = ulpi->dev.parent;
	अगर (parent->of_node)
		np = of_get_child_by_name(parent->of_node, "ulpi");
	अन्यथा अगर (parent->parent && parent->parent->of_node)
		np = of_get_child_by_name(parent->parent->of_node, "ulpi");
	अगर (!np)
		वापस 0;

	child = of_get_next_available_child(np, शून्य);
	of_node_put(np);
	अगर (!child)
		वापस -EINVAL;

	ulpi->dev.of_node = child;

	वापस 0;
पूर्ण

अटल पूर्णांक ulpi_पढ़ो_id(काष्ठा ulpi *ulpi)
अणु
	पूर्णांक ret;

	/* Test the पूर्णांकerface */
	ret = ulpi_ग_लिखो(ulpi, ULPI_SCRATCH, 0xaa);
	अगर (ret < 0)
		जाओ err;

	ret = ulpi_पढ़ो(ulpi, ULPI_SCRATCH);
	अगर (ret < 0)
		वापस ret;

	अगर (ret != 0xaa)
		जाओ err;

	ulpi->id.venकरोr = ulpi_पढ़ो(ulpi, ULPI_VENDOR_ID_LOW);
	ulpi->id.venकरोr |= ulpi_पढ़ो(ulpi, ULPI_VENDOR_ID_HIGH) << 8;

	ulpi->id.product = ulpi_पढ़ो(ulpi, ULPI_PRODUCT_ID_LOW);
	ulpi->id.product |= ulpi_पढ़ो(ulpi, ULPI_PRODUCT_ID_HIGH) << 8;

	/* Some ULPI devices करोn't have a venकरोr id so rely on OF match */
	अगर (ulpi->id.venकरोr == 0)
		जाओ err;

	request_module("ulpi:v%04xp%04x", ulpi->id.venकरोr, ulpi->id.product);
	वापस 0;
err:
	of_device_request_module(&ulpi->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक ulpi_रेजिस्टर(काष्ठा device *dev, काष्ठा ulpi *ulpi)
अणु
	पूर्णांक ret;

	ulpi->dev.parent = dev; /* needed early क्रम ops */
	ulpi->dev.bus = &ulpi_bus;
	ulpi->dev.type = &ulpi_dev_type;
	dev_set_name(&ulpi->dev, "%s.ulpi", dev_name(dev));

	ACPI_COMPANION_SET(&ulpi->dev, ACPI_COMPANION(dev));

	ret = ulpi_of_रेजिस्टर(ulpi);
	अगर (ret)
		वापस ret;

	ret = ulpi_पढ़ो_id(ulpi);
	अगर (ret)
		वापस ret;

	ret = device_रेजिस्टर(&ulpi->dev);
	अगर (ret)
		वापस ret;

	dev_dbg(&ulpi->dev, "registered ULPI PHY: vendor %04x, product %04x\n",
		ulpi->id.venकरोr, ulpi->id.product);

	वापस 0;
पूर्ण

/**
 * ulpi_रेजिस्टर_पूर्णांकerface - instantiate new ULPI device
 * @dev: USB controller's device पूर्णांकerface
 * @ops: ULPI रेजिस्टर access
 *
 * Allocates and रेजिस्टरs a ULPI device and an पूर्णांकerface क्रम it. Called from
 * the USB controller that provides the ULPI पूर्णांकerface.
 */
काष्ठा ulpi *ulpi_रेजिस्टर_पूर्णांकerface(काष्ठा device *dev,
				     स्थिर काष्ठा ulpi_ops *ops)
अणु
	काष्ठा ulpi *ulpi;
	पूर्णांक ret;

	ulpi = kzalloc(माप(*ulpi), GFP_KERNEL);
	अगर (!ulpi)
		वापस ERR_PTR(-ENOMEM);

	ulpi->ops = ops;

	ret = ulpi_रेजिस्टर(dev, ulpi);
	अगर (ret) अणु
		kमुक्त(ulpi);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस ulpi;
पूर्ण
EXPORT_SYMBOL_GPL(ulpi_रेजिस्टर_पूर्णांकerface);

/**
 * ulpi_unरेजिस्टर_पूर्णांकerface - unरेजिस्टर ULPI पूर्णांकerface
 * @ulpi: काष्ठा ulpi_पूर्णांकerface
 *
 * Unरेजिस्टरs a ULPI device and it's पूर्णांकerface that was created with
 * ulpi_create_पूर्णांकerface().
 */
व्योम ulpi_unरेजिस्टर_पूर्णांकerface(काष्ठा ulpi *ulpi)
अणु
	of_node_put(ulpi->dev.of_node);
	device_unरेजिस्टर(&ulpi->dev);
पूर्ण
EXPORT_SYMBOL_GPL(ulpi_unरेजिस्टर_पूर्णांकerface);

/* -------------------------------------------------------------------------- */

अटल पूर्णांक __init ulpi_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&ulpi_bus);
पूर्ण
subsys_initcall(ulpi_init);

अटल व्योम __निकास ulpi_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&ulpi_bus);
पूर्ण
module_निकास(ulpi_निकास);

MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("USB ULPI PHY bus");
