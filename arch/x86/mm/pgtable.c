<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/mm.h>
#समावेश <linux/gfp.h>
#समावेश <linux/hugetlb.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/mtrr.h>

#अगर_घोषित CONFIG_DYNAMIC_PHYSICAL_MASK
phys_addr_t physical_mask __ro_after_init = (1ULL << __PHYSICAL_MASK_SHIFT) - 1;
EXPORT_SYMBOL(physical_mask);
#पूर्ण_अगर

#अगर_घोषित CONFIG_HIGHPTE
#घोषणा PGTABLE_HIGHMEM __GFP_HIGHMEM
#अन्यथा
#घोषणा PGTABLE_HIGHMEM 0
#पूर्ण_अगर

#अगर_अघोषित CONFIG_PARAVIRT
अटल अंतरभूत
व्योम paravirt_tlb_हटाओ_table(काष्ठा mmu_gather *tlb, व्योम *table)
अणु
	tlb_हटाओ_page(tlb, table);
पूर्ण
#पूर्ण_अगर

gfp_t __userpte_alloc_gfp = GFP_PGTABLE_USER | PGTABLE_HIGHMEM;

pgtable_t pte_alloc_one(काष्ठा mm_काष्ठा *mm)
अणु
	वापस __pte_alloc_one(mm, __userpte_alloc_gfp);
पूर्ण

अटल पूर्णांक __init setup_userpte(अक्षर *arg)
अणु
	अगर (!arg)
		वापस -EINVAL;

	/*
	 * "userpte=nohigh" disables allocation of user pagetables in
	 * high memory.
	 */
	अगर (म_भेद(arg, "nohigh") == 0)
		__userpte_alloc_gfp &= ~__GFP_HIGHMEM;
	अन्यथा
		वापस -EINVAL;
	वापस 0;
पूर्ण
early_param("userpte", setup_userpte);

व्योम ___pte_मुक्त_tlb(काष्ठा mmu_gather *tlb, काष्ठा page *pte)
अणु
	pgtable_pte_page_dtor(pte);
	paravirt_release_pte(page_to_pfn(pte));
	paravirt_tlb_हटाओ_table(tlb, pte);
पूर्ण

#अगर CONFIG_PGTABLE_LEVELS > 2
व्योम ___pmd_मुक्त_tlb(काष्ठा mmu_gather *tlb, pmd_t *pmd)
अणु
	काष्ठा page *page = virt_to_page(pmd);
	paravirt_release_pmd(__pa(pmd) >> PAGE_SHIFT);
	/*
	 * NOTE! For PAE, any changes to the top page-directory-poपूर्णांकer-table
	 * entries need a full cr3 reload to flush.
	 */
#अगर_घोषित CONFIG_X86_PAE
	tlb->need_flush_all = 1;
#पूर्ण_अगर
	pgtable_pmd_page_dtor(page);
	paravirt_tlb_हटाओ_table(tlb, page);
पूर्ण

#अगर CONFIG_PGTABLE_LEVELS > 3
व्योम ___pud_मुक्त_tlb(काष्ठा mmu_gather *tlb, pud_t *pud)
अणु
	paravirt_release_pud(__pa(pud) >> PAGE_SHIFT);
	paravirt_tlb_हटाओ_table(tlb, virt_to_page(pud));
पूर्ण

#अगर CONFIG_PGTABLE_LEVELS > 4
व्योम ___p4d_मुक्त_tlb(काष्ठा mmu_gather *tlb, p4d_t *p4d)
अणु
	paravirt_release_p4d(__pa(p4d) >> PAGE_SHIFT);
	paravirt_tlb_हटाओ_table(tlb, virt_to_page(p4d));
पूर्ण
#पूर्ण_अगर	/* CONFIG_PGTABLE_LEVELS > 4 */
#पूर्ण_अगर	/* CONFIG_PGTABLE_LEVELS > 3 */
#पूर्ण_अगर	/* CONFIG_PGTABLE_LEVELS > 2 */

अटल अंतरभूत व्योम pgd_list_add(pgd_t *pgd)
अणु
	काष्ठा page *page = virt_to_page(pgd);

	list_add(&page->lru, &pgd_list);
पूर्ण

अटल अंतरभूत व्योम pgd_list_del(pgd_t *pgd)
अणु
	काष्ठा page *page = virt_to_page(pgd);

	list_del(&page->lru);
पूर्ण

#घोषणा UNSHARED_PTRS_PER_PGD				\
	(SHARED_KERNEL_PMD ? KERNEL_PGD_BOUNDARY : PTRS_PER_PGD)
#घोषणा MAX_UNSHARED_PTRS_PER_PGD			\
	max_t(माप_प्रकार, KERNEL_PGD_BOUNDARY, PTRS_PER_PGD)


अटल व्योम pgd_set_mm(pgd_t *pgd, काष्ठा mm_काष्ठा *mm)
अणु
	virt_to_page(pgd)->pt_mm = mm;
पूर्ण

काष्ठा mm_काष्ठा *pgd_page_get_mm(काष्ठा page *page)
अणु
	वापस page->pt_mm;
पूर्ण

अटल व्योम pgd_ctor(काष्ठा mm_काष्ठा *mm, pgd_t *pgd)
अणु
	/* If the pgd poपूर्णांकs to a shared pagetable level (either the
	   ptes in non-PAE, or shared PMD in PAE), then just copy the
	   references from swapper_pg_dir. */
	अगर (CONFIG_PGTABLE_LEVELS == 2 ||
	    (CONFIG_PGTABLE_LEVELS == 3 && SHARED_KERNEL_PMD) ||
	    CONFIG_PGTABLE_LEVELS >= 4) अणु
		clone_pgd_range(pgd + KERNEL_PGD_BOUNDARY,
				swapper_pg_dir + KERNEL_PGD_BOUNDARY,
				KERNEL_PGD_PTRS);
	पूर्ण

	/* list required to sync kernel mapping updates */
	अगर (!SHARED_KERNEL_PMD) अणु
		pgd_set_mm(pgd, mm);
		pgd_list_add(pgd);
	पूर्ण
पूर्ण

अटल व्योम pgd_dtor(pgd_t *pgd)
अणु
	अगर (SHARED_KERNEL_PMD)
		वापस;

	spin_lock(&pgd_lock);
	pgd_list_del(pgd);
	spin_unlock(&pgd_lock);
पूर्ण

/*
 * List of all pgd's needed क्रम non-PAE so it can invalidate entries
 * in both cached and uncached pgd's; not needed क्रम PAE since the
 * kernel pmd is shared. If PAE were not to share the pmd a similar
 * tactic would be needed. This is essentially codepath-based locking
 * against pageattr.c; it is the unique हाल in which a valid change
 * of kernel pagetables can't be lazily synchronized by vदो_स्मृति faults.
 * vदो_स्मृति faults work because attached pagetables are never मुक्तd.
 * -- nyc
 */

#अगर_घोषित CONFIG_X86_PAE
/*
 * In PAE mode, we need to करो a cr3 reload (=tlb flush) when
 * updating the top-level pagetable entries to guarantee the
 * processor notices the update.  Since this is expensive, and
 * all 4 top-level entries are used almost immediately in a
 * new process's lअगरe, we just pre-populate them here.
 *
 * Also, अगर we're in a paravirt environment where the kernel pmd is
 * not shared between pagetables (!SHARED_KERNEL_PMDS), we allocate
 * and initialize the kernel pmds here.
 */
#घोषणा PREALLOCATED_PMDS	UNSHARED_PTRS_PER_PGD
#घोषणा MAX_PREALLOCATED_PMDS	MAX_UNSHARED_PTRS_PER_PGD

/*
 * We allocate separate PMDs क्रम the kernel part of the user page-table
 * when PTI is enabled. We need them to map the per-process LDT पूर्णांकo the
 * user-space page-table.
 */
#घोषणा PREALLOCATED_USER_PMDS	 (boot_cpu_has(X86_FEATURE_PTI) ? \
					KERNEL_PGD_PTRS : 0)
#घोषणा MAX_PREALLOCATED_USER_PMDS KERNEL_PGD_PTRS

व्योम pud_populate(काष्ठा mm_काष्ठा *mm, pud_t *pudp, pmd_t *pmd)
अणु
	paravirt_alloc_pmd(mm, __pa(pmd) >> PAGE_SHIFT);

	/* Note: almost everything apart from _PAGE_PRESENT is
	   reserved at the pmd (PDPT) level. */
	set_pud(pudp, __pud(__pa(pmd) | _PAGE_PRESENT));

	/*
	 * According to Intel App note "TLBs, Paging-Structure Caches,
	 * and Their Invalidation", April 2007, करोcument 317080-001,
	 * section 8.1: in PAE mode we explicitly have to flush the
	 * TLB via cr3 अगर the top-level pgd is changed...
	 */
	flush_tlb_mm(mm);
पूर्ण
#अन्यथा  /* !CONFIG_X86_PAE */

/* No need to prepopulate any pagetable entries in non-PAE modes. */
#घोषणा PREALLOCATED_PMDS	0
#घोषणा MAX_PREALLOCATED_PMDS	0
#घोषणा PREALLOCATED_USER_PMDS	 0
#घोषणा MAX_PREALLOCATED_USER_PMDS 0
#पूर्ण_अगर	/* CONFIG_X86_PAE */

अटल व्योम मुक्त_pmds(काष्ठा mm_काष्ठा *mm, pmd_t *pmds[], पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		अगर (pmds[i]) अणु
			pgtable_pmd_page_dtor(virt_to_page(pmds[i]));
			मुक्त_page((अचिन्हित दीर्घ)pmds[i]);
			mm_dec_nr_pmds(mm);
		पूर्ण
पूर्ण

अटल पूर्णांक pपुनः_स्मृतिate_pmds(काष्ठा mm_काष्ठा *mm, pmd_t *pmds[], पूर्णांक count)
अणु
	पूर्णांक i;
	bool failed = false;
	gfp_t gfp = GFP_PGTABLE_USER;

	अगर (mm == &init_mm)
		gfp &= ~__GFP_ACCOUNT;

	क्रम (i = 0; i < count; i++) अणु
		pmd_t *pmd = (pmd_t *)__get_मुक्त_page(gfp);
		अगर (!pmd)
			failed = true;
		अगर (pmd && !pgtable_pmd_page_ctor(virt_to_page(pmd))) अणु
			मुक्त_page((अचिन्हित दीर्घ)pmd);
			pmd = शून्य;
			failed = true;
		पूर्ण
		अगर (pmd)
			mm_inc_nr_pmds(mm);
		pmds[i] = pmd;
	पूर्ण

	अगर (failed) अणु
		मुक्त_pmds(mm, pmds, count);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Mop up any pmd pages which may still be attached to the pgd.
 * Normally they will be मुक्तd by munmap/निकास_mmap, but any pmd we
 * pपुनः_स्मृतिate which never got a corresponding vma will need to be
 * मुक्तd manually.
 */
अटल व्योम mop_up_one_pmd(काष्ठा mm_काष्ठा *mm, pgd_t *pgdp)
अणु
	pgd_t pgd = *pgdp;

	अगर (pgd_val(pgd) != 0) अणु
		pmd_t *pmd = (pmd_t *)pgd_page_vaddr(pgd);

		pgd_clear(pgdp);

		paravirt_release_pmd(pgd_val(pgd) >> PAGE_SHIFT);
		pmd_मुक्त(mm, pmd);
		mm_dec_nr_pmds(mm);
	पूर्ण
पूर्ण

अटल व्योम pgd_mop_up_pmds(काष्ठा mm_काष्ठा *mm, pgd_t *pgdp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PREALLOCATED_PMDS; i++)
		mop_up_one_pmd(mm, &pgdp[i]);

#अगर_घोषित CONFIG_PAGE_TABLE_ISOLATION

	अगर (!boot_cpu_has(X86_FEATURE_PTI))
		वापस;

	pgdp = kernel_to_user_pgdp(pgdp);

	क्रम (i = 0; i < PREALLOCATED_USER_PMDS; i++)
		mop_up_one_pmd(mm, &pgdp[i + KERNEL_PGD_BOUNDARY]);
#पूर्ण_अगर
पूर्ण

अटल व्योम pgd_prepopulate_pmd(काष्ठा mm_काष्ठा *mm, pgd_t *pgd, pmd_t *pmds[])
अणु
	p4d_t *p4d;
	pud_t *pud;
	पूर्णांक i;

	अगर (PREALLOCATED_PMDS == 0) /* Work around gcc-3.4.x bug */
		वापस;

	p4d = p4d_offset(pgd, 0);
	pud = pud_offset(p4d, 0);

	क्रम (i = 0; i < PREALLOCATED_PMDS; i++, pud++) अणु
		pmd_t *pmd = pmds[i];

		अगर (i >= KERNEL_PGD_BOUNDARY)
			स_नकल(pmd, (pmd_t *)pgd_page_vaddr(swapper_pg_dir[i]),
			       माप(pmd_t) * PTRS_PER_PMD);

		pud_populate(mm, pud, pmd);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PAGE_TABLE_ISOLATION
अटल व्योम pgd_prepopulate_user_pmd(काष्ठा mm_काष्ठा *mm,
				     pgd_t *k_pgd, pmd_t *pmds[])
अणु
	pgd_t *s_pgd = kernel_to_user_pgdp(swapper_pg_dir);
	pgd_t *u_pgd = kernel_to_user_pgdp(k_pgd);
	p4d_t *u_p4d;
	pud_t *u_pud;
	पूर्णांक i;

	u_p4d = p4d_offset(u_pgd, 0);
	u_pud = pud_offset(u_p4d, 0);

	s_pgd += KERNEL_PGD_BOUNDARY;
	u_pud += KERNEL_PGD_BOUNDARY;

	क्रम (i = 0; i < PREALLOCATED_USER_PMDS; i++, u_pud++, s_pgd++) अणु
		pmd_t *pmd = pmds[i];

		स_नकल(pmd, (pmd_t *)pgd_page_vaddr(*s_pgd),
		       माप(pmd_t) * PTRS_PER_PMD);

		pud_populate(mm, u_pud, pmd);
	पूर्ण

पूर्ण
#अन्यथा
अटल व्योम pgd_prepopulate_user_pmd(काष्ठा mm_काष्ठा *mm,
				     pgd_t *k_pgd, pmd_t *pmds[])
अणु
पूर्ण
#पूर्ण_अगर
/*
 * Xen paravirt assumes pgd table should be in one page. 64 bit kernel also
 * assumes that pgd should be in one page.
 *
 * But kernel with PAE paging that is not running as a Xen करोमुख्य
 * only needs to allocate 32 bytes क्रम pgd instead of one page.
 */
#अगर_घोषित CONFIG_X86_PAE

#समावेश <linux/slab.h>

#घोषणा PGD_SIZE	(PTRS_PER_PGD * माप(pgd_t))
#घोषणा PGD_ALIGN	32

अटल काष्ठा kmem_cache *pgd_cache;

व्योम __init pgtable_cache_init(व्योम)
अणु
	/*
	 * When PAE kernel is running as a Xen करोमुख्य, it करोes not use
	 * shared kernel pmd. And this requires a whole page क्रम pgd.
	 */
	अगर (!SHARED_KERNEL_PMD)
		वापस;

	/*
	 * when PAE kernel is not running as a Xen करोमुख्य, it uses
	 * shared kernel pmd. Shared kernel pmd करोes not require a whole
	 * page क्रम pgd. We are able to just allocate a 32-byte क्रम pgd.
	 * During boot समय, we create a 32-byte slab क्रम pgd table allocation.
	 */
	pgd_cache = kmem_cache_create("pgd_cache", PGD_SIZE, PGD_ALIGN,
				      SLAB_PANIC, शून्य);
पूर्ण

अटल अंतरभूत pgd_t *_pgd_alloc(व्योम)
अणु
	/*
	 * If no SHARED_KERNEL_PMD, PAE kernel is running as a Xen करोमुख्य.
	 * We allocate one page क्रम pgd.
	 */
	अगर (!SHARED_KERNEL_PMD)
		वापस (pgd_t *)__get_मुक्त_pages(GFP_PGTABLE_USER,
						 PGD_ALLOCATION_ORDER);

	/*
	 * Now PAE kernel is not running as a Xen करोमुख्य. We can allocate
	 * a 32-byte slab क्रम pgd to save memory space.
	 */
	वापस kmem_cache_alloc(pgd_cache, GFP_PGTABLE_USER);
पूर्ण

अटल अंतरभूत व्योम _pgd_मुक्त(pgd_t *pgd)
अणु
	अगर (!SHARED_KERNEL_PMD)
		मुक्त_pages((अचिन्हित दीर्घ)pgd, PGD_ALLOCATION_ORDER);
	अन्यथा
		kmem_cache_मुक्त(pgd_cache, pgd);
पूर्ण
#अन्यथा

अटल अंतरभूत pgd_t *_pgd_alloc(व्योम)
अणु
	वापस (pgd_t *)__get_मुक्त_pages(GFP_PGTABLE_USER,
					 PGD_ALLOCATION_ORDER);
पूर्ण

अटल अंतरभूत व्योम _pgd_मुक्त(pgd_t *pgd)
अणु
	मुक्त_pages((अचिन्हित दीर्घ)pgd, PGD_ALLOCATION_ORDER);
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_PAE */

pgd_t *pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	pgd_t *pgd;
	pmd_t *u_pmds[MAX_PREALLOCATED_USER_PMDS];
	pmd_t *pmds[MAX_PREALLOCATED_PMDS];

	pgd = _pgd_alloc();

	अगर (pgd == शून्य)
		जाओ out;

	mm->pgd = pgd;

	अगर (pपुनः_स्मृतिate_pmds(mm, pmds, PREALLOCATED_PMDS) != 0)
		जाओ out_मुक्त_pgd;

	अगर (pपुनः_स्मृतिate_pmds(mm, u_pmds, PREALLOCATED_USER_PMDS) != 0)
		जाओ out_मुक्त_pmds;

	अगर (paravirt_pgd_alloc(mm) != 0)
		जाओ out_मुक्त_user_pmds;

	/*
	 * Make sure that pre-populating the pmds is atomic with
	 * respect to anything walking the pgd_list, so that they
	 * never see a partially populated pgd.
	 */
	spin_lock(&pgd_lock);

	pgd_ctor(mm, pgd);
	pgd_prepopulate_pmd(mm, pgd, pmds);
	pgd_prepopulate_user_pmd(mm, pgd, u_pmds);

	spin_unlock(&pgd_lock);

	वापस pgd;

out_मुक्त_user_pmds:
	मुक्त_pmds(mm, u_pmds, PREALLOCATED_USER_PMDS);
out_मुक्त_pmds:
	मुक्त_pmds(mm, pmds, PREALLOCATED_PMDS);
out_मुक्त_pgd:
	_pgd_मुक्त(pgd);
out:
	वापस शून्य;
पूर्ण

व्योम pgd_मुक्त(काष्ठा mm_काष्ठा *mm, pgd_t *pgd)
अणु
	pgd_mop_up_pmds(mm, pgd);
	pgd_dtor(pgd);
	paravirt_pgd_मुक्त(mm, pgd);
	_pgd_मुक्त(pgd);
पूर्ण

/*
 * Used to set accessed or dirty bits in the page table entries
 * on other architectures. On x86, the accessed and dirty bits
 * are tracked by hardware. However, करो_wp_page calls this function
 * to also make the pte ग_लिखोable at the same समय the dirty bit is
 * set. In that हाल we करो actually need to ग_लिखो the PTE.
 */
पूर्णांक ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
			  अचिन्हित दीर्घ address, pte_t *ptep,
			  pte_t entry, पूर्णांक dirty)
अणु
	पूर्णांक changed = !pte_same(*ptep, entry);

	अगर (changed && dirty)
		set_pte(ptep, entry);

	वापस changed;
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
पूर्णांक pmdp_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
			  अचिन्हित दीर्घ address, pmd_t *pmdp,
			  pmd_t entry, पूर्णांक dirty)
अणु
	पूर्णांक changed = !pmd_same(*pmdp, entry);

	VM_BUG_ON(address & ~HPAGE_PMD_MASK);

	अगर (changed && dirty) अणु
		set_pmd(pmdp, entry);
		/*
		 * We had a ग_लिखो-protection fault here and changed the pmd
		 * to to more permissive. No need to flush the TLB क्रम that,
		 * #PF is architecturally guaranteed to करो that and in the
		 * worst-हाल we'll generate a spurious fault.
		 */
	पूर्ण

	वापस changed;
पूर्ण

पूर्णांक pudp_set_access_flags(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
			  pud_t *pudp, pud_t entry, पूर्णांक dirty)
अणु
	पूर्णांक changed = !pud_same(*pudp, entry);

	VM_BUG_ON(address & ~HPAGE_PUD_MASK);

	अगर (changed && dirty) अणु
		set_pud(pudp, entry);
		/*
		 * We had a ग_लिखो-protection fault here and changed the pud
		 * to to more permissive. No need to flush the TLB क्रम that,
		 * #PF is architecturally guaranteed to करो that and in the
		 * worst-हाल we'll generate a spurious fault.
		 */
	पूर्ण

	वापस changed;
पूर्ण
#पूर्ण_अगर

पूर्णांक ptep_test_and_clear_young(काष्ठा vm_area_काष्ठा *vma,
			      अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	पूर्णांक ret = 0;

	अगर (pte_young(*ptep))
		ret = test_and_clear_bit(_PAGE_BIT_ACCESSED,
					 (अचिन्हित दीर्घ *) &ptep->pte);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
पूर्णांक pmdp_test_and_clear_young(काष्ठा vm_area_काष्ठा *vma,
			      अचिन्हित दीर्घ addr, pmd_t *pmdp)
अणु
	पूर्णांक ret = 0;

	अगर (pmd_young(*pmdp))
		ret = test_and_clear_bit(_PAGE_BIT_ACCESSED,
					 (अचिन्हित दीर्घ *)pmdp);

	वापस ret;
पूर्ण
पूर्णांक pudp_test_and_clear_young(काष्ठा vm_area_काष्ठा *vma,
			      अचिन्हित दीर्घ addr, pud_t *pudp)
अणु
	पूर्णांक ret = 0;

	अगर (pud_young(*pudp))
		ret = test_and_clear_bit(_PAGE_BIT_ACCESSED,
					 (अचिन्हित दीर्घ *)pudp);

	वापस ret;
पूर्ण
#पूर्ण_अगर

पूर्णांक ptep_clear_flush_young(काष्ठा vm_area_काष्ठा *vma,
			   अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	/*
	 * On x86 CPUs, clearing the accessed bit without a TLB flush
	 * करोesn't cause data corruption. [ It could cause incorrect
	 * page aging and the (mistaken) reclaim of hot pages, but the
	 * chance of that should be relatively low. ]
	 *
	 * So as a perक्रमmance optimization करोn't flush the TLB when
	 * clearing the accessed bit, it will eventually be flushed by
	 * a context चयन or a VM operation anyway. [ In the rare
	 * event of it not getting flushed क्रम a दीर्घ समय the delay
	 * shouldn't really matter because there's no real memory
	 * pressure क्रम swapout to react to. ]
	 */
	वापस ptep_test_and_clear_young(vma, address, ptep);
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
पूर्णांक pmdp_clear_flush_young(काष्ठा vm_area_काष्ठा *vma,
			   अचिन्हित दीर्घ address, pmd_t *pmdp)
अणु
	पूर्णांक young;

	VM_BUG_ON(address & ~HPAGE_PMD_MASK);

	young = pmdp_test_and_clear_young(vma, address, pmdp);
	अगर (young)
		flush_tlb_range(vma, address, address + HPAGE_PMD_SIZE);

	वापस young;
पूर्ण
#पूर्ण_अगर

/**
 * reserve_top_address - reserves a hole in the top of kernel address space
 * @reserve - size of hole to reserve
 *
 * Can be used to relocate the fixmap area and poke a hole in the top
 * of kernel address space to make room क्रम a hypervisor.
 */
व्योम __init reserve_top_address(अचिन्हित दीर्घ reserve)
अणु
#अगर_घोषित CONFIG_X86_32
	BUG_ON(fixmaps_set > 0);
	__FIXADDR_TOP = round_करोwn(-reserve, 1 << PMD_SHIFT) - PAGE_SIZE;
	prपूर्णांकk(KERN_INFO "Reserving virtual address space above 0x%08lx (rounded to 0x%08lx)\n",
	       -reserve, __FIXADDR_TOP + PAGE_SIZE);
#पूर्ण_अगर
पूर्ण

पूर्णांक fixmaps_set;

व्योम __native_set_fixmap(क्रमागत fixed_addresses idx, pte_t pte)
अणु
	अचिन्हित दीर्घ address = __fix_to_virt(idx);

#अगर_घोषित CONFIG_X86_64
       /*
	* Ensure that the अटल initial page tables are covering the
	* fixmap completely.
	*/
	BUILD_BUG_ON(__end_of_permanent_fixed_addresses >
		     (FIXMAP_PMD_NUM * PTRS_PER_PTE));
#पूर्ण_अगर

	अगर (idx >= __end_of_fixed_addresses) अणु
		BUG();
		वापस;
	पूर्ण
	set_pte_vaddr(address, pte);
	fixmaps_set++;
पूर्ण

व्योम native_set_fixmap(अचिन्हित /* क्रमागत fixed_addresses */ idx,
		       phys_addr_t phys, pgprot_t flags)
अणु
	/* Sanitize 'prot' against any unsupported bits: */
	pgprot_val(flags) &= __शेष_kernel_pte_mask;

	__native_set_fixmap(idx, pfn_pte(phys >> PAGE_SHIFT, flags));
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_HUGE_VMAP
#अगर_घोषित CONFIG_X86_5LEVEL
/**
 * p4d_set_huge - setup kernel P4D mapping
 *
 * No 512GB pages yet -- always वापस 0
 */
पूर्णांक p4d_set_huge(p4d_t *p4d, phys_addr_t addr, pgprot_t prot)
अणु
	वापस 0;
पूर्ण

/**
 * p4d_clear_huge - clear kernel P4D mapping when it is set
 *
 * No 512GB pages yet -- always वापस 0
 */
पूर्णांक p4d_clear_huge(p4d_t *p4d)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/**
 * pud_set_huge - setup kernel PUD mapping
 *
 * MTRRs can override PAT memory types with 4KiB granularity. Thereक्रमe, this
 * function sets up a huge page only अगर any of the following conditions are met:
 *
 * - MTRRs are disabled, or
 *
 * - MTRRs are enabled and the range is completely covered by a single MTRR, or
 *
 * - MTRRs are enabled and the corresponding MTRR memory type is WB, which
 *   has no effect on the requested PAT memory type.
 *
 * Callers should try to decrease page size (1GB -> 2MB -> 4K) अगर the bigger
 * page mapping attempt fails.
 *
 * Returns 1 on success and 0 on failure.
 */
पूर्णांक pud_set_huge(pud_t *pud, phys_addr_t addr, pgprot_t prot)
अणु
	u8 mtrr, unअगरorm;

	mtrr = mtrr_type_lookup(addr, addr + PUD_SIZE, &unअगरorm);
	अगर ((mtrr != MTRR_TYPE_INVALID) && (!unअगरorm) &&
	    (mtrr != MTRR_TYPE_WRBACK))
		वापस 0;

	/* Bail out अगर we are we on a populated non-leaf entry: */
	अगर (pud_present(*pud) && !pud_huge(*pud))
		वापस 0;

	set_pte((pte_t *)pud, pfn_pte(
		(u64)addr >> PAGE_SHIFT,
		__pgprot(protval_4k_2_large(pgprot_val(prot)) | _PAGE_PSE)));

	वापस 1;
पूर्ण

/**
 * pmd_set_huge - setup kernel PMD mapping
 *
 * See text over pud_set_huge() above.
 *
 * Returns 1 on success and 0 on failure.
 */
पूर्णांक pmd_set_huge(pmd_t *pmd, phys_addr_t addr, pgprot_t prot)
अणु
	u8 mtrr, unअगरorm;

	mtrr = mtrr_type_lookup(addr, addr + PMD_SIZE, &unअगरorm);
	अगर ((mtrr != MTRR_TYPE_INVALID) && (!unअगरorm) &&
	    (mtrr != MTRR_TYPE_WRBACK)) अणु
		pr_warn_once("%s: Cannot satisfy [mem %#010llx-%#010llx] with a huge-page mapping due to MTRR override.\n",
			     __func__, addr, addr + PMD_SIZE);
		वापस 0;
	पूर्ण

	/* Bail out अगर we are we on a populated non-leaf entry: */
	अगर (pmd_present(*pmd) && !pmd_huge(*pmd))
		वापस 0;

	set_pte((pte_t *)pmd, pfn_pte(
		(u64)addr >> PAGE_SHIFT,
		__pgprot(protval_4k_2_large(pgprot_val(prot)) | _PAGE_PSE)));

	वापस 1;
पूर्ण

/**
 * pud_clear_huge - clear kernel PUD mapping when it is set
 *
 * Returns 1 on success and 0 on failure (no PUD map is found).
 */
पूर्णांक pud_clear_huge(pud_t *pud)
अणु
	अगर (pud_large(*pud)) अणु
		pud_clear(pud);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pmd_clear_huge - clear kernel PMD mapping when it is set
 *
 * Returns 1 on success and 0 on failure (no PMD map is found).
 */
पूर्णांक pmd_clear_huge(pmd_t *pmd)
अणु
	अगर (pmd_large(*pmd)) अणु
		pmd_clear(pmd);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_X86_64
/**
 * pud_मुक्त_pmd_page - Clear pud entry and मुक्त pmd page.
 * @pud: Poपूर्णांकer to a PUD.
 * @addr: Virtual address associated with pud.
 *
 * Context: The pud range has been unmapped and TLB purged.
 * Return: 1 अगर clearing the entry succeeded. 0 otherwise.
 *
 * NOTE: Callers must allow a single page allocation.
 */
पूर्णांक pud_मुक्त_pmd_page(pud_t *pud, अचिन्हित दीर्घ addr)
अणु
	pmd_t *pmd, *pmd_sv;
	pte_t *pte;
	पूर्णांक i;

	pmd = (pmd_t *)pud_page_vaddr(*pud);
	pmd_sv = (pmd_t *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!pmd_sv)
		वापस 0;

	क्रम (i = 0; i < PTRS_PER_PMD; i++) अणु
		pmd_sv[i] = pmd[i];
		अगर (!pmd_none(pmd[i]))
			pmd_clear(&pmd[i]);
	पूर्ण

	pud_clear(pud);

	/* INVLPG to clear all paging-काष्ठाure caches */
	flush_tlb_kernel_range(addr, addr + PAGE_SIZE-1);

	क्रम (i = 0; i < PTRS_PER_PMD; i++) अणु
		अगर (!pmd_none(pmd_sv[i])) अणु
			pte = (pte_t *)pmd_page_vaddr(pmd_sv[i]);
			मुक्त_page((अचिन्हित दीर्घ)pte);
		पूर्ण
	पूर्ण

	मुक्त_page((अचिन्हित दीर्घ)pmd_sv);

	pgtable_pmd_page_dtor(virt_to_page(pmd));
	मुक्त_page((अचिन्हित दीर्घ)pmd);

	वापस 1;
पूर्ण

/**
 * pmd_मुक्त_pte_page - Clear pmd entry and मुक्त pte page.
 * @pmd: Poपूर्णांकer to a PMD.
 * @addr: Virtual address associated with pmd.
 *
 * Context: The pmd range has been unmapped and TLB purged.
 * Return: 1 अगर clearing the entry succeeded. 0 otherwise.
 */
पूर्णांक pmd_मुक्त_pte_page(pmd_t *pmd, अचिन्हित दीर्घ addr)
अणु
	pte_t *pte;

	pte = (pte_t *)pmd_page_vaddr(*pmd);
	pmd_clear(pmd);

	/* INVLPG to clear all paging-काष्ठाure caches */
	flush_tlb_kernel_range(addr, addr + PAGE_SIZE-1);

	मुक्त_page((अचिन्हित दीर्घ)pte);

	वापस 1;
पूर्ण

#अन्यथा /* !CONFIG_X86_64 */

/*
 * Disable मुक्त page handling on x86-PAE. This assures that ioremap()
 * करोes not update sync'd pmd entries. See vदो_स्मृति_sync_one().
 */
पूर्णांक pmd_मुक्त_pte_page(pmd_t *pmd, अचिन्हित दीर्घ addr)
अणु
	वापस pmd_none(*pmd);
पूर्ण

#पूर्ण_अगर /* CONFIG_X86_64 */
#पूर्ण_अगर	/* CONFIG_HAVE_ARCH_HUGE_VMAP */
