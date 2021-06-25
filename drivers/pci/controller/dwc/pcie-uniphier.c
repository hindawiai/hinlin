<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe host controller driver क्रम UniPhier SoCs
 * Copyright 2018 Socionext Inc.
 * Author: Kunihiko Hayashi <hayashi.kunihiko@socionext.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pci.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#समावेश "pcie-designware.h"

#घोषणा PCL_PINCTRL0			0x002c
#घोषणा PCL_PERST_PLDN_REGEN		BIT(12)
#घोषणा PCL_PERST_NOE_REGEN		BIT(11)
#घोषणा PCL_PERST_OUT_REGEN		BIT(8)
#घोषणा PCL_PERST_PLDN_REGVAL		BIT(4)
#घोषणा PCL_PERST_NOE_REGVAL		BIT(3)
#घोषणा PCL_PERST_OUT_REGVAL		BIT(0)

#घोषणा PCL_PIPEMON			0x0044
#घोषणा PCL_PCLK_ALIVE			BIT(15)

#घोषणा PCL_MODE			0x8000
#घोषणा PCL_MODE_REGEN			BIT(8)
#घोषणा PCL_MODE_REGVAL			BIT(0)

#घोषणा PCL_APP_READY_CTRL		0x8008
#घोषणा PCL_APP_LTSSM_ENABLE		BIT(0)

#घोषणा PCL_APP_PM0			0x8078
#घोषणा PCL_SYS_AUX_PWR_DET		BIT(8)

#घोषणा PCL_RCV_INT			0x8108
#घोषणा PCL_RCV_INT_ALL_ENABLE		GENMASK(20, 17)
#घोषणा PCL_CFG_BW_MGT_STATUS		BIT(4)
#घोषणा PCL_CFG_LINK_AUTO_BW_STATUS	BIT(3)
#घोषणा PCL_CFG_AER_RC_ERR_MSI_STATUS	BIT(2)
#घोषणा PCL_CFG_PME_MSI_STATUS		BIT(1)

#घोषणा PCL_RCV_INTX			0x810c
#घोषणा PCL_RCV_INTX_ALL_ENABLE		GENMASK(19, 16)
#घोषणा PCL_RCV_INTX_ALL_MASK		GENMASK(11, 8)
#घोषणा PCL_RCV_INTX_MASK_SHIFT		8
#घोषणा PCL_RCV_INTX_ALL_STATUS		GENMASK(3, 0)
#घोषणा PCL_RCV_INTX_STATUS_SHIFT	0

#घोषणा PCL_STATUS_LINK			0x8140
#घोषणा PCL_RDLH_LINK_UP		BIT(1)
#घोषणा PCL_XMLH_LINK_UP		BIT(0)

काष्ठा uniphier_pcie_priv अणु
	व्योम __iomem *base;
	काष्ठा dw_pcie pci;
	काष्ठा clk *clk;
	काष्ठा reset_control *rst;
	काष्ठा phy *phy;
	काष्ठा irq_करोमुख्य *legacy_irq_करोमुख्य;
पूर्ण;

#घोषणा to_uniphier_pcie(x)	dev_get_drvdata((x)->dev)

अटल व्योम uniphier_pcie_ltssm_enable(काष्ठा uniphier_pcie_priv *priv,
				       bool enable)
अणु
	u32 val;

	val = पढ़ोl(priv->base + PCL_APP_READY_CTRL);
	अगर (enable)
		val |= PCL_APP_LTSSM_ENABLE;
	अन्यथा
		val &= ~PCL_APP_LTSSM_ENABLE;
	ग_लिखोl(val, priv->base + PCL_APP_READY_CTRL);
पूर्ण

अटल व्योम uniphier_pcie_init_rc(काष्ठा uniphier_pcie_priv *priv)
अणु
	u32 val;

	/* set RC MODE */
	val = पढ़ोl(priv->base + PCL_MODE);
	val |= PCL_MODE_REGEN;
	val &= ~PCL_MODE_REGVAL;
	ग_लिखोl(val, priv->base + PCL_MODE);

	/* use auxiliary घातer detection */
	val = पढ़ोl(priv->base + PCL_APP_PM0);
	val |= PCL_SYS_AUX_PWR_DET;
	ग_लिखोl(val, priv->base + PCL_APP_PM0);

	/* निश्चित PERST# */
	val = पढ़ोl(priv->base + PCL_PINCTRL0);
	val &= ~(PCL_PERST_NOE_REGVAL | PCL_PERST_OUT_REGVAL
		 | PCL_PERST_PLDN_REGVAL);
	val |= PCL_PERST_NOE_REGEN | PCL_PERST_OUT_REGEN
		| PCL_PERST_PLDN_REGEN;
	ग_लिखोl(val, priv->base + PCL_PINCTRL0);

	uniphier_pcie_ltssm_enable(priv, false);

	usleep_range(100000, 200000);

	/* deनिश्चित PERST# */
	val = पढ़ोl(priv->base + PCL_PINCTRL0);
	val |= PCL_PERST_OUT_REGVAL | PCL_PERST_OUT_REGEN;
	ग_लिखोl(val, priv->base + PCL_PINCTRL0);
पूर्ण

अटल पूर्णांक uniphier_pcie_रुको_rc(काष्ठा uniphier_pcie_priv *priv)
अणु
	u32 status;
	पूर्णांक ret;

	/* रुको PIPE घड़ी */
	ret = पढ़ोl_poll_समयout(priv->base + PCL_PIPEMON, status,
				 status & PCL_PCLK_ALIVE, 100000, 1000000);
	अगर (ret) अणु
		dev_err(priv->pci.dev,
			"Failed to initialize controller in RC mode\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_pcie_link_up(काष्ठा dw_pcie *pci)
अणु
	काष्ठा uniphier_pcie_priv *priv = to_uniphier_pcie(pci);
	u32 val, mask;

	val = पढ़ोl(priv->base + PCL_STATUS_LINK);
	mask = PCL_RDLH_LINK_UP | PCL_XMLH_LINK_UP;

	वापस (val & mask) == mask;
पूर्ण

अटल पूर्णांक uniphier_pcie_start_link(काष्ठा dw_pcie *pci)
अणु
	काष्ठा uniphier_pcie_priv *priv = to_uniphier_pcie(pci);

	uniphier_pcie_ltssm_enable(priv, true);

	वापस 0;
पूर्ण

अटल व्योम uniphier_pcie_stop_link(काष्ठा dw_pcie *pci)
अणु
	काष्ठा uniphier_pcie_priv *priv = to_uniphier_pcie(pci);

	uniphier_pcie_ltssm_enable(priv, false);
पूर्ण

अटल व्योम uniphier_pcie_irq_enable(काष्ठा uniphier_pcie_priv *priv)
अणु
	ग_लिखोl(PCL_RCV_INT_ALL_ENABLE, priv->base + PCL_RCV_INT);
	ग_लिखोl(PCL_RCV_INTX_ALL_ENABLE, priv->base + PCL_RCV_INTX);
पूर्ण

अटल व्योम uniphier_pcie_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा pcie_port *pp = irq_data_get_irq_chip_data(d);
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा uniphier_pcie_priv *priv = to_uniphier_pcie(pci);
	u32 val;

	val = पढ़ोl(priv->base + PCL_RCV_INTX);
	val &= ~PCL_RCV_INTX_ALL_STATUS;
	val |= BIT(irqd_to_hwirq(d) + PCL_RCV_INTX_STATUS_SHIFT);
	ग_लिखोl(val, priv->base + PCL_RCV_INTX);
पूर्ण

अटल व्योम uniphier_pcie_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा pcie_port *pp = irq_data_get_irq_chip_data(d);
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा uniphier_pcie_priv *priv = to_uniphier_pcie(pci);
	u32 val;

	val = पढ़ोl(priv->base + PCL_RCV_INTX);
	val &= ~PCL_RCV_INTX_ALL_MASK;
	val |= BIT(irqd_to_hwirq(d) + PCL_RCV_INTX_MASK_SHIFT);
	ग_लिखोl(val, priv->base + PCL_RCV_INTX);
पूर्ण

अटल व्योम uniphier_pcie_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा pcie_port *pp = irq_data_get_irq_chip_data(d);
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा uniphier_pcie_priv *priv = to_uniphier_pcie(pci);
	u32 val;

	val = पढ़ोl(priv->base + PCL_RCV_INTX);
	val &= ~PCL_RCV_INTX_ALL_MASK;
	val &= ~BIT(irqd_to_hwirq(d) + PCL_RCV_INTX_MASK_SHIFT);
	ग_लिखोl(val, priv->base + PCL_RCV_INTX);
पूर्ण

अटल काष्ठा irq_chip uniphier_pcie_irq_chip = अणु
	.name = "PCI",
	.irq_ack = uniphier_pcie_irq_ack,
	.irq_mask = uniphier_pcie_irq_mask,
	.irq_unmask = uniphier_pcie_irq_unmask,
पूर्ण;

अटल पूर्णांक uniphier_pcie_पूर्णांकx_map(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq,
				  irq_hw_number_t hwirq)
अणु
	irq_set_chip_and_handler(irq, &uniphier_pcie_irq_chip,
				 handle_level_irq);
	irq_set_chip_data(irq, करोमुख्य->host_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops uniphier_पूर्णांकx_करोमुख्य_ops = अणु
	.map = uniphier_pcie_पूर्णांकx_map,
पूर्ण;

अटल व्योम uniphier_pcie_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा pcie_port *pp = irq_desc_get_handler_data(desc);
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा uniphier_pcie_priv *priv = to_uniphier_pcie(pci);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अचिन्हित दीर्घ reg;
	u32 val, bit, virq;

	/* INT क्रम debug */
	val = पढ़ोl(priv->base + PCL_RCV_INT);

	अगर (val & PCL_CFG_BW_MGT_STATUS)
		dev_dbg(pci->dev, "Link Bandwidth Management Event\n");
	अगर (val & PCL_CFG_LINK_AUTO_BW_STATUS)
		dev_dbg(pci->dev, "Link Autonomous Bandwidth Event\n");
	अगर (val & PCL_CFG_AER_RC_ERR_MSI_STATUS)
		dev_dbg(pci->dev, "Root Error\n");
	अगर (val & PCL_CFG_PME_MSI_STATUS)
		dev_dbg(pci->dev, "PME Interrupt\n");

	ग_लिखोl(val, priv->base + PCL_RCV_INT);

	/* INTx */
	chained_irq_enter(chip, desc);

	val = पढ़ोl(priv->base + PCL_RCV_INTX);
	reg = FIELD_GET(PCL_RCV_INTX_ALL_STATUS, val);

	क्रम_each_set_bit(bit, &reg, PCI_NUM_INTX) अणु
		virq = irq_linear_revmap(priv->legacy_irq_करोमुख्य, bit);
		generic_handle_irq(virq);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक uniphier_pcie_config_legacy_irq(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा uniphier_pcie_priv *priv = to_uniphier_pcie(pci);
	काष्ठा device_node *np = pci->dev->of_node;
	काष्ठा device_node *np_पूर्णांकc;
	पूर्णांक ret = 0;

	np_पूर्णांकc = of_get_child_by_name(np, "legacy-interrupt-controller");
	अगर (!np_पूर्णांकc) अणु
		dev_err(pci->dev, "Failed to get legacy-interrupt-controller node\n");
		वापस -EINVAL;
	पूर्ण

	pp->irq = irq_of_parse_and_map(np_पूर्णांकc, 0);
	अगर (!pp->irq) अणु
		dev_err(pci->dev, "Failed to get an IRQ entry in legacy-interrupt-controller\n");
		ret = -EINVAL;
		जाओ out_put_node;
	पूर्ण

	priv->legacy_irq_करोमुख्य = irq_करोमुख्य_add_linear(np_पूर्णांकc, PCI_NUM_INTX,
						&uniphier_पूर्णांकx_करोमुख्य_ops, pp);
	अगर (!priv->legacy_irq_करोमुख्य) अणु
		dev_err(pci->dev, "Failed to get INTx domain\n");
		ret = -ENODEV;
		जाओ out_put_node;
	पूर्ण

	irq_set_chained_handler_and_data(pp->irq, uniphier_pcie_irq_handler,
					 pp);

out_put_node:
	of_node_put(np_पूर्णांकc);
	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_pcie_host_init(काष्ठा pcie_port *pp)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_pp(pp);
	काष्ठा uniphier_pcie_priv *priv = to_uniphier_pcie(pci);
	पूर्णांक ret;

	ret = uniphier_pcie_config_legacy_irq(pp);
	अगर (ret)
		वापस ret;

	uniphier_pcie_irq_enable(priv);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_host_ops uniphier_pcie_host_ops = अणु
	.host_init = uniphier_pcie_host_init,
पूर्ण;

अटल पूर्णांक uniphier_pcie_host_enable(काष्ठा uniphier_pcie_priv *priv)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	ret = reset_control_deनिश्चित(priv->rst);
	अगर (ret)
		जाओ out_clk_disable;

	uniphier_pcie_init_rc(priv);

	ret = phy_init(priv->phy);
	अगर (ret)
		जाओ out_rst_निश्चित;

	ret = uniphier_pcie_रुको_rc(priv);
	अगर (ret)
		जाओ out_phy_निकास;

	वापस 0;

out_phy_निकास:
	phy_निकास(priv->phy);
out_rst_निश्चित:
	reset_control_निश्चित(priv->rst);
out_clk_disable:
	clk_disable_unprepare(priv->clk);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ops dw_pcie_ops = अणु
	.start_link = uniphier_pcie_start_link,
	.stop_link = uniphier_pcie_stop_link,
	.link_up = uniphier_pcie_link_up,
पूर्ण;

अटल पूर्णांक uniphier_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा uniphier_pcie_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->pci.dev = dev;
	priv->pci.ops = &dw_pcie_ops;

	priv->base = devm_platक्रमm_ioremap_resource_byname(pdev, "link");
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

	priv->rst = devm_reset_control_get_shared(dev, शून्य);
	अगर (IS_ERR(priv->rst))
		वापस PTR_ERR(priv->rst);

	priv->phy = devm_phy_optional_get(dev, "pcie-phy");
	अगर (IS_ERR(priv->phy))
		वापस PTR_ERR(priv->phy);

	platक्रमm_set_drvdata(pdev, priv);

	ret = uniphier_pcie_host_enable(priv);
	अगर (ret)
		वापस ret;

	priv->pci.pp.ops = &uniphier_pcie_host_ops;

	वापस dw_pcie_host_init(&priv->pci.pp);
पूर्ण

अटल स्थिर काष्ठा of_device_id uniphier_pcie_match[] = अणु
	अणु .compatible = "socionext,uniphier-pcie", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver uniphier_pcie_driver = अणु
	.probe  = uniphier_pcie_probe,
	.driver = अणु
		.name = "uniphier-pcie",
		.of_match_table = uniphier_pcie_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(uniphier_pcie_driver);
