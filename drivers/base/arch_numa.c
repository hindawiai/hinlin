<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * NUMA support, based on the x86 implementation.
 *
 * Copyright (C) 2015 Cavium Inc.
 * Author: Ganapatrao Kulkarni <gkulkarni@cavium.com>
 */

#घोषणा pr_fmt(fmt) "NUMA: " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/memblock.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/sections.h>

काष्ठा pglist_data *node_data[MAX_NUMNODES] __पढ़ो_mostly;
EXPORT_SYMBOL(node_data);
nodemask_t numa_nodes_parsed __initdata;
अटल पूर्णांक cpu_to_node_map[NR_CPUS] = अणु [0 ... NR_CPUS-1] = NUMA_NO_NODE पूर्ण;

अटल पूर्णांक numa_distance_cnt;
अटल u8 *numa_distance;
bool numa_off;

अटल __init पूर्णांक numa_parse_early_param(अक्षर *opt)
अणु
	अगर (!opt)
		वापस -EINVAL;
	अगर (str_has_prefix(opt, "off"))
		numa_off = true;

	वापस 0;
पूर्ण
early_param("numa", numa_parse_early_param);

cpumask_var_t node_to_cpumask_map[MAX_NUMNODES];
EXPORT_SYMBOL(node_to_cpumask_map);

#अगर_घोषित CONFIG_DEBUG_PER_CPU_MAPS

/*
 * Returns a poपूर्णांकer to the biपंचांगask of CPUs on Node 'node'.
 */
स्थिर काष्ठा cpumask *cpumask_of_node(पूर्णांक node)
अणु

	अगर (node == NUMA_NO_NODE)
		वापस cpu_all_mask;

	अगर (WARN_ON(node < 0 || node >= nr_node_ids))
		वापस cpu_none_mask;

	अगर (WARN_ON(node_to_cpumask_map[node] == शून्य))
		वापस cpu_online_mask;

	वापस node_to_cpumask_map[node];
पूर्ण
EXPORT_SYMBOL(cpumask_of_node);

#पूर्ण_अगर

अटल व्योम numa_update_cpu(अचिन्हित पूर्णांक cpu, bool हटाओ)
अणु
	पूर्णांक nid = cpu_to_node(cpu);

	अगर (nid == NUMA_NO_NODE)
		वापस;

	अगर (हटाओ)
		cpumask_clear_cpu(cpu, node_to_cpumask_map[nid]);
	अन्यथा
		cpumask_set_cpu(cpu, node_to_cpumask_map[nid]);
पूर्ण

व्योम numa_add_cpu(अचिन्हित पूर्णांक cpu)
अणु
	numa_update_cpu(cpu, false);
पूर्ण

व्योम numa_हटाओ_cpu(अचिन्हित पूर्णांक cpu)
अणु
	numa_update_cpu(cpu, true);
पूर्ण

व्योम numa_clear_node(अचिन्हित पूर्णांक cpu)
अणु
	numa_हटाओ_cpu(cpu);
	set_cpu_numa_node(cpu, NUMA_NO_NODE);
पूर्ण

/*
 * Allocate node_to_cpumask_map based on number of available nodes
 * Requires node_possible_map to be valid.
 *
 * Note: cpumask_of_node() is not valid until after this is करोne.
 * (Use CONFIG_DEBUG_PER_CPU_MAPS to check this.)
 */
अटल व्योम __init setup_node_to_cpumask_map(व्योम)
अणु
	पूर्णांक node;

	/* setup nr_node_ids अगर not करोne yet */
	अगर (nr_node_ids == MAX_NUMNODES)
		setup_nr_node_ids();

	/* allocate and clear the mapping */
	क्रम (node = 0; node < nr_node_ids; node++) अणु
		alloc_booपंचांगem_cpumask_var(&node_to_cpumask_map[node]);
		cpumask_clear(node_to_cpumask_map[node]);
	पूर्ण

	/* cpumask_of_node() will now work */
	pr_debug("Node to cpumask map for %u nodes\n", nr_node_ids);
पूर्ण

/*
 * Set the cpu to node and mem mapping
 */
व्योम numa_store_cpu_info(अचिन्हित पूर्णांक cpu)
अणु
	set_cpu_numa_node(cpu, cpu_to_node_map[cpu]);
पूर्ण

व्योम __init early_map_cpu_to_node(अचिन्हित पूर्णांक cpu, पूर्णांक nid)
अणु
	/* fallback to node 0 */
	अगर (nid < 0 || nid >= MAX_NUMNODES || numa_off)
		nid = 0;

	cpu_to_node_map[cpu] = nid;

	/*
	 * We should set the numa node of cpu0 as soon as possible, because it
	 * has alपढ़ोy been set up online beक्रमe. cpu_to_node(0) will soon be
	 * called.
	 */
	अगर (!cpu)
		set_cpu_numa_node(cpu, nid);
पूर्ण

#अगर_घोषित CONFIG_HAVE_SETUP_PER_CPU_AREA
अचिन्हित दीर्घ __per_cpu_offset[NR_CPUS] __पढ़ो_mostly;
EXPORT_SYMBOL(__per_cpu_offset);

अटल पूर्णांक __init early_cpu_to_node(पूर्णांक cpu)
अणु
	वापस cpu_to_node_map[cpu];
पूर्ण

अटल पूर्णांक __init pcpu_cpu_distance(अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक to)
अणु
	वापस node_distance(early_cpu_to_node(from), early_cpu_to_node(to));
पूर्ण

अटल व्योम * __init pcpu_fc_alloc(अचिन्हित पूर्णांक cpu, माप_प्रकार size,
				       माप_प्रकार align)
अणु
	पूर्णांक nid = early_cpu_to_node(cpu);

	वापस  memblock_alloc_try_nid(size, align,
			__pa(MAX_DMA_ADDRESS), MEMBLOCK_ALLOC_ACCESSIBLE, nid);
पूर्ण

अटल व्योम __init pcpu_fc_मुक्त(व्योम *ptr, माप_प्रकार size)
अणु
	memblock_मुक्त_early(__pa(ptr), size);
पूर्ण

व्योम __init setup_per_cpu_areas(व्योम)
अणु
	अचिन्हित दीर्घ delta;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक rc;

	/*
	 * Always reserve area क्रम module percpu variables.  That's
	 * what the legacy allocator did.
	 */
	rc = pcpu_embed_first_chunk(PERCPU_MODULE_RESERVE,
				    PERCPU_DYNAMIC_RESERVE, PAGE_SIZE,
				    pcpu_cpu_distance,
				    pcpu_fc_alloc, pcpu_fc_मुक्त);
	अगर (rc < 0)
		panic("Failed to initialize percpu areas.");

	delta = (अचिन्हित दीर्घ)pcpu_base_addr - (अचिन्हित दीर्घ)__per_cpu_start;
	क्रम_each_possible_cpu(cpu)
		__per_cpu_offset[cpu] = delta + pcpu_unit_offsets[cpu];
पूर्ण
#पूर्ण_अगर

/**
 * numa_add_memblk() - Set node id to memblk
 * @nid: NUMA node ID of the new memblk
 * @start: Start address of the new memblk
 * @end:  End address of the new memblk
 *
 * RETURNS:
 * 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक __init numa_add_memblk(पूर्णांक nid, u64 start, u64 end)
अणु
	पूर्णांक ret;

	ret = memblock_set_node(start, (end - start), &memblock.memory, nid);
	अगर (ret < 0) अणु
		pr_err("memblock [0x%llx - 0x%llx] failed to add on node %d\n",
			start, (end - 1), nid);
		वापस ret;
	पूर्ण

	node_set(nid, numa_nodes_parsed);
	वापस ret;
पूर्ण

/*
 * Initialize NODE_DATA क्रम a node on the local memory
 */
अटल व्योम __init setup_node_data(पूर्णांक nid, u64 start_pfn, u64 end_pfn)
अणु
	स्थिर माप_प्रकार nd_size = roundup(माप(pg_data_t), SMP_CACHE_BYTES);
	u64 nd_pa;
	व्योम *nd;
	पूर्णांक tnid;

	अगर (start_pfn >= end_pfn)
		pr_info("Initmem setup node %d [<memory-less node>]\n", nid);

	nd_pa = memblock_phys_alloc_try_nid(nd_size, SMP_CACHE_BYTES, nid);
	अगर (!nd_pa)
		panic("Cannot allocate %zu bytes for node %d data\n",
		      nd_size, nid);

	nd = __va(nd_pa);

	/* report and initialize */
	pr_info("NODE_DATA [mem %#010Lx-%#010Lx]\n",
		nd_pa, nd_pa + nd_size - 1);
	tnid = early_pfn_to_nid(nd_pa >> PAGE_SHIFT);
	अगर (tnid != nid)
		pr_info("NODE_DATA(%d) on node %d\n", nid, tnid);

	node_data[nid] = nd;
	स_रखो(NODE_DATA(nid), 0, माप(pg_data_t));
	NODE_DATA(nid)->node_id = nid;
	NODE_DATA(nid)->node_start_pfn = start_pfn;
	NODE_DATA(nid)->node_spanned_pages = end_pfn - start_pfn;
पूर्ण

/*
 * numa_मुक्त_distance
 *
 * The current table is मुक्तd.
 */
व्योम __init numa_मुक्त_distance(व्योम)
अणु
	माप_प्रकार size;

	अगर (!numa_distance)
		वापस;

	size = numa_distance_cnt * numa_distance_cnt *
		माप(numa_distance[0]);

	memblock_मुक्त(__pa(numa_distance), size);
	numa_distance_cnt = 0;
	numa_distance = शून्य;
पूर्ण

/*
 * Create a new NUMA distance table.
 */
अटल पूर्णांक __init numa_alloc_distance(व्योम)
अणु
	माप_प्रकार size;
	u64 phys;
	पूर्णांक i, j;

	size = nr_node_ids * nr_node_ids * माप(numa_distance[0]);
	phys = memblock_find_in_range(0, PFN_PHYS(max_pfn),
				      size, PAGE_SIZE);
	अगर (WARN_ON(!phys))
		वापस -ENOMEM;

	memblock_reserve(phys, size);

	numa_distance = __va(phys);
	numa_distance_cnt = nr_node_ids;

	/* fill with the शेष distances */
	क्रम (i = 0; i < numa_distance_cnt; i++)
		क्रम (j = 0; j < numa_distance_cnt; j++)
			numa_distance[i * numa_distance_cnt + j] = i == j ?
				LOCAL_DISTANCE : REMOTE_DISTANCE;

	pr_debug("Initialized distance table, cnt=%d\n", numa_distance_cnt);

	वापस 0;
पूर्ण

/**
 * numa_set_distance() - Set पूर्णांकer node NUMA distance from node to node.
 * @from: the 'from' node to set distance
 * @to: the 'to'  node to set distance
 * @distance: NUMA distance
 *
 * Set the distance from node @from to @to to @distance.
 * If distance table करोesn't exist, a warning is prपूर्णांकed.
 *
 * If @from or @to is higher than the highest known node or lower than zero
 * or @distance करोesn't make sense, the call is ignored.
 */
व्योम __init numa_set_distance(पूर्णांक from, पूर्णांक to, पूर्णांक distance)
अणु
	अगर (!numa_distance) अणु
		pr_warn_once("Warning: distance table not allocated yet\n");
		वापस;
	पूर्ण

	अगर (from >= numa_distance_cnt || to >= numa_distance_cnt ||
			from < 0 || to < 0) अणु
		pr_warn_once("Warning: node ids are out of bound, from=%d to=%d distance=%d\n",
			    from, to, distance);
		वापस;
	पूर्ण

	अगर ((u8)distance != distance ||
	    (from == to && distance != LOCAL_DISTANCE)) अणु
		pr_warn_once("Warning: invalid distance parameter, from=%d to=%d distance=%d\n",
			     from, to, distance);
		वापस;
	पूर्ण

	numa_distance[from * numa_distance_cnt + to] = distance;
पूर्ण

/*
 * Return NUMA distance @from to @to
 */
पूर्णांक __node_distance(पूर्णांक from, पूर्णांक to)
अणु
	अगर (from >= numa_distance_cnt || to >= numa_distance_cnt)
		वापस from == to ? LOCAL_DISTANCE : REMOTE_DISTANCE;
	वापस numa_distance[from * numa_distance_cnt + to];
पूर्ण
EXPORT_SYMBOL(__node_distance);

अटल पूर्णांक __init numa_रेजिस्टर_nodes(व्योम)
अणु
	पूर्णांक nid;
	काष्ठा memblock_region *mblk;

	/* Check that valid nid is set to memblks */
	क्रम_each_mem_region(mblk) अणु
		पूर्णांक mblk_nid = memblock_get_region_node(mblk);
		phys_addr_t start = mblk->base;
		phys_addr_t end = mblk->base + mblk->size - 1;

		अगर (mblk_nid == NUMA_NO_NODE || mblk_nid >= MAX_NUMNODES) अणु
			pr_warn("Warning: invalid memblk node %d [mem %pap-%pap]\n",
				mblk_nid, &start, &end);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Finally रेजिस्टर nodes. */
	क्रम_each_node_mask(nid, numa_nodes_parsed) अणु
		अचिन्हित दीर्घ start_pfn, end_pfn;

		get_pfn_range_क्रम_nid(nid, &start_pfn, &end_pfn);
		setup_node_data(nid, start_pfn, end_pfn);
		node_set_online(nid);
	पूर्ण

	/* Setup online nodes to actual nodes*/
	node_possible_map = numa_nodes_parsed;

	वापस 0;
पूर्ण

अटल पूर्णांक __init numa_init(पूर्णांक (*init_func)(व्योम))
अणु
	पूर्णांक ret;

	nodes_clear(numa_nodes_parsed);
	nodes_clear(node_possible_map);
	nodes_clear(node_online_map);

	ret = numa_alloc_distance();
	अगर (ret < 0)
		वापस ret;

	ret = init_func();
	अगर (ret < 0)
		जाओ out_मुक्त_distance;

	अगर (nodes_empty(numa_nodes_parsed)) अणु
		pr_info("No NUMA configuration found\n");
		ret = -EINVAL;
		जाओ out_मुक्त_distance;
	पूर्ण

	ret = numa_रेजिस्टर_nodes();
	अगर (ret < 0)
		जाओ out_मुक्त_distance;

	setup_node_to_cpumask_map();

	वापस 0;
out_मुक्त_distance:
	numa_मुक्त_distance();
	वापस ret;
पूर्ण

/**
 * dummy_numa_init() - Fallback dummy NUMA init
 *
 * Used अगर there's no underlying NUMA architecture, NUMA initialization
 * fails, or NUMA is disabled on the command line.
 *
 * Must online at least one node (node 0) and add memory blocks that cover all
 * allowed memory. It is unlikely that this function fails.
 *
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक __init dummy_numa_init(व्योम)
अणु
	phys_addr_t start = memblock_start_of_DRAM();
	phys_addr_t end = memblock_end_of_DRAM() - 1;
	पूर्णांक ret;

	अगर (numa_off)
		pr_info("NUMA disabled\n"); /* Forced off on command line. */
	pr_info("Faking a node at [mem %pap-%pap]\n", &start, &end);

	ret = numa_add_memblk(0, start, end + 1);
	अगर (ret) अणु
		pr_err("NUMA init failed\n");
		वापस ret;
	पूर्ण

	numa_off = true;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI_NUMA
अटल पूर्णांक __init arch_acpi_numa_init(व्योम)
अणु
	पूर्णांक ret;

	ret = acpi_numa_init();
	अगर (ret) अणु
		pr_info("Failed to initialise from firmware\n");
		वापस ret;
	पूर्ण

	वापस srat_disabled() ? -EINVAL : 0;
पूर्ण
#अन्यथा
अटल पूर्णांक __init arch_acpi_numa_init(व्योम)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

/**
 * arch_numa_init() - Initialize NUMA
 *
 * Try each configured NUMA initialization method until one succeeds. The
 * last fallback is dummy single node config encompassing whole memory.
 */
व्योम __init arch_numa_init(व्योम)
अणु
	अगर (!numa_off) अणु
		अगर (!acpi_disabled && !numa_init(arch_acpi_numa_init))
			वापस;
		अगर (acpi_disabled && !numa_init(of_numa_init))
			वापस;
	पूर्ण

	numa_init(dummy_numa_init);
पूर्ण
