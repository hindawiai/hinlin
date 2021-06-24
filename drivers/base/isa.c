<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ISA bus.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/isa.h>

अटल काष्ठा device isa_bus = अणु
	.init_name	= "isa"
पूर्ण;

काष्ठा isa_dev अणु
	काष्ठा device dev;
	काष्ठा device *next;
	अचिन्हित पूर्णांक id;
पूर्ण;

#घोषणा to_isa_dev(x) container_of((x), काष्ठा isa_dev, dev)

अटल पूर्णांक isa_bus_match(काष्ठा device *dev, काष्ठा device_driver *driver)
अणु
	काष्ठा isa_driver *isa_driver = to_isa_driver(driver);

	अगर (dev->platक्रमm_data == isa_driver) अणु
		अगर (!isa_driver->match ||
			isa_driver->match(dev, to_isa_dev(dev)->id))
			वापस 1;
		dev->platक्रमm_data = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक isa_bus_probe(काष्ठा device *dev)
अणु
	काष्ठा isa_driver *isa_driver = dev->platक्रमm_data;

	अगर (isa_driver && isa_driver->probe)
		वापस isa_driver->probe(dev, to_isa_dev(dev)->id);

	वापस 0;
पूर्ण

अटल पूर्णांक isa_bus_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा isa_driver *isa_driver = dev->platक्रमm_data;

	अगर (isa_driver && isa_driver->हटाओ)
		isa_driver->हटाओ(dev, to_isa_dev(dev)->id);

	वापस 0;
पूर्ण

अटल व्योम isa_bus_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा isa_driver *isa_driver = dev->platक्रमm_data;

	अगर (isa_driver && isa_driver->shutकरोwn)
		isa_driver->shutकरोwn(dev, to_isa_dev(dev)->id);
पूर्ण

अटल पूर्णांक isa_bus_suspend(काष्ठा device *dev, pm_message_t state)
अणु
	काष्ठा isa_driver *isa_driver = dev->platक्रमm_data;

	अगर (isa_driver && isa_driver->suspend)
		वापस isa_driver->suspend(dev, to_isa_dev(dev)->id, state);

	वापस 0;
पूर्ण

अटल पूर्णांक isa_bus_resume(काष्ठा device *dev)
अणु
	काष्ठा isa_driver *isa_driver = dev->platक्रमm_data;

	अगर (isa_driver && isa_driver->resume)
		वापस isa_driver->resume(dev, to_isa_dev(dev)->id);

	वापस 0;
पूर्ण

अटल काष्ठा bus_type isa_bus_type = अणु
	.name		= "isa",
	.match		= isa_bus_match,
	.probe		= isa_bus_probe,
	.हटाओ		= isa_bus_हटाओ,
	.shutकरोwn	= isa_bus_shutकरोwn,
	.suspend	= isa_bus_suspend,
	.resume		= isa_bus_resume
पूर्ण;

अटल व्योम isa_dev_release(काष्ठा device *dev)
अणु
	kमुक्त(to_isa_dev(dev));
पूर्ण

व्योम isa_unरेजिस्टर_driver(काष्ठा isa_driver *isa_driver)
अणु
	काष्ठा device *dev = isa_driver->devices;

	जबतक (dev) अणु
		काष्ठा device *पंचांगp = to_isa_dev(dev)->next;
		device_unरेजिस्टर(dev);
		dev = पंचांगp;
	पूर्ण
	driver_unरेजिस्टर(&isa_driver->driver);
पूर्ण
EXPORT_SYMBOL_GPL(isa_unरेजिस्टर_driver);

पूर्णांक isa_रेजिस्टर_driver(काष्ठा isa_driver *isa_driver, अचिन्हित पूर्णांक ndev)
अणु
	पूर्णांक error;
	अचिन्हित पूर्णांक id;

	isa_driver->driver.bus	= &isa_bus_type;
	isa_driver->devices	= शून्य;

	error = driver_रेजिस्टर(&isa_driver->driver);
	अगर (error)
		वापस error;

	क्रम (id = 0; id < ndev; id++) अणु
		काष्ठा isa_dev *isa_dev;

		isa_dev = kzalloc(माप *isa_dev, GFP_KERNEL);
		अगर (!isa_dev) अणु
			error = -ENOMEM;
			अवरोध;
		पूर्ण

		isa_dev->dev.parent	= &isa_bus;
		isa_dev->dev.bus	= &isa_bus_type;

		dev_set_name(&isa_dev->dev, "%s.%u",
			     isa_driver->driver.name, id);
		isa_dev->dev.platक्रमm_data	= isa_driver;
		isa_dev->dev.release		= isa_dev_release;
		isa_dev->id			= id;

		isa_dev->dev.coherent_dma_mask = DMA_BIT_MASK(24);
		isa_dev->dev.dma_mask = &isa_dev->dev.coherent_dma_mask;

		error = device_रेजिस्टर(&isa_dev->dev);
		अगर (error) अणु
			put_device(&isa_dev->dev);
			अवरोध;
		पूर्ण

		अगर (isa_dev->dev.platक्रमm_data) अणु
			isa_dev->next = isa_driver->devices;
			isa_driver->devices = &isa_dev->dev;
		पूर्ण अन्यथा
			device_unरेजिस्टर(&isa_dev->dev);
	पूर्ण

	अगर (!error && !isa_driver->devices)
		error = -ENODEV;

	अगर (error)
		isa_unरेजिस्टर_driver(isa_driver);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(isa_रेजिस्टर_driver);

अटल पूर्णांक __init isa_bus_init(व्योम)
अणु
	पूर्णांक error;

	error = bus_रेजिस्टर(&isa_bus_type);
	अगर (!error) अणु
		error = device_रेजिस्टर(&isa_bus);
		अगर (error)
			bus_unरेजिस्टर(&isa_bus_type);
	पूर्ण
	वापस error;
पूर्ण

postcore_initcall(isa_bus_init);
