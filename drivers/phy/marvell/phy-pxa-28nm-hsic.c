<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Linaro, Ltd.
 * Rob Herring <robh@kernel.org>
 *
 * Based on venकरोr driver:
 * Copyright (C) 2013 Marvell Inc.
 * Author: Chao Xie <xiechao.mail@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>

#घोषणा PHY_28NM_HSIC_CTRL			0x08
#घोषणा PHY_28NM_HSIC_IMPCAL_CAL		0x18
#घोषणा PHY_28NM_HSIC_PLL_CTRL01		0x1c
#घोषणा PHY_28NM_HSIC_PLL_CTRL2			0x20
#घोषणा PHY_28NM_HSIC_INT			0x28

#घोषणा PHY_28NM_HSIC_PLL_SELLPFR_SHIFT		26
#घोषणा PHY_28NM_HSIC_PLL_FBDIV_SHIFT		0
#घोषणा PHY_28NM_HSIC_PLL_REFDIV_SHIFT		9

#घोषणा PHY_28NM_HSIC_S2H_PU_PLL		BIT(10)
#घोषणा PHY_28NM_HSIC_H2S_PLL_LOCK		BIT(15)
#घोषणा PHY_28NM_HSIC_S2H_HSIC_EN		BIT(7)
#घोषणा S2H_DRV_SE0_4RESUME			BIT(14)
#घोषणा PHY_28NM_HSIC_H2S_IMPCAL_DONE		BIT(27)

#घोषणा PHY_28NM_HSIC_CONNECT_INT		BIT(1)
#घोषणा PHY_28NM_HSIC_HS_READY_INT		BIT(2)

काष्ठा mv_hsic_phy अणु
	काष्ठा phy		*phy;
	काष्ठा platक्रमm_device	*pdev;
	व्योम __iomem		*base;
	काष्ठा clk		*clk;
पूर्ण;

अटल पूर्णांक रुको_क्रम_reg(व्योम __iomem *reg, u32 mask, u32 ms)
अणु
	u32 val;

	वापस पढ़ोl_poll_समयout(reg, val, ((val & mask) == mask),
				  1000, 1000 * ms);
पूर्ण

अटल पूर्णांक mv_hsic_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा mv_hsic_phy *mv_phy = phy_get_drvdata(phy);
	काष्ठा platक्रमm_device *pdev = mv_phy->pdev;
	व्योम __iomem *base = mv_phy->base;
	पूर्णांक ret;

	clk_prepare_enable(mv_phy->clk);

	/* Set reference घड़ी */
	ग_लिखोl(0x1 << PHY_28NM_HSIC_PLL_SELLPFR_SHIFT |
		0xf0 << PHY_28NM_HSIC_PLL_FBDIV_SHIFT |
		0xd << PHY_28NM_HSIC_PLL_REFDIV_SHIFT,
		base + PHY_28NM_HSIC_PLL_CTRL01);

	/* Turn on PLL */
	ग_लिखोl(पढ़ोl(base + PHY_28NM_HSIC_PLL_CTRL2) |
		PHY_28NM_HSIC_S2H_PU_PLL,
		base + PHY_28NM_HSIC_PLL_CTRL2);

	/* Make sure PHY PLL is locked */
	ret = रुको_क्रम_reg(base + PHY_28NM_HSIC_PLL_CTRL2,
			   PHY_28NM_HSIC_H2S_PLL_LOCK, 100);
	अगर (ret) अणु
		dev_err(&pdev->dev, "HSIC PHY PLL not locked after 100mS.");
		clk_disable_unprepare(mv_phy->clk);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mv_hsic_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा mv_hsic_phy *mv_phy = phy_get_drvdata(phy);
	काष्ठा platक्रमm_device *pdev = mv_phy->pdev;
	व्योम __iomem *base = mv_phy->base;
	u32 reg;
	पूर्णांक ret;

	reg = पढ़ोl(base + PHY_28NM_HSIC_CTRL);
	/* Aव्योम SE0 state when resume क्रम some device will take it as reset */
	reg &= ~S2H_DRV_SE0_4RESUME;
	reg |= PHY_28NM_HSIC_S2H_HSIC_EN;	/* Enable HSIC PHY */
	ग_लिखोl(reg, base + PHY_28NM_HSIC_CTRL);

	/*
	 *  Calibration Timing
	 *		   ____________________________
	 *  CAL START   ___|
	 *			   ____________________
	 *  CAL_DONE    ___________|
	 *		   | 400us |
	 */

	/* Make sure PHY Calibration is पढ़ोy */
	ret = रुको_क्रम_reg(base + PHY_28NM_HSIC_IMPCAL_CAL,
			   PHY_28NM_HSIC_H2S_IMPCAL_DONE, 100);
	अगर (ret) अणु
		dev_warn(&pdev->dev, "HSIC PHY READY not set after 100mS.");
		वापस ret;
	पूर्ण

	/* Waiting क्रम HSIC connect पूर्णांक*/
	ret = रुको_क्रम_reg(base + PHY_28NM_HSIC_INT,
			   PHY_28NM_HSIC_CONNECT_INT, 200);
	अगर (ret)
		dev_warn(&pdev->dev, "HSIC wait for connect interrupt timeout.");

	वापस ret;
पूर्ण

अटल पूर्णांक mv_hsic_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा mv_hsic_phy *mv_phy = phy_get_drvdata(phy);
	व्योम __iomem *base = mv_phy->base;

	ग_लिखोl(पढ़ोl(base + PHY_28NM_HSIC_CTRL) & ~PHY_28NM_HSIC_S2H_HSIC_EN,
		base + PHY_28NM_HSIC_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_hsic_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा mv_hsic_phy *mv_phy = phy_get_drvdata(phy);
	व्योम __iomem *base = mv_phy->base;

	/* Turn off PLL */
	ग_लिखोl(पढ़ोl(base + PHY_28NM_HSIC_PLL_CTRL2) &
		~PHY_28NM_HSIC_S2H_PU_PLL,
		base + PHY_28NM_HSIC_PLL_CTRL2);

	clk_disable_unprepare(mv_phy->clk);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा phy_ops hsic_ops = अणु
	.init		= mv_hsic_phy_init,
	.घातer_on	= mv_hsic_phy_घातer_on,
	.घातer_off	= mv_hsic_phy_घातer_off,
	.निकास		= mv_hsic_phy_निकास,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक mv_hsic_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *phy_provider;
	काष्ठा mv_hsic_phy *mv_phy;

	mv_phy = devm_kzalloc(&pdev->dev, माप(*mv_phy), GFP_KERNEL);
	अगर (!mv_phy)
		वापस -ENOMEM;

	mv_phy->pdev = pdev;

	mv_phy->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(mv_phy->clk)) अणु
		dev_err(&pdev->dev, "failed to get clock.\n");
		वापस PTR_ERR(mv_phy->clk);
	पूर्ण

	mv_phy->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mv_phy->base))
		वापस PTR_ERR(mv_phy->base);

	mv_phy->phy = devm_phy_create(&pdev->dev, pdev->dev.of_node, &hsic_ops);
	अगर (IS_ERR(mv_phy->phy))
		वापस PTR_ERR(mv_phy->phy);

	phy_set_drvdata(mv_phy->phy, mv_phy);

	phy_provider = devm_of_phy_provider_रेजिस्टर(&pdev->dev, of_phy_simple_xlate);
	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id mv_hsic_phy_dt_match[] = अणु
	अणु .compatible = "marvell,pxa1928-hsic-phy", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mv_hsic_phy_dt_match);

अटल काष्ठा platक्रमm_driver mv_hsic_phy_driver = अणु
	.probe	= mv_hsic_phy_probe,
	.driver = अणु
		.name   = "mv-hsic-phy",
		.of_match_table = of_match_ptr(mv_hsic_phy_dt_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mv_hsic_phy_driver);

MODULE_AUTHOR("Rob Herring <robh@kernel.org>");
MODULE_DESCRIPTION("Marvell HSIC phy driver");
MODULE_LICENSE("GPL v2");
