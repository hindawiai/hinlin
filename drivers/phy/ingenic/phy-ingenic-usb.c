<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Ingenic SoCs USB PHY driver
 * Copyright (c) Paul Cercueil <paul@crapouillou.net>
 * Copyright (c) ौञ़छौ/ (Qi Pengzhen) <aric.pzqi@ingenic.com>
 * Copyright (c) ोउॉओौओ (Zhou Yanjie) <zhouyanjie@wanyeetech.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

/* OTGPHY रेजिस्टर offsets */
#घोषणा REG_USBPCR_OFFSET			0x00
#घोषणा REG_USBRDT_OFFSET			0x04
#घोषणा REG_USBVBFIL_OFFSET			0x08
#घोषणा REG_USBPCR1_OFFSET			0x0c

/* bits within the USBPCR रेजिस्टर */
#घोषणा USBPCR_USB_MODE				BIT(31)
#घोषणा USBPCR_AVLD_REG				BIT(30)
#घोषणा USBPCR_COMMONONN			BIT(25)
#घोषणा USBPCR_VBUSVLDEXT			BIT(24)
#घोषणा USBPCR_VBUSVLDEXTSEL		BIT(23)
#घोषणा USBPCR_POR					BIT(22)
#घोषणा USBPCR_SIDDQ				BIT(21)
#घोषणा USBPCR_OTG_DISABLE			BIT(20)
#घोषणा USBPCR_TXPREEMPHTUNE		BIT(6)

#घोषणा USBPCR_IDPULLUP_MASK		GENMASK(29, 28)
#घोषणा USBPCR_IDPULLUP_ALWAYS		0x2
#घोषणा USBPCR_IDPULLUP_SUSPEND		0x1
#घोषणा USBPCR_IDPULLUP_OTG			0x0

#घोषणा USBPCR_COMPDISTUNE_MASK		GENMASK(19, 17)
#घोषणा USBPCR_COMPDISTUNE_DFT		0x4

#घोषणा USBPCR_OTGTUNE_MASK			GENMASK(16, 14)
#घोषणा USBPCR_OTGTUNE_DFT			0x4

#घोषणा USBPCR_SQRXTUNE_MASK		GENMASK(13, 11)
#घोषणा USBPCR_SQRXTUNE_DCR_20PCT	0x7
#घोषणा USBPCR_SQRXTUNE_DFT			0x3

#घोषणा USBPCR_TXFSLSTUNE_MASK		GENMASK(10, 7)
#घोषणा USBPCR_TXFSLSTUNE_DCR_50PPT	0xf
#घोषणा USBPCR_TXFSLSTUNE_DCR_25PPT	0x7
#घोषणा USBPCR_TXFSLSTUNE_DFT		0x3
#घोषणा USBPCR_TXFSLSTUNE_INC_25PPT	0x1
#घोषणा USBPCR_TXFSLSTUNE_INC_50PPT	0x0

#घोषणा USBPCR_TXHSXVTUNE_MASK		GENMASK(5, 4)
#घोषणा USBPCR_TXHSXVTUNE_DFT		0x3
#घोषणा USBPCR_TXHSXVTUNE_DCR_15MV	0x1

#घोषणा USBPCR_TXRISETUNE_MASK		GENMASK(5, 4)
#घोषणा USBPCR_TXRISETUNE_DFT		0x3

#घोषणा USBPCR_TXVREFTUNE_MASK		GENMASK(3, 0)
#घोषणा USBPCR_TXVREFTUNE_INC_75PPT	0xb
#घोषणा USBPCR_TXVREFTUNE_INC_25PPT	0x7
#घोषणा USBPCR_TXVREFTUNE_DFT		0x5

/* bits within the USBRDTR रेजिस्टर */
#घोषणा USBRDT_UTMI_RST				BIT(27)
#घोषणा USBRDT_HB_MASK				BIT(26)
#घोषणा USBRDT_VBFIL_LD_EN			BIT(25)
#घोषणा USBRDT_IDDIG_EN				BIT(24)
#घोषणा USBRDT_IDDIG_REG			BIT(23)
#घोषणा USBRDT_VBFIL_EN				BIT(2)

/* bits within the USBPCR1 रेजिस्टर */
#घोषणा USBPCR1_BVLD_REG			BIT(31)
#घोषणा USBPCR1_DPPD				BIT(29)
#घोषणा USBPCR1_DMPD				BIT(28)
#घोषणा USBPCR1_USB_SEL				BIT(28)
#घोषणा USBPCR1_PORT_RST			BIT(21)
#घोषणा USBPCR1_WORD_IF_16BIT		BIT(19)

काष्ठा ingenic_soc_info अणु
	व्योम (*usb_phy_init)(काष्ठा phy *phy);
पूर्ण;

काष्ठा ingenic_usb_phy अणु
	स्थिर काष्ठा ingenic_soc_info *soc_info;

	काष्ठा phy *phy;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा regulator *vcc_supply;
पूर्ण;

अटल पूर्णांक ingenic_usb_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा ingenic_usb_phy *priv = phy_get_drvdata(phy);
	पूर्णांक err;
	u32 reg;

	err = clk_prepare_enable(priv->clk);
	अगर (err) अणु
		dev_err(&phy->dev, "Unable to start clock: %d\n", err);
		वापस err;
	पूर्ण

	priv->soc_info->usb_phy_init(phy);

	/* Wait क्रम PHY to reset */
	usleep_range(30, 300);
	reg = पढ़ोl(priv->base + REG_USBPCR_OFFSET);
	ग_लिखोl(reg & ~USBPCR_POR, priv->base + REG_USBPCR_OFFSET);
	usleep_range(300, 1000);

	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_usb_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा ingenic_usb_phy *priv = phy_get_drvdata(phy);

	clk_disable_unprepare(priv->clk);
	regulator_disable(priv->vcc_supply);

	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_usb_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा ingenic_usb_phy *priv = phy_get_drvdata(phy);
	पूर्णांक err;

	err = regulator_enable(priv->vcc_supply);
	अगर (err) अणु
		dev_err(&phy->dev, "Unable to enable VCC: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_usb_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा ingenic_usb_phy *priv = phy_get_drvdata(phy);

	regulator_disable(priv->vcc_supply);

	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_usb_phy_set_mode(काष्ठा phy *phy,
				  क्रमागत phy_mode mode, पूर्णांक submode)
अणु
	काष्ठा ingenic_usb_phy *priv = phy_get_drvdata(phy);
	u32 reg;

	चयन (mode) अणु
	हाल PHY_MODE_USB_HOST:
		reg = पढ़ोl(priv->base + REG_USBPCR_OFFSET);
		u32p_replace_bits(&reg, 1, USBPCR_USB_MODE);
		u32p_replace_bits(&reg, 0, USBPCR_VBUSVLDEXT);
		u32p_replace_bits(&reg, 0, USBPCR_VBUSVLDEXTSEL);
		u32p_replace_bits(&reg, 0, USBPCR_OTG_DISABLE);
		ग_लिखोl(reg, priv->base + REG_USBPCR_OFFSET);

		अवरोध;
	हाल PHY_MODE_USB_DEVICE:
		reg = पढ़ोl(priv->base + REG_USBPCR_OFFSET);
		u32p_replace_bits(&reg, 0, USBPCR_USB_MODE);
		u32p_replace_bits(&reg, 1, USBPCR_VBUSVLDEXT);
		u32p_replace_bits(&reg, 1, USBPCR_VBUSVLDEXTSEL);
		u32p_replace_bits(&reg, 1, USBPCR_OTG_DISABLE);
		ग_लिखोl(reg, priv->base + REG_USBPCR_OFFSET);

		अवरोध;
	हाल PHY_MODE_USB_OTG:
		reg = पढ़ोl(priv->base + REG_USBPCR_OFFSET);
		u32p_replace_bits(&reg, 1, USBPCR_USB_MODE);
		u32p_replace_bits(&reg, 1, USBPCR_VBUSVLDEXT);
		u32p_replace_bits(&reg, 1, USBPCR_VBUSVLDEXTSEL);
		u32p_replace_bits(&reg, 0, USBPCR_OTG_DISABLE);
		ग_लिखोl(reg, priv->base + REG_USBPCR_OFFSET);

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops ingenic_usb_phy_ops = अणु
	.init		= ingenic_usb_phy_init,
	.निकास		= ingenic_usb_phy_निकास,
	.घातer_on	= ingenic_usb_phy_घातer_on,
	.घातer_off	= ingenic_usb_phy_घातer_off,
	.set_mode	= ingenic_usb_phy_set_mode,
	.owner		= THIS_MODULE,
पूर्ण;

अटल व्योम jz4770_usb_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा ingenic_usb_phy *priv = phy_get_drvdata(phy);
	u32 reg;

	reg = USBPCR_AVLD_REG | USBPCR_COMMONONN | USBPCR_POR |
		FIELD_PREP(USBPCR_IDPULLUP_MASK, USBPCR_IDPULLUP_ALWAYS) |
		FIELD_PREP(USBPCR_COMPDISTUNE_MASK, USBPCR_COMPDISTUNE_DFT) |
		FIELD_PREP(USBPCR_OTGTUNE_MASK, USBPCR_OTGTUNE_DFT) |
		FIELD_PREP(USBPCR_SQRXTUNE_MASK, USBPCR_SQRXTUNE_DFT) |
		FIELD_PREP(USBPCR_TXFSLSTUNE_MASK, USBPCR_TXFSLSTUNE_DFT) |
		FIELD_PREP(USBPCR_TXRISETUNE_MASK, USBPCR_TXRISETUNE_DFT) |
		FIELD_PREP(USBPCR_TXVREFTUNE_MASK, USBPCR_TXVREFTUNE_DFT);
	ग_लिखोl(reg, priv->base + REG_USBPCR_OFFSET);
पूर्ण

अटल व्योम jz4775_usb_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा ingenic_usb_phy *priv = phy_get_drvdata(phy);
	u32 reg;

	reg = पढ़ोl(priv->base + REG_USBPCR1_OFFSET) | USBPCR1_USB_SEL |
		USBPCR1_WORD_IF_16BIT;
	ग_लिखोl(reg, priv->base + REG_USBPCR1_OFFSET);

	reg = USBPCR_COMMONONN | USBPCR_POR |
		FIELD_PREP(USBPCR_TXVREFTUNE_MASK, USBPCR_TXVREFTUNE_INC_75PPT);
	ग_लिखोl(reg, priv->base + REG_USBPCR_OFFSET);
पूर्ण

अटल व्योम jz4780_usb_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा ingenic_usb_phy *priv = phy_get_drvdata(phy);
	u32 reg;

	reg = पढ़ोl(priv->base + REG_USBPCR1_OFFSET) | USBPCR1_USB_SEL |
		USBPCR1_WORD_IF_16BIT;
	ग_लिखोl(reg, priv->base + REG_USBPCR1_OFFSET);

	reg = USBPCR_TXPREEMPHTUNE | USBPCR_COMMONONN | USBPCR_POR;
	ग_लिखोl(reg, priv->base + REG_USBPCR_OFFSET);
पूर्ण

अटल व्योम x1000_usb_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा ingenic_usb_phy *priv = phy_get_drvdata(phy);
	u32 reg;

	reg = पढ़ोl(priv->base + REG_USBPCR1_OFFSET) | USBPCR1_WORD_IF_16BIT;
	ग_लिखोl(reg, priv->base + REG_USBPCR1_OFFSET);

	reg = USBPCR_TXPREEMPHTUNE | USBPCR_COMMONONN | USBPCR_POR |
		FIELD_PREP(USBPCR_SQRXTUNE_MASK, USBPCR_SQRXTUNE_DCR_20PCT) |
		FIELD_PREP(USBPCR_TXHSXVTUNE_MASK, USBPCR_TXHSXVTUNE_DCR_15MV) |
		FIELD_PREP(USBPCR_TXVREFTUNE_MASK, USBPCR_TXVREFTUNE_INC_25PPT);
	ग_लिखोl(reg, priv->base + REG_USBPCR_OFFSET);
पूर्ण

अटल व्योम x1830_usb_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा ingenic_usb_phy *priv = phy_get_drvdata(phy);
	u32 reg;

	/* rdt */
	ग_लिखोl(USBRDT_VBFIL_EN | USBRDT_UTMI_RST, priv->base + REG_USBRDT_OFFSET);

	reg = पढ़ोl(priv->base + REG_USBPCR1_OFFSET) | USBPCR1_WORD_IF_16BIT |
		USBPCR1_DMPD | USBPCR1_DPPD;
	ग_लिखोl(reg, priv->base + REG_USBPCR1_OFFSET);

	reg = USBPCR_VBUSVLDEXT | USBPCR_TXPREEMPHTUNE | USBPCR_COMMONONN | USBPCR_POR |
		FIELD_PREP(USBPCR_IDPULLUP_MASK, USBPCR_IDPULLUP_OTG);
	ग_लिखोl(reg, priv->base + REG_USBPCR_OFFSET);
पूर्ण

अटल व्योम x2000_usb_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा ingenic_usb_phy *priv = phy_get_drvdata(phy);
	u32 reg;

	reg = पढ़ोl(priv->base + REG_USBPCR1_OFFSET) | USBPCR1_DPPD | USBPCR1_DMPD;
	ग_लिखोl(reg & ~USBPCR1_PORT_RST, priv->base + REG_USBPCR1_OFFSET);

	reg = USBPCR_POR | FIELD_PREP(USBPCR_IDPULLUP_MASK, USBPCR_IDPULLUP_OTG);
	ग_लिखोl(reg, priv->base + REG_USBPCR_OFFSET);
पूर्ण

अटल स्थिर काष्ठा ingenic_soc_info jz4770_soc_info = अणु
	.usb_phy_init = jz4770_usb_phy_init,
पूर्ण;

अटल स्थिर काष्ठा ingenic_soc_info jz4775_soc_info = अणु
	.usb_phy_init = jz4775_usb_phy_init,
पूर्ण;

अटल स्थिर काष्ठा ingenic_soc_info jz4780_soc_info = अणु
	.usb_phy_init = jz4780_usb_phy_init,
पूर्ण;

अटल स्थिर काष्ठा ingenic_soc_info x1000_soc_info = अणु
	.usb_phy_init = x1000_usb_phy_init,
पूर्ण;

अटल स्थिर काष्ठा ingenic_soc_info x1830_soc_info = अणु
	.usb_phy_init = x1830_usb_phy_init,
पूर्ण;

अटल स्थिर काष्ठा ingenic_soc_info x2000_soc_info = अणु
	.usb_phy_init = x2000_usb_phy_init,
पूर्ण;

अटल पूर्णांक ingenic_usb_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ingenic_usb_phy *priv;
	काष्ठा phy_provider *provider;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक err;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->soc_info = device_get_match_data(dev);
	अगर (!priv->soc_info) अणु
		dev_err(dev, "Error: No device match found\n");
		वापस -ENODEV;
	पूर्ण

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base)) अणु
		dev_err(dev, "Failed to map registers\n");
		वापस PTR_ERR(priv->base);
	पूर्ण

	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		err = PTR_ERR(priv->clk);
		अगर (err != -EPROBE_DEFER)
			dev_err(dev, "Failed to get clock\n");
		वापस err;
	पूर्ण

	priv->vcc_supply = devm_regulator_get(dev, "vcc");
	अगर (IS_ERR(priv->vcc_supply)) अणु
		err = PTR_ERR(priv->vcc_supply);
		अगर (err != -EPROBE_DEFER)
			dev_err(dev, "Failed to get regulator\n");
		वापस err;
	पूर्ण

	priv->phy = devm_phy_create(dev, शून्य, &ingenic_usb_phy_ops);
	अगर (IS_ERR(priv->phy))
		वापस PTR_ERR(priv->phy);

	phy_set_drvdata(priv->phy, priv);

	provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id ingenic_usb_phy_of_matches[] = अणु
	अणु .compatible = "ingenic,jz4770-phy", .data = &jz4770_soc_info पूर्ण,
	अणु .compatible = "ingenic,jz4775-phy", .data = &jz4775_soc_info पूर्ण,
	अणु .compatible = "ingenic,jz4780-phy", .data = &jz4780_soc_info पूर्ण,
	अणु .compatible = "ingenic,x1000-phy", .data = &x1000_soc_info पूर्ण,
	अणु .compatible = "ingenic,x1830-phy", .data = &x1830_soc_info पूर्ण,
	अणु .compatible = "ingenic,x2000-phy", .data = &x2000_soc_info पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ingenic_usb_phy_of_matches);

अटल काष्ठा platक्रमm_driver ingenic_usb_phy_driver = अणु
	.probe		= ingenic_usb_phy_probe,
	.driver		= अणु
		.name	= "ingenic-usb-phy",
		.of_match_table = ingenic_usb_phy_of_matches,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ingenic_usb_phy_driver);

MODULE_AUTHOR("ोउॉओौओ (Zhou Yanjie) <zhouyanjie@wanyeetech.com>");
MODULE_AUTHOR("ौञ़छौ/ (Qi Pengzhen) <aric.pzqi@ingenic.com>");
MODULE_AUTHOR("Paul Cercueil <paul@crapouillou.net>");
MODULE_DESCRIPTION("Ingenic SoCs USB PHY driver");
MODULE_LICENSE("GPL");
