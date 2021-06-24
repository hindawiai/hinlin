<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// max8998.c - Voltage regulator driver क्रम the Maxim 8998
//
//  Copyright (C) 2009-2010 Samsung Electronics
//  Kyungmin Park <kyungmin.park@samsung.com>
//  Marek Szyprowski <m.szyprowski@samsung.com>

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/mfd/max8998.h>
#समावेश <linux/mfd/max8998-निजी.h>

काष्ठा max8998_data अणु
	काष्ठा device		*dev;
	काष्ठा max8998_dev	*iodev;
	पूर्णांक			num_regulators;
	u8                      buck1_vol[4]; /* voltages क्रम selection */
	u8                      buck2_vol[2];
	अचिन्हित पूर्णांक		buck1_idx; /* index to last changed voltage */
					   /* value in a set */
	अचिन्हित पूर्णांक		buck2_idx;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक अक्षरger_current_table[] = अणु
	90000, 380000, 475000, 550000, 570000, 600000, 700000, 800000,
पूर्ण;

अटल पूर्णांक max8998_get_enable_रेजिस्टर(काष्ठा regulator_dev *rdev,
					पूर्णांक *reg, पूर्णांक *shअगरt)
अणु
	पूर्णांक lकरो = rdev_get_id(rdev);

	चयन (lकरो) अणु
	हाल MAX8998_LDO2 ... MAX8998_LDO5:
		*reg = MAX8998_REG_ONOFF1;
		*shअगरt = 3 - (lकरो - MAX8998_LDO2);
		अवरोध;
	हाल MAX8998_LDO6 ... MAX8998_LDO13:
		*reg = MAX8998_REG_ONOFF2;
		*shअगरt = 7 - (lकरो - MAX8998_LDO6);
		अवरोध;
	हाल MAX8998_LDO14 ... MAX8998_LDO17:
		*reg = MAX8998_REG_ONOFF3;
		*shअगरt = 7 - (lकरो - MAX8998_LDO14);
		अवरोध;
	हाल MAX8998_BUCK1 ... MAX8998_BUCK4:
		*reg = MAX8998_REG_ONOFF1;
		*shअगरt = 7 - (lकरो - MAX8998_BUCK1);
		अवरोध;
	हाल MAX8998_EN32KHZ_AP ... MAX8998_ENVICHG:
		*reg = MAX8998_REG_ONOFF4;
		*shअगरt = 7 - (lकरो - MAX8998_EN32KHZ_AP);
		अवरोध;
	हाल MAX8998_ESAFEOUT1 ... MAX8998_ESAFEOUT2:
		*reg = MAX8998_REG_CHGR2;
		*shअगरt = 7 - (lकरो - MAX8998_ESAFEOUT1);
		अवरोध;
	हाल MAX8998_CHARGER:
		*reg = MAX8998_REG_CHGR2;
		*shअगरt = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max8998_lकरो_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8998_data *max8998 = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *i2c = max8998->iodev->i2c;
	पूर्णांक ret, reg, shअगरt = 8;
	u8 val;

	ret = max8998_get_enable_रेजिस्टर(rdev, &reg, &shअगरt);
	अगर (ret)
		वापस ret;

	ret = max8998_पढ़ो_reg(i2c, reg, &val);
	अगर (ret)
		वापस ret;

	वापस val & (1 << shअगरt);
पूर्ण

अटल पूर्णांक max8998_lकरो_is_enabled_inverted(काष्ठा regulator_dev *rdev)
अणु
	वापस (!max8998_lकरो_is_enabled(rdev));
पूर्ण

अटल पूर्णांक max8998_lकरो_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8998_data *max8998 = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *i2c = max8998->iodev->i2c;
	पूर्णांक reg, shअगरt = 8, ret;

	ret = max8998_get_enable_रेजिस्टर(rdev, &reg, &shअगरt);
	अगर (ret)
		वापस ret;

	वापस max8998_update_reg(i2c, reg, 1<<shअगरt, 1<<shअगरt);
पूर्ण

अटल पूर्णांक max8998_lकरो_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8998_data *max8998 = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *i2c = max8998->iodev->i2c;
	पूर्णांक reg, shअगरt = 8, ret;

	ret = max8998_get_enable_रेजिस्टर(rdev, &reg, &shअगरt);
	अगर (ret)
		वापस ret;

	वापस max8998_update_reg(i2c, reg, 0, 1<<shअगरt);
पूर्ण

अटल पूर्णांक max8998_get_voltage_रेजिस्टर(काष्ठा regulator_dev *rdev,
				पूर्णांक *_reg, पूर्णांक *_shअगरt, पूर्णांक *_mask)
अणु
	पूर्णांक lकरो = rdev_get_id(rdev);
	काष्ठा max8998_data *max8998 = rdev_get_drvdata(rdev);
	पूर्णांक reg, shअगरt = 0, mask = 0xff;

	चयन (lकरो) अणु
	हाल MAX8998_LDO2 ... MAX8998_LDO3:
		reg = MAX8998_REG_LDO2_LDO3;
		mask = 0xf;
		अगर (lकरो == MAX8998_LDO2)
			shअगरt = 4;
		अन्यथा
			shअगरt = 0;
		अवरोध;
	हाल MAX8998_LDO4 ... MAX8998_LDO7:
		reg = MAX8998_REG_LDO4 + (lकरो - MAX8998_LDO4);
		अवरोध;
	हाल MAX8998_LDO8 ... MAX8998_LDO9:
		reg = MAX8998_REG_LDO8_LDO9;
		mask = 0xf;
		अगर (lकरो == MAX8998_LDO8)
			shअगरt = 4;
		अन्यथा
			shअगरt = 0;
		अवरोध;
	हाल MAX8998_LDO10 ... MAX8998_LDO11:
		reg = MAX8998_REG_LDO10_LDO11;
		अगर (lकरो == MAX8998_LDO10) अणु
			shअगरt = 5;
			mask = 0x7;
		पूर्ण अन्यथा अणु
			shअगरt = 0;
			mask = 0x1f;
		पूर्ण
		अवरोध;
	हाल MAX8998_LDO12 ... MAX8998_LDO17:
		reg = MAX8998_REG_LDO12 + (lकरो - MAX8998_LDO12);
		अवरोध;
	हाल MAX8998_BUCK1:
		reg = MAX8998_REG_BUCK1_VOLTAGE1 + max8998->buck1_idx;
		अवरोध;
	हाल MAX8998_BUCK2:
		reg = MAX8998_REG_BUCK2_VOLTAGE1 + max8998->buck2_idx;
		अवरोध;
	हाल MAX8998_BUCK3:
		reg = MAX8998_REG_BUCK3;
		अवरोध;
	हाल MAX8998_BUCK4:
		reg = MAX8998_REG_BUCK4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*_reg = reg;
	*_shअगरt = shअगरt;
	*_mask = mask;

	वापस 0;
पूर्ण

अटल पूर्णांक max8998_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8998_data *max8998 = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *i2c = max8998->iodev->i2c;
	पूर्णांक reg, shअगरt = 0, mask, ret;
	u8 val;

	ret = max8998_get_voltage_रेजिस्टर(rdev, &reg, &shअगरt, &mask);
	अगर (ret)
		वापस ret;

	ret = max8998_पढ़ो_reg(i2c, reg, &val);
	अगर (ret)
		वापस ret;

	val >>= shअगरt;
	val &= mask;

	वापस val;
पूर्ण

अटल पूर्णांक max8998_set_voltage_lकरो_sel(काष्ठा regulator_dev *rdev,
				       अचिन्हित selector)
अणु
	काष्ठा max8998_data *max8998 = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *i2c = max8998->iodev->i2c;
	पूर्णांक reg, shअगरt = 0, mask, ret;

	ret = max8998_get_voltage_रेजिस्टर(rdev, &reg, &shअगरt, &mask);
	अगर (ret)
		वापस ret;

	ret = max8998_update_reg(i2c, reg, selector<<shअगरt, mask<<shअगरt);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम buck1_gpio_set(पूर्णांक gpio1, पूर्णांक gpio2, पूर्णांक v)
अणु
	gpio_set_value(gpio1, v & 0x1);
	gpio_set_value(gpio2, (v >> 1) & 0x1);
पूर्ण

अटल अंतरभूत व्योम buck2_gpio_set(पूर्णांक gpio, पूर्णांक v)
अणु
	gpio_set_value(gpio, v & 0x1);
पूर्ण

अटल पूर्णांक max8998_set_voltage_buck_sel(काष्ठा regulator_dev *rdev,
					अचिन्हित selector)
अणु
	काष्ठा max8998_data *max8998 = rdev_get_drvdata(rdev);
	काष्ठा max8998_platक्रमm_data *pdata = max8998->iodev->pdata;
	काष्ठा i2c_client *i2c = max8998->iodev->i2c;
	पूर्णांक buck = rdev_get_id(rdev);
	पूर्णांक reg, shअगरt = 0, mask, ret, j;
	अटल u8 buck1_last_val;

	ret = max8998_get_voltage_रेजिस्टर(rdev, &reg, &shअगरt, &mask);
	अगर (ret)
		वापस ret;

	चयन (buck) अणु
	हाल MAX8998_BUCK1:
		dev_dbg(max8998->dev,
			"BUCK1, selector:%d, buck1_vol1:%d, buck1_vol2:%d\n"
			"buck1_vol3:%d, buck1_vol4:%d\n",
			selector, max8998->buck1_vol[0], max8998->buck1_vol[1],
			max8998->buck1_vol[2], max8998->buck1_vol[3]);

		अगर (gpio_is_valid(pdata->buck1_set1) &&
		    gpio_is_valid(pdata->buck1_set2)) अणु

			/* check अगर requested voltage */
			/* value is alपढ़ोy defined */
			क्रम (j = 0; j < ARRAY_SIZE(max8998->buck1_vol); j++) अणु
				अगर (max8998->buck1_vol[j] == selector) अणु
					max8998->buck1_idx = j;
					buck1_gpio_set(pdata->buck1_set1,
						       pdata->buck1_set2, j);
					जाओ buck1_निकास;
				पूर्ण
			पूर्ण

			अगर (pdata->buck_voltage_lock)
				वापस -EINVAL;

			/* no predefine regulator found */
			max8998->buck1_idx = (buck1_last_val % 2) + 2;
			dev_dbg(max8998->dev, "max8998->buck1_idx:%d\n",
				max8998->buck1_idx);
			max8998->buck1_vol[max8998->buck1_idx] = selector;
			ret = max8998_get_voltage_रेजिस्टर(rdev, &reg,
							   &shअगरt,
							   &mask);
			ret = max8998_ग_लिखो_reg(i2c, reg, selector);
			buck1_gpio_set(pdata->buck1_set1,
				       pdata->buck1_set2, max8998->buck1_idx);
			buck1_last_val++;
buck1_निकास:
			dev_dbg(max8998->dev, "%s: SET1:%d, SET2:%d\n",
				i2c->name, gpio_get_value(pdata->buck1_set1),
				gpio_get_value(pdata->buck1_set2));
			अवरोध;
		पूर्ण अन्यथा अणु
			ret = max8998_ग_लिखो_reg(i2c, reg, selector);
		पूर्ण
		अवरोध;

	हाल MAX8998_BUCK2:
		dev_dbg(max8998->dev,
			"BUCK2, selector:%d buck2_vol1:%d, buck2_vol2:%d\n",
			selector, max8998->buck2_vol[0], max8998->buck2_vol[1]);
		अगर (gpio_is_valid(pdata->buck2_set3)) अणु

			/* check अगर requested voltage */
			/* value is alपढ़ोy defined */
			क्रम (j = 0; j < ARRAY_SIZE(max8998->buck2_vol); j++) अणु
				अगर (max8998->buck2_vol[j] == selector) अणु
					max8998->buck2_idx = j;
					buck2_gpio_set(pdata->buck2_set3, j);
					जाओ buck2_निकास;
				पूर्ण
			पूर्ण

			अगर (pdata->buck_voltage_lock)
				वापस -EINVAL;

			max8998_get_voltage_रेजिस्टर(rdev,
					&reg, &shअगरt, &mask);
			ret = max8998_ग_लिखो_reg(i2c, reg, selector);
			max8998->buck2_vol[max8998->buck2_idx] = selector;
			buck2_gpio_set(pdata->buck2_set3, max8998->buck2_idx);
buck2_निकास:
			dev_dbg(max8998->dev, "%s: SET3:%d\n", i2c->name,
				gpio_get_value(pdata->buck2_set3));
		पूर्ण अन्यथा अणु
			ret = max8998_ग_लिखो_reg(i2c, reg, selector);
		पूर्ण
		अवरोध;

	हाल MAX8998_BUCK3:
	हाल MAX8998_BUCK4:
		ret = max8998_update_reg(i2c, reg, selector<<shअगरt,
					 mask<<shअगरt);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक max8998_set_voltage_buck_समय_sel(काष्ठा regulator_dev *rdev,
					     अचिन्हित पूर्णांक old_selector,
					     अचिन्हित पूर्णांक new_selector)
अणु
	काष्ठा max8998_data *max8998 = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *i2c = max8998->iodev->i2c;
	पूर्णांक buck = rdev_get_id(rdev);
	u8 val = 0;
	पूर्णांक dअगरference, ret;

	अगर (buck < MAX8998_BUCK1 || buck > MAX8998_BUCK4)
		वापस -EINVAL;

	/* Voltage stabilization */
	ret = max8998_पढ़ो_reg(i2c, MAX8998_REG_ONOFF4, &val);
	अगर (ret)
		वापस ret;

	/* lp3974 hasn't got ENRAMP bit - ramp is assumed as true */
	/* MAX8998 has ENRAMP bit implemented, so test it*/
	अगर (max8998->iodev->type == TYPE_MAX8998 && !(val & MAX8998_ENRAMP))
		वापस 0;

	dअगरference = (new_selector - old_selector) * rdev->desc->uV_step / 1000;
	अगर (dअगरference > 0)
		वापस DIV_ROUND_UP(dअगरference, (val & 0x0f) + 1);

	वापस 0;
पूर्ण

अटल पूर्णांक max8998_set_current_limit(काष्ठा regulator_dev *rdev,
				     पूर्णांक min_uA, पूर्णांक max_uA)
अणु
	काष्ठा max8998_data *max8998 = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *i2c = max8998->iodev->i2c;
	अचिन्हित पूर्णांक n_currents = rdev->desc->n_current_limits;
	पूर्णांक i, sel = -1;

	अगर (n_currents == 0)
		वापस -EINVAL;

	अगर (rdev->desc->curr_table) अणु
		स्थिर अचिन्हित पूर्णांक *curr_table = rdev->desc->curr_table;
		bool ascend = curr_table[n_currents - 1] > curr_table[0];

		/* search क्रम बंदst to maximum */
		अगर (ascend) अणु
			क्रम (i = n_currents - 1; i >= 0; i--) अणु
				अगर (min_uA <= curr_table[i] &&
				    curr_table[i] <= max_uA) अणु
					sel = i;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < n_currents; i++) अणु
				अगर (min_uA <= curr_table[i] &&
				    curr_table[i] <= max_uA) अणु
					sel = i;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (sel < 0)
		वापस -EINVAL;

	sel <<= ffs(rdev->desc->csel_mask) - 1;

	वापस max8998_update_reg(i2c, rdev->desc->csel_reg,
				  sel, rdev->desc->csel_mask);
पूर्ण

अटल पूर्णांक max8998_get_current_limit(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8998_data *max8998 = rdev_get_drvdata(rdev);
	काष्ठा i2c_client *i2c = max8998->iodev->i2c;
	u8 val;
	पूर्णांक ret;

	ret = max8998_पढ़ो_reg(i2c, rdev->desc->csel_reg, &val);
	अगर (ret != 0)
		वापस ret;

	val &= rdev->desc->csel_mask;
	val >>= ffs(rdev->desc->csel_mask) - 1;

	अगर (rdev->desc->curr_table) अणु
		अगर (val >= rdev->desc->n_current_limits)
			वापस -EINVAL;

		वापस rdev->desc->curr_table[val];
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा regulator_ops max8998_lकरो_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.is_enabled		= max8998_lकरो_is_enabled,
	.enable			= max8998_lकरो_enable,
	.disable		= max8998_lकरो_disable,
	.get_voltage_sel	= max8998_get_voltage_sel,
	.set_voltage_sel	= max8998_set_voltage_lकरो_sel,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max8998_buck_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.is_enabled		= max8998_lकरो_is_enabled,
	.enable			= max8998_lकरो_enable,
	.disable		= max8998_lकरो_disable,
	.get_voltage_sel	= max8998_get_voltage_sel,
	.set_voltage_sel	= max8998_set_voltage_buck_sel,
	.set_voltage_समय_sel	= max8998_set_voltage_buck_समय_sel,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max8998_अक्षरger_ops = अणु
	.set_current_limit	= max8998_set_current_limit,
	.get_current_limit	= max8998_get_current_limit,
	.is_enabled		= max8998_lकरो_is_enabled_inverted,
	/* Swapped as रेजिस्टर is inverted */
	.enable			= max8998_lकरो_disable,
	.disable		= max8998_lकरो_enable,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max8998_others_ops = अणु
	.is_enabled		= max8998_lकरो_is_enabled,
	.enable			= max8998_lकरो_enable,
	.disable		= max8998_lकरो_disable,
पूर्ण;

#घोषणा MAX8998_LINEAR_REG(_name, _ops, _min, _step, _max) \
	अणु \
		.name = #_name, \
		.id = MAX8998_##_name, \
		.ops = _ops, \
		.min_uV = (_min), \
		.uV_step = (_step), \
		.n_voltages = ((_max) - (_min)) / (_step) + 1, \
		.type = REGULATOR_VOLTAGE, \
		.owner = THIS_MODULE, \
	पूर्ण

#घोषणा MAX8998_CURRENT_REG(_name, _ops, _table, _reg, _mask) \
	अणु \
		.name = #_name, \
		.id = MAX8998_##_name, \
		.ops = _ops, \
		.curr_table = _table, \
		.n_current_limits = ARRAY_SIZE(_table), \
		.csel_reg = _reg, \
		.csel_mask = _mask, \
		.type = REGULATOR_CURRENT, \
		.owner = THIS_MODULE, \
	पूर्ण

#घोषणा MAX8998_OTHERS_REG(_name, _id) \
	अणु \
		.name = #_name, \
		.id = _id, \
		.ops = &max8998_others_ops, \
		.type = REGULATOR_VOLTAGE, \
		.owner = THIS_MODULE, \
	पूर्ण

अटल स्थिर काष्ठा regulator_desc regulators[] = अणु
	MAX8998_LINEAR_REG(LDO2, &max8998_lकरो_ops, 800000, 50000, 1300000),
	MAX8998_LINEAR_REG(LDO3, &max8998_lकरो_ops, 800000, 50000, 1300000),
	MAX8998_LINEAR_REG(LDO4, &max8998_lकरो_ops, 1600000, 100000, 3600000),
	MAX8998_LINEAR_REG(LDO5, &max8998_lकरो_ops, 1600000, 100000, 3600000),
	MAX8998_LINEAR_REG(LDO6, &max8998_lकरो_ops, 1600000, 100000, 3600000),
	MAX8998_LINEAR_REG(LDO7, &max8998_lकरो_ops, 1600000, 100000, 3600000),
	MAX8998_LINEAR_REG(LDO8, &max8998_lकरो_ops, 3000000, 100000, 3600000),
	MAX8998_LINEAR_REG(LDO9, &max8998_lकरो_ops, 2800000, 100000, 3100000),
	MAX8998_LINEAR_REG(LDO10, &max8998_lकरो_ops, 950000, 50000, 1300000),
	MAX8998_LINEAR_REG(LDO11, &max8998_lकरो_ops, 1600000, 100000, 3600000),
	MAX8998_LINEAR_REG(LDO12, &max8998_lकरो_ops, 800000, 100000, 3300000),
	MAX8998_LINEAR_REG(LDO13, &max8998_lकरो_ops, 800000, 100000, 3300000),
	MAX8998_LINEAR_REG(LDO14, &max8998_lकरो_ops, 1200000, 100000, 3300000),
	MAX8998_LINEAR_REG(LDO15, &max8998_lकरो_ops, 1200000, 100000, 3300000),
	MAX8998_LINEAR_REG(LDO16, &max8998_lकरो_ops, 1600000, 100000, 3600000),
	MAX8998_LINEAR_REG(LDO17, &max8998_lकरो_ops, 1600000, 100000, 3600000),
	MAX8998_LINEAR_REG(BUCK1, &max8998_buck_ops, 750000, 25000, 1525000),
	MAX8998_LINEAR_REG(BUCK2, &max8998_buck_ops, 750000, 25000, 1525000),
	MAX8998_LINEAR_REG(BUCK3, &max8998_buck_ops, 1600000, 100000, 3600000),
	MAX8998_LINEAR_REG(BUCK4, &max8998_buck_ops, 800000, 100000, 2300000),
	MAX8998_OTHERS_REG(EN32KHz-AP, MAX8998_EN32KHZ_AP),
	MAX8998_OTHERS_REG(EN32KHz-CP, MAX8998_EN32KHZ_CP),
	MAX8998_OTHERS_REG(ENVICHG, MAX8998_ENVICHG),
	MAX8998_OTHERS_REG(ESAFEOUT1, MAX8998_ESAFEOUT1),
	MAX8998_OTHERS_REG(ESAFEOUT2, MAX8998_ESAFEOUT2),
	MAX8998_CURRENT_REG(CHARGER, &max8998_अक्षरger_ops,
			    अक्षरger_current_table, MAX8998_REG_CHGR1, 0x7),
पूर्ण;

अटल पूर्णांक max8998_pmic_dt_parse_dvs_gpio(काष्ठा max8998_dev *iodev,
			काष्ठा max8998_platक्रमm_data *pdata,
			काष्ठा device_node *pmic_np)
अणु
	पूर्णांक gpio;

	gpio = of_get_named_gpio(pmic_np, "max8998,pmic-buck1-dvs-gpios", 0);
	अगर (!gpio_is_valid(gpio)) अणु
		dev_err(iodev->dev, "invalid buck1 gpio[0]: %d\n", gpio);
		वापस -EINVAL;
	पूर्ण
	pdata->buck1_set1 = gpio;

	gpio = of_get_named_gpio(pmic_np, "max8998,pmic-buck1-dvs-gpios", 1);
	अगर (!gpio_is_valid(gpio)) अणु
		dev_err(iodev->dev, "invalid buck1 gpio[1]: %d\n", gpio);
		वापस -EINVAL;
	पूर्ण
	pdata->buck1_set2 = gpio;

	gpio = of_get_named_gpio(pmic_np, "max8998,pmic-buck2-dvs-gpio", 0);
	अगर (!gpio_is_valid(gpio)) अणु
		dev_err(iodev->dev, "invalid buck 2 gpio: %d\n", gpio);
		वापस -EINVAL;
	पूर्ण
	pdata->buck2_set3 = gpio;

	वापस 0;
पूर्ण

अटल पूर्णांक max8998_pmic_dt_parse_pdata(काष्ठा max8998_dev *iodev,
					काष्ठा max8998_platक्रमm_data *pdata)
अणु
	काष्ठा device_node *pmic_np = iodev->dev->of_node;
	काष्ठा device_node *regulators_np, *reg_np;
	काष्ठा max8998_regulator_data *rdata;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	regulators_np = of_get_child_by_name(pmic_np, "regulators");
	अगर (!regulators_np) अणु
		dev_err(iodev->dev, "could not find regulators sub-node\n");
		वापस -EINVAL;
	पूर्ण

	/* count the number of regulators to be supported in pmic */
	pdata->num_regulators = of_get_child_count(regulators_np);

	rdata = devm_kसुस्मृति(iodev->dev,
			     pdata->num_regulators, माप(*rdata),
			     GFP_KERNEL);
	अगर (!rdata) अणु
		of_node_put(regulators_np);
		वापस -ENOMEM;
	पूर्ण

	pdata->regulators = rdata;
	क्रम (i = 0; i < ARRAY_SIZE(regulators); ++i) अणु
		reg_np = of_get_child_by_name(regulators_np,
							regulators[i].name);
		अगर (!reg_np)
			जारी;

		rdata->id = regulators[i].id;
		rdata->initdata = of_get_regulator_init_data(iodev->dev,
							     reg_np,
							     &regulators[i]);
		rdata->reg_node = reg_np;
		++rdata;
	पूर्ण
	pdata->num_regulators = rdata - pdata->regulators;

	of_node_put(reg_np);
	of_node_put(regulators_np);

	ret = max8998_pmic_dt_parse_dvs_gpio(iodev, pdata, pmic_np);
	अगर (ret)
		वापस -EINVAL;

	अगर (of_find_property(pmic_np, "max8998,pmic-buck-voltage-lock", शून्य))
		pdata->buck_voltage_lock = true;

	ret = of_property_पढ़ो_u32(pmic_np,
					"max8998,pmic-buck1-default-dvs-idx",
					&pdata->buck1_शेष_idx);
	अगर (!ret && pdata->buck1_शेष_idx >= 4) अणु
		pdata->buck1_शेष_idx = 0;
		dev_warn(iodev->dev, "invalid value for default dvs index, using 0 instead\n");
	पूर्ण

	ret = of_property_पढ़ो_u32(pmic_np,
					"max8998,pmic-buck2-default-dvs-idx",
					&pdata->buck2_शेष_idx);
	अगर (!ret && pdata->buck2_शेष_idx >= 2) अणु
		pdata->buck2_शेष_idx = 0;
		dev_warn(iodev->dev, "invalid value for default dvs index, using 0 instead\n");
	पूर्ण

	ret = of_property_पढ़ो_u32_array(pmic_np,
					"max8998,pmic-buck1-dvs-voltage",
					pdata->buck1_voltage,
					ARRAY_SIZE(pdata->buck1_voltage));
	अगर (ret) अणु
		dev_err(iodev->dev, "buck1 voltages not specified\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32_array(pmic_np,
					"max8998,pmic-buck2-dvs-voltage",
					pdata->buck2_voltage,
					ARRAY_SIZE(pdata->buck2_voltage));
	अगर (ret) अणु
		dev_err(iodev->dev, "buck2 voltages not specified\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max8998_pmic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max8998_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max8998_platक्रमm_data *pdata = iodev->pdata;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	काष्ठा max8998_data *max8998;
	काष्ठा i2c_client *i2c;
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक v;

	अगर (!pdata) अणु
		dev_err(pdev->dev.parent, "No platform init data supplied\n");
		वापस -ENODEV;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_OF) && iodev->dev->of_node) अणु
		ret = max8998_pmic_dt_parse_pdata(iodev, pdata);
		अगर (ret)
			वापस ret;
	पूर्ण

	max8998 = devm_kzalloc(&pdev->dev, माप(काष्ठा max8998_data),
			       GFP_KERNEL);
	अगर (!max8998)
		वापस -ENOMEM;

	max8998->dev = &pdev->dev;
	max8998->iodev = iodev;
	max8998->num_regulators = pdata->num_regulators;
	platक्रमm_set_drvdata(pdev, max8998);
	i2c = max8998->iodev->i2c;

	max8998->buck1_idx = pdata->buck1_शेष_idx;
	max8998->buck2_idx = pdata->buck2_शेष_idx;

	/* NOTE: */
	/* For unused GPIO NOT marked as -1 (thereof equal to 0)  WARN_ON */
	/* will be displayed */

	/* Check अगर MAX8998 voltage selection GPIOs are defined */
	अगर (gpio_is_valid(pdata->buck1_set1) &&
	    gpio_is_valid(pdata->buck1_set2)) अणु
		/* Check अगर SET1 is not equal to 0 */
		अगर (!pdata->buck1_set1) अणु
			dev_err(&pdev->dev,
				"MAX8998 SET1 GPIO defined as 0 !\n");
			WARN_ON(!pdata->buck1_set1);
			वापस -EIO;
		पूर्ण
		/* Check अगर SET2 is not equal to 0 */
		अगर (!pdata->buck1_set2) अणु
			dev_err(&pdev->dev,
				"MAX8998 SET2 GPIO defined as 0 !\n");
			WARN_ON(!pdata->buck1_set2);
			वापस -EIO;
		पूर्ण

		gpio_request(pdata->buck1_set1, "MAX8998 BUCK1_SET1");
		gpio_direction_output(pdata->buck1_set1,
				      max8998->buck1_idx & 0x1);


		gpio_request(pdata->buck1_set2, "MAX8998 BUCK1_SET2");
		gpio_direction_output(pdata->buck1_set2,
				      (max8998->buck1_idx >> 1) & 0x1);

		/* Set predefined values क्रम BUCK1 रेजिस्टरs */
		क्रम (v = 0; v < ARRAY_SIZE(pdata->buck1_voltage); ++v) अणु
			पूर्णांक index = MAX8998_BUCK1 - MAX8998_LDO2;

			i = 0;
			जबतक (regulators[index].min_uV +
			       regulators[index].uV_step * i
			       < pdata->buck1_voltage[v])
				i++;

			max8998->buck1_vol[v] = i;
			ret = max8998_ग_लिखो_reg(i2c,
					MAX8998_REG_BUCK1_VOLTAGE1 + v, i);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	अगर (gpio_is_valid(pdata->buck2_set3)) अणु
		/* Check अगर SET3 is not equal to 0 */
		अगर (!pdata->buck2_set3) अणु
			dev_err(&pdev->dev,
				"MAX8998 SET3 GPIO defined as 0 !\n");
			WARN_ON(!pdata->buck2_set3);
			वापस -EIO;
		पूर्ण
		gpio_request(pdata->buck2_set3, "MAX8998 BUCK2_SET3");
		gpio_direction_output(pdata->buck2_set3,
				      max8998->buck2_idx & 0x1);

		/* Set predefined values क्रम BUCK2 रेजिस्टरs */
		क्रम (v = 0; v < ARRAY_SIZE(pdata->buck2_voltage); ++v) अणु
			पूर्णांक index = MAX8998_BUCK2 - MAX8998_LDO2;

			i = 0;
			जबतक (regulators[index].min_uV +
			       regulators[index].uV_step * i
			       < pdata->buck2_voltage[v])
				i++;

			max8998->buck2_vol[v] = i;
			ret = max8998_ग_लिखो_reg(i2c,
					MAX8998_REG_BUCK2_VOLTAGE1 + v, i);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pdata->num_regulators; i++) अणु
		पूर्णांक index = pdata->regulators[i].id - MAX8998_LDO2;

		config.dev = max8998->dev;
		config.of_node = pdata->regulators[i].reg_node;
		config.init_data = pdata->regulators[i].initdata;
		config.driver_data = max8998;

		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &regulators[index],
					       &config);
		अगर (IS_ERR(rdev)) अणु
			ret = PTR_ERR(rdev);
			dev_err(max8998->dev, "regulator %s init failed (%d)\n",
						regulators[index].name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id max8998_pmic_id[] = अणु
	अणु "max8998-pmic", TYPE_MAX8998 पूर्ण,
	अणु "lp3974-pmic", TYPE_LP3974 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max8998_pmic_id);

अटल काष्ठा platक्रमm_driver max8998_pmic_driver = अणु
	.driver = अणु
		.name = "max8998-pmic",
	पूर्ण,
	.probe = max8998_pmic_probe,
	.id_table = max8998_pmic_id,
पूर्ण;

अटल पूर्णांक __init max8998_pmic_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&max8998_pmic_driver);
पूर्ण
subsys_initcall(max8998_pmic_init);

अटल व्योम __निकास max8998_pmic_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&max8998_pmic_driver);
पूर्ण
module_निकास(max8998_pmic_cleanup);

MODULE_DESCRIPTION("MAXIM 8998 voltage regulator driver");
MODULE_AUTHOR("Kyungmin Park <kyungmin.park@samsung.com>");
MODULE_LICENSE("GPL");
