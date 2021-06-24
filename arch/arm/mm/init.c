<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mm/init.c
 *
 *  Copyright (C) 1995-2005 Russell King
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/swap.h>
#समावेश <linux/init.h>
#समावेश <linux/mman.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task.h>
#समावेश <linux/export.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/initrd.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/gfp.h>
#समावेश <linux/memblock.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/sizes.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/swiotlb.h>

#समावेश <यंत्र/cp15.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/memblock.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/ptdump.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "mm.h"

#अगर_घोषित CONFIG_CPU_CP15_MMU
अचिन्हित दीर्घ __init __clear_cr(अचिन्हित दीर्घ mask)
अणु
	cr_alignment = cr_alignment & ~mask;
	वापस cr_alignment;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_BLK_DEV_INITRD
अटल पूर्णांक __init parse_tag_initrd(स्थिर काष्ठा tag *tag)
अणु
	pr_warn("ATAG_INITRD is deprecated; "
		"please update your bootloader.\n");
	phys_initrd_start = __virt_to_phys(tag->u.initrd.start);
	phys_initrd_size = tag->u.initrd.size;
	वापस 0;
पूर्ण

__tagtable(ATAG_INITRD, parse_tag_initrd);

अटल पूर्णांक __init parse_tag_initrd2(स्थिर काष्ठा tag *tag)
अणु
	phys_initrd_start = tag->u.initrd.start;
	phys_initrd_size = tag->u.initrd.size;
	वापस 0;
पूर्ण

__tagtable(ATAG_INITRD2, parse_tag_initrd2);
#पूर्ण_अगर

अटल व्योम __init find_limits(अचिन्हित दीर्घ *min, अचिन्हित दीर्घ *max_low,
			       अचिन्हित दीर्घ *max_high)
अणु
	*max_low = PFN_DOWN(memblock_get_current_limit());
	*min = PFN_UP(memblock_start_of_DRAM());
	*max_high = PFN_DOWN(memblock_end_of_DRAM());
पूर्ण

#अगर_घोषित CONFIG_ZONE_DMA

phys_addr_t arm_dma_zone_size __पढ़ो_mostly;
EXPORT_SYMBOL(arm_dma_zone_size);

/*
 * The DMA mask corresponding to the maximum bus address allocatable
 * using GFP_DMA.  The शेष here places no restriction on DMA
 * allocations.  This must be the smallest DMA mask in the प्रणाली,
 * so a successful GFP_DMA allocation will always satisfy this.
 */
phys_addr_t arm_dma_limit;
अचिन्हित दीर्घ arm_dma_pfn_limit;
#पूर्ण_अगर

व्योम __init setup_dma_zone(स्थिर काष्ठा machine_desc *mdesc)
अणु
#अगर_घोषित CONFIG_ZONE_DMA
	अगर (mdesc->dma_zone_size) अणु
		arm_dma_zone_size = mdesc->dma_zone_size;
		arm_dma_limit = PHYS_OFFSET + arm_dma_zone_size - 1;
	पूर्ण अन्यथा
		arm_dma_limit = 0xffffffff;
	arm_dma_pfn_limit = arm_dma_limit >> PAGE_SHIFT;
#पूर्ण_अगर
पूर्ण

अटल व्योम __init zone_sizes_init(अचिन्हित दीर्घ min, अचिन्हित दीर्घ max_low,
	अचिन्हित दीर्घ max_high)
अणु
	अचिन्हित दीर्घ max_zone_pfn[MAX_NR_ZONES] = अणु 0 पूर्ण;

#अगर_घोषित CONFIG_ZONE_DMA
	max_zone_pfn[ZONE_DMA] = min(arm_dma_pfn_limit, max_low);
#पूर्ण_अगर
	max_zone_pfn[ZONE_NORMAL] = max_low;
#अगर_घोषित CONFIG_HIGHMEM
	max_zone_pfn[ZONE_HIGHMEM] = max_high;
#पूर्ण_अगर
	मुक्त_area_init(max_zone_pfn);
पूर्ण

#अगर_घोषित CONFIG_HAVE_ARCH_PFN_VALID
पूर्णांक pfn_valid(अचिन्हित दीर्घ pfn)
अणु
	phys_addr_t addr = __pfn_to_phys(pfn);

	अगर (__phys_to_pfn(addr) != pfn)
		वापस 0;

	वापस memblock_is_map_memory(addr);
पूर्ण
EXPORT_SYMBOL(pfn_valid);
#पूर्ण_अगर

अटल bool arm_memblock_steal_permitted = true;

phys_addr_t __init arm_memblock_steal(phys_addr_t size, phys_addr_t align)
अणु
	phys_addr_t phys;

	BUG_ON(!arm_memblock_steal_permitted);

	phys = memblock_phys_alloc(size, align);
	अगर (!phys)
		panic("Failed to steal %pa bytes at %pS\n",
		      &size, (व्योम *)_RET_IP_);

	memblock_मुक्त(phys, size);
	memblock_हटाओ(phys, size);

	वापस phys;
पूर्ण

अटल व्योम __init arm_initrd_init(व्योम)
अणु
#अगर_घोषित CONFIG_BLK_DEV_INITRD
	phys_addr_t start;
	अचिन्हित दीर्घ size;

	initrd_start = initrd_end = 0;

	अगर (!phys_initrd_size)
		वापस;

	/*
	 * Round the memory region to page boundaries as per मुक्त_initrd_mem()
	 * This allows us to detect whether the pages overlapping the initrd
	 * are in use, but more importantly, reserves the entire set of pages
	 * as we करोn't want these pages allocated क्रम other purposes.
	 */
	start = round_करोwn(phys_initrd_start, PAGE_SIZE);
	size = phys_initrd_size + (phys_initrd_start - start);
	size = round_up(size, PAGE_SIZE);

	अगर (!memblock_is_region_memory(start, size)) अणु
		pr_err("INITRD: 0x%08llx+0x%08lx is not a memory region - disabling initrd\n",
		       (u64)start, size);
		वापस;
	पूर्ण

	अगर (memblock_is_region_reserved(start, size)) अणु
		pr_err("INITRD: 0x%08llx+0x%08lx overlaps in-use memory region - disabling initrd\n",
		       (u64)start, size);
		वापस;
	पूर्ण

	memblock_reserve(start, size);

	/* Now convert initrd to भव addresses */
	initrd_start = __phys_to_virt(phys_initrd_start);
	initrd_end = initrd_start + phys_initrd_size;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_CPU_ICACHE_MISMATCH_WORKAROUND
व्योम check_cpu_icache_size(पूर्णांक cpuid)
अणु
	u32 size, ctr;

	यंत्र("mrc p15, 0, %0, c0, c0, 1" : "=r" (ctr));

	size = 1 << ((ctr & 0xf) + 2);
	अगर (cpuid != 0 && icache_size != size)
		pr_info("CPU%u: detected I-Cache line size mismatch, workaround enabled\n",
			cpuid);
	अगर (icache_size > size)
		icache_size = size;
पूर्ण
#पूर्ण_अगर

व्योम __init arm_memblock_init(स्थिर काष्ठा machine_desc *mdesc)
अणु
	/* Register the kernel text, kernel data and initrd with memblock. */
	memblock_reserve(__pa(KERNEL_START), KERNEL_END - KERNEL_START);

	arm_initrd_init();

	arm_mm_memblock_reserve();

	/* reserve any platक्रमm specअगरic memblock areas */
	अगर (mdesc->reserve)
		mdesc->reserve();

	early_init_fdt_scan_reserved_mem();

	/* reserve memory क्रम DMA contiguous allocations */
	dma_contiguous_reserve(arm_dma_limit);

	arm_memblock_steal_permitted = false;
	memblock_dump_all();
पूर्ण

व्योम __init booपंचांगem_init(व्योम)
अणु
	memblock_allow_resize();

	find_limits(&min_low_pfn, &max_low_pfn, &max_pfn);

	early_memtest((phys_addr_t)min_low_pfn << PAGE_SHIFT,
		      (phys_addr_t)max_low_pfn << PAGE_SHIFT);

	/*
	 * sparse_init() tries to allocate memory from memblock, so must be
	 * करोne after the fixed reservations
	 */
	sparse_init();

	/*
	 * Now मुक्त the memory - मुक्त_area_init needs
	 * the sparse mem_map arrays initialized by sparse_init()
	 * क्रम memmap_init_zone(), otherwise all PFNs are invalid.
	 */
	zone_sizes_init(min_low_pfn, max_low_pfn, max_pfn);
पूर्ण

/*
 * Poison init memory with an undefined inकाष्ठाion (ARM) or a branch to an
 * undefined inकाष्ठाion (Thumb).
 */
अटल अंतरभूत व्योम poison_init_mem(व्योम *s, माप_प्रकार count)
अणु
	u32 *p = (u32 *)s;
	क्रम (; count != 0; count -= 4)
		*p++ = 0xe7fddef0;
पूर्ण

अटल व्योम __init मुक्त_highpages(व्योम)
अणु
#अगर_घोषित CONFIG_HIGHMEM
	अचिन्हित दीर्घ max_low = max_low_pfn;
	phys_addr_t range_start, range_end;
	u64 i;

	/* set highmem page मुक्त */
	क्रम_each_मुक्त_mem_range(i, NUMA_NO_NODE, MEMBLOCK_NONE,
				&range_start, &range_end, शून्य) अणु
		अचिन्हित दीर्घ start = PFN_UP(range_start);
		अचिन्हित दीर्घ end = PFN_DOWN(range_end);

		/* Ignore complete lowmem entries */
		अगर (end <= max_low)
			जारी;

		/* Truncate partial highmem entries */
		अगर (start < max_low)
			start = max_low;

		क्रम (; start < end; start++)
			मुक्त_highmem_page(pfn_to_page(start));
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * mem_init() marks the मुक्त areas in the mem_map and tells us how much
 * memory is मुक्त.  This is करोne after various parts of the प्रणाली have
 * claimed their memory after the kernel image.
 */
व्योम __init mem_init(व्योम)
अणु
#अगर_घोषित CONFIG_ARM_LPAE
	अगर (swiotlb_क्रमce == SWIOTLB_FORCE ||
	    max_pfn > arm_dma_pfn_limit)
		swiotlb_init(1);
	अन्यथा
		swiotlb_क्रमce = SWIOTLB_NO_FORCE;
#पूर्ण_अगर

	set_max_mapnr(pfn_to_page(max_pfn) - mem_map);

	/* this will put all unused low memory onto the मुक्तlists */
	memblock_मुक्त_all();

#अगर_घोषित CONFIG_SA1111
	/* now that our DMA memory is actually so designated, we can मुक्त it */
	मुक्त_reserved_area(__va(PHYS_OFFSET), swapper_pg_dir, -1, शून्य);
#पूर्ण_अगर

	मुक्त_highpages();

	/*
	 * Check boundaries twice: Some fundamental inconsistencies can
	 * be detected at build समय alपढ़ोy.
	 */
#अगर_घोषित CONFIG_MMU
	BUILD_BUG_ON(TASK_SIZE				> MODULES_VADDR);
	BUG_ON(TASK_SIZE 				> MODULES_VADDR);
#पूर्ण_अगर

#अगर_घोषित CONFIG_HIGHMEM
	BUILD_BUG_ON(PKMAP_BASE + LAST_PKMAP * PAGE_SIZE > PAGE_OFFSET);
	BUG_ON(PKMAP_BASE + LAST_PKMAP * PAGE_SIZE	> PAGE_OFFSET);
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_STRICT_KERNEL_RWX
काष्ठा section_perm अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
	pmdval_t mask;
	pmdval_t prot;
	pmdval_t clear;
पूर्ण;

/* First section-aligned location at or after __start_rodata. */
बाह्य अक्षर __start_rodata_section_aligned[];

अटल काष्ठा section_perm nx_perms[] = अणु
	/* Make pages tables, etc beक्रमe _stext RW (set NX). */
	अणु
		.name	= "pre-text NX",
		.start	= PAGE_OFFSET,
		.end	= (अचिन्हित दीर्घ)_stext,
		.mask	= ~PMD_SECT_XN,
		.prot	= PMD_SECT_XN,
	पूर्ण,
	/* Make init RW (set NX). */
	अणु
		.name	= "init NX",
		.start	= (अचिन्हित दीर्घ)__init_begin,
		.end	= (अचिन्हित दीर्घ)_sdata,
		.mask	= ~PMD_SECT_XN,
		.prot	= PMD_SECT_XN,
	पूर्ण,
	/* Make rodata NX (set RO in ro_perms below). */
	अणु
		.name	= "rodata NX",
		.start  = (अचिन्हित दीर्घ)__start_rodata_section_aligned,
		.end    = (अचिन्हित दीर्घ)__init_begin,
		.mask   = ~PMD_SECT_XN,
		.prot   = PMD_SECT_XN,
	पूर्ण,
पूर्ण;

अटल काष्ठा section_perm ro_perms[] = अणु
	/* Make kernel code and rodata RX (set RO). */
	अणु
		.name	= "text/rodata RO",
		.start  = (अचिन्हित दीर्घ)_stext,
		.end    = (अचिन्हित दीर्घ)__init_begin,
#अगर_घोषित CONFIG_ARM_LPAE
		.mask   = ~(L_PMD_SECT_RDONLY | PMD_SECT_AP2),
		.prot   = L_PMD_SECT_RDONLY | PMD_SECT_AP2,
#अन्यथा
		.mask   = ~(PMD_SECT_APX | PMD_SECT_AP_WRITE),
		.prot   = PMD_SECT_APX | PMD_SECT_AP_WRITE,
		.clear  = PMD_SECT_AP_WRITE,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

/*
 * Updates section permissions only क्रम the current mm (sections are
 * copied पूर्णांकo each mm). During startup, this is the init_mm. Is only
 * safe to be called with preemption disabled, as under stop_machine().
 */
अटल अंतरभूत व्योम section_update(अचिन्हित दीर्घ addr, pmdval_t mask,
				  pmdval_t prot, काष्ठा mm_काष्ठा *mm)
अणु
	pmd_t *pmd;

	pmd = pmd_offset(pud_offset(p4d_offset(pgd_offset(mm, addr), addr), addr), addr);

#अगर_घोषित CONFIG_ARM_LPAE
	pmd[0] = __pmd((pmd_val(pmd[0]) & mask) | prot);
#अन्यथा
	अगर (addr & SECTION_SIZE)
		pmd[1] = __pmd((pmd_val(pmd[1]) & mask) | prot);
	अन्यथा
		pmd[0] = __pmd((pmd_val(pmd[0]) & mask) | prot);
#पूर्ण_अगर
	flush_pmd_entry(pmd);
	local_flush_tlb_kernel_range(addr, addr + SECTION_SIZE);
पूर्ण

/* Make sure extended page tables are in use. */
अटल अंतरभूत bool arch_has_strict_perms(व्योम)
अणु
	अगर (cpu_architecture() < CPU_ARCH_ARMv6)
		वापस false;

	वापस !!(get_cr() & CR_XP);
पूर्ण

अटल व्योम set_section_perms(काष्ठा section_perm *perms, पूर्णांक n, bool set,
			      काष्ठा mm_काष्ठा *mm)
अणु
	माप_प्रकार i;
	अचिन्हित दीर्घ addr;

	अगर (!arch_has_strict_perms())
		वापस;

	क्रम (i = 0; i < n; i++) अणु
		अगर (!IS_ALIGNED(perms[i].start, SECTION_SIZE) ||
		    !IS_ALIGNED(perms[i].end, SECTION_SIZE)) अणु
			pr_err("BUG: %s section %lx-%lx not aligned to %lx\n",
				perms[i].name, perms[i].start, perms[i].end,
				SECTION_SIZE);
			जारी;
		पूर्ण

		क्रम (addr = perms[i].start;
		     addr < perms[i].end;
		     addr += SECTION_SIZE)
			section_update(addr, perms[i].mask,
				set ? perms[i].prot : perms[i].clear, mm);
	पूर्ण

पूर्ण

/**
 * update_sections_early पूर्णांकended to be called only through stop_machine
 * framework and executed by only one CPU जबतक all other CPUs will spin and
 * रुको, so no locking is required in this function.
 */
अटल व्योम update_sections_early(काष्ठा section_perm perms[], पूर्णांक n)
अणु
	काष्ठा task_काष्ठा *t, *s;

	क्रम_each_process(t) अणु
		अगर (t->flags & PF_KTHREAD)
			जारी;
		क्रम_each_thपढ़ो(t, s)
			अगर (s->mm)
				set_section_perms(perms, n, true, s->mm);
	पूर्ण
	set_section_perms(perms, n, true, current->active_mm);
	set_section_perms(perms, n, true, &init_mm);
पूर्ण

अटल पूर्णांक __fix_kernmem_perms(व्योम *unused)
अणु
	update_sections_early(nx_perms, ARRAY_SIZE(nx_perms));
	वापस 0;
पूर्ण

अटल व्योम fix_kernmem_perms(व्योम)
अणु
	stop_machine(__fix_kernmem_perms, शून्य, शून्य);
पूर्ण

अटल पूर्णांक __mark_rodata_ro(व्योम *unused)
अणु
	update_sections_early(ro_perms, ARRAY_SIZE(ro_perms));
	वापस 0;
पूर्ण

व्योम mark_rodata_ro(व्योम)
अणु
	stop_machine(__mark_rodata_ro, शून्य, शून्य);
	debug_checkwx();
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम fix_kernmem_perms(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_STRICT_KERNEL_RWX */

व्योम मुक्त_iniपंचांगem(व्योम)
अणु
	fix_kernmem_perms();

	poison_init_mem(__init_begin, __init_end - __init_begin);
	अगर (!machine_is_पूर्णांकegrator() && !machine_is_cपूर्णांकegrator())
		मुक्त_iniपंचांगem_शेष(-1);
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_INITRD
व्योम मुक्त_initrd_mem(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (start == initrd_start)
		start = round_करोwn(start, PAGE_SIZE);
	अगर (end == initrd_end)
		end = round_up(end, PAGE_SIZE);

	poison_init_mem((व्योम *)start, PAGE_ALIGN(end) - start);
	मुक्त_reserved_area((व्योम *)start, (व्योम *)end, -1, "initrd");
पूर्ण
#पूर्ण_अगर
