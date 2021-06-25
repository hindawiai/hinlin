<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * omap-usb2.c - USB PHY, talking to USB controller on TI SoCs.
 *
 * Copyright (C) 2012-2020 Texas Instruments Incorporated - http://www.ti.com
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/omap_control_phy.h>
#समावेश <linux/phy/omap_usb.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/usb/phy_companion.h>

#घोषणा USB2PHY_ANA_CONFIG1		0x4c
#घोषणा USB2PHY_DISCON_BYP_LATCH	BIT(31)

#घोषणा USB2PHY_CHRG_DET			0x14
#घोषणा USB2PHY_CHRG_DET_USE_CHG_DET_REG	BIT(29)
#घोषणा USB2PHY_CHRG_DET_DIS_CHG_DET		BIT(28)

/* SoC Specअगरic USB2_OTG रेजिस्टर definitions */
#घोषणा AM654_USB2_OTG_PD		BIT(8)
#घोषणा AM654_USB2_VBUS_DET_EN		BIT(5)
#घोषणा AM654_USB2_VBUSVALID_DET_EN	BIT(4)

#घोषणा OMAP_DEV_PHY_PD		BIT(0)
#घोषणा OMAP_USB2_PHY_PD	BIT(28)

#घोषणा AM437X_USB2_PHY_PD		BIT(0)
#घोषणा AM437X_USB2_OTG_PD		BIT(1)
#घोषणा AM437X_USB2_OTGVDET_EN		BIT(19)
#घोषणा AM437X_USB2_OTGSESSEND_EN	BIT(20)

/* Driver Flags */
#घोषणा OMAP_USB2_HAS_START_SRP			BIT(0)
#घोषणा OMAP_USB2_HAS_SET_VBUS			BIT(1)
#घोषणा OMAP_USB2_CALIBRATE_FALSE_DISCONNECT	BIT(2)
#घोषणा OMAP_USB2_DISABLE_CHRG_DET		BIT(3)

काष्ठा omap_usb अणु
	काष्ठा usb_phy		phy;
	काष्ठा phy_companion	*comparator;
	व्योम __iomem		*pll_ctrl_base;
	व्योम __iomem		*phy_base;
	काष्ठा device		*dev;
	काष्ठा device		*control_dev;
	काष्ठा clk		*wkupclk;
	काष्ठा clk		*optclk;
	u8			flags;
	काष्ठा regmap		*syscon_phy_घातer; /* ctrl. reg. acces */
	अचिन्हित पूर्णांक		घातer_reg; /* घातer reg. index within syscon */
	u32			mask;
	u32			घातer_on;
	u32			घातer_off;
पूर्ण;

#घोषणा	phy_to_omapusb(x)	container_of((x), काष्ठा omap_usb, phy)

काष्ठा usb_phy_data अणु
	स्थिर अक्षर *label;
	u8 flags;
	u32 mask;
	u32 घातer_on;
	u32 घातer_off;
पूर्ण;

अटल अंतरभूत u32 omap_usb_पढ़ोl(व्योम __iomem *addr, अचिन्हित पूर्णांक offset)
अणु
	वापस __raw_पढ़ोl(addr + offset);
पूर्ण

अटल अंतरभूत व्योम omap_usb_ग_लिखोl(व्योम __iomem *addr, अचिन्हित पूर्णांक offset,
				   u32 data)
अणु
	__raw_ग_लिखोl(data, addr + offset);
पूर्ण

/**
 * omap_usb2_set_comparator - links the comparator present in the प्रणाली with
 *	this phy
 * @comparator - the companion phy(comparator) क्रम this phy
 *
 * The phy companion driver should call this API passing the phy_companion
 * filled with set_vbus and start_srp to be used by usb phy.
 *
 * For use by phy companion driver
 */
पूर्णांक omap_usb2_set_comparator(काष्ठा phy_companion *comparator)
अणु
	काष्ठा omap_usb	*phy;
	काष्ठा usb_phy	*x = usb_get_phy(USB_PHY_TYPE_USB2);

	अगर (IS_ERR(x))
		वापस -ENODEV;

	phy = phy_to_omapusb(x);
	phy->comparator = comparator;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(omap_usb2_set_comparator);

अटल पूर्णांक omap_usb_set_vbus(काष्ठा usb_otg *otg, bool enabled)
अणु
	काष्ठा omap_usb *phy = phy_to_omapusb(otg->usb_phy);

	अगर (!phy->comparator)
		वापस -ENODEV;

	वापस phy->comparator->set_vbus(phy->comparator, enabled);
पूर्ण

अटल पूर्णांक omap_usb_start_srp(काष्ठा usb_otg *otg)
अणु
	काष्ठा omap_usb *phy = phy_to_omapusb(otg->usb_phy);

	अगर (!phy->comparator)
		वापस -ENODEV;

	वापस phy->comparator->start_srp(phy->comparator);
पूर्ण

अटल पूर्णांक omap_usb_set_host(काष्ठा usb_otg *otg, काष्ठा usb_bus *host)
अणु
	otg->host = host;
	अगर (!host)
		otg->state = OTG_STATE_UNDEFINED;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_usb_set_peripheral(काष्ठा usb_otg *otg,
				   काष्ठा usb_gadget *gadget)
अणु
	otg->gadget = gadget;
	अगर (!gadget)
		otg->state = OTG_STATE_UNDEFINED;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_usb_phy_घातer(काष्ठा omap_usb *phy, पूर्णांक on)
अणु
	u32 val;
	पूर्णांक ret;

	अगर (!phy->syscon_phy_घातer) अणु
		omap_control_phy_घातer(phy->control_dev, on);
		वापस 0;
	पूर्ण

	अगर (on)
		val = phy->घातer_on;
	अन्यथा
		val = phy->घातer_off;

	ret = regmap_update_bits(phy->syscon_phy_घातer, phy->घातer_reg,
				 phy->mask, val);
	वापस ret;
पूर्ण

अटल पूर्णांक omap_usb_घातer_off(काष्ठा phy *x)
अणु
	काष्ठा omap_usb *phy = phy_get_drvdata(x);

	वापस omap_usb_phy_घातer(phy, false);
पूर्ण

अटल पूर्णांक omap_usb_घातer_on(काष्ठा phy *x)
अणु
	काष्ठा omap_usb *phy = phy_get_drvdata(x);

	वापस omap_usb_phy_घातer(phy, true);
पूर्ण

अटल पूर्णांक omap_usb2_disable_घड़ीs(काष्ठा omap_usb *phy)
अणु
	clk_disable_unprepare(phy->wkupclk);
	अगर (!IS_ERR(phy->optclk))
		clk_disable_unprepare(phy->optclk);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_usb2_enable_घड़ीs(काष्ठा omap_usb *phy)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(phy->wkupclk);
	अगर (ret < 0) अणु
		dev_err(phy->dev, "Failed to enable wkupclk %d\n", ret);
		जाओ err0;
	पूर्ण

	अगर (!IS_ERR(phy->optclk)) अणु
		ret = clk_prepare_enable(phy->optclk);
		अगर (ret < 0) अणु
			dev_err(phy->dev, "Failed to enable optclk %d\n", ret);
			जाओ err1;
		पूर्ण
	पूर्ण

	वापस 0;

err1:
	clk_disable(phy->wkupclk);

err0:
	वापस ret;
पूर्ण

अटल पूर्णांक omap_usb_init(काष्ठा phy *x)
अणु
	काष्ठा omap_usb *phy = phy_get_drvdata(x);
	u32 val;

	omap_usb2_enable_घड़ीs(phy);

	अगर (phy->flags & OMAP_USB2_CALIBRATE_FALSE_DISCONNECT) अणु
		/*
		 *
		 * Reduce the sensitivity of पूर्णांकernal PHY by enabling the
		 * DISCON_BYP_LATCH of the USB2PHY_ANA_CONFIG1 रेजिस्टर. This
		 * resolves issues with certain devices which can otherwise
		 * be prone to false disconnects.
		 *
		 */
		val = omap_usb_पढ़ोl(phy->phy_base, USB2PHY_ANA_CONFIG1);
		val |= USB2PHY_DISCON_BYP_LATCH;
		omap_usb_ग_लिखोl(phy->phy_base, USB2PHY_ANA_CONFIG1, val);
	पूर्ण

	अगर (phy->flags & OMAP_USB2_DISABLE_CHRG_DET) अणु
		val = omap_usb_पढ़ोl(phy->phy_base, USB2PHY_CHRG_DET);
		val |= USB2PHY_CHRG_DET_USE_CHG_DET_REG |
		       USB2PHY_CHRG_DET_DIS_CHG_DET;
		omap_usb_ग_लिखोl(phy->phy_base, USB2PHY_CHRG_DET, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omap_usb_निकास(काष्ठा phy *x)
अणु
	काष्ठा omap_usb *phy = phy_get_drvdata(x);

	वापस omap_usb2_disable_घड़ीs(phy);
पूर्ण

अटल स्थिर काष्ठा phy_ops ops = अणु
	.init		= omap_usb_init,
	.निकास		= omap_usb_निकास,
	.घातer_on	= omap_usb_घातer_on,
	.घातer_off	= omap_usb_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा usb_phy_data omap_usb2_data = अणु
	.label = "omap_usb2",
	.flags = OMAP_USB2_HAS_START_SRP | OMAP_USB2_HAS_SET_VBUS,
	.mask = OMAP_DEV_PHY_PD,
	.घातer_off = OMAP_DEV_PHY_PD,
पूर्ण;

अटल स्थिर काष्ठा usb_phy_data omap5_usb2_data = अणु
	.label = "omap5_usb2",
	.flags = 0,
	.mask = OMAP_DEV_PHY_PD,
	.घातer_off = OMAP_DEV_PHY_PD,
पूर्ण;

अटल स्थिर काष्ठा usb_phy_data dra7x_usb2_data = अणु
	.label = "dra7x_usb2",
	.flags = OMAP_USB2_CALIBRATE_FALSE_DISCONNECT,
	.mask = OMAP_DEV_PHY_PD,
	.घातer_off = OMAP_DEV_PHY_PD,
पूर्ण;

अटल स्थिर काष्ठा usb_phy_data dra7x_usb2_phy2_data = अणु
	.label = "dra7x_usb2_phy2",
	.flags = OMAP_USB2_CALIBRATE_FALSE_DISCONNECT,
	.mask = OMAP_USB2_PHY_PD,
	.घातer_off = OMAP_USB2_PHY_PD,
पूर्ण;

अटल स्थिर काष्ठा usb_phy_data am437x_usb2_data = अणु
	.label = "am437x_usb2",
	.flags =  0,
	.mask = AM437X_USB2_PHY_PD | AM437X_USB2_OTG_PD |
		AM437X_USB2_OTGVDET_EN | AM437X_USB2_OTGSESSEND_EN,
	.घातer_on = AM437X_USB2_OTGVDET_EN | AM437X_USB2_OTGSESSEND_EN,
	.घातer_off = AM437X_USB2_PHY_PD | AM437X_USB2_OTG_PD,
पूर्ण;

अटल स्थिर काष्ठा usb_phy_data am654_usb2_data = अणु
	.label = "am654_usb2",
	.flags = OMAP_USB2_CALIBRATE_FALSE_DISCONNECT,
	.mask = AM654_USB2_OTG_PD | AM654_USB2_VBUS_DET_EN |
		AM654_USB2_VBUSVALID_DET_EN,
	.घातer_on = AM654_USB2_VBUS_DET_EN | AM654_USB2_VBUSVALID_DET_EN,
	.घातer_off = AM654_USB2_OTG_PD,
पूर्ण;

अटल स्थिर काष्ठा of_device_id omap_usb2_id_table[] = अणु
	अणु
		.compatible = "ti,omap-usb2",
		.data = &omap_usb2_data,
	पूर्ण,
	अणु
		.compatible = "ti,omap5-usb2",
		.data = &omap5_usb2_data,
	पूर्ण,
	अणु
		.compatible = "ti,dra7x-usb2",
		.data = &dra7x_usb2_data,
	पूर्ण,
	अणु
		.compatible = "ti,dra7x-usb2-phy2",
		.data = &dra7x_usb2_phy2_data,
	पूर्ण,
	अणु
		.compatible = "ti,am437x-usb2",
		.data = &am437x_usb2_data,
	पूर्ण,
	अणु
		.compatible = "ti,am654-usb2",
		.data = &am654_usb2_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_usb2_id_table);

अटल व्योम omap_usb2_init_errata(काष्ठा omap_usb *phy)
अणु
	अटल स्थिर काष्ठा soc_device_attribute am65x_sr10_soc_devices[] = अणु
		अणु .family = "AM65X", .revision = "SR1.0" पूर्ण,
		अणु /* sentinel */ पूर्ण
	पूर्ण;

	/*
	 * Errata i2075: USB2PHY: USB2PHY Charger Detect is Enabled by
	 * Default Without VBUS Presence.
	 *
	 * AM654x SR1.0 has a silicon bug due to which D+ is pulled high after
	 * POR, which could cause क्रमागतeration failure with some USB hubs.
	 * Disabling the USB2_PHY Charger Detect function will put D+
	 * पूर्णांकo the normal state.
	 */
	अगर (soc_device_match(am65x_sr10_soc_devices))
		phy->flags |= OMAP_USB2_DISABLE_CHRG_DET;
पूर्ण

अटल पूर्णांक omap_usb2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_usb	*phy;
	काष्ठा phy *generic_phy;
	काष्ठा phy_provider *phy_provider;
	काष्ठा usb_otg *otg;
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा device_node *control_node;
	काष्ठा platक्रमm_device *control_pdev;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा usb_phy_data *phy_data;

	of_id = of_match_device(omap_usb2_id_table, &pdev->dev);

	अगर (!of_id)
		वापस -EINVAL;

	phy_data = (काष्ठा usb_phy_data *)of_id->data;

	phy = devm_kzalloc(&pdev->dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	otg = devm_kzalloc(&pdev->dev, माप(*otg), GFP_KERNEL);
	अगर (!otg)
		वापस -ENOMEM;

	phy->dev		= &pdev->dev;

	phy->phy.dev		= phy->dev;
	phy->phy.label		= phy_data->label;
	phy->phy.otg		= otg;
	phy->phy.type		= USB_PHY_TYPE_USB2;
	phy->mask		= phy_data->mask;
	phy->घातer_on		= phy_data->घातer_on;
	phy->घातer_off		= phy_data->घातer_off;
	phy->flags		= phy_data->flags;

	omap_usb2_init_errata(phy);

	phy->phy_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(phy->phy_base))
		वापस PTR_ERR(phy->phy_base);

	phy->syscon_phy_घातer = syscon_regmap_lookup_by_phandle(node,
								"syscon-phy-power");
	अगर (IS_ERR(phy->syscon_phy_घातer)) अणु
		dev_dbg(&pdev->dev,
			"can't get syscon-phy-power, using control device\n");
		phy->syscon_phy_घातer = शून्य;

		control_node = of_parse_phandle(node, "ctrl-module", 0);
		अगर (!control_node) अणु
			dev_err(&pdev->dev,
				"Failed to get control device phandle\n");
			वापस -EINVAL;
		पूर्ण

		control_pdev = of_find_device_by_node(control_node);
		अगर (!control_pdev) अणु
			dev_err(&pdev->dev, "Failed to get control device\n");
			वापस -EINVAL;
		पूर्ण
		phy->control_dev = &control_pdev->dev;
	पूर्ण अन्यथा अणु
		अगर (of_property_पढ़ो_u32_index(node,
					       "syscon-phy-power", 1,
					       &phy->घातer_reg)) अणु
			dev_err(&pdev->dev,
				"couldn't get power reg. offset\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	phy->wkupclk = devm_clk_get(phy->dev, "wkupclk");
	अगर (IS_ERR(phy->wkupclk)) अणु
		अगर (PTR_ERR(phy->wkupclk) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		dev_warn(&pdev->dev, "unable to get wkupclk %ld, trying old name\n",
			 PTR_ERR(phy->wkupclk));
		phy->wkupclk = devm_clk_get(phy->dev, "usb_phy_cm_clk32k");

		अगर (IS_ERR(phy->wkupclk)) अणु
			अगर (PTR_ERR(phy->wkupclk) != -EPROBE_DEFER)
				dev_err(&pdev->dev, "unable to get usb_phy_cm_clk32k\n");
			वापस PTR_ERR(phy->wkupclk);
		पूर्ण

		dev_warn(&pdev->dev,
			 "found usb_phy_cm_clk32k, please fix DTS\n");
	पूर्ण

	phy->optclk = devm_clk_get(phy->dev, "refclk");
	अगर (IS_ERR(phy->optclk)) अणु
		अगर (PTR_ERR(phy->optclk) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		dev_dbg(&pdev->dev, "unable to get refclk, trying old name\n");
		phy->optclk = devm_clk_get(phy->dev, "usb_otg_ss_refclk960m");

		अगर (IS_ERR(phy->optclk)) अणु
			अगर (PTR_ERR(phy->optclk) != -EPROBE_DEFER) अणु
				dev_dbg(&pdev->dev,
					"unable to get usb_otg_ss_refclk960m\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_warn(&pdev->dev,
				 "found usb_otg_ss_refclk960m, please fix DTS\n");
		पूर्ण
	पूर्ण

	otg->set_host = omap_usb_set_host;
	otg->set_peripheral = omap_usb_set_peripheral;
	अगर (phy_data->flags & OMAP_USB2_HAS_SET_VBUS)
		otg->set_vbus = omap_usb_set_vbus;
	अगर (phy_data->flags & OMAP_USB2_HAS_START_SRP)
		otg->start_srp = omap_usb_start_srp;
	otg->usb_phy = &phy->phy;

	platक्रमm_set_drvdata(pdev, phy);
	pm_runसमय_enable(phy->dev);

	generic_phy = devm_phy_create(phy->dev, शून्य, &ops);
	अगर (IS_ERR(generic_phy)) अणु
		pm_runसमय_disable(phy->dev);
		वापस PTR_ERR(generic_phy);
	पूर्ण

	phy_set_drvdata(generic_phy, phy);
	omap_usb_घातer_off(generic_phy);

	phy_provider = devm_of_phy_provider_रेजिस्टर(phy->dev,
						     of_phy_simple_xlate);
	अगर (IS_ERR(phy_provider)) अणु
		pm_runसमय_disable(phy->dev);
		वापस PTR_ERR(phy_provider);
	पूर्ण

	usb_add_phy_dev(&phy->phy);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_usb2_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_usb	*phy = platक्रमm_get_drvdata(pdev);

	usb_हटाओ_phy(&phy->phy);
	pm_runसमय_disable(phy->dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver omap_usb2_driver = अणु
	.probe		= omap_usb2_probe,
	.हटाओ		= omap_usb2_हटाओ,
	.driver		= अणु
		.name	= "omap-usb2",
		.of_match_table = omap_usb2_id_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(omap_usb2_driver);

MODULE_ALIAS("platform:omap_usb2");
MODULE_AUTHOR("Texas Instruments Inc.");
MODULE_DESCRIPTION("OMAP USB2 phy driver");
MODULE_LICENSE("GPL v2");
