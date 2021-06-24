<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hfsplus/inode.c
 *
 * Copyright (C) 2001
 * Brad Boyer (flar@allandria.com)
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 *
 * Inode handling routines
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/mpage.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/uपन.स>
#समावेश <linux/fileattr.h>

#समावेश "hfsplus_fs.h"
#समावेश "hfsplus_raw.h"
#समावेश "xattr.h"

अटल पूर्णांक hfsplus_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस block_पढ़ो_full_page(page, hfsplus_get_block);
पूर्ण

अटल पूर्णांक hfsplus_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस block_ग_लिखो_full_page(page, hfsplus_get_block, wbc);
पूर्ण

अटल व्योम hfsplus_ग_लिखो_failed(काष्ठा address_space *mapping, loff_t to)
अणु
	काष्ठा inode *inode = mapping->host;

	अगर (to > inode->i_size) अणु
		truncate_pagecache(inode, inode->i_size);
		hfsplus_file_truncate(inode);
	पूर्ण
पूर्ण

अटल पूर्णांक hfsplus_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक ret;

	*pagep = शून्य;
	ret = cont_ग_लिखो_begin(file, mapping, pos, len, flags, pagep, fsdata,
				hfsplus_get_block,
				&HFSPLUS_I(mapping->host)->phys_size);
	अगर (unlikely(ret))
		hfsplus_ग_लिखो_failed(mapping, pos + len);

	वापस ret;
पूर्ण

अटल sector_t hfsplus_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	वापस generic_block_bmap(mapping, block, hfsplus_get_block);
पूर्ण

अटल पूर्णांक hfsplus_releasepage(काष्ठा page *page, gfp_t mask)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा hfs_btree *tree;
	काष्ठा hfs_bnode *node;
	u32 nidx;
	पूर्णांक i, res = 1;

	चयन (inode->i_ino) अणु
	हाल HFSPLUS_EXT_CNID:
		tree = HFSPLUS_SB(sb)->ext_tree;
		अवरोध;
	हाल HFSPLUS_CAT_CNID:
		tree = HFSPLUS_SB(sb)->cat_tree;
		अवरोध;
	हाल HFSPLUS_ATTR_CNID:
		tree = HFSPLUS_SB(sb)->attr_tree;
		अवरोध;
	शेष:
		BUG();
		वापस 0;
	पूर्ण
	अगर (!tree)
		वापस 0;
	अगर (tree->node_size >= PAGE_SIZE) अणु
		nidx = page->index >>
			(tree->node_size_shअगरt - PAGE_SHIFT);
		spin_lock(&tree->hash_lock);
		node = hfs_bnode_findhash(tree, nidx);
		अगर (!node)
			;
		अन्यथा अगर (atomic_पढ़ो(&node->refcnt))
			res = 0;
		अगर (res && node) अणु
			hfs_bnode_unhash(node);
			hfs_bnode_मुक्त(node);
		पूर्ण
		spin_unlock(&tree->hash_lock);
	पूर्ण अन्यथा अणु
		nidx = page->index <<
			(PAGE_SHIFT - tree->node_size_shअगरt);
		i = 1 << (PAGE_SHIFT - tree->node_size_shअगरt);
		spin_lock(&tree->hash_lock);
		करो अणु
			node = hfs_bnode_findhash(tree, nidx++);
			अगर (!node)
				जारी;
			अगर (atomic_पढ़ो(&node->refcnt)) अणु
				res = 0;
				अवरोध;
			पूर्ण
			hfs_bnode_unhash(node);
			hfs_bnode_मुक्त(node);
		पूर्ण जबतक (--i && nidx < tree->node_count);
		spin_unlock(&tree->hash_lock);
	पूर्ण
	वापस res ? try_to_मुक्त_buffers(page) : 0;
पूर्ण

अटल sमाप_प्रकार hfsplus_direct_IO(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा address_space *mapping = file->f_mapping;
	काष्ठा inode *inode = mapping->host;
	माप_प्रकार count = iov_iter_count(iter);
	sमाप_प्रकार ret;

	ret = blockdev_direct_IO(iocb, inode, iter, hfsplus_get_block);

	/*
	 * In हाल of error extending ग_लिखो may have instantiated a few
	 * blocks outside i_size. Trim these off again.
	 */
	अगर (unlikely(iov_iter_rw(iter) == WRITE && ret < 0)) अणु
		loff_t isize = i_size_पढ़ो(inode);
		loff_t end = iocb->ki_pos + count;

		अगर (end > isize)
			hfsplus_ग_लिखो_failed(mapping, end);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hfsplus_ग_लिखोpages(काष्ठा address_space *mapping,
			      काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस mpage_ग_लिखोpages(mapping, wbc, hfsplus_get_block);
पूर्ण

स्थिर काष्ठा address_space_operations hfsplus_btree_aops = अणु
	.पढ़ोpage	= hfsplus_पढ़ोpage,
	.ग_लिखोpage	= hfsplus_ग_लिखोpage,
	.ग_लिखो_begin	= hfsplus_ग_लिखो_begin,
	.ग_लिखो_end	= generic_ग_लिखो_end,
	.bmap		= hfsplus_bmap,
	.releasepage	= hfsplus_releasepage,
पूर्ण;

स्थिर काष्ठा address_space_operations hfsplus_aops = अणु
	.पढ़ोpage	= hfsplus_पढ़ोpage,
	.ग_लिखोpage	= hfsplus_ग_लिखोpage,
	.ग_लिखो_begin	= hfsplus_ग_लिखो_begin,
	.ग_लिखो_end	= generic_ग_लिखो_end,
	.bmap		= hfsplus_bmap,
	.direct_IO	= hfsplus_direct_IO,
	.ग_लिखोpages	= hfsplus_ग_लिखोpages,
पूर्ण;

स्थिर काष्ठा dentry_operations hfsplus_dentry_operations = अणु
	.d_hash       = hfsplus_hash_dentry,
	.d_compare    = hfsplus_compare_dentry,
पूर्ण;

अटल व्योम hfsplus_get_perms(काष्ठा inode *inode,
		काष्ठा hfsplus_perm *perms, पूर्णांक dir)
अणु
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(inode->i_sb);
	u16 mode;

	mode = be16_to_cpu(perms->mode);

	i_uid_ग_लिखो(inode, be32_to_cpu(perms->owner));
	अगर (!i_uid_पढ़ो(inode) && !mode)
		inode->i_uid = sbi->uid;

	i_gid_ग_लिखो(inode, be32_to_cpu(perms->group));
	अगर (!i_gid_पढ़ो(inode) && !mode)
		inode->i_gid = sbi->gid;

	अगर (dir) अणु
		mode = mode ? (mode & S_IALLUGO) : (S_IRWXUGO & ~(sbi->umask));
		mode |= S_IFसूची;
	पूर्ण अन्यथा अगर (!mode)
		mode = S_IFREG | ((S_IRUGO|S_IWUGO) & ~(sbi->umask));
	inode->i_mode = mode;

	HFSPLUS_I(inode)->userflags = perms->userflags;
	अगर (perms->rootflags & HFSPLUS_FLG_IMMUTABLE)
		inode->i_flags |= S_IMMUTABLE;
	अन्यथा
		inode->i_flags &= ~S_IMMUTABLE;
	अगर (perms->rootflags & HFSPLUS_FLG_APPEND)
		inode->i_flags |= S_APPEND;
	अन्यथा
		inode->i_flags &= ~S_APPEND;
पूर्ण

अटल पूर्णांक hfsplus_file_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (HFSPLUS_IS_RSRC(inode))
		inode = HFSPLUS_I(inode)->rsrc_inode;
	अगर (!(file->f_flags & O_LARGEखाता) && i_size_पढ़ो(inode) > MAX_NON_LFS)
		वापस -EOVERFLOW;
	atomic_inc(&HFSPLUS_I(inode)->खोलोcnt);
	वापस 0;
पूर्ण

अटल पूर्णांक hfsplus_file_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा super_block *sb = inode->i_sb;

	अगर (HFSPLUS_IS_RSRC(inode))
		inode = HFSPLUS_I(inode)->rsrc_inode;
	अगर (atomic_dec_and_test(&HFSPLUS_I(inode)->खोलोcnt)) अणु
		inode_lock(inode);
		hfsplus_file_truncate(inode);
		अगर (inode->i_flags & S_DEAD) अणु
			hfsplus_delete_cat(inode->i_ino,
					   HFSPLUS_SB(sb)->hidden_dir, शून्य);
			hfsplus_delete_inode(inode);
		पूर्ण
		inode_unlock(inode);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hfsplus_setattr(काष्ठा user_namespace *mnt_userns,
			   काष्ठा dentry *dentry, काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक error;

	error = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (error)
		वापस error;

	अगर ((attr->ia_valid & ATTR_SIZE) &&
	    attr->ia_size != i_size_पढ़ो(inode)) अणु
		inode_dio_रुको(inode);
		अगर (attr->ia_size > inode->i_size) अणु
			error = generic_cont_expand_simple(inode,
							   attr->ia_size);
			अगर (error)
				वापस error;
		पूर्ण
		truncate_setsize(inode, attr->ia_size);
		hfsplus_file_truncate(inode);
		inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	पूर्ण

	setattr_copy(&init_user_ns, inode, attr);
	mark_inode_dirty(inode);

	वापस 0;
पूर्ण

पूर्णांक hfsplus_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		    काष्ठा kstat *stat, u32 request_mask,
		    अचिन्हित पूर्णांक query_flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	काष्ठा hfsplus_inode_info *hip = HFSPLUS_I(inode);

	अगर (inode->i_flags & S_APPEND)
		stat->attributes |= STATX_ATTR_APPEND;
	अगर (inode->i_flags & S_IMMUTABLE)
		stat->attributes |= STATX_ATTR_IMMUTABLE;
	अगर (hip->userflags & HFSPLUS_FLG_NODUMP)
		stat->attributes |= STATX_ATTR_NODUMP;

	stat->attributes_mask |= STATX_ATTR_APPEND | STATX_ATTR_IMMUTABLE |
				 STATX_ATTR_NODUMP;

	generic_fillattr(&init_user_ns, inode, stat);
	वापस 0;
पूर्ण

पूर्णांक hfsplus_file_fsync(काष्ठा file *file, loff_t start, loff_t end,
		       पूर्णांक datasync)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा hfsplus_inode_info *hip = HFSPLUS_I(inode);
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(inode->i_sb);
	पूर्णांक error = 0, error2;

	error = file_ग_लिखो_and_रुको_range(file, start, end);
	अगर (error)
		वापस error;
	inode_lock(inode);

	/*
	 * Sync inode metadata पूर्णांकo the catalog and extent trees.
	 */
	sync_inode_metadata(inode, 1);

	/*
	 * And explicitly ग_लिखो out the btrees.
	 */
	अगर (test_and_clear_bit(HFSPLUS_I_CAT_सूचीTY, &hip->flags))
		error = filemap_ग_लिखो_and_रुको(sbi->cat_tree->inode->i_mapping);

	अगर (test_and_clear_bit(HFSPLUS_I_EXT_सूचीTY, &hip->flags)) अणु
		error2 =
			filemap_ग_लिखो_and_रुको(sbi->ext_tree->inode->i_mapping);
		अगर (!error)
			error = error2;
	पूर्ण

	अगर (test_and_clear_bit(HFSPLUS_I_ATTR_सूचीTY, &hip->flags)) अणु
		अगर (sbi->attr_tree) अणु
			error2 =
				filemap_ग_लिखो_and_रुको(
					    sbi->attr_tree->inode->i_mapping);
			अगर (!error)
				error = error2;
		पूर्ण अन्यथा अणु
			pr_err("sync non-existent attributes tree\n");
		पूर्ण
	पूर्ण

	अगर (test_and_clear_bit(HFSPLUS_I_ALLOC_सूचीTY, &hip->flags)) अणु
		error2 = filemap_ग_लिखो_and_रुको(sbi->alloc_file->i_mapping);
		अगर (!error)
			error = error2;
	पूर्ण

	अगर (!test_bit(HFSPLUS_SB_NOBARRIER, &sbi->flags))
		blkdev_issue_flush(inode->i_sb->s_bdev);

	inode_unlock(inode);

	वापस error;
पूर्ण

अटल स्थिर काष्ठा inode_operations hfsplus_file_inode_operations = अणु
	.setattr	= hfsplus_setattr,
	.getattr	= hfsplus_getattr,
	.listxattr	= hfsplus_listxattr,
	.fileattr_get	= hfsplus_fileattr_get,
	.fileattr_set	= hfsplus_fileattr_set,
पूर्ण;

अटल स्थिर काष्ठा file_operations hfsplus_file_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो_iter	= generic_file_पढ़ो_iter,
	.ग_लिखो_iter	= generic_file_ग_लिखो_iter,
	.mmap		= generic_file_mmap,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.fsync		= hfsplus_file_fsync,
	.खोलो		= hfsplus_file_खोलो,
	.release	= hfsplus_file_release,
	.unlocked_ioctl = hfsplus_ioctl,
पूर्ण;

काष्ठा inode *hfsplus_new_inode(काष्ठा super_block *sb, काष्ठा inode *dir,
				umode_t mode)
अणु
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(sb);
	काष्ठा inode *inode = new_inode(sb);
	काष्ठा hfsplus_inode_info *hip;

	अगर (!inode)
		वापस शून्य;

	inode->i_ino = sbi->next_cnid++;
	inode_init_owner(&init_user_ns, inode, dir, mode);
	set_nlink(inode, 1);
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);

	hip = HFSPLUS_I(inode);
	INIT_LIST_HEAD(&hip->खोलो_dir_list);
	spin_lock_init(&hip->खोलो_dir_lock);
	mutex_init(&hip->extents_lock);
	atomic_set(&hip->खोलोcnt, 0);
	hip->extent_state = 0;
	hip->flags = 0;
	hip->userflags = 0;
	hip->subfolders = 0;
	स_रखो(hip->first_extents, 0, माप(hfsplus_extent_rec));
	स_रखो(hip->cached_extents, 0, माप(hfsplus_extent_rec));
	hip->alloc_blocks = 0;
	hip->first_blocks = 0;
	hip->cached_start = 0;
	hip->cached_blocks = 0;
	hip->phys_size = 0;
	hip->fs_blocks = 0;
	hip->rsrc_inode = शून्य;
	अगर (S_ISसूची(inode->i_mode)) अणु
		inode->i_size = 2;
		sbi->folder_count++;
		inode->i_op = &hfsplus_dir_inode_operations;
		inode->i_fop = &hfsplus_dir_operations;
	पूर्ण अन्यथा अगर (S_ISREG(inode->i_mode)) अणु
		sbi->file_count++;
		inode->i_op = &hfsplus_file_inode_operations;
		inode->i_fop = &hfsplus_file_operations;
		inode->i_mapping->a_ops = &hfsplus_aops;
		hip->clump_blocks = sbi->data_clump_blocks;
	पूर्ण अन्यथा अगर (S_ISLNK(inode->i_mode)) अणु
		sbi->file_count++;
		inode->i_op = &page_symlink_inode_operations;
		inode_nohighmem(inode);
		inode->i_mapping->a_ops = &hfsplus_aops;
		hip->clump_blocks = 1;
	पूर्ण अन्यथा
		sbi->file_count++;
	insert_inode_hash(inode);
	mark_inode_dirty(inode);
	hfsplus_mark_mdb_dirty(sb);

	वापस inode;
पूर्ण

व्योम hfsplus_delete_inode(काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;

	अगर (S_ISसूची(inode->i_mode)) अणु
		HFSPLUS_SB(sb)->folder_count--;
		hfsplus_mark_mdb_dirty(sb);
		वापस;
	पूर्ण
	HFSPLUS_SB(sb)->file_count--;
	अगर (S_ISREG(inode->i_mode)) अणु
		अगर (!inode->i_nlink) अणु
			inode->i_size = 0;
			hfsplus_file_truncate(inode);
		पूर्ण
	पूर्ण अन्यथा अगर (S_ISLNK(inode->i_mode)) अणु
		inode->i_size = 0;
		hfsplus_file_truncate(inode);
	पूर्ण
	hfsplus_mark_mdb_dirty(sb);
पूर्ण

व्योम hfsplus_inode_पढ़ो_विभाजन(काष्ठा inode *inode, काष्ठा hfsplus_विभाजन_raw *विभाजन)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(sb);
	काष्ठा hfsplus_inode_info *hip = HFSPLUS_I(inode);
	u32 count;
	पूर्णांक i;

	स_नकल(&hip->first_extents, &विभाजन->extents, माप(hfsplus_extent_rec));
	क्रम (count = 0, i = 0; i < 8; i++)
		count += be32_to_cpu(विभाजन->extents[i].block_count);
	hip->first_blocks = count;
	स_रखो(hip->cached_extents, 0, माप(hfsplus_extent_rec));
	hip->cached_start = 0;
	hip->cached_blocks = 0;

	hip->alloc_blocks = be32_to_cpu(विभाजन->total_blocks);
	hip->phys_size = inode->i_size = be64_to_cpu(विभाजन->total_size);
	hip->fs_blocks =
		(inode->i_size + sb->s_blocksize - 1) >> sb->s_blocksize_bits;
	inode_set_bytes(inode, hip->fs_blocks << sb->s_blocksize_bits);
	hip->clump_blocks =
		be32_to_cpu(विभाजन->clump_size) >> sbi->alloc_blksz_shअगरt;
	अगर (!hip->clump_blocks) अणु
		hip->clump_blocks = HFSPLUS_IS_RSRC(inode) ?
			sbi->rsrc_clump_blocks :
			sbi->data_clump_blocks;
	पूर्ण
पूर्ण

व्योम hfsplus_inode_ग_लिखो_विभाजन(काष्ठा inode *inode,
		काष्ठा hfsplus_विभाजन_raw *विभाजन)
अणु
	स_नकल(&विभाजन->extents, &HFSPLUS_I(inode)->first_extents,
	       माप(hfsplus_extent_rec));
	विभाजन->total_size = cpu_to_be64(inode->i_size);
	विभाजन->total_blocks = cpu_to_be32(HFSPLUS_I(inode)->alloc_blocks);
पूर्ण

पूर्णांक hfsplus_cat_पढ़ो_inode(काष्ठा inode *inode, काष्ठा hfs_find_data *fd)
अणु
	hfsplus_cat_entry entry;
	पूर्णांक res = 0;
	u16 type;

	type = hfs_bnode_पढ़ो_u16(fd->bnode, fd->entryoffset);

	HFSPLUS_I(inode)->linkid = 0;
	अगर (type == HFSPLUS_FOLDER) अणु
		काष्ठा hfsplus_cat_folder *folder = &entry.folder;

		अगर (fd->entrylength < माप(काष्ठा hfsplus_cat_folder))
			/* panic? */;
		hfs_bnode_पढ़ो(fd->bnode, &entry, fd->entryoffset,
					माप(काष्ठा hfsplus_cat_folder));
		hfsplus_get_perms(inode, &folder->permissions, 1);
		set_nlink(inode, 1);
		inode->i_size = 2 + be32_to_cpu(folder->valence);
		inode->i_aसमय = hfsp_mt2ut(folder->access_date);
		inode->i_mसमय = hfsp_mt2ut(folder->content_mod_date);
		inode->i_स_समय = hfsp_mt2ut(folder->attribute_mod_date);
		HFSPLUS_I(inode)->create_date = folder->create_date;
		HFSPLUS_I(inode)->fs_blocks = 0;
		अगर (folder->flags & cpu_to_be16(HFSPLUS_HAS_FOLDER_COUNT)) अणु
			HFSPLUS_I(inode)->subfolders =
				be32_to_cpu(folder->subfolders);
		पूर्ण
		inode->i_op = &hfsplus_dir_inode_operations;
		inode->i_fop = &hfsplus_dir_operations;
	पूर्ण अन्यथा अगर (type == HFSPLUS_खाता) अणु
		काष्ठा hfsplus_cat_file *file = &entry.file;

		अगर (fd->entrylength < माप(काष्ठा hfsplus_cat_file))
			/* panic? */;
		hfs_bnode_पढ़ो(fd->bnode, &entry, fd->entryoffset,
					माप(काष्ठा hfsplus_cat_file));

		hfsplus_inode_पढ़ो_विभाजन(inode, HFSPLUS_IS_RSRC(inode) ?
					&file->rsrc_विभाजन : &file->data_विभाजन);
		hfsplus_get_perms(inode, &file->permissions, 0);
		set_nlink(inode, 1);
		अगर (S_ISREG(inode->i_mode)) अणु
			अगर (file->permissions.dev)
				set_nlink(inode,
					  be32_to_cpu(file->permissions.dev));
			inode->i_op = &hfsplus_file_inode_operations;
			inode->i_fop = &hfsplus_file_operations;
			inode->i_mapping->a_ops = &hfsplus_aops;
		पूर्ण अन्यथा अगर (S_ISLNK(inode->i_mode)) अणु
			inode->i_op = &page_symlink_inode_operations;
			inode_nohighmem(inode);
			inode->i_mapping->a_ops = &hfsplus_aops;
		पूर्ण अन्यथा अणु
			init_special_inode(inode, inode->i_mode,
					   be32_to_cpu(file->permissions.dev));
		पूर्ण
		inode->i_aसमय = hfsp_mt2ut(file->access_date);
		inode->i_mसमय = hfsp_mt2ut(file->content_mod_date);
		inode->i_स_समय = hfsp_mt2ut(file->attribute_mod_date);
		HFSPLUS_I(inode)->create_date = file->create_date;
	पूर्ण अन्यथा अणु
		pr_err("bad catalog entry used to create inode\n");
		res = -EIO;
	पूर्ण
	वापस res;
पूर्ण

पूर्णांक hfsplus_cat_ग_लिखो_inode(काष्ठा inode *inode)
अणु
	काष्ठा inode *मुख्य_inode = inode;
	काष्ठा hfs_find_data fd;
	hfsplus_cat_entry entry;

	अगर (HFSPLUS_IS_RSRC(inode))
		मुख्य_inode = HFSPLUS_I(inode)->rsrc_inode;

	अगर (!मुख्य_inode->i_nlink)
		वापस 0;

	अगर (hfs_find_init(HFSPLUS_SB(मुख्य_inode->i_sb)->cat_tree, &fd))
		/* panic? */
		वापस -EIO;

	अगर (hfsplus_find_cat(मुख्य_inode->i_sb, मुख्य_inode->i_ino, &fd))
		/* panic? */
		जाओ out;

	अगर (S_ISसूची(मुख्य_inode->i_mode)) अणु
		काष्ठा hfsplus_cat_folder *folder = &entry.folder;

		अगर (fd.entrylength < माप(काष्ठा hfsplus_cat_folder))
			/* panic? */;
		hfs_bnode_पढ़ो(fd.bnode, &entry, fd.entryoffset,
					माप(काष्ठा hfsplus_cat_folder));
		/* simple node checks? */
		hfsplus_cat_set_perms(inode, &folder->permissions);
		folder->access_date = hfsp_ut2mt(inode->i_aसमय);
		folder->content_mod_date = hfsp_ut2mt(inode->i_mसमय);
		folder->attribute_mod_date = hfsp_ut2mt(inode->i_स_समय);
		folder->valence = cpu_to_be32(inode->i_size - 2);
		अगर (folder->flags & cpu_to_be16(HFSPLUS_HAS_FOLDER_COUNT)) अणु
			folder->subfolders =
				cpu_to_be32(HFSPLUS_I(inode)->subfolders);
		पूर्ण
		hfs_bnode_ग_लिखो(fd.bnode, &entry, fd.entryoffset,
					 माप(काष्ठा hfsplus_cat_folder));
	पूर्ण अन्यथा अगर (HFSPLUS_IS_RSRC(inode)) अणु
		काष्ठा hfsplus_cat_file *file = &entry.file;
		hfs_bnode_पढ़ो(fd.bnode, &entry, fd.entryoffset,
			       माप(काष्ठा hfsplus_cat_file));
		hfsplus_inode_ग_लिखो_विभाजन(inode, &file->rsrc_विभाजन);
		hfs_bnode_ग_लिखो(fd.bnode, &entry, fd.entryoffset,
				माप(काष्ठा hfsplus_cat_file));
	पूर्ण अन्यथा अणु
		काष्ठा hfsplus_cat_file *file = &entry.file;

		अगर (fd.entrylength < माप(काष्ठा hfsplus_cat_file))
			/* panic? */;
		hfs_bnode_पढ़ो(fd.bnode, &entry, fd.entryoffset,
					माप(काष्ठा hfsplus_cat_file));
		hfsplus_inode_ग_लिखो_विभाजन(inode, &file->data_विभाजन);
		hfsplus_cat_set_perms(inode, &file->permissions);
		अगर (HFSPLUS_FLG_IMMUTABLE &
				(file->permissions.rootflags |
					file->permissions.userflags))
			file->flags |= cpu_to_be16(HFSPLUS_खाता_LOCKED);
		अन्यथा
			file->flags &= cpu_to_be16(~HFSPLUS_खाता_LOCKED);
		file->access_date = hfsp_ut2mt(inode->i_aसमय);
		file->content_mod_date = hfsp_ut2mt(inode->i_mसमय);
		file->attribute_mod_date = hfsp_ut2mt(inode->i_स_समय);
		hfs_bnode_ग_लिखो(fd.bnode, &entry, fd.entryoffset,
					 माप(काष्ठा hfsplus_cat_file));
	पूर्ण

	set_bit(HFSPLUS_I_CAT_सूचीTY, &HFSPLUS_I(inode)->flags);
out:
	hfs_find_निकास(&fd);
	वापस 0;
पूर्ण

पूर्णांक hfsplus_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा hfsplus_inode_info *hip = HFSPLUS_I(inode);
	अचिन्हित पूर्णांक flags = 0;

	अगर (inode->i_flags & S_IMMUTABLE)
		flags |= FS_IMMUTABLE_FL;
	अगर (inode->i_flags & S_APPEND)
		flags |= FS_APPEND_FL;
	अगर (hip->userflags & HFSPLUS_FLG_NODUMP)
		flags |= FS_NODUMP_FL;

	fileattr_fill_flags(fa, flags);

	वापस 0;
पूर्ण

पूर्णांक hfsplus_fileattr_set(काष्ठा user_namespace *mnt_userns,
			 काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा hfsplus_inode_info *hip = HFSPLUS_I(inode);
	अचिन्हित पूर्णांक new_fl = 0;

	अगर (fileattr_has_fsx(fa))
		वापस -EOPNOTSUPP;

	/* करोn't silently ignore unsupported ext2 flags */
	अगर (fa->flags & ~(FS_IMMUTABLE_FL|FS_APPEND_FL|FS_NODUMP_FL))
		वापस -EOPNOTSUPP;

	अगर (fa->flags & FS_IMMUTABLE_FL)
		new_fl |= S_IMMUTABLE;

	अगर (fa->flags & FS_APPEND_FL)
		new_fl |= S_APPEND;

	inode_set_flags(inode, new_fl, S_IMMUTABLE | S_APPEND);

	अगर (fa->flags & FS_NODUMP_FL)
		hip->userflags |= HFSPLUS_FLG_NODUMP;
	अन्यथा
		hip->userflags &= ~HFSPLUS_FLG_NODUMP;

	inode->i_स_समय = current_समय(inode);
	mark_inode_dirty(inode);

	वापस 0;
पूर्ण
