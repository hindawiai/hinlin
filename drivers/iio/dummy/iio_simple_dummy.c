<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011 Jonathan Cameron
 *
 * A reference industrial I/O driver to illustrate the functionality available.
 *
 * There are numerous real drivers to illustrate the finer poपूर्णांकs.
 * The purpose of this driver is to provide a driver with far more comments
 * and explanatory notes than any 'real' driver would have.
 * Anyone starting out writing an IIO driver should first make sure they
 * understand all of this driver except those bits specअगरically marked
 * as being present to allow us to 'fake' the presence of hardware.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/sw_device.h>
#समावेश "iio_simple_dummy.h"

अटल स्थिर काष्ठा config_item_type iio_dummy_type = अणु
	.ct_owner = THIS_MODULE,
पूर्ण;

/**
 * काष्ठा iio_dummy_accel_calibscale - realworld to रेजिस्टर mapping
 * @val: first value in पढ़ो_raw - here पूर्णांकeger part.
 * @val2: second value in पढ़ो_raw etc - here micro part.
 * @regval: रेजिस्टर value - magic device specअगरic numbers.
 */
काष्ठा iio_dummy_accel_calibscale अणु
	पूर्णांक val;
	पूर्णांक val2;
	पूर्णांक regval; /* what would be written to hardware */
पूर्ण;

अटल स्थिर काष्ठा iio_dummy_accel_calibscale dummy_scales[] = अणु
	अणु 0, 100, 0x8 पूर्ण, /* 0.000100 */
	अणु 0, 133, 0x7 पूर्ण, /* 0.000133 */
	अणु 733, 13, 0x9 पूर्ण, /* 733.000013 */
पूर्ण;

#अगर_घोषित CONFIG_IIO_SIMPLE_DUMMY_EVENTS

/*
 * simple event - triggered when value rises above
 * a threshold
 */
अटल स्थिर काष्ठा iio_event_spec iio_dummy_event = अणु
	.type = IIO_EV_TYPE_THRESH,
	.dir = IIO_EV_सूची_RISING,
	.mask_separate = BIT(IIO_EV_INFO_VALUE) | BIT(IIO_EV_INFO_ENABLE),
पूर्ण;

/*
 * simple step detect event - triggered when a step is detected
 */
अटल स्थिर काष्ठा iio_event_spec step_detect_event = अणु
	.type = IIO_EV_TYPE_CHANGE,
	.dir = IIO_EV_सूची_NONE,
	.mask_separate = BIT(IIO_EV_INFO_ENABLE),
पूर्ण;

/*
 * simple transition event - triggered when the reported running confidence
 * value rises above a threshold value
 */
अटल स्थिर काष्ठा iio_event_spec iio_running_event = अणु
	.type = IIO_EV_TYPE_THRESH,
	.dir = IIO_EV_सूची_RISING,
	.mask_separate = BIT(IIO_EV_INFO_VALUE) | BIT(IIO_EV_INFO_ENABLE),
पूर्ण;

/*
 * simple transition event - triggered when the reported walking confidence
 * value falls under a threshold value
 */
अटल स्थिर काष्ठा iio_event_spec iio_walking_event = अणु
	.type = IIO_EV_TYPE_THRESH,
	.dir = IIO_EV_सूची_FALLING,
	.mask_separate = BIT(IIO_EV_INFO_VALUE) | BIT(IIO_EV_INFO_ENABLE),
पूर्ण;
#पूर्ण_अगर

/*
 * iio_dummy_channels - Description of available channels
 *
 * This array of काष्ठाures tells the IIO core about what the device
 * actually provides क्रम a given channel.
 */
अटल स्थिर काष्ठा iio_chan_spec iio_dummy_channels[] = अणु
	/* indexed ADC channel in_voltage0_raw etc */
	अणु
		.type = IIO_VOLTAGE,
		/* Channel has a numeric index of 0 */
		.indexed = 1,
		.channel = 0,
		/* What other inक्रमmation is available? */
		.info_mask_separate =
		/*
		 * in_voltage0_raw
		 * Raw (unscaled no bias removal etc) measurement
		 * from the device.
		 */
		BIT(IIO_CHAN_INFO_RAW) |
		/*
		 * in_voltage0_offset
		 * Offset क्रम userspace to apply prior to scale
		 * when converting to standard units (microvolts)
		 */
		BIT(IIO_CHAN_INFO_OFFSET) |
		/*
		 * in_voltage0_scale
		 * Multipler क्रम userspace to apply post offset
		 * when converting to standard units (microvolts)
		 */
		BIT(IIO_CHAN_INFO_SCALE),
		/*
		 * sampling_frequency
		 * The frequency in Hz at which the channels are sampled
		 */
		.info_mask_shared_by_dir = BIT(IIO_CHAN_INFO_SAMP_FREQ),
		/* The ordering of elements in the buffer via an क्रमागत */
		.scan_index = DUMMY_INDEX_VOLTAGE_0,
		.scan_type = अणु /* Description of storage in buffer */
			.sign = 'u', /* अचिन्हित */
			.realbits = 13, /* 13 bits */
			.storagebits = 16, /* 16 bits used क्रम storage */
			.shअगरt = 0, /* zero shअगरt */
		पूर्ण,
#अगर_घोषित CONFIG_IIO_SIMPLE_DUMMY_EVENTS
		.event_spec = &iio_dummy_event,
		.num_event_specs = 1,
#पूर्ण_अगर /* CONFIG_IIO_SIMPLE_DUMMY_EVENTS */
	पूर्ण,
	/* Dअगरferential ADC channel in_voltage1-voltage2_raw etc*/
	अणु
		.type = IIO_VOLTAGE,
		.dअगरferential = 1,
		/*
		 * Indexing क्रम dअगरferential channels uses channel
		 * क्रम the positive part, channel2 क्रम the negative.
		 */
		.indexed = 1,
		.channel = 1,
		.channel2 = 2,
		/*
		 * in_voltage1-voltage2_raw
		 * Raw (unscaled no bias removal etc) measurement
		 * from the device.
		 */
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		/*
		 * in_voltage-voltage_scale
		 * Shared version of scale - shared by dअगरferential
		 * input channels of type IIO_VOLTAGE.
		 */
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
		/*
		 * sampling_frequency
		 * The frequency in Hz at which the channels are sampled
		 */
		.scan_index = DUMMY_INDEX_DIFFVOLTAGE_1M2,
		.scan_type = अणु /* Description of storage in buffer */
			.sign = 's', /* चिन्हित */
			.realbits = 12, /* 12 bits */
			.storagebits = 16, /* 16 bits used क्रम storage */
			.shअगरt = 0, /* zero shअगरt */
		पूर्ण,
	पूर्ण,
	/* Dअगरferential ADC channel in_voltage3-voltage4_raw etc*/
	अणु
		.type = IIO_VOLTAGE,
		.dअगरferential = 1,
		.indexed = 1,
		.channel = 3,
		.channel2 = 4,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_shared_by_dir = BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.scan_index = DUMMY_INDEX_DIFFVOLTAGE_3M4,
		.scan_type = अणु
			.sign = 's',
			.realbits = 11,
			.storagebits = 16,
			.shअगरt = 0,
		पूर्ण,
	पूर्ण,
	/*
	 * 'modified' (i.e. axis specअगरied) acceleration channel
	 * in_accel_z_raw
	 */
	अणु
		.type = IIO_ACCEL,
		.modअगरied = 1,
		/* Channel 2 is use क्रम modअगरiers */
		.channel2 = IIO_MOD_X,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
		/*
		 * Internal bias and gain correction values. Applied
		 * by the hardware or driver prior to userspace
		 * seeing the पढ़ोings. Typically part of hardware
		 * calibration.
		 */
		BIT(IIO_CHAN_INFO_CALIBSCALE) |
		BIT(IIO_CHAN_INFO_CALIBBIAS),
		.info_mask_shared_by_dir = BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.scan_index = DUMMY_INDEX_ACCELX,
		.scan_type = अणु /* Description of storage in buffer */
			.sign = 's', /* चिन्हित */
			.realbits = 16, /* 16 bits */
			.storagebits = 16, /* 16 bits used क्रम storage */
			.shअगरt = 0, /* zero shअगरt */
		पूर्ण,
	पूर्ण,
	/*
	 * Convenience macro क्रम बारtamps. 4 is the index in
	 * the buffer.
	 */
	IIO_CHAN_SOFT_TIMESTAMP(4),
	/* DAC channel out_voltage0_raw */
	अणु
		.type = IIO_VOLTAGE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.scan_index = -1, /* No buffer support */
		.output = 1,
		.indexed = 1,
		.channel = 0,
	पूर्ण,
	अणु
		.type = IIO_STEPS,
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_ENABLE) |
			BIT(IIO_CHAN_INFO_CALIBHEIGHT),
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.scan_index = -1, /* No buffer support */
#अगर_घोषित CONFIG_IIO_SIMPLE_DUMMY_EVENTS
		.event_spec = &step_detect_event,
		.num_event_specs = 1,
#पूर्ण_अगर /* CONFIG_IIO_SIMPLE_DUMMY_EVENTS */
	पूर्ण,
	अणु
		.type = IIO_ACTIVITY,
		.modअगरied = 1,
		.channel2 = IIO_MOD_RUNNING,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.scan_index = -1, /* No buffer support */
#अगर_घोषित CONFIG_IIO_SIMPLE_DUMMY_EVENTS
		.event_spec = &iio_running_event,
		.num_event_specs = 1,
#पूर्ण_अगर /* CONFIG_IIO_SIMPLE_DUMMY_EVENTS */
	पूर्ण,
	अणु
		.type = IIO_ACTIVITY,
		.modअगरied = 1,
		.channel2 = IIO_MOD_WALKING,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.scan_index = -1, /* No buffer support */
#अगर_घोषित CONFIG_IIO_SIMPLE_DUMMY_EVENTS
		.event_spec = &iio_walking_event,
		.num_event_specs = 1,
#पूर्ण_अगर /* CONFIG_IIO_SIMPLE_DUMMY_EVENTS */
	पूर्ण,
पूर्ण;

/**
 * iio_dummy_पढ़ो_raw() - data पढ़ो function.
 * @indio_dev:	the काष्ठा iio_dev associated with this device instance
 * @chan:	the channel whose data is to be पढ़ो
 * @val:	first element of वापसed value (typically INT)
 * @val2:	second element of वापसed value (typically MICRO)
 * @mask:	what we actually want to पढ़ो as per the info_mask_*
 *		in iio_chan_spec.
 */
अटल पूर्णांक iio_dummy_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक *val,
			      पूर्णांक *val2,
			      दीर्घ mask)
अणु
	काष्ठा iio_dummy_state *st = iio_priv(indio_dev);
	पूर्णांक ret = -EINVAL;

	mutex_lock(&st->lock);
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW: /* magic value - channel value पढ़ो */
		चयन (chan->type) अणु
		हाल IIO_VOLTAGE:
			अगर (chan->output) अणु
				/* Set पूर्णांकeger part to cached value */
				*val = st->dac_val;
				ret = IIO_VAL_INT;
			पूर्ण अन्यथा अगर (chan->dअगरferential) अणु
				अगर (chan->channel == 1)
					*val = st->dअगरferential_adc_val[0];
				अन्यथा
					*val = st->dअगरferential_adc_val[1];
				ret = IIO_VAL_INT;
			पूर्ण अन्यथा अणु
				*val = st->single_ended_adc_val;
				ret = IIO_VAL_INT;
			पूर्ण
			अवरोध;
		हाल IIO_ACCEL:
			*val = st->accel_val;
			ret = IIO_VAL_INT;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (chan->type) अणु
		हाल IIO_STEPS:
			*val = st->steps;
			ret = IIO_VAL_INT;
			अवरोध;
		हाल IIO_ACTIVITY:
			चयन (chan->channel2) अणु
			हाल IIO_MOD_RUNNING:
				*val = st->activity_running;
				ret = IIO_VAL_INT;
				अवरोध;
			हाल IIO_MOD_WALKING:
				*val = st->activity_walking;
				ret = IIO_VAL_INT;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_OFFSET:
		/* only single ended adc -> 7 */
		*val = 7;
		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_VOLTAGE:
			चयन (chan->dअगरferential) अणु
			हाल 0:
				/* only single ended adc -> 0.001333 */
				*val = 0;
				*val2 = 1333;
				ret = IIO_VAL_INT_PLUS_MICRO;
				अवरोध;
			हाल 1:
				/* all dअगरferential adc -> 0.000001344 */
				*val = 0;
				*val2 = 1344;
				ret = IIO_VAL_INT_PLUS_न_अंकO;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		/* only the acceleration axis - पढ़ो from cache */
		*val = st->accel_calibbias;
		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBSCALE:
		*val = st->accel_calibscale->val;
		*val2 = st->accel_calibscale->val2;
		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = 3;
		*val2 = 33;
		ret = IIO_VAL_INT_PLUS_न_अंकO;
		अवरोध;
	हाल IIO_CHAN_INFO_ENABLE:
		चयन (chan->type) अणु
		हाल IIO_STEPS:
			*val = st->steps_enabled;
			ret = IIO_VAL_INT;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBHEIGHT:
		चयन (chan->type) अणु
		हाल IIO_STEPS:
			*val = st->height;
			ret = IIO_VAL_INT;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

/**
 * iio_dummy_ग_लिखो_raw() - data ग_लिखो function.
 * @indio_dev:	the काष्ठा iio_dev associated with this device instance
 * @chan:	the channel whose data is to be written
 * @val:	first element of value to set (typically INT)
 * @val2:	second element of value to set (typically MICRO)
 * @mask:	what we actually want to ग_लिखो as per the info_mask_*
 *		in iio_chan_spec.
 *
 * Note that all raw ग_लिखोs are assumed IIO_VAL_INT and info mask elements
 * are assumed to be IIO_INT_PLUS_MICRO unless the callback ग_लिखो_raw_get_fmt
 * in काष्ठा iio_info is provided by the driver.
 */
अटल पूर्णांक iio_dummy_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val,
			       पूर्णांक val2,
			       दीर्घ mask)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	काष्ठा iio_dummy_state *st = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_VOLTAGE:
			अगर (chan->output == 0)
				वापस -EINVAL;

			/* Locking not required as writing single value */
			mutex_lock(&st->lock);
			st->dac_val = val;
			mutex_unlock(&st->lock);
			वापस 0;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (chan->type) अणु
		हाल IIO_STEPS:
			mutex_lock(&st->lock);
			st->steps = val;
			mutex_unlock(&st->lock);
			वापस 0;
		हाल IIO_ACTIVITY:
			अगर (val < 0)
				val = 0;
			अगर (val > 100)
				val = 100;
			चयन (chan->channel2) अणु
			हाल IIO_MOD_RUNNING:
				st->activity_running = val;
				वापस 0;
			हाल IIO_MOD_WALKING:
				st->activity_walking = val;
				वापस 0;
			शेष:
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_CALIBSCALE:
		mutex_lock(&st->lock);
		/* Compare against table - hard matching here */
		क्रम (i = 0; i < ARRAY_SIZE(dummy_scales); i++)
			अगर (val == dummy_scales[i].val &&
			    val2 == dummy_scales[i].val2)
				अवरोध;
		अगर (i == ARRAY_SIZE(dummy_scales))
			ret = -EINVAL;
		अन्यथा
			st->accel_calibscale = &dummy_scales[i];
		mutex_unlock(&st->lock);
		वापस ret;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		mutex_lock(&st->lock);
		st->accel_calibbias = val;
		mutex_unlock(&st->lock);
		वापस 0;
	हाल IIO_CHAN_INFO_ENABLE:
		चयन (chan->type) अणु
		हाल IIO_STEPS:
			mutex_lock(&st->lock);
			st->steps_enabled = val;
			mutex_unlock(&st->lock);
			वापस 0;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_CALIBHEIGHT:
		चयन (chan->type) अणु
		हाल IIO_STEPS:
			st->height = val;
			वापस 0;
		शेष:
			वापस -EINVAL;
		पूर्ण

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * Device type specअगरic inक्रमmation.
 */
अटल स्थिर काष्ठा iio_info iio_dummy_info = अणु
	.पढ़ो_raw = &iio_dummy_पढ़ो_raw,
	.ग_लिखो_raw = &iio_dummy_ग_लिखो_raw,
#अगर_घोषित CONFIG_IIO_SIMPLE_DUMMY_EVENTS
	.पढ़ो_event_config = &iio_simple_dummy_पढ़ो_event_config,
	.ग_लिखो_event_config = &iio_simple_dummy_ग_लिखो_event_config,
	.पढ़ो_event_value = &iio_simple_dummy_पढ़ो_event_value,
	.ग_लिखो_event_value = &iio_simple_dummy_ग_लिखो_event_value,
#पूर्ण_अगर /* CONFIG_IIO_SIMPLE_DUMMY_EVENTS */
पूर्ण;

/**
 * iio_dummy_init_device() - device instance specअगरic init
 * @indio_dev: the iio device काष्ठाure
 *
 * Most drivers have one of these to set up शेष values,
 * reset the device to known state etc.
 */
अटल पूर्णांक iio_dummy_init_device(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dummy_state *st = iio_priv(indio_dev);

	st->dac_val = 0;
	st->single_ended_adc_val = 73;
	st->dअगरferential_adc_val[0] = 33;
	st->dअगरferential_adc_val[1] = -34;
	st->accel_val = 34;
	st->accel_calibbias = -7;
	st->accel_calibscale = &dummy_scales[0];
	st->steps = 47;
	st->activity_running = 98;
	st->activity_walking = 4;

	वापस 0;
पूर्ण

/**
 * iio_dummy_probe() - device instance probe
 * @name: name of this instance.
 *
 * Arguments are bus type specअगरic.
 * I2C: iio_dummy_probe(काष्ठा i2c_client *client,
 *                      स्थिर काष्ठा i2c_device_id *id)
 * SPI: iio_dummy_probe(काष्ठा spi_device *spi)
 */
अटल काष्ठा iio_sw_device *iio_dummy_probe(स्थिर अक्षर *name)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev;
	काष्ठा iio_dummy_state *st;
	काष्ठा iio_sw_device *swd;
	काष्ठा device *parent = शून्य;

	/*
	 * With hardware: Set the parent device.
	 * parent = &spi->dev;
	 * parent = &client->dev;
	 */

	swd = kzalloc(माप(*swd), GFP_KERNEL);
	अगर (!swd) अणु
		ret = -ENOMEM;
		जाओ error_kzalloc;
	पूर्ण
	/*
	 * Allocate an IIO device.
	 *
	 * This काष्ठाure contains all generic state
	 * inक्रमmation about the device instance.
	 * It also has a region (accessed by iio_priv()
	 * क्रम chip specअगरic state inक्रमmation.
	 */
	indio_dev = iio_device_alloc(parent, माप(*st));
	अगर (!indio_dev) अणु
		ret = -ENOMEM;
		जाओ error_ret;
	पूर्ण

	st = iio_priv(indio_dev);
	mutex_init(&st->lock);

	iio_dummy_init_device(indio_dev);

	 /*
	 * Make the iio_dev काष्ठा available to हटाओ function.
	 * Bus equivalents
	 * i2c_set_clientdata(client, indio_dev);
	 * spi_set_drvdata(spi, indio_dev);
	 */
	swd->device = indio_dev;

	/*
	 * Set the device name.
	 *
	 * This is typically a part number and obtained from the module
	 * id table.
	 * e.g. क्रम i2c and spi:
	 *    indio_dev->name = id->name;
	 *    indio_dev->name = spi_get_device_id(spi)->name;
	 */
	indio_dev->name = kstrdup(name, GFP_KERNEL);

	/* Provide description of available channels */
	indio_dev->channels = iio_dummy_channels;
	indio_dev->num_channels = ARRAY_SIZE(iio_dummy_channels);

	/*
	 * Provide device type specअगरic पूर्णांकerface functions and
	 * स्थिरant data.
	 */
	indio_dev->info = &iio_dummy_info;

	/* Specअगरy that device provides sysfs type पूर्णांकerfaces */
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = iio_simple_dummy_events_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ error_मुक्त_device;

	ret = iio_simple_dummy_configure_buffer(indio_dev);
	अगर (ret < 0)
		जाओ error_unरेजिस्टर_events;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ error_unconfigure_buffer;

	iio_swd_group_init_type_name(swd, name, &iio_dummy_type);

	वापस swd;
error_unconfigure_buffer:
	iio_simple_dummy_unconfigure_buffer(indio_dev);
error_unरेजिस्टर_events:
	iio_simple_dummy_events_unरेजिस्टर(indio_dev);
error_मुक्त_device:
	iio_device_मुक्त(indio_dev);
error_ret:
	kमुक्त(swd);
error_kzalloc:
	वापस ERR_PTR(ret);
पूर्ण

/**
 * iio_dummy_हटाओ() - device instance removal function
 * @swd: poपूर्णांकer to software IIO device असलtraction
 *
 * Parameters follow those of iio_dummy_probe क्रम buses.
 */
अटल पूर्णांक iio_dummy_हटाओ(काष्ठा iio_sw_device *swd)
अणु
	/*
	 * Get a poपूर्णांकer to the device instance iio_dev काष्ठाure
	 * from the bus subप्रणाली. E.g.
	 * काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	 * काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	 */
	काष्ठा iio_dev *indio_dev = swd->device;

	/* Unरेजिस्टर the device */
	iio_device_unरेजिस्टर(indio_dev);

	/* Device specअगरic code to घातer करोwn etc */

	/* Buffered capture related cleanup */
	iio_simple_dummy_unconfigure_buffer(indio_dev);

	iio_simple_dummy_events_unरेजिस्टर(indio_dev);

	/* Free all काष्ठाures */
	kमुक्त(indio_dev->name);
	iio_device_मुक्त(indio_dev);

	वापस 0;
पूर्ण

/*
 * module_iio_sw_device_driver() -  device driver registration
 *
 * Varies depending on bus type of the device. As there is no device
 * here, call probe directly. For inक्रमmation on device registration
 * i2c:
 * Documentation/i2c/writing-clients.rst
 * spi:
 * Documentation/spi/spi-summary.rst
 */
अटल स्थिर काष्ठा iio_sw_device_ops iio_dummy_device_ops = अणु
	.probe = iio_dummy_probe,
	.हटाओ = iio_dummy_हटाओ,
पूर्ण;

अटल काष्ठा iio_sw_device_type iio_dummy_device = अणु
	.name = "dummy",
	.owner = THIS_MODULE,
	.ops = &iio_dummy_device_ops,
पूर्ण;

module_iio_sw_device_driver(iio_dummy_device);

MODULE_AUTHOR("Jonathan Cameron <jic23@kernel.org>");
MODULE_DESCRIPTION("IIO dummy driver");
MODULE_LICENSE("GPL v2");
