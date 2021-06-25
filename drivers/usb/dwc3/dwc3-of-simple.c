<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dwc3-of-simple.c - OF glue layer क्रम simple पूर्णांकegrations
 *
 * Copyright (c) 2015 Texas Instruments Incorporated - https://www.ti.com
 *
 * Author: Felipe Balbi <balbi@ti.com>
 *
 * This is a combination of the old dwc3-qcom.c by Ivan T. Ivanov
 * <iivanov@mm-sol.com> and the original patch adding support क्रम Xilinx' SoC
 * by Subbaraya Sundeep Bhatta <subbaraya.sundeep.bhatta@xilinx.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>

काष्ठा dwc3_of_simple अणु
	काष्ठा device		*dev;
	काष्ठा clk_bulk_data	*clks;
	पूर्णांक			num_घड़ीs;
	काष्ठा reset_control	*resets;
	bool			need_reset;
पूर्ण;

अटल पूर्णांक dwc3_of_simple_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dwc3_of_simple	*simple;
	काष्ठा device		*dev = &pdev->dev;
	काष्ठा device_node	*np = dev->of_node;

	पूर्णांक			ret;

	simple = devm_kzalloc(dev, माप(*simple), GFP_KERNEL);
	अगर (!simple)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, simple);
	simple->dev = dev;

	/*
	 * Some controllers need to toggle the usb3-otg reset beक्रमe trying to
	 * initialize the PHY, otherwise the PHY बार out.
	 */
	अगर (of_device_is_compatible(np, "rockchip,rk3399-dwc3"))
		simple->need_reset = true;

	simple->resets = of_reset_control_array_get(np, false, true,
						    true);
	अगर (IS_ERR(simple->resets)) अणु
		ret = PTR_ERR(simple->resets);
		dev_err(dev, "failed to get device resets, err=%d\n", ret);
		वापस ret;
	पूर्ण

	ret = reset_control_deनिश्चित(simple->resets);
	अगर (ret)
		जाओ err_resetc_put;

	ret = clk_bulk_get_all(simple->dev, &simple->clks);
	अगर (ret < 0)
		जाओ err_resetc_निश्चित;

	simple->num_घड़ीs = ret;
	ret = clk_bulk_prepare_enable(simple->num_घड़ीs, simple->clks);
	अगर (ret)
		जाओ err_resetc_निश्चित;

	ret = of_platक्रमm_populate(np, शून्य, शून्य, dev);
	अगर (ret)
		जाओ err_clk_put;

	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);

	वापस 0;

err_clk_put:
	clk_bulk_disable_unprepare(simple->num_घड़ीs, simple->clks);
	clk_bulk_put_all(simple->num_घड़ीs, simple->clks);

err_resetc_निश्चित:
	reset_control_निश्चित(simple->resets);

err_resetc_put:
	reset_control_put(simple->resets);
	वापस ret;
पूर्ण

अटल व्योम __dwc3_of_simple_tearकरोwn(काष्ठा dwc3_of_simple *simple)
अणु
	of_platक्रमm_depopulate(simple->dev);

	clk_bulk_disable_unprepare(simple->num_घड़ीs, simple->clks);
	clk_bulk_put_all(simple->num_घड़ीs, simple->clks);
	simple->num_घड़ीs = 0;

	reset_control_निश्चित(simple->resets);

	reset_control_put(simple->resets);

	pm_runसमय_disable(simple->dev);
	pm_runसमय_put_noidle(simple->dev);
	pm_runसमय_set_suspended(simple->dev);
पूर्ण

अटल पूर्णांक dwc3_of_simple_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dwc3_of_simple	*simple = platक्रमm_get_drvdata(pdev);

	__dwc3_of_simple_tearकरोwn(simple);

	वापस 0;
पूर्ण

अटल व्योम dwc3_of_simple_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dwc3_of_simple	*simple = platक्रमm_get_drvdata(pdev);

	__dwc3_of_simple_tearकरोwn(simple);
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_of_simple_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा dwc3_of_simple	*simple = dev_get_drvdata(dev);

	clk_bulk_disable(simple->num_घड़ीs, simple->clks);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_of_simple_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा dwc3_of_simple	*simple = dev_get_drvdata(dev);

	वापस clk_bulk_enable(simple->num_घड़ीs, simple->clks);
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_of_simple_suspend(काष्ठा device *dev)
अणु
	काष्ठा dwc3_of_simple *simple = dev_get_drvdata(dev);

	अगर (simple->need_reset)
		reset_control_निश्चित(simple->resets);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused dwc3_of_simple_resume(काष्ठा device *dev)
अणु
	काष्ठा dwc3_of_simple *simple = dev_get_drvdata(dev);

	अगर (simple->need_reset)
		reset_control_deनिश्चित(simple->resets);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dwc3_of_simple_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(dwc3_of_simple_suspend, dwc3_of_simple_resume)
	SET_RUNTIME_PM_OPS(dwc3_of_simple_runसमय_suspend,
			dwc3_of_simple_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_dwc3_simple_match[] = अणु
	अणु .compatible = "rockchip,rk3399-dwc3" पूर्ण,
	अणु .compatible = "cavium,octeon-7130-usb-uctl" पूर्ण,
	अणु .compatible = "sprd,sc9860-dwc3" पूर्ण,
	अणु .compatible = "allwinner,sun50i-h6-dwc3" पूर्ण,
	अणु .compatible = "hisilicon,hi3670-dwc3" पूर्ण,
	अणु .compatible = "intel,keembay-dwc3" पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_dwc3_simple_match);

अटल काष्ठा platक्रमm_driver dwc3_of_simple_driver = अणु
	.probe		= dwc3_of_simple_probe,
	.हटाओ		= dwc3_of_simple_हटाओ,
	.shutकरोwn	= dwc3_of_simple_shutकरोwn,
	.driver		= अणु
		.name	= "dwc3-of-simple",
		.of_match_table = of_dwc3_simple_match,
		.pm	= &dwc3_of_simple_dev_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dwc3_of_simple_driver);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("DesignWare USB3 OF Simple Glue Layer");
MODULE_AUTHOR("Felipe Balbi <balbi@ti.com>");
