<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/* Copyright 2019 NXP */
#समावेश <linux/fsl/enetc_mdपन.स>
#समावेश <linux/of_mdपन.स>
#समावेश "enetc_pf.h"

#घोषणा ENETC_MDIO_DEV_ID	0xee01
#घोषणा ENETC_MDIO_DEV_NAME	"FSL PCIe IE Central MDIO"
#घोषणा ENETC_MDIO_BUS_NAME	ENETC_MDIO_DEV_NAME " Bus"
#घोषणा ENETC_MDIO_DRV_NAME	ENETC_MDIO_DEV_NAME " driver"

अटल पूर्णांक enetc_pci_mdio_probe(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा enetc_mdio_priv *mdio_priv;
	काष्ठा device *dev = &pdev->dev;
	व्योम __iomem *port_regs;
	काष्ठा enetc_hw *hw;
	काष्ठा mii_bus *bus;
	पूर्णांक err;

	port_regs = pci_iomap(pdev, 0, 0);
	अगर (!port_regs) अणु
		dev_err(dev, "iomap failed\n");
		err = -ENXIO;
		जाओ err_ioremap;
	पूर्ण

	hw = enetc_hw_alloc(dev, port_regs);
	अगर (IS_ERR(hw)) अणु
		err = PTR_ERR(hw);
		जाओ err_hw_alloc;
	पूर्ण

	bus = devm_mdiobus_alloc_size(dev, माप(*mdio_priv));
	अगर (!bus) अणु
		err = -ENOMEM;
		जाओ err_mdiobus_alloc;
	पूर्ण

	bus->name = ENETC_MDIO_BUS_NAME;
	bus->पढ़ो = enetc_mdio_पढ़ो;
	bus->ग_लिखो = enetc_mdio_ग_लिखो;
	bus->parent = dev;
	mdio_priv = bus->priv;
	mdio_priv->hw = hw;
	mdio_priv->mdio_base = ENETC_EMDIO_BASE;
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s", dev_name(dev));

	pcie_flr(pdev);
	err = pci_enable_device_mem(pdev);
	अगर (err) अणु
		dev_err(dev, "device enable failed\n");
		जाओ err_pci_enable;
	पूर्ण

	err = pci_request_region(pdev, 0, KBUILD_MODNAME);
	अगर (err) अणु
		dev_err(dev, "pci_request_region failed\n");
		जाओ err_pci_mem_reg;
	पूर्ण

	err = of_mdiobus_रेजिस्टर(bus, dev->of_node);
	अगर (err)
		जाओ err_mdiobus_reg;

	pci_set_drvdata(pdev, bus);

	वापस 0;

err_mdiobus_reg:
	pci_release_mem_regions(pdev);
err_pci_mem_reg:
	pci_disable_device(pdev);
err_pci_enable:
err_mdiobus_alloc:
err_hw_alloc:
	iounmap(port_regs);
err_ioremap:
	वापस err;
पूर्ण

अटल व्योम enetc_pci_mdio_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mii_bus *bus = pci_get_drvdata(pdev);
	काष्ठा enetc_mdio_priv *mdio_priv;

	mdiobus_unरेजिस्टर(bus);
	mdio_priv = bus->priv;
	iounmap(mdio_priv->hw->port);
	pci_release_mem_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id enetc_pci_mdio_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_FREESCALE, ENETC_MDIO_DEV_ID) पूर्ण,
	अणु 0, पूर्ण /* End of table. */
पूर्ण;
MODULE_DEVICE_TABLE(pci, enetc_pci_mdio_id_table);

अटल काष्ठा pci_driver enetc_pci_mdio_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = enetc_pci_mdio_id_table,
	.probe = enetc_pci_mdio_probe,
	.हटाओ = enetc_pci_mdio_हटाओ,
पूर्ण;
module_pci_driver(enetc_pci_mdio_driver);

MODULE_DESCRIPTION(ENETC_MDIO_DRV_NAME);
MODULE_LICENSE("Dual BSD/GPL");
