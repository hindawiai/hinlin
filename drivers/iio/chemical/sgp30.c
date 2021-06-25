<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sgp30.c - Support क्रम Sensirion SGP Gas Sensors
 *
 * Copyright (C) 2018 Andreas Brauchli <andreas.brauchli@sensirion.com>
 *
 * I2C slave address: 0x58
 *
 * Datasheets:
 * https://www.sensirion.com/file/datasheet_sgp30
 * https://www.sensirion.com/file/datasheet_sgpc3
 *
 * TODO:
 * - baseline support
 * - humidity compensation
 * - घातer mode चयनing (SGPC3)
 */

#समावेश <linux/crc8.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mutex.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा SGP_WORD_LEN				2
#घोषणा SGP_CRC8_POLYNOMIAL			0x31
#घोषणा SGP_CRC8_INIT				0xff
#घोषणा SGP_CRC8_LEN				1
#घोषणा SGP_CMD(cmd_word)			cpu_to_be16(cmd_word)
#घोषणा SGP_CMD_DURATION_US			12000
#घोषणा SGP_MEASUREMENT_DURATION_US		50000
#घोषणा SGP_CMD_LEN				SGP_WORD_LEN
#घोषणा SGP_CMD_MAX_BUF_SIZE			(SGP_CMD_LEN + 2 * SGP_WORD_LEN)
#घोषणा SGP_MEASUREMENT_LEN			2
#घोषणा SGP30_MEASURE_INTERVAL_HZ		1
#घोषणा SGPC3_MEASURE_INTERVAL_HZ		2
#घोषणा SGP_VERS_PRODUCT(data)	((((data)->feature_set) & 0xf000) >> 12)
#घोषणा SGP_VERS_RESERVED(data)	((((data)->feature_set) & 0x0800) >> 11)
#घोषणा SGP_VERS_GEN(data)	((((data)->feature_set) & 0x0600) >> 9)
#घोषणा SGP_VERS_ENG_BIT(data)	((((data)->feature_set) & 0x0100) >> 8)
#घोषणा SGP_VERS_MAJOR(data)	((((data)->feature_set) & 0x00e0) >> 5)
#घोषणा SGP_VERS_MINOR(data)	(((data)->feature_set) & 0x001f)

DECLARE_CRC8_TABLE(sgp_crc8_table);

क्रमागत sgp_product_id अणु
	SGP30 = 0,
	SGPC3,
पूर्ण;

क्रमागत sgp30_channel_idx अणु
	SGP30_IAQ_TVOC_IDX = 0,
	SGP30_IAQ_CO2EQ_IDX,
	SGP30_SIG_ETOH_IDX,
	SGP30_SIG_H2_IDX,
पूर्ण;

क्रमागत sgpc3_channel_idx अणु
	SGPC3_IAQ_TVOC_IDX = 10,
	SGPC3_SIG_ETOH_IDX,
पूर्ण;

क्रमागत sgp_cmd अणु
	SGP_CMD_IAQ_INIT			= SGP_CMD(0x2003),
	SGP_CMD_IAQ_MEASURE			= SGP_CMD(0x2008),
	SGP_CMD_GET_FEATURE_SET			= SGP_CMD(0x202f),
	SGP_CMD_GET_SERIAL_ID			= SGP_CMD(0x3682),

	SGP30_CMD_MEASURE_SIGNAL		= SGP_CMD(0x2050),

	SGPC3_CMD_MEASURE_RAW			= SGP_CMD(0x2046),
पूर्ण;

काष्ठा sgp_version अणु
	u8 major;
	u8 minor;
पूर्ण;

काष्ठा sgp_crc_word अणु
	__be16 value;
	u8 crc8;
पूर्ण __attribute__((__packed__));

जोड़ sgp_पढ़ोing अणु
	u8 start;
	काष्ठा sgp_crc_word raw_words[4];
पूर्ण;

क्रमागत _iaq_buffer_state अणु
	IAQ_BUFFER_EMPTY = 0,
	IAQ_BUFFER_DEFAULT_VALS,
	IAQ_BUFFER_VALID,
पूर्ण;

काष्ठा sgp_data अणु
	काष्ठा i2c_client *client;
	काष्ठा task_काष्ठा *iaq_thपढ़ो;
	काष्ठा mutex data_lock;
	अचिन्हित दीर्घ iaq_init_start_jअगरfies;
	अचिन्हित दीर्घ iaq_defval_skip_jअगरfies;
	u16 product_id;
	u16 feature_set;
	अचिन्हित दीर्घ measure_पूर्णांकerval_jअगरfies;
	क्रमागत sgp_cmd iaq_init_cmd;
	क्रमागत sgp_cmd measure_iaq_cmd;
	क्रमागत sgp_cmd measure_gas_संकेतs_cmd;
	जोड़ sgp_पढ़ोing buffer;
	जोड़ sgp_पढ़ोing iaq_buffer;
	क्रमागत _iaq_buffer_state iaq_buffer_state;
पूर्ण;

काष्ठा sgp_device अणु
	स्थिर काष्ठा iio_chan_spec *channels;
	पूर्णांक num_channels;
पूर्ण;

अटल स्थिर काष्ठा sgp_version supported_versions_sgp30[] = अणु
	अणु
		.major = 1,
		.minor = 0,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sgp_version supported_versions_sgpc3[] = अणु
	अणु
		.major = 0,
		.minor = 4,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec sgp30_channels[] = अणु
	अणु
		.type = IIO_CONCENTRATION,
		.channel2 = IIO_MOD_VOC,
		.modअगरied = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.address = SGP30_IAQ_TVOC_IDX,
	पूर्ण,
	अणु
		.type = IIO_CONCENTRATION,
		.channel2 = IIO_MOD_CO2,
		.modअगरied = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.address = SGP30_IAQ_CO2EQ_IDX,
	पूर्ण,
	अणु
		.type = IIO_CONCENTRATION,
		.channel2 = IIO_MOD_ETHANOL,
		.modअगरied = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.address = SGP30_SIG_ETOH_IDX,
	पूर्ण,
	अणु
		.type = IIO_CONCENTRATION,
		.channel2 = IIO_MOD_H2,
		.modअगरied = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.address = SGP30_SIG_H2_IDX,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec sgpc3_channels[] = अणु
	अणु
		.type = IIO_CONCENTRATION,
		.channel2 = IIO_MOD_VOC,
		.modअगरied = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.address = SGPC3_IAQ_TVOC_IDX,
	पूर्ण,
	अणु
		.type = IIO_CONCENTRATION,
		.channel2 = IIO_MOD_ETHANOL,
		.modअगरied = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.address = SGPC3_SIG_ETOH_IDX,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sgp_device sgp_devices[] = अणु
	[SGP30] = अणु
		.channels = sgp30_channels,
		.num_channels = ARRAY_SIZE(sgp30_channels),
	पूर्ण,
	[SGPC3] = अणु
		.channels = sgpc3_channels,
		.num_channels = ARRAY_SIZE(sgpc3_channels),
	पूर्ण,
पूर्ण;

/**
 * sgp_verअगरy_buffer() - verअगरy the checksums of the data buffer words
 *
 * @data:       SGP data
 * @buf:        Raw data buffer
 * @word_count: Num data words stored in the buffer, excluding CRC bytes
 *
 * Return:      0 on success, negative error otherwise.
 */
अटल पूर्णांक sgp_verअगरy_buffer(स्थिर काष्ठा sgp_data *data,
			     जोड़ sgp_पढ़ोing *buf, माप_प्रकार word_count)
अणु
	माप_प्रकार size = word_count * (SGP_WORD_LEN + SGP_CRC8_LEN);
	पूर्णांक i;
	u8 crc;
	u8 *data_buf = &buf->start;

	क्रम (i = 0; i < size; i += SGP_WORD_LEN + SGP_CRC8_LEN) अणु
		crc = crc8(sgp_crc8_table, &data_buf[i], SGP_WORD_LEN,
			   SGP_CRC8_INIT);
		अगर (crc != data_buf[i + SGP_WORD_LEN]) अणु
			dev_err(&data->client->dev, "CRC error\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sgp_पढ़ो_cmd() - पढ़ोs data from sensor after issuing a command
 * The caller must hold data->data_lock क्रम the duration of the call.
 * @data:        SGP data
 * @cmd:         SGP Command to issue
 * @buf:         Raw data buffer to use
 * @word_count:  Num words to पढ़ो, excluding CRC bytes
 * @duration_us: Time taken to sensor to take a पढ़ोing and data to be पढ़ोy.
 *
 * Return:       0 on success, negative error otherwise.
 */
अटल पूर्णांक sgp_पढ़ो_cmd(काष्ठा sgp_data *data, क्रमागत sgp_cmd cmd,
			जोड़ sgp_पढ़ोing *buf, माप_प्रकार word_count,
			अचिन्हित दीर्घ duration_us)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = data->client;
	माप_प्रकार size = word_count * (SGP_WORD_LEN + SGP_CRC8_LEN);
	u8 *data_buf;

	ret = i2c_master_send(client, (स्थिर अक्षर *)&cmd, SGP_CMD_LEN);
	अगर (ret != SGP_CMD_LEN)
		वापस -EIO;
	usleep_range(duration_us, duration_us + 1000);

	अगर (word_count == 0)
		वापस 0;

	data_buf = &buf->start;
	ret = i2c_master_recv(client, data_buf, size);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != size)
		वापस -EIO;

	वापस sgp_verअगरy_buffer(data, buf, word_count);
पूर्ण

/**
 * sgp_measure_iaq() - measure and retrieve IAQ values from sensor
 * The caller must hold data->data_lock क्रम the duration of the call.
 * @data:       SGP data
 *
 * Return:      0 on success, -EBUSY on शेष values, negative error
 *              otherwise.
 */

अटल पूर्णांक sgp_measure_iaq(काष्ठा sgp_data *data)
अणु
	पूर्णांक ret;
	/* data contains शेष values */
	bool शेष_vals = !समय_after(jअगरfies, data->iaq_init_start_jअगरfies +
						 data->iaq_defval_skip_jअगरfies);

	ret = sgp_पढ़ो_cmd(data, data->measure_iaq_cmd, &data->iaq_buffer,
			   SGP_MEASUREMENT_LEN, SGP_MEASUREMENT_DURATION_US);
	अगर (ret < 0)
		वापस ret;

	data->iaq_buffer_state = IAQ_BUFFER_DEFAULT_VALS;

	अगर (शेष_vals)
		वापस -EBUSY;

	data->iaq_buffer_state = IAQ_BUFFER_VALID;

	वापस 0;
पूर्ण

अटल व्योम sgp_iaq_thपढ़ो_sleep_until(स्थिर काष्ठा sgp_data *data,
				       अचिन्हित दीर्घ sleep_jअगरfies)
अणु
	स्थिर दीर्घ IAQ_POLL = 50000;

	जबतक (!समय_after(jअगरfies, sleep_jअगरfies)) अणु
		usleep_range(IAQ_POLL, IAQ_POLL + 10000);
		अगर (kthपढ़ो_should_stop() || data->iaq_init_start_jअगरfies == 0)
			वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक sgp_iaq_thपढ़ोfn(व्योम *p)
अणु
	काष्ठा sgp_data *data = (काष्ठा sgp_data *)p;
	अचिन्हित दीर्घ next_update_jअगरfies;
	पूर्णांक ret;

	जबतक (!kthपढ़ो_should_stop()) अणु
		mutex_lock(&data->data_lock);
		अगर (data->iaq_init_start_jअगरfies == 0) अणु
			ret = sgp_पढ़ो_cmd(data, data->iaq_init_cmd, शून्य, 0,
					   SGP_CMD_DURATION_US);
			अगर (ret < 0)
				जाओ unlock_sleep_जारी;
			data->iaq_init_start_jअगरfies = jअगरfies;
		पूर्ण

		ret = sgp_measure_iaq(data);
		अगर (ret && ret != -EBUSY) अणु
			dev_warn(&data->client->dev,
				 "IAQ measurement error [%d]\n", ret);
		पूर्ण
unlock_sleep_जारी:
		next_update_jअगरfies = jअगरfies + data->measure_पूर्णांकerval_jअगरfies;
		mutex_unlock(&data->data_lock);
		sgp_iaq_thपढ़ो_sleep_until(data, next_update_jअगरfies);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sgp_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा sgp_data *data = iio_priv(indio_dev);
	काष्ठा sgp_crc_word *words;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		mutex_lock(&data->data_lock);
		अगर (data->iaq_buffer_state != IAQ_BUFFER_VALID) अणु
			mutex_unlock(&data->data_lock);
			वापस -EBUSY;
		पूर्ण
		words = data->iaq_buffer.raw_words;
		चयन (chan->address) अणु
		हाल SGP30_IAQ_TVOC_IDX:
		हाल SGPC3_IAQ_TVOC_IDX:
			*val = 0;
			*val2 = be16_to_cpu(words[1].value);
			ret = IIO_VAL_INT_PLUS_न_अंकO;
			अवरोध;
		हाल SGP30_IAQ_CO2EQ_IDX:
			*val = 0;
			*val2 = be16_to_cpu(words[0].value);
			ret = IIO_VAL_INT_PLUS_MICRO;
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		mutex_unlock(&data->data_lock);
		अवरोध;
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&data->data_lock);
		अगर (chan->address == SGPC3_SIG_ETOH_IDX) अणु
			अगर (data->iaq_buffer_state == IAQ_BUFFER_EMPTY)
				ret = -EBUSY;
			अन्यथा
				ret = 0;
			words = data->iaq_buffer.raw_words;
		पूर्ण अन्यथा अणु
			ret = sgp_पढ़ो_cmd(data, data->measure_gas_संकेतs_cmd,
					   &data->buffer, SGP_MEASUREMENT_LEN,
					   SGP_MEASUREMENT_DURATION_US);
			words = data->buffer.raw_words;
		पूर्ण
		अगर (ret) अणु
			mutex_unlock(&data->data_lock);
			वापस ret;
		पूर्ण

		चयन (chan->address) अणु
		हाल SGP30_SIG_ETOH_IDX:
			*val = be16_to_cpu(words[1].value);
			ret = IIO_VAL_INT;
			अवरोध;
		हाल SGPC3_SIG_ETOH_IDX:
		हाल SGP30_SIG_H2_IDX:
			*val = be16_to_cpu(words[0].value);
			ret = IIO_VAL_INT;
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		mutex_unlock(&data->data_lock);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sgp_check_compat(काष्ठा sgp_data *data,
			    अचिन्हित पूर्णांक product_id)
अणु
	काष्ठा device *dev = &data->client->dev;
	स्थिर काष्ठा sgp_version *supported_versions;
	u16 ix, num_fs;
	u16 product, generation, major, minor;

	/* driver करोes not match product */
	generation = SGP_VERS_GEN(data);
	अगर (generation != 0) अणु
		dev_err(dev,
			"incompatible product generation %d != 0", generation);
		वापस -ENODEV;
	पूर्ण

	product = SGP_VERS_PRODUCT(data);
	अगर (product != product_id) अणु
		dev_err(dev, "sensor reports a different product: 0x%04hx\n",
			product);
		वापस -ENODEV;
	पूर्ण

	अगर (SGP_VERS_RESERVED(data))
		dev_warn(dev, "reserved bit is set\n");

	/* engineering samples are not supported: no पूर्णांकerface guarantees */
	अगर (SGP_VERS_ENG_BIT(data))
		वापस -ENODEV;

	चयन (product) अणु
	हाल SGP30:
		supported_versions = supported_versions_sgp30;
		num_fs = ARRAY_SIZE(supported_versions_sgp30);
		अवरोध;
	हाल SGPC3:
		supported_versions = supported_versions_sgpc3;
		num_fs = ARRAY_SIZE(supported_versions_sgpc3);
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	major = SGP_VERS_MAJOR(data);
	minor = SGP_VERS_MINOR(data);
	क्रम (ix = 0; ix < num_fs; ix++) अणु
		अगर (major == supported_versions[ix].major &&
		    minor >= supported_versions[ix].minor)
			वापस 0;
	पूर्ण
	dev_err(dev, "unsupported sgp version: %d.%d\n", major, minor);

	वापस -ENODEV;
पूर्ण

अटल व्योम sgp_init(काष्ठा sgp_data *data)
अणु
	data->iaq_init_cmd = SGP_CMD_IAQ_INIT;
	data->iaq_init_start_jअगरfies = 0;
	data->iaq_buffer_state = IAQ_BUFFER_EMPTY;
	चयन (SGP_VERS_PRODUCT(data)) अणु
	हाल SGP30:
		data->measure_पूर्णांकerval_jअगरfies = SGP30_MEASURE_INTERVAL_HZ * HZ;
		data->measure_iaq_cmd = SGP_CMD_IAQ_MEASURE;
		data->measure_gas_संकेतs_cmd = SGP30_CMD_MEASURE_SIGNAL;
		data->product_id = SGP30;
		data->iaq_defval_skip_jअगरfies = 15 * HZ;
		अवरोध;
	हाल SGPC3:
		data->measure_पूर्णांकerval_jअगरfies = SGPC3_MEASURE_INTERVAL_HZ * HZ;
		data->measure_iaq_cmd = SGPC3_CMD_MEASURE_RAW;
		data->measure_gas_संकेतs_cmd = SGPC3_CMD_MEASURE_RAW;
		data->product_id = SGPC3;
		data->iaq_defval_skip_jअगरfies =
			43 * data->measure_पूर्णांकerval_jअगरfies;
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info sgp_info = अणु
	.पढ़ो_raw	= sgp_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sgp_dt_ids[] = अणु
	अणु .compatible = "sensirion,sgp30", .data = (व्योम *)SGP30 पूर्ण,
	अणु .compatible = "sensirion,sgpc3", .data = (व्योम *)SGPC3 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक sgp_probe(काष्ठा i2c_client *client,
		     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा iio_dev *indio_dev;
	काष्ठा sgp_data *data;
	अचिन्हित दीर्घ product_id;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	अगर (dev_fwnode(dev))
		product_id = (अचिन्हित दीर्घ)device_get_match_data(dev);
	अन्यथा
		product_id = id->driver_data;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	crc8_populate_msb(sgp_crc8_table, SGP_CRC8_POLYNOMIAL);
	mutex_init(&data->data_lock);

	/* get feature set version and ग_लिखो it to client data */
	ret = sgp_पढ़ो_cmd(data, SGP_CMD_GET_FEATURE_SET, &data->buffer, 1,
			   SGP_CMD_DURATION_US);
	अगर (ret < 0)
		वापस ret;

	data->feature_set = be16_to_cpu(data->buffer.raw_words[0].value);

	ret = sgp_check_compat(data, product_id);
	अगर (ret)
		वापस ret;

	indio_dev->info = &sgp_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = sgp_devices[product_id].channels;
	indio_dev->num_channels = sgp_devices[product_id].num_channels;

	sgp_init(data);

	ret = devm_iio_device_रेजिस्टर(dev, indio_dev);
	अगर (ret) अणु
		dev_err(dev, "failed to register iio device\n");
		वापस ret;
	पूर्ण

	data->iaq_thपढ़ो = kthपढ़ो_run(sgp_iaq_thपढ़ोfn, data,
				       "%s-iaq", data->client->name);

	वापस 0;
पूर्ण

अटल पूर्णांक sgp_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा sgp_data *data = iio_priv(indio_dev);

	अगर (data->iaq_thपढ़ो)
		kthपढ़ो_stop(data->iaq_thपढ़ो);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id sgp_id[] = अणु
	अणु "sgp30", SGP30 पूर्ण,
	अणु "sgpc3", SGPC3 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, sgp_id);
MODULE_DEVICE_TABLE(of, sgp_dt_ids);

अटल काष्ठा i2c_driver sgp_driver = अणु
	.driver = अणु
		.name = "sgp30",
		.of_match_table = sgp_dt_ids,
	पूर्ण,
	.probe = sgp_probe,
	.हटाओ = sgp_हटाओ,
	.id_table = sgp_id,
पूर्ण;
module_i2c_driver(sgp_driver);

MODULE_AUTHOR("Andreas Brauchli <andreas.brauchli@sensirion.com>");
MODULE_AUTHOR("Pascal Sachs <pascal.sachs@sensirion.com>");
MODULE_DESCRIPTION("Sensirion SGP gas sensors");
MODULE_LICENSE("GPL v2");
