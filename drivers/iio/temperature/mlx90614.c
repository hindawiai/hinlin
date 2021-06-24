<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mlx90614.c - Support क्रम Melexis MLX90614 contactless IR temperature sensor
 *
 * Copyright (c) 2014 Peter Meerwald <pmeerw@pmeerw.net>
 * Copyright (c) 2015 Essensium NV
 * Copyright (c) 2015 Melexis
 *
 * Driver क्रम the Melexis MLX90614 I2C 16-bit IR thermopile sensor
 *
 * (7-bit I2C slave address 0x5a, 100KHz bus speed only!)
 *
 * To wake up from sleep mode, the SDA line must be held low जबतक SCL is high
 * क्रम at least 33ms.  This is achieved with an extra GPIO that can be connected
 * directly to the SDA line.  In normal operation, the GPIO is set as input and
 * will not पूर्णांकerfere in I2C communication.  While the GPIO is driven low, the
 * i2c adapter is locked since it cannot be used by other clients.  The SCL line
 * always has a pull-up so we करो not need an extra GPIO to drive it high.  If
 * the "wakeup" GPIO is not given, घातer management will be disabled.
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा MLX90614_OP_RAM		0x00
#घोषणा MLX90614_OP_EEPROM	0x20
#घोषणा MLX90614_OP_SLEEP	0xff

/* RAM offsets with 16-bit data, MSB first */
#घोषणा MLX90614_RAW1	(MLX90614_OP_RAM | 0x04) /* raw data IR channel 1 */
#घोषणा MLX90614_RAW2	(MLX90614_OP_RAM | 0x05) /* raw data IR channel 2 */
#घोषणा MLX90614_TA	(MLX90614_OP_RAM | 0x06) /* ambient temperature */
#घोषणा MLX90614_TOBJ1	(MLX90614_OP_RAM | 0x07) /* object 1 temperature */
#घोषणा MLX90614_TOBJ2	(MLX90614_OP_RAM | 0x08) /* object 2 temperature */

/* EEPROM offsets with 16-bit data, MSB first */
#घोषणा MLX90614_EMISSIVITY	(MLX90614_OP_EEPROM | 0x04) /* emissivity correction coefficient */
#घोषणा MLX90614_CONFIG		(MLX90614_OP_EEPROM | 0x05) /* configuration रेजिस्टर */

/* Control bits in configuration रेजिस्टर */
#घोषणा MLX90614_CONFIG_IIR_SHIFT 0 /* IIR coefficient */
#घोषणा MLX90614_CONFIG_IIR_MASK (0x7 << MLX90614_CONFIG_IIR_SHIFT)
#घोषणा MLX90614_CONFIG_DUAL_SHIFT 6 /* single (0) or dual (1) IR sensor */
#घोषणा MLX90614_CONFIG_DUAL_MASK (1 << MLX90614_CONFIG_DUAL_SHIFT)
#घोषणा MLX90614_CONFIG_FIR_SHIFT 8 /* FIR coefficient */
#घोषणा MLX90614_CONFIG_FIR_MASK (0x7 << MLX90614_CONFIG_FIR_SHIFT)
#घोषणा MLX90614_CONFIG_GAIN_SHIFT 11 /* gain */
#घोषणा MLX90614_CONFIG_GAIN_MASK (0x7 << MLX90614_CONFIG_GAIN_SHIFT)

/* Timings (in ms) */
#घोषणा MLX90614_TIMING_EEPROM 20 /* समय क्रम EEPROM ग_लिखो/erase to complete */
#घोषणा MLX90614_TIMING_WAKEUP 34 /* समय to hold SDA low क्रम wake-up */
#घोषणा MLX90614_TIMING_STARTUP 250 /* समय beक्रमe first data after wake-up */

#घोषणा MLX90614_AUTOSLEEP_DELAY 5000 /* शेष स्वतःsleep delay */

/* Magic स्थिरants */
#घोषणा MLX90614_CONST_OFFSET_DEC -13657 /* decimal part of the Kelvin offset */
#घोषणा MLX90614_CONST_OFFSET_REM 500000 /* reमुख्यder of offset (273.15*50) */
#घोषणा MLX90614_CONST_SCALE 20 /* Scale in milliKelvin (0.02 * 1000) */
#घोषणा MLX90614_CONST_RAW_EMISSIVITY_MAX 65535 /* max value क्रम emissivity */
#घोषणा MLX90614_CONST_EMISSIVITY_RESOLUTION 15259 /* 1/65535 ~ 0.000015259 */
#घोषणा MLX90614_CONST_FIR 0x7 /* Fixed value क्रम FIR part of low pass filter */

काष्ठा mlx90614_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock; /* क्रम EEPROM access only */
	काष्ठा gpio_desc *wakeup_gpio; /* शून्य to disable sleep/wake-up */
	अचिन्हित दीर्घ पढ़ोy_बारtamp; /* in jअगरfies */
पूर्ण;

/* Bandwidth values क्रम IIR filtering */
अटल स्थिर पूर्णांक mlx90614_iir_values[] = अणु77, 31, 20, 15, 723, 153, 110, 86पूर्ण;
अटल IIO_CONST_ATTR(in_temp_object_filter_low_pass_3db_frequency_available,
		      "0.15 0.20 0.31 0.77 0.86 1.10 1.53 7.23");

अटल काष्ठा attribute *mlx90614_attributes[] = अणु
	&iio_स्थिर_attr_in_temp_object_filter_low_pass_3db_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mlx90614_attr_group = अणु
	.attrs = mlx90614_attributes,
पूर्ण;

/*
 * Erase an address and ग_लिखो word.
 * The mutex must be locked beक्रमe calling.
 */
अटल s32 mlx90614_ग_लिखो_word(स्थिर काष्ठा i2c_client *client, u8 command,
			       u16 value)
अणु
	/*
	 * Note: The mlx90614 requires a PEC on writing but करोes not send us a
	 * valid PEC on पढ़ोing.  Hence, we cannot set I2C_CLIENT_PEC in
	 * i2c_client.flags.  As a workaround, we use i2c_smbus_xfer here.
	 */
	जोड़ i2c_smbus_data data;
	s32 ret;

	dev_dbg(&client->dev, "Writing 0x%x to address 0x%x", value, command);

	data.word = 0x0000; /* erase command */
	ret = i2c_smbus_xfer(client->adapter, client->addr,
			     client->flags | I2C_CLIENT_PEC,
			     I2C_SMBUS_WRITE, command,
			     I2C_SMBUS_WORD_DATA, &data);
	अगर (ret < 0)
		वापस ret;

	msleep(MLX90614_TIMING_EEPROM);

	data.word = value; /* actual ग_लिखो */
	ret = i2c_smbus_xfer(client->adapter, client->addr,
			     client->flags | I2C_CLIENT_PEC,
			     I2C_SMBUS_WRITE, command,
			     I2C_SMBUS_WORD_DATA, &data);

	msleep(MLX90614_TIMING_EEPROM);

	वापस ret;
पूर्ण

/*
 * Find the IIR value inside mlx90614_iir_values array and वापस its position
 * which is equivalent to the bit value in sensor रेजिस्टर
 */
अटल अंतरभूत s32 mlx90614_iir_search(स्थिर काष्ठा i2c_client *client,
				      पूर्णांक value)
अणु
	पूर्णांक i;
	s32 ret;

	क्रम (i = 0; i < ARRAY_SIZE(mlx90614_iir_values); ++i) अणु
		अगर (value == mlx90614_iir_values[i])
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(mlx90614_iir_values))
		वापस -EINVAL;

	/*
	 * CONFIG रेजिस्टर values must not be changed so
	 * we must पढ़ो them beक्रमe we actually ग_लिखो
	 * changes
	 */
	ret = i2c_smbus_पढ़ो_word_data(client, MLX90614_CONFIG);
	अगर (ret < 0)
		वापस ret;

	ret &= ~MLX90614_CONFIG_FIR_MASK;
	ret |= MLX90614_CONST_FIR << MLX90614_CONFIG_FIR_SHIFT;
	ret &= ~MLX90614_CONFIG_IIR_MASK;
	ret |= i << MLX90614_CONFIG_IIR_SHIFT;

	/* Write changed values */
	ret = mlx90614_ग_लिखो_word(client, MLX90614_CONFIG, ret);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
/*
 * If @startup is true, make sure MLX90614_TIMING_STARTUP ms have elapsed since
 * the last wake-up.  This is normally only needed to get a valid temperature
 * पढ़ोing.  EEPROM access करोes not need such delay.
 * Return 0 on success, <0 on error.
 */
अटल पूर्णांक mlx90614_घातer_get(काष्ठा mlx90614_data *data, bool startup)
अणु
	अचिन्हित दीर्घ now;

	अगर (!data->wakeup_gpio)
		वापस 0;

	pm_runसमय_get_sync(&data->client->dev);

	अगर (startup) अणु
		now = jअगरfies;
		अगर (समय_beक्रमe(now, data->पढ़ोy_बारtamp) &&
		    msleep_पूर्णांकerruptible(jअगरfies_to_msecs(
				data->पढ़ोy_बारtamp - now)) != 0) अणु
			pm_runसमय_put_स्वतःsuspend(&data->client->dev);
			वापस -EINTR;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mlx90614_घातer_put(काष्ठा mlx90614_data *data)
अणु
	अगर (!data->wakeup_gpio)
		वापस;

	pm_runसमय_mark_last_busy(&data->client->dev);
	pm_runसमय_put_स्वतःsuspend(&data->client->dev);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक mlx90614_घातer_get(काष्ठा mlx90614_data *data, bool startup)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mlx90614_घातer_put(काष्ठा mlx90614_data *data)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mlx90614_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *val,
			    पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mlx90614_data *data = iio_priv(indio_dev);
	u8 cmd;
	s32 ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW: /* 0.02K / LSB */
		चयन (channel->channel2) अणु
		हाल IIO_MOD_TEMP_AMBIENT:
			cmd = MLX90614_TA;
			अवरोध;
		हाल IIO_MOD_TEMP_OBJECT:
			चयन (channel->channel) अणु
			हाल 0:
				cmd = MLX90614_TOBJ1;
				अवरोध;
			हाल 1:
				cmd = MLX90614_TOBJ2;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		ret = mlx90614_घातer_get(data, true);
		अगर (ret < 0)
			वापस ret;
		ret = i2c_smbus_पढ़ो_word_data(data->client, cmd);
		mlx90614_घातer_put(data);

		अगर (ret < 0)
			वापस ret;

		/* MSB is an error flag */
		अगर (ret & 0x8000)
			वापस -EIO;

		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = MLX90614_CONST_OFFSET_DEC;
		*val2 = MLX90614_CONST_OFFSET_REM;
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SCALE:
		*val = MLX90614_CONST_SCALE;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_CALIBEMISSIVITY: /* 1/65535 / LSB */
		mlx90614_घातer_get(data, false);
		mutex_lock(&data->lock);
		ret = i2c_smbus_पढ़ो_word_data(data->client,
					       MLX90614_EMISSIVITY);
		mutex_unlock(&data->lock);
		mlx90614_घातer_put(data);

		अगर (ret < 0)
			वापस ret;

		अगर (ret == MLX90614_CONST_RAW_EMISSIVITY_MAX) अणु
			*val = 1;
			*val2 = 0;
		पूर्ण अन्यथा अणु
			*val = 0;
			*val2 = ret * MLX90614_CONST_EMISSIVITY_RESOLUTION;
		पूर्ण
		वापस IIO_VAL_INT_PLUS_न_अंकO;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY: /* IIR setting with
							     FIR = 1024 */
		mlx90614_घातer_get(data, false);
		mutex_lock(&data->lock);
		ret = i2c_smbus_पढ़ो_word_data(data->client, MLX90614_CONFIG);
		mutex_unlock(&data->lock);
		mlx90614_घातer_put(data);

		अगर (ret < 0)
			वापस ret;

		*val = mlx90614_iir_values[ret & MLX90614_CONFIG_IIR_MASK] / 100;
		*val2 = (mlx90614_iir_values[ret & MLX90614_CONFIG_IIR_MASK] % 100) *
			10000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx90614_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक val,
			     पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा mlx90614_data *data = iio_priv(indio_dev);
	s32 ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_CALIBEMISSIVITY: /* 1/65535 / LSB */
		अगर (val < 0 || val2 < 0 || val > 1 || (val == 1 && val2 != 0))
			वापस -EINVAL;
		val = val * MLX90614_CONST_RAW_EMISSIVITY_MAX +
			val2 / MLX90614_CONST_EMISSIVITY_RESOLUTION;

		mlx90614_घातer_get(data, false);
		mutex_lock(&data->lock);
		ret = mlx90614_ग_लिखो_word(data->client, MLX90614_EMISSIVITY,
					  val);
		mutex_unlock(&data->lock);
		mlx90614_घातer_put(data);

		वापस ret;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY: /* IIR Filter setting */
		अगर (val < 0 || val2 < 0)
			वापस -EINVAL;

		mlx90614_घातer_get(data, false);
		mutex_lock(&data->lock);
		ret = mlx90614_iir_search(data->client,
					  val * 100 + val2 / 10000);
		mutex_unlock(&data->lock);
		mlx90614_घातer_put(data);

		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx90614_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
				     काष्ठा iio_chan_spec स्थिर *channel,
				     दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_CALIBEMISSIVITY:
		वापस IIO_VAL_INT_PLUS_न_अंकO;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mlx90614_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.modअगरied = 1,
		.channel2 = IIO_MOD_TEMP_AMBIENT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		    BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.modअगरied = 1,
		.channel2 = IIO_MOD_TEMP_OBJECT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
		    BIT(IIO_CHAN_INFO_CALIBEMISSIVITY) |
			BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		    BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.indexed = 1,
		.modअगरied = 1,
		.channel = 1,
		.channel2 = IIO_MOD_TEMP_OBJECT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
		    BIT(IIO_CHAN_INFO_CALIBEMISSIVITY) |
			BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		    BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_info mlx90614_info = अणु
	.पढ़ो_raw = mlx90614_पढ़ो_raw,
	.ग_लिखो_raw = mlx90614_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = mlx90614_ग_लिखो_raw_get_fmt,
	.attrs = &mlx90614_attr_group,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mlx90614_sleep(काष्ठा mlx90614_data *data)
अणु
	s32 ret;

	अगर (!data->wakeup_gpio) अणु
		dev_dbg(&data->client->dev, "Sleep disabled");
		वापस -ENOSYS;
	पूर्ण

	dev_dbg(&data->client->dev, "Requesting sleep");

	mutex_lock(&data->lock);
	ret = i2c_smbus_xfer(data->client->adapter, data->client->addr,
			     data->client->flags | I2C_CLIENT_PEC,
			     I2C_SMBUS_WRITE, MLX90614_OP_SLEEP,
			     I2C_SMBUS_BYTE, शून्य);
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक mlx90614_wakeup(काष्ठा mlx90614_data *data)
अणु
	अगर (!data->wakeup_gpio) अणु
		dev_dbg(&data->client->dev, "Wake-up disabled");
		वापस -ENOSYS;
	पूर्ण

	dev_dbg(&data->client->dev, "Requesting wake-up");

	i2c_lock_bus(data->client->adapter, I2C_LOCK_ROOT_ADAPTER);
	gpiod_direction_output(data->wakeup_gpio, 0);
	msleep(MLX90614_TIMING_WAKEUP);
	gpiod_direction_input(data->wakeup_gpio);
	i2c_unlock_bus(data->client->adapter, I2C_LOCK_ROOT_ADAPTER);

	data->पढ़ोy_बारtamp = jअगरfies +
			msecs_to_jअगरfies(MLX90614_TIMING_STARTUP);

	/*
	 * Quirk: the i2c controller may get confused right after the
	 * wake-up संकेत has been sent.  As a workaround, करो a dummy पढ़ो.
	 * If the पढ़ो fails, the controller will probably be reset so that
	 * further पढ़ोs will work.
	 */
	i2c_smbus_पढ़ो_word_data(data->client, MLX90614_CONFIG);

	वापस 0;
पूर्ण

/* Return wake-up GPIO or शून्य अगर sleep functionality should be disabled. */
अटल काष्ठा gpio_desc *mlx90614_probe_wakeup(काष्ठा i2c_client *client)
अणु
	काष्ठा gpio_desc *gpio;

	अगर (!i2c_check_functionality(client->adapter,
						I2C_FUNC_SMBUS_WRITE_BYTE)) अणु
		dev_info(&client->dev,
			 "i2c adapter does not support SMBUS_WRITE_BYTE, sleep disabled");
		वापस शून्य;
	पूर्ण

	gpio = devm_gpiod_get_optional(&client->dev, "wakeup", GPIOD_IN);

	अगर (IS_ERR(gpio)) अणु
		dev_warn(&client->dev,
			 "gpio acquisition failed with error %ld, sleep disabled",
			 PTR_ERR(gpio));
		वापस शून्य;
	पूर्ण अन्यथा अगर (!gpio) अणु
		dev_info(&client->dev,
			 "wakeup-gpio not found, sleep disabled");
	पूर्ण

	वापस gpio;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक mlx90614_sleep(काष्ठा mlx90614_data *data)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत पूर्णांक mlx90614_wakeup(काष्ठा mlx90614_data *data)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत काष्ठा gpio_desc *mlx90614_probe_wakeup(काष्ठा i2c_client *client)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

/* Return 0 क्रम single sensor, 1 क्रम dual sensor, <0 on error. */
अटल पूर्णांक mlx90614_probe_num_ir_sensors(काष्ठा i2c_client *client)
अणु
	s32 ret;

	ret = i2c_smbus_पढ़ो_word_data(client, MLX90614_CONFIG);

	अगर (ret < 0)
		वापस ret;

	वापस (ret & MLX90614_CONFIG_DUAL_MASK) ? 1 : 0;
पूर्ण

अटल पूर्णांक mlx90614_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा mlx90614_data *data;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_WORD_DATA))
		वापस -EOPNOTSUPP;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	mutex_init(&data->lock);
	data->wakeup_gpio = mlx90614_probe_wakeup(client);

	mlx90614_wakeup(data);

	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &mlx90614_info;

	ret = mlx90614_probe_num_ir_sensors(client);
	चयन (ret) अणु
	हाल 0:
		dev_dbg(&client->dev, "Found single sensor");
		indio_dev->channels = mlx90614_channels;
		indio_dev->num_channels = 2;
		अवरोध;
	हाल 1:
		dev_dbg(&client->dev, "Found dual sensor");
		indio_dev->channels = mlx90614_channels;
		indio_dev->num_channels = 3;
		अवरोध;
	शेष:
		वापस ret;
	पूर्ण

	अगर (data->wakeup_gpio) अणु
		pm_runसमय_set_स्वतःsuspend_delay(&client->dev,
						 MLX90614_AUTOSLEEP_DELAY);
		pm_runसमय_use_स्वतःsuspend(&client->dev);
		pm_runसमय_set_active(&client->dev);
		pm_runसमय_enable(&client->dev);
	पूर्ण

	वापस iio_device_रेजिस्टर(indio_dev);
पूर्ण

अटल पूर्णांक mlx90614_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा mlx90614_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	अगर (data->wakeup_gpio) अणु
		pm_runसमय_disable(&client->dev);
		अगर (!pm_runसमय_status_suspended(&client->dev))
			mlx90614_sleep(data);
		pm_runसमय_set_suspended(&client->dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mlx90614_id[] = अणु
	अणु "mlx90614", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mlx90614_id);

अटल स्थिर काष्ठा of_device_id mlx90614_of_match[] = अणु
	अणु .compatible = "melexis,mlx90614" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mlx90614_of_match);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mlx90614_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा mlx90614_data *data = iio_priv(indio_dev);

	अगर (data->wakeup_gpio && pm_runसमय_active(dev))
		वापस mlx90614_sleep(data);

	वापस 0;
पूर्ण

अटल पूर्णांक mlx90614_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा mlx90614_data *data = iio_priv(indio_dev);
	पूर्णांक err;

	अगर (data->wakeup_gpio) अणु
		err = mlx90614_wakeup(data);
		अगर (err < 0)
			वापस err;

		pm_runसमय_disable(dev);
		pm_runसमय_set_active(dev);
		pm_runसमय_enable(dev);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mlx90614_pm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा mlx90614_data *data = iio_priv(indio_dev);

	वापस mlx90614_sleep(data);
पूर्ण

अटल पूर्णांक mlx90614_pm_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा mlx90614_data *data = iio_priv(indio_dev);

	वापस mlx90614_wakeup(data);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops mlx90614_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(mlx90614_pm_suspend, mlx90614_pm_resume)
	SET_RUNTIME_PM_OPS(mlx90614_pm_runसमय_suspend,
			   mlx90614_pm_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा i2c_driver mlx90614_driver = अणु
	.driver = अणु
		.name	= "mlx90614",
		.of_match_table = mlx90614_of_match,
		.pm	= &mlx90614_pm_ops,
	पूर्ण,
	.probe = mlx90614_probe,
	.हटाओ = mlx90614_हटाओ,
	.id_table = mlx90614_id,
पूर्ण;
module_i2c_driver(mlx90614_driver);

MODULE_AUTHOR("Peter Meerwald <pmeerw@pmeerw.net>");
MODULE_AUTHOR("Vianney le Clथऊment de Saint-Marcq <vianney.leclement@essensium.com>");
MODULE_AUTHOR("Crt Mori <cmo@melexis.com>");
MODULE_DESCRIPTION("Melexis MLX90614 contactless IR temperature sensor driver");
MODULE_LICENSE("GPL");
