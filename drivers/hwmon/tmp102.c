<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Texas Instruments TMP102 SMBus temperature sensor driver
 *
 * Copyright (C) 2010 Steven King <sfking@fdwdc.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of.h>

#घोषणा	DRIVER_NAME "tmp102"

#घोषणा	TMP102_TEMP_REG			0x00
#घोषणा	TMP102_CONF_REG			0x01
/* note: these bit definitions are byte swapped */
#घोषणा		TMP102_CONF_SD		0x0100
#घोषणा		TMP102_CONF_TM		0x0200
#घोषणा		TMP102_CONF_POL		0x0400
#घोषणा		TMP102_CONF_F0		0x0800
#घोषणा		TMP102_CONF_F1		0x1000
#घोषणा		TMP102_CONF_R0		0x2000
#घोषणा		TMP102_CONF_R1		0x4000
#घोषणा		TMP102_CONF_OS		0x8000
#घोषणा		TMP102_CONF_EM		0x0010
#घोषणा		TMP102_CONF_AL		0x0020
#घोषणा		TMP102_CONF_CR0		0x0040
#घोषणा		TMP102_CONF_CR1		0x0080
#घोषणा	TMP102_TLOW_REG			0x02
#घोषणा	TMP102_THIGH_REG		0x03

#घोषणा TMP102_CONFREG_MASK	(TMP102_CONF_SD | TMP102_CONF_TM | \
				 TMP102_CONF_POL | TMP102_CONF_F0 | \
				 TMP102_CONF_F1 | TMP102_CONF_OS | \
				 TMP102_CONF_EM | TMP102_CONF_AL | \
				 TMP102_CONF_CR0 | TMP102_CONF_CR1)

#घोषणा TMP102_CONFIG_CLEAR	(TMP102_CONF_SD | TMP102_CONF_OS | \
				 TMP102_CONF_CR0)
#घोषणा TMP102_CONFIG_SET	(TMP102_CONF_TM | TMP102_CONF_EM | \
				 TMP102_CONF_CR1)

#घोषणा CONVERSION_TIME_MS		35	/* in milli-seconds */

काष्ठा पंचांगp102 अणु
	काष्ठा regmap *regmap;
	u16 config_orig;
	अचिन्हित दीर्घ पढ़ोy_समय;
पूर्ण;

/* convert left adjusted 13-bit TMP102 रेजिस्टर value to milliCelsius */
अटल अंतरभूत पूर्णांक पंचांगp102_reg_to_mC(s16 val)
अणु
	वापस ((val & ~0x01) * 1000) / 128;
पूर्ण

/* convert milliCelsius to left adjusted 13-bit TMP102 रेजिस्टर value */
अटल अंतरभूत u16 पंचांगp102_mC_to_reg(पूर्णांक val)
अणु
	वापस (val * 128) / 1000;
पूर्ण

अटल पूर्णांक पंचांगp102_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		       u32 attr, पूर्णांक channel, दीर्घ *temp)
अणु
	काष्ठा पंचांगp102 *पंचांगp102 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक regval;
	पूर्णांक err, reg;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		/* Is it too early to वापस a conversion ? */
		अगर (समय_beक्रमe(jअगरfies, पंचांगp102->पढ़ोy_समय)) अणु
			dev_dbg(dev, "%s: Conversion not ready yet..\n", __func__);
			वापस -EAGAIN;
		पूर्ण
		reg = TMP102_TEMP_REG;
		अवरोध;
	हाल hwmon_temp_max_hyst:
		reg = TMP102_TLOW_REG;
		अवरोध;
	हाल hwmon_temp_max:
		reg = TMP102_THIGH_REG;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	err = regmap_पढ़ो(पंचांगp102->regmap, reg, &regval);
	अगर (err < 0)
		वापस err;
	*temp = पंचांगp102_reg_to_mC(regval);

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांगp102_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ temp)
अणु
	काष्ठा पंचांगp102 *पंचांगp102 = dev_get_drvdata(dev);
	पूर्णांक reg;

	चयन (attr) अणु
	हाल hwmon_temp_max_hyst:
		reg = TMP102_TLOW_REG;
		अवरोध;
	हाल hwmon_temp_max:
		reg = TMP102_THIGH_REG;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	temp = clamp_val(temp, -256000, 255000);
	वापस regmap_ग_लिखो(पंचांगp102->regmap, reg, पंचांगp102_mC_to_reg(temp));
पूर्ण

अटल umode_t पंचांगp102_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type,
				 u32 attr, पूर्णांक channel)
अणु
	अगर (type != hwmon_temp)
		वापस 0;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		वापस 0444;
	हाल hwmon_temp_max_hyst:
	हाल hwmon_temp_max:
		वापस 0644;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *पंचांगp102_info[] = अणु
	HWMON_CHANNEL_INFO(chip,
			   HWMON_C_REGISTER_TZ),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops पंचांगp102_hwmon_ops = अणु
	.is_visible = पंचांगp102_is_visible,
	.पढ़ो = पंचांगp102_पढ़ो,
	.ग_लिखो = पंचांगp102_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info पंचांगp102_chip_info = अणु
	.ops = &पंचांगp102_hwmon_ops,
	.info = पंचांगp102_info,
पूर्ण;

अटल व्योम पंचांगp102_restore_config(व्योम *data)
अणु
	काष्ठा पंचांगp102 *पंचांगp102 = data;

	regmap_ग_लिखो(पंचांगp102->regmap, TMP102_CONF_REG, पंचांगp102->config_orig);
पूर्ण

अटल bool पंचांगp102_is_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg != TMP102_TEMP_REG;
पूर्ण

अटल bool पंचांगp102_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg == TMP102_TEMP_REG;
पूर्ण

अटल स्थिर काष्ठा regmap_config पंचांगp102_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = TMP102_THIGH_REG,
	.ग_लिखोable_reg = पंचांगp102_is_ग_लिखोable_reg,
	.अस्थिर_reg = पंचांगp102_is_अस्थिर_reg,
	.val_क्रमmat_endian = REGMAP_ENDIAN_BIG,
	.cache_type = REGCACHE_RBTREE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल पूर्णांक पंचांगp102_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा पंचांगp102 *पंचांगp102;
	अचिन्हित पूर्णांक regval;
	पूर्णांक err;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WORD_DATA)) अणु
		dev_err(dev,
			"adapter doesn't support SMBus word transactions\n");
		वापस -ENODEV;
	पूर्ण

	पंचांगp102 = devm_kzalloc(dev, माप(*पंचांगp102), GFP_KERNEL);
	अगर (!पंचांगp102)
		वापस -ENOMEM;

	i2c_set_clientdata(client, पंचांगp102);

	पंचांगp102->regmap = devm_regmap_init_i2c(client, &पंचांगp102_regmap_config);
	अगर (IS_ERR(पंचांगp102->regmap))
		वापस PTR_ERR(पंचांगp102->regmap);

	err = regmap_पढ़ो(पंचांगp102->regmap, TMP102_CONF_REG, &regval);
	अगर (err < 0) अणु
		dev_err(dev, "error reading config register\n");
		वापस err;
	पूर्ण

	अगर ((regval & ~TMP102_CONFREG_MASK) !=
	    (TMP102_CONF_R0 | TMP102_CONF_R1)) अणु
		dev_err(dev, "unexpected config register value\n");
		वापस -ENODEV;
	पूर्ण

	पंचांगp102->config_orig = regval;

	err = devm_add_action_or_reset(dev, पंचांगp102_restore_config, पंचांगp102);
	अगर (err)
		वापस err;

	regval &= ~TMP102_CONFIG_CLEAR;
	regval |= TMP102_CONFIG_SET;

	err = regmap_ग_लिखो(पंचांगp102->regmap, TMP102_CONF_REG, regval);
	अगर (err < 0) अणु
		dev_err(dev, "error writing config register\n");
		वापस err;
	पूर्ण

	/*
	 * Mark that we are not पढ़ोy with data until the first
	 * conversion is complete
	 */
	पंचांगp102->पढ़ोy_समय = jअगरfies + msecs_to_jअगरfies(CONVERSION_TIME_MS);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, client->name,
							 पंचांगp102,
							 &पंचांगp102_chip_info,
							 शून्य);
	अगर (IS_ERR(hwmon_dev)) अणु
		dev_dbg(dev, "unable to register hwmon device\n");
		वापस PTR_ERR(hwmon_dev);
	पूर्ण
	dev_info(dev, "initialized\n");

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक पंचांगp102_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा पंचांगp102 *पंचांगp102 = i2c_get_clientdata(client);

	वापस regmap_update_bits(पंचांगp102->regmap, TMP102_CONF_REG,
				  TMP102_CONF_SD, TMP102_CONF_SD);
पूर्ण

अटल पूर्णांक पंचांगp102_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा पंचांगp102 *पंचांगp102 = i2c_get_clientdata(client);
	पूर्णांक err;

	err = regmap_update_bits(पंचांगp102->regmap, TMP102_CONF_REG,
				 TMP102_CONF_SD, 0);

	पंचांगp102->पढ़ोy_समय = jअगरfies + msecs_to_jअगरfies(CONVERSION_TIME_MS);

	वापस err;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल SIMPLE_DEV_PM_OPS(पंचांगp102_dev_pm_ops, पंचांगp102_suspend, पंचांगp102_resume);

अटल स्थिर काष्ठा i2c_device_id पंचांगp102_id[] = अणु
	अणु "tmp102", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, पंचांगp102_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused पंचांगp102_of_match[] = अणु
	अणु .compatible = "ti,tmp102" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, पंचांगp102_of_match);

अटल काष्ठा i2c_driver पंचांगp102_driver = अणु
	.driver.name	= DRIVER_NAME,
	.driver.of_match_table = of_match_ptr(पंचांगp102_of_match),
	.driver.pm	= &पंचांगp102_dev_pm_ops,
	.probe_new	= पंचांगp102_probe,
	.id_table	= पंचांगp102_id,
पूर्ण;

module_i2c_driver(पंचांगp102_driver);

MODULE_AUTHOR("Steven King <sfking@fdwdc.com>");
MODULE_DESCRIPTION("Texas Instruments TMP102 temperature sensor driver");
MODULE_LICENSE("GPL");
