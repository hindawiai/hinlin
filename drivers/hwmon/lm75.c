<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lm75.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *	 monitoring
 * Copyright (c) 1998, 1999  Froकरो Looijaard <froकरोl@dds.nl>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/util_macros.h>
#समावेश <linux/regulator/consumer.h>
#समावेश "lm75.h"

/*
 * This driver handles the LM75 and compatible digital temperature sensors.
 */

क्रमागत lm75_type अणु		/* keep sorted in alphabetical order */
	adt75,
	ds1775,
	ds75,
	ds7505,
	g751,
	lm75,
	lm75a,
	lm75b,
	max6625,
	max6626,
	max31725,
	mcp980x,
	pct2075,
	stds75,
	stlm75,
	tcn75,
	पंचांगp100,
	पंचांगp101,
	पंचांगp105,
	पंचांगp112,
	पंचांगp175,
	पंचांगp275,
	पंचांगp75,
	पंचांगp75b,
	पंचांगp75c,
पूर्ण;

/**
 * काष्ठा lm75_params - lm75 configuration parameters.
 * @set_mask:		Bits to set in configuration रेजिस्टर when configuring
 *			the chip.
 * @clr_mask:		Bits to clear in configuration रेजिस्टर when configuring
 *			the chip.
 * @शेष_resolution:	Default number of bits to represent the temperature
 *			value.
 * @resolution_limits:	Limit रेजिस्टर resolution. Optional. Should be set अगर
 *			the resolution of limit रेजिस्टरs करोes not match the
 *			resolution of the temperature रेजिस्टर.
 * @resolutions:	List of resolutions associated with sample बार.
 *			Optional. Should be set अगर num_sample_बार is larger
 *			than 1, and अगर the resolution changes with sample बार.
 *			If set, number of entries must match num_sample_बार.
 * @शेष_sample_समय:Sample समय to be set by शेष.
 * @num_sample_बार:	Number of possible sample बार to be set. Optional.
 *			Should be set अगर the number of sample बार is larger
 *			than one.
 * @sample_बार:	All the possible sample बार to be set. Mandatory अगर
 *			num_sample_बार is larger than 1. If set, number of
 *			entries must match num_sample_बार.
 */

काष्ठा lm75_params अणु
	u8			set_mask;
	u8			clr_mask;
	u8			शेष_resolution;
	u8			resolution_limits;
	स्थिर u8		*resolutions;
	अचिन्हित पूर्णांक		शेष_sample_समय;
	u8			num_sample_बार;
	स्थिर अचिन्हित पूर्णांक	*sample_बार;
पूर्ण;

/* Addresses scanned */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x48, 0x49, 0x4a, 0x4b, 0x4c,
					0x4d, 0x4e, 0x4f, I2C_CLIENT_END पूर्ण;

/* The LM75 रेजिस्टरs */
#घोषणा LM75_REG_TEMP		0x00
#घोषणा LM75_REG_CONF		0x01
#घोषणा LM75_REG_HYST		0x02
#घोषणा LM75_REG_MAX		0x03
#घोषणा PCT2075_REG_IDLE	0x04

/* Each client has this additional data */
काष्ठा lm75_data अणु
	काष्ठा i2c_client		*client;
	काष्ठा regmap			*regmap;
	काष्ठा regulator		*vs;
	u8				orig_conf;
	u8				current_conf;
	u8				resolution;	/* In bits, 9 to 16 */
	अचिन्हित पूर्णांक			sample_समय;	/* In ms */
	क्रमागत lm75_type			kind;
	स्थिर काष्ठा lm75_params	*params;
पूर्ण;

/*-----------------------------------------------------------------------*/

अटल स्थिर u8 lm75_sample_set_masks[] = अणु 0 << 5, 1 << 5, 2 << 5, 3 << 5 पूर्ण;

#घोषणा LM75_SAMPLE_CLEAR_MASK	(3 << 5)

/* The काष्ठाure below stores the configuration values of the supported devices.
 * In हाल of being supported multiple configurations, the शेष one must
 * always be the first element of the array
 */
अटल स्थिर काष्ठा lm75_params device_params[] = अणु
	[adt75] = अणु
		.clr_mask = 1 << 5,	/* not one-shot mode */
		.शेष_resolution = 12,
		.शेष_sample_समय = MSEC_PER_SEC / 10,
	पूर्ण,
	[ds1775] = अणु
		.clr_mask = 3 << 5,
		.set_mask = 2 << 5,	/* 11-bit mode */
		.शेष_resolution = 11,
		.शेष_sample_समय = 500,
		.num_sample_बार = 4,
		.sample_बार = (अचिन्हित पूर्णांक [])अणु 125, 250, 500, 1000 पूर्ण,
		.resolutions = (u8 []) अणु9, 10, 11, 12 पूर्ण,
	पूर्ण,
	[ds75] = अणु
		.clr_mask = 3 << 5,
		.set_mask = 2 << 5,	/* 11-bit mode */
		.शेष_resolution = 11,
		.शेष_sample_समय = 600,
		.num_sample_बार = 4,
		.sample_बार = (अचिन्हित पूर्णांक [])अणु 150, 300, 600, 1200 पूर्ण,
		.resolutions = (u8 []) अणु9, 10, 11, 12 पूर्ण,
	पूर्ण,
	[stds75] = अणु
		.clr_mask = 3 << 5,
		.set_mask = 2 << 5,	/* 11-bit mode */
		.शेष_resolution = 11,
		.शेष_sample_समय = 600,
		.num_sample_बार = 4,
		.sample_बार = (अचिन्हित पूर्णांक [])अणु 150, 300, 600, 1200 पूर्ण,
		.resolutions = (u8 []) अणु9, 10, 11, 12 पूर्ण,
	पूर्ण,
	[stlm75] = अणु
		.शेष_resolution = 9,
		.शेष_sample_समय = MSEC_PER_SEC / 6,
	पूर्ण,
	[ds7505] = अणु
		.set_mask = 3 << 5,	/* 12-bit mode*/
		.शेष_resolution = 12,
		.शेष_sample_समय = 200,
		.num_sample_बार = 4,
		.sample_बार = (अचिन्हित पूर्णांक [])अणु 25, 50, 100, 200 पूर्ण,
		.resolutions = (u8 []) अणु9, 10, 11, 12 पूर्ण,
	पूर्ण,
	[g751] = अणु
		.शेष_resolution = 9,
		.शेष_sample_समय = MSEC_PER_SEC / 10,
	पूर्ण,
	[lm75] = अणु
		.शेष_resolution = 9,
		.शेष_sample_समय = MSEC_PER_SEC / 10,
	पूर्ण,
	[lm75a] = अणु
		.शेष_resolution = 9,
		.शेष_sample_समय = MSEC_PER_SEC / 10,
	पूर्ण,
	[lm75b] = अणु
		.शेष_resolution = 11,
		.शेष_sample_समय = MSEC_PER_SEC / 10,
	पूर्ण,
	[max6625] = अणु
		.शेष_resolution = 9,
		.शेष_sample_समय = MSEC_PER_SEC / 7,
	पूर्ण,
	[max6626] = अणु
		.शेष_resolution = 12,
		.शेष_sample_समय = MSEC_PER_SEC / 7,
		.resolution_limits = 9,
	पूर्ण,
	[max31725] = अणु
		.शेष_resolution = 16,
		.शेष_sample_समय = MSEC_PER_SEC / 20,
	पूर्ण,
	[tcn75] = अणु
		.शेष_resolution = 9,
		.शेष_sample_समय = MSEC_PER_SEC / 18,
	पूर्ण,
	[pct2075] = अणु
		.शेष_resolution = 11,
		.शेष_sample_समय = MSEC_PER_SEC / 10,
		.num_sample_बार = 31,
		.sample_बार = (अचिन्हित पूर्णांक [])अणु 100, 200, 300, 400, 500, 600,
		700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700,
		1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700,
		2800, 2900, 3000, 3100 पूर्ण,
	पूर्ण,
	[mcp980x] = अणु
		.set_mask = 3 << 5,	/* 12-bit mode */
		.clr_mask = 1 << 7,	/* not one-shot mode */
		.शेष_resolution = 12,
		.resolution_limits = 9,
		.शेष_sample_समय = 240,
		.num_sample_बार = 4,
		.sample_बार = (अचिन्हित पूर्णांक [])अणु 30, 60, 120, 240 पूर्ण,
		.resolutions = (u8 []) अणु9, 10, 11, 12 पूर्ण,
	पूर्ण,
	[पंचांगp100] = अणु
		.set_mask = 3 << 5,	/* 12-bit mode */
		.clr_mask = 1 << 7,	/* not one-shot mode */
		.शेष_resolution = 12,
		.शेष_sample_समय = 320,
		.num_sample_बार = 4,
		.sample_बार = (अचिन्हित पूर्णांक [])अणु 40, 80, 160, 320 पूर्ण,
		.resolutions = (u8 []) अणु9, 10, 11, 12 पूर्ण,
	पूर्ण,
	[पंचांगp101] = अणु
		.set_mask = 3 << 5,	/* 12-bit mode */
		.clr_mask = 1 << 7,	/* not one-shot mode */
		.शेष_resolution = 12,
		.शेष_sample_समय = 320,
		.num_sample_बार = 4,
		.sample_बार = (अचिन्हित पूर्णांक [])अणु 40, 80, 160, 320 पूर्ण,
		.resolutions = (u8 []) अणु9, 10, 11, 12 पूर्ण,
	पूर्ण,
	[पंचांगp105] = अणु
		.set_mask = 3 << 5,	/* 12-bit mode */
		.clr_mask = 1 << 7,	/* not one-shot mode*/
		.शेष_resolution = 12,
		.शेष_sample_समय = 220,
		.num_sample_बार = 4,
		.sample_बार = (अचिन्हित पूर्णांक [])अणु 28, 55, 110, 220 पूर्ण,
		.resolutions = (u8 []) अणु9, 10, 11, 12 पूर्ण,
	पूर्ण,
	[पंचांगp112] = अणु
		.set_mask = 3 << 5,	/* 8 samples / second */
		.clr_mask = 1 << 7,	/* no one-shot mode*/
		.शेष_resolution = 12,
		.शेष_sample_समय = 125,
		.num_sample_बार = 4,
		.sample_बार = (अचिन्हित पूर्णांक [])अणु 125, 250, 1000, 4000 पूर्ण,
	पूर्ण,
	[पंचांगp175] = अणु
		.set_mask = 3 << 5,	/* 12-bit mode */
		.clr_mask = 1 << 7,	/* not one-shot mode*/
		.शेष_resolution = 12,
		.शेष_sample_समय = 220,
		.num_sample_बार = 4,
		.sample_बार = (अचिन्हित पूर्णांक [])अणु 28, 55, 110, 220 पूर्ण,
		.resolutions = (u8 []) अणु9, 10, 11, 12 पूर्ण,
	पूर्ण,
	[पंचांगp275] = अणु
		.set_mask = 3 << 5,	/* 12-bit mode */
		.clr_mask = 1 << 7,	/* not one-shot mode*/
		.शेष_resolution = 12,
		.शेष_sample_समय = 220,
		.num_sample_बार = 4,
		.sample_बार = (अचिन्हित पूर्णांक [])अणु 28, 55, 110, 220 पूर्ण,
		.resolutions = (u8 []) अणु9, 10, 11, 12 पूर्ण,
	पूर्ण,
	[पंचांगp75] = अणु
		.set_mask = 3 << 5,	/* 12-bit mode */
		.clr_mask = 1 << 7,	/* not one-shot mode*/
		.शेष_resolution = 12,
		.शेष_sample_समय = 220,
		.num_sample_बार = 4,
		.sample_बार = (अचिन्हित पूर्णांक [])अणु 28, 55, 110, 220 पूर्ण,
		.resolutions = (u8 []) अणु9, 10, 11, 12 पूर्ण,
	पूर्ण,
	[पंचांगp75b] = अणु /* not one-shot mode, Conversion rate 37Hz */
		.clr_mask = 1 << 7 | 3 << 5,
		.शेष_resolution = 12,
		.शेष_sample_समय = MSEC_PER_SEC / 37,
		.sample_बार = (अचिन्हित पूर्णांक [])अणु MSEC_PER_SEC / 37,
			MSEC_PER_SEC / 18,
			MSEC_PER_SEC / 9, MSEC_PER_SEC / 4 पूर्ण,
		.num_sample_बार = 4,
	पूर्ण,
	[पंचांगp75c] = अणु
		.clr_mask = 1 << 5,	/*not one-shot mode*/
		.शेष_resolution = 12,
		.शेष_sample_समय = MSEC_PER_SEC / 12,
	पूर्ण
पूर्ण;

अटल अंतरभूत दीर्घ lm75_reg_to_mc(s16 temp, u8 resolution)
अणु
	वापस ((temp >> (16 - resolution)) * 1000) >> (resolution - 8);
पूर्ण

अटल पूर्णांक lm75_ग_लिखो_config(काष्ठा lm75_data *data, u8 set_mask,
			     u8 clr_mask)
अणु
	u8 value;

	clr_mask |= LM75_SHUTDOWN;
	value = data->current_conf & ~clr_mask;
	value |= set_mask;

	अगर (data->current_conf != value) अणु
		s32 err;

		err = i2c_smbus_ग_लिखो_byte_data(data->client, LM75_REG_CONF,
						value);
		अगर (err)
			वापस err;
		data->current_conf = value;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lm75_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		     u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा lm75_data *data = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक regval;
	पूर्णांक err, reg;

	चयन (type) अणु
	हाल hwmon_chip:
		चयन (attr) अणु
		हाल hwmon_chip_update_पूर्णांकerval:
			*val = data->sample_समय;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_input:
			reg = LM75_REG_TEMP;
			अवरोध;
		हाल hwmon_temp_max:
			reg = LM75_REG_MAX;
			अवरोध;
		हाल hwmon_temp_max_hyst:
			reg = LM75_REG_HYST;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		err = regmap_पढ़ो(data->regmap, reg, &regval);
		अगर (err < 0)
			वापस err;

		*val = lm75_reg_to_mc(regval, data->resolution);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lm75_ग_लिखो_temp(काष्ठा device *dev, u32 attr, दीर्घ temp)
अणु
	काष्ठा lm75_data *data = dev_get_drvdata(dev);
	u8 resolution;
	पूर्णांक reg;

	चयन (attr) अणु
	हाल hwmon_temp_max:
		reg = LM75_REG_MAX;
		अवरोध;
	हाल hwmon_temp_max_hyst:
		reg = LM75_REG_HYST;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * Resolution of limit रेजिस्टरs is assumed to be the same as the
	 * temperature input रेजिस्टर resolution unless given explicitly.
	 */
	अगर (data->params->resolution_limits)
		resolution = data->params->resolution_limits;
	अन्यथा
		resolution = data->resolution;

	temp = clamp_val(temp, LM75_TEMP_MIN, LM75_TEMP_MAX);
	temp = DIV_ROUND_CLOSEST(temp  << (resolution - 8),
				 1000) << (16 - resolution);

	वापस regmap_ग_लिखो(data->regmap, reg, (u16)temp);
पूर्ण

अटल पूर्णांक lm75_update_पूर्णांकerval(काष्ठा device *dev, दीर्घ val)
अणु
	काष्ठा lm75_data *data = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक reg;
	u8 index;
	s32 err;

	index = find_बंदst(val, data->params->sample_बार,
			     (पूर्णांक)data->params->num_sample_बार);

	चयन (data->kind) अणु
	शेष:
		err = lm75_ग_लिखो_config(data, lm75_sample_set_masks[index],
					LM75_SAMPLE_CLEAR_MASK);
		अगर (err)
			वापस err;

		data->sample_समय = data->params->sample_बार[index];
		अगर (data->params->resolutions)
			data->resolution = data->params->resolutions[index];
		अवरोध;
	हाल पंचांगp112:
		err = regmap_पढ़ो(data->regmap, LM75_REG_CONF, &reg);
		अगर (err < 0)
			वापस err;
		reg &= ~0x00c0;
		reg |= (3 - index) << 6;
		err = regmap_ग_लिखो(data->regmap, LM75_REG_CONF, reg);
		अगर (err < 0)
			वापस err;
		data->sample_समय = data->params->sample_बार[index];
		अवरोध;
	हाल pct2075:
		err = i2c_smbus_ग_लिखो_byte_data(data->client, PCT2075_REG_IDLE,
						index + 1);
		अगर (err)
			वापस err;
		data->sample_समय = data->params->sample_बार[index];
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lm75_ग_लिखो_chip(काष्ठा device *dev, u32 attr, दीर्घ val)
अणु
	चयन (attr) अणु
	हाल hwmon_chip_update_पूर्णांकerval:
		वापस lm75_update_पूर्णांकerval(dev, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lm75_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		      u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	चयन (type) अणु
	हाल hwmon_chip:
		वापस lm75_ग_लिखो_chip(dev, attr, val);
	हाल hwmon_temp:
		वापस lm75_ग_लिखो_temp(dev, attr, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल umode_t lm75_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type,
			       u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा lm75_data *config_data = data;

	चयन (type) अणु
	हाल hwmon_chip:
		चयन (attr) अणु
		हाल hwmon_chip_update_पूर्णांकerval:
			अगर (config_data->params->num_sample_बार > 1)
				वापस 0644;
			वापस 0444;
		पूर्ण
		अवरोध;
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_input:
			वापस 0444;
		हाल hwmon_temp_max:
		हाल hwmon_temp_max_hyst:
			वापस 0644;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *lm75_info[] = अणु
	HWMON_CHANNEL_INFO(chip,
			   HWMON_C_REGISTER_TZ | HWMON_C_UPDATE_INTERVAL),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops lm75_hwmon_ops = अणु
	.is_visible = lm75_is_visible,
	.पढ़ो = lm75_पढ़ो,
	.ग_लिखो = lm75_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info lm75_chip_info = अणु
	.ops = &lm75_hwmon_ops,
	.info = lm75_info,
पूर्ण;

अटल bool lm75_is_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg != LM75_REG_TEMP;
पूर्ण

अटल bool lm75_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg == LM75_REG_TEMP || reg == LM75_REG_CONF;
पूर्ण

अटल स्थिर काष्ठा regmap_config lm75_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = PCT2075_REG_IDLE,
	.ग_लिखोable_reg = lm75_is_ग_लिखोable_reg,
	.अस्थिर_reg = lm75_is_अस्थिर_reg,
	.val_क्रमmat_endian = REGMAP_ENDIAN_BIG,
	.cache_type = REGCACHE_RBTREE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल व्योम lm75_disable_regulator(व्योम *data)
अणु
	काष्ठा lm75_data *lm75 = data;

	regulator_disable(lm75->vs);
पूर्ण

अटल व्योम lm75_हटाओ(व्योम *data)
अणु
	काष्ठा lm75_data *lm75 = data;
	काष्ठा i2c_client *client = lm75->client;

	i2c_smbus_ग_लिखो_byte_data(client, LM75_REG_CONF, lm75->orig_conf);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm75_ids[];

अटल पूर्णांक lm75_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा lm75_data *data;
	पूर्णांक status, err;
	क्रमागत lm75_type kind;

	अगर (client->dev.of_node)
		kind = (क्रमागत lm75_type)of_device_get_match_data(&client->dev);
	अन्यथा
		kind = i2c_match_id(lm75_ids, client)->driver_data;

	अगर (!i2c_check_functionality(client->adapter,
			I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA))
		वापस -EIO;

	data = devm_kzalloc(dev, माप(काष्ठा lm75_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	data->kind = kind;

	data->vs = devm_regulator_get(dev, "vs");
	अगर (IS_ERR(data->vs))
		वापस PTR_ERR(data->vs);

	data->regmap = devm_regmap_init_i2c(client, &lm75_regmap_config);
	अगर (IS_ERR(data->regmap))
		वापस PTR_ERR(data->regmap);

	/* Set to LM75 resolution (9 bits, 1/2 degree C) and range.
	 * Then tweak to be more precise when appropriate.
	 */

	data->params = &device_params[data->kind];

	/* Save शेष sample समय and resolution*/
	data->sample_समय = data->params->शेष_sample_समय;
	data->resolution = data->params->शेष_resolution;

	/* Enable the घातer */
	err = regulator_enable(data->vs);
	अगर (err) अणु
		dev_err(dev, "failed to enable regulator: %d\n", err);
		वापस err;
	पूर्ण

	err = devm_add_action_or_reset(dev, lm75_disable_regulator, data);
	अगर (err)
		वापस err;

	/* Cache original configuration */
	status = i2c_smbus_पढ़ो_byte_data(client, LM75_REG_CONF);
	अगर (status < 0) अणु
		dev_dbg(dev, "Can't read config? %d\n", status);
		वापस status;
	पूर्ण
	data->orig_conf = status;
	data->current_conf = status;

	err = lm75_ग_लिखो_config(data, data->params->set_mask,
				data->params->clr_mask);
	अगर (err)
		वापस err;

	err = devm_add_action_or_reset(dev, lm75_हटाओ, data);
	अगर (err)
		वापस err;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, client->name,
							 data, &lm75_chip_info,
							 शून्य);
	अगर (IS_ERR(hwmon_dev))
		वापस PTR_ERR(hwmon_dev);

	dev_info(dev, "%s: sensor '%s'\n", dev_name(hwmon_dev), client->name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm75_ids[] = अणु
	अणु "adt75", adt75, पूर्ण,
	अणु "ds1775", ds1775, पूर्ण,
	अणु "ds75", ds75, पूर्ण,
	अणु "ds7505", ds7505, पूर्ण,
	अणु "g751", g751, पूर्ण,
	अणु "lm75", lm75, पूर्ण,
	अणु "lm75a", lm75a, पूर्ण,
	अणु "lm75b", lm75b, पूर्ण,
	अणु "max6625", max6625, पूर्ण,
	अणु "max6626", max6626, पूर्ण,
	अणु "max31725", max31725, पूर्ण,
	अणु "max31726", max31725, पूर्ण,
	अणु "mcp980x", mcp980x, पूर्ण,
	अणु "pct2075", pct2075, पूर्ण,
	अणु "stds75", stds75, पूर्ण,
	अणु "stlm75", stlm75, पूर्ण,
	अणु "tcn75", tcn75, पूर्ण,
	अणु "tmp100", पंचांगp100, पूर्ण,
	अणु "tmp101", पंचांगp101, पूर्ण,
	अणु "tmp105", पंचांगp105, पूर्ण,
	अणु "tmp112", पंचांगp112, पूर्ण,
	अणु "tmp175", पंचांगp175, पूर्ण,
	अणु "tmp275", पंचांगp275, पूर्ण,
	अणु "tmp75", पंचांगp75, पूर्ण,
	अणु "tmp75b", पंचांगp75b, पूर्ण,
	अणु "tmp75c", पंचांगp75c, पूर्ण,
	अणु /* LIST END */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lm75_ids);

अटल स्थिर काष्ठा of_device_id __maybe_unused lm75_of_match[] = अणु
	अणु
		.compatible = "adi,adt75",
		.data = (व्योम *)adt75
	पूर्ण,
	अणु
		.compatible = "dallas,ds1775",
		.data = (व्योम *)ds1775
	पूर्ण,
	अणु
		.compatible = "dallas,ds75",
		.data = (व्योम *)ds75
	पूर्ण,
	अणु
		.compatible = "dallas,ds7505",
		.data = (व्योम *)ds7505
	पूर्ण,
	अणु
		.compatible = "gmt,g751",
		.data = (व्योम *)g751
	पूर्ण,
	अणु
		.compatible = "national,lm75",
		.data = (व्योम *)lm75
	पूर्ण,
	अणु
		.compatible = "national,lm75a",
		.data = (व्योम *)lm75a
	पूर्ण,
	अणु
		.compatible = "national,lm75b",
		.data = (व्योम *)lm75b
	पूर्ण,
	अणु
		.compatible = "maxim,max6625",
		.data = (व्योम *)max6625
	पूर्ण,
	अणु
		.compatible = "maxim,max6626",
		.data = (व्योम *)max6626
	पूर्ण,
	अणु
		.compatible = "maxim,max31725",
		.data = (व्योम *)max31725
	पूर्ण,
	अणु
		.compatible = "maxim,max31726",
		.data = (व्योम *)max31725
	पूर्ण,
	अणु
		.compatible = "maxim,mcp980x",
		.data = (व्योम *)mcp980x
	पूर्ण,
	अणु
		.compatible = "nxp,pct2075",
		.data = (व्योम *)pct2075
	पूर्ण,
	अणु
		.compatible = "st,stds75",
		.data = (व्योम *)stds75
	पूर्ण,
	अणु
		.compatible = "st,stlm75",
		.data = (व्योम *)stlm75
	पूर्ण,
	अणु
		.compatible = "microchip,tcn75",
		.data = (व्योम *)tcn75
	पूर्ण,
	अणु
		.compatible = "ti,tmp100",
		.data = (व्योम *)पंचांगp100
	पूर्ण,
	अणु
		.compatible = "ti,tmp101",
		.data = (व्योम *)पंचांगp101
	पूर्ण,
	अणु
		.compatible = "ti,tmp105",
		.data = (व्योम *)पंचांगp105
	पूर्ण,
	अणु
		.compatible = "ti,tmp112",
		.data = (व्योम *)पंचांगp112
	पूर्ण,
	अणु
		.compatible = "ti,tmp175",
		.data = (व्योम *)पंचांगp175
	पूर्ण,
	अणु
		.compatible = "ti,tmp275",
		.data = (व्योम *)पंचांगp275
	पूर्ण,
	अणु
		.compatible = "ti,tmp75",
		.data = (व्योम *)पंचांगp75
	पूर्ण,
	अणु
		.compatible = "ti,tmp75b",
		.data = (व्योम *)पंचांगp75b
	पूर्ण,
	अणु
		.compatible = "ti,tmp75c",
		.data = (व्योम *)पंचांगp75c
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lm75_of_match);

#घोषणा LM75A_ID 0xA1

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक lm75_detect(काष्ठा i2c_client *new_client,
		       काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = new_client->adapter;
	पूर्णांक i;
	पूर्णांक conf, hyst, os;
	bool is_lm75a = 0;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WORD_DATA))
		वापस -ENODEV;

	/*
	 * Now, we करो the reमुख्यing detection. There is no identअगरication-
	 * dedicated रेजिस्टर so we have to rely on several tricks:
	 * unused bits, रेजिस्टरs cycling over 8-address boundaries,
	 * addresses 0x04-0x07 वापसing the last पढ़ो value.
	 * The cycling+unused addresses combination is not tested,
	 * since it would signअगरicantly slow the detection करोwn and would
	 * hardly add any value.
	 *
	 * The National Semiconductor LM75A is dअगरferent than earlier
	 * LM75s.  It has an ID byte of 0xaX (where X is the chip
	 * revision, with 1 being the only revision in existence) in
	 * रेजिस्टर 7, and unused रेजिस्टरs वापस 0xff rather than the
	 * last पढ़ो value.
	 *
	 * Note that this function only detects the original National
	 * Semiconductor LM75 and the LM75A. Clones from other venकरोrs
	 * aren't detected, on purpose, because they are typically never
	 * found on PC hardware. They are found on embedded designs where
	 * they can be instantiated explicitly so detection is not needed.
	 * The असलence of identअगरication रेजिस्टरs on all these clones
	 * would make their exhaustive detection very dअगरficult and weak,
	 * and odds are that the driver would bind to unsupported devices.
	 */

	/* Unused bits */
	conf = i2c_smbus_पढ़ो_byte_data(new_client, 1);
	अगर (conf & 0xe0)
		वापस -ENODEV;

	/* First check क्रम LM75A */
	अगर (i2c_smbus_पढ़ो_byte_data(new_client, 7) == LM75A_ID) अणु
		/*
		 * LM75A वापसs 0xff on unused रेजिस्टरs so
		 * just to be sure we check क्रम that too.
		 */
		अगर (i2c_smbus_पढ़ो_byte_data(new_client, 4) != 0xff
		 || i2c_smbus_पढ़ो_byte_data(new_client, 5) != 0xff
		 || i2c_smbus_पढ़ो_byte_data(new_client, 6) != 0xff)
			वापस -ENODEV;
		is_lm75a = 1;
		hyst = i2c_smbus_पढ़ो_byte_data(new_client, 2);
		os = i2c_smbus_पढ़ो_byte_data(new_client, 3);
	पूर्ण अन्यथा अणु /* Traditional style LM75 detection */
		/* Unused addresses */
		hyst = i2c_smbus_पढ़ो_byte_data(new_client, 2);
		अगर (i2c_smbus_पढ़ो_byte_data(new_client, 4) != hyst
		 || i2c_smbus_पढ़ो_byte_data(new_client, 5) != hyst
		 || i2c_smbus_पढ़ो_byte_data(new_client, 6) != hyst
		 || i2c_smbus_पढ़ो_byte_data(new_client, 7) != hyst)
			वापस -ENODEV;
		os = i2c_smbus_पढ़ो_byte_data(new_client, 3);
		अगर (i2c_smbus_पढ़ो_byte_data(new_client, 4) != os
		 || i2c_smbus_पढ़ो_byte_data(new_client, 5) != os
		 || i2c_smbus_पढ़ो_byte_data(new_client, 6) != os
		 || i2c_smbus_पढ़ो_byte_data(new_client, 7) != os)
			वापस -ENODEV;
	पूर्ण
	/*
	 * It is very unlikely that this is a LM75 अगर both
	 * hysteresis and temperature limit रेजिस्टरs are 0.
	 */
	अगर (hyst == 0 && os == 0)
		वापस -ENODEV;

	/* Addresses cycling */
	क्रम (i = 8; i <= 248; i += 40) अणु
		अगर (i2c_smbus_पढ़ो_byte_data(new_client, i + 1) != conf
		 || i2c_smbus_पढ़ो_byte_data(new_client, i + 2) != hyst
		 || i2c_smbus_पढ़ो_byte_data(new_client, i + 3) != os)
			वापस -ENODEV;
		अगर (is_lm75a && i2c_smbus_पढ़ो_byte_data(new_client, i + 7)
				!= LM75A_ID)
			वापस -ENODEV;
	पूर्ण

	strlcpy(info->type, is_lm75a ? "lm75a" : "lm75", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक lm75_suspend(काष्ठा device *dev)
अणु
	पूर्णांक status;
	काष्ठा i2c_client *client = to_i2c_client(dev);

	status = i2c_smbus_पढ़ो_byte_data(client, LM75_REG_CONF);
	अगर (status < 0) अणु
		dev_dbg(&client->dev, "Can't read config? %d\n", status);
		वापस status;
	पूर्ण
	status = status | LM75_SHUTDOWN;
	i2c_smbus_ग_लिखो_byte_data(client, LM75_REG_CONF, status);
	वापस 0;
पूर्ण

अटल पूर्णांक lm75_resume(काष्ठा device *dev)
अणु
	पूर्णांक status;
	काष्ठा i2c_client *client = to_i2c_client(dev);

	status = i2c_smbus_पढ़ो_byte_data(client, LM75_REG_CONF);
	अगर (status < 0) अणु
		dev_dbg(&client->dev, "Can't read config? %d\n", status);
		वापस status;
	पूर्ण
	status = status & ~LM75_SHUTDOWN;
	i2c_smbus_ग_लिखो_byte_data(client, LM75_REG_CONF, status);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops lm75_dev_pm_ops = अणु
	.suspend	= lm75_suspend,
	.resume		= lm75_resume,
पूर्ण;
#घोषणा LM75_DEV_PM_OPS (&lm75_dev_pm_ops)
#अन्यथा
#घोषणा LM75_DEV_PM_OPS शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा i2c_driver lm75_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "lm75",
		.of_match_table = of_match_ptr(lm75_of_match),
		.pm	= LM75_DEV_PM_OPS,
	पूर्ण,
	.probe_new	= lm75_probe,
	.id_table	= lm75_ids,
	.detect		= lm75_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(lm75_driver);

MODULE_AUTHOR("Frodo Looijaard <frodol@dds.nl>");
MODULE_DESCRIPTION("LM75 driver");
MODULE_LICENSE("GPL");
