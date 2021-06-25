<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe host controller driver क्रम ST Microelectronics SPEAr13xx SoCs
 *
 * SPEAr13xx PCIe Glue Layer Source Code
 *
 * Copyright (C) 2010-2014 ST Microelectronics
 * Pratyush Anand <pratyush.anand@gmail.com>
 * Mohit Kumar <mohit.kumar.dhaka@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/pci.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/resource.h>

#समावेश "pcie-designware.h"

काष्ठा spear13xx_pcie अणु
	काष्ठा dw_pcie		*pci;
	व्योम __iomem		*app_base;
	काष्ठा phy		*phy;
	काष्ठा clk		*clk;
पूर्ण;

काष्ठा pcie_app_reg अणु
	u32	app_ctrl_0;		/* cr0 */
	u32	app_ctrl_1;		/* cr1 */
	u32	app_status_0;		/* cr2 */
	u32	app_status_1;		/* cr3 */
	u32	msg_status;		/* cr4 */
	u32	msg_payload;		/* cr5 */
	u32	पूर्णांक_sts;		/* cr6 */
	u32	पूर्णांक_clr;		/* cr7 */
	u32	पूर्णांक_mask;		/* cr8 */
	u32	mst_bmisc;		/* cr9 */
	u32	phy_ctrl;		/* cr10 */
	u32	phy_status;		/* cr11 */
	u32	cxpl_debug_info_0;	/* cr12 */
	u32	cxpl_debug_info_1;	/* cr13 */
	u32	ven_msg_ctrl_0;		/* cr14 */
	u32	ven_msg_ctrl_1;		/* cr15 */
	u32	ven_msg_data_0;		/* cr16 */
	u32	ven_msg_data_1;		/* cr17 */
	u32	ven_msi_0;		/* cr18 */
	u32	ven_msi_1;		/* cr19 */
	u32	mst_rmisc;		/* cr20 */
पूर्ण;

/* CR0 ID */
#घोषणा APP_LTSSM_ENABLE_ID			3
#घोषणा DEVICE_TYPE_RC				(4 << 25)
#घोषणा MISCTRL_EN_ID				30
#घोषणा REG_TRANSLATION_ENABLE			31

/* CR3 ID */
#घोषणा XMLH_LINK_UP				(1 << 6)

/* CR6 */
#घोषणा MSI_CTRL_INT				(1 << 26)

#घोषणा to_spear13xx_pcie(x)	dev_get_drvdata((x)->dev)

अटल पूर्णांक spear13xx_pcie_start_link(काष्ठा dw_pcie *pci)
अणु
	काष्ठा spear13xx_pcie *spear13xx_pcie = to_spear13xx_pcie(pci);
	काष्ठा pcie_app_reg *app_reg = spear13xx_pcie->app_base;

	/* enable ltssm */
	ग_लिखोl(DEVICE_TYPE_RC | (1 << MISCTRL_EN_ID)
			| (1 << APP_LTSSM_ENABLE_ID)
			| ((u32)1 << REG_TRANSLATION_ENABLE),
			&app_reg->app_ctrl_0);

	वापस 0;
पूर्ण

अटल irqवापस_t spear13xx_pcie_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा spear13xx_pcie *spear13xx_pcie = arg;
	काष्ठा pcie_app_reg *app_reg = spear13xx_pcie->app_base;
	काष्ठा dw_pcie *pci = spear13xx_pcie->pci;
	काष्ठा pcie_port *pp = &pci->pp;
	अचिन्हित पूर्णांक status;

	status = पढ़ोl(&app_reg->पूर्णांक_sts);

	अगर (status & MSI_CTRL_INT) अणु
		BUG_ON(!IS_ENABLED(CONFIG_PCI_MSI));
		dw_handle_msi_irq(pp);
	पूर्ण

	ग_लिखोl(status, &app_reg->पूर्णांक_clr);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम spear13xx_pcie_enable_पूर्णांकerrupts(काष्ठा spear13xx_pcie *spear13xx_pcie)
अणु
	काष्ठा pcie_app_reg *app_reg = spear13xx_pcie->app_base;

	/* Enable MSI पूर्णांकerrupt */
	अगर (IS_ENABLED(CONFIG_PCI_MSI))
		ग_लिखोl(पढ़ोl(&app_reg->पूर्णांक_mask) |
				MSI_CTRL_INT, &app_reg->पूर्णांक_mask);
पूर्ण

अटल पूर्णांक spear13xx_pcie_link_up(काष्ठा dw_pcie *pci)
अणु
	काष्ठा spear13xx_pcie *spear13xx_pcie = to_spear13xx_pcie(pci);
	काष्ठा pcie_app_reg *app_reg = spear13xx_pcie->app_base;

	अगर (पढ़ोl(&app_reg->app_status_1) & XMLH_LINK_UP)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक spear13xx_pcie_host_init(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा spear13xx_pcie *spear13xx_pcie = to_spear13xx_pcie(pci);
	u32 exp_cap_off = dw_pcie_find_capability(pci, PCI_CAP_ID_EXP);
	u32 val;

	spear13xx_pcie->app_base = pci->dbi_base + 0x2000;

	/*
	 * this controller support only 128 bytes पढ़ो size, however its
	 * शेष value in capability रेजिस्टर is 512 bytes. So क्रमce
	 * it to 128 here.
	 */
	val = dw_pcie_पढ़ोw_dbi(pci, exp_cap_off + PCI_EXP_DEVCTL);
	val &= ~PCI_EXP_DEVCTL_READRQ;
	dw_pcie_ग_लिखोw_dbi(pci, exp_cap_off + PCI_EXP_DEVCTL, val);

	dw_pcie_ग_लिखोw_dbi(pci, PCI_VENDOR_ID, 0x104A);
	dw_pcie_ग_लिखोw_dbi(pci, PCI_DEVICE_ID, 0xCD80);

	spear13xx_pcie_enable_पूर्णांकerrupts(spear13xx_pcie);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_host_ops spear13xx_pcie_host_ops = अणु
	.host_init = spear13xx_pcie_host_init,
पूर्ण;

अटल पूर्णांक spear13xx_add_pcie_port(काष्ठा spear13xx_pcie *spear13xx_pcie,
				   काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_pcie *pci = spear13xx_pcie->pci;
	काष्ठा pcie_port *pp = &pci->pp;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	pp->irq = platक्रमm_get_irq(pdev, 0);
	अगर (pp->irq < 0)
		वापस pp->irq;

	ret = devm_request_irq(dev, pp->irq, spear13xx_pcie_irq_handler,
			       IRQF_SHARED | IRQF_NO_THREAD,
			       "spear1340-pcie", spear13xx_pcie);
	अगर (ret) अणु
		dev_err(dev, "failed to request irq %d\n", pp->irq);
		वापस ret;
	पूर्ण

	pp->ops = &spear13xx_pcie_host_ops;
	pp->msi_irq = -ENODEV;

	ret = dw_pcie_host_init(pp);
	अगर (ret) अणु
		dev_err(dev, "failed to initialize host\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ops dw_pcie_ops = अणु
	.link_up = spear13xx_pcie_link_up,
	.start_link = spear13xx_pcie_start_link,
पूर्ण;

अटल पूर्णांक spear13xx_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dw_pcie *pci;
	काष्ठा spear13xx_pcie *spear13xx_pcie;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;

	spear13xx_pcie = devm_kzalloc(dev, माप(*spear13xx_pcie), GFP_KERNEL);
	अगर (!spear13xx_pcie)
		वापस -ENOMEM;

	pci = devm_kzalloc(dev, माप(*pci), GFP_KERNEL);
	अगर (!pci)
		वापस -ENOMEM;

	pci->dev = dev;
	pci->ops = &dw_pcie_ops;

	spear13xx_pcie->pci = pci;

	spear13xx_pcie->phy = devm_phy_get(dev, "pcie-phy");
	अगर (IS_ERR(spear13xx_pcie->phy)) अणु
		ret = PTR_ERR(spear13xx_pcie->phy);
		अगर (ret == -EPROBE_DEFER)
			dev_info(dev, "probe deferred\n");
		अन्यथा
			dev_err(dev, "couldn't get pcie-phy\n");
		वापस ret;
	पूर्ण

	phy_init(spear13xx_pcie->phy);

	spear13xx_pcie->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(spear13xx_pcie->clk)) अणु
		dev_err(dev, "couldn't get clk for pcie\n");
		वापस PTR_ERR(spear13xx_pcie->clk);
	पूर्ण
	ret = clk_prepare_enable(spear13xx_pcie->clk);
	अगर (ret) अणु
		dev_err(dev, "couldn't enable clk for pcie\n");
		वापस ret;
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "st,pcie-is-gen1"))
		pci->link_gen = 1;

	platक्रमm_set_drvdata(pdev, spear13xx_pcie);

	ret = spear13xx_add_pcie_port(spear13xx_pcie, pdev);
	अगर (ret < 0)
		जाओ fail_clk;

	वापस 0;

fail_clk:
	clk_disable_unprepare(spear13xx_pcie->clk);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id spear13xx_pcie_of_match[] = अणु
	अणु .compatible = "st,spear1340-pcie", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver spear13xx_pcie_driver = अणु
	.probe		= spear13xx_pcie_probe,
	.driver = अणु
		.name	= "spear-pcie",
		.of_match_table = of_match_ptr(spear13xx_pcie_of_match),
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(spear13xx_pcie_driver);
