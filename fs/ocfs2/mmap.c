<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * mmap.c
 *
 * Code to deal with the mess that is clustered mmap.
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/uपन.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/rbtree.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "aops.h"
#समावेश "dlmglue.h"
#समावेश "file.h"
#समावेश "inode.h"
#समावेश "mmap.h"
#समावेश "super.h"
#समावेश "ocfs2_trace.h"


अटल vm_fault_t ocfs2_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	sigset_t oldset;
	vm_fault_t ret;

	ocfs2_block_संकेतs(&oldset);
	ret = filemap_fault(vmf);
	ocfs2_unblock_संकेतs(&oldset);

	trace_ocfs2_fault(OCFS2_I(vma->vm_file->f_mapping->host)->ip_blkno,
			  vma, vmf->page, vmf->pgoff);
	वापस ret;
पूर्ण

अटल vm_fault_t __ocfs2_page_mkग_लिखो(काष्ठा file *file,
			काष्ठा buffer_head *di_bh, काष्ठा page *page)
अणु
	पूर्णांक err;
	vm_fault_t ret = VM_FAULT_NOPAGE;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा address_space *mapping = inode->i_mapping;
	loff_t pos = page_offset(page);
	अचिन्हित पूर्णांक len = PAGE_SIZE;
	pgoff_t last_index;
	काष्ठा page *locked_page = शून्य;
	व्योम *fsdata;
	loff_t size = i_size_पढ़ो(inode);

	last_index = (size - 1) >> PAGE_SHIFT;

	/*
	 * There are हालs that lead to the page no दीर्घer beदीर्घing to the
	 * mapping.
	 * 1) pagecache truncates locally due to memory pressure.
	 * 2) pagecache truncates when another is taking EX lock against 
	 * inode lock. see ocfs2_data_convert_worker.
	 * 
	 * The i_size check करोesn't catch the हाल where nodes truncated and
	 * then re-extended the file. We'll re-check the page mapping after
	 * taking the page lock inside of ocfs2_ग_लिखो_begin_nolock().
	 *
	 * Let VM retry with these हालs.
	 */
	अगर ((page->mapping != inode->i_mapping) ||
	    (!PageUptodate(page)) ||
	    (page_offset(page) >= size))
		जाओ out;

	/*
	 * Call ocfs2_ग_लिखो_begin() and ocfs2_ग_लिखो_end() to take
	 * advantage of the allocation code there. We pass a ग_लिखो
	 * length of the whole page (chopped to i_size) to make sure
	 * the whole thing is allocated.
	 *
	 * Since we know the page is up to date, we करोn't have to
	 * worry about ocfs2_ग_लिखो_begin() skipping some buffer पढ़ोs
	 * because the "write" would invalidate their data.
	 */
	अगर (page->index == last_index)
		len = ((size - 1) & ~PAGE_MASK) + 1;

	err = ocfs2_ग_लिखो_begin_nolock(mapping, pos, len, OCFS2_WRITE_MMAP,
				       &locked_page, &fsdata, di_bh, page);
	अगर (err) अणु
		अगर (err != -ENOSPC)
			mlog_त्रुटि_सं(err);
		ret = vmf_error(err);
		जाओ out;
	पूर्ण

	अगर (!locked_page) अणु
		ret = VM_FAULT_NOPAGE;
		जाओ out;
	पूर्ण
	err = ocfs2_ग_लिखो_end_nolock(mapping, pos, len, len, fsdata);
	BUG_ON(err != len);
	ret = VM_FAULT_LOCKED;
out:
	वापस ret;
पूर्ण

अटल vm_fault_t ocfs2_page_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	काष्ठा page *page = vmf->page;
	काष्ठा inode *inode = file_inode(vmf->vma->vm_file);
	काष्ठा buffer_head *di_bh = शून्य;
	sigset_t oldset;
	पूर्णांक err;
	vm_fault_t ret;

	sb_start_pagefault(inode->i_sb);
	ocfs2_block_संकेतs(&oldset);

	/*
	 * The cluster locks taken will block a truncate from another
	 * node. Taking the data lock will also ensure that we करोn't
	 * attempt page truncation as part of a करोwnconvert.
	 */
	err = ocfs2_inode_lock(inode, &di_bh, 1);
	अगर (err < 0) अणु
		mlog_त्रुटि_सं(err);
		ret = vmf_error(err);
		जाओ out;
	पूर्ण

	/*
	 * The alloc sem should be enough to serialize with
	 * ocfs2_truncate_file() changing i_size as well as any thपढ़ो
	 * modअगरying the inode btree.
	 */
	करोwn_ग_लिखो(&OCFS2_I(inode)->ip_alloc_sem);

	ret = __ocfs2_page_mkग_लिखो(vmf->vma->vm_file, di_bh, page);

	up_ग_लिखो(&OCFS2_I(inode)->ip_alloc_sem);

	brअन्यथा(di_bh);
	ocfs2_inode_unlock(inode, 1);

out:
	ocfs2_unblock_संकेतs(&oldset);
	sb_end_pagefault(inode->i_sb);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा ocfs2_file_vm_ops = अणु
	.fault		= ocfs2_fault,
	.page_mkग_लिखो	= ocfs2_page_mkग_लिखो,
पूर्ण;

पूर्णांक ocfs2_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक ret = 0, lock_level = 0;

	ret = ocfs2_inode_lock_aसमय(file_inode(file),
				    file->f_path.mnt, &lock_level, 1);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण
	ocfs2_inode_unlock(file_inode(file), lock_level);
out:
	vma->vm_ops = &ocfs2_file_vm_ops;
	वापस 0;
पूर्ण

