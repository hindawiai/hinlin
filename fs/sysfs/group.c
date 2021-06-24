<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/sysfs/group.c - Operations क्रम adding/removing multiple files at once.
 *
 * Copyright (c) 2003 Patrick Mochel
 * Copyright (c) 2003 Open Source Development Lab
 * Copyright (c) 2013 Greg Kroah-Harपंचांगan
 * Copyright (c) 2013 The Linux Foundation
 */

#समावेश <linux/kobject.h>
#समावेश <linux/module.h>
#समावेश <linux/dcache.h>
#समावेश <linux/namei.h>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश "sysfs.h"


अटल व्योम हटाओ_files(काष्ठा kernfs_node *parent,
			 स्थिर काष्ठा attribute_group *grp)
अणु
	काष्ठा attribute *स्थिर *attr;
	काष्ठा bin_attribute *स्थिर *bin_attr;

	अगर (grp->attrs)
		क्रम (attr = grp->attrs; *attr; attr++)
			kernfs_हटाओ_by_name(parent, (*attr)->name);
	अगर (grp->bin_attrs)
		क्रम (bin_attr = grp->bin_attrs; *bin_attr; bin_attr++)
			kernfs_हटाओ_by_name(parent, (*bin_attr)->attr.name);
पूर्ण

अटल पूर्णांक create_files(काष्ठा kernfs_node *parent, काष्ठा kobject *kobj,
			kuid_t uid, kgid_t gid,
			स्थिर काष्ठा attribute_group *grp, पूर्णांक update)
अणु
	काष्ठा attribute *स्थिर *attr;
	काष्ठा bin_attribute *स्थिर *bin_attr;
	पूर्णांक error = 0, i;

	अगर (grp->attrs) अणु
		क्रम (i = 0, attr = grp->attrs; *attr && !error; i++, attr++) अणु
			umode_t mode = (*attr)->mode;

			/*
			 * In update mode, we're changing the permissions or
			 * visibility.  Do this by first removing then
			 * re-adding (अगर required) the file.
			 */
			अगर (update)
				kernfs_हटाओ_by_name(parent, (*attr)->name);
			अगर (grp->is_visible) अणु
				mode = grp->is_visible(kobj, *attr, i);
				अगर (!mode)
					जारी;
			पूर्ण

			WARN(mode & ~(SYSFS_PREALLOC | 0664),
			     "Attribute %s: Invalid permissions 0%o\n",
			     (*attr)->name, mode);

			mode &= SYSFS_PREALLOC | 0664;
			error = sysfs_add_file_mode_ns(parent, *attr, false,
						       mode, uid, gid, शून्य);
			अगर (unlikely(error))
				अवरोध;
		पूर्ण
		अगर (error) अणु
			हटाओ_files(parent, grp);
			जाओ निकास;
		पूर्ण
	पूर्ण

	अगर (grp->bin_attrs) अणु
		क्रम (i = 0, bin_attr = grp->bin_attrs; *bin_attr; i++, bin_attr++) अणु
			umode_t mode = (*bin_attr)->attr.mode;

			अगर (update)
				kernfs_हटाओ_by_name(parent,
						(*bin_attr)->attr.name);
			अगर (grp->is_bin_visible) अणु
				mode = grp->is_bin_visible(kobj, *bin_attr, i);
				अगर (!mode)
					जारी;
			पूर्ण

			WARN(mode & ~(SYSFS_PREALLOC | 0664),
			     "Attribute %s: Invalid permissions 0%o\n",
			     (*bin_attr)->attr.name, mode);

			mode &= SYSFS_PREALLOC | 0664;
			error = sysfs_add_file_mode_ns(parent,
					&(*bin_attr)->attr, true,
					mode,
					uid, gid, शून्य);
			अगर (error)
				अवरोध;
		पूर्ण
		अगर (error)
			हटाओ_files(parent, grp);
	पूर्ण
निकास:
	वापस error;
पूर्ण


अटल पूर्णांक पूर्णांकernal_create_group(काष्ठा kobject *kobj, पूर्णांक update,
				 स्थिर काष्ठा attribute_group *grp)
अणु
	काष्ठा kernfs_node *kn;
	kuid_t uid;
	kgid_t gid;
	पूर्णांक error;

	अगर (WARN_ON(!kobj || (!update && !kobj->sd)))
		वापस -EINVAL;

	/* Updates may happen beक्रमe the object has been instantiated */
	अगर (unlikely(update && !kobj->sd))
		वापस -EINVAL;
	अगर (!grp->attrs && !grp->bin_attrs) अणु
		WARN(1, "sysfs: (bin_)attrs not set by subsystem for group: %s/%s\n",
			kobj->name, grp->name ?: "");
		वापस -EINVAL;
	पूर्ण
	kobject_get_ownership(kobj, &uid, &gid);
	अगर (grp->name) अणु
		अगर (update) अणु
			kn = kernfs_find_and_get(kobj->sd, grp->name);
			अगर (!kn) अणु
				pr_warn("Can't update unknown attr grp name: %s/%s\n",
					kobj->name, grp->name);
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			kn = kernfs_create_dir_ns(kobj->sd, grp->name,
						  S_IRWXU | S_IRUGO | S_IXUGO,
						  uid, gid, kobj, शून्य);
			अगर (IS_ERR(kn)) अणु
				अगर (PTR_ERR(kn) == -EEXIST)
					sysfs_warn_dup(kobj->sd, grp->name);
				वापस PTR_ERR(kn);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		kn = kobj->sd;
	kernfs_get(kn);
	error = create_files(kn, kobj, uid, gid, grp, update);
	अगर (error) अणु
		अगर (grp->name)
			kernfs_हटाओ(kn);
	पूर्ण
	kernfs_put(kn);

	अगर (grp->name && update)
		kernfs_put(kn);

	वापस error;
पूर्ण

/**
 * sysfs_create_group - given a directory kobject, create an attribute group
 * @kobj:	The kobject to create the group on
 * @grp:	The attribute group to create
 *
 * This function creates a group क्रम the first समय.  It will explicitly
 * warn and error अगर any of the attribute files being created alपढ़ोy exist.
 *
 * Returns 0 on success or error code on failure.
 */
पूर्णांक sysfs_create_group(काष्ठा kobject *kobj,
		       स्थिर काष्ठा attribute_group *grp)
अणु
	वापस पूर्णांकernal_create_group(kobj, 0, grp);
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_create_group);

अटल पूर्णांक पूर्णांकernal_create_groups(काष्ठा kobject *kobj, पूर्णांक update,
				  स्थिर काष्ठा attribute_group **groups)
अणु
	पूर्णांक error = 0;
	पूर्णांक i;

	अगर (!groups)
		वापस 0;

	क्रम (i = 0; groups[i]; i++) अणु
		error = पूर्णांकernal_create_group(kobj, update, groups[i]);
		अगर (error) अणु
			जबतक (--i >= 0)
				sysfs_हटाओ_group(kobj, groups[i]);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस error;
पूर्ण

/**
 * sysfs_create_groups - given a directory kobject, create a bunch of attribute groups
 * @kobj:	The kobject to create the group on
 * @groups:	The attribute groups to create, शून्य terminated
 *
 * This function creates a bunch of attribute groups.  If an error occurs when
 * creating a group, all previously created groups will be हटाओd, unwinding
 * everything back to the original state when this function was called.
 * It will explicitly warn and error अगर any of the attribute files being
 * created alपढ़ोy exist.
 *
 * Returns 0 on success or error code from sysfs_create_group on failure.
 */
पूर्णांक sysfs_create_groups(काष्ठा kobject *kobj,
			स्थिर काष्ठा attribute_group **groups)
अणु
	वापस पूर्णांकernal_create_groups(kobj, 0, groups);
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_create_groups);

/**
 * sysfs_update_groups - given a directory kobject, create a bunch of attribute groups
 * @kobj:	The kobject to update the group on
 * @groups:	The attribute groups to update, शून्य terminated
 *
 * This function update a bunch of attribute groups.  If an error occurs when
 * updating a group, all previously updated groups will be हटाओd together
 * with alपढ़ोy existing (not updated) attributes.
 *
 * Returns 0 on success or error code from sysfs_update_group on failure.
 */
पूर्णांक sysfs_update_groups(काष्ठा kobject *kobj,
			स्थिर काष्ठा attribute_group **groups)
अणु
	वापस पूर्णांकernal_create_groups(kobj, 1, groups);
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_update_groups);

/**
 * sysfs_update_group - given a directory kobject, update an attribute group
 * @kobj:	The kobject to update the group on
 * @grp:	The attribute group to update
 *
 * This function updates an attribute group.  Unlike
 * sysfs_create_group(), it will explicitly not warn or error अगर any
 * of the attribute files being created alपढ़ोy exist.  Furthermore,
 * अगर the visibility of the files has changed through the is_visible()
 * callback, it will update the permissions and add or हटाओ the
 * relevant files. Changing a group's name (subdirectory name under
 * kobj's directory in sysfs) is not allowed.
 *
 * The primary use क्रम this function is to call it after making a change
 * that affects group visibility.
 *
 * Returns 0 on success or error code on failure.
 */
पूर्णांक sysfs_update_group(काष्ठा kobject *kobj,
		       स्थिर काष्ठा attribute_group *grp)
अणु
	वापस पूर्णांकernal_create_group(kobj, 1, grp);
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_update_group);

/**
 * sysfs_हटाओ_group: हटाओ a group from a kobject
 * @kobj:	kobject to हटाओ the group from
 * @grp:	group to हटाओ
 *
 * This function हटाओs a group of attributes from a kobject.  The attributes
 * previously have to have been created क्रम this group, otherwise it will fail.
 */
व्योम sysfs_हटाओ_group(काष्ठा kobject *kobj,
			स्थिर काष्ठा attribute_group *grp)
अणु
	काष्ठा kernfs_node *parent = kobj->sd;
	काष्ठा kernfs_node *kn;

	अगर (grp->name) अणु
		kn = kernfs_find_and_get(parent, grp->name);
		अगर (!kn) अणु
			WARN(!kn, KERN_WARNING
			     "sysfs group '%s' not found for kobject '%s'\n",
			     grp->name, kobject_name(kobj));
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		kn = parent;
		kernfs_get(kn);
	पूर्ण

	हटाओ_files(kn, grp);
	अगर (grp->name)
		kernfs_हटाओ(kn);

	kernfs_put(kn);
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_हटाओ_group);

/**
 * sysfs_हटाओ_groups - हटाओ a list of groups
 *
 * @kobj:	The kobject क्रम the groups to be हटाओd from
 * @groups:	शून्य terminated list of groups to be हटाओd
 *
 * If groups is not शून्य, हटाओ the specअगरied groups from the kobject.
 */
व्योम sysfs_हटाओ_groups(काष्ठा kobject *kobj,
			 स्थिर काष्ठा attribute_group **groups)
अणु
	पूर्णांक i;

	अगर (!groups)
		वापस;
	क्रम (i = 0; groups[i]; i++)
		sysfs_हटाओ_group(kobj, groups[i]);
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_हटाओ_groups);

/**
 * sysfs_merge_group - merge files पूर्णांकo a pre-existing attribute group.
 * @kobj:	The kobject containing the group.
 * @grp:	The files to create and the attribute group they beदीर्घ to.
 *
 * This function वापसs an error अगर the group करोesn't exist or any of the
 * files alपढ़ोy exist in that group, in which हाल none of the new files
 * are created.
 */
पूर्णांक sysfs_merge_group(काष्ठा kobject *kobj,
		       स्थिर काष्ठा attribute_group *grp)
अणु
	काष्ठा kernfs_node *parent;
	kuid_t uid;
	kgid_t gid;
	पूर्णांक error = 0;
	काष्ठा attribute *स्थिर *attr;
	पूर्णांक i;

	parent = kernfs_find_and_get(kobj->sd, grp->name);
	अगर (!parent)
		वापस -ENOENT;

	kobject_get_ownership(kobj, &uid, &gid);

	क्रम ((i = 0, attr = grp->attrs); *attr && !error; (++i, ++attr))
		error = sysfs_add_file_mode_ns(parent, *attr, false,
					       (*attr)->mode, uid, gid, शून्य);
	अगर (error) अणु
		जबतक (--i >= 0)
			kernfs_हटाओ_by_name(parent, (*--attr)->name);
	पूर्ण
	kernfs_put(parent);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_merge_group);

/**
 * sysfs_unmerge_group - हटाओ files from a pre-existing attribute group.
 * @kobj:	The kobject containing the group.
 * @grp:	The files to हटाओ and the attribute group they beदीर्घ to.
 */
व्योम sysfs_unmerge_group(काष्ठा kobject *kobj,
		       स्थिर काष्ठा attribute_group *grp)
अणु
	काष्ठा kernfs_node *parent;
	काष्ठा attribute *स्थिर *attr;

	parent = kernfs_find_and_get(kobj->sd, grp->name);
	अगर (parent) अणु
		क्रम (attr = grp->attrs; *attr; ++attr)
			kernfs_हटाओ_by_name(parent, (*attr)->name);
		kernfs_put(parent);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_unmerge_group);

/**
 * sysfs_add_link_to_group - add a symlink to an attribute group.
 * @kobj:	The kobject containing the group.
 * @group_name:	The name of the group.
 * @target:	The target kobject of the symlink to create.
 * @link_name:	The name of the symlink to create.
 */
पूर्णांक sysfs_add_link_to_group(काष्ठा kobject *kobj, स्थिर अक्षर *group_name,
			    काष्ठा kobject *target, स्थिर अक्षर *link_name)
अणु
	काष्ठा kernfs_node *parent;
	पूर्णांक error = 0;

	parent = kernfs_find_and_get(kobj->sd, group_name);
	अगर (!parent)
		वापस -ENOENT;

	error = sysfs_create_link_sd(parent, target, link_name);
	kernfs_put(parent);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_add_link_to_group);

/**
 * sysfs_हटाओ_link_from_group - हटाओ a symlink from an attribute group.
 * @kobj:	The kobject containing the group.
 * @group_name:	The name of the group.
 * @link_name:	The name of the symlink to हटाओ.
 */
व्योम sysfs_हटाओ_link_from_group(काष्ठा kobject *kobj, स्थिर अक्षर *group_name,
				  स्थिर अक्षर *link_name)
अणु
	काष्ठा kernfs_node *parent;

	parent = kernfs_find_and_get(kobj->sd, group_name);
	अगर (parent) अणु
		kernfs_हटाओ_by_name(parent, link_name);
		kernfs_put(parent);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_हटाओ_link_from_group);

/**
 * compat_only_sysfs_link_entry_to_kobj - add a symlink to a kobject poपूर्णांकing
 * to a group or an attribute
 * @kobj:		The kobject containing the group.
 * @target_kobj:	The target kobject.
 * @target_name:	The name of the target group or attribute.
 * @symlink_name:	The name of the symlink file (target_name will be
 *			considered अगर symlink_name is शून्य).
 */
पूर्णांक compat_only_sysfs_link_entry_to_kobj(काष्ठा kobject *kobj,
					 काष्ठा kobject *target_kobj,
					 स्थिर अक्षर *target_name,
					 स्थिर अक्षर *symlink_name)
अणु
	काष्ठा kernfs_node *target;
	काष्ठा kernfs_node *entry;
	काष्ठा kernfs_node *link;

	/*
	 * We करोn't own @target_kobj and it may be हटाओd at any समय.
	 * Synchronize using sysfs_symlink_target_lock. See sysfs_हटाओ_dir()
	 * क्रम details.
	 */
	spin_lock(&sysfs_symlink_target_lock);
	target = target_kobj->sd;
	अगर (target)
		kernfs_get(target);
	spin_unlock(&sysfs_symlink_target_lock);
	अगर (!target)
		वापस -ENOENT;

	entry = kernfs_find_and_get(target_kobj->sd, target_name);
	अगर (!entry) अणु
		kernfs_put(target);
		वापस -ENOENT;
	पूर्ण

	अगर (!symlink_name)
		symlink_name = target_name;

	link = kernfs_create_link(kobj->sd, symlink_name, entry);
	अगर (PTR_ERR(link) == -EEXIST)
		sysfs_warn_dup(kobj->sd, symlink_name);

	kernfs_put(entry);
	kernfs_put(target);
	वापस PTR_ERR_OR_ZERO(link);
पूर्ण
EXPORT_SYMBOL_GPL(compat_only_sysfs_link_entry_to_kobj);

अटल पूर्णांक sysfs_group_attrs_change_owner(काष्ठा kernfs_node *grp_kn,
					  स्थिर काष्ठा attribute_group *grp,
					  काष्ठा iattr *newattrs)
अणु
	काष्ठा kernfs_node *kn;
	पूर्णांक error;

	अगर (grp->attrs) अणु
		काष्ठा attribute *स्थिर *attr;

		क्रम (attr = grp->attrs; *attr; attr++) अणु
			kn = kernfs_find_and_get(grp_kn, (*attr)->name);
			अगर (!kn)
				वापस -ENOENT;

			error = kernfs_setattr(kn, newattrs);
			kernfs_put(kn);
			अगर (error)
				वापस error;
		पूर्ण
	पूर्ण

	अगर (grp->bin_attrs) अणु
		काष्ठा bin_attribute *स्थिर *bin_attr;

		क्रम (bin_attr = grp->bin_attrs; *bin_attr; bin_attr++) अणु
			kn = kernfs_find_and_get(grp_kn, (*bin_attr)->attr.name);
			अगर (!kn)
				वापस -ENOENT;

			error = kernfs_setattr(kn, newattrs);
			kernfs_put(kn);
			अगर (error)
				वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sysfs_group_change_owner - change owner of an attribute group.
 * @kobj:	The kobject containing the group.
 * @grp:	The attribute group.
 * @kuid:	new owner's kuid
 * @kgid:	new owner's kgid
 *
 * Returns 0 on success or error code on failure.
 */
पूर्णांक sysfs_group_change_owner(काष्ठा kobject *kobj,
			     स्थिर काष्ठा attribute_group *grp, kuid_t kuid,
			     kgid_t kgid)
अणु
	काष्ठा kernfs_node *grp_kn;
	पूर्णांक error;
	काष्ठा iattr newattrs = अणु
		.ia_valid = ATTR_UID | ATTR_GID,
		.ia_uid = kuid,
		.ia_gid = kgid,
	पूर्ण;

	अगर (!kobj->state_in_sysfs)
		वापस -EINVAL;

	अगर (grp->name) अणु
		grp_kn = kernfs_find_and_get(kobj->sd, grp->name);
	पूर्ण अन्यथा अणु
		kernfs_get(kobj->sd);
		grp_kn = kobj->sd;
	पूर्ण
	अगर (!grp_kn)
		वापस -ENOENT;

	error = kernfs_setattr(grp_kn, &newattrs);
	अगर (!error)
		error = sysfs_group_attrs_change_owner(grp_kn, grp, &newattrs);

	kernfs_put(grp_kn);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_group_change_owner);

/**
 * sysfs_groups_change_owner - change owner of a set of attribute groups.
 * @kobj:	The kobject containing the groups.
 * @groups:	The attribute groups.
 * @kuid:	new owner's kuid
 * @kgid:	new owner's kgid
 *
 * Returns 0 on success or error code on failure.
 */
पूर्णांक sysfs_groups_change_owner(काष्ठा kobject *kobj,
			      स्थिर काष्ठा attribute_group **groups,
			      kuid_t kuid, kgid_t kgid)
अणु
	पूर्णांक error = 0, i;

	अगर (!kobj->state_in_sysfs)
		वापस -EINVAL;

	अगर (!groups)
		वापस 0;

	क्रम (i = 0; groups[i]; i++) अणु
		error = sysfs_group_change_owner(kobj, groups[i], kuid, kgid);
		अगर (error)
			अवरोध;
	पूर्ण

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(sysfs_groups_change_owner);
