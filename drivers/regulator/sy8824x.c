<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// SY8824C/SY8824E regulator driver
//
// Copyright (C) 2019 Synaptics Incorporated
//
// Author: Jisheng Zhang <jszhang@kernel.org>

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>

#घोषणा SY8824C_BUCK_EN		(1 << 7)
#घोषणा SY8824C_MODE		(1 << 6)

काष्ठा sy8824_config अणु
	/* रेजिस्टरs */
	अचिन्हित पूर्णांक vol_reg;
	अचिन्हित पूर्णांक mode_reg;
	अचिन्हित पूर्णांक enable_reg;
	/* Voltage range and step(linear) */
	अचिन्हित पूर्णांक vsel_min;
	अचिन्हित पूर्णांक vsel_step;
	अचिन्हित पूर्णांक vsel_count;
पूर्ण;

काष्ठा sy8824_device_info अणु
	काष्ठा device *dev;
	काष्ठा regulator_desc desc;
	काष्ठा regulator_init_data *regulator;
	स्थिर काष्ठा sy8824_config *cfg;
पूर्ण;

अटल पूर्णांक sy8824_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा sy8824_device_info *di = rdev_get_drvdata(rdev);
	स्थिर काष्ठा sy8824_config *cfg = di->cfg;

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		regmap_update_bits(rdev->regmap, cfg->mode_reg,
				   SY8824C_MODE, SY8824C_MODE);
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		regmap_update_bits(rdev->regmap, cfg->mode_reg,
				   SY8824C_MODE, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक sy8824_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा sy8824_device_info *di = rdev_get_drvdata(rdev);
	स्थिर काष्ठा sy8824_config *cfg = di->cfg;
	u32 val;
	पूर्णांक ret = 0;

	ret = regmap_पढ़ो(rdev->regmap, cfg->mode_reg, &val);
	अगर (ret < 0)
		वापस ret;
	अगर (val & SY8824C_MODE)
		वापस REGULATOR_MODE_FAST;
	अन्यथा
		वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल स्थिर काष्ठा regulator_ops sy8824_regulator_ops = अणु
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.map_voltage = regulator_map_voltage_linear,
	.list_voltage = regulator_list_voltage_linear,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_mode = sy8824_set_mode,
	.get_mode = sy8824_get_mode,
पूर्ण;

अटल पूर्णांक sy8824_regulator_रेजिस्टर(काष्ठा sy8824_device_info *di,
			काष्ठा regulator_config *config)
अणु
	काष्ठा regulator_desc *rdesc = &di->desc;
	स्थिर काष्ठा sy8824_config *cfg = di->cfg;
	काष्ठा regulator_dev *rdev;

	rdesc->name = "sy8824-reg";
	rdesc->supply_name = "vin";
	rdesc->ops = &sy8824_regulator_ops;
	rdesc->type = REGULATOR_VOLTAGE;
	rdesc->n_voltages = cfg->vsel_count;
	rdesc->enable_reg = cfg->enable_reg;
	rdesc->enable_mask = SY8824C_BUCK_EN;
	rdesc->min_uV = cfg->vsel_min;
	rdesc->uV_step = cfg->vsel_step;
	rdesc->vsel_reg = cfg->vol_reg;
	rdesc->vsel_mask = cfg->vsel_count - 1;
	rdesc->owner = THIS_MODULE;

	rdev = devm_regulator_रेजिस्टर(di->dev, &di->desc, config);
	वापस PTR_ERR_OR_ZERO(rdev);
पूर्ण

अटल स्थिर काष्ठा regmap_config sy8824_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक sy8824_i2c_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा sy8824_device_info *di;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	di = devm_kzalloc(dev, माप(काष्ठा sy8824_device_info), GFP_KERNEL);
	अगर (!di)
		वापस -ENOMEM;

	di->regulator = of_get_regulator_init_data(dev, np, &di->desc);
	अगर (!di->regulator) अणु
		dev_err(dev, "Platform data not found!\n");
		वापस -EINVAL;
	पूर्ण

	di->dev = dev;
	di->cfg = of_device_get_match_data(dev);

	regmap = devm_regmap_init_i2c(client, &sy8824_regmap_config);
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

	ret = sy8824_regulator_रेजिस्टर(di, &config);
	अगर (ret < 0)
		dev_err(dev, "Failed to register regulator!\n");
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sy8824_config sy8824c_cfg = अणु
	.vol_reg = 0x00,
	.mode_reg = 0x00,
	.enable_reg = 0x00,
	.vsel_min = 762500,
	.vsel_step = 12500,
	.vsel_count = 64,
पूर्ण;

अटल स्थिर काष्ठा sy8824_config sy8824e_cfg = अणु
	.vol_reg = 0x00,
	.mode_reg = 0x00,
	.enable_reg = 0x00,
	.vsel_min = 700000,
	.vsel_step = 12500,
	.vsel_count = 64,
पूर्ण;

अटल स्थिर काष्ठा sy8824_config sy20276_cfg = अणु
	.vol_reg = 0x00,
	.mode_reg = 0x01,
	.enable_reg = 0x01,
	.vsel_min = 600000,
	.vsel_step = 10000,
	.vsel_count = 128,
पूर्ण;

अटल स्थिर काष्ठा sy8824_config sy20278_cfg = अणु
	.vol_reg = 0x00,
	.mode_reg = 0x01,
	.enable_reg = 0x01,
	.vsel_min = 762500,
	.vsel_step = 12500,
	.vsel_count = 64,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sy8824_dt_ids[] = अणु
	अणु
		.compatible = "silergy,sy8824c",
		.data = &sy8824c_cfg
	पूर्ण,
	अणु
		.compatible = "silergy,sy8824e",
		.data = &sy8824e_cfg
	पूर्ण,
	अणु
		.compatible = "silergy,sy20276",
		.data = &sy20276_cfg
	पूर्ण,
	अणु
		.compatible = "silergy,sy20278",
		.data = &sy20278_cfg
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sy8824_dt_ids);

अटल स्थिर काष्ठा i2c_device_id sy8824_id[] = अणु
	अणु "sy8824", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sy8824_id);

अटल काष्ठा i2c_driver sy8824_regulator_driver = अणु
	.driver = अणु
		.name = "sy8824-regulator",
		.of_match_table = of_match_ptr(sy8824_dt_ids),
	पूर्ण,
	.probe_new = sy8824_i2c_probe,
	.id_table = sy8824_id,
पूर्ण;
module_i2c_driver(sy8824_regulator_driver);

MODULE_AUTHOR("Jisheng Zhang <jszhang@kernel.org>");
MODULE_DESCRIPTION("SY8824C/SY8824E regulator driver");
MODULE_LICENSE("GPL v2");
