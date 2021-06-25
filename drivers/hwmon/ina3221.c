<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * INA3221 Triple Current/Voltage Monitor
 *
 * Copyright (C) 2016 Texas Instruments Incorporated - https://www.ti.com/
 *	Andrew F. Davis <afd@ti.com>
 */

#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/util_macros.h>

#घोषणा INA3221_DRIVER_NAME		"ina3221"

#घोषणा INA3221_CONFIG			0x00
#घोषणा INA3221_SHUNT1			0x01
#घोषणा INA3221_BUS1			0x02
#घोषणा INA3221_SHUNT2			0x03
#घोषणा INA3221_BUS2			0x04
#घोषणा INA3221_SHUNT3			0x05
#घोषणा INA3221_BUS3			0x06
#घोषणा INA3221_CRIT1			0x07
#घोषणा INA3221_WARN1			0x08
#घोषणा INA3221_CRIT2			0x09
#घोषणा INA3221_WARN2			0x0a
#घोषणा INA3221_CRIT3			0x0b
#घोषणा INA3221_WARN3			0x0c
#घोषणा INA3221_SHUNT_SUM		0x0d
#घोषणा INA3221_CRIT_SUM		0x0e
#घोषणा INA3221_MASK_ENABLE		0x0f

#घोषणा INA3221_CONFIG_MODE_MASK	GENMASK(2, 0)
#घोषणा INA3221_CONFIG_MODE_POWERDOWN	0
#घोषणा INA3221_CONFIG_MODE_SHUNT	BIT(0)
#घोषणा INA3221_CONFIG_MODE_BUS		BIT(1)
#घोषणा INA3221_CONFIG_MODE_CONTINUOUS	BIT(2)
#घोषणा INA3221_CONFIG_VSH_CT_SHIFT	3
#घोषणा INA3221_CONFIG_VSH_CT_MASK	GENMASK(5, 3)
#घोषणा INA3221_CONFIG_VSH_CT(x)	(((x) & GENMASK(5, 3)) >> 3)
#घोषणा INA3221_CONFIG_VBUS_CT_SHIFT	6
#घोषणा INA3221_CONFIG_VBUS_CT_MASK	GENMASK(8, 6)
#घोषणा INA3221_CONFIG_VBUS_CT(x)	(((x) & GENMASK(8, 6)) >> 6)
#घोषणा INA3221_CONFIG_AVG_SHIFT	9
#घोषणा INA3221_CONFIG_AVG_MASK		GENMASK(11, 9)
#घोषणा INA3221_CONFIG_AVG(x)		(((x) & GENMASK(11, 9)) >> 9)
#घोषणा INA3221_CONFIG_CHs_EN_MASK	GENMASK(14, 12)
#घोषणा INA3221_CONFIG_CHx_EN(x)	BIT(14 - (x))

#घोषणा INA3221_MASK_ENABLE_SCC_MASK	GENMASK(14, 12)

#घोषणा INA3221_CONFIG_DEFAULT		0x7127
#घोषणा INA3221_RSHUNT_DEFAULT		10000

क्रमागत ina3221_fields अणु
	/* Configuration */
	F_RST,

	/* Status Flags */
	F_CVRF,

	/* Warning Flags */
	F_WF3, F_WF2, F_WF1,

	/* Alert Flags: SF is the summation-alert flag */
	F_SF, F_CF3, F_CF2, F_CF1,

	/* sentinel */
	F_MAX_FIELDS
पूर्ण;

अटल स्थिर काष्ठा reg_field ina3221_reg_fields[] = अणु
	[F_RST] = REG_FIELD(INA3221_CONFIG, 15, 15),

	[F_CVRF] = REG_FIELD(INA3221_MASK_ENABLE, 0, 0),
	[F_WF3] = REG_FIELD(INA3221_MASK_ENABLE, 3, 3),
	[F_WF2] = REG_FIELD(INA3221_MASK_ENABLE, 4, 4),
	[F_WF1] = REG_FIELD(INA3221_MASK_ENABLE, 5, 5),
	[F_SF] = REG_FIELD(INA3221_MASK_ENABLE, 6, 6),
	[F_CF3] = REG_FIELD(INA3221_MASK_ENABLE, 7, 7),
	[F_CF2] = REG_FIELD(INA3221_MASK_ENABLE, 8, 8),
	[F_CF1] = REG_FIELD(INA3221_MASK_ENABLE, 9, 9),
पूर्ण;

क्रमागत ina3221_channels अणु
	INA3221_CHANNEL1,
	INA3221_CHANNEL2,
	INA3221_CHANNEL3,
	INA3221_NUM_CHANNELS
पूर्ण;

/**
 * काष्ठा ina3221_input - channel input source specअगरic inक्रमmation
 * @label: label of channel input source
 * @shunt_resistor: shunt resistor value of channel input source
 * @disconnected: connection status of channel input source
 */
काष्ठा ina3221_input अणु
	स्थिर अक्षर *label;
	पूर्णांक shunt_resistor;
	bool disconnected;
पूर्ण;

/**
 * काष्ठा ina3221_data - device specअगरic inक्रमmation
 * @pm_dev: Device poपूर्णांकer क्रम pm runसमय
 * @regmap: Register map of the device
 * @fields: Register fields of the device
 * @inमाला_दो: Array of channel input source specअगरic काष्ठाures
 * @lock: mutex lock to serialize sysfs attribute accesses
 * @reg_config: Register value of INA3221_CONFIG
 * @summation_shunt_resistor: equivalent shunt resistor value क्रम summation
 * @single_shot: running in single-shot operating mode
 */
काष्ठा ina3221_data अणु
	काष्ठा device *pm_dev;
	काष्ठा regmap *regmap;
	काष्ठा regmap_field *fields[F_MAX_FIELDS];
	काष्ठा ina3221_input inमाला_दो[INA3221_NUM_CHANNELS];
	काष्ठा mutex lock;
	u32 reg_config;
	पूर्णांक summation_shunt_resistor;

	bool single_shot;
पूर्ण;

अटल अंतरभूत bool ina3221_is_enabled(काष्ठा ina3221_data *ina, पूर्णांक channel)
अणु
	/* Summation channel checks shunt resistor values */
	अगर (channel > INA3221_CHANNEL3)
		वापस ina->summation_shunt_resistor != 0;

	वापस pm_runसमय_active(ina->pm_dev) &&
	       (ina->reg_config & INA3221_CONFIG_CHx_EN(channel));
पूर्ण

/*
 * Helper function to वापस the resistor value क्रम current summation.
 *
 * There is a condition to calculate current summation -- all the shunt
 * resistor values should be the same, so as to simply fit the क्रमmula:
 *     current summation = shunt voltage summation / shunt resistor
 *
 * Returns the equivalent shunt resistor value on success or 0 on failure
 */
अटल अंतरभूत पूर्णांक ina3221_summation_shunt_resistor(काष्ठा ina3221_data *ina)
अणु
	काष्ठा ina3221_input *input = ina->inमाला_दो;
	पूर्णांक i, shunt_resistor = 0;

	क्रम (i = 0; i < INA3221_NUM_CHANNELS; i++) अणु
		अगर (input[i].disconnected || !input[i].shunt_resistor)
			जारी;
		अगर (!shunt_resistor) अणु
			/* Found the reference shunt resistor value */
			shunt_resistor = input[i].shunt_resistor;
		पूर्ण अन्यथा अणु
			/* No summation अगर resistor values are dअगरferent */
			अगर (shunt_resistor != input[i].shunt_resistor)
				वापस 0;
		पूर्ण
	पूर्ण

	वापस shunt_resistor;
पूर्ण

/* Lookup table क्रम Bus and Shunt conversion बार in usec */
अटल स्थिर u16 ina3221_conv_समय[] = अणु
	140, 204, 332, 588, 1100, 2116, 4156, 8244,
पूर्ण;

/* Lookup table क्रम number of samples using in averaging mode */
अटल स्थिर पूर्णांक ina3221_avg_samples[] = अणु
	1, 4, 16, 64, 128, 256, 512, 1024,
पूर्ण;

/* Converting update_पूर्णांकerval in msec to conversion समय in usec */
अटल अंतरभूत u32 ina3221_पूर्णांकerval_ms_to_conv_समय(u16 config, पूर्णांक पूर्णांकerval)
अणु
	u32 channels = hweight16(config & INA3221_CONFIG_CHs_EN_MASK);
	u32 samples_idx = INA3221_CONFIG_AVG(config);
	u32 samples = ina3221_avg_samples[samples_idx];

	/* Bisect the result to Bus and Shunt conversion बार */
	वापस DIV_ROUND_CLOSEST(पूर्णांकerval * 1000 / 2, channels * samples);
पूर्ण

/* Converting CONFIG रेजिस्टर value to update_पूर्णांकerval in usec */
अटल अंतरभूत u32 ina3221_reg_to_पूर्णांकerval_us(u16 config)
अणु
	u32 channels = hweight16(config & INA3221_CONFIG_CHs_EN_MASK);
	u32 vbus_ct_idx = INA3221_CONFIG_VBUS_CT(config);
	u32 vsh_ct_idx = INA3221_CONFIG_VSH_CT(config);
	u32 samples_idx = INA3221_CONFIG_AVG(config);
	u32 samples = ina3221_avg_samples[samples_idx];
	u32 vbus_ct = ina3221_conv_समय[vbus_ct_idx];
	u32 vsh_ct = ina3221_conv_समय[vsh_ct_idx];

	/* Calculate total conversion समय */
	वापस channels * (vbus_ct + vsh_ct) * samples;
पूर्ण

अटल अंतरभूत पूर्णांक ina3221_रुको_क्रम_data(काष्ठा ina3221_data *ina)
अणु
	u32 रुको, cvrf;

	रुको = ina3221_reg_to_पूर्णांकerval_us(ina->reg_config);

	/* Polling the CVRF bit to make sure पढ़ो data is पढ़ोy */
	वापस regmap_field_पढ़ो_poll_समयout(ina->fields[F_CVRF],
					      cvrf, cvrf, रुको, रुको * 2);
पूर्ण

अटल पूर्णांक ina3221_पढ़ो_value(काष्ठा ina3221_data *ina, अचिन्हित पूर्णांक reg,
			      पूर्णांक *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(ina->regmap, reg, &regval);
	अगर (ret)
		वापस ret;

	/*
	 * Shunt Voltage Sum रेजिस्टर has 14-bit value with 1-bit shअगरt
	 * Other Shunt Voltage रेजिस्टरs have 12 bits with 3-bit shअगरt
	 */
	अगर (reg == INA3221_SHUNT_SUM)
		*val = sign_extend32(regval >> 1, 14);
	अन्यथा
		*val = sign_extend32(regval >> 3, 12);

	वापस 0;
पूर्ण

अटल स्थिर u8 ina3221_in_reg[] = अणु
	INA3221_BUS1,
	INA3221_BUS2,
	INA3221_BUS3,
	INA3221_SHUNT1,
	INA3221_SHUNT2,
	INA3221_SHUNT3,
	INA3221_SHUNT_SUM,
पूर्ण;

अटल पूर्णांक ina3221_पढ़ो_chip(काष्ठा device *dev, u32 attr, दीर्घ *val)
अणु
	काष्ठा ina3221_data *ina = dev_get_drvdata(dev);
	पूर्णांक regval;

	चयन (attr) अणु
	हाल hwmon_chip_samples:
		regval = INA3221_CONFIG_AVG(ina->reg_config);
		*val = ina3221_avg_samples[regval];
		वापस 0;
	हाल hwmon_chip_update_पूर्णांकerval:
		/* Return in msec */
		*val = ina3221_reg_to_पूर्णांकerval_us(ina->reg_config);
		*val = DIV_ROUND_CLOSEST(*val, 1000);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ina3221_पढ़ो_in(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	स्थिर bool is_shunt = channel > INA3221_CHANNEL3;
	काष्ठा ina3221_data *ina = dev_get_drvdata(dev);
	u8 reg = ina3221_in_reg[channel];
	पूर्णांक regval, ret;

	/*
	 * Translate shunt channel index to sensor channel index except
	 * the 7th channel (6 since being 0-aligned) is क्रम summation.
	 */
	अगर (channel != 6)
		channel %= INA3221_NUM_CHANNELS;

	चयन (attr) अणु
	हाल hwmon_in_input:
		अगर (!ina3221_is_enabled(ina, channel))
			वापस -ENODATA;

		/* Write CONFIG रेजिस्टर to trigger a single-shot measurement */
		अगर (ina->single_shot)
			regmap_ग_लिखो(ina->regmap, INA3221_CONFIG,
				     ina->reg_config);

		ret = ina3221_रुको_क्रम_data(ina);
		अगर (ret)
			वापस ret;

		ret = ina3221_पढ़ो_value(ina, reg, &regval);
		अगर (ret)
			वापस ret;

		/*
		 * Scale of shunt voltage (uV): LSB is 40uV
		 * Scale of bus voltage (mV): LSB is 8mV
		 */
		*val = regval * (is_shunt ? 40 : 8);
		वापस 0;
	हाल hwmon_in_enable:
		*val = ina3221_is_enabled(ina, channel);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर u8 ina3221_curr_reg[][INA3221_NUM_CHANNELS + 1] = अणु
	[hwmon_curr_input] = अणु INA3221_SHUNT1, INA3221_SHUNT2,
			       INA3221_SHUNT3, INA3221_SHUNT_SUM पूर्ण,
	[hwmon_curr_max] = अणु INA3221_WARN1, INA3221_WARN2, INA3221_WARN3, 0 पूर्ण,
	[hwmon_curr_crit] = अणु INA3221_CRIT1, INA3221_CRIT2,
			      INA3221_CRIT3, INA3221_CRIT_SUM पूर्ण,
	[hwmon_curr_max_alarm] = अणु F_WF1, F_WF2, F_WF3, 0 पूर्ण,
	[hwmon_curr_crit_alarm] = अणु F_CF1, F_CF2, F_CF3, F_SF पूर्ण,
पूर्ण;

अटल पूर्णांक ina3221_पढ़ो_curr(काष्ठा device *dev, u32 attr,
			     पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा ina3221_data *ina = dev_get_drvdata(dev);
	काष्ठा ina3221_input *input = ina->inमाला_दो;
	u8 reg = ina3221_curr_reg[attr][channel];
	पूर्णांक resistance_uo, voltage_nv;
	पूर्णांक regval, ret;

	अगर (channel > INA3221_CHANNEL3)
		resistance_uo = ina->summation_shunt_resistor;
	अन्यथा
		resistance_uo = input[channel].shunt_resistor;

	चयन (attr) अणु
	हाल hwmon_curr_input:
		अगर (!ina3221_is_enabled(ina, channel))
			वापस -ENODATA;

		/* Write CONFIG रेजिस्टर to trigger a single-shot measurement */
		अगर (ina->single_shot)
			regmap_ग_लिखो(ina->regmap, INA3221_CONFIG,
				     ina->reg_config);

		ret = ina3221_रुको_क्रम_data(ina);
		अगर (ret)
			वापस ret;

		fallthrough;
	हाल hwmon_curr_crit:
	हाल hwmon_curr_max:
		अगर (!resistance_uo)
			वापस -ENODATA;

		ret = ina3221_पढ़ो_value(ina, reg, &regval);
		अगर (ret)
			वापस ret;

		/* Scale of shunt voltage: LSB is 40uV (40000nV) */
		voltage_nv = regval * 40000;
		/* Return current in mA */
		*val = DIV_ROUND_CLOSEST(voltage_nv, resistance_uo);
		वापस 0;
	हाल hwmon_curr_crit_alarm:
	हाल hwmon_curr_max_alarm:
		/* No actual रेजिस्टर पढ़ो अगर channel is disabled */
		अगर (!ina3221_is_enabled(ina, channel)) अणु
			/* Return 0 क्रम alert flags */
			*val = 0;
			वापस 0;
		पूर्ण
		ret = regmap_field_पढ़ो(ina->fields[reg], &regval);
		अगर (ret)
			वापस ret;
		*val = regval;
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ina3221_ग_लिखो_chip(काष्ठा device *dev, u32 attr, दीर्घ val)
अणु
	काष्ठा ina3221_data *ina = dev_get_drvdata(dev);
	पूर्णांक ret, idx;
	u32 पंचांगp;

	चयन (attr) अणु
	हाल hwmon_chip_samples:
		idx = find_बंदst(val, ina3221_avg_samples,
				   ARRAY_SIZE(ina3221_avg_samples));

		पंचांगp = (ina->reg_config & ~INA3221_CONFIG_AVG_MASK) |
		      (idx << INA3221_CONFIG_AVG_SHIFT);
		ret = regmap_ग_लिखो(ina->regmap, INA3221_CONFIG, पंचांगp);
		अगर (ret)
			वापस ret;

		/* Update reg_config accordingly */
		ina->reg_config = पंचांगp;
		वापस 0;
	हाल hwmon_chip_update_पूर्णांकerval:
		पंचांगp = ina3221_पूर्णांकerval_ms_to_conv_समय(ina->reg_config, val);
		idx = find_बंदst(पंचांगp, ina3221_conv_समय,
				   ARRAY_SIZE(ina3221_conv_समय));

		/* Update Bus and Shunt voltage conversion बार */
		पंचांगp = INA3221_CONFIG_VBUS_CT_MASK | INA3221_CONFIG_VSH_CT_MASK;
		पंचांगp = (ina->reg_config & ~पंचांगp) |
		      (idx << INA3221_CONFIG_VBUS_CT_SHIFT) |
		      (idx << INA3221_CONFIG_VSH_CT_SHIFT);
		ret = regmap_ग_लिखो(ina->regmap, INA3221_CONFIG, पंचांगp);
		अगर (ret)
			वापस ret;

		/* Update reg_config accordingly */
		ina->reg_config = पंचांगp;
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ina3221_ग_लिखो_curr(काष्ठा device *dev, u32 attr,
			      पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा ina3221_data *ina = dev_get_drvdata(dev);
	काष्ठा ina3221_input *input = ina->inमाला_दो;
	u8 reg = ina3221_curr_reg[attr][channel];
	पूर्णांक resistance_uo, current_ma, voltage_uv;
	पूर्णांक regval;

	अगर (channel > INA3221_CHANNEL3)
		resistance_uo = ina->summation_shunt_resistor;
	अन्यथा
		resistance_uo = input[channel].shunt_resistor;

	अगर (!resistance_uo)
		वापस -EOPNOTSUPP;

	/* clamp current */
	current_ma = clamp_val(val,
			       पूर्णांक_न्यून / resistance_uo,
			       पूर्णांक_उच्च / resistance_uo);

	voltage_uv = DIV_ROUND_CLOSEST(current_ma * resistance_uo, 1000);

	/* clamp voltage */
	voltage_uv = clamp_val(voltage_uv, -163800, 163800);

	/*
	 * Formula to convert voltage_uv to रेजिस्टर value:
	 *     regval = (voltage_uv / scale) << shअगरt
	 * Note:
	 *     The scale is 40uV क्रम all shunt voltage रेजिस्टरs
	 *     Shunt Voltage Sum रेजिस्टर left-shअगरts 1 bit
	 *     All other Shunt Voltage रेजिस्टरs shअगरt 3 bits
	 * Results:
	 *     SHUNT_SUM: (1 / 40uV) << 1 = 1 / 20uV
	 *     SHUNT[1-3]: (1 / 40uV) << 3 = 1 / 5uV
	 */
	अगर (reg == INA3221_SHUNT_SUM)
		regval = DIV_ROUND_CLOSEST(voltage_uv, 20) & 0xfffe;
	अन्यथा
		regval = DIV_ROUND_CLOSEST(voltage_uv, 5) & 0xfff8;

	वापस regmap_ग_लिखो(ina->regmap, reg, regval);
पूर्ण

अटल पूर्णांक ina3221_ग_लिखो_enable(काष्ठा device *dev, पूर्णांक channel, bool enable)
अणु
	काष्ठा ina3221_data *ina = dev_get_drvdata(dev);
	u16 config, mask = INA3221_CONFIG_CHx_EN(channel);
	u16 config_old = ina->reg_config & mask;
	u32 पंचांगp;
	पूर्णांक ret;

	config = enable ? mask : 0;

	/* Bypass अगर enable status is not being changed */
	अगर (config_old == config)
		वापस 0;

	/* For enabling routine, increase refcount and resume() at first */
	अगर (enable) अणु
		ret = pm_runसमय_resume_and_get(ina->pm_dev);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to get PM runtime\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* Enable or disable the channel */
	पंचांगp = (ina->reg_config & ~mask) | (config & mask);
	ret = regmap_ग_लिखो(ina->regmap, INA3221_CONFIG, पंचांगp);
	अगर (ret)
		जाओ fail;

	/* Cache the latest config रेजिस्टर value */
	ina->reg_config = पंचांगp;

	/* For disabling routine, decrease refcount or suspend() at last */
	अगर (!enable)
		pm_runसमय_put_sync(ina->pm_dev);

	वापस 0;

fail:
	अगर (enable) अणु
		dev_err(dev, "Failed to enable channel %d: error %d\n",
			channel, ret);
		pm_runसमय_put_sync(ina->pm_dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ina3221_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा ina3221_data *ina = dev_get_drvdata(dev);
	पूर्णांक ret;

	mutex_lock(&ina->lock);

	चयन (type) अणु
	हाल hwmon_chip:
		ret = ina3221_पढ़ो_chip(dev, attr, val);
		अवरोध;
	हाल hwmon_in:
		/* 0-align channel ID */
		ret = ina3221_पढ़ो_in(dev, attr, channel - 1, val);
		अवरोध;
	हाल hwmon_curr:
		ret = ina3221_पढ़ो_curr(dev, attr, channel, val);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	mutex_unlock(&ina->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ina3221_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			 u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा ina3221_data *ina = dev_get_drvdata(dev);
	पूर्णांक ret;

	mutex_lock(&ina->lock);

	चयन (type) अणु
	हाल hwmon_chip:
		ret = ina3221_ग_लिखो_chip(dev, attr, val);
		अवरोध;
	हाल hwmon_in:
		/* 0-align channel ID */
		ret = ina3221_ग_लिखो_enable(dev, channel - 1, val);
		अवरोध;
	हाल hwmon_curr:
		ret = ina3221_ग_लिखो_curr(dev, attr, channel, val);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	mutex_unlock(&ina->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ina3221_पढ़ो_string(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			       u32 attr, पूर्णांक channel, स्थिर अक्षर **str)
अणु
	काष्ठा ina3221_data *ina = dev_get_drvdata(dev);
	पूर्णांक index = channel - 1;

	अगर (channel == 7)
		*str = "sum of shunt voltages";
	अन्यथा
		*str = ina->inमाला_दो[index].label;

	वापस 0;
पूर्ण

अटल umode_t ina3221_is_visible(स्थिर व्योम *drvdata,
				  क्रमागत hwmon_sensor_types type,
				  u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा ina3221_data *ina = drvdata;
	स्थिर काष्ठा ina3221_input *input = शून्य;

	चयन (type) अणु
	हाल hwmon_chip:
		चयन (attr) अणु
		हाल hwmon_chip_samples:
		हाल hwmon_chip_update_पूर्णांकerval:
			वापस 0644;
		शेष:
			वापस 0;
		पूर्ण
	हाल hwmon_in:
		/* Ignore in0_ */
		अगर (channel == 0)
			वापस 0;

		चयन (attr) अणु
		हाल hwmon_in_label:
			अगर (channel - 1 <= INA3221_CHANNEL3)
				input = &ina->inमाला_दो[channel - 1];
			अन्यथा अगर (channel == 7)
				वापस 0444;
			/* Hide label node अगर label is not provided */
			वापस (input && input->label) ? 0444 : 0;
		हाल hwmon_in_input:
			वापस 0444;
		हाल hwmon_in_enable:
			वापस 0644;
		शेष:
			वापस 0;
		पूर्ण
	हाल hwmon_curr:
		चयन (attr) अणु
		हाल hwmon_curr_input:
		हाल hwmon_curr_crit_alarm:
		हाल hwmon_curr_max_alarm:
			वापस 0444;
		हाल hwmon_curr_crit:
		हाल hwmon_curr_max:
			वापस 0644;
		शेष:
			वापस 0;
		पूर्ण
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

#घोषणा INA3221_HWMON_CURR_CONFIG (HWMON_C_INPUT | \
				   HWMON_C_CRIT | HWMON_C_CRIT_ALARM | \
				   HWMON_C_MAX | HWMON_C_MAX_ALARM)

अटल स्थिर काष्ठा hwmon_channel_info *ina3221_info[] = अणु
	HWMON_CHANNEL_INFO(chip,
			   HWMON_C_SAMPLES,
			   HWMON_C_UPDATE_INTERVAL),
	HWMON_CHANNEL_INFO(in,
			   /* 0: dummy, skipped in is_visible */
			   HWMON_I_INPUT,
			   /* 1-3: input voltage Channels */
			   HWMON_I_INPUT | HWMON_I_ENABLE | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_ENABLE | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_ENABLE | HWMON_I_LABEL,
			   /* 4-6: shunt voltage Channels */
			   HWMON_I_INPUT,
			   HWMON_I_INPUT,
			   HWMON_I_INPUT,
			   /* 7: summation of shunt voltage channels */
			   HWMON_I_INPUT | HWMON_I_LABEL),
	HWMON_CHANNEL_INFO(curr,
			   /* 1-3: current channels*/
			   INA3221_HWMON_CURR_CONFIG,
			   INA3221_HWMON_CURR_CONFIG,
			   INA3221_HWMON_CURR_CONFIG,
			   /* 4: summation of current channels */
			   HWMON_C_INPUT | HWMON_C_CRIT | HWMON_C_CRIT_ALARM),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops ina3221_hwmon_ops = अणु
	.is_visible = ina3221_is_visible,
	.पढ़ो_string = ina3221_पढ़ो_string,
	.पढ़ो = ina3221_पढ़ो,
	.ग_लिखो = ina3221_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info ina3221_chip_info = अणु
	.ops = &ina3221_hwmon_ops,
	.info = ina3221_info,
पूर्ण;

/* Extra attribute groups */
अटल sमाप_प्रकार ina3221_shunt_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sd_attr = to_sensor_dev_attr(attr);
	काष्ठा ina3221_data *ina = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक channel = sd_attr->index;
	काष्ठा ina3221_input *input = &ina->inमाला_दो[channel];

	वापस sysfs_emit(buf, "%d\n", input->shunt_resistor);
पूर्ण

अटल sमाप_प्रकार ina3221_shunt_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sd_attr = to_sensor_dev_attr(attr);
	काष्ठा ina3221_data *ina = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक channel = sd_attr->index;
	काष्ठा ina3221_input *input = &ina->inमाला_दो[channel];
	पूर्णांक val;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 0, &val);
	अगर (ret)
		वापस ret;

	val = clamp_val(val, 1, पूर्णांक_उच्च);

	input->shunt_resistor = val;

	/* Update summation_shunt_resistor क्रम summation channel */
	ina->summation_shunt_resistor = ina3221_summation_shunt_resistor(ina);

	वापस count;
पूर्ण

/* shunt resistance */
अटल SENSOR_DEVICE_ATTR_RW(shunt1_resistor, ina3221_shunt, INA3221_CHANNEL1);
अटल SENSOR_DEVICE_ATTR_RW(shunt2_resistor, ina3221_shunt, INA3221_CHANNEL2);
अटल SENSOR_DEVICE_ATTR_RW(shunt3_resistor, ina3221_shunt, INA3221_CHANNEL3);

अटल काष्ठा attribute *ina3221_attrs[] = अणु
	&sensor_dev_attr_shunt1_resistor.dev_attr.attr,
	&sensor_dev_attr_shunt2_resistor.dev_attr.attr,
	&sensor_dev_attr_shunt3_resistor.dev_attr.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ina3221);

अटल स्थिर काष्ठा regmap_range ina3221_yes_ranges[] = अणु
	regmap_reg_range(INA3221_CONFIG, INA3221_BUS3),
	regmap_reg_range(INA3221_SHUNT_SUM, INA3221_SHUNT_SUM),
	regmap_reg_range(INA3221_MASK_ENABLE, INA3221_MASK_ENABLE),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table ina3221_अस्थिर_table = अणु
	.yes_ranges = ina3221_yes_ranges,
	.n_yes_ranges = ARRAY_SIZE(ina3221_yes_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config ina3221_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,

	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_table = &ina3221_अस्थिर_table,
पूर्ण;

अटल पूर्णांक ina3221_probe_child_from_dt(काष्ठा device *dev,
				       काष्ठा device_node *child,
				       काष्ठा ina3221_data *ina)
अणु
	काष्ठा ina3221_input *input;
	u32 val;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(child, "reg", &val);
	अगर (ret) अणु
		dev_err(dev, "missing reg property of %pOFn\n", child);
		वापस ret;
	पूर्ण अन्यथा अगर (val > INA3221_CHANNEL3) अणु
		dev_err(dev, "invalid reg %d of %pOFn\n", val, child);
		वापस ret;
	पूर्ण

	input = &ina->inमाला_दो[val];

	/* Log the disconnected channel input */
	अगर (!of_device_is_available(child)) अणु
		input->disconnected = true;
		वापस 0;
	पूर्ण

	/* Save the connected input label अगर available */
	of_property_पढ़ो_string(child, "label", &input->label);

	/* Overग_लिखो शेष shunt resistor value optionally */
	अगर (!of_property_पढ़ो_u32(child, "shunt-resistor-micro-ohms", &val)) अणु
		अगर (val < 1 || val > पूर्णांक_उच्च) अणु
			dev_err(dev, "invalid shunt resistor value %u of %pOFn\n",
				val, child);
			वापस -EINVAL;
		पूर्ण
		input->shunt_resistor = val;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ina3221_probe_from_dt(काष्ठा device *dev, काष्ठा ina3221_data *ina)
अणु
	स्थिर काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *child;
	पूर्णांक ret;

	/* Compatible with non-DT platक्रमms */
	अगर (!np)
		वापस 0;

	ina->single_shot = of_property_पढ़ो_bool(np, "ti,single-shot");

	क्रम_each_child_of_node(np, child) अणु
		ret = ina3221_probe_child_from_dt(dev, child, ina);
		अगर (ret) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ina3221_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा ina3221_data *ina;
	काष्ठा device *hwmon_dev;
	पूर्णांक i, ret;

	ina = devm_kzalloc(dev, माप(*ina), GFP_KERNEL);
	अगर (!ina)
		वापस -ENOMEM;

	ina->regmap = devm_regmap_init_i2c(client, &ina3221_regmap_config);
	अगर (IS_ERR(ina->regmap)) अणु
		dev_err(dev, "Unable to allocate register map\n");
		वापस PTR_ERR(ina->regmap);
	पूर्ण

	क्रम (i = 0; i < F_MAX_FIELDS; i++) अणु
		ina->fields[i] = devm_regmap_field_alloc(dev,
							 ina->regmap,
							 ina3221_reg_fields[i]);
		अगर (IS_ERR(ina->fields[i])) अणु
			dev_err(dev, "Unable to allocate regmap fields\n");
			वापस PTR_ERR(ina->fields[i]);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < INA3221_NUM_CHANNELS; i++)
		ina->inमाला_दो[i].shunt_resistor = INA3221_RSHUNT_DEFAULT;

	ret = ina3221_probe_from_dt(dev, ina);
	अगर (ret) अणु
		dev_err(dev, "Unable to probe from device tree\n");
		वापस ret;
	पूर्ण

	/* The driver will be reset, so use reset value */
	ina->reg_config = INA3221_CONFIG_DEFAULT;

	/* Clear continuous bit to use single-shot mode */
	अगर (ina->single_shot)
		ina->reg_config &= ~INA3221_CONFIG_MODE_CONTINUOUS;

	/* Disable channels अगर their inमाला_दो are disconnected */
	क्रम (i = 0; i < INA3221_NUM_CHANNELS; i++) अणु
		अगर (ina->inमाला_दो[i].disconnected)
			ina->reg_config &= ~INA3221_CONFIG_CHx_EN(i);
	पूर्ण

	/* Initialize summation_shunt_resistor क्रम summation channel control */
	ina->summation_shunt_resistor = ina3221_summation_shunt_resistor(ina);

	ina->pm_dev = dev;
	mutex_init(&ina->lock);
	dev_set_drvdata(dev, ina);

	/* Enable PM runसमय -- status is suspended by शेष */
	pm_runसमय_enable(ina->pm_dev);

	/* Initialize (resume) the device */
	क्रम (i = 0; i < INA3221_NUM_CHANNELS; i++) अणु
		अगर (ina->inमाला_दो[i].disconnected)
			जारी;
		/* Match the refcount with number of enabled channels */
		ret = pm_runसमय_get_sync(ina->pm_dev);
		अगर (ret < 0)
			जाओ fail;
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, client->name, ina,
							 &ina3221_chip_info,
							 ina3221_groups);
	अगर (IS_ERR(hwmon_dev)) अणु
		dev_err(dev, "Unable to register hwmon device\n");
		ret = PTR_ERR(hwmon_dev);
		जाओ fail;
	पूर्ण

	वापस 0;

fail:
	pm_runसमय_disable(ina->pm_dev);
	pm_runसमय_set_suspended(ina->pm_dev);
	/* pm_runसमय_put_noidle() will decrease the PM refcount until 0 */
	क्रम (i = 0; i < INA3221_NUM_CHANNELS; i++)
		pm_runसमय_put_noidle(ina->pm_dev);
	mutex_destroy(&ina->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ina3221_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ina3221_data *ina = dev_get_drvdata(&client->dev);
	पूर्णांक i;

	pm_runसमय_disable(ina->pm_dev);
	pm_runसमय_set_suspended(ina->pm_dev);

	/* pm_runसमय_put_noidle() will decrease the PM refcount until 0 */
	क्रम (i = 0; i < INA3221_NUM_CHANNELS; i++)
		pm_runसमय_put_noidle(ina->pm_dev);

	mutex_destroy(&ina->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ina3221_suspend(काष्ठा device *dev)
अणु
	काष्ठा ina3221_data *ina = dev_get_drvdata(dev);
	पूर्णांक ret;

	/* Save config रेजिस्टर value and enable cache-only */
	ret = regmap_पढ़ो(ina->regmap, INA3221_CONFIG, &ina->reg_config);
	अगर (ret)
		वापस ret;

	/* Set to घातer-करोwn mode क्रम घातer saving */
	ret = regmap_update_bits(ina->regmap, INA3221_CONFIG,
				 INA3221_CONFIG_MODE_MASK,
				 INA3221_CONFIG_MODE_POWERDOWN);
	अगर (ret)
		वापस ret;

	regcache_cache_only(ina->regmap, true);
	regcache_mark_dirty(ina->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ina3221_resume(काष्ठा device *dev)
अणु
	काष्ठा ina3221_data *ina = dev_get_drvdata(dev);
	पूर्णांक ret;

	regcache_cache_only(ina->regmap, false);

	/* Software reset the chip */
	ret = regmap_field_ग_लिखो(ina->fields[F_RST], true);
	अगर (ret) अणु
		dev_err(dev, "Unable to reset device\n");
		वापस ret;
	पूर्ण

	/* Restore cached रेजिस्टर values to hardware */
	ret = regcache_sync(ina->regmap);
	अगर (ret)
		वापस ret;

	/* Restore config रेजिस्टर value to hardware */
	ret = regmap_ग_लिखो(ina->regmap, INA3221_CONFIG, ina->reg_config);
	अगर (ret)
		वापस ret;

	/* Initialize summation channel control */
	अगर (ina->summation_shunt_resistor) अणु
		/*
		 * Take all three channels पूर्णांकo summation by शेष
		 * Shunt measurements of disconnected channels should
		 * be 0, so it करोes not matter क्रम summation.
		 */
		ret = regmap_update_bits(ina->regmap, INA3221_MASK_ENABLE,
					 INA3221_MASK_ENABLE_SCC_MASK,
					 INA3221_MASK_ENABLE_SCC_MASK);
		अगर (ret) अणु
			dev_err(dev, "Unable to control summation channel\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ina3221_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(ina3221_suspend, ina3221_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id ina3221_of_match_table[] = अणु
	अणु .compatible = "ti,ina3221", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ina3221_of_match_table);

अटल स्थिर काष्ठा i2c_device_id ina3221_ids[] = अणु
	अणु "ina3221", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ina3221_ids);

अटल काष्ठा i2c_driver ina3221_i2c_driver = अणु
	.probe_new = ina3221_probe,
	.हटाओ = ina3221_हटाओ,
	.driver = अणु
		.name = INA3221_DRIVER_NAME,
		.of_match_table = ina3221_of_match_table,
		.pm = &ina3221_pm,
	पूर्ण,
	.id_table = ina3221_ids,
पूर्ण;
module_i2c_driver(ina3221_i2c_driver);

MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_DESCRIPTION("Texas Instruments INA3221 HWMon Driver");
MODULE_LICENSE("GPL v2");
