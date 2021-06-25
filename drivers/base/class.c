<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * class.c - basic device class management
 *
 * Copyright (c) 2002-3 Patrick Mochel
 * Copyright (c) 2002-3 Open Source Development Lअसल
 * Copyright (c) 2003-2004 Greg Kroah-Harपंचांगan
 * Copyright (c) 2003-2004 IBM Corp.
 */

#समावेश <linux/device/class.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/kdev_t.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/genhd.h>
#समावेश <linux/mutex.h>
#समावेश "base.h"

#घोषणा to_class_attr(_attr) container_of(_attr, काष्ठा class_attribute, attr)

अटल sमाप_प्रकार class_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा class_attribute *class_attr = to_class_attr(attr);
	काष्ठा subsys_निजी *cp = to_subsys_निजी(kobj);
	sमाप_प्रकार ret = -EIO;

	अगर (class_attr->show)
		ret = class_attr->show(cp->class, class_attr, buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार class_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा class_attribute *class_attr = to_class_attr(attr);
	काष्ठा subsys_निजी *cp = to_subsys_निजी(kobj);
	sमाप_प्रकार ret = -EIO;

	अगर (class_attr->store)
		ret = class_attr->store(cp->class, class_attr, buf, count);
	वापस ret;
पूर्ण

अटल व्योम class_release(काष्ठा kobject *kobj)
अणु
	काष्ठा subsys_निजी *cp = to_subsys_निजी(kobj);
	काष्ठा class *class = cp->class;

	pr_debug("class '%s': release.\n", class->name);

	अगर (class->class_release)
		class->class_release(class);
	अन्यथा
		pr_debug("class '%s' does not have a release() function, "
			 "be careful\n", class->name);

	kमुक्त(cp);
पूर्ण

अटल स्थिर काष्ठा kobj_ns_type_operations *class_child_ns_type(काष्ठा kobject *kobj)
अणु
	काष्ठा subsys_निजी *cp = to_subsys_निजी(kobj);
	काष्ठा class *class = cp->class;

	वापस class->ns_type;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops class_sysfs_ops = अणु
	.show	   = class_attr_show,
	.store	   = class_attr_store,
पूर्ण;

अटल काष्ठा kobj_type class_ktype = अणु
	.sysfs_ops	= &class_sysfs_ops,
	.release	= class_release,
	.child_ns_type	= class_child_ns_type,
पूर्ण;

/* Hotplug events क्रम classes go to the class subsys */
अटल काष्ठा kset *class_kset;


पूर्णांक class_create_file_ns(काष्ठा class *cls, स्थिर काष्ठा class_attribute *attr,
			 स्थिर व्योम *ns)
अणु
	पूर्णांक error;

	अगर (cls)
		error = sysfs_create_file_ns(&cls->p->subsys.kobj,
					     &attr->attr, ns);
	अन्यथा
		error = -EINVAL;
	वापस error;
पूर्ण

व्योम class_हटाओ_file_ns(काष्ठा class *cls, स्थिर काष्ठा class_attribute *attr,
			  स्थिर व्योम *ns)
अणु
	अगर (cls)
		sysfs_हटाओ_file_ns(&cls->p->subsys.kobj, &attr->attr, ns);
पूर्ण

अटल काष्ठा class *class_get(काष्ठा class *cls)
अणु
	अगर (cls)
		kset_get(&cls->p->subsys);
	वापस cls;
पूर्ण

अटल व्योम class_put(काष्ठा class *cls)
अणु
	अगर (cls)
		kset_put(&cls->p->subsys);
पूर्ण

अटल काष्ठा device *klist_class_to_dev(काष्ठा klist_node *n)
अणु
	काष्ठा device_निजी *p = to_device_निजी_class(n);
	वापस p->device;
पूर्ण

अटल व्योम klist_class_dev_get(काष्ठा klist_node *n)
अणु
	काष्ठा device *dev = klist_class_to_dev(n);

	get_device(dev);
पूर्ण

अटल व्योम klist_class_dev_put(काष्ठा klist_node *n)
अणु
	काष्ठा device *dev = klist_class_to_dev(n);

	put_device(dev);
पूर्ण

अटल पूर्णांक class_add_groups(काष्ठा class *cls,
			    स्थिर काष्ठा attribute_group **groups)
अणु
	वापस sysfs_create_groups(&cls->p->subsys.kobj, groups);
पूर्ण

अटल व्योम class_हटाओ_groups(काष्ठा class *cls,
				स्थिर काष्ठा attribute_group **groups)
अणु
	वापस sysfs_हटाओ_groups(&cls->p->subsys.kobj, groups);
पूर्ण

पूर्णांक __class_रेजिस्टर(काष्ठा class *cls, काष्ठा lock_class_key *key)
अणु
	काष्ठा subsys_निजी *cp;
	पूर्णांक error;

	pr_debug("device class '%s': registering\n", cls->name);

	cp = kzalloc(माप(*cp), GFP_KERNEL);
	अगर (!cp)
		वापस -ENOMEM;
	klist_init(&cp->klist_devices, klist_class_dev_get, klist_class_dev_put);
	INIT_LIST_HEAD(&cp->पूर्णांकerfaces);
	kset_init(&cp->glue_dirs);
	__mutex_init(&cp->mutex, "subsys mutex", key);
	error = kobject_set_name(&cp->subsys.kobj, "%s", cls->name);
	अगर (error) अणु
		kमुक्त(cp);
		वापस error;
	पूर्ण

	/* set the शेष /sys/dev directory क्रम devices of this class */
	अगर (!cls->dev_kobj)
		cls->dev_kobj = sysfs_dev_अक्षर_kobj;

#अगर defined(CONFIG_BLOCK)
	/* let the block class directory show up in the root of sysfs */
	अगर (!sysfs_deprecated || cls != &block_class)
		cp->subsys.kobj.kset = class_kset;
#अन्यथा
	cp->subsys.kobj.kset = class_kset;
#पूर्ण_अगर
	cp->subsys.kobj.ktype = &class_ktype;
	cp->class = cls;
	cls->p = cp;

	error = kset_रेजिस्टर(&cp->subsys);
	अगर (error) अणु
		kमुक्त(cp);
		वापस error;
	पूर्ण
	error = class_add_groups(class_get(cls), cls->class_groups);
	class_put(cls);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(__class_रेजिस्टर);

व्योम class_unरेजिस्टर(काष्ठा class *cls)
अणु
	pr_debug("device class '%s': unregistering\n", cls->name);
	class_हटाओ_groups(cls, cls->class_groups);
	kset_unरेजिस्टर(&cls->p->subsys);
पूर्ण

अटल व्योम class_create_release(काष्ठा class *cls)
अणु
	pr_debug("%s called for %s\n", __func__, cls->name);
	kमुक्त(cls);
पूर्ण

/**
 * __class_create - create a काष्ठा class काष्ठाure
 * @owner: poपूर्णांकer to the module that is to "own" this काष्ठा class
 * @name: poपूर्णांकer to a string क्रम the name of this class.
 * @key: the lock_class_key क्रम this class; used by mutex lock debugging
 *
 * This is used to create a काष्ठा class poपूर्णांकer that can then be used
 * in calls to device_create().
 *
 * Returns &काष्ठा class poपूर्णांकer on success, or ERR_PTR() on error.
 *
 * Note, the poपूर्णांकer created here is to be destroyed when finished by
 * making a call to class_destroy().
 */
काष्ठा class *__class_create(काष्ठा module *owner, स्थिर अक्षर *name,
			     काष्ठा lock_class_key *key)
अणु
	काष्ठा class *cls;
	पूर्णांक retval;

	cls = kzalloc(माप(*cls), GFP_KERNEL);
	अगर (!cls) अणु
		retval = -ENOMEM;
		जाओ error;
	पूर्ण

	cls->name = name;
	cls->owner = owner;
	cls->class_release = class_create_release;

	retval = __class_रेजिस्टर(cls, key);
	अगर (retval)
		जाओ error;

	वापस cls;

error:
	kमुक्त(cls);
	वापस ERR_PTR(retval);
पूर्ण
EXPORT_SYMBOL_GPL(__class_create);

/**
 * class_destroy - destroys a काष्ठा class काष्ठाure
 * @cls: poपूर्णांकer to the काष्ठा class that is to be destroyed
 *
 * Note, the poपूर्णांकer to be destroyed must have been created with a call
 * to class_create().
 */
व्योम class_destroy(काष्ठा class *cls)
अणु
	अगर ((cls == शून्य) || (IS_ERR(cls)))
		वापस;

	class_unरेजिस्टर(cls);
पूर्ण

/**
 * class_dev_iter_init - initialize class device iterator
 * @iter: class iterator to initialize
 * @class: the class we wanna iterate over
 * @start: the device to start iterating from, अगर any
 * @type: device_type of the devices to iterate over, शून्य क्रम all
 *
 * Initialize class iterator @iter such that it iterates over devices
 * of @class.  If @start is set, the list iteration will start there,
 * otherwise अगर it is शून्य, the iteration starts at the beginning of
 * the list.
 */
व्योम class_dev_iter_init(काष्ठा class_dev_iter *iter, काष्ठा class *class,
			 काष्ठा device *start, स्थिर काष्ठा device_type *type)
अणु
	काष्ठा klist_node *start_knode = शून्य;

	अगर (start)
		start_knode = &start->p->knode_class;
	klist_iter_init_node(&class->p->klist_devices, &iter->ki, start_knode);
	iter->type = type;
पूर्ण
EXPORT_SYMBOL_GPL(class_dev_iter_init);

/**
 * class_dev_iter_next - iterate to the next device
 * @iter: class iterator to proceed
 *
 * Proceed @iter to the next device and वापस it.  Returns शून्य अगर
 * iteration is complete.
 *
 * The वापसed device is referenced and won't be released till
 * iterator is proceed to the next device or निकासed.  The caller is
 * मुक्त to करो whatever it wants to करो with the device including
 * calling back पूर्णांकo class code.
 */
काष्ठा device *class_dev_iter_next(काष्ठा class_dev_iter *iter)
अणु
	काष्ठा klist_node *knode;
	काष्ठा device *dev;

	जबतक (1) अणु
		knode = klist_next(&iter->ki);
		अगर (!knode)
			वापस शून्य;
		dev = klist_class_to_dev(knode);
		अगर (!iter->type || iter->type == dev->type)
			वापस dev;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(class_dev_iter_next);

/**
 * class_dev_iter_निकास - finish iteration
 * @iter: class iterator to finish
 *
 * Finish an iteration.  Always call this function after iteration is
 * complete whether the iteration ran till the end or not.
 */
व्योम class_dev_iter_निकास(काष्ठा class_dev_iter *iter)
अणु
	klist_iter_निकास(&iter->ki);
पूर्ण
EXPORT_SYMBOL_GPL(class_dev_iter_निकास);

/**
 * class_क्रम_each_device - device iterator
 * @class: the class we're iterating
 * @start: the device to start with in the list, अगर any.
 * @data: data क्रम the callback
 * @fn: function to be called क्रम each device
 *
 * Iterate over @class's list of devices, and call @fn क्रम each,
 * passing it @data.  If @start is set, the list iteration will start
 * there, otherwise अगर it is शून्य, the iteration starts at the
 * beginning of the list.
 *
 * We check the वापस of @fn each समय. If it वापसs anything
 * other than 0, we अवरोध out and वापस that value.
 *
 * @fn is allowed to करो anything including calling back पूर्णांकo class
 * code.  There's no locking restriction.
 */
पूर्णांक class_क्रम_each_device(काष्ठा class *class, काष्ठा device *start,
			  व्योम *data, पूर्णांक (*fn)(काष्ठा device *, व्योम *))
अणु
	काष्ठा class_dev_iter iter;
	काष्ठा device *dev;
	पूर्णांक error = 0;

	अगर (!class)
		वापस -EINVAL;
	अगर (!class->p) अणु
		WARN(1, "%s called for class '%s' before it was initialized",
		     __func__, class->name);
		वापस -EINVAL;
	पूर्ण

	class_dev_iter_init(&iter, class, start, शून्य);
	जबतक ((dev = class_dev_iter_next(&iter))) अणु
		error = fn(dev, data);
		अगर (error)
			अवरोध;
	पूर्ण
	class_dev_iter_निकास(&iter);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(class_क्रम_each_device);

/**
 * class_find_device - device iterator क्रम locating a particular device
 * @class: the class we're iterating
 * @start: Device to begin with
 * @data: data क्रम the match function
 * @match: function to check device
 *
 * This is similar to the class_क्रम_each_dev() function above, but it
 * वापसs a reference to a device that is 'found' क्रम later use, as
 * determined by the @match callback.
 *
 * The callback should वापस 0 अगर the device करोesn't match and non-zero
 * अगर it करोes.  If the callback वापसs non-zero, this function will
 * वापस to the caller and not iterate over any more devices.
 *
 * Note, you will need to drop the reference with put_device() after use.
 *
 * @match is allowed to करो anything including calling back पूर्णांकo class
 * code.  There's no locking restriction.
 */
काष्ठा device *class_find_device(काष्ठा class *class, काष्ठा device *start,
				 स्थिर व्योम *data,
				 पूर्णांक (*match)(काष्ठा device *, स्थिर व्योम *))
अणु
	काष्ठा class_dev_iter iter;
	काष्ठा device *dev;

	अगर (!class)
		वापस शून्य;
	अगर (!class->p) अणु
		WARN(1, "%s called for class '%s' before it was initialized",
		     __func__, class->name);
		वापस शून्य;
	पूर्ण

	class_dev_iter_init(&iter, class, start, शून्य);
	जबतक ((dev = class_dev_iter_next(&iter))) अणु
		अगर (match(dev, data)) अणु
			get_device(dev);
			अवरोध;
		पूर्ण
	पूर्ण
	class_dev_iter_निकास(&iter);

	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(class_find_device);

पूर्णांक class_पूर्णांकerface_रेजिस्टर(काष्ठा class_पूर्णांकerface *class_पूर्णांकf)
अणु
	काष्ठा class *parent;
	काष्ठा class_dev_iter iter;
	काष्ठा device *dev;

	अगर (!class_पूर्णांकf || !class_पूर्णांकf->class)
		वापस -ENODEV;

	parent = class_get(class_पूर्णांकf->class);
	अगर (!parent)
		वापस -EINVAL;

	mutex_lock(&parent->p->mutex);
	list_add_tail(&class_पूर्णांकf->node, &parent->p->पूर्णांकerfaces);
	अगर (class_पूर्णांकf->add_dev) अणु
		class_dev_iter_init(&iter, parent, शून्य, शून्य);
		जबतक ((dev = class_dev_iter_next(&iter)))
			class_पूर्णांकf->add_dev(dev, class_पूर्णांकf);
		class_dev_iter_निकास(&iter);
	पूर्ण
	mutex_unlock(&parent->p->mutex);

	वापस 0;
पूर्ण

व्योम class_पूर्णांकerface_unरेजिस्टर(काष्ठा class_पूर्णांकerface *class_पूर्णांकf)
अणु
	काष्ठा class *parent = class_पूर्णांकf->class;
	काष्ठा class_dev_iter iter;
	काष्ठा device *dev;

	अगर (!parent)
		वापस;

	mutex_lock(&parent->p->mutex);
	list_del_init(&class_पूर्णांकf->node);
	अगर (class_पूर्णांकf->हटाओ_dev) अणु
		class_dev_iter_init(&iter, parent, शून्य, शून्य);
		जबतक ((dev = class_dev_iter_next(&iter)))
			class_पूर्णांकf->हटाओ_dev(dev, class_पूर्णांकf);
		class_dev_iter_निकास(&iter);
	पूर्ण
	mutex_unlock(&parent->p->mutex);

	class_put(parent);
पूर्ण

sमाप_प्रकार show_class_attr_string(काष्ठा class *class,
			       काष्ठा class_attribute *attr, अक्षर *buf)
अणु
	काष्ठा class_attribute_string *cs;

	cs = container_of(attr, काष्ठा class_attribute_string, attr);
	वापस sysfs_emit(buf, "%s\n", cs->str);
पूर्ण

EXPORT_SYMBOL_GPL(show_class_attr_string);

काष्ठा class_compat अणु
	काष्ठा kobject *kobj;
पूर्ण;

/**
 * class_compat_रेजिस्टर - रेजिस्टर a compatibility class
 * @name: the name of the class
 *
 * Compatibility class are meant as a temporary user-space compatibility
 * workaround when converting a family of class devices to a bus devices.
 */
काष्ठा class_compat *class_compat_रेजिस्टर(स्थिर अक्षर *name)
अणु
	काष्ठा class_compat *cls;

	cls = kदो_स्मृति(माप(काष्ठा class_compat), GFP_KERNEL);
	अगर (!cls)
		वापस शून्य;
	cls->kobj = kobject_create_and_add(name, &class_kset->kobj);
	अगर (!cls->kobj) अणु
		kमुक्त(cls);
		वापस शून्य;
	पूर्ण
	वापस cls;
पूर्ण
EXPORT_SYMBOL_GPL(class_compat_रेजिस्टर);

/**
 * class_compat_unरेजिस्टर - unरेजिस्टर a compatibility class
 * @cls: the class to unरेजिस्टर
 */
व्योम class_compat_unरेजिस्टर(काष्ठा class_compat *cls)
अणु
	kobject_put(cls->kobj);
	kमुक्त(cls);
पूर्ण
EXPORT_SYMBOL_GPL(class_compat_unरेजिस्टर);

/**
 * class_compat_create_link - create a compatibility class device link to
 *			      a bus device
 * @cls: the compatibility class
 * @dev: the target bus device
 * @device_link: an optional device to which a "device" link should be created
 */
पूर्णांक class_compat_create_link(काष्ठा class_compat *cls, काष्ठा device *dev,
			     काष्ठा device *device_link)
अणु
	पूर्णांक error;

	error = sysfs_create_link(cls->kobj, &dev->kobj, dev_name(dev));
	अगर (error)
		वापस error;

	/*
	 * Optionally add a "device" link (typically to the parent), as a
	 * class device would have one and we want to provide as much
	 * backwards compatibility as possible.
	 */
	अगर (device_link) अणु
		error = sysfs_create_link(&dev->kobj, &device_link->kobj,
					  "device");
		अगर (error)
			sysfs_हटाओ_link(cls->kobj, dev_name(dev));
	पूर्ण

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(class_compat_create_link);

/**
 * class_compat_हटाओ_link - हटाओ a compatibility class device link to
 *			      a bus device
 * @cls: the compatibility class
 * @dev: the target bus device
 * @device_link: an optional device to which a "device" link was previously
 * 		 created
 */
व्योम class_compat_हटाओ_link(काष्ठा class_compat *cls, काष्ठा device *dev,
			      काष्ठा device *device_link)
अणु
	अगर (device_link)
		sysfs_हटाओ_link(&dev->kobj, "device");
	sysfs_हटाओ_link(cls->kobj, dev_name(dev));
पूर्ण
EXPORT_SYMBOL_GPL(class_compat_हटाओ_link);

पूर्णांक __init classes_init(व्योम)
अणु
	class_kset = kset_create_and_add("class", शून्य, शून्य);
	अगर (!class_kset)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

EXPORT_SYMBOL_GPL(class_create_file_ns);
EXPORT_SYMBOL_GPL(class_हटाओ_file_ns);
EXPORT_SYMBOL_GPL(class_unरेजिस्टर);
EXPORT_SYMBOL_GPL(class_destroy);

EXPORT_SYMBOL_GPL(class_पूर्णांकerface_रेजिस्टर);
EXPORT_SYMBOL_GPL(class_पूर्णांकerface_unरेजिस्टर);
