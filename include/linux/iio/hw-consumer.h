<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Industrial I/O in kernel hardware consumer पूर्णांकerface
 *
 * Copyright 2017 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#अगर_अघोषित LINUX_IIO_HW_CONSUMER_H
#घोषणा LINUX_IIO_HW_CONSUMER_H

काष्ठा iio_hw_consumer;

काष्ठा iio_hw_consumer *iio_hw_consumer_alloc(काष्ठा device *dev);
व्योम iio_hw_consumer_मुक्त(काष्ठा iio_hw_consumer *hwc);
काष्ठा iio_hw_consumer *devm_iio_hw_consumer_alloc(काष्ठा device *dev);
पूर्णांक iio_hw_consumer_enable(काष्ठा iio_hw_consumer *hwc);
व्योम iio_hw_consumer_disable(काष्ठा iio_hw_consumer *hwc);

#पूर्ण_अगर
