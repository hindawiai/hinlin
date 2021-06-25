<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_64_PGTABLE_H_
#घोषणा _ASM_POWERPC_BOOK3S_64_PGTABLE_H_

#समावेश <यंत्र-generic/pgtable-nop4d.h>

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/mmdebug.h>
#समावेश <linux/bug.h>
#समावेश <linux/sizes.h>
#पूर्ण_अगर

/*
 * Common bits between hash and Radix page table
 */
#घोषणा _PAGE_BIT_SWAP_TYPE	0

#घोषणा _PAGE_EXEC		0x00001 /* execute permission */
#घोषणा _PAGE_WRITE		0x00002 /* ग_लिखो access allowed */
#घोषणा _PAGE_READ		0x00004	/* पढ़ो access allowed */
#घोषणा _PAGE_RW		(_PAGE_READ | _PAGE_WRITE)
#घोषणा _PAGE_RWX		(_PAGE_READ | _PAGE_WRITE | _PAGE_EXEC)
#घोषणा _PAGE_PRIVILEGED	0x00008 /* kernel access only */
#घोषणा _PAGE_SAO		0x00010 /* Strong access order */
#घोषणा _PAGE_NON_IDEMPOTENT	0x00020 /* non idempotent memory */
#घोषणा _PAGE_TOLERANT		0x00030 /* tolerant memory, cache inhibited */
#घोषणा _PAGE_सूचीTY		0x00080 /* C: page changed */
#घोषणा _PAGE_ACCESSED		0x00100 /* R: page referenced */
/*
 * Software bits
 */
#घोषणा _RPAGE_SW0		0x2000000000000000UL
#घोषणा _RPAGE_SW1		0x00800
#घोषणा _RPAGE_SW2		0x00400
#घोषणा _RPAGE_SW3		0x00200
#घोषणा _RPAGE_RSV1		0x00040UL

#घोषणा _RPAGE_PKEY_BIT4	0x1000000000000000UL
#घोषणा _RPAGE_PKEY_BIT3	0x0800000000000000UL
#घोषणा _RPAGE_PKEY_BIT2	0x0400000000000000UL
#घोषणा _RPAGE_PKEY_BIT1	0x0200000000000000UL
#घोषणा _RPAGE_PKEY_BIT0	0x0100000000000000UL

#घोषणा _PAGE_PTE		0x4000000000000000UL	/* distinguishes PTEs from poपूर्णांकers */
#घोषणा _PAGE_PRESENT		0x8000000000000000UL	/* pte contains a translation */
/*
 * We need to mark a pmd pte invalid जबतक splitting. We can करो that by clearing
 * the _PAGE_PRESENT bit. But then that will be taken as a swap pte. In order to
 * dअगरferentiate between two use a SW field when invalidating.
 *
 * We करो that temporary invalidate क्रम regular pte entry in ptep_set_access_flags
 *
 * This is used only when _PAGE_PRESENT is cleared.
 */
#घोषणा _PAGE_INVALID		_RPAGE_SW0

/*
 * Top and bottom bits of RPN which can be used by hash
 * translation mode, because we expect them to be zero
 * otherwise.
 */
#घोषणा _RPAGE_RPN0		0x01000
#घोषणा _RPAGE_RPN1		0x02000
#घोषणा _RPAGE_RPN43		0x0080000000000000UL
#घोषणा _RPAGE_RPN42		0x0040000000000000UL
#घोषणा _RPAGE_RPN41		0x0020000000000000UL

/* Max physical address bit as per radix table */
#घोषणा _RPAGE_PA_MAX		56

/*
 * Max physical address bit we will use क्रम now.
 *
 * This is mostly a hardware limitation and क्रम now Power9 has
 * a 51 bit limit.
 *
 * This is dअगरferent from the number of physical bit required to address
 * the last byte of memory. That is defined by MAX_PHYSMEM_BITS.
 * MAX_PHYSMEM_BITS is a linux limitation imposed by the maximum
 * number of sections we can support (SECTIONS_SHIFT).
 *
 * This is dअगरferent from Radix page table limitation above and
 * should always be less than that. The limit is करोne such that
 * we can overload the bits between _RPAGE_PA_MAX and _PAGE_PA_MAX
 * क्रम hash linux page table specअगरic bits.
 *
 * In order to be compatible with future hardware generations we keep
 * some offsets and limit this क्रम now to 53
 */
#घोषणा _PAGE_PA_MAX		53

#घोषणा _PAGE_SOFT_सूचीTY	_RPAGE_SW3 /* software: software dirty tracking */
#घोषणा _PAGE_SPECIAL		_RPAGE_SW2 /* software: special page */
#घोषणा _PAGE_DEVMAP		_RPAGE_SW1 /* software: ZONE_DEVICE page */

/*
 * Drivers request क्रम cache inhibited pte mapping using _PAGE_NO_CACHE
 * Instead of fixing all of them, add an alternate define which
 * maps CI pte mapping.
 */
#घोषणा _PAGE_NO_CACHE		_PAGE_TOLERANT
/*
 * We support _RPAGE_PA_MAX bit real address in pte. On the linux side
 * we are limited by _PAGE_PA_MAX. Clear everything above _PAGE_PA_MAX
 * and every thing below PAGE_SHIFT;
 */
#घोषणा PTE_RPN_MASK	(((1UL << _PAGE_PA_MAX) - 1) & (PAGE_MASK))
/*
 * set of bits not changed in pmd_modअगरy. Even though we have hash specअगरic bits
 * in here, on radix we expect them to be zero.
 */
#घोषणा _HPAGE_CHG_MASK (PTE_RPN_MASK | _PAGE_HPTEFLAGS | _PAGE_सूचीTY | \
			 _PAGE_ACCESSED | H_PAGE_THP_HUGE | _PAGE_PTE | \
			 _PAGE_SOFT_सूचीTY | _PAGE_DEVMAP)
/*
 * user access blocked by key
 */
#घोषणा _PAGE_KERNEL_RW		(_PAGE_PRIVILEGED | _PAGE_RW | _PAGE_सूचीTY)
#घोषणा _PAGE_KERNEL_RO		 (_PAGE_PRIVILEGED | _PAGE_READ)
#घोषणा _PAGE_KERNEL_ROX	 (_PAGE_PRIVILEGED | _PAGE_READ | _PAGE_EXEC)
#घोषणा _PAGE_KERNEL_RWX	(_PAGE_PRIVILEGED | _PAGE_सूचीTY |	\
				 _PAGE_RW | _PAGE_EXEC)
/*
 * _PAGE_CHG_MASK masks of bits that are to be preserved across
 * pgprot changes
 */
#घोषणा _PAGE_CHG_MASK	(PTE_RPN_MASK | _PAGE_HPTEFLAGS | _PAGE_सूचीTY | \
			 _PAGE_ACCESSED | _PAGE_SPECIAL | _PAGE_PTE |	\
			 _PAGE_SOFT_सूचीTY | _PAGE_DEVMAP)

/*
 * We define 2 sets of base prot bits, one क्रम basic pages (ie,
 * cacheable kernel and user pages) and one क्रम non cacheable
 * pages. We always set _PAGE_COHERENT when SMP is enabled or
 * the processor might need it क्रम DMA coherency.
 */
#घोषणा _PAGE_BASE_NC	(_PAGE_PRESENT | _PAGE_ACCESSED)
#घोषणा _PAGE_BASE	(_PAGE_BASE_NC)

/* Permission masks used to generate the __P and __S table,
 *
 * Note:__pgprot is defined in arch/घातerpc/include/यंत्र/page.h
 *
 * Write permissions imply पढ़ो permissions क्रम now (we could make ग_लिखो-only
 * pages on BookE but we करोn't bother क्रम now). Execute permission control is
 * possible on platक्रमms that define _PAGE_EXEC
 */
#घोषणा PAGE_NONE	__pgprot(_PAGE_BASE | _PAGE_PRIVILEGED)
#घोषणा PAGE_SHARED	__pgprot(_PAGE_BASE | _PAGE_RW)
#घोषणा PAGE_SHARED_X	__pgprot(_PAGE_BASE | _PAGE_RW | _PAGE_EXEC)
#घोषणा PAGE_COPY	__pgprot(_PAGE_BASE | _PAGE_READ)
#घोषणा PAGE_COPY_X	__pgprot(_PAGE_BASE | _PAGE_READ | _PAGE_EXEC)
#घोषणा PAGE_READONLY	__pgprot(_PAGE_BASE | _PAGE_READ)
#घोषणा PAGE_READONLY_X	__pgprot(_PAGE_BASE | _PAGE_READ | _PAGE_EXEC)

/* Permission masks used क्रम kernel mappings */
#घोषणा PAGE_KERNEL	__pgprot(_PAGE_BASE | _PAGE_KERNEL_RW)
#घोषणा PAGE_KERNEL_NC	__pgprot(_PAGE_BASE_NC | _PAGE_KERNEL_RW | \
				 _PAGE_TOLERANT)
#घोषणा PAGE_KERNEL_NCG	__pgprot(_PAGE_BASE_NC | _PAGE_KERNEL_RW | \
				 _PAGE_NON_IDEMPOTENT)
#घोषणा PAGE_KERNEL_X	__pgprot(_PAGE_BASE | _PAGE_KERNEL_RWX)
#घोषणा PAGE_KERNEL_RO	__pgprot(_PAGE_BASE | _PAGE_KERNEL_RO)
#घोषणा PAGE_KERNEL_ROX	__pgprot(_PAGE_BASE | _PAGE_KERNEL_ROX)

/*
 * Protection used क्रम kernel text. We want the debuggers to be able to
 * set अवरोधpoपूर्णांकs anywhere, so करोn't ग_लिखो protect the kernel text
 * on platक्रमms where such control is possible.
 */
#अगर defined(CONFIG_KGDB) || defined(CONFIG_XMON) || defined(CONFIG_BDI_SWITCH) || \
	defined(CONFIG_KPROBES) || defined(CONFIG_DYNAMIC_FTRACE)
#घोषणा PAGE_KERNEL_TEXT	PAGE_KERNEL_X
#अन्यथा
#घोषणा PAGE_KERNEL_TEXT	PAGE_KERNEL_ROX
#पूर्ण_अगर

/* Make modules code happy. We करोn't set RO yet */
#घोषणा PAGE_KERNEL_EXEC	PAGE_KERNEL_X
#घोषणा PAGE_AGP		(PAGE_KERNEL_NC)

#अगर_अघोषित __ASSEMBLY__
/*
 * page table defines
 */
बाह्य अचिन्हित दीर्घ __pte_index_size;
बाह्य अचिन्हित दीर्घ __pmd_index_size;
बाह्य अचिन्हित दीर्घ __pud_index_size;
बाह्य अचिन्हित दीर्घ __pgd_index_size;
बाह्य अचिन्हित दीर्घ __pud_cache_index;
#घोषणा PTE_INDEX_SIZE  __pte_index_size
#घोषणा PMD_INDEX_SIZE  __pmd_index_size
#घोषणा PUD_INDEX_SIZE  __pud_index_size
#घोषणा PGD_INDEX_SIZE  __pgd_index_size
/* pmd table use page table fragments */
#घोषणा PMD_CACHE_INDEX  0
#घोषणा PUD_CACHE_INDEX __pud_cache_index
/*
 * Because of use of pte fragments and THP, size of page table
 * are not always derived out of index size above.
 */
बाह्य अचिन्हित दीर्घ __pte_table_size;
बाह्य अचिन्हित दीर्घ __pmd_table_size;
बाह्य अचिन्हित दीर्घ __pud_table_size;
बाह्य अचिन्हित दीर्घ __pgd_table_size;
#घोषणा PTE_TABLE_SIZE	__pte_table_size
#घोषणा PMD_TABLE_SIZE	__pmd_table_size
#घोषणा PUD_TABLE_SIZE	__pud_table_size
#घोषणा PGD_TABLE_SIZE	__pgd_table_size

बाह्य अचिन्हित दीर्घ __pmd_val_bits;
बाह्य अचिन्हित दीर्घ __pud_val_bits;
बाह्य अचिन्हित दीर्घ __pgd_val_bits;
#घोषणा PMD_VAL_BITS	__pmd_val_bits
#घोषणा PUD_VAL_BITS	__pud_val_bits
#घोषणा PGD_VAL_BITS	__pgd_val_bits

बाह्य अचिन्हित दीर्घ __pte_frag_nr;
#घोषणा PTE_FRAG_NR __pte_frag_nr
बाह्य अचिन्हित दीर्घ __pte_frag_size_shअगरt;
#घोषणा PTE_FRAG_SIZE_SHIFT __pte_frag_size_shअगरt
#घोषणा PTE_FRAG_SIZE (1UL << PTE_FRAG_SIZE_SHIFT)

बाह्य अचिन्हित दीर्घ __pmd_frag_nr;
#घोषणा PMD_FRAG_NR __pmd_frag_nr
बाह्य अचिन्हित दीर्घ __pmd_frag_size_shअगरt;
#घोषणा PMD_FRAG_SIZE_SHIFT __pmd_frag_size_shअगरt
#घोषणा PMD_FRAG_SIZE (1UL << PMD_FRAG_SIZE_SHIFT)

#घोषणा PTRS_PER_PTE	(1 << PTE_INDEX_SIZE)
#घोषणा PTRS_PER_PMD	(1 << PMD_INDEX_SIZE)
#घोषणा PTRS_PER_PUD	(1 << PUD_INDEX_SIZE)
#घोषणा PTRS_PER_PGD	(1 << PGD_INDEX_SIZE)

/* PMD_SHIFT determines what a second-level page table entry can map */
#घोषणा PMD_SHIFT	(PAGE_SHIFT + PTE_INDEX_SIZE)
#घोषणा PMD_SIZE	(1UL << PMD_SHIFT)
#घोषणा PMD_MASK	(~(PMD_SIZE-1))

/* PUD_SHIFT determines what a third-level page table entry can map */
#घोषणा PUD_SHIFT	(PMD_SHIFT + PMD_INDEX_SIZE)
#घोषणा PUD_SIZE	(1UL << PUD_SHIFT)
#घोषणा PUD_MASK	(~(PUD_SIZE-1))

/* PGसूची_SHIFT determines what a fourth-level page table entry can map */
#घोषणा PGसूची_SHIFT	(PUD_SHIFT + PUD_INDEX_SIZE)
#घोषणा PGसूची_SIZE	(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK	(~(PGसूची_SIZE-1))

/* Bits to mask out from a PMD to get to the PTE page */
#घोषणा PMD_MASKED_BITS		0xc0000000000000ffUL
/* Bits to mask out from a PUD to get to the PMD page */
#घोषणा PUD_MASKED_BITS		0xc0000000000000ffUL
/* Bits to mask out from a PGD to get to the PUD page */
#घोषणा P4D_MASKED_BITS		0xc0000000000000ffUL

/*
 * Used as an indicator क्रम rcu callback functions
 */
क्रमागत pgtable_index अणु
	PTE_INDEX = 0,
	PMD_INDEX,
	PUD_INDEX,
	PGD_INDEX,
	/*
	 * Below are used with 4k page size and hugetlb
	 */
	HTLB_16M_INDEX,
	HTLB_16G_INDEX,
पूर्ण;

बाह्य अचिन्हित दीर्घ __vदो_स्मृति_start;
बाह्य अचिन्हित दीर्घ __vदो_स्मृति_end;
#घोषणा VMALLOC_START	__vदो_स्मृति_start
#घोषणा VMALLOC_END	__vदो_स्मृति_end

अटल अंतरभूत अचिन्हित पूर्णांक ioremap_max_order(व्योम)
अणु
	अगर (radix_enabled())
		वापस PUD_SHIFT;
	वापस 7 + PAGE_SHIFT; /* शेष from linux/vदो_स्मृति.h */
पूर्ण
#घोषणा IOREMAP_MAX_ORDER ioremap_max_order()

बाह्य अचिन्हित दीर्घ __kernel_virt_start;
बाह्य अचिन्हित दीर्घ __kernel_io_start;
बाह्य अचिन्हित दीर्घ __kernel_io_end;
#घोषणा KERN_VIRT_START __kernel_virt_start
#घोषणा KERN_IO_START  __kernel_io_start
#घोषणा KERN_IO_END __kernel_io_end

बाह्य काष्ठा page *vmemmap;
बाह्य अचिन्हित दीर्घ pci_io_base;
#पूर्ण_अगर /* __ASSEMBLY__ */

#समावेश <यंत्र/book3s/64/hash.h>
#समावेश <यंत्र/book3s/64/radix.h>

#अगर H_MAX_PHYSMEM_BITS > R_MAX_PHYSMEM_BITS
#घोषणा  MAX_PHYSMEM_BITS	H_MAX_PHYSMEM_BITS
#अन्यथा
#घोषणा  MAX_PHYSMEM_BITS	R_MAX_PHYSMEM_BITS
#पूर्ण_अगर


#अगर_घोषित CONFIG_PPC_64K_PAGES
#समावेश <यंत्र/book3s/64/pgtable-64k.h>
#अन्यथा
#समावेश <यंत्र/book3s/64/pgtable-4k.h>
#पूर्ण_अगर

#समावेश <यंत्र/barrier.h>
/*
 * IO space itself carved पूर्णांकo the PIO region (ISA and PHB IO space) and
 * the ioremap space
 *
 *  ISA_IO_BASE = KERN_IO_START, 64K reserved area
 *  PHB_IO_BASE = ISA_IO_BASE + 64K to ISA_IO_BASE + 2G, PHB IO spaces
 * IOREMAP_BASE = ISA_IO_BASE + 2G to VMALLOC_START + PGTABLE_RANGE
 */
#घोषणा FULL_IO_SIZE	0x80000000ul
#घोषणा  ISA_IO_BASE	(KERN_IO_START)
#घोषणा  ISA_IO_END	(KERN_IO_START + 0x10000ul)
#घोषणा  PHB_IO_BASE	(ISA_IO_END)
#घोषणा  PHB_IO_END	(KERN_IO_START + FULL_IO_SIZE)
#घोषणा IOREMAP_BASE	(PHB_IO_END)
#घोषणा IOREMAP_START	(ioremap_bot)
#घोषणा IOREMAP_END	(KERN_IO_END - FIXADDR_SIZE)
#घोषणा FIXADDR_SIZE	SZ_32M

/* Advertise special mapping type क्रम AGP */
#घोषणा HAVE_PAGE_AGP

#अगर_अघोषित __ASSEMBLY__

/*
 * This is the शेष implementation of various PTE accessors, it's
 * used in all हालs except Book3S with 64K pages where we have a
 * concept of sub-pages
 */
#अगर_अघोषित __real_pte

#घोषणा __real_pte(e, p, o)		((real_pte_t)अणु(e)पूर्ण)
#घोषणा __rpte_to_pte(r)	((r).pte)
#घोषणा __rpte_to_hidx(r,index)	(pte_val(__rpte_to_pte(r)) >> H_PAGE_F_GIX_SHIFT)

#घोषणा pte_iterate_hashed_subpages(rpte, psize, va, index, shअगरt)       \
	करो अणु							         \
		index = 0;					         \
		shअगरt = mmu_psize_defs[psize].shअगरt;		         \

#घोषणा pte_iterate_hashed_end() पूर्ण जबतक(0)

/*
 * We expect this to be called only क्रम user addresses or kernel भव
 * addresses other than the linear mapping.
 */
#घोषणा pte_pagesize_index(mm, addr, pte)	MMU_PAGE_4K

#पूर्ण_अगर /* __real_pte */

अटल अंतरभूत अचिन्हित दीर्घ pte_update(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				       pte_t *ptep, अचिन्हित दीर्घ clr,
				       अचिन्हित दीर्घ set, पूर्णांक huge)
अणु
	अगर (radix_enabled())
		वापस radix__pte_update(mm, addr, ptep, clr, set, huge);
	वापस hash__pte_update(mm, addr, ptep, clr, set, huge);
पूर्ण
/*
 * For hash even अगर we have _PAGE_ACCESSED = 0, we करो a pte_update.
 * We currently हटाओ entries from the hashtable regardless of whether
 * the entry was young or dirty.
 *
 * We should be more पूर्णांकelligent about this but क्रम the moment we override
 * these functions and क्रमce a tlb flush unconditionally
 * For radix: H_PAGE_HASHPTE should be zero. Hence we can use the same
 * function क्रम both hash and radix.
 */
अटल अंतरभूत पूर्णांक __ptep_test_and_clear_young(काष्ठा mm_काष्ठा *mm,
					      अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	अचिन्हित दीर्घ old;

	अगर ((pte_raw(*ptep) & cpu_to_be64(_PAGE_ACCESSED | H_PAGE_HASHPTE)) == 0)
		वापस 0;
	old = pte_update(mm, addr, ptep, _PAGE_ACCESSED, 0, 0);
	वापस (old & _PAGE_ACCESSED) != 0;
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
#घोषणा ptep_test_and_clear_young(__vma, __addr, __ptep)	\
(अणु								\
	__ptep_test_and_clear_young((__vma)->vm_mm, __addr, __ptep); \
पूर्ण)

/*
 * On Book3S CPUs, clearing the accessed bit without a TLB flush
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
#घोषणा __HAVE_ARCH_PTEP_CLEAR_YOUNG_FLUSH
#घोषणा ptep_clear_flush_young ptep_test_and_clear_young

#घोषणा __HAVE_ARCH_PMDP_CLEAR_YOUNG_FLUSH
#घोषणा pmdp_clear_flush_young pmdp_test_and_clear_young

अटल अंतरभूत पूर्णांक __pte_ग_लिखो(pte_t pte)
अणु
	वापस !!(pte_raw(pte) & cpu_to_be64(_PAGE_WRITE));
पूर्ण

#अगर_घोषित CONFIG_NUMA_BALANCING
#घोषणा pte_savedग_लिखो pte_savedग_लिखो
अटल अंतरभूत bool pte_savedग_लिखो(pte_t pte)
अणु
	/*
	 * Saved ग_लिखो ptes are prot none ptes that करोesn't have
	 * privileged bit sit. We mark prot none as one which has
	 * present and pviliged bit set and RWX cleared. To mark
	 * protnone which used to have _PAGE_WRITE set we clear
	 * the privileged bit.
	 */
	वापस !(pte_raw(pte) & cpu_to_be64(_PAGE_RWX | _PAGE_PRIVILEGED));
पूर्ण
#अन्यथा
#घोषणा pte_savedग_लिखो pte_savedग_लिखो
अटल अंतरभूत bool pte_savedग_लिखो(pte_t pte)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte)
अणु
	वापस __pte_ग_लिखो(pte) || pte_savedग_लिखो(pte);
पूर्ण

अटल अंतरभूत पूर्णांक pte_पढ़ो(pte_t pte)
अणु
	वापस !!(pte_raw(pte) & cpu_to_be64(_PAGE_READ));
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_SET_WRPROTECT
अटल अंतरभूत व्योम ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				      pte_t *ptep)
अणु
	अगर (__pte_ग_लिखो(*ptep))
		pte_update(mm, addr, ptep, _PAGE_WRITE, 0, 0);
	अन्यथा अगर (unlikely(pte_savedग_लिखो(*ptep)))
		pte_update(mm, addr, ptep, 0, _PAGE_PRIVILEGED, 0);
पूर्ण

#घोषणा __HAVE_ARCH_HUGE_PTEP_SET_WRPROTECT
अटल अंतरभूत व्योम huge_ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm,
					   अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	/*
	 * We should not find protnone क्रम hugetlb, but this complete the
	 * पूर्णांकerface.
	 */
	अगर (__pte_ग_लिखो(*ptep))
		pte_update(mm, addr, ptep, _PAGE_WRITE, 0, 1);
	अन्यथा अगर (unlikely(pte_savedग_लिखो(*ptep)))
		pte_update(mm, addr, ptep, 0, _PAGE_PRIVILEGED, 1);
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_GET_AND_CLEAR
अटल अंतरभूत pte_t ptep_get_and_clear(काष्ठा mm_काष्ठा *mm,
				       अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	अचिन्हित दीर्घ old = pte_update(mm, addr, ptep, ~0UL, 0, 0);
	वापस __pte(old);
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_GET_AND_CLEAR_FULL
अटल अंतरभूत pte_t ptep_get_and_clear_full(काष्ठा mm_काष्ठा *mm,
					    अचिन्हित दीर्घ addr,
					    pte_t *ptep, पूर्णांक full)
अणु
	अगर (full && radix_enabled()) अणु
		/*
		 * We know that this is a full mm pte clear and
		 * hence can be sure there is no parallel set_pte.
		 */
		वापस radix__ptep_get_and_clear_full(mm, addr, ptep, full);
	पूर्ण
	वापस ptep_get_and_clear(mm, addr, ptep);
पूर्ण


अटल अंतरभूत व्योम pte_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			     pte_t * ptep)
अणु
	pte_update(mm, addr, ptep, ~0UL, 0, 0);
पूर्ण

अटल अंतरभूत पूर्णांक pte_dirty(pte_t pte)
अणु
	वापस !!(pte_raw(pte) & cpu_to_be64(_PAGE_सूचीTY));
पूर्ण

अटल अंतरभूत पूर्णांक pte_young(pte_t pte)
अणु
	वापस !!(pte_raw(pte) & cpu_to_be64(_PAGE_ACCESSED));
पूर्ण

अटल अंतरभूत पूर्णांक pte_special(pte_t pte)
अणु
	वापस !!(pte_raw(pte) & cpu_to_be64(_PAGE_SPECIAL));
पूर्ण

अटल अंतरभूत bool pte_exec(pte_t pte)
अणु
	वापस !!(pte_raw(pte) & cpu_to_be64(_PAGE_EXEC));
पूर्ण


#अगर_घोषित CONFIG_HAVE_ARCH_SOFT_सूचीTY
अटल अंतरभूत bool pte_soft_dirty(pte_t pte)
अणु
	वापस !!(pte_raw(pte) & cpu_to_be64(_PAGE_SOFT_सूचीTY));
पूर्ण

अटल अंतरभूत pte_t pte_mksoft_dirty(pte_t pte)
अणु
	वापस __pte_raw(pte_raw(pte) | cpu_to_be64(_PAGE_SOFT_सूचीTY));
पूर्ण

अटल अंतरभूत pte_t pte_clear_soft_dirty(pte_t pte)
अणु
	वापस __pte_raw(pte_raw(pte) & cpu_to_be64(~_PAGE_SOFT_सूचीTY));
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_SOFT_सूचीTY */

#अगर_घोषित CONFIG_NUMA_BALANCING
अटल अंतरभूत पूर्णांक pte_protnone(pte_t pte)
अणु
	वापस (pte_raw(pte) & cpu_to_be64(_PAGE_PRESENT | _PAGE_PTE | _PAGE_RWX)) ==
		cpu_to_be64(_PAGE_PRESENT | _PAGE_PTE);
पूर्ण

#घोषणा pte_mk_savedग_लिखो pte_mk_savedग_लिखो
अटल अंतरभूत pte_t pte_mk_savedग_लिखो(pte_t pte)
अणु
	/*
	 * Used by Autonuma subप्रणाली to preserve the ग_लिखो bit
	 * जबतक marking the pte PROT_NONE. Only allow this
	 * on PROT_NONE pte
	 */
	VM_BUG_ON((pte_raw(pte) & cpu_to_be64(_PAGE_PRESENT | _PAGE_RWX | _PAGE_PRIVILEGED)) !=
		  cpu_to_be64(_PAGE_PRESENT | _PAGE_PRIVILEGED));
	वापस __pte_raw(pte_raw(pte) & cpu_to_be64(~_PAGE_PRIVILEGED));
पूर्ण

#घोषणा pte_clear_savedग_लिखो pte_clear_savedग_लिखो
अटल अंतरभूत pte_t pte_clear_savedग_लिखो(pte_t pte)
अणु
	/*
	 * Used by KSM subप्रणाली to make a protnone pte पढ़ोonly.
	 */
	VM_BUG_ON(!pte_protnone(pte));
	वापस __pte_raw(pte_raw(pte) | cpu_to_be64(_PAGE_PRIVILEGED));
पूर्ण
#अन्यथा
#घोषणा pte_clear_savedग_लिखो pte_clear_savedग_लिखो
अटल अंतरभूत pte_t pte_clear_savedग_लिखो(pte_t pte)
अणु
	VM_WARN_ON(1);
	वापस __pte_raw(pte_raw(pte) & cpu_to_be64(~_PAGE_WRITE));
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */

अटल अंतरभूत bool pte_hw_valid(pte_t pte)
अणु
	वापस (pte_raw(pte) & cpu_to_be64(_PAGE_PRESENT | _PAGE_PTE)) ==
		cpu_to_be64(_PAGE_PRESENT | _PAGE_PTE);
पूर्ण

अटल अंतरभूत पूर्णांक pte_present(pte_t pte)
अणु
	/*
	 * A pte is considerent present अगर _PAGE_PRESENT is set.
	 * We also need to consider the pte present which is marked
	 * invalid during ptep_set_access_flags. Hence we look क्रम _PAGE_INVALID
	 * अगर we find _PAGE_PRESENT cleared.
	 */

	अगर (pte_hw_valid(pte))
		वापस true;
	वापस (pte_raw(pte) & cpu_to_be64(_PAGE_INVALID | _PAGE_PTE)) ==
		cpu_to_be64(_PAGE_INVALID | _PAGE_PTE);
पूर्ण

#अगर_घोषित CONFIG_PPC_MEM_KEYS
बाह्य bool arch_pte_access_permitted(u64 pte, bool ग_लिखो, bool execute);
#अन्यथा
अटल अंतरभूत bool arch_pte_access_permitted(u64 pte, bool ग_लिखो, bool execute)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_MEM_KEYS */

अटल अंतरभूत bool pte_user(pte_t pte)
अणु
	वापस !(pte_raw(pte) & cpu_to_be64(_PAGE_PRIVILEGED));
पूर्ण

#घोषणा pte_access_permitted pte_access_permitted
अटल अंतरभूत bool pte_access_permitted(pte_t pte, bool ग_लिखो)
अणु
	/*
	 * _PAGE_READ is needed क्रम any access and will be
	 * cleared क्रम PROT_NONE
	 */
	अगर (!pte_present(pte) || !pte_user(pte) || !pte_पढ़ो(pte))
		वापस false;

	अगर (ग_लिखो && !pte_ग_लिखो(pte))
		वापस false;

	वापस arch_pte_access_permitted(pte_val(pte), ग_लिखो, 0);
पूर्ण

/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 *
 * Even अगर PTEs can be अचिन्हित दीर्घ दीर्घ, a PFN is always an अचिन्हित
 * दीर्घ क्रम now.
 */
अटल अंतरभूत pte_t pfn_pte(अचिन्हित दीर्घ pfn, pgprot_t pgprot)
अणु
	VM_BUG_ON(pfn >> (64 - PAGE_SHIFT));
	VM_BUG_ON((pfn << PAGE_SHIFT) & ~PTE_RPN_MASK);

	वापस __pte(((pte_basic_t)pfn << PAGE_SHIFT) | pgprot_val(pgprot) | _PAGE_PTE);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pte_pfn(pte_t pte)
अणु
	वापस (pte_val(pte) & PTE_RPN_MASK) >> PAGE_SHIFT;
पूर्ण

/* Generic modअगरiers क्रम PTE bits */
अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	अगर (unlikely(pte_savedग_लिखो(pte)))
		वापस pte_clear_savedग_लिखो(pte);
	वापस __pte_raw(pte_raw(pte) & cpu_to_be64(~_PAGE_WRITE));
पूर्ण

अटल अंतरभूत pte_t pte_exprotect(pte_t pte)
अणु
	वापस __pte_raw(pte_raw(pte) & cpu_to_be64(~_PAGE_EXEC));
पूर्ण

अटल अंतरभूत pte_t pte_mkclean(pte_t pte)
अणु
	वापस __pte_raw(pte_raw(pte) & cpu_to_be64(~_PAGE_सूचीTY));
पूर्ण

अटल अंतरभूत pte_t pte_mkold(pte_t pte)
अणु
	वापस __pte_raw(pte_raw(pte) & cpu_to_be64(~_PAGE_ACCESSED));
पूर्ण

अटल अंतरभूत pte_t pte_mkexec(pte_t pte)
अणु
	वापस __pte_raw(pte_raw(pte) | cpu_to_be64(_PAGE_EXEC));
पूर्ण

अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	/*
	 * ग_लिखो implies पढ़ो, hence set both
	 */
	वापस __pte_raw(pte_raw(pte) | cpu_to_be64(_PAGE_RW));
पूर्ण

अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)
अणु
	वापस __pte_raw(pte_raw(pte) | cpu_to_be64(_PAGE_सूचीTY | _PAGE_SOFT_सूचीTY));
पूर्ण

अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)
अणु
	वापस __pte_raw(pte_raw(pte) | cpu_to_be64(_PAGE_ACCESSED));
पूर्ण

अटल अंतरभूत pte_t pte_mkspecial(pte_t pte)
अणु
	वापस __pte_raw(pte_raw(pte) | cpu_to_be64(_PAGE_SPECIAL));
पूर्ण

अटल अंतरभूत pte_t pte_mkhuge(pte_t pte)
अणु
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkdevmap(pte_t pte)
अणु
	वापस __pte_raw(pte_raw(pte) | cpu_to_be64(_PAGE_SPECIAL | _PAGE_DEVMAP));
पूर्ण

अटल अंतरभूत pte_t pte_mkprivileged(pte_t pte)
अणु
	वापस __pte_raw(pte_raw(pte) | cpu_to_be64(_PAGE_PRIVILEGED));
पूर्ण

अटल अंतरभूत pte_t pte_mkuser(pte_t pte)
अणु
	वापस __pte_raw(pte_raw(pte) & cpu_to_be64(~_PAGE_PRIVILEGED));
पूर्ण

/*
 * This is potentially called with a pmd as the argument, in which हाल it's not
 * safe to check _PAGE_DEVMAP unless we also confirm that _PAGE_PTE is set.
 * That's because the bit we use क्रम _PAGE_DEVMAP is not reserved क्रम software
 * use in page directory entries (ie. non-ptes).
 */
अटल अंतरभूत पूर्णांक pte_devmap(pte_t pte)
अणु
	u64 mask = cpu_to_be64(_PAGE_DEVMAP | _PAGE_PTE);

	वापस (pte_raw(pte) & mask) == mask;
पूर्ण

अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	/* FIXME!! check whether this need to be a conditional */
	वापस __pte_raw((pte_raw(pte) & cpu_to_be64(_PAGE_CHG_MASK)) |
			 cpu_to_be64(pgprot_val(newprot)));
पूर्ण

/* Encode and de-code a swap entry */
#घोषणा MAX_SWAPखाताS_CHECK() करो अणु \
	BUILD_BUG_ON(MAX_SWAPखाताS_SHIFT > SWP_TYPE_BITS); \
	/*							\
	 * Don't have overlapping bits with _PAGE_HPTEFLAGS	\
	 * We filter HPTEFLAGS on set_pte.			\
	 */							\
	BUILD_BUG_ON(_PAGE_HPTEFLAGS & (0x1f << _PAGE_BIT_SWAP_TYPE)); \
	BUILD_BUG_ON(_PAGE_HPTEFLAGS & _PAGE_SWP_SOFT_सूचीTY);	\
	पूर्ण जबतक (0)

#घोषणा SWP_TYPE_BITS 5
#घोषणा __swp_type(x)		(((x).val >> _PAGE_BIT_SWAP_TYPE) \
				& ((1UL << SWP_TYPE_BITS) - 1))
#घोषणा __swp_offset(x)		(((x).val & PTE_RPN_MASK) >> PAGE_SHIFT)
#घोषणा __swp_entry(type, offset)	((swp_entry_t) अणु \
				((type) << _PAGE_BIT_SWAP_TYPE) \
				| (((offset) << PAGE_SHIFT) & PTE_RPN_MASK)पूर्ण)
/*
 * swp_entry_t must be independent of pte bits. We build a swp_entry_t from
 * swap type and offset we get from swap and convert that to pte to find a
 * matching pte in linux page table.
 * Clear bits not found in swap entries here.
 */
#घोषणा __pte_to_swp_entry(pte)	((swp_entry_t) अणु pte_val((pte)) & ~_PAGE_PTE पूर्ण)
#घोषणा __swp_entry_to_pte(x)	__pte((x).val | _PAGE_PTE)
#घोषणा __pmd_to_swp_entry(pmd)	(__pte_to_swp_entry(pmd_pte(pmd)))
#घोषणा __swp_entry_to_pmd(x)	(pte_pmd(__swp_entry_to_pte(x)))

#अगर_घोषित CONFIG_MEM_SOFT_सूचीTY
#घोषणा _PAGE_SWP_SOFT_सूचीTY   (1UL << (SWP_TYPE_BITS + _PAGE_BIT_SWAP_TYPE))
#अन्यथा
#घोषणा _PAGE_SWP_SOFT_सूचीTY	0UL
#पूर्ण_अगर /* CONFIG_MEM_SOFT_सूचीTY */

#अगर_घोषित CONFIG_HAVE_ARCH_SOFT_सूचीTY
अटल अंतरभूत pte_t pte_swp_mksoft_dirty(pte_t pte)
अणु
	वापस __pte_raw(pte_raw(pte) | cpu_to_be64(_PAGE_SWP_SOFT_सूचीTY));
पूर्ण

अटल अंतरभूत bool pte_swp_soft_dirty(pte_t pte)
अणु
	वापस !!(pte_raw(pte) & cpu_to_be64(_PAGE_SWP_SOFT_सूचीTY));
पूर्ण

अटल अंतरभूत pte_t pte_swp_clear_soft_dirty(pte_t pte)
अणु
	वापस __pte_raw(pte_raw(pte) & cpu_to_be64(~_PAGE_SWP_SOFT_सूचीTY));
पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_SOFT_सूचीTY */

अटल अंतरभूत bool check_pte_access(अचिन्हित दीर्घ access, अचिन्हित दीर्घ ptev)
अणु
	/*
	 * This check क्रम _PAGE_RWX and _PAGE_PRESENT bits
	 */
	अगर (access & ~ptev)
		वापस false;
	/*
	 * This check क्रम access to privilege space
	 */
	अगर ((access & _PAGE_PRIVILEGED) != (ptev & _PAGE_PRIVILEGED))
		वापस false;

	वापस true;
पूर्ण
/*
 * Generic functions with hash/radix callbacks
 */

अटल अंतरभूत व्योम __ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
					   pte_t *ptep, pte_t entry,
					   अचिन्हित दीर्घ address,
					   पूर्णांक psize)
अणु
	अगर (radix_enabled())
		वापस radix__ptep_set_access_flags(vma, ptep, entry,
						    address, psize);
	वापस hash__ptep_set_access_flags(ptep, entry);
पूर्ण

#घोषणा __HAVE_ARCH_PTE_SAME
अटल अंतरभूत पूर्णांक pte_same(pte_t pte_a, pte_t pte_b)
अणु
	अगर (radix_enabled())
		वापस radix__pte_same(pte_a, pte_b);
	वापस hash__pte_same(pte_a, pte_b);
पूर्ण

अटल अंतरभूत पूर्णांक pte_none(pte_t pte)
अणु
	अगर (radix_enabled())
		वापस radix__pte_none(pte);
	वापस hash__pte_none(pte);
पूर्ण

अटल अंतरभूत व्योम __set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				pte_t *ptep, pte_t pte, पूर्णांक percpu)
अणु

	VM_WARN_ON(!(pte_raw(pte) & cpu_to_be64(_PAGE_PTE)));
	/*
	 * Keep the _PAGE_PTE added till we are sure we handle _PAGE_PTE
	 * in all the callers.
	 */
	pte = __pte_raw(pte_raw(pte) | cpu_to_be64(_PAGE_PTE));

	अगर (radix_enabled())
		वापस radix__set_pte_at(mm, addr, ptep, pte, percpu);
	वापस hash__set_pte_at(mm, addr, ptep, pte, percpu);
पूर्ण

#घोषणा _PAGE_CACHE_CTL	(_PAGE_SAO | _PAGE_NON_IDEMPOTENT | _PAGE_TOLERANT)

#घोषणा pgprot_noncached pgprot_noncached
अटल अंतरभूत pgprot_t pgprot_noncached(pgprot_t prot)
अणु
	वापस __pgprot((pgprot_val(prot) & ~_PAGE_CACHE_CTL) |
			_PAGE_NON_IDEMPOTENT);
पूर्ण

#घोषणा pgprot_noncached_wc pgprot_noncached_wc
अटल अंतरभूत pgprot_t pgprot_noncached_wc(pgprot_t prot)
अणु
	वापस __pgprot((pgprot_val(prot) & ~_PAGE_CACHE_CTL) |
			_PAGE_TOLERANT);
पूर्ण

#घोषणा pgprot_cached pgprot_cached
अटल अंतरभूत pgprot_t pgprot_cached(pgprot_t prot)
अणु
	वापस __pgprot((pgprot_val(prot) & ~_PAGE_CACHE_CTL));
पूर्ण

#घोषणा pgprot_ग_लिखोcombine pgprot_ग_लिखोcombine
अटल अंतरभूत pgprot_t pgprot_ग_लिखोcombine(pgprot_t prot)
अणु
	वापस pgprot_noncached_wc(prot);
पूर्ण
/*
 * check a pte mapping have cache inhibited property
 */
अटल अंतरभूत bool pte_ci(pte_t pte)
अणु
	__be64 pte_v = pte_raw(pte);

	अगर (((pte_v & cpu_to_be64(_PAGE_CACHE_CTL)) == cpu_to_be64(_PAGE_TOLERANT)) ||
	    ((pte_v & cpu_to_be64(_PAGE_CACHE_CTL)) == cpu_to_be64(_PAGE_NON_IDEMPOTENT)))
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत व्योम pmd_clear(pmd_t *pmdp)
अणु
	अगर (IS_ENABLED(CONFIG_DEBUG_VM) && !radix_enabled()) अणु
		/*
		 * Don't use this अगर we can possibly have a hash page table
		 * entry mapping this.
		 */
		WARN_ON((pmd_val(*pmdp) & (H_PAGE_HASHPTE | _PAGE_PTE)) == (H_PAGE_HASHPTE | _PAGE_PTE));
	पूर्ण
	*pmdp = __pmd(0);
पूर्ण

अटल अंतरभूत पूर्णांक pmd_none(pmd_t pmd)
अणु
	वापस !pmd_raw(pmd);
पूर्ण

अटल अंतरभूत पूर्णांक pmd_present(pmd_t pmd)
अणु
	/*
	 * A pmd is considerent present अगर _PAGE_PRESENT is set.
	 * We also need to consider the pmd present which is marked
	 * invalid during a split. Hence we look क्रम _PAGE_INVALID
	 * अगर we find _PAGE_PRESENT cleared.
	 */
	अगर (pmd_raw(pmd) & cpu_to_be64(_PAGE_PRESENT | _PAGE_INVALID))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_is_serializing(pmd_t pmd)
अणु
	/*
	 * If the pmd is undergoing a split, the _PAGE_PRESENT bit is clear
	 * and _PAGE_INVALID is set (see pmd_present, pmdp_invalidate).
	 *
	 * This condition may also occur when flushing a pmd जबतक flushing
	 * it (see ptep_modअगरy_prot_start), so callers must ensure this
	 * हाल is fine as well.
	 */
	अगर ((pmd_raw(pmd) & cpu_to_be64(_PAGE_PRESENT | _PAGE_INVALID)) ==
						cpu_to_be64(_PAGE_INVALID))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_bad(pmd_t pmd)
अणु
	अगर (radix_enabled())
		वापस radix__pmd_bad(pmd);
	वापस hash__pmd_bad(pmd);
पूर्ण

अटल अंतरभूत व्योम pud_clear(pud_t *pudp)
अणु
	अगर (IS_ENABLED(CONFIG_DEBUG_VM) && !radix_enabled()) अणु
		/*
		 * Don't use this अगर we can possibly have a hash page table
		 * entry mapping this.
		 */
		WARN_ON((pud_val(*pudp) & (H_PAGE_HASHPTE | _PAGE_PTE)) == (H_PAGE_HASHPTE | _PAGE_PTE));
	पूर्ण
	*pudp = __pud(0);
पूर्ण

अटल अंतरभूत पूर्णांक pud_none(pud_t pud)
अणु
	वापस !pud_raw(pud);
पूर्ण

अटल अंतरभूत पूर्णांक pud_present(pud_t pud)
अणु
	वापस !!(pud_raw(pud) & cpu_to_be64(_PAGE_PRESENT));
पूर्ण

बाह्य काष्ठा page *pud_page(pud_t pud);
बाह्य काष्ठा page *pmd_page(pmd_t pmd);
अटल अंतरभूत pte_t pud_pte(pud_t pud)
अणु
	वापस __pte_raw(pud_raw(pud));
पूर्ण

अटल अंतरभूत pud_t pte_pud(pte_t pte)
अणु
	वापस __pud_raw(pte_raw(pte));
पूर्ण
#घोषणा pud_ग_लिखो(pud)		pte_ग_लिखो(pud_pte(pud))

अटल अंतरभूत पूर्णांक pud_bad(pud_t pud)
अणु
	अगर (radix_enabled())
		वापस radix__pud_bad(pud);
	वापस hash__pud_bad(pud);
पूर्ण

#घोषणा pud_access_permitted pud_access_permitted
अटल अंतरभूत bool pud_access_permitted(pud_t pud, bool ग_लिखो)
अणु
	वापस pte_access_permitted(pud_pte(pud), ग_लिखो);
पूर्ण

#घोषणा __p4d_raw(x)	((p4d_t) अणु __pgd_raw(x) पूर्ण)
अटल अंतरभूत __be64 p4d_raw(p4d_t x)
अणु
	वापस pgd_raw(x.pgd);
पूर्ण

#घोषणा p4d_ग_लिखो(p4d)		pte_ग_लिखो(p4d_pte(p4d))

अटल अंतरभूत व्योम p4d_clear(p4d_t *p4dp)
अणु
	*p4dp = __p4d(0);
पूर्ण

अटल अंतरभूत पूर्णांक p4d_none(p4d_t p4d)
अणु
	वापस !p4d_raw(p4d);
पूर्ण

अटल अंतरभूत पूर्णांक p4d_present(p4d_t p4d)
अणु
	वापस !!(p4d_raw(p4d) & cpu_to_be64(_PAGE_PRESENT));
पूर्ण

अटल अंतरभूत pte_t p4d_pte(p4d_t p4d)
अणु
	वापस __pte_raw(p4d_raw(p4d));
पूर्ण

अटल अंतरभूत p4d_t pte_p4d(pte_t pte)
अणु
	वापस __p4d_raw(pte_raw(pte));
पूर्ण

अटल अंतरभूत पूर्णांक p4d_bad(p4d_t p4d)
अणु
	अगर (radix_enabled())
		वापस radix__p4d_bad(p4d);
	वापस hash__p4d_bad(p4d);
पूर्ण

#घोषणा p4d_access_permitted p4d_access_permitted
अटल अंतरभूत bool p4d_access_permitted(p4d_t p4d, bool ग_लिखो)
अणु
	वापस pte_access_permitted(p4d_pte(p4d), ग_लिखो);
पूर्ण

बाह्य काष्ठा page *p4d_page(p4d_t p4d);

/* Poपूर्णांकers in the page table tree are physical addresses */
#घोषणा __pgtable_ptr_val(ptr)	__pa(ptr)

#घोषणा pud_page_vaddr(pud)	__va(pud_val(pud) & ~PUD_MASKED_BITS)
#घोषणा p4d_page_vaddr(p4d)	__va(p4d_val(p4d) & ~P4D_MASKED_BITS)

#घोषणा pte_ERROR(e) \
	pr_err("%s:%d: bad pte %08lx.\n", __खाता__, __LINE__, pte_val(e))
#घोषणा pmd_ERROR(e) \
	pr_err("%s:%d: bad pmd %08lx.\n", __खाता__, __LINE__, pmd_val(e))
#घोषणा pud_ERROR(e) \
	pr_err("%s:%d: bad pud %08lx.\n", __खाता__, __LINE__, pud_val(e))
#घोषणा pgd_ERROR(e) \
	pr_err("%s:%d: bad pgd %08lx.\n", __खाता__, __LINE__, pgd_val(e))

अटल अंतरभूत पूर्णांक map_kernel_page(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ pa, pgprot_t prot)
अणु
	अगर (radix_enabled()) अणु
#अगर defined(CONFIG_PPC_RADIX_MMU) && defined(DEBUG_VM)
		अचिन्हित दीर्घ page_size = 1 << mmu_psize_defs[mmu_io_psize].shअगरt;
		WARN((page_size != PAGE_SIZE), "I/O page size != PAGE_SIZE");
#पूर्ण_अगर
		वापस radix__map_kernel_page(ea, pa, prot, PAGE_SIZE);
	पूर्ण
	वापस hash__map_kernel_page(ea, pa, prot);
पूर्ण

अटल अंतरभूत पूर्णांक __meminit vmemmap_create_mapping(अचिन्हित दीर्घ start,
						   अचिन्हित दीर्घ page_size,
						   अचिन्हित दीर्घ phys)
अणु
	अगर (radix_enabled())
		वापस radix__vmemmap_create_mapping(start, page_size, phys);
	वापस hash__vmemmap_create_mapping(start, page_size, phys);
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
अटल अंतरभूत व्योम vmemmap_हटाओ_mapping(अचिन्हित दीर्घ start,
					  अचिन्हित दीर्घ page_size)
अणु
	अगर (radix_enabled())
		वापस radix__vmemmap_हटाओ_mapping(start, page_size);
	वापस hash__vmemmap_हटाओ_mapping(start, page_size);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत pte_t pmd_pte(pmd_t pmd)
अणु
	वापस __pte_raw(pmd_raw(pmd));
पूर्ण

अटल अंतरभूत pmd_t pte_pmd(pte_t pte)
अणु
	वापस __pmd_raw(pte_raw(pte));
पूर्ण

अटल अंतरभूत pte_t *pmdp_ptep(pmd_t *pmd)
अणु
	वापस (pte_t *)pmd;
पूर्ण
#घोषणा pmd_pfn(pmd)		pte_pfn(pmd_pte(pmd))
#घोषणा pmd_dirty(pmd)		pte_dirty(pmd_pte(pmd))
#घोषणा pmd_young(pmd)		pte_young(pmd_pte(pmd))
#घोषणा pmd_mkold(pmd)		pte_pmd(pte_mkold(pmd_pte(pmd)))
#घोषणा pmd_wrprotect(pmd)	pte_pmd(pte_wrprotect(pmd_pte(pmd)))
#घोषणा pmd_सूची_गढ़ोty(pmd)	pte_pmd(pte_सूची_गढ़ोty(pmd_pte(pmd)))
#घोषणा pmd_mkclean(pmd)	pte_pmd(pte_mkclean(pmd_pte(pmd)))
#घोषणा pmd_mkyoung(pmd)	pte_pmd(pte_mkyoung(pmd_pte(pmd)))
#घोषणा pmd_mkग_लिखो(pmd)	pte_pmd(pte_mkग_लिखो(pmd_pte(pmd)))
#घोषणा pmd_mk_savedग_लिखो(pmd)	pte_pmd(pte_mk_savedग_लिखो(pmd_pte(pmd)))
#घोषणा pmd_clear_savedग_लिखो(pmd)	pte_pmd(pte_clear_savedग_लिखो(pmd_pte(pmd)))

#अगर_घोषित CONFIG_HAVE_ARCH_SOFT_सूचीTY
#घोषणा pmd_soft_dirty(pmd)    pte_soft_dirty(pmd_pte(pmd))
#घोषणा pmd_mksoft_dirty(pmd)  pte_pmd(pte_mksoft_dirty(pmd_pte(pmd)))
#घोषणा pmd_clear_soft_dirty(pmd) pte_pmd(pte_clear_soft_dirty(pmd_pte(pmd)))

#अगर_घोषित CONFIG_ARCH_ENABLE_THP_MIGRATION
#घोषणा pmd_swp_mksoft_dirty(pmd)	pte_pmd(pte_swp_mksoft_dirty(pmd_pte(pmd)))
#घोषणा pmd_swp_soft_dirty(pmd)		pte_swp_soft_dirty(pmd_pte(pmd))
#घोषणा pmd_swp_clear_soft_dirty(pmd)	pte_pmd(pte_swp_clear_soft_dirty(pmd_pte(pmd)))
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_HAVE_ARCH_SOFT_सूचीTY */

#अगर_घोषित CONFIG_NUMA_BALANCING
अटल अंतरभूत पूर्णांक pmd_protnone(pmd_t pmd)
अणु
	वापस pte_protnone(pmd_pte(pmd));
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */

#घोषणा pmd_ग_लिखो(pmd)		pte_ग_लिखो(pmd_pte(pmd))
#घोषणा __pmd_ग_लिखो(pmd)	__pte_ग_लिखो(pmd_pte(pmd))
#घोषणा pmd_savedग_लिखो(pmd)	pte_savedग_लिखो(pmd_pte(pmd))

#घोषणा pmd_access_permitted pmd_access_permitted
अटल अंतरभूत bool pmd_access_permitted(pmd_t pmd, bool ग_लिखो)
अणु
	/*
	 * pmdp_invalidate sets this combination (which is not caught by
	 * !pte_present() check in pte_access_permitted), to prevent
	 * lock-मुक्त lookups, as part of the serialize_against_pte_lookup()
	 * synchronisation.
	 *
	 * This also catches the हाल where the PTE's hardware PRESENT bit is
	 * cleared जबतक TLB is flushed, which is suboptimal but should not
	 * be frequent.
	 */
	अगर (pmd_is_serializing(pmd))
		वापस false;

	वापस pte_access_permitted(pmd_pte(pmd), ग_लिखो);
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
बाह्य pmd_t pfn_pmd(अचिन्हित दीर्घ pfn, pgprot_t pgprot);
बाह्य pmd_t mk_pmd(काष्ठा page *page, pgprot_t pgprot);
बाह्य pmd_t pmd_modअगरy(pmd_t pmd, pgprot_t newprot);
बाह्य व्योम set_pmd_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		       pmd_t *pmdp, pmd_t pmd);
अटल अंतरभूत व्योम update_mmu_cache_pmd(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ addr, pmd_t *pmd)
अणु
पूर्ण

बाह्य पूर्णांक hash__has_transparent_hugepage(व्योम);
अटल अंतरभूत पूर्णांक has_transparent_hugepage(व्योम)
अणु
	अगर (radix_enabled())
		वापस radix__has_transparent_hugepage();
	वापस hash__has_transparent_hugepage();
पूर्ण
#घोषणा has_transparent_hugepage has_transparent_hugepage

अटल अंतरभूत अचिन्हित दीर्घ
pmd_hugepage_update(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pmd_t *pmdp,
		    अचिन्हित दीर्घ clr, अचिन्हित दीर्घ set)
अणु
	अगर (radix_enabled())
		वापस radix__pmd_hugepage_update(mm, addr, pmdp, clr, set);
	वापस hash__pmd_hugepage_update(mm, addr, pmdp, clr, set);
पूर्ण

/*
 * वापसs true क्रम pmd migration entries, THP, devmap, hugetlb
 * But compile समय dependent on THP config
 */
अटल अंतरभूत पूर्णांक pmd_large(pmd_t pmd)
अणु
	वापस !!(pmd_raw(pmd) & cpu_to_be64(_PAGE_PTE));
पूर्ण

/*
 * For radix we should always find H_PAGE_HASHPTE zero. Hence
 * the below will work क्रम radix too
 */
अटल अंतरभूत पूर्णांक __pmdp_test_and_clear_young(काष्ठा mm_काष्ठा *mm,
					      अचिन्हित दीर्घ addr, pmd_t *pmdp)
अणु
	अचिन्हित दीर्घ old;

	अगर ((pmd_raw(*pmdp) & cpu_to_be64(_PAGE_ACCESSED | H_PAGE_HASHPTE)) == 0)
		वापस 0;
	old = pmd_hugepage_update(mm, addr, pmdp, _PAGE_ACCESSED, 0);
	वापस ((old & _PAGE_ACCESSED) != 0);
पूर्ण

#घोषणा __HAVE_ARCH_PMDP_SET_WRPROTECT
अटल अंतरभूत व्योम pmdp_set_wrprotect(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				      pmd_t *pmdp)
अणु
	अगर (__pmd_ग_लिखो((*pmdp)))
		pmd_hugepage_update(mm, addr, pmdp, _PAGE_WRITE, 0);
	अन्यथा अगर (unlikely(pmd_savedग_लिखो(*pmdp)))
		pmd_hugepage_update(mm, addr, pmdp, 0, _PAGE_PRIVILEGED);
पूर्ण

/*
 * Only वापसs true क्रम a THP. False क्रम pmd migration entry.
 * We also need to वापस true when we come across a pte that
 * in between a thp split. While splitting THP, we mark the pmd
 * invalid (pmdp_invalidate()) beक्रमe we set it with pte page
 * address. A pmd_trans_huge() check against a pmd entry during that समय
 * should वापस true.
 * We should not call this on a hugetlb entry. We should check क्रम HugeTLB
 * entry using vma->vm_flags
 * The page table walk rule is explained in Documentation/vm/transhuge.rst
 */
अटल अंतरभूत पूर्णांक pmd_trans_huge(pmd_t pmd)
अणु
	अगर (!pmd_present(pmd))
		वापस false;

	अगर (radix_enabled())
		वापस radix__pmd_trans_huge(pmd);
	वापस hash__pmd_trans_huge(pmd);
पूर्ण

#घोषणा __HAVE_ARCH_PMD_SAME
अटल अंतरभूत पूर्णांक pmd_same(pmd_t pmd_a, pmd_t pmd_b)
अणु
	अगर (radix_enabled())
		वापस radix__pmd_same(pmd_a, pmd_b);
	वापस hash__pmd_same(pmd_a, pmd_b);
पूर्ण

अटल अंतरभूत pmd_t __pmd_mkhuge(pmd_t pmd)
अणु
	अगर (radix_enabled())
		वापस radix__pmd_mkhuge(pmd);
	वापस hash__pmd_mkhuge(pmd);
पूर्ण

/*
 * pfn_pmd वापस a pmd_t that can be used as pmd pte entry.
 */
अटल अंतरभूत pmd_t pmd_mkhuge(pmd_t pmd)
अणु
#अगर_घोषित CONFIG_DEBUG_VM
	अगर (radix_enabled())
		WARN_ON((pmd_raw(pmd) & cpu_to_be64(_PAGE_PTE)) == 0);
	अन्यथा
		WARN_ON((pmd_raw(pmd) & cpu_to_be64(_PAGE_PTE | H_PAGE_THP_HUGE)) !=
			cpu_to_be64(_PAGE_PTE | H_PAGE_THP_HUGE));
#पूर्ण_अगर
	वापस pmd;
पूर्ण

#घोषणा __HAVE_ARCH_PMDP_SET_ACCESS_FLAGS
बाह्य पूर्णांक pmdp_set_access_flags(काष्ठा vm_area_काष्ठा *vma,
				 अचिन्हित दीर्घ address, pmd_t *pmdp,
				 pmd_t entry, पूर्णांक dirty);

#घोषणा __HAVE_ARCH_PMDP_TEST_AND_CLEAR_YOUNG
बाह्य पूर्णांक pmdp_test_and_clear_young(काष्ठा vm_area_काष्ठा *vma,
				     अचिन्हित दीर्घ address, pmd_t *pmdp);

#घोषणा __HAVE_ARCH_PMDP_HUGE_GET_AND_CLEAR
अटल अंतरभूत pmd_t pmdp_huge_get_and_clear(काष्ठा mm_काष्ठा *mm,
					    अचिन्हित दीर्घ addr, pmd_t *pmdp)
अणु
	अगर (radix_enabled())
		वापस radix__pmdp_huge_get_and_clear(mm, addr, pmdp);
	वापस hash__pmdp_huge_get_and_clear(mm, addr, pmdp);
पूर्ण

अटल अंतरभूत pmd_t pmdp_collapse_flush(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ address, pmd_t *pmdp)
अणु
	अगर (radix_enabled())
		वापस radix__pmdp_collapse_flush(vma, address, pmdp);
	वापस hash__pmdp_collapse_flush(vma, address, pmdp);
पूर्ण
#घोषणा pmdp_collapse_flush pmdp_collapse_flush

#घोषणा __HAVE_ARCH_PMDP_HUGE_GET_AND_CLEAR_FULL
pmd_t pmdp_huge_get_and_clear_full(काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ addr,
				   pmd_t *pmdp, पूर्णांक full);

#घोषणा __HAVE_ARCH_PGTABLE_DEPOSIT
अटल अंतरभूत व्योम pgtable_trans_huge_deposit(काष्ठा mm_काष्ठा *mm,
					      pmd_t *pmdp, pgtable_t pgtable)
अणु
	अगर (radix_enabled())
		वापस radix__pgtable_trans_huge_deposit(mm, pmdp, pgtable);
	वापस hash__pgtable_trans_huge_deposit(mm, pmdp, pgtable);
पूर्ण

#घोषणा __HAVE_ARCH_PGTABLE_WITHDRAW
अटल अंतरभूत pgtable_t pgtable_trans_huge_withdraw(काष्ठा mm_काष्ठा *mm,
						    pmd_t *pmdp)
अणु
	अगर (radix_enabled())
		वापस radix__pgtable_trans_huge_withdraw(mm, pmdp);
	वापस hash__pgtable_trans_huge_withdraw(mm, pmdp);
पूर्ण

#घोषणा __HAVE_ARCH_PMDP_INVALIDATE
बाह्य pmd_t pmdp_invalidate(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
			     pmd_t *pmdp);

#घोषणा pmd_move_must_withdraw pmd_move_must_withdraw
काष्ठा spinlock;
बाह्य पूर्णांक pmd_move_must_withdraw(काष्ठा spinlock *new_pmd_ptl,
				  काष्ठा spinlock *old_pmd_ptl,
				  काष्ठा vm_area_काष्ठा *vma);
/*
 * Hash translation mode use the deposited table to store hash pte
 * slot inक्रमmation.
 */
#घोषणा arch_needs_pgtable_deposit arch_needs_pgtable_deposit
अटल अंतरभूत bool arch_needs_pgtable_deposit(व्योम)
अणु
	अगर (radix_enabled())
		वापस false;
	वापस true;
पूर्ण
बाह्य व्योम serialize_against_pte_lookup(काष्ठा mm_काष्ठा *mm);


अटल अंतरभूत pmd_t pmd_mkdevmap(pmd_t pmd)
अणु
	अगर (radix_enabled())
		वापस radix__pmd_mkdevmap(pmd);
	वापस hash__pmd_mkdevmap(pmd);
पूर्ण

अटल अंतरभूत पूर्णांक pmd_devmap(pmd_t pmd)
अणु
	वापस pte_devmap(pmd_pte(pmd));
पूर्ण

अटल अंतरभूत पूर्णांक pud_devmap(pud_t pud)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pgd_devmap(pgd_t pgd)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

अटल अंतरभूत पूर्णांक pud_pfn(pud_t pud)
अणु
	/*
	 * Currently all calls to pud_pfn() are gated around a pud_devmap()
	 * check so this should never be used. If it grows another user we
	 * want to know about it.
	 */
	BUILD_BUG();
	वापस 0;
पूर्ण
#घोषणा __HAVE_ARCH_PTEP_MODIFY_PROT_TRANSACTION
pte_t ptep_modअगरy_prot_start(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ, pte_t *);
व्योम ptep_modअगरy_prot_commit(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ,
			     pte_t *, pte_t, pte_t);

/*
 * Returns true क्रम a R -> RW upgrade of pte
 */
अटल अंतरभूत bool is_pte_rw_upgrade(अचिन्हित दीर्घ old_val, अचिन्हित दीर्घ new_val)
अणु
	अगर (!(old_val & _PAGE_READ))
		वापस false;

	अगर ((!(old_val & _PAGE_WRITE)) && (new_val & _PAGE_WRITE))
		वापस true;

	वापस false;
पूर्ण

/*
 * Like pmd_huge() and pmd_large(), but works regardless of config options
 */
#घोषणा pmd_is_leaf pmd_is_leaf
#घोषणा pmd_leaf pmd_is_leaf
अटल अंतरभूत bool pmd_is_leaf(pmd_t pmd)
अणु
	वापस !!(pmd_raw(pmd) & cpu_to_be64(_PAGE_PTE));
पूर्ण

#घोषणा pud_is_leaf pud_is_leaf
#घोषणा pud_leaf pud_is_leaf
अटल अंतरभूत bool pud_is_leaf(pud_t pud)
अणु
	वापस !!(pud_raw(pud) & cpu_to_be64(_PAGE_PTE));
पूर्ण

#घोषणा p4d_is_leaf p4d_is_leaf
#घोषणा p4d_leaf p4d_is_leaf
अटल अंतरभूत bool p4d_is_leaf(p4d_t p4d)
अणु
	वापस !!(p4d_raw(p4d) & cpu_to_be64(_PAGE_PTE));
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_POWERPC_BOOK3S_64_PGTABLE_H_ */
