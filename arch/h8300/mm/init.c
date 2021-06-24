<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/h8300/mm/init.c
 *
 *  Copyright (C) 1998  D. Jeff Dionne <jeff@lineo.ca>,
 *                      Kenneth Albanowski <kjahds@kjahds.com>,
 *  Copyright (C) 2000  Lineo, Inc.  (www.lineo.com)
 *
 *  Based on:
 *
 *  linux/arch/m68knommu/mm/init.c
 *  linux/arch/m68k/mm/init.c
 *
 *  Copyright (C) 1995  Hamish Macकरोnald
 *
 *  JAN/1999 -- hacked to support ColdFire (gerg@snapgear.com)
 *  DEC/2000 -- linux 2.4 support <davidm@snapgear.com>
 */

#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/init.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/memblock.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/sections.h>

/*
 * ZERO_PAGE is a special page that is used क्रम zero-initialized
 * data and COW.
 */
अचिन्हित दीर्घ empty_zero_page;

/*
 * paging_init() जारीs the भव memory environment setup which
 * was begun by the code in arch/head.S.
 * The parameters are poपूर्णांकers to where to stick the starting and ending
 * addresses of available kernel भव memory.
 */
व्योम __init paging_init(व्योम)
अणु
	/*
	 * Make sure start_mem is page aligned,  otherwise booपंचांगem and
	 * page_alloc get dअगरferent views og the world.
	 */
	अचिन्हित दीर्घ start_mem = PAGE_ALIGN(memory_start);
	अचिन्हित दीर्घ end_mem   = memory_end & PAGE_MASK;

	pr_debug("start_mem is %#lx\nvirtual_end is %#lx\n",
		 start_mem, end_mem);

	/*
	 * Initialize the bad page table and bad page to poपूर्णांक
	 * to a couple of allocated pages.
	 */
	empty_zero_page = (अचिन्हित दीर्घ)memblock_alloc(PAGE_SIZE, PAGE_SIZE);
	अगर (!empty_zero_page)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, PAGE_SIZE, PAGE_SIZE);

	/*
	 * Set up SFC/DFC रेजिस्टरs (user data space).
	 */
	set_fs(USER_DS);

	pr_debug("before free_area_init\n");

	pr_debug("free_area_init -> start_mem is %#lx\nvirtual_end is %#lx\n",
		 start_mem, end_mem);

	अणु
		अचिन्हित दीर्घ max_zone_pfn[MAX_NR_ZONES] = अणु0, पूर्ण;

		max_zone_pfn[ZONE_NORMAL] = end_mem >> PAGE_SHIFT;
		मुक्त_area_init(max_zone_pfn);
	पूर्ण
पूर्ण

व्योम __init mem_init(व्योम)
अणु
	pr_devel("Mem_init: start=%lx, end=%lx\n", memory_start, memory_end);

	high_memory = (व्योम *) (memory_end & PAGE_MASK);
	max_mapnr = MAP_NR(high_memory);

	/* this will put all low memory onto the मुक्तlists */
	memblock_मुक्त_all();
पूर्ण
