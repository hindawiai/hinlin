<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// pv88080-regulator.c - Regulator device driver क्रम PV88080
// Copyright (C) 2016  Powerventure Semiconductor Ltd.

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regmap.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश "pv88080-regulator.h"

#घोषणा PV88080_MAX_REGULATORS	4

/* PV88080 REGULATOR IDs */
क्रमागत अणु
	/* BUCKs */
	PV88080_ID_BUCK1,
	PV88080_ID_BUCK2,
	PV88080_ID_BUCK3,
	PV88080_ID_HVBUCK,
पूर्ण;

क्रमागत pv88080_types अणु
	TYPE_PV88080_AA,
	TYPE_PV88080_BA,
पूर्ण;

काष्ठा pv88080_regulator अणु
	काष्ठा regulator_desc desc;
	अचिन्हित पूर्णांक mode_reg;
	अचिन्हित पूर्णांक conf2;
	अचिन्हित पूर्णांक conf5;
पूर्ण;

काष्ठा pv88080 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा regulator_dev *rdev[PV88080_MAX_REGULATORS];
	अचिन्हित दीर्घ type;
	स्थिर काष्ठा pv88080_compatible_regmap *regmap_config;
पूर्ण;

काष्ठा pv88080_buck_voltage अणु
	पूर्णांक min_uV;
	पूर्णांक max_uV;
	पूर्णांक uV_step;
पूर्ण;

काष्ठा pv88080_buck_regmap अणु
	/* REGS */
	पूर्णांक buck_enable_reg;
	पूर्णांक buck_vsel_reg;
	पूर्णांक buck_mode_reg;
	पूर्णांक buck_limit_reg;
	पूर्णांक buck_vdac_range_reg;
	पूर्णांक buck_vrange_gain_reg;
	/* MASKS */
	पूर्णांक buck_enable_mask;
	पूर्णांक buck_vsel_mask;
	पूर्णांक buck_limit_mask;
पूर्ण;

काष्ठा pv88080_compatible_regmap अणु
	/* BUCK1, 2, 3 */
	काष्ठा pv88080_buck_regmap buck_regmap[PV88080_MAX_REGULATORS-1];
	/* HVBUCK */
	पूर्णांक hvbuck_enable_reg;
	पूर्णांक hvbuck_vsel_reg;
	पूर्णांक hvbuck_enable_mask;
	पूर्णांक hvbuck_vsel_mask;
पूर्ण;

अटल स्थिर काष्ठा regmap_config pv88080_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

/* Current limits array (in uA) क्रम BUCK1, BUCK2, BUCK3.
 * Entry indexes corresponds to रेजिस्टर values.
 */

अटल स्थिर अचिन्हित पूर्णांक pv88080_buck1_limits[] = अणु
	3230000, 5130000, 6960000, 8790000
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक pv88080_buck23_limits[] = अणु
	1496000, 2393000, 3291000, 4189000
पूर्ण;

अटल स्थिर काष्ठा pv88080_buck_voltage pv88080_buck_vol[2] = अणु
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
पूर्ण;

अटल स्थिर काष्ठा pv88080_compatible_regmap pv88080_aa_regs = अणु
	/* BUCK1 */
	.buck_regmap[0] = अणु
		.buck_enable_reg      = PV88080AA_REG_BUCK1_CONF0,
		.buck_vsel_reg        = PV88080AA_REG_BUCK1_CONF0,
		.buck_mode_reg        = PV88080AA_REG_BUCK1_CONF1,
		.buck_limit_reg       = PV88080AA_REG_BUCK1_CONF1,
		.buck_vdac_range_reg  = PV88080AA_REG_BUCK1_CONF2,
		.buck_vrange_gain_reg = PV88080AA_REG_BUCK1_CONF5,
		.buck_enable_mask     = PV88080_BUCK1_EN,
		.buck_vsel_mask       = PV88080_VBUCK1_MASK,
		.buck_limit_mask      = PV88080_BUCK1_ILIM_MASK,
	पूर्ण,
	/* BUCK2 */
	.buck_regmap[1] = अणु
		.buck_enable_reg      = PV88080AA_REG_BUCK2_CONF0,
		.buck_vsel_reg        = PV88080AA_REG_BUCK2_CONF0,
		.buck_mode_reg        = PV88080AA_REG_BUCK2_CONF1,
		.buck_limit_reg	      = PV88080AA_REG_BUCK2_CONF1,
		.buck_vdac_range_reg  = PV88080AA_REG_BUCK2_CONF2,
		.buck_vrange_gain_reg = PV88080AA_REG_BUCK2_CONF5,
		.buck_enable_mask	  = PV88080_BUCK2_EN,
		.buck_vsel_mask       = PV88080_VBUCK2_MASK,
		.buck_limit_mask      = PV88080_BUCK2_ILIM_MASK,
	पूर्ण,
	/* BUCK3 */
	.buck_regmap[2] = अणु
		.buck_enable_reg	  = PV88080AA_REG_BUCK3_CONF0,
		.buck_vsel_reg        = PV88080AA_REG_BUCK3_CONF0,
		.buck_mode_reg        = PV88080AA_REG_BUCK3_CONF1,
		.buck_limit_reg	      = PV88080AA_REG_BUCK3_CONF1,
		.buck_vdac_range_reg  = PV88080AA_REG_BUCK3_CONF2,
		.buck_vrange_gain_reg = PV88080AA_REG_BUCK3_CONF5,
		.buck_enable_mask	  = PV88080_BUCK3_EN,
		.buck_vsel_mask       = PV88080_VBUCK3_MASK,
		.buck_limit_mask      = PV88080_BUCK3_ILIM_MASK,
	पूर्ण,
	/* HVBUCK */
	.hvbuck_enable_reg	      = PV88080AA_REG_HVBUCK_CONF2,
	.hvbuck_vsel_reg          = PV88080AA_REG_HVBUCK_CONF1,
	.hvbuck_enable_mask       = PV88080_HVBUCK_EN,
	.hvbuck_vsel_mask         = PV88080_VHVBUCK_MASK,
पूर्ण;

अटल स्थिर काष्ठा pv88080_compatible_regmap pv88080_ba_regs = अणु
	/* BUCK1 */
	.buck_regmap[0] = अणु
		.buck_enable_reg	  = PV88080BA_REG_BUCK1_CONF0,
		.buck_vsel_reg        = PV88080BA_REG_BUCK1_CONF0,
		.buck_mode_reg        = PV88080BA_REG_BUCK1_CONF1,
		.buck_limit_reg       = PV88080BA_REG_BUCK1_CONF1,
		.buck_vdac_range_reg  = PV88080BA_REG_BUCK1_CONF2,
		.buck_vrange_gain_reg = PV88080BA_REG_BUCK1_CONF5,
		.buck_enable_mask     = PV88080_BUCK1_EN,
		.buck_vsel_mask       = PV88080_VBUCK1_MASK,
		.buck_limit_mask	  = PV88080_BUCK1_ILIM_MASK,
	पूर्ण,
	/* BUCK2 */
	.buck_regmap[1] = अणु
		.buck_enable_reg	  = PV88080BA_REG_BUCK2_CONF0,
		.buck_vsel_reg        = PV88080BA_REG_BUCK2_CONF0,
		.buck_mode_reg        = PV88080BA_REG_BUCK2_CONF1,
		.buck_limit_reg	      = PV88080BA_REG_BUCK2_CONF1,
		.buck_vdac_range_reg  = PV88080BA_REG_BUCK2_CONF2,
		.buck_vrange_gain_reg = PV88080BA_REG_BUCK2_CONF5,
		.buck_enable_mask	  = PV88080_BUCK2_EN,
		.buck_vsel_mask       = PV88080_VBUCK2_MASK,
		.buck_limit_mask	  = PV88080_BUCK2_ILIM_MASK,
	पूर्ण,
	/* BUCK3 */
	.buck_regmap[2] = अणु
		.buck_enable_reg	  = PV88080BA_REG_BUCK3_CONF0,
		.buck_vsel_reg        = PV88080BA_REG_BUCK3_CONF0,
		.buck_mode_reg        = PV88080BA_REG_BUCK3_CONF1,
		.buck_limit_reg	      = PV88080BA_REG_BUCK3_CONF1,
		.buck_vdac_range_reg  = PV88080BA_REG_BUCK3_CONF2,
		.buck_vrange_gain_reg = PV88080BA_REG_BUCK3_CONF5,
		.buck_enable_mask	  = PV88080_BUCK3_EN,
		.buck_vsel_mask       = PV88080_VBUCK3_MASK,
		.buck_limit_mask	  = PV88080_BUCK3_ILIM_MASK,
	पूर्ण,
	/* HVBUCK */
	.hvbuck_enable_reg	      = PV88080BA_REG_HVBUCK_CONF2,
	.hvbuck_vsel_reg          = PV88080BA_REG_HVBUCK_CONF1,
	.hvbuck_enable_mask       = PV88080_HVBUCK_EN,
	.hvbuck_vsel_mask		  = PV88080_VHVBUCK_MASK,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pv88080_dt_ids[] = अणु
	अणु .compatible = "pvs,pv88080",    .data = (व्योम *)TYPE_PV88080_AA पूर्ण,
	अणु .compatible = "pvs,pv88080-aa", .data = (व्योम *)TYPE_PV88080_AA पूर्ण,
	अणु .compatible = "pvs,pv88080-ba", .data = (व्योम *)TYPE_PV88080_BA पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pv88080_dt_ids);
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक pv88080_buck_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा pv88080_regulator *info = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक data;
	पूर्णांक ret, mode = 0;

	ret = regmap_पढ़ो(rdev->regmap, info->mode_reg, &data);
	अगर (ret < 0)
		वापस ret;

	चयन (data & PV88080_BUCK1_MODE_MASK) अणु
	हाल PV88080_BUCK_MODE_SYNC:
		mode = REGULATOR_MODE_FAST;
		अवरोध;
	हाल PV88080_BUCK_MODE_AUTO:
		mode = REGULATOR_MODE_NORMAL;
		अवरोध;
	हाल PV88080_BUCK_MODE_SLEEP:
		mode = REGULATOR_MODE_STANDBY;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस mode;
पूर्ण

अटल पूर्णांक pv88080_buck_set_mode(काष्ठा regulator_dev *rdev,
					अचिन्हित पूर्णांक mode)
अणु
	काष्ठा pv88080_regulator *info = rdev_get_drvdata(rdev);
	पूर्णांक val = 0;

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		val = PV88080_BUCK_MODE_SYNC;
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		val = PV88080_BUCK_MODE_AUTO;
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		val = PV88080_BUCK_MODE_SLEEP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(rdev->regmap, info->mode_reg,
					PV88080_BUCK1_MODE_MASK, val);
पूर्ण

अटल स्थिर काष्ठा regulator_ops pv88080_buck_ops = अणु
	.get_mode = pv88080_buck_get_mode,
	.set_mode = pv88080_buck_set_mode,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.set_current_limit = regulator_set_current_limit_regmap,
	.get_current_limit = regulator_get_current_limit_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops pv88080_hvbuck_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_linear,
पूर्ण;

#घोषणा PV88080_BUCK(chip, regl_name, min, step, max, limits_array) \
अणु\
	.desc	=	अणु\
		.id = chip##_ID_##regl_name,\
		.name = __stringअगरy(chip##_##regl_name),\
		.of_match = of_match_ptr(#regl_name),\
		.regulators_node = of_match_ptr("regulators"),\
		.type = REGULATOR_VOLTAGE,\
		.owner = THIS_MODULE,\
		.ops = &pv88080_buck_ops,\
		.min_uV = min, \
		.uV_step = step, \
		.n_voltages = ((max) - (min))/(step) + 1, \
		.curr_table = limits_array, \
		.n_current_limits = ARRAY_SIZE(limits_array), \
	पूर्ण,\
पूर्ण

#घोषणा PV88080_HVBUCK(chip, regl_name, min, step, max) \
अणु\
	.desc	=	अणु\
		.id = chip##_ID_##regl_name,\
		.name = __stringअगरy(chip##_##regl_name),\
		.of_match = of_match_ptr(#regl_name),\
		.regulators_node = of_match_ptr("regulators"),\
		.type = REGULATOR_VOLTAGE,\
		.owner = THIS_MODULE,\
		.ops = &pv88080_hvbuck_ops,\
		.min_uV = min, \
		.uV_step = step, \
		.n_voltages = ((max) - (min))/(step) + 1, \
	पूर्ण,\
पूर्ण

अटल काष्ठा pv88080_regulator pv88080_regulator_info[] = अणु
	PV88080_BUCK(PV88080, BUCK1, 600000, 6250, 1393750,
		pv88080_buck1_limits),
	PV88080_BUCK(PV88080, BUCK2, 600000, 6250, 1393750,
		pv88080_buck23_limits),
	PV88080_BUCK(PV88080, BUCK3, 600000, 6250, 1393750,
		pv88080_buck23_limits),
	PV88080_HVBUCK(PV88080, HVBUCK, 0, 5000, 1275000),
पूर्ण;

अटल irqवापस_t pv88080_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pv88080 *chip = data;
	पूर्णांक i, reg_val, err, ret = IRQ_NONE;

	err = regmap_पढ़ो(chip->regmap, PV88080_REG_EVENT_A, &reg_val);
	अगर (err < 0)
		जाओ error_i2c;

	अगर (reg_val & PV88080_E_VDD_FLT) अणु
		क्रम (i = 0; i < PV88080_MAX_REGULATORS; i++) अणु
			अगर (chip->rdev[i] != शून्य)
				regulator_notअगरier_call_chain(chip->rdev[i],
					REGULATOR_EVENT_UNDER_VOLTAGE,
					शून्य);
		पूर्ण

		err = regmap_ग_लिखो(chip->regmap, PV88080_REG_EVENT_A,
			PV88080_E_VDD_FLT);
		अगर (err < 0)
			जाओ error_i2c;

		ret = IRQ_HANDLED;
	पूर्ण

	अगर (reg_val & PV88080_E_OVER_TEMP) अणु
		क्रम (i = 0; i < PV88080_MAX_REGULATORS; i++) अणु
			अगर (chip->rdev[i] != शून्य)
				regulator_notअगरier_call_chain(chip->rdev[i],
					REGULATOR_EVENT_OVER_TEMP,
					शून्य);
		पूर्ण

		err = regmap_ग_लिखो(chip->regmap, PV88080_REG_EVENT_A,
			PV88080_E_OVER_TEMP);
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
अटल पूर्णांक pv88080_i2c_probe(काष्ठा i2c_client *i2c,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regulator_init_data *init_data = dev_get_platdata(&i2c->dev);
	काष्ठा pv88080 *chip;
	स्थिर काष्ठा pv88080_compatible_regmap *regmap_config;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक i, error, ret;
	अचिन्हित पूर्णांक conf2, conf5;

	chip = devm_kzalloc(&i2c->dev, माप(काष्ठा pv88080), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->dev = &i2c->dev;
	chip->regmap = devm_regmap_init_i2c(i2c, &pv88080_regmap_config);
	अगर (IS_ERR(chip->regmap)) अणु
		error = PTR_ERR(chip->regmap);
		dev_err(chip->dev, "Failed to allocate register map: %d\n",
			error);
		वापस error;
	पूर्ण

	अगर (i2c->dev.of_node) अणु
		match = of_match_node(pv88080_dt_ids, i2c->dev.of_node);
		अगर (!match) अणु
			dev_err(chip->dev, "Failed to get of_match_node\n");
			वापस -EINVAL;
		पूर्ण
		chip->type = (अचिन्हित दीर्घ)match->data;
	पूर्ण अन्यथा अणु
		chip->type = id->driver_data;
	पूर्ण

	i2c_set_clientdata(i2c, chip);

	अगर (i2c->irq != 0) अणु
		ret = regmap_ग_लिखो(chip->regmap, PV88080_REG_MASK_A, 0xFF);
		अगर (ret < 0) अणु
			dev_err(chip->dev,
				"Failed to mask A reg: %d\n", ret);
			वापस ret;
		पूर्ण
		ret = regmap_ग_लिखो(chip->regmap, PV88080_REG_MASK_B, 0xFF);
		अगर (ret < 0) अणु
			dev_err(chip->dev,
				"Failed to mask B reg: %d\n", ret);
			वापस ret;
		पूर्ण
		ret = regmap_ग_लिखो(chip->regmap, PV88080_REG_MASK_C, 0xFF);
		अगर (ret < 0) अणु
			dev_err(chip->dev,
				"Failed to mask C reg: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = devm_request_thपढ़ोed_irq(&i2c->dev, i2c->irq, शून्य,
					pv88080_irq_handler,
					IRQF_TRIGGER_LOW|IRQF_ONESHOT,
					"pv88080", chip);
		अगर (ret != 0) अणु
			dev_err(chip->dev, "Failed to request IRQ: %d\n",
				i2c->irq);
			वापस ret;
		पूर्ण

		ret = regmap_update_bits(chip->regmap, PV88080_REG_MASK_A,
			PV88080_M_VDD_FLT | PV88080_M_OVER_TEMP, 0);
		अगर (ret < 0) अणु
			dev_err(chip->dev,
				"Failed to update mask reg: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_warn(chip->dev, "No IRQ configured\n");
	पूर्ण

	चयन (chip->type) अणु
	हाल TYPE_PV88080_AA:
		chip->regmap_config = &pv88080_aa_regs;
		अवरोध;
	हाल TYPE_PV88080_BA:
		chip->regmap_config = &pv88080_ba_regs;
		अवरोध;
	पूर्ण

	regmap_config = chip->regmap_config;
	config.dev = chip->dev;
	config.regmap = chip->regmap;

	/* Registeration क्रम BUCK1, 2, 3 */
	क्रम (i = 0; i < PV88080_MAX_REGULATORS-1; i++) अणु
		अगर (init_data)
			config.init_data = &init_data[i];

		pv88080_regulator_info[i].desc.csel_reg
			= regmap_config->buck_regmap[i].buck_limit_reg;
		pv88080_regulator_info[i].desc.csel_mask
			= regmap_config->buck_regmap[i].buck_limit_mask;
		pv88080_regulator_info[i].mode_reg
			= regmap_config->buck_regmap[i].buck_mode_reg;
		pv88080_regulator_info[i].conf2
			= regmap_config->buck_regmap[i].buck_vdac_range_reg;
		pv88080_regulator_info[i].conf5
			= regmap_config->buck_regmap[i].buck_vrange_gain_reg;
		pv88080_regulator_info[i].desc.enable_reg
			= regmap_config->buck_regmap[i].buck_enable_reg;
		pv88080_regulator_info[i].desc.enable_mask
			= regmap_config->buck_regmap[i].buck_enable_mask;
		pv88080_regulator_info[i].desc.vsel_reg
			= regmap_config->buck_regmap[i].buck_vsel_reg;
		pv88080_regulator_info[i].desc.vsel_mask
			= regmap_config->buck_regmap[i].buck_vsel_mask;

		ret = regmap_पढ़ो(chip->regmap,
				pv88080_regulator_info[i].conf2, &conf2);
		अगर (ret < 0)
			वापस ret;
		conf2 = ((conf2 >> PV88080_BUCK_VDAC_RANGE_SHIFT) &
			PV88080_BUCK_VDAC_RANGE_MASK);

		ret = regmap_पढ़ो(chip->regmap,
				pv88080_regulator_info[i].conf5, &conf5);
		अगर (ret < 0)
			वापस ret;
		conf5 = ((conf5 >> PV88080_BUCK_VRANGE_GAIN_SHIFT) &
			PV88080_BUCK_VRANGE_GAIN_MASK);

		pv88080_regulator_info[i].desc.min_uV =
			pv88080_buck_vol[conf2].min_uV * (conf5+1);
		pv88080_regulator_info[i].desc.uV_step =
			pv88080_buck_vol[conf2].uV_step * (conf5+1);
		pv88080_regulator_info[i].desc.n_voltages =
			((pv88080_buck_vol[conf2].max_uV * (conf5+1))
			- (pv88080_regulator_info[i].desc.min_uV))
			/(pv88080_regulator_info[i].desc.uV_step) + 1;

		config.driver_data = (व्योम *)&pv88080_regulator_info[i];
		chip->rdev[i] = devm_regulator_रेजिस्टर(chip->dev,
			&pv88080_regulator_info[i].desc, &config);
		अगर (IS_ERR(chip->rdev[i])) अणु
			dev_err(chip->dev,
				"Failed to register PV88080 regulator\n");
			वापस PTR_ERR(chip->rdev[i]);
		पूर्ण
	पूर्ण

	pv88080_regulator_info[PV88080_ID_HVBUCK].desc.enable_reg
		= regmap_config->hvbuck_enable_reg;
	pv88080_regulator_info[PV88080_ID_HVBUCK].desc.enable_mask
		= regmap_config->hvbuck_enable_mask;
	pv88080_regulator_info[PV88080_ID_HVBUCK].desc.vsel_reg
		= regmap_config->hvbuck_vsel_reg;
	pv88080_regulator_info[PV88080_ID_HVBUCK].desc.vsel_mask
		= regmap_config->hvbuck_vsel_mask;

	/* Registeration क्रम HVBUCK */
	अगर (init_data)
		config.init_data = &init_data[PV88080_ID_HVBUCK];

	config.driver_data = (व्योम *)&pv88080_regulator_info[PV88080_ID_HVBUCK];
	chip->rdev[PV88080_ID_HVBUCK] = devm_regulator_रेजिस्टर(chip->dev,
		&pv88080_regulator_info[PV88080_ID_HVBUCK].desc, &config);
	अगर (IS_ERR(chip->rdev[PV88080_ID_HVBUCK])) अणु
		dev_err(chip->dev, "Failed to register PV88080 regulator\n");
		वापस PTR_ERR(chip->rdev[PV88080_ID_HVBUCK]);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pv88080_i2c_id[] = अणु
	अणु "pv88080",    TYPE_PV88080_AA पूर्ण,
	अणु "pv88080-aa", TYPE_PV88080_AA पूर्ण,
	अणु "pv88080-ba", TYPE_PV88080_BA पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pv88080_i2c_id);

अटल काष्ठा i2c_driver pv88080_regulator_driver = अणु
	.driver = अणु
		.name = "pv88080",
		.of_match_table = of_match_ptr(pv88080_dt_ids),
	पूर्ण,
	.probe = pv88080_i2c_probe,
	.id_table = pv88080_i2c_id,
पूर्ण;

module_i2c_driver(pv88080_regulator_driver);

MODULE_AUTHOR("James Ban <James.Ban.opensource@diasemi.com>");
MODULE_DESCRIPTION("Regulator device driver for Powerventure PV88080");
MODULE_LICENSE("GPL");
