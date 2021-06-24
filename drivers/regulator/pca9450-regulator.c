<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2020 NXP.
 * NXP PCA9450 pmic driver
 */

#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/regulator/pca9450.h>

काष्ठा pc9450_dvs_config अणु
	अचिन्हित पूर्णांक run_reg; /* dvs0 */
	अचिन्हित पूर्णांक run_mask;
	अचिन्हित पूर्णांक standby_reg; /* dvs1 */
	अचिन्हित पूर्णांक standby_mask;
पूर्ण;

काष्ठा pca9450_regulator_desc अणु
	काष्ठा regulator_desc desc;
	स्थिर काष्ठा pc9450_dvs_config dvs;
पूर्ण;

काष्ठा pca9450 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा gpio_desc *sd_vsel_gpio;
	क्रमागत pca9450_chip_type type;
	अचिन्हित पूर्णांक rcnt;
	पूर्णांक irq;
पूर्ण;

अटल स्थिर काष्ठा regmap_range pca9450_status_range = अणु
	.range_min = PCA9450_REG_INT1,
	.range_max = PCA9450_REG_PWRON_STAT,
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table pca9450_अस्थिर_regs = अणु
	.yes_ranges = &pca9450_status_range,
	.n_yes_ranges = 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config pca9450_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.अस्थिर_table = &pca9450_अस्थिर_regs,
	.max_रेजिस्टर = PCA9450_MAX_REGISTER - 1,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

/*
 * BUCK1/2/3
 * BUCK1RAM[1:0] BUCK1 DVS ramp rate setting
 * 00: 25mV/1usec
 * 01: 25mV/2usec
 * 10: 25mV/4usec
 * 11: 25mV/8usec
 */
अटल पूर्णांक pca9450_dvs_set_ramp_delay(काष्ठा regulator_dev *rdev,
				      पूर्णांक ramp_delay)
अणु
	पूर्णांक id = rdev_get_id(rdev);
	अचिन्हित पूर्णांक ramp_value;

	चयन (ramp_delay) अणु
	हाल 1 ... 3125:
		ramp_value = BUCK1_RAMP_3P125MV;
		अवरोध;
	हाल 3126 ... 6250:
		ramp_value = BUCK1_RAMP_6P25MV;
		अवरोध;
	हाल 6251 ... 12500:
		ramp_value = BUCK1_RAMP_12P5MV;
		अवरोध;
	हाल 12501 ... 25000:
		ramp_value = BUCK1_RAMP_25MV;
		अवरोध;
	शेष:
		ramp_value = BUCK1_RAMP_25MV;
	पूर्ण

	वापस regmap_update_bits(rdev->regmap, PCA9450_REG_BUCK1CTRL + id * 3,
				  BUCK1_RAMP_MASK, ramp_value << 6);
पूर्ण

अटल स्थिर काष्ठा regulator_ops pca9450_dvs_buck_regulator_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_linear_range,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.set_ramp_delay = pca9450_dvs_set_ramp_delay,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops pca9450_buck_regulator_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_linear_range,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops pca9450_lकरो_regulator_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_linear_range,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
पूर्ण;

/*
 * BUCK1/2/3
 * 0.60 to 2.1875V (12.5mV step)
 */
अटल स्थिर काष्ठा linear_range pca9450_dvs_buck_volts[] = अणु
	REGULATOR_LINEAR_RANGE(600000,  0x00, 0x7F, 12500),
पूर्ण;

/*
 * BUCK4/5/6
 * 0.6V to 3.4V (25mV step)
 */
अटल स्थिर काष्ठा linear_range pca9450_buck_volts[] = अणु
	REGULATOR_LINEAR_RANGE(600000, 0x00, 0x70, 25000),
	REGULATOR_LINEAR_RANGE(3400000, 0x71, 0x7F, 0),
पूर्ण;

/*
 * LDO1
 * 1.6 to 3.3V ()
 */
अटल स्थिर काष्ठा linear_range pca9450_lकरो1_volts[] = अणु
	REGULATOR_LINEAR_RANGE(1600000, 0x00, 0x03, 100000),
	REGULATOR_LINEAR_RANGE(3000000, 0x04, 0x07, 100000),
पूर्ण;

/*
 * LDO2
 * 0.8 to 1.15V (50mV step)
 */
अटल स्थिर काष्ठा linear_range pca9450_lकरो2_volts[] = अणु
	REGULATOR_LINEAR_RANGE(800000, 0x00, 0x07, 50000),
पूर्ण;

/*
 * LDO3/4
 * 0.8 to 3.3V (100mV step)
 */
अटल स्थिर काष्ठा linear_range pca9450_lकरो34_volts[] = अणु
	REGULATOR_LINEAR_RANGE(800000, 0x00, 0x19, 100000),
	REGULATOR_LINEAR_RANGE(3300000, 0x1A, 0x1F, 0),
पूर्ण;

/*
 * LDO5
 * 1.8 to 3.3V (100mV step)
 */
अटल स्थिर काष्ठा linear_range pca9450_lकरो5_volts[] = अणु
	REGULATOR_LINEAR_RANGE(1800000,  0x00, 0x0F, 100000),
पूर्ण;

अटल पूर्णांक buck_set_dvs(स्थिर काष्ठा regulator_desc *desc,
			काष्ठा device_node *np, काष्ठा regmap *regmap,
			अक्षर *prop, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask)
अणु
	पूर्णांक ret, i;
	uपूर्णांक32_t uv;

	ret = of_property_पढ़ो_u32(np, prop, &uv);
	अगर (ret == -EINVAL)
		वापस 0;
	अन्यथा अगर (ret)
		वापस ret;

	क्रम (i = 0; i < desc->n_voltages; i++) अणु
		ret = regulator_desc_list_voltage_linear_range(desc, i);
		अगर (ret < 0)
			जारी;
		अगर (ret == uv) अणु
			i <<= ffs(desc->vsel_mask) - 1;
			ret = regmap_update_bits(regmap, reg, mask, i);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pca9450_set_dvs_levels(काष्ठा device_node *np,
			    स्थिर काष्ठा regulator_desc *desc,
			    काष्ठा regulator_config *cfg)
अणु
	काष्ठा pca9450_regulator_desc *data = container_of(desc,
					काष्ठा pca9450_regulator_desc, desc);
	स्थिर काष्ठा pc9450_dvs_config *dvs = &data->dvs;
	अचिन्हित पूर्णांक reg, mask;
	अक्षर *prop;
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < PCA9450_DVS_LEVEL_MAX; i++) अणु
		चयन (i) अणु
		हाल PCA9450_DVS_LEVEL_RUN:
			prop = "nxp,dvs-run-voltage";
			reg = dvs->run_reg;
			mask = dvs->run_mask;
			अवरोध;
		हाल PCA9450_DVS_LEVEL_STANDBY:
			prop = "nxp,dvs-standby-voltage";
			reg = dvs->standby_reg;
			mask = dvs->standby_mask;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = buck_set_dvs(desc, np, cfg->regmap, prop, reg, mask);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pca9450_regulator_desc pca9450a_regulators[] = अणु
	अणु
		.desc = अणु
			.name = "buck1",
			.of_match = of_match_ptr("BUCK1"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_BUCK1,
			.ops = &pca9450_dvs_buck_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_BUCK1_VOLTAGE_NUM,
			.linear_ranges = pca9450_dvs_buck_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_dvs_buck_volts),
			.vsel_reg = PCA9450_REG_BUCK1OUT_DVS0,
			.vsel_mask = BUCK1OUT_DVS0_MASK,
			.enable_reg = PCA9450_REG_BUCK1CTRL,
			.enable_mask = BUCK1_ENMODE_MASK,
			.owner = THIS_MODULE,
			.of_parse_cb = pca9450_set_dvs_levels,
		पूर्ण,
		.dvs = अणु
			.run_reg = PCA9450_REG_BUCK1OUT_DVS0,
			.run_mask = BUCK1OUT_DVS0_MASK,
			.standby_reg = PCA9450_REG_BUCK1OUT_DVS1,
			.standby_mask = BUCK1OUT_DVS1_MASK,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck2",
			.of_match = of_match_ptr("BUCK2"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_BUCK2,
			.ops = &pca9450_dvs_buck_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_BUCK2_VOLTAGE_NUM,
			.linear_ranges = pca9450_dvs_buck_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_dvs_buck_volts),
			.vsel_reg = PCA9450_REG_BUCK2OUT_DVS0,
			.vsel_mask = BUCK2OUT_DVS0_MASK,
			.enable_reg = PCA9450_REG_BUCK2CTRL,
			.enable_mask = BUCK1_ENMODE_MASK,
			.owner = THIS_MODULE,
			.of_parse_cb = pca9450_set_dvs_levels,
		पूर्ण,
		.dvs = अणु
			.run_reg = PCA9450_REG_BUCK2OUT_DVS0,
			.run_mask = BUCK2OUT_DVS0_MASK,
			.standby_reg = PCA9450_REG_BUCK2OUT_DVS1,
			.standby_mask = BUCK2OUT_DVS1_MASK,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck3",
			.of_match = of_match_ptr("BUCK3"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_BUCK3,
			.ops = &pca9450_dvs_buck_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_BUCK3_VOLTAGE_NUM,
			.linear_ranges = pca9450_dvs_buck_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_dvs_buck_volts),
			.vsel_reg = PCA9450_REG_BUCK3OUT_DVS0,
			.vsel_mask = BUCK3OUT_DVS0_MASK,
			.enable_reg = PCA9450_REG_BUCK3CTRL,
			.enable_mask = BUCK3_ENMODE_MASK,
			.owner = THIS_MODULE,
			.of_parse_cb = pca9450_set_dvs_levels,
		पूर्ण,
		.dvs = अणु
			.run_reg = PCA9450_REG_BUCK3OUT_DVS0,
			.run_mask = BUCK3OUT_DVS0_MASK,
			.standby_reg = PCA9450_REG_BUCK3OUT_DVS1,
			.standby_mask = BUCK3OUT_DVS1_MASK,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck4",
			.of_match = of_match_ptr("BUCK4"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_BUCK4,
			.ops = &pca9450_buck_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_BUCK4_VOLTAGE_NUM,
			.linear_ranges = pca9450_buck_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_buck_volts),
			.vsel_reg = PCA9450_REG_BUCK4OUT,
			.vsel_mask = BUCK4OUT_MASK,
			.enable_reg = PCA9450_REG_BUCK4CTRL,
			.enable_mask = BUCK4_ENMODE_MASK,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck5",
			.of_match = of_match_ptr("BUCK5"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_BUCK5,
			.ops = &pca9450_buck_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_BUCK5_VOLTAGE_NUM,
			.linear_ranges = pca9450_buck_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_buck_volts),
			.vsel_reg = PCA9450_REG_BUCK5OUT,
			.vsel_mask = BUCK5OUT_MASK,
			.enable_reg = PCA9450_REG_BUCK5CTRL,
			.enable_mask = BUCK5_ENMODE_MASK,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck6",
			.of_match = of_match_ptr("BUCK6"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_BUCK6,
			.ops = &pca9450_buck_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_BUCK6_VOLTAGE_NUM,
			.linear_ranges = pca9450_buck_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_buck_volts),
			.vsel_reg = PCA9450_REG_BUCK6OUT,
			.vsel_mask = BUCK6OUT_MASK,
			.enable_reg = PCA9450_REG_BUCK6CTRL,
			.enable_mask = BUCK6_ENMODE_MASK,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo1",
			.of_match = of_match_ptr("LDO1"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_LDO1,
			.ops = &pca9450_lकरो_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_LDO1_VOLTAGE_NUM,
			.linear_ranges = pca9450_lकरो1_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_lकरो1_volts),
			.vsel_reg = PCA9450_REG_LDO1CTRL,
			.vsel_mask = LDO1OUT_MASK,
			.enable_reg = PCA9450_REG_LDO1CTRL,
			.enable_mask = LDO1_EN_MASK,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo2",
			.of_match = of_match_ptr("LDO2"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_LDO2,
			.ops = &pca9450_lकरो_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_LDO2_VOLTAGE_NUM,
			.linear_ranges = pca9450_lकरो2_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_lकरो2_volts),
			.vsel_reg = PCA9450_REG_LDO2CTRL,
			.vsel_mask = LDO2OUT_MASK,
			.enable_reg = PCA9450_REG_LDO2CTRL,
			.enable_mask = LDO2_EN_MASK,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo3",
			.of_match = of_match_ptr("LDO3"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_LDO3,
			.ops = &pca9450_lकरो_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_LDO3_VOLTAGE_NUM,
			.linear_ranges = pca9450_lकरो34_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_lकरो34_volts),
			.vsel_reg = PCA9450_REG_LDO3CTRL,
			.vsel_mask = LDO3OUT_MASK,
			.enable_reg = PCA9450_REG_LDO3CTRL,
			.enable_mask = LDO3_EN_MASK,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo4",
			.of_match = of_match_ptr("LDO4"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_LDO4,
			.ops = &pca9450_lकरो_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_LDO4_VOLTAGE_NUM,
			.linear_ranges = pca9450_lकरो34_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_lकरो34_volts),
			.vsel_reg = PCA9450_REG_LDO4CTRL,
			.vsel_mask = LDO4OUT_MASK,
			.enable_reg = PCA9450_REG_LDO4CTRL,
			.enable_mask = LDO4_EN_MASK,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo5",
			.of_match = of_match_ptr("LDO5"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_LDO5,
			.ops = &pca9450_lकरो_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_LDO5_VOLTAGE_NUM,
			.linear_ranges = pca9450_lकरो5_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_lकरो5_volts),
			.vsel_reg = PCA9450_REG_LDO5CTRL_H,
			.vsel_mask = LDO5HOUT_MASK,
			.enable_reg = PCA9450_REG_LDO5CTRL_H,
			.enable_mask = LDO5H_EN_MASK,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

/*
 * Buck3 हटाओd on PCA9450B and connected with Buck1 पूर्णांकernal क्रम dual phase
 * on PCA9450C as no Buck3.
 */
अटल स्थिर काष्ठा pca9450_regulator_desc pca9450bc_regulators[] = अणु
	अणु
		.desc = अणु
			.name = "buck1",
			.of_match = of_match_ptr("BUCK1"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_BUCK1,
			.ops = &pca9450_dvs_buck_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_BUCK1_VOLTAGE_NUM,
			.linear_ranges = pca9450_dvs_buck_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_dvs_buck_volts),
			.vsel_reg = PCA9450_REG_BUCK1OUT_DVS0,
			.vsel_mask = BUCK1OUT_DVS0_MASK,
			.enable_reg = PCA9450_REG_BUCK1CTRL,
			.enable_mask = BUCK1_ENMODE_MASK,
			.owner = THIS_MODULE,
			.of_parse_cb = pca9450_set_dvs_levels,
		पूर्ण,
		.dvs = अणु
			.run_reg = PCA9450_REG_BUCK1OUT_DVS0,
			.run_mask = BUCK1OUT_DVS0_MASK,
			.standby_reg = PCA9450_REG_BUCK1OUT_DVS1,
			.standby_mask = BUCK1OUT_DVS1_MASK,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck2",
			.of_match = of_match_ptr("BUCK2"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_BUCK2,
			.ops = &pca9450_dvs_buck_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_BUCK2_VOLTAGE_NUM,
			.linear_ranges = pca9450_dvs_buck_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_dvs_buck_volts),
			.vsel_reg = PCA9450_REG_BUCK2OUT_DVS0,
			.vsel_mask = BUCK2OUT_DVS0_MASK,
			.enable_reg = PCA9450_REG_BUCK2CTRL,
			.enable_mask = BUCK1_ENMODE_MASK,
			.owner = THIS_MODULE,
			.of_parse_cb = pca9450_set_dvs_levels,
		पूर्ण,
		.dvs = अणु
			.run_reg = PCA9450_REG_BUCK2OUT_DVS0,
			.run_mask = BUCK2OUT_DVS0_MASK,
			.standby_reg = PCA9450_REG_BUCK2OUT_DVS1,
			.standby_mask = BUCK2OUT_DVS1_MASK,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck4",
			.of_match = of_match_ptr("BUCK4"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_BUCK4,
			.ops = &pca9450_buck_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_BUCK4_VOLTAGE_NUM,
			.linear_ranges = pca9450_buck_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_buck_volts),
			.vsel_reg = PCA9450_REG_BUCK4OUT,
			.vsel_mask = BUCK4OUT_MASK,
			.enable_reg = PCA9450_REG_BUCK4CTRL,
			.enable_mask = BUCK4_ENMODE_MASK,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck5",
			.of_match = of_match_ptr("BUCK5"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_BUCK5,
			.ops = &pca9450_buck_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_BUCK5_VOLTAGE_NUM,
			.linear_ranges = pca9450_buck_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_buck_volts),
			.vsel_reg = PCA9450_REG_BUCK5OUT,
			.vsel_mask = BUCK5OUT_MASK,
			.enable_reg = PCA9450_REG_BUCK5CTRL,
			.enable_mask = BUCK5_ENMODE_MASK,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck6",
			.of_match = of_match_ptr("BUCK6"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_BUCK6,
			.ops = &pca9450_buck_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_BUCK6_VOLTAGE_NUM,
			.linear_ranges = pca9450_buck_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_buck_volts),
			.vsel_reg = PCA9450_REG_BUCK6OUT,
			.vsel_mask = BUCK6OUT_MASK,
			.enable_reg = PCA9450_REG_BUCK6CTRL,
			.enable_mask = BUCK6_ENMODE_MASK,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo1",
			.of_match = of_match_ptr("LDO1"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_LDO1,
			.ops = &pca9450_lकरो_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_LDO1_VOLTAGE_NUM,
			.linear_ranges = pca9450_lकरो1_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_lकरो1_volts),
			.vsel_reg = PCA9450_REG_LDO1CTRL,
			.vsel_mask = LDO1OUT_MASK,
			.enable_reg = PCA9450_REG_LDO1CTRL,
			.enable_mask = LDO1_EN_MASK,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo2",
			.of_match = of_match_ptr("LDO2"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_LDO2,
			.ops = &pca9450_lकरो_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_LDO2_VOLTAGE_NUM,
			.linear_ranges = pca9450_lकरो2_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_lकरो2_volts),
			.vsel_reg = PCA9450_REG_LDO2CTRL,
			.vsel_mask = LDO2OUT_MASK,
			.enable_reg = PCA9450_REG_LDO2CTRL,
			.enable_mask = LDO2_EN_MASK,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo3",
			.of_match = of_match_ptr("LDO3"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_LDO3,
			.ops = &pca9450_lकरो_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_LDO3_VOLTAGE_NUM,
			.linear_ranges = pca9450_lकरो34_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_lकरो34_volts),
			.vsel_reg = PCA9450_REG_LDO3CTRL,
			.vsel_mask = LDO3OUT_MASK,
			.enable_reg = PCA9450_REG_LDO3CTRL,
			.enable_mask = LDO3_EN_MASK,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo4",
			.of_match = of_match_ptr("LDO4"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_LDO4,
			.ops = &pca9450_lकरो_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_LDO4_VOLTAGE_NUM,
			.linear_ranges = pca9450_lकरो34_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_lकरो34_volts),
			.vsel_reg = PCA9450_REG_LDO4CTRL,
			.vsel_mask = LDO4OUT_MASK,
			.enable_reg = PCA9450_REG_LDO4CTRL,
			.enable_mask = LDO4_EN_MASK,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo5",
			.of_match = of_match_ptr("LDO5"),
			.regulators_node = of_match_ptr("regulators"),
			.id = PCA9450_LDO5,
			.ops = &pca9450_lकरो_regulator_ops,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = PCA9450_LDO5_VOLTAGE_NUM,
			.linear_ranges = pca9450_lकरो5_volts,
			.n_linear_ranges = ARRAY_SIZE(pca9450_lकरो5_volts),
			.vsel_reg = PCA9450_REG_LDO5CTRL_H,
			.vsel_mask = LDO5HOUT_MASK,
			.enable_reg = PCA9450_REG_LDO5CTRL_H,
			.enable_mask = LDO5H_EN_MASK,
			.owner = THIS_MODULE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल irqवापस_t pca9450_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pca9450 *pca9450 = data;
	काष्ठा regmap *regmap = pca9450->regmap;
	अचिन्हित पूर्णांक status;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, PCA9450_REG_INT1, &status);
	अगर (ret < 0) अणु
		dev_err(pca9450->dev,
			"Failed to read INT1(%d)\n", ret);
		वापस IRQ_NONE;
	पूर्ण

	अगर (status & IRQ_PWRON)
		dev_warn(pca9450->dev, "PWRON interrupt.\n");

	अगर (status & IRQ_WDOGB)
		dev_warn(pca9450->dev, "WDOGB interrupt.\n");

	अगर (status & IRQ_VR_FLT1)
		dev_warn(pca9450->dev, "VRFLT1 interrupt.\n");

	अगर (status & IRQ_VR_FLT2)
		dev_warn(pca9450->dev, "VRFLT2 interrupt.\n");

	अगर (status & IRQ_LOWVSYS)
		dev_warn(pca9450->dev, "LOWVSYS interrupt.\n");

	अगर (status & IRQ_THERM_105)
		dev_warn(pca9450->dev, "IRQ_THERM_105 interrupt.\n");

	अगर (status & IRQ_THERM_125)
		dev_warn(pca9450->dev, "IRQ_THERM_125 interrupt.\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pca9450_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	क्रमागत pca9450_chip_type type = (अचिन्हित पूर्णांक)(uपूर्णांकptr_t)
				      of_device_get_match_data(&i2c->dev);
	स्थिर काष्ठा pca9450_regulator_desc	*regulator_desc;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा pca9450 *pca9450;
	अचिन्हित पूर्णांक device_id, i;
	पूर्णांक ret;

	अगर (!i2c->irq) अणु
		dev_err(&i2c->dev, "No IRQ configured?\n");
		वापस -EINVAL;
	पूर्ण

	pca9450 = devm_kzalloc(&i2c->dev, माप(काष्ठा pca9450), GFP_KERNEL);
	अगर (!pca9450)
		वापस -ENOMEM;

	चयन (type) अणु
	हाल PCA9450_TYPE_PCA9450A:
		regulator_desc = pca9450a_regulators;
		pca9450->rcnt = ARRAY_SIZE(pca9450a_regulators);
		अवरोध;
	हाल PCA9450_TYPE_PCA9450BC:
		regulator_desc = pca9450bc_regulators;
		pca9450->rcnt = ARRAY_SIZE(pca9450bc_regulators);
		अवरोध;
	शेष:
		dev_err(&i2c->dev, "Unknown device type");
		वापस -EINVAL;
	पूर्ण

	pca9450->irq = i2c->irq;
	pca9450->type = type;
	pca9450->dev = &i2c->dev;

	dev_set_drvdata(&i2c->dev, pca9450);

	pca9450->regmap = devm_regmap_init_i2c(i2c,
					       &pca9450_regmap_config);
	अगर (IS_ERR(pca9450->regmap)) अणु
		dev_err(&i2c->dev, "regmap initialization failed\n");
		वापस PTR_ERR(pca9450->regmap);
	पूर्ण

	ret = regmap_पढ़ो(pca9450->regmap, PCA9450_REG_DEV_ID, &device_id);
	अगर (ret) अणु
		dev_err(&i2c->dev, "Read device id error\n");
		वापस ret;
	पूर्ण

	/* Check your board and dts क्रम match the right pmic */
	अगर (((device_id >> 4) != 0x1 && type == PCA9450_TYPE_PCA9450A) ||
	    ((device_id >> 4) != 0x3 && type == PCA9450_TYPE_PCA9450BC)) अणु
		dev_err(&i2c->dev, "Device id(%x) mismatched\n",
			device_id >> 4);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < pca9450->rcnt; i++) अणु
		स्थिर काष्ठा regulator_desc *desc;
		काष्ठा regulator_dev *rdev;
		स्थिर काष्ठा pca9450_regulator_desc *r;

		r = &regulator_desc[i];
		desc = &r->desc;

		config.regmap = pca9450->regmap;
		config.dev = pca9450->dev;

		rdev = devm_regulator_रेजिस्टर(pca9450->dev, desc, &config);
		अगर (IS_ERR(rdev)) अणु
			ret = PTR_ERR(rdev);
			dev_err(pca9450->dev,
				"Failed to register regulator(%s): %d\n",
				desc->name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(pca9450->dev, pca9450->irq, शून्य,
					pca9450_irq_handler,
					(IRQF_TRIGGER_FALLING | IRQF_ONESHOT),
					"pca9450-irq", pca9450);
	अगर (ret != 0) अणु
		dev_err(pca9450->dev, "Failed to request IRQ: %d\n",
			pca9450->irq);
		वापस ret;
	पूर्ण
	/* Unmask all पूर्णांकerrupt except PWRON/WDOG/RSVD */
	ret = regmap_update_bits(pca9450->regmap, PCA9450_REG_INT1_MSK,
				IRQ_VR_FLT1 | IRQ_VR_FLT2 | IRQ_LOWVSYS |
				IRQ_THERM_105 | IRQ_THERM_125,
				IRQ_PWRON | IRQ_WDOGB | IRQ_RSVD);
	अगर (ret) अणु
		dev_err(&i2c->dev, "Unmask irq error\n");
		वापस ret;
	पूर्ण

	/* Clear PRESET_EN bit in BUCK123_DVS to use DVS रेजिस्टरs */
	ret = regmap_clear_bits(pca9450->regmap, PCA9450_REG_BUCK123_DVS,
				BUCK123_PRESET_EN);
	अगर (ret) अणु
		dev_err(&i2c->dev, "Failed to clear PRESET_EN bit: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Set reset behavior on निश्चितion of WDOG_B संकेत */
	ret = regmap_update_bits(pca9450->regmap, PCA9450_REG_RESET_CTRL,
				WDOG_B_CFG_MASK, WDOG_B_CFG_COLD_LDO12);
	अगर (ret) अणु
		dev_err(&i2c->dev, "Failed to set WDOG_B reset behavior\n");
		वापस ret;
	पूर्ण

	/*
	 * The driver uses the LDO5CTRL_H रेजिस्टर to control the LDO5 regulator.
	 * This is only valid अगर the SD_VSEL input of the PMIC is high. Let's
	 * check अगर the pin is available as GPIO and set it to high.
	 */
	pca9450->sd_vsel_gpio = gpiod_get_optional(pca9450->dev, "sd-vsel", GPIOD_OUT_HIGH);

	अगर (IS_ERR(pca9450->sd_vsel_gpio)) अणु
		dev_err(&i2c->dev, "Failed to get SD_VSEL GPIO\n");
		वापस PTR_ERR(pca9450->sd_vsel_gpio);
	पूर्ण

	dev_info(&i2c->dev, "%s probed.\n",
		type == PCA9450_TYPE_PCA9450A ? "pca9450a" : "pca9450bc");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pca9450_of_match[] = अणु
	अणु
		.compatible = "nxp,pca9450a",
		.data = (व्योम *)PCA9450_TYPE_PCA9450A,
	पूर्ण,
	अणु
		.compatible = "nxp,pca9450b",
		.data = (व्योम *)PCA9450_TYPE_PCA9450BC,
	पूर्ण,
	अणु
		.compatible = "nxp,pca9450c",
		.data = (व्योम *)PCA9450_TYPE_PCA9450BC,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pca9450_of_match);

अटल काष्ठा i2c_driver pca9450_i2c_driver = अणु
	.driver = अणु
		.name = "nxp-pca9450",
		.of_match_table = pca9450_of_match,
	पूर्ण,
	.probe = pca9450_i2c_probe,
पूर्ण;

module_i2c_driver(pca9450_i2c_driver);

MODULE_AUTHOR("Robin Gong <yibin.gong@nxp.com>");
MODULE_DESCRIPTION("NXP PCA9450 Power Management IC driver");
MODULE_LICENSE("GPL");
