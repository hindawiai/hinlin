<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * fixed.c
 *
 * Copyright 2008 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 *
 * Copyright (c) 2009 Nokia Corporation
 * Roger Quadros <ext-roger.quadros@nokia.com>
 *
 * This is useful क्रम प्रणालीs with mixed controllable and
 * non-controllable regulators, as well as क्रम allowing testing on
 * प्रणालीs with no controllable regulators.
 */

#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/clk.h>


काष्ठा fixed_voltage_data अणु
	काष्ठा regulator_desc desc;
	काष्ठा regulator_dev *dev;

	काष्ठा clk *enable_घड़ी;
	अचिन्हित पूर्णांक enable_counter;
	पूर्णांक perक्रमmance_state;
पूर्ण;

काष्ठा fixed_dev_type अणु
	bool has_enable_घड़ी;
	bool has_perक्रमmance_state;
पूर्ण;

अटल पूर्णांक reg_घड़ी_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा fixed_voltage_data *priv = rdev_get_drvdata(rdev);
	पूर्णांक ret = 0;

	ret = clk_prepare_enable(priv->enable_घड़ी);
	अगर (ret)
		वापस ret;

	priv->enable_counter++;

	वापस ret;
पूर्ण

अटल पूर्णांक reg_घड़ी_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा fixed_voltage_data *priv = rdev_get_drvdata(rdev);

	clk_disable_unprepare(priv->enable_घड़ी);
	priv->enable_counter--;

	वापस 0;
पूर्ण

अटल पूर्णांक reg_करोमुख्य_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा fixed_voltage_data *priv = rdev_get_drvdata(rdev);
	काष्ठा device *dev = rdev->dev.parent;
	पूर्णांक ret;

	ret = dev_pm_genpd_set_perक्रमmance_state(dev, priv->perक्रमmance_state);
	अगर (ret)
		वापस ret;

	priv->enable_counter++;

	वापस ret;
पूर्ण

अटल पूर्णांक reg_करोमुख्य_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा fixed_voltage_data *priv = rdev_get_drvdata(rdev);
	काष्ठा device *dev = rdev->dev.parent;
	पूर्णांक ret;

	ret = dev_pm_genpd_set_perक्रमmance_state(dev, 0);
	अगर (ret)
		वापस ret;

	priv->enable_counter--;

	वापस 0;
पूर्ण

अटल पूर्णांक reg_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा fixed_voltage_data *priv = rdev_get_drvdata(rdev);

	वापस priv->enable_counter > 0;
पूर्ण


/**
 * of_get_fixed_voltage_config - extract fixed_voltage_config काष्ठाure info
 * @dev: device requesting क्रम fixed_voltage_config
 * @desc: regulator description
 *
 * Populates fixed_voltage_config काष्ठाure by extracting data from device
 * tree node, वापसs a poपूर्णांकer to the populated काष्ठाure of शून्य अगर memory
 * alloc fails.
 */
अटल काष्ठा fixed_voltage_config *
of_get_fixed_voltage_config(काष्ठा device *dev,
			    स्थिर काष्ठा regulator_desc *desc)
अणु
	काष्ठा fixed_voltage_config *config;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा regulator_init_data *init_data;

	config = devm_kzalloc(dev, माप(काष्ठा fixed_voltage_config),
								 GFP_KERNEL);
	अगर (!config)
		वापस ERR_PTR(-ENOMEM);

	config->init_data = of_get_regulator_init_data(dev, dev->of_node, desc);
	अगर (!config->init_data)
		वापस ERR_PTR(-EINVAL);

	init_data = config->init_data;
	init_data->स्थिरraपूर्णांकs.apply_uV = 0;

	config->supply_name = init_data->स्थिरraपूर्णांकs.name;
	अगर (init_data->स्थिरraपूर्णांकs.min_uV == init_data->स्थिरraपूर्णांकs.max_uV) अणु
		config->microvolts = init_data->स्थिरraपूर्णांकs.min_uV;
	पूर्ण अन्यथा अणु
		dev_err(dev,
			 "Fixed regulator specified with variable voltages\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (init_data->स्थिरraपूर्णांकs.boot_on)
		config->enabled_at_boot = true;

	of_property_पढ़ो_u32(np, "startup-delay-us", &config->startup_delay);
	of_property_पढ़ो_u32(np, "off-on-delay-us", &config->off_on_delay);

	अगर (of_find_property(np, "vin-supply", शून्य))
		config->input_supply = "vin";

	वापस config;
पूर्ण

अटल स्थिर काष्ठा regulator_ops fixed_voltage_ops = अणु
पूर्ण;

अटल स्थिर काष्ठा regulator_ops fixed_voltage_clkenabled_ops = अणु
	.enable = reg_घड़ी_enable,
	.disable = reg_घड़ी_disable,
	.is_enabled = reg_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops fixed_voltage_करोमुख्य_ops = अणु
	.enable = reg_करोमुख्य_enable,
	.disable = reg_करोमुख्य_disable,
	.is_enabled = reg_is_enabled,
पूर्ण;

अटल पूर्णांक reg_fixed_voltage_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fixed_voltage_config *config;
	काष्ठा fixed_voltage_data *drvdata;
	स्थिर काष्ठा fixed_dev_type *drvtype = of_device_get_match_data(dev);
	काष्ठा regulator_config cfg = अणु पूर्ण;
	क्रमागत gpiod_flags gflags;
	पूर्णांक ret;

	drvdata = devm_kzalloc(&pdev->dev, माप(काष्ठा fixed_voltage_data),
			       GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	अगर (pdev->dev.of_node) अणु
		config = of_get_fixed_voltage_config(&pdev->dev,
						     &drvdata->desc);
		अगर (IS_ERR(config))
			वापस PTR_ERR(config);
	पूर्ण अन्यथा अणु
		config = dev_get_platdata(&pdev->dev);
	पूर्ण

	अगर (!config)
		वापस -ENOMEM;

	drvdata->desc.name = devm_kstrdup(&pdev->dev,
					  config->supply_name,
					  GFP_KERNEL);
	अगर (drvdata->desc.name == शून्य) अणु
		dev_err(&pdev->dev, "Failed to allocate supply name\n");
		वापस -ENOMEM;
	पूर्ण
	drvdata->desc.type = REGULATOR_VOLTAGE;
	drvdata->desc.owner = THIS_MODULE;

	अगर (drvtype && drvtype->has_enable_घड़ी) अणु
		drvdata->desc.ops = &fixed_voltage_clkenabled_ops;

		drvdata->enable_घड़ी = devm_clk_get(dev, शून्य);
		अगर (IS_ERR(drvdata->enable_घड़ी)) अणु
			dev_err(dev, "Can't get enable-clock from devicetree\n");
			वापस -ENOENT;
		पूर्ण
	पूर्ण अन्यथा अगर (drvtype && drvtype->has_perक्रमmance_state) अणु
		drvdata->desc.ops = &fixed_voltage_करोमुख्य_ops;

		drvdata->perक्रमmance_state = of_get_required_opp_perक्रमmance_state(dev->of_node, 0);
		अगर (drvdata->perक्रमmance_state < 0) अणु
			dev_err(dev, "Can't get performance state from devicetree\n");
			वापस drvdata->perक्रमmance_state;
		पूर्ण
	पूर्ण अन्यथा अणु
		drvdata->desc.ops = &fixed_voltage_ops;
	पूर्ण

	drvdata->desc.enable_समय = config->startup_delay;
	drvdata->desc.off_on_delay = config->off_on_delay;

	अगर (config->input_supply) अणु
		drvdata->desc.supply_name = devm_kstrdup(&pdev->dev,
					    config->input_supply,
					    GFP_KERNEL);
		अगर (!drvdata->desc.supply_name) अणु
			dev_err(&pdev->dev,
				"Failed to allocate input supply\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (config->microvolts)
		drvdata->desc.n_voltages = 1;

	drvdata->desc.fixed_uV = config->microvolts;

	/*
	 * The संकेत will be inverted by the GPIO core अगर flagged so in the
	 * descriptor.
	 */
	अगर (config->enabled_at_boot)
		gflags = GPIOD_OUT_HIGH;
	अन्यथा
		gflags = GPIOD_OUT_LOW;

	/*
	 * Some fixed regulators share the enable line between two
	 * regulators which makes it necessary to get a handle on the
	 * same descriptor क्रम two dअगरferent consumers. This will get
	 * the GPIO descriptor, but only the first call will initialize
	 * it so any flags such as inversion or खोलो drain will only
	 * be set up by the first caller and assumed identical on the
	 * next caller.
	 *
	 * FIXME: find a better way to deal with this.
	 */
	gflags |= GPIOD_FLAGS_BIT_NONEXCLUSIVE;

	/*
	 * Do not use devm* here: the regulator core takes over the
	 * lअगरecycle management of the GPIO descriptor.
	 */
	cfg.ena_gpiod = gpiod_get_optional(&pdev->dev, शून्य, gflags);
	अगर (IS_ERR(cfg.ena_gpiod))
		वापस PTR_ERR(cfg.ena_gpiod);

	cfg.dev = &pdev->dev;
	cfg.init_data = config->init_data;
	cfg.driver_data = drvdata;
	cfg.of_node = pdev->dev.of_node;

	drvdata->dev = devm_regulator_रेजिस्टर(&pdev->dev, &drvdata->desc,
					       &cfg);
	अगर (IS_ERR(drvdata->dev)) अणु
		ret = PTR_ERR(drvdata->dev);
		dev_err(&pdev->dev, "Failed to register regulator: %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, drvdata);

	dev_dbg(&pdev->dev, "%s supplying %duV\n", drvdata->desc.name,
		drvdata->desc.fixed_uV);

	वापस 0;
पूर्ण

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा fixed_dev_type fixed_voltage_data = अणु
	.has_enable_घड़ी = false,
पूर्ण;

अटल स्थिर काष्ठा fixed_dev_type fixed_clkenable_data = अणु
	.has_enable_घड़ी = true,
पूर्ण;

अटल स्थिर काष्ठा fixed_dev_type fixed_करोमुख्य_data = अणु
	.has_perक्रमmance_state = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id fixed_of_match[] = अणु
	अणु
		.compatible = "regulator-fixed",
		.data = &fixed_voltage_data,
	पूर्ण,
	अणु
		.compatible = "regulator-fixed-clock",
		.data = &fixed_clkenable_data,
	पूर्ण,
	अणु
		.compatible = "regulator-fixed-domain",
		.data = &fixed_करोमुख्य_data,
	पूर्ण,
	अणु
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, fixed_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver regulator_fixed_voltage_driver = अणु
	.probe		= reg_fixed_voltage_probe,
	.driver		= अणु
		.name		= "reg-fixed-voltage",
		.of_match_table = of_match_ptr(fixed_of_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init regulator_fixed_voltage_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&regulator_fixed_voltage_driver);
पूर्ण
subsys_initcall(regulator_fixed_voltage_init);

अटल व्योम __निकास regulator_fixed_voltage_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&regulator_fixed_voltage_driver);
पूर्ण
module_निकास(regulator_fixed_voltage_निकास);

MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("Fixed voltage regulator");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:reg-fixed-voltage");
