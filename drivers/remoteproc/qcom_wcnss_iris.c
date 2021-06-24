<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Qualcomm Wireless Connectivity Subप्रणाली Iris driver
 *
 * Copyright (C) 2016 Linaro Ltd
 * Copyright (C) 2014 Sony Mobile Communications AB
 * Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "qcom_wcnss.h"

काष्ठा qcom_iris अणु
	काष्ठा device *dev;

	काष्ठा clk *xo_clk;

	काष्ठा regulator_bulk_data *vregs;
	माप_प्रकार num_vregs;
पूर्ण;

काष्ठा iris_data अणु
	स्थिर काष्ठा wcnss_vreg_info *vregs;
	माप_प्रकार num_vregs;

	bool use_48mhz_xo;
पूर्ण;

अटल स्थिर काष्ठा iris_data wcn3620_data = अणु
	.vregs = (काष्ठा wcnss_vreg_info[]) अणु
		अणु "vddxo",  1800000, 1800000, 10000 पूर्ण,
		अणु "vddrfa", 1300000, 1300000, 100000 पूर्ण,
		अणु "vddpa",  3300000, 3300000, 515000 पूर्ण,
		अणु "vdddig", 1800000, 1800000, 10000 पूर्ण,
	पूर्ण,
	.num_vregs = 4,
	.use_48mhz_xo = false,
पूर्ण;

अटल स्थिर काष्ठा iris_data wcn3660_data = अणु
	.vregs = (काष्ठा wcnss_vreg_info[]) अणु
		अणु "vddxo",  1800000, 1800000, 10000 पूर्ण,
		अणु "vddrfa", 1300000, 1300000, 100000 पूर्ण,
		अणु "vddpa",  2900000, 3000000, 515000 पूर्ण,
		अणु "vdddig", 1200000, 1225000, 10000 पूर्ण,
	पूर्ण,
	.num_vregs = 4,
	.use_48mhz_xo = true,
पूर्ण;

अटल स्थिर काष्ठा iris_data wcn3680_data = अणु
	.vregs = (काष्ठा wcnss_vreg_info[]) अणु
		अणु "vddxo",  1800000, 1800000, 10000 पूर्ण,
		अणु "vddrfa", 1300000, 1300000, 100000 पूर्ण,
		अणु "vddpa",  3300000, 3300000, 515000 पूर्ण,
		अणु "vdddig", 1800000, 1800000, 10000 पूर्ण,
	पूर्ण,
	.num_vregs = 4,
	.use_48mhz_xo = true,
पूर्ण;

पूर्णांक qcom_iris_enable(काष्ठा qcom_iris *iris)
अणु
	पूर्णांक ret;

	ret = regulator_bulk_enable(iris->num_vregs, iris->vregs);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(iris->xo_clk);
	अगर (ret) अणु
		dev_err(iris->dev, "failed to enable xo clk\n");
		जाओ disable_regulators;
	पूर्ण

	वापस 0;

disable_regulators:
	regulator_bulk_disable(iris->num_vregs, iris->vregs);

	वापस ret;
पूर्ण

व्योम qcom_iris_disable(काष्ठा qcom_iris *iris)
अणु
	clk_disable_unprepare(iris->xo_clk);
	regulator_bulk_disable(iris->num_vregs, iris->vregs);
पूर्ण

अटल पूर्णांक qcom_iris_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा iris_data *data;
	काष्ठा qcom_wcnss *wcnss;
	काष्ठा qcom_iris *iris;
	पूर्णांक ret;
	पूर्णांक i;

	iris = devm_kzalloc(&pdev->dev, माप(काष्ठा qcom_iris), GFP_KERNEL);
	अगर (!iris)
		वापस -ENOMEM;

	data = of_device_get_match_data(&pdev->dev);
	wcnss = dev_get_drvdata(pdev->dev.parent);

	iris->xo_clk = devm_clk_get(&pdev->dev, "xo");
	अगर (IS_ERR(iris->xo_clk)) अणु
		अगर (PTR_ERR(iris->xo_clk) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "failed to acquire xo clk\n");
		वापस PTR_ERR(iris->xo_clk);
	पूर्ण

	iris->num_vregs = data->num_vregs;
	iris->vregs = devm_kसुस्मृति(&pdev->dev,
				   iris->num_vregs,
				   माप(काष्ठा regulator_bulk_data),
				   GFP_KERNEL);
	अगर (!iris->vregs)
		वापस -ENOMEM;

	क्रम (i = 0; i < iris->num_vregs; i++)
		iris->vregs[i].supply = data->vregs[i].name;

	ret = devm_regulator_bulk_get(&pdev->dev, iris->num_vregs, iris->vregs);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to get regulators\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < iris->num_vregs; i++) अणु
		अगर (data->vregs[i].max_voltage)
			regulator_set_voltage(iris->vregs[i].consumer,
					      data->vregs[i].min_voltage,
					      data->vregs[i].max_voltage);

		अगर (data->vregs[i].load_uA)
			regulator_set_load(iris->vregs[i].consumer,
					   data->vregs[i].load_uA);
	पूर्ण

	qcom_wcnss_assign_iris(wcnss, iris, data->use_48mhz_xo);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_iris_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_wcnss *wcnss = dev_get_drvdata(pdev->dev.parent);

	qcom_wcnss_assign_iris(wcnss, शून्य, false);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id iris_of_match[] = अणु
	अणु .compatible = "qcom,wcn3620", .data = &wcn3620_data पूर्ण,
	अणु .compatible = "qcom,wcn3660", .data = &wcn3660_data पूर्ण,
	अणु .compatible = "qcom,wcn3660b", .data = &wcn3680_data पूर्ण,
	अणु .compatible = "qcom,wcn3680", .data = &wcn3680_data पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, iris_of_match);

काष्ठा platक्रमm_driver qcom_iris_driver = अणु
	.probe = qcom_iris_probe,
	.हटाओ = qcom_iris_हटाओ,
	.driver = अणु
		.name = "qcom-iris",
		.of_match_table = iris_of_match,
	पूर्ण,
पूर्ण;
