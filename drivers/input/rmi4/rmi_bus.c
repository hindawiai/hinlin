<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011-2016 Synaptics Incorporated
 * Copyright (c) 2011 Unixphere
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/list.h>
#समावेश <linux/pm.h>
#समावेश <linux/rmi.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/of.h>
#समावेश "rmi_bus.h"
#समावेश "rmi_driver.h"

अटल पूर्णांक debug_flags;
module_param(debug_flags, पूर्णांक, 0644);
MODULE_PARM_DESC(debug_flags, "control debugging information");

व्योम rmi_dbg(पूर्णांक flags, काष्ठा device *dev, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (flags & debug_flags) अणु
		बहु_शुरू(args, fmt);

		vaf.fmt = fmt;
		vaf.va = &args;

		dev_prपूर्णांकk(KERN_DEBUG, dev, "%pV", &vaf);

		बहु_पूर्ण(args);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rmi_dbg);

/*
 * RMI Physical devices
 *
 * Physical RMI device consists of several functions serving particular
 * purpose. For example F11 is a 2D touch sensor जबतक F01 is a generic
 * function present in every RMI device.
 */

अटल व्योम rmi_release_device(काष्ठा device *dev)
अणु
	काष्ठा rmi_device *rmi_dev = to_rmi_device(dev);

	kमुक्त(rmi_dev);
पूर्ण

अटल स्थिर काष्ठा device_type rmi_device_type = अणु
	.name		= "rmi4_sensor",
	.release	= rmi_release_device,
पूर्ण;

bool rmi_is_physical_device(काष्ठा device *dev)
अणु
	वापस dev->type == &rmi_device_type;
पूर्ण

/**
 * rmi_रेजिस्टर_transport_device - रेजिस्टर a transport device connection
 * on the RMI bus.  Transport drivers provide communication from the devices
 * on a bus (such as SPI, I2C, and so on) to the RMI4 sensor.
 *
 * @xport: the transport device to रेजिस्टर
 */
पूर्णांक rmi_रेजिस्टर_transport_device(काष्ठा rmi_transport_dev *xport)
अणु
	अटल atomic_t transport_device_count = ATOMIC_INIT(0);
	काष्ठा rmi_device *rmi_dev;
	पूर्णांक error;

	rmi_dev = kzalloc(माप(काष्ठा rmi_device), GFP_KERNEL);
	अगर (!rmi_dev)
		वापस -ENOMEM;

	device_initialize(&rmi_dev->dev);

	rmi_dev->xport = xport;
	rmi_dev->number = atomic_inc_वापस(&transport_device_count) - 1;

	dev_set_name(&rmi_dev->dev, "rmi4-%02d", rmi_dev->number);

	rmi_dev->dev.bus = &rmi_bus_type;
	rmi_dev->dev.type = &rmi_device_type;

	xport->rmi_dev = rmi_dev;

	error = device_add(&rmi_dev->dev);
	अगर (error)
		जाओ err_put_device;

	rmi_dbg(RMI_DEBUG_CORE, xport->dev,
		"%s: Registered %s as %s.\n", __func__,
		dev_name(rmi_dev->xport->dev), dev_name(&rmi_dev->dev));

	वापस 0;

err_put_device:
	put_device(&rmi_dev->dev);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(rmi_रेजिस्टर_transport_device);

/**
 * rmi_unरेजिस्टर_transport_device - unरेजिस्टर a transport device connection
 * @xport: the transport driver to unरेजिस्टर
 *
 */
व्योम rmi_unरेजिस्टर_transport_device(काष्ठा rmi_transport_dev *xport)
अणु
	काष्ठा rmi_device *rmi_dev = xport->rmi_dev;

	device_del(&rmi_dev->dev);
	put_device(&rmi_dev->dev);
पूर्ण
EXPORT_SYMBOL(rmi_unरेजिस्टर_transport_device);


/* Function specअगरic stuff */

अटल व्योम rmi_release_function(काष्ठा device *dev)
अणु
	काष्ठा rmi_function *fn = to_rmi_function(dev);

	kमुक्त(fn);
पूर्ण

अटल स्थिर काष्ठा device_type rmi_function_type = अणु
	.name		= "rmi4_function",
	.release	= rmi_release_function,
पूर्ण;

bool rmi_is_function_device(काष्ठा device *dev)
अणु
	वापस dev->type == &rmi_function_type;
पूर्ण

अटल पूर्णांक rmi_function_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा rmi_function_handler *handler = to_rmi_function_handler(drv);
	काष्ठा rmi_function *fn = to_rmi_function(dev);

	वापस fn->fd.function_number == handler->func;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल व्योम rmi_function_of_probe(काष्ठा rmi_function *fn)
अणु
	अक्षर of_name[9];
	काष्ठा device_node *node = fn->rmi_dev->xport->dev->of_node;

	snम_लिखो(of_name, माप(of_name), "rmi4-f%02x",
		fn->fd.function_number);
	fn->dev.of_node = of_get_child_by_name(node, of_name);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम rmi_function_of_probe(काष्ठा rmi_function *fn)
अणुपूर्ण
#पूर्ण_अगर

अटल काष्ठा irq_chip rmi_irq_chip = अणु
	.name = "rmi4",
पूर्ण;

अटल पूर्णांक rmi_create_function_irq(काष्ठा rmi_function *fn,
				   काष्ठा rmi_function_handler *handler)
अणु
	काष्ठा rmi_driver_data *drvdata = dev_get_drvdata(&fn->rmi_dev->dev);
	पूर्णांक i, error;

	क्रम (i = 0; i < fn->num_of_irqs; i++) अणु
		set_bit(fn->irq_pos + i, fn->irq_mask);

		fn->irq[i] = irq_create_mapping(drvdata->irqकरोमुख्य,
						fn->irq_pos + i);

		irq_set_chip_data(fn->irq[i], fn);
		irq_set_chip_and_handler(fn->irq[i], &rmi_irq_chip,
					 handle_simple_irq);
		irq_set_nested_thपढ़ो(fn->irq[i], 1);

		error = devm_request_thपढ़ोed_irq(&fn->dev, fn->irq[i], शून्य,
					handler->attention, IRQF_ONESHOT,
					dev_name(&fn->dev), fn);
		अगर (error) अणु
			dev_err(&fn->dev, "Error %d registering IRQ\n", error);
			वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_function_probe(काष्ठा device *dev)
अणु
	काष्ठा rmi_function *fn = to_rmi_function(dev);
	काष्ठा rmi_function_handler *handler =
					to_rmi_function_handler(dev->driver);
	पूर्णांक error;

	rmi_function_of_probe(fn);

	अगर (handler->probe) अणु
		error = handler->probe(fn);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (fn->num_of_irqs && handler->attention) अणु
		error = rmi_create_function_irq(fn, handler);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rmi_function_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा rmi_function *fn = to_rmi_function(dev);
	काष्ठा rmi_function_handler *handler =
					to_rmi_function_handler(dev->driver);

	अगर (handler->हटाओ)
		handler->हटाओ(fn);

	वापस 0;
पूर्ण

पूर्णांक rmi_रेजिस्टर_function(काष्ठा rmi_function *fn)
अणु
	काष्ठा rmi_device *rmi_dev = fn->rmi_dev;
	पूर्णांक error;

	device_initialize(&fn->dev);

	dev_set_name(&fn->dev, "%s.fn%02x",
		     dev_name(&rmi_dev->dev), fn->fd.function_number);

	fn->dev.parent = &rmi_dev->dev;
	fn->dev.type = &rmi_function_type;
	fn->dev.bus = &rmi_bus_type;

	error = device_add(&fn->dev);
	अगर (error) अणु
		dev_err(&rmi_dev->dev,
			"Failed device_register function device %s\n",
			dev_name(&fn->dev));
		जाओ err_put_device;
	पूर्ण

	rmi_dbg(RMI_DEBUG_CORE, &rmi_dev->dev, "Registered F%02X.\n",
			fn->fd.function_number);

	वापस 0;

err_put_device:
	put_device(&fn->dev);
	वापस error;
पूर्ण

व्योम rmi_unरेजिस्टर_function(काष्ठा rmi_function *fn)
अणु
	पूर्णांक i;

	rmi_dbg(RMI_DEBUG_CORE, &fn->dev, "Unregistering F%02X.\n",
			fn->fd.function_number);

	device_del(&fn->dev);
	of_node_put(fn->dev.of_node);
	put_device(&fn->dev);

	क्रम (i = 0; i < fn->num_of_irqs; i++)
		irq_dispose_mapping(fn->irq[i]);

पूर्ण

/**
 * rmi_रेजिस्टर_function_handler - रेजिस्टर a handler क्रम an RMI function
 * @handler: RMI handler that should be रेजिस्टरed.
 * @owner: poपूर्णांकer to module that implements the handler
 * @mod_name: name of the module implementing the handler
 *
 * This function perक्रमms additional setup of RMI function handler and
 * रेजिस्टरs it with the RMI core so that it can be bound to
 * RMI function devices.
 */
पूर्णांक __rmi_रेजिस्टर_function_handler(काष्ठा rmi_function_handler *handler,
				     काष्ठा module *owner,
				     स्थिर अक्षर *mod_name)
अणु
	काष्ठा device_driver *driver = &handler->driver;
	पूर्णांक error;

	driver->bus = &rmi_bus_type;
	driver->owner = owner;
	driver->mod_name = mod_name;
	driver->probe = rmi_function_probe;
	driver->हटाओ = rmi_function_हटाओ;

	error = driver_रेजिस्टर(driver);
	अगर (error) अणु
		pr_err("driver_register() failed for %s, error: %d\n",
			driver->name, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__rmi_रेजिस्टर_function_handler);

/**
 * rmi_unरेजिस्टर_function_handler - unरेजिस्टर given RMI function handler
 * @handler: RMI handler that should be unरेजिस्टरed.
 *
 * This function unरेजिस्टरs given function handler from RMI core which
 * causes it to be unbound from the function devices.
 */
व्योम rmi_unरेजिस्टर_function_handler(काष्ठा rmi_function_handler *handler)
अणु
	driver_unरेजिस्टर(&handler->driver);
पूर्ण
EXPORT_SYMBOL_GPL(rmi_unरेजिस्टर_function_handler);

/* Bus specअगरic stuff */

अटल पूर्णांक rmi_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	bool physical = rmi_is_physical_device(dev);

	/* First see अगर types are not compatible */
	अगर (physical != rmi_is_physical_driver(drv))
		वापस 0;

	वापस physical || rmi_function_match(dev, drv);
पूर्ण

काष्ठा bus_type rmi_bus_type = अणु
	.match		= rmi_bus_match,
	.name		= "rmi4",
पूर्ण;

अटल काष्ठा rmi_function_handler *fn_handlers[] = अणु
	&rmi_f01_handler,
#अगर_घोषित CONFIG_RMI4_F03
	&rmi_f03_handler,
#पूर्ण_अगर
#अगर_घोषित CONFIG_RMI4_F11
	&rmi_f11_handler,
#पूर्ण_अगर
#अगर_घोषित CONFIG_RMI4_F12
	&rmi_f12_handler,
#पूर्ण_अगर
#अगर_घोषित CONFIG_RMI4_F30
	&rmi_f30_handler,
#पूर्ण_अगर
#अगर_घोषित CONFIG_RMI4_F34
	&rmi_f34_handler,
#पूर्ण_अगर
#अगर_घोषित CONFIG_RMI4_F3A
	&rmi_f3a_handler,
#पूर्ण_अगर
#अगर_घोषित CONFIG_RMI4_F54
	&rmi_f54_handler,
#पूर्ण_अगर
#अगर_घोषित CONFIG_RMI4_F55
	&rmi_f55_handler,
#पूर्ण_अगर
पूर्ण;

अटल व्योम __rmi_unरेजिस्टर_function_handlers(पूर्णांक start_idx)
अणु
	पूर्णांक i;

	क्रम (i = start_idx; i >= 0; i--)
		rmi_unरेजिस्टर_function_handler(fn_handlers[i]);
पूर्ण

अटल व्योम rmi_unरेजिस्टर_function_handlers(व्योम)
अणु
	__rmi_unरेजिस्टर_function_handlers(ARRAY_SIZE(fn_handlers) - 1);
पूर्ण

अटल पूर्णांक rmi_रेजिस्टर_function_handlers(व्योम)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fn_handlers); i++)	अणु
		ret = rmi_रेजिस्टर_function_handler(fn_handlers[i]);
		अगर (ret) अणु
			pr_err("%s: error registering the RMI F%02x handler: %d\n",
				__func__, fn_handlers[i]->func, ret);
			जाओ err_unरेजिस्टर_function_handlers;
		पूर्ण
	पूर्ण

	वापस 0;

err_unरेजिस्टर_function_handlers:
	__rmi_unरेजिस्टर_function_handlers(i - 1);
	वापस ret;
पूर्ण

पूर्णांक rmi_of_property_पढ़ो_u32(काष्ठा device *dev, u32 *result,
				स्थिर अक्षर *prop, bool optional)
अणु
	पूर्णांक retval;
	u32 val = 0;

	retval = of_property_पढ़ो_u32(dev->of_node, prop, &val);
	अगर (retval && (!optional && retval == -EINVAL)) अणु
		dev_err(dev, "Failed to get %s value: %d\n",
			prop, retval);
		वापस retval;
	पूर्ण
	*result = val;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rmi_of_property_पढ़ो_u32);

अटल पूर्णांक __init rmi_bus_init(व्योम)
अणु
	पूर्णांक error;

	error = bus_रेजिस्टर(&rmi_bus_type);
	अगर (error) अणु
		pr_err("%s: error registering the RMI bus: %d\n",
			__func__, error);
		वापस error;
	पूर्ण

	error = rmi_रेजिस्टर_function_handlers();
	अगर (error)
		जाओ err_unरेजिस्टर_bus;

	error = rmi_रेजिस्टर_physical_driver();
	अगर (error) अणु
		pr_err("%s: error registering the RMI physical driver: %d\n",
			__func__, error);
		जाओ err_unरेजिस्टर_bus;
	पूर्ण

	वापस 0;

err_unरेजिस्टर_bus:
	bus_unरेजिस्टर(&rmi_bus_type);
	वापस error;
पूर्ण
module_init(rmi_bus_init);

अटल व्योम __निकास rmi_bus_निकास(व्योम)
अणु
	/*
	 * We should only ever get here अगर all drivers are unloaded, so
	 * all we have to करो at this poपूर्णांक is unरेजिस्टर ourselves.
	 */

	rmi_unरेजिस्टर_physical_driver();
	rmi_unरेजिस्टर_function_handlers();
	bus_unरेजिस्टर(&rmi_bus_type);
पूर्ण
module_निकास(rmi_bus_निकास);

MODULE_AUTHOR("Christopher Heiny <cheiny@synaptics.com");
MODULE_AUTHOR("Andrew Duggan <aduggan@synaptics.com");
MODULE_DESCRIPTION("RMI bus");
MODULE_LICENSE("GPL");
