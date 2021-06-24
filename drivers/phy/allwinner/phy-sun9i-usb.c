<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Allwinner sun9i USB phy driver
 *
 * Copyright (C) 2014-2015 Chen-Yu Tsai <wens@csie.org>
 *
 * Based on phy-sun4i-usb.c from
 * Hans de Goede <hdegoede@redhat.com>
 *
 * and code from
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/usb/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#घोषणा SUNXI_AHB_INCR16_BURST_EN	BIT(11)
#घोषणा SUNXI_AHB_INCR8_BURST_EN	BIT(10)
#घोषणा SUNXI_AHB_INCR4_BURST_EN	BIT(9)
#घोषणा SUNXI_AHB_INCRX_ALIGN_EN	BIT(8)
#घोषणा SUNXI_ULPI_BYPASS_EN		BIT(0)

/* usb1 HSIC specअगरic bits */
#घोषणा SUNXI_EHCI_HS_FORCE		BIT(20)
#घोषणा SUNXI_HSIC_CONNECT_DET		BIT(17)
#घोषणा SUNXI_HSIC_CONNECT_INT		BIT(16)
#घोषणा SUNXI_HSIC			BIT(1)

काष्ठा sun9i_usb_phy अणु
	काष्ठा phy *phy;
	व्योम __iomem *pmu;
	काष्ठा reset_control *reset;
	काष्ठा clk *clk;
	काष्ठा clk *hsic_clk;
	क्रमागत usb_phy_पूर्णांकerface type;
पूर्ण;

अटल व्योम sun9i_usb_phy_passby(काष्ठा sun9i_usb_phy *phy, पूर्णांक enable)
अणु
	u32 bits, reg_value;

	bits = SUNXI_AHB_INCR16_BURST_EN | SUNXI_AHB_INCR8_BURST_EN |
		SUNXI_AHB_INCR4_BURST_EN | SUNXI_AHB_INCRX_ALIGN_EN |
		SUNXI_ULPI_BYPASS_EN;

	अगर (phy->type == USBPHY_INTERFACE_MODE_HSIC)
		bits |= SUNXI_HSIC | SUNXI_EHCI_HS_FORCE |
			SUNXI_HSIC_CONNECT_DET | SUNXI_HSIC_CONNECT_INT;

	reg_value = पढ़ोl(phy->pmu);

	अगर (enable)
		reg_value |= bits;
	अन्यथा
		reg_value &= ~bits;

	ग_लिखोl(reg_value, phy->pmu);
पूर्ण

अटल पूर्णांक sun9i_usb_phy_init(काष्ठा phy *_phy)
अणु
	काष्ठा sun9i_usb_phy *phy = phy_get_drvdata(_phy);
	पूर्णांक ret;

	ret = clk_prepare_enable(phy->clk);
	अगर (ret)
		जाओ err_clk;

	ret = clk_prepare_enable(phy->hsic_clk);
	अगर (ret)
		जाओ err_hsic_clk;

	ret = reset_control_deनिश्चित(phy->reset);
	अगर (ret)
		जाओ err_reset;

	sun9i_usb_phy_passby(phy, 1);
	वापस 0;

err_reset:
	clk_disable_unprepare(phy->hsic_clk);

err_hsic_clk:
	clk_disable_unprepare(phy->clk);

err_clk:
	वापस ret;
पूर्ण

अटल पूर्णांक sun9i_usb_phy_निकास(काष्ठा phy *_phy)
अणु
	काष्ठा sun9i_usb_phy *phy = phy_get_drvdata(_phy);

	sun9i_usb_phy_passby(phy, 0);
	reset_control_निश्चित(phy->reset);
	clk_disable_unprepare(phy->hsic_clk);
	clk_disable_unprepare(phy->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops sun9i_usb_phy_ops = अणु
	.init		= sun9i_usb_phy_init,
	.निकास		= sun9i_usb_phy_निकास,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक sun9i_usb_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun9i_usb_phy *phy;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा phy_provider *phy_provider;

	phy = devm_kzalloc(dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	phy->type = of_usb_get_phy_mode(np);
	अगर (phy->type == USBPHY_INTERFACE_MODE_HSIC) अणु
		phy->clk = devm_clk_get(dev, "hsic_480M");
		अगर (IS_ERR(phy->clk)) अणु
			dev_err(dev, "failed to get hsic_480M clock\n");
			वापस PTR_ERR(phy->clk);
		पूर्ण

		phy->hsic_clk = devm_clk_get(dev, "hsic_12M");
		अगर (IS_ERR(phy->hsic_clk)) अणु
			dev_err(dev, "failed to get hsic_12M clock\n");
			वापस PTR_ERR(phy->hsic_clk);
		पूर्ण

		phy->reset = devm_reset_control_get(dev, "hsic");
		अगर (IS_ERR(phy->reset)) अणु
			dev_err(dev, "failed to get reset control\n");
			वापस PTR_ERR(phy->reset);
		पूर्ण
	पूर्ण अन्यथा अणु
		phy->clk = devm_clk_get(dev, "phy");
		अगर (IS_ERR(phy->clk)) अणु
			dev_err(dev, "failed to get phy clock\n");
			वापस PTR_ERR(phy->clk);
		पूर्ण

		phy->reset = devm_reset_control_get(dev, "phy");
		अगर (IS_ERR(phy->reset)) अणु
			dev_err(dev, "failed to get reset control\n");
			वापस PTR_ERR(phy->reset);
		पूर्ण
	पूर्ण

	phy->pmu = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(phy->pmu))
		वापस PTR_ERR(phy->pmu);

	phy->phy = devm_phy_create(dev, शून्य, &sun9i_usb_phy_ops);
	अगर (IS_ERR(phy->phy)) अणु
		dev_err(dev, "failed to create PHY\n");
		वापस PTR_ERR(phy->phy);
	पूर्ण

	phy_set_drvdata(phy->phy, phy);
	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id sun9i_usb_phy_of_match[] = अणु
	अणु .compatible = "allwinner,sun9i-a80-usb-phy" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sun9i_usb_phy_of_match);

अटल काष्ठा platक्रमm_driver sun9i_usb_phy_driver = अणु
	.probe	= sun9i_usb_phy_probe,
	.driver = अणु
		.of_match_table	= sun9i_usb_phy_of_match,
		.name  = "sun9i-usb-phy",
	पूर्ण
पूर्ण;
module_platक्रमm_driver(sun9i_usb_phy_driver);

MODULE_DESCRIPTION("Allwinner sun9i USB phy driver");
MODULE_AUTHOR("Chen-Yu Tsai <wens@csie.org>");
MODULE_LICENSE("GPL");
