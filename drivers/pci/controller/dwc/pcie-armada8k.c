<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe host controller driver क्रम Marvell Armada-8K SoCs
 *
 * Armada-8K PCIe Glue Layer Source Code
 *
 * Copyright (C) 2016 Marvell Technology Group Ltd.
 *
 * Author: Yehuda Yitshak <yehuday@marvell.com>
 * Author: Shadi Ammouri <shadi@marvell.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/pci.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/resource.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_irq.h>

#समावेश "pcie-designware.h"

#घोषणा ARMADA8K_PCIE_MAX_LANES PCIE_LNK_X4

काष्ठा armada8k_pcie अणु
	काष्ठा dw_pcie *pci;
	काष्ठा clk *clk;
	काष्ठा clk *clk_reg;
	काष्ठा phy *phy[ARMADA8K_PCIE_MAX_LANES];
	अचिन्हित पूर्णांक phy_count;
पूर्ण;

#घोषणा PCIE_VENDOR_REGS_OFFSET		0x8000

#घोषणा PCIE_GLOBAL_CONTROL_REG		(PCIE_VENDOR_REGS_OFFSET + 0x0)
#घोषणा PCIE_APP_LTSSM_EN		BIT(2)
#घोषणा PCIE_DEVICE_TYPE_SHIFT		4
#घोषणा PCIE_DEVICE_TYPE_MASK		0xF
#घोषणा PCIE_DEVICE_TYPE_RC		0x4 /* Root complex */

#घोषणा PCIE_GLOBAL_STATUS_REG		(PCIE_VENDOR_REGS_OFFSET + 0x8)
#घोषणा PCIE_GLB_STS_RDLH_LINK_UP	BIT(1)
#घोषणा PCIE_GLB_STS_PHY_LINK_UP	BIT(9)

#घोषणा PCIE_GLOBAL_INT_CAUSE1_REG	(PCIE_VENDOR_REGS_OFFSET + 0x1C)
#घोषणा PCIE_GLOBAL_INT_MASK1_REG	(PCIE_VENDOR_REGS_OFFSET + 0x20)
#घोषणा PCIE_INT_A_ASSERT_MASK		BIT(9)
#घोषणा PCIE_INT_B_ASSERT_MASK		BIT(10)
#घोषणा PCIE_INT_C_ASSERT_MASK		BIT(11)
#घोषणा PCIE_INT_D_ASSERT_MASK		BIT(12)

#घोषणा PCIE_ARCACHE_TRC_REG		(PCIE_VENDOR_REGS_OFFSET + 0x50)
#घोषणा PCIE_AWCACHE_TRC_REG		(PCIE_VENDOR_REGS_OFFSET + 0x54)
#घोषणा PCIE_ARUSER_REG			(PCIE_VENDOR_REGS_OFFSET + 0x5C)
#घोषणा PCIE_AWUSER_REG			(PCIE_VENDOR_REGS_OFFSET + 0x60)
/*
 * AR/AW Cache शेषs: Normal memory, Write-Back, Read / Write
 * allocate
 */
#घोषणा ARCACHE_DEFAULT_VALUE		0x3511
#घोषणा AWCACHE_DEFAULT_VALUE		0x5311

#घोषणा DOMAIN_OUTER_SHAREABLE		0x2
#घोषणा AX_USER_DOMAIN_MASK		0x3
#घोषणा AX_USER_DOMAIN_SHIFT		4

#घोषणा to_armada8k_pcie(x)	dev_get_drvdata((x)->dev)

अटल व्योम armada8k_pcie_disable_phys(काष्ठा armada8k_pcie *pcie)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARMADA8K_PCIE_MAX_LANES; i++) अणु
		phy_घातer_off(pcie->phy[i]);
		phy_निकास(pcie->phy[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक armada8k_pcie_enable_phys(काष्ठा armada8k_pcie *pcie)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < ARMADA8K_PCIE_MAX_LANES; i++) अणु
		ret = phy_init(pcie->phy[i]);
		अगर (ret)
			वापस ret;

		ret = phy_set_mode_ext(pcie->phy[i], PHY_MODE_PCIE,
				       pcie->phy_count);
		अगर (ret) अणु
			phy_निकास(pcie->phy[i]);
			वापस ret;
		पूर्ण

		ret = phy_घातer_on(pcie->phy[i]);
		अगर (ret) अणु
			phy_निकास(pcie->phy[i]);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक armada8k_pcie_setup_phys(काष्ठा armada8k_pcie *pcie)
अणु
	काष्ठा dw_pcie *pci = pcie->pci;
	काष्ठा device *dev = pci->dev;
	काष्ठा device_node *node = dev->of_node;
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARMADA8K_PCIE_MAX_LANES; i++) अणु
		pcie->phy[i] = devm_of_phy_get_by_index(dev, node, i);
		अगर (IS_ERR(pcie->phy[i])) अणु
			अगर (PTR_ERR(pcie->phy[i]) != -ENODEV)
				वापस PTR_ERR(pcie->phy[i]);

			pcie->phy[i] = शून्य;
			जारी;
		पूर्ण

		pcie->phy_count++;
	पूर्ण

	/* Old bindings miss the PHY handle, so just warn अगर there is no PHY */
	अगर (!pcie->phy_count)
		dev_warn(dev, "No available PHY\n");

	ret = armada8k_pcie_enable_phys(pcie);
	अगर (ret)
		dev_err(dev, "Failed to initialize PHY(s) (%d)\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक armada8k_pcie_link_up(काष्ठा dw_pcie *pci)
अणु
	u32 reg;
	u32 mask = PCIE_GLB_STS_RDLH_LINK_UP | PCIE_GLB_STS_PHY_LINK_UP;

	reg = dw_pcie_पढ़ोl_dbi(pci, PCIE_GLOBAL_STATUS_REG);

	अगर ((reg & mask) == mask)
		वापस 1;

	dev_dbg(pci->dev, "No link detected (Global-Status: 0x%08x).\n", reg);
	वापस 0;
पूर्ण

अटल पूर्णांक armada8k_pcie_start_link(काष्ठा dw_pcie *pci)
अणु
	u32 reg;

	/* Start LTSSM */
	reg = dw_pcie_पढ़ोl_dbi(pci, PCIE_GLOBAL_CONTROL_REG);
	reg |= PCIE_APP_LTSSM_EN;
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_GLOBAL_CONTROL_REG, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक armada8k_pcie_host_init(काष्ठा pcie_port *pp)
अणु
	u32 reg;
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);

	अगर (!dw_pcie_link_up(pci)) अणु
		/* Disable LTSSM state machine to enable configuration */
		reg = dw_pcie_पढ़ोl_dbi(pci, PCIE_GLOBAL_CONTROL_REG);
		reg &= ~(PCIE_APP_LTSSM_EN);
		dw_pcie_ग_लिखोl_dbi(pci, PCIE_GLOBAL_CONTROL_REG, reg);
	पूर्ण

	/* Set the device to root complex mode */
	reg = dw_pcie_पढ़ोl_dbi(pci, PCIE_GLOBAL_CONTROL_REG);
	reg &= ~(PCIE_DEVICE_TYPE_MASK << PCIE_DEVICE_TYPE_SHIFT);
	reg |= PCIE_DEVICE_TYPE_RC << PCIE_DEVICE_TYPE_SHIFT;
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_GLOBAL_CONTROL_REG, reg);

	/* Set the PCIe master AxCache attributes */
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_ARCACHE_TRC_REG, ARCACHE_DEFAULT_VALUE);
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_AWCACHE_TRC_REG, AWCACHE_DEFAULT_VALUE);

	/* Set the PCIe master AxDoमुख्य attributes */
	reg = dw_pcie_पढ़ोl_dbi(pci, PCIE_ARUSER_REG);
	reg &= ~(AX_USER_DOMAIN_MASK << AX_USER_DOMAIN_SHIFT);
	reg |= DOMAIN_OUTER_SHAREABLE << AX_USER_DOMAIN_SHIFT;
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_ARUSER_REG, reg);

	reg = dw_pcie_पढ़ोl_dbi(pci, PCIE_AWUSER_REG);
	reg &= ~(AX_USER_DOMAIN_MASK << AX_USER_DOMAIN_SHIFT);
	reg |= DOMAIN_OUTER_SHAREABLE << AX_USER_DOMAIN_SHIFT;
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_AWUSER_REG, reg);

	/* Enable INT A-D पूर्णांकerrupts */
	reg = dw_pcie_पढ़ोl_dbi(pci, PCIE_GLOBAL_INT_MASK1_REG);
	reg |= PCIE_INT_A_ASSERT_MASK | PCIE_INT_B_ASSERT_MASK |
	       PCIE_INT_C_ASSERT_MASK | PCIE_INT_D_ASSERT_MASK;
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_GLOBAL_INT_MASK1_REG, reg);

	वापस 0;
पूर्ण

अटल irqवापस_t armada8k_pcie_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा armada8k_pcie *pcie = arg;
	काष्ठा dw_pcie *pci = pcie->pci;
	u32 val;

	/*
	 * Interrupts are directly handled by the device driver of the
	 * PCI device. However, they are also latched पूर्णांकo the PCIe
	 * controller, so we simply discard them.
	 */
	val = dw_pcie_पढ़ोl_dbi(pci, PCIE_GLOBAL_INT_CAUSE1_REG);
	dw_pcie_ग_लिखोl_dbi(pci, PCIE_GLOBAL_INT_CAUSE1_REG, val);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_host_ops armada8k_pcie_host_ops = अणु
	.host_init = armada8k_pcie_host_init,
पूर्ण;

अटल पूर्णांक armada8k_add_pcie_port(काष्ठा armada8k_pcie *pcie,
				  काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_pcie *pci = pcie->pci;
	काष्ठा pcie_port *pp = &pci->pp;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	pp->ops = &armada8k_pcie_host_ops;

	pp->irq = platक्रमm_get_irq(pdev, 0);
	अगर (pp->irq < 0)
		वापस pp->irq;

	ret = devm_request_irq(dev, pp->irq, armada8k_pcie_irq_handler,
			       IRQF_SHARED, "armada8k-pcie", pcie);
	अगर (ret) अणु
		dev_err(dev, "failed to request irq %d\n", pp->irq);
		वापस ret;
	पूर्ण

	ret = dw_pcie_host_init(pp);
	अगर (ret) अणु
		dev_err(dev, "failed to initialize host: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ops dw_pcie_ops = अणु
	.link_up = armada8k_pcie_link_up,
	.start_link = armada8k_pcie_start_link,
पूर्ण;

अटल पूर्णांक armada8k_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_pcie *pci;
	काष्ठा armada8k_pcie *pcie;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *base;
	पूर्णांक ret;

	pcie = devm_kzalloc(dev, माप(*pcie), GFP_KERNEL);
	अगर (!pcie)
		वापस -ENOMEM;

	pci = devm_kzalloc(dev, माप(*pci), GFP_KERNEL);
	अगर (!pci)
		वापस -ENOMEM;

	pci->dev = dev;
	pci->ops = &dw_pcie_ops;

	pcie->pci = pci;

	pcie->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(pcie->clk))
		वापस PTR_ERR(pcie->clk);

	ret = clk_prepare_enable(pcie->clk);
	अगर (ret)
		वापस ret;

	pcie->clk_reg = devm_clk_get(dev, "reg");
	अगर (pcie->clk_reg == ERR_PTR(-EPROBE_DEFER)) अणु
		ret = -EPROBE_DEFER;
		जाओ fail;
	पूर्ण
	अगर (!IS_ERR(pcie->clk_reg)) अणु
		ret = clk_prepare_enable(pcie->clk_reg);
		अगर (ret)
			जाओ fail_clkreg;
	पूर्ण

	/* Get the dw-pcie unit configuration/control रेजिस्टरs base. */
	base = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "ctrl");
	pci->dbi_base = devm_pci_remap_cfg_resource(dev, base);
	अगर (IS_ERR(pci->dbi_base)) अणु
		ret = PTR_ERR(pci->dbi_base);
		जाओ fail_clkreg;
	पूर्ण

	ret = armada8k_pcie_setup_phys(pcie);
	अगर (ret)
		जाओ fail_clkreg;

	platक्रमm_set_drvdata(pdev, pcie);

	ret = armada8k_add_pcie_port(pcie, pdev);
	अगर (ret)
		जाओ disable_phy;

	वापस 0;

disable_phy:
	armada8k_pcie_disable_phys(pcie);
fail_clkreg:
	clk_disable_unprepare(pcie->clk_reg);
fail:
	clk_disable_unprepare(pcie->clk);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id armada8k_pcie_of_match[] = अणु
	अणु .compatible = "marvell,armada8k-pcie", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver armada8k_pcie_driver = अणु
	.probe		= armada8k_pcie_probe,
	.driver = अणु
		.name	= "armada8k-pcie",
		.of_match_table = of_match_ptr(armada8k_pcie_of_match),
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(armada8k_pcie_driver);
