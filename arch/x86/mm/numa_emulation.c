<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NUMA emulation
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/topology.h>
#समावेश <linux/memblock.h>
#समावेश <यंत्र/dma.h>

#समावेश "numa_internal.h"

अटल पूर्णांक emu_nid_to_phys[MAX_NUMNODES];
अटल अक्षर *emu_cmdline __initdata;

पूर्णांक __init numa_emu_cmdline(अक्षर *str)
अणु
	emu_cmdline = str;
	वापस 0;
पूर्ण

अटल पूर्णांक __init emu_find_memblk_by_nid(पूर्णांक nid, स्थिर काष्ठा numa_meminfo *mi)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mi->nr_blks; i++)
		अगर (mi->blk[i].nid == nid)
			वापस i;
	वापस -ENOENT;
पूर्ण

अटल u64 __init mem_hole_size(u64 start, u64 end)
अणु
	अचिन्हित दीर्घ start_pfn = PFN_UP(start);
	अचिन्हित दीर्घ end_pfn = PFN_DOWN(end);

	अगर (start_pfn < end_pfn)
		वापस PFN_PHYS(असलent_pages_in_range(start_pfn, end_pfn));
	वापस 0;
पूर्ण

/*
 * Sets up nid to range from @start to @end.  The वापस value is -त्रुटि_सं अगर
 * something went wrong, 0 otherwise.
 */
अटल पूर्णांक __init emu_setup_memblk(काष्ठा numa_meminfo *ei,
				   काष्ठा numa_meminfo *pi,
				   पूर्णांक nid, पूर्णांक phys_blk, u64 size)
अणु
	काष्ठा numa_memblk *eb = &ei->blk[ei->nr_blks];
	काष्ठा numa_memblk *pb = &pi->blk[phys_blk];

	अगर (ei->nr_blks >= NR_NODE_MEMBLKS) अणु
		pr_err("NUMA: Too many emulated memblks, failing emulation\n");
		वापस -EINVAL;
	पूर्ण

	ei->nr_blks++;
	eb->start = pb->start;
	eb->end = pb->start + size;
	eb->nid = nid;

	अगर (emu_nid_to_phys[nid] == NUMA_NO_NODE)
		emu_nid_to_phys[nid] = pb->nid;

	pb->start += size;
	अगर (pb->start >= pb->end) अणु
		WARN_ON_ONCE(pb->start > pb->end);
		numa_हटाओ_memblk_from(phys_blk, pi);
	पूर्ण

	prपूर्णांकk(KERN_INFO "Faking node %d at [mem %#018Lx-%#018Lx] (%LuMB)\n",
	       nid, eb->start, eb->end - 1, (eb->end - eb->start) >> 20);
	वापस 0;
पूर्ण

/*
 * Sets up nr_nodes fake nodes पूर्णांकerleaved over physical nodes ranging from addr
 * to max_addr.
 *
 * Returns zero on success or negative on error.
 */
अटल पूर्णांक __init split_nodes_पूर्णांकerleave(काष्ठा numa_meminfo *ei,
					 काष्ठा numa_meminfo *pi,
					 u64 addr, u64 max_addr, पूर्णांक nr_nodes)
अणु
	nodemask_t physnode_mask = numa_nodes_parsed;
	u64 size;
	पूर्णांक big;
	पूर्णांक nid = 0;
	पूर्णांक i, ret;

	अगर (nr_nodes <= 0)
		वापस -1;
	अगर (nr_nodes > MAX_NUMNODES) अणु
		pr_info("numa=fake=%d too large, reducing to %d\n",
			nr_nodes, MAX_NUMNODES);
		nr_nodes = MAX_NUMNODES;
	पूर्ण

	/*
	 * Calculate target node size.  x86_32 freaks on __uभागdi3() so करो
	 * the भागision in uदीर्घ number of pages and convert back.
	 */
	size = max_addr - addr - mem_hole_size(addr, max_addr);
	size = PFN_PHYS((अचिन्हित दीर्घ)(size >> PAGE_SHIFT) / nr_nodes);

	/*
	 * Calculate the number of big nodes that can be allocated as a result
	 * of consolidating the reमुख्यder.
	 */
	big = ((size & ~FAKE_NODE_MIN_HASH_MASK) * nr_nodes) /
		FAKE_NODE_MIN_SIZE;

	size &= FAKE_NODE_MIN_HASH_MASK;
	अगर (!size) अणु
		pr_err("Not enough memory for each node.  "
			"NUMA emulation disabled.\n");
		वापस -1;
	पूर्ण

	/*
	 * Continue to fill physical nodes with fake nodes until there is no
	 * memory left on any of them.
	 */
	जबतक (nodes_weight(physnode_mask)) अणु
		क्रम_each_node_mask(i, physnode_mask) अणु
			u64 dma32_end = PFN_PHYS(MAX_DMA32_PFN);
			u64 start, limit, end;
			पूर्णांक phys_blk;

			phys_blk = emu_find_memblk_by_nid(i, pi);
			अगर (phys_blk < 0) अणु
				node_clear(i, physnode_mask);
				जारी;
			पूर्ण
			start = pi->blk[phys_blk].start;
			limit = pi->blk[phys_blk].end;
			end = start + size;

			अगर (nid < big)
				end += FAKE_NODE_MIN_SIZE;

			/*
			 * Continue to add memory to this fake node अगर its
			 * non-reserved memory is less than the per-node size.
			 */
			जबतक (end - start - mem_hole_size(start, end) < size) अणु
				end += FAKE_NODE_MIN_SIZE;
				अगर (end > limit) अणु
					end = limit;
					अवरोध;
				पूर्ण
			पूर्ण

			/*
			 * If there won't be at least FAKE_NODE_MIN_SIZE of
			 * non-reserved memory in ZONE_DMA32 क्रम the next node,
			 * this one must extend to the boundary.
			 */
			अगर (end < dma32_end && dma32_end - end -
			    mem_hole_size(end, dma32_end) < FAKE_NODE_MIN_SIZE)
				end = dma32_end;

			/*
			 * If there won't be enough non-reserved memory क्रम the
			 * next node, this one must extend to the end of the
			 * physical node.
			 */
			अगर (limit - end - mem_hole_size(end, limit) < size)
				end = limit;

			ret = emu_setup_memblk(ei, pi, nid++ % nr_nodes,
					       phys_blk,
					       min(end, limit) - start);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Returns the end address of a node so that there is at least `size' amount of
 * non-reserved memory or `max_addr' is reached.
 */
अटल u64 __init find_end_of_node(u64 start, u64 max_addr, u64 size)
अणु
	u64 end = start + size;

	जबतक (end - start - mem_hole_size(start, end) < size) अणु
		end += FAKE_NODE_MIN_SIZE;
		अगर (end > max_addr) अणु
			end = max_addr;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस end;
पूर्ण

अटल u64 unअगरorm_size(u64 max_addr, u64 base, u64 hole, पूर्णांक nr_nodes)
अणु
	अचिन्हित दीर्घ max_pfn = PHYS_PFN(max_addr);
	अचिन्हित दीर्घ base_pfn = PHYS_PFN(base);
	अचिन्हित दीर्घ hole_pfns = PHYS_PFN(hole);

	वापस PFN_PHYS((max_pfn - base_pfn - hole_pfns) / nr_nodes);
पूर्ण

/*
 * Sets up fake nodes of `size' पूर्णांकerleaved over physical nodes ranging from
 * `addr' to `max_addr'.
 *
 * Returns zero on success or negative on error.
 */
अटल पूर्णांक __init split_nodes_size_पूर्णांकerleave_unअगरorm(काष्ठा numa_meminfo *ei,
					      काष्ठा numa_meminfo *pi,
					      u64 addr, u64 max_addr, u64 size,
					      पूर्णांक nr_nodes, काष्ठा numa_memblk *pblk,
					      पूर्णांक nid)
अणु
	nodemask_t physnode_mask = numa_nodes_parsed;
	पूर्णांक i, ret, unअगरorm = 0;
	u64 min_size;

	अगर ((!size && !nr_nodes) || (nr_nodes && !pblk))
		वापस -1;

	/*
	 * In the 'uniform' हाल split the passed in physical node by
	 * nr_nodes, in the non-unअगरorm हाल, ignore the passed in
	 * physical block and try to create nodes of at least size
	 * @size.
	 *
	 * In the unअगरorm हाल, split the nodes strictly by physical
	 * capacity, i.e. ignore holes. In the non-unअगरorm हाल account
	 * क्रम holes and treat @size as a minimum न्यूनमान.
	 */
	अगर (!nr_nodes)
		nr_nodes = MAX_NUMNODES;
	अन्यथा अणु
		nodes_clear(physnode_mask);
		node_set(pblk->nid, physnode_mask);
		unअगरorm = 1;
	पूर्ण

	अगर (unअगरorm) अणु
		min_size = unअगरorm_size(max_addr, addr, 0, nr_nodes);
		size = min_size;
	पूर्ण अन्यथा अणु
		/*
		 * The limit on emulated nodes is MAX_NUMNODES, so the
		 * size per node is increased accordingly अगर the
		 * requested size is too small.  This creates a unअगरorm
		 * distribution of node sizes across the entire machine
		 * (but not necessarily over physical nodes).
		 */
		min_size = unअगरorm_size(max_addr, addr,
				mem_hole_size(addr, max_addr), nr_nodes);
	पूर्ण
	min_size = ALIGN(max(min_size, FAKE_NODE_MIN_SIZE), FAKE_NODE_MIN_SIZE);
	अगर (size < min_size) अणु
		pr_err("Fake node size %LuMB too small, increasing to %LuMB\n",
			size >> 20, min_size >> 20);
		size = min_size;
	पूर्ण
	size = ALIGN_DOWN(size, FAKE_NODE_MIN_SIZE);

	/*
	 * Fill physical nodes with fake nodes of size until there is no memory
	 * left on any of them.
	 */
	जबतक (nodes_weight(physnode_mask)) अणु
		क्रम_each_node_mask(i, physnode_mask) अणु
			u64 dma32_end = PFN_PHYS(MAX_DMA32_PFN);
			u64 start, limit, end;
			पूर्णांक phys_blk;

			phys_blk = emu_find_memblk_by_nid(i, pi);
			अगर (phys_blk < 0) अणु
				node_clear(i, physnode_mask);
				जारी;
			पूर्ण

			start = pi->blk[phys_blk].start;
			limit = pi->blk[phys_blk].end;

			अगर (unअगरorm)
				end = start + size;
			अन्यथा
				end = find_end_of_node(start, limit, size);
			/*
			 * If there won't be at least FAKE_NODE_MIN_SIZE of
			 * non-reserved memory in ZONE_DMA32 क्रम the next node,
			 * this one must extend to the boundary.
			 */
			अगर (end < dma32_end && dma32_end - end -
			    mem_hole_size(end, dma32_end) < FAKE_NODE_MIN_SIZE)
				end = dma32_end;

			/*
			 * If there won't be enough non-reserved memory क्रम the
			 * next node, this one must extend to the end of the
			 * physical node.
			 */
			अगर ((limit - end - mem_hole_size(end, limit) < size)
					&& !unअगरorm)
				end = limit;

			ret = emu_setup_memblk(ei, pi, nid++ % MAX_NUMNODES,
					       phys_blk,
					       min(end, limit) - start);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण
	वापस nid;
पूर्ण

अटल पूर्णांक __init split_nodes_size_पूर्णांकerleave(काष्ठा numa_meminfo *ei,
					      काष्ठा numa_meminfo *pi,
					      u64 addr, u64 max_addr, u64 size)
अणु
	वापस split_nodes_size_पूर्णांकerleave_unअगरorm(ei, pi, addr, max_addr, size,
			0, शून्य, 0);
पूर्ण

अटल पूर्णांक __init setup_emu2phys_nid(पूर्णांक *dfl_phys_nid)
अणु
	पूर्णांक i, max_emu_nid = 0;

	*dfl_phys_nid = NUMA_NO_NODE;
	क्रम (i = 0; i < ARRAY_SIZE(emu_nid_to_phys); i++) अणु
		अगर (emu_nid_to_phys[i] != NUMA_NO_NODE) अणु
			max_emu_nid = i;
			अगर (*dfl_phys_nid == NUMA_NO_NODE)
				*dfl_phys_nid = emu_nid_to_phys[i];
		पूर्ण
	पूर्ण

	वापस max_emu_nid;
पूर्ण

/**
 * numa_emulation - Emulate NUMA nodes
 * @numa_meminfo: NUMA configuration to massage
 * @numa_dist_cnt: The size of the physical NUMA distance table
 *
 * Emulate NUMA nodes according to the numa=fake kernel parameter.
 * @numa_meminfo contains the physical memory configuration and is modअगरied
 * to reflect the emulated configuration on success.  @numa_dist_cnt is
 * used to determine the size of the physical distance table.
 *
 * On success, the following modअगरications are made.
 *
 * - @numa_meminfo is updated to reflect the emulated nodes.
 *
 * - __apicid_to_node[] is updated such that APIC IDs are mapped to the
 *   emulated nodes.
 *
 * - NUMA distance table is rebuilt to represent distances between emulated
 *   nodes.  The distances are determined considering how emulated nodes
 *   are mapped to physical nodes and match the actual distances.
 *
 * - emu_nid_to_phys[] reflects how emulated nodes are mapped to physical
 *   nodes.  This is used by numa_add_cpu() and numa_हटाओ_cpu().
 *
 * If emulation is not enabled or fails, emu_nid_to_phys[] is filled with
 * identity mapping and no other modअगरication is made.
 */
व्योम __init numa_emulation(काष्ठा numa_meminfo *numa_meminfo, पूर्णांक numa_dist_cnt)
अणु
	अटल काष्ठा numa_meminfo ei __initdata;
	अटल काष्ठा numa_meminfo pi __initdata;
	स्थिर u64 max_addr = PFN_PHYS(max_pfn);
	u8 *phys_dist = शून्य;
	माप_प्रकार phys_size = numa_dist_cnt * numa_dist_cnt * माप(phys_dist[0]);
	पूर्णांक max_emu_nid, dfl_phys_nid;
	पूर्णांक i, j, ret;

	अगर (!emu_cmdline)
		जाओ no_emu;

	स_रखो(&ei, 0, माप(ei));
	pi = *numa_meminfo;

	क्रम (i = 0; i < MAX_NUMNODES; i++)
		emu_nid_to_phys[i] = NUMA_NO_NODE;

	/*
	 * If the numa=fake command-line contains a 'M' or 'G', it represents
	 * the fixed node size.  Otherwise, अगर it is just a single number N,
	 * split the प्रणाली RAM पूर्णांकo N fake nodes.
	 */
	अगर (म_अक्षर(emu_cmdline, 'U')) अणु
		nodemask_t physnode_mask = numa_nodes_parsed;
		अचिन्हित दीर्घ n;
		पूर्णांक nid = 0;

		n = simple_म_से_अदीर्घ(emu_cmdline, &emu_cmdline, 0);
		ret = -1;
		क्रम_each_node_mask(i, physnode_mask) अणु
			/*
			 * The reason we pass in blk[0] is due to
			 * numa_हटाओ_memblk_from() called by
			 * emu_setup_memblk() will delete entry 0
			 * and then move everything अन्यथा up in the pi.blk
			 * array. Thereक्रमe we should always be looking
			 * at blk[0].
			 */
			ret = split_nodes_size_पूर्णांकerleave_unअगरorm(&ei, &pi,
					pi.blk[0].start, pi.blk[0].end, 0,
					n, &pi.blk[0], nid);
			अगर (ret < 0)
				अवरोध;
			अगर (ret < n) अणु
				pr_info("%s: phys: %d only got %d of %ld nodes, failing\n",
						__func__, i, ret, n);
				ret = -1;
				अवरोध;
			पूर्ण
			nid = ret;
		पूर्ण
	पूर्ण अन्यथा अगर (म_अक्षर(emu_cmdline, 'M') || strchr(emu_cmdline, 'G')) अणु
		u64 size;

		size = memparse(emu_cmdline, &emu_cmdline);
		ret = split_nodes_size_पूर्णांकerleave(&ei, &pi, 0, max_addr, size);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ n;

		n = simple_म_से_अदीर्घ(emu_cmdline, &emu_cmdline, 0);
		ret = split_nodes_पूर्णांकerleave(&ei, &pi, 0, max_addr, n);
	पूर्ण
	अगर (*emu_cmdline == ':')
		emu_cmdline++;

	अगर (ret < 0)
		जाओ no_emu;

	अगर (numa_cleanup_meminfo(&ei) < 0) अणु
		pr_warn("NUMA: Warning: constructed meminfo invalid, disabling emulation\n");
		जाओ no_emu;
	पूर्ण

	/* copy the physical distance table */
	अगर (numa_dist_cnt) अणु
		u64 phys;

		phys = memblock_find_in_range(0, PFN_PHYS(max_pfn_mapped),
					      phys_size, PAGE_SIZE);
		अगर (!phys) अणु
			pr_warn("NUMA: Warning: can't allocate copy of distance table, disabling emulation\n");
			जाओ no_emu;
		पूर्ण
		memblock_reserve(phys, phys_size);
		phys_dist = __va(phys);

		क्रम (i = 0; i < numa_dist_cnt; i++)
			क्रम (j = 0; j < numa_dist_cnt; j++)
				phys_dist[i * numa_dist_cnt + j] =
					node_distance(i, j);
	पूर्ण

	/*
	 * Determine the max emulated nid and the शेष phys nid to use
	 * क्रम unmapped nodes.
	 */
	max_emu_nid = setup_emu2phys_nid(&dfl_phys_nid);

	/* commit */
	*numa_meminfo = ei;

	/* Make sure numa_nodes_parsed only contains emulated nodes */
	nodes_clear(numa_nodes_parsed);
	क्रम (i = 0; i < ARRAY_SIZE(ei.blk); i++)
		अगर (ei.blk[i].start != ei.blk[i].end &&
		    ei.blk[i].nid != NUMA_NO_NODE)
			node_set(ei.blk[i].nid, numa_nodes_parsed);

	/*
	 * Transक्रमm __apicid_to_node table to use emulated nids by
	 * reverse-mapping phys_nid.  The maps should always exist but fall
	 * back to zero just in हाल.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(__apicid_to_node); i++) अणु
		अगर (__apicid_to_node[i] == NUMA_NO_NODE)
			जारी;
		क्रम (j = 0; j < ARRAY_SIZE(emu_nid_to_phys); j++)
			अगर (__apicid_to_node[i] == emu_nid_to_phys[j])
				अवरोध;
		__apicid_to_node[i] = j < ARRAY_SIZE(emu_nid_to_phys) ? j : 0;
	पूर्ण

	/* make sure all emulated nodes are mapped to a physical node */
	क्रम (i = 0; i < ARRAY_SIZE(emu_nid_to_phys); i++)
		अगर (emu_nid_to_phys[i] == NUMA_NO_NODE)
			emu_nid_to_phys[i] = dfl_phys_nid;

	/* transक्रमm distance table */
	numa_reset_distance();
	क्रम (i = 0; i < max_emu_nid + 1; i++) अणु
		क्रम (j = 0; j < max_emu_nid + 1; j++) अणु
			पूर्णांक physi = emu_nid_to_phys[i];
			पूर्णांक physj = emu_nid_to_phys[j];
			पूर्णांक dist;

			अगर (get_option(&emu_cmdline, &dist) == 2)
				;
			अन्यथा अगर (physi >= numa_dist_cnt || physj >= numa_dist_cnt)
				dist = physi == physj ?
					LOCAL_DISTANCE : REMOTE_DISTANCE;
			अन्यथा
				dist = phys_dist[physi * numa_dist_cnt + physj];

			numa_set_distance(i, j, dist);
		पूर्ण
	पूर्ण

	/* मुक्त the copied physical distance table */
	अगर (phys_dist)
		memblock_मुक्त(__pa(phys_dist), phys_size);
	वापस;

no_emu:
	/* No emulation.  Build identity emu_nid_to_phys[] क्रम numa_add_cpu() */
	क्रम (i = 0; i < ARRAY_SIZE(emu_nid_to_phys); i++)
		emu_nid_to_phys[i] = i;
पूर्ण

#अगर_अघोषित CONFIG_DEBUG_PER_CPU_MAPS
व्योम numa_add_cpu(पूर्णांक cpu)
अणु
	पूर्णांक physnid, nid;

	nid = early_cpu_to_node(cpu);
	BUG_ON(nid == NUMA_NO_NODE || !node_online(nid));

	physnid = emu_nid_to_phys[nid];

	/*
	 * Map the cpu to each emulated node that is allocated on the physical
	 * node of the cpu's apic id.
	 */
	क्रम_each_online_node(nid)
		अगर (emu_nid_to_phys[nid] == physnid)
			cpumask_set_cpu(cpu, node_to_cpumask_map[nid]);
पूर्ण

व्योम numa_हटाओ_cpu(पूर्णांक cpu)
अणु
	पूर्णांक i;

	क्रम_each_online_node(i)
		cpumask_clear_cpu(cpu, node_to_cpumask_map[i]);
पूर्ण
#अन्यथा	/* !CONFIG_DEBUG_PER_CPU_MAPS */
अटल व्योम numa_set_cpumask(पूर्णांक cpu, bool enable)
अणु
	पूर्णांक nid, physnid;

	nid = early_cpu_to_node(cpu);
	अगर (nid == NUMA_NO_NODE) अणु
		/* early_cpu_to_node() alपढ़ोy emits a warning and trace */
		वापस;
	पूर्ण

	physnid = emu_nid_to_phys[nid];

	क्रम_each_online_node(nid) अणु
		अगर (emu_nid_to_phys[nid] != physnid)
			जारी;

		debug_cpumask_set_cpu(cpu, nid, enable);
	पूर्ण
पूर्ण

व्योम numa_add_cpu(पूर्णांक cpu)
अणु
	numa_set_cpumask(cpu, true);
पूर्ण

व्योम numa_हटाओ_cpu(पूर्णांक cpu)
अणु
	numa_set_cpumask(cpu, false);
पूर्ण
#पूर्ण_अगर	/* !CONFIG_DEBUG_PER_CPU_MAPS */
