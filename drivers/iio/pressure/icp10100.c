<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2020 InvenSense, Inc.
 *
 * Driver क्रम InvenSense ICP-1010xx barometric pressure and temperature sensor.
 *
 * Datasheet:
 * http://www.invensense.com/wp-content/uploads/2018/01/DS-000186-ICP-101xx-v1.2.pdf
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/crc8.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/log2.h>
#समावेश <linux/math64.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/iio/iपन.स>

#घोषणा ICP10100_ID_REG_GET(_reg)	((_reg) & 0x003F)
#घोषणा ICP10100_ID_REG			0x08
#घोषणा ICP10100_RESPONSE_WORD_LENGTH	3
#घोषणा ICP10100_CRC8_WORD_LENGTH	2
#घोषणा ICP10100_CRC8_POLYNOMIAL	0x31
#घोषणा ICP10100_CRC8_INIT		0xFF

क्रमागत icp10100_mode अणु
	ICP10100_MODE_LP,	/* Low घातer mode: 1x sampling */
	ICP10100_MODE_N,	/* Normal mode: 2x sampling */
	ICP10100_MODE_LN,	/* Low noise mode: 4x sampling */
	ICP10100_MODE_ULN,	/* Ultra low noise mode: 8x sampling */
	ICP10100_MODE_NB,
पूर्ण;

काष्ठा icp10100_state अणु
	काष्ठा mutex lock;
	काष्ठा i2c_client *client;
	काष्ठा regulator *vdd;
	क्रमागत icp10100_mode mode;
	पूर्णांक16_t cal[4];
पूर्ण;

काष्ठा icp10100_command अणु
	__be16 cmd;
	अचिन्हित दीर्घ रुको_us;
	अचिन्हित दीर्घ रुको_max_us;
	माप_प्रकार response_word_nb;
पूर्ण;

अटल स्थिर काष्ठा icp10100_command icp10100_cmd_soft_reset = अणु
	.cmd = cpu_to_be16(0x805D),
	.रुको_us = 170,
	.रुको_max_us = 200,
	.response_word_nb = 0,
पूर्ण;

अटल स्थिर काष्ठा icp10100_command icp10100_cmd_पढ़ो_id = अणु
	.cmd = cpu_to_be16(0xEFC8),
	.रुको_us = 0,
	.response_word_nb = 1,
पूर्ण;

अटल स्थिर काष्ठा icp10100_command icp10100_cmd_पढ़ो_otp = अणु
	.cmd = cpu_to_be16(0xC7F7),
	.रुको_us = 0,
	.response_word_nb = 1,
पूर्ण;

अटल स्थिर काष्ठा icp10100_command icp10100_cmd_measure[] = अणु
	[ICP10100_MODE_LP] = अणु
		.cmd = cpu_to_be16(0x401A),
		.रुको_us = 1800,
		.रुको_max_us = 2000,
		.response_word_nb = 3,
	पूर्ण,
	[ICP10100_MODE_N] = अणु
		.cmd = cpu_to_be16(0x48A3),
		.रुको_us = 6300,
		.रुको_max_us = 6500,
		.response_word_nb = 3,
	पूर्ण,
	[ICP10100_MODE_LN] = अणु
		.cmd = cpu_to_be16(0x5059),
		.रुको_us = 23800,
		.रुको_max_us = 24000,
		.response_word_nb = 3,
	पूर्ण,
	[ICP10100_MODE_ULN] = अणु
		.cmd = cpu_to_be16(0x58E0),
		.रुको_us = 94500,
		.रुको_max_us = 94700,
		.response_word_nb = 3,
	पूर्ण,
पूर्ण;

अटल स्थिर uपूर्णांक8_t icp10100_चयन_mode_otp[] =
	अणु0xC5, 0x95, 0x00, 0x66, 0x9cपूर्ण;

DECLARE_CRC8_TABLE(icp10100_crc8_table);

अटल अंतरभूत पूर्णांक icp10100_i2c_xfer(काष्ठा i2c_adapter *adap,
				    काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	पूर्णांक ret;

	ret = i2c_transfer(adap, msgs, num);
	अगर (ret < 0)
		वापस ret;

	अगर (ret != num)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक icp10100_send_cmd(काष्ठा icp10100_state *st,
			     स्थिर काष्ठा icp10100_command *cmd,
			     __be16 *buf, माप_प्रकार buf_len)
अणु
	माप_प्रकार size = cmd->response_word_nb * ICP10100_RESPONSE_WORD_LENGTH;
	uपूर्णांक8_t data[16];
	uपूर्णांक8_t *ptr;
	uपूर्णांक8_t *buf_ptr = (uपूर्णांक8_t *)buf;
	काष्ठा i2c_msg msgs[2] = अणु
		अणु
			.addr = st->client->addr,
			.flags = 0,
			.len = 2,
			.buf = (uपूर्णांक8_t *)&cmd->cmd,
		पूर्ण, अणु
			.addr = st->client->addr,
			.flags = I2C_M_RD,
			.len = size,
			.buf = data,
		पूर्ण,
	पूर्ण;
	uपूर्णांक8_t crc;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (size > माप(data))
		वापस -EINVAL;

	अगर (cmd->response_word_nb > 0 &&
			(buf == शून्य || buf_len < (cmd->response_word_nb * 2)))
		वापस -EINVAL;

	dev_dbg(&st->client->dev, "sending cmd %#x\n", be16_to_cpu(cmd->cmd));

	अगर (cmd->response_word_nb > 0 && cmd->रुको_us == 0) अणु
		/* direct command-response without रुकोing */
		ret = icp10100_i2c_xfer(st->client->adapter, msgs,
					ARRAY_SIZE(msgs));
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		/* transfer command ग_लिखो */
		ret = icp10100_i2c_xfer(st->client->adapter, &msgs[0], 1);
		अगर (ret)
			वापस ret;
		अगर (cmd->रुको_us > 0)
			usleep_range(cmd->रुको_us, cmd->रुको_max_us);
		/* transfer response पढ़ो अगर needed */
		अगर (cmd->response_word_nb > 0) अणु
			ret = icp10100_i2c_xfer(st->client->adapter, &msgs[1], 1);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण
	पूर्ण

	/* process पढ़ो words with crc checking */
	क्रम (i = 0; i < cmd->response_word_nb; ++i) अणु
		ptr = &data[i * ICP10100_RESPONSE_WORD_LENGTH];
		crc = crc8(icp10100_crc8_table, ptr, ICP10100_CRC8_WORD_LENGTH,
			   ICP10100_CRC8_INIT);
		अगर (crc != ptr[ICP10100_CRC8_WORD_LENGTH]) अणु
			dev_err(&st->client->dev, "crc error recv=%#x calc=%#x\n",
				ptr[ICP10100_CRC8_WORD_LENGTH], crc);
			वापस -EIO;
		पूर्ण
		*buf_ptr++ = ptr[0];
		*buf_ptr++ = ptr[1];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक icp10100_पढ़ो_cal_otp(काष्ठा icp10100_state *st)
अणु
	__be16 val;
	पूर्णांक i;
	पूर्णांक ret;

	/* चयन पूर्णांकo OTP पढ़ो mode */
	ret = i2c_master_send(st->client, icp10100_चयन_mode_otp,
			      ARRAY_SIZE(icp10100_चयन_mode_otp));
	अगर (ret < 0)
		वापस ret;
	अगर (ret != ARRAY_SIZE(icp10100_चयन_mode_otp))
		वापस -EIO;

	/* पढ़ो 4 calibration values */
	क्रम (i = 0; i < 4; ++i) अणु
		ret = icp10100_send_cmd(st, &icp10100_cmd_पढ़ो_otp,
					&val, माप(val));
		अगर (ret)
			वापस ret;
		st->cal[i] = be16_to_cpu(val);
		dev_dbg(&st->client->dev, "cal[%d] = %d\n", i, st->cal[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक icp10100_init_chip(काष्ठा icp10100_state *st)
अणु
	__be16 val;
	uपूर्णांक16_t id;
	पूर्णांक ret;

	/* पढ़ो and check id */
	ret = icp10100_send_cmd(st, &icp10100_cmd_पढ़ो_id, &val, माप(val));
	अगर (ret)
		वापस ret;
	id = ICP10100_ID_REG_GET(be16_to_cpu(val));
	अगर (id != ICP10100_ID_REG) अणु
		dev_err(&st->client->dev, "invalid id %#x\n", id);
		वापस -ENODEV;
	पूर्ण

	/* पढ़ो calibration data from OTP */
	ret = icp10100_पढ़ो_cal_otp(st);
	अगर (ret)
		वापस ret;

	/* reset chip */
	वापस icp10100_send_cmd(st, &icp10100_cmd_soft_reset, शून्य, 0);
पूर्ण

अटल पूर्णांक icp10100_get_measures(काष्ठा icp10100_state *st,
				uपूर्णांक32_t *pressure, uपूर्णांक16_t *temperature)
अणु
	स्थिर काष्ठा icp10100_command *cmd;
	__be16 measures[3];
	पूर्णांक ret;

	pm_runसमय_get_sync(&st->client->dev);

	mutex_lock(&st->lock);
	cmd = &icp10100_cmd_measure[st->mode];
	ret = icp10100_send_cmd(st, cmd, measures, माप(measures));
	mutex_unlock(&st->lock);
	अगर (ret)
		जाओ error_measure;

	*pressure = (be16_to_cpu(measures[0]) << 8) |
			(be16_to_cpu(measures[1]) >> 8);
	*temperature = be16_to_cpu(measures[2]);

	pm_runसमय_mark_last_busy(&st->client->dev);
error_measure:
	pm_runसमय_put_स्वतःsuspend(&st->client->dev);
	वापस ret;
पूर्ण

अटल uपूर्णांक32_t icp10100_get_pressure(काष्ठा icp10100_state *st,
				      uपूर्णांक32_t raw_pressure, uपूर्णांक16_t raw_temp)
अणु
	अटल पूर्णांक32_t p_calib[] = अणु45000, 80000, 105000पूर्ण;
	अटल पूर्णांक32_t lut_lower = 3670016;
	अटल पूर्णांक32_t lut_upper = 12058624;
	अटल पूर्णांक32_t inv_quadr_factor = 16777216;
	अटल पूर्णांक32_t offset_factor = 2048;
	पूर्णांक64_t val1, val2;
	पूर्णांक32_t p_lut[3];
	पूर्णांक32_t t, t_square;
	पूर्णांक64_t a, b, c;
	uपूर्णांक32_t pressure_mPa;

	dev_dbg(&st->client->dev, "raw: pressure = %u, temp = %u\n",
		raw_pressure, raw_temp);

	/* compute p_lut values */
	t = (पूर्णांक32_t)raw_temp - 32768;
	t_square = t * t;
	val1 = (पूर्णांक64_t)st->cal[0] * (पूर्णांक64_t)t_square;
	p_lut[0] = lut_lower + (पूर्णांक32_t)भाग_s64(val1, inv_quadr_factor);
	val1 = (पूर्णांक64_t)st->cal[1] * (पूर्णांक64_t)t_square;
	p_lut[1] = offset_factor * st->cal[3] +
			(पूर्णांक32_t)भाग_s64(val1, inv_quadr_factor);
	val1 = (पूर्णांक64_t)st->cal[2] * (पूर्णांक64_t)t_square;
	p_lut[2] = lut_upper + (पूर्णांक32_t)भाग_s64(val1, inv_quadr_factor);
	dev_dbg(&st->client->dev, "p_lut = [%d, %d, %d]\n",
		p_lut[0], p_lut[1], p_lut[2]);

	/* compute a, b, c factors */
	val1 = (पूर्णांक64_t)p_lut[0] * (पूर्णांक64_t)p_lut[1] *
			(पूर्णांक64_t)(p_calib[0] - p_calib[1]) +
		(पूर्णांक64_t)p_lut[1] * (पूर्णांक64_t)p_lut[2] *
			(पूर्णांक64_t)(p_calib[1] - p_calib[2]) +
		(पूर्णांक64_t)p_lut[2] * (पूर्णांक64_t)p_lut[0] *
			(पूर्णांक64_t)(p_calib[2] - p_calib[0]);
	val2 = (पूर्णांक64_t)p_lut[2] * (पूर्णांक64_t)(p_calib[0] - p_calib[1]) +
		(पूर्णांक64_t)p_lut[0] * (पूर्णांक64_t)(p_calib[1] - p_calib[2]) +
		(पूर्णांक64_t)p_lut[1] * (पूर्णांक64_t)(p_calib[2] - p_calib[0]);
	c = भाग64_s64(val1, val2);
	dev_dbg(&st->client->dev, "val1 = %lld, val2 = %lld, c = %lld\n",
		val1, val2, c);
	val1 = (पूर्णांक64_t)p_calib[0] * (पूर्णांक64_t)p_lut[0] -
		(पूर्णांक64_t)p_calib[1] * (पूर्णांक64_t)p_lut[1] -
		(पूर्णांक64_t)(p_calib[1] - p_calib[0]) * c;
	val2 = (पूर्णांक64_t)p_lut[0] - (पूर्णांक64_t)p_lut[1];
	a = भाग64_s64(val1, val2);
	dev_dbg(&st->client->dev, "val1 = %lld, val2 = %lld, a = %lld\n",
		val1, val2, a);
	b = ((पूर्णांक64_t)p_calib[0] - a) * ((पूर्णांक64_t)p_lut[0] + c);
	dev_dbg(&st->client->dev, "b = %lld\n", b);

	/*
	 * pressure_Pa = a + (b / (c + raw_pressure))
	 * pressure_mPa = 1000 * pressure_Pa
	 */
	pressure_mPa = 1000LL * a + भाग64_s64(1000LL * b, c + raw_pressure);

	वापस pressure_mPa;
पूर्ण

अटल पूर्णांक icp10100_पढ़ो_raw_measures(काष्ठा iio_dev *indio_dev,
				      काष्ठा iio_chan_spec स्थिर *chan,
				      पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा icp10100_state *st = iio_priv(indio_dev);
	uपूर्णांक32_t raw_pressure;
	uपूर्णांक16_t raw_temp;
	uपूर्णांक32_t pressure_mPa;
	पूर्णांक ret;

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret)
		वापस ret;

	ret = icp10100_get_measures(st, &raw_pressure, &raw_temp);
	अगर (ret)
		जाओ error_release;

	चयन (chan->type) अणु
	हाल IIO_PRESSURE:
		pressure_mPa = icp10100_get_pressure(st, raw_pressure,
						     raw_temp);
		/* mPa to kPa */
		*val = pressure_mPa / 1000000;
		*val2 = pressure_mPa % 1000000;
		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;
	हाल IIO_TEMP:
		*val = raw_temp;
		ret = IIO_VAL_INT;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

error_release:
	iio_device_release_direct_mode(indio_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक icp10100_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा icp10100_state *st = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
	हाल IIO_CHAN_INFO_PROCESSED:
		वापस icp10100_पढ़ो_raw_measures(indio_dev, chan, val, val2);
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			/* 1000 * 175तओC / 65536 in mतओC */
			*val = 2;
			*val2 = 670288;
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_OFFSET:
		चयन (chan->type) अणु
		हाल IIO_TEMP:
			/* 1000 * -45तओC in mतओC */
			*val = -45000;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		mutex_lock(&st->lock);
		*val = 1 << st->mode;
		mutex_unlock(&st->lock);
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक icp10100_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
			       दीर्घ mask)
अणु
	अटल पूर्णांक oversamplings[] = अणु1, 2, 4, 8पूर्ण;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		*vals = oversamplings;
		*type = IIO_VAL_INT;
		*length = ARRAY_SIZE(oversamplings);
		वापस IIO_AVAIL_LIST;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक icp10100_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा icp10100_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक mode;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		/* oversampling is always positive and a घातer of 2 */
		अगर (val <= 0 || !is_घातer_of_2(val))
			वापस -EINVAL;
		mode = ilog2(val);
		अगर (mode >= ICP10100_MODE_NB)
			वापस -EINVAL;
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		mutex_lock(&st->lock);
		st->mode = mode;
		mutex_unlock(&st->lock);
		iio_device_release_direct_mode(indio_dev);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक icp10100_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
				      काष्ठा iio_chan_spec स्थिर *chan,
				      दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info icp10100_info = अणु
	.पढ़ो_raw = icp10100_पढ़ो_raw,
	.पढ़ो_avail = icp10100_पढ़ो_avail,
	.ग_लिखो_raw = icp10100_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = icp10100_ग_लिखो_raw_get_fmt,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec icp10100_channels[] = अणु
	अणु
		.type = IIO_PRESSURE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.info_mask_shared_by_all =
			BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),
		.info_mask_shared_by_all_available =
			BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),
	पूर्ण, अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.info_mask_shared_by_all =
			BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),
		.info_mask_shared_by_all_available =
			BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO),
	पूर्ण,
पूर्ण;

अटल पूर्णांक icp10100_enable_regulator(काष्ठा icp10100_state *st)
अणु
	पूर्णांक ret;

	ret = regulator_enable(st->vdd);
	अगर (ret)
		वापस ret;
	msleep(100);

	वापस 0;
पूर्ण

अटल व्योम icp10100_disable_regulator_action(व्योम *data)
अणु
	काष्ठा icp10100_state *st = data;
	पूर्णांक ret;

	ret = regulator_disable(st->vdd);
	अगर (ret)
		dev_err(&st->client->dev, "error %d disabling vdd\n", ret);
पूर्ण

अटल व्योम icp10100_pm_disable(व्योम *data)
अणु
	काष्ठा device *dev = data;

	pm_runसमय_put_sync_suspend(dev);
	pm_runसमय_disable(dev);
पूर्ण

अटल पूर्णांक icp10100_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा icp10100_state *st;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "plain i2c transactions not supported\n");
		वापस -ENODEV;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	i2c_set_clientdata(client, indio_dev);
	indio_dev->name = client->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = icp10100_channels;
	indio_dev->num_channels = ARRAY_SIZE(icp10100_channels);
	indio_dev->info = &icp10100_info;

	st = iio_priv(indio_dev);
	mutex_init(&st->lock);
	st->client = client;
	st->mode = ICP10100_MODE_N;

	st->vdd = devm_regulator_get(&client->dev, "vdd");
	अगर (IS_ERR(st->vdd))
		वापस PTR_ERR(st->vdd);

	ret = icp10100_enable_regulator(st);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(&client->dev,
				       icp10100_disable_regulator_action, st);
	अगर (ret)
		वापस ret;

	/* has to be करोne beक्रमe the first i2c communication */
	crc8_populate_msb(icp10100_crc8_table, ICP10100_CRC8_POLYNOMIAL);

	ret = icp10100_init_chip(st);
	अगर (ret) अणु
		dev_err(&client->dev, "init chip error %d\n", ret);
		वापस ret;
	पूर्ण

	/* enable runसमय pm with स्वतःsuspend delay of 2s */
	pm_runसमय_get_noresume(&client->dev);
	pm_runसमय_set_active(&client->dev);
	pm_runसमय_enable(&client->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&client->dev, 2000);
	pm_runसमय_use_स्वतःsuspend(&client->dev);
	pm_runसमय_put(&client->dev);
	ret = devm_add_action_or_reset(&client->dev, icp10100_pm_disable,
				       &client->dev);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल पूर्णांक __maybe_unused icp10100_suspend(काष्ठा device *dev)
अणु
	काष्ठा icp10100_state *st = iio_priv(dev_get_drvdata(dev));
	पूर्णांक ret;

	mutex_lock(&st->lock);
	ret = regulator_disable(st->vdd);
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused icp10100_resume(काष्ठा device *dev)
अणु
	काष्ठा icp10100_state *st = iio_priv(dev_get_drvdata(dev));
	पूर्णांक ret;

	mutex_lock(&st->lock);

	ret = icp10100_enable_regulator(st);
	अगर (ret)
		जाओ out_unlock;

	/* reset chip */
	ret = icp10100_send_cmd(st, &icp10100_cmd_soft_reset, शून्य, 0);

out_unlock:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

अटल UNIVERSAL_DEV_PM_OPS(icp10100_pm, icp10100_suspend, icp10100_resume,
			    शून्य);

अटल स्थिर काष्ठा of_device_id icp10100_of_match[] = अणु
	अणु
		.compatible = "invensense,icp10100",
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, icp10100_of_match);

अटल स्थिर काष्ठा i2c_device_id icp10100_id[] = अणु
	अणु "icp10100", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, icp10100_id);

अटल काष्ठा i2c_driver icp10100_driver = अणु
	.driver = अणु
		.name = "icp10100",
		.pm = &icp10100_pm,
		.of_match_table = icp10100_of_match,
	पूर्ण,
	.probe = icp10100_probe,
	.id_table = icp10100_id,
पूर्ण;
module_i2c_driver(icp10100_driver);

MODULE_AUTHOR("InvenSense, Inc.");
MODULE_DESCRIPTION("InvenSense icp10100 driver");
MODULE_LICENSE("GPL");
