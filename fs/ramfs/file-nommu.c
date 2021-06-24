<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* file-nommu.c: no-MMU version of ramfs
 *
 * Copyright (C) 2005 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/backing-dev.h>
#समावेश <linux/ramfs.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/mman.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश <linux/uaccess.h>
#समावेश "internal.h"

अटल पूर्णांक ramfs_nommu_setattr(काष्ठा user_namespace *, काष्ठा dentry *, काष्ठा iattr *);
अटल अचिन्हित दीर्घ ramfs_nommu_get_unmapped_area(काष्ठा file *file,
						   अचिन्हित दीर्घ addr,
						   अचिन्हित दीर्घ len,
						   अचिन्हित दीर्घ pgoff,
						   अचिन्हित दीर्घ flags);
अटल पूर्णांक ramfs_nommu_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma);

अटल अचिन्हित ramfs_mmap_capabilities(काष्ठा file *file)
अणु
	वापस NOMMU_MAP_सूचीECT | NOMMU_MAP_COPY | NOMMU_MAP_READ |
		NOMMU_MAP_WRITE | NOMMU_MAP_EXEC;
पूर्ण

स्थिर काष्ठा file_operations ramfs_file_operations = अणु
	.mmap_capabilities	= ramfs_mmap_capabilities,
	.mmap			= ramfs_nommu_mmap,
	.get_unmapped_area	= ramfs_nommu_get_unmapped_area,
	.पढ़ो_iter		= generic_file_पढ़ो_iter,
	.ग_लिखो_iter		= generic_file_ग_लिखो_iter,
	.fsync			= noop_fsync,
	.splice_पढ़ो		= generic_file_splice_पढ़ो,
	.splice_ग_लिखो		= iter_file_splice_ग_लिखो,
	.llseek			= generic_file_llseek,
पूर्ण;

स्थिर काष्ठा inode_operations ramfs_file_inode_operations = अणु
	.setattr		= ramfs_nommu_setattr,
	.getattr		= simple_getattr,
पूर्ण;

/*****************************************************************************/
/*
 * add a contiguous set of pages पूर्णांकo a ramfs inode when it's truncated from
 * size 0 on the assumption that it's going to be used क्रम an mmap of shared
 * memory
 */
पूर्णांक ramfs_nommu_expand_क्रम_mapping(काष्ठा inode *inode, माप_प्रकार newsize)
अणु
	अचिन्हित दीर्घ npages, xpages, loop;
	काष्ठा page *pages;
	अचिन्हित order;
	व्योम *data;
	पूर्णांक ret;
	gfp_t gfp = mapping_gfp_mask(inode->i_mapping);

	/* make various checks */
	order = get_order(newsize);
	अगर (unlikely(order >= MAX_ORDER))
		वापस -EFBIG;

	ret = inode_newsize_ok(inode, newsize);
	अगर (ret)
		वापस ret;

	i_size_ग_लिखो(inode, newsize);

	/* allocate enough contiguous pages to be able to satisfy the
	 * request */
	pages = alloc_pages(gfp, order);
	अगर (!pages)
		वापस -ENOMEM;

	/* split the high-order page पूर्णांकo an array of single pages */
	xpages = 1UL << order;
	npages = (newsize + PAGE_SIZE - 1) >> PAGE_SHIFT;

	split_page(pages, order);

	/* trim off any pages we करोn't actually require */
	क्रम (loop = npages; loop < xpages; loop++)
		__मुक्त_page(pages + loop);

	/* clear the memory we allocated */
	newsize = PAGE_SIZE * npages;
	data = page_address(pages);
	स_रखो(data, 0, newsize);

	/* attach all the pages to the inode's address space */
	क्रम (loop = 0; loop < npages; loop++) अणु
		काष्ठा page *page = pages + loop;

		ret = add_to_page_cache_lru(page, inode->i_mapping, loop,
					gfp);
		अगर (ret < 0)
			जाओ add_error;

		/* prevent the page from being discarded on memory pressure */
		SetPageDirty(page);
		SetPageUptodate(page);

		unlock_page(page);
		put_page(page);
	पूर्ण

	वापस 0;

add_error:
	जबतक (loop < npages)
		__मुक्त_page(pages + loop++);
	वापस ret;
पूर्ण

/*****************************************************************************/
/*
 *
 */
अटल पूर्णांक ramfs_nommu_resize(काष्ठा inode *inode, loff_t newsize, loff_t size)
अणु
	पूर्णांक ret;

	/* assume a truncate from zero size is going to be क्रम the purposes of
	 * shared mmap */
	अगर (size == 0) अणु
		अगर (unlikely(newsize >> 32))
			वापस -EFBIG;

		वापस ramfs_nommu_expand_क्रम_mapping(inode, newsize);
	पूर्ण

	/* check that a decrease in size करोesn't cut off any shared mappings */
	अगर (newsize < size) अणु
		ret = nommu_shrink_inode_mappings(inode, size, newsize);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	truncate_setsize(inode, newsize);
	वापस 0;
पूर्ण

/*****************************************************************************/
/*
 * handle a change of attributes
 * - we're specअगरically पूर्णांकerested in a change of size
 */
अटल पूर्णांक ramfs_nommu_setattr(काष्ठा user_namespace *mnt_userns,
			       काष्ठा dentry *dentry, काष्ठा iattr *ia)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	अचिन्हित पूर्णांक old_ia_valid = ia->ia_valid;
	पूर्णांक ret = 0;

	/* POSIX UID/GID verअगरication क्रम setting inode attributes */
	ret = setattr_prepare(&init_user_ns, dentry, ia);
	अगर (ret)
		वापस ret;

	/* pick out size-changing events */
	अगर (ia->ia_valid & ATTR_SIZE) अणु
		loff_t size = inode->i_size;

		अगर (ia->ia_size != size) अणु
			ret = ramfs_nommu_resize(inode, ia->ia_size, size);
			अगर (ret < 0 || ia->ia_valid == ATTR_SIZE)
				जाओ out;
		पूर्ण अन्यथा अणु
			/* we skipped the truncate but must still update
			 * बारtamps
			 */
			ia->ia_valid |= ATTR_MTIME|ATTR_CTIME;
		पूर्ण
	पूर्ण

	setattr_copy(&init_user_ns, inode, ia);
 out:
	ia->ia_valid = old_ia_valid;
	वापस ret;
पूर्ण

/*****************************************************************************/
/*
 * try to determine where a shared mapping can be made
 * - we require that:
 *   - the pages to be mapped must exist
 *   - the pages be physically contiguous in sequence
 */
अटल अचिन्हित दीर्घ ramfs_nommu_get_unmapped_area(काष्ठा file *file,
					    अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
					    अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ maxpages, lpages, nr, loop, ret;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा page **pages = शून्य, **ptr, *page;
	loff_t isize;

	/* the mapping mustn't extend beyond the खातापूर्ण */
	lpages = (len + PAGE_SIZE - 1) >> PAGE_SHIFT;
	isize = i_size_पढ़ो(inode);

	ret = -ENOSYS;
	maxpages = (isize + PAGE_SIZE - 1) >> PAGE_SHIFT;
	अगर (pgoff >= maxpages)
		जाओ out;

	अगर (maxpages - pgoff < lpages)
		जाओ out;

	/* gang-find the pages */
	pages = kसुस्मृति(lpages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!pages)
		जाओ out_मुक्त;

	nr = find_get_pages_contig(inode->i_mapping, pgoff, lpages, pages);
	अगर (nr != lpages)
		जाओ out_मुक्त_pages; /* leave अगर some pages were missing */

	/* check the pages क्रम physical adjacency */
	ptr = pages;
	page = *ptr++;
	page++;
	क्रम (loop = lpages; loop > 1; loop--)
		अगर (*ptr++ != page++)
			जाओ out_मुक्त_pages;

	/* okay - all conditions fulfilled */
	ret = (अचिन्हित दीर्घ) page_address(pages[0]);

out_मुक्त_pages:
	ptr = pages;
	क्रम (loop = nr; loop > 0; loop--)
		put_page(*ptr++);
out_मुक्त:
	kमुक्त(pages);
out:
	वापस ret;
पूर्ण

/*****************************************************************************/
/*
 * set up a mapping क्रम shared memory segments
 */
अटल पूर्णांक ramfs_nommu_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (!(vma->vm_flags & (VM_SHARED | VM_MAYSHARE)))
		वापस -ENOSYS;

	file_accessed(file);
	vma->vm_ops = &generic_file_vm_ops;
	वापस 0;
पूर्ण
