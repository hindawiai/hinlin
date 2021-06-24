<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Sensirion SPS30 particulate matter sensor driver
 *
 * Copyright (c) Tomasz Duszynski <tduszyns@gmail.com>
 *
 * I2C slave address: 0x69
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/crc8.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#घोषणा SPS30_CRC8_POLYNOMIAL 0x31
/* max number of bytes needed to store PM measurements or serial string */
#घोषणा SPS30_MAX_READ_SIZE 48
/* sensor measures reliably up to 3000 ug / m3 */
#घोषणा SPS30_MAX_PM 3000
/* minimum and maximum self cleaning periods in seconds */
#घोषणा SPS30_AUTO_CLEANING_PERIOD_MIN 0
#घोषणा SPS30_AUTO_CLEANING_PERIOD_MAX 604800

/* SPS30 commands */
#घोषणा SPS30_START_MEAS 0x0010
#घोषणा SPS30_STOP_MEAS 0x0104
#घोषणा SPS30_RESET 0xd304
#घोषणा SPS30_READ_DATA_READY_FLAG 0x0202
#घोषणा SPS30_READ_DATA 0x0300
#घोषणा SPS30_READ_SERIAL 0xd033
#घोषणा SPS30_START_FAN_CLEANING 0x5607
#घोषणा SPS30_AUTO_CLEANING_PERIOD 0x8004
/* not a sensor command per se, used only to distinguish ग_लिखो from पढ़ो */
#घोषणा SPS30_READ_AUTO_CLEANING_PERIOD 0x8005

क्रमागत अणु
	PM1,
	PM2P5,
	PM4,
	PM10,
पूर्ण;

क्रमागत अणु
	RESET,
	MEASURING,
पूर्ण;

काष्ठा sps30_state अणु
	काष्ठा i2c_client *client;
	/*
	 * Guards against concurrent access to sensor रेजिस्टरs.
	 * Must be held whenever sequence of commands is to be executed.
	 */
	काष्ठा mutex lock;
	पूर्णांक state;
पूर्ण;

DECLARE_CRC8_TABLE(sps30_crc8_table);

अटल पूर्णांक sps30_ग_लिखो_then_पढ़ो(काष्ठा sps30_state *state, u8 *txbuf,
				 पूर्णांक txsize, u8 *rxbuf, पूर्णांक rxsize)
अणु
	पूर्णांक ret;

	/*
	 * Sensor करोes not support repeated start so instead of
	 * sending two i2c messages in a row we just send one by one.
	 */
	ret = i2c_master_send(state->client, txbuf, txsize);
	अगर (ret != txsize)
		वापस ret < 0 ? ret : -EIO;

	अगर (!rxbuf)
		वापस 0;

	ret = i2c_master_recv(state->client, rxbuf, rxsize);
	अगर (ret != rxsize)
		वापस ret < 0 ? ret : -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक sps30_करो_cmd(काष्ठा sps30_state *state, u16 cmd, u8 *data, पूर्णांक size)
अणु
	/*
	 * Internally sensor stores measurements in a following manner:
	 *
	 * PM1: upper two bytes, crc8, lower two bytes, crc8
	 * PM2P5: upper two bytes, crc8, lower two bytes, crc8
	 * PM4: upper two bytes, crc8, lower two bytes, crc8
	 * PM10: upper two bytes, crc8, lower two bytes, crc8
	 *
	 * What follows next are number concentration measurements and
	 * typical particle size measurement which we omit.
	 */
	u8 buf[SPS30_MAX_READ_SIZE] = अणु cmd >> 8, cmd पूर्ण;
	पूर्णांक i, ret = 0;

	चयन (cmd) अणु
	हाल SPS30_START_MEAS:
		buf[2] = 0x03;
		buf[3] = 0x00;
		buf[4] = crc8(sps30_crc8_table, &buf[2], 2, CRC8_INIT_VALUE);
		ret = sps30_ग_लिखो_then_पढ़ो(state, buf, 5, शून्य, 0);
		अवरोध;
	हाल SPS30_STOP_MEAS:
	हाल SPS30_RESET:
	हाल SPS30_START_FAN_CLEANING:
		ret = sps30_ग_लिखो_then_पढ़ो(state, buf, 2, शून्य, 0);
		अवरोध;
	हाल SPS30_READ_AUTO_CLEANING_PERIOD:
		buf[0] = SPS30_AUTO_CLEANING_PERIOD >> 8;
		buf[1] = (u8)(SPS30_AUTO_CLEANING_PERIOD & 0xff);
		fallthrough;
	हाल SPS30_READ_DATA_READY_FLAG:
	हाल SPS30_READ_DATA:
	हाल SPS30_READ_SERIAL:
		/* every two data bytes are checksummed */
		size += size / 2;
		ret = sps30_ग_लिखो_then_पढ़ो(state, buf, 2, buf, size);
		अवरोध;
	हाल SPS30_AUTO_CLEANING_PERIOD:
		buf[2] = data[0];
		buf[3] = data[1];
		buf[4] = crc8(sps30_crc8_table, &buf[2], 2, CRC8_INIT_VALUE);
		buf[5] = data[2];
		buf[6] = data[3];
		buf[7] = crc8(sps30_crc8_table, &buf[5], 2, CRC8_INIT_VALUE);
		ret = sps30_ग_लिखो_then_पढ़ो(state, buf, 8, शून्य, 0);
		अवरोध;
	पूर्ण

	अगर (ret)
		वापस ret;

	/* validate received data and strip off crc bytes */
	क्रम (i = 0; i < size; i += 3) अणु
		u8 crc = crc8(sps30_crc8_table, &buf[i], 2, CRC8_INIT_VALUE);

		अगर (crc != buf[i + 2]) अणु
			dev_err(&state->client->dev,
				"data integrity check failed\n");
			वापस -EIO;
		पूर्ण

		*data++ = buf[i];
		*data++ = buf[i + 1];
	पूर्ण

	वापस 0;
पूर्ण

अटल s32 sps30_भग्न_to_पूर्णांक_clamped(स्थिर u8 *fp)
अणु
	पूर्णांक val = get_unaligned_be32(fp);
	पूर्णांक mantissa = val & GENMASK(22, 0);
	/* this is fine since passed भग्न is always non-negative */
	पूर्णांक exp = val >> 23;
	पूर्णांक fraction, shअगरt;

	/* special हाल 0 */
	अगर (!exp && !mantissa)
		वापस 0;

	exp -= 127;
	अगर (exp < 0) अणु
		/* वापस values ranging from 1 to 99 */
		वापस ((((1 << 23) + mantissa) * 100) >> 23) >> (-exp);
	पूर्ण

	/* वापस values ranging from 100 to 300000 */
	shअगरt = 23 - exp;
	val = (1 << exp) + (mantissa >> shअगरt);
	अगर (val >= SPS30_MAX_PM)
		वापस SPS30_MAX_PM * 100;

	fraction = mantissa & GENMASK(shअगरt - 1, 0);

	वापस val * 100 + ((fraction * 100) >> shअगरt);
पूर्ण

अटल पूर्णांक sps30_करो_meas(काष्ठा sps30_state *state, s32 *data, पूर्णांक size)
अणु
	पूर्णांक i, ret, tries = 5;
	u8 पंचांगp[16];

	अगर (state->state == RESET) अणु
		ret = sps30_करो_cmd(state, SPS30_START_MEAS, शून्य, 0);
		अगर (ret)
			वापस ret;

		state->state = MEASURING;
	पूर्ण

	जबतक (tries--) अणु
		ret = sps30_करो_cmd(state, SPS30_READ_DATA_READY_FLAG, पंचांगp, 2);
		अगर (ret)
			वापस -EIO;

		/* new measurements पढ़ोy to be पढ़ो */
		अगर (पंचांगp[1] == 1)
			अवरोध;

		msleep_पूर्णांकerruptible(300);
	पूर्ण

	अगर (tries == -1)
		वापस -ETIMEDOUT;

	ret = sps30_करो_cmd(state, SPS30_READ_DATA, पंचांगp, माप(पूर्णांक) * size);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < size; i++)
		data[i] = sps30_भग्न_to_पूर्णांक_clamped(&पंचांगp[4 * i]);

	वापस 0;
पूर्ण

अटल irqवापस_t sps30_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा sps30_state *state = iio_priv(indio_dev);
	पूर्णांक ret;
	काष्ठा अणु
		s32 data[4]; /* PM1, PM2P5, PM4, PM10 */
		s64 ts;
	पूर्ण scan;

	mutex_lock(&state->lock);
	ret = sps30_करो_meas(state, scan.data, ARRAY_SIZE(scan.data));
	mutex_unlock(&state->lock);
	अगर (ret)
		जाओ err;

	iio_push_to_buffers_with_बारtamp(indio_dev, &scan,
					   iio_get_समय_ns(indio_dev));
err:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sps30_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			  काष्ठा iio_chan_spec स्थिर *chan,
			  पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा sps30_state *state = iio_priv(indio_dev);
	पूर्णांक data[4], ret = -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (chan->type) अणु
		हाल IIO_MASSCONCENTRATION:
			mutex_lock(&state->lock);
			/* पढ़ो up to the number of bytes actually needed */
			चयन (chan->channel2) अणु
			हाल IIO_MOD_PM1:
				ret = sps30_करो_meas(state, data, 1);
				अवरोध;
			हाल IIO_MOD_PM2P5:
				ret = sps30_करो_meas(state, data, 2);
				अवरोध;
			हाल IIO_MOD_PM4:
				ret = sps30_करो_meas(state, data, 3);
				अवरोध;
			हाल IIO_MOD_PM10:
				ret = sps30_करो_meas(state, data, 4);
				अवरोध;
			पूर्ण
			mutex_unlock(&state->lock);
			अगर (ret)
				वापस ret;

			*val = data[chan->address] / 100;
			*val2 = (data[chan->address] % 100) * 10000;

			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_MASSCONCENTRATION:
			चयन (chan->channel2) अणु
			हाल IIO_MOD_PM1:
			हाल IIO_MOD_PM2P5:
			हाल IIO_MOD_PM4:
			हाल IIO_MOD_PM10:
				*val = 0;
				*val2 = 10000;

				वापस IIO_VAL_INT_PLUS_MICRO;
			शेष:
				वापस -EINVAL;
			पूर्ण
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sps30_करो_cmd_reset(काष्ठा sps30_state *state)
अणु
	पूर्णांक ret;

	ret = sps30_करो_cmd(state, SPS30_RESET, शून्य, 0);
	msleep(300);
	/*
	 * Power-on-reset causes sensor to produce some glitch on i2c bus and
	 * some controllers end up in error state. Recover simply by placing
	 * some data on the bus, क्रम example STOP_MEAS command, which
	 * is NOP in this हाल.
	 */
	sps30_करो_cmd(state, SPS30_STOP_MEAS, शून्य, 0);
	state->state = RESET;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार start_cleaning_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा sps30_state *state = iio_priv(indio_dev);
	पूर्णांक val, ret;

	अगर (kstrtoपूर्णांक(buf, 0, &val) || val != 1)
		वापस -EINVAL;

	mutex_lock(&state->lock);
	ret = sps30_करो_cmd(state, SPS30_START_FAN_CLEANING, शून्य, 0);
	mutex_unlock(&state->lock);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

अटल sमाप_प्रकार cleaning_period_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा sps30_state *state = iio_priv(indio_dev);
	u8 पंचांगp[4];
	पूर्णांक ret;

	mutex_lock(&state->lock);
	ret = sps30_करो_cmd(state, SPS30_READ_AUTO_CLEANING_PERIOD, पंचांगp, 4);
	mutex_unlock(&state->lock);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", get_unaligned_be32(पंचांगp));
पूर्ण

अटल sमाप_प्रकार cleaning_period_store(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा sps30_state *state = iio_priv(indio_dev);
	पूर्णांक val, ret;
	u8 पंचांगp[4];

	अगर (kstrtoपूर्णांक(buf, 0, &val))
		वापस -EINVAL;

	अगर ((val < SPS30_AUTO_CLEANING_PERIOD_MIN) ||
	    (val > SPS30_AUTO_CLEANING_PERIOD_MAX))
		वापस -EINVAL;

	put_unaligned_be32(val, पंचांगp);

	mutex_lock(&state->lock);
	ret = sps30_करो_cmd(state, SPS30_AUTO_CLEANING_PERIOD, पंचांगp, 0);
	अगर (ret) अणु
		mutex_unlock(&state->lock);
		वापस ret;
	पूर्ण

	msleep(20);

	/*
	 * sensor requires reset in order to वापस up to date self cleaning
	 * period
	 */
	ret = sps30_करो_cmd_reset(state);
	अगर (ret)
		dev_warn(dev,
			 "period changed but reads will return the old value\n");

	mutex_unlock(&state->lock);

	वापस len;
पूर्ण

अटल sमाप_प्रकार cleaning_period_available_show(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "[%d %d %d]\n",
			SPS30_AUTO_CLEANING_PERIOD_MIN, 1,
			SPS30_AUTO_CLEANING_PERIOD_MAX);
पूर्ण

अटल IIO_DEVICE_ATTR_WO(start_cleaning, 0);
अटल IIO_DEVICE_ATTR_RW(cleaning_period, 0);
अटल IIO_DEVICE_ATTR_RO(cleaning_period_available, 0);

अटल काष्ठा attribute *sps30_attrs[] = अणु
	&iio_dev_attr_start_cleaning.dev_attr.attr,
	&iio_dev_attr_cleaning_period.dev_attr.attr,
	&iio_dev_attr_cleaning_period_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group sps30_attr_group = अणु
	.attrs = sps30_attrs,
पूर्ण;

अटल स्थिर काष्ठा iio_info sps30_info = अणु
	.attrs = &sps30_attr_group,
	.पढ़ो_raw = sps30_पढ़ो_raw,
पूर्ण;

#घोषणा SPS30_CHAN(_index, _mod) अणु \
	.type = IIO_MASSCONCENTRATION, \
	.modअगरied = 1, \
	.channel2 = IIO_MOD_ ## _mod, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
	.address = _mod, \
	.scan_index = _index, \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = 19, \
		.storagebits = 32, \
		.endianness = IIO_CPU, \
	पूर्ण, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec sps30_channels[] = अणु
	SPS30_CHAN(0, PM1),
	SPS30_CHAN(1, PM2P5),
	SPS30_CHAN(2, PM4),
	SPS30_CHAN(3, PM10),
	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

अटल व्योम sps30_stop_meas(व्योम *data)
अणु
	काष्ठा sps30_state *state = data;

	sps30_करो_cmd(state, SPS30_STOP_MEAS, शून्य, 0);
पूर्ण

अटल स्थिर अचिन्हित दीर्घ sps30_scan_masks[] = अणु 0x0f, 0x00 पूर्ण;

अटल पूर्णांक sps30_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा sps30_state *state;
	u8 buf[32];
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -EOPNOTSUPP;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*state));
	अगर (!indio_dev)
		वापस -ENOMEM;

	state = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	state->client = client;
	state->state = RESET;
	indio_dev->info = &sps30_info;
	indio_dev->name = client->name;
	indio_dev->channels = sps30_channels;
	indio_dev->num_channels = ARRAY_SIZE(sps30_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->available_scan_masks = sps30_scan_masks;

	mutex_init(&state->lock);
	crc8_populate_msb(sps30_crc8_table, SPS30_CRC8_POLYNOMIAL);

	ret = sps30_करो_cmd_reset(state);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to reset device\n");
		वापस ret;
	पूर्ण

	ret = sps30_करो_cmd(state, SPS30_READ_SERIAL, buf, माप(buf));
	अगर (ret) अणु
		dev_err(&client->dev, "failed to read serial number\n");
		वापस ret;
	पूर्ण
	/* वापसed serial number is alपढ़ोy NUL terminated */
	dev_info(&client->dev, "serial number: %s\n", buf);

	ret = devm_add_action_or_reset(&client->dev, sps30_stop_meas, state);
	अगर (ret)
		वापस ret;

	ret = devm_iio_triggered_buffer_setup(&client->dev, indio_dev, शून्य,
					      sps30_trigger_handler, शून्य);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id sps30_id[] = अणु
	अणु "sps30" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sps30_id);

अटल स्थिर काष्ठा of_device_id sps30_of_match[] = अणु
	अणु .compatible = "sensirion,sps30" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sps30_of_match);

अटल काष्ठा i2c_driver sps30_driver = अणु
	.driver = अणु
		.name = "sps30",
		.of_match_table = sps30_of_match,
	पूर्ण,
	.id_table = sps30_id,
	.probe_new = sps30_probe,
पूर्ण;
module_i2c_driver(sps30_driver);

MODULE_AUTHOR("Tomasz Duszynski <tduszyns@gmail.com>");
MODULE_DESCRIPTION("Sensirion SPS30 particulate matter sensor driver");
MODULE_LICENSE("GPL v2");
