<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MMP Audio Clock Controller driver
 *
 * Copyright (C) 2020 Lubomir Rपूर्णांकel <lkundrak@v3.sk>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_घड़ी.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <dt-bindings/घड़ी/marvell,mmp2-audपन.स>

/* Audio Controller Registers */
#घोषणा SSPA_AUD_CTRL				0x04
#घोषणा SSPA_AUD_PLL_CTRL0			0x08
#घोषणा SSPA_AUD_PLL_CTRL1			0x0c

/* SSPA Audio Control Register */
#घोषणा SSPA_AUD_CTRL_SYSCLK_SHIFT		0
#घोषणा SSPA_AUD_CTRL_SYSCLK_DIV_SHIFT		1
#घोषणा SSPA_AUD_CTRL_SSPA0_MUX_SHIFT		7
#घोषणा SSPA_AUD_CTRL_SSPA0_SHIFT		8
#घोषणा SSPA_AUD_CTRL_SSPA0_DIV_SHIFT		9
#घोषणा SSPA_AUD_CTRL_SSPA1_SHIFT		16
#घोषणा SSPA_AUD_CTRL_SSPA1_DIV_SHIFT		17
#घोषणा SSPA_AUD_CTRL_SSPA1_MUX_SHIFT		23
#घोषणा SSPA_AUD_CTRL_DIV_MASK			0x7e

/* SSPA Audio PLL Control 0 Register */
#घोषणा SSPA_AUD_PLL_CTRL0_DIV_OCLK_MODULO_MASK (0x7 << 28)
#घोषणा SSPA_AUD_PLL_CTRL0_DIV_OCLK_MODULO(x)	((x) << 28)
#घोषणा SSPA_AUD_PLL_CTRL0_FRACT_MASK		(0xfffff << 8)
#घोषणा SSPA_AUD_PLL_CTRL0_FRACT(x)		((x) << 8)
#घोषणा SSPA_AUD_PLL_CTRL0_ENA_DITHER		(1 << 7)
#घोषणा SSPA_AUD_PLL_CTRL0_ICP_2UA		(0 << 5)
#घोषणा SSPA_AUD_PLL_CTRL0_ICP_5UA		(1 << 5)
#घोषणा SSPA_AUD_PLL_CTRL0_ICP_7UA		(2 << 5)
#घोषणा SSPA_AUD_PLL_CTRL0_ICP_10UA		(3 << 5)
#घोषणा SSPA_AUD_PLL_CTRL0_DIV_FBCCLK_MASK	(0x3 << 3)
#घोषणा SSPA_AUD_PLL_CTRL0_DIV_FBCCLK(x)	((x) << 3)
#घोषणा SSPA_AUD_PLL_CTRL0_DIV_MCLK_MASK	(0x1 << 2)
#घोषणा SSPA_AUD_PLL_CTRL0_DIV_MCLK(x)		((x) << 2)
#घोषणा SSPA_AUD_PLL_CTRL0_PD_OVPROT_DIS	(1 << 1)
#घोषणा SSPA_AUD_PLL_CTRL0_PU			(1 << 0)

/* SSPA Audio PLL Control 1 Register */
#घोषणा SSPA_AUD_PLL_CTRL1_SEL_FAST_CLK		(1 << 24)
#घोषणा SSPA_AUD_PLL_CTRL1_CLK_SEL_MASK		(1 << 11)
#घोषणा SSPA_AUD_PLL_CTRL1_CLK_SEL_AUDIO_PLL	(1 << 11)
#घोषणा SSPA_AUD_PLL_CTRL1_CLK_SEL_VCXO		(0 << 11)
#घोषणा SSPA_AUD_PLL_CTRL1_DIV_OCLK_PATTERN_MASK (0x7ff << 0)
#घोषणा SSPA_AUD_PLL_CTRL1_DIV_OCLK_PATTERN(x)	((x) << 0)

काष्ठा mmp2_audio_clk अणु
	व्योम __iomem *mmio_base;

	काष्ठा clk_hw audio_pll_hw;
	काष्ठा clk_mux sspa_mux;
	काष्ठा clk_mux sspa1_mux;
	काष्ठा clk_भागider sysclk_भाग;
	काष्ठा clk_भागider sspa0_भाग;
	काष्ठा clk_भागider sspa1_भाग;
	काष्ठा clk_gate sysclk_gate;
	काष्ठा clk_gate sspa0_gate;
	काष्ठा clk_gate sspa1_gate;

	u32 aud_ctrl;
	u32 aud_pll_ctrl0;
	u32 aud_pll_ctrl1;

	spinlock_t lock;

	/* Must be last */
	काष्ठा clk_hw_onecell_data clk_data;
पूर्ण;

अटल स्थिर काष्ठा अणु
	अचिन्हित दीर्घ parent_rate;
	अचिन्हित दीर्घ freq_vco;
	अचिन्हित अक्षर mclk;
	अचिन्हित अक्षर fbcclk;
	अचिन्हित लघु fract;
पूर्ण preभागs[] = अणु
	अणु 26000000, 135475200, 0, 0, 0x8a18 पूर्ण,
	अणु 26000000, 147456000, 0, 1, 0x0da1 पूर्ण,
	अणु 38400000, 135475200, 1, 2, 0x8208 पूर्ण,
	अणु 38400000, 147456000, 1, 3, 0xaaaa पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	अचिन्हित अक्षर भागisor;
	अचिन्हित अक्षर modulo;
	अचिन्हित अक्षर pattern;
पूर्ण postभागs[] = अणु
	अणु   1,	3,  0, पूर्ण,
	अणु   2,	5,  0, पूर्ण,
	अणु   4,	0,  0, पूर्ण,
	अणु   6,	1,  1, पूर्ण,
	अणु   8,	1,  0, पूर्ण,
	अणु   9,	1,  2, पूर्ण,
	अणु  12,	2,  1, पूर्ण,
	अणु  16,	2,  0, पूर्ण,
	अणु  18,	2,  2, पूर्ण,
	अणु  24,	4,  1, पूर्ण,
	अणु  36,	4,  2, पूर्ण,
	अणु  48,	6,  1, पूर्ण,
	अणु  72,	6,  2, पूर्ण,
पूर्ण;

अटल अचिन्हित दीर्घ audio_pll_recalc_rate(काष्ठा clk_hw *hw,
					   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा mmp2_audio_clk *priv = container_of(hw, काष्ठा mmp2_audio_clk, audio_pll_hw);
	अचिन्हित पूर्णांक preभाग;
	अचिन्हित पूर्णांक postभाग;
	u32 aud_pll_ctrl0;
	u32 aud_pll_ctrl1;

	aud_pll_ctrl0 = पढ़ोl(priv->mmio_base + SSPA_AUD_PLL_CTRL0);
	aud_pll_ctrl0 &= SSPA_AUD_PLL_CTRL0_DIV_OCLK_MODULO_MASK |
			 SSPA_AUD_PLL_CTRL0_FRACT_MASK |
			 SSPA_AUD_PLL_CTRL0_ENA_DITHER |
			 SSPA_AUD_PLL_CTRL0_DIV_FBCCLK_MASK |
			 SSPA_AUD_PLL_CTRL0_DIV_MCLK_MASK |
			 SSPA_AUD_PLL_CTRL0_PU;

	aud_pll_ctrl1 = पढ़ोl(priv->mmio_base + SSPA_AUD_PLL_CTRL1);
	aud_pll_ctrl1 &= SSPA_AUD_PLL_CTRL1_CLK_SEL_MASK |
			 SSPA_AUD_PLL_CTRL1_DIV_OCLK_PATTERN_MASK;

	क्रम (preभाग = 0; preभाग < ARRAY_SIZE(preभागs); preभाग++) अणु
		अगर (preभागs[preभाग].parent_rate != parent_rate)
			जारी;
		क्रम (postभाग = 0; postभाग < ARRAY_SIZE(postभागs); postभाग++) अणु
			अचिन्हित दीर्घ freq;
			u32 val;

			val = SSPA_AUD_PLL_CTRL0_ENA_DITHER;
			val |= SSPA_AUD_PLL_CTRL0_PU;
			val |= SSPA_AUD_PLL_CTRL0_DIV_OCLK_MODULO(postभागs[postभाग].modulo);
			val |= SSPA_AUD_PLL_CTRL0_FRACT(preभागs[preभाग].fract);
			val |= SSPA_AUD_PLL_CTRL0_DIV_FBCCLK(preभागs[preभाग].fbcclk);
			val |= SSPA_AUD_PLL_CTRL0_DIV_MCLK(preभागs[preभाग].mclk);
			अगर (val != aud_pll_ctrl0)
				जारी;

			val = SSPA_AUD_PLL_CTRL1_CLK_SEL_AUDIO_PLL;
			val |= SSPA_AUD_PLL_CTRL1_DIV_OCLK_PATTERN(postभागs[postभाग].pattern);
			अगर (val != aud_pll_ctrl1)
				जारी;

			freq = preभागs[preभाग].freq_vco;
			freq /= postभागs[postभाग].भागisor;
			वापस freq;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ audio_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ *parent_rate)
अणु
	अचिन्हित पूर्णांक preभाग;
	अचिन्हित पूर्णांक postभाग;
	दीर्घ rounded = 0;

	क्रम (preभाग = 0; preभाग < ARRAY_SIZE(preभागs); preभाग++) अणु
		अगर (preभागs[preभाग].parent_rate != *parent_rate)
			जारी;
		क्रम (postभाग = 0; postभाग < ARRAY_SIZE(postभागs); postभाग++) अणु
			दीर्घ freq = preभागs[preभाग].freq_vco;

			freq /= postभागs[postभाग].भागisor;
			अगर (freq == rate)
				वापस rate;
			अगर (freq < rate)
				जारी;
			अगर (rounded && freq > rounded)
				जारी;
			rounded = freq;
		पूर्ण
	पूर्ण

	वापस rounded;
पूर्ण

अटल पूर्णांक audio_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा mmp2_audio_clk *priv = container_of(hw, काष्ठा mmp2_audio_clk, audio_pll_hw);
	अचिन्हित पूर्णांक preभाग;
	अचिन्हित पूर्णांक postभाग;
	अचिन्हित दीर्घ val;

	क्रम (preभाग = 0; preभाग < ARRAY_SIZE(preभागs); preभाग++) अणु
		अगर (preभागs[preभाग].parent_rate != parent_rate)
			जारी;

		क्रम (postभाग = 0; postभाग < ARRAY_SIZE(postभागs); postभाग++) अणु
			अगर (rate * postभागs[postभाग].भागisor != preभागs[preभाग].freq_vco)
				जारी;

			val = SSPA_AUD_PLL_CTRL0_ENA_DITHER;
			val |= SSPA_AUD_PLL_CTRL0_PU;
			val |= SSPA_AUD_PLL_CTRL0_DIV_OCLK_MODULO(postभागs[postभाग].modulo);
			val |= SSPA_AUD_PLL_CTRL0_FRACT(preभागs[preभाग].fract);
			val |= SSPA_AUD_PLL_CTRL0_DIV_FBCCLK(preभागs[preभाग].fbcclk);
			val |= SSPA_AUD_PLL_CTRL0_DIV_MCLK(preभागs[preभाग].mclk);
			ग_लिखोl(val, priv->mmio_base + SSPA_AUD_PLL_CTRL0);

			val = SSPA_AUD_PLL_CTRL1_CLK_SEL_AUDIO_PLL;
			val |= SSPA_AUD_PLL_CTRL1_DIV_OCLK_PATTERN(postभागs[postभाग].pattern);
			ग_लिखोl(val, priv->mmio_base + SSPA_AUD_PLL_CTRL1);

			वापस 0;
		पूर्ण
	पूर्ण

	वापस -दुस्फल;
पूर्ण

अटल स्थिर काष्ठा clk_ops audio_pll_ops = अणु
	.recalc_rate = audio_pll_recalc_rate,
	.round_rate = audio_pll_round_rate,
	.set_rate = audio_pll_set_rate,
पूर्ण;

अटल पूर्णांक रेजिस्टर_घड़ीs(काष्ठा mmp2_audio_clk *priv, काष्ठा device *dev)
अणु
	स्थिर काष्ठा clk_parent_data sspa_mux_parents[] = अणु
		अणु .hw = &priv->audio_pll_hw पूर्ण,
		अणु .fw_name = "i2s0" पूर्ण,
	पूर्ण;
	स्थिर काष्ठा clk_parent_data sspa1_mux_parents[] = अणु
		अणु .hw = &priv->audio_pll_hw पूर्ण,
		अणु .fw_name = "i2s1" पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	priv->audio_pll_hw.init = CLK_HW_INIT_FW_NAME("audio_pll",
				"vctcxo", &audio_pll_ops,
				CLK_SET_RATE_PARENT);
	ret = devm_clk_hw_रेजिस्टर(dev, &priv->audio_pll_hw);
	अगर (ret)
		वापस ret;

	priv->sspa_mux.hw.init = CLK_HW_INIT_PARENTS_DATA("sspa_mux",
				sspa_mux_parents, &clk_mux_ops,
				CLK_SET_RATE_PARENT);
	priv->sspa_mux.reg = priv->mmio_base + SSPA_AUD_CTRL;
	priv->sspa_mux.mask = 1;
	priv->sspa_mux.shअगरt = SSPA_AUD_CTRL_SSPA0_MUX_SHIFT;
	ret = devm_clk_hw_रेजिस्टर(dev, &priv->sspa_mux.hw);
	अगर (ret)
		वापस ret;

	priv->sysclk_भाग.hw.init = CLK_HW_INIT_HW("sys_div",
				&priv->sspa_mux.hw, &clk_भागider_ops,
				CLK_SET_RATE_PARENT);
	priv->sysclk_भाग.reg = priv->mmio_base + SSPA_AUD_CTRL;
	priv->sysclk_भाग.shअगरt = SSPA_AUD_CTRL_SYSCLK_DIV_SHIFT;
	priv->sysclk_भाग.width = 6;
	priv->sysclk_भाग.flags = CLK_DIVIDER_ONE_BASED;
	priv->sysclk_भाग.flags |= CLK_DIVIDER_ROUND_CLOSEST;
	priv->sysclk_भाग.flags |= CLK_DIVIDER_ALLOW_ZERO;
	ret = devm_clk_hw_रेजिस्टर(dev, &priv->sysclk_भाग.hw);
	अगर (ret)
		वापस ret;

	priv->sysclk_gate.hw.init = CLK_HW_INIT_HW("sys_clk",
				&priv->sysclk_भाग.hw, &clk_gate_ops,
				CLK_SET_RATE_PARENT);
	priv->sysclk_gate.reg = priv->mmio_base + SSPA_AUD_CTRL;
	priv->sysclk_gate.bit_idx = SSPA_AUD_CTRL_SYSCLK_SHIFT;
	ret = devm_clk_hw_रेजिस्टर(dev, &priv->sysclk_gate.hw);
	अगर (ret)
		वापस ret;

	priv->sspa0_भाग.hw.init = CLK_HW_INIT_HW("sspa0_div",
				&priv->sspa_mux.hw, &clk_भागider_ops, 0);
	priv->sspa0_भाग.reg = priv->mmio_base + SSPA_AUD_CTRL;
	priv->sspa0_भाग.shअगरt = SSPA_AUD_CTRL_SSPA0_DIV_SHIFT;
	priv->sspa0_भाग.width = 6;
	priv->sspa0_भाग.flags = CLK_DIVIDER_ONE_BASED;
	priv->sspa0_भाग.flags |= CLK_DIVIDER_ROUND_CLOSEST;
	priv->sspa0_भाग.flags |= CLK_DIVIDER_ALLOW_ZERO;
	ret = devm_clk_hw_रेजिस्टर(dev, &priv->sspa0_भाग.hw);
	अगर (ret)
		वापस ret;

	priv->sspa0_gate.hw.init = CLK_HW_INIT_HW("sspa0_clk",
				&priv->sspa0_भाग.hw, &clk_gate_ops,
				CLK_SET_RATE_PARENT);
	priv->sspa0_gate.reg = priv->mmio_base + SSPA_AUD_CTRL;
	priv->sspa0_gate.bit_idx = SSPA_AUD_CTRL_SSPA0_SHIFT;
	ret = devm_clk_hw_रेजिस्टर(dev, &priv->sspa0_gate.hw);
	अगर (ret)
		वापस ret;

	priv->sspa1_mux.hw.init = CLK_HW_INIT_PARENTS_DATA("sspa1_mux",
				sspa1_mux_parents, &clk_mux_ops,
				CLK_SET_RATE_PARENT);
	priv->sspa1_mux.reg = priv->mmio_base + SSPA_AUD_CTRL;
	priv->sspa1_mux.mask = 1;
	priv->sspa1_mux.shअगरt = SSPA_AUD_CTRL_SSPA1_MUX_SHIFT;
	ret = devm_clk_hw_रेजिस्टर(dev, &priv->sspa1_mux.hw);
	अगर (ret)
		वापस ret;

	priv->sspa1_भाग.hw.init = CLK_HW_INIT_HW("sspa1_div",
				&priv->sspa1_mux.hw, &clk_भागider_ops, 0);
	priv->sspa1_भाग.reg = priv->mmio_base + SSPA_AUD_CTRL;
	priv->sspa1_भाग.shअगरt = SSPA_AUD_CTRL_SSPA1_DIV_SHIFT;
	priv->sspa1_भाग.width = 6;
	priv->sspa1_भाग.flags = CLK_DIVIDER_ONE_BASED;
	priv->sspa1_भाग.flags |= CLK_DIVIDER_ROUND_CLOSEST;
	priv->sspa1_भाग.flags |= CLK_DIVIDER_ALLOW_ZERO;
	ret = devm_clk_hw_रेजिस्टर(dev, &priv->sspa1_भाग.hw);
	अगर (ret)
		वापस ret;

	priv->sspa1_gate.hw.init = CLK_HW_INIT_HW("sspa1_clk",
				&priv->sspa1_भाग.hw, &clk_gate_ops,
				CLK_SET_RATE_PARENT);
	priv->sspa1_gate.reg = priv->mmio_base + SSPA_AUD_CTRL;
	priv->sspa1_gate.bit_idx = SSPA_AUD_CTRL_SSPA1_SHIFT;
	ret = devm_clk_hw_रेजिस्टर(dev, &priv->sspa1_gate.hw);
	अगर (ret)
		वापस ret;

	priv->clk_data.hws[MMP2_CLK_AUDIO_SYSCLK] = &priv->sysclk_gate.hw;
	priv->clk_data.hws[MMP2_CLK_AUDIO_SSPA0] = &priv->sspa0_gate.hw;
	priv->clk_data.hws[MMP2_CLK_AUDIO_SSPA1] = &priv->sspa1_gate.hw;
	priv->clk_data.num = MMP2_CLK_AUDIO_NR_CLKS;

	वापस of_clk_add_hw_provider(dev->of_node, of_clk_hw_onecell_get,
				      &priv->clk_data);
पूर्ण

अटल पूर्णांक mmp2_audio_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mmp2_audio_clk *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev,
			    काष्ठा_size(priv, clk_data.hws,
					MMP2_CLK_AUDIO_NR_CLKS),
			    GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	spin_lock_init(&priv->lock);
	platक्रमm_set_drvdata(pdev, priv);

	priv->mmio_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->mmio_base))
		वापस PTR_ERR(priv->mmio_base);

	pm_runसमय_enable(&pdev->dev);
	ret = pm_clk_create(&pdev->dev);
	अगर (ret)
		जाओ disable_pm_runसमय;

	ret = pm_clk_add(&pdev->dev, "audio");
	अगर (ret)
		जाओ destroy_pm_clk;

	ret = रेजिस्टर_घड़ीs(priv, &pdev->dev);
	अगर (ret)
		जाओ destroy_pm_clk;

	वापस 0;

destroy_pm_clk:
	pm_clk_destroy(&pdev->dev);
disable_pm_runसमय:
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक mmp2_audio_clk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_clk_destroy(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mmp2_audio_clk_suspend(काष्ठा device *dev)
अणु
	काष्ठा mmp2_audio_clk *priv = dev_get_drvdata(dev);

	priv->aud_ctrl = पढ़ोl(priv->mmio_base + SSPA_AUD_CTRL);
	priv->aud_pll_ctrl0 = पढ़ोl(priv->mmio_base + SSPA_AUD_PLL_CTRL0);
	priv->aud_pll_ctrl1 = पढ़ोl(priv->mmio_base + SSPA_AUD_PLL_CTRL1);
	pm_clk_suspend(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक mmp2_audio_clk_resume(काष्ठा device *dev)
अणु
	काष्ठा mmp2_audio_clk *priv = dev_get_drvdata(dev);

	pm_clk_resume(dev);
	ग_लिखोl(priv->aud_ctrl, priv->mmio_base + SSPA_AUD_CTRL);
	ग_लिखोl(priv->aud_pll_ctrl0, priv->mmio_base + SSPA_AUD_PLL_CTRL0);
	ग_लिखोl(priv->aud_pll_ctrl1, priv->mmio_base + SSPA_AUD_PLL_CTRL1);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops mmp2_audio_clk_pm_ops = अणु
	SET_RUNTIME_PM_OPS(mmp2_audio_clk_suspend, mmp2_audio_clk_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id mmp2_audio_clk_of_match[] = अणु
	अणु .compatible = "marvell,mmp2-audio-clock" पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, mmp2_audio_clk_of_match);

अटल काष्ठा platक्रमm_driver mmp2_audio_clk_driver = अणु
	.driver = अणु
		.name = "mmp2-audio-clock",
		.of_match_table = of_match_ptr(mmp2_audio_clk_of_match),
		.pm = &mmp2_audio_clk_pm_ops,
	पूर्ण,
	.probe = mmp2_audio_clk_probe,
	.हटाओ = mmp2_audio_clk_हटाओ,
पूर्ण;
module_platक्रमm_driver(mmp2_audio_clk_driver);

MODULE_AUTHOR("Lubomir Rintel <lkundrak@v3.sk>");
MODULE_DESCRIPTION("Clock driver for MMP2 Audio subsystem");
MODULE_LICENSE("GPL");
