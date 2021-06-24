<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Qualcomm APCS घड़ी controller driver
 *
 * Copyright (c) 2017, Linaro Limited
 * Author: Georgi Djakov <georgi.djakov@linaro.org>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश "clk-regmap.h"
#समावेश "clk-regmap-mux-div.h"

अटल स्थिर u32 gpll0_a53cc_map[] = अणु 4, 5 पूर्ण;

अटल स्थिर काष्ठा clk_parent_data pdata[] = अणु
	अणु .fw_name = "aux", .name = "gpll0_vote", पूर्ण,
	अणु .fw_name = "pll", .name = "a53pll", पूर्ण,
पूर्ण;

/*
 * We use the notअगरier function क्रम चयनing to a temporary safe configuration
 * (mux and भागider), जबतक the A53 PLL is reconfigured.
 */
अटल पूर्णांक a53cc_notअगरier_cb(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			     व्योम *data)
अणु
	पूर्णांक ret = 0;
	काष्ठा clk_regmap_mux_भाग *md = container_of(nb,
						     काष्ठा clk_regmap_mux_भाग,
						     clk_nb);
	अगर (event == PRE_RATE_CHANGE)
		/* set the mux and भागider to safe frequency (400mhz) */
		ret = mux_भाग_set_src_भाग(md, 4, 3);

	वापस notअगरier_from_त्रुटि_सं(ret);
पूर्ण

अटल पूर्णांक qcom_apcs_msm8916_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device *parent = dev->parent;
	काष्ठा clk_regmap_mux_भाग *a53cc;
	काष्ठा regmap *regmap;
	काष्ठा clk_init_data init = अणु पूर्ण;
	पूर्णांक ret = -ENODEV;

	regmap = dev_get_regmap(parent, शून्य);
	अगर (!regmap) अणु
		dev_err(dev, "failed to get regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	a53cc = devm_kzalloc(dev, माप(*a53cc), GFP_KERNEL);
	अगर (!a53cc)
		वापस -ENOMEM;

	init.name = "a53mux";
	init.parent_data = pdata;
	init.num_parents = ARRAY_SIZE(pdata);
	init.ops = &clk_regmap_mux_भाग_ops;
	init.flags = CLK_SET_RATE_PARENT;

	a53cc->clkr.hw.init = &init;
	a53cc->clkr.regmap = regmap;
	a53cc->reg_offset = 0x50;
	a53cc->hid_width = 5;
	a53cc->hid_shअगरt = 0;
	a53cc->src_width = 3;
	a53cc->src_shअगरt = 8;
	a53cc->parent_map = gpll0_a53cc_map;

	a53cc->pclk = devm_clk_get(parent, शून्य);
	अगर (IS_ERR(a53cc->pclk)) अणु
		ret = PTR_ERR(a53cc->pclk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get clk: %d\n", ret);
		वापस ret;
	पूर्ण

	a53cc->clk_nb.notअगरier_call = a53cc_notअगरier_cb;
	ret = clk_notअगरier_रेजिस्टर(a53cc->pclk, &a53cc->clk_nb);
	अगर (ret) अणु
		dev_err(dev, "failed to register clock notifier: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_clk_रेजिस्टर_regmap(dev, &a53cc->clkr);
	अगर (ret) अणु
		dev_err(dev, "failed to register regmap clock: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get,
					  &a53cc->clkr.hw);
	अगर (ret) अणु
		dev_err(dev, "failed to add clock provider: %d\n", ret);
		जाओ err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, a53cc);

	वापस 0;

err:
	clk_notअगरier_unरेजिस्टर(a53cc->pclk, &a53cc->clk_nb);
	वापस ret;
पूर्ण

अटल पूर्णांक qcom_apcs_msm8916_clk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_regmap_mux_भाग *a53cc = platक्रमm_get_drvdata(pdev);

	clk_notअगरier_unरेजिस्टर(a53cc->pclk, &a53cc->clk_nb);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver qcom_apcs_msm8916_clk_driver = अणु
	.probe = qcom_apcs_msm8916_clk_probe,
	.हटाओ = qcom_apcs_msm8916_clk_हटाओ,
	.driver = अणु
		.name = "qcom-apcs-msm8916-clk",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qcom_apcs_msm8916_clk_driver);

MODULE_AUTHOR("Georgi Djakov <georgi.djakov@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Qualcomm MSM8916 APCS clock driver");
