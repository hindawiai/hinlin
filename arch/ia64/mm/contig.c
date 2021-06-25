<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1998-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *	Stephane Eranian <eranian@hpl.hp.com>
 * Copyright (C) 2000, Rohit Seth <rohit.seth@पूर्णांकel.com>
 * Copyright (C) 1999 VA Linux Systems
 * Copyright (C) 1999 Walt Drummond <drummond@valinux.com>
 * Copyright (C) 2003 Silicon Graphics, Inc. All rights reserved.
 *
 * Routines used by ia64 machines with contiguous (or भवly contiguous)
 * memory.
 */
#समावेश <linux/efi.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mm.h>
#समावेश <linux/nmi.h>
#समावेश <linux/swap.h>
#समावेश <linux/sizes.h>

#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/meminit.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/mca.h>

/* physical address where the booपंचांगem map is located */
अचिन्हित दीर्घ booपंचांगap_start;

#अगर_घोषित CONFIG_SMP
अटल व्योम *cpu_data;
/**
 * per_cpu_init - setup per-cpu variables
 *
 * Allocate and setup per-cpu data areas.
 */
व्योम *per_cpu_init(व्योम)
अणु
	अटल bool first_समय = true;
	व्योम *cpu0_data = __cpu0_per_cpu;
	अचिन्हित पूर्णांक cpu;

	अगर (!first_समय)
		जाओ skip;
	first_समय = false;

	/*
	 * get_मुक्त_pages() cannot be used beक्रमe cpu_init() करोne.
	 * BSP allocates PERCPU_PAGE_SIZE bytes क्रम all possible CPUs
	 * to aव्योम that AP calls get_zeroed_page().
	 */
	क्रम_each_possible_cpu(cpu) अणु
		व्योम *src = cpu == 0 ? cpu0_data : __phys_per_cpu_start;

		स_नकल(cpu_data, src, __per_cpu_end - __per_cpu_start);
		__per_cpu_offset[cpu] = (अक्षर *)cpu_data - __per_cpu_start;
		per_cpu(local_per_cpu_offset, cpu) = __per_cpu_offset[cpu];

		/*
		 * percpu area क्रम cpu0 is moved from the __init area
		 * which is setup by head.S and used till this poपूर्णांक.
		 * Update ar.k3.  This move is ensures that percpu
		 * area क्रम cpu0 is on the correct node and its
		 * भव address isn't insanely far from other
		 * percpu areas which is important क्रम congruent
		 * percpu allocator.
		 */
		अगर (cpu == 0)
			ia64_set_kr(IA64_KR_PER_CPU_DATA, __pa(cpu_data) -
				    (अचिन्हित दीर्घ)__per_cpu_start);

		cpu_data += PERCPU_PAGE_SIZE;
	पूर्ण
skip:
	वापस __per_cpu_start + __per_cpu_offset[smp_processor_id()];
पूर्ण

अटल अंतरभूत व्योम
alloc_per_cpu_data(व्योम)
अणु
	माप_प्रकार size = PERCPU_PAGE_SIZE * num_possible_cpus();

	cpu_data = memblock_alloc_from(size, PERCPU_PAGE_SIZE,
				       __pa(MAX_DMA_ADDRESS));
	अगर (!cpu_data)
		panic("%s: Failed to allocate %lu bytes align=%lx from=%lx\n",
		      __func__, size, PERCPU_PAGE_SIZE, __pa(MAX_DMA_ADDRESS));
पूर्ण

/**
 * setup_per_cpu_areas - setup percpu areas
 *
 * Arch code has alपढ़ोy allocated and initialized percpu areas.  All
 * this function has to करो is to teach the determined layout to the
 * dynamic percpu allocator, which happens to be more complex than
 * creating whole new ones using helpers.
 */
व्योम __init
setup_per_cpu_areas(व्योम)
अणु
	काष्ठा pcpu_alloc_info *ai;
	काष्ठा pcpu_group_info *gi;
	अचिन्हित पूर्णांक cpu;
	sमाप_प्रकार अटल_size, reserved_size, dyn_size;

	ai = pcpu_alloc_alloc_info(1, num_possible_cpus());
	अगर (!ai)
		panic("failed to allocate pcpu_alloc_info");
	gi = &ai->groups[0];

	/* units are asचिन्हित consecutively to possible cpus */
	क्रम_each_possible_cpu(cpu)
		gi->cpu_map[gi->nr_units++] = cpu;

	/* set parameters */
	अटल_size = __per_cpu_end - __per_cpu_start;
	reserved_size = PERCPU_MODULE_RESERVE;
	dyn_size = PERCPU_PAGE_SIZE - अटल_size - reserved_size;
	अगर (dyn_size < 0)
		panic("percpu area overflow static=%zd reserved=%zd\n",
		      अटल_size, reserved_size);

	ai->अटल_size		= अटल_size;
	ai->reserved_size	= reserved_size;
	ai->dyn_size		= dyn_size;
	ai->unit_size		= PERCPU_PAGE_SIZE;
	ai->atom_size		= PAGE_SIZE;
	ai->alloc_size		= PERCPU_PAGE_SIZE;

	pcpu_setup_first_chunk(ai, __per_cpu_start + __per_cpu_offset[0]);
	pcpu_मुक्त_alloc_info(ai);
पूर्ण
#अन्यथा
#घोषणा alloc_per_cpu_data() करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_SMP */

/**
 * find_memory - setup memory map
 *
 * Walk the EFI memory map and find usable memory क्रम the प्रणाली, taking
 * पूर्णांकo account reserved areas.
 */
व्योम __init
find_memory (व्योम)
अणु
	reserve_memory();

	/* first find highest page frame number */
	min_low_pfn = ~0UL;
	max_low_pfn = 0;
	efi_memmap_walk(find_max_min_low_pfn, शून्य);
	max_pfn = max_low_pfn;

	memblock_add_node(0, PFN_PHYS(max_low_pfn), 0);

	find_initrd();

	alloc_per_cpu_data();
पूर्ण

अटल पूर्णांक __init find_largest_hole(u64 start, u64 end, व्योम *arg)
अणु
	u64 *max_gap = arg;

	अटल u64 last_end = PAGE_OFFSET;

	/* NOTE: this algorithm assumes efi memmap table is ordered */

	अगर (*max_gap < (start - last_end))
		*max_gap = start - last_end;
	last_end = end;
	वापस 0;
पूर्ण

अटल व्योम __init verअगरy_gap_असलence(व्योम)
अणु
	अचिन्हित दीर्घ max_gap;

	/* Forbid FLATMEM अगर hole is > than 1G */
	efi_memmap_walk(find_largest_hole, (u64 *)&max_gap);
	अगर (max_gap >= SZ_1G)
		panic("Cannot use FLATMEM with %ldMB hole\n"
		      "Please switch over to SPARSEMEM\n",
		      (max_gap >> 20));
पूर्ण

/*
 * Set up the page tables.
 */

व्योम __init
paging_init (व्योम)
अणु
	अचिन्हित दीर्घ max_dma;
	अचिन्हित दीर्घ max_zone_pfns[MAX_NR_ZONES];

	स_रखो(max_zone_pfns, 0, माप(max_zone_pfns));
	max_dma = virt_to_phys((व्योम *) MAX_DMA_ADDRESS) >> PAGE_SHIFT;
	max_zone_pfns[ZONE_DMA32] = max_dma;
	max_zone_pfns[ZONE_NORMAL] = max_low_pfn;

	verअगरy_gap_असलence();

	मुक्त_area_init(max_zone_pfns);
	zero_page_memmap_ptr = virt_to_page(ia64_imva(empty_zero_page));
पूर्ण
