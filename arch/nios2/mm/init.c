<शैली गुरु>
/*
 * Copyright (C) 2013 Altera Corporation
 * Copyright (C) 2010 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2009 Wind River Systems Inc
 *   Implemented by fredrik.markstrom@gmail.com and ivarholmqvist@gmail.com
 * Copyright (C) 2004 Microtronix Datacom Ltd
 *
 * based on arch/m68k/mm/init.c
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
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
#समावेश <linux/init.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/memblock.h>
#समावेश <linux/slab.h>
#समावेश <linux/binfmts.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/cpuinfo.h>
#समावेश <यंत्र/processor.h>

pgd_t *pgd_current;

/*
 * paging_init() जारीs the भव memory environment setup which
 * was begun by the code in arch/head.S.
 * The parameters are poपूर्णांकers to where to stick the starting and ending
 * addresses of available kernel भव memory.
 */
व्योम __init paging_init(व्योम)
अणु
	अचिन्हित दीर्घ max_zone_pfn[MAX_NR_ZONES] = अणु 0 पूर्ण;

	pagetable_init();
	pgd_current = swapper_pg_dir;

	max_zone_pfn[ZONE_NORMAL] = max_mapnr;

	/* pass the memory from the booपंचांगem allocator to the मुख्य allocator */
	मुक्त_area_init(max_zone_pfn);

	flush_dcache_range((अचिन्हित दीर्घ)empty_zero_page,
			(अचिन्हित दीर्घ)empty_zero_page + PAGE_SIZE);
पूर्ण

व्योम __init mem_init(व्योम)
अणु
	अचिन्हित दीर्घ end_mem   = memory_end; /* this must not include
						kernel stack at top */

	pr_debug("mem_init: start=%lx, end=%lx\n", memory_start, memory_end);

	end_mem &= PAGE_MASK;
	high_memory = __va(end_mem);

	/* this will put all memory onto the मुक्तlists */
	memblock_मुक्त_all();
पूर्ण

व्योम __init mmu_init(व्योम)
अणु
	flush_tlb_all();
पूर्ण

#घोषणा __page_aligned(order) __aligned(PAGE_SIZE << (order))
pgd_t swapper_pg_dir[PTRS_PER_PGD] __page_aligned(PGD_ORDER);
pte_t invalid_pte_table[PTRS_PER_PTE] __page_aligned(PTE_ORDER);
अटल काष्ठा page *kuser_page[1];

अटल पूर्णांक alloc_kuser_page(व्योम)
अणु
	बाह्य अक्षर __kuser_helper_start[], __kuser_helper_end[];
	पूर्णांक kuser_sz = __kuser_helper_end - __kuser_helper_start;
	अचिन्हित दीर्घ vpage;

	vpage = get_zeroed_page(GFP_ATOMIC);
	अगर (!vpage)
		वापस -ENOMEM;

	/* Copy kuser helpers */
	स_नकल((व्योम *)vpage, __kuser_helper_start, kuser_sz);

	flush_icache_range(vpage, vpage + KUSER_SIZE);
	kuser_page[0] = virt_to_page(vpage);

	वापस 0;
पूर्ण
arch_initcall(alloc_kuser_page);

पूर्णांक arch_setup_additional_pages(काष्ठा linux_binprm *bprm, पूर्णांक uses_पूर्णांकerp)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	पूर्णांक ret;

	mmap_ग_लिखो_lock(mm);

	/* Map kuser helpers to user space address */
	ret = install_special_mapping(mm, KUSER_BASE, KUSER_SIZE,
				      VM_READ | VM_EXEC | VM_MAYREAD |
				      VM_MAYEXEC, kuser_page);

	mmap_ग_लिखो_unlock(mm);

	वापस ret;
पूर्ण

स्थिर अक्षर *arch_vma_name(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस (vma->vm_start == KUSER_BASE) ? "[kuser]" : शून्य;
पूर्ण
