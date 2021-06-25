<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2009 Chen Liqin <liqin.chen@sunplusct.com>
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 * Copyright (C) 2017 SiFive
 * Copyright (C) 2017 XiaojingZhu <zhuxiaoj@ict.ac.cn>
 */

#अगर_अघोषित _ASM_RISCV_PAGE_H
#घोषणा _ASM_RISCV_PAGE_H

#समावेश <linux/pfn.h>
#समावेश <linux/स्थिर.h>

#घोषणा PAGE_SHIFT	(12)
#घोषणा PAGE_SIZE	(_AC(1, UL) << PAGE_SHIFT)
#घोषणा PAGE_MASK	(~(PAGE_SIZE - 1))

#अगर_घोषित CONFIG_64BIT
#घोषणा HUGE_MAX_HSTATE		2
#अन्यथा
#घोषणा HUGE_MAX_HSTATE		1
#पूर्ण_अगर
#घोषणा HPAGE_SHIFT		PMD_SHIFT
#घोषणा HPAGE_SIZE		(_AC(1, UL) << HPAGE_SHIFT)
#घोषणा HPAGE_MASK              (~(HPAGE_SIZE - 1))
#घोषणा HUGETLB_PAGE_ORDER      (HPAGE_SHIFT - PAGE_SHIFT)

/*
 * PAGE_OFFSET -- the first address of the first page of memory.
 * When not using MMU this corresponds to the first मुक्त page in
 * physical memory (aligned on a page boundary).
 */
#घोषणा PAGE_OFFSET		_AC(CONFIG_PAGE_OFFSET, UL)

#घोषणा KERN_VIRT_SIZE (-PAGE_OFFSET)

#अगर_अघोषित __ASSEMBLY__

#घोषणा PAGE_UP(addr)	(((addr)+((PAGE_SIZE)-1))&(~((PAGE_SIZE)-1)))
#घोषणा PAGE_DOWN(addr)	((addr)&(~((PAGE_SIZE)-1)))

/* align addr on a size boundary - adjust address up/करोwn अगर needed */
#घोषणा _ALIGN_UP(addr, size)	(((addr)+((size)-1))&(~((size)-1)))
#घोषणा _ALIGN_DOWN(addr, size)	((addr)&(~((size)-1)))

/* align addr on a size boundary - adjust address up अगर needed */
#घोषणा _ALIGN(addr, size)	_ALIGN_UP(addr, size)

#घोषणा clear_page(pgaddr)			स_रखो((pgaddr), 0, PAGE_SIZE)
#घोषणा copy_page(to, from)			स_नकल((to), (from), PAGE_SIZE)

#घोषणा clear_user_page(pgaddr, vaddr, page)	स_रखो((pgaddr), 0, PAGE_SIZE)
#घोषणा copy_user_page(vto, vfrom, vaddr, topg) \
			स_नकल((vto), (vfrom), PAGE_SIZE)

/*
 * Use काष्ठा definitions to apply C type checking
 */

/* Page Global Directory entry */
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ pgd;
पूर्ण pgd_t;

/* Page Table entry */
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ pte;
पूर्ण pte_t;

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ pgprot;
पूर्ण pgprot_t;

प्रकार काष्ठा page *pgtable_t;

#घोषणा pte_val(x)	((x).pte)
#घोषणा pgd_val(x)	((x).pgd)
#घोषणा pgprot_val(x)	((x).pgprot)

#घोषणा __pte(x)	((pte_t) अणु (x) पूर्ण)
#घोषणा __pgd(x)	((pgd_t) अणु (x) पूर्ण)
#घोषणा __pgprot(x)	((pgprot_t) अणु (x) पूर्ण)

#अगर_घोषित CONFIG_64BIT
#घोषणा PTE_FMT "%016lx"
#अन्यथा
#घोषणा PTE_FMT "%08lx"
#पूर्ण_अगर

#अगर_घोषित CONFIG_MMU
बाह्य अचिन्हित दीर्घ va_pa_offset;
#अगर_घोषित CONFIG_64BIT
बाह्य अचिन्हित दीर्घ va_kernel_pa_offset;
#पूर्ण_अगर
#अगर_घोषित CONFIG_XIP_KERNEL
बाह्य अचिन्हित दीर्घ va_kernel_xip_pa_offset;
#पूर्ण_अगर
बाह्य अचिन्हित दीर्घ pfn_base;
#घोषणा ARCH_PFN_OFFSET		(pfn_base)
#अन्यथा
#घोषणा va_pa_offset		0
#अगर_घोषित CONFIG_64BIT
#घोषणा va_kernel_pa_offset	0
#पूर्ण_अगर
#घोषणा ARCH_PFN_OFFSET		(PAGE_OFFSET >> PAGE_SHIFT)
#पूर्ण_अगर /* CONFIG_MMU */

बाह्य अचिन्हित दीर्घ kernel_virt_addr;

#अगर_घोषित CONFIG_64BIT
#घोषणा linear_mapping_pa_to_va(x)	((व्योम *)((अचिन्हित दीर्घ)(x) + va_pa_offset))
#अगर_घोषित CONFIG_XIP_KERNEL
#घोषणा kernel_mapping_pa_to_va(y)	(अणु						\
	अचिन्हित दीर्घ _y = y;								\
	(_y >= CONFIG_PHYS_RAM_BASE) ?							\
		(व्योम *)((अचिन्हित दीर्घ)(_y) + va_kernel_pa_offset + XIP_OFFSET) :	\
		(व्योम *)((अचिन्हित दीर्घ)(_y) + va_kernel_xip_pa_offset);		\
	पूर्ण)
#अन्यथा
#घोषणा kernel_mapping_pa_to_va(x)	((व्योम *)((अचिन्हित दीर्घ)(x) + va_kernel_pa_offset))
#पूर्ण_अगर
#घोषणा __pa_to_va_nodebug(x)		linear_mapping_pa_to_va(x)

#घोषणा linear_mapping_va_to_pa(x)	((अचिन्हित दीर्घ)(x) - va_pa_offset)
#अगर_घोषित CONFIG_XIP_KERNEL
#घोषणा kernel_mapping_va_to_pa(y) (अणु						\
	अचिन्हित दीर्घ _y = y;							\
	(_y < kernel_virt_addr + XIP_OFFSET) ?					\
		((अचिन्हित दीर्घ)(_y) - va_kernel_xip_pa_offset) :		\
		((अचिन्हित दीर्घ)(_y) - va_kernel_pa_offset - XIP_OFFSET);	\
	पूर्ण)
#अन्यथा
#घोषणा kernel_mapping_va_to_pa(x)	((अचिन्हित दीर्घ)(x) - va_kernel_pa_offset)
#पूर्ण_अगर
#घोषणा __va_to_pa_nodebug(x)	(अणु						\
	अचिन्हित दीर्घ _x = x;							\
	(_x < kernel_virt_addr) ?						\
		linear_mapping_va_to_pa(_x) : kernel_mapping_va_to_pa(_x);	\
	पूर्ण)
#अन्यथा
#घोषणा __pa_to_va_nodebug(x)  ((व्योम *)((अचिन्हित दीर्घ) (x) + va_pa_offset))
#घोषणा __va_to_pa_nodebug(x)  ((अचिन्हित दीर्घ)(x) - va_pa_offset)
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_VIRTUAL
बाह्य phys_addr_t __virt_to_phys(अचिन्हित दीर्घ x);
बाह्य phys_addr_t __phys_addr_symbol(अचिन्हित दीर्घ x);
#अन्यथा
#घोषणा __virt_to_phys(x)	__va_to_pa_nodebug(x)
#घोषणा __phys_addr_symbol(x)	__va_to_pa_nodebug(x)
#पूर्ण_अगर /* CONFIG_DEBUG_VIRTUAL */

#घोषणा __pa_symbol(x)	__phys_addr_symbol(RELOC_HIDE((अचिन्हित दीर्घ)(x), 0))
#घोषणा __pa(x)		__virt_to_phys((अचिन्हित दीर्घ)(x))
#घोषणा __va(x)		((व्योम *)__pa_to_va_nodebug((phys_addr_t)(x)))

#घोषणा phys_to_pfn(phys)	(PFN_DOWN(phys))
#घोषणा pfn_to_phys(pfn)	(PFN_PHYS(pfn))

#घोषणा virt_to_pfn(vaddr)	(phys_to_pfn(__pa(vaddr)))
#घोषणा pfn_to_virt(pfn)	(__va(pfn_to_phys(pfn)))

#घोषणा virt_to_page(vaddr)	(pfn_to_page(virt_to_pfn(vaddr)))
#घोषणा page_to_virt(page)	(pfn_to_virt(page_to_pfn(page)))

#घोषणा page_to_phys(page)	(pfn_to_phys(page_to_pfn(page)))
#घोषणा page_to_bus(page)	(page_to_phys(page))
#घोषणा phys_to_page(paddr)	(pfn_to_page(phys_to_pfn(paddr)))

#अगर_घोषित CONFIG_FLATMEM
#घोषणा pfn_valid(pfn) \
	(((pfn) >= ARCH_PFN_OFFSET) && (((pfn) - ARCH_PFN_OFFSET) < max_mapnr))
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

#घोषणा virt_addr_valid(vaddr)	(अणु						\
	अचिन्हित दीर्घ _addr = (अचिन्हित दीर्घ)vaddr;				\
	(अचिन्हित दीर्घ)(_addr) >= PAGE_OFFSET && pfn_valid(virt_to_pfn(_addr));	\
पूर्ण)

#घोषणा VM_DATA_DEFAULT_FLAGS	VM_DATA_FLAGS_NON_EXEC

#समावेश <यंत्र-generic/memory_model.h>
#समावेश <यंत्र-generic/getorder.h>

#पूर्ण_अगर /* _ASM_RISCV_PAGE_H */
