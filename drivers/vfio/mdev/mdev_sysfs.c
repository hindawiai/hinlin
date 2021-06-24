<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * File attributes क्रम Mediated devices
 *
 * Copyright (c) 2016, NVIDIA CORPORATION. All rights reserved.
 *     Author: Neo Jia <cjia@nvidia.com>
 *             Kirti Wankhede <kwankhede@nvidia.com>
 */

#समावेश <linux/sysfs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/uuid.h>
#समावेश <linux/mdev.h>

#समावेश "mdev_private.h"

/* Static functions */

अटल sमाप_प्रकार mdev_type_attr_show(काष्ठा kobject *kobj,
				     काष्ठा attribute *__attr, अक्षर *buf)
अणु
	काष्ठा mdev_type_attribute *attr = to_mdev_type_attr(__attr);
	काष्ठा mdev_type *type = to_mdev_type(kobj);
	sमाप_प्रकार ret = -EIO;

	अगर (attr->show)
		ret = attr->show(type, attr, buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार mdev_type_attr_store(काष्ठा kobject *kobj,
				      काष्ठा attribute *__attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा mdev_type_attribute *attr = to_mdev_type_attr(__attr);
	काष्ठा mdev_type *type = to_mdev_type(kobj);
	sमाप_प्रकार ret = -EIO;

	अगर (attr->store)
		ret = attr->store(type, attr, buf, count);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops mdev_type_sysfs_ops = अणु
	.show = mdev_type_attr_show,
	.store = mdev_type_attr_store,
पूर्ण;

अटल sमाप_प्रकार create_store(काष्ठा mdev_type *mtype,
			    काष्ठा mdev_type_attribute *attr, स्थिर अक्षर *buf,
			    माप_प्रकार count)
अणु
	अक्षर *str;
	guid_t uuid;
	पूर्णांक ret;

	अगर ((count < UUID_STRING_LEN) || (count > UUID_STRING_LEN + 1))
		वापस -EINVAL;

	str = kstrndup(buf, count, GFP_KERNEL);
	अगर (!str)
		वापस -ENOMEM;

	ret = guid_parse(str, &uuid);
	kमुक्त(str);
	अगर (ret)
		वापस ret;

	ret = mdev_device_create(mtype, &uuid);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल MDEV_TYPE_ATTR_WO(create);

अटल व्योम mdev_type_release(काष्ठा kobject *kobj)
अणु
	काष्ठा mdev_type *type = to_mdev_type(kobj);

	pr_debug("Releasing group %s\n", kobj->name);
	/* Pairs with the get in add_mdev_supported_type() */
	mdev_put_parent(type->parent);
	kमुक्त(type);
पूर्ण

अटल काष्ठा kobj_type mdev_type_ktype = अणु
	.sysfs_ops = &mdev_type_sysfs_ops,
	.release = mdev_type_release,
पूर्ण;

अटल काष्ठा mdev_type *add_mdev_supported_type(काष्ठा mdev_parent *parent,
						 अचिन्हित पूर्णांक type_group_id)
अणु
	काष्ठा mdev_type *type;
	काष्ठा attribute_group *group =
		parent->ops->supported_type_groups[type_group_id];
	पूर्णांक ret;

	अगर (!group->name) अणु
		pr_err("%s: Type name empty!\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	type = kzalloc(माप(*type), GFP_KERNEL);
	अगर (!type)
		वापस ERR_PTR(-ENOMEM);

	type->kobj.kset = parent->mdev_types_kset;
	type->parent = parent;
	/* Pairs with the put in mdev_type_release() */
	mdev_get_parent(parent);
	type->type_group_id = type_group_id;

	ret = kobject_init_and_add(&type->kobj, &mdev_type_ktype, शून्य,
				   "%s-%s", dev_driver_string(parent->dev),
				   group->name);
	अगर (ret) अणु
		kobject_put(&type->kobj);
		वापस ERR_PTR(ret);
	पूर्ण

	ret = sysfs_create_file(&type->kobj, &mdev_type_attr_create.attr);
	अगर (ret)
		जाओ attr_create_failed;

	type->devices_kobj = kobject_create_and_add("devices", &type->kobj);
	अगर (!type->devices_kobj) अणु
		ret = -ENOMEM;
		जाओ attr_devices_failed;
	पूर्ण

	ret = sysfs_create_files(&type->kobj,
				 (स्थिर काष्ठा attribute **)group->attrs);
	अगर (ret) अणु
		ret = -ENOMEM;
		जाओ attrs_failed;
	पूर्ण
	वापस type;

attrs_failed:
	kobject_put(type->devices_kobj);
attr_devices_failed:
	sysfs_हटाओ_file(&type->kobj, &mdev_type_attr_create.attr);
attr_create_failed:
	kobject_del(&type->kobj);
	kobject_put(&type->kobj);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम हटाओ_mdev_supported_type(काष्ठा mdev_type *type)
अणु
	काष्ठा attribute_group *group =
		type->parent->ops->supported_type_groups[type->type_group_id];

	sysfs_हटाओ_files(&type->kobj,
			   (स्थिर काष्ठा attribute **)group->attrs);
	kobject_put(type->devices_kobj);
	sysfs_हटाओ_file(&type->kobj, &mdev_type_attr_create.attr);
	kobject_del(&type->kobj);
	kobject_put(&type->kobj);
पूर्ण

अटल पूर्णांक add_mdev_supported_type_groups(काष्ठा mdev_parent *parent)
अणु
	पूर्णांक i;

	क्रम (i = 0; parent->ops->supported_type_groups[i]; i++) अणु
		काष्ठा mdev_type *type;

		type = add_mdev_supported_type(parent, i);
		अगर (IS_ERR(type)) अणु
			काष्ठा mdev_type *ltype, *पंचांगp;

			list_क्रम_each_entry_safe(ltype, पंचांगp, &parent->type_list,
						  next) अणु
				list_del(&ltype->next);
				हटाओ_mdev_supported_type(ltype);
			पूर्ण
			वापस PTR_ERR(type);
		पूर्ण
		list_add(&type->next, &parent->type_list);
	पूर्ण
	वापस 0;
पूर्ण

/* mdev sysfs functions */
व्योम parent_हटाओ_sysfs_files(काष्ठा mdev_parent *parent)
अणु
	काष्ठा mdev_type *type, *पंचांगp;

	list_क्रम_each_entry_safe(type, पंचांगp, &parent->type_list, next) अणु
		list_del(&type->next);
		हटाओ_mdev_supported_type(type);
	पूर्ण

	sysfs_हटाओ_groups(&parent->dev->kobj, parent->ops->dev_attr_groups);
	kset_unरेजिस्टर(parent->mdev_types_kset);
पूर्ण

पूर्णांक parent_create_sysfs_files(काष्ठा mdev_parent *parent)
अणु
	पूर्णांक ret;

	parent->mdev_types_kset = kset_create_and_add("mdev_supported_types",
					       शून्य, &parent->dev->kobj);

	अगर (!parent->mdev_types_kset)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&parent->type_list);

	ret = sysfs_create_groups(&parent->dev->kobj,
				  parent->ops->dev_attr_groups);
	अगर (ret)
		जाओ create_err;

	ret = add_mdev_supported_type_groups(parent);
	अगर (ret)
		sysfs_हटाओ_groups(&parent->dev->kobj,
				    parent->ops->dev_attr_groups);
	अन्यथा
		वापस ret;

create_err:
	kset_unरेजिस्टर(parent->mdev_types_kset);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार हटाओ_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा mdev_device *mdev = to_mdev_device(dev);
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 0, &val) < 0)
		वापस -EINVAL;

	अगर (val && device_हटाओ_file_self(dev, attr)) अणु
		पूर्णांक ret;

		ret = mdev_device_हटाओ(mdev);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस count;
पूर्ण

अटल DEVICE_ATTR_WO(हटाओ);

अटल स्थिर काष्ठा attribute *mdev_device_attrs[] = अणु
	&dev_attr_हटाओ.attr,
	शून्य,
पूर्ण;

पूर्णांक mdev_create_sysfs_files(काष्ठा mdev_device *mdev)
अणु
	काष्ठा mdev_type *type = mdev->type;
	काष्ठा kobject *kobj = &mdev->dev.kobj;
	पूर्णांक ret;

	ret = sysfs_create_link(type->devices_kobj, kobj, dev_name(&mdev->dev));
	अगर (ret)
		वापस ret;

	ret = sysfs_create_link(kobj, &type->kobj, "mdev_type");
	अगर (ret)
		जाओ type_link_failed;

	ret = sysfs_create_files(kobj, mdev_device_attrs);
	अगर (ret)
		जाओ create_files_failed;

	वापस ret;

create_files_failed:
	sysfs_हटाओ_link(kobj, "mdev_type");
type_link_failed:
	sysfs_हटाओ_link(mdev->type->devices_kobj, dev_name(&mdev->dev));
	वापस ret;
पूर्ण

व्योम mdev_हटाओ_sysfs_files(काष्ठा mdev_device *mdev)
अणु
	काष्ठा kobject *kobj = &mdev->dev.kobj;

	sysfs_हटाओ_files(kobj, mdev_device_attrs);
	sysfs_हटाओ_link(kobj, "mdev_type");
	sysfs_हटाओ_link(mdev->type->devices_kobj, dev_name(&mdev->dev));
पूर्ण
