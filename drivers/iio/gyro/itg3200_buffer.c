<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * itg3200_buffer.c -- support InvenSense ITG3200
 *                     Digital 3-Axis Gyroscope driver
 *
 * Copyright (c) 2011 Christian Strobel <christian.strobel@iis.fraunhofer.de>
 * Copyright (c) 2011 Manuel Stahl <manuel.stahl@iis.fraunhofer.de>
 * Copyright (c) 2012 Thorsten Nowak <thorsten.nowak@iis.fraunhofer.de>
 */

#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/gyro/itg3200.h>


अटल पूर्णांक itg3200_पढ़ो_all_channels(काष्ठा i2c_client *i2c, __be16 *buf)
अणु
	u8 tx = 0x80 | ITG3200_REG_TEMP_OUT_H;
	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.addr = i2c->addr,
			.flags = i2c->flags,
			.len = 1,
			.buf = &tx,
		पूर्ण,
		अणु
			.addr = i2c->addr,
			.flags = i2c->flags | I2C_M_RD,
			.len = ITG3200_SCAN_ELEMENTS * माप(s16),
			.buf = (अक्षर *)&buf,
		पूर्ण,
	पूर्ण;

	वापस i2c_transfer(i2c->adapter, msg, 2);
पूर्ण

अटल irqवापस_t itg3200_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा itg3200 *st = iio_priv(indio_dev);
	/*
	 * Ensure correct alignment and padding including क्रम the
	 * बारtamp that may be inserted.
	 */
	काष्ठा अणु
		__be16 buf[ITG3200_SCAN_ELEMENTS];
		s64 ts __aligned(8);
	पूर्ण scan;

	पूर्णांक ret = itg3200_पढ़ो_all_channels(st->i2c, scan.buf);
	अगर (ret < 0)
		जाओ error_ret;

	iio_push_to_buffers_with_बारtamp(indio_dev, &scan, pf->बारtamp);

	iio_trigger_notअगरy_करोne(indio_dev->trig);

error_ret:
	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक itg3200_buffer_configure(काष्ठा iio_dev *indio_dev)
अणु
	वापस iio_triggered_buffer_setup(indio_dev, &iio_pollfunc_store_समय,
		itg3200_trigger_handler, शून्य);
पूर्ण

व्योम itg3200_buffer_unconfigure(काष्ठा iio_dev *indio_dev)
अणु
	iio_triggered_buffer_cleanup(indio_dev);
पूर्ण


अटल पूर्णांक itg3200_data_rdy_trigger_set_state(काष्ठा iio_trigger *trig,
		bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	पूर्णांक ret;
	u8 msc;

	ret = itg3200_पढ़ो_reg_8(indio_dev, ITG3200_REG_IRQ_CONFIG, &msc);
	अगर (ret)
		जाओ error_ret;

	अगर (state)
		msc |= ITG3200_IRQ_DATA_RDY_ENABLE;
	अन्यथा
		msc &= ~ITG3200_IRQ_DATA_RDY_ENABLE;

	ret = itg3200_ग_लिखो_reg_8(indio_dev, ITG3200_REG_IRQ_CONFIG, msc);
	अगर (ret)
		जाओ error_ret;

error_ret:
	वापस ret;

पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops itg3200_trigger_ops = अणु
	.set_trigger_state = &itg3200_data_rdy_trigger_set_state,
पूर्ण;

पूर्णांक itg3200_probe_trigger(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;
	काष्ठा itg3200 *st = iio_priv(indio_dev);

	st->trig = iio_trigger_alloc(&st->i2c->dev, "%s-dev%d", indio_dev->name,
				     indio_dev->id);
	अगर (!st->trig)
		वापस -ENOMEM;

	ret = request_irq(st->i2c->irq,
			  &iio_trigger_generic_data_rdy_poll,
			  IRQF_TRIGGER_RISING,
			  "itg3200_data_rdy",
			  st->trig);
	अगर (ret)
		जाओ error_मुक्त_trig;


	st->trig->ops = &itg3200_trigger_ops;
	iio_trigger_set_drvdata(st->trig, indio_dev);
	ret = iio_trigger_रेजिस्टर(st->trig);
	अगर (ret)
		जाओ error_मुक्त_irq;

	/* select शेष trigger */
	indio_dev->trig = iio_trigger_get(st->trig);

	वापस 0;

error_मुक्त_irq:
	मुक्त_irq(st->i2c->irq, st->trig);
error_मुक्त_trig:
	iio_trigger_मुक्त(st->trig);
	वापस ret;
पूर्ण

व्योम itg3200_हटाओ_trigger(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा itg3200 *st = iio_priv(indio_dev);

	iio_trigger_unरेजिस्टर(st->trig);
	मुक्त_irq(st->i2c->irq, st->trig);
	iio_trigger_मुक्त(st->trig);
पूर्ण
