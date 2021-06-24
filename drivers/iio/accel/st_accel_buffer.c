<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics accelerometers driver
 *
 * Copyright 2012-2013 STMicroelectronics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#समावेश <linux/iio/common/st_sensors.h>
#समावेश "st_accel.h"

पूर्णांक st_accel_trig_set_state(काष्ठा iio_trigger *trig, bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);

	वापस st_sensors_set_dataपढ़ोy_irq(indio_dev, state);
पूर्ण

अटल पूर्णांक st_accel_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक err;

	err = st_sensors_set_axis_enable(indio_dev, indio_dev->active_scan_mask[0]);
	अगर (err < 0)
		वापस err;

	err = st_sensors_set_enable(indio_dev, true);
	अगर (err < 0)
		जाओ st_accel_buffer_enable_all_axis;

	वापस 0;

st_accel_buffer_enable_all_axis:
	st_sensors_set_axis_enable(indio_dev, ST_SENSORS_ENABLE_ALL_AXIS);
	वापस err;
पूर्ण

अटल पूर्णांक st_accel_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक err;

	err = st_sensors_set_enable(indio_dev, false);
	अगर (err < 0)
		वापस err;

	वापस st_sensors_set_axis_enable(indio_dev,
					  ST_SENSORS_ENABLE_ALL_AXIS);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops st_accel_buffer_setup_ops = अणु
	.postenable = &st_accel_buffer_postenable,
	.predisable = &st_accel_buffer_predisable,
पूर्ण;

पूर्णांक st_accel_allocate_ring(काष्ठा iio_dev *indio_dev)
अणु
	वापस iio_triggered_buffer_setup(indio_dev, शून्य,
		&st_sensors_trigger_handler, &st_accel_buffer_setup_ops);
पूर्ण

व्योम st_accel_deallocate_ring(काष्ठा iio_dev *indio_dev)
अणु
	iio_triggered_buffer_cleanup(indio_dev);
पूर्ण

MODULE_AUTHOR("Denis Ciocca <denis.ciocca@st.com>");
MODULE_DESCRIPTION("STMicroelectronics accelerometers buffer");
MODULE_LICENSE("GPL v2");
