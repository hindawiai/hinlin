<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Red Hat.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/xattr.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/posix_acl.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/slab.h>

#समावेश "ctree.h"
#समावेश "btrfs_inode.h"
#समावेश "xattr.h"

काष्ठा posix_acl *btrfs_get_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	पूर्णांक size;
	स्थिर अक्षर *name;
	अक्षर *value = शून्य;
	काष्ठा posix_acl *acl;

	चयन (type) अणु
	हाल ACL_TYPE_ACCESS:
		name = XATTR_NAME_POSIX_ACL_ACCESS;
		अवरोध;
	हाल ACL_TYPE_DEFAULT:
		name = XATTR_NAME_POSIX_ACL_DEFAULT;
		अवरोध;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	size = btrfs_getxattr(inode, name, शून्य, 0);
	अगर (size > 0) अणु
		value = kzalloc(size, GFP_KERNEL);
		अगर (!value)
			वापस ERR_PTR(-ENOMEM);
		size = btrfs_getxattr(inode, name, value, size);
	पूर्ण
	अगर (size > 0)
		acl = posix_acl_from_xattr(&init_user_ns, value, size);
	अन्यथा अगर (size == -ENODATA || size == 0)
		acl = शून्य;
	अन्यथा
		acl = ERR_PTR(size);
	kमुक्त(value);

	वापस acl;
पूर्ण

अटल पूर्णांक __btrfs_set_acl(काष्ठा btrfs_trans_handle *trans,
			 काष्ठा inode *inode, काष्ठा posix_acl *acl, पूर्णांक type)
अणु
	पूर्णांक ret, size = 0;
	स्थिर अक्षर *name;
	अक्षर *value = शून्य;

	चयन (type) अणु
	हाल ACL_TYPE_ACCESS:
		name = XATTR_NAME_POSIX_ACL_ACCESS;
		अवरोध;
	हाल ACL_TYPE_DEFAULT:
		अगर (!S_ISसूची(inode->i_mode))
			वापस acl ? -EINVAL : 0;
		name = XATTR_NAME_POSIX_ACL_DEFAULT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (acl) अणु
		अचिन्हित पूर्णांक nofs_flag;

		size = posix_acl_xattr_size(acl->a_count);
		/*
		 * We're holding a transaction handle, so use a NOFS memory
		 * allocation context to aव्योम deadlock अगर reclaim happens.
		 */
		nofs_flag = meदो_स्मृति_nofs_save();
		value = kदो_स्मृति(size, GFP_KERNEL);
		meदो_स्मृति_nofs_restore(nofs_flag);
		अगर (!value) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		ret = posix_acl_to_xattr(&init_user_ns, acl, value, size);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	अगर (trans)
		ret = btrfs_setxattr(trans, inode, name, value, size, 0);
	अन्यथा
		ret = btrfs_setxattr_trans(inode, name, value, size, 0);

out:
	kमुक्त(value);

	अगर (!ret)
		set_cached_acl(inode, type, acl);

	वापस ret;
पूर्ण

पूर्णांक btrfs_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		  काष्ठा posix_acl *acl, पूर्णांक type)
अणु
	पूर्णांक ret;
	umode_t old_mode = inode->i_mode;

	अगर (type == ACL_TYPE_ACCESS && acl) अणु
		ret = posix_acl_update_mode(&init_user_ns, inode,
					    &inode->i_mode, &acl);
		अगर (ret)
			वापस ret;
	पूर्ण
	ret = __btrfs_set_acl(शून्य, inode, acl, type);
	अगर (ret)
		inode->i_mode = old_mode;
	वापस ret;
पूर्ण

पूर्णांक btrfs_init_acl(काष्ठा btrfs_trans_handle *trans,
		   काष्ठा inode *inode, काष्ठा inode *dir)
अणु
	काष्ठा posix_acl *शेष_acl, *acl;
	पूर्णांक ret = 0;

	/* this happens with subvols */
	अगर (!dir)
		वापस 0;

	ret = posix_acl_create(dir, &inode->i_mode, &शेष_acl, &acl);
	अगर (ret)
		वापस ret;

	अगर (शेष_acl) अणु
		ret = __btrfs_set_acl(trans, inode, शेष_acl,
				      ACL_TYPE_DEFAULT);
		posix_acl_release(शेष_acl);
	पूर्ण

	अगर (acl) अणु
		अगर (!ret)
			ret = __btrfs_set_acl(trans, inode, acl,
					      ACL_TYPE_ACCESS);
		posix_acl_release(acl);
	पूर्ण

	अगर (!शेष_acl && !acl)
		cache_no_acl(inode);
	वापस ret;
पूर्ण
