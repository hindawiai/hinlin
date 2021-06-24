<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * The Industrial I/O core, software IIO devices functions
 *
 * Copyright (c) 2016 Intel Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kmod.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>

#समावेश <linux/iio/sw_device.h>
#समावेश <linux/iio/configfs.h>
#समावेश <linux/configfs.h>

अटल काष्ठा config_group *iio_devices_group;
अटल स्थिर काष्ठा config_item_type iio_device_type_group_type;

अटल स्थिर काष्ठा config_item_type iio_devices_group_type = अणु
	.ct_owner = THIS_MODULE,
पूर्ण;

अटल LIST_HEAD(iio_device_types_list);
अटल DEFINE_MUTEX(iio_device_types_lock);

अटल
काष्ठा iio_sw_device_type *__iio_find_sw_device_type(स्थिर अक्षर *name,
						     अचिन्हित len)
अणु
	काष्ठा iio_sw_device_type *d = शून्य, *iter;

	list_क्रम_each_entry(iter, &iio_device_types_list, list)
		अगर (!म_भेद(iter->name, name)) अणु
			d = iter;
			अवरोध;
		पूर्ण

	वापस d;
पूर्ण

पूर्णांक iio_रेजिस्टर_sw_device_type(काष्ठा iio_sw_device_type *d)
अणु
	काष्ठा iio_sw_device_type *iter;
	पूर्णांक ret = 0;

	mutex_lock(&iio_device_types_lock);
	iter = __iio_find_sw_device_type(d->name, म_माप(d->name));
	अगर (iter)
		ret = -EBUSY;
	अन्यथा
		list_add_tail(&d->list, &iio_device_types_list);
	mutex_unlock(&iio_device_types_lock);

	अगर (ret)
		वापस ret;

	d->group = configfs_रेजिस्टर_शेष_group(iio_devices_group, d->name,
						&iio_device_type_group_type);
	अगर (IS_ERR(d->group))
		ret = PTR_ERR(d->group);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(iio_रेजिस्टर_sw_device_type);

व्योम iio_unरेजिस्टर_sw_device_type(काष्ठा iio_sw_device_type *dt)
अणु
	काष्ठा iio_sw_device_type *iter;

	mutex_lock(&iio_device_types_lock);
	iter = __iio_find_sw_device_type(dt->name, म_माप(dt->name));
	अगर (iter)
		list_del(&dt->list);
	mutex_unlock(&iio_device_types_lock);

	configfs_unरेजिस्टर_शेष_group(dt->group);
पूर्ण
EXPORT_SYMBOL(iio_unरेजिस्टर_sw_device_type);

अटल
काष्ठा iio_sw_device_type *iio_get_sw_device_type(स्थिर अक्षर *name)
अणु
	काष्ठा iio_sw_device_type *dt;

	mutex_lock(&iio_device_types_lock);
	dt = __iio_find_sw_device_type(name, म_माप(name));
	अगर (dt && !try_module_get(dt->owner))
		dt = शून्य;
	mutex_unlock(&iio_device_types_lock);

	वापस dt;
पूर्ण

काष्ठा iio_sw_device *iio_sw_device_create(स्थिर अक्षर *type, स्थिर अक्षर *name)
अणु
	काष्ठा iio_sw_device *d;
	काष्ठा iio_sw_device_type *dt;

	dt = iio_get_sw_device_type(type);
	अगर (!dt) अणु
		pr_err("Invalid device type: %s\n", type);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	d = dt->ops->probe(name);
	अगर (IS_ERR(d))
		जाओ out_module_put;

	d->device_type = dt;

	वापस d;
out_module_put:
	module_put(dt->owner);
	वापस d;
पूर्ण
EXPORT_SYMBOL(iio_sw_device_create);

व्योम iio_sw_device_destroy(काष्ठा iio_sw_device *d)
अणु
	काष्ठा iio_sw_device_type *dt = d->device_type;

	dt->ops->हटाओ(d);
	module_put(dt->owner);
पूर्ण
EXPORT_SYMBOL(iio_sw_device_destroy);

अटल काष्ठा config_group *device_make_group(काष्ठा config_group *group,
					      स्थिर अक्षर *name)
अणु
	काष्ठा iio_sw_device *d;

	d = iio_sw_device_create(group->cg_item.ci_name, name);
	अगर (IS_ERR(d))
		वापस ERR_CAST(d);

	config_item_set_name(&d->group.cg_item, "%s", name);

	वापस &d->group;
पूर्ण

अटल व्योम device_drop_group(काष्ठा config_group *group,
			      काष्ठा config_item *item)
अणु
	काष्ठा iio_sw_device *d = to_iio_sw_device(item);

	iio_sw_device_destroy(d);
	config_item_put(item);
पूर्ण

अटल काष्ठा configfs_group_operations device_ops = अणु
	.make_group	= &device_make_group,
	.drop_item	= &device_drop_group,
पूर्ण;

अटल स्थिर काष्ठा config_item_type iio_device_type_group_type = अणु
	.ct_group_ops = &device_ops,
	.ct_owner       = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init iio_sw_device_init(व्योम)
अणु
	iio_devices_group =
		configfs_रेजिस्टर_शेष_group(&iio_configfs_subsys.su_group,
						"devices",
						&iio_devices_group_type);
	वापस PTR_ERR_OR_ZERO(iio_devices_group);
पूर्ण
module_init(iio_sw_device_init);

अटल व्योम __निकास iio_sw_device_निकास(व्योम)
अणु
	configfs_unरेजिस्टर_शेष_group(iio_devices_group);
पूर्ण
module_निकास(iio_sw_device_निकास);

MODULE_AUTHOR("Daniel Baluta <daniel.baluta@intel.com>");
MODULE_DESCRIPTION("Industrial I/O software devices support");
MODULE_LICENSE("GPL v2");
