<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SWAPOPS_H
#घोषणा _LINUX_SWAPOPS_H

#समावेश <linux/radix-tree.h>
#समावेश <linux/bug.h>
#समावेश <linux/mm_types.h>

#अगर_घोषित CONFIG_MMU

/*
 * swapcache pages are stored in the swapper_space radix tree.  We want to
 * get good packing density in that tree, so the index should be dense in
 * the low-order bits.
 *
 * We arrange the `type' and `offset' fields so that `type' is at the seven
 * high-order bits of the swp_entry_t and `offset' is right-aligned in the
 * reमुख्यing bits.  Although `type' itself needs only five bits, we allow क्रम
 * shmem/पंचांगpfs to shअगरt it all up a further two bits: see swp_to_radix_entry().
 *
 * swp_entry_t's are *never* stored anywhere in their arch-dependent क्रमmat.
 */
#घोषणा SWP_TYPE_SHIFT	(BITS_PER_XA_VALUE - MAX_SWAPखाताS_SHIFT)
#घोषणा SWP_OFFSET_MASK	((1UL << SWP_TYPE_SHIFT) - 1)

/* Clear all flags but only keep swp_entry_t related inक्रमmation */
अटल अंतरभूत pte_t pte_swp_clear_flags(pte_t pte)
अणु
	अगर (pte_swp_soft_dirty(pte))
		pte = pte_swp_clear_soft_dirty(pte);
	अगर (pte_swp_uffd_wp(pte))
		pte = pte_swp_clear_uffd_wp(pte);
	वापस pte;
पूर्ण

/*
 * Store a type+offset पूर्णांकo a swp_entry_t in an arch-independent क्रमmat
 */
अटल अंतरभूत swp_entry_t swp_entry(अचिन्हित दीर्घ type, pgoff_t offset)
अणु
	swp_entry_t ret;

	ret.val = (type << SWP_TYPE_SHIFT) | (offset & SWP_OFFSET_MASK);
	वापस ret;
पूर्ण

/*
 * Extract the `type' field from a swp_entry_t.  The swp_entry_t is in
 * arch-independent क्रमmat
 */
अटल अंतरभूत अचिन्हित swp_type(swp_entry_t entry)
अणु
	वापस (entry.val >> SWP_TYPE_SHIFT);
पूर्ण

/*
 * Extract the `offset' field from a swp_entry_t.  The swp_entry_t is in
 * arch-independent क्रमmat
 */
अटल अंतरभूत pgoff_t swp_offset(swp_entry_t entry)
अणु
	वापस entry.val & SWP_OFFSET_MASK;
पूर्ण

/* check whether a pte poपूर्णांकs to a swap entry */
अटल अंतरभूत पूर्णांक is_swap_pte(pte_t pte)
अणु
	वापस !pte_none(pte) && !pte_present(pte);
पूर्ण

/*
 * Convert the arch-dependent pte representation of a swp_entry_t पूर्णांकo an
 * arch-independent swp_entry_t.
 */
अटल अंतरभूत swp_entry_t pte_to_swp_entry(pte_t pte)
अणु
	swp_entry_t arch_entry;

	pte = pte_swp_clear_flags(pte);
	arch_entry = __pte_to_swp_entry(pte);
	वापस swp_entry(__swp_type(arch_entry), __swp_offset(arch_entry));
पूर्ण

/*
 * Convert the arch-independent representation of a swp_entry_t पूर्णांकo the
 * arch-dependent pte representation.
 */
अटल अंतरभूत pte_t swp_entry_to_pte(swp_entry_t entry)
अणु
	swp_entry_t arch_entry;

	arch_entry = __swp_entry(swp_type(entry), swp_offset(entry));
	वापस __swp_entry_to_pte(arch_entry);
पूर्ण

अटल अंतरभूत swp_entry_t radix_to_swp_entry(व्योम *arg)
अणु
	swp_entry_t entry;

	entry.val = xa_to_value(arg);
	वापस entry;
पूर्ण

अटल अंतरभूत व्योम *swp_to_radix_entry(swp_entry_t entry)
अणु
	वापस xa_mk_value(entry.val);
पूर्ण

#अगर IS_ENABLED(CONFIG_DEVICE_PRIVATE)
अटल अंतरभूत swp_entry_t make_device_निजी_entry(काष्ठा page *page, bool ग_लिखो)
अणु
	वापस swp_entry(ग_लिखो ? SWP_DEVICE_WRITE : SWP_DEVICE_READ,
			 page_to_pfn(page));
पूर्ण

अटल अंतरभूत bool is_device_निजी_entry(swp_entry_t entry)
अणु
	पूर्णांक type = swp_type(entry);
	वापस type == SWP_DEVICE_READ || type == SWP_DEVICE_WRITE;
पूर्ण

अटल अंतरभूत व्योम make_device_निजी_entry_पढ़ो(swp_entry_t *entry)
अणु
	*entry = swp_entry(SWP_DEVICE_READ, swp_offset(*entry));
पूर्ण

अटल अंतरभूत bool is_ग_लिखो_device_निजी_entry(swp_entry_t entry)
अणु
	वापस unlikely(swp_type(entry) == SWP_DEVICE_WRITE);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ device_निजी_entry_to_pfn(swp_entry_t entry)
अणु
	वापस swp_offset(entry);
पूर्ण

अटल अंतरभूत काष्ठा page *device_निजी_entry_to_page(swp_entry_t entry)
अणु
	वापस pfn_to_page(swp_offset(entry));
पूर्ण
#अन्यथा /* CONFIG_DEVICE_PRIVATE */
अटल अंतरभूत swp_entry_t make_device_निजी_entry(काष्ठा page *page, bool ग_लिखो)
अणु
	वापस swp_entry(0, 0);
पूर्ण

अटल अंतरभूत व्योम make_device_निजी_entry_पढ़ो(swp_entry_t *entry)
अणु
पूर्ण

अटल अंतरभूत bool is_device_निजी_entry(swp_entry_t entry)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool is_ग_लिखो_device_निजी_entry(swp_entry_t entry)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ device_निजी_entry_to_pfn(swp_entry_t entry)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा page *device_निजी_entry_to_page(swp_entry_t entry)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DEVICE_PRIVATE */

#अगर_घोषित CONFIG_MIGRATION
अटल अंतरभूत swp_entry_t make_migration_entry(काष्ठा page *page, पूर्णांक ग_लिखो)
अणु
	BUG_ON(!PageLocked(compound_head(page)));

	वापस swp_entry(ग_लिखो ? SWP_MIGRATION_WRITE : SWP_MIGRATION_READ,
			page_to_pfn(page));
पूर्ण

अटल अंतरभूत पूर्णांक is_migration_entry(swp_entry_t entry)
अणु
	वापस unlikely(swp_type(entry) == SWP_MIGRATION_READ ||
			swp_type(entry) == SWP_MIGRATION_WRITE);
पूर्ण

अटल अंतरभूत पूर्णांक is_ग_लिखो_migration_entry(swp_entry_t entry)
अणु
	वापस unlikely(swp_type(entry) == SWP_MIGRATION_WRITE);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ migration_entry_to_pfn(swp_entry_t entry)
अणु
	वापस swp_offset(entry);
पूर्ण

अटल अंतरभूत काष्ठा page *migration_entry_to_page(swp_entry_t entry)
अणु
	काष्ठा page *p = pfn_to_page(swp_offset(entry));
	/*
	 * Any use of migration entries may only occur जबतक the
	 * corresponding page is locked
	 */
	BUG_ON(!PageLocked(compound_head(p)));
	वापस p;
पूर्ण

अटल अंतरभूत व्योम make_migration_entry_पढ़ो(swp_entry_t *entry)
अणु
	*entry = swp_entry(SWP_MIGRATION_READ, swp_offset(*entry));
पूर्ण

बाह्य व्योम __migration_entry_रुको(काष्ठा mm_काष्ठा *mm, pte_t *ptep,
					spinlock_t *ptl);
बाह्य व्योम migration_entry_रुको(काष्ठा mm_काष्ठा *mm, pmd_t *pmd,
					अचिन्हित दीर्घ address);
बाह्य व्योम migration_entry_रुको_huge(काष्ठा vm_area_काष्ठा *vma,
		काष्ठा mm_काष्ठा *mm, pte_t *pte);
#अन्यथा

#घोषणा make_migration_entry(page, ग_लिखो) swp_entry(0, 0)
अटल अंतरभूत पूर्णांक is_migration_entry(swp_entry_t swp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ migration_entry_to_pfn(swp_entry_t entry)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा page *migration_entry_to_page(swp_entry_t entry)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम make_migration_entry_पढ़ो(swp_entry_t *entryp) अणु पूर्ण
अटल अंतरभूत व्योम __migration_entry_रुको(काष्ठा mm_काष्ठा *mm, pte_t *ptep,
					spinlock_t *ptl) अणु पूर्ण
अटल अंतरभूत व्योम migration_entry_रुको(काष्ठा mm_काष्ठा *mm, pmd_t *pmd,
					 अचिन्हित दीर्घ address) अणु पूर्ण
अटल अंतरभूत व्योम migration_entry_रुको_huge(काष्ठा vm_area_काष्ठा *vma,
		काष्ठा mm_काष्ठा *mm, pte_t *pte) अणु पूर्ण
अटल अंतरभूत पूर्णांक is_ग_लिखो_migration_entry(swp_entry_t entry)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

काष्ठा page_vma_mapped_walk;

#अगर_घोषित CONFIG_ARCH_ENABLE_THP_MIGRATION
बाह्य व्योम set_pmd_migration_entry(काष्ठा page_vma_mapped_walk *pvmw,
		काष्ठा page *page);

बाह्य व्योम हटाओ_migration_pmd(काष्ठा page_vma_mapped_walk *pvmw,
		काष्ठा page *new);

बाह्य व्योम pmd_migration_entry_रुको(काष्ठा mm_काष्ठा *mm, pmd_t *pmd);

अटल अंतरभूत swp_entry_t pmd_to_swp_entry(pmd_t pmd)
अणु
	swp_entry_t arch_entry;

	अगर (pmd_swp_soft_dirty(pmd))
		pmd = pmd_swp_clear_soft_dirty(pmd);
	arch_entry = __pmd_to_swp_entry(pmd);
	वापस swp_entry(__swp_type(arch_entry), __swp_offset(arch_entry));
पूर्ण

अटल अंतरभूत pmd_t swp_entry_to_pmd(swp_entry_t entry)
अणु
	swp_entry_t arch_entry;

	arch_entry = __swp_entry(swp_type(entry), swp_offset(entry));
	वापस __swp_entry_to_pmd(arch_entry);
पूर्ण

अटल अंतरभूत पूर्णांक is_pmd_migration_entry(pmd_t pmd)
अणु
	वापस !pmd_present(pmd) && is_migration_entry(pmd_to_swp_entry(pmd));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम set_pmd_migration_entry(काष्ठा page_vma_mapped_walk *pvmw,
		काष्ठा page *page)
अणु
	BUILD_BUG();
पूर्ण

अटल अंतरभूत व्योम हटाओ_migration_pmd(काष्ठा page_vma_mapped_walk *pvmw,
		काष्ठा page *new)
अणु
	BUILD_BUG();
पूर्ण

अटल अंतरभूत व्योम pmd_migration_entry_रुको(काष्ठा mm_काष्ठा *m, pmd_t *p) अणु पूर्ण

अटल अंतरभूत swp_entry_t pmd_to_swp_entry(pmd_t pmd)
अणु
	वापस swp_entry(0, 0);
पूर्ण

अटल अंतरभूत pmd_t swp_entry_to_pmd(swp_entry_t entry)
अणु
	वापस __pmd(0);
पूर्ण

अटल अंतरभूत पूर्णांक is_pmd_migration_entry(pmd_t pmd)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MEMORY_FAILURE

बाह्य atomic_दीर्घ_t num_poisoned_pages __पढ़ो_mostly;

/*
 * Support क्रम hardware poisoned pages
 */
अटल अंतरभूत swp_entry_t make_hwpoison_entry(काष्ठा page *page)
अणु
	BUG_ON(!PageLocked(page));
	वापस swp_entry(SWP_HWPOISON, page_to_pfn(page));
पूर्ण

अटल अंतरभूत पूर्णांक is_hwpoison_entry(swp_entry_t entry)
अणु
	वापस swp_type(entry) == SWP_HWPOISON;
पूर्ण

अटल अंतरभूत व्योम num_poisoned_pages_inc(व्योम)
अणु
	atomic_दीर्घ_inc(&num_poisoned_pages);
पूर्ण

अटल अंतरभूत व्योम num_poisoned_pages_dec(व्योम)
अणु
	atomic_दीर्घ_dec(&num_poisoned_pages);
पूर्ण

#अन्यथा

अटल अंतरभूत swp_entry_t make_hwpoison_entry(काष्ठा page *page)
अणु
	वापस swp_entry(0, 0);
पूर्ण

अटल अंतरभूत पूर्णांक is_hwpoison_entry(swp_entry_t swp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम num_poisoned_pages_inc(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_MEMORY_FAILURE) || defined(CONFIG_MIGRATION) || \
    defined(CONFIG_DEVICE_PRIVATE)
अटल अंतरभूत पूर्णांक non_swap_entry(swp_entry_t entry)
अणु
	वापस swp_type(entry) >= MAX_SWAPखाताS;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक non_swap_entry(swp_entry_t entry)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_MMU */
#पूर्ण_अगर /* _LINUX_SWAPOPS_H */
