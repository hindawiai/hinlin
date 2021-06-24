<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC_PGTABLE_H
#घोषणा _SPARC_PGTABLE_H

/*  यंत्र/pgtable.h:  Defines and functions used to work
 *                        with Sparc page tables.
 *
 *  Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 *  Copyright (C) 1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 */

#समावेश <linux/स्थिर.h>

#घोषणा PMD_SHIFT		18
#घोषणा PMD_SIZE        	(1UL << PMD_SHIFT)
#घोषणा PMD_MASK        	(~(PMD_SIZE-1))
#घोषणा PMD_ALIGN(__addr) 	(((__addr) + ~PMD_MASK) & PMD_MASK)

#घोषणा PGसूची_SHIFT     	24
#घोषणा PGसूची_SIZE      	(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK      	(~(PGसूची_SIZE-1))
#घोषणा PGसूची_ALIGN(__addr) 	(((__addr) + ~PGसूची_MASK) & PGसूची_MASK)

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र-generic/pgtable-nopud.h>

#समावेश <linux/spinlock.h>
#समावेश <linux/mm_types.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/pgtsrmmu.h>
#समावेश <यंत्र/vaddrs.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/cpu_type.h>


काष्ठा vm_area_काष्ठा;
काष्ठा page;

व्योम load_mmu(व्योम);
अचिन्हित दीर्घ calc_highpages(व्योम);
अचिन्हित दीर्घ __init booपंचांगem_init(अचिन्हित दीर्घ *pages_avail);

#घोषणा pte_ERROR(e)   __builtin_trap()
#घोषणा pmd_ERROR(e)   __builtin_trap()
#घोषणा pgd_ERROR(e)   __builtin_trap()

#घोषणा PTRS_PER_PTE    	64
#घोषणा PTRS_PER_PMD    	64
#घोषणा PTRS_PER_PGD    	256
#घोषणा USER_PTRS_PER_PGD	PAGE_OFFSET / PGसूची_SIZE
#घोषणा FIRST_USER_ADDRESS	0UL
#घोषणा PTE_SIZE		(PTRS_PER_PTE*4)

#घोषणा PAGE_NONE	SRMMU_PAGE_NONE
#घोषणा PAGE_SHARED	SRMMU_PAGE_SHARED
#घोषणा PAGE_COPY	SRMMU_PAGE_COPY
#घोषणा PAGE_READONLY	SRMMU_PAGE_RDONLY
#घोषणा PAGE_KERNEL	SRMMU_PAGE_KERNEL

/* Top-level page directory - dummy used by init-mm.
 * srmmu.c will assign the real one (which is dynamically sized) */
#घोषणा swapper_pg_dir शून्य

व्योम paging_init(व्योम);

बाह्य अचिन्हित दीर्घ ptr_in_current_pgd;

/*         xwr */
#घोषणा __P000  PAGE_NONE
#घोषणा __P001  PAGE_READONLY
#घोषणा __P010  PAGE_COPY
#घोषणा __P011  PAGE_COPY
#घोषणा __P100  PAGE_READONLY
#घोषणा __P101  PAGE_READONLY
#घोषणा __P110  PAGE_COPY
#घोषणा __P111  PAGE_COPY

#घोषणा __S000	PAGE_NONE
#घोषणा __S001	PAGE_READONLY
#घोषणा __S010	PAGE_SHARED
#घोषणा __S011	PAGE_SHARED
#घोषणा __S100	PAGE_READONLY
#घोषणा __S101	PAGE_READONLY
#घोषणा __S110	PAGE_SHARED
#घोषणा __S111	PAGE_SHARED

/* First physical page can be anywhere, the following is needed so that
 * va-->pa and vice versa conversions work properly without perक्रमmance
 * hit क्रम all __pa()/__va() operations.
 */
बाह्य अचिन्हित दीर्घ phys_base;
बाह्य अचिन्हित दीर्घ pfn_base;

/*
 * ZERO_PAGE is a global shared page that is always zero: used
 * क्रम zero-mapped memory areas etc..
 */
बाह्य अचिन्हित दीर्घ empty_zero_page[PAGE_SIZE / माप(अचिन्हित दीर्घ)];

#घोषणा ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))

/*
 * In general all page table modअगरications should use the V8 atomic
 * swap inकाष्ठाion.  This insures the mmu and the cpu are in sync
 * with respect to ref/mod bits in the page tables.
 */
अटल अंतरभूत अचिन्हित दीर्घ srmmu_swap(अचिन्हित दीर्घ *addr, अचिन्हित दीर्घ value)
अणु
	__यंत्र__ __अस्थिर__("swap [%2], %0" :
			"=&r" (value) : "0" (value), "r" (addr) : "memory");
	वापस value;
पूर्ण

/* Certain architectures need to करो special things when pte's
 * within a page table are directly modअगरied.  Thus, the following
 * hook is made available.
 */

अटल अंतरभूत व्योम set_pte(pte_t *ptep, pte_t pteval)
अणु
	srmmu_swap((अचिन्हित दीर्घ *)ptep, pte_val(pteval));
पूर्ण

#घोषणा set_pte_at(mm,addr,ptep,pteval) set_pte(ptep,pteval)

अटल अंतरभूत पूर्णांक srmmu_device_memory(अचिन्हित दीर्घ x)
अणु
	वापस ((x & 0xF0000000) != 0);
पूर्ण

अटल अंतरभूत काष्ठा page *pmd_page(pmd_t pmd)
अणु
	अगर (srmmu_device_memory(pmd_val(pmd)))
		BUG();
	वापस pfn_to_page((pmd_val(pmd) & SRMMU_PTD_PMASK) >> (PAGE_SHIFT-4));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __pmd_page(pmd_t pmd)
अणु
	अचिन्हित दीर्घ v;

	अगर (srmmu_device_memory(pmd_val(pmd)))
		BUG();

	v = pmd_val(pmd) & SRMMU_PTD_PMASK;
	वापस (अचिन्हित दीर्घ)__nocache_va(v << 4);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pmd_page_vaddr(pmd_t pmd)
अणु
	अचिन्हित दीर्घ v = pmd_val(pmd) & SRMMU_PTD_PMASK;
	वापस (अचिन्हित दीर्घ)__nocache_va(v << 4);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pud_page_vaddr(pud_t pud)
अणु
	अगर (srmmu_device_memory(pud_val(pud))) अणु
		वापस ~0;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ v = pud_val(pud) & SRMMU_PTD_PMASK;
		वापस (अचिन्हित दीर्घ)__nocache_va(v << 4);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक pte_present(pte_t pte)
अणु
	वापस ((pte_val(pte) & SRMMU_ET_MASK) == SRMMU_ET_PTE);
पूर्ण

अटल अंतरभूत पूर्णांक pte_none(pte_t pte)
अणु
	वापस !pte_val(pte);
पूर्ण

अटल अंतरभूत व्योम __pte_clear(pte_t *ptep)
अणु
	set_pte(ptep, __pte(0));
पूर्ण

अटल अंतरभूत व्योम pte_clear(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr, pte_t *ptep)
अणु
	__pte_clear(ptep);
पूर्ण

अटल अंतरभूत पूर्णांक pmd_bad(pmd_t pmd)
अणु
	वापस (pmd_val(pmd) & SRMMU_ET_MASK) != SRMMU_ET_PTD;
पूर्ण

अटल अंतरभूत पूर्णांक pmd_present(pmd_t pmd)
अणु
	वापस ((pmd_val(pmd) & SRMMU_ET_MASK) == SRMMU_ET_PTD);
पूर्ण

अटल अंतरभूत पूर्णांक pmd_none(pmd_t pmd)
अणु
	वापस !pmd_val(pmd);
पूर्ण

अटल अंतरभूत व्योम pmd_clear(pmd_t *pmdp)
अणु
	set_pte((pte_t *)&pmd_val(*pmdp), __pte(0));
पूर्ण

अटल अंतरभूत पूर्णांक pud_none(pud_t pud)
अणु
	वापस !(pud_val(pud) & 0xFFFFFFF);
पूर्ण

अटल अंतरभूत पूर्णांक pud_bad(pud_t pud)
अणु
	वापस (pud_val(pud) & SRMMU_ET_MASK) != SRMMU_ET_PTD;
पूर्ण

अटल अंतरभूत पूर्णांक pud_present(pud_t pud)
अणु
	वापस ((pud_val(pud) & SRMMU_ET_MASK) == SRMMU_ET_PTD);
पूर्ण

अटल अंतरभूत व्योम pud_clear(pud_t *pudp)
अणु
	set_pte((pte_t *)pudp, __pte(0));
पूर्ण

/*
 * The following only work अगर pte_present() is true.
 * Undefined behaviour अगर not..
 */
अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte)
अणु
	वापस pte_val(pte) & SRMMU_WRITE;
पूर्ण

अटल अंतरभूत पूर्णांक pte_dirty(pte_t pte)
अणु
	वापस pte_val(pte) & SRMMU_सूचीTY;
पूर्ण

अटल अंतरभूत पूर्णांक pte_young(pte_t pte)
अणु
	वापस pte_val(pte) & SRMMU_REF;
पूर्ण

अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	वापस __pte(pte_val(pte) & ~SRMMU_WRITE);
पूर्ण

अटल अंतरभूत pte_t pte_mkclean(pte_t pte)
अणु
	वापस __pte(pte_val(pte) & ~SRMMU_सूचीTY);
पूर्ण

अटल अंतरभूत pte_t pte_mkold(pte_t pte)
अणु
	वापस __pte(pte_val(pte) & ~SRMMU_REF);
पूर्ण

अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | SRMMU_WRITE);
पूर्ण

अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | SRMMU_सूचीTY);
पूर्ण

अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)
अणु
	वापस __pte(pte_val(pte) | SRMMU_REF);
पूर्ण

#घोषणा pfn_pte(pfn, prot)		mk_pte(pfn_to_page(pfn), prot)

अटल अंतरभूत अचिन्हित दीर्घ pte_pfn(pte_t pte)
अणु
	अगर (srmmu_device_memory(pte_val(pte))) अणु
		/* Just वापस something that will cause
		 * pfn_valid() to वापस false.  This makes
		 * copy_one_pte() to just directly copy to
		 * PTE over.
		 */
		वापस ~0UL;
	पूर्ण
	वापस (pte_val(pte) & SRMMU_PTE_PMASK) >> (PAGE_SHIFT-4);
पूर्ण

#घोषणा pte_page(pte)	pfn_to_page(pte_pfn(pte))

/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 */
अटल अंतरभूत pte_t mk_pte(काष्ठा page *page, pgprot_t pgprot)
अणु
	वापस __pte((page_to_pfn(page) << (PAGE_SHIFT-4)) | pgprot_val(pgprot));
पूर्ण

अटल अंतरभूत pte_t mk_pte_phys(अचिन्हित दीर्घ page, pgprot_t pgprot)
अणु
	वापस __pte(((page) >> 4) | pgprot_val(pgprot));
पूर्ण

अटल अंतरभूत pte_t mk_pte_io(अचिन्हित दीर्घ page, pgprot_t pgprot, पूर्णांक space)
अणु
	वापस __pte(((page) >> 4) | (space << 28) | pgprot_val(pgprot));
पूर्ण

#घोषणा pgprot_noncached pgprot_noncached
अटल अंतरभूत pgprot_t pgprot_noncached(pgprot_t prot)
अणु
	pgprot_val(prot) &= ~pgprot_val(__pgprot(SRMMU_CACHE));
	वापस prot;
पूर्ण

अटल pte_t pte_modअगरy(pte_t pte, pgprot_t newprot) __attribute_स्थिर__;
अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	वापस __pte((pte_val(pte) & SRMMU_CHG_MASK) |
		pgprot_val(newprot));
पूर्ण

/* only used by the huge vmap code, should never be called */
#घोषणा pud_page(pud)			शून्य

काष्ठा seq_file;
व्योम mmu_info(काष्ठा seq_file *m);

/* Fault handler stuff... */
#घोषणा FAULT_CODE_PROT     0x1
#घोषणा FAULT_CODE_WRITE    0x2
#घोषणा FAULT_CODE_USER     0x4

#घोषणा update_mmu_cache(vma, address, ptep) करो अणु पूर्ण जबतक (0)

व्योम srmmu_mapiorange(अचिन्हित पूर्णांक bus, अचिन्हित दीर्घ xpa,
                      अचिन्हित दीर्घ xva, अचिन्हित पूर्णांक len);
व्योम srmmu_unmapiorange(अचिन्हित दीर्घ virt_addr, अचिन्हित पूर्णांक len);

/* Encode and de-code a swap entry */
अटल अंतरभूत अचिन्हित दीर्घ __swp_type(swp_entry_t entry)
अणु
	वापस (entry.val >> SRMMU_SWP_TYPE_SHIFT) & SRMMU_SWP_TYPE_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __swp_offset(swp_entry_t entry)
अणु
	वापस (entry.val >> SRMMU_SWP_OFF_SHIFT) & SRMMU_SWP_OFF_MASK;
पूर्ण

अटल अंतरभूत swp_entry_t __swp_entry(अचिन्हित दीर्घ type, अचिन्हित दीर्घ offset)
अणु
	वापस (swp_entry_t) अणु
		(type & SRMMU_SWP_TYPE_MASK) << SRMMU_SWP_TYPE_SHIFT
		| (offset & SRMMU_SWP_OFF_MASK) << SRMMU_SWP_OFF_SHIFT पूर्ण;
पूर्ण

#घोषणा __pte_to_swp_entry(pte)		((swp_entry_t) अणु pte_val(pte) पूर्ण)
#घोषणा __swp_entry_to_pte(x)		((pte_t) अणु (x).val पूर्ण)

अटल अंतरभूत अचिन्हित दीर्घ
__get_phys (अचिन्हित दीर्घ addr)
अणु
	चयन (sparc_cpu_model)अणु
	हाल sun4m:
	हाल sun4d:
		वापस ((srmmu_get_pte (addr) & 0xffffff00) << 4);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
__get_iospace (अचिन्हित दीर्घ addr)
अणु
	चयन (sparc_cpu_model)अणु
	हाल sun4m:
	हाल sun4d:
		वापस (srmmu_get_pte (addr) >> 28);
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

बाह्य अचिन्हित दीर्घ *sparc_valid_addr_biपंचांगap;

/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
#घोषणा kern_addr_valid(addr) \
	(test_bit(__pa((अचिन्हित दीर्घ)(addr))>>20, sparc_valid_addr_biपंचांगap))

/*
 * For sparc32&64, the pfn in io_remap_pfn_range() carries <iospace> in
 * its high 4 bits.  These macros/functions put it there or get it from there.
 */
#घोषणा MK_IOSPACE_PFN(space, pfn)	(pfn | (space << (BITS_PER_LONG - 4)))
#घोषणा GET_IOSPACE(pfn)		(pfn >> (BITS_PER_LONG - 4))
#घोषणा GET_PFN(pfn)			(pfn & 0x0fffffffUL)

पूर्णांक remap_pfn_range(काष्ठा vm_area_काष्ठा *, अचिन्हित दीर्घ, अचिन्हित दीर्घ,
		    अचिन्हित दीर्घ, pgprot_t);

अटल अंतरभूत पूर्णांक io_remap_pfn_range(काष्ठा vm_area_काष्ठा *vma,
				     अचिन्हित दीर्घ from, अचिन्हित दीर्घ pfn,
				     अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	अचिन्हित दीर्घ दीर्घ offset, space, phys_base;

	offset = ((अचिन्हित दीर्घ दीर्घ) GET_PFN(pfn)) << PAGE_SHIFT;
	space = GET_IOSPACE(pfn);
	phys_base = offset | (space << 32ULL);

	वापस remap_pfn_range(vma, from, phys_base >> PAGE_SHIFT, size, prot);
पूर्ण
#घोषणा io_remap_pfn_range io_remap_pfn_range

#घोषणा __HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
#घोषणा ptep_set_access_flags(__vma, __address, __ptep, __entry, __dirty) \
(अणु									  \
	पूर्णांक __changed = !pte_same(*(__ptep), __entry);			  \
	अगर (__changed) अणु						  \
		set_pte_at((__vma)->vm_mm, (__address), __ptep, __entry); \
		flush_tlb_page(__vma, __address);			  \
	पूर्ण								  \
	__changed;							  \
पूर्ण)

#पूर्ण_अगर /* !(__ASSEMBLY__) */

#घोषणा VMALLOC_START           _AC(0xfe600000,UL)
#घोषणा VMALLOC_END             _AC(0xffc00000,UL)

/* We provide our own get_unmapped_area to cope with VA holes क्रम userland */
#घोषणा HAVE_ARCH_UNMAPPED_AREA

#पूर्ण_अगर /* !(_SPARC_PGTABLE_H) */
