<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/minix/namei.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#समावेश "minix.h"

अटल पूर्णांक add_nondir(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	पूर्णांक err = minix_add_link(dentry, inode);
	अगर (!err) अणु
		d_instantiate(dentry, inode);
		वापस 0;
	पूर्ण
	inode_dec_link_count(inode);
	iput(inode);
	वापस err;
पूर्ण

अटल काष्ठा dentry *minix_lookup(काष्ठा inode * dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode * inode = शून्य;
	ino_t ino;

	अगर (dentry->d_name.len > minix_sb(dir->i_sb)->s_namelen)
		वापस ERR_PTR(-ENAMETOOLONG);

	ino = minix_inode_by_name(dentry);
	अगर (ino)
		inode = minix_iget(dir->i_sb, ino);
	वापस d_splice_alias(inode, dentry);
पूर्ण

अटल पूर्णांक minix_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, umode_t mode, dev_t rdev)
अणु
	पूर्णांक error;
	काष्ठा inode *inode;

	अगर (!old_valid_dev(rdev))
		वापस -EINVAL;

	inode = minix_new_inode(dir, mode, &error);

	अगर (inode) अणु
		minix_set_inode(inode, rdev);
		mark_inode_dirty(inode);
		error = add_nondir(dentry, inode);
	पूर्ण
	वापस error;
पूर्ण

अटल पूर्णांक minix_क्षणिक_ख(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			 काष्ठा dentry *dentry, umode_t mode)
अणु
	पूर्णांक error;
	काष्ठा inode *inode = minix_new_inode(dir, mode, &error);
	अगर (inode) अणु
		minix_set_inode(inode, 0);
		mark_inode_dirty(inode);
		d_क्षणिक_ख(dentry, inode);
	पूर्ण
	वापस error;
पूर्ण

अटल पूर्णांक minix_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	वापस minix_mknod(mnt_userns, dir, dentry, mode, 0);
पूर्ण

अटल पूर्णांक minix_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			 काष्ठा dentry *dentry, स्थिर अक्षर *symname)
अणु
	पूर्णांक err = -ENAMETOOLONG;
	पूर्णांक i = म_माप(symname)+1;
	काष्ठा inode * inode;

	अगर (i > dir->i_sb->s_blocksize)
		जाओ out;

	inode = minix_new_inode(dir, S_IFLNK | 0777, &err);
	अगर (!inode)
		जाओ out;

	minix_set_inode(inode, 0);
	err = page_symlink(inode, symname, i);
	अगर (err)
		जाओ out_fail;

	err = add_nondir(dentry, inode);
out:
	वापस err;

out_fail:
	inode_dec_link_count(inode);
	iput(inode);
	जाओ out;
पूर्ण

अटल पूर्णांक minix_link(काष्ठा dentry * old_dentry, काष्ठा inode * dir,
	काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(old_dentry);

	inode->i_स_समय = current_समय(inode);
	inode_inc_link_count(inode);
	ihold(inode);
	वापस add_nondir(dentry, inode);
पूर्ण

अटल पूर्णांक minix_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा inode * inode;
	पूर्णांक err;

	inode_inc_link_count(dir);

	inode = minix_new_inode(dir, S_IFसूची | mode, &err);
	अगर (!inode)
		जाओ out_dir;

	minix_set_inode(inode, 0);

	inode_inc_link_count(inode);

	err = minix_make_empty(inode, dir);
	अगर (err)
		जाओ out_fail;

	err = minix_add_link(dentry, inode);
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

अटल पूर्णांक minix_unlink(काष्ठा inode * dir, काष्ठा dentry *dentry)
अणु
	पूर्णांक err = -ENOENT;
	काष्ठा inode * inode = d_inode(dentry);
	काष्ठा page * page;
	काष्ठा minix_dir_entry * de;

	de = minix_find_entry(dentry, &page);
	अगर (!de)
		जाओ end_unlink;

	err = minix_delete_entry(de, page);
	अगर (err)
		जाओ end_unlink;

	inode->i_स_समय = dir->i_स_समय;
	inode_dec_link_count(inode);
end_unlink:
	वापस err;
पूर्ण

अटल पूर्णांक minix_सूची_हटाओ(काष्ठा inode * dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode * inode = d_inode(dentry);
	पूर्णांक err = -ENOTEMPTY;

	अगर (minix_empty_dir(inode)) अणु
		err = minix_unlink(dir, dentry);
		अगर (!err) अणु
			inode_dec_link_count(dir);
			inode_dec_link_count(inode);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक minix_नाम(काष्ठा user_namespace *mnt_userns,
			काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode * old_inode = d_inode(old_dentry);
	काष्ठा inode * new_inode = d_inode(new_dentry);
	काष्ठा page * dir_page = शून्य;
	काष्ठा minix_dir_entry * dir_de = शून्य;
	काष्ठा page * old_page;
	काष्ठा minix_dir_entry * old_de;
	पूर्णांक err = -ENOENT;

	अगर (flags & ~RENAME_NOREPLACE)
		वापस -EINVAL;

	old_de = minix_find_entry(old_dentry, &old_page);
	अगर (!old_de)
		जाओ out;

	अगर (S_ISसूची(old_inode->i_mode)) अणु
		err = -EIO;
		dir_de = minix_करोtकरोt(old_inode, &dir_page);
		अगर (!dir_de)
			जाओ out_old;
	पूर्ण

	अगर (new_inode) अणु
		काष्ठा page * new_page;
		काष्ठा minix_dir_entry * new_de;

		err = -ENOTEMPTY;
		अगर (dir_de && !minix_empty_dir(new_inode))
			जाओ out_dir;

		err = -ENOENT;
		new_de = minix_find_entry(new_dentry, &new_page);
		अगर (!new_de)
			जाओ out_dir;
		minix_set_link(new_de, new_page, old_inode);
		new_inode->i_स_समय = current_समय(new_inode);
		अगर (dir_de)
			drop_nlink(new_inode);
		inode_dec_link_count(new_inode);
	पूर्ण अन्यथा अणु
		err = minix_add_link(new_dentry, old_inode);
		अगर (err)
			जाओ out_dir;
		अगर (dir_de)
			inode_inc_link_count(new_dir);
	पूर्ण

	minix_delete_entry(old_de, old_page);
	mark_inode_dirty(old_inode);

	अगर (dir_de) अणु
		minix_set_link(dir_de, dir_page, new_dir);
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
स्थिर काष्ठा inode_operations minix_dir_inode_operations = अणु
	.create		= minix_create,
	.lookup		= minix_lookup,
	.link		= minix_link,
	.unlink		= minix_unlink,
	.symlink	= minix_symlink,
	.सूची_गढ़ो		= minix_सूची_गढ़ो,
	.सूची_हटाओ		= minix_सूची_हटाओ,
	.mknod		= minix_mknod,
	.नाम		= minix_नाम,
	.getattr	= minix_getattr,
	.क्षणिक_ख	= minix_क्षणिक_ख,
पूर्ण;
