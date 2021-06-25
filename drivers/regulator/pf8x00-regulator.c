<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 NXP
 * Copyright (C) 2019 Boundary Devices
 * Copyright (C) 2020 Amarula Solutions(India)
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>

/* रेजिस्टरs */
#घोषणा PF8X00_DEVICEID			0x00
#घोषणा PF8X00_REVID			0x01
#घोषणा PF8X00_EMREV			0x02
#घोषणा PF8X00_PROGID			0x03
#घोषणा PF8X00_IMS_INT			0x04
#घोषणा PF8X00_IMS_THERM		0x07
#घोषणा PF8X00_SW_MODE_INT		0x0a
#घोषणा PF8X00_SW_MODE_MASK		0x0b
#घोषणा PF8X00_IMS_SW_ILIM		0x12
#घोषणा PF8X00_IMS_LDO_ILIM		0x15
#घोषणा PF8X00_IMS_SW_UV		0x18
#घोषणा PF8X00_IMS_SW_OV		0x1b
#घोषणा PF8X00_IMS_LDO_UV		0x1e
#घोषणा PF8X00_IMS_LDO_OV		0x21
#घोषणा PF8X00_IMS_PWRON		0x24
#घोषणा PF8X00_SYS_INT			0x27
#घोषणा PF8X00_HARD_FAULT		0x29
#घोषणा PF8X00_FSOB_FLAGS		0x2a
#घोषणा PF8X00_FSOB_SELECT		0x2b
#घोषणा PF8X00_ABIST_OV1		0x2c
#घोषणा PF8X00_ABIST_OV2		0x2d
#घोषणा PF8X00_ABIST_UV1		0x2e
#घोषणा PF8X00_ABIST_UV2		0x2f
#घोषणा PF8X00_TEST_FLAGS		0x30
#घोषणा PF8X00_ABIST_RUN		0x31
#घोषणा PF8X00_RANDOM_GEN		0x33
#घोषणा PF8X00_RANDOM_CHK		0x34
#घोषणा PF8X00_VMONEN1			0x35
#घोषणा PF8X00_VMONEN2			0x36
#घोषणा PF8X00_CTRL1			0x37
#घोषणा PF8X00_CTRL2			0x38
#घोषणा PF8X00_CTRL3			0x39
#घोषणा PF8X00_PWRUP_CTRL		0x3a
#घोषणा PF8X00_RESETBMCU		0x3c
#घोषणा PF8X00_PGOOD			0x3d
#घोषणा PF8X00_PWRDN_DLY1		0x3e
#घोषणा PF8X00_PWRDN_DLY2		0x3f
#घोषणा PF8X00_FREQ_CTRL		0x40
#घोषणा PF8X00_COINCELL_CTRL		0x41
#घोषणा PF8X00_PWRON			0x42
#घोषणा PF8X00_WD_CONFIG		0x43
#घोषणा PF8X00_WD_CLEAR			0x44
#घोषणा PF8X00_WD_EXPIRE		0x45
#घोषणा PF8X00_WD_COUNTER		0x46
#घोषणा PF8X00_FAULT_COUNTER		0x47
#घोषणा PF8X00_FSAFE_COUNTER		0x48
#घोषणा PF8X00_FAULT_TIMER		0x49
#घोषणा PF8X00_AMUX			0x4a
#घोषणा PF8X00_SW1_CONFIG1		0x4d
#घोषणा PF8X00_LDO1_CONFIG1		0x85
#घोषणा PF8X00_VSNVS_CONFIG1		0x9d
#घोषणा PF8X00_PAGE_SELECT		0x9f

/* regulators */
क्रमागत pf8x00_regulators अणु
	PF8X00_LDO1,
	PF8X00_LDO2,
	PF8X00_LDO3,
	PF8X00_LDO4,
	PF8X00_BUCK1,
	PF8X00_BUCK2,
	PF8X00_BUCK3,
	PF8X00_BUCK4,
	PF8X00_BUCK5,
	PF8X00_BUCK6,
	PF8X00_BUCK7,
	PF8X00_VSNVS,

	PF8X00_MAX_REGULATORS,
पूर्ण;

क्रमागत pf8x00_buck_states अणु
	SW_CONFIG1,
	SW_CONFIG2,
	SW_PWRUP,
	SW_MODE1,
	SW_RUN_VOLT,
	SW_STBY_VOLT,
पूर्ण;
#घोषणा PF8X00_SW_BASE(i)		(8 * (i - PF8X00_BUCK1) + PF8X00_SW1_CONFIG1)

क्रमागत pf8x00_lकरो_states अणु
	LDO_CONFIG1,
	LDO_CONFIG2,
	LDO_PWRUP,
	LDO_RUN_VOLT,
	LDO_STBY_VOLT,
पूर्ण;
#घोषणा PF8X00_LDO_BASE(i)		(6 * (i - PF8X00_LDO1) + PF8X00_LDO1_CONFIG1)

क्रमागत swxilim_bits अणु
	SWXILIM_2100_MA,
	SWXILIM_2600_MA,
	SWXILIM_3000_MA,
	SWXILIM_4500_MA,
पूर्ण;
#घोषणा PF8X00_SWXILIM_SHIFT		3
#घोषणा PF8X00_SWXILIM_MASK		GENMASK(4, 3)
#घोषणा PF8X00_SWXPHASE_MASK		GENMASK(2, 0)
#घोषणा PF8X00_SWXPHASE_SHIFT		7

क्रमागत pf8x00_devid अणु
	PF8100			= 0x0,
	PF8121A			= BIT(1),
	PF8200			= BIT(3),
पूर्ण;
#घोषणा PF8X00_FAM			BIT(6)
#घोषणा PF8X00_DEVICE_FAM_MASK		GENMASK(7, 4)
#घोषणा PF8X00_DEVICE_ID_MASK		GENMASK(3, 0)

काष्ठा pf8x00_regulator_data अणु
	काष्ठा regulator_desc desc;
	अचिन्हित पूर्णांक suspend_enable_reg;
	अचिन्हित पूर्णांक suspend_enable_mask;
	अचिन्हित पूर्णांक suspend_voltage_reg;
	अचिन्हित पूर्णांक suspend_voltage_cache;
पूर्ण;

काष्ठा pf8x00_chip अणु
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
पूर्ण;

अटल स्थिर काष्ठा regmap_config pf8x00_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = PF8X00_PAGE_SELECT,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

/* VLDOx output: 1.5V to 5.0V */
अटल स्थिर पूर्णांक pf8x00_lकरो_voltages[] = अणु
	1500000, 1600000, 1800000, 1850000, 2150000, 2500000, 2800000, 3000000,
	3100000, 3150000, 3200000, 3300000, 3350000, 1650000, 1700000, 5000000,
पूर्ण;

/* Output: 2.1A to 4.5A */
अटल स्थिर अचिन्हित पूर्णांक pf8x00_sw_current_table[] = अणु
	2100000, 2600000, 3000000, 4500000,
पूर्ण;

/* Output: 0.4V to 1.8V */
#घोषणा PF8XOO_SW1_6_VOLTAGE_NUM 0xB2
अटल स्थिर काष्ठा linear_range pf8x00_sw1_to_6_voltages[] = अणु
	REGULATOR_LINEAR_RANGE(400000, 0x00, 0xB0, 6250),
	REGULATOR_LINEAR_RANGE(1800000, 0xB1, 0xB1, 0),
पूर्ण;

/* Output: 1.0V to 4.1V */
अटल स्थिर पूर्णांक pf8x00_sw7_voltages[] = अणु
	1000000, 1100000, 1200000, 1250000, 1300000, 1350000, 1500000, 1600000,
	1800000, 1850000, 2000000, 2100000, 2150000, 2250000, 2300000, 2400000,
	2500000, 2800000, 3150000, 3200000, 3250000, 3300000, 3350000, 3400000,
	3500000, 3800000, 4000000, 4100000, 4100000, 4100000, 4100000, 4100000,
पूर्ण;

/* Output: 1.8V, 3.0V, or 3.3V */
अटल स्थिर पूर्णांक pf8x00_vsnvs_voltages[] = अणु
	0, 1800000, 3000000, 3300000,
पूर्ण;

अटल व्योम swxilim_select(काष्ठा pf8x00_chip *chip, पूर्णांक id, पूर्णांक ilim)
अणु
	u8 ilim_sel;
	u8 reg = PF8X00_SW_BASE(id) + SW_CONFIG2;

	चयन (ilim) अणु
	हाल 2100:
		ilim_sel = SWXILIM_2100_MA;
		अवरोध;
	हाल 2600:
		ilim_sel = SWXILIM_2600_MA;
		अवरोध;
	हाल 3000:
		ilim_sel = SWXILIM_3000_MA;
		अवरोध;
	हाल 4500:
		ilim_sel = SWXILIM_4500_MA;
		अवरोध;
	शेष:
		ilim_sel = SWXILIM_2100_MA;
		अवरोध;
	पूर्ण

	regmap_update_bits(chip->regmap, reg,
					PF8X00_SWXILIM_MASK,
					ilim_sel << PF8X00_SWXILIM_SHIFT);
पूर्ण

अटल व्योम handle_ilim_property(काष्ठा device_node *np,
			      स्थिर काष्ठा regulator_desc *desc,
			      काष्ठा regulator_config *config)
अणु
	काष्ठा pf8x00_chip *chip = config->driver_data;
	पूर्णांक ret;
	पूर्णांक val;

	अगर ((desc->id >= PF8X00_BUCK1) && (desc->id <= PF8X00_BUCK7)) अणु
		ret = of_property_पढ़ो_u32(np, "nxp,ilim-ma", &val);
		अगर (ret) अणु
			dev_dbg(chip->dev, "unspecified ilim for BUCK%d, use value stored in OTP\n",
				desc->id - PF8X00_LDO4);
			वापस;
		पूर्ण

		dev_warn(chip->dev, "nxp,ilim-ma is deprecated, please use regulator-max-microamp\n");
		swxilim_select(chip, desc->id, val);

	पूर्ण अन्यथा
		dev_warn(chip->dev, "nxp,ilim-ma used with incorrect regulator (%d)\n", desc->id);
पूर्ण

अटल व्योम handle_shअगरt_property(काष्ठा device_node *np,
			      स्थिर काष्ठा regulator_desc *desc,
			      काष्ठा regulator_config *config)
अणु
	अचिन्हित अक्षर id = desc->id - PF8X00_LDO4;
	अचिन्हित अक्षर reg = PF8X00_SW_BASE(id) + SW_CONFIG2;
	काष्ठा pf8x00_chip *chip = config->driver_data;

	पूर्णांक phase;
	पूर्णांक val;
	पूर्णांक ret;
	अगर ((desc->id >= PF8X00_BUCK1) && (desc->id <= PF8X00_BUCK7)) अणु
		ret = of_property_पढ़ो_u32(np, "nxp,phase-shift", &val);
		अगर (ret) अणु
			dev_dbg(chip->dev,
				"unspecified phase-shift for BUCK%d, using OTP configuration\n",
				id);
			वापस;
		पूर्ण

		अगर (val < 0 || val > 315 || val % 45 != 0) अणु
			dev_warn(config->dev,
				"invalid phase_shift %d for BUCK%d, using OTP configuration\n",
				val, id);
			वापस;
		पूर्ण

		phase = val / 45;

		अगर (phase >= 1)
			phase -= 1;
		अन्यथा
			phase = PF8X00_SWXPHASE_SHIFT;

		regmap_update_bits(chip->regmap, reg,
				PF8X00_SWXPHASE_MASK,
				phase);
	पूर्ण अन्यथा
		dev_warn(chip->dev, "nxp,phase-shift used with incorrect regulator (%d)\n", id);

पूर्ण

अटल पूर्णांक pf8x00_of_parse_cb(काष्ठा device_node *np,
			      स्थिर काष्ठा regulator_desc *desc,
			      काष्ठा regulator_config *config)
अणु

	handle_ilim_property(np, desc, config);
	handle_shअगरt_property(np, desc, config);

	वापस 0;
पूर्ण

अटल पूर्णांक pf8x00_suspend_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा pf8x00_regulator_data *regl = rdev_get_drvdata(rdev);
	काष्ठा regmap *rmap = rdev_get_regmap(rdev);

	वापस regmap_update_bits(rmap, regl->suspend_enable_reg,
				  regl->suspend_enable_mask,
				  regl->suspend_enable_mask);
पूर्ण

अटल पूर्णांक pf8x00_suspend_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा pf8x00_regulator_data *regl = rdev_get_drvdata(rdev);
	काष्ठा regmap *rmap = rdev_get_regmap(rdev);

	वापस regmap_update_bits(rmap, regl->suspend_enable_reg,
				  regl->suspend_enable_mask, 0);
पूर्ण

अटल पूर्णांक pf8x00_set_suspend_voltage(काष्ठा regulator_dev *rdev, पूर्णांक uV)
अणु
	काष्ठा pf8x00_regulator_data *regl = rdev_get_drvdata(rdev);
	पूर्णांक ret;

	अगर (regl->suspend_voltage_cache == uV)
		वापस 0;

	ret = regulator_map_voltage_iterate(rdev, uV, uV);
	अगर (ret < 0) अणु
		dev_err(rdev_get_dev(rdev), "failed to map %i uV\n", uV);
		वापस ret;
	पूर्ण

	dev_dbg(rdev_get_dev(rdev), "uV: %i, reg: 0x%x, msk: 0x%x, val: 0x%x\n",
		uV, regl->suspend_voltage_reg, regl->desc.vsel_mask, ret);
	ret = regmap_update_bits(rdev->regmap, regl->suspend_voltage_reg,
				 regl->desc.vsel_mask, ret);
	अगर (ret < 0) अणु
		dev_err(rdev_get_dev(rdev), "failed to set %i uV\n", uV);
		वापस ret;
	पूर्ण

	regl->suspend_voltage_cache = uV;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regulator_ops pf8x00_lकरो_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_table,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_suspend_enable = pf8x00_suspend_enable,
	.set_suspend_disable = pf8x00_suspend_disable,
	.set_suspend_voltage = pf8x00_set_suspend_voltage,
पूर्ण;


अटल स्थिर काष्ठा regulator_ops pf8x00_buck1_6_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_linear_range,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.get_current_limit = regulator_get_current_limit_regmap,
	.set_current_limit = regulator_set_current_limit_regmap,
	.set_suspend_enable = pf8x00_suspend_enable,
	.set_suspend_disable = pf8x00_suspend_disable,
	.set_suspend_voltage = pf8x00_set_suspend_voltage,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops pf8x00_buck7_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.get_current_limit = regulator_get_current_limit_regmap,
	.set_current_limit = regulator_set_current_limit_regmap,
	.set_suspend_enable = pf8x00_suspend_enable,
	.set_suspend_disable = pf8x00_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops pf8x00_vsnvs_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
पूर्ण;

#घोषणा PF8X00LDO(_id, _name, base, voltages)			\
	[PF8X00_LDO ## _id] = अणु					\
		.desc = अणु					\
			.name = _name,				\
			.of_match = _name,			\
			.regulators_node = "regulators",	\
			.n_voltages = ARRAY_SIZE(voltages),	\
			.ops = &pf8x00_lकरो_ops,			\
			.type = REGULATOR_VOLTAGE,		\
			.id = PF8X00_LDO ## _id,		\
			.owner = THIS_MODULE,			\
			.volt_table = voltages,			\
			.vsel_reg = (base) + LDO_RUN_VOLT,	\
			.vsel_mask = 0xff,			\
			.enable_reg = (base) + LDO_CONFIG2,	\
			.enable_val = 0x2,			\
			.disable_val = 0x0,			\
			.enable_mask = 2,			\
		पूर्ण,						\
		.suspend_enable_reg = (base) + LDO_CONFIG2,	\
		.suspend_enable_mask = 1,			\
		.suspend_voltage_reg = (base) + LDO_STBY_VOLT,	\
	पूर्ण

#घोषणा PF8X00BUCK(_id, _name, base, voltages)			\
	[PF8X00_BUCK ## _id] = अणु				\
		.desc = अणु					\
			.name = _name,				\
			.of_match = _name,			\
			.regulators_node = "regulators",	\
			.of_parse_cb = pf8x00_of_parse_cb,	\
			.n_voltages = PF8XOO_SW1_6_VOLTAGE_NUM,	\
			.ops = &pf8x00_buck1_6_ops,		\
			.type = REGULATOR_VOLTAGE,		\
			.id = PF8X00_BUCK ## _id,		\
			.owner = THIS_MODULE,			\
			.ramp_delay = 19000,			\
			.linear_ranges = pf8x00_sw1_to_6_voltages, \
			.n_linear_ranges = \
				ARRAY_SIZE(pf8x00_sw1_to_6_voltages), \
			.vsel_reg = (base) + SW_RUN_VOLT,	\
			.vsel_mask = 0xff,			\
			.curr_table = pf8x00_sw_current_table, \
			.n_current_limits = \
				ARRAY_SIZE(pf8x00_sw_current_table), \
			.csel_reg = (base) + SW_CONFIG2,	\
			.csel_mask = PF8X00_SWXILIM_MASK,	\
			.enable_reg = (base) + SW_MODE1,	\
			.enable_val = 0x3,			\
			.disable_val = 0x0,			\
			.enable_mask = 0x3,			\
			.enable_समय = 500,			\
		पूर्ण,						\
		.suspend_enable_reg = (base) + SW_MODE1,	\
		.suspend_enable_mask = 0xc,			\
		.suspend_voltage_reg = (base) + SW_STBY_VOLT,	\
	पूर्ण

#घोषणा PF8X00BUCK7(_name, base, voltages)			\
	[PF8X00_BUCK7] = अणु				\
		.desc = अणु					\
			.name = _name,				\
			.of_match = _name,			\
			.regulators_node = "regulators",	\
			.of_parse_cb = pf8x00_of_parse_cb,	\
			.n_voltages = ARRAY_SIZE(voltages),	\
			.ops = &pf8x00_buck7_ops,		\
			.type = REGULATOR_VOLTAGE,		\
			.id = PF8X00_BUCK7,		\
			.owner = THIS_MODULE,			\
			.ramp_delay = 19000,			\
			.volt_table = voltages,			\
			.vsel_reg = (base) + SW_RUN_VOLT,	\
			.vsel_mask = 0xff,			\
			.curr_table = pf8x00_sw_current_table, \
			.n_current_limits = \
				ARRAY_SIZE(pf8x00_sw_current_table), \
			.csel_reg = (base) + SW_CONFIG2,	\
			.csel_mask = PF8X00_SWXILIM_MASK,	\
			.enable_reg = (base) + SW_MODE1,	\
			.enable_val = 0x3,			\
			.disable_val = 0x0,			\
			.enable_mask = 0x3,			\
			.enable_समय = 500,			\
		पूर्ण,						\
	पूर्ण


#घोषणा PF8X00VSNVS(_name, base, voltages)			\
	[PF8X00_VSNVS] = अणु					\
		.desc = अणु					\
			.name = _name,				\
			.of_match = _name,			\
			.regulators_node = "regulators",	\
			.n_voltages = ARRAY_SIZE(voltages),	\
			.ops = &pf8x00_vsnvs_ops,		\
			.type = REGULATOR_VOLTAGE,		\
			.id = PF8X00_VSNVS,			\
			.owner = THIS_MODULE,			\
			.volt_table = voltages,			\
			.vsel_reg = (base),			\
			.vsel_mask = 0x3,			\
		पूर्ण,						\
	पूर्ण

अटल काष्ठा pf8x00_regulator_data pf8x00_regs_data[PF8X00_MAX_REGULATORS] = अणु
	PF8X00LDO(1, "ldo1", PF8X00_LDO_BASE(PF8X00_LDO1), pf8x00_lकरो_voltages),
	PF8X00LDO(2, "ldo2", PF8X00_LDO_BASE(PF8X00_LDO2), pf8x00_lकरो_voltages),
	PF8X00LDO(3, "ldo3", PF8X00_LDO_BASE(PF8X00_LDO3), pf8x00_lकरो_voltages),
	PF8X00LDO(4, "ldo4", PF8X00_LDO_BASE(PF8X00_LDO4), pf8x00_lकरो_voltages),
	PF8X00BUCK(1, "buck1", PF8X00_SW_BASE(PF8X00_BUCK1), pf8x00_sw1_to_6_voltages),
	PF8X00BUCK(2, "buck2", PF8X00_SW_BASE(PF8X00_BUCK2), pf8x00_sw1_to_6_voltages),
	PF8X00BUCK(3, "buck3", PF8X00_SW_BASE(PF8X00_BUCK3), pf8x00_sw1_to_6_voltages),
	PF8X00BUCK(4, "buck4", PF8X00_SW_BASE(PF8X00_BUCK4), pf8x00_sw1_to_6_voltages),
	PF8X00BUCK(5, "buck5", PF8X00_SW_BASE(PF8X00_BUCK5), pf8x00_sw1_to_6_voltages),
	PF8X00BUCK(6, "buck6", PF8X00_SW_BASE(PF8X00_BUCK6), pf8x00_sw1_to_6_voltages),
	PF8X00BUCK7("buck7", PF8X00_SW_BASE(PF8X00_BUCK7), pf8x00_sw7_voltages),
	PF8X00VSNVS("vsnvs", PF8X00_VSNVS_CONFIG1, pf8x00_vsnvs_voltages),
पूर्ण;

अटल पूर्णांक pf8x00_identअगरy(काष्ठा pf8x00_chip *chip)
अणु
	अचिन्हित पूर्णांक value;
	u8 dev_fam, dev_id;
	स्थिर अक्षर *name = शून्य;
	पूर्णांक ret;

	ret = regmap_पढ़ो(chip->regmap, PF8X00_DEVICEID, &value);
	अगर (ret) अणु
		dev_err(chip->dev, "failed to read chip family\n");
		वापस ret;
	पूर्ण

	dev_fam = value & PF8X00_DEVICE_FAM_MASK;
	चयन (dev_fam) अणु
	हाल PF8X00_FAM:
		अवरोध;
	शेष:
		dev_err(chip->dev,
			"Chip 0x%x is not from PF8X00 family\n", dev_fam);
		वापस ret;
	पूर्ण

	dev_id = value & PF8X00_DEVICE_ID_MASK;
	चयन (dev_id) अणु
	हाल PF8100:
		name = "PF8100";
		अवरोध;
	हाल PF8121A:
		name = "PF8121A";
		अवरोध;
	हाल PF8200:
		name = "PF8200";
		अवरोध;
	शेष:
		dev_err(chip->dev, "Unknown pf8x00 device id 0x%x\n", dev_id);
		वापस -ENODEV;
	पूर्ण

	dev_info(chip->dev, "%s PMIC found.\n", name);

	वापस 0;
पूर्ण

अटल पूर्णांक pf8x00_i2c_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा regulator_config config = अणु शून्य, पूर्ण;
	काष्ठा pf8x00_chip *chip;
	पूर्णांक id;
	पूर्णांक ret;

	chip = devm_kzalloc(&client->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	i2c_set_clientdata(client, chip);
	chip->dev = &client->dev;

	chip->regmap = devm_regmap_init_i2c(client, &pf8x00_regmap_config);
	अगर (IS_ERR(chip->regmap)) अणु
		ret = PTR_ERR(chip->regmap);
		dev_err(&client->dev,
			"regmap allocation failed with err %d\n", ret);
		वापस ret;
	पूर्ण

	ret = pf8x00_identअगरy(chip);
	अगर (ret)
		वापस ret;

	क्रम (id = 0; id < ARRAY_SIZE(pf8x00_regs_data); id++) अणु
		काष्ठा pf8x00_regulator_data *data = &pf8x00_regs_data[id];
		काष्ठा regulator_dev *rdev;

		config.dev = chip->dev;
		config.driver_data = data;
		config.regmap = chip->regmap;

		rdev = devm_regulator_रेजिस्टर(&client->dev, &data->desc, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&client->dev,
				"failed to register %s regulator\n", data->desc.name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pf8x00_dt_ids[] = अणु
	अणु .compatible = "nxp,pf8100",पूर्ण,
	अणु .compatible = "nxp,pf8121a",पूर्ण,
	अणु .compatible = "nxp,pf8200",पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pf8x00_dt_ids);

अटल स्थिर काष्ठा i2c_device_id pf8x00_i2c_id[] = अणु
	अणु "pf8100", 0 पूर्ण,
	अणु "pf8121a", 0 पूर्ण,
	अणु "pf8200", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pf8x00_i2c_id);

अटल काष्ठा i2c_driver pf8x00_regulator_driver = अणु
	.id_table = pf8x00_i2c_id,
	.driver = अणु
		.name = "pf8x00",
		.of_match_table = pf8x00_dt_ids,
	पूर्ण,
	.probe_new = pf8x00_i2c_probe,
पूर्ण;
module_i2c_driver(pf8x00_regulator_driver);

MODULE_AUTHOR("Jagan Teki <jagan@amarulasolutions.com>");
MODULE_AUTHOR("Troy Kisky <troy.kisky@boundarydevices.com>");
MODULE_DESCRIPTION("Regulator Driver for NXP's PF8100/PF8121A/PF8200 PMIC");
MODULE_LICENSE("GPL v2");
