<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/sysfs/symlink.c - sysfs symlink implementation
 *
 * Copyright (c) 2001-3 Patrick Mochel
 * Copyright (c) 2007 SUSE Linux Products GmbH
 * Copyright (c) 2007 Tejun Heo <teheo@suse.de>
 *
 * Please see Documentation/fileप्रणालीs/sysfs.rst क्रम more inक्रमmation.
 */

#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/kobject.h>
#समावेश <linux/mutex.h>
#समावेश <linux/security.h>

#समावेश "sysfs.h"

अटल पूर्णांक sysfs_करो_create_link_sd(काष्ठा kernfs_node *parent,
				   काष्ठा kobject *target_kobj,
				   स्थिर अक्षर *name, पूर्णांक warn)
अणु
	काष्ठा kernfs_node *kn, *target = शून्य;

	अगर (WARN_ON(!name || !parent))
		वापस -EINVAL;

	/*
	 * We करोn't own @target_kobj and it may be हटाओd at any समय.
	 * Synchronize using sysfs_symlink_target_lock.  See
	 * sysfs_हटाओ_dir() क्रम details.
	 */
	spin_lock(&sysfs_symlink_target_lock);
	अगर (target_kobj->sd) अणु
		target = target_kobj->sd;
		kernfs_get(target);
	पूर्ण
	spin_unlock(&sysfs_symlink_target_lock);

	अगर (!target)
		वापस -ENOENT;

	kn = kernfs_create_link(parent, name, target);
	kernfs_put(target);

	अगर (!IS_ERR(kn))
		वापस 0;

	अगर (warn && PTR_ERR(kn) == -EEXIST)
		sysfs_warn_dup(parent, name);
	वापस PTR_ERR(kn);
पूर्ण

/**
 *	sysfs_create_link_sd - create symlink to a given object.
 *	@kn:		directory we're creating the link in.
 *	@target:	object we're poपूर्णांकing to.
 *	@name:		name of the symlink.
 */
पूर्णांक sysfs_create_link_sd(काष्ठा kernfs_node *kn, काष्ठा kobject *target,
			 स्थिर अक्षर *name)
अणु
	वापस sysfs_करो_create_link_sd(kn, target, name, 1);
पूर्ण

अटल पूर्णांक sysfs_करो_create_link(काष्ठा kobject *kobj, काष्ठा kobject *target,
				स्थिर अक्षर *name, पूर्णांक warn)
अणु
	काष्ठा kernfs_node *parent = शून्य;

	अगर (!kobj)
		parent = sysfs_root_kn;
	अन्यथा
		parent = kobj->sd;

	अगर (!parent)
		वापस -EFAULT;

	वापस sysfs_करो_create_link_sd(parent, target, name, warn);
पूर्ण

/**
 *	sysfs_create_link - create symlink between two objects.
 *	@kobj:	object whose directory we're creating the link in.
 *	@target:	object we're poपूर्णांकing to.
 *	@name:		name of the symlink.
 */
पूर्णांक sysfs_create_link(काष्ठा kobject *kobj, काष्ठा kobject *target,
		      स्थिर अक्षर *name)
अणु
	वापस sysfs_करो_create_link(kobj, target, name, 1);
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_create_link);

/**
 *	sysfs_create_link_nowarn - create symlink between two objects.
 *	@kobj:	object whose directory we're creating the link in.
 *	@target:	object we're poपूर्णांकing to.
 *	@name:		name of the symlink.
 *
 *	This function करोes the same as sysfs_create_link(), but it
 *	करोesn't warn अगर the link alपढ़ोy exists.
 */
पूर्णांक sysfs_create_link_nowarn(काष्ठा kobject *kobj, काष्ठा kobject *target,
			     स्थिर अक्षर *name)
अणु
	वापस sysfs_करो_create_link(kobj, target, name, 0);
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_create_link_nowarn);

/**
 *	sysfs_delete_link - हटाओ symlink in object's directory.
 *	@kobj:	object we're acting क्रम.
 *	@targ:	object we're poपूर्णांकing to.
 *	@name:	name of the symlink to हटाओ.
 *
 *	Unlike sysfs_हटाओ_link sysfs_delete_link has enough inक्रमmation
 *	to successfully delete symlinks in tagged directories.
 */
व्योम sysfs_delete_link(काष्ठा kobject *kobj, काष्ठा kobject *targ,
			स्थिर अक्षर *name)
अणु
	स्थिर व्योम *ns = शून्य;

	/*
	 * We करोn't own @target and it may be हटाओd at any समय.
	 * Synchronize using sysfs_symlink_target_lock.  See
	 * sysfs_हटाओ_dir() क्रम details.
	 */
	spin_lock(&sysfs_symlink_target_lock);
	अगर (targ->sd && kernfs_ns_enabled(kobj->sd))
		ns = targ->sd->ns;
	spin_unlock(&sysfs_symlink_target_lock);
	kernfs_हटाओ_by_name_ns(kobj->sd, name, ns);
पूर्ण

/**
 *	sysfs_हटाओ_link - हटाओ symlink in object's directory.
 *	@kobj:	object we're acting क्रम.
 *	@name:	name of the symlink to हटाओ.
 */
व्योम sysfs_हटाओ_link(काष्ठा kobject *kobj, स्थिर अक्षर *name)
अणु
	काष्ठा kernfs_node *parent = शून्य;

	अगर (!kobj)
		parent = sysfs_root_kn;
	अन्यथा
		parent = kobj->sd;

	kernfs_हटाओ_by_name(parent, name);
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_हटाओ_link);

/**
 *	sysfs_नाम_link_ns - नाम symlink in object's directory.
 *	@kobj:	object we're acting क्रम.
 *	@targ:	object we're poपूर्णांकing to.
 *	@old:	previous name of the symlink.
 *	@new:	new name of the symlink.
 *	@new_ns: new namespace of the symlink.
 *
 *	A helper function क्रम the common नाम symlink idiom.
 */
पूर्णांक sysfs_नाम_link_ns(काष्ठा kobject *kobj, काष्ठा kobject *targ,
			 स्थिर अक्षर *old, स्थिर अक्षर *new, स्थिर व्योम *new_ns)
अणु
	काष्ठा kernfs_node *parent, *kn = शून्य;
	स्थिर व्योम *old_ns = शून्य;
	पूर्णांक result;

	अगर (!kobj)
		parent = sysfs_root_kn;
	अन्यथा
		parent = kobj->sd;

	अगर (targ->sd)
		old_ns = targ->sd->ns;

	result = -ENOENT;
	kn = kernfs_find_and_get_ns(parent, old, old_ns);
	अगर (!kn)
		जाओ out;

	result = -EINVAL;
	अगर (kernfs_type(kn) != KERNFS_LINK)
		जाओ out;
	अगर (kn->symlink.target_kn->priv != targ)
		जाओ out;

	result = kernfs_नाम_ns(kn, parent, new, new_ns);

out:
	kernfs_put(kn);
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_नाम_link_ns);
