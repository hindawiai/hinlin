<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Fuel gauge driver क्रम Maxim 17042 / 8966 / 8997
//  Note that Maxim 8966 and 8997 are mfd and this is its subdevice.
//
// Copyright (C) 2011 Samsung Electronics
// MyungJoo Ham <myungjoo.ham@samsung.com>
//
// This driver is based on max17040_battery.c

#समावेश <linux/acpi.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/घातer/max17042_battery.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>

/* Status रेजिस्टर bits */
#घोषणा STATUS_POR_BIT         (1 << 1)
#घोषणा STATUS_BST_BIT         (1 << 3)
#घोषणा STATUS_VMN_BIT         (1 << 8)
#घोषणा STATUS_TMN_BIT         (1 << 9)
#घोषणा STATUS_SMN_BIT         (1 << 10)
#घोषणा STATUS_BI_BIT          (1 << 11)
#घोषणा STATUS_VMX_BIT         (1 << 12)
#घोषणा STATUS_TMX_BIT         (1 << 13)
#घोषणा STATUS_SMX_BIT         (1 << 14)
#घोषणा STATUS_BR_BIT          (1 << 15)

/* Interrupt mask bits */
#घोषणा CONFIG_ALRT_BIT_ENBL	(1 << 2)
#घोषणा STATUS_INTR_SOCMIN_BIT	(1 << 10)
#घोषणा STATUS_INTR_SOCMAX_BIT	(1 << 14)

#घोषणा VFSOC0_LOCK		0x0000
#घोषणा VFSOC0_UNLOCK		0x0080
#घोषणा MODEL_UNLOCK1	0X0059
#घोषणा MODEL_UNLOCK2	0X00C4
#घोषणा MODEL_LOCK1		0X0000
#घोषणा MODEL_LOCK2		0X0000

#घोषणा dQ_ACC_DIV	0x4
#घोषणा dP_ACC_100	0x1900
#घोषणा dP_ACC_200	0x3200

#घोषणा MAX17042_VMAX_TOLERANCE		50 /* 50 mV */

काष्ठा max17042_chip अणु
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	काष्ठा घातer_supply *battery;
	क्रमागत max170xx_chip_type chip_type;
	काष्ठा max17042_platक्रमm_data *pdata;
	काष्ठा work_काष्ठा work;
	पूर्णांक    init_complete;
पूर्ण;

अटल क्रमागत घातer_supply_property max17042_battery_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_VOLTAGE_MIN,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_AVG,
	POWER_SUPPLY_PROP_VOLTAGE_OCV,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CHARGE_COUNTER,
	POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TEMP_ALERT_MIN,
	POWER_SUPPLY_PROP_TEMP_ALERT_MAX,
	POWER_SUPPLY_PROP_TEMP_MIN,
	POWER_SUPPLY_PROP_TEMP_MAX,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_SCOPE,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
	// these two have to be at the end on the list
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CURRENT_AVG,
पूर्ण;

अटल पूर्णांक max17042_get_temperature(काष्ठा max17042_chip *chip, पूर्णांक *temp)
अणु
	पूर्णांक ret;
	u32 data;
	काष्ठा regmap *map = chip->regmap;

	ret = regmap_पढ़ो(map, MAX17042_TEMP, &data);
	अगर (ret < 0)
		वापस ret;

	*temp = sign_extend32(data, 15);
	/* The value is converted पूर्णांकo deci-centigrade scale */
	/* Units of LSB = 1 / 256 degree Celsius */
	*temp = *temp * 10 / 256;
	वापस 0;
पूर्ण

अटल पूर्णांक max17042_get_status(काष्ठा max17042_chip *chip, पूर्णांक *status)
अणु
	पूर्णांक ret, अक्षरge_full, अक्षरge_now;
	पूर्णांक avg_current;
	u32 data;

	ret = घातer_supply_am_i_supplied(chip->battery);
	अगर (ret < 0) अणु
		*status = POWER_SUPPLY_STATUS_UNKNOWN;
		वापस 0;
	पूर्ण
	अगर (ret == 0) अणु
		*status = POWER_SUPPLY_STATUS_DISCHARGING;
		वापस 0;
	पूर्ण

	/*
	 * The MAX170xx has builtin end-of-अक्षरge detection and will update
	 * FullCAP to match RepCap when it detects end of अक्षरging.
	 *
	 * When this cycle the battery माला_लो अक्षरged to a higher (calculated)
	 * capacity then the previous cycle then FullCAP will get updated
	 * continuously once end-of-अक्षरge detection kicks in, so allow the
	 * 2 to dअगरfer a bit.
	 */

	ret = regmap_पढ़ो(chip->regmap, MAX17042_FullCAP, &अक्षरge_full);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(chip->regmap, MAX17042_RepCap, &अक्षरge_now);
	अगर (ret < 0)
		वापस ret;

	अगर ((अक्षरge_full - अक्षरge_now) <= MAX17042_FULL_THRESHOLD) अणु
		*status = POWER_SUPPLY_STATUS_FULL;
		वापस 0;
	पूर्ण

	/*
	 * Even though we are supplied, we may still be disअक्षरging अगर the
	 * supply is e.g. only delivering 5V 0.5A. Check current अगर available.
	 */
	अगर (!chip->pdata->enable_current_sense) अणु
		*status = POWER_SUPPLY_STATUS_CHARGING;
		वापस 0;
	पूर्ण

	ret = regmap_पढ़ो(chip->regmap, MAX17042_AvgCurrent, &data);
	अगर (ret < 0)
		वापस ret;

	avg_current = sign_extend32(data, 15);
	avg_current *= 1562500 / chip->pdata->r_sns;

	अगर (avg_current > 0)
		*status = POWER_SUPPLY_STATUS_CHARGING;
	अन्यथा
		*status = POWER_SUPPLY_STATUS_DISCHARGING;

	वापस 0;
पूर्ण

अटल पूर्णांक max17042_get_battery_health(काष्ठा max17042_chip *chip, पूर्णांक *health)
अणु
	पूर्णांक temp, vavg, vbatt, ret;
	u32 val;

	ret = regmap_पढ़ो(chip->regmap, MAX17042_AvgVCELL, &val);
	अगर (ret < 0)
		जाओ health_error;

	/* bits [0-3] unused */
	vavg = val * 625 / 8;
	/* Convert to millivolts */
	vavg /= 1000;

	ret = regmap_पढ़ो(chip->regmap, MAX17042_VCELL, &val);
	अगर (ret < 0)
		जाओ health_error;

	/* bits [0-3] unused */
	vbatt = val * 625 / 8;
	/* Convert to millivolts */
	vbatt /= 1000;

	अगर (vavg < chip->pdata->vmin) अणु
		*health = POWER_SUPPLY_HEALTH_DEAD;
		जाओ out;
	पूर्ण

	अगर (vbatt > chip->pdata->vmax + MAX17042_VMAX_TOLERANCE) अणु
		*health = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		जाओ out;
	पूर्ण

	ret = max17042_get_temperature(chip, &temp);
	अगर (ret < 0)
		जाओ health_error;

	अगर (temp < chip->pdata->temp_min) अणु
		*health = POWER_SUPPLY_HEALTH_COLD;
		जाओ out;
	पूर्ण

	अगर (temp > chip->pdata->temp_max) अणु
		*health = POWER_SUPPLY_HEALTH_OVERHEAT;
		जाओ out;
	पूर्ण

	*health = POWER_SUPPLY_HEALTH_GOOD;

out:
	वापस 0;

health_error:
	वापस ret;
पूर्ण

अटल पूर्णांक max17042_get_property(काष्ठा घातer_supply *psy,
			    क्रमागत घातer_supply_property psp,
			    जोड़ घातer_supply_propval *val)
अणु
	काष्ठा max17042_chip *chip = घातer_supply_get_drvdata(psy);
	काष्ठा regmap *map = chip->regmap;
	पूर्णांक ret;
	u32 data;
	u64 data64;

	अगर (!chip->init_complete)
		वापस -EAGAIN;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		ret = max17042_get_status(chip, &val->पूर्णांकval);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		ret = regmap_पढ़ो(map, MAX17042_STATUS, &data);
		अगर (ret < 0)
			वापस ret;

		अगर (data & MAX17042_STATUS_BattAbsent)
			val->पूर्णांकval = 0;
		अन्यथा
			val->पूर्णांकval = 1;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_LION;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CYCLE_COUNT:
		ret = regmap_पढ़ो(map, MAX17042_Cycles, &data);
		अगर (ret < 0)
			वापस ret;

		val->पूर्णांकval = data;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX:
		ret = regmap_पढ़ो(map, MAX17042_MinMaxVolt, &data);
		अगर (ret < 0)
			वापस ret;

		val->पूर्णांकval = data >> 8;
		val->पूर्णांकval *= 20000; /* Units of LSB = 20mV */
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN:
		ret = regmap_पढ़ो(map, MAX17042_MinMaxVolt, &data);
		अगर (ret < 0)
			वापस ret;

		val->पूर्णांकval = (data & 0xff) * 20000; /* Units of 20mV */
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		अगर (chip->chip_type == MAXIM_DEVICE_TYPE_MAX17042)
			ret = regmap_पढ़ो(map, MAX17042_V_empty, &data);
		अन्यथा अगर (chip->chip_type == MAXIM_DEVICE_TYPE_MAX17055)
			ret = regmap_पढ़ो(map, MAX17055_V_empty, &data);
		अन्यथा
			ret = regmap_पढ़ो(map, MAX17047_V_empty, &data);
		अगर (ret < 0)
			वापस ret;

		val->पूर्णांकval = data >> 7;
		val->पूर्णांकval *= 10000; /* Units of LSB = 10mV */
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = regmap_पढ़ो(map, MAX17042_VCELL, &data);
		अगर (ret < 0)
			वापस ret;

		val->पूर्णांकval = data * 625 / 8;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_AVG:
		ret = regmap_पढ़ो(map, MAX17042_AvgVCELL, &data);
		अगर (ret < 0)
			वापस ret;

		val->पूर्णांकval = data * 625 / 8;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_OCV:
		ret = regmap_पढ़ो(map, MAX17042_OCVInternal, &data);
		अगर (ret < 0)
			वापस ret;

		val->पूर्णांकval = data * 625 / 8;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		ret = regmap_पढ़ो(map, MAX17042_RepSOC, &data);
		अगर (ret < 0)
			वापस ret;

		val->पूर्णांकval = data >> 8;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		ret = regmap_पढ़ो(map, MAX17042_DesignCap, &data);
		अगर (ret < 0)
			वापस ret;

		data64 = data * 5000000ll;
		करो_भाग(data64, chip->pdata->r_sns);
		val->पूर्णांकval = data64;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
		ret = regmap_पढ़ो(map, MAX17042_FullCAP, &data);
		अगर (ret < 0)
			वापस ret;

		data64 = data * 5000000ll;
		करो_भाग(data64, chip->pdata->r_sns);
		val->पूर्णांकval = data64;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		ret = regmap_पढ़ो(map, MAX17042_RepCap, &data);
		अगर (ret < 0)
			वापस ret;

		data64 = data * 5000000ll;
		करो_भाग(data64, chip->pdata->r_sns);
		val->पूर्णांकval = data64;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_COUNTER:
		ret = regmap_पढ़ो(map, MAX17042_QH, &data);
		अगर (ret < 0)
			वापस ret;

		data64 = sign_extend64(data, 15) * 5000000ll;
		val->पूर्णांकval = भाग_s64(data64, chip->pdata->r_sns);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		ret = max17042_get_temperature(chip, &val->पूर्णांकval);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP_ALERT_MIN:
		ret = regmap_पढ़ो(map, MAX17042_TALRT_Th, &data);
		अगर (ret < 0)
			वापस ret;
		/* LSB is Alert Minimum. In deci-centigrade */
		val->पूर्णांकval = sign_extend32(data & 0xff, 7) * 10;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP_ALERT_MAX:
		ret = regmap_पढ़ो(map, MAX17042_TALRT_Th, &data);
		अगर (ret < 0)
			वापस ret;
		/* MSB is Alert Maximum. In deci-centigrade */
		val->पूर्णांकval = sign_extend32(data >> 8, 7) * 10;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP_MIN:
		val->पूर्णांकval = chip->pdata->temp_min;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP_MAX:
		val->पूर्णांकval = chip->pdata->temp_max;
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		ret = max17042_get_battery_health(chip, &val->पूर्णांकval);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल POWER_SUPPLY_PROP_SCOPE:
		val->पूर्णांकval = POWER_SUPPLY_SCOPE_SYSTEM;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		अगर (chip->pdata->enable_current_sense) अणु
			ret = regmap_पढ़ो(map, MAX17042_Current, &data);
			अगर (ret < 0)
				वापस ret;

			data64 = sign_extend64(data, 15) * 1562500ll;
			val->पूर्णांकval = भाग_s64(data64, chip->pdata->r_sns);
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
		अगर (chip->pdata->enable_current_sense) अणु
			ret = regmap_पढ़ो(map, MAX17042_AvgCurrent, &data);
			अगर (ret < 0)
				वापस ret;

			data64 = sign_extend64(data, 15) * 1562500ll;
			val->पूर्णांकval = भाग_s64(data64, chip->pdata->r_sns);
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		ret = regmap_पढ़ो(map, MAX17042_ICHGTerm, &data);
		अगर (ret < 0)
			वापस ret;

		data64 = data * 1562500ll;
		val->पूर्णांकval = भाग_s64(data64, chip->pdata->r_sns);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW:
		ret = regmap_पढ़ो(map, MAX17042_TTE, &data);
		अगर (ret < 0)
			वापस ret;

		val->पूर्णांकval = data * 5625 / 1000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक max17042_set_property(काष्ठा घातer_supply *psy,
			    क्रमागत घातer_supply_property psp,
			    स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा max17042_chip *chip = घातer_supply_get_drvdata(psy);
	काष्ठा regmap *map = chip->regmap;
	पूर्णांक ret = 0;
	u32 data;
	पूर्णांक8_t temp;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_TEMP_ALERT_MIN:
		ret = regmap_पढ़ो(map, MAX17042_TALRT_Th, &data);
		अगर (ret < 0)
			वापस ret;

		/* Input in deci-centigrade, convert to centigrade */
		temp = val->पूर्णांकval / 10;
		/* क्रमce min < max */
		अगर (temp >= (पूर्णांक8_t)(data >> 8))
			temp = (पूर्णांक8_t)(data >> 8) - 1;
		/* Write both MAX and MIN ALERT */
		data = (data & 0xff00) + temp;
		ret = regmap_ग_लिखो(map, MAX17042_TALRT_Th, data);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP_ALERT_MAX:
		ret = regmap_पढ़ो(map, MAX17042_TALRT_Th, &data);
		अगर (ret < 0)
			वापस ret;

		/* Input in Deci-Centigrade, convert to centigrade */
		temp = val->पूर्णांकval / 10;
		/* क्रमce max > min */
		अगर (temp <= (पूर्णांक8_t)(data & 0xff))
			temp = (पूर्णांक8_t)(data & 0xff) + 1;
		/* Write both MAX and MIN ALERT */
		data = (data & 0xff) + (temp << 8);
		ret = regmap_ग_लिखो(map, MAX17042_TALRT_Th, data);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक max17042_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp)
अणु
	पूर्णांक ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_TEMP_ALERT_MIN:
	हाल POWER_SUPPLY_PROP_TEMP_ALERT_MAX:
		ret = 1;
		अवरोध;
	शेष:
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम max17042_बाह्यal_घातer_changed(काष्ठा घातer_supply *psy)
अणु
	घातer_supply_changed(psy);
पूर्ण

अटल पूर्णांक max17042_ग_लिखो_verअगरy_reg(काष्ठा regmap *map, u8 reg, u32 value)
अणु
	पूर्णांक retries = 8;
	पूर्णांक ret;
	u32 पढ़ो_value;

	करो अणु
		ret = regmap_ग_लिखो(map, reg, value);
		regmap_पढ़ो(map, reg, &पढ़ो_value);
		अगर (पढ़ो_value != value) अणु
			ret = -EIO;
			retries--;
		पूर्ण
	पूर्ण जबतक (retries && पढ़ो_value != value);

	अगर (ret < 0)
		pr_err("%s: err %d\n", __func__, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम max17042_override_por(काष्ठा regmap *map,
					 u8 reg, u16 value)
अणु
	अगर (value)
		regmap_ग_लिखो(map, reg, value);
पूर्ण

अटल अंतरभूत व्योम max17042_unlock_model(काष्ठा max17042_chip *chip)
अणु
	काष्ठा regmap *map = chip->regmap;

	regmap_ग_लिखो(map, MAX17042_MLOCKReg1, MODEL_UNLOCK1);
	regmap_ग_लिखो(map, MAX17042_MLOCKReg2, MODEL_UNLOCK2);
पूर्ण

अटल अंतरभूत व्योम max17042_lock_model(काष्ठा max17042_chip *chip)
अणु
	काष्ठा regmap *map = chip->regmap;

	regmap_ग_लिखो(map, MAX17042_MLOCKReg1, MODEL_LOCK1);
	regmap_ग_लिखो(map, MAX17042_MLOCKReg2, MODEL_LOCK2);
पूर्ण

अटल अंतरभूत व्योम max17042_ग_लिखो_model_data(काष्ठा max17042_chip *chip,
					u8 addr, पूर्णांक size)
अणु
	काष्ठा regmap *map = chip->regmap;
	पूर्णांक i;

	क्रम (i = 0; i < size; i++)
		regmap_ग_लिखो(map, addr + i,
			chip->pdata->config_data->cell_अक्षर_tbl[i]);
पूर्ण

अटल अंतरभूत व्योम max17042_पढ़ो_model_data(काष्ठा max17042_chip *chip,
					u8 addr, u16 *data, पूर्णांक size)
अणु
	काष्ठा regmap *map = chip->regmap;
	पूर्णांक i;
	u32 पंचांगp;

	क्रम (i = 0; i < size; i++) अणु
		regmap_पढ़ो(map, addr + i, &पंचांगp);
		data[i] = (u16)पंचांगp;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक max17042_model_data_compare(काष्ठा max17042_chip *chip,
					u16 *data1, u16 *data2, पूर्णांक size)
अणु
	पूर्णांक i;

	अगर (स_भेद(data1, data2, size)) अणु
		dev_err(&chip->client->dev, "%s compare failed\n", __func__);
		क्रम (i = 0; i < size; i++)
			dev_info(&chip->client->dev, "0x%x, 0x%x",
				data1[i], data2[i]);
		dev_info(&chip->client->dev, "\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक max17042_init_model(काष्ठा max17042_chip *chip)
अणु
	पूर्णांक ret;
	पूर्णांक table_size = ARRAY_SIZE(chip->pdata->config_data->cell_अक्षर_tbl);
	u16 *temp_data;

	temp_data = kसुस्मृति(table_size, माप(*temp_data), GFP_KERNEL);
	अगर (!temp_data)
		वापस -ENOMEM;

	max17042_unlock_model(chip);
	max17042_ग_लिखो_model_data(chip, MAX17042_MODELChrTbl,
				table_size);
	max17042_पढ़ो_model_data(chip, MAX17042_MODELChrTbl, temp_data,
				table_size);

	ret = max17042_model_data_compare(
		chip,
		chip->pdata->config_data->cell_अक्षर_tbl,
		temp_data,
		table_size);

	max17042_lock_model(chip);
	kमुक्त(temp_data);

	वापस ret;
पूर्ण

अटल पूर्णांक max17042_verअगरy_model_lock(काष्ठा max17042_chip *chip)
अणु
	पूर्णांक i;
	पूर्णांक table_size = ARRAY_SIZE(chip->pdata->config_data->cell_अक्षर_tbl);
	u16 *temp_data;
	पूर्णांक ret = 0;

	temp_data = kसुस्मृति(table_size, माप(*temp_data), GFP_KERNEL);
	अगर (!temp_data)
		वापस -ENOMEM;

	max17042_पढ़ो_model_data(chip, MAX17042_MODELChrTbl, temp_data,
				table_size);
	क्रम (i = 0; i < table_size; i++)
		अगर (temp_data[i])
			ret = -EINVAL;

	kमुक्त(temp_data);
	वापस ret;
पूर्ण

अटल व्योम max17042_ग_लिखो_config_regs(काष्ठा max17042_chip *chip)
अणु
	काष्ठा max17042_config_data *config = chip->pdata->config_data;
	काष्ठा regmap *map = chip->regmap;

	regmap_ग_लिखो(map, MAX17042_CONFIG, config->config);
	regmap_ग_लिखो(map, MAX17042_LearnCFG, config->learn_cfg);
	regmap_ग_लिखो(map, MAX17042_FilterCFG,
			config->filter_cfg);
	regmap_ग_लिखो(map, MAX17042_RelaxCFG, config->relax_cfg);
	अगर (chip->chip_type == MAXIM_DEVICE_TYPE_MAX17047 ||
			chip->chip_type == MAXIM_DEVICE_TYPE_MAX17050 ||
			chip->chip_type == MAXIM_DEVICE_TYPE_MAX17055)
		regmap_ग_लिखो(map, MAX17047_FullSOCThr,
						config->full_soc_thresh);
पूर्ण

अटल व्योम  max17042_ग_लिखो_custom_regs(काष्ठा max17042_chip *chip)
अणु
	काष्ठा max17042_config_data *config = chip->pdata->config_data;
	काष्ठा regmap *map = chip->regmap;

	max17042_ग_लिखो_verअगरy_reg(map, MAX17042_RCOMP0, config->rcomp0);
	max17042_ग_लिखो_verअगरy_reg(map, MAX17042_TempCo,	config->tcompc0);
	max17042_ग_लिखो_verअगरy_reg(map, MAX17042_ICHGTerm, config->ichgt_term);
	अगर (chip->chip_type == MAXIM_DEVICE_TYPE_MAX17042) अणु
		regmap_ग_लिखो(map, MAX17042_EmptyTempCo,	config->empty_tempco);
		max17042_ग_लिखो_verअगरy_reg(map, MAX17042_K_empty0,
					config->kempty0);
	पूर्ण अन्यथा अणु
		max17042_ग_लिखो_verअगरy_reg(map, MAX17047_QRTbl00,
						config->qrtbl00);
		max17042_ग_लिखो_verअगरy_reg(map, MAX17047_QRTbl10,
						config->qrtbl10);
		max17042_ग_लिखो_verअगरy_reg(map, MAX17047_QRTbl20,
						config->qrtbl20);
		max17042_ग_लिखो_verअगरy_reg(map, MAX17047_QRTbl30,
						config->qrtbl30);
	पूर्ण
पूर्ण

अटल व्योम max17042_update_capacity_regs(काष्ठा max17042_chip *chip)
अणु
	काष्ठा max17042_config_data *config = chip->pdata->config_data;
	काष्ठा regmap *map = chip->regmap;

	max17042_ग_लिखो_verअगरy_reg(map, MAX17042_FullCAP,
				config->fullcap);
	regmap_ग_लिखो(map, MAX17042_DesignCap, config->design_cap);
	max17042_ग_लिखो_verअगरy_reg(map, MAX17042_FullCAPNom,
				config->fullcapnom);
पूर्ण

अटल व्योम max17042_reset_vfsoc0_reg(काष्ठा max17042_chip *chip)
अणु
	अचिन्हित पूर्णांक vfSoc;
	काष्ठा regmap *map = chip->regmap;

	regmap_पढ़ो(map, MAX17042_VFSOC, &vfSoc);
	regmap_ग_लिखो(map, MAX17042_VFSOC0Enable, VFSOC0_UNLOCK);
	max17042_ग_लिखो_verअगरy_reg(map, MAX17042_VFSOC0, vfSoc);
	regmap_ग_लिखो(map, MAX17042_VFSOC0Enable, VFSOC0_LOCK);
पूर्ण

अटल व्योम max17042_load_new_capacity_params(काष्ठा max17042_chip *chip)
अणु
	u32 full_cap0, rep_cap, dq_acc, vfSoc;
	u32 rem_cap;

	काष्ठा max17042_config_data *config = chip->pdata->config_data;
	काष्ठा regmap *map = chip->regmap;

	regmap_पढ़ो(map, MAX17042_FullCAP0, &full_cap0);
	regmap_पढ़ो(map, MAX17042_VFSOC, &vfSoc);

	/* fg_vfSoc needs to shअगरted by 8 bits to get the
	 * perc in 1% accuracy, to get the right rem_cap multiply
	 * full_cap0, fg_vfSoc and devide by 100
	 */
	rem_cap = ((vfSoc >> 8) * full_cap0) / 100;
	max17042_ग_लिखो_verअगरy_reg(map, MAX17042_RemCap, rem_cap);

	rep_cap = rem_cap;
	max17042_ग_लिखो_verअगरy_reg(map, MAX17042_RepCap, rep_cap);

	/* Write dQ_acc to 200% of Capacity and dP_acc to 200% */
	dq_acc = config->fullcap / dQ_ACC_DIV;
	max17042_ग_लिखो_verअगरy_reg(map, MAX17042_dQacc, dq_acc);
	max17042_ग_लिखो_verअगरy_reg(map, MAX17042_dPacc, dP_ACC_200);

	max17042_ग_लिखो_verअगरy_reg(map, MAX17042_FullCAP,
			config->fullcap);
	regmap_ग_लिखो(map, MAX17042_DesignCap,
			config->design_cap);
	max17042_ग_लिखो_verअगरy_reg(map, MAX17042_FullCAPNom,
			config->fullcapnom);
	/* Update SOC रेजिस्टर with new SOC */
	regmap_ग_लिखो(map, MAX17042_RepSOC, vfSoc);
पूर्ण

/*
 * Block ग_लिखो all the override values coming from platक्रमm data.
 * This function MUST be called beक्रमe the POR initialization procedure
 * specअगरied by maxim.
 */
अटल अंतरभूत व्योम max17042_override_por_values(काष्ठा max17042_chip *chip)
अणु
	काष्ठा regmap *map = chip->regmap;
	काष्ठा max17042_config_data *config = chip->pdata->config_data;

	max17042_override_por(map, MAX17042_TGAIN, config->tgain);
	max17042_override_por(map, MAx17042_TOFF, config->toff);
	max17042_override_por(map, MAX17042_CGAIN, config->cgain);
	max17042_override_por(map, MAX17042_COFF, config->coff);

	max17042_override_por(map, MAX17042_VALRT_Th, config->valrt_thresh);
	max17042_override_por(map, MAX17042_TALRT_Th, config->talrt_thresh);
	max17042_override_por(map, MAX17042_SALRT_Th,
						config->soc_alrt_thresh);
	max17042_override_por(map, MAX17042_CONFIG, config->config);
	max17042_override_por(map, MAX17042_SHDNTIMER, config->shdnसमयr);

	max17042_override_por(map, MAX17042_DesignCap, config->design_cap);
	max17042_override_por(map, MAX17042_ICHGTerm, config->ichgt_term);

	max17042_override_por(map, MAX17042_AtRate, config->at_rate);
	max17042_override_por(map, MAX17042_LearnCFG, config->learn_cfg);
	max17042_override_por(map, MAX17042_FilterCFG, config->filter_cfg);
	max17042_override_por(map, MAX17042_RelaxCFG, config->relax_cfg);
	max17042_override_por(map, MAX17042_MiscCFG, config->misc_cfg);
	max17042_override_por(map, MAX17042_MaskSOC, config->masksoc);

	max17042_override_por(map, MAX17042_FullCAP, config->fullcap);
	max17042_override_por(map, MAX17042_FullCAPNom, config->fullcapnom);
	अगर (chip->chip_type == MAXIM_DEVICE_TYPE_MAX17042)
		max17042_override_por(map, MAX17042_SOC_empty,
						config->socempty);
	max17042_override_por(map, MAX17042_LAvg_empty, config->lavg_empty);
	max17042_override_por(map, MAX17042_dQacc, config->dqacc);
	max17042_override_por(map, MAX17042_dPacc, config->dpacc);

	अगर (chip->chip_type == MAXIM_DEVICE_TYPE_MAX17042)
		max17042_override_por(map, MAX17042_V_empty, config->vempty);
	अगर (chip->chip_type == MAXIM_DEVICE_TYPE_MAX17055)
		max17042_override_por(map, MAX17055_V_empty, config->vempty);
	अन्यथा
		max17042_override_por(map, MAX17047_V_empty, config->vempty);
	max17042_override_por(map, MAX17042_TempNom, config->temp_nom);
	max17042_override_por(map, MAX17042_TempLim, config->temp_lim);
	max17042_override_por(map, MAX17042_FCTC, config->fctc);
	max17042_override_por(map, MAX17042_RCOMP0, config->rcomp0);
	max17042_override_por(map, MAX17042_TempCo, config->tcompc0);
	अगर (chip->chip_type &&
	    ((chip->chip_type == MAXIM_DEVICE_TYPE_MAX17042) ||
	    (chip->chip_type == MAXIM_DEVICE_TYPE_MAX17047) ||
	    (chip->chip_type == MAXIM_DEVICE_TYPE_MAX17050))) अणु
		max17042_override_por(map, MAX17042_EmptyTempCo,
						config->empty_tempco);
		max17042_override_por(map, MAX17042_K_empty0,
						config->kempty0);
	पूर्ण
पूर्ण

अटल पूर्णांक max17042_init_chip(काष्ठा max17042_chip *chip)
अणु
	काष्ठा regmap *map = chip->regmap;
	पूर्णांक ret;

	max17042_override_por_values(chip);
	/* After Power up, the MAX17042 requires 500mS in order
	 * to perक्रमm संकेत debouncing and initial SOC reporting
	 */
	msleep(500);

	/* Initialize configuration */
	max17042_ग_लिखो_config_regs(chip);

	/* ग_लिखो cell अक्षरacterization data */
	ret = max17042_init_model(chip);
	अगर (ret) अणु
		dev_err(&chip->client->dev, "%s init failed\n",
			__func__);
		वापस -EIO;
	पूर्ण

	ret = max17042_verअगरy_model_lock(chip);
	अगर (ret) अणु
		dev_err(&chip->client->dev, "%s lock verify failed\n",
			__func__);
		वापस -EIO;
	पूर्ण
	/* ग_लिखो custom parameters */
	max17042_ग_लिखो_custom_regs(chip);

	/* update capacity params */
	max17042_update_capacity_regs(chip);

	/* delay must be atleast 350mS to allow VFSOC
	 * to be calculated from the new configuration
	 */
	msleep(350);

	/* reset vfsoc0 reg */
	max17042_reset_vfsoc0_reg(chip);

	/* load new capacity params */
	max17042_load_new_capacity_params(chip);

	/* Init complete, Clear the POR bit */
	regmap_update_bits(map, MAX17042_STATUS, STATUS_POR_BIT, 0x0);
	वापस 0;
पूर्ण

अटल व्योम max17042_set_soc_threshold(काष्ठा max17042_chip *chip, u16 off)
अणु
	काष्ठा regmap *map = chip->regmap;
	u32 soc, soc_tr;

	/* program पूर्णांकerrupt thresholds such that we should
	 * get पूर्णांकerrupt क्रम every 'off' perc change in the soc
	 */
	regmap_पढ़ो(map, MAX17042_RepSOC, &soc);
	soc >>= 8;
	soc_tr = (soc + off) << 8;
	soc_tr |= (soc - off);
	regmap_ग_लिखो(map, MAX17042_SALRT_Th, soc_tr);
पूर्ण

अटल irqवापस_t max17042_thपढ़ो_handler(पूर्णांक id, व्योम *dev)
अणु
	काष्ठा max17042_chip *chip = dev;
	u32 val;

	regmap_पढ़ो(chip->regmap, MAX17042_STATUS, &val);
	अगर ((val & STATUS_INTR_SOCMIN_BIT) ||
		(val & STATUS_INTR_SOCMAX_BIT)) अणु
		dev_info(&chip->client->dev, "SOC threshold INTR\n");
		max17042_set_soc_threshold(chip, 1);
	पूर्ण

	घातer_supply_changed(chip->battery);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम max17042_init_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा max17042_chip *chip = container_of(work,
				काष्ठा max17042_chip, work);
	पूर्णांक ret;

	/* Initialize रेजिस्टरs according to values from the platक्रमm data */
	अगर (chip->pdata->enable_por_init && chip->pdata->config_data) अणु
		ret = max17042_init_chip(chip);
		अगर (ret)
			वापस;
	पूर्ण

	chip->init_complete = 1;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल काष्ठा max17042_platक्रमm_data *
max17042_get_of_pdata(काष्ठा max17042_chip *chip)
अणु
	काष्ठा device *dev = &chip->client->dev;
	काष्ठा device_node *np = dev->of_node;
	u32 prop;
	काष्ठा max17042_platक्रमm_data *pdata;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	/*
	 * Require current sense resistor value to be specअगरied क्रम
	 * current-sense functionality to be enabled at all.
	 */
	अगर (of_property_पढ़ो_u32(np, "maxim,rsns-microohm", &prop) == 0) अणु
		pdata->r_sns = prop;
		pdata->enable_current_sense = true;
	पूर्ण

	अगर (of_property_पढ़ो_s32(np, "maxim,cold-temp", &pdata->temp_min))
		pdata->temp_min = पूर्णांक_न्यून;
	अगर (of_property_पढ़ो_s32(np, "maxim,over-heat-temp", &pdata->temp_max))
		pdata->temp_max = पूर्णांक_उच्च;
	अगर (of_property_पढ़ो_s32(np, "maxim,dead-volt", &pdata->vmin))
		pdata->vmin = पूर्णांक_न्यून;
	अगर (of_property_पढ़ो_s32(np, "maxim,over-volt", &pdata->vmax))
		pdata->vmax = पूर्णांक_उच्च;

	वापस pdata;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा max17042_reg_data max17047_शेष_pdata_init_regs[] = अणु
	/*
	 * Some firmwares करो not set FullSOCThr, Enable End-of-Charge Detection
	 * when the voltage FG reports 95%, as recommended in the datasheet.
	 */
	अणु MAX17047_FullSOCThr, MAX17042_BATTERY_FULL << 8 पूर्ण,
पूर्ण;

अटल काष्ठा max17042_platक्रमm_data *
max17042_get_शेष_pdata(काष्ठा max17042_chip *chip)
अणु
	काष्ठा device *dev = &chip->client->dev;
	काष्ठा max17042_platक्रमm_data *pdata;
	पूर्णांक ret, misc_cfg;

	/*
	 * The MAX17047 माला_लो used on x86 where we might not have pdata, assume
	 * the firmware will alपढ़ोy have initialized the fuel-gauge and provide
	 * शेष values क्रम the non init bits to make things work.
	 */
	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस pdata;

	अगर ((chip->chip_type == MAXIM_DEVICE_TYPE_MAX17047) ||
	    (chip->chip_type == MAXIM_DEVICE_TYPE_MAX17050)) अणु
		pdata->init_data = max17047_शेष_pdata_init_regs;
		pdata->num_init_data =
			ARRAY_SIZE(max17047_शेष_pdata_init_regs);
	पूर्ण

	ret = regmap_पढ़ो(chip->regmap, MAX17042_MiscCFG, &misc_cfg);
	अगर (ret < 0)
		वापस शून्य;

	/* If bits 0-1 are set to 3 then only Voltage पढ़ोings are used */
	अगर ((misc_cfg & 0x3) == 0x3)
		pdata->enable_current_sense = false;
	अन्यथा
		pdata->enable_current_sense = true;

	pdata->vmin = MAX17042_DEFAULT_VMIN;
	pdata->vmax = MAX17042_DEFAULT_VMAX;
	pdata->temp_min = MAX17042_DEFAULT_TEMP_MIN;
	pdata->temp_max = MAX17042_DEFAULT_TEMP_MAX;

	वापस pdata;
पूर्ण

अटल काष्ठा max17042_platक्रमm_data *
max17042_get_pdata(काष्ठा max17042_chip *chip)
अणु
	काष्ठा device *dev = &chip->client->dev;

#अगर_घोषित CONFIG_OF
	अगर (dev->of_node)
		वापस max17042_get_of_pdata(chip);
#पूर्ण_अगर
	अगर (dev->platक्रमm_data)
		वापस dev->platक्रमm_data;

	वापस max17042_get_शेष_pdata(chip);
पूर्ण

अटल स्थिर काष्ठा regmap_config max17042_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.val_क्रमmat_endian = REGMAP_ENDIAN_NATIVE,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc max17042_psy_desc = अणु
	.name		= "max170xx_battery",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.get_property	= max17042_get_property,
	.set_property	= max17042_set_property,
	.property_is_ग_लिखोable	= max17042_property_is_ग_लिखोable,
	.बाह्यal_घातer_changed	= max17042_बाह्यal_घातer_changed,
	.properties	= max17042_battery_props,
	.num_properties	= ARRAY_SIZE(max17042_battery_props),
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc max17042_no_current_sense_psy_desc = अणु
	.name		= "max170xx_battery",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.get_property	= max17042_get_property,
	.set_property	= max17042_set_property,
	.property_is_ग_लिखोable	= max17042_property_is_ग_लिखोable,
	.properties	= max17042_battery_props,
	.num_properties	= ARRAY_SIZE(max17042_battery_props) - 2,
पूर्ण;

अटल व्योम max17042_stop_work(व्योम *data)
अणु
	काष्ठा max17042_chip *chip = data;

	cancel_work_sync(&chip->work);
पूर्ण

अटल पूर्णांक max17042_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	स्थिर काष्ठा घातer_supply_desc *max17042_desc = &max17042_psy_desc;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	स्थिर काष्ठा acpi_device_id *acpi_id = शून्य;
	काष्ठा device *dev = &client->dev;
	काष्ठा max17042_chip *chip;
	पूर्णांक ret;
	पूर्णांक i;
	u32 val;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WORD_DATA))
		वापस -EIO;

	chip = devm_kzalloc(&client->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->client = client;
	अगर (id) अणु
		chip->chip_type = id->driver_data;
	पूर्ण अन्यथा अणु
		acpi_id = acpi_match_device(dev->driver->acpi_match_table, dev);
		अगर (!acpi_id)
			वापस -ENODEV;

		chip->chip_type = acpi_id->driver_data;
	पूर्ण
	chip->regmap = devm_regmap_init_i2c(client, &max17042_regmap_config);
	अगर (IS_ERR(chip->regmap)) अणु
		dev_err(&client->dev, "Failed to initialize regmap\n");
		वापस -EINVAL;
	पूर्ण

	chip->pdata = max17042_get_pdata(chip);
	अगर (!chip->pdata) अणु
		dev_err(&client->dev, "no platform data provided\n");
		वापस -EINVAL;
	पूर्ण

	i2c_set_clientdata(client, chip);
	psy_cfg.drv_data = chip;
	psy_cfg.of_node = dev->of_node;

	/* When current is not measured,
	 * CURRENT_NOW and CURRENT_AVG properties should be invisible. */
	अगर (!chip->pdata->enable_current_sense)
		max17042_desc = &max17042_no_current_sense_psy_desc;

	अगर (chip->pdata->r_sns == 0)
		chip->pdata->r_sns = MAX17042_DEFAULT_SNS_RESISTOR;

	अगर (chip->pdata->init_data)
		क्रम (i = 0; i < chip->pdata->num_init_data; i++)
			regmap_ग_लिखो(chip->regmap,
					chip->pdata->init_data[i].addr,
					chip->pdata->init_data[i].data);

	अगर (!chip->pdata->enable_current_sense) अणु
		regmap_ग_लिखो(chip->regmap, MAX17042_CGAIN, 0x0000);
		regmap_ग_लिखो(chip->regmap, MAX17042_MiscCFG, 0x0003);
		regmap_ग_लिखो(chip->regmap, MAX17042_LearnCFG, 0x0007);
	पूर्ण

	chip->battery = devm_घातer_supply_रेजिस्टर(&client->dev, max17042_desc,
						   &psy_cfg);
	अगर (IS_ERR(chip->battery)) अणु
		dev_err(&client->dev, "failed: power supply register\n");
		वापस PTR_ERR(chip->battery);
	पूर्ण

	अगर (client->irq) अणु
		अचिन्हित पूर्णांक flags = IRQF_TRIGGER_FALLING | IRQF_ONESHOT;

		/*
		 * On ACPI प्रणालीs the IRQ may be handled by ACPI-event code,
		 * so we need to share (अगर the ACPI code is willing to share).
		 */
		अगर (acpi_id)
			flags |= IRQF_SHARED | IRQF_PROBE_SHARED;

		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						शून्य,
						max17042_thपढ़ो_handler, flags,
						chip->battery->desc->name,
						chip);
		अगर (!ret) अणु
			regmap_update_bits(chip->regmap, MAX17042_CONFIG,
					CONFIG_ALRT_BIT_ENBL,
					CONFIG_ALRT_BIT_ENBL);
			max17042_set_soc_threshold(chip, 1);
		पूर्ण अन्यथा अणु
			client->irq = 0;
			अगर (ret != -EBUSY)
				dev_err(&client->dev, "Failed to get IRQ\n");
		पूर्ण
	पूर्ण
	/* Not able to update the अक्षरge threshold when exceeded? -> disable */
	अगर (!client->irq)
		regmap_ग_लिखो(chip->regmap, MAX17042_SALRT_Th, 0xff00);

	regmap_पढ़ो(chip->regmap, MAX17042_STATUS, &val);
	अगर (val & STATUS_POR_BIT) अणु
		INIT_WORK(&chip->work, max17042_init_worker);
		ret = devm_add_action(&client->dev, max17042_stop_work, chip);
		अगर (ret)
			वापस ret;
		schedule_work(&chip->work);
	पूर्ण अन्यथा अणु
		chip->init_complete = 1;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक max17042_suspend(काष्ठा device *dev)
अणु
	काष्ठा max17042_chip *chip = dev_get_drvdata(dev);

	/*
	 * disable the irq and enable irq_wake
	 * capability to the पूर्णांकerrupt line.
	 */
	अगर (chip->client->irq) अणु
		disable_irq(chip->client->irq);
		enable_irq_wake(chip->client->irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max17042_resume(काष्ठा device *dev)
अणु
	काष्ठा max17042_chip *chip = dev_get_drvdata(dev);

	अगर (chip->client->irq) अणु
		disable_irq_wake(chip->client->irq);
		enable_irq(chip->client->irq);
		/* re-program the SOC thresholds to 1% change */
		max17042_set_soc_threshold(chip, 1);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(max17042_pm_ops, max17042_suspend,
			max17042_resume);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id max17042_acpi_match[] = अणु
	अणु "MAX17047", MAXIM_DEVICE_TYPE_MAX17047 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, max17042_acpi_match);
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id max17042_dt_match[] = अणु
	अणु .compatible = "maxim,max17042" पूर्ण,
	अणु .compatible = "maxim,max17047" पूर्ण,
	अणु .compatible = "maxim,max17050" पूर्ण,
	अणु .compatible = "maxim,max17055" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, max17042_dt_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id max17042_id[] = अणु
	अणु "max17042", MAXIM_DEVICE_TYPE_MAX17042 पूर्ण,
	अणु "max17047", MAXIM_DEVICE_TYPE_MAX17047 पूर्ण,
	अणु "max17050", MAXIM_DEVICE_TYPE_MAX17050 पूर्ण,
	अणु "max17055", MAXIM_DEVICE_TYPE_MAX17055 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max17042_id);

अटल काष्ठा i2c_driver max17042_i2c_driver = अणु
	.driver	= अणु
		.name	= "max17042",
		.acpi_match_table = ACPI_PTR(max17042_acpi_match),
		.of_match_table = of_match_ptr(max17042_dt_match),
		.pm	= &max17042_pm_ops,
	पूर्ण,
	.probe		= max17042_probe,
	.id_table	= max17042_id,
पूर्ण;
module_i2c_driver(max17042_i2c_driver);

MODULE_AUTHOR("MyungJoo Ham <myungjoo.ham@samsung.com>");
MODULE_DESCRIPTION("MAX17042 Fuel Gauge");
MODULE_LICENSE("GPL");
