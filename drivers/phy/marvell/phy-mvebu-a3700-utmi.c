<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Marvell
 *
 * Authors:
 *   Igal Liberman <igall@marvell.com>
 *   Miquथउl Raynal <miquel.raynal@bootlin.com>
 *
 * Marvell A3700 UTMI PHY driver
 */

#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

/* Armada 3700 UTMI PHY रेजिस्टरs */
#घोषणा USB2_PHY_PLL_CTRL_REG0			0x0
#घोषणा   PLL_REF_DIV_OFF			0
#घोषणा   PLL_REF_DIV_MASK			GENMASK(6, 0)
#घोषणा   PLL_REF_DIV_5				5
#घोषणा   PLL_FB_DIV_OFF			16
#घोषणा   PLL_FB_DIV_MASK			GENMASK(24, 16)
#घोषणा   PLL_FB_DIV_96				96
#घोषणा   PLL_SEL_LPFR_OFF			28
#घोषणा   PLL_SEL_LPFR_MASK			GENMASK(29, 28)
#घोषणा   PLL_READY				BIT(31)
#घोषणा USB2_PHY_CAL_CTRL			0x8
#घोषणा   PHY_PLLCAL_DONE			BIT(31)
#घोषणा   PHY_IMPCAL_DONE			BIT(23)
#घोषणा USB2_RX_CHAN_CTRL1			0x18
#घोषणा   USB2PHY_SQCAL_DONE			BIT(31)
#घोषणा USB2_PHY_OTG_CTRL			0x34
#घोषणा   PHY_PU_OTG				BIT(4)
#घोषणा USB2_PHY_CHRGR_DETECT			0x38
#घोषणा   PHY_CDP_EN				BIT(2)
#घोषणा   PHY_DCP_EN				BIT(3)
#घोषणा   PHY_PD_EN				BIT(4)
#घोषणा   PHY_PU_CHRG_DTC			BIT(5)
#घोषणा   PHY_CDP_DM_AUTO			BIT(7)
#घोषणा   PHY_ENSWITCH_DP			BIT(12)
#घोषणा   PHY_ENSWITCH_DM			BIT(13)

/* Armada 3700 USB miscellaneous रेजिस्टरs */
#घोषणा USB2_PHY_CTRL(usb32)			(usb32 ? 0x20 : 0x4)
#घोषणा   RB_USB2PHY_PU				BIT(0)
#घोषणा   USB2_DP_PULLDN_DEV_MODE		BIT(5)
#घोषणा   USB2_DM_PULLDN_DEV_MODE		BIT(6)
#घोषणा   RB_USB2PHY_SUSPM(usb32)		(usb32 ? BIT(14) : BIT(7))

#घोषणा PLL_LOCK_DELAY_US			10000
#घोषणा PLL_LOCK_TIMEOUT_US			1000000

/**
 * काष्ठा mvebu_a3700_uपंचांगi_caps - PHY capabilities
 *
 * @usb32: Flag indicating which PHY is in use (impacts the रेजिस्टर map):
 *           - The UTMI PHY wired to the USB3/USB2 controller (otg)
 *           - The UTMI PHY wired to the USB2 controller (host only)
 * @ops: PHY operations
 */
काष्ठा mvebu_a3700_uपंचांगi_caps अणु
	पूर्णांक usb32;
	स्थिर काष्ठा phy_ops *ops;
पूर्ण;

/**
 * काष्ठा mvebu_a3700_uपंचांगi - PHY driver data
 *
 * @regs: PHY रेजिस्टरs
 * @usb_misc: Regmap with USB miscellaneous रेजिस्टरs including PHY ones
 * @caps: PHY capabilities
 * @phy: PHY handle
 */
काष्ठा mvebu_a3700_uपंचांगi अणु
	व्योम __iomem *regs;
	काष्ठा regmap *usb_misc;
	स्थिर काष्ठा mvebu_a3700_uपंचांगi_caps *caps;
	काष्ठा phy *phy;
पूर्ण;

अटल पूर्णांक mvebu_a3700_uपंचांगi_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा mvebu_a3700_uपंचांगi *uपंचांगi = phy_get_drvdata(phy);
	काष्ठा device *dev = &phy->dev;
	पूर्णांक usb32 = uपंचांगi->caps->usb32;
	पूर्णांक ret = 0;
	u32 reg;

	/*
	 * Setup PLL. 40MHz घड़ी used to be the शेष, being 25MHz now.
	 * See "PLL Settings for Typical REFCLK" table.
	 */
	reg = पढ़ोl(uपंचांगi->regs + USB2_PHY_PLL_CTRL_REG0);
	reg &= ~(PLL_REF_DIV_MASK | PLL_FB_DIV_MASK | PLL_SEL_LPFR_MASK);
	reg |= (PLL_REF_DIV_5 << PLL_REF_DIV_OFF) |
	       (PLL_FB_DIV_96 << PLL_FB_DIV_OFF);
	ग_लिखोl(reg, uपंचांगi->regs + USB2_PHY_PLL_CTRL_REG0);

	/* Enable PHY pull up and disable USB2 suspend */
	regmap_update_bits(uपंचांगi->usb_misc, USB2_PHY_CTRL(usb32),
			   RB_USB2PHY_SUSPM(usb32) | RB_USB2PHY_PU,
			   RB_USB2PHY_SUSPM(usb32) | RB_USB2PHY_PU);

	अगर (usb32) अणु
		/* Power up OTG module */
		reg = पढ़ोl(uपंचांगi->regs + USB2_PHY_OTG_CTRL);
		reg |= PHY_PU_OTG;
		ग_लिखोl(reg, uपंचांगi->regs + USB2_PHY_OTG_CTRL);

		/* Disable PHY अक्षरger detection */
		reg = पढ़ोl(uपंचांगi->regs + USB2_PHY_CHRGR_DETECT);
		reg &= ~(PHY_CDP_EN | PHY_DCP_EN | PHY_PD_EN | PHY_PU_CHRG_DTC |
			 PHY_CDP_DM_AUTO | PHY_ENSWITCH_DP | PHY_ENSWITCH_DM);
		ग_लिखोl(reg, uपंचांगi->regs + USB2_PHY_CHRGR_DETECT);

		/* Disable PHY DP/DM pull-करोwn (used क्रम device mode) */
		regmap_update_bits(uपंचांगi->usb_misc, USB2_PHY_CTRL(usb32),
				   USB2_DP_PULLDN_DEV_MODE |
				   USB2_DM_PULLDN_DEV_MODE, 0);
	पूर्ण

	/* Wait क्रम PLL calibration */
	ret = पढ़ोl_poll_समयout(uपंचांगi->regs + USB2_PHY_CAL_CTRL, reg,
				 reg & PHY_PLLCAL_DONE,
				 PLL_LOCK_DELAY_US, PLL_LOCK_TIMEOUT_US);
	अगर (ret) अणु
		dev_err(dev, "Failed to end USB2 PLL calibration\n");
		वापस ret;
	पूर्ण

	/* Wait क्रम impedance calibration */
	ret = पढ़ोl_poll_समयout(uपंचांगi->regs + USB2_PHY_CAL_CTRL, reg,
				 reg & PHY_IMPCAL_DONE,
				 PLL_LOCK_DELAY_US, PLL_LOCK_TIMEOUT_US);
	अगर (ret) अणु
		dev_err(dev, "Failed to end USB2 impedance calibration\n");
		वापस ret;
	पूर्ण

	/* Wait क्रम squelch calibration */
	ret = पढ़ोl_poll_समयout(uपंचांगi->regs + USB2_RX_CHAN_CTRL1, reg,
				 reg & USB2PHY_SQCAL_DONE,
				 PLL_LOCK_DELAY_US, PLL_LOCK_TIMEOUT_US);
	अगर (ret) अणु
		dev_err(dev, "Failed to end USB2 unknown calibration\n");
		वापस ret;
	पूर्ण

	/* Wait क्रम PLL to be locked */
	ret = पढ़ोl_poll_समयout(uपंचांगi->regs + USB2_PHY_PLL_CTRL_REG0, reg,
				 reg & PLL_READY,
				 PLL_LOCK_DELAY_US, PLL_LOCK_TIMEOUT_US);
	अगर (ret)
		dev_err(dev, "Failed to lock USB2 PLL\n");

	वापस ret;
पूर्ण

अटल पूर्णांक mvebu_a3700_uपंचांगi_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा mvebu_a3700_uपंचांगi *uपंचांगi = phy_get_drvdata(phy);
	पूर्णांक usb32 = uपंचांगi->caps->usb32;
	u32 reg;

	/* Disable PHY pull-up and enable USB2 suspend */
	reg = पढ़ोl(uपंचांगi->regs + USB2_PHY_CTRL(usb32));
	reg &= ~(RB_USB2PHY_PU | RB_USB2PHY_SUSPM(usb32));
	ग_लिखोl(reg, uपंचांगi->regs + USB2_PHY_CTRL(usb32));

	/* Power करोwn OTG module */
	अगर (usb32) अणु
		reg = पढ़ोl(uपंचांगi->regs + USB2_PHY_OTG_CTRL);
		reg &= ~PHY_PU_OTG;
		ग_लिखोl(reg, uपंचांगi->regs + USB2_PHY_OTG_CTRL);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops mvebu_a3700_uपंचांगi_phy_ops = अणु
	.घातer_on = mvebu_a3700_uपंचांगi_phy_घातer_on,
	.घातer_off = mvebu_a3700_uपंचांगi_phy_घातer_off,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा mvebu_a3700_uपंचांगi_caps mvebu_a3700_uपंचांगi_otg_phy_caps = अणु
	.usb32 = true,
	.ops = &mvebu_a3700_uपंचांगi_phy_ops,
पूर्ण;

अटल स्थिर काष्ठा mvebu_a3700_uपंचांगi_caps mvebu_a3700_uपंचांगi_host_phy_caps = अणु
	.usb32 = false,
	.ops = &mvebu_a3700_uपंचांगi_phy_ops,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mvebu_a3700_uपंचांगi_of_match[] = अणु
	अणु
		.compatible = "marvell,a3700-utmi-otg-phy",
		.data = &mvebu_a3700_uपंचांगi_otg_phy_caps,
	पूर्ण,
	अणु
		.compatible = "marvell,a3700-utmi-host-phy",
		.data = &mvebu_a3700_uपंचांगi_host_phy_caps,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mvebu_a3700_uपंचांगi_of_match);

अटल पूर्णांक mvebu_a3700_uपंचांगi_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mvebu_a3700_uपंचांगi *uपंचांगi;
	काष्ठा phy_provider *provider;

	uपंचांगi = devm_kzalloc(dev, माप(*uपंचांगi), GFP_KERNEL);
	अगर (!uपंचांगi)
		वापस -ENOMEM;

	/* Get UTMI memory region */
	uपंचांगi->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(uपंचांगi->regs))
		वापस PTR_ERR(uपंचांगi->regs);

	/* Get miscellaneous Host/PHY region */
	uपंचांगi->usb_misc = syscon_regmap_lookup_by_phandle(dev->of_node,
							 "marvell,usb-misc-reg");
	अगर (IS_ERR(uपंचांगi->usb_misc)) अणु
		dev_err(dev,
			"Missing USB misc purpose system controller\n");
		वापस PTR_ERR(uपंचांगi->usb_misc);
	पूर्ण

	/* Retrieve PHY capabilities */
	uपंचांगi->caps = of_device_get_match_data(dev);

	/* Instantiate the PHY */
	uपंचांगi->phy = devm_phy_create(dev, शून्य, uपंचांगi->caps->ops);
	अगर (IS_ERR(uपंचांगi->phy)) अणु
		dev_err(dev, "Failed to create the UTMI PHY\n");
		वापस PTR_ERR(uपंचांगi->phy);
	पूर्ण

	phy_set_drvdata(uपंचांगi->phy, uपंचांगi);

	/* Ensure the PHY is घातered off */
	uपंचांगi->caps->ops->घातer_off(uपंचांगi->phy);

	provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(provider);
पूर्ण

अटल काष्ठा platक्रमm_driver mvebu_a3700_uपंचांगi_driver = अणु
	.probe	= mvebu_a3700_uपंचांगi_phy_probe,
	.driver	= अणु
		.name		= "mvebu-a3700-utmi-phy",
		.of_match_table	= mvebu_a3700_uपंचांगi_of_match,
	 पूर्ण,
पूर्ण;
module_platक्रमm_driver(mvebu_a3700_uपंचांगi_driver);

MODULE_AUTHOR("Igal Liberman <igall@marvell.com>");
MODULE_AUTHOR("Miquel Raynal <miquel.raynal@bootlin.com>");
MODULE_DESCRIPTION("Marvell EBU A3700 UTMI PHY driver");
MODULE_LICENSE("GPL v2");
