<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ext4/symlink.c
 *
 * Only fast symlinks left here - the rest is करोne by generic code. AV, 1999
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/fs/minix/symlink.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  ext4 symlink handling code
 */

#समावेश <linux/fs.h>
#समावेश <linux/namei.h>
#समावेश "ext4.h"
#समावेश "xattr.h"

अटल स्थिर अक्षर *ext4_encrypted_get_link(काष्ठा dentry *dentry,
					   काष्ठा inode *inode,
					   काष्ठा delayed_call *करोne)
अणु
	काष्ठा page *cpage = शून्य;
	स्थिर व्योम *caddr;
	अचिन्हित पूर्णांक max_size;
	स्थिर अक्षर *paddr;

	अगर (!dentry)
		वापस ERR_PTR(-ECHILD);

	अगर (ext4_inode_is_fast_symlink(inode)) अणु
		caddr = EXT4_I(inode)->i_data;
		max_size = माप(EXT4_I(inode)->i_data);
	पूर्ण अन्यथा अणु
		cpage = पढ़ो_mapping_page(inode->i_mapping, 0, शून्य);
		अगर (IS_ERR(cpage))
			वापस ERR_CAST(cpage);
		caddr = page_address(cpage);
		max_size = inode->i_sb->s_blocksize;
	पूर्ण

	paddr = fscrypt_get_symlink(inode, caddr, max_size, करोne);
	अगर (cpage)
		put_page(cpage);
	वापस paddr;
पूर्ण

स्थिर काष्ठा inode_operations ext4_encrypted_symlink_inode_operations = अणु
	.get_link	= ext4_encrypted_get_link,
	.setattr	= ext4_setattr,
	.getattr	= ext4_getattr,
	.listxattr	= ext4_listxattr,
पूर्ण;

स्थिर काष्ठा inode_operations ext4_symlink_inode_operations = अणु
	.get_link	= page_get_link,
	.setattr	= ext4_setattr,
	.getattr	= ext4_getattr,
	.listxattr	= ext4_listxattr,
पूर्ण;

स्थिर काष्ठा inode_operations ext4_fast_symlink_inode_operations = अणु
	.get_link	= simple_get_link,
	.setattr	= ext4_setattr,
	.getattr	= ext4_getattr,
	.listxattr	= ext4_listxattr,
पूर्ण;
