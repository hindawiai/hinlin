<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe controller EP driver क्रम Freescale Layerscape SoCs
 *
 * Copyright (C) 2018 NXP Semiconductor.
 *
 * Author: Xiaowei Bao <xiaowei.bao@nxp.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/resource.h>

#समावेश "pcie-designware.h"

#घोषणा to_ls_pcie_ep(x)	dev_get_drvdata((x)->dev)

काष्ठा ls_pcie_ep_drvdata अणु
	u32				func_offset;
	स्थिर काष्ठा dw_pcie_ep_ops	*ops;
	स्थिर काष्ठा dw_pcie_ops	*dw_pcie_ops;
पूर्ण;

काष्ठा ls_pcie_ep अणु
	काष्ठा dw_pcie			*pci;
	काष्ठा pci_epc_features		*ls_epc;
	स्थिर काष्ठा ls_pcie_ep_drvdata *drvdata;
पूर्ण;

अटल पूर्णांक ls_pcie_establish_link(काष्ठा dw_pcie *pci)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ops dw_ls_pcie_ep_ops = अणु
	.start_link = ls_pcie_establish_link,
पूर्ण;

अटल स्थिर काष्ठा pci_epc_features*
ls_pcie_ep_get_features(काष्ठा dw_pcie_ep *ep)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	काष्ठा ls_pcie_ep *pcie = to_ls_pcie_ep(pci);

	वापस pcie->ls_epc;
पूर्ण

अटल व्योम ls_pcie_ep_init(काष्ठा dw_pcie_ep *ep)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	काष्ठा ls_pcie_ep *pcie = to_ls_pcie_ep(pci);
	काष्ठा dw_pcie_ep_func *ep_func;
	क्रमागत pci_barno bar;

	ep_func = dw_pcie_ep_get_func_from_ep(ep, 0);
	अगर (!ep_func)
		वापस;

	क्रम (bar = 0; bar < PCI_STD_NUM_BARS; bar++)
		dw_pcie_ep_reset_bar(pci, bar);

	pcie->ls_epc->msi_capable = ep_func->msi_cap ? true : false;
	pcie->ls_epc->msix_capable = ep_func->msix_cap ? true : false;
पूर्ण

अटल पूर्णांक ls_pcie_ep_उठाओ_irq(काष्ठा dw_pcie_ep *ep, u8 func_no,
				क्रमागत pci_epc_irq_type type, u16 पूर्णांकerrupt_num)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);

	चयन (type) अणु
	हाल PCI_EPC_IRQ_LEGACY:
		वापस dw_pcie_ep_उठाओ_legacy_irq(ep, func_no);
	हाल PCI_EPC_IRQ_MSI:
		वापस dw_pcie_ep_उठाओ_msi_irq(ep, func_no, पूर्णांकerrupt_num);
	हाल PCI_EPC_IRQ_MSIX:
		वापस dw_pcie_ep_उठाओ_msix_irq_करोorbell(ep, func_no,
							  पूर्णांकerrupt_num);
	शेष:
		dev_err(pci->dev, "UNKNOWN IRQ type\n");
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक ls_pcie_ep_func_conf_select(काष्ठा dw_pcie_ep *ep,
						u8 func_no)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	काष्ठा ls_pcie_ep *pcie = to_ls_pcie_ep(pci);

	WARN_ON(func_no && !pcie->drvdata->func_offset);
	वापस pcie->drvdata->func_offset * func_no;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ep_ops ls_pcie_ep_ops = अणु
	.ep_init = ls_pcie_ep_init,
	.उठाओ_irq = ls_pcie_ep_उठाओ_irq,
	.get_features = ls_pcie_ep_get_features,
	.func_conf_select = ls_pcie_ep_func_conf_select,
पूर्ण;

अटल स्थिर काष्ठा ls_pcie_ep_drvdata ls1_ep_drvdata = अणु
	.ops = &ls_pcie_ep_ops,
	.dw_pcie_ops = &dw_ls_pcie_ep_ops,
पूर्ण;

अटल स्थिर काष्ठा ls_pcie_ep_drvdata ls2_ep_drvdata = अणु
	.func_offset = 0x20000,
	.ops = &ls_pcie_ep_ops,
	.dw_pcie_ops = &dw_ls_pcie_ep_ops,
पूर्ण;

अटल स्थिर काष्ठा ls_pcie_ep_drvdata lx2_ep_drvdata = अणु
	.func_offset = 0x8000,
	.ops = &ls_pcie_ep_ops,
	.dw_pcie_ops = &dw_ls_pcie_ep_ops,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ls_pcie_ep_of_match[] = अणु
	अणु .compatible = "fsl,ls1046a-pcie-ep", .data = &ls1_ep_drvdata पूर्ण,
	अणु .compatible = "fsl,ls1088a-pcie-ep", .data = &ls2_ep_drvdata पूर्ण,
	अणु .compatible = "fsl,ls2088a-pcie-ep", .data = &ls2_ep_drvdata पूर्ण,
	अणु .compatible = "fsl,lx2160ar2-pcie-ep", .data = &lx2_ep_drvdata पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक __init ls_pcie_ep_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dw_pcie *pci;
	काष्ठा ls_pcie_ep *pcie;
	काष्ठा pci_epc_features *ls_epc;
	काष्ठा resource *dbi_base;

	pcie = devm_kzalloc(dev, माप(*pcie), GFP_KERNEL);
	अगर (!pcie)
		वापस -ENOMEM;

	pci = devm_kzalloc(dev, माप(*pci), GFP_KERNEL);
	अगर (!pci)
		वापस -ENOMEM;

	ls_epc = devm_kzalloc(dev, माप(*ls_epc), GFP_KERNEL);
	अगर (!ls_epc)
		वापस -ENOMEM;

	pcie->drvdata = of_device_get_match_data(dev);

	pci->dev = dev;
	pci->ops = pcie->drvdata->dw_pcie_ops;

	ls_epc->bar_fixed_64bit = (1 << BAR_2) | (1 << BAR_4);

	pcie->pci = pci;
	pcie->ls_epc = ls_epc;

	dbi_base = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "regs");
	pci->dbi_base = devm_pci_remap_cfg_resource(dev, dbi_base);
	अगर (IS_ERR(pci->dbi_base))
		वापस PTR_ERR(pci->dbi_base);

	pci->ep.ops = &ls_pcie_ep_ops;

	platक्रमm_set_drvdata(pdev, pcie);

	वापस dw_pcie_ep_init(&pci->ep);
पूर्ण

अटल काष्ठा platक्रमm_driver ls_pcie_ep_driver = अणु
	.driver = अणु
		.name = "layerscape-pcie-ep",
		.of_match_table = ls_pcie_ep_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver_probe(ls_pcie_ep_driver, ls_pcie_ep_probe);
