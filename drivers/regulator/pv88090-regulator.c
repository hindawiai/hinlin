<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// pv88090-regulator.c - Regulator device driver क्रम PV88090
// Copyright (C) 2015  Powerventure Semiconductor Ltd.

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
#समावेश <linux/regulator/of_regulator.h>
#समावेश "pv88090-regulator.h"

#घोषणा PV88090_MAX_REGULATORS	5

/* PV88090 REGULATOR IDs */
क्रमागत अणु
	/* BUCKs */
	PV88090_ID_BUCK1,
	PV88090_ID_BUCK2,
	PV88090_ID_BUCK3,

	/* LDOs */
	PV88090_ID_LDO1,
	PV88090_ID_LDO2,
पूर्ण;

काष्ठा pv88090_regulator अणु
	काष्ठा regulator_desc desc;
	अचिन्हित पूर्णांक conf;
	अचिन्हित पूर्णांक conf2;
पूर्ण;

काष्ठा pv88090 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा regulator_dev *rdev[PV88090_MAX_REGULATORS];
पूर्ण;

काष्ठा pv88090_buck_voltage अणु
	पूर्णांक min_uV;
	पूर्णांक max_uV;
	पूर्णांक uV_step;
पूर्ण;

अटल स्थिर काष्ठा regmap_config pv88090_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

/* Current limits array (in uA) क्रम BUCK1, BUCK2, BUCK3.
 *  Entry indexes corresponds to रेजिस्टर values.
 */

अटल स्थिर अचिन्हित पूर्णांक pv88090_buck1_limits[] = अणु
	 220000,  440000,  660000,  880000, 1100000, 1320000, 1540000, 1760000,
	1980000, 2200000, 2420000, 2640000, 2860000, 3080000, 3300000, 3520000,
	3740000, 3960000, 4180000, 4400000, 4620000, 4840000, 5060000, 5280000,
	5500000, 5720000, 5940000, 6160000, 6380000, 6600000, 6820000, 7040000
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pv88090_buck23_limits[] = अणु
	1496000, 2393000, 3291000, 4189000
पूर्ण;

अटल स्थिर काष्ठा pv88090_buck_voltage pv88090_buck_vol[3] = अणु
	अणु
		.min_uV = 600000,
		.max_uV = 1393750,
		.uV_step = 6250,
	पूर्ण,

	अणु
		.min_uV = 1400000,
		.max_uV = 2193750,
		.uV_step = 6250,
	पूर्ण,
	अणु
		.min_uV = 1250000,
		.max_uV = 2837500,
		.uV_step = 12500,
	पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक pv88090_buck_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा pv88090_regulator *info = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक data;
	पूर्णांक ret, mode = 0;

	ret = regmap_पढ़ो(rdev->regmap, info->conf, &data);
	अगर (ret < 0)
		वापस ret;

	चयन (data & PV88090_BUCK1_MODE_MASK) अणु
	हाल PV88090_BUCK_MODE_SYNC:
		mode = REGULATOR_MODE_FAST;
		अवरोध;
	हाल PV88090_BUCK_MODE_AUTO:
		mode = REGULATOR_MODE_NORMAL;
		अवरोध;
	हाल PV88090_BUCK_MODE_SLEEP:
		mode = REGULATOR_MODE_STANDBY;
		अवरोध;
	पूर्ण

	वापस mode;
पूर्ण

अटल पूर्णांक pv88090_buck_set_mode(काष्ठा regulator_dev *rdev,
					अचिन्हित पूर्णांक mode)
अणु
	काष्ठा pv88090_regulator *info = rdev_get_drvdata(rdev);
	पूर्णांक val = 0;

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		val = PV88090_BUCK_MODE_SYNC;
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		val = PV88090_BUCK_MODE_AUTO;
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		val = PV88090_BUCK_MODE_SLEEP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(rdev->regmap, info->conf,
					PV88090_BUCK1_MODE_MASK, val);
पूर्ण

अटल स्थिर काष्ठा regulator_ops pv88090_buck_ops = अणु
	.get_mode = pv88090_buck_get_mode,
	.set_mode = pv88090_buck_set_mode,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.set_current_limit = regulator_set_current_limit_regmap,
	.get_current_limit = regulator_get_current_limit_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops pv88090_lकरो_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_linear,
पूर्ण;

#घोषणा PV88090_BUCK(chip, regl_name, min, step, max, limits_array) \
अणु\
	.desc	=	अणु\
		.id = chip##_ID_##regl_name,\
		.name = __stringअगरy(chip##_##regl_name),\
		.of_match = of_match_ptr(#regl_name),\
		.regulators_node = of_match_ptr("regulators"),\
		.type = REGULATOR_VOLTAGE,\
		.owner = THIS_MODULE,\
		.ops = &pv88090_buck_ops,\
		.min_uV = min, \
		.uV_step = step, \
		.n_voltages = ((max) - (min))/(step) + 1, \
		.enable_reg = PV88090_REG_##regl_name##_CONF0, \
		.enable_mask = PV88090_##regl_name##_EN, \
		.vsel_reg = PV88090_REG_##regl_name##_CONF0, \
		.vsel_mask = PV88090_V##regl_name##_MASK, \
		.curr_table = limits_array, \
		.n_current_limits = ARRAY_SIZE(limits_array), \
		.csel_reg = PV88090_REG_##regl_name##_CONF1, \
		.csel_mask = PV88090_##regl_name##_ILIM_MASK, \
	पूर्ण,\
	.conf = PV88090_REG_##regl_name##_CONF1, \
	.conf2 = PV88090_REG_##regl_name##_CONF2, \
पूर्ण

#घोषणा PV88090_LDO(chip, regl_name, min, step, max) \
अणु\
	.desc	=	अणु\
		.id = chip##_ID_##regl_name,\
		.name = __stringअगरy(chip##_##regl_name),\
		.of_match = of_match_ptr(#regl_name),\
		.regulators_node = of_match_ptr("regulators"),\
		.type = REGULATOR_VOLTAGE,\
		.owner = THIS_MODULE,\
		.ops = &pv88090_lकरो_ops,\
		.min_uV = min, \
		.uV_step = step, \
		.n_voltages = ((max) - (min))/(step) + 1, \
		.enable_reg = PV88090_REG_##regl_name##_CONT, \
		.enable_mask = PV88090_##regl_name##_EN, \
		.vsel_reg = PV88090_REG_##regl_name##_CONT, \
		.vsel_mask = PV88090_V##regl_name##_MASK, \
	पूर्ण,\
पूर्ण

अटल काष्ठा pv88090_regulator pv88090_regulator_info[] = अणु
	PV88090_BUCK(PV88090, BUCK1, 600000, 6250, 1393750,
		pv88090_buck1_limits),
	PV88090_BUCK(PV88090, BUCK2, 600000, 6250, 1393750,
		pv88090_buck23_limits),
	PV88090_BUCK(PV88090, BUCK3, 600000, 6250, 1393750,
		pv88090_buck23_limits),
	PV88090_LDO(PV88090, LDO1, 1200000, 50000, 4350000),
	PV88090_LDO(PV88090, LDO2,  650000, 25000, 2225000),
पूर्ण;

अटल irqवापस_t pv88090_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pv88090 *chip = data;
	पूर्णांक i, reg_val, err, ret = IRQ_NONE;

	err = regmap_पढ़ो(chip->regmap, PV88090_REG_EVENT_A, &reg_val);
	अगर (err < 0)
		जाओ error_i2c;

	अगर (reg_val & PV88090_E_VDD_FLT) अणु
		क्रम (i = 0; i < PV88090_MAX_REGULATORS; i++) अणु
			अगर (chip->rdev[i] != शून्य)
				regulator_notअगरier_call_chain(chip->rdev[i],
					REGULATOR_EVENT_UNDER_VOLTAGE,
					शून्य);
		पूर्ण

		err = regmap_ग_लिखो(chip->regmap, PV88090_REG_EVENT_A,
			PV88090_E_VDD_FLT);
		अगर (err < 0)
			जाओ error_i2c;

		ret = IRQ_HANDLED;
	पूर्ण

	अगर (reg_val & PV88090_E_OVER_TEMP) अणु
		क्रम (i = 0; i < PV88090_MAX_REGULATORS; i++) अणु
			अगर (chip->rdev[i] != शून्य)
				regulator_notअगरier_call_chain(chip->rdev[i],
					REGULATOR_EVENT_OVER_TEMP,
					शून्य);
		पूर्ण

		err = regmap_ग_लिखो(chip->regmap, PV88090_REG_EVENT_A,
			PV88090_E_OVER_TEMP);
		अगर (err < 0)
			जाओ error_i2c;

		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;

error_i2c:
	dev_err(chip->dev, "I2C error : %d\n", err);
	वापस IRQ_NONE;
पूर्ण

/*
 * I2C driver पूर्णांकerface functions
 */
अटल पूर्णांक pv88090_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा regulator_init_data *init_data = dev_get_platdata(&i2c->dev);
	काष्ठा pv88090 *chip;
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक error, i, ret = 0;
	अचिन्हित पूर्णांक conf2, range, index;

	chip = devm_kzalloc(&i2c->dev, माप(काष्ठा pv88090), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->dev = &i2c->dev;
	chip->regmap = devm_regmap_init_i2c(i2c, &pv88090_regmap_config);
	अगर (IS_ERR(chip->regmap)) अणु
		error = PTR_ERR(chip->regmap);
		dev_err(chip->dev, "Failed to allocate register map: %d\n",
			error);
		वापस error;
	पूर्ण

	i2c_set_clientdata(i2c, chip);

	अगर (i2c->irq != 0) अणु
		ret = regmap_ग_लिखो(chip->regmap, PV88090_REG_MASK_A, 0xFF);
		अगर (ret < 0) अणु
			dev_err(chip->dev,
				"Failed to mask A reg: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = regmap_ग_लिखो(chip->regmap, PV88090_REG_MASK_B, 0xFF);
		अगर (ret < 0) अणु
			dev_err(chip->dev,
				"Failed to mask B reg: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = devm_request_thपढ़ोed_irq(&i2c->dev, i2c->irq, शून्य,
					pv88090_irq_handler,
					IRQF_TRIGGER_LOW|IRQF_ONESHOT,
					"pv88090", chip);
		अगर (ret != 0) अणु
			dev_err(chip->dev, "Failed to request IRQ: %d\n",
				i2c->irq);
			वापस ret;
		पूर्ण

		ret = regmap_update_bits(chip->regmap, PV88090_REG_MASK_A,
			PV88090_M_VDD_FLT | PV88090_M_OVER_TEMP, 0);
		अगर (ret < 0) अणु
			dev_err(chip->dev,
				"Failed to update mask reg: %d\n", ret);
			वापस ret;
		पूर्ण

	पूर्ण अन्यथा अणु
		dev_warn(chip->dev, "No IRQ configured\n");
	पूर्ण

	config.dev = chip->dev;
	config.regmap = chip->regmap;

	क्रम (i = 0; i < PV88090_MAX_REGULATORS; i++) अणु
		अगर (init_data)
			config.init_data = &init_data[i];

		अगर (i == PV88090_ID_BUCK2 || i == PV88090_ID_BUCK3) अणु
			ret = regmap_पढ़ो(chip->regmap,
				pv88090_regulator_info[i].conf2, &conf2);
			अगर (ret < 0)
				वापस ret;

			conf2 = (conf2 >> PV88090_BUCK_VDAC_RANGE_SHIFT) &
				PV88090_BUCK_VDAC_RANGE_MASK;

			ret = regmap_पढ़ो(chip->regmap,
				PV88090_REG_BUCK_FOLD_RANGE, &range);
			अगर (ret < 0)
				वापस ret;

			range = (range >>
				 (PV88090_BUCK_VRANGE_GAIN_SHIFT + i - 1)) &
				PV88090_BUCK_VRANGE_GAIN_MASK;
			index = ((range << 1) | conf2);
			अगर (index > PV88090_ID_BUCK3) अणु
				dev_err(chip->dev,
					"Invalid index(%d)\n", index);
				वापस -EINVAL;
			पूर्ण

			pv88090_regulator_info[i].desc.min_uV
				= pv88090_buck_vol[index].min_uV;
			pv88090_regulator_info[i].desc.uV_step
				= pv88090_buck_vol[index].uV_step;
			pv88090_regulator_info[i].desc.n_voltages
				= ((pv88090_buck_vol[index].max_uV)
				- (pv88090_buck_vol[index].min_uV))
				/(pv88090_buck_vol[index].uV_step) + 1;
		पूर्ण

		config.driver_data = (व्योम *)&pv88090_regulator_info[i];
		chip->rdev[i] = devm_regulator_रेजिस्टर(chip->dev,
			&pv88090_regulator_info[i].desc, &config);
		अगर (IS_ERR(chip->rdev[i])) अणु
			dev_err(chip->dev,
				"Failed to register PV88090 regulator\n");
			वापस PTR_ERR(chip->rdev[i]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pv88090_i2c_id[] = अणु
	अणु"pv88090", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pv88090_i2c_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pv88090_dt_ids[] = अणु
	अणु .compatible = "pvs,pv88090", .data = &pv88090_i2c_id[0] पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pv88090_dt_ids);
#पूर्ण_अगर

अटल काष्ठा i2c_driver pv88090_regulator_driver = अणु
	.driver = अणु
		.name = "pv88090",
		.of_match_table = of_match_ptr(pv88090_dt_ids),
	पूर्ण,
	.probe_new = pv88090_i2c_probe,
	.id_table = pv88090_i2c_id,
पूर्ण;

module_i2c_driver(pv88090_regulator_driver);

MODULE_AUTHOR("James Ban <James.Ban.opensource@diasemi.com>");
MODULE_DESCRIPTION("Regulator device driver for Powerventure PV88090");
MODULE_LICENSE("GPL");
