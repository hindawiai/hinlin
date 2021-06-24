<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/m68k/mm/init.c
 *
 *  Copyright (C) 1995  Hamish Macकरोnald
 *
 *  Contains common initialization routines, specअगरic init code moved
 *  to motorola.c and sun3mmu.c
 */

#समावेश <linux/module.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/setup.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/पन.स>
#अगर_घोषित CONFIG_ATARI
#समावेश <यंत्र/atari_stram.h>
#पूर्ण_अगर
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/tlb.h>

/*
 * ZERO_PAGE is a special page that is used क्रम zero-initialized
 * data and COW.
 */
व्योम *empty_zero_page;
EXPORT_SYMBOL(empty_zero_page);

#अगर_घोषित CONFIG_MMU

पूर्णांक m68k_virt_to_node_shअगरt;

#अगर_घोषित CONFIG_DISCONTIGMEM
pg_data_t pg_data_map[MAX_NUMNODES];
EXPORT_SYMBOL(pg_data_map);

pg_data_t *pg_data_table[65];
EXPORT_SYMBOL(pg_data_table);
#पूर्ण_अगर

व्योम __init m68k_setup_node(पूर्णांक node)
अणु
#अगर_घोषित CONFIG_DISCONTIGMEM
	काष्ठा m68k_mem_info *info = m68k_memory + node;
	पूर्णांक i, end;

	i = (अचिन्हित दीर्घ)phys_to_virt(info->addr) >> __virt_to_node_shअगरt();
	end = (अचिन्हित दीर्घ)phys_to_virt(info->addr + info->size - 1) >> __virt_to_node_shअगरt();
	क्रम (; i <= end; i++) अणु
		अगर (pg_data_table[i])
			pr_warn("overlap at %u for chunk %u\n", i, node);
		pg_data_table[i] = pg_data_map + node;
	पूर्ण
#पूर्ण_अगर
	node_set_online(node);
पूर्ण

#अन्यथा /* CONFIG_MMU */

/*
 * paging_init() जारीs the भव memory environment setup which
 * was begun by the code in arch/head.S.
 * The parameters are poपूर्णांकers to where to stick the starting and ending
 * addresses of available kernel भव memory.
 */
व्योम __init paging_init(व्योम)
अणु
	/*
	 * Make sure start_mem is page aligned, otherwise booपंचांगem and
	 * page_alloc get dअगरferent views of the world.
	 */
	अचिन्हित दीर्घ end_mem = memory_end & PAGE_MASK;
	अचिन्हित दीर्घ max_zone_pfn[MAX_NR_ZONES] = अणु 0, पूर्ण;

	high_memory = (व्योम *) end_mem;

	empty_zero_page = memblock_alloc(PAGE_SIZE, PAGE_SIZE);
	अगर (!empty_zero_page)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, PAGE_SIZE, PAGE_SIZE);

	/*
	 * Set up SFC/DFC रेजिस्टरs (user data space).
	 */
	set_fs (USER_DS);

	max_zone_pfn[ZONE_DMA] = end_mem >> PAGE_SHIFT;
	मुक्त_area_init(max_zone_pfn);
पूर्ण

#पूर्ण_अगर /* CONFIG_MMU */

व्योम मुक्त_iniपंचांगem(व्योम)
अणु
#अगर_अघोषित CONFIG_MMU_SUN3
	मुक्त_iniपंचांगem_शेष(-1);
#पूर्ण_अगर /* CONFIG_MMU_SUN3 */
पूर्ण

#अगर defined(CONFIG_MMU) && !defined(CONFIG_COLDFIRE)
#घोषणा VECTORS	&vectors[0]
#अन्यथा
#घोषणा VECTORS	_ramvec
#पूर्ण_अगर

अटल अंतरभूत व्योम init_poपूर्णांकer_tables(व्योम)
अणु
#अगर defined(CONFIG_MMU) && !defined(CONFIG_SUN3) && !defined(CONFIG_COLDFIRE)
	पूर्णांक i, j;

	/* insert poपूर्णांकer tables allocated so far पूर्णांकo the tablelist */
	init_poपूर्णांकer_table(kernel_pg_dir, TABLE_PGD);
	क्रम (i = 0; i < PTRS_PER_PGD; i++) अणु
		pud_t *pud = (pud_t *)&kernel_pg_dir[i];
		pmd_t *pmd_dir;

		अगर (!pud_present(*pud))
			जारी;

		pmd_dir = (pmd_t *)pgd_page_vaddr(kernel_pg_dir[i]);
		init_poपूर्णांकer_table(pmd_dir, TABLE_PMD);

		क्रम (j = 0; j < PTRS_PER_PMD; j++) अणु
			pmd_t *pmd = &pmd_dir[j];
			pte_t *pte_dir;

			अगर (!pmd_present(*pmd))
				जारी;

			pte_dir = (pte_t *)pmd_page_vaddr(*pmd);
			init_poपूर्णांकer_table(pte_dir, TABLE_PTE);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम __init mem_init(व्योम)
अणु
	/* this will put all memory onto the मुक्तlists */
	memblock_मुक्त_all();
	init_poपूर्णांकer_tables();
पूर्ण
