<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2008, Christoph Hellwig
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_attr.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_error.h"
#समावेश "xfs_acl.h"
#समावेश "xfs_da_format.h"
#समावेश "xfs_da_btree.h"
#समावेश "xfs_trans.h"

#समावेश <linux/posix_acl_xattr.h>

/*
 * Locking scheme:
 *  - all ACL updates are रक्षित by inode->i_mutex, which is taken beक्रमe
 *    calling पूर्णांकo this file.
 */

STATIC काष्ठा posix_acl *
xfs_acl_from_disk(
	काष्ठा xfs_mount	*mp,
	स्थिर काष्ठा xfs_acl	*aclp,
	पूर्णांक			len,
	पूर्णांक			max_entries)
अणु
	काष्ठा posix_acl_entry *acl_e;
	काष्ठा posix_acl *acl;
	स्थिर काष्ठा xfs_acl_entry *ace;
	अचिन्हित पूर्णांक count, i;

	अगर (len < माप(*aclp)) अणु
		XFS_CORRUPTION_ERROR(__func__, XFS_ERRLEVEL_LOW, mp, aclp,
				len);
		वापस ERR_PTR(-EFSCORRUPTED);
	पूर्ण

	count = be32_to_cpu(aclp->acl_cnt);
	अगर (count > max_entries || XFS_ACL_SIZE(count) != len) अणु
		XFS_CORRUPTION_ERROR(__func__, XFS_ERRLEVEL_LOW, mp, aclp,
				len);
		वापस ERR_PTR(-EFSCORRUPTED);
	पूर्ण

	acl = posix_acl_alloc(count, GFP_KERNEL);
	अगर (!acl)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < count; i++) अणु
		acl_e = &acl->a_entries[i];
		ace = &aclp->acl_entry[i];

		/*
		 * The tag is 32 bits on disk and 16 bits in core.
		 *
		 * Because every access to it goes through the core
		 * क्रमmat first this is not a problem.
		 */
		acl_e->e_tag = be32_to_cpu(ace->ae_tag);
		acl_e->e_perm = be16_to_cpu(ace->ae_perm);

		चयन (acl_e->e_tag) अणु
		हाल ACL_USER:
			acl_e->e_uid = make_kuid(&init_user_ns,
						 be32_to_cpu(ace->ae_id));
			अवरोध;
		हाल ACL_GROUP:
			acl_e->e_gid = make_kgid(&init_user_ns,
						 be32_to_cpu(ace->ae_id));
			अवरोध;
		हाल ACL_USER_OBJ:
		हाल ACL_GROUP_OBJ:
		हाल ACL_MASK:
		हाल ACL_OTHER:
			अवरोध;
		शेष:
			जाओ fail;
		पूर्ण
	पूर्ण
	वापस acl;

fail:
	posix_acl_release(acl);
	वापस ERR_PTR(-EINVAL);
पूर्ण

STATIC व्योम
xfs_acl_to_disk(काष्ठा xfs_acl *aclp, स्थिर काष्ठा posix_acl *acl)
अणु
	स्थिर काष्ठा posix_acl_entry *acl_e;
	काष्ठा xfs_acl_entry *ace;
	पूर्णांक i;

	aclp->acl_cnt = cpu_to_be32(acl->a_count);
	क्रम (i = 0; i < acl->a_count; i++) अणु
		ace = &aclp->acl_entry[i];
		acl_e = &acl->a_entries[i];

		ace->ae_tag = cpu_to_be32(acl_e->e_tag);
		चयन (acl_e->e_tag) अणु
		हाल ACL_USER:
			ace->ae_id = cpu_to_be32(
					from_kuid(&init_user_ns, acl_e->e_uid));
			अवरोध;
		हाल ACL_GROUP:
			ace->ae_id = cpu_to_be32(
					from_kgid(&init_user_ns, acl_e->e_gid));
			अवरोध;
		शेष:
			ace->ae_id = cpu_to_be32(ACL_UNDEFINED_ID);
			अवरोध;
		पूर्ण

		ace->ae_perm = cpu_to_be16(acl_e->e_perm);
	पूर्ण
पूर्ण

काष्ठा posix_acl *
xfs_get_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा posix_acl	*acl = शून्य;
	काष्ठा xfs_da_args	args = अणु
		.dp		= ip,
		.attr_filter	= XFS_ATTR_ROOT,
		.valuelen	= XFS_ACL_MAX_SIZE(mp),
	पूर्ण;
	पूर्णांक			error;

	trace_xfs_get_acl(ip);

	चयन (type) अणु
	हाल ACL_TYPE_ACCESS:
		args.name = SGI_ACL_खाता;
		अवरोध;
	हाल ACL_TYPE_DEFAULT:
		args.name = SGI_ACL_DEFAULT;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	args.namelen = म_माप(args.name);

	/*
	 * If the attribute करोesn't exist make sure we have a negative cache
	 * entry, क्रम any other error assume it is transient.
	 */
	error = xfs_attr_get(&args);
	अगर (!error) अणु
		acl = xfs_acl_from_disk(mp, args.value, args.valuelen,
					XFS_ACL_MAX_ENTRIES(mp));
	पूर्ण अन्यथा अगर (error != -ENOATTR) अणु
		acl = ERR_PTR(error);
	पूर्ण

	kmem_मुक्त(args.value);
	वापस acl;
पूर्ण

पूर्णांक
__xfs_set_acl(काष्ठा inode *inode, काष्ठा posix_acl *acl, पूर्णांक type)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	काष्ठा xfs_da_args	args = अणु
		.dp		= ip,
		.attr_filter	= XFS_ATTR_ROOT,
	पूर्ण;
	पूर्णांक			error;

	चयन (type) अणु
	हाल ACL_TYPE_ACCESS:
		args.name = SGI_ACL_खाता;
		अवरोध;
	हाल ACL_TYPE_DEFAULT:
		अगर (!S_ISसूची(inode->i_mode))
			वापस acl ? -EACCES : 0;
		args.name = SGI_ACL_DEFAULT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	args.namelen = म_माप(args.name);

	अगर (acl) अणु
		args.valuelen = XFS_ACL_SIZE(acl->a_count);
		args.value = kvzalloc(args.valuelen, GFP_KERNEL);
		अगर (!args.value)
			वापस -ENOMEM;
		xfs_acl_to_disk(args.value, acl);
	पूर्ण

	error = xfs_attr_set(&args);
	kmem_मुक्त(args.value);

	/*
	 * If the attribute didn't exist to start with that's fine.
	 */
	अगर (!acl && error == -ENOATTR)
		error = 0;
	अगर (!error)
		set_cached_acl(inode, type, acl);
	वापस error;
पूर्ण

अटल पूर्णांक
xfs_acl_set_mode(
	काष्ठा inode		*inode,
	umode_t			mode)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_trans	*tp;
	पूर्णांक			error;

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_ichange, 0, 0, 0, &tp);
	अगर (error)
		वापस error;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, XFS_ILOCK_EXCL);
	inode->i_mode = mode;
	inode->i_स_समय = current_समय(inode);
	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);

	अगर (mp->m_flags & XFS_MOUNT_WSYNC)
		xfs_trans_set_sync(tp);
	वापस xfs_trans_commit(tp);
पूर्ण

पूर्णांक
xfs_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
	    काष्ठा posix_acl *acl, पूर्णांक type)
अणु
	umode_t mode;
	bool set_mode = false;
	पूर्णांक error = 0;

	अगर (!acl)
		जाओ set_acl;

	error = -E2BIG;
	अगर (acl->a_count > XFS_ACL_MAX_ENTRIES(XFS_M(inode->i_sb)))
		वापस error;

	अगर (type == ACL_TYPE_ACCESS) अणु
		error = posix_acl_update_mode(mnt_userns, inode, &mode, &acl);
		अगर (error)
			वापस error;
		set_mode = true;
	पूर्ण

 set_acl:
	/*
	 * We set the mode after successfully updating the ACL xattr because the
	 * xattr update can fail at ENOSPC and we करोn't want to change the mode
	 * अगर the ACL update hasn't been applied.
	 */
	error =  __xfs_set_acl(inode, acl, type);
	अगर (!error && set_mode && mode != inode->i_mode)
		error = xfs_acl_set_mode(inode, mode);
	वापस error;
पूर्ण

/*
 * Invalidate any cached ACLs अगर the user has bypassed the ACL पूर्णांकerface.
 * We करोn't validate the content whatsoever so it is caller responsibility to
 * provide data in valid क्रमmat and ensure i_mode is consistent.
 */
व्योम
xfs_क्रमget_acl(
	काष्ठा inode		*inode,
	स्थिर अक्षर		*name)
अणु
	अगर (!म_भेद(name, SGI_ACL_खाता))
		क्रमget_cached_acl(inode, ACL_TYPE_ACCESS);
	अन्यथा अगर (!म_भेद(name, SGI_ACL_DEFAULT))
		क्रमget_cached_acl(inode, ACL_TYPE_DEFAULT);
पूर्ण
