<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * The Industrial I/O core, software trigger functions
 *
 * Copyright (c) 2015 Intel Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kmod.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>

#समावेश <linux/iio/sw_trigger.h>
#समावेश <linux/iio/configfs.h>
#समावेश <linux/configfs.h>

अटल काष्ठा config_group *iio_triggers_group;
अटल स्थिर काष्ठा config_item_type iio_trigger_type_group_type;

अटल स्थिर काष्ठा config_item_type iio_triggers_group_type = अणु
	.ct_owner = THIS_MODULE,
पूर्ण;

अटल LIST_HEAD(iio_trigger_types_list);
अटल DEFINE_MUTEX(iio_trigger_types_lock);

अटल
काष्ठा iio_sw_trigger_type *__iio_find_sw_trigger_type(स्थिर अक्षर *name,
						       अचिन्हित len)
अणु
	काष्ठा iio_sw_trigger_type *t = शून्य, *iter;

	list_क्रम_each_entry(iter, &iio_trigger_types_list, list)
		अगर (!म_भेद(iter->name, name)) अणु
			t = iter;
			अवरोध;
		पूर्ण

	वापस t;
पूर्ण

पूर्णांक iio_रेजिस्टर_sw_trigger_type(काष्ठा iio_sw_trigger_type *t)
अणु
	काष्ठा iio_sw_trigger_type *iter;
	पूर्णांक ret = 0;

	mutex_lock(&iio_trigger_types_lock);
	iter = __iio_find_sw_trigger_type(t->name, म_माप(t->name));
	अगर (iter)
		ret = -EBUSY;
	अन्यथा
		list_add_tail(&t->list, &iio_trigger_types_list);
	mutex_unlock(&iio_trigger_types_lock);

	अगर (ret)
		वापस ret;

	t->group = configfs_रेजिस्टर_शेष_group(iio_triggers_group, t->name,
						&iio_trigger_type_group_type);
	अगर (IS_ERR(t->group))
		ret = PTR_ERR(t->group);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(iio_रेजिस्टर_sw_trigger_type);

व्योम iio_unरेजिस्टर_sw_trigger_type(काष्ठा iio_sw_trigger_type *t)
अणु
	काष्ठा iio_sw_trigger_type *iter;

	mutex_lock(&iio_trigger_types_lock);
	iter = __iio_find_sw_trigger_type(t->name, म_माप(t->name));
	अगर (iter)
		list_del(&t->list);
	mutex_unlock(&iio_trigger_types_lock);

	configfs_unरेजिस्टर_शेष_group(t->group);
पूर्ण
EXPORT_SYMBOL(iio_unरेजिस्टर_sw_trigger_type);

अटल
काष्ठा iio_sw_trigger_type *iio_get_sw_trigger_type(स्थिर अक्षर *name)
अणु
	काष्ठा iio_sw_trigger_type *t;

	mutex_lock(&iio_trigger_types_lock);
	t = __iio_find_sw_trigger_type(name, म_माप(name));
	अगर (t && !try_module_get(t->owner))
		t = शून्य;
	mutex_unlock(&iio_trigger_types_lock);

	वापस t;
पूर्ण

काष्ठा iio_sw_trigger *iio_sw_trigger_create(स्थिर अक्षर *type, स्थिर अक्षर *name)
अणु
	काष्ठा iio_sw_trigger *t;
	काष्ठा iio_sw_trigger_type *tt;

	tt = iio_get_sw_trigger_type(type);
	अगर (!tt) अणु
		pr_err("Invalid trigger type: %s\n", type);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	t = tt->ops->probe(name);
	अगर (IS_ERR(t))
		जाओ out_module_put;

	t->trigger_type = tt;

	वापस t;
out_module_put:
	module_put(tt->owner);
	वापस t;
पूर्ण
EXPORT_SYMBOL(iio_sw_trigger_create);

व्योम iio_sw_trigger_destroy(काष्ठा iio_sw_trigger *t)
अणु
	काष्ठा iio_sw_trigger_type *tt = t->trigger_type;

	tt->ops->हटाओ(t);
	module_put(tt->owner);
पूर्ण
EXPORT_SYMBOL(iio_sw_trigger_destroy);

अटल काष्ठा config_group *trigger_make_group(काष्ठा config_group *group,
					       स्थिर अक्षर *name)
अणु
	काष्ठा iio_sw_trigger *t;

	t = iio_sw_trigger_create(group->cg_item.ci_name, name);
	अगर (IS_ERR(t))
		वापस ERR_CAST(t);

	config_item_set_name(&t->group.cg_item, "%s", name);

	वापस &t->group;
पूर्ण

अटल व्योम trigger_drop_group(काष्ठा config_group *group,
			       काष्ठा config_item *item)
अणु
	काष्ठा iio_sw_trigger *t = to_iio_sw_trigger(item);

	iio_sw_trigger_destroy(t);
	config_item_put(item);
पूर्ण

अटल काष्ठा configfs_group_operations trigger_ops = अणु
	.make_group	= &trigger_make_group,
	.drop_item	= &trigger_drop_group,
पूर्ण;

अटल स्थिर काष्ठा config_item_type iio_trigger_type_group_type = अणु
	.ct_group_ops = &trigger_ops,
	.ct_owner       = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init iio_sw_trigger_init(व्योम)
अणु
	iio_triggers_group =
		configfs_रेजिस्टर_शेष_group(&iio_configfs_subsys.su_group,
						"triggers",
						&iio_triggers_group_type);
	वापस PTR_ERR_OR_ZERO(iio_triggers_group);
पूर्ण
module_init(iio_sw_trigger_init);

अटल व्योम __निकास iio_sw_trigger_निकास(व्योम)
अणु
	configfs_unरेजिस्टर_शेष_group(iio_triggers_group);
पूर्ण
module_निकास(iio_sw_trigger_निकास);

MODULE_AUTHOR("Daniel Baluta <daniel.baluta@intel.com>");
MODULE_DESCRIPTION("Industrial I/O software triggers support");
MODULE_LICENSE("GPL v2");
