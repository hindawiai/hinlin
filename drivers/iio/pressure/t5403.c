<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * t5403.c - Support क्रम EPCOS T5403 pressure/temperature sensor
 *
 * Copyright (c) 2014 Peter Meerwald <pmeerw@pmeerw.net>
 *
 * (7-bit I2C slave address 0x77)
 *
 * TODO: end-of-conversion irq
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/delay.h>

#घोषणा T5403_DATA 0xf5 /* data, LSB first, 16 bit */
#घोषणा T5403_CALIB_DATA 0x8e /* 10 calibration coeff., LSB first, 16 bit */
#घोषणा T5403_SLAVE_ADDR 0x88 /* I2C slave address, 0x77 */
#घोषणा T5403_COMMAND 0xf1

/* command bits */
#घोषणा T5403_MODE_SHIFT 3 /* conversion समय: 2, 8, 16, 66 ms */
#घोषणा T5403_PT BIT(1) /* 0 .. pressure, 1 .. temperature measurement */
#घोषणा T5403_SCO BIT(0) /* start conversion */

#घोषणा T5403_MODE_LOW 0
#घोषणा T5403_MODE_STANDARD 1
#घोषणा T5403_MODE_HIGH 2
#घोषणा T5403_MODE_ULTRA_HIGH 3

#घोषणा T5403_I2C_MASK (~BIT(7))
#घोषणा T5403_I2C_ADDR 0x77

अटल स्थिर पूर्णांक t5403_pressure_conv_ms[] = अणु2, 8, 16, 66पूर्ण;

काष्ठा t5403_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	पूर्णांक mode;
	__le16 c[10];
पूर्ण;

#घोषणा T5403_C_U16(i) le16_to_cpu(data->c[(i) - 1])
#घोषणा T5403_C(i) sign_extend32(T5403_C_U16(i), 15)

अटल पूर्णांक t5403_पढ़ो(काष्ठा t5403_data *data, bool pressure)
अणु
	पूर्णांक रुको_समय = 3;  /* wakeup समय in ms */

	पूर्णांक ret = i2c_smbus_ग_लिखो_byte_data(data->client, T5403_COMMAND,
		(pressure ? (data->mode << T5403_MODE_SHIFT) : T5403_PT) |
		T5403_SCO);
	अगर (ret < 0)
		वापस ret;

	रुको_समय += pressure ? t5403_pressure_conv_ms[data->mode] : 2;

	msleep(रुको_समय);

	वापस i2c_smbus_पढ़ो_word_data(data->client, T5403_DATA);
पूर्ण

अटल पूर्णांक t5403_comp_pressure(काष्ठा t5403_data *data, पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक ret;
	s16 t_r;
	u16 p_r;
	s32 S, O, X;

	mutex_lock(&data->lock);

	ret = t5403_पढ़ो(data, false);
	अगर (ret < 0)
		जाओ करोne;
	t_r = ret;

	ret = t5403_पढ़ो(data, true);
	अगर (ret < 0)
		जाओ करोne;
	p_r = ret;

	/* see EPCOS application note */
	S = T5403_C_U16(3) + (s32) T5403_C_U16(4) * t_r / 0x20000 +
		T5403_C(5) * t_r / 0x8000 * t_r / 0x80000 +
		T5403_C(9) * t_r / 0x8000 * t_r / 0x8000 * t_r / 0x10000;

	O = T5403_C(6) * 0x4000 + T5403_C(7) * t_r / 8 +
		T5403_C(8) * t_r / 0x8000 * t_r / 16 +
		T5403_C(9) * t_r / 0x8000 * t_r / 0x10000 * t_r;

	X = (S * p_r + O) / 0x4000;

	X += ((X - 75000) * (X - 75000) / 0x10000 - 9537) *
	    T5403_C(10) / 0x10000;

	*val = X / 1000;
	*val2 = (X % 1000) * 1000;

करोne:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक t5403_comp_temp(काष्ठा t5403_data *data, पूर्णांक *val)
अणु
	पूर्णांक ret;
	s16 t_r;

	mutex_lock(&data->lock);
	ret = t5403_पढ़ो(data, false);
	अगर (ret < 0)
		जाओ करोne;
	t_r = ret;

	/* see EPCOS application note */
	*val = ((s32) T5403_C_U16(1) * t_r / 0x100 +
		(s32) T5403_C_U16(2) * 0x40) * 1000 / 0x10000;

करोne:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक t5403_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			  काष्ठा iio_chan_spec स्थिर *chan,
			  पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा t5403_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (chan->type) अणु
		हाल IIO_PRESSURE:
			ret = t5403_comp_pressure(data, val, val2);
			अगर (ret < 0)
				वापस ret;
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_TEMP:
			ret = t5403_comp_temp(data, val);
			अगर (ret < 0)
				वापस ret;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
	    पूर्ण
	हाल IIO_CHAN_INFO_INT_TIME:
		*val = 0;
		*val2 = t5403_pressure_conv_ms[data->mode] * 1000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक t5403_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा t5403_data *data = iio_priv(indio_dev);
	पूर्णांक i;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_INT_TIME:
		अगर (val != 0)
			वापस -EINVAL;
		क्रम (i = 0; i < ARRAY_SIZE(t5403_pressure_conv_ms); i++)
			अगर (val2 == t5403_pressure_conv_ms[i] * 1000) अणु
				mutex_lock(&data->lock);
				data->mode = i;
				mutex_unlock(&data->lock);
				वापस 0;
			पूर्ण
		वापस -EINVAL;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec t5403_channels[] = अणु
	अणु
		.type = IIO_PRESSURE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED) |
		    BIT(IIO_CHAN_INFO_INT_TIME),
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
	पूर्ण,
पूर्ण;

अटल IIO_CONST_ATTR_INT_TIME_AVAIL("0.002 0.008 0.016 0.066");

अटल काष्ठा attribute *t5403_attributes[] = अणु
	&iio_स्थिर_attr_पूर्णांकegration_समय_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group t5403_attribute_group = अणु
	.attrs = t5403_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info t5403_info = अणु
	.पढ़ो_raw = &t5403_पढ़ो_raw,
	.ग_लिखो_raw = &t5403_ग_लिखो_raw,
	.attrs = &t5403_attribute_group,
पूर्ण;

अटल पूर्णांक t5403_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा t5403_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_WORD_DATA |
	    I2C_FUNC_SMBUS_I2C_BLOCK))
		वापस -EOPNOTSUPP;

	ret = i2c_smbus_पढ़ो_byte_data(client, T5403_SLAVE_ADDR);
	अगर (ret < 0)
		वापस ret;
	अगर ((ret & T5403_I2C_MASK) != T5403_I2C_ADDR)
		वापस -ENODEV;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	data->client = client;
	mutex_init(&data->lock);

	i2c_set_clientdata(client, indio_dev);
	indio_dev->info = &t5403_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = t5403_channels;
	indio_dev->num_channels = ARRAY_SIZE(t5403_channels);

	data->mode = T5403_MODE_STANDARD;

	ret = i2c_smbus_पढ़ो_i2c_block_data(data->client, T5403_CALIB_DATA,
	    माप(data->c), (u8 *) data->c);
	अगर (ret < 0)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id t5403_id[] = अणु
	अणु "t5403", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, t5403_id);

अटल काष्ठा i2c_driver t5403_driver = अणु
	.driver = अणु
		.name	= "t5403",
	पूर्ण,
	.probe = t5403_probe,
	.id_table = t5403_id,
पूर्ण;
module_i2c_driver(t5403_driver);

MODULE_AUTHOR("Peter Meerwald <pmeerw@pmeerw.net>");
MODULE_DESCRIPTION("EPCOS T5403 pressure/temperature sensor driver");
MODULE_LICENSE("GPL");
