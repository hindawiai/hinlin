<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * RPR-0521 ROHM Ambient Light and Proximity Sensor
 *
 * Copyright (c) 2015, Intel Corporation.
 *
 * IIO driver क्रम RPR-0521RS (7-bit I2C slave address 0x38).
 *
 * TODO: illuminance channel
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/delay.h>
#समावेश <linux/acpi.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा RPR0521_REG_SYSTEM_CTRL		0x40
#घोषणा RPR0521_REG_MODE_CTRL		0x41
#घोषणा RPR0521_REG_ALS_CTRL		0x42
#घोषणा RPR0521_REG_PXS_CTRL		0x43
#घोषणा RPR0521_REG_PXS_DATA		0x44 /* 16-bit, little endian */
#घोषणा RPR0521_REG_ALS_DATA0		0x46 /* 16-bit, little endian */
#घोषणा RPR0521_REG_ALS_DATA1		0x48 /* 16-bit, little endian */
#घोषणा RPR0521_REG_INTERRUPT		0x4A
#घोषणा RPR0521_REG_PS_OFFSET_LSB	0x53
#घोषणा RPR0521_REG_ID			0x92

#घोषणा RPR0521_MODE_ALS_MASK		BIT(7)
#घोषणा RPR0521_MODE_PXS_MASK		BIT(6)
#घोषणा RPR0521_MODE_MEAS_TIME_MASK	GENMASK(3, 0)
#घोषणा RPR0521_ALS_DATA0_GAIN_MASK	GENMASK(5, 4)
#घोषणा RPR0521_ALS_DATA0_GAIN_SHIFT	4
#घोषणा RPR0521_ALS_DATA1_GAIN_MASK	GENMASK(3, 2)
#घोषणा RPR0521_ALS_DATA1_GAIN_SHIFT	2
#घोषणा RPR0521_PXS_GAIN_MASK		GENMASK(5, 4)
#घोषणा RPR0521_PXS_GAIN_SHIFT		4
#घोषणा RPR0521_PXS_PERSISTENCE_MASK	GENMASK(3, 0)
#घोषणा RPR0521_INTERRUPT_INT_TRIG_PS_MASK	BIT(0)
#घोषणा RPR0521_INTERRUPT_INT_TRIG_ALS_MASK	BIT(1)
#घोषणा RPR0521_INTERRUPT_INT_REASSERT_MASK	BIT(3)
#घोषणा RPR0521_INTERRUPT_ALS_INT_STATUS_MASK	BIT(6)
#घोषणा RPR0521_INTERRUPT_PS_INT_STATUS_MASK	BIT(7)

#घोषणा RPR0521_MODE_ALS_ENABLE		BIT(7)
#घोषणा RPR0521_MODE_ALS_DISABLE	0x00
#घोषणा RPR0521_MODE_PXS_ENABLE		BIT(6)
#घोषणा RPR0521_MODE_PXS_DISABLE	0x00
#घोषणा RPR0521_PXS_PERSISTENCE_DRDY	0x00

#घोषणा RPR0521_INTERRUPT_INT_TRIG_PS_ENABLE	BIT(0)
#घोषणा RPR0521_INTERRUPT_INT_TRIG_PS_DISABLE	0x00
#घोषणा RPR0521_INTERRUPT_INT_TRIG_ALS_ENABLE	BIT(1)
#घोषणा RPR0521_INTERRUPT_INT_TRIG_ALS_DISABLE	0x00
#घोषणा RPR0521_INTERRUPT_INT_REASSERT_ENABLE	BIT(3)
#घोषणा RPR0521_INTERRUPT_INT_REASSERT_DISABLE	0x00

#घोषणा RPR0521_MANUFACT_ID		0xE0
#घोषणा RPR0521_DEFAULT_MEAS_TIME	0x06 /* ALS - 100ms, PXS - 100ms */

#घोषणा RPR0521_DRV_NAME		"RPR0521"
#घोषणा RPR0521_IRQ_NAME		"rpr0521_event"
#घोषणा RPR0521_REGMAP_NAME		"rpr0521_regmap"

#घोषणा RPR0521_SLEEP_DELAY_MS	2000

#घोषणा RPR0521_ALS_SCALE_AVAIL "0.007812 0.015625 0.5 1"
#घोषणा RPR0521_PXS_SCALE_AVAIL "0.125 0.5 1"

काष्ठा rpr0521_gain अणु
	पूर्णांक scale;
	पूर्णांक uscale;
पूर्ण;

अटल स्थिर काष्ठा rpr0521_gain rpr0521_als_gain[4] = अणु
	अणु1, 0पूर्ण,		/* x1 */
	अणु0, 500000पूर्ण,	/* x2 */
	अणु0, 15625पूर्ण,	/* x64 */
	अणु0, 7812पूर्ण,	/* x128 */
पूर्ण;

अटल स्थिर काष्ठा rpr0521_gain rpr0521_pxs_gain[3] = अणु
	अणु1, 0पूर्ण,		/* x1 */
	अणु0, 500000पूर्ण,	/* x2 */
	अणु0, 125000पूर्ण,	/* x4 */
पूर्ण;

क्रमागत rpr0521_channel अणु
	RPR0521_CHAN_PXS,
	RPR0521_CHAN_ALS_DATA0,
	RPR0521_CHAN_ALS_DATA1,
पूर्ण;

काष्ठा rpr0521_reg_desc अणु
	u8 address;
	u8 device_mask;
पूर्ण;

अटल स्थिर काष्ठा rpr0521_reg_desc rpr0521_data_reg[] = अणु
	[RPR0521_CHAN_PXS]	= अणु
		.address	= RPR0521_REG_PXS_DATA,
		.device_mask	= RPR0521_MODE_PXS_MASK,
	पूर्ण,
	[RPR0521_CHAN_ALS_DATA0] = अणु
		.address	= RPR0521_REG_ALS_DATA0,
		.device_mask	= RPR0521_MODE_ALS_MASK,
	पूर्ण,
	[RPR0521_CHAN_ALS_DATA1] = अणु
		.address	= RPR0521_REG_ALS_DATA1,
		.device_mask	= RPR0521_MODE_ALS_MASK,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpr0521_gain_info अणु
	u8 reg;
	u8 mask;
	u8 shअगरt;
	स्थिर काष्ठा rpr0521_gain *gain;
	पूर्णांक size;
पूर्ण rpr0521_gain[] = अणु
	[RPR0521_CHAN_PXS] = अणु
		.reg	= RPR0521_REG_PXS_CTRL,
		.mask	= RPR0521_PXS_GAIN_MASK,
		.shअगरt	= RPR0521_PXS_GAIN_SHIFT,
		.gain	= rpr0521_pxs_gain,
		.size	= ARRAY_SIZE(rpr0521_pxs_gain),
	पूर्ण,
	[RPR0521_CHAN_ALS_DATA0] = अणु
		.reg	= RPR0521_REG_ALS_CTRL,
		.mask	= RPR0521_ALS_DATA0_GAIN_MASK,
		.shअगरt	= RPR0521_ALS_DATA0_GAIN_SHIFT,
		.gain	= rpr0521_als_gain,
		.size	= ARRAY_SIZE(rpr0521_als_gain),
	पूर्ण,
	[RPR0521_CHAN_ALS_DATA1] = अणु
		.reg	= RPR0521_REG_ALS_CTRL,
		.mask	= RPR0521_ALS_DATA1_GAIN_MASK,
		.shअगरt	= RPR0521_ALS_DATA1_GAIN_SHIFT,
		.gain	= rpr0521_als_gain,
		.size	= ARRAY_SIZE(rpr0521_als_gain),
	पूर्ण,
पूर्ण;

काष्ठा rpr0521_samp_freq अणु
	पूर्णांक	als_hz;
	पूर्णांक	als_uhz;
	पूर्णांक	pxs_hz;
	पूर्णांक	pxs_uhz;
पूर्ण;

अटल स्थिर काष्ठा rpr0521_samp_freq rpr0521_samp_freq_i[13] = अणु
/*	अणुALS, PXSपूर्ण,		   W==currently writable option */
	अणु0, 0, 0, 0पूर्ण,		/* W0000, 0=standby */
	अणु0, 0, 100, 0पूर्ण,		/*  0001 */
	अणु0, 0, 25, 0पूर्ण,		/*  0010 */
	अणु0, 0, 10, 0पूर्ण,		/*  0011 */
	अणु0, 0, 2, 500000पूर्ण,	/*  0100 */
	अणु10, 0, 20, 0पूर्ण,		/*  0101 */
	अणु10, 0, 10, 0पूर्ण,		/* W0110 */
	अणु10, 0, 2, 500000पूर्ण,	/*  0111 */
	अणु2, 500000, 20, 0पूर्ण,	/*  1000, measurement 100ms, sleep 300ms */
	अणु2, 500000, 10, 0पूर्ण,	/*  1001, measurement 100ms, sleep 300ms */
	अणु2, 500000, 0, 0पूर्ण,	/*  1010, high sensitivity mode */
	अणु2, 500000, 2, 500000पूर्ण,	/* W1011, high sensitivity mode */
	अणु20, 0, 20, 0पूर्ण	/* 1100, ALS_data x 0.5, see specअगरication P.18 */
पूर्ण;

काष्ठा rpr0521_data अणु
	काष्ठा i2c_client *client;

	/* protect device params updates (e.g state, gain) */
	काष्ठा mutex lock;

	/* device active status */
	bool als_dev_en;
	bool pxs_dev_en;

	काष्ठा iio_trigger *drdy_trigger0;
	s64 irq_बारtamp;

	/* optimize runसमय pm ops - enable/disable device only अगर needed */
	bool als_ps_need_en;
	bool pxs_ps_need_en;
	bool als_need_dis;
	bool pxs_need_dis;

	काष्ठा regmap *regmap;

	/*
	 * Ensure correct naturally aligned बारtamp.
	 * Note that the पढ़ो will put garbage data पूर्णांकo
	 * the padding but this should not be a problem
	 */
	काष्ठा अणु
		__le16 channels[3];
		u8 garbage;
		s64 ts __aligned(8);
	पूर्ण scan;
पूर्ण;

अटल IIO_CONST_ATTR(in_पूर्णांकensity_scale_available, RPR0521_ALS_SCALE_AVAIL);
अटल IIO_CONST_ATTR(in_proximity_scale_available, RPR0521_PXS_SCALE_AVAIL);

/*
 * Start with easy freq first, whole table of freq combinations is more
 * complicated.
 */
अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL("2.5 10");

अटल काष्ठा attribute *rpr0521_attributes[] = अणु
	&iio_स्थिर_attr_in_पूर्णांकensity_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_in_proximity_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group rpr0521_attribute_group = अणु
	.attrs = rpr0521_attributes,
पूर्ण;

/* Order of the channel data in buffer */
क्रमागत rpr0521_scan_index_order अणु
	RPR0521_CHAN_INDEX_PXS,
	RPR0521_CHAN_INDEX_BOTH,
	RPR0521_CHAN_INDEX_IR,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ rpr0521_available_scan_masks[] = अणु
	BIT(RPR0521_CHAN_INDEX_PXS) | BIT(RPR0521_CHAN_INDEX_BOTH) |
	BIT(RPR0521_CHAN_INDEX_IR),
	0
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec rpr0521_channels[] = अणु
	अणु
		.type = IIO_PROXIMITY,
		.address = RPR0521_CHAN_PXS,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_OFFSET) |
			BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.scan_index = RPR0521_CHAN_INDEX_PXS,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_LE,
		पूर्ण,
	पूर्ण,
	अणु
		.type = IIO_INTENSITY,
		.modअगरied = 1,
		.address = RPR0521_CHAN_ALS_DATA0,
		.channel2 = IIO_MOD_LIGHT_BOTH,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.scan_index = RPR0521_CHAN_INDEX_BOTH,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_LE,
		पूर्ण,
	पूर्ण,
	अणु
		.type = IIO_INTENSITY,
		.modअगरied = 1,
		.address = RPR0521_CHAN_ALS_DATA1,
		.channel2 = IIO_MOD_LIGHT_IR,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.scan_index = RPR0521_CHAN_INDEX_IR,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_LE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक rpr0521_als_enable(काष्ठा rpr0521_data *data, u8 status)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(data->regmap, RPR0521_REG_MODE_CTRL,
				 RPR0521_MODE_ALS_MASK,
				 status);
	अगर (ret < 0)
		वापस ret;

	अगर (status & RPR0521_MODE_ALS_MASK)
		data->als_dev_en = true;
	अन्यथा
		data->als_dev_en = false;

	वापस 0;
पूर्ण

अटल पूर्णांक rpr0521_pxs_enable(काष्ठा rpr0521_data *data, u8 status)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(data->regmap, RPR0521_REG_MODE_CTRL,
				 RPR0521_MODE_PXS_MASK,
				 status);
	अगर (ret < 0)
		वापस ret;

	अगर (status & RPR0521_MODE_PXS_MASK)
		data->pxs_dev_en = true;
	अन्यथा
		data->pxs_dev_en = false;

	वापस 0;
पूर्ण

/**
 * rpr0521_set_घातer_state - handles runसमय PM state and sensors enabled status
 *
 * @data: rpr0521 device निजी data
 * @on: state to be set क्रम devices in @device_mask
 * @device_mask: biपंचांगask specअगरying क्रम which device we need to update @on state
 *
 * Calls क्रम this function must be balanced so that each ON should have matching
 * OFF. Otherwise pm usage_count माला_लो out of sync.
 */
अटल पूर्णांक rpr0521_set_घातer_state(काष्ठा rpr0521_data *data, bool on,
				   u8 device_mask)
अणु
#अगर_घोषित CONFIG_PM
	पूर्णांक ret;

	अगर (device_mask & RPR0521_MODE_ALS_MASK) अणु
		data->als_ps_need_en = on;
		data->als_need_dis = !on;
	पूर्ण

	अगर (device_mask & RPR0521_MODE_PXS_MASK) अणु
		data->pxs_ps_need_en = on;
		data->pxs_need_dis = !on;
	पूर्ण

	/*
	 * On: _resume() is called only when we are suspended
	 * Off: _suspend() is called after delay अगर _resume() is not
	 * called beक्रमe that.
	 * Note: If either measurement is re-enabled beक्रमe _suspend(),
	 * both stay enabled until _suspend().
	 */
	अगर (on) अणु
		ret = pm_runसमय_get_sync(&data->client->dev);
	पूर्ण अन्यथा अणु
		pm_runसमय_mark_last_busy(&data->client->dev);
		ret = pm_runसमय_put_स्वतःsuspend(&data->client->dev);
	पूर्ण
	अगर (ret < 0) अणु
		dev_err(&data->client->dev,
			"Failed: rpr0521_set_power_state for %d, ret %d\n",
			on, ret);
		अगर (on)
			pm_runसमय_put_noidle(&data->client->dev);

		वापस ret;
	पूर्ण

	अगर (on) अणु
		/* If _resume() was not called, enable measurement now. */
		अगर (data->als_ps_need_en) अणु
			ret = rpr0521_als_enable(data, RPR0521_MODE_ALS_ENABLE);
			अगर (ret)
				वापस ret;
			data->als_ps_need_en = false;
		पूर्ण

		अगर (data->pxs_ps_need_en) अणु
			ret = rpr0521_pxs_enable(data, RPR0521_MODE_PXS_ENABLE);
			अगर (ret)
				वापस ret;
			data->pxs_ps_need_en = false;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

/* Interrupt रेजिस्टर tells अगर this sensor caused the पूर्णांकerrupt or not. */
अटल अंतरभूत bool rpr0521_is_triggered(काष्ठा rpr0521_data *data)
अणु
	पूर्णांक ret;
	पूर्णांक reg;

	ret = regmap_पढ़ो(data->regmap, RPR0521_REG_INTERRUPT, &reg);
	अगर (ret < 0)
		वापस false;   /* Reg पढ़ो failed. */
	अगर (reg &
	    (RPR0521_INTERRUPT_ALS_INT_STATUS_MASK |
	    RPR0521_INTERRUPT_PS_INT_STATUS_MASK))
		वापस true;
	अन्यथा
		वापस false;   /* Int not from this sensor. */
पूर्ण

/* IRQ to trigger handler */
अटल irqवापस_t rpr0521_drdy_irq_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा rpr0521_data *data = iio_priv(indio_dev);

	data->irq_बारtamp = iio_get_समय_ns(indio_dev);
	/*
	 * We need to wake the thपढ़ो to पढ़ो the पूर्णांकerrupt reg. It
	 * is not possible to करो that here because regmap_पढ़ो takes a
	 * mutex.
	 */

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t rpr0521_drdy_irq_thपढ़ो(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा rpr0521_data *data = iio_priv(indio_dev);

	अगर (rpr0521_is_triggered(data)) अणु
		iio_trigger_poll_chained(data->drdy_trigger0);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t rpr0521_trigger_consumer_store_समय(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;

	/* Other trigger polls store समय here. */
	अगर (!iio_trigger_using_own(indio_dev))
		pf->बारtamp = iio_get_समय_ns(indio_dev);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t rpr0521_trigger_consumer_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा rpr0521_data *data = iio_priv(indio_dev);
	पूर्णांक err;

	/* Use irq बारtamp when reasonable. */
	अगर (iio_trigger_using_own(indio_dev) && data->irq_बारtamp) अणु
		pf->बारtamp = data->irq_बारtamp;
		data->irq_बारtamp = 0;
	पूर्ण
	/* Other chained trigger polls get बारtamp only here. */
	अगर (!pf->बारtamp)
		pf->बारtamp = iio_get_समय_ns(indio_dev);

	err = regmap_bulk_पढ़ो(data->regmap, RPR0521_REG_PXS_DATA,
		data->scan.channels,
		(3 * 2) + 1);	/* 3 * 16-bit + (discarded) पूर्णांक clear reg. */
	अगर (!err)
		iio_push_to_buffers_with_बारtamp(indio_dev,
						   &data->scan, pf->बारtamp);
	अन्यथा
		dev_err(&data->client->dev,
			"Trigger consumer can't read from sensor.\n");
	pf->बारtamp = 0;

	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rpr0521_ग_लिखो_पूर्णांक_enable(काष्ठा rpr0521_data *data)
अणु
	पूर्णांक err;

	/* Interrupt after each measurement */
	err = regmap_update_bits(data->regmap, RPR0521_REG_PXS_CTRL,
		RPR0521_PXS_PERSISTENCE_MASK,
		RPR0521_PXS_PERSISTENCE_DRDY);
	अगर (err) अणु
		dev_err(&data->client->dev, "PS control reg write fail.\n");
		वापस -EBUSY;
		पूर्ण

	/* Ignore latch and mode because of drdy */
	err = regmap_ग_लिखो(data->regmap, RPR0521_REG_INTERRUPT,
		RPR0521_INTERRUPT_INT_REASSERT_DISABLE |
		RPR0521_INTERRUPT_INT_TRIG_ALS_DISABLE |
		RPR0521_INTERRUPT_INT_TRIG_PS_ENABLE
		);
	अगर (err) अणु
		dev_err(&data->client->dev, "Interrupt setup write fail.\n");
		वापस -EBUSY;
		पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rpr0521_ग_लिखो_पूर्णांक_disable(काष्ठा rpr0521_data *data)
अणु
	/* Don't care of clearing mode, निश्चित and latch. */
	वापस regmap_ग_लिखो(data->regmap, RPR0521_REG_INTERRUPT,
				RPR0521_INTERRUPT_INT_TRIG_ALS_DISABLE |
				RPR0521_INTERRUPT_INT_TRIG_PS_DISABLE
				);
पूर्ण

/*
 * Trigger producer enable / disable. Note that there will be trigs only when
 * measurement data is पढ़ोy to be पढ़ो.
 */
अटल पूर्णांक rpr0521_pxs_drdy_set_state(काष्ठा iio_trigger *trigger,
	bool enable_drdy)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trigger);
	काष्ठा rpr0521_data *data = iio_priv(indio_dev);
	पूर्णांक err;

	अगर (enable_drdy)
		err = rpr0521_ग_लिखो_पूर्णांक_enable(data);
	अन्यथा
		err = rpr0521_ग_लिखो_पूर्णांक_disable(data);
	अगर (err)
		dev_err(&data->client->dev, "rpr0521_pxs_drdy_set_state failed\n");

	वापस err;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops rpr0521_trigger_ops = अणु
	.set_trigger_state = rpr0521_pxs_drdy_set_state,
	पूर्ण;


अटल पूर्णांक rpr0521_buffer_preenable(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक err;
	काष्ठा rpr0521_data *data = iio_priv(indio_dev);

	mutex_lock(&data->lock);
	err = rpr0521_set_घातer_state(data, true,
		(RPR0521_MODE_PXS_MASK | RPR0521_MODE_ALS_MASK));
	mutex_unlock(&data->lock);
	अगर (err)
		dev_err(&data->client->dev, "_buffer_preenable fail\n");

	वापस err;
पूर्ण

अटल पूर्णांक rpr0521_buffer_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक err;
	काष्ठा rpr0521_data *data = iio_priv(indio_dev);

	mutex_lock(&data->lock);
	err = rpr0521_set_घातer_state(data, false,
		(RPR0521_MODE_PXS_MASK | RPR0521_MODE_ALS_MASK));
	mutex_unlock(&data->lock);
	अगर (err)
		dev_err(&data->client->dev, "_buffer_postdisable fail\n");

	वापस err;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops rpr0521_buffer_setup_ops = अणु
	.preenable = rpr0521_buffer_preenable,
	.postdisable = rpr0521_buffer_postdisable,
पूर्ण;

अटल पूर्णांक rpr0521_get_gain(काष्ठा rpr0521_data *data, पूर्णांक chan,
			    पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक ret, reg, idx;

	ret = regmap_पढ़ो(data->regmap, rpr0521_gain[chan].reg, &reg);
	अगर (ret < 0)
		वापस ret;

	idx = (rpr0521_gain[chan].mask & reg) >> rpr0521_gain[chan].shअगरt;
	*val = rpr0521_gain[chan].gain[idx].scale;
	*val2 = rpr0521_gain[chan].gain[idx].uscale;

	वापस 0;
पूर्ण

अटल पूर्णांक rpr0521_set_gain(काष्ठा rpr0521_data *data, पूर्णांक chan,
			    पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i, idx = -EINVAL;

	/* get gain index */
	क्रम (i = 0; i < rpr0521_gain[chan].size; i++)
		अगर (val == rpr0521_gain[chan].gain[i].scale &&
		    val2 == rpr0521_gain[chan].gain[i].uscale) अणु
			idx = i;
			अवरोध;
		पूर्ण

	अगर (idx < 0)
		वापस idx;

	वापस regmap_update_bits(data->regmap, rpr0521_gain[chan].reg,
				  rpr0521_gain[chan].mask,
				  idx << rpr0521_gain[chan].shअगरt);
पूर्ण

अटल पूर्णांक rpr0521_पढ़ो_samp_freq(काष्ठा rpr0521_data *data,
				क्रमागत iio_chan_type chan_type,
			    पूर्णांक *val, पूर्णांक *val2)
अणु
	पूर्णांक reg, ret;

	ret = regmap_पढ़ो(data->regmap, RPR0521_REG_MODE_CTRL, &reg);
	अगर (ret < 0)
		वापस ret;

	reg &= RPR0521_MODE_MEAS_TIME_MASK;
	अगर (reg >= ARRAY_SIZE(rpr0521_samp_freq_i))
		वापस -EINVAL;

	चयन (chan_type) अणु
	हाल IIO_INTENSITY:
		*val = rpr0521_samp_freq_i[reg].als_hz;
		*val2 = rpr0521_samp_freq_i[reg].als_uhz;
		वापस 0;

	हाल IIO_PROXIMITY:
		*val = rpr0521_samp_freq_i[reg].pxs_hz;
		*val2 = rpr0521_samp_freq_i[reg].pxs_uhz;
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक rpr0521_ग_लिखो_samp_freq_common(काष्ठा rpr0521_data *data,
				क्रमागत iio_chan_type chan_type,
				पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i;

	/*
	 * Ignore channel
	 * both pxs and als are setup only to same freq because of simplicity
	 */
	चयन (val) अणु
	हाल 0:
		i = 0;
		अवरोध;

	हाल 2:
		अगर (val2 != 500000)
			वापस -EINVAL;

		i = 11;
		अवरोध;

	हाल 10:
		i = 6;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(data->regmap,
		RPR0521_REG_MODE_CTRL,
		RPR0521_MODE_MEAS_TIME_MASK,
		i);
पूर्ण

अटल पूर्णांक rpr0521_पढ़ो_ps_offset(काष्ठा rpr0521_data *data, पूर्णांक *offset)
अणु
	पूर्णांक ret;
	__le16 buffer;

	ret = regmap_bulk_पढ़ो(data->regmap,
		RPR0521_REG_PS_OFFSET_LSB, &buffer, माप(buffer));

	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Failed to read PS OFFSET register\n");
		वापस ret;
	पूर्ण
	*offset = le16_to_cpu(buffer);

	वापस ret;
पूर्ण

अटल पूर्णांक rpr0521_ग_लिखो_ps_offset(काष्ठा rpr0521_data *data, पूर्णांक offset)
अणु
	पूर्णांक ret;
	__le16 buffer;

	buffer = cpu_to_le16(offset & 0x3ff);
	ret = regmap_raw_ग_लिखो(data->regmap,
		RPR0521_REG_PS_OFFSET_LSB, &buffer, माप(buffer));

	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Failed to write PS OFFSET register\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rpr0521_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			    पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा rpr0521_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	पूर्णांक busy;
	u8 device_mask;
	__le16 raw_data;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (chan->type != IIO_INTENSITY && chan->type != IIO_PROXIMITY)
			वापस -EINVAL;

		busy = iio_device_claim_direct_mode(indio_dev);
		अगर (busy)
			वापस -EBUSY;

		device_mask = rpr0521_data_reg[chan->address].device_mask;

		mutex_lock(&data->lock);
		ret = rpr0521_set_घातer_state(data, true, device_mask);
		अगर (ret < 0)
			जाओ rpr0521_पढ़ो_raw_out;

		ret = regmap_bulk_पढ़ो(data->regmap,
				       rpr0521_data_reg[chan->address].address,
				       &raw_data, माप(raw_data));
		अगर (ret < 0) अणु
			rpr0521_set_घातer_state(data, false, device_mask);
			जाओ rpr0521_पढ़ो_raw_out;
		पूर्ण

		ret = rpr0521_set_घातer_state(data, false, device_mask);

rpr0521_पढ़ो_raw_out:
		mutex_unlock(&data->lock);
		iio_device_release_direct_mode(indio_dev);
		अगर (ret < 0)
			वापस ret;

		*val = le16_to_cpu(raw_data);

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		mutex_lock(&data->lock);
		ret = rpr0521_get_gain(data, chan->address, val, val2);
		mutex_unlock(&data->lock);
		अगर (ret < 0)
			वापस ret;

		वापस IIO_VAL_INT_PLUS_MICRO;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&data->lock);
		ret = rpr0521_पढ़ो_samp_freq(data, chan->type, val, val2);
		mutex_unlock(&data->lock);
		अगर (ret < 0)
			वापस ret;

		वापस IIO_VAL_INT_PLUS_MICRO;

	हाल IIO_CHAN_INFO_OFFSET:
		mutex_lock(&data->lock);
		ret = rpr0521_पढ़ो_ps_offset(data, val);
		mutex_unlock(&data->lock);
		अगर (ret < 0)
			वापस ret;

		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक rpr0521_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val,
			     पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा rpr0521_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		mutex_lock(&data->lock);
		ret = rpr0521_set_gain(data, chan->address, val, val2);
		mutex_unlock(&data->lock);

		वापस ret;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&data->lock);
		ret = rpr0521_ग_लिखो_samp_freq_common(data, chan->type,
						     val, val2);
		mutex_unlock(&data->lock);

		वापस ret;

	हाल IIO_CHAN_INFO_OFFSET:
		mutex_lock(&data->lock);
		ret = rpr0521_ग_लिखो_ps_offset(data, val);
		mutex_unlock(&data->lock);

		वापस ret;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info rpr0521_info = अणु
	.पढ़ो_raw	= rpr0521_पढ़ो_raw,
	.ग_लिखो_raw	= rpr0521_ग_लिखो_raw,
	.attrs		= &rpr0521_attribute_group,
पूर्ण;

अटल पूर्णांक rpr0521_init(काष्ठा rpr0521_data *data)
अणु
	पूर्णांक ret;
	पूर्णांक id;

	ret = regmap_पढ़ो(data->regmap, RPR0521_REG_ID, &id);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Failed to read REG_ID register\n");
		वापस ret;
	पूर्ण

	अगर (id != RPR0521_MANUFACT_ID) अणु
		dev_err(&data->client->dev, "Wrong id, got %x, expected %x\n",
			id, RPR0521_MANUFACT_ID);
		वापस -ENODEV;
	पूर्ण

	/* set शेष measurement समय - 100 ms क्रम both ALS and PS */
	ret = regmap_update_bits(data->regmap, RPR0521_REG_MODE_CTRL,
				 RPR0521_MODE_MEAS_TIME_MASK,
				 RPR0521_DEFAULT_MEAS_TIME);
	अगर (ret) अणु
		pr_err("regmap_update_bits returned %d\n", ret);
		वापस ret;
	पूर्ण

#अगर_अघोषित CONFIG_PM
	ret = rpr0521_als_enable(data, RPR0521_MODE_ALS_ENABLE);
	अगर (ret < 0)
		वापस ret;
	ret = rpr0521_pxs_enable(data, RPR0521_MODE_PXS_ENABLE);
	अगर (ret < 0)
		वापस ret;
#पूर्ण_अगर

	data->irq_बारtamp = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक rpr0521_घातeroff(काष्ठा rpr0521_data *data)
अणु
	पूर्णांक ret;
	पूर्णांक पंचांगp;

	ret = regmap_update_bits(data->regmap, RPR0521_REG_MODE_CTRL,
				 RPR0521_MODE_ALS_MASK |
				 RPR0521_MODE_PXS_MASK,
				 RPR0521_MODE_ALS_DISABLE |
				 RPR0521_MODE_PXS_DISABLE);
	अगर (ret < 0)
		वापस ret;

	data->als_dev_en = false;
	data->pxs_dev_en = false;

	/*
	 * Int pin keeps state after घातer off. Set pin to high impedance
	 * mode to prevent घातer drain.
	 */
	ret = regmap_पढ़ो(data->regmap, RPR0521_REG_INTERRUPT, &पंचांगp);
	अगर (ret) अणु
		dev_err(&data->client->dev, "Failed to reset int pin.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool rpr0521_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RPR0521_REG_MODE_CTRL:
	हाल RPR0521_REG_ALS_CTRL:
	हाल RPR0521_REG_PXS_CTRL:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config rpr0521_regmap_config = अणु
	.name		= RPR0521_REGMAP_NAME,

	.reg_bits	= 8,
	.val_bits	= 8,

	.max_रेजिस्टर	= RPR0521_REG_ID,
	.cache_type	= REGCACHE_RBTREE,
	.अस्थिर_reg	= rpr0521_is_अस्थिर_reg,
पूर्ण;

अटल पूर्णांक rpr0521_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rpr0521_data *data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	regmap = devm_regmap_init_i2c(client, &rpr0521_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "regmap_init failed!\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	data->regmap = regmap;

	mutex_init(&data->lock);

	indio_dev->info = &rpr0521_info;
	indio_dev->name = RPR0521_DRV_NAME;
	indio_dev->channels = rpr0521_channels;
	indio_dev->num_channels = ARRAY_SIZE(rpr0521_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = rpr0521_init(data);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "rpr0521 chip init failed\n");
		वापस ret;
	पूर्ण

	ret = pm_runसमय_set_active(&client->dev);
	अगर (ret < 0)
		जाओ err_घातeroff;

	pm_runसमय_enable(&client->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&client->dev, RPR0521_SLEEP_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(&client->dev);

	/*
	 * If sensor ग_लिखो/पढ़ो is needed in _probe after _use_स्वतःsuspend,
	 * sensor needs to be _resumed first using rpr0521_set_घातer_state().
	 */

	/* IRQ to trigger setup */
	अगर (client->irq) अणु
		/* Trigger0 producer setup */
		data->drdy_trigger0 = devm_iio_trigger_alloc(
			indio_dev->dev.parent,
			"%s-dev%d", indio_dev->name, indio_dev->id);
		अगर (!data->drdy_trigger0) अणु
			ret = -ENOMEM;
			जाओ err_pm_disable;
		पूर्ण
		data->drdy_trigger0->ops = &rpr0521_trigger_ops;
		indio_dev->available_scan_masks = rpr0521_available_scan_masks;
		iio_trigger_set_drvdata(data->drdy_trigger0, indio_dev);

		/* Ties irq to trigger producer handler. */
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
			rpr0521_drdy_irq_handler, rpr0521_drdy_irq_thपढ़ो,
			IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
			RPR0521_IRQ_NAME, indio_dev);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "request irq %d for trigger0 failed\n",
				client->irq);
			जाओ err_pm_disable;
			पूर्ण

		ret = devm_iio_trigger_रेजिस्टर(indio_dev->dev.parent,
						data->drdy_trigger0);
		अगर (ret) अणु
			dev_err(&client->dev, "iio trigger register failed\n");
			जाओ err_pm_disable;
		पूर्ण

		/*
		 * Now whole pipe from physical पूर्णांकerrupt (irq defined by
		 * devicetree to device) to trigger0 output is set up.
		 */

		/* Trigger consumer setup */
		ret = devm_iio_triggered_buffer_setup(indio_dev->dev.parent,
			indio_dev,
			rpr0521_trigger_consumer_store_समय,
			rpr0521_trigger_consumer_handler,
			&rpr0521_buffer_setup_ops);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "iio triggered buffer setup failed\n");
			जाओ err_pm_disable;
		पूर्ण
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ err_pm_disable;

	वापस 0;

err_pm_disable:
	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	pm_runसमय_put_noidle(&client->dev);
err_घातeroff:
	rpr0521_घातeroff(data);

	वापस ret;
पूर्ण

अटल पूर्णांक rpr0521_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unरेजिस्टर(indio_dev);

	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	pm_runसमय_put_noidle(&client->dev);

	rpr0521_घातeroff(iio_priv(indio_dev));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rpr0521_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा rpr0521_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->lock);
	/* If measurements are enabled, enable them on resume */
	अगर (!data->als_need_dis)
		data->als_ps_need_en = data->als_dev_en;
	अगर (!data->pxs_need_dis)
		data->pxs_ps_need_en = data->pxs_dev_en;

	/* disable channels and sets अणुals,pxsपूर्ण_dev_en to false */
	ret = rpr0521_घातeroff(data);
	regcache_mark_dirty(data->regmap);
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक rpr0521_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा rpr0521_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	regcache_sync(data->regmap);
	अगर (data->als_ps_need_en) अणु
		ret = rpr0521_als_enable(data, RPR0521_MODE_ALS_ENABLE);
		अगर (ret < 0)
			वापस ret;
		data->als_ps_need_en = false;
	पूर्ण

	अगर (data->pxs_ps_need_en) अणु
		ret = rpr0521_pxs_enable(data, RPR0521_MODE_PXS_ENABLE);
		अगर (ret < 0)
			वापस ret;
		data->pxs_ps_need_en = false;
	पूर्ण
	msleep(100);	//रुको क्रम first measurement result

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops rpr0521_pm_ops = अणु
	SET_RUNTIME_PM_OPS(rpr0521_runसमय_suspend,
			   rpr0521_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id rpr0521_acpi_match[] = अणु
	अणु"RPR0521", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rpr0521_acpi_match);

अटल स्थिर काष्ठा i2c_device_id rpr0521_id[] = अणु
	अणु"rpr0521", 0पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, rpr0521_id);

अटल काष्ठा i2c_driver rpr0521_driver = अणु
	.driver = अणु
		.name	= RPR0521_DRV_NAME,
		.pm	= &rpr0521_pm_ops,
		.acpi_match_table = ACPI_PTR(rpr0521_acpi_match),
	पूर्ण,
	.probe		= rpr0521_probe,
	.हटाओ		= rpr0521_हटाओ,
	.id_table	= rpr0521_id,
पूर्ण;

module_i2c_driver(rpr0521_driver);

MODULE_AUTHOR("Daniel Baluta <daniel.baluta@intel.com>");
MODULE_DESCRIPTION("RPR0521 ROHM Ambient Light and Proximity Sensor driver");
MODULE_LICENSE("GPL v2");
