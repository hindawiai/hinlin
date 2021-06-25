<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// max77693_अक्षरger.c - Battery अक्षरger driver क्रम the Maxim 77693
//
// Copyright (C) 2014 Samsung Electronics
// Krzysztof Kozlowski <krzk@kernel.org>

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/max77693.h>
#समावेश <linux/mfd/max77693-common.h>
#समावेश <linux/mfd/max77693-निजी.h>

#घोषणा MAX77693_CHARGER_NAME				"max77693-charger"
अटल स्थिर अक्षर *max77693_अक्षरger_model		= "MAX77693";
अटल स्थिर अक्षर *max77693_अक्षरger_manufacturer	= "Maxim Integrated";

काष्ठा max77693_अक्षरger अणु
	काष्ठा device		*dev;
	काष्ठा max77693_dev	*max77693;
	काष्ठा घातer_supply	*अक्षरger;

	u32 स्थिरant_volt;
	u32 min_प्रणाली_volt;
	u32 thermal_regulation_temp;
	u32 batttery_overcurrent;
	u32 अक्षरge_input_threshold_volt;
पूर्ण;

अटल पूर्णांक max77693_get_अक्षरger_state(काष्ठा regmap *regmap, पूर्णांक *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक data;

	ret = regmap_पढ़ो(regmap, MAX77693_CHG_REG_CHG_DETAILS_01, &data);
	अगर (ret < 0)
		वापस ret;

	data &= CHG_DETAILS_01_CHG_MASK;
	data >>= CHG_DETAILS_01_CHG_SHIFT;

	चयन (data) अणु
	हाल MAX77693_CHARGING_PREQUALIFICATION:
	हाल MAX77693_CHARGING_FAST_CONST_CURRENT:
	हाल MAX77693_CHARGING_FAST_CONST_VOLTAGE:
	हाल MAX77693_CHARGING_TOP_OFF:
	/* In high temp the अक्षरging current is reduced, but still अक्षरging */
	हाल MAX77693_CHARGING_HIGH_TEMP:
		*val = POWER_SUPPLY_STATUS_CHARGING;
		अवरोध;
	हाल MAX77693_CHARGING_DONE:
		*val = POWER_SUPPLY_STATUS_FULL;
		अवरोध;
	हाल MAX77693_CHARGING_TIMER_EXPIRED:
	हाल MAX77693_CHARGING_THERMISTOR_SUSPEND:
		*val = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अवरोध;
	हाल MAX77693_CHARGING_OFF:
	हाल MAX77693_CHARGING_OVER_TEMP:
	हाल MAX77693_CHARGING_WATCHDOG_EXPIRED:
		*val = POWER_SUPPLY_STATUS_DISCHARGING;
		अवरोध;
	हाल MAX77693_CHARGING_RESERVED:
	शेष:
		*val = POWER_SUPPLY_STATUS_UNKNOWN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77693_get_अक्षरge_type(काष्ठा regmap *regmap, पूर्णांक *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक data;

	ret = regmap_पढ़ो(regmap, MAX77693_CHG_REG_CHG_DETAILS_01, &data);
	अगर (ret < 0)
		वापस ret;

	data &= CHG_DETAILS_01_CHG_MASK;
	data >>= CHG_DETAILS_01_CHG_SHIFT;

	चयन (data) अणु
	हाल MAX77693_CHARGING_PREQUALIFICATION:
	/*
	 * Top-off: trickle or fast? In top-off the current varies between
	 * 100 and 250 mA. It is higher than prequalअगरication current.
	 */
	हाल MAX77693_CHARGING_TOP_OFF:
		*val = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
		अवरोध;
	हाल MAX77693_CHARGING_FAST_CONST_CURRENT:
	हाल MAX77693_CHARGING_FAST_CONST_VOLTAGE:
	/* In high temp the अक्षरging current is reduced, but still अक्षरging */
	हाल MAX77693_CHARGING_HIGH_TEMP:
		*val = POWER_SUPPLY_CHARGE_TYPE_FAST;
		अवरोध;
	हाल MAX77693_CHARGING_DONE:
	हाल MAX77693_CHARGING_TIMER_EXPIRED:
	हाल MAX77693_CHARGING_THERMISTOR_SUSPEND:
	हाल MAX77693_CHARGING_OFF:
	हाल MAX77693_CHARGING_OVER_TEMP:
	हाल MAX77693_CHARGING_WATCHDOG_EXPIRED:
		*val = POWER_SUPPLY_CHARGE_TYPE_NONE;
		अवरोध;
	हाल MAX77693_CHARGING_RESERVED:
	शेष:
		*val = POWER_SUPPLY_CHARGE_TYPE_UNKNOWN;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Supported health statuses:
 *  - POWER_SUPPLY_HEALTH_DEAD
 *  - POWER_SUPPLY_HEALTH_GOOD
 *  - POWER_SUPPLY_HEALTH_OVERVOLTAGE
 *  - POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE
 *  - POWER_SUPPLY_HEALTH_UNKNOWN
 *  - POWER_SUPPLY_HEALTH_UNSPEC_FAILURE
 */
अटल पूर्णांक max77693_get_battery_health(काष्ठा regmap *regmap, पूर्णांक *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक data;

	ret = regmap_पढ़ो(regmap, MAX77693_CHG_REG_CHG_DETAILS_01, &data);
	अगर (ret < 0)
		वापस ret;

	data &= CHG_DETAILS_01_BAT_MASK;
	data >>= CHG_DETAILS_01_BAT_SHIFT;

	चयन (data) अणु
	हाल MAX77693_BATTERY_NOBAT:
		*val = POWER_SUPPLY_HEALTH_DEAD;
		अवरोध;
	हाल MAX77693_BATTERY_PREQUALIFICATION:
	हाल MAX77693_BATTERY_GOOD:
	हाल MAX77693_BATTERY_LOWVOLTAGE:
		*val = POWER_SUPPLY_HEALTH_GOOD;
		अवरोध;
	हाल MAX77693_BATTERY_TIMER_EXPIRED:
		/*
		 * Took दीर्घer to अक्षरge than expected, अक्षरging suspended.
		 * Damaged battery?
		 */
		*val = POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE;
		अवरोध;
	हाल MAX77693_BATTERY_OVERVOLTAGE:
		*val = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		अवरोध;
	हाल MAX77693_BATTERY_OVERCURRENT:
		*val = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		अवरोध;
	हाल MAX77693_BATTERY_RESERVED:
	शेष:
		*val = POWER_SUPPLY_HEALTH_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77693_get_present(काष्ठा regmap *regmap, पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक data;
	पूर्णांक ret;

	/*
	 * Read CHG_INT_OK रेजिस्टर. High DETBAT bit here should be
	 * equal to value 0x0 in CHG_DETAILS_01/BAT field.
	 */
	ret = regmap_पढ़ो(regmap, MAX77693_CHG_REG_CHG_INT_OK, &data);
	अगर (ret < 0)
		वापस ret;

	*val = (data & CHG_INT_OK_DETBAT_MASK) ? 0 : 1;

	वापस 0;
पूर्ण

अटल पूर्णांक max77693_get_online(काष्ठा regmap *regmap, पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक data;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, MAX77693_CHG_REG_CHG_INT_OK, &data);
	अगर (ret < 0)
		वापस ret;

	*val = (data & CHG_INT_OK_CHGIN_MASK) ? 1 : 0;

	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property max77693_अक्षरger_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;

अटल पूर्णांक max77693_अक्षरger_get_property(काष्ठा घातer_supply *psy,
			    क्रमागत घातer_supply_property psp,
			    जोड़ घातer_supply_propval *val)
अणु
	काष्ठा max77693_अक्षरger *chg = घातer_supply_get_drvdata(psy);
	काष्ठा regmap *regmap = chg->max77693->regmap;
	पूर्णांक ret = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		ret = max77693_get_अक्षरger_state(regmap, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		ret = max77693_get_अक्षरge_type(regmap, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		ret = max77693_get_battery_health(regmap, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		ret = max77693_get_present(regmap, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		ret = max77693_get_online(regmap, &val->पूर्णांकval);
		अवरोध;
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = max77693_अक्षरger_model;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = max77693_अक्षरger_manufacturer;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc max77693_अक्षरger_desc = अणु
	.name		= MAX77693_CHARGER_NAME,
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.properties	= max77693_अक्षरger_props,
	.num_properties	= ARRAY_SIZE(max77693_अक्षरger_props),
	.get_property	= max77693_अक्षरger_get_property,
पूर्ण;

अटल sमाप_प्रकार device_attr_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count,
		पूर्णांक (*fn)(काष्ठा max77693_अक्षरger *, अचिन्हित दीर्घ))
अणु
	काष्ठा max77693_अक्षरger *chg = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	ret = fn(chg, val);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार fast_अक्षरge_समयr_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा max77693_अक्षरger *chg = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक data, val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(chg->max77693->regmap, MAX77693_CHG_REG_CHG_CNFG_01,
			&data);
	अगर (ret < 0)
		वापस ret;

	data &= CHG_CNFG_01_FCHGTIME_MASK;
	data >>= CHG_CNFG_01_FCHGTIME_SHIFT;
	चयन (data) अणु
	हाल 0x1 ... 0x7:
		/* Starting from 4 hours, step by 2 hours */
		val = 4 + (data - 1) * 2;
		अवरोध;
	हाल 0x0:
	शेष:
		val = 0;
		अवरोध;
	पूर्ण

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", val);
पूर्ण

अटल पूर्णांक max77693_set_fast_अक्षरge_समयr(काष्ठा max77693_अक्षरger *chg,
		अचिन्हित दीर्घ hours)
अणु
	अचिन्हित पूर्णांक data;

	/*
	 * 0x00 - disable
	 * 0x01 - 4h
	 * 0x02 - 6h
	 * ...
	 * 0x07 - 16h
	 * Round करोwn odd values.
	 */
	चयन (hours) अणु
	हाल 4 ... 16:
		data = (hours - 4) / 2 + 1;
		अवरोध;
	हाल 0:
		/* Disable */
		data = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	data <<= CHG_CNFG_01_FCHGTIME_SHIFT;

	वापस regmap_update_bits(chg->max77693->regmap,
			MAX77693_CHG_REG_CHG_CNFG_01,
			CHG_CNFG_01_FCHGTIME_MASK, data);
पूर्ण

अटल sमाप_प्रकार fast_अक्षरge_समयr_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस device_attr_store(dev, attr, buf, count,
			max77693_set_fast_अक्षरge_समयr);
पूर्ण

अटल sमाप_प्रकार top_off_threshold_current_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा max77693_अक्षरger *chg = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक data, val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(chg->max77693->regmap, MAX77693_CHG_REG_CHG_CNFG_03,
			&data);
	अगर (ret < 0)
		वापस ret;

	data &= CHG_CNFG_03_TOITH_MASK;
	data >>= CHG_CNFG_03_TOITH_SHIFT;

	अगर (data <= 0x04)
		val = 100000 + data * 25000;
	अन्यथा
		val = data * 50000;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", val);
पूर्ण

अटल पूर्णांक max77693_set_top_off_threshold_current(काष्ठा max77693_अक्षरger *chg,
		अचिन्हित दीर्घ uamp)
अणु
	अचिन्हित पूर्णांक data;

	अगर (uamp < 100000 || uamp > 350000)
		वापस -EINVAL;

	अगर (uamp <= 200000)
		data = (uamp - 100000) / 25000;
	अन्यथा
		/* (200000, 350000> */
		data = uamp / 50000;

	data <<= CHG_CNFG_03_TOITH_SHIFT;

	वापस regmap_update_bits(chg->max77693->regmap,
			MAX77693_CHG_REG_CHG_CNFG_03,
			CHG_CNFG_03_TOITH_MASK, data);
पूर्ण

अटल sमाप_प्रकार top_off_threshold_current_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस device_attr_store(dev, attr, buf, count,
			max77693_set_top_off_threshold_current);
पूर्ण

अटल sमाप_प्रकार top_off_समयr_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा max77693_अक्षरger *chg = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक data, val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(chg->max77693->regmap, MAX77693_CHG_REG_CHG_CNFG_03,
			&data);
	अगर (ret < 0)
		वापस ret;

	data &= CHG_CNFG_03_TOTIME_MASK;
	data >>= CHG_CNFG_03_TOTIME_SHIFT;

	val = data * 10;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", val);
पूर्ण

अटल पूर्णांक max77693_set_top_off_समयr(काष्ठा max77693_अक्षरger *chg,
		अचिन्हित दीर्घ minutes)
अणु
	अचिन्हित पूर्णांक data;

	अगर (minutes > 70)
		वापस -EINVAL;

	data = minutes / 10;
	data <<= CHG_CNFG_03_TOTIME_SHIFT;

	वापस regmap_update_bits(chg->max77693->regmap,
			MAX77693_CHG_REG_CHG_CNFG_03,
			CHG_CNFG_03_TOTIME_MASK, data);
पूर्ण

अटल sमाप_प्रकार top_off_समयr_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस device_attr_store(dev, attr, buf, count,
			max77693_set_top_off_समयr);
पूर्ण

अटल DEVICE_ATTR_RW(fast_अक्षरge_समयr);
अटल DEVICE_ATTR_RW(top_off_threshold_current);
अटल DEVICE_ATTR_RW(top_off_समयr);

अटल पूर्णांक max77693_set_स्थिरant_volt(काष्ठा max77693_अक्षरger *chg,
		अचिन्हित पूर्णांक uvolt)
अणु
	अचिन्हित पूर्णांक data;

	/*
	 * 0x00 - 3.650 V
	 * 0x01 - 3.675 V
	 * ...
	 * 0x1b - 4.325 V
	 * 0x1c - 4.340 V
	 * 0x1d - 4.350 V
	 * 0x1e - 4.375 V
	 * 0x1f - 4.400 V
	 */
	अगर (uvolt >= 3650000 && uvolt < 4340000)
		data = (uvolt - 3650000) / 25000;
	अन्यथा अगर (uvolt >= 4340000 && uvolt < 4350000)
		data = 0x1c;
	अन्यथा अगर (uvolt >= 4350000 && uvolt <= 4400000)
		data = 0x1d + (uvolt - 4350000) / 25000;
	अन्यथा अणु
		dev_err(chg->dev, "Wrong value for charging constant voltage\n");
		वापस -EINVAL;
	पूर्ण

	data <<= CHG_CNFG_04_CHGCVPRM_SHIFT;

	dev_dbg(chg->dev, "Charging constant voltage: %u (0x%x)\n", uvolt,
			data);

	वापस regmap_update_bits(chg->max77693->regmap,
			MAX77693_CHG_REG_CHG_CNFG_04,
			CHG_CNFG_04_CHGCVPRM_MASK, data);
पूर्ण

अटल पूर्णांक max77693_set_min_प्रणाली_volt(काष्ठा max77693_अक्षरger *chg,
		अचिन्हित पूर्णांक uvolt)
अणु
	अचिन्हित पूर्णांक data;

	अगर (uvolt < 3000000 || uvolt > 3700000) अणु
		dev_err(chg->dev, "Wrong value for minimum system regulation voltage\n");
		वापस -EINVAL;
	पूर्ण

	data = (uvolt - 3000000) / 100000;

	data <<= CHG_CNFG_04_MINVSYS_SHIFT;

	dev_dbg(chg->dev, "Minimum system regulation voltage: %u (0x%x)\n",
			uvolt, data);

	वापस regmap_update_bits(chg->max77693->regmap,
			MAX77693_CHG_REG_CHG_CNFG_04,
			CHG_CNFG_04_MINVSYS_MASK, data);
पूर्ण

अटल पूर्णांक max77693_set_thermal_regulation_temp(काष्ठा max77693_अक्षरger *chg,
		अचिन्हित पूर्णांक cels)
अणु
	अचिन्हित पूर्णांक data;

	चयन (cels) अणु
	हाल 70:
	हाल 85:
	हाल 100:
	हाल 115:
		data = (cels - 70) / 15;
		अवरोध;
	शेष:
		dev_err(chg->dev, "Wrong value for thermal regulation loop temperature\n");
		वापस -EINVAL;
	पूर्ण

	data <<= CHG_CNFG_07_REGTEMP_SHIFT;

	dev_dbg(chg->dev, "Thermal regulation loop temperature: %u (0x%x)\n",
			cels, data);

	वापस regmap_update_bits(chg->max77693->regmap,
			MAX77693_CHG_REG_CHG_CNFG_07,
			CHG_CNFG_07_REGTEMP_MASK, data);
पूर्ण

अटल पूर्णांक max77693_set_batttery_overcurrent(काष्ठा max77693_अक्षरger *chg,
		अचिन्हित पूर्णांक uamp)
अणु
	अचिन्हित पूर्णांक data;

	अगर (uamp && (uamp < 2000000 || uamp > 3500000)) अणु
		dev_err(chg->dev, "Wrong value for battery overcurrent\n");
		वापस -EINVAL;
	पूर्ण

	अगर (uamp)
		data = ((uamp - 2000000) / 250000) + 1;
	अन्यथा
		data = 0; /* disable */

	data <<= CHG_CNFG_12_B2SOVRC_SHIFT;

	dev_dbg(chg->dev, "Battery overcurrent: %u (0x%x)\n", uamp, data);

	वापस regmap_update_bits(chg->max77693->regmap,
			MAX77693_CHG_REG_CHG_CNFG_12,
			CHG_CNFG_12_B2SOVRC_MASK, data);
पूर्ण

अटल पूर्णांक max77693_set_अक्षरge_input_threshold_volt(काष्ठा max77693_अक्षरger *chg,
		अचिन्हित पूर्णांक uvolt)
अणु
	अचिन्हित पूर्णांक data;

	चयन (uvolt) अणु
	हाल 4300000:
		data = 0x0;
		अवरोध;
	हाल 4700000:
	हाल 4800000:
	हाल 4900000:
		data = (uvolt - 4700000) / 100000;
		अवरोध;
	शेष:
		dev_err(chg->dev, "Wrong value for charge input voltage regulation threshold\n");
		वापस -EINVAL;
	पूर्ण

	data <<= CHG_CNFG_12_VCHGINREG_SHIFT;

	dev_dbg(chg->dev, "Charge input voltage regulation threshold: %u (0x%x)\n",
			uvolt, data);

	वापस regmap_update_bits(chg->max77693->regmap,
			MAX77693_CHG_REG_CHG_CNFG_12,
			CHG_CNFG_12_VCHGINREG_MASK, data);
पूर्ण

/*
 * Sets अक्षरger रेजिस्टरs to proper and safe शेष values.
 */
अटल पूर्णांक max77693_reg_init(काष्ठा max77693_अक्षरger *chg)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक data;

	/* Unlock अक्षरger रेजिस्टर protection */
	data = (0x3 << CHG_CNFG_06_CHGPROT_SHIFT);
	ret = regmap_update_bits(chg->max77693->regmap,
				MAX77693_CHG_REG_CHG_CNFG_06,
				CHG_CNFG_06_CHGPROT_MASK, data);
	अगर (ret) अणु
		dev_err(chg->dev, "Error unlocking registers: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = max77693_set_fast_अक्षरge_समयr(chg, DEFAULT_FAST_CHARGE_TIMER);
	अगर (ret)
		वापस ret;

	ret = max77693_set_top_off_threshold_current(chg,
			DEFAULT_TOP_OFF_THRESHOLD_CURRENT);
	अगर (ret)
		वापस ret;

	ret = max77693_set_top_off_समयr(chg, DEFAULT_TOP_OFF_TIMER);
	अगर (ret)
		वापस ret;

	ret = max77693_set_स्थिरant_volt(chg, chg->स्थिरant_volt);
	अगर (ret)
		वापस ret;

	ret = max77693_set_min_प्रणाली_volt(chg, chg->min_प्रणाली_volt);
	अगर (ret)
		वापस ret;

	ret = max77693_set_thermal_regulation_temp(chg,
			chg->thermal_regulation_temp);
	अगर (ret)
		वापस ret;

	ret = max77693_set_batttery_overcurrent(chg, chg->batttery_overcurrent);
	अगर (ret)
		वापस ret;

	वापस max77693_set_अक्षरge_input_threshold_volt(chg,
			chg->अक्षरge_input_threshold_volt);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल पूर्णांक max77693_dt_init(काष्ठा device *dev, काष्ठा max77693_अक्षरger *chg)
अणु
	काष्ठा device_node *np = dev->of_node;

	अगर (!np) अणु
		dev_err(dev, "no charger OF node\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "maxim,constant-microvolt",
			&chg->स्थिरant_volt))
		chg->स्थिरant_volt = DEFAULT_CONSTANT_VOLT;

	अगर (of_property_पढ़ो_u32(np, "maxim,min-system-microvolt",
			&chg->min_प्रणाली_volt))
		chg->min_प्रणाली_volt = DEFAULT_MIN_SYSTEM_VOLT;

	अगर (of_property_पढ़ो_u32(np, "maxim,thermal-regulation-celsius",
			&chg->thermal_regulation_temp))
		chg->thermal_regulation_temp = DEFAULT_THERMAL_REGULATION_TEMP;

	अगर (of_property_पढ़ो_u32(np, "maxim,battery-overcurrent-microamp",
			&chg->batttery_overcurrent))
		chg->batttery_overcurrent = DEFAULT_BATTERY_OVERCURRENT;

	अगर (of_property_पढ़ो_u32(np, "maxim,charge-input-threshold-microvolt",
			&chg->अक्षरge_input_threshold_volt))
		chg->अक्षरge_input_threshold_volt =
			DEFAULT_CHARGER_INPUT_THRESHOLD_VOLT;

	वापस 0;
पूर्ण
#अन्यथा /* CONFIG_OF */
अटल पूर्णांक max77693_dt_init(काष्ठा device *dev, काष्ठा max77693_अक्षरger *chg)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */

अटल पूर्णांक max77693_अक्षरger_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max77693_अक्षरger *chg;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा max77693_dev *max77693 = dev_get_drvdata(pdev->dev.parent);
	पूर्णांक ret;

	chg = devm_kzalloc(&pdev->dev, माप(*chg), GFP_KERNEL);
	अगर (!chg)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, chg);
	chg->dev = &pdev->dev;
	chg->max77693 = max77693;

	ret = max77693_dt_init(&pdev->dev, chg);
	अगर (ret)
		वापस ret;

	ret = max77693_reg_init(chg);
	अगर (ret)
		वापस ret;

	psy_cfg.drv_data = chg;

	ret = device_create_file(&pdev->dev, &dev_attr_fast_अक्षरge_समयr);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed: create fast charge timer sysfs entry\n");
		जाओ err;
	पूर्ण

	ret = device_create_file(&pdev->dev,
			&dev_attr_top_off_threshold_current);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed: create top off current sysfs entry\n");
		जाओ err;
	पूर्ण

	ret = device_create_file(&pdev->dev, &dev_attr_top_off_समयr);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed: create top off timer sysfs entry\n");
		जाओ err;
	पूर्ण

	chg->अक्षरger = घातer_supply_रेजिस्टर(&pdev->dev,
						&max77693_अक्षरger_desc,
						&psy_cfg);
	अगर (IS_ERR(chg->अक्षरger)) अणु
		dev_err(&pdev->dev, "failed: power supply register\n");
		ret = PTR_ERR(chg->अक्षरger);
		जाओ err;
	पूर्ण

	वापस 0;

err:
	device_हटाओ_file(&pdev->dev, &dev_attr_top_off_समयr);
	device_हटाओ_file(&pdev->dev, &dev_attr_top_off_threshold_current);
	device_हटाओ_file(&pdev->dev, &dev_attr_fast_अक्षरge_समयr);

	वापस ret;
पूर्ण

अटल पूर्णांक max77693_अक्षरger_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max77693_अक्षरger *chg = platक्रमm_get_drvdata(pdev);

	device_हटाओ_file(&pdev->dev, &dev_attr_top_off_समयr);
	device_हटाओ_file(&pdev->dev, &dev_attr_top_off_threshold_current);
	device_हटाओ_file(&pdev->dev, &dev_attr_fast_अक्षरge_समयr);

	घातer_supply_unरेजिस्टर(chg->अक्षरger);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id max77693_अक्षरger_id[] = अणु
	अणु "max77693-charger", 0, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max77693_अक्षरger_id);

अटल काष्ठा platक्रमm_driver max77693_अक्षरger_driver = अणु
	.driver = अणु
		.name	= "max77693-charger",
	पूर्ण,
	.probe		= max77693_अक्षरger_probe,
	.हटाओ		= max77693_अक्षरger_हटाओ,
	.id_table	= max77693_अक्षरger_id,
पूर्ण;
module_platक्रमm_driver(max77693_अक्षरger_driver);

MODULE_AUTHOR("Krzysztof Kozlowski <krzk@kernel.org>");
MODULE_DESCRIPTION("Maxim 77693 charger driver");
MODULE_LICENSE("GPL");
