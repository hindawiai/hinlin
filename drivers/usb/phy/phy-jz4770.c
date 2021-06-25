<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Ingenic SoCs USB PHY driver
 * Copyright (c) Paul Cercueil <paul@crapouillou.net>
 * Copyright (c) ौञ़छौ/ (Qi Pengzhen) <aric.pzqi@ingenic.com>
 * Copyright (c) ोउॉओौओ (Zhou Yanjie) <zhouyanjie@wanyeetech.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/phy.h>

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

#घोषणा USBPCR_IDPULLUP_LSB	28
#घोषणा USBPCR_IDPULLUP_MASK		GENMASK(29, USBPCR_IDPULLUP_LSB)
#घोषणा USBPCR_IDPULLUP_ALWAYS		(0x2 << USBPCR_IDPULLUP_LSB)
#घोषणा USBPCR_IDPULLUP_SUSPEND		(0x1 << USBPCR_IDPULLUP_LSB)
#घोषणा USBPCR_IDPULLUP_OTG			(0x0 << USBPCR_IDPULLUP_LSB)

#घोषणा USBPCR_COMPDISTUNE_LSB		17
#घोषणा USBPCR_COMPDISTUNE_MASK		GENMASK(19, USBPCR_COMPDISTUNE_LSB)
#घोषणा USBPCR_COMPDISTUNE_DFT		(0x4 << USBPCR_COMPDISTUNE_LSB)

#घोषणा USBPCR_OTGTUNE_LSB			14
#घोषणा USBPCR_OTGTUNE_MASK			GENMASK(16, USBPCR_OTGTUNE_LSB)
#घोषणा USBPCR_OTGTUNE_DFT			(0x4 << USBPCR_OTGTUNE_LSB)

#घोषणा USBPCR_SQRXTUNE_LSB	11
#घोषणा USBPCR_SQRXTUNE_MASK		GENMASK(13, USBPCR_SQRXTUNE_LSB)
#घोषणा USBPCR_SQRXTUNE_DCR_20PCT	(0x7 << USBPCR_SQRXTUNE_LSB)
#घोषणा USBPCR_SQRXTUNE_DFT			(0x3 << USBPCR_SQRXTUNE_LSB)

#घोषणा USBPCR_TXFSLSTUNE_LSB		7
#घोषणा USBPCR_TXFSLSTUNE_MASK		GENMASK(10, USBPCR_TXFSLSTUNE_LSB)
#घोषणा USBPCR_TXFSLSTUNE_DCR_50PPT	(0xf << USBPCR_TXFSLSTUNE_LSB)
#घोषणा USBPCR_TXFSLSTUNE_DCR_25PPT	(0x7 << USBPCR_TXFSLSTUNE_LSB)
#घोषणा USBPCR_TXFSLSTUNE_DFT		(0x3 << USBPCR_TXFSLSTUNE_LSB)
#घोषणा USBPCR_TXFSLSTUNE_INC_25PPT	(0x1 << USBPCR_TXFSLSTUNE_LSB)
#घोषणा USBPCR_TXFSLSTUNE_INC_50PPT	(0x0 << USBPCR_TXFSLSTUNE_LSB)

#घोषणा USBPCR_TXHSXVTUNE_LSB		4
#घोषणा USBPCR_TXHSXVTUNE_MASK		GENMASK(5, USBPCR_TXHSXVTUNE_LSB)
#घोषणा USBPCR_TXHSXVTUNE_DFT		(0x3 << USBPCR_TXHSXVTUNE_LSB)
#घोषणा USBPCR_TXHSXVTUNE_DCR_15MV	(0x1 << USBPCR_TXHSXVTUNE_LSB)

#घोषणा USBPCR_TXRISETUNE_LSB		4
#घोषणा USBPCR_TXRISETUNE_MASK		GENMASK(5, USBPCR_TXRISETUNE_LSB)
#घोषणा USBPCR_TXRISETUNE_DFT		(0x3 << USBPCR_TXRISETUNE_LSB)

#घोषणा USBPCR_TXVREFTUNE_LSB		0
#घोषणा USBPCR_TXVREFTUNE_MASK		GENMASK(3, USBPCR_TXVREFTUNE_LSB)
#घोषणा USBPCR_TXVREFTUNE_INC_25PPT	(0x7 << USBPCR_TXVREFTUNE_LSB)
#घोषणा USBPCR_TXVREFTUNE_DFT		(0x5 << USBPCR_TXVREFTUNE_LSB)

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
#घोषणा USBPCR1_WORD_IF_16BIT		BIT(19)

क्रमागत ingenic_usb_phy_version अणु
	ID_JZ4770,
	ID_JZ4780,
	ID_X1000,
	ID_X1830,
पूर्ण;

काष्ठा ingenic_soc_info अणु
	क्रमागत ingenic_usb_phy_version version;

	व्योम (*usb_phy_init)(काष्ठा usb_phy *phy);
पूर्ण;

काष्ठा jz4770_phy अणु
	स्थिर काष्ठा ingenic_soc_info *soc_info;

	काष्ठा usb_phy phy;
	काष्ठा usb_otg otg;
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा regulator *vcc_supply;
पूर्ण;

अटल अंतरभूत काष्ठा jz4770_phy *otg_to_jz4770_phy(काष्ठा usb_otg *otg)
अणु
	वापस container_of(otg, काष्ठा jz4770_phy, otg);
पूर्ण

अटल अंतरभूत काष्ठा jz4770_phy *phy_to_jz4770_phy(काष्ठा usb_phy *phy)
अणु
	वापस container_of(phy, काष्ठा jz4770_phy, phy);
पूर्ण

अटल पूर्णांक ingenic_usb_phy_set_peripheral(काष्ठा usb_otg *otg,
				     काष्ठा usb_gadget *gadget)
अणु
	काष्ठा jz4770_phy *priv = otg_to_jz4770_phy(otg);
	u32 reg;

	अगर (priv->soc_info->version >= ID_X1000) अणु
		reg = पढ़ोl(priv->base + REG_USBPCR1_OFFSET);
		reg |= USBPCR1_BVLD_REG;
		ग_लिखोl(reg, priv->base + REG_USBPCR1_OFFSET);
	पूर्ण

	reg = पढ़ोl(priv->base + REG_USBPCR_OFFSET);
	reg &= ~USBPCR_USB_MODE;
	reg |= USBPCR_VBUSVLDEXT | USBPCR_VBUSVLDEXTSEL | USBPCR_OTG_DISABLE;
	ग_लिखोl(reg, priv->base + REG_USBPCR_OFFSET);

	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_usb_phy_set_host(काष्ठा usb_otg *otg, काष्ठा usb_bus *host)
अणु
	काष्ठा jz4770_phy *priv = otg_to_jz4770_phy(otg);
	u32 reg;

	reg = पढ़ोl(priv->base + REG_USBPCR_OFFSET);
	reg &= ~(USBPCR_VBUSVLDEXT | USBPCR_VBUSVLDEXTSEL | USBPCR_OTG_DISABLE);
	reg |= USBPCR_USB_MODE;
	ग_लिखोl(reg, priv->base + REG_USBPCR_OFFSET);

	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_usb_phy_init(काष्ठा usb_phy *phy)
अणु
	काष्ठा jz4770_phy *priv = phy_to_jz4770_phy(phy);
	पूर्णांक err;
	u32 reg;

	err = regulator_enable(priv->vcc_supply);
	अगर (err) अणु
		dev_err(priv->dev, "Unable to enable VCC: %d\n", err);
		वापस err;
	पूर्ण

	err = clk_prepare_enable(priv->clk);
	अगर (err) अणु
		dev_err(priv->dev, "Unable to start clock: %d\n", err);
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

अटल व्योम ingenic_usb_phy_shutकरोwn(काष्ठा usb_phy *phy)
अणु
	काष्ठा jz4770_phy *priv = phy_to_jz4770_phy(phy);

	clk_disable_unprepare(priv->clk);
	regulator_disable(priv->vcc_supply);
पूर्ण

अटल व्योम ingenic_usb_phy_हटाओ(व्योम *phy)
अणु
	usb_हटाओ_phy(phy);
पूर्ण

अटल व्योम jz4770_usb_phy_init(काष्ठा usb_phy *phy)
अणु
	काष्ठा jz4770_phy *priv = phy_to_jz4770_phy(phy);
	u32 reg;

	reg = USBPCR_AVLD_REG | USBPCR_COMMONONN | USBPCR_IDPULLUP_ALWAYS |
		USBPCR_COMPDISTUNE_DFT | USBPCR_OTGTUNE_DFT | USBPCR_SQRXTUNE_DFT |
		USBPCR_TXFSLSTUNE_DFT | USBPCR_TXRISETUNE_DFT | USBPCR_TXVREFTUNE_DFT |
		USBPCR_POR;
	ग_लिखोl(reg, priv->base + REG_USBPCR_OFFSET);
पूर्ण

अटल व्योम jz4780_usb_phy_init(काष्ठा usb_phy *phy)
अणु
	काष्ठा jz4770_phy *priv = phy_to_jz4770_phy(phy);
	u32 reg;

	reg = पढ़ोl(priv->base + REG_USBPCR1_OFFSET) | USBPCR1_USB_SEL |
		USBPCR1_WORD_IF_16BIT;
	ग_लिखोl(reg, priv->base + REG_USBPCR1_OFFSET);

	reg = USBPCR_TXPREEMPHTUNE | USBPCR_COMMONONN | USBPCR_POR;
	ग_लिखोl(reg, priv->base + REG_USBPCR_OFFSET);
पूर्ण

अटल व्योम x1000_usb_phy_init(काष्ठा usb_phy *phy)
अणु
	काष्ठा jz4770_phy *priv = phy_to_jz4770_phy(phy);
	u32 reg;

	reg = पढ़ोl(priv->base + REG_USBPCR1_OFFSET) | USBPCR1_WORD_IF_16BIT;
	ग_लिखोl(reg, priv->base + REG_USBPCR1_OFFSET);

	reg = USBPCR_SQRXTUNE_DCR_20PCT | USBPCR_TXPREEMPHTUNE |
		USBPCR_TXHSXVTUNE_DCR_15MV | USBPCR_TXVREFTUNE_INC_25PPT |
		USBPCR_COMMONONN | USBPCR_POR;
	ग_लिखोl(reg, priv->base + REG_USBPCR_OFFSET);
पूर्ण

अटल व्योम x1830_usb_phy_init(काष्ठा usb_phy *phy)
अणु
	काष्ठा jz4770_phy *priv = phy_to_jz4770_phy(phy);
	u32 reg;

	/* rdt */
	ग_लिखोl(USBRDT_VBFIL_EN | USBRDT_UTMI_RST, priv->base + REG_USBRDT_OFFSET);

	reg = पढ़ोl(priv->base + REG_USBPCR1_OFFSET) | USBPCR1_WORD_IF_16BIT |
		USBPCR1_DMPD | USBPCR1_DPPD;
	ग_लिखोl(reg, priv->base + REG_USBPCR1_OFFSET);

	reg = USBPCR_IDPULLUP_OTG | USBPCR_VBUSVLDEXT |	USBPCR_TXPREEMPHTUNE |
		USBPCR_COMMONONN | USBPCR_POR;
	ग_लिखोl(reg, priv->base + REG_USBPCR_OFFSET);
पूर्ण

अटल स्थिर काष्ठा ingenic_soc_info jz4770_soc_info = अणु
	.version = ID_JZ4770,

	.usb_phy_init = jz4770_usb_phy_init,
पूर्ण;

अटल स्थिर काष्ठा ingenic_soc_info jz4780_soc_info = अणु
	.version = ID_JZ4780,

	.usb_phy_init = jz4780_usb_phy_init,
पूर्ण;

अटल स्थिर काष्ठा ingenic_soc_info x1000_soc_info = अणु
	.version = ID_X1000,

	.usb_phy_init = x1000_usb_phy_init,
पूर्ण;

अटल स्थिर काष्ठा ingenic_soc_info x1830_soc_info = अणु
	.version = ID_X1830,

	.usb_phy_init = x1830_usb_phy_init,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ingenic_usb_phy_of_matches[] = अणु
	अणु .compatible = "ingenic,jz4770-phy", .data = &jz4770_soc_info पूर्ण,
	अणु .compatible = "ingenic,jz4780-phy", .data = &jz4780_soc_info पूर्ण,
	अणु .compatible = "ingenic,x1000-phy", .data = &x1000_soc_info पूर्ण,
	अणु .compatible = "ingenic,x1830-phy", .data = &x1830_soc_info पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ingenic_usb_phy_of_matches);

अटल पूर्णांक jz4770_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा jz4770_phy *priv;
	पूर्णांक err;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->soc_info = device_get_match_data(&pdev->dev);
	अगर (!priv->soc_info) अणु
		dev_err(&pdev->dev, "Error: No device match found\n");
		वापस -ENODEV;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);
	priv->dev = dev;
	priv->phy.dev = dev;
	priv->phy.otg = &priv->otg;
	priv->phy.label = "ingenic-usb-phy";
	priv->phy.init = ingenic_usb_phy_init;
	priv->phy.shutकरोwn = ingenic_usb_phy_shutकरोwn;

	priv->otg.state = OTG_STATE_UNDEFINED;
	priv->otg.usb_phy = &priv->phy;
	priv->otg.set_host = ingenic_usb_phy_set_host;
	priv->otg.set_peripheral = ingenic_usb_phy_set_peripheral;

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

	err = usb_add_phy(&priv->phy, USB_PHY_TYPE_USB2);
	अगर (err) अणु
		अगर (err != -EPROBE_DEFER)
			dev_err(dev, "Unable to register PHY\n");
		वापस err;
	पूर्ण

	वापस devm_add_action_or_reset(dev, ingenic_usb_phy_हटाओ, &priv->phy);
पूर्ण

अटल काष्ठा platक्रमm_driver ingenic_phy_driver = अणु
	.probe		= jz4770_phy_probe,
	.driver		= अणु
		.name	= "jz4770-phy",
		.of_match_table = ingenic_usb_phy_of_matches,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ingenic_phy_driver);

MODULE_AUTHOR("ोउॉओौओ (Zhou Yanjie) <zhouyanjie@wanyeetech.com>");
MODULE_AUTHOR("ौञ़छौ/ (Qi Pengzhen) <aric.pzqi@ingenic.com>");
MODULE_AUTHOR("Paul Cercueil <paul@crapouillou.net>");
MODULE_DESCRIPTION("Ingenic SoCs USB PHY driver");
MODULE_LICENSE("GPL");
