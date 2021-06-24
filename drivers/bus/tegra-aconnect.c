<शैली गुरु>
/*
 * Tegra ACONNECT Bus Driver
 *
 * Copyright (C) 2016, NVIDIA CORPORATION.  All rights reserved.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

काष्ठा tegra_aconnect अणु
	काष्ठा clk	*ape_clk;
	काष्ठा clk	*apb2ape_clk;
पूर्ण;

अटल पूर्णांक tegra_aconnect_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_aconnect *aconnect;

	अगर (!pdev->dev.of_node)
		वापस -EINVAL;

	aconnect = devm_kzalloc(&pdev->dev, माप(काष्ठा tegra_aconnect),
				GFP_KERNEL);
	अगर (!aconnect)
		वापस -ENOMEM;

	aconnect->ape_clk = devm_clk_get(&pdev->dev, "ape");
	अगर (IS_ERR(aconnect->ape_clk)) अणु
		dev_err(&pdev->dev, "Can't retrieve ape clock\n");
		वापस PTR_ERR(aconnect->ape_clk);
	पूर्ण

	aconnect->apb2ape_clk = devm_clk_get(&pdev->dev, "apb2ape");
	अगर (IS_ERR(aconnect->apb2ape_clk)) अणु
		dev_err(&pdev->dev, "Can't retrieve apb2ape clock\n");
		वापस PTR_ERR(aconnect->apb2ape_clk);
	पूर्ण

	dev_set_drvdata(&pdev->dev, aconnect);
	pm_runसमय_enable(&pdev->dev);

	of_platक्रमm_populate(pdev->dev.of_node, शून्य, शून्य, &pdev->dev);

	dev_info(&pdev->dev, "Tegra ACONNECT bus registered\n");

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_aconnect_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_aconnect_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tegra_aconnect *aconnect = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(aconnect->ape_clk);
	अगर (ret) अणु
		dev_err(dev, "ape clk_enable failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(aconnect->apb2ape_clk);
	अगर (ret) अणु
		clk_disable_unprepare(aconnect->ape_clk);
		dev_err(dev, "apb2ape clk_enable failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra_aconnect_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tegra_aconnect *aconnect = dev_get_drvdata(dev);

	clk_disable_unprepare(aconnect->ape_clk);
	clk_disable_unprepare(aconnect->apb2ape_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra_aconnect_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra_aconnect_runसमय_suspend,
			   tegra_aconnect_runसमय_resume, शून्य)
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				      pm_runसमय_क्रमce_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra_aconnect_of_match[] = अणु
	अणु .compatible = "nvidia,tegra210-aconnect", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tegra_aconnect_of_match);

अटल काष्ठा platक्रमm_driver tegra_aconnect_driver = अणु
	.probe = tegra_aconnect_probe,
	.हटाओ = tegra_aconnect_हटाओ,
	.driver = अणु
		.name = "tegra-aconnect",
		.of_match_table = tegra_aconnect_of_match,
		.pm = &tegra_aconnect_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(tegra_aconnect_driver);

MODULE_DESCRIPTION("NVIDIA Tegra ACONNECT Bus Driver");
MODULE_AUTHOR("Jon Hunter <jonathanh@nvidia.com>");
MODULE_LICENSE("GPL v2");
