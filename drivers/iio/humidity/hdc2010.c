<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * hdc2010.c - Support क्रम the TI HDC2010 and HDC2080
 * temperature + relative humidity sensors
 *
 * Copyright (C) 2020 Norphonic AS
 * Author: Eugene Zaikonnikov <ez@norphonic.com>
 *
 * Datasheet: https://www.ti.com/product/HDC2010/datasheet
 * Datasheet: https://www.ti.com/product/HDC2080/datasheet
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/bitops.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा HDC2010_REG_TEMP_LOW			0x00
#घोषणा HDC2010_REG_TEMP_HIGH			0x01
#घोषणा HDC2010_REG_HUMIDITY_LOW		0x02
#घोषणा HDC2010_REG_HUMIDITY_HIGH		0x03
#घोषणा HDC2010_REG_INTERRUPT_DRDY		0x04
#घोषणा HDC2010_REG_TEMP_MAX			0x05
#घोषणा HDC2010_REG_HUMIDITY_MAX		0x06
#घोषणा HDC2010_REG_INTERRUPT_EN		0x07
#घोषणा HDC2010_REG_TEMP_OFFSET_ADJ		0x08
#घोषणा HDC2010_REG_HUMIDITY_OFFSET_ADJ		0x09
#घोषणा HDC2010_REG_TEMP_THR_L			0x0a
#घोषणा HDC2010_REG_TEMP_THR_H			0x0b
#घोषणा HDC2010_REG_RH_THR_L			0x0c
#घोषणा HDC2010_REG_RH_THR_H			0x0d
#घोषणा HDC2010_REG_RESET_DRDY_INT_CONF		0x0e
#घोषणा HDC2010_REG_MEASUREMENT_CONF		0x0f

#घोषणा HDC2010_MEAS_CONF			GENMASK(2, 1)
#घोषणा HDC2010_MEAS_TRIG			BIT(0)
#घोषणा HDC2010_HEATER_EN			BIT(3)
#घोषणा HDC2010_AMM				GENMASK(6, 4)

काष्ठा hdc2010_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	u8 measurement_config;
	u8 पूर्णांकerrupt_config;
	u8 drdy_config;
पूर्ण;

क्रमागत hdc2010_addr_groups अणु
	HDC2010_GROUP_TEMP = 0,
	HDC2010_GROUP_HUMIDITY,
पूर्ण;

काष्ठा hdc2010_reg_record अणु
	अचिन्हित दीर्घ primary;
	अचिन्हित दीर्घ peak;
पूर्ण;

अटल स्थिर काष्ठा hdc2010_reg_record hdc2010_reg_translation[] = अणु
	[HDC2010_GROUP_TEMP] = अणु
		.primary = HDC2010_REG_TEMP_LOW,
		.peak = HDC2010_REG_TEMP_MAX,
	पूर्ण,
	[HDC2010_GROUP_HUMIDITY] = अणु
		.primary = HDC2010_REG_HUMIDITY_LOW,
		.peak = HDC2010_REG_HUMIDITY_MAX,
	पूर्ण,
पूर्ण;

अटल IIO_CONST_ATTR(out_current_heater_raw_available, "0 1");

अटल काष्ठा attribute *hdc2010_attributes[] = अणु
	&iio_स्थिर_attr_out_current_heater_raw_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group hdc2010_attribute_group = अणु
	.attrs = hdc2010_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec hdc2010_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.address = HDC2010_GROUP_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_PEAK) |
			BIT(IIO_CHAN_INFO_OFFSET) |
			BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
	अणु
		.type = IIO_HUMIDITYRELATIVE,
		.address = HDC2010_GROUP_HUMIDITY,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_PEAK) |
			BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
	अणु
		.type = IIO_CURRENT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.extend_name = "heater",
		.output = 1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक hdc2010_update_drdy_config(काष्ठा hdc2010_data *data,
					     अक्षर mask, अक्षर val)
अणु
	u8 पंचांगp = (~mask & data->drdy_config) | val;
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
					HDC2010_REG_RESET_DRDY_INT_CONF, पंचांगp);
	अगर (ret)
		वापस ret;

	data->drdy_config = पंचांगp;

	वापस 0;
पूर्ण

अटल पूर्णांक hdc2010_get_prim_measurement_word(काष्ठा hdc2010_data *data,
					     काष्ठा iio_chan_spec स्थिर *chan)
अणु
	काष्ठा i2c_client *client = data->client;
	s32 ret;

	ret = i2c_smbus_पढ़ो_word_data(client,
			hdc2010_reg_translation[chan->address].primary);

	अगर (ret < 0)
		dev_err(&client->dev, "Could not read sensor measurement word\n");

	वापस ret;
पूर्ण

अटल पूर्णांक hdc2010_get_peak_measurement_byte(काष्ठा hdc2010_data *data,
					     काष्ठा iio_chan_spec स्थिर *chan)
अणु
	काष्ठा i2c_client *client = data->client;
	s32 ret;

	ret = i2c_smbus_पढ़ो_byte_data(client,
			hdc2010_reg_translation[chan->address].peak);

	अगर (ret < 0)
		dev_err(&client->dev, "Could not read sensor measurement byte\n");

	वापस ret;
पूर्ण

अटल पूर्णांक hdc2010_get_heater_status(काष्ठा hdc2010_data *data)
अणु
	वापस !!(data->drdy_config & HDC2010_HEATER_EN);
पूर्ण

अटल पूर्णांक hdc2010_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			    पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा hdc2010_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW: अणु
		पूर्णांक ret;

		अगर (chan->type == IIO_CURRENT) अणु
			*val = hdc2010_get_heater_status(data);
			वापस IIO_VAL_INT;
		पूर्ण
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		mutex_lock(&data->lock);
		ret = hdc2010_get_prim_measurement_word(data, chan);
		mutex_unlock(&data->lock);
		iio_device_release_direct_mode(indio_dev);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	पूर्ण
	हाल IIO_CHAN_INFO_PEAK: अणु
		पूर्णांक ret;

		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		mutex_lock(&data->lock);
		ret = hdc2010_get_peak_measurement_byte(data, chan);
		mutex_unlock(&data->lock);
		iio_device_release_direct_mode(indio_dev);
		अगर (ret < 0)
			वापस ret;
		/* Scaling up the value so we can use same offset as RAW */
		*val = ret * 256;
		वापस IIO_VAL_INT;
	पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		*val2 = 65536;
		अगर (chan->type == IIO_TEMP)
			*val = 165000;
		अन्यथा
			*val = 100000;
		वापस IIO_VAL_FRACTIONAL;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = -15887;
		*val2 = 515151;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक hdc2010_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा hdc2010_data *data = iio_priv(indio_dev);
	पूर्णांक new, ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (chan->type != IIO_CURRENT || val2 != 0)
			वापस -EINVAL;

		चयन (val) अणु
		हाल 1:
			new = HDC2010_HEATER_EN;
			अवरोध;
		हाल 0:
			new = 0;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		mutex_lock(&data->lock);
		ret = hdc2010_update_drdy_config(data, HDC2010_HEATER_EN, new);
		mutex_unlock(&data->lock);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info hdc2010_info = अणु
	.पढ़ो_raw = hdc2010_पढ़ो_raw,
	.ग_लिखो_raw = hdc2010_ग_लिखो_raw,
	.attrs = &hdc2010_attribute_group,
पूर्ण;

अटल पूर्णांक hdc2010_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा hdc2010_data *data;
	u8 पंचांगp;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter,
	    I2C_FUNC_SMBUS_WORD_DATA | I2C_FUNC_SMBUS_BYTE | I2C_FUNC_I2C))
		वापस -EOPNOTSUPP;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	mutex_init(&data->lock);

	indio_dev->dev.parent = &client->dev;
	/*
	 * As DEVICE ID रेजिस्टर करोes not dअगरferentiate between
	 * HDC2010 and HDC2080, we have the name hardcoded
	 */
	indio_dev->name = "hdc2010";
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &hdc2010_info;

	indio_dev->channels = hdc2010_channels;
	indio_dev->num_channels = ARRAY_SIZE(hdc2010_channels);

	/* Enable Automatic Measurement Mode at 5Hz */
	ret = hdc2010_update_drdy_config(data, HDC2010_AMM, HDC2010_AMM);
	अगर (ret)
		वापस ret;

	/*
	 * We enable both temp and humidity measurement.
	 * However the measurement won't start even in AMM until triggered.
	 */
	पंचांगp = (data->measurement_config & ~HDC2010_MEAS_CONF) |
		HDC2010_MEAS_TRIG;

	ret = i2c_smbus_ग_लिखो_byte_data(client, HDC2010_REG_MEASUREMENT_CONF, पंचांगp);
	अगर (ret) अणु
		dev_warn(&client->dev, "Unable to set up measurement\n");
		अगर (hdc2010_update_drdy_config(data, HDC2010_AMM, 0))
			dev_warn(&client->dev, "Unable to restore default AMM\n");
		वापस ret;
	पूर्ण

	data->measurement_config = पंचांगp;

	वापस iio_device_रेजिस्टर(indio_dev);
पूर्ण

अटल पूर्णांक hdc2010_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा hdc2010_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	/* Disable Automatic Measurement Mode */
	अगर (hdc2010_update_drdy_config(data, HDC2010_AMM, 0))
		dev_warn(&client->dev, "Unable to restore default AMM\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id hdc2010_id[] = अणु
	अणु "hdc2010" पूर्ण,
	अणु "hdc2080" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, hdc2010_id);

अटल स्थिर काष्ठा of_device_id hdc2010_dt_ids[] = अणु
	अणु .compatible = "ti,hdc2010" पूर्ण,
	अणु .compatible = "ti,hdc2080" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hdc2010_dt_ids);

अटल काष्ठा i2c_driver hdc2010_driver = अणु
	.driver = अणु
		.name	= "hdc2010",
		.of_match_table = hdc2010_dt_ids,
	पूर्ण,
	.probe = hdc2010_probe,
	.हटाओ = hdc2010_हटाओ,
	.id_table = hdc2010_id,
पूर्ण;
module_i2c_driver(hdc2010_driver);

MODULE_AUTHOR("Eugene Zaikonnikov <ez@norphonic.com>");
MODULE_DESCRIPTION("TI HDC2010 humidity and temperature sensor driver");
MODULE_LICENSE("GPL");
