<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mm/fault-armv.c
 *
 *  Copyright (C) 1995  Linus Torvalds
 *  Modअगरications क्रम ARM processor (c) 1995-2002 Russell King
 */
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/bitops.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/bugs.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cachetype.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "mm.h"

अटल pteval_t shared_pte_mask = L_PTE_MT_BUFFERABLE;

#अगर __LINUX_ARM_ARCH__ < 6
/*
 * We take the easy way out of this problem - we make the
 * PTE uncacheable.  However, we leave the ग_लिखो buffer on.
 *
 * Note that the pte lock held when calling update_mmu_cache must also
 * guard the pte (somewhere अन्यथा in the same mm) that we modअगरy here.
 * Thereक्रमe those configurations which might call adjust_pte (those
 * without CONFIG_CPU_CACHE_VIPT) cannot support split page_table_lock.
 */
अटल पूर्णांक करो_adjust_pte(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
	अचिन्हित दीर्घ pfn, pte_t *ptep)
अणु
	pte_t entry = *ptep;
	पूर्णांक ret;

	/*
	 * If this page is present, it's actually being shared.
	 */
	ret = pte_present(entry);

	/*
	 * If this page isn't present, or is alपढ़ोy setup to
	 * fault (ie, is old), we can safely ignore any issues.
	 */
	अगर (ret && (pte_val(entry) & L_PTE_MT_MASK) != shared_pte_mask) अणु
		flush_cache_page(vma, address, pfn);
		outer_flush_range((pfn << PAGE_SHIFT),
				  (pfn << PAGE_SHIFT) + PAGE_SIZE);
		pte_val(entry) &= ~L_PTE_MT_MASK;
		pte_val(entry) |= shared_pte_mask;
		set_pte_at(vma->vm_mm, address, ptep, entry);
		flush_tlb_page(vma, address);
	पूर्ण

	वापस ret;
पूर्ण

#अगर USE_SPLIT_PTE_PTLOCKS
/*
 * If we are using split PTE locks, then we need to take the page
 * lock here.  Otherwise we are using shared mm->page_table_lock
 * which is alपढ़ोy locked, thus cannot take it.
 */
अटल अंतरभूत व्योम करो_pte_lock(spinlock_t *ptl)
अणु
	/*
	 * Use nested version here to indicate that we are alपढ़ोy
	 * holding one similar spinlock.
	 */
	spin_lock_nested(ptl, SINGLE_DEPTH_NESTING);
पूर्ण

अटल अंतरभूत व्योम करो_pte_unlock(spinlock_t *ptl)
अणु
	spin_unlock(ptl);
पूर्ण
#अन्यथा /* !USE_SPLIT_PTE_PTLOCKS */
अटल अंतरभूत व्योम करो_pte_lock(spinlock_t *ptl) अणुपूर्ण
अटल अंतरभूत व्योम करो_pte_unlock(spinlock_t *ptl) अणुपूर्ण
#पूर्ण_अगर /* USE_SPLIT_PTE_PTLOCKS */

अटल पूर्णांक adjust_pte(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
	अचिन्हित दीर्घ pfn)
अणु
	spinlock_t *ptl;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	पूर्णांक ret;

	pgd = pgd_offset(vma->vm_mm, address);
	अगर (pgd_none_or_clear_bad(pgd))
		वापस 0;

	p4d = p4d_offset(pgd, address);
	अगर (p4d_none_or_clear_bad(p4d))
		वापस 0;

	pud = pud_offset(p4d, address);
	अगर (pud_none_or_clear_bad(pud))
		वापस 0;

	pmd = pmd_offset(pud, address);
	अगर (pmd_none_or_clear_bad(pmd))
		वापस 0;

	/*
	 * This is called जबतक another page table is mapped, so we
	 * must use the nested version.  This also means we need to
	 * खोलो-code the spin-locking.
	 */
	ptl = pte_lockptr(vma->vm_mm, pmd);
	pte = pte_offset_map(pmd, address);
	करो_pte_lock(ptl);

	ret = करो_adjust_pte(vma, address, pfn, pte);

	करो_pte_unlock(ptl);
	pte_unmap(pte);

	वापस ret;
पूर्ण

अटल व्योम
make_coherent(काष्ठा address_space *mapping, काष्ठा vm_area_काष्ठा *vma,
	अचिन्हित दीर्घ addr, pte_t *ptep, अचिन्हित दीर्घ pfn)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	काष्ठा vm_area_काष्ठा *mpnt;
	अचिन्हित दीर्घ offset;
	pgoff_t pgoff;
	पूर्णांक aliases = 0;

	pgoff = vma->vm_pgoff + ((addr - vma->vm_start) >> PAGE_SHIFT);

	/*
	 * If we have any shared mappings that are in the same mm
	 * space, then we need to handle them specially to मुख्यtain
	 * cache coherency.
	 */
	flush_dcache_mmap_lock(mapping);
	vma_पूर्णांकerval_tree_क्रमeach(mpnt, &mapping->i_mmap, pgoff, pgoff) अणु
		/*
		 * If this VMA is not in our MM, we can ignore it.
		 * Note that we पूर्णांकentionally mask out the VMA
		 * that we are fixing up.
		 */
		अगर (mpnt->vm_mm != mm || mpnt == vma)
			जारी;
		अगर (!(mpnt->vm_flags & VM_MAYSHARE))
			जारी;
		offset = (pgoff - mpnt->vm_pgoff) << PAGE_SHIFT;
		aliases += adjust_pte(mpnt, mpnt->vm_start + offset, pfn);
	पूर्ण
	flush_dcache_mmap_unlock(mapping);
	अगर (aliases)
		करो_adjust_pte(vma, addr, pfn, ptep);
पूर्ण

/*
 * Take care of architecture specअगरic things when placing a new PTE पूर्णांकo
 * a page table, or changing an existing PTE.  Basically, there are two
 * things that we need to take care of:
 *
 *  1. If PG_dcache_clean is not set क्रम the page, we need to ensure
 *     that any cache entries क्रम the kernels भव memory
 *     range are written back to the page.
 *  2. If we have multiple shared mappings of the same space in
 *     an object, we need to deal with the cache aliasing issues.
 *
 * Note that the pte lock will be held.
 */
व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
	pte_t *ptep)
अणु
	अचिन्हित दीर्घ pfn = pte_pfn(*ptep);
	काष्ठा address_space *mapping;
	काष्ठा page *page;

	अगर (!pfn_valid(pfn))
		वापस;

	/*
	 * The zero page is never written to, so never has any dirty
	 * cache lines, and thereक्रमe never needs to be flushed.
	 */
	page = pfn_to_page(pfn);
	अगर (page == ZERO_PAGE(0))
		वापस;

	mapping = page_mapping_file(page);
	अगर (!test_and_set_bit(PG_dcache_clean, &page->flags))
		__flush_dcache_page(mapping, page);
	अगर (mapping) अणु
		अगर (cache_is_vivt())
			make_coherent(mapping, vma, addr, ptep, pfn);
		अन्यथा अगर (vma->vm_flags & VM_EXEC)
			__flush_icache_all();
	पूर्ण
पूर्ण
#पूर्ण_अगर	/* __LINUX_ARM_ARCH__ < 6 */

/*
 * Check whether the ग_लिखो buffer has physical address aliasing
 * issues.  If it has, we need to aव्योम them क्रम the हाल where
 * we have several shared mappings of the same object in user
 * space.
 */
अटल पूर्णांक __init check_ग_लिखोbuffer(अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2)
अणु
	रेजिस्टर अचिन्हित दीर्घ zero = 0, one = 1, val;

	local_irq_disable();
	mb();
	*p1 = one;
	mb();
	*p2 = zero;
	mb();
	val = *p1;
	mb();
	local_irq_enable();
	वापस val != zero;
पूर्ण

व्योम __init check_ग_लिखोbuffer_bugs(व्योम)
अणु
	काष्ठा page *page;
	स्थिर अक्षर *reason;
	अचिन्हित दीर्घ v = 1;

	pr_info("CPU: Testing write buffer coherency: ");

	page = alloc_page(GFP_KERNEL);
	अगर (page) अणु
		अचिन्हित दीर्घ *p1, *p2;
		pgprot_t prot = __pgprot_modअगरy(PAGE_KERNEL,
					L_PTE_MT_MASK, L_PTE_MT_BUFFERABLE);

		p1 = vmap(&page, 1, VM_IOREMAP, prot);
		p2 = vmap(&page, 1, VM_IOREMAP, prot);

		अगर (p1 && p2) अणु
			v = check_ग_लिखोbuffer(p1, p2);
			reason = "enabling work-around";
		पूर्ण अन्यथा अणु
			reason = "unable to map memory\n";
		पूर्ण

		vunmap(p1);
		vunmap(p2);
		put_page(page);
	पूर्ण अन्यथा अणु
		reason = "unable to grab page\n";
	पूर्ण

	अगर (v) अणु
		pr_cont("failed, %s\n", reason);
		shared_pte_mask = L_PTE_MT_UNCACHED;
	पूर्ण अन्यथा अणु
		pr_cont("ok\n");
	पूर्ण
पूर्ण
