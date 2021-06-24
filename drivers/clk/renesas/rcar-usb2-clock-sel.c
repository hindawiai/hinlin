<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas R-Car USB2.0 घड़ी selector
 *
 * Copyright (C) 2017 Renesas Electronics Corp.
 *
 * Based on renesas-cpg-mssr.c
 *
 * Copyright (C) 2015 Glider bvba
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>

#घोषणा USB20_CLKSET0		0x00
#घोषणा CLKSET0_INTCLK_EN	BIT(11)
#घोषणा CLKSET0_PRIVATE		BIT(0)
#घोषणा CLKSET0_EXTAL_ONLY	(CLKSET0_INTCLK_EN | CLKSET0_PRIVATE)

अटल स्थिर काष्ठा clk_bulk_data rcar_usb2_घड़ीs[] = अणु
	अणु .id = "ehci_ohci", पूर्ण,
	अणु .id = "hs-usb-if", पूर्ण,
पूर्ण;

काष्ठा usb2_घड़ी_sel_priv अणु
	व्योम __iomem *base;
	काष्ठा clk_hw hw;
	काष्ठा clk_bulk_data clks[ARRAY_SIZE(rcar_usb2_घड़ीs)];
	काष्ठा reset_control *rsts;
	bool extal;
	bool xtal;
पूर्ण;
#घोषणा to_priv(_hw)	container_of(_hw, काष्ठा usb2_घड़ी_sel_priv, hw)

अटल व्योम usb2_घड़ी_sel_enable_extal_only(काष्ठा usb2_घड़ी_sel_priv *priv)
अणु
	u16 val = पढ़ोw(priv->base + USB20_CLKSET0);

	pr_debug("%s: enter %d %d %x\n", __func__,
		 priv->extal, priv->xtal, val);

	अगर (priv->extal && !priv->xtal && val != CLKSET0_EXTAL_ONLY)
		ग_लिखोw(CLKSET0_EXTAL_ONLY, priv->base + USB20_CLKSET0);
पूर्ण

अटल व्योम usb2_घड़ी_sel_disable_extal_only(काष्ठा usb2_घड़ी_sel_priv *priv)
अणु
	अगर (priv->extal && !priv->xtal)
		ग_लिखोw(CLKSET0_PRIVATE, priv->base + USB20_CLKSET0);
पूर्ण

अटल पूर्णांक usb2_घड़ी_sel_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा usb2_घड़ी_sel_priv *priv = to_priv(hw);
	पूर्णांक ret;

	ret = reset_control_deनिश्चित(priv->rsts);
	अगर (ret)
		वापस ret;

	ret = clk_bulk_prepare_enable(ARRAY_SIZE(priv->clks), priv->clks);
	अगर (ret) अणु
		reset_control_निश्चित(priv->rsts);
		वापस ret;
	पूर्ण

	usb2_घड़ी_sel_enable_extal_only(priv);

	वापस 0;
पूर्ण

अटल व्योम usb2_घड़ी_sel_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा usb2_घड़ी_sel_priv *priv = to_priv(hw);

	usb2_घड़ी_sel_disable_extal_only(priv);

	clk_bulk_disable_unprepare(ARRAY_SIZE(priv->clks), priv->clks);
	reset_control_निश्चित(priv->rsts);
पूर्ण

/*
 * This module seems a mux, but this driver assumes a gate because
 * ehci/ohci platक्रमm drivers करोn't support clk_set_parent() क्रम now.
 * If this driver acts as a gate, ehci/ohci-platक्रमm drivers करोn't need
 * any modअगरication.
 */
अटल स्थिर काष्ठा clk_ops usb2_घड़ी_sel_घड़ी_ops = अणु
	.enable = usb2_घड़ी_sel_enable,
	.disable = usb2_घड़ी_sel_disable,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rcar_usb2_घड़ी_sel_match[] = अणु
	अणु .compatible = "renesas,rcar-gen3-usb2-clock-sel" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक rcar_usb2_घड़ी_sel_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb2_घड़ी_sel_priv *priv = dev_get_drvdata(dev);

	usb2_घड़ी_sel_disable_extal_only(priv);
	pm_runसमय_put(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_usb2_घड़ी_sel_resume(काष्ठा device *dev)
अणु
	काष्ठा usb2_घड़ी_sel_priv *priv = dev_get_drvdata(dev);

	pm_runसमय_get_sync(dev);
	usb2_घड़ी_sel_enable_extal_only(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_usb2_घड़ी_sel_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा usb2_घड़ी_sel_priv *priv = platक्रमm_get_drvdata(pdev);

	of_clk_del_provider(dev->of_node);
	clk_hw_unरेजिस्टर(&priv->hw);
	pm_runसमय_put(dev);
	pm_runसमय_disable(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_usb2_घड़ी_sel_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा usb2_घड़ी_sel_priv *priv;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init = अणुपूर्ण;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	स_नकल(priv->clks, rcar_usb2_घड़ीs, माप(priv->clks));
	ret = devm_clk_bulk_get(dev, ARRAY_SIZE(priv->clks), priv->clks);
	अगर (ret < 0)
		वापस ret;

	priv->rsts = devm_reset_control_array_get_shared(dev);
	अगर (IS_ERR(priv->rsts))
		वापस PTR_ERR(priv->rsts);

	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);

	clk = devm_clk_get(dev, "usb_extal");
	अगर (!IS_ERR(clk) && !clk_prepare_enable(clk)) अणु
		priv->extal = !!clk_get_rate(clk);
		clk_disable_unprepare(clk);
	पूर्ण
	clk = devm_clk_get(dev, "usb_xtal");
	अगर (!IS_ERR(clk) && !clk_prepare_enable(clk)) अणु
		priv->xtal = !!clk_get_rate(clk);
		clk_disable_unprepare(clk);
	पूर्ण

	अगर (!priv->extal && !priv->xtal) अणु
		dev_err(dev, "This driver needs usb_extal or usb_xtal\n");
		वापस -ENOENT;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);
	dev_set_drvdata(dev, priv);

	init.name = "rcar_usb2_clock_sel";
	init.ops = &usb2_घड़ी_sel_घड़ी_ops;
	priv->hw.init = &init;

	clk = clk_रेजिस्टर(शून्य, &priv->hw);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	वापस of_clk_add_hw_provider(np, of_clk_hw_simple_get, &priv->hw);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rcar_usb2_घड़ी_sel_pm_ops = अणु
	.suspend	= rcar_usb2_घड़ी_sel_suspend,
	.resume		= rcar_usb2_घड़ी_sel_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver rcar_usb2_घड़ी_sel_driver = अणु
	.driver		= अणु
		.name	= "rcar-usb2-clock-sel",
		.of_match_table = rcar_usb2_घड़ी_sel_match,
		.pm	= &rcar_usb2_घड़ी_sel_pm_ops,
	पूर्ण,
	.probe		= rcar_usb2_घड़ी_sel_probe,
	.हटाओ		= rcar_usb2_घड़ी_sel_हटाओ,
पूर्ण;
builtin_platक्रमm_driver(rcar_usb2_घड़ी_sel_driver);

MODULE_DESCRIPTION("Renesas R-Car USB2 clock selector Driver");
MODULE_LICENSE("GPL v2");
