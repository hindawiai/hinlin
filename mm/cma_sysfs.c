<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * CMA SysFS Interface
 *
 * Copyright (c) 2021 Minchan Kim <minchan@kernel.org>
 */

#समावेश <linux/cma.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश "cma.h"

#घोषणा CMA_ATTR_RO(_name) \
	अटल काष्ठा kobj_attribute _name##_attr = __ATTR_RO(_name)

व्योम cma_sysfs_account_success_pages(काष्ठा cma *cma, अचिन्हित दीर्घ nr_pages)
अणु
	atomic64_add(nr_pages, &cma->nr_pages_succeeded);
पूर्ण

व्योम cma_sysfs_account_fail_pages(काष्ठा cma *cma, अचिन्हित दीर्घ nr_pages)
अणु
	atomic64_add(nr_pages, &cma->nr_pages_failed);
पूर्ण

अटल अंतरभूत काष्ठा cma *cma_from_kobj(काष्ठा kobject *kobj)
अणु
	वापस container_of(kobj, काष्ठा cma_kobject, kobj)->cma;
पूर्ण

अटल sमाप_प्रकार alloc_pages_success_show(काष्ठा kobject *kobj,
					काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cma *cma = cma_from_kobj(kobj);

	वापस sysfs_emit(buf, "%llu\n",
			  atomic64_पढ़ो(&cma->nr_pages_succeeded));
पूर्ण
CMA_ATTR_RO(alloc_pages_success);

अटल sमाप_प्रकार alloc_pages_fail_show(काष्ठा kobject *kobj,
				     काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cma *cma = cma_from_kobj(kobj);

	वापस sysfs_emit(buf, "%llu\n", atomic64_पढ़ो(&cma->nr_pages_failed));
पूर्ण
CMA_ATTR_RO(alloc_pages_fail);

अटल व्योम cma_kobj_release(काष्ठा kobject *kobj)
अणु
	काष्ठा cma *cma = cma_from_kobj(kobj);
	काष्ठा cma_kobject *cma_kobj = cma->cma_kobj;

	kमुक्त(cma_kobj);
	cma->cma_kobj = शून्य;
पूर्ण

अटल काष्ठा attribute *cma_attrs[] = अणु
	&alloc_pages_success_attr.attr,
	&alloc_pages_fail_attr.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(cma);

अटल काष्ठा kobj_type cma_ktype = अणु
	.release = cma_kobj_release,
	.sysfs_ops = &kobj_sysfs_ops,
	.शेष_groups = cma_groups,
पूर्ण;

अटल पूर्णांक __init cma_sysfs_init(व्योम)
अणु
	काष्ठा kobject *cma_kobj_root;
	काष्ठा cma_kobject *cma_kobj;
	काष्ठा cma *cma;
	पूर्णांक i, err;

	cma_kobj_root = kobject_create_and_add("cma", mm_kobj);
	अगर (!cma_kobj_root)
		वापस -ENOMEM;

	क्रम (i = 0; i < cma_area_count; i++) अणु
		cma_kobj = kzalloc(माप(*cma_kobj), GFP_KERNEL);
		अगर (!cma_kobj) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		cma = &cma_areas[i];
		cma->cma_kobj = cma_kobj;
		cma_kobj->cma = cma;
		err = kobject_init_and_add(&cma_kobj->kobj, &cma_ktype,
					   cma_kobj_root, "%s", cma->name);
		अगर (err) अणु
			kobject_put(&cma_kobj->kobj);
			जाओ out;
		पूर्ण
	पूर्ण

	वापस 0;
out:
	जबतक (--i >= 0) अणु
		cma = &cma_areas[i];
		kobject_put(&cma->cma_kobj->kobj);
	पूर्ण
	kobject_put(cma_kobj_root);

	वापस err;
पूर्ण
subsys_initcall(cma_sysfs_init);
