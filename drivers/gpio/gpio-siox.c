<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2018 Pengutronix, Uwe Kleine-Kथघnig <kernel@pengutronix.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/siox.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/of.h>

काष्ठा gpio_siox_ddata अणु
	काष्ठा gpio_chip gchip;
	काष्ठा irq_chip ichip;
	काष्ठा mutex lock;
	u8 setdata[1];
	u8 getdata[3];

	raw_spinlock_t irqlock;
	u32 irq_enable;
	u32 irq_status;
	u32 irq_type[20];
पूर्ण;

/*
 * Note that this callback only sets the value that is घड़ीed out in the next
 * cycle.
 */
अटल पूर्णांक gpio_siox_set_data(काष्ठा siox_device *sdevice, u8 status, u8 buf[])
अणु
	काष्ठा gpio_siox_ddata *ddata = dev_get_drvdata(&sdevice->dev);

	mutex_lock(&ddata->lock);
	buf[0] = ddata->setdata[0];
	mutex_unlock(&ddata->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_siox_get_data(काष्ठा siox_device *sdevice, स्थिर u8 buf[])
अणु
	काष्ठा gpio_siox_ddata *ddata = dev_get_drvdata(&sdevice->dev);
	माप_प्रकार offset;
	u32 trigger;

	mutex_lock(&ddata->lock);

	raw_spin_lock_irq(&ddata->irqlock);

	क्रम (offset = 0; offset < 12; ++offset) अणु
		अचिन्हित पूर्णांक bitpos = 11 - offset;
		अचिन्हित पूर्णांक gpiolevel = buf[bitpos / 8] & (1 << bitpos % 8);
		अचिन्हित पूर्णांक prev_level =
			ddata->getdata[bitpos / 8] & (1 << (bitpos % 8));
		u32 irq_type = ddata->irq_type[offset];

		अगर (gpiolevel) अणु
			अगर ((irq_type & IRQ_TYPE_LEVEL_HIGH) ||
			    ((irq_type & IRQ_TYPE_EDGE_RISING) && !prev_level))
				ddata->irq_status |= 1 << offset;
		पूर्ण अन्यथा अणु
			अगर ((irq_type & IRQ_TYPE_LEVEL_LOW) ||
			    ((irq_type & IRQ_TYPE_EDGE_FALLING) && prev_level))
				ddata->irq_status |= 1 << offset;
		पूर्ण
	पूर्ण

	trigger = ddata->irq_status & ddata->irq_enable;

	raw_spin_unlock_irq(&ddata->irqlock);

	ddata->getdata[0] = buf[0];
	ddata->getdata[1] = buf[1];
	ddata->getdata[2] = buf[2];

	mutex_unlock(&ddata->lock);

	क्रम (offset = 0; offset < 12; ++offset) अणु
		अगर (trigger & (1 << offset)) अणु
			काष्ठा irq_करोमुख्य *irqकरोमुख्य = ddata->gchip.irq.करोमुख्य;
			अचिन्हित पूर्णांक irq = irq_find_mapping(irqकरोमुख्य, offset);

			/*
			 * Conceptually handle_nested_irq should call the flow
			 * handler of the irq chip. But it करोesn't, so we have
			 * to clean the irq_status here.
			 */
			raw_spin_lock_irq(&ddata->irqlock);
			ddata->irq_status &= ~(1 << offset);
			raw_spin_unlock_irq(&ddata->irqlock);

			handle_nested_irq(irq);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gpio_siox_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip *ic = irq_data_get_irq_chip(d);
	काष्ठा gpio_siox_ddata *ddata =
		container_of(ic, काष्ठा gpio_siox_ddata, ichip);

	raw_spin_lock(&ddata->irqlock);
	ddata->irq_status &= ~(1 << d->hwirq);
	raw_spin_unlock(&ddata->irqlock);
पूर्ण

अटल व्योम gpio_siox_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip *ic = irq_data_get_irq_chip(d);
	काष्ठा gpio_siox_ddata *ddata =
		container_of(ic, काष्ठा gpio_siox_ddata, ichip);

	raw_spin_lock(&ddata->irqlock);
	ddata->irq_enable &= ~(1 << d->hwirq);
	raw_spin_unlock(&ddata->irqlock);
पूर्ण

अटल व्योम gpio_siox_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip *ic = irq_data_get_irq_chip(d);
	काष्ठा gpio_siox_ddata *ddata =
		container_of(ic, काष्ठा gpio_siox_ddata, ichip);

	raw_spin_lock(&ddata->irqlock);
	ddata->irq_enable |= 1 << d->hwirq;
	raw_spin_unlock(&ddata->irqlock);
पूर्ण

अटल पूर्णांक gpio_siox_irq_set_type(काष्ठा irq_data *d, u32 type)
अणु
	काष्ठा irq_chip *ic = irq_data_get_irq_chip(d);
	काष्ठा gpio_siox_ddata *ddata =
		container_of(ic, काष्ठा gpio_siox_ddata, ichip);

	raw_spin_lock(&ddata->irqlock);
	ddata->irq_type[d->hwirq] = type;
	raw_spin_unlock(&ddata->irqlock);

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_siox_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा gpio_siox_ddata *ddata =
		container_of(chip, काष्ठा gpio_siox_ddata, gchip);
	पूर्णांक ret;

	mutex_lock(&ddata->lock);

	अगर (offset >= 12) अणु
		अचिन्हित पूर्णांक bitpos = 19 - offset;

		ret = ddata->setdata[0] & (1 << bitpos);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक bitpos = 11 - offset;

		ret = ddata->getdata[bitpos / 8] & (1 << (bitpos % 8));
	पूर्ण

	mutex_unlock(&ddata->lock);

	वापस ret;
पूर्ण

अटल व्योम gpio_siox_set(काष्ठा gpio_chip *chip,
			  अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	काष्ठा gpio_siox_ddata *ddata =
		container_of(chip, काष्ठा gpio_siox_ddata, gchip);
	u8 mask = 1 << (19 - offset);

	mutex_lock(&ddata->lock);

	अगर (value)
		ddata->setdata[0] |= mask;
	अन्यथा
		ddata->setdata[0] &= ~mask;

	mutex_unlock(&ddata->lock);
पूर्ण

अटल पूर्णांक gpio_siox_direction_input(काष्ठा gpio_chip *chip,
				     अचिन्हित पूर्णांक offset)
अणु
	अगर (offset >= 12)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक gpio_siox_direction_output(काष्ठा gpio_chip *chip,
				      अचिन्हित पूर्णांक offset, पूर्णांक value)
अणु
	अगर (offset < 12)
		वापस -EINVAL;

	gpio_siox_set(chip, offset, value);
	वापस 0;
पूर्ण

अटल पूर्णांक gpio_siox_get_direction(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	अगर (offset < 12)
		वापस GPIO_LINE_सूचीECTION_IN;
	अन्यथा
		वापस GPIO_LINE_सूचीECTION_OUT;
पूर्ण

अटल पूर्णांक gpio_siox_probe(काष्ठा siox_device *sdevice)
अणु
	काष्ठा gpio_siox_ddata *ddata;
	काष्ठा gpio_irq_chip *girq;
	काष्ठा device *dev = &sdevice->dev;
	पूर्णांक ret;

	ddata = devm_kzalloc(dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	dev_set_drvdata(dev, ddata);

	mutex_init(&ddata->lock);
	raw_spin_lock_init(&ddata->irqlock);

	ddata->gchip.base = -1;
	ddata->gchip.can_sleep = 1;
	ddata->gchip.parent = dev;
	ddata->gchip.owner = THIS_MODULE;
	ddata->gchip.get = gpio_siox_get;
	ddata->gchip.set = gpio_siox_set;
	ddata->gchip.direction_input = gpio_siox_direction_input;
	ddata->gchip.direction_output = gpio_siox_direction_output;
	ddata->gchip.get_direction = gpio_siox_get_direction;
	ddata->gchip.ngpio = 20;

	ddata->ichip.name = "siox-gpio";
	ddata->ichip.irq_ack = gpio_siox_irq_ack;
	ddata->ichip.irq_mask = gpio_siox_irq_mask;
	ddata->ichip.irq_unmask = gpio_siox_irq_unmask;
	ddata->ichip.irq_set_type = gpio_siox_irq_set_type;

	girq = &ddata->gchip.irq;
	girq->chip = &ddata->ichip;
	girq->शेष_type = IRQ_TYPE_NONE;
	girq->handler = handle_level_irq;
	girq->thपढ़ोed = true;

	ret = devm_gpiochip_add_data(dev, &ddata->gchip, शून्य);
	अगर (ret)
		dev_err(dev, "Failed to register gpio chip (%d)\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा siox_driver gpio_siox_driver = अणु
	.probe = gpio_siox_probe,
	.set_data = gpio_siox_set_data,
	.get_data = gpio_siox_get_data,
	.driver = अणु
		.name = "gpio-siox",
	पूर्ण,
पूर्ण;
module_siox_driver(gpio_siox_driver);

MODULE_AUTHOR("Uwe Kleine-Koenig <u.kleine-koenig@pengutronix.de>");
MODULE_DESCRIPTION("SIOX gpio driver");
MODULE_LICENSE("GPL v2");
