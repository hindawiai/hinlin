<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2014, Samsung Electronics Co. Ltd. All Rights Reserved.
 */

#समावेश <linux/iio/common/ssp_sensors.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/kfअगरo_buf.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश "ssp_iio_sensor.h"

/**
 * ssp_common_buffer_postenable() - generic postenable callback क्रम ssp buffer
 *
 * @indio_dev:		iio device
 *
 * Returns 0 or negative value in हाल of error
 */
पूर्णांक ssp_common_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ssp_sensor_data *spd = iio_priv(indio_dev);
	काष्ठा ssp_data *data = dev_get_drvdata(indio_dev->dev.parent->parent);

	/* the allocation is made in post because scan size is known in this
	 * moment
	 * */
	spd->buffer = kदो_स्मृति(indio_dev->scan_bytes, GFP_KERNEL | GFP_DMA);
	अगर (!spd->buffer)
		वापस -ENOMEM;

	वापस ssp_enable_sensor(data, spd->type,
				 ssp_get_sensor_delay(data, spd->type));
पूर्ण
EXPORT_SYMBOL(ssp_common_buffer_postenable);

/**
 * ssp_common_buffer_postdisable() - generic postdisable callback क्रम ssp buffer
 *
 * @indio_dev:		iio device
 *
 * Returns 0 or negative value in हाल of error
 */
पूर्णांक ssp_common_buffer_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;
	काष्ठा ssp_sensor_data *spd = iio_priv(indio_dev);
	काष्ठा ssp_data *data = dev_get_drvdata(indio_dev->dev.parent->parent);

	ret = ssp_disable_sensor(data, spd->type);
	अगर (ret < 0)
		वापस ret;

	kमुक्त(spd->buffer);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ssp_common_buffer_postdisable);

/**
 * ssp_common_process_data() - Common process data callback क्रम ssp sensors
 *
 * @indio_dev:		iio device
 * @buf:		source buffer
 * @len:		sensor data length
 * @बारtamp:		प्रणाली बारtamp
 *
 * Returns 0 or negative value in हाल of error
 */
पूर्णांक ssp_common_process_data(काष्ठा iio_dev *indio_dev, व्योम *buf,
			    अचिन्हित पूर्णांक len, पूर्णांक64_t बारtamp)
अणु
	__le32 समय;
	पूर्णांक64_t calculated_समय = 0;
	काष्ठा ssp_sensor_data *spd = iio_priv(indio_dev);

	अगर (indio_dev->scan_bytes == 0)
		वापस 0;

	/*
	 * it always sends full set of samples, remember about available masks
	 */
	स_नकल(spd->buffer, buf, len);

	अगर (indio_dev->scan_बारtamp) अणु
		स_नकल(&समय, &((अक्षर *)buf)[len], SSP_TIME_SIZE);
		calculated_समय =
			बारtamp + (पूर्णांक64_t)le32_to_cpu(समय) * 1000000;
	पूर्ण

	वापस iio_push_to_buffers_with_बारtamp(indio_dev, spd->buffer,
						  calculated_समय);
पूर्ण
EXPORT_SYMBOL(ssp_common_process_data);

MODULE_AUTHOR("Karol Wrona <k.wrona@samsung.com>");
MODULE_DESCRIPTION("Samsung sensorhub commons");
MODULE_LICENSE("GPL");
