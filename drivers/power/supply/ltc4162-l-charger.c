<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Analog Devices (Linear Technology) LTC4162-L अक्षरger IC.
 *  Copyright (C) 2020, Topic Embedded Products
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>

/* Registers (names based on what datasheet uses) */
#घोषणा LTC4162L_EN_LIMIT_ALERTS_REG		0x0D
#घोषणा LTC4162L_EN_CHARGER_STATE_ALERTS_REG	0x0E
#घोषणा LTC4162L_EN_CHARGE_STATUS_ALERTS_REG	0x0F
#घोषणा LTC4162L_CONFIG_BITS_REG		0x14
#घोषणा LTC4162L_IIN_LIMIT_TARGET		0x15
#घोषणा LTC4162L_ARM_SHIP_MODE			0x19
#घोषणा LTC4162L_CHARGE_CURRENT_SETTING		0X1A
#घोषणा LTC4162L_VCHARGE_SETTING		0X1B
#घोषणा LTC4162L_C_OVER_X_THRESHOLD		0x1C
#घोषणा LTC4162L_MAX_CV_TIME			0X1D
#घोषणा LTC4162L_MAX_CHARGE_TIME		0X1E
#घोषणा LTC4162L_CHARGER_CONFIG_BITS		0x29
#घोषणा LTC4162L_CHARGER_STATE			0x34
#घोषणा LTC4162L_CHARGE_STATUS			0x35
#घोषणा LTC4162L_LIMIT_ALERTS_REG		0x36
#घोषणा LTC4162L_CHARGER_STATE_ALERTS_REG	0x37
#घोषणा LTC4162L_CHARGE_STATUS_ALERTS_REG	0x38
#घोषणा LTC4162L_SYSTEM_STATUS_REG		0x39
#घोषणा LTC4162L_VBAT				0x3A
#घोषणा LTC4162L_VIN				0x3B
#घोषणा LTC4162L_VOUT				0x3C
#घोषणा LTC4162L_IBAT				0x3D
#घोषणा LTC4162L_IIN				0x3E
#घोषणा LTC4162L_DIE_TEMPERATURE		0x3F
#घोषणा LTC4162L_THERMISTOR_VOLTAGE		0x40
#घोषणा LTC4162L_BSR				0x41
#घोषणा LTC4162L_JEITA_REGION			0x42
#घोषणा LTC4162L_CHEM_CELLS_REG			0x43
#घोषणा LTC4162L_ICHARGE_DAC			0x44
#घोषणा LTC4162L_VCHARGE_DAC			0x45
#घोषणा LTC4162L_IIN_LIMIT_DAC			0x46
#घोषणा LTC4162L_VBAT_FILT			0x47
#घोषणा LTC4162L_INPUT_UNDERVOLTAGE_DAC		0x4B

/* Enumeration as in datasheet. Inभागidual bits are mutually exclusive. */
क्रमागत ltc4162l_state अणु
	battery_detection = 2048,
	अक्षरger_suspended = 256,
	preअक्षरge = 128,   /* trickle on low bat voltage */
	cc_cv_अक्षरge = 64, /* normal अक्षरge */
	ntc_छोड़ो = 32,
	समयr_term = 16,
	c_over_x_term = 8, /* battery is full */
	max_अक्षरge_समय_fault = 4,
	bat_missing_fault = 2,
	bat_लघु_fault = 1
पूर्ण;

/* Inभागidual bits are mutually exclusive. Only active in अक्षरging states.*/
क्रमागत ltc4162l_अक्षरge_status अणु
	ilim_reg_active = 32,
	thermal_reg_active = 16,
	vin_uvcl_active = 8,
	iin_limit_active = 4,
	स्थिरant_current = 2,
	स्थिरant_voltage = 1,
	अक्षरger_off = 0
पूर्ण;

/* Magic number to ग_लिखो to ARM_SHIP_MODE रेजिस्टर */
#घोषणा LTC4162L_ARM_SHIP_MODE_MAGIC 21325

काष्ठा ltc4162l_info अणु
	काष्ठा i2c_client	*client;
	काष्ठा regmap		*regmap;
	काष्ठा घातer_supply	*अक्षरger;
	u32 rsnsb;	/* Series resistor that sets अक्षरge current, microOhm */
	u32 rsnsi;	/* Series resistor to measure input current, microOhm */
	u8 cell_count;	/* Number of connected cells, 0 जबतक unknown */
पूर्ण;

अटल u8 ltc4162l_get_cell_count(काष्ठा ltc4162l_info *info)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	/* Once पढ़ो successfully */
	अगर (info->cell_count)
		वापस info->cell_count;

	ret = regmap_पढ़ो(info->regmap, LTC4162L_CHEM_CELLS_REG, &val);
	अगर (ret)
		वापस 0;

	/* Lower 4 bits is the cell count, or 0 अगर the chip करोesn't know yet */
	val &= 0x0f;
	अगर (!val)
		वापस 0;

	/* Once determined, keep the value */
	info->cell_count = val;

	वापस val;
पूर्ण;

/* Convert क्रमागत value to POWER_SUPPLY_STATUS value */
अटल पूर्णांक ltc4162l_state_decode(क्रमागत ltc4162l_state value)
अणु
	चयन (value) अणु
	हाल preअक्षरge:
	हाल cc_cv_अक्षरge:
		वापस POWER_SUPPLY_STATUS_CHARGING;
	हाल c_over_x_term:
		वापस POWER_SUPPLY_STATUS_FULL;
	हाल bat_missing_fault:
	हाल bat_लघु_fault:
		वापस POWER_SUPPLY_STATUS_UNKNOWN;
	शेष:
		वापस POWER_SUPPLY_STATUS_NOT_CHARGING;
	पूर्ण
पूर्ण;

अटल पूर्णांक ltc4162l_get_status(काष्ठा ltc4162l_info *info,
			       जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, LTC4162L_CHARGER_STATE, &regval);
	अगर (ret) अणु
		dev_err(&info->client->dev, "Failed to read CHARGER_STATE\n");
		वापस ret;
	पूर्ण

	val->पूर्णांकval = ltc4162l_state_decode(regval);

	वापस 0;
पूर्ण

अटल पूर्णांक ltc4162l_अक्षरge_status_decode(क्रमागत ltc4162l_अक्षरge_status value)
अणु
	अगर (!value)
		वापस POWER_SUPPLY_CHARGE_TYPE_NONE;

	/* स्थिरant voltage/current and input_current limit are "fast" modes */
	अगर (value <= iin_limit_active)
		वापस POWER_SUPPLY_CHARGE_TYPE_FAST;

	/* Anything that's not fast we'll वापस as trickle */
	वापस POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
पूर्ण

अटल पूर्णांक ltc4162l_get_अक्षरge_type(काष्ठा ltc4162l_info *info,
				    जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, LTC4162L_CHARGE_STATUS, &regval);
	अगर (ret)
		वापस ret;

	val->पूर्णांकval = ltc4162l_अक्षरge_status_decode(regval);

	वापस 0;
पूर्ण

अटल पूर्णांक ltc4162l_state_to_health(क्रमागत ltc4162l_state value)
अणु
	चयन (value) अणु
	हाल ntc_छोड़ो:
		वापस POWER_SUPPLY_HEALTH_OVERHEAT;
	हाल समयr_term:
		वापस POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE;
	हाल max_अक्षरge_समय_fault:
		वापस POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE;
	हाल bat_missing_fault:
		वापस POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
	हाल bat_लघु_fault:
		वापस POWER_SUPPLY_HEALTH_DEAD;
	शेष:
		वापस POWER_SUPPLY_HEALTH_GOOD;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc4162l_get_health(काष्ठा ltc4162l_info *info,
			       जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, LTC4162L_CHARGER_STATE, &regval);
	अगर (ret)
		वापस ret;

	val->पूर्णांकval = ltc4162l_state_to_health(regval);

	वापस 0;
पूर्ण

अटल पूर्णांक ltc4162l_get_online(काष्ठा ltc4162l_info *info,
			       जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, LTC4162L_SYSTEM_STATUS_REG, &regval);
	अगर (ret)
		वापस ret;

	/* BIT(2) indicates अगर input voltage is sufficient to अक्षरge */
	val->पूर्णांकval = !!(regval & BIT(2));

	वापस 0;
पूर्ण

अटल पूर्णांक ltc4162l_get_vbat(काष्ठा ltc4162l_info *info,
				  अचिन्हित पूर्णांक reg,
				  जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, reg, &regval);
	अगर (ret)
		वापस ret;

	/* cell_count थ 192.4NञV/LSB */
	regval *= 1924;
	regval *= ltc4162l_get_cell_count(info);
	regval /= 10;
	val->पूर्णांकval = regval;

	वापस 0;
पूर्ण

अटल पूर्णांक ltc4162l_get_ibat(काष्ठा ltc4162l_info *info,
			     जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, LTC4162L_IBAT, &regval);
	अगर (ret)
		वापस ret;

	/* Signed 16-bit number, 1.466NञV / RSNSB amperes/LSB. */
	ret = (s16)(regval & 0xFFFF);
	val->पूर्णांकval = 100 * mult_frac(ret, 14660, (पूर्णांक)info->rsnsb);

	वापस 0;
पूर्ण


अटल पूर्णांक ltc4162l_get_input_voltage(काष्ठा ltc4162l_info *info,
				      जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, LTC4162L_VIN, &regval);
	अगर (ret)
		वापस ret;

	/* 1.649mV/LSB */
	val->पूर्णांकval =  regval * 1694;

	वापस 0;
पूर्ण

अटल पूर्णांक ltc4162l_get_input_current(काष्ठा ltc4162l_info *info,
				      जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, LTC4162L_IIN, &regval);
	अगर (ret)
		वापस ret;

	/* Signed 16-bit number, 1.466NञV / RSNSI amperes/LSB. */
	ret = (s16)(regval & 0xFFFF);
	ret *= 14660;
	ret /= info->rsnsi;
	ret *= 100;

	val->पूर्णांकval = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ltc4162l_get_iअक्षरge(काष्ठा ltc4162l_info *info,
				अचिन्हित पूर्णांक reg,
				जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, reg, &regval);
	अगर (ret)
		वापस ret;

	regval &= BIT(6) - 1; /* Only the lower 5 bits */

	/* The अक्षरge current servo level: (iअक्षरge_dac + 1) थ 1mV/RSNSB */
	++regval;
	val->पूर्णांकval = 10000u * mult_frac(regval, 100000u, info->rsnsb);

	वापस 0;
पूर्ण

अटल पूर्णांक ltc4162l_set_iअक्षरge(काष्ठा ltc4162l_info *info,
				अचिन्हित पूर्णांक reg,
				अचिन्हित पूर्णांक value)
अणु
	value = mult_frac(value, info->rsnsb, 100000u);
	value /= 10000u;

	/* Round to lowest possible */
	अगर (value)
		--value;

	अगर (value > 31)
		वापस -EINVAL;

	वापस regmap_ग_लिखो(info->regmap, reg, value);
पूर्ण


अटल पूर्णांक ltc4162l_get_vअक्षरge(काष्ठा ltc4162l_info *info,
				अचिन्हित पूर्णांक reg,
				जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;
	u32 voltage;

	ret = regmap_पढ़ो(info->regmap, reg, &regval);
	अगर (ret)
		वापस ret;

	regval &= BIT(6) - 1; /* Only the lower 5 bits */

	/*
	 * अक्षरge voltage setting can be computed from
	 * cell_count थ (vअक्षरge_setting थ 12.5mV + 3.8125V)
	 * where vअक्षरge_setting ranges from 0 to 31 (4.2V max).
	 */
	voltage = 3812500 + (regval * 12500);
	voltage *= ltc4162l_get_cell_count(info);
	val->पूर्णांकval = voltage;

	वापस 0;
पूर्ण

अटल पूर्णांक ltc4162l_set_vअक्षरge(काष्ठा ltc4162l_info *info,
				अचिन्हित पूर्णांक reg,
				अचिन्हित पूर्णांक value)
अणु
	u8 cell_count = ltc4162l_get_cell_count(info);

	अगर (!cell_count)
		वापस -EBUSY; /* Not available yet, try again later */

	value /= cell_count;

	अगर (value < 3812500)
		वापस -EINVAL;

	value -= 3812500;
	value /= 12500;

	अगर (value > 31)
		वापस -EINVAL;

	वापस regmap_ग_लिखो(info->regmap, reg, value);
पूर्ण

अटल पूर्णांक ltc4162l_get_iin_limit_dac(काष्ठा ltc4162l_info *info,
				     जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, LTC4162L_IIN_LIMIT_DAC, &regval);
	अगर (ret)
		वापस ret;

	regval &= BIT(6) - 1; /* Only 6 bits */

	/* (iin_limit_dac + 1) थ 500NञV / RSNSI */
	++regval;
	regval *= 5000000u;
	regval /= info->rsnsi;
	val->पूर्णांकval = 100u * regval;

	वापस 0;
पूर्ण

अटल पूर्णांक ltc4162l_set_iin_limit(काष्ठा ltc4162l_info *info,
				  अचिन्हित पूर्णांक value)
अणु
	अचिन्हित पूर्णांक regval;

	regval = mult_frac(value, info->rsnsi, 50000u);
	regval /= 10000u;
	अगर (regval)
		--regval;
	अगर (regval > 63)
		regval = 63;

	वापस regmap_ग_लिखो(info->regmap, LTC4162L_IIN_LIMIT_TARGET, regval);
पूर्ण

अटल पूर्णांक ltc4162l_get_die_temp(काष्ठा ltc4162l_info *info,
				 जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, LTC4162L_DIE_TEMPERATURE, &regval);
	अगर (ret)
		वापस ret;

	/* die_temp थ 0.0215तओC/LSB - 264.4तओC */
	ret = (s16)(regval & 0xFFFF);
	ret *= 215;
	ret /= 100; /* Centidegrees scale */
	ret -= 26440;
	val->पूर्णांकval = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ltc4162l_get_term_current(काष्ठा ltc4162l_info *info,
				     जोड़ घातer_supply_propval *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, LTC4162L_CHARGER_CONFIG_BITS, &regval);
	अगर (ret)
		वापस ret;

	/* Check अगर C_OVER_X_THRESHOLD is enabled */
	अगर (!(regval & BIT(2))) अणु
		val->पूर्णांकval = 0;
		वापस 0;
	पूर्ण

	ret = regmap_पढ़ो(info->regmap, LTC4162L_C_OVER_X_THRESHOLD, &regval);
	अगर (ret)
		वापस ret;

	/* 1.466NञV / RSNSB amperes/LSB */
	regval *= 14660u;
	regval /= info->rsnsb;
	val->पूर्णांकval = 100 * regval;

	वापस 0;
पूर्ण

अटल पूर्णांक ltc4162l_set_term_current(काष्ठा ltc4162l_info *info,
				     अचिन्हित पूर्णांक value)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक regval;

	अगर (!value) अणु
		/* Disable en_c_over_x_term when set to zero */
		वापस regmap_update_bits(info->regmap,
					  LTC4162L_CHARGER_CONFIG_BITS,
					  BIT(2), 0);
	पूर्ण

	regval = mult_frac(value, info->rsnsb, 14660u);
	regval /= 100u;

	ret =  regmap_ग_लिखो(info->regmap, LTC4162L_C_OVER_X_THRESHOLD, regval);
	अगर (ret)
		वापस ret;

	/* Set en_c_over_x_term after changing the threshold value */
	वापस regmap_update_bits(info->regmap, LTC4162L_CHARGER_CONFIG_BITS,
				  BIT(2), BIT(2));
पूर्ण

/* Custom properties */
अटल स्थिर अक्षर * स्थिर ltc4162l_अक्षरge_status_name[] = अणु
	"ilim_reg_active", /* 32 */
	"thermal_reg_active",
	"vin_uvcl_active",
	"iin_limit_active",
	"constant_current",
	"constant_voltage",
	"charger_off" /* 0 */
पूर्ण;

अटल sमाप_प्रकार अक्षरge_status_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	काष्ठा ltc4162l_info *info = घातer_supply_get_drvdata(psy);
	स्थिर अक्षर *result = ltc4162l_अक्षरge_status_name[
				ARRAY_SIZE(ltc4162l_अक्षरge_status_name) - 1];
	अचिन्हित पूर्णांक regval;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक index;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, LTC4162L_CHARGE_STATUS, &regval);
	अगर (ret)
		वापस ret;

	/* Only one bit is set according to datasheet, let's be safe here */
	क्रम (mask = 32, index = 0; mask != 0; mask >>= 1, ++index) अणु
		अगर (regval & mask) अणु
			result = ltc4162l_अक्षरge_status_name[index];
			अवरोध;
		पूर्ण
	पूर्ण

	वापस प्र_लिखो(buf, "%s\n", result);
पूर्ण
अटल DEVICE_ATTR_RO(अक्षरge_status);

अटल sमाप_प्रकार vbat_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	काष्ठा ltc4162l_info *info = घातer_supply_get_drvdata(psy);
	जोड़ घातer_supply_propval val;
	पूर्णांक ret;

	ret = ltc4162l_get_vbat(info, LTC4162L_VBAT, &val);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", val.पूर्णांकval);
पूर्ण
अटल DEVICE_ATTR_RO(vbat);

अटल sमाप_प्रकार vbat_avg_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	काष्ठा ltc4162l_info *info = घातer_supply_get_drvdata(psy);
	जोड़ घातer_supply_propval val;
	पूर्णांक ret;

	ret = ltc4162l_get_vbat(info, LTC4162L_VBAT_FILT, &val);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", val.पूर्णांकval);
पूर्ण
अटल DEVICE_ATTR_RO(vbat_avg);

अटल sमाप_प्रकार ibat_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	काष्ठा ltc4162l_info *info = घातer_supply_get_drvdata(psy);
	जोड़ घातer_supply_propval val;
	पूर्णांक ret;

	ret = ltc4162l_get_ibat(info, &val);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", val.पूर्णांकval);
पूर्ण
अटल DEVICE_ATTR_RO(ibat);

अटल sमाप_प्रकार क्रमce_telemetry_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	काष्ठा ltc4162l_info *info = घातer_supply_get_drvdata(psy);
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, LTC4162L_CONFIG_BITS_REG, &regval);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%u\n", regval & BIT(2) ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार क्रमce_telemetry_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr,
	स्थिर अक्षर *buf,
	माप_प्रकार count)
अणु
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	काष्ठा ltc4162l_info *info = घातer_supply_get_drvdata(psy);
	पूर्णांक ret;
	अचिन्हित पूर्णांक value;

	ret = kstrtouपूर्णांक(buf, 0, &value);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_update_bits(info->regmap, LTC4162L_CONFIG_BITS_REG,
				 BIT(2), value ? BIT(2) : 0);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(क्रमce_telemetry);

अटल sमाप_प्रकार arm_ship_mode_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	काष्ठा ltc4162l_info *info = घातer_supply_get_drvdata(psy);
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, LTC4162L_ARM_SHIP_MODE, &regval);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%u\n",
		regval == LTC4162L_ARM_SHIP_MODE_MAGIC ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार arm_ship_mode_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr,
	स्थिर अक्षर *buf,
	माप_प्रकार count)
अणु
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	काष्ठा ltc4162l_info *info = घातer_supply_get_drvdata(psy);
	पूर्णांक ret;
	अचिन्हित पूर्णांक value;

	ret = kstrtouपूर्णांक(buf, 0, &value);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(info->regmap, LTC4162L_ARM_SHIP_MODE,
				value ? LTC4162L_ARM_SHIP_MODE_MAGIC : 0);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(arm_ship_mode);

अटल काष्ठा attribute *ltc4162l_sysfs_entries[] = अणु
	&dev_attr_अक्षरge_status.attr,
	&dev_attr_ibat.attr,
	&dev_attr_vbat.attr,
	&dev_attr_vbat_avg.attr,
	&dev_attr_क्रमce_telemetry.attr,
	&dev_attr_arm_ship_mode.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ltc4162l_attr_group = अणु
	.name	= शून्य,	/* put in device directory */
	.attrs	= ltc4162l_sysfs_entries,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *ltc4162l_attr_groups[] = अणु
	&ltc4162l_attr_group,
	शून्य,
पूर्ण;

अटल पूर्णांक ltc4162l_get_property(काष्ठा घातer_supply *psy,
				 क्रमागत घातer_supply_property psp,
				 जोड़ घातer_supply_propval *val)
अणु
	काष्ठा ltc4162l_info *info = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		वापस ltc4162l_get_status(info, val);
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		वापस ltc4162l_get_अक्षरge_type(info, val);
	हाल POWER_SUPPLY_PROP_HEALTH:
		वापस ltc4162l_get_health(info, val);
	हाल POWER_SUPPLY_PROP_ONLINE:
		वापस ltc4162l_get_online(info, val);
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		वापस ltc4162l_get_input_voltage(info, val);
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		वापस ltc4162l_get_input_current(info, val);
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		वापस ltc4162l_get_iअक्षरge(info,
				LTC4162L_ICHARGE_DAC, val);
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		वापस ltc4162l_get_iअक्षरge(info,
				LTC4162L_CHARGE_CURRENT_SETTING, val);
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		वापस ltc4162l_get_vअक्षरge(info,
				LTC4162L_VCHARGE_DAC, val);
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		वापस ltc4162l_get_vअक्षरge(info,
				LTC4162L_VCHARGE_SETTING, val);
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		वापस ltc4162l_get_iin_limit_dac(info, val);
	हाल POWER_SUPPLY_PROP_TEMP:
		वापस ltc4162l_get_die_temp(info, val);
	हाल POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		वापस ltc4162l_get_term_current(info, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc4162l_set_property(काष्ठा घातer_supply *psy,
					 क्रमागत घातer_supply_property psp,
					 स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा ltc4162l_info *info = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		वापस ltc4162l_set_iअक्षरge(info,
				LTC4162L_CHARGE_CURRENT_SETTING, val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		वापस ltc4162l_set_vअक्षरge(info,
				LTC4162L_VCHARGE_SETTING, val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		वापस ltc4162l_set_iin_limit(info, val->पूर्णांकval);
	हाल POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		वापस ltc4162l_set_term_current(info, val->पूर्णांकval);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc4162l_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
						क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
	हाल POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/* Charger घातer supply property routines */
अटल क्रमागत घातer_supply_property ltc4162l_properties[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc ltc4162l_desc = अणु
	.name		= "ltc4162-l",
	.type		= POWER_SUPPLY_TYPE_MAINS,
	.properties	= ltc4162l_properties,
	.num_properties	= ARRAY_SIZE(ltc4162l_properties),
	.get_property	= ltc4162l_get_property,
	.set_property	= ltc4162l_set_property,
	.property_is_ग_लिखोable = ltc4162l_property_is_ग_लिखोable,
पूर्ण;

अटल bool ltc4162l_is_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* all रेजिस्टरs up to this one are ग_लिखोable */
	अगर (reg <= LTC4162L_CHARGER_CONFIG_BITS)
		वापस true;

	/* The ALERTS रेजिस्टरs can be written to clear alerts */
	अगर (reg >= LTC4162L_LIMIT_ALERTS_REG &&
	    reg <= LTC4162L_CHARGE_STATUS_ALERTS_REG)
		वापस true;

	वापस false;
पूर्ण

अटल bool ltc4162l_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* all रेजिस्टरs after this one are पढ़ो-only status रेजिस्टरs */
	वापस reg > LTC4162L_CHARGER_CONFIG_BITS;
पूर्ण

अटल स्थिर काष्ठा regmap_config ltc4162l_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 16,
	.val_क्रमmat_endian = REGMAP_ENDIAN_LITTLE,
	.ग_लिखोable_reg	= ltc4162l_is_ग_लिखोable_reg,
	.अस्थिर_reg	= ltc4162l_is_अस्थिर_reg,
	.max_रेजिस्टर	= LTC4162L_INPUT_UNDERVOLTAGE_DAC,
	.cache_type	= REGCACHE_RBTREE,
पूर्ण;

अटल व्योम ltc4162l_clear_पूर्णांकerrupts(काष्ठा ltc4162l_info *info)
अणु
	/* Acknowledge पूर्णांकerrupt to chip by clearing all events */
	regmap_ग_लिखो(info->regmap, LTC4162L_LIMIT_ALERTS_REG, 0);
	regmap_ग_लिखो(info->regmap, LTC4162L_CHARGER_STATE_ALERTS_REG, 0);
	regmap_ग_लिखो(info->regmap, LTC4162L_CHARGE_STATUS_ALERTS_REG, 0);
पूर्ण

अटल पूर्णांक ltc4162l_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा device *dev = &client->dev;
	काष्ठा ltc4162l_info *info;
	काष्ठा घातer_supply_config ltc4162l_config = अणुपूर्ण;
	u32 value;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WORD_DATA)) अणु
		dev_err(dev, "No support for SMBUS_WORD_DATA\n");
		वापस -ENODEV;
	पूर्ण
	info = devm_kzalloc(dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->client = client;
	i2c_set_clientdata(client, info);

	info->regmap = devm_regmap_init_i2c(client, &ltc4162l_regmap_config);
	अगर (IS_ERR(info->regmap)) अणु
		dev_err(dev, "Failed to initialize register map\n");
		वापस PTR_ERR(info->regmap);
	पूर्ण

	ret = device_property_पढ़ो_u32(dev, "lltc,rsnsb-micro-ohms",
				       &info->rsnsb);
	अगर (ret) अणु
		dev_err(dev, "Missing lltc,rsnsb-micro-ohms property\n");
		वापस ret;
	पूर्ण
	अगर (!info->rsnsb)
		वापस -EINVAL;

	ret = device_property_पढ़ो_u32(dev, "lltc,rsnsi-micro-ohms",
				       &info->rsnsi);
	अगर (ret) अणु
		dev_err(dev, "Missing lltc,rsnsi-micro-ohms property\n");
		वापस ret;
	पूर्ण
	अगर (!info->rsnsi)
		वापस -EINVAL;

	अगर (!device_property_पढ़ो_u32(dev, "lltc,cell-count", &value))
		info->cell_count = value;

	ltc4162l_config.of_node = dev->of_node;
	ltc4162l_config.drv_data = info;
	ltc4162l_config.attr_grp = ltc4162l_attr_groups;

	info->अक्षरger = devm_घातer_supply_रेजिस्टर(dev, &ltc4162l_desc,
						   &ltc4162l_config);
	अगर (IS_ERR(info->अक्षरger)) अणु
		dev_err(dev, "Failed to register charger\n");
		वापस PTR_ERR(info->अक्षरger);
	पूर्ण

	/* Disable the threshold alerts, we're not using them */
	regmap_ग_लिखो(info->regmap, LTC4162L_EN_LIMIT_ALERTS_REG, 0);

	/* Enable पूर्णांकerrupts on all status changes */
	regmap_ग_लिखो(info->regmap, LTC4162L_EN_CHARGER_STATE_ALERTS_REG,
		     0x1fff);
	regmap_ग_लिखो(info->regmap, LTC4162L_EN_CHARGE_STATUS_ALERTS_REG, 0x1f);

	ltc4162l_clear_पूर्णांकerrupts(info);

	वापस 0;
पूर्ण

अटल व्योम ltc4162l_alert(काष्ठा i2c_client *client,
			   क्रमागत i2c_alert_protocol type, अचिन्हित पूर्णांक flag)
अणु
	काष्ठा ltc4162l_info *info = i2c_get_clientdata(client);

	अगर (type != I2C_PROTOCOL_SMBUS_ALERT)
		वापस;

	ltc4162l_clear_पूर्णांकerrupts(info);
	घातer_supply_changed(info->अक्षरger);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ltc4162l_i2c_id_table[] = अणु
	अणु "ltc4162-l", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ltc4162l_i2c_id_table);

अटल स्थिर काष्ठा of_device_id ltc4162l_of_match[] = अणु
	अणु .compatible = "lltc,ltc4162-l", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ltc4162l_of_match);

अटल काष्ठा i2c_driver ltc4162l_driver = अणु
	.probe		= ltc4162l_probe,
	.alert		= ltc4162l_alert,
	.id_table	= ltc4162l_i2c_id_table,
	.driver = अणु
		.name		= "ltc4162-l-charger",
		.of_match_table	= of_match_ptr(ltc4162l_of_match),
	पूर्ण,
पूर्ण;
module_i2c_driver(ltc4162l_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mike Looijmans <mike.looijmans@topic.nl>");
MODULE_DESCRIPTION("LTC4162-L charger driver");
