<शैली गुरु>
/*
 * FUSE: Fileप्रणाली in Userspace
 * Copyright (C) 2001-2016  Miklos Szeredi <miklos@szeredi.hu>
 *
 * This program can be distributed under the terms of the GNU GPL.
 * See the file COPYING.
 */

#समावेश "fuse_i.h"

#समावेश <linux/xattr.h>
#समावेश <linux/posix_acl_xattr.h>

पूर्णांक fuse_setxattr(काष्ठा inode *inode, स्थिर अक्षर *name, स्थिर व्योम *value,
		  माप_प्रकार size, पूर्णांक flags, अचिन्हित पूर्णांक extra_flags)
अणु
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	FUSE_ARGS(args);
	काष्ठा fuse_setxattr_in inarg;
	पूर्णांक err;

	अगर (fm->fc->no_setxattr)
		वापस -EOPNOTSUPP;

	स_रखो(&inarg, 0, माप(inarg));
	inarg.size = size;
	inarg.flags = flags;
	inarg.setxattr_flags = extra_flags;

	args.opcode = FUSE_SETXATTR;
	args.nodeid = get_node_id(inode);
	args.in_numargs = 3;
	args.in_args[0].size = fm->fc->setxattr_ext ?
		माप(inarg) : FUSE_COMPAT_SETXATTR_IN_SIZE;
	args.in_args[0].value = &inarg;
	args.in_args[1].size = म_माप(name) + 1;
	args.in_args[1].value = name;
	args.in_args[2].size = size;
	args.in_args[2].value = value;
	err = fuse_simple_request(fm, &args);
	अगर (err == -ENOSYS) अणु
		fm->fc->no_setxattr = 1;
		err = -EOPNOTSUPP;
	पूर्ण
	अगर (!err) अणु
		fuse_invalidate_attr(inode);
		fuse_update_स_समय(inode);
	पूर्ण
	वापस err;
पूर्ण

sमाप_प्रकार fuse_getxattr(काष्ठा inode *inode, स्थिर अक्षर *name, व्योम *value,
		      माप_प्रकार size)
अणु
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	FUSE_ARGS(args);
	काष्ठा fuse_getxattr_in inarg;
	काष्ठा fuse_getxattr_out outarg;
	sमाप_प्रकार ret;

	अगर (fm->fc->no_getxattr)
		वापस -EOPNOTSUPP;

	स_रखो(&inarg, 0, माप(inarg));
	inarg.size = size;
	args.opcode = FUSE_GETXATTR;
	args.nodeid = get_node_id(inode);
	args.in_numargs = 2;
	args.in_args[0].size = माप(inarg);
	args.in_args[0].value = &inarg;
	args.in_args[1].size = म_माप(name) + 1;
	args.in_args[1].value = name;
	/* This is really two dअगरferent operations rolled पूर्णांकo one */
	args.out_numargs = 1;
	अगर (size) अणु
		args.out_argvar = true;
		args.out_args[0].size = size;
		args.out_args[0].value = value;
	पूर्ण अन्यथा अणु
		args.out_args[0].size = माप(outarg);
		args.out_args[0].value = &outarg;
	पूर्ण
	ret = fuse_simple_request(fm, &args);
	अगर (!ret && !size)
		ret = min_t(sमाप_प्रकार, outarg.size, XATTR_SIZE_MAX);
	अगर (ret == -ENOSYS) अणु
		fm->fc->no_getxattr = 1;
		ret = -EOPNOTSUPP;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक fuse_verअगरy_xattr_list(अक्षर *list, माप_प्रकार size)
अणु
	माप_प्रकार origsize = size;

	जबतक (size) अणु
		माप_प्रकार thislen = strnlen(list, size);

		अगर (!thislen || thislen == size)
			वापस -EIO;

		size -= thislen + 1;
		list += thislen + 1;
	पूर्ण

	वापस origsize;
पूर्ण

sमाप_प्रकार fuse_listxattr(काष्ठा dentry *entry, अक्षर *list, माप_प्रकार size)
अणु
	काष्ठा inode *inode = d_inode(entry);
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	FUSE_ARGS(args);
	काष्ठा fuse_getxattr_in inarg;
	काष्ठा fuse_getxattr_out outarg;
	sमाप_प्रकार ret;

	अगर (fuse_is_bad(inode))
		वापस -EIO;

	अगर (!fuse_allow_current_process(fm->fc))
		वापस -EACCES;

	अगर (fm->fc->no_listxattr)
		वापस -EOPNOTSUPP;

	स_रखो(&inarg, 0, माप(inarg));
	inarg.size = size;
	args.opcode = FUSE_LISTXATTR;
	args.nodeid = get_node_id(inode);
	args.in_numargs = 1;
	args.in_args[0].size = माप(inarg);
	args.in_args[0].value = &inarg;
	/* This is really two dअगरferent operations rolled पूर्णांकo one */
	args.out_numargs = 1;
	अगर (size) अणु
		args.out_argvar = true;
		args.out_args[0].size = size;
		args.out_args[0].value = list;
	पूर्ण अन्यथा अणु
		args.out_args[0].size = माप(outarg);
		args.out_args[0].value = &outarg;
	पूर्ण
	ret = fuse_simple_request(fm, &args);
	अगर (!ret && !size)
		ret = min_t(sमाप_प्रकार, outarg.size, XATTR_LIST_MAX);
	अगर (ret > 0 && size)
		ret = fuse_verअगरy_xattr_list(list, ret);
	अगर (ret == -ENOSYS) अणु
		fm->fc->no_listxattr = 1;
		ret = -EOPNOTSUPP;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक fuse_हटाओxattr(काष्ठा inode *inode, स्थिर अक्षर *name)
अणु
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	FUSE_ARGS(args);
	पूर्णांक err;

	अगर (fm->fc->no_हटाओxattr)
		वापस -EOPNOTSUPP;

	args.opcode = FUSE_REMOVEXATTR;
	args.nodeid = get_node_id(inode);
	args.in_numargs = 1;
	args.in_args[0].size = म_माप(name) + 1;
	args.in_args[0].value = name;
	err = fuse_simple_request(fm, &args);
	अगर (err == -ENOSYS) अणु
		fm->fc->no_हटाओxattr = 1;
		err = -EOPNOTSUPP;
	पूर्ण
	अगर (!err) अणु
		fuse_invalidate_attr(inode);
		fuse_update_स_समय(inode);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक fuse_xattr_get(स्थिर काष्ठा xattr_handler *handler,
			 काष्ठा dentry *dentry, काष्ठा inode *inode,
			 स्थिर अक्षर *name, व्योम *value, माप_प्रकार size)
अणु
	अगर (fuse_is_bad(inode))
		वापस -EIO;

	वापस fuse_getxattr(inode, name, value, size);
पूर्ण

अटल पूर्णांक fuse_xattr_set(स्थिर काष्ठा xattr_handler *handler,
			  काष्ठा user_namespace *mnt_userns,
			  काष्ठा dentry *dentry, काष्ठा inode *inode,
			  स्थिर अक्षर *name, स्थिर व्योम *value, माप_प्रकार size,
			  पूर्णांक flags)
अणु
	अगर (fuse_is_bad(inode))
		वापस -EIO;

	अगर (!value)
		वापस fuse_हटाओxattr(inode, name);

	वापस fuse_setxattr(inode, name, value, size, flags, 0);
पूर्ण

अटल bool no_xattr_list(काष्ठा dentry *dentry)
अणु
	वापस false;
पूर्ण

अटल पूर्णांक no_xattr_get(स्थिर काष्ठा xattr_handler *handler,
			काष्ठा dentry *dentry, काष्ठा inode *inode,
			स्थिर अक्षर *name, व्योम *value, माप_प्रकार size)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक no_xattr_set(स्थिर काष्ठा xattr_handler *handler,
			काष्ठा user_namespace *mnt_userns,
			काष्ठा dentry *dentry, काष्ठा inode *nodee,
			स्थिर अक्षर *name, स्थिर व्योम *value,
			माप_प्रकार size, पूर्णांक flags)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा xattr_handler fuse_xattr_handler = अणु
	.prefix = "",
	.get    = fuse_xattr_get,
	.set    = fuse_xattr_set,
पूर्ण;

स्थिर काष्ठा xattr_handler *fuse_xattr_handlers[] = अणु
	&fuse_xattr_handler,
	शून्य
पूर्ण;

स्थिर काष्ठा xattr_handler *fuse_acl_xattr_handlers[] = अणु
	&posix_acl_access_xattr_handler,
	&posix_acl_शेष_xattr_handler,
	&fuse_xattr_handler,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा xattr_handler fuse_no_acl_access_xattr_handler = अणु
	.name  = XATTR_NAME_POSIX_ACL_ACCESS,
	.flags = ACL_TYPE_ACCESS,
	.list  = no_xattr_list,
	.get   = no_xattr_get,
	.set   = no_xattr_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler fuse_no_acl_शेष_xattr_handler = अणु
	.name  = XATTR_NAME_POSIX_ACL_DEFAULT,
	.flags = ACL_TYPE_ACCESS,
	.list  = no_xattr_list,
	.get   = no_xattr_get,
	.set   = no_xattr_set,
पूर्ण;

स्थिर काष्ठा xattr_handler *fuse_no_acl_xattr_handlers[] = अणु
	&fuse_no_acl_access_xattr_handler,
	&fuse_no_acl_शेष_xattr_handler,
	&fuse_xattr_handler,
	शून्य
पूर्ण;
