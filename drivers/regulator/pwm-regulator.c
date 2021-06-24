<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Regulator driver क्रम PWM Regulators
 *
 * Copyright (C) 2014 - STMicroelectronics Inc.
 *
 * Author: Lee Jones <lee.jones@linaro.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/gpio/consumer.h>

काष्ठा pwm_continuous_reg_data अणु
	अचिन्हित पूर्णांक min_uV_dutycycle;
	अचिन्हित पूर्णांक max_uV_dutycycle;
	अचिन्हित पूर्णांक dutycycle_unit;
पूर्ण;

काष्ठा pwm_regulator_data अणु
	/*  Shared */
	काष्ठा pwm_device *pwm;

	/* Voltage table */
	काष्ठा pwm_voltages *duty_cycle_table;

	/* Continuous mode info */
	काष्ठा pwm_continuous_reg_data continuous;

	/* regulator descriptor */
	काष्ठा regulator_desc desc;

	पूर्णांक state;

	/* Enable GPIO */
	काष्ठा gpio_desc *enb_gpio;
पूर्ण;

काष्ठा pwm_voltages अणु
	अचिन्हित पूर्णांक uV;
	अचिन्हित पूर्णांक dutycycle;
पूर्ण;

/*
 * Voltage table call-backs
 */
अटल व्योम pwm_regulator_init_state(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा pwm_regulator_data *drvdata = rdev_get_drvdata(rdev);
	काष्ठा pwm_state pwm_state;
	अचिन्हित पूर्णांक dutycycle;
	पूर्णांक i;

	pwm_get_state(drvdata->pwm, &pwm_state);
	dutycycle = pwm_get_relative_duty_cycle(&pwm_state, 100);

	क्रम (i = 0; i < rdev->desc->n_voltages; i++) अणु
		अगर (dutycycle == drvdata->duty_cycle_table[i].dutycycle) अणु
			drvdata->state = i;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक pwm_regulator_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा pwm_regulator_data *drvdata = rdev_get_drvdata(rdev);

	अगर (drvdata->state < 0)
		pwm_regulator_init_state(rdev);

	वापस drvdata->state;
पूर्ण

अटल पूर्णांक pwm_regulator_set_voltage_sel(काष्ठा regulator_dev *rdev,
					 अचिन्हित selector)
अणु
	काष्ठा pwm_regulator_data *drvdata = rdev_get_drvdata(rdev);
	काष्ठा pwm_state pstate;
	पूर्णांक ret;

	pwm_init_state(drvdata->pwm, &pstate);
	pwm_set_relative_duty_cycle(&pstate,
			drvdata->duty_cycle_table[selector].dutycycle, 100);

	ret = pwm_apply_state(drvdata->pwm, &pstate);
	अगर (ret) अणु
		dev_err(&rdev->dev, "Failed to configure PWM: %d\n", ret);
		वापस ret;
	पूर्ण

	drvdata->state = selector;

	वापस 0;
पूर्ण

अटल पूर्णांक pwm_regulator_list_voltage(काष्ठा regulator_dev *rdev,
				      अचिन्हित selector)
अणु
	काष्ठा pwm_regulator_data *drvdata = rdev_get_drvdata(rdev);

	अगर (selector >= rdev->desc->n_voltages)
		वापस -EINVAL;

	वापस drvdata->duty_cycle_table[selector].uV;
पूर्ण

अटल पूर्णांक pwm_regulator_enable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा pwm_regulator_data *drvdata = rdev_get_drvdata(dev);

	gpiod_set_value_cansleep(drvdata->enb_gpio, 1);

	वापस pwm_enable(drvdata->pwm);
पूर्ण

अटल पूर्णांक pwm_regulator_disable(काष्ठा regulator_dev *dev)
अणु
	काष्ठा pwm_regulator_data *drvdata = rdev_get_drvdata(dev);

	pwm_disable(drvdata->pwm);

	gpiod_set_value_cansleep(drvdata->enb_gpio, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक pwm_regulator_is_enabled(काष्ठा regulator_dev *dev)
अणु
	काष्ठा pwm_regulator_data *drvdata = rdev_get_drvdata(dev);

	अगर (drvdata->enb_gpio && !gpiod_get_value_cansleep(drvdata->enb_gpio))
		वापस false;

	वापस pwm_is_enabled(drvdata->pwm);
पूर्ण

अटल पूर्णांक pwm_regulator_get_voltage(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा pwm_regulator_data *drvdata = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक min_uV_duty = drvdata->continuous.min_uV_dutycycle;
	अचिन्हित पूर्णांक max_uV_duty = drvdata->continuous.max_uV_dutycycle;
	अचिन्हित पूर्णांक duty_unit = drvdata->continuous.dutycycle_unit;
	पूर्णांक min_uV = rdev->स्थिरraपूर्णांकs->min_uV;
	पूर्णांक max_uV = rdev->स्थिरraपूर्णांकs->max_uV;
	पूर्णांक dअगरf_uV = max_uV - min_uV;
	काष्ठा pwm_state pstate;
	अचिन्हित पूर्णांक dअगरf_duty;
	अचिन्हित पूर्णांक voltage;

	pwm_get_state(drvdata->pwm, &pstate);

	voltage = pwm_get_relative_duty_cycle(&pstate, duty_unit);

	/*
	 * The dutycycle क्रम min_uV might be greater than the one क्रम max_uV.
	 * This is happening when the user needs an inversed polarity, but the
	 * PWM device करोes not support inversing it in hardware.
	 */
	अगर (max_uV_duty < min_uV_duty) अणु
		voltage = min_uV_duty - voltage;
		dअगरf_duty = min_uV_duty - max_uV_duty;
	पूर्ण अन्यथा अणु
		voltage = voltage - min_uV_duty;
		dअगरf_duty = max_uV_duty - min_uV_duty;
	पूर्ण

	voltage = DIV_ROUND_CLOSEST_ULL((u64)voltage * dअगरf_uV, dअगरf_duty);

	वापस voltage + min_uV;
पूर्ण

अटल पूर्णांक pwm_regulator_set_voltage(काष्ठा regulator_dev *rdev,
				     पूर्णांक req_min_uV, पूर्णांक req_max_uV,
				     अचिन्हित पूर्णांक *selector)
अणु
	काष्ठा pwm_regulator_data *drvdata = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक min_uV_duty = drvdata->continuous.min_uV_dutycycle;
	अचिन्हित पूर्णांक max_uV_duty = drvdata->continuous.max_uV_dutycycle;
	अचिन्हित पूर्णांक duty_unit = drvdata->continuous.dutycycle_unit;
	पूर्णांक min_uV = rdev->स्थिरraपूर्णांकs->min_uV;
	पूर्णांक max_uV = rdev->स्थिरraपूर्णांकs->max_uV;
	पूर्णांक dअगरf_uV = max_uV - min_uV;
	काष्ठा pwm_state pstate;
	अचिन्हित पूर्णांक dअगरf_duty;
	अचिन्हित पूर्णांक dutycycle;
	पूर्णांक ret;

	pwm_init_state(drvdata->pwm, &pstate);

	/*
	 * The dutycycle क्रम min_uV might be greater than the one क्रम max_uV.
	 * This is happening when the user needs an inversed polarity, but the
	 * PWM device करोes not support inversing it in hardware.
	 */
	अगर (max_uV_duty < min_uV_duty)
		dअगरf_duty = min_uV_duty - max_uV_duty;
	अन्यथा
		dअगरf_duty = max_uV_duty - min_uV_duty;

	dutycycle = DIV_ROUND_CLOSEST_ULL((u64)(req_min_uV - min_uV) *
					  dअगरf_duty,
					  dअगरf_uV);

	अगर (max_uV_duty < min_uV_duty)
		dutycycle = min_uV_duty - dutycycle;
	अन्यथा
		dutycycle = min_uV_duty + dutycycle;

	pwm_set_relative_duty_cycle(&pstate, dutycycle, duty_unit);

	ret = pwm_apply_state(drvdata->pwm, &pstate);
	अगर (ret) अणु
		dev_err(&rdev->dev, "Failed to configure PWM: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regulator_ops pwm_regulator_voltage_table_ops = अणु
	.set_voltage_sel = pwm_regulator_set_voltage_sel,
	.get_voltage_sel = pwm_regulator_get_voltage_sel,
	.list_voltage    = pwm_regulator_list_voltage,
	.map_voltage     = regulator_map_voltage_iterate,
	.enable          = pwm_regulator_enable,
	.disable         = pwm_regulator_disable,
	.is_enabled      = pwm_regulator_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops pwm_regulator_voltage_continuous_ops = अणु
	.get_voltage = pwm_regulator_get_voltage,
	.set_voltage = pwm_regulator_set_voltage,
	.enable          = pwm_regulator_enable,
	.disable         = pwm_regulator_disable,
	.is_enabled      = pwm_regulator_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc pwm_regulator_desc = अणु
	.name		= "pwm-regulator",
	.type		= REGULATOR_VOLTAGE,
	.owner		= THIS_MODULE,
	.supply_name    = "pwm",
पूर्ण;

अटल पूर्णांक pwm_regulator_init_table(काष्ठा platक्रमm_device *pdev,
				    काष्ठा pwm_regulator_data *drvdata)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा pwm_voltages *duty_cycle_table;
	अचिन्हित पूर्णांक length = 0;
	पूर्णांक ret;

	of_find_property(np, "voltage-table", &length);

	अगर ((length < माप(*duty_cycle_table)) ||
	    (length % माप(*duty_cycle_table))) अणु
		dev_err(&pdev->dev, "voltage-table length(%d) is invalid\n",
			length);
		वापस -EINVAL;
	पूर्ण

	duty_cycle_table = devm_kzalloc(&pdev->dev, length, GFP_KERNEL);
	अगर (!duty_cycle_table)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_u32_array(np, "voltage-table",
					 (u32 *)duty_cycle_table,
					 length / माप(u32));
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to read voltage-table: %d\n", ret);
		वापस ret;
	पूर्ण

	drvdata->state			= -ENOTRECOVERABLE;
	drvdata->duty_cycle_table	= duty_cycle_table;
	drvdata->desc.ops = &pwm_regulator_voltage_table_ops;
	drvdata->desc.n_voltages	= length / माप(*duty_cycle_table);

	वापस 0;
पूर्ण

अटल पूर्णांक pwm_regulator_init_continuous(काष्ठा platक्रमm_device *pdev,
					 काष्ठा pwm_regulator_data *drvdata)
अणु
	u32 dutycycle_range[2] = अणु 0, 100 पूर्ण;
	u32 dutycycle_unit = 100;

	drvdata->desc.ops = &pwm_regulator_voltage_continuous_ops;
	drvdata->desc.continuous_voltage_range = true;

	of_property_पढ़ो_u32_array(pdev->dev.of_node,
				   "pwm-dutycycle-range",
				   dutycycle_range, 2);
	of_property_पढ़ो_u32(pdev->dev.of_node, "pwm-dutycycle-unit",
			     &dutycycle_unit);

	अगर (dutycycle_range[0] > dutycycle_unit ||
	    dutycycle_range[1] > dutycycle_unit)
		वापस -EINVAL;

	drvdata->continuous.dutycycle_unit = dutycycle_unit;
	drvdata->continuous.min_uV_dutycycle = dutycycle_range[0];
	drvdata->continuous.max_uV_dutycycle = dutycycle_range[1];

	वापस 0;
पूर्ण

अटल पूर्णांक pwm_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा regulator_init_data *init_data;
	काष्ठा pwm_regulator_data *drvdata;
	काष्ठा regulator_dev *regulator;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा device_node *np = pdev->dev.of_node;
	क्रमागत gpiod_flags gpio_flags;
	पूर्णांक ret;

	अगर (!np) अणु
		dev_err(&pdev->dev, "Device Tree node missing\n");
		वापस -EINVAL;
	पूर्ण

	drvdata = devm_kzalloc(&pdev->dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	स_नकल(&drvdata->desc, &pwm_regulator_desc, माप(drvdata->desc));

	अगर (of_find_property(np, "voltage-table", शून्य))
		ret = pwm_regulator_init_table(pdev, drvdata);
	अन्यथा
		ret = pwm_regulator_init_continuous(pdev, drvdata);
	अगर (ret)
		वापस ret;

	init_data = of_get_regulator_init_data(&pdev->dev, np,
					       &drvdata->desc);
	अगर (!init_data)
		वापस -ENOMEM;

	config.of_node = np;
	config.dev = &pdev->dev;
	config.driver_data = drvdata;
	config.init_data = init_data;

	drvdata->pwm = devm_pwm_get(&pdev->dev, शून्य);
	अगर (IS_ERR(drvdata->pwm)) अणु
		ret = PTR_ERR(drvdata->pwm);
		अगर (ret == -EPROBE_DEFER)
			dev_dbg(&pdev->dev,
				"Failed to get PWM, deferring probe\n");
		अन्यथा
			dev_err(&pdev->dev, "Failed to get PWM: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (init_data->स्थिरraपूर्णांकs.boot_on || init_data->स्थिरraपूर्णांकs.always_on)
		gpio_flags = GPIOD_OUT_HIGH;
	अन्यथा
		gpio_flags = GPIOD_OUT_LOW;
	drvdata->enb_gpio = devm_gpiod_get_optional(&pdev->dev, "enable",
						    gpio_flags);
	अगर (IS_ERR(drvdata->enb_gpio)) अणु
		ret = PTR_ERR(drvdata->enb_gpio);
		dev_err(&pdev->dev, "Failed to get enable GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = pwm_adjust_config(drvdata->pwm);
	अगर (ret)
		वापस ret;

	regulator = devm_regulator_रेजिस्टर(&pdev->dev,
					    &drvdata->desc, &config);
	अगर (IS_ERR(regulator)) अणु
		ret = PTR_ERR(regulator);
		dev_err(&pdev->dev, "Failed to register regulator %s: %d\n",
			drvdata->desc.name, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused pwm_of_match[] = अणु
	अणु .compatible = "pwm-regulator" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pwm_of_match);

अटल काष्ठा platक्रमm_driver pwm_regulator_driver = अणु
	.driver = अणु
		.name		= "pwm-regulator",
		.of_match_table = of_match_ptr(pwm_of_match),
	पूर्ण,
	.probe = pwm_regulator_probe,
पूर्ण;

module_platक्रमm_driver(pwm_regulator_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lee Jones <lee.jones@linaro.org>");
MODULE_DESCRIPTION("PWM Regulator Driver");
MODULE_ALIAS("platform:pwm-regulator");
