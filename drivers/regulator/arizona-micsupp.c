<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// arizona-micsupp.c  --  Microphone supply क्रम Arizona devices
//
// Copyright 2012 Wolfson Microelectronics PLC.
//
// Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <sound/soc.h>

#समावेश <linux/mfd/arizona/core.h>
#समावेश <linux/mfd/arizona/pdata.h>
#समावेश <linux/mfd/arizona/रेजिस्टरs.h>

#समावेश <linux/mfd/madera/core.h>
#समावेश <linux/mfd/madera/pdata.h>
#समावेश <linux/mfd/madera/रेजिस्टरs.h>

#समावेश <linux/regulator/arizona-micsupp.h>

काष्ठा arizona_micsupp अणु
	काष्ठा regulator_dev *regulator;
	काष्ठा regmap *regmap;
	काष्ठा snd_soc_dapm_context **dapm;
	अचिन्हित पूर्णांक enable_reg;
	काष्ठा device *dev;

	काष्ठा regulator_consumer_supply supply;
	काष्ठा regulator_init_data init_data;

	काष्ठा work_काष्ठा check_cp_work;
पूर्ण;

अटल व्योम arizona_micsupp_check_cp(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा arizona_micsupp *micsupp =
		container_of(work, काष्ठा arizona_micsupp, check_cp_work);
	काष्ठा snd_soc_dapm_context *dapm = *micsupp->dapm;
	काष्ठा snd_soc_component *component;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(micsupp->regmap, micsupp->enable_reg, &val);
	अगर (ret != 0) अणु
		dev_err(micsupp->dev,
			"Failed to read CP state: %d\n", ret);
		वापस;
	पूर्ण

	अगर (dapm) अणु
		component = snd_soc_dapm_to_component(dapm);

		अगर ((val & (ARIZONA_CPMIC_ENA | ARIZONA_CPMIC_BYPASS)) ==
		    ARIZONA_CPMIC_ENA)
			snd_soc_component_क्रमce_enable_pin(component,
							   "MICSUPP");
		अन्यथा
			snd_soc_component_disable_pin(component, "MICSUPP");

		snd_soc_dapm_sync(dapm);
	पूर्ण
पूर्ण

अटल पूर्णांक arizona_micsupp_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा arizona_micsupp *micsupp = rdev_get_drvdata(rdev);
	पूर्णांक ret;

	ret = regulator_enable_regmap(rdev);

	अगर (ret == 0)
		schedule_work(&micsupp->check_cp_work);

	वापस ret;
पूर्ण

अटल पूर्णांक arizona_micsupp_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा arizona_micsupp *micsupp = rdev_get_drvdata(rdev);
	पूर्णांक ret;

	ret = regulator_disable_regmap(rdev);
	अगर (ret == 0)
		schedule_work(&micsupp->check_cp_work);

	वापस ret;
पूर्ण

अटल पूर्णांक arizona_micsupp_set_bypass(काष्ठा regulator_dev *rdev, bool ena)
अणु
	काष्ठा arizona_micsupp *micsupp = rdev_get_drvdata(rdev);
	पूर्णांक ret;

	ret = regulator_set_bypass_regmap(rdev, ena);
	अगर (ret == 0)
		schedule_work(&micsupp->check_cp_work);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regulator_ops arizona_micsupp_ops = अणु
	.enable = arizona_micsupp_enable,
	.disable = arizona_micsupp_disable,
	.is_enabled = regulator_is_enabled_regmap,

	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,

	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,

	.get_bypass = regulator_get_bypass_regmap,
	.set_bypass = arizona_micsupp_set_bypass,
पूर्ण;

अटल स्थिर काष्ठा linear_range arizona_micsupp_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(1700000, 0,    0x1e, 50000),
	REGULATOR_LINEAR_RANGE(3300000, 0x1f, 0x1f, 0),
पूर्ण;

अटल स्थिर काष्ठा regulator_desc arizona_micsupp = अणु
	.name = "MICVDD",
	.supply_name = "CPVDD",
	.type = REGULATOR_VOLTAGE,
	.n_voltages = 32,
	.ops = &arizona_micsupp_ops,

	.vsel_reg = ARIZONA_LDO2_CONTROL_1,
	.vsel_mask = ARIZONA_LDO2_VSEL_MASK,
	.enable_reg = ARIZONA_MIC_CHARGE_PUMP_1,
	.enable_mask = ARIZONA_CPMIC_ENA,
	.bypass_reg = ARIZONA_MIC_CHARGE_PUMP_1,
	.bypass_mask = ARIZONA_CPMIC_BYPASS,

	.linear_ranges = arizona_micsupp_ranges,
	.n_linear_ranges = ARRAY_SIZE(arizona_micsupp_ranges),

	.enable_समय = 3000,

	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा linear_range arizona_micsupp_ext_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(900000,  0,    0x14, 25000),
	REGULATOR_LINEAR_RANGE(1500000, 0x15, 0x27, 100000),
पूर्ण;

अटल स्थिर काष्ठा regulator_desc arizona_micsupp_ext = अणु
	.name = "MICVDD",
	.supply_name = "CPVDD",
	.type = REGULATOR_VOLTAGE,
	.n_voltages = 40,
	.ops = &arizona_micsupp_ops,

	.vsel_reg = ARIZONA_LDO2_CONTROL_1,
	.vsel_mask = ARIZONA_LDO2_VSEL_MASK,
	.enable_reg = ARIZONA_MIC_CHARGE_PUMP_1,
	.enable_mask = ARIZONA_CPMIC_ENA,
	.bypass_reg = ARIZONA_MIC_CHARGE_PUMP_1,
	.bypass_mask = ARIZONA_CPMIC_BYPASS,

	.linear_ranges = arizona_micsupp_ext_ranges,
	.n_linear_ranges = ARRAY_SIZE(arizona_micsupp_ext_ranges),

	.enable_समय = 3000,

	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा regulator_init_data arizona_micsupp_शेष = अणु
	.स्थिरraपूर्णांकs = अणु
		.valid_ops_mask = REGULATOR_CHANGE_STATUS |
				REGULATOR_CHANGE_VOLTAGE |
				REGULATOR_CHANGE_BYPASS,
		.min_uV = 1700000,
		.max_uV = 3300000,
	पूर्ण,

	.num_consumer_supplies = 1,
पूर्ण;

अटल स्थिर काष्ठा regulator_init_data arizona_micsupp_ext_शेष = अणु
	.स्थिरraपूर्णांकs = अणु
		.valid_ops_mask = REGULATOR_CHANGE_STATUS |
				REGULATOR_CHANGE_VOLTAGE |
				REGULATOR_CHANGE_BYPASS,
		.min_uV = 900000,
		.max_uV = 3300000,
	पूर्ण,

	.num_consumer_supplies = 1,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc madera_micsupp = अणु
	.name = "MICVDD",
	.supply_name = "CPVDD1",
	.type = REGULATOR_VOLTAGE,
	.n_voltages = 40,
	.ops = &arizona_micsupp_ops,

	.vsel_reg = MADERA_LDO2_CONTROL_1,
	.vsel_mask = MADERA_LDO2_VSEL_MASK,
	.enable_reg = MADERA_MIC_CHARGE_PUMP_1,
	.enable_mask = MADERA_CPMIC_ENA,
	.bypass_reg = MADERA_MIC_CHARGE_PUMP_1,
	.bypass_mask = MADERA_CPMIC_BYPASS,

	.linear_ranges = arizona_micsupp_ext_ranges,
	.n_linear_ranges = ARRAY_SIZE(arizona_micsupp_ext_ranges),

	.enable_समय = 3000,

	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक arizona_micsupp_of_get_pdata(काष्ठा arizona_micsupp_pdata *pdata,
					काष्ठा regulator_config *config,
					स्थिर काष्ठा regulator_desc *desc)
अणु
	काष्ठा arizona_micsupp *micsupp = config->driver_data;
	काष्ठा device_node *np;
	काष्ठा regulator_init_data *init_data;

	np = of_get_child_by_name(config->dev->of_node, "micvdd");

	अगर (np) अणु
		config->of_node = np;

		init_data = of_get_regulator_init_data(config->dev, np, desc);

		अगर (init_data) अणु
			init_data->consumer_supplies = &micsupp->supply;
			init_data->num_consumer_supplies = 1;

			pdata->init_data = init_data;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक arizona_micsupp_common_init(काष्ठा platक्रमm_device *pdev,
				       काष्ठा arizona_micsupp *micsupp,
				       स्थिर काष्ठा regulator_desc *desc,
				       काष्ठा arizona_micsupp_pdata *pdata)
अणु
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक ret;

	INIT_WORK(&micsupp->check_cp_work, arizona_micsupp_check_cp);

	micsupp->init_data.consumer_supplies = &micsupp->supply;
	micsupp->supply.supply = "MICVDD";
	micsupp->supply.dev_name = dev_name(micsupp->dev);
	micsupp->enable_reg = desc->enable_reg;

	config.dev = micsupp->dev;
	config.driver_data = micsupp;
	config.regmap = micsupp->regmap;

	अगर (IS_ENABLED(CONFIG_OF)) अणु
		अगर (!dev_get_platdata(micsupp->dev)) अणु
			ret = arizona_micsupp_of_get_pdata(pdata, &config,
							   desc);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	अगर (pdata->init_data)
		config.init_data = pdata->init_data;
	अन्यथा
		config.init_data = &micsupp->init_data;

	/* Default to regulated mode */
	regmap_update_bits(micsupp->regmap, micsupp->enable_reg,
			   ARIZONA_CPMIC_BYPASS, 0);

	micsupp->regulator = devm_regulator_रेजिस्टर(&pdev->dev,
						     desc,
						     &config);

	of_node_put(config.of_node);

	अगर (IS_ERR(micsupp->regulator)) अणु
		ret = PTR_ERR(micsupp->regulator);
		dev_err(micsupp->dev, "Failed to register mic supply: %d\n",
			ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, micsupp);

	वापस 0;
पूर्ण

अटल पूर्णांक arizona_micsupp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arizona *arizona = dev_get_drvdata(pdev->dev.parent);
	स्थिर काष्ठा regulator_desc *desc;
	काष्ठा arizona_micsupp *micsupp;

	micsupp = devm_kzalloc(&pdev->dev, माप(*micsupp), GFP_KERNEL);
	अगर (!micsupp)
		वापस -ENOMEM;

	micsupp->regmap = arizona->regmap;
	micsupp->dapm = &arizona->dapm;
	micsupp->dev = arizona->dev;

	/*
	 * Since the chip usually supplies itself we provide some
	 * शेष init_data क्रम it.  This will be overridden with
	 * platक्रमm data अगर provided.
	 */
	चयन (arizona->type) अणु
	हाल WM5110:
	हाल WM8280:
		desc = &arizona_micsupp_ext;
		micsupp->init_data = arizona_micsupp_ext_शेष;
		अवरोध;
	शेष:
		desc = &arizona_micsupp;
		micsupp->init_data = arizona_micsupp_शेष;
		अवरोध;
	पूर्ण

	वापस arizona_micsupp_common_init(pdev, micsupp, desc,
					   &arizona->pdata.micvdd);
पूर्ण

अटल पूर्णांक madera_micsupp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा madera *madera = dev_get_drvdata(pdev->dev.parent);
	काष्ठा arizona_micsupp *micsupp;

	micsupp = devm_kzalloc(&pdev->dev, माप(*micsupp), GFP_KERNEL);
	अगर (!micsupp)
		वापस -ENOMEM;

	micsupp->regmap = madera->regmap;
	micsupp->dapm = &madera->dapm;
	micsupp->dev = madera->dev;
	micsupp->init_data = arizona_micsupp_ext_शेष;

	वापस arizona_micsupp_common_init(pdev, micsupp, &madera_micsupp,
					   &madera->pdata.micvdd);
पूर्ण

अटल काष्ठा platक्रमm_driver arizona_micsupp_driver = अणु
	.probe = arizona_micsupp_probe,
	.driver		= अणु
		.name	= "arizona-micsupp",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver madera_micsupp_driver = अणु
	.probe = madera_micsupp_probe,
	.driver		= अणु
		.name	= "madera-micsupp",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर arizona_micsupp_drivers[] = अणु
	&arizona_micsupp_driver,
	&madera_micsupp_driver,
पूर्ण;

अटल पूर्णांक __init arizona_micsupp_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(arizona_micsupp_drivers,
					 ARRAY_SIZE(arizona_micsupp_drivers));
पूर्ण
module_init(arizona_micsupp_init);

अटल व्योम __निकास arizona_micsupp_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(arizona_micsupp_drivers,
				    ARRAY_SIZE(arizona_micsupp_drivers));
पूर्ण
module_निकास(arizona_micsupp_निकास);

/* Module inक्रमmation */
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("Arizona microphone supply driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:arizona-micsupp");
MODULE_ALIAS("platform:madera-micsupp");
