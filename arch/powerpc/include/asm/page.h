<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_PAGE_H
#घोषणा _ASM_POWERPC_PAGE_H

/*
 * Copyright (C) 2001,2005 IBM Corporation.
 */

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#अन्यथा
#समावेश <यंत्र/types.h>
#पूर्ण_अगर
#समावेश <यंत्र/यंत्र-स्थिर.h>

/*
 * On regular PPC32 page size is 4K (but we support 4K/16K/64K/256K pages
 * on PPC44x and 4K/16K on 8xx). For PPC64 we support either 4K or 64K software
 * page size. When using 64K pages however, whether we are really supporting
 * 64K pages in HW or not is irrelevant to those definitions.
 */
#घोषणा PAGE_SHIFT		CONFIG_PPC_PAGE_SHIFT
#घोषणा PAGE_SIZE		(ASM_CONST(1) << PAGE_SHIFT)

#अगर_अघोषित __ASSEMBLY__
#अगर_अघोषित CONFIG_HUGETLB_PAGE
#घोषणा HPAGE_SHIFT PAGE_SHIFT
#या_अगर defined(CONFIG_PPC_BOOK3S_64)
बाह्य अचिन्हित पूर्णांक hpage_shअगरt;
#घोषणा HPAGE_SHIFT hpage_shअगरt
#या_अगर defined(CONFIG_PPC_8xx)
#घोषणा HPAGE_SHIFT		19	/* 512k pages */
#या_अगर defined(CONFIG_PPC_FSL_BOOK3E)
#घोषणा HPAGE_SHIFT		22	/* 4M pages */
#पूर्ण_अगर
#घोषणा HPAGE_SIZE		((1UL) << HPAGE_SHIFT)
#घोषणा HPAGE_MASK		(~(HPAGE_SIZE - 1))
#घोषणा HUGETLB_PAGE_ORDER	(HPAGE_SHIFT - PAGE_SHIFT)
#घोषणा HUGE_MAX_HSTATE		(MMU_PAGE_COUNT-1)
#पूर्ण_अगर

/*
 * Subtle: (1 << PAGE_SHIFT) is an पूर्णांक, not an अचिन्हित दीर्घ. So अगर we
 * assign PAGE_MASK to a larger type it माला_लो extended the way we want
 * (i.e. with 1s in the high bits)
 */
#घोषणा PAGE_MASK      (~((1 << PAGE_SHIFT) - 1))

/*
 * KERNELBASE is the भव address of the start of the kernel, it's often
 * the same as PAGE_OFFSET, but _might not be_.
 *
 * The kdump dump kernel is one example where KERNELBASE != PAGE_OFFSET.
 *
 * PAGE_OFFSET is the भव address of the start of lowmem.
 *
 * PHYSICAL_START is the physical address of the start of the kernel.
 *
 * MEMORY_START is the physical address of the start of lowmem.
 *
 * KERNELBASE, PAGE_OFFSET, and PHYSICAL_START are all configurable on
 * ppc32 and based on how they are set we determine MEMORY_START.
 *
 * For the linear mapping the following equation should be true:
 * KERNELBASE - PAGE_OFFSET = PHYSICAL_START - MEMORY_START
 *
 * Also, KERNELBASE >= PAGE_OFFSET and PHYSICAL_START >= MEMORY_START
 *
 * There are two ways to determine a physical address from a भव one:
 * va = pa + PAGE_OFFSET - MEMORY_START
 * va = pa + KERNELBASE - PHYSICAL_START
 *
 * If you want to know something's offset from the start of the kernel you
 * should subtract KERNELBASE.
 *
 * If you want to test अगर something's a kernel address, use is_kernel_addr().
 */

#घोषणा KERNELBASE      ASM_CONST(CONFIG_KERNEL_START)
#घोषणा PAGE_OFFSET	ASM_CONST(CONFIG_PAGE_OFFSET)
#घोषणा LOAD_OFFSET	ASM_CONST((CONFIG_KERNEL_START-CONFIG_PHYSICAL_START))

#अगर defined(CONFIG_NONSTATIC_KERNEL)
#अगर_अघोषित __ASSEMBLY__

बाह्य phys_addr_t memstart_addr;
बाह्य phys_addr_t kernstart_addr;

#अगर defined(CONFIG_RELOCATABLE) && defined(CONFIG_PPC32)
बाह्य दीर्घ दीर्घ virt_phys_offset;
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */
#घोषणा PHYSICAL_START	kernstart_addr

#अन्यथा	/* !CONFIG_NONSTATIC_KERNEL */
#घोषणा PHYSICAL_START	ASM_CONST(CONFIG_PHYSICAL_START)
#पूर्ण_अगर

/* See Description below क्रम VIRT_PHYS_OFFSET */
#अगर defined(CONFIG_PPC32) && defined(CONFIG_BOOKE)
#अगर_घोषित CONFIG_RELOCATABLE
#घोषणा VIRT_PHYS_OFFSET virt_phys_offset
#अन्यथा
#घोषणा VIRT_PHYS_OFFSET (KERNELBASE - PHYSICAL_START)
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC64
#घोषणा MEMORY_START	0UL
#या_अगर defined(CONFIG_NONSTATIC_KERNEL)
#घोषणा MEMORY_START	memstart_addr
#अन्यथा
#घोषणा MEMORY_START	(PHYSICAL_START + PAGE_OFFSET - KERNELBASE)
#पूर्ण_अगर

#अगर_घोषित CONFIG_FLATMEM
#घोषणा ARCH_PFN_OFFSET		((अचिन्हित दीर्घ)(MEMORY_START >> PAGE_SHIFT))
#अगर_अघोषित __ASSEMBLY__
बाह्य अचिन्हित दीर्घ max_mapnr;
अटल अंतरभूत bool pfn_valid(अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित दीर्घ min_pfn = ARCH_PFN_OFFSET;

	वापस pfn >= min_pfn && pfn < max_mapnr;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

#घोषणा virt_to_pfn(kaddr)	(__pa(kaddr) >> PAGE_SHIFT)
#घोषणा virt_to_page(kaddr)	pfn_to_page(virt_to_pfn(kaddr))
#घोषणा pfn_to_kaddr(pfn)	__va((pfn) << PAGE_SHIFT)

#घोषणा virt_addr_valid(kaddr)	pfn_valid(virt_to_pfn(kaddr))

/*
 * On Book-E parts we need __va to parse the device tree and we can't
 * determine MEMORY_START until then.  However we can determine PHYSICAL_START
 * from inक्रमmation at hand (program counter, TLB lookup).
 *
 * On BookE with RELOCATABLE && PPC32
 *
 *   With RELOCATABLE && PPC32,  we support loading the kernel at any physical
 *   address without any restriction on the page alignment.
 *
 *   We find the runसमय address of _stext and relocate ourselves based on 
 *   the following calculation:
 *
 *  	  भव_base = ALIGN_DOWN(KERNELBASE,256M) +
 *  				MODULO(_stext.run,256M)
 *   and create the following mapping:
 *
 * 	  ALIGN_DOWN(_stext.run,256M) => ALIGN_DOWN(KERNELBASE,256M)
 *
 *   When we process relocations, we cannot depend on the
 *   existing equation क्रम the __va()/__pa() translations:
 *
 * 	   __va(x) = (x)  - PHYSICAL_START + KERNELBASE
 *
 *   Where:
 *   	 PHYSICAL_START = kernstart_addr = Physical address of _stext
 *  	 KERNELBASE = Compiled भव address of _stext.
 *
 *   This क्रमmula holds true अगरf, kernel load address is TLB page aligned.
 *
 *   In our हाल, we need to also account क्रम the shअगरt in the kernel Virtual 
 *   address.
 *
 *   E.g.,
 *
 *   Let the kernel be loaded at 64MB and KERNELBASE be 0xc0000000 (same as PAGE_OFFSET).
 *   In this हाल, we would be mapping 0 to 0xc0000000, and kernstart_addr = 64M
 *
 *   Now __va(1MB) = (0x100000) - (0x4000000) + 0xc0000000
 *                 = 0xbc100000 , which is wrong.
 *
 *   Rather, it should be : 0xc0000000 + 0x100000 = 0xc0100000
 *      	according to our mapping.
 *
 *   Hence we use the following क्रमmula to get the translations right:
 *
 * 	  __va(x) = (x) - [ PHYSICAL_START - Effective KERNELBASE ]
 *
 * 	  Where :
 * 		PHYSICAL_START = dynamic load address.(kernstart_addr variable)
 * 		Effective KERNELBASE = भव_base =
 * 				     = ALIGN_DOWN(KERNELBASE,256M) +
 * 						MODULO(PHYSICAL_START,256M)
 *
 * 	To make the cost of __va() / __pa() more light weight, we पूर्णांकroduce
 * 	a new variable virt_phys_offset, which will hold :
 *
 * 	virt_phys_offset = Effective KERNELBASE - PHYSICAL_START
 * 			 = ALIGN_DOWN(KERNELBASE,256M) - 
 * 			 	ALIGN_DOWN(PHYSICALSTART,256M)
 *
 * 	Hence :
 *
 * 	__va(x) = x - PHYSICAL_START + Effective KERNELBASE
 * 		= x + virt_phys_offset
 *
 * 		and
 * 	__pa(x) = x + PHYSICAL_START - Effective KERNELBASE
 * 		= x - virt_phys_offset
 * 		
 * On non-Book-E PPC64 PAGE_OFFSET and MEMORY_START are स्थिरants so use
 * the other definitions क्रम __va & __pa.
 */
#अगर defined(CONFIG_PPC32) && defined(CONFIG_BOOKE)
#घोषणा __va(x) ((व्योम *)(अचिन्हित दीर्घ)((phys_addr_t)(x) + VIRT_PHYS_OFFSET))
#घोषणा __pa(x) ((phys_addr_t)(अचिन्हित दीर्घ)(x) - VIRT_PHYS_OFFSET)
#अन्यथा
#अगर_घोषित CONFIG_PPC64
/*
 * gcc miscompiles (अचिन्हित दीर्घ)(&अटल_var) - PAGE_OFFSET
 * with -mcmodel=medium, so we use & and | instead of - and + on 64-bit.
 * This also results in better code generation.
 */
#घोषणा __va(x)								\
(अणु									\
	VIRTUAL_BUG_ON((अचिन्हित दीर्घ)(x) >= PAGE_OFFSET);		\
	(व्योम *)(अचिन्हित दीर्घ)((phys_addr_t)(x) | PAGE_OFFSET);	\
पूर्ण)

#घोषणा __pa(x)								\
(अणु									\
	VIRTUAL_BUG_ON((अचिन्हित दीर्घ)(x) < PAGE_OFFSET);		\
	(अचिन्हित दीर्घ)(x) & 0x0fffffffffffffffUL;			\
पूर्ण)

#अन्यथा /* 32-bit, non book E */
#घोषणा __va(x) ((व्योम *)(अचिन्हित दीर्घ)((phys_addr_t)(x) + PAGE_OFFSET - MEMORY_START))
#घोषणा __pa(x) ((अचिन्हित दीर्घ)(x) - PAGE_OFFSET + MEMORY_START)
#पूर्ण_अगर
#पूर्ण_अगर

/*
 * Unक्रमtunately the PLT is in the BSS in the PPC32 ELF ABI,
 * and needs to be executable.  This means the whole heap ends
 * up being executable.
 */
#घोषणा VM_DATA_DEFAULT_FLAGS32	VM_DATA_FLAGS_TSK_EXEC
#घोषणा VM_DATA_DEFAULT_FLAGS64	VM_DATA_FLAGS_NON_EXEC

#अगर_घोषित __घातerpc64__
#समावेश <यंत्र/page_64.h>
#अन्यथा
#समावेश <यंत्र/page_32.h>
#पूर्ण_अगर

/*
 * Don't compare things with KERNELBASE or PAGE_OFFSET to test क्रम
 * "kernelness", use is_kernel_addr() - it should करो what you want.
 */
#अगर_घोषित CONFIG_PPC_BOOK3E_64
#घोषणा is_kernel_addr(x)	((x) >= 0x8000000000000000ul)
#या_अगर defined(CONFIG_PPC_BOOK3S_64)
#घोषणा is_kernel_addr(x)	((x) >= PAGE_OFFSET)
#अन्यथा
#घोषणा is_kernel_addr(x)	((x) >= TASK_SIZE)
#पूर्ण_अगर

#अगर_अघोषित CONFIG_PPC_BOOK3S_64
/*
 * Use the top bit of the higher-level page table entries to indicate whether
 * the entries we poपूर्णांक to contain hugepages.  This works because we know that
 * the page tables live in kernel space.  If we ever decide to support having
 * page tables at arbitrary addresses, this अवरोधs and will have to change.
 */
#अगर_घोषित CONFIG_PPC64
#घोषणा PD_HUGE 0x8000000000000000UL
#अन्यथा
#घोषणा PD_HUGE 0x80000000
#पूर्ण_अगर

#अन्यथा	/* CONFIG_PPC_BOOK3S_64 */
/*
 * Book3S 64 stores real addresses in the hugepd entries to
 * aव्योम overlaps with _PAGE_PRESENT and _PAGE_PTE.
 */
#घोषणा HUGEPD_ADDR_MASK	(0x0ffffffffffffffful & ~HUGEPD_SHIFT_MASK)
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */

/*
 * Some number of bits at the level of the page table that poपूर्णांकs to
 * a hugepte are used to encode the size.  This masks those bits.
 * On 8xx, HW assistance requires 4k alignment क्रम the hugepte.
 */
#अगर_घोषित CONFIG_PPC_8xx
#घोषणा HUGEPD_SHIFT_MASK     0xfff
#अन्यथा
#घोषणा HUGEPD_SHIFT_MASK     0x3f
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित CONFIG_PPC_BOOK3S_64
#समावेश <यंत्र/pgtable-be-types.h>
#अन्यथा
#समावेश <यंत्र/pgtable-types.h>
#पूर्ण_अगर


#अगर_अघोषित CONFIG_HUGETLB_PAGE
#घोषणा is_hugepd(pdep)		(0)
#घोषणा pgd_huge(pgd)		(0)
#पूर्ण_अगर /* CONFIG_HUGETLB_PAGE */

काष्ठा page;
बाह्य व्योम clear_user_page(व्योम *page, अचिन्हित दीर्घ vaddr, काष्ठा page *pg);
बाह्य व्योम copy_user_page(व्योम *to, व्योम *from, अचिन्हित दीर्घ vaddr,
		काष्ठा page *p);
बाह्य पूर्णांक devmem_is_allowed(अचिन्हित दीर्घ pfn);

#अगर_घोषित CONFIG_PPC_SMLPAR
व्योम arch_मुक्त_page(काष्ठा page *page, पूर्णांक order);
#घोषणा HAVE_ARCH_FREE_PAGE
#पूर्ण_अगर

काष्ठा vm_area_काष्ठा;

बाह्य अचिन्हित दीर्घ kernstart_virt_addr;

अटल अंतरभूत अचिन्हित दीर्घ kaslr_offset(व्योम)
अणु
	वापस kernstart_virt_addr - KERNELBASE;
पूर्ण

#समावेश <यंत्र-generic/memory_model.h>
#पूर्ण_अगर /* __ASSEMBLY__ */
#समावेश <यंत्र/slice.h>

#पूर्ण_अगर /* _ASM_POWERPC_PAGE_H */
