<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* The industrial I/O core, trigger consumer functions
 *
 * Copyright (c) 2008-2011 Jonathan Cameron
 */

#अगर_अघोषित __LINUX_IIO_TRIGGER_CONSUMER_H__
#घोषणा __LINUX_IIO_TRIGGER_CONSUMER_H__

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>

काष्ठा iio_dev;
काष्ठा iio_trigger;

/**
 * काष्ठा iio_poll_func - poll function pair
 *
 * @indio_dev:			data specअगरic to device (passed पूर्णांकo poll func)
 * @h:				the function that is actually run on trigger
 * @thपढ़ो:			thपढ़ोed पूर्णांकerrupt part
 * @type:			the type of पूर्णांकerrupt (basically अगर oneshot)
 * @name:			name used to identअगरy the trigger consumer.
 * @irq:			the corresponding irq as allocated from the
 *				trigger pool
 * @बारtamp:			some devices need a बारtamp grabbed as soon
 *				as possible after the trigger - hence handler
 *				passes it via here.
 **/
काष्ठा iio_poll_func अणु
	काष्ठा iio_dev *indio_dev;
	irqवापस_t (*h)(पूर्णांक irq, व्योम *p);
	irqवापस_t (*thपढ़ो)(पूर्णांक irq, व्योम *p);
	पूर्णांक type;
	अक्षर *name;
	पूर्णांक irq;
	s64 बारtamp;
पूर्ण;


__म_लिखो(5, 6) काष्ठा iio_poll_func
*iio_alloc_pollfunc(irqवापस_t (*h)(पूर्णांक irq, व्योम *p),
		    irqवापस_t (*thपढ़ो)(पूर्णांक irq, व्योम *p),
		    पूर्णांक type,
		    काष्ठा iio_dev *indio_dev,
		    स्थिर अक्षर *fmt,
		    ...);
व्योम iio_dealloc_pollfunc(काष्ठा iio_poll_func *pf);
irqवापस_t iio_pollfunc_store_समय(पूर्णांक irq, व्योम *p);

व्योम iio_trigger_notअगरy_करोne(काष्ठा iio_trigger *trig);

#पूर्ण_अगर
