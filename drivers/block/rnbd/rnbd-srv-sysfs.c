<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RDMA Network Block Driver
 *
 * Copyright (c) 2014 - 2018 ProfitBricks GmbH. All rights reserved.
 * Copyright (c) 2018 - 2019 1&1 IONOS Cloud GmbH. All rights reserved.
 * Copyright (c) 2019 - 2020 1&1 IONOS SE. All rights reserved.
 */
#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) KBUILD_MODNAME " L" __stringअगरy(__LINE__) ": " fmt

#समावेश <uapi/linux/सीमा.स>
#समावेश <linux/kobject.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/genhd.h>
#समावेश <linux/list.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>

#समावेश "rnbd-srv.h"

अटल काष्ठा device *rnbd_dev;
अटल काष्ठा class *rnbd_dev_class;
अटल काष्ठा kobject *rnbd_devs_kobj;

अटल व्योम rnbd_srv_dev_release(काष्ठा kobject *kobj)
अणु
	काष्ठा rnbd_srv_dev *dev;

	dev = container_of(kobj, काष्ठा rnbd_srv_dev, dev_kobj);

	kमुक्त(dev);
पूर्ण

अटल काष्ठा kobj_type dev_ktype = अणु
	.sysfs_ops = &kobj_sysfs_ops,
	.release = rnbd_srv_dev_release
पूर्ण;

पूर्णांक rnbd_srv_create_dev_sysfs(काष्ठा rnbd_srv_dev *dev,
			       काष्ठा block_device *bdev,
			       स्थिर अक्षर *dev_name)
अणु
	काष्ठा kobject *bdev_kobj;
	पूर्णांक ret;

	ret = kobject_init_and_add(&dev->dev_kobj, &dev_ktype,
				   rnbd_devs_kobj, dev_name);
	अगर (ret) अणु
		kobject_put(&dev->dev_kobj);
		वापस ret;
	पूर्ण

	dev->dev_sessions_kobj = kobject_create_and_add("sessions",
							&dev->dev_kobj);
	अगर (!dev->dev_sessions_kobj) अणु
		ret = -ENOMEM;
		जाओ मुक्त_dev_kobj;
	पूर्ण

	bdev_kobj = &disk_to_dev(bdev->bd_disk)->kobj;
	ret = sysfs_create_link(&dev->dev_kobj, bdev_kobj, "block_dev");
	अगर (ret)
		जाओ put_sess_kobj;

	वापस 0;

put_sess_kobj:
	kobject_put(dev->dev_sessions_kobj);
मुक्त_dev_kobj:
	kobject_del(&dev->dev_kobj);
	kobject_put(&dev->dev_kobj);
	वापस ret;
पूर्ण

व्योम rnbd_srv_destroy_dev_sysfs(काष्ठा rnbd_srv_dev *dev)
अणु
	sysfs_हटाओ_link(&dev->dev_kobj, "block_dev");
	kobject_del(dev->dev_sessions_kobj);
	kobject_put(dev->dev_sessions_kobj);
	kobject_del(&dev->dev_kobj);
	kobject_put(&dev->dev_kobj);
पूर्ण

अटल sमाप_प्रकार पढ़ो_only_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			      अक्षर *page)
अणु
	काष्ठा rnbd_srv_sess_dev *sess_dev;

	sess_dev = container_of(kobj, काष्ठा rnbd_srv_sess_dev, kobj);

	वापस scnम_लिखो(page, PAGE_SIZE, "%d\n",
			 !(sess_dev->खोलो_flags & FMODE_WRITE));
पूर्ण

अटल काष्ठा kobj_attribute rnbd_srv_dev_session_ro_attr =
	__ATTR_RO(पढ़ो_only);

अटल sमाप_प्रकार access_mode_show(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr,
				अक्षर *page)
अणु
	काष्ठा rnbd_srv_sess_dev *sess_dev;

	sess_dev = container_of(kobj, काष्ठा rnbd_srv_sess_dev, kobj);

	वापस scnम_लिखो(page, PAGE_SIZE, "%s\n",
			 rnbd_access_mode_str(sess_dev->access_mode));
पूर्ण

अटल काष्ठा kobj_attribute rnbd_srv_dev_session_access_mode_attr =
	__ATTR_RO(access_mode);

अटल sमाप_प्रकार mapping_path_show(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	काष्ठा rnbd_srv_sess_dev *sess_dev;

	sess_dev = container_of(kobj, काष्ठा rnbd_srv_sess_dev, kobj);

	वापस scnम_लिखो(page, PAGE_SIZE, "%s\n", sess_dev->pathname);
पूर्ण

अटल काष्ठा kobj_attribute rnbd_srv_dev_session_mapping_path_attr =
	__ATTR_RO(mapping_path);

अटल sमाप_प्रकार rnbd_srv_dev_session_क्रमce_बंद_show(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	वापस scnम_लिखो(page, PAGE_SIZE, "Usage: echo 1 > %s\n",
			 attr->attr.name);
पूर्ण

अटल sमाप_प्रकार rnbd_srv_dev_session_क्रमce_बंद_store(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा rnbd_srv_sess_dev *sess_dev;

	sess_dev = container_of(kobj, काष्ठा rnbd_srv_sess_dev, kobj);

	अगर (!sysfs_streq(buf, "1")) अणु
		rnbd_srv_err(sess_dev, "%s: invalid value: '%s'\n",
			      attr->attr.name, buf);
		वापस -EINVAL;
	पूर्ण

	rnbd_srv_info(sess_dev, "force close requested\n");
	rnbd_srv_sess_dev_क्रमce_बंद(sess_dev, attr);

	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute rnbd_srv_dev_session_क्रमce_बंद_attr =
	__ATTR(क्रमce_बंद, 0644,
	       rnbd_srv_dev_session_क्रमce_बंद_show,
	       rnbd_srv_dev_session_क्रमce_बंद_store);

अटल काष्ठा attribute *rnbd_srv_शेष_dev_sessions_attrs[] = अणु
	&rnbd_srv_dev_session_access_mode_attr.attr,
	&rnbd_srv_dev_session_ro_attr.attr,
	&rnbd_srv_dev_session_mapping_path_attr.attr,
	&rnbd_srv_dev_session_क्रमce_बंद_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group rnbd_srv_शेष_dev_session_attr_group = अणु
	.attrs = rnbd_srv_शेष_dev_sessions_attrs,
पूर्ण;

व्योम rnbd_srv_destroy_dev_session_sysfs(काष्ठा rnbd_srv_sess_dev *sess_dev)
अणु
	sysfs_हटाओ_group(&sess_dev->kobj,
			   &rnbd_srv_शेष_dev_session_attr_group);

	kobject_del(&sess_dev->kobj);
	kobject_put(&sess_dev->kobj);
पूर्ण

अटल व्योम rnbd_srv_sess_dev_release(काष्ठा kobject *kobj)
अणु
	काष्ठा rnbd_srv_sess_dev *sess_dev;

	sess_dev = container_of(kobj, काष्ठा rnbd_srv_sess_dev, kobj);
	rnbd_destroy_sess_dev(sess_dev, sess_dev->keep_id);
पूर्ण

अटल काष्ठा kobj_type rnbd_srv_sess_dev_ktype = अणु
	.sysfs_ops	= &kobj_sysfs_ops,
	.release	= rnbd_srv_sess_dev_release,
पूर्ण;

पूर्णांक rnbd_srv_create_dev_session_sysfs(काष्ठा rnbd_srv_sess_dev *sess_dev)
अणु
	पूर्णांक ret;

	ret = kobject_init_and_add(&sess_dev->kobj, &rnbd_srv_sess_dev_ktype,
				   sess_dev->dev->dev_sessions_kobj, "%s",
				   sess_dev->sess->sessname);
	अगर (ret) अणु
		kobject_put(&sess_dev->kobj);
		वापस ret;
	पूर्ण

	ret = sysfs_create_group(&sess_dev->kobj,
				 &rnbd_srv_शेष_dev_session_attr_group);
	अगर (ret) अणु
		kobject_del(&sess_dev->kobj);
		kobject_put(&sess_dev->kobj);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक rnbd_srv_create_sysfs_files(व्योम)
अणु
	पूर्णांक err;

	rnbd_dev_class = class_create(THIS_MODULE, "rnbd-server");
	अगर (IS_ERR(rnbd_dev_class))
		वापस PTR_ERR(rnbd_dev_class);

	rnbd_dev = device_create(rnbd_dev_class, शून्य,
				  MKDEV(0, 0), शून्य, "ctl");
	अगर (IS_ERR(rnbd_dev)) अणु
		err = PTR_ERR(rnbd_dev);
		जाओ cls_destroy;
	पूर्ण
	rnbd_devs_kobj = kobject_create_and_add("devices", &rnbd_dev->kobj);
	अगर (!rnbd_devs_kobj) अणु
		err = -ENOMEM;
		जाओ dev_destroy;
	पूर्ण

	वापस 0;

dev_destroy:
	device_destroy(rnbd_dev_class, MKDEV(0, 0));
cls_destroy:
	class_destroy(rnbd_dev_class);

	वापस err;
पूर्ण

व्योम rnbd_srv_destroy_sysfs_files(व्योम)
अणु
	kobject_del(rnbd_devs_kobj);
	kobject_put(rnbd_devs_kobj);
	device_destroy(rnbd_dev_class, MKDEV(0, 0));
	class_destroy(rnbd_dev_class);
पूर्ण
