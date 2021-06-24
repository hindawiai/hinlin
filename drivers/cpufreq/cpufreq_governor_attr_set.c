<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Abstract code क्रम CPUFreq governor tunable sysfs attributes.
 *
 * Copyright (C) 2016, Intel Corporation
 * Author: Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 */

#समावेश "cpufreq_governor.h"

अटल अंतरभूत काष्ठा gov_attr_set *to_gov_attr_set(काष्ठा kobject *kobj)
अणु
	वापस container_of(kobj, काष्ठा gov_attr_set, kobj);
पूर्ण

अटल अंतरभूत काष्ठा governor_attr *to_gov_attr(काष्ठा attribute *attr)
अणु
	वापस container_of(attr, काष्ठा governor_attr, attr);
पूर्ण

अटल sमाप_प्रकार governor_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा governor_attr *gattr = to_gov_attr(attr);

	वापस gattr->show(to_gov_attr_set(kobj), buf);
पूर्ण

अटल sमाप_प्रकार governor_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gov_attr_set *attr_set = to_gov_attr_set(kobj);
	काष्ठा governor_attr *gattr = to_gov_attr(attr);
	पूर्णांक ret;

	mutex_lock(&attr_set->update_lock);
	ret = attr_set->usage_count ? gattr->store(attr_set, buf, count) : -EBUSY;
	mutex_unlock(&attr_set->update_lock);
	वापस ret;
पूर्ण

स्थिर काष्ठा sysfs_ops governor_sysfs_ops = अणु
	.show	= governor_show,
	.store	= governor_store,
पूर्ण;
EXPORT_SYMBOL_GPL(governor_sysfs_ops);

व्योम gov_attr_set_init(काष्ठा gov_attr_set *attr_set, काष्ठा list_head *list_node)
अणु
	INIT_LIST_HEAD(&attr_set->policy_list);
	mutex_init(&attr_set->update_lock);
	attr_set->usage_count = 1;
	list_add(list_node, &attr_set->policy_list);
पूर्ण
EXPORT_SYMBOL_GPL(gov_attr_set_init);

व्योम gov_attr_set_get(काष्ठा gov_attr_set *attr_set, काष्ठा list_head *list_node)
अणु
	mutex_lock(&attr_set->update_lock);
	attr_set->usage_count++;
	list_add(list_node, &attr_set->policy_list);
	mutex_unlock(&attr_set->update_lock);
पूर्ण
EXPORT_SYMBOL_GPL(gov_attr_set_get);

अचिन्हित पूर्णांक gov_attr_set_put(काष्ठा gov_attr_set *attr_set, काष्ठा list_head *list_node)
अणु
	अचिन्हित पूर्णांक count;

	mutex_lock(&attr_set->update_lock);
	list_del(list_node);
	count = --attr_set->usage_count;
	mutex_unlock(&attr_set->update_lock);
	अगर (count)
		वापस count;

	kobject_put(&attr_set->kobj);
	mutex_destroy(&attr_set->update_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gov_attr_set_put);
