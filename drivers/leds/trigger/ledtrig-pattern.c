<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * LED pattern trigger
 *
 * Idea discussed with Pavel Machek. Raphael Teysseyre implemented
 * the first version, Baolin Wang simplअगरied and improved the approach.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>

#घोषणा MAX_PATTERNS		1024
/*
 * When करोing gradual dimming, the led brightness will be updated
 * every 50 milliseconds.
 */
#घोषणा UPDATE_INTERVAL		50

काष्ठा pattern_trig_data अणु
	काष्ठा led_classdev *led_cdev;
	काष्ठा led_pattern patterns[MAX_PATTERNS];
	काष्ठा led_pattern *curr;
	काष्ठा led_pattern *next;
	काष्ठा mutex lock;
	u32 npatterns;
	पूर्णांक repeat;
	पूर्णांक last_repeat;
	पूर्णांक delta_t;
	bool is_indefinite;
	bool is_hw_pattern;
	काष्ठा समयr_list समयr;
पूर्ण;

अटल व्योम pattern_trig_update_patterns(काष्ठा pattern_trig_data *data)
अणु
	data->curr = data->next;
	अगर (!data->is_indefinite && data->curr == data->patterns)
		data->repeat--;

	अगर (data->next == data->patterns + data->npatterns - 1)
		data->next = data->patterns;
	अन्यथा
		data->next++;

	data->delta_t = 0;
पूर्ण

अटल पूर्णांक pattern_trig_compute_brightness(काष्ठा pattern_trig_data *data)
अणु
	पूर्णांक step_brightness;

	/*
	 * If current tuple's duration is less than the dimming पूर्णांकerval,
	 * we should treat it as a step change of brightness instead of
	 * करोing gradual dimming.
	 */
	अगर (data->delta_t == 0 || data->curr->delta_t < UPDATE_INTERVAL)
		वापस data->curr->brightness;

	step_brightness = असल(data->next->brightness - data->curr->brightness);
	step_brightness = data->delta_t * step_brightness / data->curr->delta_t;

	अगर (data->next->brightness > data->curr->brightness)
		वापस data->curr->brightness + step_brightness;
	अन्यथा
		वापस data->curr->brightness - step_brightness;
पूर्ण

अटल व्योम pattern_trig_समयr_function(काष्ठा समयr_list *t)
अणु
	काष्ठा pattern_trig_data *data = from_समयr(data, t, समयr);

	क्रम (;;) अणु
		अगर (!data->is_indefinite && !data->repeat)
			अवरोध;

		अगर (data->curr->brightness == data->next->brightness) अणु
			/* Step change of brightness */
			led_set_brightness(data->led_cdev,
					   data->curr->brightness);
			mod_समयr(&data->समयr,
				  jअगरfies + msecs_to_jअगरfies(data->curr->delta_t));
			अगर (!data->next->delta_t) अणु
				/* Skip the tuple with zero duration */
				pattern_trig_update_patterns(data);
			पूर्ण
			/* Select next tuple */
			pattern_trig_update_patterns(data);
		पूर्ण अन्यथा अणु
			/* Gradual dimming */

			/*
			 * If the accumulation समय is larger than current
			 * tuple's duration, we should go next one and re-check
			 * अगर we repeated करोne.
			 */
			अगर (data->delta_t > data->curr->delta_t) अणु
				pattern_trig_update_patterns(data);
				जारी;
			पूर्ण

			led_set_brightness(data->led_cdev,
					   pattern_trig_compute_brightness(data));
			mod_समयr(&data->समयr,
				  jअगरfies + msecs_to_jअगरfies(UPDATE_INTERVAL));

			/* Accumulate the gradual dimming समय */
			data->delta_t += UPDATE_INTERVAL;
		पूर्ण

		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक pattern_trig_start_pattern(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा pattern_trig_data *data = led_cdev->trigger_data;

	अगर (!data->npatterns)
		वापस 0;

	अगर (data->is_hw_pattern) अणु
		वापस led_cdev->pattern_set(led_cdev, data->patterns,
					     data->npatterns, data->repeat);
	पूर्ण

	/* At least 2 tuples क्रम software pattern. */
	अगर (data->npatterns < 2)
		वापस -EINVAL;

	data->delta_t = 0;
	data->curr = data->patterns;
	data->next = data->patterns + 1;
	data->समयr.expires = jअगरfies;
	add_समयr(&data->समयr);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार repeat_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा pattern_trig_data *data = led_cdev->trigger_data;
	पूर्णांक repeat;

	mutex_lock(&data->lock);

	repeat = data->last_repeat;

	mutex_unlock(&data->lock);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", repeat);
पूर्ण

अटल sमाप_प्रकार repeat_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा pattern_trig_data *data = led_cdev->trigger_data;
	पूर्णांक err, res;

	err = kstrtos32(buf, 10, &res);
	अगर (err)
		वापस err;

	/* Number 0 and negative numbers except -1 are invalid. */
	अगर (res < -1 || res == 0)
		वापस -EINVAL;

	mutex_lock(&data->lock);

	del_समयr_sync(&data->समयr);

	अगर (data->is_hw_pattern)
		led_cdev->pattern_clear(led_cdev);

	data->last_repeat = data->repeat = res;
	/* -1 means repeat indefinitely */
	अगर (data->repeat == -1)
		data->is_indefinite = true;
	अन्यथा
		data->is_indefinite = false;

	err = pattern_trig_start_pattern(led_cdev);

	mutex_unlock(&data->lock);
	वापस err < 0 ? err : count;
पूर्ण

अटल DEVICE_ATTR_RW(repeat);

अटल sमाप_प्रकार pattern_trig_show_patterns(काष्ठा pattern_trig_data *data,
					  अक्षर *buf, bool hw_pattern)
अणु
	sमाप_प्रकार count = 0;
	पूर्णांक i;

	mutex_lock(&data->lock);

	अगर (!data->npatterns || (data->is_hw_pattern ^ hw_pattern))
		जाओ out;

	क्रम (i = 0; i < data->npatterns; i++) अणु
		count += scnम_लिखो(buf + count, PAGE_SIZE - count,
				   "%d %u ",
				   data->patterns[i].brightness,
				   data->patterns[i].delta_t);
	पूर्ण

	buf[count - 1] = '\n';

out:
	mutex_unlock(&data->lock);
	वापस count;
पूर्ण

अटल पूर्णांक pattern_trig_store_patterns_string(काष्ठा pattern_trig_data *data,
					      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ccount, cr, offset = 0;

	जबतक (offset < count - 1 && data->npatterns < MAX_PATTERNS) अणु
		cr = 0;
		ccount = माला_पूछो(buf + offset, "%u %u %n",
				&data->patterns[data->npatterns].brightness,
				&data->patterns[data->npatterns].delta_t, &cr);

		अगर (ccount != 2 ||
		    data->patterns[data->npatterns].brightness > data->led_cdev->max_brightness) अणु
			data->npatterns = 0;
			वापस -EINVAL;
		पूर्ण

		offset += cr;
		data->npatterns++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pattern_trig_store_patterns_पूर्णांक(काष्ठा pattern_trig_data *data,
					   स्थिर u32 *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i += 2) अणु
		data->patterns[data->npatterns].brightness = buf[i];
		data->patterns[data->npatterns].delta_t = buf[i + 1];
		data->npatterns++;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार pattern_trig_store_patterns(काष्ठा led_classdev *led_cdev,
					   स्थिर अक्षर *buf, स्थिर u32 *buf_पूर्णांक,
					   माप_प्रकार count, bool hw_pattern)
अणु
	काष्ठा pattern_trig_data *data = led_cdev->trigger_data;
	पूर्णांक err = 0;

	mutex_lock(&data->lock);

	del_समयr_sync(&data->समयr);

	अगर (data->is_hw_pattern)
		led_cdev->pattern_clear(led_cdev);

	data->is_hw_pattern = hw_pattern;
	data->npatterns = 0;

	अगर (buf)
		err = pattern_trig_store_patterns_string(data, buf, count);
	अन्यथा
		err = pattern_trig_store_patterns_पूर्णांक(data, buf_पूर्णांक, count);
	अगर (err)
		जाओ out;

	err = pattern_trig_start_pattern(led_cdev);
	अगर (err)
		data->npatterns = 0;

out:
	mutex_unlock(&data->lock);
	वापस err < 0 ? err : count;
पूर्ण

अटल sमाप_प्रकार pattern_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा pattern_trig_data *data = led_cdev->trigger_data;

	वापस pattern_trig_show_patterns(data, buf, false);
पूर्ण

अटल sमाप_प्रकार pattern_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);

	वापस pattern_trig_store_patterns(led_cdev, buf, शून्य, count, false);
पूर्ण

अटल DEVICE_ATTR_RW(pattern);

अटल sमाप_प्रकार hw_pattern_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा pattern_trig_data *data = led_cdev->trigger_data;

	वापस pattern_trig_show_patterns(data, buf, true);
पूर्ण

अटल sमाप_प्रकार hw_pattern_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);

	वापस pattern_trig_store_patterns(led_cdev, buf, शून्य, count, true);
पूर्ण

अटल DEVICE_ATTR_RW(hw_pattern);

अटल umode_t pattern_trig_attrs_mode(काष्ठा kobject *kobj,
				       काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);

	अगर (attr == &dev_attr_repeat.attr || attr == &dev_attr_pattern.attr)
		वापस attr->mode;
	अन्यथा अगर (attr == &dev_attr_hw_pattern.attr && led_cdev->pattern_set)
		वापस attr->mode;

	वापस 0;
पूर्ण

अटल काष्ठा attribute *pattern_trig_attrs[] = अणु
	&dev_attr_pattern.attr,
	&dev_attr_hw_pattern.attr,
	&dev_attr_repeat.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group pattern_trig_group = अणु
	.attrs = pattern_trig_attrs,
	.is_visible = pattern_trig_attrs_mode,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *pattern_trig_groups[] = अणु
	&pattern_trig_group,
	शून्य,
पूर्ण;

अटल व्योम pattern_init(काष्ठा led_classdev *led_cdev)
अणु
	अचिन्हित पूर्णांक size = 0;
	u32 *pattern;
	पूर्णांक err;

	pattern = led_get_शेष_pattern(led_cdev, &size);
	अगर (!pattern)
		वापस;

	अगर (size % 2) अणु
		dev_warn(led_cdev->dev, "Expected pattern of tuples\n");
		जाओ out;
	पूर्ण

	err = pattern_trig_store_patterns(led_cdev, शून्य, pattern, size, false);
	अगर (err < 0)
		dev_warn(led_cdev->dev,
			 "Pattern initialization failed with error %d\n", err);

out:
	kमुक्त(pattern);
पूर्ण

अटल पूर्णांक pattern_trig_activate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा pattern_trig_data *data;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	अगर (!!led_cdev->pattern_set ^ !!led_cdev->pattern_clear) अणु
		dev_warn(led_cdev->dev,
			 "Hardware pattern ops validation failed\n");
		led_cdev->pattern_set = शून्य;
		led_cdev->pattern_clear = शून्य;
	पूर्ण

	data->is_indefinite = true;
	data->last_repeat = -1;
	mutex_init(&data->lock);
	data->led_cdev = led_cdev;
	led_set_trigger_data(led_cdev, data);
	समयr_setup(&data->समयr, pattern_trig_समयr_function, 0);
	led_cdev->activated = true;

	अगर (led_cdev->flags & LED_INIT_DEFAULT_TRIGGER) अणु
		pattern_init(led_cdev);
		/*
		 * Mark as initialized even on pattern_init() error because
		 * any consecutive call to it would produce the same error.
		 */
		led_cdev->flags &= ~LED_INIT_DEFAULT_TRIGGER;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pattern_trig_deactivate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा pattern_trig_data *data = led_cdev->trigger_data;

	अगर (!led_cdev->activated)
		वापस;

	अगर (led_cdev->pattern_clear)
		led_cdev->pattern_clear(led_cdev);

	del_समयr_sync(&data->समयr);

	led_set_brightness(led_cdev, LED_OFF);
	kमुक्त(data);
	led_cdev->activated = false;
पूर्ण

अटल काष्ठा led_trigger pattern_led_trigger = अणु
	.name = "pattern",
	.activate = pattern_trig_activate,
	.deactivate = pattern_trig_deactivate,
	.groups = pattern_trig_groups,
पूर्ण;

अटल पूर्णांक __init pattern_trig_init(व्योम)
अणु
	वापस led_trigger_रेजिस्टर(&pattern_led_trigger);
पूर्ण

अटल व्योम __निकास pattern_trig_निकास(व्योम)
अणु
	led_trigger_unरेजिस्टर(&pattern_led_trigger);
पूर्ण

module_init(pattern_trig_init);
module_निकास(pattern_trig_निकास);

MODULE_AUTHOR("Raphael Teysseyre <rteysseyre@gmail.com>");
MODULE_AUTHOR("Baolin Wang <baolin.wang@linaro.org>");
MODULE_DESCRIPTION("LED Pattern trigger");
MODULE_LICENSE("GPL v2");
