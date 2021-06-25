<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2014, Samsung Electronics Co. Ltd. All Rights Reserved.
 */

#समावेश <linux/iio/common/ssp_sensors.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/kfअगरo_buf.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश "../common/ssp_sensors/ssp_iio_sensor.h"

#घोषणा SSP_CHANNEL_COUNT 3

#घोषणा SSP_GYROSCOPE_NAME "ssp-gyroscope"
अटल स्थिर अक्षर ssp_gyro_name[] = SSP_GYROSCOPE_NAME;

क्रमागत ssp_gyro_3d_channel अणु
	SSP_CHANNEL_SCAN_INDEX_X,
	SSP_CHANNEL_SCAN_INDEX_Y,
	SSP_CHANNEL_SCAN_INDEX_Z,
	SSP_CHANNEL_SCAN_INDEX_TIME,
पूर्ण;

अटल पूर्णांक ssp_gyro_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			     पूर्णांक *val2, दीर्घ mask)
अणु
	u32 t;
	काष्ठा ssp_data *data = dev_get_drvdata(indio_dev->dev.parent->parent);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		t = ssp_get_sensor_delay(data, SSP_GYROSCOPE_SENSOR);
		ssp_convert_to_freq(t, val, val2);
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ssp_gyro_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val,
			      पूर्णांक val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	काष्ठा ssp_data *data = dev_get_drvdata(indio_dev->dev.parent->parent);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = ssp_convert_to_समय(val, val2);
		ret = ssp_change_delay(data, SSP_GYROSCOPE_SENSOR, ret);
		अगर (ret < 0)
			dev_err(&indio_dev->dev, "gyro sensor enable fail\n");

		वापस ret;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info ssp_gyro_iio_info = अणु
	.पढ़ो_raw = &ssp_gyro_पढ़ो_raw,
	.ग_लिखो_raw = &ssp_gyro_ग_लिखो_raw,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ ssp_gyro_scan_mask[] = अणु 0x07, 0, पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ssp_gyro_channels[] = अणु
	SSP_CHANNEL_AG(IIO_ANGL_VEL, IIO_MOD_X, SSP_CHANNEL_SCAN_INDEX_X),
	SSP_CHANNEL_AG(IIO_ANGL_VEL, IIO_MOD_Y, SSP_CHANNEL_SCAN_INDEX_Y),
	SSP_CHANNEL_AG(IIO_ANGL_VEL, IIO_MOD_Z, SSP_CHANNEL_SCAN_INDEX_Z),
	SSP_CHAN_TIMESTAMP(SSP_CHANNEL_SCAN_INDEX_TIME),
पूर्ण;

अटल पूर्णांक ssp_process_gyro_data(काष्ठा iio_dev *indio_dev, व्योम *buf,
				 पूर्णांक64_t बारtamp)
अणु
	वापस ssp_common_process_data(indio_dev, buf, SSP_GYROSCOPE_SIZE,
				       बारtamp);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops ssp_gyro_buffer_ops = अणु
	.postenable = &ssp_common_buffer_postenable,
	.postdisable = &ssp_common_buffer_postdisable,
पूर्ण;

अटल पूर्णांक ssp_gyro_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev;
	काष्ठा ssp_sensor_data *spd;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*spd));
	अगर (!indio_dev)
		वापस -ENOMEM;

	spd = iio_priv(indio_dev);

	spd->process_data = ssp_process_gyro_data;
	spd->type = SSP_GYROSCOPE_SENSOR;

	indio_dev->name = ssp_gyro_name;
	indio_dev->info = &ssp_gyro_iio_info;
	indio_dev->channels = ssp_gyro_channels;
	indio_dev->num_channels = ARRAY_SIZE(ssp_gyro_channels);
	indio_dev->available_scan_masks = ssp_gyro_scan_mask;

	ret = devm_iio_kfअगरo_buffer_setup(&pdev->dev, indio_dev,
					  INDIO_BUFFER_SOFTWARE,
					  &ssp_gyro_buffer_ops);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, indio_dev);

	ret = devm_iio_device_रेजिस्टर(&pdev->dev, indio_dev);
	अगर (ret < 0)
		वापस ret;

	/* ssp रेजिस्टरing should be करोne after all iio setup */
	ssp_रेजिस्टर_consumer(indio_dev, SSP_GYROSCOPE_SENSOR);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ssp_gyro_driver = अणु
	.driver = अणु
		.name = SSP_GYROSCOPE_NAME,
	पूर्ण,
	.probe = ssp_gyro_probe,
पूर्ण;

module_platक्रमm_driver(ssp_gyro_driver);

MODULE_AUTHOR("Karol Wrona <k.wrona@samsung.com>");
MODULE_DESCRIPTION("Samsung sensorhub gyroscopes driver");
MODULE_LICENSE("GPL");
