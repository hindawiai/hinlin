<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/devfreq/governor_userspace.c
 *
 *  Copyright (C) 2011 Samsung Electronics
 *	MyungJoo Ham <myungjoo.ham@samsung.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/devfreq.h>
#समावेश <linux/pm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश "governor.h"

काष्ठा userspace_data अणु
	अचिन्हित दीर्घ user_frequency;
	bool valid;
पूर्ण;

अटल पूर्णांक devfreq_userspace_func(काष्ठा devfreq *df, अचिन्हित दीर्घ *freq)
अणु
	काष्ठा userspace_data *data = df->data;

	अगर (data->valid)
		*freq = data->user_frequency;
	अन्यथा
		*freq = df->previous_freq; /* No user freq specअगरied yet */

	वापस 0;
पूर्ण

अटल sमाप_प्रकार store_freq(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा devfreq *devfreq = to_devfreq(dev);
	काष्ठा userspace_data *data;
	अचिन्हित दीर्घ wanted;
	पूर्णांक err = 0;

	mutex_lock(&devfreq->lock);
	data = devfreq->data;

	माला_पूछो(buf, "%lu", &wanted);
	data->user_frequency = wanted;
	data->valid = true;
	err = update_devfreq(devfreq);
	अगर (err == 0)
		err = count;
	mutex_unlock(&devfreq->lock);
	वापस err;
पूर्ण

अटल sमाप_प्रकार show_freq(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा devfreq *devfreq = to_devfreq(dev);
	काष्ठा userspace_data *data;
	पूर्णांक err = 0;

	mutex_lock(&devfreq->lock);
	data = devfreq->data;

	अगर (data->valid)
		err = प्र_लिखो(buf, "%lu\n", data->user_frequency);
	अन्यथा
		err = प्र_लिखो(buf, "undefined\n");
	mutex_unlock(&devfreq->lock);
	वापस err;
पूर्ण

अटल DEVICE_ATTR(set_freq, 0644, show_freq, store_freq);
अटल काष्ठा attribute *dev_entries[] = अणु
	&dev_attr_set_freq.attr,
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group dev_attr_group = अणु
	.name	= DEVFREQ_GOV_USERSPACE,
	.attrs	= dev_entries,
पूर्ण;

अटल पूर्णांक userspace_init(काष्ठा devfreq *devfreq)
अणु
	पूर्णांक err = 0;
	काष्ठा userspace_data *data = kzalloc(माप(काष्ठा userspace_data),
					      GFP_KERNEL);

	अगर (!data) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण
	data->valid = false;
	devfreq->data = data;

	err = sysfs_create_group(&devfreq->dev.kobj, &dev_attr_group);
out:
	वापस err;
पूर्ण

अटल व्योम userspace_निकास(काष्ठा devfreq *devfreq)
अणु
	/*
	 * Remove the sysfs entry, unless this is being called after
	 * device_del(), which should have करोne this alपढ़ोy via kobject_del().
	 */
	अगर (devfreq->dev.kobj.sd)
		sysfs_हटाओ_group(&devfreq->dev.kobj, &dev_attr_group);

	kमुक्त(devfreq->data);
	devfreq->data = शून्य;
पूर्ण

अटल पूर्णांक devfreq_userspace_handler(काष्ठा devfreq *devfreq,
			अचिन्हित पूर्णांक event, व्योम *data)
अणु
	पूर्णांक ret = 0;

	चयन (event) अणु
	हाल DEVFREQ_GOV_START:
		ret = userspace_init(devfreq);
		अवरोध;
	हाल DEVFREQ_GOV_STOP:
		userspace_निकास(devfreq);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा devfreq_governor devfreq_userspace = अणु
	.name = DEVFREQ_GOV_USERSPACE,
	.get_target_freq = devfreq_userspace_func,
	.event_handler = devfreq_userspace_handler,
पूर्ण;

अटल पूर्णांक __init devfreq_userspace_init(व्योम)
अणु
	वापस devfreq_add_governor(&devfreq_userspace);
पूर्ण
subsys_initcall(devfreq_userspace_init);

अटल व्योम __निकास devfreq_userspace_निकास(व्योम)
अणु
	पूर्णांक ret;

	ret = devfreq_हटाओ_governor(&devfreq_userspace);
	अगर (ret)
		pr_err("%s: failed remove governor %d\n", __func__, ret);

	वापस;
पूर्ण
module_निकास(devfreq_userspace_निकास);
MODULE_LICENSE("GPL");
