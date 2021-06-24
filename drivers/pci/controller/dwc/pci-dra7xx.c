<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * pcie-dra7xx - PCIe controller driver क्रम TI DRA7xx SoCs
 *
 * Copyright (C) 2013-2014 Texas Instruments Incorporated - https://www.ti.com
 *
 * Authors: Kishon Vijay Abraham I <kishon@ti.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/resource.h>
#समावेश <linux/types.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/gpio/consumer.h>

#समावेश "../../pci.h"
#समावेश "pcie-designware.h"

/* PCIe controller wrapper DRA7XX configuration रेजिस्टरs */

#घोषणा	PCIECTRL_DRA7XX_CONF_IRQSTATUS_MAIN		0x0024
#घोषणा	PCIECTRL_DRA7XX_CONF_IRQENABLE_SET_MAIN		0x0028
#घोषणा	ERR_SYS						BIT(0)
#घोषणा	ERR_FATAL					BIT(1)
#घोषणा	ERR_NONFATAL					BIT(2)
#घोषणा	ERR_COR						BIT(3)
#घोषणा	ERR_AXI						BIT(4)
#घोषणा	ERR_ECRC					BIT(5)
#घोषणा	PME_TURN_OFF					BIT(8)
#घोषणा	PME_TO_ACK					BIT(9)
#घोषणा	PM_PME						BIT(10)
#घोषणा	LINK_REQ_RST					BIT(11)
#घोषणा	LINK_UP_EVT					BIT(12)
#घोषणा	CFG_BME_EVT					BIT(13)
#घोषणा	CFG_MSE_EVT					BIT(14)
#घोषणा	INTERRUPTS (ERR_SYS | ERR_FATAL | ERR_NONFATAL | ERR_COR | ERR_AXI | \
			ERR_ECRC | PME_TURN_OFF | PME_TO_ACK | PM_PME | \
			LINK_REQ_RST | LINK_UP_EVT | CFG_BME_EVT | CFG_MSE_EVT)

#घोषणा	PCIECTRL_DRA7XX_CONF_IRQSTATUS_MSI		0x0034
#घोषणा	PCIECTRL_DRA7XX_CONF_IRQENABLE_SET_MSI		0x0038
#घोषणा	INTA						BIT(0)
#घोषणा	INTB						BIT(1)
#घोषणा	INTC						BIT(2)
#घोषणा	INTD						BIT(3)
#घोषणा	MSI						BIT(4)
#घोषणा	LEG_EP_INTERRUPTS (INTA | INTB | INTC | INTD)

#घोषणा	PCIECTRL_TI_CONF_DEVICE_TYPE			0x0100
#घोषणा	DEVICE_TYPE_EP					0x0
#घोषणा	DEVICE_TYPE_LEG_EP				0x1
#घोषणा	DEVICE_TYPE_RC					0x4

#घोषणा	PCIECTRL_DRA7XX_CONF_DEVICE_CMD			0x0104
#घोषणा	LTSSM_EN					0x1

#घोषणा	PCIECTRL_DRA7XX_CONF_PHY_CS			0x010C
#घोषणा	LINK_UP						BIT(16)
#घोषणा	DRA7XX_CPU_TO_BUS_ADDR				0x0FFFFFFF

#घोषणा	PCIECTRL_TI_CONF_INTX_ASSERT			0x0124
#घोषणा	PCIECTRL_TI_CONF_INTX_DEASSERT			0x0128

#घोषणा	PCIECTRL_TI_CONF_MSI_XMT			0x012c
#घोषणा MSI_REQ_GRANT					BIT(0)
#घोषणा MSI_VECTOR_SHIFT				7

#घोषणा PCIE_1LANE_2LANE_SELECTION			BIT(13)
#घोषणा PCIE_B1C0_MODE_SEL				BIT(2)
#घोषणा PCIE_B0_B1_TSYNCEN				BIT(0)

काष्ठा dra7xx_pcie अणु
	काष्ठा dw_pcie		*pci;
	व्योम __iomem		*base;		/* DT ti_conf */
	पूर्णांक			phy_count;	/* DT phy-names count */
	काष्ठा phy		**phy;
	काष्ठा irq_करोमुख्य	*irq_करोमुख्य;
	क्रमागत dw_pcie_device_mode mode;
पूर्ण;

काष्ठा dra7xx_pcie_of_data अणु
	क्रमागत dw_pcie_device_mode mode;
	u32 b1co_mode_sel_mask;
पूर्ण;

#घोषणा to_dra7xx_pcie(x)	dev_get_drvdata((x)->dev)

अटल अंतरभूत u32 dra7xx_pcie_पढ़ोl(काष्ठा dra7xx_pcie *pcie, u32 offset)
अणु
	वापस पढ़ोl(pcie->base + offset);
पूर्ण

अटल अंतरभूत व्योम dra7xx_pcie_ग_लिखोl(काष्ठा dra7xx_pcie *pcie, u32 offset,
				      u32 value)
अणु
	ग_लिखोl(value, pcie->base + offset);
पूर्ण

अटल u64 dra7xx_pcie_cpu_addr_fixup(काष्ठा dw_pcie *pci, u64 pci_addr)
अणु
	वापस pci_addr & DRA7XX_CPU_TO_BUS_ADDR;
पूर्ण

अटल पूर्णांक dra7xx_pcie_link_up(काष्ठा dw_pcie *pci)
अणु
	काष्ठा dra7xx_pcie *dra7xx = to_dra7xx_pcie(pci);
	u32 reg = dra7xx_pcie_पढ़ोl(dra7xx, PCIECTRL_DRA7XX_CONF_PHY_CS);

	वापस !!(reg & LINK_UP);
पूर्ण

अटल व्योम dra7xx_pcie_stop_link(काष्ठा dw_pcie *pci)
अणु
	काष्ठा dra7xx_pcie *dra7xx = to_dra7xx_pcie(pci);
	u32 reg;

	reg = dra7xx_pcie_पढ़ोl(dra7xx, PCIECTRL_DRA7XX_CONF_DEVICE_CMD);
	reg &= ~LTSSM_EN;
	dra7xx_pcie_ग_लिखोl(dra7xx, PCIECTRL_DRA7XX_CONF_DEVICE_CMD, reg);
पूर्ण

अटल पूर्णांक dra7xx_pcie_establish_link(काष्ठा dw_pcie *pci)
अणु
	काष्ठा dra7xx_pcie *dra7xx = to_dra7xx_pcie(pci);
	काष्ठा device *dev = pci->dev;
	u32 reg;

	अगर (dw_pcie_link_up(pci)) अणु
		dev_err(dev, "link is already up\n");
		वापस 0;
	पूर्ण

	reg = dra7xx_pcie_पढ़ोl(dra7xx, PCIECTRL_DRA7XX_CONF_DEVICE_CMD);
	reg |= LTSSM_EN;
	dra7xx_pcie_ग_लिखोl(dra7xx, PCIECTRL_DRA7XX_CONF_DEVICE_CMD, reg);

	वापस 0;
पूर्ण

अटल व्योम dra7xx_pcie_enable_msi_पूर्णांकerrupts(काष्ठा dra7xx_pcie *dra7xx)
अणु
	dra7xx_pcie_ग_लिखोl(dra7xx, PCIECTRL_DRA7XX_CONF_IRQSTATUS_MSI,
			   LEG_EP_INTERRUPTS | MSI);

	dra7xx_pcie_ग_लिखोl(dra7xx,
			   PCIECTRL_DRA7XX_CONF_IRQENABLE_SET_MSI,
			   MSI | LEG_EP_INTERRUPTS);
पूर्ण

अटल व्योम dra7xx_pcie_enable_wrapper_पूर्णांकerrupts(काष्ठा dra7xx_pcie *dra7xx)
अणु
	dra7xx_pcie_ग_लिखोl(dra7xx, PCIECTRL_DRA7XX_CONF_IRQSTATUS_MAIN,
			   INTERRUPTS);
	dra7xx_pcie_ग_लिखोl(dra7xx, PCIECTRL_DRA7XX_CONF_IRQENABLE_SET_MAIN,
			   INTERRUPTS);
पूर्ण

अटल व्योम dra7xx_pcie_enable_पूर्णांकerrupts(काष्ठा dra7xx_pcie *dra7xx)
अणु
	dra7xx_pcie_enable_wrapper_पूर्णांकerrupts(dra7xx);
	dra7xx_pcie_enable_msi_पूर्णांकerrupts(dra7xx);
पूर्ण

अटल पूर्णांक dra7xx_pcie_host_init(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा dra7xx_pcie *dra7xx = to_dra7xx_pcie(pci);

	dra7xx_pcie_enable_पूर्णांकerrupts(dra7xx);

	वापस 0;
पूर्ण

अटल पूर्णांक dra7xx_pcie_पूर्णांकx_map(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq,
				irq_hw_number_t hwirq)
अणु
	irq_set_chip_and_handler(irq, &dummy_irq_chip, handle_simple_irq);
	irq_set_chip_data(irq, करोमुख्य->host_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops पूर्णांकx_करोमुख्य_ops = अणु
	.map = dra7xx_pcie_पूर्णांकx_map,
	.xlate = pci_irqd_पूर्णांकx_xlate,
पूर्ण;

अटल पूर्णांक dra7xx_pcie_handle_msi(काष्ठा pcie_port *pp, पूर्णांक index)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	अचिन्हित दीर्घ val;
	पूर्णांक pos, irq;

	val = dw_pcie_पढ़ोl_dbi(pci, PCIE_MSI_INTR0_STATUS +
				   (index * MSI_REG_CTRL_BLOCK_SIZE));
	अगर (!val)
		वापस 0;

	pos = find_next_bit(&val, MAX_MSI_IRQS_PER_CTRL, 0);
	जबतक (pos != MAX_MSI_IRQS_PER_CTRL) अणु
		irq = irq_find_mapping(pp->irq_करोमुख्य,
				       (index * MAX_MSI_IRQS_PER_CTRL) + pos);
		generic_handle_irq(irq);
		pos++;
		pos = find_next_bit(&val, MAX_MSI_IRQS_PER_CTRL, pos);
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम dra7xx_pcie_handle_msi_irq(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	पूर्णांक ret, i, count, num_ctrls;

	num_ctrls = pp->num_vectors / MAX_MSI_IRQS_PER_CTRL;

	/**
	 * Need to make sure all MSI status bits पढ़ो 0 beक्रमe निकासing.
	 * Else, new MSI IRQs are not रेजिस्टरed by the wrapper. Have an
	 * upperbound क्रम the loop and निकास the IRQ in हाल of IRQ flood
	 * to aव्योम locking up प्रणाली in पूर्णांकerrupt context.
	 */
	count = 0;
	करो अणु
		ret = 0;

		क्रम (i = 0; i < num_ctrls; i++)
			ret |= dra7xx_pcie_handle_msi(pp, i);
		count++;
	पूर्ण जबतक (ret && count <= 1000);

	अगर (count > 1000)
		dev_warn_ratelimited(pci->dev,
				     "Too many MSI IRQs to handle\n");
पूर्ण

अटल व्योम dra7xx_pcie_msi_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा dra7xx_pcie *dra7xx;
	काष्ठा dw_pcie *pci;
	काष्ठा pcie_port *pp;
	अचिन्हित दीर्घ reg;
	u32 virq, bit;

	chained_irq_enter(chip, desc);

	pp = irq_desc_get_handler_data(desc);
	pci = to_dw_pcie_from_pp(pp);
	dra7xx = to_dra7xx_pcie(pci);

	reg = dra7xx_pcie_पढ़ोl(dra7xx, PCIECTRL_DRA7XX_CONF_IRQSTATUS_MSI);
	dra7xx_pcie_ग_लिखोl(dra7xx, PCIECTRL_DRA7XX_CONF_IRQSTATUS_MSI, reg);

	चयन (reg) अणु
	हाल MSI:
		dra7xx_pcie_handle_msi_irq(pp);
		अवरोध;
	हाल INTA:
	हाल INTB:
	हाल INTC:
	हाल INTD:
		क्रम_each_set_bit(bit, &reg, PCI_NUM_INTX) अणु
			virq = irq_find_mapping(dra7xx->irq_करोमुख्य, bit);
			अगर (virq)
				generic_handle_irq(virq);
		पूर्ण
		अवरोध;
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल irqवापस_t dra7xx_pcie_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा dra7xx_pcie *dra7xx = arg;
	काष्ठा dw_pcie *pci = dra7xx->pci;
	काष्ठा device *dev = pci->dev;
	काष्ठा dw_pcie_ep *ep = &pci->ep;
	u32 reg;

	reg = dra7xx_pcie_पढ़ोl(dra7xx, PCIECTRL_DRA7XX_CONF_IRQSTATUS_MAIN);

	अगर (reg & ERR_SYS)
		dev_dbg(dev, "System Error\n");

	अगर (reg & ERR_FATAL)
		dev_dbg(dev, "Fatal Error\n");

	अगर (reg & ERR_NONFATAL)
		dev_dbg(dev, "Non Fatal Error\n");

	अगर (reg & ERR_COR)
		dev_dbg(dev, "Correctable Error\n");

	अगर (reg & ERR_AXI)
		dev_dbg(dev, "AXI tag lookup fatal Error\n");

	अगर (reg & ERR_ECRC)
		dev_dbg(dev, "ECRC Error\n");

	अगर (reg & PME_TURN_OFF)
		dev_dbg(dev,
			"Power Management Event Turn-Off message received\n");

	अगर (reg & PME_TO_ACK)
		dev_dbg(dev,
			"Power Management Turn-Off Ack message received\n");

	अगर (reg & PM_PME)
		dev_dbg(dev, "PM Power Management Event message received\n");

	अगर (reg & LINK_REQ_RST)
		dev_dbg(dev, "Link Request Reset\n");

	अगर (reg & LINK_UP_EVT) अणु
		अगर (dra7xx->mode == DW_PCIE_EP_TYPE)
			dw_pcie_ep_linkup(ep);
		dev_dbg(dev, "Link-up state change\n");
	पूर्ण

	अगर (reg & CFG_BME_EVT)
		dev_dbg(dev, "CFG 'Bus Master Enable' change\n");

	अगर (reg & CFG_MSE_EVT)
		dev_dbg(dev, "CFG 'Memory Space Enable' change\n");

	dra7xx_pcie_ग_लिखोl(dra7xx, PCIECTRL_DRA7XX_CONF_IRQSTATUS_MAIN, reg);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dra7xx_pcie_init_irq_करोमुख्य(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा device *dev = pci->dev;
	काष्ठा dra7xx_pcie *dra7xx = to_dra7xx_pcie(pci);
	काष्ठा device_node *node = dev->of_node;
	काष्ठा device_node *pcie_पूर्णांकc_node =  of_get_next_child(node, शून्य);

	अगर (!pcie_पूर्णांकc_node) अणु
		dev_err(dev, "No PCIe Intc node found\n");
		वापस -ENODEV;
	पूर्ण

	irq_set_chained_handler_and_data(pp->irq, dra7xx_pcie_msi_irq_handler,
					 pp);
	dra7xx->irq_करोमुख्य = irq_करोमुख्य_add_linear(pcie_पूर्णांकc_node, PCI_NUM_INTX,
						   &पूर्णांकx_करोमुख्य_ops, pp);
	of_node_put(pcie_पूर्णांकc_node);
	अगर (!dra7xx->irq_करोमुख्य) अणु
		dev_err(dev, "Failed to get a INTx IRQ domain\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_host_ops dra7xx_pcie_host_ops = अणु
	.host_init = dra7xx_pcie_host_init,
पूर्ण;

अटल व्योम dra7xx_pcie_ep_init(काष्ठा dw_pcie_ep *ep)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	काष्ठा dra7xx_pcie *dra7xx = to_dra7xx_pcie(pci);
	क्रमागत pci_barno bar;

	क्रम (bar = 0; bar < PCI_STD_NUM_BARS; bar++)
		dw_pcie_ep_reset_bar(pci, bar);

	dra7xx_pcie_enable_wrapper_पूर्णांकerrupts(dra7xx);
पूर्ण

अटल व्योम dra7xx_pcie_उठाओ_legacy_irq(काष्ठा dra7xx_pcie *dra7xx)
अणु
	dra7xx_pcie_ग_लिखोl(dra7xx, PCIECTRL_TI_CONF_INTX_ASSERT, 0x1);
	mdelay(1);
	dra7xx_pcie_ग_लिखोl(dra7xx, PCIECTRL_TI_CONF_INTX_DEASSERT, 0x1);
पूर्ण

अटल व्योम dra7xx_pcie_उठाओ_msi_irq(काष्ठा dra7xx_pcie *dra7xx,
				      u8 पूर्णांकerrupt_num)
अणु
	u32 reg;

	reg = (पूर्णांकerrupt_num - 1) << MSI_VECTOR_SHIFT;
	reg |= MSI_REQ_GRANT;
	dra7xx_pcie_ग_लिखोl(dra7xx, PCIECTRL_TI_CONF_MSI_XMT, reg);
पूर्ण

अटल पूर्णांक dra7xx_pcie_उठाओ_irq(काष्ठा dw_pcie_ep *ep, u8 func_no,
				 क्रमागत pci_epc_irq_type type, u16 पूर्णांकerrupt_num)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	काष्ठा dra7xx_pcie *dra7xx = to_dra7xx_pcie(pci);

	चयन (type) अणु
	हाल PCI_EPC_IRQ_LEGACY:
		dra7xx_pcie_उठाओ_legacy_irq(dra7xx);
		अवरोध;
	हाल PCI_EPC_IRQ_MSI:
		dra7xx_pcie_उठाओ_msi_irq(dra7xx, पूर्णांकerrupt_num);
		अवरोध;
	शेष:
		dev_err(pci->dev, "UNKNOWN IRQ type\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_epc_features dra7xx_pcie_epc_features = अणु
	.linkup_notअगरier = true,
	.msi_capable = true,
	.msix_capable = false,
पूर्ण;

अटल स्थिर काष्ठा pci_epc_features*
dra7xx_pcie_get_features(काष्ठा dw_pcie_ep *ep)
अणु
	वापस &dra7xx_pcie_epc_features;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ep_ops pcie_ep_ops = अणु
	.ep_init = dra7xx_pcie_ep_init,
	.उठाओ_irq = dra7xx_pcie_उठाओ_irq,
	.get_features = dra7xx_pcie_get_features,
पूर्ण;

अटल पूर्णांक dra7xx_add_pcie_ep(काष्ठा dra7xx_pcie *dra7xx,
			      काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा dw_pcie_ep *ep;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dw_pcie *pci = dra7xx->pci;

	ep = &pci->ep;
	ep->ops = &pcie_ep_ops;

	pci->dbi_base = devm_platक्रमm_ioremap_resource_byname(pdev, "ep_dbics");
	अगर (IS_ERR(pci->dbi_base))
		वापस PTR_ERR(pci->dbi_base);

	pci->dbi_base2 =
		devm_platक्रमm_ioremap_resource_byname(pdev, "ep_dbics2");
	अगर (IS_ERR(pci->dbi_base2))
		वापस PTR_ERR(pci->dbi_base2);

	ret = dw_pcie_ep_init(ep);
	अगर (ret) अणु
		dev_err(dev, "failed to initialize endpoint\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dra7xx_add_pcie_port(काष्ठा dra7xx_pcie *dra7xx,
				काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा dw_pcie *pci = dra7xx->pci;
	काष्ठा pcie_port *pp = &pci->pp;
	काष्ठा device *dev = pci->dev;

	pp->irq = platक्रमm_get_irq(pdev, 1);
	अगर (pp->irq < 0)
		वापस pp->irq;

	/* MSI IRQ is muxed */
	pp->msi_irq = -ENODEV;

	ret = dra7xx_pcie_init_irq_करोमुख्य(pp);
	अगर (ret < 0)
		वापस ret;

	pci->dbi_base = devm_platक्रमm_ioremap_resource_byname(pdev, "rc_dbics");
	अगर (IS_ERR(pci->dbi_base))
		वापस PTR_ERR(pci->dbi_base);

	pp->ops = &dra7xx_pcie_host_ops;

	ret = dw_pcie_host_init(pp);
	अगर (ret) अणु
		dev_err(dev, "failed to initialize host\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ops dw_pcie_ops = अणु
	.cpu_addr_fixup = dra7xx_pcie_cpu_addr_fixup,
	.start_link = dra7xx_pcie_establish_link,
	.stop_link = dra7xx_pcie_stop_link,
	.link_up = dra7xx_pcie_link_up,
पूर्ण;

अटल व्योम dra7xx_pcie_disable_phy(काष्ठा dra7xx_pcie *dra7xx)
अणु
	पूर्णांक phy_count = dra7xx->phy_count;

	जबतक (phy_count--) अणु
		phy_घातer_off(dra7xx->phy[phy_count]);
		phy_निकास(dra7xx->phy[phy_count]);
	पूर्ण
पूर्ण

अटल पूर्णांक dra7xx_pcie_enable_phy(काष्ठा dra7xx_pcie *dra7xx)
अणु
	पूर्णांक phy_count = dra7xx->phy_count;
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < phy_count; i++) अणु
		ret = phy_set_mode(dra7xx->phy[i], PHY_MODE_PCIE);
		अगर (ret < 0)
			जाओ err_phy;

		ret = phy_init(dra7xx->phy[i]);
		अगर (ret < 0)
			जाओ err_phy;

		ret = phy_घातer_on(dra7xx->phy[i]);
		अगर (ret < 0) अणु
			phy_निकास(dra7xx->phy[i]);
			जाओ err_phy;
		पूर्ण
	पूर्ण

	वापस 0;

err_phy:
	जबतक (--i >= 0) अणु
		phy_घातer_off(dra7xx->phy[i]);
		phy_निकास(dra7xx->phy[i]);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dra7xx_pcie_of_data dra7xx_pcie_rc_of_data = अणु
	.mode = DW_PCIE_RC_TYPE,
पूर्ण;

अटल स्थिर काष्ठा dra7xx_pcie_of_data dra7xx_pcie_ep_of_data = अणु
	.mode = DW_PCIE_EP_TYPE,
पूर्ण;

अटल स्थिर काष्ठा dra7xx_pcie_of_data dra746_pcie_rc_of_data = अणु
	.b1co_mode_sel_mask = BIT(2),
	.mode = DW_PCIE_RC_TYPE,
पूर्ण;

अटल स्थिर काष्ठा dra7xx_pcie_of_data dra726_pcie_rc_of_data = अणु
	.b1co_mode_sel_mask = GENMASK(3, 2),
	.mode = DW_PCIE_RC_TYPE,
पूर्ण;

अटल स्थिर काष्ठा dra7xx_pcie_of_data dra746_pcie_ep_of_data = अणु
	.b1co_mode_sel_mask = BIT(2),
	.mode = DW_PCIE_EP_TYPE,
पूर्ण;

अटल स्थिर काष्ठा dra7xx_pcie_of_data dra726_pcie_ep_of_data = अणु
	.b1co_mode_sel_mask = GENMASK(3, 2),
	.mode = DW_PCIE_EP_TYPE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_dra7xx_pcie_match[] = अणु
	अणु
		.compatible = "ti,dra7-pcie",
		.data = &dra7xx_pcie_rc_of_data,
	पूर्ण,
	अणु
		.compatible = "ti,dra7-pcie-ep",
		.data = &dra7xx_pcie_ep_of_data,
	पूर्ण,
	अणु
		.compatible = "ti,dra746-pcie-rc",
		.data = &dra746_pcie_rc_of_data,
	पूर्ण,
	अणु
		.compatible = "ti,dra726-pcie-rc",
		.data = &dra726_pcie_rc_of_data,
	पूर्ण,
	अणु
		.compatible = "ti,dra746-pcie-ep",
		.data = &dra746_pcie_ep_of_data,
	पूर्ण,
	अणु
		.compatible = "ti,dra726-pcie-ep",
		.data = &dra726_pcie_ep_of_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

/*
 * dra7xx_pcie_unaligned_memaccess: workaround क्रम AM572x/AM571x Errata i870
 * @dra7xx: the dra7xx device where the workaround should be applied
 *
 * Access to the PCIe slave port that are not 32-bit aligned will result
 * in incorrect mapping to TLP Address and Byte enable fields. Thereक्रमe,
 * byte and half-word accesses are not possible to byte offset 0x1, 0x2, or
 * 0x3.
 *
 * To aव्योम this issue set PCIE_SS1_AXI2OCP_LEGACY_MODE_ENABLE to 1.
 */
अटल पूर्णांक dra7xx_pcie_unaligned_memaccess(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा of_phandle_args args;
	काष्ठा regmap *regmap;

	regmap = syscon_regmap_lookup_by_phandle(np,
						 "ti,syscon-unaligned-access");
	अगर (IS_ERR(regmap)) अणु
		dev_dbg(dev, "can't get ti,syscon-unaligned-access\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_parse_phandle_with_fixed_args(np, "ti,syscon-unaligned-access",
					       2, 0, &args);
	अगर (ret) अणु
		dev_err(dev, "failed to parse ti,syscon-unaligned-access\n");
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(regmap, args.args[0], args.args[1],
				 args.args[1]);
	अगर (ret)
		dev_err(dev, "failed to enable unaligned access\n");

	of_node_put(args.np);

	वापस ret;
पूर्ण

अटल पूर्णांक dra7xx_pcie_configure_two_lane(काष्ठा device *dev,
					  u32 b1co_mode_sel_mask)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा regmap *pcie_syscon;
	अचिन्हित पूर्णांक pcie_reg;
	u32 mask;
	u32 val;

	pcie_syscon = syscon_regmap_lookup_by_phandle(np, "ti,syscon-lane-sel");
	अगर (IS_ERR(pcie_syscon)) अणु
		dev_err(dev, "unable to get ti,syscon-lane-sel\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32_index(np, "ti,syscon-lane-sel", 1,
				       &pcie_reg)) अणु
		dev_err(dev, "couldn't get lane selection reg offset\n");
		वापस -EINVAL;
	पूर्ण

	mask = b1co_mode_sel_mask | PCIE_B0_B1_TSYNCEN;
	val = PCIE_B1C0_MODE_SEL | PCIE_B0_B1_TSYNCEN;
	regmap_update_bits(pcie_syscon, pcie_reg, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक dra7xx_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u32 reg;
	पूर्णांक ret;
	पूर्णांक irq;
	पूर्णांक i;
	पूर्णांक phy_count;
	काष्ठा phy **phy;
	काष्ठा device_link **link;
	व्योम __iomem *base;
	काष्ठा dw_pcie *pci;
	काष्ठा dra7xx_pcie *dra7xx;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	अक्षर name[10];
	काष्ठा gpio_desc *reset;
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा dra7xx_pcie_of_data *data;
	क्रमागत dw_pcie_device_mode mode;
	u32 b1co_mode_sel_mask;

	match = of_match_device(of_match_ptr(of_dra7xx_pcie_match), dev);
	अगर (!match)
		वापस -EINVAL;

	data = (काष्ठा dra7xx_pcie_of_data *)match->data;
	mode = (क्रमागत dw_pcie_device_mode)data->mode;
	b1co_mode_sel_mask = data->b1co_mode_sel_mask;

	dra7xx = devm_kzalloc(dev, माप(*dra7xx), GFP_KERNEL);
	अगर (!dra7xx)
		वापस -ENOMEM;

	pci = devm_kzalloc(dev, माप(*pci), GFP_KERNEL);
	अगर (!pci)
		वापस -ENOMEM;

	pci->dev = dev;
	pci->ops = &dw_pcie_ops;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	base = devm_platक्रमm_ioremap_resource_byname(pdev, "ti_conf");
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	phy_count = of_property_count_strings(np, "phy-names");
	अगर (phy_count < 0) अणु
		dev_err(dev, "unable to find the strings\n");
		वापस phy_count;
	पूर्ण

	phy = devm_kसुस्मृति(dev, phy_count, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	link = devm_kसुस्मृति(dev, phy_count, माप(*link), GFP_KERNEL);
	अगर (!link)
		वापस -ENOMEM;

	क्रम (i = 0; i < phy_count; i++) अणु
		snम_लिखो(name, माप(name), "pcie-phy%d", i);
		phy[i] = devm_phy_get(dev, name);
		अगर (IS_ERR(phy[i]))
			वापस PTR_ERR(phy[i]);

		link[i] = device_link_add(dev, &phy[i]->dev, DL_FLAG_STATELESS);
		अगर (!link[i]) अणु
			ret = -EINVAL;
			जाओ err_link;
		पूर्ण
	पूर्ण

	dra7xx->base = base;
	dra7xx->phy = phy;
	dra7xx->pci = pci;
	dra7xx->phy_count = phy_count;

	अगर (phy_count == 2) अणु
		ret = dra7xx_pcie_configure_two_lane(dev, b1co_mode_sel_mask);
		अगर (ret < 0)
			dra7xx->phy_count = 1; /* Fallback to x1 lane mode */
	पूर्ण

	ret = dra7xx_pcie_enable_phy(dra7xx);
	अगर (ret) अणु
		dev_err(dev, "failed to enable phy\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dra7xx);

	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "pm_runtime_get_sync failed\n");
		जाओ err_get_sync;
	पूर्ण

	reset = devm_gpiod_get_optional(dev, शून्य, GPIOD_OUT_HIGH);
	अगर (IS_ERR(reset)) अणु
		ret = PTR_ERR(reset);
		dev_err(&pdev->dev, "gpio request failed, ret %d\n", ret);
		जाओ err_gpio;
	पूर्ण

	reg = dra7xx_pcie_पढ़ोl(dra7xx, PCIECTRL_DRA7XX_CONF_DEVICE_CMD);
	reg &= ~LTSSM_EN;
	dra7xx_pcie_ग_लिखोl(dra7xx, PCIECTRL_DRA7XX_CONF_DEVICE_CMD, reg);

	चयन (mode) अणु
	हाल DW_PCIE_RC_TYPE:
		अगर (!IS_ENABLED(CONFIG_PCI_DRA7XX_HOST)) अणु
			ret = -ENODEV;
			जाओ err_gpio;
		पूर्ण

		dra7xx_pcie_ग_लिखोl(dra7xx, PCIECTRL_TI_CONF_DEVICE_TYPE,
				   DEVICE_TYPE_RC);

		ret = dra7xx_pcie_unaligned_memaccess(dev);
		अगर (ret)
			dev_err(dev, "WA for Errata i870 not applied\n");

		ret = dra7xx_add_pcie_port(dra7xx, pdev);
		अगर (ret < 0)
			जाओ err_gpio;
		अवरोध;
	हाल DW_PCIE_EP_TYPE:
		अगर (!IS_ENABLED(CONFIG_PCI_DRA7XX_EP)) अणु
			ret = -ENODEV;
			जाओ err_gpio;
		पूर्ण

		dra7xx_pcie_ग_लिखोl(dra7xx, PCIECTRL_TI_CONF_DEVICE_TYPE,
				   DEVICE_TYPE_EP);

		ret = dra7xx_pcie_unaligned_memaccess(dev);
		अगर (ret)
			जाओ err_gpio;

		ret = dra7xx_add_pcie_ep(dra7xx, pdev);
		अगर (ret < 0)
			जाओ err_gpio;
		अवरोध;
	शेष:
		dev_err(dev, "INVALID device type %d\n", mode);
	पूर्ण
	dra7xx->mode = mode;

	ret = devm_request_irq(dev, irq, dra7xx_pcie_irq_handler,
			       IRQF_SHARED, "dra7xx-pcie-main", dra7xx);
	अगर (ret) अणु
		dev_err(dev, "failed to request irq\n");
		जाओ err_gpio;
	पूर्ण

	वापस 0;

err_gpio:
err_get_sync:
	pm_runसमय_put(dev);
	pm_runसमय_disable(dev);
	dra7xx_pcie_disable_phy(dra7xx);

err_link:
	जबतक (--i >= 0)
		device_link_del(link[i]);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक dra7xx_pcie_suspend(काष्ठा device *dev)
अणु
	काष्ठा dra7xx_pcie *dra7xx = dev_get_drvdata(dev);
	काष्ठा dw_pcie *pci = dra7xx->pci;
	u32 val;

	अगर (dra7xx->mode != DW_PCIE_RC_TYPE)
		वापस 0;

	/* clear MSE */
	val = dw_pcie_पढ़ोl_dbi(pci, PCI_COMMAND);
	val &= ~PCI_COMMAND_MEMORY;
	dw_pcie_ग_लिखोl_dbi(pci, PCI_COMMAND, val);

	वापस 0;
पूर्ण

अटल पूर्णांक dra7xx_pcie_resume(काष्ठा device *dev)
अणु
	काष्ठा dra7xx_pcie *dra7xx = dev_get_drvdata(dev);
	काष्ठा dw_pcie *pci = dra7xx->pci;
	u32 val;

	अगर (dra7xx->mode != DW_PCIE_RC_TYPE)
		वापस 0;

	/* set MSE */
	val = dw_pcie_पढ़ोl_dbi(pci, PCI_COMMAND);
	val |= PCI_COMMAND_MEMORY;
	dw_pcie_ग_लिखोl_dbi(pci, PCI_COMMAND, val);

	वापस 0;
पूर्ण

अटल पूर्णांक dra7xx_pcie_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा dra7xx_pcie *dra7xx = dev_get_drvdata(dev);

	dra7xx_pcie_disable_phy(dra7xx);

	वापस 0;
पूर्ण

अटल पूर्णांक dra7xx_pcie_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा dra7xx_pcie *dra7xx = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = dra7xx_pcie_enable_phy(dra7xx);
	अगर (ret) अणु
		dev_err(dev, "failed to enable phy\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम dra7xx_pcie_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dra7xx_pcie *dra7xx = dev_get_drvdata(dev);
	पूर्णांक ret;

	dra7xx_pcie_stop_link(dra7xx->pci);

	ret = pm_runसमय_put_sync(dev);
	अगर (ret < 0)
		dev_dbg(dev, "pm_runtime_put_sync failed\n");

	pm_runसमय_disable(dev);
	dra7xx_pcie_disable_phy(dra7xx);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dra7xx_pcie_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(dra7xx_pcie_suspend, dra7xx_pcie_resume)
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(dra7xx_pcie_suspend_noirq,
				      dra7xx_pcie_resume_noirq)
पूर्ण;

अटल काष्ठा platक्रमm_driver dra7xx_pcie_driver = अणु
	.probe = dra7xx_pcie_probe,
	.driver = अणु
		.name	= "dra7-pcie",
		.of_match_table = of_dra7xx_pcie_match,
		.suppress_bind_attrs = true,
		.pm	= &dra7xx_pcie_pm_ops,
	पूर्ण,
	.shutकरोwn = dra7xx_pcie_shutकरोwn,
पूर्ण;
builtin_platक्रमm_driver(dra7xx_pcie_driver);
