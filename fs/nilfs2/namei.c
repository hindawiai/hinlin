<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * namei.c - NILFS pathname lookup operations.
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Modअगरied क्रम NILFS by Amagai Yoshiji and Ryusuke Konishi.
 */
/*
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

#समावेश <linux/pagemap.h>
#समावेश "nilfs.h"
#समावेश "export.h"

#घोषणा NILFS_FID_SIZE_NON_CONNECTABLE \
	(दुरत्व(काष्ठा nilfs_fid, parent_gen) / 4)
#घोषणा NILFS_FID_SIZE_CONNECTABLE	(माप(काष्ठा nilfs_fid) / 4)

अटल अंतरभूत पूर्णांक nilfs_add_nondir(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	पूर्णांक err = nilfs_add_link(dentry, inode);

	अगर (!err) अणु
		d_instantiate_new(dentry, inode);
		वापस 0;
	पूर्ण
	inode_dec_link_count(inode);
	unlock_new_inode(inode);
	iput(inode);
	वापस err;
पूर्ण

/*
 * Methods themselves.
 */

अटल काष्ठा dentry *
nilfs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode;
	ino_t ino;

	अगर (dentry->d_name.len > NILFS_NAME_LEN)
		वापस ERR_PTR(-ENAMETOOLONG);

	ino = nilfs_inode_by_name(dir, &dentry->d_name);
	inode = ino ? nilfs_iget(dir->i_sb, NILFS_I(dir)->i_root, ino) : शून्य;
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
अटल पूर्णांक nilfs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	काष्ठा inode *inode;
	काष्ठा nilfs_transaction_info ti;
	पूर्णांक err;

	err = nilfs_transaction_begin(dir->i_sb, &ti, 1);
	अगर (err)
		वापस err;
	inode = nilfs_new_inode(dir, mode);
	err = PTR_ERR(inode);
	अगर (!IS_ERR(inode)) अणु
		inode->i_op = &nilfs_file_inode_operations;
		inode->i_fop = &nilfs_file_operations;
		inode->i_mapping->a_ops = &nilfs_aops;
		nilfs_mark_inode_dirty(inode);
		err = nilfs_add_nondir(dentry, inode);
	पूर्ण
	अगर (!err)
		err = nilfs_transaction_commit(dir->i_sb);
	अन्यथा
		nilfs_transaction_पात(dir->i_sb);

	वापस err;
पूर्ण

अटल पूर्णांक
nilfs_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
	    काष्ठा dentry *dentry, umode_t mode, dev_t rdev)
अणु
	काष्ठा inode *inode;
	काष्ठा nilfs_transaction_info ti;
	पूर्णांक err;

	err = nilfs_transaction_begin(dir->i_sb, &ti, 1);
	अगर (err)
		वापस err;
	inode = nilfs_new_inode(dir, mode);
	err = PTR_ERR(inode);
	अगर (!IS_ERR(inode)) अणु
		init_special_inode(inode, inode->i_mode, rdev);
		nilfs_mark_inode_dirty(inode);
		err = nilfs_add_nondir(dentry, inode);
	पूर्ण
	अगर (!err)
		err = nilfs_transaction_commit(dir->i_sb);
	अन्यथा
		nilfs_transaction_पात(dir->i_sb);

	वापस err;
पूर्ण

अटल पूर्णांक nilfs_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			 काष्ठा dentry *dentry, स्थिर अक्षर *symname)
अणु
	काष्ठा nilfs_transaction_info ti;
	काष्ठा super_block *sb = dir->i_sb;
	अचिन्हित पूर्णांक l = म_माप(symname) + 1;
	काष्ठा inode *inode;
	पूर्णांक err;

	अगर (l > sb->s_blocksize)
		वापस -ENAMETOOLONG;

	err = nilfs_transaction_begin(dir->i_sb, &ti, 1);
	अगर (err)
		वापस err;

	inode = nilfs_new_inode(dir, S_IFLNK | 0777);
	err = PTR_ERR(inode);
	अगर (IS_ERR(inode))
		जाओ out;

	/* slow symlink */
	inode->i_op = &nilfs_symlink_inode_operations;
	inode_nohighmem(inode);
	inode->i_mapping->a_ops = &nilfs_aops;
	err = page_symlink(inode, symname, l);
	अगर (err)
		जाओ out_fail;

	/* mark_inode_dirty(inode); */
	/* page_symlink() करो this */

	err = nilfs_add_nondir(dentry, inode);
out:
	अगर (!err)
		err = nilfs_transaction_commit(dir->i_sb);
	अन्यथा
		nilfs_transaction_पात(dir->i_sb);

	वापस err;

out_fail:
	drop_nlink(inode);
	nilfs_mark_inode_dirty(inode);
	unlock_new_inode(inode);
	iput(inode);
	जाओ out;
पूर्ण

अटल पूर्णांक nilfs_link(काष्ठा dentry *old_dentry, काष्ठा inode *dir,
		      काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(old_dentry);
	काष्ठा nilfs_transaction_info ti;
	पूर्णांक err;

	err = nilfs_transaction_begin(dir->i_sb, &ti, 1);
	अगर (err)
		वापस err;

	inode->i_स_समय = current_समय(inode);
	inode_inc_link_count(inode);
	ihold(inode);

	err = nilfs_add_link(dentry, inode);
	अगर (!err) अणु
		d_instantiate(dentry, inode);
		err = nilfs_transaction_commit(dir->i_sb);
	पूर्ण अन्यथा अणु
		inode_dec_link_count(inode);
		iput(inode);
		nilfs_transaction_पात(dir->i_sb);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक nilfs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा inode *inode;
	काष्ठा nilfs_transaction_info ti;
	पूर्णांक err;

	err = nilfs_transaction_begin(dir->i_sb, &ti, 1);
	अगर (err)
		वापस err;

	inc_nlink(dir);

	inode = nilfs_new_inode(dir, S_IFसूची | mode);
	err = PTR_ERR(inode);
	अगर (IS_ERR(inode))
		जाओ out_dir;

	inode->i_op = &nilfs_dir_inode_operations;
	inode->i_fop = &nilfs_dir_operations;
	inode->i_mapping->a_ops = &nilfs_aops;

	inc_nlink(inode);

	err = nilfs_make_empty(inode, dir);
	अगर (err)
		जाओ out_fail;

	err = nilfs_add_link(dentry, inode);
	अगर (err)
		जाओ out_fail;

	nilfs_mark_inode_dirty(inode);
	d_instantiate_new(dentry, inode);
out:
	अगर (!err)
		err = nilfs_transaction_commit(dir->i_sb);
	अन्यथा
		nilfs_transaction_पात(dir->i_sb);

	वापस err;

out_fail:
	drop_nlink(inode);
	drop_nlink(inode);
	nilfs_mark_inode_dirty(inode);
	unlock_new_inode(inode);
	iput(inode);
out_dir:
	drop_nlink(dir);
	nilfs_mark_inode_dirty(dir);
	जाओ out;
पूर्ण

अटल पूर्णांक nilfs_करो_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode;
	काष्ठा nilfs_dir_entry *de;
	काष्ठा page *page;
	पूर्णांक err;

	err = -ENOENT;
	de = nilfs_find_entry(dir, &dentry->d_name, &page);
	अगर (!de)
		जाओ out;

	inode = d_inode(dentry);
	err = -EIO;
	अगर (le64_to_cpu(de->inode) != inode->i_ino)
		जाओ out;

	अगर (!inode->i_nlink) अणु
		nilfs_warn(inode->i_sb,
			   "deleting nonexistent file (ino=%lu), %d",
			   inode->i_ino, inode->i_nlink);
		set_nlink(inode, 1);
	पूर्ण
	err = nilfs_delete_entry(de, page);
	अगर (err)
		जाओ out;

	inode->i_स_समय = dir->i_स_समय;
	drop_nlink(inode);
	err = 0;
out:
	वापस err;
पूर्ण

अटल पूर्णांक nilfs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा nilfs_transaction_info ti;
	पूर्णांक err;

	err = nilfs_transaction_begin(dir->i_sb, &ti, 0);
	अगर (err)
		वापस err;

	err = nilfs_करो_unlink(dir, dentry);

	अगर (!err) अणु
		nilfs_mark_inode_dirty(dir);
		nilfs_mark_inode_dirty(d_inode(dentry));
		err = nilfs_transaction_commit(dir->i_sb);
	पूर्ण अन्यथा
		nilfs_transaction_पात(dir->i_sb);

	वापस err;
पूर्ण

अटल पूर्णांक nilfs_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा nilfs_transaction_info ti;
	पूर्णांक err;

	err = nilfs_transaction_begin(dir->i_sb, &ti, 0);
	अगर (err)
		वापस err;

	err = -ENOTEMPTY;
	अगर (nilfs_empty_dir(inode)) अणु
		err = nilfs_करो_unlink(dir, dentry);
		अगर (!err) अणु
			inode->i_size = 0;
			drop_nlink(inode);
			nilfs_mark_inode_dirty(inode);
			drop_nlink(dir);
			nilfs_mark_inode_dirty(dir);
		पूर्ण
	पूर्ण
	अगर (!err)
		err = nilfs_transaction_commit(dir->i_sb);
	अन्यथा
		nilfs_transaction_पात(dir->i_sb);

	वापस err;
पूर्ण

अटल पूर्णांक nilfs_नाम(काष्ठा user_namespace *mnt_userns,
			काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *old_inode = d_inode(old_dentry);
	काष्ठा inode *new_inode = d_inode(new_dentry);
	काष्ठा page *dir_page = शून्य;
	काष्ठा nilfs_dir_entry *dir_de = शून्य;
	काष्ठा page *old_page;
	काष्ठा nilfs_dir_entry *old_de;
	काष्ठा nilfs_transaction_info ti;
	पूर्णांक err;

	अगर (flags & ~RENAME_NOREPLACE)
		वापस -EINVAL;

	err = nilfs_transaction_begin(old_dir->i_sb, &ti, 1);
	अगर (unlikely(err))
		वापस err;

	err = -ENOENT;
	old_de = nilfs_find_entry(old_dir, &old_dentry->d_name, &old_page);
	अगर (!old_de)
		जाओ out;

	अगर (S_ISसूची(old_inode->i_mode)) अणु
		err = -EIO;
		dir_de = nilfs_करोtकरोt(old_inode, &dir_page);
		अगर (!dir_de)
			जाओ out_old;
	पूर्ण

	अगर (new_inode) अणु
		काष्ठा page *new_page;
		काष्ठा nilfs_dir_entry *new_de;

		err = -ENOTEMPTY;
		अगर (dir_de && !nilfs_empty_dir(new_inode))
			जाओ out_dir;

		err = -ENOENT;
		new_de = nilfs_find_entry(new_dir, &new_dentry->d_name, &new_page);
		अगर (!new_de)
			जाओ out_dir;
		nilfs_set_link(new_dir, new_de, new_page, old_inode);
		nilfs_mark_inode_dirty(new_dir);
		new_inode->i_स_समय = current_समय(new_inode);
		अगर (dir_de)
			drop_nlink(new_inode);
		drop_nlink(new_inode);
		nilfs_mark_inode_dirty(new_inode);
	पूर्ण अन्यथा अणु
		err = nilfs_add_link(new_dentry, old_inode);
		अगर (err)
			जाओ out_dir;
		अगर (dir_de) अणु
			inc_nlink(new_dir);
			nilfs_mark_inode_dirty(new_dir);
		पूर्ण
	पूर्ण

	/*
	 * Like most other Unix प्रणालीs, set the स_समय क्रम inodes on a
	 * नाम.
	 */
	old_inode->i_स_समय = current_समय(old_inode);

	nilfs_delete_entry(old_de, old_page);

	अगर (dir_de) अणु
		nilfs_set_link(old_inode, dir_de, dir_page, new_dir);
		drop_nlink(old_dir);
	पूर्ण
	nilfs_mark_inode_dirty(old_dir);
	nilfs_mark_inode_dirty(old_inode);

	err = nilfs_transaction_commit(old_dir->i_sb);
	वापस err;

out_dir:
	अगर (dir_de) अणु
		kunmap(dir_page);
		put_page(dir_page);
	पूर्ण
out_old:
	kunmap(old_page);
	put_page(old_page);
out:
	nilfs_transaction_पात(old_dir->i_sb);
	वापस err;
पूर्ण

/*
 * Export operations
 */
अटल काष्ठा dentry *nilfs_get_parent(काष्ठा dentry *child)
अणु
	अचिन्हित दीर्घ ino;
	काष्ठा inode *inode;
	काष्ठा nilfs_root *root;

	ino = nilfs_inode_by_name(d_inode(child), &करोtकरोt_name);
	अगर (!ino)
		वापस ERR_PTR(-ENOENT);

	root = NILFS_I(d_inode(child))->i_root;

	inode = nilfs_iget(child->d_sb, root, ino);
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);

	वापस d_obtain_alias(inode);
पूर्ण

अटल काष्ठा dentry *nilfs_get_dentry(काष्ठा super_block *sb, u64 cno,
				       u64 ino, u32 gen)
अणु
	काष्ठा nilfs_root *root;
	काष्ठा inode *inode;

	अगर (ino < NILFS_FIRST_INO(sb) && ino != NILFS_ROOT_INO)
		वापस ERR_PTR(-ESTALE);

	root = nilfs_lookup_root(sb->s_fs_info, cno);
	अगर (!root)
		वापस ERR_PTR(-ESTALE);

	inode = nilfs_iget(sb, root, ino);
	nilfs_put_root(root);

	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);
	अगर (gen && inode->i_generation != gen) अणु
		iput(inode);
		वापस ERR_PTR(-ESTALE);
	पूर्ण
	वापस d_obtain_alias(inode);
पूर्ण

अटल काष्ठा dentry *nilfs_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fh,
					 पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	काष्ठा nilfs_fid *fid = (काष्ठा nilfs_fid *)fh;

	अगर (fh_len < NILFS_FID_SIZE_NON_CONNECTABLE ||
	    (fh_type != खाताID_NILFS_WITH_PARENT &&
	     fh_type != खाताID_NILFS_WITHOUT_PARENT))
		वापस शून्य;

	वापस nilfs_get_dentry(sb, fid->cno, fid->ino, fid->gen);
पूर्ण

अटल काष्ठा dentry *nilfs_fh_to_parent(काष्ठा super_block *sb, काष्ठा fid *fh,
					 पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	काष्ठा nilfs_fid *fid = (काष्ठा nilfs_fid *)fh;

	अगर (fh_len < NILFS_FID_SIZE_CONNECTABLE ||
	    fh_type != खाताID_NILFS_WITH_PARENT)
		वापस शून्य;

	वापस nilfs_get_dentry(sb, fid->cno, fid->parent_ino, fid->parent_gen);
पूर्ण

अटल पूर्णांक nilfs_encode_fh(काष्ठा inode *inode, __u32 *fh, पूर्णांक *lenp,
			   काष्ठा inode *parent)
अणु
	काष्ठा nilfs_fid *fid = (काष्ठा nilfs_fid *)fh;
	काष्ठा nilfs_root *root = NILFS_I(inode)->i_root;
	पूर्णांक type;

	अगर (parent && *lenp < NILFS_FID_SIZE_CONNECTABLE) अणु
		*lenp = NILFS_FID_SIZE_CONNECTABLE;
		वापस खाताID_INVALID;
	पूर्ण
	अगर (*lenp < NILFS_FID_SIZE_NON_CONNECTABLE) अणु
		*lenp = NILFS_FID_SIZE_NON_CONNECTABLE;
		वापस खाताID_INVALID;
	पूर्ण

	fid->cno = root->cno;
	fid->ino = inode->i_ino;
	fid->gen = inode->i_generation;

	अगर (parent) अणु
		fid->parent_ino = parent->i_ino;
		fid->parent_gen = parent->i_generation;
		type = खाताID_NILFS_WITH_PARENT;
		*lenp = NILFS_FID_SIZE_CONNECTABLE;
	पूर्ण अन्यथा अणु
		type = खाताID_NILFS_WITHOUT_PARENT;
		*lenp = NILFS_FID_SIZE_NON_CONNECTABLE;
	पूर्ण

	वापस type;
पूर्ण

स्थिर काष्ठा inode_operations nilfs_dir_inode_operations = अणु
	.create		= nilfs_create,
	.lookup		= nilfs_lookup,
	.link		= nilfs_link,
	.unlink		= nilfs_unlink,
	.symlink	= nilfs_symlink,
	.सूची_गढ़ो		= nilfs_सूची_गढ़ो,
	.सूची_हटाओ		= nilfs_सूची_हटाओ,
	.mknod		= nilfs_mknod,
	.नाम		= nilfs_नाम,
	.setattr	= nilfs_setattr,
	.permission	= nilfs_permission,
	.fiemap		= nilfs_fiemap,
	.fileattr_get	= nilfs_fileattr_get,
	.fileattr_set	= nilfs_fileattr_set,
पूर्ण;

स्थिर काष्ठा inode_operations nilfs_special_inode_operations = अणु
	.setattr	= nilfs_setattr,
	.permission	= nilfs_permission,
पूर्ण;

स्थिर काष्ठा inode_operations nilfs_symlink_inode_operations = अणु
	.get_link	= page_get_link,
	.permission     = nilfs_permission,
पूर्ण;

स्थिर काष्ठा export_operations nilfs_export_ops = अणु
	.encode_fh = nilfs_encode_fh,
	.fh_to_dentry = nilfs_fh_to_dentry,
	.fh_to_parent = nilfs_fh_to_parent,
	.get_parent = nilfs_get_parent,
पूर्ण;
