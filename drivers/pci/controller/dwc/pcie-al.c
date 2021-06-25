<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe host controller driver क्रम Amazon's Annapurna Lअसल IP (used in chips
 * such as Graviton and Alpine)
 *
 * Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Author: Jonathan Chocron <jonnyc@amazon.com>
 */

#समावेश <linux/pci.h>
#समावेश <linux/pci-ecam.h>
#समावेश <linux/pci-acpi.h>
#समावेश "../../pci.h"

#अगर defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIRKS)

काष्ठा al_pcie_acpi  अणु
	व्योम __iomem *dbi_base;
पूर्ण;

अटल व्योम __iomem *al_pcie_map_bus(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				     पूर्णांक where)
अणु
	काष्ठा pci_config_winकरोw *cfg = bus->sysdata;
	काष्ठा al_pcie_acpi *pcie = cfg->priv;
	व्योम __iomem *dbi_base = pcie->dbi_base;

	अगर (bus->number == cfg->busr.start) अणु
		/*
		 * The DW PCIe core करोesn't filter out transactions to other
		 * devices/functions on the root bus num, so we करो this here.
		 */
		अगर (PCI_SLOT(devfn) > 0)
			वापस शून्य;
		अन्यथा
			वापस dbi_base + where;
	पूर्ण

	वापस pci_ecam_map_bus(bus, devfn, where);
पूर्ण

अटल पूर्णांक al_pcie_init(काष्ठा pci_config_winकरोw *cfg)
अणु
	काष्ठा device *dev = cfg->parent;
	काष्ठा acpi_device *adev = to_acpi_device(dev);
	काष्ठा acpi_pci_root *root = acpi_driver_data(adev);
	काष्ठा al_pcie_acpi *al_pcie;
	काष्ठा resource *res;
	पूर्णांक ret;

	al_pcie = devm_kzalloc(dev, माप(*al_pcie), GFP_KERNEL);
	अगर (!al_pcie)
		वापस -ENOMEM;

	res = devm_kzalloc(dev, माप(*res), GFP_KERNEL);
	अगर (!res)
		वापस -ENOMEM;

	ret = acpi_get_rc_resources(dev, "AMZN0001", root->segment, res);
	अगर (ret) अणु
		dev_err(dev, "can't get rc dbi base address for SEG %d\n",
			root->segment);
		वापस ret;
	पूर्ण

	dev_dbg(dev, "Root port dbi res: %pR\n", res);

	al_pcie->dbi_base = devm_pci_remap_cfg_resource(dev, res);
	अगर (IS_ERR(al_pcie->dbi_base))
		वापस PTR_ERR(al_pcie->dbi_base);

	cfg->priv = al_pcie;

	वापस 0;
पूर्ण

स्थिर काष्ठा pci_ecam_ops al_pcie_ops = अणु
	.init         =  al_pcie_init,
	.pci_ops      = अणु
		.map_bus    = al_pcie_map_bus,
		.पढ़ो       = pci_generic_config_पढ़ो,
		.ग_लिखो      = pci_generic_config_ग_लिखो,
	पूर्ण
पूर्ण;

#पूर्ण_अगर /* defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIRKS) */

#अगर_घोषित CONFIG_PCIE_AL

#समावेश <linux/of_pci.h>
#समावेश "pcie-designware.h"

#घोषणा AL_PCIE_REV_ID_2	2
#घोषणा AL_PCIE_REV_ID_3	3
#घोषणा AL_PCIE_REV_ID_4	4

#घोषणा AXI_BASE_OFFSET		0x0

#घोषणा DEVICE_ID_OFFSET	0x16c

#घोषणा DEVICE_REV_ID			0x0
#घोषणा DEVICE_REV_ID_DEV_ID_MASK	GENMASK(31, 16)

#घोषणा DEVICE_REV_ID_DEV_ID_X4		0
#घोषणा DEVICE_REV_ID_DEV_ID_X8		2
#घोषणा DEVICE_REV_ID_DEV_ID_X16	4

#घोषणा OB_CTRL_REV1_2_OFFSET	0x0040
#घोषणा OB_CTRL_REV3_5_OFFSET	0x0030

#घोषणा CFG_TARGET_BUS			0x0
#घोषणा CFG_TARGET_BUS_MASK_MASK	GENMASK(7, 0)
#घोषणा CFG_TARGET_BUS_BUSNUM_MASK	GENMASK(15, 8)

#घोषणा CFG_CONTROL			0x4
#घोषणा CFG_CONTROL_SUBBUS_MASK		GENMASK(15, 8)
#घोषणा CFG_CONTROL_SEC_BUS_MASK	GENMASK(23, 16)

काष्ठा al_pcie_reg_offsets अणु
	अचिन्हित पूर्णांक ob_ctrl;
पूर्ण;

काष्ठा al_pcie_target_bus_cfg अणु
	u8 reg_val;
	u8 reg_mask;
	u8 ecam_mask;
पूर्ण;

काष्ठा al_pcie अणु
	काष्ठा dw_pcie *pci;
	व्योम __iomem *controller_base; /* base of PCIe unit (not DW core) */
	काष्ठा device *dev;
	resource_माप_प्रकार ecam_size;
	अचिन्हित पूर्णांक controller_rev_id;
	काष्ठा al_pcie_reg_offsets reg_offsets;
	काष्ठा al_pcie_target_bus_cfg target_bus_cfg;
पूर्ण;

#घोषणा to_al_pcie(x)		dev_get_drvdata((x)->dev)

अटल अंतरभूत u32 al_pcie_controller_पढ़ोl(काष्ठा al_pcie *pcie, u32 offset)
अणु
	वापस पढ़ोl_relaxed(pcie->controller_base + offset);
पूर्ण

अटल अंतरभूत व्योम al_pcie_controller_ग_लिखोl(काष्ठा al_pcie *pcie, u32 offset,
					     u32 val)
अणु
	ग_लिखोl_relaxed(val, pcie->controller_base + offset);
पूर्ण

अटल पूर्णांक al_pcie_rev_id_get(काष्ठा al_pcie *pcie, अचिन्हित पूर्णांक *rev_id)
अणु
	u32 dev_rev_id_val;
	u32 dev_id_val;

	dev_rev_id_val = al_pcie_controller_पढ़ोl(pcie, AXI_BASE_OFFSET +
						  DEVICE_ID_OFFSET +
						  DEVICE_REV_ID);
	dev_id_val = FIELD_GET(DEVICE_REV_ID_DEV_ID_MASK, dev_rev_id_val);

	चयन (dev_id_val) अणु
	हाल DEVICE_REV_ID_DEV_ID_X4:
		*rev_id = AL_PCIE_REV_ID_2;
		अवरोध;
	हाल DEVICE_REV_ID_DEV_ID_X8:
		*rev_id = AL_PCIE_REV_ID_3;
		अवरोध;
	हाल DEVICE_REV_ID_DEV_ID_X16:
		*rev_id = AL_PCIE_REV_ID_4;
		अवरोध;
	शेष:
		dev_err(pcie->dev, "Unsupported dev_id_val (0x%x)\n",
			dev_id_val);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(pcie->dev, "dev_id_val: 0x%x\n", dev_id_val);

	वापस 0;
पूर्ण

अटल पूर्णांक al_pcie_reg_offsets_set(काष्ठा al_pcie *pcie)
अणु
	चयन (pcie->controller_rev_id) अणु
	हाल AL_PCIE_REV_ID_2:
		pcie->reg_offsets.ob_ctrl = OB_CTRL_REV1_2_OFFSET;
		अवरोध;
	हाल AL_PCIE_REV_ID_3:
	हाल AL_PCIE_REV_ID_4:
		pcie->reg_offsets.ob_ctrl = OB_CTRL_REV3_5_OFFSET;
		अवरोध;
	शेष:
		dev_err(pcie->dev, "Unsupported controller rev_id: 0x%x\n",
			pcie->controller_rev_id);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम al_pcie_target_bus_set(काष्ठा al_pcie *pcie,
					  u8 target_bus,
					  u8 mask_target_bus)
अणु
	u32 reg;

	reg = FIELD_PREP(CFG_TARGET_BUS_MASK_MASK, mask_target_bus) |
	      FIELD_PREP(CFG_TARGET_BUS_BUSNUM_MASK, target_bus);

	al_pcie_controller_ग_लिखोl(pcie, AXI_BASE_OFFSET +
				  pcie->reg_offsets.ob_ctrl + CFG_TARGET_BUS,
				  reg);
पूर्ण

अटल व्योम __iomem *al_pcie_conf_addr_map_bus(काष्ठा pci_bus *bus,
					       अचिन्हित पूर्णांक devfn, पूर्णांक where)
अणु
	काष्ठा pcie_port *pp = bus->sysdata;
	काष्ठा al_pcie *pcie = to_al_pcie(to_dw_pcie_from_pp(pp));
	अचिन्हित पूर्णांक busnr = bus->number;
	काष्ठा al_pcie_target_bus_cfg *target_bus_cfg = &pcie->target_bus_cfg;
	अचिन्हित पूर्णांक busnr_ecam = busnr & target_bus_cfg->ecam_mask;
	अचिन्हित पूर्णांक busnr_reg = busnr & target_bus_cfg->reg_mask;

	अगर (busnr_reg != target_bus_cfg->reg_val) अणु
		dev_dbg(pcie->pci->dev, "Changing target bus busnum val from 0x%x to 0x%x\n",
			target_bus_cfg->reg_val, busnr_reg);
		target_bus_cfg->reg_val = busnr_reg;
		al_pcie_target_bus_set(pcie,
				       target_bus_cfg->reg_val,
				       target_bus_cfg->reg_mask);
	पूर्ण

	वापस pp->va_cfg0_base + PCIE_ECAM_OFFSET(busnr_ecam, devfn, where);
पूर्ण

अटल काष्ठा pci_ops al_child_pci_ops = अणु
	.map_bus = al_pcie_conf_addr_map_bus,
	.पढ़ो = pci_generic_config_पढ़ो,
	.ग_लिखो = pci_generic_config_ग_लिखो,
पूर्ण;

अटल व्योम al_pcie_config_prepare(काष्ठा al_pcie *pcie)
अणु
	काष्ठा al_pcie_target_bus_cfg *target_bus_cfg;
	काष्ठा pcie_port *pp = &pcie->pci->pp;
	अचिन्हित पूर्णांक ecam_bus_mask;
	u32 cfg_control_offset;
	u8 subordinate_bus;
	u8 secondary_bus;
	u32 cfg_control;
	u32 reg;
	काष्ठा resource *bus = resource_list_first_type(&pp->bridge->winकरोws, IORESOURCE_BUS)->res;

	target_bus_cfg = &pcie->target_bus_cfg;

	ecam_bus_mask = (pcie->ecam_size >> PCIE_ECAM_BUS_SHIFT) - 1;
	अगर (ecam_bus_mask > 255) अणु
		dev_warn(pcie->dev, "ECAM window size is larger than 256MB. Cutting off at 256\n");
		ecam_bus_mask = 255;
	पूर्ण

	/* This portion is taken from the transaction address */
	target_bus_cfg->ecam_mask = ecam_bus_mask;
	/* This portion is taken from the cfg_target_bus reg */
	target_bus_cfg->reg_mask = ~target_bus_cfg->ecam_mask;
	target_bus_cfg->reg_val = bus->start & target_bus_cfg->reg_mask;

	al_pcie_target_bus_set(pcie, target_bus_cfg->reg_val,
			       target_bus_cfg->reg_mask);

	secondary_bus = bus->start + 1;
	subordinate_bus = bus->end;

	/* Set the valid values of secondary and subordinate buses */
	cfg_control_offset = AXI_BASE_OFFSET + pcie->reg_offsets.ob_ctrl +
			     CFG_CONTROL;

	cfg_control = al_pcie_controller_पढ़ोl(pcie, cfg_control_offset);

	reg = cfg_control &
	      ~(CFG_CONTROL_SEC_BUS_MASK | CFG_CONTROL_SUBBUS_MASK);

	reg |= FIELD_PREP(CFG_CONTROL_SUBBUS_MASK, subordinate_bus) |
	       FIELD_PREP(CFG_CONTROL_SEC_BUS_MASK, secondary_bus);

	al_pcie_controller_ग_लिखोl(pcie, cfg_control_offset, reg);
पूर्ण

अटल पूर्णांक al_pcie_host_init(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा al_pcie *pcie = to_al_pcie(pci);
	पूर्णांक rc;

	pp->bridge->child_ops = &al_child_pci_ops;

	rc = al_pcie_rev_id_get(pcie, &pcie->controller_rev_id);
	अगर (rc)
		वापस rc;

	rc = al_pcie_reg_offsets_set(pcie);
	अगर (rc)
		वापस rc;

	al_pcie_config_prepare(pcie);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_host_ops al_pcie_host_ops = अणु
	.host_init = al_pcie_host_init,
पूर्ण;

अटल पूर्णांक al_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *controller_res;
	काष्ठा resource *ecam_res;
	काष्ठा al_pcie *al_pcie;
	काष्ठा dw_pcie *pci;

	al_pcie = devm_kzalloc(dev, माप(*al_pcie), GFP_KERNEL);
	अगर (!al_pcie)
		वापस -ENOMEM;

	pci = devm_kzalloc(dev, माप(*pci), GFP_KERNEL);
	अगर (!pci)
		वापस -ENOMEM;

	pci->dev = dev;
	pci->pp.ops = &al_pcie_host_ops;

	al_pcie->pci = pci;
	al_pcie->dev = dev;

	ecam_res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "config");
	अगर (!ecam_res) अणु
		dev_err(dev, "couldn't find 'config' reg in DT\n");
		वापस -ENOENT;
	पूर्ण
	al_pcie->ecam_size = resource_size(ecam_res);

	controller_res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						      "controller");
	al_pcie->controller_base = devm_ioremap_resource(dev, controller_res);
	अगर (IS_ERR(al_pcie->controller_base)) अणु
		dev_err(dev, "couldn't remap controller base %pR\n",
			controller_res);
		वापस PTR_ERR(al_pcie->controller_base);
	पूर्ण

	dev_dbg(dev, "From DT: controller_base: %pR\n", controller_res);

	platक्रमm_set_drvdata(pdev, al_pcie);

	वापस dw_pcie_host_init(&pci->pp);
पूर्ण

अटल स्थिर काष्ठा of_device_id al_pcie_of_match[] = अणु
	अणु .compatible = "amazon,al-alpine-v2-pcie",
	पूर्ण,
	अणु .compatible = "amazon,al-alpine-v3-pcie",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver al_pcie_driver = अणु
	.driver = अणु
		.name	= "al-pcie",
		.of_match_table = al_pcie_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = al_pcie_probe,
पूर्ण;
builtin_platक्रमm_driver(al_pcie_driver);

#पूर्ण_अगर /* CONFIG_PCIE_AL*/
