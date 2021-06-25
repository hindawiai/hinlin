<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PGTABLE_64_DEFS_H
#घोषणा _ASM_X86_PGTABLE_64_DEFS_H

#समावेश <यंत्र/sparseस्मृति.स>

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/types.h>
#समावेश <यंत्र/kaslr.h>

/*
 * These are used to make use of C type-checking..
 */
प्रकार अचिन्हित दीर्घ	pteval_t;
प्रकार अचिन्हित दीर्घ	pmdval_t;
प्रकार अचिन्हित दीर्घ	pudval_t;
प्रकार अचिन्हित दीर्घ	p4dval_t;
प्रकार अचिन्हित दीर्घ	pgdval_t;
प्रकार अचिन्हित दीर्घ	pgprotval_t;

प्रकार काष्ठा अणु pteval_t pte; पूर्ण pte_t;

#अगर_घोषित CONFIG_X86_5LEVEL
बाह्य अचिन्हित पूर्णांक __pgtable_l5_enabled;

#अगर_घोषित USE_EARLY_PGTABLE_L5
/*
 * cpu_feature_enabled() is not available in early boot code.
 * Use variable instead.
 */
अटल अंतरभूत bool pgtable_l5_enabled(व्योम)
अणु
	वापस __pgtable_l5_enabled;
पूर्ण
#अन्यथा
#घोषणा pgtable_l5_enabled() cpu_feature_enabled(X86_FEATURE_LA57)
#पूर्ण_अगर /* USE_EARLY_PGTABLE_L5 */

#अन्यथा
#घोषणा pgtable_l5_enabled() 0
#पूर्ण_अगर /* CONFIG_X86_5LEVEL */

बाह्य अचिन्हित पूर्णांक pgdir_shअगरt;
बाह्य अचिन्हित पूर्णांक ptrs_per_p4d;

#पूर्ण_अगर	/* !__ASSEMBLY__ */

#घोषणा SHARED_KERNEL_PMD	0

#अगर_घोषित CONFIG_X86_5LEVEL

/*
 * PGसूची_SHIFT determines what a top-level page table entry can map
 */
#घोषणा PGसूची_SHIFT	pgdir_shअगरt
#घोषणा PTRS_PER_PGD	512

/*
 * 4th level page in 5-level paging हाल
 */
#घोषणा P4D_SHIFT		39
#घोषणा MAX_PTRS_PER_P4D	512
#घोषणा PTRS_PER_P4D		ptrs_per_p4d
#घोषणा P4D_SIZE		(_AC(1, UL) << P4D_SHIFT)
#घोषणा P4D_MASK		(~(P4D_SIZE - 1))

#घोषणा MAX_POSSIBLE_PHYSMEM_BITS	52

#अन्यथा /* CONFIG_X86_5LEVEL */

/*
 * PGसूची_SHIFT determines what a top-level page table entry can map
 */
#घोषणा PGसूची_SHIFT		39
#घोषणा PTRS_PER_PGD		512
#घोषणा MAX_PTRS_PER_P4D	1

#पूर्ण_अगर /* CONFIG_X86_5LEVEL */

/*
 * 3rd level page
 */
#घोषणा PUD_SHIFT	30
#घोषणा PTRS_PER_PUD	512

/*
 * PMD_SHIFT determines the size of the area a middle-level
 * page table can map
 */
#घोषणा PMD_SHIFT	21
#घोषणा PTRS_PER_PMD	512

/*
 * entries per page directory level
 */
#घोषणा PTRS_PER_PTE	512

#घोषणा PMD_SIZE	(_AC(1, UL) << PMD_SHIFT)
#घोषणा PMD_MASK	(~(PMD_SIZE - 1))
#घोषणा PUD_SIZE	(_AC(1, UL) << PUD_SHIFT)
#घोषणा PUD_MASK	(~(PUD_SIZE - 1))
#घोषणा PGसूची_SIZE	(_AC(1, UL) << PGसूची_SHIFT)
#घोषणा PGसूची_MASK	(~(PGसूची_SIZE - 1))

/*
 * See Documentation/x86/x86_64/mm.rst क्रम a description of the memory map.
 *
 * Be very careful vs. KASLR when changing anything here. The KASLR address
 * range must not overlap with anything except the KASAN shaकरोw area, which
 * is correct as KASAN disables KASLR.
 */
#घोषणा MAXMEM			(1UL << MAX_PHYSMEM_BITS)

#घोषणा GUARD_HOLE_PGD_ENTRY	-256UL
#घोषणा GUARD_HOLE_SIZE		(16UL << PGसूची_SHIFT)
#घोषणा GUARD_HOLE_BASE_ADDR	(GUARD_HOLE_PGD_ENTRY << PGसूची_SHIFT)
#घोषणा GUARD_HOLE_END_ADDR	(GUARD_HOLE_BASE_ADDR + GUARD_HOLE_SIZE)

#घोषणा LDT_PGD_ENTRY		-240UL
#घोषणा LDT_BASE_ADDR		(LDT_PGD_ENTRY << PGसूची_SHIFT)
#घोषणा LDT_END_ADDR		(LDT_BASE_ADDR + PGसूची_SIZE)

#घोषणा __VMALLOC_BASE_L4	0xffffc90000000000UL
#घोषणा __VMALLOC_BASE_L5 	0xffa0000000000000UL

#घोषणा VMALLOC_SIZE_TB_L4	32UL
#घोषणा VMALLOC_SIZE_TB_L5	12800UL

#घोषणा __VMEMMAP_BASE_L4	0xffffea0000000000UL
#घोषणा __VMEMMAP_BASE_L5	0xffd4000000000000UL

#अगर_घोषित CONFIG_DYNAMIC_MEMORY_LAYOUT
# define VMALLOC_START		vदो_स्मृति_base
# define VMALLOC_SIZE_TB	(pgtable_l5_enabled() ? VMALLOC_SIZE_TB_L5 : VMALLOC_SIZE_TB_L4)
# define VMEMMAP_START		vmemmap_base
#अन्यथा
# define VMALLOC_START		__VMALLOC_BASE_L4
# define VMALLOC_SIZE_TB	VMALLOC_SIZE_TB_L4
# define VMEMMAP_START		__VMEMMAP_BASE_L4
#पूर्ण_अगर /* CONFIG_DYNAMIC_MEMORY_LAYOUT */

#घोषणा VMALLOC_END		(VMALLOC_START + (VMALLOC_SIZE_TB << 40) - 1)

#घोषणा MODULES_VADDR		(__START_KERNEL_map + KERNEL_IMAGE_SIZE)
/* The module sections ends with the start of the fixmap */
#अगर_अघोषित CONFIG_DEBUG_KMAP_LOCAL_FORCE_MAP
# define MODULES_END		_AC(0xffffffffff000000, UL)
#अन्यथा
# define MODULES_END		_AC(0xfffffffffe000000, UL)
#पूर्ण_अगर
#घोषणा MODULES_LEN		(MODULES_END - MODULES_VADDR)

#घोषणा ESPFIX_PGD_ENTRY	_AC(-2, UL)
#घोषणा ESPFIX_BASE_ADDR	(ESPFIX_PGD_ENTRY << P4D_SHIFT)

#घोषणा CPU_ENTRY_AREA_PGD	_AC(-4, UL)
#घोषणा CPU_ENTRY_AREA_BASE	(CPU_ENTRY_AREA_PGD << P4D_SHIFT)

#घोषणा EFI_VA_START		( -4 * (_AC(1, UL) << 30))
#घोषणा EFI_VA_END		(-68 * (_AC(1, UL) << 30))

#घोषणा EARLY_DYNAMIC_PAGE_TABLES	64

#घोषणा PGD_KERNEL_START	((PAGE_SIZE / 2) / माप(pgd_t))

#पूर्ण_अगर /* _ASM_X86_PGTABLE_64_DEFS_H */
