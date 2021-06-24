<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम Maxim MAX6621
 *
 * Copyright (c) 2017 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2017 Vadim Pasternak <vadimp@mellanox.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>

#घोषणा MAX6621_DRV_NAME		"max6621"
#घोषणा MAX6621_TEMP_INPUT_REG_NUM	9
#घोषणा MAX6621_TEMP_INPUT_MIN		-127000
#घोषणा MAX6621_TEMP_INPUT_MAX		128000
#घोषणा MAX6621_TEMP_ALERT_CHAN_SHIFT	1

#घोषणा MAX6621_TEMP_S0D0_REG		0x00
#घोषणा MAX6621_TEMP_S0D1_REG		0x01
#घोषणा MAX6621_TEMP_S1D0_REG		0x02
#घोषणा MAX6621_TEMP_S1D1_REG		0x03
#घोषणा MAX6621_TEMP_S2D0_REG		0x04
#घोषणा MAX6621_TEMP_S2D1_REG		0x05
#घोषणा MAX6621_TEMP_S3D0_REG		0x06
#घोषणा MAX6621_TEMP_S3D1_REG		0x07
#घोषणा MAX6621_TEMP_MAX_REG		0x08
#घोषणा MAX6621_TEMP_MAX_ADDR_REG	0x0a
#घोषणा MAX6621_TEMP_ALERT_CAUSE_REG	0x0b
#घोषणा MAX6621_CONFIG0_REG		0x0c
#घोषणा MAX6621_CONFIG1_REG		0x0d
#घोषणा MAX6621_CONFIG2_REG		0x0e
#घोषणा MAX6621_CONFIG3_REG		0x0f
#घोषणा MAX6621_TEMP_S0_ALERT_REG	0x10
#घोषणा MAX6621_TEMP_S1_ALERT_REG	0x11
#घोषणा MAX6621_TEMP_S2_ALERT_REG	0x12
#घोषणा MAX6621_TEMP_S3_ALERT_REG	0x13
#घोषणा MAX6621_CLEAR_ALERT_REG		0x15
#घोषणा MAX6621_REG_MAX			(MAX6621_CLEAR_ALERT_REG + 1)
#घोषणा MAX6621_REG_TEMP_SHIFT		0x06

#घोषणा MAX6621_ENABLE_TEMP_ALERTS_BIT	4
#घोषणा MAX6621_ENABLE_I2C_CRC_BIT	5
#घोषणा MAX6621_ENABLE_ALTERNATE_DATA	6
#घोषणा MAX6621_ENABLE_LOCKUP_TO	7
#घोषणा MAX6621_ENABLE_S0D0_BIT		8
#घोषणा MAX6621_ENABLE_S3D1_BIT		15
#घोषणा MAX6621_ENABLE_TEMP_ALL		GENMASK(MAX6621_ENABLE_S3D1_BIT, \
						MAX6621_ENABLE_S0D0_BIT)
#घोषणा MAX6621_POLL_DELAY_MASK		0x5
#घोषणा MAX6621_CONFIG0_INIT		(MAX6621_ENABLE_TEMP_ALL | \
					 BIT(MAX6621_ENABLE_LOCKUP_TO) | \
					 BIT(MAX6621_ENABLE_I2C_CRC_BIT) | \
					 MAX6621_POLL_DELAY_MASK)
#घोषणा MAX6621_PECI_BIT_TIME		0x2
#घोषणा MAX6621_PECI_RETRY_NUM		0x3
#घोषणा MAX6621_CONFIG1_INIT		((MAX6621_PECI_BIT_TIME << 8) | \
					 MAX6621_PECI_RETRY_NUM)

/* Error codes */
#घोषणा MAX6621_TRAN_FAILED	0x8100	/*
					 * PECI transaction failed क्रम more
					 * than the configured number of
					 * consecutive retries.
					 */
#घोषणा MAX6621_POOL_DIS	0x8101	/*
					 * Polling disabled क्रम requested
					 * socket/करोमुख्य.
					 */
#घोषणा MAX6621_POOL_UNCOMPLETE	0x8102	/*
					 * First poll not yet completed क्रम
					 * requested socket/करोमुख्य (on
					 * startup).
					 */
#घोषणा MAX6621_SD_DIS		0x8103	/*
					 * Read maximum temperature requested,
					 * but no sockets/करोमुख्यs enabled or
					 * all enabled sockets/करोमुख्यs have
					 * errors; or पढ़ो maximum temperature
					 * address requested, but पढ़ो maximum
					 * temperature was not called.
					 */
#घोषणा MAX6621_ALERT_DIS	0x8104	/*
					 * Get alert socket/करोमुख्य requested,
					 * but no alert active.
					 */
#घोषणा MAX6621_PECI_ERR_MIN	0x8000	/* Intel spec PECI error min value. */
#घोषणा MAX6621_PECI_ERR_MAX	0x80ff	/* Intel spec PECI error max value. */

अटल स्थिर u32 max6621_temp_regs[] = अणु
	MAX6621_TEMP_MAX_REG, MAX6621_TEMP_S0D0_REG, MAX6621_TEMP_S1D0_REG,
	MAX6621_TEMP_S2D0_REG, MAX6621_TEMP_S3D0_REG, MAX6621_TEMP_S0D1_REG,
	MAX6621_TEMP_S1D1_REG, MAX6621_TEMP_S2D1_REG, MAX6621_TEMP_S3D1_REG,
पूर्ण;

अटल स्थिर अक्षर *स्थिर max6621_temp_labels[] = अणु
	"maximum",
	"socket0_0",
	"socket1_0",
	"socket2_0",
	"socket3_0",
	"socket0_1",
	"socket1_1",
	"socket2_1",
	"socket3_1",
पूर्ण;

अटल स्थिर पूर्णांक max6621_temp_alert_chan2reg[] = अणु
	MAX6621_TEMP_S0_ALERT_REG,
	MAX6621_TEMP_S1_ALERT_REG,
	MAX6621_TEMP_S2_ALERT_REG,
	MAX6621_TEMP_S3_ALERT_REG,
पूर्ण;

/**
 * काष्ठा max6621_data - निजी data:
 *
 * @client: I2C client;
 * @regmap: रेजिस्टर map handle;
 * @input_chan2reg: mapping from channel to रेजिस्टर;
 */
काष्ठा max6621_data अणु
	काष्ठा i2c_client	*client;
	काष्ठा regmap		*regmap;
	पूर्णांक			input_chan2reg[MAX6621_TEMP_INPUT_REG_NUM + 1];
पूर्ण;

अटल दीर्घ max6621_temp_mc2reg(दीर्घ val)
अणु
	वापस (val / 1000L) << MAX6621_REG_TEMP_SHIFT;
पूर्ण

अटल umode_t
max6621_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type, u32 attr,
		   पूर्णांक channel)
अणु
	/* Skip channels which are not physically conncted. */
	अगर (((काष्ठा max6621_data *)data)->input_chan2reg[channel] < 0)
		वापस 0;

	चयन (type) अणु
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_input:
		हाल hwmon_temp_label:
		हाल hwmon_temp_crit_alarm:
			वापस 0444;
		हाल hwmon_temp_offset:
		हाल hwmon_temp_crit:
			वापस 0644;
		शेष:
			अवरोध;
		पूर्ण

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max6621_verअगरy_reg_data(काष्ठा device *dev, पूर्णांक regval)
अणु
	अगर (regval >= MAX6621_PECI_ERR_MIN &&
	    regval <= MAX6621_PECI_ERR_MAX) अणु
		dev_dbg(dev, "PECI error code - err 0x%04x.\n",
			regval);

		वापस -EIO;
	पूर्ण

	चयन (regval) अणु
	हाल MAX6621_TRAN_FAILED:
		dev_dbg(dev, "PECI transaction failed - err 0x%04x.\n",
			regval);
		वापस -EIO;
	हाल MAX6621_POOL_DIS:
		dev_dbg(dev, "Polling disabled - err 0x%04x.\n", regval);
		वापस -EOPNOTSUPP;
	हाल MAX6621_POOL_UNCOMPLETE:
		dev_dbg(dev, "First poll not completed on startup - err 0x%04x.\n",
			regval);
		वापस -EIO;
	हाल MAX6621_SD_DIS:
		dev_dbg(dev, "Resource is disabled - err 0x%04x.\n", regval);
		वापस -EOPNOTSUPP;
	हाल MAX6621_ALERT_DIS:
		dev_dbg(dev, "No alert active - err 0x%04x.\n", regval);
		वापस -EOPNOTSUPP;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक
max6621_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type, u32 attr,
	     पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा max6621_data *data = dev_get_drvdata(dev);
	u32 regval;
	पूर्णांक reg;
	s8 temp;
	पूर्णांक ret;

	चयन (type) अणु
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_input:
			reg = data->input_chan2reg[channel];
			ret = regmap_पढ़ो(data->regmap, reg, &regval);
			अगर (ret)
				वापस ret;

			ret = max6621_verअगरy_reg_data(dev, regval);
			अगर (ret)
				वापस ret;

			/*
			 * Bit MAX6621_REG_TEMP_SHIFT represents 1 degree step.
			 * The temperature is given in two's complement and 8
			 * bits is used क्रम the रेजिस्टर conversion.
			 */
			temp = (regval >> MAX6621_REG_TEMP_SHIFT);
			*val = temp * 1000L;

			अवरोध;
		हाल hwmon_temp_offset:
			ret = regmap_पढ़ो(data->regmap, MAX6621_CONFIG2_REG,
					  &regval);
			अगर (ret)
				वापस ret;

			ret = max6621_verअगरy_reg_data(dev, regval);
			अगर (ret)
				वापस ret;

			*val = (regval >> MAX6621_REG_TEMP_SHIFT) *
			       1000L;

			अवरोध;
		हाल hwmon_temp_crit:
			channel -= MAX6621_TEMP_ALERT_CHAN_SHIFT;
			reg = max6621_temp_alert_chan2reg[channel];
			ret = regmap_पढ़ो(data->regmap, reg, &regval);
			अगर (ret)
				वापस ret;

			ret = max6621_verअगरy_reg_data(dev, regval);
			अगर (ret)
				वापस ret;

			*val = regval * 1000L;

			अवरोध;
		हाल hwmon_temp_crit_alarm:
			/*
			 * Set val to zero to recover the हाल, when पढ़ोing
			 * MAX6621_TEMP_ALERT_CAUSE_REG results in क्रम example
			 * MAX6621_ALERT_DIS. Reading will वापस with error,
			 * but in such हाल alarm should be वापसed as 0.
			 */
			*val = 0;
			ret = regmap_पढ़ो(data->regmap,
					  MAX6621_TEMP_ALERT_CAUSE_REG,
					  &regval);
			अगर (ret)
				वापस ret;

			ret = max6621_verअगरy_reg_data(dev, regval);
			अगर (ret) अणु
				/* Do not report error अगर alert is disabled. */
				अगर (regval == MAX6621_ALERT_DIS)
					वापस 0;
				अन्यथा
					वापस ret;
			पूर्ण

			/*
			 * Clear the alert स्वतःmatically, using send-byte
			 * smbus protocol क्रम clearing alert.
			 */
			अगर (regval) अणु
				ret = i2c_smbus_ग_लिखो_byte(data->client,
						MAX6621_CLEAR_ALERT_REG);
				अगर (ret)
					वापस ret;
			पूर्ण

			*val = !!regval;

			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
max6621_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type, u32 attr,
	      पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा max6621_data *data = dev_get_drvdata(dev);
	u32 reg;

	चयन (type) अणु
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_offset:
			/* Clamp to allowed range to prevent overflow. */
			val = clamp_val(val, MAX6621_TEMP_INPUT_MIN,
					MAX6621_TEMP_INPUT_MAX);
			val = max6621_temp_mc2reg(val);

			वापस regmap_ग_लिखो(data->regmap,
					    MAX6621_CONFIG2_REG, val);
		हाल hwmon_temp_crit:
			channel -= MAX6621_TEMP_ALERT_CHAN_SHIFT;
			reg = max6621_temp_alert_chan2reg[channel];
			/* Clamp to allowed range to prevent overflow. */
			val = clamp_val(val, MAX6621_TEMP_INPUT_MIN,
					MAX6621_TEMP_INPUT_MAX);
			val = val / 1000L;

			वापस regmap_ग_लिखो(data->regmap, reg, val);
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
max6621_पढ़ो_string(काष्ठा device *dev, क्रमागत hwmon_sensor_types type, u32 attr,
		    पूर्णांक channel, स्थिर अक्षर **str)
अणु
	चयन (type) अणु
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_label:
			*str = max6621_temp_labels[channel];
			वापस 0;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल bool max6621_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX6621_CONFIG0_REG:
	हाल MAX6621_CONFIG1_REG:
	हाल MAX6621_CONFIG2_REG:
	हाल MAX6621_CONFIG3_REG:
	हाल MAX6621_TEMP_S0_ALERT_REG:
	हाल MAX6621_TEMP_S1_ALERT_REG:
	हाल MAX6621_TEMP_S2_ALERT_REG:
	हाल MAX6621_TEMP_S3_ALERT_REG:
	हाल MAX6621_TEMP_ALERT_CAUSE_REG:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool max6621_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX6621_TEMP_S0D0_REG:
	हाल MAX6621_TEMP_S0D1_REG:
	हाल MAX6621_TEMP_S1D0_REG:
	हाल MAX6621_TEMP_S1D1_REG:
	हाल MAX6621_TEMP_S2D0_REG:
	हाल MAX6621_TEMP_S2D1_REG:
	हाल MAX6621_TEMP_S3D0_REG:
	हाल MAX6621_TEMP_S3D1_REG:
	हाल MAX6621_TEMP_MAX_REG:
	हाल MAX6621_TEMP_MAX_ADDR_REG:
	हाल MAX6621_CONFIG0_REG:
	हाल MAX6621_CONFIG1_REG:
	हाल MAX6621_CONFIG2_REG:
	हाल MAX6621_CONFIG3_REG:
	हाल MAX6621_TEMP_S0_ALERT_REG:
	हाल MAX6621_TEMP_S1_ALERT_REG:
	हाल MAX6621_TEMP_S2_ALERT_REG:
	हाल MAX6621_TEMP_S3_ALERT_REG:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool max6621_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX6621_TEMP_S0D0_REG:
	हाल MAX6621_TEMP_S0D1_REG:
	हाल MAX6621_TEMP_S1D0_REG:
	हाल MAX6621_TEMP_S1D1_REG:
	हाल MAX6621_TEMP_S2D0_REG:
	हाल MAX6621_TEMP_S2D1_REG:
	हाल MAX6621_TEMP_S3D0_REG:
	हाल MAX6621_TEMP_S3D1_REG:
	हाल MAX6621_TEMP_MAX_REG:
	हाल MAX6621_TEMP_S0_ALERT_REG:
	हाल MAX6621_TEMP_S1_ALERT_REG:
	हाल MAX6621_TEMP_S2_ALERT_REG:
	हाल MAX6621_TEMP_S3_ALERT_REG:
	हाल MAX6621_TEMP_ALERT_CAUSE_REG:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर काष्ठा reg_शेष max6621_regmap_शेष[] = अणु
	अणु MAX6621_CONFIG0_REG, MAX6621_CONFIG0_INIT पूर्ण,
	अणु MAX6621_CONFIG1_REG, MAX6621_CONFIG1_INIT पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config max6621_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = MAX6621_REG_MAX,
	.val_क्रमmat_endian = REGMAP_ENDIAN_LITTLE,
	.cache_type = REGCACHE_FLAT,
	.ग_लिखोable_reg = max6621_ग_लिखोable_reg,
	.पढ़ोable_reg = max6621_पढ़ोable_reg,
	.अस्थिर_reg = max6621_अस्थिर_reg,
	.reg_शेषs = max6621_regmap_शेष,
	.num_reg_शेषs = ARRAY_SIZE(max6621_regmap_शेष),
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *max6621_info[] = अणु
	HWMON_CHANNEL_INFO(chip,
			   HWMON_C_REGISTER_TZ),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_LABEL | HWMON_T_OFFSET,
			   HWMON_T_INPUT | HWMON_T_CRIT | HWMON_T_CRIT_ALARM | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_CRIT | HWMON_T_CRIT_ALARM | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_CRIT | HWMON_T_CRIT_ALARM | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_CRIT | HWMON_T_CRIT_ALARM | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL,
			   HWMON_T_INPUT | HWMON_T_LABEL),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops max6621_hwmon_ops = अणु
	.पढ़ो = max6621_पढ़ो,
	.ग_लिखो = max6621_ग_लिखो,
	.पढ़ो_string = max6621_पढ़ो_string,
	.is_visible = max6621_is_visible,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info max6621_chip_info = अणु
	.ops = &max6621_hwmon_ops,
	.info = max6621_info,
पूर्ण;

अटल पूर्णांक max6621_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा max6621_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक i;
	पूर्णांक ret;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->regmap = devm_regmap_init_i2c(client, &max6621_regmap_config);
	अगर (IS_ERR(data->regmap))
		वापस PTR_ERR(data->regmap);

	i2c_set_clientdata(client, data);
	data->client = client;

	/* Set CONFIG0 रेजिस्टर masking temperature alerts and PEC. */
	ret = regmap_ग_लिखो(data->regmap, MAX6621_CONFIG0_REG,
			   MAX6621_CONFIG0_INIT);
	अगर (ret)
		वापस ret;

	/* Set CONFIG1 रेजिस्टर क्रम PEC access retry number. */
	ret = regmap_ग_लिखो(data->regmap, MAX6621_CONFIG1_REG,
			   MAX6621_CONFIG1_INIT);
	अगर (ret)
		वापस ret;

	/* Sync रेजिस्टरs with hardware. */
	regcache_mark_dirty(data->regmap);
	ret = regcache_sync(data->regmap);
	अगर (ret)
		वापस ret;

	/* Verअगरy which temperature input रेजिस्टरs are enabled. */
	क्रम (i = 0; i < MAX6621_TEMP_INPUT_REG_NUM; i++) अणु
		ret = i2c_smbus_पढ़ो_word_data(client, max6621_temp_regs[i]);
		अगर (ret < 0)
			वापस ret;
		ret = max6621_verअगरy_reg_data(dev, ret);
		अगर (ret) अणु
			data->input_chan2reg[i] = -1;
			जारी;
		पूर्ण

		data->input_chan2reg[i] = max6621_temp_regs[i];
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, client->name,
							 data,
							 &max6621_chip_info,
							 शून्य);

	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max6621_id[] = अणु
	अणु MAX6621_DRV_NAME, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max6621_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused max6621_of_match[] = अणु
	अणु .compatible = "maxim,max6621" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max6621_of_match);

अटल काष्ठा i2c_driver max6621_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name = MAX6621_DRV_NAME,
		.of_match_table = of_match_ptr(max6621_of_match),
	पूर्ण,
	.probe_new	= max6621_probe,
	.id_table	= max6621_id,
पूर्ण;

module_i2c_driver(max6621_driver);

MODULE_AUTHOR("Vadim Pasternak <vadimp@mellanox.com>");
MODULE_DESCRIPTION("Driver for Maxim MAX6621");
MODULE_LICENSE("GPL");
