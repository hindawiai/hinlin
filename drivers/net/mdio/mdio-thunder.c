<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2009-2016 Cavium, Inc.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/gfp.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/pci.h>
#समावेश <linux/phy.h>

#समावेश "mdio-cavium.h"

काष्ठा thunder_mdiobus_nexus अणु
	व्योम __iomem *bar0;
	काष्ठा cavium_mdiobus *buses[4];
पूर्ण;

अटल पूर्णांक thunder_mdiobus_pci_probe(काष्ठा pci_dev *pdev,
				     स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा device_node *node;
	काष्ठा fwnode_handle *fwn;
	काष्ठा thunder_mdiobus_nexus *nexus;
	पूर्णांक err;
	पूर्णांक i;

	nexus = devm_kzalloc(&pdev->dev, माप(*nexus), GFP_KERNEL);
	अगर (!nexus)
		वापस -ENOMEM;

	pci_set_drvdata(pdev, nexus);

	err = pcim_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to enable PCI device\n");
		pci_set_drvdata(pdev, शून्य);
		वापस err;
	पूर्ण

	err = pci_request_regions(pdev, KBUILD_MODNAME);
	अगर (err) अणु
		dev_err(&pdev->dev, "pci_request_regions failed\n");
		जाओ err_disable_device;
	पूर्ण

	nexus->bar0 = pcim_iomap(pdev, 0, pci_resource_len(pdev, 0));
	अगर (!nexus->bar0) अणु
		err = -ENOMEM;
		जाओ err_release_regions;
	पूर्ण

	i = 0;
	device_क्रम_each_child_node(&pdev->dev, fwn) अणु
		काष्ठा resource r;
		काष्ठा mii_bus *mii_bus;
		काष्ठा cavium_mdiobus *bus;
		जोड़ cvmx_smix_en smi_en;

		/* If it is not an OF node we cannot handle it yet, so
		 * निकास the loop.
		 */
		node = to_of_node(fwn);
		अगर (!node)
			अवरोध;

		err = of_address_to_resource(node, 0, &r);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"Couldn't translate address for \"%pOFn\"\n",
				node);
			अवरोध;
		पूर्ण

		mii_bus = devm_mdiobus_alloc_size(&pdev->dev, माप(*bus));
		अगर (!mii_bus)
			अवरोध;
		bus = mii_bus->priv;
		bus->mii_bus = mii_bus;

		nexus->buses[i] = bus;
		i++;

		bus->रेजिस्टर_base = nexus->bar0 +
			r.start - pci_resource_start(pdev, 0);

		smi_en.u64 = 0;
		smi_en.s.en = 1;
		oct_mdio_ग_लिखोq(smi_en.u64, bus->रेजिस्टर_base + SMI_EN);
		bus->mii_bus->name = KBUILD_MODNAME;
		snम_लिखो(bus->mii_bus->id, MII_BUS_ID_SIZE, "%llx", r.start);
		bus->mii_bus->parent = &pdev->dev;
		bus->mii_bus->पढ़ो = cavium_mdiobus_पढ़ो;
		bus->mii_bus->ग_लिखो = cavium_mdiobus_ग_लिखो;

		err = of_mdiobus_रेजिस्टर(bus->mii_bus, node);
		अगर (err)
			dev_err(&pdev->dev, "of_mdiobus_register failed\n");

		dev_info(&pdev->dev, "Added bus at %llx\n", r.start);
		अगर (i >= ARRAY_SIZE(nexus->buses))
			अवरोध;
	पूर्ण
	वापस 0;

err_release_regions:
	pci_release_regions(pdev);

err_disable_device:
	pci_set_drvdata(pdev, शून्य);
	वापस err;
पूर्ण

अटल व्योम thunder_mdiobus_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;
	काष्ठा thunder_mdiobus_nexus *nexus = pci_get_drvdata(pdev);

	क्रम (i = 0; i < ARRAY_SIZE(nexus->buses); i++) अणु
		काष्ठा cavium_mdiobus *bus = nexus->buses[i];

		अगर (!bus)
			जारी;

		mdiobus_unरेजिस्टर(bus->mii_bus);
		oct_mdio_ग_लिखोq(0, bus->रेजिस्टर_base + SMI_EN);
	पूर्ण
	pci_release_regions(pdev);
	pci_set_drvdata(pdev, शून्य);
पूर्ण

अटल स्थिर काष्ठा pci_device_id thunder_mdiobus_id_table[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_CAVIUM, 0xa02b) पूर्ण,
	अणु 0, पूर्ण /* End of table. */
पूर्ण;
MODULE_DEVICE_TABLE(pci, thunder_mdiobus_id_table);

अटल काष्ठा pci_driver thunder_mdiobus_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = thunder_mdiobus_id_table,
	.probe = thunder_mdiobus_pci_probe,
	.हटाओ = thunder_mdiobus_pci_हटाओ,
पूर्ण;

module_pci_driver(thunder_mdiobus_driver);

MODULE_DESCRIPTION("Cavium ThunderX MDIO bus driver");
MODULE_LICENSE("GPL v2");
