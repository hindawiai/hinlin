<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MEN Chameleon Bus.
 *
 * Copyright (C) 2014 MEN Mikroelektronik GmbH (www.men.de)
 * Author: Johannes Thumshirn <johannes.thumshirn@men.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/mcb.h>

#समावेश "mcb-internal.h"

काष्ठा priv अणु
	काष्ठा mcb_bus *bus;
	phys_addr_t mapbase;
	व्योम __iomem *base;
पूर्ण;

अटल पूर्णांक mcb_pci_get_irq(काष्ठा mcb_device *mdev)
अणु
	काष्ठा mcb_bus *mbus = mdev->bus;
	काष्ठा device *dev = mbus->carrier;
	काष्ठा pci_dev *pdev = to_pci_dev(dev);

	वापस pdev->irq;
पूर्ण

अटल पूर्णांक mcb_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा resource *res;
	काष्ठा priv *priv;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	priv = devm_kzalloc(&pdev->dev, माप(काष्ठा priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to enable PCI device\n");
		वापस -ENODEV;
	पूर्ण
	pci_set_master(pdev);

	priv->mapbase = pci_resource_start(pdev, 0);
	अगर (!priv->mapbase) अणु
		dev_err(&pdev->dev, "No PCI resource\n");
		ret = -ENODEV;
		जाओ out_disable;
	पूर्ण

	res = devm_request_mem_region(&pdev->dev, priv->mapbase,
				      CHAM_HEADER_SIZE,
				      KBUILD_MODNAME);
	अगर (!res) अणु
		dev_err(&pdev->dev, "Failed to request PCI memory\n");
		ret = -EBUSY;
		जाओ out_disable;
	पूर्ण

	priv->base = devm_ioremap(&pdev->dev, priv->mapbase, CHAM_HEADER_SIZE);
	अगर (!priv->base) अणु
		dev_err(&pdev->dev, "Cannot ioremap\n");
		ret = -ENOMEM;
		जाओ out_disable;
	पूर्ण

	flags = pci_resource_flags(pdev, 0);
	अगर (flags & IORESOURCE_IO) अणु
		ret = -ENOTSUPP;
		dev_err(&pdev->dev,
			"IO mapped PCI devices are not supported\n");
		जाओ out_disable;
	पूर्ण

	pci_set_drvdata(pdev, priv);

	priv->bus = mcb_alloc_bus(&pdev->dev);
	अगर (IS_ERR(priv->bus)) अणु
		ret = PTR_ERR(priv->bus);
		जाओ out_disable;
	पूर्ण

	priv->bus->get_irq = mcb_pci_get_irq;

	ret = chameleon_parse_cells(priv->bus, priv->mapbase, priv->base);
	अगर (ret < 0)
		जाओ out_mcb_bus;

	dev_dbg(&pdev->dev, "Found %d cells\n", ret);

	mcb_bus_add_devices(priv->bus);

	वापस 0;

out_mcb_bus:
	mcb_release_bus(priv->bus);
out_disable:
	pci_disable_device(pdev);
	वापस ret;
पूर्ण

अटल व्योम mcb_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा priv *priv = pci_get_drvdata(pdev);

	mcb_release_bus(priv->bus);

	pci_disable_device(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id mcb_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_MEN, PCI_DEVICE_ID_MEN_CHAMELEON) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_ALTERA, PCI_DEVICE_ID_MEN_CHAMELEON) पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, mcb_pci_tbl);

अटल काष्ठा pci_driver mcb_pci_driver = अणु
	.name = "mcb-pci",
	.id_table = mcb_pci_tbl,
	.probe = mcb_pci_probe,
	.हटाओ = mcb_pci_हटाओ,
पूर्ण;

module_pci_driver(mcb_pci_driver);

MODULE_AUTHOR("Johannes Thumshirn <johannes.thumshirn@men.de>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MCB over PCI support");
MODULE_IMPORT_NS(MCB);
