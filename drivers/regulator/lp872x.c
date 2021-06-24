<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2012 Texas Instruments
 *
 * Author: Milo(Woogyom) Kim <milo.kim@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/regulator/lp872x.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regulator/of_regulator.h>

/* Registers : LP8720/8725 shared */
#घोषणा LP872X_GENERAL_CFG		0x00
#घोषणा LP872X_LDO1_VOUT		0x01
#घोषणा LP872X_LDO2_VOUT		0x02
#घोषणा LP872X_LDO3_VOUT		0x03
#घोषणा LP872X_LDO4_VOUT		0x04
#घोषणा LP872X_LDO5_VOUT		0x05

/* Registers : LP8720 */
#घोषणा LP8720_BUCK_VOUT1		0x06
#घोषणा LP8720_BUCK_VOUT2		0x07
#घोषणा LP8720_ENABLE			0x08

/* Registers : LP8725 */
#घोषणा LP8725_LILO1_VOUT		0x06
#घोषणा LP8725_LILO2_VOUT		0x07
#घोषणा LP8725_BUCK1_VOUT1		0x08
#घोषणा LP8725_BUCK1_VOUT2		0x09
#घोषणा LP8725_BUCK2_VOUT1		0x0A
#घोषणा LP8725_BUCK2_VOUT2		0x0B
#घोषणा LP8725_BUCK_CTRL		0x0C
#घोषणा LP8725_LDO_CTRL			0x0D

/* Mask/shअगरt : LP8720/LP8725 shared */
#घोषणा LP872X_VOUT_M			0x1F
#घोषणा LP872X_START_DELAY_M		0xE0
#घोषणा LP872X_START_DELAY_S		5
#घोषणा LP872X_EN_LDO1_M		BIT(0)
#घोषणा LP872X_EN_LDO2_M		BIT(1)
#घोषणा LP872X_EN_LDO3_M		BIT(2)
#घोषणा LP872X_EN_LDO4_M		BIT(3)
#घोषणा LP872X_EN_LDO5_M		BIT(4)

/* Mask/shअगरt : LP8720 */
#घोषणा LP8720_TIMESTEP_S		0		/* Addr 00h */
#घोषणा LP8720_TIMESTEP_M		BIT(0)
#घोषणा LP8720_EXT_DVS_M		BIT(2)
#घोषणा LP8720_BUCK_FPWM_S		5		/* Addr 07h */
#घोषणा LP8720_BUCK_FPWM_M		BIT(5)
#घोषणा LP8720_EN_BUCK_M		BIT(5)		/* Addr 08h */
#घोषणा LP8720_DVS_SEL_M		BIT(7)

/* Mask/shअगरt : LP8725 */
#घोषणा LP8725_TIMESTEP_M		0xC0		/* Addr 00h */
#घोषणा LP8725_TIMESTEP_S		6
#घोषणा LP8725_BUCK1_EN_M		BIT(0)
#घोषणा LP8725_DVS1_M			BIT(2)
#घोषणा LP8725_DVS2_M			BIT(3)
#घोषणा LP8725_BUCK2_EN_M		BIT(4)
#घोषणा LP8725_BUCK_CL_M		0xC0		/* Addr 09h, 0Bh */
#घोषणा LP8725_BUCK_CL_S		6
#घोषणा LP8725_BUCK1_FPWM_S		1		/* Addr 0Ch */
#घोषणा LP8725_BUCK1_FPWM_M		BIT(1)
#घोषणा LP8725_BUCK2_FPWM_S		5
#घोषणा LP8725_BUCK2_FPWM_M		BIT(5)
#घोषणा LP8725_EN_LILO1_M		BIT(5)		/* Addr 0Dh */
#घोषणा LP8725_EN_LILO2_M		BIT(6)

/* PWM mode */
#घोषणा LP872X_FORCE_PWM		1
#घोषणा LP872X_AUTO_PWM			0

#घोषणा LP8720_NUM_REGULATORS		6
#घोषणा LP8725_NUM_REGULATORS		9
#घोषणा EXTERN_DVS_USED			0
#घोषणा MAX_DELAY			6

/* Default DVS Mode */
#घोषणा LP8720_DEFAULT_DVS		0
#घोषणा LP8725_DEFAULT_DVS		BIT(2)

/* dump रेजिस्टरs in regmap-debugfs */
#घोषणा MAX_REGISTERS			0x0F

क्रमागत lp872x_id अणु
	LP8720,
	LP8725,
पूर्ण;

काष्ठा lp872x अणु
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	क्रमागत lp872x_id chipid;
	काष्ठा lp872x_platक्रमm_data *pdata;
	पूर्णांक num_regulators;
	क्रमागत lp872x_dvs_state dvs_pin;
पूर्ण;

/* LP8720/LP8725 shared voltage table क्रम LDOs */
अटल स्थिर अचिन्हित पूर्णांक lp872x_lकरो_vtbl[] = अणु
	1200000, 1250000, 1300000, 1350000, 1400000, 1450000, 1500000, 1550000,
	1600000, 1650000, 1700000, 1750000, 1800000, 1850000, 1900000, 2000000,
	2100000, 2200000, 2300000, 2400000, 2500000, 2600000, 2650000, 2700000,
	2750000, 2800000, 2850000, 2900000, 2950000, 3000000, 3100000, 3300000,
पूर्ण;

/* LP8720 LDO4 voltage table */
अटल स्थिर अचिन्हित पूर्णांक lp8720_lकरो4_vtbl[] = अणु
	 800000,  850000,  900000, 1000000, 1100000, 1200000, 1250000, 1300000,
	1350000, 1400000, 1450000, 1500000, 1550000, 1600000, 1650000, 1700000,
	1750000, 1800000, 1850000, 1900000, 2000000, 2100000, 2200000, 2300000,
	2400000, 2500000, 2600000, 2650000, 2700000, 2750000, 2800000, 2850000,
पूर्ण;

/* LP8725 LILO(Low Input Low Output) voltage table */
अटल स्थिर अचिन्हित पूर्णांक lp8725_lilo_vtbl[] = अणु
	 800000,  850000,  900000,  950000, 1000000, 1050000, 1100000, 1150000,
	1200000, 1250000, 1300000, 1350000, 1400000, 1500000, 1600000, 1700000,
	1800000, 1900000, 2000000, 2100000, 2200000, 2300000, 2400000, 2500000,
	2600000, 2700000, 2800000, 2850000, 2900000, 3000000, 3100000, 3300000,
पूर्ण;

/* LP8720 BUCK voltage table */
#घोषणा EXT_R		0	/* बाह्यal resistor भागider */
अटल स्थिर अचिन्हित पूर्णांक lp8720_buck_vtbl[] = अणु
	  EXT_R,  800000,  850000,  900000,  950000, 1000000, 1050000, 1100000,
	1150000, 1200000, 1250000, 1300000, 1350000, 1400000, 1450000, 1500000,
	1550000, 1600000, 1650000, 1700000, 1750000, 1800000, 1850000, 1900000,
	1950000, 2000000, 2050000, 2100000, 2150000, 2200000, 2250000, 2300000,
पूर्ण;

/* LP8725 BUCK voltage table */
अटल स्थिर अचिन्हित पूर्णांक lp8725_buck_vtbl[] = अणु
	 800000,  850000,  900000,  950000, 1000000, 1050000, 1100000, 1150000,
	1200000, 1250000, 1300000, 1350000, 1400000, 1500000, 1600000, 1700000,
	1750000, 1800000, 1850000, 1900000, 2000000, 2100000, 2200000, 2300000,
	2400000, 2500000, 2600000, 2700000, 2800000, 2850000, 2900000, 3000000,
पूर्ण;

/* LP8725 BUCK current limit */
अटल स्थिर अचिन्हित पूर्णांक lp8725_buck_uA[] = अणु
	460000, 780000, 1050000, 1370000,
पूर्ण;

अटल पूर्णांक lp872x_पढ़ो_byte(काष्ठा lp872x *lp, u8 addr, u8 *data)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(lp->regmap, addr, &val);
	अगर (ret < 0) अणु
		dev_err(lp->dev, "failed to read 0x%.2x\n", addr);
		वापस ret;
	पूर्ण

	*data = (u8)val;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक lp872x_ग_लिखो_byte(काष्ठा lp872x *lp, u8 addr, u8 data)
अणु
	वापस regmap_ग_लिखो(lp->regmap, addr, data);
पूर्ण

अटल अंतरभूत पूर्णांक lp872x_update_bits(काष्ठा lp872x *lp, u8 addr,
				अचिन्हित पूर्णांक mask, u8 data)
अणु
	वापस regmap_update_bits(lp->regmap, addr, mask, data);
पूर्ण

अटल पूर्णांक lp872x_get_बारtep_usec(काष्ठा lp872x *lp)
अणु
	क्रमागत lp872x_id chip = lp->chipid;
	u8 val, mask, shअगरt;
	पूर्णांक *समय_usec, size, ret;
	पूर्णांक lp8720_समय_usec[] = अणु 25, 50 पूर्ण;
	पूर्णांक lp8725_समय_usec[] = अणु 32, 64, 128, 256 पूर्ण;

	चयन (chip) अणु
	हाल LP8720:
		mask = LP8720_TIMESTEP_M;
		shअगरt = LP8720_TIMESTEP_S;
		समय_usec = &lp8720_समय_usec[0];
		size = ARRAY_SIZE(lp8720_समय_usec);
		अवरोध;
	हाल LP8725:
		mask = LP8725_TIMESTEP_M;
		shअगरt = LP8725_TIMESTEP_S;
		समय_usec = &lp8725_समय_usec[0];
		size = ARRAY_SIZE(lp8725_समय_usec);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = lp872x_पढ़ो_byte(lp, LP872X_GENERAL_CFG, &val);
	अगर (ret)
		वापस ret;

	val = (val & mask) >> shअगरt;
	अगर (val >= size)
		वापस -EINVAL;

	वापस *(समय_usec + val);
पूर्ण

अटल पूर्णांक lp872x_regulator_enable_समय(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा lp872x *lp = rdev_get_drvdata(rdev);
	क्रमागत lp872x_regulator_id rid = rdev_get_id(rdev);
	पूर्णांक समय_step_us = lp872x_get_बारtep_usec(lp);
	पूर्णांक ret;
	u8 addr, val;

	अगर (समय_step_us < 0)
		वापस समय_step_us;

	चयन (rid) अणु
	हाल LP8720_ID_LDO1 ... LP8720_ID_BUCK:
		addr = LP872X_LDO1_VOUT + rid;
		अवरोध;
	हाल LP8725_ID_LDO1 ... LP8725_ID_BUCK1:
		addr = LP872X_LDO1_VOUT + rid - LP8725_ID_BASE;
		अवरोध;
	हाल LP8725_ID_BUCK2:
		addr = LP8725_BUCK2_VOUT1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = lp872x_पढ़ो_byte(lp, addr, &val);
	अगर (ret)
		वापस ret;

	val = (val & LP872X_START_DELAY_M) >> LP872X_START_DELAY_S;

	वापस val > MAX_DELAY ? 0 : val * समय_step_us;
पूर्ण

अटल व्योम lp872x_set_dvs(काष्ठा lp872x *lp, क्रमागत lp872x_dvs_sel dvs_sel,
			पूर्णांक gpio)
अणु
	क्रमागत lp872x_dvs_state state;

	state = dvs_sel == SEL_V1 ? DVS_HIGH : DVS_LOW;
	gpio_set_value(gpio, state);
	lp->dvs_pin = state;
पूर्ण

अटल u8 lp872x_select_buck_vout_addr(काष्ठा lp872x *lp,
				क्रमागत lp872x_regulator_id buck)
अणु
	u8 val, addr;

	अगर (lp872x_पढ़ो_byte(lp, LP872X_GENERAL_CFG, &val))
		वापस 0;

	चयन (buck) अणु
	हाल LP8720_ID_BUCK:
		अगर (val & LP8720_EXT_DVS_M) अणु
			addr = (lp->dvs_pin == DVS_HIGH) ?
				LP8720_BUCK_VOUT1 : LP8720_BUCK_VOUT2;
		पूर्ण अन्यथा अणु
			अगर (lp872x_पढ़ो_byte(lp, LP8720_ENABLE, &val))
				वापस 0;

			addr = val & LP8720_DVS_SEL_M ?
				LP8720_BUCK_VOUT1 : LP8720_BUCK_VOUT2;
		पूर्ण
		अवरोध;
	हाल LP8725_ID_BUCK1:
		अगर (val & LP8725_DVS1_M)
			addr = LP8725_BUCK1_VOUT1;
		अन्यथा
			addr = (lp->dvs_pin == DVS_HIGH) ?
				LP8725_BUCK1_VOUT1 : LP8725_BUCK1_VOUT2;
		अवरोध;
	हाल LP8725_ID_BUCK2:
		addr =  val & LP8725_DVS2_M ?
			LP8725_BUCK2_VOUT1 : LP8725_BUCK2_VOUT2;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस addr;
पूर्ण

अटल bool lp872x_is_valid_buck_addr(u8 addr)
अणु
	चयन (addr) अणु
	हाल LP8720_BUCK_VOUT1:
	हाल LP8720_BUCK_VOUT2:
	हाल LP8725_BUCK1_VOUT1:
	हाल LP8725_BUCK1_VOUT2:
	हाल LP8725_BUCK2_VOUT1:
	हाल LP8725_BUCK2_VOUT2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक lp872x_buck_set_voltage_sel(काष्ठा regulator_dev *rdev,
					अचिन्हित selector)
अणु
	काष्ठा lp872x *lp = rdev_get_drvdata(rdev);
	क्रमागत lp872x_regulator_id buck = rdev_get_id(rdev);
	u8 addr, mask = LP872X_VOUT_M;
	काष्ठा lp872x_dvs *dvs = lp->pdata ? lp->pdata->dvs : शून्य;

	अगर (dvs && gpio_is_valid(dvs->gpio))
		lp872x_set_dvs(lp, dvs->vsel, dvs->gpio);

	addr = lp872x_select_buck_vout_addr(lp, buck);
	अगर (!lp872x_is_valid_buck_addr(addr))
		वापस -EINVAL;

	वापस lp872x_update_bits(lp, addr, mask, selector);
पूर्ण

अटल पूर्णांक lp872x_buck_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा lp872x *lp = rdev_get_drvdata(rdev);
	क्रमागत lp872x_regulator_id buck = rdev_get_id(rdev);
	u8 addr, val;
	पूर्णांक ret;

	addr = lp872x_select_buck_vout_addr(lp, buck);
	अगर (!lp872x_is_valid_buck_addr(addr))
		वापस -EINVAL;

	ret = lp872x_पढ़ो_byte(lp, addr, &val);
	अगर (ret)
		वापस ret;

	वापस val & LP872X_VOUT_M;
पूर्ण

अटल पूर्णांक lp872x_buck_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा lp872x *lp = rdev_get_drvdata(rdev);
	क्रमागत lp872x_regulator_id buck = rdev_get_id(rdev);
	u8 addr, mask, shअगरt, val;

	चयन (buck) अणु
	हाल LP8720_ID_BUCK:
		addr = LP8720_BUCK_VOUT2;
		mask = LP8720_BUCK_FPWM_M;
		shअगरt = LP8720_BUCK_FPWM_S;
		अवरोध;
	हाल LP8725_ID_BUCK1:
		addr = LP8725_BUCK_CTRL;
		mask = LP8725_BUCK1_FPWM_M;
		shअगरt = LP8725_BUCK1_FPWM_S;
		अवरोध;
	हाल LP8725_ID_BUCK2:
		addr = LP8725_BUCK_CTRL;
		mask = LP8725_BUCK2_FPWM_M;
		shअगरt = LP8725_BUCK2_FPWM_S;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (mode == REGULATOR_MODE_FAST)
		val = LP872X_FORCE_PWM << shअगरt;
	अन्यथा अगर (mode == REGULATOR_MODE_NORMAL)
		val = LP872X_AUTO_PWM << shअगरt;
	अन्यथा
		वापस -EINVAL;

	वापस lp872x_update_bits(lp, addr, mask, val);
पूर्ण

अटल अचिन्हित पूर्णांक lp872x_buck_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा lp872x *lp = rdev_get_drvdata(rdev);
	क्रमागत lp872x_regulator_id buck = rdev_get_id(rdev);
	u8 addr, mask, val;
	पूर्णांक ret;

	चयन (buck) अणु
	हाल LP8720_ID_BUCK:
		addr = LP8720_BUCK_VOUT2;
		mask = LP8720_BUCK_FPWM_M;
		अवरोध;
	हाल LP8725_ID_BUCK1:
		addr = LP8725_BUCK_CTRL;
		mask = LP8725_BUCK1_FPWM_M;
		अवरोध;
	हाल LP8725_ID_BUCK2:
		addr = LP8725_BUCK_CTRL;
		mask = LP8725_BUCK2_FPWM_M;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = lp872x_पढ़ो_byte(lp, addr, &val);
	अगर (ret)
		वापस ret;

	वापस val & mask ? REGULATOR_MODE_FAST : REGULATOR_MODE_NORMAL;
पूर्ण

अटल स्थिर काष्ठा regulator_ops lp872x_lकरो_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.enable_समय = lp872x_regulator_enable_समय,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops lp8720_buck_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
	.set_voltage_sel = lp872x_buck_set_voltage_sel,
	.get_voltage_sel = lp872x_buck_get_voltage_sel,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.enable_समय = lp872x_regulator_enable_समय,
	.set_mode = lp872x_buck_set_mode,
	.get_mode = lp872x_buck_get_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops lp8725_buck_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_ascend,
	.set_voltage_sel = lp872x_buck_set_voltage_sel,
	.get_voltage_sel = lp872x_buck_get_voltage_sel,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.enable_समय = lp872x_regulator_enable_समय,
	.set_mode = lp872x_buck_set_mode,
	.get_mode = lp872x_buck_get_mode,
	.set_current_limit = regulator_set_current_limit_regmap,
	.get_current_limit = regulator_get_current_limit_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc lp8720_regulator_desc[] = अणु
	अणु
		.name = "ldo1",
		.of_match = of_match_ptr("ldo1"),
		.id = LP8720_ID_LDO1,
		.ops = &lp872x_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lp872x_lकरो_vtbl),
		.volt_table = lp872x_lकरो_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP872X_LDO1_VOUT,
		.vsel_mask = LP872X_VOUT_M,
		.enable_reg = LP8720_ENABLE,
		.enable_mask = LP872X_EN_LDO1_M,
	पूर्ण,
	अणु
		.name = "ldo2",
		.of_match = of_match_ptr("ldo2"),
		.id = LP8720_ID_LDO2,
		.ops = &lp872x_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lp872x_lकरो_vtbl),
		.volt_table = lp872x_lकरो_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP872X_LDO2_VOUT,
		.vsel_mask = LP872X_VOUT_M,
		.enable_reg = LP8720_ENABLE,
		.enable_mask = LP872X_EN_LDO2_M,
	पूर्ण,
	अणु
		.name = "ldo3",
		.of_match = of_match_ptr("ldo3"),
		.id = LP8720_ID_LDO3,
		.ops = &lp872x_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lp872x_lकरो_vtbl),
		.volt_table = lp872x_lकरो_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP872X_LDO3_VOUT,
		.vsel_mask = LP872X_VOUT_M,
		.enable_reg = LP8720_ENABLE,
		.enable_mask = LP872X_EN_LDO3_M,
	पूर्ण,
	अणु
		.name = "ldo4",
		.of_match = of_match_ptr("ldo4"),
		.id = LP8720_ID_LDO4,
		.ops = &lp872x_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lp8720_lकरो4_vtbl),
		.volt_table = lp8720_lकरो4_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP872X_LDO4_VOUT,
		.vsel_mask = LP872X_VOUT_M,
		.enable_reg = LP8720_ENABLE,
		.enable_mask = LP872X_EN_LDO4_M,
	पूर्ण,
	अणु
		.name = "ldo5",
		.of_match = of_match_ptr("ldo5"),
		.id = LP8720_ID_LDO5,
		.ops = &lp872x_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lp872x_lकरो_vtbl),
		.volt_table = lp872x_lकरो_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP872X_LDO5_VOUT,
		.vsel_mask = LP872X_VOUT_M,
		.enable_reg = LP8720_ENABLE,
		.enable_mask = LP872X_EN_LDO5_M,
	पूर्ण,
	अणु
		.name = "buck",
		.of_match = of_match_ptr("buck"),
		.id = LP8720_ID_BUCK,
		.ops = &lp8720_buck_ops,
		.n_voltages = ARRAY_SIZE(lp8720_buck_vtbl),
		.volt_table = lp8720_buck_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.enable_reg = LP8720_ENABLE,
		.enable_mask = LP8720_EN_BUCK_M,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc lp8725_regulator_desc[] = अणु
	अणु
		.name = "ldo1",
		.of_match = of_match_ptr("ldo1"),
		.id = LP8725_ID_LDO1,
		.ops = &lp872x_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lp872x_lकरो_vtbl),
		.volt_table = lp872x_lकरो_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP872X_LDO1_VOUT,
		.vsel_mask = LP872X_VOUT_M,
		.enable_reg = LP8725_LDO_CTRL,
		.enable_mask = LP872X_EN_LDO1_M,
	पूर्ण,
	अणु
		.name = "ldo2",
		.of_match = of_match_ptr("ldo2"),
		.id = LP8725_ID_LDO2,
		.ops = &lp872x_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lp872x_lकरो_vtbl),
		.volt_table = lp872x_lकरो_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP872X_LDO2_VOUT,
		.vsel_mask = LP872X_VOUT_M,
		.enable_reg = LP8725_LDO_CTRL,
		.enable_mask = LP872X_EN_LDO2_M,
	पूर्ण,
	अणु
		.name = "ldo3",
		.of_match = of_match_ptr("ldo3"),
		.id = LP8725_ID_LDO3,
		.ops = &lp872x_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lp872x_lकरो_vtbl),
		.volt_table = lp872x_lकरो_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP872X_LDO3_VOUT,
		.vsel_mask = LP872X_VOUT_M,
		.enable_reg = LP8725_LDO_CTRL,
		.enable_mask = LP872X_EN_LDO3_M,
	पूर्ण,
	अणु
		.name = "ldo4",
		.of_match = of_match_ptr("ldo4"),
		.id = LP8725_ID_LDO4,
		.ops = &lp872x_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lp872x_lकरो_vtbl),
		.volt_table = lp872x_lकरो_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP872X_LDO4_VOUT,
		.vsel_mask = LP872X_VOUT_M,
		.enable_reg = LP8725_LDO_CTRL,
		.enable_mask = LP872X_EN_LDO4_M,
	पूर्ण,
	अणु
		.name = "ldo5",
		.of_match = of_match_ptr("ldo5"),
		.id = LP8725_ID_LDO5,
		.ops = &lp872x_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lp872x_lकरो_vtbl),
		.volt_table = lp872x_lकरो_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP872X_LDO5_VOUT,
		.vsel_mask = LP872X_VOUT_M,
		.enable_reg = LP8725_LDO_CTRL,
		.enable_mask = LP872X_EN_LDO5_M,
	पूर्ण,
	अणु
		.name = "lilo1",
		.of_match = of_match_ptr("lilo1"),
		.id = LP8725_ID_LILO1,
		.ops = &lp872x_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lp8725_lilo_vtbl),
		.volt_table = lp8725_lilo_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP8725_LILO1_VOUT,
		.vsel_mask = LP872X_VOUT_M,
		.enable_reg = LP8725_LDO_CTRL,
		.enable_mask = LP8725_EN_LILO1_M,
	पूर्ण,
	अणु
		.name = "lilo2",
		.of_match = of_match_ptr("lilo2"),
		.id = LP8725_ID_LILO2,
		.ops = &lp872x_lकरो_ops,
		.n_voltages = ARRAY_SIZE(lp8725_lilo_vtbl),
		.volt_table = lp8725_lilo_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.vsel_reg = LP8725_LILO2_VOUT,
		.vsel_mask = LP872X_VOUT_M,
		.enable_reg = LP8725_LDO_CTRL,
		.enable_mask = LP8725_EN_LILO2_M,
	पूर्ण,
	अणु
		.name = "buck1",
		.of_match = of_match_ptr("buck1"),
		.id = LP8725_ID_BUCK1,
		.ops = &lp8725_buck_ops,
		.n_voltages = ARRAY_SIZE(lp8725_buck_vtbl),
		.volt_table = lp8725_buck_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.enable_reg = LP872X_GENERAL_CFG,
		.enable_mask = LP8725_BUCK1_EN_M,
		.curr_table = lp8725_buck_uA,
		.n_current_limits = ARRAY_SIZE(lp8725_buck_uA),
		.csel_reg = LP8725_BUCK1_VOUT2,
		.csel_mask = LP8725_BUCK_CL_M,
	पूर्ण,
	अणु
		.name = "buck2",
		.of_match = of_match_ptr("buck2"),
		.id = LP8725_ID_BUCK2,
		.ops = &lp8725_buck_ops,
		.n_voltages = ARRAY_SIZE(lp8725_buck_vtbl),
		.volt_table = lp8725_buck_vtbl,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
		.enable_reg = LP872X_GENERAL_CFG,
		.enable_mask = LP8725_BUCK2_EN_M,
		.curr_table = lp8725_buck_uA,
		.n_current_limits = ARRAY_SIZE(lp8725_buck_uA),
		.csel_reg = LP8725_BUCK2_VOUT2,
		.csel_mask = LP8725_BUCK_CL_M,
	पूर्ण,
पूर्ण;

अटल पूर्णांक lp872x_init_dvs(काष्ठा lp872x *lp)
अणु
	पूर्णांक ret, gpio;
	काष्ठा lp872x_dvs *dvs = lp->pdata ? lp->pdata->dvs : शून्य;
	क्रमागत lp872x_dvs_state pinstate;
	u8 mask[] = अणु LP8720_EXT_DVS_M, LP8725_DVS1_M | LP8725_DVS2_M पूर्ण;
	u8 शेष_dvs_mode[] = अणु LP8720_DEFAULT_DVS, LP8725_DEFAULT_DVS पूर्ण;

	अगर (!dvs)
		जाओ set_शेष_dvs_mode;

	gpio = dvs->gpio;
	अगर (!gpio_is_valid(gpio))
		जाओ set_शेष_dvs_mode;

	pinstate = dvs->init_state;
	ret = devm_gpio_request_one(lp->dev, gpio, pinstate, "LP872X DVS");
	अगर (ret) अणु
		dev_err(lp->dev, "gpio request err: %d\n", ret);
		वापस ret;
	पूर्ण

	lp->dvs_pin = pinstate;

	वापस 0;

set_शेष_dvs_mode:
	वापस lp872x_update_bits(lp, LP872X_GENERAL_CFG, mask[lp->chipid],
				शेष_dvs_mode[lp->chipid]);
पूर्ण

अटल पूर्णांक lp872x_hw_enable(काष्ठा lp872x *lp)
अणु
	पूर्णांक ret, gpio;

	अगर (!lp->pdata)
		वापस -EINVAL;

	gpio = lp->pdata->enable_gpio;
	अगर (!gpio_is_valid(gpio))
		वापस 0;

	/* Always set enable GPIO high. */
	ret = devm_gpio_request_one(lp->dev, gpio, GPIOF_OUT_INIT_HIGH, "LP872X EN");
	अगर (ret) अणु
		dev_err(lp->dev, "gpio request err: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Each chip has a dअगरferent enable delay. */
	अगर (lp->chipid == LP8720)
		usleep_range(LP8720_ENABLE_DELAY, 1.5 * LP8720_ENABLE_DELAY);
	अन्यथा
		usleep_range(LP8725_ENABLE_DELAY, 1.5 * LP8725_ENABLE_DELAY);

	वापस 0;
पूर्ण

अटल पूर्णांक lp872x_config(काष्ठा lp872x *lp)
अणु
	काष्ठा lp872x_platक्रमm_data *pdata = lp->pdata;
	पूर्णांक ret;

	अगर (!pdata || !pdata->update_config)
		जाओ init_dvs;

	ret = lp872x_ग_लिखो_byte(lp, LP872X_GENERAL_CFG, pdata->general_config);
	अगर (ret)
		वापस ret;

init_dvs:
	वापस lp872x_init_dvs(lp);
पूर्ण

अटल काष्ठा regulator_init_data
*lp872x_find_regulator_init_data(पूर्णांक id, काष्ठा lp872x *lp)
अणु
	काष्ठा lp872x_platक्रमm_data *pdata = lp->pdata;
	पूर्णांक i;

	अगर (!pdata)
		वापस शून्य;

	क्रम (i = 0; i < lp->num_regulators; i++) अणु
		अगर (pdata->regulator_data[i].id == id)
			वापस pdata->regulator_data[i].init_data;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक lp872x_regulator_रेजिस्टर(काष्ठा lp872x *lp)
अणु
	स्थिर काष्ठा regulator_desc *desc;
	काष्ठा regulator_config cfg = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	पूर्णांक i;

	क्रम (i = 0; i < lp->num_regulators; i++) अणु
		desc = (lp->chipid == LP8720) ? &lp8720_regulator_desc[i] :
						&lp8725_regulator_desc[i];

		cfg.dev = lp->dev;
		cfg.init_data = lp872x_find_regulator_init_data(desc->id, lp);
		cfg.driver_data = lp;
		cfg.regmap = lp->regmap;

		rdev = devm_regulator_रेजिस्टर(lp->dev, desc, &cfg);
		अगर (IS_ERR(rdev)) अणु
			dev_err(lp->dev, "regulator register err");
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config lp872x_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = MAX_REGISTERS,
पूर्ण;

#अगर_घोषित CONFIG_OF

#घोषणा LP872X_VALID_OPMODE	(REGULATOR_MODE_FAST | REGULATOR_MODE_NORMAL)

अटल काष्ठा of_regulator_match lp8720_matches[] = अणु
	अणु .name = "ldo1", .driver_data = (व्योम *)LP8720_ID_LDO1, पूर्ण,
	अणु .name = "ldo2", .driver_data = (व्योम *)LP8720_ID_LDO2, पूर्ण,
	अणु .name = "ldo3", .driver_data = (व्योम *)LP8720_ID_LDO3, पूर्ण,
	अणु .name = "ldo4", .driver_data = (व्योम *)LP8720_ID_LDO4, पूर्ण,
	अणु .name = "ldo5", .driver_data = (व्योम *)LP8720_ID_LDO5, पूर्ण,
	अणु .name = "buck", .driver_data = (व्योम *)LP8720_ID_BUCK, पूर्ण,
पूर्ण;

अटल काष्ठा of_regulator_match lp8725_matches[] = अणु
	अणु .name = "ldo1", .driver_data = (व्योम *)LP8725_ID_LDO1, पूर्ण,
	अणु .name = "ldo2", .driver_data = (व्योम *)LP8725_ID_LDO2, पूर्ण,
	अणु .name = "ldo3", .driver_data = (व्योम *)LP8725_ID_LDO3, पूर्ण,
	अणु .name = "ldo4", .driver_data = (व्योम *)LP8725_ID_LDO4, पूर्ण,
	अणु .name = "ldo5", .driver_data = (व्योम *)LP8725_ID_LDO5, पूर्ण,
	अणु .name = "lilo1", .driver_data = (व्योम *)LP8725_ID_LILO1, पूर्ण,
	अणु .name = "lilo2", .driver_data = (व्योम *)LP8725_ID_LILO2, पूर्ण,
	अणु .name = "buck1", .driver_data = (व्योम *)LP8725_ID_BUCK1, पूर्ण,
	अणु .name = "buck2", .driver_data = (व्योम *)LP8725_ID_BUCK2, पूर्ण,
पूर्ण;

अटल काष्ठा lp872x_platक्रमm_data
*lp872x_populate_pdata_from_dt(काष्ठा device *dev, क्रमागत lp872x_id which)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा lp872x_platक्रमm_data *pdata;
	काष्ठा of_regulator_match *match;
	पूर्णांक num_matches;
	पूर्णांक count;
	पूर्णांक i;
	u8 dvs_state;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	of_property_पढ़ो_u8(np, "ti,general-config", &pdata->general_config);
	अगर (of_find_property(np, "ti,update-config", शून्य))
		pdata->update_config = true;

	pdata->dvs = devm_kzalloc(dev, माप(काष्ठा lp872x_dvs), GFP_KERNEL);
	अगर (!pdata->dvs)
		वापस ERR_PTR(-ENOMEM);

	pdata->dvs->gpio = of_get_named_gpio(np, "ti,dvs-gpio", 0);
	of_property_पढ़ो_u8(np, "ti,dvs-vsel", (u8 *)&pdata->dvs->vsel);
	of_property_पढ़ो_u8(np, "ti,dvs-state", &dvs_state);
	pdata->dvs->init_state = dvs_state ? DVS_HIGH : DVS_LOW;

	pdata->enable_gpio = of_get_named_gpio(np, "enable-gpios", 0);

	अगर (of_get_child_count(np) == 0)
		जाओ out;

	चयन (which) अणु
	हाल LP8720:
		match = lp8720_matches;
		num_matches = ARRAY_SIZE(lp8720_matches);
		अवरोध;
	हाल LP8725:
		match = lp8725_matches;
		num_matches = ARRAY_SIZE(lp8725_matches);
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	count = of_regulator_match(dev, np, match, num_matches);
	अगर (count <= 0)
		जाओ out;

	क्रम (i = 0; i < num_matches; i++) अणु
		pdata->regulator_data[i].id =
				(क्रमागत lp872x_regulator_id)match[i].driver_data;
		pdata->regulator_data[i].init_data = match[i].init_data;
	पूर्ण
out:
	वापस pdata;
पूर्ण
#अन्यथा
अटल काष्ठा lp872x_platक्रमm_data
*lp872x_populate_pdata_from_dt(काष्ठा device *dev, क्रमागत lp872x_id which)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक lp872x_probe(काष्ठा i2c_client *cl, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lp872x *lp;
	काष्ठा lp872x_platक्रमm_data *pdata;
	पूर्णांक ret;
	अटल स्थिर पूर्णांक lp872x_num_regulators[] = अणु
		[LP8720] = LP8720_NUM_REGULATORS,
		[LP8725] = LP8725_NUM_REGULATORS,
	पूर्ण;

	अगर (cl->dev.of_node) अणु
		pdata = lp872x_populate_pdata_from_dt(&cl->dev,
					      (क्रमागत lp872x_id)id->driver_data);
		अगर (IS_ERR(pdata))
			वापस PTR_ERR(pdata);
	पूर्ण अन्यथा अणु
		pdata = dev_get_platdata(&cl->dev);
	पूर्ण

	lp = devm_kzalloc(&cl->dev, माप(काष्ठा lp872x), GFP_KERNEL);
	अगर (!lp)
		वापस -ENOMEM;

	lp->num_regulators = lp872x_num_regulators[id->driver_data];

	lp->regmap = devm_regmap_init_i2c(cl, &lp872x_regmap_config);
	अगर (IS_ERR(lp->regmap)) अणु
		ret = PTR_ERR(lp->regmap);
		dev_err(&cl->dev, "regmap init i2c err: %d\n", ret);
		वापस ret;
	पूर्ण

	lp->dev = &cl->dev;
	lp->pdata = pdata;
	lp->chipid = id->driver_data;
	i2c_set_clientdata(cl, lp);

	ret = lp872x_hw_enable(lp);
	अगर (ret)
		वापस ret;

	ret = lp872x_config(lp);
	अगर (ret)
		वापस ret;

	वापस lp872x_regulator_रेजिस्टर(lp);
पूर्ण

अटल स्थिर काष्ठा of_device_id lp872x_dt_ids[] = अणु
	अणु .compatible = "ti,lp8720", पूर्ण,
	अणु .compatible = "ti,lp8725", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lp872x_dt_ids);

अटल स्थिर काष्ठा i2c_device_id lp872x_ids[] = अणु
	अणु"lp8720", LP8720पूर्ण,
	अणु"lp8725", LP8725पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lp872x_ids);

अटल काष्ठा i2c_driver lp872x_driver = अणु
	.driver = अणु
		.name = "lp872x",
		.of_match_table = of_match_ptr(lp872x_dt_ids),
	पूर्ण,
	.probe = lp872x_probe,
	.id_table = lp872x_ids,
पूर्ण;

module_i2c_driver(lp872x_driver);

MODULE_DESCRIPTION("TI/National Semiconductor LP872x PMU Regulator Driver");
MODULE_AUTHOR("Milo Kim");
MODULE_LICENSE("GPL");
