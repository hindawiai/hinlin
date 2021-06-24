<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_PGTABLE_H
#घोषणा _ASM_RISCV_PGTABLE_H

#समावेश <linux/mmzone.h>
#समावेश <linux/sizes.h>

#समावेश <यंत्र/pgtable-bits.h>

#अगर_अघोषित CONFIG_MMU
#घोषणा KERNEL_LINK_ADDR	PAGE_OFFSET
#अन्यथा

#घोषणा ADDRESS_SPACE_END	(UL(-1))

#अगर_घोषित CONFIG_64BIT
/* Leave 2GB क्रम kernel and BPF at the end of the address space */
#घोषणा KERNEL_LINK_ADDR	(ADDRESS_SPACE_END - SZ_2G + 1)
#अन्यथा
#घोषणा KERNEL_LINK_ADDR	PAGE_OFFSET
#पूर्ण_अगर

#घोषणा VMALLOC_SIZE     (KERN_VIRT_SIZE >> 1)
#घोषणा VMALLOC_END      (PAGE_OFFSET - 1)
#घोषणा VMALLOC_START    (PAGE_OFFSET - VMALLOC_SIZE)

#घोषणा BPF_JIT_REGION_SIZE	(SZ_128M)
#अगर_घोषित CONFIG_64BIT
#घोषणा BPF_JIT_REGION_START	(BPF_JIT_REGION_END - BPF_JIT_REGION_SIZE)
#घोषणा BPF_JIT_REGION_END	(MODULES_END)
#अन्यथा
#घोषणा BPF_JIT_REGION_START	(PAGE_OFFSET - BPF_JIT_REGION_SIZE)
#घोषणा BPF_JIT_REGION_END	(VMALLOC_END)
#पूर्ण_अगर

/* Modules always live beक्रमe the kernel */
#अगर_घोषित CONFIG_64BIT
#घोषणा MODULES_VADDR	(PFN_ALIGN((अचिन्हित दीर्घ)&_end) - SZ_2G)
#घोषणा MODULES_END	(PFN_ALIGN((अचिन्हित दीर्घ)&_start))
#पूर्ण_अगर

/*
 * Roughly size the vmemmap space to be large enough to fit enough
 * काष्ठा pages to map half the भव address space. Then
 * position vmemmap directly below the VMALLOC region.
 */
#घोषणा VMEMMAP_SHIFT \
	(CONFIG_VA_BITS - PAGE_SHIFT - 1 + STRUCT_PAGE_MAX_SHIFT)
#घोषणा VMEMMAP_SIZE	BIT(VMEMMAP_SHIFT)
#घोषणा VMEMMAP_END	(VMALLOC_START - 1)
#घोषणा VMEMMAP_START	(VMALLOC_START - VMEMMAP_SIZE)

/*
 * Define vmemmap क्रम pfn_to_page & page_to_pfn calls. Needed अगर kernel
 * is configured with CONFIG_SPARSEMEM_VMEMMAP enabled.
 */
#घोषणा vmemmap		((काष्ठा page *)VMEMMAP_START)

#घोषणा PCI_IO_SIZE      SZ_16M
#घोषणा PCI_IO_END       VMEMMAP_START
#घोषणा PCI_IO_START     (PCI_IO_END - PCI_IO_SIZE)

#घोषणा FIXADDR_TOP      PCI_IO_START
#अगर_घोषित CONFIG_64BIT
#घोषणा FIXADDR_SIZE     PMD_SIZE
#अन्यथा
#घोषणा FIXADDR_SIZE     PGसूची_SIZE
#पूर्ण_अगर
#घोषणा FIXADDR_START    (FIXADDR_TOP - FIXADDR_SIZE)

#पूर्ण_अगर

#अगर_घोषित CONFIG_XIP_KERNEL
#घोषणा XIP_OFFSET		SZ_8M
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

/* Page Upper Directory not used in RISC-V */
#समावेश <यंत्र-generic/pgtable-nopud.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <linux/mm_types.h>

#अगर_घोषित CONFIG_64BIT
#समावेश <यंत्र/pgtable-64.h>
#अन्यथा
#समावेश <यंत्र/pgtable-32.h>
#पूर्ण_अगर /* CONFIG_64BIT */

#अगर_घोषित CONFIG_XIP_KERNEL
#घोषणा XIP_FIXUP(addr) (अणु							\
	uपूर्णांकptr_t __a = (uपूर्णांकptr_t)(addr);					\
	(__a >= CONFIG_XIP_PHYS_ADDR && __a < CONFIG_XIP_PHYS_ADDR + SZ_16M) ?	\
		__a - CONFIG_XIP_PHYS_ADDR + CONFIG_PHYS_RAM_BASE - XIP_OFFSET :\
		__a;								\
	पूर्ण)
#अन्यथा
#घोषणा XIP_FIXUP(addr)		(addr)
#पूर्ण_अगर /* CONFIG_XIP_KERNEL */

#अगर_घोषित CONFIG_MMU
/* Number of entries in the page global directory */
#घोषणा PTRS_PER_PGD    (PAGE_SIZE / माप(pgd_t))
/* Number of entries in the page table */
#घोषणा PTRS_PER_PTE    (PAGE_SIZE / माप(pte_t))

/* Number of PGD entries that a user-mode program can use */
#घोषणा USER_PTRS_PER_PGD   (TASK_SIZE / PGसूची_SIZE)

/* Page protection bits */
#घोषणा _PAGE_BASE	(_PAGE_PRESENT | _PAGE_ACCESSED | _PAGE_USER)

#घोषणा PAGE_NONE		__pgprot(_PAGE_PROT_NONE)
#घोषणा PAGE_READ		__pgprot(_PAGE_BASE | _PAGE_READ)
#घोषणा PAGE_WRITE		__pgprot(_PAGE_BASE | _PAGE_READ | _PAGE_WRITE)
#घोषणा PAGE_EXEC		__pgprot(_PAGE_BASE | _PAGE_EXEC)
#घोषणा PAGE_READ_EXEC		__pgprot(_PAGE_BASE | _PAGE_READ | _PAGE_EXEC)
#घोषणा PAGE_WRITE_EXEC		__pgprot(_PAGE_BASE | _PAGE_READ |	\
					 _PAGE_EXEC | _PAGE_WRITE)

#घोषणा PAGE_COPY		PAGE_READ
#घोषणा PAGE_COPY_EXEC		PAGE_EXEC
#घोषणा PAGE_COPY_READ_EXEC	PAGE_READ_EXEC
#घोषणा PAGE_SHARED		PAGE_WRITE
#घोषणा PAGE_SHARED_EXEC	PAGE_WRITE_EXEC

#घोषणा _PAGE_KERNEL		(_PAGE_READ \
				| _PAGE_WRITE \
				| _PAGE_PRESENT \
				| _PAGE_ACCESSED \
				| _PAGE_सूचीTY)

#घोषणा PAGE_KERNEL		__pgprot(_PAGE_KERNEL)
#घोषणा PAGE_KERNEL_READ	__pgprot(_PAGE_KERNEL & ~_PAGE_WRITE)
#घोषणा PAGE_KERNEL_EXEC	__pgprot(_PAGE_KERNEL | _PAGE_EXEC)
#घोषणा PAGE_KERNEL_READ_EXEC	__pgprot((_PAGE_KERNEL & ~_PAGE_WRITE) \
					 | _PAGE_EXEC)

#घोषणा PAGE_TABLE		__pgprot(_PAGE_TABLE)

/*
 * The RISC-V ISA करोesn't yet specify how to query or modify PMAs, so we can't
 * change the properties of memory regions.
 */
#घोषणा _PAGE_IOREMAP _PAGE_KERNEL

बाह्य pgd_t swapper_pg_dir[];

/* MAP_PRIVATE permissions: xwr (copy-on-ग_लिखो) */
#घोषणा __P000	PAGE_NONE
#घोषणा __P001	PAGE_READ
#घोषणा __P010	PAGE_COPY
#घोषणा __P011	PAGE_COPY
#घोषणा __P100	PAGE_EXEC
#घोषणा __P101	PAGE_READ_EXEC
#घोषणा __P110	PAGE_COPY_EXEC
#घोषणा __P111	PAGE_COPY_READ_EXEC

/* MAP_SHARED permissions: xwr */
#घोषणा __S000	PAGE_NONE
#घोषणा __S001	PAGE_READ
#घोषणा __S010	PAGE_SHARED
#घोषणा __S011	PAGE_SHARED
#घोषणा __S100	PAGE_EXEC
#घोषणा __S101	PAGE_READ_EXEC
#घोषणा __S110	PAGE_SHARED_EXEC
#घोषणा __S111	PAGE_SHARED_EXEC

अटल अंतरभूत पूर्णांक pmd_present(pmd_t pmd)
अणु
	वापस (pmd_val(pmd) & (_PAGE_PRESENT | _PAGE_PROT_NONE));
पूर्ण

अटल अंतरभूत पूर्णांक pmd_none(pmd_t pmd)
अणु
	वापस (pmd_val(pmd) == 0);
पूर्ण

अटल अंतरभूत पूर्णांक pmd_bad(pmd_t pmd)
अणु
	वापस !pmd_present(pmd);
पूर्ण

#घोषणा pmd_leaf	pmd_leaf
अटल अंतरभूत पूर्णांक pmd_leaf(pmd_t pmd)
अणु
	वापस pmd_present(pmd) &&
	       (pmd_val(pmd) & (_PAGE_READ | _PAGE_WRITE | _PAGE_EXEC));
पूर्ण

अटल अंतरभूत व्योम set_pmd(pmd_t *pmdp, pmd_t pmd)
अणु
	*pmdp = pmd;
पूर्ण

अटल अंतरभूत व्योम pmd_clear(pmd_t *pmdp)
अणु
	set_pmd(pmdp, __pmd(0));
पूर्ण

अटल अंतरभूत pgd_t pfn_pgd(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	वापस __pgd((pfn << _PAGE_PFN_SHIFT) | pgprot_val(prot));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ _pgd_pfn(pgd_t pgd)
अणु
	वापस pgd_val(pgd) >> _PAGE_PFN_SHIFT;
पूर्ण

अटल अंतरभूत काष्ठा page *pmd_page(pmd_t pmd)
अणु
	वापस pfn_to_page(pmd_val(pmd) >> _PAGE_PFN_SHIFT);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pmd_page_vaddr(pmd_t pmd)
अणु
	वापस (अचिन्हित दीर्घ)pfn_to_virt(pmd_val(pmd) >> _PAGE_PFN_SHIFT);
पूर्ण

अटल अंतरभूत pte_t pmd_pte(pmd_t pmd)
अणु
	वापस __pte(pmd_val(pmd));
पूर्ण

/* Yields the page frame number (PFN) of a page table entry */
अटल अंतरभूत अचिन्हित दीर्घ pte_pfn(pte_t pte)
अणु
	वापस (pte_val(pte) >> _PAGE_PFN_SHIFT);
पूर्ण

#घोषणा pte_page(x)     pfn_to_page(pte_pfn(x))

/* Conकाष्ठाs a page table entry */
अटल अंतरभूत pte_t pfn_pte(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	वापस __pte((pfn << _PAGE_PFN_SHIFT) | pgprot_val(prot));
पूर्ण

#घोषणा mk_pte(page, prot)       pfn_pte(page_to_pfn(page), prot)

अटल अंतरभूत पूर्णांक pte_present(pte_t pte)
अणु
	वापस (pte_val(pte) & (_PAGE_PRESENT | _PAGE_PROT_NONE));
पूर्ण

अटल अंतरभूत पूर्णांक pte_none(pte_t pte)
अणु
	वापस (pte_val(pte) == 0);
पूर्ण

अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_WRITE;
पूर्ण

अटल अंतरभूत पूर्णांक pte_exec(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_EXEC;
पूर्ण

अटल अंतरभूत पूर्णांक pte_huge(pte_t pte)
अणु
	वापस pte_present(pte)
		&& (pte_val(pte) & (_PAGE_READ | _PAGE_WRITE | _PAGE_EXEC));
पूर्ण

अटल अंतरभूत पूर्णांक pte_dirty(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_सूचीTY;
पूर्ण

अटल अंतरभूत पूर्णांक pte_young(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_ACCESSED;
पूर्ण

अटल अंतरभूत पूर्णांक pte_special(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_SPECIAL;
पूर्ण

/* अटल अंतरभूत pte_t pte_rdprotect(pte_t pte) */

अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	वापस __pte(pte_val(pte) & ~(_PAGE_WRITE));
पूर्ण

/* अटल अंतरभूत pte_t pte_mkपढ़ो(pte_t pte) */

अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_WRITE);
पूर्ण

/* अटल अंतरभूत pte_t pte_mkexec(pte_t pte) */

अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_सूचीTY);
पूर्ण

अटल अंतरभूत pte_t pte_mkclean(pte_t pte)
अणु
	वापस __pte(pte_val(pte) & ~(_PAGE_सूचीTY));
पूर्ण

अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_ACCESSED);
पूर्ण

अटल अंतरभूत pte_t pte_mkold(pte_t pte)
अणु
	वापस __pte(pte_val(pte) & ~(_PAGE_ACCESSED));
पूर्ण

अटल अंतरभूत pte_t pte_mkspecial(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | _PAGE_SPECIAL);
पूर्ण

अटल अंतरभूत pte_t pte_mkhuge(pte_t pte)
अणु
	वापस pte;
पूर्ण

#अगर_घोषित CONFIG_NUMA_BALANCING
/*
 * See the comment in include/यंत्र-generic/pgtable.h
 */
अटल अंतरभूत पूर्णांक pte_protnone(pte_t pte)
अणु
	वापस (pte_val(pte) & (_PAGE_PRESENT | _PAGE_PROT_NONE)) == _PAGE_PROT_NONE;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_protnone(pmd_t pmd)
अणु
	वापस pte_protnone(pmd_pte(pmd));
पूर्ण
#पूर्ण_अगर

/* Modअगरy page protection bits */
अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	वापस __pte((pte_val(pte) & _PAGE_CHG_MASK) | pgprot_val(newprot));
पूर्ण

#घोषणा pgd_ERROR(e) \
	pr_err("%s:%d: bad pgd " PTE_FMT ".\n", __खाता__, __LINE__, pgd_val(e))


/* Commit new configuration to MMU hardware */
अटल अंतरभूत व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma,
	अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	/*
	 * The kernel assumes that TLBs करोn't cache invalid entries, but
	 * in RISC-V, SFENCE.VMA specअगरies an ordering स्थिरraपूर्णांक, not a
	 * cache flush; it is necessary even after writing invalid entries.
	 * Relying on flush_tlb_fix_spurious_fault would suffice, but
	 * the extra traps reduce perक्रमmance.  So, eagerly SFENCE.VMA.
	 */
	local_flush_tlb_page(address);
पूर्ण

#घोषणा __HAVE_ARCH_PTE_SAME
अटल अंतरभूत पूर्णांक pte_same(pte_t pte_a, pte_t pte_b)
अणु
	वापस pte_val(pte_a) == pte_val(pte_b);
पूर्ण

/*
 * Certain architectures need to करो special things when PTEs within
 * a page table are directly modअगरied.  Thus, the following hook is
 * made available.
 */
अटल अंतरभूत व्योम set_pte(pte_t *ptep, pte_t pteval)
अणु
	*ptep = pteval;
पूर्ण

व्योम flush_icache_pte(pte_t pte);

अटल अंतरभूत व्योम set_pte_at(काष्ठा mm_काष्ठा *mm,
	अचिन्हित दीर्घ addr, pte_t *ptep, pte_t pteval)
अणु
	अगर (pte_present(pteval) && pte_exec(pteval))
		flush_icache_pte(pteval);

	set_pte(ptep, pteval);
पूर्ण

अटल अंतरभूत व्योम pte_clear(काष्ठा mm_काष्ठा *mm,
	अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	set_pte_at(mm, addr, ptep, __pte(0));
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
अटल अंतरभूत पूर्णांक ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ address, pte_t *ptep,
					pte_t entry, पूर्णांक dirty)
अणु
	अगर (!pte_same(*ptep, entry))
		set_pte_at(vma->vm_mm, address, ptep, entry);
	/*
	 * update_mmu_cache will unconditionally execute, handling both
	 * the हाल that the PTE changed and the spurious fault हाल.
	 */
	वापस true;
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_GET_AND_CLEAR
अटल अंतरभूत pte_t ptep_get_and_clear(काष्ठा mm_काष्ठा *mm,
				       अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	वापस __pte(atomic_दीर्घ_xchg((atomic_दीर्घ_t *)ptep, 0));
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
अटल अंतरभूत पूर्णांक ptep_test_and_clear_young(काष्ठा vm_area_काष्ठा *vma,
					    अचिन्हित दीर्घ address,
					    pte_t *ptep)
अणु
	अगर (!pte_young(*ptep))
		वापस 0;
	वापस test_and_clear_bit(_PAGE_ACCESSED_OFFSET, &pte_val(*ptep));
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_SET_WRPROTECT
अटल अंतरभूत व्योम ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm,
				      अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	atomic_दीर्घ_and(~(अचिन्हित दीर्घ)_PAGE_WRITE, (atomic_दीर्घ_t *)ptep);
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_CLEAR_YOUNG_FLUSH
अटल अंतरभूत पूर्णांक ptep_clear_flush_young(काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	/*
	 * This comment is borrowed from x86, but applies equally to RISC-V:
	 *
	 * Clearing the accessed bit without a TLB flush
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

/*
 * Encode and decode a swap entry
 *
 * Format of swap PTE:
 *	bit            0:	_PAGE_PRESENT (zero)
 *	bit            1:	_PAGE_PROT_NONE (zero)
 *	bits      2 to 6:	swap type
 *	bits 7 to XLEN-1:	swap offset
 */
#घोषणा __SWP_TYPE_SHIFT	2
#घोषणा __SWP_TYPE_BITS		5
#घोषणा __SWP_TYPE_MASK		((1UL << __SWP_TYPE_BITS) - 1)
#घोषणा __SWP_OFFSET_SHIFT	(__SWP_TYPE_BITS + __SWP_TYPE_SHIFT)

#घोषणा MAX_SWAPखाताS_CHECK()	\
	BUILD_BUG_ON(MAX_SWAPखाताS_SHIFT > __SWP_TYPE_BITS)

#घोषणा __swp_type(x)	(((x).val >> __SWP_TYPE_SHIFT) & __SWP_TYPE_MASK)
#घोषणा __swp_offset(x)	((x).val >> __SWP_OFFSET_SHIFT)
#घोषणा __swp_entry(type, offset) ((swp_entry_t) \
	अणु ((type) << __SWP_TYPE_SHIFT) | ((offset) << __SWP_OFFSET_SHIFT) पूर्ण)

#घोषणा __pte_to_swp_entry(pte)	((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(x)	((pte_t) अणु (x).val पूर्ण)

/*
 * In the RV64 Linux scheme, we give the user half of the भव-address space
 * and give the kernel the other (upper) half.
 */
#अगर_घोषित CONFIG_64BIT
#घोषणा KERN_VIRT_START	(-(BIT(CONFIG_VA_BITS)) + TASK_SIZE)
#अन्यथा
#घोषणा KERN_VIRT_START	FIXADDR_START
#पूर्ण_अगर

/*
 * Task size is 0x4000000000 क्रम RV64 or 0x9fc00000 क्रम RV32.
 * Note that PGसूची_SIZE must evenly भागide TASK_SIZE.
 */
#अगर_घोषित CONFIG_64BIT
#घोषणा TASK_SIZE (PGसूची_SIZE * PTRS_PER_PGD / 2)
#अन्यथा
#घोषणा TASK_SIZE FIXADDR_START
#पूर्ण_अगर

#अन्यथा /* CONFIG_MMU */

#घोषणा PAGE_SHARED		__pgprot(0)
#घोषणा PAGE_KERNEL		__pgprot(0)
#घोषणा swapper_pg_dir		शून्य
#घोषणा TASK_SIZE		0xffffffffUL
#घोषणा VMALLOC_START		0
#घोषणा VMALLOC_END		TASK_SIZE

#पूर्ण_अगर /* !CONFIG_MMU */

#घोषणा kern_addr_valid(addr)   (1) /* FIXME */

बाह्य अक्षर _start[];
बाह्य व्योम *_dtb_early_va;
बाह्य uपूर्णांकptr_t _dtb_early_pa;
#अगर defined(CONFIG_XIP_KERNEL) && defined(CONFIG_MMU)
#घोषणा dtb_early_va	(*(व्योम **)XIP_FIXUP(&_dtb_early_va))
#घोषणा dtb_early_pa	(*(uपूर्णांकptr_t *)XIP_FIXUP(&_dtb_early_pa))
#अन्यथा
#घोषणा dtb_early_va	_dtb_early_va
#घोषणा dtb_early_pa	_dtb_early_pa
#पूर्ण_अगर /* CONFIG_XIP_KERNEL */

व्योम setup_booपंचांगem(व्योम);
व्योम paging_init(व्योम);
व्योम misc_mem_init(व्योम);

#घोषणा FIRST_USER_ADDRESS  0

/*
 * ZERO_PAGE is a global shared page that is always zero,
 * used क्रम zero-mapped memory areas, etc.
 */
बाह्य अचिन्हित दीर्घ empty_zero_page[PAGE_SIZE / माप(अचिन्हित दीर्घ)];
#घोषणा ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_RISCV_PGTABLE_H */
