<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/sysv/namei.c
 *
 *  minix/namei.c
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  coh/namei.c
 *  Copyright (C) 1993  Pascal Haible, Bruno Haible
 *
 *  sysv/namei.c
 *  Copyright (C) 1993  Bruno Haible
 *  Copyright (C) 1997, 1998  Krzysztof G. Baranowski
 */

#समावेश <linux/pagemap.h>
#समावेश "sysv.h"

अटल पूर्णांक add_nondir(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	पूर्णांक err = sysv_add_link(dentry, inode);
	अगर (!err) अणु
		d_instantiate(dentry, inode);
		वापस 0;
	पूर्ण
	inode_dec_link_count(inode);
	iput(inode);
	वापस err;
पूर्ण

अटल काष्ठा dentry *sysv_lookup(काष्ठा inode * dir, काष्ठा dentry * dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode * inode = शून्य;
	ino_t ino;

	अगर (dentry->d_name.len > SYSV_NAMELEN)
		वापस ERR_PTR(-ENAMETOOLONG);
	ino = sysv_inode_by_name(dentry);
	अगर (ino)
		inode = sysv_iget(dir->i_sb, ino);
	वापस d_splice_alias(inode, dentry);
पूर्ण

अटल पूर्णांक sysv_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, umode_t mode, dev_t rdev)
अणु
	काष्ठा inode * inode;
	पूर्णांक err;

	अगर (!old_valid_dev(rdev))
		वापस -EINVAL;

	inode = sysv_new_inode(dir, mode);
	err = PTR_ERR(inode);

	अगर (!IS_ERR(inode)) अणु
		sysv_set_inode(inode, rdev);
		mark_inode_dirty(inode);
		err = add_nondir(dentry, inode);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक sysv_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	वापस sysv_mknod(&init_user_ns, dir, dentry, mode, 0);
पूर्ण

अटल पूर्णांक sysv_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			काष्ठा dentry *dentry, स्थिर अक्षर *symname)
अणु
	पूर्णांक err = -ENAMETOOLONG;
	पूर्णांक l = म_माप(symname)+1;
	काष्ठा inode * inode;

	अगर (l > dir->i_sb->s_blocksize)
		जाओ out;

	inode = sysv_new_inode(dir, S_IFLNK|0777);
	err = PTR_ERR(inode);
	अगर (IS_ERR(inode))
		जाओ out;
	
	sysv_set_inode(inode, 0);
	err = page_symlink(inode, symname, l);
	अगर (err)
		जाओ out_fail;

	mark_inode_dirty(inode);
	err = add_nondir(dentry, inode);
out:
	वापस err;

out_fail:
	inode_dec_link_count(inode);
	iput(inode);
	जाओ out;
पूर्ण

अटल पूर्णांक sysv_link(काष्ठा dentry * old_dentry, काष्ठा inode * dir, 
	काष्ठा dentry * dentry)
अणु
	काष्ठा inode *inode = d_inode(old_dentry);

	inode->i_स_समय = current_समय(inode);
	inode_inc_link_count(inode);
	ihold(inode);

	वापस add_nondir(dentry, inode);
पूर्ण

अटल पूर्णांक sysv_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा inode * inode;
	पूर्णांक err;

	inode_inc_link_count(dir);

	inode = sysv_new_inode(dir, S_IFसूची|mode);
	err = PTR_ERR(inode);
	अगर (IS_ERR(inode))
		जाओ out_dir;

	sysv_set_inode(inode, 0);

	inode_inc_link_count(inode);

	err = sysv_make_empty(inode, dir);
	अगर (err)
		जाओ out_fail;

	err = sysv_add_link(dentry, inode);
	अगर (err)
		जाओ out_fail;

        d_instantiate(dentry, inode);
out:
	वापस err;

out_fail:
	inode_dec_link_count(inode);
	inode_dec_link_count(inode);
	iput(inode);
out_dir:
	inode_dec_link_count(dir);
	जाओ out;
पूर्ण

अटल पूर्णांक sysv_unlink(काष्ठा inode * dir, काष्ठा dentry * dentry)
अणु
	काष्ठा inode * inode = d_inode(dentry);
	काष्ठा page * page;
	काष्ठा sysv_dir_entry * de;
	पूर्णांक err = -ENOENT;

	de = sysv_find_entry(dentry, &page);
	अगर (!de)
		जाओ out;

	err = sysv_delete_entry (de, page);
	अगर (err)
		जाओ out;

	inode->i_स_समय = dir->i_स_समय;
	inode_dec_link_count(inode);
out:
	वापस err;
पूर्ण

अटल पूर्णांक sysv_सूची_हटाओ(काष्ठा inode * dir, काष्ठा dentry * dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक err = -ENOTEMPTY;

	अगर (sysv_empty_dir(inode)) अणु
		err = sysv_unlink(dir, dentry);
		अगर (!err) अणु
			inode->i_size = 0;
			inode_dec_link_count(inode);
			inode_dec_link_count(dir);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/*
 * Anybody can नाम anything with this: the permission checks are left to the
 * higher-level routines.
 */
अटल पूर्णांक sysv_नाम(काष्ठा user_namespace *mnt_userns, काष्ठा inode *old_dir,
		       काष्ठा dentry *old_dentry, काष्ठा inode *new_dir,
		       काष्ठा dentry *new_dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode * old_inode = d_inode(old_dentry);
	काष्ठा inode * new_inode = d_inode(new_dentry);
	काष्ठा page * dir_page = शून्य;
	काष्ठा sysv_dir_entry * dir_de = शून्य;
	काष्ठा page * old_page;
	काष्ठा sysv_dir_entry * old_de;
	पूर्णांक err = -ENOENT;

	अगर (flags & ~RENAME_NOREPLACE)
		वापस -EINVAL;

	old_de = sysv_find_entry(old_dentry, &old_page);
	अगर (!old_de)
		जाओ out;

	अगर (S_ISसूची(old_inode->i_mode)) अणु
		err = -EIO;
		dir_de = sysv_करोtकरोt(old_inode, &dir_page);
		अगर (!dir_de)
			जाओ out_old;
	पूर्ण

	अगर (new_inode) अणु
		काष्ठा page * new_page;
		काष्ठा sysv_dir_entry * new_de;

		err = -ENOTEMPTY;
		अगर (dir_de && !sysv_empty_dir(new_inode))
			जाओ out_dir;

		err = -ENOENT;
		new_de = sysv_find_entry(new_dentry, &new_page);
		अगर (!new_de)
			जाओ out_dir;
		sysv_set_link(new_de, new_page, old_inode);
		new_inode->i_स_समय = current_समय(new_inode);
		अगर (dir_de)
			drop_nlink(new_inode);
		inode_dec_link_count(new_inode);
	पूर्ण अन्यथा अणु
		err = sysv_add_link(new_dentry, old_inode);
		अगर (err)
			जाओ out_dir;
		अगर (dir_de)
			inode_inc_link_count(new_dir);
	पूर्ण

	sysv_delete_entry(old_de, old_page);
	mark_inode_dirty(old_inode);

	अगर (dir_de) अणु
		sysv_set_link(dir_de, dir_page, new_dir);
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

/*
 * directories can handle most operations...
 */
स्थिर काष्ठा inode_operations sysv_dir_inode_operations = अणु
	.create		= sysv_create,
	.lookup		= sysv_lookup,
	.link		= sysv_link,
	.unlink		= sysv_unlink,
	.symlink	= sysv_symlink,
	.सूची_गढ़ो		= sysv_सूची_गढ़ो,
	.सूची_हटाओ		= sysv_सूची_हटाओ,
	.mknod		= sysv_mknod,
	.नाम		= sysv_नाम,
	.getattr	= sysv_getattr,
पूर्ण;
