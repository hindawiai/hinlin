<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * security/tomoyo/mount.c
 *
 * Copyright (C) 2005-2011  NTT DATA CORPORATION
 */

#समावेश <linux/slab.h>
#समावेश <uapi/linux/mount.h>
#समावेश "common.h"

/* String table क्रम special mount operations. */
अटल स्थिर अक्षर * स्थिर tomoyo_mounts[TOMOYO_MAX_SPECIAL_MOUNT] = अणु
	[TOMOYO_MOUNT_BIND]            = "--bind",
	[TOMOYO_MOUNT_MOVE]            = "--move",
	[TOMOYO_MOUNT_REMOUNT]         = "--remount",
	[TOMOYO_MOUNT_MAKE_UNBINDABLE] = "--make-unbindable",
	[TOMOYO_MOUNT_MAKE_PRIVATE]    = "--make-private",
	[TOMOYO_MOUNT_MAKE_SLAVE]      = "--make-slave",
	[TOMOYO_MOUNT_MAKE_SHARED]     = "--make-shared",
पूर्ण;

/**
 * tomoyo_audit_mount_log - Audit mount log.
 *
 * @r: Poपूर्णांकer to "struct tomoyo_request_info".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_audit_mount_log(काष्ठा tomoyo_request_info *r)
अणु
	वापस tomoyo_supervisor(r, "file mount %s %s %s 0x%lX\n",
				 r->param.mount.dev->name,
				 r->param.mount.dir->name,
				 r->param.mount.type->name,
				 r->param.mount.flags);
पूर्ण

/**
 * tomoyo_check_mount_acl - Check permission क्रम path path path number operation.
 *
 * @r:   Poपूर्णांकer to "struct tomoyo_request_info".
 * @ptr: Poपूर्णांकer to "struct tomoyo_acl_info".
 *
 * Returns true अगर granted, false otherwise.
 */
अटल bool tomoyo_check_mount_acl(काष्ठा tomoyo_request_info *r,
				   स्थिर काष्ठा tomoyo_acl_info *ptr)
अणु
	स्थिर काष्ठा tomoyo_mount_acl *acl =
		container_of(ptr, typeof(*acl), head);

	वापस tomoyo_compare_number_जोड़(r->param.mount.flags,
					   &acl->flags) &&
		tomoyo_compare_name_जोड़(r->param.mount.type,
					  &acl->fs_type) &&
		tomoyo_compare_name_जोड़(r->param.mount.dir,
					  &acl->dir_name) &&
		(!r->param.mount.need_dev ||
		 tomoyo_compare_name_जोड़(r->param.mount.dev,
					   &acl->dev_name));
पूर्ण

/**
 * tomoyo_mount_acl - Check permission क्रम mount() operation.
 *
 * @r:        Poपूर्णांकer to "struct tomoyo_request_info".
 * @dev_name: Name of device file. Maybe शून्य.
 * @dir:      Poपूर्णांकer to "struct path".
 * @type:     Name of fileप्रणाली type.
 * @flags:    Mount options.
 *
 * Returns 0 on success, negative value otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
अटल पूर्णांक tomoyo_mount_acl(काष्ठा tomoyo_request_info *r,
			    स्थिर अक्षर *dev_name,
			    स्थिर काष्ठा path *dir, स्थिर अक्षर *type,
			    अचिन्हित दीर्घ flags)
अणु
	काष्ठा tomoyo_obj_info obj = अणु पूर्ण;
	काष्ठा path path;
	काष्ठा file_प्रणाली_type *fstype = शून्य;
	स्थिर अक्षर *requested_type = शून्य;
	स्थिर अक्षर *requested_dir_name = शून्य;
	स्थिर अक्षर *requested_dev_name = शून्य;
	काष्ठा tomoyo_path_info rtype;
	काष्ठा tomoyo_path_info rdev;
	काष्ठा tomoyo_path_info rdir;
	पूर्णांक need_dev = 0;
	पूर्णांक error = -ENOMEM;

	r->obj = &obj;

	/* Get fstype. */
	requested_type = tomoyo_encode(type);
	अगर (!requested_type)
		जाओ out;
	rtype.name = requested_type;
	tomoyo_fill_path_info(&rtype);

	/* Get mount poपूर्णांक. */
	obj.path2 = *dir;
	requested_dir_name = tomoyo_realpath_from_path(dir);
	अगर (!requested_dir_name) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण
	rdir.name = requested_dir_name;
	tomoyo_fill_path_info(&rdir);

	/* Compare fs name. */
	अगर (type == tomoyo_mounts[TOMOYO_MOUNT_REMOUNT]) अणु
		/* dev_name is ignored. */
	पूर्ण अन्यथा अगर (type == tomoyo_mounts[TOMOYO_MOUNT_MAKE_UNBINDABLE] ||
		   type == tomoyo_mounts[TOMOYO_MOUNT_MAKE_PRIVATE] ||
		   type == tomoyo_mounts[TOMOYO_MOUNT_MAKE_SLAVE] ||
		   type == tomoyo_mounts[TOMOYO_MOUNT_MAKE_SHARED]) अणु
		/* dev_name is ignored. */
	पूर्ण अन्यथा अगर (type == tomoyo_mounts[TOMOYO_MOUNT_BIND] ||
		   type == tomoyo_mounts[TOMOYO_MOUNT_MOVE]) अणु
		need_dev = -1; /* dev_name is a directory */
	पूर्ण अन्यथा अणु
		fstype = get_fs_type(type);
		अगर (!fstype) अणु
			error = -ENODEV;
			जाओ out;
		पूर्ण
		अगर (fstype->fs_flags & FS_REQUIRES_DEV)
			/* dev_name is a block device file. */
			need_dev = 1;
	पूर्ण
	अगर (need_dev) अणु
		/* Get mount poपूर्णांक or device file. */
		अगर (!dev_name || kern_path(dev_name, LOOKUP_FOLLOW, &path)) अणु
			error = -ENOENT;
			जाओ out;
		पूर्ण
		obj.path1 = path;
		requested_dev_name = tomoyo_realpath_from_path(&path);
		अगर (!requested_dev_name) अणु
			error = -ENOENT;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Map dev_name to "<NULL>" अगर no dev_name given. */
		अगर (!dev_name)
			dev_name = "<NULL>";
		requested_dev_name = tomoyo_encode(dev_name);
		अगर (!requested_dev_name) अणु
			error = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण
	rdev.name = requested_dev_name;
	tomoyo_fill_path_info(&rdev);
	r->param_type = TOMOYO_TYPE_MOUNT_ACL;
	r->param.mount.need_dev = need_dev;
	r->param.mount.dev = &rdev;
	r->param.mount.dir = &rdir;
	r->param.mount.type = &rtype;
	r->param.mount.flags = flags;
	करो अणु
		tomoyo_check_acl(r, tomoyo_check_mount_acl);
		error = tomoyo_audit_mount_log(r);
	पूर्ण जबतक (error == TOMOYO_RETRY_REQUEST);
 out:
	kमुक्त(requested_dev_name);
	kमुक्त(requested_dir_name);
	अगर (fstype)
		put_fileप्रणाली(fstype);
	kमुक्त(requested_type);
	/* Drop refcount obtained by kern_path(). */
	अगर (obj.path1.dentry)
		path_put(&obj.path1);
	वापस error;
पूर्ण

/**
 * tomoyo_mount_permission - Check permission क्रम mount() operation.
 *
 * @dev_name:  Name of device file. Maybe शून्य.
 * @path:      Poपूर्णांकer to "struct path".
 * @type:      Name of fileप्रणाली type. Maybe शून्य.
 * @flags:     Mount options.
 * @data_page: Optional data. Maybe शून्य.
 *
 * Returns 0 on success, negative value otherwise.
 */
पूर्णांक tomoyo_mount_permission(स्थिर अक्षर *dev_name, स्थिर काष्ठा path *path,
			    स्थिर अक्षर *type, अचिन्हित दीर्घ flags,
			    व्योम *data_page)
अणु
	काष्ठा tomoyo_request_info r;
	पूर्णांक error;
	पूर्णांक idx;

	अगर (tomoyo_init_request_info(&r, शून्य, TOMOYO_MAC_खाता_MOUNT)
	    == TOMOYO_CONFIG_DISABLED)
		वापस 0;
	अगर ((flags & MS_MGC_MSK) == MS_MGC_VAL)
		flags &= ~MS_MGC_MSK;
	अगर (flags & MS_REMOUNT) अणु
		type = tomoyo_mounts[TOMOYO_MOUNT_REMOUNT];
		flags &= ~MS_REMOUNT;
	पूर्ण अन्यथा अगर (flags & MS_BIND) अणु
		type = tomoyo_mounts[TOMOYO_MOUNT_BIND];
		flags &= ~MS_BIND;
	पूर्ण अन्यथा अगर (flags & MS_SHARED) अणु
		अगर (flags & (MS_PRIVATE | MS_SLAVE | MS_UNBINDABLE))
			वापस -EINVAL;
		type = tomoyo_mounts[TOMOYO_MOUNT_MAKE_SHARED];
		flags &= ~MS_SHARED;
	पूर्ण अन्यथा अगर (flags & MS_PRIVATE) अणु
		अगर (flags & (MS_SHARED | MS_SLAVE | MS_UNBINDABLE))
			वापस -EINVAL;
		type = tomoyo_mounts[TOMOYO_MOUNT_MAKE_PRIVATE];
		flags &= ~MS_PRIVATE;
	पूर्ण अन्यथा अगर (flags & MS_SLAVE) अणु
		अगर (flags & (MS_SHARED | MS_PRIVATE | MS_UNBINDABLE))
			वापस -EINVAL;
		type = tomoyo_mounts[TOMOYO_MOUNT_MAKE_SLAVE];
		flags &= ~MS_SLAVE;
	पूर्ण अन्यथा अगर (flags & MS_UNBINDABLE) अणु
		अगर (flags & (MS_SHARED | MS_PRIVATE | MS_SLAVE))
			वापस -EINVAL;
		type = tomoyo_mounts[TOMOYO_MOUNT_MAKE_UNBINDABLE];
		flags &= ~MS_UNBINDABLE;
	पूर्ण अन्यथा अगर (flags & MS_MOVE) अणु
		type = tomoyo_mounts[TOMOYO_MOUNT_MOVE];
		flags &= ~MS_MOVE;
	पूर्ण
	अगर (!type)
		type = "<NULL>";
	idx = tomoyo_पढ़ो_lock();
	error = tomoyo_mount_acl(&r, dev_name, path, type, flags);
	tomoyo_पढ़ो_unlock(idx);
	वापस error;
पूर्ण
