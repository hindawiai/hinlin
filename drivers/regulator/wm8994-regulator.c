<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// wm8994-regulator.c  --  Regulator driver क्रम the WM8994
//
// Copyright 2009 Wolfson Microelectronics PLC.
//
// Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/slab.h>

#समावेश <linux/mfd/wm8994/core.h>
#समावेश <linux/mfd/wm8994/रेजिस्टरs.h>
#समावेश <linux/mfd/wm8994/pdata.h>

काष्ठा wm8994_lकरो अणु
	काष्ठा regulator_dev *regulator;
	काष्ठा wm8994 *wm8994;
	काष्ठा regulator_consumer_supply supply;
	काष्ठा regulator_init_data init_data;
पूर्ण;

#घोषणा WM8994_LDO1_MAX_SELECTOR 0x7
#घोषणा WM8994_LDO2_MAX_SELECTOR 0x3

अटल स्थिर काष्ठा regulator_ops wm8994_lकरो1_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
पूर्ण;

अटल पूर्णांक wm8994_lकरो2_list_voltage(काष्ठा regulator_dev *rdev,
				    अचिन्हित पूर्णांक selector)
अणु
	काष्ठा wm8994_lकरो *lकरो = rdev_get_drvdata(rdev);

	अगर (selector > WM8994_LDO2_MAX_SELECTOR)
		वापस -EINVAL;

	चयन (lकरो->wm8994->type) अणु
	हाल WM8994:
		वापस (selector * 100000) + 900000;
	हाल WM8958:
		वापस (selector * 100000) + 1000000;
	हाल WM1811:
		चयन (selector) अणु
		हाल 0:
			वापस -EINVAL;
		शेष:
			वापस (selector * 100000) + 950000;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regulator_ops wm8994_lकरो2_ops = अणु
	.list_voltage = wm8994_lकरो2_list_voltage,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc wm8994_lकरो_desc[] = अणु
	अणु
		.name = "LDO1",
		.id = 1,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = WM8994_LDO1_MAX_SELECTOR + 1,
		.vsel_reg = WM8994_LDO_1,
		.vsel_mask = WM8994_LDO1_VSEL_MASK,
		.ops = &wm8994_lकरो1_ops,
		.min_uV = 2400000,
		.uV_step = 100000,
		.enable_समय = 3000,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "LDO2",
		.id = 2,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = WM8994_LDO2_MAX_SELECTOR + 1,
		.vsel_reg = WM8994_LDO_2,
		.vsel_mask = WM8994_LDO2_VSEL_MASK,
		.ops = &wm8994_lकरो2_ops,
		.enable_समय = 3000,
		.owner = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regulator_consumer_supply wm8994_lकरो_consumer[] = अणु
	अणु .supply = "AVDD1" पूर्ण,
	अणु .supply = "DCVDD" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regulator_init_data wm8994_lकरो_शेष[] = अणु
	अणु
		.स्थिरraपूर्णांकs = अणु
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
		.num_consumer_supplies = 1,
	पूर्ण,
	अणु
		.स्थिरraपूर्णांकs = अणु
			.valid_ops_mask = REGULATOR_CHANGE_STATUS,
		पूर्ण,
		.num_consumer_supplies = 1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक wm8994_lकरो_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm8994 *wm8994 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm8994_pdata *pdata = dev_get_platdata(wm8994->dev);
	पूर्णांक id = pdev->id % ARRAY_SIZE(pdata->lकरो);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा wm8994_lकरो *lकरो;
	काष्ठा gpio_desc *gpiod;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "Probing LDO%d\n", id + 1);

	lकरो = devm_kzalloc(&pdev->dev, माप(काष्ठा wm8994_lकरो), GFP_KERNEL);
	अगर (!lकरो)
		वापस -ENOMEM;

	lकरो->wm8994 = wm8994;
	lकरो->supply = wm8994_lकरो_consumer[id];
	lकरो->supply.dev_name = dev_name(wm8994->dev);

	config.dev = wm8994->dev;
	config.driver_data = lकरो;
	config.regmap = wm8994->regmap;
	config.init_data = &lकरो->init_data;

	/*
	 * Look up LDO enable GPIO from the parent device node, we करोn't
	 * use devm because the regulator core will मुक्त the GPIO
	 */
	gpiod = gpiod_get_optional(pdev->dev.parent,
				   id ? "wlf,ldo2ena" : "wlf,ldo1ena",
				   GPIOD_OUT_LOW |
				   GPIOD_FLAGS_BIT_NONEXCLUSIVE);
	अगर (IS_ERR(gpiod))
		वापस PTR_ERR(gpiod);
	config.ena_gpiod = gpiod;

	/* Use शेष स्थिरraपूर्णांकs अगर none set up */
	अगर (!pdata || !pdata->lकरो[id].init_data || wm8994->dev->of_node) अणु
		dev_dbg(wm8994->dev, "Using default init data, supply %s %s\n",
			lकरो->supply.dev_name, lकरो->supply.supply);

		lकरो->init_data = wm8994_lकरो_शेष[id];
		lकरो->init_data.consumer_supplies = &lकरो->supply;
		अगर (!gpiod)
			lकरो->init_data.स्थिरraपूर्णांकs.valid_ops_mask = 0;
	पूर्ण अन्यथा अणु
		lकरो->init_data = *pdata->lकरो[id].init_data;
	पूर्ण

	/*
	 * At this poपूर्णांक the GPIO descriptor is handled over to the
	 * regulator core and we need not worry about it on the
	 * error path.
	 */
	lकरो->regulator = devm_regulator_रेजिस्टर(&pdev->dev,
						 &wm8994_lकरो_desc[id],
						 &config);
	अगर (IS_ERR(lकरो->regulator)) अणु
		ret = PTR_ERR(lकरो->regulator);
		dev_err(wm8994->dev, "Failed to register LDO%d: %d\n",
			id + 1, ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, lकरो);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wm8994_lकरो_driver = अणु
	.probe = wm8994_lकरो_probe,
	.driver		= अणु
		.name	= "wm8994-ldo",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wm8994_lकरो_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("WM8994 LDO driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm8994-ldo");
