<शैली गुरु>
/*
 * sysfs.c - sysfs support
 *
 * (C) 2006-2007 Shaohua Li <shaohua.li@पूर्णांकel.com>
 *
 * This code is licenced under the GPL.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/cpu.h>
#समावेश <linux/completion.h>
#समावेश <linux/capability.h>
#समावेश <linux/device.h>
#समावेश <linux/kobject.h>

#समावेश "cpuidle.h"

अटल sमाप_प्रकार show_available_governors(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	sमाप_प्रकार i = 0;
	काष्ठा cpuidle_governor *पंचांगp;

	mutex_lock(&cpuidle_lock);
	list_क्रम_each_entry(पंचांगp, &cpuidle_governors, governor_list) अणु
		अगर (i >= (sमाप_प्रकार) (PAGE_SIZE - (CPUIDLE_NAME_LEN + 2)))
			जाओ out;

		i += scnम_लिखो(&buf[i], CPUIDLE_NAME_LEN + 1, "%s ", पंचांगp->name);
	पूर्ण

out:
	i+= प्र_लिखो(&buf[i], "\n");
	mutex_unlock(&cpuidle_lock);
	वापस i;
पूर्ण

अटल sमाप_प्रकार show_current_driver(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	sमाप_प्रकार ret;
	काष्ठा cpuidle_driver *drv;

	spin_lock(&cpuidle_driver_lock);
	drv = cpuidle_get_driver();
	अगर (drv)
		ret = प्र_लिखो(buf, "%s\n", drv->name);
	अन्यथा
		ret = प्र_लिखो(buf, "none\n");
	spin_unlock(&cpuidle_driver_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार show_current_governor(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	sमाप_प्रकार ret;

	mutex_lock(&cpuidle_lock);
	अगर (cpuidle_curr_governor)
		ret = प्र_लिखो(buf, "%s\n", cpuidle_curr_governor->name);
	अन्यथा
		ret = प्र_लिखो(buf, "none\n");
	mutex_unlock(&cpuidle_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार store_current_governor(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अक्षर gov_name[CPUIDLE_NAME_LEN + 1];
	पूर्णांक ret;
	काष्ठा cpuidle_governor *gov;

	ret = माला_पूछो(buf, "%" __stringअगरy(CPUIDLE_NAME_LEN) "s", gov_name);
	अगर (ret != 1)
		वापस -EINVAL;

	mutex_lock(&cpuidle_lock);
	ret = -EINVAL;
	list_क्रम_each_entry(gov, &cpuidle_governors, governor_list) अणु
		अगर (!म_भेदन(gov->name, gov_name, CPUIDLE_NAME_LEN)) अणु
			ret = cpuidle_चयन_governor(gov);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&cpuidle_lock);

	वापस ret ? ret : count;
पूर्ण

अटल DEVICE_ATTR(available_governors, 0444, show_available_governors, शून्य);
अटल DEVICE_ATTR(current_driver, 0444, show_current_driver, शून्य);
अटल DEVICE_ATTR(current_governor, 0644, show_current_governor,
				   store_current_governor);
अटल DEVICE_ATTR(current_governor_ro, 0444, show_current_governor, शून्य);

अटल काष्ठा attribute *cpuidle_attrs[] = अणु
	&dev_attr_available_governors.attr,
	&dev_attr_current_driver.attr,
	&dev_attr_current_governor.attr,
	&dev_attr_current_governor_ro.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group cpuidle_attr_group = अणु
	.attrs = cpuidle_attrs,
	.name = "cpuidle",
पूर्ण;

/**
 * cpuidle_add_पूर्णांकerface - add CPU global sysfs attributes
 * @dev: the target device
 */
पूर्णांक cpuidle_add_पूर्णांकerface(काष्ठा device *dev)
अणु
	वापस sysfs_create_group(&dev->kobj, &cpuidle_attr_group);
पूर्ण

/**
 * cpuidle_हटाओ_पूर्णांकerface - हटाओ CPU global sysfs attributes
 * @dev: the target device
 */
व्योम cpuidle_हटाओ_पूर्णांकerface(काष्ठा device *dev)
अणु
	sysfs_हटाओ_group(&dev->kobj, &cpuidle_attr_group);
पूर्ण

काष्ठा cpuidle_attr अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा cpuidle_device *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा cpuidle_device *, स्थिर अक्षर *, माप_प्रकार count);
पूर्ण;

#घोषणा attr_to_cpuidleattr(a) container_of(a, काष्ठा cpuidle_attr, attr)

काष्ठा cpuidle_device_kobj अणु
	काष्ठा cpuidle_device *dev;
	काष्ठा completion kobj_unरेजिस्टर;
	काष्ठा kobject kobj;
पूर्ण;

अटल अंतरभूत काष्ठा cpuidle_device *to_cpuidle_device(काष्ठा kobject *kobj)
अणु
	काष्ठा cpuidle_device_kobj *kdev =
		container_of(kobj, काष्ठा cpuidle_device_kobj, kobj);

	वापस kdev->dev;
पूर्ण

अटल sमाप_प्रकार cpuidle_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			    अक्षर *buf)
अणु
	पूर्णांक ret = -EIO;
	काष्ठा cpuidle_device *dev = to_cpuidle_device(kobj);
	काष्ठा cpuidle_attr *cattr = attr_to_cpuidleattr(attr);

	अगर (cattr->show) अणु
		mutex_lock(&cpuidle_lock);
		ret = cattr->show(dev, buf);
		mutex_unlock(&cpuidle_lock);
	पूर्ण
	वापस ret;
पूर्ण

अटल sमाप_प्रकार cpuidle_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret = -EIO;
	काष्ठा cpuidle_device *dev = to_cpuidle_device(kobj);
	काष्ठा cpuidle_attr *cattr = attr_to_cpuidleattr(attr);

	अगर (cattr->store) अणु
		mutex_lock(&cpuidle_lock);
		ret = cattr->store(dev, buf, count);
		mutex_unlock(&cpuidle_lock);
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops cpuidle_sysfs_ops = अणु
	.show = cpuidle_show,
	.store = cpuidle_store,
पूर्ण;

अटल व्योम cpuidle_sysfs_release(काष्ठा kobject *kobj)
अणु
	काष्ठा cpuidle_device_kobj *kdev =
		container_of(kobj, काष्ठा cpuidle_device_kobj, kobj);

	complete(&kdev->kobj_unरेजिस्टर);
पूर्ण

अटल काष्ठा kobj_type ktype_cpuidle = अणु
	.sysfs_ops = &cpuidle_sysfs_ops,
	.release = cpuidle_sysfs_release,
पूर्ण;

काष्ठा cpuidle_state_attr अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा cpuidle_state *, \
					काष्ठा cpuidle_state_usage *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा cpuidle_state *, \
			काष्ठा cpuidle_state_usage *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

#घोषणा define_one_state_ro(_name, show) \
अटल काष्ठा cpuidle_state_attr attr_##_name = __ATTR(_name, 0444, show, शून्य)

#घोषणा define_one_state_rw(_name, show, store) \
अटल काष्ठा cpuidle_state_attr attr_##_name = __ATTR(_name, 0644, show, store)

#घोषणा define_show_state_function(_name) \
अटल sमाप_प्रकार show_state_##_name(काष्ठा cpuidle_state *state, \
			 काष्ठा cpuidle_state_usage *state_usage, अक्षर *buf) \
अणु \
	वापस प्र_लिखो(buf, "%u\n", state->_name);\
पूर्ण

#घोषणा define_show_state_ull_function(_name) \
अटल sमाप_प्रकार show_state_##_name(काष्ठा cpuidle_state *state, \
				  काष्ठा cpuidle_state_usage *state_usage, \
				  अक्षर *buf)				\
अणु \
	वापस प्र_लिखो(buf, "%llu\n", state_usage->_name);\
पूर्ण

#घोषणा define_show_state_str_function(_name) \
अटल sमाप_प्रकार show_state_##_name(काष्ठा cpuidle_state *state, \
				  काष्ठा cpuidle_state_usage *state_usage, \
				  अक्षर *buf)				\
अणु \
	अगर (state->_name[0] == '\0')\
		वापस प्र_लिखो(buf, "<null>\n");\
	वापस प्र_लिखो(buf, "%s\n", state->_name);\
पूर्ण

#घोषणा define_show_state_समय_function(_name) \
अटल sमाप_प्रकार show_state_##_name(काष्ठा cpuidle_state *state, \
				  काष्ठा cpuidle_state_usage *state_usage, \
				  अक्षर *buf) \
अणु \
	वापस प्र_लिखो(buf, "%llu\n", kसमय_प्रकारo_us(state->_name##_ns)); \
पूर्ण

define_show_state_समय_function(निकास_latency)
define_show_state_समय_function(target_residency)
define_show_state_function(घातer_usage)
define_show_state_ull_function(usage)
define_show_state_ull_function(rejected)
define_show_state_str_function(name)
define_show_state_str_function(desc)
define_show_state_ull_function(above)
define_show_state_ull_function(below)

अटल sमाप_प्रकार show_state_समय(काष्ठा cpuidle_state *state,
			       काष्ठा cpuidle_state_usage *state_usage,
			       अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu\n", kसमय_प्रकारo_us(state_usage->समय_ns));
पूर्ण

अटल sमाप_प्रकार show_state_disable(काष्ठा cpuidle_state *state,
				  काष्ठा cpuidle_state_usage *state_usage,
				  अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%llu\n",
		       state_usage->disable & CPUIDLE_STATE_DISABLED_BY_USER);
पूर्ण

अटल sमाप_प्रकार store_state_disable(काष्ठा cpuidle_state *state,
				   काष्ठा cpuidle_state_usage *state_usage,
				   स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक value;
	पूर्णांक err;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	err = kstrtouपूर्णांक(buf, 0, &value);
	अगर (err)
		वापस err;

	अगर (value)
		state_usage->disable |= CPUIDLE_STATE_DISABLED_BY_USER;
	अन्यथा
		state_usage->disable &= ~CPUIDLE_STATE_DISABLED_BY_USER;

	वापस size;
पूर्ण

अटल sमाप_प्रकार show_state_शेष_status(काष्ठा cpuidle_state *state,
					  काष्ठा cpuidle_state_usage *state_usage,
					  अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n",
		       state->flags & CPUIDLE_FLAG_OFF ? "disabled" : "enabled");
पूर्ण

define_one_state_ro(name, show_state_name);
define_one_state_ro(desc, show_state_desc);
define_one_state_ro(latency, show_state_निकास_latency);
define_one_state_ro(residency, show_state_target_residency);
define_one_state_ro(घातer, show_state_घातer_usage);
define_one_state_ro(usage, show_state_usage);
define_one_state_ro(rejected, show_state_rejected);
define_one_state_ro(समय, show_state_समय);
define_one_state_rw(disable, show_state_disable, store_state_disable);
define_one_state_ro(above, show_state_above);
define_one_state_ro(below, show_state_below);
define_one_state_ro(शेष_status, show_state_शेष_status);

अटल काष्ठा attribute *cpuidle_state_शेष_attrs[] = अणु
	&attr_name.attr,
	&attr_desc.attr,
	&attr_latency.attr,
	&attr_residency.attr,
	&attr_घातer.attr,
	&attr_usage.attr,
	&attr_rejected.attr,
	&attr_समय.attr,
	&attr_disable.attr,
	&attr_above.attr,
	&attr_below.attr,
	&attr_शेष_status.attr,
	शून्य
पूर्ण;

काष्ठा cpuidle_state_kobj अणु
	काष्ठा cpuidle_state *state;
	काष्ठा cpuidle_state_usage *state_usage;
	काष्ठा completion kobj_unरेजिस्टर;
	काष्ठा kobject kobj;
	काष्ठा cpuidle_device *device;
पूर्ण;

#अगर_घोषित CONFIG_SUSPEND
#घोषणा define_show_state_s2idle_ull_function(_name) \
अटल sमाप_प्रकार show_state_s2idle_##_name(काष्ठा cpuidle_state *state, \
					 काष्ठा cpuidle_state_usage *state_usage, \
					 अक्षर *buf)				\
अणु \
	वापस प्र_लिखो(buf, "%llu\n", state_usage->s2idle_##_name);\
पूर्ण

define_show_state_s2idle_ull_function(usage);
define_show_state_s2idle_ull_function(समय);

#घोषणा define_one_state_s2idle_ro(_name, show) \
अटल काष्ठा cpuidle_state_attr attr_s2idle_##_name = \
	__ATTR(_name, 0444, show, शून्य)

define_one_state_s2idle_ro(usage, show_state_s2idle_usage);
define_one_state_s2idle_ro(समय, show_state_s2idle_समय);

अटल काष्ठा attribute *cpuidle_state_s2idle_attrs[] = अणु
	&attr_s2idle_usage.attr,
	&attr_s2idle_समय.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group cpuidle_state_s2idle_group = अणु
	.name	= "s2idle",
	.attrs	= cpuidle_state_s2idle_attrs,
पूर्ण;

अटल व्योम cpuidle_add_s2idle_attr_group(काष्ठा cpuidle_state_kobj *kobj)
अणु
	पूर्णांक ret;

	अगर (!kobj->state->enter_s2idle)
		वापस;

	ret = sysfs_create_group(&kobj->kobj, &cpuidle_state_s2idle_group);
	अगर (ret)
		pr_debug("%s: sysfs attribute group not created\n", __func__);
पूर्ण

अटल व्योम cpuidle_हटाओ_s2idle_attr_group(काष्ठा cpuidle_state_kobj *kobj)
अणु
	अगर (kobj->state->enter_s2idle)
		sysfs_हटाओ_group(&kobj->kobj, &cpuidle_state_s2idle_group);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cpuidle_add_s2idle_attr_group(काष्ठा cpuidle_state_kobj *kobj) अणु पूर्ण
अटल अंतरभूत व्योम cpuidle_हटाओ_s2idle_attr_group(काष्ठा cpuidle_state_kobj *kobj) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_SUSPEND */

#घोषणा kobj_to_state_obj(k) container_of(k, काष्ठा cpuidle_state_kobj, kobj)
#घोषणा kobj_to_state(k) (kobj_to_state_obj(k)->state)
#घोषणा kobj_to_state_usage(k) (kobj_to_state_obj(k)->state_usage)
#घोषणा kobj_to_device(k) (kobj_to_state_obj(k)->device)
#घोषणा attr_to_stateattr(a) container_of(a, काष्ठा cpuidle_state_attr, attr)

अटल sमाप_प्रकार cpuidle_state_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				  अक्षर *buf)
अणु
	पूर्णांक ret = -EIO;
	काष्ठा cpuidle_state *state = kobj_to_state(kobj);
	काष्ठा cpuidle_state_usage *state_usage = kobj_to_state_usage(kobj);
	काष्ठा cpuidle_state_attr *cattr = attr_to_stateattr(attr);

	अगर (cattr->show)
		ret = cattr->show(state, state_usage, buf);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार cpuidle_state_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret = -EIO;
	काष्ठा cpuidle_state *state = kobj_to_state(kobj);
	काष्ठा cpuidle_state_usage *state_usage = kobj_to_state_usage(kobj);
	काष्ठा cpuidle_state_attr *cattr = attr_to_stateattr(attr);
	काष्ठा cpuidle_device *dev = kobj_to_device(kobj);

	अगर (cattr->store)
		ret = cattr->store(state, state_usage, buf, size);

	/* reset poll समय cache */
	dev->poll_limit_ns = 0;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops cpuidle_state_sysfs_ops = अणु
	.show = cpuidle_state_show,
	.store = cpuidle_state_store,
पूर्ण;

अटल व्योम cpuidle_state_sysfs_release(काष्ठा kobject *kobj)
अणु
	काष्ठा cpuidle_state_kobj *state_obj = kobj_to_state_obj(kobj);

	complete(&state_obj->kobj_unरेजिस्टर);
पूर्ण

अटल काष्ठा kobj_type ktype_state_cpuidle = अणु
	.sysfs_ops = &cpuidle_state_sysfs_ops,
	.शेष_attrs = cpuidle_state_शेष_attrs,
	.release = cpuidle_state_sysfs_release,
पूर्ण;

अटल अंतरभूत व्योम cpuidle_मुक्त_state_kobj(काष्ठा cpuidle_device *device, पूर्णांक i)
अणु
	cpuidle_हटाओ_s2idle_attr_group(device->kobjs[i]);
	kobject_put(&device->kobjs[i]->kobj);
	रुको_क्रम_completion(&device->kobjs[i]->kobj_unरेजिस्टर);
	kमुक्त(device->kobjs[i]);
	device->kobjs[i] = शून्य;
पूर्ण

/**
 * cpuidle_add_state_sysfs - adds cpuidle states sysfs attributes
 * @device: the target device
 */
अटल पूर्णांक cpuidle_add_state_sysfs(काष्ठा cpuidle_device *device)
अणु
	पूर्णांक i, ret = -ENOMEM;
	काष्ठा cpuidle_state_kobj *kobj;
	काष्ठा cpuidle_device_kobj *kdev = device->kobj_dev;
	काष्ठा cpuidle_driver *drv = cpuidle_get_cpu_driver(device);

	/* state statistics */
	क्रम (i = 0; i < drv->state_count; i++) अणु
		kobj = kzalloc(माप(काष्ठा cpuidle_state_kobj), GFP_KERNEL);
		अगर (!kobj) अणु
			ret = -ENOMEM;
			जाओ error_state;
		पूर्ण
		kobj->state = &drv->states[i];
		kobj->state_usage = &device->states_usage[i];
		kobj->device = device;
		init_completion(&kobj->kobj_unरेजिस्टर);

		ret = kobject_init_and_add(&kobj->kobj, &ktype_state_cpuidle,
					   &kdev->kobj, "state%d", i);
		अगर (ret) अणु
			kobject_put(&kobj->kobj);
			जाओ error_state;
		पूर्ण
		cpuidle_add_s2idle_attr_group(kobj);
		kobject_uevent(&kobj->kobj, KOBJ_ADD);
		device->kobjs[i] = kobj;
	पूर्ण

	वापस 0;

error_state:
	क्रम (i = i - 1; i >= 0; i--)
		cpuidle_मुक्त_state_kobj(device, i);
	वापस ret;
पूर्ण

/**
 * cpuidle_हटाओ_driver_sysfs - हटाओs the cpuidle states sysfs attributes
 * @device: the target device
 */
अटल व्योम cpuidle_हटाओ_state_sysfs(काष्ठा cpuidle_device *device)
अणु
	काष्ठा cpuidle_driver *drv = cpuidle_get_cpu_driver(device);
	पूर्णांक i;

	क्रम (i = 0; i < drv->state_count; i++)
		cpuidle_मुक्त_state_kobj(device, i);
पूर्ण

#अगर_घोषित CONFIG_CPU_IDLE_MULTIPLE_DRIVERS
#घोषणा kobj_to_driver_kobj(k) container_of(k, काष्ठा cpuidle_driver_kobj, kobj)
#घोषणा attr_to_driver_attr(a) container_of(a, काष्ठा cpuidle_driver_attr, attr)

#घोषणा define_one_driver_ro(_name, show)                       \
	अटल काष्ठा cpuidle_driver_attr attr_driver_##_name = \
		__ATTR(_name, 0444, show, शून्य)

काष्ठा cpuidle_driver_kobj अणु
	काष्ठा cpuidle_driver *drv;
	काष्ठा completion kobj_unरेजिस्टर;
	काष्ठा kobject kobj;
पूर्ण;

काष्ठा cpuidle_driver_attr अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा cpuidle_driver *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा cpuidle_driver *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

अटल sमाप_प्रकार show_driver_name(काष्ठा cpuidle_driver *drv, अक्षर *buf)
अणु
	sमाप_प्रकार ret;

	spin_lock(&cpuidle_driver_lock);
	ret = प्र_लिखो(buf, "%s\n", drv ? drv->name : "none");
	spin_unlock(&cpuidle_driver_lock);

	वापस ret;
पूर्ण

अटल व्योम cpuidle_driver_sysfs_release(काष्ठा kobject *kobj)
अणु
	काष्ठा cpuidle_driver_kobj *driver_kobj = kobj_to_driver_kobj(kobj);
	complete(&driver_kobj->kobj_unरेजिस्टर);
पूर्ण

अटल sमाप_प्रकार cpuidle_driver_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				   अक्षर *buf)
अणु
	पूर्णांक ret = -EIO;
	काष्ठा cpuidle_driver_kobj *driver_kobj = kobj_to_driver_kobj(kobj);
	काष्ठा cpuidle_driver_attr *dattr = attr_to_driver_attr(attr);

	अगर (dattr->show)
		ret = dattr->show(driver_kobj->drv, buf);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार cpuidle_driver_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret = -EIO;
	काष्ठा cpuidle_driver_kobj *driver_kobj = kobj_to_driver_kobj(kobj);
	काष्ठा cpuidle_driver_attr *dattr = attr_to_driver_attr(attr);

	अगर (dattr->store)
		ret = dattr->store(driver_kobj->drv, buf, size);

	वापस ret;
पूर्ण

define_one_driver_ro(name, show_driver_name);

अटल स्थिर काष्ठा sysfs_ops cpuidle_driver_sysfs_ops = अणु
	.show = cpuidle_driver_show,
	.store = cpuidle_driver_store,
पूर्ण;

अटल काष्ठा attribute *cpuidle_driver_शेष_attrs[] = अणु
	&attr_driver_name.attr,
	शून्य
पूर्ण;

अटल काष्ठा kobj_type ktype_driver_cpuidle = अणु
	.sysfs_ops = &cpuidle_driver_sysfs_ops,
	.शेष_attrs = cpuidle_driver_शेष_attrs,
	.release = cpuidle_driver_sysfs_release,
पूर्ण;

/**
 * cpuidle_add_driver_sysfs - adds the driver name sysfs attribute
 * @dev: the target device
 */
अटल पूर्णांक cpuidle_add_driver_sysfs(काष्ठा cpuidle_device *dev)
अणु
	काष्ठा cpuidle_driver_kobj *kdrv;
	काष्ठा cpuidle_device_kobj *kdev = dev->kobj_dev;
	काष्ठा cpuidle_driver *drv = cpuidle_get_cpu_driver(dev);
	पूर्णांक ret;

	kdrv = kzalloc(माप(*kdrv), GFP_KERNEL);
	अगर (!kdrv)
		वापस -ENOMEM;

	kdrv->drv = drv;
	init_completion(&kdrv->kobj_unरेजिस्टर);

	ret = kobject_init_and_add(&kdrv->kobj, &ktype_driver_cpuidle,
				   &kdev->kobj, "driver");
	अगर (ret) अणु
		kobject_put(&kdrv->kobj);
		वापस ret;
	पूर्ण

	kobject_uevent(&kdrv->kobj, KOBJ_ADD);
	dev->kobj_driver = kdrv;

	वापस ret;
पूर्ण

/**
 * cpuidle_हटाओ_driver_sysfs - हटाओs the driver name sysfs attribute
 * @dev: the target device
 */
अटल व्योम cpuidle_हटाओ_driver_sysfs(काष्ठा cpuidle_device *dev)
अणु
	काष्ठा cpuidle_driver_kobj *kdrv = dev->kobj_driver;
	kobject_put(&kdrv->kobj);
	रुको_क्रम_completion(&kdrv->kobj_unरेजिस्टर);
	kमुक्त(kdrv);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक cpuidle_add_driver_sysfs(काष्ठा cpuidle_device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cpuidle_हटाओ_driver_sysfs(काष्ठा cpuidle_device *dev)
अणु
	;
पूर्ण
#पूर्ण_अगर

/**
 * cpuidle_add_device_sysfs - adds device specअगरic sysfs attributes
 * @device: the target device
 */
पूर्णांक cpuidle_add_device_sysfs(काष्ठा cpuidle_device *device)
अणु
	पूर्णांक ret;

	ret = cpuidle_add_state_sysfs(device);
	अगर (ret)
		वापस ret;

	ret = cpuidle_add_driver_sysfs(device);
	अगर (ret)
		cpuidle_हटाओ_state_sysfs(device);
	वापस ret;
पूर्ण

/**
 * cpuidle_हटाओ_device_sysfs : हटाओs device specअगरic sysfs attributes
 * @device : the target device
 */
व्योम cpuidle_हटाओ_device_sysfs(काष्ठा cpuidle_device *device)
अणु
	cpuidle_हटाओ_driver_sysfs(device);
	cpuidle_हटाओ_state_sysfs(device);
पूर्ण

/**
 * cpuidle_add_sysfs - creates a sysfs instance क्रम the target device
 * @dev: the target device
 */
पूर्णांक cpuidle_add_sysfs(काष्ठा cpuidle_device *dev)
अणु
	काष्ठा cpuidle_device_kobj *kdev;
	काष्ठा device *cpu_dev = get_cpu_device((अचिन्हित दीर्घ)dev->cpu);
	पूर्णांक error;

	/*
	 * Return अगर cpu_device is not setup क्रम this CPU.
	 *
	 * This could happen अगर the arch did not set up cpu_device
	 * since this CPU is not in cpu_present mask and the
	 * driver did not send a correct CPU mask during registration.
	 * Without this check we would end up passing bogus
	 * value क्रम &cpu_dev->kobj in kobject_init_and_add()
	 */
	अगर (!cpu_dev)
		वापस -ENODEV;

	kdev = kzalloc(माप(*kdev), GFP_KERNEL);
	अगर (!kdev)
		वापस -ENOMEM;
	kdev->dev = dev;
	dev->kobj_dev = kdev;

	init_completion(&kdev->kobj_unरेजिस्टर);

	error = kobject_init_and_add(&kdev->kobj, &ktype_cpuidle, &cpu_dev->kobj,
				   "cpuidle");
	अगर (error) अणु
		kobject_put(&kdev->kobj);
		वापस error;
	पूर्ण

	kobject_uevent(&kdev->kobj, KOBJ_ADD);

	वापस 0;
पूर्ण

/**
 * cpuidle_हटाओ_sysfs - deletes a sysfs instance on the target device
 * @dev: the target device
 */
व्योम cpuidle_हटाओ_sysfs(काष्ठा cpuidle_device *dev)
अणु
	काष्ठा cpuidle_device_kobj *kdev = dev->kobj_dev;

	kobject_put(&kdev->kobj);
	रुको_क्रम_completion(&kdev->kobj_unरेजिस्टर);
	kमुक्त(kdev);
पूर्ण
