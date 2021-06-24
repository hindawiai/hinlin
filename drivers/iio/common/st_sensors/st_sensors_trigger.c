<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics sensors trigger library driver
 *
 * Copyright 2012-2013 STMicroelectronics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/common/st_sensors.h>
#समावेश "st_sensors_core.h"

/**
 * st_sensors_new_samples_available() - check अगर more samples came in
 * @indio_dev: IIO device reference.
 * @sdata: Sensor data.
 *
 * वापसs:
 * false - no new samples available or पढ़ो error
 * true - new samples available
 */
अटल bool st_sensors_new_samples_available(काष्ठा iio_dev *indio_dev,
					     काष्ठा st_sensor_data *sdata)
अणु
	पूर्णांक ret, status;

	/* How would I know अगर I can't check it? */
	अगर (!sdata->sensor_settings->drdy_irq.stat_drdy.addr)
		वापस true;

	/* No scan mask, no पूर्णांकerrupt */
	अगर (!indio_dev->active_scan_mask)
		वापस false;

	ret = regmap_पढ़ो(sdata->regmap,
			  sdata->sensor_settings->drdy_irq.stat_drdy.addr,
			  &status);
	अगर (ret < 0) अणु
		dev_err(sdata->dev, "error checking samples available\n");
		वापस false;
	पूर्ण

	वापस !!(status & sdata->sensor_settings->drdy_irq.stat_drdy.mask);
पूर्ण

/**
 * st_sensors_irq_handler() - top half of the IRQ-based triggers
 * @irq: irq number
 * @p: निजी handler data
 */
अटल irqवापस_t st_sensors_irq_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_trigger *trig = p;
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);

	/* Get the समय stamp as बंद in समय as possible */
	sdata->hw_बारtamp = iio_get_समय_ns(indio_dev);
	वापस IRQ_WAKE_THREAD;
पूर्ण

/**
 * st_sensors_irq_thपढ़ो() - bottom half of the IRQ-based triggers
 * @irq: irq number
 * @p: निजी handler data
 */
अटल irqवापस_t st_sensors_irq_thपढ़ो(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_trigger *trig = p;
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);

	/*
	 * If this trigger is backed by a hardware पूर्णांकerrupt and we have a
	 * status रेजिस्टर, check अगर this IRQ came from us. Notice that
	 * we will process also अगर st_sensors_new_samples_available()
	 * वापसs negative: अगर we can't check status, then poll
	 * unconditionally.
	 */
	अगर (sdata->hw_irq_trigger &&
	    st_sensors_new_samples_available(indio_dev, sdata)) अणु
		iio_trigger_poll_chained(p);
	पूर्ण अन्यथा अणु
		dev_dbg(sdata->dev, "spurious IRQ\n");
		वापस IRQ_NONE;
	पूर्ण

	/*
	 * If we have proper level IRQs the handler will be re-entered अगर
	 * the line is still active, so वापस here and come back in through
	 * the top half अगर need be.
	 */
	अगर (!sdata->edge_irq)
		वापस IRQ_HANDLED;

	/*
	 * If we are using edge IRQs, new samples arrived जबतक processing
	 * the IRQ and those may be missed unless we pick them here, so poll
	 * again. If the sensor delivery frequency is very high, this thपढ़ो
	 * turns पूर्णांकo a polled loop handler.
	 */
	जबतक (sdata->hw_irq_trigger &&
	       st_sensors_new_samples_available(indio_dev, sdata)) अणु
		dev_dbg(sdata->dev, "more samples came in during polling\n");
		sdata->hw_बारtamp = iio_get_समय_ns(indio_dev);
		iio_trigger_poll_chained(p);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक st_sensors_allocate_trigger(काष्ठा iio_dev *indio_dev,
				स्थिर काष्ठा iio_trigger_ops *trigger_ops)
अणु
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);
	अचिन्हित दीर्घ irq_trig;
	पूर्णांक err;

	sdata->trig = iio_trigger_alloc(sdata->dev, "%s-trigger",
					indio_dev->name);
	अगर (sdata->trig == शून्य) अणु
		dev_err(&indio_dev->dev, "failed to allocate iio trigger.\n");
		वापस -ENOMEM;
	पूर्ण

	iio_trigger_set_drvdata(sdata->trig, indio_dev);
	sdata->trig->ops = trigger_ops;

	irq_trig = irqd_get_trigger_type(irq_get_irq_data(sdata->irq));
	/*
	 * If the IRQ is triggered on falling edge, we need to mark the
	 * पूर्णांकerrupt as active low, अगर the hardware supports this.
	 */
	चयन(irq_trig) अणु
	हाल IRQF_TRIGGER_FALLING:
	हाल IRQF_TRIGGER_LOW:
		अगर (!sdata->sensor_settings->drdy_irq.addr_ihl) अणु
			dev_err(&indio_dev->dev,
				"falling/low specified for IRQ but hardware supports only rising/high: will request rising/high\n");
			अगर (irq_trig == IRQF_TRIGGER_FALLING)
				irq_trig = IRQF_TRIGGER_RISING;
			अगर (irq_trig == IRQF_TRIGGER_LOW)
				irq_trig = IRQF_TRIGGER_HIGH;
		पूर्ण अन्यथा अणु
			/* Set up INT active low i.e. falling edge */
			err = st_sensors_ग_लिखो_data_with_mask(indio_dev,
				sdata->sensor_settings->drdy_irq.addr_ihl,
				sdata->sensor_settings->drdy_irq.mask_ihl, 1);
			अगर (err < 0)
				जाओ iio_trigger_मुक्त;
			dev_info(&indio_dev->dev,
				 "interrupts on the falling edge or active low level\n");
		पूर्ण
		अवरोध;
	हाल IRQF_TRIGGER_RISING:
		dev_info(&indio_dev->dev,
			 "interrupts on the rising edge\n");
		अवरोध;
	हाल IRQF_TRIGGER_HIGH:
		dev_info(&indio_dev->dev,
			 "interrupts active high level\n");
		अवरोध;
	शेष:
		/* This is the most preferred mode, अगर possible */
		dev_err(&indio_dev->dev,
			"unsupported IRQ trigger specified (%lx), enforce rising edge\n", irq_trig);
		irq_trig = IRQF_TRIGGER_RISING;
	पूर्ण

	/* Tell the पूर्णांकerrupt handler that we're dealing with edges */
	अगर (irq_trig == IRQF_TRIGGER_FALLING ||
	    irq_trig == IRQF_TRIGGER_RISING) अणु
		अगर (!sdata->sensor_settings->drdy_irq.stat_drdy.addr) अणु
			dev_err(&indio_dev->dev,
				"edge IRQ not supported w/o stat register.\n");
			err = -EOPNOTSUPP;
			जाओ iio_trigger_मुक्त;
		पूर्ण
		sdata->edge_irq = true;
	पूर्ण अन्यथा अणु
		/*
		 * If we're not using edges (i.e. level पूर्णांकerrupts) we
		 * just mask off the IRQ, handle one पूर्णांकerrupt, then
		 * अगर the line is still low, we वापस to the
		 * पूर्णांकerrupt handler top half again and start over.
		 */
		irq_trig |= IRQF_ONESHOT;
	पूर्ण

	/*
	 * If the पूर्णांकerrupt pin is Open Drain, by definition this
	 * means that the पूर्णांकerrupt line may be shared with other
	 * peripherals. But to करो this we also need to have a status
	 * रेजिस्टर and mask to figure out अगर this sensor was firing
	 * the IRQ or not, so we can tell the पूर्णांकerrupt handle that
	 * it was "our" पूर्णांकerrupt.
	 */
	अगर (sdata->पूर्णांक_pin_खोलो_drain &&
	    sdata->sensor_settings->drdy_irq.stat_drdy.addr)
		irq_trig |= IRQF_SHARED;

	err = request_thपढ़ोed_irq(sdata->irq,
				   st_sensors_irq_handler,
				   st_sensors_irq_thपढ़ो,
				   irq_trig,
				   sdata->trig->name,
				   sdata->trig);
	अगर (err) अणु
		dev_err(&indio_dev->dev, "failed to request trigger IRQ.\n");
		जाओ iio_trigger_मुक्त;
	पूर्ण

	err = iio_trigger_रेजिस्टर(sdata->trig);
	अगर (err < 0) अणु
		dev_err(&indio_dev->dev, "failed to register iio trigger.\n");
		जाओ iio_trigger_रेजिस्टर_error;
	पूर्ण
	indio_dev->trig = iio_trigger_get(sdata->trig);

	वापस 0;

iio_trigger_रेजिस्टर_error:
	मुक्त_irq(sdata->irq, sdata->trig);
iio_trigger_मुक्त:
	iio_trigger_मुक्त(sdata->trig);
	वापस err;
पूर्ण
EXPORT_SYMBOL(st_sensors_allocate_trigger);

व्योम st_sensors_deallocate_trigger(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा st_sensor_data *sdata = iio_priv(indio_dev);

	iio_trigger_unरेजिस्टर(sdata->trig);
	मुक्त_irq(sdata->irq, sdata->trig);
	iio_trigger_मुक्त(sdata->trig);
पूर्ण
EXPORT_SYMBOL(st_sensors_deallocate_trigger);

पूर्णांक st_sensors_validate_device(काष्ठा iio_trigger *trig,
			       काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा iio_dev *indio = iio_trigger_get_drvdata(trig);

	अगर (indio != indio_dev)
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(st_sensors_validate_device);

MODULE_AUTHOR("Denis Ciocca <denis.ciocca@st.com>");
MODULE_DESCRIPTION("STMicroelectronics ST-sensors trigger");
MODULE_LICENSE("GPL v2");
