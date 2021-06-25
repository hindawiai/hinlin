<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Copyright 2014 Embest Technology Co. Ltd. Inc.
// bd71815-regulator.c ROHM BD71815 regulator driver
//
// Author: Tony Luo <luofc@embedinfo.com>
//
// Partially rewritten at 2021 by
// Matti Vaittinen <matti.vaitinen@fi.rohmeurope.com>

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/mfd/rohm-generic.h>
#समावेश <linux/mfd/rohm-bd71815.h>
#समावेश <linux/regulator/of_regulator.h>

काष्ठा bd71815_regulator अणु
	काष्ठा regulator_desc desc;
	स्थिर काष्ठा rohm_dvs_config *dvs;
पूर्ण;

काष्ठा bd71815_pmic अणु
	काष्ठा bd71815_regulator descs[BD71815_REGULATOR_CNT];
	काष्ठा regmap *regmap;
	काष्ठा device *dev;
	काष्ठा gpio_descs *gps;
	काष्ठा regulator_dev *rdev[BD71815_REGULATOR_CNT];
पूर्ण;

अटल स्थिर पूर्णांक bd7181x_wled_currents[] = अणु
	10, 20, 30, 50, 70, 100, 200, 300, 500, 700, 1000, 2000, 3000, 4000,
	5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000, 15000,
	16000, 17000, 18000, 19000, 20000, 21000, 22000, 23000, 24000, 25000,
पूर्ण;

अटल स्थिर काष्ठा rohm_dvs_config buck1_dvs = अणु
	.level_map		= ROHM_DVS_LEVEL_RUN | ROHM_DVS_LEVEL_SNVS |
				  ROHM_DVS_LEVEL_SUSPEND | ROHM_DVS_LEVEL_LPSR,
	.run_reg		= BD71815_REG_BUCK1_VOLT_H,
	.run_mask		= BD71815_VOLT_MASK,
	.run_on_mask		= BD71815_BUCK_RUN_ON,
	.snvs_on_mask		= BD71815_BUCK_SNVS_ON,
	.suspend_reg		= BD71815_REG_BUCK1_VOLT_L,
	.suspend_mask		= BD71815_VOLT_MASK,
	.suspend_on_mask	= BD71815_BUCK_SUSP_ON,
	.lpsr_reg		= BD71815_REG_BUCK1_VOLT_L,
	.lpsr_mask		= BD71815_VOLT_MASK,
	.lpsr_on_mask		= BD71815_BUCK_LPSR_ON,
पूर्ण;

अटल स्थिर काष्ठा rohm_dvs_config buck2_dvs = अणु
	.level_map		= ROHM_DVS_LEVEL_RUN | ROHM_DVS_LEVEL_SNVS |
				  ROHM_DVS_LEVEL_SUSPEND | ROHM_DVS_LEVEL_LPSR,
	.run_reg		= BD71815_REG_BUCK2_VOLT_H,
	.run_mask		= BD71815_VOLT_MASK,
	.run_on_mask		= BD71815_BUCK_RUN_ON,
	.snvs_on_mask		= BD71815_BUCK_SNVS_ON,
	.suspend_reg		= BD71815_REG_BUCK2_VOLT_L,
	.suspend_mask		= BD71815_VOLT_MASK,
	.suspend_on_mask	= BD71815_BUCK_SUSP_ON,
	.lpsr_reg		= BD71815_REG_BUCK2_VOLT_L,
	.lpsr_mask		= BD71815_VOLT_MASK,
	.lpsr_on_mask		= BD71815_BUCK_LPSR_ON,
पूर्ण;

अटल स्थिर काष्ठा rohm_dvs_config buck3_dvs = अणु
	.level_map		= ROHM_DVS_LEVEL_RUN | ROHM_DVS_LEVEL_SNVS |
				  ROHM_DVS_LEVEL_SUSPEND | ROHM_DVS_LEVEL_LPSR,
	.run_reg		= BD71815_REG_BUCK3_VOLT,
	.run_mask		= BD71815_VOLT_MASK,
	.run_on_mask		= BD71815_BUCK_RUN_ON,
	.snvs_on_mask		= BD71815_BUCK_SNVS_ON,
	.suspend_on_mask	= BD71815_BUCK_SUSP_ON,
	.lpsr_on_mask		= BD71815_BUCK_LPSR_ON,
पूर्ण;

अटल स्थिर काष्ठा rohm_dvs_config buck4_dvs = अणु
	.level_map		= ROHM_DVS_LEVEL_RUN | ROHM_DVS_LEVEL_SNVS |
				  ROHM_DVS_LEVEL_SUSPEND | ROHM_DVS_LEVEL_LPSR,
	.run_reg		= BD71815_REG_BUCK4_VOLT,
	.run_mask		= BD71815_VOLT_MASK,
	.run_on_mask		= BD71815_BUCK_RUN_ON,
	.snvs_on_mask		= BD71815_BUCK_SNVS_ON,
	.suspend_on_mask	= BD71815_BUCK_SUSP_ON,
	.lpsr_on_mask		= BD71815_BUCK_LPSR_ON,
पूर्ण;

अटल स्थिर काष्ठा rohm_dvs_config lकरो1_dvs = अणु
	.level_map		= ROHM_DVS_LEVEL_RUN | ROHM_DVS_LEVEL_SNVS |
				  ROHM_DVS_LEVEL_SUSPEND | ROHM_DVS_LEVEL_LPSR,
	.run_reg		= BD71815_REG_LDO_MODE1,
	.run_mask		= BD71815_VOLT_MASK,
	.run_on_mask		= LDO1_RUN_ON,
	.snvs_on_mask		= LDO1_SNVS_ON,
	.suspend_on_mask	= LDO1_SUSP_ON,
	.lpsr_on_mask		= LDO1_LPSR_ON,
पूर्ण;

अटल स्थिर काष्ठा rohm_dvs_config lकरो2_dvs = अणु
	.level_map		= ROHM_DVS_LEVEL_RUN | ROHM_DVS_LEVEL_SNVS |
				  ROHM_DVS_LEVEL_SUSPEND | ROHM_DVS_LEVEL_LPSR,
	.run_reg		= BD71815_REG_LDO_MODE2,
	.run_mask		= BD71815_VOLT_MASK,
	.run_on_mask		= LDO2_RUN_ON,
	.snvs_on_mask		= LDO2_SNVS_ON,
	.suspend_on_mask	= LDO2_SUSP_ON,
	.lpsr_on_mask		= LDO2_LPSR_ON,
पूर्ण;

अटल स्थिर काष्ठा rohm_dvs_config lकरो3_dvs = अणु
	.level_map		= ROHM_DVS_LEVEL_RUN | ROHM_DVS_LEVEL_SNVS |
				  ROHM_DVS_LEVEL_SUSPEND | ROHM_DVS_LEVEL_LPSR,
	.run_reg		= BD71815_REG_LDO_MODE2,
	.run_mask		= BD71815_VOLT_MASK,
	.run_on_mask		= LDO3_RUN_ON,
	.snvs_on_mask		= LDO3_SNVS_ON,
	.suspend_on_mask	= LDO3_SUSP_ON,
	.lpsr_on_mask		= LDO3_LPSR_ON,
पूर्ण;

अटल स्थिर काष्ठा rohm_dvs_config lकरो4_dvs = अणु
	.level_map		= ROHM_DVS_LEVEL_RUN | ROHM_DVS_LEVEL_SNVS |
				  ROHM_DVS_LEVEL_SUSPEND | ROHM_DVS_LEVEL_LPSR,
	.run_reg		= BD71815_REG_LDO_MODE3,
	.run_mask		= BD71815_VOLT_MASK,
	.run_on_mask		= LDO4_RUN_ON,
	.snvs_on_mask		= LDO4_SNVS_ON,
	.suspend_on_mask	= LDO4_SUSP_ON,
	.lpsr_on_mask		= LDO4_LPSR_ON,
पूर्ण;

अटल स्थिर काष्ठा rohm_dvs_config lकरो5_dvs = अणु
	.level_map		= ROHM_DVS_LEVEL_RUN | ROHM_DVS_LEVEL_SNVS |
				  ROHM_DVS_LEVEL_SUSPEND | ROHM_DVS_LEVEL_LPSR,
	.run_reg		= BD71815_REG_LDO_MODE3,
	.run_mask		= BD71815_VOLT_MASK,
	.run_on_mask		= LDO5_RUN_ON,
	.snvs_on_mask		= LDO5_SNVS_ON,
	.suspend_on_mask	= LDO5_SUSP_ON,
	.lpsr_on_mask		= LDO5_LPSR_ON,
पूर्ण;

अटल स्थिर काष्ठा rohm_dvs_config dvref_dvs = अणु
	.level_map		= ROHM_DVS_LEVEL_RUN | ROHM_DVS_LEVEL_SNVS |
				  ROHM_DVS_LEVEL_SUSPEND | ROHM_DVS_LEVEL_LPSR,
	.run_on_mask		= DVREF_RUN_ON,
	.snvs_on_mask		= DVREF_SNVS_ON,
	.suspend_on_mask	= DVREF_SUSP_ON,
	.lpsr_on_mask		= DVREF_LPSR_ON,
पूर्ण;

अटल स्थिर काष्ठा rohm_dvs_config lकरोlpsr_dvs = अणु
	.level_map		= ROHM_DVS_LEVEL_RUN | ROHM_DVS_LEVEL_SNVS |
				  ROHM_DVS_LEVEL_SUSPEND | ROHM_DVS_LEVEL_LPSR,
	.run_on_mask		= DVREF_RUN_ON,
	.snvs_on_mask		= DVREF_SNVS_ON,
	.suspend_on_mask	= DVREF_SUSP_ON,
	.lpsr_on_mask		= DVREF_LPSR_ON,
पूर्ण;

अटल स्थिर काष्ठा rohm_dvs_config buck5_dvs = अणु
	.level_map		= ROHM_DVS_LEVEL_RUN | ROHM_DVS_LEVEL_SNVS |
				  ROHM_DVS_LEVEL_SUSPEND | ROHM_DVS_LEVEL_LPSR,
	.run_reg		= BD71815_REG_BUCK5_VOLT,
	.run_mask		= BD71815_VOLT_MASK,
	.run_on_mask		= BD71815_BUCK_RUN_ON,
	.snvs_on_mask		= BD71815_BUCK_SNVS_ON,
	.suspend_on_mask	= BD71815_BUCK_SUSP_ON,
	.lpsr_on_mask		= BD71815_BUCK_LPSR_ON,
पूर्ण;

अटल पूर्णांक set_hw_dvs_levels(काष्ठा device_node *np,
			     स्थिर काष्ठा regulator_desc *desc,
			     काष्ठा regulator_config *cfg)
अणु
	काष्ठा bd71815_regulator *data;

	data = container_of(desc, काष्ठा bd71815_regulator, desc);
	वापस rohm_regulator_set_dvs_levels(data->dvs, np, desc, cfg->regmap);
पूर्ण

/*
 * Bucks 1 and 2 have two voltage selection रेजिस्टरs where selected
 * voltage can be set. Which of the रेजिस्टरs is used can be either controlled
 * by a control bit in रेजिस्टर - or by HW state. If HW state specअगरic voltages
 * are given - then we assume HW state based control should be used.
 *
 * If volatge value is updated to currently selected रेजिस्टर - then output
 * voltage is immediately changed no matter what is set as ramp rate. Thus we
 * शेष changing voltage by writing new value to inactive रेजिस्टर and
 * then updating the 'register selection' bit. This naturally only works when
 * HW state machine is not used to select the voltage.
 */
अटल पूर्णांक buck12_set_hw_dvs_levels(काष्ठा device_node *np,
				    स्थिर काष्ठा regulator_desc *desc,
				    काष्ठा regulator_config *cfg)
अणु
	काष्ठा bd71815_regulator *data;
	पूर्णांक ret = 0, val;

	data = container_of(desc, काष्ठा bd71815_regulator, desc);

	अगर (of_find_property(np, "rohm,dvs-run-voltage", शून्य) ||
	    of_find_property(np, "rohm,dvs-suspend-voltage", शून्य) ||
	    of_find_property(np, "rohm,dvs-lpsr-voltage", शून्य) ||
	    of_find_property(np, "rohm,dvs-snvs-voltage", शून्य)) अणु
		ret = regmap_पढ़ो(cfg->regmap, desc->vsel_reg, &val);
		अगर (ret)
			वापस ret;

		अगर (!(BD71815_BUCK_STBY_DVS & val) &&
		    !(BD71815_BUCK_DVSSEL & val)) अणु
			पूर्णांक val2;

			/*
			 * We are currently using voltage from _L.
			 * We'd better copy it to _H and चयन to it to
			 * aव्योम shutting us करोwn अगर LPSR or SUSPEND is set to
			 * disabled. _L value is at reg _H + 1
			 */
			ret = regmap_पढ़ो(cfg->regmap, desc->vsel_reg + 1,
					  &val2);
			अगर (ret)
				वापस ret;

			ret = regmap_update_bits(cfg->regmap, desc->vsel_reg,
						 BD71815_VOLT_MASK |
						 BD71815_BUCK_DVSSEL,
						 val2 | BD71815_BUCK_DVSSEL);
			अगर (ret)
				वापस ret;
		पूर्ण
		ret = rohm_regulator_set_dvs_levels(data->dvs, np, desc,
						    cfg->regmap);
		अगर (ret)
			वापस ret;
		/*
		 * DVS levels were given => use HW-state machine क्रम voltage
		 * controls. NOTE: AFAIK, This means that अगर voltage is changed
		 * by SW the ramp-rate is not respected. Should we disable
		 * SW voltage control when the HW state machine is used?
		 */
		ret = regmap_update_bits(cfg->regmap, desc->vsel_reg,
					 BD71815_BUCK_STBY_DVS,
					 BD71815_BUCK_STBY_DVS);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * BUCK1/2
 * BUCK1RAMPRATE[1:0] BUCK1 DVS ramp rate setting
 * 00: 10.00mV/usec	10mV 1uS
 * 01: 5.00mV/usec	10mV 2uS
 * 10: 2.50mV/usec	10mV 4uS
 * 11: 1.25mV/usec	10mV 8uS
 */
अटल स्थिर अचिन्हित पूर्णांक bd7181x_ramp_table[] = अणु 1250, 2500, 5000, 10000 पूर्ण;

अटल पूर्णांक bd7181x_led_set_current_limit(काष्ठा regulator_dev *rdev,
					पूर्णांक min_uA, पूर्णांक max_uA)
अणु
	पूर्णांक ret;
	पूर्णांक onstatus;

	onstatus = regulator_is_enabled_regmap(rdev);

	ret = regulator_set_current_limit_regmap(rdev, min_uA, max_uA);
	अगर (!ret) अणु
		पूर्णांक newstatus;

		newstatus = regulator_is_enabled_regmap(rdev);
		अगर (onstatus != newstatus) अणु
			/*
			 * HW FIX: spurious led status change detected. Toggle
			 * state as a workaround
			 */
			अगर (onstatus)
				ret = regulator_enable_regmap(rdev);
			अन्यथा
				ret = regulator_disable_regmap(rdev);

			अगर (ret)
				dev_err(rdev_get_dev(rdev),
					"failed to revert the LED state (%d)\n",
					ret);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bd7181x_buck12_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा bd71815_pmic *pmic = rdev_get_drvdata(rdev);
	पूर्णांक rid = rdev_get_id(rdev);
	पूर्णांक ret, regh, regl, val;

	regh = BD71815_REG_BUCK1_VOLT_H + rid * 0x2;
	regl = BD71815_REG_BUCK1_VOLT_L + rid * 0x2;

	ret = regmap_पढ़ो(pmic->regmap, regh, &val);
	अगर (ret)
		वापस ret;

	/*
	 * If we use HW state machine based voltage reg selection - then we
	 * वापस BD71815_REG_BUCK1_VOLT_H which is used at RUN.
	 * Else we करो वापस the BD71815_REG_BUCK1_VOLT_H or
	 * BD71815_REG_BUCK1_VOLT_L depending on which is selected to be used
	 * by BD71815_BUCK_DVSSEL bit
	 */
	अगर ((!(val & BD71815_BUCK_STBY_DVS)) && (!(val & BD71815_BUCK_DVSSEL)))
		ret = regmap_पढ़ो(pmic->regmap, regl, &val);

	अगर (ret)
		वापस ret;

	वापस val & BD71815_VOLT_MASK;
पूर्ण

/*
 * For Buck 1/2.
 */
अटल पूर्णांक bd7181x_buck12_set_voltage_sel(काष्ठा regulator_dev *rdev,
					  अचिन्हित पूर्णांक sel)
अणु
	काष्ठा bd71815_pmic *pmic = rdev_get_drvdata(rdev);
	पूर्णांक rid = rdev_get_id(rdev);
	पूर्णांक ret, val, reg, regh, regl;

	regh = BD71815_REG_BUCK1_VOLT_H + rid*0x2;
	regl = BD71815_REG_BUCK1_VOLT_L + rid*0x2;

	ret = regmap_पढ़ो(pmic->regmap, regh, &val);
	अगर (ret)
		वापस ret;

	/*
	 * If bucks 1 & 2 are controlled by state machine - then the RUN state
	 * voltage is set to BD71815_REG_BUCK1_VOLT_H. Changing SUSPEND/LPSR
	 * voltages at runसमय is not supported by this driver.
	 */
	अगर (((val & BD71815_BUCK_STBY_DVS))) अणु
		वापस regmap_update_bits(pmic->regmap, regh, BD71815_VOLT_MASK,
					  sel);
	पूर्ण
	/* Update new voltage to the रेजिस्टर which is not selected now */
	अगर (val & BD71815_BUCK_DVSSEL)
		reg = regl;
	अन्यथा
		reg = regh;

	ret = regmap_update_bits(pmic->regmap, reg, BD71815_VOLT_MASK, sel);
	अगर (ret)
		वापस ret;

	/* Select the other DVS रेजिस्टर to be used */
	वापस regmap_update_bits(pmic->regmap, regh, BD71815_BUCK_DVSSEL, ~val);
पूर्ण

अटल स्थिर काष्ठा regulator_ops bd7181x_lकरो_regulator_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops bd7181x_fixed_regulator_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_linear,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops bd7181x_buck_regulator_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops bd7181x_buck12_regulator_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.set_voltage_sel = bd7181x_buck12_set_voltage_sel,
	.get_voltage_sel = bd7181x_buck12_get_voltage_sel,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.set_ramp_delay = regulator_set_ramp_delay_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops bd7181x_led_regulator_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_current_limit = bd7181x_led_set_current_limit,
	.get_current_limit = regulator_get_current_limit_regmap,
पूर्ण;

#घोषणा BD71815_FIXED_REG(_name, _id, ereg, emsk, voltage, _dvs)	\
	[(_id)] = अणु							\
		.desc = अणु						\
			.name = #_name,					\
			.of_match = of_match_ptr(#_name),		\
			.regulators_node = of_match_ptr("regulators"),	\
			.n_voltages = 1,				\
			.ops = &bd7181x_fixed_regulator_ops,		\
			.type = REGULATOR_VOLTAGE,			\
			.id = (_id),					\
			.owner = THIS_MODULE,				\
			.min_uV = (voltage),				\
			.enable_reg = (ereg),				\
			.enable_mask = (emsk),				\
			.of_parse_cb = set_hw_dvs_levels,		\
		पूर्ण,							\
		.dvs = (_dvs),						\
	पूर्ण

#घोषणा BD71815_BUCK_REG(_name, _id, vsel, ereg, min, max, step, _dvs)	\
	[(_id)] = अणु							\
		.desc = अणु						\
			.name = #_name,					\
			.of_match = of_match_ptr(#_name),		\
			.regulators_node = of_match_ptr("regulators"),	\
			.n_voltages = ((max) - (min)) / (step) + 1,	\
			.ops = &bd7181x_buck_regulator_ops,		\
			.type = REGULATOR_VOLTAGE,			\
			.id = (_id),					\
			.owner = THIS_MODULE,				\
			.min_uV = (min),				\
			.uV_step = (step),				\
			.vsel_reg = (vsel),				\
			.vsel_mask = BD71815_VOLT_MASK,			\
			.enable_reg = (ereg),				\
			.enable_mask = BD71815_BUCK_RUN_ON,		\
			.of_parse_cb = set_hw_dvs_levels,		\
		पूर्ण,							\
		.dvs = (_dvs),						\
	पूर्ण

#घोषणा BD71815_BUCK12_REG(_name, _id, vsel, ereg, min, max, step,	\
			   _dvs)					\
	[(_id)] = अणु							\
		.desc = अणु						\
			.name = #_name,					\
			.of_match = of_match_ptr(#_name),		\
			.regulators_node = of_match_ptr("regulators"),	\
			.n_voltages = ((max) - (min)) / (step) + 1,	\
			.ops = &bd7181x_buck12_regulator_ops,		\
			.type = REGULATOR_VOLTAGE,			\
			.id = (_id),					\
			.owner = THIS_MODULE,				\
			.min_uV = (min),				\
			.uV_step = (step),				\
			.vsel_reg = (vsel),				\
			.vsel_mask = 0x3f,				\
			.enable_reg = (ereg),				\
			.enable_mask = 0x04,				\
			.ramp_reg = (ereg),				\
			.ramp_mask = BD71815_BUCK_RAMPRATE_MASK,	\
			.ramp_delay_table = bd7181x_ramp_table,		\
			.n_ramp_values = ARRAY_SIZE(bd7181x_ramp_table),\
			.of_parse_cb = buck12_set_hw_dvs_levels,	\
		पूर्ण,							\
		.dvs = (_dvs),						\
	पूर्ण

#घोषणा BD71815_LED_REG(_name, _id, csel, mask, ereg, emsk, currents)	\
	[(_id)] = अणु							\
		.desc = अणु						\
			.name = #_name,					\
			.of_match = of_match_ptr(#_name),		\
			.regulators_node = of_match_ptr("regulators"),	\
			.n_current_limits = ARRAY_SIZE(currents),	\
			.ops = &bd7181x_led_regulator_ops,		\
			.type = REGULATOR_CURRENT,			\
			.id = (_id),					\
			.owner = THIS_MODULE,				\
			.curr_table = currents,				\
			.csel_reg = (csel),				\
			.csel_mask = (mask),				\
			.enable_reg = (ereg),				\
			.enable_mask = (emsk),				\
		पूर्ण,							\
	पूर्ण

#घोषणा BD71815_LDO_REG(_name, _id, vsel, ereg, emsk, min, max, step,	\
			_dvs)						\
	[(_id)] = अणु							\
		.desc = अणु						\
			.name = #_name,					\
			.of_match = of_match_ptr(#_name),		\
			.regulators_node = of_match_ptr("regulators"),	\
			.n_voltages = ((max) - (min)) / (step) + 1,	\
			.ops = &bd7181x_lकरो_regulator_ops,		\
			.type = REGULATOR_VOLTAGE,			\
			.id = (_id),					\
			.owner = THIS_MODULE,				\
			.min_uV = (min),				\
			.uV_step = (step),				\
			.vsel_reg = (vsel),				\
			.vsel_mask = BD71815_VOLT_MASK,			\
			.enable_reg = (ereg),				\
			.enable_mask = (emsk),				\
			.of_parse_cb = set_hw_dvs_levels,		\
		पूर्ण,							\
		.dvs = (_dvs),						\
	पूर्ण

अटल काष्ठा bd71815_regulator bd71815_regulators[] = अणु
	BD71815_BUCK12_REG(buck1, BD71815_BUCK1, BD71815_REG_BUCK1_VOLT_H,
			   BD71815_REG_BUCK1_MODE, 800000, 2000000, 25000,
			   &buck1_dvs),
	BD71815_BUCK12_REG(buck2, BD71815_BUCK2, BD71815_REG_BUCK2_VOLT_H,
			   BD71815_REG_BUCK2_MODE, 800000, 2000000, 25000,
			   &buck2_dvs),
	BD71815_BUCK_REG(buck3, BD71815_BUCK3, BD71815_REG_BUCK3_VOLT,
			 BD71815_REG_BUCK3_MODE,  1200000, 2700000, 50000,
			 &buck3_dvs),
	BD71815_BUCK_REG(buck4, BD71815_BUCK4, BD71815_REG_BUCK4_VOLT,
			 BD71815_REG_BUCK4_MODE,  1100000, 1850000, 25000,
			 &buck4_dvs),
	BD71815_BUCK_REG(buck5, BD71815_BUCK5, BD71815_REG_BUCK5_VOLT,
			 BD71815_REG_BUCK5_MODE,  1800000, 3300000, 50000,
			 &buck5_dvs),
	BD71815_LDO_REG(lकरो1, BD71815_LDO1, BD71815_REG_LDO1_VOLT,
			BD71815_REG_LDO_MODE1, LDO1_RUN_ON, 800000, 3300000,
			50000, &lकरो1_dvs),
	BD71815_LDO_REG(lकरो2, BD71815_LDO2, BD71815_REG_LDO2_VOLT,
			BD71815_REG_LDO_MODE2, LDO2_RUN_ON, 800000, 3300000,
			50000, &lकरो2_dvs),
	/*
	 * Let's शेष LDO3 to be enabled by SW. We can override ops अगर DT
	 * says LDO3 should be enabled by HW when DCIN is connected.
	 */
	BD71815_LDO_REG(lकरो3, BD71815_LDO3, BD71815_REG_LDO3_VOLT,
			BD71815_REG_LDO_MODE2, LDO3_RUN_ON, 800000, 3300000,
			50000, &lकरो3_dvs),
	BD71815_LDO_REG(lकरो4, BD71815_LDO4, BD71815_REG_LDO4_VOLT,
			BD71815_REG_LDO_MODE3, LDO4_RUN_ON, 800000, 3300000,
			50000, &lकरो4_dvs),
	BD71815_LDO_REG(lकरो5, BD71815_LDO5, BD71815_REG_LDO5_VOLT_H,
			BD71815_REG_LDO_MODE3, LDO5_RUN_ON, 800000, 3300000,
			50000, &lकरो5_dvs),
	BD71815_FIXED_REG(lकरोdvref, BD71815_LDODVREF, BD71815_REG_LDO_MODE4,
			  DVREF_RUN_ON, 3000000, &dvref_dvs),
	BD71815_FIXED_REG(lकरोlpsr, BD71815_LDOLPSR, BD71815_REG_LDO_MODE4,
			  LDO_LPSR_RUN_ON, 1800000, &lकरोlpsr_dvs),
	BD71815_LED_REG(wled, BD71815_WLED, BD71815_REG_LED_DIMM, LED_DIMM_MASK,
			BD71815_REG_LED_CTRL, LED_RUN_ON,
			bd7181x_wled_currents),
पूर्ण;

अटल पूर्णांक bd7181x_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bd71815_pmic *pmic;
	काष्ठा regulator_config config = अणुपूर्ण;
	पूर्णांक i, ret;
	काष्ठा gpio_desc *lकरो4_en;

	pmic = devm_kzalloc(&pdev->dev, माप(*pmic), GFP_KERNEL);
	अगर (!pmic)
		वापस -ENOMEM;

	स_नकल(pmic->descs, bd71815_regulators,	माप(pmic->descs));

	pmic->dev = &pdev->dev;
	pmic->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!pmic->regmap) अणु
		dev_err(pmic->dev, "No parent regmap\n");
		वापस -ENODEV;
	पूर्ण
	platक्रमm_set_drvdata(pdev, pmic);
	lकरो4_en = devm_gpiod_get_from_of_node(&pdev->dev,
					      pdev->dev.parent->of_node,
						 "rohm,vsel-gpios", 0,
						 GPIOD_ASIS, "ldo4-en");

	अगर (IS_ERR(lकरो4_en)) अणु
		ret = PTR_ERR(lकरो4_en);
		अगर (ret != -ENOENT)
			वापस ret;
		lकरो4_en = शून्य;
	पूर्ण

	/* Disable to go to ship-mode */
	ret = regmap_update_bits(pmic->regmap, BD71815_REG_PWRCTRL,
				 RESTARTEN, 0);
	अगर (ret)
		वापस ret;

	config.dev = pdev->dev.parent;
	config.regmap = pmic->regmap;

	क्रम (i = 0; i < BD71815_REGULATOR_CNT; i++) अणु
		काष्ठा regulator_desc *desc;
		काष्ठा regulator_dev *rdev;

		desc = &pmic->descs[i].desc;
		अगर (i == BD71815_LDO4)
			config.ena_gpiod = lकरो4_en;

		config.driver_data = pmic;

		rdev = devm_regulator_रेजिस्टर(&pdev->dev, desc, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev,
				"failed to register %s regulator\n",
				desc->name);
			वापस PTR_ERR(rdev);
		पूर्ण
		config.ena_gpiod = शून्य;
		pmic->rdev[i] = rdev;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id bd7181x_pmic_id[] = अणु
	अणु "bd71815-pmic", ROHM_CHIP_TYPE_BD71815 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, bd7181x_pmic_id);

अटल काष्ठा platक्रमm_driver bd7181x_regulator = अणु
	.driver = अणु
		.name = "bd7181x-pmic",
		.owner = THIS_MODULE,
	पूर्ण,
	.probe = bd7181x_probe,
	.id_table = bd7181x_pmic_id,
पूर्ण;
module_platक्रमm_driver(bd7181x_regulator);

MODULE_AUTHOR("Tony Luo <luofc@embedinfo.com>");
MODULE_DESCRIPTION("BD71815 voltage regulator driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:bd7181x-pmic");
