<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CE4100 PCI-I2C glue code क्रम PXA's driver
 * Author: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 *
 * The CE4100's I2C device is more or less the same one as found on PXA.
 * It करोes not support slave mode, the रेजिस्टर slightly moved. This PCI
 * device provides three bars, every contains a single I2C controller.
 */
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>

#घोषणा CE4100_PCI_I2C_DEVS	3

काष्ठा ce4100_devices अणु
	काष्ठा platक्रमm_device *pdev[CE4100_PCI_I2C_DEVS];
पूर्ण;

अटल काष्ठा platक्रमm_device *add_i2c_device(काष्ठा pci_dev *dev, पूर्णांक bar)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा i2c_pxa_platक्रमm_data pdata;
	काष्ठा resource res[2];
	काष्ठा device_node *child;
	अटल पूर्णांक devnum;
	पूर्णांक ret;

	स_रखो(&pdata, 0, माप(काष्ठा i2c_pxa_platक्रमm_data));
	स_रखो(&res, 0, माप(res));

	res[0].flags = IORESOURCE_MEM;
	res[0].start = pci_resource_start(dev, bar);
	res[0].end = pci_resource_end(dev, bar);

	res[1].flags = IORESOURCE_IRQ;
	res[1].start = dev->irq;
	res[1].end = dev->irq;

	क्रम_each_child_of_node(dev->dev.of_node, child) अणु
		स्थिर व्योम *prop;
		काष्ठा resource r;
		पूर्णांक ret;

		ret = of_address_to_resource(child, 0, &r);
		अगर (ret < 0)
			जारी;
		अगर (r.start != res[0].start)
			जारी;
		अगर (r.end != res[0].end)
			जारी;
		अगर (r.flags != res[0].flags)
			जारी;

		prop = of_get_property(child, "fast-mode", शून्य);
		अगर (prop)
			pdata.fast_mode = 1;

		अवरोध;
	पूर्ण

	अगर (!child) अणु
		dev_err(&dev->dev, "failed to match a DT node for bar %d.\n",
				bar);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	pdev = platक्रमm_device_alloc("ce4100-i2c", devnum);
	अगर (!pdev) अणु
		of_node_put(child);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	pdev->dev.parent = &dev->dev;
	pdev->dev.of_node = child;

	ret = platक्रमm_device_add_resources(pdev, res, ARRAY_SIZE(res));
	अगर (ret)
		जाओ err;

	ret = platक्रमm_device_add_data(pdev, &pdata, माप(pdata));
	अगर (ret)
		जाओ err;

	ret = platक्रमm_device_add(pdev);
	अगर (ret)
		जाओ err;
	devnum++;
	वापस pdev;
err:
	platक्रमm_device_put(pdev);
out:
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक ce4100_i2c_probe(काष्ठा pci_dev *dev,
		स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	काष्ठा ce4100_devices *sds;

	ret = pci_enable_device_mem(dev);
	अगर (ret)
		वापस ret;

	अगर (!dev->dev.of_node) अणु
		dev_err(&dev->dev, "Missing device tree node.\n");
		वापस -EINVAL;
	पूर्ण
	sds = kzalloc(माप(*sds), GFP_KERNEL);
	अगर (!sds) अणु
		ret = -ENOMEM;
		जाओ err_mem;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(sds->pdev); i++) अणु
		sds->pdev[i] = add_i2c_device(dev, i);
		अगर (IS_ERR(sds->pdev[i])) अणु
			ret = PTR_ERR(sds->pdev[i]);
			जबतक (--i >= 0)
				platक्रमm_device_unरेजिस्टर(sds->pdev[i]);
			जाओ err_dev_add;
		पूर्ण
	पूर्ण
	pci_set_drvdata(dev, sds);
	वापस 0;

err_dev_add:
	kमुक्त(sds);
err_mem:
	pci_disable_device(dev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pci_device_id ce4100_i2c_devices[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, 0x2e68)पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा pci_driver ce4100_i2c_driver = अणु
	.driver = अणु
		.suppress_bind_attrs = true,
	पूर्ण,
	.name           = "ce4100_i2c",
	.id_table       = ce4100_i2c_devices,
	.probe          = ce4100_i2c_probe,
पूर्ण;
builtin_pci_driver(ce4100_i2c_driver);
