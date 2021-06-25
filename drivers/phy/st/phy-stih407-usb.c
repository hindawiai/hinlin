<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 STMicroelectronics
 *
 * STMicroelectronics Generic PHY driver क्रम STiH407 USB2.
 *
 * Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/clk.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/phy/phy.h>

#घोषणा PHYPARAM_REG	1
#घोषणा PHYCTRL_REG	2

/* Default PHY_SEL and REFCLKSEL configuration */
#घोषणा STIH407_USB_PICOPHY_CTRL_PORT_CONF	0x6
#घोषणा STIH407_USB_PICOPHY_CTRL_PORT_MASK	0x1f

/* ports parameters overriding */
#घोषणा STIH407_USB_PICOPHY_PARAM_DEF		0x39a4dc
#घोषणा STIH407_USB_PICOPHY_PARAM_MASK		0xffffffff

काष्ठा stih407_usb2_picophy अणु
	काष्ठा phy *phy;
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	काष्ठा reset_control *rstc;
	काष्ठा reset_control *rstport;
	पूर्णांक ctrl;
	पूर्णांक param;
पूर्ण;

अटल पूर्णांक stih407_usb2_pico_ctrl(काष्ठा stih407_usb2_picophy *phy_dev)
अणु
	reset_control_deनिश्चित(phy_dev->rstc);

	वापस regmap_update_bits(phy_dev->regmap, phy_dev->ctrl,
				  STIH407_USB_PICOPHY_CTRL_PORT_MASK,
				  STIH407_USB_PICOPHY_CTRL_PORT_CONF);
पूर्ण

अटल पूर्णांक stih407_usb2_init_port(काष्ठा phy *phy)
अणु
	पूर्णांक ret;
	काष्ठा stih407_usb2_picophy *phy_dev = phy_get_drvdata(phy);

	stih407_usb2_pico_ctrl(phy_dev);

	ret = regmap_update_bits(phy_dev->regmap,
				 phy_dev->param,
				 STIH407_USB_PICOPHY_PARAM_MASK,
				 STIH407_USB_PICOPHY_PARAM_DEF);
	अगर (ret)
		वापस ret;

	वापस reset_control_deनिश्चित(phy_dev->rstport);
पूर्ण

अटल पूर्णांक stih407_usb2_निकास_port(काष्ठा phy *phy)
अणु
	काष्ठा stih407_usb2_picophy *phy_dev = phy_get_drvdata(phy);

	/*
	 * Only port reset is निश्चितed, phy global reset is kept untouched
	 * as other ports may still be active. When all ports are in reset
	 * state, assumption is made that घातer will be cut off on the phy, in
	 * हाल of suspend क्रम instance. Theoretically, निश्चितing inभागidual
	 * reset (like here) or global reset should be equivalent.
	 */
	वापस reset_control_निश्चित(phy_dev->rstport);
पूर्ण

अटल स्थिर काष्ठा phy_ops stih407_usb2_picophy_data = अणु
	.init = stih407_usb2_init_port,
	.निकास = stih407_usb2_निकास_port,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक stih407_usb2_picophy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा stih407_usb2_picophy *phy_dev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा phy_provider *phy_provider;
	काष्ठा phy *phy;
	पूर्णांक ret;

	phy_dev = devm_kzalloc(dev, माप(*phy_dev), GFP_KERNEL);
	अगर (!phy_dev)
		वापस -ENOMEM;

	phy_dev->dev = dev;
	dev_set_drvdata(dev, phy_dev);

	phy_dev->rstc = devm_reset_control_get_shared(dev, "global");
	अगर (IS_ERR(phy_dev->rstc)) अणु
		dev_err(dev, "failed to ctrl picoPHY reset\n");
		वापस PTR_ERR(phy_dev->rstc);
	पूर्ण

	phy_dev->rstport = devm_reset_control_get_exclusive(dev, "port");
	अगर (IS_ERR(phy_dev->rstport)) अणु
		dev_err(dev, "failed to ctrl picoPHY reset\n");
		वापस PTR_ERR(phy_dev->rstport);
	पूर्ण

	/* Reset port by शेष: only deनिश्चित it in phy init */
	reset_control_निश्चित(phy_dev->rstport);

	phy_dev->regmap = syscon_regmap_lookup_by_phandle(np, "st,syscfg");
	अगर (IS_ERR(phy_dev->regmap)) अणु
		dev_err(dev, "No syscfg phandle specified\n");
		वापस PTR_ERR(phy_dev->regmap);
	पूर्ण

	ret = of_property_पढ़ो_u32_index(np, "st,syscfg", PHYPARAM_REG,
					&phy_dev->param);
	अगर (ret) अणु
		dev_err(dev, "can't get phyparam offset (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32_index(np, "st,syscfg", PHYCTRL_REG,
					&phy_dev->ctrl);
	अगर (ret) अणु
		dev_err(dev, "can't get phyctrl offset (%d)\n", ret);
		वापस ret;
	पूर्ण

	phy = devm_phy_create(dev, शून्य, &stih407_usb2_picophy_data);
	अगर (IS_ERR(phy)) अणु
		dev_err(dev, "failed to create Display Port PHY\n");
		वापस PTR_ERR(phy);
	पूर्ण

	phy_dev->phy = phy;
	phy_set_drvdata(phy, phy_dev);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(phy_provider))
		वापस PTR_ERR(phy_provider);

	dev_info(dev, "STiH407 USB Generic picoPHY driver probed!");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id stih407_usb2_picophy_of_match[] = अणु
	अणु .compatible = "st,stih407-usb2-phy" पूर्ण,
	अणु /*sentinel */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, stih407_usb2_picophy_of_match);

अटल काष्ठा platक्रमm_driver stih407_usb2_picophy_driver = अणु
	.probe = stih407_usb2_picophy_probe,
	.driver = अणु
		   .name = "stih407-usb-genphy",
		   .of_match_table = stih407_usb2_picophy_of_match,
		   पूर्ण
पूर्ण;

module_platक्रमm_driver(stih407_usb2_picophy_driver);

MODULE_AUTHOR("Giuseppe Cavallaro <peppe.cavallaro@st.com>");
MODULE_DESCRIPTION("STMicroelectronics Generic picoPHY driver for STiH407");
MODULE_LICENSE("GPL v2");
