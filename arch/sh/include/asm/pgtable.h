<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * This file contains the functions and defines necessary to modअगरy and
 * use the SuperH page table tree.
 *
 * Copyright (C) 1999 Niibe Yutaka
 * Copyright (C) 2002 - 2007 Paul Mundt
 */
#अगर_अघोषित __ASM_SH_PGTABLE_H
#घोषणा __ASM_SH_PGTABLE_H

#अगर_घोषित CONFIG_X2TLB
#समावेश <यंत्र/pgtable-3level.h>
#अन्यथा
#समावेश <यंत्र/pgtable-2level.h>
#पूर्ण_अगर
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mmu.h>

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/fixmap.h>

/*
 * ZERO_PAGE is a global shared page that is always zero: used
 * क्रम zero-mapped memory areas etc..
 */
बाह्य अचिन्हित दीर्घ empty_zero_page[PAGE_SIZE / माप(अचिन्हित दीर्घ)];
#घोषणा ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))

#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * Effective and physical address definitions, to aid with sign
 * extension.
 */
#घोषणा NEFF		32
#घोषणा	NEFF_SIGN	(1LL << (NEFF - 1))
#घोषणा	NEFF_MASK	(-1LL << NEFF)

अटल अंतरभूत अचिन्हित दीर्घ दीर्घ neff_sign_extend(अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ दीर्घ extended = val;
	वापस (extended & NEFF_SIGN) ? (extended | NEFF_MASK) : extended;
पूर्ण

#अगर_घोषित CONFIG_29BIT
#घोषणा NPHYS		29
#अन्यथा
#घोषणा NPHYS		32
#पूर्ण_अगर

#घोषणा	NPHYS_SIGN	(1LL << (NPHYS - 1))
#घोषणा	NPHYS_MASK	(-1LL << NPHYS)

#घोषणा PGसूची_SIZE	(1UL << PGसूची_SHIFT)
#घोषणा PGसूची_MASK	(~(PGसूची_SIZE-1))

/* Entries per level */
#घोषणा PTRS_PER_PTE	(PAGE_SIZE / (1 << PTE_MAGNITUDE))

#घोषणा FIRST_USER_ADDRESS	0UL

#घोषणा PHYS_ADDR_MASK29		0x1fffffff
#घोषणा PHYS_ADDR_MASK32		0xffffffff

अटल अंतरभूत अचिन्हित दीर्घ phys_addr_mask(व्योम)
अणु
	/* Is the MMU in 29bit mode? */
	अगर (__in_29bit_mode())
		वापस PHYS_ADDR_MASK29;

	वापस PHYS_ADDR_MASK32;
पूर्ण

#घोषणा PTE_PHYS_MASK		(phys_addr_mask() & PAGE_MASK)
#घोषणा PTE_FLAGS_MASK		(~(PTE_PHYS_MASK) << PAGE_SHIFT)

#घोषणा VMALLOC_START	(P3SEG)
#घोषणा VMALLOC_END	(FIXADDR_START-2*PAGE_SIZE)

#समावेश <यंत्र/pgtable_32.h>

/*
 * SH-X and lower (legacy) SuperH parts (SH-3, SH-4, some SH-4A) can't करो page
 * protection क्रम execute, and considers it the same as a पढ़ो. Also, ग_लिखो
 * permission implies पढ़ो permission. This is the बंदst we can get..
 *
 * SH-X2 (SH7785) and later parts take this to the opposite end of the extreme,
 * not only supporting separate execute, पढ़ो, and ग_लिखो bits, but having
 * completely separate permission bits क्रम user and kernel space.
 */
	 /*xwr*/
#घोषणा __P000	PAGE_NONE
#घोषणा __P001	PAGE_READONLY
#घोषणा __P010	PAGE_COPY
#घोषणा __P011	PAGE_COPY
#घोषणा __P100	PAGE_EXECREAD
#घोषणा __P101	PAGE_EXECREAD
#घोषणा __P110	PAGE_COPY
#घोषणा __P111	PAGE_COPY

#घोषणा __S000	PAGE_NONE
#घोषणा __S001	PAGE_READONLY
#घोषणा __S010	PAGE_WRITEONLY
#घोषणा __S011	PAGE_SHARED
#घोषणा __S100	PAGE_EXECREAD
#घोषणा __S101	PAGE_EXECREAD
#घोषणा __S110	PAGE_RWX
#घोषणा __S111	PAGE_RWX

प्रकार pte_t *pte_addr_t;

#घोषणा kern_addr_valid(addr)	(1)

#घोषणा pte_pfn(x)		((अचिन्हित दीर्घ)(((x).pte_low >> PAGE_SHIFT)))

काष्ठा vm_area_काष्ठा;
काष्ठा mm_काष्ठा;

बाह्य व्योम __update_cache(काष्ठा vm_area_काष्ठा *vma,
			   अचिन्हित दीर्घ address, pte_t pte);
बाह्य व्योम __update_tlb(काष्ठा vm_area_काष्ठा *vma,
			 अचिन्हित दीर्घ address, pte_t pte);

अटल अंतरभूत व्योम
update_mmu_cache(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address, pte_t *ptep)
अणु
	pte_t pte = *ptep;
	__update_cache(vma, address, pte);
	__update_tlb(vma, address, pte);
पूर्ण

बाह्य pgd_t swapper_pg_dir[PTRS_PER_PGD];
बाह्य व्योम paging_init(व्योम);
बाह्य व्योम page_table_range_init(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				  pgd_t *pgd);

अटल अंतरभूत bool __pte_access_permitted(pte_t pte, u64 prot)
अणु
	वापस (pte_val(pte) & (prot | _PAGE_SPECIAL)) == prot;
पूर्ण

#अगर_घोषित CONFIG_X2TLB
अटल अंतरभूत bool pte_access_permitted(pte_t pte, bool ग_लिखो)
अणु
	u64 prot = _PAGE_PRESENT;

	prot |= _PAGE_EXT(_PAGE_EXT_KERN_READ | _PAGE_EXT_USER_READ);
	अगर (ग_लिखो)
		prot |= _PAGE_EXT(_PAGE_EXT_KERN_WRITE | _PAGE_EXT_USER_WRITE);
	वापस __pte_access_permitted(pte, prot);
पूर्ण
#अन्यथा
अटल अंतरभूत bool pte_access_permitted(pte_t pte, bool ग_लिखो)
अणु
	u64 prot = _PAGE_PRESENT | _PAGE_USER;

	अगर (ग_लिखो)
		prot |= _PAGE_RW;
	वापस __pte_access_permitted(pte, prot);
पूर्ण
#पूर्ण_अगर

#घोषणा pte_access_permitted pte_access_permitted

/* arch/sh/mm/mmap.c */
#घोषणा HAVE_ARCH_UNMAPPED_AREA
#घोषणा HAVE_ARCH_UNMAPPED_AREA_TOPDOWN

#पूर्ण_अगर /* __ASM_SH_PGTABLE_H */
