<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe host controller driver क्रम Freescale Layerscape SoCs
 *
 * Copyright (C) 2014 Freescale Semiconductor.
 *
 * Author: Minghuan Lian <Minghuan.Lian@मुक्तscale.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/resource.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#समावेश "pcie-designware.h"

/* PEX1/2 Misc Ports Status Register */
#घोषणा SCFG_PEXMSCPORTSR(pex_idx)	(0x94 + (pex_idx) * 4)
#घोषणा LTSSM_STATE_SHIFT	20
#घोषणा LTSSM_STATE_MASK	0x3f
#घोषणा LTSSM_PCIE_L0		0x11 /* L0 state */

/* PEX Internal Configuration Registers */
#घोषणा PCIE_STRFMR1		0x71c /* Symbol Timer & Filter Mask Register1 */
#घोषणा PCIE_ABSERR		0x8d0 /* Bridge Slave Error Response Register */
#घोषणा PCIE_ABSERR_SETTING	0x9401 /* Forward error of non-posted request */

#घोषणा PCIE_IATU_NUM		6

काष्ठा ls_pcie_drvdata अणु
	u32 lut_offset;
	u32 ltssm_shअगरt;
	u32 lut_dbg;
	स्थिर काष्ठा dw_pcie_host_ops *ops;
	स्थिर काष्ठा dw_pcie_ops *dw_pcie_ops;
पूर्ण;

काष्ठा ls_pcie अणु
	काष्ठा dw_pcie *pci;
	व्योम __iomem *lut;
	काष्ठा regmap *scfg;
	स्थिर काष्ठा ls_pcie_drvdata *drvdata;
	पूर्णांक index;
पूर्ण;

#घोषणा to_ls_pcie(x)	dev_get_drvdata((x)->dev)

अटल bool ls_pcie_is_bridge(काष्ठा ls_pcie *pcie)
अणु
	काष्ठा dw_pcie *pci = pcie->pci;
	u32 header_type;

	header_type = ioपढ़ो8(pci->dbi_base + PCI_HEADER_TYPE);
	header_type &= 0x7f;

	वापस header_type == PCI_HEADER_TYPE_BRIDGE;
पूर्ण

/* Clear multi-function bit */
अटल व्योम ls_pcie_clear_multअगरunction(काष्ठा ls_pcie *pcie)
अणु
	काष्ठा dw_pcie *pci = pcie->pci;

	ioग_लिखो8(PCI_HEADER_TYPE_BRIDGE, pci->dbi_base + PCI_HEADER_TYPE);
पूर्ण

/* Drop MSG TLP except क्रम Venकरोr MSG */
अटल व्योम ls_pcie_drop_msg_tlp(काष्ठा ls_pcie *pcie)
अणु
	u32 val;
	काष्ठा dw_pcie *pci = pcie->pci;

	val = ioपढ़ो32(pci->dbi_base + PCIE_STRFMR1);
	val &= 0xDFFFFFFF;
	ioग_लिखो32(val, pci->dbi_base + PCIE_STRFMR1);
पूर्ण

अटल पूर्णांक ls1021_pcie_link_up(काष्ठा dw_pcie *pci)
अणु
	u32 state;
	काष्ठा ls_pcie *pcie = to_ls_pcie(pci);

	अगर (!pcie->scfg)
		वापस 0;

	regmap_पढ़ो(pcie->scfg, SCFG_PEXMSCPORTSR(pcie->index), &state);
	state = (state >> LTSSM_STATE_SHIFT) & LTSSM_STATE_MASK;

	अगर (state < LTSSM_PCIE_L0)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक ls_pcie_link_up(काष्ठा dw_pcie *pci)
अणु
	काष्ठा ls_pcie *pcie = to_ls_pcie(pci);
	u32 state;

	state = (ioपढ़ो32(pcie->lut + pcie->drvdata->lut_dbg) >>
		 pcie->drvdata->ltssm_shअगरt) &
		 LTSSM_STATE_MASK;

	अगर (state < LTSSM_PCIE_L0)
		वापस 0;

	वापस 1;
पूर्ण

/* Forward error response of outbound non-posted requests */
अटल व्योम ls_pcie_fix_error_response(काष्ठा ls_pcie *pcie)
अणु
	काष्ठा dw_pcie *pci = pcie->pci;

	ioग_लिखो32(PCIE_ABSERR_SETTING, pci->dbi_base + PCIE_ABSERR);
पूर्ण

अटल पूर्णांक ls_pcie_host_init(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा ls_pcie *pcie = to_ls_pcie(pci);

	ls_pcie_fix_error_response(pcie);

	dw_pcie_dbi_ro_wr_en(pci);
	ls_pcie_clear_multअगरunction(pcie);
	dw_pcie_dbi_ro_wr_dis(pci);

	ls_pcie_drop_msg_tlp(pcie);

	वापस 0;
पूर्ण

अटल पूर्णांक ls1021_pcie_host_init(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा ls_pcie *pcie = to_ls_pcie(pci);
	काष्ठा device *dev = pci->dev;
	u32 index[2];
	पूर्णांक ret;

	pcie->scfg = syscon_regmap_lookup_by_phandle(dev->of_node,
						     "fsl,pcie-scfg");
	अगर (IS_ERR(pcie->scfg)) अणु
		ret = PTR_ERR(pcie->scfg);
		dev_err(dev, "No syscfg phandle specified\n");
		pcie->scfg = शून्य;
		वापस ret;
	पूर्ण

	अगर (of_property_पढ़ो_u32_array(dev->of_node,
				       "fsl,pcie-scfg", index, 2)) अणु
		pcie->scfg = शून्य;
		वापस -EINVAL;
	पूर्ण
	pcie->index = index[1];

	वापस ls_pcie_host_init(pp);
पूर्ण

अटल स्थिर काष्ठा dw_pcie_host_ops ls1021_pcie_host_ops = अणु
	.host_init = ls1021_pcie_host_init,
पूर्ण;

अटल स्थिर काष्ठा dw_pcie_host_ops ls_pcie_host_ops = अणु
	.host_init = ls_pcie_host_init,
पूर्ण;

अटल स्थिर काष्ठा dw_pcie_ops dw_ls1021_pcie_ops = अणु
	.link_up = ls1021_pcie_link_up,
पूर्ण;

अटल स्थिर काष्ठा dw_pcie_ops dw_ls_pcie_ops = अणु
	.link_up = ls_pcie_link_up,
पूर्ण;

अटल स्थिर काष्ठा ls_pcie_drvdata ls1021_drvdata = अणु
	.ops = &ls1021_pcie_host_ops,
	.dw_pcie_ops = &dw_ls1021_pcie_ops,
पूर्ण;

अटल स्थिर काष्ठा ls_pcie_drvdata ls1043_drvdata = अणु
	.lut_offset = 0x10000,
	.ltssm_shअगरt = 24,
	.lut_dbg = 0x7fc,
	.ops = &ls_pcie_host_ops,
	.dw_pcie_ops = &dw_ls_pcie_ops,
पूर्ण;

अटल स्थिर काष्ठा ls_pcie_drvdata ls1046_drvdata = अणु
	.lut_offset = 0x80000,
	.ltssm_shअगरt = 24,
	.lut_dbg = 0x407fc,
	.ops = &ls_pcie_host_ops,
	.dw_pcie_ops = &dw_ls_pcie_ops,
पूर्ण;

अटल स्थिर काष्ठा ls_pcie_drvdata ls2080_drvdata = अणु
	.lut_offset = 0x80000,
	.ltssm_shअगरt = 0,
	.lut_dbg = 0x7fc,
	.ops = &ls_pcie_host_ops,
	.dw_pcie_ops = &dw_ls_pcie_ops,
पूर्ण;

अटल स्थिर काष्ठा ls_pcie_drvdata ls2088_drvdata = अणु
	.lut_offset = 0x80000,
	.ltssm_shअगरt = 0,
	.lut_dbg = 0x407fc,
	.ops = &ls_pcie_host_ops,
	.dw_pcie_ops = &dw_ls_pcie_ops,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ls_pcie_of_match[] = अणु
	अणु .compatible = "fsl,ls1012a-pcie", .data = &ls1046_drvdata पूर्ण,
	अणु .compatible = "fsl,ls1021a-pcie", .data = &ls1021_drvdata पूर्ण,
	अणु .compatible = "fsl,ls1028a-pcie", .data = &ls2088_drvdata पूर्ण,
	अणु .compatible = "fsl,ls1043a-pcie", .data = &ls1043_drvdata पूर्ण,
	अणु .compatible = "fsl,ls1046a-pcie", .data = &ls1046_drvdata पूर्ण,
	अणु .compatible = "fsl,ls2080a-pcie", .data = &ls2080_drvdata पूर्ण,
	अणु .compatible = "fsl,ls2085a-pcie", .data = &ls2080_drvdata पूर्ण,
	अणु .compatible = "fsl,ls2088a-pcie", .data = &ls2088_drvdata पूर्ण,
	अणु .compatible = "fsl,ls1088a-pcie", .data = &ls2088_drvdata पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक ls_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dw_pcie *pci;
	काष्ठा ls_pcie *pcie;
	काष्ठा resource *dbi_base;

	pcie = devm_kzalloc(dev, माप(*pcie), GFP_KERNEL);
	अगर (!pcie)
		वापस -ENOMEM;

	pci = devm_kzalloc(dev, माप(*pci), GFP_KERNEL);
	अगर (!pci)
		वापस -ENOMEM;

	pcie->drvdata = of_device_get_match_data(dev);

	pci->dev = dev;
	pci->ops = pcie->drvdata->dw_pcie_ops;
	pci->pp.ops = pcie->drvdata->ops;

	pcie->pci = pci;

	dbi_base = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "regs");
	pci->dbi_base = devm_pci_remap_cfg_resource(dev, dbi_base);
	अगर (IS_ERR(pci->dbi_base))
		वापस PTR_ERR(pci->dbi_base);

	pcie->lut = pci->dbi_base + pcie->drvdata->lut_offset;

	अगर (!ls_pcie_is_bridge(pcie))
		वापस -ENODEV;

	platक्रमm_set_drvdata(pdev, pcie);

	वापस dw_pcie_host_init(&pci->pp);
पूर्ण

अटल काष्ठा platक्रमm_driver ls_pcie_driver = अणु
	.probe = ls_pcie_probe,
	.driver = अणु
		.name = "layerscape-pcie",
		.of_match_table = ls_pcie_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(ls_pcie_driver);
