<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Qualcomm PMIC VBUS output regulator driver
//
// Copyright (c) 2020, The Linux Foundation. All rights reserved.

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/regmap.h>

#घोषणा CMD_OTG				0x40
#घोषणा OTG_EN				BIT(0)
#घोषणा OTG_CFG				0x53
#घोषणा OTG_EN_SRC_CFG			BIT(1)

अटल स्थिर काष्ठा regulator_ops qcom_usb_vbus_reg_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
पूर्ण;

अटल काष्ठा regulator_desc qcom_usb_vbus_rdesc = अणु
	.name = "usb_vbus",
	.ops = &qcom_usb_vbus_reg_ops,
	.owner = THIS_MODULE,
	.type = REGULATOR_VOLTAGE,
पूर्ण;

अटल पूर्णांक qcom_usb_vbus_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा regulator_dev *rdev;
	काष्ठा regmap *regmap;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_init_data *init_data;
	पूर्णांक ret;
	u32 base;

	ret = of_property_पढ़ो_u32(dev->of_node, "reg", &base);
	अगर (ret < 0) अणु
		dev_err(dev, "no base address found\n");
		वापस ret;
	पूर्ण

	regmap = dev_get_regmap(dev->parent, शून्य);
	अगर (!regmap) अणु
		dev_err(dev, "Failed to get regmap\n");
		वापस -ENOENT;
	पूर्ण

	init_data = of_get_regulator_init_data(dev, dev->of_node,
					       &qcom_usb_vbus_rdesc);
	अगर (!init_data)
		वापस -ENOMEM;

	qcom_usb_vbus_rdesc.enable_reg = base + CMD_OTG;
	qcom_usb_vbus_rdesc.enable_mask = OTG_EN;
	config.dev = dev;
	config.init_data = init_data;
	config.of_node = dev->of_node;
	config.regmap = regmap;

	rdev = devm_regulator_रेजिस्टर(dev, &qcom_usb_vbus_rdesc, &config);
	अगर (IS_ERR(rdev)) अणु
		ret = PTR_ERR(rdev);
		dev_err(dev, "not able to register vbus reg %d\n", ret);
		वापस ret;
	पूर्ण

	/* Disable HW logic क्रम VBUS enable */
	regmap_update_bits(regmap, base + OTG_CFG, OTG_EN_SRC_CFG, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id qcom_usb_vbus_regulator_match[] = अणु
	अणु .compatible = "qcom,pm8150b-vbus-reg" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_usb_vbus_regulator_match);

अटल काष्ठा platक्रमm_driver qcom_usb_vbus_regulator_driver = अणु
	.driver		= अणु
		.name	= "qcom-usb-vbus-regulator",
		.of_match_table = qcom_usb_vbus_regulator_match,
	पूर्ण,
	.probe		= qcom_usb_vbus_regulator_probe,
पूर्ण;
module_platक्रमm_driver(qcom_usb_vbus_regulator_driver);

MODULE_DESCRIPTION("Qualcomm USB vbus regulator driver");
MODULE_LICENSE("GPL v2");
