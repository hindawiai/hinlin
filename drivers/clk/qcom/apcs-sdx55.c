<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Qualcomm SDX55 APCS घड़ी controller driver
 *
 * Copyright (c) 2020, Linaro Limited
 * Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/cpu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश "clk-regmap.h"
#समावेश "clk-regmap-mux-div.h"

अटल स्थिर u32 apcs_mux_clk_parent_map[] = अणु 0, 1, 5 पूर्ण;

अटल स्थिर काष्ठा clk_parent_data pdata[] = अणु
	अणु .fw_name = "ref" पूर्ण,
	अणु .fw_name = "aux" पूर्ण,
	अणु .fw_name = "pll" पूर्ण,
पूर्ण;

/*
 * We use the notअगरier function क्रम चयनing to a temporary safe configuration
 * (mux and भागider), जबतक the A7 PLL is reconfigured.
 */
अटल पूर्णांक a7cc_notअगरier_cb(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			    व्योम *data)
अणु
	पूर्णांक ret = 0;
	काष्ठा clk_regmap_mux_भाग *md = container_of(nb,
						     काष्ठा clk_regmap_mux_भाग,
						     clk_nb);
	अगर (event == PRE_RATE_CHANGE)
		/* set the mux and भागider to safe frequency (400mhz) */
		ret = mux_भाग_set_src_भाग(md, 1, 2);

	वापस notअगरier_from_त्रुटि_सं(ret);
पूर्ण

अटल पूर्णांक qcom_apcs_sdx55_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device *parent = dev->parent;
	काष्ठा device *cpu_dev;
	काष्ठा clk_regmap_mux_भाग *a7cc;
	काष्ठा regmap *regmap;
	काष्ठा clk_init_data init = अणु पूर्ण;
	पूर्णांक ret;

	regmap = dev_get_regmap(parent, शून्य);
	अगर (!regmap) अणु
		dev_err_probe(dev, -ENODEV, "Failed to get parent regmap\n");
		वापस -ENODEV;
	पूर्ण

	a7cc = devm_kzalloc(dev, माप(*a7cc), GFP_KERNEL);
	अगर (!a7cc)
		वापस -ENOMEM;

	init.name = "a7mux";
	init.parent_data = pdata;
	init.num_parents = ARRAY_SIZE(pdata);
	init.ops = &clk_regmap_mux_भाग_ops;

	a7cc->clkr.hw.init = &init;
	a7cc->clkr.regmap = regmap;
	a7cc->reg_offset = 0x8;
	a7cc->hid_width = 5;
	a7cc->hid_shअगरt = 0;
	a7cc->src_width = 3;
	a7cc->src_shअगरt = 8;
	a7cc->parent_map = apcs_mux_clk_parent_map;

	a7cc->pclk = devm_clk_get(parent, "pll");
	अगर (IS_ERR(a7cc->pclk)) अणु
		ret = PTR_ERR(a7cc->pclk);
		अगर (ret != -EPROBE_DEFER)
			dev_err_probe(dev, ret, "Failed to get PLL clk\n");
		वापस ret;
	पूर्ण

	a7cc->clk_nb.notअगरier_call = a7cc_notअगरier_cb;
	ret = clk_notअगरier_रेजिस्टर(a7cc->pclk, &a7cc->clk_nb);
	अगर (ret) अणु
		dev_err_probe(dev, ret, "Failed to register clock notifier\n");
		वापस ret;
	पूर्ण

	ret = devm_clk_रेजिस्टर_regmap(dev, &a7cc->clkr);
	अगर (ret) अणु
		dev_err_probe(dev, ret, "Failed to register regmap clock\n");
		जाओ err;
	पूर्ण

	ret = devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get,
					  &a7cc->clkr.hw);
	अगर (ret) अणु
		dev_err_probe(dev, ret, "Failed to add clock provider\n");
		जाओ err;
	पूर्ण

	platक्रमm_set_drvdata(pdev, a7cc);

	/*
	 * Attach the घातer करोमुख्य to cpudev. Since there is no dedicated driver
	 * क्रम CPUs and the SDX55 platक्रमm lacks hardware specअगरic CPUFreq
	 * driver, there seems to be no better place to करो this. So करो it here!
	 */
	cpu_dev = get_cpu_device(0);
	dev_pm_करोमुख्य_attach(cpu_dev, true);

	वापस 0;

err:
	clk_notअगरier_unरेजिस्टर(a7cc->pclk, &a7cc->clk_nb);
	वापस ret;
पूर्ण

अटल पूर्णांक qcom_apcs_sdx55_clk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *cpu_dev = get_cpu_device(0);
	काष्ठा clk_regmap_mux_भाग *a7cc = platक्रमm_get_drvdata(pdev);

	clk_notअगरier_unरेजिस्टर(a7cc->pclk, &a7cc->clk_nb);
	dev_pm_करोमुख्य_detach(cpu_dev, true);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver qcom_apcs_sdx55_clk_driver = अणु
	.probe = qcom_apcs_sdx55_clk_probe,
	.हटाओ = qcom_apcs_sdx55_clk_हटाओ,
	.driver = अणु
		.name = "qcom-sdx55-acps-clk",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qcom_apcs_sdx55_clk_driver);

MODULE_AUTHOR("Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Qualcomm SDX55 APCS clock driver");
