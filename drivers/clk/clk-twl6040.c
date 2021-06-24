<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
* TWL6040 घड़ी module driver क्रम OMAP4 McPDM functional घड़ी
*
* Copyright (C) 2012 Texas Instruments Inc.
* Peter Ujfalusi <peter.ujfalusi@ti.com>
*/

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/twl6040.h>
#समावेश <linux/clk-provider.h>

काष्ठा twl6040_pdmclk अणु
	काष्ठा twl6040 *twl6040;
	काष्ठा device *dev;
	काष्ठा clk_hw pdmclk_hw;
	पूर्णांक enabled;
पूर्ण;

अटल पूर्णांक twl6040_pdmclk_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा twl6040_pdmclk *pdmclk = container_of(hw, काष्ठा twl6040_pdmclk,
						     pdmclk_hw);

	वापस pdmclk->enabled;
पूर्ण

अटल पूर्णांक twl6040_pdmclk_reset_one_घड़ी(काष्ठा twl6040_pdmclk *pdmclk,
					  अचिन्हित पूर्णांक reg)
अणु
	स्थिर u8 reset_mask = TWL6040_HPLLRST;	/* Same क्रम HPPLL and LPPLL */
	पूर्णांक ret;

	ret = twl6040_set_bits(pdmclk->twl6040, reg, reset_mask);
	अगर (ret < 0)
		वापस ret;

	ret = twl6040_clear_bits(pdmclk->twl6040, reg, reset_mask);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * TWL6040A2 Phoenix Audio IC erratum #6: "PDM Clock Generation Issue At
 * Cold Temperature". This affects cold boot and deeper idle states it
 * seems. The workaround consists of resetting HPPLL and LPPLL.
 */
अटल पूर्णांक twl6040_pdmclk_quirk_reset_घड़ीs(काष्ठा twl6040_pdmclk *pdmclk)
अणु
	पूर्णांक ret;

	ret = twl6040_pdmclk_reset_one_घड़ी(pdmclk, TWL6040_REG_HPPLLCTL);
	अगर (ret)
		वापस ret;

	ret = twl6040_pdmclk_reset_one_घड़ी(pdmclk, TWL6040_REG_LPPLLCTL);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक twl6040_pdmclk_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा twl6040_pdmclk *pdmclk = container_of(hw, काष्ठा twl6040_pdmclk,
						     pdmclk_hw);
	पूर्णांक ret;

	ret = twl6040_घातer(pdmclk->twl6040, 1);
	अगर (ret)
		वापस ret;

	ret = twl6040_pdmclk_quirk_reset_घड़ीs(pdmclk);
	अगर (ret)
		जाओ out_err;

	pdmclk->enabled = 1;

	वापस 0;

out_err:
	dev_err(pdmclk->dev, "%s: error %i\n", __func__, ret);
	twl6040_घातer(pdmclk->twl6040, 0);

	वापस ret;
पूर्ण

अटल व्योम twl6040_pdmclk_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा twl6040_pdmclk *pdmclk = container_of(hw, काष्ठा twl6040_pdmclk,
						     pdmclk_hw);
	पूर्णांक ret;

	ret = twl6040_घातer(pdmclk->twl6040, 0);
	अगर (!ret)
		pdmclk->enabled = 0;

पूर्ण

अटल अचिन्हित दीर्घ twl6040_pdmclk_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा twl6040_pdmclk *pdmclk = container_of(hw, काष्ठा twl6040_pdmclk,
						     pdmclk_hw);

	वापस twl6040_get_sysclk(pdmclk->twl6040);
पूर्ण

अटल स्थिर काष्ठा clk_ops twl6040_pdmclk_ops = अणु
	.is_prepared = twl6040_pdmclk_is_prepared,
	.prepare = twl6040_pdmclk_prepare,
	.unprepare = twl6040_pdmclk_unprepare,
	.recalc_rate = twl6040_pdmclk_recalc_rate,
पूर्ण;

अटल स्थिर काष्ठा clk_init_data twl6040_pdmclk_init = अणु
	.name = "pdmclk",
	.ops = &twl6040_pdmclk_ops,
	.flags = CLK_GET_RATE_NOCACHE,
पूर्ण;

अटल पूर्णांक twl6040_pdmclk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl6040 *twl6040 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा twl6040_pdmclk *clkdata;
	पूर्णांक ret;

	clkdata = devm_kzalloc(&pdev->dev, माप(*clkdata), GFP_KERNEL);
	अगर (!clkdata)
		वापस -ENOMEM;

	clkdata->dev = &pdev->dev;
	clkdata->twl6040 = twl6040;

	clkdata->pdmclk_hw.init = &twl6040_pdmclk_init;
	ret = devm_clk_hw_रेजिस्टर(&pdev->dev, &clkdata->pdmclk_hw);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, clkdata);

	वापस devm_of_clk_add_hw_provider(&pdev->dev, of_clk_hw_simple_get,
					   &clkdata->pdmclk_hw);
पूर्ण

अटल काष्ठा platक्रमm_driver twl6040_pdmclk_driver = अणु
	.driver = अणु
		.name = "twl6040-pdmclk",
	पूर्ण,
	.probe = twl6040_pdmclk_probe,
पूर्ण;

module_platक्रमm_driver(twl6040_pdmclk_driver);

MODULE_DESCRIPTION("TWL6040 clock driver for McPDM functional clock");
MODULE_AUTHOR("Peter Ujfalusi <peter.ujfalusi@ti.com>");
MODULE_ALIAS("platform:twl6040-pdmclk");
MODULE_LICENSE("GPL");
