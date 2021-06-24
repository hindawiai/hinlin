<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support क्रम polling mode क्रम input devices.
 */

#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश "input-poller.h"

काष्ठा input_dev_poller अणु
	व्योम (*poll)(काष्ठा input_dev *dev);

	अचिन्हित पूर्णांक poll_पूर्णांकerval; /* msec */
	अचिन्हित पूर्णांक poll_पूर्णांकerval_max; /* msec */
	अचिन्हित पूर्णांक poll_पूर्णांकerval_min; /* msec */

	काष्ठा input_dev *input;
	काष्ठा delayed_work work;
पूर्ण;

अटल व्योम input_dev_poller_queue_work(काष्ठा input_dev_poller *poller)
अणु
	अचिन्हित दीर्घ delay;

	delay = msecs_to_jअगरfies(poller->poll_पूर्णांकerval);
	अगर (delay >= HZ)
		delay = round_jअगरfies_relative(delay);

	queue_delayed_work(प्रणाली_मुक्तzable_wq, &poller->work, delay);
पूर्ण

अटल व्योम input_dev_poller_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा input_dev_poller *poller =
		container_of(work, काष्ठा input_dev_poller, work.work);

	poller->poll(poller->input);
	input_dev_poller_queue_work(poller);
पूर्ण

व्योम input_dev_poller_finalize(काष्ठा input_dev_poller *poller)
अणु
	अगर (!poller->poll_पूर्णांकerval)
		poller->poll_पूर्णांकerval = 500;
	अगर (!poller->poll_पूर्णांकerval_max)
		poller->poll_पूर्णांकerval_max = poller->poll_पूर्णांकerval;
पूर्ण

व्योम input_dev_poller_start(काष्ठा input_dev_poller *poller)
अणु
	/* Only start polling अगर polling is enabled */
	अगर (poller->poll_पूर्णांकerval > 0) अणु
		poller->poll(poller->input);
		input_dev_poller_queue_work(poller);
	पूर्ण
पूर्ण

व्योम input_dev_poller_stop(काष्ठा input_dev_poller *poller)
अणु
	cancel_delayed_work_sync(&poller->work);
पूर्ण

पूर्णांक input_setup_polling(काष्ठा input_dev *dev,
			व्योम (*poll_fn)(काष्ठा input_dev *dev))
अणु
	काष्ठा input_dev_poller *poller;

	poller = kzalloc(माप(*poller), GFP_KERNEL);
	अगर (!poller) अणु
		/*
		 * We want to show message even though kzalloc() may have
		 * prपूर्णांकed backtrace as knowing what instance of input
		 * device we were dealing with is helpful.
		 */
		dev_err(dev->dev.parent ?: &dev->dev,
			"%s: unable to allocate poller structure\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	INIT_DELAYED_WORK(&poller->work, input_dev_poller_work);
	poller->input = dev;
	poller->poll = poll_fn;

	dev->poller = poller;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(input_setup_polling);

अटल bool input_dev_ensure_poller(काष्ठा input_dev *dev)
अणु
	अगर (!dev->poller) अणु
		dev_err(dev->dev.parent ?: &dev->dev,
			"poller structure has not been set up\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम input_set_poll_पूर्णांकerval(काष्ठा input_dev *dev, अचिन्हित पूर्णांक पूर्णांकerval)
अणु
	अगर (input_dev_ensure_poller(dev))
		dev->poller->poll_पूर्णांकerval = पूर्णांकerval;
पूर्ण
EXPORT_SYMBOL(input_set_poll_पूर्णांकerval);

व्योम input_set_min_poll_पूर्णांकerval(काष्ठा input_dev *dev, अचिन्हित पूर्णांक पूर्णांकerval)
अणु
	अगर (input_dev_ensure_poller(dev))
		dev->poller->poll_पूर्णांकerval_min = पूर्णांकerval;
पूर्ण
EXPORT_SYMBOL(input_set_min_poll_पूर्णांकerval);

व्योम input_set_max_poll_पूर्णांकerval(काष्ठा input_dev *dev, अचिन्हित पूर्णांक पूर्णांकerval)
अणु
	अगर (input_dev_ensure_poller(dev))
		dev->poller->poll_पूर्णांकerval_max = पूर्णांकerval;
पूर्ण
EXPORT_SYMBOL(input_set_max_poll_पूर्णांकerval);

पूर्णांक input_get_poll_पूर्णांकerval(काष्ठा input_dev *dev)
अणु
	अगर (!dev->poller)
		वापस -EINVAL;

	वापस dev->poller->poll_पूर्णांकerval;
पूर्ण
EXPORT_SYMBOL(input_get_poll_पूर्णांकerval);

/* SYSFS पूर्णांकerface */

अटल sमाप_प्रकार input_dev_get_poll_पूर्णांकerval(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा input_dev *input = to_input_dev(dev);

	वापस प्र_लिखो(buf, "%d\n", input->poller->poll_पूर्णांकerval);
पूर्ण

अटल sमाप_प्रकार input_dev_set_poll_पूर्णांकerval(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा input_dev *input = to_input_dev(dev);
	काष्ठा input_dev_poller *poller = input->poller;
	अचिन्हित पूर्णांक पूर्णांकerval;
	पूर्णांक err;

	err = kstrtouपूर्णांक(buf, 0, &पूर्णांकerval);
	अगर (err)
		वापस err;

	अगर (पूर्णांकerval < poller->poll_पूर्णांकerval_min)
		वापस -EINVAL;

	अगर (पूर्णांकerval > poller->poll_पूर्णांकerval_max)
		वापस -EINVAL;

	mutex_lock(&input->mutex);

	poller->poll_पूर्णांकerval = पूर्णांकerval;

	अगर (input_device_enabled(input)) अणु
		cancel_delayed_work_sync(&poller->work);
		अगर (poller->poll_पूर्णांकerval > 0)
			input_dev_poller_queue_work(poller);
	पूर्ण

	mutex_unlock(&input->mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(poll, 0644,
		   input_dev_get_poll_पूर्णांकerval, input_dev_set_poll_पूर्णांकerval);

अटल sमाप_प्रकार input_dev_get_poll_max(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा input_dev *input = to_input_dev(dev);

	वापस प्र_लिखो(buf, "%d\n", input->poller->poll_पूर्णांकerval_max);
पूर्ण

अटल DEVICE_ATTR(max, 0444, input_dev_get_poll_max, शून्य);

अटल sमाप_प्रकार input_dev_get_poll_min(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा input_dev *input = to_input_dev(dev);

	वापस प्र_लिखो(buf, "%d\n", input->poller->poll_पूर्णांकerval_min);
पूर्ण

अटल DEVICE_ATTR(min, 0444, input_dev_get_poll_min, शून्य);

अटल umode_t input_poller_attrs_visible(काष्ठा kobject *kobj,
					  काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा input_dev *input = to_input_dev(dev);

	वापस input->poller ? attr->mode : 0;
पूर्ण

अटल काष्ठा attribute *input_poller_attrs[] = अणु
	&dev_attr_poll.attr,
	&dev_attr_max.attr,
	&dev_attr_min.attr,
	शून्य
पूर्ण;

काष्ठा attribute_group input_poller_attribute_group = अणु
	.is_visible	= input_poller_attrs_visible,
	.attrs		= input_poller_attrs,
पूर्ण;
