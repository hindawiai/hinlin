<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/sysv/file.c
 *
 *  minix/file.c
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  coh/file.c
 *  Copyright (C) 1993  Pascal Haible, Bruno Haible
 *
 *  sysv/file.c
 *  Copyright (C) 1993  Bruno Haible
 *
 *  SystemV/Coherent regular file handling primitives
 */

#समावेश "sysv.h"

/*
 * We have mostly शून्यs here: the current शेषs are OK क्रम
 * the coh fileप्रणाली.
 */
स्थिर काष्ठा file_operations sysv_file_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो_iter	= generic_file_पढ़ो_iter,
	.ग_लिखो_iter	= generic_file_ग_लिखो_iter,
	.mmap		= generic_file_mmap,
	.fsync		= generic_file_fsync,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
पूर्ण;

अटल पूर्णांक sysv_setattr(काष्ठा user_namespace *mnt_userns,
			काष्ठा dentry *dentry, काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक error;

	error = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (error)
		वापस error;

	अगर ((attr->ia_valid & ATTR_SIZE) &&
	    attr->ia_size != i_size_पढ़ो(inode)) अणु
		error = inode_newsize_ok(inode, attr->ia_size);
		अगर (error)
			वापस error;
		truncate_setsize(inode, attr->ia_size);
		sysv_truncate(inode);
	पूर्ण

	setattr_copy(&init_user_ns, inode, attr);
	mark_inode_dirty(inode);
	वापस 0;
पूर्ण

स्थिर काष्ठा inode_operations sysv_file_inode_operations = अणु
	.setattr	= sysv_setattr,
	.getattr	= sysv_getattr,
पूर्ण;
