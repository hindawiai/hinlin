<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2015 Linaro Ltd.
 * Copyright (c) 2015 HiSilicon Limited.
 */

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regmap.h>

#घोषणा SC_PERIPH_CTRL4			0x00c

#घोषणा CTRL4_PICO_SIDDQ		BIT(6)
#घोषणा CTRL4_PICO_OGDISABLE		BIT(8)
#घोषणा CTRL4_PICO_VBUSVLDEXT		BIT(10)
#घोषणा CTRL4_PICO_VBUSVLDEXTSEL	BIT(11)
#घोषणा CTRL4_OTG_PHY_SEL		BIT(21)

#घोषणा SC_PERIPH_CTRL5			0x010

#घोषणा CTRL5_USBOTG_RES_SEL		BIT(3)
#घोषणा CTRL5_PICOPHY_ACAENB		BIT(4)
#घोषणा CTRL5_PICOPHY_BC_MODE		BIT(5)
#घोषणा CTRL5_PICOPHY_CHRGSEL		BIT(6)
#घोषणा CTRL5_PICOPHY_VDATSRCEND	BIT(7)
#घोषणा CTRL5_PICOPHY_VDATDETENB	BIT(8)
#घोषणा CTRL5_PICOPHY_DCDENB		BIT(9)
#घोषणा CTRL5_PICOPHY_IDDIG		BIT(10)

#घोषणा SC_PERIPH_CTRL8			0x018
#घोषणा SC_PERIPH_RSTEN0		0x300
#घोषणा SC_PERIPH_RSTDIS0		0x304

#घोषणा RST0_USBOTG_BUS			BIT(4)
#घोषणा RST0_POR_PICOPHY		BIT(5)
#घोषणा RST0_USBOTG			BIT(6)
#घोषणा RST0_USBOTG_32K			BIT(7)

#घोषणा EYE_PATTERN_PARA		0x7053348c

काष्ठा hi6220_priv अणु
	काष्ठा regmap *reg;
	काष्ठा device *dev;
पूर्ण;

अटल व्योम hi6220_phy_init(काष्ठा hi6220_priv *priv)
अणु
	काष्ठा regmap *reg = priv->reg;
	u32 val, mask;

	val = RST0_USBOTG_BUS | RST0_POR_PICOPHY |
	      RST0_USBOTG | RST0_USBOTG_32K;
	mask = val;
	regmap_update_bits(reg, SC_PERIPH_RSTEN0, mask, val);
	regmap_update_bits(reg, SC_PERIPH_RSTDIS0, mask, val);
पूर्ण

अटल पूर्णांक hi6220_phy_setup(काष्ठा hi6220_priv *priv, bool on)
अणु
	काष्ठा regmap *reg = priv->reg;
	u32 val, mask;
	पूर्णांक ret;

	अगर (on) अणु
		val = CTRL5_USBOTG_RES_SEL | CTRL5_PICOPHY_ACAENB;
		mask = val | CTRL5_PICOPHY_BC_MODE;
		ret = regmap_update_bits(reg, SC_PERIPH_CTRL5, mask, val);
		अगर (ret)
			जाओ out;

		val =  CTRL4_PICO_VBUSVLDEXT | CTRL4_PICO_VBUSVLDEXTSEL |
		       CTRL4_OTG_PHY_SEL;
		mask = val | CTRL4_PICO_SIDDQ | CTRL4_PICO_OGDISABLE;
		ret = regmap_update_bits(reg, SC_PERIPH_CTRL4, mask, val);
		अगर (ret)
			जाओ out;

		ret = regmap_ग_लिखो(reg, SC_PERIPH_CTRL8, EYE_PATTERN_PARA);
		अगर (ret)
			जाओ out;
	पूर्ण अन्यथा अणु
		val = CTRL4_PICO_SIDDQ;
		mask = val;
		ret = regmap_update_bits(reg, SC_PERIPH_CTRL4, mask, val);
		अगर (ret)
			जाओ out;
	पूर्ण

	वापस 0;
out:
	dev_err(priv->dev, "failed to setup phy ret: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hi6220_phy_start(काष्ठा phy *phy)
अणु
	काष्ठा hi6220_priv *priv = phy_get_drvdata(phy);

	वापस hi6220_phy_setup(priv, true);
पूर्ण

अटल पूर्णांक hi6220_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा hi6220_priv *priv = phy_get_drvdata(phy);

	वापस hi6220_phy_setup(priv, false);
पूर्ण

अटल स्थिर काष्ठा phy_ops hi6220_phy_ops = अणु
	.init		= hi6220_phy_start,
	.निकास		= hi6220_phy_निकास,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक hi6220_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *phy_provider;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy *phy;
	काष्ठा hi6220_priv *priv;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;
	priv->reg = syscon_regmap_lookup_by_phandle(dev->of_node,
					"hisilicon,peripheral-syscon");
	अगर (IS_ERR(priv->reg)) अणु
		dev_err(dev, "no hisilicon,peripheral-syscon\n");
		वापस PTR_ERR(priv->reg);
	पूर्ण

	hi6220_phy_init(priv);

	phy = devm_phy_create(dev, शून्य, &hi6220_phy_ops);
	अगर (IS_ERR(phy))
		वापस PTR_ERR(phy);

	phy_set_drvdata(phy, priv);
	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id hi6220_phy_of_match[] = अणु
	अणु.compatible = "hisilicon,hi6220-usb-phy",पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hi6220_phy_of_match);

अटल काष्ठा platक्रमm_driver hi6220_phy_driver = अणु
	.probe	= hi6220_phy_probe,
	.driver = अणु
		.name	= "hi6220-usb-phy",
		.of_match_table	= hi6220_phy_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(hi6220_phy_driver);

MODULE_DESCRIPTION("HISILICON HI6220 USB PHY driver");
MODULE_ALIAS("platform:hi6220-usb-phy");
MODULE_LICENSE("GPL");
