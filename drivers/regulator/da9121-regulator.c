<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// DA9121 Single-channel dual-phase 10A buck converter
//
// Copyright (C) 2020 Axis Communications AB
//
// DA9130 Single-channel dual-phase 10A buck converter (Automotive)
// DA9217 Single-channel dual-phase  6A buck converter
// DA9122 Dual-channel single-phase  5A buck converter
// DA9131 Dual-channel single-phase  5A buck converter (Automotive)
// DA9220 Dual-channel single-phase  3A buck converter
// DA9132 Dual-channel single-phase  3A buck converter (Automotive)
//
// Copyright (C) 2020 Dialog Semiconductor

#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regulator/da9121.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>

#समावेश "da9121-regulator.h"

/* Chip data */
काष्ठा da9121 अणु
	काष्ठा device *dev;
	काष्ठा delayed_work work;
	काष्ठा da9121_pdata *pdata;
	काष्ठा regmap *regmap;
	काष्ठा regulator_dev *rdev[DA9121_IDX_MAX];
	अचिन्हित पूर्णांक persistent[2];
	अचिन्हित पूर्णांक passive_delay;
	पूर्णांक chip_irq;
	पूर्णांक variant_id;
	पूर्णांक subvariant_id;
पूर्ण;

/* Define ranges क्रम dअगरferent variants, enabling translation to/from
 * रेजिस्टरs. Maximums give scope to allow क्रम transients.
 */
काष्ठा da9121_range अणु
	पूर्णांक val_min;
	पूर्णांक val_max;
	पूर्णांक val_stp;
	पूर्णांक reg_min;
	पूर्णांक reg_max;
पूर्ण;

अटल काष्ठा da9121_range da9121_10A_2phase_current = अणु
	.val_min =  7000000,
	.val_max = 20000000,
	.val_stp =  1000000,
	.reg_min = 1,
	.reg_max = 14,
पूर्ण;

अटल काष्ठा da9121_range da9121_6A_2phase_current = अणु
	.val_min =  7000000,
	.val_max = 12000000,
	.val_stp =  1000000,
	.reg_min = 1,
	.reg_max = 6,
पूर्ण;

अटल काष्ठा da9121_range da9121_5A_1phase_current = अणु
	.val_min =  3500000,
	.val_max = 10000000,
	.val_stp =   500000,
	.reg_min = 1,
	.reg_max = 14,
पूर्ण;

अटल काष्ठा da9121_range da9121_3A_1phase_current = अणु
	.val_min = 3500000,
	.val_max = 6000000,
	.val_stp =  500000,
	.reg_min = 1,
	.reg_max = 6,
पूर्ण;

काष्ठा da9121_variant_info अणु
	पूर्णांक num_bucks;
	पूर्णांक num_phases;
	काष्ठा da9121_range *current_range;
पूर्ण;

अटल स्थिर काष्ठा da9121_variant_info variant_parameters[] = अणु
	अणु 1, 2, &da9121_10A_2phase_current पूर्ण,	//DA9121_TYPE_DA9121_DA9130
	अणु 2, 1, &da9121_3A_1phase_current  पूर्ण,	//DA9121_TYPE_DA9220_DA9132
	अणु 2, 1, &da9121_5A_1phase_current  पूर्ण,	//DA9121_TYPE_DA9122_DA9131
	अणु 1, 2, &da9121_6A_2phase_current  पूर्ण,	//DA9121_TYPE_DA9217
पूर्ण;

काष्ठा da9121_field अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक msk;
पूर्ण;

अटल स्थिर काष्ठा da9121_field da9121_current_field[2] = अणु
	अणु DA9121_REG_BUCK_BUCK1_2, DA9121_MASK_BUCK_BUCKx_2_CHx_ILIM पूर्ण,
	अणु DA9xxx_REG_BUCK_BUCK2_2, DA9121_MASK_BUCK_BUCKx_2_CHx_ILIM पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा da9121_field da9121_mode_field[2] = अणु
	अणु DA9121_REG_BUCK_BUCK1_4, DA9121_MASK_BUCK_BUCKx_4_CHx_A_MODE पूर्ण,
	अणु DA9xxx_REG_BUCK_BUCK2_4, DA9121_MASK_BUCK_BUCKx_4_CHx_A_MODE पूर्ण,
पूर्ण;

काष्ठा status_event_data अणु
	पूर्णांक buck_id; /* 0=core, 1/2-buck */
	पूर्णांक reg_index;  /* index क्रम status/event/mask रेजिस्टर selection */
	पूर्णांक status_bit; /* bit masks... */
	पूर्णांक event_bit;
	पूर्णांक mask_bit;
	अचिन्हित दीर्घ notअगरication; /* Notअगरication क्रम status inception */
	अक्षर *warn; /* अगर शून्य, notअगरy - otherwise dev_warn this string */
पूर्ण;

#घोषणा DA9121_STATUS(id, bank, name, notअगरication, warning) \
	अणु id, bank, \
	DA9121_MASK_SYS_STATUS_##bank##_##name, \
	DA9121_MASK_SYS_EVENT_##bank##_E_##name, \
	DA9121_MASK_SYS_MASK_##bank##_M_##name, \
	notअगरication, warning पूर्ण

/* For second buck related event bits that are specअगरic to DA9122, DA9220 variants */
#घोषणा DA9xxx_STATUS(id, bank, name, notअगरication, warning) \
	अणु id, bank, \
	DA9xxx_MASK_SYS_STATUS_##bank##_##name, \
	DA9xxx_MASK_SYS_EVENT_##bank##_E_##name, \
	DA9xxx_MASK_SYS_MASK_##bank##_M_##name, \
	notअगरication, warning पूर्ण

/* The status संकेतs that may need servicing, depending on device variant.
 * After निश्चितion, they persist; so event is notअगरied, the IRQ disabled,
 * and status polled until clear again and IRQ is reenabled.
 *
 * SG/PG1/PG2 should be set when device first घातers up and should never
 * re-occur. When this driver starts, it is expected that these will have
 * self-cleared क्रम when the IRQs are enabled, so these should never be seen.
 * If seen, the implication is that the device has reset.
 *
 * GPIO0/1/2 are not configured क्रम use by शेष, so should not be seen.
 */
अटल स्थिर काष्ठा status_event_data status_event_handling[] = अणु
	DA9xxx_STATUS(0, 0, SG, 0, "Handled E_SG\n"),
	DA9121_STATUS(0, 0, TEMP_CRIT, (REGULATOR_EVENT_OVER_TEMP|REGULATOR_EVENT_DISABLE), शून्य),
	DA9121_STATUS(0, 0, TEMP_WARN, REGULATOR_EVENT_OVER_TEMP, शून्य),
	DA9121_STATUS(1, 1, PG1, 0, "Handled E_PG1\n"),
	DA9121_STATUS(1, 1, OV1, REGULATOR_EVENT_REGULATION_OUT, शून्य),
	DA9121_STATUS(1, 1, UV1, REGULATOR_EVENT_UNDER_VOLTAGE, शून्य),
	DA9121_STATUS(1, 1, OC1, REGULATOR_EVENT_OVER_CURRENT, शून्य),
	DA9xxx_STATUS(2, 1, PG2, 0, "Handled E_PG2\n"),
	DA9xxx_STATUS(2, 1, OV2, REGULATOR_EVENT_REGULATION_OUT, शून्य),
	DA9xxx_STATUS(2, 1, UV2, REGULATOR_EVENT_UNDER_VOLTAGE, शून्य),
	DA9xxx_STATUS(2, 1, OC2, REGULATOR_EVENT_OVER_CURRENT, शून्य),
	DA9121_STATUS(0, 2, GPIO0, 0, "Handled E_GPIO0\n"),
	DA9121_STATUS(0, 2, GPIO1, 0, "Handled E_GPIO1\n"),
	DA9121_STATUS(0, 2, GPIO2, 0, "Handled E_GPIO2\n"),
पूर्ण;

अटल पूर्णांक da9121_get_current_limit(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा da9121 *chip = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	काष्ठा da9121_range *range =
		variant_parameters[chip->variant_id].current_range;
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret = 0;

	ret = regmap_पढ़ो(chip->regmap, da9121_current_field[id].reg, &val);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Cannot read BUCK register: %d\n", ret);
		जाओ error;
	पूर्ण

	अगर (val < range->reg_min) अणु
		ret = -EACCES;
		जाओ error;
	पूर्ण

	अगर (val > range->reg_max) अणु
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	वापस range->val_min + (range->val_stp * (val - range->reg_min));
error:
	वापस ret;
पूर्ण

अटल पूर्णांक da9121_उच्चमानing_selector(काष्ठा regulator_dev *rdev,
		पूर्णांक min, पूर्णांक max,
		अचिन्हित पूर्णांक *selector)
अणु
	काष्ठा da9121 *chip = rdev_get_drvdata(rdev);
	काष्ठा da9121_range *range =
		variant_parameters[chip->variant_id].current_range;
	अचिन्हित पूर्णांक level;
	अचिन्हित पूर्णांक i = 0;
	अचिन्हित पूर्णांक sel = 0;
	पूर्णांक ret = 0;

	अगर (range->val_min > max || range->val_max < min) अणु
		dev_err(chip->dev,
			"Requested current out of regulator capability\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	level = range->val_max;
	क्रम (i = range->reg_max; i >= range->reg_min; i--) अणु
		अगर (level <= max) अणु
			sel = i;
			अवरोध;
		पूर्ण
		level -= range->val_stp;
	पूर्ण

	अगर (level < min) अणु
		dev_err(chip->dev,
			"Best match falls below minimum requested current\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	*selector = sel;
error:
	वापस ret;
पूर्ण

अटल पूर्णांक da9121_set_current_limit(काष्ठा regulator_dev *rdev,
				पूर्णांक min_ua, पूर्णांक max_ua)
अणु
	काष्ठा da9121 *chip = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	काष्ठा da9121_range *range =
		variant_parameters[chip->variant_id].current_range;
	अचिन्हित पूर्णांक sel = 0;
	पूर्णांक ret = 0;

	अगर (min_ua < range->val_min ||
	    max_ua > range->val_max) अणु
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	ret = da9121_उच्चमानing_selector(rdev, min_ua, max_ua, &sel);
	अगर (ret < 0)
		जाओ error;

	ret = regmap_update_bits(chip->regmap,
				da9121_current_field[id].reg,
				da9121_current_field[id].msk,
				(अचिन्हित पूर्णांक)sel);
	अगर (ret < 0)
		dev_err(chip->dev, "Cannot update BUCK current limit, err: %d\n", ret);

error:
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक da9121_map_mode(अचिन्हित पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल DA9121_BUCK_MODE_FORCE_PWM:
		वापस REGULATOR_MODE_FAST;
	हाल DA9121_BUCK_MODE_FORCE_PWM_SHEDDING:
		वापस REGULATOR_MODE_NORMAL;
	हाल DA9121_BUCK_MODE_AUTO:
		वापस REGULATOR_MODE_IDLE;
	हाल DA9121_BUCK_MODE_FORCE_PFM:
		वापस REGULATOR_MODE_STANDBY;
	शेष:
		वापस REGULATOR_MODE_INVALID;
	पूर्ण
पूर्ण

अटल पूर्णांक da9121_buck_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा da9121 *chip = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	अचिन्हित पूर्णांक val;

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		val = DA9121_BUCK_MODE_FORCE_PWM;
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		val = DA9121_BUCK_MODE_FORCE_PWM_SHEDDING;
		अवरोध;
	हाल REGULATOR_MODE_IDLE:
		val = DA9121_BUCK_MODE_AUTO;
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		val = DA9121_BUCK_MODE_FORCE_PFM;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(chip->regmap,
				  da9121_mode_field[id].reg,
				  da9121_mode_field[id].msk,
				  val);
पूर्ण

अटल अचिन्हित पूर्णांक da9121_buck_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा da9121 *chip = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	अचिन्हित पूर्णांक val, mode;
	पूर्णांक ret = 0;

	ret = regmap_पढ़ो(chip->regmap, da9121_mode_field[id].reg, &val);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Cannot read BUCK register: %d\n", ret);
		वापस -EINVAL;
	पूर्ण

	mode = da9121_map_mode(val & da9121_mode_field[id].msk);
	अगर (mode == REGULATOR_MODE_INVALID)
		वापस -EINVAL;

	वापस mode;
पूर्ण

अटल स्थिर काष्ठा regulator_ops da9121_buck_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.get_current_limit = da9121_get_current_limit,
	.set_current_limit = da9121_set_current_limit,
	.set_mode = da9121_buck_set_mode,
	.get_mode = da9121_buck_get_mode,
पूर्ण;

अटल काष्ठा of_regulator_match da9121_matches[] = अणु
	[DA9121_IDX_BUCK1] = अणु .name = "buck1" पूर्ण,
	[DA9121_IDX_BUCK2] = अणु .name = "buck2" पूर्ण,
पूर्ण;

अटल पूर्णांक da9121_of_parse_cb(काष्ठा device_node *np,
				स्थिर काष्ठा regulator_desc *desc,
				काष्ठा regulator_config *config)
अणु
	काष्ठा da9121 *chip = config->driver_data;
	काष्ठा da9121_pdata *pdata;
	काष्ठा gpio_desc *ena_gpiod;

	अगर (chip->pdata == शून्य) अणु
		pdata = devm_kzalloc(chip->dev, माप(*pdata), GFP_KERNEL);
		अगर (!pdata)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		pdata = chip->pdata;
	पूर्ण

	pdata->num_buck++;

	अगर (pdata->num_buck > variant_parameters[chip->variant_id].num_bucks) अणु
		dev_err(chip->dev, "Error: excessive regulators for device\n");
		वापस -ENODEV;
	पूर्ण

	ena_gpiod = fwnode_gpiod_get_index(of_fwnode_handle(np), "enable", 0,
						GPIOD_OUT_HIGH |
						GPIOD_FLAGS_BIT_NONEXCLUSIVE,
						"da9121-enable");
	अगर (!IS_ERR(ena_gpiod))
		config->ena_gpiod = ena_gpiod;

	अगर (variant_parameters[chip->variant_id].num_bucks == 2) अणु
		uपूर्णांक32_t ripple_cancel;
		uपूर्णांक32_t ripple_reg;
		पूर्णांक ret;

		अगर (of_property_पढ़ो_u32(da9121_matches[pdata->num_buck-1].of_node,
				"dlg,ripple-cancel", &ripple_cancel)) अणु
			अगर (pdata->num_buck > 1)
				ripple_reg = DA9xxx_REG_BUCK_BUCK2_7;
			अन्यथा
				ripple_reg = DA9121_REG_BUCK_BUCK1_7;

			ret = regmap_update_bits(chip->regmap, ripple_reg,
				DA9xxx_MASK_BUCK_BUCKx_7_CHx_RIPPLE_CANCEL,
				ripple_cancel);
			अगर (ret < 0)
				dev_err(chip->dev, "Cannot set ripple mode, err: %d\n", ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा DA9121_MIN_MV		300
#घोषणा DA9121_MAX_MV		1900
#घोषणा DA9121_STEP_MV		10
#घोषणा DA9121_MIN_SEL		(DA9121_MIN_MV / DA9121_STEP_MV)
#घोषणा DA9121_N_VOLTAGES	(((DA9121_MAX_MV - DA9121_MIN_MV) / DA9121_STEP_MV) \
				 + 1 + DA9121_MIN_SEL)

अटल स्थिर काष्ठा regulator_desc da9121_reg = अणु
	.id = DA9121_IDX_BUCK1,
	.name = "da9121",
	.of_match = "buck1",
	.of_parse_cb = da9121_of_parse_cb,
	.owner = THIS_MODULE,
	.regulators_node = of_match_ptr("regulators"),
	.of_map_mode = da9121_map_mode,
	.ops = &da9121_buck_ops,
	.type = REGULATOR_VOLTAGE,
	.n_voltages = DA9121_N_VOLTAGES,
	.min_uV = DA9121_MIN_MV * 1000,
	.uV_step = DA9121_STEP_MV * 1000,
	.linear_min_sel = DA9121_MIN_SEL,
	.vsel_reg = DA9121_REG_BUCK_BUCK1_5,
	.vsel_mask = DA9121_MASK_BUCK_BUCKx_5_CHx_A_VOUT,
	.enable_reg = DA9121_REG_BUCK_BUCK1_0,
	.enable_mask = DA9121_MASK_BUCK_BUCKx_0_CHx_EN,
	/* Default value of BUCK_BUCK1_0.CH1_SRC_DVC_UP */
	.ramp_delay = 20000,
	/* tBUCK_EN */
	.enable_समय = 20,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc da9220_reg[2] = अणु
	अणु
		.id = DA9121_IDX_BUCK1,
		.name = "DA9220/DA9132 BUCK1",
		.of_match = "buck1",
		.of_parse_cb = da9121_of_parse_cb,
		.owner = THIS_MODULE,
		.regulators_node = of_match_ptr("regulators"),
		.of_map_mode = da9121_map_mode,
		.ops = &da9121_buck_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = DA9121_N_VOLTAGES,
		.min_uV = DA9121_MIN_MV * 1000,
		.uV_step = DA9121_STEP_MV * 1000,
		.linear_min_sel = DA9121_MIN_SEL,
		.enable_reg = DA9121_REG_BUCK_BUCK1_0,
		.enable_mask = DA9121_MASK_BUCK_BUCKx_0_CHx_EN,
		.vsel_reg = DA9121_REG_BUCK_BUCK1_5,
		.vsel_mask = DA9121_MASK_BUCK_BUCKx_5_CHx_A_VOUT,
	पूर्ण,
	अणु
		.id = DA9121_IDX_BUCK2,
		.name = "DA9220/DA9132 BUCK2",
		.of_match = "buck2",
		.of_parse_cb = da9121_of_parse_cb,
		.owner = THIS_MODULE,
		.regulators_node = of_match_ptr("regulators"),
		.of_map_mode = da9121_map_mode,
		.ops = &da9121_buck_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = DA9121_N_VOLTAGES,
		.min_uV = DA9121_MIN_MV * 1000,
		.uV_step = DA9121_STEP_MV * 1000,
		.linear_min_sel = DA9121_MIN_SEL,
		.enable_reg = DA9xxx_REG_BUCK_BUCK2_0,
		.enable_mask = DA9121_MASK_BUCK_BUCKx_0_CHx_EN,
		.vsel_reg = DA9xxx_REG_BUCK_BUCK2_5,
		.vsel_mask = DA9121_MASK_BUCK_BUCKx_5_CHx_A_VOUT,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा regulator_desc da9122_reg[2] = अणु
	अणु
		.id = DA9121_IDX_BUCK1,
		.name = "DA9122/DA9131 BUCK1",
		.of_match = "buck1",
		.of_parse_cb = da9121_of_parse_cb,
		.owner = THIS_MODULE,
		.regulators_node = of_match_ptr("regulators"),
		.of_map_mode = da9121_map_mode,
		.ops = &da9121_buck_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = DA9121_N_VOLTAGES,
		.min_uV = DA9121_MIN_MV * 1000,
		.uV_step = DA9121_STEP_MV * 1000,
		.linear_min_sel = DA9121_MIN_SEL,
		.enable_reg = DA9121_REG_BUCK_BUCK1_0,
		.enable_mask = DA9121_MASK_BUCK_BUCKx_0_CHx_EN,
		.vsel_reg = DA9121_REG_BUCK_BUCK1_5,
		.vsel_mask = DA9121_MASK_BUCK_BUCKx_5_CHx_A_VOUT,
	पूर्ण,
	अणु
		.id = DA9121_IDX_BUCK2,
		.name = "DA9122/DA9131 BUCK2",
		.of_match = "buck2",
		.of_parse_cb = da9121_of_parse_cb,
		.owner = THIS_MODULE,
		.regulators_node = of_match_ptr("regulators"),
		.of_map_mode = da9121_map_mode,
		.ops = &da9121_buck_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = DA9121_N_VOLTAGES,
		.min_uV = DA9121_MIN_MV * 1000,
		.uV_step = DA9121_STEP_MV * 1000,
		.linear_min_sel = DA9121_MIN_SEL,
		.enable_reg = DA9xxx_REG_BUCK_BUCK2_0,
		.enable_mask = DA9121_MASK_BUCK_BUCKx_0_CHx_EN,
		.vsel_reg = DA9xxx_REG_BUCK_BUCK2_5,
		.vsel_mask = DA9121_MASK_BUCK_BUCKx_5_CHx_A_VOUT,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा regulator_desc da9217_reg = अणु
	.id = DA9121_IDX_BUCK1,
	.name = "DA9217 BUCK1",
	.of_match = "buck1",
	.of_parse_cb = da9121_of_parse_cb,
	.owner = THIS_MODULE,
	.regulators_node = of_match_ptr("regulators"),
	.of_map_mode = da9121_map_mode,
	.ops = &da9121_buck_ops,
	.type = REGULATOR_VOLTAGE,
	.n_voltages = DA9121_N_VOLTAGES,
	.min_uV = DA9121_MIN_MV * 1000,
	.uV_step = DA9121_STEP_MV * 1000,
	.linear_min_sel = DA9121_MIN_SEL,
	.enable_reg = DA9121_REG_BUCK_BUCK1_0,
	.enable_mask = DA9121_MASK_BUCK_BUCKx_0_CHx_EN,
	.vsel_reg = DA9121_REG_BUCK_BUCK1_5,
	.vsel_mask = DA9121_MASK_BUCK_BUCKx_5_CHx_A_VOUT,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc *local_da9121_regulators[][DA9121_IDX_MAX] = अणु
	[DA9121_TYPE_DA9121_DA9130] = अणु &da9121_reg, शून्य पूर्ण,
	[DA9121_TYPE_DA9220_DA9132] = अणु &da9220_reg[0], &da9220_reg[1] पूर्ण,
	[DA9121_TYPE_DA9122_DA9131] = अणु &da9122_reg[0], &da9122_reg[1] पूर्ण,
	[DA9121_TYPE_DA9217] = अणु &da9217_reg, शून्य पूर्ण,
पूर्ण;

अटल व्योम da9121_status_poll_on(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा da9121 *chip = container_of(work, काष्ठा da9121, work.work);
	पूर्णांक status[3] = अणु0पूर्ण;
	पूर्णांक clear[3] = अणु0पूर्ण;
	अचिन्हित दीर्घ delay;
	पूर्णांक i;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(chip->regmap, DA9121_REG_SYS_STATUS_0, status, 2);
	अगर (ret < 0) अणु
		dev_err(chip->dev,
			"Failed to read STATUS registers: %d\n", ret);
		जाओ error;
	पूर्ण

	/* Possible events are tested to be within range क्रम the variant, potentially
	 * masked by the IRQ handler (not just warned about), as having been masked,
	 * and the respective state cleared - then flagged to unmask क्रम next IRQ.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(status_event_handling); i++) अणु
		स्थिर काष्ठा status_event_data *item = &status_event_handling[i];
		पूर्णांक reg_idx = item->reg_index;
		bool relevant = (item->buck_id <= variant_parameters[chip->variant_id].num_bucks);
		bool supported = (item->warn == शून्य);
		bool persisting = (chip->persistent[reg_idx] & item->event_bit);
		bool now_cleared = !(status[reg_idx] & item->status_bit);

		अगर (relevant && supported && persisting && now_cleared) अणु
			clear[reg_idx] |= item->mask_bit;
			chip->persistent[reg_idx] &= ~item->event_bit;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		अगर (clear[i]) अणु
			अचिन्हित पूर्णांक reg = DA9121_REG_SYS_MASK_0 + i;
			अचिन्हित पूर्णांक mbit = clear[i];

			ret = regmap_update_bits(chip->regmap, reg, mbit, 0);
			अगर (ret < 0) अणु
				dev_err(chip->dev,
					"Failed to unmask 0x%02x %d\n",
					reg, ret);
				जाओ error;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (chip->persistent[0] | chip->persistent[1]) अणु
		delay = msecs_to_jअगरfies(chip->passive_delay);
		queue_delayed_work(प्रणाली_मुक्तzable_wq, &chip->work, delay);
	पूर्ण

error:
	वापस;
पूर्ण

अटल irqवापस_t da9121_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9121 *chip = data;
	काष्ठा regulator_dev *rdev;
	पूर्णांक event[3] = अणु0पूर्ण;
	पूर्णांक handled[3] = अणु0पूर्ण;
	पूर्णांक mask[3] = अणु0पूर्ण;
	पूर्णांक ret = IRQ_NONE;
	पूर्णांक i;
	पूर्णांक err;

	err = regmap_bulk_पढ़ो(chip->regmap, DA9121_REG_SYS_EVENT_0, event, 3);
	अगर (err < 0) अणु
		dev_err(chip->dev, "Failed to read EVENT registers %d\n", err);
		ret = IRQ_NONE;
		जाओ error;
	पूर्ण

	err = regmap_bulk_पढ़ो(chip->regmap, DA9121_REG_SYS_MASK_0, mask, 3);
	अगर (err < 0) अणु
		dev_err(chip->dev,
			"Failed to read MASK registers: %d\n", ret);
		ret = IRQ_NONE;
		जाओ error;
	पूर्ण

	rdev = chip->rdev[DA9121_IDX_BUCK1];

	/* Possible events are tested to be within range क्रम the variant, currently
	 * enabled, and having triggered this IRQ. The event may then be notअगरied,
	 * or a warning given क्रम unexpected events - those from device POR, and
	 * currently unsupported GPIO configurations.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(status_event_handling); i++) अणु
		स्थिर काष्ठा status_event_data *item = &status_event_handling[i];
		पूर्णांक reg_idx = item->reg_index;
		bool relevant = (item->buck_id <= variant_parameters[chip->variant_id].num_bucks);
		bool enabled = !(mask[reg_idx] & item->mask_bit);
		bool active = (event[reg_idx] & item->event_bit);
		bool notअगरy = (item->warn == शून्य);

		अगर (relevant && enabled && active) अणु
			अगर (notअगरy) अणु
				chip->persistent[reg_idx] |= item->event_bit;
				regulator_notअगरier_call_chain(rdev, item->notअगरication, शून्य);
			पूर्ण अन्यथा अणु
				dev_warn(chip->dev, item->warn);
				handled[reg_idx] |= item->event_bit;
				ret = IRQ_HANDLED;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 3; i++) अणु
		अगर (event[i] != handled[i]) अणु
			dev_warn(chip->dev,
				"Unhandled event(s) in bank%d 0x%02x\n", i,
				event[i] ^ handled[i]);
		पूर्ण
	पूर्ण

	/* Mask the पूर्णांकerrupts क्रम persistent events OV, OC, UV, WARN, CRIT */
	क्रम (i = 0; i < 2; i++) अणु
		अगर (handled[i]) अणु
			अचिन्हित पूर्णांक reg = DA9121_REG_SYS_MASK_0 + i;
			अचिन्हित पूर्णांक mbit = handled[i];

			err = regmap_update_bits(chip->regmap, reg, mbit, mbit);
			अगर (err < 0) अणु
				dev_err(chip->dev,
					"Failed to mask 0x%02x interrupt %d\n",
					reg, err);
				ret = IRQ_NONE;
				जाओ error;
			पूर्ण
		पूर्ण
	पूर्ण

	/* clear the events */
	अगर (handled[0] | handled[1] | handled[2]) अणु
		err = regmap_bulk_ग_लिखो(chip->regmap, DA9121_REG_SYS_EVENT_0, handled, 3);
		अगर (err < 0) अणु
			dev_err(chip->dev, "Fail to write EVENTs %d\n", err);
			ret = IRQ_NONE;
			जाओ error;
		पूर्ण
	पूर्ण

	queue_delayed_work(प्रणाली_मुक्तzable_wq, &chip->work, 0);
error:
	वापस ret;
पूर्ण

अटल पूर्णांक da9121_set_regulator_config(काष्ठा da9121 *chip)
अणु
	काष्ठा regulator_config config = अणु पूर्ण;
	अचिन्हित पूर्णांक max_matches = variant_parameters[chip->variant_id].num_bucks;
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < max_matches; i++) अणु
		स्थिर काष्ठा regulator_desc *regl_desc =
			local_da9121_regulators[chip->variant_id][i];

		config.dev = chip->dev;
		config.driver_data = chip;
		config.regmap = chip->regmap;

		chip->rdev[i] = devm_regulator_रेजिस्टर(chip->dev,
					regl_desc, &config);
		अगर (IS_ERR(chip->rdev[i])) अणु
			dev_err(chip->dev, "Failed to register regulator %s, %d/%d\n",
				regl_desc->name, (i+1), max_matches);
			ret = PTR_ERR(chip->rdev[i]);
			जाओ error;
		पूर्ण
	पूर्ण

error:
	वापस ret;
पूर्ण

/* DA9121 chip रेजिस्टर model */
अटल स्थिर काष्ठा regmap_range da9121_1ch_पढ़ोable_ranges[] = अणु
	regmap_reg_range(DA9121_REG_SYS_STATUS_0, DA9121_REG_SYS_MASK_3),
	regmap_reg_range(DA9121_REG_SYS_CONFIG_2, DA9121_REG_SYS_CONFIG_3),
	regmap_reg_range(DA9121_REG_SYS_GPIO0_0, DA9121_REG_SYS_GPIO2_1),
	regmap_reg_range(DA9121_REG_BUCK_BUCK1_0, DA9121_REG_BUCK_BUCK1_6),
	regmap_reg_range(DA9121_REG_OTP_DEVICE_ID, DA9121_REG_OTP_CONFIG_ID),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9121_1ch_पढ़ोable_table = अणु
	.yes_ranges = da9121_1ch_पढ़ोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9121_1ch_पढ़ोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range da9121_2ch_पढ़ोable_ranges[] = अणु
	regmap_reg_range(DA9121_REG_SYS_STATUS_0, DA9121_REG_SYS_MASK_3),
	regmap_reg_range(DA9121_REG_SYS_CONFIG_2, DA9121_REG_SYS_CONFIG_3),
	regmap_reg_range(DA9121_REG_SYS_GPIO0_0, DA9121_REG_SYS_GPIO2_1),
	regmap_reg_range(DA9121_REG_BUCK_BUCK1_0, DA9121_REG_BUCK_BUCK1_7),
	regmap_reg_range(DA9xxx_REG_BUCK_BUCK2_0, DA9xxx_REG_BUCK_BUCK2_7),
	regmap_reg_range(DA9121_REG_OTP_DEVICE_ID, DA9121_REG_OTP_CONFIG_ID),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9121_2ch_पढ़ोable_table = अणु
	.yes_ranges = da9121_2ch_पढ़ोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9121_2ch_पढ़ोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range da9121_1ch_ग_लिखोable_ranges[] = अणु
	regmap_reg_range(DA9121_REG_SYS_EVENT_0, DA9121_REG_SYS_MASK_3),
	regmap_reg_range(DA9121_REG_SYS_CONFIG_2, DA9121_REG_SYS_CONFIG_3),
	regmap_reg_range(DA9121_REG_SYS_GPIO0_0, DA9121_REG_SYS_GPIO2_1),
	regmap_reg_range(DA9121_REG_BUCK_BUCK1_0, DA9121_REG_BUCK_BUCK1_2),
	regmap_reg_range(DA9121_REG_BUCK_BUCK1_4, DA9121_REG_BUCK_BUCK1_6),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9121_1ch_ग_लिखोable_table = अणु
	.yes_ranges = da9121_1ch_ग_लिखोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9121_1ch_ग_लिखोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range da9121_2ch_ग_लिखोable_ranges[] = अणु
	regmap_reg_range(DA9121_REG_SYS_EVENT_0, DA9121_REG_SYS_MASK_3),
	regmap_reg_range(DA9121_REG_SYS_CONFIG_2, DA9121_REG_SYS_CONFIG_3),
	regmap_reg_range(DA9121_REG_SYS_GPIO0_0, DA9121_REG_SYS_GPIO2_1),
	regmap_reg_range(DA9121_REG_BUCK_BUCK1_0, DA9121_REG_BUCK_BUCK1_2),
	regmap_reg_range(DA9121_REG_BUCK_BUCK1_4, DA9121_REG_BUCK_BUCK1_7),
	regmap_reg_range(DA9xxx_REG_BUCK_BUCK2_0, DA9xxx_REG_BUCK_BUCK2_2),
	regmap_reg_range(DA9xxx_REG_BUCK_BUCK2_4, DA9xxx_REG_BUCK_BUCK2_7),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9121_2ch_ग_लिखोable_table = अणु
	.yes_ranges = da9121_2ch_ग_लिखोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9121_2ch_ग_लिखोable_ranges),
पूर्ण;


अटल स्थिर काष्ठा regmap_range da9121_अस्थिर_ranges[] = अणु
	regmap_reg_range(DA9121_REG_SYS_STATUS_0, DA9121_REG_SYS_EVENT_2),
	regmap_reg_range(DA9121_REG_SYS_GPIO0_0, DA9121_REG_SYS_GPIO2_1),
	regmap_reg_range(DA9121_REG_BUCK_BUCK1_0, DA9121_REG_BUCK_BUCK1_6),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table da9121_अस्थिर_table = अणु
	.yes_ranges = da9121_अस्थिर_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9121_अस्थिर_ranges),
पूर्ण;

/* DA9121 regmap config क्रम 1 channel variants */
अटल काष्ठा regmap_config da9121_1ch_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = DA9121_REG_OTP_CONFIG_ID,
	.rd_table = &da9121_1ch_पढ़ोable_table,
	.wr_table = &da9121_1ch_ग_लिखोable_table,
	.अस्थिर_table = &da9121_अस्थिर_table,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

/* DA9121 regmap config क्रम 2 channel variants */
अटल काष्ठा regmap_config da9121_2ch_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = DA9121_REG_OTP_CONFIG_ID,
	.rd_table = &da9121_2ch_पढ़ोable_table,
	.wr_table = &da9121_2ch_ग_लिखोable_table,
	.अस्थिर_table = &da9121_अस्थिर_table,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक da9121_check_device_type(काष्ठा i2c_client *i2c, काष्ठा da9121 *chip)
अणु
	u32 device_id;
	u32 variant_id;
	u8 variant_mrc, variant_vrc;
	अक्षर *type;
	bool config_match = false;
	पूर्णांक ret = 0;

	ret = regmap_पढ़ो(chip->regmap, DA9121_REG_OTP_DEVICE_ID, &device_id);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Cannot read device ID: %d\n", ret);
		जाओ error;
	पूर्ण

	ret = regmap_पढ़ो(chip->regmap, DA9121_REG_OTP_VARIANT_ID, &variant_id);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Cannot read variant ID: %d\n", ret);
		जाओ error;
	पूर्ण

	अगर (device_id != DA9121_DEVICE_ID) अणु
		dev_err(chip->dev, "Invalid device ID: 0x%02x\n", device_id);
		ret = -ENODEV;
		जाओ error;
	पूर्ण

	variant_vrc = variant_id & DA9121_MASK_OTP_VARIANT_ID_VRC;

	चयन (chip->subvariant_id) अणु
	हाल DA9121_SUBTYPE_DA9121:
		type = "DA9121";
		config_match = (variant_vrc == DA9121_VARIANT_VRC);
		अवरोध;
	हाल DA9121_SUBTYPE_DA9130:
		type = "DA9130";
		config_match = (variant_vrc == DA9130_VARIANT_VRC);
		अवरोध;
	हाल DA9121_SUBTYPE_DA9220:
		type = "DA9220";
		config_match = (variant_vrc == DA9220_VARIANT_VRC);
		अवरोध;
	हाल DA9121_SUBTYPE_DA9132:
		type = "DA9132";
		config_match = (variant_vrc == DA9132_VARIANT_VRC);
		अवरोध;
	हाल DA9121_SUBTYPE_DA9122:
		type = "DA9122";
		config_match = (variant_vrc == DA9122_VARIANT_VRC);
		अवरोध;
	हाल DA9121_SUBTYPE_DA9131:
		type = "DA9131";
		config_match = (variant_vrc == DA9131_VARIANT_VRC);
		अवरोध;
	हाल DA9121_SUBTYPE_DA9217:
		type = "DA9217";
		config_match = (variant_vrc == DA9217_VARIANT_VRC);
		अवरोध;
	शेष:
		type = "Unknown";
		अवरोध;
	पूर्ण

	dev_info(chip->dev,
		 "Device detected (device-ID: 0x%02X, var-ID: 0x%02X, %s)\n",
		 device_id, variant_id, type);

	अगर (!config_match) अणु
		dev_err(chip->dev, "Device tree configuration does not match detected device.\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	variant_mrc = (variant_id & DA9121_MASK_OTP_VARIANT_ID_MRC)
			>> DA9121_SHIFT_OTP_VARIANT_ID_MRC;

	अगर ((device_id == DA9121_DEVICE_ID) &&
	    (variant_mrc < DA9121_VARIANT_MRC_BASE)) अणु
		dev_err(chip->dev,
			"Cannot support variant MRC: 0x%02X\n", variant_mrc);
		ret = -EINVAL;
	पूर्ण
error:
	वापस ret;
पूर्ण

अटल पूर्णांक da9121_assign_chip_model(काष्ठा i2c_client *i2c,
			काष्ठा da9121 *chip)
अणु
	काष्ठा regmap_config *regmap;
	पूर्णांक ret = 0;

	chip->dev = &i2c->dev;

	/* Use configured subtype to select the regulator descriptor index and
	 * रेजिस्टर map, common to both consumer and स्वतःmotive grade variants
	 */
	चयन (chip->subvariant_id) अणु
	हाल DA9121_SUBTYPE_DA9121:
	हाल DA9121_SUBTYPE_DA9130:
		chip->variant_id = DA9121_TYPE_DA9121_DA9130;
		regmap = &da9121_1ch_regmap_config;
		अवरोध;
	हाल DA9121_SUBTYPE_DA9217:
		chip->variant_id = DA9121_TYPE_DA9217;
		regmap = &da9121_1ch_regmap_config;
		अवरोध;
	हाल DA9121_SUBTYPE_DA9122:
	हाल DA9121_SUBTYPE_DA9131:
		chip->variant_id = DA9121_TYPE_DA9122_DA9131;
		regmap = &da9121_2ch_regmap_config;
		अवरोध;
	हाल DA9121_SUBTYPE_DA9220:
	हाल DA9121_SUBTYPE_DA9132:
		chip->variant_id = DA9121_TYPE_DA9220_DA9132;
		regmap = &da9121_2ch_regmap_config;
		अवरोध;
	पूर्ण

	/* Set these up क्रम of_regulator_match call which may want .of_map_modes */
	da9121_matches[0].desc = local_da9121_regulators[chip->variant_id][0];
	da9121_matches[1].desc = local_da9121_regulators[chip->variant_id][1];

	chip->regmap = devm_regmap_init_i2c(i2c, regmap);
	अगर (IS_ERR(chip->regmap)) अणु
		ret = PTR_ERR(chip->regmap);
		dev_err(chip->dev, "Failed to configure a register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = da9121_check_device_type(i2c, chip);

	वापस ret;
पूर्ण

अटल पूर्णांक da9121_config_irq(काष्ठा i2c_client *i2c,
			काष्ठा da9121 *chip)
अणु
	अचिन्हित पूर्णांक p_delay = DA9121_DEFAULT_POLLING_PERIOD_MS;
	स्थिर पूर्णांक mask_all[4] = अणु 0, 0, 0xFF, 0xFF पूर्ण;
	पूर्णांक ret = 0;

	chip->chip_irq = i2c->irq;

	अगर (chip->chip_irq != 0) अणु
		अगर (!of_property_पढ़ो_u32(chip->dev->of_node,
					  "dlg,irq-polling-delay-passive-ms",
					  &p_delay)) अणु
			अगर (p_delay < DA9121_MIN_POLLING_PERIOD_MS ||
			    p_delay > DA9121_MAX_POLLING_PERIOD_MS) अणु
				dev_warn(chip->dev,
					 "Out-of-range polling period %d ms\n",
					 p_delay);
				p_delay = DA9121_DEFAULT_POLLING_PERIOD_MS;
			पूर्ण
		पूर्ण

		chip->passive_delay = p_delay;

		ret = request_thपढ़ोed_irq(chip->chip_irq, शून्य,
					da9121_irq_handler,
					IRQF_TRIGGER_LOW|IRQF_ONESHOT,
					"da9121", chip);
		अगर (ret != 0) अणु
			dev_err(chip->dev, "Failed IRQ request: %d\n",
				chip->chip_irq);
			जाओ error;
		पूर्ण

		ret = regmap_bulk_ग_लिखो(chip->regmap, DA9121_REG_SYS_MASK_0, mask_all, 4);
		अगर (ret != 0) अणु
			dev_err(chip->dev, "Failed to set IRQ masks: %d\n",
				ret);
			जाओ regmap_error;
		पूर्ण

		INIT_DELAYED_WORK(&chip->work, da9121_status_poll_on);
		dev_info(chip->dev, "Interrupt polling period set at %d ms\n",
			 chip->passive_delay);
	पूर्ण
error:
	वापस ret;
regmap_error:
	मुक्त_irq(chip->chip_irq, chip);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id da9121_dt_ids[] = अणु
	अणु .compatible = "dlg,da9121", .data = (व्योम *) DA9121_SUBTYPE_DA9121 पूर्ण,
	अणु .compatible = "dlg,da9130", .data = (व्योम *) DA9121_SUBTYPE_DA9130 पूर्ण,
	अणु .compatible = "dlg,da9217", .data = (व्योम *) DA9121_SUBTYPE_DA9217 पूर्ण,
	अणु .compatible = "dlg,da9122", .data = (व्योम *) DA9121_SUBTYPE_DA9122 पूर्ण,
	अणु .compatible = "dlg,da9131", .data = (व्योम *) DA9121_SUBTYPE_DA9131 पूर्ण,
	अणु .compatible = "dlg,da9220", .data = (व्योम *) DA9121_SUBTYPE_DA9220 पूर्ण,
	अणु .compatible = "dlg,da9132", .data = (व्योम *) DA9121_SUBTYPE_DA9132 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, da9121_dt_ids);

अटल अंतरभूत पूर्णांक da9121_of_get_id(काष्ठा device *dev)
अणु
	स्थिर काष्ठा of_device_id *id = of_match_device(da9121_dt_ids, dev);

	अगर (!id) अणु
		dev_err(dev, "%s: Failed\n", __func__);
		वापस -EINVAL;
	पूर्ण
	वापस (uपूर्णांकptr_t)id->data;
पूर्ण

अटल पूर्णांक da9121_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा da9121 *chip;
	स्थिर पूर्णांक mask_all[4] = अणु 0xFF, 0xFF, 0xFF, 0xFF पूर्ण;
	पूर्णांक ret = 0;

	chip = devm_kzalloc(&i2c->dev, माप(काष्ठा da9121), GFP_KERNEL);
	अगर (!chip) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	chip->pdata = i2c->dev.platक्रमm_data;
	chip->subvariant_id = da9121_of_get_id(&i2c->dev);

	ret = da9121_assign_chip_model(i2c, chip);
	अगर (ret < 0)
		जाओ error;

	ret = regmap_bulk_ग_लिखो(chip->regmap, DA9121_REG_SYS_MASK_0, mask_all, 4);
	अगर (ret != 0) अणु
		dev_err(chip->dev, "Failed to set IRQ masks: %d\n", ret);
		जाओ error;
	पूर्ण

	ret = da9121_set_regulator_config(chip);
	अगर (ret < 0)
		जाओ error;

	ret = da9121_config_irq(i2c, chip);

error:
	वापस ret;
पूर्ण

अटल पूर्णांक da9121_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा da9121 *chip = i2c_get_clientdata(i2c);
	स्थिर पूर्णांक mask_all[4] = अणु 0xFF, 0xFF, 0xFF, 0xFF पूर्ण;
	पूर्णांक ret = 0;

	मुक्त_irq(chip->chip_irq, chip);
	cancel_delayed_work_sync(&chip->work);

	ret = regmap_bulk_ग_लिखो(chip->regmap, DA9121_REG_SYS_MASK_0, mask_all, 4);
	अगर (ret != 0)
		dev_err(chip->dev, "Failed to set IRQ masks: %d\n", ret);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id da9121_i2c_id[] = अणु
	अणु"da9121", DA9121_TYPE_DA9121_DA9130पूर्ण,
	अणु"da9130", DA9121_TYPE_DA9121_DA9130पूर्ण,
	अणु"da9217", DA9121_TYPE_DA9217पूर्ण,
	अणु"da9122", DA9121_TYPE_DA9122_DA9131पूर्ण,
	अणु"da9131", DA9121_TYPE_DA9122_DA9131पूर्ण,
	अणु"da9220", DA9121_TYPE_DA9220_DA9132पूर्ण,
	अणु"da9132", DA9121_TYPE_DA9220_DA9132पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, da9121_i2c_id);

अटल काष्ठा i2c_driver da9121_regulator_driver = अणु
	.driver = अणु
		.name = "da9121",
		.of_match_table = of_match_ptr(da9121_dt_ids),
	पूर्ण,
	.probe = da9121_i2c_probe,
	.हटाओ = da9121_i2c_हटाओ,
	.id_table = da9121_i2c_id,
पूर्ण;

module_i2c_driver(da9121_regulator_driver);

MODULE_LICENSE("GPL v2");
