<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  thermal.c - sysfs पूर्णांकerface of thermal devices
 *
 *  Copyright (C) 2016 Eduarकरो Valentin <edubezval@gmail.com>
 *
 *  Highly based on original thermal_core.c
 *  Copyright (C) 2008 Intel Corp
 *  Copyright (C) 2008 Zhang Rui <rui.zhang@पूर्णांकel.com>
 *  Copyright (C) 2008 Sujith Thomas <sujith.thomas@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/sysfs.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/jअगरfies.h>

#समावेश "thermal_core.h"

/* sys I/F क्रम thermal zone */

अटल sमाप_प्रकार
type_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा thermal_zone_device *tz = to_thermal_zone(dev);

	वापस प्र_लिखो(buf, "%s\n", tz->type);
पूर्ण

अटल sमाप_प्रकार
temp_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा thermal_zone_device *tz = to_thermal_zone(dev);
	पूर्णांक temperature, ret;

	ret = thermal_zone_get_temp(tz, &temperature);

	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", temperature);
पूर्ण

अटल sमाप_प्रकार
mode_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा thermal_zone_device *tz = to_thermal_zone(dev);
	पूर्णांक enabled = thermal_zone_device_is_enabled(tz);

	वापस प्र_लिखो(buf, "%s\n", enabled ? "enabled" : "disabled");
पूर्ण

अटल sमाप_प्रकार
mode_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा thermal_zone_device *tz = to_thermal_zone(dev);
	पूर्णांक result;

	अगर (!म_भेदन(buf, "enabled", माप("enabled") - 1))
		result = thermal_zone_device_enable(tz);
	अन्यथा अगर (!म_भेदन(buf, "disabled", माप("disabled") - 1))
		result = thermal_zone_device_disable(tz);
	अन्यथा
		result = -EINVAL;

	अगर (result)
		वापस result;

	वापस count;
पूर्ण

अटल sमाप_प्रकार
trip_poपूर्णांक_type_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा thermal_zone_device *tz = to_thermal_zone(dev);
	क्रमागत thermal_trip_type type;
	पूर्णांक trip, result;

	अगर (!tz->ops->get_trip_type)
		वापस -EPERM;

	अगर (माला_पूछो(attr->attr.name, "trip_point_%d_type", &trip) != 1)
		वापस -EINVAL;

	result = tz->ops->get_trip_type(tz, trip, &type);
	अगर (result)
		वापस result;

	चयन (type) अणु
	हाल THERMAL_TRIP_CRITICAL:
		वापस प्र_लिखो(buf, "critical\n");
	हाल THERMAL_TRIP_HOT:
		वापस प्र_लिखो(buf, "hot\n");
	हाल THERMAL_TRIP_PASSIVE:
		वापस प्र_लिखो(buf, "passive\n");
	हाल THERMAL_TRIP_ACTIVE:
		वापस प्र_लिखो(buf, "active\n");
	शेष:
		वापस प्र_लिखो(buf, "unknown\n");
	पूर्ण
पूर्ण

अटल sमाप_प्रकार
trip_poपूर्णांक_temp_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा thermal_zone_device *tz = to_thermal_zone(dev);
	पूर्णांक trip, ret;
	पूर्णांक temperature, hyst = 0;
	क्रमागत thermal_trip_type type;

	अगर (!tz->ops->set_trip_temp)
		वापस -EPERM;

	अगर (माला_पूछो(attr->attr.name, "trip_point_%d_temp", &trip) != 1)
		वापस -EINVAL;

	अगर (kstrtoपूर्णांक(buf, 10, &temperature))
		वापस -EINVAL;

	ret = tz->ops->set_trip_temp(tz, trip, temperature);
	अगर (ret)
		वापस ret;

	अगर (tz->ops->get_trip_hyst) अणु
		ret = tz->ops->get_trip_hyst(tz, trip, &hyst);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = tz->ops->get_trip_type(tz, trip, &type);
	अगर (ret)
		वापस ret;

	thermal_notअगरy_tz_trip_change(tz->id, trip, type, temperature, hyst);

	thermal_zone_device_update(tz, THERMAL_EVENT_UNSPECIFIED);

	वापस count;
पूर्ण

अटल sमाप_प्रकार
trip_poपूर्णांक_temp_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा thermal_zone_device *tz = to_thermal_zone(dev);
	पूर्णांक trip, ret;
	पूर्णांक temperature;

	अगर (!tz->ops->get_trip_temp)
		वापस -EPERM;

	अगर (माला_पूछो(attr->attr.name, "trip_point_%d_temp", &trip) != 1)
		वापस -EINVAL;

	ret = tz->ops->get_trip_temp(tz, trip, &temperature);

	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", temperature);
पूर्ण

अटल sमाप_प्रकार
trip_poपूर्णांक_hyst_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा thermal_zone_device *tz = to_thermal_zone(dev);
	पूर्णांक trip, ret;
	पूर्णांक temperature;

	अगर (!tz->ops->set_trip_hyst)
		वापस -EPERM;

	अगर (माला_पूछो(attr->attr.name, "trip_point_%d_hyst", &trip) != 1)
		वापस -EINVAL;

	अगर (kstrtoपूर्णांक(buf, 10, &temperature))
		वापस -EINVAL;

	/*
	 * We are not करोing any check on the 'temperature' value
	 * here. The driver implementing 'set_trip_hyst' has to
	 * take care of this.
	 */
	ret = tz->ops->set_trip_hyst(tz, trip, temperature);

	अगर (!ret)
		thermal_zone_set_trips(tz);

	वापस ret ? ret : count;
पूर्ण

अटल sमाप_प्रकार
trip_poपूर्णांक_hyst_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा thermal_zone_device *tz = to_thermal_zone(dev);
	पूर्णांक trip, ret;
	पूर्णांक temperature;

	अगर (!tz->ops->get_trip_hyst)
		वापस -EPERM;

	अगर (माला_पूछो(attr->attr.name, "trip_point_%d_hyst", &trip) != 1)
		वापस -EINVAL;

	ret = tz->ops->get_trip_hyst(tz, trip, &temperature);

	वापस ret ? ret : प्र_लिखो(buf, "%d\n", temperature);
पूर्ण

अटल sमाप_प्रकार
policy_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा thermal_zone_device *tz = to_thermal_zone(dev);
	अक्षर name[THERMAL_NAME_LENGTH];
	पूर्णांक ret;

	snम_लिखो(name, माप(name), "%s", buf);

	ret = thermal_zone_device_set_policy(tz, name);
	अगर (!ret)
		ret = count;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
policy_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा thermal_zone_device *tz = to_thermal_zone(dev);

	वापस प्र_लिखो(buf, "%s\n", tz->governor->name);
पूर्ण

अटल sमाप_प्रकार
available_policies_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	वापस thermal_build_list_of_policies(buf);
पूर्ण

#अगर (IS_ENABLED(CONFIG_THERMAL_EMULATION))
अटल sमाप_प्रकार
emul_temp_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा thermal_zone_device *tz = to_thermal_zone(dev);
	पूर्णांक ret = 0;
	पूर्णांक temperature;

	अगर (kstrtoपूर्णांक(buf, 10, &temperature))
		वापस -EINVAL;

	अगर (!tz->ops->set_emul_temp) अणु
		mutex_lock(&tz->lock);
		tz->emul_temperature = temperature;
		mutex_unlock(&tz->lock);
	पूर्ण अन्यथा अणु
		ret = tz->ops->set_emul_temp(tz, temperature);
	पूर्ण

	अगर (!ret)
		thermal_zone_device_update(tz, THERMAL_EVENT_UNSPECIFIED);

	वापस ret ? ret : count;
पूर्ण
अटल DEVICE_ATTR_WO(emul_temp);
#पूर्ण_अगर

अटल sमाप_प्रकार
sustainable_घातer_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
		       अक्षर *buf)
अणु
	काष्ठा thermal_zone_device *tz = to_thermal_zone(dev);

	अगर (tz->tzp)
		वापस प्र_लिखो(buf, "%u\n", tz->tzp->sustainable_घातer);
	अन्यथा
		वापस -EIO;
पूर्ण

अटल sमाप_प्रकार
sustainable_घातer_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा thermal_zone_device *tz = to_thermal_zone(dev);
	u32 sustainable_घातer;

	अगर (!tz->tzp)
		वापस -EIO;

	अगर (kstrtou32(buf, 10, &sustainable_घातer))
		वापस -EINVAL;

	tz->tzp->sustainable_घातer = sustainable_घातer;

	वापस count;
पूर्ण

#घोषणा create_s32_tzp_attr(name)					\
	अटल sमाप_प्रकार							\
	name##_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, \
		अक्षर *buf)						\
	अणु								\
	काष्ठा thermal_zone_device *tz = to_thermal_zone(dev);		\
									\
	अगर (tz->tzp)							\
		वापस प्र_लिखो(buf, "%d\n", tz->tzp->name);		\
	अन्यथा								\
		वापस -EIO;						\
	पूर्ण								\
									\
	अटल sमाप_प्रकार							\
	name##_store(काष्ठा device *dev, काष्ठा device_attribute *devattr, \
		स्थिर अक्षर *buf, माप_प्रकार count)				\
	अणु								\
		काष्ठा thermal_zone_device *tz = to_thermal_zone(dev);	\
		s32 value;						\
									\
		अगर (!tz->tzp)						\
			वापस -EIO;					\
									\
		अगर (kstrtos32(buf, 10, &value))				\
			वापस -EINVAL;					\
									\
		tz->tzp->name = value;					\
									\
		वापस count;						\
	पूर्ण								\
	अटल DEVICE_ATTR_RW(name)

create_s32_tzp_attr(k_po);
create_s32_tzp_attr(k_pu);
create_s32_tzp_attr(k_i);
create_s32_tzp_attr(k_d);
create_s32_tzp_attr(पूर्णांकegral_cutoff);
create_s32_tzp_attr(slope);
create_s32_tzp_attr(offset);
#अघोषित create_s32_tzp_attr

/*
 * These are thermal zone device attributes that will always be present.
 * All the attributes created क्रम tzp (create_s32_tzp_attr) also are always
 * present on the sysfs पूर्णांकerface.
 */
अटल DEVICE_ATTR_RO(type);
अटल DEVICE_ATTR_RO(temp);
अटल DEVICE_ATTR_RW(policy);
अटल DEVICE_ATTR_RO(available_policies);
अटल DEVICE_ATTR_RW(sustainable_घातer);

/* These thermal zone device attributes are created based on conditions */
अटल DEVICE_ATTR_RW(mode);

/* These attributes are unconditionally added to a thermal zone */
अटल काष्ठा attribute *thermal_zone_dev_attrs[] = अणु
	&dev_attr_type.attr,
	&dev_attr_temp.attr,
#अगर (IS_ENABLED(CONFIG_THERMAL_EMULATION))
	&dev_attr_emul_temp.attr,
#पूर्ण_अगर
	&dev_attr_policy.attr,
	&dev_attr_available_policies.attr,
	&dev_attr_sustainable_घातer.attr,
	&dev_attr_k_po.attr,
	&dev_attr_k_pu.attr,
	&dev_attr_k_i.attr,
	&dev_attr_k_d.attr,
	&dev_attr_पूर्णांकegral_cutoff.attr,
	&dev_attr_slope.attr,
	&dev_attr_offset.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group thermal_zone_attribute_group = अणु
	.attrs = thermal_zone_dev_attrs,
पूर्ण;

अटल काष्ठा attribute *thermal_zone_mode_attrs[] = अणु
	&dev_attr_mode.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group thermal_zone_mode_attribute_group = अणु
	.attrs = thermal_zone_mode_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *thermal_zone_attribute_groups[] = अणु
	&thermal_zone_attribute_group,
	&thermal_zone_mode_attribute_group,
	/* This is not शून्य terminated as we create the group dynamically */
पूर्ण;

/**
 * create_trip_attrs() - create attributes क्रम trip poपूर्णांकs
 * @tz:		the thermal zone device
 * @mask:	Writeable trip poपूर्णांक biपंचांगap.
 *
 * helper function to instantiate sysfs entries क्रम every trip
 * poपूर्णांक and its properties of a काष्ठा thermal_zone_device.
 *
 * Return: 0 on success, the proper error value otherwise.
 */
अटल पूर्णांक create_trip_attrs(काष्ठा thermal_zone_device *tz, पूर्णांक mask)
अणु
	काष्ठा attribute **attrs;
	पूर्णांक indx;

	/* This function works only क्रम zones with at least one trip */
	अगर (tz->trips <= 0)
		वापस -EINVAL;

	tz->trip_type_attrs = kसुस्मृति(tz->trips, माप(*tz->trip_type_attrs),
				      GFP_KERNEL);
	अगर (!tz->trip_type_attrs)
		वापस -ENOMEM;

	tz->trip_temp_attrs = kसुस्मृति(tz->trips, माप(*tz->trip_temp_attrs),
				      GFP_KERNEL);
	अगर (!tz->trip_temp_attrs) अणु
		kमुक्त(tz->trip_type_attrs);
		वापस -ENOMEM;
	पूर्ण

	अगर (tz->ops->get_trip_hyst) अणु
		tz->trip_hyst_attrs = kसुस्मृति(tz->trips,
					      माप(*tz->trip_hyst_attrs),
					      GFP_KERNEL);
		अगर (!tz->trip_hyst_attrs) अणु
			kमुक्त(tz->trip_type_attrs);
			kमुक्त(tz->trip_temp_attrs);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	attrs = kसुस्मृति(tz->trips * 3 + 1, माप(*attrs), GFP_KERNEL);
	अगर (!attrs) अणु
		kमुक्त(tz->trip_type_attrs);
		kमुक्त(tz->trip_temp_attrs);
		अगर (tz->ops->get_trip_hyst)
			kमुक्त(tz->trip_hyst_attrs);
		वापस -ENOMEM;
	पूर्ण

	क्रम (indx = 0; indx < tz->trips; indx++) अणु
		/* create trip type attribute */
		snम_लिखो(tz->trip_type_attrs[indx].name, THERMAL_NAME_LENGTH,
			 "trip_point_%d_type", indx);

		sysfs_attr_init(&tz->trip_type_attrs[indx].attr.attr);
		tz->trip_type_attrs[indx].attr.attr.name =
						tz->trip_type_attrs[indx].name;
		tz->trip_type_attrs[indx].attr.attr.mode = S_IRUGO;
		tz->trip_type_attrs[indx].attr.show = trip_poपूर्णांक_type_show;
		attrs[indx] = &tz->trip_type_attrs[indx].attr.attr;

		/* create trip temp attribute */
		snम_लिखो(tz->trip_temp_attrs[indx].name, THERMAL_NAME_LENGTH,
			 "trip_point_%d_temp", indx);

		sysfs_attr_init(&tz->trip_temp_attrs[indx].attr.attr);
		tz->trip_temp_attrs[indx].attr.attr.name =
						tz->trip_temp_attrs[indx].name;
		tz->trip_temp_attrs[indx].attr.attr.mode = S_IRUGO;
		tz->trip_temp_attrs[indx].attr.show = trip_poपूर्णांक_temp_show;
		अगर (IS_ENABLED(CONFIG_THERMAL_WRITABLE_TRIPS) &&
		    mask & (1 << indx)) अणु
			tz->trip_temp_attrs[indx].attr.attr.mode |= S_IWUSR;
			tz->trip_temp_attrs[indx].attr.store =
							trip_poपूर्णांक_temp_store;
		पूर्ण
		attrs[indx + tz->trips] = &tz->trip_temp_attrs[indx].attr.attr;

		/* create Optional trip hyst attribute */
		अगर (!tz->ops->get_trip_hyst)
			जारी;
		snम_लिखो(tz->trip_hyst_attrs[indx].name, THERMAL_NAME_LENGTH,
			 "trip_point_%d_hyst", indx);

		sysfs_attr_init(&tz->trip_hyst_attrs[indx].attr.attr);
		tz->trip_hyst_attrs[indx].attr.attr.name =
					tz->trip_hyst_attrs[indx].name;
		tz->trip_hyst_attrs[indx].attr.attr.mode = S_IRUGO;
		tz->trip_hyst_attrs[indx].attr.show = trip_poपूर्णांक_hyst_show;
		अगर (tz->ops->set_trip_hyst) अणु
			tz->trip_hyst_attrs[indx].attr.attr.mode |= S_IWUSR;
			tz->trip_hyst_attrs[indx].attr.store =
					trip_poपूर्णांक_hyst_store;
		पूर्ण
		attrs[indx + tz->trips * 2] =
					&tz->trip_hyst_attrs[indx].attr.attr;
	पूर्ण
	attrs[tz->trips * 3] = शून्य;

	tz->trips_attribute_group.attrs = attrs;

	वापस 0;
पूर्ण

/**
 * destroy_trip_attrs() - destroy attributes क्रम trip poपूर्णांकs
 * @tz:		the thermal zone device
 *
 * helper function to मुक्त resources allocated by create_trip_attrs()
 */
अटल व्योम destroy_trip_attrs(काष्ठा thermal_zone_device *tz)
अणु
	अगर (!tz)
		वापस;

	kमुक्त(tz->trip_type_attrs);
	kमुक्त(tz->trip_temp_attrs);
	अगर (tz->ops->get_trip_hyst)
		kमुक्त(tz->trip_hyst_attrs);
	kमुक्त(tz->trips_attribute_group.attrs);
पूर्ण

पूर्णांक thermal_zone_create_device_groups(काष्ठा thermal_zone_device *tz,
				      पूर्णांक mask)
अणु
	स्थिर काष्ठा attribute_group **groups;
	पूर्णांक i, size, result;

	/* we need one extra क्रम trips and the शून्य to terminate the array */
	size = ARRAY_SIZE(thermal_zone_attribute_groups) + 2;
	/* This also takes care of API requirement to be शून्य terminated */
	groups = kसुस्मृति(size, माप(*groups), GFP_KERNEL);
	अगर (!groups)
		वापस -ENOMEM;

	क्रम (i = 0; i < size - 2; i++)
		groups[i] = thermal_zone_attribute_groups[i];

	अगर (tz->trips) अणु
		result = create_trip_attrs(tz, mask);
		अगर (result) अणु
			kमुक्त(groups);

			वापस result;
		पूर्ण

		groups[size - 2] = &tz->trips_attribute_group;
	पूर्ण

	tz->device.groups = groups;

	वापस 0;
पूर्ण

व्योम thermal_zone_destroy_device_groups(काष्ठा thermal_zone_device *tz)
अणु
	अगर (!tz)
		वापस;

	अगर (tz->trips)
		destroy_trip_attrs(tz);

	kमुक्त(tz->device.groups);
पूर्ण

/* sys I/F क्रम cooling device */
अटल sमाप_प्रकार
cdev_type_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा thermal_cooling_device *cdev = to_cooling_device(dev);

	वापस प्र_लिखो(buf, "%s\n", cdev->type);
पूर्ण

अटल sमाप_प्रकार max_state_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा thermal_cooling_device *cdev = to_cooling_device(dev);
	अचिन्हित दीर्घ state;
	पूर्णांक ret;

	ret = cdev->ops->get_max_state(cdev, &state);
	अगर (ret)
		वापस ret;
	वापस प्र_लिखो(buf, "%ld\n", state);
पूर्ण

अटल sमाप_प्रकार cur_state_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा thermal_cooling_device *cdev = to_cooling_device(dev);
	अचिन्हित दीर्घ state;
	पूर्णांक ret;

	ret = cdev->ops->get_cur_state(cdev, &state);
	अगर (ret)
		वापस ret;
	वापस प्र_लिखो(buf, "%ld\n", state);
पूर्ण

अटल sमाप_प्रकार
cur_state_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा thermal_cooling_device *cdev = to_cooling_device(dev);
	अचिन्हित दीर्घ state;
	पूर्णांक result;

	अगर (माला_पूछो(buf, "%ld\n", &state) != 1)
		वापस -EINVAL;

	अगर ((दीर्घ)state < 0)
		वापस -EINVAL;

	mutex_lock(&cdev->lock);

	result = cdev->ops->set_cur_state(cdev, state);
	अगर (!result)
		thermal_cooling_device_stats_update(cdev, state);

	mutex_unlock(&cdev->lock);
	वापस result ? result : count;
पूर्ण

अटल काष्ठा device_attribute
dev_attr_cdev_type = __ATTR(type, 0444, cdev_type_show, शून्य);
अटल DEVICE_ATTR_RO(max_state);
अटल DEVICE_ATTR_RW(cur_state);

अटल काष्ठा attribute *cooling_device_attrs[] = अणु
	&dev_attr_cdev_type.attr,
	&dev_attr_max_state.attr,
	&dev_attr_cur_state.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group cooling_device_attr_group = अणु
	.attrs = cooling_device_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *cooling_device_attr_groups[] = अणु
	&cooling_device_attr_group,
	शून्य, /* Space allocated क्रम cooling_device_stats_attr_group */
	शून्य,
पूर्ण;

#अगर_घोषित CONFIG_THERMAL_STATISTICS
काष्ठा cooling_dev_stats अणु
	spinlock_t lock;
	अचिन्हित पूर्णांक total_trans;
	अचिन्हित दीर्घ state;
	अचिन्हित दीर्घ max_states;
	kसमय_प्रकार last_समय;
	kसमय_प्रकार *समय_in_state;
	अचिन्हित पूर्णांक *trans_table;
पूर्ण;

अटल व्योम update_समय_in_state(काष्ठा cooling_dev_stats *stats)
अणु
	kसमय_प्रकार now = kसमय_get(), delta;

	delta = kसमय_sub(now, stats->last_समय);
	stats->समय_in_state[stats->state] =
		kसमय_add(stats->समय_in_state[stats->state], delta);
	stats->last_समय = now;
पूर्ण

व्योम thermal_cooling_device_stats_update(काष्ठा thermal_cooling_device *cdev,
					 अचिन्हित दीर्घ new_state)
अणु
	काष्ठा cooling_dev_stats *stats = cdev->stats;

	अगर (!stats)
		वापस;

	spin_lock(&stats->lock);

	अगर (stats->state == new_state)
		जाओ unlock;

	update_समय_in_state(stats);
	stats->trans_table[stats->state * stats->max_states + new_state]++;
	stats->state = new_state;
	stats->total_trans++;

unlock:
	spin_unlock(&stats->lock);
पूर्ण

अटल sमाप_प्रकार total_trans_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा thermal_cooling_device *cdev = to_cooling_device(dev);
	काष्ठा cooling_dev_stats *stats = cdev->stats;
	पूर्णांक ret;

	spin_lock(&stats->lock);
	ret = प्र_लिखो(buf, "%u\n", stats->total_trans);
	spin_unlock(&stats->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
समय_in_state_ms_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      अक्षर *buf)
अणु
	काष्ठा thermal_cooling_device *cdev = to_cooling_device(dev);
	काष्ठा cooling_dev_stats *stats = cdev->stats;
	sमाप_प्रकार len = 0;
	पूर्णांक i;

	spin_lock(&stats->lock);
	update_समय_in_state(stats);

	क्रम (i = 0; i < stats->max_states; i++) अणु
		len += प्र_लिखो(buf + len, "state%u\t%llu\n", i,
			       kसमय_प्रकारo_ms(stats->समय_in_state[i]));
	पूर्ण
	spin_unlock(&stats->lock);

	वापस len;
पूर्ण

अटल sमाप_प्रकार
reset_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
	    माप_प्रकार count)
अणु
	काष्ठा thermal_cooling_device *cdev = to_cooling_device(dev);
	काष्ठा cooling_dev_stats *stats = cdev->stats;
	पूर्णांक i, states = stats->max_states;

	spin_lock(&stats->lock);

	stats->total_trans = 0;
	stats->last_समय = kसमय_get();
	स_रखो(stats->trans_table, 0,
	       states * states * माप(*stats->trans_table));

	क्रम (i = 0; i < stats->max_states; i++)
		stats->समय_in_state[i] = kसमय_set(0, 0);

	spin_unlock(&stats->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार trans_table_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा thermal_cooling_device *cdev = to_cooling_device(dev);
	काष्ठा cooling_dev_stats *stats = cdev->stats;
	sमाप_प्रकार len = 0;
	पूर्णांक i, j;

	len += snम_लिखो(buf + len, PAGE_SIZE - len, " From  :    To\n");
	len += snम_लिखो(buf + len, PAGE_SIZE - len, "       : ");
	क्रम (i = 0; i < stats->max_states; i++) अणु
		अगर (len >= PAGE_SIZE)
			अवरोध;
		len += snम_लिखो(buf + len, PAGE_SIZE - len, "state%2u  ", i);
	पूर्ण
	अगर (len >= PAGE_SIZE)
		वापस PAGE_SIZE;

	len += snम_लिखो(buf + len, PAGE_SIZE - len, "\n");

	क्रम (i = 0; i < stats->max_states; i++) अणु
		अगर (len >= PAGE_SIZE)
			अवरोध;

		len += snम_लिखो(buf + len, PAGE_SIZE - len, "state%2u:", i);

		क्रम (j = 0; j < stats->max_states; j++) अणु
			अगर (len >= PAGE_SIZE)
				अवरोध;
			len += snम_लिखो(buf + len, PAGE_SIZE - len, "%8u ",
				stats->trans_table[i * stats->max_states + j]);
		पूर्ण
		अगर (len >= PAGE_SIZE)
			अवरोध;
		len += snम_लिखो(buf + len, PAGE_SIZE - len, "\n");
	पूर्ण

	अगर (len >= PAGE_SIZE) अणु
		pr_warn_once("Thermal transition table exceeds PAGE_SIZE. Disabling\n");
		वापस -EFBIG;
	पूर्ण
	वापस len;
पूर्ण

अटल DEVICE_ATTR_RO(total_trans);
अटल DEVICE_ATTR_RO(समय_in_state_ms);
अटल DEVICE_ATTR_WO(reset);
अटल DEVICE_ATTR_RO(trans_table);

अटल काष्ठा attribute *cooling_device_stats_attrs[] = अणु
	&dev_attr_total_trans.attr,
	&dev_attr_समय_in_state_ms.attr,
	&dev_attr_reset.attr,
	&dev_attr_trans_table.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group cooling_device_stats_attr_group = अणु
	.attrs = cooling_device_stats_attrs,
	.name = "stats"
पूर्ण;

अटल व्योम cooling_device_stats_setup(काष्ठा thermal_cooling_device *cdev)
अणु
	काष्ठा cooling_dev_stats *stats;
	अचिन्हित दीर्घ states;
	पूर्णांक var;

	अगर (cdev->ops->get_max_state(cdev, &states))
		वापस;

	states++; /* Total number of states is highest state + 1 */

	var = माप(*stats);
	var += माप(*stats->समय_in_state) * states;
	var += माप(*stats->trans_table) * states * states;

	stats = kzalloc(var, GFP_KERNEL);
	अगर (!stats)
		वापस;

	stats->समय_in_state = (kसमय_प्रकार *)(stats + 1);
	stats->trans_table = (अचिन्हित पूर्णांक *)(stats->समय_in_state + states);
	cdev->stats = stats;
	stats->last_समय = kसमय_get();
	stats->max_states = states;

	spin_lock_init(&stats->lock);

	/* Fill the empty slot left in cooling_device_attr_groups */
	var = ARRAY_SIZE(cooling_device_attr_groups) - 2;
	cooling_device_attr_groups[var] = &cooling_device_stats_attr_group;
पूर्ण

अटल व्योम cooling_device_stats_destroy(काष्ठा thermal_cooling_device *cdev)
अणु
	kमुक्त(cdev->stats);
	cdev->stats = शून्य;
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम
cooling_device_stats_setup(काष्ठा thermal_cooling_device *cdev) अणुपूर्ण
अटल अंतरभूत व्योम
cooling_device_stats_destroy(काष्ठा thermal_cooling_device *cdev) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_THERMAL_STATISTICS */

व्योम thermal_cooling_device_setup_sysfs(काष्ठा thermal_cooling_device *cdev)
अणु
	cooling_device_stats_setup(cdev);
	cdev->device.groups = cooling_device_attr_groups;
पूर्ण

व्योम thermal_cooling_device_destroy_sysfs(काष्ठा thermal_cooling_device *cdev)
अणु
	cooling_device_stats_destroy(cdev);
पूर्ण

/* these helper will be used only at the समय of bindig */
sमाप_प्रकार
trip_poपूर्णांक_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा thermal_instance *instance;

	instance =
	    container_of(attr, काष्ठा thermal_instance, attr);

	वापस प्र_लिखो(buf, "%d\n", instance->trip);
पूर्ण

sमाप_प्रकार
weight_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा thermal_instance *instance;

	instance = container_of(attr, काष्ठा thermal_instance, weight_attr);

	वापस प्र_लिखो(buf, "%d\n", instance->weight);
पूर्ण

sमाप_प्रकार weight_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा thermal_instance *instance;
	पूर्णांक ret, weight;

	ret = kstrtoपूर्णांक(buf, 0, &weight);
	अगर (ret)
		वापस ret;

	instance = container_of(attr, काष्ठा thermal_instance, weight_attr);
	instance->weight = weight;

	वापस count;
पूर्ण
