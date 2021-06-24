<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset-controller.h>

#समावेश <dt-bindings/reset/qcom,sdm845-pdc.h>

#घोषणा RPMH_PDC_SYNC_RESET	0x100

काष्ठा qcom_pdc_reset_map अणु
	u8 bit;
पूर्ण;

काष्ठा qcom_pdc_reset_data अणु
	काष्ठा reset_controller_dev rcdev;
	काष्ठा regmap *regmap;
पूर्ण;

अटल स्थिर काष्ठा regmap_config sdm845_pdc_regmap_config = अणु
	.name		= "pdc-reset",
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= 0x20000,
	.fast_io	= true,
पूर्ण;

अटल स्थिर काष्ठा qcom_pdc_reset_map sdm845_pdc_resets[] = अणु
	[PDC_APPS_SYNC_RESET] = अणु0पूर्ण,
	[PDC_SP_SYNC_RESET] = अणु1पूर्ण,
	[PDC_AUDIO_SYNC_RESET] = अणु2पूर्ण,
	[PDC_SENSORS_SYNC_RESET] = अणु3पूर्ण,
	[PDC_AOP_SYNC_RESET] = अणु4पूर्ण,
	[PDC_DEBUG_SYNC_RESET] = अणु5पूर्ण,
	[PDC_GPU_SYNC_RESET] = अणु6पूर्ण,
	[PDC_DISPLAY_SYNC_RESET] = अणु7पूर्ण,
	[PDC_COMPUTE_SYNC_RESET] = अणु8पूर्ण,
	[PDC_MODEM_SYNC_RESET] = अणु9पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा qcom_pdc_reset_data *to_qcom_pdc_reset_data(
				काष्ठा reset_controller_dev *rcdev)
अणु
	वापस container_of(rcdev, काष्ठा qcom_pdc_reset_data, rcdev);
पूर्ण

अटल पूर्णांक qcom_pdc_control_निश्चित(काष्ठा reset_controller_dev *rcdev,
					अचिन्हित दीर्घ idx)
अणु
	काष्ठा qcom_pdc_reset_data *data = to_qcom_pdc_reset_data(rcdev);

	वापस regmap_update_bits(data->regmap, RPMH_PDC_SYNC_RESET,
				  BIT(sdm845_pdc_resets[idx].bit),
				  BIT(sdm845_pdc_resets[idx].bit));
पूर्ण

अटल पूर्णांक qcom_pdc_control_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
					अचिन्हित दीर्घ idx)
अणु
	काष्ठा qcom_pdc_reset_data *data = to_qcom_pdc_reset_data(rcdev);

	वापस regmap_update_bits(data->regmap, RPMH_PDC_SYNC_RESET,
				  BIT(sdm845_pdc_resets[idx].bit), 0);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops qcom_pdc_reset_ops = अणु
	.निश्चित = qcom_pdc_control_निश्चित,
	.deनिश्चित = qcom_pdc_control_deनिश्चित,
पूर्ण;

अटल पूर्णांक qcom_pdc_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qcom_pdc_reset_data *data;
	काष्ठा device *dev = &pdev->dev;
	व्योम __iomem *base;
	काष्ठा resource *res;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	data->regmap = devm_regmap_init_mmio(dev, base,
					     &sdm845_pdc_regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		dev_err(dev, "Unable to initialize regmap\n");
		वापस PTR_ERR(data->regmap);
	पूर्ण

	data->rcdev.owner = THIS_MODULE;
	data->rcdev.ops = &qcom_pdc_reset_ops;
	data->rcdev.nr_resets = ARRAY_SIZE(sdm845_pdc_resets);
	data->rcdev.of_node = dev->of_node;

	वापस devm_reset_controller_रेजिस्टर(dev, &data->rcdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_pdc_reset_of_match[] = अणु
	अणु .compatible = "qcom,sdm845-pdc-global" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_pdc_reset_of_match);

अटल काष्ठा platक्रमm_driver qcom_pdc_reset_driver = अणु
	.probe = qcom_pdc_reset_probe,
	.driver = अणु
		.name = "qcom_pdc_reset",
		.of_match_table = qcom_pdc_reset_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qcom_pdc_reset_driver);

MODULE_DESCRIPTION("Qualcomm PDC Reset Driver");
MODULE_LICENSE("GPL v2");
