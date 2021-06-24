<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cros_ec_sensors - Driver क्रम Chrome OS Embedded Controller sensors.
 *
 * Copyright (C) 2016 Google, Inc
 *
 * This driver uses the cros-ec पूर्णांकerface to communicate with the Chrome OS
 * EC about sensors data. Data access is presented through iio sysfs.
 */

#समावेश <linux/device.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/common/cros_ec_sensors_core.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/kfअगरo_buf.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा CROS_EC_SENSORS_MAX_CHANNELS 4

/* State data क्रम ec_sensors iio driver. */
काष्ठा cros_ec_sensors_state अणु
	/* Shared by all sensors */
	काष्ठा cros_ec_sensors_core_state core;

	काष्ठा iio_chan_spec channels[CROS_EC_SENSORS_MAX_CHANNELS];
पूर्ण;

अटल पूर्णांक cros_ec_sensors_पढ़ो(काष्ठा iio_dev *indio_dev,
			  काष्ठा iio_chan_spec स्थिर *chan,
			  पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा cros_ec_sensors_state *st = iio_priv(indio_dev);
	s16 data = 0;
	s64 val64;
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक idx = chan->scan_index;

	mutex_lock(&st->core.cmd_lock);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = st->core.पढ़ो_ec_sensors_data(indio_dev, 1 << idx, &data);
		अगर (ret < 0)
			अवरोध;
		ret = IIO_VAL_INT;
		*val = data;
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		st->core.param.cmd = MOTIONSENSE_CMD_SENSOR_OFFSET;
		st->core.param.sensor_offset.flags = 0;

		ret = cros_ec_motion_send_host_cmd(&st->core, 0);
		अगर (ret < 0)
			अवरोध;

		/* Save values */
		क्रम (i = CROS_EC_SENSOR_X; i < CROS_EC_SENSOR_MAX_AXIS; i++)
			st->core.calib[i].offset =
				st->core.resp->sensor_offset.offset[i];
		ret = IIO_VAL_INT;
		*val = st->core.calib[idx].offset;
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBSCALE:
		st->core.param.cmd = MOTIONSENSE_CMD_SENSOR_SCALE;
		st->core.param.sensor_offset.flags = 0;

		ret = cros_ec_motion_send_host_cmd(&st->core, 0);
		अगर (ret == -EPROTO || ret == -EOPNOTSUPP) अणु
			/* Reading calibscale is not supported on older EC. */
			*val = 1;
			*val2 = 0;
			ret = IIO_VAL_INT_PLUS_MICRO;
			अवरोध;
		पूर्ण अन्यथा अगर (ret) अणु
			अवरोध;
		पूर्ण

		/* Save values */
		क्रम (i = CROS_EC_SENSOR_X; i < CROS_EC_SENSOR_MAX_AXIS; i++)
			st->core.calib[i].scale =
				st->core.resp->sensor_scale.scale[i];

		*val = st->core.calib[idx].scale >> 15;
		*val2 = ((st->core.calib[idx].scale & 0x7FFF) * 1000000LL) /
			MOTION_SENSE_DEFAULT_SCALE;
		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		st->core.param.cmd = MOTIONSENSE_CMD_SENSOR_RANGE;
		st->core.param.sensor_range.data = EC_MOTION_SENSE_NO_VALUE;

		ret = cros_ec_motion_send_host_cmd(&st->core, 0);
		अगर (ret < 0)
			अवरोध;

		val64 = st->core.resp->sensor_range.ret;
		चयन (st->core.type) अणु
		हाल MOTIONSENSE_TYPE_ACCEL:
			/*
			 * EC वापसs data in g, iio exepects m/s^2.
			 * Do not use IIO_G_TO_M_S_2 to aव्योम precision loss.
			 */
			*val = भाग_s64(val64 * 980665, 10);
			*val2 = 10000 << (CROS_EC_SENSOR_BITS - 1);
			ret = IIO_VAL_FRACTIONAL;
			अवरोध;
		हाल MOTIONSENSE_TYPE_GYRO:
			/*
			 * EC वापसs data in dps, iio expects rad/s.
			 * Do not use IIO_DEGREE_TO_RAD to aव्योम precision
			 * loss. Round to the nearest पूर्णांकeger.
			 */
			*val = 0;
			*val2 = भाग_s64(val64 * 3141592653ULL,
					180 << (CROS_EC_SENSOR_BITS - 1));
			ret = IIO_VAL_INT_PLUS_न_अंकO;
			अवरोध;
		हाल MOTIONSENSE_TYPE_MAG:
			/*
			 * EC वापसs data in 16LSB / uT,
			 * iio expects Gauss
			 */
			*val = val64;
			*val2 = 100 << (CROS_EC_SENSOR_BITS - 1);
			ret = IIO_VAL_FRACTIONAL;
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		ret = cros_ec_sensors_core_पढ़ो(&st->core, chan, val, val2,
						mask);
		अवरोध;
	पूर्ण
	mutex_unlock(&st->core.cmd_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक cros_ec_sensors_ग_लिखो(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा cros_ec_sensors_state *st = iio_priv(indio_dev);
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक idx = chan->scan_index;

	mutex_lock(&st->core.cmd_lock);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_CALIBBIAS:
		st->core.calib[idx].offset = val;

		/* Send to EC क्रम each axis, even अगर not complete */
		st->core.param.cmd = MOTIONSENSE_CMD_SENSOR_OFFSET;
		st->core.param.sensor_offset.flags =
			MOTION_SENSE_SET_OFFSET;
		क्रम (i = CROS_EC_SENSOR_X; i < CROS_EC_SENSOR_MAX_AXIS; i++)
			st->core.param.sensor_offset.offset[i] =
				st->core.calib[i].offset;
		st->core.param.sensor_offset.temp =
			EC_MOTION_SENSE_INVALID_CALIB_TEMP;

		ret = cros_ec_motion_send_host_cmd(&st->core, 0);
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBSCALE:
		st->core.calib[idx].scale = val;
		/* Send to EC क्रम each axis, even अगर not complete */

		st->core.param.cmd = MOTIONSENSE_CMD_SENSOR_SCALE;
		st->core.param.sensor_offset.flags =
			MOTION_SENSE_SET_OFFSET;
		क्रम (i = CROS_EC_SENSOR_X; i < CROS_EC_SENSOR_MAX_AXIS; i++)
			st->core.param.sensor_scale.scale[i] =
				st->core.calib[i].scale;
		st->core.param.sensor_scale.temp =
			EC_MOTION_SENSE_INVALID_CALIB_TEMP;

		ret = cros_ec_motion_send_host_cmd(&st->core, 0);
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (st->core.type == MOTIONSENSE_TYPE_MAG) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		st->core.param.cmd = MOTIONSENSE_CMD_SENSOR_RANGE;
		st->core.param.sensor_range.data = val;

		/* Always roundup, so caller माला_लो at least what it asks क्रम. */
		st->core.param.sensor_range.roundup = 1;

		ret = cros_ec_motion_send_host_cmd(&st->core, 0);
		अगर (ret == 0) अणु
			st->core.range_updated = true;
			st->core.curr_range = val;
		पूर्ण
		अवरोध;
	शेष:
		ret = cros_ec_sensors_core_ग_लिखो(
				&st->core, chan, val, val2, mask);
		अवरोध;
	पूर्ण

	mutex_unlock(&st->core.cmd_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info ec_sensors_info = अणु
	.पढ़ो_raw = &cros_ec_sensors_पढ़ो,
	.ग_लिखो_raw = &cros_ec_sensors_ग_लिखो,
	.पढ़ो_avail = &cros_ec_sensors_core_पढ़ो_avail,
पूर्ण;

अटल पूर्णांक cros_ec_sensors_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा iio_dev *indio_dev;
	काष्ठा cros_ec_sensors_state *state;
	काष्ठा iio_chan_spec *channel;
	पूर्णांक ret, i;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*state));
	अगर (!indio_dev)
		वापस -ENOMEM;

	ret = cros_ec_sensors_core_init(pdev, indio_dev, true,
					cros_ec_sensors_capture,
					cros_ec_sensors_push_data);
	अगर (ret)
		वापस ret;

	indio_dev->info = &ec_sensors_info;
	state = iio_priv(indio_dev);
	क्रम (channel = state->channels, i = CROS_EC_SENSOR_X;
	     i < CROS_EC_SENSOR_MAX_AXIS; i++, channel++) अणु
		/* Common part */
		channel->info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_CALIBBIAS) |
			BIT(IIO_CHAN_INFO_CALIBSCALE);
		channel->info_mask_shared_by_all =
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_SAMP_FREQ);
		channel->info_mask_shared_by_all_available =
			BIT(IIO_CHAN_INFO_SAMP_FREQ);
		channel->scan_type.realbits = CROS_EC_SENSOR_BITS;
		channel->scan_type.storagebits = CROS_EC_SENSOR_BITS;
		channel->scan_index = i;
		channel->ext_info = cros_ec_sensors_ext_info;
		channel->modअगरied = 1;
		channel->channel2 = IIO_MOD_X + i;
		channel->scan_type.sign = 's';

		/* Sensor specअगरic */
		चयन (state->core.type) अणु
		हाल MOTIONSENSE_TYPE_ACCEL:
			channel->type = IIO_ACCEL;
			अवरोध;
		हाल MOTIONSENSE_TYPE_GYRO:
			channel->type = IIO_ANGL_VEL;
			अवरोध;
		हाल MOTIONSENSE_TYPE_MAG:
			channel->type = IIO_MAGN;
			अवरोध;
		शेष:
			dev_err(&pdev->dev, "Unknown motion sensor\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Timestamp */
	channel->type = IIO_TIMESTAMP;
	channel->channel = -1;
	channel->scan_index = CROS_EC_SENSOR_MAX_AXIS;
	channel->scan_type.sign = 's';
	channel->scan_type.realbits = 64;
	channel->scan_type.storagebits = 64;

	indio_dev->channels = state->channels;
	indio_dev->num_channels = CROS_EC_SENSORS_MAX_CHANNELS;

	/* There is only enough room क्रम accel and gyro in the io space */
	अगर ((state->core.ec->cmd_पढ़ोmem != शून्य) &&
	    (state->core.type != MOTIONSENSE_TYPE_MAG))
		state->core.पढ़ो_ec_sensors_data = cros_ec_sensors_पढ़ो_lpc;
	अन्यथा
		state->core.पढ़ो_ec_sensors_data = cros_ec_sensors_पढ़ो_cmd;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id cros_ec_sensors_ids[] = अणु
	अणु
		.name = "cros-ec-accel",
	पूर्ण,
	अणु
		.name = "cros-ec-gyro",
	पूर्ण,
	अणु
		.name = "cros-ec-mag",
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, cros_ec_sensors_ids);

अटल काष्ठा platक्रमm_driver cros_ec_sensors_platक्रमm_driver = अणु
	.driver = अणु
		.name	= "cros-ec-sensors",
		.pm	= &cros_ec_sensors_pm_ops,
	पूर्ण,
	.probe		= cros_ec_sensors_probe,
	.id_table	= cros_ec_sensors_ids,
पूर्ण;
module_platक्रमm_driver(cros_ec_sensors_platक्रमm_driver);

MODULE_DESCRIPTION("ChromeOS EC 3-axis sensors driver");
MODULE_LICENSE("GPL v2");
