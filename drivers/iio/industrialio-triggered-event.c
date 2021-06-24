<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Cogent Embedded, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/triggered_event.h>
#समावेश <linux/iio/trigger_consumer.h>

/**
 * iio_triggered_event_setup() - Setup pollfunc_event क्रम triggered event
 * @indio_dev:	IIO device काष्ठाure
 * @h:		Function which will be used as pollfunc_event top half
 * @thपढ़ो:	Function which will be used as pollfunc_event bottom half
 *
 * This function combines some common tasks which will normally be perक्रमmed
 * when setting up a triggered event. It will allocate the pollfunc_event and
 * set mode to use it क्रम triggered event.
 *
 * Beक्रमe calling this function the indio_dev काष्ठाure should alपढ़ोy be
 * completely initialized, but not yet रेजिस्टरed. In practice this means that
 * this function should be called right beक्रमe iio_device_रेजिस्टर().
 *
 * To मुक्त the resources allocated by this function call
 * iio_triggered_event_cleanup().
 */
पूर्णांक iio_triggered_event_setup(काष्ठा iio_dev *indio_dev,
			      irqवापस_t (*h)(पूर्णांक irq, व्योम *p),
			      irqवापस_t (*thपढ़ो)(पूर्णांक irq, व्योम *p))
अणु
	indio_dev->pollfunc_event = iio_alloc_pollfunc(h,
						       thपढ़ो,
						       IRQF_ONESHOT,
						       indio_dev,
						       "%s_consumer%d",
						       indio_dev->name,
						       indio_dev->id);
	अगर (indio_dev->pollfunc_event == शून्य)
		वापस -ENOMEM;

	/* Flag that events polling is possible */
	indio_dev->modes |= INDIO_EVENT_TRIGGERED;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(iio_triggered_event_setup);

/**
 * iio_triggered_event_cleanup() - Free resources allocated by iio_triggered_event_setup()
 * @indio_dev: IIO device काष्ठाure
 */
व्योम iio_triggered_event_cleanup(काष्ठा iio_dev *indio_dev)
अणु
	indio_dev->modes &= ~INDIO_EVENT_TRIGGERED;
	iio_dealloc_pollfunc(indio_dev->pollfunc_event);
पूर्ण
EXPORT_SYMBOL(iio_triggered_event_cleanup);

MODULE_AUTHOR("Vladimir Barinov");
MODULE_DESCRIPTION("IIO helper functions for setting up triggered events");
MODULE_LICENSE("GPL");
