<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Power capping class
 * Copyright (c) 2013, Intel Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/घातercap.h>

#घोषणा to_घातercap_zone(n) container_of(n, काष्ठा घातercap_zone, dev)
#घोषणा to_घातercap_control_type(n) \
			container_of(n, काष्ठा घातercap_control_type, dev)

/* Power zone show function */
#घोषणा define_घातer_zone_show(_attr)		\
अटल sमाप_प्रकार _attr##_show(काष्ठा device *dev, \
					काष्ठा device_attribute *dev_attr,\
					अक्षर *buf) \
अणु \
	u64 value; \
	sमाप_प्रकार len = -EINVAL; \
	काष्ठा घातercap_zone *घातer_zone = to_घातercap_zone(dev); \
	\
	अगर (घातer_zone->ops->get_##_attr) अणु \
		अगर (!घातer_zone->ops->get_##_attr(घातer_zone, &value)) \
			len = प्र_लिखो(buf, "%lld\n", value); \
	पूर्ण \
	\
	वापस len; \
पूर्ण

/* The only meaningful input is 0 (reset), others are silently ignored */
#घोषणा define_घातer_zone_store(_attr)		\
अटल sमाप_प्रकार _attr##_store(काष्ठा device *dev,\
				काष्ठा device_attribute *dev_attr, \
				स्थिर अक्षर *buf, माप_प्रकार count) \
अणु \
	पूर्णांक err; \
	काष्ठा घातercap_zone *घातer_zone = to_घातercap_zone(dev); \
	u64 value; \
	\
	err = kम_से_अदीर्घl(buf, 10, &value); \
	अगर (err) \
		वापस -EINVAL; \
	अगर (value) \
		वापस count; \
	अगर (घातer_zone->ops->reset_##_attr) अणु \
		अगर (!घातer_zone->ops->reset_##_attr(घातer_zone)) \
			वापस count; \
	पूर्ण \
	\
	वापस -EINVAL; \
पूर्ण

/* Power zone स्थिरraपूर्णांक show function */
#घोषणा define_घातer_zone_स्थिरraपूर्णांक_show(_attr) \
अटल sमाप_प्रकार show_स्थिरraपूर्णांक_##_attr(काष्ठा device *dev, \
				काष्ठा device_attribute *dev_attr,\
				अक्षर *buf) \
अणु \
	u64 value; \
	sमाप_प्रकार len = -ENODATA; \
	काष्ठा घातercap_zone *घातer_zone = to_घातercap_zone(dev); \
	पूर्णांक id; \
	काष्ठा घातercap_zone_स्थिरraपूर्णांक *pस्थिर;\
	\
	अगर (!माला_पूछो(dev_attr->attr.name, "constraint_%d_", &id)) \
		वापस -EINVAL; \
	अगर (id >= घातer_zone->स्थिर_id_cnt)	\
		वापस -EINVAL; \
	pस्थिर = &घातer_zone->स्थिरraपूर्णांकs[id]; \
	अगर (pस्थिर && pस्थिर->ops && pस्थिर->ops->get_##_attr) अणु \
		अगर (!pस्थिर->ops->get_##_attr(घातer_zone, id, &value)) \
			len = प्र_लिखो(buf, "%lld\n", value); \
	पूर्ण \
	\
	वापस len; \
पूर्ण

/* Power zone स्थिरraपूर्णांक store function */
#घोषणा define_घातer_zone_स्थिरraपूर्णांक_store(_attr) \
अटल sमाप_प्रकार store_स्थिरraपूर्णांक_##_attr(काष्ठा device *dev,\
				काष्ठा device_attribute *dev_attr, \
				स्थिर अक्षर *buf, माप_प्रकार count) \
अणु \
	पूर्णांक err; \
	u64 value; \
	काष्ठा घातercap_zone *घातer_zone = to_घातercap_zone(dev); \
	पूर्णांक id; \
	काष्ठा घातercap_zone_स्थिरraपूर्णांक *pस्थिर;\
	\
	अगर (!माला_पूछो(dev_attr->attr.name, "constraint_%d_", &id)) \
		वापस -EINVAL; \
	अगर (id >= घातer_zone->स्थिर_id_cnt)	\
		वापस -EINVAL; \
	pस्थिर = &घातer_zone->स्थिरraपूर्णांकs[id]; \
	err = kम_से_अदीर्घl(buf, 10, &value); \
	अगर (err) \
		वापस -EINVAL; \
	अगर (pस्थिर && pस्थिर->ops && pस्थिर->ops->set_##_attr) अणु \
		अगर (!pस्थिर->ops->set_##_attr(घातer_zone, id, value)) \
			वापस count; \
	पूर्ण \
	\
	वापस -ENODATA; \
पूर्ण

/* Power zone inक्रमmation callbacks */
define_घातer_zone_show(घातer_uw);
define_घातer_zone_show(max_घातer_range_uw);
define_घातer_zone_show(energy_uj);
define_घातer_zone_store(energy_uj);
define_घातer_zone_show(max_energy_range_uj);

/* Power zone attributes */
अटल DEVICE_ATTR_RO(max_घातer_range_uw);
अटल DEVICE_ATTR_RO(घातer_uw);
अटल DEVICE_ATTR_RO(max_energy_range_uj);
अटल DEVICE_ATTR_RW(energy_uj);

/* Power zone स्थिरraपूर्णांक attributes callbacks */
define_घातer_zone_स्थिरraपूर्णांक_show(घातer_limit_uw);
define_घातer_zone_स्थिरraपूर्णांक_store(घातer_limit_uw);
define_घातer_zone_स्थिरraपूर्णांक_show(समय_winकरोw_us);
define_घातer_zone_स्थिरraपूर्णांक_store(समय_winकरोw_us);
define_घातer_zone_स्थिरraपूर्णांक_show(max_घातer_uw);
define_घातer_zone_स्थिरraपूर्णांक_show(min_घातer_uw);
define_घातer_zone_स्थिरraपूर्णांक_show(max_समय_winकरोw_us);
define_घातer_zone_स्थिरraपूर्णांक_show(min_समय_winकरोw_us);

/* For one समय seeding of स्थिरraपूर्णांक device attributes */
काष्ठा घातercap_स्थिरraपूर्णांक_attr अणु
	काष्ठा device_attribute घातer_limit_attr;
	काष्ठा device_attribute समय_winकरोw_attr;
	काष्ठा device_attribute max_घातer_attr;
	काष्ठा device_attribute min_घातer_attr;
	काष्ठा device_attribute max_समय_winकरोw_attr;
	काष्ठा device_attribute min_समय_winकरोw_attr;
	काष्ठा device_attribute name_attr;
पूर्ण;

अटल काष्ठा घातercap_स्थिरraपूर्णांक_attr
				स्थिरraपूर्णांक_attrs[MAX_CONSTRAINTS_PER_ZONE];

/* A list of घातercap control_types */
अटल LIST_HEAD(घातercap_cntrl_list);
/* Mutex to protect list of घातercap control_types */
अटल DEFINE_MUTEX(घातercap_cntrl_list_lock);

#घोषणा POWERCAP_CONSTRAINT_NAME_LEN	30 /* Some limit to aव्योम overflow */
अटल sमाप_प्रकार show_स्थिरraपूर्णांक_name(काष्ठा device *dev,
				काष्ठा device_attribute *dev_attr,
				अक्षर *buf)
अणु
	स्थिर अक्षर *name;
	काष्ठा घातercap_zone *घातer_zone = to_घातercap_zone(dev);
	पूर्णांक id;
	sमाप_प्रकार len = -ENODATA;
	काष्ठा घातercap_zone_स्थिरraपूर्णांक *pस्थिर;

	अगर (!माला_पूछो(dev_attr->attr.name, "constraint_%d_", &id))
		वापस -EINVAL;
	अगर (id >= घातer_zone->स्थिर_id_cnt)
		वापस -EINVAL;
	pस्थिर = &घातer_zone->स्थिरraपूर्णांकs[id];

	अगर (pस्थिर && pस्थिर->ops && pस्थिर->ops->get_name) अणु
		name = pस्थिर->ops->get_name(घातer_zone, id);
		अगर (name) अणु
			प्र_लिखो(buf, "%.*s\n", POWERCAP_CONSTRAINT_NAME_LEN - 1,
				name);
			len = म_माप(buf);
		पूर्ण
	पूर्ण

	वापस len;
पूर्ण

अटल पूर्णांक create_स्थिरraपूर्णांक_attribute(पूर्णांक id, स्थिर अक्षर *name,
				पूर्णांक mode,
				काष्ठा device_attribute *dev_attr,
				sमाप_प्रकार (*show)(काष्ठा device *,
					काष्ठा device_attribute *, अक्षर *),
				sमाप_प्रकार (*store)(काष्ठा device *,
					काष्ठा device_attribute *,
				स्थिर अक्षर *, माप_प्रकार)
				)
अणु

	dev_attr->attr.name = kaप्र_लिखो(GFP_KERNEL, "constraint_%d_%s",
								id, name);
	अगर (!dev_attr->attr.name)
		वापस -ENOMEM;
	dev_attr->attr.mode = mode;
	dev_attr->show = show;
	dev_attr->store = store;

	वापस 0;
पूर्ण

अटल व्योम मुक्त_स्थिरraपूर्णांक_attributes(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_CONSTRAINTS_PER_ZONE; ++i) अणु
		kमुक्त(स्थिरraपूर्णांक_attrs[i].घातer_limit_attr.attr.name);
		kमुक्त(स्थिरraपूर्णांक_attrs[i].समय_winकरोw_attr.attr.name);
		kमुक्त(स्थिरraपूर्णांक_attrs[i].name_attr.attr.name);
		kमुक्त(स्थिरraपूर्णांक_attrs[i].max_घातer_attr.attr.name);
		kमुक्त(स्थिरraपूर्णांक_attrs[i].min_घातer_attr.attr.name);
		kमुक्त(स्थिरraपूर्णांक_attrs[i].max_समय_winकरोw_attr.attr.name);
		kमुक्त(स्थिरraपूर्णांक_attrs[i].min_समय_winकरोw_attr.attr.name);
	पूर्ण
पूर्ण

अटल पूर्णांक seed_स्थिरraपूर्णांक_attributes(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < MAX_CONSTRAINTS_PER_ZONE; ++i) अणु
		ret = create_स्थिरraपूर्णांक_attribute(i, "power_limit_uw",
					S_IWUSR | S_IRUGO,
					&स्थिरraपूर्णांक_attrs[i].घातer_limit_attr,
					show_स्थिरraपूर्णांक_घातer_limit_uw,
					store_स्थिरraपूर्णांक_घातer_limit_uw);
		अगर (ret)
			जाओ err_alloc;
		ret = create_स्थिरraपूर्णांक_attribute(i, "time_window_us",
					S_IWUSR | S_IRUGO,
					&स्थिरraपूर्णांक_attrs[i].समय_winकरोw_attr,
					show_स्थिरraपूर्णांक_समय_winकरोw_us,
					store_स्थिरraपूर्णांक_समय_winकरोw_us);
		अगर (ret)
			जाओ err_alloc;
		ret = create_स्थिरraपूर्णांक_attribute(i, "name", S_IRUGO,
				&स्थिरraपूर्णांक_attrs[i].name_attr,
				show_स्थिरraपूर्णांक_name,
				शून्य);
		अगर (ret)
			जाओ err_alloc;
		ret = create_स्थिरraपूर्णांक_attribute(i, "max_power_uw", S_IRUGO,
				&स्थिरraपूर्णांक_attrs[i].max_घातer_attr,
				show_स्थिरraपूर्णांक_max_घातer_uw,
				शून्य);
		अगर (ret)
			जाओ err_alloc;
		ret = create_स्थिरraपूर्णांक_attribute(i, "min_power_uw", S_IRUGO,
				&स्थिरraपूर्णांक_attrs[i].min_घातer_attr,
				show_स्थिरraपूर्णांक_min_घातer_uw,
				शून्य);
		अगर (ret)
			जाओ err_alloc;
		ret = create_स्थिरraपूर्णांक_attribute(i, "max_time_window_us",
				S_IRUGO,
				&स्थिरraपूर्णांक_attrs[i].max_समय_winकरोw_attr,
				show_स्थिरraपूर्णांक_max_समय_winकरोw_us,
				शून्य);
		अगर (ret)
			जाओ err_alloc;
		ret = create_स्थिरraपूर्णांक_attribute(i, "min_time_window_us",
				S_IRUGO,
				&स्थिरraपूर्णांक_attrs[i].min_समय_winकरोw_attr,
				show_स्थिरraपूर्णांक_min_समय_winकरोw_us,
				शून्य);
		अगर (ret)
			जाओ err_alloc;

	पूर्ण

	वापस 0;

err_alloc:
	मुक्त_स्थिरraपूर्णांक_attributes();

	वापस ret;
पूर्ण

अटल पूर्णांक create_स्थिरraपूर्णांकs(काष्ठा घातercap_zone *घातer_zone,
			पूर्णांक nr_स्थिरraपूर्णांकs,
			स्थिर काष्ठा घातercap_zone_स्थिरraपूर्णांक_ops *स्थिर_ops)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	पूर्णांक count;
	काष्ठा घातercap_zone_स्थिरraपूर्णांक *pस्थिर;

	अगर (!घातer_zone || !स्थिर_ops || !स्थिर_ops->get_घातer_limit_uw ||
					!स्थिर_ops->set_घातer_limit_uw ||
					!स्थिर_ops->get_समय_winकरोw_us ||
					!स्थिर_ops->set_समय_winकरोw_us)
		वापस -EINVAL;

	count = घातer_zone->zone_attr_count;
	क्रम (i = 0; i < nr_स्थिरraपूर्णांकs; ++i) अणु
		pस्थिर = &घातer_zone->स्थिरraपूर्णांकs[i];
		pस्थिर->ops = स्थिर_ops;
		pस्थिर->id = घातer_zone->स्थिर_id_cnt;
		घातer_zone->स्थिर_id_cnt++;
		घातer_zone->zone_dev_attrs[count++] =
				&स्थिरraपूर्णांक_attrs[i].घातer_limit_attr.attr;
		घातer_zone->zone_dev_attrs[count++] =
				&स्थिरraपूर्णांक_attrs[i].समय_winकरोw_attr.attr;
		अगर (pस्थिर->ops->get_name)
			घातer_zone->zone_dev_attrs[count++] =
				&स्थिरraपूर्णांक_attrs[i].name_attr.attr;
		अगर (pस्थिर->ops->get_max_घातer_uw)
			घातer_zone->zone_dev_attrs[count++] =
				&स्थिरraपूर्णांक_attrs[i].max_घातer_attr.attr;
		अगर (pस्थिर->ops->get_min_घातer_uw)
			घातer_zone->zone_dev_attrs[count++] =
				&स्थिरraपूर्णांक_attrs[i].min_घातer_attr.attr;
		अगर (pस्थिर->ops->get_max_समय_winकरोw_us)
			घातer_zone->zone_dev_attrs[count++] =
				&स्थिरraपूर्णांक_attrs[i].max_समय_winकरोw_attr.attr;
		अगर (pस्थिर->ops->get_min_समय_winकरोw_us)
			घातer_zone->zone_dev_attrs[count++] =
				&स्थिरraपूर्णांक_attrs[i].min_समय_winकरोw_attr.attr;
	पूर्ण
	घातer_zone->zone_attr_count = count;

	वापस ret;
पूर्ण

अटल bool control_type_valid(व्योम *control_type)
अणु
	काष्ठा घातercap_control_type *pos = शून्य;
	bool found = false;

	mutex_lock(&घातercap_cntrl_list_lock);

	list_क्रम_each_entry(pos, &घातercap_cntrl_list, node) अणु
		अगर (pos == control_type) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&घातercap_cntrl_list_lock);

	वापस found;
पूर्ण

अटल sमाप_प्रकार name_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा घातercap_zone *घातer_zone = to_घातercap_zone(dev);

	वापस प्र_लिखो(buf, "%s\n", घातer_zone->name);
पूर्ण

अटल DEVICE_ATTR_RO(name);

/* Create zone and attributes in sysfs */
अटल व्योम create_घातer_zone_common_attributes(
					काष्ठा घातercap_zone *घातer_zone)
अणु
	पूर्णांक count = 0;

	घातer_zone->zone_dev_attrs[count++] = &dev_attr_name.attr;
	अगर (घातer_zone->ops->get_max_energy_range_uj)
		घातer_zone->zone_dev_attrs[count++] =
					&dev_attr_max_energy_range_uj.attr;
	अगर (घातer_zone->ops->get_energy_uj) अणु
		अगर (घातer_zone->ops->reset_energy_uj)
			dev_attr_energy_uj.attr.mode = S_IWUSR | S_IRUSR;
		अन्यथा
			dev_attr_energy_uj.attr.mode = S_IRUSR;
		घातer_zone->zone_dev_attrs[count++] =
					&dev_attr_energy_uj.attr;
	पूर्ण
	अगर (घातer_zone->ops->get_घातer_uw)
		घातer_zone->zone_dev_attrs[count++] =
					&dev_attr_घातer_uw.attr;
	अगर (घातer_zone->ops->get_max_घातer_range_uw)
		घातer_zone->zone_dev_attrs[count++] =
					&dev_attr_max_घातer_range_uw.attr;
	घातer_zone->zone_dev_attrs[count] = शून्य;
	घातer_zone->zone_attr_count = count;
पूर्ण

अटल व्योम घातercap_release(काष्ठा device *dev)
अणु
	bool allocated;

	अगर (dev->parent) अणु
		काष्ठा घातercap_zone *घातer_zone = to_घातercap_zone(dev);

		/* Store flag as the release() may मुक्त memory */
		allocated = घातer_zone->allocated;
		/* Remove id from parent idr काष्ठा */
		idr_हटाओ(घातer_zone->parent_idr, घातer_zone->id);
		/* Destroy idrs allocated क्रम this zone */
		idr_destroy(&घातer_zone->idr);
		kमुक्त(घातer_zone->name);
		kमुक्त(घातer_zone->zone_dev_attrs);
		kमुक्त(घातer_zone->स्थिरraपूर्णांकs);
		अगर (घातer_zone->ops->release)
			घातer_zone->ops->release(घातer_zone);
		अगर (allocated)
			kमुक्त(घातer_zone);
	पूर्ण अन्यथा अणु
		काष्ठा घातercap_control_type *control_type =
						to_घातercap_control_type(dev);

		/* Store flag as the release() may मुक्त memory */
		allocated = control_type->allocated;
		idr_destroy(&control_type->idr);
		mutex_destroy(&control_type->lock);
		अगर (control_type->ops && control_type->ops->release)
			control_type->ops->release(control_type);
		अगर (allocated)
			kमुक्त(control_type);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार enabled_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	bool mode = true;

	/* Default is enabled */
	अगर (dev->parent) अणु
		काष्ठा घातercap_zone *घातer_zone = to_घातercap_zone(dev);
		अगर (घातer_zone->ops->get_enable)
			अगर (घातer_zone->ops->get_enable(घातer_zone, &mode))
				mode = false;
	पूर्ण अन्यथा अणु
		काष्ठा घातercap_control_type *control_type =
						to_घातercap_control_type(dev);
		अगर (control_type->ops && control_type->ops->get_enable)
			अगर (control_type->ops->get_enable(control_type, &mode))
				mode = false;
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", mode);
पूर्ण

अटल sमाप_प्रकार enabled_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf,  माप_प्रकार len)
अणु
	bool mode;

	अगर (strtobool(buf, &mode))
		वापस -EINVAL;
	अगर (dev->parent) अणु
		काष्ठा घातercap_zone *घातer_zone = to_घातercap_zone(dev);
		अगर (घातer_zone->ops->set_enable)
			अगर (!घातer_zone->ops->set_enable(घातer_zone, mode))
				वापस len;
	पूर्ण अन्यथा अणु
		काष्ठा घातercap_control_type *control_type =
						to_घातercap_control_type(dev);
		अगर (control_type->ops && control_type->ops->set_enable)
			अगर (!control_type->ops->set_enable(control_type, mode))
				वापस len;
	पूर्ण

	वापस -ENOSYS;
पूर्ण

अटल DEVICE_ATTR_RW(enabled);

अटल काष्ठा attribute *घातercap_attrs[] = अणु
	&dev_attr_enabled.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(घातercap);

अटल काष्ठा class घातercap_class = अणु
	.name = "powercap",
	.dev_release = घातercap_release,
	.dev_groups = घातercap_groups,
पूर्ण;

काष्ठा घातercap_zone *घातercap_रेजिस्टर_zone(
			काष्ठा घातercap_zone *घातer_zone,
			काष्ठा घातercap_control_type *control_type,
			स्थिर अक्षर *name,
			काष्ठा घातercap_zone *parent,
			स्थिर काष्ठा घातercap_zone_ops *ops,
			पूर्णांक nr_स्थिरraपूर्णांकs,
			स्थिर काष्ठा घातercap_zone_स्थिरraपूर्णांक_ops *स्थिर_ops)
अणु
	पूर्णांक result;
	पूर्णांक nr_attrs;

	अगर (!name || !control_type || !ops ||
			nr_स्थिरraपूर्णांकs > MAX_CONSTRAINTS_PER_ZONE ||
			(!ops->get_energy_uj && !ops->get_घातer_uw) ||
			!control_type_valid(control_type))
		वापस ERR_PTR(-EINVAL);

	अगर (घातer_zone) अणु
		अगर (!ops->release)
			वापस ERR_PTR(-EINVAL);
		स_रखो(घातer_zone, 0, माप(*घातer_zone));
	पूर्ण अन्यथा अणु
		घातer_zone = kzalloc(माप(*घातer_zone), GFP_KERNEL);
		अगर (!घातer_zone)
			वापस ERR_PTR(-ENOMEM);
		घातer_zone->allocated = true;
	पूर्ण
	घातer_zone->ops = ops;
	घातer_zone->control_type_inst = control_type;
	अगर (!parent) अणु
		घातer_zone->dev.parent = &control_type->dev;
		घातer_zone->parent_idr = &control_type->idr;
	पूर्ण अन्यथा अणु
		घातer_zone->dev.parent = &parent->dev;
		घातer_zone->parent_idr = &parent->idr;
	पूर्ण
	घातer_zone->dev.class = &घातercap_class;

	mutex_lock(&control_type->lock);
	/* Using idr to get the unique id */
	result = idr_alloc(घातer_zone->parent_idr, शून्य, 0, 0, GFP_KERNEL);
	अगर (result < 0)
		जाओ err_idr_alloc;

	घातer_zone->id = result;
	idr_init(&घातer_zone->idr);
	result = -ENOMEM;
	घातer_zone->name = kstrdup(name, GFP_KERNEL);
	अगर (!घातer_zone->name)
		जाओ err_name_alloc;
	dev_set_name(&घातer_zone->dev, "%s:%x",
					dev_name(घातer_zone->dev.parent),
					घातer_zone->id);
	घातer_zone->स्थिरraपूर्णांकs = kसुस्मृति(nr_स्थिरraपूर्णांकs,
					  माप(*घातer_zone->स्थिरraपूर्णांकs),
					  GFP_KERNEL);
	अगर (!घातer_zone->स्थिरraपूर्णांकs)
		जाओ err_स्थिर_alloc;

	nr_attrs = nr_स्थिरraपूर्णांकs * POWERCAP_CONSTRAINTS_ATTRS +
						POWERCAP_ZONE_MAX_ATTRS + 1;
	घातer_zone->zone_dev_attrs = kसुस्मृति(nr_attrs, माप(व्योम *),
					     GFP_KERNEL);
	अगर (!घातer_zone->zone_dev_attrs)
		जाओ err_attr_alloc;
	create_घातer_zone_common_attributes(घातer_zone);
	result = create_स्थिरraपूर्णांकs(घातer_zone, nr_स्थिरraपूर्णांकs, स्थिर_ops);
	अगर (result)
		जाओ err_dev_ret;

	घातer_zone->zone_dev_attrs[घातer_zone->zone_attr_count] = शून्य;
	घातer_zone->dev_zone_attr_group.attrs = घातer_zone->zone_dev_attrs;
	घातer_zone->dev_attr_groups[0] = &घातer_zone->dev_zone_attr_group;
	घातer_zone->dev_attr_groups[1] = शून्य;
	घातer_zone->dev.groups = घातer_zone->dev_attr_groups;
	result = device_रेजिस्टर(&घातer_zone->dev);
	अगर (result)
		जाओ err_dev_ret;

	control_type->nr_zones++;
	mutex_unlock(&control_type->lock);

	वापस घातer_zone;

err_dev_ret:
	kमुक्त(घातer_zone->zone_dev_attrs);
err_attr_alloc:
	kमुक्त(घातer_zone->स्थिरraपूर्णांकs);
err_स्थिर_alloc:
	kमुक्त(घातer_zone->name);
err_name_alloc:
	idr_हटाओ(घातer_zone->parent_idr, घातer_zone->id);
err_idr_alloc:
	अगर (घातer_zone->allocated)
		kमुक्त(घातer_zone);
	mutex_unlock(&control_type->lock);

	वापस ERR_PTR(result);
पूर्ण
EXPORT_SYMBOL_GPL(घातercap_रेजिस्टर_zone);

पूर्णांक घातercap_unरेजिस्टर_zone(काष्ठा घातercap_control_type *control_type,
				काष्ठा घातercap_zone *घातer_zone)
अणु
	अगर (!घातer_zone || !control_type)
		वापस -EINVAL;

	mutex_lock(&control_type->lock);
	control_type->nr_zones--;
	mutex_unlock(&control_type->lock);

	device_unरेजिस्टर(&घातer_zone->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(घातercap_unरेजिस्टर_zone);

काष्ठा घातercap_control_type *घातercap_रेजिस्टर_control_type(
				काष्ठा घातercap_control_type *control_type,
				स्थिर अक्षर *name,
				स्थिर काष्ठा घातercap_control_type_ops *ops)
अणु
	पूर्णांक result;

	अगर (!name)
		वापस ERR_PTR(-EINVAL);
	अगर (control_type) अणु
		अगर (!ops || !ops->release)
			वापस ERR_PTR(-EINVAL);
		स_रखो(control_type, 0, माप(*control_type));
	पूर्ण अन्यथा अणु
		control_type = kzalloc(माप(*control_type), GFP_KERNEL);
		अगर (!control_type)
			वापस ERR_PTR(-ENOMEM);
		control_type->allocated = true;
	पूर्ण
	mutex_init(&control_type->lock);
	control_type->ops = ops;
	INIT_LIST_HEAD(&control_type->node);
	control_type->dev.class = &घातercap_class;
	dev_set_name(&control_type->dev, "%s", name);
	result = device_रेजिस्टर(&control_type->dev);
	अगर (result) अणु
		अगर (control_type->allocated)
			kमुक्त(control_type);
		वापस ERR_PTR(result);
	पूर्ण
	idr_init(&control_type->idr);

	mutex_lock(&घातercap_cntrl_list_lock);
	list_add_tail(&control_type->node, &घातercap_cntrl_list);
	mutex_unlock(&घातercap_cntrl_list_lock);

	वापस control_type;
पूर्ण
EXPORT_SYMBOL_GPL(घातercap_रेजिस्टर_control_type);

पूर्णांक घातercap_unरेजिस्टर_control_type(काष्ठा घातercap_control_type *control_type)
अणु
	काष्ठा घातercap_control_type *pos = शून्य;

	अगर (control_type->nr_zones) अणु
		dev_err(&control_type->dev, "Zones of this type still not freed\n");
		वापस -EINVAL;
	पूर्ण
	mutex_lock(&घातercap_cntrl_list_lock);
	list_क्रम_each_entry(pos, &घातercap_cntrl_list, node) अणु
		अगर (pos == control_type) अणु
			list_del(&control_type->node);
			mutex_unlock(&घातercap_cntrl_list_lock);
			device_unरेजिस्टर(&control_type->dev);
			वापस 0;
		पूर्ण
	पूर्ण
	mutex_unlock(&घातercap_cntrl_list_lock);

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(घातercap_unरेजिस्टर_control_type);

अटल पूर्णांक __init घातercap_init(व्योम)
अणु
	पूर्णांक result;

	result = seed_स्थिरraपूर्णांक_attributes();
	अगर (result)
		वापस result;

	वापस class_रेजिस्टर(&घातercap_class);
पूर्ण

fs_initcall(घातercap_init);

MODULE_DESCRIPTION("PowerCap sysfs Driver");
MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>");
MODULE_LICENSE("GPL v2");
