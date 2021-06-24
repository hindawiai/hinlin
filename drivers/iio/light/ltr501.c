<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ltr501.c - Support क्रम Lite-On LTR501 ambient light and proximity sensor
 *
 * Copyright 2014 Peter Meerwald <pmeerw@pmeerw.net>
 *
 * 7-bit I2C slave address 0x23
 *
 * TODO: IR LED अक्षरacteristics
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/regmap.h>
#समावेश <linux/acpi.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/triggered_buffer.h>

#घोषणा LTR501_DRV_NAME "ltr501"

#घोषणा LTR501_ALS_CONTR 0x80 /* ALS operation mode, SW reset */
#घोषणा LTR501_PS_CONTR 0x81 /* PS operation mode */
#घोषणा LTR501_PS_MEAS_RATE 0x84 /* measurement rate*/
#घोषणा LTR501_ALS_MEAS_RATE 0x85 /* ALS पूर्णांकeg समय, measurement rate*/
#घोषणा LTR501_PART_ID 0x86
#घोषणा LTR501_MANUFAC_ID 0x87
#घोषणा LTR501_ALS_DATA1 0x88 /* 16-bit, little endian */
#घोषणा LTR501_ALS_DATA0 0x8a /* 16-bit, little endian */
#घोषणा LTR501_ALS_PS_STATUS 0x8c
#घोषणा LTR501_PS_DATA 0x8d /* 16-bit, little endian */
#घोषणा LTR501_INTR 0x8f /* output mode, polarity, mode */
#घोषणा LTR501_PS_THRESH_UP 0x90 /* 11 bit, ps upper threshold */
#घोषणा LTR501_PS_THRESH_LOW 0x92 /* 11 bit, ps lower threshold */
#घोषणा LTR501_ALS_THRESH_UP 0x97 /* 16 bit, ALS upper threshold */
#घोषणा LTR501_ALS_THRESH_LOW 0x99 /* 16 bit, ALS lower threshold */
#घोषणा LTR501_INTR_PRST 0x9e /* ps thresh, als thresh */
#घोषणा LTR501_MAX_REG 0x9f

#घोषणा LTR501_ALS_CONTR_SW_RESET BIT(2)
#घोषणा LTR501_CONTR_PS_GAIN_MASK (BIT(3) | BIT(2))
#घोषणा LTR501_CONTR_PS_GAIN_SHIFT 2
#घोषणा LTR501_CONTR_ALS_GAIN_MASK BIT(3)
#घोषणा LTR501_CONTR_ACTIVE BIT(1)

#घोषणा LTR501_STATUS_ALS_INTR BIT(3)
#घोषणा LTR501_STATUS_ALS_RDY BIT(2)
#घोषणा LTR501_STATUS_PS_INTR BIT(1)
#घोषणा LTR501_STATUS_PS_RDY BIT(0)

#घोषणा LTR501_PS_DATA_MASK 0x7ff
#घोषणा LTR501_PS_THRESH_MASK 0x7ff
#घोषणा LTR501_ALS_THRESH_MASK 0xffff

#घोषणा LTR501_ALS_DEF_PERIOD 500000
#घोषणा LTR501_PS_DEF_PERIOD 100000

#घोषणा LTR501_REGMAP_NAME "ltr501_regmap"

#घोषणा LTR501_LUX_CONV(vis_coeff, vis_data, ir_coeff, ir_data) \
			((vis_coeff * vis_data) - (ir_coeff * ir_data))

अटल स्थिर पूर्णांक पूर्णांक_समय_mapping[] = अणु100000, 50000, 200000, 400000पूर्ण;

अटल स्थिर काष्ठा reg_field reg_field_it =
				REG_FIELD(LTR501_ALS_MEAS_RATE, 3, 4);
अटल स्थिर काष्ठा reg_field reg_field_als_पूर्णांकr =
				REG_FIELD(LTR501_INTR, 1, 1);
अटल स्थिर काष्ठा reg_field reg_field_ps_पूर्णांकr =
				REG_FIELD(LTR501_INTR, 0, 0);
अटल स्थिर काष्ठा reg_field reg_field_als_rate =
				REG_FIELD(LTR501_ALS_MEAS_RATE, 0, 2);
अटल स्थिर काष्ठा reg_field reg_field_ps_rate =
				REG_FIELD(LTR501_PS_MEAS_RATE, 0, 3);
अटल स्थिर काष्ठा reg_field reg_field_als_prst =
				REG_FIELD(LTR501_INTR_PRST, 0, 3);
अटल स्थिर काष्ठा reg_field reg_field_ps_prst =
				REG_FIELD(LTR501_INTR_PRST, 4, 7);

काष्ठा ltr501_samp_table अणु
	पूर्णांक freq_val;  /* repetition frequency in micro HZ*/
	पूर्णांक समय_val; /* repetition rate in micro seconds */
पूर्ण;

#घोषणा LTR501_RESERVED_GAIN -1

क्रमागत अणु
	ltr501 = 0,
	ltr559,
	ltr301,
पूर्ण;

काष्ठा ltr501_gain अणु
	पूर्णांक scale;
	पूर्णांक uscale;
पूर्ण;

अटल स्थिर काष्ठा ltr501_gain ltr501_als_gain_tbl[] = अणु
	अणु1, 0पूर्ण,
	अणु0, 5000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ltr501_gain ltr559_als_gain_tbl[] = अणु
	अणु1, 0पूर्ण,
	अणु0, 500000पूर्ण,
	अणु0, 250000पूर्ण,
	अणु0, 125000पूर्ण,
	अणुLTR501_RESERVED_GAIN, LTR501_RESERVED_GAINपूर्ण,
	अणुLTR501_RESERVED_GAIN, LTR501_RESERVED_GAINपूर्ण,
	अणु0, 20000पूर्ण,
	अणु0, 10000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ltr501_gain ltr501_ps_gain_tbl[] = अणु
	अणु1, 0पूर्ण,
	अणु0, 250000पूर्ण,
	अणु0, 125000पूर्ण,
	अणु0, 62500पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ltr501_gain ltr559_ps_gain_tbl[] = अणु
	अणु0, 62500पूर्ण, /* x16 gain */
	अणु0, 31250पूर्ण, /* x32 gain */
	अणु0, 15625पूर्ण, /* bits X1 are क्रम x64 gain */
	अणु0, 15624पूर्ण,
पूर्ण;

काष्ठा ltr501_chip_info अणु
	u8 partid;
	स्थिर काष्ठा ltr501_gain *als_gain;
	पूर्णांक als_gain_tbl_size;
	स्थिर काष्ठा ltr501_gain *ps_gain;
	पूर्णांक ps_gain_tbl_size;
	u8 als_mode_active;
	u8 als_gain_mask;
	u8 als_gain_shअगरt;
	काष्ठा iio_chan_spec स्थिर *channels;
	स्थिर पूर्णांक no_channels;
	स्थिर काष्ठा iio_info *info;
	स्थिर काष्ठा iio_info *info_no_irq;
पूर्ण;

काष्ठा ltr501_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock_als, lock_ps;
	काष्ठा ltr501_chip_info *chip_info;
	u8 als_contr, ps_contr;
	पूर्णांक als_period, ps_period; /* period in micro seconds */
	काष्ठा regmap *regmap;
	काष्ठा regmap_field *reg_it;
	काष्ठा regmap_field *reg_als_पूर्णांकr;
	काष्ठा regmap_field *reg_ps_पूर्णांकr;
	काष्ठा regmap_field *reg_als_rate;
	काष्ठा regmap_field *reg_ps_rate;
	काष्ठा regmap_field *reg_als_prst;
	काष्ठा regmap_field *reg_ps_prst;
पूर्ण;

अटल स्थिर काष्ठा ltr501_samp_table ltr501_als_samp_table[] = अणु
			अणु20000000, 50000पूर्ण, अणु10000000, 100000पूर्ण,
			अणु5000000, 200000पूर्ण, अणु2000000, 500000पूर्ण,
			अणु1000000, 1000000पूर्ण, अणु500000, 2000000पूर्ण,
			अणु500000, 2000000पूर्ण, अणु500000, 2000000पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ltr501_samp_table ltr501_ps_samp_table[] = अणु
			अणु20000000, 50000पूर्ण, अणु14285714, 70000पूर्ण,
			अणु10000000, 100000पूर्ण, अणु5000000, 200000पूर्ण,
			अणु2000000, 500000पूर्ण, अणु1000000, 1000000पूर्ण,
			अणु500000, 2000000पूर्ण, अणु500000, 2000000पूर्ण,
			अणु500000, 2000000पूर्ण
पूर्ण;

अटल पूर्णांक ltr501_match_samp_freq(स्थिर काष्ठा ltr501_samp_table *tab,
					   पूर्णांक len, पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i, freq;

	freq = val * 1000000 + val2;

	क्रम (i = 0; i < len; i++) अणु
		अगर (tab[i].freq_val == freq)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ltr501_als_पढ़ो_samp_freq(स्थिर काष्ठा ltr501_data *data,
				     पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक ret, i;

	ret = regmap_field_पढ़ो(data->reg_als_rate, &i);
	अगर (ret < 0)
		वापस ret;

	अगर (i < 0 || i >= ARRAY_SIZE(ltr501_als_samp_table))
		वापस -EINVAL;

	*val = ltr501_als_samp_table[i].freq_val / 1000000;
	*val2 = ltr501_als_samp_table[i].freq_val % 1000000;

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

अटल पूर्णांक ltr501_ps_पढ़ो_samp_freq(स्थिर काष्ठा ltr501_data *data,
				    पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक ret, i;

	ret = regmap_field_पढ़ो(data->reg_ps_rate, &i);
	अगर (ret < 0)
		वापस ret;

	अगर (i < 0 || i >= ARRAY_SIZE(ltr501_ps_samp_table))
		वापस -EINVAL;

	*val = ltr501_ps_samp_table[i].freq_val / 1000000;
	*val2 = ltr501_ps_samp_table[i].freq_val % 1000000;

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

अटल पूर्णांक ltr501_als_ग_लिखो_samp_freq(काष्ठा ltr501_data *data,
				      पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i, ret;

	i = ltr501_match_samp_freq(ltr501_als_samp_table,
				   ARRAY_SIZE(ltr501_als_samp_table),
				   val, val2);

	अगर (i < 0)
		वापस i;

	mutex_lock(&data->lock_als);
	ret = regmap_field_ग_लिखो(data->reg_als_rate, i);
	mutex_unlock(&data->lock_als);

	वापस ret;
पूर्ण

अटल पूर्णांक ltr501_ps_ग_लिखो_samp_freq(काष्ठा ltr501_data *data,
				     पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i, ret;

	i = ltr501_match_samp_freq(ltr501_ps_samp_table,
				   ARRAY_SIZE(ltr501_ps_samp_table),
				   val, val2);

	अगर (i < 0)
		वापस i;

	mutex_lock(&data->lock_ps);
	ret = regmap_field_ग_लिखो(data->reg_ps_rate, i);
	mutex_unlock(&data->lock_ps);

	वापस ret;
पूर्ण

अटल पूर्णांक ltr501_als_पढ़ो_samp_period(स्थिर काष्ठा ltr501_data *data, पूर्णांक *val)
अणु
	पूर्णांक ret, i;

	ret = regmap_field_पढ़ो(data->reg_als_rate, &i);
	अगर (ret < 0)
		वापस ret;

	अगर (i < 0 || i >= ARRAY_SIZE(ltr501_als_samp_table))
		वापस -EINVAL;

	*val = ltr501_als_samp_table[i].समय_val;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक ltr501_ps_पढ़ो_samp_period(स्थिर काष्ठा ltr501_data *data, पूर्णांक *val)
अणु
	पूर्णांक ret, i;

	ret = regmap_field_पढ़ो(data->reg_ps_rate, &i);
	अगर (ret < 0)
		वापस ret;

	अगर (i < 0 || i >= ARRAY_SIZE(ltr501_ps_samp_table))
		वापस -EINVAL;

	*val = ltr501_ps_samp_table[i].समय_val;

	वापस IIO_VAL_INT;
पूर्ण

/* IR and visible spectrum coeff's are given in data sheet */
अटल अचिन्हित दीर्घ ltr501_calculate_lux(u16 vis_data, u16 ir_data)
अणु
	अचिन्हित दीर्घ ratio, lux;

	अगर (vis_data == 0)
		वापस 0;

	/* multiply numerator by 100 to aव्योम handling ratio < 1 */
	ratio = DIV_ROUND_UP(ir_data * 100, ir_data + vis_data);

	अगर (ratio < 45)
		lux = LTR501_LUX_CONV(1774, vis_data, -1105, ir_data);
	अन्यथा अगर (ratio >= 45 && ratio < 64)
		lux = LTR501_LUX_CONV(3772, vis_data, 1336, ir_data);
	अन्यथा अगर (ratio >= 64 && ratio < 85)
		lux = LTR501_LUX_CONV(1690, vis_data, 169, ir_data);
	अन्यथा
		lux = 0;

	वापस lux / 1000;
पूर्ण

अटल पूर्णांक ltr501_drdy(स्थिर काष्ठा ltr501_data *data, u8 drdy_mask)
अणु
	पूर्णांक tries = 100;
	पूर्णांक ret, status;

	जबतक (tries--) अणु
		ret = regmap_पढ़ो(data->regmap, LTR501_ALS_PS_STATUS, &status);
		अगर (ret < 0)
			वापस ret;
		अगर ((status & drdy_mask) == drdy_mask)
			वापस 0;
		msleep(25);
	पूर्ण

	dev_err(&data->client->dev, "ltr501_drdy() failed, data not ready\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक ltr501_set_it_समय(काष्ठा ltr501_data *data, पूर्णांक it)
अणु
	पूर्णांक ret, i, index = -1, status;

	क्रम (i = 0; i < ARRAY_SIZE(पूर्णांक_समय_mapping); i++) अणु
		अगर (पूर्णांक_समय_mapping[i] == it) अणु
			index = i;
			अवरोध;
		पूर्ण
	पूर्ण
	/* Make sure पूर्णांकeg समय index is valid */
	अगर (index < 0)
		वापस -EINVAL;

	ret = regmap_पढ़ो(data->regmap, LTR501_ALS_CONTR, &status);
	अगर (ret < 0)
		वापस ret;

	अगर (status & LTR501_CONTR_ALS_GAIN_MASK) अणु
		/*
		 * 200 ms and 400 ms पूर्णांकeg समय can only be
		 * used in dynamic range 1
		 */
		अगर (index > 1)
			वापस -EINVAL;
	पूर्ण अन्यथा
		/* 50 ms पूर्णांकeg समय can only be used in dynamic range 2 */
		अगर (index == 1)
			वापस -EINVAL;

	वापस regmap_field_ग_लिखो(data->reg_it, index);
पूर्ण

/* पढ़ो पूर्णांक समय in micro seconds */
अटल पूर्णांक ltr501_पढ़ो_it_समय(स्थिर काष्ठा ltr501_data *data,
			       पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक ret, index;

	ret = regmap_field_पढ़ो(data->reg_it, &index);
	अगर (ret < 0)
		वापस ret;

	/* Make sure पूर्णांकeg समय index is valid */
	अगर (index < 0 || index >= ARRAY_SIZE(पूर्णांक_समय_mapping))
		वापस -EINVAL;

	*val2 = पूर्णांक_समय_mapping[index];
	*val = 0;

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

अटल पूर्णांक ltr501_पढ़ो_als(स्थिर काष्ठा ltr501_data *data, __le16 buf[2])
अणु
	पूर्णांक ret;

	ret = ltr501_drdy(data, LTR501_STATUS_ALS_RDY);
	अगर (ret < 0)
		वापस ret;
	/* always पढ़ो both ALS channels in given order */
	वापस regmap_bulk_पढ़ो(data->regmap, LTR501_ALS_DATA1,
				buf, 2 * माप(__le16));
पूर्ण

अटल पूर्णांक ltr501_पढ़ो_ps(स्थिर काष्ठा ltr501_data *data)
अणु
	पूर्णांक ret, status;

	ret = ltr501_drdy(data, LTR501_STATUS_PS_RDY);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_bulk_पढ़ो(data->regmap, LTR501_PS_DATA,
			       &status, 2);
	अगर (ret < 0)
		वापस ret;

	वापस status;
पूर्ण

अटल पूर्णांक ltr501_पढ़ो_पूर्णांकr_prst(स्थिर काष्ठा ltr501_data *data,
				 क्रमागत iio_chan_type type,
				 पूर्णांक *val2)
अणु
	पूर्णांक ret, samp_period, prst;

	चयन (type) अणु
	हाल IIO_INTENSITY:
		ret = regmap_field_पढ़ो(data->reg_als_prst, &prst);
		अगर (ret < 0)
			वापस ret;

		ret = ltr501_als_पढ़ो_samp_period(data, &samp_period);

		अगर (ret < 0)
			वापस ret;
		*val2 = samp_period * prst;
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_PROXIMITY:
		ret = regmap_field_पढ़ो(data->reg_ps_prst, &prst);
		अगर (ret < 0)
			वापस ret;

		ret = ltr501_ps_पढ़ो_samp_period(data, &samp_period);

		अगर (ret < 0)
			वापस ret;

		*val2 = samp_period * prst;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ltr501_ग_लिखो_पूर्णांकr_prst(काष्ठा ltr501_data *data,
				  क्रमागत iio_chan_type type,
				  पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक ret, samp_period, new_val;
	अचिन्हित दीर्घ period;

	अगर (val < 0 || val2 < 0)
		वापस -EINVAL;

	/* period in microseconds */
	period = ((val * 1000000) + val2);

	चयन (type) अणु
	हाल IIO_INTENSITY:
		ret = ltr501_als_पढ़ो_samp_period(data, &samp_period);
		अगर (ret < 0)
			वापस ret;

		/* period should be atleast equal to sampling period */
		अगर (period < samp_period)
			वापस -EINVAL;

		new_val = DIV_ROUND_UP(period, samp_period);
		अगर (new_val < 0 || new_val > 0x0f)
			वापस -EINVAL;

		mutex_lock(&data->lock_als);
		ret = regmap_field_ग_लिखो(data->reg_als_prst, new_val);
		mutex_unlock(&data->lock_als);
		अगर (ret >= 0)
			data->als_period = period;

		वापस ret;
	हाल IIO_PROXIMITY:
		ret = ltr501_ps_पढ़ो_samp_period(data, &samp_period);
		अगर (ret < 0)
			वापस ret;

		/* period should be atleast equal to rate */
		अगर (period < samp_period)
			वापस -EINVAL;

		new_val = DIV_ROUND_UP(period, samp_period);
		अगर (new_val < 0 || new_val > 0x0f)
			वापस -EINVAL;

		mutex_lock(&data->lock_ps);
		ret = regmap_field_ग_लिखो(data->reg_ps_prst, new_val);
		mutex_unlock(&data->lock_ps);
		अगर (ret >= 0)
			data->ps_period = period;

		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_event_spec ltr501_als_event_spec[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE) |
				 BIT(IIO_EV_INFO_PERIOD),
	पूर्ण,

पूर्ण;

अटल स्थिर काष्ठा iio_event_spec ltr501_pxs_event_spec[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE) |
				 BIT(IIO_EV_INFO_PERIOD),
	पूर्ण,
पूर्ण;

#घोषणा LTR501_INTENSITY_CHANNEL(_idx, _addr, _mod, _shared, \
				 _evspec, _evsize) अणु \
	.type = IIO_INTENSITY, \
	.modअगरied = 1, \
	.address = (_addr), \
	.channel2 = (_mod), \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = (_shared), \
	.scan_index = (_idx), \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = 16, \
		.storagebits = 16, \
		.endianness = IIO_CPU, \
	पूर्ण, \
	.event_spec = _evspec,\
	.num_event_specs = _evsize,\
पूर्ण

#घोषणा LTR501_LIGHT_CHANNEL() अणु \
	.type = IIO_LIGHT, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED), \
	.scan_index = -1, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ltr501_channels[] = अणु
	LTR501_LIGHT_CHANNEL(),
	LTR501_INTENSITY_CHANNEL(0, LTR501_ALS_DATA0, IIO_MOD_LIGHT_BOTH, 0,
				 ltr501_als_event_spec,
				 ARRAY_SIZE(ltr501_als_event_spec)),
	LTR501_INTENSITY_CHANNEL(1, LTR501_ALS_DATA1, IIO_MOD_LIGHT_IR,
				 BIT(IIO_CHAN_INFO_SCALE) |
				 BIT(IIO_CHAN_INFO_INT_TIME) |
				 BIT(IIO_CHAN_INFO_SAMP_FREQ),
				 शून्य, 0),
	अणु
		.type = IIO_PROXIMITY,
		.address = LTR501_PS_DATA,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = 2,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 11,
			.storagebits = 16,
			.endianness = IIO_CPU,
		पूर्ण,
		.event_spec = ltr501_pxs_event_spec,
		.num_event_specs = ARRAY_SIZE(ltr501_pxs_event_spec),
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ltr301_channels[] = अणु
	LTR501_LIGHT_CHANNEL(),
	LTR501_INTENSITY_CHANNEL(0, LTR501_ALS_DATA0, IIO_MOD_LIGHT_BOTH, 0,
				 ltr501_als_event_spec,
				 ARRAY_SIZE(ltr501_als_event_spec)),
	LTR501_INTENSITY_CHANNEL(1, LTR501_ALS_DATA1, IIO_MOD_LIGHT_IR,
				 BIT(IIO_CHAN_INFO_SCALE) |
				 BIT(IIO_CHAN_INFO_INT_TIME) |
				 BIT(IIO_CHAN_INFO_SAMP_FREQ),
				 शून्य, 0),
	IIO_CHAN_SOFT_TIMESTAMP(2),
पूर्ण;

अटल पूर्णांक ltr501_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा ltr501_data *data = iio_priv(indio_dev);
	__le16 buf[2];
	पूर्णांक ret, i;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			ret = iio_device_claim_direct_mode(indio_dev);
			अगर (ret)
				वापस ret;

			mutex_lock(&data->lock_als);
			ret = ltr501_पढ़ो_als(data, buf);
			mutex_unlock(&data->lock_als);
			iio_device_release_direct_mode(indio_dev);
			अगर (ret < 0)
				वापस ret;
			*val = ltr501_calculate_lux(le16_to_cpu(buf[1]),
						    le16_to_cpu(buf[0]));
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		चयन (chan->type) अणु
		हाल IIO_INTENSITY:
			mutex_lock(&data->lock_als);
			ret = ltr501_पढ़ो_als(data, buf);
			mutex_unlock(&data->lock_als);
			अगर (ret < 0)
				अवरोध;
			*val = le16_to_cpu(chan->address == LTR501_ALS_DATA1 ?
					   buf[0] : buf[1]);
			ret = IIO_VAL_INT;
			अवरोध;
		हाल IIO_PROXIMITY:
			mutex_lock(&data->lock_ps);
			ret = ltr501_पढ़ो_ps(data);
			mutex_unlock(&data->lock_ps);
			अगर (ret < 0)
				अवरोध;
			*val = ret & LTR501_PS_DATA_MASK;
			ret = IIO_VAL_INT;
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		iio_device_release_direct_mode(indio_dev);
		वापस ret;

	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_INTENSITY:
			i = (data->als_contr & data->chip_info->als_gain_mask)
			     >> data->chip_info->als_gain_shअगरt;
			*val = data->chip_info->als_gain[i].scale;
			*val2 = data->chip_info->als_gain[i].uscale;
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_PROXIMITY:
			i = (data->ps_contr & LTR501_CONTR_PS_GAIN_MASK) >>
				LTR501_CONTR_PS_GAIN_SHIFT;
			*val = data->chip_info->ps_gain[i].scale;
			*val2 = data->chip_info->ps_gain[i].uscale;
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_INT_TIME:
		चयन (chan->type) अणु
		हाल IIO_INTENSITY:
			वापस ltr501_पढ़ो_it_समय(data, val, val2);
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		चयन (chan->type) अणु
		हाल IIO_INTENSITY:
			वापस ltr501_als_पढ़ो_samp_freq(data, val, val2);
		हाल IIO_PROXIMITY:
			वापस ltr501_ps_पढ़ो_samp_freq(data, val, val2);
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ltr501_get_gain_index(स्थिर काष्ठा ltr501_gain *gain, पूर्णांक size,
				 पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++)
		अगर (val == gain[i].scale && val2 == gain[i].uscale)
			वापस i;

	वापस -1;
पूर्ण

अटल पूर्णांक ltr501_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा ltr501_data *data = iio_priv(indio_dev);
	पूर्णांक i, ret, freq_val, freq_val2;
	काष्ठा ltr501_chip_info *info = data->chip_info;

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret)
		वापस ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_INTENSITY:
			i = ltr501_get_gain_index(info->als_gain,
						  info->als_gain_tbl_size,
						  val, val2);
			अगर (i < 0) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण

			data->als_contr &= ~info->als_gain_mask;
			data->als_contr |= i << info->als_gain_shअगरt;

			ret = regmap_ग_लिखो(data->regmap, LTR501_ALS_CONTR,
					   data->als_contr);
			अवरोध;
		हाल IIO_PROXIMITY:
			i = ltr501_get_gain_index(info->ps_gain,
						  info->ps_gain_tbl_size,
						  val, val2);
			अगर (i < 0) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			data->ps_contr &= ~LTR501_CONTR_PS_GAIN_MASK;
			data->ps_contr |= i << LTR501_CONTR_PS_GAIN_SHIFT;

			ret = regmap_ग_लिखो(data->regmap, LTR501_PS_CONTR,
					   data->ps_contr);
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल IIO_CHAN_INFO_INT_TIME:
		चयन (chan->type) अणु
		हाल IIO_INTENSITY:
			अगर (val != 0) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			mutex_lock(&data->lock_als);
			ret = ltr501_set_it_समय(data, val2);
			mutex_unlock(&data->lock_als);
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		चयन (chan->type) अणु
		हाल IIO_INTENSITY:
			ret = ltr501_als_पढ़ो_samp_freq(data, &freq_val,
							&freq_val2);
			अगर (ret < 0)
				अवरोध;

			ret = ltr501_als_ग_लिखो_samp_freq(data, val, val2);
			अगर (ret < 0)
				अवरोध;

			/* update persistence count when changing frequency */
			ret = ltr501_ग_लिखो_पूर्णांकr_prst(data, chan->type,
						     0, data->als_period);

			अगर (ret < 0)
				ret = ltr501_als_ग_लिखो_samp_freq(data, freq_val,
								 freq_val2);
			अवरोध;
		हाल IIO_PROXIMITY:
			ret = ltr501_ps_पढ़ो_samp_freq(data, &freq_val,
						       &freq_val2);
			अगर (ret < 0)
				अवरोध;

			ret = ltr501_ps_ग_लिखो_samp_freq(data, val, val2);
			अगर (ret < 0)
				अवरोध;

			/* update persistence count when changing frequency */
			ret = ltr501_ग_लिखो_पूर्णांकr_prst(data, chan->type,
						     0, data->ps_period);

			अगर (ret < 0)
				ret = ltr501_ps_ग_लिखो_samp_freq(data, freq_val,
								freq_val2);
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	iio_device_release_direct_mode(indio_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक ltr501_पढ़ो_thresh(स्थिर काष्ठा iio_dev *indio_dev,
			      स्थिर काष्ठा iio_chan_spec *chan,
			      क्रमागत iio_event_type type,
			      क्रमागत iio_event_direction dir,
			      क्रमागत iio_event_info info,
			      पूर्णांक *val, पूर्णांक *val2)
अणु
	स्थिर काष्ठा ltr501_data *data = iio_priv(indio_dev);
	पूर्णांक ret, thresh_data;

	चयन (chan->type) अणु
	हाल IIO_INTENSITY:
		चयन (dir) अणु
		हाल IIO_EV_सूची_RISING:
			ret = regmap_bulk_पढ़ो(data->regmap,
					       LTR501_ALS_THRESH_UP,
					       &thresh_data, 2);
			अगर (ret < 0)
				वापस ret;
			*val = thresh_data & LTR501_ALS_THRESH_MASK;
			वापस IIO_VAL_INT;
		हाल IIO_EV_सूची_FALLING:
			ret = regmap_bulk_पढ़ो(data->regmap,
					       LTR501_ALS_THRESH_LOW,
					       &thresh_data, 2);
			अगर (ret < 0)
				वापस ret;
			*val = thresh_data & LTR501_ALS_THRESH_MASK;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_PROXIMITY:
		चयन (dir) अणु
		हाल IIO_EV_सूची_RISING:
			ret = regmap_bulk_पढ़ो(data->regmap,
					       LTR501_PS_THRESH_UP,
					       &thresh_data, 2);
			अगर (ret < 0)
				वापस ret;
			*val = thresh_data & LTR501_PS_THRESH_MASK;
			वापस IIO_VAL_INT;
		हाल IIO_EV_सूची_FALLING:
			ret = regmap_bulk_पढ़ो(data->regmap,
					       LTR501_PS_THRESH_LOW,
					       &thresh_data, 2);
			अगर (ret < 0)
				वापस ret;
			*val = thresh_data & LTR501_PS_THRESH_MASK;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ltr501_ग_लिखो_thresh(काष्ठा iio_dev *indio_dev,
			       स्थिर काष्ठा iio_chan_spec *chan,
			       क्रमागत iio_event_type type,
			       क्रमागत iio_event_direction dir,
			       क्रमागत iio_event_info info,
			       पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा ltr501_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (val < 0)
		वापस -EINVAL;

	चयन (chan->type) अणु
	हाल IIO_INTENSITY:
		अगर (val > LTR501_ALS_THRESH_MASK)
			वापस -EINVAL;
		चयन (dir) अणु
		हाल IIO_EV_सूची_RISING:
			mutex_lock(&data->lock_als);
			ret = regmap_bulk_ग_लिखो(data->regmap,
						LTR501_ALS_THRESH_UP,
						&val, 2);
			mutex_unlock(&data->lock_als);
			वापस ret;
		हाल IIO_EV_सूची_FALLING:
			mutex_lock(&data->lock_als);
			ret = regmap_bulk_ग_लिखो(data->regmap,
						LTR501_ALS_THRESH_LOW,
						&val, 2);
			mutex_unlock(&data->lock_als);
			वापस ret;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_PROXIMITY:
		अगर (val > LTR501_PS_THRESH_MASK)
			वापस -EINVAL;
		चयन (dir) अणु
		हाल IIO_EV_सूची_RISING:
			mutex_lock(&data->lock_ps);
			ret = regmap_bulk_ग_लिखो(data->regmap,
						LTR501_PS_THRESH_UP,
						&val, 2);
			mutex_unlock(&data->lock_ps);
			वापस ret;
		हाल IIO_EV_सूची_FALLING:
			mutex_lock(&data->lock_ps);
			ret = regmap_bulk_ग_लिखो(data->regmap,
						LTR501_PS_THRESH_LOW,
						&val, 2);
			mutex_unlock(&data->lock_ps);
			वापस ret;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ltr501_पढ़ो_event(काष्ठा iio_dev *indio_dev,
			     स्थिर काष्ठा iio_chan_spec *chan,
			     क्रमागत iio_event_type type,
			     क्रमागत iio_event_direction dir,
			     क्रमागत iio_event_info info,
			     पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक ret;

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		वापस ltr501_पढ़ो_thresh(indio_dev, chan, type, dir,
					  info, val, val2);
	हाल IIO_EV_INFO_PERIOD:
		ret = ltr501_पढ़ो_पूर्णांकr_prst(iio_priv(indio_dev),
					    chan->type, val2);
		*val = *val2 / 1000000;
		*val2 = *val2 % 1000000;
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ltr501_ग_लिखो_event(काष्ठा iio_dev *indio_dev,
			      स्थिर काष्ठा iio_chan_spec *chan,
			      क्रमागत iio_event_type type,
			      क्रमागत iio_event_direction dir,
			      क्रमागत iio_event_info info,
			      पूर्णांक val, पूर्णांक val2)
अणु
	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		अगर (val2 != 0)
			वापस -EINVAL;
		वापस ltr501_ग_लिखो_thresh(indio_dev, chan, type, dir,
					   info, val, val2);
	हाल IIO_EV_INFO_PERIOD:
		वापस ltr501_ग_लिखो_पूर्णांकr_prst(iio_priv(indio_dev), chan->type,
					      val, val2);
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ltr501_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir)
अणु
	काष्ठा ltr501_data *data = iio_priv(indio_dev);
	पूर्णांक ret, status;

	चयन (chan->type) अणु
	हाल IIO_INTENSITY:
		ret = regmap_field_पढ़ो(data->reg_als_पूर्णांकr, &status);
		अगर (ret < 0)
			वापस ret;
		वापस status;
	हाल IIO_PROXIMITY:
		ret = regmap_field_पढ़ो(data->reg_ps_पूर्णांकr, &status);
		अगर (ret < 0)
			वापस ret;
		वापस status;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ltr501_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type,
				     क्रमागत iio_event_direction dir, पूर्णांक state)
अणु
	काष्ठा ltr501_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	/* only 1 and 0 are valid inमाला_दो */
	अगर (state != 1  && state != 0)
		वापस -EINVAL;

	चयन (chan->type) अणु
	हाल IIO_INTENSITY:
		mutex_lock(&data->lock_als);
		ret = regmap_field_ग_लिखो(data->reg_als_पूर्णांकr, state);
		mutex_unlock(&data->lock_als);
		वापस ret;
	हाल IIO_PROXIMITY:
		mutex_lock(&data->lock_ps);
		ret = regmap_field_ग_लिखो(data->reg_ps_पूर्णांकr, state);
		mutex_unlock(&data->lock_ps);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार ltr501_show_proximity_scale_avail(काष्ठा device *dev,
						 काष्ठा device_attribute *attr,
						 अक्षर *buf)
अणु
	काष्ठा ltr501_data *data = iio_priv(dev_to_iio_dev(dev));
	काष्ठा ltr501_chip_info *info = data->chip_info;
	sमाप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < info->ps_gain_tbl_size; i++) अणु
		अगर (info->ps_gain[i].scale == LTR501_RESERVED_GAIN)
			जारी;
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%d.%06d ",
				 info->ps_gain[i].scale,
				 info->ps_gain[i].uscale);
	पूर्ण

	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल sमाप_प्रकार ltr501_show_पूर्णांकensity_scale_avail(काष्ठा device *dev,
						 काष्ठा device_attribute *attr,
						 अक्षर *buf)
अणु
	काष्ठा ltr501_data *data = iio_priv(dev_to_iio_dev(dev));
	काष्ठा ltr501_chip_info *info = data->chip_info;
	sमाप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < info->als_gain_tbl_size; i++) अणु
		अगर (info->als_gain[i].scale == LTR501_RESERVED_GAIN)
			जारी;
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%d.%06d ",
				 info->als_gain[i].scale,
				 info->als_gain[i].uscale);
	पूर्ण

	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल IIO_CONST_ATTR_INT_TIME_AVAIL("0.05 0.1 0.2 0.4");
अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL("20 10 5 2 1 0.5");

अटल IIO_DEVICE_ATTR(in_proximity_scale_available, S_IRUGO,
		       ltr501_show_proximity_scale_avail, शून्य, 0);
अटल IIO_DEVICE_ATTR(in_पूर्णांकensity_scale_available, S_IRUGO,
		       ltr501_show_पूर्णांकensity_scale_avail, शून्य, 0);

अटल काष्ठा attribute *ltr501_attributes[] = अणु
	&iio_dev_attr_in_proximity_scale_available.dev_attr.attr,
	&iio_dev_attr_in_पूर्णांकensity_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_पूर्णांकegration_समय_available.dev_attr.attr,
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *ltr301_attributes[] = अणु
	&iio_dev_attr_in_पूर्णांकensity_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_पूर्णांकegration_समय_available.dev_attr.attr,
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ltr501_attribute_group = अणु
	.attrs = ltr501_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ltr301_attribute_group = अणु
	.attrs = ltr301_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info ltr501_info_no_irq = अणु
	.पढ़ो_raw = ltr501_पढ़ो_raw,
	.ग_लिखो_raw = ltr501_ग_लिखो_raw,
	.attrs = &ltr501_attribute_group,
पूर्ण;

अटल स्थिर काष्ठा iio_info ltr501_info = अणु
	.पढ़ो_raw = ltr501_पढ़ो_raw,
	.ग_लिखो_raw = ltr501_ग_लिखो_raw,
	.attrs = &ltr501_attribute_group,
	.पढ़ो_event_value	= &ltr501_पढ़ो_event,
	.ग_लिखो_event_value	= &ltr501_ग_लिखो_event,
	.पढ़ो_event_config	= &ltr501_पढ़ो_event_config,
	.ग_लिखो_event_config	= &ltr501_ग_लिखो_event_config,
पूर्ण;

अटल स्थिर काष्ठा iio_info ltr301_info_no_irq = अणु
	.पढ़ो_raw = ltr501_पढ़ो_raw,
	.ग_लिखो_raw = ltr501_ग_लिखो_raw,
	.attrs = &ltr301_attribute_group,
पूर्ण;

अटल स्थिर काष्ठा iio_info ltr301_info = अणु
	.पढ़ो_raw = ltr501_पढ़ो_raw,
	.ग_लिखो_raw = ltr501_ग_लिखो_raw,
	.attrs = &ltr301_attribute_group,
	.पढ़ो_event_value	= &ltr501_पढ़ो_event,
	.ग_लिखो_event_value	= &ltr501_ग_लिखो_event,
	.पढ़ो_event_config	= &ltr501_पढ़ो_event_config,
	.ग_लिखो_event_config	= &ltr501_ग_लिखो_event_config,
पूर्ण;

अटल काष्ठा ltr501_chip_info ltr501_chip_info_tbl[] = अणु
	[ltr501] = अणु
		.partid = 0x08,
		.als_gain = ltr501_als_gain_tbl,
		.als_gain_tbl_size = ARRAY_SIZE(ltr501_als_gain_tbl),
		.ps_gain = ltr501_ps_gain_tbl,
		.ps_gain_tbl_size = ARRAY_SIZE(ltr501_ps_gain_tbl),
		.als_mode_active = BIT(0) | BIT(1),
		.als_gain_mask = BIT(3),
		.als_gain_shअगरt = 3,
		.info = &ltr501_info,
		.info_no_irq = &ltr501_info_no_irq,
		.channels = ltr501_channels,
		.no_channels = ARRAY_SIZE(ltr501_channels),
	पूर्ण,
	[ltr559] = अणु
		.partid = 0x09,
		.als_gain = ltr559_als_gain_tbl,
		.als_gain_tbl_size = ARRAY_SIZE(ltr559_als_gain_tbl),
		.ps_gain = ltr559_ps_gain_tbl,
		.ps_gain_tbl_size = ARRAY_SIZE(ltr559_ps_gain_tbl),
		.als_mode_active = BIT(1),
		.als_gain_mask = BIT(2) | BIT(3) | BIT(4),
		.als_gain_shअगरt = 2,
		.info = &ltr501_info,
		.info_no_irq = &ltr501_info_no_irq,
		.channels = ltr501_channels,
		.no_channels = ARRAY_SIZE(ltr501_channels),
	पूर्ण,
	[ltr301] = अणु
		.partid = 0x08,
		.als_gain = ltr501_als_gain_tbl,
		.als_gain_tbl_size = ARRAY_SIZE(ltr501_als_gain_tbl),
		.als_mode_active = BIT(0) | BIT(1),
		.als_gain_mask = BIT(3),
		.als_gain_shअगरt = 3,
		.info = &ltr301_info,
		.info_no_irq = &ltr301_info_no_irq,
		.channels = ltr301_channels,
		.no_channels = ARRAY_SIZE(ltr301_channels),
	पूर्ण,
पूर्ण;

अटल पूर्णांक ltr501_ग_लिखो_contr(काष्ठा ltr501_data *data, u8 als_val, u8 ps_val)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(data->regmap, LTR501_ALS_CONTR, als_val);
	अगर (ret < 0)
		वापस ret;

	वापस regmap_ग_लिखो(data->regmap, LTR501_PS_CONTR, ps_val);
पूर्ण

अटल irqवापस_t ltr501_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा ltr501_data *data = iio_priv(indio_dev);
	काष्ठा अणु
		u16 channels[3];
		s64 ts __aligned(8);
	पूर्ण scan;
	__le16 als_buf[2];
	u8 mask = 0;
	पूर्णांक j = 0;
	पूर्णांक ret, psdata;

	स_रखो(&scan, 0, माप(scan));

	/* figure out which data needs to be पढ़ोy */
	अगर (test_bit(0, indio_dev->active_scan_mask) ||
	    test_bit(1, indio_dev->active_scan_mask))
		mask |= LTR501_STATUS_ALS_RDY;
	अगर (test_bit(2, indio_dev->active_scan_mask))
		mask |= LTR501_STATUS_PS_RDY;

	ret = ltr501_drdy(data, mask);
	अगर (ret < 0)
		जाओ करोne;

	अगर (mask & LTR501_STATUS_ALS_RDY) अणु
		ret = regmap_bulk_पढ़ो(data->regmap, LTR501_ALS_DATA1,
				       als_buf, माप(als_buf));
		अगर (ret < 0)
			वापस ret;
		अगर (test_bit(0, indio_dev->active_scan_mask))
			scan.channels[j++] = le16_to_cpu(als_buf[1]);
		अगर (test_bit(1, indio_dev->active_scan_mask))
			scan.channels[j++] = le16_to_cpu(als_buf[0]);
	पूर्ण

	अगर (mask & LTR501_STATUS_PS_RDY) अणु
		ret = regmap_bulk_पढ़ो(data->regmap, LTR501_PS_DATA,
				       &psdata, 2);
		अगर (ret < 0)
			जाओ करोne;
		scan.channels[j++] = psdata & LTR501_PS_DATA_MASK;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, &scan,
					   iio_get_समय_ns(indio_dev));

करोne:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ltr501_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा ltr501_data *data = iio_priv(indio_dev);
	पूर्णांक ret, status;

	ret = regmap_पढ़ो(data->regmap, LTR501_ALS_PS_STATUS, &status);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev,
			"irq read int reg failed\n");
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (status & LTR501_STATUS_ALS_INTR)
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_INTENSITY, 0,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_सूची_EITHER),
			       iio_get_समय_ns(indio_dev));

	अगर (status & LTR501_STATUS_PS_INTR)
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_PROXIMITY, 0,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_सूची_EITHER),
			       iio_get_समय_ns(indio_dev));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ltr501_init(काष्ठा ltr501_data *data)
अणु
	पूर्णांक ret, status;

	ret = regmap_पढ़ो(data->regmap, LTR501_ALS_CONTR, &status);
	अगर (ret < 0)
		वापस ret;

	data->als_contr = status | data->chip_info->als_mode_active;

	ret = regmap_पढ़ो(data->regmap, LTR501_PS_CONTR, &status);
	अगर (ret < 0)
		वापस ret;

	data->ps_contr = status | LTR501_CONTR_ACTIVE;

	ret = ltr501_पढ़ो_पूर्णांकr_prst(data, IIO_INTENSITY, &data->als_period);
	अगर (ret < 0)
		वापस ret;

	ret = ltr501_पढ़ो_पूर्णांकr_prst(data, IIO_PROXIMITY, &data->ps_period);
	अगर (ret < 0)
		वापस ret;

	वापस ltr501_ग_लिखो_contr(data, data->als_contr, data->ps_contr);
पूर्ण

अटल bool ltr501_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल LTR501_ALS_DATA1:
	हाल LTR501_ALS_DATA0:
	हाल LTR501_ALS_PS_STATUS:
	हाल LTR501_PS_DATA:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config ltr501_regmap_config = अणु
	.name =  LTR501_REGMAP_NAME,
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = LTR501_MAX_REG,
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_reg = ltr501_is_अस्थिर_reg,
पूर्ण;

अटल पूर्णांक ltr501_घातerकरोwn(काष्ठा ltr501_data *data)
अणु
	वापस ltr501_ग_लिखो_contr(data, data->als_contr &
				  ~data->chip_info->als_mode_active,
				  data->ps_contr & ~LTR501_CONTR_ACTIVE);
पूर्ण

अटल स्थिर अक्षर *ltr501_match_acpi_device(काष्ठा device *dev, पूर्णांक *chip_idx)
अणु
	स्थिर काष्ठा acpi_device_id *id;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	अगर (!id)
		वापस शून्य;
	*chip_idx = id->driver_data;
	वापस dev_name(dev);
पूर्ण

अटल पूर्णांक ltr501_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ltr501_data *data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा regmap *regmap;
	पूर्णांक ret, partid, chip_idx = 0;
	स्थिर अक्षर *name = शून्य;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	regmap = devm_regmap_init_i2c(client, &ltr501_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "Regmap initialization failed.\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	data->regmap = regmap;
	mutex_init(&data->lock_als);
	mutex_init(&data->lock_ps);

	data->reg_it = devm_regmap_field_alloc(&client->dev, regmap,
					       reg_field_it);
	अगर (IS_ERR(data->reg_it)) अणु
		dev_err(&client->dev, "Integ time reg field init failed.\n");
		वापस PTR_ERR(data->reg_it);
	पूर्ण

	data->reg_als_पूर्णांकr = devm_regmap_field_alloc(&client->dev, regmap,
						     reg_field_als_पूर्णांकr);
	अगर (IS_ERR(data->reg_als_पूर्णांकr)) अणु
		dev_err(&client->dev, "ALS intr mode reg field init failed\n");
		वापस PTR_ERR(data->reg_als_पूर्णांकr);
	पूर्ण

	data->reg_ps_पूर्णांकr = devm_regmap_field_alloc(&client->dev, regmap,
						    reg_field_ps_पूर्णांकr);
	अगर (IS_ERR(data->reg_ps_पूर्णांकr)) अणु
		dev_err(&client->dev, "PS intr mode reg field init failed.\n");
		वापस PTR_ERR(data->reg_ps_पूर्णांकr);
	पूर्ण

	data->reg_als_rate = devm_regmap_field_alloc(&client->dev, regmap,
						     reg_field_als_rate);
	अगर (IS_ERR(data->reg_als_rate)) अणु
		dev_err(&client->dev, "ALS samp rate field init failed.\n");
		वापस PTR_ERR(data->reg_als_rate);
	पूर्ण

	data->reg_ps_rate = devm_regmap_field_alloc(&client->dev, regmap,
						    reg_field_ps_rate);
	अगर (IS_ERR(data->reg_ps_rate)) अणु
		dev_err(&client->dev, "PS samp rate field init failed.\n");
		वापस PTR_ERR(data->reg_ps_rate);
	पूर्ण

	data->reg_als_prst = devm_regmap_field_alloc(&client->dev, regmap,
						     reg_field_als_prst);
	अगर (IS_ERR(data->reg_als_prst)) अणु
		dev_err(&client->dev, "ALS prst reg field init failed\n");
		वापस PTR_ERR(data->reg_als_prst);
	पूर्ण

	data->reg_ps_prst = devm_regmap_field_alloc(&client->dev, regmap,
						    reg_field_ps_prst);
	अगर (IS_ERR(data->reg_ps_prst)) अणु
		dev_err(&client->dev, "PS prst reg field init failed.\n");
		वापस PTR_ERR(data->reg_ps_prst);
	पूर्ण

	ret = regmap_पढ़ो(data->regmap, LTR501_PART_ID, &partid);
	अगर (ret < 0)
		वापस ret;

	अगर (id) अणु
		name = id->name;
		chip_idx = id->driver_data;
	पूर्ण अन्यथा  अगर (ACPI_HANDLE(&client->dev)) अणु
		name = ltr501_match_acpi_device(&client->dev, &chip_idx);
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	data->chip_info = &ltr501_chip_info_tbl[chip_idx];

	अगर ((partid >> 4) != data->chip_info->partid)
		वापस -ENODEV;

	indio_dev->info = data->chip_info->info;
	indio_dev->channels = data->chip_info->channels;
	indio_dev->num_channels = data->chip_info->no_channels;
	indio_dev->name = name;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = ltr501_init(data);
	अगर (ret < 0)
		वापस ret;

	अगर (client->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						शून्य, ltr501_पूर्णांकerrupt_handler,
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						"ltr501_thresh_event",
						indio_dev);
		अगर (ret) अणु
			dev_err(&client->dev, "request irq (%d) failed\n",
				client->irq);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		indio_dev->info = data->chip_info->info_no_irq;
	पूर्ण

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
					 ltr501_trigger_handler, शून्य);
	अगर (ret)
		जाओ घातerकरोwn_on_error;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_unreg_buffer;

	वापस 0;

error_unreg_buffer:
	iio_triggered_buffer_cleanup(indio_dev);
घातerकरोwn_on_error:
	ltr501_घातerकरोwn(data);
	वापस ret;
पूर्ण

अटल पूर्णांक ltr501_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	ltr501_घातerकरोwn(iio_priv(indio_dev));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ltr501_suspend(काष्ठा device *dev)
अणु
	काष्ठा ltr501_data *data = iio_priv(i2c_get_clientdata(
					    to_i2c_client(dev)));
	वापस ltr501_घातerकरोwn(data);
पूर्ण

अटल पूर्णांक ltr501_resume(काष्ठा device *dev)
अणु
	काष्ठा ltr501_data *data = iio_priv(i2c_get_clientdata(
					    to_i2c_client(dev)));

	वापस ltr501_ग_लिखो_contr(data, data->als_contr,
		data->ps_contr);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(ltr501_pm_ops, ltr501_suspend, ltr501_resume);

अटल स्थिर काष्ठा acpi_device_id ltr_acpi_match[] = अणु
	अणु"LTER0501", ltr501पूर्ण,
	अणु"LTER0559", ltr559पूर्ण,
	अणु"LTER0301", ltr301पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ltr_acpi_match);

अटल स्थिर काष्ठा i2c_device_id ltr501_id[] = अणु
	अणु "ltr501", ltr501पूर्ण,
	अणु "ltr559", ltr559पूर्ण,
	अणु "ltr301", ltr301पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ltr501_id);

अटल काष्ठा i2c_driver ltr501_driver = अणु
	.driver = अणु
		.name   = LTR501_DRV_NAME,
		.pm	= &ltr501_pm_ops,
		.acpi_match_table = ACPI_PTR(ltr_acpi_match),
	पूर्ण,
	.probe  = ltr501_probe,
	.हटाओ	= ltr501_हटाओ,
	.id_table = ltr501_id,
पूर्ण;

module_i2c_driver(ltr501_driver);

MODULE_AUTHOR("Peter Meerwald <pmeerw@pmeerw.net>");
MODULE_DESCRIPTION("Lite-On LTR501 ambient light and proximity sensor driver");
MODULE_LICENSE("GPL");
