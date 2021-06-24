<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * phy-bcm-kona-usb2.c - Broadcom Kona USB2 Phy Driver
 *
 * Copyright (C) 2013 Linaro Limited
 * Matt Porter <mporter@linaro.org>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा OTGCTL			(0)
#घोषणा OTGCTL_OTGSTAT2		BIT(31)
#घोषणा OTGCTL_OTGSTAT1		BIT(30)
#घोषणा OTGCTL_PRST_N_SW	BIT(11)
#घोषणा OTGCTL_HRESET_N		BIT(10)
#घोषणा OTGCTL_UTMI_LINE_STATE1	BIT(9)
#घोषणा OTGCTL_UTMI_LINE_STATE0	BIT(8)

#घोषणा P1CTL			(8)
#घोषणा P1CTL_SOFT_RESET	BIT(1)
#घोषणा P1CTL_NON_DRIVING	BIT(0)

काष्ठा bcm_kona_usb अणु
	व्योम __iomem *regs;
पूर्ण;

अटल व्योम bcm_kona_usb_phy_घातer(काष्ठा bcm_kona_usb *phy, पूर्णांक on)
अणु
	u32 val;

	val = पढ़ोl(phy->regs + OTGCTL);
	अगर (on) अणु
		/* Configure and घातer PHY */
		val &= ~(OTGCTL_OTGSTAT2 | OTGCTL_OTGSTAT1 |
			 OTGCTL_UTMI_LINE_STATE1 | OTGCTL_UTMI_LINE_STATE0);
		val |= OTGCTL_PRST_N_SW | OTGCTL_HRESET_N;
	पूर्ण अन्यथा अणु
		val &= ~(OTGCTL_PRST_N_SW | OTGCTL_HRESET_N);
	पूर्ण
	ग_लिखोl(val, phy->regs + OTGCTL);
पूर्ण

अटल पूर्णांक bcm_kona_usb_phy_init(काष्ठा phy *gphy)
अणु
	काष्ठा bcm_kona_usb *phy = phy_get_drvdata(gphy);
	u32 val;

	/* Soft reset PHY */
	val = पढ़ोl(phy->regs + P1CTL);
	val &= ~P1CTL_NON_DRIVING;
	val |= P1CTL_SOFT_RESET;
	ग_लिखोl(val, phy->regs + P1CTL);
	ग_लिखोl(val & ~P1CTL_SOFT_RESET, phy->regs + P1CTL);
	/* Reset needs to be निश्चितed क्रम 2ms */
	mdelay(2);
	ग_लिखोl(val | P1CTL_SOFT_RESET, phy->regs + P1CTL);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_kona_usb_phy_घातer_on(काष्ठा phy *gphy)
अणु
	काष्ठा bcm_kona_usb *phy = phy_get_drvdata(gphy);

	bcm_kona_usb_phy_घातer(phy, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_kona_usb_phy_घातer_off(काष्ठा phy *gphy)
अणु
	काष्ठा bcm_kona_usb *phy = phy_get_drvdata(gphy);

	bcm_kona_usb_phy_घातer(phy, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops ops = अणु
	.init		= bcm_kona_usb_phy_init,
	.घातer_on	= bcm_kona_usb_phy_घातer_on,
	.घातer_off	= bcm_kona_usb_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक bcm_kona_usb2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा bcm_kona_usb *phy;
	काष्ठा phy *gphy;
	काष्ठा phy_provider *phy_provider;

	phy = devm_kzalloc(dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस -ENOMEM;

	phy->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(phy->regs))
		वापस PTR_ERR(phy->regs);

	platक्रमm_set_drvdata(pdev, phy);

	gphy = devm_phy_create(dev, शून्य, &ops);
	अगर (IS_ERR(gphy))
		वापस PTR_ERR(gphy);

	/* The Kona PHY supports an 8-bit wide UTMI पूर्णांकerface */
	phy_set_bus_width(gphy, 8);

	phy_set_drvdata(gphy, phy);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev,
			of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm_kona_usb2_dt_ids[] = अणु
	अणु .compatible = "brcm,kona-usb2-phy" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, bcm_kona_usb2_dt_ids);

अटल काष्ठा platक्रमm_driver bcm_kona_usb2_driver = अणु
	.probe		= bcm_kona_usb2_probe,
	.driver		= अणु
		.name	= "bcm-kona-usb2",
		.of_match_table = bcm_kona_usb2_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(bcm_kona_usb2_driver);

MODULE_ALIAS("platform:bcm-kona-usb2");
MODULE_AUTHOR("Matt Porter <mporter@linaro.org>");
MODULE_DESCRIPTION("BCM Kona USB 2.0 PHY driver");
MODULE_LICENSE("GPL v2");
