<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Common library क्रम ADIS16XXX devices
 *
 * Copyright 2012 Analog Devices Inc.
 *   Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/export.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/imu/adis.h>

अटल पूर्णांक adis_data_rdy_trigger_set_state(काष्ठा iio_trigger *trig,
						bool state)
अणु
	काष्ठा adis *adis = iio_trigger_get_drvdata(trig);

	वापस adis_enable_irq(adis, state);
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops adis_trigger_ops = अणु
	.set_trigger_state = &adis_data_rdy_trigger_set_state,
पूर्ण;

अटल पूर्णांक adis_validate_irq_flag(काष्ठा adis *adis)
अणु
	अचिन्हित दीर्घ direction = adis->irq_flag & IRQF_TRIGGER_MASK;
	/*
	 * Typically this devices have data पढ़ोy either on the rising edge or
	 * on the falling edge of the data पढ़ोy pin. This checks enक्रमces that
	 * one of those is set in the drivers... It शेषs to
	 * IRQF_TRIGGER_RISING क्रम backward compatibility with devices that
	 * करोn't support changing the pin polarity.
	 */
	अगर (direction == IRQF_TRIGGER_NONE) अणु
		adis->irq_flag |= IRQF_TRIGGER_RISING;
		वापस 0;
	पूर्ण अन्यथा अगर (direction != IRQF_TRIGGER_RISING &&
		   direction != IRQF_TRIGGER_FALLING) अणु
		dev_err(&adis->spi->dev, "Invalid IRQ mask: %08lx\n",
			adis->irq_flag);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * devm_adis_probe_trigger() - Sets up trigger क्रम a managed adis device
 * @adis: The adis device
 * @indio_dev: The IIO device
 *
 * Returns 0 on success or a negative error code
 */
पूर्णांक devm_adis_probe_trigger(काष्ठा adis *adis, काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;

	adis->trig = devm_iio_trigger_alloc(&adis->spi->dev, "%s-dev%d",
					    indio_dev->name, indio_dev->id);
	अगर (!adis->trig)
		वापस -ENOMEM;

	adis->trig->ops = &adis_trigger_ops;
	iio_trigger_set_drvdata(adis->trig, adis);

	ret = adis_validate_irq_flag(adis);
	अगर (ret)
		वापस ret;

	ret = devm_request_irq(&adis->spi->dev, adis->spi->irq,
			       &iio_trigger_generic_data_rdy_poll,
			       adis->irq_flag,
			       indio_dev->name,
			       adis->trig);
	अगर (ret)
		वापस ret;

	वापस devm_iio_trigger_रेजिस्टर(&adis->spi->dev, adis->trig);
पूर्ण
EXPORT_SYMBOL_GPL(devm_adis_probe_trigger);

