<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * phy-da8xx-usb - TI DaVinci DA8xx USB PHY driver
 *
 * Copyright (C) 2016 David Lechner <david@lechnology.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/mfd/da8xx-cfgchip.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_data/phy-da8xx-usb.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा PHY_INIT_BITS	(CFGCHIP2_SESENDEN | CFGCHIP2_VBDTCTEN)

काष्ठा da8xx_usb_phy अणु
	काष्ठा phy_provider	*phy_provider;
	काष्ठा phy		*usb11_phy;
	काष्ठा phy		*usb20_phy;
	काष्ठा clk		*usb11_clk;
	काष्ठा clk		*usb20_clk;
	काष्ठा regmap		*regmap;
पूर्ण;

अटल पूर्णांक da8xx_usb11_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा da8xx_usb_phy *d_phy = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = clk_prepare_enable(d_phy->usb11_clk);
	अगर (ret)
		वापस ret;

	regmap_ग_लिखो_bits(d_phy->regmap, CFGCHIP(2), CFGCHIP2_USB1SUSPENDM,
			  CFGCHIP2_USB1SUSPENDM);

	वापस 0;
पूर्ण

अटल पूर्णांक da8xx_usb11_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा da8xx_usb_phy *d_phy = phy_get_drvdata(phy);

	regmap_ग_लिखो_bits(d_phy->regmap, CFGCHIP(2), CFGCHIP2_USB1SUSPENDM, 0);

	clk_disable_unprepare(d_phy->usb11_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops da8xx_usb11_phy_ops = अणु
	.घातer_on	= da8xx_usb11_phy_घातer_on,
	.घातer_off	= da8xx_usb11_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक da8xx_usb20_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा da8xx_usb_phy *d_phy = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = clk_prepare_enable(d_phy->usb20_clk);
	अगर (ret)
		वापस ret;

	regmap_ग_लिखो_bits(d_phy->regmap, CFGCHIP(2), CFGCHIP2_OTGPWRDN, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक da8xx_usb20_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा da8xx_usb_phy *d_phy = phy_get_drvdata(phy);

	regmap_ग_लिखो_bits(d_phy->regmap, CFGCHIP(2), CFGCHIP2_OTGPWRDN,
			  CFGCHIP2_OTGPWRDN);

	clk_disable_unprepare(d_phy->usb20_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक da8xx_usb20_phy_set_mode(काष्ठा phy *phy,
				    क्रमागत phy_mode mode, पूर्णांक submode)
अणु
	काष्ठा da8xx_usb_phy *d_phy = phy_get_drvdata(phy);
	u32 val;

	चयन (mode) अणु
	हाल PHY_MODE_USB_HOST:		/* Force VBUS valid, ID = 0 */
		val = CFGCHIP2_OTGMODE_FORCE_HOST;
		अवरोध;
	हाल PHY_MODE_USB_DEVICE:	/* Force VBUS valid, ID = 1 */
		val = CFGCHIP2_OTGMODE_FORCE_DEVICE;
		अवरोध;
	हाल PHY_MODE_USB_OTG:	/* Don't override the VBUS/ID comparators */
		val = CFGCHIP2_OTGMODE_NO_OVERRIDE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_ग_लिखो_bits(d_phy->regmap, CFGCHIP(2), CFGCHIP2_OTGMODE_MASK,
			  val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops da8xx_usb20_phy_ops = अणु
	.घातer_on	= da8xx_usb20_phy_घातer_on,
	.घातer_off	= da8xx_usb20_phy_घातer_off,
	.set_mode	= da8xx_usb20_phy_set_mode,
	.owner		= THIS_MODULE,
पूर्ण;

अटल काष्ठा phy *da8xx_usb_phy_of_xlate(काष्ठा device *dev,
					 काष्ठा of_phandle_args *args)
अणु
	काष्ठा da8xx_usb_phy *d_phy = dev_get_drvdata(dev);

	अगर (!d_phy)
		वापस ERR_PTR(-ENODEV);

	चयन (args->args[0]) अणु
	हाल 0:
		वापस d_phy->usb20_phy;
	हाल 1:
		वापस d_phy->usb11_phy;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण
पूर्ण

अटल पूर्णांक da8xx_usb_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device		*dev = &pdev->dev;
	काष्ठा da8xx_usb_phy_platक्रमm_data *pdata = dev->platक्रमm_data;
	काष्ठा device_node	*node = dev->of_node;
	काष्ठा da8xx_usb_phy	*d_phy;

	d_phy = devm_kzalloc(dev, माप(*d_phy), GFP_KERNEL);
	अगर (!d_phy)
		वापस -ENOMEM;

	अगर (pdata)
		d_phy->regmap = pdata->cfgchip;
	अन्यथा
		d_phy->regmap = syscon_regmap_lookup_by_compatible(
							"ti,da830-cfgchip");
	अगर (IS_ERR(d_phy->regmap)) अणु
		dev_err(dev, "Failed to get syscon\n");
		वापस PTR_ERR(d_phy->regmap);
	पूर्ण

	d_phy->usb11_clk = devm_clk_get(dev, "usb1_clk48");
	अगर (IS_ERR(d_phy->usb11_clk)) अणु
		dev_err(dev, "Failed to get usb1_clk48\n");
		वापस PTR_ERR(d_phy->usb11_clk);
	पूर्ण

	d_phy->usb20_clk = devm_clk_get(dev, "usb0_clk48");
	अगर (IS_ERR(d_phy->usb20_clk)) अणु
		dev_err(dev, "Failed to get usb0_clk48\n");
		वापस PTR_ERR(d_phy->usb20_clk);
	पूर्ण

	d_phy->usb11_phy = devm_phy_create(dev, node, &da8xx_usb11_phy_ops);
	अगर (IS_ERR(d_phy->usb11_phy)) अणु
		dev_err(dev, "Failed to create usb11 phy\n");
		वापस PTR_ERR(d_phy->usb11_phy);
	पूर्ण

	d_phy->usb20_phy = devm_phy_create(dev, node, &da8xx_usb20_phy_ops);
	अगर (IS_ERR(d_phy->usb20_phy)) अणु
		dev_err(dev, "Failed to create usb20 phy\n");
		वापस PTR_ERR(d_phy->usb20_phy);
	पूर्ण

	platक्रमm_set_drvdata(pdev, d_phy);
	phy_set_drvdata(d_phy->usb11_phy, d_phy);
	phy_set_drvdata(d_phy->usb20_phy, d_phy);

	अगर (node) अणु
		d_phy->phy_provider = devm_of_phy_provider_रेजिस्टर(dev,
							da8xx_usb_phy_of_xlate);
		अगर (IS_ERR(d_phy->phy_provider)) अणु
			dev_err(dev, "Failed to create phy provider\n");
			वापस PTR_ERR(d_phy->phy_provider);
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक ret;

		ret = phy_create_lookup(d_phy->usb11_phy, "usb-phy",
					"ohci-da8xx");
		अगर (ret)
			dev_warn(dev, "Failed to create usb11 phy lookup\n");
		ret = phy_create_lookup(d_phy->usb20_phy, "usb-phy",
					"musb-da8xx");
		अगर (ret)
			dev_warn(dev, "Failed to create usb20 phy lookup\n");
	पूर्ण

	regmap_ग_लिखो_bits(d_phy->regmap, CFGCHIP(2),
			  PHY_INIT_BITS, PHY_INIT_BITS);

	वापस 0;
पूर्ण

अटल पूर्णांक da8xx_usb_phy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da8xx_usb_phy *d_phy = platक्रमm_get_drvdata(pdev);

	अगर (!pdev->dev.of_node) अणु
		phy_हटाओ_lookup(d_phy->usb20_phy, "usb-phy", "musb-da8xx");
		phy_हटाओ_lookup(d_phy->usb11_phy, "usb-phy", "ohci-da8xx");
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id da8xx_usb_phy_ids[] = अणु
	अणु .compatible = "ti,da830-usb-phy" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, da8xx_usb_phy_ids);

अटल काष्ठा platक्रमm_driver da8xx_usb_phy_driver = अणु
	.probe	= da8xx_usb_phy_probe,
	.हटाओ	= da8xx_usb_phy_हटाओ,
	.driver	= अणु
		.name	= "da8xx-usb-phy",
		.of_match_table = da8xx_usb_phy_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(da8xx_usb_phy_driver);

MODULE_ALIAS("platform:da8xx-usb-phy");
MODULE_AUTHOR("David Lechner <david@lechnology.com>");
MODULE_DESCRIPTION("TI DA8xx USB PHY driver");
MODULE_LICENSE("GPL v2");
