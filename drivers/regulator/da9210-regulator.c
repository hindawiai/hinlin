<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// da9210-regulator.c - Regulator device driver क्रम DA9210
// Copyright (C) 2013  Dialog Semiconductor Ltd.

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/regmap.h>

#समावेश "da9210-regulator.h"

काष्ठा da9210 अणु
	काष्ठा regulator_dev *rdev;
	काष्ठा regmap *regmap;
पूर्ण;

अटल स्थिर काष्ठा regmap_config da9210_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops da9210_buck_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.set_current_limit = regulator_set_current_limit_regmap,
	.get_current_limit = regulator_get_current_limit_regmap,
पूर्ण;

/* Default limits measured in millivolts and milliamps */
#घोषणा DA9210_MIN_MV		300
#घोषणा DA9210_MAX_MV		1570
#घोषणा DA9210_STEP_MV		10

/* Current limits क्रम buck (uA) indices corresponds with रेजिस्टर values */
अटल स्थिर अचिन्हित पूर्णांक da9210_buck_limits[] = अणु
	1600000, 1800000, 2000000, 2200000, 2400000, 2600000, 2800000, 3000000,
	3200000, 3400000, 3600000, 3800000, 4000000, 4200000, 4400000, 4600000
पूर्ण;

अटल स्थिर काष्ठा regulator_desc da9210_reg = अणु
	.name = "DA9210",
	.id = 0,
	.ops = &da9210_buck_ops,
	.type = REGULATOR_VOLTAGE,
	.n_voltages = ((DA9210_MAX_MV - DA9210_MIN_MV) / DA9210_STEP_MV) + 1,
	.min_uV = (DA9210_MIN_MV * 1000),
	.uV_step = (DA9210_STEP_MV * 1000),
	.vsel_reg = DA9210_REG_VBUCK_A,
	.vsel_mask = DA9210_VBUCK_MASK,
	.enable_reg = DA9210_REG_BUCK_CONT,
	.enable_mask = DA9210_BUCK_EN,
	.owner = THIS_MODULE,
	.curr_table = da9210_buck_limits,
	.n_current_limits = ARRAY_SIZE(da9210_buck_limits),
	.csel_reg = DA9210_REG_BUCK_ILIM,
	.csel_mask = DA9210_BUCK_ILIM_MASK,
पूर्ण;

अटल irqवापस_t da9210_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9210 *chip = data;
	अचिन्हित पूर्णांक val, handled = 0;
	पूर्णांक error, ret = IRQ_NONE;

	error = regmap_पढ़ो(chip->regmap, DA9210_REG_EVENT_B, &val);
	अगर (error < 0)
		जाओ error_i2c;

	अगर (val & DA9210_E_OVCURR) अणु
		regulator_notअगरier_call_chain(chip->rdev,
					      REGULATOR_EVENT_OVER_CURRENT,
					      शून्य);
		handled |= DA9210_E_OVCURR;
	पूर्ण
	अगर (val & DA9210_E_NPWRGOOD) अणु
		regulator_notअगरier_call_chain(chip->rdev,
					      REGULATOR_EVENT_UNDER_VOLTAGE,
					      शून्य);
		handled |= DA9210_E_NPWRGOOD;
	पूर्ण
	अगर (val & (DA9210_E_TEMP_WARN | DA9210_E_TEMP_CRIT)) अणु
		regulator_notअगरier_call_chain(chip->rdev,
					      REGULATOR_EVENT_OVER_TEMP, शून्य);
		handled |= val & (DA9210_E_TEMP_WARN | DA9210_E_TEMP_CRIT);
	पूर्ण
	अगर (val & DA9210_E_VMAX) अणु
		regulator_notअगरier_call_chain(chip->rdev,
					      REGULATOR_EVENT_REGULATION_OUT,
					      शून्य);
		handled |= DA9210_E_VMAX;
	पूर्ण

	अगर (handled) अणु
		/* Clear handled events */
		error = regmap_ग_लिखो(chip->regmap, DA9210_REG_EVENT_B, handled);
		अगर (error < 0)
			जाओ error_i2c;

		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;

error_i2c:
	dev_err(regmap_get_device(chip->regmap), "I2C error : %d\n", error);
	वापस ret;
पूर्ण

/*
 * I2C driver पूर्णांकerface functions
 */

अटल स्थिर काष्ठा of_device_id __maybe_unused da9210_dt_ids[] = अणु
	अणु .compatible = "dlg,da9210", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, da9210_dt_ids);

अटल पूर्णांक da9210_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा da9210 *chip;
	काष्ठा device *dev = &i2c->dev;
	काष्ठा da9210_pdata *pdata = dev_get_platdata(dev);
	काष्ठा regulator_dev *rdev = शून्य;
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक error;
	स्थिर काष्ठा of_device_id *match;

	अगर (i2c->dev.of_node && !pdata) अणु
		match = of_match_device(of_match_ptr(da9210_dt_ids),
						&i2c->dev);
		अगर (!match) अणु
			dev_err(&i2c->dev, "Error: No device match found\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	chip = devm_kzalloc(&i2c->dev, माप(काष्ठा da9210), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->regmap = devm_regmap_init_i2c(i2c, &da9210_regmap_config);
	अगर (IS_ERR(chip->regmap)) अणु
		error = PTR_ERR(chip->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			error);
		वापस error;
	पूर्ण

	config.dev = &i2c->dev;
	config.init_data = pdata ? &pdata->da9210_स्थिरraपूर्णांकs :
		of_get_regulator_init_data(dev, dev->of_node, &da9210_reg);
	config.driver_data = chip;
	config.regmap = chip->regmap;
	config.of_node = dev->of_node;

	/* Mask all पूर्णांकerrupt sources to deनिश्चित पूर्णांकerrupt line */
	error = regmap_ग_लिखो(chip->regmap, DA9210_REG_MASK_A, ~0);
	अगर (!error)
		error = regmap_ग_लिखो(chip->regmap, DA9210_REG_MASK_B, ~0);
	अगर (error) अणु
		dev_err(&i2c->dev, "Failed to write to mask reg: %d\n", error);
		वापस error;
	पूर्ण

	rdev = devm_regulator_रेजिस्टर(&i2c->dev, &da9210_reg, &config);
	अगर (IS_ERR(rdev)) अणु
		dev_err(&i2c->dev, "Failed to register DA9210 regulator\n");
		वापस PTR_ERR(rdev);
	पूर्ण

	chip->rdev = rdev;
	अगर (i2c->irq) अणु
		error = devm_request_thपढ़ोed_irq(&i2c->dev, i2c->irq, शून्य,
						  da9210_irq_handler,
						  IRQF_TRIGGER_LOW |
						  IRQF_ONESHOT | IRQF_SHARED,
						  "da9210", chip);
		अगर (error) अणु
			dev_err(&i2c->dev, "Failed to request IRQ%u: %d\n",
				i2c->irq, error);
			वापस error;
		पूर्ण

		error = regmap_update_bits(chip->regmap, DA9210_REG_MASK_B,
					 DA9210_M_OVCURR | DA9210_M_NPWRGOOD |
					 DA9210_M_TEMP_WARN |
					 DA9210_M_TEMP_CRIT | DA9210_M_VMAX, 0);
		अगर (error < 0) अणु
			dev_err(&i2c->dev, "Failed to update mask reg: %d\n",
				error);
			वापस error;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_warn(&i2c->dev, "No IRQ configured\n");
	पूर्ण

	i2c_set_clientdata(i2c, chip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id da9210_i2c_id[] = अणु
	अणु"da9210", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, da9210_i2c_id);

अटल काष्ठा i2c_driver da9210_regulator_driver = अणु
	.driver = अणु
		.name = "da9210",
		.of_match_table = of_match_ptr(da9210_dt_ids),
	पूर्ण,
	.probe_new = da9210_i2c_probe,
	.id_table = da9210_i2c_id,
पूर्ण;

module_i2c_driver(da9210_regulator_driver);

MODULE_AUTHOR("S Twiss <stwiss.opensource@diasemi.com>");
MODULE_DESCRIPTION("Regulator device driver for Dialog DA9210");
MODULE_LICENSE("GPL v2");
