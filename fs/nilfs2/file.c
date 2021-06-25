<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * file.c - NILFS regular file handling primitives including fsync().
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Amagai Yoshiji and Ryusuke Konishi.
 */

#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश "nilfs.h"
#समावेश "segment.h"

पूर्णांक nilfs_sync_file(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	/*
	 * Called from fsync() प्रणाली call
	 * This is the only entry poपूर्णांक that can catch ग_लिखो and synch
	 * timing क्रम both data blocks and पूर्णांकermediate blocks.
	 *
	 * This function should be implemented when the ग_लिखोback function
	 * will be implemented.
	 */
	काष्ठा the_nilfs *nilfs;
	काष्ठा inode *inode = file->f_mapping->host;
	पूर्णांक err = 0;

	अगर (nilfs_inode_dirty(inode)) अणु
		अगर (datasync)
			err = nilfs_स्थिरruct_dsync_segment(inode->i_sb, inode,
							    start, end);
		अन्यथा
			err = nilfs_स्थिरruct_segment(inode->i_sb);
	पूर्ण

	nilfs = inode->i_sb->s_fs_info;
	अगर (!err)
		err = nilfs_flush_device(nilfs);

	वापस err;
पूर्ण

अटल vm_fault_t nilfs_page_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा page *page = vmf->page;
	काष्ठा inode *inode = file_inode(vma->vm_file);
	काष्ठा nilfs_transaction_info ti;
	पूर्णांक ret = 0;

	अगर (unlikely(nilfs_near_disk_full(inode->i_sb->s_fs_info)))
		वापस VM_FAULT_SIGBUS; /* -ENOSPC */

	sb_start_pagefault(inode->i_sb);
	lock_page(page);
	अगर (page->mapping != inode->i_mapping ||
	    page_offset(page) >= i_size_पढ़ो(inode) || !PageUptodate(page)) अणु
		unlock_page(page);
		ret = -EFAULT;	/* make the VM retry the fault */
		जाओ out;
	पूर्ण

	/*
	 * check to see अगर the page is mapped alपढ़ोy (no holes)
	 */
	अगर (PageMappedToDisk(page))
		जाओ mapped;

	अगर (page_has_buffers(page)) अणु
		काष्ठा buffer_head *bh, *head;
		पूर्णांक fully_mapped = 1;

		bh = head = page_buffers(page);
		करो अणु
			अगर (!buffer_mapped(bh)) अणु
				fully_mapped = 0;
				अवरोध;
			पूर्ण
		पूर्ण जबतक (bh = bh->b_this_page, bh != head);

		अगर (fully_mapped) अणु
			SetPageMappedToDisk(page);
			जाओ mapped;
		पूर्ण
	पूर्ण
	unlock_page(page);

	/*
	 * fill hole blocks
	 */
	ret = nilfs_transaction_begin(inode->i_sb, &ti, 1);
	/* never वापसs -ENOMEM, but may वापस -ENOSPC */
	अगर (unlikely(ret))
		जाओ out;

	file_update_समय(vma->vm_file);
	ret = block_page_mkग_लिखो(vma, vmf, nilfs_get_block);
	अगर (ret) अणु
		nilfs_transaction_पात(inode->i_sb);
		जाओ out;
	पूर्ण
	nilfs_set_file_dirty(inode, 1 << (PAGE_SHIFT - inode->i_blkbits));
	nilfs_transaction_commit(inode->i_sb);

 mapped:
	रुको_क्रम_stable_page(page);
 out:
	sb_end_pagefault(inode->i_sb);
	वापस block_page_mkग_लिखो_वापस(ret);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा nilfs_file_vm_ops = अणु
	.fault		= filemap_fault,
	.map_pages	= filemap_map_pages,
	.page_mkग_लिखो	= nilfs_page_mkग_लिखो,
पूर्ण;

अटल पूर्णांक nilfs_file_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	file_accessed(file);
	vma->vm_ops = &nilfs_file_vm_ops;
	वापस 0;
पूर्ण

/*
 * We have mostly शून्य's here: the current शेषs are ok क्रम
 * the nilfs fileप्रणाली.
 */
स्थिर काष्ठा file_operations nilfs_file_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो_iter	= generic_file_पढ़ो_iter,
	.ग_लिखो_iter	= generic_file_ग_लिखो_iter,
	.unlocked_ioctl	= nilfs_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= nilfs_compat_ioctl,
#पूर्ण_अगर	/* CONFIG_COMPAT */
	.mmap		= nilfs_file_mmap,
	.खोलो		= generic_file_खोलो,
	/* .release	= nilfs_release_file, */
	.fsync		= nilfs_sync_file,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
	.splice_ग_लिखो   = iter_file_splice_ग_लिखो,
पूर्ण;

स्थिर काष्ठा inode_operations nilfs_file_inode_operations = अणु
	.setattr	= nilfs_setattr,
	.permission     = nilfs_permission,
	.fiemap		= nilfs_fiemap,
	.fileattr_get	= nilfs_fileattr_get,
	.fileattr_set	= nilfs_fileattr_set,
पूर्ण;

/* end of file */
