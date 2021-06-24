<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OpenRISC idle.c
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * Modअगरications क्रम the OpenRISC architecture:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
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
#समावेश <linux/smp.h>
#समावेश <linux/memblock.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/blkdev.h>	/* क्रम initrd_* */
#समावेश <linux/pagemap.h>

#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/sections.h>

पूर्णांक mem_init_करोne;

DEFINE_PER_CPU(काष्ठा mmu_gather, mmu_gathers);

अटल व्योम __init zone_sizes_init(व्योम)
अणु
	अचिन्हित दीर्घ max_zone_pfn[MAX_NR_ZONES] = अणु 0 पूर्ण;

	/*
	 * We use only ZONE_NORMAL
	 */
	max_zone_pfn[ZONE_NORMAL] = max_low_pfn;

	मुक्त_area_init(max_zone_pfn);
पूर्ण

बाह्य स्थिर अक्षर _s_kernel_ro[], _e_kernel_ro[];

/*
 * Map all physical memory पूर्णांकo kernel's address space.
 *
 * This is explicitly coded क्रम two-level page tables, so अगर you need
 * something अन्यथा then this needs to change.
 */
अटल व्योम __init map_ram(व्योम)
अणु
	phys_addr_t start, end;
	अचिन्हित दीर्घ v, p, e;
	pgprot_t prot;
	pgd_t *pge;
	p4d_t *p4e;
	pud_t *pue;
	pmd_t *pme;
	pte_t *pte;
	u64 i;
	/* These mark extents of पढ़ो-only kernel pages...
	 * ...from vmlinux.lds.S
	 */

	v = PAGE_OFFSET;

	क्रम_each_mem_range(i, &start, &end) अणु
		p = (u32) start & PAGE_MASK;
		e = (u32) end;

		v = (u32) __va(p);
		pge = pgd_offset_k(v);

		जबतक (p < e) अणु
			पूर्णांक j;
			p4e = p4d_offset(pge, v);
			pue = pud_offset(p4e, v);
			pme = pmd_offset(pue, v);

			अगर ((u32) pue != (u32) pge || (u32) pme != (u32) pge) अणु
				panic("%s: OR1K kernel hardcoded for "
				      "two-level page tables",
				     __func__);
			पूर्ण

			/* Alloc one page क्रम holding PTE's... */
			pte = memblock_alloc_raw(PAGE_SIZE, PAGE_SIZE);
			अगर (!pte)
				panic("%s: Failed to allocate page for PTEs\n",
				      __func__);
			set_pmd(pme, __pmd(_KERNPG_TABLE + __pa(pte)));

			/* Fill the newly allocated page with PTE'S */
			क्रम (j = 0; p < e && j < PTRS_PER_PTE;
			     v += PAGE_SIZE, p += PAGE_SIZE, j++, pte++) अणु
				अगर (v >= (u32) _e_kernel_ro ||
				    v < (u32) _s_kernel_ro)
					prot = PAGE_KERNEL;
				अन्यथा
					prot = PAGE_KERNEL_RO;

				set_pte(pte, mk_pte_phys(p, prot));
			पूर्ण

			pge++;
		पूर्ण

		prपूर्णांकk(KERN_INFO "%s: Memory: 0x%x-0x%x\n", __func__,
		       start, end);
	पूर्ण
पूर्ण

व्योम __init paging_init(व्योम)
अणु
	बाह्य व्योम tlb_init(व्योम);

	पूर्णांक i;

	prपूर्णांकk(KERN_INFO "Setting up paging and PTEs.\n");

	/* clear out the init_mm.pgd that will contain the kernel's mappings */

	क्रम (i = 0; i < PTRS_PER_PGD; i++)
		swapper_pg_dir[i] = __pgd(0);

	/* make sure the current pgd table poपूर्णांकs to something sane
	 * (even अगर it is most probably not used until the next
	 *  चयन_mm)
	 */
	current_pgd[smp_processor_id()] = init_mm.pgd;

	map_ram();

	zone_sizes_init();

	/* self modअगरying code ;) */
	/* Since the old TLB miss handler has been running up until now,
	 * the kernel pages are still all RW, so we can still modअगरy the
	 * text directly... after this change and a TLB flush, the kernel
	 * pages will become RO.
	 */
	अणु
		बाह्य अचिन्हित दीर्घ dtlb_miss_handler;
		बाह्य अचिन्हित दीर्घ itlb_miss_handler;

		अचिन्हित दीर्घ *dtlb_vector = __va(0x900);
		अचिन्हित दीर्घ *itlb_vector = __va(0xa00);

		prपूर्णांकk(KERN_INFO "itlb_miss_handler %p\n", &itlb_miss_handler);
		*itlb_vector = ((अचिन्हित दीर्घ)&itlb_miss_handler -
				(अचिन्हित दीर्घ)itlb_vector) >> 2;

		/* Soft ordering स्थिरraपूर्णांक to ensure that dtlb_vector is
		 * the last thing updated
		 */
		barrier();

		prपूर्णांकk(KERN_INFO "dtlb_miss_handler %p\n", &dtlb_miss_handler);
		*dtlb_vector = ((अचिन्हित दीर्घ)&dtlb_miss_handler -
				(अचिन्हित दीर्घ)dtlb_vector) >> 2;

	पूर्ण

	/* Soft ordering स्थिरraपूर्णांक to ensure that cache invalidation and
	 * TLB flush really happen _after_ code has been modअगरied.
	 */
	barrier();

	/* Invalidate inकाष्ठाion caches after code modअगरication */
	mtspr(SPR_ICBIR, 0x900);
	mtspr(SPR_ICBIR, 0xa00);

	/* New TLB miss handlers and kernel page tables are in now place.
	 * Make sure that page flags get updated क्रम all pages in TLB by
	 * flushing the TLB and क्रमcing all TLB entries to be recreated
	 * from their page table flags.
	 */
	flush_tlb_all();
पूर्ण

/* References to section boundaries */

व्योम __init mem_init(व्योम)
अणु
	BUG_ON(!mem_map);

	max_mapnr = max_low_pfn;
	high_memory = (व्योम *)__va(max_low_pfn * PAGE_SIZE);

	/* clear the zero-page */
	स_रखो((व्योम *)empty_zero_page, 0, PAGE_SIZE);

	/* this will put all low memory onto the मुक्तlists */
	memblock_मुक्त_all();

	prपूर्णांकk("mem_init_done ...........................................\n");
	mem_init_करोne = 1;
	वापस;
पूर्ण
