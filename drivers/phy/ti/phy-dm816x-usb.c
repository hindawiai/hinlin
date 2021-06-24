<शैली गुरु>
/*
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/पन.स>
#समावेश <linux/usb/phy_companion.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/delay.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <linux/mfd/syscon.h>

/*
 * TRM has two sets of USB_CTRL रेजिस्टरs.. The correct रेजिस्टर bits
 * are in TRM section 24.9.8.2 USB_CTRL Register. The TRM करोcuments the
 * phy as being SR70LX Synopsys USB 2.0 OTG nanoPHY. It also seems at
 * least dm816x rev c ignores ग_लिखोs to USB_CTRL रेजिस्टर, but the TI
 * kernel is writing to those so it's possible that later revisions
 * have worknig USB_CTRL रेजिस्टर.
 *
 * Also note that At least USB_CTRL रेजिस्टर seems to be dm816x specअगरic
 * according to the TRM. It's possible that USBPHY_CTRL is more generic,
 * but that would have to be checked against the SR70LX करोcumentation
 * which करोes not seem to be खुलाly available.
 *
 * Finally, the phy on dm814x and am335x is dअगरferent from dm816x.
 */
#घोषणा DM816X_USB_CTRL_PHYCLKSRC	BIT(8)	/* 1 = PLL ref घड़ी */
#घोषणा DM816X_USB_CTRL_PHYSLEEP1	BIT(1)	/* Enable the first phy */
#घोषणा DM816X_USB_CTRL_PHYSLEEP0	BIT(0)	/* Enable the second phy */

#घोषणा DM816X_USBPHY_CTRL_TXRISETUNE	1
#घोषणा DM816X_USBPHY_CTRL_TXVREFTUNE	0xc
#घोषणा DM816X_USBPHY_CTRL_TXPREEMTUNE	0x2

काष्ठा dm816x_usb_phy अणु
	काष्ठा regmap *syscon;
	काष्ठा device *dev;
	अचिन्हित पूर्णांक instance;
	काष्ठा clk *refclk;
	काष्ठा usb_phy phy;
	अचिन्हित पूर्णांक usb_ctrl;		/* Shared between phy0 and phy1 */
	अचिन्हित पूर्णांक usbphy_ctrl;
पूर्ण;

अटल पूर्णांक dm816x_usb_phy_set_host(काष्ठा usb_otg *otg, काष्ठा usb_bus *host)
अणु
	otg->host = host;
	अगर (!host)
		otg->state = OTG_STATE_UNDEFINED;

	वापस 0;
पूर्ण

अटल पूर्णांक dm816x_usb_phy_set_peripheral(काष्ठा usb_otg *otg,
					 काष्ठा usb_gadget *gadget)
अणु
	otg->gadget = gadget;
	अगर (!gadget)
		otg->state = OTG_STATE_UNDEFINED;

	वापस 0;
पूर्ण

अटल पूर्णांक dm816x_usb_phy_init(काष्ठा phy *x)
अणु
	काष्ठा dm816x_usb_phy *phy = phy_get_drvdata(x);
	अचिन्हित पूर्णांक val;

	अगर (clk_get_rate(phy->refclk) != 24000000)
		dev_warn(phy->dev, "nonstandard phy refclk\n");

	/* Set PLL ref घड़ी and put phys to sleep */
	regmap_update_bits(phy->syscon, phy->usb_ctrl,
			   DM816X_USB_CTRL_PHYCLKSRC |
			   DM816X_USB_CTRL_PHYSLEEP1 |
			   DM816X_USB_CTRL_PHYSLEEP0,
			   0);
	regmap_पढ़ो(phy->syscon, phy->usb_ctrl, &val);
	अगर ((val & 3) != 0)
		dev_info(phy->dev,
			 "Working dm816x USB_CTRL! (0x%08x)\n",
			 val);

	/*
	 * TI kernel sets these values क्रम "symmetrical eye diagram and
	 * better संकेत quality" so let's assume somebody checked the
	 * values with a scope and set them here too.
	 */
	regmap_पढ़ो(phy->syscon, phy->usbphy_ctrl, &val);
	val |= DM816X_USBPHY_CTRL_TXRISETUNE |
		DM816X_USBPHY_CTRL_TXVREFTUNE |
		DM816X_USBPHY_CTRL_TXPREEMTUNE;
	regmap_ग_लिखो(phy->syscon, phy->usbphy_ctrl, val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops ops = अणु
	.init		= dm816x_usb_phy_init,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __maybe_unused dm816x_usb_phy_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा dm816x_usb_phy *phy = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक mask, val;
	पूर्णांक error = 0;

	mask = BIT(phy->instance);
	val = ~BIT(phy->instance);
	error = regmap_update_bits(phy->syscon, phy->usb_ctrl,
				   mask, val);
	अगर (error)
		dev_err(phy->dev, "phy%i failed to power off\n",
			phy->instance);
	clk_disable(phy->refclk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused dm816x_usb_phy_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा dm816x_usb_phy *phy = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक mask, val;
	पूर्णांक error;

	error = clk_enable(phy->refclk);
	अगर (error)
		वापस error;

	/*
	 * Note that at least dm816x rev c करोes not seem to करो
	 * anything with the USB_CTRL रेजिस्टर. But let's follow
	 * what the TI tree is करोing in हाल later revisions use
	 * USB_CTRL.
	 */
	mask = BIT(phy->instance);
	val = BIT(phy->instance);
	error = regmap_update_bits(phy->syscon, phy->usb_ctrl,
				   mask, val);
	अगर (error) अणु
		dev_err(phy->dev, "phy%i failed to power on\n",
			phy->instance);
		clk_disable(phy->refclk);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल UNIVERSAL_DEV_PM_OPS(dm816x_usb_phy_pm_ops,
			    dm816x_usb_phy_runसमय_suspend,
			    dm816x_usb_phy_runसमय_resume,
			    शून्य);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id dm816x_usb_phy_id_table[] = अणु
	अणु
		.compatible = "ti,dm8168-usb-phy",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, dm816x_usb_phy_id_table);
#पूर्ण_अगर

अटल पूर्णांक dm816x_usb_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dm816x_usb_phy *phy;
	काष्ठा resource *res;
	काष्ठा phy *generic_phy;
	काष्ठा phy_provider *phy_provider;
	काष्ठा usb_otg *otg;
	स्थिर काष्ठा of_device_id *of_id;
	पूर्णांक error;

	of_id = of_match_device(of_match_ptr(dm816x_usb_phy_id_table),
				&pdev->dev);
	अगर (!of_id)
		वापस -EINVAL;

	phy = devm_kzalloc(&pdev->dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENOENT;

	phy->syscon = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
						      "syscon");
	अगर (IS_ERR(phy->syscon))
		वापस PTR_ERR(phy->syscon);

	/*
	 * According to sprs614e.pdf, the first usb_ctrl is shared and
	 * the second instance क्रम usb_ctrl is reserved.. Also the
	 * रेजिस्टर bits are dअगरferent from earlier TRMs.
	 */
	phy->usb_ctrl = 0x20;
	phy->usbphy_ctrl = (res->start & 0xff) + 4;
	अगर (phy->usbphy_ctrl == 0x2c)
		phy->instance = 1;

	otg = devm_kzalloc(&pdev->dev, माप(*otg), GFP_KERNEL);
	अगर (!otg)
		वापस -ENOMEM;

	phy->dev = &pdev->dev;
	phy->phy.dev = phy->dev;
	phy->phy.label = "dm8168_usb_phy";
	phy->phy.otg = otg;
	phy->phy.type = USB_PHY_TYPE_USB2;
	otg->set_host = dm816x_usb_phy_set_host;
	otg->set_peripheral = dm816x_usb_phy_set_peripheral;
	otg->usb_phy = &phy->phy;

	platक्रमm_set_drvdata(pdev, phy);

	phy->refclk = devm_clk_get(phy->dev, "refclk");
	अगर (IS_ERR(phy->refclk))
		वापस PTR_ERR(phy->refclk);
	error = clk_prepare(phy->refclk);
	अगर (error)
		वापस error;

	pm_runसमय_enable(phy->dev);
	generic_phy = devm_phy_create(phy->dev, शून्य, &ops);
	अगर (IS_ERR(generic_phy))
		वापस PTR_ERR(generic_phy);

	phy_set_drvdata(generic_phy, phy);

	phy_provider = devm_of_phy_provider_रेजिस्टर(phy->dev,
						     of_phy_simple_xlate);
	अगर (IS_ERR(phy_provider))
		वापस PTR_ERR(phy_provider);

	usb_add_phy_dev(&phy->phy);

	वापस 0;
पूर्ण

अटल पूर्णांक dm816x_usb_phy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dm816x_usb_phy *phy = platक्रमm_get_drvdata(pdev);

	usb_हटाओ_phy(&phy->phy);
	pm_runसमय_disable(phy->dev);
	clk_unprepare(phy->refclk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver dm816x_usb_phy_driver = अणु
	.probe		= dm816x_usb_phy_probe,
	.हटाओ		= dm816x_usb_phy_हटाओ,
	.driver		= अणु
		.name	= "dm816x-usb-phy",
		.pm	= &dm816x_usb_phy_pm_ops,
		.of_match_table = of_match_ptr(dm816x_usb_phy_id_table),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dm816x_usb_phy_driver);

MODULE_ALIAS("platform:dm816x_usb");
MODULE_AUTHOR("Tony Lindgren <tony@atomide.com>");
MODULE_DESCRIPTION("dm816x usb phy driver");
MODULE_LICENSE("GPL v2");
