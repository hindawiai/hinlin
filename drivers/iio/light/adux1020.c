<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * adux1020.c - Support क्रम Analog Devices ADUX1020 photometric sensor
 *
 * Copyright (C) 2019 Linaro Ltd.
 * Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
 *
 * TODO: Triggered buffer support
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regmap.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>

#घोषणा ADUX1020_REGMAP_NAME		"adux1020_regmap"
#घोषणा ADUX1020_DRV_NAME		"adux1020"

/* System रेजिस्टरs */
#घोषणा ADUX1020_REG_CHIP_ID		0x08
#घोषणा ADUX1020_REG_SLAVE_ADDRESS	0x09

#घोषणा ADUX1020_REG_SW_RESET		0x0f
#घोषणा ADUX1020_REG_INT_ENABLE		0x1c
#घोषणा ADUX1020_REG_INT_POLARITY	0x1d
#घोषणा ADUX1020_REG_PROX_TH_ON1	0x2a
#घोषणा ADUX1020_REG_PROX_TH_OFF1	0x2b
#घोषणा	ADUX1020_REG_PROX_TYPE		0x2f
#घोषणा	ADUX1020_REG_TEST_MODES_3	0x32
#घोषणा	ADUX1020_REG_FORCE_MODE		0x33
#घोषणा	ADUX1020_REG_FREQUENCY		0x40
#घोषणा ADUX1020_REG_LED_CURRENT	0x41
#घोषणा	ADUX1020_REG_OP_MODE		0x45
#घोषणा	ADUX1020_REG_INT_MASK		0x48
#घोषणा	ADUX1020_REG_INT_STATUS		0x49
#घोषणा	ADUX1020_REG_DATA_BUFFER	0x60

/* Chip ID bits */
#घोषणा ADUX1020_CHIP_ID_MASK		GENMASK(11, 0)
#घोषणा ADUX1020_CHIP_ID		0x03fc

#घोषणा ADUX1020_SW_RESET		BIT(1)
#घोषणा ADUX1020_FIFO_FLUSH		BIT(15)
#घोषणा ADUX1020_OP_MODE_MASK		GENMASK(3, 0)
#घोषणा ADUX1020_DATA_OUT_MODE_MASK	GENMASK(7, 4)
#घोषणा ADUX1020_DATA_OUT_PROX_I	FIELD_PREP(ADUX1020_DATA_OUT_MODE_MASK, 1)

#घोषणा ADUX1020_MODE_INT_MASK		GENMASK(7, 0)
#घोषणा ADUX1020_INT_ENABLE		0x2094
#घोषणा ADUX1020_INT_DISABLE		0x2090
#घोषणा ADUX1020_PROX_INT_ENABLE	0x00f0
#घोषणा ADUX1020_PROX_ON1_INT		BIT(0)
#घोषणा ADUX1020_PROX_OFF1_INT		BIT(1)
#घोषणा ADUX1020_FIFO_INT_ENABLE	0x7f
#घोषणा ADUX1020_MODE_INT_DISABLE	0xff
#घोषणा ADUX1020_MODE_INT_STATUS_MASK	GENMASK(7, 0)
#घोषणा ADUX1020_FIFO_STATUS_MASK	GENMASK(15, 8)
#घोषणा ADUX1020_INT_CLEAR		0xff
#घोषणा ADUX1020_PROX_TYPE		BIT(15)

#घोषणा ADUX1020_INT_PROX_ON1		BIT(0)
#घोषणा ADUX1020_INT_PROX_OFF1		BIT(1)

#घोषणा ADUX1020_FORCE_CLOCK_ON		0x0f4f
#घोषणा ADUX1020_FORCE_CLOCK_RESET	0x0040
#घोषणा ADUX1020_ACTIVE_4_STATE		0x0008

#घोषणा ADUX1020_PROX_FREQ_MASK		GENMASK(7, 4)
#घोषणा ADUX1020_PROX_FREQ(x)		FIELD_PREP(ADUX1020_PROX_FREQ_MASK, x)

#घोषणा ADUX1020_LED_CURRENT_MASK	GENMASK(3, 0)
#घोषणा ADUX1020_LED_PIREF_EN		BIT(12)

/* Operating modes */
क्रमागत adux1020_op_modes अणु
	ADUX1020_MODE_STANDBY,
	ADUX1020_MODE_PROX_I,
	ADUX1020_MODE_PROX_XY,
	ADUX1020_MODE_GEST,
	ADUX1020_MODE_SAMPLE,
	ADUX1020_MODE_FORCE = 0x0e,
	ADUX1020_MODE_IDLE = 0x0f,
पूर्ण;

काष्ठा adux1020_data अणु
	काष्ठा i2c_client *client;
	काष्ठा iio_dev *indio_dev;
	काष्ठा mutex lock;
	काष्ठा regmap *regmap;
पूर्ण;

काष्ठा adux1020_mode_data अणु
	u8 bytes;
	u8 buf_len;
	u16 पूर्णांक_en;
पूर्ण;

अटल स्थिर काष्ठा adux1020_mode_data adux1020_modes[] = अणु
	[ADUX1020_MODE_PROX_I] = अणु
		.bytes = 2,
		.buf_len = 1,
		.पूर्णांक_en = ADUX1020_PROX_INT_ENABLE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config adux1020_regmap_config = अणु
	.name = ADUX1020_REGMAP_NAME,
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = 0x6F,
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence adux1020_def_conf[] = अणु
	अणु 0x000c, 0x000f पूर्ण,
	अणु 0x0010, 0x1010 पूर्ण,
	अणु 0x0011, 0x004c पूर्ण,
	अणु 0x0012, 0x5f0c पूर्ण,
	अणु 0x0013, 0xada5 पूर्ण,
	अणु 0x0014, 0x0080 पूर्ण,
	अणु 0x0015, 0x0000 पूर्ण,
	अणु 0x0016, 0x0600 पूर्ण,
	अणु 0x0017, 0x0000 पूर्ण,
	अणु 0x0018, 0x2693 पूर्ण,
	अणु 0x0019, 0x0004 पूर्ण,
	अणु 0x001a, 0x4280 पूर्ण,
	अणु 0x001b, 0x0060 पूर्ण,
	अणु 0x001c, 0x2094 पूर्ण,
	अणु 0x001d, 0x0020 पूर्ण,
	अणु 0x001e, 0x0001 पूर्ण,
	अणु 0x001f, 0x0100 पूर्ण,
	अणु 0x0020, 0x0320 पूर्ण,
	अणु 0x0021, 0x0A13 पूर्ण,
	अणु 0x0022, 0x0320 पूर्ण,
	अणु 0x0023, 0x0113 पूर्ण,
	अणु 0x0024, 0x0000 पूर्ण,
	अणु 0x0025, 0x2412 पूर्ण,
	अणु 0x0026, 0x2412 पूर्ण,
	अणु 0x0027, 0x0022 पूर्ण,
	अणु 0x0028, 0x0000 पूर्ण,
	अणु 0x0029, 0x0300 पूर्ण,
	अणु 0x002a, 0x0700 पूर्ण,
	अणु 0x002b, 0x0600 पूर्ण,
	अणु 0x002c, 0x6000 पूर्ण,
	अणु 0x002d, 0x4000 पूर्ण,
	अणु 0x002e, 0x0000 पूर्ण,
	अणु 0x002f, 0x0000 पूर्ण,
	अणु 0x0030, 0x0000 पूर्ण,
	अणु 0x0031, 0x0000 पूर्ण,
	अणु 0x0032, 0x0040 पूर्ण,
	अणु 0x0033, 0x0008 पूर्ण,
	अणु 0x0034, 0xE400 पूर्ण,
	अणु 0x0038, 0x8080 पूर्ण,
	अणु 0x0039, 0x8080 पूर्ण,
	अणु 0x003a, 0x2000 पूर्ण,
	अणु 0x003b, 0x1f00 पूर्ण,
	अणु 0x003c, 0x2000 पूर्ण,
	अणु 0x003d, 0x2000 पूर्ण,
	अणु 0x003e, 0x0000 पूर्ण,
	अणु 0x0040, 0x8069 पूर्ण,
	अणु 0x0041, 0x1f2f पूर्ण,
	अणु 0x0042, 0x4000 पूर्ण,
	अणु 0x0043, 0x0000 पूर्ण,
	अणु 0x0044, 0x0008 पूर्ण,
	अणु 0x0046, 0x0000 पूर्ण,
	अणु 0x0048, 0x00ef पूर्ण,
	अणु 0x0049, 0x0000 पूर्ण,
	अणु 0x0045, 0x0000 पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक adux1020_rates[][2] = अणु
	अणु 0, 100000 पूर्ण,
	अणु 0, 200000 पूर्ण,
	अणु 0, 500000 पूर्ण,
	अणु 1, 0 पूर्ण,
	अणु 2, 0 पूर्ण,
	अणु 5, 0 पूर्ण,
	अणु 10, 0 पूर्ण,
	अणु 20, 0 पूर्ण,
	अणु 50, 0 पूर्ण,
	अणु 100, 0 पूर्ण,
	अणु 190, 0 पूर्ण,
	अणु 450, 0 पूर्ण,
	अणु 820, 0 पूर्ण,
	अणु 1400, 0 पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक adux1020_led_currents[][2] = अणु
	अणु 0, 25000 पूर्ण,
	अणु 0, 40000 पूर्ण,
	अणु 0, 55000 पूर्ण,
	अणु 0, 70000 पूर्ण,
	अणु 0, 85000 पूर्ण,
	अणु 0, 100000 पूर्ण,
	अणु 0, 115000 पूर्ण,
	अणु 0, 130000 पूर्ण,
	अणु 0, 145000 पूर्ण,
	अणु 0, 160000 पूर्ण,
	अणु 0, 175000 पूर्ण,
	अणु 0, 190000 पूर्ण,
	अणु 0, 205000 पूर्ण,
	अणु 0, 220000 पूर्ण,
	अणु 0, 235000 पूर्ण,
	अणु 0, 250000 पूर्ण,
पूर्ण;

अटल पूर्णांक adux1020_flush_fअगरo(काष्ठा adux1020_data *data)
अणु
	पूर्णांक ret;

	/* Force Idle mode */
	ret = regmap_ग_लिखो(data->regmap, ADUX1020_REG_FORCE_MODE,
			   ADUX1020_ACTIVE_4_STATE);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_update_bits(data->regmap, ADUX1020_REG_OP_MODE,
				 ADUX1020_OP_MODE_MASK, ADUX1020_MODE_FORCE);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_update_bits(data->regmap, ADUX1020_REG_OP_MODE,
				 ADUX1020_OP_MODE_MASK, ADUX1020_MODE_IDLE);
	अगर (ret < 0)
		वापस ret;

	/* Flush FIFO */
	ret = regmap_ग_लिखो(data->regmap, ADUX1020_REG_TEST_MODES_3,
			   ADUX1020_FORCE_CLOCK_ON);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(data->regmap, ADUX1020_REG_INT_STATUS,
			   ADUX1020_FIFO_FLUSH);
	अगर (ret < 0)
		वापस ret;

	वापस regmap_ग_लिखो(data->regmap, ADUX1020_REG_TEST_MODES_3,
			    ADUX1020_FORCE_CLOCK_RESET);
पूर्ण

अटल पूर्णांक adux1020_पढ़ो_fअगरo(काष्ठा adux1020_data *data, u16 *buf, u8 buf_len)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक i, ret;

	/* Enable 32MHz घड़ी */
	ret = regmap_ग_लिखो(data->regmap, ADUX1020_REG_TEST_MODES_3,
			   ADUX1020_FORCE_CLOCK_ON);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < buf_len; i++) अणु
		ret = regmap_पढ़ो(data->regmap, ADUX1020_REG_DATA_BUFFER,
				  &regval);
		अगर (ret < 0)
			वापस ret;

		buf[i] = regval;
	पूर्ण

	/* Set 32MHz घड़ी to be controlled by पूर्णांकernal state machine */
	वापस regmap_ग_लिखो(data->regmap, ADUX1020_REG_TEST_MODES_3,
			    ADUX1020_FORCE_CLOCK_RESET);
पूर्ण

अटल पूर्णांक adux1020_set_mode(काष्ठा adux1020_data *data,
			     क्रमागत adux1020_op_modes mode)
अणु
	पूर्णांक ret;

	/* Switch to standby mode beक्रमe changing the mode */
	ret = regmap_ग_लिखो(data->regmap, ADUX1020_REG_OP_MODE,
			   ADUX1020_MODE_STANDBY);
	अगर (ret < 0)
		वापस ret;

	/* Set data out and चयन to the desired mode */
	चयन (mode) अणु
	हाल ADUX1020_MODE_PROX_I:
		ret = regmap_update_bits(data->regmap, ADUX1020_REG_OP_MODE,
					 ADUX1020_DATA_OUT_MODE_MASK,
					 ADUX1020_DATA_OUT_PROX_I);
		अगर (ret < 0)
			वापस ret;

		ret = regmap_update_bits(data->regmap, ADUX1020_REG_OP_MODE,
					 ADUX1020_OP_MODE_MASK,
					 ADUX1020_MODE_PROX_I);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adux1020_measure(काष्ठा adux1020_data *data,
			    क्रमागत adux1020_op_modes mode,
			    u16 *val)
अणु
	अचिन्हित पूर्णांक status;
	पूर्णांक ret, tries = 50;

	/* Disable INT pin as polling is going to be used */
	ret = regmap_ग_लिखो(data->regmap, ADUX1020_REG_INT_ENABLE,
			   ADUX1020_INT_DISABLE);
	अगर (ret < 0)
		वापस ret;

	/* Enable mode पूर्णांकerrupt */
	ret = regmap_update_bits(data->regmap, ADUX1020_REG_INT_MASK,
				 ADUX1020_MODE_INT_MASK,
				 adux1020_modes[mode].पूर्णांक_en);
	अगर (ret < 0)
		वापस ret;

	जबतक (tries--) अणु
		ret = regmap_पढ़ो(data->regmap, ADUX1020_REG_INT_STATUS,
				  &status);
		अगर (ret < 0)
			वापस ret;

		status &= ADUX1020_FIFO_STATUS_MASK;
		अगर (status >= adux1020_modes[mode].bytes)
			अवरोध;
		msleep(20);
	पूर्ण

	अगर (tries < 0)
		वापस -EIO;

	ret = adux1020_पढ़ो_fअगरo(data, val, adux1020_modes[mode].buf_len);
	अगर (ret < 0)
		वापस ret;

	/* Clear mode पूर्णांकerrupt */
	ret = regmap_ग_लिखो(data->regmap, ADUX1020_REG_INT_STATUS,
			   (~adux1020_modes[mode].पूर्णांक_en));
	अगर (ret < 0)
		वापस ret;

	/* Disable mode पूर्णांकerrupts */
	वापस regmap_update_bits(data->regmap, ADUX1020_REG_INT_MASK,
				  ADUX1020_MODE_INT_MASK,
				  ADUX1020_MODE_INT_DISABLE);
पूर्ण

अटल पूर्णांक adux1020_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा adux1020_data *data = iio_priv(indio_dev);
	u16 buf[3];
	पूर्णांक ret = -EINVAL;
	अचिन्हित पूर्णांक regval;

	mutex_lock(&data->lock);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_PROXIMITY:
			ret = adux1020_set_mode(data, ADUX1020_MODE_PROX_I);
			अगर (ret < 0)
				जाओ fail;

			ret = adux1020_measure(data, ADUX1020_MODE_PROX_I, buf);
			अगर (ret < 0)
				जाओ fail;

			*val = buf[0];
			ret = IIO_VAL_INT;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (chan->type) अणु
		हाल IIO_CURRENT:
			ret = regmap_पढ़ो(data->regmap,
					  ADUX1020_REG_LED_CURRENT, &regval);
			अगर (ret < 0)
				जाओ fail;

			regval = regval & ADUX1020_LED_CURRENT_MASK;

			*val = adux1020_led_currents[regval][0];
			*val2 = adux1020_led_currents[regval][1];

			ret = IIO_VAL_INT_PLUS_MICRO;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		चयन (chan->type) अणु
		हाल IIO_PROXIMITY:
			ret = regmap_पढ़ो(data->regmap, ADUX1020_REG_FREQUENCY,
					  &regval);
			अगर (ret < 0)
				जाओ fail;

			regval = FIELD_GET(ADUX1020_PROX_FREQ_MASK, regval);

			*val = adux1020_rates[regval][0];
			*val2 = adux1020_rates[regval][1];

			ret = IIO_VAL_INT_PLUS_MICRO;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

fail:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण;

अटल अंतरभूत पूर्णांक adux1020_find_index(स्थिर पूर्णांक array[][2], पूर्णांक count, पूर्णांक val,
				      पूर्णांक val2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		अगर (val == array[i][0] && val2 == array[i][1])
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक adux1020_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा adux1020_data *data = iio_priv(indio_dev);
	पूर्णांक i, ret = -EINVAL;

	mutex_lock(&data->lock);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (chan->type == IIO_PROXIMITY) अणु
			i = adux1020_find_index(adux1020_rates,
						ARRAY_SIZE(adux1020_rates),
						val, val2);
			अगर (i < 0) अणु
				ret = i;
				जाओ fail;
			पूर्ण

			ret = regmap_update_bits(data->regmap,
						 ADUX1020_REG_FREQUENCY,
						 ADUX1020_PROX_FREQ_MASK,
						 ADUX1020_PROX_FREQ(i));
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_PROCESSED:
		अगर (chan->type == IIO_CURRENT) अणु
			i = adux1020_find_index(adux1020_led_currents,
					ARRAY_SIZE(adux1020_led_currents),
					val, val2);
			अगर (i < 0) अणु
				ret = i;
				जाओ fail;
			पूर्ण

			ret = regmap_update_bits(data->regmap,
						 ADUX1020_REG_LED_CURRENT,
						 ADUX1020_LED_CURRENT_MASK, i);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

fail:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक adux1020_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
				       स्थिर काष्ठा iio_chan_spec *chan,
				       क्रमागत iio_event_type type,
				       क्रमागत iio_event_direction dir, पूर्णांक state)
अणु
	काष्ठा adux1020_data *data = iio_priv(indio_dev);
	पूर्णांक ret, mask;

	mutex_lock(&data->lock);

	ret = regmap_ग_लिखो(data->regmap, ADUX1020_REG_INT_ENABLE,
			   ADUX1020_INT_ENABLE);
	अगर (ret < 0)
		जाओ fail;

	ret = regmap_ग_लिखो(data->regmap, ADUX1020_REG_INT_POLARITY, 0);
	अगर (ret < 0)
		जाओ fail;

	चयन (chan->type) अणु
	हाल IIO_PROXIMITY:
		अगर (dir == IIO_EV_सूची_RISING)
			mask = ADUX1020_PROX_ON1_INT;
		अन्यथा
			mask = ADUX1020_PROX_OFF1_INT;

		अगर (state)
			state = 0;
		अन्यथा
			state = mask;

		ret = regmap_update_bits(data->regmap, ADUX1020_REG_INT_MASK,
					 mask, state);
		अगर (ret < 0)
			जाओ fail;

		/*
		 * Trigger proximity पूर्णांकerrupt when the पूर्णांकensity is above
		 * or below threshold
		 */
		ret = regmap_update_bits(data->regmap, ADUX1020_REG_PROX_TYPE,
					 ADUX1020_PROX_TYPE,
					 ADUX1020_PROX_TYPE);
		अगर (ret < 0)
			जाओ fail;

		/* Set proximity mode */
		ret = adux1020_set_mode(data, ADUX1020_MODE_PROX_I);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

fail:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक adux1020_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				      स्थिर काष्ठा iio_chan_spec *chan,
				      क्रमागत iio_event_type type,
				      क्रमागत iio_event_direction dir)
अणु
	काष्ठा adux1020_data *data = iio_priv(indio_dev);
	पूर्णांक ret, mask;
	अचिन्हित पूर्णांक regval;

	चयन (chan->type) अणु
	हाल IIO_PROXIMITY:
		अगर (dir == IIO_EV_सूची_RISING)
			mask = ADUX1020_PROX_ON1_INT;
		अन्यथा
			mask = ADUX1020_PROX_OFF1_INT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = regmap_पढ़ो(data->regmap, ADUX1020_REG_INT_MASK, &regval);
	अगर (ret < 0)
		वापस ret;

	वापस !(regval & mask);
पूर्ण

अटल पूर्णांक adux1020_पढ़ो_thresh(काष्ठा iio_dev *indio_dev,
				स्थिर काष्ठा iio_chan_spec *chan,
				क्रमागत iio_event_type type,
				क्रमागत iio_event_direction dir,
				क्रमागत iio_event_info info, पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा adux1020_data *data = iio_priv(indio_dev);
	u8 reg;
	पूर्णांक ret;
	अचिन्हित पूर्णांक regval;

	चयन (chan->type) अणु
	हाल IIO_PROXIMITY:
		अगर (dir == IIO_EV_सूची_RISING)
			reg = ADUX1020_REG_PROX_TH_ON1;
		अन्यथा
			reg = ADUX1020_REG_PROX_TH_OFF1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = regmap_पढ़ो(data->regmap, reg, &regval);
	अगर (ret < 0)
		वापस ret;

	*val = regval;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक adux1020_ग_लिखो_thresh(काष्ठा iio_dev *indio_dev,
				 स्थिर काष्ठा iio_chan_spec *chan,
				 क्रमागत iio_event_type type,
				 क्रमागत iio_event_direction dir,
				 क्रमागत iio_event_info info, पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा adux1020_data *data = iio_priv(indio_dev);
	u8 reg;

	चयन (chan->type) अणु
	हाल IIO_PROXIMITY:
		अगर (dir == IIO_EV_सूची_RISING)
			reg = ADUX1020_REG_PROX_TH_ON1;
		अन्यथा
			reg = ADUX1020_REG_PROX_TH_OFF1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Full scale threshold value is 0-65535  */
	अगर (val < 0 || val > 65535)
		वापस -EINVAL;

	वापस regmap_ग_लिखो(data->regmap, reg, val);
पूर्ण

अटल स्थिर काष्ठा iio_event_spec adux1020_proximity_event[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec adux1020_channels[] = अणु
	अणु
		.type = IIO_PROXIMITY,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.event_spec = adux1020_proximity_event,
		.num_event_specs = ARRAY_SIZE(adux1020_proximity_event),
	पूर्ण,
	अणु
		.type = IIO_CURRENT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.extend_name = "led",
		.output = 1,
	पूर्ण,
पूर्ण;

अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL(
		      "0.1 0.2 0.5 1 2 5 10 20 50 100 190 450 820 1400");

अटल काष्ठा attribute *adux1020_attributes[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adux1020_attribute_group = अणु
	.attrs = adux1020_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info adux1020_info = अणु
	.attrs = &adux1020_attribute_group,
	.पढ़ो_raw = adux1020_पढ़ो_raw,
	.ग_लिखो_raw = adux1020_ग_लिखो_raw,
	.पढ़ो_event_config = adux1020_पढ़ो_event_config,
	.ग_लिखो_event_config = adux1020_ग_लिखो_event_config,
	.पढ़ो_event_value = adux1020_पढ़ो_thresh,
	.ग_लिखो_event_value = adux1020_ग_लिखो_thresh,
पूर्ण;

अटल irqवापस_t adux1020_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा adux1020_data *data = iio_priv(indio_dev);
	पूर्णांक ret, status;

	ret = regmap_पढ़ो(data->regmap, ADUX1020_REG_INT_STATUS, &status);
	अगर (ret < 0)
		वापस IRQ_HANDLED;

	status &= ADUX1020_MODE_INT_STATUS_MASK;

	अगर (status & ADUX1020_INT_PROX_ON1) अणु
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_PROXIMITY, 0,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_सूची_RISING),
			       iio_get_समय_ns(indio_dev));
	पूर्ण

	अगर (status & ADUX1020_INT_PROX_OFF1) अणु
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_PROXIMITY, 0,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_सूची_FALLING),
			       iio_get_समय_ns(indio_dev));
	पूर्ण

	regmap_update_bits(data->regmap, ADUX1020_REG_INT_STATUS,
			   ADUX1020_MODE_INT_MASK, ADUX1020_INT_CLEAR);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक adux1020_chip_init(काष्ठा adux1020_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(data->regmap, ADUX1020_REG_CHIP_ID, &val);
	अगर (ret < 0)
		वापस ret;

	अगर ((val & ADUX1020_CHIP_ID_MASK) != ADUX1020_CHIP_ID) अणु
		dev_err(&client->dev, "invalid chip id 0x%04x\n", val);
		वापस -ENODEV;
	पूर्ण

	dev_dbg(&client->dev, "Detected ADUX1020 with chip id: 0x%04x\n", val);

	ret = regmap_update_bits(data->regmap, ADUX1020_REG_SW_RESET,
				 ADUX1020_SW_RESET, ADUX1020_SW_RESET);
	अगर (ret < 0)
		वापस ret;

	/* Load शेष configuration */
	ret = regmap_multi_reg_ग_लिखो(data->regmap, adux1020_def_conf,
				     ARRAY_SIZE(adux1020_def_conf));
	अगर (ret < 0)
		वापस ret;

	ret = adux1020_flush_fअगरo(data);
	अगर (ret < 0)
		वापस ret;

	/* Use LED_IREF क्रम proximity mode */
	ret = regmap_update_bits(data->regmap, ADUX1020_REG_LED_CURRENT,
				 ADUX1020_LED_PIREF_EN, 0);
	अगर (ret < 0)
		वापस ret;

	/* Mask all पूर्णांकerrupts */
	वापस regmap_update_bits(data->regmap, ADUX1020_REG_INT_MASK,
			   ADUX1020_MODE_INT_MASK, ADUX1020_MODE_INT_DISABLE);
पूर्ण

अटल पूर्णांक adux1020_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा adux1020_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	indio_dev->info = &adux1020_info;
	indio_dev->name = ADUX1020_DRV_NAME;
	indio_dev->channels = adux1020_channels;
	indio_dev->num_channels = ARRAY_SIZE(adux1020_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	data = iio_priv(indio_dev);

	data->regmap = devm_regmap_init_i2c(client, &adux1020_regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		dev_err(&client->dev, "regmap initialization failed.\n");
		वापस PTR_ERR(data->regmap);
	पूर्ण

	data->client = client;
	data->indio_dev = indio_dev;
	mutex_init(&data->lock);

	ret = adux1020_chip_init(data);
	अगर (ret)
		वापस ret;

	अगर (client->irq) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					शून्य, adux1020_पूर्णांकerrupt_handler,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					ADUX1020_DRV_NAME, indio_dev);
		अगर (ret) अणु
			dev_err(&client->dev, "irq request error %d\n", -ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adux1020_id[] = अणु
	अणु "adux1020", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adux1020_id);

अटल स्थिर काष्ठा of_device_id adux1020_of_match[] = अणु
	अणु .compatible = "adi,adux1020" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adux1020_of_match);

अटल काष्ठा i2c_driver adux1020_driver = अणु
	.driver = अणु
		.name	= ADUX1020_DRV_NAME,
		.of_match_table = adux1020_of_match,
	पूर्ण,
	.probe		= adux1020_probe,
	.id_table	= adux1020_id,
पूर्ण;
module_i2c_driver(adux1020_driver);

MODULE_AUTHOR("Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>");
MODULE_DESCRIPTION("ADUX1020 photometric sensor");
MODULE_LICENSE("GPL");
