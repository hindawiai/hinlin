<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_64_HASH_64K_H
#घोषणा _ASM_POWERPC_BOOK3S_64_HASH_64K_H

#घोषणा H_PTE_INDEX_SIZE   8  // size: 8B <<  8 = 2KB, maps 2^8  x 64KB = 16MB
#घोषणा H_PMD_INDEX_SIZE  10  // size: 8B << 10 = 8KB, maps 2^10 x 16MB = 16GB
#घोषणा H_PUD_INDEX_SIZE  10  // size: 8B << 10 = 8KB, maps 2^10 x 16GB = 16TB
#घोषणा H_PGD_INDEX_SIZE   8  // size: 8B <<  8 = 2KB, maps 2^8  x 16TB =  4PB

/*
 * If we store section details in page->flags we can't increase the MAX_PHYSMEM_BITS
 * अगर we increase SECTIONS_WIDTH we will not store node details in page->flags and
 * page_to_nid करोes a page->section->node lookup
 * Hence only increase क्रम VMEMMAP. Further depending on SPARSEMEM_EXTREME reduce
 * memory requirements with large number of sections.
 * 51 bits is the max physical real address on POWER9
 */
#अगर defined(CONFIG_SPARSEMEM_VMEMMAP) && defined(CONFIG_SPARSEMEM_EXTREME)
#घोषणा H_MAX_PHYSMEM_BITS	51
#अन्यथा
#घोषणा H_MAX_PHYSMEM_BITS	46
#पूर्ण_अगर

/*
 * Each context is 512TB size. SLB miss क्रम first context/शेष context
 * is handled in the hotpath.
 */
#घोषणा MAX_EA_BITS_PER_CONTEXT		49
#घोषणा REGION_SHIFT		MAX_EA_BITS_PER_CONTEXT

/*
 * We use one context क्रम each MAP area.
 */
#घोषणा H_KERN_MAP_SIZE		(1UL << MAX_EA_BITS_PER_CONTEXT)

/*
 * Define the address range of the kernel non-linear भव area
 * 2PB
 */
#घोषणा H_KERN_VIRT_START	ASM_CONST(0xc008000000000000)

/*
 * 64k aligned address मुक्त up few of the lower bits of RPN क्रम us
 * We steal that here. For more deatils look at pte_pfn/pfn_pte()
 */
#घोषणा H_PAGE_COMBO	_RPAGE_RPN0 /* this is a combo 4k page */
#घोषणा H_PAGE_4K_PFN	_RPAGE_RPN1 /* PFN is क्रम a single 4k page */
#घोषणा H_PAGE_BUSY	_RPAGE_RSV1     /* software: PTE & hash are busy */
#घोषणा H_PAGE_HASHPTE	_RPAGE_RPN43	/* PTE has associated HPTE */

/* memory key bits. */
#घोषणा H_PTE_PKEY_BIT4		_RPAGE_PKEY_BIT4
#घोषणा H_PTE_PKEY_BIT3		_RPAGE_PKEY_BIT3
#घोषणा H_PTE_PKEY_BIT2		_RPAGE_PKEY_BIT2
#घोषणा H_PTE_PKEY_BIT1		_RPAGE_PKEY_BIT1
#घोषणा H_PTE_PKEY_BIT0		_RPAGE_PKEY_BIT0

/*
 * We need to dअगरferentiate between explicit huge page and THP huge
 * page, since THP huge page also need to track real subpage details
 */
#घोषणा H_PAGE_THP_HUGE  H_PAGE_4K_PFN

/* PTE flags to conserve क्रम HPTE identअगरication */
#घोषणा _PAGE_HPTEFLAGS (H_PAGE_BUSY | H_PAGE_HASHPTE | H_PAGE_COMBO)
/*
 * We use a 2K PTE page fragment and another 2K क्रम storing
 * real_pte_t hash index
 * 8 bytes per each pte entry and another 8 bytes क्रम storing
 * slot details.
 */
#घोषणा H_PTE_FRAG_SIZE_SHIFT  (H_PTE_INDEX_SIZE + 3 + 1)
#घोषणा H_PTE_FRAG_NR	(PAGE_SIZE >> H_PTE_FRAG_SIZE_SHIFT)

#अगर defined(CONFIG_TRANSPARENT_HUGEPAGE) || defined(CONFIG_HUGETLB_PAGE)
#घोषणा H_PMD_FRAG_SIZE_SHIFT  (H_PMD_INDEX_SIZE + 3 + 1)
#अन्यथा
#घोषणा H_PMD_FRAG_SIZE_SHIFT  (H_PMD_INDEX_SIZE + 3)
#पूर्ण_अगर
#घोषणा H_PMD_FRAG_NR	(PAGE_SIZE >> H_PMD_FRAG_SIZE_SHIFT)

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/त्रुटिसं.स>

/*
 * With 64K pages on hash table, we have a special PTE क्रमmat that
 * uses a second "half" of the page table to encode sub-page inक्रमmation
 * in order to deal with 64K made of 4K HW pages. Thus we override the
 * generic accessors and iterators here
 */
#घोषणा __real_pte __real_pte
अटल अंतरभूत real_pte_t __real_pte(pte_t pte, pte_t *ptep, पूर्णांक offset)
अणु
	real_pte_t rpte;
	अचिन्हित दीर्घ *hidxp;

	rpte.pte = pte;

	/*
	 * Ensure that we करो not पढ़ो the hidx beक्रमe we पढ़ो the PTE. Because
	 * the ग_लिखोr side is expected to finish writing the hidx first followed
	 * by the PTE, by using smp_wmb(). pte_set_hash_slot() ensures that.
	 */
	smp_rmb();

	hidxp = (अचिन्हित दीर्घ *)(ptep + offset);
	rpte.hidx = *hidxp;
	वापस rpte;
पूर्ण

/*
 * shअगरt the hidx representation by one-modulo-0xf; i.e hidx 0 is respresented
 * as 1, 1 as 2,... , and 0xf as 0.  This convention lets us represent a
 * invalid hidx 0xf with a 0x0 bit value. PTEs are anyway zero'd when
 * allocated. We करोnt have to zero them gain; thus save on the initialization.
 */
#घोषणा HIDX_UNSHIFT_BY_ONE(x) ((x + 0xfUL) & 0xfUL) /* shअगरt backward by one */
#घोषणा HIDX_SHIFT_BY_ONE(x) ((x + 0x1UL) & 0xfUL)   /* shअगरt क्रमward by one */
#घोषणा HIDX_BITS(x, index)  (x << (index << 2))
#घोषणा BITS_TO_HIDX(x, index)  ((x >> (index << 2)) & 0xfUL)
#घोषणा INVALID_RPTE_HIDX  0x0UL

अटल अंतरभूत अचिन्हित दीर्घ __rpte_to_hidx(real_pte_t rpte, अचिन्हित दीर्घ index)
अणु
	वापस HIDX_UNSHIFT_BY_ONE(BITS_TO_HIDX(rpte.hidx, index));
पूर्ण

/*
 * Commit the hidx and वापस PTE bits that needs to be modअगरied. The caller is
 * expected to modअगरy the PTE bits accordingly and commit the PTE to memory.
 */
अटल अंतरभूत अचिन्हित दीर्घ pte_set_hidx(pte_t *ptep, real_pte_t rpte,
					 अचिन्हित पूर्णांक subpg_index,
					 अचिन्हित दीर्घ hidx, पूर्णांक offset)
अणु
	अचिन्हित दीर्घ *hidxp = (अचिन्हित दीर्घ *)(ptep + offset);

	rpte.hidx &= ~HIDX_BITS(0xfUL, subpg_index);
	*hidxp = rpte.hidx  | HIDX_BITS(HIDX_SHIFT_BY_ONE(hidx), subpg_index);

	/*
	 * Anyone पढ़ोing PTE must ensure hidx bits are पढ़ो after पढ़ोing the
	 * PTE by using the पढ़ो-side barrier smp_rmb(). __real_pte() can be
	 * used क्रम that.
	 */
	smp_wmb();

	/* No PTE bits to be modअगरied, वापस 0x0UL */
	वापस 0x0UL;
पूर्ण

#घोषणा __rpte_to_pte(r)	((r).pte)
बाह्य bool __rpte_sub_valid(real_pte_t rpte, अचिन्हित दीर्घ index);
/*
 * Trick: we set __end to va + 64k, which happens works क्रम
 * a 16M page as well as we want only one iteration
 */
#घोषणा pte_iterate_hashed_subpages(rpte, psize, vpn, index, shअगरt)	\
	करो अणु								\
		अचिन्हित दीर्घ __end = vpn + (1UL << (PAGE_SHIFT - VPN_SHIFT));	\
		अचिन्हित __split = (psize == MMU_PAGE_4K ||		\
				    psize == MMU_PAGE_64K_AP);		\
		shअगरt = mmu_psize_defs[psize].shअगरt;			\
		क्रम (index = 0; vpn < __end; index++,			\
			     vpn += (1L << (shअगरt - VPN_SHIFT))) अणु	\
		अगर (!__split || __rpte_sub_valid(rpte, index))

#घोषणा pte_iterate_hashed_end()  पूर्ण पूर्ण जबतक(0)

#घोषणा pte_pagesize_index(mm, addr, pte)	\
	(((pte) & H_PAGE_COMBO)? MMU_PAGE_4K: MMU_PAGE_64K)

बाह्य पूर्णांक remap_pfn_range(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ addr,
			   अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size, pgprot_t);
अटल अंतरभूत पूर्णांक hash__remap_4k_pfn(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
				 अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	अगर (pfn > (PTE_RPN_MASK >> PAGE_SHIFT)) अणु
		WARN(1, "remap_4k_pfn called with wrong pfn value\n");
		वापस -EINVAL;
	पूर्ण
	वापस remap_pfn_range(vma, addr, pfn, PAGE_SIZE,
			       __pgprot(pgprot_val(prot) | H_PAGE_4K_PFN));
पूर्ण

#घोषणा H_PTE_TABLE_SIZE	PTE_FRAG_SIZE
#अगर defined(CONFIG_TRANSPARENT_HUGEPAGE) || defined (CONFIG_HUGETLB_PAGE)
#घोषणा H_PMD_TABLE_SIZE	((माप(pmd_t) << PMD_INDEX_SIZE) + \
				 (माप(अचिन्हित दीर्घ) << PMD_INDEX_SIZE))
#अन्यथा
#घोषणा H_PMD_TABLE_SIZE	(माप(pmd_t) << PMD_INDEX_SIZE)
#पूर्ण_अगर
#अगर_घोषित CONFIG_HUGETLB_PAGE
#घोषणा H_PUD_TABLE_SIZE	((माप(pud_t) << PUD_INDEX_SIZE) +	\
				 (माप(अचिन्हित दीर्घ) << PUD_INDEX_SIZE))
#अन्यथा
#घोषणा H_PUD_TABLE_SIZE	(माप(pud_t) << PUD_INDEX_SIZE)
#पूर्ण_अगर
#घोषणा H_PGD_TABLE_SIZE	(माप(pgd_t) << PGD_INDEX_SIZE)

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल अंतरभूत अक्षर *get_hpte_slot_array(pmd_t *pmdp)
अणु
	/*
	 * The hpte hindex is stored in the pgtable whose address is in the
	 * second half of the PMD
	 *
	 * Order this load with the test क्रम pmd_trans_huge in the caller
	 */
	smp_rmb();
	वापस *(अक्षर **)(pmdp + PTRS_PER_PMD);


पूर्ण
/*
 * The linux hugepage PMD now include the pmd entries followed by the address
 * to the stashed pgtable_t. The stashed pgtable_t contains the hpte bits.
 * [ 000 | 1 bit secondary | 3 bit hidx | 1 bit valid]. We use one byte per
 * each HPTE entry. With 16MB hugepage and 64K HPTE we need 256 entries and
 * with 4K HPTE we need 4096 entries. Both will fit in a 4K pgtable_t.
 *
 * The top three bits are पूर्णांकentionally left as zero. This memory location
 * are also used as normal page PTE poपूर्णांकers. So अगर we have any poपूर्णांकers
 * left around जबतक we collapse a hugepage, we need to make sure
 * _PAGE_PRESENT bit of that is zero when we look at them
 */
अटल अंतरभूत अचिन्हित पूर्णांक hpte_valid(अचिन्हित अक्षर *hpte_slot_array, पूर्णांक index)
अणु
	वापस hpte_slot_array[index] & 0x1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक hpte_hash_index(अचिन्हित अक्षर *hpte_slot_array,
					   पूर्णांक index)
अणु
	वापस hpte_slot_array[index] >> 1;
पूर्ण

अटल अंतरभूत व्योम mark_hpte_slot_valid(अचिन्हित अक्षर *hpte_slot_array,
					अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक hidx)
अणु
	hpte_slot_array[index] = (hidx << 1) | 0x1;
पूर्ण

/*
 *
 * For core kernel code by design pmd_trans_huge is never run on any hugetlbfs
 * page. The hugetlbfs page table walking and mangling paths are totally
 * separated क्रमm the core VM paths and they're dअगरferentiated by
 *  VM_HUGETLB being set on vm_flags well beक्रमe any pmd_trans_huge could run.
 *
 * pmd_trans_huge() is defined as false at build समय अगर
 * CONFIG_TRANSPARENT_HUGEPAGE=n to optimize away code blocks at build
 * समय in such हाल.
 *
 * For ppc64 we need to dअगरferntiate from explicit hugepages from THP, because
 * क्रम THP we also track the subpage details at the pmd level. We करोn't करो
 * that क्रम explicit huge pages.
 *
 */
अटल अंतरभूत पूर्णांक hash__pmd_trans_huge(pmd_t pmd)
अणु
	वापस !!((pmd_val(pmd) & (_PAGE_PTE | H_PAGE_THP_HUGE | _PAGE_DEVMAP)) ==
		  (_PAGE_PTE | H_PAGE_THP_HUGE));
पूर्ण

अटल अंतरभूत पूर्णांक hash__pmd_same(pmd_t pmd_a, pmd_t pmd_b)
अणु
	वापस (((pmd_raw(pmd_a) ^ pmd_raw(pmd_b)) & ~cpu_to_be64(_PAGE_HPTEFLAGS)) == 0);
पूर्ण

अटल अंतरभूत pmd_t hash__pmd_mkhuge(pmd_t pmd)
अणु
	वापस __pmd(pmd_val(pmd) | (_PAGE_PTE | H_PAGE_THP_HUGE));
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
#पूर्ण_अगर /*  CONFIG_TRANSPARENT_HUGEPAGE */

अटल अंतरभूत pmd_t hash__pmd_mkdevmap(pmd_t pmd)
अणु
	वापस __pmd(pmd_val(pmd) | (_PAGE_PTE | H_PAGE_THP_HUGE | _PAGE_DEVMAP));
पूर्ण

#पूर्ण_अगर	/* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_POWERPC_BOOK3S_64_HASH_64K_H */
