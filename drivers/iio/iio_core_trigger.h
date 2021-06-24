<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

/* The industrial I/O core, trigger consumer handling functions
 *
 * Copyright (c) 2008 Jonathan Cameron
 */

#अगर_घोषित CONFIG_IIO_TRIGGER
/**
 * iio_device_रेजिस्टर_trigger_consumer() - set up an iio_dev to use triggers
 * @indio_dev: iio_dev associated with the device that will consume the trigger
 *
 * Return 0 अगर successful, negative otherwise
 **/
पूर्णांक iio_device_रेजिस्टर_trigger_consumer(काष्ठा iio_dev *indio_dev);

/**
 * iio_device_unरेजिस्टर_trigger_consumer() - reverse the registration process
 * @indio_dev: iio_dev associated with the device that consumed the trigger
 **/
व्योम iio_device_unरेजिस्टर_trigger_consumer(काष्ठा iio_dev *indio_dev);


पूर्णांक iio_trigger_attach_poll_func(काष्ठा iio_trigger *trig,
				 काष्ठा iio_poll_func *pf);
पूर्णांक iio_trigger_detach_poll_func(काष्ठा iio_trigger *trig,
				 काष्ठा iio_poll_func *pf);

#अन्यथा

/**
 * iio_device_रेजिस्टर_trigger_consumer() - set up an iio_dev to use triggers
 * @indio_dev: iio_dev associated with the device that will consume the trigger
 **/
अटल अंतरभूत पूर्णांक iio_device_रेजिस्टर_trigger_consumer(काष्ठा iio_dev *indio_dev)
अणु
	वापस 0;
पूर्ण

/**
 * iio_device_unरेजिस्टर_trigger_consumer() - reverse the registration process
 * @indio_dev: iio_dev associated with the device that consumed the trigger
 **/
अटल अंतरभूत व्योम iio_device_unरेजिस्टर_trigger_consumer(काष्ठा iio_dev *indio_dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक iio_trigger_attach_poll_func(काष्ठा iio_trigger *trig,
					       काष्ठा iio_poll_func *pf)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक iio_trigger_detach_poll_func(काष्ठा iio_trigger *trig,
					       काष्ठा iio_poll_func *pf)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_TRIGGER_CONSUMER */
