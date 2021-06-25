<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics magnetometers driver
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
#समावेश "st_magn.h"

पूर्णांक st_magn_trig_set_state(काष्ठा iio_trigger *trig, bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);

	वापस st_sensors_set_dataपढ़ोy_irq(indio_dev, state);
पूर्ण

अटल पूर्णांक st_magn_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	वापस st_sensors_set_enable(indio_dev, true);
पूर्ण

अटल पूर्णांक st_magn_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	वापस st_sensors_set_enable(indio_dev, false);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops st_magn_buffer_setup_ops = अणु
	.postenable = &st_magn_buffer_postenable,
	.predisable = &st_magn_buffer_predisable,
पूर्ण;

पूर्णांक st_magn_allocate_ring(काष्ठा iio_dev *indio_dev)
अणु
	वापस iio_triggered_buffer_setup(indio_dev, शून्य,
		&st_sensors_trigger_handler, &st_magn_buffer_setup_ops);
पूर्ण

व्योम st_magn_deallocate_ring(काष्ठा iio_dev *indio_dev)
अणु
	iio_triggered_buffer_cleanup(indio_dev);
पूर्ण

MODULE_AUTHOR("Denis Ciocca <denis.ciocca@st.com>");
MODULE_DESCRIPTION("STMicroelectronics magnetometers buffer");
MODULE_LICENSE("GPL v2");
