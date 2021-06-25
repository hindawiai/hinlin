<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Texas Instruments TMP108 SMBus temperature sensor driver
 *
 * Copyright (C) 2016 John Muir <john@jmuir.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा	DRIVER_NAME "tmp108"

#घोषणा	TMP108_REG_TEMP		0x00
#घोषणा	TMP108_REG_CONF		0x01
#घोषणा	TMP108_REG_TLOW		0x02
#घोषणा	TMP108_REG_THIGH	0x03

#घोषणा TMP108_TEMP_MIN_MC	-50000 /* Minimum millicelcius. */
#घोषणा TMP108_TEMP_MAX_MC	127937 /* Maximum millicelcius. */

/* Configuration रेजिस्टर bits.
 * Note: these bit definitions are byte swapped.
 */
#घोषणा TMP108_CONF_M0		0x0100 /* Sensor mode. */
#घोषणा TMP108_CONF_M1		0x0200
#घोषणा TMP108_CONF_TM		0x0400 /* Thermostat mode. */
#घोषणा TMP108_CONF_FL		0x0800 /* Watchकरोg flag - TLOW */
#घोषणा TMP108_CONF_FH		0x1000 /* Watchकरोg flag - THIGH */
#घोषणा TMP108_CONF_CR0		0x2000 /* Conversion rate. */
#घोषणा TMP108_CONF_CR1		0x4000
#घोषणा TMP108_CONF_ID		0x8000
#घोषणा TMP108_CONF_HYS0	0x0010 /* Hysteresis. */
#घोषणा TMP108_CONF_HYS1	0x0020
#घोषणा TMP108_CONF_POL		0x0080 /* Polarity of alert. */

/* Defaults set by the hardware upon reset. */
#घोषणा TMP108_CONF_DEFAULTS		(TMP108_CONF_CR0 | TMP108_CONF_TM |\
					 TMP108_CONF_HYS0 | TMP108_CONF_M1)
/* These bits are पढ़ो-only. */
#घोषणा TMP108_CONF_READ_ONLY		(TMP108_CONF_FL | TMP108_CONF_FH |\
					 TMP108_CONF_ID)

#घोषणा TMP108_CONF_MODE_MASK		(TMP108_CONF_M0|TMP108_CONF_M1)
#घोषणा TMP108_MODE_SHUTDOWN		0x0000
#घोषणा TMP108_MODE_ONE_SHOT		TMP108_CONF_M0
#घोषणा TMP108_MODE_CONTINUOUS		TMP108_CONF_M1		/* Default */
					/* When M1 is set, M0 is ignored. */

#घोषणा TMP108_CONF_CONVRATE_MASK	(TMP108_CONF_CR0|TMP108_CONF_CR1)
#घोषणा TMP108_CONVRATE_0P25HZ		0x0000
#घोषणा TMP108_CONVRATE_1HZ		TMP108_CONF_CR0		/* Default */
#घोषणा TMP108_CONVRATE_4HZ		TMP108_CONF_CR1
#घोषणा TMP108_CONVRATE_16HZ		(TMP108_CONF_CR0|TMP108_CONF_CR1)

#घोषणा TMP108_CONF_HYSTERESIS_MASK	(TMP108_CONF_HYS0|TMP108_CONF_HYS1)
#घोषणा TMP108_HYSTERESIS_0C		0x0000
#घोषणा TMP108_HYSTERESIS_1C		TMP108_CONF_HYS0	/* Default */
#घोषणा TMP108_HYSTERESIS_2C		TMP108_CONF_HYS1
#घोषणा TMP108_HYSTERESIS_4C		(TMP108_CONF_HYS0|TMP108_CONF_HYS1)

#घोषणा TMP108_CONVERSION_TIME_MS	30	/* in milli-seconds */

काष्ठा पंचांगp108 अणु
	काष्ठा regmap *regmap;
	u16 orig_config;
	अचिन्हित दीर्घ पढ़ोy_समय;
पूर्ण;

/* convert 12-bit TMP108 रेजिस्टर value to milliCelsius */
अटल अंतरभूत पूर्णांक पंचांगp108_temp_reg_to_mC(s16 val)
अणु
	वापस (val & ~0x0f) * 1000 / 256;
पूर्ण

/* convert milliCelsius to left adjusted 12-bit TMP108 रेजिस्टर value */
अटल अंतरभूत u16 पंचांगp108_mC_to_temp_reg(पूर्णांक val)
अणु
	वापस (val * 256) / 1000;
पूर्ण

अटल पूर्णांक पंचांगp108_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		       u32 attr, पूर्णांक channel, दीर्घ *temp)
अणु
	काष्ठा पंचांगp108 *पंचांगp108 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक regval;
	पूर्णांक err, hyst;

	अगर (type == hwmon_chip) अणु
		अगर (attr == hwmon_chip_update_पूर्णांकerval) अणु
			err = regmap_पढ़ो(पंचांगp108->regmap, TMP108_REG_CONF,
					  &regval);
			अगर (err < 0)
				वापस err;
			चयन (regval & TMP108_CONF_CONVRATE_MASK) अणु
			हाल TMP108_CONVRATE_0P25HZ:
			शेष:
				*temp = 4000;
				अवरोध;
			हाल TMP108_CONVRATE_1HZ:
				*temp = 1000;
				अवरोध;
			हाल TMP108_CONVRATE_4HZ:
				*temp = 250;
				अवरोध;
			हाल TMP108_CONVRATE_16HZ:
				*temp = 63;
				अवरोध;
			पूर्ण
			वापस 0;
		पूर्ण
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (attr) अणु
	हाल hwmon_temp_input:
		/* Is it too early to वापस a conversion ? */
		अगर (समय_beक्रमe(jअगरfies, पंचांगp108->पढ़ोy_समय)) अणु
			dev_dbg(dev, "%s: Conversion not ready yet..\n",
				__func__);
			वापस -EAGAIN;
		पूर्ण
		err = regmap_पढ़ो(पंचांगp108->regmap, TMP108_REG_TEMP, &regval);
		अगर (err < 0)
			वापस err;
		*temp = पंचांगp108_temp_reg_to_mC(regval);
		अवरोध;
	हाल hwmon_temp_min:
	हाल hwmon_temp_max:
		err = regmap_पढ़ो(पंचांगp108->regmap, attr == hwmon_temp_min ?
				  TMP108_REG_TLOW : TMP108_REG_THIGH, &regval);
		अगर (err < 0)
			वापस err;
		*temp = पंचांगp108_temp_reg_to_mC(regval);
		अवरोध;
	हाल hwmon_temp_min_alarm:
	हाल hwmon_temp_max_alarm:
		err = regmap_पढ़ो(पंचांगp108->regmap, TMP108_REG_CONF, &regval);
		अगर (err < 0)
			वापस err;
		*temp = !!(regval & (attr == hwmon_temp_min_alarm ?
				     TMP108_CONF_FL : TMP108_CONF_FH));
		अवरोध;
	हाल hwmon_temp_min_hyst:
	हाल hwmon_temp_max_hyst:
		err = regmap_पढ़ो(पंचांगp108->regmap, TMP108_REG_CONF, &regval);
		अगर (err < 0)
			वापस err;
		चयन (regval & TMP108_CONF_HYSTERESIS_MASK) अणु
		हाल TMP108_HYSTERESIS_0C:
		शेष:
			hyst = 0;
			अवरोध;
		हाल TMP108_HYSTERESIS_1C:
			hyst = 1000;
			अवरोध;
		हाल TMP108_HYSTERESIS_2C:
			hyst = 2000;
			अवरोध;
		हाल TMP108_HYSTERESIS_4C:
			hyst = 4000;
			अवरोध;
		पूर्ण
		err = regmap_पढ़ो(पंचांगp108->regmap, attr == hwmon_temp_min_hyst ?
				  TMP108_REG_TLOW : TMP108_REG_THIGH, &regval);
		अगर (err < 0)
			वापस err;
		*temp = पंचांगp108_temp_reg_to_mC(regval);
		अगर (attr == hwmon_temp_min_hyst)
			*temp += hyst;
		अन्यथा
			*temp -= hyst;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांगp108_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ temp)
अणु
	काष्ठा पंचांगp108 *पंचांगp108 = dev_get_drvdata(dev);
	u32 regval, mask;
	पूर्णांक err;

	अगर (type == hwmon_chip) अणु
		अगर (attr == hwmon_chip_update_पूर्णांकerval) अणु
			अगर (temp < 156)
				mask = TMP108_CONVRATE_16HZ;
			अन्यथा अगर (temp < 625)
				mask = TMP108_CONVRATE_4HZ;
			अन्यथा अगर (temp < 2500)
				mask = TMP108_CONVRATE_1HZ;
			अन्यथा
				mask = TMP108_CONVRATE_0P25HZ;
			वापस regmap_update_bits(पंचांगp108->regmap,
						  TMP108_REG_CONF,
						  TMP108_CONF_CONVRATE_MASK,
						  mask);
		पूर्ण
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (attr) अणु
	हाल hwmon_temp_min:
	हाल hwmon_temp_max:
		temp = clamp_val(temp, TMP108_TEMP_MIN_MC, TMP108_TEMP_MAX_MC);
		वापस regmap_ग_लिखो(पंचांगp108->regmap,
				    attr == hwmon_temp_min ?
					TMP108_REG_TLOW : TMP108_REG_THIGH,
				    पंचांगp108_mC_to_temp_reg(temp));
	हाल hwmon_temp_min_hyst:
	हाल hwmon_temp_max_hyst:
		temp = clamp_val(temp, TMP108_TEMP_MIN_MC, TMP108_TEMP_MAX_MC);
		err = regmap_पढ़ो(पंचांगp108->regmap,
				  attr == hwmon_temp_min_hyst ?
					TMP108_REG_TLOW : TMP108_REG_THIGH,
				  &regval);
		अगर (err < 0)
			वापस err;
		अगर (attr == hwmon_temp_min_hyst)
			temp -= पंचांगp108_temp_reg_to_mC(regval);
		अन्यथा
			temp = पंचांगp108_temp_reg_to_mC(regval) - temp;
		अगर (temp < 500)
			mask = TMP108_HYSTERESIS_0C;
		अन्यथा अगर (temp < 1500)
			mask = TMP108_HYSTERESIS_1C;
		अन्यथा अगर (temp < 3000)
			mask = TMP108_HYSTERESIS_2C;
		अन्यथा
			mask = TMP108_HYSTERESIS_4C;
		वापस regmap_update_bits(पंचांगp108->regmap, TMP108_REG_CONF,
					  TMP108_CONF_HYSTERESIS_MASK, mask);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल umode_t पंचांगp108_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type,
				 u32 attr, पूर्णांक channel)
अणु
	अगर (type == hwmon_chip && attr == hwmon_chip_update_पूर्णांकerval)
		वापस 0644;

	अगर (type != hwmon_temp)
		वापस 0;

	चयन (attr) अणु
	हाल hwmon_temp_input:
	हाल hwmon_temp_min_alarm:
	हाल hwmon_temp_max_alarm:
		वापस 0444;
	हाल hwmon_temp_min:
	हाल hwmon_temp_max:
	हाल hwmon_temp_min_hyst:
	हाल hwmon_temp_max_hyst:
		वापस 0644;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *पंचांगp108_info[] = अणु
	HWMON_CHANNEL_INFO(chip,
			   HWMON_C_REGISTER_TZ | HWMON_C_UPDATE_INTERVAL),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN |
			   HWMON_T_MIN_HYST | HWMON_T_MAX_HYST |
			   HWMON_T_MIN_ALARM | HWMON_T_MAX_ALARM),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops पंचांगp108_hwmon_ops = अणु
	.is_visible = पंचांगp108_is_visible,
	.पढ़ो = पंचांगp108_पढ़ो,
	.ग_लिखो = पंचांगp108_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info पंचांगp108_chip_info = अणु
	.ops = &पंचांगp108_hwmon_ops,
	.info = पंचांगp108_info,
पूर्ण;

अटल व्योम पंचांगp108_restore_config(व्योम *data)
अणु
	काष्ठा पंचांगp108 *पंचांगp108 = data;

	regmap_ग_लिखो(पंचांगp108->regmap, TMP108_REG_CONF, पंचांगp108->orig_config);
पूर्ण

अटल bool पंचांगp108_is_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg != TMP108_REG_TEMP;
पूर्ण

अटल bool पंचांगp108_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* Configuration रेजिस्टर must be अस्थिर to enable FL and FH. */
	वापस reg == TMP108_REG_TEMP || reg == TMP108_REG_CONF;
पूर्ण

अटल स्थिर काष्ठा regmap_config पंचांगp108_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = TMP108_REG_THIGH,
	.ग_लिखोable_reg = पंचांगp108_is_ग_लिखोable_reg,
	.अस्थिर_reg = पंचांगp108_is_अस्थिर_reg,
	.val_क्रमmat_endian = REGMAP_ENDIAN_BIG,
	.cache_type = REGCACHE_RBTREE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल पूर्णांक पंचांगp108_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा पंचांगp108 *पंचांगp108;
	पूर्णांक err;
	u32 config;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WORD_DATA)) अणु
		dev_err(dev,
			"adapter doesn't support SMBus word transactions\n");
		वापस -ENODEV;
	पूर्ण

	पंचांगp108 = devm_kzalloc(dev, माप(*पंचांगp108), GFP_KERNEL);
	अगर (!पंचांगp108)
		वापस -ENOMEM;

	dev_set_drvdata(dev, पंचांगp108);

	पंचांगp108->regmap = devm_regmap_init_i2c(client, &पंचांगp108_regmap_config);
	अगर (IS_ERR(पंचांगp108->regmap)) अणु
		err = PTR_ERR(पंचांगp108->regmap);
		dev_err(dev, "regmap init failed: %d", err);
		वापस err;
	पूर्ण

	err = regmap_पढ़ो(पंचांगp108->regmap, TMP108_REG_CONF, &config);
	अगर (err < 0) अणु
		dev_err(dev, "error reading config register: %d", err);
		वापस err;
	पूर्ण
	पंचांगp108->orig_config = config;

	/* Only continuous mode is supported. */
	config &= ~TMP108_CONF_MODE_MASK;
	config |= TMP108_MODE_CONTINUOUS;

	/* Only comparator mode is supported. */
	config &= ~TMP108_CONF_TM;

	err = regmap_ग_लिखो(पंचांगp108->regmap, TMP108_REG_CONF, config);
	अगर (err < 0) अणु
		dev_err(dev, "error writing config register: %d", err);
		वापस err;
	पूर्ण

	पंचांगp108->पढ़ोy_समय = jअगरfies;
	अगर ((पंचांगp108->orig_config & TMP108_CONF_MODE_MASK) ==
	    TMP108_MODE_SHUTDOWN)
		पंचांगp108->पढ़ोy_समय +=
			msecs_to_jअगरfies(TMP108_CONVERSION_TIME_MS);

	err = devm_add_action_or_reset(dev, पंचांगp108_restore_config, पंचांगp108);
	अगर (err) अणु
		dev_err(dev, "add action or reset failed: %d", err);
		वापस err;
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, client->name,
							 पंचांगp108,
							 &पंचांगp108_chip_info,
							 शून्य);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल पूर्णांक __maybe_unused पंचांगp108_suspend(काष्ठा device *dev)
अणु
	काष्ठा पंचांगp108 *पंचांगp108 = dev_get_drvdata(dev);

	वापस regmap_update_bits(पंचांगp108->regmap, TMP108_REG_CONF,
				  TMP108_CONF_MODE_MASK, TMP108_MODE_SHUTDOWN);
पूर्ण

अटल पूर्णांक __maybe_unused पंचांगp108_resume(काष्ठा device *dev)
अणु
	काष्ठा पंचांगp108 *पंचांगp108 = dev_get_drvdata(dev);
	पूर्णांक err;

	err = regmap_update_bits(पंचांगp108->regmap, TMP108_REG_CONF,
				 TMP108_CONF_MODE_MASK, TMP108_MODE_CONTINUOUS);
	पंचांगp108->पढ़ोy_समय = jअगरfies +
			     msecs_to_jअगरfies(TMP108_CONVERSION_TIME_MS);
	वापस err;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(पंचांगp108_dev_pm_ops, पंचांगp108_suspend, पंचांगp108_resume);

अटल स्थिर काष्ठा i2c_device_id पंचांगp108_i2c_ids[] = अणु
	अणु "tmp108", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, पंचांगp108_i2c_ids);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id पंचांगp108_of_ids[] = अणु
	अणु .compatible = "ti,tmp108", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, पंचांगp108_of_ids);
#पूर्ण_अगर

अटल काष्ठा i2c_driver पंचांगp108_driver = अणु
	.driver = अणु
		.name	= DRIVER_NAME,
		.pm	= &पंचांगp108_dev_pm_ops,
		.of_match_table = of_match_ptr(पंचांगp108_of_ids),
	पूर्ण,
	.probe_new	= पंचांगp108_probe,
	.id_table	= पंचांगp108_i2c_ids,
पूर्ण;

module_i2c_driver(पंचांगp108_driver);

MODULE_AUTHOR("John Muir <john@jmuir.com>");
MODULE_DESCRIPTION("Texas Instruments TMP108 temperature sensor driver");
MODULE_LICENSE("GPL");
