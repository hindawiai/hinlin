<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * vz89x.c - Support क्रम SGX Sensortech MiCS VZ89X VOC sensors
 *
 * Copyright (C) 2015-2018
 * Author: Matt Ranostay <matt.ranostay@konsulko.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mod_devicetable.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा VZ89X_REG_MEASUREMENT		0x09
#घोषणा VZ89X_REG_MEASUREMENT_RD_SIZE	6
#घोषणा VZ89X_REG_MEASUREMENT_WR_SIZE	3

#घोषणा VZ89X_VOC_CO2_IDX		0
#घोषणा VZ89X_VOC_SHORT_IDX		1
#घोषणा VZ89X_VOC_TVOC_IDX		2
#घोषणा VZ89X_VOC_RESISTANCE_IDX	3

#घोषणा VZ89TE_REG_MEASUREMENT		0x0c
#घोषणा VZ89TE_REG_MEASUREMENT_RD_SIZE	7
#घोषणा VZ89TE_REG_MEASUREMENT_WR_SIZE	6

#घोषणा VZ89TE_VOC_TVOC_IDX		0
#घोषणा VZ89TE_VOC_CO2_IDX		1
#घोषणा VZ89TE_VOC_RESISTANCE_IDX	2

क्रमागत अणु
	VZ89X,
	VZ89TE,
पूर्ण;

काष्ठा vz89x_chip_data;

काष्ठा vz89x_data अणु
	काष्ठा i2c_client *client;
	स्थिर काष्ठा vz89x_chip_data *chip;
	काष्ठा mutex lock;
	पूर्णांक (*xfer)(काष्ठा vz89x_data *data, u8 cmd);

	bool is_valid;
	अचिन्हित दीर्घ last_update;
	u8 buffer[VZ89TE_REG_MEASUREMENT_RD_SIZE];
पूर्ण;

काष्ठा vz89x_chip_data अणु
	bool (*valid)(काष्ठा vz89x_data *data);
	स्थिर काष्ठा iio_chan_spec *channels;
	u8 num_channels;

	u8 cmd;
	u8 पढ़ो_size;
	u8 ग_लिखो_size;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec vz89x_channels[] = अणु
	अणु
		.type = IIO_CONCENTRATION,
		.channel2 = IIO_MOD_CO2,
		.modअगरied = 1,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_RAW),
		.address = VZ89X_VOC_CO2_IDX,
	पूर्ण,
	अणु
		.type = IIO_CONCENTRATION,
		.channel2 = IIO_MOD_VOC,
		.modअगरied = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.address = VZ89X_VOC_SHORT_IDX,
		.extend_name = "short",
	पूर्ण,
	अणु
		.type = IIO_CONCENTRATION,
		.channel2 = IIO_MOD_VOC,
		.modअगरied = 1,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_RAW),
		.address = VZ89X_VOC_TVOC_IDX,
	पूर्ण,
	अणु
		.type = IIO_RESISTANCE,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
		.address = VZ89X_VOC_RESISTANCE_IDX,
		.scan_index = -1,
		.scan_type = अणु
			.endianness = IIO_LE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec vz89te_channels[] = अणु
	अणु
		.type = IIO_CONCENTRATION,
		.channel2 = IIO_MOD_VOC,
		.modअगरied = 1,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_RAW),
		.address = VZ89TE_VOC_TVOC_IDX,
	पूर्ण,

	अणु
		.type = IIO_CONCENTRATION,
		.channel2 = IIO_MOD_CO2,
		.modअगरied = 1,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_OFFSET) | BIT(IIO_CHAN_INFO_RAW),
		.address = VZ89TE_VOC_CO2_IDX,
	पूर्ण,
	अणु
		.type = IIO_RESISTANCE,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
		.address = VZ89TE_VOC_RESISTANCE_IDX,
		.scan_index = -1,
		.scan_type = अणु
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल IIO_CONST_ATTR(in_concentration_co2_scale, "0.00000698689");
अटल IIO_CONST_ATTR(in_concentration_voc_scale, "0.00000000436681223");

अटल काष्ठा attribute *vz89x_attributes[] = अणु
	&iio_स्थिर_attr_in_concentration_co2_scale.dev_attr.attr,
	&iio_स्थिर_attr_in_concentration_voc_scale.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group vz89x_attrs_group = अणु
	.attrs = vz89x_attributes,
पूर्ण;

/*
 * Chipset someसमय updates in the middle of a पढ़ोing causing it to reset the
 * data poपूर्णांकer, and causing invalid पढ़ोing of previous data.
 * We can check क्रम this by पढ़ोing MSB of the resistance पढ़ोing that is
 * always zero, and by also confirming the VOC_लघु isn't zero.
 */

अटल bool vz89x_measurement_is_valid(काष्ठा vz89x_data *data)
अणु
	अगर (data->buffer[VZ89X_VOC_SHORT_IDX] == 0)
		वापस true;

	वापस !!(data->buffer[data->chip->पढ़ो_size - 1] > 0);
पूर्ण

/* VZ89TE device has a modअगरied CRC-8 two complement check */
अटल bool vz89te_measurement_is_valid(काष्ठा vz89x_data *data)
अणु
	u8 crc = 0;
	पूर्णांक i, sum = 0;

	क्रम (i = 0; i < (data->chip->पढ़ो_size - 1); i++) अणु
		sum = crc + data->buffer[i];
		crc = sum;
		crc += sum / 256;
	पूर्ण

	वापस !((0xff - crc) == data->buffer[data->chip->पढ़ो_size - 1]);
पूर्ण

अटल पूर्णांक vz89x_i2c_xfer(काष्ठा vz89x_data *data, u8 cmd)
अणु
	स्थिर काष्ठा vz89x_chip_data *chip = data->chip;
	काष्ठा i2c_client *client = data->client;
	काष्ठा i2c_msg msg[2];
	पूर्णांक ret;
	u8 buf[6] = अणु cmd, 0, 0, 0, 0, 0xf3 पूर्ण;

	msg[0].addr = client->addr;
	msg[0].flags = client->flags;
	msg[0].len = chip->ग_लिखो_size;
	msg[0].buf  = (अक्षर *) &buf;

	msg[1].addr = client->addr;
	msg[1].flags = client->flags | I2C_M_RD;
	msg[1].len = chip->पढ़ो_size;
	msg[1].buf = (अक्षर *) &data->buffer;

	ret = i2c_transfer(client->adapter, msg, 2);

	वापस (ret == 2) ? 0 : ret;
पूर्ण

अटल पूर्णांक vz89x_smbus_xfer(काष्ठा vz89x_data *data, u8 cmd)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret;
	पूर्णांक i;

	ret = i2c_smbus_ग_लिखो_word_data(client, cmd, 0);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < data->chip->पढ़ो_size; i++) अणु
		ret = i2c_smbus_पढ़ो_byte(client);
		अगर (ret < 0)
			वापस ret;
		data->buffer[i] = ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vz89x_get_measurement(काष्ठा vz89x_data *data)
अणु
	स्थिर काष्ठा vz89x_chip_data *chip = data->chip;
	पूर्णांक ret;

	/* sensor can only be polled once a second max per datasheet */
	अगर (!समय_after(jअगरfies, data->last_update + HZ))
		वापस data->is_valid ? 0 : -EAGAIN;

	data->is_valid = false;
	data->last_update = jअगरfies;

	ret = data->xfer(data, chip->cmd);
	अगर (ret < 0)
		वापस ret;

	ret = chip->valid(data);
	अगर (ret)
		वापस -EAGAIN;

	data->is_valid = true;

	वापस 0;
पूर्ण

अटल पूर्णांक vz89x_get_resistance_पढ़ोing(काष्ठा vz89x_data *data,
					काष्ठा iio_chan_spec स्थिर *chan,
					पूर्णांक *val)
अणु
	u8 *पंचांगp = (u8 *) &data->buffer[chan->address];

	चयन (chan->scan_type.endianness) अणु
	हाल IIO_LE:
		*val = le32_to_cpup((__le32 *) पंचांगp) & GENMASK(23, 0);
		अवरोध;
	हाल IIO_BE:
		*val = be32_to_cpup((__be32 *) पंचांगp) >> 8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vz89x_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			  काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			  पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा vz89x_data *data = iio_priv(indio_dev);
	पूर्णांक ret = -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&data->lock);
		ret = vz89x_get_measurement(data);
		mutex_unlock(&data->lock);

		अगर (ret)
			वापस ret;

		चयन (chan->type) अणु
		हाल IIO_CONCENTRATION:
			*val = data->buffer[chan->address];
			वापस IIO_VAL_INT;
		हाल IIO_RESISTANCE:
			ret = vz89x_get_resistance_पढ़ोing(data, chan, val);
			अगर (!ret)
				वापस IIO_VAL_INT;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_RESISTANCE:
			*val = 10;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_OFFSET:
		चयन (chan->channel2) अणु
		हाल IIO_MOD_CO2:
			*val = 44;
			*val2 = 250000;
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_MOD_VOC:
			*val = -13;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info vz89x_info = अणु
	.attrs		= &vz89x_attrs_group,
	.पढ़ो_raw	= vz89x_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा vz89x_chip_data vz89x_chips[] = अणु
	अणु
		.valid = vz89x_measurement_is_valid,

		.cmd = VZ89X_REG_MEASUREMENT,
		.पढ़ो_size = VZ89X_REG_MEASUREMENT_RD_SIZE,
		.ग_लिखो_size = VZ89X_REG_MEASUREMENT_WR_SIZE,

		.channels = vz89x_channels,
		.num_channels = ARRAY_SIZE(vz89x_channels),
	पूर्ण,
	अणु
		.valid = vz89te_measurement_is_valid,

		.cmd = VZ89TE_REG_MEASUREMENT,
		.पढ़ो_size = VZ89TE_REG_MEASUREMENT_RD_SIZE,
		.ग_लिखो_size = VZ89TE_REG_MEASUREMENT_WR_SIZE,

		.channels = vz89te_channels,
		.num_channels = ARRAY_SIZE(vz89te_channels),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id vz89x_dt_ids[] = अणु
	अणु .compatible = "sgx,vz89x", .data = (व्योम *) VZ89X पूर्ण,
	अणु .compatible = "sgx,vz89te", .data = (व्योम *) VZ89TE पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, vz89x_dt_ids);

अटल पूर्णांक vz89x_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा iio_dev *indio_dev;
	काष्ठा vz89x_data *data;
	पूर्णांक chip_id;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;
	data = iio_priv(indio_dev);

	अगर (i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		data->xfer = vz89x_i2c_xfer;
	अन्यथा अगर (i2c_check_functionality(client->adapter,
				I2C_FUNC_SMBUS_WORD_DATA | I2C_FUNC_SMBUS_BYTE))
		data->xfer = vz89x_smbus_xfer;
	अन्यथा
		वापस -EOPNOTSUPP;

	अगर (!dev_fwnode(dev))
		chip_id = id->driver_data;
	अन्यथा
		chip_id = (अचिन्हित दीर्घ)device_get_match_data(dev);

	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	data->chip = &vz89x_chips[chip_id];
	data->last_update = jअगरfies - HZ;
	mutex_init(&data->lock);

	indio_dev->info = &vz89x_info;
	indio_dev->name = dev_name(dev);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	indio_dev->channels = data->chip->channels;
	indio_dev->num_channels = data->chip->num_channels;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id vz89x_id[] = अणु
	अणु "vz89x", VZ89X पूर्ण,
	अणु "vz89te", VZ89TE पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, vz89x_id);

अटल काष्ठा i2c_driver vz89x_driver = अणु
	.driver = अणु
		.name	= "vz89x",
		.of_match_table = vz89x_dt_ids,
	पूर्ण,
	.probe = vz89x_probe,
	.id_table = vz89x_id,
पूर्ण;
module_i2c_driver(vz89x_driver);

MODULE_AUTHOR("Matt Ranostay <matt.ranostay@konsulko.com>");
MODULE_DESCRIPTION("SGX Sensortech MiCS VZ89X VOC sensors");
MODULE_LICENSE("GPL v2");
