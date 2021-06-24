<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// pv88060-regulator.c - Regulator device driver क्रम PV88060
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
#समावेश "pv88060-regulator.h"

#घोषणा PV88060_MAX_REGULATORS	14

/* PV88060 REGULATOR IDs */
क्रमागत अणु
	/* BUCKs */
	PV88060_ID_BUCK1,

	/* LDOs */
	PV88060_ID_LDO1,
	PV88060_ID_LDO2,
	PV88060_ID_LDO3,
	PV88060_ID_LDO4,
	PV88060_ID_LDO5,
	PV88060_ID_LDO6,
	PV88060_ID_LDO7,

	/* SWTs */
	PV88060_ID_SW1,
	PV88060_ID_SW2,
	PV88060_ID_SW3,
	PV88060_ID_SW4,
	PV88060_ID_SW5,
	PV88060_ID_SW6,
पूर्ण;

काष्ठा pv88060_regulator अणु
	काष्ठा regulator_desc desc;
	अचिन्हित पूर्णांक conf;		/* buck configuration रेजिस्टर */
पूर्ण;

काष्ठा pv88060 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा regulator_dev *rdev[PV88060_MAX_REGULATORS];
पूर्ण;

अटल स्थिर काष्ठा regmap_config pv88060_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

/* Current limits array (in uA) क्रम BUCK1
 * Entry indexes corresponds to रेजिस्टर values.
 */

अटल स्थिर अचिन्हित पूर्णांक pv88060_buck1_limits[] = अणु
	1496000, 2393000, 3291000, 4189000
पूर्ण;

अटल अचिन्हित पूर्णांक pv88060_buck_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा pv88060_regulator *info = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक data;
	पूर्णांक ret, mode = 0;

	ret = regmap_पढ़ो(rdev->regmap, info->conf, &data);
	अगर (ret < 0)
		वापस ret;

	चयन (data & PV88060_BUCK_MODE_MASK) अणु
	हाल PV88060_BUCK_MODE_SYNC:
		mode = REGULATOR_MODE_FAST;
		अवरोध;
	हाल PV88060_BUCK_MODE_AUTO:
		mode = REGULATOR_MODE_NORMAL;
		अवरोध;
	हाल PV88060_BUCK_MODE_SLEEP:
		mode = REGULATOR_MODE_STANDBY;
		अवरोध;
	पूर्ण

	वापस mode;
पूर्ण

अटल पूर्णांक pv88060_buck_set_mode(काष्ठा regulator_dev *rdev,
					अचिन्हित पूर्णांक mode)
अणु
	काष्ठा pv88060_regulator *info = rdev_get_drvdata(rdev);
	पूर्णांक val = 0;

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		val = PV88060_BUCK_MODE_SYNC;
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		val = PV88060_BUCK_MODE_AUTO;
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		val = PV88060_BUCK_MODE_SLEEP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(rdev->regmap, info->conf,
					PV88060_BUCK_MODE_MASK, val);
पूर्ण

अटल स्थिर काष्ठा regulator_ops pv88060_buck_ops = अणु
	.get_mode = pv88060_buck_get_mode,
	.set_mode = pv88060_buck_set_mode,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.set_current_limit = regulator_set_current_limit_regmap,
	.get_current_limit = regulator_get_current_limit_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops pv88060_lकरो_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_linear,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops pv88060_sw_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
पूर्ण;

#घोषणा PV88060_BUCK(chip, regl_name, min, step, max, limits_array) \
अणु\
	.desc	=	अणु\
		.id = chip##_ID_##regl_name,\
		.name = __stringअगरy(chip##_##regl_name),\
		.of_match = of_match_ptr(#regl_name),\
		.regulators_node = of_match_ptr("regulators"),\
		.type = REGULATOR_VOLTAGE,\
		.owner = THIS_MODULE,\
		.ops = &pv88060_buck_ops,\
		.min_uV = min,\
		.uV_step = step,\
		.n_voltages = ((max) - (min))/(step) + 1,\
		.enable_reg = PV88060_REG_##regl_name##_CONF0,\
		.enable_mask = PV88060_BUCK_EN, \
		.vsel_reg = PV88060_REG_##regl_name##_CONF0,\
		.vsel_mask = PV88060_VBUCK_MASK,\
		.curr_table = limits_array,\
		.n_current_limits = ARRAY_SIZE(limits_array),\
		.csel_reg = PV88060_REG_##regl_name##_CONF1,\
		.csel_mask = PV88060_BUCK_ILIM_MASK,\
	पूर्ण,\
	.conf = PV88060_REG_##regl_name##_CONF1,\
पूर्ण

#घोषणा PV88060_LDO(chip, regl_name, min, step, max) \
अणु\
	.desc	=	अणु\
		.id = chip##_ID_##regl_name,\
		.name = __stringअगरy(chip##_##regl_name),\
		.of_match = of_match_ptr(#regl_name),\
		.regulators_node = of_match_ptr("regulators"),\
		.type = REGULATOR_VOLTAGE,\
		.owner = THIS_MODULE,\
		.ops = &pv88060_lकरो_ops,\
		.min_uV = min, \
		.uV_step = step, \
		.n_voltages = (step) ? ((max - min) / step + 1) : 1, \
		.enable_reg = PV88060_REG_##regl_name##_CONF, \
		.enable_mask = PV88060_LDO_EN, \
		.vsel_reg = PV88060_REG_##regl_name##_CONF, \
		.vsel_mask = PV88060_VLDO_MASK, \
	पूर्ण,\
पूर्ण

#घोषणा PV88060_SW(chip, regl_name, max) \
अणु\
	.desc	=	अणु\
		.id = chip##_ID_##regl_name,\
		.name = __stringअगरy(chip##_##regl_name),\
		.of_match = of_match_ptr(#regl_name),\
		.regulators_node = of_match_ptr("regulators"),\
		.type = REGULATOR_VOLTAGE,\
		.owner = THIS_MODULE,\
		.ops = &pv88060_sw_ops,\
		.fixed_uV = max,\
		.n_voltages = 1,\
		.enable_reg = PV88060_REG_##regl_name##_CONF,\
		.enable_mask = PV88060_SW_EN,\
	पूर्ण,\
पूर्ण

अटल स्थिर काष्ठा pv88060_regulator pv88060_regulator_info[] = अणु
	PV88060_BUCK(PV88060, BUCK1, 2800000, 12500, 4387500,
		pv88060_buck1_limits),
	PV88060_LDO(PV88060, LDO1, 1200000, 50000, 3350000),
	PV88060_LDO(PV88060, LDO2, 1200000, 50000, 3350000),
	PV88060_LDO(PV88060, LDO3, 1200000, 50000, 3350000),
	PV88060_LDO(PV88060, LDO4, 1200000, 50000, 3350000),
	PV88060_LDO(PV88060, LDO5, 1200000, 50000, 3350000),
	PV88060_LDO(PV88060, LDO6, 1200000, 50000, 3350000),
	PV88060_LDO(PV88060, LDO7, 1200000, 50000, 3350000),
	PV88060_SW(PV88060, SW1, 5000000),
	PV88060_SW(PV88060, SW2, 5000000),
	PV88060_SW(PV88060, SW3, 5000000),
	PV88060_SW(PV88060, SW4, 5000000),
	PV88060_SW(PV88060, SW5, 5000000),
	PV88060_SW(PV88060, SW6, 5000000),
पूर्ण;

अटल irqवापस_t pv88060_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pv88060 *chip = data;
	पूर्णांक i, reg_val, err, ret = IRQ_NONE;

	err = regmap_पढ़ो(chip->regmap, PV88060_REG_EVENT_A, &reg_val);
	अगर (err < 0)
		जाओ error_i2c;

	अगर (reg_val & PV88060_E_VDD_FLT) अणु
		क्रम (i = 0; i < PV88060_MAX_REGULATORS; i++) अणु
			अगर (chip->rdev[i] != शून्य)
				regulator_notअगरier_call_chain(chip->rdev[i],
					REGULATOR_EVENT_UNDER_VOLTAGE,
					शून्य);
		पूर्ण

		err = regmap_ग_लिखो(chip->regmap, PV88060_REG_EVENT_A,
			PV88060_E_VDD_FLT);
		अगर (err < 0)
			जाओ error_i2c;

		ret = IRQ_HANDLED;
	पूर्ण

	अगर (reg_val & PV88060_E_OVER_TEMP) अणु
		क्रम (i = 0; i < PV88060_MAX_REGULATORS; i++) अणु
			अगर (chip->rdev[i] != शून्य)
				regulator_notअगरier_call_chain(chip->rdev[i],
					REGULATOR_EVENT_OVER_TEMP,
					शून्य);
		पूर्ण

		err = regmap_ग_लिखो(chip->regmap, PV88060_REG_EVENT_A,
			PV88060_E_OVER_TEMP);
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
अटल पूर्णांक pv88060_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा regulator_init_data *init_data = dev_get_platdata(&i2c->dev);
	काष्ठा pv88060 *chip;
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक error, i, ret = 0;

	chip = devm_kzalloc(&i2c->dev, माप(काष्ठा pv88060), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->dev = &i2c->dev;
	chip->regmap = devm_regmap_init_i2c(i2c, &pv88060_regmap_config);
	अगर (IS_ERR(chip->regmap)) अणु
		error = PTR_ERR(chip->regmap);
		dev_err(chip->dev, "Failed to allocate register map: %d\n",
			error);
		वापस error;
	पूर्ण

	i2c_set_clientdata(i2c, chip);

	अगर (i2c->irq != 0) अणु
		ret = regmap_ग_लिखो(chip->regmap, PV88060_REG_MASK_A, 0xFF);
		अगर (ret < 0) अणु
			dev_err(chip->dev,
				"Failed to mask A reg: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = regmap_ग_लिखो(chip->regmap, PV88060_REG_MASK_B, 0xFF);
		अगर (ret < 0) अणु
			dev_err(chip->dev,
				"Failed to mask B reg: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = regmap_ग_लिखो(chip->regmap, PV88060_REG_MASK_C, 0xFF);
		अगर (ret < 0) अणु
			dev_err(chip->dev,
				"Failed to mask C reg: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = devm_request_thपढ़ोed_irq(&i2c->dev, i2c->irq, शून्य,
					pv88060_irq_handler,
					IRQF_TRIGGER_LOW|IRQF_ONESHOT,
					"pv88060", chip);
		अगर (ret != 0) अणु
			dev_err(chip->dev, "Failed to request IRQ: %d\n",
				i2c->irq);
			वापस ret;
		पूर्ण

		ret = regmap_update_bits(chip->regmap, PV88060_REG_MASK_A,
			PV88060_M_VDD_FLT | PV88060_M_OVER_TEMP, 0);
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

	क्रम (i = 0; i < PV88060_MAX_REGULATORS; i++) अणु
		अगर (init_data)
			config.init_data = &init_data[i];

		config.driver_data = (व्योम *)&pv88060_regulator_info[i];
		chip->rdev[i] = devm_regulator_रेजिस्टर(chip->dev,
			&pv88060_regulator_info[i].desc, &config);
		अगर (IS_ERR(chip->rdev[i])) अणु
			dev_err(chip->dev,
				"Failed to register PV88060 regulator\n");
			वापस PTR_ERR(chip->rdev[i]);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pv88060_i2c_id[] = अणु
	अणु"pv88060", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pv88060_i2c_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pv88060_dt_ids[] = अणु
	अणु .compatible = "pvs,pv88060", .data = &pv88060_i2c_id[0] पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pv88060_dt_ids);
#पूर्ण_अगर

अटल काष्ठा i2c_driver pv88060_regulator_driver = अणु
	.driver = अणु
		.name = "pv88060",
		.of_match_table = of_match_ptr(pv88060_dt_ids),
	पूर्ण,
	.probe_new = pv88060_i2c_probe,
	.id_table = pv88060_i2c_id,
पूर्ण;

module_i2c_driver(pv88060_regulator_driver);

MODULE_AUTHOR("James Ban <James.Ban.opensource@diasemi.com>");
MODULE_DESCRIPTION("Regulator device driver for Powerventure PV88060");
MODULE_LICENSE("GPL");
