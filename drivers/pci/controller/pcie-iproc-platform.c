<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Broadcom Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>

#समावेश "../pci.h"
#समावेश "pcie-iproc.h"

अटल स्थिर काष्ठा of_device_id iproc_pcie_of_match_table[] = अणु
	अणु
		.compatible = "brcm,iproc-pcie",
		.data = (पूर्णांक *)IPROC_PCIE_PAXB,
	पूर्ण, अणु
		.compatible = "brcm,iproc-pcie-paxb-v2",
		.data = (पूर्णांक *)IPROC_PCIE_PAXB_V2,
	पूर्ण, अणु
		.compatible = "brcm,iproc-pcie-paxc",
		.data = (पूर्णांक *)IPROC_PCIE_PAXC,
	पूर्ण, अणु
		.compatible = "brcm,iproc-pcie-paxc-v2",
		.data = (पूर्णांक *)IPROC_PCIE_PAXC_V2,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, iproc_pcie_of_match_table);

अटल पूर्णांक iproc_pcie_pltfm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा iproc_pcie *pcie;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा resource reg;
	काष्ठा pci_host_bridge *bridge;
	पूर्णांक ret;

	bridge = devm_pci_alloc_host_bridge(dev, माप(*pcie));
	अगर (!bridge)
		वापस -ENOMEM;

	pcie = pci_host_bridge_priv(bridge);

	pcie->dev = dev;
	pcie->type = (क्रमागत iproc_pcie_type) of_device_get_match_data(dev);

	ret = of_address_to_resource(np, 0, &reg);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to obtain controller resources\n");
		वापस ret;
	पूर्ण

	pcie->base = devm_pci_remap_cfgspace(dev, reg.start,
					     resource_size(&reg));
	अगर (!pcie->base) अणु
		dev_err(dev, "unable to map controller registers\n");
		वापस -ENOMEM;
	पूर्ण
	pcie->base_addr = reg.start;

	अगर (of_property_पढ़ो_bool(np, "brcm,pcie-ob")) अणु
		u32 val;

		ret = of_property_पढ़ो_u32(np, "brcm,pcie-ob-axi-offset",
					   &val);
		अगर (ret) अणु
			dev_err(dev,
				"missing brcm,pcie-ob-axi-offset property\n");
			वापस ret;
		पूर्ण
		pcie->ob.axi_offset = val;
		pcie->need_ob_cfg = true;
	पूर्ण

	/*
	 * DT nodes are not used by all platक्रमms that use the iProc PCIe
	 * core driver. For platक्रमms that require explicit inbound mapping
	 * configuration, "dma-ranges" would have been present in DT
	 */
	pcie->need_ib_cfg = of_property_पढ़ो_bool(np, "dma-ranges");

	/* PHY use is optional */
	pcie->phy = devm_phy_optional_get(dev, "pcie-phy");
	अगर (IS_ERR(pcie->phy))
		वापस PTR_ERR(pcie->phy);

	/* PAXC करोesn't support legacy IRQs, skip mapping */
	चयन (pcie->type) अणु
	हाल IPROC_PCIE_PAXC:
	हाल IPROC_PCIE_PAXC_V2:
		pcie->map_irq = शून्य;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ret = iproc_pcie_setup(pcie, &bridge->winकरोws);
	अगर (ret) अणु
		dev_err(dev, "PCIe controller setup failed\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pcie);
	वापस 0;
पूर्ण

अटल पूर्णांक iproc_pcie_pltfm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iproc_pcie *pcie = platक्रमm_get_drvdata(pdev);

	वापस iproc_pcie_हटाओ(pcie);
पूर्ण

अटल व्योम iproc_pcie_pltfm_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iproc_pcie *pcie = platक्रमm_get_drvdata(pdev);

	iproc_pcie_shutकरोwn(pcie);
पूर्ण

अटल काष्ठा platक्रमm_driver iproc_pcie_pltfm_driver = अणु
	.driver = अणु
		.name = "iproc-pcie",
		.of_match_table = of_match_ptr(iproc_pcie_of_match_table),
	पूर्ण,
	.probe = iproc_pcie_pltfm_probe,
	.हटाओ = iproc_pcie_pltfm_हटाओ,
	.shutकरोwn = iproc_pcie_pltfm_shutकरोwn,
पूर्ण;
module_platक्रमm_driver(iproc_pcie_pltfm_driver);

MODULE_AUTHOR("Ray Jui <rjui@broadcom.com>");
MODULE_DESCRIPTION("Broadcom iPROC PCIe platform driver");
MODULE_LICENSE("GPL v2");
