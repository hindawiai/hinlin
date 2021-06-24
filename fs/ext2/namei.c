<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/ext2/namei.c
 *
 * Reग_लिखो to pagecache. Almost all code had been changed, so blame me
 * अगर the things go wrong. Please, send bug reports to
 * viro@parcelfarce.linux.theplanet.co.uk
 *
 * Stuff here is basically a glue between the VFS and generic UNIXish
 * fileप्रणाली that keeps everything in pagecache. All knowledge of the
 * directory layout is in fs/ext2/dir.c - it turned out to be easily separatable
 * and it's easier to debug that way. In principle we might want to
 * generalize that a bit and turn it पूर्णांकo a library. Or not.
 *
 * The only non-अटल object here is ext2_dir_inode_operations.
 *
 * TODO: get rid of kmap() use, add पढ़ोahead.
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

#समावेश <linux/pagemap.h>
#समावेश <linux/quotaops.h>
#समावेश "ext2.h"
#समावेश "xattr.h"
#समावेश "acl.h"

अटल अंतरभूत पूर्णांक ext2_add_nondir(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	पूर्णांक err = ext2_add_link(dentry, inode);
	अगर (!err) अणु
		d_instantiate_new(dentry, inode);
		वापस 0;
	पूर्ण
	inode_dec_link_count(inode);
	discard_new_inode(inode);
	वापस err;
पूर्ण

/*
 * Methods themselves.
 */

अटल काष्ठा dentry *ext2_lookup(काष्ठा inode * dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode * inode;
	ino_t ino;
	पूर्णांक res;
	
	अगर (dentry->d_name.len > EXT2_NAME_LEN)
		वापस ERR_PTR(-ENAMETOOLONG);

	res = ext2_inode_by_name(dir, &dentry->d_name, &ino);
	अगर (res) अणु
		अगर (res != -ENOENT)
			वापस ERR_PTR(res);
		inode = शून्य;
	पूर्ण अन्यथा अणु
		inode = ext2_iget(dir->i_sb, ino);
		अगर (inode == ERR_PTR(-ESTALE)) अणु
			ext2_error(dir->i_sb, __func__,
					"deleted inode referenced: %lu",
					(अचिन्हित दीर्घ) ino);
			वापस ERR_PTR(-EIO);
		पूर्ण
	पूर्ण
	वापस d_splice_alias(inode, dentry);
पूर्ण

काष्ठा dentry *ext2_get_parent(काष्ठा dentry *child)
अणु
	ino_t ino;
	पूर्णांक res;

	res = ext2_inode_by_name(d_inode(child), &करोtकरोt_name, &ino);
	अगर (res)
		वापस ERR_PTR(res);

	वापस d_obtain_alias(ext2_iget(child->d_sb, ino));
पूर्ण 

/*
 * By the समय this is called, we alपढ़ोy have created
 * the directory cache entry क्रम the new file, but it
 * is so far negative - it has no inode.
 *
 * If the create succeeds, we fill in the inode inक्रमmation
 * with d_instantiate(). 
 */
अटल पूर्णांक ext2_create (काष्ठा user_namespace * mnt_userns,
			काष्ठा inode * dir, काष्ठा dentry * dentry,
			umode_t mode, bool excl)
अणु
	काष्ठा inode *inode;
	पूर्णांक err;

	err = dquot_initialize(dir);
	अगर (err)
		वापस err;

	inode = ext2_new_inode(dir, mode, &dentry->d_name);
	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	ext2_set_file_ops(inode);
	mark_inode_dirty(inode);
	वापस ext2_add_nondir(dentry, inode);
पूर्ण

अटल पूर्णांक ext2_क्षणिक_ख(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा inode *inode = ext2_new_inode(dir, mode, शून्य);
	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	ext2_set_file_ops(inode);
	mark_inode_dirty(inode);
	d_क्षणिक_ख(dentry, inode);
	unlock_new_inode(inode);
	वापस 0;
पूर्ण

अटल पूर्णांक ext2_mknod (काष्ठा user_namespace * mnt_userns, काष्ठा inode * dir,
	काष्ठा dentry *dentry, umode_t mode, dev_t rdev)
अणु
	काष्ठा inode * inode;
	पूर्णांक err;

	err = dquot_initialize(dir);
	अगर (err)
		वापस err;

	inode = ext2_new_inode (dir, mode, &dentry->d_name);
	err = PTR_ERR(inode);
	अगर (!IS_ERR(inode)) अणु
		init_special_inode(inode, inode->i_mode, rdev);
		inode->i_op = &ext2_special_inode_operations;
		mark_inode_dirty(inode);
		err = ext2_add_nondir(dentry, inode);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक ext2_symlink (काष्ठा user_namespace * mnt_userns, काष्ठा inode * dir,
	काष्ठा dentry * dentry, स्थिर अक्षर * symname)
अणु
	काष्ठा super_block * sb = dir->i_sb;
	पूर्णांक err = -ENAMETOOLONG;
	अचिन्हित l = म_माप(symname)+1;
	काष्ठा inode * inode;

	अगर (l > sb->s_blocksize)
		जाओ out;

	err = dquot_initialize(dir);
	अगर (err)
		जाओ out;

	inode = ext2_new_inode (dir, S_IFLNK | S_IRWXUGO, &dentry->d_name);
	err = PTR_ERR(inode);
	अगर (IS_ERR(inode))
		जाओ out;

	अगर (l > माप (EXT2_I(inode)->i_data)) अणु
		/* slow symlink */
		inode->i_op = &ext2_symlink_inode_operations;
		inode_nohighmem(inode);
		अगर (test_opt(inode->i_sb, NOBH))
			inode->i_mapping->a_ops = &ext2_nobh_aops;
		अन्यथा
			inode->i_mapping->a_ops = &ext2_aops;
		err = page_symlink(inode, symname, l);
		अगर (err)
			जाओ out_fail;
	पूर्ण अन्यथा अणु
		/* fast symlink */
		inode->i_op = &ext2_fast_symlink_inode_operations;
		inode->i_link = (अक्षर*)EXT2_I(inode)->i_data;
		स_नकल(inode->i_link, symname, l);
		inode->i_size = l-1;
	पूर्ण
	mark_inode_dirty(inode);

	err = ext2_add_nondir(dentry, inode);
out:
	वापस err;

out_fail:
	inode_dec_link_count(inode);
	discard_new_inode(inode);
	जाओ out;
पूर्ण

अटल पूर्णांक ext2_link (काष्ठा dentry * old_dentry, काष्ठा inode * dir,
	काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(old_dentry);
	पूर्णांक err;

	err = dquot_initialize(dir);
	अगर (err)
		वापस err;

	inode->i_स_समय = current_समय(inode);
	inode_inc_link_count(inode);
	ihold(inode);

	err = ext2_add_link(dentry, inode);
	अगर (!err) अणु
		d_instantiate(dentry, inode);
		वापस 0;
	पूर्ण
	inode_dec_link_count(inode);
	iput(inode);
	वापस err;
पूर्ण

अटल पूर्णांक ext2_सूची_गढ़ो(काष्ठा user_namespace * mnt_userns,
	काष्ठा inode * dir, काष्ठा dentry * dentry, umode_t mode)
अणु
	काष्ठा inode * inode;
	पूर्णांक err;

	err = dquot_initialize(dir);
	अगर (err)
		वापस err;

	inode_inc_link_count(dir);

	inode = ext2_new_inode(dir, S_IFसूची | mode, &dentry->d_name);
	err = PTR_ERR(inode);
	अगर (IS_ERR(inode))
		जाओ out_dir;

	inode->i_op = &ext2_dir_inode_operations;
	inode->i_fop = &ext2_dir_operations;
	अगर (test_opt(inode->i_sb, NOBH))
		inode->i_mapping->a_ops = &ext2_nobh_aops;
	अन्यथा
		inode->i_mapping->a_ops = &ext2_aops;

	inode_inc_link_count(inode);

	err = ext2_make_empty(inode, dir);
	अगर (err)
		जाओ out_fail;

	err = ext2_add_link(dentry, inode);
	अगर (err)
		जाओ out_fail;

	d_instantiate_new(dentry, inode);
out:
	वापस err;

out_fail:
	inode_dec_link_count(inode);
	inode_dec_link_count(inode);
	discard_new_inode(inode);
out_dir:
	inode_dec_link_count(dir);
	जाओ out;
पूर्ण

अटल पूर्णांक ext2_unlink(काष्ठा inode * dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode * inode = d_inode(dentry);
	काष्ठा ext2_dir_entry_2 * de;
	काष्ठा page * page;
	व्योम *page_addr;
	पूर्णांक err;

	err = dquot_initialize(dir);
	अगर (err)
		जाओ out;

	de = ext2_find_entry(dir, &dentry->d_name, &page, &page_addr);
	अगर (IS_ERR(de)) अणु
		err = PTR_ERR(de);
		जाओ out;
	पूर्ण

	err = ext2_delete_entry (de, page);
	ext2_put_page(page, page_addr);
	अगर (err)
		जाओ out;

	inode->i_स_समय = dir->i_स_समय;
	inode_dec_link_count(inode);
	err = 0;
out:
	वापस err;
पूर्ण

अटल पूर्णांक ext2_सूची_हटाओ (काष्ठा inode * dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode * inode = d_inode(dentry);
	पूर्णांक err = -ENOTEMPTY;

	अगर (ext2_empty_dir(inode)) अणु
		err = ext2_unlink(dir, dentry);
		अगर (!err) अणु
			inode->i_size = 0;
			inode_dec_link_count(inode);
			inode_dec_link_count(dir);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक ext2_नाम (काष्ठा user_namespace * mnt_userns,
			काष्ठा inode * old_dir, काष्ठा dentry * old_dentry,
			काष्ठा inode * new_dir, काष्ठा dentry * new_dentry,
			अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode * old_inode = d_inode(old_dentry);
	काष्ठा inode * new_inode = d_inode(new_dentry);
	काष्ठा page * dir_page = शून्य;
	व्योम *dir_page_addr;
	काष्ठा ext2_dir_entry_2 * dir_de = शून्य;
	काष्ठा page * old_page;
	व्योम *old_page_addr;
	काष्ठा ext2_dir_entry_2 * old_de;
	पूर्णांक err;

	अगर (flags & ~RENAME_NOREPLACE)
		वापस -EINVAL;

	err = dquot_initialize(old_dir);
	अगर (err)
		जाओ out;

	err = dquot_initialize(new_dir);
	अगर (err)
		जाओ out;

	old_de = ext2_find_entry(old_dir, &old_dentry->d_name, &old_page,
				 &old_page_addr);
	अगर (IS_ERR(old_de)) अणु
		err = PTR_ERR(old_de);
		जाओ out;
	पूर्ण

	अगर (S_ISसूची(old_inode->i_mode)) अणु
		err = -EIO;
		dir_de = ext2_करोtकरोt(old_inode, &dir_page, &dir_page_addr);
		अगर (!dir_de)
			जाओ out_old;
	पूर्ण

	अगर (new_inode) अणु
		व्योम *page_addr;
		काष्ठा page *new_page;
		काष्ठा ext2_dir_entry_2 *new_de;

		err = -ENOTEMPTY;
		अगर (dir_de && !ext2_empty_dir (new_inode))
			जाओ out_dir;

		new_de = ext2_find_entry(new_dir, &new_dentry->d_name,
					 &new_page, &page_addr);
		अगर (IS_ERR(new_de)) अणु
			err = PTR_ERR(new_de);
			जाओ out_dir;
		पूर्ण
		ext2_set_link(new_dir, new_de, new_page, page_addr, old_inode, 1);
		ext2_put_page(new_page, page_addr);
		new_inode->i_स_समय = current_समय(new_inode);
		अगर (dir_de)
			drop_nlink(new_inode);
		inode_dec_link_count(new_inode);
	पूर्ण अन्यथा अणु
		err = ext2_add_link(new_dentry, old_inode);
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
	mark_inode_dirty(old_inode);

	ext2_delete_entry(old_de, old_page);

	अगर (dir_de) अणु
		अगर (old_dir != new_dir)
			ext2_set_link(old_inode, dir_de, dir_page,
				      dir_page_addr, new_dir, 0);

		ext2_put_page(dir_page, dir_page_addr);
		inode_dec_link_count(old_dir);
	पूर्ण

	ext2_put_page(old_page, old_page_addr);
	वापस 0;

out_dir:
	अगर (dir_de)
		ext2_put_page(dir_page, dir_page_addr);
out_old:
	ext2_put_page(old_page, old_page_addr);
out:
	वापस err;
पूर्ण

स्थिर काष्ठा inode_operations ext2_dir_inode_operations = अणु
	.create		= ext2_create,
	.lookup		= ext2_lookup,
	.link		= ext2_link,
	.unlink		= ext2_unlink,
	.symlink	= ext2_symlink,
	.सूची_गढ़ो		= ext2_सूची_गढ़ो,
	.सूची_हटाओ		= ext2_सूची_हटाओ,
	.mknod		= ext2_mknod,
	.नाम		= ext2_नाम,
	.listxattr	= ext2_listxattr,
	.getattr	= ext2_getattr,
	.setattr	= ext2_setattr,
	.get_acl	= ext2_get_acl,
	.set_acl	= ext2_set_acl,
	.क्षणिक_ख	= ext2_क्षणिक_ख,
	.fileattr_get	= ext2_fileattr_get,
	.fileattr_set	= ext2_fileattr_set,
पूर्ण;

स्थिर काष्ठा inode_operations ext2_special_inode_operations = अणु
	.listxattr	= ext2_listxattr,
	.getattr	= ext2_getattr,
	.setattr	= ext2_setattr,
	.get_acl	= ext2_get_acl,
	.set_acl	= ext2_set_acl,
पूर्ण;
