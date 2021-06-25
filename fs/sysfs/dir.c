<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/sysfs/dir.c - sysfs core and dir operation implementation
 *
 * Copyright (c) 2001-3 Patrick Mochel
 * Copyright (c) 2007 SUSE Linux Products GmbH
 * Copyright (c) 2007 Tejun Heo <teheo@suse.de>
 *
 * Please see Documentation/fileप्रणालीs/sysfs.rst क्रम more inक्रमmation.
 */

#घोषणा pr_fmt(fmt)	"sysfs: " fmt

#समावेश <linux/fs.h>
#समावेश <linux/kobject.h>
#समावेश <linux/slab.h>
#समावेश "sysfs.h"

DEFINE_SPINLOCK(sysfs_symlink_target_lock);

व्योम sysfs_warn_dup(काष्ठा kernfs_node *parent, स्थिर अक्षर *name)
अणु
	अक्षर *buf;

	buf = kzalloc(PATH_MAX, GFP_KERNEL);
	अगर (buf)
		kernfs_path(parent, buf, PATH_MAX);

	pr_warn("cannot create duplicate filename '%s/%s'\n", buf, name);
	dump_stack();

	kमुक्त(buf);
पूर्ण

/**
 * sysfs_create_dir_ns - create a directory क्रम an object with a namespace tag
 * @kobj: object we're creating directory क्रम
 * @ns: the namespace tag to use
 */
पूर्णांक sysfs_create_dir_ns(काष्ठा kobject *kobj, स्थिर व्योम *ns)
अणु
	काष्ठा kernfs_node *parent, *kn;
	kuid_t uid;
	kgid_t gid;

	अगर (WARN_ON(!kobj))
		वापस -EINVAL;

	अगर (kobj->parent)
		parent = kobj->parent->sd;
	अन्यथा
		parent = sysfs_root_kn;

	अगर (!parent)
		वापस -ENOENT;

	kobject_get_ownership(kobj, &uid, &gid);

	kn = kernfs_create_dir_ns(parent, kobject_name(kobj),
				  S_IRWXU | S_IRUGO | S_IXUGO, uid, gid,
				  kobj, ns);
	अगर (IS_ERR(kn)) अणु
		अगर (PTR_ERR(kn) == -EEXIST)
			sysfs_warn_dup(parent, kobject_name(kobj));
		वापस PTR_ERR(kn);
	पूर्ण

	kobj->sd = kn;
	वापस 0;
पूर्ण

/**
 *	sysfs_हटाओ_dir - हटाओ an object's directory.
 *	@kobj:	object.
 *
 *	The only thing special about this is that we हटाओ any files in
 *	the directory beक्रमe we हटाओ the directory, and we've अंतरभूतd
 *	what used to be sysfs_सूची_हटाओ() below, instead of calling separately.
 */
व्योम sysfs_हटाओ_dir(काष्ठा kobject *kobj)
अणु
	काष्ठा kernfs_node *kn = kobj->sd;

	/*
	 * In general, kboject owner is responsible क्रम ensuring removal
	 * करोesn't race with other operations and sysfs doesn't provide any
	 * protection; however, when @kobj is used as a symlink target, the
	 * symlinking entity usually करोesn't own @kobj and thus has no
	 * control over removal.  @kobj->sd may be हटाओd anyसमय
	 * and symlink code may end up dereferencing an alपढ़ोy मुक्तd node.
	 *
	 * sysfs_symlink_target_lock synchronizes @kobj->sd
	 * disassociation against symlink operations so that symlink code
	 * can safely dereference @kobj->sd.
	 */
	spin_lock(&sysfs_symlink_target_lock);
	kobj->sd = शून्य;
	spin_unlock(&sysfs_symlink_target_lock);

	अगर (kn) अणु
		WARN_ON_ONCE(kernfs_type(kn) != KERNFS_सूची);
		kernfs_हटाओ(kn);
	पूर्ण
पूर्ण

पूर्णांक sysfs_नाम_dir_ns(काष्ठा kobject *kobj, स्थिर अक्षर *new_name,
			स्थिर व्योम *new_ns)
अणु
	काष्ठा kernfs_node *parent;
	पूर्णांक ret;

	parent = kernfs_get_parent(kobj->sd);
	ret = kernfs_नाम_ns(kobj->sd, parent, new_name, new_ns);
	kernfs_put(parent);
	वापस ret;
पूर्ण

पूर्णांक sysfs_move_dir_ns(काष्ठा kobject *kobj, काष्ठा kobject *new_parent_kobj,
		      स्थिर व्योम *new_ns)
अणु
	काष्ठा kernfs_node *kn = kobj->sd;
	काष्ठा kernfs_node *new_parent;

	new_parent = new_parent_kobj && new_parent_kobj->sd ?
		new_parent_kobj->sd : sysfs_root_kn;

	वापस kernfs_नाम_ns(kn, new_parent, kn->name, new_ns);
पूर्ण

/**
 * sysfs_create_mount_poपूर्णांक - create an always empty directory
 * @parent_kobj:  kobject that will contain this always empty directory
 * @name: The name of the always empty directory to add
 */
पूर्णांक sysfs_create_mount_poपूर्णांक(काष्ठा kobject *parent_kobj, स्थिर अक्षर *name)
अणु
	काष्ठा kernfs_node *kn, *parent = parent_kobj->sd;

	kn = kernfs_create_empty_dir(parent, name);
	अगर (IS_ERR(kn)) अणु
		अगर (PTR_ERR(kn) == -EEXIST)
			sysfs_warn_dup(parent, name);
		वापस PTR_ERR(kn);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_create_mount_poपूर्णांक);

/**
 *	sysfs_हटाओ_mount_poपूर्णांक - हटाओ an always empty directory.
 *	@parent_kobj: kobject that will contain this always empty directory
 *	@name: The name of the always empty directory to हटाओ
 *
 */
व्योम sysfs_हटाओ_mount_poपूर्णांक(काष्ठा kobject *parent_kobj, स्थिर अक्षर *name)
अणु
	काष्ठा kernfs_node *parent = parent_kobj->sd;

	kernfs_हटाओ_by_name_ns(parent, name, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_हटाओ_mount_poपूर्णांक);
