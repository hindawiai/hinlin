<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (c) 2017 NXP. */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा PHY_CTRL0			0x0
#घोषणा PHY_CTRL0_REF_SSP_EN		BIT(2)
#घोषणा PHY_CTRL0_FSEL_MASK		GENMASK(10, 5)
#घोषणा PHY_CTRL0_FSEL_24M		0x2a

#घोषणा PHY_CTRL1			0x4
#घोषणा PHY_CTRL1_RESET			BIT(0)
#घोषणा PHY_CTRL1_COMMONONN		BIT(1)
#घोषणा PHY_CTRL1_ATERESET		BIT(3)
#घोषणा PHY_CTRL1_VDATSRCENB0		BIT(19)
#घोषणा PHY_CTRL1_VDATDETENB0		BIT(20)

#घोषणा PHY_CTRL2			0x8
#घोषणा PHY_CTRL2_TXENABLEN0		BIT(8)
#घोषणा PHY_CTRL2_OTG_DISABLE		BIT(9)

#घोषणा PHY_CTRL6			0x18
#घोषणा PHY_CTRL6_ALT_CLK_EN		BIT(1)
#घोषणा PHY_CTRL6_ALT_CLK_SEL		BIT(0)

काष्ठा imx8mq_usb_phy अणु
	काष्ठा phy *phy;
	काष्ठा clk *clk;
	व्योम __iomem *base;
	काष्ठा regulator *vbus;
पूर्ण;

अटल पूर्णांक imx8mq_usb_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा imx8mq_usb_phy *imx_phy = phy_get_drvdata(phy);
	u32 value;

	value = पढ़ोl(imx_phy->base + PHY_CTRL1);
	value &= ~(PHY_CTRL1_VDATSRCENB0 | PHY_CTRL1_VDATDETENB0 |
		   PHY_CTRL1_COMMONONN);
	value |= PHY_CTRL1_RESET | PHY_CTRL1_ATERESET;
	ग_लिखोl(value, imx_phy->base + PHY_CTRL1);

	value = पढ़ोl(imx_phy->base + PHY_CTRL0);
	value |= PHY_CTRL0_REF_SSP_EN;
	ग_लिखोl(value, imx_phy->base + PHY_CTRL0);

	value = पढ़ोl(imx_phy->base + PHY_CTRL2);
	value |= PHY_CTRL2_TXENABLEN0;
	ग_लिखोl(value, imx_phy->base + PHY_CTRL2);

	value = पढ़ोl(imx_phy->base + PHY_CTRL1);
	value &= ~(PHY_CTRL1_RESET | PHY_CTRL1_ATERESET);
	ग_लिखोl(value, imx_phy->base + PHY_CTRL1);

	वापस 0;
पूर्ण

अटल पूर्णांक imx8mp_usb_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा imx8mq_usb_phy *imx_phy = phy_get_drvdata(phy);
	u32 value;

	/* USB3.0 PHY संकेत fsel क्रम 24M ref */
	value = पढ़ोl(imx_phy->base + PHY_CTRL0);
	value &= ~PHY_CTRL0_FSEL_MASK;
	value |= FIELD_PREP(PHY_CTRL0_FSEL_MASK, PHY_CTRL0_FSEL_24M);
	ग_लिखोl(value, imx_phy->base + PHY_CTRL0);

	/* Disable alt_clk_en and use पूर्णांकernal MPLL घड़ीs */
	value = पढ़ोl(imx_phy->base + PHY_CTRL6);
	value &= ~(PHY_CTRL6_ALT_CLK_SEL | PHY_CTRL6_ALT_CLK_EN);
	ग_लिखोl(value, imx_phy->base + PHY_CTRL6);

	value = पढ़ोl(imx_phy->base + PHY_CTRL1);
	value &= ~(PHY_CTRL1_VDATSRCENB0 | PHY_CTRL1_VDATDETENB0);
	value |= PHY_CTRL1_RESET | PHY_CTRL1_ATERESET;
	ग_लिखोl(value, imx_phy->base + PHY_CTRL1);

	value = पढ़ोl(imx_phy->base + PHY_CTRL0);
	value |= PHY_CTRL0_REF_SSP_EN;
	ग_लिखोl(value, imx_phy->base + PHY_CTRL0);

	value = पढ़ोl(imx_phy->base + PHY_CTRL2);
	value |= PHY_CTRL2_TXENABLEN0 | PHY_CTRL2_OTG_DISABLE;
	ग_लिखोl(value, imx_phy->base + PHY_CTRL2);

	udelay(10);

	value = पढ़ोl(imx_phy->base + PHY_CTRL1);
	value &= ~(PHY_CTRL1_RESET | PHY_CTRL1_ATERESET);
	ग_लिखोl(value, imx_phy->base + PHY_CTRL1);

	वापस 0;
पूर्ण

अटल पूर्णांक imx8mq_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा imx8mq_usb_phy *imx_phy = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = regulator_enable(imx_phy->vbus);
	अगर (ret)
		वापस ret;

	वापस clk_prepare_enable(imx_phy->clk);
पूर्ण

अटल पूर्णांक imx8mq_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा imx8mq_usb_phy *imx_phy = phy_get_drvdata(phy);

	clk_disable_unprepare(imx_phy->clk);
	regulator_disable(imx_phy->vbus);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops imx8mq_usb_phy_ops = अणु
	.init		= imx8mq_usb_phy_init,
	.घातer_on	= imx8mq_phy_घातer_on,
	.घातer_off	= imx8mq_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा phy_ops imx8mp_usb_phy_ops = अणु
	.init		= imx8mp_usb_phy_init,
	.घातer_on	= imx8mq_phy_घातer_on,
	.घातer_off	= imx8mq_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx8mq_usb_phy_of_match[] = अणु
	अणु.compatible = "fsl,imx8mq-usb-phy",
	 .data = &imx8mq_usb_phy_ops,पूर्ण,
	अणु.compatible = "fsl,imx8mp-usb-phy",
	 .data = &imx8mp_usb_phy_ops,पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx8mq_usb_phy_of_match);

अटल पूर्णांक imx8mq_usb_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *phy_provider;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा imx8mq_usb_phy *imx_phy;
	स्थिर काष्ठा phy_ops *phy_ops;

	imx_phy = devm_kzalloc(dev, माप(*imx_phy), GFP_KERNEL);
	अगर (!imx_phy)
		वापस -ENOMEM;

	imx_phy->clk = devm_clk_get(dev, "phy");
	अगर (IS_ERR(imx_phy->clk)) अणु
		dev_err(dev, "failed to get imx8mq usb phy clock\n");
		वापस PTR_ERR(imx_phy->clk);
	पूर्ण

	imx_phy->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(imx_phy->base))
		वापस PTR_ERR(imx_phy->base);

	phy_ops = of_device_get_match_data(dev);
	अगर (!phy_ops)
		वापस -EINVAL;

	imx_phy->phy = devm_phy_create(dev, शून्य, phy_ops);
	अगर (IS_ERR(imx_phy->phy))
		वापस PTR_ERR(imx_phy->phy);

	imx_phy->vbus = devm_regulator_get(dev, "vbus");
	अगर (IS_ERR(imx_phy->vbus))
		वापस PTR_ERR(imx_phy->vbus);

	phy_set_drvdata(imx_phy->phy, imx_phy);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल काष्ठा platक्रमm_driver imx8mq_usb_phy_driver = अणु
	.probe	= imx8mq_usb_phy_probe,
	.driver = अणु
		.name	= "imx8mq-usb-phy",
		.of_match_table	= imx8mq_usb_phy_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(imx8mq_usb_phy_driver);

MODULE_DESCRIPTION("FSL IMX8MQ USB PHY driver");
MODULE_LICENSE("GPL");
