<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2008-2009 PetaLogix
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 */

#अगर_अघोषित _ASM_MICROBLAZE_PGTABLE_H
#घोषणा _ASM_MICROBLAZE_PGTABLE_H

#समावेश <यंत्र/setup.h>

#अगर_अघोषित __ASSEMBLY__
बाह्य पूर्णांक mem_init_करोne;
#पूर्ण_अगर

#समावेश <यंत्र-generic/pgtable-nopmd.h>

#अगर_घोषित __KERNEL__
#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/sched.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <यंत्र/processor.h>		/* For TASK_SIZE */
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/page.h>

#घोषणा FIRST_USER_ADDRESS	0UL

बाह्य अचिन्हित दीर्घ va_to_phys(अचिन्हित दीर्घ address);
बाह्य pte_t *va_to_pte(अचिन्हित दीर्घ address);

/*
 * The following only work अगर pte_present() is true.
 * Undefined behaviour अगर not..
 */

/* Start and end of the vदो_स्मृति area. */
/* Make sure to map the vदो_स्मृति area above the pinned kernel memory area
   of 32Mb.  */
#घोषणा VMALLOC_START	(CONFIG_KERNEL_START + CONFIG_LOWMEM_SIZE)
#घोषणा VMALLOC_END	ioremap_bot

#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * Macro to mark a page protection value as "uncacheable".
 */

#घोषणा _PAGE_CACHE_CTL	(_PAGE_GUARDED | _PAGE_NO_CACHE | \
							_PAGE_WRITETHRU)

#घोषणा pgprot_noncached(prot) \
			(__pgprot((pgprot_val(prot) & ~_PAGE_CACHE_CTL) | \
					_PAGE_NO_CACHE | _PAGE_GUARDED))

#घोषणा pgprot_noncached_wc(prot) \
			 (__pgprot((pgprot_val(prot) & ~_PAGE_CACHE_CTL) | \
							_PAGE_NO_CACHE))

/*
 * The MicroBlaze MMU is identical to the PPC-40x MMU, and uses a hash
 * table containing PTEs, together with a set of 16 segment रेजिस्टरs, to
 * define the भव to physical address mapping.
 *
 * We use the hash table as an extended TLB, i.e. a cache of currently
 * active mappings.  We मुख्यtain a two-level page table tree, much
 * like that used by the i386, क्रम the sake of the Linux memory
 * management code.  Low-level assembler code in hashtable.S
 * (procedure hash_page) is responsible क्रम extracting ptes from the
 * tree and putting them पूर्णांकo the hash table when necessary, and
 * updating the accessed and modअगरied bits in the page table tree.
 */

/*
 * The MicroBlaze processor has a TLB architecture identical to PPC-40x. The
 * inकाष्ठाion and data sides share a unअगरied, 64-entry, semi-associative
 * TLB which is मुख्यtained totally under software control. In addition, the
 * inकाष्ठाion side has a hardware-managed, 2,4, or 8-entry, fully-associative
 * TLB which serves as a first level to the shared TLB. These two TLBs are
 * known as the UTLB and ITLB, respectively (see "mmu.h" क्रम definitions).
 */

/*
 * The normal हाल is that PTEs are 32-bits and we have a 1-page
 * 1024-entry pgdir poपूर्णांकing to 1-page 1024-entry PTE pages.  -- paulus
 *
 */

/* PGसूची_SHIFT determines what a top-level page table entry can map */
#घोषणा PGसूची_SHIFT	(PAGE_SHIFT + PTE_SHIFT)
#घोषणा PGसूची_SIZE	(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK	(~(PGसूची_SIZE-1))

/*
 * entries per page directory level: our page-table tree is two-level, so
 * we करोn't really have any PMD directory.
 */
#घोषणा PTRS_PER_PTE	(1 << PTE_SHIFT)
#घोषणा PTRS_PER_PMD	1
#घोषणा PTRS_PER_PGD	(1 << (32 - PGसूची_SHIFT))

#घोषणा USER_PTRS_PER_PGD	(TASK_SIZE / PGसूची_SIZE)
#घोषणा FIRST_USER_PGD_NR	0

#घोषणा USER_PGD_PTRS (PAGE_OFFSET >> PGसूची_SHIFT)
#घोषणा KERNEL_PGD_PTRS (PTRS_PER_PGD-USER_PGD_PTRS)

#घोषणा pte_ERROR(e) \
	prपूर्णांकk(KERN_ERR "%s:%d: bad pte "PTE_FMT".\n", \
		__खाता__, __LINE__, pte_val(e))
#घोषणा pgd_ERROR(e) \
	prपूर्णांकk(KERN_ERR "%s:%d: bad pgd %08lx.\n", \
		__खाता__, __LINE__, pgd_val(e))

/*
 * Bits in a linux-style PTE.  These match the bits in the
 * (hardware-defined) PTE as बंदly as possible.
 */

/* There are several potential gotchas here.  The hardware TLBLO
 * field looks like this:
 *
 * 0  1  2  3  4  ... 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 * RPN.....................  0  0 EX WR ZSEL.......  W  I  M  G
 *
 * Where possible we make the Linux PTE bits match up with this
 *
 * - bits 20 and 21 must be cleared, because we use 4k pages (4xx can
 * support करोwn to 1k pages), this is करोne in the TLBMiss exception
 * handler.
 * - We use only zones 0 (क्रम kernel pages) and 1 (क्रम user pages)
 * of the 16 available.  Bit 24-26 of the TLB are cleared in the TLB
 * miss handler.  Bit 27 is PAGE_USER, thus selecting the correct
 * zone.
 * - PRESENT *must* be in the bottom two bits because swap cache
 * entries use the top 30 bits.  Because 4xx करोesn't support SMP
 * anyway, M is irrelevant so we borrow it क्रम PAGE_PRESENT.  Bit 30
 * is cleared in the TLB miss handler beक्रमe the TLB entry is loaded.
 * - All other bits of the PTE are loaded पूर्णांकo TLBLO without
 *  * modअगरication, leaving us only the bits 20, 21, 24, 25, 26, 30 क्रम
 * software PTE bits.  We actually use bits 21, 24, 25, and
 * 30 respectively क्रम the software bits: ACCESSED, सूचीTY, RW, and
 * PRESENT.
 */

/* Definitions क्रम MicroBlaze. */
#घोषणा	_PAGE_GUARDED	0x001	/* G: page is guarded from prefetch */
#घोषणा _PAGE_PRESENT	0x002	/* software: PTE contains a translation */
#घोषणा	_PAGE_NO_CACHE	0x004	/* I: caching is inhibited */
#घोषणा	_PAGE_WRITETHRU	0x008	/* W: caching is ग_लिखो-through */
#घोषणा	_PAGE_USER	0x010	/* matches one of the zone permission bits */
#घोषणा	_PAGE_RW	0x040	/* software: Writes permitted */
#घोषणा	_PAGE_सूचीTY	0x080	/* software: dirty page */
#घोषणा _PAGE_HWWRITE	0x100	/* hardware: Dirty & RW, set in exception */
#घोषणा _PAGE_HWEXEC	0x200	/* hardware: EX permission */
#घोषणा _PAGE_ACCESSED	0x400	/* software: R: page referenced */
#घोषणा _PMD_PRESENT	PAGE_MASK

/*
 * Some bits are unused...
 */
#अगर_अघोषित _PAGE_HASHPTE
#घोषणा _PAGE_HASHPTE	0
#पूर्ण_अगर
#अगर_अघोषित _PTE_NONE_MASK
#घोषणा _PTE_NONE_MASK	0
#पूर्ण_अगर
#अगर_अघोषित _PAGE_SHARED
#घोषणा _PAGE_SHARED	0
#पूर्ण_अगर
#अगर_अघोषित _PAGE_EXEC
#घोषणा _PAGE_EXEC	0
#पूर्ण_अगर

#घोषणा _PAGE_CHG_MASK	(PAGE_MASK | _PAGE_ACCESSED | _PAGE_सूचीTY)

/*
 * Note: the _PAGE_COHERENT bit स्वतःmatically माला_लो set in the hardware
 * PTE अगर CONFIG_SMP is defined (hash_page करोes this); there is no need
 * to have it in the Linux PTE, and in fact the bit could be reused क्रम
 * another purpose.  -- paulus.
 */
#घोषणा _PAGE_BASE	(_PAGE_PRESENT | _PAGE_ACCESSED)
#घोषणा _PAGE_WRENABLE	(_PAGE_RW | _PAGE_सूचीTY | _PAGE_HWWRITE)

#घोषणा _PAGE_KERNEL \
	(_PAGE_BASE | _PAGE_WRENABLE | _PAGE_SHARED | _PAGE_HWEXEC)

#घोषणा _PAGE_IO	(_PAGE_KERNEL | _PAGE_NO_CACHE | _PAGE_GUARDED)

#घोषणा PAGE_NONE	__pgprot(_PAGE_BASE)
#घोषणा PAGE_READONLY	__pgprot(_PAGE_BASE | _PAGE_USER)
#घोषणा PAGE_READONLY_X	__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_EXEC)
#घोषणा PAGE_SHARED	__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_RW)
#घोषणा PAGE_SHARED_X \
		__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_RW | _PAGE_EXEC)
#घोषणा PAGE_COPY	__pgprot(_PAGE_BASE | _PAGE_USER)
#घोषणा PAGE_COPY_X	__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_EXEC)

#घोषणा PAGE_KERNEL	__pgprot(_PAGE_KERNEL)
#घोषणा PAGE_KERNEL_RO	__pgprot(_PAGE_BASE | _PAGE_SHARED)
#घोषणा PAGE_KERNEL_CI	__pgprot(_PAGE_IO)

/*
 * We consider execute permission the same as पढ़ो.
 * Also, ग_लिखो permissions imply पढ़ो permissions.
 */
#घोषणा __P000	PAGE_NONE
#घोषणा __P001	PAGE_READONLY_X
#घोषणा __P010	PAGE_COPY
#घोषणा __P011	PAGE_COPY_X
#घोषणा __P100	PAGE_READONLY
#घोषणा __P101	PAGE_READONLY_X
#घोषणा __P110	PAGE_COPY
#घोषणा __P111	PAGE_COPY_X

#घोषणा __S000	PAGE_NONE
#घोषणा __S001	PAGE_READONLY_X
#घोषणा __S010	PAGE_SHARED
#घोषणा __S011	PAGE_SHARED_X
#घोषणा __S100	PAGE_READONLY
#घोषणा __S101	PAGE_READONLY_X
#घोषणा __S110	PAGE_SHARED
#घोषणा __S111	PAGE_SHARED_X

#अगर_अघोषित __ASSEMBLY__
/*
 * ZERO_PAGE is a global shared page that is always zero: used
 * क्रम zero-mapped memory areas etc..
 */
बाह्य अचिन्हित दीर्घ empty_zero_page[1024];
#घोषणा ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))

#पूर्ण_अगर /* __ASSEMBLY__ */

#घोषणा pte_none(pte)		((pte_val(pte) & ~_PTE_NONE_MASK) == 0)
#घोषणा pte_present(pte)	(pte_val(pte) & _PAGE_PRESENT)
#घोषणा pte_clear(mm, addr, ptep) \
	करो अणु set_pte_at((mm), (addr), (ptep), __pte(0)); पूर्ण जबतक (0)

#घोषणा pmd_none(pmd)		(!pmd_val(pmd))
#घोषणा	pmd_bad(pmd)		((pmd_val(pmd) & _PMD_PRESENT) == 0)
#घोषणा	pmd_present(pmd)	((pmd_val(pmd) & _PMD_PRESENT) != 0)
#घोषणा	pmd_clear(pmdp)		करो अणु pmd_val(*(pmdp)) = 0; पूर्ण जबतक (0)

#घोषणा pte_page(x)		(mem_map + (अचिन्हित दीर्घ) \
				((pte_val(x) - memory_start) >> PAGE_SHIFT))
#घोषणा PFN_SHIFT_OFFSET	(PAGE_SHIFT)

#घोषणा pte_pfn(x)		(pte_val(x) >> PFN_SHIFT_OFFSET)

#घोषणा pfn_pte(pfn, prot) \
	__pte(((pte_basic_t)(pfn) << PFN_SHIFT_OFFSET) | pgprot_val(prot))

#अगर_अघोषित __ASSEMBLY__
/*
 * The following only work अगर pte_present() is true.
 * Undefined behaviour अगर not..
 */
अटल अंतरभूत पूर्णांक pte_पढ़ो(pte_t pte)  अणु वापस pte_val(pte) & _PAGE_USER; पूर्ण
अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte) अणु वापस pte_val(pte) & _PAGE_RW; पूर्ण
अटल अंतरभूत पूर्णांक pte_exec(pte_t pte)  अणु वापस pte_val(pte) & _PAGE_EXEC; पूर्ण
अटल अंतरभूत पूर्णांक pte_dirty(pte_t pte) अणु वापस pte_val(pte) & _PAGE_सूचीTY; पूर्ण
अटल अंतरभूत पूर्णांक pte_young(pte_t pte) अणु वापस pte_val(pte) & _PAGE_ACCESSED; पूर्ण

अटल अंतरभूत व्योम pte_uncache(pte_t pte) अणु pte_val(pte) |= _PAGE_NO_CACHE; पूर्ण
अटल अंतरभूत व्योम pte_cache(pte_t pte)   अणु pte_val(pte) &= ~_PAGE_NO_CACHE; पूर्ण

अटल अंतरभूत pte_t pte_rdprotect(pte_t pte) \
		अणु pte_val(pte) &= ~_PAGE_USER; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_wrprotect(pte_t pte) \
	अणु pte_val(pte) &= ~(_PAGE_RW | _PAGE_HWWRITE); वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_exprotect(pte_t pte) \
	अणु pte_val(pte) &= ~_PAGE_EXEC; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mkclean(pte_t pte) \
	अणु pte_val(pte) &= ~(_PAGE_सूचीTY | _PAGE_HWWRITE); वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mkold(pte_t pte) \
	अणु pte_val(pte) &= ~_PAGE_ACCESSED; वापस pte; पूर्ण

अटल अंतरभूत pte_t pte_mkपढ़ो(pte_t pte) \
	अणु pte_val(pte) |= _PAGE_USER; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mkexec(pte_t pte) \
	अणु pte_val(pte) |= _PAGE_USER | _PAGE_EXEC; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte) \
	अणु pte_val(pte) |= _PAGE_RW; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte) \
	अणु pte_val(pte) |= _PAGE_सूचीTY; वापस pte; पूर्ण
अटल अंतरभूत pte_t pte_mkyoung(pte_t pte) \
	अणु pte_val(pte) |= _PAGE_ACCESSED; वापस pte; पूर्ण

/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 */

अटल अंतरभूत pte_t mk_pte_phys(phys_addr_t physpage, pgprot_t pgprot)
अणु
	pte_t pte;
	pte_val(pte) = physpage | pgprot_val(pgprot);
	वापस pte;
पूर्ण

#घोषणा mk_pte(page, pgprot) \
(अणु									   \
	pte_t pte;							   \
	pte_val(pte) = (((page - mem_map) << PAGE_SHIFT) + memory_start) |  \
			pgprot_val(pgprot);				   \
	pte;								   \
पूर्ण)

अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	pte_val(pte) = (pte_val(pte) & _PAGE_CHG_MASK) | pgprot_val(newprot);
	वापस pte;
पूर्ण

/*
 * Atomic PTE updates.
 *
 * pte_update clears and sets bit atomically, and वापसs
 * the old pte value.
 * The ((अचिन्हित दीर्घ)(p+1) - 4) hack is to get to the least-signअगरicant
 * 32 bits of the PTE regardless of whether PTEs are 32 or 64 bits.
 */
अटल अंतरभूत अचिन्हित दीर्घ pte_update(pte_t *p, अचिन्हित दीर्घ clr,
				अचिन्हित दीर्घ set)
अणु
	अचिन्हित दीर्घ flags, old, पंचांगp;

	raw_local_irq_save(flags);

	__यंत्र__ __अस्थिर__(	"lw	%0, %2, r0	\n"
				"andn	%1, %0, %3	\n"
				"or	%1, %1, %4	\n"
				"sw	%1, %2, r0	\n"
			: "=&r" (old), "=&r" (पंचांगp)
			: "r" ((अचिन्हित दीर्घ)(p + 1) - 4), "r" (clr), "r" (set)
			: "cc");

	raw_local_irq_restore(flags);

	वापस old;
पूर्ण

/*
 * set_pte stores a linux PTE पूर्णांकo the linux page table.
 */
अटल अंतरभूत व्योम set_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		pte_t *ptep, pte_t pte)
अणु
	*ptep = pte;
पूर्ण

अटल अंतरभूत व्योम set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		pte_t *ptep, pte_t pte)
अणु
	*ptep = pte;
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
अटल अंतरभूत पूर्णांक ptep_test_and_clear_young(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	वापस (pte_update(ptep, _PAGE_ACCESSED, 0) & _PAGE_ACCESSED) != 0;
पूर्ण

अटल अंतरभूत पूर्णांक ptep_test_and_clear_dirty(काष्ठा mm_काष्ठा *mm,
		अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	वापस (pte_update(ptep, \
		(_PAGE_सूचीTY | _PAGE_HWWRITE), 0) & _PAGE_सूचीTY) != 0;
पूर्ण

#घोषणा __HAVE_ARCH_PTEP_GET_AND_CLEAR
अटल अंतरभूत pte_t ptep_get_and_clear(काष्ठा mm_काष्ठा *mm,
		अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	वापस __pte(pte_update(ptep, ~_PAGE_HASHPTE, 0));
पूर्ण

/*अटल अंतरभूत व्योम ptep_set_wrprotect(काष्ठा mm_काष्ठा *mm,
		अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pte_update(ptep, (_PAGE_RW | _PAGE_HWWRITE), 0);
पूर्ण*/

अटल अंतरभूत व्योम ptep_सूची_गढ़ोty(काष्ठा mm_काष्ठा *mm,
		अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	pte_update(ptep, 0, _PAGE_सूचीTY);
पूर्ण

/*#घोषणा pte_same(A,B)	(((pte_val(A) ^ pte_val(B)) & ~_PAGE_HASHPTE) == 0)*/

/* Convert pmd entry to page */
/* our pmd entry is an effective address of pte table*/
/* वापसs effective address of the pmd entry*/
अटल अंतरभूत अचिन्हित दीर्घ pmd_page_vaddr(pmd_t pmd)
अणु
	वापस ((अचिन्हित दीर्घ) (pmd_val(pmd) & PAGE_MASK));
पूर्ण

/* वापसs काष्ठा *page of the pmd entry*/
#घोषणा pmd_page(pmd)	(pfn_to_page(__pa(pmd_val(pmd)) >> PAGE_SHIFT))

/* Find an entry in the third-level page table.. */

बाह्य pgd_t swapper_pg_dir[PTRS_PER_PGD];

/*
 * Encode and decode a swap entry.
 * Note that the bits we use in a PTE क्रम representing a swap entry
 * must not include the _PAGE_PRESENT bit, or the _PAGE_HASHPTE bit
 * (अगर used).  -- paulus
 */
#घोषणा __swp_type(entry)		((entry).val & 0x3f)
#घोषणा __swp_offset(entry)	((entry).val >> 6)
#घोषणा __swp_entry(type, offset) \
		((swp_entry_t) अणु (type) | ((offset) << 6) पूर्ण)
#घोषणा __pte_to_swp_entry(pte)	((swp_entry_t) अणु pte_val(pte) >> 2 पूर्ण)
#घोषणा __swp_entry_to_pte(x)	((pte_t) अणु (x).val << 2 पूर्ण)

बाह्य अचिन्हित दीर्घ iopa(अचिन्हित दीर्घ addr);

/* Values क्रम nocacheflag and cmode */
/* These are not used by the APUS kernel_map, but prevents
 * compilation errors.
 */
#घोषणा	IOMAP_FULL_CACHING	0
#घोषणा	IOMAP_NOCACHE_SER	1
#घोषणा	IOMAP_NOCACHE_NONSER	2
#घोषणा	IOMAP_NO_COPYBACK	3

/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
#घोषणा kern_addr_valid(addr)	(1)

व्योम करो_page_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address,
		   अचिन्हित दीर्घ error_code);

व्योम mapin_ram(व्योम);
पूर्णांक map_page(अचिन्हित दीर्घ va, phys_addr_t pa, पूर्णांक flags);

बाह्य पूर्णांक mem_init_करोne;

यंत्रlinkage व्योम __init mmu_init(व्योम);

व्योम __init *early_get_page(व्योम);

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __KERNEL__ */

#अगर_अघोषित __ASSEMBLY__
बाह्य अचिन्हित दीर्घ ioremap_bot, ioremap_base;

व्योम setup_memory(व्योम);
#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_MICROBLAZE_PGTABLE_H */
