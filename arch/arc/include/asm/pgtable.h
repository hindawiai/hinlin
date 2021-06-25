<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * vineetg: May 2011
 *  -Folded PAGE_PRESENT (used by VM) and PAGE_VALID (used by MMU) पूर्णांकo 1.
 *     They are semantically the same although in dअगरferent contexts
 *     VALID marks a TLB entry exists and it will only happen अगर PRESENT
 *  - Utilise some unused मुक्त bits to confine PTE flags to 12 bits
 *     This is a must क्रम 4k pg-sz
 *
 * vineetg: Mar 2011 - changes to accommodate MMU TLB Page Descriptor mods
 *  -TLB Locking never really existed, except क्रम initial specs
 *  -SILENT_xxx not needed क्रम our port
 *  -Per my request, MMU V3 changes the layout of some of the bits
 *     to aव्योम a few shअगरts in TLB Miss handlers.
 *
 * vineetg: April 2010
 *  -PGD entry no दीर्घer contains any flags. If empty it is 0, otherwise has
 *   Pg-Tbl ptr. Thus pmd_present(), pmd_valid(), pmd_set( ) become simpler
 *
 * vineetg: April 2010
 *  -Switched क्रमm 8:11:13 split क्रम page table lookup to 11:8:13
 *  -this speeds up page table allocation itself as we now have to स_रखो 1K
 *    instead of 8k per page table.
 * -TODO: Right now page table alloc is 8K and rest 7K is unused
 *    need to optimise it
 *
 * Amit Bhor, Sameer Dhavale: Codito Technologies 2004
 */

#अगर_अघोषित _ASM_ARC_PGTABLE_H
#घोषणा _ASM_ARC_PGTABLE_H

#समावेश <linux/bits.h>
#समावेश <यंत्र-generic/pgtable-nopmd.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mmu.h>	/* to propagate CONFIG_ARC_MMU_VER <n> */

/**************************************************************************
 * Page Table Flags
 *
 * ARC700 MMU only deals with softare managed TLB entries.
 * Page Tables are purely क्रम Linux VM's consumption and the bits below are
 * suited to that (uniqueness). Hence some are not implemented in the TLB and
 * some have dअगरferent value in TLB.
 * e.g. MMU v2: K_READ bit is 8 and so is GLOBAL (possible because they live in
 *      seperate PD0 and PD1, which combined क्रमms a translation entry)
 *      जबतक क्रम PTE perspective, they are 8 and 9 respectively
 * with MMU v3: Most bits (except SHARED) represent the exact hardware pos
 *      (saves some bit shअगरt ops in TLB Miss hdlrs)
 */

#अगर (CONFIG_ARC_MMU_VER <= 2)

#घोषणा _PAGE_ACCESSED      (1<<1)	/* Page is accessed (S) */
#घोषणा _PAGE_CACHEABLE     (1<<2)	/* Page is cached (H) */
#घोषणा _PAGE_EXECUTE       (1<<3)	/* Page has user execute perm (H) */
#घोषणा _PAGE_WRITE         (1<<4)	/* Page has user ग_लिखो perm (H) */
#घोषणा _PAGE_READ          (1<<5)	/* Page has user पढ़ो perm (H) */
#घोषणा _PAGE_सूचीTY         (1<<6)	/* Page modअगरied (dirty) (S) */
#घोषणा _PAGE_SPECIAL       (1<<7)
#घोषणा _PAGE_GLOBAL        (1<<8)	/* Page is global (H) */
#घोषणा _PAGE_PRESENT       (1<<10)	/* TLB entry is valid (H) */

#अन्यथा	/* MMU v3 onwards */

#घोषणा _PAGE_CACHEABLE     (1<<0)	/* Page is cached (H) */
#घोषणा _PAGE_EXECUTE       (1<<1)	/* Page has user execute perm (H) */
#घोषणा _PAGE_WRITE         (1<<2)	/* Page has user ग_लिखो perm (H) */
#घोषणा _PAGE_READ          (1<<3)	/* Page has user पढ़ो perm (H) */
#घोषणा _PAGE_ACCESSED      (1<<4)	/* Page is accessed (S) */
#घोषणा _PAGE_सूचीTY         (1<<5)	/* Page modअगरied (dirty) (S) */
#घोषणा _PAGE_SPECIAL       (1<<6)

#अगर (CONFIG_ARC_MMU_VER >= 4)
#घोषणा _PAGE_WTHRU         (1<<7)	/* Page cache mode ग_लिखो-thru (H) */
#पूर्ण_अगर

#घोषणा _PAGE_GLOBAL        (1<<8)	/* Page is global (H) */
#घोषणा _PAGE_PRESENT       (1<<9)	/* TLB entry is valid (H) */

#अगर (CONFIG_ARC_MMU_VER >= 4)
#घोषणा _PAGE_HW_SZ         (1<<10)	/* Page Size indicator (H): 0 normal, 1 super */
#पूर्ण_अगर

#घोषणा _PAGE_SHARED_CODE   (1<<11)	/* Shared Code page with cmn vaddr
					   usable क्रम shared TLB entries (H) */

#घोषणा _PAGE_UNUSED_BIT    (1<<12)
#पूर्ण_अगर

/* vदो_स्मृति permissions */
#घोषणा _K_PAGE_PERMS  (_PAGE_EXECUTE | _PAGE_WRITE | _PAGE_READ | \
			_PAGE_GLOBAL | _PAGE_PRESENT)

#अगर_अघोषित CONFIG_ARC_CACHE_PAGES
#अघोषित _PAGE_CACHEABLE
#घोषणा _PAGE_CACHEABLE 0
#पूर्ण_अगर

#अगर_अघोषित _PAGE_HW_SZ
#घोषणा _PAGE_HW_SZ	0
#पूर्ण_अगर

/* Defaults क्रम every user page */
#घोषणा ___DEF (_PAGE_PRESENT | _PAGE_CACHEABLE)

/* Set of bits not changed in pte_modअगरy */
#घोषणा _PAGE_CHG_MASK	(PAGE_MASK_PHYS | _PAGE_ACCESSED | _PAGE_सूचीTY | \
							   _PAGE_SPECIAL)
/* More Abbrevaited helpers */
#घोषणा PAGE_U_NONE     __pgprot(___DEF)
#घोषणा PAGE_U_R        __pgprot(___DEF | _PAGE_READ)
#घोषणा PAGE_U_W_R      __pgprot(___DEF | _PAGE_READ | _PAGE_WRITE)
#घोषणा PAGE_U_X_R      __pgprot(___DEF | _PAGE_READ | _PAGE_EXECUTE)
#घोषणा PAGE_U_X_W_R    __pgprot(___DEF | _PAGE_READ | _PAGE_WRITE | \
						       _PAGE_EXECUTE)

#घोषणा PAGE_SHARED	PAGE_U_W_R

/* While kernel runs out of unstranslated space, vदो_स्मृति/modules use a chunk of
 * user vaddr space - visible in all addr spaces, but kernel mode only
 * Thus Global, all-kernel-access, no-user-access, cached
 */
#घोषणा PAGE_KERNEL          __pgprot(_K_PAGE_PERMS | _PAGE_CACHEABLE)

/* ioremap */
#घोषणा PAGE_KERNEL_NO_CACHE __pgprot(_K_PAGE_PERMS)

/* Masks क्रम actual TLB "PD"s */
#घोषणा PTE_BITS_IN_PD0		(_PAGE_GLOBAL | _PAGE_PRESENT | _PAGE_HW_SZ)
#घोषणा PTE_BITS_RWX		(_PAGE_EXECUTE | _PAGE_WRITE | _PAGE_READ)

#घोषणा PTE_BITS_NON_RWX_IN_PD1	(PAGE_MASK_PHYS | _PAGE_CACHEABLE)

/**************************************************************************
 * Mapping of vm_flags (Generic VM) to PTE flags (arch specअगरic)
 *
 * Certain हालs have 1:1 mapping
 *  e.g. __P101 means VM_READ, VM_EXEC and !VM_SHARED
 *       which directly corresponds to  PAGE_U_X_R
 *
 * Other rules which cause the भागergence from 1:1 mapping
 *
 *  1. Although ARC700 can करो exclusive execute/ग_लिखो protection (meaning R
 *     can be tracked independet of X/W unlike some other CPUs), still to
 *     keep things consistent with other archs:
 *      -Write implies Read:   W => R
 *      -Execute implies Read: X => R
 *
 *  2. Pvt Writable करोesn't have Write Enabled initially: Pvt-W => !W
 *     This is to enable COW mechanism
 */
	/* xwr */
#घोषणा __P000  PAGE_U_NONE
#घोषणा __P001  PAGE_U_R
#घोषणा __P010  PAGE_U_R	/* Pvt-W => !W */
#घोषणा __P011  PAGE_U_R	/* Pvt-W => !W */
#घोषणा __P100  PAGE_U_X_R	/* X => R */
#घोषणा __P101  PAGE_U_X_R
#घोषणा __P110  PAGE_U_X_R	/* Pvt-W => !W and X => R */
#घोषणा __P111  PAGE_U_X_R	/* Pvt-W => !W */

#घोषणा __S000  PAGE_U_NONE
#घोषणा __S001  PAGE_U_R
#घोषणा __S010  PAGE_U_W_R	/* W => R */
#घोषणा __S011  PAGE_U_W_R
#घोषणा __S100  PAGE_U_X_R	/* X => R */
#घोषणा __S101  PAGE_U_X_R
#घोषणा __S110  PAGE_U_X_W_R	/* X => R */
#घोषणा __S111  PAGE_U_X_W_R

/****************************************************************
 * 2 tier (PGD:PTE) software page walker
 *
 * [31]		    32 bit भव address              [0]
 * -------------------------------------------------------
 * |               | <------------ PGसूची_SHIFT ----------> |
 * |		   |					 |
 * | BITS_FOR_PGD  |  BITS_FOR_PTE  | <-- PAGE_SHIFT --> |
 * -------------------------------------------------------
 *       |                  |                |
 *       |                  |                --> off in page frame
 *       |                  ---> index पूर्णांकo Page Table
 *       ----> index पूर्णांकo Page Directory
 *
 * In a single page size configuration, only PAGE_SHIFT is fixed
 * So both PGD and PTE sizing can be tweaked
 *  e.g. 8K page (PAGE_SHIFT 13) can have
 *  - PGसूची_SHIFT 21  -> 11:8:13 address split
 *  - PGसूची_SHIFT 24  -> 8:11:13 address split
 *
 * If Super Page is configured, PGसूची_SHIFT becomes fixed too,
 * so the sizing flexibility is gone.
 */

#अगर defined(CONFIG_ARC_HUGEPAGE_16M)
#घोषणा PGसूची_SHIFT	24
#या_अगर defined(CONFIG_ARC_HUGEPAGE_2M)
#घोषणा PGसूची_SHIFT	21
#अन्यथा
/*
 * Only Normal page support so "hackable" (see comment above)
 * Default value provides 11:8:13 (8K), 11:9:12 (4K)
 */
#घोषणा PGसूची_SHIFT	21
#पूर्ण_अगर

#घोषणा BITS_FOR_PTE	(PGसूची_SHIFT - PAGE_SHIFT)
#घोषणा BITS_FOR_PGD	(32 - PGसूची_SHIFT)

#घोषणा PGसूची_SIZE	BIT(PGसूची_SHIFT)	/* vaddr span, not PDG sz */
#घोषणा PGसूची_MASK	(~(PGसूची_SIZE-1))

#घोषणा	PTRS_PER_PTE	BIT(BITS_FOR_PTE)
#घोषणा	PTRS_PER_PGD	BIT(BITS_FOR_PGD)

/*
 * Number of entries a user land program use.
 * TASK_SIZE is the maximum vaddr that can be used by a userland program.
 */
#घोषणा	USER_PTRS_PER_PGD	(TASK_SIZE / PGसूची_SIZE)

/*
 * No special requirements क्रम lowest भव address we permit any user space
 * mapping to be mapped at.
 */
#घोषणा FIRST_USER_ADDRESS      0UL


/****************************************************************
 * Bucket load of VM Helpers
 */

#अगर_अघोषित __ASSEMBLY__

#घोषणा pte_ERROR(e) \
	pr_crit("%s:%d: bad pte %08lx.\n", __खाता__, __LINE__, pte_val(e))
#घोषणा pgd_ERROR(e) \
	pr_crit("%s:%d: bad pgd %08lx.\n", __खाता__, __LINE__, pgd_val(e))

/* the zero page used क्रम uninitialized and anonymous pages */
बाह्य अक्षर empty_zero_page[PAGE_SIZE];
#घोषणा ZERO_PAGE(vaddr)	(virt_to_page(empty_zero_page))

#घोषणा set_pte(pteptr, pteval)	((*(pteptr)) = (pteval))
#घोषणा set_pmd(pmdptr, pmdval)	(*(pmdptr) = pmdval)

/* find the page descriptor of the Page Tbl ref by PMD entry */
#घोषणा pmd_page(pmd)		virt_to_page(pmd_val(pmd) & PAGE_MASK)

/* find the logical addr (phy क्रम ARC) of the Page Tbl ref by PMD entry */
#घोषणा pmd_page_vaddr(pmd)	(pmd_val(pmd) & PAGE_MASK)

/* In a 2 level sys, setup the PGD entry with PTE value */
अटल अंतरभूत व्योम pmd_set(pmd_t *pmdp, pte_t *ptep)
अणु
	pmd_val(*pmdp) = (अचिन्हित दीर्घ)ptep;
पूर्ण

#घोषणा pte_none(x)			(!pte_val(x))
#घोषणा pte_present(x)			(pte_val(x) & _PAGE_PRESENT)
#घोषणा pte_clear(mm, addr, ptep)	set_pte_at(mm, addr, ptep, __pte(0))

#घोषणा pmd_none(x)			(!pmd_val(x))
#घोषणा	pmd_bad(x)			((pmd_val(x) & ~PAGE_MASK))
#घोषणा pmd_present(x)			(pmd_val(x))
#घोषणा pmd_leaf(x)			(pmd_val(x) & _PAGE_HW_SZ)
#घोषणा pmd_clear(xp)			करो अणु pmd_val(*(xp)) = 0; पूर्ण जबतक (0)

#घोषणा pte_page(pte)		pfn_to_page(pte_pfn(pte))
#घोषणा mk_pte(page, prot)	pfn_pte(page_to_pfn(page), prot)
#घोषणा pfn_pte(pfn, prot)	__pte(__pfn_to_phys(pfn) | pgprot_val(prot))

/* Don't use virt_to_pfn क्रम macros below: could cause truncations क्रम PAE40*/
#घोषणा pte_pfn(pte)		(pte_val(pte) >> PAGE_SHIFT)

/* Zoo of pte_xxx function */
#घोषणा pte_पढ़ो(pte)		(pte_val(pte) & _PAGE_READ)
#घोषणा pte_ग_लिखो(pte)		(pte_val(pte) & _PAGE_WRITE)
#घोषणा pte_dirty(pte)		(pte_val(pte) & _PAGE_सूचीTY)
#घोषणा pte_young(pte)		(pte_val(pte) & _PAGE_ACCESSED)
#घोषणा pte_special(pte)	(pte_val(pte) & _PAGE_SPECIAL)

#घोषणा PTE_BIT_FUNC(fn, op) \
	अटल अंतरभूत pte_t pte_##fn(pte_t pte) अणु pte_val(pte) op; वापस pte; पूर्ण

PTE_BIT_FUNC(mknotpresent,	&= ~(_PAGE_PRESENT));
PTE_BIT_FUNC(wrprotect,	&= ~(_PAGE_WRITE));
PTE_BIT_FUNC(mkग_लिखो,	|= (_PAGE_WRITE));
PTE_BIT_FUNC(mkclean,	&= ~(_PAGE_सूचीTY));
PTE_BIT_FUNC(सूची_गढ़ोty,	|= (_PAGE_सूचीTY));
PTE_BIT_FUNC(mkold,	&= ~(_PAGE_ACCESSED));
PTE_BIT_FUNC(mkyoung,	|= (_PAGE_ACCESSED));
PTE_BIT_FUNC(exprotect,	&= ~(_PAGE_EXECUTE));
PTE_BIT_FUNC(mkexec,	|= (_PAGE_EXECUTE));
PTE_BIT_FUNC(mkspecial,	|= (_PAGE_SPECIAL));
PTE_BIT_FUNC(mkhuge,	|= (_PAGE_HW_SZ));

अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	वापस __pte((pte_val(pte) & _PAGE_CHG_MASK) | pgprot_val(newprot));
पूर्ण

/* Macro to mark a page protection as uncacheable */
#घोषणा pgprot_noncached(prot)	(__pgprot(pgprot_val(prot) & ~_PAGE_CACHEABLE))

अटल अंतरभूत व्योम set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      pte_t *ptep, pte_t pteval)
अणु
	set_pte(ptep, pteval);
पूर्ण

/*
 * Macro to quickly access the PGD entry, utlising the fact that some
 * arch may cache the poपूर्णांकer to Page Directory of "current" task
 * in a MMU रेजिस्टर
 *
 * Thus task->mm->pgd (3 poपूर्णांकer dereferences, cache misses etc simply
 * becomes पढ़ो a रेजिस्टर
 *
 * ********CAUTION*******:
 * Kernel code might be dealing with some mm_काष्ठा of NON "current"
 * Thus use this macro only when you are certain that "current" is current
 * e.g. when dealing with संकेत frame setup code etc
 */
#अगर_घोषित ARC_USE_SCRATCH_REG
#घोषणा pgd_offset_fast(mm, addr)	\
(अणु					\
	pgd_t *pgd_base = (pgd_t *) पढ़ो_aux_reg(ARC_REG_SCRATCH_DATA0);  \
	pgd_base + pgd_index(addr);	\
पूर्ण)
#अन्यथा
#घोषणा pgd_offset_fast(mm, addr)	pgd_offset(mm, addr)
#पूर्ण_अगर

बाह्य pgd_t swapper_pg_dir[] __aligned(PAGE_SIZE);
व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
		      pte_t *ptep);

/* Encode swap अणुtype,offपूर्ण tuple पूर्णांकo PTE
 * We reserve 13 bits क्रम 5-bit @type, keeping bits 12-5 zero, ensuring that
 * PAGE_PRESENT is zero in a PTE holding swap "identifier"
 */
#घोषणा __swp_entry(type, off)	((swp_entry_t) अणु \
					((type) & 0x1f) | ((off) << 13) पूर्ण)

/* Decode a PTE containing swap "identifier "पूर्णांकo स्थिरituents */
#घोषणा __swp_type(pte_lookalike)	(((pte_lookalike).val) & 0x1f)
#घोषणा __swp_offset(pte_lookalike)	((pte_lookalike).val >> 13)

/* NOPs, to keep generic kernel happy */
#घोषणा __pte_to_swp_entry(pte)	((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(x)	((pte_t) अणु (x).val पूर्ण)

#घोषणा kern_addr_valid(addr)	(1)

/*
 * remap a physical page `pfn' of size `size' with page protection `prot'
 * पूर्णांकo भव address `from'
 */
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
#समावेश <यंत्र/hugepage.h>
#पूर्ण_अगर

/* to cope with aliasing VIPT cache */
#घोषणा HAVE_ARCH_UNMAPPED_AREA

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर
