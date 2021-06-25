<शैली गुरु>
/*
 * PPC Huge TLB Page Support क्रम Kernel.
 *
 * Copyright (C) 2003 David Gibson, IBM Corporation.
 * Copyright (C) 2011 Becky Bruce, Freescale Semiconductor
 *
 * Based on the IA-32 version:
 * Copyright (C) 2002, Rohit Seth <rohit.seth@पूर्णांकel.com>
 */

#समावेश <linux/mm.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/export.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/memblock.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/swap.h>
#समावेश <linux/swapops.h>
#समावेश <linux/kmemleak.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/hugetlb.h>
#समावेश <यंत्र/pte-walk.h>

bool hugetlb_disabled = false;

#घोषणा hugepd_none(hpd)	(hpd_val(hpd) == 0)

#घोषणा PTE_T_ORDER	(__builtin_ffs(माप(pte_basic_t)) - \
			 __builtin_ffs(माप(व्योम *)))

pte_t *huge_pte_offset(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ sz)
अणु
	/*
	 * Only called क्रम hugetlbfs pages, hence can ignore THP and the
	 * irq disabled walk.
	 */
	वापस __find_linux_pte(mm->pgd, addr, शून्य, शून्य);
पूर्ण

अटल पूर्णांक __hugepte_alloc(काष्ठा mm_काष्ठा *mm, hugepd_t *hpdp,
			   अचिन्हित दीर्घ address, अचिन्हित पूर्णांक pdshअगरt,
			   अचिन्हित पूर्णांक pshअगरt, spinlock_t *ptl)
अणु
	काष्ठा kmem_cache *cachep;
	pte_t *new;
	पूर्णांक i;
	पूर्णांक num_hugepd;

	अगर (pshअगरt >= pdshअगरt) अणु
		cachep = PGT_CACHE(PTE_T_ORDER);
		num_hugepd = 1 << (pshअगरt - pdshअगरt);
	पूर्ण अन्यथा अणु
		cachep = PGT_CACHE(pdshअगरt - pshअगरt);
		num_hugepd = 1;
	पूर्ण

	अगर (!cachep) अणु
		WARN_ONCE(1, "No page table cache created for hugetlb tables");
		वापस -ENOMEM;
	पूर्ण

	new = kmem_cache_alloc(cachep, pgtable_gfp_flags(mm, GFP_KERNEL));

	BUG_ON(pshअगरt > HUGEPD_SHIFT_MASK);
	BUG_ON((अचिन्हित दीर्घ)new & HUGEPD_SHIFT_MASK);

	अगर (!new)
		वापस -ENOMEM;

	/*
	 * Make sure other cpus find the hugepd set only after a
	 * properly initialized page table is visible to them.
	 * For more details look क्रम comment in __pte_alloc().
	 */
	smp_wmb();

	spin_lock(ptl);
	/*
	 * We have multiple higher-level entries that poपूर्णांक to the same
	 * actual pte location.  Fill in each as we go and backtrack on error.
	 * We need all of these so the DTLB pgtable walk code can find the
	 * right higher-level entry without knowing अगर it's a hugepage or not.
	 */
	क्रम (i = 0; i < num_hugepd; i++, hpdp++) अणु
		अगर (unlikely(!hugepd_none(*hpdp)))
			अवरोध;
		hugepd_populate(hpdp, new, pshअगरt);
	पूर्ण
	/* If we bailed from the क्रम loop early, an error occurred, clean up */
	अगर (i < num_hugepd) अणु
		क्रम (i = i - 1 ; i >= 0; i--, hpdp--)
			*hpdp = __hugepd(0);
		kmem_cache_मुक्त(cachep, new);
	पूर्ण अन्यथा अणु
		kmemleak_ignore(new);
	पूर्ण
	spin_unlock(ptl);
	वापस 0;
पूर्ण

/*
 * At this poपूर्णांक we करो the placement change only क्रम BOOK3S 64. This would
 * possibly work on other subarchs.
 */
pte_t *huge_pte_alloc(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
		      अचिन्हित दीर्घ addr, अचिन्हित दीर्घ sz)
अणु
	pgd_t *pg;
	p4d_t *p4;
	pud_t *pu;
	pmd_t *pm;
	hugepd_t *hpdp = शून्य;
	अचिन्हित pshअगरt = __ffs(sz);
	अचिन्हित pdshअगरt = PGसूची_SHIFT;
	spinlock_t *ptl;

	addr &= ~(sz-1);
	pg = pgd_offset(mm, addr);
	p4 = p4d_offset(pg, addr);

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	अगर (pshअगरt == PGसूची_SHIFT)
		/* 16GB huge page */
		वापस (pte_t *) p4;
	अन्यथा अगर (pshअगरt > PUD_SHIFT) अणु
		/*
		 * We need to use hugepd table
		 */
		ptl = &mm->page_table_lock;
		hpdp = (hugepd_t *)p4;
	पूर्ण अन्यथा अणु
		pdshअगरt = PUD_SHIFT;
		pu = pud_alloc(mm, p4, addr);
		अगर (!pu)
			वापस शून्य;
		अगर (pshअगरt == PUD_SHIFT)
			वापस (pte_t *)pu;
		अन्यथा अगर (pshअगरt > PMD_SHIFT) अणु
			ptl = pud_lockptr(mm, pu);
			hpdp = (hugepd_t *)pu;
		पूर्ण अन्यथा अणु
			pdshअगरt = PMD_SHIFT;
			pm = pmd_alloc(mm, pu, addr);
			अगर (!pm)
				वापस शून्य;
			अगर (pshअगरt == PMD_SHIFT)
				/* 16MB hugepage */
				वापस (pte_t *)pm;
			अन्यथा अणु
				ptl = pmd_lockptr(mm, pm);
				hpdp = (hugepd_t *)pm;
			पूर्ण
		पूर्ण
	पूर्ण
#अन्यथा
	अगर (pshअगरt >= PGसूची_SHIFT) अणु
		ptl = &mm->page_table_lock;
		hpdp = (hugepd_t *)p4;
	पूर्ण अन्यथा अणु
		pdshअगरt = PUD_SHIFT;
		pu = pud_alloc(mm, p4, addr);
		अगर (!pu)
			वापस शून्य;
		अगर (pshअगरt >= PUD_SHIFT) अणु
			ptl = pud_lockptr(mm, pu);
			hpdp = (hugepd_t *)pu;
		पूर्ण अन्यथा अणु
			pdshअगरt = PMD_SHIFT;
			pm = pmd_alloc(mm, pu, addr);
			अगर (!pm)
				वापस शून्य;
			ptl = pmd_lockptr(mm, pm);
			hpdp = (hugepd_t *)pm;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अगर (!hpdp)
		वापस शून्य;

	अगर (IS_ENABLED(CONFIG_PPC_8xx) && pshअगरt < PMD_SHIFT)
		वापस pte_alloc_map(mm, (pmd_t *)hpdp, addr);

	BUG_ON(!hugepd_none(*hpdp) && !hugepd_ok(*hpdp));

	अगर (hugepd_none(*hpdp) && __hugepte_alloc(mm, hpdp, addr,
						  pdshअगरt, pshअगरt, ptl))
		वापस शून्य;

	वापस hugepte_offset(*hpdp, addr, pdshअगरt);
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S_64
/*
 * Tracks gpages after the device tree is scanned and beक्रमe the
 * huge_boot_pages list is पढ़ोy on pseries.
 */
#घोषणा MAX_NUMBER_GPAGES	1024
__initdata अटल u64 gpage_मुक्तarray[MAX_NUMBER_GPAGES];
__initdata अटल अचिन्हित nr_gpages;

/*
 * Build list of addresses of gigantic pages.  This function is used in early
 * boot beक्रमe the buddy allocator is setup.
 */
व्योम __init pseries_add_gpage(u64 addr, u64 page_size, अचिन्हित दीर्घ number_of_pages)
अणु
	अगर (!addr)
		वापस;
	जबतक (number_of_pages > 0) अणु
		gpage_मुक्तarray[nr_gpages] = addr;
		nr_gpages++;
		number_of_pages--;
		addr += page_size;
	पूर्ण
पूर्ण

अटल पूर्णांक __init pseries_alloc_booपंचांगem_huge_page(काष्ठा hstate *hstate)
अणु
	काष्ठा huge_booपंचांगem_page *m;
	अगर (nr_gpages == 0)
		वापस 0;
	m = phys_to_virt(gpage_मुक्तarray[--nr_gpages]);
	gpage_मुक्तarray[nr_gpages] = 0;
	list_add(&m->list, &huge_boot_pages);
	m->hstate = hstate;
	वापस 1;
पूर्ण
#पूर्ण_अगर


पूर्णांक __init alloc_booपंचांगem_huge_page(काष्ठा hstate *h)
अणु

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	अगर (firmware_has_feature(FW_FEATURE_LPAR) && !radix_enabled())
		वापस pseries_alloc_booपंचांगem_huge_page(h);
#पूर्ण_अगर
	वापस __alloc_booपंचांगem_huge_page(h);
पूर्ण

#अगर_अघोषित CONFIG_PPC_BOOK3S_64
#घोषणा HUGEPD_FREELIST_SIZE \
	((PAGE_SIZE - माप(काष्ठा hugepd_मुक्तlist)) / माप(pte_t))

काष्ठा hugepd_मुक्तlist अणु
	काष्ठा rcu_head	rcu;
	अचिन्हित पूर्णांक index;
	व्योम *ptes[];
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा hugepd_मुक्तlist *, hugepd_मुक्तlist_cur);

अटल व्योम hugepd_मुक्त_rcu_callback(काष्ठा rcu_head *head)
अणु
	काष्ठा hugepd_मुक्तlist *batch =
		container_of(head, काष्ठा hugepd_मुक्तlist, rcu);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < batch->index; i++)
		kmem_cache_मुक्त(PGT_CACHE(PTE_T_ORDER), batch->ptes[i]);

	मुक्त_page((अचिन्हित दीर्घ)batch);
पूर्ण

अटल व्योम hugepd_मुक्त(काष्ठा mmu_gather *tlb, व्योम *hugepte)
अणु
	काष्ठा hugepd_मुक्तlist **batchp;

	batchp = &get_cpu_var(hugepd_मुक्तlist_cur);

	अगर (atomic_पढ़ो(&tlb->mm->mm_users) < 2 ||
	    mm_is_thपढ़ो_local(tlb->mm)) अणु
		kmem_cache_मुक्त(PGT_CACHE(PTE_T_ORDER), hugepte);
		put_cpu_var(hugepd_मुक्तlist_cur);
		वापस;
	पूर्ण

	अगर (*batchp == शून्य) अणु
		*batchp = (काष्ठा hugepd_मुक्तlist *)__get_मुक्त_page(GFP_ATOMIC);
		(*batchp)->index = 0;
	पूर्ण

	(*batchp)->ptes[(*batchp)->index++] = hugepte;
	अगर ((*batchp)->index == HUGEPD_FREELIST_SIZE) अणु
		call_rcu(&(*batchp)->rcu, hugepd_मुक्त_rcu_callback);
		*batchp = शून्य;
	पूर्ण
	put_cpu_var(hugepd_मुक्तlist_cur);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम hugepd_मुक्त(काष्ठा mmu_gather *tlb, व्योम *hugepte) अणुपूर्ण
#पूर्ण_अगर

/* Return true when the entry to be मुक्तd maps more than the area being मुक्तd */
अटल bool range_is_outside_limits(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				    अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing,
				    अचिन्हित दीर्घ mask)
अणु
	अगर ((start & mask) < न्यूनमान)
		वापस true;
	अगर (उच्चमानing) अणु
		उच्चमानing &= mask;
		अगर (!उच्चमानing)
			वापस true;
	पूर्ण
	वापस end - 1 > उच्चमानing - 1;
पूर्ण

अटल व्योम मुक्त_hugepd_range(काष्ठा mmu_gather *tlb, hugepd_t *hpdp, पूर्णांक pdshअगरt,
			      अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
			      अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing)
अणु
	pte_t *hugepte = hugepd_page(*hpdp);
	पूर्णांक i;

	अचिन्हित दीर्घ pdmask = ~((1UL << pdshअगरt) - 1);
	अचिन्हित पूर्णांक num_hugepd = 1;
	अचिन्हित पूर्णांक shअगरt = hugepd_shअगरt(*hpdp);

	/* Note: On fsl the hpdp may be the first of several */
	अगर (shअगरt > pdshअगरt)
		num_hugepd = 1 << (shअगरt - pdshअगरt);

	अगर (range_is_outside_limits(start, end, न्यूनमान, उच्चमानing, pdmask))
		वापस;

	क्रम (i = 0; i < num_hugepd; i++, hpdp++)
		*hpdp = __hugepd(0);

	अगर (shअगरt >= pdshअगरt)
		hugepd_मुक्त(tlb, hugepte);
	अन्यथा
		pgtable_मुक्त_tlb(tlb, hugepte,
				 get_hugepd_cache_index(pdshअगरt - shअगरt));
पूर्ण

अटल व्योम hugetlb_मुक्त_pte_range(काष्ठा mmu_gather *tlb, pmd_t *pmd,
				   अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				   अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing)
अणु
	pgtable_t token = pmd_pgtable(*pmd);

	अगर (range_is_outside_limits(addr, end, न्यूनमान, उच्चमानing, PMD_MASK))
		वापस;

	pmd_clear(pmd);
	pte_मुक्त_tlb(tlb, token, addr);
	mm_dec_nr_ptes(tlb->mm);
पूर्ण

अटल व्योम hugetlb_मुक्त_pmd_range(काष्ठा mmu_gather *tlb, pud_t *pud,
				   अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				   अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing)
अणु
	pmd_t *pmd;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ start;

	start = addr;
	करो अणु
		अचिन्हित दीर्घ more;

		pmd = pmd_offset(pud, addr);
		next = pmd_addr_end(addr, end);
		अगर (!is_hugepd(__hugepd(pmd_val(*pmd)))) अणु
			अगर (pmd_none_or_clear_bad(pmd))
				जारी;

			/*
			 * अगर it is not hugepd poपूर्णांकer, we should alपढ़ोy find
			 * it cleared.
			 */
			WARN_ON(!IS_ENABLED(CONFIG_PPC_8xx));

			hugetlb_मुक्त_pte_range(tlb, pmd, addr, end, न्यूनमान, उच्चमानing);

			जारी;
		पूर्ण
		/*
		 * Increment next by the size of the huge mapping since
		 * there may be more than one entry at this level क्रम a
		 * single hugepage, but all of them poपूर्णांक to
		 * the same kmem cache that holds the hugepte.
		 */
		more = addr + (1 << hugepd_shअगरt(*(hugepd_t *)pmd));
		अगर (more > next)
			next = more;

		मुक्त_hugepd_range(tlb, (hugepd_t *)pmd, PMD_SHIFT,
				  addr, next, न्यूनमान, उच्चमानing);
	पूर्ण जबतक (addr = next, addr != end);

	अगर (range_is_outside_limits(start, end, न्यूनमान, उच्चमानing, PUD_MASK))
		वापस;

	pmd = pmd_offset(pud, start & PUD_MASK);
	pud_clear(pud);
	pmd_मुक्त_tlb(tlb, pmd, start & PUD_MASK);
	mm_dec_nr_pmds(tlb->mm);
पूर्ण

अटल व्योम hugetlb_मुक्त_pud_range(काष्ठा mmu_gather *tlb, p4d_t *p4d,
				   अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
				   अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing)
अणु
	pud_t *pud;
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ start;

	start = addr;
	करो अणु
		pud = pud_offset(p4d, addr);
		next = pud_addr_end(addr, end);
		अगर (!is_hugepd(__hugepd(pud_val(*pud)))) अणु
			अगर (pud_none_or_clear_bad(pud))
				जारी;
			hugetlb_मुक्त_pmd_range(tlb, pud, addr, next, न्यूनमान,
					       उच्चमानing);
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ more;
			/*
			 * Increment next by the size of the huge mapping since
			 * there may be more than one entry at this level क्रम a
			 * single hugepage, but all of them poपूर्णांक to
			 * the same kmem cache that holds the hugepte.
			 */
			more = addr + (1 << hugepd_shअगरt(*(hugepd_t *)pud));
			अगर (more > next)
				next = more;

			मुक्त_hugepd_range(tlb, (hugepd_t *)pud, PUD_SHIFT,
					  addr, next, न्यूनमान, उच्चमानing);
		पूर्ण
	पूर्ण जबतक (addr = next, addr != end);

	अगर (range_is_outside_limits(start, end, न्यूनमान, उच्चमानing, PGसूची_MASK))
		वापस;

	pud = pud_offset(p4d, start & PGसूची_MASK);
	p4d_clear(p4d);
	pud_मुक्त_tlb(tlb, pud, start & PGसूची_MASK);
	mm_dec_nr_puds(tlb->mm);
पूर्ण

/*
 * This function मुक्तs user-level page tables of a process.
 */
व्योम hugetlb_मुक्त_pgd_range(काष्ठा mmu_gather *tlb,
			    अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
			    अचिन्हित दीर्घ न्यूनमान, अचिन्हित दीर्घ उच्चमानing)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	अचिन्हित दीर्घ next;

	/*
	 * Because there are a number of dअगरferent possible pagetable
	 * layouts क्रम hugepage ranges, we limit knowledge of how
	 * things should be laid out to the allocation path
	 * (huge_pte_alloc(), above).  Everything अन्यथा works out the
	 * काष्ठाure as it goes from inक्रमmation in the hugepd
	 * poपूर्णांकers.  That means that we can't here use the
	 * optimization used in the normal page मुक्त_pgd_range(), of
	 * checking whether we're actually covering a large enough
	 * range to have to करो anything at the top level of the walk
	 * instead of at the bottom.
	 *
	 * To make sense of this, you should probably go पढ़ो the big
	 * block comment at the top of the normal मुक्त_pgd_range(),
	 * too.
	 */

	करो अणु
		next = pgd_addr_end(addr, end);
		pgd = pgd_offset(tlb->mm, addr);
		p4d = p4d_offset(pgd, addr);
		अगर (!is_hugepd(__hugepd(pgd_val(*pgd)))) अणु
			अगर (p4d_none_or_clear_bad(p4d))
				जारी;
			hugetlb_मुक्त_pud_range(tlb, p4d, addr, next, न्यूनमान, उच्चमानing);
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ more;
			/*
			 * Increment next by the size of the huge mapping since
			 * there may be more than one entry at the pgd level
			 * क्रम a single hugepage, but all of them poपूर्णांक to the
			 * same kmem cache that holds the hugepte.
			 */
			more = addr + (1 << hugepd_shअगरt(*(hugepd_t *)pgd));
			अगर (more > next)
				next = more;

			मुक्त_hugepd_range(tlb, (hugepd_t *)p4d, PGसूची_SHIFT,
					  addr, next, न्यूनमान, उच्चमानing);
		पूर्ण
	पूर्ण जबतक (addr = next, addr != end);
पूर्ण

काष्ठा page *follow_huge_pd(काष्ठा vm_area_काष्ठा *vma,
			    अचिन्हित दीर्घ address, hugepd_t hpd,
			    पूर्णांक flags, पूर्णांक pdshअगरt)
अणु
	pte_t *ptep;
	spinlock_t *ptl;
	काष्ठा page *page = शून्य;
	अचिन्हित दीर्घ mask;
	पूर्णांक shअगरt = hugepd_shअगरt(hpd);
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

retry:
	/*
	 * hugepage directory entries are रक्षित by mm->page_table_lock
	 * Use this instead of huge_pte_lockptr
	 */
	ptl = &mm->page_table_lock;
	spin_lock(ptl);

	ptep = hugepte_offset(hpd, address, pdshअगरt);
	अगर (pte_present(*ptep)) अणु
		mask = (1UL << shअगरt) - 1;
		page = pte_page(*ptep);
		page += ((address & mask) >> PAGE_SHIFT);
		अगर (flags & FOLL_GET)
			get_page(page);
	पूर्ण अन्यथा अणु
		अगर (is_hugetlb_entry_migration(*ptep)) अणु
			spin_unlock(ptl);
			__migration_entry_रुको(mm, ptep, ptl);
			जाओ retry;
		पूर्ण
	पूर्ण
	spin_unlock(ptl);
	वापस page;
पूर्ण

#अगर_घोषित CONFIG_PPC_MM_SLICES
अचिन्हित दीर्घ hugetlb_get_unmapped_area(काष्ठा file *file, अचिन्हित दीर्घ addr,
					अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
					अचिन्हित दीर्घ flags)
अणु
	काष्ठा hstate *hstate = hstate_file(file);
	पूर्णांक mmu_psize = shअगरt_to_mmu_psize(huge_page_shअगरt(hstate));

#अगर_घोषित CONFIG_PPC_RADIX_MMU
	अगर (radix_enabled())
		वापस radix__hugetlb_get_unmapped_area(file, addr, len,
						       pgoff, flags);
#पूर्ण_अगर
	वापस slice_get_unmapped_area(addr, len, flags, mmu_psize, 1);
पूर्ण
#पूर्ण_अगर

अचिन्हित दीर्घ vma_mmu_pagesize(काष्ठा vm_area_काष्ठा *vma)
अणु
	/* With radix we करोn't use slice, so derive it from vma*/
	अगर (IS_ENABLED(CONFIG_PPC_MM_SLICES) && !radix_enabled()) अणु
		अचिन्हित पूर्णांक psize = get_slice_psize(vma->vm_mm, vma->vm_start);

		वापस 1UL << mmu_pमाप_प्रकारo_shअगरt(psize);
	पूर्ण
	वापस vma_kernel_pagesize(vma);
पूर्ण

bool __init arch_hugetlb_valid_size(अचिन्हित दीर्घ size)
अणु
	पूर्णांक shअगरt = __ffs(size);
	पूर्णांक mmu_psize;

	/* Check that it is a page size supported by the hardware and
	 * that it fits within pagetable and slice limits. */
	अगर (size <= PAGE_SIZE || !is_घातer_of_2(size))
		वापस false;

	mmu_psize = check_and_get_huge_psize(shअगरt);
	अगर (mmu_psize < 0)
		वापस false;

	BUG_ON(mmu_psize_defs[mmu_psize].shअगरt != shअगरt);

	वापस true;
पूर्ण

अटल पूर्णांक __init add_huge_page_size(अचिन्हित दीर्घ दीर्घ size)
अणु
	पूर्णांक shअगरt = __ffs(size);

	अगर (!arch_hugetlb_valid_size((अचिन्हित दीर्घ)size))
		वापस -EINVAL;

	hugetlb_add_hstate(shअगरt - PAGE_SHIFT);
	वापस 0;
पूर्ण

अटल पूर्णांक __init hugetlbpage_init(व्योम)
अणु
	bool configured = false;
	पूर्णांक psize;

	अगर (hugetlb_disabled) अणु
		pr_info("HugeTLB support is disabled!\n");
		वापस 0;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_PPC_BOOK3S_64) && !radix_enabled() &&
	    !mmu_has_feature(MMU_FTR_16M_PAGE))
		वापस -ENODEV;

	क्रम (psize = 0; psize < MMU_PAGE_COUNT; ++psize) अणु
		अचिन्हित shअगरt;
		अचिन्हित pdshअगरt;

		अगर (!mmu_psize_defs[psize].shअगरt)
			जारी;

		shअगरt = mmu_pमाप_प्रकारo_shअगरt(psize);

#अगर_घोषित CONFIG_PPC_BOOK3S_64
		अगर (shअगरt > PGसूची_SHIFT)
			जारी;
		अन्यथा अगर (shअगरt > PUD_SHIFT)
			pdshअगरt = PGसूची_SHIFT;
		अन्यथा अगर (shअगरt > PMD_SHIFT)
			pdshअगरt = PUD_SHIFT;
		अन्यथा
			pdshअगरt = PMD_SHIFT;
#अन्यथा
		अगर (shअगरt < PUD_SHIFT)
			pdshअगरt = PMD_SHIFT;
		अन्यथा अगर (shअगरt < PGसूची_SHIFT)
			pdshअगरt = PUD_SHIFT;
		अन्यथा
			pdshअगरt = PGसूची_SHIFT;
#पूर्ण_अगर

		अगर (add_huge_page_size(1ULL << shअगरt) < 0)
			जारी;
		/*
		 * अगर we have pdshअगरt and shअगरt value same, we करोn't
		 * use pgt cache क्रम hugepd.
		 */
		अगर (pdshअगरt > shअगरt) अणु
			अगर (!IS_ENABLED(CONFIG_PPC_8xx))
				pgtable_cache_add(pdshअगरt - shअगरt);
		पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_PPC_FSL_BOOK3E) ||
			   IS_ENABLED(CONFIG_PPC_8xx)) अणु
			pgtable_cache_add(PTE_T_ORDER);
		पूर्ण

		configured = true;
	पूर्ण

	अगर (configured) अणु
		अगर (IS_ENABLED(CONFIG_HUGETLB_PAGE_SIZE_VARIABLE))
			hugetlbpage_init_शेष();
	पूर्ण अन्यथा
		pr_info("Failed to initialize. Disabling HugeTLB");

	वापस 0;
पूर्ण

arch_initcall(hugetlbpage_init);

व्योम __init gigantic_hugetlb_cma_reserve(व्योम)
अणु
	अचिन्हित दीर्घ order = 0;

	अगर (radix_enabled())
		order = PUD_SHIFT - PAGE_SHIFT;
	अन्यथा अगर (!firmware_has_feature(FW_FEATURE_LPAR) && mmu_psize_defs[MMU_PAGE_16G].shअगरt)
		/*
		 * For pseries we करो use ibm,expected#pages क्रम reserving 16G pages.
		 */
		order = mmu_pमाप_प्रकारo_shअगरt(MMU_PAGE_16G) - PAGE_SHIFT;

	अगर (order) अणु
		VM_WARN_ON(order < MAX_ORDER);
		hugetlb_cma_reserve(order);
	पूर्ण
पूर्ण
