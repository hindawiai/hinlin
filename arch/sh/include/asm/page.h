<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_PAGE_H
#घोषणा __ASM_SH_PAGE_H

/*
 * Copyright (C) 1999  Niibe Yutaka
 */

#समावेश <linux/स्थिर.h>

/* PAGE_SHIFT determines the page size */
#अगर defined(CONFIG_PAGE_SIZE_4KB)
# define PAGE_SHIFT	12
#या_अगर defined(CONFIG_PAGE_SIZE_8KB)
# define PAGE_SHIFT	13
#या_अगर defined(CONFIG_PAGE_SIZE_16KB)
# define PAGE_SHIFT	14
#या_अगर defined(CONFIG_PAGE_SIZE_64KB)
# define PAGE_SHIFT	16
#अन्यथा
# error "Bogus kernel page size?"
#पूर्ण_अगर

#घोषणा PAGE_SIZE	(_AC(1, UL) << PAGE_SHIFT)
#घोषणा PAGE_MASK	(~(PAGE_SIZE-1))
#घोषणा PTE_MASK	PAGE_MASK

#अगर defined(CONFIG_HUGETLB_PAGE_SIZE_64K)
#घोषणा HPAGE_SHIFT	16
#या_अगर defined(CONFIG_HUGETLB_PAGE_SIZE_256K)
#घोषणा HPAGE_SHIFT	18
#या_अगर defined(CONFIG_HUGETLB_PAGE_SIZE_1MB)
#घोषणा HPAGE_SHIFT	20
#या_अगर defined(CONFIG_HUGETLB_PAGE_SIZE_4MB)
#घोषणा HPAGE_SHIFT	22
#या_अगर defined(CONFIG_HUGETLB_PAGE_SIZE_64MB)
#घोषणा HPAGE_SHIFT	26
#पूर्ण_अगर

#अगर_घोषित CONFIG_HUGETLB_PAGE
#घोषणा HPAGE_SIZE		(1UL << HPAGE_SHIFT)
#घोषणा HPAGE_MASK		(~(HPAGE_SIZE-1))
#घोषणा HUGETLB_PAGE_ORDER	(HPAGE_SHIFT-PAGE_SHIFT)
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__
#समावेश <यंत्र/uncached.h>

बाह्य अचिन्हित दीर्घ shm_align_mask;
बाह्य अचिन्हित दीर्घ max_low_pfn, min_low_pfn;
बाह्य अचिन्हित दीर्घ memory_start, memory_end, memory_limit;

अटल अंतरभूत अचिन्हित दीर्घ
pages_करो_alias(अचिन्हित दीर्घ addr1, अचिन्हित दीर्घ addr2)
अणु
	वापस (addr1 ^ addr2) & shm_align_mask;
पूर्ण

#घोषणा clear_page(page)	स_रखो((व्योम *)(page), 0, PAGE_SIZE)
बाह्य व्योम copy_page(व्योम *to, व्योम *from);
#घोषणा copy_user_page(to, from, vaddr, pg)  __copy_user(to, from, PAGE_SIZE)

काष्ठा page;
काष्ठा vm_area_काष्ठा;

बाह्य व्योम copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
			       अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma);
#घोषणा __HAVE_ARCH_COPY_USER_HIGHPAGE
बाह्य व्योम clear_user_highpage(काष्ठा page *page, अचिन्हित दीर्घ vaddr);
#घोषणा clear_user_highpage	clear_user_highpage

/*
 * These are used to make use of C type-checking..
 */
#अगर_घोषित CONFIG_X2TLB
प्रकार काष्ठा अणु अचिन्हित दीर्घ pte_low, pte_high; पूर्ण pte_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ दीर्घ pgprot; पूर्ण pgprot_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ दीर्घ pgd; पूर्ण pgd_t;
#घोषणा pte_val(x) \
	((x).pte_low | ((अचिन्हित दीर्घ दीर्घ)(x).pte_high << 32))
#घोषणा __pte(x) \
	(अणु pte_t __pte = अणु(x), ((अचिन्हित दीर्घ दीर्घ)(x)) >> 32पूर्ण; __pte; पूर्ण)
#अन्यथा
प्रकार काष्ठा अणु अचिन्हित दीर्घ pte_low; पूर्ण pte_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgprot; पूर्ण pgprot_t;
प्रकार काष्ठा अणु अचिन्हित दीर्घ pgd; पूर्ण pgd_t;
#घोषणा pte_val(x)	((x).pte_low)
#घोषणा __pte(x)	((pte_t) अणु (x) पूर्ण )
#पूर्ण_अगर

#घोषणा pgd_val(x)	((x).pgd)
#घोषणा pgprot_val(x)	((x).pgprot)

#घोषणा __pgd(x) ((pgd_t) अणु (x) पूर्ण )
#घोषणा __pgprot(x)	((pgprot_t) अणु (x) पूर्ण )

प्रकार काष्ठा page *pgtable_t;

#घोषणा pte_pgprot(x) __pgprot(pte_val(x) & PTE_FLAGS_MASK)

#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * __MEMORY_START and SIZE are the physical addresses and size of RAM.
 */
#घोषणा __MEMORY_START		CONFIG_MEMORY_START
#घोषणा __MEMORY_SIZE		CONFIG_MEMORY_SIZE

/*
 * PHYSICAL_OFFSET is the offset in physical memory where the base
 * of the kernel is loaded.
 */
#अगर_घोषित CONFIG_PHYSICAL_START
#घोषणा PHYSICAL_OFFSET (CONFIG_PHYSICAL_START - __MEMORY_START)
#अन्यथा
#घोषणा PHYSICAL_OFFSET 0
#पूर्ण_अगर

/*
 * PAGE_OFFSET is the भव address of the start of kernel address
 * space.
 */
#घोषणा PAGE_OFFSET		CONFIG_PAGE_OFFSET

/*
 * Virtual to physical RAM address translation.
 *
 * In 29 bit mode, the physical offset of RAM from address 0 is visible in
 * the kernel भव address space, and thus we करोn't have to take
 * this पूर्णांकo account when translating. However in 32 bit mode this offset
 * is not visible (it is part of the PMB mapping) and so needs to be
 * added or subtracted as required.
 */
#अगर_घोषित CONFIG_PMB
#घोषणा ___pa(x)	((x)-PAGE_OFFSET+__MEMORY_START)
#घोषणा ___va(x)	((x)+PAGE_OFFSET-__MEMORY_START)
#अन्यथा
#घोषणा ___pa(x)	((x)-PAGE_OFFSET)
#घोषणा ___va(x)	((x)+PAGE_OFFSET)
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__
#घोषणा __pa(x)		___pa((अचिन्हित दीर्घ)x)
#घोषणा __va(x)		(व्योम *)___va((अचिन्हित दीर्घ)x)
#पूर्ण_अगर /* !__ASSEMBLY__ */

#अगर_घोषित CONFIG_UNCACHED_MAPPING
#अगर defined(CONFIG_29BIT)
#घोषणा UNCAC_ADDR(addr)	P2SEGADDR(addr)
#घोषणा CAC_ADDR(addr)		P1SEGADDR(addr)
#अन्यथा
#घोषणा UNCAC_ADDR(addr)	((addr) - PAGE_OFFSET + uncached_start)
#घोषणा CAC_ADDR(addr)		((addr) - uncached_start + PAGE_OFFSET)
#पूर्ण_अगर
#अन्यथा
#घोषणा UNCAC_ADDR(addr)	((addr))
#घोषणा CAC_ADDR(addr)		((addr))
#पूर्ण_अगर

#घोषणा pfn_to_kaddr(pfn)	__va((pfn) << PAGE_SHIFT)
#घोषणा page_to_phys(page)	(page_to_pfn(page) << PAGE_SHIFT)

/*
 * PFN = physical frame number (ie PFN 0 == physical address 0)
 * PFN_START is the PFN of the first page of RAM. By defining this we
 * करोn't have काष्ठा page entries क्रम the portion of address space
 * between physical address 0 and the start of RAM.
 */
#घोषणा PFN_START		(__MEMORY_START >> PAGE_SHIFT)
#घोषणा ARCH_PFN_OFFSET		(PFN_START)
#घोषणा virt_to_page(kaddr)	pfn_to_page(__pa(kaddr) >> PAGE_SHIFT)
#अगर_घोषित CONFIG_FLATMEM
#घोषणा pfn_valid(pfn)		((pfn) >= min_low_pfn && (pfn) < max_low_pfn)
#पूर्ण_अगर
#घोषणा virt_addr_valid(kaddr)	pfn_valid(__pa(kaddr) >> PAGE_SHIFT)

#समावेश <यंत्र-generic/memory_model.h>
#समावेश <यंत्र-generic/getorder.h>

/*
 * Some drivers need to perक्रमm DMA पूर्णांकo kदो_स्मृति'ed buffers
 * and so we have to increase the kदो_स्मृति minalign क्रम this.
 */
#घोषणा ARCH_DMA_MINALIGN	L1_CACHE_BYTES

#पूर्ण_अगर /* __ASM_SH_PAGE_H */
