<शैली गुरु>
/*
 * Copyright (C) 2008 Red Hat, Inc. All rights reserved.
 *
 * This file is released under the GPL.
 */

#समावेश <linux/sysfs.h>
#समावेश <linux/dm-ioctl.h>
#समावेश "dm-core.h"
#समावेश "dm-rq.h"

काष्ठा dm_sysfs_attr अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा mapped_device *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा mapped_device *, स्थिर अक्षर *, माप_प्रकार count);
पूर्ण;

#घोषणा DM_ATTR_RO(_name) \
काष्ठा dm_sysfs_attr dm_attr_##_name = \
	__ATTR(_name, S_IRUGO, dm_attr_##_name##_show, शून्य)

अटल sमाप_प्रकार dm_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			    अक्षर *page)
अणु
	काष्ठा dm_sysfs_attr *dm_attr;
	काष्ठा mapped_device *md;
	sमाप_प्रकार ret;

	dm_attr = container_of(attr, काष्ठा dm_sysfs_attr, attr);
	अगर (!dm_attr->show)
		वापस -EIO;

	md = dm_get_from_kobject(kobj);
	अगर (!md)
		वापस -EINVAL;

	ret = dm_attr->show(md, page);
	dm_put(md);

	वापस ret;
पूर्ण

#घोषणा DM_ATTR_RW(_name) \
काष्ठा dm_sysfs_attr dm_attr_##_name = \
	__ATTR(_name, S_IRUGO | S_IWUSR, dm_attr_##_name##_show, dm_attr_##_name##_store)

अटल sमाप_प्रकार dm_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			     स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा dm_sysfs_attr *dm_attr;
	काष्ठा mapped_device *md;
	sमाप_प्रकार ret;

	dm_attr = container_of(attr, काष्ठा dm_sysfs_attr, attr);
	अगर (!dm_attr->store)
		वापस -EIO;

	md = dm_get_from_kobject(kobj);
	अगर (!md)
		वापस -EINVAL;

	ret = dm_attr->store(md, page, count);
	dm_put(md);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार dm_attr_name_show(काष्ठा mapped_device *md, अक्षर *buf)
अणु
	अगर (dm_copy_name_and_uuid(md, buf, शून्य))
		वापस -EIO;

	म_जोड़ो(buf, "\n");
	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार dm_attr_uuid_show(काष्ठा mapped_device *md, अक्षर *buf)
अणु
	अगर (dm_copy_name_and_uuid(md, शून्य, buf))
		वापस -EIO;

	म_जोड़ो(buf, "\n");
	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार dm_attr_suspended_show(काष्ठा mapped_device *md, अक्षर *buf)
अणु
	प्र_लिखो(buf, "%d\n", dm_suspended_md(md));

	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार dm_attr_use_blk_mq_show(काष्ठा mapped_device *md, अक्षर *buf)
अणु
	/* Purely क्रम userspace compatibility */
	प्र_लिखो(buf, "%d\n", true);

	वापस म_माप(buf);
पूर्ण

अटल DM_ATTR_RO(name);
अटल DM_ATTR_RO(uuid);
अटल DM_ATTR_RO(suspended);
अटल DM_ATTR_RO(use_blk_mq);
अटल DM_ATTR_RW(rq_based_seq_io_merge_deadline);

अटल काष्ठा attribute *dm_attrs[] = अणु
	&dm_attr_name.attr,
	&dm_attr_uuid.attr,
	&dm_attr_suspended.attr,
	&dm_attr_use_blk_mq.attr,
	&dm_attr_rq_based_seq_io_merge_deadline.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा sysfs_ops dm_sysfs_ops = अणु
	.show	= dm_attr_show,
	.store	= dm_attr_store,
पूर्ण;

अटल काष्ठा kobj_type dm_ktype = अणु
	.sysfs_ops	= &dm_sysfs_ops,
	.शेष_attrs	= dm_attrs,
	.release	= dm_kobject_release,
पूर्ण;

/*
 * Initialize kobj
 * because nobody using md yet, no need to call explicit dm_get/put
 */
पूर्णांक dm_sysfs_init(काष्ठा mapped_device *md)
अणु
	वापस kobject_init_and_add(dm_kobject(md), &dm_ktype,
				    &disk_to_dev(dm_disk(md))->kobj,
				    "%s", "dm");
पूर्ण

/*
 * Remove kobj, called after all references हटाओd
 */
व्योम dm_sysfs_निकास(काष्ठा mapped_device *md)
अणु
	काष्ठा kobject *kobj = dm_kobject(md);
	kobject_put(kobj);
	रुको_क्रम_completion(dm_get_completion_from_kobject(kobj));
पूर्ण
