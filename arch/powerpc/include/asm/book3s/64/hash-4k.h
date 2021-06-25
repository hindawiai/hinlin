<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_64_HASH_4K_H
#घोषणा _ASM_POWERPC_BOOK3S_64_HASH_4K_H

#घोषणा H_PTE_INDEX_SIZE  9  // size: 8B << 9 = 4KB, maps: 2^9 x   4KB =   2MB
#घोषणा H_PMD_INDEX_SIZE  7  // size: 8B << 7 = 1KB, maps: 2^7 x   2MB = 256MB
#घोषणा H_PUD_INDEX_SIZE  9  // size: 8B << 9 = 4KB, maps: 2^9 x 256MB = 128GB
#घोषणा H_PGD_INDEX_SIZE  9  // size: 8B << 9 = 4KB, maps: 2^9 x 128GB =  64TB

/*
 * Each context is 512TB. But on 4k we restrict our max TASK size to 64TB
 * Hence also limit max EA bits to 64TB.
 */
#घोषणा MAX_EA_BITS_PER_CONTEXT		46


/*
 * Our page table limit us to 64TB. For 64TB physical memory, we only need 64GB
 * of vmemmap space. To better support sparse memory layout, we use 61TB
 * linear map range, 1TB of vदो_स्मृति, 1TB of I/O and 1TB of vmememmap.
 */
#घोषणा REGION_SHIFT		(40)
#घोषणा H_KERN_MAP_SIZE		(ASM_CONST(1) << REGION_SHIFT)

/*
 * Limits the linear mapping range
 */
#घोषणा H_MAX_PHYSMEM_BITS	46

/*
 * Define the address range of the kernel non-linear भव area (61TB)
 */
#घोषणा H_KERN_VIRT_START	ASM_CONST(0xc0003d0000000000)

#अगर_अघोषित __ASSEMBLY__
#घोषणा H_PTE_TABLE_SIZE	(माप(pte_t) << H_PTE_INDEX_SIZE)
#घोषणा H_PMD_TABLE_SIZE	(माप(pmd_t) << H_PMD_INDEX_SIZE)
#घोषणा H_PUD_TABLE_SIZE	(माप(pud_t) << H_PUD_INDEX_SIZE)
#घोषणा H_PGD_TABLE_SIZE	(माप(pgd_t) << H_PGD_INDEX_SIZE)

#घोषणा H_PAGE_F_GIX_SHIFT	_PAGE_PA_MAX
#घोषणा H_PAGE_F_SECOND		_RPAGE_PKEY_BIT0 /* HPTE is in 2ndary HPTEG */
#घोषणा H_PAGE_F_GIX		(_RPAGE_RPN43 | _RPAGE_RPN42 | _RPAGE_RPN41)
#घोषणा H_PAGE_BUSY		_RPAGE_RSV1
#घोषणा H_PAGE_HASHPTE		_RPAGE_PKEY_BIT4

/* PTE flags to conserve क्रम HPTE identअगरication */
#घोषणा _PAGE_HPTEFLAGS (H_PAGE_BUSY | H_PAGE_HASHPTE | \
			 H_PAGE_F_SECOND | H_PAGE_F_GIX)
/*
 * Not supported by 4k linux page size
 */
#घोषणा H_PAGE_4K_PFN	0x0
#घोषणा H_PAGE_THP_HUGE 0x0
#घोषणा H_PAGE_COMBO	0x0

/* 8 bytes per each pte entry */
#घोषणा H_PTE_FRAG_SIZE_SHIFT  (H_PTE_INDEX_SIZE + 3)
#घोषणा H_PTE_FRAG_NR	(PAGE_SIZE >> H_PTE_FRAG_SIZE_SHIFT)
#घोषणा H_PMD_FRAG_SIZE_SHIFT  (H_PMD_INDEX_SIZE + 3)
#घोषणा H_PMD_FRAG_NR	(PAGE_SIZE >> H_PMD_FRAG_SIZE_SHIFT)

/* memory key bits, only 8 keys supported */
#घोषणा H_PTE_PKEY_BIT4	0
#घोषणा H_PTE_PKEY_BIT3	0
#घोषणा H_PTE_PKEY_BIT2	_RPAGE_PKEY_BIT3
#घोषणा H_PTE_PKEY_BIT1	_RPAGE_PKEY_BIT2
#घोषणा H_PTE_PKEY_BIT0	_RPAGE_PKEY_BIT1


/*
 * On all 4K setups, remap_4k_pfn() equates to remap_pfn_range()
 */
#घोषणा remap_4k_pfn(vma, addr, pfn, prot)	\
	remap_pfn_range((vma), (addr), (pfn), PAGE_SIZE, (prot))

#अगर_घोषित CONFIG_HUGETLB_PAGE
अटल अंतरभूत पूर्णांक hash__hugepd_ok(hugepd_t hpd)
अणु
	अचिन्हित दीर्घ hpdval = hpd_val(hpd);
	/*
	 * अगर it is not a pte and have hugepd shअगरt mask
	 * set, then it is a hugepd directory poपूर्णांकer
	 */
	अगर (!(hpdval & _PAGE_PTE) && (hpdval & _PAGE_PRESENT) &&
	    ((hpdval & HUGEPD_SHIFT_MASK) != 0))
		वापस true;
	वापस false;
पूर्ण
#पूर्ण_अगर

/*
 * 4K PTE क्रमmat is dअगरferent from 64K PTE क्रमmat. Saving the hash_slot is just
 * a matter of वापसing the PTE bits that need to be modअगरied. On 64K PTE,
 * things are a little more involved and hence needs many more parameters to
 * accomplish the same. However we want to असलtract this out from the caller by
 * keeping the prototype consistent across the two क्रमmats.
 */
अटल अंतरभूत अचिन्हित दीर्घ pte_set_hidx(pte_t *ptep, real_pte_t rpte,
					 अचिन्हित पूर्णांक subpg_index, अचिन्हित दीर्घ hidx,
					 पूर्णांक offset)
अणु
	वापस (hidx << H_PAGE_F_GIX_SHIFT) &
		(H_PAGE_F_SECOND | H_PAGE_F_GIX);
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE

अटल अंतरभूत अक्षर *get_hpte_slot_array(pmd_t *pmdp)
अणु
	BUG();
	वापस शून्य;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक hpte_valid(अचिन्हित अक्षर *hpte_slot_array, पूर्णांक index)
अणु
	BUG();
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक hpte_hash_index(अचिन्हित अक्षर *hpte_slot_array,
					   पूर्णांक index)
अणु
	BUG();
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mark_hpte_slot_valid(अचिन्हित अक्षर *hpte_slot_array,
					अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक hidx)
अणु
	BUG();
पूर्ण

अटल अंतरभूत पूर्णांक hash__pmd_trans_huge(pmd_t pmd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक hash__pmd_same(pmd_t pmd_a, pmd_t pmd_b)
अणु
	BUG();
	वापस 0;
पूर्ण

अटल अंतरभूत pmd_t hash__pmd_mkhuge(pmd_t pmd)
अणु
	BUG();
	वापस pmd;
पूर्ण

बाह्य अचिन्हित दीर्घ hash__pmd_hugepage_update(काष्ठा mm_काष्ठा *mm,
					   अचिन्हित दीर्घ addr, pmd_t *pmdp,
					   अचिन्हित दीर्घ clr, अचिन्हित दीर्घ set);
बाह्य pmd_t hash__pmdp_collapse_flush(काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ address, pmd_t *pmdp);
बाह्य व्योम hash__pgtable_trans_huge_deposit(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp,
					 pgtable_t pgtable);
बाह्य pgtable_t hash__pgtable_trans_huge_withdraw(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp);
बाह्य pmd_t hash__pmdp_huge_get_and_clear(काष्ठा mm_काष्ठा *mm,
				       अचिन्हित दीर्घ addr, pmd_t *pmdp);
बाह्य पूर्णांक hash__has_transparent_hugepage(व्योम);
#पूर्ण_अगर

अटल अंतरभूत pmd_t hash__pmd_mkdevmap(pmd_t pmd)
अणु
	BUG();
	वापस pmd;
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_POWERPC_BOOK3S_64_HASH_4K_H */
