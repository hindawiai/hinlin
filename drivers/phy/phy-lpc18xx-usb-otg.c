<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PHY driver क्रम NXP LPC18xx/43xx पूर्णांकernal USB OTG PHY
 *
 * Copyright (C) 2015 Joachim Eastwood <manabian@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

/* USB OTG PHY रेजिस्टर offset and bit in CREG */
#घोषणा LPC18XX_CREG_CREG0		0x004
#घोषणा LPC18XX_CREG_CREG0_USB0PHY	BIT(5)

काष्ठा lpc18xx_usb_otg_phy अणु
	काष्ठा phy *phy;
	काष्ठा clk *clk;
	काष्ठा regmap *reg;
पूर्ण;

अटल पूर्णांक lpc18xx_usb_otg_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा lpc18xx_usb_otg_phy *lpc = phy_get_drvdata(phy);
	पूर्णांक ret;

	/* The PHY must be घड़ीed at 480 MHz */
	ret = clk_set_rate(lpc->clk, 480000000);
	अगर (ret)
		वापस ret;

	वापस clk_prepare(lpc->clk);
पूर्ण

अटल पूर्णांक lpc18xx_usb_otg_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा lpc18xx_usb_otg_phy *lpc = phy_get_drvdata(phy);

	clk_unprepare(lpc->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc18xx_usb_otg_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा lpc18xx_usb_otg_phy *lpc = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = clk_enable(lpc->clk);
	अगर (ret)
		वापस ret;

	/* The bit in CREG is cleared to enable the PHY */
	ret = regmap_update_bits(lpc->reg, LPC18XX_CREG_CREG0,
				  LPC18XX_CREG_CREG0_USB0PHY, 0);
	अगर (ret) अणु
		clk_disable(lpc->clk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lpc18xx_usb_otg_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा lpc18xx_usb_otg_phy *lpc = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = regmap_update_bits(lpc->reg, LPC18XX_CREG_CREG0,
				 LPC18XX_CREG_CREG0_USB0PHY,
				 LPC18XX_CREG_CREG0_USB0PHY);
	अगर (ret)
		वापस ret;

	clk_disable(lpc->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops lpc18xx_usb_otg_phy_ops = अणु
	.init		= lpc18xx_usb_otg_phy_init,
	.निकास		= lpc18xx_usb_otg_phy_निकास,
	.घातer_on	= lpc18xx_usb_otg_phy_घातer_on,
	.घातer_off	= lpc18xx_usb_otg_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक lpc18xx_usb_otg_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *phy_provider;
	काष्ठा lpc18xx_usb_otg_phy *lpc;

	lpc = devm_kzalloc(&pdev->dev, माप(*lpc), GFP_KERNEL);
	अगर (!lpc)
		वापस -ENOMEM;

	lpc->reg = syscon_node_to_regmap(pdev->dev.of_node->parent);
	अगर (IS_ERR(lpc->reg)) अणु
		dev_err(&pdev->dev, "failed to get syscon\n");
		वापस PTR_ERR(lpc->reg);
	पूर्ण

	lpc->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(lpc->clk)) अणु
		dev_err(&pdev->dev, "failed to get clock\n");
		वापस PTR_ERR(lpc->clk);
	पूर्ण

	lpc->phy = devm_phy_create(&pdev->dev, शून्य, &lpc18xx_usb_otg_phy_ops);
	अगर (IS_ERR(lpc->phy)) अणु
		dev_err(&pdev->dev, "failed to create PHY\n");
		वापस PTR_ERR(lpc->phy);
	पूर्ण

	phy_set_drvdata(lpc->phy, lpc);

	phy_provider = devm_of_phy_provider_रेजिस्टर(&pdev->dev,
						     of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id lpc18xx_usb_otg_phy_match[] = अणु
	अणु .compatible = "nxp,lpc1850-usb-otg-phy" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc18xx_usb_otg_phy_match);

अटल काष्ठा platक्रमm_driver lpc18xx_usb_otg_phy_driver = अणु
	.probe		= lpc18xx_usb_otg_phy_probe,
	.driver		= अणु
		.name	= "lpc18xx-usb-otg-phy",
		.of_match_table = lpc18xx_usb_otg_phy_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lpc18xx_usb_otg_phy_driver);

MODULE_AUTHOR("Joachim Eastwood <manabian@gmail.com>");
MODULE_DESCRIPTION("NXP LPC18xx/43xx USB OTG PHY driver");
MODULE_LICENSE("GPL v2");
