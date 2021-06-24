<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) International Business Machines  Corp., 2002-2004
 *   Copyright (C) Andreas Gruenbacher, 2001
 *   Copyright (C) Linus Torvalds, 1991, 1992
 */

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश "jfs_incore.h"
#समावेश "jfs_txnmgr.h"
#समावेश "jfs_xattr.h"
#समावेश "jfs_acl.h"

काष्ठा posix_acl *jfs_get_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	काष्ठा posix_acl *acl;
	अक्षर *ea_name;
	पूर्णांक size;
	अक्षर *value = शून्य;

	चयन(type) अणु
		हाल ACL_TYPE_ACCESS:
			ea_name = XATTR_NAME_POSIX_ACL_ACCESS;
			अवरोध;
		हाल ACL_TYPE_DEFAULT:
			ea_name = XATTR_NAME_POSIX_ACL_DEFAULT;
			अवरोध;
		शेष:
			वापस ERR_PTR(-EINVAL);
	पूर्ण

	size = __jfs_getxattr(inode, ea_name, शून्य, 0);

	अगर (size > 0) अणु
		value = kदो_स्मृति(size, GFP_KERNEL);
		अगर (!value)
			वापस ERR_PTR(-ENOMEM);
		size = __jfs_getxattr(inode, ea_name, value, size);
	पूर्ण

	अगर (size < 0) अणु
		अगर (size == -ENODATA)
			acl = शून्य;
		अन्यथा
			acl = ERR_PTR(size);
	पूर्ण अन्यथा अणु
		acl = posix_acl_from_xattr(&init_user_ns, value, size);
	पूर्ण
	kमुक्त(value);
	वापस acl;
पूर्ण

अटल पूर्णांक __jfs_set_acl(tid_t tid, काष्ठा inode *inode, पूर्णांक type,
		       काष्ठा posix_acl *acl)
अणु
	अक्षर *ea_name;
	पूर्णांक rc;
	पूर्णांक size = 0;
	अक्षर *value = शून्य;

	चयन (type) अणु
	हाल ACL_TYPE_ACCESS:
		ea_name = XATTR_NAME_POSIX_ACL_ACCESS;
		अवरोध;
	हाल ACL_TYPE_DEFAULT:
		ea_name = XATTR_NAME_POSIX_ACL_DEFAULT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (acl) अणु
		size = posix_acl_xattr_size(acl->a_count);
		value = kदो_स्मृति(size, GFP_KERNEL);
		अगर (!value)
			वापस -ENOMEM;
		rc = posix_acl_to_xattr(&init_user_ns, acl, value, size);
		अगर (rc < 0)
			जाओ out;
	पूर्ण
	rc = __jfs_setxattr(tid, inode, ea_name, value, size, 0);
out:
	kमुक्त(value);

	अगर (!rc)
		set_cached_acl(inode, type, acl);

	वापस rc;
पूर्ण

पूर्णांक jfs_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		काष्ठा posix_acl *acl, पूर्णांक type)
अणु
	पूर्णांक rc;
	tid_t tid;
	पूर्णांक update_mode = 0;
	umode_t mode = inode->i_mode;

	tid = txBegin(inode->i_sb, 0);
	mutex_lock(&JFS_IP(inode)->commit_mutex);
	अगर (type == ACL_TYPE_ACCESS && acl) अणु
		rc = posix_acl_update_mode(&init_user_ns, inode, &mode, &acl);
		अगर (rc)
			जाओ end_tx;
		अगर (mode != inode->i_mode)
			update_mode = 1;
	पूर्ण
	rc = __jfs_set_acl(tid, inode, type, acl);
	अगर (!rc) अणु
		अगर (update_mode) अणु
			inode->i_mode = mode;
			inode->i_स_समय = current_समय(inode);
			mark_inode_dirty(inode);
		पूर्ण
		rc = txCommit(tid, 1, &inode, 0);
	पूर्ण
end_tx:
	txEnd(tid);
	mutex_unlock(&JFS_IP(inode)->commit_mutex);
	वापस rc;
पूर्ण

पूर्णांक jfs_init_acl(tid_t tid, काष्ठा inode *inode, काष्ठा inode *dir)
अणु
	काष्ठा posix_acl *शेष_acl, *acl;
	पूर्णांक rc = 0;

	rc = posix_acl_create(dir, &inode->i_mode, &शेष_acl, &acl);
	अगर (rc)
		वापस rc;

	अगर (शेष_acl) अणु
		rc = __jfs_set_acl(tid, inode, ACL_TYPE_DEFAULT, शेष_acl);
		posix_acl_release(शेष_acl);
	पूर्ण अन्यथा अणु
		inode->i_शेष_acl = शून्य;
	पूर्ण

	अगर (acl) अणु
		अगर (!rc)
			rc = __jfs_set_acl(tid, inode, ACL_TYPE_ACCESS, acl);
		posix_acl_release(acl);
	पूर्ण अन्यथा अणु
		inode->i_acl = शून्य;
	पूर्ण

	JFS_IP(inode)->mode2 = (JFS_IP(inode)->mode2 & 0xffff0000) |
			       inode->i_mode;

	वापस rc;
पूर्ण
