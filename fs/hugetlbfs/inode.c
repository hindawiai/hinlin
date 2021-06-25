<शैली गुरु>
/*
 * hugetlbpage-backed fileप्रणाली.  Based on ramfs.
 *
 * Nadia Yvette Chambers, 2002
 *
 * Copyright (C) 2002 Linus Torvalds.
 * License: GPL
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/thपढ़ो_info.h>
#समावेश <यंत्र/current.h>
#समावेश <linux/sched/संकेत.स>		/* हटाओ ASAP */
#समावेश <linux/fभाग.स>
#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/file.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/capability.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/backing-dev.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/mman.h>
#समावेश <linux/slab.h>
#समावेश <linux/dnotअगरy.h>
#समावेश <linux/statfs.h>
#समावेश <linux/security.h>
#समावेश <linux/magic.h>
#समावेश <linux/migrate.h>
#समावेश <linux/uपन.स>

#समावेश <linux/uaccess.h>
#समावेश <linux/sched/mm.h>

अटल स्थिर काष्ठा super_operations hugetlbfs_ops;
अटल स्थिर काष्ठा address_space_operations hugetlbfs_aops;
स्थिर काष्ठा file_operations hugetlbfs_file_operations;
अटल स्थिर काष्ठा inode_operations hugetlbfs_dir_inode_operations;
अटल स्थिर काष्ठा inode_operations hugetlbfs_inode_operations;

क्रमागत hugetlbfs_माप_प्रकारype अणु NO_SIZE, SIZE_STD, SIZE_PERCENT पूर्ण;

काष्ठा hugetlbfs_fs_context अणु
	काष्ठा hstate		*hstate;
	अचिन्हित दीर्घ दीर्घ	max_size_opt;
	अचिन्हित दीर्घ दीर्घ	min_size_opt;
	दीर्घ			max_hpages;
	दीर्घ			nr_inodes;
	दीर्घ			min_hpages;
	क्रमागत hugetlbfs_माप_प्रकारype max_val_type;
	क्रमागत hugetlbfs_माप_प्रकारype min_val_type;
	kuid_t			uid;
	kgid_t			gid;
	umode_t			mode;
पूर्ण;

पूर्णांक sysctl_hugetlb_shm_group;

क्रमागत hugetlb_param अणु
	Opt_gid,
	Opt_min_size,
	Opt_mode,
	Opt_nr_inodes,
	Opt_pagesize,
	Opt_size,
	Opt_uid,
पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec hugetlb_fs_parameters[] = अणु
	fsparam_u32   ("gid",		Opt_gid),
	fsparam_string("min_size",	Opt_min_size),
	fsparam_u32   ("mode",		Opt_mode),
	fsparam_string("nr_inodes",	Opt_nr_inodes),
	fsparam_string("pagesize",	Opt_pagesize),
	fsparam_string("size",		Opt_size),
	fsparam_u32   ("uid",		Opt_uid),
	अणुपूर्ण
पूर्ण;

#अगर_घोषित CONFIG_NUMA
अटल अंतरभूत व्योम hugetlb_set_vma_policy(काष्ठा vm_area_काष्ठा *vma,
					काष्ठा inode *inode, pgoff_t index)
अणु
	vma->vm_policy = mpol_shared_policy_lookup(&HUGETLBFS_I(inode)->policy,
							index);
पूर्ण

अटल अंतरभूत व्योम hugetlb_drop_vma_policy(काष्ठा vm_area_काष्ठा *vma)
अणु
	mpol_cond_put(vma->vm_policy);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम hugetlb_set_vma_policy(काष्ठा vm_area_काष्ठा *vma,
					काष्ठा inode *inode, pgoff_t index)
अणु
पूर्ण

अटल अंतरभूत व्योम hugetlb_drop_vma_policy(काष्ठा vm_area_काष्ठा *vma)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम huge_pagevec_release(काष्ठा pagevec *pvec)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pagevec_count(pvec); ++i)
		put_page(pvec->pages[i]);

	pagevec_reinit(pvec);
पूर्ण

/*
 * Mask used when checking the page offset value passed in via प्रणाली
 * calls.  This value will be converted to a loff_t which is चिन्हित.
 * Thereक्रमe, we want to check the upper PAGE_SHIFT + 1 bits of the
 * value.  The extra bit (- 1 in the shअगरt value) is to take the sign
 * bit पूर्णांकo account.
 */
#घोषणा PGOFF_LOFFT_MAX \
	(((1UL << (PAGE_SHIFT + 1)) - 1) <<  (BITS_PER_LONG - (PAGE_SHIFT + 1)))

अटल पूर्णांक hugetlbfs_file_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा hugetlbfs_inode_info *info = HUGETLBFS_I(inode);
	loff_t len, vma_len;
	पूर्णांक ret;
	काष्ठा hstate *h = hstate_file(file);

	/*
	 * vma address alignment (but not the pgoff alignment) has
	 * alपढ़ोy been checked by prepare_hugepage_range.  If you add
	 * any error वापसs here, करो so after setting VM_HUGETLB, so
	 * is_vm_hugetlb_page tests below unmap_region go the right
	 * way when करो_mmap unwinds (may be important on घातerpc
	 * and ia64).
	 */
	vma->vm_flags |= VM_HUGETLB | VM_DONTEXPAND;
	vma->vm_ops = &hugetlb_vm_ops;

	ret = seal_check_future_ग_लिखो(info->seals, vma);
	अगर (ret)
		वापस ret;

	/*
	 * page based offset in vm_pgoff could be sufficiently large to
	 * overflow a loff_t when converted to byte offset.  This can
	 * only happen on architectures where माप(loff_t) ==
	 * माप(अचिन्हित दीर्घ).  So, only check in those instances.
	 */
	अगर (माप(अचिन्हित दीर्घ) == माप(loff_t)) अणु
		अगर (vma->vm_pgoff & PGOFF_LOFFT_MAX)
			वापस -EINVAL;
	पूर्ण

	/* must be huge page aligned */
	अगर (vma->vm_pgoff & (~huge_page_mask(h) >> PAGE_SHIFT))
		वापस -EINVAL;

	vma_len = (loff_t)(vma->vm_end - vma->vm_start);
	len = vma_len + ((loff_t)vma->vm_pgoff << PAGE_SHIFT);
	/* check क्रम overflow */
	अगर (len < vma_len)
		वापस -EINVAL;

	inode_lock(inode);
	file_accessed(file);

	ret = -ENOMEM;
	अगर (!hugetlb_reserve_pages(inode,
				vma->vm_pgoff >> huge_page_order(h),
				len >> huge_page_shअगरt(h), vma,
				vma->vm_flags))
		जाओ out;

	ret = 0;
	अगर (vma->vm_flags & VM_WRITE && inode->i_size < len)
		i_size_ग_लिखो(inode, len);
out:
	inode_unlock(inode);

	वापस ret;
पूर्ण

/*
 * Called under mmap_ग_लिखो_lock(mm).
 */

#अगर_अघोषित HAVE_ARCH_HUGETLB_UNMAPPED_AREA
अटल अचिन्हित दीर्घ
hugetlb_get_unmapped_area_bottomup(काष्ठा file *file, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा hstate *h = hstate_file(file);
	काष्ठा vm_unmapped_area_info info;

	info.flags = 0;
	info.length = len;
	info.low_limit = current->mm->mmap_base;
	info.high_limit = TASK_SIZE;
	info.align_mask = PAGE_MASK & ~huge_page_mask(h);
	info.align_offset = 0;
	वापस vm_unmapped_area(&info);
पूर्ण

अटल अचिन्हित दीर्घ
hugetlb_get_unmapped_area_topकरोwn(काष्ठा file *file, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा hstate *h = hstate_file(file);
	काष्ठा vm_unmapped_area_info info;

	info.flags = VM_UNMAPPED_AREA_TOPDOWN;
	info.length = len;
	info.low_limit = max(PAGE_SIZE, mmap_min_addr);
	info.high_limit = current->mm->mmap_base;
	info.align_mask = PAGE_MASK & ~huge_page_mask(h);
	info.align_offset = 0;
	addr = vm_unmapped_area(&info);

	/*
	 * A failed mmap() very likely causes application failure,
	 * so fall back to the bottom-up function here. This scenario
	 * can happen with large stack limits and large mmap()
	 * allocations.
	 */
	अगर (unlikely(offset_in_page(addr))) अणु
		VM_BUG_ON(addr != -ENOMEM);
		info.flags = 0;
		info.low_limit = current->mm->mmap_base;
		info.high_limit = TASK_SIZE;
		addr = vm_unmapped_area(&info);
	पूर्ण

	वापस addr;
पूर्ण

अटल अचिन्हित दीर्घ
hugetlb_get_unmapped_area(काष्ठा file *file, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा hstate *h = hstate_file(file);

	अगर (len & ~huge_page_mask(h))
		वापस -EINVAL;
	अगर (len > TASK_SIZE)
		वापस -ENOMEM;

	अगर (flags & MAP_FIXED) अणु
		अगर (prepare_hugepage_range(file, addr, len))
			वापस -EINVAL;
		वापस addr;
	पूर्ण

	अगर (addr) अणु
		addr = ALIGN(addr, huge_page_size(h));
		vma = find_vma(mm, addr);
		अगर (TASK_SIZE - len >= addr &&
		    (!vma || addr + len <= vm_start_gap(vma)))
			वापस addr;
	पूर्ण

	/*
	 * Use mm->get_unmapped_area value as a hपूर्णांक to use topकरोwn routine.
	 * If architectures have special needs, they should define their own
	 * version of hugetlb_get_unmapped_area.
	 */
	अगर (mm->get_unmapped_area == arch_get_unmapped_area_topकरोwn)
		वापस hugetlb_get_unmapped_area_topकरोwn(file, addr, len,
				pgoff, flags);
	वापस hugetlb_get_unmapped_area_bottomup(file, addr, len,
			pgoff, flags);
पूर्ण
#पूर्ण_अगर

अटल माप_प्रकार
hugetlbfs_पढ़ो_actor(काष्ठा page *page, अचिन्हित दीर्घ offset,
			काष्ठा iov_iter *to, अचिन्हित दीर्घ size)
अणु
	माप_प्रकार copied = 0;
	पूर्णांक i, chunksize;

	/* Find which 4k chunk and offset with in that chunk */
	i = offset >> PAGE_SHIFT;
	offset = offset & ~PAGE_MASK;

	जबतक (size) अणु
		माप_प्रकार n;
		chunksize = PAGE_SIZE;
		अगर (offset)
			chunksize -= offset;
		अगर (chunksize > size)
			chunksize = size;
		n = copy_page_to_iter(&page[i], offset, chunksize, to);
		copied += n;
		अगर (n != chunksize)
			वापस copied;
		offset = 0;
		size -= chunksize;
		i++;
	पूर्ण
	वापस copied;
पूर्ण

/*
 * Support क्रम पढ़ो() - Find the page attached to f_mapping and copy out the
 * data. Its *very* similar to generic_file_buffered_पढ़ो(), we can't use that
 * since it has PAGE_SIZE assumptions.
 */
अटल sमाप_प्रकार hugetlbfs_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा hstate *h = hstate_file(file);
	काष्ठा address_space *mapping = file->f_mapping;
	काष्ठा inode *inode = mapping->host;
	अचिन्हित दीर्घ index = iocb->ki_pos >> huge_page_shअगरt(h);
	अचिन्हित दीर्घ offset = iocb->ki_pos & ~huge_page_mask(h);
	अचिन्हित दीर्घ end_index;
	loff_t isize;
	sमाप_प्रकार retval = 0;

	जबतक (iov_iter_count(to)) अणु
		काष्ठा page *page;
		माप_प्रकार nr, copied;

		/* nr is the maximum number of bytes to copy from this page */
		nr = huge_page_size(h);
		isize = i_size_पढ़ो(inode);
		अगर (!isize)
			अवरोध;
		end_index = (isize - 1) >> huge_page_shअगरt(h);
		अगर (index > end_index)
			अवरोध;
		अगर (index == end_index) अणु
			nr = ((isize - 1) & ~huge_page_mask(h)) + 1;
			अगर (nr <= offset)
				अवरोध;
		पूर्ण
		nr = nr - offset;

		/* Find the page */
		page = find_lock_page(mapping, index);
		अगर (unlikely(page == शून्य)) अणु
			/*
			 * We have a HOLE, zero out the user-buffer क्रम the
			 * length of the hole or request.
			 */
			copied = iov_iter_zero(nr, to);
		पूर्ण अन्यथा अणु
			unlock_page(page);

			/*
			 * We have the page, copy it to user space buffer.
			 */
			copied = hugetlbfs_पढ़ो_actor(page, offset, to, nr);
			put_page(page);
		पूर्ण
		offset += copied;
		retval += copied;
		अगर (copied != nr && iov_iter_count(to)) अणु
			अगर (!retval)
				retval = -EFAULT;
			अवरोध;
		पूर्ण
		index += offset >> huge_page_shअगरt(h);
		offset &= ~huge_page_mask(h);
	पूर्ण
	iocb->ki_pos = ((loff_t)index << huge_page_shअगरt(h)) + offset;
	वापस retval;
पूर्ण

अटल पूर्णांक hugetlbfs_ग_लिखो_begin(काष्ठा file *file,
			काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hugetlbfs_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित copied,
			काष्ठा page *page, व्योम *fsdata)
अणु
	BUG();
	वापस -EINVAL;
पूर्ण

अटल व्योम हटाओ_huge_page(काष्ठा page *page)
अणु
	ClearPageDirty(page);
	ClearPageUptodate(page);
	delete_from_page_cache(page);
पूर्ण

अटल व्योम
hugetlb_vmdelete_list(काष्ठा rb_root_cached *root, pgoff_t start, pgoff_t end)
अणु
	काष्ठा vm_area_काष्ठा *vma;

	/*
	 * end == 0 indicates that the entire range after
	 * start should be unmapped.
	 */
	vma_पूर्णांकerval_tree_क्रमeach(vma, root, start, end ? end : अच_दीर्घ_उच्च) अणु
		अचिन्हित दीर्घ v_offset;
		अचिन्हित दीर्घ v_end;

		/*
		 * Can the expression below overflow on 32-bit arches?
		 * No, because the पूर्णांकerval tree वापसs us only those vmas
		 * which overlap the truncated area starting at pgoff,
		 * and no vma on a 32-bit arch can span beyond the 4GB.
		 */
		अगर (vma->vm_pgoff < start)
			v_offset = (start - vma->vm_pgoff) << PAGE_SHIFT;
		अन्यथा
			v_offset = 0;

		अगर (!end)
			v_end = vma->vm_end;
		अन्यथा अणु
			v_end = ((end - vma->vm_pgoff) << PAGE_SHIFT)
							+ vma->vm_start;
			अगर (v_end > vma->vm_end)
				v_end = vma->vm_end;
		पूर्ण

		unmap_hugepage_range(vma, vma->vm_start + v_offset, v_end,
									शून्य);
	पूर्ण
पूर्ण

/*
 * हटाओ_inode_hugepages handles two distinct हालs: truncation and hole
 * punch.  There are subtle dअगरferences in operation क्रम each हाल.
 *
 * truncation is indicated by end of range being Lदीर्घ_उच्च
 *	In this हाल, we first scan the range and release found pages.
 *	After releasing pages, hugetlb_unreserve_pages cleans up region/reserve
 *	maps and global counts.  Page faults can not race with truncation
 *	in this routine.  hugetlb_no_page() holds i_mmap_rwsem and prevents
 *	page faults in the truncated range by checking i_size.  i_size is
 *	modअगरied जबतक holding i_mmap_rwsem.
 * hole punch is indicated अगर end is not Lदीर्घ_उच्च
 *	In the hole punch हाल we scan the range and release found pages.
 *	Only when releasing a page is the associated region/reserve map
 *	deleted.  The region/reserve map क्रम ranges without associated
 *	pages are not modअगरied.  Page faults can race with hole punch.
 *	This is indicated अगर we find a mapped page.
 * Note: If the passed end of range value is beyond the end of file, but
 * not Lदीर्घ_उच्च this routine still perक्रमms a hole punch operation.
 */
अटल व्योम हटाओ_inode_hugepages(काष्ठा inode *inode, loff_t lstart,
				   loff_t lend)
अणु
	काष्ठा hstate *h = hstate_inode(inode);
	काष्ठा address_space *mapping = &inode->i_data;
	स्थिर pgoff_t start = lstart >> huge_page_shअगरt(h);
	स्थिर pgoff_t end = lend >> huge_page_shअगरt(h);
	काष्ठा pagevec pvec;
	pgoff_t next, index;
	पूर्णांक i, मुक्तd = 0;
	bool truncate_op = (lend == Lदीर्घ_उच्च);

	pagevec_init(&pvec);
	next = start;
	जबतक (next < end) अणु
		/*
		 * When no more pages are found, we are करोne.
		 */
		अगर (!pagevec_lookup_range(&pvec, mapping, &next, end - 1))
			अवरोध;

		क्रम (i = 0; i < pagevec_count(&pvec); ++i) अणु
			काष्ठा page *page = pvec.pages[i];
			u32 hash = 0;

			index = page->index;
			अगर (!truncate_op) अणु
				/*
				 * Only need to hold the fault mutex in the
				 * hole punch हाल.  This prevents races with
				 * page faults.  Races are not possible in the
				 * हाल of truncation.
				 */
				hash = hugetlb_fault_mutex_hash(mapping, index);
				mutex_lock(&hugetlb_fault_mutex_table[hash]);
			पूर्ण

			/*
			 * If page is mapped, it was faulted in after being
			 * unmapped in caller.  Unmap (again) now after taking
			 * the fault mutex.  The mutex will prevent faults
			 * until we finish removing the page.
			 *
			 * This race can only happen in the hole punch हाल.
			 * Getting here in a truncate operation is a bug.
			 */
			अगर (unlikely(page_mapped(page))) अणु
				BUG_ON(truncate_op);

				mutex_unlock(&hugetlb_fault_mutex_table[hash]);
				i_mmap_lock_ग_लिखो(mapping);
				mutex_lock(&hugetlb_fault_mutex_table[hash]);
				hugetlb_vmdelete_list(&mapping->i_mmap,
					index * pages_per_huge_page(h),
					(index + 1) * pages_per_huge_page(h));
				i_mmap_unlock_ग_लिखो(mapping);
			पूर्ण

			lock_page(page);
			/*
			 * We must मुक्त the huge page and हटाओ from page
			 * cache (हटाओ_huge_page) BEFORE removing the
			 * region/reserve map (hugetlb_unreserve_pages).  In
			 * rare out of memory conditions, removal of the
			 * region/reserve map could fail. Correspondingly,
			 * the subpool and global reserve usage count can need
			 * to be adjusted.
			 */
			VM_BUG_ON(HPageRestoreReserve(page));
			हटाओ_huge_page(page);
			मुक्तd++;
			अगर (!truncate_op) अणु
				अगर (unlikely(hugetlb_unreserve_pages(inode,
							index, index + 1, 1)))
					hugetlb_fix_reserve_counts(inode);
			पूर्ण

			unlock_page(page);
			अगर (!truncate_op)
				mutex_unlock(&hugetlb_fault_mutex_table[hash]);
		पूर्ण
		huge_pagevec_release(&pvec);
		cond_resched();
	पूर्ण

	अगर (truncate_op)
		(व्योम)hugetlb_unreserve_pages(inode, start, दीर्घ_उच्च, मुक्तd);
पूर्ण

अटल व्योम hugetlbfs_evict_inode(काष्ठा inode *inode)
अणु
	काष्ठा resv_map *resv_map;

	हटाओ_inode_hugepages(inode, 0, Lदीर्घ_उच्च);

	/*
	 * Get the resv_map from the address space embedded in the inode.
	 * This is the address space which poपूर्णांकs to any resv_map allocated
	 * at inode creation समय.  If this is a device special inode,
	 * i_mapping may not poपूर्णांक to the original address space.
	 */
	resv_map = (काष्ठा resv_map *)(&inode->i_data)->निजी_data;
	/* Only regular and link inodes have associated reserve maps */
	अगर (resv_map)
		resv_map_release(&resv_map->refs);
	clear_inode(inode);
पूर्ण

अटल व्योम hugetlb_vmtruncate(काष्ठा inode *inode, loff_t offset)
अणु
	pgoff_t pgoff;
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा hstate *h = hstate_inode(inode);

	BUG_ON(offset & ~huge_page_mask(h));
	pgoff = offset >> PAGE_SHIFT;

	i_mmap_lock_ग_लिखो(mapping);
	i_size_ग_लिखो(inode, offset);
	अगर (!RB_EMPTY_ROOT(&mapping->i_mmap.rb_root))
		hugetlb_vmdelete_list(&mapping->i_mmap, pgoff, 0);
	i_mmap_unlock_ग_लिखो(mapping);
	हटाओ_inode_hugepages(inode, offset, Lदीर्घ_उच्च);
पूर्ण

अटल दीर्घ hugetlbfs_punch_hole(काष्ठा inode *inode, loff_t offset, loff_t len)
अणु
	काष्ठा hstate *h = hstate_inode(inode);
	loff_t hpage_size = huge_page_size(h);
	loff_t hole_start, hole_end;

	/*
	 * For hole punch round up the beginning offset of the hole and
	 * round करोwn the end.
	 */
	hole_start = round_up(offset, hpage_size);
	hole_end = round_करोwn(offset + len, hpage_size);

	अगर (hole_end > hole_start) अणु
		काष्ठा address_space *mapping = inode->i_mapping;
		काष्ठा hugetlbfs_inode_info *info = HUGETLBFS_I(inode);

		inode_lock(inode);

		/* रक्षित by i_rwsem */
		अगर (info->seals & (F_SEAL_WRITE | F_SEAL_FUTURE_WRITE)) अणु
			inode_unlock(inode);
			वापस -EPERM;
		पूर्ण

		i_mmap_lock_ग_लिखो(mapping);
		अगर (!RB_EMPTY_ROOT(&mapping->i_mmap.rb_root))
			hugetlb_vmdelete_list(&mapping->i_mmap,
						hole_start >> PAGE_SHIFT,
						hole_end  >> PAGE_SHIFT);
		i_mmap_unlock_ग_लिखो(mapping);
		हटाओ_inode_hugepages(inode, hole_start, hole_end);
		inode_unlock(inode);
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ hugetlbfs_fallocate(काष्ठा file *file, पूर्णांक mode, loff_t offset,
				loff_t len)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा hugetlbfs_inode_info *info = HUGETLBFS_I(inode);
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा hstate *h = hstate_inode(inode);
	काष्ठा vm_area_काष्ठा pseuकरो_vma;
	काष्ठा mm_काष्ठा *mm = current->mm;
	loff_t hpage_size = huge_page_size(h);
	अचिन्हित दीर्घ hpage_shअगरt = huge_page_shअगरt(h);
	pgoff_t start, index, end;
	पूर्णांक error;
	u32 hash;

	अगर (mode & ~(FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE))
		वापस -EOPNOTSUPP;

	अगर (mode & FALLOC_FL_PUNCH_HOLE)
		वापस hugetlbfs_punch_hole(inode, offset, len);

	/*
	 * Default pपुनः_स्मृतिate हाल.
	 * For this range, start is rounded करोwn and end is rounded up
	 * as well as being converted to page offsets.
	 */
	start = offset >> hpage_shअगरt;
	end = (offset + len + hpage_size - 1) >> hpage_shअगरt;

	inode_lock(inode);

	/* We need to check rlimit even when FALLOC_FL_KEEP_SIZE */
	error = inode_newsize_ok(inode, offset + len);
	अगर (error)
		जाओ out;

	अगर ((info->seals & F_SEAL_GROW) && offset + len > inode->i_size) अणु
		error = -EPERM;
		जाओ out;
	पूर्ण

	/*
	 * Initialize a pseuकरो vma as this is required by the huge page
	 * allocation routines.  If NUMA is configured, use page index
	 * as input to create an allocation policy.
	 */
	vma_init(&pseuकरो_vma, mm);
	pseuकरो_vma.vm_flags = (VM_HUGETLB | VM_MAYSHARE | VM_SHARED);
	pseuकरो_vma.vm_file = file;

	क्रम (index = start; index < end; index++) अणु
		/*
		 * This is supposed to be the vaddr where the page is being
		 * faulted in, but we have no vaddr here.
		 */
		काष्ठा page *page;
		अचिन्हित दीर्घ addr;

		cond_resched();

		/*
		 * fallocate(2) manpage permits EINTR; we may have been
		 * पूर्णांकerrupted because we are using up too much memory.
		 */
		अगर (संकेत_pending(current)) अणु
			error = -EINTR;
			अवरोध;
		पूर्ण

		/* Set numa allocation policy based on index */
		hugetlb_set_vma_policy(&pseuकरो_vma, inode, index);

		/* addr is the offset within the file (zero based) */
		addr = index * hpage_size;

		/*
		 * fault mutex taken here, protects against fault path
		 * and hole punch.  inode_lock previously taken protects
		 * against truncation.
		 */
		hash = hugetlb_fault_mutex_hash(mapping, index);
		mutex_lock(&hugetlb_fault_mutex_table[hash]);

		/* See अगर alपढ़ोy present in mapping to aव्योम alloc/मुक्त */
		page = find_get_page(mapping, index);
		अगर (page) अणु
			put_page(page);
			mutex_unlock(&hugetlb_fault_mutex_table[hash]);
			hugetlb_drop_vma_policy(&pseuकरो_vma);
			जारी;
		पूर्ण

		/*
		 * Allocate page without setting the aव्योम_reserve argument.
		 * There certainly are no reserves associated with the
		 * pseuकरो_vma.  However, there could be shared mappings with
		 * reserves क्रम the file at the inode level.  If we fallocate
		 * pages in these areas, we need to consume the reserves
		 * to keep reservation accounting consistent.
		 */
		page = alloc_huge_page(&pseuकरो_vma, addr, 0);
		hugetlb_drop_vma_policy(&pseuकरो_vma);
		अगर (IS_ERR(page)) अणु
			mutex_unlock(&hugetlb_fault_mutex_table[hash]);
			error = PTR_ERR(page);
			जाओ out;
		पूर्ण
		clear_huge_page(page, addr, pages_per_huge_page(h));
		__SetPageUptodate(page);
		error = huge_add_to_page_cache(page, mapping, index);
		अगर (unlikely(error)) अणु
			restore_reserve_on_error(h, &pseuकरो_vma, addr, page);
			put_page(page);
			mutex_unlock(&hugetlb_fault_mutex_table[hash]);
			जाओ out;
		पूर्ण

		mutex_unlock(&hugetlb_fault_mutex_table[hash]);

		SetHPageMigratable(page);
		/*
		 * unlock_page because locked by add_to_page_cache()
		 * put_page() due to reference from alloc_huge_page()
		 */
		unlock_page(page);
		put_page(page);
	पूर्ण

	अगर (!(mode & FALLOC_FL_KEEP_SIZE) && offset + len > inode->i_size)
		i_size_ग_लिखो(inode, offset + len);
	inode->i_स_समय = current_समय(inode);
out:
	inode_unlock(inode);
	वापस error;
पूर्ण

अटल पूर्णांक hugetlbfs_setattr(काष्ठा user_namespace *mnt_userns,
			     काष्ठा dentry *dentry, काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा hstate *h = hstate_inode(inode);
	पूर्णांक error;
	अचिन्हित पूर्णांक ia_valid = attr->ia_valid;
	काष्ठा hugetlbfs_inode_info *info = HUGETLBFS_I(inode);

	error = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (error)
		वापस error;

	अगर (ia_valid & ATTR_SIZE) अणु
		loff_t oldsize = inode->i_size;
		loff_t newsize = attr->ia_size;

		अगर (newsize & ~huge_page_mask(h))
			वापस -EINVAL;
		/* रक्षित by i_rwsem */
		अगर ((newsize < oldsize && (info->seals & F_SEAL_SHRINK)) ||
		    (newsize > oldsize && (info->seals & F_SEAL_GROW)))
			वापस -EPERM;
		hugetlb_vmtruncate(inode, newsize);
	पूर्ण

	setattr_copy(&init_user_ns, inode, attr);
	mark_inode_dirty(inode);
	वापस 0;
पूर्ण

अटल काष्ठा inode *hugetlbfs_get_root(काष्ठा super_block *sb,
					काष्ठा hugetlbfs_fs_context *ctx)
अणु
	काष्ठा inode *inode;

	inode = new_inode(sb);
	अगर (inode) अणु
		inode->i_ino = get_next_ino();
		inode->i_mode = S_IFसूची | ctx->mode;
		inode->i_uid = ctx->uid;
		inode->i_gid = ctx->gid;
		inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
		inode->i_op = &hugetlbfs_dir_inode_operations;
		inode->i_fop = &simple_dir_operations;
		/* directory inodes start off with i_nlink == 2 (क्रम "." entry) */
		inc_nlink(inode);
		lockdep_annotate_inode_mutex_key(inode);
	पूर्ण
	वापस inode;
पूर्ण

/*
 * Hugetlbfs is not reclaimable; thereक्रमe its i_mmap_rwsem will never
 * be taken from reclaim -- unlike regular fileप्रणालीs. This needs an
 * annotation because huge_pmd_share() करोes an allocation under hugetlb's
 * i_mmap_rwsem.
 */
अटल काष्ठा lock_class_key hugetlbfs_i_mmap_rwsem_key;

अटल काष्ठा inode *hugetlbfs_get_inode(काष्ठा super_block *sb,
					काष्ठा inode *dir,
					umode_t mode, dev_t dev)
अणु
	काष्ठा inode *inode;
	काष्ठा resv_map *resv_map = शून्य;

	/*
	 * Reserve maps are only needed क्रम inodes that can have associated
	 * page allocations.
	 */
	अगर (S_ISREG(mode) || S_ISLNK(mode)) अणु
		resv_map = resv_map_alloc();
		अगर (!resv_map)
			वापस शून्य;
	पूर्ण

	inode = new_inode(sb);
	अगर (inode) अणु
		काष्ठा hugetlbfs_inode_info *info = HUGETLBFS_I(inode);

		inode->i_ino = get_next_ino();
		inode_init_owner(&init_user_ns, inode, dir, mode);
		lockdep_set_class(&inode->i_mapping->i_mmap_rwsem,
				&hugetlbfs_i_mmap_rwsem_key);
		inode->i_mapping->a_ops = &hugetlbfs_aops;
		inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
		inode->i_mapping->निजी_data = resv_map;
		info->seals = F_SEAL_SEAL;
		चयन (mode & S_IFMT) अणु
		शेष:
			init_special_inode(inode, mode, dev);
			अवरोध;
		हाल S_IFREG:
			inode->i_op = &hugetlbfs_inode_operations;
			inode->i_fop = &hugetlbfs_file_operations;
			अवरोध;
		हाल S_IFसूची:
			inode->i_op = &hugetlbfs_dir_inode_operations;
			inode->i_fop = &simple_dir_operations;

			/* directory inodes start off with i_nlink == 2 (क्रम "." entry) */
			inc_nlink(inode);
			अवरोध;
		हाल S_IFLNK:
			inode->i_op = &page_symlink_inode_operations;
			inode_nohighmem(inode);
			अवरोध;
		पूर्ण
		lockdep_annotate_inode_mutex_key(inode);
	पूर्ण अन्यथा अणु
		अगर (resv_map)
			kref_put(&resv_map->refs, resv_map_release);
	पूर्ण

	वापस inode;
पूर्ण

/*
 * File creation. Allocate an inode, and we're करोne..
 */
अटल पूर्णांक करो_hugetlbfs_mknod(काष्ठा inode *dir,
			काष्ठा dentry *dentry,
			umode_t mode,
			dev_t dev,
			bool क्षणिक_ख)
अणु
	काष्ठा inode *inode;
	पूर्णांक error = -ENOSPC;

	inode = hugetlbfs_get_inode(dir->i_sb, dir, mode, dev);
	अगर (inode) अणु
		dir->i_स_समय = dir->i_mसमय = current_समय(dir);
		अगर (क्षणिक_ख) अणु
			d_क्षणिक_ख(dentry, inode);
		पूर्ण अन्यथा अणु
			d_instantiate(dentry, inode);
			dget(dentry);/* Extra count - pin the dentry in core */
		पूर्ण
		error = 0;
	पूर्ण
	वापस error;
पूर्ण

अटल पूर्णांक hugetlbfs_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			   काष्ठा dentry *dentry, umode_t mode, dev_t dev)
अणु
	वापस करो_hugetlbfs_mknod(dir, dentry, mode, dev, false);
पूर्ण

अटल पूर्णांक hugetlbfs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			   काष्ठा dentry *dentry, umode_t mode)
अणु
	पूर्णांक retval = hugetlbfs_mknod(&init_user_ns, dir, dentry,
				     mode | S_IFसूची, 0);
	अगर (!retval)
		inc_nlink(dir);
	वापस retval;
पूर्ण

अटल पूर्णांक hugetlbfs_create(काष्ठा user_namespace *mnt_userns,
			    काष्ठा inode *dir, काष्ठा dentry *dentry,
			    umode_t mode, bool excl)
अणु
	वापस hugetlbfs_mknod(&init_user_ns, dir, dentry, mode | S_IFREG, 0);
पूर्ण

अटल पूर्णांक hugetlbfs_क्षणिक_ख(काष्ठा user_namespace *mnt_userns,
			     काष्ठा inode *dir, काष्ठा dentry *dentry,
			     umode_t mode)
अणु
	वापस करो_hugetlbfs_mknod(dir, dentry, mode | S_IFREG, 0, true);
पूर्ण

अटल पूर्णांक hugetlbfs_symlink(काष्ठा user_namespace *mnt_userns,
			     काष्ठा inode *dir, काष्ठा dentry *dentry,
			     स्थिर अक्षर *symname)
अणु
	काष्ठा inode *inode;
	पूर्णांक error = -ENOSPC;

	inode = hugetlbfs_get_inode(dir->i_sb, dir, S_IFLNK|S_IRWXUGO, 0);
	अगर (inode) अणु
		पूर्णांक l = म_माप(symname)+1;
		error = page_symlink(inode, symname, l);
		अगर (!error) अणु
			d_instantiate(dentry, inode);
			dget(dentry);
		पूर्ण अन्यथा
			iput(inode);
	पूर्ण
	dir->i_स_समय = dir->i_mसमय = current_समय(dir);

	वापस error;
पूर्ण

अटल पूर्णांक hugetlbfs_migrate_page(काष्ठा address_space *mapping,
				काष्ठा page *newpage, काष्ठा page *page,
				क्रमागत migrate_mode mode)
अणु
	पूर्णांक rc;

	rc = migrate_huge_page_move_mapping(mapping, newpage, page);
	अगर (rc != MIGRATEPAGE_SUCCESS)
		वापस rc;

	अगर (hugetlb_page_subpool(page)) अणु
		hugetlb_set_page_subpool(newpage, hugetlb_page_subpool(page));
		hugetlb_set_page_subpool(page, शून्य);
	पूर्ण

	अगर (mode != MIGRATE_SYNC_NO_COPY)
		migrate_page_copy(newpage, page);
	अन्यथा
		migrate_page_states(newpage, page);

	वापस MIGRATEPAGE_SUCCESS;
पूर्ण

अटल पूर्णांक hugetlbfs_error_हटाओ_page(काष्ठा address_space *mapping,
				काष्ठा page *page)
अणु
	काष्ठा inode *inode = mapping->host;
	pgoff_t index = page->index;

	हटाओ_huge_page(page);
	अगर (unlikely(hugetlb_unreserve_pages(inode, index, index + 1, 1)))
		hugetlb_fix_reserve_counts(inode);

	वापस 0;
पूर्ण

/*
 * Display the mount options in /proc/mounts.
 */
अटल पूर्णांक hugetlbfs_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा hugetlbfs_sb_info *sbinfo = HUGETLBFS_SB(root->d_sb);
	काष्ठा hugepage_subpool *spool = sbinfo->spool;
	अचिन्हित दीर्घ hpage_size = huge_page_size(sbinfo->hstate);
	अचिन्हित hpage_shअगरt = huge_page_shअगरt(sbinfo->hstate);
	अक्षर mod;

	अगर (!uid_eq(sbinfo->uid, GLOBAL_ROOT_UID))
		seq_म_लिखो(m, ",uid=%u",
			   from_kuid_munged(&init_user_ns, sbinfo->uid));
	अगर (!gid_eq(sbinfo->gid, GLOBAL_ROOT_GID))
		seq_म_लिखो(m, ",gid=%u",
			   from_kgid_munged(&init_user_ns, sbinfo->gid));
	अगर (sbinfo->mode != 0755)
		seq_म_लिखो(m, ",mode=%o", sbinfo->mode);
	अगर (sbinfo->max_inodes != -1)
		seq_म_लिखो(m, ",nr_inodes=%lu", sbinfo->max_inodes);

	hpage_size /= 1024;
	mod = 'K';
	अगर (hpage_size >= 1024) अणु
		hpage_size /= 1024;
		mod = 'M';
	पूर्ण
	seq_म_लिखो(m, ",pagesize=%lu%c", hpage_size, mod);
	अगर (spool) अणु
		अगर (spool->max_hpages != -1)
			seq_म_लिखो(m, ",size=%llu",
				   (अचिन्हित दीर्घ दीर्घ)spool->max_hpages << hpage_shअगरt);
		अगर (spool->min_hpages != -1)
			seq_म_लिखो(m, ",min_size=%llu",
				   (अचिन्हित दीर्घ दीर्घ)spool->min_hpages << hpage_shअगरt);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hugetlbfs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा hugetlbfs_sb_info *sbinfo = HUGETLBFS_SB(dentry->d_sb);
	काष्ठा hstate *h = hstate_inode(d_inode(dentry));

	buf->f_type = HUGETLBFS_MAGIC;
	buf->f_bsize = huge_page_size(h);
	अगर (sbinfo) अणु
		spin_lock(&sbinfo->stat_lock);
		/* If no limits set, just report 0 क्रम max/मुक्त/used
		 * blocks, like simple_statfs() */
		अगर (sbinfo->spool) अणु
			दीर्घ मुक्त_pages;

			spin_lock(&sbinfo->spool->lock);
			buf->f_blocks = sbinfo->spool->max_hpages;
			मुक्त_pages = sbinfo->spool->max_hpages
				- sbinfo->spool->used_hpages;
			buf->f_bavail = buf->f_bमुक्त = मुक्त_pages;
			spin_unlock(&sbinfo->spool->lock);
			buf->f_files = sbinfo->max_inodes;
			buf->f_fमुक्त = sbinfo->मुक्त_inodes;
		पूर्ण
		spin_unlock(&sbinfo->stat_lock);
	पूर्ण
	buf->f_namelen = NAME_MAX;
	वापस 0;
पूर्ण

अटल व्योम hugetlbfs_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा hugetlbfs_sb_info *sbi = HUGETLBFS_SB(sb);

	अगर (sbi) अणु
		sb->s_fs_info = शून्य;

		अगर (sbi->spool)
			hugepage_put_subpool(sbi->spool);

		kमुक्त(sbi);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक hugetlbfs_dec_मुक्त_inodes(काष्ठा hugetlbfs_sb_info *sbinfo)
अणु
	अगर (sbinfo->मुक्त_inodes >= 0) अणु
		spin_lock(&sbinfo->stat_lock);
		अगर (unlikely(!sbinfo->मुक्त_inodes)) अणु
			spin_unlock(&sbinfo->stat_lock);
			वापस 0;
		पूर्ण
		sbinfo->मुक्त_inodes--;
		spin_unlock(&sbinfo->stat_lock);
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम hugetlbfs_inc_मुक्त_inodes(काष्ठा hugetlbfs_sb_info *sbinfo)
अणु
	अगर (sbinfo->मुक्त_inodes >= 0) अणु
		spin_lock(&sbinfo->stat_lock);
		sbinfo->मुक्त_inodes++;
		spin_unlock(&sbinfo->stat_lock);
	पूर्ण
पूर्ण


अटल काष्ठा kmem_cache *hugetlbfs_inode_cachep;

अटल काष्ठा inode *hugetlbfs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा hugetlbfs_sb_info *sbinfo = HUGETLBFS_SB(sb);
	काष्ठा hugetlbfs_inode_info *p;

	अगर (unlikely(!hugetlbfs_dec_मुक्त_inodes(sbinfo)))
		वापस शून्य;
	p = kmem_cache_alloc(hugetlbfs_inode_cachep, GFP_KERNEL);
	अगर (unlikely(!p)) अणु
		hugetlbfs_inc_मुक्त_inodes(sbinfo);
		वापस शून्य;
	पूर्ण

	/*
	 * Any समय after allocation, hugetlbfs_destroy_inode can be called
	 * क्रम the inode.  mpol_मुक्त_shared_policy is unconditionally called
	 * as part of hugetlbfs_destroy_inode.  So, initialize policy here
	 * in हाल of a quick call to destroy.
	 *
	 * Note that the policy is initialized even अगर we are creating a
	 * निजी inode.  This simplअगरies hugetlbfs_destroy_inode.
	 */
	mpol_shared_policy_init(&p->policy, शून्य);

	वापस &p->vfs_inode;
पूर्ण

अटल व्योम hugetlbfs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(hugetlbfs_inode_cachep, HUGETLBFS_I(inode));
पूर्ण

अटल व्योम hugetlbfs_destroy_inode(काष्ठा inode *inode)
अणु
	hugetlbfs_inc_मुक्त_inodes(HUGETLBFS_SB(inode->i_sb));
	mpol_मुक्त_shared_policy(&HUGETLBFS_I(inode)->policy);
पूर्ण

अटल स्थिर काष्ठा address_space_operations hugetlbfs_aops = अणु
	.ग_लिखो_begin	= hugetlbfs_ग_लिखो_begin,
	.ग_लिखो_end	= hugetlbfs_ग_लिखो_end,
	.set_page_dirty	=  __set_page_dirty_no_ग_लिखोback,
	.migratepage    = hugetlbfs_migrate_page,
	.error_हटाओ_page	= hugetlbfs_error_हटाओ_page,
पूर्ण;


अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा hugetlbfs_inode_info *ei = (काष्ठा hugetlbfs_inode_info *)foo;

	inode_init_once(&ei->vfs_inode);
पूर्ण

स्थिर काष्ठा file_operations hugetlbfs_file_operations = अणु
	.पढ़ो_iter		= hugetlbfs_पढ़ो_iter,
	.mmap			= hugetlbfs_file_mmap,
	.fsync			= noop_fsync,
	.get_unmapped_area	= hugetlb_get_unmapped_area,
	.llseek			= शेष_llseek,
	.fallocate		= hugetlbfs_fallocate,
पूर्ण;

अटल स्थिर काष्ठा inode_operations hugetlbfs_dir_inode_operations = अणु
	.create		= hugetlbfs_create,
	.lookup		= simple_lookup,
	.link		= simple_link,
	.unlink		= simple_unlink,
	.symlink	= hugetlbfs_symlink,
	.सूची_गढ़ो		= hugetlbfs_सूची_गढ़ो,
	.सूची_हटाओ		= simple_सूची_हटाओ,
	.mknod		= hugetlbfs_mknod,
	.नाम		= simple_नाम,
	.setattr	= hugetlbfs_setattr,
	.क्षणिक_ख	= hugetlbfs_क्षणिक_ख,
पूर्ण;

अटल स्थिर काष्ठा inode_operations hugetlbfs_inode_operations = अणु
	.setattr	= hugetlbfs_setattr,
पूर्ण;

अटल स्थिर काष्ठा super_operations hugetlbfs_ops = अणु
	.alloc_inode    = hugetlbfs_alloc_inode,
	.मुक्त_inode     = hugetlbfs_मुक्त_inode,
	.destroy_inode  = hugetlbfs_destroy_inode,
	.evict_inode	= hugetlbfs_evict_inode,
	.statfs		= hugetlbfs_statfs,
	.put_super	= hugetlbfs_put_super,
	.show_options	= hugetlbfs_show_options,
पूर्ण;

/*
 * Convert size option passed from command line to number of huge pages
 * in the pool specअगरied by hstate.  Size option could be in bytes
 * (val_type == SIZE_STD) or percentage of the pool (val_type == SIZE_PERCENT).
 */
अटल दीर्घ
hugetlbfs_माप_प्रकारo_hpages(काष्ठा hstate *h, अचिन्हित दीर्घ दीर्घ size_opt,
			 क्रमागत hugetlbfs_माप_प्रकारype val_type)
अणु
	अगर (val_type == NO_SIZE)
		वापस -1;

	अगर (val_type == SIZE_PERCENT) अणु
		size_opt <<= huge_page_shअगरt(h);
		size_opt *= h->max_huge_pages;
		करो_भाग(size_opt, 100);
	पूर्ण

	size_opt >>= huge_page_shअगरt(h);
	वापस size_opt;
पूर्ण

/*
 * Parse one mount parameter.
 */
अटल पूर्णांक hugetlbfs_parse_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	काष्ठा hugetlbfs_fs_context *ctx = fc->fs_निजी;
	काष्ठा fs_parse_result result;
	अक्षर *rest;
	अचिन्हित दीर्घ ps;
	पूर्णांक opt;

	opt = fs_parse(fc, hugetlb_fs_parameters, param, &result);
	अगर (opt < 0)
		वापस opt;

	चयन (opt) अणु
	हाल Opt_uid:
		ctx->uid = make_kuid(current_user_ns(), result.uपूर्णांक_32);
		अगर (!uid_valid(ctx->uid))
			जाओ bad_val;
		वापस 0;

	हाल Opt_gid:
		ctx->gid = make_kgid(current_user_ns(), result.uपूर्णांक_32);
		अगर (!gid_valid(ctx->gid))
			जाओ bad_val;
		वापस 0;

	हाल Opt_mode:
		ctx->mode = result.uपूर्णांक_32 & 01777U;
		वापस 0;

	हाल Opt_size:
		/* memparse() will accept a K/M/G without a digit */
		अगर (!है_अंक(param->string[0]))
			जाओ bad_val;
		ctx->max_size_opt = memparse(param->string, &rest);
		ctx->max_val_type = SIZE_STD;
		अगर (*rest == '%')
			ctx->max_val_type = SIZE_PERCENT;
		वापस 0;

	हाल Opt_nr_inodes:
		/* memparse() will accept a K/M/G without a digit */
		अगर (!है_अंक(param->string[0]))
			जाओ bad_val;
		ctx->nr_inodes = memparse(param->string, &rest);
		वापस 0;

	हाल Opt_pagesize:
		ps = memparse(param->string, &rest);
		ctx->hstate = माप_प्रकारo_hstate(ps);
		अगर (!ctx->hstate) अणु
			pr_err("Unsupported page size %lu MB\n", ps >> 20);
			वापस -EINVAL;
		पूर्ण
		वापस 0;

	हाल Opt_min_size:
		/* memparse() will accept a K/M/G without a digit */
		अगर (!है_अंक(param->string[0]))
			जाओ bad_val;
		ctx->min_size_opt = memparse(param->string, &rest);
		ctx->min_val_type = SIZE_STD;
		अगर (*rest == '%')
			ctx->min_val_type = SIZE_PERCENT;
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण

bad_val:
	वापस invalfc(fc, "Bad value '%s' for mount option '%s'\n",
		      param->string, param->key);
पूर्ण

/*
 * Validate the parsed options.
 */
अटल पूर्णांक hugetlbfs_validate(काष्ठा fs_context *fc)
अणु
	काष्ठा hugetlbfs_fs_context *ctx = fc->fs_निजी;

	/*
	 * Use huge page pool size (in hstate) to convert the size
	 * options to number of huge pages.  If NO_SIZE, -1 is वापसed.
	 */
	ctx->max_hpages = hugetlbfs_माप_प्रकारo_hpages(ctx->hstate,
						   ctx->max_size_opt,
						   ctx->max_val_type);
	ctx->min_hpages = hugetlbfs_माप_प्रकारo_hpages(ctx->hstate,
						   ctx->min_size_opt,
						   ctx->min_val_type);

	/*
	 * If max_size was specअगरied, then min_size must be smaller
	 */
	अगर (ctx->max_val_type > NO_SIZE &&
	    ctx->min_hpages > ctx->max_hpages) अणु
		pr_err("Minimum size can not be greater than maximum size\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
hugetlbfs_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा hugetlbfs_fs_context *ctx = fc->fs_निजी;
	काष्ठा hugetlbfs_sb_info *sbinfo;

	sbinfo = kदो_स्मृति(माप(काष्ठा hugetlbfs_sb_info), GFP_KERNEL);
	अगर (!sbinfo)
		वापस -ENOMEM;
	sb->s_fs_info = sbinfo;
	spin_lock_init(&sbinfo->stat_lock);
	sbinfo->hstate		= ctx->hstate;
	sbinfo->max_inodes	= ctx->nr_inodes;
	sbinfo->मुक्त_inodes	= ctx->nr_inodes;
	sbinfo->spool		= शून्य;
	sbinfo->uid		= ctx->uid;
	sbinfo->gid		= ctx->gid;
	sbinfo->mode		= ctx->mode;

	/*
	 * Allocate and initialize subpool अगर maximum or minimum size is
	 * specअगरied.  Any needed reservations (क्रम minimum size) are taken
	 * taken when the subpool is created.
	 */
	अगर (ctx->max_hpages != -1 || ctx->min_hpages != -1) अणु
		sbinfo->spool = hugepage_new_subpool(ctx->hstate,
						     ctx->max_hpages,
						     ctx->min_hpages);
		अगर (!sbinfo->spool)
			जाओ out_मुक्त;
	पूर्ण
	sb->s_maxbytes = MAX_LFS_खाताSIZE;
	sb->s_blocksize = huge_page_size(ctx->hstate);
	sb->s_blocksize_bits = huge_page_shअगरt(ctx->hstate);
	sb->s_magic = HUGETLBFS_MAGIC;
	sb->s_op = &hugetlbfs_ops;
	sb->s_समय_gran = 1;

	/*
	 * Due to the special and limited functionality of hugetlbfs, it करोes
	 * not work well as a stacking fileप्रणाली.
	 */
	sb->s_stack_depth = खाताSYSTEM_MAX_STACK_DEPTH;
	sb->s_root = d_make_root(hugetlbfs_get_root(sb, ctx));
	अगर (!sb->s_root)
		जाओ out_मुक्त;
	वापस 0;
out_मुक्त:
	kमुक्त(sbinfo->spool);
	kमुक्त(sbinfo);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक hugetlbfs_get_tree(काष्ठा fs_context *fc)
अणु
	पूर्णांक err = hugetlbfs_validate(fc);
	अगर (err)
		वापस err;
	वापस get_tree_nodev(fc, hugetlbfs_fill_super);
पूर्ण

अटल व्योम hugetlbfs_fs_context_मुक्त(काष्ठा fs_context *fc)
अणु
	kमुक्त(fc->fs_निजी);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations hugetlbfs_fs_context_ops = अणु
	.मुक्त		= hugetlbfs_fs_context_मुक्त,
	.parse_param	= hugetlbfs_parse_param,
	.get_tree	= hugetlbfs_get_tree,
पूर्ण;

अटल पूर्णांक hugetlbfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा hugetlbfs_fs_context *ctx;

	ctx = kzalloc(माप(काष्ठा hugetlbfs_fs_context), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->max_hpages	= -1; /* No limit on size by शेष */
	ctx->nr_inodes	= -1; /* No limit on number of inodes by शेष */
	ctx->uid	= current_fsuid();
	ctx->gid	= current_fsgid();
	ctx->mode	= 0755;
	ctx->hstate	= &शेष_hstate;
	ctx->min_hpages	= -1; /* No शेष minimum size */
	ctx->max_val_type = NO_SIZE;
	ctx->min_val_type = NO_SIZE;
	fc->fs_निजी = ctx;
	fc->ops	= &hugetlbfs_fs_context_ops;
	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type hugetlbfs_fs_type = अणु
	.name			= "hugetlbfs",
	.init_fs_context	= hugetlbfs_init_fs_context,
	.parameters		= hugetlb_fs_parameters,
	.समाप्त_sb		= समाप्त_litter_super,
पूर्ण;

अटल काष्ठा vfsmount *hugetlbfs_vfsmount[HUGE_MAX_HSTATE];

अटल पूर्णांक can_करो_hugetlb_shm(व्योम)
अणु
	kgid_t shm_group;
	shm_group = make_kgid(&init_user_ns, sysctl_hugetlb_shm_group);
	वापस capable(CAP_IPC_LOCK) || in_group_p(shm_group);
पूर्ण

अटल पूर्णांक get_hstate_idx(पूर्णांक page_size_log)
अणु
	काष्ठा hstate *h = hstate_sizelog(page_size_log);

	अगर (!h)
		वापस -1;
	वापस hstate_index(h);
पूर्ण

/*
 * Note that size should be aligned to proper hugepage size in caller side,
 * otherwise hugetlb_reserve_pages reserves one less hugepages than पूर्णांकended.
 */
काष्ठा file *hugetlb_file_setup(स्थिर अक्षर *name, माप_प्रकार size,
				vm_flags_t acctflag, काष्ठा user_काष्ठा **user,
				पूर्णांक creat_flags, पूर्णांक page_size_log)
अणु
	काष्ठा inode *inode;
	काष्ठा vfsmount *mnt;
	पूर्णांक hstate_idx;
	काष्ठा file *file;

	hstate_idx = get_hstate_idx(page_size_log);
	अगर (hstate_idx < 0)
		वापस ERR_PTR(-ENODEV);

	*user = शून्य;
	mnt = hugetlbfs_vfsmount[hstate_idx];
	अगर (!mnt)
		वापस ERR_PTR(-ENOENT);

	अगर (creat_flags == HUGETLB_SHMFS_INODE && !can_करो_hugetlb_shm()) अणु
		*user = current_user();
		अगर (user_shm_lock(size, *user)) अणु
			task_lock(current);
			pr_warn_once("%s (%d): Using mlock ulimits for SHM_HUGETLB is deprecated\n",
				current->comm, current->pid);
			task_unlock(current);
		पूर्ण अन्यथा अणु
			*user = शून्य;
			वापस ERR_PTR(-EPERM);
		पूर्ण
	पूर्ण

	file = ERR_PTR(-ENOSPC);
	inode = hugetlbfs_get_inode(mnt->mnt_sb, शून्य, S_IFREG | S_IRWXUGO, 0);
	अगर (!inode)
		जाओ out;
	अगर (creat_flags == HUGETLB_SHMFS_INODE)
		inode->i_flags |= S_PRIVATE;

	inode->i_size = size;
	clear_nlink(inode);

	अगर (!hugetlb_reserve_pages(inode, 0,
			size >> huge_page_shअगरt(hstate_inode(inode)), शून्य,
			acctflag))
		file = ERR_PTR(-ENOMEM);
	अन्यथा
		file = alloc_file_pseuकरो(inode, mnt, name, O_RDWR,
					&hugetlbfs_file_operations);
	अगर (!IS_ERR(file))
		वापस file;

	iput(inode);
out:
	अगर (*user) अणु
		user_shm_unlock(size, *user);
		*user = शून्य;
	पूर्ण
	वापस file;
पूर्ण

अटल काष्ठा vfsmount *__init mount_one_hugetlbfs(काष्ठा hstate *h)
अणु
	काष्ठा fs_context *fc;
	काष्ठा vfsmount *mnt;

	fc = fs_context_क्रम_mount(&hugetlbfs_fs_type, SB_KERNMOUNT);
	अगर (IS_ERR(fc)) अणु
		mnt = ERR_CAST(fc);
	पूर्ण अन्यथा अणु
		काष्ठा hugetlbfs_fs_context *ctx = fc->fs_निजी;
		ctx->hstate = h;
		mnt = fc_mount(fc);
		put_fs_context(fc);
	पूर्ण
	अगर (IS_ERR(mnt))
		pr_err("Cannot mount internal hugetlbfs for page size %luK",
		       huge_page_size(h) >> 10);
	वापस mnt;
पूर्ण

अटल पूर्णांक __init init_hugetlbfs_fs(व्योम)
अणु
	काष्ठा vfsmount *mnt;
	काष्ठा hstate *h;
	पूर्णांक error;
	पूर्णांक i;

	अगर (!hugepages_supported()) अणु
		pr_info("disabling because there are no supported hugepage sizes\n");
		वापस -ENOTSUPP;
	पूर्ण

	error = -ENOMEM;
	hugetlbfs_inode_cachep = kmem_cache_create("hugetlbfs_inode_cache",
					माप(काष्ठा hugetlbfs_inode_info),
					0, SLAB_ACCOUNT, init_once);
	अगर (hugetlbfs_inode_cachep == शून्य)
		जाओ out;

	error = रेजिस्टर_fileप्रणाली(&hugetlbfs_fs_type);
	अगर (error)
		जाओ out_मुक्त;

	/* शेष hstate mount is required */
	mnt = mount_one_hugetlbfs(&शेष_hstate);
	अगर (IS_ERR(mnt)) अणु
		error = PTR_ERR(mnt);
		जाओ out_unreg;
	पूर्ण
	hugetlbfs_vfsmount[शेष_hstate_idx] = mnt;

	/* other hstates are optional */
	i = 0;
	क्रम_each_hstate(h) अणु
		अगर (i == शेष_hstate_idx) अणु
			i++;
			जारी;
		पूर्ण

		mnt = mount_one_hugetlbfs(h);
		अगर (IS_ERR(mnt))
			hugetlbfs_vfsmount[i] = शून्य;
		अन्यथा
			hugetlbfs_vfsmount[i] = mnt;
		i++;
	पूर्ण

	वापस 0;

 out_unreg:
	(व्योम)unरेजिस्टर_fileप्रणाली(&hugetlbfs_fs_type);
 out_मुक्त:
	kmem_cache_destroy(hugetlbfs_inode_cachep);
 out:
	वापस error;
पूर्ण
fs_initcall(init_hugetlbfs_fs)
