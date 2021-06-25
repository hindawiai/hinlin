<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// SY8827N regulator driver
//
// Copyright (C) 2020 Synaptics Incorporated
//
// Author: Jisheng Zhang <jszhang@kernel.org>

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>

#घोषणा SY8827N_VSEL0		0
#घोषणा   SY8827N_BUCK_EN	(1 << 7)
#घोषणा   SY8827N_MODE		(1 << 6)
#घोषणा SY8827N_VSEL1		1
#घोषणा SY8827N_CTRL		2

#घोषणा SY8827N_NVOLTAGES	64
#घोषणा SY8827N_VSELMIN		600000
#घोषणा SY8827N_VSELSTEP	12500

काष्ठा sy8827n_device_info अणु
	काष्ठा device *dev;
	काष्ठा regulator_desc desc;
	काष्ठा regulator_init_data *regulator;
	काष्ठा gpio_desc *en_gpio;
	अचिन्हित पूर्णांक vsel_reg;
पूर्ण;

अटल पूर्णांक sy8827n_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा sy8827n_device_info *di = rdev_get_drvdata(rdev);

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		regmap_update_bits(rdev->regmap, di->vsel_reg,
				   SY8827N_MODE, SY8827N_MODE);
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		regmap_update_bits(rdev->regmap, di->vsel_reg,
				   SY8827N_MODE, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक sy8827n_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा sy8827n_device_info *di = rdev_get_drvdata(rdev);
	u32 val;
	पूर्णांक ret = 0;

	ret = regmap_पढ़ो(rdev->regmap, di->vsel_reg, &val);
	अगर (ret < 0)
		वापस ret;
	अगर (val & SY8827N_MODE)
		वापस REGULATOR_MODE_FAST;
	अन्यथा
		वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल स्थिर काष्ठा regulator_ops sy8827n_regulator_ops = अणु
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.map_voltage = regulator_map_voltage_linear,
	.list_voltage = regulator_list_voltage_linear,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_mode = sy8827n_set_mode,
	.get_mode = sy8827n_get_mode,
पूर्ण;

अटल पूर्णांक sy8827n_regulator_रेजिस्टर(काष्ठा sy8827n_device_info *di,
			काष्ठा regulator_config *config)
अणु
	काष्ठा regulator_desc *rdesc = &di->desc;
	काष्ठा regulator_dev *rdev;

	rdesc->name = "sy8827n-reg";
	rdesc->supply_name = "vin";
	rdesc->ops = &sy8827n_regulator_ops;
	rdesc->type = REGULATOR_VOLTAGE;
	rdesc->n_voltages = SY8827N_NVOLTAGES;
	rdesc->enable_reg = di->vsel_reg;
	rdesc->enable_mask = SY8827N_BUCK_EN;
	rdesc->min_uV = SY8827N_VSELMIN;
	rdesc->uV_step = SY8827N_VSELSTEP;
	rdesc->vsel_reg = di->vsel_reg;
	rdesc->vsel_mask = rdesc->n_voltages - 1;
	rdesc->owner = THIS_MODULE;

	rdev = devm_regulator_रेजिस्टर(di->dev, &di->desc, config);
	वापस PTR_ERR_OR_ZERO(rdev);
पूर्ण

अटल स्थिर काष्ठा regmap_config sy8827n_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक sy8827n_i2c_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा sy8827n_device_info *di;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	di = devm_kzalloc(dev, माप(काष्ठा sy8827n_device_info), GFP_KERNEL);
	अगर (!di)
		वापस -ENOMEM;

	di->regulator = of_get_regulator_init_data(dev, np, &di->desc);
	अगर (!di->regulator) अणु
		dev_err(dev, "Platform data not found!\n");
		वापस -EINVAL;
	पूर्ण

	di->en_gpio = devm_gpiod_get_optional(dev, "enable", GPIOD_OUT_HIGH);
	अगर (IS_ERR(di->en_gpio))
		वापस PTR_ERR(di->en_gpio);

	अगर (of_property_पढ़ो_bool(np, "silergy,vsel-state-high"))
		di->vsel_reg = SY8827N_VSEL1;
	अन्यथा
		di->vsel_reg = SY8827N_VSEL0;

	di->dev = dev;

	regmap = devm_regmap_init_i2c(client, &sy8827n_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "Failed to allocate regmap!\n");
		वापस PTR_ERR(regmap);
	पूर्ण
	i2c_set_clientdata(client, di);

	config.dev = di->dev;
	config.init_data = di->regulator;
	config.regmap = regmap;
	config.driver_data = di;
	config.of_node = np;

	ret = sy8827n_regulator_रेजिस्टर(di, &config);
	अगर (ret < 0)
		dev_err(dev, "Failed to register regulator!\n");
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id sy8827n_dt_ids[] = अणु
	अणु
		.compatible = "silergy,sy8827n",
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sy8827n_dt_ids);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id sy8827n_id[] = अणु
	अणु "sy8827n", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sy8827n_id);

अटल काष्ठा i2c_driver sy8827n_regulator_driver = अणु
	.driver = अणु
		.name = "sy8827n-regulator",
		.of_match_table = of_match_ptr(sy8827n_dt_ids),
	पूर्ण,
	.probe_new = sy8827n_i2c_probe,
	.id_table = sy8827n_id,
पूर्ण;
module_i2c_driver(sy8827n_regulator_driver);

MODULE_AUTHOR("Jisheng Zhang <jszhang@kernel.org>");
MODULE_DESCRIPTION("SY8827N regulator driver");
MODULE_LICENSE("GPL v2");
