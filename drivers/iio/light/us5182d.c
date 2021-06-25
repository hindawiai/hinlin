<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 Intel Corporation
 *
 * Driver क्रम UPISEMI us5182d Proximity and Ambient Light Sensor.
 *
 * To करो: Interrupt support.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा US5182D_REG_CFG0				0x00
#घोषणा US5182D_CFG0_ONESHOT_EN				BIT(6)
#घोषणा US5182D_CFG0_SHUTDOWN_EN			BIT(7)
#घोषणा US5182D_CFG0_WORD_ENABLE			BIT(0)
#घोषणा US5182D_CFG0_PROX				BIT(3)
#घोषणा US5182D_CFG0_PX_IRQ				BIT(2)

#घोषणा US5182D_REG_CFG1				0x01
#घोषणा US5182D_CFG1_ALS_RES16				BIT(4)
#घोषणा US5182D_CFG1_AGAIN_DEFAULT			0x00

#घोषणा US5182D_REG_CFG2				0x02
#घोषणा US5182D_CFG2_PX_RES16				BIT(4)
#घोषणा US5182D_CFG2_PXGAIN_DEFAULT			BIT(2)

#घोषणा US5182D_REG_CFG3				0x03
#घोषणा US5182D_CFG3_LED_CURRENT100			(BIT(4) | BIT(5))
#घोषणा US5182D_CFG3_INT_SOURCE_PX			BIT(3)

#घोषणा US5182D_REG_CFG4				0x10

/*
 * Registers क्रम tuning the स्वतः dark current cancelling feature.
 * DARK_TH(reg 0x27,0x28) - threshold (counts) क्रम स्वतः dark cancelling.
 * when ALS  > DARK_TH --> ALS_Code = ALS - Upper(0x2A) * Dark
 * when ALS < DARK_TH --> ALS_Code = ALS - Lower(0x29) * Dark
 */
#घोषणा US5182D_REG_UDARK_TH			0x27
#घोषणा US5182D_REG_DARK_AUTO_EN		0x2b
#घोषणा US5182D_REG_AUTO_LDARK_GAIN		0x29
#घोषणा US5182D_REG_AUTO_HDARK_GAIN		0x2a

/* Thresholds क्रम events: px low (0x08-l, 0x09-h), px high (0x0a-l 0x0b-h) */
#घोषणा US5182D_REG_PXL_TH			0x08
#घोषणा US5182D_REG_PXH_TH			0x0a

#घोषणा US5182D_REG_PXL_TH_DEFAULT		1000
#घोषणा US5182D_REG_PXH_TH_DEFAULT		30000

#घोषणा US5182D_OPMODE_ALS			0x01
#घोषणा US5182D_OPMODE_PX			0x02
#घोषणा US5182D_OPMODE_SHIFT			4

#घोषणा US5182D_REG_DARK_AUTO_EN_DEFAULT	0x80
#घोषणा US5182D_REG_AUTO_LDARK_GAIN_DEFAULT	0x16
#घोषणा US5182D_REG_AUTO_HDARK_GAIN_DEFAULT	0x00

#घोषणा US5182D_REG_ADL				0x0c
#घोषणा US5182D_REG_PDL				0x0e

#घोषणा US5182D_REG_MODE_STORE			0x21
#घोषणा US5182D_STORE_MODE			0x01

#घोषणा US5182D_REG_CHIPID			0xb2

#घोषणा US5182D_OPMODE_MASK			GENMASK(5, 4)
#घोषणा US5182D_AGAIN_MASK			0x07
#घोषणा US5182D_RESET_CHIP			0x01

#घोषणा US5182D_CHIPID				0x26
#घोषणा US5182D_DRV_NAME			"us5182d"

#घोषणा US5182D_GA_RESOLUTION			1000

#घोषणा US5182D_READ_BYTE			1
#घोषणा US5182D_READ_WORD			2
#घोषणा US5182D_OPSTORE_SLEEP_TIME		20 /* ms */
#घोषणा US5182D_SLEEP_MS			3000 /* ms */
#घोषणा US5182D_PXH_TH_DISABLE			0xffff
#घोषणा US5182D_PXL_TH_DISABLE			0x0000

/* Available ranges: [12354, 7065, 3998, 2202, 1285, 498, 256, 138] lux */
अटल स्थिर पूर्णांक us5182d_scales[] = अणु188500, 107800, 61000, 33600, 19600, 7600,
				     3900, 2100पूर्ण;

/*
 * Experimental thresholds that work with US5182D sensor on evaluation board
 * roughly between 12-32 lux
 */
अटल u16 us5182d_dark_ths_vals[] = अणु170, 200, 512, 512, 800, 2000, 4000,
				      8000पूर्ण;

क्रमागत mode अणु
	US5182D_ALS_PX,
	US5182D_ALS_ONLY,
	US5182D_PX_ONLY
पूर्ण;

क्रमागत pmode अणु
	US5182D_CONTINUOUS,
	US5182D_ONESHOT
पूर्ण;

काष्ठा us5182d_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;

	/* Glass attenuation factor */
	u32 ga;

	/* Dark gain tuning */
	u8 lower_dark_gain;
	u8 upper_dark_gain;
	u16 *us5182d_dark_ths;

	u16 px_low_th;
	u16 px_high_th;

	पूर्णांक rising_en;
	पूर्णांक falling_en;

	u8 opmode;
	u8 घातer_mode;

	bool als_enabled;
	bool px_enabled;

	bool शेष_continuous;
पूर्ण;

अटल IIO_CONST_ATTR(in_illuminance_scale_available,
		      "0.0021 0.0039 0.0076 0.0196 0.0336 0.061 0.1078 0.1885");

अटल काष्ठा attribute *us5182d_attrs[] = अणु
	&iio_स्थिर_attr_in_illuminance_scale_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group us5182d_attr_group = अणु
	.attrs = us5182d_attrs,
पूर्ण;

अटल स्थिर काष्ठा अणु
	u8 reg;
	u8 val;
पूर्ण us5182d_regvals[] = अणु
	अणुUS5182D_REG_CFG0, US5182D_CFG0_WORD_ENABLEपूर्ण,
	अणुUS5182D_REG_CFG1, US5182D_CFG1_ALS_RES16पूर्ण,
	अणुUS5182D_REG_CFG2, (US5182D_CFG2_PX_RES16 |
			    US5182D_CFG2_PXGAIN_DEFAULT)पूर्ण,
	अणुUS5182D_REG_CFG3, US5182D_CFG3_LED_CURRENT100 |
			   US5182D_CFG3_INT_SOURCE_PXपूर्ण,
	अणुUS5182D_REG_CFG4, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec us5182d_events[] = अणु
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

अटल स्थिर काष्ठा iio_chan_spec us5182d_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
	अणु
		.type = IIO_PROXIMITY,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.event_spec = us5182d_events,
		.num_event_specs = ARRAY_SIZE(us5182d_events),
	पूर्ण
पूर्ण;

अटल पूर्णांक us5182d_oneshot_en(काष्ठा us5182d_data *data)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, US5182D_REG_CFG0);
	अगर (ret < 0)
		वापस ret;

	/*
	 * In oneshot mode the chip will घातer itself करोwn after taking the
	 * required measurement.
	 */
	ret = ret | US5182D_CFG0_ONESHOT_EN;

	वापस i2c_smbus_ग_लिखो_byte_data(data->client, US5182D_REG_CFG0, ret);
पूर्ण

अटल पूर्णांक us5182d_set_opmode(काष्ठा us5182d_data *data, u8 mode)
अणु
	पूर्णांक ret;

	अगर (mode == data->opmode)
		वापस 0;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, US5182D_REG_CFG0);
	अगर (ret < 0)
		वापस ret;

	/* update mode */
	ret = ret & ~US5182D_OPMODE_MASK;
	ret = ret | (mode << US5182D_OPMODE_SHIFT);

	/*
	 * After updating the operating mode, the chip requires that
	 * the operation is stored, by writing 1 in the STORE_MODE
	 * रेजिस्टर (स्वतः-clearing).
	 */
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, US5182D_REG_CFG0, ret);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, US5182D_REG_MODE_STORE,
					US5182D_STORE_MODE);
	अगर (ret < 0)
		वापस ret;

	data->opmode = mode;
	msleep(US5182D_OPSTORE_SLEEP_TIME);

	वापस 0;
पूर्ण

अटल पूर्णांक us5182d_als_enable(काष्ठा us5182d_data *data)
अणु
	पूर्णांक ret;
	u8 mode;

	अगर (data->घातer_mode == US5182D_ONESHOT) अणु
		ret = us5182d_set_opmode(data, US5182D_ALS_ONLY);
		अगर (ret < 0)
			वापस ret;
		data->px_enabled = false;
	पूर्ण

	अगर (data->als_enabled)
		वापस 0;

	mode = data->px_enabled ? US5182D_ALS_PX : US5182D_ALS_ONLY;

	ret = us5182d_set_opmode(data, mode);
	अगर (ret < 0)
		वापस ret;

	data->als_enabled = true;

	वापस 0;
पूर्ण

अटल पूर्णांक us5182d_px_enable(काष्ठा us5182d_data *data)
अणु
	पूर्णांक ret;
	u8 mode;

	अगर (data->घातer_mode == US5182D_ONESHOT) अणु
		ret = us5182d_set_opmode(data, US5182D_PX_ONLY);
		अगर (ret < 0)
			वापस ret;
		data->als_enabled = false;
	पूर्ण

	अगर (data->px_enabled)
		वापस 0;

	mode = data->als_enabled ? US5182D_ALS_PX : US5182D_PX_ONLY;

	ret = us5182d_set_opmode(data, mode);
	अगर (ret < 0)
		वापस ret;

	data->px_enabled = true;

	वापस 0;
पूर्ण

अटल पूर्णांक us5182d_get_als(काष्ठा us5182d_data *data)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ result;

	ret = us5182d_als_enable(data);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_पढ़ो_word_data(data->client,
				       US5182D_REG_ADL);
	अगर (ret < 0)
		वापस ret;

	result = ret * data->ga / US5182D_GA_RESOLUTION;
	अगर (result > 0xffff)
		result = 0xffff;

	वापस result;
पूर्ण

अटल पूर्णांक us5182d_get_px(काष्ठा us5182d_data *data)
अणु
	पूर्णांक ret;

	ret = us5182d_px_enable(data);
	अगर (ret < 0)
		वापस ret;

	वापस i2c_smbus_पढ़ो_word_data(data->client,
					US5182D_REG_PDL);
पूर्ण

अटल पूर्णांक us5182d_shutकरोwn_en(काष्ठा us5182d_data *data, u8 state)
अणु
	पूर्णांक ret;

	अगर (data->घातer_mode == US5182D_ONESHOT)
		वापस 0;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, US5182D_REG_CFG0);
	अगर (ret < 0)
		वापस ret;

	ret = ret & ~US5182D_CFG0_SHUTDOWN_EN;
	ret = ret | state;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, US5182D_REG_CFG0, ret);
	अगर (ret < 0)
		वापस ret;

	अगर (state & US5182D_CFG0_SHUTDOWN_EN) अणु
		data->als_enabled = false;
		data->px_enabled = false;
	पूर्ण

	वापस ret;
पूर्ण


अटल पूर्णांक us5182d_set_घातer_state(काष्ठा us5182d_data *data, bool on)
अणु
	पूर्णांक ret;

	अगर (data->घातer_mode == US5182D_ONESHOT)
		वापस 0;

	अगर (on) अणु
		ret = pm_runसमय_get_sync(&data->client->dev);
		अगर (ret < 0)
			pm_runसमय_put_noidle(&data->client->dev);
	पूर्ण अन्यथा अणु
		pm_runसमय_mark_last_busy(&data->client->dev);
		ret = pm_runसमय_put_स्वतःsuspend(&data->client->dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक us5182d_पढ़ो_value(काष्ठा us5182d_data *data,
			      काष्ठा iio_chan_spec स्थिर *chan)
अणु
	पूर्णांक ret, value;

	mutex_lock(&data->lock);

	अगर (data->घातer_mode == US5182D_ONESHOT) अणु
		ret = us5182d_oneshot_en(data);
		अगर (ret < 0)
			जाओ out_err;
	पूर्ण

	ret = us5182d_set_घातer_state(data, true);
	अगर (ret < 0)
		जाओ out_err;

	अगर (chan->type == IIO_LIGHT)
		ret = us5182d_get_als(data);
	अन्यथा
		ret = us5182d_get_px(data);
	अगर (ret < 0)
		जाओ out_घातeroff;

	value = ret;

	ret = us5182d_set_घातer_state(data, false);
	अगर (ret < 0)
		जाओ out_err;

	mutex_unlock(&data->lock);
	वापस value;

out_घातeroff:
	us5182d_set_घातer_state(data, false);
out_err:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक us5182d_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			    पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा us5182d_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = us5182d_पढ़ो_value(data, chan);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		ret = i2c_smbus_पढ़ो_byte_data(data->client, US5182D_REG_CFG1);
		अगर (ret < 0)
			वापस ret;
		*val = 0;
		*val2 = us5182d_scales[ret & US5182D_AGAIN_MASK];
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * us5182d_update_dark_th - update Darh_Th रेजिस्टरs
 * @data:	us5182d_data काष्ठाure
 * @index:	index in us5182d_dark_ths array to use क्रम the updated value
 *
 * Function needs to be called with a lock held because it needs two i2c ग_लिखो
 * byte operations as these रेजिस्टरs (0x27 0x28) करोn't work in word mode
 * accessing.
 */
अटल पूर्णांक us5182d_update_dark_th(काष्ठा us5182d_data *data, पूर्णांक index)
अणु
	__be16 dark_th = cpu_to_be16(data->us5182d_dark_ths[index]);
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, US5182D_REG_UDARK_TH,
					((u8 *)&dark_th)[0]);
	अगर (ret < 0)
		वापस ret;

	वापस i2c_smbus_ग_लिखो_byte_data(data->client, US5182D_REG_UDARK_TH + 1,
					((u8 *)&dark_th)[1]);
पूर्ण

/**
 * us5182d_apply_scale - update the ALS scale
 * @data:	us5182d_data काष्ठाure
 * @index:	index in us5182d_scales array to use क्रम the updated value
 *
 * Function needs to be called with a lock held as we're having more than one
 * i2c operation.
 */
अटल पूर्णांक us5182d_apply_scale(काष्ठा us5182d_data *data, पूर्णांक index)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, US5182D_REG_CFG1);
	अगर (ret < 0)
		वापस ret;

	ret = ret & (~US5182D_AGAIN_MASK);
	ret |= index;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, US5182D_REG_CFG1, ret);
	अगर (ret < 0)
		वापस ret;

	वापस us5182d_update_dark_th(data, index);
पूर्ण

अटल पूर्णांक us5182d_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val,
			     पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा us5182d_data *data = iio_priv(indio_dev);
	पूर्णांक ret, i;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		अगर (val != 0)
			वापस -EINVAL;
		क्रम (i = 0; i < ARRAY_SIZE(us5182d_scales); i++)
			अगर (val2 == us5182d_scales[i]) अणु
				mutex_lock(&data->lock);
				ret = us5182d_apply_scale(data, i);
				mutex_unlock(&data->lock);
				वापस ret;
			पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक us5182d_setup_prox(काष्ठा iio_dev *indio_dev,
			      क्रमागत iio_event_direction dir, u16 val)
अणु
	काष्ठा us5182d_data *data = iio_priv(indio_dev);

	अगर (dir == IIO_EV_सूची_FALLING)
		वापस i2c_smbus_ग_लिखो_word_data(data->client,
						 US5182D_REG_PXL_TH, val);
	अन्यथा अगर (dir == IIO_EV_सूची_RISING)
		वापस i2c_smbus_ग_लिखो_word_data(data->client,
						 US5182D_REG_PXH_TH, val);

	वापस 0;
पूर्ण

अटल पूर्णांक us5182d_पढ़ो_thresh(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, क्रमागत iio_event_info info, पूर्णांक *val,
	पूर्णांक *val2)
अणु
	काष्ठा us5182d_data *data = iio_priv(indio_dev);

	चयन (dir) अणु
	हाल IIO_EV_सूची_RISING:
		mutex_lock(&data->lock);
		*val = data->px_high_th;
		mutex_unlock(&data->lock);
		अवरोध;
	हाल IIO_EV_सूची_FALLING:
		mutex_lock(&data->lock);
		*val = data->px_low_th;
		mutex_unlock(&data->lock);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक us5182d_ग_लिखो_thresh(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, क्रमागत iio_event_info info, पूर्णांक val,
	पूर्णांक val2)
अणु
	काष्ठा us5182d_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (val < 0 || val > अच_लघु_उच्च || val2 != 0)
		वापस -EINVAL;

	चयन (dir) अणु
	हाल IIO_EV_सूची_RISING:
		mutex_lock(&data->lock);
		अगर (data->rising_en) अणु
			ret = us5182d_setup_prox(indio_dev, dir, val);
			अगर (ret < 0)
				जाओ err;
		पूर्ण
		data->px_high_th = val;
		mutex_unlock(&data->lock);
		अवरोध;
	हाल IIO_EV_सूची_FALLING:
		mutex_lock(&data->lock);
		अगर (data->falling_en) अणु
			ret = us5182d_setup_prox(indio_dev, dir, val);
			अगर (ret < 0)
				जाओ err;
		पूर्ण
		data->px_low_th = val;
		mutex_unlock(&data->lock);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
err:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक us5182d_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir)
अणु
	काष्ठा us5182d_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (dir) अणु
	हाल IIO_EV_सूची_RISING:
		mutex_lock(&data->lock);
		ret = data->rising_en;
		mutex_unlock(&data->lock);
		अवरोध;
	हाल IIO_EV_सूची_FALLING:
		mutex_lock(&data->lock);
		ret = data->falling_en;
		mutex_unlock(&data->lock);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक us5182d_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
	क्रमागत iio_event_direction dir, पूर्णांक state)
अणु
	काष्ठा us5182d_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	u16 new_th;

	mutex_lock(&data->lock);

	चयन (dir) अणु
	हाल IIO_EV_सूची_RISING:
		अगर (data->rising_en == state) अणु
			mutex_unlock(&data->lock);
			वापस 0;
		पूर्ण
		new_th = US5182D_PXH_TH_DISABLE;
		अगर (state) अणु
			data->घातer_mode = US5182D_CONTINUOUS;
			ret = us5182d_set_घातer_state(data, true);
			अगर (ret < 0)
				जाओ err;
			ret = us5182d_px_enable(data);
			अगर (ret < 0)
				जाओ err_घातeroff;
			new_th = data->px_high_th;
		पूर्ण
		ret = us5182d_setup_prox(indio_dev, dir, new_th);
		अगर (ret < 0)
			जाओ err_घातeroff;
		data->rising_en = state;
		अवरोध;
	हाल IIO_EV_सूची_FALLING:
		अगर (data->falling_en == state) अणु
			mutex_unlock(&data->lock);
			वापस 0;
		पूर्ण
		new_th =  US5182D_PXL_TH_DISABLE;
		अगर (state) अणु
			data->घातer_mode = US5182D_CONTINUOUS;
			ret = us5182d_set_घातer_state(data, true);
			अगर (ret < 0)
				जाओ err;
			ret = us5182d_px_enable(data);
			अगर (ret < 0)
				जाओ err_घातeroff;
			new_th = data->px_low_th;
		पूर्ण
		ret = us5182d_setup_prox(indio_dev, dir, new_th);
		अगर (ret < 0)
			जाओ err_घातeroff;
		data->falling_en = state;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (!state) अणु
		ret = us5182d_set_घातer_state(data, false);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	अगर (!data->falling_en && !data->rising_en && !data->शेष_continuous)
		data->घातer_mode = US5182D_ONESHOT;

	mutex_unlock(&data->lock);
	वापस 0;

err_घातeroff:
	अगर (state)
		us5182d_set_घातer_state(data, false);
err:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info us5182d_info = अणु
	.पढ़ो_raw = us5182d_पढ़ो_raw,
	.ग_लिखो_raw = us5182d_ग_लिखो_raw,
	.attrs = &us5182d_attr_group,
	.पढ़ो_event_value = &us5182d_पढ़ो_thresh,
	.ग_लिखो_event_value = &us5182d_ग_लिखो_thresh,
	.पढ़ो_event_config = &us5182d_पढ़ो_event_config,
	.ग_लिखो_event_config = &us5182d_ग_लिखो_event_config,
पूर्ण;

अटल पूर्णांक us5182d_reset(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा us5182d_data *data = iio_priv(indio_dev);

	वापस i2c_smbus_ग_लिखो_byte_data(data->client, US5182D_REG_CFG3,
					 US5182D_RESET_CHIP);
पूर्ण

अटल पूर्णांक us5182d_init(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा us5182d_data *data = iio_priv(indio_dev);
	पूर्णांक i, ret;

	ret = us5182d_reset(indio_dev);
	अगर (ret < 0)
		वापस ret;

	data->opmode = 0;
	data->घातer_mode = US5182D_CONTINUOUS;
	data->px_low_th = US5182D_REG_PXL_TH_DEFAULT;
	data->px_high_th = US5182D_REG_PXH_TH_DEFAULT;

	क्रम (i = 0; i < ARRAY_SIZE(us5182d_regvals); i++) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(data->client,
						us5182d_regvals[i].reg,
						us5182d_regvals[i].val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	data->als_enabled = true;
	data->px_enabled = true;

	अगर (!data->शेष_continuous) अणु
		ret = us5182d_shutकरोwn_en(data, US5182D_CFG0_SHUTDOWN_EN);
		अगर (ret < 0)
			वापस ret;
		data->घातer_mode = US5182D_ONESHOT;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम us5182d_get_platक्रमm_data(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा us5182d_data *data = iio_priv(indio_dev);

	अगर (device_property_पढ़ो_u32(&data->client->dev, "upisemi,glass-coef",
				     &data->ga))
		data->ga = US5182D_GA_RESOLUTION;
	अगर (device_property_पढ़ो_u16_array(&data->client->dev,
					   "upisemi,dark-ths",
					   data->us5182d_dark_ths,
					   ARRAY_SIZE(us5182d_dark_ths_vals)))
		data->us5182d_dark_ths = us5182d_dark_ths_vals;
	अगर (device_property_पढ़ो_u8(&data->client->dev,
				    "upisemi,upper-dark-gain",
				    &data->upper_dark_gain))
		data->upper_dark_gain = US5182D_REG_AUTO_HDARK_GAIN_DEFAULT;
	अगर (device_property_पढ़ो_u8(&data->client->dev,
				    "upisemi,lower-dark-gain",
				    &data->lower_dark_gain))
		data->lower_dark_gain = US5182D_REG_AUTO_LDARK_GAIN_DEFAULT;
	data->शेष_continuous = device_property_पढ़ो_bool(&data->client->dev,
							     "upisemi,continuous");
पूर्ण

अटल पूर्णांक  us5182d_dark_gain_config(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा us5182d_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = us5182d_update_dark_th(data, US5182D_CFG1_AGAIN_DEFAULT);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
					US5182D_REG_AUTO_LDARK_GAIN,
					data->lower_dark_gain);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
					US5182D_REG_AUTO_HDARK_GAIN,
					data->upper_dark_gain);
	अगर (ret < 0)
		वापस ret;

	वापस i2c_smbus_ग_लिखो_byte_data(data->client, US5182D_REG_DARK_AUTO_EN,
					 US5182D_REG_DARK_AUTO_EN_DEFAULT);
पूर्ण

अटल irqवापस_t us5182d_irq_thपढ़ो_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा us5182d_data *data = iio_priv(indio_dev);
	क्रमागत iio_event_direction dir;
	पूर्णांक ret;
	u64 ev;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, US5182D_REG_CFG0);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "i2c transfer error in irq\n");
		वापस IRQ_HANDLED;
	पूर्ण

	dir = ret & US5182D_CFG0_PROX ? IIO_EV_सूची_RISING : IIO_EV_सूची_FALLING;
	ev = IIO_UNMOD_EVENT_CODE(IIO_PROXIMITY, 1, IIO_EV_TYPE_THRESH, dir);

	iio_push_event(indio_dev, ev, iio_get_समय_ns(indio_dev));

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, US5182D_REG_CFG0,
					ret & ~US5182D_CFG0_PX_IRQ);
	अगर (ret < 0)
		dev_err(&data->client->dev, "i2c transfer error in irq\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक us5182d_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा us5182d_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	mutex_init(&data->lock);

	indio_dev->info = &us5182d_info;
	indio_dev->name = US5182D_DRV_NAME;
	indio_dev->channels = us5182d_channels;
	indio_dev->num_channels = ARRAY_SIZE(us5182d_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, US5182D_REG_CHIPID);
	अगर (ret != US5182D_CHIPID) अणु
		dev_err(&data->client->dev,
			"Failed to detect US5182 light chip\n");
		वापस (ret < 0) ? ret : -ENODEV;
	पूर्ण

	अगर (client->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq, शून्य,
						us5182d_irq_thपढ़ो_handler,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						"us5182d-irq", indio_dev);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा
		dev_warn(&client->dev, "no valid irq found\n");

	us5182d_get_platक्रमm_data(indio_dev);
	ret = us5182d_init(indio_dev);
	अगर (ret < 0)
		वापस ret;

	ret = us5182d_dark_gain_config(indio_dev);
	अगर (ret < 0)
		जाओ out_err;

	अगर (data->शेष_continuous) अणु
		ret = pm_runसमय_set_active(&client->dev);
		अगर (ret < 0)
			जाओ out_err;
	पूर्ण

	pm_runसमय_enable(&client->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&client->dev,
					 US5182D_SLEEP_MS);
	pm_runसमय_use_स्वतःsuspend(&client->dev);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ out_err;

	वापस 0;

out_err:
	us5182d_shutकरोwn_en(data, US5182D_CFG0_SHUTDOWN_EN);
	वापस ret;

पूर्ण

अटल पूर्णांक us5182d_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा us5182d_data *data = iio_priv(i2c_get_clientdata(client));

	iio_device_unरेजिस्टर(i2c_get_clientdata(client));

	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);

	वापस us5182d_shutकरोwn_en(data, US5182D_CFG0_SHUTDOWN_EN);
पूर्ण

#अगर defined(CONFIG_PM_SLEEP) || defined(CONFIG_PM)
अटल पूर्णांक us5182d_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा us5182d_data *data = iio_priv(indio_dev);

	अगर (data->घातer_mode == US5182D_CONTINUOUS)
		वापस us5182d_shutकरोwn_en(data, US5182D_CFG0_SHUTDOWN_EN);

	वापस 0;
पूर्ण

अटल पूर्णांक us5182d_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा us5182d_data *data = iio_priv(indio_dev);

	अगर (data->घातer_mode == US5182D_CONTINUOUS)
		वापस us5182d_shutकरोwn_en(data,
					   ~US5182D_CFG0_SHUTDOWN_EN & 0xff);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops us5182d_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(us5182d_suspend, us5182d_resume)
	SET_RUNTIME_PM_OPS(us5182d_suspend, us5182d_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id us5182d_acpi_match[] = अणु
	अणु "USD5182", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, us5182d_acpi_match);

अटल स्थिर काष्ठा i2c_device_id us5182d_id[] = अणु
		अणु"usd5182", 0पूर्ण,
		अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, us5182d_id);

अटल स्थिर काष्ठा of_device_id us5182d_of_match[] = अणु
	अणु .compatible = "upisemi,usd5182" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, us5182d_of_match);

अटल काष्ठा i2c_driver us5182d_driver = अणु
	.driver = अणु
		.name = US5182D_DRV_NAME,
		.pm = &us5182d_pm_ops,
		.of_match_table = us5182d_of_match,
		.acpi_match_table = ACPI_PTR(us5182d_acpi_match),
	पूर्ण,
	.probe = us5182d_probe,
	.हटाओ = us5182d_हटाओ,
	.id_table = us5182d_id,

पूर्ण;
module_i2c_driver(us5182d_driver);

MODULE_AUTHOR("Adriana Reus <adriana.reus@intel.com>");
MODULE_DESCRIPTION("Driver for us5182d Proximity and Light Sensor");
MODULE_LICENSE("GPL v2");
