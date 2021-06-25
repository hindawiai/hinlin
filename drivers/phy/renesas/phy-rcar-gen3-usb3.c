<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas R-Car Gen3 क्रम USB3.0 PHY driver
 *
 * Copyright (C) 2017 Renesas Electronics Corporation
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा USB30_CLKSET0		0x034
#घोषणा USB30_CLKSET1		0x036
#घोषणा USB30_SSC_SET		0x038
#घोषणा USB30_PHY_ENABLE	0x060
#घोषणा USB30_VBUS_EN		0x064

/* USB30_CLKSET0 */
#घोषणा CLKSET0_PRIVATE			0x05c0
#घोषणा CLKSET0_USB30_FSEL_USB_EXTAL	0x0002

/* USB30_CLKSET1 */
#घोषणा CLKSET1_USB30_PLL_MULTI_SHIFT		6
#घोषणा CLKSET1_USB30_PLL_MULTI_USB_EXTAL	(0x64 << \
						 CLKSET1_USB30_PLL_MULTI_SHIFT)
#घोषणा CLKSET1_PHYRESET	BIT(4)	/* 1: reset */
#घोषणा CLKSET1_REF_CLKDIV	BIT(3)	/* 1: USB_EXTAL */
#घोषणा CLKSET1_PRIVATE_2_1	BIT(1)	/* Write B'01 */
#घोषणा CLKSET1_REF_CLK_SEL	BIT(0)	/* 1: USB3S0_CLK_P */

/* USB30_SSC_SET */
#घोषणा SSC_SET_SSC_EN		BIT(12)
#घोषणा SSC_SET_RANGE_SHIFT	9
#घोषणा SSC_SET_RANGE_4980	(0x0 << SSC_SET_RANGE_SHIFT)
#घोषणा SSC_SET_RANGE_4492	(0x1 << SSC_SET_RANGE_SHIFT)
#घोषणा SSC_SET_RANGE_4003	(0x2 << SSC_SET_RANGE_SHIFT)

/* USB30_PHY_ENABLE */
#घोषणा PHY_ENABLE_RESET_EN	BIT(4)

/* USB30_VBUS_EN */
#घोषणा VBUS_EN_VBUS_EN		BIT(1)

काष्ठा rcar_gen3_usb3 अणु
	व्योम __iomem *base;
	काष्ठा phy *phy;
	u32 ssc_range;
	bool usb3s_clk;
	bool usb_extal;
पूर्ण;

अटल व्योम ग_लिखो_clkset1_क्रम_usb_extal(काष्ठा rcar_gen3_usb3 *r, bool reset)
अणु
	u16 val = CLKSET1_USB30_PLL_MULTI_USB_EXTAL |
		  CLKSET1_REF_CLKDIV | CLKSET1_PRIVATE_2_1;

	अगर (reset)
		val |= CLKSET1_PHYRESET;

	ग_लिखोw(val, r->base + USB30_CLKSET1);
पूर्ण

अटल व्योम rcar_gen3_phy_usb3_enable_ssc(काष्ठा rcar_gen3_usb3 *r)
अणु
	u16 val = SSC_SET_SSC_EN;

	चयन (r->ssc_range) अणु
	हाल 4980:
		val |= SSC_SET_RANGE_4980;
		अवरोध;
	हाल 4492:
		val |= SSC_SET_RANGE_4492;
		अवरोध;
	हाल 4003:
		val |= SSC_SET_RANGE_4003;
		अवरोध;
	शेष:
		dev_err(&r->phy->dev, "%s: unsupported range (%x)\n", __func__,
			r->ssc_range);
		वापस;
	पूर्ण

	ग_लिखोw(val, r->base + USB30_SSC_SET);
पूर्ण

अटल व्योम rcar_gen3_phy_usb3_select_usb_extal(काष्ठा rcar_gen3_usb3 *r)
अणु
	ग_लिखो_clkset1_क्रम_usb_extal(r, false);
	अगर (r->ssc_range)
		rcar_gen3_phy_usb3_enable_ssc(r);
	ग_लिखोw(CLKSET0_PRIVATE | CLKSET0_USB30_FSEL_USB_EXTAL,
	       r->base + USB30_CLKSET0);
	ग_लिखोw(PHY_ENABLE_RESET_EN, r->base + USB30_PHY_ENABLE);
	ग_लिखो_clkset1_क्रम_usb_extal(r, true);
	usleep_range(10, 20);
	ग_लिखो_clkset1_क्रम_usb_extal(r, false);
पूर्ण

अटल पूर्णांक rcar_gen3_phy_usb3_init(काष्ठा phy *p)
अणु
	काष्ठा rcar_gen3_usb3 *r = phy_get_drvdata(p);

	dev_vdbg(&r->phy->dev, "%s: enter (%d, %d, %d)\n", __func__,
		 r->usb3s_clk, r->usb_extal, r->ssc_range);

	अगर (!r->usb3s_clk && r->usb_extal)
		rcar_gen3_phy_usb3_select_usb_extal(r);

	/* Enables VBUS detection anyway */
	ग_लिखोw(VBUS_EN_VBUS_EN, r->base + USB30_VBUS_EN);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops rcar_gen3_phy_usb3_ops = अणु
	.init		= rcar_gen3_phy_usb3_init,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rcar_gen3_phy_usb3_match_table[] = अणु
	अणु .compatible = "renesas,rcar-gen3-usb3-phy" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rcar_gen3_phy_usb3_match_table);

अटल पूर्णांक rcar_gen3_phy_usb3_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rcar_gen3_usb3 *r;
	काष्ठा phy_provider *provider;
	पूर्णांक ret = 0;
	काष्ठा clk *clk;

	अगर (!dev->of_node) अणु
		dev_err(dev, "This driver needs device tree\n");
		वापस -EINVAL;
	पूर्ण

	r = devm_kzalloc(dev, माप(*r), GFP_KERNEL);
	अगर (!r)
		वापस -ENOMEM;

	r->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(r->base))
		वापस PTR_ERR(r->base);

	clk = devm_clk_get(dev, "usb3s_clk");
	अगर (!IS_ERR(clk) && !clk_prepare_enable(clk)) अणु
		r->usb3s_clk = !!clk_get_rate(clk);
		clk_disable_unprepare(clk);
	पूर्ण
	clk = devm_clk_get(dev, "usb_extal");
	अगर (!IS_ERR(clk) && !clk_prepare_enable(clk)) अणु
		r->usb_extal = !!clk_get_rate(clk);
		clk_disable_unprepare(clk);
	पूर्ण

	अगर (!r->usb3s_clk && !r->usb_extal) अणु
		dev_err(dev, "This driver needs usb3s_clk and/or usb_extal\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	/*
	 * devm_phy_create() will call pm_runसमय_enable(&phy->dev);
	 * And then, phy-core will manage runसमय pm क्रम this device.
	 */
	pm_runसमय_enable(dev);

	r->phy = devm_phy_create(dev, शून्य, &rcar_gen3_phy_usb3_ops);
	अगर (IS_ERR(r->phy)) अणु
		dev_err(dev, "Failed to create USB3 PHY\n");
		ret = PTR_ERR(r->phy);
		जाओ error;
	पूर्ण

	of_property_पढ़ो_u32(dev->of_node, "renesas,ssc-range", &r->ssc_range);

	platक्रमm_set_drvdata(pdev, r);
	phy_set_drvdata(r->phy, r);

	provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(provider)) अणु
		dev_err(dev, "Failed to register PHY provider\n");
		ret = PTR_ERR(provider);
		जाओ error;
	पूर्ण

	वापस 0;

error:
	pm_runसमय_disable(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक rcar_gen3_phy_usb3_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण;

अटल काष्ठा platक्रमm_driver rcar_gen3_phy_usb3_driver = अणु
	.driver = अणु
		.name		= "phy_rcar_gen3_usb3",
		.of_match_table	= rcar_gen3_phy_usb3_match_table,
	पूर्ण,
	.probe	= rcar_gen3_phy_usb3_probe,
	.हटाओ = rcar_gen3_phy_usb3_हटाओ,
पूर्ण;
module_platक्रमm_driver(rcar_gen3_phy_usb3_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Renesas R-Car Gen3 USB 3.0 PHY");
MODULE_AUTHOR("Yoshihiro Shimoda <yoshihiro.shimoda.uh@renesas.com>");
