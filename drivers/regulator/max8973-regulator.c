<शैली गुरु>
/*
 * max8973-regulator.c -- Maxim max8973
 *
 * Regulator driver क्रम MAXIM 8973 DC-DC step-करोwn चयनing regulator.
 *
 * Copyright (c) 2012, NVIDIA Corporation.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 * whether express or implied; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307, USA
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/max8973-regulator.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>
#समावेश <linux/thermal.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>

/* Register definitions */
#घोषणा MAX8973_VOUT					0x0
#घोषणा MAX8973_VOUT_DVS				0x1
#घोषणा MAX8973_CONTROL1				0x2
#घोषणा MAX8973_CONTROL2				0x3
#घोषणा MAX8973_CHIPID1					0x4
#घोषणा MAX8973_CHIPID2					0x5

#घोषणा MAX8973_MAX_VOUT_REG				2

/* MAX8973_VOUT */
#घोषणा MAX8973_VOUT_ENABLE				BIT(7)
#घोषणा MAX8973_VOUT_MASK				0x7F

/* MAX8973_VOUT_DVS */
#घोषणा MAX8973_DVS_VOUT_MASK				0x7F

/* MAX8973_CONTROL1 */
#घोषणा MAX8973_SNS_ENABLE				BIT(7)
#घोषणा MAX8973_FPWM_EN_M				BIT(6)
#घोषणा MAX8973_NFSR_ENABLE				BIT(5)
#घोषणा MAX8973_AD_ENABLE				BIT(4)
#घोषणा MAX8973_BIAS_ENABLE				BIT(3)
#घोषणा MAX8973_FREQSHIFT_9PER				BIT(2)

#घोषणा MAX8973_RAMP_12mV_PER_US			0x0
#घोषणा MAX8973_RAMP_25mV_PER_US			0x1
#घोषणा MAX8973_RAMP_50mV_PER_US			0x2
#घोषणा MAX8973_RAMP_200mV_PER_US			0x3
#घोषणा MAX8973_RAMP_MASK				0x3

/* MAX8973_CONTROL2 */
#घोषणा MAX8973_WDTMR_ENABLE				BIT(6)
#घोषणा MAX8973_DISCH_ENBABLE				BIT(5)
#घोषणा MAX8973_FT_ENABLE				BIT(4)
#घोषणा MAX77621_T_JUNCTION_120				BIT(7)

#घोषणा MAX8973_CKKADV_TRIP_MASK			0xC
#घोषणा MAX8973_CKKADV_TRIP_DISABLE			0xC
#घोषणा MAX8973_CKKADV_TRIP_75mV_PER_US			0x0
#घोषणा MAX8973_CKKADV_TRIP_150mV_PER_US		0x4
#घोषणा MAX8973_CKKADV_TRIP_75mV_PER_US_HIST_DIS	0x8
#घोषणा MAX8973_CONTROL_CLKADV_TRIP_MASK		0x00030000

#घोषणा MAX8973_INDUCTOR_MIN_30_PER			0x0
#घोषणा MAX8973_INDUCTOR_NOMINAL			0x1
#घोषणा MAX8973_INDUCTOR_PLUS_30_PER			0x2
#घोषणा MAX8973_INDUCTOR_PLUS_60_PER			0x3
#घोषणा MAX8973_CONTROL_INDUCTOR_VALUE_MASK		0x00300000

#घोषणा MAX8973_MIN_VOLATGE				606250
#घोषणा MAX8973_MAX_VOLATGE				1400000
#घोषणा MAX8973_VOLATGE_STEP				6250
#घोषणा MAX8973_BUCK_N_VOLTAGE				0x80

#घोषणा MAX77621_CHIPID_TJINT_S				BIT(0)

#घोषणा MAX77621_NORMAL_OPERATING_TEMP			100000
#घोषणा MAX77621_TJINT_WARNING_TEMP_120			120000
#घोषणा MAX77621_TJINT_WARNING_TEMP_140			140000

क्रमागत device_id अणु
	MAX8973,
	MAX77621
पूर्ण;

/* Maxim 8973 chip inक्रमmation */
काष्ठा max8973_chip अणु
	काष्ठा device *dev;
	काष्ठा regulator_desc desc;
	काष्ठा regmap *regmap;
	bool enable_बाह्यal_control;
	पूर्णांक dvs_gpio;
	पूर्णांक lru_index[MAX8973_MAX_VOUT_REG];
	पूर्णांक curr_vout_val[MAX8973_MAX_VOUT_REG];
	पूर्णांक curr_vout_reg;
	पूर्णांक curr_gpio_val;
	काष्ठा regulator_ops ops;
	क्रमागत device_id id;
	पूर्णांक junction_temp_warning;
	पूर्णांक irq;
	काष्ठा thermal_zone_device *tz_device;
पूर्ण;

/*
 * find_voltage_set_रेजिस्टर: Find new voltage configuration रेजिस्टर (VOUT).
 * The finding of the new VOUT रेजिस्टर will be based on the LRU mechanism.
 * Each VOUT रेजिस्टर will have dअगरferent voltage configured . This
 * Function will look अगर any of the VOUT रेजिस्टर have requested voltage set
 * or not.
 *     - If it is alपढ़ोy there then it will make that रेजिस्टर as most
 *       recently used and वापस as found so that caller need not to set
 *       the VOUT रेजिस्टर but need to set the proper gpios to select this
 *       VOUT रेजिस्टर.
 *     - If requested voltage is not found then it will use the least
 *       recently mechanism to get new VOUT रेजिस्टर क्रम new configuration
 *       and will वापस not_found so that caller need to set new VOUT
 *       रेजिस्टर and then gpios (both).
 */
अटल bool find_voltage_set_रेजिस्टर(काष्ठा max8973_chip *tps,
		पूर्णांक req_vsel, पूर्णांक *vout_reg, पूर्णांक *gpio_val)
अणु
	पूर्णांक i;
	bool found = false;
	पूर्णांक new_vout_reg = tps->lru_index[MAX8973_MAX_VOUT_REG - 1];
	पूर्णांक found_index = MAX8973_MAX_VOUT_REG - 1;

	क्रम (i = 0; i < MAX8973_MAX_VOUT_REG; ++i) अणु
		अगर (tps->curr_vout_val[tps->lru_index[i]] == req_vsel) अणु
			new_vout_reg = tps->lru_index[i];
			found_index = i;
			found = true;
			जाओ update_lru_index;
		पूर्ण
	पूर्ण

update_lru_index:
	क्रम (i = found_index; i > 0; i--)
		tps->lru_index[i] = tps->lru_index[i - 1];

	tps->lru_index[0] = new_vout_reg;
	*gpio_val = new_vout_reg;
	*vout_reg = MAX8973_VOUT + new_vout_reg;
	वापस found;
पूर्ण

अटल पूर्णांक max8973_dcdc_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8973_chip *max = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक data;
	पूर्णांक ret;

	ret = regmap_पढ़ो(max->regmap, max->curr_vout_reg, &data);
	अगर (ret < 0) अणु
		dev_err(max->dev, "register %d read failed, err = %d\n",
			max->curr_vout_reg, ret);
		वापस ret;
	पूर्ण
	वापस data & MAX8973_VOUT_MASK;
पूर्ण

अटल पूर्णांक max8973_dcdc_set_voltage_sel(काष्ठा regulator_dev *rdev,
	     अचिन्हित vsel)
अणु
	काष्ठा max8973_chip *max = rdev_get_drvdata(rdev);
	पूर्णांक ret;
	bool found = false;
	पूर्णांक vout_reg = max->curr_vout_reg;
	पूर्णांक gpio_val = max->curr_gpio_val;

	/*
	 * If gpios are available to select the VOUT रेजिस्टर then least
	 * recently used रेजिस्टर क्रम new configuration.
	 */
	अगर (gpio_is_valid(max->dvs_gpio))
		found = find_voltage_set_रेजिस्टर(max, vsel,
					&vout_reg, &gpio_val);

	अगर (!found) अणु
		ret = regmap_update_bits(max->regmap, vout_reg,
					MAX8973_VOUT_MASK, vsel);
		अगर (ret < 0) अणु
			dev_err(max->dev, "register %d update failed, err %d\n",
				 vout_reg, ret);
			वापस ret;
		पूर्ण
		max->curr_vout_reg = vout_reg;
		max->curr_vout_val[gpio_val] = vsel;
	पूर्ण

	/* Select proper VOUT रेजिस्टर vio gpios */
	अगर (gpio_is_valid(max->dvs_gpio)) अणु
		gpio_set_value_cansleep(max->dvs_gpio, gpio_val & 0x1);
		max->curr_gpio_val = gpio_val;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक max8973_dcdc_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा max8973_chip *max = rdev_get_drvdata(rdev);
	पूर्णांक ret;
	पूर्णांक pwm;

	/* Enable क्रमce PWM mode in FAST mode only. */
	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		pwm = MAX8973_FPWM_EN_M;
		अवरोध;

	हाल REGULATOR_MODE_NORMAL:
		pwm = 0;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(max->regmap, MAX8973_CONTROL1,
				MAX8973_FPWM_EN_M, pwm);
	अगर (ret < 0)
		dev_err(max->dev, "register %d update failed, err %d\n",
				MAX8973_CONTROL1, ret);
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक max8973_dcdc_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8973_chip *max = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक data;
	पूर्णांक ret;

	ret = regmap_पढ़ो(max->regmap, MAX8973_CONTROL1, &data);
	अगर (ret < 0) अणु
		dev_err(max->dev, "register %d read failed, err %d\n",
				MAX8973_CONTROL1, ret);
		वापस ret;
	पूर्ण
	वापस (data & MAX8973_FPWM_EN_M) ?
		REGULATOR_MODE_FAST : REGULATOR_MODE_NORMAL;
पूर्ण

अटल पूर्णांक max8973_set_ramp_delay(काष्ठा regulator_dev *rdev,
		पूर्णांक ramp_delay)
अणु
	काष्ठा max8973_chip *max = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक control;
	पूर्णांक ret;

	/* Set ramp delay */
	अगर (ramp_delay <= 12000)
		control = MAX8973_RAMP_12mV_PER_US;
	अन्यथा अगर (ramp_delay <= 25000)
		control = MAX8973_RAMP_25mV_PER_US;
	अन्यथा अगर (ramp_delay <= 50000)
		control = MAX8973_RAMP_50mV_PER_US;
	अन्यथा अगर (ramp_delay <= 200000)
		control = MAX8973_RAMP_200mV_PER_US;
	अन्यथा
		वापस -EINVAL;

	ret = regmap_update_bits(max->regmap, MAX8973_CONTROL1,
			MAX8973_RAMP_MASK, control);
	अगर (ret < 0)
		dev_err(max->dev, "register %d update failed, %d",
				MAX8973_CONTROL1, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक max8973_set_current_limit(काष्ठा regulator_dev *rdev,
		पूर्णांक min_ua, पूर्णांक max_ua)
अणु
	काष्ठा max8973_chip *max = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (max_ua <= 9000000)
		val = MAX8973_CKKADV_TRIP_75mV_PER_US;
	अन्यथा अगर (max_ua <= 12000000)
		val = MAX8973_CKKADV_TRIP_150mV_PER_US;
	अन्यथा
		val = MAX8973_CKKADV_TRIP_DISABLE;

	ret = regmap_update_bits(max->regmap, MAX8973_CONTROL2,
			MAX8973_CKKADV_TRIP_MASK, val);
	अगर (ret < 0) अणु
		dev_err(max->dev, "register %d update failed: %d\n",
				MAX8973_CONTROL2, ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक max8973_get_current_limit(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max8973_chip *max = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक control2;
	पूर्णांक ret;

	ret = regmap_पढ़ो(max->regmap, MAX8973_CONTROL2, &control2);
	अगर (ret < 0) अणु
		dev_err(max->dev, "register %d read failed: %d\n",
				MAX8973_CONTROL2, ret);
		वापस ret;
	पूर्ण
	चयन (control2 & MAX8973_CKKADV_TRIP_MASK) अणु
	हाल MAX8973_CKKADV_TRIP_DISABLE:
		वापस 15000000;
	हाल MAX8973_CKKADV_TRIP_150mV_PER_US:
		वापस 12000000;
	हाल MAX8973_CKKADV_TRIP_75mV_PER_US:
		वापस 9000000;
	शेष:
		अवरोध;
	पूर्ण
	वापस 9000000;
पूर्ण

अटल स्थिर काष्ठा regulator_ops max8973_dcdc_ops = अणु
	.get_voltage_sel	= max8973_dcdc_get_voltage_sel,
	.set_voltage_sel	= max8973_dcdc_set_voltage_sel,
	.list_voltage		= regulator_list_voltage_linear,
	.set_mode		= max8973_dcdc_set_mode,
	.get_mode		= max8973_dcdc_get_mode,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_ramp_delay		= max8973_set_ramp_delay,
पूर्ण;

अटल पूर्णांक max8973_init_dcdc(काष्ठा max8973_chip *max,
			     काष्ठा max8973_regulator_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;
	uपूर्णांक8_t	control1 = 0;
	uपूर्णांक8_t control2 = 0;
	अचिन्हित पूर्णांक data;

	ret = regmap_पढ़ो(max->regmap, MAX8973_CONTROL1, &data);
	अगर (ret < 0) अणु
		dev_err(max->dev, "register %d read failed, err = %d",
				MAX8973_CONTROL1, ret);
		वापस ret;
	पूर्ण
	control1 = data & MAX8973_RAMP_MASK;
	चयन (control1) अणु
	हाल MAX8973_RAMP_12mV_PER_US:
		max->desc.ramp_delay = 12000;
		अवरोध;
	हाल MAX8973_RAMP_25mV_PER_US:
		max->desc.ramp_delay = 25000;
		अवरोध;
	हाल MAX8973_RAMP_50mV_PER_US:
		max->desc.ramp_delay = 50000;
		अवरोध;
	हाल MAX8973_RAMP_200mV_PER_US:
		max->desc.ramp_delay = 200000;
		अवरोध;
	पूर्ण

	अगर (pdata->control_flags & MAX8973_CONTROL_REMOTE_SENSE_ENABLE)
		control1 |= MAX8973_SNS_ENABLE;

	अगर (!(pdata->control_flags & MAX8973_CONTROL_FALLING_SLEW_RATE_ENABLE))
		control1 |= MAX8973_NFSR_ENABLE;

	अगर (pdata->control_flags & MAX8973_CONTROL_OUTPUT_ACTIVE_DISCH_ENABLE)
		control1 |= MAX8973_AD_ENABLE;

	अगर (pdata->control_flags & MAX8973_CONTROL_BIAS_ENABLE) अणु
		control1 |= MAX8973_BIAS_ENABLE;
		max->desc.enable_समय = 20;
	पूर्ण अन्यथा अणु
		max->desc.enable_समय = 240;
	पूर्ण

	अगर (pdata->control_flags & MAX8973_CONTROL_FREQ_SHIFT_9PER_ENABLE)
		control1 |= MAX8973_FREQSHIFT_9PER;

	अगर ((pdata->junction_temp_warning == MAX77621_TJINT_WARNING_TEMP_120) &&
	    (max->id == MAX77621))
		control2 |= MAX77621_T_JUNCTION_120;

	अगर (!(pdata->control_flags & MAX8973_CONTROL_PULL_DOWN_ENABLE))
		control2 |= MAX8973_DISCH_ENBABLE;

	/*  Clock advance trip configuration */
	चयन (pdata->control_flags & MAX8973_CONTROL_CLKADV_TRIP_MASK) अणु
	हाल MAX8973_CONTROL_CLKADV_TRIP_DISABLED:
		control2 |= MAX8973_CKKADV_TRIP_DISABLE;
		अवरोध;

	हाल MAX8973_CONTROL_CLKADV_TRIP_75mV_PER_US:
		control2 |= MAX8973_CKKADV_TRIP_75mV_PER_US;
		अवरोध;

	हाल MAX8973_CONTROL_CLKADV_TRIP_150mV_PER_US:
		control2 |= MAX8973_CKKADV_TRIP_150mV_PER_US;
		अवरोध;

	हाल MAX8973_CONTROL_CLKADV_TRIP_75mV_PER_US_HIST_DIS:
		control2 |= MAX8973_CKKADV_TRIP_75mV_PER_US_HIST_DIS;
		अवरोध;
	पूर्ण

	/* Configure inductor value */
	चयन (pdata->control_flags & MAX8973_CONTROL_INDUCTOR_VALUE_MASK) अणु
	हाल MAX8973_CONTROL_INDUCTOR_VALUE_NOMINAL:
		control2 |= MAX8973_INDUCTOR_NOMINAL;
		अवरोध;

	हाल MAX8973_CONTROL_INDUCTOR_VALUE_MINUS_30_PER:
		control2 |= MAX8973_INDUCTOR_MIN_30_PER;
		अवरोध;

	हाल MAX8973_CONTROL_INDUCTOR_VALUE_PLUS_30_PER:
		control2 |= MAX8973_INDUCTOR_PLUS_30_PER;
		अवरोध;

	हाल MAX8973_CONTROL_INDUCTOR_VALUE_PLUS_60_PER:
		control2 |= MAX8973_INDUCTOR_PLUS_60_PER;
		अवरोध;
	पूर्ण

	ret = regmap_ग_लिखो(max->regmap, MAX8973_CONTROL1, control1);
	अगर (ret < 0) अणु
		dev_err(max->dev, "register %d write failed, err = %d",
				MAX8973_CONTROL1, ret);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(max->regmap, MAX8973_CONTROL2, control2);
	अगर (ret < 0) अणु
		dev_err(max->dev, "register %d write failed, err = %d",
				MAX8973_CONTROL2, ret);
		वापस ret;
	पूर्ण

	/* If बाह्यal control is enabled then disable EN bit */
	अगर (max->enable_बाह्यal_control && (max->id == MAX8973)) अणु
		ret = regmap_update_bits(max->regmap, MAX8973_VOUT,
						MAX8973_VOUT_ENABLE, 0);
		अगर (ret < 0)
			dev_err(max->dev, "register %d update failed, err = %d",
				MAX8973_VOUT, ret);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक max8973_thermal_पढ़ो_temp(व्योम *data, पूर्णांक *temp)
अणु
	काष्ठा max8973_chip *mchip = data;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(mchip->regmap, MAX8973_CHIPID1, &val);
	अगर (ret < 0) अणु
		dev_err(mchip->dev, "Failed to read register CHIPID1, %d", ret);
		वापस ret;
	पूर्ण

	/* +1 degC to trigger cool devive */
	अगर (val & MAX77621_CHIPID_TJINT_S)
		*temp = mchip->junction_temp_warning + 1000;
	अन्यथा
		*temp = MAX77621_NORMAL_OPERATING_TEMP;

	वापस 0;
पूर्ण

अटल irqवापस_t max8973_thermal_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा max8973_chip *mchip = data;

	thermal_zone_device_update(mchip->tz_device,
				   THERMAL_EVENT_UNSPECIFIED);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops max77621_tz_ops = अणु
	.get_temp = max8973_thermal_पढ़ो_temp,
पूर्ण;

अटल पूर्णांक max8973_thermal_init(काष्ठा max8973_chip *mchip)
अणु
	काष्ठा thermal_zone_device *tzd;
	काष्ठा irq_data *irq_data;
	अचिन्हित दीर्घ irq_flags = 0;
	पूर्णांक ret;

	अगर (mchip->id != MAX77621)
		वापस 0;

	tzd = devm_thermal_zone_of_sensor_रेजिस्टर(mchip->dev, 0, mchip,
						   &max77621_tz_ops);
	अगर (IS_ERR(tzd)) अणु
		ret = PTR_ERR(tzd);
		dev_err(mchip->dev, "Failed to register thermal sensor: %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (mchip->irq <= 0)
		वापस 0;

	irq_data = irq_get_irq_data(mchip->irq);
	अगर (irq_data)
		irq_flags = irqd_get_trigger_type(irq_data);

	ret = devm_request_thपढ़ोed_irq(mchip->dev, mchip->irq, शून्य,
					max8973_thermal_irq,
					IRQF_ONESHOT | IRQF_SHARED | irq_flags,
					dev_name(mchip->dev), mchip);
	अगर (ret < 0) अणु
		dev_err(mchip->dev, "Failed to request irq %d, %d\n",
			mchip->irq, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config max8973_regmap_config = अणु
	.reg_bits		= 8,
	.val_bits		= 8,
	.max_रेजिस्टर		= MAX8973_CHIPID2,
	.cache_type		= REGCACHE_RBTREE,
पूर्ण;

अटल काष्ठा max8973_regulator_platक्रमm_data *max8973_parse_dt(
		काष्ठा device *dev)
अणु
	काष्ठा max8973_regulator_platक्रमm_data *pdata;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;
	u32 pval;
	bool etr_enable;
	bool etr_sensitivity_high;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	pdata->enable_ext_control = of_property_पढ़ो_bool(np,
						"maxim,externally-enable");
	pdata->dvs_gpio = of_get_named_gpio(np, "maxim,dvs-gpio", 0);

	ret = of_property_पढ़ो_u32(np, "maxim,dvs-default-state", &pval);
	अगर (!ret)
		pdata->dvs_def_state = pval;

	अगर (of_property_पढ़ो_bool(np, "maxim,enable-remote-sense"))
		pdata->control_flags  |= MAX8973_CONTROL_REMOTE_SENSE_ENABLE;

	अगर (of_property_पढ़ो_bool(np, "maxim,enable-falling-slew-rate"))
		pdata->control_flags  |=
				MAX8973_CONTROL_FALLING_SLEW_RATE_ENABLE;

	अगर (of_property_पढ़ो_bool(np, "maxim,enable-active-discharge"))
		pdata->control_flags  |=
				MAX8973_CONTROL_OUTPUT_ACTIVE_DISCH_ENABLE;

	अगर (of_property_पढ़ो_bool(np, "maxim,enable-frequency-shift"))
		pdata->control_flags  |= MAX8973_CONTROL_FREQ_SHIFT_9PER_ENABLE;

	अगर (of_property_पढ़ो_bool(np, "maxim,enable-bias-control"))
		pdata->control_flags  |= MAX8973_CONTROL_BIAS_ENABLE;

	etr_enable = of_property_पढ़ो_bool(np, "maxim,enable-etr");
	etr_sensitivity_high = of_property_पढ़ो_bool(np,
				"maxim,enable-high-etr-sensitivity");
	अगर (etr_sensitivity_high)
		etr_enable = true;

	अगर (etr_enable) अणु
		अगर (etr_sensitivity_high)
			pdata->control_flags |=
				MAX8973_CONTROL_CLKADV_TRIP_75mV_PER_US;
		अन्यथा
			pdata->control_flags |=
				MAX8973_CONTROL_CLKADV_TRIP_150mV_PER_US;
	पूर्ण अन्यथा अणु
		pdata->control_flags |= MAX8973_CONTROL_CLKADV_TRIP_DISABLED;
	पूर्ण

	pdata->junction_temp_warning = MAX77621_TJINT_WARNING_TEMP_140;
	ret = of_property_पढ़ो_u32(np, "junction-warn-millicelsius", &pval);
	अगर (!ret && (pval <= MAX77621_TJINT_WARNING_TEMP_120))
		pdata->junction_temp_warning = MAX77621_TJINT_WARNING_TEMP_120;

	वापस pdata;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_max8973_match_tbl[] = अणु
	अणु .compatible = "maxim,max8973", .data = (व्योम *)MAX8973, पूर्ण,
	अणु .compatible = "maxim,max77621", .data = (व्योम *)MAX77621, पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_max8973_match_tbl);

अटल पूर्णांक max8973_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max8973_regulator_platक्रमm_data *pdata;
	काष्ठा regulator_init_data *ridata;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	काष्ठा max8973_chip *max;
	bool pdata_from_dt = false;
	अचिन्हित पूर्णांक chip_id;
	काष्ठा gpio_desc *gpiod;
	क्रमागत gpiod_flags gflags;
	पूर्णांक ret;

	pdata = dev_get_platdata(&client->dev);

	अगर (!pdata && client->dev.of_node) अणु
		pdata = max8973_parse_dt(&client->dev);
		pdata_from_dt = true;
	पूर्ण

	अगर (!pdata) अणु
		dev_err(&client->dev, "No Platform data");
		वापस -EIO;
	पूर्ण

	अगर (pdata->dvs_gpio == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	max = devm_kzalloc(&client->dev, माप(*max), GFP_KERNEL);
	अगर (!max)
		वापस -ENOMEM;

	max->regmap = devm_regmap_init_i2c(client, &max8973_regmap_config);
	अगर (IS_ERR(max->regmap)) अणु
		ret = PTR_ERR(max->regmap);
		dev_err(&client->dev, "regmap init failed, err %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (client->dev.of_node) अणु
		स्थिर काष्ठा of_device_id *match;

		match = of_match_device(of_match_ptr(of_max8973_match_tbl),
				&client->dev);
		अगर (!match)
			वापस -ENODATA;
		max->id = (u32)((uपूर्णांकptr_t)match->data);
	पूर्ण अन्यथा अणु
		max->id = id->driver_data;
	पूर्ण

	ret = regmap_पढ़ो(max->regmap, MAX8973_CHIPID1, &chip_id);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "register CHIPID1 read failed, %d", ret);
		वापस ret;
	पूर्ण

	dev_info(&client->dev, "CHIP-ID OTP: 0x%02x ID_M: 0x%02x\n",
			(chip_id >> 4) & 0xF, (chip_id >> 1) & 0x7);

	i2c_set_clientdata(client, max);
	max->ops = max8973_dcdc_ops;
	max->dev = &client->dev;
	max->desc.name = id->name;
	max->desc.id = 0;
	max->desc.ops = &max->ops;
	max->desc.type = REGULATOR_VOLTAGE;
	max->desc.owner = THIS_MODULE;
	max->desc.min_uV = MAX8973_MIN_VOLATGE;
	max->desc.uV_step = MAX8973_VOLATGE_STEP;
	max->desc.n_voltages = MAX8973_BUCK_N_VOLTAGE;

	max->dvs_gpio = (pdata->dvs_gpio) ? pdata->dvs_gpio : -EINVAL;
	max->enable_बाह्यal_control = pdata->enable_ext_control;
	max->curr_gpio_val = pdata->dvs_def_state;
	max->curr_vout_reg = MAX8973_VOUT + pdata->dvs_def_state;
	max->junction_temp_warning = pdata->junction_temp_warning;

	max->lru_index[0] = max->curr_vout_reg;

	अगर (gpio_is_valid(max->dvs_gpio)) अणु
		पूर्णांक gpio_flags;
		पूर्णांक i;

		gpio_flags = (pdata->dvs_def_state) ?
				GPIOF_OUT_INIT_HIGH : GPIOF_OUT_INIT_LOW;
		ret = devm_gpio_request_one(&client->dev, max->dvs_gpio,
				gpio_flags, "max8973-dvs");
		अगर (ret) अणु
			dev_err(&client->dev,
				"gpio_request for gpio %d failed, err = %d\n",
				max->dvs_gpio, ret);
			वापस ret;
		पूर्ण

		/*
		 * Initialize the lru index with vout_reg id
		 * The index 0 will be most recently used and
		 * set with the max->curr_vout_reg */
		क्रम (i = 0; i < MAX8973_MAX_VOUT_REG; ++i)
			max->lru_index[i] = i;
		max->lru_index[0] = max->curr_vout_reg;
		max->lru_index[max->curr_vout_reg] = 0;
	पूर्ण अन्यथा अणु
		/*
		 * If there is no DVS GPIO, the VOUT रेजिस्टर
		 * address is fixed.
		 */
		max->ops.set_voltage_sel = regulator_set_voltage_sel_regmap;
		max->ops.get_voltage_sel = regulator_get_voltage_sel_regmap;
		max->desc.vsel_reg = max->curr_vout_reg;
		max->desc.vsel_mask = MAX8973_VOUT_MASK;
	पूर्ण

	अगर (pdata_from_dt)
		pdata->reg_init_data = of_get_regulator_init_data(&client->dev,
					client->dev.of_node, &max->desc);

	ridata = pdata->reg_init_data;
	चयन (max->id) अणु
	हाल MAX8973:
		अगर (!pdata->enable_ext_control) अणु
			max->desc.enable_reg = MAX8973_VOUT;
			max->desc.enable_mask = MAX8973_VOUT_ENABLE;
			max->ops.enable = regulator_enable_regmap;
			max->ops.disable = regulator_disable_regmap;
			max->ops.is_enabled = regulator_is_enabled_regmap;
			अवरोध;
		पूर्ण

		अगर (ridata && (ridata->स्थिरraपूर्णांकs.always_on ||
			       ridata->स्थिरraपूर्णांकs.boot_on))
			gflags = GPIOD_OUT_HIGH;
		अन्यथा
			gflags = GPIOD_OUT_LOW;
		gflags |= GPIOD_FLAGS_BIT_NONEXCLUSIVE;
		gpiod = devm_gpiod_get_optional(&client->dev,
						"maxim,enable",
						gflags);
		अगर (IS_ERR(gpiod))
			वापस PTR_ERR(gpiod);
		अगर (gpiod) अणु
			config.ena_gpiod = gpiod;
			max->enable_बाह्यal_control = true;
		पूर्ण

		अवरोध;

	हाल MAX77621:
		/*
		 * We करो not let the core चयन this regulator on/off,
		 * we just leave it on.
		 */
		gpiod = devm_gpiod_get_optional(&client->dev,
						"maxim,enable",
						GPIOD_OUT_HIGH);
		अगर (IS_ERR(gpiod))
			वापस PTR_ERR(gpiod);
		अगर (gpiod)
			max->enable_बाह्यal_control = true;

		max->desc.enable_reg = MAX8973_VOUT;
		max->desc.enable_mask = MAX8973_VOUT_ENABLE;
		max->ops.enable = regulator_enable_regmap;
		max->ops.disable = regulator_disable_regmap;
		max->ops.is_enabled = regulator_is_enabled_regmap;
		max->ops.set_current_limit = max8973_set_current_limit;
		max->ops.get_current_limit = max8973_get_current_limit;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ret = max8973_init_dcdc(max, pdata);
	अगर (ret < 0) अणु
		dev_err(max->dev, "Max8973 Init failed, err = %d\n", ret);
		वापस ret;
	पूर्ण

	config.dev = &client->dev;
	config.init_data = pdata->reg_init_data;
	config.driver_data = max;
	config.of_node = client->dev.of_node;
	config.regmap = max->regmap;

	/*
	 * Register the regulators
	 * Turn the GPIO descriptor over to the regulator core क्रम
	 * lअगरecycle management अगर we pass an ena_gpiod.
	 */
	अगर (config.ena_gpiod)
		devm_gpiod_unhinge(&client->dev, config.ena_gpiod);
	rdev = devm_regulator_रेजिस्टर(&client->dev, &max->desc, &config);
	अगर (IS_ERR(rdev)) अणु
		ret = PTR_ERR(rdev);
		dev_err(max->dev, "regulator register failed, err %d\n", ret);
		वापस ret;
	पूर्ण

	max8973_thermal_init(max);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max8973_id[] = अणु
	अणु.name = "max8973", .driver_data = MAX8973पूर्ण,
	अणु.name = "max77621", .driver_data = MAX77621पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max8973_id);

अटल काष्ठा i2c_driver max8973_i2c_driver = अणु
	.driver = अणु
		.name = "max8973",
		.of_match_table = of_max8973_match_tbl,
	पूर्ण,
	.probe = max8973_probe,
	.id_table = max8973_id,
पूर्ण;

अटल पूर्णांक __init max8973_init(व्योम)
अणु
	वापस i2c_add_driver(&max8973_i2c_driver);
पूर्ण
subsys_initcall(max8973_init);

अटल व्योम __निकास max8973_cleanup(व्योम)
अणु
	i2c_del_driver(&max8973_i2c_driver);
पूर्ण
module_निकास(max8973_cleanup);

MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_DESCRIPTION("MAX8973 voltage regulator driver");
MODULE_LICENSE("GPL v2");
