<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * KVM/MIPS MMU handling in the KVM module.
 *
 * Copyright (C) 2012  MIPS Technologies, Inc.  All rights reserved.
 * Authors: Sanjay Lal <sanjayl@kymasys.com>
 */

#समावेश <linux/highस्मृति.स>
#समावेश <linux/kvm_host.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/pgभाग.स>

/*
 * KVM_MMU_CACHE_MIN_PAGES is the number of GPA page table translation levels
 * क्रम which pages need to be cached.
 */
#अगर defined(__PAGETABLE_PMD_FOLDED)
#घोषणा KVM_MMU_CACHE_MIN_PAGES 1
#अन्यथा
#घोषणा KVM_MMU_CACHE_MIN_PAGES 2
#पूर्ण_अगर

व्योम kvm_mmu_मुक्त_memory_caches(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_mmu_मुक्त_memory_cache(&vcpu->arch.mmu_page_cache);
पूर्ण

/**
 * kvm_pgd_init() - Initialise KVM GPA page directory.
 * @page:	Poपूर्णांकer to page directory (PGD) क्रम KVM GPA.
 *
 * Initialise a KVM GPA page directory with poपूर्णांकers to the invalid table, i.e.
 * representing no mappings. This is similar to pgd_init(), however it
 * initialises all the page directory poपूर्णांकers, not just the ones corresponding
 * to the userland address space (since it is क्रम the guest physical address
 * space rather than a भव address space).
 */
अटल व्योम kvm_pgd_init(व्योम *page)
अणु
	अचिन्हित दीर्घ *p, *end;
	अचिन्हित दीर्घ entry;

#अगर_घोषित __PAGETABLE_PMD_FOLDED
	entry = (अचिन्हित दीर्घ)invalid_pte_table;
#अन्यथा
	entry = (अचिन्हित दीर्घ)invalid_pmd_table;
#पूर्ण_अगर

	p = (अचिन्हित दीर्घ *)page;
	end = p + PTRS_PER_PGD;

	करो अणु
		p[0] = entry;
		p[1] = entry;
		p[2] = entry;
		p[3] = entry;
		p[4] = entry;
		p += 8;
		p[-3] = entry;
		p[-2] = entry;
		p[-1] = entry;
	पूर्ण जबतक (p != end);
पूर्ण

/**
 * kvm_pgd_alloc() - Allocate and initialise a KVM GPA page directory.
 *
 * Allocate a blank KVM GPA page directory (PGD) क्रम representing guest physical
 * to host physical page mappings.
 *
 * Returns:	Poपूर्णांकer to new KVM GPA page directory.
 *		शून्य on allocation failure.
 */
pgd_t *kvm_pgd_alloc(व्योम)
अणु
	pgd_t *ret;

	ret = (pgd_t *)__get_मुक्त_pages(GFP_KERNEL, PGD_ORDER);
	अगर (ret)
		kvm_pgd_init(ret);

	वापस ret;
पूर्ण

/**
 * kvm_mips_walk_pgd() - Walk page table with optional allocation.
 * @pgd:	Page directory poपूर्णांकer.
 * @addr:	Address to index page table using.
 * @cache:	MMU page cache to allocate new page tables from, or शून्य.
 *
 * Walk the page tables poपूर्णांकed to by @pgd to find the PTE corresponding to the
 * address @addr. If page tables करोn't exist क्रम @addr, they will be created
 * from the MMU cache अगर @cache is not शून्य.
 *
 * Returns:	Poपूर्णांकer to pte_t corresponding to @addr.
 *		शून्य अगर a page table करोesn't exist क्रम @addr and !@cache.
 *		शून्य अगर a page table allocation failed.
 */
अटल pte_t *kvm_mips_walk_pgd(pgd_t *pgd, काष्ठा kvm_mmu_memory_cache *cache,
				अचिन्हित दीर्घ addr)
अणु
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	pgd += pgd_index(addr);
	अगर (pgd_none(*pgd)) अणु
		/* Not used on MIPS yet */
		BUG();
		वापस शून्य;
	पूर्ण
	p4d = p4d_offset(pgd, addr);
	pud = pud_offset(p4d, addr);
	अगर (pud_none(*pud)) अणु
		pmd_t *new_pmd;

		अगर (!cache)
			वापस शून्य;
		new_pmd = kvm_mmu_memory_cache_alloc(cache);
		pmd_init((अचिन्हित दीर्घ)new_pmd,
			 (अचिन्हित दीर्घ)invalid_pte_table);
		pud_populate(शून्य, pud, new_pmd);
	पूर्ण
	pmd = pmd_offset(pud, addr);
	अगर (pmd_none(*pmd)) अणु
		pte_t *new_pte;

		अगर (!cache)
			वापस शून्य;
		new_pte = kvm_mmu_memory_cache_alloc(cache);
		clear_page(new_pte);
		pmd_populate_kernel(शून्य, pmd, new_pte);
	पूर्ण
	वापस pte_offset_kernel(pmd, addr);
पूर्ण

/* Caller must hold kvm->mm_lock */
अटल pte_t *kvm_mips_pte_क्रम_gpa(काष्ठा kvm *kvm,
				   काष्ठा kvm_mmu_memory_cache *cache,
				   अचिन्हित दीर्घ addr)
अणु
	वापस kvm_mips_walk_pgd(kvm->arch.gpa_mm.pgd, cache, addr);
पूर्ण

/*
 * kvm_mips_flush_gpa_अणुpte,pmd,pud,pgd,ptपूर्ण.
 * Flush a range of guest physical address space from the VM's GPA page tables.
 */

अटल bool kvm_mips_flush_gpa_pte(pte_t *pte, अचिन्हित दीर्घ start_gpa,
				   अचिन्हित दीर्घ end_gpa)
अणु
	पूर्णांक i_min = pte_index(start_gpa);
	पूर्णांक i_max = pte_index(end_gpa);
	bool safe_to_हटाओ = (i_min == 0 && i_max == PTRS_PER_PTE - 1);
	पूर्णांक i;

	क्रम (i = i_min; i <= i_max; ++i) अणु
		अगर (!pte_present(pte[i]))
			जारी;

		set_pte(pte + i, __pte(0));
	पूर्ण
	वापस safe_to_हटाओ;
पूर्ण

अटल bool kvm_mips_flush_gpa_pmd(pmd_t *pmd, अचिन्हित दीर्घ start_gpa,
				   अचिन्हित दीर्घ end_gpa)
अणु
	pte_t *pte;
	अचिन्हित दीर्घ end = ~0ul;
	पूर्णांक i_min = pmd_index(start_gpa);
	पूर्णांक i_max = pmd_index(end_gpa);
	bool safe_to_हटाओ = (i_min == 0 && i_max == PTRS_PER_PMD - 1);
	पूर्णांक i;

	क्रम (i = i_min; i <= i_max; ++i, start_gpa = 0) अणु
		अगर (!pmd_present(pmd[i]))
			जारी;

		pte = pte_offset_kernel(pmd + i, 0);
		अगर (i == i_max)
			end = end_gpa;

		अगर (kvm_mips_flush_gpa_pte(pte, start_gpa, end)) अणु
			pmd_clear(pmd + i);
			pte_मुक्त_kernel(शून्य, pte);
		पूर्ण अन्यथा अणु
			safe_to_हटाओ = false;
		पूर्ण
	पूर्ण
	वापस safe_to_हटाओ;
पूर्ण

अटल bool kvm_mips_flush_gpa_pud(pud_t *pud, अचिन्हित दीर्घ start_gpa,
				   अचिन्हित दीर्घ end_gpa)
अणु
	pmd_t *pmd;
	अचिन्हित दीर्घ end = ~0ul;
	पूर्णांक i_min = pud_index(start_gpa);
	पूर्णांक i_max = pud_index(end_gpa);
	bool safe_to_हटाओ = (i_min == 0 && i_max == PTRS_PER_PUD - 1);
	पूर्णांक i;

	क्रम (i = i_min; i <= i_max; ++i, start_gpa = 0) अणु
		अगर (!pud_present(pud[i]))
			जारी;

		pmd = pmd_offset(pud + i, 0);
		अगर (i == i_max)
			end = end_gpa;

		अगर (kvm_mips_flush_gpa_pmd(pmd, start_gpa, end)) अणु
			pud_clear(pud + i);
			pmd_मुक्त(शून्य, pmd);
		पूर्ण अन्यथा अणु
			safe_to_हटाओ = false;
		पूर्ण
	पूर्ण
	वापस safe_to_हटाओ;
पूर्ण

अटल bool kvm_mips_flush_gpa_pgd(pgd_t *pgd, अचिन्हित दीर्घ start_gpa,
				   अचिन्हित दीर्घ end_gpa)
अणु
	p4d_t *p4d;
	pud_t *pud;
	अचिन्हित दीर्घ end = ~0ul;
	पूर्णांक i_min = pgd_index(start_gpa);
	पूर्णांक i_max = pgd_index(end_gpa);
	bool safe_to_हटाओ = (i_min == 0 && i_max == PTRS_PER_PGD - 1);
	पूर्णांक i;

	क्रम (i = i_min; i <= i_max; ++i, start_gpa = 0) अणु
		अगर (!pgd_present(pgd[i]))
			जारी;

		p4d = p4d_offset(pgd, 0);
		pud = pud_offset(p4d + i, 0);
		अगर (i == i_max)
			end = end_gpa;

		अगर (kvm_mips_flush_gpa_pud(pud, start_gpa, end)) अणु
			pgd_clear(pgd + i);
			pud_मुक्त(शून्य, pud);
		पूर्ण अन्यथा अणु
			safe_to_हटाओ = false;
		पूर्ण
	पूर्ण
	वापस safe_to_हटाओ;
पूर्ण

/**
 * kvm_mips_flush_gpa_pt() - Flush a range of guest physical addresses.
 * @kvm:	KVM poपूर्णांकer.
 * @start_gfn:	Guest frame number of first page in GPA range to flush.
 * @end_gfn:	Guest frame number of last page in GPA range to flush.
 *
 * Flushes a range of GPA mappings from the GPA page tables.
 *
 * The caller must hold the @kvm->mmu_lock spinlock.
 *
 * Returns:	Whether its safe to हटाओ the top level page directory because
 *		all lower levels have been हटाओd.
 */
bool kvm_mips_flush_gpa_pt(काष्ठा kvm *kvm, gfn_t start_gfn, gfn_t end_gfn)
अणु
	वापस kvm_mips_flush_gpa_pgd(kvm->arch.gpa_mm.pgd,
				      start_gfn << PAGE_SHIFT,
				      end_gfn << PAGE_SHIFT);
पूर्ण

#घोषणा BUILD_PTE_RANGE_OP(name, op)					\
अटल पूर्णांक kvm_mips_##name##_pte(pte_t *pte, अचिन्हित दीर्घ start,	\
				 अचिन्हित दीर्घ end)			\
अणु									\
	पूर्णांक ret = 0;							\
	पूर्णांक i_min = pte_index(start);				\
	पूर्णांक i_max = pte_index(end);					\
	पूर्णांक i;								\
	pte_t old, new;							\
									\
	क्रम (i = i_min; i <= i_max; ++i) अणु				\
		अगर (!pte_present(pte[i]))				\
			जारी;					\
									\
		old = pte[i];						\
		new = op(old);						\
		अगर (pte_val(new) == pte_val(old))			\
			जारी;					\
		set_pte(pte + i, new);					\
		ret = 1;						\
	पूर्ण								\
	वापस ret;							\
पूर्ण									\
									\
/* वापसs true अगर anything was करोne */					\
अटल पूर्णांक kvm_mips_##name##_pmd(pmd_t *pmd, अचिन्हित दीर्घ start,	\
				 अचिन्हित दीर्घ end)			\
अणु									\
	पूर्णांक ret = 0;							\
	pte_t *pte;							\
	अचिन्हित दीर्घ cur_end = ~0ul;					\
	पूर्णांक i_min = pmd_index(start);				\
	पूर्णांक i_max = pmd_index(end);					\
	पूर्णांक i;								\
									\
	क्रम (i = i_min; i <= i_max; ++i, start = 0) अणु			\
		अगर (!pmd_present(pmd[i]))				\
			जारी;					\
									\
		pte = pte_offset_kernel(pmd + i, 0);				\
		अगर (i == i_max)						\
			cur_end = end;					\
									\
		ret |= kvm_mips_##name##_pte(pte, start, cur_end);	\
	पूर्ण								\
	वापस ret;							\
पूर्ण									\
									\
अटल पूर्णांक kvm_mips_##name##_pud(pud_t *pud, अचिन्हित दीर्घ start,	\
				 अचिन्हित दीर्घ end)			\
अणु									\
	पूर्णांक ret = 0;							\
	pmd_t *pmd;							\
	अचिन्हित दीर्घ cur_end = ~0ul;					\
	पूर्णांक i_min = pud_index(start);				\
	पूर्णांक i_max = pud_index(end);					\
	पूर्णांक i;								\
									\
	क्रम (i = i_min; i <= i_max; ++i, start = 0) अणु			\
		अगर (!pud_present(pud[i]))				\
			जारी;					\
									\
		pmd = pmd_offset(pud + i, 0);				\
		अगर (i == i_max)						\
			cur_end = end;					\
									\
		ret |= kvm_mips_##name##_pmd(pmd, start, cur_end);	\
	पूर्ण								\
	वापस ret;							\
पूर्ण									\
									\
अटल पूर्णांक kvm_mips_##name##_pgd(pgd_t *pgd, अचिन्हित दीर्घ start,	\
				 अचिन्हित दीर्घ end)			\
अणु									\
	पूर्णांक ret = 0;							\
	p4d_t *p4d;							\
	pud_t *pud;							\
	अचिन्हित दीर्घ cur_end = ~0ul;					\
	पूर्णांक i_min = pgd_index(start);					\
	पूर्णांक i_max = pgd_index(end);					\
	पूर्णांक i;								\
									\
	क्रम (i = i_min; i <= i_max; ++i, start = 0) अणु			\
		अगर (!pgd_present(pgd[i]))				\
			जारी;					\
									\
		p4d = p4d_offset(pgd, 0);				\
		pud = pud_offset(p4d + i, 0);				\
		अगर (i == i_max)						\
			cur_end = end;					\
									\
		ret |= kvm_mips_##name##_pud(pud, start, cur_end);	\
	पूर्ण								\
	वापस ret;							\
पूर्ण

/*
 * kvm_mips_mkclean_gpa_pt.
 * Mark a range of guest physical address space clean (ग_लिखोs fault) in the VM's
 * GPA page table to allow dirty page tracking.
 */

BUILD_PTE_RANGE_OP(mkclean, pte_mkclean)

/**
 * kvm_mips_mkclean_gpa_pt() - Make a range of guest physical addresses clean.
 * @kvm:	KVM poपूर्णांकer.
 * @start_gfn:	Guest frame number of first page in GPA range to flush.
 * @end_gfn:	Guest frame number of last page in GPA range to flush.
 *
 * Make a range of GPA mappings clean so that guest ग_लिखोs will fault and
 * trigger dirty page logging.
 *
 * The caller must hold the @kvm->mmu_lock spinlock.
 *
 * Returns:	Whether any GPA mappings were modअगरied, which would require
 *		derived mappings (GVA page tables & TLB enties) to be
 *		invalidated.
 */
पूर्णांक kvm_mips_mkclean_gpa_pt(काष्ठा kvm *kvm, gfn_t start_gfn, gfn_t end_gfn)
अणु
	वापस kvm_mips_mkclean_pgd(kvm->arch.gpa_mm.pgd,
				    start_gfn << PAGE_SHIFT,
				    end_gfn << PAGE_SHIFT);
पूर्ण

/**
 * kvm_arch_mmu_enable_log_dirty_pt_masked() - ग_लिखो protect dirty pages
 * @kvm:	The KVM poपूर्णांकer
 * @slot:	The memory slot associated with mask
 * @gfn_offset:	The gfn offset in memory slot
 * @mask:	The mask of dirty pages at offset 'gfn_offset' in this memory
 *		slot to be ग_लिखो रक्षित
 *
 * Walks bits set in mask ग_लिखो protects the associated pte's. Caller must
 * acquire @kvm->mmu_lock.
 */
व्योम kvm_arch_mmu_enable_log_dirty_pt_masked(काष्ठा kvm *kvm,
		काष्ठा kvm_memory_slot *slot,
		gfn_t gfn_offset, अचिन्हित दीर्घ mask)
अणु
	gfn_t base_gfn = slot->base_gfn + gfn_offset;
	gfn_t start = base_gfn +  __ffs(mask);
	gfn_t end = base_gfn + __fls(mask);

	kvm_mips_mkclean_gpa_pt(kvm, start, end);
पूर्ण

/*
 * kvm_mips_mkold_gpa_pt.
 * Mark a range of guest physical address space old (all accesses fault) in the
 * VM's GPA page table to allow detection of commonly used pages.
 */

BUILD_PTE_RANGE_OP(mkold, pte_mkold)

अटल पूर्णांक kvm_mips_mkold_gpa_pt(काष्ठा kvm *kvm, gfn_t start_gfn,
				 gfn_t end_gfn)
अणु
	वापस kvm_mips_mkold_pgd(kvm->arch.gpa_mm.pgd,
				  start_gfn << PAGE_SHIFT,
				  end_gfn << PAGE_SHIFT);
पूर्ण

bool kvm_unmap_gfn_range(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	kvm_mips_flush_gpa_pt(kvm, range->start, range->end);
	वापस 1;
पूर्ण

bool kvm_set_spte_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	gpa_t gpa = range->start << PAGE_SHIFT;
	pte_t hva_pte = range->pte;
	pte_t *gpa_pte = kvm_mips_pte_क्रम_gpa(kvm, शून्य, gpa);
	pte_t old_pte;

	अगर (!gpa_pte)
		वापस false;

	/* Mapping may need adjusting depending on memslot flags */
	old_pte = *gpa_pte;
	अगर (range->slot->flags & KVM_MEM_LOG_सूचीTY_PAGES && !pte_dirty(old_pte))
		hva_pte = pte_mkclean(hva_pte);
	अन्यथा अगर (range->slot->flags & KVM_MEM_READONLY)
		hva_pte = pte_wrprotect(hva_pte);

	set_pte(gpa_pte, hva_pte);

	/* Replacing an असलent or old page करोesn't need flushes */
	अगर (!pte_present(old_pte) || !pte_young(old_pte))
		वापस false;

	/* Pages swapped, aged, moved, or cleaned require flushes */
	वापस !pte_present(hva_pte) ||
	       !pte_young(hva_pte) ||
	       pte_pfn(old_pte) != pte_pfn(hva_pte) ||
	       (pte_dirty(old_pte) && !pte_dirty(hva_pte));
पूर्ण

bool kvm_age_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	वापस kvm_mips_mkold_gpa_pt(kvm, range->start, range->end);
पूर्ण

bool kvm_test_age_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	gpa_t gpa = range->start << PAGE_SHIFT;
	pte_t *gpa_pte = kvm_mips_pte_क्रम_gpa(kvm, शून्य, gpa);

	अगर (!gpa_pte)
		वापस 0;
	वापस pte_young(*gpa_pte);
पूर्ण

/**
 * _kvm_mips_map_page_fast() - Fast path GPA fault handler.
 * @vcpu:		VCPU poपूर्णांकer.
 * @gpa:		Guest physical address of fault.
 * @ग_लिखो_fault:	Whether the fault was due to a ग_लिखो.
 * @out_entry:		New PTE क्रम @gpa (written on success unless शून्य).
 * @out_buddy:		New PTE क्रम @gpa's buddy (written on success unless
 *			शून्य).
 *
 * Perक्रमm fast path GPA fault handling, करोing all that can be करोne without
 * calling पूर्णांकo KVM. This handles marking old pages young (क्रम idle page
 * tracking), and dirtying of clean pages (क्रम dirty page logging).
 *
 * Returns:	0 on success, in which हाल we can update derived mappings and
 *		resume guest execution.
 *		-EFAULT on failure due to असलent GPA mapping or ग_लिखो to
 *		पढ़ो-only page, in which हाल KVM must be consulted.
 */
अटल पूर्णांक _kvm_mips_map_page_fast(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gpa,
				   bool ग_लिखो_fault,
				   pte_t *out_entry, pte_t *out_buddy)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	gfn_t gfn = gpa >> PAGE_SHIFT;
	pte_t *ptep;
	kvm_pfn_t pfn = 0;	/* silence bogus GCC warning */
	bool pfn_valid = false;
	पूर्णांक ret = 0;

	spin_lock(&kvm->mmu_lock);

	/* Fast path - just check GPA page table क्रम an existing entry */
	ptep = kvm_mips_pte_क्रम_gpa(kvm, शून्य, gpa);
	अगर (!ptep || !pte_present(*ptep)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	/* Track access to pages marked old */
	अगर (!pte_young(*ptep)) अणु
		set_pte(ptep, pte_mkyoung(*ptep));
		pfn = pte_pfn(*ptep);
		pfn_valid = true;
		/* call kvm_set_pfn_accessed() after unlock */
	पूर्ण
	अगर (ग_लिखो_fault && !pte_dirty(*ptep)) अणु
		अगर (!pte_ग_लिखो(*ptep)) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण

		/* Track dirtying of ग_लिखोable pages */
		set_pte(ptep, pte_सूची_गढ़ोty(*ptep));
		pfn = pte_pfn(*ptep);
		mark_page_dirty(kvm, gfn);
		kvm_set_pfn_dirty(pfn);
	पूर्ण

	अगर (out_entry)
		*out_entry = *ptep;
	अगर (out_buddy)
		*out_buddy = *ptep_buddy(ptep);

out:
	spin_unlock(&kvm->mmu_lock);
	अगर (pfn_valid)
		kvm_set_pfn_accessed(pfn);
	वापस ret;
पूर्ण

/**
 * kvm_mips_map_page() - Map a guest physical page.
 * @vcpu:		VCPU poपूर्णांकer.
 * @gpa:		Guest physical address of fault.
 * @ग_लिखो_fault:	Whether the fault was due to a ग_लिखो.
 * @out_entry:		New PTE क्रम @gpa (written on success unless शून्य).
 * @out_buddy:		New PTE क्रम @gpa's buddy (written on success unless
 *			शून्य).
 *
 * Handle GPA faults by creating a new GPA mapping (or updating an existing
 * one).
 *
 * This takes care of marking pages young or dirty (idle/dirty page tracking),
 * asking KVM क्रम the corresponding PFN, and creating a mapping in the GPA page
 * tables. Derived mappings (GVA page tables and TLBs) must be handled by the
 * caller.
 *
 * Returns:	0 on success, in which हाल the caller may use the @out_entry
 *		and @out_buddy PTEs to update derived mappings and resume guest
 *		execution.
 *		-EFAULT अगर there is no memory region at @gpa or a ग_लिखो was
 *		attempted to a पढ़ो-only memory region. This is usually handled
 *		as an MMIO access.
 */
अटल पूर्णांक kvm_mips_map_page(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gpa,
			     bool ग_लिखो_fault,
			     pte_t *out_entry, pte_t *out_buddy)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvm_mmu_memory_cache *memcache = &vcpu->arch.mmu_page_cache;
	gfn_t gfn = gpa >> PAGE_SHIFT;
	पूर्णांक srcu_idx, err;
	kvm_pfn_t pfn;
	pte_t *ptep, entry, old_pte;
	bool ग_लिखोable;
	अचिन्हित दीर्घ prot_bits;
	अचिन्हित दीर्घ mmu_seq;

	/* Try the fast path to handle old / clean pages */
	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
	err = _kvm_mips_map_page_fast(vcpu, gpa, ग_लिखो_fault, out_entry,
				      out_buddy);
	अगर (!err)
		जाओ out;

	/* We need a minimum of cached pages पढ़ोy क्रम page table creation */
	err = kvm_mmu_topup_memory_cache(memcache, KVM_MMU_CACHE_MIN_PAGES);
	अगर (err)
		जाओ out;

retry:
	/*
	 * Used to check क्रम invalidations in progress, of the pfn that is
	 * वापसed by pfn_to_pfn_prot below.
	 */
	mmu_seq = kvm->mmu_notअगरier_seq;
	/*
	 * Ensure the पढ़ो of mmu_notअगरier_seq isn't reordered with PTE पढ़ोs in
	 * gfn_to_pfn_prot() (which calls get_user_pages()), so that we करोn't
	 * risk the page we get a reference to getting unmapped beक्रमe we have a
	 * chance to grab the mmu_lock without mmu_notअगरier_retry() noticing.
	 *
	 * This smp_rmb() pairs with the effective smp_wmb() of the combination
	 * of the pte_unmap_unlock() after the PTE is zapped, and the
	 * spin_lock() in kvm_mmu_notअगरier_invalidate_<page|range_end>() beक्रमe
	 * mmu_notअगरier_seq is incremented.
	 */
	smp_rmb();

	/* Slow path - ask KVM core whether we can access this GPA */
	pfn = gfn_to_pfn_prot(kvm, gfn, ग_लिखो_fault, &ग_लिखोable);
	अगर (is_error_noslot_pfn(pfn)) अणु
		err = -EFAULT;
		जाओ out;
	पूर्ण

	spin_lock(&kvm->mmu_lock);
	/* Check अगर an invalidation has taken place since we got pfn */
	अगर (mmu_notअगरier_retry(kvm, mmu_seq)) अणु
		/*
		 * This can happen when mappings are changed asynchronously, but
		 * also synchronously अगर a COW is triggered by
		 * gfn_to_pfn_prot().
		 */
		spin_unlock(&kvm->mmu_lock);
		kvm_release_pfn_clean(pfn);
		जाओ retry;
	पूर्ण

	/* Ensure page tables are allocated */
	ptep = kvm_mips_pte_क्रम_gpa(kvm, memcache, gpa);

	/* Set up the PTE */
	prot_bits = _PAGE_PRESENT | __READABLE | _page_cachable_शेष;
	अगर (ग_लिखोable) अणु
		prot_bits |= _PAGE_WRITE;
		अगर (ग_लिखो_fault) अणु
			prot_bits |= __WRITEABLE;
			mark_page_dirty(kvm, gfn);
			kvm_set_pfn_dirty(pfn);
		पूर्ण
	पूर्ण
	entry = pfn_pte(pfn, __pgprot(prot_bits));

	/* Write the PTE */
	old_pte = *ptep;
	set_pte(ptep, entry);

	err = 0;
	अगर (out_entry)
		*out_entry = *ptep;
	अगर (out_buddy)
		*out_buddy = *ptep_buddy(ptep);

	spin_unlock(&kvm->mmu_lock);
	kvm_release_pfn_clean(pfn);
	kvm_set_pfn_accessed(pfn);
out:
	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
	वापस err;
पूर्ण

पूर्णांक kvm_mips_handle_vz_root_tlb_fault(अचिन्हित दीर्घ badvaddr,
				      काष्ठा kvm_vcpu *vcpu,
				      bool ग_लिखो_fault)
अणु
	पूर्णांक ret;

	ret = kvm_mips_map_page(vcpu, badvaddr, ग_लिखो_fault, शून्य, शून्य);
	अगर (ret)
		वापस ret;

	/* Invalidate this entry in the TLB */
	वापस kvm_vz_host_tlb_inv(vcpu, badvaddr);
पूर्ण

/**
 * kvm_mips_migrate_count() - Migrate समयr.
 * @vcpu:	Virtual CPU.
 *
 * Migrate CP0_Count hrसमयr to the current CPU by cancelling and restarting it
 * अगर it was running prior to being cancelled.
 *
 * Must be called when the VCPU is migrated to a dअगरferent CPU to ensure that
 * समयr expiry during guest execution पूर्णांकerrupts the guest and causes the
 * पूर्णांकerrupt to be delivered in a समयly manner.
 */
अटल व्योम kvm_mips_migrate_count(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (hrसमयr_cancel(&vcpu->arch.comparecount_समयr))
		hrसमयr_restart(&vcpu->arch.comparecount_समयr);
पूर्ण

/* Restore ASID once we are scheduled back after preemption */
व्योम kvm_arch_vcpu_load(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ flags;

	kvm_debug("%s: vcpu %p, cpu: %d\n", __func__, vcpu, cpu);

	local_irq_save(flags);

	vcpu->cpu = cpu;
	अगर (vcpu->arch.last_sched_cpu != cpu) अणु
		kvm_debug("[%d->%d]KVM VCPU[%d] switch\n",
			  vcpu->arch.last_sched_cpu, cpu, vcpu->vcpu_id);
		/*
		 * Migrate the समयr पूर्णांकerrupt to the current CPU so that it
		 * always पूर्णांकerrupts the guest and synchronously triggers a
		 * guest समयr पूर्णांकerrupt.
		 */
		kvm_mips_migrate_count(vcpu);
	पूर्ण

	/* restore guest state to रेजिस्टरs */
	kvm_mips_callbacks->vcpu_load(vcpu, cpu);

	local_irq_restore(flags);
पूर्ण

/* ASID can change अगर another task is scheduled during preemption */
व्योम kvm_arch_vcpu_put(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक cpu;

	local_irq_save(flags);

	cpu = smp_processor_id();
	vcpu->arch.last_sched_cpu = cpu;
	vcpu->cpu = -1;

	/* save guest state in रेजिस्टरs */
	kvm_mips_callbacks->vcpu_put(vcpu, cpu);

	local_irq_restore(flags);
पूर्ण
