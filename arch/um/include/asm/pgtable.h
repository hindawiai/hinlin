<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Copyright 2003 PathScale, Inc.
 * Derived from include/यंत्र-i386/pgtable.h
 */

#अगर_अघोषित __UM_PGTABLE_H
#घोषणा __UM_PGTABLE_H

#समावेश <यंत्र/fixmap.h>

#घोषणा _PAGE_PRESENT	0x001
#घोषणा _PAGE_NEWPAGE	0x002
#घोषणा _PAGE_NEWPROT	0x004
#घोषणा _PAGE_RW	0x020
#घोषणा _PAGE_USER	0x040
#घोषणा _PAGE_ACCESSED	0x080
#घोषणा _PAGE_सूचीTY	0x100
/* If _PAGE_PRESENT is clear, we use these: */
#घोषणा _PAGE_PROTNONE	0x010	/* अगर the user mapped it with PROT_NONE;
				   pte_present gives true */

#अगर_घोषित CONFIG_3_LEVEL_PGTABLES
#समावेश <यंत्र/pgtable-3level.h>
#अन्यथा
#समावेश <यंत्र/pgtable-2level.h>
#पूर्ण_अगर

बाह्य pgd_t swapper_pg_dir[PTRS_PER_PGD];

/* zero page used क्रम uninitialized stuff */
बाह्य अचिन्हित दीर्घ *empty_zero_page;

/* Just any arbitrary offset to the start of the vदो_स्मृति VM area: the
 * current 8MB value just means that there will be a 8MB "hole" after the
 * physical memory until the kernel भव memory starts.  That means that
 * any out-of-bounds memory accesses will hopefully be caught.
 * The vदो_स्मृति() routines leaves a hole of 4kB between each vदो_स्मृतिed
 * area क्रम the same reason. ;)
 */

बाह्य अचिन्हित दीर्घ end_iomem;

#घोषणा VMALLOC_OFFSET	(__va_space)
#घोषणा VMALLOC_START ((end_iomem + VMALLOC_OFFSET) & ~(VMALLOC_OFFSET-1))
#घोषणा PKMAP_BASE ((FIXADDR_START - LAST_PKMAP * PAGE_SIZE) & PMD_MASK)
#घोषणा VMALLOC_END	(FIXADDR_START-2*PAGE_SIZE)
#घोषणा MODULES_VADDR	VMALLOC_START
#घोषणा MODULES_END	VMALLOC_END
#घोषणा MODULES_LEN	(MODULES_VADDR - MODULES_END)

#घोषणा _PAGE_TABLE	(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER | _PAGE_ACCESSED | _PAGE_सूचीTY)
#घोषणा _KERNPG_TABLE	(_PAGE_PRESENT | _PAGE_RW | _PAGE_ACCESSED | _PAGE_सूचीTY)
#घोषणा _PAGE_CHG_MASK	(PAGE_MASK | _PAGE_ACCESSED | _PAGE_सूचीTY)
#घोषणा __PAGE_KERNEL_EXEC                                              \
	 (_PAGE_PRESENT | _PAGE_RW | _PAGE_सूचीTY | _PAGE_ACCESSED)
#घोषणा PAGE_NONE	__pgprot(_PAGE_PROTNONE | _PAGE_ACCESSED)
#घोषणा PAGE_SHARED	__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER | _PAGE_ACCESSED)
#घोषणा PAGE_COPY	__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED)
#घोषणा PAGE_READONLY	__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED)
#घोषणा PAGE_KERNEL	__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_सूचीTY | _PAGE_ACCESSED)
#घोषणा PAGE_KERNEL_EXEC	__pgprot(__PAGE_KERNEL_EXEC)

/*
 * The i386 can't करो page protection क्रम execute, and considers that the same
 * are पढ़ो.
 * Also, ग_लिखो permissions imply पढ़ो permissions. This is the बंदst we can
 * get..
 */
#घोषणा __P000	PAGE_NONE
#घोषणा __P001	PAGE_READONLY
#घोषणा __P010	PAGE_COPY
#घोषणा __P011	PAGE_COPY
#घोषणा __P100	PAGE_READONLY
#घोषणा __P101	PAGE_READONLY
#घोषणा __P110	PAGE_COPY
#घोषणा __P111	PAGE_COPY

#घोषणा __S000	PAGE_NONE
#घोषणा __S001	PAGE_READONLY
#घोषणा __S010	PAGE_SHARED
#घोषणा __S011	PAGE_SHARED
#घोषणा __S100	PAGE_READONLY
#घोषणा __S101	PAGE_READONLY
#घोषणा __S110	PAGE_SHARED
#घोषणा __S111	PAGE_SHARED

/*
 * ZERO_PAGE is a global shared page that is always zero: used
 * क्रम zero-mapped memory areas etc..
 */
#घोषणा ZERO_PAGE(vaddr) virt_to_page(empty_zero_page)

#घोषणा pte_clear(mm,addr,xp) pte_set_val(*(xp), (phys_t) 0, __pgprot(_PAGE_NEWPAGE))

#घोषणा pmd_none(x)	(!((अचिन्हित दीर्घ)pmd_val(x) & ~_PAGE_NEWPAGE))
#घोषणा	pmd_bad(x)	((pmd_val(x) & (~PAGE_MASK & ~_PAGE_USER)) != _KERNPG_TABLE)

#घोषणा pmd_present(x)	(pmd_val(x) & _PAGE_PRESENT)
#घोषणा pmd_clear(xp)	करो अणु pmd_val(*(xp)) = _PAGE_NEWPAGE; पूर्ण जबतक (0)

#घोषणा pmd_newpage(x)  (pmd_val(x) & _PAGE_NEWPAGE)
#घोषणा pmd_mkuptodate(x) (pmd_val(x) &= ~_PAGE_NEWPAGE)

#घोषणा pud_newpage(x)  (pud_val(x) & _PAGE_NEWPAGE)
#घोषणा pud_mkuptodate(x) (pud_val(x) &= ~_PAGE_NEWPAGE)

#घोषणा p4d_newpage(x)  (p4d_val(x) & _PAGE_NEWPAGE)
#घोषणा p4d_mkuptodate(x) (p4d_val(x) &= ~_PAGE_NEWPAGE)

#घोषणा pmd_page(pmd) phys_to_page(pmd_val(pmd) & PAGE_MASK)

#घोषणा pte_page(x) pfn_to_page(pte_pfn(x))

#घोषणा pte_present(x)	pte_get_bits(x, (_PAGE_PRESENT | _PAGE_PROTNONE))

/*
 * =================================
 * Flags checking section.
 * =================================
 */

अटल अंतरभूत पूर्णांक pte_none(pte_t pte)
अणु
	वापस pte_is_zero(pte);
पूर्ण

/*
 * The following only work अगर pte_present() is true.
 * Undefined behaviour अगर not..
 */
अटल अंतरभूत पूर्णांक pte_पढ़ो(pte_t pte)
अणु
	वापस((pte_get_bits(pte, _PAGE_USER)) &&
	       !(pte_get_bits(pte, _PAGE_PROTNONE)));
पूर्ण

अटल अंतरभूत पूर्णांक pte_exec(pte_t pte)अणु
	वापस((pte_get_bits(pte, _PAGE_USER)) &&
	       !(pte_get_bits(pte, _PAGE_PROTNONE)));
पूर्ण

अटल अंतरभूत पूर्णांक pte_ग_लिखो(pte_t pte)
अणु
	वापस((pte_get_bits(pte, _PAGE_RW)) &&
	       !(pte_get_bits(pte, _PAGE_PROTNONE)));
पूर्ण

अटल अंतरभूत पूर्णांक pte_dirty(pte_t pte)
अणु
	वापस pte_get_bits(pte, _PAGE_सूचीTY);
पूर्ण

अटल अंतरभूत पूर्णांक pte_young(pte_t pte)
अणु
	वापस pte_get_bits(pte, _PAGE_ACCESSED);
पूर्ण

अटल अंतरभूत पूर्णांक pte_newpage(pte_t pte)
अणु
	वापस pte_get_bits(pte, _PAGE_NEWPAGE);
पूर्ण

अटल अंतरभूत पूर्णांक pte_newprot(pte_t pte)
अणु
	वापस(pte_present(pte) && (pte_get_bits(pte, _PAGE_NEWPROT)));
पूर्ण

/*
 * =================================
 * Flags setting section.
 * =================================
 */

अटल अंतरभूत pte_t pte_mknewprot(pte_t pte)
अणु
	pte_set_bits(pte, _PAGE_NEWPROT);
	वापस(pte);
पूर्ण

अटल अंतरभूत pte_t pte_mkclean(pte_t pte)
अणु
	pte_clear_bits(pte, _PAGE_सूचीTY);
	वापस(pte);
पूर्ण

अटल अंतरभूत pte_t pte_mkold(pte_t pte)
अणु
	pte_clear_bits(pte, _PAGE_ACCESSED);
	वापस(pte);
पूर्ण

अटल अंतरभूत pte_t pte_wrprotect(pte_t pte)
अणु
	अगर (likely(pte_get_bits(pte, _PAGE_RW)))
		pte_clear_bits(pte, _PAGE_RW);
	अन्यथा
		वापस pte;
	वापस(pte_mknewprot(pte));
पूर्ण

अटल अंतरभूत pte_t pte_mkपढ़ो(pte_t pte)
अणु
	अगर (unlikely(pte_get_bits(pte, _PAGE_USER)))
		वापस pte;
	pte_set_bits(pte, _PAGE_USER);
	वापस(pte_mknewprot(pte));
पूर्ण

अटल अंतरभूत pte_t pte_सूची_गढ़ोty(pte_t pte)
अणु
	pte_set_bits(pte, _PAGE_सूचीTY);
	वापस(pte);
पूर्ण

अटल अंतरभूत pte_t pte_mkyoung(pte_t pte)
अणु
	pte_set_bits(pte, _PAGE_ACCESSED);
	वापस(pte);
पूर्ण

अटल अंतरभूत pte_t pte_mkग_लिखो(pte_t pte)
अणु
	अगर (unlikely(pte_get_bits(pte,  _PAGE_RW)))
		वापस pte;
	pte_set_bits(pte, _PAGE_RW);
	वापस(pte_mknewprot(pte));
पूर्ण

अटल अंतरभूत pte_t pte_mkuptodate(pte_t pte)
अणु
	pte_clear_bits(pte, _PAGE_NEWPAGE);
	अगर(pte_present(pte))
		pte_clear_bits(pte, _PAGE_NEWPROT);
	वापस(pte);
पूर्ण

अटल अंतरभूत pte_t pte_mknewpage(pte_t pte)
अणु
	pte_set_bits(pte, _PAGE_NEWPAGE);
	वापस(pte);
पूर्ण

अटल अंतरभूत व्योम set_pte(pte_t *pteptr, pte_t pteval)
अणु
	pte_copy(*pteptr, pteval);

	/* If it's a swap entry, it needs to be marked _PAGE_NEWPAGE so
	 * fix_range knows to unmap it.  _PAGE_NEWPROT is specअगरic to
	 * mapped pages.
	 */

	*pteptr = pte_mknewpage(*pteptr);
	अगर(pte_present(*pteptr)) *pteptr = pte_mknewprot(*pteptr);
पूर्ण

अटल अंतरभूत व्योम set_pte_at(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      pte_t *pteptr, pte_t pteval)
अणु
	set_pte(pteptr, pteval);
पूर्ण

#घोषणा __HAVE_ARCH_PTE_SAME
अटल अंतरभूत पूर्णांक pte_same(pte_t pte_a, pte_t pte_b)
अणु
	वापस !((pte_val(pte_a) ^ pte_val(pte_b)) & ~_PAGE_NEWPAGE);
पूर्ण

/*
 * Conversion functions: convert a page and protection to a page entry,
 * and a page entry and page directory to the page they refer to.
 */

#घोषणा phys_to_page(phys) pfn_to_page(phys_to_pfn(phys))
#घोषणा __virt_to_page(virt) phys_to_page(__pa(virt))
#घोषणा page_to_phys(page) pfn_to_phys(page_to_pfn(page))
#घोषणा virt_to_page(addr) __virt_to_page((स्थिर अचिन्हित दीर्घ) addr)

#घोषणा mk_pte(page, pgprot) \
	(अणु pte_t pte;					\
							\
	pte_set_val(pte, page_to_phys(page), (pgprot));	\
	अगर (pte_present(pte))				\
		pte_mknewprot(pte_mknewpage(pte));	\
	pte;पूर्ण)

अटल अंतरभूत pte_t pte_modअगरy(pte_t pte, pgprot_t newprot)
अणु
	pte_set_val(pte, (pte_val(pte) & _PAGE_CHG_MASK), newprot);
	वापस pte;
पूर्ण

/*
 * the pmd page can be thought of an array like this: pmd_t[PTRS_PER_PMD]
 *
 * this macro वापसs the index of the entry in the pmd page which would
 * control the given भव address
 */
#घोषणा pmd_page_vaddr(pmd) ((अचिन्हित दीर्घ) __va(pmd_val(pmd) & PAGE_MASK))

काष्ठा mm_काष्ठा;
बाह्य pte_t *virt_to_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr);

#घोषणा update_mmu_cache(vma,address,ptep) करो अणुपूर्ण जबतक (0)

/* Encode and de-code a swap entry */
#घोषणा __swp_type(x)			(((x).val >> 5) & 0x1f)
#घोषणा __swp_offset(x)			((x).val >> 11)

#घोषणा __swp_entry(type, offset) \
	((swp_entry_t) अणु ((type) << 5) | ((offset) << 11) पूर्ण)
#घोषणा __pte_to_swp_entry(pte) \
	((swp_entry_t) अणु pte_val(pte_mkuptodate(pte)) पूर्ण)
#घोषणा __swp_entry_to_pte(x)		((pte_t) अणु (x).val पूर्ण)

#घोषणा kern_addr_valid(addr) (1)

/* Clear a kernel PTE and flush it from the TLB */
#घोषणा kpte_clear_flush(ptep, vaddr)		\
करो अणु						\
	pte_clear(&init_mm, (vaddr), (ptep));	\
	__flush_tlb_one((vaddr));		\
पूर्ण जबतक (0)

#पूर्ण_अगर
