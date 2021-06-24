<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/f2fs/file.c
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 */
#समावेश <linux/fs.h>
#समावेश <linux/f2fs_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/buffer_head.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/types.h>
#समावेश <linux/compat.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mount.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/uपन.स>
#समावेश <linux/uuid.h>
#समावेश <linux/file.h>
#समावेश <linux/nls.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/fileattr.h>

#समावेश "f2fs.h"
#समावेश "node.h"
#समावेश "segment.h"
#समावेश "xattr.h"
#समावेश "acl.h"
#समावेश "gc.h"
#समावेश <trace/events/f2fs.h>
#समावेश <uapi/linux/f2fs.h>

अटल vm_fault_t f2fs_filemap_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा inode *inode = file_inode(vmf->vma->vm_file);
	vm_fault_t ret;

	करोwn_पढ़ो(&F2FS_I(inode)->i_mmap_sem);
	ret = filemap_fault(vmf);
	up_पढ़ो(&F2FS_I(inode)->i_mmap_sem);

	अगर (!ret)
		f2fs_update_iostat(F2FS_I_SB(inode), APP_MAPPED_READ_IO,
							F2FS_BLKSIZE);

	trace_f2fs_filemap_fault(inode, vmf->pgoff, (अचिन्हित दीर्घ)ret);

	वापस ret;
पूर्ण

अटल vm_fault_t f2fs_vm_page_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	काष्ठा page *page = vmf->page;
	काष्ठा inode *inode = file_inode(vmf->vma->vm_file);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा dnode_of_data dn;
	bool need_alloc = true;
	पूर्णांक err = 0;

	अगर (unlikely(IS_IMMUTABLE(inode)))
		वापस VM_FAULT_SIGBUS;

	अगर (unlikely(f2fs_cp_error(sbi))) अणु
		err = -EIO;
		जाओ err;
	पूर्ण

	अगर (!f2fs_is_checkpoपूर्णांक_पढ़ोy(sbi)) अणु
		err = -ENOSPC;
		जाओ err;
	पूर्ण

	err = f2fs_convert_अंतरभूत_inode(inode);
	अगर (err)
		जाओ err;

#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
	अगर (f2fs_compressed_file(inode)) अणु
		पूर्णांक ret = f2fs_is_compressed_cluster(inode, page->index);

		अगर (ret < 0) अणु
			err = ret;
			जाओ err;
		पूर्ण अन्यथा अगर (ret) अणु
			अगर (ret < F2FS_I(inode)->i_cluster_size) अणु
				err = -EAGAIN;
				जाओ err;
			पूर्ण
			need_alloc = false;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	/* should करो out of any locked page */
	अगर (need_alloc)
		f2fs_balance_fs(sbi, true);

	sb_start_pagefault(inode->i_sb);

	f2fs_bug_on(sbi, f2fs_has_अंतरभूत_data(inode));

	file_update_समय(vmf->vma->vm_file);
	करोwn_पढ़ो(&F2FS_I(inode)->i_mmap_sem);
	lock_page(page);
	अगर (unlikely(page->mapping != inode->i_mapping ||
			page_offset(page) > i_size_पढ़ो(inode) ||
			!PageUptodate(page))) अणु
		unlock_page(page);
		err = -EFAULT;
		जाओ out_sem;
	पूर्ण

	अगर (need_alloc) अणु
		/* block allocation */
		f2fs_करो_map_lock(sbi, F2FS_GET_BLOCK_PRE_AIO, true);
		set_new_dnode(&dn, inode, शून्य, शून्य, 0);
		err = f2fs_get_block(&dn, page->index);
		f2fs_put_dnode(&dn);
		f2fs_करो_map_lock(sbi, F2FS_GET_BLOCK_PRE_AIO, false);
	पूर्ण

#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
	अगर (!need_alloc) अणु
		set_new_dnode(&dn, inode, शून्य, शून्य, 0);
		err = f2fs_get_dnode_of_data(&dn, page->index, LOOKUP_NODE);
		f2fs_put_dnode(&dn);
	पूर्ण
#पूर्ण_अगर
	अगर (err) अणु
		unlock_page(page);
		जाओ out_sem;
	पूर्ण

	f2fs_रुको_on_page_ग_लिखोback(page, DATA, false, true);

	/* रुको क्रम GCed page ग_लिखोback via META_MAPPING */
	f2fs_रुको_on_block_ग_लिखोback(inode, dn.data_blkaddr);

	/*
	 * check to see अगर the page is mapped alपढ़ोy (no holes)
	 */
	अगर (PageMappedToDisk(page))
		जाओ out_sem;

	/* page is wholly or partially inside खातापूर्ण */
	अगर (((loff_t)(page->index + 1) << PAGE_SHIFT) >
						i_size_पढ़ो(inode)) अणु
		loff_t offset;

		offset = i_size_पढ़ो(inode) & ~PAGE_MASK;
		zero_user_segment(page, offset, PAGE_SIZE);
	पूर्ण
	set_page_dirty(page);
	अगर (!PageUptodate(page))
		SetPageUptodate(page);

	f2fs_update_iostat(sbi, APP_MAPPED_IO, F2FS_BLKSIZE);
	f2fs_update_समय(sbi, REQ_TIME);

	trace_f2fs_vm_page_mkग_लिखो(page, DATA);
out_sem:
	up_पढ़ो(&F2FS_I(inode)->i_mmap_sem);

	sb_end_pagefault(inode->i_sb);
err:
	वापस block_page_mkग_लिखो_वापस(err);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा f2fs_file_vm_ops = अणु
	.fault		= f2fs_filemap_fault,
	.map_pages	= filemap_map_pages,
	.page_mkग_लिखो	= f2fs_vm_page_mkग_लिखो,
पूर्ण;

अटल पूर्णांक get_parent_ino(काष्ठा inode *inode, nid_t *pino)
अणु
	काष्ठा dentry *dentry;

	/*
	 * Make sure to get the non-deleted alias.  The alias associated with
	 * the खोलो file descriptor being fsync()'ed may be deleted alपढ़ोy.
	 */
	dentry = d_find_alias(inode);
	अगर (!dentry)
		वापस 0;

	*pino = parent_ino(dentry);
	dput(dentry);
	वापस 1;
पूर्ण

अटल अंतरभूत क्रमागत cp_reason_type need_करो_checkpoपूर्णांक(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	क्रमागत cp_reason_type cp_reason = CP_NO_NEEDED;

	अगर (!S_ISREG(inode->i_mode))
		cp_reason = CP_NON_REGULAR;
	अन्यथा अगर (f2fs_compressed_file(inode))
		cp_reason = CP_COMPRESSED;
	अन्यथा अगर (inode->i_nlink != 1)
		cp_reason = CP_HARDLINK;
	अन्यथा अगर (is_sbi_flag_set(sbi, SBI_NEED_CP))
		cp_reason = CP_SB_NEED_CP;
	अन्यथा अगर (file_wrong_pino(inode))
		cp_reason = CP_WRONG_PINO;
	अन्यथा अगर (!f2fs_space_क्रम_roll_क्रमward(sbi))
		cp_reason = CP_NO_SPC_ROLL;
	अन्यथा अगर (!f2fs_is_checkpoपूर्णांकed_node(sbi, F2FS_I(inode)->i_pino))
		cp_reason = CP_NODE_NEED_CP;
	अन्यथा अगर (test_opt(sbi, FASTBOOT))
		cp_reason = CP_FASTBOOT_MODE;
	अन्यथा अगर (F2FS_OPTION(sbi).active_logs == 2)
		cp_reason = CP_SPEC_LOG_NUM;
	अन्यथा अगर (F2FS_OPTION(sbi).fsync_mode == FSYNC_MODE_STRICT &&
		f2fs_need_dentry_mark(sbi, inode->i_ino) &&
		f2fs_exist_written_data(sbi, F2FS_I(inode)->i_pino,
							TRANS_सूची_INO))
		cp_reason = CP_RECOVER_सूची;

	वापस cp_reason;
पूर्ण

अटल bool need_inode_page_update(काष्ठा f2fs_sb_info *sbi, nid_t ino)
अणु
	काष्ठा page *i = find_get_page(NODE_MAPPING(sbi), ino);
	bool ret = false;
	/* But we need to aव्योम that there are some inode updates */
	अगर ((i && PageDirty(i)) || f2fs_need_inode_block_update(sbi, ino))
		ret = true;
	f2fs_put_page(i, 0);
	वापस ret;
पूर्ण

अटल व्योम try_to_fix_pino(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_inode_info *fi = F2FS_I(inode);
	nid_t pino;

	करोwn_ग_लिखो(&fi->i_sem);
	अगर (file_wrong_pino(inode) && inode->i_nlink == 1 &&
			get_parent_ino(inode, &pino)) अणु
		f2fs_i_pino_ग_लिखो(inode, pino);
		file_got_pino(inode);
	पूर्ण
	up_ग_लिखो(&fi->i_sem);
पूर्ण

अटल पूर्णांक f2fs_करो_sync_file(काष्ठा file *file, loff_t start, loff_t end,
						पूर्णांक datasync, bool atomic)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	nid_t ino = inode->i_ino;
	पूर्णांक ret = 0;
	क्रमागत cp_reason_type cp_reason = 0;
	काष्ठा ग_लिखोback_control wbc = अणु
		.sync_mode = WB_SYNC_ALL,
		.nr_to_ग_लिखो = दीर्घ_उच्च,
		.क्रम_reclaim = 0,
	पूर्ण;
	अचिन्हित पूर्णांक seq_id = 0;

	अगर (unlikely(f2fs_पढ़ोonly(inode->i_sb) ||
				is_sbi_flag_set(sbi, SBI_CP_DISABLED)))
		वापस 0;

	trace_f2fs_sync_file_enter(inode);

	अगर (S_ISसूची(inode->i_mode))
		जाओ go_ग_लिखो;

	/* अगर fdatasync is triggered, let's करो in-place-update */
	अगर (datasync || get_dirty_pages(inode) <= SM_I(sbi)->min_fsync_blocks)
		set_inode_flag(inode, FI_NEED_IPU);
	ret = file_ग_लिखो_and_रुको_range(file, start, end);
	clear_inode_flag(inode, FI_NEED_IPU);

	अगर (ret) अणु
		trace_f2fs_sync_file_निकास(inode, cp_reason, datasync, ret);
		वापस ret;
	पूर्ण

	/* अगर the inode is dirty, let's recover all the समय */
	अगर (!f2fs_skip_inode_update(inode, datasync)) अणु
		f2fs_ग_लिखो_inode(inode, शून्य);
		जाओ go_ग_लिखो;
	पूर्ण

	/*
	 * अगर there is no written data, करोn't waste समय to ग_लिखो recovery info.
	 */
	अगर (!is_inode_flag_set(inode, FI_APPEND_WRITE) &&
			!f2fs_exist_written_data(sbi, ino, APPEND_INO)) अणु

		/* it may call ग_लिखो_inode just prior to fsync */
		अगर (need_inode_page_update(sbi, ino))
			जाओ go_ग_लिखो;

		अगर (is_inode_flag_set(inode, FI_UPDATE_WRITE) ||
				f2fs_exist_written_data(sbi, ino, UPDATE_INO))
			जाओ flush_out;
		जाओ out;
	पूर्ण
go_ग_लिखो:
	/*
	 * Both of fdatasync() and fsync() are able to be recovered from
	 * sudden-घातer-off.
	 */
	करोwn_पढ़ो(&F2FS_I(inode)->i_sem);
	cp_reason = need_करो_checkpoपूर्णांक(inode);
	up_पढ़ो(&F2FS_I(inode)->i_sem);

	अगर (cp_reason) अणु
		/* all the dirty node pages should be flushed क्रम POR */
		ret = f2fs_sync_fs(inode->i_sb, 1);

		/*
		 * We've secured consistency through sync_fs. Following pino
		 * will be used only क्रम fsynced inodes after checkpoपूर्णांक.
		 */
		try_to_fix_pino(inode);
		clear_inode_flag(inode, FI_APPEND_WRITE);
		clear_inode_flag(inode, FI_UPDATE_WRITE);
		जाओ out;
	पूर्ण
sync_nodes:
	atomic_inc(&sbi->wb_sync_req[NODE]);
	ret = f2fs_fsync_node_pages(sbi, inode, &wbc, atomic, &seq_id);
	atomic_dec(&sbi->wb_sync_req[NODE]);
	अगर (ret)
		जाओ out;

	/* अगर cp_error was enabled, we should aव्योम infinite loop */
	अगर (unlikely(f2fs_cp_error(sbi))) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (f2fs_need_inode_block_update(sbi, ino)) अणु
		f2fs_mark_inode_dirty_sync(inode, true);
		f2fs_ग_लिखो_inode(inode, शून्य);
		जाओ sync_nodes;
	पूर्ण

	/*
	 * If it's atomic_write, it's just fine to keep ग_लिखो ordering. So
	 * here we करोn't need to रुको क्रम node ग_लिखो completion, since we use
	 * node chain which serializes node blocks. If one of node ग_लिखोs are
	 * reordered, we can see simply broken chain, resulting in stopping
	 * roll-क्रमward recovery. It means we'll recover all or none node blocks
	 * given fsync mark.
	 */
	अगर (!atomic) अणु
		ret = f2fs_रुको_on_node_pages_ग_लिखोback(sbi, seq_id);
		अगर (ret)
			जाओ out;
	पूर्ण

	/* once recovery info is written, करोn't need to tack this */
	f2fs_हटाओ_ino_entry(sbi, ino, APPEND_INO);
	clear_inode_flag(inode, FI_APPEND_WRITE);
flush_out:
	अगर (!atomic && F2FS_OPTION(sbi).fsync_mode != FSYNC_MODE_NOBARRIER)
		ret = f2fs_issue_flush(sbi, inode->i_ino);
	अगर (!ret) अणु
		f2fs_हटाओ_ino_entry(sbi, ino, UPDATE_INO);
		clear_inode_flag(inode, FI_UPDATE_WRITE);
		f2fs_हटाओ_ino_entry(sbi, ino, FLUSH_INO);
	पूर्ण
	f2fs_update_समय(sbi, REQ_TIME);
out:
	trace_f2fs_sync_file_निकास(inode, cp_reason, datasync, ret);
	वापस ret;
पूर्ण

पूर्णांक f2fs_sync_file(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	अगर (unlikely(f2fs_cp_error(F2FS_I_SB(file_inode(file)))))
		वापस -EIO;
	वापस f2fs_करो_sync_file(file, start, end, datasync, false);
पूर्ण

अटल bool __found_offset(काष्ठा address_space *mapping, block_t blkaddr,
				pgoff_t index, पूर्णांक whence)
अणु
	चयन (whence) अणु
	हाल SEEK_DATA:
		अगर (__is_valid_data_blkaddr(blkaddr))
			वापस true;
		अगर (blkaddr == NEW_ADDR &&
		    xa_get_mark(&mapping->i_pages, index, PAGECACHE_TAG_सूचीTY))
			वापस true;
		अवरोध;
	हाल SEEK_HOLE:
		अगर (blkaddr == शून्य_ADDR)
			वापस true;
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

अटल loff_t f2fs_seek_block(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	loff_t maxbytes = inode->i_sb->s_maxbytes;
	काष्ठा dnode_of_data dn;
	pgoff_t pgofs, end_offset;
	loff_t data_ofs = offset;
	loff_t isize;
	पूर्णांक err = 0;

	inode_lock(inode);

	isize = i_size_पढ़ो(inode);
	अगर (offset >= isize)
		जाओ fail;

	/* handle अंतरभूत data हाल */
	अगर (f2fs_has_अंतरभूत_data(inode)) अणु
		अगर (whence == SEEK_HOLE) अणु
			data_ofs = isize;
			जाओ found;
		पूर्ण अन्यथा अगर (whence == SEEK_DATA) अणु
			data_ofs = offset;
			जाओ found;
		पूर्ण
	पूर्ण

	pgofs = (pgoff_t)(offset >> PAGE_SHIFT);

	क्रम (; data_ofs < isize; data_ofs = (loff_t)pgofs << PAGE_SHIFT) अणु
		set_new_dnode(&dn, inode, शून्य, शून्य, 0);
		err = f2fs_get_dnode_of_data(&dn, pgofs, LOOKUP_NODE);
		अगर (err && err != -ENOENT) अणु
			जाओ fail;
		पूर्ण अन्यथा अगर (err == -ENOENT) अणु
			/* direct node करोes not exists */
			अगर (whence == SEEK_DATA) अणु
				pgofs = f2fs_get_next_page_offset(&dn, pgofs);
				जारी;
			पूर्ण अन्यथा अणु
				जाओ found;
			पूर्ण
		पूर्ण

		end_offset = ADDRS_PER_PAGE(dn.node_page, inode);

		/* find data/hole in dnode block */
		क्रम (; dn.ofs_in_node < end_offset;
				dn.ofs_in_node++, pgofs++,
				data_ofs = (loff_t)pgofs << PAGE_SHIFT) अणु
			block_t blkaddr;

			blkaddr = f2fs_data_blkaddr(&dn);

			अगर (__is_valid_data_blkaddr(blkaddr) &&
				!f2fs_is_valid_blkaddr(F2FS_I_SB(inode),
					blkaddr, DATA_GENERIC_ENHANCE)) अणु
				f2fs_put_dnode(&dn);
				जाओ fail;
			पूर्ण

			अगर (__found_offset(file->f_mapping, blkaddr,
							pgofs, whence)) अणु
				f2fs_put_dnode(&dn);
				जाओ found;
			पूर्ण
		पूर्ण
		f2fs_put_dnode(&dn);
	पूर्ण

	अगर (whence == SEEK_DATA)
		जाओ fail;
found:
	अगर (whence == SEEK_HOLE && data_ofs > isize)
		data_ofs = isize;
	inode_unlock(inode);
	वापस vfs_setpos(file, data_ofs, maxbytes);
fail:
	inode_unlock(inode);
	वापस -ENXIO;
पूर्ण

अटल loff_t f2fs_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	loff_t maxbytes = inode->i_sb->s_maxbytes;

	अगर (f2fs_compressed_file(inode))
		maxbytes = max_file_blocks(inode) << F2FS_BLKSIZE_BITS;

	चयन (whence) अणु
	हाल शुरू_से:
	हाल प्रस्तुत_से:
	हाल अंत_से:
		वापस generic_file_llseek_size(file, offset, whence,
						maxbytes, i_size_पढ़ो(inode));
	हाल SEEK_DATA:
	हाल SEEK_HOLE:
		अगर (offset < 0)
			वापस -ENXIO;
		वापस f2fs_seek_block(file, offset, whence);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक f2fs_file_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा inode *inode = file_inode(file);

	अगर (unlikely(f2fs_cp_error(F2FS_I_SB(inode))))
		वापस -EIO;

	अगर (!f2fs_is_compress_backend_पढ़ोy(inode))
		वापस -EOPNOTSUPP;

	file_accessed(file);
	vma->vm_ops = &f2fs_file_vm_ops;
	set_inode_flag(inode, FI_MMAP_खाता);
	वापस 0;
पूर्ण

अटल पूर्णांक f2fs_file_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक err = fscrypt_file_खोलो(inode, filp);

	अगर (err)
		वापस err;

	अगर (!f2fs_is_compress_backend_पढ़ोy(inode))
		वापस -EOPNOTSUPP;

	err = fsverity_file_खोलो(inode, filp);
	अगर (err)
		वापस err;

	filp->f_mode |= FMODE_NOWAIT;

	वापस dquot_file_खोलो(inode, filp);
पूर्ण

व्योम f2fs_truncate_data_blocks_range(काष्ठा dnode_of_data *dn, पूर्णांक count)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dn->inode);
	काष्ठा f2fs_node *raw_node;
	पूर्णांक nr_मुक्त = 0, ofs = dn->ofs_in_node, len = count;
	__le32 *addr;
	पूर्णांक base = 0;
	bool compressed_cluster = false;
	पूर्णांक cluster_index = 0, valid_blocks = 0;
	पूर्णांक cluster_size = F2FS_I(dn->inode)->i_cluster_size;
	bool released = !atomic_पढ़ो(&F2FS_I(dn->inode)->i_compr_blocks);

	अगर (IS_INODE(dn->node_page) && f2fs_has_extra_attr(dn->inode))
		base = get_extra_isize(dn->inode);

	raw_node = F2FS_NODE(dn->node_page);
	addr = blkaddr_in_node(raw_node) + base + ofs;

	/* Assumption: truncateion starts with cluster */
	क्रम (; count > 0; count--, addr++, dn->ofs_in_node++, cluster_index++) अणु
		block_t blkaddr = le32_to_cpu(*addr);

		अगर (f2fs_compressed_file(dn->inode) &&
					!(cluster_index & (cluster_size - 1))) अणु
			अगर (compressed_cluster)
				f2fs_i_compr_blocks_update(dn->inode,
							valid_blocks, false);
			compressed_cluster = (blkaddr == COMPRESS_ADDR);
			valid_blocks = 0;
		पूर्ण

		अगर (blkaddr == शून्य_ADDR)
			जारी;

		dn->data_blkaddr = शून्य_ADDR;
		f2fs_set_data_blkaddr(dn);

		अगर (__is_valid_data_blkaddr(blkaddr)) अणु
			अगर (!f2fs_is_valid_blkaddr(sbi, blkaddr,
					DATA_GENERIC_ENHANCE))
				जारी;
			अगर (compressed_cluster)
				valid_blocks++;
		पूर्ण

		अगर (dn->ofs_in_node == 0 && IS_INODE(dn->node_page))
			clear_inode_flag(dn->inode, FI_FIRST_BLOCK_WRITTEN);

		f2fs_invalidate_blocks(sbi, blkaddr);

		अगर (!released || blkaddr != COMPRESS_ADDR)
			nr_मुक्त++;
	पूर्ण

	अगर (compressed_cluster)
		f2fs_i_compr_blocks_update(dn->inode, valid_blocks, false);

	अगर (nr_मुक्त) अणु
		pgoff_t fofs;
		/*
		 * once we invalidate valid blkaddr in range [ofs, ofs + count],
		 * we will invalidate all blkaddr in the whole range.
		 */
		fofs = f2fs_start_bidx_of_node(ofs_of_node(dn->node_page),
							dn->inode) + ofs;
		f2fs_update_extent_cache_range(dn, fofs, 0, len);
		dec_valid_block_count(sbi, dn->inode, nr_मुक्त);
	पूर्ण
	dn->ofs_in_node = ofs;

	f2fs_update_समय(sbi, REQ_TIME);
	trace_f2fs_truncate_data_blocks_range(dn->inode, dn->nid,
					 dn->ofs_in_node, nr_मुक्त);
पूर्ण

व्योम f2fs_truncate_data_blocks(काष्ठा dnode_of_data *dn)
अणु
	f2fs_truncate_data_blocks_range(dn, ADDRS_PER_BLOCK(dn->inode));
पूर्ण

अटल पूर्णांक truncate_partial_data_page(काष्ठा inode *inode, u64 from,
								bool cache_only)
अणु
	loff_t offset = from & (PAGE_SIZE - 1);
	pgoff_t index = from >> PAGE_SHIFT;
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा page *page;

	अगर (!offset && !cache_only)
		वापस 0;

	अगर (cache_only) अणु
		page = find_lock_page(mapping, index);
		अगर (page && PageUptodate(page))
			जाओ truncate_out;
		f2fs_put_page(page, 1);
		वापस 0;
	पूर्ण

	page = f2fs_get_lock_data_page(inode, index, true);
	अगर (IS_ERR(page))
		वापस PTR_ERR(page) == -ENOENT ? 0 : PTR_ERR(page);
truncate_out:
	f2fs_रुको_on_page_ग_लिखोback(page, DATA, true, true);
	zero_user(page, offset, PAGE_SIZE - offset);

	/* An encrypted inode should have a key and truncate the last page. */
	f2fs_bug_on(F2FS_I_SB(inode), cache_only && IS_ENCRYPTED(inode));
	अगर (!cache_only)
		set_page_dirty(page);
	f2fs_put_page(page, 1);
	वापस 0;
पूर्ण

पूर्णांक f2fs_करो_truncate_blocks(काष्ठा inode *inode, u64 from, bool lock)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा dnode_of_data dn;
	pgoff_t मुक्त_from;
	पूर्णांक count = 0, err = 0;
	काष्ठा page *ipage;
	bool truncate_page = false;

	trace_f2fs_truncate_blocks_enter(inode, from);

	मुक्त_from = (pgoff_t)F2FS_BLK_ALIGN(from);

	अगर (मुक्त_from >= max_file_blocks(inode))
		जाओ मुक्त_partial;

	अगर (lock)
		f2fs_lock_op(sbi);

	ipage = f2fs_get_node_page(sbi, inode->i_ino);
	अगर (IS_ERR(ipage)) अणु
		err = PTR_ERR(ipage);
		जाओ out;
	पूर्ण

	अगर (f2fs_has_अंतरभूत_data(inode)) अणु
		f2fs_truncate_अंतरभूत_inode(inode, ipage, from);
		f2fs_put_page(ipage, 1);
		truncate_page = true;
		जाओ out;
	पूर्ण

	set_new_dnode(&dn, inode, ipage, शून्य, 0);
	err = f2fs_get_dnode_of_data(&dn, मुक्त_from, LOOKUP_NODE_RA);
	अगर (err) अणु
		अगर (err == -ENOENT)
			जाओ मुक्त_next;
		जाओ out;
	पूर्ण

	count = ADDRS_PER_PAGE(dn.node_page, inode);

	count -= dn.ofs_in_node;
	f2fs_bug_on(sbi, count < 0);

	अगर (dn.ofs_in_node || IS_INODE(dn.node_page)) अणु
		f2fs_truncate_data_blocks_range(&dn, count);
		मुक्त_from += count;
	पूर्ण

	f2fs_put_dnode(&dn);
मुक्त_next:
	err = f2fs_truncate_inode_blocks(inode, मुक्त_from);
out:
	अगर (lock)
		f2fs_unlock_op(sbi);
मुक्त_partial:
	/* lastly zero out the first data page */
	अगर (!err)
		err = truncate_partial_data_page(inode, from, truncate_page);

	trace_f2fs_truncate_blocks_निकास(inode, err);
	वापस err;
पूर्ण

पूर्णांक f2fs_truncate_blocks(काष्ठा inode *inode, u64 from, bool lock)
अणु
	u64 मुक्त_from = from;
	पूर्णांक err;

#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
	/*
	 * क्रम compressed file, only support cluster size
	 * aligned truncation.
	 */
	अगर (f2fs_compressed_file(inode))
		मुक्त_from = round_up(from,
				F2FS_I(inode)->i_cluster_size << PAGE_SHIFT);
#पूर्ण_अगर

	err = f2fs_करो_truncate_blocks(inode, मुक्त_from, lock);
	अगर (err)
		वापस err;

#अगर_घोषित CONFIG_F2FS_FS_COMPRESSION
	अगर (from != मुक्त_from) अणु
		err = f2fs_truncate_partial_cluster(inode, from, lock);
		अगर (err)
			वापस err;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

पूर्णांक f2fs_truncate(काष्ठा inode *inode)
अणु
	पूर्णांक err;

	अगर (unlikely(f2fs_cp_error(F2FS_I_SB(inode))))
		वापस -EIO;

	अगर (!(S_ISREG(inode->i_mode) || S_ISसूची(inode->i_mode) ||
				S_ISLNK(inode->i_mode)))
		वापस 0;

	trace_f2fs_truncate(inode);

	अगर (समय_प्रकारo_inject(F2FS_I_SB(inode), FAULT_TRUNCATE)) अणु
		f2fs_show_injection_info(F2FS_I_SB(inode), FAULT_TRUNCATE);
		वापस -EIO;
	पूर्ण

	err = dquot_initialize(inode);
	अगर (err)
		वापस err;

	/* we should check अंतरभूत_data size */
	अगर (!f2fs_may_अंतरभूत_data(inode)) अणु
		err = f2fs_convert_अंतरभूत_inode(inode);
		अगर (err)
			वापस err;
	पूर्ण

	err = f2fs_truncate_blocks(inode, i_size_पढ़ो(inode), true);
	अगर (err)
		वापस err;

	inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	f2fs_mark_inode_dirty_sync(inode, false);
	वापस 0;
पूर्ण

पूर्णांक f2fs_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		 काष्ठा kstat *stat, u32 request_mask, अचिन्हित पूर्णांक query_flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	काष्ठा f2fs_inode_info *fi = F2FS_I(inode);
	काष्ठा f2fs_inode *ri;
	अचिन्हित पूर्णांक flags;

	अगर (f2fs_has_extra_attr(inode) &&
			f2fs_sb_has_inode_crसमय(F2FS_I_SB(inode)) &&
			F2FS_FITS_IN_INODE(ri, fi->i_extra_isize, i_crसमय)) अणु
		stat->result_mask |= STATX_BTIME;
		stat->bसमय.tv_sec = fi->i_crसमय.tv_sec;
		stat->bसमय.tv_nsec = fi->i_crसमय.tv_nsec;
	पूर्ण

	flags = fi->i_flags;
	अगर (flags & F2FS_COMPR_FL)
		stat->attributes |= STATX_ATTR_COMPRESSED;
	अगर (flags & F2FS_APPEND_FL)
		stat->attributes |= STATX_ATTR_APPEND;
	अगर (IS_ENCRYPTED(inode))
		stat->attributes |= STATX_ATTR_ENCRYPTED;
	अगर (flags & F2FS_IMMUTABLE_FL)
		stat->attributes |= STATX_ATTR_IMMUTABLE;
	अगर (flags & F2FS_NODUMP_FL)
		stat->attributes |= STATX_ATTR_NODUMP;
	अगर (IS_VERITY(inode))
		stat->attributes |= STATX_ATTR_VERITY;

	stat->attributes_mask |= (STATX_ATTR_COMPRESSED |
				  STATX_ATTR_APPEND |
				  STATX_ATTR_ENCRYPTED |
				  STATX_ATTR_IMMUTABLE |
				  STATX_ATTR_NODUMP |
				  STATX_ATTR_VERITY);

	generic_fillattr(&init_user_ns, inode, stat);

	/* we need to show initial sectors used क्रम अंतरभूत_data/dentries */
	अगर ((S_ISREG(inode->i_mode) && f2fs_has_अंतरभूत_data(inode)) ||
					f2fs_has_अंतरभूत_dentry(inode))
		stat->blocks += (stat->size + 511) >> 9;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_F2FS_FS_POSIX_ACL
अटल व्योम __setattr_copy(काष्ठा user_namespace *mnt_userns,
			   काष्ठा inode *inode, स्थिर काष्ठा iattr *attr)
अणु
	अचिन्हित पूर्णांक ia_valid = attr->ia_valid;

	अगर (ia_valid & ATTR_UID)
		inode->i_uid = attr->ia_uid;
	अगर (ia_valid & ATTR_GID)
		inode->i_gid = attr->ia_gid;
	अगर (ia_valid & ATTR_ATIME)
		inode->i_aसमय = attr->ia_aसमय;
	अगर (ia_valid & ATTR_MTIME)
		inode->i_mसमय = attr->ia_mसमय;
	अगर (ia_valid & ATTR_CTIME)
		inode->i_स_समय = attr->ia_स_समय;
	अगर (ia_valid & ATTR_MODE) अणु
		umode_t mode = attr->ia_mode;
		kgid_t kgid = i_gid_पूर्णांकo_mnt(mnt_userns, inode);

		अगर (!in_group_p(kgid) && !capable_wrt_inode_uidgid(mnt_userns, inode, CAP_FSETID))
			mode &= ~S_ISGID;
		set_acl_inode(inode, mode);
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा __setattr_copy setattr_copy
#पूर्ण_अगर

पूर्णांक f2fs_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		 काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक err;

	अगर (unlikely(f2fs_cp_error(F2FS_I_SB(inode))))
		वापस -EIO;

	अगर (unlikely(IS_IMMUTABLE(inode)))
		वापस -EPERM;

	अगर (unlikely(IS_APPEND(inode) &&
			(attr->ia_valid & (ATTR_MODE | ATTR_UID |
				  ATTR_GID | ATTR_TIMES_SET))))
		वापस -EPERM;

	अगर ((attr->ia_valid & ATTR_SIZE) &&
		!f2fs_is_compress_backend_पढ़ोy(inode))
		वापस -EOPNOTSUPP;

	err = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (err)
		वापस err;

	err = fscrypt_prepare_setattr(dentry, attr);
	अगर (err)
		वापस err;

	err = fsverity_prepare_setattr(dentry, attr);
	अगर (err)
		वापस err;

	अगर (is_quota_modअगरication(inode, attr)) अणु
		err = dquot_initialize(inode);
		अगर (err)
			वापस err;
	पूर्ण
	अगर ((attr->ia_valid & ATTR_UID &&
		!uid_eq(attr->ia_uid, inode->i_uid)) ||
		(attr->ia_valid & ATTR_GID &&
		!gid_eq(attr->ia_gid, inode->i_gid))) अणु
		f2fs_lock_op(F2FS_I_SB(inode));
		err = dquot_transfer(inode, attr);
		अगर (err) अणु
			set_sbi_flag(F2FS_I_SB(inode),
					SBI_QUOTA_NEED_REPAIR);
			f2fs_unlock_op(F2FS_I_SB(inode));
			वापस err;
		पूर्ण
		/*
		 * update uid/gid under lock_op(), so that dquot and inode can
		 * be updated atomically.
		 */
		अगर (attr->ia_valid & ATTR_UID)
			inode->i_uid = attr->ia_uid;
		अगर (attr->ia_valid & ATTR_GID)
			inode->i_gid = attr->ia_gid;
		f2fs_mark_inode_dirty_sync(inode, true);
		f2fs_unlock_op(F2FS_I_SB(inode));
	पूर्ण

	अगर (attr->ia_valid & ATTR_SIZE) अणु
		loff_t old_size = i_size_पढ़ो(inode);

		अगर (attr->ia_size > MAX_INLINE_DATA(inode)) अणु
			/*
			 * should convert अंतरभूत inode beक्रमe i_size_ग_लिखो to
			 * keep smaller than अंतरभूत_data size with अंतरभूत flag.
			 */
			err = f2fs_convert_अंतरभूत_inode(inode);
			अगर (err)
				वापस err;
		पूर्ण

		करोwn_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
		करोwn_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);

		truncate_setsize(inode, attr->ia_size);

		अगर (attr->ia_size <= old_size)
			err = f2fs_truncate(inode);
		/*
		 * करो not trim all blocks after i_size अगर target size is
		 * larger than i_size.
		 */
		up_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);
		up_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
		अगर (err)
			वापस err;

		spin_lock(&F2FS_I(inode)->i_size_lock);
		inode->i_mसमय = inode->i_स_समय = current_समय(inode);
		F2FS_I(inode)->last_disk_size = i_size_पढ़ो(inode);
		spin_unlock(&F2FS_I(inode)->i_size_lock);
	पूर्ण

	__setattr_copy(&init_user_ns, inode, attr);

	अगर (attr->ia_valid & ATTR_MODE) अणु
		err = posix_acl_chmod(&init_user_ns, inode, f2fs_get_inode_mode(inode));

		अगर (is_inode_flag_set(inode, FI_ACL_MODE)) अणु
			अगर (!err)
				inode->i_mode = F2FS_I(inode)->i_acl_mode;
			clear_inode_flag(inode, FI_ACL_MODE);
		पूर्ण
	पूर्ण

	/* file size may changed here */
	f2fs_mark_inode_dirty_sync(inode, true);

	/* inode change will produce dirty node pages flushed by checkpoपूर्णांक */
	f2fs_balance_fs(F2FS_I_SB(inode), true);

	वापस err;
पूर्ण

स्थिर काष्ठा inode_operations f2fs_file_inode_operations = अणु
	.getattr	= f2fs_getattr,
	.setattr	= f2fs_setattr,
	.get_acl	= f2fs_get_acl,
	.set_acl	= f2fs_set_acl,
	.listxattr	= f2fs_listxattr,
	.fiemap		= f2fs_fiemap,
	.fileattr_get	= f2fs_fileattr_get,
	.fileattr_set	= f2fs_fileattr_set,
पूर्ण;

अटल पूर्णांक fill_zero(काष्ठा inode *inode, pgoff_t index,
					loff_t start, loff_t len)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा page *page;

	अगर (!len)
		वापस 0;

	f2fs_balance_fs(sbi, true);

	f2fs_lock_op(sbi);
	page = f2fs_get_new_data_page(inode, शून्य, index, false);
	f2fs_unlock_op(sbi);

	अगर (IS_ERR(page))
		वापस PTR_ERR(page);

	f2fs_रुको_on_page_ग_लिखोback(page, DATA, true, true);
	zero_user(page, start, len);
	set_page_dirty(page);
	f2fs_put_page(page, 1);
	वापस 0;
पूर्ण

पूर्णांक f2fs_truncate_hole(काष्ठा inode *inode, pgoff_t pg_start, pgoff_t pg_end)
अणु
	पूर्णांक err;

	जबतक (pg_start < pg_end) अणु
		काष्ठा dnode_of_data dn;
		pgoff_t end_offset, count;

		set_new_dnode(&dn, inode, शून्य, शून्य, 0);
		err = f2fs_get_dnode_of_data(&dn, pg_start, LOOKUP_NODE);
		अगर (err) अणु
			अगर (err == -ENOENT) अणु
				pg_start = f2fs_get_next_page_offset(&dn,
								pg_start);
				जारी;
			पूर्ण
			वापस err;
		पूर्ण

		end_offset = ADDRS_PER_PAGE(dn.node_page, inode);
		count = min(end_offset - dn.ofs_in_node, pg_end - pg_start);

		f2fs_bug_on(F2FS_I_SB(inode), count == 0 || count > end_offset);

		f2fs_truncate_data_blocks_range(&dn, count);
		f2fs_put_dnode(&dn);

		pg_start += count;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक punch_hole(काष्ठा inode *inode, loff_t offset, loff_t len)
अणु
	pgoff_t pg_start, pg_end;
	loff_t off_start, off_end;
	पूर्णांक ret;

	ret = f2fs_convert_अंतरभूत_inode(inode);
	अगर (ret)
		वापस ret;

	pg_start = ((अचिन्हित दीर्घ दीर्घ) offset) >> PAGE_SHIFT;
	pg_end = ((अचिन्हित दीर्घ दीर्घ) offset + len) >> PAGE_SHIFT;

	off_start = offset & (PAGE_SIZE - 1);
	off_end = (offset + len) & (PAGE_SIZE - 1);

	अगर (pg_start == pg_end) अणु
		ret = fill_zero(inode, pg_start, off_start,
						off_end - off_start);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		अगर (off_start) अणु
			ret = fill_zero(inode, pg_start++, off_start,
						PAGE_SIZE - off_start);
			अगर (ret)
				वापस ret;
		पूर्ण
		अगर (off_end) अणु
			ret = fill_zero(inode, pg_end, 0, off_end);
			अगर (ret)
				वापस ret;
		पूर्ण

		अगर (pg_start < pg_end) अणु
			काष्ठा address_space *mapping = inode->i_mapping;
			loff_t blk_start, blk_end;
			काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);

			f2fs_balance_fs(sbi, true);

			blk_start = (loff_t)pg_start << PAGE_SHIFT;
			blk_end = (loff_t)pg_end << PAGE_SHIFT;

			करोwn_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
			करोwn_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);

			truncate_inode_pages_range(mapping, blk_start,
					blk_end - 1);

			f2fs_lock_op(sbi);
			ret = f2fs_truncate_hole(inode, pg_start, pg_end);
			f2fs_unlock_op(sbi);

			up_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);
			up_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __पढ़ो_out_blkaddrs(काष्ठा inode *inode, block_t *blkaddr,
				पूर्णांक *करो_replace, pgoff_t off, pgoff_t len)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा dnode_of_data dn;
	पूर्णांक ret, करोne, i;

next_dnode:
	set_new_dnode(&dn, inode, शून्य, शून्य, 0);
	ret = f2fs_get_dnode_of_data(&dn, off, LOOKUP_NODE_RA);
	अगर (ret && ret != -ENOENT) अणु
		वापस ret;
	पूर्ण अन्यथा अगर (ret == -ENOENT) अणु
		अगर (dn.max_level == 0)
			वापस -ENOENT;
		करोne = min((pgoff_t)ADDRS_PER_BLOCK(inode) -
						dn.ofs_in_node, len);
		blkaddr += करोne;
		करो_replace += करोne;
		जाओ next;
	पूर्ण

	करोne = min((pgoff_t)ADDRS_PER_PAGE(dn.node_page, inode) -
							dn.ofs_in_node, len);
	क्रम (i = 0; i < करोne; i++, blkaddr++, करो_replace++, dn.ofs_in_node++) अणु
		*blkaddr = f2fs_data_blkaddr(&dn);

		अगर (__is_valid_data_blkaddr(*blkaddr) &&
			!f2fs_is_valid_blkaddr(sbi, *blkaddr,
					DATA_GENERIC_ENHANCE)) अणु
			f2fs_put_dnode(&dn);
			वापस -EFSCORRUPTED;
		पूर्ण

		अगर (!f2fs_is_checkpoपूर्णांकed_data(sbi, *blkaddr)) अणु

			अगर (f2fs_lfs_mode(sbi)) अणु
				f2fs_put_dnode(&dn);
				वापस -EOPNOTSUPP;
			पूर्ण

			/* करो not invalidate this block address */
			f2fs_update_data_blkaddr(&dn, शून्य_ADDR);
			*करो_replace = 1;
		पूर्ण
	पूर्ण
	f2fs_put_dnode(&dn);
next:
	len -= करोne;
	off += करोne;
	अगर (len)
		जाओ next_dnode;
	वापस 0;
पूर्ण

अटल पूर्णांक __roll_back_blkaddrs(काष्ठा inode *inode, block_t *blkaddr,
				पूर्णांक *करो_replace, pgoff_t off, पूर्णांक len)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा dnode_of_data dn;
	पूर्णांक ret, i;

	क्रम (i = 0; i < len; i++, करो_replace++, blkaddr++) अणु
		अगर (*करो_replace == 0)
			जारी;

		set_new_dnode(&dn, inode, शून्य, शून्य, 0);
		ret = f2fs_get_dnode_of_data(&dn, off + i, LOOKUP_NODE_RA);
		अगर (ret) अणु
			dec_valid_block_count(sbi, inode, 1);
			f2fs_invalidate_blocks(sbi, *blkaddr);
		पूर्ण अन्यथा अणु
			f2fs_update_data_blkaddr(&dn, *blkaddr);
		पूर्ण
		f2fs_put_dnode(&dn);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __clone_blkaddrs(काष्ठा inode *src_inode, काष्ठा inode *dst_inode,
			block_t *blkaddr, पूर्णांक *करो_replace,
			pgoff_t src, pgoff_t dst, pgoff_t len, bool full)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(src_inode);
	pgoff_t i = 0;
	पूर्णांक ret;

	जबतक (i < len) अणु
		अगर (blkaddr[i] == शून्य_ADDR && !full) अणु
			i++;
			जारी;
		पूर्ण

		अगर (करो_replace[i] || blkaddr[i] == शून्य_ADDR) अणु
			काष्ठा dnode_of_data dn;
			काष्ठा node_info ni;
			माप_प्रकार new_size;
			pgoff_t ilen;

			set_new_dnode(&dn, dst_inode, शून्य, शून्य, 0);
			ret = f2fs_get_dnode_of_data(&dn, dst + i, ALLOC_NODE);
			अगर (ret)
				वापस ret;

			ret = f2fs_get_node_info(sbi, dn.nid, &ni);
			अगर (ret) अणु
				f2fs_put_dnode(&dn);
				वापस ret;
			पूर्ण

			ilen = min((pgoff_t)
				ADDRS_PER_PAGE(dn.node_page, dst_inode) -
						dn.ofs_in_node, len - i);
			करो अणु
				dn.data_blkaddr = f2fs_data_blkaddr(&dn);
				f2fs_truncate_data_blocks_range(&dn, 1);

				अगर (करो_replace[i]) अणु
					f2fs_i_blocks_ग_लिखो(src_inode,
							1, false, false);
					f2fs_i_blocks_ग_लिखो(dst_inode,
							1, true, false);
					f2fs_replace_block(sbi, &dn, dn.data_blkaddr,
					blkaddr[i], ni.version, true, false);

					करो_replace[i] = 0;
				पूर्ण
				dn.ofs_in_node++;
				i++;
				new_size = (loff_t)(dst + i) << PAGE_SHIFT;
				अगर (dst_inode->i_size < new_size)
					f2fs_i_size_ग_लिखो(dst_inode, new_size);
			पूर्ण जबतक (--ilen && (करो_replace[i] || blkaddr[i] == शून्य_ADDR));

			f2fs_put_dnode(&dn);
		पूर्ण अन्यथा अणु
			काष्ठा page *psrc, *pdst;

			psrc = f2fs_get_lock_data_page(src_inode,
							src + i, true);
			अगर (IS_ERR(psrc))
				वापस PTR_ERR(psrc);
			pdst = f2fs_get_new_data_page(dst_inode, शून्य, dst + i,
								true);
			अगर (IS_ERR(pdst)) अणु
				f2fs_put_page(psrc, 1);
				वापस PTR_ERR(pdst);
			पूर्ण
			f2fs_copy_page(psrc, pdst);
			set_page_dirty(pdst);
			f2fs_put_page(pdst, 1);
			f2fs_put_page(psrc, 1);

			ret = f2fs_truncate_hole(src_inode,
						src + i, src + i + 1);
			अगर (ret)
				वापस ret;
			i++;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __exchange_data_block(काष्ठा inode *src_inode,
			काष्ठा inode *dst_inode, pgoff_t src, pgoff_t dst,
			pgoff_t len, bool full)
अणु
	block_t *src_blkaddr;
	पूर्णांक *करो_replace;
	pgoff_t olen;
	पूर्णांक ret;

	जबतक (len) अणु
		olen = min((pgoff_t)4 * ADDRS_PER_BLOCK(src_inode), len);

		src_blkaddr = f2fs_kvzalloc(F2FS_I_SB(src_inode),
					array_size(olen, माप(block_t)),
					GFP_NOFS);
		अगर (!src_blkaddr)
			वापस -ENOMEM;

		करो_replace = f2fs_kvzalloc(F2FS_I_SB(src_inode),
					array_size(olen, माप(पूर्णांक)),
					GFP_NOFS);
		अगर (!करो_replace) अणु
			kvमुक्त(src_blkaddr);
			वापस -ENOMEM;
		पूर्ण

		ret = __पढ़ो_out_blkaddrs(src_inode, src_blkaddr,
					करो_replace, src, olen);
		अगर (ret)
			जाओ roll_back;

		ret = __clone_blkaddrs(src_inode, dst_inode, src_blkaddr,
					करो_replace, src, dst, olen, full);
		अगर (ret)
			जाओ roll_back;

		src += olen;
		dst += olen;
		len -= olen;

		kvमुक्त(src_blkaddr);
		kvमुक्त(करो_replace);
	पूर्ण
	वापस 0;

roll_back:
	__roll_back_blkaddrs(src_inode, src_blkaddr, करो_replace, src, olen);
	kvमुक्त(src_blkaddr);
	kvमुक्त(करो_replace);
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_करो_collapse(काष्ठा inode *inode, loff_t offset, loff_t len)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	pgoff_t nrpages = DIV_ROUND_UP(i_size_पढ़ो(inode), PAGE_SIZE);
	pgoff_t start = offset >> PAGE_SHIFT;
	pgoff_t end = (offset + len) >> PAGE_SHIFT;
	पूर्णांक ret;

	f2fs_balance_fs(sbi, true);

	/* aव्योम gc operation during block exchange */
	करोwn_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
	करोwn_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);

	f2fs_lock_op(sbi);
	f2fs_drop_extent_tree(inode);
	truncate_pagecache(inode, offset);
	ret = __exchange_data_block(inode, inode, end, start, nrpages - end, true);
	f2fs_unlock_op(sbi);

	up_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);
	up_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_collapse_range(काष्ठा inode *inode, loff_t offset, loff_t len)
अणु
	loff_t new_size;
	पूर्णांक ret;

	अगर (offset + len >= i_size_पढ़ो(inode))
		वापस -EINVAL;

	/* collapse range should be aligned to block size of f2fs. */
	अगर (offset & (F2FS_BLKSIZE - 1) || len & (F2FS_BLKSIZE - 1))
		वापस -EINVAL;

	ret = f2fs_convert_अंतरभूत_inode(inode);
	अगर (ret)
		वापस ret;

	/* ग_लिखो out all dirty pages from offset */
	ret = filemap_ग_लिखो_and_रुको_range(inode->i_mapping, offset, Lदीर्घ_उच्च);
	अगर (ret)
		वापस ret;

	ret = f2fs_करो_collapse(inode, offset, len);
	अगर (ret)
		वापस ret;

	/* ग_लिखो out all moved pages, अगर possible */
	करोwn_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);
	filemap_ग_लिखो_and_रुको_range(inode->i_mapping, offset, Lदीर्घ_उच्च);
	truncate_pagecache(inode, offset);

	new_size = i_size_पढ़ो(inode) - len;
	ret = f2fs_truncate_blocks(inode, new_size, true);
	up_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);
	अगर (!ret)
		f2fs_i_size_ग_लिखो(inode, new_size);
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_करो_zero_range(काष्ठा dnode_of_data *dn, pgoff_t start,
								pgoff_t end)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dn->inode);
	pgoff_t index = start;
	अचिन्हित पूर्णांक ofs_in_node = dn->ofs_in_node;
	blkcnt_t count = 0;
	पूर्णांक ret;

	क्रम (; index < end; index++, dn->ofs_in_node++) अणु
		अगर (f2fs_data_blkaddr(dn) == शून्य_ADDR)
			count++;
	पूर्ण

	dn->ofs_in_node = ofs_in_node;
	ret = f2fs_reserve_new_blocks(dn, count);
	अगर (ret)
		वापस ret;

	dn->ofs_in_node = ofs_in_node;
	क्रम (index = start; index < end; index++, dn->ofs_in_node++) अणु
		dn->data_blkaddr = f2fs_data_blkaddr(dn);
		/*
		 * f2fs_reserve_new_blocks will not guarantee entire block
		 * allocation.
		 */
		अगर (dn->data_blkaddr == शून्य_ADDR) अणु
			ret = -ENOSPC;
			अवरोध;
		पूर्ण
		अगर (dn->data_blkaddr != NEW_ADDR) अणु
			f2fs_invalidate_blocks(sbi, dn->data_blkaddr);
			dn->data_blkaddr = NEW_ADDR;
			f2fs_set_data_blkaddr(dn);
		पूर्ण
	पूर्ण

	f2fs_update_extent_cache_range(dn, start, 0, index - start);

	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_zero_range(काष्ठा inode *inode, loff_t offset, loff_t len,
								पूर्णांक mode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा address_space *mapping = inode->i_mapping;
	pgoff_t index, pg_start, pg_end;
	loff_t new_size = i_size_पढ़ो(inode);
	loff_t off_start, off_end;
	पूर्णांक ret = 0;

	ret = inode_newsize_ok(inode, (len + offset));
	अगर (ret)
		वापस ret;

	ret = f2fs_convert_अंतरभूत_inode(inode);
	अगर (ret)
		वापस ret;

	ret = filemap_ग_लिखो_and_रुको_range(mapping, offset, offset + len - 1);
	अगर (ret)
		वापस ret;

	pg_start = ((अचिन्हित दीर्घ दीर्घ) offset) >> PAGE_SHIFT;
	pg_end = ((अचिन्हित दीर्घ दीर्घ) offset + len) >> PAGE_SHIFT;

	off_start = offset & (PAGE_SIZE - 1);
	off_end = (offset + len) & (PAGE_SIZE - 1);

	अगर (pg_start == pg_end) अणु
		ret = fill_zero(inode, pg_start, off_start,
						off_end - off_start);
		अगर (ret)
			वापस ret;

		new_size = max_t(loff_t, new_size, offset + len);
	पूर्ण अन्यथा अणु
		अगर (off_start) अणु
			ret = fill_zero(inode, pg_start++, off_start,
						PAGE_SIZE - off_start);
			अगर (ret)
				वापस ret;

			new_size = max_t(loff_t, new_size,
					(loff_t)pg_start << PAGE_SHIFT);
		पूर्ण

		क्रम (index = pg_start; index < pg_end;) अणु
			काष्ठा dnode_of_data dn;
			अचिन्हित पूर्णांक end_offset;
			pgoff_t end;

			करोwn_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
			करोwn_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);

			truncate_pagecache_range(inode,
				(loff_t)index << PAGE_SHIFT,
				((loff_t)pg_end << PAGE_SHIFT) - 1);

			f2fs_lock_op(sbi);

			set_new_dnode(&dn, inode, शून्य, शून्य, 0);
			ret = f2fs_get_dnode_of_data(&dn, index, ALLOC_NODE);
			अगर (ret) अणु
				f2fs_unlock_op(sbi);
				up_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);
				up_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
				जाओ out;
			पूर्ण

			end_offset = ADDRS_PER_PAGE(dn.node_page, inode);
			end = min(pg_end, end_offset - dn.ofs_in_node + index);

			ret = f2fs_करो_zero_range(&dn, index, end);
			f2fs_put_dnode(&dn);

			f2fs_unlock_op(sbi);
			up_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);
			up_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);

			f2fs_balance_fs(sbi, dn.node_changed);

			अगर (ret)
				जाओ out;

			index = end;
			new_size = max_t(loff_t, new_size,
					(loff_t)index << PAGE_SHIFT);
		पूर्ण

		अगर (off_end) अणु
			ret = fill_zero(inode, pg_end, 0, off_end);
			अगर (ret)
				जाओ out;

			new_size = max_t(loff_t, new_size, offset + len);
		पूर्ण
	पूर्ण

out:
	अगर (new_size > i_size_पढ़ो(inode)) अणु
		अगर (mode & FALLOC_FL_KEEP_SIZE)
			file_set_keep_isize(inode);
		अन्यथा
			f2fs_i_size_ग_लिखो(inode, new_size);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_insert_range(काष्ठा inode *inode, loff_t offset, loff_t len)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	pgoff_t nr, pg_start, pg_end, delta, idx;
	loff_t new_size;
	पूर्णांक ret = 0;

	new_size = i_size_पढ़ो(inode) + len;
	ret = inode_newsize_ok(inode, new_size);
	अगर (ret)
		वापस ret;

	अगर (offset >= i_size_पढ़ो(inode))
		वापस -EINVAL;

	/* insert range should be aligned to block size of f2fs. */
	अगर (offset & (F2FS_BLKSIZE - 1) || len & (F2FS_BLKSIZE - 1))
		वापस -EINVAL;

	ret = f2fs_convert_अंतरभूत_inode(inode);
	अगर (ret)
		वापस ret;

	f2fs_balance_fs(sbi, true);

	करोwn_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);
	ret = f2fs_truncate_blocks(inode, i_size_पढ़ो(inode), true);
	up_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);
	अगर (ret)
		वापस ret;

	/* ग_लिखो out all dirty pages from offset */
	ret = filemap_ग_लिखो_and_रुको_range(inode->i_mapping, offset, Lदीर्घ_उच्च);
	अगर (ret)
		वापस ret;

	pg_start = offset >> PAGE_SHIFT;
	pg_end = (offset + len) >> PAGE_SHIFT;
	delta = pg_end - pg_start;
	idx = DIV_ROUND_UP(i_size_पढ़ो(inode), PAGE_SIZE);

	/* aव्योम gc operation during block exchange */
	करोwn_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
	करोwn_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);
	truncate_pagecache(inode, offset);

	जबतक (!ret && idx > pg_start) अणु
		nr = idx - pg_start;
		अगर (nr > delta)
			nr = delta;
		idx -= nr;

		f2fs_lock_op(sbi);
		f2fs_drop_extent_tree(inode);

		ret = __exchange_data_block(inode, inode, idx,
					idx + delta, nr, false);
		f2fs_unlock_op(sbi);
	पूर्ण
	up_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);
	up_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);

	/* ग_लिखो out all moved pages, अगर possible */
	करोwn_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);
	filemap_ग_लिखो_and_रुको_range(inode->i_mapping, offset, Lदीर्घ_उच्च);
	truncate_pagecache(inode, offset);
	up_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);

	अगर (!ret)
		f2fs_i_size_ग_लिखो(inode, new_size);
	वापस ret;
पूर्ण

अटल पूर्णांक expand_inode_data(काष्ठा inode *inode, loff_t offset,
					loff_t len, पूर्णांक mode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा f2fs_map_blocks map = अणु .m_next_pgofs = शून्य,
			.m_next_extent = शून्य, .m_seg_type = NO_CHECK_TYPE,
			.m_may_create = true पूर्ण;
	pgoff_t pg_start, pg_end;
	loff_t new_size = i_size_पढ़ो(inode);
	loff_t off_end;
	block_t expanded = 0;
	पूर्णांक err;

	err = inode_newsize_ok(inode, (len + offset));
	अगर (err)
		वापस err;

	err = f2fs_convert_अंतरभूत_inode(inode);
	अगर (err)
		वापस err;

	f2fs_balance_fs(sbi, true);

	pg_start = ((अचिन्हित दीर्घ दीर्घ)offset) >> PAGE_SHIFT;
	pg_end = ((अचिन्हित दीर्घ दीर्घ)offset + len) >> PAGE_SHIFT;
	off_end = (offset + len) & (PAGE_SIZE - 1);

	map.m_lblk = pg_start;
	map.m_len = pg_end - pg_start;
	अगर (off_end)
		map.m_len++;

	अगर (!map.m_len)
		वापस 0;

	अगर (f2fs_is_pinned_file(inode)) अणु
		block_t sec_blks = BLKS_PER_SEC(sbi);
		block_t sec_len = roundup(map.m_len, sec_blks);

		map.m_len = sec_blks;
next_alloc:
		अगर (has_not_enough_मुक्त_secs(sbi, 0,
			GET_SEC_FROM_SEG(sbi, overprovision_segments(sbi)))) अणु
			करोwn_ग_लिखो(&sbi->gc_lock);
			err = f2fs_gc(sbi, true, false, false, शून्य_SEGNO);
			अगर (err && err != -ENODATA && err != -EAGAIN)
				जाओ out_err;
		पूर्ण

		करोwn_ग_लिखो(&sbi->pin_sem);

		f2fs_lock_op(sbi);
		f2fs_allocate_new_section(sbi, CURSEG_COLD_DATA_PINNED, false);
		f2fs_unlock_op(sbi);

		map.m_seg_type = CURSEG_COLD_DATA_PINNED;
		err = f2fs_map_blocks(inode, &map, 1, F2FS_GET_BLOCK_PRE_DIO);

		up_ग_लिखो(&sbi->pin_sem);

		expanded += map.m_len;
		sec_len -= map.m_len;
		map.m_lblk += map.m_len;
		अगर (!err && sec_len)
			जाओ next_alloc;

		map.m_len = expanded;
	पूर्ण अन्यथा अणु
		err = f2fs_map_blocks(inode, &map, 1, F2FS_GET_BLOCK_PRE_AIO);
		expanded = map.m_len;
	पूर्ण
out_err:
	अगर (err) अणु
		pgoff_t last_off;

		अगर (!expanded)
			वापस err;

		last_off = pg_start + expanded - 1;

		/* update new size to the failed position */
		new_size = (last_off == pg_end) ? offset + len :
					(loff_t)(last_off + 1) << PAGE_SHIFT;
	पूर्ण अन्यथा अणु
		new_size = ((loff_t)pg_end << PAGE_SHIFT) + off_end;
	पूर्ण

	अगर (new_size > i_size_पढ़ो(inode)) अणु
		अगर (mode & FALLOC_FL_KEEP_SIZE)
			file_set_keep_isize(inode);
		अन्यथा
			f2fs_i_size_ग_लिखो(inode, new_size);
	पूर्ण

	वापस err;
पूर्ण

अटल दीर्घ f2fs_fallocate(काष्ठा file *file, पूर्णांक mode,
				loff_t offset, loff_t len)
अणु
	काष्ठा inode *inode = file_inode(file);
	दीर्घ ret = 0;

	अगर (unlikely(f2fs_cp_error(F2FS_I_SB(inode))))
		वापस -EIO;
	अगर (!f2fs_is_checkpoपूर्णांक_पढ़ोy(F2FS_I_SB(inode)))
		वापस -ENOSPC;
	अगर (!f2fs_is_compress_backend_पढ़ोy(inode))
		वापस -EOPNOTSUPP;

	/* f2fs only support ->fallocate क्रम regular file */
	अगर (!S_ISREG(inode->i_mode))
		वापस -EINVAL;

	अगर (IS_ENCRYPTED(inode) &&
		(mode & (FALLOC_FL_COLLAPSE_RANGE | FALLOC_FL_INSERT_RANGE)))
		वापस -EOPNOTSUPP;

	अगर (f2fs_compressed_file(inode) &&
		(mode & (FALLOC_FL_PUNCH_HOLE | FALLOC_FL_COLLAPSE_RANGE |
			FALLOC_FL_ZERO_RANGE | FALLOC_FL_INSERT_RANGE)))
		वापस -EOPNOTSUPP;

	अगर (mode & ~(FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE |
			FALLOC_FL_COLLAPSE_RANGE | FALLOC_FL_ZERO_RANGE |
			FALLOC_FL_INSERT_RANGE))
		वापस -EOPNOTSUPP;

	inode_lock(inode);

	अगर (mode & FALLOC_FL_PUNCH_HOLE) अणु
		अगर (offset >= inode->i_size)
			जाओ out;

		ret = punch_hole(inode, offset, len);
	पूर्ण अन्यथा अगर (mode & FALLOC_FL_COLLAPSE_RANGE) अणु
		ret = f2fs_collapse_range(inode, offset, len);
	पूर्ण अन्यथा अगर (mode & FALLOC_FL_ZERO_RANGE) अणु
		ret = f2fs_zero_range(inode, offset, len, mode);
	पूर्ण अन्यथा अगर (mode & FALLOC_FL_INSERT_RANGE) अणु
		ret = f2fs_insert_range(inode, offset, len);
	पूर्ण अन्यथा अणु
		ret = expand_inode_data(inode, offset, len, mode);
	पूर्ण

	अगर (!ret) अणु
		inode->i_mसमय = inode->i_स_समय = current_समय(inode);
		f2fs_mark_inode_dirty_sync(inode, false);
		f2fs_update_समय(F2FS_I_SB(inode), REQ_TIME);
	पूर्ण

out:
	inode_unlock(inode);

	trace_f2fs_fallocate(inode, mode, offset, len, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_release_file(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	/*
	 * f2fs_relase_file is called at every बंद calls. So we should
	 * not drop any inmemory pages by बंद called by other process.
	 */
	अगर (!(filp->f_mode & FMODE_WRITE) ||
			atomic_पढ़ो(&inode->i_ग_लिखोcount) != 1)
		वापस 0;

	/* some reमुख्यed atomic pages should discarded */
	अगर (f2fs_is_atomic_file(inode))
		f2fs_drop_inmem_pages(inode);
	अगर (f2fs_is_अस्थिर_file(inode)) अणु
		set_inode_flag(inode, FI_DROP_CACHE);
		filemap_fdataग_लिखो(inode->i_mapping);
		clear_inode_flag(inode, FI_DROP_CACHE);
		clear_inode_flag(inode, FI_VOLATILE_खाता);
		stat_dec_अस्थिर_ग_लिखो(inode);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक f2fs_file_flush(काष्ठा file *file, fl_owner_t id)
अणु
	काष्ठा inode *inode = file_inode(file);

	/*
	 * If the process करोing a transaction is crashed, we should करो
	 * roll-back. Otherwise, other पढ़ोer/ग_लिखो can see corrupted database
	 * until all the ग_लिखोrs बंद its file. Since this should be करोne
	 * beक्रमe dropping file lock, it needs to करो in ->flush.
	 */
	अगर (f2fs_is_atomic_file(inode) &&
			F2FS_I(inode)->inmem_task == current)
		f2fs_drop_inmem_pages(inode);
	वापस 0;
पूर्ण

अटल पूर्णांक f2fs_setflags_common(काष्ठा inode *inode, u32 अगरlags, u32 mask)
अणु
	काष्ठा f2fs_inode_info *fi = F2FS_I(inode);
	u32 masked_flags = fi->i_flags & mask;

	/* mask can be shrunk by flags_valid selector */
	अगरlags &= mask;

	/* Is it quota file? Do not allow user to mess with it */
	अगर (IS_NOQUOTA(inode))
		वापस -EPERM;

	अगर ((अगरlags ^ masked_flags) & F2FS_CASEFOLD_FL) अणु
		अगर (!f2fs_sb_has_हालfold(F2FS_I_SB(inode)))
			वापस -EOPNOTSUPP;
		अगर (!f2fs_empty_dir(inode))
			वापस -ENOTEMPTY;
	पूर्ण

	अगर (अगरlags & (F2FS_COMPR_FL | F2FS_NOCOMP_FL)) अणु
		अगर (!f2fs_sb_has_compression(F2FS_I_SB(inode)))
			वापस -EOPNOTSUPP;
		अगर ((अगरlags & F2FS_COMPR_FL) && (अगरlags & F2FS_NOCOMP_FL))
			वापस -EINVAL;
	पूर्ण

	अगर ((अगरlags ^ masked_flags) & F2FS_COMPR_FL) अणु
		अगर (masked_flags & F2FS_COMPR_FL) अणु
			अगर (!f2fs_disable_compressed_file(inode))
				वापस -EINVAL;
		पूर्ण
		अगर (अगरlags & F2FS_NOCOMP_FL)
			वापस -EINVAL;
		अगर (अगरlags & F2FS_COMPR_FL) अणु
			अगर (!f2fs_may_compress(inode))
				वापस -EINVAL;
			अगर (S_ISREG(inode->i_mode) && inode->i_size)
				वापस -EINVAL;

			set_compress_context(inode);
		पूर्ण
	पूर्ण
	अगर ((अगरlags ^ masked_flags) & F2FS_NOCOMP_FL) अणु
		अगर (masked_flags & F2FS_COMPR_FL)
			वापस -EINVAL;
	पूर्ण

	fi->i_flags = अगरlags | (fi->i_flags & ~mask);
	f2fs_bug_on(F2FS_I_SB(inode), (fi->i_flags & F2FS_COMPR_FL) &&
					(fi->i_flags & F2FS_NOCOMP_FL));

	अगर (fi->i_flags & F2FS_PROJINHERIT_FL)
		set_inode_flag(inode, FI_PROJ_INHERIT);
	अन्यथा
		clear_inode_flag(inode, FI_PROJ_INHERIT);

	inode->i_स_समय = current_समय(inode);
	f2fs_set_inode_flags(inode);
	f2fs_mark_inode_dirty_sync(inode, true);
	वापस 0;
पूर्ण

/* FS_IOC_[GS]ETFLAGS and FS_IOC_FS[GS]ETXATTR support */

/*
 * To make a new on-disk f2fs i_flag gettable via FS_IOC_GETFLAGS, add an entry
 * क्रम it to f2fs_fsflags_map[], and add its FS_*_FL equivalent to
 * F2FS_GETTABLE_FS_FL.  To also make it settable via FS_IOC_SETFLAGS, also add
 * its FS_*_FL equivalent to F2FS_SETTABLE_FS_FL.
 *
 * Translating flags to fsx_flags value used by FS_IOC_FSGETXATTR and
 * FS_IOC_FSSETXATTR is करोne by the VFS.
 */

अटल स्थिर काष्ठा अणु
	u32 अगरlag;
	u32 fsflag;
पूर्ण f2fs_fsflags_map[] = अणु
	अणु F2FS_COMPR_FL,	FS_COMPR_FL पूर्ण,
	अणु F2FS_SYNC_FL,		FS_SYNC_FL पूर्ण,
	अणु F2FS_IMMUTABLE_FL,	FS_IMMUTABLE_FL पूर्ण,
	अणु F2FS_APPEND_FL,	FS_APPEND_FL पूर्ण,
	अणु F2FS_NODUMP_FL,	FS_NODUMP_FL पूर्ण,
	अणु F2FS_NOATIME_FL,	FS_NOATIME_FL पूर्ण,
	अणु F2FS_NOCOMP_FL,	FS_NOCOMP_FL पूर्ण,
	अणु F2FS_INDEX_FL,	FS_INDEX_FL पूर्ण,
	अणु F2FS_सूचीSYNC_FL,	FS_सूचीSYNC_FL पूर्ण,
	अणु F2FS_PROJINHERIT_FL,	FS_PROJINHERIT_FL पूर्ण,
	अणु F2FS_CASEFOLD_FL,	FS_CASEFOLD_FL पूर्ण,
पूर्ण;

#घोषणा F2FS_GETTABLE_FS_FL (		\
		FS_COMPR_FL |		\
		FS_SYNC_FL |		\
		FS_IMMUTABLE_FL |	\
		FS_APPEND_FL |		\
		FS_NODUMP_FL |		\
		FS_NOATIME_FL |		\
		FS_NOCOMP_FL |		\
		FS_INDEX_FL |		\
		FS_सूचीSYNC_FL |		\
		FS_PROJINHERIT_FL |	\
		FS_ENCRYPT_FL |		\
		FS_INLINE_DATA_FL |	\
		FS_NOCOW_FL |		\
		FS_VERITY_FL |		\
		FS_CASEFOLD_FL)

#घोषणा F2FS_SETTABLE_FS_FL (		\
		FS_COMPR_FL |		\
		FS_SYNC_FL |		\
		FS_IMMUTABLE_FL |	\
		FS_APPEND_FL |		\
		FS_NODUMP_FL |		\
		FS_NOATIME_FL |		\
		FS_NOCOMP_FL |		\
		FS_सूचीSYNC_FL |		\
		FS_PROJINHERIT_FL |	\
		FS_CASEFOLD_FL)

/* Convert f2fs on-disk i_flags to FS_IOC_अणुGET,SETपूर्णFLAGS flags */
अटल अंतरभूत u32 f2fs_अगरlags_to_fsflags(u32 अगरlags)
अणु
	u32 fsflags = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(f2fs_fsflags_map); i++)
		अगर (अगरlags & f2fs_fsflags_map[i].अगरlag)
			fsflags |= f2fs_fsflags_map[i].fsflag;

	वापस fsflags;
पूर्ण

/* Convert FS_IOC_अणुGET,SETपूर्णFLAGS flags to f2fs on-disk i_flags */
अटल अंतरभूत u32 f2fs_fsflags_to_अगरlags(u32 fsflags)
अणु
	u32 अगरlags = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(f2fs_fsflags_map); i++)
		अगर (fsflags & f2fs_fsflags_map[i].fsflag)
			अगरlags |= f2fs_fsflags_map[i].अगरlag;

	वापस अगरlags;
पूर्ण

अटल पूर्णांक f2fs_ioc_getversion(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);

	वापस put_user(inode->i_generation, (पूर्णांक __user *)arg);
पूर्ण

अटल पूर्णांक f2fs_ioc_start_atomic_ग_लिखो(काष्ठा file *filp)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा f2fs_inode_info *fi = F2FS_I(inode);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	पूर्णांक ret;

	अगर (!inode_owner_or_capable(&init_user_ns, inode))
		वापस -EACCES;

	अगर (!S_ISREG(inode->i_mode))
		वापस -EINVAL;

	अगर (filp->f_flags & O_सूचीECT)
		वापस -EINVAL;

	ret = mnt_want_ग_लिखो_file(filp);
	अगर (ret)
		वापस ret;

	inode_lock(inode);

	f2fs_disable_compressed_file(inode);

	अगर (f2fs_is_atomic_file(inode)) अणु
		अगर (is_inode_flag_set(inode, FI_ATOMIC_REVOKE_REQUEST))
			ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = f2fs_convert_अंतरभूत_inode(inode);
	अगर (ret)
		जाओ out;

	करोwn_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);

	/*
	 * Should रुको end_io to count F2FS_WB_CP_DATA correctly by
	 * f2fs_is_atomic_file.
	 */
	अगर (get_dirty_pages(inode))
		f2fs_warn(F2FS_I_SB(inode), "Unexpected flush for atomic writes: ino=%lu, npages=%u",
			  inode->i_ino, get_dirty_pages(inode));
	ret = filemap_ग_लिखो_and_रुको_range(inode->i_mapping, 0, Lदीर्घ_उच्च);
	अगर (ret) अणु
		up_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
		जाओ out;
	पूर्ण

	spin_lock(&sbi->inode_lock[ATOMIC_खाता]);
	अगर (list_empty(&fi->inmem_ilist))
		list_add_tail(&fi->inmem_ilist, &sbi->inode_list[ATOMIC_खाता]);
	sbi->atomic_files++;
	spin_unlock(&sbi->inode_lock[ATOMIC_खाता]);

	/* add inode in inmem_list first and set atomic_file */
	set_inode_flag(inode, FI_ATOMIC_खाता);
	clear_inode_flag(inode, FI_ATOMIC_REVOKE_REQUEST);
	up_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);

	f2fs_update_समय(F2FS_I_SB(inode), REQ_TIME);
	F2FS_I(inode)->inmem_task = current;
	stat_update_max_atomic_ग_लिखो(inode);
out:
	inode_unlock(inode);
	mnt_drop_ग_लिखो_file(filp);
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_ioc_commit_atomic_ग_लिखो(काष्ठा file *filp)
अणु
	काष्ठा inode *inode = file_inode(filp);
	पूर्णांक ret;

	अगर (!inode_owner_or_capable(&init_user_ns, inode))
		वापस -EACCES;

	ret = mnt_want_ग_लिखो_file(filp);
	अगर (ret)
		वापस ret;

	f2fs_balance_fs(F2FS_I_SB(inode), true);

	inode_lock(inode);

	अगर (f2fs_is_अस्थिर_file(inode)) अणु
		ret = -EINVAL;
		जाओ err_out;
	पूर्ण

	अगर (f2fs_is_atomic_file(inode)) अणु
		ret = f2fs_commit_inmem_pages(inode);
		अगर (ret)
			जाओ err_out;

		ret = f2fs_करो_sync_file(filp, 0, Lदीर्घ_उच्च, 0, true);
		अगर (!ret)
			f2fs_drop_inmem_pages(inode);
	पूर्ण अन्यथा अणु
		ret = f2fs_करो_sync_file(filp, 0, Lदीर्घ_उच्च, 1, false);
	पूर्ण
err_out:
	अगर (is_inode_flag_set(inode, FI_ATOMIC_REVOKE_REQUEST)) अणु
		clear_inode_flag(inode, FI_ATOMIC_REVOKE_REQUEST);
		ret = -EINVAL;
	पूर्ण
	inode_unlock(inode);
	mnt_drop_ग_लिखो_file(filp);
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_ioc_start_अस्थिर_ग_लिखो(काष्ठा file *filp)
अणु
	काष्ठा inode *inode = file_inode(filp);
	पूर्णांक ret;

	अगर (!inode_owner_or_capable(&init_user_ns, inode))
		वापस -EACCES;

	अगर (!S_ISREG(inode->i_mode))
		वापस -EINVAL;

	ret = mnt_want_ग_लिखो_file(filp);
	अगर (ret)
		वापस ret;

	inode_lock(inode);

	अगर (f2fs_is_अस्थिर_file(inode))
		जाओ out;

	ret = f2fs_convert_अंतरभूत_inode(inode);
	अगर (ret)
		जाओ out;

	stat_inc_अस्थिर_ग_लिखो(inode);
	stat_update_max_अस्थिर_ग_लिखो(inode);

	set_inode_flag(inode, FI_VOLATILE_खाता);
	f2fs_update_समय(F2FS_I_SB(inode), REQ_TIME);
out:
	inode_unlock(inode);
	mnt_drop_ग_लिखो_file(filp);
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_ioc_release_अस्थिर_ग_लिखो(काष्ठा file *filp)
अणु
	काष्ठा inode *inode = file_inode(filp);
	पूर्णांक ret;

	अगर (!inode_owner_or_capable(&init_user_ns, inode))
		वापस -EACCES;

	ret = mnt_want_ग_लिखो_file(filp);
	अगर (ret)
		वापस ret;

	inode_lock(inode);

	अगर (!f2fs_is_अस्थिर_file(inode))
		जाओ out;

	अगर (!f2fs_is_first_block_written(inode)) अणु
		ret = truncate_partial_data_page(inode, 0, true);
		जाओ out;
	पूर्ण

	ret = punch_hole(inode, 0, F2FS_BLKSIZE);
out:
	inode_unlock(inode);
	mnt_drop_ग_लिखो_file(filp);
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_ioc_पात_अस्थिर_ग_लिखो(काष्ठा file *filp)
अणु
	काष्ठा inode *inode = file_inode(filp);
	पूर्णांक ret;

	अगर (!inode_owner_or_capable(&init_user_ns, inode))
		वापस -EACCES;

	ret = mnt_want_ग_लिखो_file(filp);
	अगर (ret)
		वापस ret;

	inode_lock(inode);

	अगर (f2fs_is_atomic_file(inode))
		f2fs_drop_inmem_pages(inode);
	अगर (f2fs_is_अस्थिर_file(inode)) अणु
		clear_inode_flag(inode, FI_VOLATILE_खाता);
		stat_dec_अस्थिर_ग_लिखो(inode);
		ret = f2fs_करो_sync_file(filp, 0, Lदीर्घ_उच्च, 0, true);
	पूर्ण

	clear_inode_flag(inode, FI_ATOMIC_REVOKE_REQUEST);

	inode_unlock(inode);

	mnt_drop_ग_लिखो_file(filp);
	f2fs_update_समय(F2FS_I_SB(inode), REQ_TIME);
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_ioc_shutकरोwn(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा super_block *sb = sbi->sb;
	__u32 in;
	पूर्णांक ret = 0;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (get_user(in, (__u32 __user *)arg))
		वापस -EFAULT;

	अगर (in != F2FS_GOING_DOWN_FULLSYNC) अणु
		ret = mnt_want_ग_लिखो_file(filp);
		अगर (ret) अणु
			अगर (ret == -EROFS) अणु
				ret = 0;
				f2fs_stop_checkpoपूर्णांक(sbi, false);
				set_sbi_flag(sbi, SBI_IS_SHUTDOWN);
				trace_f2fs_shutकरोwn(sbi, in, ret);
			पूर्ण
			वापस ret;
		पूर्ण
	पूर्ण

	चयन (in) अणु
	हाल F2FS_GOING_DOWN_FULLSYNC:
		ret = मुक्तze_bdev(sb->s_bdev);
		अगर (ret)
			जाओ out;
		f2fs_stop_checkpoपूर्णांक(sbi, false);
		set_sbi_flag(sbi, SBI_IS_SHUTDOWN);
		thaw_bdev(sb->s_bdev);
		अवरोध;
	हाल F2FS_GOING_DOWN_METASYNC:
		/* करो checkpoपूर्णांक only */
		ret = f2fs_sync_fs(sb, 1);
		अगर (ret)
			जाओ out;
		f2fs_stop_checkpoपूर्णांक(sbi, false);
		set_sbi_flag(sbi, SBI_IS_SHUTDOWN);
		अवरोध;
	हाल F2FS_GOING_DOWN_NOSYNC:
		f2fs_stop_checkpoपूर्णांक(sbi, false);
		set_sbi_flag(sbi, SBI_IS_SHUTDOWN);
		अवरोध;
	हाल F2FS_GOING_DOWN_METAFLUSH:
		f2fs_sync_meta_pages(sbi, META, दीर्घ_उच्च, FS_META_IO);
		f2fs_stop_checkpoपूर्णांक(sbi, false);
		set_sbi_flag(sbi, SBI_IS_SHUTDOWN);
		अवरोध;
	हाल F2FS_GOING_DOWN_NEED_FSCK:
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		set_sbi_flag(sbi, SBI_CP_DISABLED_QUICK);
		set_sbi_flag(sbi, SBI_IS_सूचीTY);
		/* करो checkpoपूर्णांक only */
		ret = f2fs_sync_fs(sb, 1);
		जाओ out;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	f2fs_stop_gc_thपढ़ो(sbi);
	f2fs_stop_discard_thपढ़ो(sbi);

	f2fs_drop_discard_cmd(sbi);
	clear_opt(sbi, DISCARD);

	f2fs_update_समय(sbi, REQ_TIME);
out:
	अगर (in != F2FS_GOING_DOWN_FULLSYNC)
		mnt_drop_ग_लिखो_file(filp);

	trace_f2fs_shutकरोwn(sbi, in, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_ioc_fitrim(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा request_queue *q = bdev_get_queue(sb->s_bdev);
	काष्ठा fstrim_range range;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (!f2fs_hw_support_discard(F2FS_SB(sb)))
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&range, (काष्ठा fstrim_range __user *)arg,
				माप(range)))
		वापस -EFAULT;

	ret = mnt_want_ग_लिखो_file(filp);
	अगर (ret)
		वापस ret;

	range.minlen = max((अचिन्हित पूर्णांक)range.minlen,
				q->limits.discard_granularity);
	ret = f2fs_trim_fs(F2FS_SB(sb), &range);
	mnt_drop_ग_लिखो_file(filp);
	अगर (ret < 0)
		वापस ret;

	अगर (copy_to_user((काष्ठा fstrim_range __user *)arg, &range,
				माप(range)))
		वापस -EFAULT;
	f2fs_update_समय(F2FS_I_SB(inode), REQ_TIME);
	वापस 0;
पूर्ण

अटल bool uuid_is_nonzero(__u8 u[16])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++)
		अगर (u[i])
			वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक f2fs_ioc_set_encryption_policy(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);

	अगर (!f2fs_sb_has_encrypt(F2FS_I_SB(inode)))
		वापस -EOPNOTSUPP;

	f2fs_update_समय(F2FS_I_SB(inode), REQ_TIME);

	वापस fscrypt_ioctl_set_policy(filp, (स्थिर व्योम __user *)arg);
पूर्ण

अटल पूर्णांक f2fs_ioc_get_encryption_policy(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	अगर (!f2fs_sb_has_encrypt(F2FS_I_SB(file_inode(filp))))
		वापस -EOPNOTSUPP;
	वापस fscrypt_ioctl_get_policy(filp, (व्योम __user *)arg);
पूर्ण

अटल पूर्णांक f2fs_ioc_get_encryption_pwsalt(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	पूर्णांक err;

	अगर (!f2fs_sb_has_encrypt(sbi))
		वापस -EOPNOTSUPP;

	err = mnt_want_ग_लिखो_file(filp);
	अगर (err)
		वापस err;

	करोwn_ग_लिखो(&sbi->sb_lock);

	अगर (uuid_is_nonzero(sbi->raw_super->encrypt_pw_salt))
		जाओ got_it;

	/* update superblock with uuid */
	generate_अक्रमom_uuid(sbi->raw_super->encrypt_pw_salt);

	err = f2fs_commit_super(sbi, false);
	अगर (err) अणु
		/* unकरो new data */
		स_रखो(sbi->raw_super->encrypt_pw_salt, 0, 16);
		जाओ out_err;
	पूर्ण
got_it:
	अगर (copy_to_user((__u8 __user *)arg, sbi->raw_super->encrypt_pw_salt,
									16))
		err = -EFAULT;
out_err:
	up_ग_लिखो(&sbi->sb_lock);
	mnt_drop_ग_लिखो_file(filp);
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_ioc_get_encryption_policy_ex(काष्ठा file *filp,
					     अचिन्हित दीर्घ arg)
अणु
	अगर (!f2fs_sb_has_encrypt(F2FS_I_SB(file_inode(filp))))
		वापस -EOPNOTSUPP;

	वापस fscrypt_ioctl_get_policy_ex(filp, (व्योम __user *)arg);
पूर्ण

अटल पूर्णांक f2fs_ioc_add_encryption_key(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	अगर (!f2fs_sb_has_encrypt(F2FS_I_SB(file_inode(filp))))
		वापस -EOPNOTSUPP;

	वापस fscrypt_ioctl_add_key(filp, (व्योम __user *)arg);
पूर्ण

अटल पूर्णांक f2fs_ioc_हटाओ_encryption_key(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	अगर (!f2fs_sb_has_encrypt(F2FS_I_SB(file_inode(filp))))
		वापस -EOPNOTSUPP;

	वापस fscrypt_ioctl_हटाओ_key(filp, (व्योम __user *)arg);
पूर्ण

अटल पूर्णांक f2fs_ioc_हटाओ_encryption_key_all_users(काष्ठा file *filp,
						    अचिन्हित दीर्घ arg)
अणु
	अगर (!f2fs_sb_has_encrypt(F2FS_I_SB(file_inode(filp))))
		वापस -EOPNOTSUPP;

	वापस fscrypt_ioctl_हटाओ_key_all_users(filp, (व्योम __user *)arg);
पूर्ण

अटल पूर्णांक f2fs_ioc_get_encryption_key_status(काष्ठा file *filp,
					      अचिन्हित दीर्घ arg)
अणु
	अगर (!f2fs_sb_has_encrypt(F2FS_I_SB(file_inode(filp))))
		वापस -EOPNOTSUPP;

	वापस fscrypt_ioctl_get_key_status(filp, (व्योम __user *)arg);
पूर्ण

अटल पूर्णांक f2fs_ioc_get_encryption_nonce(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	अगर (!f2fs_sb_has_encrypt(F2FS_I_SB(file_inode(filp))))
		वापस -EOPNOTSUPP;

	वापस fscrypt_ioctl_get_nonce(filp, (व्योम __user *)arg);
पूर्ण

अटल पूर्णांक f2fs_ioc_gc(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	__u32 sync;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (get_user(sync, (__u32 __user *)arg))
		वापस -EFAULT;

	अगर (f2fs_पढ़ोonly(sbi->sb))
		वापस -EROFS;

	ret = mnt_want_ग_लिखो_file(filp);
	अगर (ret)
		वापस ret;

	अगर (!sync) अणु
		अगर (!करोwn_ग_लिखो_trylock(&sbi->gc_lock)) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		करोwn_ग_लिखो(&sbi->gc_lock);
	पूर्ण

	ret = f2fs_gc(sbi, sync, true, false, शून्य_SEGNO);
out:
	mnt_drop_ग_लिखो_file(filp);
	वापस ret;
पूर्ण

अटल पूर्णांक __f2fs_ioc_gc_range(काष्ठा file *filp, काष्ठा f2fs_gc_range *range)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(file_inode(filp));
	u64 end;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (f2fs_पढ़ोonly(sbi->sb))
		वापस -EROFS;

	end = range->start + range->len;
	अगर (end < range->start || range->start < MAIN_BLKADDR(sbi) ||
					end >= MAX_BLKADDR(sbi))
		वापस -EINVAL;

	ret = mnt_want_ग_लिखो_file(filp);
	अगर (ret)
		वापस ret;

करो_more:
	अगर (!range->sync) अणु
		अगर (!करोwn_ग_लिखो_trylock(&sbi->gc_lock)) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		करोwn_ग_लिखो(&sbi->gc_lock);
	पूर्ण

	ret = f2fs_gc(sbi, range->sync, true, false,
				GET_SEGNO(sbi, range->start));
	अगर (ret) अणु
		अगर (ret == -EBUSY)
			ret = -EAGAIN;
		जाओ out;
	पूर्ण
	range->start += BLKS_PER_SEC(sbi);
	अगर (range->start <= end)
		जाओ करो_more;
out:
	mnt_drop_ग_लिखो_file(filp);
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_ioc_gc_range(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा f2fs_gc_range range;

	अगर (copy_from_user(&range, (काष्ठा f2fs_gc_range __user *)arg,
							माप(range)))
		वापस -EFAULT;
	वापस __f2fs_ioc_gc_range(filp, &range);
पूर्ण

अटल पूर्णांक f2fs_ioc_ग_लिखो_checkpoपूर्णांक(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (f2fs_पढ़ोonly(sbi->sb))
		वापस -EROFS;

	अगर (unlikely(is_sbi_flag_set(sbi, SBI_CP_DISABLED))) अणु
		f2fs_info(sbi, "Skipping Checkpoint. Checkpoints currently disabled.");
		वापस -EINVAL;
	पूर्ण

	ret = mnt_want_ग_लिखो_file(filp);
	अगर (ret)
		वापस ret;

	ret = f2fs_sync_fs(sbi->sb, 1);

	mnt_drop_ग_लिखो_file(filp);
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_defragment_range(काष्ठा f2fs_sb_info *sbi,
					काष्ठा file *filp,
					काष्ठा f2fs_defragment *range)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा f2fs_map_blocks map = अणु .m_next_extent = शून्य,
					.m_seg_type = NO_CHECK_TYPE,
					.m_may_create = false पूर्ण;
	काष्ठा extent_info ei = अणु0, 0, 0पूर्ण;
	pgoff_t pg_start, pg_end, next_pgofs;
	अचिन्हित पूर्णांक blk_per_seg = sbi->blocks_per_seg;
	अचिन्हित पूर्णांक total = 0, sec_num;
	block_t blk_end = 0;
	bool fragmented = false;
	पूर्णांक err;

	/* अगर in-place-update policy is enabled, करोn't waste समय here */
	अगर (f2fs_should_update_inplace(inode, शून्य))
		वापस -EINVAL;

	pg_start = range->start >> PAGE_SHIFT;
	pg_end = (range->start + range->len) >> PAGE_SHIFT;

	f2fs_balance_fs(sbi, true);

	inode_lock(inode);

	/* ग_लिखोback all dirty pages in the range */
	err = filemap_ग_लिखो_and_रुको_range(inode->i_mapping, range->start,
						range->start + range->len - 1);
	अगर (err)
		जाओ out;

	/*
	 * lookup mapping info in extent cache, skip defragmenting अगर physical
	 * block addresses are continuous.
	 */
	अगर (f2fs_lookup_extent_cache(inode, pg_start, &ei)) अणु
		अगर (ei.fofs + ei.len >= pg_end)
			जाओ out;
	पूर्ण

	map.m_lblk = pg_start;
	map.m_next_pgofs = &next_pgofs;

	/*
	 * lookup mapping info in dnode page cache, skip defragmenting अगर all
	 * physical block addresses are continuous even अगर there are hole(s)
	 * in logical blocks.
	 */
	जबतक (map.m_lblk < pg_end) अणु
		map.m_len = pg_end - map.m_lblk;
		err = f2fs_map_blocks(inode, &map, 0, F2FS_GET_BLOCK_DEFAULT);
		अगर (err)
			जाओ out;

		अगर (!(map.m_flags & F2FS_MAP_FLAGS)) अणु
			map.m_lblk = next_pgofs;
			जारी;
		पूर्ण

		अगर (blk_end && blk_end != map.m_pblk)
			fragmented = true;

		/* record total count of block that we're going to move */
		total += map.m_len;

		blk_end = map.m_pblk + map.m_len;

		map.m_lblk += map.m_len;
	पूर्ण

	अगर (!fragmented) अणु
		total = 0;
		जाओ out;
	पूर्ण

	sec_num = DIV_ROUND_UP(total, BLKS_PER_SEC(sbi));

	/*
	 * make sure there are enough मुक्त section क्रम LFS allocation, this can
	 * aव्योम defragment running in SSR mode when मुक्त section are allocated
	 * पूर्णांकensively
	 */
	अगर (has_not_enough_मुक्त_secs(sbi, 0, sec_num)) अणु
		err = -EAGAIN;
		जाओ out;
	पूर्ण

	map.m_lblk = pg_start;
	map.m_len = pg_end - pg_start;
	total = 0;

	जबतक (map.m_lblk < pg_end) अणु
		pgoff_t idx;
		पूर्णांक cnt = 0;

करो_map:
		map.m_len = pg_end - map.m_lblk;
		err = f2fs_map_blocks(inode, &map, 0, F2FS_GET_BLOCK_DEFAULT);
		अगर (err)
			जाओ clear_out;

		अगर (!(map.m_flags & F2FS_MAP_FLAGS)) अणु
			map.m_lblk = next_pgofs;
			जाओ check;
		पूर्ण

		set_inode_flag(inode, FI_DO_DEFRAG);

		idx = map.m_lblk;
		जबतक (idx < map.m_lblk + map.m_len && cnt < blk_per_seg) अणु
			काष्ठा page *page;

			page = f2fs_get_lock_data_page(inode, idx, true);
			अगर (IS_ERR(page)) अणु
				err = PTR_ERR(page);
				जाओ clear_out;
			पूर्ण

			set_page_dirty(page);
			f2fs_put_page(page, 1);

			idx++;
			cnt++;
			total++;
		पूर्ण

		map.m_lblk = idx;
check:
		अगर (map.m_lblk < pg_end && cnt < blk_per_seg)
			जाओ करो_map;

		clear_inode_flag(inode, FI_DO_DEFRAG);

		err = filemap_fdataग_लिखो(inode->i_mapping);
		अगर (err)
			जाओ out;
	पूर्ण
clear_out:
	clear_inode_flag(inode, FI_DO_DEFRAG);
out:
	inode_unlock(inode);
	अगर (!err)
		range->len = (u64)total << PAGE_SHIFT;
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_ioc_defragment(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा f2fs_defragment range;
	पूर्णांक err;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (!S_ISREG(inode->i_mode) || f2fs_is_atomic_file(inode))
		वापस -EINVAL;

	अगर (f2fs_पढ़ोonly(sbi->sb))
		वापस -EROFS;

	अगर (copy_from_user(&range, (काष्ठा f2fs_defragment __user *)arg,
							माप(range)))
		वापस -EFAULT;

	/* verअगरy alignment of offset & size */
	अगर (range.start & (F2FS_BLKSIZE - 1) || range.len & (F2FS_BLKSIZE - 1))
		वापस -EINVAL;

	अगर (unlikely((range.start + range.len) >> PAGE_SHIFT >
					max_file_blocks(inode)))
		वापस -EINVAL;

	err = mnt_want_ग_लिखो_file(filp);
	अगर (err)
		वापस err;

	err = f2fs_defragment_range(sbi, filp, &range);
	mnt_drop_ग_लिखो_file(filp);

	f2fs_update_समय(sbi, REQ_TIME);
	अगर (err < 0)
		वापस err;

	अगर (copy_to_user((काष्ठा f2fs_defragment __user *)arg, &range,
							माप(range)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक f2fs_move_file_range(काष्ठा file *file_in, loff_t pos_in,
			काष्ठा file *file_out, loff_t pos_out, माप_प्रकार len)
अणु
	काष्ठा inode *src = file_inode(file_in);
	काष्ठा inode *dst = file_inode(file_out);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(src);
	माप_प्रकार olen = len, dst_max_i_size = 0;
	माप_प्रकार dst_osize;
	पूर्णांक ret;

	अगर (file_in->f_path.mnt != file_out->f_path.mnt ||
				src->i_sb != dst->i_sb)
		वापस -EXDEV;

	अगर (unlikely(f2fs_पढ़ोonly(src->i_sb)))
		वापस -EROFS;

	अगर (!S_ISREG(src->i_mode) || !S_ISREG(dst->i_mode))
		वापस -EINVAL;

	अगर (IS_ENCRYPTED(src) || IS_ENCRYPTED(dst))
		वापस -EOPNOTSUPP;

	अगर (pos_out < 0 || pos_in < 0)
		वापस -EINVAL;

	अगर (src == dst) अणु
		अगर (pos_in == pos_out)
			वापस 0;
		अगर (pos_out > pos_in && pos_out < pos_in + len)
			वापस -EINVAL;
	पूर्ण

	inode_lock(src);
	अगर (src != dst) अणु
		ret = -EBUSY;
		अगर (!inode_trylock(dst))
			जाओ out;
	पूर्ण

	ret = -EINVAL;
	अगर (pos_in + len > src->i_size || pos_in + len < pos_in)
		जाओ out_unlock;
	अगर (len == 0)
		olen = len = src->i_size - pos_in;
	अगर (pos_in + len == src->i_size)
		len = ALIGN(src->i_size, F2FS_BLKSIZE) - pos_in;
	अगर (len == 0) अणु
		ret = 0;
		जाओ out_unlock;
	पूर्ण

	dst_osize = dst->i_size;
	अगर (pos_out + olen > dst->i_size)
		dst_max_i_size = pos_out + olen;

	/* verअगरy the end result is block aligned */
	अगर (!IS_ALIGNED(pos_in, F2FS_BLKSIZE) ||
			!IS_ALIGNED(pos_in + len, F2FS_BLKSIZE) ||
			!IS_ALIGNED(pos_out, F2FS_BLKSIZE))
		जाओ out_unlock;

	ret = f2fs_convert_अंतरभूत_inode(src);
	अगर (ret)
		जाओ out_unlock;

	ret = f2fs_convert_अंतरभूत_inode(dst);
	अगर (ret)
		जाओ out_unlock;

	/* ग_लिखो out all dirty pages from offset */
	ret = filemap_ग_लिखो_and_रुको_range(src->i_mapping,
					pos_in, pos_in + len);
	अगर (ret)
		जाओ out_unlock;

	ret = filemap_ग_लिखो_and_रुको_range(dst->i_mapping,
					pos_out, pos_out + len);
	अगर (ret)
		जाओ out_unlock;

	f2fs_balance_fs(sbi, true);

	करोwn_ग_लिखो(&F2FS_I(src)->i_gc_rwsem[WRITE]);
	अगर (src != dst) अणु
		ret = -EBUSY;
		अगर (!करोwn_ग_लिखो_trylock(&F2FS_I(dst)->i_gc_rwsem[WRITE]))
			जाओ out_src;
	पूर्ण

	f2fs_lock_op(sbi);
	ret = __exchange_data_block(src, dst, pos_in >> F2FS_BLKSIZE_BITS,
				pos_out >> F2FS_BLKSIZE_BITS,
				len >> F2FS_BLKSIZE_BITS, false);

	अगर (!ret) अणु
		अगर (dst_max_i_size)
			f2fs_i_size_ग_लिखो(dst, dst_max_i_size);
		अन्यथा अगर (dst_osize != dst->i_size)
			f2fs_i_size_ग_लिखो(dst, dst_osize);
	पूर्ण
	f2fs_unlock_op(sbi);

	अगर (src != dst)
		up_ग_लिखो(&F2FS_I(dst)->i_gc_rwsem[WRITE]);
out_src:
	up_ग_लिखो(&F2FS_I(src)->i_gc_rwsem[WRITE]);
out_unlock:
	अगर (src != dst)
		inode_unlock(dst);
out:
	inode_unlock(src);
	वापस ret;
पूर्ण

अटल पूर्णांक __f2fs_ioc_move_range(काष्ठा file *filp,
				काष्ठा f2fs_move_range *range)
अणु
	काष्ठा fd dst;
	पूर्णांक err;

	अगर (!(filp->f_mode & FMODE_READ) ||
			!(filp->f_mode & FMODE_WRITE))
		वापस -EBADF;

	dst = fdget(range->dst_fd);
	अगर (!dst.file)
		वापस -EBADF;

	अगर (!(dst.file->f_mode & FMODE_WRITE)) अणु
		err = -EBADF;
		जाओ err_out;
	पूर्ण

	err = mnt_want_ग_लिखो_file(filp);
	अगर (err)
		जाओ err_out;

	err = f2fs_move_file_range(filp, range->pos_in, dst.file,
					range->pos_out, range->len);

	mnt_drop_ग_लिखो_file(filp);
err_out:
	fdput(dst);
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_ioc_move_range(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा f2fs_move_range range;

	अगर (copy_from_user(&range, (काष्ठा f2fs_move_range __user *)arg,
							माप(range)))
		वापस -EFAULT;
	वापस __f2fs_ioc_move_range(filp, &range);
पूर्ण

अटल पूर्णांक f2fs_ioc_flush_device(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा sit_info *sm = SIT_I(sbi);
	अचिन्हित पूर्णांक start_segno = 0, end_segno = 0;
	अचिन्हित पूर्णांक dev_start_segno = 0, dev_end_segno = 0;
	काष्ठा f2fs_flush_device range;
	पूर्णांक ret;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (f2fs_पढ़ोonly(sbi->sb))
		वापस -EROFS;

	अगर (unlikely(is_sbi_flag_set(sbi, SBI_CP_DISABLED)))
		वापस -EINVAL;

	अगर (copy_from_user(&range, (काष्ठा f2fs_flush_device __user *)arg,
							माप(range)))
		वापस -EFAULT;

	अगर (!f2fs_is_multi_device(sbi) || sbi->s_ndevs - 1 <= range.dev_num ||
			__is_large_section(sbi)) अणु
		f2fs_warn(sbi, "Can't flush %u in %d for segs_per_sec %u != 1",
			  range.dev_num, sbi->s_ndevs, sbi->segs_per_sec);
		वापस -EINVAL;
	पूर्ण

	ret = mnt_want_ग_लिखो_file(filp);
	अगर (ret)
		वापस ret;

	अगर (range.dev_num != 0)
		dev_start_segno = GET_SEGNO(sbi, FDEV(range.dev_num).start_blk);
	dev_end_segno = GET_SEGNO(sbi, FDEV(range.dev_num).end_blk);

	start_segno = sm->last_victim[FLUSH_DEVICE];
	अगर (start_segno < dev_start_segno || start_segno >= dev_end_segno)
		start_segno = dev_start_segno;
	end_segno = min(start_segno + range.segments, dev_end_segno);

	जबतक (start_segno < end_segno) अणु
		अगर (!करोwn_ग_लिखो_trylock(&sbi->gc_lock)) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण
		sm->last_victim[GC_CB] = end_segno + 1;
		sm->last_victim[GC_GREEDY] = end_segno + 1;
		sm->last_victim[ALLOC_NEXT] = end_segno + 1;
		ret = f2fs_gc(sbi, true, true, true, start_segno);
		अगर (ret == -EAGAIN)
			ret = 0;
		अन्यथा अगर (ret < 0)
			अवरोध;
		start_segno++;
	पूर्ण
out:
	mnt_drop_ग_लिखो_file(filp);
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_ioc_get_features(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	u32 sb_feature = le32_to_cpu(F2FS_I_SB(inode)->raw_super->feature);

	/* Must validate to set it with SQLite behavior in Android. */
	sb_feature |= F2FS_FEATURE_ATOMIC_WRITE;

	वापस put_user(sb_feature, (u32 __user *)arg);
पूर्ण

#अगर_घोषित CONFIG_QUOTA
पूर्णांक f2fs_transfer_project_quota(काष्ठा inode *inode, kprojid_t kprojid)
अणु
	काष्ठा dquot *transfer_to[MAXQUOTAS] = अणुपूर्ण;
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा super_block *sb = sbi->sb;
	पूर्णांक err = 0;

	transfer_to[PRJQUOTA] = dqget(sb, make_kqid_projid(kprojid));
	अगर (!IS_ERR(transfer_to[PRJQUOTA])) अणु
		err = __dquot_transfer(inode, transfer_to);
		अगर (err)
			set_sbi_flag(sbi, SBI_QUOTA_NEED_REPAIR);
		dqput(transfer_to[PRJQUOTA]);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_ioc_setproject(काष्ठा inode *inode, __u32 projid)
अणु
	काष्ठा f2fs_inode_info *fi = F2FS_I(inode);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा page *ipage;
	kprojid_t kprojid;
	पूर्णांक err;

	अगर (!f2fs_sb_has_project_quota(sbi)) अणु
		अगर (projid != F2FS_DEF_PROJID)
			वापस -EOPNOTSUPP;
		अन्यथा
			वापस 0;
	पूर्ण

	अगर (!f2fs_has_extra_attr(inode))
		वापस -EOPNOTSUPP;

	kprojid = make_kprojid(&init_user_ns, (projid_t)projid);

	अगर (projid_eq(kprojid, F2FS_I(inode)->i_projid))
		वापस 0;

	err = -EPERM;
	/* Is it quota file? Do not allow user to mess with it */
	अगर (IS_NOQUOTA(inode))
		वापस err;

	ipage = f2fs_get_node_page(sbi, inode->i_ino);
	अगर (IS_ERR(ipage))
		वापस PTR_ERR(ipage);

	अगर (!F2FS_FITS_IN_INODE(F2FS_INODE(ipage), fi->i_extra_isize,
								i_projid)) अणु
		err = -EOVERFLOW;
		f2fs_put_page(ipage, 1);
		वापस err;
	पूर्ण
	f2fs_put_page(ipage, 1);

	err = dquot_initialize(inode);
	अगर (err)
		वापस err;

	f2fs_lock_op(sbi);
	err = f2fs_transfer_project_quota(inode, kprojid);
	अगर (err)
		जाओ out_unlock;

	F2FS_I(inode)->i_projid = kprojid;
	inode->i_स_समय = current_समय(inode);
	f2fs_mark_inode_dirty_sync(inode, true);
out_unlock:
	f2fs_unlock_op(sbi);
	वापस err;
पूर्ण
#अन्यथा
पूर्णांक f2fs_transfer_project_quota(काष्ठा inode *inode, kprojid_t kprojid)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक f2fs_ioc_setproject(काष्ठा inode *inode, __u32 projid)
अणु
	अगर (projid != F2FS_DEF_PROJID)
		वापस -EOPNOTSUPP;
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक f2fs_fileattr_get(काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा f2fs_inode_info *fi = F2FS_I(inode);
	u32 fsflags = f2fs_अगरlags_to_fsflags(fi->i_flags);

	अगर (IS_ENCRYPTED(inode))
		fsflags |= FS_ENCRYPT_FL;
	अगर (IS_VERITY(inode))
		fsflags |= FS_VERITY_FL;
	अगर (f2fs_has_अंतरभूत_data(inode) || f2fs_has_अंतरभूत_dentry(inode))
		fsflags |= FS_INLINE_DATA_FL;
	अगर (is_inode_flag_set(inode, FI_PIN_खाता))
		fsflags |= FS_NOCOW_FL;

	fileattr_fill_flags(fa, fsflags & F2FS_GETTABLE_FS_FL);

	अगर (f2fs_sb_has_project_quota(F2FS_I_SB(inode)))
		fa->fsx_projid = from_kprojid(&init_user_ns, fi->i_projid);

	वापस 0;
पूर्ण

पूर्णांक f2fs_fileattr_set(काष्ठा user_namespace *mnt_userns,
		      काष्ठा dentry *dentry, काष्ठा fileattr *fa)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	u32 fsflags = fa->flags, mask = F2FS_SETTABLE_FS_FL;
	u32 अगरlags;
	पूर्णांक err;

	अगर (unlikely(f2fs_cp_error(F2FS_I_SB(inode))))
		वापस -EIO;
	अगर (!f2fs_is_checkpoपूर्णांक_पढ़ोy(F2FS_I_SB(inode)))
		वापस -ENOSPC;
	अगर (fsflags & ~F2FS_GETTABLE_FS_FL)
		वापस -EOPNOTSUPP;
	fsflags &= F2FS_SETTABLE_FS_FL;
	अगर (!fa->flags_valid)
		mask &= FS_COMMON_FL;

	अगरlags = f2fs_fsflags_to_अगरlags(fsflags);
	अगर (f2fs_mask_flags(inode->i_mode, अगरlags) != अगरlags)
		वापस -EOPNOTSUPP;

	err = f2fs_setflags_common(inode, अगरlags, f2fs_fsflags_to_अगरlags(mask));
	अगर (!err)
		err = f2fs_ioc_setproject(inode, fa->fsx_projid);

	वापस err;
पूर्ण

पूर्णांक f2fs_pin_file_control(काष्ठा inode *inode, bool inc)
अणु
	काष्ठा f2fs_inode_info *fi = F2FS_I(inode);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);

	/* Use i_gc_failures क्रम normal file as a risk संकेत. */
	अगर (inc)
		f2fs_i_gc_failures_ग_लिखो(inode,
				fi->i_gc_failures[GC_FAILURE_PIN] + 1);

	अगर (fi->i_gc_failures[GC_FAILURE_PIN] > sbi->gc_pin_file_threshold) अणु
		f2fs_warn(sbi, "%s: Enable GC = ino %lx after %x GC trials",
			  __func__, inode->i_ino,
			  fi->i_gc_failures[GC_FAILURE_PIN]);
		clear_inode_flag(inode, FI_PIN_खाता);
		वापस -EAGAIN;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक f2fs_ioc_set_pin_file(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	__u32 pin;
	पूर्णांक ret = 0;

	अगर (get_user(pin, (__u32 __user *)arg))
		वापस -EFAULT;

	अगर (!S_ISREG(inode->i_mode))
		वापस -EINVAL;

	अगर (f2fs_पढ़ोonly(F2FS_I_SB(inode)->sb))
		वापस -EROFS;

	ret = mnt_want_ग_लिखो_file(filp);
	अगर (ret)
		वापस ret;

	inode_lock(inode);

	अगर (f2fs_should_update_outplace(inode, शून्य)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!pin) अणु
		clear_inode_flag(inode, FI_PIN_खाता);
		f2fs_i_gc_failures_ग_लिखो(inode, 0);
		जाओ करोne;
	पूर्ण

	अगर (f2fs_pin_file_control(inode, false)) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	ret = f2fs_convert_अंतरभूत_inode(inode);
	अगर (ret)
		जाओ out;

	अगर (!f2fs_disable_compressed_file(inode)) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	set_inode_flag(inode, FI_PIN_खाता);
	ret = F2FS_I(inode)->i_gc_failures[GC_FAILURE_PIN];
करोne:
	f2fs_update_समय(F2FS_I_SB(inode), REQ_TIME);
out:
	inode_unlock(inode);
	mnt_drop_ग_लिखो_file(filp);
	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_ioc_get_pin_file(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	__u32 pin = 0;

	अगर (is_inode_flag_set(inode, FI_PIN_खाता))
		pin = F2FS_I(inode)->i_gc_failures[GC_FAILURE_PIN];
	वापस put_user(pin, (u32 __user *)arg);
पूर्ण

पूर्णांक f2fs_precache_extents(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_inode_info *fi = F2FS_I(inode);
	काष्ठा f2fs_map_blocks map;
	pgoff_t m_next_extent;
	loff_t end;
	पूर्णांक err;

	अगर (is_inode_flag_set(inode, FI_NO_EXTENT))
		वापस -EOPNOTSUPP;

	map.m_lblk = 0;
	map.m_next_pgofs = शून्य;
	map.m_next_extent = &m_next_extent;
	map.m_seg_type = NO_CHECK_TYPE;
	map.m_may_create = false;
	end = max_file_blocks(inode);

	जबतक (map.m_lblk < end) अणु
		map.m_len = end - map.m_lblk;

		करोwn_ग_लिखो(&fi->i_gc_rwsem[WRITE]);
		err = f2fs_map_blocks(inode, &map, 0, F2FS_GET_BLOCK_PRECACHE);
		up_ग_लिखो(&fi->i_gc_rwsem[WRITE]);
		अगर (err)
			वापस err;

		map.m_lblk = m_next_extent;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक f2fs_ioc_precache_extents(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	वापस f2fs_precache_extents(file_inode(filp));
पूर्ण

अटल पूर्णांक f2fs_ioc_resize_fs(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(file_inode(filp));
	__u64 block_count;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (f2fs_पढ़ोonly(sbi->sb))
		वापस -EROFS;

	अगर (copy_from_user(&block_count, (व्योम __user *)arg,
			   माप(block_count)))
		वापस -EFAULT;

	वापस f2fs_resize_fs(sbi, block_count);
पूर्ण

अटल पूर्णांक f2fs_ioc_enable_verity(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);

	f2fs_update_समय(F2FS_I_SB(inode), REQ_TIME);

	अगर (!f2fs_sb_has_verity(F2FS_I_SB(inode))) अणु
		f2fs_warn(F2FS_I_SB(inode),
			  "Can't enable fs-verity on inode %lu: the verity feature is not enabled on this filesystem.\n",
			  inode->i_ino);
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस fsverity_ioctl_enable(filp, (स्थिर व्योम __user *)arg);
पूर्ण

अटल पूर्णांक f2fs_ioc_measure_verity(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	अगर (!f2fs_sb_has_verity(F2FS_I_SB(file_inode(filp))))
		वापस -EOPNOTSUPP;

	वापस fsverity_ioctl_measure(filp, (व्योम __user *)arg);
पूर्ण

अटल पूर्णांक f2fs_ioc_पढ़ो_verity_metadata(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	अगर (!f2fs_sb_has_verity(F2FS_I_SB(file_inode(filp))))
		वापस -EOPNOTSUPP;

	वापस fsverity_ioctl_पढ़ो_metadata(filp, (स्थिर व्योम __user *)arg);
पूर्ण

अटल पूर्णांक f2fs_ioc_getfslabel(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	अक्षर *vbuf;
	पूर्णांक count;
	पूर्णांक err = 0;

	vbuf = f2fs_kzalloc(sbi, MAX_VOLUME_NAME, GFP_KERNEL);
	अगर (!vbuf)
		वापस -ENOMEM;

	करोwn_पढ़ो(&sbi->sb_lock);
	count = utf16s_to_utf8s(sbi->raw_super->volume_name,
			ARRAY_SIZE(sbi->raw_super->volume_name),
			UTF16_LITTLE_ENDIAN, vbuf, MAX_VOLUME_NAME);
	up_पढ़ो(&sbi->sb_lock);

	अगर (copy_to_user((अक्षर __user *)arg, vbuf,
				min(FSLABEL_MAX, count)))
		err = -EFAULT;

	kमुक्त(vbuf);
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_ioc_setfslabel(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	अक्षर *vbuf;
	पूर्णांक err = 0;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	vbuf = strndup_user((स्थिर अक्षर __user *)arg, FSLABEL_MAX);
	अगर (IS_ERR(vbuf))
		वापस PTR_ERR(vbuf);

	err = mnt_want_ग_लिखो_file(filp);
	अगर (err)
		जाओ out;

	करोwn_ग_लिखो(&sbi->sb_lock);

	स_रखो(sbi->raw_super->volume_name, 0,
			माप(sbi->raw_super->volume_name));
	utf8s_to_utf16s(vbuf, म_माप(vbuf), UTF16_LITTLE_ENDIAN,
			sbi->raw_super->volume_name,
			ARRAY_SIZE(sbi->raw_super->volume_name));

	err = f2fs_commit_super(sbi, false);

	up_ग_लिखो(&sbi->sb_lock);

	mnt_drop_ग_लिखो_file(filp);
out:
	kमुक्त(vbuf);
	वापस err;
पूर्ण

अटल पूर्णांक f2fs_get_compress_blocks(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	__u64 blocks;

	अगर (!f2fs_sb_has_compression(F2FS_I_SB(inode)))
		वापस -EOPNOTSUPP;

	अगर (!f2fs_compressed_file(inode))
		वापस -EINVAL;

	blocks = atomic_पढ़ो(&F2FS_I(inode)->i_compr_blocks);
	वापस put_user(blocks, (u64 __user *)arg);
पूर्ण

अटल पूर्णांक release_compress_blocks(काष्ठा dnode_of_data *dn, pgoff_t count)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dn->inode);
	अचिन्हित पूर्णांक released_blocks = 0;
	पूर्णांक cluster_size = F2FS_I(dn->inode)->i_cluster_size;
	block_t blkaddr;
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		blkaddr = data_blkaddr(dn->inode, dn->node_page,
						dn->ofs_in_node + i);

		अगर (!__is_valid_data_blkaddr(blkaddr))
			जारी;
		अगर (unlikely(!f2fs_is_valid_blkaddr(sbi, blkaddr,
					DATA_GENERIC_ENHANCE)))
			वापस -EFSCORRUPTED;
	पूर्ण

	जबतक (count) अणु
		पूर्णांक compr_blocks = 0;

		क्रम (i = 0; i < cluster_size; i++, dn->ofs_in_node++) अणु
			blkaddr = f2fs_data_blkaddr(dn);

			अगर (i == 0) अणु
				अगर (blkaddr == COMPRESS_ADDR)
					जारी;
				dn->ofs_in_node += cluster_size;
				जाओ next;
			पूर्ण

			अगर (__is_valid_data_blkaddr(blkaddr))
				compr_blocks++;

			अगर (blkaddr != NEW_ADDR)
				जारी;

			dn->data_blkaddr = शून्य_ADDR;
			f2fs_set_data_blkaddr(dn);
		पूर्ण

		f2fs_i_compr_blocks_update(dn->inode, compr_blocks, false);
		dec_valid_block_count(sbi, dn->inode,
					cluster_size - compr_blocks);

		released_blocks += cluster_size - compr_blocks;
next:
		count -= cluster_size;
	पूर्ण

	वापस released_blocks;
पूर्ण

अटल पूर्णांक f2fs_release_compress_blocks(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	pgoff_t page_idx = 0, last_idx;
	अचिन्हित पूर्णांक released_blocks = 0;
	पूर्णांक ret;
	पूर्णांक ग_लिखोcount;

	अगर (!f2fs_sb_has_compression(F2FS_I_SB(inode)))
		वापस -EOPNOTSUPP;

	अगर (!f2fs_compressed_file(inode))
		वापस -EINVAL;

	अगर (f2fs_पढ़ोonly(sbi->sb))
		वापस -EROFS;

	ret = mnt_want_ग_लिखो_file(filp);
	अगर (ret)
		वापस ret;

	f2fs_balance_fs(F2FS_I_SB(inode), true);

	inode_lock(inode);

	ग_लिखोcount = atomic_पढ़ो(&inode->i_ग_लिखोcount);
	अगर ((filp->f_mode & FMODE_WRITE && ग_लिखोcount != 1) ||
			(!(filp->f_mode & FMODE_WRITE) && ग_लिखोcount)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (IS_IMMUTABLE(inode)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = filemap_ग_लिखो_and_रुको_range(inode->i_mapping, 0, Lदीर्घ_उच्च);
	अगर (ret)
		जाओ out;

	F2FS_I(inode)->i_flags |= F2FS_IMMUTABLE_FL;
	f2fs_set_inode_flags(inode);
	inode->i_स_समय = current_समय(inode);
	f2fs_mark_inode_dirty_sync(inode, true);

	अगर (!atomic_पढ़ो(&F2FS_I(inode)->i_compr_blocks))
		जाओ out;

	करोwn_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
	करोwn_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);

	last_idx = DIV_ROUND_UP(i_size_पढ़ो(inode), PAGE_SIZE);

	जबतक (page_idx < last_idx) अणु
		काष्ठा dnode_of_data dn;
		pgoff_t end_offset, count;

		set_new_dnode(&dn, inode, शून्य, शून्य, 0);
		ret = f2fs_get_dnode_of_data(&dn, page_idx, LOOKUP_NODE);
		अगर (ret) अणु
			अगर (ret == -ENOENT) अणु
				page_idx = f2fs_get_next_page_offset(&dn,
								page_idx);
				ret = 0;
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		end_offset = ADDRS_PER_PAGE(dn.node_page, inode);
		count = min(end_offset - dn.ofs_in_node, last_idx - page_idx);
		count = round_up(count, F2FS_I(inode)->i_cluster_size);

		ret = release_compress_blocks(&dn, count);

		f2fs_put_dnode(&dn);

		अगर (ret < 0)
			अवरोध;

		page_idx += count;
		released_blocks += ret;
	पूर्ण

	up_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
	up_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);
out:
	inode_unlock(inode);

	mnt_drop_ग_लिखो_file(filp);

	अगर (ret >= 0) अणु
		ret = put_user(released_blocks, (u64 __user *)arg);
	पूर्ण अन्यथा अगर (released_blocks &&
			atomic_पढ़ो(&F2FS_I(inode)->i_compr_blocks)) अणु
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		f2fs_warn(sbi, "%s: partial blocks were released i_ino=%lx "
			"iblocks=%llu, released=%u, compr_blocks=%u, "
			"run fsck to fix.",
			__func__, inode->i_ino, inode->i_blocks,
			released_blocks,
			atomic_पढ़ो(&F2FS_I(inode)->i_compr_blocks));
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक reserve_compress_blocks(काष्ठा dnode_of_data *dn, pgoff_t count)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(dn->inode);
	अचिन्हित पूर्णांक reserved_blocks = 0;
	पूर्णांक cluster_size = F2FS_I(dn->inode)->i_cluster_size;
	block_t blkaddr;
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		blkaddr = data_blkaddr(dn->inode, dn->node_page,
						dn->ofs_in_node + i);

		अगर (!__is_valid_data_blkaddr(blkaddr))
			जारी;
		अगर (unlikely(!f2fs_is_valid_blkaddr(sbi, blkaddr,
					DATA_GENERIC_ENHANCE)))
			वापस -EFSCORRUPTED;
	पूर्ण

	जबतक (count) अणु
		पूर्णांक compr_blocks = 0;
		blkcnt_t reserved;
		पूर्णांक ret;

		क्रम (i = 0; i < cluster_size; i++, dn->ofs_in_node++) अणु
			blkaddr = f2fs_data_blkaddr(dn);

			अगर (i == 0) अणु
				अगर (blkaddr == COMPRESS_ADDR)
					जारी;
				dn->ofs_in_node += cluster_size;
				जाओ next;
			पूर्ण

			अगर (__is_valid_data_blkaddr(blkaddr)) अणु
				compr_blocks++;
				जारी;
			पूर्ण

			dn->data_blkaddr = NEW_ADDR;
			f2fs_set_data_blkaddr(dn);
		पूर्ण

		reserved = cluster_size - compr_blocks;
		ret = inc_valid_block_count(sbi, dn->inode, &reserved);
		अगर (ret)
			वापस ret;

		अगर (reserved != cluster_size - compr_blocks)
			वापस -ENOSPC;

		f2fs_i_compr_blocks_update(dn->inode, compr_blocks, true);

		reserved_blocks += reserved;
next:
		count -= cluster_size;
	पूर्ण

	वापस reserved_blocks;
पूर्ण

अटल पूर्णांक f2fs_reserve_compress_blocks(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	pgoff_t page_idx = 0, last_idx;
	अचिन्हित पूर्णांक reserved_blocks = 0;
	पूर्णांक ret;

	अगर (!f2fs_sb_has_compression(F2FS_I_SB(inode)))
		वापस -EOPNOTSUPP;

	अगर (!f2fs_compressed_file(inode))
		वापस -EINVAL;

	अगर (f2fs_पढ़ोonly(sbi->sb))
		वापस -EROFS;

	ret = mnt_want_ग_लिखो_file(filp);
	अगर (ret)
		वापस ret;

	अगर (atomic_पढ़ो(&F2FS_I(inode)->i_compr_blocks))
		जाओ out;

	f2fs_balance_fs(F2FS_I_SB(inode), true);

	inode_lock(inode);

	अगर (!IS_IMMUTABLE(inode)) अणु
		ret = -EINVAL;
		जाओ unlock_inode;
	पूर्ण

	करोwn_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
	करोwn_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);

	last_idx = DIV_ROUND_UP(i_size_पढ़ो(inode), PAGE_SIZE);

	जबतक (page_idx < last_idx) अणु
		काष्ठा dnode_of_data dn;
		pgoff_t end_offset, count;

		set_new_dnode(&dn, inode, शून्य, शून्य, 0);
		ret = f2fs_get_dnode_of_data(&dn, page_idx, LOOKUP_NODE);
		अगर (ret) अणु
			अगर (ret == -ENOENT) अणु
				page_idx = f2fs_get_next_page_offset(&dn,
								page_idx);
				ret = 0;
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		end_offset = ADDRS_PER_PAGE(dn.node_page, inode);
		count = min(end_offset - dn.ofs_in_node, last_idx - page_idx);
		count = round_up(count, F2FS_I(inode)->i_cluster_size);

		ret = reserve_compress_blocks(&dn, count);

		f2fs_put_dnode(&dn);

		अगर (ret < 0)
			अवरोध;

		page_idx += count;
		reserved_blocks += ret;
	पूर्ण

	up_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
	up_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);

	अगर (ret >= 0) अणु
		F2FS_I(inode)->i_flags &= ~F2FS_IMMUTABLE_FL;
		f2fs_set_inode_flags(inode);
		inode->i_स_समय = current_समय(inode);
		f2fs_mark_inode_dirty_sync(inode, true);
	पूर्ण
unlock_inode:
	inode_unlock(inode);
out:
	mnt_drop_ग_लिखो_file(filp);

	अगर (ret >= 0) अणु
		ret = put_user(reserved_blocks, (u64 __user *)arg);
	पूर्ण अन्यथा अगर (reserved_blocks &&
			atomic_पढ़ो(&F2FS_I(inode)->i_compr_blocks)) अणु
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		f2fs_warn(sbi, "%s: partial blocks were released i_ino=%lx "
			"iblocks=%llu, reserved=%u, compr_blocks=%u, "
			"run fsck to fix.",
			__func__, inode->i_ino, inode->i_blocks,
			reserved_blocks,
			atomic_पढ़ो(&F2FS_I(inode)->i_compr_blocks));
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_secure_erase(काष्ठा block_device *bdev, काष्ठा inode *inode,
		pgoff_t off, block_t block, block_t len, u32 flags)
अणु
	काष्ठा request_queue *q = bdev_get_queue(bdev);
	sector_t sector = SECTOR_FROM_BLOCK(block);
	sector_t nr_sects = SECTOR_FROM_BLOCK(len);
	पूर्णांक ret = 0;

	अगर (!q)
		वापस -ENXIO;

	अगर (flags & F2FS_TRIM_खाता_DISCARD)
		ret = blkdev_issue_discard(bdev, sector, nr_sects, GFP_NOFS,
						blk_queue_secure_erase(q) ?
						BLKDEV_DISCARD_SECURE : 0);

	अगर (!ret && (flags & F2FS_TRIM_खाता_ZEROOUT)) अणु
		अगर (IS_ENCRYPTED(inode))
			ret = fscrypt_zeroout_range(inode, off, block, len);
		अन्यथा
			ret = blkdev_issue_zeroout(bdev, sector, nr_sects,
					GFP_NOFS, 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_sec_trim_file(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा block_device *prev_bdev = शून्य;
	काष्ठा f2fs_sectrim_range range;
	pgoff_t index, pg_end, prev_index = 0;
	block_t prev_block = 0, len = 0;
	loff_t end_addr;
	bool to_end = false;
	पूर्णांक ret = 0;

	अगर (!(filp->f_mode & FMODE_WRITE))
		वापस -EBADF;

	अगर (copy_from_user(&range, (काष्ठा f2fs_sectrim_range __user *)arg,
				माप(range)))
		वापस -EFAULT;

	अगर (range.flags == 0 || (range.flags & ~F2FS_TRIM_खाता_MASK) ||
			!S_ISREG(inode->i_mode))
		वापस -EINVAL;

	अगर (((range.flags & F2FS_TRIM_खाता_DISCARD) &&
			!f2fs_hw_support_discard(sbi)) ||
			((range.flags & F2FS_TRIM_खाता_ZEROOUT) &&
			 IS_ENCRYPTED(inode) && f2fs_is_multi_device(sbi)))
		वापस -EOPNOTSUPP;

	file_start_ग_लिखो(filp);
	inode_lock(inode);

	अगर (f2fs_is_atomic_file(inode) || f2fs_compressed_file(inode) ||
			range.start >= inode->i_size) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (range.len == 0)
		जाओ err;

	अगर (inode->i_size - range.start > range.len) अणु
		end_addr = range.start + range.len;
	पूर्ण अन्यथा अणु
		end_addr = range.len == (u64)-1 ?
			sbi->sb->s_maxbytes : inode->i_size;
		to_end = true;
	पूर्ण

	अगर (!IS_ALIGNED(range.start, F2FS_BLKSIZE) ||
			(!to_end && !IS_ALIGNED(end_addr, F2FS_BLKSIZE))) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	index = F2FS_BYTES_TO_BLK(range.start);
	pg_end = DIV_ROUND_UP(end_addr, F2FS_BLKSIZE);

	ret = f2fs_convert_अंतरभूत_inode(inode);
	अगर (ret)
		जाओ err;

	करोwn_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
	करोwn_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);

	ret = filemap_ग_लिखो_and_रुको_range(mapping, range.start,
			to_end ? Lदीर्घ_उच्च : end_addr - 1);
	अगर (ret)
		जाओ out;

	truncate_inode_pages_range(mapping, range.start,
			to_end ? -1 : end_addr - 1);

	जबतक (index < pg_end) अणु
		काष्ठा dnode_of_data dn;
		pgoff_t end_offset, count;
		पूर्णांक i;

		set_new_dnode(&dn, inode, शून्य, शून्य, 0);
		ret = f2fs_get_dnode_of_data(&dn, index, LOOKUP_NODE);
		अगर (ret) अणु
			अगर (ret == -ENOENT) अणु
				index = f2fs_get_next_page_offset(&dn, index);
				जारी;
			पूर्ण
			जाओ out;
		पूर्ण

		end_offset = ADDRS_PER_PAGE(dn.node_page, inode);
		count = min(end_offset - dn.ofs_in_node, pg_end - index);
		क्रम (i = 0; i < count; i++, index++, dn.ofs_in_node++) अणु
			काष्ठा block_device *cur_bdev;
			block_t blkaddr = f2fs_data_blkaddr(&dn);

			अगर (!__is_valid_data_blkaddr(blkaddr))
				जारी;

			अगर (!f2fs_is_valid_blkaddr(sbi, blkaddr,
						DATA_GENERIC_ENHANCE)) अणु
				ret = -EFSCORRUPTED;
				f2fs_put_dnode(&dn);
				जाओ out;
			पूर्ण

			cur_bdev = f2fs_target_device(sbi, blkaddr, शून्य);
			अगर (f2fs_is_multi_device(sbi)) अणु
				पूर्णांक di = f2fs_target_device_index(sbi, blkaddr);

				blkaddr -= FDEV(di).start_blk;
			पूर्ण

			अगर (len) अणु
				अगर (prev_bdev == cur_bdev &&
						index == prev_index + len &&
						blkaddr == prev_block + len) अणु
					len++;
				पूर्ण अन्यथा अणु
					ret = f2fs_secure_erase(prev_bdev,
						inode, prev_index, prev_block,
						len, range.flags);
					अगर (ret) अणु
						f2fs_put_dnode(&dn);
						जाओ out;
					पूर्ण

					len = 0;
				पूर्ण
			पूर्ण

			अगर (!len) अणु
				prev_bdev = cur_bdev;
				prev_index = index;
				prev_block = blkaddr;
				len = 1;
			पूर्ण
		पूर्ण

		f2fs_put_dnode(&dn);

		अगर (fatal_संकेत_pending(current)) अणु
			ret = -EINTR;
			जाओ out;
		पूर्ण
		cond_resched();
	पूर्ण

	अगर (len)
		ret = f2fs_secure_erase(prev_bdev, inode, prev_index,
				prev_block, len, range.flags);
out:
	up_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);
	up_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
err:
	inode_unlock(inode);
	file_end_ग_लिखो(filp);

	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_ioc_get_compress_option(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा f2fs_comp_option option;

	अगर (!f2fs_sb_has_compression(F2FS_I_SB(inode)))
		वापस -EOPNOTSUPP;

	inode_lock_shared(inode);

	अगर (!f2fs_compressed_file(inode)) अणु
		inode_unlock_shared(inode);
		वापस -ENODATA;
	पूर्ण

	option.algorithm = F2FS_I(inode)->i_compress_algorithm;
	option.log_cluster_size = F2FS_I(inode)->i_log_cluster_size;

	inode_unlock_shared(inode);

	अगर (copy_to_user((काष्ठा f2fs_comp_option __user *)arg, &option,
				माप(option)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक f2fs_ioc_set_compress_option(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा f2fs_comp_option option;
	पूर्णांक ret = 0;

	अगर (!f2fs_sb_has_compression(sbi))
		वापस -EOPNOTSUPP;

	अगर (!(filp->f_mode & FMODE_WRITE))
		वापस -EBADF;

	अगर (copy_from_user(&option, (काष्ठा f2fs_comp_option __user *)arg,
				माप(option)))
		वापस -EFAULT;

	अगर (!f2fs_compressed_file(inode) ||
			option.log_cluster_size < MIN_COMPRESS_LOG_SIZE ||
			option.log_cluster_size > MAX_COMPRESS_LOG_SIZE ||
			option.algorithm >= COMPRESS_MAX)
		वापस -EINVAL;

	file_start_ग_लिखो(filp);
	inode_lock(inode);

	अगर (f2fs_is_mmap_file(inode) || get_dirty_pages(inode)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (inode->i_size != 0) अणु
		ret = -EFBIG;
		जाओ out;
	पूर्ण

	F2FS_I(inode)->i_compress_algorithm = option.algorithm;
	F2FS_I(inode)->i_log_cluster_size = option.log_cluster_size;
	F2FS_I(inode)->i_cluster_size = 1 << option.log_cluster_size;
	f2fs_mark_inode_dirty_sync(inode, true);

	अगर (!f2fs_is_compress_backend_पढ़ोy(inode))
		f2fs_warn(sbi, "compression algorithm is successfully set, "
			"but current kernel doesn't support this algorithm.");
out:
	inode_unlock(inode);
	file_end_ग_लिखो(filp);

	वापस ret;
पूर्ण

अटल पूर्णांक redirty_blocks(काष्ठा inode *inode, pgoff_t page_idx, पूर्णांक len)
अणु
	DEFINE_READAHEAD(ractl, शून्य, शून्य, inode->i_mapping, page_idx);
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा page *page;
	pgoff_t redirty_idx = page_idx;
	पूर्णांक i, page_len = 0, ret = 0;

	page_cache_ra_unbounded(&ractl, len, 0);

	क्रम (i = 0; i < len; i++, page_idx++) अणु
		page = पढ़ो_cache_page(mapping, page_idx, शून्य, शून्य);
		अगर (IS_ERR(page)) अणु
			ret = PTR_ERR(page);
			अवरोध;
		पूर्ण
		page_len++;
	पूर्ण

	क्रम (i = 0; i < page_len; i++, redirty_idx++) अणु
		page = find_lock_page(mapping, redirty_idx);
		अगर (!page) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
		set_page_dirty(page);
		f2fs_put_page(page, 1);
		f2fs_put_page(page, 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_ioc_decompress_file(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा f2fs_inode_info *fi = F2FS_I(inode);
	pgoff_t page_idx = 0, last_idx;
	अचिन्हित पूर्णांक blk_per_seg = sbi->blocks_per_seg;
	पूर्णांक cluster_size = F2FS_I(inode)->i_cluster_size;
	पूर्णांक count, ret;

	अगर (!f2fs_sb_has_compression(sbi) ||
			F2FS_OPTION(sbi).compress_mode != COMPR_MODE_USER)
		वापस -EOPNOTSUPP;

	अगर (!(filp->f_mode & FMODE_WRITE))
		वापस -EBADF;

	अगर (!f2fs_compressed_file(inode))
		वापस -EINVAL;

	f2fs_balance_fs(F2FS_I_SB(inode), true);

	file_start_ग_लिखो(filp);
	inode_lock(inode);

	अगर (!f2fs_is_compress_backend_पढ़ोy(inode)) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (f2fs_is_mmap_file(inode)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = filemap_ग_लिखो_and_रुको_range(inode->i_mapping, 0, Lदीर्घ_उच्च);
	अगर (ret)
		जाओ out;

	अगर (!atomic_पढ़ो(&fi->i_compr_blocks))
		जाओ out;

	last_idx = DIV_ROUND_UP(i_size_पढ़ो(inode), PAGE_SIZE);

	count = last_idx - page_idx;
	जबतक (count) अणु
		पूर्णांक len = min(cluster_size, count);

		ret = redirty_blocks(inode, page_idx, len);
		अगर (ret < 0)
			अवरोध;

		अगर (get_dirty_pages(inode) >= blk_per_seg)
			filemap_fdataग_लिखो(inode->i_mapping);

		count -= len;
		page_idx += len;
	पूर्ण

	अगर (!ret)
		ret = filemap_ग_लिखो_and_रुको_range(inode->i_mapping, 0,
							Lदीर्घ_उच्च);

	अगर (ret)
		f2fs_warn(sbi, "%s: The file might be partially decompressed "
				"(errno=%d). Please delete the file.\n",
				__func__, ret);
out:
	inode_unlock(inode);
	file_end_ग_लिखो(filp);

	वापस ret;
पूर्ण

अटल पूर्णांक f2fs_ioc_compress_file(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	pgoff_t page_idx = 0, last_idx;
	अचिन्हित पूर्णांक blk_per_seg = sbi->blocks_per_seg;
	पूर्णांक cluster_size = F2FS_I(inode)->i_cluster_size;
	पूर्णांक count, ret;

	अगर (!f2fs_sb_has_compression(sbi) ||
			F2FS_OPTION(sbi).compress_mode != COMPR_MODE_USER)
		वापस -EOPNOTSUPP;

	अगर (!(filp->f_mode & FMODE_WRITE))
		वापस -EBADF;

	अगर (!f2fs_compressed_file(inode))
		वापस -EINVAL;

	f2fs_balance_fs(F2FS_I_SB(inode), true);

	file_start_ग_लिखो(filp);
	inode_lock(inode);

	अगर (!f2fs_is_compress_backend_पढ़ोy(inode)) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (f2fs_is_mmap_file(inode)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ret = filemap_ग_लिखो_and_रुको_range(inode->i_mapping, 0, Lदीर्घ_उच्च);
	अगर (ret)
		जाओ out;

	set_inode_flag(inode, FI_ENABLE_COMPRESS);

	last_idx = DIV_ROUND_UP(i_size_पढ़ो(inode), PAGE_SIZE);

	count = last_idx - page_idx;
	जबतक (count) अणु
		पूर्णांक len = min(cluster_size, count);

		ret = redirty_blocks(inode, page_idx, len);
		अगर (ret < 0)
			अवरोध;

		अगर (get_dirty_pages(inode) >= blk_per_seg)
			filemap_fdataग_लिखो(inode->i_mapping);

		count -= len;
		page_idx += len;
	पूर्ण

	अगर (!ret)
		ret = filemap_ग_लिखो_and_रुको_range(inode->i_mapping, 0,
							Lदीर्घ_उच्च);

	clear_inode_flag(inode, FI_ENABLE_COMPRESS);

	अगर (ret)
		f2fs_warn(sbi, "%s: The file might be partially compressed "
				"(errno=%d). Please delete the file.\n",
				__func__, ret);
out:
	inode_unlock(inode);
	file_end_ग_लिखो(filp);

	वापस ret;
पूर्ण

अटल दीर्घ __f2fs_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल FS_IOC_GETVERSION:
		वापस f2fs_ioc_getversion(filp, arg);
	हाल F2FS_IOC_START_ATOMIC_WRITE:
		वापस f2fs_ioc_start_atomic_ग_लिखो(filp);
	हाल F2FS_IOC_COMMIT_ATOMIC_WRITE:
		वापस f2fs_ioc_commit_atomic_ग_लिखो(filp);
	हाल F2FS_IOC_START_VOLATILE_WRITE:
		वापस f2fs_ioc_start_अस्थिर_ग_लिखो(filp);
	हाल F2FS_IOC_RELEASE_VOLATILE_WRITE:
		वापस f2fs_ioc_release_अस्थिर_ग_लिखो(filp);
	हाल F2FS_IOC_ABORT_VOLATILE_WRITE:
		वापस f2fs_ioc_पात_अस्थिर_ग_लिखो(filp);
	हाल F2FS_IOC_SHUTDOWN:
		वापस f2fs_ioc_shutकरोwn(filp, arg);
	हाल FITRIM:
		वापस f2fs_ioc_fitrim(filp, arg);
	हाल FS_IOC_SET_ENCRYPTION_POLICY:
		वापस f2fs_ioc_set_encryption_policy(filp, arg);
	हाल FS_IOC_GET_ENCRYPTION_POLICY:
		वापस f2fs_ioc_get_encryption_policy(filp, arg);
	हाल FS_IOC_GET_ENCRYPTION_PWSALT:
		वापस f2fs_ioc_get_encryption_pwsalt(filp, arg);
	हाल FS_IOC_GET_ENCRYPTION_POLICY_EX:
		वापस f2fs_ioc_get_encryption_policy_ex(filp, arg);
	हाल FS_IOC_ADD_ENCRYPTION_KEY:
		वापस f2fs_ioc_add_encryption_key(filp, arg);
	हाल FS_IOC_REMOVE_ENCRYPTION_KEY:
		वापस f2fs_ioc_हटाओ_encryption_key(filp, arg);
	हाल FS_IOC_REMOVE_ENCRYPTION_KEY_ALL_USERS:
		वापस f2fs_ioc_हटाओ_encryption_key_all_users(filp, arg);
	हाल FS_IOC_GET_ENCRYPTION_KEY_STATUS:
		वापस f2fs_ioc_get_encryption_key_status(filp, arg);
	हाल FS_IOC_GET_ENCRYPTION_NONCE:
		वापस f2fs_ioc_get_encryption_nonce(filp, arg);
	हाल F2FS_IOC_GARBAGE_COLLECT:
		वापस f2fs_ioc_gc(filp, arg);
	हाल F2FS_IOC_GARBAGE_COLLECT_RANGE:
		वापस f2fs_ioc_gc_range(filp, arg);
	हाल F2FS_IOC_WRITE_CHECKPOINT:
		वापस f2fs_ioc_ग_लिखो_checkpoपूर्णांक(filp, arg);
	हाल F2FS_IOC_DEFRAGMENT:
		वापस f2fs_ioc_defragment(filp, arg);
	हाल F2FS_IOC_MOVE_RANGE:
		वापस f2fs_ioc_move_range(filp, arg);
	हाल F2FS_IOC_FLUSH_DEVICE:
		वापस f2fs_ioc_flush_device(filp, arg);
	हाल F2FS_IOC_GET_FEATURES:
		वापस f2fs_ioc_get_features(filp, arg);
	हाल F2FS_IOC_GET_PIN_खाता:
		वापस f2fs_ioc_get_pin_file(filp, arg);
	हाल F2FS_IOC_SET_PIN_खाता:
		वापस f2fs_ioc_set_pin_file(filp, arg);
	हाल F2FS_IOC_PRECACHE_EXTENTS:
		वापस f2fs_ioc_precache_extents(filp, arg);
	हाल F2FS_IOC_RESIZE_FS:
		वापस f2fs_ioc_resize_fs(filp, arg);
	हाल FS_IOC_ENABLE_VERITY:
		वापस f2fs_ioc_enable_verity(filp, arg);
	हाल FS_IOC_MEASURE_VERITY:
		वापस f2fs_ioc_measure_verity(filp, arg);
	हाल FS_IOC_READ_VERITY_METADATA:
		वापस f2fs_ioc_पढ़ो_verity_metadata(filp, arg);
	हाल FS_IOC_GETFSLABEL:
		वापस f2fs_ioc_getfslabel(filp, arg);
	हाल FS_IOC_SETFSLABEL:
		वापस f2fs_ioc_setfslabel(filp, arg);
	हाल F2FS_IOC_GET_COMPRESS_BLOCKS:
		वापस f2fs_get_compress_blocks(filp, arg);
	हाल F2FS_IOC_RELEASE_COMPRESS_BLOCKS:
		वापस f2fs_release_compress_blocks(filp, arg);
	हाल F2FS_IOC_RESERVE_COMPRESS_BLOCKS:
		वापस f2fs_reserve_compress_blocks(filp, arg);
	हाल F2FS_IOC_SEC_TRIM_खाता:
		वापस f2fs_sec_trim_file(filp, arg);
	हाल F2FS_IOC_GET_COMPRESS_OPTION:
		वापस f2fs_ioc_get_compress_option(filp, arg);
	हाल F2FS_IOC_SET_COMPRESS_OPTION:
		वापस f2fs_ioc_set_compress_option(filp, arg);
	हाल F2FS_IOC_DECOMPRESS_खाता:
		वापस f2fs_ioc_decompress_file(filp, arg);
	हाल F2FS_IOC_COMPRESS_खाता:
		वापस f2fs_ioc_compress_file(filp, arg);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

दीर्घ f2fs_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अगर (unlikely(f2fs_cp_error(F2FS_I_SB(file_inode(filp)))))
		वापस -EIO;
	अगर (!f2fs_is_checkpoपूर्णांक_पढ़ोy(F2FS_I_SB(file_inode(filp))))
		वापस -ENOSPC;

	वापस __f2fs_ioctl(filp, cmd, arg);
पूर्ण

अटल sमाप_प्रकार f2fs_file_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file_inode(file);
	पूर्णांक ret;

	अगर (!f2fs_is_compress_backend_पढ़ोy(inode))
		वापस -EOPNOTSUPP;

	ret = generic_file_पढ़ो_iter(iocb, iter);

	अगर (ret > 0)
		f2fs_update_iostat(F2FS_I_SB(inode), APP_READ_IO, ret);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार f2fs_file_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file_inode(file);
	sमाप_प्रकार ret;

	अगर (unlikely(f2fs_cp_error(F2FS_I_SB(inode)))) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (!f2fs_is_compress_backend_पढ़ोy(inode)) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (iocb->ki_flags & IOCB_NOWAIT) अणु
		अगर (!inode_trylock(inode)) अणु
			ret = -EAGAIN;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		inode_lock(inode);
	पूर्ण

	अगर (unlikely(IS_IMMUTABLE(inode))) अणु
		ret = -EPERM;
		जाओ unlock;
	पूर्ण

	ret = generic_ग_लिखो_checks(iocb, from);
	अगर (ret > 0) अणु
		bool pपुनः_स्मृतिated = false;
		माप_प्रकार target_size = 0;
		पूर्णांक err;

		अगर (iov_iter_fault_in_पढ़ोable(from, iov_iter_count(from)))
			set_inode_flag(inode, FI_NO_PREALLOC);

		अगर ((iocb->ki_flags & IOCB_NOWAIT)) अणु
			अगर (!f2fs_overग_लिखो_io(inode, iocb->ki_pos,
						iov_iter_count(from)) ||
				f2fs_has_अंतरभूत_data(inode) ||
				f2fs_क्रमce_buffered_io(inode, iocb, from)) अणु
				clear_inode_flag(inode, FI_NO_PREALLOC);
				inode_unlock(inode);
				ret = -EAGAIN;
				जाओ out;
			पूर्ण
			जाओ ग_लिखो;
		पूर्ण

		अगर (is_inode_flag_set(inode, FI_NO_PREALLOC))
			जाओ ग_लिखो;

		अगर (iocb->ki_flags & IOCB_सूचीECT) अणु
			/*
			 * Convert अंतरभूत data क्रम Direct I/O beक्रमe entering
			 * f2fs_direct_IO().
			 */
			err = f2fs_convert_अंतरभूत_inode(inode);
			अगर (err)
				जाओ out_err;
			/*
			 * If क्रमce_buffere_io() is true, we have to allocate
			 * blocks all the समय, since f2fs_direct_IO will fall
			 * back to buffered IO.
			 */
			अगर (!f2fs_क्रमce_buffered_io(inode, iocb, from) &&
					allow_outplace_dio(inode, iocb, from))
				जाओ ग_लिखो;
		पूर्ण
		pपुनः_स्मृतिated = true;
		target_size = iocb->ki_pos + iov_iter_count(from);

		err = f2fs_pपुनः_स्मृतिate_blocks(iocb, from);
		अगर (err) अणु
out_err:
			clear_inode_flag(inode, FI_NO_PREALLOC);
			inode_unlock(inode);
			ret = err;
			जाओ out;
		पूर्ण
ग_लिखो:
		ret = __generic_file_ग_लिखो_iter(iocb, from);
		clear_inode_flag(inode, FI_NO_PREALLOC);

		/* अगर we couldn't ग_लिखो data, we should deallocate blocks. */
		अगर (pपुनः_स्मृतिated && i_size_पढ़ो(inode) < target_size) अणु
			करोwn_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
			करोwn_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);
			f2fs_truncate(inode);
			up_ग_लिखो(&F2FS_I(inode)->i_mmap_sem);
			up_ग_लिखो(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
		पूर्ण

		अगर (ret > 0)
			f2fs_update_iostat(F2FS_I_SB(inode), APP_WRITE_IO, ret);
	पूर्ण
unlock:
	inode_unlock(inode);
out:
	trace_f2fs_file_ग_लिखो_iter(inode, iocb->ki_pos,
					iov_iter_count(from), ret);
	अगर (ret > 0)
		ret = generic_ग_लिखो_sync(iocb, ret);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
काष्ठा compat_f2fs_gc_range अणु
	u32 sync;
	compat_u64 start;
	compat_u64 len;
पूर्ण;
#घोषणा F2FS_IOC32_GARBAGE_COLLECT_RANGE	_IOW(F2FS_IOCTL_MAGIC, 11,\
						काष्ठा compat_f2fs_gc_range)

अटल पूर्णांक f2fs_compat_ioc_gc_range(काष्ठा file *file, अचिन्हित दीर्घ arg)
अणु
	काष्ठा compat_f2fs_gc_range __user *urange;
	काष्ठा f2fs_gc_range range;
	पूर्णांक err;

	urange = compat_ptr(arg);
	err = get_user(range.sync, &urange->sync);
	err |= get_user(range.start, &urange->start);
	err |= get_user(range.len, &urange->len);
	अगर (err)
		वापस -EFAULT;

	वापस __f2fs_ioc_gc_range(file, &range);
पूर्ण

काष्ठा compat_f2fs_move_range अणु
	u32 dst_fd;
	compat_u64 pos_in;
	compat_u64 pos_out;
	compat_u64 len;
पूर्ण;
#घोषणा F2FS_IOC32_MOVE_RANGE		_IOWR(F2FS_IOCTL_MAGIC, 9,	\
					काष्ठा compat_f2fs_move_range)

अटल पूर्णांक f2fs_compat_ioc_move_range(काष्ठा file *file, अचिन्हित दीर्घ arg)
अणु
	काष्ठा compat_f2fs_move_range __user *urange;
	काष्ठा f2fs_move_range range;
	पूर्णांक err;

	urange = compat_ptr(arg);
	err = get_user(range.dst_fd, &urange->dst_fd);
	err |= get_user(range.pos_in, &urange->pos_in);
	err |= get_user(range.pos_out, &urange->pos_out);
	err |= get_user(range.len, &urange->len);
	अगर (err)
		वापस -EFAULT;

	वापस __f2fs_ioc_move_range(file, &range);
पूर्ण

दीर्घ f2fs_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	अगर (unlikely(f2fs_cp_error(F2FS_I_SB(file_inode(file)))))
		वापस -EIO;
	अगर (!f2fs_is_checkpoपूर्णांक_पढ़ोy(F2FS_I_SB(file_inode(file))))
		वापस -ENOSPC;

	चयन (cmd) अणु
	हाल FS_IOC32_GETVERSION:
		cmd = FS_IOC_GETVERSION;
		अवरोध;
	हाल F2FS_IOC32_GARBAGE_COLLECT_RANGE:
		वापस f2fs_compat_ioc_gc_range(file, arg);
	हाल F2FS_IOC32_MOVE_RANGE:
		वापस f2fs_compat_ioc_move_range(file, arg);
	हाल F2FS_IOC_START_ATOMIC_WRITE:
	हाल F2FS_IOC_COMMIT_ATOMIC_WRITE:
	हाल F2FS_IOC_START_VOLATILE_WRITE:
	हाल F2FS_IOC_RELEASE_VOLATILE_WRITE:
	हाल F2FS_IOC_ABORT_VOLATILE_WRITE:
	हाल F2FS_IOC_SHUTDOWN:
	हाल FITRIM:
	हाल FS_IOC_SET_ENCRYPTION_POLICY:
	हाल FS_IOC_GET_ENCRYPTION_PWSALT:
	हाल FS_IOC_GET_ENCRYPTION_POLICY:
	हाल FS_IOC_GET_ENCRYPTION_POLICY_EX:
	हाल FS_IOC_ADD_ENCRYPTION_KEY:
	हाल FS_IOC_REMOVE_ENCRYPTION_KEY:
	हाल FS_IOC_REMOVE_ENCRYPTION_KEY_ALL_USERS:
	हाल FS_IOC_GET_ENCRYPTION_KEY_STATUS:
	हाल FS_IOC_GET_ENCRYPTION_NONCE:
	हाल F2FS_IOC_GARBAGE_COLLECT:
	हाल F2FS_IOC_WRITE_CHECKPOINT:
	हाल F2FS_IOC_DEFRAGMENT:
	हाल F2FS_IOC_FLUSH_DEVICE:
	हाल F2FS_IOC_GET_FEATURES:
	हाल F2FS_IOC_GET_PIN_खाता:
	हाल F2FS_IOC_SET_PIN_खाता:
	हाल F2FS_IOC_PRECACHE_EXTENTS:
	हाल F2FS_IOC_RESIZE_FS:
	हाल FS_IOC_ENABLE_VERITY:
	हाल FS_IOC_MEASURE_VERITY:
	हाल FS_IOC_READ_VERITY_METADATA:
	हाल FS_IOC_GETFSLABEL:
	हाल FS_IOC_SETFSLABEL:
	हाल F2FS_IOC_GET_COMPRESS_BLOCKS:
	हाल F2FS_IOC_RELEASE_COMPRESS_BLOCKS:
	हाल F2FS_IOC_RESERVE_COMPRESS_BLOCKS:
	हाल F2FS_IOC_SEC_TRIM_खाता:
	हाल F2FS_IOC_GET_COMPRESS_OPTION:
	हाल F2FS_IOC_SET_COMPRESS_OPTION:
	हाल F2FS_IOC_DECOMPRESS_खाता:
	हाल F2FS_IOC_COMPRESS_खाता:
		अवरोध;
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
	वापस __f2fs_ioctl(file, cmd, (अचिन्हित दीर्घ) compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा file_operations f2fs_file_operations = अणु
	.llseek		= f2fs_llseek,
	.पढ़ो_iter	= f2fs_file_पढ़ो_iter,
	.ग_लिखो_iter	= f2fs_file_ग_लिखो_iter,
	.खोलो		= f2fs_file_खोलो,
	.release	= f2fs_release_file,
	.mmap		= f2fs_file_mmap,
	.flush		= f2fs_file_flush,
	.fsync		= f2fs_sync_file,
	.fallocate	= f2fs_fallocate,
	.unlocked_ioctl	= f2fs_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= f2fs_compat_ioctl,
#पूर्ण_अगर
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो	= iter_file_splice_ग_लिखो,
पूर्ण;
