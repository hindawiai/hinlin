<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ddbridge.c: Digital Devices PCIe bridge driver
 *
 * Copyright (C) 2010-2017 Digital Devices GmbH
 *                         Ralph Metzler <rjkm@metzlerbros.de>
 *                         Marcus Metzler <mocm@metzlerbros.de>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2 only, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/पन.स>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/समयr.h>
#समावेश <linux/i2c.h>
#समावेश <linux/swab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "ddbridge.h"
#समावेश "ddbridge-i2c.h"
#समावेश "ddbridge-regs.h"
#समावेश "ddbridge-hw.h"
#समावेश "ddbridge-io.h"

/****************************************************************************/
/* module parameters */

#अगर_घोषित CONFIG_PCI_MSI
#अगर_घोषित CONFIG_DVB_DDBRIDGE_MSIENABLE
अटल पूर्णांक msi = 1;
#अन्यथा
अटल पूर्णांक msi;
#पूर्ण_अगर
module_param(msi, पूर्णांक, 0444);
#अगर_घोषित CONFIG_DVB_DDBRIDGE_MSIENABLE
MODULE_PARM_DESC(msi, "Control MSI interrupts: 0-disable, 1-enable (default)");
#अन्यथा
MODULE_PARM_DESC(msi, "Control MSI interrupts: 0-disable (default), 1-enable");
#पूर्ण_अगर
#पूर्ण_अगर

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

अटल व्योम ddb_irq_disable(काष्ठा ddb *dev)
अणु
	ddbग_लिखोl(dev, 0, INTERRUPT_ENABLE);
	ddbग_लिखोl(dev, 0, MSI1_ENABLE);
पूर्ण

अटल व्योम ddb_msi_निकास(काष्ठा ddb *dev)
अणु
#अगर_घोषित CONFIG_PCI_MSI
	अगर (dev->msi)
		pci_मुक्त_irq_vectors(dev->pdev);
#पूर्ण_अगर
पूर्ण

अटल व्योम ddb_irq_निकास(काष्ठा ddb *dev)
अणु
	ddb_irq_disable(dev);
	अगर (dev->msi == 2)
		मुक्त_irq(pci_irq_vector(dev->pdev, 1), dev);
	मुक्त_irq(pci_irq_vector(dev->pdev, 0), dev);
पूर्ण

अटल व्योम ddb_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ddb *dev = (काष्ठा ddb *)pci_get_drvdata(pdev);

	ddb_device_destroy(dev);
	ddb_ports_detach(dev);
	ddb_i2c_release(dev);

	ddb_irq_निकास(dev);
	ddb_msi_निकास(dev);
	ddb_ports_release(dev);
	ddb_buffers_मुक्त(dev);

	ddb_unmap(dev);
	pci_set_drvdata(pdev, शून्य);
	pci_disable_device(pdev);
पूर्ण

#अगर_घोषित CONFIG_PCI_MSI
अटल व्योम ddb_irq_msi(काष्ठा ddb *dev, पूर्णांक nr)
अणु
	पूर्णांक stat;

	अगर (msi && pci_msi_enabled()) अणु
		stat = pci_alloc_irq_vectors(dev->pdev, 1, nr,
					     PCI_IRQ_MSI | PCI_IRQ_MSIX);
		अगर (stat >= 1) अणु
			dev->msi = stat;
			dev_info(dev->dev, "using %d MSI interrupt(s)\n",
				 dev->msi);
		पूर्ण अन्यथा अणु
			dev_info(dev->dev, "MSI not available.\n");
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ddb_irq_init(काष्ठा ddb *dev)
अणु
	पूर्णांक stat;
	पूर्णांक irq_flag = IRQF_SHARED;

	ddbग_लिखोl(dev, 0x00000000, INTERRUPT_ENABLE);
	ddbग_लिखोl(dev, 0x00000000, MSI1_ENABLE);
	ddbग_लिखोl(dev, 0x00000000, MSI2_ENABLE);
	ddbग_लिखोl(dev, 0x00000000, MSI3_ENABLE);
	ddbग_लिखोl(dev, 0x00000000, MSI4_ENABLE);
	ddbग_लिखोl(dev, 0x00000000, MSI5_ENABLE);
	ddbग_लिखोl(dev, 0x00000000, MSI6_ENABLE);
	ddbग_लिखोl(dev, 0x00000000, MSI7_ENABLE);

#अगर_घोषित CONFIG_PCI_MSI
	ddb_irq_msi(dev, 2);

	अगर (dev->msi)
		irq_flag = 0;
	अगर (dev->msi == 2) अणु
		stat = request_irq(pci_irq_vector(dev->pdev, 0),
				   ddb_irq_handler0, irq_flag, "ddbridge",
				   (व्योम *)dev);
		अगर (stat < 0)
			वापस stat;
		stat = request_irq(pci_irq_vector(dev->pdev, 1),
				   ddb_irq_handler1, irq_flag, "ddbridge",
				   (व्योम *)dev);
		अगर (stat < 0) अणु
			मुक्त_irq(pci_irq_vector(dev->pdev, 0), dev);
			वापस stat;
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		stat = request_irq(pci_irq_vector(dev->pdev, 0),
				   ddb_irq_handler, irq_flag, "ddbridge",
				   (व्योम *)dev);
		अगर (stat < 0)
			वापस stat;
	पूर्ण
	अगर (dev->msi == 2) अणु
		ddbग_लिखोl(dev, 0x0fffff00, INTERRUPT_ENABLE);
		ddbग_लिखोl(dev, 0x0000000f, MSI1_ENABLE);
	पूर्ण अन्यथा अणु
		ddbग_लिखोl(dev, 0x0fffff0f, INTERRUPT_ENABLE);
		ddbग_लिखोl(dev, 0x00000000, MSI1_ENABLE);
	पूर्ण
	वापस stat;
पूर्ण

अटल पूर्णांक ddb_probe(काष्ठा pci_dev *pdev,
		     स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा ddb *dev;
	पूर्णांक stat = 0;

	अगर (pci_enable_device(pdev) < 0)
		वापस -ENODEV;

	pci_set_master(pdev);

	अगर (pci_set_dma_mask(pdev, DMA_BIT_MASK(64)))
		अगर (pci_set_dma_mask(pdev, DMA_BIT_MASK(32)))
			वापस -ENODEV;

	dev = vzalloc(माप(*dev));
	अगर (!dev)
		वापस -ENOMEM;

	mutex_init(&dev->mutex);
	dev->has_dma = 1;
	dev->pdev = pdev;
	dev->dev = &pdev->dev;
	pci_set_drvdata(pdev, dev);

	dev->link[0].ids.venकरोr = id->venकरोr;
	dev->link[0].ids.device = id->device;
	dev->link[0].ids.subvenकरोr = id->subvenकरोr;
	dev->link[0].ids.subdevice = pdev->subप्रणाली_device;
	dev->link[0].ids.devid = (id->device << 16) | id->venकरोr;

	dev->link[0].dev = dev;
	dev->link[0].info = get_ddb_info(id->venकरोr, id->device,
					 id->subvenकरोr, pdev->subप्रणाली_device);

	dev_info(&pdev->dev, "detected %s\n", dev->link[0].info->name);

	dev->regs_len = pci_resource_len(dev->pdev, 0);
	dev->regs = ioremap(pci_resource_start(dev->pdev, 0),
			    pci_resource_len(dev->pdev, 0));

	अगर (!dev->regs) अणु
		dev_err(&pdev->dev, "not enough memory for register map\n");
		stat = -ENOMEM;
		जाओ fail;
	पूर्ण
	अगर (ddbपढ़ोl(dev, 0) == 0xffffffff) अणु
		dev_err(&pdev->dev, "cannot read registers\n");
		stat = -ENODEV;
		जाओ fail;
	पूर्ण

	dev->link[0].ids.hwid = ddbपढ़ोl(dev, 0);
	dev->link[0].ids.regmapid = ddbपढ़ोl(dev, 4);

	dev_info(&pdev->dev, "HW %08x REGMAP %08x\n",
		 dev->link[0].ids.hwid, dev->link[0].ids.regmapid);

	ddbग_लिखोl(dev, 0, DMA_BASE_READ);
	ddbग_लिखोl(dev, 0, DMA_BASE_WRITE);

	stat = ddb_irq_init(dev);
	अगर (stat < 0)
		जाओ fail0;

	अगर (ddb_init(dev) == 0)
		वापस 0;

	ddb_irq_निकास(dev);
fail0:
	dev_err(&pdev->dev, "fail0\n");
	ddb_msi_निकास(dev);
fail:
	dev_err(&pdev->dev, "fail\n");

	ddb_unmap(dev);
	pci_set_drvdata(pdev, शून्य);
	pci_disable_device(pdev);
	वापस -1;
पूर्ण

/****************************************************************************/
/****************************************************************************/
/****************************************************************************/

#घोषणा DDB_DEVICE_ANY(_device) \
		अणु PCI_DEVICE_SUB(DDVID, _device, DDVID, PCI_ANY_ID) पूर्ण

अटल स्थिर काष्ठा pci_device_id ddb_id_table[] = अणु
	DDB_DEVICE_ANY(0x0002),
	DDB_DEVICE_ANY(0x0003),
	DDB_DEVICE_ANY(0x0005),
	DDB_DEVICE_ANY(0x0006),
	DDB_DEVICE_ANY(0x0007),
	DDB_DEVICE_ANY(0x0008),
	DDB_DEVICE_ANY(0x0009),
	DDB_DEVICE_ANY(0x0011),
	DDB_DEVICE_ANY(0x0012),
	DDB_DEVICE_ANY(0x0013),
	DDB_DEVICE_ANY(0x0201),
	DDB_DEVICE_ANY(0x0203),
	DDB_DEVICE_ANY(0x0210),
	DDB_DEVICE_ANY(0x0220),
	DDB_DEVICE_ANY(0x0320),
	DDB_DEVICE_ANY(0x0321),
	DDB_DEVICE_ANY(0x0322),
	DDB_DEVICE_ANY(0x0323),
	DDB_DEVICE_ANY(0x0328),
	DDB_DEVICE_ANY(0x0329),
	अणु0पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, ddb_id_table);

अटल काष्ठा pci_driver ddb_pci_driver = अणु
	.name        = "ddbridge",
	.id_table    = ddb_id_table,
	.probe       = ddb_probe,
	.हटाओ      = ddb_हटाओ,
पूर्ण;

अटल __init पूर्णांक module_init_ddbridge(व्योम)
अणु
	पूर्णांक stat;

	pr_info("Digital Devices PCIE bridge driver "
		DDBRIDGE_VERSION
		", Copyright (C) 2010-17 Digital Devices GmbH\n");
	stat = ddb_init_ddbridge();
	अगर (stat < 0)
		वापस stat;
	stat = pci_रेजिस्टर_driver(&ddb_pci_driver);
	अगर (stat < 0)
		ddb_निकास_ddbridge(0, stat);

	वापस stat;
पूर्ण

अटल __निकास व्योम module_निकास_ddbridge(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ddb_pci_driver);
	ddb_निकास_ddbridge(0, 0);
पूर्ण

module_init(module_init_ddbridge);
module_निकास(module_निकास_ddbridge);

MODULE_DESCRIPTION("Digital Devices PCIe Bridge");
MODULE_AUTHOR("Ralph and Marcus Metzler, Metzler Brothers Systementwicklung GbR");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(DDBRIDGE_VERSION);
