<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_HUGE_MM_H
#घोषणा _LINUX_HUGE_MM_H

#समावेश <linux/sched/coredump.h>
#समावेश <linux/mm_types.h>

#समावेश <linux/fs.h> /* only क्रम vma_is_dax() */

vm_fault_t करो_huge_pmd_anonymous_page(काष्ठा vm_fault *vmf);
पूर्णांक copy_huge_pmd(काष्ठा mm_काष्ठा *dst_mm, काष्ठा mm_काष्ठा *src_mm,
		  pmd_t *dst_pmd, pmd_t *src_pmd, अचिन्हित दीर्घ addr,
		  काष्ठा vm_area_काष्ठा *vma);
व्योम huge_pmd_set_accessed(काष्ठा vm_fault *vmf, pmd_t orig_pmd);
पूर्णांक copy_huge_pud(काष्ठा mm_काष्ठा *dst_mm, काष्ठा mm_काष्ठा *src_mm,
		  pud_t *dst_pud, pud_t *src_pud, अचिन्हित दीर्घ addr,
		  काष्ठा vm_area_काष्ठा *vma);

#अगर_घोषित CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD
व्योम huge_pud_set_accessed(काष्ठा vm_fault *vmf, pud_t orig_pud);
#अन्यथा
अटल अंतरभूत व्योम huge_pud_set_accessed(काष्ठा vm_fault *vmf, pud_t orig_pud)
अणु
पूर्ण
#पूर्ण_अगर

vm_fault_t करो_huge_pmd_wp_page(काष्ठा vm_fault *vmf, pmd_t orig_pmd);
काष्ठा page *follow_trans_huge_pmd(काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ addr, pmd_t *pmd,
				   अचिन्हित पूर्णांक flags);
bool madvise_मुक्त_huge_pmd(काष्ठा mmu_gather *tlb, काष्ठा vm_area_काष्ठा *vma,
			   pmd_t *pmd, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ next);
पूर्णांक zap_huge_pmd(काष्ठा mmu_gather *tlb, काष्ठा vm_area_काष्ठा *vma, pmd_t *pmd,
		 अचिन्हित दीर्घ addr);
पूर्णांक zap_huge_pud(काष्ठा mmu_gather *tlb, काष्ठा vm_area_काष्ठा *vma, pud_t *pud,
		 अचिन्हित दीर्घ addr);
bool move_huge_pmd(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ old_addr,
		   अचिन्हित दीर्घ new_addr, pmd_t *old_pmd, pmd_t *new_pmd);
पूर्णांक change_huge_pmd(काष्ठा vm_area_काष्ठा *vma, pmd_t *pmd, अचिन्हित दीर्घ addr,
		    pgprot_t newprot, अचिन्हित दीर्घ cp_flags);
vm_fault_t vmf_insert_pfn_pmd_prot(काष्ठा vm_fault *vmf, pfn_t pfn,
				   pgprot_t pgprot, bool ग_लिखो);

/**
 * vmf_insert_pfn_pmd - insert a pmd size pfn
 * @vmf: Structure describing the fault
 * @pfn: pfn to insert
 * @pgprot: page protection to use
 * @ग_लिखो: whether it's a ग_लिखो fault
 *
 * Insert a pmd size pfn. See vmf_insert_pfn() क्रम additional info.
 *
 * Return: vm_fault_t value.
 */
अटल अंतरभूत vm_fault_t vmf_insert_pfn_pmd(काष्ठा vm_fault *vmf, pfn_t pfn,
					    bool ग_लिखो)
अणु
	वापस vmf_insert_pfn_pmd_prot(vmf, pfn, vmf->vma->vm_page_prot, ग_लिखो);
पूर्ण
vm_fault_t vmf_insert_pfn_pud_prot(काष्ठा vm_fault *vmf, pfn_t pfn,
				   pgprot_t pgprot, bool ग_लिखो);

/**
 * vmf_insert_pfn_pud - insert a pud size pfn
 * @vmf: Structure describing the fault
 * @pfn: pfn to insert
 * @pgprot: page protection to use
 * @ग_लिखो: whether it's a ग_लिखो fault
 *
 * Insert a pud size pfn. See vmf_insert_pfn() क्रम additional info.
 *
 * Return: vm_fault_t value.
 */
अटल अंतरभूत vm_fault_t vmf_insert_pfn_pud(काष्ठा vm_fault *vmf, pfn_t pfn,
					    bool ग_लिखो)
अणु
	वापस vmf_insert_pfn_pud_prot(vmf, pfn, vmf->vma->vm_page_prot, ग_लिखो);
पूर्ण

क्रमागत transparent_hugepage_flag अणु
	TRANSPARENT_HUGEPAGE_NEVER_DAX,
	TRANSPARENT_HUGEPAGE_FLAG,
	TRANSPARENT_HUGEPAGE_REQ_MADV_FLAG,
	TRANSPARENT_HUGEPAGE_DEFRAG_सूचीECT_FLAG,
	TRANSPARENT_HUGEPAGE_DEFRAG_KSWAPD_FLAG,
	TRANSPARENT_HUGEPAGE_DEFRAG_KSWAPD_OR_MADV_FLAG,
	TRANSPARENT_HUGEPAGE_DEFRAG_REQ_MADV_FLAG,
	TRANSPARENT_HUGEPAGE_DEFRAG_KHUGEPAGED_FLAG,
	TRANSPARENT_HUGEPAGE_USE_ZERO_PAGE_FLAG,
पूर्ण;

काष्ठा kobject;
काष्ठा kobj_attribute;

sमाप_प्रकार single_hugepage_flag_store(काष्ठा kobject *kobj,
				   काष्ठा kobj_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार count,
				   क्रमागत transparent_hugepage_flag flag);
sमाप_प्रकार single_hugepage_flag_show(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr, अक्षर *buf,
				  क्रमागत transparent_hugepage_flag flag);
बाह्य काष्ठा kobj_attribute shmem_enabled_attr;

#घोषणा HPAGE_PMD_ORDER (HPAGE_PMD_SHIFT-PAGE_SHIFT)
#घोषणा HPAGE_PMD_NR (1<<HPAGE_PMD_ORDER)

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
#घोषणा HPAGE_PMD_SHIFT PMD_SHIFT
#घोषणा HPAGE_PMD_SIZE	((1UL) << HPAGE_PMD_SHIFT)
#घोषणा HPAGE_PMD_MASK	(~(HPAGE_PMD_SIZE - 1))

#घोषणा HPAGE_PUD_SHIFT PUD_SHIFT
#घोषणा HPAGE_PUD_SIZE	((1UL) << HPAGE_PUD_SHIFT)
#घोषणा HPAGE_PUD_MASK	(~(HPAGE_PUD_SIZE - 1))

बाह्य अचिन्हित दीर्घ transparent_hugepage_flags;

/*
 * to be used on vmas which are known to support THP.
 * Use transparent_hugepage_enabled otherwise
 */
अटल अंतरभूत bool __transparent_hugepage_enabled(काष्ठा vm_area_काष्ठा *vma)
अणु

	/*
	 * If the hardware/firmware marked hugepage support disabled.
	 */
	अगर (transparent_hugepage_flags & (1 << TRANSPARENT_HUGEPAGE_NEVER_DAX))
		वापस false;

	अगर (vma->vm_flags & VM_NOHUGEPAGE)
		वापस false;

	अगर (vma_is_temporary_stack(vma))
		वापस false;

	अगर (test_bit(MMF_DISABLE_THP, &vma->vm_mm->flags))
		वापस false;

	अगर (transparent_hugepage_flags & (1 << TRANSPARENT_HUGEPAGE_FLAG))
		वापस true;

	अगर (vma_is_dax(vma))
		वापस true;

	अगर (transparent_hugepage_flags &
				(1 << TRANSPARENT_HUGEPAGE_REQ_MADV_FLAG))
		वापस !!(vma->vm_flags & VM_HUGEPAGE);

	वापस false;
पूर्ण

bool transparent_hugepage_enabled(काष्ठा vm_area_काष्ठा *vma);

#घोषणा HPAGE_CACHE_INDEX_MASK (HPAGE_PMD_NR - 1)

अटल अंतरभूत bool transhuge_vma_suitable(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ haddr)
अणु
	/* Don't have to check pgoff क्रम anonymous vma */
	अगर (!vma_is_anonymous(vma)) अणु
		अगर (((vma->vm_start >> PAGE_SHIFT) & HPAGE_CACHE_INDEX_MASK) !=
			(vma->vm_pgoff & HPAGE_CACHE_INDEX_MASK))
			वापस false;
	पूर्ण

	अगर (haddr < vma->vm_start || haddr + HPAGE_PMD_SIZE > vma->vm_end)
		वापस false;
	वापस true;
पूर्ण

#घोषणा transparent_hugepage_use_zero_page()				\
	(transparent_hugepage_flags &					\
	 (1<<TRANSPARENT_HUGEPAGE_USE_ZERO_PAGE_FLAG))

अचिन्हित दीर्घ thp_get_unmapped_area(काष्ठा file *filp, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags);

व्योम prep_transhuge_page(काष्ठा page *page);
व्योम मुक्त_transhuge_page(काष्ठा page *page);
bool is_transparent_hugepage(काष्ठा page *page);

bool can_split_huge_page(काष्ठा page *page, पूर्णांक *pextra_pins);
पूर्णांक split_huge_page_to_list(काष्ठा page *page, काष्ठा list_head *list);
अटल अंतरभूत पूर्णांक split_huge_page(काष्ठा page *page)
अणु
	वापस split_huge_page_to_list(page, शून्य);
पूर्ण
व्योम deferred_split_huge_page(काष्ठा page *page);

व्योम __split_huge_pmd(काष्ठा vm_area_काष्ठा *vma, pmd_t *pmd,
		अचिन्हित दीर्घ address, bool मुक्तze, काष्ठा page *page);

#घोषणा split_huge_pmd(__vma, __pmd, __address)				\
	करो अणु								\
		pmd_t *____pmd = (__pmd);				\
		अगर (is_swap_pmd(*____pmd) || pmd_trans_huge(*____pmd)	\
					|| pmd_devmap(*____pmd))	\
			__split_huge_pmd(__vma, __pmd, __address,	\
						false, शून्य);		\
	पूर्ण  जबतक (0)


व्योम split_huge_pmd_address(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
		bool मुक्तze, काष्ठा page *page);

व्योम __split_huge_pud(काष्ठा vm_area_काष्ठा *vma, pud_t *pud,
		अचिन्हित दीर्घ address);

#घोषणा split_huge_pud(__vma, __pud, __address)				\
	करो अणु								\
		pud_t *____pud = (__pud);				\
		अगर (pud_trans_huge(*____pud)				\
					|| pud_devmap(*____pud))	\
			__split_huge_pud(__vma, __pud, __address);	\
	पूर्ण  जबतक (0)

पूर्णांक hugepage_madvise(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ *vm_flags,
		     पूर्णांक advice);
व्योम vma_adjust_trans_huge(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			   अचिन्हित दीर्घ end, दीर्घ adjust_next);
spinlock_t *__pmd_trans_huge_lock(pmd_t *pmd, काष्ठा vm_area_काष्ठा *vma);
spinlock_t *__pud_trans_huge_lock(pud_t *pud, काष्ठा vm_area_काष्ठा *vma);

अटल अंतरभूत पूर्णांक is_swap_pmd(pmd_t pmd)
अणु
	वापस !pmd_none(pmd) && !pmd_present(pmd);
पूर्ण

/* mmap_lock must be held on entry */
अटल अंतरभूत spinlock_t *pmd_trans_huge_lock(pmd_t *pmd,
		काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (is_swap_pmd(*pmd) || pmd_trans_huge(*pmd) || pmd_devmap(*pmd))
		वापस __pmd_trans_huge_lock(pmd, vma);
	अन्यथा
		वापस शून्य;
पूर्ण
अटल अंतरभूत spinlock_t *pud_trans_huge_lock(pud_t *pud,
		काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (pud_trans_huge(*pud) || pud_devmap(*pud))
		वापस __pud_trans_huge_lock(pud, vma);
	अन्यथा
		वापस शून्य;
पूर्ण

/**
 * thp_head - Head page of a transparent huge page.
 * @page: Any page (tail, head or regular) found in the page cache.
 */
अटल अंतरभूत काष्ठा page *thp_head(काष्ठा page *page)
अणु
	वापस compound_head(page);
पूर्ण

/**
 * thp_order - Order of a transparent huge page.
 * @page: Head page of a transparent huge page.
 */
अटल अंतरभूत अचिन्हित पूर्णांक thp_order(काष्ठा page *page)
अणु
	VM_BUG_ON_PGFLAGS(PageTail(page), page);
	अगर (PageHead(page))
		वापस HPAGE_PMD_ORDER;
	वापस 0;
पूर्ण

/**
 * thp_nr_pages - The number of regular pages in this huge page.
 * @page: The head page of a huge page.
 */
अटल अंतरभूत पूर्णांक thp_nr_pages(काष्ठा page *page)
अणु
	VM_BUG_ON_PGFLAGS(PageTail(page), page);
	अगर (PageHead(page))
		वापस HPAGE_PMD_NR;
	वापस 1;
पूर्ण

काष्ठा page *follow_devmap_pmd(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		pmd_t *pmd, पूर्णांक flags, काष्ठा dev_pagemap **pgmap);
काष्ठा page *follow_devmap_pud(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		pud_t *pud, पूर्णांक flags, काष्ठा dev_pagemap **pgmap);

vm_fault_t करो_huge_pmd_numa_page(काष्ठा vm_fault *vmf, pmd_t orig_pmd);

बाह्य काष्ठा page *huge_zero_page;
बाह्य अचिन्हित दीर्घ huge_zero_pfn;

अटल अंतरभूत bool is_huge_zero_page(काष्ठा page *page)
अणु
	वापस READ_ONCE(huge_zero_page) == page;
पूर्ण

अटल अंतरभूत bool is_huge_zero_pmd(pmd_t pmd)
अणु
	वापस READ_ONCE(huge_zero_pfn) == pmd_pfn(pmd) && pmd_present(pmd);
पूर्ण

अटल अंतरभूत bool is_huge_zero_pud(pud_t pud)
अणु
	वापस false;
पूर्ण

काष्ठा page *mm_get_huge_zero_page(काष्ठा mm_काष्ठा *mm);
व्योम mm_put_huge_zero_page(काष्ठा mm_काष्ठा *mm);

#घोषणा mk_huge_pmd(page, prot) pmd_mkhuge(mk_pmd(page, prot))

अटल अंतरभूत bool thp_migration_supported(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_ARCH_ENABLE_THP_MIGRATION);
पूर्ण

अटल अंतरभूत काष्ठा list_head *page_deferred_list(काष्ठा page *page)
अणु
	/*
	 * Global or memcg deferred list in the second tail pages is
	 * occupied by compound_head.
	 */
	वापस &page[2].deferred_list;
पूर्ण

#अन्यथा /* CONFIG_TRANSPARENT_HUGEPAGE */
#घोषणा HPAGE_PMD_SHIFT (अणु BUILD_BUG(); 0; पूर्ण)
#घोषणा HPAGE_PMD_MASK (अणु BUILD_BUG(); 0; पूर्ण)
#घोषणा HPAGE_PMD_SIZE (अणु BUILD_BUG(); 0; पूर्ण)

#घोषणा HPAGE_PUD_SHIFT (अणु BUILD_BUG(); 0; पूर्ण)
#घोषणा HPAGE_PUD_MASK (अणु BUILD_BUG(); 0; पूर्ण)
#घोषणा HPAGE_PUD_SIZE (अणु BUILD_BUG(); 0; पूर्ण)

अटल अंतरभूत काष्ठा page *thp_head(काष्ठा page *page)
अणु
	VM_BUG_ON_PGFLAGS(PageTail(page), page);
	वापस page;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक thp_order(काष्ठा page *page)
अणु
	VM_BUG_ON_PGFLAGS(PageTail(page), page);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक thp_nr_pages(काष्ठा page *page)
अणु
	VM_BUG_ON_PGFLAGS(PageTail(page), page);
	वापस 1;
पूर्ण

अटल अंतरभूत bool __transparent_hugepage_enabled(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool transparent_hugepage_enabled(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool transhuge_vma_suitable(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ haddr)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम prep_transhuge_page(काष्ठा page *page) अणुपूर्ण

अटल अंतरभूत bool is_transparent_hugepage(काष्ठा page *page)
अणु
	वापस false;
पूर्ण

#घोषणा transparent_hugepage_flags 0UL

#घोषणा thp_get_unmapped_area	शून्य

अटल अंतरभूत bool
can_split_huge_page(काष्ठा page *page, पूर्णांक *pextra_pins)
अणु
	BUILD_BUG();
	वापस false;
पूर्ण
अटल अंतरभूत पूर्णांक
split_huge_page_to_list(काष्ठा page *page, काष्ठा list_head *list)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक split_huge_page(काष्ठा page *page)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम deferred_split_huge_page(काष्ठा page *page) अणुपूर्ण
#घोषणा split_huge_pmd(__vma, __pmd, __address)	\
	करो अणु पूर्ण जबतक (0)

अटल अंतरभूत व्योम __split_huge_pmd(काष्ठा vm_area_काष्ठा *vma, pmd_t *pmd,
		अचिन्हित दीर्घ address, bool मुक्तze, काष्ठा page *page) अणुपूर्ण
अटल अंतरभूत व्योम split_huge_pmd_address(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ address, bool मुक्तze, काष्ठा page *page) अणुपूर्ण

#घोषणा split_huge_pud(__vma, __pmd, __address)	\
	करो अणु पूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक hugepage_madvise(काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ *vm_flags, पूर्णांक advice)
अणु
	BUG();
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम vma_adjust_trans_huge(काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ start,
					 अचिन्हित दीर्घ end,
					 दीर्घ adjust_next)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक is_swap_pmd(pmd_t pmd)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत spinlock_t *pmd_trans_huge_lock(pmd_t *pmd,
		काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत spinlock_t *pud_trans_huge_lock(pud_t *pud,
		काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत vm_fault_t करो_huge_pmd_numa_page(काष्ठा vm_fault *vmf,
		pmd_t orig_pmd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool is_huge_zero_page(काष्ठा page *page)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool is_huge_zero_pmd(pmd_t pmd)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool is_huge_zero_pud(pud_t pud)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम mm_put_huge_zero_page(काष्ठा mm_काष्ठा *mm)
अणु
	वापस;
पूर्ण

अटल अंतरभूत काष्ठा page *follow_devmap_pmd(काष्ठा vm_area_काष्ठा *vma,
	अचिन्हित दीर्घ addr, pmd_t *pmd, पूर्णांक flags, काष्ठा dev_pagemap **pgmap)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा page *follow_devmap_pud(काष्ठा vm_area_काष्ठा *vma,
	अचिन्हित दीर्घ addr, pud_t *pud, पूर्णांक flags, काष्ठा dev_pagemap **pgmap)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool thp_migration_supported(व्योम)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

/**
 * thp_size - Size of a transparent huge page.
 * @page: Head page of a transparent huge page.
 *
 * Return: Number of bytes in this page.
 */
अटल अंतरभूत अचिन्हित दीर्घ thp_size(काष्ठा page *page)
अणु
	वापस PAGE_SIZE << thp_order(page);
पूर्ण

#पूर्ण_अगर /* _LINUX_HUGE_MM_H */
