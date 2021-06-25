<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright IBM Corp 2019
/*
 * The DPS310 is a barometric pressure and temperature sensor.
 * Currently only पढ़ोing a single temperature is supported by
 * this driver.
 *
 * https://www.infineon.com/dgdl/?fileId=5546d462576f34750157750826c42242
 *
 * Temperature calculation:
 *   c0 * 0.5 + c1 * T_raw / kT तओC
 *
 * TODO:
 *  - Optionally support the FIFO
 */

#समावेश <linux/i2c.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा DPS310_DEV_NAME		"dps310"

#घोषणा DPS310_PRS_B0		0x00
#घोषणा DPS310_PRS_B1		0x01
#घोषणा DPS310_PRS_B2		0x02
#घोषणा DPS310_TMP_B0		0x03
#घोषणा DPS310_TMP_B1		0x04
#घोषणा DPS310_TMP_B2		0x05
#घोषणा DPS310_PRS_CFG		0x06
#घोषणा  DPS310_PRS_RATE_BITS	GENMASK(6, 4)
#घोषणा  DPS310_PRS_PRC_BITS	GENMASK(3, 0)
#घोषणा DPS310_TMP_CFG		0x07
#घोषणा  DPS310_TMP_RATE_BITS	GENMASK(6, 4)
#घोषणा  DPS310_TMP_PRC_BITS	GENMASK(3, 0)
#घोषणा  DPS310_TMP_EXT		BIT(7)
#घोषणा DPS310_MEAS_CFG		0x08
#घोषणा  DPS310_MEAS_CTRL_BITS	GENMASK(2, 0)
#घोषणा   DPS310_PRS_EN		BIT(0)
#घोषणा   DPS310_TEMP_EN	BIT(1)
#घोषणा   DPS310_BACKGROUND	BIT(2)
#घोषणा  DPS310_PRS_RDY		BIT(4)
#घोषणा  DPS310_TMP_RDY		BIT(5)
#घोषणा  DPS310_SENSOR_RDY	BIT(6)
#घोषणा  DPS310_COEF_RDY	BIT(7)
#घोषणा DPS310_CFG_REG		0x09
#घोषणा  DPS310_INT_HL		BIT(7)
#घोषणा  DPS310_TMP_SHIFT_EN	BIT(3)
#घोषणा  DPS310_PRS_SHIFT_EN	BIT(4)
#घोषणा  DPS310_FIFO_EN		BIT(5)
#घोषणा  DPS310_SPI_EN		BIT(6)
#घोषणा DPS310_RESET		0x0c
#घोषणा  DPS310_RESET_MAGIC	0x09
#घोषणा DPS310_COEF_BASE	0x10

/* Make sure sleep समय is <= 20ms क्रम usleep_range */
#घोषणा DPS310_POLL_SLEEP_US(t)		min(20000, (t) / 8)
/* Silently handle error in rate value here */
#घोषणा DPS310_POLL_TIMEOUT_US(rc)	((rc) <= 0 ? 1000000 : 1000000 / (rc))

#घोषणा DPS310_PRS_BASE		DPS310_PRS_B0
#घोषणा DPS310_TMP_BASE		DPS310_TMP_B0

/*
 * These values (defined in the spec) indicate how to scale the raw रेजिस्टर
 * values क्रम each level of precision available.
 */
अटल स्थिर पूर्णांक scale_factors[] = अणु
	 524288,
	1572864,
	3670016,
	7864320,
	 253952,
	 516096,
	1040384,
	2088960,
पूर्ण;

काष्ठा dps310_data अणु
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	काष्ठा mutex lock;	/* Lock क्रम sequential HW access functions */

	s32 c0, c1;
	s32 c00, c10, c20, c30, c01, c11, c21;
	s32 pressure_raw;
	s32 temp_raw;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec dps310_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO) |
			BIT(IIO_CHAN_INFO_SAMP_FREQ) |
			BIT(IIO_CHAN_INFO_PROCESSED),
	पूर्ण,
	अणु
		.type = IIO_PRESSURE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO) |
			BIT(IIO_CHAN_INFO_SAMP_FREQ) |
			BIT(IIO_CHAN_INFO_PROCESSED),
	पूर्ण,
पूर्ण;

/* To be called after checking the COEF_RDY bit in MEAS_CFG */
अटल पूर्णांक dps310_get_coefs(काष्ठा dps310_data *data)
अणु
	पूर्णांक rc;
	u8 coef[18];
	u32 c0, c1;
	u32 c00, c10, c20, c30, c01, c11, c21;

	/* Read all sensor calibration coefficients from the COEF रेजिस्टरs. */
	rc = regmap_bulk_पढ़ो(data->regmap, DPS310_COEF_BASE, coef,
			      माप(coef));
	अगर (rc < 0)
		वापस rc;

	/*
	 * Calculate temperature calibration coefficients c0 and c1. The
	 * numbers are 12-bit 2's complement numbers.
	 */
	c0 = (coef[0] << 4) | (coef[1] >> 4);
	data->c0 = sign_extend32(c0, 11);

	c1 = ((coef[1] & GENMASK(3, 0)) << 8) | coef[2];
	data->c1 = sign_extend32(c1, 11);

	/*
	 * Calculate pressure calibration coefficients. c00 and c10 are 20 bit
	 * 2's complement numbers, while the rest are 16 bit 2's complement
	 * numbers.
	 */
	c00 = (coef[3] << 12) | (coef[4] << 4) | (coef[5] >> 4);
	data->c00 = sign_extend32(c00, 19);

	c10 = ((coef[5] & GENMASK(3, 0)) << 16) | (coef[6] << 8) | coef[7];
	data->c10 = sign_extend32(c10, 19);

	c01 = (coef[8] << 8) | coef[9];
	data->c01 = sign_extend32(c01, 15);

	c11 = (coef[10] << 8) | coef[11];
	data->c11 = sign_extend32(c11, 15);

	c20 = (coef[12] << 8) | coef[13];
	data->c20 = sign_extend32(c20, 15);

	c21 = (coef[14] << 8) | coef[15];
	data->c21 = sign_extend32(c21, 15);

	c30 = (coef[16] << 8) | coef[17];
	data->c30 = sign_extend32(c30, 15);

	वापस 0;
पूर्ण

अटल पूर्णांक dps310_get_pres_precision(काष्ठा dps310_data *data)
अणु
	पूर्णांक rc;
	पूर्णांक val;

	rc = regmap_पढ़ो(data->regmap, DPS310_PRS_CFG, &val);
	अगर (rc < 0)
		वापस rc;

	वापस BIT(val & GENMASK(2, 0));
पूर्ण

अटल पूर्णांक dps310_get_temp_precision(काष्ठा dps310_data *data)
अणु
	पूर्णांक rc;
	पूर्णांक val;

	rc = regmap_पढ़ो(data->regmap, DPS310_TMP_CFG, &val);
	अगर (rc < 0)
		वापस rc;

	/*
	 * Scale factor is bottom 4 bits of the रेजिस्टर, but 1111 is
	 * reserved so just grab bottom three
	 */
	वापस BIT(val & GENMASK(2, 0));
पूर्ण

/* Called with lock held */
अटल पूर्णांक dps310_set_pres_precision(काष्ठा dps310_data *data, पूर्णांक val)
अणु
	पूर्णांक rc;
	u8 shअगरt_en;

	अगर (val < 0 || val > 128)
		वापस -EINVAL;

	shअगरt_en = val >= 16 ? DPS310_PRS_SHIFT_EN : 0;
	rc = regmap_ग_लिखो_bits(data->regmap, DPS310_CFG_REG,
			       DPS310_PRS_SHIFT_EN, shअगरt_en);
	अगर (rc)
		वापस rc;

	वापस regmap_update_bits(data->regmap, DPS310_PRS_CFG,
				  DPS310_PRS_PRC_BITS, ilog2(val));
पूर्ण

/* Called with lock held */
अटल पूर्णांक dps310_set_temp_precision(काष्ठा dps310_data *data, पूर्णांक val)
अणु
	पूर्णांक rc;
	u8 shअगरt_en;

	अगर (val < 0 || val > 128)
		वापस -EINVAL;

	shअगरt_en = val >= 16 ? DPS310_TMP_SHIFT_EN : 0;
	rc = regmap_ग_लिखो_bits(data->regmap, DPS310_CFG_REG,
			       DPS310_TMP_SHIFT_EN, shअगरt_en);
	अगर (rc)
		वापस rc;

	वापस regmap_update_bits(data->regmap, DPS310_TMP_CFG,
				  DPS310_TMP_PRC_BITS, ilog2(val));
पूर्ण

/* Called with lock held */
अटल पूर्णांक dps310_set_pres_samp_freq(काष्ठा dps310_data *data, पूर्णांक freq)
अणु
	u8 val;

	अगर (freq < 0 || freq > 128)
		वापस -EINVAL;

	val = ilog2(freq) << 4;

	वापस regmap_update_bits(data->regmap, DPS310_PRS_CFG,
				  DPS310_PRS_RATE_BITS, val);
पूर्ण

/* Called with lock held */
अटल पूर्णांक dps310_set_temp_samp_freq(काष्ठा dps310_data *data, पूर्णांक freq)
अणु
	u8 val;

	अगर (freq < 0 || freq > 128)
		वापस -EINVAL;

	val = ilog2(freq) << 4;

	वापस regmap_update_bits(data->regmap, DPS310_TMP_CFG,
				  DPS310_TMP_RATE_BITS, val);
पूर्ण

अटल पूर्णांक dps310_get_pres_samp_freq(काष्ठा dps310_data *data)
अणु
	पूर्णांक rc;
	पूर्णांक val;

	rc = regmap_पढ़ो(data->regmap, DPS310_PRS_CFG, &val);
	अगर (rc < 0)
		वापस rc;

	वापस BIT((val & DPS310_PRS_RATE_BITS) >> 4);
पूर्ण

अटल पूर्णांक dps310_get_temp_samp_freq(काष्ठा dps310_data *data)
अणु
	पूर्णांक rc;
	पूर्णांक val;

	rc = regmap_पढ़ो(data->regmap, DPS310_TMP_CFG, &val);
	अगर (rc < 0)
		वापस rc;

	वापस BIT((val & DPS310_TMP_RATE_BITS) >> 4);
पूर्ण

अटल पूर्णांक dps310_get_pres_k(काष्ठा dps310_data *data)
अणु
	पूर्णांक rc = dps310_get_pres_precision(data);

	अगर (rc < 0)
		वापस rc;

	वापस scale_factors[ilog2(rc)];
पूर्ण

अटल पूर्णांक dps310_get_temp_k(काष्ठा dps310_data *data)
अणु
	पूर्णांक rc = dps310_get_temp_precision(data);

	अगर (rc < 0)
		वापस rc;

	वापस scale_factors[ilog2(rc)];
पूर्ण

अटल पूर्णांक dps310_पढ़ो_pres_raw(काष्ठा dps310_data *data)
अणु
	पूर्णांक rc;
	पूर्णांक rate;
	पूर्णांक पढ़ोy;
	पूर्णांक समयout;
	s32 raw;
	u8 val[3];

	अगर (mutex_lock_पूर्णांकerruptible(&data->lock))
		वापस -EINTR;

	rate = dps310_get_pres_samp_freq(data);
	समयout = DPS310_POLL_TIMEOUT_US(rate);

	/* Poll क्रम sensor पढ़ोiness; base the समयout upon the sample rate. */
	rc = regmap_पढ़ो_poll_समयout(data->regmap, DPS310_MEAS_CFG, पढ़ोy,
				      पढ़ोy & DPS310_PRS_RDY,
				      DPS310_POLL_SLEEP_US(समयout), समयout);
	अगर (rc)
		जाओ करोne;

	rc = regmap_bulk_पढ़ो(data->regmap, DPS310_PRS_BASE, val, माप(val));
	अगर (rc < 0)
		जाओ करोne;

	raw = (val[0] << 16) | (val[1] << 8) | val[2];
	data->pressure_raw = sign_extend32(raw, 23);

करोne:
	mutex_unlock(&data->lock);
	वापस rc;
पूर्ण

/* Called with lock held */
अटल पूर्णांक dps310_पढ़ो_temp_पढ़ोy(काष्ठा dps310_data *data)
अणु
	पूर्णांक rc;
	u8 val[3];
	s32 raw;

	rc = regmap_bulk_पढ़ो(data->regmap, DPS310_TMP_BASE, val, माप(val));
	अगर (rc < 0)
		वापस rc;

	raw = (val[0] << 16) | (val[1] << 8) | val[2];
	data->temp_raw = sign_extend32(raw, 23);

	वापस 0;
पूर्ण

अटल पूर्णांक dps310_पढ़ो_temp_raw(काष्ठा dps310_data *data)
अणु
	पूर्णांक rc;
	पूर्णांक rate;
	पूर्णांक पढ़ोy;
	पूर्णांक समयout;

	अगर (mutex_lock_पूर्णांकerruptible(&data->lock))
		वापस -EINTR;

	rate = dps310_get_temp_samp_freq(data);
	समयout = DPS310_POLL_TIMEOUT_US(rate);

	/* Poll क्रम sensor पढ़ोiness; base the समयout upon the sample rate. */
	rc = regmap_पढ़ो_poll_समयout(data->regmap, DPS310_MEAS_CFG, पढ़ोy,
				      पढ़ोy & DPS310_TMP_RDY,
				      DPS310_POLL_SLEEP_US(समयout), समयout);
	अगर (rc < 0)
		जाओ करोne;

	rc = dps310_पढ़ो_temp_पढ़ोy(data);

करोne:
	mutex_unlock(&data->lock);
	वापस rc;
पूर्ण

अटल bool dps310_is_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल DPS310_PRS_CFG:
	हाल DPS310_TMP_CFG:
	हाल DPS310_MEAS_CFG:
	हाल DPS310_CFG_REG:
	हाल DPS310_RESET:
	/* No करोcumentation available on the रेजिस्टरs below */
	हाल 0x0e:
	हाल 0x0f:
	हाल 0x62:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool dps310_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल DPS310_PRS_B0:
	हाल DPS310_PRS_B1:
	हाल DPS310_PRS_B2:
	हाल DPS310_TMP_B0:
	हाल DPS310_TMP_B1:
	हाल DPS310_TMP_B2:
	हाल DPS310_MEAS_CFG:
	हाल 0x32:	/* No करोcumentation available on this रेजिस्टर */
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक dps310_ग_लिखो_raw(काष्ठा iio_dev *iio,
			    काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val,
			    पूर्णांक val2, दीर्घ mask)
अणु
	पूर्णांक rc;
	काष्ठा dps310_data *data = iio_priv(iio);

	अगर (mutex_lock_पूर्णांकerruptible(&data->lock))
		वापस -EINTR;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		चयन (chan->type) अणु
		हाल IIO_PRESSURE:
			rc = dps310_set_pres_samp_freq(data, val);
			अवरोध;

		हाल IIO_TEMP:
			rc = dps310_set_temp_samp_freq(data, val);
			अवरोध;

		शेष:
			rc = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		चयन (chan->type) अणु
		हाल IIO_PRESSURE:
			rc = dps310_set_pres_precision(data, val);
			अवरोध;

		हाल IIO_TEMP:
			rc = dps310_set_temp_precision(data, val);
			अवरोध;

		शेष:
			rc = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		rc = -EINVAL;
		अवरोध;
	पूर्ण

	mutex_unlock(&data->lock);
	वापस rc;
पूर्ण

अटल पूर्णांक dps310_calculate_pressure(काष्ठा dps310_data *data)
अणु
	पूर्णांक i;
	पूर्णांक rc;
	पूर्णांक t_पढ़ोy;
	पूर्णांक kpi = dps310_get_pres_k(data);
	पूर्णांक kti = dps310_get_temp_k(data);
	s64 rem = 0ULL;
	s64 pressure = 0ULL;
	s64 p;
	s64 t;
	s64 denoms[7];
	s64 nums[7];
	s64 rems[7];
	s64 kp;
	s64 kt;

	अगर (kpi < 0)
		वापस kpi;

	अगर (kti < 0)
		वापस kti;

	kp = (s64)kpi;
	kt = (s64)kti;

	/* Refresh temp अगर it's पढ़ोy, otherwise just use the latest value */
	अगर (mutex_trylock(&data->lock)) अणु
		rc = regmap_पढ़ो(data->regmap, DPS310_MEAS_CFG, &t_पढ़ोy);
		अगर (rc >= 0 && t_पढ़ोy & DPS310_TMP_RDY)
			dps310_पढ़ो_temp_पढ़ोy(data);

		mutex_unlock(&data->lock);
	पूर्ण

	p = (s64)data->pressure_raw;
	t = (s64)data->temp_raw;

	/* Section 4.9.1 of the DPS310 spec; algebra'd to aव्योम underflow */
	nums[0] = (s64)data->c00;
	denoms[0] = 1LL;
	nums[1] = p * (s64)data->c10;
	denoms[1] = kp;
	nums[2] = p * p * (s64)data->c20;
	denoms[2] = kp * kp;
	nums[3] = p * p * p * (s64)data->c30;
	denoms[3] = kp * kp * kp;
	nums[4] = t * (s64)data->c01;
	denoms[4] = kt;
	nums[5] = t * p * (s64)data->c11;
	denoms[5] = kp * kt;
	nums[6] = t * p * p * (s64)data->c21;
	denoms[6] = kp * kp * kt;

	/* Kernel lacks a भाग64_s64_rem function; denoms are all positive */
	क्रम (i = 0; i < 7; ++i) अणु
		u64 irem;

		अगर (nums[i] < 0LL) अणु
			pressure -= भाग64_u64_rem(-nums[i], denoms[i], &irem);
			rems[i] = -irem;
		पूर्ण अन्यथा अणु
			pressure += भाग64_u64_rem(nums[i], denoms[i], &irem);
			rems[i] = (s64)irem;
		पूर्ण
	पूर्ण

	/* Increase precision and calculate the reमुख्यder sum */
	क्रम (i = 0; i < 7; ++i)
		rem += भाग64_s64((s64)rems[i] * 1000000000LL, denoms[i]);

	pressure += भाग_s64(rem, 1000000000LL);
	अगर (pressure < 0LL)
		वापस -दुस्फल;

	वापस (पूर्णांक)min_t(s64, pressure, पूर्णांक_उच्च);
पूर्ण

अटल पूर्णांक dps310_पढ़ो_pressure(काष्ठा dps310_data *data, पूर्णांक *val, पूर्णांक *val2,
				दीर्घ mask)
अणु
	पूर्णांक rc;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		rc = dps310_get_pres_samp_freq(data);
		अगर (rc < 0)
			वापस rc;

		*val = rc;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_PROCESSED:
		rc = dps310_पढ़ो_pres_raw(data);
		अगर (rc)
			वापस rc;

		rc = dps310_calculate_pressure(data);
		अगर (rc < 0)
			वापस rc;

		*val = rc;
		*val2 = 1000; /* Convert Pa to KPa per IIO ABI */
		वापस IIO_VAL_FRACTIONAL;

	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		rc = dps310_get_pres_precision(data);
		अगर (rc < 0)
			वापस rc;

		*val = rc;
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक dps310_calculate_temp(काष्ठा dps310_data *data)
अणु
	s64 c0;
	s64 t;
	पूर्णांक kt = dps310_get_temp_k(data);

	अगर (kt < 0)
		वापस kt;

	/* Obtain inverse-scaled offset */
	c0 = भाग_s64((s64)kt * (s64)data->c0, 2);

	/* Add the offset to the unscaled temperature */
	t = c0 + ((s64)data->temp_raw * (s64)data->c1);

	/* Convert to milliCelsius and scale the temperature */
	वापस (पूर्णांक)भाग_s64(t * 1000LL, kt);
पूर्ण

अटल पूर्णांक dps310_पढ़ो_temp(काष्ठा dps310_data *data, पूर्णांक *val, पूर्णांक *val2,
			    दीर्घ mask)
अणु
	पूर्णांक rc;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		rc = dps310_get_temp_samp_freq(data);
		अगर (rc < 0)
			वापस rc;

		*val = rc;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_PROCESSED:
		rc = dps310_पढ़ो_temp_raw(data);
		अगर (rc)
			वापस rc;

		rc = dps310_calculate_temp(data);
		अगर (rc < 0)
			वापस rc;

		*val = rc;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		rc = dps310_get_temp_precision(data);
		अगर (rc < 0)
			वापस rc;

		*val = rc;
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक dps310_पढ़ो_raw(काष्ठा iio_dev *iio,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा dps310_data *data = iio_priv(iio);

	चयन (chan->type) अणु
	हाल IIO_PRESSURE:
		वापस dps310_पढ़ो_pressure(data, val, val2, mask);

	हाल IIO_TEMP:
		वापस dps310_पढ़ो_temp(data, val, val2, mask);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम dps310_reset(व्योम *action_data)
अणु
	काष्ठा dps310_data *data = action_data;

	regmap_ग_लिखो(data->regmap, DPS310_RESET, DPS310_RESET_MAGIC);
पूर्ण

अटल स्थिर काष्ठा regmap_config dps310_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.ग_लिखोable_reg = dps310_is_ग_लिखोable_reg,
	.अस्थिर_reg = dps310_is_अस्थिर_reg,
	.cache_type = REGCACHE_RBTREE,
	.max_रेजिस्टर = 0x62, /* No करोcumentation available on this रेजिस्टर */
पूर्ण;

अटल स्थिर काष्ठा iio_info dps310_info = अणु
	.पढ़ो_raw = dps310_पढ़ो_raw,
	.ग_लिखो_raw = dps310_ग_लिखो_raw,
पूर्ण;

/*
 * Some verions of chip will पढ़ो temperatures in the ~60C range when
 * its actually ~20C. This is the manufacturer recommended workaround
 * to correct the issue. The रेजिस्टरs used below are unकरोcumented.
 */
अटल पूर्णांक dps310_temp_workaround(काष्ठा dps310_data *data)
अणु
	पूर्णांक rc;
	पूर्णांक reg;

	rc = regmap_पढ़ो(data->regmap, 0x32, &reg);
	अगर (rc < 0)
		वापस rc;

	/*
	 * If bit 1 is set then the device is okay, and the workaround करोes not
	 * need to be applied
	 */
	अगर (reg & BIT(1))
		वापस 0;

	rc = regmap_ग_लिखो(data->regmap, 0x0e, 0xA5);
	अगर (rc < 0)
		वापस rc;

	rc = regmap_ग_लिखो(data->regmap, 0x0f, 0x96);
	अगर (rc < 0)
		वापस rc;

	rc = regmap_ग_लिखो(data->regmap, 0x62, 0x02);
	अगर (rc < 0)
		वापस rc;

	rc = regmap_ग_लिखो(data->regmap, 0x0e, 0x00);
	अगर (rc < 0)
		वापस rc;

	वापस regmap_ग_लिखो(data->regmap, 0x0f, 0x00);
पूर्ण

अटल पूर्णांक dps310_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा dps310_data *data;
	काष्ठा iio_dev *iio;
	पूर्णांक rc, पढ़ोy;

	iio = devm_iio_device_alloc(&client->dev,  माप(*data));
	अगर (!iio)
		वापस -ENOMEM;

	data = iio_priv(iio);
	data->client = client;
	mutex_init(&data->lock);

	iio->name = id->name;
	iio->channels = dps310_channels;
	iio->num_channels = ARRAY_SIZE(dps310_channels);
	iio->info = &dps310_info;
	iio->modes = INDIO_सूचीECT_MODE;

	data->regmap = devm_regmap_init_i2c(client, &dps310_regmap_config);
	अगर (IS_ERR(data->regmap))
		वापस PTR_ERR(data->regmap);

	/* Register to run the device reset when the device is हटाओd */
	rc = devm_add_action_or_reset(&client->dev, dps310_reset, data);
	अगर (rc)
		वापस rc;

	/*
	 * Set up pressure sensor in single sample, one measurement per second
	 * mode
	 */
	rc = regmap_ग_लिखो(data->regmap, DPS310_PRS_CFG, 0);

	/*
	 * Set up बाह्यal (MEMS) temperature sensor in single sample, one
	 * measurement per second mode
	 */
	rc = regmap_ग_लिखो(data->regmap, DPS310_TMP_CFG, DPS310_TMP_EXT);
	अगर (rc < 0)
		वापस rc;

	/* Temp and pressure shअगरts are disabled when PRC <= 8 */
	rc = regmap_ग_लिखो_bits(data->regmap, DPS310_CFG_REG,
			       DPS310_PRS_SHIFT_EN | DPS310_TMP_SHIFT_EN, 0);
	अगर (rc < 0)
		वापस rc;

	/* MEAS_CFG करोesn't update correctly unless first written with 0 */
	rc = regmap_ग_लिखो_bits(data->regmap, DPS310_MEAS_CFG,
			       DPS310_MEAS_CTRL_BITS, 0);
	अगर (rc < 0)
		वापस rc;

	/* Turn on temperature and pressure measurement in the background */
	rc = regmap_ग_लिखो_bits(data->regmap, DPS310_MEAS_CFG,
			       DPS310_MEAS_CTRL_BITS, DPS310_PRS_EN |
			       DPS310_TEMP_EN | DPS310_BACKGROUND);
	अगर (rc < 0)
		वापस rc;

	/*
	 * Calibration coefficients required क्रम reporting temperature.
	 * They are available 40ms after the device has started
	 */
	rc = regmap_पढ़ो_poll_समयout(data->regmap, DPS310_MEAS_CFG, पढ़ोy,
				      पढ़ोy & DPS310_COEF_RDY, 10000, 40000);
	अगर (rc < 0)
		वापस rc;

	rc = dps310_get_coefs(data);
	अगर (rc < 0)
		वापस rc;

	rc = dps310_temp_workaround(data);
	अगर (rc < 0)
		वापस rc;

	rc = devm_iio_device_रेजिस्टर(&client->dev, iio);
	अगर (rc)
		वापस rc;

	i2c_set_clientdata(client, iio);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id dps310_id[] = अणु
	अणु DPS310_DEV_NAME, 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, dps310_id);

अटल काष्ठा i2c_driver dps310_driver = अणु
	.driver = अणु
		.name = DPS310_DEV_NAME,
	पूर्ण,
	.probe = dps310_probe,
	.id_table = dps310_id,
पूर्ण;
module_i2c_driver(dps310_driver);

MODULE_AUTHOR("Joel Stanley <joel@jms.id.au>");
MODULE_DESCRIPTION("Infineon DPS310 pressure and temperature sensor");
MODULE_LICENSE("GPL v2");
