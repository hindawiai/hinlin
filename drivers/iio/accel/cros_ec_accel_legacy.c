<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम older Chrome OS EC accelerometer
 *
 * Copyright 2017 Google, Inc
 *
 * This driver uses the memory mapper cros-ec पूर्णांकerface to communicate
 * with the Chrome OS EC about accelerometer data or older commands.
 * Accelerometer access is presented through iio sysfs.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/common/cros_ec_sensors_core.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/kfअगरo_buf.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा DRV_NAME	"cros-ec-accel-legacy"

#घोषणा CROS_EC_SENSOR_LEGACY_NUM 2
/*
 * Sensor scale hard coded at 10 bits per g, computed as:
 * g / (2^10 - 1) = 0.009586168; with g = 9.80665 m.s^-2
 */
#घोषणा ACCEL_LEGACY_NSCALE 9586168

/*
 * Sensor frequency is hard-coded to 10Hz.
 */
अटल स्थिर पूर्णांक cros_ec_legacy_sample_freq[] = अणु 10, 0 पूर्ण;

अटल पूर्णांक cros_ec_accel_legacy_पढ़ो_cmd(काष्ठा iio_dev *indio_dev,
				  अचिन्हित दीर्घ scan_mask, s16 *data)
अणु
	काष्ठा cros_ec_sensors_core_state *st = iio_priv(indio_dev);
	पूर्णांक ret;
	अचिन्हित पूर्णांक i;
	u8 sensor_num;

	/*
	 * Read all sensor data through a command.
	 * Save sensor_num, it is assumed to stay.
	 */
	sensor_num = st->param.info.sensor_num;
	st->param.cmd = MOTIONSENSE_CMD_DUMP;
	st->param.dump.max_sensor_count = CROS_EC_SENSOR_LEGACY_NUM;
	ret = cros_ec_motion_send_host_cmd(st,
			माप(st->resp->dump) + CROS_EC_SENSOR_LEGACY_NUM *
			माप(काष्ठा ec_response_motion_sensor_data));
	st->param.info.sensor_num = sensor_num;
	अगर (ret != 0) अणु
		dev_warn(&indio_dev->dev, "Unable to read sensor data\n");
		वापस ret;
	पूर्ण

	क्रम_each_set_bit(i, &scan_mask, indio_dev->masklength) अणु
		*data = st->resp->dump.sensor[sensor_num].data[i] *
			st->sign[i];
		data++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_accel_legacy_पढ़ो(काष्ठा iio_dev *indio_dev,
				     काष्ठा iio_chan_spec स्थिर *chan,
				     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा cros_ec_sensors_core_state *st = iio_priv(indio_dev);
	s16 data = 0;
	पूर्णांक ret;
	पूर्णांक idx = chan->scan_index;

	mutex_lock(&st->cmd_lock);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = st->पढ़ो_ec_sensors_data(indio_dev, 1 << idx, &data);
		अगर (ret < 0)
			अवरोध;
		ret = IIO_VAL_INT;
		*val = data;
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		WARN_ON(st->type != MOTIONSENSE_TYPE_ACCEL);
		*val = 0;
		*val2 = ACCEL_LEGACY_NSCALE;
		ret = IIO_VAL_INT_PLUS_न_अंकO;
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		/* Calibration not supported. */
		*val = 0;
		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = cros_ec_legacy_sample_freq[0];
		*val2 = cros_ec_legacy_sample_freq[1];
		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;
	शेष:
		ret = cros_ec_sensors_core_पढ़ो(st, chan, val, val2,
				mask);
		अवरोध;
	पूर्ण
	mutex_unlock(&st->cmd_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक cros_ec_accel_legacy_ग_लिखो(काष्ठा iio_dev *indio_dev,
				      काष्ठा iio_chan_spec स्थिर *chan,
				      पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	/*
	 * Do nothing but करोn't वापस an error code to allow calibration
	 * script to work.
	 */
	अगर (mask == IIO_CHAN_INFO_CALIBBIAS)
		वापस 0;

	वापस -EINVAL;
पूर्ण

/**
 * cros_ec_accel_legacy_पढ़ो_avail() - get available values
 * @indio_dev:		poपूर्णांकer to state inक्रमmation क्रम device
 * @chan:	channel specअगरication काष्ठाure table
 * @vals:	list of available values
 * @type:	type of data वापसed
 * @length:	number of data वापसed in the array
 * @mask:	specअगरies which values to be requested
 *
 * Return:	an error code or IIO_AVAIL_LIST
 */
अटल पूर्णांक cros_ec_accel_legacy_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
					   काष्ठा iio_chan_spec स्थिर *chan,
					   स्थिर पूर्णांक **vals,
					   पूर्णांक *type,
					   पूर्णांक *length,
					   दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*length = ARRAY_SIZE(cros_ec_legacy_sample_freq);
		*vals = cros_ec_legacy_sample_freq;
		*type = IIO_VAL_INT_PLUS_MICRO;
		वापस IIO_AVAIL_LIST;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info cros_ec_accel_legacy_info = अणु
	.पढ़ो_raw = &cros_ec_accel_legacy_पढ़ो,
	.ग_लिखो_raw = &cros_ec_accel_legacy_ग_लिखो,
	.पढ़ो_avail = &cros_ec_accel_legacy_पढ़ो_avail,
पूर्ण;

/*
 * Present the channel using HTML5 standard:
 * need to invert X and Y and invert some lid axis.
 */
#घोषणा CROS_EC_ACCEL_ROTATE_AXIS(_axis)				\
	((_axis) == CROS_EC_SENSOR_Z ? CROS_EC_SENSOR_Z :		\
	 ((_axis) == CROS_EC_SENSOR_X ? CROS_EC_SENSOR_Y :		\
	  CROS_EC_SENSOR_X))

#घोषणा CROS_EC_ACCEL_LEGACY_CHAN(_axis)				\
	अणु								\
		.type = IIO_ACCEL,					\
		.channel2 = IIO_MOD_X + (_axis),			\
		.modअगरied = 1,					        \
		.info_mask_separate =					\
			BIT(IIO_CHAN_INFO_RAW) |			\
			BIT(IIO_CHAN_INFO_CALIBBIAS),			\
		.info_mask_shared_by_all =				\
			BIT(IIO_CHAN_INFO_SCALE) |			\
			BIT(IIO_CHAN_INFO_SAMP_FREQ),			\
		.info_mask_shared_by_all_available =			\
			BIT(IIO_CHAN_INFO_SAMP_FREQ),			\
		.ext_info = cros_ec_sensors_ext_info,			\
		.scan_type = अणु						\
			.sign = 's',					\
			.realbits = CROS_EC_SENSOR_BITS,		\
			.storagebits = CROS_EC_SENSOR_BITS,		\
		पूर्ण,							\
		.scan_index = CROS_EC_ACCEL_ROTATE_AXIS(_axis),		\
	पूर्ण								\

अटल स्थिर काष्ठा iio_chan_spec cros_ec_accel_legacy_channels[] = अणु
		CROS_EC_ACCEL_LEGACY_CHAN(CROS_EC_SENSOR_X),
		CROS_EC_ACCEL_LEGACY_CHAN(CROS_EC_SENSOR_Y),
		CROS_EC_ACCEL_LEGACY_CHAN(CROS_EC_SENSOR_Z),
		IIO_CHAN_SOFT_TIMESTAMP(CROS_EC_SENSOR_MAX_AXIS)
पूर्ण;

अटल पूर्णांक cros_ec_accel_legacy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा iio_dev *indio_dev;
	काष्ठा cros_ec_sensors_core_state *state;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*state));
	अगर (!indio_dev)
		वापस -ENOMEM;

	ret = cros_ec_sensors_core_init(pdev, indio_dev, true,
					cros_ec_sensors_capture, शून्य);
	अगर (ret)
		वापस ret;

	indio_dev->info = &cros_ec_accel_legacy_info;
	state = iio_priv(indio_dev);

	अगर (state->ec->cmd_पढ़ोmem != शून्य)
		state->पढ़ो_ec_sensors_data = cros_ec_sensors_पढ़ो_lpc;
	अन्यथा
		state->पढ़ो_ec_sensors_data = cros_ec_accel_legacy_पढ़ो_cmd;

	indio_dev->channels = cros_ec_accel_legacy_channels;
	indio_dev->num_channels = ARRAY_SIZE(cros_ec_accel_legacy_channels);
	/* The lid sensor needs to be presented inverted. */
	अगर (state->loc == MOTIONSENSE_LOC_LID) अणु
		state->sign[CROS_EC_SENSOR_X] = -1;
		state->sign[CROS_EC_SENSOR_Z] = -1;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver cros_ec_accel_platक्रमm_driver = अणु
	.driver = अणु
		.name	= DRV_NAME,
	पूर्ण,
	.probe		= cros_ec_accel_legacy_probe,
पूर्ण;
module_platक्रमm_driver(cros_ec_accel_platक्रमm_driver);

MODULE_DESCRIPTION("ChromeOS EC legacy accelerometer driver");
MODULE_AUTHOR("Gwendal Grignou <gwendal@chromium.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
