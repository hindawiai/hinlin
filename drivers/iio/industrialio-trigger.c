<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* The industrial I/O core, trigger handling functions
 *
 * Copyright (c) 2008 Jonathan Cameron
 */

#समावेश <linux/kernel.h>
#समावेश <linux/idr.h>
#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/trigger.h>
#समावेश "iio_core.h"
#समावेश "iio_core_trigger.h"
#समावेश <linux/iio/trigger_consumer.h>

/* RFC - Question of approach
 * Make the common हाल (single sensor single trigger)
 * simple by starting trigger capture from when first sensors
 * is added.
 *
 * Complex simultaneous start requires use of 'hold' functionality
 * of the trigger. (not implemented)
 *
 * Any other suggestions?
 */

अटल DEFINE_IDA(iio_trigger_ida);

/* Single list of all available triggers */
अटल LIST_HEAD(iio_trigger_list);
अटल DEFINE_MUTEX(iio_trigger_list_lock);

/**
 * iio_trigger_पढ़ो_name() - retrieve useful identअगरying name
 * @dev:	device associated with the iio_trigger
 * @attr:	poपूर्णांकer to the device_attribute काष्ठाure that is
 *		being processed
 * @buf:	buffer to prपूर्णांक the name पूर्णांकo
 *
 * Return: a negative number on failure or the number of written
 *	   अक्षरacters on success.
 */
अटल sमाप_प्रकार iio_trigger_पढ़ो_name(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा iio_trigger *trig = to_iio_trigger(dev);
	वापस sysfs_emit(buf, "%s\n", trig->name);
पूर्ण

अटल DEVICE_ATTR(name, S_IRUGO, iio_trigger_पढ़ो_name, शून्य);

अटल काष्ठा attribute *iio_trig_dev_attrs[] = अणु
	&dev_attr_name.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(iio_trig_dev);

अटल काष्ठा iio_trigger *__iio_trigger_find_by_name(स्थिर अक्षर *name);

पूर्णांक __iio_trigger_रेजिस्टर(काष्ठा iio_trigger *trig_info,
			   काष्ठा module *this_mod)
अणु
	पूर्णांक ret;

	trig_info->owner = this_mod;

	trig_info->id = ida_simple_get(&iio_trigger_ida, 0, 0, GFP_KERNEL);
	अगर (trig_info->id < 0)
		वापस trig_info->id;

	/* Set the name used क्रम the sysfs directory etc */
	dev_set_name(&trig_info->dev, "trigger%d", trig_info->id);

	ret = device_add(&trig_info->dev);
	अगर (ret)
		जाओ error_unरेजिस्टर_id;

	/* Add to list of available triggers held by the IIO core */
	mutex_lock(&iio_trigger_list_lock);
	अगर (__iio_trigger_find_by_name(trig_info->name)) अणु
		pr_err("Duplicate trigger name '%s'\n", trig_info->name);
		ret = -EEXIST;
		जाओ error_device_del;
	पूर्ण
	list_add_tail(&trig_info->list, &iio_trigger_list);
	mutex_unlock(&iio_trigger_list_lock);

	वापस 0;

error_device_del:
	mutex_unlock(&iio_trigger_list_lock);
	device_del(&trig_info->dev);
error_unरेजिस्टर_id:
	ida_simple_हटाओ(&iio_trigger_ida, trig_info->id);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__iio_trigger_रेजिस्टर);

व्योम iio_trigger_unरेजिस्टर(काष्ठा iio_trigger *trig_info)
अणु
	mutex_lock(&iio_trigger_list_lock);
	list_del(&trig_info->list);
	mutex_unlock(&iio_trigger_list_lock);

	ida_simple_हटाओ(&iio_trigger_ida, trig_info->id);
	/* Possible issue in here */
	device_del(&trig_info->dev);
पूर्ण
EXPORT_SYMBOL(iio_trigger_unरेजिस्टर);

पूर्णांक iio_trigger_set_immutable(काष्ठा iio_dev *indio_dev, काष्ठा iio_trigger *trig)
अणु
	अगर (!indio_dev || !trig)
		वापस -EINVAL;

	mutex_lock(&indio_dev->mlock);
	WARN_ON(indio_dev->trig_पढ़ोonly);

	indio_dev->trig = iio_trigger_get(trig);
	indio_dev->trig_पढ़ोonly = true;
	mutex_unlock(&indio_dev->mlock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(iio_trigger_set_immutable);

/* Search क्रम trigger by name, assuming iio_trigger_list_lock held */
अटल काष्ठा iio_trigger *__iio_trigger_find_by_name(स्थिर अक्षर *name)
अणु
	काष्ठा iio_trigger *iter;

	list_क्रम_each_entry(iter, &iio_trigger_list, list)
		अगर (!म_भेद(iter->name, name))
			वापस iter;

	वापस शून्य;
पूर्ण

अटल काष्ठा iio_trigger *iio_trigger_acquire_by_name(स्थिर अक्षर *name)
अणु
	काष्ठा iio_trigger *trig = शून्य, *iter;

	mutex_lock(&iio_trigger_list_lock);
	list_क्रम_each_entry(iter, &iio_trigger_list, list)
		अगर (sysfs_streq(iter->name, name)) अणु
			trig = iter;
			iio_trigger_get(trig);
			अवरोध;
		पूर्ण
	mutex_unlock(&iio_trigger_list_lock);

	वापस trig;
पूर्ण

व्योम iio_trigger_poll(काष्ठा iio_trigger *trig)
अणु
	पूर्णांक i;

	अगर (!atomic_पढ़ो(&trig->use_count)) अणु
		atomic_set(&trig->use_count, CONFIG_IIO_CONSUMERS_PER_TRIGGER);

		क्रम (i = 0; i < CONFIG_IIO_CONSUMERS_PER_TRIGGER; i++) अणु
			अगर (trig->subirqs[i].enabled)
				generic_handle_irq(trig->subirq_base + i);
			अन्यथा
				iio_trigger_notअगरy_करोne(trig);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(iio_trigger_poll);

irqवापस_t iio_trigger_generic_data_rdy_poll(पूर्णांक irq, व्योम *निजी)
अणु
	iio_trigger_poll(निजी);
	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL(iio_trigger_generic_data_rdy_poll);

व्योम iio_trigger_poll_chained(काष्ठा iio_trigger *trig)
अणु
	पूर्णांक i;

	अगर (!atomic_पढ़ो(&trig->use_count)) अणु
		atomic_set(&trig->use_count, CONFIG_IIO_CONSUMERS_PER_TRIGGER);

		क्रम (i = 0; i < CONFIG_IIO_CONSUMERS_PER_TRIGGER; i++) अणु
			अगर (trig->subirqs[i].enabled)
				handle_nested_irq(trig->subirq_base + i);
			अन्यथा
				iio_trigger_notअगरy_करोne(trig);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(iio_trigger_poll_chained);

व्योम iio_trigger_notअगरy_करोne(काष्ठा iio_trigger *trig)
अणु
	अगर (atomic_dec_and_test(&trig->use_count) && trig->ops &&
	    trig->ops->reenable)
		trig->ops->reenable(trig);
पूर्ण
EXPORT_SYMBOL(iio_trigger_notअगरy_करोne);

/* Trigger Consumer related functions */
अटल पूर्णांक iio_trigger_get_irq(काष्ठा iio_trigger *trig)
अणु
	पूर्णांक ret;

	mutex_lock(&trig->pool_lock);
	ret = biपंचांगap_find_मुक्त_region(trig->pool,
				      CONFIG_IIO_CONSUMERS_PER_TRIGGER,
				      ilog2(1));
	mutex_unlock(&trig->pool_lock);
	अगर (ret >= 0)
		ret += trig->subirq_base;

	वापस ret;
पूर्ण

अटल व्योम iio_trigger_put_irq(काष्ठा iio_trigger *trig, पूर्णांक irq)
अणु
	mutex_lock(&trig->pool_lock);
	clear_bit(irq - trig->subirq_base, trig->pool);
	mutex_unlock(&trig->pool_lock);
पूर्ण

/* Complनिकासy in here.  With certain triggers (datardy) an acknowledgement
 * may be needed अगर the pollfuncs करो not include the data पढ़ो क्रम the
 * triggering device.
 * This is not currently handled.  Alternative of not enabling trigger unless
 * the relevant function is in there may be the best option.
 */
/* Worth protecting against द्विगुन additions? */
पूर्णांक iio_trigger_attach_poll_func(काष्ठा iio_trigger *trig,
				 काष्ठा iio_poll_func *pf)
अणु
	bool notinuse =
		biपंचांगap_empty(trig->pool, CONFIG_IIO_CONSUMERS_PER_TRIGGER);
	पूर्णांक ret = 0;

	/* Prevent the module from being हटाओd whilst attached to a trigger */
	__module_get(pf->indio_dev->driver_module);

	/* Get irq number */
	pf->irq = iio_trigger_get_irq(trig);
	अगर (pf->irq < 0) अणु
		pr_err("Could not find an available irq for trigger %s, CONFIG_IIO_CONSUMERS_PER_TRIGGER=%d limit might be exceeded\n",
			trig->name, CONFIG_IIO_CONSUMERS_PER_TRIGGER);
		जाओ out_put_module;
	पूर्ण

	/* Request irq */
	ret = request_thपढ़ोed_irq(pf->irq, pf->h, pf->thपढ़ो,
				   pf->type, pf->name,
				   pf);
	अगर (ret < 0)
		जाओ out_put_irq;

	/* Enable trigger in driver */
	अगर (trig->ops && trig->ops->set_trigger_state && notinuse) अणु
		ret = trig->ops->set_trigger_state(trig, true);
		अगर (ret < 0)
			जाओ out_मुक्त_irq;
	पूर्ण

	/*
	 * Check अगर we just रेजिस्टरed to our own trigger: we determine that
	 * this is the हाल अगर the IIO device and the trigger device share the
	 * same parent device.
	 */
	अगर (pf->indio_dev->dev.parent == trig->dev.parent)
		trig->attached_own_device = true;

	वापस ret;

out_मुक्त_irq:
	मुक्त_irq(pf->irq, pf);
out_put_irq:
	iio_trigger_put_irq(trig, pf->irq);
out_put_module:
	module_put(pf->indio_dev->driver_module);
	वापस ret;
पूर्ण

पूर्णांक iio_trigger_detach_poll_func(काष्ठा iio_trigger *trig,
				 काष्ठा iio_poll_func *pf)
अणु
	bool no_other_users =
		biपंचांगap_weight(trig->pool, CONFIG_IIO_CONSUMERS_PER_TRIGGER) == 1;
	पूर्णांक ret = 0;

	अगर (trig->ops && trig->ops->set_trigger_state && no_other_users) अणु
		ret = trig->ops->set_trigger_state(trig, false);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (pf->indio_dev->dev.parent == trig->dev.parent)
		trig->attached_own_device = false;
	iio_trigger_put_irq(trig, pf->irq);
	मुक्त_irq(pf->irq, pf);
	module_put(pf->indio_dev->driver_module);

	वापस ret;
पूर्ण

irqवापस_t iio_pollfunc_store_समय(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;

	pf->बारtamp = iio_get_समय_ns(pf->indio_dev);
	वापस IRQ_WAKE_THREAD;
पूर्ण
EXPORT_SYMBOL(iio_pollfunc_store_समय);

काष्ठा iio_poll_func
*iio_alloc_pollfunc(irqवापस_t (*h)(पूर्णांक irq, व्योम *p),
		    irqवापस_t (*thपढ़ो)(पूर्णांक irq, व्योम *p),
		    पूर्णांक type,
		    काष्ठा iio_dev *indio_dev,
		    स्थिर अक्षर *fmt,
		    ...)
अणु
	बहु_सूची vargs;
	काष्ठा iio_poll_func *pf;

	pf = kदो_स्मृति(माप *pf, GFP_KERNEL);
	अगर (pf == शून्य)
		वापस शून्य;
	बहु_शुरू(vargs, fmt);
	pf->name = kvaप्र_लिखो(GFP_KERNEL, fmt, vargs);
	बहु_पूर्ण(vargs);
	अगर (pf->name == शून्य) अणु
		kमुक्त(pf);
		वापस शून्य;
	पूर्ण
	pf->h = h;
	pf->thपढ़ो = thपढ़ो;
	pf->type = type;
	pf->indio_dev = indio_dev;

	वापस pf;
पूर्ण
EXPORT_SYMBOL_GPL(iio_alloc_pollfunc);

व्योम iio_dealloc_pollfunc(काष्ठा iio_poll_func *pf)
अणु
	kमुक्त(pf->name);
	kमुक्त(pf);
पूर्ण
EXPORT_SYMBOL_GPL(iio_dealloc_pollfunc);

/**
 * iio_trigger_पढ़ो_current() - trigger consumer sysfs query current trigger
 * @dev:	device associated with an industrial I/O device
 * @attr:	poपूर्णांकer to the device_attribute काष्ठाure that
 *		is being processed
 * @buf:	buffer where the current trigger name will be prपूर्णांकed पूर्णांकo
 *
 * For trigger consumers the current_trigger पूर्णांकerface allows the trigger
 * used by the device to be queried.
 *
 * Return: a negative number on failure, the number of अक्षरacters written
 *	   on success or 0 अगर no trigger is available
 */
अटल sमाप_प्रकार iio_trigger_पढ़ो_current(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);

	अगर (indio_dev->trig)
		वापस sysfs_emit(buf, "%s\n", indio_dev->trig->name);
	वापस 0;
पूर्ण

/**
 * iio_trigger_ग_लिखो_current() - trigger consumer sysfs set current trigger
 * @dev:	device associated with an industrial I/O device
 * @attr:	device attribute that is being processed
 * @buf:	string buffer that holds the name of the trigger
 * @len:	length of the trigger name held by buf
 *
 * For trigger consumers the current_trigger पूर्णांकerface allows the trigger
 * used क्रम this device to be specअगरied at run समय based on the trigger's
 * name.
 *
 * Return: negative error code on failure or length of the buffer
 *	   on success
 */
अटल sमाप_प्रकार iio_trigger_ग_लिखो_current(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf,
					 माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा iio_trigger *oldtrig = indio_dev->trig;
	काष्ठा iio_trigger *trig;
	पूर्णांक ret;

	mutex_lock(&indio_dev->mlock);
	अगर (indio_dev->currenपंचांगode == INDIO_BUFFER_TRIGGERED) अणु
		mutex_unlock(&indio_dev->mlock);
		वापस -EBUSY;
	पूर्ण
	अगर (indio_dev->trig_पढ़ोonly) अणु
		mutex_unlock(&indio_dev->mlock);
		वापस -EPERM;
	पूर्ण
	mutex_unlock(&indio_dev->mlock);

	trig = iio_trigger_acquire_by_name(buf);
	अगर (oldtrig == trig) अणु
		ret = len;
		जाओ out_trigger_put;
	पूर्ण

	अगर (trig && indio_dev->info->validate_trigger) अणु
		ret = indio_dev->info->validate_trigger(indio_dev, trig);
		अगर (ret)
			जाओ out_trigger_put;
	पूर्ण

	अगर (trig && trig->ops && trig->ops->validate_device) अणु
		ret = trig->ops->validate_device(trig, indio_dev);
		अगर (ret)
			जाओ out_trigger_put;
	पूर्ण

	indio_dev->trig = trig;

	अगर (oldtrig) अणु
		अगर (indio_dev->modes & INDIO_EVENT_TRIGGERED)
			iio_trigger_detach_poll_func(oldtrig,
						     indio_dev->pollfunc_event);
		iio_trigger_put(oldtrig);
	पूर्ण
	अगर (indio_dev->trig) अणु
		अगर (indio_dev->modes & INDIO_EVENT_TRIGGERED)
			iio_trigger_attach_poll_func(indio_dev->trig,
						     indio_dev->pollfunc_event);
	पूर्ण

	वापस len;

out_trigger_put:
	अगर (trig)
		iio_trigger_put(trig);
	वापस ret;
पूर्ण

अटल DEVICE_ATTR(current_trigger, S_IRUGO | S_IWUSR,
		   iio_trigger_पढ़ो_current,
		   iio_trigger_ग_लिखो_current);

अटल काष्ठा attribute *iio_trigger_consumer_attrs[] = अणु
	&dev_attr_current_trigger.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group iio_trigger_consumer_attr_group = अणु
	.name = "trigger",
	.attrs = iio_trigger_consumer_attrs,
पूर्ण;

अटल व्योम iio_trig_release(काष्ठा device *device)
अणु
	काष्ठा iio_trigger *trig = to_iio_trigger(device);
	पूर्णांक i;

	अगर (trig->subirq_base) अणु
		क्रम (i = 0; i < CONFIG_IIO_CONSUMERS_PER_TRIGGER; i++) अणु
			irq_modअगरy_status(trig->subirq_base + i,
					  IRQ_NOAUTOEN,
					  IRQ_NOREQUEST | IRQ_NOPROBE);
			irq_set_chip(trig->subirq_base + i,
				     शून्य);
			irq_set_handler(trig->subirq_base + i,
					शून्य);
		पूर्ण

		irq_मुक्त_descs(trig->subirq_base,
			       CONFIG_IIO_CONSUMERS_PER_TRIGGER);
	पूर्ण
	kमुक्त(trig->name);
	kमुक्त(trig);
पूर्ण

अटल स्थिर काष्ठा device_type iio_trig_type = अणु
	.release = iio_trig_release,
	.groups = iio_trig_dev_groups,
पूर्ण;

अटल व्योम iio_trig_subirqmask(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(d);
	काष्ठा iio_trigger *trig = container_of(chip, काष्ठा iio_trigger, subirq_chip);

	trig->subirqs[d->irq - trig->subirq_base].enabled = false;
पूर्ण

अटल व्योम iio_trig_subirqunmask(काष्ठा irq_data *d)
अणु
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(d);
	काष्ठा iio_trigger *trig = container_of(chip, काष्ठा iio_trigger, subirq_chip);

	trig->subirqs[d->irq - trig->subirq_base].enabled = true;
पूर्ण

अटल __म_लिखो(2, 0)
काष्ठा iio_trigger *viio_trigger_alloc(काष्ठा device *parent,
				       स्थिर अक्षर *fmt,
				       बहु_सूची vargs)
अणु
	काष्ठा iio_trigger *trig;
	पूर्णांक i;

	trig = kzalloc(माप *trig, GFP_KERNEL);
	अगर (!trig)
		वापस शून्य;

	trig->dev.parent = parent;
	trig->dev.type = &iio_trig_type;
	trig->dev.bus = &iio_bus_type;
	device_initialize(&trig->dev);

	mutex_init(&trig->pool_lock);
	trig->subirq_base = irq_alloc_descs(-1, 0,
					    CONFIG_IIO_CONSUMERS_PER_TRIGGER,
					    0);
	अगर (trig->subirq_base < 0)
		जाओ मुक्त_trig;

	trig->name = kvaप्र_लिखो(GFP_KERNEL, fmt, vargs);
	अगर (trig->name == शून्य)
		जाओ मुक्त_descs;

	trig->subirq_chip.name = trig->name;
	trig->subirq_chip.irq_mask = &iio_trig_subirqmask;
	trig->subirq_chip.irq_unmask = &iio_trig_subirqunmask;
	क्रम (i = 0; i < CONFIG_IIO_CONSUMERS_PER_TRIGGER; i++) अणु
		irq_set_chip(trig->subirq_base + i, &trig->subirq_chip);
		irq_set_handler(trig->subirq_base + i, &handle_simple_irq);
		irq_modअगरy_status(trig->subirq_base + i,
				  IRQ_NOREQUEST | IRQ_NOAUTOEN, IRQ_NOPROBE);
	पूर्ण
	get_device(&trig->dev);

	वापस trig;

मुक्त_descs:
	irq_मुक्त_descs(trig->subirq_base, CONFIG_IIO_CONSUMERS_PER_TRIGGER);
मुक्त_trig:
	kमुक्त(trig);
	वापस शून्य;
पूर्ण

/**
 * iio_trigger_alloc - Allocate a trigger
 * @parent:		Device to allocate iio_trigger क्रम
 * @fmt:		trigger name क्रमmat. If it includes क्रमmat
 *			specअगरiers, the additional arguments following
 *			क्रमmat are क्रमmatted and inserted in the resulting
 *			string replacing their respective specअगरiers.
 * RETURNS:
 * Poपूर्णांकer to allocated iio_trigger on success, शून्य on failure.
 */
काष्ठा iio_trigger *iio_trigger_alloc(काष्ठा device *parent, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा iio_trigger *trig;
	बहु_सूची vargs;

	बहु_शुरू(vargs, fmt);
	trig = viio_trigger_alloc(parent, fmt, vargs);
	बहु_पूर्ण(vargs);

	वापस trig;
पूर्ण
EXPORT_SYMBOL(iio_trigger_alloc);

व्योम iio_trigger_मुक्त(काष्ठा iio_trigger *trig)
अणु
	अगर (trig)
		put_device(&trig->dev);
पूर्ण
EXPORT_SYMBOL(iio_trigger_मुक्त);

अटल व्योम devm_iio_trigger_release(काष्ठा device *dev, व्योम *res)
अणु
	iio_trigger_मुक्त(*(काष्ठा iio_trigger **)res);
पूर्ण

/**
 * devm_iio_trigger_alloc - Resource-managed iio_trigger_alloc()
 * Managed iio_trigger_alloc.  iio_trigger allocated with this function is
 * स्वतःmatically मुक्तd on driver detach.
 * @parent:		Device to allocate iio_trigger क्रम
 * @fmt:		trigger name क्रमmat. If it includes क्रमmat
 *			specअगरiers, the additional arguments following
 *			क्रमmat are क्रमmatted and inserted in the resulting
 *			string replacing their respective specअगरiers.
 *
 *
 * RETURNS:
 * Poपूर्णांकer to allocated iio_trigger on success, शून्य on failure.
 */
काष्ठा iio_trigger *devm_iio_trigger_alloc(काष्ठा device *parent, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा iio_trigger **ptr, *trig;
	बहु_सूची vargs;

	ptr = devres_alloc(devm_iio_trigger_release, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस शून्य;

	/* use raw alloc_dr क्रम kदो_स्मृति caller tracing */
	बहु_शुरू(vargs, fmt);
	trig = viio_trigger_alloc(parent, fmt, vargs);
	बहु_पूर्ण(vargs);
	अगर (trig) अणु
		*ptr = trig;
		devres_add(parent, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस trig;
पूर्ण
EXPORT_SYMBOL_GPL(devm_iio_trigger_alloc);

अटल व्योम devm_iio_trigger_unreg(काष्ठा device *dev, व्योम *res)
अणु
	iio_trigger_unरेजिस्टर(*(काष्ठा iio_trigger **)res);
पूर्ण

/**
 * __devm_iio_trigger_रेजिस्टर - Resource-managed iio_trigger_रेजिस्टर()
 * @dev:	device this trigger was allocated क्रम
 * @trig_info:	trigger to रेजिस्टर
 * @this_mod:   module रेजिस्टरing the trigger
 *
 * Managed iio_trigger_रेजिस्टर().  The IIO trigger रेजिस्टरed with this
 * function is स्वतःmatically unरेजिस्टरed on driver detach. This function
 * calls iio_trigger_रेजिस्टर() पूर्णांकernally. Refer to that function क्रम more
 * inक्रमmation.
 *
 * RETURNS:
 * 0 on success, negative error number on failure.
 */
पूर्णांक __devm_iio_trigger_रेजिस्टर(काष्ठा device *dev,
				काष्ठा iio_trigger *trig_info,
				काष्ठा module *this_mod)
अणु
	काष्ठा iio_trigger **ptr;
	पूर्णांक ret;

	ptr = devres_alloc(devm_iio_trigger_unreg, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	*ptr = trig_info;
	ret = __iio_trigger_रेजिस्टर(trig_info, this_mod);
	अगर (!ret)
		devres_add(dev, ptr);
	अन्यथा
		devres_मुक्त(ptr);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__devm_iio_trigger_रेजिस्टर);

bool iio_trigger_using_own(काष्ठा iio_dev *indio_dev)
अणु
	वापस indio_dev->trig->attached_own_device;
पूर्ण
EXPORT_SYMBOL(iio_trigger_using_own);

/**
 * iio_trigger_validate_own_device - Check अगर a trigger and IIO device beदीर्घ to
 *  the same device
 * @trig: The IIO trigger to check
 * @indio_dev: the IIO device to check
 *
 * This function can be used as the validate_device callback क्रम triggers that
 * can only be attached to their own device.
 *
 * Return: 0 अगर both the trigger and the IIO device beदीर्घ to the same
 * device, -EINVAL otherwise.
 */
पूर्णांक iio_trigger_validate_own_device(काष्ठा iio_trigger *trig,
				    काष्ठा iio_dev *indio_dev)
अणु
	अगर (indio_dev->dev.parent != trig->dev.parent)
		वापस -EINVAL;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(iio_trigger_validate_own_device);

पूर्णांक iio_device_रेजिस्टर_trigger_consumer(काष्ठा iio_dev *indio_dev)
अणु
	वापस iio_device_रेजिस्टर_sysfs_group(indio_dev,
					       &iio_trigger_consumer_attr_group);
पूर्ण

व्योम iio_device_unरेजिस्टर_trigger_consumer(काष्ठा iio_dev *indio_dev)
अणु
	/* Clean up an associated but not attached trigger reference */
	अगर (indio_dev->trig)
		iio_trigger_put(indio_dev->trig);
पूर्ण
