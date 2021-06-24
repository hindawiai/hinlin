<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 ROHM Semiconductors
// bd71837-regulator.c ROHM BD71837MWV/BD71847MWV regulator driver

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/rohm-bd718x7.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/slab.h>

/* Typical regulator startup बार as per data sheet in uS */
#घोषणा BD71847_BUCK1_STARTUP_TIME 144
#घोषणा BD71847_BUCK2_STARTUP_TIME 162
#घोषणा BD71847_BUCK3_STARTUP_TIME 162
#घोषणा BD71847_BUCK4_STARTUP_TIME 240
#घोषणा BD71847_BUCK5_STARTUP_TIME 270
#घोषणा BD71847_BUCK6_STARTUP_TIME 200
#घोषणा BD71847_LDO1_STARTUP_TIME  440
#घोषणा BD71847_LDO2_STARTUP_TIME  370
#घोषणा BD71847_LDO3_STARTUP_TIME  310
#घोषणा BD71847_LDO4_STARTUP_TIME  400
#घोषणा BD71847_LDO5_STARTUP_TIME  530
#घोषणा BD71847_LDO6_STARTUP_TIME  400

#घोषणा BD71837_BUCK1_STARTUP_TIME 160
#घोषणा BD71837_BUCK2_STARTUP_TIME 180
#घोषणा BD71837_BUCK3_STARTUP_TIME 180
#घोषणा BD71837_BUCK4_STARTUP_TIME 180
#घोषणा BD71837_BUCK5_STARTUP_TIME 160
#घोषणा BD71837_BUCK6_STARTUP_TIME 240
#घोषणा BD71837_BUCK7_STARTUP_TIME 220
#घोषणा BD71837_BUCK8_STARTUP_TIME 200
#घोषणा BD71837_LDO1_STARTUP_TIME  440
#घोषणा BD71837_LDO2_STARTUP_TIME  370
#घोषणा BD71837_LDO3_STARTUP_TIME  310
#घोषणा BD71837_LDO4_STARTUP_TIME  400
#घोषणा BD71837_LDO5_STARTUP_TIME  310
#घोषणा BD71837_LDO6_STARTUP_TIME  400
#घोषणा BD71837_LDO7_STARTUP_TIME  530

/*
 * BD718(37/47/50) have two "enable control modes". ON/OFF can either be
 * controlled by software - or by PMIC पूर्णांकernal HW state machine. Whether
 * regulator should be under SW or HW control can be defined from device-tree.
 * Let's provide separate ops क्रम regulators to use depending on the "enable
 * control mode".
 */
#घोषणा BD718XX_HWOPNAME(swopname) swopname##_hwcontrol

#घोषणा BD718XX_OPS(name, _list_voltage, _map_voltage, _set_voltage_sel, \
		   _get_voltage_sel, _set_voltage_समय_sel, _set_ramp_delay) \
अटल स्थिर काष्ठा regulator_ops name = अणु			\
	.enable = regulator_enable_regmap,			\
	.disable = regulator_disable_regmap,			\
	.is_enabled = regulator_is_enabled_regmap,		\
	.list_voltage = (_list_voltage),			\
	.map_voltage = (_map_voltage),				\
	.set_voltage_sel = (_set_voltage_sel),			\
	.get_voltage_sel = (_get_voltage_sel),			\
	.set_voltage_समय_sel = (_set_voltage_समय_sel),	\
	.set_ramp_delay = (_set_ramp_delay),			\
पूर्ण;								\
								\
अटल स्थिर काष्ठा regulator_ops BD718XX_HWOPNAME(name) = अणु	\
	.is_enabled = always_enabled_by_hwstate,		\
	.list_voltage = (_list_voltage),			\
	.map_voltage = (_map_voltage),				\
	.set_voltage_sel = (_set_voltage_sel),			\
	.get_voltage_sel = (_get_voltage_sel),			\
	.set_voltage_समय_sel = (_set_voltage_समय_sel),	\
	.set_ramp_delay = (_set_ramp_delay),			\
पूर्ण								\

/*
 * BUCK1/2/3/4
 * BUCK1RAMPRATE[1:0] BUCK1 DVS ramp rate setting
 * 00: 10.00mV/usec 10mV 1uS
 * 01: 5.00mV/usec	10mV 2uS
 * 10: 2.50mV/usec	10mV 4uS
 * 11: 1.25mV/usec	10mV 8uS
 */
अटल स्थिर अचिन्हित पूर्णांक bd718xx_ramp_delay[] = अणु 10000, 5000, 2500, 1250 पूर्ण;

/* These functions are used when regulators are under HW state machine control.
 * We assume PMIC is in RUN state because SW running and able to query the
 * status. Most of the regulators have fixed ON or OFF state at RUN/IDLE so क्रम
 * them we just वापस a स्थिरant. BD71837 BUCK3 and BUCK4 are exceptions as
 * they support configuring the ON/OFF state क्रम RUN.
 *
 * Note क्रम next hacker - these PMICs have a रेजिस्टर where the HW state can be
 * पढ़ो. If assuming RUN appears to be false in your use-हाल - you can
 * implement state पढ़ोing (although that is not going to be atomic) beक्रमe
 * वापसing the enable state.
 */
अटल पूर्णांक always_enabled_by_hwstate(काष्ठा regulator_dev *rdev)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक never_enabled_by_hwstate(काष्ठा regulator_dev *rdev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक bd71837_get_buck34_enable_hwctrl(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(rdev->regmap, rdev->desc->enable_reg, &val);
	अगर (ret)
		वापस ret;

	वापस !!(BD718XX_BUCK_RUN_ON & val);
पूर्ण
/*
 * On BD71837 (not on BD71847, BD71850, ...)
 * Bucks 1 to 4 support DVS. PWM mode is used when voltage is changed.
 * Bucks 5 to 8 and LDOs can use PFM and must be disabled when voltage
 * is changed. Hence we वापस -EBUSY क्रम these अगर voltage is changed
 * when BUCK/LDO is enabled.
 *
 * On BD71847, BD71850, ... The LDO voltage can be changed when LDO is
 * enabled. But अगर voltage is increased the LDO घातer-good monitoring
 * must be disabled क्रम the duration of changing + 1mS to ensure voltage
 * has reached the higher level beक्रमe HW करोes next under voltage detection
 * cycle.
 */
अटल पूर्णांक bd71837_set_voltage_sel_restricted(काष्ठा regulator_dev *rdev,
						    अचिन्हित पूर्णांक sel)
अणु
	अगर (rdev->desc->ops->is_enabled(rdev))
		वापस -EBUSY;

	वापस regulator_set_voltage_sel_regmap(rdev, sel);
पूर्ण

अटल व्योम voltage_change_करोne(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक sel,
				अचिन्हित पूर्णांक *mask)
अणु
	पूर्णांक ret;

	अगर (*mask) अणु
		/*
		 * Let's allow scheduling as we use I2C anyways. We just need to
		 * guarantee minimum of 1ms sleep - it shouldn't matter अगर we
		 * exceed it due to the scheduling.
		 */
		msleep(1);
		/*
		 * Note क्रम next hacker. The PWRGOOD should not be masked on
		 * BD71847 so we will just unconditionally enable detection
		 * when voltage is set.
		 * If someone want's to disable PWRGOOD he must implement
		 * caching and restoring the old value here. I am not
		 * aware of such use-हालs so क्रम the sake of the simplicity
		 * we just always enable PWRGOOD here.
		 */
		ret = regmap_update_bits(rdev->regmap, BD718XX_REG_MVRFLTMASK2,
					 *mask, 0);
		अगर (ret)
			dev_err(&rdev->dev,
				"Failed to re-enable voltage monitoring (%d)\n",
				ret);
	पूर्ण
पूर्ण

अटल पूर्णांक voltage_change_prepare(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक sel,
				  अचिन्हित पूर्णांक *mask)
अणु
	पूर्णांक ret;

	*mask = 0;
	अगर (rdev->desc->ops->is_enabled(rdev)) अणु
		पूर्णांक now, new;

		now = rdev->desc->ops->get_voltage_sel(rdev);
		अगर (now < 0)
			वापस now;

		now = rdev->desc->ops->list_voltage(rdev, now);
		अगर (now < 0)
			वापस now;

		new = rdev->desc->ops->list_voltage(rdev, sel);
		अगर (new < 0)
			वापस new;

		/*
		 * If we increase LDO voltage when LDO is enabled we need to
		 * disable the घातer-good detection until voltage has reached
		 * the new level. According to HW colleagues the maximum समय
		 * it takes is 1000us. I assume that on प्रणालीs with light load
		 * this might be less - and we could probably use DT to give
		 * प्रणाली specअगरic delay value अगर perक्रमmance matters.
		 *
		 * Well, knowing we use I2C here and can add scheduling delays
		 * I करोn't think it is worth the hassle and I just add fixed
		 * 1ms sleep here (and allow scheduling). If this turns out to
		 * be a problem we can change it to delay and make the delay
		 * समय configurable.
		 */
		अगर (new > now) अणु
			पूर्णांक lकरो_offset = rdev->desc->id - BD718XX_LDO1;

			*mask = BD718XX_LDO1_VRMON80 << lकरो_offset;
			ret = regmap_update_bits(rdev->regmap,
						 BD718XX_REG_MVRFLTMASK2,
						 *mask, *mask);
			अगर (ret) अणु
				dev_err(&rdev->dev,
					"Failed to stop voltage monitoring\n");
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bd718xx_set_voltage_sel_restricted(काष्ठा regulator_dev *rdev,
						    अचिन्हित पूर्णांक sel)
अणु
	पूर्णांक ret;
	पूर्णांक mask;

	ret = voltage_change_prepare(rdev, sel, &mask);
	अगर (ret)
		वापस ret;

	ret = regulator_set_voltage_sel_regmap(rdev, sel);
	voltage_change_करोne(rdev, sel, &mask);

	वापस ret;
पूर्ण

अटल पूर्णांक bd718xx_set_voltage_sel_pickable_restricted(
		काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक sel)
अणु
	पूर्णांक ret;
	पूर्णांक mask;

	ret = voltage_change_prepare(rdev, sel, &mask);
	अगर (ret)
		वापस ret;

	ret = regulator_set_voltage_sel_pickable_regmap(rdev, sel);
	voltage_change_करोne(rdev, sel, &mask);

	वापस ret;
पूर्ण

अटल पूर्णांक bd71837_set_voltage_sel_pickable_restricted(
		काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक sel)
अणु
	अगर (rdev->desc->ops->is_enabled(rdev))
		वापस -EBUSY;

	वापस regulator_set_voltage_sel_pickable_regmap(rdev, sel);
पूर्ण

/*
 * OPS common क्रम BD71847 and BD71850
 */
BD718XX_OPS(bd718xx_pickable_range_lकरो_ops,
	    regulator_list_voltage_pickable_linear_range, शून्य,
	    bd718xx_set_voltage_sel_pickable_restricted,
	    regulator_get_voltage_sel_pickable_regmap, शून्य, शून्य);

/* BD71847 and BD71850 LDO 5 is by शेष OFF at RUN state */
अटल स्थिर काष्ठा regulator_ops bd718xx_lकरो5_ops_hwstate = अणु
	.is_enabled = never_enabled_by_hwstate,
	.list_voltage = regulator_list_voltage_pickable_linear_range,
	.set_voltage_sel = bd718xx_set_voltage_sel_pickable_restricted,
	.get_voltage_sel = regulator_get_voltage_sel_pickable_regmap,
पूर्ण;

BD718XX_OPS(bd718xx_pickable_range_buck_ops,
	    regulator_list_voltage_pickable_linear_range, शून्य,
	    regulator_set_voltage_sel_pickable_regmap,
	    regulator_get_voltage_sel_pickable_regmap,
	    regulator_set_voltage_समय_sel, शून्य);

BD718XX_OPS(bd718xx_lकरो_regulator_ops, regulator_list_voltage_linear_range,
	    शून्य, bd718xx_set_voltage_sel_restricted,
	    regulator_get_voltage_sel_regmap, शून्य, शून्य);

BD718XX_OPS(bd718xx_lकरो_regulator_nolinear_ops, regulator_list_voltage_table,
	    शून्य, bd718xx_set_voltage_sel_restricted,
	    regulator_get_voltage_sel_regmap, शून्य, शून्य);

BD718XX_OPS(bd718xx_buck_regulator_ops, regulator_list_voltage_linear_range,
	    शून्य, regulator_set_voltage_sel_regmap,
	    regulator_get_voltage_sel_regmap, regulator_set_voltage_समय_sel,
	    शून्य);

BD718XX_OPS(bd718xx_buck_regulator_nolinear_ops, regulator_list_voltage_table,
	    regulator_map_voltage_ascend, regulator_set_voltage_sel_regmap,
	    regulator_get_voltage_sel_regmap, regulator_set_voltage_समय_sel,
	    शून्य);

/*
 * OPS क्रम BD71837
 */
BD718XX_OPS(bd71837_pickable_range_lकरो_ops,
	    regulator_list_voltage_pickable_linear_range, शून्य,
	    bd71837_set_voltage_sel_pickable_restricted,
	    regulator_get_voltage_sel_pickable_regmap, शून्य, शून्य);

BD718XX_OPS(bd71837_pickable_range_buck_ops,
	    regulator_list_voltage_pickable_linear_range, शून्य,
	    bd71837_set_voltage_sel_pickable_restricted,
	    regulator_get_voltage_sel_pickable_regmap,
	    regulator_set_voltage_समय_sel, शून्य);

BD718XX_OPS(bd71837_lकरो_regulator_ops, regulator_list_voltage_linear_range,
	    शून्य, bd71837_set_voltage_sel_restricted,
	    regulator_get_voltage_sel_regmap, शून्य, शून्य);

BD718XX_OPS(bd71837_lकरो_regulator_nolinear_ops, regulator_list_voltage_table,
	    शून्य, bd71837_set_voltage_sel_restricted,
	    regulator_get_voltage_sel_regmap, शून्य, शून्य);

BD718XX_OPS(bd71837_buck_regulator_ops, regulator_list_voltage_linear_range,
	    शून्य, bd71837_set_voltage_sel_restricted,
	    regulator_get_voltage_sel_regmap, regulator_set_voltage_समय_sel,
	    शून्य);

BD718XX_OPS(bd71837_buck_regulator_nolinear_ops, regulator_list_voltage_table,
	    regulator_map_voltage_ascend, bd71837_set_voltage_sel_restricted,
	    regulator_get_voltage_sel_regmap, regulator_set_voltage_समय_sel,
	    शून्य);
/*
 * BD71837 bucks 3 and 4 support defining their enable/disable state also
 * when buck enable state is under HW state machine control. In that हाल the
 * bit [2] in CTRL रेजिस्टर is used to indicate अगर regulator should be ON.
 */
अटल स्थिर काष्ठा regulator_ops bd71837_buck34_ops_hwctrl = अणु
	.is_enabled = bd71837_get_buck34_enable_hwctrl,
	.list_voltage = regulator_list_voltage_linear_range,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.set_ramp_delay = regulator_set_ramp_delay_regmap,
पूर्ण;

/*
 * OPS क्रम all of the ICs - BD718(37/47/50)
 */
BD718XX_OPS(bd718xx_dvs_buck_regulator_ops, regulator_list_voltage_linear_range,
	    शून्य, regulator_set_voltage_sel_regmap,
	    regulator_get_voltage_sel_regmap, regulator_set_voltage_समय_sel,
	    /* bd718xx_buck1234_set_ramp_delay */ regulator_set_ramp_delay_regmap);

/*
 * BD71837 BUCK1/2/3/4
 * BD71847 BUCK1/2
 * 0.70 to 1.30V (10mV step)
 */
अटल स्थिर काष्ठा linear_range bd718xx_dvs_buck_volts[] = अणु
	REGULATOR_LINEAR_RANGE(700000, 0x00, 0x3C, 10000),
	REGULATOR_LINEAR_RANGE(1300000, 0x3D, 0x3F, 0),
पूर्ण;

/*
 * BD71837 BUCK5
 * 0.7V to 1.35V  (range 0)
 * and
 * 0.675 to 1.325 (range 1)
 */
अटल स्थिर काष्ठा linear_range bd71837_buck5_volts[] = अणु
	/* Ranges when VOLT_SEL bit is 0 */
	REGULATOR_LINEAR_RANGE(700000, 0x00, 0x03, 100000),
	REGULATOR_LINEAR_RANGE(1050000, 0x04, 0x05, 50000),
	REGULATOR_LINEAR_RANGE(1200000, 0x06, 0x07, 150000),
	/* Ranges when VOLT_SEL bit is 1  */
	REGULATOR_LINEAR_RANGE(675000, 0x0, 0x3, 100000),
	REGULATOR_LINEAR_RANGE(1025000, 0x4, 0x5, 50000),
	REGULATOR_LINEAR_RANGE(1175000, 0x6, 0x7, 150000),
पूर्ण;

/*
 * Range selector क्रम first 3 linear ranges is 0x0
 * and 0x1 क्रम last 3 ranges.
 */
अटल स्थिर अचिन्हित पूर्णांक bd71837_buck5_volt_range_sel[] = अणु
	0x0, 0x0, 0x0, 0x80, 0x80, 0x80
पूर्ण;

/*
 * BD71847 BUCK3
 */
अटल स्थिर काष्ठा linear_range bd71847_buck3_volts[] = अणु
	/* Ranges when VOLT_SEL bits are 00 */
	REGULATOR_LINEAR_RANGE(700000, 0x00, 0x03, 100000),
	REGULATOR_LINEAR_RANGE(1050000, 0x04, 0x05, 50000),
	REGULATOR_LINEAR_RANGE(1200000, 0x06, 0x07, 150000),
	/* Ranges when VOLT_SEL bits are 01 */
	REGULATOR_LINEAR_RANGE(550000, 0x0, 0x7, 50000),
	/* Ranges when VOLT_SEL bits are 11 */
	REGULATOR_LINEAR_RANGE(675000, 0x0, 0x3, 100000),
	REGULATOR_LINEAR_RANGE(1025000, 0x4, 0x5, 50000),
	REGULATOR_LINEAR_RANGE(1175000, 0x6, 0x7, 150000),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक bd71847_buck3_volt_range_sel[] = अणु
	0x0, 0x0, 0x0, 0x40, 0x80, 0x80, 0x80
पूर्ण;

अटल स्थिर काष्ठा linear_range bd71847_buck4_volts[] = अणु
	REGULATOR_LINEAR_RANGE(3000000, 0x00, 0x03, 100000),
	REGULATOR_LINEAR_RANGE(2600000, 0x00, 0x03, 100000),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक bd71847_buck4_volt_range_sel[] = अणु 0x0, 0x40 पूर्ण;

/*
 * BUCK6
 * 3.0V to 3.3V (step 100mV)
 */
अटल स्थिर काष्ठा linear_range bd71837_buck6_volts[] = अणु
	REGULATOR_LINEAR_RANGE(3000000, 0x00, 0x03, 100000),
पूर्ण;

/*
 * BD71837 BUCK7
 * BD71847 BUCK5
 * 000 = 1.605V
 * 001 = 1.695V
 * 010 = 1.755V
 * 011 = 1.8V (Initial)
 * 100 = 1.845V
 * 101 = 1.905V
 * 110 = 1.95V
 * 111 = 1.995V
 */
अटल स्थिर अचिन्हित पूर्णांक bd718xx_3rd_nodvs_buck_volts[] = अणु
	1605000, 1695000, 1755000, 1800000, 1845000, 1905000, 1950000, 1995000
पूर्ण;

/*
 * BUCK8
 * 0.8V to 1.40V (step 10mV)
 */
अटल स्थिर काष्ठा linear_range bd718xx_4th_nodvs_buck_volts[] = अणु
	REGULATOR_LINEAR_RANGE(800000, 0x00, 0x3C, 10000),
पूर्ण;

/*
 * LDO1
 * 3.0 to 3.3V (100mV step)
 */
अटल स्थिर काष्ठा linear_range bd718xx_lकरो1_volts[] = अणु
	REGULATOR_LINEAR_RANGE(3000000, 0x00, 0x03, 100000),
	REGULATOR_LINEAR_RANGE(1600000, 0x00, 0x03, 100000),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक bd718xx_lकरो1_volt_range_sel[] = अणु 0x0, 0x20 पूर्ण;

/*
 * LDO2
 * 0.8 or 0.9V
 */
अटल स्थिर अचिन्हित पूर्णांक lकरो_2_volts[] = अणु
	900000, 800000
पूर्ण;

/*
 * LDO3
 * 1.8 to 3.3V (100mV step)
 */
अटल स्थिर काष्ठा linear_range bd718xx_lकरो3_volts[] = अणु
	REGULATOR_LINEAR_RANGE(1800000, 0x00, 0x0F, 100000),
पूर्ण;

/*
 * LDO4
 * 0.9 to 1.8V (100mV step)
 */
अटल स्थिर काष्ठा linear_range bd718xx_lकरो4_volts[] = अणु
	REGULATOR_LINEAR_RANGE(900000, 0x00, 0x09, 100000),
पूर्ण;

/*
 * LDO5 क्रम BD71837
 * 1.8 to 3.3V (100mV step)
 */
अटल स्थिर काष्ठा linear_range bd71837_lकरो5_volts[] = अणु
	REGULATOR_LINEAR_RANGE(1800000, 0x00, 0x0F, 100000),
पूर्ण;

/*
 * LDO5 क्रम BD71837
 * 1.8 to 3.3V (100mV step)
 */
अटल स्थिर काष्ठा linear_range bd71847_lकरो5_volts[] = अणु
	REGULATOR_LINEAR_RANGE(1800000, 0x00, 0x0F, 100000),
	REGULATOR_LINEAR_RANGE(800000, 0x00, 0x0F, 100000),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक bd71847_lकरो5_volt_range_sel[] = अणु 0x0, 0x20 पूर्ण;

/*
 * LDO6
 * 0.9 to 1.8V (100mV step)
 */
अटल स्थिर काष्ठा linear_range bd718xx_lकरो6_volts[] = अणु
	REGULATOR_LINEAR_RANGE(900000, 0x00, 0x09, 100000),
पूर्ण;

/*
 * LDO7
 * 1.8 to 3.3V (100mV step)
 */
अटल स्थिर काष्ठा linear_range bd71837_lकरो7_volts[] = अणु
	REGULATOR_LINEAR_RANGE(1800000, 0x00, 0x0F, 100000),
पूर्ण;

काष्ठा reg_init अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक val;
पूर्ण;
काष्ठा bd718xx_regulator_data अणु
	काष्ठा regulator_desc desc;
	स्थिर काष्ठा rohm_dvs_config dvs;
	स्थिर काष्ठा reg_init init;
	स्थिर काष्ठा reg_init *additional_inits;
	पूर्णांक additional_init_amnt;
पूर्ण;

/*
 * There is a HW quirk in BD71837. The shutकरोwn sequence timings क्रम
 * bucks/LDOs which are controlled via रेजिस्टर पूर्णांकerface are changed.
 * At PMIC घातeroff the voltage क्रम BUCK6/7 is cut immediately at the
 * beginning of shut-करोwn sequence. As bucks 6 and 7 are parent
 * supplies क्रम LDO5 and LDO6 - this causes LDO5/6 voltage
 * monitoring to errorneously detect under voltage and क्रमce PMIC to
 * emergency state instead of घातeroff. In order to aव्योम this we
 * disable voltage monitoring क्रम LDO5 and LDO6
 */
अटल स्थिर काष्ठा reg_init bd71837_lकरो5_inits[] = अणु
	अणु
		.reg = BD718XX_REG_MVRFLTMASK2,
		.mask = BD718XX_LDO5_VRMON80,
		.val = BD718XX_LDO5_VRMON80,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_init bd71837_lकरो6_inits[] = अणु
	अणु
		.reg = BD718XX_REG_MVRFLTMASK2,
		.mask = BD718XX_LDO6_VRMON80,
		.val = BD718XX_LDO6_VRMON80,
	पूर्ण,
पूर्ण;

अटल पूर्णांक buck_set_hw_dvs_levels(काष्ठा device_node *np,
			    स्थिर काष्ठा regulator_desc *desc,
			    काष्ठा regulator_config *cfg)
अणु
	काष्ठा bd718xx_regulator_data *data;

	data = container_of(desc, काष्ठा bd718xx_regulator_data, desc);

	वापस rohm_regulator_set_dvs_levels(&data->dvs, np, desc, cfg->regmap);
पूर्ण

अटल स्थिर काष्ठा regulator_ops *bd71847_swcontrol_ops[] = अणु
	&bd718xx_dvs_buck_regulator_ops, &bd718xx_dvs_buck_regulator_ops,
	&bd718xx_pickable_range_buck_ops, &bd718xx_pickable_range_buck_ops,
	&bd718xx_buck_regulator_nolinear_ops, &bd718xx_buck_regulator_ops,
	&bd718xx_pickable_range_lकरो_ops, &bd718xx_lकरो_regulator_nolinear_ops,
	&bd718xx_lकरो_regulator_ops, &bd718xx_lकरो_regulator_ops,
	&bd718xx_pickable_range_lकरो_ops, &bd718xx_lकरो_regulator_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops *bd71847_hwcontrol_ops[] = अणु
	&BD718XX_HWOPNAME(bd718xx_dvs_buck_regulator_ops),
	&BD718XX_HWOPNAME(bd718xx_dvs_buck_regulator_ops),
	&BD718XX_HWOPNAME(bd718xx_pickable_range_buck_ops),
	&BD718XX_HWOPNAME(bd718xx_pickable_range_buck_ops),
	&BD718XX_HWOPNAME(bd718xx_buck_regulator_nolinear_ops),
	&BD718XX_HWOPNAME(bd718xx_buck_regulator_ops),
	&BD718XX_HWOPNAME(bd718xx_pickable_range_lकरो_ops),
	&BD718XX_HWOPNAME(bd718xx_lकरो_regulator_nolinear_ops),
	&BD718XX_HWOPNAME(bd718xx_lकरो_regulator_ops),
	&BD718XX_HWOPNAME(bd718xx_lकरो_regulator_ops),
	&bd718xx_lकरो5_ops_hwstate,
	&BD718XX_HWOPNAME(bd718xx_lकरो_regulator_ops),
पूर्ण;

अटल काष्ठा bd718xx_regulator_data bd71847_regulators[] = अणु
	अणु
		.desc = अणु
			.name = "buck1",
			.of_match = of_match_ptr("BUCK1"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_BUCK1,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD718XX_DVS_BUCK_VOLTAGE_NUM,
			.linear_ranges = bd718xx_dvs_buck_volts,
			.n_linear_ranges =
				ARRAY_SIZE(bd718xx_dvs_buck_volts),
			.vsel_reg = BD718XX_REG_BUCK1_VOLT_RUN,
			.vsel_mask = DVS_BUCK_RUN_MASK,
			.enable_reg = BD718XX_REG_BUCK1_CTRL,
			.enable_mask = BD718XX_BUCK_EN,
			.enable_समय = BD71847_BUCK1_STARTUP_TIME,
			.owner = THIS_MODULE,
			.ramp_delay_table = bd718xx_ramp_delay,
			.n_ramp_values = ARRAY_SIZE(bd718xx_ramp_delay),
			.ramp_reg = BD718XX_REG_BUCK1_CTRL,
			.ramp_mask = BUCK_RAMPRATE_MASK,
			.of_parse_cb = buck_set_hw_dvs_levels,
		पूर्ण,
		.dvs = अणु
			.level_map = ROHM_DVS_LEVEL_RUN | ROHM_DVS_LEVEL_IDLE |
				     ROHM_DVS_LEVEL_SUSPEND,
			.run_reg = BD718XX_REG_BUCK1_VOLT_RUN,
			.run_mask = DVS_BUCK_RUN_MASK,
			.idle_reg = BD718XX_REG_BUCK1_VOLT_IDLE,
			.idle_mask = DVS_BUCK_RUN_MASK,
			.suspend_reg = BD718XX_REG_BUCK1_VOLT_SUSP,
			.suspend_mask = DVS_BUCK_RUN_MASK,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_BUCK1_CTRL,
			.mask = BD718XX_BUCK_SEL,
			.val = BD718XX_BUCK_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck2",
			.of_match = of_match_ptr("BUCK2"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_BUCK2,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD718XX_DVS_BUCK_VOLTAGE_NUM,
			.linear_ranges = bd718xx_dvs_buck_volts,
			.n_linear_ranges = ARRAY_SIZE(bd718xx_dvs_buck_volts),
			.vsel_reg = BD718XX_REG_BUCK2_VOLT_RUN,
			.vsel_mask = DVS_BUCK_RUN_MASK,
			.enable_reg = BD718XX_REG_BUCK2_CTRL,
			.enable_mask = BD718XX_BUCK_EN,
			.enable_समय = BD71847_BUCK2_STARTUP_TIME,
			.ramp_delay_table = bd718xx_ramp_delay,
			.n_ramp_values = ARRAY_SIZE(bd718xx_ramp_delay),
			.ramp_reg = BD718XX_REG_BUCK2_CTRL,
			.ramp_mask = BUCK_RAMPRATE_MASK,
			.owner = THIS_MODULE,
			.of_parse_cb = buck_set_hw_dvs_levels,
		पूर्ण,
		.dvs = अणु
			.level_map = ROHM_DVS_LEVEL_RUN | ROHM_DVS_LEVEL_IDLE,
			.run_reg = BD718XX_REG_BUCK2_VOLT_RUN,
			.run_mask = DVS_BUCK_RUN_MASK,
			.idle_reg = BD718XX_REG_BUCK2_VOLT_IDLE,
			.idle_mask = DVS_BUCK_RUN_MASK,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_BUCK2_CTRL,
			.mask = BD718XX_BUCK_SEL,
			.val = BD718XX_BUCK_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck3",
			.of_match = of_match_ptr("BUCK3"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_BUCK3,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD71847_BUCK3_VOLTAGE_NUM,
			.linear_ranges = bd71847_buck3_volts,
			.n_linear_ranges =
				ARRAY_SIZE(bd71847_buck3_volts),
			.vsel_reg = BD718XX_REG_1ST_NODVS_BUCK_VOLT,
			.vsel_mask = BD718XX_1ST_NODVS_BUCK_MASK,
			.vsel_range_reg = BD718XX_REG_1ST_NODVS_BUCK_VOLT,
			.vsel_range_mask = BD71847_BUCK3_RANGE_MASK,
			.linear_range_selectors = bd71847_buck3_volt_range_sel,
			.enable_reg = BD718XX_REG_1ST_NODVS_BUCK_CTRL,
			.enable_mask = BD718XX_BUCK_EN,
			.enable_समय = BD71847_BUCK3_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_1ST_NODVS_BUCK_CTRL,
			.mask = BD718XX_BUCK_SEL,
			.val = BD718XX_BUCK_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck4",
			.of_match = of_match_ptr("BUCK4"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_BUCK4,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD71847_BUCK4_VOLTAGE_NUM,
			.linear_ranges = bd71847_buck4_volts,
			.n_linear_ranges =
				ARRAY_SIZE(bd71847_buck4_volts),
			.enable_reg = BD718XX_REG_2ND_NODVS_BUCK_CTRL,
			.vsel_reg = BD718XX_REG_2ND_NODVS_BUCK_VOLT,
			.vsel_mask = BD71847_BUCK4_MASK,
			.vsel_range_reg = BD718XX_REG_2ND_NODVS_BUCK_VOLT,
			.vsel_range_mask = BD71847_BUCK4_RANGE_MASK,
			.linear_range_selectors = bd71847_buck4_volt_range_sel,
			.enable_mask = BD718XX_BUCK_EN,
			.enable_समय = BD71847_BUCK4_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_2ND_NODVS_BUCK_CTRL,
			.mask = BD718XX_BUCK_SEL,
			.val = BD718XX_BUCK_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck5",
			.of_match = of_match_ptr("BUCK5"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_BUCK5,
			.type = REGULATOR_VOLTAGE,
			.volt_table = &bd718xx_3rd_nodvs_buck_volts[0],
			.n_voltages = ARRAY_SIZE(bd718xx_3rd_nodvs_buck_volts),
			.vsel_reg = BD718XX_REG_3RD_NODVS_BUCK_VOLT,
			.vsel_mask = BD718XX_3RD_NODVS_BUCK_MASK,
			.enable_reg = BD718XX_REG_3RD_NODVS_BUCK_CTRL,
			.enable_mask = BD718XX_BUCK_EN,
			.enable_समय = BD71847_BUCK5_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_3RD_NODVS_BUCK_CTRL,
			.mask = BD718XX_BUCK_SEL,
			.val = BD718XX_BUCK_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck6",
			.of_match = of_match_ptr("BUCK6"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_BUCK6,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD718XX_4TH_NODVS_BUCK_VOLTAGE_NUM,
			.linear_ranges = bd718xx_4th_nodvs_buck_volts,
			.n_linear_ranges =
				ARRAY_SIZE(bd718xx_4th_nodvs_buck_volts),
			.vsel_reg = BD718XX_REG_4TH_NODVS_BUCK_VOLT,
			.vsel_mask = BD718XX_4TH_NODVS_BUCK_MASK,
			.enable_reg = BD718XX_REG_4TH_NODVS_BUCK_CTRL,
			.enable_mask = BD718XX_BUCK_EN,
			.enable_समय = BD71847_BUCK6_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_4TH_NODVS_BUCK_CTRL,
			.mask = BD718XX_BUCK_SEL,
			.val = BD718XX_BUCK_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo1",
			.of_match = of_match_ptr("LDO1"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_LDO1,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD718XX_LDO1_VOLTAGE_NUM,
			.linear_ranges = bd718xx_lकरो1_volts,
			.n_linear_ranges = ARRAY_SIZE(bd718xx_lकरो1_volts),
			.vsel_reg = BD718XX_REG_LDO1_VOLT,
			.vsel_mask = BD718XX_LDO1_MASK,
			.vsel_range_reg = BD718XX_REG_LDO1_VOLT,
			.vsel_range_mask = BD718XX_LDO1_RANGE_MASK,
			.linear_range_selectors = bd718xx_lकरो1_volt_range_sel,
			.enable_reg = BD718XX_REG_LDO1_VOLT,
			.enable_mask = BD718XX_LDO_EN,
			.enable_समय = BD71847_LDO1_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_LDO1_VOLT,
			.mask = BD718XX_LDO_SEL,
			.val = BD718XX_LDO_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo2",
			.of_match = of_match_ptr("LDO2"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_LDO2,
			.type = REGULATOR_VOLTAGE,
			.volt_table = &lकरो_2_volts[0],
			.vsel_reg = BD718XX_REG_LDO2_VOLT,
			.vsel_mask = BD718XX_LDO2_MASK,
			.n_voltages = ARRAY_SIZE(lकरो_2_volts),
			.enable_reg = BD718XX_REG_LDO2_VOLT,
			.enable_mask = BD718XX_LDO_EN,
			.enable_समय = BD71847_LDO2_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_LDO2_VOLT,
			.mask = BD718XX_LDO_SEL,
			.val = BD718XX_LDO_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo3",
			.of_match = of_match_ptr("LDO3"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_LDO3,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD718XX_LDO3_VOLTAGE_NUM,
			.linear_ranges = bd718xx_lकरो3_volts,
			.n_linear_ranges = ARRAY_SIZE(bd718xx_lकरो3_volts),
			.vsel_reg = BD718XX_REG_LDO3_VOLT,
			.vsel_mask = BD718XX_LDO3_MASK,
			.enable_reg = BD718XX_REG_LDO3_VOLT,
			.enable_mask = BD718XX_LDO_EN,
			.enable_समय = BD71847_LDO3_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_LDO3_VOLT,
			.mask = BD718XX_LDO_SEL,
			.val = BD718XX_LDO_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo4",
			.of_match = of_match_ptr("LDO4"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_LDO4,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD718XX_LDO4_VOLTAGE_NUM,
			.linear_ranges = bd718xx_lकरो4_volts,
			.n_linear_ranges = ARRAY_SIZE(bd718xx_lकरो4_volts),
			.vsel_reg = BD718XX_REG_LDO4_VOLT,
			.vsel_mask = BD718XX_LDO4_MASK,
			.enable_reg = BD718XX_REG_LDO4_VOLT,
			.enable_mask = BD718XX_LDO_EN,
			.enable_समय = BD71847_LDO4_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_LDO4_VOLT,
			.mask = BD718XX_LDO_SEL,
			.val = BD718XX_LDO_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo5",
			.of_match = of_match_ptr("LDO5"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_LDO5,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD71847_LDO5_VOLTAGE_NUM,
			.linear_ranges = bd71847_lकरो5_volts,
			.n_linear_ranges = ARRAY_SIZE(bd71847_lकरो5_volts),
			.vsel_reg = BD718XX_REG_LDO5_VOLT,
			.vsel_mask = BD71847_LDO5_MASK,
			.vsel_range_reg = BD718XX_REG_LDO5_VOLT,
			.vsel_range_mask = BD71847_LDO5_RANGE_MASK,
			.linear_range_selectors = bd71847_lकरो5_volt_range_sel,
			.enable_reg = BD718XX_REG_LDO5_VOLT,
			.enable_mask = BD718XX_LDO_EN,
			.enable_समय = BD71847_LDO5_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_LDO5_VOLT,
			.mask = BD718XX_LDO_SEL,
			.val = BD718XX_LDO_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo6",
			.of_match = of_match_ptr("LDO6"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_LDO6,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD718XX_LDO6_VOLTAGE_NUM,
			.linear_ranges = bd718xx_lकरो6_volts,
			.n_linear_ranges = ARRAY_SIZE(bd718xx_lकरो6_volts),
			/* LDO6 is supplied by buck5 */
			.supply_name = "buck5",
			.vsel_reg = BD718XX_REG_LDO6_VOLT,
			.vsel_mask = BD718XX_LDO6_MASK,
			.enable_reg = BD718XX_REG_LDO6_VOLT,
			.enable_mask = BD718XX_LDO_EN,
			.enable_समय = BD71847_LDO6_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_LDO6_VOLT,
			.mask = BD718XX_LDO_SEL,
			.val = BD718XX_LDO_SEL,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops *bd71837_swcontrol_ops[] = अणु
	&bd718xx_dvs_buck_regulator_ops, &bd718xx_dvs_buck_regulator_ops,
	&bd718xx_dvs_buck_regulator_ops, &bd718xx_dvs_buck_regulator_ops,
	&bd71837_pickable_range_buck_ops, &bd71837_buck_regulator_ops,
	&bd71837_buck_regulator_nolinear_ops, &bd71837_buck_regulator_ops,
	&bd71837_pickable_range_lकरो_ops, &bd71837_lकरो_regulator_nolinear_ops,
	&bd71837_lकरो_regulator_ops, &bd71837_lकरो_regulator_ops,
	&bd71837_lकरो_regulator_ops, &bd71837_lकरो_regulator_ops,
	&bd71837_lकरो_regulator_ops,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops *bd71837_hwcontrol_ops[] = अणु
	&BD718XX_HWOPNAME(bd718xx_dvs_buck_regulator_ops),
	&BD718XX_HWOPNAME(bd718xx_dvs_buck_regulator_ops),
	&bd71837_buck34_ops_hwctrl, &bd71837_buck34_ops_hwctrl,
	&BD718XX_HWOPNAME(bd71837_pickable_range_buck_ops),
	&BD718XX_HWOPNAME(bd71837_buck_regulator_ops),
	&BD718XX_HWOPNAME(bd71837_buck_regulator_nolinear_ops),
	&BD718XX_HWOPNAME(bd71837_buck_regulator_ops),
	&BD718XX_HWOPNAME(bd71837_pickable_range_lकरो_ops),
	&BD718XX_HWOPNAME(bd71837_lकरो_regulator_nolinear_ops),
	&BD718XX_HWOPNAME(bd71837_lकरो_regulator_ops),
	&BD718XX_HWOPNAME(bd71837_lकरो_regulator_ops),
	&BD718XX_HWOPNAME(bd71837_lकरो_regulator_ops),
	&BD718XX_HWOPNAME(bd71837_lकरो_regulator_ops),
	&BD718XX_HWOPNAME(bd71837_lकरो_regulator_ops),
पूर्ण;

अटल काष्ठा bd718xx_regulator_data bd71837_regulators[] = अणु
	अणु
		.desc = अणु
			.name = "buck1",
			.of_match = of_match_ptr("BUCK1"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_BUCK1,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD718XX_DVS_BUCK_VOLTAGE_NUM,
			.linear_ranges = bd718xx_dvs_buck_volts,
			.n_linear_ranges = ARRAY_SIZE(bd718xx_dvs_buck_volts),
			.vsel_reg = BD718XX_REG_BUCK1_VOLT_RUN,
			.vsel_mask = DVS_BUCK_RUN_MASK,
			.enable_reg = BD718XX_REG_BUCK1_CTRL,
			.enable_mask = BD718XX_BUCK_EN,
			.enable_समय = BD71837_BUCK1_STARTUP_TIME,
			.ramp_delay_table = bd718xx_ramp_delay,
			.n_ramp_values = ARRAY_SIZE(bd718xx_ramp_delay),
			.ramp_reg = BD718XX_REG_BUCK1_CTRL,
			.ramp_mask = BUCK_RAMPRATE_MASK,
			.owner = THIS_MODULE,
			.of_parse_cb = buck_set_hw_dvs_levels,
		पूर्ण,
		.dvs = अणु
			.level_map = ROHM_DVS_LEVEL_RUN | ROHM_DVS_LEVEL_IDLE |
				     ROHM_DVS_LEVEL_SUSPEND,
			.run_reg = BD718XX_REG_BUCK1_VOLT_RUN,
			.run_mask = DVS_BUCK_RUN_MASK,
			.idle_reg = BD718XX_REG_BUCK1_VOLT_IDLE,
			.idle_mask = DVS_BUCK_RUN_MASK,
			.suspend_reg = BD718XX_REG_BUCK1_VOLT_SUSP,
			.suspend_mask = DVS_BUCK_RUN_MASK,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_BUCK1_CTRL,
			.mask = BD718XX_BUCK_SEL,
			.val = BD718XX_BUCK_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck2",
			.of_match = of_match_ptr("BUCK2"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_BUCK2,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD718XX_DVS_BUCK_VOLTAGE_NUM,
			.linear_ranges = bd718xx_dvs_buck_volts,
			.n_linear_ranges = ARRAY_SIZE(bd718xx_dvs_buck_volts),
			.vsel_reg = BD718XX_REG_BUCK2_VOLT_RUN,
			.vsel_mask = DVS_BUCK_RUN_MASK,
			.enable_reg = BD718XX_REG_BUCK2_CTRL,
			.enable_mask = BD718XX_BUCK_EN,
			.enable_समय = BD71837_BUCK2_STARTUP_TIME,
			.ramp_delay_table = bd718xx_ramp_delay,
			.n_ramp_values = ARRAY_SIZE(bd718xx_ramp_delay),
			.ramp_reg = BD718XX_REG_BUCK2_CTRL,
			.ramp_mask = BUCK_RAMPRATE_MASK,
			.owner = THIS_MODULE,
			.of_parse_cb = buck_set_hw_dvs_levels,
		पूर्ण,
		.dvs = अणु
			.level_map = ROHM_DVS_LEVEL_RUN | ROHM_DVS_LEVEL_IDLE,
			.run_reg = BD718XX_REG_BUCK2_VOLT_RUN,
			.run_mask = DVS_BUCK_RUN_MASK,
			.idle_reg = BD718XX_REG_BUCK2_VOLT_IDLE,
			.idle_mask = DVS_BUCK_RUN_MASK,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_BUCK2_CTRL,
			.mask = BD718XX_BUCK_SEL,
			.val = BD718XX_BUCK_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck3",
			.of_match = of_match_ptr("BUCK3"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_BUCK3,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD718XX_DVS_BUCK_VOLTAGE_NUM,
			.linear_ranges = bd718xx_dvs_buck_volts,
			.n_linear_ranges = ARRAY_SIZE(bd718xx_dvs_buck_volts),
			.vsel_reg = BD71837_REG_BUCK3_VOLT_RUN,
			.vsel_mask = DVS_BUCK_RUN_MASK,
			.enable_reg = BD71837_REG_BUCK3_CTRL,
			.enable_mask = BD718XX_BUCK_EN,
			.enable_समय = BD71837_BUCK3_STARTUP_TIME,
			.ramp_delay_table = bd718xx_ramp_delay,
			.n_ramp_values = ARRAY_SIZE(bd718xx_ramp_delay),
			.ramp_reg = BD71837_REG_BUCK3_CTRL,
			.ramp_mask = BUCK_RAMPRATE_MASK,
			.owner = THIS_MODULE,
			.of_parse_cb = buck_set_hw_dvs_levels,
		पूर्ण,
		.dvs = अणु
			.level_map = ROHM_DVS_LEVEL_RUN,
			.run_reg = BD71837_REG_BUCK3_VOLT_RUN,
			.run_mask = DVS_BUCK_RUN_MASK,
		पूर्ण,
		.init = अणु
			.reg = BD71837_REG_BUCK3_CTRL,
			.mask = BD718XX_BUCK_SEL,
			.val = BD718XX_BUCK_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck4",
			.of_match = of_match_ptr("BUCK4"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_BUCK4,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD718XX_DVS_BUCK_VOLTAGE_NUM,
			.linear_ranges = bd718xx_dvs_buck_volts,
			.n_linear_ranges = ARRAY_SIZE(bd718xx_dvs_buck_volts),
			.vsel_reg = BD71837_REG_BUCK4_VOLT_RUN,
			.vsel_mask = DVS_BUCK_RUN_MASK,
			.enable_reg = BD71837_REG_BUCK4_CTRL,
			.enable_mask = BD718XX_BUCK_EN,
			.enable_समय = BD71837_BUCK4_STARTUP_TIME,
			.ramp_delay_table = bd718xx_ramp_delay,
			.n_ramp_values = ARRAY_SIZE(bd718xx_ramp_delay),
			.ramp_reg = BD71837_REG_BUCK4_CTRL,
			.ramp_mask = BUCK_RAMPRATE_MASK,
			.owner = THIS_MODULE,
			.of_parse_cb = buck_set_hw_dvs_levels,
		पूर्ण,
		.dvs = अणु
			.level_map = ROHM_DVS_LEVEL_RUN,
			.run_reg = BD71837_REG_BUCK4_VOLT_RUN,
			.run_mask = DVS_BUCK_RUN_MASK,
		पूर्ण,
		.init = अणु
			.reg = BD71837_REG_BUCK4_CTRL,
			.mask = BD718XX_BUCK_SEL,
			.val = BD718XX_BUCK_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck5",
			.of_match = of_match_ptr("BUCK5"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_BUCK5,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD71837_BUCK5_VOLTAGE_NUM,
			.linear_ranges = bd71837_buck5_volts,
			.n_linear_ranges =
				ARRAY_SIZE(bd71837_buck5_volts),
			.vsel_reg = BD718XX_REG_1ST_NODVS_BUCK_VOLT,
			.vsel_mask = BD71837_BUCK5_MASK,
			.vsel_range_reg = BD718XX_REG_1ST_NODVS_BUCK_VOLT,
			.vsel_range_mask = BD71837_BUCK5_RANGE_MASK,
			.linear_range_selectors = bd71837_buck5_volt_range_sel,
			.enable_reg = BD718XX_REG_1ST_NODVS_BUCK_CTRL,
			.enable_mask = BD718XX_BUCK_EN,
			.enable_समय = BD71837_BUCK5_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_1ST_NODVS_BUCK_CTRL,
			.mask = BD718XX_BUCK_SEL,
			.val = BD718XX_BUCK_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck6",
			.of_match = of_match_ptr("BUCK6"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_BUCK6,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD71837_BUCK6_VOLTAGE_NUM,
			.linear_ranges = bd71837_buck6_volts,
			.n_linear_ranges =
				ARRAY_SIZE(bd71837_buck6_volts),
			.vsel_reg = BD718XX_REG_2ND_NODVS_BUCK_VOLT,
			.vsel_mask = BD71837_BUCK6_MASK,
			.enable_reg = BD718XX_REG_2ND_NODVS_BUCK_CTRL,
			.enable_mask = BD718XX_BUCK_EN,
			.enable_समय = BD71837_BUCK6_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_2ND_NODVS_BUCK_CTRL,
			.mask = BD718XX_BUCK_SEL,
			.val = BD718XX_BUCK_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck7",
			.of_match = of_match_ptr("BUCK7"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_BUCK7,
			.type = REGULATOR_VOLTAGE,
			.volt_table = &bd718xx_3rd_nodvs_buck_volts[0],
			.n_voltages = ARRAY_SIZE(bd718xx_3rd_nodvs_buck_volts),
			.vsel_reg = BD718XX_REG_3RD_NODVS_BUCK_VOLT,
			.vsel_mask = BD718XX_3RD_NODVS_BUCK_MASK,
			.enable_reg = BD718XX_REG_3RD_NODVS_BUCK_CTRL,
			.enable_mask = BD718XX_BUCK_EN,
			.enable_समय = BD71837_BUCK7_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_3RD_NODVS_BUCK_CTRL,
			.mask = BD718XX_BUCK_SEL,
			.val = BD718XX_BUCK_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "buck8",
			.of_match = of_match_ptr("BUCK8"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_BUCK8,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD718XX_4TH_NODVS_BUCK_VOLTAGE_NUM,
			.linear_ranges = bd718xx_4th_nodvs_buck_volts,
			.n_linear_ranges =
				ARRAY_SIZE(bd718xx_4th_nodvs_buck_volts),
			.vsel_reg = BD718XX_REG_4TH_NODVS_BUCK_VOLT,
			.vsel_mask = BD718XX_4TH_NODVS_BUCK_MASK,
			.enable_reg = BD718XX_REG_4TH_NODVS_BUCK_CTRL,
			.enable_mask = BD718XX_BUCK_EN,
			.enable_समय = BD71837_BUCK8_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_4TH_NODVS_BUCK_CTRL,
			.mask = BD718XX_BUCK_SEL,
			.val = BD718XX_BUCK_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo1",
			.of_match = of_match_ptr("LDO1"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_LDO1,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD718XX_LDO1_VOLTAGE_NUM,
			.linear_ranges = bd718xx_lकरो1_volts,
			.n_linear_ranges = ARRAY_SIZE(bd718xx_lकरो1_volts),
			.vsel_reg = BD718XX_REG_LDO1_VOLT,
			.vsel_mask = BD718XX_LDO1_MASK,
			.vsel_range_reg = BD718XX_REG_LDO1_VOLT,
			.vsel_range_mask = BD718XX_LDO1_RANGE_MASK,
			.linear_range_selectors = bd718xx_lकरो1_volt_range_sel,
			.enable_reg = BD718XX_REG_LDO1_VOLT,
			.enable_mask = BD718XX_LDO_EN,
			.enable_समय = BD71837_LDO1_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_LDO1_VOLT,
			.mask = BD718XX_LDO_SEL,
			.val = BD718XX_LDO_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo2",
			.of_match = of_match_ptr("LDO2"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_LDO2,
			.type = REGULATOR_VOLTAGE,
			.volt_table = &lकरो_2_volts[0],
			.vsel_reg = BD718XX_REG_LDO2_VOLT,
			.vsel_mask = BD718XX_LDO2_MASK,
			.n_voltages = ARRAY_SIZE(lकरो_2_volts),
			.enable_reg = BD718XX_REG_LDO2_VOLT,
			.enable_mask = BD718XX_LDO_EN,
			.enable_समय = BD71837_LDO2_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_LDO2_VOLT,
			.mask = BD718XX_LDO_SEL,
			.val = BD718XX_LDO_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo3",
			.of_match = of_match_ptr("LDO3"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_LDO3,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD718XX_LDO3_VOLTAGE_NUM,
			.linear_ranges = bd718xx_lकरो3_volts,
			.n_linear_ranges = ARRAY_SIZE(bd718xx_lकरो3_volts),
			.vsel_reg = BD718XX_REG_LDO3_VOLT,
			.vsel_mask = BD718XX_LDO3_MASK,
			.enable_reg = BD718XX_REG_LDO3_VOLT,
			.enable_mask = BD718XX_LDO_EN,
			.enable_समय = BD71837_LDO3_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_LDO3_VOLT,
			.mask = BD718XX_LDO_SEL,
			.val = BD718XX_LDO_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo4",
			.of_match = of_match_ptr("LDO4"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_LDO4,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD718XX_LDO4_VOLTAGE_NUM,
			.linear_ranges = bd718xx_lकरो4_volts,
			.n_linear_ranges = ARRAY_SIZE(bd718xx_lकरो4_volts),
			.vsel_reg = BD718XX_REG_LDO4_VOLT,
			.vsel_mask = BD718XX_LDO4_MASK,
			.enable_reg = BD718XX_REG_LDO4_VOLT,
			.enable_mask = BD718XX_LDO_EN,
			.enable_समय = BD71837_LDO4_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_LDO4_VOLT,
			.mask = BD718XX_LDO_SEL,
			.val = BD718XX_LDO_SEL,
		पूर्ण,
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo5",
			.of_match = of_match_ptr("LDO5"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_LDO5,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD71837_LDO5_VOLTAGE_NUM,
			.linear_ranges = bd71837_lकरो5_volts,
			.n_linear_ranges = ARRAY_SIZE(bd71837_lकरो5_volts),
			/* LDO5 is supplied by buck6 */
			.supply_name = "buck6",
			.vsel_reg = BD718XX_REG_LDO5_VOLT,
			.vsel_mask = BD71837_LDO5_MASK,
			.enable_reg = BD718XX_REG_LDO5_VOLT,
			.enable_mask = BD718XX_LDO_EN,
			.enable_समय = BD71837_LDO5_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_LDO5_VOLT,
			.mask = BD718XX_LDO_SEL,
			.val = BD718XX_LDO_SEL,
		पूर्ण,
		.additional_inits = bd71837_lकरो5_inits,
		.additional_init_amnt = ARRAY_SIZE(bd71837_lकरो5_inits),
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo6",
			.of_match = of_match_ptr("LDO6"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_LDO6,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD718XX_LDO6_VOLTAGE_NUM,
			.linear_ranges = bd718xx_lकरो6_volts,
			.n_linear_ranges = ARRAY_SIZE(bd718xx_lकरो6_volts),
			/* LDO6 is supplied by buck7 */
			.supply_name = "buck7",
			.vsel_reg = BD718XX_REG_LDO6_VOLT,
			.vsel_mask = BD718XX_LDO6_MASK,
			.enable_reg = BD718XX_REG_LDO6_VOLT,
			.enable_mask = BD718XX_LDO_EN,
			.enable_समय = BD71837_LDO6_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD718XX_REG_LDO6_VOLT,
			.mask = BD718XX_LDO_SEL,
			.val = BD718XX_LDO_SEL,
		पूर्ण,
		.additional_inits = bd71837_lकरो6_inits,
		.additional_init_amnt = ARRAY_SIZE(bd71837_lकरो6_inits),
	पूर्ण,
	अणु
		.desc = अणु
			.name = "ldo7",
			.of_match = of_match_ptr("LDO7"),
			.regulators_node = of_match_ptr("regulators"),
			.id = BD718XX_LDO7,
			.type = REGULATOR_VOLTAGE,
			.n_voltages = BD71837_LDO7_VOLTAGE_NUM,
			.linear_ranges = bd71837_lकरो7_volts,
			.n_linear_ranges = ARRAY_SIZE(bd71837_lकरो7_volts),
			.vsel_reg = BD71837_REG_LDO7_VOLT,
			.vsel_mask = BD71837_LDO7_MASK,
			.enable_reg = BD71837_REG_LDO7_VOLT,
			.enable_mask = BD718XX_LDO_EN,
			.enable_समय = BD71837_LDO7_STARTUP_TIME,
			.owner = THIS_MODULE,
		पूर्ण,
		.init = अणु
			.reg = BD71837_REG_LDO7_VOLT,
			.mask = BD718XX_LDO_SEL,
			.val = BD718XX_LDO_SEL,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम mark_hw_controlled(काष्ठा device *dev, काष्ठा device_node *np,
			       काष्ठा bd718xx_regulator_data *reg_data,
			       अचिन्हित पूर्णांक num_reg_data, पूर्णांक *info)
अणु
	पूर्णांक i;

	क्रम (i = 1; i <= num_reg_data; i++) अणु
		अगर (!of_node_name_eq(np, reg_data[i-1].desc.of_match))
			जारी;

		*info |= 1 << (i - 1);
		dev_dbg(dev, "regulator %d runlevel controlled\n", i);
		वापस;
	पूर्ण
	dev_warn(dev, "Bad regulator node\n");
पूर्ण

/*
 * Setups where regulator (especially the buck8) output voltage is scaled
 * by adding बाह्यal connection where some other regulator output is connected
 * to feedback-pin (over suitable resistors) is getting popular amongst users
 * of BD71837. (This allows क्रम example scaling करोwn the buck8 voltages to suit
 * lover GPU voltages क्रम projects where buck8 is (ab)used to supply घातer
 * क्रम GPU. Additionally some setups करो allow DVS क्रम buck8 but as this करो
 * produce voltage spikes the HW must be evaluated to be able to survive this
 * - hence I keep the DVS disabled क्रम non DVS bucks by शेष. I करोn't want
 * to help you burn your proto board)
 *
 * So we allow describing this बाह्यal connection from DT and scale the
 * voltages accordingly. This is what the connection should look like:
 *
 * |------------|
 * |	buck 8  |-------+----->Vout
 * |		|	|
 * |------------|	|
 *	| FB pin	|
 *	|		|
 *	+-------+--R2---+
 *		|
 *		R1
 *		|
 *	V FB-pull-up
 *
 *	Here the buck output is sअगरted according to क्रमmula:
 *
 * Vout_o = Vo - (Vpu - Vo)*R2/R1
 * Linear_step = step_orig*(R1+R2)/R1
 *
 * where:
 * Vout_o is adjusted voltage output at vsel reg value 0
 * Vo is original voltage output at vsel reg value 0
 * Vpu is the pull-up voltage V FB-pull-up in the picture
 * R1 and R2 are resistor values.
 *
 * As a real world example क्रम buck8 and a specअगरic GPU:
 * VLDO = 1.6V (used as FB-pull-up)
 * R1 = 1000ohms
 * R2 = 150ohms
 * VSEL 0x0 => 0.8V ै  (VLDO ै  0.8) * R2 / R1 = 0.68V
 * Linear Step = 10mV * (R1 + R2) / R1 = 11.5mV
 */
अटल पूर्णांक setup_feedback_loop(काष्ठा device *dev, काष्ठा device_node *np,
			       काष्ठा bd718xx_regulator_data *reg_data,
			       अचिन्हित पूर्णांक num_reg_data, पूर्णांक fb_uv)
अणु
	पूर्णांक i, r1, r2, ret;

	/*
	 * We करो adjust the values in the global desc based on DT settings.
	 * This may not be best approach as it can cause problems अगर more than
	 * one PMIC is controlled from same processor. I करोn't see such use-हाल
	 * क्रम BD718x7 now - so we spare some bits.
	 *
	 * If this will poपूर्णांक out to be a problem - then we can allocate new
	 * bd718xx_regulator_data array at probe and just use the global
	 * array as a ढाँचा where we copy initial values. Then we can
	 * use allocated descs क्रम regultor registration and करो IC specअगरic
	 * modअगरications to this copy जबतक leaving other PMICs untouched. But
	 * that means allocating new array क्रम each PMIC - and currently I see
	 * no need क्रम that.
	 */

	क्रम (i = 0; i < num_reg_data; i++) अणु
		काष्ठा regulator_desc *desc = &reg_data[i].desc;
		पूर्णांक j;

		अगर (!of_node_name_eq(np, desc->of_match))
			जारी;

		pr_info("Looking at node '%s'\n", desc->of_match);

		/* The feedback loop connection करोes not make sense क्रम LDOs */
		अगर (desc->id >= BD718XX_LDO1)
			वापस -EINVAL;

		ret = of_property_पढ़ो_u32(np, "rohm,feedback-pull-up-r1-ohms",
					   &r1);
		अगर (ret)
			वापस ret;

		अगर (!r1)
			वापस -EINVAL;

		ret = of_property_पढ़ो_u32(np, "rohm,feedback-pull-up-r2-ohms",
					   &r2);
		अगर (ret)
			वापस ret;

		अगर (desc->n_linear_ranges && desc->linear_ranges) अणु
			काष्ठा linear_range *new;

			new = devm_kzalloc(dev, desc->n_linear_ranges *
					   माप(काष्ठा linear_range),
					   GFP_KERNEL);
			अगर (!new)
				वापस -ENOMEM;

			क्रम (j = 0; j < desc->n_linear_ranges; j++) अणु
				पूर्णांक min = desc->linear_ranges[j].min;
				पूर्णांक step = desc->linear_ranges[j].step;

				min -= (fb_uv - min)*r2/r1;
				step = step * (r1 + r2);
				step /= r1;

				new[j].min = min;
				new[j].step = step;

				dev_dbg(dev, "%s: old range min %d, step %d\n",
					desc->name, desc->linear_ranges[j].min,
					desc->linear_ranges[j].step);
				dev_dbg(dev, "new range min %d, step %d\n", min,
					step);
			पूर्ण
			desc->linear_ranges = new;
		पूर्ण
		dev_dbg(dev, "regulator '%s' has FB pull-up configured\n",
			desc->name);

		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक get_special_regulators(काष्ठा device *dev,
				  काष्ठा bd718xx_regulator_data *reg_data,
				  अचिन्हित पूर्णांक num_reg_data, पूर्णांक *info)
अणु
	पूर्णांक ret;
	काष्ठा device_node *np;
	काष्ठा device_node *nproot = dev->of_node;
	पूर्णांक uv;

	*info = 0;

	nproot = of_get_child_by_name(nproot, "regulators");
	अगर (!nproot) अणु
		dev_err(dev, "failed to find regulators node\n");
		वापस -ENODEV;
	पूर्ण
	क्रम_each_child_of_node(nproot, np) अणु
		अगर (of_property_पढ़ो_bool(np, "rohm,no-regulator-enable-control"))
			mark_hw_controlled(dev, np, reg_data, num_reg_data,
					   info);
		ret = of_property_पढ़ो_u32(np, "rohm,fb-pull-up-microvolt",
					   &uv);
		अगर (ret) अणु
			अगर (ret == -EINVAL)
				जारी;
			अन्यथा
				जाओ err_out;
		पूर्ण

		ret = setup_feedback_loop(dev, np, reg_data, num_reg_data, uv);
		अगर (ret)
			जाओ err_out;
	पूर्ण

	of_node_put(nproot);
	वापस 0;

err_out:
	of_node_put(np);
	of_node_put(nproot);

	वापस ret;
पूर्ण

अटल पूर्णांक bd718xx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap;
	काष्ठा regulator_config config = अणु 0 पूर्ण;
	पूर्णांक i, j, err, omit_enable;
	bool use_snvs;
	काष्ठा bd718xx_regulator_data *reg_data;
	अचिन्हित पूर्णांक num_reg_data;
	क्रमागत rohm_chip_type chip = platक्रमm_get_device_id(pdev)->driver_data;
	स्थिर काष्ठा regulator_ops **swops, **hwops;

	regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!regmap) अणु
		dev_err(&pdev->dev, "No MFD driver data\n");
		वापस -EINVAL;
	पूर्ण

	चयन (chip) अणु
	हाल ROHM_CHIP_TYPE_BD71837:
		reg_data = bd71837_regulators;
		num_reg_data = ARRAY_SIZE(bd71837_regulators);
		swops = &bd71837_swcontrol_ops[0];
		hwops = &bd71837_hwcontrol_ops[0];
		अवरोध;
	हाल ROHM_CHIP_TYPE_BD71847:
		reg_data = bd71847_regulators;
		num_reg_data = ARRAY_SIZE(bd71847_regulators);
		swops = &bd71847_swcontrol_ops[0];
		hwops = &bd71847_hwcontrol_ops[0];
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Unsupported chip type\n");
		err = -EINVAL;
		जाओ err;
	पूर्ण

	/* Register LOCK release */
	err = regmap_update_bits(regmap, BD718XX_REG_REGLOCK,
				 (REGLOCK_PWRSEQ | REGLOCK_VREG), 0);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to unlock PMIC (%d)\n", err);
		जाओ err;
	पूर्ण अन्यथा अणु
		dev_dbg(&pdev->dev, "Unlocked lock register 0x%x\n",
			BD718XX_REG_REGLOCK);
	पूर्ण

	use_snvs = of_property_पढ़ो_bool(pdev->dev.parent->of_node,
					 "rohm,reset-snvs-powered");

	/*
	 * Change the next stage from घातeroff to be READY instead of SNVS
	 * क्रम all reset types because OTP loading at READY will clear SEL
	 * bit allowing HW शेषs क्रम घातer rails to be used
	 */
	अगर (!use_snvs) अणु
		err = regmap_update_bits(regmap, BD718XX_REG_TRANS_COND1,
					 BD718XX_ON_REQ_POWEROFF_MASK |
					 BD718XX_SWRESET_POWEROFF_MASK |
					 BD718XX_WDOG_POWEROFF_MASK |
					 BD718XX_KEY_L_POWEROFF_MASK,
					 BD718XX_POWOFF_TO_RDY);
		अगर (err) अणु
			dev_err(&pdev->dev, "Failed to change reset target\n");
			जाओ err;
		पूर्ण अन्यथा अणु
			dev_dbg(&pdev->dev,
				"Changed all resets from SVNS to READY\n");
		पूर्ण
	पूर्ण

	config.dev = pdev->dev.parent;
	config.regmap = regmap;
	/*
	 * There are हालs when we want to leave the enable-control क्रम
	 * the HW state machine and use this driver only क्रम voltage control.
	 * One special हाल is when we use PMIC_STBY_REQ line from SoC to PMIC
	 * in order to set the प्रणाली to SUSPEND state.
	 *
	 * If regulator is taken under SW control the regulator state will not
	 * be affected by PMIC state machine - Eg. regulator is likely to stay
	 * on even in SUSPEND
	 */
	err = get_special_regulators(pdev->dev.parent, reg_data, num_reg_data,
				     &omit_enable);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < num_reg_data; i++) अणु

		काष्ठा regulator_desc *desc;
		काष्ठा regulator_dev *rdev;
		काष्ठा bd718xx_regulator_data *r;
		पूर्णांक no_enable_control = omit_enable & (1 << i);

		r = &reg_data[i];
		desc = &r->desc;

		अगर (no_enable_control)
			desc->ops = hwops[i];
		अन्यथा
			desc->ops = swops[i];

		rdev = devm_regulator_रेजिस्टर(&pdev->dev, desc, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev,
				"failed to register %s regulator\n",
				desc->name);
			err = PTR_ERR(rdev);
			जाओ err;
		पूर्ण

		/*
		 * Regulator रेजिस्टर माला_लो the regulator स्थिरraपूर्णांकs and
		 * applies them (set_machine_स्थिरraपूर्णांकs). This should have
		 * turned the control रेजिस्टर(s) to correct values and we
		 * can now चयन the control from PMIC state machine to the
		 * रेजिस्टर पूर्णांकerface
		 *
		 * At घातeroff transition PMIC HW disables EN bit क्रम
		 * regulators but leaves SEL bit untouched. So अगर state
		 * transition from POWEROFF is करोne to SNVS - then all घातer
		 * rails controlled by SW (having SEL bit set) stay disabled
		 * as EN is cleared. This will result boot failure अगर any
		 * crucial प्रणालीs are घातered by these rails. We करोn't
		 * enable SW control क्रम crucial regulators अगर snvs state is
		 * used
		 */
		अगर (!no_enable_control && (!use_snvs ||
		    !rdev->स्थिरraपूर्णांकs->always_on ||
		    !rdev->स्थिरraपूर्णांकs->boot_on)) अणु
			err = regmap_update_bits(regmap, r->init.reg,
						 r->init.mask, r->init.val);
			अगर (err) अणु
				dev_err(&pdev->dev,
					"Failed to take control for (%s)\n",
					desc->name);
				जाओ err;
			पूर्ण
		पूर्ण
		क्रम (j = 0; j < r->additional_init_amnt; j++) अणु
			err = regmap_update_bits(regmap,
						 r->additional_inits[j].reg,
						 r->additional_inits[j].mask,
						 r->additional_inits[j].val);
			अगर (err) अणु
				dev_err(&pdev->dev,
					"Buck (%s) initialization failed\n",
					desc->name);
				जाओ err;
			पूर्ण
		पूर्ण
	पूर्ण

err:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id bd718x7_pmic_id[] = अणु
	अणु "bd71837-pmic", ROHM_CHIP_TYPE_BD71837 पूर्ण,
	अणु "bd71847-pmic", ROHM_CHIP_TYPE_BD71847 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, bd718x7_pmic_id);

अटल काष्ठा platक्रमm_driver bd718xx_regulator = अणु
	.driver = अणु
		.name = "bd718xx-pmic",
	पूर्ण,
	.probe = bd718xx_probe,
	.id_table = bd718x7_pmic_id,
पूर्ण;

module_platक्रमm_driver(bd718xx_regulator);

MODULE_AUTHOR("Matti Vaittinen <matti.vaittinen@fi.rohmeurope.com>");
MODULE_DESCRIPTION("BD71837/BD71847 voltage regulator driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:bd718xx-pmic");
