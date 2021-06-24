<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sys.c
 *
 * OCFS2 cluster sysfs पूर्णांकerface
 *
 * Copyright (C) 2005 Oracle.  All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/kobject.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/fs.h>

#समावेश "ocfs2_nodemanager.h"
#समावेश "masklog.h"
#समावेश "sys.h"


अटल sमाप_प्रकार version_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			    अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", O2NM_API_VERSION);
पूर्ण
अटल काष्ठा kobj_attribute attr_version =
	__ATTR(पूर्णांकerface_revision, S_IRUGO, version_show, शून्य);

अटल काष्ठा attribute *o2cb_attrs[] = अणु
	&attr_version.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group o2cb_attr_group = अणु
	.attrs = o2cb_attrs,
पूर्ण;

अटल काष्ठा kset *o2cb_kset;

व्योम o2cb_sys_shutकरोwn(व्योम)
अणु
	mlog_sys_shutकरोwn();
	kset_unरेजिस्टर(o2cb_kset);
पूर्ण

पूर्णांक o2cb_sys_init(व्योम)
अणु
	पूर्णांक ret;

	o2cb_kset = kset_create_and_add("o2cb", शून्य, fs_kobj);
	अगर (!o2cb_kset)
		वापस -ENOMEM;

	ret = sysfs_create_group(&o2cb_kset->kobj, &o2cb_attr_group);
	अगर (ret)
		जाओ error;

	ret = mlog_sys_init(o2cb_kset);
	अगर (ret)
		जाओ error;
	वापस 0;
error:
	kset_unरेजिस्टर(o2cb_kset);
	वापस ret;
पूर्ण
