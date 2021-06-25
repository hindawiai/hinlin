<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011 Jonathan Cameron
 *
 * Companion module to the iio simple dummy example driver.
 * The purpose of this is to generate 'fake' event पूर्णांकerrupts thus
 * allowing that driver's code to be as बंद as possible to that of
 * a normal driver talking to hardware.  The approach used here
 * is not पूर्णांकended to be general and just happens to work क्रम this
 * particular use हाल.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/sysfs.h>

#समावेश "iio_dummy_evgen.h"
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/irq_sim.h>

/* Fiddly bit of faking and irq without hardware */
#घोषणा IIO_EVENTGEN_NO 10

/**
 * काष्ठा iio_dummy_eventgen - event generator specअगरic state
 * @regs: irq regs we are faking
 * @lock: protect the evgen state
 * @inuse: mask of which irqs are connected
 * @irq_sim: पूर्णांकerrupt simulator
 * @base: base of irq range
 * @irq_sim_करोमुख्य: irq simulator करोमुख्य
 */
काष्ठा iio_dummy_eventgen अणु
	काष्ठा iio_dummy_regs regs[IIO_EVENTGEN_NO];
	काष्ठा mutex lock;
	bool inuse[IIO_EVENTGEN_NO];
	काष्ठा irq_करोमुख्य *irq_sim_करोमुख्य;
पूर्ण;

/* We can only ever have one instance of this 'device' */
अटल काष्ठा iio_dummy_eventgen *iio_evgen;

अटल पूर्णांक iio_dummy_evgen_create(व्योम)
अणु
	पूर्णांक ret;

	iio_evgen = kzalloc(माप(*iio_evgen), GFP_KERNEL);
	अगर (!iio_evgen)
		वापस -ENOMEM;

	iio_evgen->irq_sim_करोमुख्य = irq_करोमुख्य_create_sim(शून्य,
							  IIO_EVENTGEN_NO);
	अगर (IS_ERR(iio_evgen->irq_sim_करोमुख्य)) अणु
		ret = PTR_ERR(iio_evgen->irq_sim_करोमुख्य);
		kमुक्त(iio_evgen);
		वापस ret;
	पूर्ण

	mutex_init(&iio_evgen->lock);

	वापस 0;
पूर्ण

/**
 * iio_dummy_evgen_get_irq() - get an evgen provided irq क्रम a device
 *
 * This function will give a मुक्त allocated irq to a client device.
 * That irq can then be caused to 'fire' by using the associated sysfs file.
 */
पूर्णांक iio_dummy_evgen_get_irq(व्योम)
अणु
	पूर्णांक i, ret = 0;

	अगर (!iio_evgen)
		वापस -ENODEV;

	mutex_lock(&iio_evgen->lock);
	क्रम (i = 0; i < IIO_EVENTGEN_NO; i++) अणु
		अगर (!iio_evgen->inuse[i]) अणु
			ret = irq_create_mapping(iio_evgen->irq_sim_करोमुख्य, i);
			iio_evgen->inuse[i] = true;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&iio_evgen->lock);
	अगर (i == IIO_EVENTGEN_NO)
		वापस -ENOMEM;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(iio_dummy_evgen_get_irq);

/**
 * iio_dummy_evgen_release_irq() - give the irq back.
 * @irq: irq being वापसed to the pool
 *
 * Used by client driver instances to give the irqs back when they disconnect
 */
व्योम iio_dummy_evgen_release_irq(पूर्णांक irq)
अणु
	काष्ठा irq_data *irqd = irq_get_irq_data(irq);

	mutex_lock(&iio_evgen->lock);
	iio_evgen->inuse[irqd_to_hwirq(irqd)] = false;
	irq_dispose_mapping(irq);
	mutex_unlock(&iio_evgen->lock);
पूर्ण
EXPORT_SYMBOL_GPL(iio_dummy_evgen_release_irq);

काष्ठा iio_dummy_regs *iio_dummy_evgen_get_regs(पूर्णांक irq)
अणु
	काष्ठा irq_data *irqd = irq_get_irq_data(irq);

	वापस &iio_evgen->regs[irqd_to_hwirq(irqd)];

पूर्ण
EXPORT_SYMBOL_GPL(iio_dummy_evgen_get_regs);

अटल व्योम iio_dummy_evgen_मुक्त(व्योम)
अणु
	irq_करोमुख्य_हटाओ_sim(iio_evgen->irq_sim_करोमुख्य);
	kमुक्त(iio_evgen);
पूर्ण

अटल व्योम iio_evgen_release(काष्ठा device *dev)
अणु
	iio_dummy_evgen_मुक्त();
पूर्ण

अटल sमाप_प्रकार iio_evgen_poke(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf,
			      माप_प्रकार len)
अणु
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	अचिन्हित दीर्घ event;
	पूर्णांक ret, irq;

	ret = kम_से_अदीर्घ(buf, 10, &event);
	अगर (ret)
		वापस ret;

	iio_evgen->regs[this_attr->address].reg_id   = this_attr->address;
	iio_evgen->regs[this_attr->address].reg_data = event;

	irq = irq_find_mapping(iio_evgen->irq_sim_करोमुख्य, this_attr->address);
	ret = irq_set_irqchip_state(irq, IRQCHIP_STATE_PENDING, true);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(poke_ev0, S_IWUSR, शून्य, &iio_evgen_poke, 0);
अटल IIO_DEVICE_ATTR(poke_ev1, S_IWUSR, शून्य, &iio_evgen_poke, 1);
अटल IIO_DEVICE_ATTR(poke_ev2, S_IWUSR, शून्य, &iio_evgen_poke, 2);
अटल IIO_DEVICE_ATTR(poke_ev3, S_IWUSR, शून्य, &iio_evgen_poke, 3);
अटल IIO_DEVICE_ATTR(poke_ev4, S_IWUSR, शून्य, &iio_evgen_poke, 4);
अटल IIO_DEVICE_ATTR(poke_ev5, S_IWUSR, शून्य, &iio_evgen_poke, 5);
अटल IIO_DEVICE_ATTR(poke_ev6, S_IWUSR, शून्य, &iio_evgen_poke, 6);
अटल IIO_DEVICE_ATTR(poke_ev7, S_IWUSR, शून्य, &iio_evgen_poke, 7);
अटल IIO_DEVICE_ATTR(poke_ev8, S_IWUSR, शून्य, &iio_evgen_poke, 8);
अटल IIO_DEVICE_ATTR(poke_ev9, S_IWUSR, शून्य, &iio_evgen_poke, 9);

अटल काष्ठा attribute *iio_evgen_attrs[] = अणु
	&iio_dev_attr_poke_ev0.dev_attr.attr,
	&iio_dev_attr_poke_ev1.dev_attr.attr,
	&iio_dev_attr_poke_ev2.dev_attr.attr,
	&iio_dev_attr_poke_ev3.dev_attr.attr,
	&iio_dev_attr_poke_ev4.dev_attr.attr,
	&iio_dev_attr_poke_ev5.dev_attr.attr,
	&iio_dev_attr_poke_ev6.dev_attr.attr,
	&iio_dev_attr_poke_ev7.dev_attr.attr,
	&iio_dev_attr_poke_ev8.dev_attr.attr,
	&iio_dev_attr_poke_ev9.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group iio_evgen_group = अणु
	.attrs = iio_evgen_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *iio_evgen_groups[] = अणु
	&iio_evgen_group,
	शून्य
पूर्ण;

अटल काष्ठा device iio_evgen_dev = अणु
	.bus = &iio_bus_type,
	.groups = iio_evgen_groups,
	.release = &iio_evgen_release,
पूर्ण;

अटल __init पूर्णांक iio_dummy_evgen_init(व्योम)
अणु
	पूर्णांक ret = iio_dummy_evgen_create();

	अगर (ret < 0)
		वापस ret;
	device_initialize(&iio_evgen_dev);
	dev_set_name(&iio_evgen_dev, "iio_evgen");
	ret = device_add(&iio_evgen_dev);
	अगर (ret)
		put_device(&iio_evgen_dev);
	वापस ret;
पूर्ण
module_init(iio_dummy_evgen_init);

अटल __निकास व्योम iio_dummy_evgen_निकास(व्योम)
अणु
	device_unरेजिस्टर(&iio_evgen_dev);
पूर्ण
module_निकास(iio_dummy_evgen_निकास);

MODULE_AUTHOR("Jonathan Cameron <jic23@kernel.org>");
MODULE_DESCRIPTION("IIO dummy driver");
MODULE_LICENSE("GPL v2");
