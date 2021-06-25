<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * vl6180.c - Support क्रम STMicroelectronics VL6180 ALS, range and proximity
 * sensor
 *
 * Copyright 2017 Peter Meerwald-Stadler <pmeerw@pmeerw.net>
 * Copyright 2017 Manivannan Sadhasivam <manivannanece23@gmail.com>
 *
 * IIO driver क्रम VL6180 (7-bit I2C slave address 0x29)
 *
 * Range: 0 to 100mm
 * ALS: < 1 Lux up to 100 kLux
 * IR: 850nm
 *
 * TODO: irq, threshold events, continuous mode, hardware buffer
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/delay.h>
#समावेश <linux/util_macros.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा VL6180_DRV_NAME "vl6180"

/* Device identअगरication रेजिस्टर and value */
#घोषणा VL6180_MODEL_ID	0x000
#घोषणा VL6180_MODEL_ID_VAL 0xb4

/* Configuration रेजिस्टरs */
#घोषणा VL6180_INTR_CONFIG 0x014
#घोषणा VL6180_INTR_CLEAR 0x015
#घोषणा VL6180_OUT_OF_RESET 0x016
#घोषणा VL6180_HOLD 0x017
#घोषणा VL6180_RANGE_START 0x018
#घोषणा VL6180_ALS_START 0x038
#घोषणा VL6180_ALS_GAIN 0x03f
#घोषणा VL6180_ALS_IT 0x040

/* Status रेजिस्टरs */
#घोषणा VL6180_RANGE_STATUS 0x04d
#घोषणा VL6180_ALS_STATUS 0x04e
#घोषणा VL6180_INTR_STATUS 0x04f

/* Result value रेजिस्टरs */
#घोषणा VL6180_ALS_VALUE 0x050
#घोषणा VL6180_RANGE_VALUE 0x062
#घोषणा VL6180_RANGE_RATE 0x066

/* bits of the RANGE_START and ALS_START रेजिस्टर */
#घोषणा VL6180_MODE_CONT BIT(1) /* continuous mode */
#घोषणा VL6180_STARTSTOP BIT(0) /* start measurement, स्वतः-reset */

/* bits of the INTR_STATUS and INTR_CONFIG रेजिस्टर */
#घोषणा VL6180_ALS_READY BIT(5)
#घोषणा VL6180_RANGE_READY BIT(2)

/* bits of the INTR_CLEAR रेजिस्टर */
#घोषणा VL6180_CLEAR_ERROR BIT(2)
#घोषणा VL6180_CLEAR_ALS BIT(1)
#घोषणा VL6180_CLEAR_RANGE BIT(0)

/* bits of the HOLD रेजिस्टर */
#घोषणा VL6180_HOLD_ON BIT(0)

/* शेष value क्रम the ALS_IT रेजिस्टर */
#घोषणा VL6180_ALS_IT_100 0x63 /* 100 ms */

/* values क्रम the ALS_GAIN रेजिस्टर */
#घोषणा VL6180_ALS_GAIN_1 0x46
#घोषणा VL6180_ALS_GAIN_1_25 0x45
#घोषणा VL6180_ALS_GAIN_1_67 0x44
#घोषणा VL6180_ALS_GAIN_2_5 0x43
#घोषणा VL6180_ALS_GAIN_5 0x42
#घोषणा VL6180_ALS_GAIN_10 0x41
#घोषणा VL6180_ALS_GAIN_20 0x40
#घोषणा VL6180_ALS_GAIN_40 0x47

काष्ठा vl6180_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	अचिन्हित पूर्णांक als_gain_milli;
	अचिन्हित पूर्णांक als_it_ms;
पूर्ण;

क्रमागत अणु VL6180_ALS, VL6180_RANGE, VL6180_PROX पूर्ण;

/**
 * काष्ठा vl6180_chan_regs - Registers क्रम accessing channels
 * @drdy_mask:			Data पढ़ोy bit in status रेजिस्टर
 * @start_reg:			Conversion start रेजिस्टर
 * @value_reg:			Result value रेजिस्टर
 * @word:			Register word length
 */
काष्ठा vl6180_chan_regs अणु
	u8 drdy_mask;
	u16 start_reg, value_reg;
	bool word;
पूर्ण;

अटल स्थिर काष्ठा vl6180_chan_regs vl6180_chan_regs_table[] = अणु
	[VL6180_ALS] = अणु
		.drdy_mask = VL6180_ALS_READY,
		.start_reg = VL6180_ALS_START,
		.value_reg = VL6180_ALS_VALUE,
		.word = true,
	पूर्ण,
	[VL6180_RANGE] = अणु
		.drdy_mask = VL6180_RANGE_READY,
		.start_reg = VL6180_RANGE_START,
		.value_reg = VL6180_RANGE_VALUE,
		.word = false,
	पूर्ण,
	[VL6180_PROX] = अणु
		.drdy_mask = VL6180_RANGE_READY,
		.start_reg = VL6180_RANGE_START,
		.value_reg = VL6180_RANGE_RATE,
		.word = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक vl6180_पढ़ो(काष्ठा i2c_client *client, u16 cmd, व्योम *databuf,
		       u8 len)
अणु
	__be16 cmdbuf = cpu_to_be16(cmd);
	काष्ठा i2c_msg msgs[2] = अणु
		अणु .addr = client->addr, .len = माप(cmdbuf), .buf = (u8 *) &cmdbuf पूर्ण,
		अणु .addr = client->addr, .len = len, .buf = databuf,
		  .flags = I2C_M_RD पूर्ण पूर्ण;
	पूर्णांक ret;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret < 0)
		dev_err(&client->dev, "failed reading register 0x%04x\n", cmd);

	वापस ret;
पूर्ण

अटल पूर्णांक vl6180_पढ़ो_byte(काष्ठा i2c_client *client, u16 cmd)
अणु
	u8 data;
	पूर्णांक ret;

	ret = vl6180_पढ़ो(client, cmd, &data, माप(data));
	अगर (ret < 0)
		वापस ret;

	वापस data;
पूर्ण

अटल पूर्णांक vl6180_पढ़ो_word(काष्ठा i2c_client *client, u16 cmd)
अणु
	__be16 data;
	पूर्णांक ret;

	ret = vl6180_पढ़ो(client, cmd, &data, माप(data));
	अगर (ret < 0)
		वापस ret;

	वापस be16_to_cpu(data);
पूर्ण

अटल पूर्णांक vl6180_ग_लिखो_byte(काष्ठा i2c_client *client, u16 cmd, u8 val)
अणु
	u8 buf[3];
	काष्ठा i2c_msg msgs[1] = अणु
		अणु .addr = client->addr, .len = माप(buf), .buf = (u8 *) &buf पूर्ण पूर्ण;
	पूर्णांक ret;

	buf[0] = cmd >> 8;
	buf[1] = cmd & 0xff;
	buf[2] = val;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed writing register 0x%04x\n", cmd);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vl6180_ग_लिखो_word(काष्ठा i2c_client *client, u16 cmd, u16 val)
अणु
	__be16 buf[2];
	काष्ठा i2c_msg msgs[1] = अणु
		अणु .addr = client->addr, .len = माप(buf), .buf = (u8 *) &buf पूर्ण पूर्ण;
	पूर्णांक ret;

	buf[0] = cpu_to_be16(cmd);
	buf[1] = cpu_to_be16(val);

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed writing register 0x%04x\n", cmd);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vl6180_measure(काष्ठा vl6180_data *data, पूर्णांक addr)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक tries = 20, ret;
	u16 value;

	mutex_lock(&data->lock);
	/* Start single shot measurement */
	ret = vl6180_ग_लिखो_byte(client,
		vl6180_chan_regs_table[addr].start_reg, VL6180_STARTSTOP);
	अगर (ret < 0)
		जाओ fail;

	जबतक (tries--) अणु
		ret = vl6180_पढ़ो_byte(client, VL6180_INTR_STATUS);
		अगर (ret < 0)
			जाओ fail;

		अगर (ret & vl6180_chan_regs_table[addr].drdy_mask)
			अवरोध;
		msleep(20);
	पूर्ण

	अगर (tries < 0) अणु
		ret = -EIO;
		जाओ fail;
	पूर्ण

	/* Read result value from appropriate रेजिस्टरs */
	ret = vl6180_chan_regs_table[addr].word ?
		vl6180_पढ़ो_word(client, vl6180_chan_regs_table[addr].value_reg) :
		vl6180_पढ़ो_byte(client, vl6180_chan_regs_table[addr].value_reg);
	अगर (ret < 0)
		जाओ fail;
	value = ret;

	/* Clear the पूर्णांकerrupt flag after data पढ़ो */
	ret = vl6180_ग_लिखो_byte(client, VL6180_INTR_CLEAR,
		VL6180_CLEAR_ERROR | VL6180_CLEAR_ALS | VL6180_CLEAR_RANGE);
	अगर (ret < 0)
		जाओ fail;

	ret = value;

fail:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec vl6180_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.address = VL6180_ALS,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_INT_TIME) |
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_HARDWAREGAIN),
	पूर्ण, अणु
		.type = IIO_DISTANCE,
		.address = VL6180_RANGE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण, अणु
		.type = IIO_PROXIMITY,
		.address = VL6180_PROX,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
	पूर्ण
पूर्ण;

/*
 * Available Ambient Light Sensor gain settings, 1/1000th, and
 * corresponding setting क्रम the VL6180_ALS_GAIN रेजिस्टर
 */
अटल स्थिर पूर्णांक vl6180_als_gain_tab[8] = अणु
	1000, 1250, 1670, 2500, 5000, 10000, 20000, 40000
पूर्ण;
अटल स्थिर u8 vl6180_als_gain_tab_bits[8] = अणु
	VL6180_ALS_GAIN_1,    VL6180_ALS_GAIN_1_25,
	VL6180_ALS_GAIN_1_67, VL6180_ALS_GAIN_2_5,
	VL6180_ALS_GAIN_5,    VL6180_ALS_GAIN_10,
	VL6180_ALS_GAIN_20,   VL6180_ALS_GAIN_40
पूर्ण;

अटल पूर्णांक vl6180_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा vl6180_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = vl6180_measure(data, chan->address);
		अगर (ret < 0)
			वापस ret;
		*val = ret;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_INT_TIME:
		*val = data->als_it_ms;
		*val2 = 1000;

		वापस IIO_VAL_FRACTIONAL;

	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			/* one ALS count is 0.32 Lux @ gain 1, IT 100 ms */
			*val = 32000; /* 0.32 * 1000 * 100 */
			*val2 = data->als_gain_milli * data->als_it_ms;

			वापस IIO_VAL_FRACTIONAL;

		हाल IIO_DISTANCE:
			*val = 0; /* sensor reports mm, scale to meter */
			*val2 = 1000;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		*val = data->als_gain_milli;
		*val2 = 1000;

		वापस IIO_VAL_FRACTIONAL;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल IIO_CONST_ATTR(als_gain_available, "1 1.25 1.67 2.5 5 10 20 40");

अटल काष्ठा attribute *vl6180_attributes[] = अणु
	&iio_स्थिर_attr_als_gain_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group vl6180_attribute_group = अणु
	.attrs = vl6180_attributes,
पूर्ण;

/* HOLD is needed beक्रमe updating any config रेजिस्टरs */
अटल पूर्णांक vl6180_hold(काष्ठा vl6180_data *data, bool hold)
अणु
	वापस vl6180_ग_लिखो_byte(data->client, VL6180_HOLD,
		hold ? VL6180_HOLD_ON : 0);
पूर्ण

अटल पूर्णांक vl6180_set_als_gain(काष्ठा vl6180_data *data, पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i, ret, gain;

	अगर (val < 1 || val > 40)
		वापस -EINVAL;

	gain = (val * 1000000 + val2) / 1000;
	अगर (gain < 1 || gain > 40000)
		वापस -EINVAL;

	i = find_बंदst(gain, vl6180_als_gain_tab,
			 ARRAY_SIZE(vl6180_als_gain_tab));

	mutex_lock(&data->lock);
	ret = vl6180_hold(data, true);
	अगर (ret < 0)
		जाओ fail;

	ret = vl6180_ग_लिखो_byte(data->client, VL6180_ALS_GAIN,
				vl6180_als_gain_tab_bits[i]);

	अगर (ret >= 0)
		data->als_gain_milli = vl6180_als_gain_tab[i];

fail:
	vl6180_hold(data, false);
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vl6180_set_it(काष्ठा vl6180_data *data, पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक ret, it_ms;

	it_ms = DIV_ROUND_CLOSEST(val2, 1000); /* round to ms */
	अगर (val != 0 || it_ms < 1 || it_ms > 512)
		वापस -EINVAL;

	mutex_lock(&data->lock);
	ret = vl6180_hold(data, true);
	अगर (ret < 0)
		जाओ fail;

	ret = vl6180_ग_लिखो_word(data->client, VL6180_ALS_IT, it_ms - 1);

	अगर (ret >= 0)
		data->als_it_ms = it_ms;

fail:
	vl6180_hold(data, false);
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक vl6180_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा vl6180_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_INT_TIME:
		वापस vl6180_set_it(data, val, val2);

	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		अगर (chan->type != IIO_LIGHT)
			वापस -EINVAL;

		वापस vl6180_set_als_gain(data, val, val2);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info vl6180_info = अणु
	.पढ़ो_raw = vl6180_पढ़ो_raw,
	.ग_लिखो_raw = vl6180_ग_लिखो_raw,
	.attrs = &vl6180_attribute_group,
पूर्ण;

अटल पूर्णांक vl6180_init(काष्ठा vl6180_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret;

	ret = vl6180_पढ़ो_byte(client, VL6180_MODEL_ID);
	अगर (ret < 0)
		वापस ret;

	अगर (ret != VL6180_MODEL_ID_VAL) अणु
		dev_err(&client->dev, "invalid model ID %02x\n", ret);
		वापस -ENODEV;
	पूर्ण

	ret = vl6180_hold(data, true);
	अगर (ret < 0)
		वापस ret;

	ret = vl6180_पढ़ो_byte(client, VL6180_OUT_OF_RESET);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Detect false reset condition here. This bit is always set when the
	 * प्रणाली comes out of reset.
	 */
	अगर (ret != 0x01)
		dev_info(&client->dev, "device is not fresh out of reset\n");

	/* Enable ALS and Range पढ़ोy पूर्णांकerrupts */
	ret = vl6180_ग_लिखो_byte(client, VL6180_INTR_CONFIG,
				VL6180_ALS_READY | VL6180_RANGE_READY);
	अगर (ret < 0)
		वापस ret;

	/* ALS पूर्णांकegration समय: 100ms */
	data->als_it_ms = 100;
	ret = vl6180_ग_लिखो_word(client, VL6180_ALS_IT, VL6180_ALS_IT_100);
	अगर (ret < 0)
		वापस ret;

	/* ALS gain: 1 */
	data->als_gain_milli = 1000;
	ret = vl6180_ग_लिखो_byte(client, VL6180_ALS_GAIN, VL6180_ALS_GAIN_1);
	अगर (ret < 0)
		वापस ret;

	ret = vl6180_ग_लिखो_byte(client, VL6180_OUT_OF_RESET, 0x00);
	अगर (ret < 0)
		वापस ret;

	वापस vl6180_hold(data, false);
पूर्ण

अटल पूर्णांक vl6180_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा vl6180_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	mutex_init(&data->lock);

	indio_dev->info = &vl6180_info;
	indio_dev->channels = vl6180_channels;
	indio_dev->num_channels = ARRAY_SIZE(vl6180_channels);
	indio_dev->name = VL6180_DRV_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = vl6180_init(data);
	अगर (ret < 0)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id vl6180_of_match[] = अणु
	अणु .compatible = "st,vl6180", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, vl6180_of_match);

अटल स्थिर काष्ठा i2c_device_id vl6180_id[] = अणु
	अणु "vl6180", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, vl6180_id);

अटल काष्ठा i2c_driver vl6180_driver = अणु
	.driver = अणु
		.name   = VL6180_DRV_NAME,
		.of_match_table = vl6180_of_match,
	पूर्ण,
	.probe  = vl6180_probe,
	.id_table = vl6180_id,
पूर्ण;

module_i2c_driver(vl6180_driver);

MODULE_AUTHOR("Peter Meerwald-Stadler <pmeerw@pmeerw.net>");
MODULE_AUTHOR("Manivannan Sadhasivam <manivannanece23@gmail.com>");
MODULE_DESCRIPTION("STMicro VL6180 ALS, range and proximity sensor driver");
MODULE_LICENSE("GPL");
