<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* The industrial I/O core, trigger handling functions
 *
 * Copyright (c) 2008 Jonathan Cameron
 */
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/atomic.h>

#अगर_अघोषित _IIO_TRIGGER_H_
#घोषणा _IIO_TRIGGER_H_

#अगर_घोषित CONFIG_IIO_TRIGGER
काष्ठा iio_subirq अणु
	bool enabled;
पूर्ण;

काष्ठा iio_dev;
काष्ठा iio_trigger;

/**
 * काष्ठा iio_trigger_ops - operations काष्ठाure क्रम an iio_trigger.
 * @set_trigger_state:	चयन on/off the trigger on demand
 * @reenable:		function to reenable the trigger when the
 *			use count is zero (may be शून्य)
 * @validate_device:	function to validate the device when the
 *			current trigger माला_लो changed.
 *
 * This is typically अटल स्थिर within a driver and shared by
 * instances of a given device.
 **/
काष्ठा iio_trigger_ops अणु
	पूर्णांक (*set_trigger_state)(काष्ठा iio_trigger *trig, bool state);
	व्योम (*reenable)(काष्ठा iio_trigger *trig);
	पूर्णांक (*validate_device)(काष्ठा iio_trigger *trig,
			       काष्ठा iio_dev *indio_dev);
पूर्ण;


/**
 * काष्ठा iio_trigger - industrial I/O trigger device
 * @ops:		[DRIVER] operations काष्ठाure
 * @owner:		[INTERN] owner of this driver module
 * @id:			[INTERN] unique id number
 * @name:		[DRIVER] unique name
 * @dev:		[DRIVER] associated device (अगर relevant)
 * @list:		[INTERN] used in मुख्यtenance of global trigger list
 * @alloc_list:		[DRIVER] used क्रम driver specअगरic trigger list
 * @use_count:		[INTERN] use count क्रम the trigger.
 * @subirq_chip:	[INTERN] associate 'virtual' irq chip.
 * @subirq_base:	[INTERN] base number क्रम irqs provided by trigger.
 * @subirqs:		[INTERN] inक्रमmation about the 'child' irqs.
 * @pool:		[INTERN] biपंचांगap of irqs currently in use.
 * @pool_lock:		[INTERN] protection of the irq pool.
 * @attached_own_device:[INTERN] अगर we are using our own device as trigger,
 *			i.e. अगर we रेजिस्टरed a poll function to the same
 *			device as the one providing the trigger.
 **/
काष्ठा iio_trigger अणु
	स्थिर काष्ठा iio_trigger_ops	*ops;
	काष्ठा module			*owner;
	पूर्णांक				id;
	स्थिर अक्षर			*name;
	काष्ठा device			dev;

	काष्ठा list_head		list;
	काष्ठा list_head		alloc_list;
	atomic_t			use_count;

	काष्ठा irq_chip			subirq_chip;
	पूर्णांक				subirq_base;

	काष्ठा iio_subirq subirqs[CONFIG_IIO_CONSUMERS_PER_TRIGGER];
	अचिन्हित दीर्घ pool[BITS_TO_LONGS(CONFIG_IIO_CONSUMERS_PER_TRIGGER)];
	काष्ठा mutex			pool_lock;
	bool				attached_own_device;
पूर्ण;


अटल अंतरभूत काष्ठा iio_trigger *to_iio_trigger(काष्ठा device *d)
अणु
	वापस container_of(d, काष्ठा iio_trigger, dev);
पूर्ण

अटल अंतरभूत व्योम iio_trigger_put(काष्ठा iio_trigger *trig)
अणु
	module_put(trig->owner);
	put_device(&trig->dev);
पूर्ण

अटल अंतरभूत काष्ठा iio_trigger *iio_trigger_get(काष्ठा iio_trigger *trig)
अणु
	get_device(&trig->dev);
	__module_get(trig->owner);

	वापस trig;
पूर्ण

/**
 * iio_trigger_set_drvdata() - Set trigger driver data
 * @trig: IIO trigger काष्ठाure
 * @data: Driver specअगरic data
 *
 * Allows to attach an arbitrary poपूर्णांकer to an IIO trigger, which can later be
 * retrieved by iio_trigger_get_drvdata().
 */
अटल अंतरभूत व्योम iio_trigger_set_drvdata(काष्ठा iio_trigger *trig, व्योम *data)
अणु
	dev_set_drvdata(&trig->dev, data);
पूर्ण

/**
 * iio_trigger_get_drvdata() - Get trigger driver data
 * @trig: IIO trigger काष्ठाure
 *
 * Returns the data previously set with iio_trigger_set_drvdata()
 */
अटल अंतरभूत व्योम *iio_trigger_get_drvdata(काष्ठा iio_trigger *trig)
अणु
	वापस dev_get_drvdata(&trig->dev);
पूर्ण

/**
 * iio_trigger_रेजिस्टर() - रेजिस्टर a trigger with the IIO core
 * @trig_info:	trigger to be रेजिस्टरed
 **/
#घोषणा iio_trigger_रेजिस्टर(trig_info) \
	__iio_trigger_रेजिस्टर((trig_info), THIS_MODULE)
पूर्णांक __iio_trigger_रेजिस्टर(काष्ठा iio_trigger *trig_info,
			   काष्ठा module *this_mod);

#घोषणा devm_iio_trigger_रेजिस्टर(dev, trig_info) \
	__devm_iio_trigger_रेजिस्टर((dev), (trig_info), THIS_MODULE)
पूर्णांक __devm_iio_trigger_रेजिस्टर(काष्ठा device *dev,
				काष्ठा iio_trigger *trig_info,
				काष्ठा module *this_mod);

/**
 * iio_trigger_unरेजिस्टर() - unरेजिस्टर a trigger from the core
 * @trig_info:	trigger to be unरेजिस्टरed
 **/
व्योम iio_trigger_unरेजिस्टर(काष्ठा iio_trigger *trig_info);

/**
 * iio_trigger_set_immutable() - set an immutable trigger on destination
 *
 * @indio_dev: IIO device काष्ठाure containing the device
 * @trig: trigger to assign to device
 *
 **/
पूर्णांक iio_trigger_set_immutable(काष्ठा iio_dev *indio_dev, काष्ठा iio_trigger *trig);

/**
 * iio_trigger_poll() - called on a trigger occurring
 * @trig:	trigger which occurred
 *
 * Typically called in relevant hardware पूर्णांकerrupt handler.
 **/
व्योम iio_trigger_poll(काष्ठा iio_trigger *trig);
व्योम iio_trigger_poll_chained(काष्ठा iio_trigger *trig);

irqवापस_t iio_trigger_generic_data_rdy_poll(पूर्णांक irq, व्योम *निजी);

__म_लिखो(2, 3)
काष्ठा iio_trigger *iio_trigger_alloc(काष्ठा device *parent, स्थिर अक्षर *fmt, ...);
व्योम iio_trigger_मुक्त(काष्ठा iio_trigger *trig);

/**
 * iio_trigger_using_own() - tells us अगर we use our own HW trigger ourselves
 * @indio_dev:  device to check
 */
bool iio_trigger_using_own(काष्ठा iio_dev *indio_dev);

पूर्णांक iio_trigger_validate_own_device(काष्ठा iio_trigger *trig,
				     काष्ठा iio_dev *indio_dev);

#अन्यथा
काष्ठा iio_trigger;
काष्ठा iio_trigger_ops;
#पूर्ण_अगर
#पूर्ण_अगर /* _IIO_TRIGGER_H_ */
