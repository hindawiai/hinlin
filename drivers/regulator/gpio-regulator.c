<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * gpio-regulator.c
 *
 * Copyright 2011 Heiko Stuebner <heiko@sntech.de>
 *
 * based on fixed.c
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
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/regulator/gpio-regulator.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

काष्ठा gpio_regulator_data अणु
	काष्ठा regulator_desc desc;

	काष्ठा gpio_desc **gpiods;
	पूर्णांक nr_gpios;

	काष्ठा gpio_regulator_state *states;
	पूर्णांक nr_states;

	पूर्णांक state;
पूर्ण;

अटल पूर्णांक gpio_regulator_get_value(काष्ठा regulator_dev *dev)
अणु
	काष्ठा gpio_regulator_data *data = rdev_get_drvdata(dev);
	पूर्णांक ptr;

	क्रम (ptr = 0; ptr < data->nr_states; ptr++)
		अगर (data->states[ptr].gpios == data->state)
			वापस data->states[ptr].value;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक gpio_regulator_set_voltage(काष्ठा regulator_dev *dev,
					पूर्णांक min_uV, पूर्णांक max_uV,
					अचिन्हित *selector)
अणु
	काष्ठा gpio_regulator_data *data = rdev_get_drvdata(dev);
	पूर्णांक ptr, target = 0, state, best_val = पूर्णांक_उच्च;

	क्रम (ptr = 0; ptr < data->nr_states; ptr++)
		अगर (data->states[ptr].value < best_val &&
		    data->states[ptr].value >= min_uV &&
		    data->states[ptr].value <= max_uV) अणु
			target = data->states[ptr].gpios;
			best_val = data->states[ptr].value;
			अगर (selector)
				*selector = ptr;
		पूर्ण

	अगर (best_val == पूर्णांक_उच्च)
		वापस -EINVAL;

	क्रम (ptr = 0; ptr < data->nr_gpios; ptr++) अणु
		state = (target & (1 << ptr)) >> ptr;
		gpiod_set_value_cansleep(data->gpiods[ptr], state);
	पूर्ण
	data->state = target;

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_regulator_list_voltage(काष्ठा regulator_dev *dev,
				      अचिन्हित selector)
अणु
	काष्ठा gpio_regulator_data *data = rdev_get_drvdata(dev);

	अगर (selector >= data->nr_states)
		वापस -EINVAL;

	वापस data->states[selector].value;
पूर्ण

अटल पूर्णांक gpio_regulator_set_current_limit(काष्ठा regulator_dev *dev,
					पूर्णांक min_uA, पूर्णांक max_uA)
अणु
	काष्ठा gpio_regulator_data *data = rdev_get_drvdata(dev);
	पूर्णांक ptr, target = 0, state, best_val = 0;

	क्रम (ptr = 0; ptr < data->nr_states; ptr++)
		अगर (data->states[ptr].value > best_val &&
		    data->states[ptr].value >= min_uA &&
		    data->states[ptr].value <= max_uA) अणु
			target = data->states[ptr].gpios;
			best_val = data->states[ptr].value;
		पूर्ण

	अगर (best_val == 0)
		वापस -EINVAL;

	क्रम (ptr = 0; ptr < data->nr_gpios; ptr++) अणु
		state = (target & (1 << ptr)) >> ptr;
		gpiod_set_value_cansleep(data->gpiods[ptr], state);
	पूर्ण
	data->state = target;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regulator_ops gpio_regulator_voltage_ops = अणु
	.get_voltage = gpio_regulator_get_value,
	.set_voltage = gpio_regulator_set_voltage,
	.list_voltage = gpio_regulator_list_voltage,
पूर्ण;

अटल काष्ठा gpio_regulator_config *
of_get_gpio_regulator_config(काष्ठा device *dev, काष्ठा device_node *np,
			     स्थिर काष्ठा regulator_desc *desc)
अणु
	काष्ठा gpio_regulator_config *config;
	स्थिर अक्षर *regtype;
	पूर्णांक proplen, i;
	पूर्णांक ngpios;
	पूर्णांक ret;

	config = devm_kzalloc(dev,
			माप(काष्ठा gpio_regulator_config),
			GFP_KERNEL);
	अगर (!config)
		वापस ERR_PTR(-ENOMEM);

	config->init_data = of_get_regulator_init_data(dev, np, desc);
	अगर (!config->init_data)
		वापस ERR_PTR(-EINVAL);

	config->supply_name = config->init_data->स्थिरraपूर्णांकs.name;

	अगर (config->init_data->स्थिरraपूर्णांकs.boot_on)
		config->enabled_at_boot = true;

	/*
	 * Do not use: unकरोcumented device tree property.
	 * This is kept around solely क्रम device tree ABI stability.
	 */
	अगर (of_property_पढ़ो_bool(np, "enable-at-boot"))
		config->enabled_at_boot = true;

	of_property_पढ़ो_u32(np, "startup-delay-us", &config->startup_delay);

	/* Fetch GPIO init levels */
	ngpios = gpiod_count(dev, शून्य);
	अगर (ngpios > 0) अणु
		config->gflags = devm_kzalloc(dev,
					      माप(क्रमागत gpiod_flags)
					      * ngpios,
					      GFP_KERNEL);
		अगर (!config->gflags)
			वापस ERR_PTR(-ENOMEM);

		क्रम (i = 0; i < ngpios; i++) अणु
			u32 val;

			ret = of_property_पढ़ो_u32_index(np, "gpios-states", i,
							 &val);

			/* Default to high per specअगरication */
			अगर (ret)
				config->gflags[i] = GPIOD_OUT_HIGH;
			अन्यथा
				config->gflags[i] =
					val ? GPIOD_OUT_HIGH : GPIOD_OUT_LOW;
		पूर्ण
	पूर्ण
	config->ngpios = ngpios;

	/* Fetch states. */
	proplen = of_property_count_u32_elems(np, "states");
	अगर (proplen < 0) अणु
		dev_err(dev, "No 'states' property found\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	config->states = devm_kसुस्मृति(dev,
				proplen / 2,
				माप(काष्ठा gpio_regulator_state),
				GFP_KERNEL);
	अगर (!config->states)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < proplen / 2; i++) अणु
		of_property_पढ़ो_u32_index(np, "states", i * 2,
					   &config->states[i].value);
		of_property_पढ़ो_u32_index(np, "states", i * 2 + 1,
					   &config->states[i].gpios);
	पूर्ण
	config->nr_states = i;

	config->type = REGULATOR_VOLTAGE;
	ret = of_property_पढ़ो_string(np, "regulator-type", &regtype);
	अगर (ret >= 0) अणु
		अगर (!म_भेदन("voltage", regtype, 7))
			config->type = REGULATOR_VOLTAGE;
		अन्यथा अगर (!म_भेदन("current", regtype, 7))
			config->type = REGULATOR_CURRENT;
		अन्यथा
			dev_warn(dev, "Unknown regulator-type '%s'\n",
				 regtype);
	पूर्ण

	वापस config;
पूर्ण

अटल स्थिर काष्ठा regulator_ops gpio_regulator_current_ops = अणु
	.get_current_limit = gpio_regulator_get_value,
	.set_current_limit = gpio_regulator_set_current_limit,
पूर्ण;

अटल पूर्णांक gpio_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा gpio_regulator_config *config = dev_get_platdata(dev);
	काष्ठा device_node *np = dev->of_node;
	काष्ठा gpio_regulator_data *drvdata;
	काष्ठा regulator_config cfg = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	क्रमागत gpiod_flags gflags;
	पूर्णांक ptr, ret, state, i;

	drvdata = devm_kzalloc(dev, माप(काष्ठा gpio_regulator_data),
			       GFP_KERNEL);
	अगर (drvdata == शून्य)
		वापस -ENOMEM;

	अगर (np) अणु
		config = of_get_gpio_regulator_config(dev, np,
						      &drvdata->desc);
		अगर (IS_ERR(config))
			वापस PTR_ERR(config);
	पूर्ण

	drvdata->desc.name = devm_kstrdup(dev, config->supply_name, GFP_KERNEL);
	अगर (drvdata->desc.name == शून्य) अणु
		dev_err(dev, "Failed to allocate supply name\n");
		वापस -ENOMEM;
	पूर्ण

	drvdata->gpiods = devm_kzalloc(dev, माप(काष्ठा gpio_desc *),
				       GFP_KERNEL);
	अगर (!drvdata->gpiods)
		वापस -ENOMEM;
	क्रम (i = 0; i < config->ngpios; i++) अणु
		drvdata->gpiods[i] = devm_gpiod_get_index(dev,
							  शून्य,
							  i,
							  config->gflags[i]);
		अगर (IS_ERR(drvdata->gpiods[i]))
			वापस PTR_ERR(drvdata->gpiods[i]);
		/* This is good to know */
		gpiod_set_consumer_name(drvdata->gpiods[i], drvdata->desc.name);
	पूर्ण
	drvdata->nr_gpios = config->ngpios;

	drvdata->states = devm_kmemdup(dev,
				       config->states,
				       config->nr_states *
				       माप(काष्ठा gpio_regulator_state),
				       GFP_KERNEL);
	अगर (drvdata->states == शून्य) अणु
		dev_err(dev, "Failed to allocate state data\n");
		वापस -ENOMEM;
	पूर्ण
	drvdata->nr_states = config->nr_states;

	drvdata->desc.owner = THIS_MODULE;
	drvdata->desc.enable_समय = config->startup_delay;

	/* handle regulator type*/
	चयन (config->type) अणु
	हाल REGULATOR_VOLTAGE:
		drvdata->desc.type = REGULATOR_VOLTAGE;
		drvdata->desc.ops = &gpio_regulator_voltage_ops;
		drvdata->desc.n_voltages = config->nr_states;
		अवरोध;
	हाल REGULATOR_CURRENT:
		drvdata->desc.type = REGULATOR_CURRENT;
		drvdata->desc.ops = &gpio_regulator_current_ops;
		अवरोध;
	शेष:
		dev_err(dev, "No regulator type set\n");
		वापस -EINVAL;
	पूर्ण

	/* build initial state from gpio init data. */
	state = 0;
	क्रम (ptr = 0; ptr < drvdata->nr_gpios; ptr++) अणु
		अगर (config->gflags[ptr] == GPIOD_OUT_HIGH)
			state |= (1 << ptr);
	पूर्ण
	drvdata->state = state;

	cfg.dev = dev;
	cfg.init_data = config->init_data;
	cfg.driver_data = drvdata;
	cfg.of_node = np;

	/*
	 * The संकेत will be inverted by the GPIO core अगर flagged so in the
	 * descriptor.
	 */
	अगर (config->enabled_at_boot)
		gflags = GPIOD_OUT_HIGH | GPIOD_FLAGS_BIT_NONEXCLUSIVE;
	अन्यथा
		gflags = GPIOD_OUT_LOW | GPIOD_FLAGS_BIT_NONEXCLUSIVE;

	cfg.ena_gpiod = gpiod_get_optional(dev, "enable", gflags);
	अगर (IS_ERR(cfg.ena_gpiod))
		वापस PTR_ERR(cfg.ena_gpiod);

	rdev = devm_regulator_रेजिस्टर(dev, &drvdata->desc, &cfg);
	अगर (IS_ERR(rdev)) अणु
		ret = PTR_ERR(rdev);
		dev_err(dev, "Failed to register regulator: %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, drvdata);

	वापस 0;
पूर्ण

#अगर defined(CONFIG_OF)
अटल स्थिर काष्ठा of_device_id regulator_gpio_of_match[] = अणु
	अणु .compatible = "regulator-gpio", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, regulator_gpio_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver gpio_regulator_driver = अणु
	.probe		= gpio_regulator_probe,
	.driver		= अणु
		.name		= "gpio-regulator",
		.of_match_table = of_match_ptr(regulator_gpio_of_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init gpio_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&gpio_regulator_driver);
पूर्ण
subsys_initcall(gpio_regulator_init);

अटल व्योम __निकास gpio_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&gpio_regulator_driver);
पूर्ण
module_निकास(gpio_regulator_निकास);

MODULE_AUTHOR("Heiko Stuebner <heiko@sntech.de>");
MODULE_DESCRIPTION("gpio voltage regulator");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:gpio-regulator");
