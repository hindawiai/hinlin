<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ROHM BH1710/BH1715/BH1721/BH1750/BH1751 ambient light sensor driver
 *
 * Copyright (c) Tomasz Duszynski <tduszyns@gmail.com>
 *
 * Data sheets:
 *  http://rohmfs.rohm.com/en/products/databook/datasheet/ic/sensor/light/bh1710fvc-e.pdf
 *  http://rohmfs.rohm.com/en/products/databook/datasheet/ic/sensor/light/bh1715fvc-e.pdf
 *  http://rohmfs.rohm.com/en/products/databook/datasheet/ic/sensor/light/bh1721fvc-e.pdf
 *  http://rohmfs.rohm.com/en/products/databook/datasheet/ic/sensor/light/bh1750fvi-e.pdf
 *  http://rohmfs.rohm.com/en/products/databook/datasheet/ic/sensor/light/bh1751fvi-e.pdf
 *
 * 7-bit I2C slave addresses:
 *  0x23 (ADDR pin low)
 *  0x5C (ADDR pin high)
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/module.h>

#घोषणा BH1750_POWER_DOWN		0x00
#घोषणा BH1750_ONE_TIME_H_RES_MODE	0x20 /* स्वतः-mode क्रम BH1721 */
#घोषणा BH1750_CHANGE_INT_TIME_H_BIT	0x40
#घोषणा BH1750_CHANGE_INT_TIME_L_BIT	0x60

क्रमागत अणु
	BH1710,
	BH1721,
	BH1750,
पूर्ण;

काष्ठा bh1750_chip_info;
काष्ठा bh1750_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	स्थिर काष्ठा bh1750_chip_info *chip_info;
	u16 mtreg;
पूर्ण;

काष्ठा bh1750_chip_info अणु
	u16 mtreg_min;
	u16 mtreg_max;
	u16 mtreg_शेष;
	पूर्णांक mtreg_to_usec;
	पूर्णांक mtreg_to_scale;

	/*
	 * For BH1710/BH1721 all possible पूर्णांकegration समय values won't fit
	 * पूर्णांकo one page so displaying is limited to every second one.
	 * Note, that user can still ग_लिखो proper values which were not
	 * listed.
	 */
	पूर्णांक inc;

	u16 पूर्णांक_समय_low_mask;
	u16 पूर्णांक_समय_high_mask;
पूर्ण;

अटल स्थिर काष्ठा bh1750_chip_info bh1750_chip_info_tbl[] = अणु
	[BH1710] = अणु 140, 1022, 300, 400,  250000000, 2, 0x001F, 0x03E0 पूर्ण,
	[BH1721] = अणु 140, 1020, 300, 400,  250000000, 2, 0x0010, 0x03E0 पूर्ण,
	[BH1750] = अणु 31,  254,  69,  1740, 57500000,  1, 0x001F, 0x00E0 पूर्ण,
पूर्ण;

अटल पूर्णांक bh1750_change_पूर्णांक_समय(काष्ठा bh1750_data *data, पूर्णांक usec)
अणु
	पूर्णांक ret;
	u16 val;
	u8 regval;
	स्थिर काष्ठा bh1750_chip_info *chip_info = data->chip_info;

	अगर ((usec % chip_info->mtreg_to_usec) != 0)
		वापस -EINVAL;

	val = usec / chip_info->mtreg_to_usec;
	अगर (val < chip_info->mtreg_min || val > chip_info->mtreg_max)
		वापस -EINVAL;

	ret = i2c_smbus_ग_लिखो_byte(data->client, BH1750_POWER_DOWN);
	अगर (ret < 0)
		वापस ret;

	regval = (val & chip_info->पूर्णांक_समय_high_mask) >> 5;
	ret = i2c_smbus_ग_लिखो_byte(data->client,
				   BH1750_CHANGE_INT_TIME_H_BIT | regval);
	अगर (ret < 0)
		वापस ret;

	regval = val & chip_info->पूर्णांक_समय_low_mask;
	ret = i2c_smbus_ग_लिखो_byte(data->client,
				   BH1750_CHANGE_INT_TIME_L_BIT | regval);
	अगर (ret < 0)
		वापस ret;

	data->mtreg = val;

	वापस 0;
पूर्ण

अटल पूर्णांक bh1750_पढ़ो(काष्ठा bh1750_data *data, पूर्णांक *val)
अणु
	पूर्णांक ret;
	__be16 result;
	स्थिर काष्ठा bh1750_chip_info *chip_info = data->chip_info;
	अचिन्हित दीर्घ delay = chip_info->mtreg_to_usec * data->mtreg;

	/*
	 * BH1721 will enter continuous mode on receiving this command.
	 * Note, that this eliminates need क्रम bh1750_resume().
	 */
	ret = i2c_smbus_ग_लिखो_byte(data->client, BH1750_ONE_TIME_H_RES_MODE);
	अगर (ret < 0)
		वापस ret;

	usleep_range(delay + 15000, delay + 40000);

	ret = i2c_master_recv(data->client, (अक्षर *)&result, 2);
	अगर (ret < 0)
		वापस ret;

	*val = be16_to_cpu(result);

	वापस 0;
पूर्ण

अटल पूर्णांक bh1750_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret, पंचांगp;
	काष्ठा bh1750_data *data = iio_priv(indio_dev);
	स्थिर काष्ठा bh1750_chip_info *chip_info = data->chip_info;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			mutex_lock(&data->lock);
			ret = bh1750_पढ़ो(data, val);
			mutex_unlock(&data->lock);
			अगर (ret < 0)
				वापस ret;

			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		पंचांगp = chip_info->mtreg_to_scale / data->mtreg;
		*val = पंचांगp / 1000000;
		*val2 = पंचांगp % 1000000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_INT_TIME:
		*val = 0;
		*val2 = chip_info->mtreg_to_usec * data->mtreg;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक bh1750_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	काष्ठा bh1750_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_INT_TIME:
		अगर (val != 0)
			वापस -EINVAL;

		mutex_lock(&data->lock);
		ret = bh1750_change_पूर्णांक_समय(data, val2);
		mutex_unlock(&data->lock);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार bh1750_show_पूर्णांक_समय_available(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक i;
	माप_प्रकार len = 0;
	काष्ठा bh1750_data *data = iio_priv(dev_to_iio_dev(dev));
	स्थिर काष्ठा bh1750_chip_info *chip_info = data->chip_info;

	क्रम (i = chip_info->mtreg_min; i <= chip_info->mtreg_max; i += chip_info->inc)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "0.%06d ",
				 chip_info->mtreg_to_usec * i);

	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल IIO_DEV_ATTR_INT_TIME_AVAIL(bh1750_show_पूर्णांक_समय_available);

अटल काष्ठा attribute *bh1750_attributes[] = अणु
	&iio_dev_attr_पूर्णांकegration_समय_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group bh1750_attribute_group = अणु
	.attrs = bh1750_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info bh1750_info = अणु
	.attrs = &bh1750_attribute_group,
	.पढ़ो_raw = bh1750_पढ़ो_raw,
	.ग_लिखो_raw = bh1750_ग_लिखो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec bh1750_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE) |
				      BIT(IIO_CHAN_INFO_INT_TIME)
	पूर्ण
पूर्ण;

अटल पूर्णांक bh1750_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret, usec;
	काष्ठा bh1750_data *data;
	काष्ठा iio_dev *indio_dev;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C |
				I2C_FUNC_SMBUS_WRITE_BYTE))
		वापस -EOPNOTSUPP;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	data->chip_info = &bh1750_chip_info_tbl[id->driver_data];

	usec = data->chip_info->mtreg_to_usec * data->chip_info->mtreg_शेष;
	ret = bh1750_change_पूर्णांक_समय(data, usec);
	अगर (ret < 0)
		वापस ret;

	mutex_init(&data->lock);
	indio_dev->info = &bh1750_info;
	indio_dev->name = id->name;
	indio_dev->channels = bh1750_channels;
	indio_dev->num_channels = ARRAY_SIZE(bh1750_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	वापस iio_device_रेजिस्टर(indio_dev);
पूर्ण

अटल पूर्णांक bh1750_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा bh1750_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	mutex_lock(&data->lock);
	i2c_smbus_ग_लिखो_byte(client, BH1750_POWER_DOWN);
	mutex_unlock(&data->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused bh1750_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा bh1750_data *data =
		iio_priv(i2c_get_clientdata(to_i2c_client(dev)));

	/*
	 * This is मुख्यly क्रम BH1721 which करोesn't enter घातer करोwn
	 * mode स्वतःmatically.
	 */
	mutex_lock(&data->lock);
	ret = i2c_smbus_ग_लिखो_byte(data->client, BH1750_POWER_DOWN);
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(bh1750_pm_ops, bh1750_suspend, शून्य);

अटल स्थिर काष्ठा i2c_device_id bh1750_id[] = अणु
	अणु "bh1710", BH1710 पूर्ण,
	अणु "bh1715", BH1750 पूर्ण,
	अणु "bh1721", BH1721 पूर्ण,
	अणु "bh1750", BH1750 पूर्ण,
	अणु "bh1751", BH1750 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bh1750_id);

अटल स्थिर काष्ठा of_device_id bh1750_of_match[] = अणु
	अणु .compatible = "rohm,bh1710", पूर्ण,
	अणु .compatible = "rohm,bh1715", पूर्ण,
	अणु .compatible = "rohm,bh1721", पूर्ण,
	अणु .compatible = "rohm,bh1750", पूर्ण,
	अणु .compatible = "rohm,bh1751", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bh1750_of_match);

अटल काष्ठा i2c_driver bh1750_driver = अणु
	.driver = अणु
		.name = "bh1750",
		.of_match_table = bh1750_of_match,
		.pm = &bh1750_pm_ops,
	पूर्ण,
	.probe = bh1750_probe,
	.हटाओ = bh1750_हटाओ,
	.id_table = bh1750_id,

पूर्ण;
module_i2c_driver(bh1750_driver);

MODULE_AUTHOR("Tomasz Duszynski <tduszyns@gmail.com>");
MODULE_DESCRIPTION("ROHM BH1710/BH1715/BH1721/BH1750/BH1751 als driver");
MODULE_LICENSE("GPL v2");
