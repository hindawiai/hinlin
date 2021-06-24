<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MIGRATE_H
#घोषणा _LINUX_MIGRATE_H

#समावेश <linux/mm.h>
#समावेश <linux/mempolicy.h>
#समावेश <linux/migrate_mode.h>
#समावेश <linux/hugetlb.h>

प्रकार काष्ठा page *new_page_t(काष्ठा page *page, अचिन्हित दीर्घ निजी);
प्रकार व्योम मुक्त_page_t(काष्ठा page *page, अचिन्हित दीर्घ निजी);

काष्ठा migration_target_control;

/*
 * Return values from addresss_space_operations.migratepage():
 * - negative त्रुटि_सं on page migration failure;
 * - zero on page migration success;
 */
#घोषणा MIGRATEPAGE_SUCCESS		0

क्रमागत migrate_reason अणु
	MR_COMPACTION,
	MR_MEMORY_FAILURE,
	MR_MEMORY_HOTPLUG,
	MR_SYSCALL,		/* also applies to cpusets */
	MR_MEMPOLICY_MBIND,
	MR_NUMA_MISPLACED,
	MR_CONTIG_RANGE,
	MR_LONGTERM_PIN,
	MR_TYPES
पूर्ण;

/* In mm/debug.c; also keep sync with include/trace/events/migrate.h */
बाह्य स्थिर अक्षर *migrate_reason_names[MR_TYPES];

#अगर_घोषित CONFIG_MIGRATION

बाह्य व्योम putback_movable_pages(काष्ठा list_head *l);
बाह्य पूर्णांक migrate_page(काष्ठा address_space *mapping,
			काष्ठा page *newpage, काष्ठा page *page,
			क्रमागत migrate_mode mode);
बाह्य पूर्णांक migrate_pages(काष्ठा list_head *l, new_page_t new, मुक्त_page_t मुक्त,
		अचिन्हित दीर्घ निजी, क्रमागत migrate_mode mode, पूर्णांक reason);
बाह्य काष्ठा page *alloc_migration_target(काष्ठा page *page, अचिन्हित दीर्घ निजी);
बाह्य पूर्णांक isolate_movable_page(काष्ठा page *page, isolate_mode_t mode);

बाह्य व्योम migrate_page_states(काष्ठा page *newpage, काष्ठा page *page);
बाह्य व्योम migrate_page_copy(काष्ठा page *newpage, काष्ठा page *page);
बाह्य पूर्णांक migrate_huge_page_move_mapping(काष्ठा address_space *mapping,
				  काष्ठा page *newpage, काष्ठा page *page);
बाह्य पूर्णांक migrate_page_move_mapping(काष्ठा address_space *mapping,
		काष्ठा page *newpage, काष्ठा page *page, पूर्णांक extra_count);
#अन्यथा

अटल अंतरभूत व्योम putback_movable_pages(काष्ठा list_head *l) अणुपूर्ण
अटल अंतरभूत पूर्णांक migrate_pages(काष्ठा list_head *l, new_page_t new,
		मुक्त_page_t मुक्त, अचिन्हित दीर्घ निजी, क्रमागत migrate_mode mode,
		पूर्णांक reason)
	अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत काष्ठा page *alloc_migration_target(काष्ठा page *page,
		अचिन्हित दीर्घ निजी)
	अणु वापस शून्य; पूर्ण
अटल अंतरभूत पूर्णांक isolate_movable_page(काष्ठा page *page, isolate_mode_t mode)
	अणु वापस -EBUSY; पूर्ण

अटल अंतरभूत व्योम migrate_page_states(काष्ठा page *newpage, काष्ठा page *page)
अणु
पूर्ण

अटल अंतरभूत व्योम migrate_page_copy(काष्ठा page *newpage,
				     काष्ठा page *page) अणुपूर्ण

अटल अंतरभूत पूर्णांक migrate_huge_page_move_mapping(काष्ठा address_space *mapping,
				  काष्ठा page *newpage, काष्ठा page *page)
अणु
	वापस -ENOSYS;
पूर्ण

#पूर्ण_अगर /* CONFIG_MIGRATION */

#अगर_घोषित CONFIG_COMPACTION
बाह्य पूर्णांक PageMovable(काष्ठा page *page);
बाह्य व्योम __SetPageMovable(काष्ठा page *page, काष्ठा address_space *mapping);
बाह्य व्योम __ClearPageMovable(काष्ठा page *page);
#अन्यथा
अटल अंतरभूत पूर्णांक PageMovable(काष्ठा page *page) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम __SetPageMovable(काष्ठा page *page,
				काष्ठा address_space *mapping)
अणु
पूर्ण
अटल अंतरभूत व्योम __ClearPageMovable(काष्ठा page *page)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NUMA_BALANCING
बाह्य bool pmd_trans_migrating(pmd_t pmd);
बाह्य पूर्णांक migrate_misplaced_page(काष्ठा page *page,
				  काष्ठा vm_area_काष्ठा *vma, पूर्णांक node);
#अन्यथा
अटल अंतरभूत bool pmd_trans_migrating(pmd_t pmd)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत पूर्णांक migrate_misplaced_page(काष्ठा page *page,
					 काष्ठा vm_area_काष्ठा *vma, पूर्णांक node)
अणु
	वापस -EAGAIN; /* can't migrate now */
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */

#अगर defined(CONFIG_NUMA_BALANCING) && defined(CONFIG_TRANSPARENT_HUGEPAGE)
बाह्य पूर्णांक migrate_misplaced_transhuge_page(काष्ठा mm_काष्ठा *mm,
			काष्ठा vm_area_काष्ठा *vma,
			pmd_t *pmd, pmd_t entry,
			अचिन्हित दीर्घ address,
			काष्ठा page *page, पूर्णांक node);
#अन्यथा
अटल अंतरभूत पूर्णांक migrate_misplaced_transhuge_page(काष्ठा mm_काष्ठा *mm,
			काष्ठा vm_area_काष्ठा *vma,
			pmd_t *pmd, pmd_t entry,
			अचिन्हित दीर्घ address,
			काष्ठा page *page, पूर्णांक node)
अणु
	वापस -EAGAIN;
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING && CONFIG_TRANSPARENT_HUGEPAGE*/


#अगर_घोषित CONFIG_MIGRATION

/*
 * Watch out क्रम PAE architecture, which has an अचिन्हित दीर्घ, and might not
 * have enough bits to store all physical address and flags. So far we have
 * enough room क्रम all our flags.
 */
#घोषणा MIGRATE_PFN_VALID	(1UL << 0)
#घोषणा MIGRATE_PFN_MIGRATE	(1UL << 1)
#घोषणा MIGRATE_PFN_LOCKED	(1UL << 2)
#घोषणा MIGRATE_PFN_WRITE	(1UL << 3)
#घोषणा MIGRATE_PFN_SHIFT	6

अटल अंतरभूत काष्ठा page *migrate_pfn_to_page(अचिन्हित दीर्घ mpfn)
अणु
	अगर (!(mpfn & MIGRATE_PFN_VALID))
		वापस शून्य;
	वापस pfn_to_page(mpfn >> MIGRATE_PFN_SHIFT);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ migrate_pfn(अचिन्हित दीर्घ pfn)
अणु
	वापस (pfn << MIGRATE_PFN_SHIFT) | MIGRATE_PFN_VALID;
पूर्ण

क्रमागत migrate_vma_direction अणु
	MIGRATE_VMA_SELECT_SYSTEM = 1 << 0,
	MIGRATE_VMA_SELECT_DEVICE_PRIVATE = 1 << 1,
पूर्ण;

काष्ठा migrate_vma अणु
	काष्ठा vm_area_काष्ठा	*vma;
	/*
	 * Both src and dst array must be big enough क्रम
	 * (end - start) >> PAGE_SHIFT entries.
	 *
	 * The src array must not be modअगरied by the caller after
	 * migrate_vma_setup(), and must not change the dst array after
	 * migrate_vma_pages() वापसs.
	 */
	अचिन्हित दीर्घ		*dst;
	अचिन्हित दीर्घ		*src;
	अचिन्हित दीर्घ		cpages;
	अचिन्हित दीर्घ		npages;
	अचिन्हित दीर्घ		start;
	अचिन्हित दीर्घ		end;

	/*
	 * Set to the owner value also stored in page->pgmap->owner क्रम
	 * migrating out of device निजी memory. The flags also need to
	 * be set to MIGRATE_VMA_SELECT_DEVICE_PRIVATE.
	 * The caller should always set this field when using mmu notअगरier
	 * callbacks to aव्योम device MMU invalidations क्रम device निजी
	 * pages that are not being migrated.
	 */
	व्योम			*pgmap_owner;
	अचिन्हित दीर्घ		flags;
पूर्ण;

पूर्णांक migrate_vma_setup(काष्ठा migrate_vma *args);
व्योम migrate_vma_pages(काष्ठा migrate_vma *migrate);
व्योम migrate_vma_finalize(काष्ठा migrate_vma *migrate);

#पूर्ण_अगर /* CONFIG_MIGRATION */

#पूर्ण_अगर /* _LINUX_MIGRATE_H */
