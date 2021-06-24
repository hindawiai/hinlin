<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Phy provider क्रम USB 3.0 controller on HiSilicon 3660 platक्रमm
 *
 * Copyright (C) 2017-2018 Hilisicon Electronics Co., Ltd.
 *		http://www.huawei.com
 *
 * Authors: Yu Chen <chenyu56@huawei.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा PERI_CRG_CLK_EN4			0x40
#घोषणा PERI_CRG_CLK_DIS4			0x44
#घोषणा GT_CLK_USB3OTG_REF			BIT(0)
#घोषणा GT_ACLK_USB3OTG				BIT(1)

#घोषणा PERI_CRG_RSTEN4				0x90
#घोषणा PERI_CRG_RSTDIS4			0x94
#घोषणा IP_RST_USB3OTGPHY_POR			BIT(3)
#घोषणा IP_RST_USB3OTG				BIT(5)

#घोषणा PERI_CRG_ISODIS				0x148
#घोषणा USB_REFCLK_ISO_EN			BIT(25)

#घोषणा PCTRL_PERI_CTRL3			0x10
#घोषणा PCTRL_PERI_CTRL3_MSK_START		16
#घोषणा USB_TCXO_EN				BIT(1)

#घोषणा PCTRL_PERI_CTRL24			0x64
#घोषणा SC_CLK_USB3PHY_3MUX1_SEL		BIT(25)

#घोषणा USBOTG3_CTRL0				0x00
#घोषणा SC_USB3PHY_ABB_GT_EN			BIT(15)

#घोषणा USBOTG3_CTRL2				0x08
#घोषणा USBOTG3CTRL2_POWERDOWN_HSP		BIT(0)
#घोषणा USBOTG3CTRL2_POWERDOWN_SSP		BIT(1)

#घोषणा USBOTG3_CTRL3				0x0C
#घोषणा USBOTG3_CTRL3_VBUSVLDEXT		BIT(6)
#घोषणा USBOTG3_CTRL3_VBUSVLDEXTSEL		BIT(5)

#घोषणा USBOTG3_CTRL4				0x10

#घोषणा USBOTG3_CTRL7				0x1c
#घोषणा REF_SSP_EN				BIT(16)

/* This value config the शेष txtune parameter of the usb 2.0 phy */
#घोषणा HI3660_USB_DEFAULT_PHY_PARAM		0x1c466e3

काष्ठा hi3660_priv अणु
	काष्ठा device *dev;
	काष्ठा regmap *peri_crg;
	काष्ठा regmap *pctrl;
	काष्ठा regmap *otg_bc;
	u32 eye_diagram_param;
पूर्ण;

अटल पूर्णांक hi3660_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा hi3660_priv *priv = phy_get_drvdata(phy);
	u32 val, mask;
	पूर्णांक ret;

	/* usb refclk iso disable */
	ret = regmap_ग_लिखो(priv->peri_crg, PERI_CRG_ISODIS, USB_REFCLK_ISO_EN);
	अगर (ret)
		जाओ out;

	/* enable usb_tcxo_en */
	val = USB_TCXO_EN | (USB_TCXO_EN << PCTRL_PERI_CTRL3_MSK_START);
	ret = regmap_ग_लिखो(priv->pctrl, PCTRL_PERI_CTRL3, val);
	अगर (ret)
		जाओ out;

	/* निश्चित phy */
	val = IP_RST_USB3OTGPHY_POR | IP_RST_USB3OTG;
	ret = regmap_ग_लिखो(priv->peri_crg, PERI_CRG_RSTEN4, val);
	अगर (ret)
		जाओ out;

	/* enable phy ref clk */
	val = SC_USB3PHY_ABB_GT_EN;
	mask = val;
	ret = regmap_update_bits(priv->otg_bc, USBOTG3_CTRL0, mask, val);
	अगर (ret)
		जाओ out;

	val = REF_SSP_EN;
	mask = val;
	ret = regmap_update_bits(priv->otg_bc, USBOTG3_CTRL7, mask, val);
	अगर (ret)
		जाओ out;

	/* निकास from IDDQ mode */
	mask = USBOTG3CTRL2_POWERDOWN_HSP | USBOTG3CTRL2_POWERDOWN_SSP;
	ret = regmap_update_bits(priv->otg_bc, USBOTG3_CTRL2, mask, 0);
	अगर (ret)
		जाओ out;

	/* delay क्रम निकास from IDDQ mode */
	usleep_range(100, 120);

	/* deनिश्चित phy */
	val = IP_RST_USB3OTGPHY_POR | IP_RST_USB3OTG;
	ret = regmap_ग_लिखो(priv->peri_crg, PERI_CRG_RSTDIS4, val);
	अगर (ret)
		जाओ out;

	/* delay क्रम phy deनिश्चितed */
	usleep_range(10000, 15000);

	/* fake vbus valid संकेत */
	val = USBOTG3_CTRL3_VBUSVLDEXT | USBOTG3_CTRL3_VBUSVLDEXTSEL;
	mask = val;
	ret = regmap_update_bits(priv->otg_bc, USBOTG3_CTRL3, mask, val);
	अगर (ret)
		जाओ out;

	/* delay क्रम vbus valid */
	usleep_range(100, 120);

	ret = regmap_ग_लिखो(priv->otg_bc, USBOTG3_CTRL4,
			priv->eye_diagram_param);
	अगर (ret)
		जाओ out;

	वापस 0;
out:
	dev_err(priv->dev, "failed to init phy ret: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hi3660_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा hi3660_priv *priv = phy_get_drvdata(phy);
	u32 val;
	पूर्णांक ret;

	/* निश्चित phy */
	val = IP_RST_USB3OTGPHY_POR;
	ret = regmap_ग_लिखो(priv->peri_crg, PERI_CRG_RSTEN4, val);
	अगर (ret)
		जाओ out;

	/* disable usb_tcxo_en */
	val = USB_TCXO_EN << PCTRL_PERI_CTRL3_MSK_START;
	ret = regmap_ग_लिखो(priv->pctrl, PCTRL_PERI_CTRL3, val);
	अगर (ret)
		जाओ out;

	वापस 0;
out:
	dev_err(priv->dev, "failed to exit phy ret: %d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा phy_ops hi3660_phy_ops = अणु
	.init		= hi3660_phy_init,
	.निकास		= hi3660_phy_निकास,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक hi3660_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *phy_provider;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy *phy;
	काष्ठा hi3660_priv *priv;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;
	priv->peri_crg = syscon_regmap_lookup_by_phandle(dev->of_node,
					"hisilicon,pericrg-syscon");
	अगर (IS_ERR(priv->peri_crg)) अणु
		dev_err(dev, "no hisilicon,pericrg-syscon\n");
		वापस PTR_ERR(priv->peri_crg);
	पूर्ण

	priv->pctrl = syscon_regmap_lookup_by_phandle(dev->of_node,
					"hisilicon,pctrl-syscon");
	अगर (IS_ERR(priv->pctrl)) अणु
		dev_err(dev, "no hisilicon,pctrl-syscon\n");
		वापस PTR_ERR(priv->pctrl);
	पूर्ण

	/* node of hi3660 phy is a sub-node of usb3_otg_bc */
	priv->otg_bc = syscon_node_to_regmap(dev->parent->of_node);
	अगर (IS_ERR(priv->otg_bc)) अणु
		dev_err(dev, "no hisilicon,usb3-otg-bc-syscon\n");
		वापस PTR_ERR(priv->otg_bc);
	पूर्ण

	अगर (of_property_पढ़ो_u32(dev->of_node, "hisilicon,eye-diagram-param",
		&(priv->eye_diagram_param)))
		priv->eye_diagram_param = HI3660_USB_DEFAULT_PHY_PARAM;

	phy = devm_phy_create(dev, शून्य, &hi3660_phy_ops);
	अगर (IS_ERR(phy))
		वापस PTR_ERR(phy);

	phy_set_drvdata(phy, priv);
	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id hi3660_phy_of_match[] = अणु
	अणु.compatible = "hisilicon,hi3660-usb-phy",पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hi3660_phy_of_match);

अटल काष्ठा platक्रमm_driver hi3660_phy_driver = अणु
	.probe	= hi3660_phy_probe,
	.driver = अणु
		.name	= "hi3660-usb-phy",
		.of_match_table	= hi3660_phy_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(hi3660_phy_driver);

MODULE_AUTHOR("Yu Chen <chenyu56@huawei.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Hilisicon Hi3660 USB3 PHY Driver");
