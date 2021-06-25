<शैली गुरु>
/*
 * FUSE: Fileप्रणाली in Userspace
 * Copyright (C) 2016 Canonical Ltd. <seth.क्रमshee@canonical.com>
 *
 * This program can be distributed under the terms of the GNU GPL.
 * See the file COPYING.
 */

#समावेश "fuse_i.h"

#समावेश <linux/posix_acl.h>
#समावेश <linux/posix_acl_xattr.h>

काष्ठा posix_acl *fuse_get_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	पूर्णांक size;
	स्थिर अक्षर *name;
	व्योम *value = शून्य;
	काष्ठा posix_acl *acl;

	अगर (fuse_is_bad(inode))
		वापस ERR_PTR(-EIO);

	अगर (!fc->posix_acl || fc->no_getxattr)
		वापस शून्य;

	अगर (type == ACL_TYPE_ACCESS)
		name = XATTR_NAME_POSIX_ACL_ACCESS;
	अन्यथा अगर (type == ACL_TYPE_DEFAULT)
		name = XATTR_NAME_POSIX_ACL_DEFAULT;
	अन्यथा
		वापस ERR_PTR(-EOPNOTSUPP);

	value = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!value)
		वापस ERR_PTR(-ENOMEM);
	size = fuse_getxattr(inode, name, value, PAGE_SIZE);
	अगर (size > 0)
		acl = posix_acl_from_xattr(fc->user_ns, value, size);
	अन्यथा अगर ((size == 0) || (size == -ENODATA) ||
		 (size == -EOPNOTSUPP && fc->no_getxattr))
		acl = शून्य;
	अन्यथा अगर (size == -दुस्फल)
		acl = ERR_PTR(-E2BIG);
	अन्यथा
		acl = ERR_PTR(size);

	kमुक्त(value);
	वापस acl;
पूर्ण

पूर्णांक fuse_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		 काष्ठा posix_acl *acl, पूर्णांक type)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	स्थिर अक्षर *name;
	पूर्णांक ret;

	अगर (fuse_is_bad(inode))
		वापस -EIO;

	अगर (!fc->posix_acl || fc->no_setxattr)
		वापस -EOPNOTSUPP;

	अगर (type == ACL_TYPE_ACCESS)
		name = XATTR_NAME_POSIX_ACL_ACCESS;
	अन्यथा अगर (type == ACL_TYPE_DEFAULT)
		name = XATTR_NAME_POSIX_ACL_DEFAULT;
	अन्यथा
		वापस -EINVAL;

	अगर (acl) अणु
		अचिन्हित पूर्णांक extra_flags = 0;
		/*
		 * Fuse userspace is responsible क्रम updating access
		 * permissions in the inode, अगर needed. fuse_setxattr
		 * invalidates the inode attributes, which will क्रमce
		 * them to be refreshed the next समय they are used,
		 * and it also updates i_स_समय.
		 */
		माप_प्रकार size = posix_acl_xattr_size(acl->a_count);
		व्योम *value;

		अगर (size > PAGE_SIZE)
			वापस -E2BIG;

		value = kदो_स्मृति(size, GFP_KERNEL);
		अगर (!value)
			वापस -ENOMEM;

		ret = posix_acl_to_xattr(fc->user_ns, acl, value, size);
		अगर (ret < 0) अणु
			kमुक्त(value);
			वापस ret;
		पूर्ण

		अगर (!in_group_p(i_gid_पूर्णांकo_mnt(&init_user_ns, inode)) &&
		    !capable_wrt_inode_uidgid(&init_user_ns, inode, CAP_FSETID))
			extra_flags |= FUSE_SETXATTR_ACL_KILL_SGID;

		ret = fuse_setxattr(inode, name, value, size, 0, extra_flags);
		kमुक्त(value);
	पूर्ण अन्यथा अणु
		ret = fuse_हटाओxattr(inode, name);
	पूर्ण
	क्रमget_all_cached_acls(inode);
	fuse_invalidate_attr(inode);

	वापस ret;
पूर्ण
