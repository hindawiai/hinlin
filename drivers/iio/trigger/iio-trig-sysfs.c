<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2011 Analog Devices Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/irq_work.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/trigger.h>

काष्ठा iio_sysfs_trig अणु
	काष्ठा iio_trigger *trig;
	काष्ठा irq_work work;
	पूर्णांक id;
	काष्ठा list_head l;
पूर्ण;

अटल LIST_HEAD(iio_sysfs_trig_list);
अटल DEFINE_MUTEX(iio_sysfs_trig_list_mut);

अटल पूर्णांक iio_sysfs_trigger_probe(पूर्णांक id);
अटल sमाप_प्रकार iio_sysfs_trig_add(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf,
				  माप_प्रकार len)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ input;

	ret = kम_से_अदीर्घ(buf, 10, &input);
	अगर (ret)
		वापस ret;
	ret = iio_sysfs_trigger_probe(input);
	अगर (ret)
		वापस ret;
	वापस len;
पूर्ण
अटल DEVICE_ATTR(add_trigger, S_IWUSR, शून्य, &iio_sysfs_trig_add);

अटल पूर्णांक iio_sysfs_trigger_हटाओ(पूर्णांक id);
अटल sमाप_प्रकार iio_sysfs_trig_हटाओ(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf,
				     माप_प्रकार len)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ input;

	ret = kम_से_अदीर्घ(buf, 10, &input);
	अगर (ret)
		वापस ret;
	ret = iio_sysfs_trigger_हटाओ(input);
	अगर (ret)
		वापस ret;
	वापस len;
पूर्ण

अटल DEVICE_ATTR(हटाओ_trigger, S_IWUSR, शून्य, &iio_sysfs_trig_हटाओ);

अटल काष्ठा attribute *iio_sysfs_trig_attrs[] = अणु
	&dev_attr_add_trigger.attr,
	&dev_attr_हटाओ_trigger.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group iio_sysfs_trig_group = अणु
	.attrs = iio_sysfs_trig_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *iio_sysfs_trig_groups[] = अणु
	&iio_sysfs_trig_group,
	शून्य
पूर्ण;


/* Nothing to actually करो upon release */
अटल व्योम iio_trigger_sysfs_release(काष्ठा device *dev)
अणु
पूर्ण

अटल काष्ठा device iio_sysfs_trig_dev = अणु
	.bus = &iio_bus_type,
	.groups = iio_sysfs_trig_groups,
	.release = &iio_trigger_sysfs_release,
पूर्ण;

अटल व्योम iio_sysfs_trigger_work(काष्ठा irq_work *work)
अणु
	काष्ठा iio_sysfs_trig *trig = container_of(work, काष्ठा iio_sysfs_trig,
							work);

	iio_trigger_poll(trig->trig);
पूर्ण

अटल sमाप_प्रकार iio_sysfs_trigger_poll(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा iio_trigger *trig = to_iio_trigger(dev);
	काष्ठा iio_sysfs_trig *sysfs_trig = iio_trigger_get_drvdata(trig);

	irq_work_queue(&sysfs_trig->work);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(trigger_now, S_IWUSR, शून्य, iio_sysfs_trigger_poll);

अटल काष्ठा attribute *iio_sysfs_trigger_attrs[] = अणु
	&dev_attr_trigger_now.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group iio_sysfs_trigger_attr_group = अणु
	.attrs = iio_sysfs_trigger_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *iio_sysfs_trigger_attr_groups[] = अणु
	&iio_sysfs_trigger_attr_group,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा iio_trigger_ops iio_sysfs_trigger_ops = अणु
पूर्ण;

अटल पूर्णांक iio_sysfs_trigger_probe(पूर्णांक id)
अणु
	काष्ठा iio_sysfs_trig *t;
	पूर्णांक ret;
	bool foundit = false;

	mutex_lock(&iio_sysfs_trig_list_mut);
	list_क्रम_each_entry(t, &iio_sysfs_trig_list, l)
		अगर (id == t->id) अणु
			foundit = true;
			अवरोध;
		पूर्ण
	अगर (foundit) अणु
		ret = -EINVAL;
		जाओ out1;
	पूर्ण
	t = kदो_स्मृति(माप(*t), GFP_KERNEL);
	अगर (t == शून्य) अणु
		ret = -ENOMEM;
		जाओ out1;
	पूर्ण
	t->id = id;
	t->trig = iio_trigger_alloc(&iio_sysfs_trig_dev, "sysfstrig%d", id);
	अगर (!t->trig) अणु
		ret = -ENOMEM;
		जाओ मुक्त_t;
	पूर्ण

	t->trig->dev.groups = iio_sysfs_trigger_attr_groups;
	t->trig->ops = &iio_sysfs_trigger_ops;
	iio_trigger_set_drvdata(t->trig, t);

	t->work = IRQ_WORK_INIT_HARD(iio_sysfs_trigger_work);

	ret = iio_trigger_रेजिस्टर(t->trig);
	अगर (ret)
		जाओ out2;
	list_add(&t->l, &iio_sysfs_trig_list);
	__module_get(THIS_MODULE);
	mutex_unlock(&iio_sysfs_trig_list_mut);
	वापस 0;

out2:
	iio_trigger_मुक्त(t->trig);
मुक्त_t:
	kमुक्त(t);
out1:
	mutex_unlock(&iio_sysfs_trig_list_mut);
	वापस ret;
पूर्ण

अटल पूर्णांक iio_sysfs_trigger_हटाओ(पूर्णांक id)
अणु
	bool foundit = false;
	काष्ठा iio_sysfs_trig *t;

	mutex_lock(&iio_sysfs_trig_list_mut);
	list_क्रम_each_entry(t, &iio_sysfs_trig_list, l)
		अगर (id == t->id) अणु
			foundit = true;
			अवरोध;
		पूर्ण
	अगर (!foundit) अणु
		mutex_unlock(&iio_sysfs_trig_list_mut);
		वापस -EINVAL;
	पूर्ण

	iio_trigger_unरेजिस्टर(t->trig);
	iio_trigger_मुक्त(t->trig);

	list_del(&t->l);
	kमुक्त(t);
	module_put(THIS_MODULE);
	mutex_unlock(&iio_sysfs_trig_list_mut);
	वापस 0;
पूर्ण


अटल पूर्णांक __init iio_sysfs_trig_init(व्योम)
अणु
	device_initialize(&iio_sysfs_trig_dev);
	dev_set_name(&iio_sysfs_trig_dev, "iio_sysfs_trigger");
	वापस device_add(&iio_sysfs_trig_dev);
पूर्ण
module_init(iio_sysfs_trig_init);

अटल व्योम __निकास iio_sysfs_trig_निकास(व्योम)
अणु
	device_unरेजिस्टर(&iio_sysfs_trig_dev);
पूर्ण
module_निकास(iio_sysfs_trig_निकास);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Sysfs based trigger for the iio subsystem");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:iio-trig-sysfs");
