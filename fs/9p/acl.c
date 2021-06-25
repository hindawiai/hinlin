<शैली गुरु>
/*
 * Copyright IBM Corporation, 2010
 * Author Aneesh Kumar K.V <aneesh.kumar@linux.vnet.ibm.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <net/9p/9p.h>
#समावेश <net/9p/client.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश "xattr.h"
#समावेश "acl.h"
#समावेश "v9fs.h"
#समावेश "v9fs_vfs.h"
#समावेश "fid.h"

अटल काष्ठा posix_acl *__v9fs_get_acl(काष्ठा p9_fid *fid, अक्षर *name)
अणु
	sमाप_प्रकार size;
	व्योम *value = शून्य;
	काष्ठा posix_acl *acl = शून्य;

	size = v9fs_fid_xattr_get(fid, name, शून्य, 0);
	अगर (size > 0) अणु
		value = kzalloc(size, GFP_NOFS);
		अगर (!value)
			वापस ERR_PTR(-ENOMEM);
		size = v9fs_fid_xattr_get(fid, name, value, size);
		अगर (size > 0) अणु
			acl = posix_acl_from_xattr(&init_user_ns, value, size);
			अगर (IS_ERR(acl))
				जाओ err_out;
		पूर्ण
	पूर्ण अन्यथा अगर (size == -ENODATA || size == 0 ||
		   size == -ENOSYS || size == -EOPNOTSUPP) अणु
		acl = शून्य;
	पूर्ण अन्यथा
		acl = ERR_PTR(-EIO);

err_out:
	kमुक्त(value);
	वापस acl;
पूर्ण

पूर्णांक v9fs_get_acl(काष्ठा inode *inode, काष्ठा p9_fid *fid)
अणु
	पूर्णांक retval = 0;
	काष्ठा posix_acl *pacl, *dacl;
	काष्ठा v9fs_session_info *v9ses;

	v9ses = v9fs_inode2v9ses(inode);
	अगर (((v9ses->flags & V9FS_ACCESS_MASK) != V9FS_ACCESS_CLIENT) ||
			((v9ses->flags & V9FS_ACL_MASK) != V9FS_POSIX_ACL)) अणु
		set_cached_acl(inode, ACL_TYPE_DEFAULT, शून्य);
		set_cached_acl(inode, ACL_TYPE_ACCESS, शून्य);
		वापस 0;
	पूर्ण
	/* get the शेष/access acl values and cache them */
	dacl = __v9fs_get_acl(fid, XATTR_NAME_POSIX_ACL_DEFAULT);
	pacl = __v9fs_get_acl(fid, XATTR_NAME_POSIX_ACL_ACCESS);

	अगर (!IS_ERR(dacl) && !IS_ERR(pacl)) अणु
		set_cached_acl(inode, ACL_TYPE_DEFAULT, dacl);
		set_cached_acl(inode, ACL_TYPE_ACCESS, pacl);
	पूर्ण अन्यथा
		retval = -EIO;

	अगर (!IS_ERR(dacl))
		posix_acl_release(dacl);

	अगर (!IS_ERR(pacl))
		posix_acl_release(pacl);

	वापस retval;
पूर्ण

अटल काष्ठा posix_acl *v9fs_get_cached_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	काष्ठा posix_acl *acl;
	/*
	 * 9p Always cache the acl value when
	 * instantiating the inode (v9fs_inode_from_fid)
	 */
	acl = get_cached_acl(inode, type);
	BUG_ON(is_uncached_acl(acl));
	वापस acl;
पूर्ण

काष्ठा posix_acl *v9fs_iop_get_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	काष्ठा v9fs_session_info *v9ses;

	v9ses = v9fs_inode2v9ses(inode);
	अगर (((v9ses->flags & V9FS_ACCESS_MASK) != V9FS_ACCESS_CLIENT) ||
			((v9ses->flags & V9FS_ACL_MASK) != V9FS_POSIX_ACL)) अणु
		/*
		 * On access = client  and acl = on mode get the acl
		 * values from the server
		 */
		वापस शून्य;
	पूर्ण
	वापस v9fs_get_cached_acl(inode, type);

पूर्ण

अटल पूर्णांक v9fs_set_acl(काष्ठा p9_fid *fid, पूर्णांक type, काष्ठा posix_acl *acl)
अणु
	पूर्णांक retval;
	अक्षर *name;
	माप_प्रकार size;
	व्योम *buffer;
	अगर (!acl)
		वापस 0;

	/* Set a setxattr request to server */
	size = posix_acl_xattr_size(acl->a_count);
	buffer = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;
	retval = posix_acl_to_xattr(&init_user_ns, acl, buffer, size);
	अगर (retval < 0)
		जाओ err_मुक्त_out;
	चयन (type) अणु
	हाल ACL_TYPE_ACCESS:
		name = XATTR_NAME_POSIX_ACL_ACCESS;
		अवरोध;
	हाल ACL_TYPE_DEFAULT:
		name = XATTR_NAME_POSIX_ACL_DEFAULT;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	retval = v9fs_fid_xattr_set(fid, name, buffer, size, 0);
err_मुक्त_out:
	kमुक्त(buffer);
	वापस retval;
पूर्ण

पूर्णांक v9fs_acl_chmod(काष्ठा inode *inode, काष्ठा p9_fid *fid)
अणु
	पूर्णांक retval = 0;
	काष्ठा posix_acl *acl;

	अगर (S_ISLNK(inode->i_mode))
		वापस -EOPNOTSUPP;
	acl = v9fs_get_cached_acl(inode, ACL_TYPE_ACCESS);
	अगर (acl) अणु
		retval = __posix_acl_chmod(&acl, GFP_KERNEL, inode->i_mode);
		अगर (retval)
			वापस retval;
		set_cached_acl(inode, ACL_TYPE_ACCESS, acl);
		retval = v9fs_set_acl(fid, ACL_TYPE_ACCESS, acl);
		posix_acl_release(acl);
	पूर्ण
	वापस retval;
पूर्ण

पूर्णांक v9fs_set_create_acl(काष्ठा inode *inode, काष्ठा p9_fid *fid,
			काष्ठा posix_acl *dacl, काष्ठा posix_acl *acl)
अणु
	set_cached_acl(inode, ACL_TYPE_DEFAULT, dacl);
	set_cached_acl(inode, ACL_TYPE_ACCESS, acl);
	v9fs_set_acl(fid, ACL_TYPE_DEFAULT, dacl);
	v9fs_set_acl(fid, ACL_TYPE_ACCESS, acl);
	वापस 0;
पूर्ण

व्योम v9fs_put_acl(काष्ठा posix_acl *dacl,
		  काष्ठा posix_acl *acl)
अणु
	posix_acl_release(dacl);
	posix_acl_release(acl);
पूर्ण

पूर्णांक v9fs_acl_mode(काष्ठा inode *dir, umode_t *modep,
		  काष्ठा posix_acl **dpacl, काष्ठा posix_acl **pacl)
अणु
	पूर्णांक retval = 0;
	umode_t mode = *modep;
	काष्ठा posix_acl *acl = शून्य;

	अगर (!S_ISLNK(mode)) अणु
		acl = v9fs_get_cached_acl(dir, ACL_TYPE_DEFAULT);
		अगर (IS_ERR(acl))
			वापस PTR_ERR(acl);
		अगर (!acl)
			mode &= ~current_umask();
	पूर्ण
	अगर (acl) अणु
		अगर (S_ISसूची(mode))
			*dpacl = posix_acl_dup(acl);
		retval = __posix_acl_create(&acl, GFP_NOFS, &mode);
		अगर (retval < 0)
			वापस retval;
		अगर (retval > 0)
			*pacl = acl;
		अन्यथा
			posix_acl_release(acl);
	पूर्ण
	*modep  = mode;
	वापस 0;
पूर्ण

अटल पूर्णांक v9fs_xattr_get_acl(स्थिर काष्ठा xattr_handler *handler,
			      काष्ठा dentry *dentry, काष्ठा inode *inode,
			      स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा v9fs_session_info *v9ses;
	काष्ठा posix_acl *acl;
	पूर्णांक error;

	v9ses = v9fs_dentry2v9ses(dentry);
	/*
	 * We allow set/get/list of acl when access=client is not specअगरied
	 */
	अगर ((v9ses->flags & V9FS_ACCESS_MASK) != V9FS_ACCESS_CLIENT)
		वापस v9fs_xattr_get(dentry, handler->name, buffer, size);

	acl = v9fs_get_cached_acl(inode, handler->flags);
	अगर (IS_ERR(acl))
		वापस PTR_ERR(acl);
	अगर (acl == शून्य)
		वापस -ENODATA;
	error = posix_acl_to_xattr(&init_user_ns, acl, buffer, size);
	posix_acl_release(acl);

	वापस error;
पूर्ण

अटल पूर्णांक v9fs_xattr_set_acl(स्थिर काष्ठा xattr_handler *handler,
			      काष्ठा user_namespace *mnt_userns,
			      काष्ठा dentry *dentry, काष्ठा inode *inode,
			      स्थिर अक्षर *name, स्थिर व्योम *value,
			      माप_प्रकार size, पूर्णांक flags)
अणु
	पूर्णांक retval;
	काष्ठा posix_acl *acl;
	काष्ठा v9fs_session_info *v9ses;

	v9ses = v9fs_dentry2v9ses(dentry);
	/*
	 * set the attribute on the remote. Without even looking at the
	 * xattr value. We leave it to the server to validate
	 */
	अगर ((v9ses->flags & V9FS_ACCESS_MASK) != V9FS_ACCESS_CLIENT)
		वापस v9fs_xattr_set(dentry, handler->name, value, size,
				      flags);

	अगर (S_ISLNK(inode->i_mode))
		वापस -EOPNOTSUPP;
	अगर (!inode_owner_or_capable(&init_user_ns, inode))
		वापस -EPERM;
	अगर (value) अणु
		/* update the cached acl value */
		acl = posix_acl_from_xattr(&init_user_ns, value, size);
		अगर (IS_ERR(acl))
			वापस PTR_ERR(acl);
		अन्यथा अगर (acl) अणु
			retval = posix_acl_valid(inode->i_sb->s_user_ns, acl);
			अगर (retval)
				जाओ err_out;
		पूर्ण
	पूर्ण अन्यथा
		acl = शून्य;

	चयन (handler->flags) अणु
	हाल ACL_TYPE_ACCESS:
		अगर (acl) अणु
			काष्ठा iattr iattr = अणु 0 पूर्ण;
			काष्ठा posix_acl *old_acl = acl;

			retval = posix_acl_update_mode(&init_user_ns, inode,
						       &iattr.ia_mode, &acl);
			अगर (retval)
				जाओ err_out;
			अगर (!acl) अणु
				/*
				 * ACL can be represented
				 * by the mode bits. So करोn't
				 * update ACL.
				 */
				posix_acl_release(old_acl);
				value = शून्य;
				size = 0;
			पूर्ण
			iattr.ia_valid = ATTR_MODE;
			/* FIXME should we update स_समय ?
			 * What is the following setxattr update the
			 * mode ?
			 */
			v9fs_vfs_setattr_करोtl(&init_user_ns, dentry, &iattr);
		पूर्ण
		अवरोध;
	हाल ACL_TYPE_DEFAULT:
		अगर (!S_ISसूची(inode->i_mode)) अणु
			retval = acl ? -EINVAL : 0;
			जाओ err_out;
		पूर्ण
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	retval = v9fs_xattr_set(dentry, handler->name, value, size, flags);
	अगर (!retval)
		set_cached_acl(inode, handler->flags, acl);
err_out:
	posix_acl_release(acl);
	वापस retval;
पूर्ण

स्थिर काष्ठा xattr_handler v9fs_xattr_acl_access_handler = अणु
	.name	= XATTR_NAME_POSIX_ACL_ACCESS,
	.flags	= ACL_TYPE_ACCESS,
	.get	= v9fs_xattr_get_acl,
	.set	= v9fs_xattr_set_acl,
पूर्ण;

स्थिर काष्ठा xattr_handler v9fs_xattr_acl_शेष_handler = अणु
	.name	= XATTR_NAME_POSIX_ACL_DEFAULT,
	.flags	= ACL_TYPE_DEFAULT,
	.get	= v9fs_xattr_get_acl,
	.set	= v9fs_xattr_set_acl,
पूर्ण;
