<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe endpoपूर्णांक controller driver क्रम UniPhier SoCs
 * Copyright 2018 Socionext Inc.
 * Author: Kunihiko Hayashi <hayashi.kunihiko@socionext.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#समावेश "pcie-designware.h"

/* Link Glue रेजिस्टरs */
#घोषणा PCL_RSTCTRL0			0x0010
#घोषणा PCL_RSTCTRL_AXI_REG		BIT(3)
#घोषणा PCL_RSTCTRL_AXI_SLAVE		BIT(2)
#घोषणा PCL_RSTCTRL_AXI_MASTER		BIT(1)
#घोषणा PCL_RSTCTRL_PIPE3		BIT(0)

#घोषणा PCL_RSTCTRL1			0x0020
#घोषणा PCL_RSTCTRL_PERST		BIT(0)

#घोषणा PCL_RSTCTRL2			0x0024
#घोषणा PCL_RSTCTRL_PHY_RESET		BIT(0)

#घोषणा PCL_MODE			0x8000
#घोषणा PCL_MODE_REGEN			BIT(8)
#घोषणा PCL_MODE_REGVAL			BIT(0)

#घोषणा PCL_APP_CLK_CTRL		0x8004
#घोषणा PCL_APP_CLK_REQ			BIT(0)

#घोषणा PCL_APP_READY_CTRL		0x8008
#घोषणा PCL_APP_LTSSM_ENABLE		BIT(0)

#घोषणा PCL_APP_MSI0			0x8040
#घोषणा PCL_APP_VEN_MSI_TC_MASK		GENMASK(10, 8)
#घोषणा PCL_APP_VEN_MSI_VECTOR_MASK	GENMASK(4, 0)

#घोषणा PCL_APP_MSI1			0x8044
#घोषणा PCL_APP_MSI_REQ			BIT(0)

#घोषणा PCL_APP_INTX			0x8074
#घोषणा PCL_APP_INTX_SYS_INT		BIT(0)

/* निश्चितion समय of INTx in usec */
#घोषणा PCL_INTX_WIDTH_USEC		30

काष्ठा uniphier_pcie_ep_priv अणु
	व्योम __iomem *base;
	काष्ठा dw_pcie pci;
	काष्ठा clk *clk, *clk_gio;
	काष्ठा reset_control *rst, *rst_gio;
	काष्ठा phy *phy;
	स्थिर काष्ठा pci_epc_features *features;
पूर्ण;

#घोषणा to_uniphier_pcie(x)	dev_get_drvdata((x)->dev)

अटल व्योम uniphier_pcie_ltssm_enable(काष्ठा uniphier_pcie_ep_priv *priv,
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

अटल व्योम uniphier_pcie_phy_reset(काष्ठा uniphier_pcie_ep_priv *priv,
				    bool निश्चित)
अणु
	u32 val;

	val = पढ़ोl(priv->base + PCL_RSTCTRL2);
	अगर (निश्चित)
		val |= PCL_RSTCTRL_PHY_RESET;
	अन्यथा
		val &= ~PCL_RSTCTRL_PHY_RESET;
	ग_लिखोl(val, priv->base + PCL_RSTCTRL2);
पूर्ण

अटल व्योम uniphier_pcie_init_ep(काष्ठा uniphier_pcie_ep_priv *priv)
अणु
	u32 val;

	/* set EP mode */
	val = पढ़ोl(priv->base + PCL_MODE);
	val |= PCL_MODE_REGEN | PCL_MODE_REGVAL;
	ग_लिखोl(val, priv->base + PCL_MODE);

	/* घड़ी request */
	val = पढ़ोl(priv->base + PCL_APP_CLK_CTRL);
	val &= ~PCL_APP_CLK_REQ;
	ग_लिखोl(val, priv->base + PCL_APP_CLK_CTRL);

	/* deनिश्चित PIPE3 and AXI reset */
	val = पढ़ोl(priv->base + PCL_RSTCTRL0);
	val |= PCL_RSTCTRL_AXI_REG | PCL_RSTCTRL_AXI_SLAVE
		| PCL_RSTCTRL_AXI_MASTER | PCL_RSTCTRL_PIPE3;
	ग_लिखोl(val, priv->base + PCL_RSTCTRL0);

	uniphier_pcie_ltssm_enable(priv, false);

	msleep(100);
पूर्ण

अटल पूर्णांक uniphier_pcie_start_link(काष्ठा dw_pcie *pci)
अणु
	काष्ठा uniphier_pcie_ep_priv *priv = to_uniphier_pcie(pci);

	uniphier_pcie_ltssm_enable(priv, true);

	वापस 0;
पूर्ण

अटल व्योम uniphier_pcie_stop_link(काष्ठा dw_pcie *pci)
अणु
	काष्ठा uniphier_pcie_ep_priv *priv = to_uniphier_pcie(pci);

	uniphier_pcie_ltssm_enable(priv, false);
पूर्ण

अटल व्योम uniphier_pcie_ep_init(काष्ठा dw_pcie_ep *ep)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	क्रमागत pci_barno bar;

	क्रम (bar = BAR_0; bar <= BAR_5; bar++)
		dw_pcie_ep_reset_bar(pci, bar);
पूर्ण

अटल पूर्णांक uniphier_pcie_ep_उठाओ_legacy_irq(काष्ठा dw_pcie_ep *ep)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	काष्ठा uniphier_pcie_ep_priv *priv = to_uniphier_pcie(pci);
	u32 val;

	/*
	 * This makes pulse संकेत to send INTx to the RC, so this should
	 * be cleared as soon as possible. This sequence is covered with
	 * mutex in pci_epc_उठाओ_irq().
	 */
	/* निश्चित INTx */
	val = पढ़ोl(priv->base + PCL_APP_INTX);
	val |= PCL_APP_INTX_SYS_INT;
	ग_लिखोl(val, priv->base + PCL_APP_INTX);

	udelay(PCL_INTX_WIDTH_USEC);

	/* deनिश्चित INTx */
	val &= ~PCL_APP_INTX_SYS_INT;
	ग_लिखोl(val, priv->base + PCL_APP_INTX);

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_pcie_ep_उठाओ_msi_irq(काष्ठा dw_pcie_ep *ep,
					  u8 func_no, u16 पूर्णांकerrupt_num)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	काष्ठा uniphier_pcie_ep_priv *priv = to_uniphier_pcie(pci);
	u32 val;

	val = FIELD_PREP(PCL_APP_VEN_MSI_TC_MASK, func_no)
		| FIELD_PREP(PCL_APP_VEN_MSI_VECTOR_MASK, पूर्णांकerrupt_num - 1);
	ग_लिखोl(val, priv->base + PCL_APP_MSI0);

	val = पढ़ोl(priv->base + PCL_APP_MSI1);
	val |= PCL_APP_MSI_REQ;
	ग_लिखोl(val, priv->base + PCL_APP_MSI1);

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_pcie_ep_उठाओ_irq(काष्ठा dw_pcie_ep *ep, u8 func_no,
				      क्रमागत pci_epc_irq_type type,
				      u16 पूर्णांकerrupt_num)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);

	चयन (type) अणु
	हाल PCI_EPC_IRQ_LEGACY:
		वापस uniphier_pcie_ep_उठाओ_legacy_irq(ep);
	हाल PCI_EPC_IRQ_MSI:
		वापस uniphier_pcie_ep_उठाओ_msi_irq(ep, func_no,
						      पूर्णांकerrupt_num);
	शेष:
		dev_err(pci->dev, "UNKNOWN IRQ type (%d)\n", type);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pci_epc_features*
uniphier_pcie_get_features(काष्ठा dw_pcie_ep *ep)
अणु
	काष्ठा dw_pcie *pci = to_dw_pcie_from_ep(ep);
	काष्ठा uniphier_pcie_ep_priv *priv = to_uniphier_pcie(pci);

	वापस priv->features;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ep_ops uniphier_pcie_ep_ops = अणु
	.ep_init = uniphier_pcie_ep_init,
	.उठाओ_irq = uniphier_pcie_ep_उठाओ_irq,
	.get_features = uniphier_pcie_get_features,
पूर्ण;

अटल पूर्णांक uniphier_pcie_ep_enable(काष्ठा uniphier_pcie_ep_priv *priv)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(priv->clk_gio);
	अगर (ret)
		जाओ out_clk_disable;

	ret = reset_control_deनिश्चित(priv->rst);
	अगर (ret)
		जाओ out_clk_gio_disable;

	ret = reset_control_deनिश्चित(priv->rst_gio);
	अगर (ret)
		जाओ out_rst_निश्चित;

	uniphier_pcie_init_ep(priv);

	uniphier_pcie_phy_reset(priv, true);

	ret = phy_init(priv->phy);
	अगर (ret)
		जाओ out_rst_gio_निश्चित;

	uniphier_pcie_phy_reset(priv, false);

	वापस 0;

out_rst_gio_निश्चित:
	reset_control_निश्चित(priv->rst_gio);
out_rst_निश्चित:
	reset_control_निश्चित(priv->rst);
out_clk_gio_disable:
	clk_disable_unprepare(priv->clk_gio);
out_clk_disable:
	clk_disable_unprepare(priv->clk);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dw_pcie_ops dw_pcie_ops = अणु
	.start_link = uniphier_pcie_start_link,
	.stop_link = uniphier_pcie_stop_link,
पूर्ण;

अटल पूर्णांक uniphier_pcie_ep_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा uniphier_pcie_ep_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->features = of_device_get_match_data(dev);
	अगर (WARN_ON(!priv->features))
		वापस -EINVAL;

	priv->pci.dev = dev;
	priv->pci.ops = &dw_pcie_ops;

	priv->base = devm_platक्रमm_ioremap_resource_byname(pdev, "link");
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	priv->clk_gio = devm_clk_get(dev, "gio");
	अगर (IS_ERR(priv->clk_gio))
		वापस PTR_ERR(priv->clk_gio);

	priv->rst_gio = devm_reset_control_get_shared(dev, "gio");
	अगर (IS_ERR(priv->rst_gio))
		वापस PTR_ERR(priv->rst_gio);

	priv->clk = devm_clk_get(dev, "link");
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

	priv->rst = devm_reset_control_get_shared(dev, "link");
	अगर (IS_ERR(priv->rst))
		वापस PTR_ERR(priv->rst);

	priv->phy = devm_phy_optional_get(dev, "pcie-phy");
	अगर (IS_ERR(priv->phy)) अणु
		ret = PTR_ERR(priv->phy);
		dev_err(dev, "Failed to get phy (%d)\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	ret = uniphier_pcie_ep_enable(priv);
	अगर (ret)
		वापस ret;

	priv->pci.ep.ops = &uniphier_pcie_ep_ops;
	वापस dw_pcie_ep_init(&priv->pci.ep);
पूर्ण

अटल स्थिर काष्ठा pci_epc_features uniphier_pro5_data = अणु
	.linkup_notअगरier = false,
	.msi_capable = true,
	.msix_capable = false,
	.align = 1 << 16,
	.bar_fixed_64bit = BIT(BAR_0) | BIT(BAR_2) | BIT(BAR_4),
	.reserved_bar =  BIT(BAR_4),
पूर्ण;

अटल स्थिर काष्ठा of_device_id uniphier_pcie_ep_match[] = अणु
	अणु
		.compatible = "socionext,uniphier-pro5-pcie-ep",
		.data = &uniphier_pro5_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver uniphier_pcie_ep_driver = अणु
	.probe  = uniphier_pcie_ep_probe,
	.driver = अणु
		.name = "uniphier-pcie-ep",
		.of_match_table = uniphier_pcie_ep_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(uniphier_pcie_ep_driver);
