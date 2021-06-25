<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * pgtable.h: SpitFire page table operations.
 *
 * Copyright 1996,1997 David S. Miller (davem@caip.rutgers.edu)
 * Copyright 1997,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 */

#अगर_अघोषित _SPARC64_PGTABLE_H
#घोषणा _SPARC64_PGTABLE_H

/* This file contains the functions and defines necessary to modअगरy and use
 * the SpitFire page tables.
 */

#समावेश <यंत्र-generic/pgtable-nop4d.h>
#समावेश <linux/compiler.h>
#समावेश <linux/स्थिर.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/spitfire.h>
#समावेश <यंत्र/asi.h>
#समावेश <यंत्र/adi.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>

/* The kernel image occupies 0x4000000 to 0x6000000 (4MB --> 96MB).
 * The page copy blockops can use 0x6000000 to 0x8000000.
 * The 8K TSB is mapped in the 0x8000000 to 0x8400000 range.
 * The 4M TSB is mapped in the 0x8400000 to 0x8800000 range.
 * The PROM resides in an area spanning 0xf0000000 to 0x100000000.
 * The vदो_स्मृति area spans 0x100000000 to 0x200000000.
 * Since modules need to be in the lowest 32-bits of the address space,
 * we place them right beक्रमe the OBP area from 0x10000000 to 0xf0000000.
 * There is a single अटल kernel PMD which maps from 0x0 to address
 * 0x400000000.
 */
#घोषणा	TLBTEMP_BASE		_AC(0x0000000006000000,UL)
#घोषणा	TSBMAP_8K_BASE		_AC(0x0000000008000000,UL)
#घोषणा	TSBMAP_4M_BASE		_AC(0x0000000008400000,UL)
#घोषणा MODULES_VADDR		_AC(0x0000000010000000,UL)
#घोषणा MODULES_LEN		_AC(0x00000000e0000000,UL)
#घोषणा MODULES_END		_AC(0x00000000f0000000,UL)
#घोषणा LOW_OBP_ADDRESS		_AC(0x00000000f0000000,UL)
#घोषणा HI_OBP_ADDRESS		_AC(0x0000000100000000,UL)
#घोषणा VMALLOC_START		_AC(0x0000000100000000,UL)
#घोषणा VMEMMAP_BASE		VMALLOC_END

/* PMD_SHIFT determines the size of the area a second-level page
 * table can map
 */
#घोषणा PMD_SHIFT	(PAGE_SHIFT + (PAGE_SHIFT-3))
#घोषणा PMD_SIZE	(_AC(1,UL) << PMD_SHIFT)
#घोषणा PMD_MASK	(~(PMD_SIZE-1))
#घोषणा PMD_BITS	(PAGE_SHIFT - 3)

/* PUD_SHIFT determines the size of the area a third-level page
 * table can map
 */
#घोषणा PUD_SHIFT	(PMD_SHIFT + PMD_BITS)
#घोषणा PUD_SIZE	(_AC(1,UL) << PUD_SHIFT)
#घोषणा PUD_MASK	(~(PUD_SIZE-1))
#घोषणा PUD_BITS	(PAGE_SHIFT - 3)

/* PGसूची_SHIFT determines what a fourth-level page table entry can map */
#घोषणा PGसूची_SHIFT	(PUD_SHIFT + PUD_BITS)
#घोषणा PGसूची_SIZE	(_AC(1,UL) << PGसूची_SHIFT)
#घोषणा PGसूची_MASK	(~(PGसूची_SIZE-1))
#घोषणा PGसूची_BITS	(PAGE_SHIFT - 3)

#अगर (MAX_PHYS_ADDRESS_BITS > PGसूची_SHIFT + PGसूची_BITS)
#त्रुटि MAX_PHYS_ADDRESS_BITS exceeds what kernel page tables can support
#पूर्ण_अगर

#अगर (PGसूची_SHIFT + PGसूची_BITS) != 53
#त्रुटि Page table parameters करो not cover भव address space properly.
#पूर्ण_अगर

#अगर (PMD_SHIFT != HPAGE_SHIFT)
#त्रुटि PMD_SHIFT must equal HPAGE_SHIFT क्रम transparent huge pages.
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

बाह्य अचिन्हित दीर्घ VMALLOC_END;

#घोषणा vmemmap			((काष्ठा page *)VMEMMAP_BASE)

#समावेश <linux/sched.h>

bool kern_addr_valid(अचिन्हित दीर्घ addr);

/* Entries per page directory level. */
#घोषणा PTRS_PER_PTE	(1UL << (PAGE_SHIFT-3))
#घोषणा PTRS_PER_PMD	(1UL << PMD_BITS)
#घोषणा PTRS_PER_PUD	(1UL << PUD_BITS)
#घोषणा PTRS_PER_PGD	(1UL << PGसूची_BITS)

/* Kernel has a separate 44bit address space. */
#घोषणा FIRST_USER_ADDRESS	0UL

#घोषणा pmd_ERROR(e)							\
	pr_err("%s:%d: bad pmd %p(%016lx) seen at (%pS)\n",		\
	       __खाता__, __LINE__, &(e), pmd_val(e), __builtin_वापस_address(0))
#घोषणा pud_ERROR(e)							\
	pr_err("%s:%d: bad pud %p(%016lx) seen at (%pS)\n",		\
	       __खाता__, __LINE__, &(e), pud_val(e), __builtin_वापस_address(0))
#घोषणा pgd_ERROR(e)							\
	pr_err("%s:%d: bad pgd %p(%016lx) seen at (%pS)\n",		\
	       __खाता__, __LINE__, &(e), pgd_val(e), __builtin_वापस_address(0))

#पूर्ण_अगर /* !(__ASSEMBLY__) */

/* PTE bits which are the same in SUN4U and SUN4V क्रमmat.  */
#घोषणा _PAGE_VALID	  _AC(0x8000000000000000,UL) /* Valid TTE            */
#घोषणा _PAGE_R	  	  _AC(0x8000000000000000,UL) /* Keep ref bit uptodate*/
#घोषणा _PAGE_SPECIAL     _AC(0x0200000000000000,UL) /* Special page         */
#घोषणा _PAGE_PMD_HUGE    _AC(0x0100000000000000,UL) /* Huge page            */
#घोषणा _PAGE_PUD_HUGE    _PAGE_PMD_HUGE

/* SUN4U pte bits... */
#घोषणा _PAGE_SZ4MB_4U	  _AC(0x6000000000000000,UL) /* 4MB Page             */
#घोषणा _PAGE_SZ512K_4U	  _AC(0x4000000000000000,UL) /* 512K Page            */
#घोषणा _PAGE_SZ64K_4U	  _AC(0x2000000000000000,UL) /* 64K Page             */
#घोषणा _PAGE_SZ8K_4U	  _AC(0x0000000000000000,UL) /* 8K Page              */
#घोषणा _PAGE_NFO_4U	  _AC(0x1000000000000000,UL) /* No Fault Only        */
#घोषणा _PAGE_IE_4U	  _AC(0x0800000000000000,UL) /* Invert Endianness    */
#घोषणा _PAGE_SOFT2_4U	  _AC(0x07FC000000000000,UL) /* Software bits, set 2 */
#घोषणा _PAGE_SPECIAL_4U  _AC(0x0200000000000000,UL) /* Special page         */
#घोषणा _PAGE_PMD_HUGE_4U _AC(0x0100000000000000,UL) /* Huge page            */
#घोषणा _PAGE_RES1_4U	  _AC(0x0002000000000000,UL) /* Reserved             */
#घोषणा _PAGE_SZ32MB_4U	  _AC(0x0001000000000000,UL) /* (Panther) 32MB page  */
#घोषणा _PAGE_SZ256MB_4U  _AC(0x2001000000000000,UL) /* (Panther) 256MB page */
#घोषणा _PAGE_SZALL_4U	  _AC(0x6001000000000000,UL) /* All pgsz bits        */
#घोषणा _PAGE_SN_4U	  _AC(0x0000800000000000,UL) /* (Cheetah) Snoop      */
#घोषणा _PAGE_RES2_4U	  _AC(0x0000780000000000,UL) /* Reserved             */
#घोषणा _PAGE_PADDR_4U	  _AC(0x000007FFFFFFE000,UL) /* (Cheetah) pa[42:13]  */
#घोषणा _PAGE_SOFT_4U	  _AC(0x0000000000001F80,UL) /* Software bits:       */
#घोषणा _PAGE_EXEC_4U	  _AC(0x0000000000001000,UL) /* Executable SW bit    */
#घोषणा _PAGE_MODIFIED_4U _AC(0x0000000000000800,UL) /* Modअगरied (dirty)     */
#घोषणा _PAGE_ACCESSED_4U _AC(0x0000000000000400,UL) /* Accessed (ref'd)     */
#घोषणा _PAGE_READ_4U	  _AC(0x0000000000000200,UL) /* Readable SW Bit      */
#घोषणा _PAGE_WRITE_4U	  _AC(0x0000000000000100,UL) /* Writable SW Bit      */
#घोषणा _PAGE_PRESENT_4U  _AC(0x0000000000000080,UL) /* Present              */
#घोषणा _PAGE_L_4U	  _AC(0x0000000000000040,UL) /* Locked TTE           */
#घोषणा _PAGE_CP_4U	  _AC(0x0000000000000020,UL) /* Cacheable in P-Cache */
#घोषणा _PAGE_CV_4U	  _AC(0x0000000000000010,UL) /* Cacheable in V-Cache */
#घोषणा _PAGE_E_4U	  _AC(0x0000000000000008,UL) /* side-Effect          */
#घोषणा _PAGE_P_4U	  _AC(0x0000000000000004,UL) /* Privileged Page      */
#घोषणा _PAGE_W_4U	  _AC(0x0000000000000002,UL) /* Writable             */

/* SUN4V pte bits... */
#घोषणा _PAGE_NFO_4V	  _AC(0x4000000000000000,UL) /* No Fault Only        */
#घोषणा _PAGE_SOFT2_4V	  _AC(0x3F00000000000000,UL) /* Software bits, set 2 */
#घोषणा _PAGE_MODIFIED_4V _AC(0x2000000000000000,UL) /* Modअगरied (dirty)     */
#घोषणा _PAGE_ACCESSED_4V _AC(0x1000000000000000,UL) /* Accessed (ref'd)     */
#घोषणा _PAGE_READ_4V	  _AC(0x0800000000000000,UL) /* Readable SW Bit      */
#घोषणा _PAGE_WRITE_4V	  _AC(0x0400000000000000,UL) /* Writable SW Bit      */
#घोषणा _PAGE_SPECIAL_4V  _AC(0x0200000000000000,UL) /* Special page         */
#घोषणा _PAGE_PMD_HUGE_4V _AC(0x0100000000000000,UL) /* Huge page            */
#घोषणा _PAGE_PADDR_4V	  _AC(0x00FFFFFFFFFFE000,UL) /* paddr[55:13]         */
#घोषणा _PAGE_IE_4V	  _AC(0x0000000000001000,UL) /* Invert Endianness    */
#घोषणा _PAGE_E_4V	  _AC(0x0000000000000800,UL) /* side-Effect          */
#घोषणा _PAGE_CP_4V	  _AC(0x0000000000000400,UL) /* Cacheable in P-Cache */
#घोषणा _PAGE_CV_4V	  _AC(0x0000000000000200,UL) /* Cacheable in V-Cache */
/* Bit 9 is used to enable MCD corruption detection instead on M7 */
#घोषणा _PAGE_MCD_4V      _AC(0x0000000000000200,UL) /* Memory Corruption    */
#घोषणा _PAGE_P_4V	  _AC(0x0000000000000100,UL) /* Privileged Page      */
#घोषणा _PAGE_EXEC_4V	  _AC(0x0000000000000080,UL) /* Executable Page      */
#घोषणा _PAGE_W_4V	  _AC(0x0000000000000040,UL) /* Writable             */
#घोषणा _PAGE_SOFT_4V	  _AC(0x0000000000000030,UL) /* Software bits        */
#घोषणा _PAGE_PRESENT_4V  _AC(0x0000000000000010,UL) /* Present              */
#घोषणा _PAGE_RESV_4V	  _AC(0x0000000000000008,UL) /* Reserved             */
#घोषणा _PAGE_SZ16GB_4V	  _AC(0x0000000000000007,UL) /* 16GB Page            */
#घोषणा _PAGE_SZ2GB_4V	  _AC(0x0000000000000006,UL) /* 2GB Page             */
#घोषणा _PAGE_SZ256MB_4V  _AC(0x0000000000000005,UL) /* 256MB Page           */
#घोषणा _PAGE_SZ32MB_4V	  _AC(0x0000000000000004,UL) /* 32MB Page            */
#घोषणा _PAGE_SZ4MB_4V	  _AC(0x0000000000000003,UL) /* 4MB Page             */
#घोषणा _PAGE_SZ512K_4V	  _AC(0x0000000000000002,UL) /* 512K Page            */
#घोषणा _PAGE_SZ64K_4V	  _AC(0x0000000000000001,UL) /* 64K Page             */
#घोषणा _PAGE_SZ8K_4V	  _AC(0x0000000000000000,UL) /* 8K Page              */
#घोषणा _PAGE_SZALL_4V	  _AC(0x0000000000000007,UL) /* All pgsz bits        */

#घोषणा _PAGE_SZBITS_4U	_PAGE_SZ8K_4U
#घोषणा _PAGE_SZBITS_4V	_PAGE_SZ8K_4V

#अगर REAL_HPAGE_SHIFT != 22
#त्रुटि REAL_HPAGE_SHIFT and _PAGE_SZHUGE_foo must match up
#पूर्ण_अगर

#घोषणा _PAGE_SZHUGE_4U	_PAGE_SZ4MB_4U
#घोषणा _PAGE_SZHUGE_4V	_PAGE_SZ4MB_4V

/* These are actually filled in at boot समय by sun4अणुu,vपूर्ण_pgprot_init() */
#घोषणा __P000	__pgprot(0)
#घोषणा __P001	__pgprot(0)
#घोषणा __P010	__pgprot(0)
#घोषणा __P011	__pgprot(0)
#घोषणा __P100	__pgprot(0)
#घोषणा __P101	__pgprot(0)
#घोषणा __P110	__pgprot(0)
#घोषणा __P111	__pgprot(0)

#घोषणा __S000	__pgprot(0)
#घोषणा __S001	__pgprot(0)
#घोषणा __S010	__pgprot(0)
#घोषणा __S011	__pgprot(0)
#घोषणा __S100	__pgprot(0)
#घोषणा __S101	__pgprot(0)
#घोषणा __S110	__pgprot(0)
#घोषणा __S111	__pgprot(0)

#अगर_अघोषित __ASSEMBLY__

pte_t mk_pte_io(अचिन्हित दीर्घ, pgprot_t, पूर्णांक, अचिन्हित दीर्घ);

अचिन्हित दीर्घ pte_sz_bits(अचिन्हित दीर्घ size);

बाह्य pgprot_t PAGE_KERNEL;
बाह्य pgprot_t PAGE_KERNEL_LOCKED;
बाह्य pgprot_t PAGE_COPY;
बाह्य pgprot_t PAGE_SHARED;

/* XXX This ugliness is क्रम the atyfb driver's sparc mmap() support. XXX */
बाह्य अचिन्हित दीर्घ _PAGE_IE;
बाह्य अचिन्हित दीर्घ _PAGE_E;
बाह्य अचिन्हित दीर्घ _PAGE_CACHE;

बाह्य अचिन्हित दीर्घ pg_iobits;
बाह्य अचिन्हित दीर्घ _PAGE_ALL_SZ_BITS;

बाह्य काष्ठा page *mem_map_zero;
#घोषणा ZERO_PAGE(vaddr)	(mem_map_zero)

/* PFNs are real physical page numbers.  However, mem_map only begins to record
 * per-page inक्रमmation starting at pfn_base.  This is to handle प्रणालीs where
 * the first physical page in the machine is at some huge physical address,
 * such as 4GB.   This is common on a partitioned E10000, क्रम example.
 */
अटल अंतरभूत pte_t pfn_pte(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	अचिन्हित दीर्घ paddr = pfn << PAGE_SHIFT;

	BUILD_BUG_ON(_PAGE_SZBITS_4U != 0UL || _PAGE_SZBITS_4V != 0UL);
	वापस __pte(paddr | pgprot_val(prot));
पूर्ण
#घोषणा mk_pte(page, pgprot)	pfn_pte(page_to_pfn(page), (pgprot))

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल अंतरभूत pmd_t pfn_pmd(अचिन्हित दीर्घ page_nr, pgprot_t pgprot)
अणु
	pte_t pte = pfn_pte(page_nr, pgprot);

	वापस __pmd(pte_val(pte));
पूर्ण
#घोषणा mk_pmd(page, pgprot)	pfn_pmd(page_to_pfn(page), (pgprot))
#पूर्ण_अगर

/* This one can be करोne with two shअगरts.  */
अटल अंतरभूत अचिन्हित दीर्घ pte_pfn(pte_t pte)
अणु
	अचिन्हित दीर्घ ret;

	__यंत्र__ __अस्थिर__(
	"\n661:	sllx		%1, %2, %0\n"
	"	srlx		%0, %3, %0\n"
	"	.section	.sun4v_2insn_patch, \"ax\"\n"
	"	.word		661b\n"
	"	sllx		%1, %4, %0\n"
	"	srlx		%0, %5, %0\n"
	"	.previous\n"
	: "=r" (ret)
	: "r" (pte_val(pte)),
	  "i" (21), "i" (21 + PAGE_SHIFT),
	  "i" (8), "i" (8 + PAGE_SHIFT));

	वापस ret;
पूर्ण
#घोषणा pte_page(x) pfn_to_page(pte_pfn(x))

अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t prot)
अणु
	अचिन्हित दीर्घ mask, पंचांगp;

	/* SUN4U: 0x630107ffffffec38 (negated == 0x9cfef800000013c7)
	 * SUN4V: 0x33ffffffffffee07 (negated == 0xcc000000000011f8)
	 *
	 * Even अगर we use negation tricks the result is still a 6
	 * inकाष्ठाion sequence, so करोn't try to play fancy and just
	 * करो the most straightक्रमward implementation.
	 *
	 * Note: We encode this पूर्णांकo 3 sun4v 2-insn patch sequences.
	 */

	BUILD_BUG_ON(_PAGE_SZBITS_4U != 0UL || _PAGE_SZBITS_4V != 0UL);
	__यंत्र__ __अस्थिर__(
	"\n661:	sethi		%%uhi(%2), %1\n"
	"	sethi		%%hi(%2), %0\n"
	"\n662:	or		%1, %%ulo(%2), %1\n"
	"	or		%0, %%lo(%2), %0\n"
	"\n663:	sllx		%1, 32, %1\n"
	"	or		%0, %1, %0\n"
	"	.section	.sun4v_2insn_patch, \"ax\"\n"
	"	.word		661b\n"
	"	sethi		%%uhi(%3), %1\n"
	"	sethi		%%hi(%3), %0\n"
	"	.word		662b\n"
	"	or		%1, %%ulo(%3), %1\n"
	"	or		%0, %%lo(%3), %0\n"
	"	.word		663b\n"
	"	sllx		%1, 32, %1\n"
	"	or		%0, %1, %0\n"
	"	.previous\n"
	"	.section	.sun_m7_2insn_patch, \"ax\"\n"
	"	.word		661b\n"
	"	sethi		%%uhi(%4), %1\n"
	"	sethi		%%hi(%4), %0\n"
	"	.word		662b\n"
	"	or		%1, %%ulo(%4), %1\n"
	"	or		%0, %%lo(%4), %0\n"
	"	.word		663b\n"
	"	sllx		%1, 32, %1\n"
	"	or		%0, %1, %0\n"
	"	.previous\n"
	: "=r" (mask), "=r" (पंचांगp)
	: "i" (_PAGE_PADDR_4U | _PAGE_MODIFIED_4U | _PAGE_ACCESSED_4U |
	       _PAGE_CP_4U | _PAGE_CV_4U | _PAGE_E_4U |
	       _PAGE_SPECIAL | _PAGE_PMD_HUGE | _PAGE_SZALL_4U),
	  "i" (_PAGE_PADDR_4V | _PAGE_MODIFIED_4V | _PAGE_ACCESSED_4V |
	       _PAGE_CP_4V | _PAGE_CV_4V | _PAGE_E_4V |
	       _PAGE_SPECIAL | _PAGE_PMD_HUGE | _PAGE_SZALL_4V),
	  "i" (_PAGE_PADDR_4V | _PAGE_MODIFIED_4V | _PAGE_ACCESSED_4V |
	       _PAGE_CP_4V | _PAGE_E_4V |
	       _PAGE_SPECIAL | _PAGE_PMD_HUGE | _PAGE_SZALL_4V));

	वापस __pte((pte_val(pte) & mask) | (pgprot_val(prot) & ~mask));
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल अंतरभूत pmd_t pmd_modअगरy(pmd_t pmd, pgprot_t newprot)
अणु
	pte_t pte = __pte(pmd_val(pmd));

	pte = pte_modअगरy(pte, newprot);

	वापस __pmd(pte_val(pte));
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत pgprot_t pgprot_noncached(pgprot_t prot)
अणु
	अचिन्हित दीर्घ val = pgprot_val(prot);

	__यंत्र__ __अस्थिर__(
	"\n661:	andn		%0, %2, %0\n"
	"	or		%0, %3, %0\n"
	"	.section	.sun4v_2insn_patch, \"ax\"\n"
	"	.word		661b\n"
	"	andn		%0, %4, %0\n"
	"	or		%0, %5, %0\n"
	"	.previous\n"
	"	.section	.sun_m7_2insn_patch, \"ax\"\n"
	"	.word		661b\n"
	"	andn		%0, %6, %0\n"
	"	or		%0, %5, %0\n"
	"	.previous\n"
	: "=r" (val)
	: "0" (val), "i" (_PAGE_CP_4U | _PAGE_CV_4U), "i" (_PAGE_E_4U),
	             "i" (_PAGE_CP_4V | _PAGE_CV_4V), "i" (_PAGE_E_4V),
	             "i" (_PAGE_CP_4V));

	वापस __pgprot(val);
पूर्ण
/* Various pieces of code check क्रम platक्रमm support by अगरdef testing
 * on "pgprot_noncached".  That's broken and should be fixed, but क्रम
 * now...
 */
#घोषणा pgprot_noncached pgprot_noncached

#अगर defined(CONFIG_HUGETLB_PAGE) || defined(CONFIG_TRANSPARENT_HUGEPAGE)
बाह्य pte_t arch_make_huge_pte(pte_t entry, काष्ठा vm_area_काष्ठा *vma,
				काष्ठा page *page, पूर्णांक writable);
#घोषणा arch_make_huge_pte arch_make_huge_pte
अटल अंतरभूत अचिन्हित दीर्घ __pte_शेष_huge_mask(व्योम)
अणु
	अचिन्हित दीर्घ mask;

	__यंत्र__ __अस्थिर__(
	"\n661:	sethi		%%uhi(%1), %0\n"
	"	sllx		%0, 32, %0\n"
	"	.section	.sun4v_2insn_patch, \"ax\"\n"
	"	.word		661b\n"
	"	mov		%2, %0\n"
	"	nop\n"
	"	.previous\n"
	: "=r" (mask)
	: "i" (_PAGE_SZHUGE_4U), "i" (_PAGE_SZHUGE_4V));

	वापस mask;
पूर्ण

अटल अंतरभूत pte_t pte_mkhuge(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | __pte_शेष_huge_mask());
पूर्ण

अटल अंतरभूत bool is_शेष_hugetlb_pte(pte_t pte)
अणु
	अचिन्हित दीर्घ mask = __pte_शेष_huge_mask();

	वापस (pte_val(pte) & mask) == mask;
पूर्ण

अटल अंतरभूत bool is_hugetlb_pmd(pmd_t pmd)
अणु
	वापस !!(pmd_val(pmd) & _PAGE_PMD_HUGE);
पूर्ण

अटल अंतरभूत bool is_hugetlb_pud(pud_t pud)
अणु
	वापस !!(pud_val(pud) & _PAGE_PUD_HUGE);
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल अंतरभूत pmd_t pmd_mkhuge(pmd_t pmd)
अणु
	pte_t pte = __pte(pmd_val(pmd));

	pte = pte_mkhuge(pte);
	pte_val(pte) |= _PAGE_PMD_HUGE;

	वापस __pmd(pte_val(pte));
पूर्ण
#पूर्ण_अगर
#अन्यथा
अटल अंतरभूत bool is_hugetlb_pte(pte_t pte)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)
अणु
	अचिन्हित दीर्घ val = pte_val(pte), पंचांगp;

	__यंत्र__ __अस्थिर__(
	"\n661:	or		%0, %3, %0\n"
	"	nop\n"
	"\n662:	nop\n"
	"	nop\n"
	"	.section	.sun4v_2insn_patch, \"ax\"\n"
	"	.word		661b\n"
	"	sethi		%%uhi(%4), %1\n"
	"	sllx		%1, 32, %1\n"
	"	.word		662b\n"
	"	or		%1, %%lo(%4), %1\n"
	"	or		%0, %1, %0\n"
	"	.previous\n"
	: "=r" (val), "=r" (पंचांगp)
	: "0" (val), "i" (_PAGE_MODIFIED_4U | _PAGE_W_4U),
	  "i" (_PAGE_MODIFIED_4V | _PAGE_W_4V));

	वापस __pte(val);
पूर्ण

अटल अंतरभूत pte_t pte_mkclean(pte_t pte)
अणु
	अचिन्हित दीर्घ val = pte_val(pte), पंचांगp;

	__यंत्र__ __अस्थिर__(
	"\n661:	andn		%0, %3, %0\n"
	"	nop\n"
	"\n662:	nop\n"
	"	nop\n"
	"	.section	.sun4v_2insn_patch, \"ax\"\n"
	"	.word		661b\n"
	"	sethi		%%uhi(%4), %1\n"
	"	sllx		%1, 32, %1\n"
	"	.word		662b\n"
	"	or		%1, %%lo(%4), %1\n"
	"	andn		%0, %1, %0\n"
	"	.previous\n"
	: "=r" (val), "=r" (पंचांगp)
	: "0" (val), "i" (_PAGE_MODIFIED_4U | _PAGE_W_4U),
	  "i" (_PAGE_MODIFIED_4V | _PAGE_W_4V));

	वापस __pte(val);
पूर्ण

अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	अचिन्हित दीर्घ val = pte_val(pte), mask;

	__यंत्र__ __अस्थिर__(
	"\n661:	mov		%1, %0\n"
	"	nop\n"
	"	.section	.sun4v_2insn_patch, \"ax\"\n"
	"	.word		661b\n"
	"	sethi		%%uhi(%2), %0\n"
	"	sllx		%0, 32, %0\n"
	"	.previous\n"
	: "=r" (mask)
	: "i" (_PAGE_WRITE_4U), "i" (_PAGE_WRITE_4V));

	वापस __pte(val | mask);
पूर्ण

अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	अचिन्हित दीर्घ val = pte_val(pte), पंचांगp;

	__यंत्र__ __अस्थिर__(
	"\n661:	andn		%0, %3, %0\n"
	"	nop\n"
	"\n662:	nop\n"
	"	nop\n"
	"	.section	.sun4v_2insn_patch, \"ax\"\n"
	"	.word		661b\n"
	"	sethi		%%uhi(%4), %1\n"
	"	sllx		%1, 32, %1\n"
	"	.word		662b\n"
	"	or		%1, %%lo(%4), %1\n"
	"	andn		%0, %1, %0\n"
	"	.previous\n"
	: "=r" (val), "=r" (पंचांगp)
	: "0" (val), "i" (_PAGE_WRITE_4U | _PAGE_W_4U),
	  "i" (_PAGE_WRITE_4V | _PAGE_W_4V));

	वापस __pte(val);
पूर्ण

अटल अंतरभूत pte_t pte_mkold(pte_t pte)
अणु
	अचिन्हित दीर्घ mask;

	__यंत्र__ __अस्थिर__(
	"\n661:	mov		%1, %0\n"
	"	nop\n"
	"	.section	.sun4v_2insn_patch, \"ax\"\n"
	"	.word		661b\n"
	"	sethi		%%uhi(%2), %0\n"
	"	sllx		%0, 32, %0\n"
	"	.previous\n"
	: "=r" (mask)
	: "i" (_PAGE_ACCESSED_4U), "i" (_PAGE_ACCESSED_4V));

	mask |= _PAGE_R;

	वापस __pte(pte_val(pte) & ~mask);
पूर्ण

अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)
अणु
	अचिन्हित दीर्घ mask;

	__यंत्र__ __अस्थिर__(
	"\n661:	mov		%1, %0\n"
	"	nop\n"
	"	.section	.sun4v_2insn_patch, \"ax\"\n"
	"	.word		661b\n"
	"	sethi		%%uhi(%2), %0\n"
	"	sllx		%0, 32, %0\n"
	"	.previous\n"
	: "=r" (mask)
	: "i" (_PAGE_ACCESSED_4U), "i" (_PAGE_ACCESSED_4V));

	mask |= _PAGE_R;

	वापस __pte(pte_val(pte) | mask);
पूर्ण

अटल अंतरभूत pte_t pte_mkspecial(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_SPECIAL;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mkmcd(pte_t pte)
अणु
	pte_val(pte) |= _PAGE_MCD_4V;
	वापस pte;
पूर्ण

अटल अंतरभूत pte_t pte_mknoपंचांगcd(pte_t pte)
अणु
	pte_val(pte) &= ~_PAGE_MCD_4V;
	वापस pte;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pte_young(pte_t pte)
अणु
	अचिन्हित दीर्घ mask;

	__यंत्र__ __अस्थिर__(
	"\n661:	mov		%1, %0\n"
	"	nop\n"
	"	.section	.sun4v_2insn_patch, \"ax\"\n"
	"	.word		661b\n"
	"	sethi		%%uhi(%2), %0\n"
	"	sllx		%0, 32, %0\n"
	"	.previous\n"
	: "=r" (mask)
	: "i" (_PAGE_ACCESSED_4U), "i" (_PAGE_ACCESSED_4V));

	वापस (pte_val(pte) & mask);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pte_dirty(pte_t pte)
अणु
	अचिन्हित दीर्घ mask;

	__यंत्र__ __अस्थिर__(
	"\n661:	mov		%1, %0\n"
	"	nop\n"
	"	.section	.sun4v_2insn_patch, \"ax\"\n"
	"	.word		661b\n"
	"	sethi		%%uhi(%2), %0\n"
	"	sllx		%0, 32, %0\n"
	"	.previous\n"
	: "=r" (mask)
	: "i" (_PAGE_MODIFIED_4U), "i" (_PAGE_MODIFIED_4V));

	वापस (pte_val(pte) & mask);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pte_ग_लिखो(pte_t pte)
अणु
	अचिन्हित दीर्घ mask;

	__यंत्र__ __अस्थिर__(
	"\n661:	mov		%1, %0\n"
	"	nop\n"
	"	.section	.sun4v_2insn_patch, \"ax\"\n"
	"	.word		661b\n"
	"	sethi		%%uhi(%2), %0\n"
	"	sllx		%0, 32, %0\n"
	"	.previous\n"
	: "=r" (mask)
	: "i" (_PAGE_WRITE_4U), "i" (_PAGE_WRITE_4V));

	वापस (pte_val(pte) & mask);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pte_exec(pte_t pte)
अणु
	अचिन्हित दीर्घ mask;

	__यंत्र__ __अस्थिर__(
	"\n661:	sethi		%%hi(%1), %0\n"
	"	.section	.sun4v_1insn_patch, \"ax\"\n"
	"	.word		661b\n"
	"	mov		%2, %0\n"
	"	.previous\n"
	: "=r" (mask)
	: "i" (_PAGE_EXEC_4U), "i" (_PAGE_EXEC_4V));

	वापस (pte_val(pte) & mask);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pte_present(pte_t pte)
अणु
	अचिन्हित दीर्घ val = pte_val(pte);

	__यंत्र__ __अस्थिर__(
	"\n661:	and		%0, %2, %0\n"
	"	.section	.sun4v_1insn_patch, \"ax\"\n"
	"	.word		661b\n"
	"	and		%0, %3, %0\n"
	"	.previous\n"
	: "=r" (val)
	: "0" (val), "i" (_PAGE_PRESENT_4U), "i" (_PAGE_PRESENT_4V));

	वापस val;
पूर्ण

#घोषणा pte_accessible pte_accessible
अटल अंतरभूत अचिन्हित दीर्घ pte_accessible(काष्ठा mm_काष्ठा *mm, pte_t a)
अणु
	वापस pte_val(a) & _PAGE_VALID;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pte_special(pte_t pte)
अणु
	वापस pte_val(pte) & _PAGE_SPECIAL;
पूर्ण

#घोषणा pmd_leaf	pmd_large
अटल अंतरभूत अचिन्हित दीर्घ pmd_large(pmd_t pmd)
अणु
	pte_t pte = __pte(pmd_val(pmd));

	वापस pte_val(pte) & _PAGE_PMD_HUGE;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pmd_pfn(pmd_t pmd)
अणु
	pte_t pte = __pte(pmd_val(pmd));

	वापस pte_pfn(pte);
पूर्ण

#घोषणा pmd_ग_लिखो pmd_ग_लिखो
अटल अंतरभूत अचिन्हित दीर्घ pmd_ग_लिखो(pmd_t pmd)
अणु
	pte_t pte = __pte(pmd_val(pmd));

	वापस pte_ग_लिखो(pte);
पूर्ण

#घोषणा pud_ग_लिखो(pud)	pte_ग_लिखो(__pte(pud_val(pud)))

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल अंतरभूत अचिन्हित दीर्घ pmd_dirty(pmd_t pmd)
अणु
	pte_t pte = __pte(pmd_val(pmd));

	वापस pte_dirty(pte);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pmd_young(pmd_t pmd)
अणु
	pte_t pte = __pte(pmd_val(pmd));

	वापस pte_young(pte);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pmd_trans_huge(pmd_t pmd)
अणु
	pte_t pte = __pte(pmd_val(pmd));

	वापस pte_val(pte) & _PAGE_PMD_HUGE;
पूर्ण

अटल अंतरभूत pmd_t pmd_mkold(pmd_t pmd)
अणु
	pte_t pte = __pte(pmd_val(pmd));

	pte = pte_mkold(pte);

	वापस __pmd(pte_val(pte));
पूर्ण

अटल अंतरभूत pmd_t pmd_wrprotect(pmd_t pmd)
अणु
	pte_t pte = __pte(pmd_val(pmd));

	pte = pte_wrprotect(pte);

	वापस __pmd(pte_val(pte));
पूर्ण

अटल अंतरभूत pmd_t pmd_सूची_गढ़ोty(pmd_t pmd)
अणु
	pte_t pte = __pte(pmd_val(pmd));

	pte = pte_सूची_गढ़ोty(pte);

	वापस __pmd(pte_val(pte));
पूर्ण

अटल अंतरभूत pmd_t pmd_mkclean(pmd_t pmd)
अणु
	pte_t pte = __pte(pmd_val(pmd));

	pte = pte_mkclean(pte);

	वापस __pmd(pte_val(pte));
पूर्ण

अटल अंतरभूत pmd_t pmd_mkyoung(pmd_t pmd)
अणु
	pte_t pte = __pte(pmd_val(pmd));

	pte = pte_mkyoung(pte);

	वापस __pmd(pte_val(pte));
पूर्ण

अटल अंतरभूत pmd_t pmd_mkग_लिखो(pmd_t pmd)
अणु
	pte_t pte = __pte(pmd_val(pmd));

	pte = pte_mkग_लिखो(pte);

	वापस __pmd(pte_val(pte));
पूर्ण

अटल अंतरभूत pgprot_t pmd_pgprot(pmd_t entry)
अणु
	अचिन्हित दीर्घ val = pmd_val(entry);

	वापस __pgprot(val);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक pmd_present(pmd_t pmd)
अणु
	वापस pmd_val(pmd) != 0UL;
पूर्ण

#घोषणा pmd_none(pmd)			(!pmd_val(pmd))

/* pmd_bad() is only called on non-trans-huge PMDs.  Our encoding is
 * very simple, it's just the physical address.  PTE tables are of
 * size PAGE_SIZE so make sure the sub-PAGE_SIZE bits are clear and
 * the top bits outside of the range of any physical address size we
 * support are clear as well.  We also validate the physical itself.
 */
#घोषणा pmd_bad(pmd)			(pmd_val(pmd) & ~PAGE_MASK)

#घोषणा pud_none(pud)			(!pud_val(pud))

#घोषणा pud_bad(pud)			(pud_val(pud) & ~PAGE_MASK)

#घोषणा p4d_none(p4d)			(!p4d_val(p4d))

#घोषणा p4d_bad(p4d)			(p4d_val(p4d) & ~PAGE_MASK)

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
व्योम set_pmd_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
		pmd_t *pmdp, pmd_t pmd);
#अन्यथा
अटल अंतरभूत व्योम set_pmd_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      pmd_t *pmdp, pmd_t pmd)
अणु
	*pmdp = pmd;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम pmd_set(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp, pte_t *ptep)
अणु
	अचिन्हित दीर्घ val = __pa((अचिन्हित दीर्घ) (ptep));

	pmd_val(*pmdp) = val;
पूर्ण

#घोषणा pud_set(pudp, pmdp)	\
	(pud_val(*(pudp)) = (__pa((अचिन्हित दीर्घ) (pmdp))))
अटल अंतरभूत अचिन्हित दीर्घ pmd_page_vaddr(pmd_t pmd)
अणु
	pte_t pte = __pte(pmd_val(pmd));
	अचिन्हित दीर्घ pfn;

	pfn = pte_pfn(pte);

	वापस ((अचिन्हित दीर्घ) __va(pfn << PAGE_SHIFT));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pud_page_vaddr(pud_t pud)
अणु
	pte_t pte = __pte(pud_val(pud));
	अचिन्हित दीर्घ pfn;

	pfn = pte_pfn(pte);

	वापस ((अचिन्हित दीर्घ) __va(pfn << PAGE_SHIFT));
पूर्ण

#घोषणा pmd_page(pmd) 			virt_to_page((व्योम *)pmd_page_vaddr(pmd))
#घोषणा pud_page(pud) 			virt_to_page((व्योम *)pud_page_vaddr(pud))
#घोषणा pmd_clear(pmdp)			(pmd_val(*(pmdp)) = 0UL)
#घोषणा pud_present(pud)		(pud_val(pud) != 0U)
#घोषणा pud_clear(pudp)			(pud_val(*(pudp)) = 0UL)
#घोषणा p4d_page_vaddr(p4d)		\
	((अचिन्हित दीर्घ) __va(p4d_val(p4d)))
#घोषणा p4d_present(p4d)		(p4d_val(p4d) != 0U)
#घोषणा p4d_clear(p4dp)			(p4d_val(*(p4dp)) = 0UL)

/* only used by the stubbed out hugetlb gup code, should never be called */
#घोषणा p4d_page(p4d)			शून्य

#घोषणा pud_leaf	pud_large
अटल अंतरभूत अचिन्हित दीर्घ pud_large(pud_t pud)
अणु
	pte_t pte = __pte(pud_val(pud));

	वापस pte_val(pte) & _PAGE_PMD_HUGE;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pud_pfn(pud_t pud)
अणु
	pte_t pte = __pte(pud_val(pud));

	वापस pte_pfn(pte);
पूर्ण

/* Same in both SUN4V and SUN4U.  */
#घोषणा pte_none(pte) 			(!pte_val(pte))

#घोषणा p4d_set(p4dp, pudp)	\
	(p4d_val(*(p4dp)) = (__pa((अचिन्हित दीर्घ) (pudp))))

/* We cannot include <linux/mm_types.h> at this poपूर्णांक yet: */
बाह्य काष्ठा mm_काष्ठा init_mm;

/* Actual page table PTE updates.  */
व्योम tlb_batch_add(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr,
		   pte_t *ptep, pte_t orig, पूर्णांक fullmm,
		   अचिन्हित पूर्णांक hugepage_shअगरt);

अटल व्योम maybe_tlb_batch_add(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr,
				pte_t *ptep, pte_t orig, पूर्णांक fullmm,
				अचिन्हित पूर्णांक hugepage_shअगरt)
अणु
	/* It is more efficient to let flush_tlb_kernel_range()
	 * handle init_mm tlb flushes.
	 *
	 * SUN4V NOTE: _PAGE_VALID is the same value in both the SUN4U
	 *             and SUN4V pte layout, so this अंतरभूत test is fine.
	 */
	अगर (likely(mm != &init_mm) && pte_accessible(mm, orig))
		tlb_batch_add(mm, vaddr, ptep, orig, fullmm, hugepage_shअगरt);
पूर्ण

#घोषणा __HAVE_ARCH_PMDP_HUGE_GET_AND_CLEAR
अटल अंतरभूत pmd_t pmdp_huge_get_and_clear(काष्ठा mm_काष्ठा *mm,
					    अचिन्हित दीर्घ addr,
					    pmd_t *pmdp)
अणु
	pmd_t pmd = *pmdp;
	set_pmd_at(mm, addr, pmdp, __pmd(0UL));
	वापस pmd;
पूर्ण

अटल अंतरभूत व्योम __set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			     pte_t *ptep, pte_t pte, पूर्णांक fullmm)
अणु
	pte_t orig = *ptep;

	*ptep = pte;
	maybe_tlb_batch_add(mm, addr, ptep, orig, fullmm, PAGE_SHIFT);
पूर्ण

#घोषणा set_pte_at(mm,addr,ptep,pte)	\
	__set_pte_at((mm), (addr), (ptep), (pte), 0)

#घोषणा pte_clear(mm,addr,ptep)		\
	set_pte_at((mm), (addr), (ptep), __pte(0UL))

#घोषणा __HAVE_ARCH_PTE_CLEAR_NOT_PRESENT_FULL
#घोषणा pte_clear_not_present_full(mm,addr,ptep,fullmm)	\
	__set_pte_at((mm), (addr), (ptep), __pte(0UL), (fullmm))

#अगर_घोषित DCACHE_ALIASING_POSSIBLE
#घोषणा __HAVE_ARCH_MOVE_PTE
#घोषणा move_pte(pte, prot, old_addr, new_addr)				\
(अणु									\
	pte_t newpte = (pte);						\
	अगर (tlb_type != hypervisor && pte_present(pte)) अणु		\
		अचिन्हित दीर्घ this_pfn = pte_pfn(pte);			\
									\
		अगर (pfn_valid(this_pfn) &&				\
		    (((old_addr) ^ (new_addr)) & (1 << 13)))		\
			flush_dcache_page_all(current->mm,		\
					      pfn_to_page(this_pfn));	\
	पूर्ण								\
	newpte;								\
पूर्ण)
#पूर्ण_अगर

बाह्य pgd_t swapper_pg_dir[PTRS_PER_PGD];

व्योम paging_init(व्योम);
अचिन्हित दीर्घ find_ecache_flush_span(अचिन्हित दीर्घ size);

काष्ठा seq_file;
व्योम mmu_info(काष्ठा seq_file *);

काष्ठा vm_area_काष्ठा;
व्योम update_mmu_cache(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ, pte_t *);
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
व्योम update_mmu_cache_pmd(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
			  pmd_t *pmd);

#घोषणा __HAVE_ARCH_PMDP_INVALIDATE
बाह्य pmd_t pmdp_invalidate(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
			    pmd_t *pmdp);

#घोषणा __HAVE_ARCH_PGTABLE_DEPOSIT
व्योम pgtable_trans_huge_deposit(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp,
				pgtable_t pgtable);

#घोषणा __HAVE_ARCH_PGTABLE_WITHDRAW
pgtable_t pgtable_trans_huge_withdraw(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp);
#पूर्ण_अगर

/* Encode and de-code a swap entry */
#घोषणा __swp_type(entry)	(((entry).val >> PAGE_SHIFT) & 0xffUL)
#घोषणा __swp_offset(entry)	((entry).val >> (PAGE_SHIFT + 8UL))
#घोषणा __swp_entry(type, offset)	\
	( (swp_entry_t) \
	  अणु \
		(((दीर्घ)(type) << PAGE_SHIFT) | \
                 ((दीर्घ)(offset) << (PAGE_SHIFT + 8UL))) \
	  पूर्ण )
#घोषणा __pte_to_swp_entry(pte)		((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(x)		((pte_t) अणु (x).val पूर्ण)

पूर्णांक page_in_phys_avail(अचिन्हित दीर्घ paddr);

/*
 * For sparc32&64, the pfn in io_remap_pfn_range() carries <iospace> in
 * its high 4 bits.  These macros/functions put it there or get it from there.
 */
#घोषणा MK_IOSPACE_PFN(space, pfn)	(pfn | (space << (BITS_PER_LONG - 4)))
#घोषणा GET_IOSPACE(pfn)		(pfn >> (BITS_PER_LONG - 4))
#घोषणा GET_PFN(pfn)			(pfn & 0x0fffffffffffffffUL)

पूर्णांक remap_pfn_range(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ, अचिन्हित दीर्घ,
		    अचिन्हित दीर्घ, pgprot_t);

व्योम adi_restore_tags(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
		      अचिन्हित दीर्घ addr, pte_t pte);

पूर्णांक adi_save_tags(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
		  अचिन्हित दीर्घ addr, pte_t oldpte);

#घोषणा __HAVE_ARCH_DO_SWAP_PAGE
अटल अंतरभूत व्योम arch_करो_swap_page(काष्ठा mm_काष्ठा *mm,
				     काष्ठा vm_area_काष्ठा *vma,
				     अचिन्हित दीर्घ addr,
				     pte_t pte, pte_t oldpte)
अणु
	/* If this is a new page being mapped in, there can be no
	 * ADI tags stored away क्रम this page. Skip looking क्रम
	 * stored tags
	 */
	अगर (pte_none(oldpte))
		वापस;

	अगर (adi_state.enabled && (pte_val(pte) & _PAGE_MCD_4V))
		adi_restore_tags(mm, vma, addr, pte);
पूर्ण

#घोषणा __HAVE_ARCH_UNMAP_ONE
अटल अंतरभूत पूर्णांक arch_unmap_one(काष्ठा mm_काष्ठा *mm,
				 काष्ठा vm_area_काष्ठा *vma,
				 अचिन्हित दीर्घ addr, pte_t oldpte)
अणु
	अगर (adi_state.enabled && (pte_val(oldpte) & _PAGE_MCD_4V))
		वापस adi_save_tags(mm, vma, addr, oldpte);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक io_remap_pfn_range(काष्ठा vm_area_काष्ठा *vma,
				     अचिन्हित दीर्घ from, अचिन्हित दीर्घ pfn,
				     अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	अचिन्हित दीर्घ offset = GET_PFN(pfn) << PAGE_SHIFT;
	पूर्णांक space = GET_IOSPACE(pfn);
	अचिन्हित दीर्घ phys_base;

	phys_base = offset | (((अचिन्हित दीर्घ) space) << 32UL);

	वापस remap_pfn_range(vma, from, phys_base >> PAGE_SHIFT, size, prot);
पूर्ण
#घोषणा io_remap_pfn_range io_remap_pfn_range

अटल अंतरभूत अचिन्हित दीर्घ __untagged_addr(अचिन्हित दीर्घ start)
अणु
	अगर (adi_capable()) अणु
		दीर्घ addr = start;

		/* If userspace has passed a versioned address, kernel
		 * will not find it in the VMAs since it करोes not store
		 * the version tags in the list of VMAs. Storing version
		 * tags in list of VMAs is impractical since they can be
		 * changed any समय from userspace without dropping पूर्णांकo
		 * kernel. Any address search in VMAs will be करोne with
		 * non-versioned addresses. Ensure the ADI version bits
		 * are dropped here by sign extending the last bit beक्रमe
		 * ADI bits. IOMMU करोes not implement version tags.
		 */
		वापस (addr << (दीर्घ)adi_nbits()) >> (दीर्घ)adi_nbits();
	पूर्ण

	वापस start;
पूर्ण
#घोषणा untagged_addr(addr) \
	((__typeof__(addr))(__untagged_addr((अचिन्हित दीर्घ)(addr))))

अटल अंतरभूत bool pte_access_permitted(pte_t pte, bool ग_लिखो)
अणु
	u64 prot;

	अगर (tlb_type == hypervisor) अणु
		prot = _PAGE_PRESENT_4V | _PAGE_P_4V;
		अगर (ग_लिखो)
			prot |= _PAGE_WRITE_4V;
	पूर्ण अन्यथा अणु
		prot = _PAGE_PRESENT_4U | _PAGE_P_4U;
		अगर (ग_लिखो)
			prot |= _PAGE_WRITE_4U;
	पूर्ण

	वापस (pte_val(pte) & (prot | _PAGE_SPECIAL)) == prot;
पूर्ण
#घोषणा pte_access_permitted pte_access_permitted

#समावेश <यंत्र/tlbflush.h>

/* We provide our own get_unmapped_area to cope with VA holes and
 * SHM area cache aliasing क्रम userland.
 */
#घोषणा HAVE_ARCH_UNMAPPED_AREA
#घोषणा HAVE_ARCH_UNMAPPED_AREA_TOPDOWN

/* We provide a special get_unmapped_area क्रम framebuffer mmaps to try and use
 * the largest alignment possible such that larget PTEs can be used.
 */
अचिन्हित दीर्घ get_fb_unmapped_area(काष्ठा file *filp, अचिन्हित दीर्घ,
				   अचिन्हित दीर्घ, अचिन्हित दीर्घ,
				   अचिन्हित दीर्घ);
#घोषणा HAVE_ARCH_FB_UNMAPPED_AREA

व्योम sun4v_रेजिस्टर_fault_status(व्योम);
व्योम sun4v_ktsb_रेजिस्टर(व्योम);
व्योम __init cheetah_ecache_flush_init(व्योम);
व्योम sun4v_patch_tlb_handlers(व्योम);

बाह्य अचिन्हित दीर्घ cmdline_memory_size;

यंत्रlinkage व्योम करो_sparc64_fault(काष्ठा pt_regs *regs);

#अगर_घोषित CONFIG_HUGETLB_PAGE

#घोषणा pud_leaf_size pud_leaf_size
बाह्य अचिन्हित दीर्घ pud_leaf_size(pud_t pud);

#घोषणा pmd_leaf_size pmd_leaf_size
बाह्य अचिन्हित दीर्घ pmd_leaf_size(pmd_t pmd);

#घोषणा pte_leaf_size pte_leaf_size
बाह्य अचिन्हित दीर्घ pte_leaf_size(pte_t pte);

#पूर्ण_अगर /* CONFIG_HUGETLB_PAGE */

#पूर्ण_अगर /* !(__ASSEMBLY__) */

#पूर्ण_अगर /* !(_SPARC64_PGTABLE_H) */
