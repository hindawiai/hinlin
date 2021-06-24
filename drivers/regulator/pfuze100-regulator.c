<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (C) 2011-2013 Freescale Semiconductor, Inc. All Rights Reserved.

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/pfuze100.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>

#घोषणा PFUZE_FLAG_DISABLE_SW	BIT(1)

#घोषणा PFUZE_NUMREGS		128
#घोषणा PFUZE100_VOL_OFFSET	0
#घोषणा PFUZE100_STANDBY_OFFSET	1
#घोषणा PFUZE100_MODE_OFFSET	3
#घोषणा PFUZE100_CONF_OFFSET	4

#घोषणा PFUZE100_DEVICEID	0x0
#घोषणा PFUZE100_REVID		0x3
#घोषणा PFUZE100_FABID		0x4

#घोषणा PFUZE100_COINVOL	0x1a
#घोषणा PFUZE100_SW1ABVOL	0x20
#घोषणा PFUZE100_SW1ABMODE	0x23
#घोषणा PFUZE100_SW1CVOL	0x2e
#घोषणा PFUZE100_SW1CMODE	0x31
#घोषणा PFUZE100_SW2VOL		0x35
#घोषणा PFUZE100_SW2MODE	0x38
#घोषणा PFUZE100_SW3AVOL	0x3c
#घोषणा PFUZE100_SW3AMODE	0x3f
#घोषणा PFUZE100_SW3BVOL	0x43
#घोषणा PFUZE100_SW3BMODE	0x46
#घोषणा PFUZE100_SW4VOL		0x4a
#घोषणा PFUZE100_SW4MODE	0x4d
#घोषणा PFUZE100_SWBSTCON1	0x66
#घोषणा PFUZE100_VREFDDRCON	0x6a
#घोषणा PFUZE100_VSNVSVOL	0x6b
#घोषणा PFUZE100_VGEN1VOL	0x6c
#घोषणा PFUZE100_VGEN2VOL	0x6d
#घोषणा PFUZE100_VGEN3VOL	0x6e
#घोषणा PFUZE100_VGEN4VOL	0x6f
#घोषणा PFUZE100_VGEN5VOL	0x70
#घोषणा PFUZE100_VGEN6VOL	0x71

#घोषणा PFUZE100_SWxMODE_MASK	0xf
#घोषणा PFUZE100_SWxMODE_APS_APS	0x8
#घोषणा PFUZE100_SWxMODE_APS_OFF	0x4

#घोषणा PFUZE100_VGENxLPWR	BIT(6)
#घोषणा PFUZE100_VGENxSTBY	BIT(5)

क्रमागत chips अणु PFUZE100, PFUZE200, PFUZE3000 = 3, PFUZE3001 = 0x31, पूर्ण;

काष्ठा pfuze_regulator अणु
	काष्ठा regulator_desc desc;
	अचिन्हित अक्षर stby_reg;
	अचिन्हित अक्षर stby_mask;
	bool sw_reg;
पूर्ण;

काष्ठा pfuze_chip अणु
	पूर्णांक	chip_id;
	पूर्णांक     flags;
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	काष्ठा pfuze_regulator regulator_descs[PFUZE100_MAX_REGULATOR];
	काष्ठा regulator_dev *regulators[PFUZE100_MAX_REGULATOR];
	काष्ठा pfuze_regulator *pfuze_regulators;
पूर्ण;

अटल स्थिर पूर्णांक pfuze100_swbst[] = अणु
	5000000, 5050000, 5100000, 5150000,
पूर्ण;

अटल स्थिर पूर्णांक pfuze100_vsnvs[] = अणु
	1000000, 1100000, 1200000, 1300000, 1500000, 1800000, 3000000,
पूर्ण;

अटल स्थिर पूर्णांक pfuze100_coin[] = अणु
	2500000, 2700000, 2800000, 2900000, 3000000, 3100000, 3200000, 3300000,
पूर्ण;

अटल स्थिर पूर्णांक pfuze3000_sw1a[] = अणु
	700000, 725000, 750000, 775000, 800000, 825000, 850000, 875000,
	900000, 925000, 950000, 975000, 1000000, 1025000, 1050000, 1075000,
	1100000, 1125000, 1150000, 1175000, 1200000, 1225000, 1250000, 1275000,
	1300000, 1325000, 1350000, 1375000, 1400000, 1425000, 1800000, 3300000,
पूर्ण;

अटल स्थिर पूर्णांक pfuze3000_sw2lo[] = अणु
	1500000, 1550000, 1600000, 1650000, 1700000, 1750000, 1800000, 1850000,
पूर्ण;

अटल स्थिर पूर्णांक pfuze3000_sw2hi[] = अणु
	2500000, 2800000, 2850000, 3000000, 3100000, 3150000, 3200000, 3300000,
पूर्ण;

अटल स्थिर काष्ठा of_device_id pfuze_dt_ids[] = अणु
	अणु .compatible = "fsl,pfuze100", .data = (व्योम *)PFUZE100पूर्ण,
	अणु .compatible = "fsl,pfuze200", .data = (व्योम *)PFUZE200पूर्ण,
	अणु .compatible = "fsl,pfuze3000", .data = (व्योम *)PFUZE3000पूर्ण,
	अणु .compatible = "fsl,pfuze3001", .data = (व्योम *)PFUZE3001पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pfuze_dt_ids);

अटल पूर्णांक pfuze100_set_ramp_delay(काष्ठा regulator_dev *rdev, पूर्णांक ramp_delay)
अणु
	काष्ठा pfuze_chip *pfuze100 = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	bool reg_has_ramp_delay;
	अचिन्हित पूर्णांक ramp_bits = 0;
	पूर्णांक ret;

	चयन (pfuze100->chip_id) अणु
	हाल PFUZE3001:
		/* no dynamic voltage scaling क्रम PF3001 */
		reg_has_ramp_delay = false;
		अवरोध;
	हाल PFUZE3000:
		reg_has_ramp_delay = (id < PFUZE3000_SWBST);
		अवरोध;
	हाल PFUZE200:
		reg_has_ramp_delay = (id < PFUZE200_SWBST);
		अवरोध;
	हाल PFUZE100:
	शेष:
		reg_has_ramp_delay = (id < PFUZE100_SWBST);
		अवरोध;
	पूर्ण

	अगर (reg_has_ramp_delay) अणु
		अगर (ramp_delay > 0) अणु
			ramp_delay = 12500 / ramp_delay;
			ramp_bits = (ramp_delay >> 1) - (ramp_delay >> 3);
		पूर्ण

		ret = regmap_update_bits(pfuze100->regmap,
					 rdev->desc->vsel_reg + 4,
					 0xc0, ramp_bits << 6);
		अगर (ret < 0)
			dev_err(pfuze100->dev, "ramp failed, err %d\n", ret);
	पूर्ण अन्यथा अणु
		ret = -EACCES;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regulator_ops pfuze100_lकरो_regulator_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops pfuze100_fixed_regulator_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_linear,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops pfuze100_sw_regulator_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.set_ramp_delay = pfuze100_set_ramp_delay,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops pfuze100_sw_disable_regulator_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.set_ramp_delay = pfuze100_set_ramp_delay,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops pfuze100_swb_regulator_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,

पूर्ण;

अटल स्थिर काष्ठा regulator_ops pfuze3000_sw_regulator_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.set_ramp_delay = pfuze100_set_ramp_delay,

पूर्ण;

#घोषणा PFUZE100_FIXED_REG(_chip, _name, base, voltage)	\
	[_chip ## _ ## _name] = अणु	\
		.desc = अणु	\
			.name = #_name,	\
			.n_voltages = 1,	\
			.ops = &pfuze100_fixed_regulator_ops,	\
			.type = REGULATOR_VOLTAGE,	\
			.id = _chip ## _ ## _name,	\
			.owner = THIS_MODULE,	\
			.min_uV = (voltage),	\
			.enable_reg = (base),	\
			.enable_mask = 0x10,	\
		पूर्ण,	\
	पूर्ण

#घोषणा PFUZE100_SW_REG(_chip, _name, base, min, max, step)	\
	[_chip ## _ ## _name] = अणु	\
		.desc = अणु	\
			.name = #_name,\
			.n_voltages = ((max) - (min)) / (step) + 1,	\
			.ops = &pfuze100_sw_regulator_ops,	\
			.type = REGULATOR_VOLTAGE,	\
			.id = _chip ## _ ## _name,	\
			.owner = THIS_MODULE,	\
			.min_uV = (min),	\
			.uV_step = (step),	\
			.vsel_reg = (base) + PFUZE100_VOL_OFFSET,	\
			.vsel_mask = 0x3f,	\
			.enable_reg = (base) + PFUZE100_MODE_OFFSET,	\
			.enable_mask = 0xf,	\
		पूर्ण,	\
		.stby_reg = (base) + PFUZE100_STANDBY_OFFSET,	\
		.stby_mask = 0x3f,	\
		.sw_reg = true,		\
	पूर्ण

#घोषणा PFUZE100_SWB_REG(_chip, _name, base, mask, voltages)	\
	[_chip ## _ ##  _name] = अणु	\
		.desc = अणु	\
			.name = #_name,	\
			.n_voltages = ARRAY_SIZE(voltages),	\
			.ops = &pfuze100_swb_regulator_ops,	\
			.type = REGULATOR_VOLTAGE,	\
			.id = _chip ## _ ## _name,	\
			.owner = THIS_MODULE,	\
			.volt_table = voltages,	\
			.vsel_reg = (base),	\
			.vsel_mask = (mask),	\
			.enable_reg = (base),	\
			.enable_mask = 0x48,	\
		पूर्ण,	\
	पूर्ण

#घोषणा PFUZE100_VGEN_REG(_chip, _name, base, min, max, step)	\
	[_chip ## _ ## _name] = अणु	\
		.desc = अणु	\
			.name = #_name,	\
			.n_voltages = ((max) - (min)) / (step) + 1,	\
			.ops = &pfuze100_lकरो_regulator_ops,	\
			.type = REGULATOR_VOLTAGE,	\
			.id = _chip ## _ ## _name,	\
			.owner = THIS_MODULE,	\
			.min_uV = (min),	\
			.uV_step = (step),	\
			.vsel_reg = (base),	\
			.vsel_mask = 0xf,	\
			.enable_reg = (base),	\
			.enable_mask = 0x10,	\
		पूर्ण,	\
		.stby_reg = (base),	\
		.stby_mask = 0x20,	\
	पूर्ण

#घोषणा PFUZE100_COIN_REG(_chip, _name, base, mask, voltages)	\
	[_chip ## _ ##  _name] = अणु	\
		.desc = अणु	\
			.name = #_name,	\
			.n_voltages = ARRAY_SIZE(voltages),	\
			.ops = &pfuze100_swb_regulator_ops,	\
			.type = REGULATOR_VOLTAGE,	\
			.id = _chip ## _ ## _name,	\
			.owner = THIS_MODULE,	\
			.volt_table = voltages,	\
			.vsel_reg = (base),	\
			.vsel_mask = (mask),	\
			.enable_reg = (base),	\
			.enable_mask = 0x8,	\
		पूर्ण,	\
	पूर्ण

#घोषणा PFUZE3000_VCC_REG(_chip, _name, base, min, max, step)	अणु	\
	.desc = अणु	\
		.name = #_name,	\
		.n_voltages = ((max) - (min)) / (step) + 1,	\
		.ops = &pfuze100_lकरो_regulator_ops,	\
		.type = REGULATOR_VOLTAGE,	\
		.id = _chip ## _ ## _name,	\
		.owner = THIS_MODULE,	\
		.min_uV = (min),	\
		.uV_step = (step),	\
		.vsel_reg = (base),	\
		.vsel_mask = 0x3,	\
		.enable_reg = (base),	\
		.enable_mask = 0x10,	\
	पूर्ण,	\
	.stby_reg = (base),	\
	.stby_mask = 0x20,	\
पूर्ण

/* No linar हाल क्रम the some चयनes of PFUZE3000 */
#घोषणा PFUZE3000_SW_REG(_chip, _name, base, mask, voltages)	\
	[_chip ## _ ##  _name] = अणु	\
		.desc = अणु	\
			.name = #_name,	\
			.n_voltages = ARRAY_SIZE(voltages),	\
			.ops = &pfuze3000_sw_regulator_ops,	\
			.type = REGULATOR_VOLTAGE,	\
			.id = _chip ## _ ## _name,	\
			.owner = THIS_MODULE,	\
			.volt_table = voltages,	\
			.vsel_reg = (base) + PFUZE100_VOL_OFFSET,	\
			.vsel_mask = (mask),	\
			.enable_reg = (base) + PFUZE100_MODE_OFFSET,	\
			.enable_mask = 0xf,	\
			.enable_val = 0x8,	\
			.enable_समय = 500,	\
		पूर्ण,	\
		.stby_reg = (base) + PFUZE100_STANDBY_OFFSET,	\
		.stby_mask = (mask),	\
		.sw_reg = true,		\
	पूर्ण

#घोषणा PFUZE3000_SW3_REG(_chip, _name, base, min, max, step)	अणु	\
	.desc = अणु	\
		.name = #_name,\
		.n_voltages = ((max) - (min)) / (step) + 1,	\
		.ops = &pfuze100_sw_regulator_ops,	\
		.type = REGULATOR_VOLTAGE,	\
		.id = _chip ## _ ## _name,	\
		.owner = THIS_MODULE,	\
		.min_uV = (min),	\
		.uV_step = (step),	\
		.vsel_reg = (base) + PFUZE100_VOL_OFFSET,	\
		.vsel_mask = 0xf,	\
	पूर्ण,	\
	.stby_reg = (base) + PFUZE100_STANDBY_OFFSET,	\
	.stby_mask = 0xf,	\
पूर्ण

/* PFUZE100 */
अटल काष्ठा pfuze_regulator pfuze100_regulators[] = अणु
	PFUZE100_SW_REG(PFUZE100, SW1AB, PFUZE100_SW1ABVOL, 300000, 1875000, 25000),
	PFUZE100_SW_REG(PFUZE100, SW1C, PFUZE100_SW1CVOL, 300000, 1875000, 25000),
	PFUZE100_SW_REG(PFUZE100, SW2, PFUZE100_SW2VOL, 400000, 1975000, 25000),
	PFUZE100_SW_REG(PFUZE100, SW3A, PFUZE100_SW3AVOL, 400000, 1975000, 25000),
	PFUZE100_SW_REG(PFUZE100, SW3B, PFUZE100_SW3BVOL, 400000, 1975000, 25000),
	PFUZE100_SW_REG(PFUZE100, SW4, PFUZE100_SW4VOL, 400000, 1975000, 25000),
	PFUZE100_SWB_REG(PFUZE100, SWBST, PFUZE100_SWBSTCON1, 0x3 , pfuze100_swbst),
	PFUZE100_SWB_REG(PFUZE100, VSNVS, PFUZE100_VSNVSVOL, 0x7, pfuze100_vsnvs),
	PFUZE100_FIXED_REG(PFUZE100, VREFDDR, PFUZE100_VREFDDRCON, 750000),
	PFUZE100_VGEN_REG(PFUZE100, VGEN1, PFUZE100_VGEN1VOL, 800000, 1550000, 50000),
	PFUZE100_VGEN_REG(PFUZE100, VGEN2, PFUZE100_VGEN2VOL, 800000, 1550000, 50000),
	PFUZE100_VGEN_REG(PFUZE100, VGEN3, PFUZE100_VGEN3VOL, 1800000, 3300000, 100000),
	PFUZE100_VGEN_REG(PFUZE100, VGEN4, PFUZE100_VGEN4VOL, 1800000, 3300000, 100000),
	PFUZE100_VGEN_REG(PFUZE100, VGEN5, PFUZE100_VGEN5VOL, 1800000, 3300000, 100000),
	PFUZE100_VGEN_REG(PFUZE100, VGEN6, PFUZE100_VGEN6VOL, 1800000, 3300000, 100000),
	PFUZE100_COIN_REG(PFUZE100, COIN, PFUZE100_COINVOL, 0x7, pfuze100_coin),
पूर्ण;

अटल काष्ठा pfuze_regulator pfuze200_regulators[] = अणु
	PFUZE100_SW_REG(PFUZE200, SW1AB, PFUZE100_SW1ABVOL, 300000, 1875000, 25000),
	PFUZE100_SW_REG(PFUZE200, SW2, PFUZE100_SW2VOL, 400000, 1975000, 25000),
	PFUZE100_SW_REG(PFUZE200, SW3A, PFUZE100_SW3AVOL, 400000, 1975000, 25000),
	PFUZE100_SW_REG(PFUZE200, SW3B, PFUZE100_SW3BVOL, 400000, 1975000, 25000),
	PFUZE100_SWB_REG(PFUZE200, SWBST, PFUZE100_SWBSTCON1, 0x3 , pfuze100_swbst),
	PFUZE100_SWB_REG(PFUZE200, VSNVS, PFUZE100_VSNVSVOL, 0x7, pfuze100_vsnvs),
	PFUZE100_FIXED_REG(PFUZE200, VREFDDR, PFUZE100_VREFDDRCON, 750000),
	PFUZE100_VGEN_REG(PFUZE200, VGEN1, PFUZE100_VGEN1VOL, 800000, 1550000, 50000),
	PFUZE100_VGEN_REG(PFUZE200, VGEN2, PFUZE100_VGEN2VOL, 800000, 1550000, 50000),
	PFUZE100_VGEN_REG(PFUZE200, VGEN3, PFUZE100_VGEN3VOL, 1800000, 3300000, 100000),
	PFUZE100_VGEN_REG(PFUZE200, VGEN4, PFUZE100_VGEN4VOL, 1800000, 3300000, 100000),
	PFUZE100_VGEN_REG(PFUZE200, VGEN5, PFUZE100_VGEN5VOL, 1800000, 3300000, 100000),
	PFUZE100_VGEN_REG(PFUZE200, VGEN6, PFUZE100_VGEN6VOL, 1800000, 3300000, 100000),
	PFUZE100_COIN_REG(PFUZE200, COIN, PFUZE100_COINVOL, 0x7, pfuze100_coin),
पूर्ण;

अटल काष्ठा pfuze_regulator pfuze3000_regulators[] = अणु
	PFUZE3000_SW_REG(PFUZE3000, SW1A, PFUZE100_SW1ABVOL, 0x1f, pfuze3000_sw1a),
	PFUZE100_SW_REG(PFUZE3000, SW1B, PFUZE100_SW1CVOL, 700000, 1475000, 25000),
	PFUZE3000_SW_REG(PFUZE3000, SW2, PFUZE100_SW2VOL, 0x7, pfuze3000_sw2lo),
	PFUZE3000_SW3_REG(PFUZE3000, SW3, PFUZE100_SW3AVOL, 900000, 1650000, 50000),
	PFUZE100_SWB_REG(PFUZE3000, SWBST, PFUZE100_SWBSTCON1, 0x3, pfuze100_swbst),
	PFUZE100_SWB_REG(PFUZE3000, VSNVS, PFUZE100_VSNVSVOL, 0x7, pfuze100_vsnvs),
	PFUZE100_FIXED_REG(PFUZE3000, VREFDDR, PFUZE100_VREFDDRCON, 750000),
	PFUZE100_VGEN_REG(PFUZE3000, VLDO1, PFUZE100_VGEN1VOL, 1800000, 3300000, 100000),
	PFUZE100_VGEN_REG(PFUZE3000, VLDO2, PFUZE100_VGEN2VOL, 800000, 1550000, 50000),
	PFUZE3000_VCC_REG(PFUZE3000, VCCSD, PFUZE100_VGEN3VOL, 2850000, 3300000, 150000),
	PFUZE3000_VCC_REG(PFUZE3000, V33, PFUZE100_VGEN4VOL, 2850000, 3300000, 150000),
	PFUZE100_VGEN_REG(PFUZE3000, VLDO3, PFUZE100_VGEN5VOL, 1800000, 3300000, 100000),
	PFUZE100_VGEN_REG(PFUZE3000, VLDO4, PFUZE100_VGEN6VOL, 1800000, 3300000, 100000),
पूर्ण;

अटल काष्ठा pfuze_regulator pfuze3001_regulators[] = अणु
	PFUZE3000_SW_REG(PFUZE3001, SW1, PFUZE100_SW1ABVOL, 0x1f, pfuze3000_sw1a),
	PFUZE3000_SW_REG(PFUZE3001, SW2, PFUZE100_SW2VOL, 0x7, pfuze3000_sw2lo),
	PFUZE3000_SW3_REG(PFUZE3001, SW3, PFUZE100_SW3AVOL, 900000, 1650000, 50000),
	PFUZE100_SWB_REG(PFUZE3001, VSNVS, PFUZE100_VSNVSVOL, 0x7, pfuze100_vsnvs),
	PFUZE100_VGEN_REG(PFUZE3001, VLDO1, PFUZE100_VGEN1VOL, 1800000, 3300000, 100000),
	PFUZE100_VGEN_REG(PFUZE3001, VLDO2, PFUZE100_VGEN2VOL, 800000, 1550000, 50000),
	PFUZE3000_VCC_REG(PFUZE3001, VCCSD, PFUZE100_VGEN3VOL, 2850000, 3300000, 150000),
	PFUZE3000_VCC_REG(PFUZE3001, V33, PFUZE100_VGEN4VOL, 2850000, 3300000, 150000),
	PFUZE100_VGEN_REG(PFUZE3001, VLDO3, PFUZE100_VGEN5VOL, 1800000, 3300000, 100000),
	PFUZE100_VGEN_REG(PFUZE3001, VLDO4, PFUZE100_VGEN6VOL, 1800000, 3300000, 100000),
पूर्ण;

/* PFUZE100 */
अटल काष्ठा of_regulator_match pfuze100_matches[] = अणु
	अणु .name = "sw1ab",	पूर्ण,
	अणु .name = "sw1c",	पूर्ण,
	अणु .name = "sw2",	पूर्ण,
	अणु .name = "sw3a",	पूर्ण,
	अणु .name = "sw3b",	पूर्ण,
	अणु .name = "sw4",	पूर्ण,
	अणु .name = "swbst",	पूर्ण,
	अणु .name = "vsnvs",	पूर्ण,
	अणु .name = "vrefddr",	पूर्ण,
	अणु .name = "vgen1",	पूर्ण,
	अणु .name = "vgen2",	पूर्ण,
	अणु .name = "vgen3",	पूर्ण,
	अणु .name = "vgen4",	पूर्ण,
	अणु .name = "vgen5",	पूर्ण,
	अणु .name = "vgen6",	पूर्ण,
	अणु .name = "coin",	पूर्ण,
पूर्ण;

/* PFUZE200 */
अटल काष्ठा of_regulator_match pfuze200_matches[] = अणु

	अणु .name = "sw1ab",	पूर्ण,
	अणु .name = "sw2",	पूर्ण,
	अणु .name = "sw3a",	पूर्ण,
	अणु .name = "sw3b",	पूर्ण,
	अणु .name = "swbst",	पूर्ण,
	अणु .name = "vsnvs",	पूर्ण,
	अणु .name = "vrefddr",	पूर्ण,
	अणु .name = "vgen1",	पूर्ण,
	अणु .name = "vgen2",	पूर्ण,
	अणु .name = "vgen3",	पूर्ण,
	अणु .name = "vgen4",	पूर्ण,
	अणु .name = "vgen5",	पूर्ण,
	अणु .name = "vgen6",	पूर्ण,
	अणु .name = "coin",	पूर्ण,
पूर्ण;

/* PFUZE3000 */
अटल काष्ठा of_regulator_match pfuze3000_matches[] = अणु

	अणु .name = "sw1a",	पूर्ण,
	अणु .name = "sw1b",	पूर्ण,
	अणु .name = "sw2",	पूर्ण,
	अणु .name = "sw3",	पूर्ण,
	अणु .name = "swbst",	पूर्ण,
	अणु .name = "vsnvs",	पूर्ण,
	अणु .name = "vrefddr",	पूर्ण,
	अणु .name = "vldo1",	पूर्ण,
	अणु .name = "vldo2",	पूर्ण,
	अणु .name = "vccsd",	पूर्ण,
	अणु .name = "v33",	पूर्ण,
	अणु .name = "vldo3",	पूर्ण,
	अणु .name = "vldo4",	पूर्ण,
पूर्ण;

/* PFUZE3001 */
अटल काष्ठा of_regulator_match pfuze3001_matches[] = अणु

	अणु .name = "sw1",	पूर्ण,
	अणु .name = "sw2",	पूर्ण,
	अणु .name = "sw3",	पूर्ण,
	अणु .name = "vsnvs",	पूर्ण,
	अणु .name = "vldo1",	पूर्ण,
	अणु .name = "vldo2",	पूर्ण,
	अणु .name = "vccsd",	पूर्ण,
	अणु .name = "v33",	पूर्ण,
	अणु .name = "vldo3",	पूर्ण,
	अणु .name = "vldo4",	पूर्ण,
पूर्ण;

अटल काष्ठा of_regulator_match *pfuze_matches;

अटल पूर्णांक pfuze_parse_regulators_dt(काष्ठा pfuze_chip *chip)
अणु
	काष्ठा device *dev = chip->dev;
	काष्ठा device_node *np, *parent;
	पूर्णांक ret;

	np = of_node_get(dev->of_node);
	अगर (!np)
		वापस -EINVAL;

	अगर (of_property_पढ़ो_bool(np, "fsl,pfuze-support-disable-sw"))
		chip->flags |= PFUZE_FLAG_DISABLE_SW;

	parent = of_get_child_by_name(np, "regulators");
	अगर (!parent) अणु
		dev_err(dev, "regulators node not found\n");
		वापस -EINVAL;
	पूर्ण

	चयन (chip->chip_id) अणु
	हाल PFUZE3001:
		pfuze_matches = pfuze3001_matches;
		ret = of_regulator_match(dev, parent, pfuze3001_matches,
					 ARRAY_SIZE(pfuze3001_matches));
		अवरोध;
	हाल PFUZE3000:
		pfuze_matches = pfuze3000_matches;
		ret = of_regulator_match(dev, parent, pfuze3000_matches,
					 ARRAY_SIZE(pfuze3000_matches));
		अवरोध;
	हाल PFUZE200:
		pfuze_matches = pfuze200_matches;
		ret = of_regulator_match(dev, parent, pfuze200_matches,
					 ARRAY_SIZE(pfuze200_matches));
		अवरोध;

	हाल PFUZE100:
	शेष:
		pfuze_matches = pfuze100_matches;
		ret = of_regulator_match(dev, parent, pfuze100_matches,
					 ARRAY_SIZE(pfuze100_matches));
		अवरोध;
	पूर्ण

	of_node_put(parent);
	अगर (ret < 0) अणु
		dev_err(dev, "Error parsing regulator init data: %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा regulator_init_data *match_init_data(पूर्णांक index)
अणु
	वापस pfuze_matches[index].init_data;
पूर्ण

अटल अंतरभूत काष्ठा device_node *match_of_node(पूर्णांक index)
अणु
	वापस pfuze_matches[index].of_node;
पूर्ण

अटल काष्ठा pfuze_chip *syspm_pfuze_chip;

अटल व्योम pfuze_घातer_off_prepare(व्योम)
अणु
	dev_info(syspm_pfuze_chip->dev, "Configure standby mode for power off");

	/* Switch from शेष mode: APS/APS to APS/Off */
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_SW1ABMODE,
			   PFUZE100_SWxMODE_MASK, PFUZE100_SWxMODE_APS_OFF);
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_SW1CMODE,
			   PFUZE100_SWxMODE_MASK, PFUZE100_SWxMODE_APS_OFF);
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_SW2MODE,
			   PFUZE100_SWxMODE_MASK, PFUZE100_SWxMODE_APS_OFF);
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_SW3AMODE,
			   PFUZE100_SWxMODE_MASK, PFUZE100_SWxMODE_APS_OFF);
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_SW3BMODE,
			   PFUZE100_SWxMODE_MASK, PFUZE100_SWxMODE_APS_OFF);
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_SW4MODE,
			   PFUZE100_SWxMODE_MASK, PFUZE100_SWxMODE_APS_OFF);

	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_VGEN1VOL,
			   PFUZE100_VGENxLPWR | PFUZE100_VGENxSTBY,
			   PFUZE100_VGENxSTBY);
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_VGEN2VOL,
			   PFUZE100_VGENxLPWR | PFUZE100_VGENxSTBY,
			   PFUZE100_VGENxSTBY);
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_VGEN3VOL,
			   PFUZE100_VGENxLPWR | PFUZE100_VGENxSTBY,
			   PFUZE100_VGENxSTBY);
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_VGEN4VOL,
			   PFUZE100_VGENxLPWR | PFUZE100_VGENxSTBY,
			   PFUZE100_VGENxSTBY);
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_VGEN5VOL,
			   PFUZE100_VGENxLPWR | PFUZE100_VGENxSTBY,
			   PFUZE100_VGENxSTBY);
	regmap_update_bits(syspm_pfuze_chip->regmap, PFUZE100_VGEN6VOL,
			   PFUZE100_VGENxLPWR | PFUZE100_VGENxSTBY,
			   PFUZE100_VGENxSTBY);
पूर्ण

अटल पूर्णांक pfuze_घातer_off_prepare_init(काष्ठा pfuze_chip *pfuze_chip)
अणु
	अगर (pfuze_chip->chip_id != PFUZE100) अणु
		dev_warn(pfuze_chip->dev, "Requested pm_power_off_prepare handler for not supported chip\n");
		वापस -ENODEV;
	पूर्ण

	अगर (pm_घातer_off_prepare) अणु
		dev_warn(pfuze_chip->dev, "pm_power_off_prepare is already registered.\n");
		वापस -EBUSY;
	पूर्ण

	अगर (syspm_pfuze_chip) अणु
		dev_warn(pfuze_chip->dev, "syspm_pfuze_chip is already set.\n");
		वापस -EBUSY;
	पूर्ण

	syspm_pfuze_chip = pfuze_chip;
	pm_घातer_off_prepare = pfuze_घातer_off_prepare;

	वापस 0;
पूर्ण

अटल पूर्णांक pfuze_identअगरy(काष्ठा pfuze_chip *pfuze_chip)
अणु
	अचिन्हित पूर्णांक value;
	पूर्णांक ret;

	ret = regmap_पढ़ो(pfuze_chip->regmap, PFUZE100_DEVICEID, &value);
	अगर (ret)
		वापस ret;

	अगर (((value & 0x0f) == 0x8) && (pfuze_chip->chip_id == PFUZE100)) अणु
		/*
		 * Freescale misprogrammed 1-3% of parts prior to week 8 of 2013
		 * as ID=8 in PFUZE100
		 */
		dev_info(pfuze_chip->dev, "Assuming misprogrammed ID=0x8");
	पूर्ण अन्यथा अगर ((value & 0x0f) != pfuze_chip->chip_id &&
		   (value & 0xf0) >> 4 != pfuze_chip->chip_id &&
		   (value != pfuze_chip->chip_id)) अणु
		/* device id NOT match with your setting */
		dev_warn(pfuze_chip->dev, "Illegal ID: %x\n", value);
		वापस -ENODEV;
	पूर्ण

	ret = regmap_पढ़ो(pfuze_chip->regmap, PFUZE100_REVID, &value);
	अगर (ret)
		वापस ret;
	dev_info(pfuze_chip->dev,
		 "Full layer: %x, Metal layer: %x\n",
		 (value & 0xf0) >> 4, value & 0x0f);

	ret = regmap_पढ़ो(pfuze_chip->regmap, PFUZE100_FABID, &value);
	अगर (ret)
		वापस ret;
	dev_info(pfuze_chip->dev, "FAB: %x, FIN: %x\n",
		 (value & 0xc) >> 2, value & 0x3);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config pfuze_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = PFUZE_NUMREGS - 1,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक pfuze100_regulator_probe(काष्ठा i2c_client *client,
				    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा pfuze_chip *pfuze_chip;
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक i, ret;
	स्थिर काष्ठा of_device_id *match;
	u32 regulator_num;
	u32 sw_check_start, sw_check_end, sw_hi = 0x40;

	pfuze_chip = devm_kzalloc(&client->dev, माप(*pfuze_chip),
			GFP_KERNEL);
	अगर (!pfuze_chip)
		वापस -ENOMEM;

	अगर (client->dev.of_node) अणु
		match = of_match_device(of_match_ptr(pfuze_dt_ids),
				&client->dev);
		अगर (!match) अणु
			dev_err(&client->dev, "Error: No device match found\n");
			वापस -ENODEV;
		पूर्ण
		pfuze_chip->chip_id = (पूर्णांक)(दीर्घ)match->data;
	पूर्ण अन्यथा अगर (id) अणु
		pfuze_chip->chip_id = id->driver_data;
	पूर्ण अन्यथा अणु
		dev_err(&client->dev, "No dts match or id table match found\n");
		वापस -ENODEV;
	पूर्ण

	i2c_set_clientdata(client, pfuze_chip);
	pfuze_chip->dev = &client->dev;

	pfuze_chip->regmap = devm_regmap_init_i2c(client, &pfuze_regmap_config);
	अगर (IS_ERR(pfuze_chip->regmap)) अणु
		ret = PTR_ERR(pfuze_chip->regmap);
		dev_err(&client->dev,
			"regmap allocation failed with err %d\n", ret);
		वापस ret;
	पूर्ण

	ret = pfuze_identअगरy(pfuze_chip);
	अगर (ret) अणु
		dev_err(&client->dev, "unrecognized pfuze chip ID!\n");
		वापस ret;
	पूर्ण

	/* use the right regulators after identअगरy the right device */
	चयन (pfuze_chip->chip_id) अणु
	हाल PFUZE3001:
		pfuze_chip->pfuze_regulators = pfuze3001_regulators;
		regulator_num = ARRAY_SIZE(pfuze3001_regulators);
		sw_check_start = PFUZE3001_SW2;
		sw_check_end = PFUZE3001_SW2;
		sw_hi = 1 << 3;
		अवरोध;
	हाल PFUZE3000:
		pfuze_chip->pfuze_regulators = pfuze3000_regulators;
		regulator_num = ARRAY_SIZE(pfuze3000_regulators);
		sw_check_start = PFUZE3000_SW2;
		sw_check_end = PFUZE3000_SW2;
		sw_hi = 1 << 3;
		अवरोध;
	हाल PFUZE200:
		pfuze_chip->pfuze_regulators = pfuze200_regulators;
		regulator_num = ARRAY_SIZE(pfuze200_regulators);
		sw_check_start = PFUZE200_SW2;
		sw_check_end = PFUZE200_SW3B;
		अवरोध;
	हाल PFUZE100:
	शेष:
		pfuze_chip->pfuze_regulators = pfuze100_regulators;
		regulator_num = ARRAY_SIZE(pfuze100_regulators);
		sw_check_start = PFUZE100_SW2;
		sw_check_end = PFUZE100_SW4;
		अवरोध;
	पूर्ण
	dev_info(&client->dev, "pfuze%s found.\n",
		(pfuze_chip->chip_id == PFUZE100) ? "100" :
		(((pfuze_chip->chip_id == PFUZE200) ? "200" :
		((pfuze_chip->chip_id == PFUZE3000) ? "3000" : "3001"))));

	स_नकल(pfuze_chip->regulator_descs, pfuze_chip->pfuze_regulators,
		माप(pfuze_chip->regulator_descs));

	ret = pfuze_parse_regulators_dt(pfuze_chip);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < regulator_num; i++) अणु
		काष्ठा regulator_init_data *init_data;
		काष्ठा regulator_desc *desc;
		पूर्णांक val;

		desc = &pfuze_chip->regulator_descs[i].desc;

		init_data = match_init_data(i);

		/* SW2~SW4 high bit check and modअगरy the voltage value table */
		अगर (i >= sw_check_start && i <= sw_check_end) अणु
			ret = regmap_पढ़ो(pfuze_chip->regmap,
						desc->vsel_reg, &val);
			अगर (ret) अणु
				dev_err(&client->dev, "Fails to read from the register.\n");
				वापस ret;
			पूर्ण

			अगर (val & sw_hi) अणु
				अगर (pfuze_chip->chip_id == PFUZE3000 ||
					pfuze_chip->chip_id == PFUZE3001) अणु
					desc->volt_table = pfuze3000_sw2hi;
					desc->n_voltages = ARRAY_SIZE(pfuze3000_sw2hi);
				पूर्ण अन्यथा अणु
					desc->min_uV = 800000;
					desc->uV_step = 50000;
					desc->n_voltages = 51;
				पूर्ण
			पूर्ण
		पूर्ण

		/*
		 * Allow SW regulators to turn off. Checking it trough a flag is
		 * a workaround to keep the backward compatibility with existing
		 * old dtb's which may relay on the fact that we didn't disable
		 * the चयनed regulator till yet.
		 */
		अगर (pfuze_chip->flags & PFUZE_FLAG_DISABLE_SW) अणु
			अगर (pfuze_chip->chip_id == PFUZE100 ||
				pfuze_chip->chip_id == PFUZE200) अणु
				अगर (pfuze_chip->regulator_descs[i].sw_reg) अणु
					desc->ops = &pfuze100_sw_disable_regulator_ops;
					desc->enable_val = 0x8;
					desc->disable_val = 0x0;
					desc->enable_समय = 500;
				पूर्ण
			पूर्ण
		पूर्ण

		config.dev = &client->dev;
		config.init_data = init_data;
		config.driver_data = pfuze_chip;
		config.of_node = match_of_node(i);

		pfuze_chip->regulators[i] =
			devm_regulator_रेजिस्टर(&client->dev, desc, &config);
		अगर (IS_ERR(pfuze_chip->regulators[i])) अणु
			dev_err(&client->dev, "register regulator%s failed\n",
				pfuze_chip->pfuze_regulators[i].desc.name);
			वापस PTR_ERR(pfuze_chip->regulators[i]);
		पूर्ण
	पूर्ण

	अगर (of_property_पढ़ो_bool(client->dev.of_node,
				  "fsl,pmic-stby-poweroff"))
		वापस pfuze_घातer_off_prepare_init(pfuze_chip);

	वापस 0;
पूर्ण

अटल पूर्णांक pfuze100_regulator_हटाओ(काष्ठा i2c_client *client)
अणु
	अगर (syspm_pfuze_chip) अणु
		syspm_pfuze_chip = शून्य;
		pm_घातer_off_prepare = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver pfuze_driver = अणु
	.driver = अणु
		.name = "pfuze100-regulator",
		.of_match_table = pfuze_dt_ids,
	पूर्ण,
	.probe = pfuze100_regulator_probe,
	.हटाओ = pfuze100_regulator_हटाओ,
पूर्ण;
module_i2c_driver(pfuze_driver);

MODULE_AUTHOR("Robin Gong <b38343@freescale.com>");
MODULE_DESCRIPTION("Regulator Driver for Freescale PFUZE100/200/3000/3001 PMIC");
MODULE_LICENSE("GPL v2");
