<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
 /*
 * Copyright (c) 2012 Analog Devices, Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/buffer_impl.h>
#समावेश <linux/iio/kfअगरo_buf.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>

/**
 * iio_triggered_buffer_setup_ext() - Setup triggered buffer and pollfunc
 * @indio_dev:		IIO device काष्ठाure
 * @h:			Function which will be used as pollfunc top half
 * @thपढ़ो:		Function which will be used as pollfunc bottom half
 * @setup_ops:		Buffer setup functions to use क्रम this device.
 *			If शून्य the शेष setup functions क्रम triggered
 *			buffers will be used.
 * @buffer_attrs:	Extra sysfs buffer attributes क्रम this IIO buffer
 *
 * This function combines some common tasks which will normally be perक्रमmed
 * when setting up a triggered buffer. It will allocate the buffer and the
 * pollfunc.
 *
 * Beक्रमe calling this function the indio_dev काष्ठाure should alपढ़ोy be
 * completely initialized, but not yet रेजिस्टरed. In practice this means that
 * this function should be called right beक्रमe iio_device_रेजिस्टर().
 *
 * To मुक्त the resources allocated by this function call
 * iio_triggered_buffer_cleanup().
 */
पूर्णांक iio_triggered_buffer_setup_ext(काष्ठा iio_dev *indio_dev,
	irqवापस_t (*h)(पूर्णांक irq, व्योम *p),
	irqवापस_t (*thपढ़ो)(पूर्णांक irq, व्योम *p),
	स्थिर काष्ठा iio_buffer_setup_ops *setup_ops,
	स्थिर काष्ठा attribute **buffer_attrs)
अणु
	काष्ठा iio_buffer *buffer;
	पूर्णांक ret;

	buffer = iio_kfअगरo_allocate();
	अगर (!buffer) अणु
		ret = -ENOMEM;
		जाओ error_ret;
	पूर्ण

	indio_dev->pollfunc = iio_alloc_pollfunc(h,
						 thपढ़ो,
						 IRQF_ONESHOT,
						 indio_dev,
						 "%s_consumer%d",
						 indio_dev->name,
						 indio_dev->id);
	अगर (indio_dev->pollfunc == शून्य) अणु
		ret = -ENOMEM;
		जाओ error_kfअगरo_मुक्त;
	पूर्ण

	/* Ring buffer functions - here trigger setup related */
	indio_dev->setup_ops = setup_ops;

	/* Flag that polled ring buffering is possible */
	indio_dev->modes |= INDIO_BUFFER_TRIGGERED;

	buffer->attrs = buffer_attrs;

	ret = iio_device_attach_buffer(indio_dev, buffer);
	अगर (ret < 0)
		जाओ error_dealloc_pollfunc;

	वापस 0;

error_dealloc_pollfunc:
	iio_dealloc_pollfunc(indio_dev->pollfunc);
error_kfअगरo_मुक्त:
	iio_kfअगरo_मुक्त(buffer);
error_ret:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(iio_triggered_buffer_setup_ext);

/**
 * iio_triggered_buffer_cleanup() - Free resources allocated by iio_triggered_buffer_setup_ext()
 * @indio_dev: IIO device काष्ठाure
 */
व्योम iio_triggered_buffer_cleanup(काष्ठा iio_dev *indio_dev)
अणु
	iio_dealloc_pollfunc(indio_dev->pollfunc);
	iio_kfअगरo_मुक्त(indio_dev->buffer);
पूर्ण
EXPORT_SYMBOL(iio_triggered_buffer_cleanup);

अटल व्योम devm_iio_triggered_buffer_clean(काष्ठा device *dev, व्योम *res)
अणु
	iio_triggered_buffer_cleanup(*(काष्ठा iio_dev **)res);
पूर्ण

पूर्णांक devm_iio_triggered_buffer_setup_ext(काष्ठा device *dev,
					काष्ठा iio_dev *indio_dev,
					irqवापस_t (*h)(पूर्णांक irq, व्योम *p),
					irqवापस_t (*thपढ़ो)(पूर्णांक irq, व्योम *p),
					स्थिर काष्ठा iio_buffer_setup_ops *ops,
					स्थिर काष्ठा attribute **buffer_attrs)
अणु
	काष्ठा iio_dev **ptr;
	पूर्णांक ret;

	ptr = devres_alloc(devm_iio_triggered_buffer_clean, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	*ptr = indio_dev;

	ret = iio_triggered_buffer_setup_ext(indio_dev, h, thपढ़ो, ops,
					     buffer_attrs);
	अगर (!ret)
		devres_add(dev, ptr);
	अन्यथा
		devres_मुक्त(ptr);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_iio_triggered_buffer_setup_ext);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("IIO helper functions for setting up triggered buffers");
MODULE_LICENSE("GPL");
