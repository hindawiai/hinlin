<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * srf08.c - Support क्रम Devantech SRFxx ultrasonic ranger
 *           with i2c पूर्णांकerface
 * actually supported are srf02, srf08, srf10
 *
 * Copyright (c) 2016, 2017 Andreas Klinger <ak@it-klinger.de>
 *
 * For details about the device see:
 * https://www.robot-electronics.co.uk/hपंचांग/srf08tech.hपंचांगl
 * https://www.robot-electronics.co.uk/hपंचांग/srf10tech.hपंचांग
 * https://www.robot-electronics.co.uk/hपंचांग/srf02tech.hपंचांग
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

/* रेजिस्टरs of SRF08 device */
#घोषणा SRF08_WRITE_COMMAND	0x00	/* Command Register */
#घोषणा SRF08_WRITE_MAX_GAIN	0x01	/* Max Gain Register: 0 .. 31 */
#घोषणा SRF08_WRITE_RANGE	0x02	/* Range Register: 0 .. 255 */
#घोषणा SRF08_READ_SW_REVISION	0x00	/* Software Revision */
#घोषणा SRF08_READ_LIGHT	0x01	/* Light Sensor during last echo */
#घोषणा SRF08_READ_ECHO_1_HIGH	0x02	/* Range of first echo received */
#घोषणा SRF08_READ_ECHO_1_LOW	0x03	/* Range of first echo received */

#घोषणा SRF08_CMD_RANGING_CM	0x51	/* Ranging Mode - Result in cm */

क्रमागत srf08_sensor_type अणु
	SRF02,
	SRF08,
	SRF10,
	SRF_MAX_TYPE
पूर्ण;

काष्ठा srf08_chip_info अणु
	स्थिर पूर्णांक		*sensitivity_avail;
	पूर्णांक			num_sensitivity_avail;
	पूर्णांक			sensitivity_शेष;

	/* शेष value of Range in mm */
	पूर्णांक			range_शेष;
पूर्ण;

काष्ठा srf08_data अणु
	काष्ठा i2c_client	*client;

	/*
	 * Gain in the datasheet is called sensitivity here to distinct it
	 * from the gain used with amplअगरiers of adc's
	 */
	पूर्णांक			sensitivity;

	/* max. Range in mm */
	पूर्णांक			range_mm;
	काष्ठा mutex		lock;

	/*
	 * triggered buffer
	 * 1x16-bit channel + 3x16 padding + 4x16 बारtamp
	 */
	s16			buffer[8];

	/* Sensor-Type */
	क्रमागत srf08_sensor_type	sensor_type;

	/* Chip-specअगरic inक्रमmation */
	स्थिर काष्ठा srf08_chip_info	*chip_info;
पूर्ण;

/*
 * in the करोcumentation one can पढ़ो about the "Gain" of the device
 * which is used here क्रम amplअगरying the संकेत and filtering out unwanted
 * ones.
 * But with ADC's this term is already used differently and that's why it
 * is called "Sensitivity" here.
 */
अटल स्थिर काष्ठा srf08_chip_info srf02_chip_info = अणु
	.sensitivity_avail	= शून्य,
	.num_sensitivity_avail	= 0,
	.sensitivity_शेष	= 0,

	.range_शेष		= 0,
पूर्ण;

अटल स्थिर पूर्णांक srf08_sensitivity_avail[] = अणु
	 94,  97, 100, 103, 107, 110, 114, 118,
	123, 128, 133, 139, 145, 152, 159, 168,
	177, 187, 199, 212, 227, 245, 265, 288,
	317, 352, 395, 450, 524, 626, 777, 1025
	पूर्ण;

अटल स्थिर काष्ठा srf08_chip_info srf08_chip_info = अणु
	.sensitivity_avail	= srf08_sensitivity_avail,
	.num_sensitivity_avail	= ARRAY_SIZE(srf08_sensitivity_avail),
	.sensitivity_शेष	= 1025,

	.range_शेष		= 6020,
पूर्ण;

अटल स्थिर पूर्णांक srf10_sensitivity_avail[] = अणु
	 40,  40,  50,  60,  70,  80, 100, 120,
	140, 200, 250, 300, 350, 400, 500, 600,
	700,
	पूर्ण;

अटल स्थिर काष्ठा srf08_chip_info srf10_chip_info = अणु
	.sensitivity_avail	= srf10_sensitivity_avail,
	.num_sensitivity_avail	= ARRAY_SIZE(srf10_sensitivity_avail),
	.sensitivity_शेष	= 700,

	.range_शेष		= 6020,
पूर्ण;

अटल पूर्णांक srf08_पढ़ो_ranging(काष्ठा srf08_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret, i;
	पूर्णांक रुकोसमय;

	mutex_lock(&data->lock);

	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
			SRF08_WRITE_COMMAND, SRF08_CMD_RANGING_CM);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "write command - err: %d\n", ret);
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण

	/*
	 * we पढ़ो here until a correct version number shows up as
	 * suggested by the करोcumentation
	 *
	 * with an ultrasonic speed of 343 m/s and a roundtrip of it
	 * sleep the expected duration and try to पढ़ो from the device
	 * अगर nothing useful is पढ़ो try it in a लघुer grid
	 *
	 * polling क्रम not more than 20 ms should be enough
	 */
	रुकोसमय = 1 + data->range_mm / 172;
	msleep(रुकोसमय);
	क्रम (i = 0; i < 4; i++) अणु
		ret = i2c_smbus_पढ़ो_byte_data(data->client,
						SRF08_READ_SW_REVISION);

		/* check अगर a valid version number is पढ़ो */
		अगर (ret < 255 && ret > 0)
			अवरोध;
		msleep(5);
	पूर्ण

	अगर (ret >= 255 || ret <= 0) अणु
		dev_err(&client->dev, "device not ready\n");
		mutex_unlock(&data->lock);
		वापस -EIO;
	पूर्ण

	ret = i2c_smbus_पढ़ो_word_swapped(data->client,
						SRF08_READ_ECHO_1_HIGH);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "cannot read distance: ret=%d\n", ret);
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण

	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल irqवापस_t srf08_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा srf08_data *data = iio_priv(indio_dev);
	s16 sensor_data;

	sensor_data = srf08_पढ़ो_ranging(data);
	अगर (sensor_data < 0)
		जाओ err;

	mutex_lock(&data->lock);

	data->buffer[0] = sensor_data;
	iio_push_to_buffers_with_बारtamp(indio_dev,
						data->buffer, pf->बारtamp);

	mutex_unlock(&data->lock);
err:
	iio_trigger_notअगरy_करोne(indio_dev->trig);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक srf08_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *val,
			    पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा srf08_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (channel->type != IIO_DISTANCE)
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = srf08_पढ़ो_ranging(data);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		/* 1 LSB is 1 cm */
		*val = 0;
		*val2 = 10000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार srf08_show_range_mm_available(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "[0.043 0.043 11.008]\n");
पूर्ण

अटल IIO_DEVICE_ATTR(sensor_max_range_available, S_IRUGO,
				srf08_show_range_mm_available, शून्य, 0);

अटल sमाप_प्रकार srf08_show_range_mm(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा srf08_data *data = iio_priv(indio_dev);

	वापस प्र_लिखो(buf, "%d.%03d\n", data->range_mm / 1000,
						data->range_mm % 1000);
पूर्ण

/*
 * set the range of the sensor to an even multiple of 43 mm
 * which corresponds to 1 LSB in the रेजिस्टर
 *
 * रेजिस्टर value    corresponding range
 *         0x00             43 mm
 *         0x01             86 mm
 *         0x02            129 mm
 *         ...
 *         0xFF          11008 mm
 */
अटल sमाप_प्रकार srf08_ग_लिखो_range_mm(काष्ठा srf08_data *data, अचिन्हित पूर्णांक val)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = data->client;
	अचिन्हित पूर्णांक mod;
	u8 regval;

	ret = val / 43 - 1;
	mod = val % 43;

	अगर (mod || (ret < 0) || (ret > 255))
		वापस -EINVAL;

	regval = ret;

	mutex_lock(&data->lock);

	ret = i2c_smbus_ग_लिखो_byte_data(client, SRF08_WRITE_RANGE, regval);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "write_range - err: %d\n", ret);
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण

	data->range_mm = val;

	mutex_unlock(&data->lock);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार srf08_store_range_mm(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा srf08_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	पूर्णांक पूर्णांकeger, fract;

	ret = iio_str_to_fixpoपूर्णांक(buf, 100, &पूर्णांकeger, &fract);
	अगर (ret)
		वापस ret;

	ret = srf08_ग_लिखो_range_mm(data, पूर्णांकeger * 1000 + fract);
	अगर (ret < 0)
		वापस ret;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(sensor_max_range, S_IRUGO | S_IWUSR,
			srf08_show_range_mm, srf08_store_range_mm, 0);

अटल sमाप_प्रकार srf08_show_sensitivity_available(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक i, len = 0;
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा srf08_data *data = iio_priv(indio_dev);

	क्रम (i = 0; i < data->chip_info->num_sensitivity_avail; i++)
		अगर (data->chip_info->sensitivity_avail[i])
			len += प्र_लिखो(buf + len, "%d ",
				data->chip_info->sensitivity_avail[i]);

	len += प्र_लिखो(buf + len, "\n");

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(sensor_sensitivity_available, S_IRUGO,
				srf08_show_sensitivity_available, शून्य, 0);

अटल sमाप_प्रकार srf08_show_sensitivity(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा srf08_data *data = iio_priv(indio_dev);
	पूर्णांक len;

	len = प्र_लिखो(buf, "%d\n", data->sensitivity);

	वापस len;
पूर्ण

अटल sमाप_प्रकार srf08_ग_लिखो_sensitivity(काष्ठा srf08_data *data,
							अचिन्हित पूर्णांक val)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret, i;
	u8 regval;

	अगर (!val)
		वापस -EINVAL;

	क्रम (i = 0; i < data->chip_info->num_sensitivity_avail; i++)
		अगर (val && (val == data->chip_info->sensitivity_avail[i])) अणु
			regval = i;
			अवरोध;
		पूर्ण

	अगर (i >= data->chip_info->num_sensitivity_avail)
		वापस -EINVAL;

	mutex_lock(&data->lock);

	ret = i2c_smbus_ग_लिखो_byte_data(client, SRF08_WRITE_MAX_GAIN, regval);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "write_sensitivity - err: %d\n", ret);
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण

	data->sensitivity = val;

	mutex_unlock(&data->lock);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार srf08_store_sensitivity(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा srf08_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = kstrtouपूर्णांक(buf, 10, &val);
	अगर (ret)
		वापस ret;

	ret = srf08_ग_लिखो_sensitivity(data, val);
	अगर (ret < 0)
		वापस ret;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(sensor_sensitivity, S_IRUGO | S_IWUSR,
			srf08_show_sensitivity, srf08_store_sensitivity, 0);

अटल काष्ठा attribute *srf08_attributes[] = अणु
	&iio_dev_attr_sensor_max_range.dev_attr.attr,
	&iio_dev_attr_sensor_max_range_available.dev_attr.attr,
	&iio_dev_attr_sensor_sensitivity.dev_attr.attr,
	&iio_dev_attr_sensor_sensitivity_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group srf08_attribute_group = अणु
	.attrs = srf08_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec srf08_channels[] = अणु
	अणु
		.type = IIO_DISTANCE,
		.info_mask_separate =
				BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 's',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_CPU,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(1),
पूर्ण;

अटल स्थिर काष्ठा iio_info srf08_info = अणु
	.पढ़ो_raw = srf08_पढ़ो_raw,
	.attrs = &srf08_attribute_group,
पूर्ण;

/*
 * srf02 करोn't have an adjustable range or sensitivity,
 * so we करोn't need attributes at all
 */
अटल स्थिर काष्ठा iio_info srf02_info = अणु
	.पढ़ो_raw = srf08_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक srf08_probe(काष्ठा i2c_client *client,
					 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा srf08_data *data;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter,
					I2C_FUNC_SMBUS_READ_BYTE_DATA |
					I2C_FUNC_SMBUS_WRITE_BYTE_DATA |
					I2C_FUNC_SMBUS_READ_WORD_DATA))
		वापस -ENODEV;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	data->sensor_type = (क्रमागत srf08_sensor_type)id->driver_data;

	चयन (data->sensor_type) अणु
	हाल SRF02:
		data->chip_info = &srf02_chip_info;
		indio_dev->info = &srf02_info;
		अवरोध;
	हाल SRF08:
		data->chip_info = &srf08_chip_info;
		indio_dev->info = &srf08_info;
		अवरोध;
	हाल SRF10:
		data->chip_info = &srf10_chip_info;
		indio_dev->info = &srf08_info;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = srf08_channels;
	indio_dev->num_channels = ARRAY_SIZE(srf08_channels);

	mutex_init(&data->lock);

	ret = devm_iio_triggered_buffer_setup(&client->dev, indio_dev,
			iio_pollfunc_store_समय, srf08_trigger_handler, शून्य);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "setup of iio triggered buffer failed\n");
		वापस ret;
	पूर्ण

	अगर (data->chip_info->range_शेष) अणु
		/*
		 * set शेष range of device in mm here
		 * these रेजिस्टर values cannot be पढ़ो from the hardware
		 * thereक्रमe set driver specअगरic शेष values
		 *
		 * srf02 करोn't have a default value so it'll be omitted
		 */
		ret = srf08_ग_लिखो_range_mm(data,
					data->chip_info->range_शेष);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (data->chip_info->sensitivity_शेष) अणु
		/*
		 * set शेष sensitivity of device here
		 * these रेजिस्टर values cannot be पढ़ो from the hardware
		 * thereक्रमe set driver specअगरic शेष values
		 *
		 * srf02 करोn't have a default value so it'll be omitted
		 */
		ret = srf08_ग_लिखो_sensitivity(data,
				data->chip_info->sensitivity_शेष);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id of_srf08_match[] = अणु
	अणु .compatible = "devantech,srf02", (व्योम *)SRF02पूर्ण,
	अणु .compatible = "devantech,srf08", (व्योम *)SRF08पूर्ण,
	अणु .compatible = "devantech,srf10", (व्योम *)SRF10पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, of_srf08_match);

अटल स्थिर काष्ठा i2c_device_id srf08_id[] = अणु
	अणु "srf02", SRF02 पूर्ण,
	अणु "srf08", SRF08 पूर्ण,
	अणु "srf10", SRF10 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, srf08_id);

अटल काष्ठा i2c_driver srf08_driver = अणु
	.driver = अणु
		.name	= "srf08",
		.of_match_table	= of_srf08_match,
	पूर्ण,
	.probe = srf08_probe,
	.id_table = srf08_id,
पूर्ण;
module_i2c_driver(srf08_driver);

MODULE_AUTHOR("Andreas Klinger <ak@it-klinger.de>");
MODULE_DESCRIPTION("Devantech SRF02/SRF08/SRF10 i2c ultrasonic ranger driver");
MODULE_LICENSE("GPL");
