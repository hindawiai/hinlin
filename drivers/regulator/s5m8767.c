<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (c) 2011 Samsung Electronics Co., Ltd
//              http://www.samsung.com

#समावेश <linux/err.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/mfd/samsung/core.h>
#समावेश <linux/mfd/samsung/s5m8767.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/regmap.h>

#घोषणा S5M8767_OPMODE_NORMAL_MODE 0x1

काष्ठा s5m8767_info अणु
	काष्ठा device *dev;
	काष्ठा sec_pmic_dev *iodev;
	पूर्णांक num_regulators;
	काष्ठा sec_opmode_data *opmode;

	पूर्णांक ramp_delay;
	bool buck2_ramp;
	bool buck3_ramp;
	bool buck4_ramp;

	bool buck2_gpiodvs;
	bool buck3_gpiodvs;
	bool buck4_gpiodvs;
	u8 buck2_vol[8];
	u8 buck3_vol[8];
	u8 buck4_vol[8];
	पूर्णांक buck_gpios[3];
	पूर्णांक buck_ds[3];
	पूर्णांक buck_gpioindex;
पूर्ण;

काष्ठा sec_voltage_desc अणु
	पूर्णांक max;
	पूर्णांक min;
	पूर्णांक step;
पूर्ण;

अटल स्थिर काष्ठा sec_voltage_desc buck_voltage_val1 = अणु
	.max = 2225000,
	.min =  650000,
	.step =   6250,
पूर्ण;

अटल स्थिर काष्ठा sec_voltage_desc buck_voltage_val2 = अणु
	.max = 1600000,
	.min =  600000,
	.step =   6250,
पूर्ण;

अटल स्थिर काष्ठा sec_voltage_desc buck_voltage_val3 = अणु
	.max = 3000000,
	.min =  750000,
	.step =  12500,
पूर्ण;

अटल स्थिर काष्ठा sec_voltage_desc lकरो_voltage_val1 = अणु
	.max = 3950000,
	.min =  800000,
	.step =  50000,
पूर्ण;

अटल स्थिर काष्ठा sec_voltage_desc lकरो_voltage_val2 = अणु
	.max = 2375000,
	.min =  800000,
	.step =  25000,
पूर्ण;

अटल स्थिर काष्ठा sec_voltage_desc *reg_voltage_map[] = अणु
	[S5M8767_LDO1] = &lकरो_voltage_val2,
	[S5M8767_LDO2] = &lकरो_voltage_val2,
	[S5M8767_LDO3] = &lकरो_voltage_val1,
	[S5M8767_LDO4] = &lकरो_voltage_val1,
	[S5M8767_LDO5] = &lकरो_voltage_val1,
	[S5M8767_LDO6] = &lकरो_voltage_val2,
	[S5M8767_LDO7] = &lकरो_voltage_val2,
	[S5M8767_LDO8] = &lकरो_voltage_val2,
	[S5M8767_LDO9] = &lकरो_voltage_val1,
	[S5M8767_LDO10] = &lकरो_voltage_val1,
	[S5M8767_LDO11] = &lकरो_voltage_val1,
	[S5M8767_LDO12] = &lकरो_voltage_val1,
	[S5M8767_LDO13] = &lकरो_voltage_val1,
	[S5M8767_LDO14] = &lकरो_voltage_val1,
	[S5M8767_LDO15] = &lकरो_voltage_val2,
	[S5M8767_LDO16] = &lकरो_voltage_val1,
	[S5M8767_LDO17] = &lकरो_voltage_val1,
	[S5M8767_LDO18] = &lकरो_voltage_val1,
	[S5M8767_LDO19] = &lकरो_voltage_val1,
	[S5M8767_LDO20] = &lकरो_voltage_val1,
	[S5M8767_LDO21] = &lकरो_voltage_val1,
	[S5M8767_LDO22] = &lकरो_voltage_val1,
	[S5M8767_LDO23] = &lकरो_voltage_val1,
	[S5M8767_LDO24] = &lकरो_voltage_val1,
	[S5M8767_LDO25] = &lकरो_voltage_val1,
	[S5M8767_LDO26] = &lकरो_voltage_val1,
	[S5M8767_LDO27] = &lकरो_voltage_val1,
	[S5M8767_LDO28] = &lकरो_voltage_val1,
	[S5M8767_BUCK1] = &buck_voltage_val1,
	[S5M8767_BUCK2] = &buck_voltage_val2,
	[S5M8767_BUCK3] = &buck_voltage_val2,
	[S5M8767_BUCK4] = &buck_voltage_val2,
	[S5M8767_BUCK5] = &buck_voltage_val1,
	[S5M8767_BUCK6] = &buck_voltage_val1,
	[S5M8767_BUCK7] = &buck_voltage_val3,
	[S5M8767_BUCK8] = &buck_voltage_val3,
	[S5M8767_BUCK9] = &buck_voltage_val3,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक s5m8767_opmode_reg[][4] = अणु
	/* अणुOFF, ON, LOWPOWER, SUSPENDपूर्ण */
	/* LDO1 ... LDO28 */
	अणु0x0, 0x3, 0x2, 0x1पूर्ण, /* LDO1 */
	अणु0x0, 0x3, 0x2, 0x1पूर्ण,
	अणु0x0, 0x3, 0x2, 0x1पूर्ण,
	अणु0x0, 0x0, 0x0, 0x0पूर्ण,
	अणु0x0, 0x3, 0x2, 0x1पूर्ण, /* LDO5 */
	अणु0x0, 0x3, 0x2, 0x1पूर्ण,
	अणु0x0, 0x3, 0x2, 0x1पूर्ण,
	अणु0x0, 0x3, 0x2, 0x1पूर्ण,
	अणु0x0, 0x3, 0x2, 0x1पूर्ण,
	अणु0x0, 0x3, 0x2, 0x1पूर्ण, /* LDO10 */
	अणु0x0, 0x3, 0x2, 0x1पूर्ण,
	अणु0x0, 0x3, 0x2, 0x1पूर्ण,
	अणु0x0, 0x3, 0x2, 0x1पूर्ण,
	अणु0x0, 0x3, 0x2, 0x1पूर्ण,
	अणु0x0, 0x3, 0x2, 0x1पूर्ण, /* LDO15 */
	अणु0x0, 0x3, 0x2, 0x1पूर्ण,
	अणु0x0, 0x3, 0x2, 0x1पूर्ण,
	अणु0x0, 0x0, 0x0, 0x0पूर्ण,
	अणु0x0, 0x3, 0x2, 0x1पूर्ण,
	अणु0x0, 0x3, 0x2, 0x1पूर्ण, /* LDO20 */
	अणु0x0, 0x3, 0x2, 0x1पूर्ण,
	अणु0x0, 0x3, 0x2, 0x1पूर्ण,
	अणु0x0, 0x0, 0x0, 0x0पूर्ण,
	अणु0x0, 0x3, 0x2, 0x1पूर्ण,
	अणु0x0, 0x3, 0x2, 0x1पूर्ण, /* LDO25 */
	अणु0x0, 0x3, 0x2, 0x1पूर्ण,
	अणु0x0, 0x3, 0x2, 0x1पूर्ण,
	अणु0x0, 0x3, 0x2, 0x1पूर्ण, /* LDO28 */

	/* BUCK1 ... BUCK9 */
	अणु0x0, 0x3, 0x1, 0x1पूर्ण, /* BUCK1 */
	अणु0x0, 0x3, 0x1, 0x1पूर्ण,
	अणु0x0, 0x3, 0x1, 0x1पूर्ण,
	अणु0x0, 0x3, 0x1, 0x1पूर्ण,
	अणु0x0, 0x3, 0x2, 0x1पूर्ण, /* BUCK5 */
	अणु0x0, 0x3, 0x1, 0x1पूर्ण,
	अणु0x0, 0x3, 0x1, 0x1पूर्ण,
	अणु0x0, 0x3, 0x1, 0x1पूर्ण,
	अणु0x0, 0x3, 0x1, 0x1पूर्ण, /* BUCK9 */
पूर्ण;

अटल पूर्णांक s5m8767_get_रेजिस्टर(काष्ठा s5m8767_info *s5m8767, पूर्णांक reg_id,
				पूर्णांक *reg, पूर्णांक *enable_ctrl)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक mode;

	चयन (reg_id) अणु
	हाल S5M8767_LDO1 ... S5M8767_LDO2:
		*reg = S5M8767_REG_LDO1CTRL + (reg_id - S5M8767_LDO1);
		अवरोध;
	हाल S5M8767_LDO3 ... S5M8767_LDO28:
		*reg = S5M8767_REG_LDO3CTRL + (reg_id - S5M8767_LDO3);
		अवरोध;
	हाल S5M8767_BUCK1:
		*reg = S5M8767_REG_BUCK1CTRL1;
		अवरोध;
	हाल S5M8767_BUCK2 ... S5M8767_BUCK4:
		*reg = S5M8767_REG_BUCK2CTRL + (reg_id - S5M8767_BUCK2) * 9;
		अवरोध;
	हाल S5M8767_BUCK5:
		*reg = S5M8767_REG_BUCK5CTRL1;
		अवरोध;
	हाल S5M8767_BUCK6 ... S5M8767_BUCK9:
		*reg = S5M8767_REG_BUCK6CTRL1 + (reg_id - S5M8767_BUCK6) * 2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < s5m8767->num_regulators; i++) अणु
		अगर (s5m8767->opmode[i].id == reg_id) अणु
			mode = s5m8767->opmode[i].mode;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i >= s5m8767->num_regulators)
		वापस -EINVAL;

	*enable_ctrl = s5m8767_opmode_reg[reg_id][mode] << S5M8767_ENCTRL_SHIFT;

	वापस 0;
पूर्ण

अटल पूर्णांक s5m8767_get_vsel_reg(पूर्णांक reg_id, काष्ठा s5m8767_info *s5m8767)
अणु
	पूर्णांक reg;

	चयन (reg_id) अणु
	हाल S5M8767_LDO1 ... S5M8767_LDO2:
		reg = S5M8767_REG_LDO1CTRL + (reg_id - S5M8767_LDO1);
		अवरोध;
	हाल S5M8767_LDO3 ... S5M8767_LDO28:
		reg = S5M8767_REG_LDO3CTRL + (reg_id - S5M8767_LDO3);
		अवरोध;
	हाल S5M8767_BUCK1:
		reg = S5M8767_REG_BUCK1CTRL2;
		अवरोध;
	हाल S5M8767_BUCK2:
		reg = S5M8767_REG_BUCK2DVS1;
		अगर (s5m8767->buck2_gpiodvs)
			reg += s5m8767->buck_gpioindex;
		अवरोध;
	हाल S5M8767_BUCK3:
		reg = S5M8767_REG_BUCK3DVS1;
		अगर (s5m8767->buck3_gpiodvs)
			reg += s5m8767->buck_gpioindex;
		अवरोध;
	हाल S5M8767_BUCK4:
		reg = S5M8767_REG_BUCK4DVS1;
		अगर (s5m8767->buck4_gpiodvs)
			reg += s5m8767->buck_gpioindex;
		अवरोध;
	हाल S5M8767_BUCK5:
		reg = S5M8767_REG_BUCK5CTRL2;
		अवरोध;
	हाल S5M8767_BUCK6 ... S5M8767_BUCK9:
		reg = S5M8767_REG_BUCK6CTRL2 + (reg_id - S5M8767_BUCK6) * 2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस reg;
पूर्ण

अटल पूर्णांक s5m8767_convert_voltage_to_sel(स्थिर काष्ठा sec_voltage_desc *desc,
					  पूर्णांक min_vol)
अणु
	पूर्णांक selector = 0;

	अगर (desc == शून्य)
		वापस -EINVAL;

	अगर (min_vol > desc->max)
		वापस -EINVAL;

	अगर (min_vol < desc->min)
		min_vol = desc->min;

	selector = DIV_ROUND_UP(min_vol - desc->min, desc->step);

	अगर (desc->min + desc->step * selector > desc->max)
		वापस -EINVAL;

	वापस selector;
पूर्ण

अटल अंतरभूत पूर्णांक s5m8767_set_high(काष्ठा s5m8767_info *s5m8767)
अणु
	पूर्णांक temp_index = s5m8767->buck_gpioindex;

	gpio_set_value(s5m8767->buck_gpios[0], (temp_index >> 2) & 0x1);
	gpio_set_value(s5m8767->buck_gpios[1], (temp_index >> 1) & 0x1);
	gpio_set_value(s5m8767->buck_gpios[2], temp_index & 0x1);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक s5m8767_set_low(काष्ठा s5m8767_info *s5m8767)
अणु
	पूर्णांक temp_index = s5m8767->buck_gpioindex;

	gpio_set_value(s5m8767->buck_gpios[2], temp_index & 0x1);
	gpio_set_value(s5m8767->buck_gpios[1], (temp_index >> 1) & 0x1);
	gpio_set_value(s5m8767->buck_gpios[0], (temp_index >> 2) & 0x1);

	वापस 0;
पूर्ण

अटल पूर्णांक s5m8767_set_voltage_sel(काष्ठा regulator_dev *rdev,
				   अचिन्हित selector)
अणु
	काष्ठा s5m8767_info *s5m8767 = rdev_get_drvdata(rdev);
	पूर्णांक reg_id = rdev_get_id(rdev);
	पूर्णांक old_index, index = 0;
	u8 *buck234_vol = शून्य;

	चयन (reg_id) अणु
	हाल S5M8767_LDO1 ... S5M8767_LDO28:
		अवरोध;
	हाल S5M8767_BUCK1 ... S5M8767_BUCK6:
		अगर (reg_id == S5M8767_BUCK2 && s5m8767->buck2_gpiodvs)
			buck234_vol = &s5m8767->buck2_vol[0];
		अन्यथा अगर (reg_id == S5M8767_BUCK3 && s5m8767->buck3_gpiodvs)
			buck234_vol = &s5m8767->buck3_vol[0];
		अन्यथा अगर (reg_id == S5M8767_BUCK4 && s5m8767->buck4_gpiodvs)
			buck234_vol = &s5m8767->buck4_vol[0];
		अवरोध;
	हाल S5M8767_BUCK7 ... S5M8767_BUCK8:
		वापस -EINVAL;
	हाल S5M8767_BUCK9:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* buck234_vol != शून्य means to control buck234 voltage via DVS GPIO */
	अगर (buck234_vol) अणु
		जबतक (*buck234_vol != selector) अणु
			buck234_vol++;
			index++;
		पूर्ण
		old_index = s5m8767->buck_gpioindex;
		s5m8767->buck_gpioindex = index;

		अगर (index > old_index)
			वापस s5m8767_set_high(s5m8767);
		अन्यथा
			वापस s5m8767_set_low(s5m8767);
	पूर्ण अन्यथा अणु
		वापस regulator_set_voltage_sel_regmap(rdev, selector);
	पूर्ण
पूर्ण

अटल पूर्णांक s5m8767_set_voltage_समय_sel(काष्ठा regulator_dev *rdev,
					     अचिन्हित पूर्णांक old_sel,
					     अचिन्हित पूर्णांक new_sel)
अणु
	काष्ठा s5m8767_info *s5m8767 = rdev_get_drvdata(rdev);

	अगर ((old_sel < new_sel) && s5m8767->ramp_delay)
		वापस DIV_ROUND_UP(rdev->desc->uV_step * (new_sel - old_sel),
					s5m8767->ramp_delay * 1000);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regulator_ops s5m8767_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= s5m8767_set_voltage_sel,
	.set_voltage_समय_sel	= s5m8767_set_voltage_समय_sel,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops s5m8767_buck78_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
पूर्ण;

#घोषणा s5m8767_regulator_desc(_name) अणु		\
	.name		= #_name,		\
	.id		= S5M8767_##_name,	\
	.ops		= &s5m8767_ops,		\
	.type		= REGULATOR_VOLTAGE,	\
	.owner		= THIS_MODULE,		\
पूर्ण

#घोषणा s5m8767_regulator_buck78_desc(_name) अणु	\
	.name		= #_name,		\
	.id		= S5M8767_##_name,	\
	.ops		= &s5m8767_buck78_ops,	\
	.type		= REGULATOR_VOLTAGE,	\
	.owner		= THIS_MODULE,		\
पूर्ण

अटल काष्ठा regulator_desc regulators[] = अणु
	s5m8767_regulator_desc(LDO1),
	s5m8767_regulator_desc(LDO2),
	s5m8767_regulator_desc(LDO3),
	s5m8767_regulator_desc(LDO4),
	s5m8767_regulator_desc(LDO5),
	s5m8767_regulator_desc(LDO6),
	s5m8767_regulator_desc(LDO7),
	s5m8767_regulator_desc(LDO8),
	s5m8767_regulator_desc(LDO9),
	s5m8767_regulator_desc(LDO10),
	s5m8767_regulator_desc(LDO11),
	s5m8767_regulator_desc(LDO12),
	s5m8767_regulator_desc(LDO13),
	s5m8767_regulator_desc(LDO14),
	s5m8767_regulator_desc(LDO15),
	s5m8767_regulator_desc(LDO16),
	s5m8767_regulator_desc(LDO17),
	s5m8767_regulator_desc(LDO18),
	s5m8767_regulator_desc(LDO19),
	s5m8767_regulator_desc(LDO20),
	s5m8767_regulator_desc(LDO21),
	s5m8767_regulator_desc(LDO22),
	s5m8767_regulator_desc(LDO23),
	s5m8767_regulator_desc(LDO24),
	s5m8767_regulator_desc(LDO25),
	s5m8767_regulator_desc(LDO26),
	s5m8767_regulator_desc(LDO27),
	s5m8767_regulator_desc(LDO28),
	s5m8767_regulator_desc(BUCK1),
	s5m8767_regulator_desc(BUCK2),
	s5m8767_regulator_desc(BUCK3),
	s5m8767_regulator_desc(BUCK4),
	s5m8767_regulator_desc(BUCK5),
	s5m8767_regulator_desc(BUCK6),
	s5m8767_regulator_buck78_desc(BUCK7),
	s5m8767_regulator_buck78_desc(BUCK8),
	s5m8767_regulator_desc(BUCK9),
पूर्ण;

/*
 * Enable GPIO control over BUCK9 in regulator_config क्रम that regulator.
 */
अटल व्योम s5m8767_regulator_config_ext_control(काष्ठा s5m8767_info *s5m8767,
		काष्ठा sec_regulator_data *rdata,
		काष्ठा regulator_config *config)
अणु
	पूर्णांक i, mode = 0;

	अगर (rdata->id != S5M8767_BUCK9)
		वापस;

	/* Check अगर opmode क्रम regulator matches S5M8767_ENCTRL_USE_GPIO */
	क्रम (i = 0; i < s5m8767->num_regulators; i++) अणु
		स्थिर काष्ठा sec_opmode_data *opmode = &s5m8767->opmode[i];
		अगर (opmode->id == rdata->id) अणु
			mode = s5m8767_opmode_reg[rdata->id][opmode->mode];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (mode != S5M8767_ENCTRL_USE_GPIO) अणु
		dev_warn(s5m8767->dev,
				"ext-control for %pOFn: mismatched op_mode (%x), ignoring\n",
				rdata->reg_node, mode);
		वापस;
	पूर्ण

	अगर (!rdata->ext_control_gpiod) अणु
		dev_warn(s5m8767->dev,
				"ext-control for %pOFn: GPIO not valid, ignoring\n",
			 rdata->reg_node);
		वापस;
	पूर्ण

	config->ena_gpiod = rdata->ext_control_gpiod;
पूर्ण

/*
 * Turn on GPIO control over BUCK9.
 */
अटल पूर्णांक s5m8767_enable_ext_control(काष्ठा s5m8767_info *s5m8767,
		काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक id = rdev_get_id(rdev);
	पूर्णांक ret, reg, enable_ctrl;

	अगर (id != S5M8767_BUCK9)
		वापस -EINVAL;

	ret = s5m8767_get_रेजिस्टर(s5m8767, id, &reg, &enable_ctrl);
	अगर (ret)
		वापस ret;

	वापस regmap_update_bits(s5m8767->iodev->regmap_pmic,
			reg, S5M8767_ENCTRL_MASK,
			S5M8767_ENCTRL_USE_GPIO << S5M8767_ENCTRL_SHIFT);
पूर्ण


#अगर_घोषित CONFIG_OF
अटल पूर्णांक s5m8767_pmic_dt_parse_dvs_gpio(काष्ठा sec_pmic_dev *iodev,
			काष्ठा sec_platक्रमm_data *pdata,
			काष्ठा device_node *pmic_np)
अणु
	पूर्णांक i, gpio;

	क्रम (i = 0; i < 3; i++) अणु
		gpio = of_get_named_gpio(pmic_np,
					"s5m8767,pmic-buck-dvs-gpios", i);
		अगर (!gpio_is_valid(gpio)) अणु
			dev_err(iodev->dev, "invalid gpio[%d]: %d\n", i, gpio);
			वापस -EINVAL;
		पूर्ण
		pdata->buck_gpios[i] = gpio;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक s5m8767_pmic_dt_parse_ds_gpio(काष्ठा sec_pmic_dev *iodev,
			काष्ठा sec_platक्रमm_data *pdata,
			काष्ठा device_node *pmic_np)
अणु
	पूर्णांक i, gpio;

	क्रम (i = 0; i < 3; i++) अणु
		gpio = of_get_named_gpio(pmic_np,
					"s5m8767,pmic-buck-ds-gpios", i);
		अगर (!gpio_is_valid(gpio)) अणु
			dev_err(iodev->dev, "invalid gpio[%d]: %d\n", i, gpio);
			वापस -EINVAL;
		पूर्ण
		pdata->buck_ds[i] = gpio;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक s5m8767_pmic_dt_parse_pdata(काष्ठा platक्रमm_device *pdev,
					काष्ठा sec_platक्रमm_data *pdata)
अणु
	काष्ठा sec_pmic_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device_node *pmic_np, *regulators_np, *reg_np;
	काष्ठा sec_regulator_data *rdata;
	काष्ठा sec_opmode_data *rmode;
	अचिन्हित पूर्णांक i, dvs_voltage_nr = 8, ret;

	pmic_np = iodev->dev->of_node;
	अगर (!pmic_np) अणु
		dev_err(iodev->dev, "could not find pmic sub-node\n");
		वापस -ENODEV;
	पूर्ण

	regulators_np = of_get_child_by_name(pmic_np, "regulators");
	अगर (!regulators_np) अणु
		dev_err(iodev->dev, "could not find regulators sub-node\n");
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

	rmode = devm_kसुस्मृति(&pdev->dev,
			     pdata->num_regulators, माप(*rmode),
			     GFP_KERNEL);
	अगर (!rmode) अणु
		of_node_put(regulators_np);
		वापस -ENOMEM;
	पूर्ण

	pdata->regulators = rdata;
	pdata->opmode = rmode;
	क्रम_each_child_of_node(regulators_np, reg_np) अणु
		क्रम (i = 0; i < ARRAY_SIZE(regulators); i++)
			अगर (of_node_name_eq(reg_np, regulators[i].name))
				अवरोध;

		अगर (i == ARRAY_SIZE(regulators)) अणु
			dev_warn(iodev->dev,
			"don't know how to configure regulator %pOFn\n",
			reg_np);
			जारी;
		पूर्ण

		rdata->ext_control_gpiod = devm_fwnode_gpiod_get(
			&pdev->dev,
			of_fwnode_handle(reg_np),
			"s5m8767,pmic-ext-control",
			GPIOD_OUT_HIGH | GPIOD_FLAGS_BIT_NONEXCLUSIVE,
			"s5m8767");
		अगर (PTR_ERR(rdata->ext_control_gpiod) == -ENOENT) अणु
			rdata->ext_control_gpiod = शून्य;
		पूर्ण अन्यथा अगर (IS_ERR(rdata->ext_control_gpiod)) अणु
			of_node_put(reg_np);
			of_node_put(regulators_np);
			वापस PTR_ERR(rdata->ext_control_gpiod);
		पूर्ण

		rdata->id = i;
		rdata->initdata = of_get_regulator_init_data(
						&pdev->dev, reg_np,
						&regulators[i]);
		rdata->reg_node = reg_np;
		rdata++;
		rmode->id = i;
		अगर (of_property_पढ़ो_u32(reg_np, "op_mode",
				&rmode->mode)) अणु
			dev_warn(iodev->dev,
				"no op_mode property at %pOF\n",
				reg_np);

			rmode->mode = S5M8767_OPMODE_NORMAL_MODE;
		पूर्ण
		rmode++;
	पूर्ण

	of_node_put(regulators_np);

	अगर (of_get_property(pmic_np, "s5m8767,pmic-buck2-uses-gpio-dvs", शून्य)) अणु
		pdata->buck2_gpiodvs = true;

		अगर (of_property_पढ़ो_u32_array(pmic_np,
				"s5m8767,pmic-buck2-dvs-voltage",
				pdata->buck2_voltage, dvs_voltage_nr)) अणु
			dev_err(iodev->dev, "buck2 voltages not specified\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (of_get_property(pmic_np, "s5m8767,pmic-buck3-uses-gpio-dvs", शून्य)) अणु
		pdata->buck3_gpiodvs = true;

		अगर (of_property_पढ़ो_u32_array(pmic_np,
				"s5m8767,pmic-buck3-dvs-voltage",
				pdata->buck3_voltage, dvs_voltage_nr)) अणु
			dev_err(iodev->dev, "buck3 voltages not specified\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (of_get_property(pmic_np, "s5m8767,pmic-buck4-uses-gpio-dvs", शून्य)) अणु
		pdata->buck4_gpiodvs = true;

		अगर (of_property_पढ़ो_u32_array(pmic_np,
				"s5m8767,pmic-buck4-dvs-voltage",
				pdata->buck4_voltage, dvs_voltage_nr)) अणु
			dev_err(iodev->dev, "buck4 voltages not specified\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (pdata->buck2_gpiodvs || pdata->buck3_gpiodvs ||
						pdata->buck4_gpiodvs) अणु
		ret = s5m8767_pmic_dt_parse_dvs_gpio(iodev, pdata, pmic_np);
		अगर (ret)
			वापस -EINVAL;

		अगर (of_property_पढ़ो_u32(pmic_np,
				"s5m8767,pmic-buck-default-dvs-idx",
				&pdata->buck_शेष_idx)) अणु
			pdata->buck_शेष_idx = 0;
		पूर्ण अन्यथा अणु
			अगर (pdata->buck_शेष_idx >= 8) अणु
				pdata->buck_शेष_idx = 0;
				dev_info(iodev->dev,
				"invalid value for default dvs index, use 0\n");
			पूर्ण
		पूर्ण
	पूर्ण

	ret = s5m8767_pmic_dt_parse_ds_gpio(iodev, pdata, pmic_np);
	अगर (ret)
		वापस -EINVAL;

	अगर (of_get_property(pmic_np, "s5m8767,pmic-buck2-ramp-enable", शून्य))
		pdata->buck2_ramp_enable = true;

	अगर (of_get_property(pmic_np, "s5m8767,pmic-buck3-ramp-enable", शून्य))
		pdata->buck3_ramp_enable = true;

	अगर (of_get_property(pmic_np, "s5m8767,pmic-buck4-ramp-enable", शून्य))
		pdata->buck4_ramp_enable = true;

	अगर (pdata->buck2_ramp_enable || pdata->buck3_ramp_enable
			|| pdata->buck4_ramp_enable) अणु
		अगर (of_property_पढ़ो_u32(pmic_np, "s5m8767,pmic-buck-ramp-delay",
				&pdata->buck_ramp_delay))
			pdata->buck_ramp_delay = 0;
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक s5m8767_pmic_dt_parse_pdata(काष्ठा platक्रमm_device *pdev,
					काष्ठा sec_platक्रमm_data *pdata)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

अटल पूर्णांक s5m8767_pmic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sec_pmic_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा sec_platक्रमm_data *pdata = iodev->pdata;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा s5m8767_info *s5m8767;
	पूर्णांक i, ret, buck_init;

	अगर (!pdata) अणु
		dev_err(pdev->dev.parent, "Platform data not supplied\n");
		वापस -ENODEV;
	पूर्ण

	अगर (iodev->dev->of_node) अणु
		ret = s5m8767_pmic_dt_parse_pdata(pdev, pdata);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (pdata->buck2_gpiodvs) अणु
		अगर (pdata->buck3_gpiodvs || pdata->buck4_gpiodvs) अणु
			dev_err(&pdev->dev, "S5M8767 GPIO DVS NOT VALID\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (pdata->buck3_gpiodvs) अणु
		अगर (pdata->buck2_gpiodvs || pdata->buck4_gpiodvs) अणु
			dev_err(&pdev->dev, "S5M8767 GPIO DVS NOT VALID\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (pdata->buck4_gpiodvs) अणु
		अगर (pdata->buck2_gpiodvs || pdata->buck3_gpiodvs) अणु
			dev_err(&pdev->dev, "S5M8767 GPIO DVS NOT VALID\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	s5m8767 = devm_kzalloc(&pdev->dev, माप(काष्ठा s5m8767_info),
				GFP_KERNEL);
	अगर (!s5m8767)
		वापस -ENOMEM;

	s5m8767->dev = &pdev->dev;
	s5m8767->iodev = iodev;
	s5m8767->num_regulators = pdata->num_regulators;
	platक्रमm_set_drvdata(pdev, s5m8767);

	s5m8767->buck_gpioindex = pdata->buck_शेष_idx;
	s5m8767->buck2_gpiodvs = pdata->buck2_gpiodvs;
	s5m8767->buck3_gpiodvs = pdata->buck3_gpiodvs;
	s5m8767->buck4_gpiodvs = pdata->buck4_gpiodvs;
	s5m8767->buck_gpios[0] = pdata->buck_gpios[0];
	s5m8767->buck_gpios[1] = pdata->buck_gpios[1];
	s5m8767->buck_gpios[2] = pdata->buck_gpios[2];
	s5m8767->buck_ds[0] = pdata->buck_ds[0];
	s5m8767->buck_ds[1] = pdata->buck_ds[1];
	s5m8767->buck_ds[2] = pdata->buck_ds[2];

	s5m8767->ramp_delay = pdata->buck_ramp_delay;
	s5m8767->buck2_ramp = pdata->buck2_ramp_enable;
	s5m8767->buck3_ramp = pdata->buck3_ramp_enable;
	s5m8767->buck4_ramp = pdata->buck4_ramp_enable;
	s5m8767->opmode = pdata->opmode;

	buck_init = s5m8767_convert_voltage_to_sel(&buck_voltage_val2,
						   pdata->buck2_init);

	regmap_ग_लिखो(s5m8767->iodev->regmap_pmic, S5M8767_REG_BUCK2DVS2,
			buck_init);

	buck_init = s5m8767_convert_voltage_to_sel(&buck_voltage_val2,
						   pdata->buck3_init);

	regmap_ग_लिखो(s5m8767->iodev->regmap_pmic, S5M8767_REG_BUCK3DVS2,
			buck_init);

	buck_init = s5m8767_convert_voltage_to_sel(&buck_voltage_val2,
						   pdata->buck4_init);

	regmap_ग_लिखो(s5m8767->iodev->regmap_pmic, S5M8767_REG_BUCK4DVS2,
			buck_init);

	क्रम (i = 0; i < 8; i++) अणु
		अगर (s5m8767->buck2_gpiodvs) अणु
			s5m8767->buck2_vol[i] =
				s5m8767_convert_voltage_to_sel(
						&buck_voltage_val2,
						pdata->buck2_voltage[i]);
		पूर्ण

		अगर (s5m8767->buck3_gpiodvs) अणु
			s5m8767->buck3_vol[i] =
				s5m8767_convert_voltage_to_sel(
						&buck_voltage_val2,
						pdata->buck3_voltage[i]);
		पूर्ण

		अगर (s5m8767->buck4_gpiodvs) अणु
			s5m8767->buck4_vol[i] =
				s5m8767_convert_voltage_to_sel(
						&buck_voltage_val2,
						pdata->buck4_voltage[i]);
		पूर्ण
	पूर्ण

	अगर (pdata->buck2_gpiodvs || pdata->buck3_gpiodvs ||
						pdata->buck4_gpiodvs) अणु

		अगर (!gpio_is_valid(pdata->buck_gpios[0]) ||
			!gpio_is_valid(pdata->buck_gpios[1]) ||
			!gpio_is_valid(pdata->buck_gpios[2])) अणु
			dev_err(&pdev->dev, "GPIO NOT VALID\n");
			वापस -EINVAL;
		पूर्ण

		ret = devm_gpio_request(&pdev->dev, pdata->buck_gpios[0],
					"S5M8767 SET1");
		अगर (ret)
			वापस ret;

		ret = devm_gpio_request(&pdev->dev, pdata->buck_gpios[1],
					"S5M8767 SET2");
		अगर (ret)
			वापस ret;

		ret = devm_gpio_request(&pdev->dev, pdata->buck_gpios[2],
					"S5M8767 SET3");
		अगर (ret)
			वापस ret;

		/* SET1 GPIO */
		gpio_direction_output(pdata->buck_gpios[0],
				(s5m8767->buck_gpioindex >> 2) & 0x1);
		/* SET2 GPIO */
		gpio_direction_output(pdata->buck_gpios[1],
				(s5m8767->buck_gpioindex >> 1) & 0x1);
		/* SET3 GPIO */
		gpio_direction_output(pdata->buck_gpios[2],
				(s5m8767->buck_gpioindex >> 0) & 0x1);
	पूर्ण

	ret = devm_gpio_request(&pdev->dev, pdata->buck_ds[0], "S5M8767 DS2");
	अगर (ret)
		वापस ret;

	ret = devm_gpio_request(&pdev->dev, pdata->buck_ds[1], "S5M8767 DS3");
	अगर (ret)
		वापस ret;

	ret = devm_gpio_request(&pdev->dev, pdata->buck_ds[2], "S5M8767 DS4");
	अगर (ret)
		वापस ret;

	/* DS2 GPIO */
	gpio_direction_output(pdata->buck_ds[0], 0x0);
	/* DS3 GPIO */
	gpio_direction_output(pdata->buck_ds[1], 0x0);
	/* DS4 GPIO */
	gpio_direction_output(pdata->buck_ds[2], 0x0);

	अगर (pdata->buck2_gpiodvs || pdata->buck3_gpiodvs ||
	   pdata->buck4_gpiodvs) अणु
		regmap_update_bits(s5m8767->iodev->regmap_pmic,
				S5M8767_REG_BUCK2CTRL, 1 << 1,
				(pdata->buck2_gpiodvs) ? (1 << 1) : (0 << 1));
		regmap_update_bits(s5m8767->iodev->regmap_pmic,
				S5M8767_REG_BUCK3CTRL, 1 << 1,
				(pdata->buck3_gpiodvs) ? (1 << 1) : (0 << 1));
		regmap_update_bits(s5m8767->iodev->regmap_pmic,
				S5M8767_REG_BUCK4CTRL, 1 << 1,
				(pdata->buck4_gpiodvs) ? (1 << 1) : (0 << 1));
	पूर्ण

	/* Initialize GPIO DVS रेजिस्टरs */
	क्रम (i = 0; i < 8; i++) अणु
		अगर (s5m8767->buck2_gpiodvs) अणु
			regmap_ग_लिखो(s5m8767->iodev->regmap_pmic,
					S5M8767_REG_BUCK2DVS1 + i,
					s5m8767->buck2_vol[i]);
		पूर्ण

		अगर (s5m8767->buck3_gpiodvs) अणु
			regmap_ग_लिखो(s5m8767->iodev->regmap_pmic,
					S5M8767_REG_BUCK3DVS1 + i,
					s5m8767->buck3_vol[i]);
		पूर्ण

		अगर (s5m8767->buck4_gpiodvs) अणु
			regmap_ग_लिखो(s5m8767->iodev->regmap_pmic,
					S5M8767_REG_BUCK4DVS1 + i,
					s5m8767->buck4_vol[i]);
		पूर्ण
	पूर्ण

	अगर (s5m8767->buck2_ramp)
		regmap_update_bits(s5m8767->iodev->regmap_pmic,
				S5M8767_REG_DVSRAMP, 0x08, 0x08);

	अगर (s5m8767->buck3_ramp)
		regmap_update_bits(s5m8767->iodev->regmap_pmic,
				S5M8767_REG_DVSRAMP, 0x04, 0x04);

	अगर (s5m8767->buck4_ramp)
		regmap_update_bits(s5m8767->iodev->regmap_pmic,
				S5M8767_REG_DVSRAMP, 0x02, 0x02);

	अगर (s5m8767->buck2_ramp || s5m8767->buck3_ramp
		|| s5m8767->buck4_ramp) अणु
		अचिन्हित पूर्णांक val;
		चयन (s5m8767->ramp_delay) अणु
		हाल 5:
			val = S5M8767_DVS_BUCK_RAMP_5;
			अवरोध;
		हाल 10:
			val = S5M8767_DVS_BUCK_RAMP_10;
			अवरोध;
		हाल 25:
			val = S5M8767_DVS_BUCK_RAMP_25;
			अवरोध;
		हाल 50:
			val = S5M8767_DVS_BUCK_RAMP_50;
			अवरोध;
		हाल 100:
			val = S5M8767_DVS_BUCK_RAMP_100;
			अवरोध;
		शेष:
			val = S5M8767_DVS_BUCK_RAMP_10;
		पूर्ण
		regmap_update_bits(s5m8767->iodev->regmap_pmic,
					S5M8767_REG_DVSRAMP,
					S5M8767_DVS_BUCK_RAMP_MASK,
					val << S5M8767_DVS_BUCK_RAMP_SHIFT);
	पूर्ण

	क्रम (i = 0; i < pdata->num_regulators; i++) अणु
		स्थिर काष्ठा sec_voltage_desc *desc;
		पूर्णांक id = pdata->regulators[i].id;
		पूर्णांक enable_reg, enable_val;
		काष्ठा regulator_dev *rdev;

		desc = reg_voltage_map[id];
		अगर (desc) अणु
			regulators[id].n_voltages =
				(desc->max - desc->min) / desc->step + 1;
			regulators[id].min_uV = desc->min;
			regulators[id].uV_step = desc->step;
			regulators[id].vsel_reg =
				s5m8767_get_vsel_reg(id, s5m8767);
			अगर (id < S5M8767_BUCK1)
				regulators[id].vsel_mask = 0x3f;
			अन्यथा
				regulators[id].vsel_mask = 0xff;

			ret = s5m8767_get_रेजिस्टर(s5m8767, id, &enable_reg,
					     &enable_val);
			अगर (ret) अणु
				dev_err(s5m8767->dev, "error reading registers\n");
				वापस ret;
			पूर्ण
			regulators[id].enable_reg = enable_reg;
			regulators[id].enable_mask = S5M8767_ENCTRL_MASK;
			regulators[id].enable_val = enable_val;
		पूर्ण

		config.dev = s5m8767->dev;
		config.init_data = pdata->regulators[i].initdata;
		config.driver_data = s5m8767;
		config.regmap = iodev->regmap_pmic;
		config.of_node = pdata->regulators[i].reg_node;
		config.ena_gpiod = शून्य;
		अगर (pdata->regulators[i].ext_control_gpiod) अणु
			/* Assigns config.ena_gpiod */
			s5m8767_regulator_config_ext_control(s5m8767,
					&pdata->regulators[i], &config);

			/*
			 * Hand the GPIO descriptor management over to the
			 * regulator core, हटाओ it from devres management.
			 */
			devm_gpiod_unhinge(s5m8767->dev, config.ena_gpiod);
		पूर्ण
		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &regulators[id],
						  &config);
		अगर (IS_ERR(rdev)) अणु
			ret = PTR_ERR(rdev);
			dev_err(s5m8767->dev, "regulator init failed for %d\n",
					id);
			वापस ret;
		पूर्ण

		अगर (pdata->regulators[i].ext_control_gpiod) अणु
			ret = s5m8767_enable_ext_control(s5m8767, rdev);
			अगर (ret < 0) अणु
				dev_err(s5m8767->dev,
						"failed to enable gpio control over %s: %d\n",
						rdev->desc->name, ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id s5m8767_pmic_id[] = अणु
	अणु "s5m8767-pmic", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, s5m8767_pmic_id);

अटल काष्ठा platक्रमm_driver s5m8767_pmic_driver = अणु
	.driver = अणु
		.name = "s5m8767-pmic",
	पूर्ण,
	.probe = s5m8767_pmic_probe,
	.id_table = s5m8767_pmic_id,
पूर्ण;
module_platक्रमm_driver(s5m8767_pmic_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Sangbeom Kim <sbkim73@samsung.com>");
MODULE_DESCRIPTION("Samsung S5M8767 Regulator Driver");
MODULE_LICENSE("GPL");
