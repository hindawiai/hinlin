<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2012 ARM Limited

#घोषणा DRVNAME "vexpress-regulator"
#घोषणा pr_fmt(fmt) DRVNAME ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/vexpress.h>

अटल पूर्णांक vexpress_regulator_get_voltage(काष्ठा regulator_dev *regdev)
अणु
	अचिन्हित पूर्णांक uV;
	पूर्णांक err = regmap_पढ़ो(regdev->regmap, 0, &uV);

	वापस err ? err : uV;
पूर्ण

अटल पूर्णांक vexpress_regulator_set_voltage(काष्ठा regulator_dev *regdev,
		पूर्णांक min_uV, पूर्णांक max_uV, अचिन्हित *selector)
अणु
	वापस regmap_ग_लिखो(regdev->regmap, 0, min_uV);
पूर्ण

अटल स्थिर काष्ठा regulator_ops vexpress_regulator_ops_ro = अणु
	.get_voltage = vexpress_regulator_get_voltage,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops vexpress_regulator_ops = अणु
	.get_voltage = vexpress_regulator_get_voltage,
	.set_voltage = vexpress_regulator_set_voltage,
पूर्ण;

अटल पूर्णांक vexpress_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regulator_desc *desc;
	काष्ठा regulator_init_data *init_data;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	काष्ठा regmap *regmap;

	desc = devm_kzalloc(&pdev->dev, माप(*desc), GFP_KERNEL);
	अगर (!desc)
		वापस -ENOMEM;

	regmap = devm_regmap_init_vexpress_config(&pdev->dev);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	desc->name = dev_name(&pdev->dev);
	desc->type = REGULATOR_VOLTAGE;
	desc->owner = THIS_MODULE;
	desc->continuous_voltage_range = true;

	init_data = of_get_regulator_init_data(&pdev->dev, pdev->dev.of_node,
					       desc);
	अगर (!init_data)
		वापस -EINVAL;

	init_data->स्थिरraपूर्णांकs.apply_uV = 0;
	अगर (init_data->स्थिरraपूर्णांकs.min_uV && init_data->स्थिरraपूर्णांकs.max_uV)
		desc->ops = &vexpress_regulator_ops;
	अन्यथा
		desc->ops = &vexpress_regulator_ops_ro;

	config.regmap = regmap;
	config.dev = &pdev->dev;
	config.init_data = init_data;
	config.of_node = pdev->dev.of_node;

	rdev = devm_regulator_रेजिस्टर(&pdev->dev, desc, &config);
	वापस PTR_ERR_OR_ZERO(rdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id vexpress_regulator_of_match[] = अणु
	अणु .compatible = "arm,vexpress-volt", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, vexpress_regulator_of_match);

अटल काष्ठा platक्रमm_driver vexpress_regulator_driver = अणु
	.probe = vexpress_regulator_probe,
	.driver	= अणु
		.name = DRVNAME,
		.of_match_table = vexpress_regulator_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(vexpress_regulator_driver);

MODULE_AUTHOR("Pawel Moll <pawel.moll@arm.com>");
MODULE_DESCRIPTION("Versatile Express regulator");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:vexpress-regulator");
