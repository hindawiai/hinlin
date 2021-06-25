<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CM3232 Ambient Light Sensor
 *
 * Copyright (C) 2014-2015 Capella Microप्रणालीs Inc.
 * Author: Kevin Tsai <ktsai@capellamicro.com>
 *
 * IIO driver क्रम CM3232 (7-bit I2C slave address 0x10).
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/init.h>

/* Registers Address */
#घोषणा CM3232_REG_ADDR_CMD		0x00
#घोषणा CM3232_REG_ADDR_ALS		0x50
#घोषणा CM3232_REG_ADDR_ID		0x53

#घोषणा CM3232_CMD_ALS_DISABLE		BIT(0)

#घोषणा CM3232_CMD_ALS_IT_SHIFT		2
#घोषणा CM3232_CMD_ALS_IT_MASK		(BIT(2) | BIT(3) | BIT(4))
#घोषणा CM3232_CMD_ALS_IT_DEFAULT	(0x01 << CM3232_CMD_ALS_IT_SHIFT)

#घोषणा CM3232_CMD_ALS_RESET		BIT(6)

#घोषणा CM3232_CMD_DEFAULT		CM3232_CMD_ALS_IT_DEFAULT

#घोषणा CM3232_HW_ID			0x32
#घोषणा CM3232_CALIBSCALE_DEFAULT	100000
#घोषणा CM3232_CALIBSCALE_RESOLUTION	100000
#घोषणा CM3232_MLUX_PER_LUX		1000

#घोषणा CM3232_MLUX_PER_BIT_DEFAULT	64
#घोषणा CM3232_MLUX_PER_BIT_BASE_IT	100000

अटल स्थिर काष्ठा अणु
	पूर्णांक val;
	पूर्णांक val2;
	u8 it;
पूर्ण cm3232_als_it_scales[] = अणु
	अणु0, 100000, 0पूर्ण,	/* 0.100000 */
	अणु0, 200000, 1पूर्ण,	/* 0.200000 */
	अणु0, 400000, 2पूर्ण,	/* 0.400000 */
	अणु0, 800000, 3पूर्ण,	/* 0.800000 */
	अणु1, 600000, 4पूर्ण,	/* 1.600000 */
	अणु3, 200000, 5पूर्ण,	/* 3.200000 */
पूर्ण;

काष्ठा cm3232_als_info अणु
	u8 regs_cmd_शेष;
	u8 hw_id;
	पूर्णांक calibscale;
	पूर्णांक mlux_per_bit;
	पूर्णांक mlux_per_bit_base_it;
पूर्ण;

अटल काष्ठा cm3232_als_info cm3232_als_info_शेष = अणु
	.regs_cmd_शेष = CM3232_CMD_DEFAULT,
	.hw_id = CM3232_HW_ID,
	.calibscale = CM3232_CALIBSCALE_DEFAULT,
	.mlux_per_bit = CM3232_MLUX_PER_BIT_DEFAULT,
	.mlux_per_bit_base_it = CM3232_MLUX_PER_BIT_BASE_IT,
पूर्ण;

काष्ठा cm3232_chip अणु
	काष्ठा i2c_client *client;
	काष्ठा cm3232_als_info *als_info;
	u8 regs_cmd;
	u16 regs_als;
पूर्ण;

/**
 * cm3232_reg_init() - Initialize CM3232
 * @chip:	poपूर्णांकer of काष्ठा cm3232_chip.
 *
 * Check and initialize CM3232 ambient light sensor.
 *
 * Return: 0 क्रम success; otherwise क्रम error code.
 */
अटल पूर्णांक cm3232_reg_init(काष्ठा cm3232_chip *chip)
अणु
	काष्ठा i2c_client *client = chip->client;
	s32 ret;

	chip->als_info = &cm3232_als_info_शेष;

	/* Identअगरy device */
	ret = i2c_smbus_पढ़ो_word_data(client, CM3232_REG_ADDR_ID);
	अगर (ret < 0) अणु
		dev_err(&chip->client->dev, "Error reading addr_id\n");
		वापस ret;
	पूर्ण

	अगर ((ret & 0xFF) != chip->als_info->hw_id)
		वापस -ENODEV;

	/* Disable and reset device */
	chip->regs_cmd = CM3232_CMD_ALS_DISABLE | CM3232_CMD_ALS_RESET;
	ret = i2c_smbus_ग_लिखो_byte_data(client, CM3232_REG_ADDR_CMD,
					chip->regs_cmd);
	अगर (ret < 0) अणु
		dev_err(&chip->client->dev, "Error writing reg_cmd\n");
		वापस ret;
	पूर्ण

	/* Register शेष value */
	chip->regs_cmd = chip->als_info->regs_cmd_शेष;

	/* Configure रेजिस्टर */
	ret = i2c_smbus_ग_लिखो_byte_data(client, CM3232_REG_ADDR_CMD,
					chip->regs_cmd);
	अगर (ret < 0)
		dev_err(&chip->client->dev, "Error writing reg_cmd\n");

	वापस ret;
पूर्ण

/**
 *  cm3232_पढ़ो_als_it() - Get sensor पूर्णांकegration समय
 *  @chip:	poपूर्णांकer of काष्ठा cm3232_chip
 *  @val:	poपूर्णांकer of पूर्णांक to load the पूर्णांकegration (sec).
 *  @val2:	poपूर्णांकer of पूर्णांक to load the पूर्णांकegration समय (microsecond).
 *
 *  Report the current पूर्णांकegration समय.
 *
 *  Return: IIO_VAL_INT_PLUS_MICRO क्रम success, otherwise -EINVAL.
 */
अटल पूर्णांक cm3232_पढ़ो_als_it(काष्ठा cm3232_chip *chip, पूर्णांक *val, पूर्णांक *val2)
अणु
	u16 als_it;
	पूर्णांक i;

	als_it = chip->regs_cmd;
	als_it &= CM3232_CMD_ALS_IT_MASK;
	als_it >>= CM3232_CMD_ALS_IT_SHIFT;
	क्रम (i = 0; i < ARRAY_SIZE(cm3232_als_it_scales); i++) अणु
		अगर (als_it == cm3232_als_it_scales[i].it) अणु
			*val = cm3232_als_it_scales[i].val;
			*val2 = cm3232_als_it_scales[i].val2;
			वापस IIO_VAL_INT_PLUS_MICRO;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * cm3232_ग_लिखो_als_it() - Write sensor पूर्णांकegration समय
 * @chip:	poपूर्णांकer of काष्ठा cm3232_chip.
 * @val:	पूर्णांकegration समय in second.
 * @val2:	पूर्णांकegration समय in microsecond.
 *
 * Convert पूर्णांकegration समय to sensor value.
 *
 * Return: i2c_smbus_ग_लिखो_byte_data command वापस value.
 */
अटल पूर्णांक cm3232_ग_लिखो_als_it(काष्ठा cm3232_chip *chip, पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा i2c_client *client = chip->client;
	u16 als_it, cmd;
	पूर्णांक i;
	s32 ret;

	क्रम (i = 0; i < ARRAY_SIZE(cm3232_als_it_scales); i++) अणु
		अगर (val == cm3232_als_it_scales[i].val &&
			val2 == cm3232_als_it_scales[i].val2) अणु

			als_it = cm3232_als_it_scales[i].it;
			als_it <<= CM3232_CMD_ALS_IT_SHIFT;

			cmd = chip->regs_cmd & ~CM3232_CMD_ALS_IT_MASK;
			cmd |= als_it;
			ret = i2c_smbus_ग_लिखो_byte_data(client,
							CM3232_REG_ADDR_CMD,
							cmd);
			अगर (ret < 0)
				वापस ret;
			chip->regs_cmd = cmd;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

/**
 * cm3232_get_lux() - report current lux value
 * @chip:	poपूर्णांकer of काष्ठा cm3232_chip.
 *
 * Convert sensor data to lux.  It depends on पूर्णांकegration
 * समय and calibscale variable.
 *
 * Return: Zero or positive value is lux, otherwise error code.
 */
अटल पूर्णांक cm3232_get_lux(काष्ठा cm3232_chip *chip)
अणु
	काष्ठा i2c_client *client = chip->client;
	काष्ठा cm3232_als_info *als_info = chip->als_info;
	पूर्णांक ret;
	पूर्णांक val, val2;
	पूर्णांक als_it;
	u64 lux;

	/* Calculate mlux per bit based on als_it */
	ret = cm3232_पढ़ो_als_it(chip, &val, &val2);
	अगर (ret < 0)
		वापस -EINVAL;
	als_it = val * 1000000 + val2;
	lux = (__क्रमce u64)als_info->mlux_per_bit;
	lux *= als_info->mlux_per_bit_base_it;
	lux = भाग_u64(lux, als_it);

	ret = i2c_smbus_पढ़ो_word_data(client, CM3232_REG_ADDR_ALS);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Error reading reg_addr_als\n");
		वापस ret;
	पूर्ण

	chip->regs_als = (u16)ret;
	lux *= chip->regs_als;
	lux *= als_info->calibscale;
	lux = भाग_u64(lux, CM3232_CALIBSCALE_RESOLUTION);
	lux = भाग_u64(lux, CM3232_MLUX_PER_LUX);

	अगर (lux > 0xFFFF)
		lux = 0xFFFF;

	वापस (पूर्णांक)lux;
पूर्ण

अटल पूर्णांक cm3232_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा cm3232_chip *chip = iio_priv(indio_dev);
	काष्ठा cm3232_als_info *als_info = chip->als_info;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		ret = cm3232_get_lux(chip);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_CALIBSCALE:
		*val = als_info->calibscale;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_INT_TIME:
		वापस cm3232_पढ़ो_als_it(chip, val, val2);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cm3232_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा cm3232_chip *chip = iio_priv(indio_dev);
	काष्ठा cm3232_als_info *als_info = chip->als_info;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_CALIBSCALE:
		als_info->calibscale = val;
		वापस 0;
	हाल IIO_CHAN_INFO_INT_TIME:
		वापस cm3232_ग_लिखो_als_it(chip, val, val2);
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * cm3232_get_it_available() - Get available ALS IT value
 * @dev:	poपूर्णांकer of काष्ठा device.
 * @attr:	poपूर्णांकer of काष्ठा device_attribute.
 * @buf:	poपूर्णांकer of वापस string buffer.
 *
 * Display the available पूर्णांकegration समय in second.
 *
 * Return: string length.
 */
अटल sमाप_प्रकार cm3232_get_it_available(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक i, len;

	क्रम (i = 0, len = 0; i < ARRAY_SIZE(cm3232_als_it_scales); i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%u.%06u ",
			cm3232_als_it_scales[i].val,
			cm3232_als_it_scales[i].val2);
	वापस len + scnम_लिखो(buf + len, PAGE_SIZE - len, "\n");
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec cm3232_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_PROCESSED) |
			BIT(IIO_CHAN_INFO_CALIBSCALE) |
			BIT(IIO_CHAN_INFO_INT_TIME),
	पूर्ण
पूर्ण;

अटल IIO_DEVICE_ATTR(in_illuminance_पूर्णांकegration_समय_available,
			S_IRUGO, cm3232_get_it_available, शून्य, 0);

अटल काष्ठा attribute *cm3232_attributes[] = अणु
	&iio_dev_attr_in_illuminance_पूर्णांकegration_समय_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group cm3232_attribute_group = अणु
	.attrs = cm3232_attributes
पूर्ण;

अटल स्थिर काष्ठा iio_info cm3232_info = अणु
	.पढ़ो_raw		= &cm3232_पढ़ो_raw,
	.ग_लिखो_raw		= &cm3232_ग_लिखो_raw,
	.attrs			= &cm3232_attribute_group,
पूर्ण;

अटल पूर्णांक cm3232_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cm3232_chip *chip;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*chip));
	अगर (!indio_dev)
		वापस -ENOMEM;

	chip = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	chip->client = client;

	indio_dev->channels = cm3232_channels;
	indio_dev->num_channels = ARRAY_SIZE(cm3232_channels);
	indio_dev->info = &cm3232_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = cm3232_reg_init(chip);
	अगर (ret) अणु
		dev_err(&client->dev,
			"%s: register init failed\n",
			__func__);
		वापस ret;
	पूर्ण

	वापस iio_device_रेजिस्टर(indio_dev);
पूर्ण

अटल पूर्णांक cm3232_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	i2c_smbus_ग_लिखो_byte_data(client, CM3232_REG_ADDR_CMD,
		CM3232_CMD_ALS_DISABLE);

	iio_device_unरेजिस्टर(indio_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id cm3232_id[] = अणु
	अणु"cm3232", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक cm3232_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा cm3232_chip *chip = iio_priv(indio_dev);
	काष्ठा i2c_client *client = chip->client;
	पूर्णांक ret;

	chip->regs_cmd |= CM3232_CMD_ALS_DISABLE;
	ret = i2c_smbus_ग_लिखो_byte_data(client, CM3232_REG_ADDR_CMD,
					chip->regs_cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक cm3232_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा cm3232_chip *chip = iio_priv(indio_dev);
	काष्ठा i2c_client *client = chip->client;
	पूर्णांक ret;

	chip->regs_cmd &= ~CM3232_CMD_ALS_DISABLE;
	ret = i2c_smbus_ग_लिखो_byte_data(client, CM3232_REG_ADDR_CMD,
					chip->regs_cmd | CM3232_CMD_ALS_RESET);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cm3232_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(cm3232_suspend, cm3232_resume)पूर्ण;
#पूर्ण_अगर

MODULE_DEVICE_TABLE(i2c, cm3232_id);

अटल स्थिर काष्ठा of_device_id cm3232_of_match[] = अणु
	अणु.compatible = "capella,cm3232"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cm3232_of_match);

अटल काष्ठा i2c_driver cm3232_driver = अणु
	.driver = अणु
		.name	= "cm3232",
		.of_match_table = cm3232_of_match,
#अगर_घोषित CONFIG_PM_SLEEP
		.pm	= &cm3232_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.id_table	= cm3232_id,
	.probe		= cm3232_probe,
	.हटाओ		= cm3232_हटाओ,
पूर्ण;

module_i2c_driver(cm3232_driver);

MODULE_AUTHOR("Kevin Tsai <ktsai@capellamicro.com>");
MODULE_DESCRIPTION("CM3232 ambient light sensor driver");
MODULE_LICENSE("GPL");
