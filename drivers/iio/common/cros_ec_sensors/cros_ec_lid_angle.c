<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * cros_ec_lid_angle - Driver क्रम CrOS EC lid angle sensor.
 *
 * Copyright 2018 Google, Inc
 *
 * This driver uses the cros-ec पूर्णांकerface to communicate with the Chrome OS
 * EC about counter sensors. Counters are presented through
 * iio sysfs.
 */

#समावेश <linux/delay.h>
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
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा DRV_NAME "cros-ec-lid-angle"

/*
 * One channel क्रम the lid angle, the other क्रम बारtamp.
 */
अटल स्थिर काष्ठा iio_chan_spec cros_ec_lid_angle_channels[] = अणु
	अणु
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.scan_type.realbits = CROS_EC_SENSOR_BITS,
		.scan_type.storagebits = CROS_EC_SENSOR_BITS,
		.scan_type.sign = 'u',
		.type = IIO_ANGL
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(1)
पूर्ण;

/* State data क्रम ec_sensors iio driver. */
काष्ठा cros_ec_lid_angle_state अणु
	/* Shared by all sensors */
	काष्ठा cros_ec_sensors_core_state core;
पूर्ण;

अटल पूर्णांक cros_ec_sensors_पढ़ो_lid_angle(काष्ठा iio_dev *indio_dev,
					  अचिन्हित दीर्घ scan_mask, s16 *data)
अणु
	काष्ठा cros_ec_sensors_core_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	st->param.cmd = MOTIONSENSE_CMD_LID_ANGLE;
	ret = cros_ec_motion_send_host_cmd(st, माप(st->resp->lid_angle));
	अगर (ret) अणु
		dev_warn(&indio_dev->dev, "Unable to read lid angle\n");
		वापस ret;
	पूर्ण

	*data = st->resp->lid_angle.value;
	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_lid_angle_पढ़ो(काष्ठा iio_dev *indio_dev,
				    काष्ठा iio_chan_spec स्थिर *chan,
				    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा cros_ec_lid_angle_state *st = iio_priv(indio_dev);
	s16 data;
	पूर्णांक ret;

	mutex_lock(&st->core.cmd_lock);
	ret = cros_ec_sensors_पढ़ो_lid_angle(indio_dev, 1, &data);
	अगर (ret == 0) अणु
		*val = data;
		ret = IIO_VAL_INT;
	पूर्ण
	mutex_unlock(&st->core.cmd_lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info cros_ec_lid_angle_info = अणु
	.पढ़ो_raw = &cros_ec_lid_angle_पढ़ो,
पूर्ण;

अटल पूर्णांक cros_ec_lid_angle_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा iio_dev *indio_dev;
	काष्ठा cros_ec_lid_angle_state *state;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*state));
	अगर (!indio_dev)
		वापस -ENOMEM;

	ret = cros_ec_sensors_core_init(pdev, indio_dev, false, शून्य, शून्य);
	अगर (ret)
		वापस ret;

	indio_dev->info = &cros_ec_lid_angle_info;
	state = iio_priv(indio_dev);
	indio_dev->channels = cros_ec_lid_angle_channels;
	indio_dev->num_channels = ARRAY_SIZE(cros_ec_lid_angle_channels);

	state->core.पढ़ो_ec_sensors_data = cros_ec_sensors_पढ़ो_lid_angle;

	ret = devm_iio_triggered_buffer_setup(dev, indio_dev, शून्य,
			cros_ec_sensors_capture, शून्य);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id cros_ec_lid_angle_ids[] = अणु
	अणु
		.name = DRV_NAME,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, cros_ec_lid_angle_ids);

अटल काष्ठा platक्रमm_driver cros_ec_lid_angle_platक्रमm_driver = अणु
	.driver = अणु
		.name	= DRV_NAME,
	पूर्ण,
	.probe		= cros_ec_lid_angle_probe,
	.id_table	= cros_ec_lid_angle_ids,
पूर्ण;
module_platक्रमm_driver(cros_ec_lid_angle_platक्रमm_driver);

MODULE_DESCRIPTION("ChromeOS EC driver for reporting convertible lid angle.");
MODULE_LICENSE("GPL v2");
