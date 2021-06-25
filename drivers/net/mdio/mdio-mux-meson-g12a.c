<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Baylibre, SAS.
 * Author: Jerome Brunet <jbrunet@baylibre.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/mdio-mux.h>
#समावेश <linux/module.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा ETH_PLL_STS		0x40
#घोषणा ETH_PLL_CTL0		0x44
#घोषणा  PLL_CTL0_LOCK_DIG	BIT(30)
#घोषणा  PLL_CTL0_RST		BIT(29)
#घोषणा  PLL_CTL0_EN		BIT(28)
#घोषणा  PLL_CTL0_SEL		BIT(23)
#घोषणा  PLL_CTL0_N		GENMASK(14, 10)
#घोषणा  PLL_CTL0_M		GENMASK(8, 0)
#घोषणा  PLL_LOCK_TIMEOUT	1000000
#घोषणा  PLL_MUX_NUM_PARENT	2
#घोषणा ETH_PLL_CTL1		0x48
#घोषणा ETH_PLL_CTL2		0x4c
#घोषणा ETH_PLL_CTL3		0x50
#घोषणा ETH_PLL_CTL4		0x54
#घोषणा ETH_PLL_CTL5		0x58
#घोषणा ETH_PLL_CTL6		0x5c
#घोषणा ETH_PLL_CTL7		0x60

#घोषणा ETH_PHY_CNTL0		0x80
#घोषणा   EPHY_G12A_ID		0x33010180
#घोषणा ETH_PHY_CNTL1		0x84
#घोषणा  PHY_CNTL1_ST_MODE	GENMASK(2, 0)
#घोषणा  PHY_CNTL1_ST_PHYADD	GENMASK(7, 3)
#घोषणा   EPHY_DFLT_ADD		8
#घोषणा  PHY_CNTL1_MII_MODE	GENMASK(15, 14)
#घोषणा   EPHY_MODE_RMII	0x1
#घोषणा  PHY_CNTL1_CLK_EN	BIT(16)
#घोषणा  PHY_CNTL1_CLKFREQ	BIT(17)
#घोषणा  PHY_CNTL1_PHY_ENB	BIT(18)
#घोषणा ETH_PHY_CNTL2		0x88
#घोषणा  PHY_CNTL2_USE_INTERNAL	BIT(5)
#घोषणा  PHY_CNTL2_SMI_SRC_MAC	BIT(6)
#घोषणा  PHY_CNTL2_RX_CLK_EPHY	BIT(9)

#घोषणा MESON_G12A_MDIO_EXTERNAL_ID 0
#घोषणा MESON_G12A_MDIO_INTERNAL_ID 1

काष्ठा g12a_mdio_mux अणु
	bool pll_is_enabled;
	व्योम __iomem *regs;
	व्योम *mux_handle;
	काष्ठा clk *pclk;
	काष्ठा clk *pll;
पूर्ण;

काष्ठा g12a_ephy_pll अणु
	व्योम __iomem *base;
	काष्ठा clk_hw hw;
पूर्ण;

#घोषणा g12a_ephy_pll_to_dev(_hw)			\
	container_of(_hw, काष्ठा g12a_ephy_pll, hw)

अटल अचिन्हित दीर्घ g12a_ephy_pll_recalc_rate(काष्ठा clk_hw *hw,
					       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा g12a_ephy_pll *pll = g12a_ephy_pll_to_dev(hw);
	u32 val, m, n;

	val = पढ़ोl(pll->base + ETH_PLL_CTL0);
	m = FIELD_GET(PLL_CTL0_M, val);
	n = FIELD_GET(PLL_CTL0_N, val);

	वापस parent_rate * m / n;
पूर्ण

अटल पूर्णांक g12a_ephy_pll_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा g12a_ephy_pll *pll = g12a_ephy_pll_to_dev(hw);
	u32 val = पढ़ोl(pll->base + ETH_PLL_CTL0);

	/* Apply both enable an reset */
	val |= PLL_CTL0_RST | PLL_CTL0_EN;
	ग_लिखोl(val, pll->base + ETH_PLL_CTL0);

	/* Clear the reset to let PLL lock */
	val &= ~PLL_CTL0_RST;
	ग_लिखोl(val, pll->base + ETH_PLL_CTL0);

	/* Poll on the digital lock instead of the usual analog lock
	 * This is करोne because bit 31 is unreliable on some SoC. Bit
	 * 31 may indicate that the PLL is not lock eventhough the घड़ी
	 * is actually running
	 */
	वापस पढ़ोl_poll_समयout(pll->base + ETH_PLL_CTL0, val,
				  val & PLL_CTL0_LOCK_DIG, 0, PLL_LOCK_TIMEOUT);
पूर्ण

अटल व्योम g12a_ephy_pll_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा g12a_ephy_pll *pll = g12a_ephy_pll_to_dev(hw);
	u32 val;

	val = पढ़ोl(pll->base + ETH_PLL_CTL0);
	val &= ~PLL_CTL0_EN;
	val |= PLL_CTL0_RST;
	ग_लिखोl(val, pll->base + ETH_PLL_CTL0);
पूर्ण

अटल पूर्णांक g12a_ephy_pll_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा g12a_ephy_pll *pll = g12a_ephy_pll_to_dev(hw);
	अचिन्हित पूर्णांक val;

	val = पढ़ोl(pll->base + ETH_PLL_CTL0);

	वापस (val & PLL_CTL0_LOCK_DIG) ? 1 : 0;
पूर्ण

अटल पूर्णांक g12a_ephy_pll_init(काष्ठा clk_hw *hw)
अणु
	काष्ठा g12a_ephy_pll *pll = g12a_ephy_pll_to_dev(hw);

	/* Apply PLL HW settings */
	ग_लिखोl(0x29c0040a, pll->base + ETH_PLL_CTL0);
	ग_लिखोl(0x927e0000, pll->base + ETH_PLL_CTL1);
	ग_लिखोl(0xac5f49e5, pll->base + ETH_PLL_CTL2);
	ग_लिखोl(0x00000000, pll->base + ETH_PLL_CTL3);
	ग_लिखोl(0x00000000, pll->base + ETH_PLL_CTL4);
	ग_लिखोl(0x20200000, pll->base + ETH_PLL_CTL5);
	ग_लिखोl(0x0000c002, pll->base + ETH_PLL_CTL6);
	ग_लिखोl(0x00000023, pll->base + ETH_PLL_CTL7);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops g12a_ephy_pll_ops = अणु
	.recalc_rate	= g12a_ephy_pll_recalc_rate,
	.is_enabled	= g12a_ephy_pll_is_enabled,
	.enable		= g12a_ephy_pll_enable,
	.disable	= g12a_ephy_pll_disable,
	.init		= g12a_ephy_pll_init,
पूर्ण;

अटल पूर्णांक g12a_enable_पूर्णांकernal_mdio(काष्ठा g12a_mdio_mux *priv)
अणु
	पूर्णांक ret;

	/* Enable the phy घड़ी */
	अगर (!priv->pll_is_enabled) अणु
		ret = clk_prepare_enable(priv->pll);
		अगर (ret)
			वापस ret;
	पूर्ण

	priv->pll_is_enabled = true;

	/* Initialize ephy control */
	ग_लिखोl(EPHY_G12A_ID, priv->regs + ETH_PHY_CNTL0);
	ग_लिखोl(FIELD_PREP(PHY_CNTL1_ST_MODE, 3) |
	       FIELD_PREP(PHY_CNTL1_ST_PHYADD, EPHY_DFLT_ADD) |
	       FIELD_PREP(PHY_CNTL1_MII_MODE, EPHY_MODE_RMII) |
	       PHY_CNTL1_CLK_EN |
	       PHY_CNTL1_CLKFREQ |
	       PHY_CNTL1_PHY_ENB,
	       priv->regs + ETH_PHY_CNTL1);
	ग_लिखोl(PHY_CNTL2_USE_INTERNAL |
	       PHY_CNTL2_SMI_SRC_MAC |
	       PHY_CNTL2_RX_CLK_EPHY,
	       priv->regs + ETH_PHY_CNTL2);

	वापस 0;
पूर्ण

अटल पूर्णांक g12a_enable_बाह्यal_mdio(काष्ठा g12a_mdio_mux *priv)
अणु
	/* Reset the mdio bus mux */
	ग_लिखोl_relaxed(0x0, priv->regs + ETH_PHY_CNTL2);

	/* Disable the phy घड़ी अगर enabled */
	अगर (priv->pll_is_enabled) अणु
		clk_disable_unprepare(priv->pll);
		priv->pll_is_enabled = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक g12a_mdio_चयन_fn(पूर्णांक current_child, पूर्णांक desired_child,
			       व्योम *data)
अणु
	काष्ठा g12a_mdio_mux *priv = dev_get_drvdata(data);

	अगर (current_child == desired_child)
		वापस 0;

	चयन (desired_child) अणु
	हाल MESON_G12A_MDIO_EXTERNAL_ID:
		वापस g12a_enable_बाह्यal_mdio(priv);
	हाल MESON_G12A_MDIO_INTERNAL_ID:
		वापस g12a_enable_पूर्णांकernal_mdio(priv);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा of_device_id g12a_mdio_mux_match[] = अणु
	अणु .compatible = "amlogic,g12a-mdio-mux", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, g12a_mdio_mux_match);

अटल पूर्णांक g12a_ephy_glue_clk_रेजिस्टर(काष्ठा device *dev)
अणु
	काष्ठा g12a_mdio_mux *priv = dev_get_drvdata(dev);
	स्थिर अक्षर *parent_names[PLL_MUX_NUM_PARENT];
	काष्ठा clk_init_data init;
	काष्ठा g12a_ephy_pll *pll;
	काष्ठा clk_mux *mux;
	काष्ठा clk *clk;
	अक्षर *name;
	पूर्णांक i;

	/* get the mux parents */
	क्रम (i = 0; i < PLL_MUX_NUM_PARENT; i++) अणु
		अक्षर in_name[8];

		snम_लिखो(in_name, माप(in_name), "clkin%d", i);
		clk = devm_clk_get(dev, in_name);
		अगर (IS_ERR(clk)) अणु
			अगर (PTR_ERR(clk) != -EPROBE_DEFER)
				dev_err(dev, "Missing clock %s\n", in_name);
			वापस PTR_ERR(clk);
		पूर्ण

		parent_names[i] = __clk_get_name(clk);
	पूर्ण

	/* create the input mux */
	mux = devm_kzalloc(dev, माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस -ENOMEM;

	name = kaप्र_लिखो(GFP_KERNEL, "%s#mux", dev_name(dev));
	अगर (!name)
		वापस -ENOMEM;

	init.name = name;
	init.ops = &clk_mux_ro_ops;
	init.flags = 0;
	init.parent_names = parent_names;
	init.num_parents = PLL_MUX_NUM_PARENT;

	mux->reg = priv->regs + ETH_PLL_CTL0;
	mux->shअगरt = __ffs(PLL_CTL0_SEL);
	mux->mask = PLL_CTL0_SEL >> mux->shअगरt;
	mux->hw.init = &init;

	clk = devm_clk_रेजिस्टर(dev, &mux->hw);
	kमुक्त(name);
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "failed to register input mux\n");
		वापस PTR_ERR(clk);
	पूर्ण

	/* create the pll */
	pll = devm_kzalloc(dev, माप(*pll), GFP_KERNEL);
	अगर (!pll)
		वापस -ENOMEM;

	name = kaप्र_लिखो(GFP_KERNEL, "%s#pll", dev_name(dev));
	अगर (!name)
		वापस -ENOMEM;

	init.name = name;
	init.ops = &g12a_ephy_pll_ops;
	init.flags = 0;
	parent_names[0] = __clk_get_name(clk);
	init.parent_names = parent_names;
	init.num_parents = 1;

	pll->base = priv->regs;
	pll->hw.init = &init;

	clk = devm_clk_रेजिस्टर(dev, &pll->hw);
	kमुक्त(name);
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "failed to register input mux\n");
		वापस PTR_ERR(clk);
	पूर्ण

	priv->pll = clk;

	वापस 0;
पूर्ण

अटल पूर्णांक g12a_mdio_mux_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा g12a_mdio_mux *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);

	priv->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->regs))
		वापस PTR_ERR(priv->regs);

	priv->pclk = devm_clk_get(dev, "pclk");
	अगर (IS_ERR(priv->pclk)) अणु
		ret = PTR_ERR(priv->pclk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get peripheral clock\n");
		वापस ret;
	पूर्ण

	/* Make sure the device रेजिस्टरs are घड़ीed */
	ret = clk_prepare_enable(priv->pclk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable peripheral clock");
		वापस ret;
	पूर्ण

	/* Register PLL in CCF */
	ret = g12a_ephy_glue_clk_रेजिस्टर(dev);
	अगर (ret)
		जाओ err;

	ret = mdio_mux_init(dev, dev->of_node, g12a_mdio_चयन_fn,
			    &priv->mux_handle, dev, शून्य);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "mdio multiplexer init failed: %d", ret);
		जाओ err;
	पूर्ण

	वापस 0;

err:
	clk_disable_unprepare(priv->pclk);
	वापस ret;
पूर्ण

अटल पूर्णांक g12a_mdio_mux_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा g12a_mdio_mux *priv = platक्रमm_get_drvdata(pdev);

	mdio_mux_uninit(priv->mux_handle);

	अगर (priv->pll_is_enabled)
		clk_disable_unprepare(priv->pll);

	clk_disable_unprepare(priv->pclk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver g12a_mdio_mux_driver = अणु
	.probe		= g12a_mdio_mux_probe,
	.हटाओ		= g12a_mdio_mux_हटाओ,
	.driver		= अणु
		.name	= "g12a-mdio_mux",
		.of_match_table = g12a_mdio_mux_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(g12a_mdio_mux_driver);

MODULE_DESCRIPTION("Amlogic G12a MDIO multiplexer driver");
MODULE_AUTHOR("Jerome Brunet <jbrunet@baylibre.com>");
MODULE_LICENSE("GPL v2");
