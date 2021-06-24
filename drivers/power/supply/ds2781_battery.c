<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 1-wire client/driver क्रम the Maxim/Dallas DS2781 Stand-Alone Fuel Gauge IC
 *
 * Author: Renata Sayakhova <renata@oktetद_असल.ru>
 *
 * Based on ds2780_battery drivers
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/param.h>
#समावेश <linux/pm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/idr.h>

#समावेश <linux/w1.h>
#समावेश "../../w1/slaves/w1_ds2781.h"

/* Current unit measurement in uA क्रम a 1 milli-ohm sense resistor */
#घोषणा DS2781_CURRENT_UNITS	1563
/* Charge unit measurement in uAh क्रम a 1 milli-ohm sense resistor */
#घोषणा DS2781_CHARGE_UNITS		6250
/* Number of bytes in user EEPROM space */
#घोषणा DS2781_USER_EEPROM_SIZE		(DS2781_EEPROM_BLOCK0_END - \
					DS2781_EEPROM_BLOCK0_START + 1)
/* Number of bytes in parameter EEPROM space */
#घोषणा DS2781_PARAM_EEPROM_SIZE	(DS2781_EEPROM_BLOCK1_END - \
					DS2781_EEPROM_BLOCK1_START + 1)

काष्ठा ds2781_device_info अणु
	काष्ठा device *dev;
	काष्ठा घातer_supply *bat;
	काष्ठा घातer_supply_desc bat_desc;
	काष्ठा device *w1_dev;
पूर्ण;

क्रमागत current_types अणु
	CURRENT_NOW,
	CURRENT_AVG,
पूर्ण;

अटल स्थिर अक्षर model[] = "DS2781";
अटल स्थिर अक्षर manufacturer[] = "Maxim/Dallas";

अटल अंतरभूत काष्ठा ds2781_device_info *
to_ds2781_device_info(काष्ठा घातer_supply *psy)
अणु
	वापस घातer_supply_get_drvdata(psy);
पूर्ण

अटल अंतरभूत पूर्णांक ds2781_battery_io(काष्ठा ds2781_device_info *dev_info,
	अक्षर *buf, पूर्णांक addr, माप_प्रकार count, पूर्णांक io)
अणु
	वापस w1_ds2781_io(dev_info->w1_dev, buf, addr, count, io);
पूर्ण

अटल पूर्णांक w1_ds2781_पढ़ो(काष्ठा ds2781_device_info *dev_info, अक्षर *buf,
		पूर्णांक addr, माप_प्रकार count)
अणु
	वापस ds2781_battery_io(dev_info, buf, addr, count, 0);
पूर्ण

अटल अंतरभूत पूर्णांक ds2781_पढ़ो8(काष्ठा ds2781_device_info *dev_info, u8 *val,
	पूर्णांक addr)
अणु
	वापस ds2781_battery_io(dev_info, val, addr, माप(u8), 0);
पूर्ण

अटल पूर्णांक ds2781_पढ़ो16(काष्ठा ds2781_device_info *dev_info, s16 *val,
	पूर्णांक addr)
अणु
	पूर्णांक ret;
	u8 raw[2];

	ret = ds2781_battery_io(dev_info, raw, addr, माप(raw), 0);
	अगर (ret < 0)
		वापस ret;

	*val = (raw[0] << 8) | raw[1];

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ds2781_पढ़ो_block(काष्ठा ds2781_device_info *dev_info,
	u8 *val, पूर्णांक addr, माप_प्रकार count)
अणु
	वापस ds2781_battery_io(dev_info, val, addr, count, 0);
पूर्ण

अटल अंतरभूत पूर्णांक ds2781_ग_लिखो(काष्ठा ds2781_device_info *dev_info, u8 *val,
	पूर्णांक addr, माप_प्रकार count)
अणु
	वापस ds2781_battery_io(dev_info, val, addr, count, 1);
पूर्ण

अटल अंतरभूत पूर्णांक ds2781_store_eeprom(काष्ठा device *dev, पूर्णांक addr)
अणु
	वापस w1_ds2781_eeprom_cmd(dev, addr, W1_DS2781_COPY_DATA);
पूर्ण

अटल अंतरभूत पूर्णांक ds2781_recall_eeprom(काष्ठा device *dev, पूर्णांक addr)
अणु
	वापस w1_ds2781_eeprom_cmd(dev, addr, W1_DS2781_RECALL_DATA);
पूर्ण

अटल पूर्णांक ds2781_save_eeprom(काष्ठा ds2781_device_info *dev_info, पूर्णांक reg)
अणु
	पूर्णांक ret;

	ret = ds2781_store_eeprom(dev_info->w1_dev, reg);
	अगर (ret < 0)
		वापस ret;

	ret = ds2781_recall_eeprom(dev_info->w1_dev, reg);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/* Set sense resistor value in mhos */
अटल पूर्णांक ds2781_set_sense_रेजिस्टर(काष्ठा ds2781_device_info *dev_info,
	u8 conductance)
अणु
	पूर्णांक ret;

	ret = ds2781_ग_लिखो(dev_info, &conductance,
				DS2781_RSNSP, माप(u8));
	अगर (ret < 0)
		वापस ret;

	वापस ds2781_save_eeprom(dev_info, DS2781_RSNSP);
पूर्ण

/* Get RSGAIN value from 0 to 1.999 in steps of 0.001 */
अटल पूर्णांक ds2781_get_rsgain_रेजिस्टर(काष्ठा ds2781_device_info *dev_info,
	u16 *rsgain)
अणु
	वापस ds2781_पढ़ो16(dev_info, rsgain, DS2781_RSGAIN_MSB);
पूर्ण

/* Set RSGAIN value from 0 to 1.999 in steps of 0.001 */
अटल पूर्णांक ds2781_set_rsgain_रेजिस्टर(काष्ठा ds2781_device_info *dev_info,
	u16 rsgain)
अणु
	पूर्णांक ret;
	u8 raw[] = अणुrsgain >> 8, rsgain & 0xFFपूर्ण;

	ret = ds2781_ग_लिखो(dev_info, raw,
				DS2781_RSGAIN_MSB, माप(raw));
	अगर (ret < 0)
		वापस ret;

	वापस ds2781_save_eeprom(dev_info, DS2781_RSGAIN_MSB);
पूर्ण

अटल पूर्णांक ds2781_get_voltage(काष्ठा ds2781_device_info *dev_info,
	पूर्णांक *voltage_uV)
अणु
	पूर्णांक ret;
	अक्षर val[2];
	पूर्णांक voltage_raw;

	ret = w1_ds2781_पढ़ो(dev_info, val, DS2781_VOLT_MSB, 2 * माप(u8));
	अगर (ret < 0)
		वापस ret;
	/*
	 * The voltage value is located in 10 bits across the voltage MSB
	 * and LSB रेजिस्टरs in two's complement क्रमm
	 * Sign bit of the voltage value is in bit 7 of the voltage MSB रेजिस्टर
	 * Bits 9 - 3 of the voltage value are in bits 6 - 0 of the
	 * voltage MSB रेजिस्टर
	 * Bits 2 - 0 of the voltage value are in bits 7 - 5 of the
	 * voltage LSB रेजिस्टर
	 */
	voltage_raw = (val[0] << 3) |
		(val[1] >> 5);

	/* DS2781 reports voltage in units of 9.76mV, but the battery class
	 * reports in units of uV, so convert by multiplying by 9760. */
	*voltage_uV = voltage_raw * 9760;

	वापस 0;
पूर्ण

अटल पूर्णांक ds2781_get_temperature(काष्ठा ds2781_device_info *dev_info,
	पूर्णांक *temp)
अणु
	पूर्णांक ret;
	अक्षर val[2];
	पूर्णांक temp_raw;

	ret = w1_ds2781_पढ़ो(dev_info, val, DS2781_TEMP_MSB, 2 * माप(u8));
	अगर (ret < 0)
		वापस ret;
	/*
	 * The temperature value is located in 10 bits across the temperature
	 * MSB and LSB रेजिस्टरs in two's complement क्रमm
	 * Sign bit of the temperature value is in bit 7 of the temperature
	 * MSB रेजिस्टर
	 * Bits 9 - 3 of the temperature value are in bits 6 - 0 of the
	 * temperature MSB रेजिस्टर
	 * Bits 2 - 0 of the temperature value are in bits 7 - 5 of the
	 * temperature LSB रेजिस्टर
	 */
	temp_raw = ((val[0]) << 3) |
		(val[1] >> 5);
	*temp = temp_raw + (temp_raw / 4);

	वापस 0;
पूर्ण

अटल पूर्णांक ds2781_get_current(काष्ठा ds2781_device_info *dev_info,
	क्रमागत current_types type, पूर्णांक *current_uA)
अणु
	पूर्णांक ret, sense_res;
	s16 current_raw;
	u8 sense_res_raw, reg_msb;

	/*
	 * The units of measurement क्रम current are dependent on the value of
	 * the sense resistor.
	 */
	ret = ds2781_पढ़ो8(dev_info, &sense_res_raw, DS2781_RSNSP);
	अगर (ret < 0)
		वापस ret;

	अगर (sense_res_raw == 0) अणु
		dev_err(dev_info->dev, "sense resistor value is 0\n");
		वापस -EINVAL;
	पूर्ण
	sense_res = 1000 / sense_res_raw;

	अगर (type == CURRENT_NOW)
		reg_msb = DS2781_CURRENT_MSB;
	अन्यथा अगर (type == CURRENT_AVG)
		reg_msb = DS2781_IAVG_MSB;
	अन्यथा
		वापस -EINVAL;

	/*
	 * The current value is located in 16 bits across the current MSB
	 * and LSB रेजिस्टरs in two's complement क्रमm
	 * Sign bit of the current value is in bit 7 of the current MSB रेजिस्टर
	 * Bits 14 - 8 of the current value are in bits 6 - 0 of the current
	 * MSB रेजिस्टर
	 * Bits 7 - 0 of the current value are in bits 7 - 0 of the current
	 * LSB रेजिस्टर
	 */
	ret = ds2781_पढ़ो16(dev_info, &current_raw, reg_msb);
	अगर (ret < 0)
		वापस ret;

	*current_uA = current_raw * (DS2781_CURRENT_UNITS / sense_res);
	वापस 0;
पूर्ण

अटल पूर्णांक ds2781_get_accumulated_current(काष्ठा ds2781_device_info *dev_info,
	पूर्णांक *accumulated_current)
अणु
	पूर्णांक ret, sense_res;
	s16 current_raw;
	u8 sense_res_raw;

	/*
	 * The units of measurement क्रम accumulated current are dependent on
	 * the value of the sense resistor.
	 */
	ret = ds2781_पढ़ो8(dev_info, &sense_res_raw, DS2781_RSNSP);
	अगर (ret < 0)
		वापस ret;

	अगर (sense_res_raw == 0) अणु
		dev_err(dev_info->dev, "sense resistor value is 0\n");
		वापस -EINVAL;
	पूर्ण
	sense_res = 1000 / sense_res_raw;

	/*
	 * The ACR value is located in 16 bits across the ACR MSB and
	 * LSB रेजिस्टरs
	 * Bits 15 - 8 of the ACR value are in bits 7 - 0 of the ACR
	 * MSB रेजिस्टर
	 * Bits 7 - 0 of the ACR value are in bits 7 - 0 of the ACR
	 * LSB रेजिस्टर
	 */
	ret = ds2781_पढ़ो16(dev_info, &current_raw, DS2781_ACR_MSB);
	अगर (ret < 0)
		वापस ret;

	*accumulated_current = current_raw * (DS2781_CHARGE_UNITS / sense_res);
	वापस 0;
पूर्ण

अटल पूर्णांक ds2781_get_capacity(काष्ठा ds2781_device_info *dev_info,
	पूर्णांक *capacity)
अणु
	पूर्णांक ret;
	u8 raw;

	ret = ds2781_पढ़ो8(dev_info, &raw, DS2781_RARC);
	अगर (ret < 0)
		वापस ret;

	*capacity = raw;
	वापस 0;
पूर्ण

अटल पूर्णांक ds2781_get_status(काष्ठा ds2781_device_info *dev_info, पूर्णांक *status)
अणु
	पूर्णांक ret, current_uA, capacity;

	ret = ds2781_get_current(dev_info, CURRENT_NOW, &current_uA);
	अगर (ret < 0)
		वापस ret;

	ret = ds2781_get_capacity(dev_info, &capacity);
	अगर (ret < 0)
		वापस ret;

	अगर (घातer_supply_am_i_supplied(dev_info->bat)) अणु
		अगर (capacity == 100)
			*status = POWER_SUPPLY_STATUS_FULL;
		अन्यथा अगर (current_uA > 50000)
			*status = POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा
			*status = POWER_SUPPLY_STATUS_NOT_CHARGING;
	पूर्ण अन्यथा अणु
		*status = POWER_SUPPLY_STATUS_DISCHARGING;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ds2781_get_अक्षरge_now(काष्ठा ds2781_device_info *dev_info,
	पूर्णांक *अक्षरge_now)
अणु
	पूर्णांक ret;
	u16 अक्षरge_raw;

	/*
	 * The RAAC value is located in 16 bits across the RAAC MSB and
	 * LSB रेजिस्टरs
	 * Bits 15 - 8 of the RAAC value are in bits 7 - 0 of the RAAC
	 * MSB रेजिस्टर
	 * Bits 7 - 0 of the RAAC value are in bits 7 - 0 of the RAAC
	 * LSB रेजिस्टर
	 */
	ret = ds2781_पढ़ो16(dev_info, &अक्षरge_raw, DS2781_RAAC_MSB);
	अगर (ret < 0)
		वापस ret;

	*अक्षरge_now = अक्षरge_raw * 1600;
	वापस 0;
पूर्ण

अटल पूर्णांक ds2781_get_control_रेजिस्टर(काष्ठा ds2781_device_info *dev_info,
	u8 *control_reg)
अणु
	वापस ds2781_पढ़ो8(dev_info, control_reg, DS2781_CONTROL);
पूर्ण

अटल पूर्णांक ds2781_set_control_रेजिस्टर(काष्ठा ds2781_device_info *dev_info,
	u8 control_reg)
अणु
	पूर्णांक ret;

	ret = ds2781_ग_लिखो(dev_info, &control_reg,
				DS2781_CONTROL, माप(u8));
	अगर (ret < 0)
		वापस ret;

	वापस ds2781_save_eeprom(dev_info, DS2781_CONTROL);
पूर्ण

अटल पूर्णांक ds2781_battery_get_property(काष्ठा घातer_supply *psy,
	क्रमागत घातer_supply_property psp,
	जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक ret = 0;
	काष्ठा ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = ds2781_get_voltage(dev_info, &val->पूर्णांकval);
		अवरोध;

	हाल POWER_SUPPLY_PROP_TEMP:
		ret = ds2781_get_temperature(dev_info, &val->पूर्णांकval);
		अवरोध;

	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = model;
		अवरोध;

	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = manufacturer;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = ds2781_get_current(dev_info, CURRENT_NOW, &val->पूर्णांकval);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
		ret = ds2781_get_current(dev_info, CURRENT_AVG, &val->पूर्णांकval);
		अवरोध;

	हाल POWER_SUPPLY_PROP_STATUS:
		ret = ds2781_get_status(dev_info, &val->पूर्णांकval);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CAPACITY:
		ret = ds2781_get_capacity(dev_info, &val->पूर्णांकval);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_COUNTER:
		ret = ds2781_get_accumulated_current(dev_info, &val->पूर्णांकval);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		ret = ds2781_get_अक्षरge_now(dev_info, &val->पूर्णांकval);
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property ds2781_battery_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CURRENT_AVG,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CHARGE_COUNTER,
	POWER_SUPPLY_PROP_CHARGE_NOW,
पूर्ण;

अटल sमाप_प्रकार ds2781_get_pmod_enabled(काष्ठा device *dev,
	काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	पूर्णांक ret;
	u8 control_reg;
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	काष्ठा ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	/* Get घातer mode */
	ret = ds2781_get_control_रेजिस्टर(dev_info, &control_reg);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n",
		 !!(control_reg & DS2781_CONTROL_PMOD));
पूर्ण

अटल sमाप_प्रकार ds2781_set_pmod_enabled(काष्ठा device *dev,
	काष्ठा device_attribute *attr,
	स्थिर अक्षर *buf,
	माप_प्रकार count)
अणु
	पूर्णांक ret;
	u8 control_reg, new_setting;
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	काष्ठा ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	/* Set घातer mode */
	ret = ds2781_get_control_रेजिस्टर(dev_info, &control_reg);
	अगर (ret < 0)
		वापस ret;

	ret = kstrtou8(buf, 0, &new_setting);
	अगर (ret < 0)
		वापस ret;

	अगर ((new_setting != 0) && (new_setting != 1)) अणु
		dev_err(dev_info->dev, "Invalid pmod setting (0 or 1)\n");
		वापस -EINVAL;
	पूर्ण

	अगर (new_setting)
		control_reg |= DS2781_CONTROL_PMOD;
	अन्यथा
		control_reg &= ~DS2781_CONTROL_PMOD;

	ret = ds2781_set_control_रेजिस्टर(dev_info, control_reg);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार ds2781_get_sense_resistor_value(काष्ठा device *dev,
	काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	पूर्णांक ret;
	u8 sense_resistor;
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	काष्ठा ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	ret = ds2781_पढ़ो8(dev_info, &sense_resistor, DS2781_RSNSP);
	अगर (ret < 0)
		वापस ret;

	ret = प्र_लिखो(buf, "%d\n", sense_resistor);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ds2781_set_sense_resistor_value(काष्ठा device *dev,
	काष्ठा device_attribute *attr,
	स्थिर अक्षर *buf,
	माप_प्रकार count)
अणु
	पूर्णांक ret;
	u8 new_setting;
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	काष्ठा ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	ret = kstrtou8(buf, 0, &new_setting);
	अगर (ret < 0)
		वापस ret;

	ret = ds2781_set_sense_रेजिस्टर(dev_info, new_setting);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार ds2781_get_rsgain_setting(काष्ठा device *dev,
	काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	पूर्णांक ret;
	u16 rsgain;
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	काष्ठा ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	ret = ds2781_get_rsgain_रेजिस्टर(dev_info, &rsgain);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", rsgain);
पूर्ण

अटल sमाप_प्रकार ds2781_set_rsgain_setting(काष्ठा device *dev,
	काष्ठा device_attribute *attr,
	स्थिर अक्षर *buf,
	माप_प्रकार count)
अणु
	पूर्णांक ret;
	u16 new_setting;
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	काष्ठा ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	ret = kstrtou16(buf, 0, &new_setting);
	अगर (ret < 0)
		वापस ret;

	/* Gain can only be from 0 to 1.999 in steps of .001 */
	अगर (new_setting > 1999) अणु
		dev_err(dev_info->dev, "Invalid rsgain setting (0 - 1999)\n");
		वापस -EINVAL;
	पूर्ण

	ret = ds2781_set_rsgain_रेजिस्टर(dev_info, new_setting);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार ds2781_get_pio_pin(काष्ठा device *dev,
	काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	पूर्णांक ret;
	u8 sfr;
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	काष्ठा ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	ret = ds2781_पढ़ो8(dev_info, &sfr, DS2781_SFR);
	अगर (ret < 0)
		वापस ret;

	ret = प्र_लिखो(buf, "%d\n", sfr & DS2781_SFR_PIOSC);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार ds2781_set_pio_pin(काष्ठा device *dev,
	काष्ठा device_attribute *attr,
	स्थिर अक्षर *buf,
	माप_प्रकार count)
अणु
	पूर्णांक ret;
	u8 new_setting;
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	काष्ठा ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	ret = kstrtou8(buf, 0, &new_setting);
	अगर (ret < 0)
		वापस ret;

	अगर ((new_setting != 0) && (new_setting != 1)) अणु
		dev_err(dev_info->dev, "Invalid pio_pin setting (0 or 1)\n");
		वापस -EINVAL;
	पूर्ण

	ret = ds2781_ग_लिखो(dev_info, &new_setting,
				DS2781_SFR, माप(u8));
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार ds2781_पढ़ो_param_eeprom_bin(काष्ठा file *filp,
				काष्ठा kobject *kobj,
				काष्ठा bin_attribute *bin_attr,
				अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	काष्ठा ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	वापस ds2781_पढ़ो_block(dev_info, buf,
				DS2781_EEPROM_BLOCK1_START + off, count);
पूर्ण

अटल sमाप_प्रकार ds2781_ग_लिखो_param_eeprom_bin(काष्ठा file *filp,
				काष्ठा kobject *kobj,
				काष्ठा bin_attribute *bin_attr,
				अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	काष्ठा ds2781_device_info *dev_info = to_ds2781_device_info(psy);
	पूर्णांक ret;

	ret = ds2781_ग_लिखो(dev_info, buf,
				DS2781_EEPROM_BLOCK1_START + off, count);
	अगर (ret < 0)
		वापस ret;

	ret = ds2781_save_eeprom(dev_info, DS2781_EEPROM_BLOCK1_START);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल काष्ठा bin_attribute ds2781_param_eeprom_bin_attr = अणु
	.attr = अणु
		.name = "param_eeprom",
		.mode = S_IRUGO | S_IWUSR,
	पूर्ण,
	.size = DS2781_PARAM_EEPROM_SIZE,
	.पढ़ो = ds2781_पढ़ो_param_eeprom_bin,
	.ग_लिखो = ds2781_ग_लिखो_param_eeprom_bin,
पूर्ण;

अटल sमाप_प्रकार ds2781_पढ़ो_user_eeprom_bin(काष्ठा file *filp,
				काष्ठा kobject *kobj,
				काष्ठा bin_attribute *bin_attr,
				अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	काष्ठा ds2781_device_info *dev_info = to_ds2781_device_info(psy);

	वापस ds2781_पढ़ो_block(dev_info, buf,
				DS2781_EEPROM_BLOCK0_START + off, count);

पूर्ण

अटल sमाप_प्रकार ds2781_ग_लिखो_user_eeprom_bin(काष्ठा file *filp,
				काष्ठा kobject *kobj,
				काष्ठा bin_attribute *bin_attr,
				अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा घातer_supply *psy = to_घातer_supply(dev);
	काष्ठा ds2781_device_info *dev_info = to_ds2781_device_info(psy);
	पूर्णांक ret;

	ret = ds2781_ग_लिखो(dev_info, buf,
				DS2781_EEPROM_BLOCK0_START + off, count);
	अगर (ret < 0)
		वापस ret;

	ret = ds2781_save_eeprom(dev_info, DS2781_EEPROM_BLOCK0_START);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल काष्ठा bin_attribute ds2781_user_eeprom_bin_attr = अणु
	.attr = अणु
		.name = "user_eeprom",
		.mode = S_IRUGO | S_IWUSR,
	पूर्ण,
	.size = DS2781_USER_EEPROM_SIZE,
	.पढ़ो = ds2781_पढ़ो_user_eeprom_bin,
	.ग_लिखो = ds2781_ग_लिखो_user_eeprom_bin,
पूर्ण;

अटल DEVICE_ATTR(pmod_enabled, S_IRUGO | S_IWUSR, ds2781_get_pmod_enabled,
	ds2781_set_pmod_enabled);
अटल DEVICE_ATTR(sense_resistor_value, S_IRUGO | S_IWUSR,
	ds2781_get_sense_resistor_value, ds2781_set_sense_resistor_value);
अटल DEVICE_ATTR(rsgain_setting, S_IRUGO | S_IWUSR, ds2781_get_rsgain_setting,
	ds2781_set_rsgain_setting);
अटल DEVICE_ATTR(pio_pin, S_IRUGO | S_IWUSR, ds2781_get_pio_pin,
	ds2781_set_pio_pin);

अटल काष्ठा attribute *ds2781_sysfs_attrs[] = अणु
	&dev_attr_pmod_enabled.attr,
	&dev_attr_sense_resistor_value.attr,
	&dev_attr_rsgain_setting.attr,
	&dev_attr_pio_pin.attr,
	शून्य
पूर्ण;

अटल काष्ठा bin_attribute *ds2781_sysfs_bin_attrs[] = अणु
	&ds2781_param_eeprom_bin_attr,
	&ds2781_user_eeprom_bin_attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ds2781_sysfs_group = अणु
	.attrs = ds2781_sysfs_attrs,
	.bin_attrs = ds2781_sysfs_bin_attrs,

पूर्ण;

अटल स्थिर काष्ठा attribute_group *ds2781_sysfs_groups[] = अणु
	&ds2781_sysfs_group,
	शून्य,
पूर्ण;

अटल पूर्णांक ds2781_battery_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा ds2781_device_info *dev_info;

	dev_info = devm_kzalloc(&pdev->dev, माप(*dev_info), GFP_KERNEL);
	अगर (!dev_info)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, dev_info);

	dev_info->dev			= &pdev->dev;
	dev_info->w1_dev		= pdev->dev.parent;
	dev_info->bat_desc.name		= dev_name(&pdev->dev);
	dev_info->bat_desc.type		= POWER_SUPPLY_TYPE_BATTERY;
	dev_info->bat_desc.properties	= ds2781_battery_props;
	dev_info->bat_desc.num_properties = ARRAY_SIZE(ds2781_battery_props);
	dev_info->bat_desc.get_property	= ds2781_battery_get_property;

	psy_cfg.drv_data		= dev_info;
	psy_cfg.attr_grp		= ds2781_sysfs_groups;

	dev_info->bat = devm_घातer_supply_रेजिस्टर(&pdev->dev,
						   &dev_info->bat_desc,
						   &psy_cfg);
	अगर (IS_ERR(dev_info->bat)) अणु
		dev_err(dev_info->dev, "failed to register battery\n");
		वापस PTR_ERR(dev_info->bat);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ds2781_battery_driver = अणु
	.driver = अणु
		.name = "ds2781-battery",
	पूर्ण,
	.probe	  = ds2781_battery_probe,
पूर्ण;
module_platक्रमm_driver(ds2781_battery_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Renata Sayakhova <renata@oktetlabs.ru>");
MODULE_DESCRIPTION("Maxim/Dallas DS2781 Stand-Alone Fuel Gauge IC driver");
MODULE_ALIAS("platform:ds2781-battery");

