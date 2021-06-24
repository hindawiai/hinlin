<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_PGTABLE_RADIX_H
#घोषणा _ASM_POWERPC_PGTABLE_RADIX_H

#समावेश <यंत्र/यंत्र-स्थिर.h>

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/cmpxchg.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_64K_PAGES
#समावेश <यंत्र/book3s/64/radix-64k.h>
#अन्यथा
#समावेश <यंत्र/book3s/64/radix-4k.h>
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/book3s/64/tlbflush-radix.h>
#समावेश <यंत्र/cpu_has_feature.h>
#पूर्ण_अगर

/* An empty PTE can still have a R or C ग_लिखोback */
#घोषणा RADIX_PTE_NONE_MASK		(_PAGE_सूचीTY | _PAGE_ACCESSED)

/* Bits to set in a RPMD/RPUD/RPGD */
#घोषणा RADIX_PMD_VAL_BITS		(0x8000000000000000UL | RADIX_PTE_INDEX_SIZE)
#घोषणा RADIX_PUD_VAL_BITS		(0x8000000000000000UL | RADIX_PMD_INDEX_SIZE)
#घोषणा RADIX_PGD_VAL_BITS		(0x8000000000000000UL | RADIX_PUD_INDEX_SIZE)

/* Don't have anything in the reserved bits and leaf bits */
#घोषणा RADIX_PMD_BAD_BITS		0x60000000000000e0UL
#घोषणा RADIX_PUD_BAD_BITS		0x60000000000000e0UL
#घोषणा RADIX_P4D_BAD_BITS		0x60000000000000e0UL

#घोषणा RADIX_PMD_SHIFT		(PAGE_SHIFT + RADIX_PTE_INDEX_SIZE)
#घोषणा RADIX_PUD_SHIFT		(RADIX_PMD_SHIFT + RADIX_PMD_INDEX_SIZE)
#घोषणा RADIX_PGD_SHIFT		(RADIX_PUD_SHIFT + RADIX_PUD_INDEX_SIZE)
/*
 * Size of EA range mapped by our pagetables.
 */
#घोषणा RADIX_PGTABLE_EADDR_SIZE (RADIX_PTE_INDEX_SIZE + RADIX_PMD_INDEX_SIZE +	\
			      RADIX_PUD_INDEX_SIZE + RADIX_PGD_INDEX_SIZE + PAGE_SHIFT)
#घोषणा RADIX_PGTABLE_RANGE (ASM_CONST(1) << RADIX_PGTABLE_EADDR_SIZE)

/*
 * We support 52 bit address space, Use top bit क्रम kernel
 * भव mapping. Also make sure kernel fit in the top
 * quadrant.
 *
 *           +------------------+
 *           +------------------+  Kernel भव map (0xc008000000000000)
 *           |                  |
 *           |                  |
 *           |                  |
 * 0b11......+------------------+  Kernel linear map (0xc....)
 *           |                  |
 *           |     2 quadrant   |
 *           |                  |
 * 0b10......+------------------+
 *           |                  |
 *           |    1 quadrant    |
 *           |                  |
 * 0b01......+------------------+
 *           |                  |
 *           |    0 quadrant    |
 *           |                  |
 * 0b00......+------------------+
 *
 *
 * 3rd quadrant expanded:
 * +------------------------------+
 * |                              |
 * |                              |
 * |                              |
 * +------------------------------+  Kernel vmemmap end (0xc010000000000000)
 * |                              |
 * |           512TB		  |
 * |                              |
 * +------------------------------+  Kernel IO map end/vmemap start
 * |                              |
 * |           512TB		  |
 * |                              |
 * +------------------------------+  Kernel vmap end/ IO map start
 * |                              |
 * |           512TB		  |
 * |                              |
 * +------------------------------+  Kernel virt start (0xc008000000000000)
 * |                              |
 * |                              |
 * |                              |
 * +------------------------------+  Kernel linear (0xc.....)
 */


/*
 * If we store section details in page->flags we can't increase the MAX_PHYSMEM_BITS
 * अगर we increase SECTIONS_WIDTH we will not store node details in page->flags and
 * page_to_nid करोes a page->section->node lookup
 * Hence only increase क्रम VMEMMAP. Further depending on SPARSEMEM_EXTREME reduce
 * memory requirements with large number of sections.
 * 51 bits is the max physical real address on POWER9
 */

#अगर defined(CONFIG_SPARSEMEM_VMEMMAP) && defined(CONFIG_SPARSEMEM_EXTREME)
#घोषणा R_MAX_PHYSMEM_BITS	51
#अन्यथा
#घोषणा R_MAX_PHYSMEM_BITS	46
#पूर्ण_अगर

#घोषणा RADIX_KERN_VIRT_START	ASM_CONST(0xc008000000000000)
/*
 * 49 =  MAX_EA_BITS_PER_CONTEXT (hash specअगरic). To make sure we pick
 * the same value as hash.
 */
#घोषणा RADIX_KERN_MAP_SIZE	(1UL << 49)

#घोषणा RADIX_VMALLOC_START	RADIX_KERN_VIRT_START
#घोषणा RADIX_VMALLOC_SIZE	RADIX_KERN_MAP_SIZE
#घोषणा RADIX_VMALLOC_END	(RADIX_VMALLOC_START + RADIX_VMALLOC_SIZE)

#घोषणा RADIX_KERN_IO_START	RADIX_VMALLOC_END
#घोषणा RADIX_KERN_IO_SIZE	RADIX_KERN_MAP_SIZE
#घोषणा RADIX_KERN_IO_END	(RADIX_KERN_IO_START + RADIX_KERN_IO_SIZE)

#घोषणा RADIX_VMEMMAP_START	RADIX_KERN_IO_END
#घोषणा RADIX_VMEMMAP_SIZE	RADIX_KERN_MAP_SIZE
#घोषणा RADIX_VMEMMAP_END	(RADIX_VMEMMAP_START + RADIX_VMEMMAP_SIZE)

#अगर_अघोषित __ASSEMBLY__
#घोषणा RADIX_PTE_TABLE_SIZE	(माप(pte_t) << RADIX_PTE_INDEX_SIZE)
#घोषणा RADIX_PMD_TABLE_SIZE	(माप(pmd_t) << RADIX_PMD_INDEX_SIZE)
#घोषणा RADIX_PUD_TABLE_SIZE	(माप(pud_t) << RADIX_PUD_INDEX_SIZE)
#घोषणा RADIX_PGD_TABLE_SIZE	(माप(pgd_t) << RADIX_PGD_INDEX_SIZE)

#अगर_घोषित CONFIG_STRICT_KERNEL_RWX
बाह्य व्योम radix__mark_rodata_ro(व्योम);
बाह्य व्योम radix__mark_iniपंचांगem_nx(व्योम);
#पूर्ण_अगर

बाह्य व्योम radix__ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma, pte_t *ptep,
					 pte_t entry, अचिन्हित दीर्घ address,
					 पूर्णांक psize);

बाह्य व्योम radix__ptep_modअगरy_prot_commit(काष्ठा vm_area_काष्ठा *vma,
					   अचिन्हित दीर्घ addr, pte_t *ptep,
					   pte_t old_pte, pte_t pte);

अटल अंतरभूत अचिन्हित दीर्घ __radix_pte_update(pte_t *ptep, अचिन्हित दीर्घ clr,
					       अचिन्हित दीर्घ set)
अणु
	__be64 old_be, पंचांगp_be;

	__यंत्र__ __अस्थिर__(
	"1:	ldarx	%0,0,%3		# pte_update\n"
	"	andc	%1,%0,%5	\n"
	"	or	%1,%1,%4	\n"
	"	stdcx.	%1,0,%3		\n"
	"	bne-	1b"
	: "=&r" (old_be), "=&r" (पंचांगp_be), "=m" (*ptep)
	: "r" (ptep), "r" (cpu_to_be64(set)), "r" (cpu_to_be64(clr))
	: "cc" );

	वापस be64_to_cpu(old_be);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ radix__pte_update(काष्ठा mm_काष्ठा *mm,
					अचिन्हित दीर्घ addr,
					pte_t *ptep, अचिन्हित दीर्घ clr,
					अचिन्हित दीर्घ set,
					पूर्णांक huge)
अणु
	अचिन्हित दीर्घ old_pte;

	old_pte = __radix_pte_update(ptep, clr, set);
	अगर (!huge)
		निश्चित_pte_locked(mm, addr);

	वापस old_pte;
पूर्ण

अटल अंतरभूत pte_t radix__ptep_get_and_clear_full(काष्ठा mm_काष्ठा *mm,
						   अचिन्हित दीर्घ addr,
						   pte_t *ptep, पूर्णांक full)
अणु
	अचिन्हित दीर्घ old_pte;

	अगर (full) अणु
		old_pte = pte_val(*ptep);
		*ptep = __pte(0);
	पूर्ण अन्यथा
		old_pte = radix__pte_update(mm, addr, ptep, ~0ul, 0, 0);

	वापस __pte(old_pte);
पूर्ण

अटल अंतरभूत पूर्णांक radix__pte_same(pte_t pte_a, pte_t pte_b)
अणु
	वापस ((pte_raw(pte_a) ^ pte_raw(pte_b)) == 0);
पूर्ण

अटल अंतरभूत पूर्णांक radix__pte_none(pte_t pte)
अणु
	वापस (pte_val(pte) & ~RADIX_PTE_NONE_MASK) == 0;
पूर्ण

अटल अंतरभूत व्योम radix__set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				 pte_t *ptep, pte_t pte, पूर्णांक percpu)
अणु
	*ptep = pte;

	/*
	 * The architecture suggests a ptesync after setting the pte, which
	 * orders the store that updates the pte with subsequent page table
	 * walk accesses which may load the pte. Without this it may be
	 * possible क्रम a subsequent access to result in spurious fault.
	 *
	 * This is not necessary क्रम correctness, because a spurious fault
	 * is tolerated by the page fault handler, and this store will
	 * eventually be seen. In testing, there was no noticable increase
	 * in user faults on POWER9. Aव्योमing ptesync here is a signअगरicant
	 * win क्रम things like विभाजन. If a future microarchitecture benefits
	 * from ptesync, it should probably go पूर्णांकo update_mmu_cache, rather
	 * than set_pte_at (which is used to set ptes unrelated to faults).
	 *
	 * Spurious faults from the kernel memory are not tolerated, so there
	 * is a ptesync in flush_cache_vmap, and __map_kernel_page() follows
	 * the pte update sequence from ISA Book III 6.10 Translation Table
	 * Update Synchronization Requirements.
	 */
पूर्ण

अटल अंतरभूत पूर्णांक radix__pmd_bad(pmd_t pmd)
अणु
	वापस !!(pmd_val(pmd) & RADIX_PMD_BAD_BITS);
पूर्ण

अटल अंतरभूत पूर्णांक radix__pmd_same(pmd_t pmd_a, pmd_t pmd_b)
अणु
	वापस ((pmd_raw(pmd_a) ^ pmd_raw(pmd_b)) == 0);
पूर्ण

अटल अंतरभूत पूर्णांक radix__pud_bad(pud_t pud)
अणु
	वापस !!(pud_val(pud) & RADIX_PUD_BAD_BITS);
पूर्ण


अटल अंतरभूत पूर्णांक radix__p4d_bad(p4d_t p4d)
अणु
	वापस !!(p4d_val(p4d) & RADIX_P4D_BAD_BITS);
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE

अटल अंतरभूत पूर्णांक radix__pmd_trans_huge(pmd_t pmd)
अणु
	वापस (pmd_val(pmd) & (_PAGE_PTE | _PAGE_DEVMAP)) == _PAGE_PTE;
पूर्ण

अटल अंतरभूत pmd_t radix__pmd_mkhuge(pmd_t pmd)
अणु
	वापस __pmd(pmd_val(pmd) | _PAGE_PTE);
पूर्ण

बाह्य अचिन्हित दीर्घ radix__pmd_hugepage_update(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
					  pmd_t *pmdp, अचिन्हित दीर्घ clr,
					  अचिन्हित दीर्घ set);
बाह्य pmd_t radix__pmdp_collapse_flush(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ address, pmd_t *pmdp);
बाह्य व्योम radix__pgtable_trans_huge_deposit(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp,
					pgtable_t pgtable);
बाह्य pgtable_t radix__pgtable_trans_huge_withdraw(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp);
बाह्य pmd_t radix__pmdp_huge_get_and_clear(काष्ठा mm_काष्ठा *mm,
				      अचिन्हित दीर्घ addr, pmd_t *pmdp);
अटल अंतरभूत पूर्णांक radix__has_transparent_hugepage(व्योम)
अणु
	/* For radix 2M at PMD level means thp */
	अगर (mmu_psize_defs[MMU_PAGE_2M].shअगरt == PMD_SHIFT)
		वापस 1;
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत pmd_t radix__pmd_mkdevmap(pmd_t pmd)
अणु
	वापस __pmd(pmd_val(pmd) | (_PAGE_PTE | _PAGE_DEVMAP));
पूर्ण

बाह्य पूर्णांक __meminit radix__vmemmap_create_mapping(अचिन्हित दीर्घ start,
					     अचिन्हित दीर्घ page_size,
					     अचिन्हित दीर्घ phys);
बाह्य व्योम radix__vmemmap_हटाओ_mapping(अचिन्हित दीर्घ start,
				    अचिन्हित दीर्घ page_size);

बाह्य पूर्णांक radix__map_kernel_page(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ pa,
				 pgprot_t flags, अचिन्हित पूर्णांक psz);

अटल अंतरभूत अचिन्हित दीर्घ radix__get_tree_size(व्योम)
अणु
	अचिन्हित दीर्घ rts_field;
	/*
	 * We support 52 bits, hence:
	 * bits 52 - 31 = 21, 0b10101
	 * RTS encoding details
	 * bits 0 - 3 of rts -> bits 6 - 8 अचिन्हित दीर्घ
	 * bits 4 - 5 of rts -> bits 62 - 63 of अचिन्हित दीर्घ
	 */
	rts_field = (0x5UL << 5); /* 6 - 8 bits */
	rts_field |= (0x2UL << 61);

	वापस rts_field;
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
पूर्णांक radix__create_section_mapping(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				  पूर्णांक nid, pgprot_t prot);
पूर्णांक radix__हटाओ_section_mapping(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
#पूर्ण_अगर /* CONFIG_MEMORY_HOTPLUG */
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर
