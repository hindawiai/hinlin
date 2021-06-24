<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IMG Pistachio USB PHY driver
 *
 * Copyright (C) 2015 Google, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/phy/phy-pistachio-usb.h>

#घोषणा USB_PHY_CONTROL1				0x04
#घोषणा USB_PHY_CONTROL1_FSEL_SHIFT			2
#घोषणा USB_PHY_CONTROL1_FSEL_MASK			0x7

#घोषणा USB_PHY_STRAP_CONTROL				0x10
#घोषणा USB_PHY_STRAP_CONTROL_REFCLK_SHIFT		4
#घोषणा USB_PHY_STRAP_CONTROL_REFCLK_MASK		0x3

#घोषणा USB_PHY_STATUS					0x14
#घोषणा USB_PHY_STATUS_RX_PHY_CLK			BIT(9)
#घोषणा USB_PHY_STATUS_RX_UTMI_CLK			BIT(8)
#घोषणा USB_PHY_STATUS_VBUS_FAULT			BIT(7)

काष्ठा pistachio_usb_phy अणु
	काष्ठा device *dev;
	काष्ठा regmap *cr_top;
	काष्ठा clk *phy_clk;
	अचिन्हित पूर्णांक refclk;
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ fsel_rate_map[] = अणु
	9600000,
	10000000,
	12000000,
	19200000,
	20000000,
	24000000,
	0,
	50000000,
पूर्ण;

अटल पूर्णांक pistachio_usb_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा pistachio_usb_phy *p_phy = phy_get_drvdata(phy);
	अचिन्हित दीर्घ समयout, rate;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = clk_prepare_enable(p_phy->phy_clk);
	अगर (ret < 0) अणु
		dev_err(p_phy->dev, "Failed to enable PHY clock: %d\n", ret);
		वापस ret;
	पूर्ण

	regmap_update_bits(p_phy->cr_top, USB_PHY_STRAP_CONTROL,
			   USB_PHY_STRAP_CONTROL_REFCLK_MASK <<
			   USB_PHY_STRAP_CONTROL_REFCLK_SHIFT,
			   p_phy->refclk << USB_PHY_STRAP_CONTROL_REFCLK_SHIFT);

	rate = clk_get_rate(p_phy->phy_clk);
	अगर (p_phy->refclk == REFCLK_XO_CRYSTAL && rate != 12000000) अणु
		dev_err(p_phy->dev, "Unsupported rate for XO crystal: %ld\n",
			rate);
		ret = -EINVAL;
		जाओ disable_clk;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(fsel_rate_map); i++) अणु
		अगर (rate == fsel_rate_map[i])
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(fsel_rate_map)) अणु
		dev_err(p_phy->dev, "Unsupported clock rate: %lu\n", rate);
		ret = -EINVAL;
		जाओ disable_clk;
	पूर्ण

	regmap_update_bits(p_phy->cr_top, USB_PHY_CONTROL1,
			   USB_PHY_CONTROL1_FSEL_MASK <<
			   USB_PHY_CONTROL1_FSEL_SHIFT,
			   i << USB_PHY_CONTROL1_FSEL_SHIFT);

	समयout = jअगरfies + msecs_to_jअगरfies(200);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		अचिन्हित पूर्णांक val;

		regmap_पढ़ो(p_phy->cr_top, USB_PHY_STATUS, &val);
		अगर (val & USB_PHY_STATUS_VBUS_FAULT) अणु
			dev_err(p_phy->dev, "VBUS fault detected\n");
			ret = -EIO;
			जाओ disable_clk;
		पूर्ण
		अगर ((val & USB_PHY_STATUS_RX_PHY_CLK) &&
		    (val & USB_PHY_STATUS_RX_UTMI_CLK))
			वापस 0;
		usleep_range(1000, 1500);
	पूर्ण

	dev_err(p_phy->dev, "Timed out waiting for PHY to power on\n");
	ret = -ETIMEDOUT;

disable_clk:
	clk_disable_unprepare(p_phy->phy_clk);
	वापस ret;
पूर्ण

अटल पूर्णांक pistachio_usb_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा pistachio_usb_phy *p_phy = phy_get_drvdata(phy);

	clk_disable_unprepare(p_phy->phy_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops pistachio_usb_phy_ops = अणु
	.घातer_on = pistachio_usb_phy_घातer_on,
	.घातer_off = pistachio_usb_phy_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक pistachio_usb_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pistachio_usb_phy *p_phy;
	काष्ठा phy_provider *provider;
	काष्ठा phy *phy;
	पूर्णांक ret;

	p_phy = devm_kzalloc(&pdev->dev, माप(*p_phy), GFP_KERNEL);
	अगर (!p_phy)
		वापस -ENOMEM;
	p_phy->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, p_phy);

	p_phy->cr_top = syscon_regmap_lookup_by_phandle(p_phy->dev->of_node,
							"img,cr-top");
	अगर (IS_ERR(p_phy->cr_top)) अणु
		dev_err(p_phy->dev, "Failed to get CR_TOP registers: %ld\n",
			PTR_ERR(p_phy->cr_top));
		वापस PTR_ERR(p_phy->cr_top);
	पूर्ण

	p_phy->phy_clk = devm_clk_get(p_phy->dev, "usb_phy");
	अगर (IS_ERR(p_phy->phy_clk)) अणु
		dev_err(p_phy->dev, "Failed to get usb_phy clock: %ld\n",
			PTR_ERR(p_phy->phy_clk));
		वापस PTR_ERR(p_phy->phy_clk);
	पूर्ण

	ret = of_property_पढ़ो_u32(p_phy->dev->of_node, "img,refclk",
				   &p_phy->refclk);
	अगर (ret < 0) अणु
		dev_err(p_phy->dev, "No reference clock selector specified\n");
		वापस ret;
	पूर्ण

	phy = devm_phy_create(p_phy->dev, शून्य, &pistachio_usb_phy_ops);
	अगर (IS_ERR(phy)) अणु
		dev_err(p_phy->dev, "Failed to create PHY: %ld\n",
			PTR_ERR(phy));
		वापस PTR_ERR(phy);
	पूर्ण
	phy_set_drvdata(phy, p_phy);

	provider = devm_of_phy_provider_रेजिस्टर(p_phy->dev,
						 of_phy_simple_xlate);
	अगर (IS_ERR(provider)) अणु
		dev_err(p_phy->dev, "Failed to register PHY provider: %ld\n",
			PTR_ERR(provider));
		वापस PTR_ERR(provider);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pistachio_usb_phy_of_match[] = अणु
	अणु .compatible = "img,pistachio-usb-phy", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pistachio_usb_phy_of_match);

अटल काष्ठा platक्रमm_driver pistachio_usb_phy_driver = अणु
	.probe		= pistachio_usb_phy_probe,
	.driver		= अणु
		.name	= "pistachio-usb-phy",
		.of_match_table = pistachio_usb_phy_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(pistachio_usb_phy_driver);

MODULE_AUTHOR("Andrew Bresticker <abrestic@chromium.org>");
MODULE_DESCRIPTION("IMG Pistachio USB2.0 PHY driver");
MODULE_LICENSE("GPL v2");
