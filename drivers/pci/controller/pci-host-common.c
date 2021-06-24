<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic PCI host driver common code
 *
 * Copyright (C) 2014 ARM Limited
 *
 * Author: Will Deacon <will.deacon@arm.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci-ecam.h>
#समावेश <linux/platक्रमm_device.h>

अटल व्योम gen_pci_unmap_cfg(व्योम *ptr)
अणु
	pci_ecam_मुक्त((काष्ठा pci_config_winकरोw *)ptr);
पूर्ण

अटल काष्ठा pci_config_winकरोw *gen_pci_init(काष्ठा device *dev,
		काष्ठा pci_host_bridge *bridge, स्थिर काष्ठा pci_ecam_ops *ops)
अणु
	पूर्णांक err;
	काष्ठा resource cfgres;
	काष्ठा resource_entry *bus;
	काष्ठा pci_config_winकरोw *cfg;

	err = of_address_to_resource(dev->of_node, 0, &cfgres);
	अगर (err) अणु
		dev_err(dev, "missing \"reg\" property\n");
		वापस ERR_PTR(err);
	पूर्ण

	bus = resource_list_first_type(&bridge->winकरोws, IORESOURCE_BUS);
	अगर (!bus)
		वापस ERR_PTR(-ENODEV);

	cfg = pci_ecam_create(dev, &cfgres, bus->res, ops);
	अगर (IS_ERR(cfg))
		वापस cfg;

	err = devm_add_action_or_reset(dev, gen_pci_unmap_cfg, cfg);
	अगर (err)
		वापस ERR_PTR(err);

	वापस cfg;
पूर्ण

पूर्णांक pci_host_common_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pci_host_bridge *bridge;
	काष्ठा pci_config_winकरोw *cfg;
	स्थिर काष्ठा pci_ecam_ops *ops;

	ops = of_device_get_match_data(&pdev->dev);
	अगर (!ops)
		वापस -ENODEV;

	bridge = devm_pci_alloc_host_bridge(dev, 0);
	अगर (!bridge)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, bridge);

	of_pci_check_probe_only();

	/* Parse and map our Configuration Space winकरोws */
	cfg = gen_pci_init(dev, bridge, ops);
	अगर (IS_ERR(cfg))
		वापस PTR_ERR(cfg);

	/* Do not reassign resources अगर probe only */
	अगर (!pci_has_flag(PCI_PROBE_ONLY))
		pci_add_flags(PCI_REASSIGN_ALL_BUS);

	bridge->sysdata = cfg;
	bridge->ops = (काष्ठा pci_ops *)&ops->pci_ops;
	bridge->msi_करोमुख्य = true;

	वापस pci_host_probe(bridge);
पूर्ण
EXPORT_SYMBOL_GPL(pci_host_common_probe);

पूर्णांक pci_host_common_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pci_host_bridge *bridge = platक्रमm_get_drvdata(pdev);

	pci_lock_rescan_हटाओ();
	pci_stop_root_bus(bridge->bus);
	pci_हटाओ_root_bus(bridge->bus);
	pci_unlock_rescan_हटाओ();

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pci_host_common_हटाओ);

MODULE_LICENSE("GPL v2");
