<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// arizona-lकरो1.c  --  LDO1 supply क्रम Arizona devices
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
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/slab.h>

#समावेश <linux/regulator/arizona-lकरो1.h>

#समावेश <linux/mfd/arizona/core.h>
#समावेश <linux/mfd/arizona/pdata.h>
#समावेश <linux/mfd/arizona/रेजिस्टरs.h>

#समावेश <linux/mfd/madera/core.h>
#समावेश <linux/mfd/madera/pdata.h>
#समावेश <linux/mfd/madera/रेजिस्टरs.h>

काष्ठा arizona_lकरो1 अणु
	काष्ठा regulator_dev *regulator;
	काष्ठा regmap *regmap;

	काष्ठा regulator_consumer_supply supply;
	काष्ठा regulator_init_data init_data;

	काष्ठा gpio_desc *ena_gpiod;
पूर्ण;

अटल पूर्णांक arizona_lकरो1_hc_set_voltage_sel(काष्ठा regulator_dev *rdev,
					   अचिन्हित sel)
अणु
	काष्ठा regmap *regmap = rdev_get_regmap(rdev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (sel == rdev->desc->n_voltages - 1)
		val = ARIZONA_LDO1_HI_PWR;
	अन्यथा
		val = 0;

	ret = regmap_update_bits(regmap, ARIZONA_LDO1_CONTROL_2,
				 ARIZONA_LDO1_HI_PWR, val);
	अगर (ret != 0)
		वापस ret;

	अगर (val)
		वापस 0;

	वापस regulator_set_voltage_sel_regmap(rdev, sel);
पूर्ण

अटल पूर्णांक arizona_lकरो1_hc_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा regmap *regmap = rdev_get_regmap(rdev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, ARIZONA_LDO1_CONTROL_2, &val);
	अगर (ret != 0)
		वापस ret;

	अगर (val & ARIZONA_LDO1_HI_PWR)
		वापस rdev->desc->n_voltages - 1;

	वापस regulator_get_voltage_sel_regmap(rdev);
पूर्ण

अटल स्थिर काष्ठा regulator_ops arizona_lकरो1_hc_ops = अणु
	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,
	.get_voltage_sel = arizona_lकरो1_hc_get_voltage_sel,
	.set_voltage_sel = arizona_lकरो1_hc_set_voltage_sel,
	.get_bypass = regulator_get_bypass_regmap,
	.set_bypass = regulator_set_bypass_regmap,
पूर्ण;

अटल स्थिर काष्ठा linear_range arizona_lकरो1_hc_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(900000, 0, 0x6, 50000),
	REGULATOR_LINEAR_RANGE(1800000, 0x7, 0x7, 0),
पूर्ण;

अटल स्थिर काष्ठा regulator_desc arizona_lकरो1_hc = अणु
	.name = "LDO1",
	.supply_name = "LDOVDD",
	.type = REGULATOR_VOLTAGE,
	.ops = &arizona_lकरो1_hc_ops,

	.vsel_reg = ARIZONA_LDO1_CONTROL_1,
	.vsel_mask = ARIZONA_LDO1_VSEL_MASK,
	.bypass_reg = ARIZONA_LDO1_CONTROL_1,
	.bypass_mask = ARIZONA_LDO1_BYPASS,
	.linear_ranges = arizona_lकरो1_hc_ranges,
	.n_linear_ranges = ARRAY_SIZE(arizona_lकरो1_hc_ranges),
	.n_voltages = 8,
	.enable_समय = 1500,
	.ramp_delay = 24000,

	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops arizona_lकरो1_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc arizona_lकरो1 = अणु
	.name = "LDO1",
	.supply_name = "LDOVDD",
	.type = REGULATOR_VOLTAGE,
	.ops = &arizona_lकरो1_ops,

	.vsel_reg = ARIZONA_LDO1_CONTROL_1,
	.vsel_mask = ARIZONA_LDO1_VSEL_MASK,
	.min_uV = 900000,
	.uV_step = 25000,
	.n_voltages = 13,
	.enable_समय = 500,
	.ramp_delay = 24000,

	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा regulator_init_data arizona_lकरो1_dvfs = अणु
	.स्थिरraपूर्णांकs = अणु
		.min_uV = 1200000,
		.max_uV = 1800000,
		.valid_ops_mask = REGULATOR_CHANGE_STATUS |
				  REGULATOR_CHANGE_VOLTAGE,
	पूर्ण,
	.num_consumer_supplies = 1,
पूर्ण;

अटल स्थिर काष्ठा regulator_init_data arizona_lकरो1_शेष = अणु
	.स्थिरraपूर्णांकs = अणु
		.valid_ops_mask = REGULATOR_CHANGE_STATUS,
	पूर्ण,
	.num_consumer_supplies = 1,
पूर्ण;

अटल स्थिर काष्ठा regulator_init_data arizona_lकरो1_wm5110 = अणु
	.स्थिरraपूर्णांकs = अणु
		.min_uV = 1175000,
		.max_uV = 1200000,
		.valid_ops_mask = REGULATOR_CHANGE_STATUS |
				  REGULATOR_CHANGE_VOLTAGE,
	पूर्ण,
	.num_consumer_supplies = 1,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc madera_lकरो1 = अणु
	.name = "LDO1",
	.supply_name = "LDOVDD",
	.type = REGULATOR_VOLTAGE,
	.ops = &arizona_lकरो1_ops,

	.vsel_reg = MADERA_LDO1_CONTROL_1,
	.vsel_mask = MADERA_LDO1_VSEL_MASK,
	.min_uV = 900000,
	.uV_step = 25000,
	.n_voltages = 13,
	.enable_समय = 3000,

	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा regulator_init_data madera_lकरो1_शेष = अणु
	.स्थिरraपूर्णांकs = अणु
		.min_uV = 1200000,
		.max_uV = 1200000,
		.valid_ops_mask = REGULATOR_CHANGE_STATUS,
	पूर्ण,
	.num_consumer_supplies = 1,
पूर्ण;

अटल पूर्णांक arizona_lकरो1_of_get_pdata(काष्ठा arizona_lकरो1_pdata *pdata,
				     काष्ठा regulator_config *config,
				     स्थिर काष्ठा regulator_desc *desc,
				     bool *बाह्यal_dcvdd)
अणु
	काष्ठा arizona_lकरो1 *lकरो1 = config->driver_data;
	काष्ठा device_node *np = config->dev->of_node;
	काष्ठा device_node *init_node, *dcvdd_node;
	काष्ठा regulator_init_data *init_data;

	init_node = of_get_child_by_name(np, "ldo1");
	dcvdd_node = of_parse_phandle(np, "DCVDD-supply", 0);

	अगर (init_node) अणु
		config->of_node = init_node;

		init_data = of_get_regulator_init_data(config->dev, init_node,
						       desc);
		अगर (init_data) अणु
			init_data->consumer_supplies = &lकरो1->supply;
			init_data->num_consumer_supplies = 1;

			अगर (dcvdd_node && dcvdd_node != init_node)
				*बाह्यal_dcvdd = true;

			pdata->init_data = init_data;
		पूर्ण
	पूर्ण अन्यथा अगर (dcvdd_node) अणु
		*बाह्यal_dcvdd = true;
	पूर्ण

	of_node_put(dcvdd_node);

	वापस 0;
पूर्ण

अटल पूर्णांक arizona_lकरो1_common_init(काष्ठा platक्रमm_device *pdev,
				    काष्ठा arizona_lकरो1 *lकरो1,
				    स्थिर काष्ठा regulator_desc *desc,
				    काष्ठा arizona_lकरो1_pdata *pdata,
				    bool *बाह्यal_dcvdd)
अणु
	काष्ठा device *parent_dev = pdev->dev.parent;
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक ret;

	*बाह्यal_dcvdd = false;

	lकरो1->supply.supply = "DCVDD";
	lकरो1->init_data.consumer_supplies = &lकरो1->supply;
	lकरो1->supply.dev_name = dev_name(parent_dev);

	config.dev = parent_dev;
	config.driver_data = lकरो1;
	config.regmap = lकरो1->regmap;

	अगर (IS_ENABLED(CONFIG_OF)) अणु
		अगर (!dev_get_platdata(parent_dev)) अणु
			ret = arizona_lकरो1_of_get_pdata(pdata,
							&config, desc,
							बाह्यal_dcvdd);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	/* We assume that high output = regulator off
	 * Don't use devm, since we need to get against the parent device
	 * so clean up would happen at the wrong समय
	 */
	config.ena_gpiod = gpiod_get_optional(parent_dev, "wlf,ldoena",
				GPIOD_OUT_LOW | GPIOD_FLAGS_BIT_NONEXCLUSIVE);
	अगर (IS_ERR(config.ena_gpiod))
		वापस PTR_ERR(config.ena_gpiod);

	lकरो1->ena_gpiod = config.ena_gpiod;

	अगर (pdata->init_data)
		config.init_data = pdata->init_data;
	अन्यथा
		config.init_data = &lकरो1->init_data;

	/*
	 * LDO1 can only be used to supply DCVDD so अगर it has no
	 * consumers then DCVDD is supplied बाह्यally.
	 */
	अगर (config.init_data->num_consumer_supplies == 0)
		*बाह्यal_dcvdd = true;

	lकरो1->regulator = devm_regulator_रेजिस्टर(&pdev->dev, desc, &config);

	of_node_put(config.of_node);

	अगर (IS_ERR(lकरो1->regulator)) अणु
		ret = PTR_ERR(lकरो1->regulator);
		dev_err(&pdev->dev, "Failed to register LDO1 supply: %d\n",
			ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, lकरो1);

	वापस 0;
पूर्ण

अटल पूर्णांक arizona_lकरो1_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arizona *arizona = dev_get_drvdata(pdev->dev.parent);
	काष्ठा arizona_lकरो1 *lकरो1;
	स्थिर काष्ठा regulator_desc *desc;
	bool बाह्यal_dcvdd;
	पूर्णांक ret;

	lकरो1 = devm_kzalloc(&pdev->dev, माप(*lकरो1), GFP_KERNEL);
	अगर (!lकरो1)
		वापस -ENOMEM;

	lकरो1->regmap = arizona->regmap;

	/*
	 * Since the chip usually supplies itself we provide some
	 * शेष init_data क्रम it.  This will be overridden with
	 * platक्रमm data अगर provided.
	 */
	चयन (arizona->type) अणु
	हाल WM5102:
	हाल WM8997:
	हाल WM8998:
	हाल WM1814:
		desc = &arizona_lकरो1_hc;
		lकरो1->init_data = arizona_lकरो1_dvfs;
		अवरोध;
	हाल WM5110:
	हाल WM8280:
		desc = &arizona_lकरो1;
		lकरो1->init_data = arizona_lकरो1_wm5110;
		अवरोध;
	शेष:
		desc = &arizona_lकरो1;
		lकरो1->init_data = arizona_lकरो1_शेष;
		अवरोध;
	पूर्ण

	ret = arizona_lकरो1_common_init(pdev, lकरो1, desc,
				       &arizona->pdata.lकरो1,
				       &बाह्यal_dcvdd);
	अगर (ret == 0)
		arizona->बाह्यal_dcvdd = बाह्यal_dcvdd;

	वापस ret;
पूर्ण

अटल पूर्णांक arizona_lकरो1_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arizona_lकरो1 *lकरो1 = platक्रमm_get_drvdata(pdev);

	अगर (lकरो1->ena_gpiod)
		gpiod_put(lकरो1->ena_gpiod);

	वापस 0;
पूर्ण

अटल पूर्णांक madera_lकरो1_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा madera *madera = dev_get_drvdata(pdev->dev.parent);
	काष्ठा arizona_lकरो1 *lकरो1;
	bool बाह्यal_dcvdd;
	पूर्णांक ret;

	lकरो1 = devm_kzalloc(&pdev->dev, माप(*lकरो1), GFP_KERNEL);
	अगर (!lकरो1)
		वापस -ENOMEM;

	lकरो1->regmap = madera->regmap;

	lकरो1->init_data = madera_lकरो1_शेष;

	ret = arizona_lकरो1_common_init(pdev, lकरो1, &madera_lकरो1,
				       &madera->pdata.lकरो1,
				       &बाह्यal_dcvdd);
	अगर (ret)
		वापस ret;

	madera->पूर्णांकernal_dcvdd = !बाह्यal_dcvdd;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver arizona_lकरो1_driver = अणु
	.probe = arizona_lकरो1_probe,
	.हटाओ = arizona_lकरो1_हटाओ,
	.driver		= अणु
		.name	= "arizona-ldo1",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver madera_lकरो1_driver = अणु
	.probe = madera_lकरो1_probe,
	.हटाओ = arizona_lकरो1_हटाओ,
	.driver		= अणु
		.name	= "madera-ldo1",
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर madera_lकरो1_drivers[] = अणु
	&arizona_lकरो1_driver,
	&madera_lकरो1_driver,
पूर्ण;

अटल पूर्णांक __init arizona_lकरो1_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(madera_lकरो1_drivers,
					 ARRAY_SIZE(madera_lकरो1_drivers));
पूर्ण
module_init(arizona_lकरो1_init);

अटल व्योम __निकास madera_lकरो1_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(madera_lकरो1_drivers,
				    ARRAY_SIZE(madera_lकरो1_drivers));
पूर्ण
module_निकास(madera_lकरो1_निकास);

/* Module inक्रमmation */
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("Arizona LDO1 driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:arizona-ldo1");
MODULE_ALIAS("platform:madera-ldo1");
