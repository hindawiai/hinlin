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
#समावेश <linux/sched.h>
#समावेश <linux/uपन.स>
#समावेश <net/9p/9p.h>
#समावेश <net/9p/client.h>

#समावेश "fid.h"
#समावेश "xattr.h"

sमाप_प्रकार v9fs_fid_xattr_get(काष्ठा p9_fid *fid, स्थिर अक्षर *name,
			   व्योम *buffer, माप_प्रकार buffer_size)
अणु
	sमाप_प्रकार retval;
	u64 attr_size;
	काष्ठा p9_fid *attr_fid;
	काष्ठा kvec kvec = अणु.iov_base = buffer, .iov_len = buffer_sizeपूर्ण;
	काष्ठा iov_iter to;
	पूर्णांक err;

	iov_iter_kvec(&to, READ, &kvec, 1, buffer_size);

	attr_fid = p9_client_xattrwalk(fid, name, &attr_size);
	अगर (IS_ERR(attr_fid)) अणु
		retval = PTR_ERR(attr_fid);
		p9_debug(P9_DEBUG_VFS, "p9_client_attrwalk failed %zd\n",
			 retval);
		वापस retval;
	पूर्ण
	अगर (attr_size > buffer_size) अणु
		अगर (!buffer_size) /* request to get the attr_size */
			retval = attr_size;
		अन्यथा
			retval = -दुस्फल;
	पूर्ण अन्यथा अणु
		iov_iter_truncate(&to, attr_size);
		retval = p9_client_पढ़ो(attr_fid, 0, &to, &err);
		अगर (err)
			retval = err;
	पूर्ण
	p9_client_clunk(attr_fid);
	वापस retval;
पूर्ण


/*
 * v9fs_xattr_get()
 *
 * Copy an extended attribute पूर्णांकo the buffer
 * provided, or compute the buffer size required.
 * Buffer is शून्य to compute the size of the buffer required.
 *
 * Returns a negative error number on failure, or the number of bytes
 * used / required on success.
 */
sमाप_प्रकार v9fs_xattr_get(काष्ठा dentry *dentry, स्थिर अक्षर *name,
		       व्योम *buffer, माप_प्रकार buffer_size)
अणु
	काष्ठा p9_fid *fid;
	पूर्णांक ret;

	p9_debug(P9_DEBUG_VFS, "name = %s value_len = %zu\n",
		 name, buffer_size);
	fid = v9fs_fid_lookup(dentry);
	अगर (IS_ERR(fid))
		वापस PTR_ERR(fid);
	ret = v9fs_fid_xattr_get(fid, name, buffer, buffer_size);
	p9_client_clunk(fid);

	वापस ret;
पूर्ण

/*
 * v9fs_xattr_set()
 *
 * Create, replace or हटाओ an extended attribute क्रम this inode. Buffer
 * is शून्य to हटाओ an existing extended attribute, and non-शून्य to
 * either replace an existing extended attribute, or create a new extended
 * attribute. The flags XATTR_REPLACE and XATTR_CREATE
 * specअगरy that an extended attribute must exist and must not exist
 * previous to the call, respectively.
 *
 * Returns 0, or a negative error number on failure.
 */
पूर्णांक v9fs_xattr_set(काष्ठा dentry *dentry, स्थिर अक्षर *name,
		   स्थिर व्योम *value, माप_प्रकार value_len, पूर्णांक flags)
अणु
	पूर्णांक ret;
	काष्ठा p9_fid *fid;

	fid  = v9fs_fid_lookup(dentry);
	अगर (IS_ERR(fid))
		वापस PTR_ERR(fid);
	ret = v9fs_fid_xattr_set(fid, name, value, value_len, flags);
	p9_client_clunk(fid);
	वापस ret;
पूर्ण

पूर्णांक v9fs_fid_xattr_set(काष्ठा p9_fid *fid, स्थिर अक्षर *name,
		   स्थिर व्योम *value, माप_प्रकार value_len, पूर्णांक flags)
अणु
	काष्ठा kvec kvec = अणु.iov_base = (व्योम *)value, .iov_len = value_lenपूर्ण;
	काष्ठा iov_iter from;
	पूर्णांक retval, err;

	iov_iter_kvec(&from, WRITE, &kvec, 1, value_len);

	p9_debug(P9_DEBUG_VFS, "name = %s value_len = %zu flags = %d\n",
		 name, value_len, flags);

	/* Clone it */
	fid = clone_fid(fid);
	अगर (IS_ERR(fid))
		वापस PTR_ERR(fid);

	/*
	 * On success fid poपूर्णांकs to xattr
	 */
	retval = p9_client_xattrcreate(fid, name, value_len, flags);
	अगर (retval < 0)
		p9_debug(P9_DEBUG_VFS, "p9_client_xattrcreate failed %d\n",
			 retval);
	अन्यथा
		p9_client_ग_लिखो(fid, 0, &from, &retval);
	err = p9_client_clunk(fid);
	अगर (!retval && err)
		retval = err;
	वापस retval;
पूर्ण

sमाप_प्रकार v9fs_listxattr(काष्ठा dentry *dentry, अक्षर *buffer, माप_प्रकार buffer_size)
अणु
	वापस v9fs_xattr_get(dentry, शून्य, buffer, buffer_size);
पूर्ण

अटल पूर्णांक v9fs_xattr_handler_get(स्थिर काष्ठा xattr_handler *handler,
				  काष्ठा dentry *dentry, काष्ठा inode *inode,
				  स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	स्थिर अक्षर *full_name = xattr_full_name(handler, name);

	वापस v9fs_xattr_get(dentry, full_name, buffer, size);
पूर्ण

अटल पूर्णांक v9fs_xattr_handler_set(स्थिर काष्ठा xattr_handler *handler,
				  काष्ठा user_namespace *mnt_userns,
				  काष्ठा dentry *dentry, काष्ठा inode *inode,
				  स्थिर अक्षर *name, स्थिर व्योम *value,
				  माप_प्रकार size, पूर्णांक flags)
अणु
	स्थिर अक्षर *full_name = xattr_full_name(handler, name);

	वापस v9fs_xattr_set(dentry, full_name, value, size, flags);
पूर्ण

अटल काष्ठा xattr_handler v9fs_xattr_user_handler = अणु
	.prefix	= XATTR_USER_PREFIX,
	.get	= v9fs_xattr_handler_get,
	.set	= v9fs_xattr_handler_set,
पूर्ण;

अटल काष्ठा xattr_handler v9fs_xattr_trusted_handler = अणु
	.prefix	= XATTR_TRUSTED_PREFIX,
	.get	= v9fs_xattr_handler_get,
	.set	= v9fs_xattr_handler_set,
पूर्ण;

#अगर_घोषित CONFIG_9P_FS_SECURITY
अटल काष्ठा xattr_handler v9fs_xattr_security_handler = अणु
	.prefix	= XATTR_SECURITY_PREFIX,
	.get	= v9fs_xattr_handler_get,
	.set	= v9fs_xattr_handler_set,
पूर्ण;
#पूर्ण_अगर

स्थिर काष्ठा xattr_handler *v9fs_xattr_handlers[] = अणु
	&v9fs_xattr_user_handler,
	&v9fs_xattr_trusted_handler,
#अगर_घोषित CONFIG_9P_FS_POSIX_ACL
	&v9fs_xattr_acl_access_handler,
	&v9fs_xattr_acl_शेष_handler,
#पूर्ण_अगर
#अगर_घोषित CONFIG_9P_FS_SECURITY
	&v9fs_xattr_security_handler,
#पूर्ण_अगर
	शून्य
पूर्ण;
