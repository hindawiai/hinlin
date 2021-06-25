<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  mm/userfaultfd.c
 *
 *  Copyright (C) 2015  Red Hat, Inc.
 */

#समावेश <linux/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/rmap.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>
#समावेश <linux/userfaultfd_k.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/shmem_fs.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश "internal.h"

अटल __always_अंतरभूत
काष्ठा vm_area_काष्ठा *find_dst_vma(काष्ठा mm_काष्ठा *dst_mm,
				    अचिन्हित दीर्घ dst_start,
				    अचिन्हित दीर्घ len)
अणु
	/*
	 * Make sure that the dst range is both valid and fully within a
	 * single existing vma.
	 */
	काष्ठा vm_area_काष्ठा *dst_vma;

	dst_vma = find_vma(dst_mm, dst_start);
	अगर (!dst_vma)
		वापस शून्य;

	अगर (dst_start < dst_vma->vm_start ||
	    dst_start + len > dst_vma->vm_end)
		वापस शून्य;

	/*
	 * Check the vma is रेजिस्टरed in uffd, this is required to
	 * enक्रमce the VM_MAYWRITE check करोne at uffd registration
	 * समय.
	 */
	अगर (!dst_vma->vm_userfaultfd_ctx.ctx)
		वापस शून्य;

	वापस dst_vma;
पूर्ण

अटल पूर्णांक mcopy_atomic_pte(काष्ठा mm_काष्ठा *dst_mm,
			    pmd_t *dst_pmd,
			    काष्ठा vm_area_काष्ठा *dst_vma,
			    अचिन्हित दीर्घ dst_addr,
			    अचिन्हित दीर्घ src_addr,
			    काष्ठा page **pagep,
			    bool wp_copy)
अणु
	pte_t _dst_pte, *dst_pte;
	spinlock_t *ptl;
	व्योम *page_kaddr;
	पूर्णांक ret;
	काष्ठा page *page;
	pgoff_t offset, max_off;
	काष्ठा inode *inode;

	अगर (!*pagep) अणु
		ret = -ENOMEM;
		page = alloc_page_vma(GFP_HIGHUSER_MOVABLE, dst_vma, dst_addr);
		अगर (!page)
			जाओ out;

		page_kaddr = kmap_atomic(page);
		ret = copy_from_user(page_kaddr,
				     (स्थिर व्योम __user *) src_addr,
				     PAGE_SIZE);
		kunmap_atomic(page_kaddr);

		/* fallback to copy_from_user outside mmap_lock */
		अगर (unlikely(ret)) अणु
			ret = -ENOENT;
			*pagep = page;
			/* करोn't मुक्त the page */
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		page = *pagep;
		*pagep = शून्य;
	पूर्ण

	/*
	 * The memory barrier inside __SetPageUptodate makes sure that
	 * preceding stores to the page contents become visible beक्रमe
	 * the set_pte_at() ग_लिखो.
	 */
	__SetPageUptodate(page);

	ret = -ENOMEM;
	अगर (mem_cgroup_अक्षरge(page, dst_mm, GFP_KERNEL))
		जाओ out_release;

	_dst_pte = pte_सूची_गढ़ोty(mk_pte(page, dst_vma->vm_page_prot));
	अगर (dst_vma->vm_flags & VM_WRITE) अणु
		अगर (wp_copy)
			_dst_pte = pte_mkuffd_wp(_dst_pte);
		अन्यथा
			_dst_pte = pte_mkग_लिखो(_dst_pte);
	पूर्ण

	dst_pte = pte_offset_map_lock(dst_mm, dst_pmd, dst_addr, &ptl);
	अगर (dst_vma->vm_file) अणु
		/* the shmem MAP_PRIVATE हाल requires checking the i_size */
		inode = dst_vma->vm_file->f_inode;
		offset = linear_page_index(dst_vma, dst_addr);
		max_off = DIV_ROUND_UP(i_size_पढ़ो(inode), PAGE_SIZE);
		ret = -EFAULT;
		अगर (unlikely(offset >= max_off))
			जाओ out_release_unअक्षरge_unlock;
	पूर्ण
	ret = -EEXIST;
	अगर (!pte_none(*dst_pte))
		जाओ out_release_unअक्षरge_unlock;

	inc_mm_counter(dst_mm, MM_ANONPAGES);
	page_add_new_anon_rmap(page, dst_vma, dst_addr, false);
	lru_cache_add_inactive_or_unevictable(page, dst_vma);

	set_pte_at(dst_mm, dst_addr, dst_pte, _dst_pte);

	/* No need to invalidate - it was non-present beक्रमe */
	update_mmu_cache(dst_vma, dst_addr, dst_pte);

	pte_unmap_unlock(dst_pte, ptl);
	ret = 0;
out:
	वापस ret;
out_release_unअक्षरge_unlock:
	pte_unmap_unlock(dst_pte, ptl);
out_release:
	put_page(page);
	जाओ out;
पूर्ण

अटल पूर्णांक mfill_zeropage_pte(काष्ठा mm_काष्ठा *dst_mm,
			      pmd_t *dst_pmd,
			      काष्ठा vm_area_काष्ठा *dst_vma,
			      अचिन्हित दीर्घ dst_addr)
अणु
	pte_t _dst_pte, *dst_pte;
	spinlock_t *ptl;
	पूर्णांक ret;
	pgoff_t offset, max_off;
	काष्ठा inode *inode;

	_dst_pte = pte_mkspecial(pfn_pte(my_zero_pfn(dst_addr),
					 dst_vma->vm_page_prot));
	dst_pte = pte_offset_map_lock(dst_mm, dst_pmd, dst_addr, &ptl);
	अगर (dst_vma->vm_file) अणु
		/* the shmem MAP_PRIVATE हाल requires checking the i_size */
		inode = dst_vma->vm_file->f_inode;
		offset = linear_page_index(dst_vma, dst_addr);
		max_off = DIV_ROUND_UP(i_size_पढ़ो(inode), PAGE_SIZE);
		ret = -EFAULT;
		अगर (unlikely(offset >= max_off))
			जाओ out_unlock;
	पूर्ण
	ret = -EEXIST;
	अगर (!pte_none(*dst_pte))
		जाओ out_unlock;
	set_pte_at(dst_mm, dst_addr, dst_pte, _dst_pte);
	/* No need to invalidate - it was non-present beक्रमe */
	update_mmu_cache(dst_vma, dst_addr, dst_pte);
	ret = 0;
out_unlock:
	pte_unmap_unlock(dst_pte, ptl);
	वापस ret;
पूर्ण

अटल pmd_t *mm_alloc_pmd(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;

	pgd = pgd_offset(mm, address);
	p4d = p4d_alloc(mm, pgd, address);
	अगर (!p4d)
		वापस शून्य;
	pud = pud_alloc(mm, p4d, address);
	अगर (!pud)
		वापस शून्य;
	/*
	 * Note that we didn't run this because the pmd was
	 * missing, the *pmd may be alपढ़ोy established and in
	 * turn it may also be a trans_huge_pmd.
	 */
	वापस pmd_alloc(mm, pud, address);
पूर्ण

#अगर_घोषित CONFIG_HUGETLB_PAGE
/*
 * __mcopy_atomic processing क्रम HUGETLB vmas.  Note that this routine is
 * called with mmap_lock held, it will release mmap_lock beक्रमe वापसing.
 */
अटल __always_अंतरभूत sमाप_प्रकार __mcopy_atomic_hugetlb(काष्ठा mm_काष्ठा *dst_mm,
					      काष्ठा vm_area_काष्ठा *dst_vma,
					      अचिन्हित दीर्घ dst_start,
					      अचिन्हित दीर्घ src_start,
					      अचिन्हित दीर्घ len,
					      क्रमागत mcopy_atomic_mode mode)
अणु
	पूर्णांक vm_alloc_shared = dst_vma->vm_flags & VM_SHARED;
	पूर्णांक vm_shared = dst_vma->vm_flags & VM_SHARED;
	sमाप_प्रकार err;
	pte_t *dst_pte;
	अचिन्हित दीर्घ src_addr, dst_addr;
	दीर्घ copied;
	काष्ठा page *page;
	अचिन्हित दीर्घ vma_hpagesize;
	pgoff_t idx;
	u32 hash;
	काष्ठा address_space *mapping;

	/*
	 * There is no शेष zero huge page क्रम all huge page sizes as
	 * supported by hugetlb.  A PMD_SIZE huge pages may exist as used
	 * by THP.  Since we can not reliably insert a zero page, this
	 * feature is not supported.
	 */
	अगर (mode == MCOPY_ATOMIC_ZEROPAGE) अणु
		mmap_पढ़ो_unlock(dst_mm);
		वापस -EINVAL;
	पूर्ण

	src_addr = src_start;
	dst_addr = dst_start;
	copied = 0;
	page = शून्य;
	vma_hpagesize = vma_kernel_pagesize(dst_vma);

	/*
	 * Validate alignment based on huge page size
	 */
	err = -EINVAL;
	अगर (dst_start & (vma_hpagesize - 1) || len & (vma_hpagesize - 1))
		जाओ out_unlock;

retry:
	/*
	 * On routine entry dst_vma is set.  If we had to drop mmap_lock and
	 * retry, dst_vma will be set to शून्य and we must lookup again.
	 */
	अगर (!dst_vma) अणु
		err = -ENOENT;
		dst_vma = find_dst_vma(dst_mm, dst_start, len);
		अगर (!dst_vma || !is_vm_hugetlb_page(dst_vma))
			जाओ out_unlock;

		err = -EINVAL;
		अगर (vma_hpagesize != vma_kernel_pagesize(dst_vma))
			जाओ out_unlock;

		vm_shared = dst_vma->vm_flags & VM_SHARED;
	पूर्ण

	/*
	 * If not shared, ensure the dst_vma has a anon_vma.
	 */
	err = -ENOMEM;
	अगर (!vm_shared) अणु
		अगर (unlikely(anon_vma_prepare(dst_vma)))
			जाओ out_unlock;
	पूर्ण

	जबतक (src_addr < src_start + len) अणु
		BUG_ON(dst_addr >= dst_start + len);

		/*
		 * Serialize via i_mmap_rwsem and hugetlb_fault_mutex.
		 * i_mmap_rwsem ensures the dst_pte reमुख्यs valid even
		 * in the हाल of shared pmds.  fault mutex prevents
		 * races with other faulting thपढ़ोs.
		 */
		mapping = dst_vma->vm_file->f_mapping;
		i_mmap_lock_पढ़ो(mapping);
		idx = linear_page_index(dst_vma, dst_addr);
		hash = hugetlb_fault_mutex_hash(mapping, idx);
		mutex_lock(&hugetlb_fault_mutex_table[hash]);

		err = -ENOMEM;
		dst_pte = huge_pte_alloc(dst_mm, dst_vma, dst_addr, vma_hpagesize);
		अगर (!dst_pte) अणु
			mutex_unlock(&hugetlb_fault_mutex_table[hash]);
			i_mmap_unlock_पढ़ो(mapping);
			जाओ out_unlock;
		पूर्ण

		अगर (mode != MCOPY_ATOMIC_CONTINUE &&
		    !huge_pte_none(huge_ptep_get(dst_pte))) अणु
			err = -EEXIST;
			mutex_unlock(&hugetlb_fault_mutex_table[hash]);
			i_mmap_unlock_पढ़ो(mapping);
			जाओ out_unlock;
		पूर्ण

		err = hugetlb_mcopy_atomic_pte(dst_mm, dst_pte, dst_vma,
					       dst_addr, src_addr, mode, &page);

		mutex_unlock(&hugetlb_fault_mutex_table[hash]);
		i_mmap_unlock_पढ़ो(mapping);
		vm_alloc_shared = vm_shared;

		cond_resched();

		अगर (unlikely(err == -ENOENT)) अणु
			mmap_पढ़ो_unlock(dst_mm);
			BUG_ON(!page);

			err = copy_huge_page_from_user(page,
						(स्थिर व्योम __user *)src_addr,
						vma_hpagesize / PAGE_SIZE,
						true);
			अगर (unlikely(err)) अणु
				err = -EFAULT;
				जाओ out;
			पूर्ण
			mmap_पढ़ो_lock(dst_mm);

			dst_vma = शून्य;
			जाओ retry;
		पूर्ण अन्यथा
			BUG_ON(page);

		अगर (!err) अणु
			dst_addr += vma_hpagesize;
			src_addr += vma_hpagesize;
			copied += vma_hpagesize;

			अगर (fatal_संकेत_pending(current))
				err = -EINTR;
		पूर्ण
		अगर (err)
			अवरोध;
	पूर्ण

out_unlock:
	mmap_पढ़ो_unlock(dst_mm);
out:
	अगर (page) अणु
		/*
		 * We encountered an error and are about to मुक्त a newly
		 * allocated huge page.
		 *
		 * Reservation handling is very subtle, and is dअगरferent क्रम
		 * निजी and shared mappings.  See the routine
		 * restore_reserve_on_error क्रम details.  Unक्रमtunately, we
		 * can not call restore_reserve_on_error now as it would
		 * require holding mmap_lock.
		 *
		 * If a reservation क्रम the page existed in the reservation
		 * map of a निजी mapping, the map was modअगरied to indicate
		 * the reservation was consumed when the page was allocated.
		 * We clear the HPageRestoreReserve flag now so that the global
		 * reserve count will not be incremented in मुक्त_huge_page.
		 * The reservation map will still indicate the reservation
		 * was consumed and possibly prevent later page allocation.
		 * This is better than leaking a global reservation.  If no
		 * reservation existed, it is still safe to clear
		 * HPageRestoreReserve as no adjusपंचांगents to reservation counts
		 * were made during allocation.
		 *
		 * The reservation map क्रम shared mappings indicates which
		 * pages have reservations.  When a huge page is allocated
		 * क्रम an address with a reservation, no change is made to
		 * the reserve map.  In this हाल HPageRestoreReserve will be
		 * set to indicate that the global reservation count should be
		 * incremented when the page is मुक्तd.  This is the desired
		 * behavior.  However, when a huge page is allocated क्रम an
		 * address without a reservation a reservation entry is added
		 * to the reservation map, and HPageRestoreReserve will not be
		 * set. When the page is मुक्तd, the global reserve count will
		 * NOT be incremented and it will appear as though we have
		 * leaked reserved page.  In this हाल, set HPageRestoreReserve
		 * so that the global reserve count will be incremented to
		 * match the reservation map entry which was created.
		 *
		 * Note that vm_alloc_shared is based on the flags of the vma
		 * क्रम which the page was originally allocated.  dst_vma could
		 * be dअगरferent or शून्य on error.
		 */
		अगर (vm_alloc_shared)
			SetHPageRestoreReserve(page);
		अन्यथा
			ClearHPageRestoreReserve(page);
		put_page(page);
	पूर्ण
	BUG_ON(copied < 0);
	BUG_ON(err > 0);
	BUG_ON(!copied && !err);
	वापस copied ? copied : err;
पूर्ण
#अन्यथा /* !CONFIG_HUGETLB_PAGE */
/* fail at build समय अगर gcc attempts to use this */
बाह्य sमाप_प्रकार __mcopy_atomic_hugetlb(काष्ठा mm_काष्ठा *dst_mm,
				      काष्ठा vm_area_काष्ठा *dst_vma,
				      अचिन्हित दीर्घ dst_start,
				      अचिन्हित दीर्घ src_start,
				      अचिन्हित दीर्घ len,
				      क्रमागत mcopy_atomic_mode mode);
#पूर्ण_अगर /* CONFIG_HUGETLB_PAGE */

अटल __always_अंतरभूत sमाप_प्रकार mfill_atomic_pte(काष्ठा mm_काष्ठा *dst_mm,
						pmd_t *dst_pmd,
						काष्ठा vm_area_काष्ठा *dst_vma,
						अचिन्हित दीर्घ dst_addr,
						अचिन्हित दीर्घ src_addr,
						काष्ठा page **page,
						bool zeropage,
						bool wp_copy)
अणु
	sमाप_प्रकार err;

	/*
	 * The normal page fault path क्रम a shmem will invoke the
	 * fault, fill the hole in the file and COW it right away. The
	 * result generates plain anonymous memory. So when we are
	 * asked to fill an hole in a MAP_PRIVATE shmem mapping, we'll
	 * generate anonymous memory directly without actually filling
	 * the hole. For the MAP_PRIVATE हाल the robustness check
	 * only happens in the pagetable (to verअगरy it's still none)
	 * and not in the radix tree.
	 */
	अगर (!(dst_vma->vm_flags & VM_SHARED)) अणु
		अगर (!zeropage)
			err = mcopy_atomic_pte(dst_mm, dst_pmd, dst_vma,
					       dst_addr, src_addr, page,
					       wp_copy);
		अन्यथा
			err = mfill_zeropage_pte(dst_mm, dst_pmd,
						 dst_vma, dst_addr);
	पूर्ण अन्यथा अणु
		VM_WARN_ON_ONCE(wp_copy);
		अगर (!zeropage)
			err = shmem_mcopy_atomic_pte(dst_mm, dst_pmd,
						     dst_vma, dst_addr,
						     src_addr, page);
		अन्यथा
			err = shmem_mfill_zeropage_pte(dst_mm, dst_pmd,
						       dst_vma, dst_addr);
	पूर्ण

	वापस err;
पूर्ण

अटल __always_अंतरभूत sमाप_प्रकार __mcopy_atomic(काष्ठा mm_काष्ठा *dst_mm,
					      अचिन्हित दीर्घ dst_start,
					      अचिन्हित दीर्घ src_start,
					      अचिन्हित दीर्घ len,
					      क्रमागत mcopy_atomic_mode mcopy_mode,
					      bool *mmap_changing,
					      __u64 mode)
अणु
	काष्ठा vm_area_काष्ठा *dst_vma;
	sमाप_प्रकार err;
	pmd_t *dst_pmd;
	अचिन्हित दीर्घ src_addr, dst_addr;
	दीर्घ copied;
	काष्ठा page *page;
	bool wp_copy;
	bool zeropage = (mcopy_mode == MCOPY_ATOMIC_ZEROPAGE);

	/*
	 * Sanitize the command parameters:
	 */
	BUG_ON(dst_start & ~PAGE_MASK);
	BUG_ON(len & ~PAGE_MASK);

	/* Does the address range wrap, or is the span zero-sized? */
	BUG_ON(src_start + len <= src_start);
	BUG_ON(dst_start + len <= dst_start);

	src_addr = src_start;
	dst_addr = dst_start;
	copied = 0;
	page = शून्य;
retry:
	mmap_पढ़ो_lock(dst_mm);

	/*
	 * If memory mappings are changing because of non-cooperative
	 * operation (e.g. mremap) running in parallel, bail out and
	 * request the user to retry later
	 */
	err = -EAGAIN;
	अगर (mmap_changing && READ_ONCE(*mmap_changing))
		जाओ out_unlock;

	/*
	 * Make sure the vma is not shared, that the dst range is
	 * both valid and fully within a single existing vma.
	 */
	err = -ENOENT;
	dst_vma = find_dst_vma(dst_mm, dst_start, len);
	अगर (!dst_vma)
		जाओ out_unlock;

	err = -EINVAL;
	/*
	 * shmem_zero_setup is invoked in mmap क्रम MAP_ANONYMOUS|MAP_SHARED but
	 * it will overग_लिखो vm_ops, so vma_is_anonymous must वापस false.
	 */
	अगर (WARN_ON_ONCE(vma_is_anonymous(dst_vma) &&
	    dst_vma->vm_flags & VM_SHARED))
		जाओ out_unlock;

	/*
	 * validate 'mode' now that we know the dst_vma: don't allow
	 * a wrprotect copy अगर the userfaultfd didn't रेजिस्टर as WP.
	 */
	wp_copy = mode & UFFDIO_COPY_MODE_WP;
	अगर (wp_copy && !(dst_vma->vm_flags & VM_UFFD_WP))
		जाओ out_unlock;

	/*
	 * If this is a HUGETLB vma, pass off to appropriate routine
	 */
	अगर (is_vm_hugetlb_page(dst_vma))
		वापस  __mcopy_atomic_hugetlb(dst_mm, dst_vma, dst_start,
						src_start, len, mcopy_mode);

	अगर (!vma_is_anonymous(dst_vma) && !vma_is_shmem(dst_vma))
		जाओ out_unlock;
	अगर (mcopy_mode == MCOPY_ATOMIC_CONTINUE)
		जाओ out_unlock;

	/*
	 * Ensure the dst_vma has a anon_vma or this page
	 * would get a शून्य anon_vma when moved in the
	 * dst_vma.
	 */
	err = -ENOMEM;
	अगर (!(dst_vma->vm_flags & VM_SHARED) &&
	    unlikely(anon_vma_prepare(dst_vma)))
		जाओ out_unlock;

	जबतक (src_addr < src_start + len) अणु
		pmd_t dst_pmdval;

		BUG_ON(dst_addr >= dst_start + len);

		dst_pmd = mm_alloc_pmd(dst_mm, dst_addr);
		अगर (unlikely(!dst_pmd)) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		dst_pmdval = pmd_पढ़ो_atomic(dst_pmd);
		/*
		 * If the dst_pmd is mapped as THP करोn't
		 * override it and just be strict.
		 */
		अगर (unlikely(pmd_trans_huge(dst_pmdval))) अणु
			err = -EEXIST;
			अवरोध;
		पूर्ण
		अगर (unlikely(pmd_none(dst_pmdval)) &&
		    unlikely(__pte_alloc(dst_mm, dst_pmd))) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण
		/* If an huge pmd materialized from under us fail */
		अगर (unlikely(pmd_trans_huge(*dst_pmd))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		BUG_ON(pmd_none(*dst_pmd));
		BUG_ON(pmd_trans_huge(*dst_pmd));

		err = mfill_atomic_pte(dst_mm, dst_pmd, dst_vma, dst_addr,
				       src_addr, &page, zeropage, wp_copy);
		cond_resched();

		अगर (unlikely(err == -ENOENT)) अणु
			व्योम *page_kaddr;

			mmap_पढ़ो_unlock(dst_mm);
			BUG_ON(!page);

			page_kaddr = kmap(page);
			err = copy_from_user(page_kaddr,
					     (स्थिर व्योम __user *) src_addr,
					     PAGE_SIZE);
			kunmap(page);
			अगर (unlikely(err)) अणु
				err = -EFAULT;
				जाओ out;
			पूर्ण
			जाओ retry;
		पूर्ण अन्यथा
			BUG_ON(page);

		अगर (!err) अणु
			dst_addr += PAGE_SIZE;
			src_addr += PAGE_SIZE;
			copied += PAGE_SIZE;

			अगर (fatal_संकेत_pending(current))
				err = -EINTR;
		पूर्ण
		अगर (err)
			अवरोध;
	पूर्ण

out_unlock:
	mmap_पढ़ो_unlock(dst_mm);
out:
	अगर (page)
		put_page(page);
	BUG_ON(copied < 0);
	BUG_ON(err > 0);
	BUG_ON(!copied && !err);
	वापस copied ? copied : err;
पूर्ण

sमाप_प्रकार mcopy_atomic(काष्ठा mm_काष्ठा *dst_mm, अचिन्हित दीर्घ dst_start,
		     अचिन्हित दीर्घ src_start, अचिन्हित दीर्घ len,
		     bool *mmap_changing, __u64 mode)
अणु
	वापस __mcopy_atomic(dst_mm, dst_start, src_start, len,
			      MCOPY_ATOMIC_NORMAL, mmap_changing, mode);
पूर्ण

sमाप_प्रकार mfill_zeropage(काष्ठा mm_काष्ठा *dst_mm, अचिन्हित दीर्घ start,
		       अचिन्हित दीर्घ len, bool *mmap_changing)
अणु
	वापस __mcopy_atomic(dst_mm, start, 0, len, MCOPY_ATOMIC_ZEROPAGE,
			      mmap_changing, 0);
पूर्ण

sमाप_प्रकार mcopy_जारी(काष्ठा mm_काष्ठा *dst_mm, अचिन्हित दीर्घ start,
		       अचिन्हित दीर्घ len, bool *mmap_changing)
अणु
	वापस __mcopy_atomic(dst_mm, start, 0, len, MCOPY_ATOMIC_CONTINUE,
			      mmap_changing, 0);
पूर्ण

पूर्णांक mग_लिखोprotect_range(काष्ठा mm_काष्ठा *dst_mm, अचिन्हित दीर्घ start,
			अचिन्हित दीर्घ len, bool enable_wp, bool *mmap_changing)
अणु
	काष्ठा vm_area_काष्ठा *dst_vma;
	pgprot_t newprot;
	पूर्णांक err;

	/*
	 * Sanitize the command parameters:
	 */
	BUG_ON(start & ~PAGE_MASK);
	BUG_ON(len & ~PAGE_MASK);

	/* Does the address range wrap, or is the span zero-sized? */
	BUG_ON(start + len <= start);

	mmap_पढ़ो_lock(dst_mm);

	/*
	 * If memory mappings are changing because of non-cooperative
	 * operation (e.g. mremap) running in parallel, bail out and
	 * request the user to retry later
	 */
	err = -EAGAIN;
	अगर (mmap_changing && READ_ONCE(*mmap_changing))
		जाओ out_unlock;

	err = -ENOENT;
	dst_vma = find_dst_vma(dst_mm, start, len);
	/*
	 * Make sure the vma is not shared, that the dst range is
	 * both valid and fully within a single existing vma.
	 */
	अगर (!dst_vma || (dst_vma->vm_flags & VM_SHARED))
		जाओ out_unlock;
	अगर (!userfaultfd_wp(dst_vma))
		जाओ out_unlock;
	अगर (!vma_is_anonymous(dst_vma))
		जाओ out_unlock;

	अगर (enable_wp)
		newprot = vm_get_page_prot(dst_vma->vm_flags & ~(VM_WRITE));
	अन्यथा
		newprot = vm_get_page_prot(dst_vma->vm_flags);

	change_protection(dst_vma, start, start + len, newprot,
			  enable_wp ? MM_CP_UFFD_WP : MM_CP_UFFD_WP_RESOLVE);

	err = 0;
out_unlock:
	mmap_पढ़ो_unlock(dst_mm);
	वापस err;
पूर्ण
