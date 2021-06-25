<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_64_HASH_H
#घोषणा _ASM_POWERPC_BOOK3S_64_HASH_H
#अगर_घोषित __KERNEL__

#समावेश <यंत्र/यंत्र-स्थिर.h>

/*
 * Common bits between 4K and 64K pages in a linux-style PTE.
 * Additional bits may be defined in pgtable-hash64-*.h
 *
 */
#घोषणा H_PTE_NONE_MASK		_PAGE_HPTEFLAGS

#अगर_घोषित CONFIG_PPC_64K_PAGES
#समावेश <यंत्र/book3s/64/hash-64k.h>
#अन्यथा
#समावेश <यंत्र/book3s/64/hash-4k.h>
#पूर्ण_अगर

/* Bits to set in a PMD/PUD/PGD entry valid bit*/
#घोषणा HASH_PMD_VAL_BITS		(0x8000000000000000UL)
#घोषणा HASH_PUD_VAL_BITS		(0x8000000000000000UL)
#घोषणा HASH_PGD_VAL_BITS		(0x8000000000000000UL)

/*
 * Size of EA range mapped by our pagetables.
 */
#घोषणा H_PGTABLE_EADDR_SIZE	(H_PTE_INDEX_SIZE + H_PMD_INDEX_SIZE + \
				 H_PUD_INDEX_SIZE + H_PGD_INDEX_SIZE + PAGE_SHIFT)
#घोषणा H_PGTABLE_RANGE		(ASM_CONST(1) << H_PGTABLE_EADDR_SIZE)
/*
 * Top 2 bits are ignored in page table walk.
 */
#घोषणा EA_MASK			(~(0xcUL << 60))

/*
 * We store the slot details in the second half of page table.
 * Increase the pud level table so that hugetlb ptes can be stored
 * at pud level.
 */
#अगर defined(CONFIG_HUGETLB_PAGE) &&  defined(CONFIG_PPC_64K_PAGES)
#घोषणा H_PUD_CACHE_INDEX	(H_PUD_INDEX_SIZE + 1)
#अन्यथा
#घोषणा H_PUD_CACHE_INDEX	(H_PUD_INDEX_SIZE)
#पूर्ण_अगर

/*
 * +------------------------------+
 * |                              |
 * |                              |
 * |                              |
 * +------------------------------+  Kernel भव map end (0xc00e000000000000)
 * |                              |
 * |                              |
 * |      512TB/16TB of vmemmap   |
 * |                              |
 * |                              |
 * +------------------------------+  Kernel vmemmap  start
 * |                              |
 * |      512TB/16TB of IO map    |
 * |                              |
 * +------------------------------+  Kernel IO map start
 * |                              |
 * |      512TB/16TB of vmap      |
 * |                              |
 * +------------------------------+  Kernel virt start (0xc008000000000000)
 * |                              |
 * |                              |
 * |                              |
 * +------------------------------+  Kernel linear (0xc.....)
 */

#घोषणा H_VMALLOC_START		H_KERN_VIRT_START
#घोषणा H_VMALLOC_SIZE		H_KERN_MAP_SIZE
#घोषणा H_VMALLOC_END		(H_VMALLOC_START + H_VMALLOC_SIZE)

#घोषणा H_KERN_IO_START		H_VMALLOC_END
#घोषणा H_KERN_IO_SIZE		H_KERN_MAP_SIZE
#घोषणा H_KERN_IO_END		(H_KERN_IO_START + H_KERN_IO_SIZE)

#घोषणा H_VMEMMAP_START		H_KERN_IO_END
#घोषणा H_VMEMMAP_SIZE		H_KERN_MAP_SIZE
#घोषणा H_VMEMMAP_END		(H_VMEMMAP_START + H_VMEMMAP_SIZE)

#घोषणा NON_LINEAR_REGION_ID(ea)	((((अचिन्हित दीर्घ)ea - H_KERN_VIRT_START) >> REGION_SHIFT) + 2)

/*
 * Region IDs
 */
#घोषणा USER_REGION_ID		0
#घोषणा LINEAR_MAP_REGION_ID	1
#घोषणा VMALLOC_REGION_ID	NON_LINEAR_REGION_ID(H_VMALLOC_START)
#घोषणा IO_REGION_ID		NON_LINEAR_REGION_ID(H_KERN_IO_START)
#घोषणा VMEMMAP_REGION_ID	NON_LINEAR_REGION_ID(H_VMEMMAP_START)
#घोषणा INVALID_REGION_ID	(VMEMMAP_REGION_ID + 1)

/*
 * Defines the address of the vmemap area, in its own region on
 * hash table CPUs.
 */
#अगर_घोषित CONFIG_PPC_MM_SLICES
#घोषणा HAVE_ARCH_UNMAPPED_AREA
#घोषणा HAVE_ARCH_UNMAPPED_AREA_TOPDOWN
#पूर्ण_अगर /* CONFIG_PPC_MM_SLICES */

/* PTEIDX nibble */
#घोषणा _PTEIDX_SECONDARY	0x8
#घोषणा _PTEIDX_GROUP_IX	0x7

#घोषणा H_PMD_BAD_BITS		(PTE_TABLE_SIZE-1)
#घोषणा H_PUD_BAD_BITS		(PMD_TABLE_SIZE-1)

#अगर_अघोषित __ASSEMBLY__
अटल अंतरभूत पूर्णांक get_region_id(अचिन्हित दीर्घ ea)
अणु
	पूर्णांक region_id;
	पूर्णांक id = (ea >> 60UL);

	अगर (id == 0)
		वापस USER_REGION_ID;

	अगर (id != (PAGE_OFFSET >> 60))
		वापस INVALID_REGION_ID;

	अगर (ea < H_KERN_VIRT_START)
		वापस LINEAR_MAP_REGION_ID;

	BUILD_BUG_ON(NON_LINEAR_REGION_ID(H_VMALLOC_START) != 2);

	region_id = NON_LINEAR_REGION_ID(ea);
	वापस region_id;
पूर्ण

#घोषणा	hash__pmd_bad(pmd)		(pmd_val(pmd) & H_PMD_BAD_BITS)
#घोषणा	hash__pud_bad(pud)		(pud_val(pud) & H_PUD_BAD_BITS)
अटल अंतरभूत पूर्णांक hash__p4d_bad(p4d_t p4d)
अणु
	वापस (p4d_val(p4d) == 0);
पूर्ण
#अगर_घोषित CONFIG_STRICT_KERNEL_RWX
बाह्य व्योम hash__mark_rodata_ro(व्योम);
बाह्य व्योम hash__mark_iniपंचांगem_nx(व्योम);
#पूर्ण_अगर

बाह्य व्योम hpte_need_flush(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			    pte_t *ptep, अचिन्हित दीर्घ pte, पूर्णांक huge);
अचिन्हित दीर्घ htab_convert_pte_flags(अचिन्हित दीर्घ pteflags, अचिन्हित दीर्घ flags);
/* Atomic PTE updates */
अटल अंतरभूत अचिन्हित दीर्घ hash__pte_update(काष्ठा mm_काष्ठा *mm,
					 अचिन्हित दीर्घ addr,
					 pte_t *ptep, अचिन्हित दीर्घ clr,
					 अचिन्हित दीर्घ set,
					 पूर्णांक huge)
अणु
	__be64 old_be, पंचांगp_be;
	अचिन्हित दीर्घ old;

	__यंत्र__ __अस्थिर__(
	"1:	ldarx	%0,0,%3		# pte_update\न\
	and.	%1,%0,%6\न\
	bne-	1b \न\
	andc	%1,%0,%4 \न\
	or	%1,%1,%7\न\
	stdcx.	%1,0,%3 \न\
	bne-	1b"
	: "=&r" (old_be), "=&r" (पंचांगp_be), "=m" (*ptep)
	: "r" (ptep), "r" (cpu_to_be64(clr)), "m" (*ptep),
	  "r" (cpu_to_be64(H_PAGE_BUSY)), "r" (cpu_to_be64(set))
	: "cc" );
	/* huge pages use the old page table lock */
	अगर (!huge)
		निश्चित_pte_locked(mm, addr);

	old = be64_to_cpu(old_be);
	अगर (old & H_PAGE_HASHPTE)
		hpte_need_flush(mm, addr, ptep, old, huge);

	वापस old;
पूर्ण

/* Set the dirty and/or accessed bits atomically in a linux PTE, this
 * function करोesn't need to flush the hash entry
 */
अटल अंतरभूत व्योम hash__ptep_set_access_flags(pte_t *ptep, pte_t entry)
अणु
	__be64 old, पंचांगp, val, mask;

	mask = cpu_to_be64(_PAGE_सूचीTY | _PAGE_ACCESSED | _PAGE_READ | _PAGE_WRITE |
			   _PAGE_EXEC | _PAGE_SOFT_सूचीTY);

	val = pte_raw(entry) & mask;

	__यंत्र__ __अस्थिर__(
	"1:	ldarx	%0,0,%4\न\
		and.	%1,%0,%6\न\
		bne-	1b \न\
		or	%0,%3,%0\न\
		stdcx.	%0,0,%4\न\
		bne-	1b"
	:"=&r" (old), "=&r" (पंचांगp), "=m" (*ptep)
	:"r" (val), "r" (ptep), "m" (*ptep), "r" (cpu_to_be64(H_PAGE_BUSY))
	:"cc");
पूर्ण

अटल अंतरभूत पूर्णांक hash__pte_same(pte_t pte_a, pte_t pte_b)
अणु
	वापस (((pte_raw(pte_a) ^ pte_raw(pte_b)) & ~cpu_to_be64(_PAGE_HPTEFLAGS)) == 0);
पूर्ण

अटल अंतरभूत पूर्णांक hash__pte_none(pte_t pte)
अणु
	वापस (pte_val(pte) & ~H_PTE_NONE_MASK) == 0;
पूर्ण

अचिन्हित दीर्घ pte_get_hash_gslot(अचिन्हित दीर्घ vpn, अचिन्हित दीर्घ shअगरt,
		पूर्णांक ssize, real_pte_t rpte, अचिन्हित पूर्णांक subpg_index);

/* This low level function perक्रमms the actual PTE insertion
 * Setting the PTE depends on the MMU type and other factors. It's
 * an horrible mess that I'm not going to try to clean up now but
 * I'm keeping it in one place rather than spपढ़ो around
 */
अटल अंतरभूत व्योम hash__set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				  pte_t *ptep, pte_t pte, पूर्णांक percpu)
अणु
	/*
	 * Anything अन्यथा just stores the PTE normally. That covers all 64-bit
	 * हालs, and 32-bit non-hash with 32-bit PTEs.
	 */
	*ptep = pte;
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
बाह्य व्योम hpte_करो_hugepage_flush(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				   pmd_t *pmdp, अचिन्हित दीर्घ old_pmd);
#अन्यथा
अटल अंतरभूत व्योम hpte_करो_hugepage_flush(काष्ठा mm_काष्ठा *mm,
					  अचिन्हित दीर्घ addr, pmd_t *pmdp,
					  अचिन्हित दीर्घ old_pmd)
अणु
	WARN(1, "%s called with THP disabled\n", __func__);
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */


पूर्णांक hash__map_kernel_page(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ pa, pgprot_t prot);
बाह्य पूर्णांक __meminit hash__vmemmap_create_mapping(अचिन्हित दीर्घ start,
					      अचिन्हित दीर्घ page_size,
					      अचिन्हित दीर्घ phys);
बाह्य व्योम hash__vmemmap_हटाओ_mapping(अचिन्हित दीर्घ start,
				     अचिन्हित दीर्घ page_size);

पूर्णांक hash__create_section_mapping(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				 पूर्णांक nid, pgprot_t prot);
पूर्णांक hash__हटाओ_section_mapping(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_BOOK3S_64_HASH_H */
