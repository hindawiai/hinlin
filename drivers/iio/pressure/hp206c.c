<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * hp206c.c - HOPERF HP206C precision barometer and alसमयter sensor
 *
 * Copyright (c) 2016, Intel Corporation.
 *
 * (7-bit I2C slave address 0x76)
 *
 * Datasheet:
 *  http://www.hoperf.com/upload/sensor/HP206C_DataSheet_EN_V2.0.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/util_macros.h>
#समावेश <linux/acpi.h>

#समावेश <यंत्र/unaligned.h>

/* I2C commands: */
#घोषणा HP206C_CMD_SOFT_RST	0x06

#घोषणा HP206C_CMD_ADC_CVT	0x40

#घोषणा HP206C_CMD_ADC_CVT_OSR_4096	0x00
#घोषणा HP206C_CMD_ADC_CVT_OSR_2048	0x04
#घोषणा HP206C_CMD_ADC_CVT_OSR_1024	0x08
#घोषणा HP206C_CMD_ADC_CVT_OSR_512	0x0c
#घोषणा HP206C_CMD_ADC_CVT_OSR_256	0x10
#घोषणा HP206C_CMD_ADC_CVT_OSR_128	0x14

#घोषणा HP206C_CMD_ADC_CVT_CHNL_PT	0x00
#घोषणा HP206C_CMD_ADC_CVT_CHNL_T	0x02

#घोषणा HP206C_CMD_READ_P	0x30
#घोषणा HP206C_CMD_READ_T	0x32

#घोषणा HP206C_CMD_READ_REG	0x80
#घोषणा HP206C_CMD_WRITE_REG	0xc0

#घोषणा HP206C_REG_INT_EN	0x0b
#घोषणा HP206C_REG_INT_CFG	0x0c

#घोषणा HP206C_REG_INT_SRC	0x0d
#घोषणा HP206C_FLAG_DEV_RDY	0x40

#घोषणा HP206C_REG_PARA		0x0f
#घोषणा HP206C_FLAG_CMPS_EN	0x80

/* Maximum spin क्रम DEV_RDY */
#घोषणा HP206C_MAX_DEV_RDY_WAIT_COUNT 20
#घोषणा HP206C_DEV_RDY_WAIT_US    20000

काष्ठा hp206c_data अणु
	काष्ठा mutex mutex;
	काष्ठा i2c_client *client;
	पूर्णांक temp_osr_index;
	पूर्णांक pres_osr_index;
पूर्ण;

काष्ठा hp206c_osr_setting अणु
	u8 osr_mask;
	अचिन्हित पूर्णांक temp_conv_समय_us;
	अचिन्हित पूर्णांक pres_conv_समय_us;
पूर्ण;

/* Data from Table 5 in datasheet. */
अटल स्थिर काष्ठा hp206c_osr_setting hp206c_osr_settings[] = अणु
	अणु HP206C_CMD_ADC_CVT_OSR_4096,	65600,	131100	पूर्ण,
	अणु HP206C_CMD_ADC_CVT_OSR_2048,	32800,	65600	पूर्ण,
	अणु HP206C_CMD_ADC_CVT_OSR_1024,	16400,	32800	पूर्ण,
	अणु HP206C_CMD_ADC_CVT_OSR_512,	8200,	16400	पूर्ण,
	अणु HP206C_CMD_ADC_CVT_OSR_256,	4100,	8200	पूर्ण,
	अणु HP206C_CMD_ADC_CVT_OSR_128,	2100,	4100	पूर्ण,
पूर्ण;
अटल स्थिर पूर्णांक hp206c_osr_rates[] = अणु 4096, 2048, 1024, 512, 256, 128 पूर्ण;
अटल स्थिर अक्षर hp206c_osr_rates_str[] = "4096 2048 1024 512 256 128";

अटल अंतरभूत पूर्णांक hp206c_पढ़ो_reg(काष्ठा i2c_client *client, u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_byte_data(client, HP206C_CMD_READ_REG | reg);
पूर्ण

अटल अंतरभूत पूर्णांक hp206c_ग_लिखो_reg(काष्ठा i2c_client *client, u8 reg, u8 val)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(client,
			HP206C_CMD_WRITE_REG | reg, val);
पूर्ण

अटल पूर्णांक hp206c_पढ़ो_20bit(काष्ठा i2c_client *client, u8 cmd)
अणु
	पूर्णांक ret;
	u8 values[3];

	ret = i2c_smbus_पढ़ो_i2c_block_data(client, cmd, माप(values), values);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != माप(values))
		वापस -EIO;
	वापस get_unaligned_be24(&values[0]) & GENMASK(19, 0);
पूर्ण

/* Spin क्रम max 160ms until DEV_RDY is 1, or वापस error. */
अटल पूर्णांक hp206c_रुको_dev_rdy(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;
	पूर्णांक count = 0;
	काष्ठा hp206c_data *data = iio_priv(indio_dev);
	काष्ठा i2c_client *client = data->client;

	जबतक (++count <= HP206C_MAX_DEV_RDY_WAIT_COUNT) अणु
		ret = hp206c_पढ़ो_reg(client, HP206C_REG_INT_SRC);
		अगर (ret < 0) अणु
			dev_err(&indio_dev->dev, "Failed READ_REG INT_SRC: %d\n", ret);
			वापस ret;
		पूर्ण
		अगर (ret & HP206C_FLAG_DEV_RDY)
			वापस 0;
		usleep_range(HP206C_DEV_RDY_WAIT_US, HP206C_DEV_RDY_WAIT_US * 3 / 2);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक hp206c_set_compensation(काष्ठा i2c_client *client, bool enabled)
अणु
	पूर्णांक val;

	val = hp206c_पढ़ो_reg(client, HP206C_REG_PARA);
	अगर (val < 0)
		वापस val;
	अगर (enabled)
		val |= HP206C_FLAG_CMPS_EN;
	अन्यथा
		val &= ~HP206C_FLAG_CMPS_EN;

	वापस hp206c_ग_लिखो_reg(client, HP206C_REG_PARA, val);
पूर्ण

/* Do a soft reset */
अटल पूर्णांक hp206c_soft_reset(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;
	काष्ठा hp206c_data *data = iio_priv(indio_dev);
	काष्ठा i2c_client *client = data->client;

	ret = i2c_smbus_ग_लिखो_byte(client, HP206C_CMD_SOFT_RST);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to reset device: %d\n", ret);
		वापस ret;
	पूर्ण

	usleep_range(400, 600);

	ret = hp206c_रुको_dev_rdy(indio_dev);
	अगर (ret) अणु
		dev_err(&client->dev, "Device not ready after soft reset: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = hp206c_set_compensation(client, true);
	अगर (ret)
		dev_err(&client->dev, "Failed to enable compensation: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक hp206c_conv_and_पढ़ो(काष्ठा iio_dev *indio_dev,
				u8 conv_cmd, u8 पढ़ो_cmd,
				अचिन्हित पूर्णांक sleep_us)
अणु
	पूर्णांक ret;
	काष्ठा hp206c_data *data = iio_priv(indio_dev);
	काष्ठा i2c_client *client = data->client;

	ret = hp206c_रुको_dev_rdy(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&indio_dev->dev, "Device not ready: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte(client, conv_cmd);
	अगर (ret < 0) अणु
		dev_err(&indio_dev->dev, "Failed convert: %d\n", ret);
		वापस ret;
	पूर्ण

	usleep_range(sleep_us, sleep_us * 3 / 2);

	ret = hp206c_रुको_dev_rdy(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&indio_dev->dev, "Device not ready: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = hp206c_पढ़ो_20bit(client, पढ़ो_cmd);
	अगर (ret < 0)
		dev_err(&indio_dev->dev, "Failed read: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hp206c_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			   पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	काष्ठा hp206c_data *data = iio_priv(indio_dev);
	स्थिर काष्ठा hp206c_osr_setting *osr_setting;
	u8 conv_cmd;

	mutex_lock(&data->mutex);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			*val = hp206c_osr_rates[data->temp_osr_index];
			ret = IIO_VAL_INT;
			अवरोध;

		हाल IIO_PRESSURE:
			*val = hp206c_osr_rates[data->pres_osr_index];
			ret = IIO_VAL_INT;
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
		अवरोध;

	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			osr_setting = &hp206c_osr_settings[data->temp_osr_index];
			conv_cmd = HP206C_CMD_ADC_CVT |
					osr_setting->osr_mask |
					HP206C_CMD_ADC_CVT_CHNL_T;
			ret = hp206c_conv_and_पढ़ो(indio_dev,
					conv_cmd,
					HP206C_CMD_READ_T,
					osr_setting->temp_conv_समय_us);
			अगर (ret >= 0) अणु
				/* 20 signअगरicant bits are provided.
				 * Extend sign over the rest.
				 */
				*val = sign_extend32(ret, 19);
				ret = IIO_VAL_INT;
			पूर्ण
			अवरोध;

		हाल IIO_PRESSURE:
			osr_setting = &hp206c_osr_settings[data->pres_osr_index];
			conv_cmd = HP206C_CMD_ADC_CVT |
					osr_setting->osr_mask |
					HP206C_CMD_ADC_CVT_CHNL_PT;
			ret = hp206c_conv_and_पढ़ो(indio_dev,
					conv_cmd,
					HP206C_CMD_READ_P,
					osr_setting->pres_conv_समय_us);
			अगर (ret >= 0) अणु
				*val = ret;
				ret = IIO_VAL_INT;
			पूर्ण
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
		अवरोध;

	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			*val = 0;
			*val2 = 10000;
			ret = IIO_VAL_INT_PLUS_MICRO;
			अवरोध;

		हाल IIO_PRESSURE:
			*val = 0;
			*val2 = 1000;
			ret = IIO_VAL_INT_PLUS_MICRO;
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	mutex_unlock(&data->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक hp206c_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	पूर्णांक ret = 0;
	काष्ठा hp206c_data *data = iio_priv(indio_dev);

	अगर (mask != IIO_CHAN_INFO_OVERSAMPLING_RATIO)
		वापस -EINVAL;
	mutex_lock(&data->mutex);
	चयन (chan->type) अणु
	हाल IIO_TEMP:
		data->temp_osr_index = find_बंदst_descending(val,
			hp206c_osr_rates, ARRAY_SIZE(hp206c_osr_rates));
		अवरोध;
	हाल IIO_PRESSURE:
		data->pres_osr_index = find_बंदst_descending(val,
			hp206c_osr_rates, ARRAY_SIZE(hp206c_osr_rates));
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	mutex_unlock(&data->mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec hp206c_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE) |
				      BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),
	पूर्ण,
	अणु
		.type = IIO_PRESSURE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE) |
				      BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),
	पूर्ण
पूर्ण;

अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL(hp206c_osr_rates_str);

अटल काष्ठा attribute *hp206c_attributes[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group hp206c_attribute_group = अणु
	.attrs = hp206c_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info hp206c_info = अणु
	.attrs = &hp206c_attribute_group,
	.पढ़ो_raw = hp206c_पढ़ो_raw,
	.ग_लिखो_raw = hp206c_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक hp206c_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा hp206c_data *data;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE |
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_READ_I2C_BLOCK)) अणु
		dev_err(&client->dev, "Adapter does not support "
				"all required i2c functionality\n");
		वापस -ENODEV;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	data->client = client;
	mutex_init(&data->mutex);

	indio_dev->info = &hp206c_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = hp206c_channels;
	indio_dev->num_channels = ARRAY_SIZE(hp206c_channels);

	i2c_set_clientdata(client, indio_dev);

	/* Do a soft reset on probe */
	ret = hp206c_soft_reset(indio_dev);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to reset on startup: %d\n", ret);
		वापस -ENODEV;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id hp206c_id[] = अणु
	अणु"hp206c"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, hp206c_id);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id hp206c_acpi_match[] = अणु
	अणु"HOP206C", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, hp206c_acpi_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver hp206c_driver = अणु
	.probe = hp206c_probe,
	.id_table = hp206c_id,
	.driver = अणु
		.name = "hp206c",
		.acpi_match_table = ACPI_PTR(hp206c_acpi_match),
	पूर्ण,
पूर्ण;

module_i2c_driver(hp206c_driver);

MODULE_DESCRIPTION("HOPERF HP206C precision barometer and altimeter sensor");
MODULE_AUTHOR("Leonard Crestez <leonard.crestez@intel.com>");
MODULE_LICENSE("GPL v2");
