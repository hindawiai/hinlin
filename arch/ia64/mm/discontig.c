<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000, 2003 Silicon Graphics, Inc.  All rights reserved.
 * Copyright (c) 2001 Intel Corp.
 * Copyright (c) 2001 Tony Luck <tony.luck@पूर्णांकel.com>
 * Copyright (c) 2002 NEC Corp.
 * Copyright (c) 2002 Kimio Suganuma <k-suganuma@da.jp.nec.com>
 * Copyright (c) 2004 Silicon Graphics, Inc
 *	Russ Anderson <rja@sgi.com>
 *	Jesse Barnes <jbarnes@sgi.com>
 *	Jack Steiner <steiner@sgi.com>
 */

/*
 * Platक्रमm initialization क्रम Discontig Memory
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/nmi.h>
#समावेश <linux/swap.h>
#समावेश <linux/memblock.h>
#समावेश <linux/acpi.h>
#समावेश <linux/efi.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/meminit.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/sections.h>

/*
 * Track per-node inक्रमmation needed to setup the boot memory allocator, the
 * per-node areas, and the real VM.
 */
काष्ठा early_node_data अणु
	काष्ठा ia64_node_data *node_data;
	अचिन्हित दीर्घ pernode_addr;
	अचिन्हित दीर्घ pernode_size;
	अचिन्हित दीर्घ min_pfn;
	अचिन्हित दीर्घ max_pfn;
पूर्ण;

अटल काष्ठा early_node_data mem_data[MAX_NUMNODES] __initdata;
अटल nodemask_t memory_less_mask __initdata;

pg_data_t *pgdat_list[MAX_NUMNODES];

/*
 * To prevent cache aliasing effects, align per-node काष्ठाures so that they
 * start at addresses that are strided by node number.
 */
#घोषणा MAX_NODE_ALIGN_OFFSET	(32 * 1024 * 1024)
#घोषणा NODEDATA_ALIGN(addr, node)						\
	((((addr) + 1024*1024-1) & ~(1024*1024-1)) + 				\
	     (((node)*PERCPU_PAGE_SIZE) & (MAX_NODE_ALIGN_OFFSET - 1)))

/**
 * build_node_maps - callback to setup mem_data काष्ठाs क्रम each node
 * @start: physical start of range
 * @len: length of range
 * @node: node where this range resides
 *
 * Detect extents of each piece of memory that we wish to
 * treat as a भवly contiguous block (i.e. each node). Each such block
 * must start on an %IA64_GRANULE_SIZE boundary, so we round the address करोwn
 * अगर necessary.  Any non-existent pages will simply be part of the भव
 * memmap.
 */
अटल पूर्णांक __init build_node_maps(अचिन्हित दीर्घ start, अचिन्हित दीर्घ len,
				  पूर्णांक node)
अणु
	अचिन्हित दीर्घ spfn, epfn, end = start + len;

	epfn = GRANULEROUNDUP(end) >> PAGE_SHIFT;
	spfn = GRANULEROUNDDOWN(start) >> PAGE_SHIFT;

	अगर (!mem_data[node].min_pfn) अणु
		mem_data[node].min_pfn = spfn;
		mem_data[node].max_pfn = epfn;
	पूर्ण अन्यथा अणु
		mem_data[node].min_pfn = min(spfn, mem_data[node].min_pfn);
		mem_data[node].max_pfn = max(epfn, mem_data[node].max_pfn);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * early_nr_cpus_node - वापस number of cpus on a given node
 * @node: node to check
 *
 * Count the number of cpus on @node.  We can't use nr_cpus_node() yet because
 * acpi_boot_init() (which builds the node_to_cpu_mask array) hasn't been
 * called yet.  Note that node 0 will also count all non-existent cpus.
 */
अटल पूर्णांक early_nr_cpus_node(पूर्णांक node)
अणु
	पूर्णांक cpu, n = 0;

	क्रम_each_possible_early_cpu(cpu)
		अगर (node == node_cpuid[cpu].nid)
			n++;

	वापस n;
पूर्ण

/**
 * compute_pernodesize - compute size of pernode data
 * @node: the node id.
 */
अटल अचिन्हित दीर्घ compute_pernodesize(पूर्णांक node)
अणु
	अचिन्हित दीर्घ pernodesize = 0, cpus;

	cpus = early_nr_cpus_node(node);
	pernodesize += PERCPU_PAGE_SIZE * cpus;
	pernodesize += node * L1_CACHE_BYTES;
	pernodesize += L1_CACHE_ALIGN(माप(pg_data_t));
	pernodesize += L1_CACHE_ALIGN(माप(काष्ठा ia64_node_data));
	pernodesize += L1_CACHE_ALIGN(माप(pg_data_t));
	pernodesize = PAGE_ALIGN(pernodesize);
	वापस pernodesize;
पूर्ण

/**
 * per_cpu_node_setup - setup per-cpu areas on each node
 * @cpu_data: per-cpu area on this node
 * @node: node to setup
 *
 * Copy the अटल per-cpu data पूर्णांकo the region we just set aside and then
 * setup __per_cpu_offset क्रम each CPU on this node.  Return a poपूर्णांकer to
 * the end of the area.
 */
अटल व्योम *per_cpu_node_setup(व्योम *cpu_data, पूर्णांक node)
अणु
#अगर_घोषित CONFIG_SMP
	पूर्णांक cpu;

	क्रम_each_possible_early_cpu(cpu) अणु
		व्योम *src = cpu == 0 ? __cpu0_per_cpu : __phys_per_cpu_start;

		अगर (node != node_cpuid[cpu].nid)
			जारी;

		स_नकल(__va(cpu_data), src, __per_cpu_end - __per_cpu_start);
		__per_cpu_offset[cpu] = (अक्षर *)__va(cpu_data) -
			__per_cpu_start;

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
			ia64_set_kr(IA64_KR_PER_CPU_DATA,
				    (अचिन्हित दीर्घ)cpu_data -
				    (अचिन्हित दीर्घ)__per_cpu_start);

		cpu_data += PERCPU_PAGE_SIZE;
	पूर्ण
#पूर्ण_अगर
	वापस cpu_data;
पूर्ण

#अगर_घोषित CONFIG_SMP
/**
 * setup_per_cpu_areas - setup percpu areas
 *
 * Arch code has alपढ़ोy allocated and initialized percpu areas.  All
 * this function has to करो is to teach the determined layout to the
 * dynamic percpu allocator, which happens to be more complex than
 * creating whole new ones using helpers.
 */
व्योम __init setup_per_cpu_areas(व्योम)
अणु
	काष्ठा pcpu_alloc_info *ai;
	काष्ठा pcpu_group_info *gi;
	अचिन्हित पूर्णांक *cpu_map;
	व्योम *base;
	अचिन्हित दीर्घ base_offset;
	अचिन्हित पूर्णांक cpu;
	sमाप_प्रकार अटल_size, reserved_size, dyn_size;
	पूर्णांक node, prev_node, unit, nr_units;

	ai = pcpu_alloc_alloc_info(MAX_NUMNODES, nr_cpu_ids);
	अगर (!ai)
		panic("failed to allocate pcpu_alloc_info");
	cpu_map = ai->groups[0].cpu_map;

	/* determine base */
	base = (व्योम *)अच_दीर्घ_उच्च;
	क्रम_each_possible_cpu(cpu)
		base = min(base,
			   (व्योम *)(__per_cpu_offset[cpu] + __per_cpu_start));
	base_offset = (व्योम *)__per_cpu_start - base;

	/* build cpu_map, units are grouped by node */
	unit = 0;
	क्रम_each_node(node)
		क्रम_each_possible_cpu(cpu)
			अगर (node == node_cpuid[cpu].nid)
				cpu_map[unit++] = cpu;
	nr_units = unit;

	/* set basic parameters */
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

	/*
	 * CPUs are put पूर्णांकo groups according to node.  Walk cpu_map
	 * and create new groups at node boundaries.
	 */
	prev_node = NUMA_NO_NODE;
	ai->nr_groups = 0;
	क्रम (unit = 0; unit < nr_units; unit++) अणु
		cpu = cpu_map[unit];
		node = node_cpuid[cpu].nid;

		अगर (node == prev_node) अणु
			gi->nr_units++;
			जारी;
		पूर्ण
		prev_node = node;

		gi = &ai->groups[ai->nr_groups++];
		gi->nr_units		= 1;
		gi->base_offset		= __per_cpu_offset[cpu] + base_offset;
		gi->cpu_map		= &cpu_map[unit];
	पूर्ण

	pcpu_setup_first_chunk(ai, base);
	pcpu_मुक्त_alloc_info(ai);
पूर्ण
#पूर्ण_अगर

/**
 * fill_pernode - initialize pernode data.
 * @node: the node id.
 * @pernode: physical address of pernode data
 * @pernodesize: size of the pernode data
 */
अटल व्योम __init fill_pernode(पूर्णांक node, अचिन्हित दीर्घ pernode,
	अचिन्हित दीर्घ pernodesize)
अणु
	व्योम *cpu_data;
	पूर्णांक cpus = early_nr_cpus_node(node);

	mem_data[node].pernode_addr = pernode;
	mem_data[node].pernode_size = pernodesize;
	स_रखो(__va(pernode), 0, pernodesize);

	cpu_data = (व्योम *)pernode;
	pernode += PERCPU_PAGE_SIZE * cpus;
	pernode += node * L1_CACHE_BYTES;

	pgdat_list[node] = __va(pernode);
	pernode += L1_CACHE_ALIGN(माप(pg_data_t));

	mem_data[node].node_data = __va(pernode);
	pernode += L1_CACHE_ALIGN(माप(काष्ठा ia64_node_data));
	pernode += L1_CACHE_ALIGN(माप(pg_data_t));

	cpu_data = per_cpu_node_setup(cpu_data, node);

	वापस;
पूर्ण

/**
 * find_pernode_space - allocate memory क्रम memory map and per-node काष्ठाures
 * @start: physical start of range
 * @len: length of range
 * @node: node where this range resides
 *
 * This routine reserves space क्रम the per-cpu data काष्ठा, the list of
 * pg_data_ts and the per-node data काष्ठा.  Each node will have something like
 * the following in the first chunk of addr. space large enough to hold it.
 *
 *    ________________________
 *   |                        |
 *   |~~~~~~~~~~~~~~~~~~~~~~~~| <-- NODEDATA_ALIGN(start, node) क्रम the first
 *   |    PERCPU_PAGE_SIZE *  |     start and length big enough
 *   |    cpus_on_this_node   | Node 0 will also have entries क्रम all non-existent cpus.
 *   |------------------------|
 *   |   local pg_data_t *    |
 *   |------------------------|
 *   |  local ia64_node_data  |
 *   |------------------------|
 *   |          ???           |
 *   |________________________|
 *
 * Once this space has been set aside, the booपंचांगem maps are initialized.  We
 * could probably move the allocation of the per-cpu and ia64_node_data space
 * outside of this function and use alloc_booपंचांगem_node(), but करोing it here
 * is straightक्रमward and we get the alignments we want so...
 */
अटल पूर्णांक __init find_pernode_space(अचिन्हित दीर्घ start, अचिन्हित दीर्घ len,
				     पूर्णांक node)
अणु
	अचिन्हित दीर्घ spfn, epfn;
	अचिन्हित दीर्घ pernodesize = 0, pernode;

	spfn = start >> PAGE_SHIFT;
	epfn = (start + len) >> PAGE_SHIFT;

	/*
	 * Make sure this memory falls within this node's usable memory
	 * since we may have thrown some away in build_maps().
	 */
	अगर (spfn < mem_data[node].min_pfn || epfn > mem_data[node].max_pfn)
		वापस 0;

	/* Don't setup this node's local space twice... */
	अगर (mem_data[node].pernode_addr)
		वापस 0;

	/*
	 * Calculate total size needed, incl. what's necessary
	 * क्रम good alignment and alias prevention.
	 */
	pernodesize = compute_pernodesize(node);
	pernode = NODEDATA_ALIGN(start, node);

	/* Is this range big enough क्रम what we want to store here? */
	अगर (start + len > (pernode + pernodesize))
		fill_pernode(node, pernode, pernodesize);

	वापस 0;
पूर्ण

/**
 * reserve_pernode_space - reserve memory क्रम per-node space
 *
 * Reserve the space used by the booपंचांगem maps & per-node space in the boot
 * allocator so that when we actually create the real mem maps we करोn't
 * use their memory.
 */
अटल व्योम __init reserve_pernode_space(व्योम)
अणु
	अचिन्हित दीर्घ base, size;
	पूर्णांक node;

	क्रम_each_online_node(node) अणु
		अगर (node_isset(node, memory_less_mask))
			जारी;

		/* Now the per-node space */
		size = mem_data[node].pernode_size;
		base = __pa(mem_data[node].pernode_addr);
		memblock_reserve(base, size);
	पूर्ण
पूर्ण

अटल व्योम scatter_node_data(व्योम)
अणु
	pg_data_t **dst;
	पूर्णांक node;

	/*
	 * क्रम_each_online_node() can't be used at here.
	 * node_online_map is not set क्रम hot-added nodes at this समय,
	 * because we are halfway through initialization of the new node's
	 * काष्ठाures.  If क्रम_each_online_node() is used, a new node's
	 * pg_data_ptrs will be not initialized. Instead of using it,
	 * pgdat_list[] is checked.
	 */
	क्रम_each_node(node) अणु
		अगर (pgdat_list[node]) अणु
			dst = LOCAL_DATA_ADDR(pgdat_list[node])->pg_data_ptrs;
			स_नकल(dst, pgdat_list, माप(pgdat_list));
		पूर्ण
	पूर्ण
पूर्ण

/**
 * initialize_pernode_data - fixup per-cpu & per-node poपूर्णांकers
 *
 * Each node's per-node area has a copy of the global pg_data_t list, so
 * we copy that to each node here, as well as setting the per-cpu poपूर्णांकer
 * to the local node data काष्ठाure.
 */
अटल व्योम __init initialize_pernode_data(व्योम)
अणु
	पूर्णांक cpu, node;

	scatter_node_data();

#अगर_घोषित CONFIG_SMP
	/* Set the node_data poपूर्णांकer क्रम each per-cpu काष्ठा */
	क्रम_each_possible_early_cpu(cpu) अणु
		node = node_cpuid[cpu].nid;
		per_cpu(ia64_cpu_info, cpu).node_data =
			mem_data[node].node_data;
	पूर्ण
#अन्यथा
	अणु
		काष्ठा cpuinfo_ia64 *cpu0_cpu_info;
		cpu = 0;
		node = node_cpuid[cpu].nid;
		cpu0_cpu_info = (काष्ठा cpuinfo_ia64 *)(__phys_per_cpu_start +
			((अक्षर *)&ia64_cpu_info - __per_cpu_start));
		cpu0_cpu_info->node_data = mem_data[node].node_data;
	पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */
पूर्ण

/**
 * memory_less_node_alloc - * attempt to allocate memory on the best NUMA slit
 * 	node but fall back to any other node when __alloc_booपंचांगem_node fails
 *	क्रम best.
 * @nid: node id
 * @pernodesize: size of this node's pernode data
 */
अटल व्योम __init *memory_less_node_alloc(पूर्णांक nid, अचिन्हित दीर्घ pernodesize)
अणु
	व्योम *ptr = शून्य;
	u8 best = 0xff;
	पूर्णांक bestnode = NUMA_NO_NODE, node, anynode = 0;

	क्रम_each_online_node(node) अणु
		अगर (node_isset(node, memory_less_mask))
			जारी;
		अन्यथा अगर (node_distance(nid, node) < best) अणु
			best = node_distance(nid, node);
			bestnode = node;
		पूर्ण
		anynode = node;
	पूर्ण

	अगर (bestnode == NUMA_NO_NODE)
		bestnode = anynode;

	ptr = memblock_alloc_try_nid(pernodesize, PERCPU_PAGE_SIZE,
				     __pa(MAX_DMA_ADDRESS),
				     MEMBLOCK_ALLOC_ACCESSIBLE,
				     bestnode);
	अगर (!ptr)
		panic("%s: Failed to allocate %lu bytes align=0x%lx nid=%d from=%lx\n",
		      __func__, pernodesize, PERCPU_PAGE_SIZE, bestnode,
		      __pa(MAX_DMA_ADDRESS));

	वापस ptr;
पूर्ण

/**
 * memory_less_nodes - allocate and initialize CPU only nodes pernode
 *	inक्रमmation.
 */
अटल व्योम __init memory_less_nodes(व्योम)
अणु
	अचिन्हित दीर्घ pernodesize;
	व्योम *pernode;
	पूर्णांक node;

	क्रम_each_node_mask(node, memory_less_mask) अणु
		pernodesize = compute_pernodesize(node);
		pernode = memory_less_node_alloc(node, pernodesize);
		fill_pernode(node, __pa(pernode), pernodesize);
	पूर्ण

	वापस;
पूर्ण

/**
 * find_memory - walk the EFI memory map and setup the booपंचांगem allocator
 *
 * Called early in boot to setup the booपंचांगem allocator, and to
 * allocate the per-cpu and per-node काष्ठाures.
 */
व्योम __init find_memory(व्योम)
अणु
	पूर्णांक node;

	reserve_memory();
	efi_memmap_walk(filter_memory, रेजिस्टर_active_ranges);

	अगर (num_online_nodes() == 0) अणु
		prपूर्णांकk(KERN_ERR "node info missing!\n");
		node_set_online(0);
	पूर्ण

	nodes_or(memory_less_mask, memory_less_mask, node_online_map);
	min_low_pfn = -1;
	max_low_pfn = 0;

	/* These actually end up getting called by call_pernode_memory() */
	efi_memmap_walk(filter_rsvd_memory, build_node_maps);
	efi_memmap_walk(filter_rsvd_memory, find_pernode_space);
	efi_memmap_walk(find_max_min_low_pfn, शून्य);

	क्रम_each_online_node(node)
		अगर (mem_data[node].min_pfn)
			node_clear(node, memory_less_mask);

	reserve_pernode_space();
	memory_less_nodes();
	initialize_pernode_data();

	max_pfn = max_low_pfn;

	find_initrd();
पूर्ण

#अगर_घोषित CONFIG_SMP
/**
 * per_cpu_init - setup per-cpu variables
 *
 * find_pernode_space() करोes most of this alपढ़ोy, we just need to set
 * local_per_cpu_offset
 */
व्योम *per_cpu_init(व्योम)
अणु
	पूर्णांक cpu;
	अटल पूर्णांक first_समय = 1;

	अगर (first_समय) अणु
		first_समय = 0;
		क्रम_each_possible_early_cpu(cpu)
			per_cpu(local_per_cpu_offset, cpu) = __per_cpu_offset[cpu];
	पूर्ण

	वापस __per_cpu_start + __per_cpu_offset[smp_processor_id()];
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

/**
 * call_pernode_memory - use SRAT to call callback functions with node info
 * @start: physical start of range
 * @len: length of range
 * @arg: function to call क्रम each range
 *
 * efi_memmap_walk() knows nothing about layout of memory across nodes. Find
 * out to which node a block of memory beदीर्घs.  Ignore memory that we cannot
 * identअगरy, and split blocks that run across multiple nodes.
 *
 * Take this opportunity to round the start address up and the end address
 * करोwn to page boundaries.
 */
व्योम call_pernode_memory(अचिन्हित दीर्घ start, अचिन्हित दीर्घ len, व्योम *arg)
अणु
	अचिन्हित दीर्घ rs, re, end = start + len;
	व्योम (*func)(अचिन्हित दीर्घ, अचिन्हित दीर्घ, पूर्णांक);
	पूर्णांक i;

	start = PAGE_ALIGN(start);
	end &= PAGE_MASK;
	अगर (start >= end)
		वापस;

	func = arg;

	अगर (!num_node_memblks) अणु
		/* No SRAT table, so assume one node (node 0) */
		अगर (start < end)
			(*func)(start, end - start, 0);
		वापस;
	पूर्ण

	क्रम (i = 0; i < num_node_memblks; i++) अणु
		rs = max(start, node_memblk[i].start_paddr);
		re = min(end, node_memblk[i].start_paddr +
			 node_memblk[i].size);

		अगर (rs < re)
			(*func)(rs, re - rs, node_memblk[i].nid);

		अगर (re == end)
			अवरोध;
	पूर्ण
पूर्ण

/**
 * paging_init - setup page tables
 *
 * paging_init() sets up the page tables क्रम each node of the प्रणाली and मुक्तs
 * the booपंचांगem allocator memory क्रम general use.
 */
व्योम __init paging_init(व्योम)
अणु
	अचिन्हित दीर्घ max_dma;
	अचिन्हित दीर्घ max_zone_pfns[MAX_NR_ZONES];

	max_dma = virt_to_phys((व्योम *) MAX_DMA_ADDRESS) >> PAGE_SHIFT;

	sparse_init();

	स_रखो(max_zone_pfns, 0, माप(max_zone_pfns));
	max_zone_pfns[ZONE_DMA32] = max_dma;
	max_zone_pfns[ZONE_NORMAL] = max_low_pfn;
	मुक्त_area_init(max_zone_pfns);

	zero_page_memmap_ptr = virt_to_page(ia64_imva(empty_zero_page));
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
pg_data_t *arch_alloc_nodedata(पूर्णांक nid)
अणु
	अचिन्हित दीर्घ size = compute_pernodesize(nid);

	वापस kzalloc(size, GFP_KERNEL);
पूर्ण

व्योम arch_मुक्त_nodedata(pg_data_t *pgdat)
अणु
	kमुक्त(pgdat);
पूर्ण

व्योम arch_refresh_nodedata(पूर्णांक update_node, pg_data_t *update_pgdat)
अणु
	pgdat_list[update_node] = update_pgdat;
	scatter_node_data();
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
पूर्णांक __meminit vmemmap_populate(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, पूर्णांक node,
		काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	वापस vmemmap_populate_basepages(start, end, node, शून्य);
पूर्ण

व्योम vmemmap_मुक्त(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
		काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
पूर्ण
#पूर्ण_अगर
