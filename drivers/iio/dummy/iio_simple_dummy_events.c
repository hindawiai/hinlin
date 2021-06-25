<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011 Jonathan Cameron
 *
 * Event handling elements of industrial I/O reference driver.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>
#समावेश "iio_simple_dummy.h"

/* Evgen 'fakes' पूर्णांकerrupt events क्रम this example */
#समावेश "iio_dummy_evgen.h"

/**
 * iio_simple_dummy_पढ़ो_event_config() - is event enabled?
 * @indio_dev: the device instance data
 * @chan: channel क्रम the event whose state is being queried
 * @type: type of the event whose state is being queried
 * @dir: direction of the vent whose state is being queried
 *
 * This function would normally query the relevant रेजिस्टरs or a cache to
 * discover अगर the event generation is enabled on the device.
 */
पूर्णांक iio_simple_dummy_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				       स्थिर काष्ठा iio_chan_spec *chan,
				       क्रमागत iio_event_type type,
				       क्रमागत iio_event_direction dir)
अणु
	काष्ठा iio_dummy_state *st = iio_priv(indio_dev);

	वापस st->event_en;
पूर्ण

/**
 * iio_simple_dummy_ग_लिखो_event_config() - set whether event is enabled
 * @indio_dev: the device instance data
 * @chan: channel क्रम the event whose state is being set
 * @type: type of the event whose state is being set
 * @dir: direction of the vent whose state is being set
 * @state: whether to enable or disable the device.
 *
 * This function would normally set the relevant रेजिस्टरs on the devices
 * so that it generates the specअगरied event. Here it just sets up a cached
 * value.
 */
पूर्णांक iio_simple_dummy_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
					स्थिर काष्ठा iio_chan_spec *chan,
					क्रमागत iio_event_type type,
					क्रमागत iio_event_direction dir,
					पूर्णांक state)
अणु
	काष्ठा iio_dummy_state *st = iio_priv(indio_dev);

	/*
	 *  Deliberately over the top code splitting to illustrate
	 * how this is करोne when multiple events exist.
	 */
	चयन (chan->type) अणु
	हाल IIO_VOLTAGE:
		चयन (type) अणु
		हाल IIO_EV_TYPE_THRESH:
			अगर (dir == IIO_EV_सूची_RISING)
				st->event_en = state;
			अन्यथा
				वापस -EINVAL;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल IIO_ACTIVITY:
		चयन (type) अणु
		हाल IIO_EV_TYPE_THRESH:
			st->event_en = state;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल IIO_STEPS:
		चयन (type) अणु
		हाल IIO_EV_TYPE_CHANGE:
			st->event_en = state;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * iio_simple_dummy_पढ़ो_event_value() - get value associated with event
 * @indio_dev: device instance specअगरic data
 * @chan: channel क्रम the event whose value is being पढ़ो
 * @type: type of the event whose value is being पढ़ो
 * @dir: direction of the vent whose value is being पढ़ो
 * @info: info type of the event whose value is being पढ़ो
 * @val: value क्रम the event code.
 * @val2: unused
 *
 * Many devices provide a large set of events of which only a subset may
 * be enabled at a समय, with value रेजिस्टरs whose meaning changes depending
 * on the event enabled. This often means that the driver must cache the values
 * associated with each possible events so that the right value is in place when
 * the enabled event is changed.
 */
पूर्णांक iio_simple_dummy_पढ़ो_event_value(काष्ठा iio_dev *indio_dev,
				      स्थिर काष्ठा iio_chan_spec *chan,
				      क्रमागत iio_event_type type,
				      क्रमागत iio_event_direction dir,
				      क्रमागत iio_event_info info,
				      पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा iio_dummy_state *st = iio_priv(indio_dev);

	*val = st->event_val;

	वापस IIO_VAL_INT;
पूर्ण

/**
 * iio_simple_dummy_ग_लिखो_event_value() - set value associate with event
 * @indio_dev: device instance specअगरic data
 * @chan: channel क्रम the event whose value is being set
 * @type: type of the event whose value is being set
 * @dir: direction of the vent whose value is being set
 * @info: info type of the event whose value is being set
 * @val: the value to be set.
 * @val2: unused
 */
पूर्णांक iio_simple_dummy_ग_लिखो_event_value(काष्ठा iio_dev *indio_dev,
				       स्थिर काष्ठा iio_chan_spec *chan,
				       क्रमागत iio_event_type type,
				       क्रमागत iio_event_direction dir,
				       क्रमागत iio_event_info info,
				       पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा iio_dummy_state *st = iio_priv(indio_dev);

	st->event_val = val;

	वापस 0;
पूर्ण

अटल irqवापस_t iio_simple_dummy_get_बारtamp(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा iio_dummy_state *st = iio_priv(indio_dev);

	st->event_बारtamp = iio_get_समय_ns(indio_dev);
	वापस IRQ_WAKE_THREAD;
पूर्ण

/**
 * iio_simple_dummy_event_handler() - identअगरy and pass on event
 * @irq: irq of event line
 * @निजी: poपूर्णांकer to device instance state.
 *
 * This handler is responsible क्रम querying the device to find out what
 * event occurred and क्रम then pushing that event towards userspace.
 * Here only one event occurs so we push that directly on with locally
 * grabbed बारtamp.
 */
अटल irqवापस_t iio_simple_dummy_event_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा iio_dummy_state *st = iio_priv(indio_dev);

	dev_dbg(&indio_dev->dev, "id %x event %x\n",
		st->regs->reg_id, st->regs->reg_data);

	चयन (st->regs->reg_data) अणु
	हाल 0:
		iio_push_event(indio_dev,
			       IIO_EVENT_CODE(IIO_VOLTAGE, 0, 0,
					      IIO_EV_सूची_RISING,
					      IIO_EV_TYPE_THRESH, 0, 0, 0),
			       st->event_बारtamp);
		अवरोध;
	हाल 1:
		अगर (st->activity_running > st->event_val)
			iio_push_event(indio_dev,
				       IIO_EVENT_CODE(IIO_ACTIVITY, 0,
						      IIO_MOD_RUNNING,
						      IIO_EV_सूची_RISING,
						      IIO_EV_TYPE_THRESH,
						      0, 0, 0),
				       st->event_बारtamp);
		अवरोध;
	हाल 2:
		अगर (st->activity_walking < st->event_val)
			iio_push_event(indio_dev,
				       IIO_EVENT_CODE(IIO_ACTIVITY, 0,
						      IIO_MOD_WALKING,
						      IIO_EV_सूची_FALLING,
						      IIO_EV_TYPE_THRESH,
						      0, 0, 0),
				       st->event_बारtamp);
		अवरोध;
	हाल 3:
		iio_push_event(indio_dev,
			       IIO_EVENT_CODE(IIO_STEPS, 0, IIO_NO_MOD,
					      IIO_EV_सूची_NONE,
					      IIO_EV_TYPE_CHANGE, 0, 0, 0),
			       st->event_बारtamp);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * iio_simple_dummy_events_रेजिस्टर() - setup पूर्णांकerrupt handling क्रम events
 * @indio_dev: device instance data
 *
 * This function requests the thपढ़ोed पूर्णांकerrupt to handle the events.
 * Normally the irq is a hardware पूर्णांकerrupt and the number comes
 * from board configuration files.  Here we get it from a companion
 * module that fakes the पूर्णांकerrupt क्रम us. Note that module in
 * no way क्रमms part of this example. Just assume that events magically
 * appear via the provided पूर्णांकerrupt.
 */
पूर्णांक iio_simple_dummy_events_रेजिस्टर(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dummy_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	/* Fire up event source - normally not present */
	st->event_irq = iio_dummy_evgen_get_irq();
	अगर (st->event_irq < 0) अणु
		ret = st->event_irq;
		जाओ error_ret;
	पूर्ण
	st->regs = iio_dummy_evgen_get_regs(st->event_irq);

	ret = request_thपढ़ोed_irq(st->event_irq,
				   &iio_simple_dummy_get_बारtamp,
				   &iio_simple_dummy_event_handler,
				   IRQF_ONESHOT,
				   "iio_simple_event",
				   indio_dev);
	अगर (ret < 0)
		जाओ error_मुक्त_evgen;
	वापस 0;

error_मुक्त_evgen:
	iio_dummy_evgen_release_irq(st->event_irq);
error_ret:
	वापस ret;
पूर्ण

/**
 * iio_simple_dummy_events_unरेजिस्टर() - tidy up पूर्णांकerrupt handling on हटाओ
 * @indio_dev: device instance data
 */
व्योम iio_simple_dummy_events_unरेजिस्टर(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dummy_state *st = iio_priv(indio_dev);

	मुक्त_irq(st->event_irq, indio_dev);
	/* Not part of normal driver */
	iio_dummy_evgen_release_irq(st->event_irq);
पूर्ण
