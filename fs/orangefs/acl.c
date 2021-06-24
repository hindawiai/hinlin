<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) 2001 Clemson University and The University of Chicago
 *
 * See COPYING in top-level directory.
 */

#समावेश "protocol.h"
#समावेश "orangefs-kernel.h"
#समावेश "orangefs-bufmap.h"
#समावेश <linux/posix_acl_xattr.h>

काष्ठा posix_acl *orangefs_get_acl(काष्ठा inode *inode, पूर्णांक type)
अणु
	काष्ठा posix_acl *acl;
	पूर्णांक ret;
	अक्षर *key = शून्य, *value = शून्य;

	चयन (type) अणु
	हाल ACL_TYPE_ACCESS:
		key = XATTR_NAME_POSIX_ACL_ACCESS;
		अवरोध;
	हाल ACL_TYPE_DEFAULT:
		key = XATTR_NAME_POSIX_ACL_DEFAULT;
		अवरोध;
	शेष:
		gossip_err("orangefs_get_acl: bogus value of type %d\n", type);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	/*
	 * Rather than incurring a network call just to determine the exact
	 * length of the attribute, I just allocate a max length to save on
	 * the network call. Conceivably, we could pass शून्य to
	 * orangefs_inode_getxattr() to probe the length of the value, but
	 * I करोn't करो that क्रम now.
	 */
	value = kदो_स्मृति(ORANGEFS_MAX_XATTR_VALUELEN, GFP_KERNEL);
	अगर (!value)
		वापस ERR_PTR(-ENOMEM);

	gossip_debug(GOSSIP_ACL_DEBUG,
		     "inode %pU, key %s, type %d\n",
		     get_khandle_from_ino(inode),
		     key,
		     type);
	ret = orangefs_inode_getxattr(inode, key, value,
				      ORANGEFS_MAX_XATTR_VALUELEN);
	/* अगर the key exists, convert it to an in-memory rep */
	अगर (ret > 0) अणु
		acl = posix_acl_from_xattr(&init_user_ns, value, ret);
	पूर्ण अन्यथा अगर (ret == -ENODATA || ret == -ENOSYS) अणु
		acl = शून्य;
	पूर्ण अन्यथा अणु
		gossip_err("inode %pU retrieving acl's failed with error %d\n",
			   get_khandle_from_ino(inode),
			   ret);
		acl = ERR_PTR(ret);
	पूर्ण
	/* kमुक्त(शून्य) is safe, so करोn't worry अगर value ever got used */
	kमुक्त(value);
	वापस acl;
पूर्ण

अटल पूर्णांक __orangefs_set_acl(काष्ठा inode *inode, काष्ठा posix_acl *acl,
			      पूर्णांक type)
अणु
	पूर्णांक error = 0;
	व्योम *value = शून्य;
	माप_प्रकार size = 0;
	स्थिर अक्षर *name = शून्य;

	चयन (type) अणु
	हाल ACL_TYPE_ACCESS:
		name = XATTR_NAME_POSIX_ACL_ACCESS;
		अवरोध;
	हाल ACL_TYPE_DEFAULT:
		name = XATTR_NAME_POSIX_ACL_DEFAULT;
		अवरोध;
	शेष:
		gossip_err("%s: invalid type %d!\n", __func__, type);
		वापस -EINVAL;
	पूर्ण

	gossip_debug(GOSSIP_ACL_DEBUG,
		     "%s: inode %pU, key %s type %d\n",
		     __func__, get_khandle_from_ino(inode),
		     name,
		     type);

	अगर (acl) अणु
		size = posix_acl_xattr_size(acl->a_count);
		value = kदो_स्मृति(size, GFP_KERNEL);
		अगर (!value)
			वापस -ENOMEM;

		error = posix_acl_to_xattr(&init_user_ns, acl, value, size);
		अगर (error < 0)
			जाओ out;
	पूर्ण

	gossip_debug(GOSSIP_ACL_DEBUG,
		     "%s: name %s, value %p, size %zd, acl %p\n",
		     __func__, name, value, size, acl);
	/*
	 * Go ahead and set the extended attribute now. NOTE: Suppose acl
	 * was शून्य, then value will be शून्य and size will be 0 and that
	 * will xlate to a हटाओxattr. However, we करोn't want हटाओxattr
	 * complain अगर attributes करोes not exist.
	 */
	error = orangefs_inode_setxattr(inode, name, value, size, 0);

out:
	kमुक्त(value);
	अगर (!error)
		set_cached_acl(inode, type, acl);
	वापस error;
पूर्ण

पूर्णांक orangefs_set_acl(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		     काष्ठा posix_acl *acl, पूर्णांक type)
अणु
	पूर्णांक error;
	काष्ठा iattr iattr;
	पूर्णांक rc;

	स_रखो(&iattr, 0, माप iattr);

	अगर (type == ACL_TYPE_ACCESS && acl) अणु
		/*
		 * posix_acl_update_mode checks to see अगर the permissions
		 * described by the ACL can be encoded पूर्णांकo the
		 * object's mode. If so, it sets "acl" to शून्य
		 * and "mode" to the new desired value. It is up to
		 * us to propagate the new mode back to the server...
		 */
		error = posix_acl_update_mode(&init_user_ns, inode,
					      &iattr.ia_mode, &acl);
		अगर (error) अणु
			gossip_err("%s: posix_acl_update_mode err: %d\n",
				   __func__,
				   error);
			वापस error;
		पूर्ण

		अगर (inode->i_mode != iattr.ia_mode)
			iattr.ia_valid = ATTR_MODE;

	पूर्ण

	rc = __orangefs_set_acl(inode, acl, type);

	अगर (!rc && (iattr.ia_valid == ATTR_MODE))
		rc = __orangefs_setattr(inode, &iattr);

	वापस rc;
पूर्ण

पूर्णांक orangefs_init_acl(काष्ठा inode *inode, काष्ठा inode *dir)
अणु
	काष्ठा posix_acl *शेष_acl, *acl;
	umode_t mode = inode->i_mode;
	काष्ठा iattr iattr;
	पूर्णांक error = 0;

	error = posix_acl_create(dir, &mode, &शेष_acl, &acl);
	अगर (error)
		वापस error;

	अगर (शेष_acl) अणु
		error = __orangefs_set_acl(inode, शेष_acl,
					   ACL_TYPE_DEFAULT);
		posix_acl_release(शेष_acl);
	पूर्ण अन्यथा अणु
		inode->i_शेष_acl = शून्य;
	पूर्ण

	अगर (acl) अणु
		अगर (!error)
			error = __orangefs_set_acl(inode, acl, ACL_TYPE_ACCESS);
		posix_acl_release(acl);
	पूर्ण अन्यथा अणु
		inode->i_acl = शून्य;
	पूर्ण

	/* If mode of the inode was changed, then करो a क्रमcible ->setattr */
	अगर (mode != inode->i_mode) अणु
		स_रखो(&iattr, 0, माप iattr);
		inode->i_mode = mode;
		iattr.ia_mode = mode;
		iattr.ia_valid |= ATTR_MODE;
		__orangefs_setattr(inode, &iattr);
	पूर्ण

	वापस error;
पूर्ण
