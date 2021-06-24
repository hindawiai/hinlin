<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// max8997.c - Regulator driver क्रम the Maxim 8997/8966
//
// Copyright (C) 2011 Samsung Electronics
// MyungJoo Ham <myungjoo.ham@samsung.com>
//
// This driver is based on max8998.c

#समावेश <linux/bug.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/mfd/max8997.h>
#समावेश <linux/mfd/max8997-निजी.h>
#समावेश <linux/regulator/of_regulator.h>

काष्ठा max8997_data अणु
	काष्ठा device *dev;
	काष्ठा max8997_dev *iodev;
	पूर्णांक num_regulators;
	पूर्णांक ramp_delay; /* in mV/us */

	bool buck1_gpiodvs;
	bool buck2_gpiodvs;
	bool buck5_gpiodvs;
	u8 buck1_vol[8];
	u8 buck2_vol[8];
	u8 buck5_vol[8];
	पूर्णांक buck125_gpios[3];
	पूर्णांक buck125_gpioindex;
	bool ignore_gpiodvs_side_effect;

	u8 saved_states[MAX8997_REG_MAX];
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक safeoutvolt[] = अणु
	4850000,
	4900000,
	4950000,
	3300000,
पूर्ण;

अटल अंतरभूत व्योम max8997_set_gpio(काष्ठा max8997_data *max8997)
अणु
	पूर्णांक set3 = (max8997->buck125_gpioindex) & 0x1;
	पूर्णांक set2 = ((max8997->buck125_gpioindex) >> 1) & 0x1;
	पूर्णांक set1 = ((max8997->buck125_gpioindex) >> 2) & 0x1;

	gpio_set_value(max8997->buck125_gpios[0], set1);
	gpio_set_value(max8997->buck125_gpios[1], set2);
	gpio_set_value(max8997->buck125_gpios[2], set3);
पूर्ण

काष्ठा voltage_map_desc अणु
	पूर्णांक min;
	पूर्णांक max;
	पूर्णांक step;
पूर्ण;

/* Voltage maps in uV */
अटल स्थिर काष्ठा voltage_map_desc lकरो_voltage_map_desc = अणु
	.min = 800000,	.max = 3950000,	.step = 50000,
पूर्ण; /* LDO1 ~ 18, 21 all */

अटल स्थिर काष्ठा voltage_map_desc buck1245_voltage_map_desc = अणु
	.min = 650000,	.max = 2225000,	.step = 25000,
पूर्ण; /* Buck1, 2, 4, 5 */

अटल स्थिर काष्ठा voltage_map_desc buck37_voltage_map_desc = अणु
	.min = 750000,	.max = 3900000,	.step = 50000,
पूर्ण; /* Buck3, 7 */

/* current map in uA */
अटल स्थिर काष्ठा voltage_map_desc अक्षरger_current_map_desc = अणु
	.min = 200000,	.max = 950000,	.step = 50000,
पूर्ण;

अटल स्थिर काष्ठा voltage_map_desc topoff_current_map_desc = अणु
	.min = 50000,	.max = 200000,	.step = 10000,
पूर्ण;

अटल स्थिर काष्ठा voltage_map_desc *reg_voltage_map[] = अणु
	[MAX8997_LDO1] = &lकरो_voltage_map_desc,
	[MAX8997_LDO2] = &lकरो_voltage_map_desc,
	[MAX8997_LDO3] = &lकरो_voltage_map_desc,
	[MAX8997_LDO4] = &lकरो_voltage_map_desc,
	[MAX8997_LDO5] = &lकरो_voltage_map_desc,
	[MAX8997_LDO6] = &lकरो_voltage_map_desc,
	[MAX8997_LDO7] = &lकरो_voltage_map_desc,
	[MAX8997_LDO8] = &lकरो_voltage_map_desc,
	[MAX8997_LDO9] = &lकरो_voltage_map_desc,
	[MAX8997_LDO10] = &lकरो_voltage_map_desc,
	[MAX8997_LDO11] = &lकरो_voltage_map_desc,
	[MAX8997_LDO12] = &lकरो_voltage_map_desc,
	[MAX8997_LDO13] = &lकरो_voltage_map_desc,
	[MAX8997_LDO14] = &lकरो_voltage_map_desc,
	[MAX8997_LDO15] = &lकरो_voltage_map_desc,
	[MAX8997_LDO16] = &lकरो_voltage_map_desc,
	[MAX8997_LDO17] = &lकरो_voltage_map_desc,
	[MAX8997_LDO18] = &lकरो_voltage_map_desc,
	[MAX8997_LDO21] = &lकरो_voltage_map_desc,
	[MAX8997_BUCK1] = &buck1245_voltage_map_desc,
	[MAX8997_BUCK2] = &buck1245_voltage_map_desc,
	[MAX8997_BUCK3] = &buck37_voltage_map_desc,
	[MAX8997_BUCK4] = &buck1245_voltage_map_desc,
	[MAX8997_BUCK5] = &buck1245_voltage_map_desc,
	[MAX8997_BUCK6] = शून्य,
	[MAX8997_BUCK7] = &buck37_voltage_map_desc,
	[MAX8997_EN32KHZ_AP] = शून्य,
	[MAX8997_EN32KHZ_CP] = शून्य,
	[MAX8997_ENVICHG] = शून्य,
	[MAX8997_ESAFEOUT1] = शून्य,
	[MAX8997_ESAFEOUT2] = शून्य,
	[MAX8997_CHARGER_CV] = शून्य,
	[MAX8997_CHARGER] = &अक्षरger_current_map_desc,
	[MAX8997_CHARGER_TOPOFF] = &topoff_current_map_desc,
पूर्ण;

अटल पूर्णांक max8997_list_voltage_अक्षरger_cv(काष्ठा regulator_dev *rdev,
		अचिन्हित पूर्णांक selector)
अणु
	पूर्णांक rid = rdev_get_id(rdev);

	अगर (rid != MAX8997_CHARGER_CV)
		जाओ err;

	चयन (selector) अणु
	हाल 0x00:
		वापस 4200000;
	हाल 0x01 ... 0x0E:
		वापस 4000000 + 20000 * (selector - 0x01);
	हाल 0x0F:
		वापस 4350000;
	शेष:
		वापस -EINVAL;
	पूर्ण
err:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक max8997_list_voltage(काष्ठा regulator_dev *rdev,
		अचिन्हित पूर्णांक selector)
अणु
	स्थिर काष्ठा voltage_map_desc *desc;
	पूर्णांक rid = rdev_get_id(rdev);
	पूर्णांक val;

	अगर (rid < 0 || rid >= ARRAY_SIZE(reg_voltage_map))
		वापस -EINVAL;

	desc = reg_voltage_map[rid];
	अगर (desc == शून्य)
		वापस -EINVAL;

	val = desc->min + desc->step * selector;
	अगर (val > desc->max)
		वापस -EINVAL;

	वापस val;
पूर्ण

अटल पूर्णांक max8997_get_enable_रेजिस्टर(काष्ठा regulator_dev *rdev,
		पूर्णांक *reg, पूर्णांक *mask, पूर्णांक *pattern)
अणु
	पूर्णांक rid = rdev_get_id(rdev);

	चयन (rid) अणु
	हाल MAX8997_LDO1 ... MAX8997_LDO21:
		*reg = MAX8997_REG_LDO1CTRL + (rid - MAX8997_LDO1);
		*mask = 0xC0;
		*pattern = 0xC0;
		अवरोध;
	हाल MAX8997_BUCK1:
		*reg = MAX8997_REG_BUCK1CTRL;
		*mask = 0x01;
		*pattern = 0x01;
		अवरोध;
	हाल MAX8997_BUCK2:
		*reg = MAX8997_REG_BUCK2CTRL;
		*mask = 0x01;
		*pattern = 0x01;
		अवरोध;
	हाल MAX8997_BUCK3:
		*reg = MAX8997_REG_BUCK3CTRL;
		*mask = 0x01;
		*pattern = 0x01;
		अवरोध;
	हाल MAX8997_BUCK4:
		*reg = MAX8997_REG_BUCK4CTRL;
		*mask = 0x01;
		*pattern = 0x01;
		अवरोध;
	हाल MAX8997_BUCK5:
		*reg = MAX8997_REG_BUCK5CTRL;
		*mask = 0x01;
		*pattern = 0x01;
		अवरोध;
	हाल MAX8997_BUCK6:
		*reg = MAX8997_REG_BUCK6CTRL;
		*mask = 0x01;
		*pattern = 0x01;
		अवरोध;
	हाल MAX8997_BUCK7:
		*reg = MAX8997_REG_BUCK7CTRL;
		*mask = 0x01;
		*pattern = 0x01;
		अवरोध;
	हाल MAX8997_EN32KHZ_AP ... MAX8997_EN32KHZ_CP:
		*reg = MAX8997_REG_MAINCON1;
		*mask = 0x01 << (rid - MAX8997_EN32KHZ_AP);
		*pattern = 0x01 << (rid - MAX8997_EN32KHZ_AP);
		अवरोध;
	हाल MAX8997_ENVICHG:
		*reg = MAX8997_REG_MBCCTRL1;
		*mask = 0x80;
		*pattern = 0x80;
		अवरोध;
	हाल MAX8997_ESAFEOUT1 ... MAX8997_ESAFEOUT2:
		*reg = MAX8997_REG_SAFEOUTCTRL;
		*mask = 0x40 << (rid - MAX8997_ESAFEOUT1);
		*pattern = 0x40 << (rid - MAX8997_ESAFEOUT1);
		अवरोध;
	हाल MAX8997_CHARGER:
		*reg = MAX8997_REG_MBCCTRL2;
		*mask = 0x40;
		*pattern = 0x40;
		अवरोध;
	शेष:
		/* Not controllable or not exists */
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max8997_reg_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8997_data *max8997 = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *i2c = max8997->iodev->i2c;
	पूर्णांक ret, reg, mask, pattern;
	u8 val;

	ret = max8997_get_enable_रेजिस्टर(rdev, &reg, &mask, &pattern);
	अगर (ret)
		वापस ret;

	ret = max8997_पढ़ो_reg(i2c, reg, &val);
	अगर (ret)
		वापस ret;

	वापस (val & mask) == pattern;
पूर्ण

अटल पूर्णांक max8997_reg_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8997_data *max8997 = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *i2c = max8997->iodev->i2c;
	पूर्णांक ret, reg, mask, pattern;

	ret = max8997_get_enable_रेजिस्टर(rdev, &reg, &mask, &pattern);
	अगर (ret)
		वापस ret;

	वापस max8997_update_reg(i2c, reg, pattern, mask);
पूर्ण

अटल पूर्णांक max8997_reg_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8997_data *max8997 = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *i2c = max8997->iodev->i2c;
	पूर्णांक ret, reg, mask, pattern;

	ret = max8997_get_enable_रेजिस्टर(rdev, &reg, &mask, &pattern);
	अगर (ret)
		वापस ret;

	वापस max8997_update_reg(i2c, reg, ~pattern, mask);
पूर्ण

अटल पूर्णांक max8997_get_voltage_रेजिस्टर(काष्ठा regulator_dev *rdev,
		पूर्णांक *_reg, पूर्णांक *_shअगरt, पूर्णांक *_mask)
अणु
	काष्ठा max8997_data *max8997 = rdev_get_drvdata(rdev);
	पूर्णांक rid = rdev_get_id(rdev);
	पूर्णांक reg, shअगरt = 0, mask = 0x3f;

	चयन (rid) अणु
	हाल MAX8997_LDO1 ... MAX8997_LDO21:
		reg = MAX8997_REG_LDO1CTRL + (rid - MAX8997_LDO1);
		अवरोध;
	हाल MAX8997_BUCK1:
		reg = MAX8997_REG_BUCK1DVS1;
		अगर (max8997->buck1_gpiodvs)
			reg += max8997->buck125_gpioindex;
		अवरोध;
	हाल MAX8997_BUCK2:
		reg = MAX8997_REG_BUCK2DVS1;
		अगर (max8997->buck2_gpiodvs)
			reg += max8997->buck125_gpioindex;
		अवरोध;
	हाल MAX8997_BUCK3:
		reg = MAX8997_REG_BUCK3DVS;
		अवरोध;
	हाल MAX8997_BUCK4:
		reg = MAX8997_REG_BUCK4DVS;
		अवरोध;
	हाल MAX8997_BUCK5:
		reg = MAX8997_REG_BUCK5DVS1;
		अगर (max8997->buck5_gpiodvs)
			reg += max8997->buck125_gpioindex;
		अवरोध;
	हाल MAX8997_BUCK7:
		reg = MAX8997_REG_BUCK7DVS;
		अवरोध;
	हाल MAX8997_ESAFEOUT1 ...  MAX8997_ESAFEOUT2:
		reg = MAX8997_REG_SAFEOUTCTRL;
		shअगरt = (rid == MAX8997_ESAFEOUT2) ? 2 : 0;
		mask = 0x3;
		अवरोध;
	हाल MAX8997_CHARGER_CV:
		reg = MAX8997_REG_MBCCTRL3;
		shअगरt = 0;
		mask = 0xf;
		अवरोध;
	हाल MAX8997_CHARGER:
		reg = MAX8997_REG_MBCCTRL4;
		shअगरt = 0;
		mask = 0xf;
		अवरोध;
	हाल MAX8997_CHARGER_TOPOFF:
		reg = MAX8997_REG_MBCCTRL5;
		shअगरt = 0;
		mask = 0xf;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*_reg = reg;
	*_shअगरt = shअगरt;
	*_mask = mask;

	वापस 0;
पूर्ण

अटल पूर्णांक max8997_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8997_data *max8997 = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *i2c = max8997->iodev->i2c;
	पूर्णांक reg, shअगरt, mask, ret;
	u8 val;

	ret = max8997_get_voltage_रेजिस्टर(rdev, &reg, &shअगरt, &mask);
	अगर (ret)
		वापस ret;

	ret = max8997_पढ़ो_reg(i2c, reg, &val);
	अगर (ret)
		वापस ret;

	val >>= shअगरt;
	val &= mask;

	वापस val;
पूर्ण

अटल अंतरभूत पूर्णांक max8997_get_voltage_proper_val(
		स्थिर काष्ठा voltage_map_desc *desc,
		पूर्णांक min_vol, पूर्णांक max_vol)
अणु
	पूर्णांक i;

	अगर (desc == शून्य)
		वापस -EINVAL;

	अगर (max_vol < desc->min || min_vol > desc->max)
		वापस -EINVAL;

	अगर (min_vol < desc->min)
		min_vol = desc->min;

	i = DIV_ROUND_UP(min_vol - desc->min, desc->step);

	अगर (desc->min + desc->step * i > max_vol)
		वापस -EINVAL;

	वापस i;
पूर्ण

अटल पूर्णांक max8997_set_voltage_अक्षरger_cv(काष्ठा regulator_dev *rdev,
		पूर्णांक min_uV, पूर्णांक max_uV, अचिन्हित *selector)
अणु
	काष्ठा max8997_data *max8997 = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *i2c = max8997->iodev->i2c;
	पूर्णांक rid = rdev_get_id(rdev);
	पूर्णांक lb, ub;
	पूर्णांक reg, shअगरt = 0, mask, ret = 0;
	u8 val = 0x0;

	अगर (rid != MAX8997_CHARGER_CV)
		वापस -EINVAL;

	ret = max8997_get_voltage_रेजिस्टर(rdev, &reg, &shअगरt, &mask);
	अगर (ret)
		वापस ret;

	अगर (max_uV < 4000000 || min_uV > 4350000)
		वापस -EINVAL;

	अगर (min_uV <= 4000000)
		val = 0x1;
	अन्यथा अगर (min_uV <= 4200000 && max_uV >= 4200000)
		val = 0x0;
	अन्यथा अणु
		lb = (min_uV - 4000001) / 20000 + 2;
		ub = (max_uV - 4000000) / 20000 + 1;

		अगर (lb > ub)
			वापस -EINVAL;

		अगर (lb < 0xf)
			val = lb;
		अन्यथा अणु
			अगर (ub >= 0xf)
				val = 0xf;
			अन्यथा
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	*selector = val;

	ret = max8997_update_reg(i2c, reg, val << shअगरt, mask);

	वापस ret;
पूर्ण

/*
 * For LDO1 ~ LDO21, BUCK1~5, BUCK7, CHARGER, CHARGER_TOPOFF
 * BUCK1, 2, and 5 are available अगर they are not controlled by gpio
 */
अटल पूर्णांक max8997_set_voltage_lकरोbuck(काष्ठा regulator_dev *rdev,
		पूर्णांक min_uV, पूर्णांक max_uV, अचिन्हित *selector)
अणु
	काष्ठा max8997_data *max8997 = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *i2c = max8997->iodev->i2c;
	स्थिर काष्ठा voltage_map_desc *desc;
	पूर्णांक rid = rdev_get_id(rdev);
	पूर्णांक i, reg, shअगरt, mask, ret;

	चयन (rid) अणु
	हाल MAX8997_LDO1 ... MAX8997_LDO21:
		अवरोध;
	हाल MAX8997_BUCK1 ... MAX8997_BUCK5:
		अवरोध;
	हाल MAX8997_BUCK6:
		वापस -EINVAL;
	हाल MAX8997_BUCK7:
		अवरोध;
	हाल MAX8997_CHARGER:
		अवरोध;
	हाल MAX8997_CHARGER_TOPOFF:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	desc = reg_voltage_map[rid];

	i = max8997_get_voltage_proper_val(desc, min_uV, max_uV);
	अगर (i < 0)
		वापस i;

	ret = max8997_get_voltage_रेजिस्टर(rdev, &reg, &shअगरt, &mask);
	अगर (ret)
		वापस ret;

	ret = max8997_update_reg(i2c, reg, i << shअगरt, mask << shअगरt);
	*selector = i;

	वापस ret;
पूर्ण

अटल पूर्णांक max8997_set_voltage_buck_समय_sel(काष्ठा regulator_dev *rdev,
						अचिन्हित पूर्णांक old_selector,
						अचिन्हित पूर्णांक new_selector)
अणु
	काष्ठा max8997_data *max8997 = rdev_get_drvdata(rdev);
	पूर्णांक rid = rdev_get_id(rdev);
	स्थिर काष्ठा voltage_map_desc *desc = reg_voltage_map[rid];

	/* Delay is required only अगर the voltage is increasing */
	अगर (old_selector >= new_selector)
		वापस 0;

	/* No need to delay अगर gpio_dvs_mode */
	चयन (rid) अणु
	हाल MAX8997_BUCK1:
		अगर (max8997->buck1_gpiodvs)
			वापस 0;
		अवरोध;
	हाल MAX8997_BUCK2:
		अगर (max8997->buck2_gpiodvs)
			वापस 0;
		अवरोध;
	हाल MAX8997_BUCK5:
		अगर (max8997->buck5_gpiodvs)
			वापस 0;
		अवरोध;
	पूर्ण

	चयन (rid) अणु
	हाल MAX8997_BUCK1:
	हाल MAX8997_BUCK2:
	हाल MAX8997_BUCK4:
	हाल MAX8997_BUCK5:
		वापस DIV_ROUND_UP(desc->step * (new_selector - old_selector),
				    max8997->ramp_delay * 1000);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Assess the damage on the voltage setting of BUCK1,2,5 by the change.
 *
 * When GPIO-DVS mode is used क्रम multiple bucks, changing the voltage value
 * of one of the bucks may affect that of another buck, which is the side
 * effect of the change (set_voltage). This function examines the GPIO-DVS
 * configurations and checks whether such side-effect exists.
 */
अटल पूर्णांक max8997_assess_side_effect(काष्ठा regulator_dev *rdev,
		u8 new_val, पूर्णांक *best)
अणु
	काष्ठा max8997_data *max8997 = rdev_get_drvdata(rdev);
	पूर्णांक rid = rdev_get_id(rdev);
	u8 *buckx_val[3];
	bool buckx_gpiodvs[3];
	पूर्णांक side_effect[8];
	पूर्णांक min_side_effect = पूर्णांक_उच्च;
	पूर्णांक i;

	*best = -1;

	चयन (rid) अणु
	हाल MAX8997_BUCK1:
		rid = 0;
		अवरोध;
	हाल MAX8997_BUCK2:
		rid = 1;
		अवरोध;
	हाल MAX8997_BUCK5:
		rid = 2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	buckx_val[0] = max8997->buck1_vol;
	buckx_val[1] = max8997->buck2_vol;
	buckx_val[2] = max8997->buck5_vol;
	buckx_gpiodvs[0] = max8997->buck1_gpiodvs;
	buckx_gpiodvs[1] = max8997->buck2_gpiodvs;
	buckx_gpiodvs[2] = max8997->buck5_gpiodvs;

	क्रम (i = 0; i < 8; i++) अणु
		पूर्णांक others;

		अगर (new_val != (buckx_val[rid])[i]) अणु
			side_effect[i] = -1;
			जारी;
		पूर्ण

		side_effect[i] = 0;
		क्रम (others = 0; others < 3; others++) अणु
			पूर्णांक dअगरf;

			अगर (others == rid)
				जारी;
			अगर (buckx_gpiodvs[others] == false)
				जारी; /* Not affected */
			dअगरf = (buckx_val[others])[i] -
				(buckx_val[others])[max8997->buck125_gpioindex];
			अगर (dअगरf > 0)
				side_effect[i] += dअगरf;
			अन्यथा अगर (dअगरf < 0)
				side_effect[i] -= dअगरf;
		पूर्ण
		अगर (side_effect[i] == 0) अणु
			*best = i;
			वापस 0; /* NO SIDE EFFECT! Use This! */
		पूर्ण
		अगर (side_effect[i] < min_side_effect) अणु
			min_side_effect = side_effect[i];
			*best = i;
		पूर्ण
	पूर्ण

	अगर (*best == -1)
		वापस -EINVAL;

	वापस side_effect[*best];
पूर्ण

/*
 * For Buck 1 ~ 5 and 7. If it is not controlled by GPIO, this calls
 * max8997_set_voltage_lकरोbuck to करो the job.
 */
अटल पूर्णांक max8997_set_voltage_buck(काष्ठा regulator_dev *rdev,
		पूर्णांक min_uV, पूर्णांक max_uV, अचिन्हित *selector)
अणु
	काष्ठा max8997_data *max8997 = rdev_get_drvdata(rdev);
	पूर्णांक rid = rdev_get_id(rdev);
	स्थिर काष्ठा voltage_map_desc *desc;
	पूर्णांक new_val, new_idx, damage, पंचांगp_val, पंचांगp_idx, पंचांगp_dmg;
	bool gpio_dvs_mode = false;

	अगर (rid < MAX8997_BUCK1 || rid > MAX8997_BUCK7)
		वापस -EINVAL;

	चयन (rid) अणु
	हाल MAX8997_BUCK1:
		अगर (max8997->buck1_gpiodvs)
			gpio_dvs_mode = true;
		अवरोध;
	हाल MAX8997_BUCK2:
		अगर (max8997->buck2_gpiodvs)
			gpio_dvs_mode = true;
		अवरोध;
	हाल MAX8997_BUCK5:
		अगर (max8997->buck5_gpiodvs)
			gpio_dvs_mode = true;
		अवरोध;
	पूर्ण

	अगर (!gpio_dvs_mode)
		वापस max8997_set_voltage_lकरोbuck(rdev, min_uV, max_uV,
						selector);

	desc = reg_voltage_map[rid];
	new_val = max8997_get_voltage_proper_val(desc, min_uV, max_uV);
	अगर (new_val < 0)
		वापस new_val;

	पंचांगp_dmg = पूर्णांक_उच्च;
	पंचांगp_idx = -1;
	पंचांगp_val = -1;
	करो अणु
		damage = max8997_assess_side_effect(rdev, new_val, &new_idx);
		अगर (damage == 0)
			जाओ out;

		अगर (पंचांगp_dmg > damage) अणु
			पंचांगp_idx = new_idx;
			पंचांगp_val = new_val;
			पंचांगp_dmg = damage;
		पूर्ण

		new_val++;
	पूर्ण जबतक (desc->min + desc->step * new_val <= desc->max);

	new_idx = पंचांगp_idx;
	new_val = पंचांगp_val;

	अगर (max8997->ignore_gpiodvs_side_effect == false)
		वापस -EINVAL;

	dev_warn(&rdev->dev,
		"MAX8997 GPIO-DVS Side Effect Warning: GPIO SET:  %d -> %d\n",
		max8997->buck125_gpioindex, पंचांगp_idx);

out:
	अगर (new_idx < 0 || new_val < 0)
		वापस -EINVAL;

	max8997->buck125_gpioindex = new_idx;
	max8997_set_gpio(max8997);
	*selector = new_val;

	वापस 0;
पूर्ण

/* For SAFEOUT1 and SAFEOUT2 */
अटल पूर्णांक max8997_set_voltage_safeout_sel(काष्ठा regulator_dev *rdev,
					   अचिन्हित selector)
अणु
	काष्ठा max8997_data *max8997 = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *i2c = max8997->iodev->i2c;
	पूर्णांक rid = rdev_get_id(rdev);
	पूर्णांक reg, shअगरt = 0, mask, ret;

	अगर (rid != MAX8997_ESAFEOUT1 && rid != MAX8997_ESAFEOUT2)
		वापस -EINVAL;

	ret = max8997_get_voltage_रेजिस्टर(rdev, &reg, &shअगरt, &mask);
	अगर (ret)
		वापस ret;

	वापस max8997_update_reg(i2c, reg, selector << shअगरt, mask << shअगरt);
पूर्ण

अटल पूर्णांक max8997_reg_disable_suspend(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8997_data *max8997 = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *i2c = max8997->iodev->i2c;
	पूर्णांक ret, reg, mask, pattern;
	पूर्णांक rid = rdev_get_id(rdev);

	ret = max8997_get_enable_रेजिस्टर(rdev, &reg, &mask, &pattern);
	अगर (ret)
		वापस ret;

	max8997_पढ़ो_reg(i2c, reg, &max8997->saved_states[rid]);

	अगर (rid == MAX8997_LDO1 ||
			rid == MAX8997_LDO10 ||
			rid == MAX8997_LDO21) अणु
		dev_dbg(&rdev->dev, "Conditional Power-Off for %s\n",
				rdev->desc->name);
		वापस max8997_update_reg(i2c, reg, 0x40, mask);
	पूर्ण

	dev_dbg(&rdev->dev, "Full Power-Off for %s (%xh -> %xh)\n",
			rdev->desc->name, max8997->saved_states[rid] & mask,
			(~pattern) & mask);
	वापस max8997_update_reg(i2c, reg, ~pattern, mask);
पूर्ण

अटल स्थिर काष्ठा regulator_ops max8997_lकरो_ops = अणु
	.list_voltage		= max8997_list_voltage,
	.is_enabled		= max8997_reg_is_enabled,
	.enable			= max8997_reg_enable,
	.disable		= max8997_reg_disable,
	.get_voltage_sel	= max8997_get_voltage_sel,
	.set_voltage		= max8997_set_voltage_lकरोbuck,
	.set_suspend_disable	= max8997_reg_disable_suspend,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max8997_buck_ops = अणु
	.list_voltage		= max8997_list_voltage,
	.is_enabled		= max8997_reg_is_enabled,
	.enable			= max8997_reg_enable,
	.disable		= max8997_reg_disable,
	.get_voltage_sel	= max8997_get_voltage_sel,
	.set_voltage		= max8997_set_voltage_buck,
	.set_voltage_समय_sel	= max8997_set_voltage_buck_समय_sel,
	.set_suspend_disable	= max8997_reg_disable_suspend,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max8997_fixedvolt_ops = अणु
	.list_voltage		= max8997_list_voltage,
	.is_enabled		= max8997_reg_is_enabled,
	.enable			= max8997_reg_enable,
	.disable		= max8997_reg_disable,
	.set_suspend_disable	= max8997_reg_disable_suspend,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max8997_safeout_ops = अणु
	.list_voltage		= regulator_list_voltage_table,
	.is_enabled		= max8997_reg_is_enabled,
	.enable			= max8997_reg_enable,
	.disable		= max8997_reg_disable,
	.get_voltage_sel	= max8997_get_voltage_sel,
	.set_voltage_sel	= max8997_set_voltage_safeout_sel,
	.set_suspend_disable	= max8997_reg_disable_suspend,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max8997_fixedstate_ops = अणु
	.list_voltage		= max8997_list_voltage_अक्षरger_cv,
	.get_voltage_sel	= max8997_get_voltage_sel,
	.set_voltage		= max8997_set_voltage_अक्षरger_cv,
पूर्ण;

अटल पूर्णांक max8997_set_current_limit(काष्ठा regulator_dev *rdev,
				     पूर्णांक min_uA, पूर्णांक max_uA)
अणु
	अचिन्हित dummy;
	पूर्णांक rid = rdev_get_id(rdev);

	अगर (rid != MAX8997_CHARGER && rid != MAX8997_CHARGER_TOPOFF)
		वापस -EINVAL;

	/* Reuse max8997_set_voltage_lकरोbuck to set current_limit. */
	वापस max8997_set_voltage_lकरोbuck(rdev, min_uA, max_uA, &dummy);
पूर्ण

अटल पूर्णांक max8997_get_current_limit(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक sel, rid = rdev_get_id(rdev);

	अगर (rid != MAX8997_CHARGER && rid != MAX8997_CHARGER_TOPOFF)
		वापस -EINVAL;

	sel = max8997_get_voltage_sel(rdev);
	अगर (sel < 0)
		वापस sel;

	/* Reuse max8997_list_voltage to get current_limit. */
	वापस max8997_list_voltage(rdev, sel);
पूर्ण

अटल स्थिर काष्ठा regulator_ops max8997_अक्षरger_ops = अणु
	.is_enabled		= max8997_reg_is_enabled,
	.enable			= max8997_reg_enable,
	.disable		= max8997_reg_disable,
	.get_current_limit	= max8997_get_current_limit,
	.set_current_limit	= max8997_set_current_limit,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max8997_अक्षरger_fixedstate_ops = अणु
	.get_current_limit	= max8997_get_current_limit,
	.set_current_limit	= max8997_set_current_limit,
पूर्ण;

#घोषणा MAX8997_VOLTAGE_REGULATOR(_name, _ops) अणु\
	.name		= #_name,		\
	.id		= MAX8997_##_name,	\
	.ops		= &_ops,		\
	.type		= REGULATOR_VOLTAGE,	\
	.owner		= THIS_MODULE,		\
पूर्ण

#घोषणा MAX8997_CURRENT_REGULATOR(_name, _ops) अणु\
	.name		= #_name,		\
	.id		= MAX8997_##_name,	\
	.ops		= &_ops,		\
	.type		= REGULATOR_CURRENT,	\
	.owner		= THIS_MODULE,		\
पूर्ण

अटल काष्ठा regulator_desc regulators[] = अणु
	MAX8997_VOLTAGE_REGULATOR(LDO1, max8997_lकरो_ops),
	MAX8997_VOLTAGE_REGULATOR(LDO2, max8997_lकरो_ops),
	MAX8997_VOLTAGE_REGULATOR(LDO3, max8997_lकरो_ops),
	MAX8997_VOLTAGE_REGULATOR(LDO4, max8997_lकरो_ops),
	MAX8997_VOLTAGE_REGULATOR(LDO5, max8997_lकरो_ops),
	MAX8997_VOLTAGE_REGULATOR(LDO6, max8997_lकरो_ops),
	MAX8997_VOLTAGE_REGULATOR(LDO7, max8997_lकरो_ops),
	MAX8997_VOLTAGE_REGULATOR(LDO8, max8997_lकरो_ops),
	MAX8997_VOLTAGE_REGULATOR(LDO9, max8997_lकरो_ops),
	MAX8997_VOLTAGE_REGULATOR(LDO10, max8997_lकरो_ops),
	MAX8997_VOLTAGE_REGULATOR(LDO11, max8997_lकरो_ops),
	MAX8997_VOLTAGE_REGULATOR(LDO12, max8997_lकरो_ops),
	MAX8997_VOLTAGE_REGULATOR(LDO13, max8997_lकरो_ops),
	MAX8997_VOLTAGE_REGULATOR(LDO14, max8997_lकरो_ops),
	MAX8997_VOLTAGE_REGULATOR(LDO15, max8997_lकरो_ops),
	MAX8997_VOLTAGE_REGULATOR(LDO16, max8997_lकरो_ops),
	MAX8997_VOLTAGE_REGULATOR(LDO17, max8997_lकरो_ops),
	MAX8997_VOLTAGE_REGULATOR(LDO18, max8997_lकरो_ops),
	MAX8997_VOLTAGE_REGULATOR(LDO21, max8997_lकरो_ops),
	MAX8997_VOLTAGE_REGULATOR(BUCK1, max8997_buck_ops),
	MAX8997_VOLTAGE_REGULATOR(BUCK2, max8997_buck_ops),
	MAX8997_VOLTAGE_REGULATOR(BUCK3, max8997_buck_ops),
	MAX8997_VOLTAGE_REGULATOR(BUCK4, max8997_buck_ops),
	MAX8997_VOLTAGE_REGULATOR(BUCK5, max8997_buck_ops),
	MAX8997_VOLTAGE_REGULATOR(BUCK6, max8997_fixedvolt_ops),
	MAX8997_VOLTAGE_REGULATOR(BUCK7, max8997_buck_ops),
	MAX8997_VOLTAGE_REGULATOR(EN32KHZ_AP, max8997_fixedvolt_ops),
	MAX8997_VOLTAGE_REGULATOR(EN32KHZ_CP, max8997_fixedvolt_ops),
	MAX8997_VOLTAGE_REGULATOR(ENVICHG, max8997_fixedvolt_ops),
	MAX8997_VOLTAGE_REGULATOR(ESAFEOUT1, max8997_safeout_ops),
	MAX8997_VOLTAGE_REGULATOR(ESAFEOUT2, max8997_safeout_ops),
	MAX8997_VOLTAGE_REGULATOR(CHARGER_CV, max8997_fixedstate_ops),
	MAX8997_CURRENT_REGULATOR(CHARGER, max8997_अक्षरger_ops),
	MAX8997_CURRENT_REGULATOR(CHARGER_TOPOFF,
				  max8997_अक्षरger_fixedstate_ops),
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल पूर्णांक max8997_pmic_dt_parse_dvs_gpio(काष्ठा platक्रमm_device *pdev,
			काष्ठा max8997_platक्रमm_data *pdata,
			काष्ठा device_node *pmic_np)
अणु
	पूर्णांक i, gpio;

	क्रम (i = 0; i < 3; i++) अणु
		gpio = of_get_named_gpio(pmic_np,
					"max8997,pmic-buck125-dvs-gpios", i);
		अगर (!gpio_is_valid(gpio)) अणु
			dev_err(&pdev->dev, "invalid gpio[%d]: %d\n", i, gpio);
			वापस -EINVAL;
		पूर्ण
		pdata->buck125_gpios[i] = gpio;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक max8997_pmic_dt_parse_pdata(काष्ठा platक्रमm_device *pdev,
					काष्ठा max8997_platक्रमm_data *pdata)
अणु
	काष्ठा max8997_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device_node *pmic_np, *regulators_np, *reg_np;
	काष्ठा max8997_regulator_data *rdata;
	अचिन्हित पूर्णांक i, dvs_voltage_nr = 1, ret;

	pmic_np = iodev->dev->of_node;
	अगर (!pmic_np) अणु
		dev_err(&pdev->dev, "could not find pmic sub-node\n");
		वापस -ENODEV;
	पूर्ण

	regulators_np = of_get_child_by_name(pmic_np, "regulators");
	अगर (!regulators_np) अणु
		dev_err(&pdev->dev, "could not find regulators sub-node\n");
		वापस -EINVAL;
	पूर्ण

	/* count the number of regulators to be supported in pmic */
	pdata->num_regulators = of_get_child_count(regulators_np);

	rdata = devm_kसुस्मृति(&pdev->dev,
			     pdata->num_regulators, माप(*rdata),
			     GFP_KERNEL);
	अगर (!rdata) अणु
		of_node_put(regulators_np);
		वापस -ENOMEM;
	पूर्ण

	pdata->regulators = rdata;
	क्रम_each_child_of_node(regulators_np, reg_np) अणु
		क्रम (i = 0; i < ARRAY_SIZE(regulators); i++)
			अगर (of_node_name_eq(reg_np, regulators[i].name))
				अवरोध;

		अगर (i == ARRAY_SIZE(regulators)) अणु
			dev_warn(&pdev->dev, "don't know how to configure regulator %pOFn\n",
				 reg_np);
			जारी;
		पूर्ण

		rdata->id = i;
		rdata->initdata = of_get_regulator_init_data(&pdev->dev,
							     reg_np,
							     &regulators[i]);
		rdata->reg_node = reg_np;
		rdata++;
	पूर्ण
	of_node_put(regulators_np);

	अगर (of_get_property(pmic_np, "max8997,pmic-buck1-uses-gpio-dvs", शून्य))
		pdata->buck1_gpiodvs = true;

	अगर (of_get_property(pmic_np, "max8997,pmic-buck2-uses-gpio-dvs", शून्य))
		pdata->buck2_gpiodvs = true;

	अगर (of_get_property(pmic_np, "max8997,pmic-buck5-uses-gpio-dvs", शून्य))
		pdata->buck5_gpiodvs = true;

	अगर (pdata->buck1_gpiodvs || pdata->buck2_gpiodvs ||
						pdata->buck5_gpiodvs) अणु
		ret = max8997_pmic_dt_parse_dvs_gpio(pdev, pdata, pmic_np);
		अगर (ret)
			वापस -EINVAL;

		अगर (of_property_पढ़ो_u32(pmic_np,
				"max8997,pmic-buck125-default-dvs-idx",
				&pdata->buck125_शेष_idx)) अणु
			pdata->buck125_शेष_idx = 0;
		पूर्ण अन्यथा अणु
			अगर (pdata->buck125_शेष_idx >= 8) अणु
				pdata->buck125_शेष_idx = 0;
				dev_info(&pdev->dev, "invalid value for default dvs index, using 0 instead\n");
			पूर्ण
		पूर्ण

		अगर (of_get_property(pmic_np,
			"max8997,pmic-ignore-gpiodvs-side-effect", शून्य))
			pdata->ignore_gpiodvs_side_effect = true;

		dvs_voltage_nr = 8;
	पूर्ण

	अगर (of_property_पढ़ो_u32_array(pmic_np,
				"max8997,pmic-buck1-dvs-voltage",
				pdata->buck1_voltage, dvs_voltage_nr)) अणु
		dev_err(&pdev->dev, "buck1 voltages not specified\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32_array(pmic_np,
				"max8997,pmic-buck2-dvs-voltage",
				pdata->buck2_voltage, dvs_voltage_nr)) अणु
		dev_err(&pdev->dev, "buck2 voltages not specified\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32_array(pmic_np,
				"max8997,pmic-buck5-dvs-voltage",
				pdata->buck5_voltage, dvs_voltage_nr)) अणु
		dev_err(&pdev->dev, "buck5 voltages not specified\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक max8997_pmic_dt_parse_pdata(काष्ठा platक्रमm_device *pdev,
					काष्ठा max8997_platक्रमm_data *pdata)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

अटल पूर्णांक max8997_pmic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8997_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max8997_platक्रमm_data *pdata = iodev->pdata;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	काष्ठा max8997_data *max8997;
	काष्ठा i2c_client *i2c;
	पूर्णांक i, ret, nr_dvs;
	u8 max_buck1 = 0, max_buck2 = 0, max_buck5 = 0;

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "No platform init data supplied.\n");
		वापस -ENODEV;
	पूर्ण

	अगर (iodev->dev->of_node) अणु
		ret = max8997_pmic_dt_parse_pdata(pdev, pdata);
		अगर (ret)
			वापस ret;
	पूर्ण

	max8997 = devm_kzalloc(&pdev->dev, माप(काष्ठा max8997_data),
			       GFP_KERNEL);
	अगर (!max8997)
		वापस -ENOMEM;

	max8997->dev = &pdev->dev;
	max8997->iodev = iodev;
	max8997->num_regulators = pdata->num_regulators;
	platक्रमm_set_drvdata(pdev, max8997);
	i2c = max8997->iodev->i2c;

	max8997->buck125_gpioindex = pdata->buck125_शेष_idx;
	max8997->buck1_gpiodvs = pdata->buck1_gpiodvs;
	max8997->buck2_gpiodvs = pdata->buck2_gpiodvs;
	max8997->buck5_gpiodvs = pdata->buck5_gpiodvs;
	स_नकल(max8997->buck125_gpios, pdata->buck125_gpios, माप(पूर्णांक) * 3);
	max8997->ignore_gpiodvs_side_effect = pdata->ignore_gpiodvs_side_effect;

	nr_dvs = (pdata->buck1_gpiodvs || pdata->buck2_gpiodvs ||
			pdata->buck5_gpiodvs) ? 8 : 1;

	क्रम (i = 0; i < nr_dvs; i++) अणु
		max8997->buck1_vol[i] = ret =
			max8997_get_voltage_proper_val(
					&buck1245_voltage_map_desc,
					pdata->buck1_voltage[i],
					pdata->buck1_voltage[i] +
					buck1245_voltage_map_desc.step);
		अगर (ret < 0)
			वापस ret;

		max8997->buck2_vol[i] = ret =
			max8997_get_voltage_proper_val(
					&buck1245_voltage_map_desc,
					pdata->buck2_voltage[i],
					pdata->buck2_voltage[i] +
					buck1245_voltage_map_desc.step);
		अगर (ret < 0)
			वापस ret;

		max8997->buck5_vol[i] = ret =
			max8997_get_voltage_proper_val(
					&buck1245_voltage_map_desc,
					pdata->buck5_voltage[i],
					pdata->buck5_voltage[i] +
					buck1245_voltage_map_desc.step);
		अगर (ret < 0)
			वापस ret;

		अगर (max_buck1 < max8997->buck1_vol[i])
			max_buck1 = max8997->buck1_vol[i];
		अगर (max_buck2 < max8997->buck2_vol[i])
			max_buck2 = max8997->buck2_vol[i];
		अगर (max_buck5 < max8997->buck5_vol[i])
			max_buck5 = max8997->buck5_vol[i];
	पूर्ण

	/* For the safety, set max voltage beक्रमe setting up */
	क्रम (i = 0; i < 8; i++) अणु
		max8997_update_reg(i2c, MAX8997_REG_BUCK1DVS1 + i,
				max_buck1, 0x3f);
		max8997_update_reg(i2c, MAX8997_REG_BUCK2DVS1 + i,
				max_buck2, 0x3f);
		max8997_update_reg(i2c, MAX8997_REG_BUCK5DVS1 + i,
				max_buck5, 0x3f);
	पूर्ण

	/* Initialize all the DVS related BUCK रेजिस्टरs */
	क्रम (i = 0; i < nr_dvs; i++) अणु
		max8997_update_reg(i2c, MAX8997_REG_BUCK1DVS1 + i,
				max8997->buck1_vol[i],
				0x3f);
		max8997_update_reg(i2c, MAX8997_REG_BUCK2DVS1 + i,
				max8997->buck2_vol[i],
				0x3f);
		max8997_update_reg(i2c, MAX8997_REG_BUCK5DVS1 + i,
				max8997->buck5_vol[i],
				0x3f);
	पूर्ण

	/*
	 * If buck 1, 2, and 5 करो not care DVS GPIO settings, ignore them.
	 * If at least one of them cares, set gpios.
	 */
	अगर (pdata->buck1_gpiodvs || pdata->buck2_gpiodvs ||
			pdata->buck5_gpiodvs) अणु

		अगर (!gpio_is_valid(pdata->buck125_gpios[0]) ||
				!gpio_is_valid(pdata->buck125_gpios[1]) ||
				!gpio_is_valid(pdata->buck125_gpios[2])) अणु
			dev_err(&pdev->dev, "GPIO NOT VALID\n");
			वापस -EINVAL;
		पूर्ण

		ret = devm_gpio_request(&pdev->dev, pdata->buck125_gpios[0],
					"MAX8997 SET1");
		अगर (ret)
			वापस ret;

		ret = devm_gpio_request(&pdev->dev, pdata->buck125_gpios[1],
					"MAX8997 SET2");
		अगर (ret)
			वापस ret;

		ret = devm_gpio_request(&pdev->dev, pdata->buck125_gpios[2],
				"MAX8997 SET3");
		अगर (ret)
			वापस ret;

		gpio_direction_output(pdata->buck125_gpios[0],
				(max8997->buck125_gpioindex >> 2)
				& 0x1); /* SET1 */
		gpio_direction_output(pdata->buck125_gpios[1],
				(max8997->buck125_gpioindex >> 1)
				& 0x1); /* SET2 */
		gpio_direction_output(pdata->buck125_gpios[2],
				(max8997->buck125_gpioindex >> 0)
				& 0x1); /* SET3 */
	पूर्ण

	/* DVS-GPIO disabled */
	max8997_update_reg(i2c, MAX8997_REG_BUCK1CTRL, (pdata->buck1_gpiodvs) ?
			(1 << 1) : (0 << 1), 1 << 1);
	max8997_update_reg(i2c, MAX8997_REG_BUCK2CTRL, (pdata->buck2_gpiodvs) ?
			(1 << 1) : (0 << 1), 1 << 1);
	max8997_update_reg(i2c, MAX8997_REG_BUCK5CTRL, (pdata->buck5_gpiodvs) ?
			(1 << 1) : (0 << 1), 1 << 1);

	/* Misc Settings */
	max8997->ramp_delay = 10; /* set 10mV/us, which is the शेष */
	max8997_ग_लिखो_reg(i2c, MAX8997_REG_BUCKRAMP, (0xf << 4) | 0x9);

	क्रम (i = 0; i < pdata->num_regulators; i++) अणु
		स्थिर काष्ठा voltage_map_desc *desc;
		पूर्णांक id = pdata->regulators[i].id;

		desc = reg_voltage_map[id];
		अगर (desc) अणु
			regulators[id].n_voltages =
				(desc->max - desc->min) / desc->step + 1;
		पूर्ण अन्यथा अगर (id == MAX8997_ESAFEOUT1 || id == MAX8997_ESAFEOUT2) अणु
			regulators[id].volt_table = safeoutvolt;
			regulators[id].n_voltages = ARRAY_SIZE(safeoutvolt);
		पूर्ण अन्यथा अगर (id == MAX8997_CHARGER_CV) अणु
			regulators[id].n_voltages = 16;
		पूर्ण

		config.dev = max8997->dev;
		config.init_data = pdata->regulators[i].initdata;
		config.driver_data = max8997;
		config.of_node = pdata->regulators[i].reg_node;

		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &regulators[id],
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(max8997->dev, "regulator init failed for %d\n",
					id);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id max8997_pmic_id[] = अणु
	अणु "max8997-pmic", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max8997_pmic_id);

अटल काष्ठा platक्रमm_driver max8997_pmic_driver = अणु
	.driver = अणु
		.name = "max8997-pmic",
	पूर्ण,
	.probe = max8997_pmic_probe,
	.id_table = max8997_pmic_id,
पूर्ण;

अटल पूर्णांक __init max8997_pmic_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&max8997_pmic_driver);
पूर्ण
subsys_initcall(max8997_pmic_init);

अटल व्योम __निकास max8997_pmic_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&max8997_pmic_driver);
पूर्ण
module_निकास(max8997_pmic_cleanup);

MODULE_DESCRIPTION("MAXIM 8997/8966 Regulator Driver");
MODULE_AUTHOR("MyungJoo Ham <myungjoo.ham@samsung.com>");
MODULE_LICENSE("GPL");
