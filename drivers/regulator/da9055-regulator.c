<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Regulator driver क्रम DA9055 PMIC
//
// Copyright(c) 2012 Dialog Semiconductor Ltd.
//
// Author: David Dajun Chen <dchen@diasemi.com>

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/of_regulator.h>

#समावेश <linux/mfd/da9055/core.h>
#समावेश <linux/mfd/da9055/reg.h>
#समावेश <linux/mfd/da9055/pdata.h>

#घोषणा DA9055_MIN_UA		0
#घोषणा DA9055_MAX_UA		3

#घोषणा DA9055_LDO_MODE_SYNC	0
#घोषणा DA9055_LDO_MODE_SLEEP	1

#घोषणा DA9055_BUCK_MODE_SLEEP	1
#घोषणा DA9055_BUCK_MODE_SYNC	2
#घोषणा DA9055_BUCK_MODE_AUTO	3

/* DA9055 REGULATOR IDs */
#घोषणा DA9055_ID_BUCK1	0
#घोषणा DA9055_ID_BUCK2	1
#घोषणा DA9055_ID_LDO1		2
#घोषणा DA9055_ID_LDO2		3
#घोषणा DA9055_ID_LDO3		4
#घोषणा DA9055_ID_LDO4		5
#घोषणा DA9055_ID_LDO5		6
#घोषणा DA9055_ID_LDO6		7

/* DA9055 BUCK current limit */
अटल स्थिर अचिन्हित पूर्णांक da9055_current_limits[] = अणु
	500000, 600000, 700000, 800000
पूर्ण;

काष्ठा da9055_conf_reg अणु
	पूर्णांक reg;
	पूर्णांक sel_mask;
	पूर्णांक en_mask;
पूर्ण;

काष्ठा da9055_volt_reg अणु
	पूर्णांक reg_a;
	पूर्णांक reg_b;
	पूर्णांक sl_shअगरt;
	पूर्णांक v_mask;
पूर्ण;

काष्ठा da9055_mode_reg अणु
	पूर्णांक reg;
	पूर्णांक mask;
	पूर्णांक shअगरt;
पूर्ण;

काष्ठा da9055_regulator_info अणु
	काष्ठा regulator_desc reg_desc;
	काष्ठा da9055_conf_reg conf;
	काष्ठा da9055_volt_reg volt;
	काष्ठा da9055_mode_reg mode;
पूर्ण;

काष्ठा da9055_regulator अणु
	काष्ठा da9055 *da9055;
	काष्ठा da9055_regulator_info *info;
	काष्ठा regulator_dev *rdev;
	क्रमागत gpio_select reg_rselect;
पूर्ण;

अटल अचिन्हित पूर्णांक da9055_buck_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा da9055_regulator *regulator = rdev_get_drvdata(rdev);
	काष्ठा da9055_regulator_info *info = regulator->info;
	पूर्णांक ret, mode = 0;

	ret = da9055_reg_पढ़ो(regulator->da9055, info->mode.reg);
	अगर (ret < 0)
		वापस ret;

	चयन ((ret & info->mode.mask) >> info->mode.shअगरt) अणु
	हाल DA9055_BUCK_MODE_SYNC:
		mode = REGULATOR_MODE_FAST;
		अवरोध;
	हाल DA9055_BUCK_MODE_AUTO:
		mode = REGULATOR_MODE_NORMAL;
		अवरोध;
	हाल DA9055_BUCK_MODE_SLEEP:
		mode = REGULATOR_MODE_STANDBY;
		अवरोध;
	पूर्ण

	वापस mode;
पूर्ण

अटल पूर्णांक da9055_buck_set_mode(काष्ठा regulator_dev *rdev,
					अचिन्हित पूर्णांक mode)
अणु
	काष्ठा da9055_regulator *regulator = rdev_get_drvdata(rdev);
	काष्ठा da9055_regulator_info *info = regulator->info;
	पूर्णांक val = 0;

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		val = DA9055_BUCK_MODE_SYNC << info->mode.shअगरt;
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		val = DA9055_BUCK_MODE_AUTO << info->mode.shअगरt;
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		val = DA9055_BUCK_MODE_SLEEP << info->mode.shअगरt;
		अवरोध;
	पूर्ण

	वापस da9055_reg_update(regulator->da9055, info->mode.reg,
				 info->mode.mask, val);
पूर्ण

अटल अचिन्हित पूर्णांक da9055_lकरो_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा da9055_regulator *regulator = rdev_get_drvdata(rdev);
	काष्ठा da9055_regulator_info *info = regulator->info;
	पूर्णांक ret;

	ret = da9055_reg_पढ़ो(regulator->da9055, info->volt.reg_b);
	अगर (ret < 0)
		वापस ret;

	अगर (ret >> info->volt.sl_shअगरt)
		वापस REGULATOR_MODE_STANDBY;
	अन्यथा
		वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल पूर्णांक da9055_lकरो_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा da9055_regulator *regulator = rdev_get_drvdata(rdev);
	काष्ठा da9055_regulator_info *info = regulator->info;
	काष्ठा da9055_volt_reg volt = info->volt;
	पूर्णांक val = 0;

	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
	हाल REGULATOR_MODE_FAST:
		val = DA9055_LDO_MODE_SYNC;
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		val = DA9055_LDO_MODE_SLEEP;
		अवरोध;
	पूर्ण

	वापस da9055_reg_update(regulator->da9055, volt.reg_b,
				 1 << volt.sl_shअगरt,
				 val << volt.sl_shअगरt);
पूर्ण

अटल पूर्णांक da9055_regulator_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा da9055_regulator *regulator = rdev_get_drvdata(rdev);
	काष्ठा da9055_regulator_info *info = regulator->info;
	काष्ठा da9055_volt_reg volt = info->volt;
	पूर्णांक ret, sel;

	/*
	 * There are two voltage रेजिस्टर set A & B क्रम voltage ramping but
	 * either one of then can be active thereक्रमe we first determine
	 * the active रेजिस्टर set.
	 */
	ret = da9055_reg_पढ़ो(regulator->da9055, info->conf.reg);
	अगर (ret < 0)
		वापस ret;

	ret &= info->conf.sel_mask;

	/* Get the voltage क्रम the active रेजिस्टर set A/B */
	अगर (ret == DA9055_REGUALTOR_SET_A)
		ret = da9055_reg_पढ़ो(regulator->da9055, volt.reg_a);
	अन्यथा
		ret = da9055_reg_पढ़ो(regulator->da9055, volt.reg_b);

	अगर (ret < 0)
		वापस ret;

	sel = (ret & volt.v_mask);
	वापस sel;
पूर्ण

अटल पूर्णांक da9055_regulator_set_voltage_sel(काष्ठा regulator_dev *rdev,
					    अचिन्हित पूर्णांक selector)
अणु
	काष्ठा da9055_regulator *regulator = rdev_get_drvdata(rdev);
	काष्ठा da9055_regulator_info *info = regulator->info;
	पूर्णांक ret;

	/*
	 * Regulator रेजिस्टर set A/B is not selected through GPIO thereक्रमe
	 * we use शेष रेजिस्टर set A क्रम voltage ramping.
	 */
	अगर (regulator->reg_rselect == NO_GPIO) अणु
		/* Select रेजिस्टर set A */
		ret = da9055_reg_update(regulator->da9055, info->conf.reg,
					info->conf.sel_mask, DA9055_SEL_REG_A);
		अगर (ret < 0)
			वापस ret;

		/* Set the voltage */
		वापस da9055_reg_update(regulator->da9055, info->volt.reg_a,
					 info->volt.v_mask, selector);
	पूर्ण

	/*
	 * Here regulator रेजिस्टर set A/B is selected through GPIO.
	 * Thereक्रमe we first determine the selected रेजिस्टर set A/B and
	 * then set the desired voltage क्रम that रेजिस्टर set A/B.
	 */
	ret = da9055_reg_पढ़ो(regulator->da9055, info->conf.reg);
	अगर (ret < 0)
		वापस ret;

	ret &= info->conf.sel_mask;

	/* Set the voltage */
	अगर (ret == DA9055_REGUALTOR_SET_A)
		वापस da9055_reg_update(regulator->da9055, info->volt.reg_a,
					 info->volt.v_mask, selector);
	अन्यथा
		वापस da9055_reg_update(regulator->da9055, info->volt.reg_b,
					 info->volt.v_mask, selector);
पूर्ण

अटल पूर्णांक da9055_regulator_set_suspend_voltage(काष्ठा regulator_dev *rdev,
						पूर्णांक uV)
अणु
	काष्ठा da9055_regulator *regulator = rdev_get_drvdata(rdev);
	काष्ठा da9055_regulator_info *info = regulator->info;
	पूर्णांक ret;

	/* Select रेजिस्टर set B क्रम suspend voltage ramping. */
	अगर (regulator->reg_rselect == NO_GPIO) अणु
		ret = da9055_reg_update(regulator->da9055, info->conf.reg,
					info->conf.sel_mask, DA9055_SEL_REG_B);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = regulator_map_voltage_linear(rdev, uV, uV);
	अगर (ret < 0)
		वापस ret;

	वापस da9055_reg_update(regulator->da9055, info->volt.reg_b,
				 info->volt.v_mask, ret);
पूर्ण

अटल पूर्णांक da9055_suspend_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा da9055_regulator *regulator = rdev_get_drvdata(rdev);
	काष्ठा da9055_regulator_info *info = regulator->info;

	/* Select रेजिस्टर set B क्रम voltage ramping. */
	अगर (regulator->reg_rselect == NO_GPIO)
		वापस da9055_reg_update(regulator->da9055, info->conf.reg,
					info->conf.sel_mask, DA9055_SEL_REG_B);
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक da9055_suspend_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा da9055_regulator *regulator = rdev_get_drvdata(rdev);
	काष्ठा da9055_regulator_info *info = regulator->info;

	/* Diselect रेजिस्टर set B. */
	अगर (regulator->reg_rselect == NO_GPIO)
		वापस da9055_reg_update(regulator->da9055, info->conf.reg,
					info->conf.sel_mask, DA9055_SEL_REG_A);
	अन्यथा
		वापस 0;
पूर्ण

अटल स्थिर काष्ठा regulator_ops da9055_buck_ops = अणु
	.get_mode = da9055_buck_get_mode,
	.set_mode = da9055_buck_set_mode,

	.get_current_limit = regulator_get_current_limit_regmap,
	.set_current_limit = regulator_set_current_limit_regmap,

	.get_voltage_sel = da9055_regulator_get_voltage_sel,
	.set_voltage_sel = da9055_regulator_set_voltage_sel,
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,

	.set_suspend_voltage = da9055_regulator_set_suspend_voltage,
	.set_suspend_enable = da9055_suspend_enable,
	.set_suspend_disable = da9055_suspend_disable,
	.set_suspend_mode = da9055_buck_set_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops da9055_lकरो_ops = अणु
	.get_mode = da9055_lकरो_get_mode,
	.set_mode = da9055_lकरो_set_mode,

	.get_voltage_sel = da9055_regulator_get_voltage_sel,
	.set_voltage_sel = da9055_regulator_set_voltage_sel,
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,

	.set_suspend_voltage = da9055_regulator_set_suspend_voltage,
	.set_suspend_enable = da9055_suspend_enable,
	.set_suspend_disable = da9055_suspend_disable,
	.set_suspend_mode = da9055_lकरो_set_mode,

पूर्ण;

#घोषणा DA9055_LDO(_id, step, min, max, vbits, voffset) \
अणु\
	.reg_desc = अणु\
		.name = #_id,\
		.of_match = of_match_ptr(#_id),\
		.regulators_node = of_match_ptr("regulators"),\
		.ops = &da9055_lकरो_ops,\
		.type = REGULATOR_VOLTAGE,\
		.id = DA9055_ID_##_id,\
		.n_voltages = (max - min) / step + 1 + (voffset), \
		.enable_reg = DA9055_REG_BCORE_CONT + DA9055_ID_##_id, \
		.enable_mask = 1, \
		.min_uV = (min) * 1000,\
		.uV_step = (step) * 1000,\
		.linear_min_sel = (voffset),\
		.owner = THIS_MODULE,\
	पूर्ण,\
	.conf = अणु\
		.reg = DA9055_REG_BCORE_CONT + DA9055_ID_##_id, \
		.sel_mask = (1 << 4),\
		.en_mask = 1,\
	पूर्ण,\
	.volt = अणु\
		.reg_a = DA9055_REG_VBCORE_A + DA9055_ID_##_id, \
		.reg_b = DA9055_REG_VBCORE_B + DA9055_ID_##_id, \
		.sl_shअगरt = 7,\
		.v_mask = (1 << (vbits)) - 1,\
	पूर्ण,\
पूर्ण

#घोषणा DA9055_BUCK(_id, step, min, max, vbits, voffset, mbits, sbits) \
अणु\
	.reg_desc = अणु\
		.name = #_id,\
		.of_match = of_match_ptr(#_id),\
		.regulators_node = of_match_ptr("regulators"),\
		.ops = &da9055_buck_ops,\
		.type = REGULATOR_VOLTAGE,\
		.id = DA9055_ID_##_id,\
		.n_voltages = (max - min) / step + 1 + (voffset), \
		.enable_reg = DA9055_REG_BCORE_CONT + DA9055_ID_##_id, \
		.enable_mask = 1,\
		.min_uV = (min) * 1000,\
		.uV_step = (step) * 1000,\
		.linear_min_sel = (voffset),\
		.owner = THIS_MODULE,\
		.curr_table = da9055_current_limits,\
		.n_current_limits = ARRAY_SIZE(da9055_current_limits),\
		.csel_reg = DA9055_REG_BUCK_LIM,\
		.csel_mask = (mbits),\
	पूर्ण,\
	.conf = अणु\
		.reg = DA9055_REG_BCORE_CONT + DA9055_ID_##_id, \
		.sel_mask = (1 << 4),\
		.en_mask = 1,\
	पूर्ण,\
	.volt = अणु\
		.reg_a = DA9055_REG_VBCORE_A + DA9055_ID_##_id, \
		.reg_b = DA9055_REG_VBCORE_B + DA9055_ID_##_id, \
		.sl_shअगरt = 7,\
		.v_mask = (1 << (vbits)) - 1,\
	पूर्ण,\
	.mode = अणु\
		.reg = DA9055_REG_BCORE_MODE,\
		.mask = (mbits),\
		.shअगरt = (sbits),\
	पूर्ण,\
पूर्ण

अटल काष्ठा da9055_regulator_info da9055_regulator_info[] = अणु
	DA9055_BUCK(BUCK1, 25, 725, 2075, 6, 9, 0xc, 2),
	DA9055_BUCK(BUCK2, 25, 925, 2500, 6, 0, 3, 0),
	DA9055_LDO(LDO1, 50, 900, 3300, 6, 2),
	DA9055_LDO(LDO2, 50, 900, 3300, 6, 3),
	DA9055_LDO(LDO3, 50, 900, 3300, 6, 2),
	DA9055_LDO(LDO4, 50, 900, 3300, 6, 2),
	DA9055_LDO(LDO5, 50, 900, 2750, 6, 2),
	DA9055_LDO(LDO6, 20, 900, 3300, 7, 0),
पूर्ण;

/*
 * Configures regulator to be controlled either through GPIO 1 or 2.
 * GPIO can control regulator state and/or select the regulator रेजिस्टर
 * set A/B क्रम voltage ramping.
 */
अटल पूर्णांक da9055_gpio_init(काष्ठा da9055_regulator *regulator,
			    काष्ठा regulator_config *config,
			    काष्ठा da9055_pdata *pdata, पूर्णांक id)
अणु
	काष्ठा da9055_regulator_info *info = regulator->info;
	पूर्णांक ret = 0;

	अगर (!pdata)
		वापस 0;

	अगर (pdata->gpio_ren && pdata->gpio_ren[id]) अणु
		अक्षर name[18];
		पूर्णांक gpio_mux = pdata->gpio_ren[id];

		config->ena_gpiod = pdata->ena_gpiods[id];

		/*
		 * GPI pin is muxed with regulator to control the
		 * regulator state.
		 */
		प्र_लिखो(name, "DA9055 GPI %d", gpio_mux);
		ret = devm_gpio_request_one(config->dev, gpio_mux, GPIOF_सूची_IN,
					    name);
		अगर (ret < 0)
			जाओ err;

		/*
		 * Let the regulator know that its state is controlled
		 * through GPI.
		 */
		ret = da9055_reg_update(regulator->da9055, info->conf.reg,
					DA9055_E_GPI_MASK,
					pdata->reg_ren[id]
					<< DA9055_E_GPI_SHIFT);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	अगर (pdata->gpio_rsel && pdata->gpio_rsel[id]) अणु
		अक्षर name[18];
		पूर्णांक gpio_mux = pdata->gpio_rsel[id];

		regulator->reg_rselect = pdata->reg_rsel[id];

		/*
		 * GPI pin is muxed with regulator to select the
		 * regulator रेजिस्टर set A/B क्रम voltage ramping.
		 */
		प्र_लिखो(name, "DA9055 GPI %d", gpio_mux);
		ret = devm_gpio_request_one(config->dev, gpio_mux, GPIOF_सूची_IN,
					    name);
		अगर (ret < 0)
			जाओ err;

		/*
		 * Let the regulator know that its रेजिस्टर set A/B
		 * will be selected through GPI क्रम voltage ramping.
		 */
		ret = da9055_reg_update(regulator->da9055, info->conf.reg,
					DA9055_V_GPI_MASK,
					pdata->reg_rsel[id]
					<< DA9055_V_GPI_SHIFT);
	पूर्ण

err:
	वापस ret;
पूर्ण

अटल irqवापस_t da9055_lकरो5_6_oc_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9055_regulator *regulator = data;

	regulator_notअगरier_call_chain(regulator->rdev,
				      REGULATOR_EVENT_OVER_CURRENT, शून्य);

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत काष्ठा da9055_regulator_info *find_regulator_info(पूर्णांक id)
अणु
	काष्ठा da9055_regulator_info *info;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(da9055_regulator_info); i++) अणु
		info = &da9055_regulator_info[i];
		अगर (info->reg_desc.id == id)
			वापस info;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक da9055_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा da9055_regulator *regulator;
	काष्ठा da9055 *da9055 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा da9055_pdata *pdata = dev_get_platdata(da9055->dev);
	पूर्णांक ret, irq;

	regulator = devm_kzalloc(&pdev->dev, माप(काष्ठा da9055_regulator),
				 GFP_KERNEL);
	अगर (!regulator)
		वापस -ENOMEM;

	regulator->info = find_regulator_info(pdev->id);
	अगर (regulator->info == शून्य) अणु
		dev_err(&pdev->dev, "invalid regulator ID specified\n");
		वापस -EINVAL;
	पूर्ण

	regulator->da9055 = da9055;
	config.dev = da9055->dev;
	config.driver_data = regulator;
	config.regmap = da9055->regmap;

	अगर (pdata)
		config.init_data = pdata->regulators[pdev->id];

	ret = da9055_gpio_init(regulator, &config, pdata, pdev->id);
	अगर (ret < 0)
		वापस ret;

	regulator->rdev = devm_regulator_रेजिस्टर(&pdev->dev,
						  &regulator->info->reg_desc,
						  &config);
	अगर (IS_ERR(regulator->rdev)) अणु
		dev_err(&pdev->dev, "Failed to register regulator %s\n",
			regulator->info->reg_desc.name);
		वापस PTR_ERR(regulator->rdev);
	पूर्ण

	/* Only LDO 5 and 6 has got the over current पूर्णांकerrupt */
	अगर (pdev->id == DA9055_ID_LDO5 || pdev->id ==  DA9055_ID_LDO6) अणु
		irq = platक्रमm_get_irq_byname(pdev, "REGULATOR");
		अगर (irq < 0)
			वापस irq;

		ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य,
						da9055_lकरो5_6_oc_irq,
						IRQF_TRIGGER_HIGH |
						IRQF_ONESHOT |
						IRQF_PROBE_SHARED,
						pdev->name, regulator);
		अगर (ret != 0) अणु
			अगर (ret != -EBUSY) अणु
				dev_err(&pdev->dev,
				"Failed to request Regulator IRQ %d: %d\n",
				irq, ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, regulator);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da9055_regulator_driver = अणु
	.probe = da9055_regulator_probe,
	.driver = अणु
		.name = "da9055-regulator",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init da9055_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&da9055_regulator_driver);
पूर्ण
subsys_initcall(da9055_regulator_init);

अटल व्योम __निकास da9055_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&da9055_regulator_driver);
पूर्ण
module_निकास(da9055_regulator_निकास);

MODULE_AUTHOR("David Dajun Chen <dchen@diasemi.com>");
MODULE_DESCRIPTION("Power Regulator driver for Dialog DA9055 PMIC");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da9055-regulator");
