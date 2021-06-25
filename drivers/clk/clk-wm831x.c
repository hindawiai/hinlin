<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * WM831x घड़ी control
 *
 * Copyright 2011-2 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/wm831x/core.h>

काष्ठा wm831x_clk अणु
	काष्ठा wm831x *wm831x;
	काष्ठा clk_hw xtal_hw;
	काष्ठा clk_hw fll_hw;
	काष्ठा clk_hw clkout_hw;
	bool xtal_ena;
पूर्ण;

अटल पूर्णांक wm831x_xtal_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा wm831x_clk *clkdata = container_of(hw, काष्ठा wm831x_clk,
						  xtal_hw);

	वापस clkdata->xtal_ena;
पूर्ण

अटल अचिन्हित दीर्घ wm831x_xtal_recalc_rate(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा wm831x_clk *clkdata = container_of(hw, काष्ठा wm831x_clk,
						  xtal_hw);

	अगर (clkdata->xtal_ena)
		वापस 32768;
	अन्यथा
		वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops wm831x_xtal_ops = अणु
	.is_prepared = wm831x_xtal_is_prepared,
	.recalc_rate = wm831x_xtal_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_init_data wm831x_xtal_init = अणु
	.name = "xtal",
	.ops = &wm831x_xtal_ops,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ wm831x_fll_स्वतः_rates[] = अणु
	 2048000,
	11289600,
	12000000,
	12288000,
	19200000,
	22579600,
	24000000,
	24576000,
पूर्ण;

अटल पूर्णांक wm831x_fll_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा wm831x_clk *clkdata = container_of(hw, काष्ठा wm831x_clk,
						  fll_hw);
	काष्ठा wm831x *wm831x = clkdata->wm831x;
	पूर्णांक ret;

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_FLL_CONTROL_1);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev, "Unable to read FLL_CONTROL_1: %d\n",
			ret);
		वापस true;
	पूर्ण

	वापस (ret & WM831X_FLL_ENA) != 0;
पूर्ण

अटल पूर्णांक wm831x_fll_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा wm831x_clk *clkdata = container_of(hw, काष्ठा wm831x_clk,
						  fll_hw);
	काष्ठा wm831x *wm831x = clkdata->wm831x;
	पूर्णांक ret;

	ret = wm831x_set_bits(wm831x, WM831X_FLL_CONTROL_1,
			      WM831X_FLL_ENA, WM831X_FLL_ENA);
	अगर (ret != 0)
		dev_crit(wm831x->dev, "Failed to enable FLL: %d\n", ret);

	/* रुको 2-3 ms क्रम new frequency taking effect */
	usleep_range(2000, 3000);

	वापस ret;
पूर्ण

अटल व्योम wm831x_fll_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा wm831x_clk *clkdata = container_of(hw, काष्ठा wm831x_clk,
						  fll_hw);
	काष्ठा wm831x *wm831x = clkdata->wm831x;
	पूर्णांक ret;

	ret = wm831x_set_bits(wm831x, WM831X_FLL_CONTROL_1, WM831X_FLL_ENA, 0);
	अगर (ret != 0)
		dev_crit(wm831x->dev, "Failed to disable FLL: %d\n", ret);
पूर्ण

अटल अचिन्हित दीर्घ wm831x_fll_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा wm831x_clk *clkdata = container_of(hw, काष्ठा wm831x_clk,
						  fll_hw);
	काष्ठा wm831x *wm831x = clkdata->wm831x;
	पूर्णांक ret;

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_CLOCK_CONTROL_2);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev, "Unable to read CLOCK_CONTROL_2: %d\n",
			ret);
		वापस 0;
	पूर्ण

	अगर (ret & WM831X_FLL_AUTO)
		वापस wm831x_fll_स्वतः_rates[ret & WM831X_FLL_AUTO_FREQ_MASK];

	dev_err(wm831x->dev, "FLL only supported in AUTO mode\n");

	वापस 0;
पूर्ण

अटल दीर्घ wm831x_fll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ *unused)
अणु
	पूर्णांक best = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(wm831x_fll_स्वतः_rates); i++)
		अगर (असल(wm831x_fll_स्वतः_rates[i] - rate) <
		    असल(wm831x_fll_स्वतः_rates[best] - rate))
			best = i;

	वापस wm831x_fll_स्वतः_rates[best];
पूर्ण

अटल पूर्णांक wm831x_fll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा wm831x_clk *clkdata = container_of(hw, काष्ठा wm831x_clk,
						  fll_hw);
	काष्ठा wm831x *wm831x = clkdata->wm831x;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(wm831x_fll_स्वतः_rates); i++)
		अगर (wm831x_fll_स्वतः_rates[i] == rate)
			अवरोध;
	अगर (i == ARRAY_SIZE(wm831x_fll_स्वतः_rates))
		वापस -EINVAL;

	अगर (wm831x_fll_is_prepared(hw))
		वापस -EPERM;

	वापस wm831x_set_bits(wm831x, WM831X_CLOCK_CONTROL_2,
			       WM831X_FLL_AUTO_FREQ_MASK, i);
पूर्ण

अटल स्थिर अक्षर *wm831x_fll_parents[] = अणु
	"xtal",
	"clkin",
पूर्ण;

अटल u8 wm831x_fll_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा wm831x_clk *clkdata = container_of(hw, काष्ठा wm831x_clk,
						  fll_hw);
	काष्ठा wm831x *wm831x = clkdata->wm831x;
	पूर्णांक ret;

	/* AUTO mode is always घड़ीed from the crystal */
	ret = wm831x_reg_पढ़ो(wm831x, WM831X_CLOCK_CONTROL_2);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev, "Unable to read CLOCK_CONTROL_2: %d\n",
			ret);
		वापस 0;
	पूर्ण

	अगर (ret & WM831X_FLL_AUTO)
		वापस 0;

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_FLL_CONTROL_5);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev, "Unable to read FLL_CONTROL_5: %d\n",
			ret);
		वापस 0;
	पूर्ण

	चयन (ret & WM831X_FLL_CLK_SRC_MASK) अणु
	हाल 0:
		वापस 0;
	हाल 1:
		वापस 1;
	शेष:
		dev_err(wm831x->dev, "Unsupported FLL clock source %d\n",
			ret & WM831X_FLL_CLK_SRC_MASK);
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा clk_ops wm831x_fll_ops = अणु
	.is_prepared = wm831x_fll_is_prepared,
	.prepare = wm831x_fll_prepare,
	.unprepare = wm831x_fll_unprepare,
	.round_rate = wm831x_fll_round_rate,
	.recalc_rate = wm831x_fll_recalc_rate,
	.set_rate = wm831x_fll_set_rate,
	.get_parent = wm831x_fll_get_parent,
पूर्ण;

अटल स्थिर काष्ठा clk_init_data wm831x_fll_init = अणु
	.name = "fll",
	.ops = &wm831x_fll_ops,
	.parent_names = wm831x_fll_parents,
	.num_parents = ARRAY_SIZE(wm831x_fll_parents),
	.flags = CLK_SET_RATE_GATE,
पूर्ण;

अटल पूर्णांक wm831x_clkout_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा wm831x_clk *clkdata = container_of(hw, काष्ठा wm831x_clk,
						  clkout_hw);
	काष्ठा wm831x *wm831x = clkdata->wm831x;
	पूर्णांक ret;

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_CLOCK_CONTROL_1);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev, "Unable to read CLOCK_CONTROL_1: %d\n",
			ret);
		वापस false;
	पूर्ण

	वापस (ret & WM831X_CLKOUT_ENA) != 0;
पूर्ण

अटल पूर्णांक wm831x_clkout_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा wm831x_clk *clkdata = container_of(hw, काष्ठा wm831x_clk,
						  clkout_hw);
	काष्ठा wm831x *wm831x = clkdata->wm831x;
	पूर्णांक ret;

	ret = wm831x_reg_unlock(wm831x);
	अगर (ret != 0) अणु
		dev_crit(wm831x->dev, "Failed to lock registers: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = wm831x_set_bits(wm831x, WM831X_CLOCK_CONTROL_1,
			      WM831X_CLKOUT_ENA, WM831X_CLKOUT_ENA);
	अगर (ret != 0)
		dev_crit(wm831x->dev, "Failed to enable CLKOUT: %d\n", ret);

	wm831x_reg_lock(wm831x);

	वापस ret;
पूर्ण

अटल व्योम wm831x_clkout_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा wm831x_clk *clkdata = container_of(hw, काष्ठा wm831x_clk,
						  clkout_hw);
	काष्ठा wm831x *wm831x = clkdata->wm831x;
	पूर्णांक ret;

	ret = wm831x_reg_unlock(wm831x);
	अगर (ret != 0) अणु
		dev_crit(wm831x->dev, "Failed to lock registers: %d\n", ret);
		वापस;
	पूर्ण

	ret = wm831x_set_bits(wm831x, WM831X_CLOCK_CONTROL_1,
			      WM831X_CLKOUT_ENA, 0);
	अगर (ret != 0)
		dev_crit(wm831x->dev, "Failed to disable CLKOUT: %d\n", ret);

	wm831x_reg_lock(wm831x);
पूर्ण

अटल स्थिर अक्षर *wm831x_clkout_parents[] = अणु
	"fll",
	"xtal",
पूर्ण;

अटल u8 wm831x_clkout_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा wm831x_clk *clkdata = container_of(hw, काष्ठा wm831x_clk,
						  clkout_hw);
	काष्ठा wm831x *wm831x = clkdata->wm831x;
	पूर्णांक ret;

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_CLOCK_CONTROL_1);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev, "Unable to read CLOCK_CONTROL_1: %d\n",
			ret);
		वापस 0;
	पूर्ण

	अगर (ret & WM831X_CLKOUT_SRC)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक wm831x_clkout_set_parent(काष्ठा clk_hw *hw, u8 parent)
अणु
	काष्ठा wm831x_clk *clkdata = container_of(hw, काष्ठा wm831x_clk,
						  clkout_hw);
	काष्ठा wm831x *wm831x = clkdata->wm831x;

	वापस wm831x_set_bits(wm831x, WM831X_CLOCK_CONTROL_1,
			       WM831X_CLKOUT_SRC,
			       parent << WM831X_CLKOUT_SRC_SHIFT);
पूर्ण

अटल स्थिर काष्ठा clk_ops wm831x_clkout_ops = अणु
	.is_prepared = wm831x_clkout_is_prepared,
	.prepare = wm831x_clkout_prepare,
	.unprepare = wm831x_clkout_unprepare,
	.get_parent = wm831x_clkout_get_parent,
	.set_parent = wm831x_clkout_set_parent,
पूर्ण;

अटल स्थिर काष्ठा clk_init_data wm831x_clkout_init = अणु
	.name = "clkout",
	.ops = &wm831x_clkout_ops,
	.parent_names = wm831x_clkout_parents,
	.num_parents = ARRAY_SIZE(wm831x_clkout_parents),
	.flags = CLK_SET_RATE_PARENT,
पूर्ण;

अटल पूर्णांक wm831x_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm831x_clk *clkdata;
	पूर्णांक ret;

	clkdata = devm_kzalloc(&pdev->dev, माप(*clkdata), GFP_KERNEL);
	अगर (!clkdata)
		वापस -ENOMEM;

	clkdata->wm831x = wm831x;

	/* XTAL_ENA can only be set via OTP/InstantConfig so just पढ़ो once */
	ret = wm831x_reg_पढ़ो(wm831x, WM831X_CLOCK_CONTROL_2);
	अगर (ret < 0) अणु
		dev_err(wm831x->dev, "Unable to read CLOCK_CONTROL_2: %d\n",
			ret);
		वापस ret;
	पूर्ण
	clkdata->xtal_ena = ret & WM831X_XTAL_ENA;

	clkdata->xtal_hw.init = &wm831x_xtal_init;
	ret = devm_clk_hw_रेजिस्टर(&pdev->dev, &clkdata->xtal_hw);
	अगर (ret)
		वापस ret;

	clkdata->fll_hw.init = &wm831x_fll_init;
	ret = devm_clk_hw_रेजिस्टर(&pdev->dev, &clkdata->fll_hw);
	अगर (ret)
		वापस ret;

	clkdata->clkout_hw.init = &wm831x_clkout_init;
	ret = devm_clk_hw_रेजिस्टर(&pdev->dev, &clkdata->clkout_hw);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, clkdata);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wm831x_clk_driver = अणु
	.probe = wm831x_clk_probe,
	.driver		= अणु
		.name	= "wm831x-clk",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wm831x_clk_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("WM831x clock driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm831x-clk");
