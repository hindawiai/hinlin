<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Wakeup statistics in sysfs
 *
 * Copyright (c) 2019 Linux Foundation
 * Copyright (c) 2019 Greg Kroah-Harपंचांगan <gregkh@linuxfoundation.org>
 * Copyright (c) 2019 Google Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/idr.h>
#समावेश <linux/init.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kobject.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयkeeping.h>

#समावेश "power.h"

अटल काष्ठा class *wakeup_class;

#घोषणा wakeup_attr(_name)						\
अटल sमाप_प्रकार _name##_show(काष्ठा device *dev,				\
			    काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा wakeup_source *ws = dev_get_drvdata(dev);		\
									\
	वापस sysfs_emit(buf, "%lu\n", ws->_name);			\
पूर्ण									\
अटल DEVICE_ATTR_RO(_name)

wakeup_attr(active_count);
wakeup_attr(event_count);
wakeup_attr(wakeup_count);
wakeup_attr(expire_count);

अटल sमाप_प्रकार active_समय_ms_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा wakeup_source *ws = dev_get_drvdata(dev);
	kसमय_प्रकार active_समय =
		ws->active ? kसमय_sub(kसमय_get(), ws->last_समय) : 0;

	वापस sysfs_emit(buf, "%lld\n", kसमय_प्रकारo_ms(active_समय));
पूर्ण
अटल DEVICE_ATTR_RO(active_समय_ms);

अटल sमाप_प्रकार total_समय_ms_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा wakeup_source *ws = dev_get_drvdata(dev);
	kसमय_प्रकार active_समय;
	kसमय_प्रकार total_समय = ws->total_समय;

	अगर (ws->active) अणु
		active_समय = kसमय_sub(kसमय_get(), ws->last_समय);
		total_समय = kसमय_add(total_समय, active_समय);
	पूर्ण

	वापस sysfs_emit(buf, "%lld\n", kसमय_प्रकारo_ms(total_समय));
पूर्ण
अटल DEVICE_ATTR_RO(total_समय_ms);

अटल sमाप_प्रकार max_समय_ms_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा wakeup_source *ws = dev_get_drvdata(dev);
	kसमय_प्रकार active_समय;
	kसमय_प्रकार max_समय = ws->max_समय;

	अगर (ws->active) अणु
		active_समय = kसमय_sub(kसमय_get(), ws->last_समय);
		अगर (active_समय > max_समय)
			max_समय = active_समय;
	पूर्ण

	वापस sysfs_emit(buf, "%lld\n", kसमय_प्रकारo_ms(max_समय));
पूर्ण
अटल DEVICE_ATTR_RO(max_समय_ms);

अटल sमाप_प्रकार last_change_ms_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा wakeup_source *ws = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%lld\n", kसमय_प्रकारo_ms(ws->last_समय));
पूर्ण
अटल DEVICE_ATTR_RO(last_change_ms);

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा wakeup_source *ws = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%s\n", ws->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल sमाप_प्रकार prevent_suspend_समय_ms_show(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा wakeup_source *ws = dev_get_drvdata(dev);
	kसमय_प्रकार prevent_sleep_समय = ws->prevent_sleep_समय;

	अगर (ws->active && ws->स्वतःsleep_enabled) अणु
		prevent_sleep_समय = kसमय_add(prevent_sleep_समय,
			kसमय_sub(kसमय_get(), ws->start_prevent_समय));
	पूर्ण

	वापस sysfs_emit(buf, "%lld\n", kसमय_प्रकारo_ms(prevent_sleep_समय));
पूर्ण
अटल DEVICE_ATTR_RO(prevent_suspend_समय_ms);

अटल काष्ठा attribute *wakeup_source_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_active_count.attr,
	&dev_attr_event_count.attr,
	&dev_attr_wakeup_count.attr,
	&dev_attr_expire_count.attr,
	&dev_attr_active_समय_ms.attr,
	&dev_attr_total_समय_ms.attr,
	&dev_attr_max_समय_ms.attr,
	&dev_attr_last_change_ms.attr,
	&dev_attr_prevent_suspend_समय_ms.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(wakeup_source);

अटल व्योम device_create_release(काष्ठा device *dev)
अणु
	kमुक्त(dev);
पूर्ण

अटल काष्ठा device *wakeup_source_device_create(काष्ठा device *parent,
						  काष्ठा wakeup_source *ws)
अणु
	काष्ठा device *dev = शून्य;
	पूर्णांक retval;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		retval = -ENOMEM;
		जाओ error;
	पूर्ण

	device_initialize(dev);
	dev->devt = MKDEV(0, 0);
	dev->class = wakeup_class;
	dev->parent = parent;
	dev->groups = wakeup_source_groups;
	dev->release = device_create_release;
	dev_set_drvdata(dev, ws);
	device_set_pm_not_required(dev);

	retval = dev_set_name(dev, "wakeup%d", ws->id);
	अगर (retval)
		जाओ error;

	retval = device_add(dev);
	अगर (retval)
		जाओ error;

	वापस dev;

error:
	put_device(dev);
	वापस ERR_PTR(retval);
पूर्ण

/**
 * wakeup_source_sysfs_add - Add wakeup_source attributes to sysfs.
 * @parent: Device given wakeup source is associated with (or शून्य अगर भव).
 * @ws: Wakeup source to be added in sysfs.
 */
पूर्णांक wakeup_source_sysfs_add(काष्ठा device *parent, काष्ठा wakeup_source *ws)
अणु
	काष्ठा device *dev;

	dev = wakeup_source_device_create(parent, ws);
	अगर (IS_ERR(dev))
		वापस PTR_ERR(dev);
	ws->dev = dev;

	वापस 0;
पूर्ण

/**
 * pm_wakeup_source_sysfs_add - Add wakeup_source attributes to sysfs
 * क्रम a device अगर they're missing.
 * @parent: Device given wakeup source is associated with
 */
पूर्णांक pm_wakeup_source_sysfs_add(काष्ठा device *parent)
अणु
	अगर (!parent->घातer.wakeup || parent->घातer.wakeup->dev)
		वापस 0;

	वापस wakeup_source_sysfs_add(parent, parent->घातer.wakeup);
पूर्ण

/**
 * wakeup_source_sysfs_हटाओ - Remove wakeup_source attributes from sysfs.
 * @ws: Wakeup source to be हटाओd from sysfs.
 */
व्योम wakeup_source_sysfs_हटाओ(काष्ठा wakeup_source *ws)
अणु
	device_unरेजिस्टर(ws->dev);
पूर्ण

अटल पूर्णांक __init wakeup_sources_sysfs_init(व्योम)
अणु
	wakeup_class = class_create(THIS_MODULE, "wakeup");

	वापस PTR_ERR_OR_ZERO(wakeup_class);
पूर्ण
postcore_initcall(wakeup_sources_sysfs_init);
