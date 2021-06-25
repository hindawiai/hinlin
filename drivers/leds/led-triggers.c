<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LED Triggers Core
 *
 * Copyright 2005-2007 Openedhand Ltd.
 *
 * Author: Riअक्षरd Purdie <rpurdie@खोलोedhand.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/device.h>
#समावेश <linux/समयr.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/leds.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश "leds.h"

/*
 * Nests outside led_cdev->trigger_lock
 */
अटल DECLARE_RWSEM(triggers_list_lock);
LIST_HEAD(trigger_list);

 /* Used by LED Class */

अटल अंतरभूत bool
trigger_relevant(काष्ठा led_classdev *led_cdev, काष्ठा led_trigger *trig)
अणु
	वापस !trig->trigger_type || trig->trigger_type == led_cdev->trigger_type;
पूर्ण

sमाप_प्रकार led_trigger_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
			  काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			  loff_t pos, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा led_trigger *trig;
	पूर्णांक ret = count;

	mutex_lock(&led_cdev->led_access);

	अगर (led_sysfs_is_disabled(led_cdev)) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	अगर (sysfs_streq(buf, "none")) अणु
		led_trigger_हटाओ(led_cdev);
		जाओ unlock;
	पूर्ण

	करोwn_पढ़ो(&triggers_list_lock);
	list_क्रम_each_entry(trig, &trigger_list, next_trig) अणु
		अगर (sysfs_streq(buf, trig->name) && trigger_relevant(led_cdev, trig)) अणु
			करोwn_ग_लिखो(&led_cdev->trigger_lock);
			led_trigger_set(led_cdev, trig);
			up_ग_लिखो(&led_cdev->trigger_lock);

			up_पढ़ो(&triggers_list_lock);
			जाओ unlock;
		पूर्ण
	पूर्ण
	/* we come here only अगर buf matches no trigger */
	ret = -EINVAL;
	up_पढ़ो(&triggers_list_lock);

unlock:
	mutex_unlock(&led_cdev->led_access);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(led_trigger_ग_लिखो);

__म_लिखो(3, 4)
अटल पूर्णांक led_trigger_snम_लिखो(अक्षर *buf, sमाप_प्रकार size, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक i;

	बहु_शुरू(args, fmt);
	अगर (size <= 0)
		i = vsnम_लिखो(शून्य, 0, fmt, args);
	अन्यथा
		i = vscnम_लिखो(buf, size, fmt, args);
	बहु_पूर्ण(args);

	वापस i;
पूर्ण

अटल पूर्णांक led_trigger_क्रमmat(अक्षर *buf, माप_प्रकार size,
			      काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा led_trigger *trig;
	पूर्णांक len = led_trigger_snम_लिखो(buf, size, "%s",
				       led_cdev->trigger ? "none" : "[none]");

	list_क्रम_each_entry(trig, &trigger_list, next_trig) अणु
		bool hit;

		अगर (!trigger_relevant(led_cdev, trig))
			जारी;

		hit = led_cdev->trigger && !म_भेद(led_cdev->trigger->name, trig->name);

		len += led_trigger_snम_लिखो(buf + len, size - len,
					    " %s%s%s", hit ? "[" : "",
					    trig->name, hit ? "]" : "");
	पूर्ण

	len += led_trigger_snम_लिखो(buf + len, size - len, "\n");

	वापस len;
पूर्ण

/*
 * It was stupid to create 10000 cpu triggers, but we are stuck with it now.
 * Don't make that mistake again. We work around it here by creating binary
 * attribute, which is not limited by length. This is _not_ good design, करो not
 * copy it.
 */
sमाप_प्रकार led_trigger_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			काष्ठा bin_attribute *attr, अक्षर *buf,
			loff_t pos, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	व्योम *data;
	पूर्णांक len;

	करोwn_पढ़ो(&triggers_list_lock);
	करोwn_पढ़ो(&led_cdev->trigger_lock);

	len = led_trigger_क्रमmat(शून्य, 0, led_cdev);
	data = kvदो_स्मृति(len + 1, GFP_KERNEL);
	अगर (!data) अणु
		up_पढ़ो(&led_cdev->trigger_lock);
		up_पढ़ो(&triggers_list_lock);
		वापस -ENOMEM;
	पूर्ण
	len = led_trigger_क्रमmat(data, len + 1, led_cdev);

	up_पढ़ो(&led_cdev->trigger_lock);
	up_पढ़ो(&triggers_list_lock);

	len = memory_पढ़ो_from_buffer(buf, count, &pos, data, len);

	kvमुक्त(data);

	वापस len;
पूर्ण
EXPORT_SYMBOL_GPL(led_trigger_पढ़ो);

/* Caller must ensure led_cdev->trigger_lock held */
पूर्णांक led_trigger_set(काष्ठा led_classdev *led_cdev, काष्ठा led_trigger *trig)
अणु
	अचिन्हित दीर्घ flags;
	अक्षर *event = शून्य;
	अक्षर *envp[2];
	स्थिर अक्षर *name;
	पूर्णांक ret;

	अगर (!led_cdev->trigger && !trig)
		वापस 0;

	name = trig ? trig->name : "none";
	event = kaप्र_लिखो(GFP_KERNEL, "TRIGGER=%s", name);

	/* Remove any existing trigger */
	अगर (led_cdev->trigger) अणु
		ग_लिखो_lock_irqsave(&led_cdev->trigger->leddev_list_lock, flags);
		list_del(&led_cdev->trig_list);
		ग_लिखो_unlock_irqrestore(&led_cdev->trigger->leddev_list_lock,
			flags);
		cancel_work_sync(&led_cdev->set_brightness_work);
		led_stop_software_blink(led_cdev);
		अगर (led_cdev->trigger->deactivate)
			led_cdev->trigger->deactivate(led_cdev);
		device_हटाओ_groups(led_cdev->dev, led_cdev->trigger->groups);
		led_cdev->trigger = शून्य;
		led_cdev->trigger_data = शून्य;
		led_cdev->activated = false;
		led_set_brightness(led_cdev, LED_OFF);
	पूर्ण
	अगर (trig) अणु
		ग_लिखो_lock_irqsave(&trig->leddev_list_lock, flags);
		list_add_tail(&led_cdev->trig_list, &trig->led_cdevs);
		ग_लिखो_unlock_irqrestore(&trig->leddev_list_lock, flags);
		led_cdev->trigger = trig;

		अगर (trig->activate)
			ret = trig->activate(led_cdev);
		अन्यथा
			ret = 0;

		अगर (ret)
			जाओ err_activate;

		ret = device_add_groups(led_cdev->dev, trig->groups);
		अगर (ret) अणु
			dev_err(led_cdev->dev, "Failed to add trigger attributes\n");
			जाओ err_add_groups;
		पूर्ण
	पूर्ण

	अगर (event) अणु
		envp[0] = event;
		envp[1] = शून्य;
		अगर (kobject_uevent_env(&led_cdev->dev->kobj, KOBJ_CHANGE, envp))
			dev_err(led_cdev->dev,
				"%s: Error sending uevent\n", __func__);
		kमुक्त(event);
	पूर्ण

	वापस 0;

err_add_groups:

	अगर (trig->deactivate)
		trig->deactivate(led_cdev);
err_activate:

	ग_लिखो_lock_irqsave(&led_cdev->trigger->leddev_list_lock, flags);
	list_del(&led_cdev->trig_list);
	ग_लिखो_unlock_irqrestore(&led_cdev->trigger->leddev_list_lock, flags);
	led_cdev->trigger = शून्य;
	led_cdev->trigger_data = शून्य;
	led_set_brightness(led_cdev, LED_OFF);
	kमुक्त(event);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(led_trigger_set);

व्योम led_trigger_हटाओ(काष्ठा led_classdev *led_cdev)
अणु
	करोwn_ग_लिखो(&led_cdev->trigger_lock);
	led_trigger_set(led_cdev, शून्य);
	up_ग_लिखो(&led_cdev->trigger_lock);
पूर्ण
EXPORT_SYMBOL_GPL(led_trigger_हटाओ);

व्योम led_trigger_set_शेष(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा led_trigger *trig;

	अगर (!led_cdev->शेष_trigger)
		वापस;

	करोwn_पढ़ो(&triggers_list_lock);
	करोwn_ग_लिखो(&led_cdev->trigger_lock);
	list_क्रम_each_entry(trig, &trigger_list, next_trig) अणु
		अगर (!म_भेद(led_cdev->शेष_trigger, trig->name) &&
		    trigger_relevant(led_cdev, trig)) अणु
			led_cdev->flags |= LED_INIT_DEFAULT_TRIGGER;
			led_trigger_set(led_cdev, trig);
			अवरोध;
		पूर्ण
	पूर्ण
	up_ग_लिखो(&led_cdev->trigger_lock);
	up_पढ़ो(&triggers_list_lock);
पूर्ण
EXPORT_SYMBOL_GPL(led_trigger_set_शेष);

व्योम led_trigger_नाम_अटल(स्थिर अक्षर *name, काष्ठा led_trigger *trig)
अणु
	/* new name must be on a temporary string to prevent races */
	BUG_ON(name == trig->name);

	करोwn_ग_लिखो(&triggers_list_lock);
	/* this assumes that trig->name was originaly allocated to
	 * non स्थिरant storage */
	म_नकल((अक्षर *)trig->name, name);
	up_ग_लिखो(&triggers_list_lock);
पूर्ण
EXPORT_SYMBOL_GPL(led_trigger_नाम_अटल);

/* LED Trigger Interface */

पूर्णांक led_trigger_रेजिस्टर(काष्ठा led_trigger *trig)
अणु
	काष्ठा led_classdev *led_cdev;
	काष्ठा led_trigger *_trig;

	rwlock_init(&trig->leddev_list_lock);
	INIT_LIST_HEAD(&trig->led_cdevs);

	करोwn_ग_लिखो(&triggers_list_lock);
	/* Make sure the trigger's name isn't alपढ़ोy in use */
	list_क्रम_each_entry(_trig, &trigger_list, next_trig) अणु
		अगर (!म_भेद(_trig->name, trig->name) &&
		    (trig->trigger_type == _trig->trigger_type ||
		     !trig->trigger_type || !_trig->trigger_type)) अणु
			up_ग_लिखो(&triggers_list_lock);
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	/* Add to the list of led triggers */
	list_add_tail(&trig->next_trig, &trigger_list);
	up_ग_लिखो(&triggers_list_lock);

	/* Register with any LEDs that have this as a शेष trigger */
	करोwn_पढ़ो(&leds_list_lock);
	list_क्रम_each_entry(led_cdev, &leds_list, node) अणु
		करोwn_ग_लिखो(&led_cdev->trigger_lock);
		अगर (!led_cdev->trigger && led_cdev->शेष_trigger &&
		    !म_भेद(led_cdev->शेष_trigger, trig->name) &&
		    trigger_relevant(led_cdev, trig)) अणु
			led_cdev->flags |= LED_INIT_DEFAULT_TRIGGER;
			led_trigger_set(led_cdev, trig);
		पूर्ण
		up_ग_लिखो(&led_cdev->trigger_lock);
	पूर्ण
	up_पढ़ो(&leds_list_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(led_trigger_रेजिस्टर);

व्योम led_trigger_unरेजिस्टर(काष्ठा led_trigger *trig)
अणु
	काष्ठा led_classdev *led_cdev;

	अगर (list_empty_careful(&trig->next_trig))
		वापस;

	/* Remove from the list of led triggers */
	करोwn_ग_लिखो(&triggers_list_lock);
	list_del_init(&trig->next_trig);
	up_ग_लिखो(&triggers_list_lock);

	/* Remove anyone actively using this trigger */
	करोwn_पढ़ो(&leds_list_lock);
	list_क्रम_each_entry(led_cdev, &leds_list, node) अणु
		करोwn_ग_लिखो(&led_cdev->trigger_lock);
		अगर (led_cdev->trigger == trig)
			led_trigger_set(led_cdev, शून्य);
		up_ग_लिखो(&led_cdev->trigger_lock);
	पूर्ण
	up_पढ़ो(&leds_list_lock);
पूर्ण
EXPORT_SYMBOL_GPL(led_trigger_unरेजिस्टर);

अटल व्योम devm_led_trigger_release(काष्ठा device *dev, व्योम *res)
अणु
	led_trigger_unरेजिस्टर(*(काष्ठा led_trigger **)res);
पूर्ण

पूर्णांक devm_led_trigger_रेजिस्टर(काष्ठा device *dev,
			      काष्ठा led_trigger *trig)
अणु
	काष्ठा led_trigger **dr;
	पूर्णांक rc;

	dr = devres_alloc(devm_led_trigger_release, माप(*dr),
			  GFP_KERNEL);
	अगर (!dr)
		वापस -ENOMEM;

	*dr = trig;

	rc = led_trigger_रेजिस्टर(trig);
	अगर (rc)
		devres_मुक्त(dr);
	अन्यथा
		devres_add(dev, dr);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(devm_led_trigger_रेजिस्टर);

/* Simple LED Trigger Interface */

व्योम led_trigger_event(काष्ठा led_trigger *trig,
			क्रमागत led_brightness brightness)
अणु
	काष्ठा led_classdev *led_cdev;
	अचिन्हित दीर्घ flags;

	अगर (!trig)
		वापस;

	पढ़ो_lock_irqsave(&trig->leddev_list_lock, flags);
	list_क्रम_each_entry(led_cdev, &trig->led_cdevs, trig_list)
		led_set_brightness(led_cdev, brightness);
	पढ़ो_unlock_irqrestore(&trig->leddev_list_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(led_trigger_event);

अटल व्योम led_trigger_blink_setup(काष्ठा led_trigger *trig,
			     अचिन्हित दीर्घ *delay_on,
			     अचिन्हित दीर्घ *delay_off,
			     पूर्णांक oneshot,
			     पूर्णांक invert)
अणु
	काष्ठा led_classdev *led_cdev;
	अचिन्हित दीर्घ flags;

	अगर (!trig)
		वापस;

	पढ़ो_lock_irqsave(&trig->leddev_list_lock, flags);
	list_क्रम_each_entry(led_cdev, &trig->led_cdevs, trig_list) अणु
		अगर (oneshot)
			led_blink_set_oneshot(led_cdev, delay_on, delay_off,
					      invert);
		अन्यथा
			led_blink_set(led_cdev, delay_on, delay_off);
	पूर्ण
	पढ़ो_unlock_irqrestore(&trig->leddev_list_lock, flags);
पूर्ण

व्योम led_trigger_blink(काष्ठा led_trigger *trig,
		       अचिन्हित दीर्घ *delay_on,
		       अचिन्हित दीर्घ *delay_off)
अणु
	led_trigger_blink_setup(trig, delay_on, delay_off, 0, 0);
पूर्ण
EXPORT_SYMBOL_GPL(led_trigger_blink);

व्योम led_trigger_blink_oneshot(काष्ठा led_trigger *trig,
			       अचिन्हित दीर्घ *delay_on,
			       अचिन्हित दीर्घ *delay_off,
			       पूर्णांक invert)
अणु
	led_trigger_blink_setup(trig, delay_on, delay_off, 1, invert);
पूर्ण
EXPORT_SYMBOL_GPL(led_trigger_blink_oneshot);

व्योम led_trigger_रेजिस्टर_simple(स्थिर अक्षर *name, काष्ठा led_trigger **tp)
अणु
	काष्ठा led_trigger *trig;
	पूर्णांक err;

	trig = kzalloc(माप(काष्ठा led_trigger), GFP_KERNEL);

	अगर (trig) अणु
		trig->name = name;
		err = led_trigger_रेजिस्टर(trig);
		अगर (err < 0) अणु
			kमुक्त(trig);
			trig = शून्य;
			pr_warn("LED trigger %s failed to register (%d)\n",
				name, err);
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_warn("LED trigger %s failed to register (no memory)\n",
			name);
	पूर्ण
	*tp = trig;
पूर्ण
EXPORT_SYMBOL_GPL(led_trigger_रेजिस्टर_simple);

व्योम led_trigger_unरेजिस्टर_simple(काष्ठा led_trigger *trig)
अणु
	अगर (trig)
		led_trigger_unरेजिस्टर(trig);
	kमुक्त(trig);
पूर्ण
EXPORT_SYMBOL_GPL(led_trigger_unरेजिस्टर_simple);
