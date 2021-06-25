<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_device.h>
#समावेश <dt-bindings/reset/qcom,sdm845-aoss.h>

काष्ठा qcom_aoss_reset_map अणु
	अचिन्हित पूर्णांक reg;
पूर्ण;

काष्ठा qcom_aoss_desc अणु
	स्थिर काष्ठा qcom_aoss_reset_map *resets;
	माप_प्रकार num_resets;
पूर्ण;

काष्ठा qcom_aoss_reset_data अणु
	काष्ठा reset_controller_dev rcdev;
	व्योम __iomem *base;
	स्थिर काष्ठा qcom_aoss_desc *desc;
पूर्ण;

अटल स्थिर काष्ठा qcom_aoss_reset_map sdm845_aoss_resets[] = अणु
	[AOSS_CC_MSS_RESTART] = अणु0x10000पूर्ण,
	[AOSS_CC_CAMSS_RESTART] = अणु0x11000पूर्ण,
	[AOSS_CC_VENUS_RESTART] = अणु0x12000पूर्ण,
	[AOSS_CC_GPU_RESTART] = अणु0x13000पूर्ण,
	[AOSS_CC_DISPSS_RESTART] = अणु0x14000पूर्ण,
	[AOSS_CC_WCSS_RESTART] = अणु0x20000पूर्ण,
	[AOSS_CC_LPASS_RESTART] = अणु0x30000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा qcom_aoss_desc sdm845_aoss_desc = अणु
	.resets = sdm845_aoss_resets,
	.num_resets = ARRAY_SIZE(sdm845_aoss_resets),
पूर्ण;

अटल अंतरभूत काष्ठा qcom_aoss_reset_data *to_qcom_aoss_reset_data(
				काष्ठा reset_controller_dev *rcdev)
अणु
	वापस container_of(rcdev, काष्ठा qcom_aoss_reset_data, rcdev);
पूर्ण

अटल पूर्णांक qcom_aoss_control_निश्चित(काष्ठा reset_controller_dev *rcdev,
				    अचिन्हित दीर्घ idx)
अणु
	काष्ठा qcom_aoss_reset_data *data = to_qcom_aoss_reset_data(rcdev);
	स्थिर काष्ठा qcom_aoss_reset_map *map = &data->desc->resets[idx];

	ग_लिखोl(1, data->base + map->reg);
	/* Wait 6 32kHz sleep cycles क्रम reset */
	usleep_range(200, 300);
	वापस 0;
पूर्ण

अटल पूर्णांक qcom_aoss_control_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				      अचिन्हित दीर्घ idx)
अणु
	काष्ठा qcom_aoss_reset_data *data = to_qcom_aoss_reset_data(rcdev);
	स्थिर काष्ठा qcom_aoss_reset_map *map = &data->desc->resets[idx];

	ग_लिखोl(0, data->base + map->reg);
	/* Wait 6 32kHz sleep cycles क्रम reset */
	usleep_range(200, 300);
	वापस 0;
पूर्ण

अटल पूर्णांक qcom_aoss_control_reset(काष्ठा reset_controller_dev *rcdev,
					अचिन्हित दीर्घ idx)
अणु
	qcom_aoss_control_निश्चित(rcdev, idx);

	वापस qcom_aoss_control_deनिश्चित(rcdev, idx);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops qcom_aoss_reset_ops = अणु
	.reset = qcom_aoss_control_reset,
	.निश्चित = qcom_aoss_control_निश्चित,
	.deनिश्चित = qcom_aoss_control_deनिश्चित,
पूर्ण;

अटल पूर्णांक qcom_aoss_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_aoss_reset_data *data;
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा qcom_aoss_desc *desc;
	काष्ठा resource *res;

	desc = of_device_get_match_data(dev);
	अगर (!desc)
		वापस -EINVAL;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->desc = desc;
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	data->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(data->base))
		वापस PTR_ERR(data->base);

	data->rcdev.owner = THIS_MODULE;
	data->rcdev.ops = &qcom_aoss_reset_ops;
	data->rcdev.nr_resets = desc->num_resets;
	data->rcdev.of_node = dev->of_node;

	वापस devm_reset_controller_रेजिस्टर(dev, &data->rcdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_aoss_reset_of_match[] = अणु
	अणु .compatible = "qcom,sdm845-aoss-cc", .data = &sdm845_aoss_desc पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_aoss_reset_of_match);

अटल काष्ठा platक्रमm_driver qcom_aoss_reset_driver = अणु
	.probe = qcom_aoss_reset_probe,
	.driver  = अणु
		.name = "qcom_aoss_reset",
		.of_match_table = qcom_aoss_reset_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(qcom_aoss_reset_driver);

MODULE_DESCRIPTION("Qualcomm AOSS Reset Driver");
MODULE_LICENSE("GPL v2");
