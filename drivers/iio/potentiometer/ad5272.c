<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Analog Devices AD5272 digital potentiometer driver
 * Copyright (C) 2018 Phil Reid <preid@electromag.com.au>
 *
 * Datasheet: https://www.analog.com/media/en/technical-करोcumentation/data-sheets/AD5272_5274.pdf
 *
 * DEVID	#Wipers	#Positions	Resistor Opts (kOhm)	i2c address
 * ad5272	1	1024		20, 50, 100		01011xx
 * ad5274	1	256		20, 100			01011xx
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>

#घोषणा  AD5272_RDAC_WR  1
#घोषणा  AD5272_RDAC_RD  2
#घोषणा  AD5272_RESET    4
#घोषणा  AD5272_CTL      7

#घोषणा  AD5272_RDAC_WR_EN  BIT(1)

काष्ठा ad5272_cfg अणु
	पूर्णांक max_pos;
	पूर्णांक kohms;
	पूर्णांक shअगरt;
पूर्ण;

क्रमागत ad5272_type अणु
	AD5272_020,
	AD5272_050,
	AD5272_100,
	AD5274_020,
	AD5274_100,
पूर्ण;

अटल स्थिर काष्ठा ad5272_cfg ad5272_cfg[] = अणु
	[AD5272_020] = अणु .max_pos = 1024, .kohms = 20 पूर्ण,
	[AD5272_050] = अणु .max_pos = 1024, .kohms = 50 पूर्ण,
	[AD5272_100] = अणु .max_pos = 1024, .kohms = 100 पूर्ण,
	[AD5274_020] = अणु .max_pos = 256,  .kohms = 20,  .shअगरt = 2 पूर्ण,
	[AD5274_100] = अणु .max_pos = 256,  .kohms = 100, .shअगरt = 2 पूर्ण,
पूर्ण;

काष्ठा ad5272_data अणु
	काष्ठा i2c_client       *client;
	काष्ठा mutex            lock;
	स्थिर काष्ठा ad5272_cfg *cfg;
	u8                      buf[2] ____cacheline_aligned;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ad5272_channel = अणु
	.type = IIO_RESISTANCE,
	.output = 1,
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
पूर्ण;

अटल पूर्णांक ad5272_ग_लिखो(काष्ठा ad5272_data *data, पूर्णांक reg, पूर्णांक val)
अणु
	पूर्णांक ret;

	data->buf[0] = (reg << 2) | ((val >> 8) & 0x3);
	data->buf[1] = (u8)val;

	mutex_lock(&data->lock);
	ret = i2c_master_send(data->client, data->buf, माप(data->buf));
	mutex_unlock(&data->lock);
	वापस ret < 0 ? ret : 0;
पूर्ण

अटल पूर्णांक ad5272_पढ़ो(काष्ठा ad5272_data *data, पूर्णांक reg, पूर्णांक *val)
अणु
	पूर्णांक ret;

	data->buf[0] = reg << 2;
	data->buf[1] = 0;

	mutex_lock(&data->lock);
	ret = i2c_master_send(data->client, data->buf, माप(data->buf));
	अगर (ret < 0)
		जाओ error;

	ret = i2c_master_recv(data->client, data->buf, माप(data->buf));
	अगर (ret < 0)
		जाओ error;

	*val = ((data->buf[0] & 0x3) << 8) | data->buf[1];
	ret = 0;
error:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ad5272_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा ad5272_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW: अणु
		ret = ad5272_पढ़ो(data, AD5272_RDAC_RD, val);
		*val = *val >> data->cfg->shअगरt;
		वापस ret ? ret : IIO_VAL_INT;
	पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		*val = 1000 * data->cfg->kohms;
		*val2 = data->cfg->max_pos;
		वापस IIO_VAL_FRACTIONAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad5272_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा ad5272_data *data = iio_priv(indio_dev);

	अगर (mask != IIO_CHAN_INFO_RAW)
		वापस -EINVAL;

	अगर (val >= data->cfg->max_pos || val < 0 || val2)
		वापस -EINVAL;

	वापस ad5272_ग_लिखो(data, AD5272_RDAC_WR, val << data->cfg->shअगरt);
पूर्ण

अटल स्थिर काष्ठा iio_info ad5272_info = अणु
	.पढ़ो_raw = ad5272_पढ़ो_raw,
	.ग_लिखो_raw = ad5272_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक ad5272_reset(काष्ठा ad5272_data *data)
अणु
	काष्ठा gpio_desc *reset_gpio;

	reset_gpio = devm_gpiod_get_optional(&data->client->dev, "reset",
		GPIOD_OUT_HIGH);
	अगर (IS_ERR(reset_gpio))
		वापस PTR_ERR(reset_gpio);

	अगर (reset_gpio) अणु
		udelay(1);
		gpiod_set_value(reset_gpio, 0);
	पूर्ण अन्यथा अणु
		ad5272_ग_लिखो(data, AD5272_RESET, 0);
	पूर्ण
	usleep_range(1000, 2000);

	वापस 0;
पूर्ण

अटल पूर्णांक ad5272_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad5272_data *data;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	i2c_set_clientdata(client, indio_dev);

	data = iio_priv(indio_dev);
	data->client = client;
	mutex_init(&data->lock);
	data->cfg = &ad5272_cfg[id->driver_data];

	ret = ad5272_reset(data);
	अगर (ret)
		वापस ret;

	ret = ad5272_ग_लिखो(data, AD5272_CTL, AD5272_RDAC_WR_EN);
	अगर (ret < 0)
		वापस -ENODEV;

	indio_dev->info = &ad5272_info;
	indio_dev->channels = &ad5272_channel;
	indio_dev->num_channels = 1;
	indio_dev->name = client->name;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id ad5272_dt_ids[] = अणु
	अणु .compatible = "adi,ad5272-020", .data = (व्योम *)AD5272_020 पूर्ण,
	अणु .compatible = "adi,ad5272-050", .data = (व्योम *)AD5272_050 पूर्ण,
	अणु .compatible = "adi,ad5272-100", .data = (व्योम *)AD5272_100 पूर्ण,
	अणु .compatible = "adi,ad5274-020", .data = (व्योम *)AD5274_020 पूर्ण,
	अणु .compatible = "adi,ad5274-100", .data = (व्योम *)AD5274_100 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ad5272_dt_ids);

अटल स्थिर काष्ठा i2c_device_id ad5272_id[] = अणु
	अणु "ad5272-020", AD5272_020 पूर्ण,
	अणु "ad5272-050", AD5272_050 पूर्ण,
	अणु "ad5272-100", AD5272_100 पूर्ण,
	अणु "ad5274-020", AD5274_020 पूर्ण,
	अणु "ad5274-100", AD5274_100 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ad5272_id);

अटल काष्ठा i2c_driver ad5272_driver = अणु
	.driver = अणु
		.name	= "ad5272",
		.of_match_table = ad5272_dt_ids,
	पूर्ण,
	.probe		= ad5272_probe,
	.id_table	= ad5272_id,
पूर्ण;

module_i2c_driver(ad5272_driver);

MODULE_AUTHOR("Phil Reid <preid@eletromag.com.au>");
MODULE_DESCRIPTION("AD5272 digital potentiometer");
MODULE_LICENSE("GPL v2");
