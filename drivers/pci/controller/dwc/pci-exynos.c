<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe host controller driver क्रम Samsung Exynos SoCs
 *
 * Copyright (C) 2013-2020 Samsung Electronics Co., Ltd.
 *		https://www.samsung.com
 *
 * Author: Jingoo Han <jg1.han@samsung.com>
 *	   Jaehoon Chung <jh80.chung@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "pcie-designware.h"

#घोषणा to_exynos_pcie(x)	dev_get_drvdata((x)->dev)

/* PCIe ELBI रेजिस्टरs */
#घोषणा PCIE_IRQ_PULSE			0x000
#घोषणा IRQ_INTA_ASSERT			BIT(0)
#घोषणा IRQ_INTB_ASSERT			BIT(2)
#घोषणा IRQ_INTC_ASSERT			BIT(4)
#घोषणा IRQ_INTD_ASSERT			BIT(6)
#घोषणा PCIE_IRQ_LEVEL			0x004
#घोषणा PCIE_IRQ_SPECIAL		0x008
#घोषणा PCIE_IRQ_EN_PULSE		0x00c
#घोषणा PCIE_IRQ_EN_LEVEL		0x010
#घोषणा PCIE_IRQ_EN_SPECIAL		0x014
#घोषणा PCIE_SW_WAKE			0x018
#घोषणा PCIE_BUS_EN			BIT(1)
#घोषणा PCIE_CORE_RESET			0x01c
#घोषणा PCIE_CORE_RESET_ENABLE		BIT(0)
#घोषणा PCIE_STICKY_RESET		0x020
#घोषणा PCIE_NONSTICKY_RESET		0x024
#घोषणा PCIE_APP_INIT_RESET		0x028
#घोषणा PCIE_APP_LTSSM_ENABLE		0x02c
#घोषणा PCIE_ELBI_RDLH_LINKUP		0x074
#घोषणा PCIE_ELBI_XMLH_LINKUP		BIT(4)
#घोषणा PCIE_ELBI_LTSSM_ENABLE		0x1
#घोषणा PCIE_ELBI_SLV_AWMISC		0x11c
#घोषणा PCIE_ELBI_SLV_ARMISC		0x120
#घोषणा PCIE_ELBI_SLV_DBI_ENABLE	BIT(21)

काष्ठा exynos_pcie अणु
	काष्ठा dw_pcie			pci;
	व्योम __iomem			*elbi_base;
	काष्ठा clk			*clk;
	काष्ठा clk			*bus_clk;
	काष्ठा phy			*phy;
	काष्ठा regulator_bulk_data	supplies[2];
पूर्ण;

अटल पूर्णांक exynos_pcie_init_clk_resources(काष्ठा exynos_pcie *ep)
अणु
	काष्ठा device *dev = ep->pci.dev;
	पूर्णांक ret;

	ret = clk_prepare_enable(ep->clk);
	अगर (ret) अणु
		dev_err(dev, "cannot enable pcie rc clock");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(ep->bus_clk);
	अगर (ret) अणु
		dev_err(dev, "cannot enable pcie bus clock");
		जाओ err_bus_clk;
	पूर्ण

	वापस 0;

err_bus_clk:
	clk_disable_unprepare(ep->clk);

	वापस ret;
पूर्ण

अटल व्योम exynos_pcie_deinit_clk_resources(काष्ठा exynos_pcie *ep)
अणु
	clk_disable_unprepare(ep->bus_clk);
	clk_disable_unprepare(ep->clk);
पूर्ण

अटल व्योम exynos_pcie_ग_लिखोl(व्योम __iomem *base, u32 val, u32 reg)
अणु
	ग_लिखोl(val, base + reg);
पूर्ण

अटल u32 exynos_pcie_पढ़ोl(व्योम __iomem *base, u32 reg)
अणु
	वापस पढ़ोl(base + reg);
पूर्ण

अटल व्योम exynos_pcie_sideband_dbi_w_mode(काष्ठा exynos_pcie *ep, bool on)
अणु
	u32 val;

	val = exynos_pcie_पढ़ोl(ep->elbi_base, PCIE_ELBI_SLV_AWMISC);
	अगर (on)
		val |= PCIE_ELBI_SLV_DBI_ENABLE;
	अन्यथा
		val &= ~PCIE_ELBI_SLV_DBI_ENABLE;
	exynos_pcie_ग_लिखोl(ep->elbi_base, val, PCIE_ELBI_SLV_AWMISC);
पूर्ण

अटल व्योम exynos_pcie_sideband_dbi_r_mode(काष्ठा exynos_pcie *ep, bool on)
अणु
	u32 val;

	val = exynos_pcie_पढ़ोl(ep->elbi_base, PCIE_ELBI_SLV_ARMISC);
	अगर (on)
		val |= PCIE_ELBI_SLV_DBI_ENABLE;
	अन्यथा
		val &= ~PCIE_ELBI_SLV_DBI_ENABLE;
	exynos_pcie_ग_लिखोl(ep->elbi_base, val, PCIE_ELBI_SLV_ARMISC);
पूर्ण

अटल व्योम exynos_pcie_निश्चित_core_reset(काष्ठा exynos_pcie *ep)
अणु
	u32 val;

	val = exynos_pcie_पढ़ोl(ep->elbi_base, PCIE_CORE_RESET);
	val &= ~PCIE_CORE_RESET_ENABLE;
	exynos_pcie_ग_लिखोl(ep->elbi_base, val, PCIE_CORE_RESET);
	exynos_pcie_ग_लिखोl(ep->elbi_base, 0, PCIE_STICKY_RESET);
	exynos_pcie_ग_लिखोl(ep->elbi_base, 0, PCIE_NONSTICKY_RESET);
पूर्ण

अटल व्योम exynos_pcie_deनिश्चित_core_reset(काष्ठा exynos_pcie *ep)
अणु
	u32 val;

	val = exynos_pcie_पढ़ोl(ep->elbi_base, PCIE_CORE_RESET);
	val |= PCIE_CORE_RESET_ENABLE;

	exynos_pcie_ग_लिखोl(ep->elbi_base, val, PCIE_CORE_RESET);
	exynos_pcie_ग_लिखोl(ep->elbi_base, 1, PCIE_STICKY_RESET);
	exynos_pcie_ग_लिखोl(ep->elbi_base, 1, PCIE_NONSTICKY_RESET);
	exynos_pcie_ग_लिखोl(ep->elbi_base, 1, PCIE_APP_INIT_RESET);
	exynos_pcie_ग_लिखोl(ep->elbi_base, 0, PCIE_APP_INIT_RESET);
पूर्ण

अटल पूर्णांक exynos_pcie_start_link(काष्ठा dw_pcie *pci)
अणु
	काष्ठा exynos_pcie *ep = to_exynos_pcie(pci);
	u32 val;

	val = exynos_pcie_पढ़ोl(ep->elbi_base, PCIE_SW_WAKE);
	val &= ~PCIE_BUS_EN;
	exynos_pcie_ग_लिखोl(ep->elbi_base, val, PCIE_SW_WAKE);

	/* निश्चित LTSSM enable */
	exynos_pcie_ग_लिखोl(ep->elbi_base, PCIE_ELBI_LTSSM_ENABLE,
			  PCIE_APP_LTSSM_ENABLE);
	वापस 0;
पूर्ण

अटल व्योम exynos_pcie_clear_irq_pulse(काष्ठा exynos_pcie *ep)
अणु
	u32 val = exynos_pcie_पढ़ोl(ep->elbi_base, PCIE_IRQ_PULSE);

	exynos_pcie_ग_लिखोl(ep->elbi_base, val, PCIE_IRQ_PULSE);
पूर्ण

अटल irqवापस_t exynos_pcie_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा exynos_pcie *ep = arg;

	exynos_pcie_clear_irq_pulse(ep);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम exynos_pcie_enable_irq_pulse(काष्ठा exynos_pcie *ep)
अणु
	u32 val = IRQ_INTA_ASSERT | IRQ_INTB_ASSERT |
		  IRQ_INTC_ASSERT | IRQ_INTD_ASSERT;

	exynos_pcie_ग_लिखोl(ep->elbi_base, val, PCIE_IRQ_EN_PULSE);
	exynos_pcie_ग_लिखोl(ep->elbi_base, 0, PCIE_IRQ_EN_LEVEL);
	exynos_pcie_ग_लिखोl(ep->elbi_base, 0, PCIE_IRQ_EN_SPECIAL);
पूर्ण

अटल u32 exynos_pcie_पढ़ो_dbi(काष्ठा dw_pcie *pci, व्योम __iomem *base,
				u32 reg, माप_प्रकार size)
अणु
	काष्ठा exynos_pcie *ep = to_exynos_pcie(pci);
	u32 val;

	exynos_pcie_sideband_dbi_r_mode(ep, true);
	dw_pcie_पढ़ो(base + reg, size, &val);
	exynos_pcie_sideband_dbi_r_mode(ep, false);
	वापस val;
पूर्ण

अटल व्योम exynos_pcie_ग_लिखो_dbi(काष्ठा dw_pcie *pci, व्योम __iomem *base,
				  u32 reg, माप_प्रकार size, u32 val)
अणु
	काष्ठा exynos_pcie *ep = to_exynos_pcie(pci);

	exynos_pcie_sideband_dbi_w_mode(ep, true);
	dw_pcie_ग_लिखो(base + reg, size, val);
	exynos_pcie_sideband_dbi_w_mode(ep, false);
पूर्ण

अटल पूर्णांक exynos_pcie_rd_own_conf(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				   पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(bus->sysdata);

	अगर (PCI_SLOT(devfn)) अणु
		*val = ~0;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	*val = dw_pcie_पढ़ो_dbi(pci, where, size);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक exynos_pcie_wr_own_conf(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				   पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(bus->sysdata);

	अगर (PCI_SLOT(devfn))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	dw_pcie_ग_लिखो_dbi(pci, where, size, val);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल काष्ठा pci_ops exynos_pci_ops = अणु
	.पढ़ो = exynos_pcie_rd_own_conf,
	.ग_लिखो = exynos_pcie_wr_own_conf,
पूर्ण;

अटल पूर्णांक exynos_pcie_link_up(काष्ठा dw_pcie *pci)
अणु
	काष्ठा exynos_pcie *ep = to_exynos_pcie(pci);
	u32 val = exynos_pcie_पढ़ोl(ep->elbi_base, PCIE_ELBI_RDLH_LINKUP);

	वापस (val & PCIE_ELBI_XMLH_LINKUP);
पूर्ण

अटल पूर्णांक exynos_pcie_host_init(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा exynos_pcie *ep = to_exynos_pcie(pci);

	pp->bridge->ops = &exynos_pci_ops;

	exynos_pcie_निश्चित_core_reset(ep);

	phy_reset(ep->phy);
	phy_घातer_on(ep->phy);
	phy_init(ep->phy);

	exynos_pcie_deनिश्चित_core_reset(ep);
	exynos_pcie_enable_irq_pulse(ep);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_host_ops exynos_pcie_host_ops = अणु
	.host_init = exynos_pcie_host_init,
पूर्ण;

अटल पूर्णांक exynos_add_pcie_port(काष्ठा exynos_pcie *ep,
				       काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_pcie *pci = &ep->pci;
	काष्ठा pcie_port *pp = &pci->pp;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	pp->irq = platक्रमm_get_irq(pdev, 0);
	अगर (pp->irq < 0)
		वापस pp->irq;

	ret = devm_request_irq(dev, pp->irq, exynos_pcie_irq_handler,
			       IRQF_SHARED, "exynos-pcie", ep);
	अगर (ret) अणु
		dev_err(dev, "failed to request irq\n");
		वापस ret;
	पूर्ण

	pp->ops = &exynos_pcie_host_ops;
	pp->msi_irq = -ENODEV;

	ret = dw_pcie_host_init(pp);
	अगर (ret) अणु
		dev_err(dev, "failed to initialize host\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ops dw_pcie_ops = अणु
	.पढ़ो_dbi = exynos_pcie_पढ़ो_dbi,
	.ग_लिखो_dbi = exynos_pcie_ग_लिखो_dbi,
	.link_up = exynos_pcie_link_up,
	.start_link = exynos_pcie_start_link,
पूर्ण;

अटल पूर्णांक exynos_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा exynos_pcie *ep;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;

	ep = devm_kzalloc(dev, माप(*ep), GFP_KERNEL);
	अगर (!ep)
		वापस -ENOMEM;

	ep->pci.dev = dev;
	ep->pci.ops = &dw_pcie_ops;

	ep->phy = devm_of_phy_get(dev, np, शून्य);
	अगर (IS_ERR(ep->phy))
		वापस PTR_ERR(ep->phy);

	/* External Local Bus पूर्णांकerface (ELBI) रेजिस्टरs */
	ep->elbi_base = devm_platक्रमm_ioremap_resource_byname(pdev, "elbi");
	अगर (IS_ERR(ep->elbi_base))
		वापस PTR_ERR(ep->elbi_base);

	ep->clk = devm_clk_get(dev, "pcie");
	अगर (IS_ERR(ep->clk)) अणु
		dev_err(dev, "Failed to get pcie rc clock\n");
		वापस PTR_ERR(ep->clk);
	पूर्ण

	ep->bus_clk = devm_clk_get(dev, "pcie_bus");
	अगर (IS_ERR(ep->bus_clk)) अणु
		dev_err(dev, "Failed to get pcie bus clock\n");
		वापस PTR_ERR(ep->bus_clk);
	पूर्ण

	ep->supplies[0].supply = "vdd18";
	ep->supplies[1].supply = "vdd10";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ep->supplies),
				      ep->supplies);
	अगर (ret)
		वापस ret;

	ret = exynos_pcie_init_clk_resources(ep);
	अगर (ret)
		वापस ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(ep->supplies), ep->supplies);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, ep);

	ret = exynos_add_pcie_port(ep, pdev);
	अगर (ret < 0)
		जाओ fail_probe;

	वापस 0;

fail_probe:
	phy_निकास(ep->phy);
	exynos_pcie_deinit_clk_resources(ep);
	regulator_bulk_disable(ARRAY_SIZE(ep->supplies), ep->supplies);

	वापस ret;
पूर्ण

अटल पूर्णांक __निकास exynos_pcie_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_pcie *ep = platक्रमm_get_drvdata(pdev);

	dw_pcie_host_deinit(&ep->pci.pp);
	exynos_pcie_निश्चित_core_reset(ep);
	phy_घातer_off(ep->phy);
	phy_निकास(ep->phy);
	exynos_pcie_deinit_clk_resources(ep);
	regulator_bulk_disable(ARRAY_SIZE(ep->supplies), ep->supplies);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos_pcie_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा exynos_pcie *ep = dev_get_drvdata(dev);

	exynos_pcie_निश्चित_core_reset(ep);
	phy_घातer_off(ep->phy);
	phy_निकास(ep->phy);
	regulator_bulk_disable(ARRAY_SIZE(ep->supplies), ep->supplies);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos_pcie_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा exynos_pcie *ep = dev_get_drvdata(dev);
	काष्ठा dw_pcie *pci = &ep->pci;
	काष्ठा pcie_port *pp = &pci->pp;
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(ep->supplies), ep->supplies);
	अगर (ret)
		वापस ret;

	/* exynos_pcie_host_init controls ep->phy */
	exynos_pcie_host_init(pp);
	dw_pcie_setup_rc(pp);
	exynos_pcie_start_link(pci);
	वापस dw_pcie_रुको_क्रम_link(pci);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops exynos_pcie_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(exynos_pcie_suspend_noirq,
				      exynos_pcie_resume_noirq)
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos_pcie_of_match[] = अणु
	अणु .compatible = "samsung,exynos5433-pcie", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver exynos_pcie_driver = अणु
	.probe		= exynos_pcie_probe,
	.हटाओ		= __निकास_p(exynos_pcie_हटाओ),
	.driver = अणु
		.name	= "exynos-pcie",
		.of_match_table = exynos_pcie_of_match,
		.pm		= &exynos_pcie_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(exynos_pcie_driver);
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(of, exynos_pcie_of_match);
