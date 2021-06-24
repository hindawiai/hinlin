<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cros_ec_light_prox - Driver क्रम light and prox sensors behing CrosEC.
 *
 * Copyright (C) 2017 Google, Inc
 */

#समावेश <linux/device.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/common/cros_ec_sensors_core.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/kfअगरo_buf.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

/*
 * We only represent one entry क्रम light or proximity. EC is merging dअगरferent
 * light sensors to वापस the what the eye would see. For proximity, we
 * currently support only one light source.
 */
#घोषणा CROS_EC_LIGHT_PROX_MAX_CHANNELS (1 + 1)

/* State data क्रम ec_sensors iio driver. */
काष्ठा cros_ec_light_prox_state अणु
	/* Shared by all sensors */
	काष्ठा cros_ec_sensors_core_state core;

	काष्ठा iio_chan_spec channels[CROS_EC_LIGHT_PROX_MAX_CHANNELS];
पूर्ण;

अटल पूर्णांक cros_ec_light_prox_पढ़ो(काष्ठा iio_dev *indio_dev,
				   काष्ठा iio_chan_spec स्थिर *chan,
				   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा cros_ec_light_prox_state *st = iio_priv(indio_dev);
	u16 data = 0;
	s64 val64;
	पूर्णांक ret;
	पूर्णांक idx = chan->scan_index;

	mutex_lock(&st->core.cmd_lock);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (chan->type == IIO_PROXIMITY) अणु
			ret = cros_ec_sensors_पढ़ो_cmd(indio_dev, 1 << idx,
						     (s16 *)&data);
			अगर (ret)
				अवरोध;
			*val = data;
			ret = IIO_VAL_INT;
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_PROCESSED:
		अगर (chan->type == IIO_LIGHT) अणु
			ret = cros_ec_sensors_पढ़ो_cmd(indio_dev, 1 << idx,
						     (s16 *)&data);
			अगर (ret)
				अवरोध;
			/*
			 * The data coming from the light sensor is
			 * pre-processed and represents the ambient light
			 * illuminance पढ़ोing expressed in lux.
			 */
			*val = data;
			ret = IIO_VAL_INT;
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		st->core.param.cmd = MOTIONSENSE_CMD_SENSOR_OFFSET;
		st->core.param.sensor_offset.flags = 0;

		ret = cros_ec_motion_send_host_cmd(&st->core, 0);
		अगर (ret)
			अवरोध;

		/* Save values */
		st->core.calib[0].offset =
			st->core.resp->sensor_offset.offset[0];

		*val = st->core.calib[idx].offset;
		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBSCALE:
		/*
		 * RANGE is used क्रम calibration
		 * scale is a number x.y, where x is coded on 16 bits,
		 * y coded on 16 bits, between 0 and 9999.
		 */
		st->core.param.cmd = MOTIONSENSE_CMD_SENSOR_RANGE;
		st->core.param.sensor_range.data = EC_MOTION_SENSE_NO_VALUE;

		ret = cros_ec_motion_send_host_cmd(&st->core, 0);
		अगर (ret)
			अवरोध;

		val64 = st->core.resp->sensor_range.ret;
		*val = val64 >> 16;
		*val2 = (val64 & 0xffff) * 100;
		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;
	शेष:
		ret = cros_ec_sensors_core_पढ़ो(&st->core, chan, val, val2,
						mask);
		अवरोध;
	पूर्ण

	mutex_unlock(&st->core.cmd_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक cros_ec_light_prox_ग_लिखो(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा cros_ec_light_prox_state *st = iio_priv(indio_dev);
	पूर्णांक ret;
	पूर्णांक idx = chan->scan_index;

	mutex_lock(&st->core.cmd_lock);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_CALIBBIAS:
		st->core.calib[idx].offset = val;
		/* Send to EC क्रम each axis, even अगर not complete */
		st->core.param.cmd = MOTIONSENSE_CMD_SENSOR_OFFSET;
		st->core.param.sensor_offset.flags = MOTION_SENSE_SET_OFFSET;
		st->core.param.sensor_offset.offset[0] =
			st->core.calib[0].offset;
		st->core.param.sensor_offset.temp =
					EC_MOTION_SENSE_INVALID_CALIB_TEMP;
		ret = cros_ec_motion_send_host_cmd(&st->core, 0);
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBSCALE:
		st->core.param.cmd = MOTIONSENSE_CMD_SENSOR_RANGE;
		st->core.curr_range = (val << 16) | (val2 / 100);
		st->core.param.sensor_range.data = st->core.curr_range;
		ret = cros_ec_motion_send_host_cmd(&st->core, 0);
		अगर (ret == 0)
			st->core.range_updated = true;
		अवरोध;
	शेष:
		ret = cros_ec_sensors_core_ग_लिखो(&st->core, chan, val, val2,
						 mask);
		अवरोध;
	पूर्ण

	mutex_unlock(&st->core.cmd_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info cros_ec_light_prox_info = अणु
	.पढ़ो_raw = &cros_ec_light_prox_पढ़ो,
	.ग_लिखो_raw = &cros_ec_light_prox_ग_लिखो,
	.पढ़ो_avail = &cros_ec_sensors_core_पढ़ो_avail,
पूर्ण;

अटल पूर्णांक cros_ec_light_prox_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा iio_dev *indio_dev;
	काष्ठा cros_ec_light_prox_state *state;
	काष्ठा iio_chan_spec *channel;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*state));
	अगर (!indio_dev)
		वापस -ENOMEM;

	ret = cros_ec_sensors_core_init(pdev, indio_dev, true,
					cros_ec_sensors_capture,
					cros_ec_sensors_push_data);
	अगर (ret)
		वापस ret;

	indio_dev->info = &cros_ec_light_prox_info;
	state = iio_priv(indio_dev);
	state->core.type = state->core.resp->info.type;
	state->core.loc = state->core.resp->info.location;
	channel = state->channels;

	/* Common part */
	channel->info_mask_shared_by_all =
		BIT(IIO_CHAN_INFO_SAMP_FREQ);
	channel->info_mask_shared_by_all_available =
		BIT(IIO_CHAN_INFO_SAMP_FREQ);
	channel->scan_type.realbits = CROS_EC_SENSOR_BITS;
	channel->scan_type.storagebits = CROS_EC_SENSOR_BITS;
	channel->scan_type.shअगरt = 0;
	channel->scan_index = 0;
	channel->ext_info = cros_ec_sensors_ext_info;
	channel->scan_type.sign = 'u';

	/* Sensor specअगरic */
	चयन (state->core.type) अणु
	हाल MOTIONSENSE_TYPE_LIGHT:
		channel->type = IIO_LIGHT;
		channel->info_mask_separate =
			BIT(IIO_CHAN_INFO_PROCESSED) |
			BIT(IIO_CHAN_INFO_CALIBBIAS) |
			BIT(IIO_CHAN_INFO_CALIBSCALE);
		अवरोध;
	हाल MOTIONSENSE_TYPE_PROX:
		channel->type = IIO_PROXIMITY;
		channel->info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_CALIBBIAS) |
			BIT(IIO_CHAN_INFO_CALIBSCALE);
		अवरोध;
	शेष:
		dev_warn(dev, "Unknown motion sensor\n");
		वापस -EINVAL;
	पूर्ण

	/* Timestamp */
	channel++;
	channel->type = IIO_TIMESTAMP;
	channel->channel = -1;
	channel->scan_index = 1;
	channel->scan_type.sign = 's';
	channel->scan_type.realbits = 64;
	channel->scan_type.storagebits = 64;

	indio_dev->channels = state->channels;

	indio_dev->num_channels = CROS_EC_LIGHT_PROX_MAX_CHANNELS;

	state->core.पढ़ो_ec_sensors_data = cros_ec_sensors_पढ़ो_cmd;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id cros_ec_light_prox_ids[] = अणु
	अणु
		.name = "cros-ec-prox",
	पूर्ण,
	अणु
		.name = "cros-ec-light",
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, cros_ec_light_prox_ids);

अटल काष्ठा platक्रमm_driver cros_ec_light_prox_platक्रमm_driver = अणु
	.driver = अणु
		.name	= "cros-ec-light-prox",
		.pm	= &cros_ec_sensors_pm_ops,
	पूर्ण,
	.probe		= cros_ec_light_prox_probe,
	.id_table	= cros_ec_light_prox_ids,
पूर्ण;
module_platक्रमm_driver(cros_ec_light_prox_platक्रमm_driver);

MODULE_DESCRIPTION("ChromeOS EC light/proximity sensors driver");
MODULE_LICENSE("GPL v2");
