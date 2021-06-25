<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2008 Christoph Hellwig.
 * Portions Copyright (C) 2000-2008 Silicon Graphics, Inc.
 */

#समावेश "xfs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_da_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_attr.h"
#समावेश "xfs_acl.h"
#समावेश "xfs_da_btree.h"

#समावेश <linux/posix_acl_xattr.h>


अटल पूर्णांक
xfs_xattr_get(स्थिर काष्ठा xattr_handler *handler, काष्ठा dentry *unused,
		काष्ठा inode *inode, स्थिर अक्षर *name, व्योम *value, माप_प्रकार size)
अणु
	काष्ठा xfs_da_args	args = अणु
		.dp		= XFS_I(inode),
		.attr_filter	= handler->flags,
		.name		= name,
		.namelen	= म_माप(name),
		.value		= value,
		.valuelen	= size,
	पूर्ण;
	पूर्णांक			error;

	error = xfs_attr_get(&args);
	अगर (error)
		वापस error;
	वापस args.valuelen;
पूर्ण

अटल पूर्णांक
xfs_xattr_set(स्थिर काष्ठा xattr_handler *handler,
	      काष्ठा user_namespace *mnt_userns, काष्ठा dentry *unused,
	      काष्ठा inode *inode, स्थिर अक्षर *name, स्थिर व्योम *value,
	      माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा xfs_da_args	args = अणु
		.dp		= XFS_I(inode),
		.attr_filter	= handler->flags,
		.attr_flags	= flags,
		.name		= name,
		.namelen	= म_माप(name),
		.value		= (व्योम *)value,
		.valuelen	= size,
	पूर्ण;
	पूर्णांक			error;

	error = xfs_attr_set(&args);
	अगर (!error && (handler->flags & XFS_ATTR_ROOT))
		xfs_क्रमget_acl(inode, name);
	वापस error;
पूर्ण

अटल स्थिर काष्ठा xattr_handler xfs_xattr_user_handler = अणु
	.prefix	= XATTR_USER_PREFIX,
	.flags	= 0, /* no flags implies user namespace */
	.get	= xfs_xattr_get,
	.set	= xfs_xattr_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler xfs_xattr_trusted_handler = अणु
	.prefix	= XATTR_TRUSTED_PREFIX,
	.flags	= XFS_ATTR_ROOT,
	.get	= xfs_xattr_get,
	.set	= xfs_xattr_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler xfs_xattr_security_handler = अणु
	.prefix	= XATTR_SECURITY_PREFIX,
	.flags	= XFS_ATTR_SECURE,
	.get	= xfs_xattr_get,
	.set	= xfs_xattr_set,
पूर्ण;

स्थिर काष्ठा xattr_handler *xfs_xattr_handlers[] = अणु
	&xfs_xattr_user_handler,
	&xfs_xattr_trusted_handler,
	&xfs_xattr_security_handler,
#अगर_घोषित CONFIG_XFS_POSIX_ACL
	&posix_acl_access_xattr_handler,
	&posix_acl_शेष_xattr_handler,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल व्योम
__xfs_xattr_put_listent(
	काष्ठा xfs_attr_list_context *context,
	अक्षर *prefix,
	पूर्णांक prefix_len,
	अचिन्हित अक्षर *name,
	पूर्णांक namelen)
अणु
	अक्षर *offset;
	पूर्णांक arraytop;

	अगर (context->count < 0 || context->seen_enough)
		वापस;

	अगर (!context->buffer)
		जाओ compute_size;

	arraytop = context->count + prefix_len + namelen + 1;
	अगर (arraytop > context->firstu) अणु
		context->count = -1;	/* insufficient space */
		context->seen_enough = 1;
		वापस;
	पूर्ण
	offset = context->buffer + context->count;
	म_नकलन(offset, prefix, prefix_len);
	offset += prefix_len;
	म_नकलन(offset, (अक्षर *)name, namelen);			/* real name */
	offset += namelen;
	*offset = '\0';

compute_size:
	context->count += prefix_len + namelen + 1;
	वापस;
पूर्ण

अटल व्योम
xfs_xattr_put_listent(
	काष्ठा xfs_attr_list_context *context,
	पूर्णांक		flags,
	अचिन्हित अक्षर	*name,
	पूर्णांक		namelen,
	पूर्णांक		valuelen)
अणु
	अक्षर *prefix;
	पूर्णांक prefix_len;

	ASSERT(context->count >= 0);

	अगर (flags & XFS_ATTR_ROOT) अणु
#अगर_घोषित CONFIG_XFS_POSIX_ACL
		अगर (namelen == SGI_ACL_खाता_SIZE &&
		    म_भेदन(name, SGI_ACL_खाता,
			    SGI_ACL_खाता_SIZE) == 0) अणु
			__xfs_xattr_put_listent(
					context, XATTR_SYSTEM_PREFIX,
					XATTR_SYSTEM_PREFIX_LEN,
					XATTR_POSIX_ACL_ACCESS,
					म_माप(XATTR_POSIX_ACL_ACCESS));
		पूर्ण अन्यथा अगर (namelen == SGI_ACL_DEFAULT_SIZE &&
			 म_भेदन(name, SGI_ACL_DEFAULT,
				 SGI_ACL_DEFAULT_SIZE) == 0) अणु
			__xfs_xattr_put_listent(
					context, XATTR_SYSTEM_PREFIX,
					XATTR_SYSTEM_PREFIX_LEN,
					XATTR_POSIX_ACL_DEFAULT,
					म_माप(XATTR_POSIX_ACL_DEFAULT));
		पूर्ण
#पूर्ण_अगर

		/*
		 * Only show root namespace entries अगर we are actually allowed to
		 * see them.
		 */
		अगर (!capable(CAP_SYS_ADMIN))
			वापस;

		prefix = XATTR_TRUSTED_PREFIX;
		prefix_len = XATTR_TRUSTED_PREFIX_LEN;
	पूर्ण अन्यथा अगर (flags & XFS_ATTR_SECURE) अणु
		prefix = XATTR_SECURITY_PREFIX;
		prefix_len = XATTR_SECURITY_PREFIX_LEN;
	पूर्ण अन्यथा अणु
		prefix = XATTR_USER_PREFIX;
		prefix_len = XATTR_USER_PREFIX_LEN;
	पूर्ण

	__xfs_xattr_put_listent(context, prefix, prefix_len, name,
				namelen);
	वापस;
पूर्ण

sमाप_प्रकार
xfs_vn_listxattr(
	काष्ठा dentry	*dentry,
	अक्षर		*data,
	माप_प्रकार		size)
अणु
	काष्ठा xfs_attr_list_context context;
	काष्ठा inode	*inode = d_inode(dentry);
	पूर्णांक		error;

	/*
	 * First पढ़ो the regular on-disk attributes.
	 */
	स_रखो(&context, 0, माप(context));
	context.dp = XFS_I(inode);
	context.resynch = 1;
	context.buffer = size ? data : शून्य;
	context.bufsize = size;
	context.firstu = context.bufsize;
	context.put_listent = xfs_xattr_put_listent;

	error = xfs_attr_list(&context);
	अगर (error)
		वापस error;
	अगर (context.count < 0)
		वापस -दुस्फल;

	वापस context.count;
पूर्ण
