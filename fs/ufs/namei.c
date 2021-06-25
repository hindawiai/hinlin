<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/ufs/namei.c
 *
 * Migration to usage of "page cache" on May 2006 by
 * Evgeniy Dushistov <dushistov@mail.ru> based on ext2 code base.
 *
 * Copyright (C) 1998
 * Daniel Pirkl <daniel.pirkl@email.cz>
 * Charles University, Faculty of Mathematics and Physics
 *
 *  from
 *
 *  linux/fs/ext2/namei.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/fs/minix/namei.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  Big-endian to little-endian byte-swapping/biपंचांगaps by
 *        David S. Miller (davem@caip.rutgers.edu), 1995
 */

#समावेश <linux/समय.स>
#समावेश <linux/fs.h>

#समावेश "ufs_fs.h"
#समावेश "ufs.h"
#समावेश "util.h"

अटल अंतरभूत पूर्णांक ufs_add_nondir(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	पूर्णांक err = ufs_add_link(dentry, inode);
	अगर (!err) अणु
		d_instantiate_new(dentry, inode);
		वापस 0;
	पूर्ण
	inode_dec_link_count(inode);
	discard_new_inode(inode);
	वापस err;
पूर्ण

अटल काष्ठा dentry *ufs_lookup(काष्ठा inode * dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode * inode = शून्य;
	ino_t ino;
	
	अगर (dentry->d_name.len > UFS_MAXNAMLEN)
		वापस ERR_PTR(-ENAMETOOLONG);

	ino = ufs_inode_by_name(dir, &dentry->d_name);
	अगर (ino)
		inode = ufs_iget(dir->i_sb, ino);
	वापस d_splice_alias(inode, dentry);
पूर्ण

/*
 * By the समय this is called, we alपढ़ोy have created
 * the directory cache entry क्रम the new file, but it
 * is so far negative - it has no inode.
 *
 * If the create succeeds, we fill in the inode inक्रमmation
 * with d_instantiate(). 
 */
अटल पूर्णांक ufs_create (काष्ठा user_namespace * mnt_userns,
		काष्ठा inode * dir, काष्ठा dentry * dentry, umode_t mode,
		bool excl)
अणु
	काष्ठा inode *inode;

	inode = ufs_new_inode(dir, mode);
	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	inode->i_op = &ufs_file_inode_operations;
	inode->i_fop = &ufs_file_operations;
	inode->i_mapping->a_ops = &ufs_aops;
	mark_inode_dirty(inode);
	वापस ufs_add_nondir(dentry, inode);
पूर्ण

अटल पूर्णांक ufs_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		     काष्ठा dentry *dentry, umode_t mode, dev_t rdev)
अणु
	काष्ठा inode *inode;
	पूर्णांक err;

	अगर (!old_valid_dev(rdev))
		वापस -EINVAL;

	inode = ufs_new_inode(dir, mode);
	err = PTR_ERR(inode);
	अगर (!IS_ERR(inode)) अणु
		init_special_inode(inode, mode, rdev);
		ufs_set_inode_dev(inode->i_sb, UFS_I(inode), rdev);
		mark_inode_dirty(inode);
		err = ufs_add_nondir(dentry, inode);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक ufs_symlink (काष्ठा user_namespace * mnt_userns, काष्ठा inode * dir,
	काष्ठा dentry * dentry, स्थिर अक्षर * symname)
अणु
	काष्ठा super_block * sb = dir->i_sb;
	पूर्णांक err;
	अचिन्हित l = म_माप(symname)+1;
	काष्ठा inode * inode;

	अगर (l > sb->s_blocksize)
		वापस -ENAMETOOLONG;

	inode = ufs_new_inode(dir, S_IFLNK | S_IRWXUGO);
	err = PTR_ERR(inode);
	अगर (IS_ERR(inode))
		वापस err;

	अगर (l > UFS_SB(sb)->s_uspi->s_maxsymlinklen) अणु
		/* slow symlink */
		inode->i_op = &page_symlink_inode_operations;
		inode_nohighmem(inode);
		inode->i_mapping->a_ops = &ufs_aops;
		err = page_symlink(inode, symname, l);
		अगर (err)
			जाओ out_fail;
	पूर्ण अन्यथा अणु
		/* fast symlink */
		inode->i_op = &simple_symlink_inode_operations;
		inode->i_link = (अक्षर *)UFS_I(inode)->i_u1.i_symlink;
		स_नकल(inode->i_link, symname, l);
		inode->i_size = l-1;
	पूर्ण
	mark_inode_dirty(inode);

	वापस ufs_add_nondir(dentry, inode);

out_fail:
	inode_dec_link_count(inode);
	discard_new_inode(inode);
	वापस err;
पूर्ण

अटल पूर्णांक ufs_link (काष्ठा dentry * old_dentry, काष्ठा inode * dir,
	काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(old_dentry);
	पूर्णांक error;

	inode->i_स_समय = current_समय(inode);
	inode_inc_link_count(inode);
	ihold(inode);

	error = ufs_add_link(dentry, inode);
	अगर (error) अणु
		inode_dec_link_count(inode);
		iput(inode);
	पूर्ण अन्यथा
		d_instantiate(dentry, inode);
	वापस error;
पूर्ण

अटल पूर्णांक ufs_सूची_गढ़ो(काष्ठा user_namespace * mnt_userns, काष्ठा inode * dir,
	काष्ठा dentry * dentry, umode_t mode)
अणु
	काष्ठा inode * inode;
	पूर्णांक err;

	inode_inc_link_count(dir);

	inode = ufs_new_inode(dir, S_IFसूची|mode);
	err = PTR_ERR(inode);
	अगर (IS_ERR(inode))
		जाओ out_dir;

	inode->i_op = &ufs_dir_inode_operations;
	inode->i_fop = &ufs_dir_operations;
	inode->i_mapping->a_ops = &ufs_aops;

	inode_inc_link_count(inode);

	err = ufs_make_empty(inode, dir);
	अगर (err)
		जाओ out_fail;

	err = ufs_add_link(dentry, inode);
	अगर (err)
		जाओ out_fail;

	d_instantiate_new(dentry, inode);
	वापस 0;

out_fail:
	inode_dec_link_count(inode);
	inode_dec_link_count(inode);
	discard_new_inode(inode);
out_dir:
	inode_dec_link_count(dir);
	वापस err;
पूर्ण

अटल पूर्णांक ufs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode * inode = d_inode(dentry);
	काष्ठा ufs_dir_entry *de;
	काष्ठा page *page;
	पूर्णांक err = -ENOENT;

	de = ufs_find_entry(dir, &dentry->d_name, &page);
	अगर (!de)
		जाओ out;

	err = ufs_delete_entry(dir, de, page);
	अगर (err)
		जाओ out;

	inode->i_स_समय = dir->i_स_समय;
	inode_dec_link_count(inode);
	err = 0;
out:
	वापस err;
पूर्ण

अटल पूर्णांक ufs_सूची_हटाओ (काष्ठा inode * dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode * inode = d_inode(dentry);
	पूर्णांक err= -ENOTEMPTY;

	अगर (ufs_empty_dir (inode)) अणु
		err = ufs_unlink(dir, dentry);
		अगर (!err) अणु
			inode->i_size = 0;
			inode_dec_link_count(inode);
			inode_dec_link_count(dir);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक ufs_नाम(काष्ठा user_namespace *mnt_userns, काष्ठा inode *old_dir,
		      काष्ठा dentry *old_dentry, काष्ठा inode *new_dir,
		      काष्ठा dentry *new_dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *old_inode = d_inode(old_dentry);
	काष्ठा inode *new_inode = d_inode(new_dentry);
	काष्ठा page *dir_page = शून्य;
	काष्ठा ufs_dir_entry * dir_de = शून्य;
	काष्ठा page *old_page;
	काष्ठा ufs_dir_entry *old_de;
	पूर्णांक err = -ENOENT;

	अगर (flags & ~RENAME_NOREPLACE)
		वापस -EINVAL;

	old_de = ufs_find_entry(old_dir, &old_dentry->d_name, &old_page);
	अगर (!old_de)
		जाओ out;

	अगर (S_ISसूची(old_inode->i_mode)) अणु
		err = -EIO;
		dir_de = ufs_करोtकरोt(old_inode, &dir_page);
		अगर (!dir_de)
			जाओ out_old;
	पूर्ण

	अगर (new_inode) अणु
		काष्ठा page *new_page;
		काष्ठा ufs_dir_entry *new_de;

		err = -ENOTEMPTY;
		अगर (dir_de && !ufs_empty_dir(new_inode))
			जाओ out_dir;

		err = -ENOENT;
		new_de = ufs_find_entry(new_dir, &new_dentry->d_name, &new_page);
		अगर (!new_de)
			जाओ out_dir;
		ufs_set_link(new_dir, new_de, new_page, old_inode, 1);
		new_inode->i_स_समय = current_समय(new_inode);
		अगर (dir_de)
			drop_nlink(new_inode);
		inode_dec_link_count(new_inode);
	पूर्ण अन्यथा अणु
		err = ufs_add_link(new_dentry, old_inode);
		अगर (err)
			जाओ out_dir;
		अगर (dir_de)
			inode_inc_link_count(new_dir);
	पूर्ण

	/*
	 * Like most other Unix प्रणालीs, set the स_समय क्रम inodes on a
 	 * नाम.
	 */
	old_inode->i_स_समय = current_समय(old_inode);

	ufs_delete_entry(old_dir, old_de, old_page);
	mark_inode_dirty(old_inode);

	अगर (dir_de) अणु
		अगर (old_dir != new_dir)
			ufs_set_link(old_inode, dir_de, dir_page, new_dir, 0);
		अन्यथा अणु
			kunmap(dir_page);
			put_page(dir_page);
		पूर्ण
		inode_dec_link_count(old_dir);
	पूर्ण
	वापस 0;


out_dir:
	अगर (dir_de) अणु
		kunmap(dir_page);
		put_page(dir_page);
	पूर्ण
out_old:
	kunmap(old_page);
	put_page(old_page);
out:
	वापस err;
पूर्ण

स्थिर काष्ठा inode_operations ufs_dir_inode_operations = अणु
	.create		= ufs_create,
	.lookup		= ufs_lookup,
	.link		= ufs_link,
	.unlink		= ufs_unlink,
	.symlink	= ufs_symlink,
	.सूची_गढ़ो		= ufs_सूची_गढ़ो,
	.सूची_हटाओ		= ufs_सूची_हटाओ,
	.mknod		= ufs_mknod,
	.नाम		= ufs_नाम,
पूर्ण;
