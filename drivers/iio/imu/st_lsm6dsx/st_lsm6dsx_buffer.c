<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics st_lsm6dsx FIFO buffer library driver
 *
 * LSM6DS3/LSM6DS3H/LSM6DSL/LSM6DSM/ISM330DLC/LSM6DS3TR-C:
 * The FIFO buffer can be configured to store data from gyroscope and
 * accelerometer. Samples are queued without any tag according to a
 * specअगरic pattern based on 'FIFO data sets' (6 bytes each):
 *  - 1st data set is reserved क्रम gyroscope data
 *  - 2nd data set is reserved क्रम accelerometer data
 * The FIFO pattern changes depending on the ODRs and decimation factors
 * asचिन्हित to the FIFO data sets. The first sequence of data stored in FIFO
 * buffer contains the data of all the enabled FIFO data sets
 * (e.g. Gx, Gy, Gz, Ax, Ay, Az), then data are repeated depending on the
 * value of the decimation factor and ODR set क्रम each FIFO data set.
 *
 * LSM6DSO/LSM6DSOX/ASM330LHH/LSM6DSR/LSM6DSRX/ISM330DHCX/LSM6DST/LSM6DSOP:
 * The FIFO buffer can be configured to store data from gyroscope and
 * accelerometer. Each sample is queued with a tag (1B) indicating data
 * source (gyroscope, accelerometer, hw समयr).
 *
 * FIFO supported modes:
 *  - BYPASS: FIFO disabled
 *  - CONTINUOUS: FIFO enabled. When the buffer is full, the FIFO index
 *    restarts from the beginning and the oldest sample is overwritten
 *
 * Copyright 2016 STMicroelectronics Inc.
 *
 * Lorenzo Bianconi <lorenzo.bianconi@st.com>
 * Denis Ciocca <denis.ciocca@st.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/iio/kfअगरo_buf.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/regmap.h>
#समावेश <linux/bitfield.h>

#समावेश <linux/platक्रमm_data/st_sensors_pdata.h>

#समावेश "st_lsm6dsx.h"

#घोषणा ST_LSM6DSX_REG_FIFO_MODE_ADDR		0x0a
#घोषणा ST_LSM6DSX_FIFO_MODE_MASK		GENMASK(2, 0)
#घोषणा ST_LSM6DSX_FIFO_ODR_MASK		GENMASK(6, 3)
#घोषणा ST_LSM6DSX_FIFO_EMPTY_MASK		BIT(12)
#घोषणा ST_LSM6DSX_REG_FIFO_OUTL_ADDR		0x3e
#घोषणा ST_LSM6DSX_REG_FIFO_OUT_TAG_ADDR	0x78
#घोषणा ST_LSM6DSX_REG_TS_RESET_ADDR		0x42

#घोषणा ST_LSM6DSX_MAX_FIFO_ODR_VAL		0x08

#घोषणा ST_LSM6DSX_TS_RESET_VAL			0xaa

काष्ठा st_lsm6dsx_decimator_entry अणु
	u8 decimator;
	u8 val;
पूर्ण;

क्रमागत st_lsm6dsx_fअगरo_tag अणु
	ST_LSM6DSX_GYRO_TAG = 0x01,
	ST_LSM6DSX_ACC_TAG = 0x02,
	ST_LSM6DSX_TS_TAG = 0x04,
	ST_LSM6DSX_EXT0_TAG = 0x0f,
	ST_LSM6DSX_EXT1_TAG = 0x10,
	ST_LSM6DSX_EXT2_TAG = 0x11,
पूर्ण;

अटल स्थिर
काष्ठा st_lsm6dsx_decimator_entry st_lsm6dsx_decimator_table[] = अणु
	अणु  0, 0x0 पूर्ण,
	अणु  1, 0x1 पूर्ण,
	अणु  2, 0x2 पूर्ण,
	अणु  3, 0x3 पूर्ण,
	अणु  4, 0x4 पूर्ण,
	अणु  8, 0x5 पूर्ण,
	अणु 16, 0x6 पूर्ण,
	अणु 32, 0x7 पूर्ण,
पूर्ण;

अटल पूर्णांक
st_lsm6dsx_get_decimator_val(काष्ठा st_lsm6dsx_sensor *sensor, u32 max_odr)
अणु
	स्थिर पूर्णांक max_size = ARRAY_SIZE(st_lsm6dsx_decimator_table);
	u32 decimator =  max_odr / sensor->odr;
	पूर्णांक i;

	अगर (decimator > 1)
		decimator = round_करोwn(decimator, 2);

	क्रम (i = 0; i < max_size; i++) अणु
		अगर (st_lsm6dsx_decimator_table[i].decimator == decimator)
			अवरोध;
	पूर्ण

	sensor->decimator = decimator;
	वापस i == max_size ? 0 : st_lsm6dsx_decimator_table[i].val;
पूर्ण

अटल व्योम st_lsm6dsx_get_max_min_odr(काष्ठा st_lsm6dsx_hw *hw,
				       u32 *max_odr, u32 *min_odr)
अणु
	काष्ठा st_lsm6dsx_sensor *sensor;
	पूर्णांक i;

	*max_odr = 0, *min_odr = ~0;
	क्रम (i = 0; i < ST_LSM6DSX_ID_MAX; i++) अणु
		अगर (!hw->iio_devs[i])
			जारी;

		sensor = iio_priv(hw->iio_devs[i]);

		अगर (!(hw->enable_mask & BIT(sensor->id)))
			जारी;

		*max_odr = max_t(u32, *max_odr, sensor->odr);
		*min_odr = min_t(u32, *min_odr, sensor->odr);
	पूर्ण
पूर्ण

अटल u8 st_lsm6dsx_get_sip(काष्ठा st_lsm6dsx_sensor *sensor, u32 min_odr)
अणु
	u8 sip = sensor->odr / min_odr;

	वापस sip > 1 ? round_करोwn(sip, 2) : sip;
पूर्ण

अटल पूर्णांक st_lsm6dsx_update_decimators(काष्ठा st_lsm6dsx_hw *hw)
अणु
	स्थिर काष्ठा st_lsm6dsx_reg *ts_dec_reg;
	काष्ठा st_lsm6dsx_sensor *sensor;
	u16 sip = 0, ts_sip = 0;
	u32 max_odr, min_odr;
	पूर्णांक err = 0, i;
	u8 data;

	st_lsm6dsx_get_max_min_odr(hw, &max_odr, &min_odr);

	क्रम (i = 0; i < ST_LSM6DSX_ID_MAX; i++) अणु
		स्थिर काष्ठा st_lsm6dsx_reg *dec_reg;

		अगर (!hw->iio_devs[i])
			जारी;

		sensor = iio_priv(hw->iio_devs[i]);
		/* update fअगरo decimators and sample in pattern */
		अगर (hw->enable_mask & BIT(sensor->id)) अणु
			sensor->sip = st_lsm6dsx_get_sip(sensor, min_odr);
			data = st_lsm6dsx_get_decimator_val(sensor, max_odr);
		पूर्ण अन्यथा अणु
			sensor->sip = 0;
			data = 0;
		पूर्ण
		ts_sip = max_t(u16, ts_sip, sensor->sip);

		dec_reg = &hw->settings->decimator[sensor->id];
		अगर (dec_reg->addr) अणु
			पूर्णांक val = ST_LSM6DSX_SHIFT_VAL(data, dec_reg->mask);

			err = st_lsm6dsx_update_bits_locked(hw, dec_reg->addr,
							    dec_reg->mask,
							    val);
			अगर (err < 0)
				वापस err;
		पूर्ण
		sip += sensor->sip;
	पूर्ण
	hw->sip = sip + ts_sip;
	hw->ts_sip = ts_sip;

	/*
	 * update hw ts decimator अगर necessary. Decimator क्रम hw बारtamp
	 * is always 1 or 0 in order to have a ts sample क्रम each data
	 * sample in FIFO
	 */
	ts_dec_reg = &hw->settings->ts_settings.decimator;
	अगर (ts_dec_reg->addr) अणु
		पूर्णांक val, ts_dec = !!hw->ts_sip;

		val = ST_LSM6DSX_SHIFT_VAL(ts_dec, ts_dec_reg->mask);
		err = st_lsm6dsx_update_bits_locked(hw, ts_dec_reg->addr,
						    ts_dec_reg->mask, val);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक st_lsm6dsx_set_fअगरo_mode(काष्ठा st_lsm6dsx_hw *hw,
				    क्रमागत st_lsm6dsx_fअगरo_mode fअगरo_mode)
अणु
	अचिन्हित पूर्णांक data;

	data = FIELD_PREP(ST_LSM6DSX_FIFO_MODE_MASK, fअगरo_mode);
	वापस st_lsm6dsx_update_bits_locked(hw, ST_LSM6DSX_REG_FIFO_MODE_ADDR,
					     ST_LSM6DSX_FIFO_MODE_MASK, data);
पूर्ण

अटल पूर्णांक st_lsm6dsx_set_fअगरo_odr(काष्ठा st_lsm6dsx_sensor *sensor,
				   bool enable)
अणु
	काष्ठा st_lsm6dsx_hw *hw = sensor->hw;
	स्थिर काष्ठा st_lsm6dsx_reg *batch_reg;
	u8 data;

	batch_reg = &hw->settings->batch[sensor->id];
	अगर (batch_reg->addr) अणु
		पूर्णांक val;

		अगर (enable) अणु
			पूर्णांक err;

			err = st_lsm6dsx_check_odr(sensor, sensor->odr,
						   &data);
			अगर (err < 0)
				वापस err;
		पूर्ण अन्यथा अणु
			data = 0;
		पूर्ण
		val = ST_LSM6DSX_SHIFT_VAL(data, batch_reg->mask);
		वापस st_lsm6dsx_update_bits_locked(hw, batch_reg->addr,
						     batch_reg->mask, val);
	पूर्ण अन्यथा अणु
		data = hw->enable_mask ? ST_LSM6DSX_MAX_FIFO_ODR_VAL : 0;
		वापस st_lsm6dsx_update_bits_locked(hw,
					ST_LSM6DSX_REG_FIFO_MODE_ADDR,
					ST_LSM6DSX_FIFO_ODR_MASK,
					FIELD_PREP(ST_LSM6DSX_FIFO_ODR_MASK,
						   data));
	पूर्ण
पूर्ण

पूर्णांक st_lsm6dsx_update_watermark(काष्ठा st_lsm6dsx_sensor *sensor, u16 watermark)
अणु
	u16 fअगरo_watermark = ~0, cur_watermark, fअगरo_th_mask;
	काष्ठा st_lsm6dsx_hw *hw = sensor->hw;
	काष्ठा st_lsm6dsx_sensor *cur_sensor;
	पूर्णांक i, err, data;
	__le16 wdata;

	अगर (!hw->sip)
		वापस 0;

	क्रम (i = 0; i < ST_LSM6DSX_ID_MAX; i++) अणु
		अगर (!hw->iio_devs[i])
			जारी;

		cur_sensor = iio_priv(hw->iio_devs[i]);

		अगर (!(hw->enable_mask & BIT(cur_sensor->id)))
			जारी;

		cur_watermark = (cur_sensor == sensor) ? watermark
						       : cur_sensor->watermark;

		fअगरo_watermark = min_t(u16, fअगरo_watermark, cur_watermark);
	पूर्ण

	fअगरo_watermark = max_t(u16, fअगरo_watermark, hw->sip);
	fअगरo_watermark = (fअगरo_watermark / hw->sip) * hw->sip;
	fअगरo_watermark = fअगरo_watermark * hw->settings->fअगरo_ops.th_wl;

	mutex_lock(&hw->page_lock);
	err = regmap_पढ़ो(hw->regmap, hw->settings->fअगरo_ops.fअगरo_th.addr + 1,
			  &data);
	अगर (err < 0)
		जाओ out;

	fअगरo_th_mask = hw->settings->fअगरo_ops.fअगरo_th.mask;
	fअगरo_watermark = ((data << 8) & ~fअगरo_th_mask) |
			 (fअगरo_watermark & fअगरo_th_mask);

	wdata = cpu_to_le16(fअगरo_watermark);
	err = regmap_bulk_ग_लिखो(hw->regmap,
				hw->settings->fअगरo_ops.fअगरo_th.addr,
				&wdata, माप(wdata));
out:
	mutex_unlock(&hw->page_lock);
	वापस err;
पूर्ण

अटल पूर्णांक st_lsm6dsx_reset_hw_ts(काष्ठा st_lsm6dsx_hw *hw)
अणु
	काष्ठा st_lsm6dsx_sensor *sensor;
	पूर्णांक i, err;

	/* reset hw ts counter */
	err = st_lsm6dsx_ग_लिखो_locked(hw, ST_LSM6DSX_REG_TS_RESET_ADDR,
				      ST_LSM6DSX_TS_RESET_VAL);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i < ST_LSM6DSX_ID_MAX; i++) अणु
		अगर (!hw->iio_devs[i])
			जारी;

		sensor = iio_priv(hw->iio_devs[i]);
		/*
		 * store enable buffer बारtamp as reference क्रम
		 * hw बारtamp
		 */
		sensor->ts_ref = iio_get_समय_ns(hw->iio_devs[i]);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक st_lsm6dsx_resume_fअगरo(काष्ठा st_lsm6dsx_hw *hw)
अणु
	पूर्णांक err;

	/* reset hw ts counter */
	err = st_lsm6dsx_reset_hw_ts(hw);
	अगर (err < 0)
		वापस err;

	वापस st_lsm6dsx_set_fअगरo_mode(hw, ST_LSM6DSX_FIFO_CONT);
पूर्ण

/*
 * Set max bulk पढ़ो to ST_LSM6DSX_MAX_WORD_LEN/ST_LSM6DSX_MAX_TAGGED_WORD_LEN
 * in order to aव्योम a kदो_स्मृति क्रम each bus access
 */
अटल अंतरभूत पूर्णांक st_lsm6dsx_पढ़ो_block(काष्ठा st_lsm6dsx_hw *hw, u8 addr,
					u8 *data, अचिन्हित पूर्णांक data_len,
					अचिन्हित पूर्णांक max_word_len)
अणु
	अचिन्हित पूर्णांक word_len, पढ़ो_len = 0;
	पूर्णांक err;

	जबतक (पढ़ो_len < data_len) अणु
		word_len = min_t(अचिन्हित पूर्णांक, data_len - पढ़ो_len,
				 max_word_len);
		err = st_lsm6dsx_पढ़ो_locked(hw, addr, data + पढ़ो_len,
					     word_len);
		अगर (err < 0)
			वापस err;
		पढ़ो_len += word_len;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा ST_LSM6DSX_IIO_BUFF_SIZE	(ALIGN(ST_LSM6DSX_SAMPLE_SIZE, \
					       माप(s64)) + माप(s64))
/**
 * st_lsm6dsx_पढ़ो_fअगरo() - hw FIFO पढ़ो routine
 * @hw: Poपूर्णांकer to instance of काष्ठा st_lsm6dsx_hw.
 *
 * Read samples from the hw FIFO and push them to IIO buffers.
 *
 * Return: Number of bytes पढ़ो from the FIFO
 */
पूर्णांक st_lsm6dsx_पढ़ो_fअगरo(काष्ठा st_lsm6dsx_hw *hw)
अणु
	काष्ठा st_lsm6dsx_sensor *acc_sensor, *gyro_sensor, *ext_sensor = शून्य;
	पूर्णांक err, sip, acc_sip, gyro_sip, ts_sip, ext_sip, पढ़ो_len, offset;
	u16 fअगरo_len, pattern_len = hw->sip * ST_LSM6DSX_SAMPLE_SIZE;
	u16 fअगरo_dअगरf_mask = hw->settings->fअगरo_ops.fअगरo_dअगरf.mask;
	bool reset_ts = false;
	__le16 fअगरo_status;
	s64 ts = 0;

	err = st_lsm6dsx_पढ़ो_locked(hw,
				     hw->settings->fअगरo_ops.fअगरo_dअगरf.addr,
				     &fअगरo_status, माप(fअगरo_status));
	अगर (err < 0) अणु
		dev_err(hw->dev, "failed to read fifo status (err=%d)\n",
			err);
		वापस err;
	पूर्ण

	अगर (fअगरo_status & cpu_to_le16(ST_LSM6DSX_FIFO_EMPTY_MASK))
		वापस 0;

	fअगरo_len = (le16_to_cpu(fअगरo_status) & fअगरo_dअगरf_mask) *
		   ST_LSM6DSX_CHAN_SIZE;
	fअगरo_len = (fअगरo_len / pattern_len) * pattern_len;

	acc_sensor = iio_priv(hw->iio_devs[ST_LSM6DSX_ID_ACC]);
	gyro_sensor = iio_priv(hw->iio_devs[ST_LSM6DSX_ID_GYRO]);
	अगर (hw->iio_devs[ST_LSM6DSX_ID_EXT0])
		ext_sensor = iio_priv(hw->iio_devs[ST_LSM6DSX_ID_EXT0]);

	क्रम (पढ़ो_len = 0; पढ़ो_len < fअगरo_len; पढ़ो_len += pattern_len) अणु
		err = st_lsm6dsx_पढ़ो_block(hw, ST_LSM6DSX_REG_FIFO_OUTL_ADDR,
					    hw->buff, pattern_len,
					    ST_LSM6DSX_MAX_WORD_LEN);
		अगर (err < 0) अणु
			dev_err(hw->dev,
				"failed to read pattern from fifo (err=%d)\n",
				err);
			वापस err;
		पूर्ण

		/*
		 * Data are written to the FIFO with a specअगरic pattern
		 * depending on the configured ODRs. The first sequence of data
		 * stored in FIFO contains the data of all enabled sensors
		 * (e.g. Gx, Gy, Gz, Ax, Ay, Az, Ts), then data are repeated
		 * depending on the value of the decimation factor set क्रम each
		 * sensor.
		 *
		 * Supposing the FIFO is storing data from gyroscope and
		 * accelerometer at dअगरferent ODRs:
		 *   - gyroscope ODR = 208Hz, accelerometer ODR = 104Hz
		 * Since the gyroscope ODR is twice the accelerometer one, the
		 * following pattern is repeated every 9 samples:
		 *   - Gx, Gy, Gz, Ax, Ay, Az, Ts, Gx, Gy, Gz, Ts, Gx, ..
		 */
		ext_sip = ext_sensor ? ext_sensor->sip : 0;
		gyro_sip = gyro_sensor->sip;
		acc_sip = acc_sensor->sip;
		ts_sip = hw->ts_sip;
		offset = 0;
		sip = 0;

		जबतक (acc_sip > 0 || gyro_sip > 0 || ext_sip > 0) अणु
			अगर (gyro_sip > 0 && !(sip % gyro_sensor->decimator)) अणु
				स_नकल(hw->scan[ST_LSM6DSX_ID_GYRO].channels,
				       &hw->buff[offset],
				       माप(hw->scan[ST_LSM6DSX_ID_GYRO].channels));
				offset += माप(hw->scan[ST_LSM6DSX_ID_GYRO].channels);
			पूर्ण
			अगर (acc_sip > 0 && !(sip % acc_sensor->decimator)) अणु
				स_नकल(hw->scan[ST_LSM6DSX_ID_ACC].channels,
				       &hw->buff[offset],
				       माप(hw->scan[ST_LSM6DSX_ID_ACC].channels));
				offset += माप(hw->scan[ST_LSM6DSX_ID_ACC].channels);
			पूर्ण
			अगर (ext_sip > 0 && !(sip % ext_sensor->decimator)) अणु
				स_नकल(hw->scan[ST_LSM6DSX_ID_EXT0].channels,
				       &hw->buff[offset],
				       माप(hw->scan[ST_LSM6DSX_ID_EXT0].channels));
				offset += माप(hw->scan[ST_LSM6DSX_ID_EXT0].channels);
			पूर्ण

			अगर (ts_sip-- > 0) अणु
				u8 data[ST_LSM6DSX_SAMPLE_SIZE];

				स_नकल(data, &hw->buff[offset], माप(data));
				/*
				 * hw बारtamp is 3B दीर्घ and it is stored
				 * in FIFO using 6B as 4th FIFO data set
				 * according to this schema:
				 * B0 = ts[15:8], B1 = ts[23:16], B3 = ts[7:0]
				 */
				ts = data[1] << 16 | data[0] << 8 | data[3];
				/*
				 * check अगर hw बारtamp engine is going to
				 * reset (the sensor generates an पूर्णांकerrupt
				 * to संकेत the hw बारtamp will reset in
				 * 1.638s)
				 */
				अगर (!reset_ts && ts >= 0xff0000)
					reset_ts = true;
				ts *= hw->ts_gain;

				offset += ST_LSM6DSX_SAMPLE_SIZE;
			पूर्ण

			अगर (gyro_sip > 0 && !(sip % gyro_sensor->decimator)) अणु
				iio_push_to_buffers_with_बारtamp(
					hw->iio_devs[ST_LSM6DSX_ID_GYRO],
					&hw->scan[ST_LSM6DSX_ID_GYRO],
					gyro_sensor->ts_ref + ts);
				gyro_sip--;
			पूर्ण
			अगर (acc_sip > 0 && !(sip % acc_sensor->decimator)) अणु
				iio_push_to_buffers_with_बारtamp(
					hw->iio_devs[ST_LSM6DSX_ID_ACC],
					&hw->scan[ST_LSM6DSX_ID_ACC],
					acc_sensor->ts_ref + ts);
				acc_sip--;
			पूर्ण
			अगर (ext_sip > 0 && !(sip % ext_sensor->decimator)) अणु
				iio_push_to_buffers_with_बारtamp(
					hw->iio_devs[ST_LSM6DSX_ID_EXT0],
					&hw->scan[ST_LSM6DSX_ID_EXT0],
					ext_sensor->ts_ref + ts);
				ext_sip--;
			पूर्ण
			sip++;
		पूर्ण
	पूर्ण

	अगर (unlikely(reset_ts)) अणु
		err = st_lsm6dsx_reset_hw_ts(hw);
		अगर (err < 0) अणु
			dev_err(hw->dev, "failed to reset hw ts (err=%d)\n",
				err);
			वापस err;
		पूर्ण
	पूर्ण
	वापस पढ़ो_len;
पूर्ण

#घोषणा ST_LSM6DSX_INVALID_SAMPLE	0x7ffd
अटल पूर्णांक
st_lsm6dsx_push_tagged_data(काष्ठा st_lsm6dsx_hw *hw, u8 tag,
			    u8 *data, s64 ts)
अणु
	s16 val = le16_to_cpu(*(__le16 *)data);
	काष्ठा st_lsm6dsx_sensor *sensor;
	काष्ठा iio_dev *iio_dev;

	/* invalid sample during bootstrap phase */
	अगर (val >= ST_LSM6DSX_INVALID_SAMPLE)
		वापस -EINVAL;

	/*
	 * EXT_TAG are managed in FIFO fashion so ST_LSM6DSX_EXT0_TAG
	 * corresponds to the first enabled channel, ST_LSM6DSX_EXT1_TAG
	 * to the second one and ST_LSM6DSX_EXT2_TAG to the last enabled
	 * channel
	 */
	चयन (tag) अणु
	हाल ST_LSM6DSX_GYRO_TAG:
		iio_dev = hw->iio_devs[ST_LSM6DSX_ID_GYRO];
		अवरोध;
	हाल ST_LSM6DSX_ACC_TAG:
		iio_dev = hw->iio_devs[ST_LSM6DSX_ID_ACC];
		अवरोध;
	हाल ST_LSM6DSX_EXT0_TAG:
		अगर (hw->enable_mask & BIT(ST_LSM6DSX_ID_EXT0))
			iio_dev = hw->iio_devs[ST_LSM6DSX_ID_EXT0];
		अन्यथा अगर (hw->enable_mask & BIT(ST_LSM6DSX_ID_EXT1))
			iio_dev = hw->iio_devs[ST_LSM6DSX_ID_EXT1];
		अन्यथा
			iio_dev = hw->iio_devs[ST_LSM6DSX_ID_EXT2];
		अवरोध;
	हाल ST_LSM6DSX_EXT1_TAG:
		अगर ((hw->enable_mask & BIT(ST_LSM6DSX_ID_EXT0)) &&
		    (hw->enable_mask & BIT(ST_LSM6DSX_ID_EXT1)))
			iio_dev = hw->iio_devs[ST_LSM6DSX_ID_EXT1];
		अन्यथा
			iio_dev = hw->iio_devs[ST_LSM6DSX_ID_EXT2];
		अवरोध;
	हाल ST_LSM6DSX_EXT2_TAG:
		iio_dev = hw->iio_devs[ST_LSM6DSX_ID_EXT2];
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	sensor = iio_priv(iio_dev);
	iio_push_to_buffers_with_बारtamp(iio_dev, data,
					   ts + sensor->ts_ref);

	वापस 0;
पूर्ण

/**
 * st_lsm6dsx_पढ़ो_tagged_fअगरo() - tagged hw FIFO पढ़ो routine
 * @hw: Poपूर्णांकer to instance of काष्ठा st_lsm6dsx_hw.
 *
 * Read samples from the hw FIFO and push them to IIO buffers.
 *
 * Return: Number of bytes पढ़ो from the FIFO
 */
पूर्णांक st_lsm6dsx_पढ़ो_tagged_fअगरo(काष्ठा st_lsm6dsx_hw *hw)
अणु
	u16 pattern_len = hw->sip * ST_LSM6DSX_TAGGED_SAMPLE_SIZE;
	u16 fअगरo_len, fअगरo_dअगरf_mask;
	/*
	 * Alignment needed as this can ultimately be passed to a
	 * call to iio_push_to_buffers_with_बारtamp() which
	 * must be passed a buffer that is aligned to 8 bytes so
	 * as to allow insertion of a naturally aligned बारtamp.
	 */
	u8 iio_buff[ST_LSM6DSX_IIO_BUFF_SIZE] __aligned(8);
	u8 tag;
	bool reset_ts = false;
	पूर्णांक i, err, पढ़ो_len;
	__le16 fअगरo_status;
	s64 ts = 0;

	err = st_lsm6dsx_पढ़ो_locked(hw,
				     hw->settings->fअगरo_ops.fअगरo_dअगरf.addr,
				     &fअगरo_status, माप(fअगरo_status));
	अगर (err < 0) अणु
		dev_err(hw->dev, "failed to read fifo status (err=%d)\n",
			err);
		वापस err;
	पूर्ण

	fअगरo_dअगरf_mask = hw->settings->fअगरo_ops.fअगरo_dअगरf.mask;
	fअगरo_len = (le16_to_cpu(fअगरo_status) & fअगरo_dअगरf_mask) *
		   ST_LSM6DSX_TAGGED_SAMPLE_SIZE;
	अगर (!fअगरo_len)
		वापस 0;

	क्रम (पढ़ो_len = 0; पढ़ो_len < fअगरo_len; पढ़ो_len += pattern_len) अणु
		err = st_lsm6dsx_पढ़ो_block(hw,
					    ST_LSM6DSX_REG_FIFO_OUT_TAG_ADDR,
					    hw->buff, pattern_len,
					    ST_LSM6DSX_MAX_TAGGED_WORD_LEN);
		अगर (err < 0) अणु
			dev_err(hw->dev,
				"failed to read pattern from fifo (err=%d)\n",
				err);
			वापस err;
		पूर्ण

		क्रम (i = 0; i < pattern_len;
		     i += ST_LSM6DSX_TAGGED_SAMPLE_SIZE) अणु
			स_नकल(iio_buff, &hw->buff[i + ST_LSM6DSX_TAG_SIZE],
			       ST_LSM6DSX_SAMPLE_SIZE);

			tag = hw->buff[i] >> 3;
			अगर (tag == ST_LSM6DSX_TS_TAG) अणु
				/*
				 * hw बारtamp is 4B दीर्घ and it is stored
				 * in FIFO according to this schema:
				 * B0 = ts[7:0], B1 = ts[15:8], B2 = ts[23:16],
				 * B3 = ts[31:24]
				 */
				ts = le32_to_cpu(*((__le32 *)iio_buff));
				/*
				 * check अगर hw बारtamp engine is going to
				 * reset (the sensor generates an पूर्णांकerrupt
				 * to संकेत the hw बारtamp will reset in
				 * 1.638s)
				 */
				अगर (!reset_ts && ts >= 0xffff0000)
					reset_ts = true;
				ts *= hw->ts_gain;
			पूर्ण अन्यथा अणु
				st_lsm6dsx_push_tagged_data(hw, tag, iio_buff,
							    ts);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (unlikely(reset_ts)) अणु
		err = st_lsm6dsx_reset_hw_ts(hw);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस पढ़ो_len;
पूर्ण

पूर्णांक st_lsm6dsx_flush_fअगरo(काष्ठा st_lsm6dsx_hw *hw)
अणु
	पूर्णांक err;

	अगर (!hw->settings->fअगरo_ops.पढ़ो_fअगरo)
		वापस -ENOTSUPP;

	mutex_lock(&hw->fअगरo_lock);

	hw->settings->fअगरo_ops.पढ़ो_fअगरo(hw);
	err = st_lsm6dsx_set_fअगरo_mode(hw, ST_LSM6DSX_FIFO_BYPASS);

	mutex_unlock(&hw->fअगरo_lock);

	वापस err;
पूर्ण

पूर्णांक st_lsm6dsx_update_fअगरo(काष्ठा st_lsm6dsx_sensor *sensor, bool enable)
अणु
	काष्ठा st_lsm6dsx_hw *hw = sensor->hw;
	u8 fअगरo_mask;
	पूर्णांक err;

	mutex_lock(&hw->conf_lock);

	अगर (enable)
		fअगरo_mask = hw->fअगरo_mask | BIT(sensor->id);
	अन्यथा
		fअगरo_mask = hw->fअगरo_mask & ~BIT(sensor->id);

	अगर (hw->fअगरo_mask) अणु
		err = st_lsm6dsx_flush_fअगरo(hw);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	अगर (sensor->id == ST_LSM6DSX_ID_EXT0 ||
	    sensor->id == ST_LSM6DSX_ID_EXT1 ||
	    sensor->id == ST_LSM6DSX_ID_EXT2) अणु
		err = st_lsm6dsx_shub_set_enable(sensor, enable);
		अगर (err < 0)
			जाओ out;
	पूर्ण अन्यथा अणु
		err = st_lsm6dsx_sensor_set_enable(sensor, enable);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	err = st_lsm6dsx_set_fअगरo_odr(sensor, enable);
	अगर (err < 0)
		जाओ out;

	err = st_lsm6dsx_update_decimators(hw);
	अगर (err < 0)
		जाओ out;

	err = st_lsm6dsx_update_watermark(sensor, sensor->watermark);
	अगर (err < 0)
		जाओ out;

	अगर (fअगरo_mask) अणु
		err = st_lsm6dsx_resume_fअगरo(hw);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	hw->fअगरo_mask = fअगरo_mask;

out:
	mutex_unlock(&hw->conf_lock);

	वापस err;
पूर्ण

अटल पूर्णांक st_lsm6dsx_buffer_preenable(काष्ठा iio_dev *iio_dev)
अणु
	काष्ठा st_lsm6dsx_sensor *sensor = iio_priv(iio_dev);
	काष्ठा st_lsm6dsx_hw *hw = sensor->hw;

	अगर (!hw->settings->fअगरo_ops.update_fअगरo)
		वापस -ENOTSUPP;

	वापस hw->settings->fअगरo_ops.update_fअगरo(sensor, true);
पूर्ण

अटल पूर्णांक st_lsm6dsx_buffer_postdisable(काष्ठा iio_dev *iio_dev)
अणु
	काष्ठा st_lsm6dsx_sensor *sensor = iio_priv(iio_dev);
	काष्ठा st_lsm6dsx_hw *hw = sensor->hw;

	अगर (!hw->settings->fअगरo_ops.update_fअगरo)
		वापस -ENOTSUPP;

	वापस hw->settings->fअगरo_ops.update_fअगरo(sensor, false);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops st_lsm6dsx_buffer_ops = अणु
	.preenable = st_lsm6dsx_buffer_preenable,
	.postdisable = st_lsm6dsx_buffer_postdisable,
पूर्ण;

पूर्णांक st_lsm6dsx_fअगरo_setup(काष्ठा st_lsm6dsx_hw *hw)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < ST_LSM6DSX_ID_MAX; i++) अणु
		अगर (!hw->iio_devs[i])
			जारी;

		ret = devm_iio_kfअगरo_buffer_setup(hw->dev, hw->iio_devs[i],
						  INDIO_BUFFER_SOFTWARE,
						  &st_lsm6dsx_buffer_ops);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
