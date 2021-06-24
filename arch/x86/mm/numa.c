<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Common code क्रम 32 and 64-bit NUMA */
#समावेश <linux/acpi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/nodemask.h>
#समावेश <linux/sched.h>
#समावेश <linux/topology.h>

#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/amd_nb.h>

#समावेश "numa_internal.h"

पूर्णांक numa_off;
nodemask_t numa_nodes_parsed __initdata;

काष्ठा pglist_data *node_data[MAX_NUMNODES] __पढ़ो_mostly;
EXPORT_SYMBOL(node_data);

अटल काष्ठा numa_meminfo numa_meminfo __initdata_or_meminfo;
अटल काष्ठा numa_meminfo numa_reserved_meminfo __initdata_or_meminfo;

अटल पूर्णांक numa_distance_cnt;
अटल u8 *numa_distance;

अटल __init पूर्णांक numa_setup(अक्षर *opt)
अणु
	अगर (!opt)
		वापस -EINVAL;
	अगर (!म_भेदन(opt, "off", 3))
		numa_off = 1;
	अगर (!म_भेदन(opt, "fake=", 5))
		वापस numa_emu_cmdline(opt + 5);
	अगर (!म_भेदन(opt, "noacpi", 6))
		disable_srat();
	अगर (!म_भेदन(opt, "nohmat", 6))
		disable_hmat();
	वापस 0;
पूर्ण
early_param("numa", numa_setup);

/*
 * apicid, cpu, node mappings
 */
s16 __apicid_to_node[MAX_LOCAL_APIC] = अणु
	[0 ... MAX_LOCAL_APIC-1] = NUMA_NO_NODE
पूर्ण;

पूर्णांक numa_cpu_node(पूर्णांक cpu)
अणु
	पूर्णांक apicid = early_per_cpu(x86_cpu_to_apicid, cpu);

	अगर (apicid != BAD_APICID)
		वापस __apicid_to_node[apicid];
	वापस NUMA_NO_NODE;
पूर्ण

cpumask_var_t node_to_cpumask_map[MAX_NUMNODES];
EXPORT_SYMBOL(node_to_cpumask_map);

/*
 * Map cpu index to node index
 */
DEFINE_EARLY_PER_CPU(पूर्णांक, x86_cpu_to_node_map, NUMA_NO_NODE);
EXPORT_EARLY_PER_CPU_SYMBOL(x86_cpu_to_node_map);

व्योम numa_set_node(पूर्णांक cpu, पूर्णांक node)
अणु
	पूर्णांक *cpu_to_node_map = early_per_cpu_ptr(x86_cpu_to_node_map);

	/* early setting, no percpu area yet */
	अगर (cpu_to_node_map) अणु
		cpu_to_node_map[cpu] = node;
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_PER_CPU_MAPS
	अगर (cpu >= nr_cpu_ids || !cpu_possible(cpu)) अणु
		prपूर्णांकk(KERN_ERR "numa_set_node: invalid cpu# (%d)\n", cpu);
		dump_stack();
		वापस;
	पूर्ण
#पूर्ण_अगर
	per_cpu(x86_cpu_to_node_map, cpu) = node;

	set_cpu_numa_node(cpu, node);
पूर्ण

व्योम numa_clear_node(पूर्णांक cpu)
अणु
	numa_set_node(cpu, NUMA_NO_NODE);
पूर्ण

/*
 * Allocate node_to_cpumask_map based on number of available nodes
 * Requires node_possible_map to be valid.
 *
 * Note: cpumask_of_node() is not valid until after this is करोne.
 * (Use CONFIG_DEBUG_PER_CPU_MAPS to check this.)
 */
व्योम __init setup_node_to_cpumask_map(व्योम)
अणु
	अचिन्हित पूर्णांक node;

	/* setup nr_node_ids अगर not करोne yet */
	अगर (nr_node_ids == MAX_NUMNODES)
		setup_nr_node_ids();

	/* allocate the map */
	क्रम (node = 0; node < nr_node_ids; node++)
		alloc_booपंचांगem_cpumask_var(&node_to_cpumask_map[node]);

	/* cpumask_of_node() will now work */
	pr_debug("Node to cpumask map for %u nodes\n", nr_node_ids);
पूर्ण

अटल पूर्णांक __init numa_add_memblk_to(पूर्णांक nid, u64 start, u64 end,
				     काष्ठा numa_meminfo *mi)
अणु
	/* ignore zero length blks */
	अगर (start == end)
		वापस 0;

	/* whine about and ignore invalid blks */
	अगर (start > end || nid < 0 || nid >= MAX_NUMNODES) अणु
		pr_warn("Warning: invalid memblk node %d [mem %#010Lx-%#010Lx]\n",
			nid, start, end - 1);
		वापस 0;
	पूर्ण

	अगर (mi->nr_blks >= NR_NODE_MEMBLKS) अणु
		pr_err("too many memblk ranges\n");
		वापस -EINVAL;
	पूर्ण

	mi->blk[mi->nr_blks].start = start;
	mi->blk[mi->nr_blks].end = end;
	mi->blk[mi->nr_blks].nid = nid;
	mi->nr_blks++;
	वापस 0;
पूर्ण

/**
 * numa_हटाओ_memblk_from - Remove one numa_memblk from a numa_meminfo
 * @idx: Index of memblk to हटाओ
 * @mi: numa_meminfo to हटाओ memblk from
 *
 * Remove @idx'th numa_memblk from @mi by shअगरting @mi->blk[] and
 * decrementing @mi->nr_blks.
 */
व्योम __init numa_हटाओ_memblk_from(पूर्णांक idx, काष्ठा numa_meminfo *mi)
अणु
	mi->nr_blks--;
	स_हटाओ(&mi->blk[idx], &mi->blk[idx + 1],
		(mi->nr_blks - idx) * माप(mi->blk[0]));
पूर्ण

/**
 * numa_move_tail_memblk - Move a numa_memblk from one numa_meminfo to another
 * @dst: numa_meminfo to append block to
 * @idx: Index of memblk to हटाओ
 * @src: numa_meminfo to हटाओ memblk from
 */
अटल व्योम __init numa_move_tail_memblk(काष्ठा numa_meminfo *dst, पूर्णांक idx,
					 काष्ठा numa_meminfo *src)
अणु
	dst->blk[dst->nr_blks++] = src->blk[idx];
	numa_हटाओ_memblk_from(idx, src);
पूर्ण

/**
 * numa_add_memblk - Add one numa_memblk to numa_meminfo
 * @nid: NUMA node ID of the new memblk
 * @start: Start address of the new memblk
 * @end: End address of the new memblk
 *
 * Add a new memblk to the शेष numa_meminfo.
 *
 * RETURNS:
 * 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक __init numa_add_memblk(पूर्णांक nid, u64 start, u64 end)
अणु
	वापस numa_add_memblk_to(nid, start, end, &numa_meminfo);
पूर्ण

/* Allocate NODE_DATA क्रम a node on the local memory */
अटल व्योम __init alloc_node_data(पूर्णांक nid)
अणु
	स्थिर माप_प्रकार nd_size = roundup(माप(pg_data_t), PAGE_SIZE);
	u64 nd_pa;
	व्योम *nd;
	पूर्णांक tnid;

	/*
	 * Allocate node data.  Try node-local memory and then any node.
	 * Never allocate in DMA zone.
	 */
	nd_pa = memblock_phys_alloc_try_nid(nd_size, SMP_CACHE_BYTES, nid);
	अगर (!nd_pa) अणु
		pr_err("Cannot find %zu bytes in any node (initial node: %d)\n",
		       nd_size, nid);
		वापस;
	पूर्ण
	nd = __va(nd_pa);

	/* report and initialize */
	prपूर्णांकk(KERN_INFO "NODE_DATA(%d) allocated [mem %#010Lx-%#010Lx]\n", nid,
	       nd_pa, nd_pa + nd_size - 1);
	tnid = early_pfn_to_nid(nd_pa >> PAGE_SHIFT);
	अगर (tnid != nid)
		prपूर्णांकk(KERN_INFO "    NODE_DATA(%d) on node %d\n", nid, tnid);

	node_data[nid] = nd;
	स_रखो(NODE_DATA(nid), 0, माप(pg_data_t));

	node_set_online(nid);
पूर्ण

/**
 * numa_cleanup_meminfo - Cleanup a numa_meminfo
 * @mi: numa_meminfo to clean up
 *
 * Sanitize @mi by merging and removing unnecessary memblks.  Also check क्रम
 * conflicts and clear unused memblks.
 *
 * RETURNS:
 * 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक __init numa_cleanup_meminfo(काष्ठा numa_meminfo *mi)
अणु
	स्थिर u64 low = 0;
	स्थिर u64 high = PFN_PHYS(max_pfn);
	पूर्णांक i, j, k;

	/* first, trim all entries */
	क्रम (i = 0; i < mi->nr_blks; i++) अणु
		काष्ठा numa_memblk *bi = &mi->blk[i];

		/* move / save reserved memory ranges */
		अगर (!memblock_overlaps_region(&memblock.memory,
					bi->start, bi->end - bi->start)) अणु
			numa_move_tail_memblk(&numa_reserved_meminfo, i--, mi);
			जारी;
		पूर्ण

		/* make sure all non-reserved blocks are inside the limits */
		bi->start = max(bi->start, low);

		/* preserve info क्रम non-RAM areas above 'max_pfn': */
		अगर (bi->end > high) अणु
			numa_add_memblk_to(bi->nid, high, bi->end,
					   &numa_reserved_meminfo);
			bi->end = high;
		पूर्ण

		/* and there's no empty block */
		अगर (bi->start >= bi->end)
			numa_हटाओ_memblk_from(i--, mi);
	पूर्ण

	/* merge neighboring / overlapping entries */
	क्रम (i = 0; i < mi->nr_blks; i++) अणु
		काष्ठा numa_memblk *bi = &mi->blk[i];

		क्रम (j = i + 1; j < mi->nr_blks; j++) अणु
			काष्ठा numa_memblk *bj = &mi->blk[j];
			u64 start, end;

			/*
			 * See whether there are overlapping blocks.  Whine
			 * about but allow overlaps of the same nid.  They
			 * will be merged below.
			 */
			अगर (bi->end > bj->start && bi->start < bj->end) अणु
				अगर (bi->nid != bj->nid) अणु
					pr_err("node %d [mem %#010Lx-%#010Lx] overlaps with node %d [mem %#010Lx-%#010Lx]\n",
					       bi->nid, bi->start, bi->end - 1,
					       bj->nid, bj->start, bj->end - 1);
					वापस -EINVAL;
				पूर्ण
				pr_warn("Warning: node %d [mem %#010Lx-%#010Lx] overlaps with itself [mem %#010Lx-%#010Lx]\n",
					bi->nid, bi->start, bi->end - 1,
					bj->start, bj->end - 1);
			पूर्ण

			/*
			 * Join together blocks on the same node, holes
			 * between which करोn't overlap with memory on other
			 * nodes.
			 */
			अगर (bi->nid != bj->nid)
				जारी;
			start = min(bi->start, bj->start);
			end = max(bi->end, bj->end);
			क्रम (k = 0; k < mi->nr_blks; k++) अणु
				काष्ठा numa_memblk *bk = &mi->blk[k];

				अगर (bi->nid == bk->nid)
					जारी;
				अगर (start < bk->end && end > bk->start)
					अवरोध;
			पूर्ण
			अगर (k < mi->nr_blks)
				जारी;
			prपूर्णांकk(KERN_INFO "NUMA: Node %d [mem %#010Lx-%#010Lx] + [mem %#010Lx-%#010Lx] -> [mem %#010Lx-%#010Lx]\n",
			       bi->nid, bi->start, bi->end - 1, bj->start,
			       bj->end - 1, start, end - 1);
			bi->start = start;
			bi->end = end;
			numa_हटाओ_memblk_from(j--, mi);
		पूर्ण
	पूर्ण

	/* clear unused ones */
	क्रम (i = mi->nr_blks; i < ARRAY_SIZE(mi->blk); i++) अणु
		mi->blk[i].start = mi->blk[i].end = 0;
		mi->blk[i].nid = NUMA_NO_NODE;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Set nodes, which have memory in @mi, in *@nodemask.
 */
अटल व्योम __init numa_nodemask_from_meminfo(nodemask_t *nodemask,
					      स्थिर काष्ठा numa_meminfo *mi)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mi->blk); i++)
		अगर (mi->blk[i].start != mi->blk[i].end &&
		    mi->blk[i].nid != NUMA_NO_NODE)
			node_set(mi->blk[i].nid, *nodemask);
पूर्ण

/**
 * numa_reset_distance - Reset NUMA distance table
 *
 * The current table is मुक्तd.  The next numa_set_distance() call will
 * create a new one.
 */
व्योम __init numa_reset_distance(व्योम)
अणु
	माप_प्रकार size = numa_distance_cnt * numa_distance_cnt * माप(numa_distance[0]);

	/* numa_distance could be 1LU marking allocation failure, test cnt */
	अगर (numa_distance_cnt)
		memblock_मुक्त(__pa(numa_distance), size);
	numa_distance_cnt = 0;
	numa_distance = शून्य;	/* enable table creation */
पूर्ण

अटल पूर्णांक __init numa_alloc_distance(व्योम)
अणु
	nodemask_t nodes_parsed;
	माप_प्रकार size;
	पूर्णांक i, j, cnt = 0;
	u64 phys;

	/* size the new table and allocate it */
	nodes_parsed = numa_nodes_parsed;
	numa_nodemask_from_meminfo(&nodes_parsed, &numa_meminfo);

	क्रम_each_node_mask(i, nodes_parsed)
		cnt = i;
	cnt++;
	size = cnt * cnt * माप(numa_distance[0]);

	phys = memblock_find_in_range(0, PFN_PHYS(max_pfn_mapped),
				      size, PAGE_SIZE);
	अगर (!phys) अणु
		pr_warn("Warning: can't allocate distance table!\n");
		/* करोn't retry until explicitly reset */
		numa_distance = (व्योम *)1LU;
		वापस -ENOMEM;
	पूर्ण
	memblock_reserve(phys, size);

	numa_distance = __va(phys);
	numa_distance_cnt = cnt;

	/* fill with the शेष distances */
	क्रम (i = 0; i < cnt; i++)
		क्रम (j = 0; j < cnt; j++)
			numa_distance[i * cnt + j] = i == j ?
				LOCAL_DISTANCE : REMOTE_DISTANCE;
	prपूर्णांकk(KERN_DEBUG "NUMA: Initialized distance table, cnt=%d\n", cnt);

	वापस 0;
पूर्ण

/**
 * numa_set_distance - Set NUMA distance from one NUMA to another
 * @from: the 'from' node to set distance
 * @to: the 'to'  node to set distance
 * @distance: NUMA distance
 *
 * Set the distance from node @from to @to to @distance.  If distance table
 * करोesn't exist, one which is large enough to accommodate all the currently
 * known nodes will be created.
 *
 * If such table cannot be allocated, a warning is prपूर्णांकed and further
 * calls are ignored until the distance table is reset with
 * numa_reset_distance().
 *
 * If @from or @to is higher than the highest known node or lower than zero
 * at the समय of table creation or @distance करोesn't make sense, the call
 * is ignored.
 * This is to allow simplअगरication of specअगरic NUMA config implementations.
 */
व्योम __init numa_set_distance(पूर्णांक from, पूर्णांक to, पूर्णांक distance)
अणु
	अगर (!numa_distance && numa_alloc_distance() < 0)
		वापस;

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

पूर्णांक __node_distance(पूर्णांक from, पूर्णांक to)
अणु
	अगर (from >= numa_distance_cnt || to >= numa_distance_cnt)
		वापस from == to ? LOCAL_DISTANCE : REMOTE_DISTANCE;
	वापस numa_distance[from * numa_distance_cnt + to];
पूर्ण
EXPORT_SYMBOL(__node_distance);

/*
 * Sanity check to catch more bad NUMA configurations (they are amazingly
 * common).  Make sure the nodes cover all memory.
 */
अटल bool __init numa_meminfo_cover_memory(स्थिर काष्ठा numa_meminfo *mi)
अणु
	u64 numaram, e820ram;
	पूर्णांक i;

	numaram = 0;
	क्रम (i = 0; i < mi->nr_blks; i++) अणु
		u64 s = mi->blk[i].start >> PAGE_SHIFT;
		u64 e = mi->blk[i].end >> PAGE_SHIFT;
		numaram += e - s;
		numaram -= __असलent_pages_in_range(mi->blk[i].nid, s, e);
		अगर ((s64)numaram < 0)
			numaram = 0;
	पूर्ण

	e820ram = max_pfn - असलent_pages_in_range(0, max_pfn);

	/* We seem to lose 3 pages somewhere. Allow 1M of slack. */
	अगर ((s64)(e820ram - numaram) >= (1 << (20 - PAGE_SHIFT))) अणु
		prपूर्णांकk(KERN_ERR "NUMA: nodes only cover %LuMB of your %LuMB e820 RAM. Not used.\n",
		       (numaram << PAGE_SHIFT) >> 20,
		       (e820ram << PAGE_SHIFT) >> 20);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/*
 * Mark all currently memblock-reserved physical memory (which covers the
 * kernel's own memory ranges) as hot-unswappable.
 */
अटल व्योम __init numa_clear_kernel_node_hotplug(व्योम)
अणु
	nodemask_t reserved_nodemask = NODE_MASK_NONE;
	काष्ठा memblock_region *mb_region;
	पूर्णांक i;

	/*
	 * We have to करो some preprocessing of memblock regions, to
	 * make them suitable क्रम reservation.
	 *
	 * At this समय, all memory regions reserved by memblock are
	 * used by the kernel, but those regions are not split up
	 * aदीर्घ node boundaries yet, and करोn't necessarily have their
	 * node ID set yet either.
	 *
	 * So iterate over all memory known to the x86 architecture,
	 * and use those ranges to set the nid in memblock.reserved.
	 * This will split up the memblock regions aदीर्घ node
	 * boundaries and will set the node IDs as well.
	 */
	क्रम (i = 0; i < numa_meminfo.nr_blks; i++) अणु
		काष्ठा numa_memblk *mb = numa_meminfo.blk + i;
		पूर्णांक ret;

		ret = memblock_set_node(mb->start, mb->end - mb->start, &memblock.reserved, mb->nid);
		WARN_ON_ONCE(ret);
	पूर्ण

	/*
	 * Now go over all reserved memblock regions, to स्थिरruct a
	 * node mask of all kernel reserved memory areas.
	 *
	 * [ Note, when booting with mem=nn[kMG] or in a kdump kernel,
	 *   numa_meminfo might not include all memblock.reserved
	 *   memory ranges, because quirks such as trim_snb_memory()
	 *   reserve specअगरic pages क्रम Sandy Bridge graphics. ]
	 */
	क्रम_each_reserved_mem_region(mb_region) अणु
		पूर्णांक nid = memblock_get_region_node(mb_region);

		अगर (nid != MAX_NUMNODES)
			node_set(nid, reserved_nodemask);
	पूर्ण

	/*
	 * Finally, clear the MEMBLOCK_HOTPLUG flag क्रम all memory
	 * beदीर्घing to the reserved node mask.
	 *
	 * Note that this will include memory regions that reside
	 * on nodes that contain kernel memory - entire nodes
	 * become hot-unpluggable:
	 */
	क्रम (i = 0; i < numa_meminfo.nr_blks; i++) अणु
		काष्ठा numa_memblk *mb = numa_meminfo.blk + i;

		अगर (!node_isset(mb->nid, reserved_nodemask))
			जारी;

		memblock_clear_hotplug(mb->start, mb->end - mb->start);
	पूर्ण
पूर्ण

अटल पूर्णांक __init numa_रेजिस्टर_memblks(काष्ठा numa_meminfo *mi)
अणु
	पूर्णांक i, nid;

	/* Account क्रम nodes with cpus and no memory */
	node_possible_map = numa_nodes_parsed;
	numa_nodemask_from_meminfo(&node_possible_map, mi);
	अगर (WARN_ON(nodes_empty(node_possible_map)))
		वापस -EINVAL;

	क्रम (i = 0; i < mi->nr_blks; i++) अणु
		काष्ठा numa_memblk *mb = &mi->blk[i];
		memblock_set_node(mb->start, mb->end - mb->start,
				  &memblock.memory, mb->nid);
	पूर्ण

	/*
	 * At very early समय, the kernel have to use some memory such as
	 * loading the kernel image. We cannot prevent this anyway. So any
	 * node the kernel resides in should be un-hotpluggable.
	 *
	 * And when we come here, alloc node data won't fail.
	 */
	numa_clear_kernel_node_hotplug();

	/*
	 * If sections array is gonna be used क्रम pfn -> nid mapping, check
	 * whether its granularity is fine enough.
	 */
	अगर (IS_ENABLED(NODE_NOT_IN_PAGE_FLAGS)) अणु
		अचिन्हित दीर्घ pfn_align = node_map_pfn_alignment();

		अगर (pfn_align && pfn_align < PAGES_PER_SECTION) अणु
			pr_warn("Node alignment %LuMB < min %LuMB, rejecting NUMA config\n",
				PFN_PHYS(pfn_align) >> 20,
				PFN_PHYS(PAGES_PER_SECTION) >> 20);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (!numa_meminfo_cover_memory(mi))
		वापस -EINVAL;

	/* Finally रेजिस्टर nodes. */
	क्रम_each_node_mask(nid, node_possible_map) अणु
		u64 start = PFN_PHYS(max_pfn);
		u64 end = 0;

		क्रम (i = 0; i < mi->nr_blks; i++) अणु
			अगर (nid != mi->blk[i].nid)
				जारी;
			start = min(mi->blk[i].start, start);
			end = max(mi->blk[i].end, end);
		पूर्ण

		अगर (start >= end)
			जारी;

		/*
		 * Don't confuse VM with a node that doesn't have the
		 * minimum amount of memory:
		 */
		अगर (end && (end - start) < NODE_MIN_SIZE)
			जारी;

		alloc_node_data(nid);
	पूर्ण

	/* Dump memblock with node info and वापस. */
	memblock_dump_all();
	वापस 0;
पूर्ण

/*
 * There are unक्रमtunately some poorly deचिन्हित मुख्यboards around that
 * only connect memory to a single CPU. This अवरोधs the 1:1 cpu->node
 * mapping. To aव्योम this fill in the mapping क्रम all possible CPUs,
 * as the number of CPUs is not known yet. We round robin the existing
 * nodes.
 */
अटल व्योम __init numa_init_array(व्योम)
अणु
	पूर्णांक rr, i;

	rr = first_node(node_online_map);
	क्रम (i = 0; i < nr_cpu_ids; i++) अणु
		अगर (early_cpu_to_node(i) != NUMA_NO_NODE)
			जारी;
		numa_set_node(i, rr);
		rr = next_node_in(rr, node_online_map);
	पूर्ण
पूर्ण

अटल पूर्णांक __init numa_init(पूर्णांक (*init_func)(व्योम))
अणु
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < MAX_LOCAL_APIC; i++)
		set_apicid_to_node(i, NUMA_NO_NODE);

	nodes_clear(numa_nodes_parsed);
	nodes_clear(node_possible_map);
	nodes_clear(node_online_map);
	स_रखो(&numa_meminfo, 0, माप(numa_meminfo));
	WARN_ON(memblock_set_node(0, ULदीर्घ_उच्च, &memblock.memory,
				  MAX_NUMNODES));
	WARN_ON(memblock_set_node(0, ULदीर्घ_उच्च, &memblock.reserved,
				  MAX_NUMNODES));
	/* In हाल that parsing SRAT failed. */
	WARN_ON(memblock_clear_hotplug(0, ULदीर्घ_उच्च));
	numa_reset_distance();

	ret = init_func();
	अगर (ret < 0)
		वापस ret;

	/*
	 * We reset memblock back to the top-करोwn direction
	 * here because अगर we configured ACPI_NUMA, we have
	 * parsed SRAT in init_func(). It is ok to have the
	 * reset here even अगर we did't configure ACPI_NUMA
	 * or acpi numa init fails and fallbacks to dummy
	 * numa init.
	 */
	memblock_set_bottom_up(false);

	ret = numa_cleanup_meminfo(&numa_meminfo);
	अगर (ret < 0)
		वापस ret;

	numa_emulation(&numa_meminfo, numa_distance_cnt);

	ret = numa_रेजिस्टर_memblks(&numa_meminfo);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < nr_cpu_ids; i++) अणु
		पूर्णांक nid = early_cpu_to_node(i);

		अगर (nid == NUMA_NO_NODE)
			जारी;
		अगर (!node_online(nid))
			numa_clear_node(i);
	पूर्ण
	numa_init_array();

	वापस 0;
पूर्ण

/**
 * dummy_numa_init - Fallback dummy NUMA init
 *
 * Used अगर there's no underlying NUMA architecture, NUMA initialization
 * fails, or NUMA is disabled on the command line.
 *
 * Must online at least one node and add memory blocks that cover all
 * allowed memory.  This function must not fail.
 */
अटल पूर्णांक __init dummy_numa_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "%s\n",
	       numa_off ? "NUMA turned off" : "No NUMA configuration found");
	prपूर्णांकk(KERN_INFO "Faking a node at [mem %#018Lx-%#018Lx]\n",
	       0LLU, PFN_PHYS(max_pfn) - 1);

	node_set(0, numa_nodes_parsed);
	numa_add_memblk(0, 0, PFN_PHYS(max_pfn));

	वापस 0;
पूर्ण

/**
 * x86_numa_init - Initialize NUMA
 *
 * Try each configured NUMA initialization method until one succeeds.  The
 * last fallback is dummy single node config encompassing whole memory and
 * never fails.
 */
व्योम __init x86_numa_init(व्योम)
अणु
	अगर (!numa_off) अणु
#अगर_घोषित CONFIG_ACPI_NUMA
		अगर (!numa_init(x86_acpi_numa_init))
			वापस;
#पूर्ण_अगर
#अगर_घोषित CONFIG_AMD_NUMA
		अगर (!numa_init(amd_numa_init))
			वापस;
#पूर्ण_अगर
	पूर्ण

	numa_init(dummy_numa_init);
पूर्ण

अटल व्योम __init init_memory_less_node(पूर्णांक nid)
अणु
	/* Allocate and initialize node data. Memory-less node is now online.*/
	alloc_node_data(nid);
	मुक्त_area_init_memoryless_node(nid);

	/*
	 * All zonelists will be built later in start_kernel() after per cpu
	 * areas are initialized.
	 */
पूर्ण

/*
 * A node may exist which has one or more Generic Initiators but no CPUs and no
 * memory.
 *
 * This function must be called after init_cpu_to_node(), to ensure that any
 * memoryless CPU nodes have alपढ़ोy been brought online, and beक्रमe the
 * node_data[nid] is needed क्रम zone list setup in build_all_zonelists().
 *
 * When this function is called, any nodes containing either memory and/or CPUs
 * will alपढ़ोy be online and there is no need to करो anything extra, even अगर
 * they also contain one or more Generic Initiators.
 */
व्योम __init init_gi_nodes(व्योम)
अणु
	पूर्णांक nid;

	क्रम_each_node_state(nid, N_GENERIC_INITIATOR)
		अगर (!node_online(nid))
			init_memory_less_node(nid);
पूर्ण

/*
 * Setup early cpu_to_node.
 *
 * Populate cpu_to_node[] only अगर x86_cpu_to_apicid[],
 * and apicid_to_node[] tables have valid entries क्रम a CPU.
 * This means we skip cpu_to_node[] initialisation क्रम NUMA
 * emulation and faking node हाल (when running a kernel compiled
 * क्रम NUMA on a non NUMA box), which is OK as cpu_to_node[]
 * is alपढ़ोy initialized in a round robin manner at numa_init_array,
 * prior to this call, and this initialization is good enough
 * क्रम the fake NUMA हालs.
 *
 * Called beक्रमe the per_cpu areas are setup.
 */
व्योम __init init_cpu_to_node(व्योम)
अणु
	पूर्णांक cpu;
	u16 *cpu_to_apicid = early_per_cpu_ptr(x86_cpu_to_apicid);

	BUG_ON(cpu_to_apicid == शून्य);

	क्रम_each_possible_cpu(cpu) अणु
		पूर्णांक node = numa_cpu_node(cpu);

		अगर (node == NUMA_NO_NODE)
			जारी;

		अगर (!node_online(node))
			init_memory_less_node(node);

		numa_set_node(cpu, node);
	पूर्ण
पूर्ण

#अगर_अघोषित CONFIG_DEBUG_PER_CPU_MAPS

# अगरndef CONFIG_NUMA_EMU
व्योम numa_add_cpu(पूर्णांक cpu)
अणु
	cpumask_set_cpu(cpu, node_to_cpumask_map[early_cpu_to_node(cpu)]);
पूर्ण

व्योम numa_हटाओ_cpu(पूर्णांक cpu)
अणु
	cpumask_clear_cpu(cpu, node_to_cpumask_map[early_cpu_to_node(cpu)]);
पूर्ण
# endअगर	/* !CONFIG_NUMA_EMU */

#अन्यथा	/* !CONFIG_DEBUG_PER_CPU_MAPS */

पूर्णांक __cpu_to_node(पूर्णांक cpu)
अणु
	अगर (early_per_cpu_ptr(x86_cpu_to_node_map)) अणु
		prपूर्णांकk(KERN_WARNING
			"cpu_to_node(%d): usage too early!\n", cpu);
		dump_stack();
		वापस early_per_cpu_ptr(x86_cpu_to_node_map)[cpu];
	पूर्ण
	वापस per_cpu(x86_cpu_to_node_map, cpu);
पूर्ण
EXPORT_SYMBOL(__cpu_to_node);

/*
 * Same function as cpu_to_node() but used अगर called beक्रमe the
 * per_cpu areas are setup.
 */
पूर्णांक early_cpu_to_node(पूर्णांक cpu)
अणु
	अगर (early_per_cpu_ptr(x86_cpu_to_node_map))
		वापस early_per_cpu_ptr(x86_cpu_to_node_map)[cpu];

	अगर (!cpu_possible(cpu)) अणु
		prपूर्णांकk(KERN_WARNING
			"early_cpu_to_node(%d): no per_cpu area!\n", cpu);
		dump_stack();
		वापस NUMA_NO_NODE;
	पूर्ण
	वापस per_cpu(x86_cpu_to_node_map, cpu);
पूर्ण

व्योम debug_cpumask_set_cpu(पूर्णांक cpu, पूर्णांक node, bool enable)
अणु
	काष्ठा cpumask *mask;

	अगर (node == NUMA_NO_NODE) अणु
		/* early_cpu_to_node() alपढ़ोy emits a warning and trace */
		वापस;
	पूर्ण
	mask = node_to_cpumask_map[node];
	अगर (!mask) अणु
		pr_err("node_to_cpumask_map[%i] NULL\n", node);
		dump_stack();
		वापस;
	पूर्ण

	अगर (enable)
		cpumask_set_cpu(cpu, mask);
	अन्यथा
		cpumask_clear_cpu(cpu, mask);

	prपूर्णांकk(KERN_DEBUG "%s cpu %d node %d: mask now %*pbl\n",
		enable ? "numa_add_cpu" : "numa_remove_cpu",
		cpu, node, cpumask_pr_args(mask));
	वापस;
पूर्ण

# अगरndef CONFIG_NUMA_EMU
अटल व्योम numa_set_cpumask(पूर्णांक cpu, bool enable)
अणु
	debug_cpumask_set_cpu(cpu, early_cpu_to_node(cpu), enable);
पूर्ण

व्योम numa_add_cpu(पूर्णांक cpu)
अणु
	numa_set_cpumask(cpu, true);
पूर्ण

व्योम numa_हटाओ_cpu(पूर्णांक cpu)
अणु
	numa_set_cpumask(cpu, false);
पूर्ण
# endअगर	/* !CONFIG_NUMA_EMU */

/*
 * Returns a poपूर्णांकer to the biपंचांगask of CPUs on Node 'node'.
 */
स्थिर काष्ठा cpumask *cpumask_of_node(पूर्णांक node)
अणु
	अगर ((अचिन्हित)node >= nr_node_ids) अणु
		prपूर्णांकk(KERN_WARNING
			"cpumask_of_node(%d): (unsigned)node >= nr_node_ids(%u)\n",
			node, nr_node_ids);
		dump_stack();
		वापस cpu_none_mask;
	पूर्ण
	अगर (node_to_cpumask_map[node] == शून्य) अणु
		prपूर्णांकk(KERN_WARNING
			"cpumask_of_node(%d): no node_to_cpumask_map!\n",
			node);
		dump_stack();
		वापस cpu_online_mask;
	पूर्ण
	वापस node_to_cpumask_map[node];
पूर्ण
EXPORT_SYMBOL(cpumask_of_node);

#पूर्ण_अगर	/* !CONFIG_DEBUG_PER_CPU_MAPS */

#अगर_घोषित CONFIG_NUMA_KEEP_MEMINFO
अटल पूर्णांक meminfo_to_nid(काष्ठा numa_meminfo *mi, u64 start)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mi->nr_blks; i++)
		अगर (mi->blk[i].start <= start && mi->blk[i].end > start)
			वापस mi->blk[i].nid;
	वापस NUMA_NO_NODE;
पूर्ण

पूर्णांक phys_to_target_node(phys_addr_t start)
अणु
	पूर्णांक nid = meminfo_to_nid(&numa_meminfo, start);

	/*
	 * Prefer online nodes, but अगर reserved memory might be
	 * hot-added जारी the search with reserved ranges.
	 */
	अगर (nid != NUMA_NO_NODE)
		वापस nid;

	वापस meminfo_to_nid(&numa_reserved_meminfo, start);
पूर्ण
EXPORT_SYMBOL_GPL(phys_to_target_node);

पूर्णांक memory_add_physaddr_to_nid(u64 start)
अणु
	पूर्णांक nid = meminfo_to_nid(&numa_meminfo, start);

	अगर (nid == NUMA_NO_NODE)
		nid = numa_meminfo.blk[0].nid;
	वापस nid;
पूर्ण
EXPORT_SYMBOL_GPL(memory_add_physaddr_to_nid);
#पूर्ण_अगर
