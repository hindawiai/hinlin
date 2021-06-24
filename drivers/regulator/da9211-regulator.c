<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// da9211-regulator.c - Regulator device driver क्रम DA9211/DA9212
// /DA9213/DA9223/DA9214/DA9224/DA9215/DA9225
// Copyright (C) 2015  Dialog Semiconductor Ltd.

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regmap.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/regulator/da9211.h>
#समावेश <dt-bindings/regulator/dlg,da9211-regulator.h>
#समावेश "da9211-regulator.h"

/* DEVICE IDs */
#घोषणा DA9211_DEVICE_ID	0x22
#घोषणा DA9213_DEVICE_ID	0x23
#घोषणा DA9215_DEVICE_ID	0x24

/* DA9211 REGULATOR IDs */
#घोषणा DA9211_ID_BUCKA	0
#घोषणा DA9211_ID_BUCKB	1

काष्ठा da9211 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा da9211_pdata *pdata;
	काष्ठा regulator_dev *rdev[DA9211_MAX_REGULATORS];
	पूर्णांक num_regulator;
	पूर्णांक chip_irq;
	पूर्णांक chip_id;
पूर्ण;

अटल स्थिर काष्ठा regmap_range_cfg da9211_regmap_range[] = अणु
	अणु
		.selector_reg = DA9211_REG_PAGE_CON,
		.selector_mask  = DA9211_REG_PAGE_MASK,
		.selector_shअगरt = DA9211_REG_PAGE_SHIFT,
		.winकरोw_start = 0,
		.winकरोw_len = 256,
		.range_min = 0,
		.range_max = 5*128,
	पूर्ण,
पूर्ण;

अटल bool da9211_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल DA9211_REG_STATUS_A:
	हाल DA9211_REG_STATUS_B:
	हाल DA9211_REG_EVENT_A:
	हाल DA9211_REG_EVENT_B:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config da9211_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 5 * 128,
	.अस्थिर_reg = da9211_अस्थिर_reg,
	.cache_type = REGCACHE_RBTREE,
	.ranges = da9211_regmap_range,
	.num_ranges = ARRAY_SIZE(da9211_regmap_range),
पूर्ण;

/* Default limits measured in millivolts and milliamps */
#घोषणा DA9211_MIN_MV		300
#घोषणा DA9211_MAX_MV		1570
#घोषणा DA9211_STEP_MV		10

/* Current limits क्रम DA9211 buck (uA) indices
 * corresponds with रेजिस्टर values
 */
अटल स्थिर पूर्णांक da9211_current_limits[] = अणु
	2000000, 2200000, 2400000, 2600000, 2800000, 3000000, 3200000, 3400000,
	3600000, 3800000, 4000000, 4200000, 4400000, 4600000, 4800000, 5000000
पूर्ण;
/* Current limits क्रम DA9213 buck (uA) indices
 * corresponds with रेजिस्टर values
 */
अटल स्थिर पूर्णांक da9213_current_limits[] = अणु
	3000000, 3200000, 3400000, 3600000, 3800000, 4000000, 4200000, 4400000,
	4600000, 4800000, 5000000, 5200000, 5400000, 5600000, 5800000, 6000000
पूर्ण;
/* Current limits क्रम DA9215 buck (uA) indices
 * corresponds with रेजिस्टर values
 */
अटल स्थिर पूर्णांक da9215_current_limits[] = अणु
	4000000, 4200000, 4400000, 4600000, 4800000, 5000000, 5200000, 5400000,
	5600000, 5800000, 6000000, 6200000, 6400000, 6600000, 6800000, 7000000
पूर्ण;

अटल अचिन्हित पूर्णांक da9211_map_buck_mode(अचिन्हित पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल DA9211_BUCK_MODE_SLEEP:
		वापस REGULATOR_MODE_STANDBY;
	हाल DA9211_BUCK_MODE_SYNC:
		वापस REGULATOR_MODE_FAST;
	हाल DA9211_BUCK_MODE_AUTO:
		वापस REGULATOR_MODE_NORMAL;
	शेष:
		वापस REGULATOR_MODE_INVALID;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक da9211_buck_get_mode(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक id = rdev_get_id(rdev);
	काष्ठा da9211 *chip = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक data;
	पूर्णांक ret, mode = 0;

	ret = regmap_पढ़ो(chip->regmap, DA9211_REG_BUCKA_CONF+id, &data);
	अगर (ret < 0)
		वापस ret;

	चयन (data & 0x03) अणु
	हाल DA9211_BUCK_MODE_SYNC:
		mode = REGULATOR_MODE_FAST;
		अवरोध;
	हाल DA9211_BUCK_MODE_AUTO:
		mode = REGULATOR_MODE_NORMAL;
		अवरोध;
	हाल DA9211_BUCK_MODE_SLEEP:
		mode = REGULATOR_MODE_STANDBY;
		अवरोध;
	पूर्ण

	वापस mode;
पूर्ण

अटल पूर्णांक da9211_buck_set_mode(काष्ठा regulator_dev *rdev,
					अचिन्हित पूर्णांक mode)
अणु
	पूर्णांक id = rdev_get_id(rdev);
	काष्ठा da9211 *chip = rdev_get_drvdata(rdev);
	पूर्णांक val = 0;

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		val = DA9211_BUCK_MODE_SYNC;
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		val = DA9211_BUCK_MODE_AUTO;
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		val = DA9211_BUCK_MODE_SLEEP;
		अवरोध;
	पूर्ण

	वापस regmap_update_bits(chip->regmap, DA9211_REG_BUCKA_CONF+id,
					0x03, val);
पूर्ण

अटल पूर्णांक da9211_set_current_limit(काष्ठा regulator_dev *rdev, पूर्णांक min,
				    पूर्णांक max)
अणु
	पूर्णांक id = rdev_get_id(rdev);
	काष्ठा da9211 *chip = rdev_get_drvdata(rdev);
	पूर्णांक i, max_size;
	स्थिर पूर्णांक *current_limits;

	चयन (chip->chip_id) अणु
	हाल DA9211:
		current_limits = da9211_current_limits;
		max_size = ARRAY_SIZE(da9211_current_limits)-1;
		अवरोध;
	हाल DA9213:
		current_limits = da9213_current_limits;
		max_size = ARRAY_SIZE(da9213_current_limits)-1;
		अवरोध;
	हाल DA9215:
		current_limits = da9215_current_limits;
		max_size = ARRAY_SIZE(da9215_current_limits)-1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* search क्रम बंदst to maximum */
	क्रम (i = max_size; i >= 0; i--) अणु
		अगर (min <= current_limits[i] &&
		    max >= current_limits[i]) अणु
				वापस regmap_update_bits(chip->regmap,
					DA9211_REG_BUCK_ILIM,
					(0x0F << id*4), (i << id*4));
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक da9211_get_current_limit(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक id = rdev_get_id(rdev);
	काष्ठा da9211 *chip = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक data;
	पूर्णांक ret;
	स्थिर पूर्णांक *current_limits;

	चयन (chip->chip_id) अणु
	हाल DA9211:
		current_limits = da9211_current_limits;
		अवरोध;
	हाल DA9213:
		current_limits = da9213_current_limits;
		अवरोध;
	हाल DA9215:
		current_limits = da9215_current_limits;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = regmap_पढ़ो(chip->regmap, DA9211_REG_BUCK_ILIM, &data);
	अगर (ret < 0)
		वापस ret;

	/* select one of 16 values: 0000 (2000mA or 3000mA)
	 * to 1111 (5000mA or 6000mA).
	 */
	data = (data >> id*4) & 0x0F;
	वापस current_limits[data];
पूर्ण

अटल स्थिर काष्ठा regulator_ops da9211_buck_ops = अणु
	.get_mode = da9211_buck_get_mode,
	.set_mode = da9211_buck_set_mode,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.set_current_limit = da9211_set_current_limit,
	.get_current_limit = da9211_get_current_limit,
पूर्ण;

#घोषणा DA9211_BUCK(_id) \
अणु\
	.name = #_id,\
	.ops = &da9211_buck_ops,\
	.type = REGULATOR_VOLTAGE,\
	.id = DA9211_ID_##_id,\
	.n_voltages = (DA9211_MAX_MV - DA9211_MIN_MV) / DA9211_STEP_MV + 1,\
	.min_uV = (DA9211_MIN_MV * 1000),\
	.uV_step = (DA9211_STEP_MV * 1000),\
	.enable_reg = DA9211_REG_BUCKA_CONT + DA9211_ID_##_id,\
	.enable_mask = DA9211_BUCKA_EN,\
	.vsel_reg = DA9211_REG_VBUCKA_A + DA9211_ID_##_id * 2,\
	.vsel_mask = DA9211_VBUCK_MASK,\
	.owner = THIS_MODULE,\
	.of_map_mode = da9211_map_buck_mode,\
पूर्ण

अटल काष्ठा regulator_desc da9211_regulators[] = अणु
	DA9211_BUCK(BUCKA),
	DA9211_BUCK(BUCKB),
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल काष्ठा of_regulator_match da9211_matches[] = अणु
	[DA9211_ID_BUCKA] = अणु
		.name = "BUCKA",
		.desc = &da9211_regulators[DA9211_ID_BUCKA],
	पूर्ण,
	[DA9211_ID_BUCKB] = अणु
		.name = "BUCKB",
		.desc = &da9211_regulators[DA9211_ID_BUCKB],
	पूर्ण,
	पूर्ण;

अटल काष्ठा da9211_pdata *da9211_parse_regulators_dt(
		काष्ठा device *dev)
अणु
	काष्ठा da9211_pdata *pdata;
	काष्ठा device_node *node;
	पूर्णांक i, num, n;

	node = of_get_child_by_name(dev->of_node, "regulators");
	अगर (!node) अणु
		dev_err(dev, "regulators node not found\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	num = of_regulator_match(dev, node, da9211_matches,
				 ARRAY_SIZE(da9211_matches));
	of_node_put(node);
	अगर (num < 0) अणु
		dev_err(dev, "Failed to match regulators\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	pdata->num_buck = num;

	n = 0;
	क्रम (i = 0; i < ARRAY_SIZE(da9211_matches); i++) अणु
		अगर (!da9211_matches[i].init_data)
			जारी;

		pdata->init_data[n] = da9211_matches[i].init_data;
		pdata->reg_node[n] = da9211_matches[i].of_node;
		pdata->gpiod_ren[n] = devm_fwnode_gpiod_get(dev,
					of_fwnode_handle(pdata->reg_node[n]),
					"enable",
					GPIOD_OUT_HIGH |
						GPIOD_FLAGS_BIT_NONEXCLUSIVE,
					"da9211-enable");
		अगर (IS_ERR(pdata->gpiod_ren[n]))
			pdata->gpiod_ren[n] = शून्य;
		n++;
	पूर्ण

	वापस pdata;
पूर्ण
#अन्यथा
अटल काष्ठा da9211_pdata *da9211_parse_regulators_dt(
		काष्ठा device *dev)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण
#पूर्ण_अगर

अटल irqवापस_t da9211_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9211 *chip = data;
	पूर्णांक reg_val, err, ret = IRQ_NONE;

	err = regmap_पढ़ो(chip->regmap, DA9211_REG_EVENT_B, &reg_val);
	अगर (err < 0)
		जाओ error_i2c;

	अगर (reg_val & DA9211_E_OV_CURR_A) अणु
		regulator_notअगरier_call_chain(chip->rdev[0],
			REGULATOR_EVENT_OVER_CURRENT, शून्य);

		err = regmap_ग_लिखो(chip->regmap, DA9211_REG_EVENT_B,
			DA9211_E_OV_CURR_A);
		अगर (err < 0)
			जाओ error_i2c;

		ret = IRQ_HANDLED;
	पूर्ण

	अगर (reg_val & DA9211_E_OV_CURR_B) अणु
		regulator_notअगरier_call_chain(chip->rdev[1],
			REGULATOR_EVENT_OVER_CURRENT, शून्य);

		err = regmap_ग_लिखो(chip->regmap, DA9211_REG_EVENT_B,
			DA9211_E_OV_CURR_B);
		अगर (err < 0)
			जाओ error_i2c;

		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;

error_i2c:
	dev_err(chip->dev, "I2C error : %d\n", err);
	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक da9211_regulator_init(काष्ठा da9211 *chip)
अणु
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक data;

	ret = regmap_पढ़ो(chip->regmap, DA9211_REG_CONFIG_E, &data);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to read CONFIG_E reg: %d\n", ret);
		वापस ret;
	पूर्ण

	data &= DA9211_SLAVE_SEL;
	/* If configuration क्रम 1/2 bucks is dअगरferent between platक्रमm data
	 * and the रेजिस्टर, driver should निकास.
	 */
	अगर (chip->pdata->num_buck == 1 && data == 0x00)
		chip->num_regulator = 1;
	अन्यथा अगर (chip->pdata->num_buck == 2 && data != 0x00)
		chip->num_regulator = 2;
	अन्यथा अणु
		dev_err(chip->dev, "Configuration is mismatched\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < chip->num_regulator; i++) अणु
		config.init_data = chip->pdata->init_data[i];
		config.dev = chip->dev;
		config.driver_data = chip;
		config.regmap = chip->regmap;
		config.of_node = chip->pdata->reg_node[i];

		अगर (chip->pdata->gpiod_ren[i])
			config.ena_gpiod = chip->pdata->gpiod_ren[i];
		अन्यथा
			config.ena_gpiod = शून्य;

		/*
		 * Hand the GPIO descriptor management over to the regulator
		 * core, हटाओ it from GPIO devres management.
		 */
		अगर (config.ena_gpiod)
			devm_gpiod_unhinge(chip->dev, config.ena_gpiod);
		chip->rdev[i] = devm_regulator_रेजिस्टर(chip->dev,
			&da9211_regulators[i], &config);
		अगर (IS_ERR(chip->rdev[i])) अणु
			dev_err(chip->dev,
				"Failed to register DA9211 regulator\n");
			वापस PTR_ERR(chip->rdev[i]);
		पूर्ण

		अगर (chip->chip_irq != 0) अणु
			ret = regmap_update_bits(chip->regmap,
				DA9211_REG_MASK_B, DA9211_M_OV_CURR_A << i, 0);
			अगर (ret < 0) अणु
				dev_err(chip->dev,
					"Failed to update mask reg: %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * I2C driver पूर्णांकerface functions
 */
अटल पूर्णांक da9211_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा da9211 *chip;
	पूर्णांक error, ret;
	अचिन्हित पूर्णांक data;

	chip = devm_kzalloc(&i2c->dev, माप(काष्ठा da9211), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->dev = &i2c->dev;
	chip->regmap = devm_regmap_init_i2c(i2c, &da9211_regmap_config);
	अगर (IS_ERR(chip->regmap)) अणु
		error = PTR_ERR(chip->regmap);
		dev_err(chip->dev, "Failed to allocate register map: %d\n",
			error);
		वापस error;
	पूर्ण

	i2c_set_clientdata(i2c, chip);

	chip->pdata = i2c->dev.platक्रमm_data;

	ret = regmap_पढ़ो(chip->regmap, DA9211_REG_DEVICE_ID, &data);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to read DEVICE_ID reg: %d\n", ret);
		वापस ret;
	पूर्ण

	चयन (data) अणु
	हाल DA9211_DEVICE_ID:
		chip->chip_id = DA9211;
		अवरोध;
	हाल DA9213_DEVICE_ID:
		chip->chip_id = DA9213;
		अवरोध;
	हाल DA9215_DEVICE_ID:
		chip->chip_id = DA9215;
		अवरोध;
	शेष:
		dev_err(chip->dev, "Unsupported device id = 0x%x.\n", data);
		वापस -ENODEV;
	पूर्ण

	अगर (!chip->pdata)
		chip->pdata = da9211_parse_regulators_dt(chip->dev);

	अगर (IS_ERR(chip->pdata)) अणु
		dev_err(chip->dev, "No regulators defined for the platform\n");
		वापस PTR_ERR(chip->pdata);
	पूर्ण

	chip->chip_irq = i2c->irq;

	अगर (chip->chip_irq != 0) अणु
		ret = devm_request_thपढ़ोed_irq(chip->dev, chip->chip_irq, शून्य,
					da9211_irq_handler,
					IRQF_TRIGGER_LOW|IRQF_ONESHOT,
					"da9211", chip);
		अगर (ret != 0) अणु
			dev_err(chip->dev, "Failed to request IRQ: %d\n",
				chip->chip_irq);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_warn(chip->dev, "No IRQ configured\n");
	पूर्ण

	ret = da9211_regulator_init(chip);

	अगर (ret < 0)
		dev_err(chip->dev, "Failed to initialize regulator: %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id da9211_i2c_id[] = अणु
	अणु"da9211", DA9211पूर्ण,
	अणु"da9212", DA9212पूर्ण,
	अणु"da9213", DA9213पूर्ण,
	अणु"da9223", DA9223पूर्ण,
	अणु"da9214", DA9214पूर्ण,
	अणु"da9224", DA9224पूर्ण,
	अणु"da9215", DA9215पूर्ण,
	अणु"da9225", DA9225पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, da9211_i2c_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id da9211_dt_ids[] = अणु
	अणु .compatible = "dlg,da9211", .data = &da9211_i2c_id[0] पूर्ण,
	अणु .compatible = "dlg,da9212", .data = &da9211_i2c_id[1] पूर्ण,
	अणु .compatible = "dlg,da9213", .data = &da9211_i2c_id[2] पूर्ण,
	अणु .compatible = "dlg,da9223", .data = &da9211_i2c_id[3] पूर्ण,
	अणु .compatible = "dlg,da9214", .data = &da9211_i2c_id[4] पूर्ण,
	अणु .compatible = "dlg,da9224", .data = &da9211_i2c_id[5] पूर्ण,
	अणु .compatible = "dlg,da9215", .data = &da9211_i2c_id[6] पूर्ण,
	अणु .compatible = "dlg,da9225", .data = &da9211_i2c_id[7] पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, da9211_dt_ids);
#पूर्ण_अगर

अटल काष्ठा i2c_driver da9211_regulator_driver = अणु
	.driver = अणु
		.name = "da9211",
		.of_match_table = of_match_ptr(da9211_dt_ids),
	पूर्ण,
	.probe_new = da9211_i2c_probe,
	.id_table = da9211_i2c_id,
पूर्ण;

module_i2c_driver(da9211_regulator_driver);

MODULE_AUTHOR("James Ban <James.Ban.opensource@diasemi.com>");
MODULE_DESCRIPTION("DA9211/DA9212/DA9213/DA9223/DA9214/DA9224/DA9215/DA9225 regulator driver");
MODULE_LICENSE("GPL");
