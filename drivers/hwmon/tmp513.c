<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Texas Instruments TMP512, TMP513 घातer monitor chips
 *
 * TMP513:
 * Thermal/Power Management with Triple Remote and
 * Local Temperature Sensor and Current Shunt Monitor
 * Datasheet: https://www.ti.com/lit/gpn/पंचांगp513
 *
 * TMP512:
 * Thermal/Power Management with Dual Remote
 *	and Local Temperature Sensor and Current Shunt Monitor
 * Datasheet: https://www.ti.com/lit/gpn/पंचांगp512
 *
 * Copyright (C) 2019 Eric Tremblay <etremblay@distech-controls.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 */

#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/util_macros.h>

// Common रेजिस्टर definition
#घोषणा TMP51X_SHUNT_CONFIG		0x00
#घोषणा TMP51X_TEMP_CONFIG		0x01
#घोषणा TMP51X_STATUS			0x02
#घोषणा TMP51X_SMBUS_ALERT		0x03
#घोषणा TMP51X_SHUNT_CURRENT_RESULT	0x04
#घोषणा TMP51X_BUS_VOLTAGE_RESULT	0x05
#घोषणा TMP51X_POWER_RESULT		0x06
#घोषणा TMP51X_BUS_CURRENT_RESULT	0x07
#घोषणा TMP51X_LOCAL_TEMP_RESULT	0x08
#घोषणा TMP51X_REMOTE_TEMP_RESULT_1	0x09
#घोषणा TMP51X_REMOTE_TEMP_RESULT_2	0x0A
#घोषणा TMP51X_SHUNT_CURRENT_H_LIMIT	0x0C
#घोषणा TMP51X_SHUNT_CURRENT_L_LIMIT	0x0D
#घोषणा TMP51X_BUS_VOLTAGE_H_LIMIT	0x0E
#घोषणा TMP51X_BUS_VOLTAGE_L_LIMIT	0x0F
#घोषणा TMP51X_POWER_LIMIT		0x10
#घोषणा TMP51X_LOCAL_TEMP_LIMIT	0x11
#घोषणा TMP51X_REMOTE_TEMP_LIMIT_1	0x12
#घोषणा TMP51X_REMOTE_TEMP_LIMIT_2	0x13
#घोषणा TMP51X_SHUNT_CALIBRATION	0x15
#घोषणा TMP51X_N_FACTOR_AND_HYST_1	0x16
#घोषणा TMP51X_N_FACTOR_2		0x17
#घोषणा TMP51X_MAN_ID_REG		0xFE
#घोषणा TMP51X_DEVICE_ID_REG		0xFF

// TMP513 specअगरic रेजिस्टर definition
#घोषणा TMP513_REMOTE_TEMP_RESULT_3	0x0B
#घोषणा TMP513_REMOTE_TEMP_LIMIT_3	0x14
#घोषणा TMP513_N_FACTOR_3		0x18

// Common attrs, and शून्य
#घोषणा TMP51X_MANUFACTURER_ID		0x55FF

#घोषणा TMP512_DEVICE_ID		0x22FF
#घोषणा TMP513_DEVICE_ID		0x23FF

// Default config
#घोषणा TMP51X_SHUNT_CONFIG_DEFAULT	0x399F
#घोषणा TMP51X_SHUNT_VALUE_DEFAULT	1000
#घोषणा TMP51X_VBUS_RANGE_DEFAULT	TMP51X_VBUS_RANGE_32V
#घोषणा TMP51X_PGA_DEFAULT		8
#घोषणा TMP51X_MAX_REGISTER_ADDR	0xFF

#घोषणा TMP512_TEMP_CONFIG_DEFAULT	0xBF80
#घोषणा TMP513_TEMP_CONFIG_DEFAULT	0xFF80

// Mask and shअगरt
#घोषणा CURRENT_SENSE_VOLTAGE_320_MASK	0x1800
#घोषणा CURRENT_SENSE_VOLTAGE_160_MASK	0x1000
#घोषणा CURRENT_SENSE_VOLTAGE_80_MASK	0x0800
#घोषणा CURRENT_SENSE_VOLTAGE_40_MASK	0

#घोषणा TMP51X_BUS_VOLTAGE_MASK		0x2000
#घोषणा TMP51X_NFACTOR_MASK		0xFF00
#घोषणा TMP51X_HYST_MASK		0x00FF

#घोषणा TMP51X_BUS_VOLTAGE_SHIFT	3
#घोषणा TMP51X_TEMP_SHIFT		3

// Alarms
#घोषणा TMP51X_SHUNT_CURRENT_H_LIMIT_POS	15
#घोषणा TMP51X_SHUNT_CURRENT_L_LIMIT_POS	14
#घोषणा TMP51X_BUS_VOLTAGE_H_LIMIT_POS		13
#घोषणा TMP51X_BUS_VOLTAGE_L_LIMIT_POS		12
#घोषणा TMP51X_POWER_LIMIT_POS			11
#घोषणा TMP51X_LOCAL_TEMP_LIMIT_POS		10
#घोषणा TMP51X_REMOTE_TEMP_LIMIT_1_POS		9
#घोषणा TMP51X_REMOTE_TEMP_LIMIT_2_POS		8
#घोषणा TMP513_REMOTE_TEMP_LIMIT_3_POS		7

#घोषणा TMP51X_VBUS_RANGE_32V		32000000
#घोषणा TMP51X_VBUS_RANGE_16V		16000000

// Max and Min value
#घोषणा MAX_BUS_VOLTAGE_32_LIMIT	32764
#घोषणा MAX_BUS_VOLTAGE_16_LIMIT	16382

// Max possible value is -256 to +256 but datasheet indicated -40 to 125.
#घोषणा MAX_TEMP_LIMIT			125000
#घोषणा MIN_TEMP_LIMIT			-40000

#घोषणा MAX_TEMP_HYST			127500

अटल स्थिर u8 TMP51X_TEMP_INPUT[4] = अणु
	TMP51X_LOCAL_TEMP_RESULT,
	TMP51X_REMOTE_TEMP_RESULT_1,
	TMP51X_REMOTE_TEMP_RESULT_2,
	TMP513_REMOTE_TEMP_RESULT_3
पूर्ण;

अटल स्थिर u8 TMP51X_TEMP_CRIT[4] = अणु
	TMP51X_LOCAL_TEMP_LIMIT,
	TMP51X_REMOTE_TEMP_LIMIT_1,
	TMP51X_REMOTE_TEMP_LIMIT_2,
	TMP513_REMOTE_TEMP_LIMIT_3
पूर्ण;

अटल स्थिर u8 TMP51X_TEMP_CRIT_ALARM[4] = अणु
	TMP51X_LOCAL_TEMP_LIMIT_POS,
	TMP51X_REMOTE_TEMP_LIMIT_1_POS,
	TMP51X_REMOTE_TEMP_LIMIT_2_POS,
	TMP513_REMOTE_TEMP_LIMIT_3_POS
पूर्ण;

अटल स्थिर u8 TMP51X_TEMP_CRIT_HYST[4] = अणु
	TMP51X_N_FACTOR_AND_HYST_1,
	TMP51X_N_FACTOR_AND_HYST_1,
	TMP51X_N_FACTOR_AND_HYST_1,
	TMP51X_N_FACTOR_AND_HYST_1
पूर्ण;

अटल स्थिर u8 TMP51X_CURR_INPUT[2] = अणु
	TMP51X_SHUNT_CURRENT_RESULT,
	TMP51X_BUS_CURRENT_RESULT
पूर्ण;

अटल काष्ठा regmap_config पंचांगp51x_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = TMP51X_MAX_REGISTER_ADDR,
पूर्ण;

क्रमागत पंचांगp51x_ids अणु
	पंचांगp512, पंचांगp513
पूर्ण;

काष्ठा पंचांगp51x_data अणु
	u16 shunt_config;
	u16 pga_gain;
	u32 vbus_range_uvolt;

	u16 temp_config;
	u32 nfactor[3];

	u32 shunt_uohms;

	u32 curr_lsb_ua;
	u32 pwr_lsb_uw;

	क्रमागत पंचांगp51x_ids id;
	काष्ठा regmap *regmap;
पूर्ण;

// Set the shअगरt based on the gain 8=4, 4=3, 2=2, 1=1
अटल अंतरभूत u8 पंचांगp51x_get_pga_shअगरt(काष्ठा पंचांगp51x_data *data)
अणु
	वापस 5 - ffs(data->pga_gain);
पूर्ण

अटल पूर्णांक पंचांगp51x_get_value(काष्ठा पंचांगp51x_data *data, u8 reg, u8 pos,
			    अचिन्हित पूर्णांक regval, दीर्घ *val)
अणु
	चयन (reg) अणु
	हाल TMP51X_STATUS:
		*val = (regval >> pos) & 1;
		अवरोध;
	हाल TMP51X_SHUNT_CURRENT_RESULT:
	हाल TMP51X_SHUNT_CURRENT_H_LIMIT:
	हाल TMP51X_SHUNT_CURRENT_L_LIMIT:
		/*
		 * The valus is पढ़ो in voltage in the chip but reported as
		 * current to the user.
		 * 2's complement number shअगरted by one to four depending
		 * on the pga gain setting. 1lsb = 10uV
		 */
		*val = sign_extend32(regval, 17 - पंचांगp51x_get_pga_shअगरt(data));
		*val = DIV_ROUND_CLOSEST(*val * 10000, data->shunt_uohms);
		अवरोध;
	हाल TMP51X_BUS_VOLTAGE_RESULT:
	हाल TMP51X_BUS_VOLTAGE_H_LIMIT:
	हाल TMP51X_BUS_VOLTAGE_L_LIMIT:
		// 1lsb = 4mV
		*val = (regval >> TMP51X_BUS_VOLTAGE_SHIFT) * 4;
		अवरोध;
	हाल TMP51X_POWER_RESULT:
	हाल TMP51X_POWER_LIMIT:
		// Power = (current * BusVoltage) / 5000
		*val = regval * data->pwr_lsb_uw;
		अवरोध;
	हाल TMP51X_BUS_CURRENT_RESULT:
		// Current = (ShuntVoltage * CalibrationRegister) / 4096
		*val = sign_extend32(regval, 16) * data->curr_lsb_ua;
		*val = DIV_ROUND_CLOSEST(*val, 1000);
		अवरोध;
	हाल TMP51X_LOCAL_TEMP_RESULT:
	हाल TMP51X_REMOTE_TEMP_RESULT_1:
	हाल TMP51X_REMOTE_TEMP_RESULT_2:
	हाल TMP513_REMOTE_TEMP_RESULT_3:
	हाल TMP51X_LOCAL_TEMP_LIMIT:
	हाल TMP51X_REMOTE_TEMP_LIMIT_1:
	हाल TMP51X_REMOTE_TEMP_LIMIT_2:
	हाल TMP513_REMOTE_TEMP_LIMIT_3:
		// 1lsb = 0.0625 degrees centigrade
		*val = sign_extend32(regval, 16) >> TMP51X_TEMP_SHIFT;
		*val = DIV_ROUND_CLOSEST(*val * 625, 10);
		अवरोध;
	हाल TMP51X_N_FACTOR_AND_HYST_1:
		// 1lsb = 0.5 degrees centigrade
		*val = (regval & TMP51X_HYST_MASK) * 500;
		अवरोध;
	शेष:
		// Programmer goofed
		WARN_ON_ONCE(1);
		*val = 0;
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांगp51x_set_value(काष्ठा पंचांगp51x_data *data, u8 reg, दीर्घ val)
अणु
	पूर्णांक regval, max_val;
	u32 mask = 0;

	चयन (reg) अणु
	हाल TMP51X_SHUNT_CURRENT_H_LIMIT:
	हाल TMP51X_SHUNT_CURRENT_L_LIMIT:
		/*
		 * The user enter current value and we convert it to
		 * voltage. 1lsb = 10uV
		 */
		val = DIV_ROUND_CLOSEST(val * data->shunt_uohms, 10000);
		max_val = U16_MAX >> पंचांगp51x_get_pga_shअगरt(data);
		regval = clamp_val(val, -max_val, max_val);
		अवरोध;
	हाल TMP51X_BUS_VOLTAGE_H_LIMIT:
	हाल TMP51X_BUS_VOLTAGE_L_LIMIT:
		// 1lsb = 4mV
		max_val = (data->vbus_range_uvolt == TMP51X_VBUS_RANGE_32V) ?
			MAX_BUS_VOLTAGE_32_LIMIT : MAX_BUS_VOLTAGE_16_LIMIT;

		val = clamp_val(DIV_ROUND_CLOSEST(val, 4), 0, max_val);
		regval = val << TMP51X_BUS_VOLTAGE_SHIFT;
		अवरोध;
	हाल TMP51X_POWER_LIMIT:
		regval = clamp_val(DIV_ROUND_CLOSEST(val, data->pwr_lsb_uw), 0,
				   U16_MAX);
		अवरोध;
	हाल TMP51X_LOCAL_TEMP_LIMIT:
	हाल TMP51X_REMOTE_TEMP_LIMIT_1:
	हाल TMP51X_REMOTE_TEMP_LIMIT_2:
	हाल TMP513_REMOTE_TEMP_LIMIT_3:
		// 1lsb = 0.0625 degrees centigrade
		val = clamp_val(val, MIN_TEMP_LIMIT, MAX_TEMP_LIMIT);
		regval = DIV_ROUND_CLOSEST(val * 10, 625) << TMP51X_TEMP_SHIFT;
		अवरोध;
	हाल TMP51X_N_FACTOR_AND_HYST_1:
		// 1lsb = 0.5 degrees centigrade
		val = clamp_val(val, 0, MAX_TEMP_HYST);
		regval = DIV_ROUND_CLOSEST(val, 500);
		mask = TMP51X_HYST_MASK;
		अवरोध;
	शेष:
		// Programmer goofed
		WARN_ON_ONCE(1);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (mask == 0)
		वापस regmap_ग_लिखो(data->regmap, reg, regval);
	अन्यथा
		वापस regmap_update_bits(data->regmap, reg, mask, regval);
पूर्ण

अटल u8 पंचांगp51x_get_reg(क्रमागत hwmon_sensor_types type, u32 attr, पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_input:
			वापस TMP51X_TEMP_INPUT[channel];
		हाल hwmon_temp_crit_alarm:
			वापस TMP51X_STATUS;
		हाल hwmon_temp_crit:
			वापस TMP51X_TEMP_CRIT[channel];
		हाल hwmon_temp_crit_hyst:
			वापस TMP51X_TEMP_CRIT_HYST[channel];
		पूर्ण
		अवरोध;
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_input:
			वापस TMP51X_BUS_VOLTAGE_RESULT;
		हाल hwmon_in_lcrit_alarm:
		हाल hwmon_in_crit_alarm:
			वापस TMP51X_STATUS;
		हाल hwmon_in_lcrit:
			वापस TMP51X_BUS_VOLTAGE_L_LIMIT;
		हाल hwmon_in_crit:
			वापस TMP51X_BUS_VOLTAGE_H_LIMIT;
		पूर्ण
		अवरोध;
	हाल hwmon_curr:
		चयन (attr) अणु
		हाल hwmon_curr_input:
			वापस TMP51X_CURR_INPUT[channel];
		हाल hwmon_curr_lcrit_alarm:
		हाल hwmon_curr_crit_alarm:
			वापस TMP51X_STATUS;
		हाल hwmon_curr_lcrit:
			वापस TMP51X_SHUNT_CURRENT_L_LIMIT;
		हाल hwmon_curr_crit:
			वापस TMP51X_SHUNT_CURRENT_H_LIMIT;
		पूर्ण
		अवरोध;
	हाल hwmon_घातer:
		चयन (attr) अणु
		हाल hwmon_घातer_input:
			वापस TMP51X_POWER_RESULT;
		हाल hwmon_घातer_crit_alarm:
			वापस TMP51X_STATUS;
		हाल hwmon_घातer_crit:
			वापस TMP51X_POWER_LIMIT;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल u8 पंचांगp51x_get_status_pos(क्रमागत hwmon_sensor_types type, u32 attr,
				पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_crit_alarm:
			वापस TMP51X_TEMP_CRIT_ALARM[channel];
		पूर्ण
		अवरोध;
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_lcrit_alarm:
			वापस TMP51X_BUS_VOLTAGE_L_LIMIT_POS;
		हाल hwmon_in_crit_alarm:
			वापस TMP51X_BUS_VOLTAGE_H_LIMIT_POS;
		पूर्ण
		अवरोध;
	हाल hwmon_curr:
		चयन (attr) अणु
		हाल hwmon_curr_lcrit_alarm:
			वापस TMP51X_SHUNT_CURRENT_L_LIMIT_POS;
		हाल hwmon_curr_crit_alarm:
			वापस TMP51X_SHUNT_CURRENT_H_LIMIT_POS;
		पूर्ण
		अवरोध;
	हाल hwmon_घातer:
		चयन (attr) अणु
		हाल hwmon_घातer_crit_alarm:
			वापस TMP51X_POWER_LIMIT_POS;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांगp51x_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		       u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा पंचांगp51x_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;
	u32 regval;
	u8 pos = 0, reg = 0;

	reg = पंचांगp51x_get_reg(type, attr, channel);
	अगर (reg == 0)
		वापस -EOPNOTSUPP;

	अगर (reg == TMP51X_STATUS)
		pos = पंचांगp51x_get_status_pos(type, attr, channel);

	ret = regmap_पढ़ो(data->regmap, reg, &regval);
	अगर (ret < 0)
		वापस ret;

	वापस पंचांगp51x_get_value(data, reg, pos, regval, val);
पूर्ण

अटल पूर्णांक पंचांगp51x_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	u8 reg = 0;

	reg = पंचांगp51x_get_reg(type, attr, channel);
	अगर (reg == 0)
		वापस -EOPNOTSUPP;

	वापस पंचांगp51x_set_value(dev_get_drvdata(dev), reg, val);
पूर्ण

अटल umode_t पंचांगp51x_is_visible(स्थिर व्योम *_data,
				 क्रमागत hwmon_sensor_types type, u32 attr,
				 पूर्णांक channel)
अणु
	स्थिर काष्ठा पंचांगp51x_data *data = _data;

	चयन (type) अणु
	हाल hwmon_temp:
		अगर (data->id == पंचांगp512 && channel == 4)
			वापस 0;
		चयन (attr) अणु
		हाल hwmon_temp_input:
		हाल hwmon_temp_crit_alarm:
			वापस 0444;
		हाल hwmon_temp_crit:
			वापस 0644;
		हाल hwmon_temp_crit_hyst:
			अगर (channel == 0)
				वापस 0644;
			वापस 0444;
		पूर्ण
		अवरोध;
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_input:
		हाल hwmon_in_lcrit_alarm:
		हाल hwmon_in_crit_alarm:
			वापस 0444;
		हाल hwmon_in_lcrit:
		हाल hwmon_in_crit:
			वापस 0644;
		पूर्ण
		अवरोध;
	हाल hwmon_curr:
		अगर (!data->shunt_uohms)
			वापस 0;

		चयन (attr) अणु
		हाल hwmon_curr_input:
		हाल hwmon_curr_lcrit_alarm:
		हाल hwmon_curr_crit_alarm:
			वापस 0444;
		हाल hwmon_curr_lcrit:
		हाल hwmon_curr_crit:
			वापस 0644;
		पूर्ण
		अवरोध;
	हाल hwmon_घातer:
		अगर (!data->shunt_uohms)
			वापस 0;

		चयन (attr) अणु
		हाल hwmon_घातer_input:
		हाल hwmon_घातer_crit_alarm:
			वापस 0444;
		हाल hwmon_घातer_crit:
			वापस 0644;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *पंचांगp51x_info[] = अणु
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_CRIT | HWMON_T_CRIT_ALARM |
			   HWMON_T_CRIT_HYST,
			   HWMON_T_INPUT | HWMON_T_CRIT | HWMON_T_CRIT_ALARM |
			   HWMON_T_CRIT_HYST,
			   HWMON_T_INPUT | HWMON_T_CRIT | HWMON_T_CRIT_ALARM |
			   HWMON_T_CRIT_HYST,
			   HWMON_T_INPUT | HWMON_T_CRIT | HWMON_T_CRIT_ALARM |
			   HWMON_T_CRIT_HYST),
	HWMON_CHANNEL_INFO(in,
			   HWMON_I_INPUT | HWMON_I_LCRIT | HWMON_I_LCRIT_ALARM |
			   HWMON_I_CRIT | HWMON_I_CRIT_ALARM),
	HWMON_CHANNEL_INFO(curr,
			   HWMON_C_INPUT | HWMON_C_LCRIT | HWMON_C_LCRIT_ALARM |
			   HWMON_C_CRIT | HWMON_C_CRIT_ALARM,
			   HWMON_C_INPUT),
	HWMON_CHANNEL_INFO(घातer,
			   HWMON_P_INPUT | HWMON_P_CRIT | HWMON_P_CRIT_ALARM),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops पंचांगp51x_hwmon_ops = अणु
	.is_visible = पंचांगp51x_is_visible,
	.पढ़ो = पंचांगp51x_पढ़ो,
	.ग_लिखो = पंचांगp51x_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info पंचांगp51x_chip_info = अणु
	.ops = &पंचांगp51x_hwmon_ops,
	.info = पंचांगp51x_info,
पूर्ण;

/*
 * Calibrate the पंचांगp51x following the datasheet method
 */
अटल पूर्णांक पंचांगp51x_calibrate(काष्ठा पंचांगp51x_data *data)
अणु
	पूर्णांक vshunt_max = data->pga_gain * 40;
	u64 max_curr_ma;
	u32 भाग;

	/*
	 * If shunt_uohms is equal to 0, the calibration should be set to 0.
	 * The consequence will be that the current and घातer measurement engine
	 * of the sensor will not work. Temperature and voltage sensing will
	 * जारी to work.
	 */
	अगर (data->shunt_uohms == 0)
		वापस regmap_ग_लिखो(data->regmap, TMP51X_SHUNT_CALIBRATION, 0);

	max_curr_ma = DIV_ROUND_CLOSEST_ULL(vshunt_max * 1000 * 1000,
					    data->shunt_uohms);

	/*
	 * Calculate the minimal bit resolution क्रम the current and the घातer.
	 * Those values will be used during रेजिस्टर पूर्णांकerpretation.
	 */
	data->curr_lsb_ua = DIV_ROUND_CLOSEST_ULL(max_curr_ma * 1000, 32767);
	data->pwr_lsb_uw = 20 * data->curr_lsb_ua;

	भाग = DIV_ROUND_CLOSEST_ULL(data->curr_lsb_ua * data->shunt_uohms,
				    1000 * 1000);

	वापस regmap_ग_लिखो(data->regmap, TMP51X_SHUNT_CALIBRATION,
			    DIV_ROUND_CLOSEST(40960, भाग));
पूर्ण

/*
 * Initialize the configuration and calibration रेजिस्टरs.
 */
अटल पूर्णांक पंचांगp51x_init(काष्ठा पंचांगp51x_data *data)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret = regmap_ग_लिखो(data->regmap, TMP51X_SHUNT_CONFIG,
			       data->shunt_config);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(data->regmap, TMP51X_TEMP_CONFIG, data->temp_config);
	अगर (ret < 0)
		वापस ret;

	// nFactor configuration
	ret = regmap_update_bits(data->regmap, TMP51X_N_FACTOR_AND_HYST_1,
				 TMP51X_NFACTOR_MASK, data->nfactor[0] << 8);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(data->regmap, TMP51X_N_FACTOR_2,
			   data->nfactor[1] << 8);
	अगर (ret < 0)
		वापस ret;

	अगर (data->id == पंचांगp513) अणु
		ret = regmap_ग_लिखो(data->regmap, TMP513_N_FACTOR_3,
				   data->nfactor[2] << 8);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = पंचांगp51x_calibrate(data);
	अगर (ret < 0)
		वापस ret;

	// Read the status रेजिस्टर beक्रमe using as the datasheet propose
	वापस regmap_पढ़ो(data->regmap, TMP51X_STATUS, &regval);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id पंचांगp51x_id[] = अणु
	अणु "tmp512", पंचांगp512 पूर्ण,
	अणु "tmp513", पंचांगp513 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, पंचांगp51x_id);

अटल स्थिर काष्ठा of_device_id पंचांगp51x_of_match[] = अणु
	अणु
		.compatible = "ti,tmp512",
		.data = (व्योम *)पंचांगp512
	पूर्ण,
	अणु
		.compatible = "ti,tmp513",
		.data = (व्योम *)पंचांगp513
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, पंचांगp51x_of_match);

अटल पूर्णांक पंचांगp51x_vbus_range_to_reg(काष्ठा device *dev,
				    काष्ठा पंचांगp51x_data *data)
अणु
	अगर (data->vbus_range_uvolt == TMP51X_VBUS_RANGE_32V) अणु
		data->shunt_config |= TMP51X_BUS_VOLTAGE_MASK;
	पूर्ण अन्यथा अगर (data->vbus_range_uvolt == TMP51X_VBUS_RANGE_16V) अणु
		data->shunt_config &= ~TMP51X_BUS_VOLTAGE_MASK;
	पूर्ण अन्यथा अणु
		dev_err(dev, "ti,bus-range-microvolt is invalid: %u\n",
			data->vbus_range_uvolt);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पंचांगp51x_pga_gain_to_reg(काष्ठा device *dev, काष्ठा पंचांगp51x_data *data)
अणु
	अगर (data->pga_gain == 8) अणु
		data->shunt_config |= CURRENT_SENSE_VOLTAGE_320_MASK;
	पूर्ण अन्यथा अगर (data->pga_gain == 4) अणु
		data->shunt_config |= CURRENT_SENSE_VOLTAGE_160_MASK;
	पूर्ण अन्यथा अगर (data->pga_gain == 2) अणु
		data->shunt_config |= CURRENT_SENSE_VOLTAGE_80_MASK;
	पूर्ण अन्यथा अगर (data->pga_gain == 1) अणु
		data->shunt_config |= CURRENT_SENSE_VOLTAGE_40_MASK;
	पूर्ण अन्यथा अणु
		dev_err(dev, "ti,pga-gain is invalid: %u\n", data->pga_gain);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पंचांगp51x_पढ़ो_properties(काष्ठा device *dev, काष्ठा पंचांगp51x_data *data)
अणु
	पूर्णांक ret;
	u32 nfactor[3];
	u32 val;

	ret = device_property_पढ़ो_u32(dev, "shunt-resistor-micro-ohms", &val);
	data->shunt_uohms = (ret >= 0) ? val : TMP51X_SHUNT_VALUE_DEFAULT;

	ret = device_property_पढ़ो_u32(dev, "ti,bus-range-microvolt", &val);
	data->vbus_range_uvolt = (ret >= 0) ? val : TMP51X_VBUS_RANGE_DEFAULT;
	ret = पंचांगp51x_vbus_range_to_reg(dev, data);
	अगर (ret < 0)
		वापस ret;

	ret = device_property_पढ़ो_u32(dev, "ti,pga-gain", &val);
	data->pga_gain = (ret >= 0) ? val : TMP51X_PGA_DEFAULT;
	ret = पंचांगp51x_pga_gain_to_reg(dev, data);
	अगर (ret < 0)
		वापस ret;

	ret = device_property_पढ़ो_u32_array(dev, "ti,nfactor", nfactor,
					    (data->id == पंचांगp513) ? 3 : 2);
	अगर (ret >= 0)
		स_नकल(data->nfactor, nfactor, (data->id == पंचांगp513) ? 3 : 2);

	// Check अगर shunt value is compatible with pga-gain
	अगर (data->shunt_uohms > data->pga_gain * 40 * 1000 * 1000) अणु
		dev_err(dev, "shunt-resistor: %u too big for pga_gain: %u\n",
			data->shunt_uohms, data->pga_gain);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम पंचांगp51x_use_शेष(काष्ठा पंचांगp51x_data *data)
अणु
	data->vbus_range_uvolt = TMP51X_VBUS_RANGE_DEFAULT;
	data->pga_gain = TMP51X_PGA_DEFAULT;
	data->shunt_uohms = TMP51X_SHUNT_VALUE_DEFAULT;
पूर्ण

अटल पूर्णांक पंचांगp51x_configure(काष्ठा device *dev, काष्ठा पंचांगp51x_data *data)
अणु
	data->shunt_config = TMP51X_SHUNT_CONFIG_DEFAULT;
	data->temp_config = (data->id == पंचांगp513) ?
			TMP513_TEMP_CONFIG_DEFAULT : TMP512_TEMP_CONFIG_DEFAULT;

	अगर (dev->of_node)
		वापस पंचांगp51x_पढ़ो_properties(dev, data);

	पंचांगp51x_use_शेष(data);

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांगp51x_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा पंचांगp51x_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक ret;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	अगर (client->dev.of_node)
		data->id = (क्रमागत पंचांगp51x_ids)device_get_match_data(&client->dev);
	अन्यथा
		data->id = i2c_match_id(पंचांगp51x_id, client)->driver_data;

	ret = पंचांगp51x_configure(dev, data);
	अगर (ret < 0) अणु
		dev_err(dev, "error configuring the device: %d\n", ret);
		वापस ret;
	पूर्ण

	data->regmap = devm_regmap_init_i2c(client, &पंचांगp51x_regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		dev_err(dev, "failed to allocate register map\n");
		वापस PTR_ERR(data->regmap);
	पूर्ण

	ret = पंचांगp51x_init(data);
	अगर (ret < 0) अणु
		dev_err(dev, "error configuring the device: %d\n", ret);
		वापस -ENODEV;
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, client->name,
							 data,
							 &पंचांगp51x_chip_info,
							 शून्य);
	अगर (IS_ERR(hwmon_dev))
		वापस PTR_ERR(hwmon_dev);

	dev_dbg(dev, "power monitor %s\n", client->name);

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver पंचांगp51x_driver = अणु
	.driver = अणु
		.name	= "tmp51x",
		.of_match_table = of_match_ptr(पंचांगp51x_of_match),
	पूर्ण,
	.probe_new	= पंचांगp51x_probe,
	.id_table	= पंचांगp51x_id,
पूर्ण;

module_i2c_driver(पंचांगp51x_driver);

MODULE_AUTHOR("Eric Tremblay <etremblay@distechcontrols.com>");
MODULE_DESCRIPTION("tmp51x driver");
MODULE_LICENSE("GPL");
