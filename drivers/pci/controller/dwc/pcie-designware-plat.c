<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe RC driver क्रम Synopsys DesignWare Core
 *
 * Copyright (C) 2015-2016 Synopsys, Inc. (www.synopsys.com)
 *
 * Authors: Joao Pपूर्णांकo <Joao.Pपूर्णांकo@synopsys.com>
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/resource.h>
#समावेश <linux/types.h>
#समावेश <linux/regmap.h>

#समावेश "pcie-designware.h"

काष्ठा dw_plat_pcie अणु
	काष्ठा dw_pcie			*pci;
	काष्ठा regmap			*regmap;
	क्रमागत dw_pcie_device_mode	mode;
पूर्ण;

काष्ठा dw_plat_pcie_of_data अणु
	क्रमागत dw_pcie_device_mode	mode;
पूर्ण;

अटल स्थिर काष्ठा of_device_id dw_plat_pcie_of_match[];

अटल स्थिर काष्ठा dw_pcie_host_ops dw_plat_pcie_host_ops = अणु
पूर्ण;

अटल पूर्णांक dw_plat_pcie_establish_link(काष्ठा dw_pcie *pci)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ops dw_pcie_ops = अणु
	.start_link = dw_plat_pcie_establish_link,
पूर्ण;

अटल व्योम dw_plat_pcie_ep_init(काष्ठा dw_pcie_ep *ep)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	क्रमागत pci_barno bar;

	क्रम (bar = 0; bar < PCI_STD_NUM_BARS; bar++)
		dw_pcie_ep_reset_bar(pci, bar);
पूर्ण

अटल पूर्णांक dw_plat_pcie_ep_उठाओ_irq(काष्ठा dw_pcie_ep *ep, u8 func_no,
				     क्रमागत pci_epc_irq_type type,
				     u16 पूर्णांकerrupt_num)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);

	चयन (type) अणु
	हाल PCI_EPC_IRQ_LEGACY:
		वापस dw_pcie_ep_उठाओ_legacy_irq(ep, func_no);
	हाल PCI_EPC_IRQ_MSI:
		वापस dw_pcie_ep_उठाओ_msi_irq(ep, func_no, पूर्णांकerrupt_num);
	हाल PCI_EPC_IRQ_MSIX:
		वापस dw_pcie_ep_उठाओ_msix_irq(ep, func_no, पूर्णांकerrupt_num);
	शेष:
		dev_err(pci->dev, "UNKNOWN IRQ type\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_epc_features dw_plat_pcie_epc_features = अणु
	.linkup_notअगरier = false,
	.msi_capable = true,
	.msix_capable = true,
पूर्ण;

अटल स्थिर काष्ठा pci_epc_features*
dw_plat_pcie_get_features(काष्ठा dw_pcie_ep *ep)
अणु
	वापस &dw_plat_pcie_epc_features;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ep_ops pcie_ep_ops = अणु
	.ep_init = dw_plat_pcie_ep_init,
	.उठाओ_irq = dw_plat_pcie_ep_उठाओ_irq,
	.get_features = dw_plat_pcie_get_features,
पूर्ण;

अटल पूर्णांक dw_plat_add_pcie_port(काष्ठा dw_plat_pcie *dw_plat_pcie,
				 काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_pcie *pci = dw_plat_pcie->pci;
	काष्ठा pcie_port *pp = &pci->pp;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	pp->irq = platक्रमm_get_irq(pdev, 1);
	अगर (pp->irq < 0)
		वापस pp->irq;

	pp->num_vectors = MAX_MSI_IRQS;
	pp->ops = &dw_plat_pcie_host_ops;

	ret = dw_pcie_host_init(pp);
	अगर (ret) अणु
		dev_err(dev, "Failed to initialize host\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dw_plat_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dw_plat_pcie *dw_plat_pcie;
	काष्ठा dw_pcie *pci;
	पूर्णांक ret;
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा dw_plat_pcie_of_data *data;
	क्रमागत dw_pcie_device_mode mode;

	match = of_match_device(dw_plat_pcie_of_match, dev);
	अगर (!match)
		वापस -EINVAL;

	data = (काष्ठा dw_plat_pcie_of_data *)match->data;
	mode = (क्रमागत dw_pcie_device_mode)data->mode;

	dw_plat_pcie = devm_kzalloc(dev, माप(*dw_plat_pcie), GFP_KERNEL);
	अगर (!dw_plat_pcie)
		वापस -ENOMEM;

	pci = devm_kzalloc(dev, माप(*pci), GFP_KERNEL);
	अगर (!pci)
		वापस -ENOMEM;

	pci->dev = dev;
	pci->ops = &dw_pcie_ops;

	dw_plat_pcie->pci = pci;
	dw_plat_pcie->mode = mode;

	platक्रमm_set_drvdata(pdev, dw_plat_pcie);

	चयन (dw_plat_pcie->mode) अणु
	हाल DW_PCIE_RC_TYPE:
		अगर (!IS_ENABLED(CONFIG_PCIE_DW_PLAT_HOST))
			वापस -ENODEV;

		ret = dw_plat_add_pcie_port(dw_plat_pcie, pdev);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल DW_PCIE_EP_TYPE:
		अगर (!IS_ENABLED(CONFIG_PCIE_DW_PLAT_EP))
			वापस -ENODEV;

		pci->ep.ops = &pcie_ep_ops;
		वापस dw_pcie_ep_init(&pci->ep);
		अवरोध;
	शेष:
		dev_err(dev, "INVALID device type %d\n", dw_plat_pcie->mode);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_plat_pcie_of_data dw_plat_pcie_rc_of_data = अणु
	.mode = DW_PCIE_RC_TYPE,
पूर्ण;

अटल स्थिर काष्ठा dw_plat_pcie_of_data dw_plat_pcie_ep_of_data = अणु
	.mode = DW_PCIE_EP_TYPE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id dw_plat_pcie_of_match[] = अणु
	अणु
		.compatible = "snps,dw-pcie",
		.data = &dw_plat_pcie_rc_of_data,
	पूर्ण,
	अणु
		.compatible = "snps,dw-pcie-ep",
		.data = &dw_plat_pcie_ep_of_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver dw_plat_pcie_driver = अणु
	.driver = अणु
		.name	= "dw-pcie",
		.of_match_table = dw_plat_pcie_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = dw_plat_pcie_probe,
पूर्ण;
builtin_platक्रमm_driver(dw_plat_pcie_driver);
