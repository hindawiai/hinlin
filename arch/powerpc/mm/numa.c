<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pSeries NUMA support
 *
 * Copyright (C) 2002 Anton Blanअक्षरd <anton@au.ibm.com>, IBM
 */
#घोषणा pr_fmt(fmt) "numa: " fmt

#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/memblock.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/export.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/cpu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>
#समावेश <linux/pfn.h>
#समावेश <linux/cpuset.h>
#समावेश <linux/node.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/sparseस्मृति.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/topology.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/paca.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/vdso.h>
#समावेश <यंत्र/drस्मृति.स>

अटल पूर्णांक numa_enabled = 1;

अटल अक्षर *cmdline __initdata;

अटल पूर्णांक numa_debug;
#घोषणा dbg(args...) अगर (numa_debug) अणु prपूर्णांकk(KERN_INFO args); पूर्ण

पूर्णांक numa_cpu_lookup_table[NR_CPUS];
cpumask_var_t node_to_cpumask_map[MAX_NUMNODES];
काष्ठा pglist_data *node_data[MAX_NUMNODES];

EXPORT_SYMBOL(numa_cpu_lookup_table);
EXPORT_SYMBOL(node_to_cpumask_map);
EXPORT_SYMBOL(node_data);

अटल पूर्णांक min_common_depth;
अटल पूर्णांक n_mem_addr_cells, n_mem_size_cells;
अटल पूर्णांक क्रमm1_affinity;

#घोषणा MAX_DISTANCE_REF_POINTS 4
अटल पूर्णांक distance_ref_poपूर्णांकs_depth;
अटल स्थिर __be32 *distance_ref_poपूर्णांकs;
अटल पूर्णांक distance_lookup_table[MAX_NUMNODES][MAX_DISTANCE_REF_POINTS];

/*
 * Allocate node_to_cpumask_map based on number of available nodes
 * Requires node_possible_map to be valid.
 *
 * Note: cpumask_of_node() is not valid until after this is करोne.
 */
अटल व्योम __init setup_node_to_cpumask_map(व्योम)
अणु
	अचिन्हित पूर्णांक node;

	/* setup nr_node_ids अगर not करोne yet */
	अगर (nr_node_ids == MAX_NUMNODES)
		setup_nr_node_ids();

	/* allocate the map */
	क्रम_each_node(node)
		alloc_booपंचांगem_cpumask_var(&node_to_cpumask_map[node]);

	/* cpumask_of_node() will now work */
	dbg("Node to cpumask map for %u nodes\n", nr_node_ids);
पूर्ण

अटल पूर्णांक __init fake_numa_create_new_node(अचिन्हित दीर्घ end_pfn,
						अचिन्हित पूर्णांक *nid)
अणु
	अचिन्हित दीर्घ दीर्घ mem;
	अक्षर *p = cmdline;
	अटल अचिन्हित पूर्णांक fake_nid;
	अटल अचिन्हित दीर्घ दीर्घ curr_boundary;

	/*
	 * Modअगरy node id, अगरf we started creating NUMA nodes
	 * We want to जारी from where we left of the last समय
	 */
	अगर (fake_nid)
		*nid = fake_nid;
	/*
	 * In हाल there are no more arguments to parse, the
	 * node_id should be the same as the last fake node id
	 * (we've handled this above).
	 */
	अगर (!p)
		वापस 0;

	mem = memparse(p, &p);
	अगर (!mem)
		वापस 0;

	अगर (mem < curr_boundary)
		वापस 0;

	curr_boundary = mem;

	अगर ((end_pfn << PAGE_SHIFT) > mem) अणु
		/*
		 * Skip commas and spaces
		 */
		जबतक (*p == ',' || *p == ' ' || *p == '\t')
			p++;

		cmdline = p;
		fake_nid++;
		*nid = fake_nid;
		dbg("created new fake_node with id %d\n", fake_nid);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम reset_numa_cpu_lookup_table(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		numa_cpu_lookup_table[cpu] = -1;
पूर्ण

अटल व्योम map_cpu_to_node(पूर्णांक cpu, पूर्णांक node)
अणु
	update_numa_cpu_lookup_table(cpu, node);

	dbg("adding cpu %d to node %d\n", cpu, node);

	अगर (!(cpumask_test_cpu(cpu, node_to_cpumask_map[node])))
		cpumask_set_cpu(cpu, node_to_cpumask_map[node]);
पूर्ण

#अगर defined(CONFIG_HOTPLUG_CPU) || defined(CONFIG_PPC_SPLPAR)
अटल व्योम unmap_cpu_from_node(अचिन्हित दीर्घ cpu)
अणु
	पूर्णांक node = numa_cpu_lookup_table[cpu];

	dbg("removing cpu %lu from node %d\n", cpu, node);

	अगर (cpumask_test_cpu(cpu, node_to_cpumask_map[node])) अणु
		cpumask_clear_cpu(cpu, node_to_cpumask_map[node]);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "WARNING: cpu %lu not found in node %d\n",
		       cpu, node);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU || CONFIG_PPC_SPLPAR */

पूर्णांक cpu_distance(__be32 *cpu1_assoc, __be32 *cpu2_assoc)
अणु
	पूर्णांक dist = 0;

	पूर्णांक i, index;

	क्रम (i = 0; i < distance_ref_poपूर्णांकs_depth; i++) अणु
		index = be32_to_cpu(distance_ref_poपूर्णांकs[i]);
		अगर (cpu1_assoc[index] == cpu2_assoc[index])
			अवरोध;
		dist++;
	पूर्ण

	वापस dist;
पूर्ण

/* must hold reference to node during call */
अटल स्थिर __be32 *of_get_associativity(काष्ठा device_node *dev)
अणु
	वापस of_get_property(dev, "ibm,associativity", शून्य);
पूर्ण

पूर्णांक __node_distance(पूर्णांक a, पूर्णांक b)
अणु
	पूर्णांक i;
	पूर्णांक distance = LOCAL_DISTANCE;

	अगर (!क्रमm1_affinity)
		वापस ((a == b) ? LOCAL_DISTANCE : REMOTE_DISTANCE);

	क्रम (i = 0; i < distance_ref_poपूर्णांकs_depth; i++) अणु
		अगर (distance_lookup_table[a][i] == distance_lookup_table[b][i])
			अवरोध;

		/* Double the distance क्रम each NUMA level */
		distance *= 2;
	पूर्ण

	वापस distance;
पूर्ण
EXPORT_SYMBOL(__node_distance);

अटल व्योम initialize_distance_lookup_table(पूर्णांक nid,
		स्थिर __be32 *associativity)
अणु
	पूर्णांक i;

	अगर (!क्रमm1_affinity)
		वापस;

	क्रम (i = 0; i < distance_ref_poपूर्णांकs_depth; i++) अणु
		स्थिर __be32 *entry;

		entry = &associativity[be32_to_cpu(distance_ref_poपूर्णांकs[i]) - 1];
		distance_lookup_table[nid][i] = of_पढ़ो_number(entry, 1);
	पूर्ण
पूर्ण

/*
 * Returns nid in the range [0..nr_node_ids], or -1 अगर no useful NUMA
 * info is found.
 */
अटल पूर्णांक associativity_to_nid(स्थिर __be32 *associativity)
अणु
	पूर्णांक nid = NUMA_NO_NODE;

	अगर (!numa_enabled)
		जाओ out;

	अगर (of_पढ़ो_number(associativity, 1) >= min_common_depth)
		nid = of_पढ़ो_number(&associativity[min_common_depth], 1);

	/* POWER4 LPAR uses 0xffff as invalid node */
	अगर (nid == 0xffff || nid >= nr_node_ids)
		nid = NUMA_NO_NODE;

	अगर (nid > 0 &&
		of_पढ़ो_number(associativity, 1) >= distance_ref_poपूर्णांकs_depth) अणु
		/*
		 * Skip the length field and send start of associativity array
		 */
		initialize_distance_lookup_table(nid, associativity + 1);
	पूर्ण

out:
	वापस nid;
पूर्ण

/* Returns the nid associated with the given device tree node,
 * or -1 अगर not found.
 */
अटल पूर्णांक of_node_to_nid_single(काष्ठा device_node *device)
अणु
	पूर्णांक nid = NUMA_NO_NODE;
	स्थिर __be32 *पंचांगp;

	पंचांगp = of_get_associativity(device);
	अगर (पंचांगp)
		nid = associativity_to_nid(पंचांगp);
	वापस nid;
पूर्ण

/* Walk the device tree upwards, looking क्रम an associativity id */
पूर्णांक of_node_to_nid(काष्ठा device_node *device)
अणु
	पूर्णांक nid = NUMA_NO_NODE;

	of_node_get(device);
	जबतक (device) अणु
		nid = of_node_to_nid_single(device);
		अगर (nid != -1)
			अवरोध;

		device = of_get_next_parent(device);
	पूर्ण
	of_node_put(device);

	वापस nid;
पूर्ण
EXPORT_SYMBOL(of_node_to_nid);

अटल पूर्णांक __init find_min_common_depth(व्योम)
अणु
	पूर्णांक depth;
	काष्ठा device_node *root;

	अगर (firmware_has_feature(FW_FEATURE_OPAL))
		root = of_find_node_by_path("/ibm,opal");
	अन्यथा
		root = of_find_node_by_path("/rtas");
	अगर (!root)
		root = of_find_node_by_path("/");

	/*
	 * This property is a set of 32-bit पूर्णांकegers, each representing
	 * an index पूर्णांकo the ibm,associativity nodes.
	 *
	 * With क्रमm 0 affinity the first पूर्णांकeger is क्रम an SMP configuration
	 * (should be all 0's) and the second is क्रम a normal NUMA
	 * configuration. We have only one level of NUMA.
	 *
	 * With क्रमm 1 affinity the first पूर्णांकeger is the most signअगरicant
	 * NUMA boundary and the following are progressively less signअगरicant
	 * boundaries. There can be more than one level of NUMA.
	 */
	distance_ref_poपूर्णांकs = of_get_property(root,
					"ibm,associativity-reference-points",
					&distance_ref_poपूर्णांकs_depth);

	अगर (!distance_ref_poपूर्णांकs) अणु
		dbg("NUMA: ibm,associativity-reference-points not found.\n");
		जाओ err;
	पूर्ण

	distance_ref_poपूर्णांकs_depth /= माप(पूर्णांक);

	अगर (firmware_has_feature(FW_FEATURE_OPAL) ||
	    firmware_has_feature(FW_FEATURE_TYPE1_AFFINITY)) अणु
		dbg("Using form 1 affinity\n");
		क्रमm1_affinity = 1;
	पूर्ण

	अगर (क्रमm1_affinity) अणु
		depth = of_पढ़ो_number(distance_ref_poपूर्णांकs, 1);
	पूर्ण अन्यथा अणु
		अगर (distance_ref_poपूर्णांकs_depth < 2) अणु
			prपूर्णांकk(KERN_WARNING "NUMA: "
				"short ibm,associativity-reference-points\n");
			जाओ err;
		पूर्ण

		depth = of_पढ़ो_number(&distance_ref_poपूर्णांकs[1], 1);
	पूर्ण

	/*
	 * Warn and cap अगर the hardware supports more than
	 * MAX_DISTANCE_REF_POINTS करोमुख्यs.
	 */
	अगर (distance_ref_poपूर्णांकs_depth > MAX_DISTANCE_REF_POINTS) अणु
		prपूर्णांकk(KERN_WARNING "NUMA: distance array capped at "
			"%d entries\n", MAX_DISTANCE_REF_POINTS);
		distance_ref_poपूर्णांकs_depth = MAX_DISTANCE_REF_POINTS;
	पूर्ण

	of_node_put(root);
	वापस depth;

err:
	of_node_put(root);
	वापस -1;
पूर्ण

अटल व्योम __init get_n_mem_cells(पूर्णांक *n_addr_cells, पूर्णांक *n_size_cells)
अणु
	काष्ठा device_node *memory = शून्य;

	memory = of_find_node_by_type(memory, "memory");
	अगर (!memory)
		panic("numa.c: No memory nodes found!");

	*n_addr_cells = of_n_addr_cells(memory);
	*n_size_cells = of_n_size_cells(memory);
	of_node_put(memory);
पूर्ण

अटल अचिन्हित दीर्घ पढ़ो_n_cells(पूर्णांक n, स्थिर __be32 **buf)
अणु
	अचिन्हित दीर्घ result = 0;

	जबतक (n--) अणु
		result = (result << 32) | of_पढ़ो_number(*buf, 1);
		(*buf)++;
	पूर्ण
	वापस result;
पूर्ण

काष्ठा assoc_arrays अणु
	u32	n_arrays;
	u32	array_sz;
	स्थिर __be32 *arrays;
पूर्ण;

/*
 * Retrieve and validate the list of associativity arrays क्रम drconf
 * memory from the ibm,associativity-lookup-arrays property of the
 * device tree..
 *
 * The layout of the ibm,associativity-lookup-arrays property is a number N
 * indicating the number of associativity arrays, followed by a number M
 * indicating the size of each associativity array, followed by a list
 * of N associativity arrays.
 */
अटल पूर्णांक of_get_assoc_arrays(काष्ठा assoc_arrays *aa)
अणु
	काष्ठा device_node *memory;
	स्थिर __be32 *prop;
	u32 len;

	memory = of_find_node_by_path("/ibm,dynamic-reconfiguration-memory");
	अगर (!memory)
		वापस -1;

	prop = of_get_property(memory, "ibm,associativity-lookup-arrays", &len);
	अगर (!prop || len < 2 * माप(अचिन्हित पूर्णांक)) अणु
		of_node_put(memory);
		वापस -1;
	पूर्ण

	aa->n_arrays = of_पढ़ो_number(prop++, 1);
	aa->array_sz = of_पढ़ो_number(prop++, 1);

	of_node_put(memory);

	/* Now that we know the number of arrays and size of each array,
	 * revalidate the size of the property पढ़ो in.
	 */
	अगर (len < (aa->n_arrays * aa->array_sz + 2) * माप(अचिन्हित पूर्णांक))
		वापस -1;

	aa->arrays = prop;
	वापस 0;
पूर्ण

/*
 * This is like of_node_to_nid_single() क्रम memory represented in the
 * ibm,dynamic-reconfiguration-memory node.
 */
पूर्णांक of_drconf_to_nid_single(काष्ठा drmem_lmb *lmb)
अणु
	काष्ठा assoc_arrays aa = अणु .arrays = शून्य पूर्ण;
	पूर्णांक शेष_nid = NUMA_NO_NODE;
	पूर्णांक nid = शेष_nid;
	पूर्णांक rc, index;

	अगर ((min_common_depth < 0) || !numa_enabled)
		वापस शेष_nid;

	rc = of_get_assoc_arrays(&aa);
	अगर (rc)
		वापस शेष_nid;

	अगर (min_common_depth <= aa.array_sz &&
	    !(lmb->flags & DRCONF_MEM_AI_INVALID) && lmb->aa_index < aa.n_arrays) अणु
		index = lmb->aa_index * aa.array_sz + min_common_depth - 1;
		nid = of_पढ़ो_number(&aa.arrays[index], 1);

		अगर (nid == 0xffff || nid >= nr_node_ids)
			nid = शेष_nid;

		अगर (nid > 0) अणु
			index = lmb->aa_index * aa.array_sz;
			initialize_distance_lookup_table(nid,
							&aa.arrays[index]);
		पूर्ण
	पूर्ण

	वापस nid;
पूर्ण

#अगर_घोषित CONFIG_PPC_SPLPAR
अटल पूर्णांक vphn_get_nid(दीर्घ lcpu)
अणु
	__be32 associativity[VPHN_ASSOC_बफ_मानE] = अणु0पूर्ण;
	दीर्घ rc, hwid;

	/*
	 * On a shared lpar, device tree will not have node associativity.
	 * At this समय lppaca, or its __old_status field may not be
	 * updated. Hence kernel cannot detect अगर its on a shared lpar. So
	 * request an explicit associativity irrespective of whether the
	 * lpar is shared or dedicated. Use the device tree property as a
	 * fallback. cpu_to_phys_id is only valid between
	 * smp_setup_cpu_maps() and smp_setup_pacas().
	 */
	अगर (firmware_has_feature(FW_FEATURE_VPHN)) अणु
		अगर (cpu_to_phys_id)
			hwid = cpu_to_phys_id[lcpu];
		अन्यथा
			hwid = get_hard_smp_processor_id(lcpu);

		rc = hcall_vphn(hwid, VPHN_FLAG_VCPU, associativity);
		अगर (rc == H_SUCCESS)
			वापस associativity_to_nid(associativity);
	पूर्ण

	वापस NUMA_NO_NODE;
पूर्ण
#अन्यथा
अटल पूर्णांक vphn_get_nid(दीर्घ unused)
अणु
	वापस NUMA_NO_NODE;
पूर्ण
#पूर्ण_अगर  /* CONFIG_PPC_SPLPAR */

/*
 * Figure out to which करोमुख्य a cpu beदीर्घs and stick it there.
 * Return the id of the करोमुख्य used.
 */
अटल पूर्णांक numa_setup_cpu(अचिन्हित दीर्घ lcpu)
अणु
	काष्ठा device_node *cpu;
	पूर्णांक fcpu = cpu_first_thपढ़ो_sibling(lcpu);
	पूर्णांक nid = NUMA_NO_NODE;

	अगर (!cpu_present(lcpu)) अणु
		set_cpu_numa_node(lcpu, first_online_node);
		वापस first_online_node;
	पूर्ण

	/*
	 * If a valid cpu-to-node mapping is alपढ़ोy available, use it
	 * directly instead of querying the firmware, since it represents
	 * the most recent mapping notअगरied to us by the platक्रमm (eg: VPHN).
	 * Since cpu_to_node binding reमुख्यs the same क्रम all thपढ़ोs in the
	 * core. If a valid cpu-to-node mapping is alपढ़ोy available, क्रम
	 * the first thपढ़ो in the core, use it.
	 */
	nid = numa_cpu_lookup_table[fcpu];
	अगर (nid >= 0) अणु
		map_cpu_to_node(lcpu, nid);
		वापस nid;
	पूर्ण

	nid = vphn_get_nid(lcpu);
	अगर (nid != NUMA_NO_NODE)
		जाओ out_present;

	cpu = of_get_cpu_node(lcpu, शून्य);

	अगर (!cpu) अणु
		WARN_ON(1);
		अगर (cpu_present(lcpu))
			जाओ out_present;
		अन्यथा
			जाओ out;
	पूर्ण

	nid = of_node_to_nid_single(cpu);
	of_node_put(cpu);

out_present:
	अगर (nid < 0 || !node_possible(nid))
		nid = first_online_node;

	/*
	 * Update क्रम the first thपढ़ो of the core. All thपढ़ोs of a core
	 * have to be part of the same node. This not only aव्योमs querying
	 * क्रम every other thपढ़ो in the core, but always aव्योमs a हाल
	 * where भव node associativity change causes subsequent thपढ़ोs
	 * of a core to be associated with dअगरferent nid. However अगर first
	 * thपढ़ो is alपढ़ोy online, expect it to have a valid mapping.
	 */
	अगर (fcpu != lcpu) अणु
		WARN_ON(cpu_online(fcpu));
		map_cpu_to_node(fcpu, nid);
	पूर्ण

	map_cpu_to_node(lcpu, nid);
out:
	वापस nid;
पूर्ण

अटल व्योम verअगरy_cpu_node_mapping(पूर्णांक cpu, पूर्णांक node)
अणु
	पूर्णांक base, sibling, i;

	/* Verअगरy that all the thपढ़ोs in the core beदीर्घ to the same node */
	base = cpu_first_thपढ़ो_sibling(cpu);

	क्रम (i = 0; i < thपढ़ोs_per_core; i++) अणु
		sibling = base + i;

		अगर (sibling == cpu || cpu_is_offline(sibling))
			जारी;

		अगर (cpu_to_node(sibling) != node) अणु
			WARN(1, "CPU thread siblings %d and %d don't belong"
				" to the same node!\n", cpu, sibling);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* Must run beक्रमe sched करोमुख्यs notअगरier. */
अटल पूर्णांक ppc_numa_cpu_prepare(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक nid;

	nid = numa_setup_cpu(cpu);
	verअगरy_cpu_node_mapping(cpu, nid);
	वापस 0;
पूर्ण

अटल पूर्णांक ppc_numa_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_HOTPLUG_CPU
	unmap_cpu_from_node(cpu);
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * Check and possibly modअगरy a memory region to enक्रमce the memory limit.
 *
 * Returns the size the region should have to enक्रमce the memory limit.
 * This will either be the original value of size, a truncated value,
 * or zero. If the वापसed value of size is 0 the region should be
 * discarded as it lies wholly above the memory limit.
 */
अटल अचिन्हित दीर्घ __init numa_enक्रमce_memory_limit(अचिन्हित दीर्घ start,
						      अचिन्हित दीर्घ size)
अणु
	/*
	 * We use memblock_end_of_DRAM() in here instead of memory_limit because
	 * we've alपढ़ोy adjusted it क्रम the limit and it takes care of
	 * having memory holes below the limit.  Also, in the हाल of
	 * iommu_is_off, memory_limit is not set but is implicitly enक्रमced.
	 */

	अगर (start + size <= memblock_end_of_DRAM())
		वापस size;

	अगर (start >= memblock_end_of_DRAM())
		वापस 0;

	वापस memblock_end_of_DRAM() - start;
पूर्ण

/*
 * Reads the counter क्रम a given entry in
 * linux,drconf-usable-memory property
 */
अटल अंतरभूत पूर्णांक __init पढ़ो_usm_ranges(स्थिर __be32 **usm)
अणु
	/*
	 * For each lmb in ibm,dynamic-memory a corresponding
	 * entry in linux,drconf-usable-memory property contains
	 * a counter followed by that many (base, size) duple.
	 * पढ़ो the counter from linux,drconf-usable-memory
	 */
	वापस पढ़ो_n_cells(n_mem_size_cells, usm);
पूर्ण

/*
 * Extract NUMA inक्रमmation from the ibm,dynamic-reconfiguration-memory
 * node.  This assumes n_mem_अणुaddr,sizeपूर्ण_cells have been set.
 */
अटल पूर्णांक __init numa_setup_drmem_lmb(काष्ठा drmem_lmb *lmb,
					स्थिर __be32 **usm,
					व्योम *data)
अणु
	अचिन्हित पूर्णांक ranges, is_kexec_kdump = 0;
	अचिन्हित दीर्घ base, size, sz;
	पूर्णांक nid;

	/*
	 * Skip this block अगर the reserved bit is set in flags (0x80)
	 * or अगर the block is not asचिन्हित to this partition (0x8)
	 */
	अगर ((lmb->flags & DRCONF_MEM_RESERVED)
	    || !(lmb->flags & DRCONF_MEM_ASSIGNED))
		वापस 0;

	अगर (*usm)
		is_kexec_kdump = 1;

	base = lmb->base_addr;
	size = drmem_lmb_size();
	ranges = 1;

	अगर (is_kexec_kdump) अणु
		ranges = पढ़ो_usm_ranges(usm);
		अगर (!ranges) /* there are no (base, size) duple */
			वापस 0;
	पूर्ण

	करो अणु
		अगर (is_kexec_kdump) अणु
			base = पढ़ो_n_cells(n_mem_addr_cells, usm);
			size = पढ़ो_n_cells(n_mem_size_cells, usm);
		पूर्ण

		nid = of_drconf_to_nid_single(lmb);
		fake_numa_create_new_node(((base + size) >> PAGE_SHIFT),
					  &nid);
		node_set_online(nid);
		sz = numa_enक्रमce_memory_limit(base, size);
		अगर (sz)
			memblock_set_node(base, sz, &memblock.memory, nid);
	पूर्ण जबतक (--ranges);

	वापस 0;
पूर्ण

अटल पूर्णांक __init parse_numa_properties(व्योम)
अणु
	काष्ठा device_node *memory;
	पूर्णांक शेष_nid = 0;
	अचिन्हित दीर्घ i;

	अगर (numa_enabled == 0) अणु
		prपूर्णांकk(KERN_WARNING "NUMA disabled by user\n");
		वापस -1;
	पूर्ण

	min_common_depth = find_min_common_depth();

	अगर (min_common_depth < 0) अणु
		/*
		 * अगर we fail to parse min_common_depth from device tree
		 * mark the numa disabled, boot with numa disabled.
		 */
		numa_enabled = false;
		वापस min_common_depth;
	पूर्ण

	dbg("NUMA associativity depth for CPU/Memory: %d\n", min_common_depth);

	/*
	 * Even though we connect cpus to numa करोमुख्यs later in SMP
	 * init, we need to know the node ids now. This is because
	 * each node to be onlined must have NODE_DATA etc backing it.
	 */
	क्रम_each_present_cpu(i) अणु
		काष्ठा device_node *cpu;
		पूर्णांक nid = vphn_get_nid(i);

		/*
		 * Don't fall back to शेष_nid yet -- we will plug
		 * cpus पूर्णांकo nodes once the memory scan has discovered
		 * the topology.
		 */
		अगर (nid == NUMA_NO_NODE) अणु
			cpu = of_get_cpu_node(i, शून्य);
			BUG_ON(!cpu);
			nid = of_node_to_nid_single(cpu);
			of_node_put(cpu);
		पूर्ण

		node_set_online(nid);
	पूर्ण

	get_n_mem_cells(&n_mem_addr_cells, &n_mem_size_cells);

	क्रम_each_node_by_type(memory, "memory") अणु
		अचिन्हित दीर्घ start;
		अचिन्हित दीर्घ size;
		पूर्णांक nid;
		पूर्णांक ranges;
		स्थिर __be32 *memcell_buf;
		अचिन्हित पूर्णांक len;

		memcell_buf = of_get_property(memory,
			"linux,usable-memory", &len);
		अगर (!memcell_buf || len <= 0)
			memcell_buf = of_get_property(memory, "reg", &len);
		अगर (!memcell_buf || len <= 0)
			जारी;

		/* ranges in cell */
		ranges = (len >> 2) / (n_mem_addr_cells + n_mem_size_cells);
new_range:
		/* these are order-sensitive, and modअगरy the buffer poपूर्णांकer */
		start = पढ़ो_n_cells(n_mem_addr_cells, &memcell_buf);
		size = पढ़ो_n_cells(n_mem_size_cells, &memcell_buf);

		/*
		 * Assumption: either all memory nodes or none will
		 * have associativity properties.  If none, then
		 * everything goes to शेष_nid.
		 */
		nid = of_node_to_nid_single(memory);
		अगर (nid < 0)
			nid = शेष_nid;

		fake_numa_create_new_node(((start + size) >> PAGE_SHIFT), &nid);
		node_set_online(nid);

		size = numa_enक्रमce_memory_limit(start, size);
		अगर (size)
			memblock_set_node(start, size, &memblock.memory, nid);

		अगर (--ranges)
			जाओ new_range;
	पूर्ण

	/*
	 * Now करो the same thing क्रम each MEMBLOCK listed in the
	 * ibm,dynamic-memory property in the
	 * ibm,dynamic-reconfiguration-memory node.
	 */
	memory = of_find_node_by_path("/ibm,dynamic-reconfiguration-memory");
	अगर (memory) अणु
		walk_drmem_lmbs(memory, शून्य, numa_setup_drmem_lmb);
		of_node_put(memory);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __init setup_nonnuma(व्योम)
अणु
	अचिन्हित दीर्घ top_of_ram = memblock_end_of_DRAM();
	अचिन्हित दीर्घ total_ram = memblock_phys_mem_size();
	अचिन्हित दीर्घ start_pfn, end_pfn;
	अचिन्हित पूर्णांक nid = 0;
	पूर्णांक i;

	prपूर्णांकk(KERN_DEBUG "Top of RAM: 0x%lx, Total RAM: 0x%lx\n",
	       top_of_ram, total_ram);
	prपूर्णांकk(KERN_DEBUG "Memory hole size: %ldMB\n",
	       (top_of_ram - total_ram) >> 20);

	क्रम_each_mem_pfn_range(i, MAX_NUMNODES, &start_pfn, &end_pfn, शून्य) अणु
		fake_numa_create_new_node(end_pfn, &nid);
		memblock_set_node(PFN_PHYS(start_pfn),
				  PFN_PHYS(end_pfn - start_pfn),
				  &memblock.memory, nid);
		node_set_online(nid);
	पूर्ण
पूर्ण

व्योम __init dump_numa_cpu_topology(व्योम)
अणु
	अचिन्हित पूर्णांक node;
	अचिन्हित पूर्णांक cpu, count;

	अगर (!numa_enabled)
		वापस;

	क्रम_each_online_node(node) अणु
		pr_info("Node %d CPUs:", node);

		count = 0;
		/*
		 * If we used a CPU iterator here we would miss prपूर्णांकing
		 * the holes in the cpumap.
		 */
		क्रम (cpu = 0; cpu < nr_cpu_ids; cpu++) अणु
			अगर (cpumask_test_cpu(cpu,
					node_to_cpumask_map[node])) अणु
				अगर (count == 0)
					pr_cont(" %u", cpu);
				++count;
			पूर्ण अन्यथा अणु
				अगर (count > 1)
					pr_cont("-%u", cpu - 1);
				count = 0;
			पूर्ण
		पूर्ण

		अगर (count > 1)
			pr_cont("-%u", nr_cpu_ids - 1);
		pr_cont("\n");
	पूर्ण
पूर्ण

/* Initialize NODE_DATA क्रम a node on the local memory */
अटल व्योम __init setup_node_data(पूर्णांक nid, u64 start_pfn, u64 end_pfn)
अणु
	u64 spanned_pages = end_pfn - start_pfn;
	स्थिर माप_प्रकार nd_size = roundup(माप(pg_data_t), SMP_CACHE_BYTES);
	u64 nd_pa;
	व्योम *nd;
	पूर्णांक tnid;

	nd_pa = memblock_phys_alloc_try_nid(nd_size, SMP_CACHE_BYTES, nid);
	अगर (!nd_pa)
		panic("Cannot allocate %zu bytes for node %d data\n",
		      nd_size, nid);

	nd = __va(nd_pa);

	/* report and initialize */
	pr_info("  NODE_DATA [mem %#010Lx-%#010Lx]\n",
		nd_pa, nd_pa + nd_size - 1);
	tnid = early_pfn_to_nid(nd_pa >> PAGE_SHIFT);
	अगर (tnid != nid)
		pr_info("    NODE_DATA(%d) on node %d\n", nid, tnid);

	node_data[nid] = nd;
	स_रखो(NODE_DATA(nid), 0, माप(pg_data_t));
	NODE_DATA(nid)->node_id = nid;
	NODE_DATA(nid)->node_start_pfn = start_pfn;
	NODE_DATA(nid)->node_spanned_pages = spanned_pages;
पूर्ण

अटल व्योम __init find_possible_nodes(व्योम)
अणु
	काष्ठा device_node *rtas;
	स्थिर __be32 *करोमुख्यs;
	पूर्णांक prop_length, max_nodes;
	u32 i;

	अगर (!numa_enabled)
		वापस;

	rtas = of_find_node_by_path("/rtas");
	अगर (!rtas)
		वापस;

	/*
	 * ibm,current-associativity-करोमुख्यs is a fairly recent property. If
	 * it करोesn't exist, then fallback on ibm,max-associativity-करोमुख्यs.
	 * Current denotes what the platक्रमm can support compared to max
	 * which denotes what the Hypervisor can support.
	 */
	करोमुख्यs = of_get_property(rtas, "ibm,current-associativity-domains",
					&prop_length);
	अगर (!करोमुख्यs) अणु
		करोमुख्यs = of_get_property(rtas, "ibm,max-associativity-domains",
					&prop_length);
		अगर (!करोमुख्यs)
			जाओ out;
	पूर्ण

	max_nodes = of_पढ़ो_number(&करोमुख्यs[min_common_depth], 1);
	क्रम (i = 0; i < max_nodes; i++) अणु
		अगर (!node_possible(i))
			node_set(i, node_possible_map);
	पूर्ण

	prop_length /= माप(पूर्णांक);
	अगर (prop_length > min_common_depth + 2)
		coregroup_enabled = 1;

out:
	of_node_put(rtas);
पूर्ण

व्योम __init mem_topology_setup(व्योम)
अणु
	पूर्णांक cpu;

	/*
	 * Linux/mm assumes node 0 to be online at boot. However this is not
	 * true on PowerPC, where node 0 is similar to any other node, it
	 * could be cpuless, memoryless node. So क्रमce node 0 to be offline
	 * क्रम now. This will prevent cpuless, memoryless node 0 showing up
	 * unnecessarily as online. If a node has cpus or memory that need
	 * to be online, then node will anyway be marked online.
	 */
	node_set_offline(0);

	अगर (parse_numa_properties())
		setup_nonnuma();

	/*
	 * Modअगरy the set of possible NUMA nodes to reflect inक्रमmation
	 * available about the set of online nodes, and the set of nodes
	 * that we expect to make use of क्रम this platक्रमm's affinity
	 * calculations.
	 */
	nodes_and(node_possible_map, node_possible_map, node_online_map);

	find_possible_nodes();

	setup_node_to_cpumask_map();

	reset_numa_cpu_lookup_table();

	क्रम_each_possible_cpu(cpu) अणु
		/*
		 * Powerpc with CONFIG_NUMA always used to have a node 0,
		 * even अगर it was memoryless or cpuless. For all cpus that
		 * are possible but not present, cpu_to_node() would poपूर्णांक
		 * to node 0. To हटाओ a cpuless, memoryless dummy node,
		 * घातerpc need to make sure all possible but not present
		 * cpu_to_node are set to a proper node.
		 */
		numa_setup_cpu(cpu);
	पूर्ण
पूर्ण

व्योम __init iniपंचांगem_init(व्योम)
अणु
	पूर्णांक nid;

	max_low_pfn = memblock_end_of_DRAM() >> PAGE_SHIFT;
	max_pfn = max_low_pfn;

	memblock_dump_all();

	क्रम_each_online_node(nid) अणु
		अचिन्हित दीर्घ start_pfn, end_pfn;

		get_pfn_range_क्रम_nid(nid, &start_pfn, &end_pfn);
		setup_node_data(nid, start_pfn, end_pfn);
	पूर्ण

	sparse_init();

	/*
	 * We need the numa_cpu_lookup_table to be accurate क्रम all CPUs,
	 * even beक्रमe we online them, so that we can use cpu_to_अणुnode,memपूर्ण
	 * early in boot, cf. smp_prepare_cpus().
	 * _nocalls() + manual invocation is used because cpuhp is not yet
	 * initialized क्रम the boot CPU.
	 */
	cpuhp_setup_state_nocalls(CPUHP_POWER_NUMA_PREPARE, "powerpc/numa:prepare",
				  ppc_numa_cpu_prepare, ppc_numa_cpu_dead);
पूर्ण

अटल पूर्णांक __init early_numa(अक्षर *p)
अणु
	अगर (!p)
		वापस 0;

	अगर (म_माला(p, "off"))
		numa_enabled = 0;

	अगर (म_माला(p, "debug"))
		numa_debug = 1;

	p = म_माला(p, "fake=");
	अगर (p)
		cmdline = p + म_माप("fake=");

	वापस 0;
पूर्ण
early_param("numa", early_numa);

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
/*
 * Find the node associated with a hot added memory section क्रम
 * memory represented in the device tree by the property
 * ibm,dynamic-reconfiguration-memory/ibm,dynamic-memory.
 */
अटल पूर्णांक hot_add_drconf_scn_to_nid(अचिन्हित दीर्घ scn_addr)
अणु
	काष्ठा drmem_lmb *lmb;
	अचिन्हित दीर्घ lmb_size;
	पूर्णांक nid = NUMA_NO_NODE;

	lmb_size = drmem_lmb_size();

	क्रम_each_drmem_lmb(lmb) अणु
		/* skip this block अगर it is reserved or not asचिन्हित to
		 * this partition */
		अगर ((lmb->flags & DRCONF_MEM_RESERVED)
		    || !(lmb->flags & DRCONF_MEM_ASSIGNED))
			जारी;

		अगर ((scn_addr < lmb->base_addr)
		    || (scn_addr >= (lmb->base_addr + lmb_size)))
			जारी;

		nid = of_drconf_to_nid_single(lmb);
		अवरोध;
	पूर्ण

	वापस nid;
पूर्ण

/*
 * Find the node associated with a hot added memory section क्रम memory
 * represented in the device tree as a node (i.e. memory@XXXX) क्रम
 * each memblock.
 */
अटल पूर्णांक hot_add_node_scn_to_nid(अचिन्हित दीर्घ scn_addr)
अणु
	काष्ठा device_node *memory;
	पूर्णांक nid = NUMA_NO_NODE;

	क्रम_each_node_by_type(memory, "memory") अणु
		अचिन्हित दीर्घ start, size;
		पूर्णांक ranges;
		स्थिर __be32 *memcell_buf;
		अचिन्हित पूर्णांक len;

		memcell_buf = of_get_property(memory, "reg", &len);
		अगर (!memcell_buf || len <= 0)
			जारी;

		/* ranges in cell */
		ranges = (len >> 2) / (n_mem_addr_cells + n_mem_size_cells);

		जबतक (ranges--) अणु
			start = पढ़ो_n_cells(n_mem_addr_cells, &memcell_buf);
			size = पढ़ो_n_cells(n_mem_size_cells, &memcell_buf);

			अगर ((scn_addr < start) || (scn_addr >= (start + size)))
				जारी;

			nid = of_node_to_nid_single(memory);
			अवरोध;
		पूर्ण

		अगर (nid >= 0)
			अवरोध;
	पूर्ण

	of_node_put(memory);

	वापस nid;
पूर्ण

/*
 * Find the node associated with a hot added memory section.  Section
 * corresponds to a SPARSEMEM section, not an MEMBLOCK.  It is assumed that
 * sections are fully contained within a single MEMBLOCK.
 */
पूर्णांक hot_add_scn_to_nid(अचिन्हित दीर्घ scn_addr)
अणु
	काष्ठा device_node *memory = शून्य;
	पूर्णांक nid;

	अगर (!numa_enabled)
		वापस first_online_node;

	memory = of_find_node_by_path("/ibm,dynamic-reconfiguration-memory");
	अगर (memory) अणु
		nid = hot_add_drconf_scn_to_nid(scn_addr);
		of_node_put(memory);
	पूर्ण अन्यथा अणु
		nid = hot_add_node_scn_to_nid(scn_addr);
	पूर्ण

	अगर (nid < 0 || !node_possible(nid))
		nid = first_online_node;

	वापस nid;
पूर्ण

अटल u64 hot_add_drconf_memory_max(व्योम)
अणु
	काष्ठा device_node *memory = शून्य;
	काष्ठा device_node *dn = शून्य;
	स्थिर __be64 *lrdr = शून्य;

	dn = of_find_node_by_path("/rtas");
	अगर (dn) अणु
		lrdr = of_get_property(dn, "ibm,lrdr-capacity", शून्य);
		of_node_put(dn);
		अगर (lrdr)
			वापस be64_to_cpup(lrdr);
	पूर्ण

	memory = of_find_node_by_path("/ibm,dynamic-reconfiguration-memory");
	अगर (memory) अणु
		of_node_put(memory);
		वापस drmem_lmb_memory_max();
	पूर्ण
	वापस 0;
पूर्ण

/*
 * memory_hotplug_max - वापस max address of memory that may be added
 *
 * This is currently only used on प्रणालीs that support drconfig memory
 * hotplug.
 */
u64 memory_hotplug_max(व्योम)
अणु
        वापस max(hot_add_drconf_memory_max(), memblock_end_of_DRAM());
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMORY_HOTPLUG */

/* Virtual Processor Home Node (VPHN) support */
#अगर_घोषित CONFIG_PPC_SPLPAR
अटल पूर्णांक topology_inited;

/*
 * Retrieve the new associativity inक्रमmation क्रम a भव processor's
 * home node.
 */
अटल दीर्घ vphn_get_associativity(अचिन्हित दीर्घ cpu,
					__be32 *associativity)
अणु
	दीर्घ rc;

	rc = hcall_vphn(get_hard_smp_processor_id(cpu),
				VPHN_FLAG_VCPU, associativity);

	चयन (rc) अणु
	हाल H_SUCCESS:
		dbg("VPHN hcall succeeded. Reset polling...\n");
		जाओ out;

	हाल H_FUNCTION:
		pr_err_ratelimited("VPHN unsupported. Disabling polling...\n");
		अवरोध;
	हाल H_HARDWARE:
		pr_err_ratelimited("hcall_vphn() experienced a hardware fault "
			"preventing VPHN. Disabling polling...\n");
		अवरोध;
	हाल H_PARAMETER:
		pr_err_ratelimited("hcall_vphn() was passed an invalid parameter. "
			"Disabling polling...\n");
		अवरोध;
	शेष:
		pr_err_ratelimited("hcall_vphn() returned %ld. Disabling polling...\n"
			, rc);
		अवरोध;
	पूर्ण
out:
	वापस rc;
पूर्ण

पूर्णांक find_and_online_cpu_nid(पूर्णांक cpu)
अणु
	__be32 associativity[VPHN_ASSOC_बफ_मानE] = अणु0पूर्ण;
	पूर्णांक new_nid;

	/* Use associativity from first thपढ़ो क्रम all siblings */
	अगर (vphn_get_associativity(cpu, associativity))
		वापस cpu_to_node(cpu);

	new_nid = associativity_to_nid(associativity);
	अगर (new_nid < 0 || !node_possible(new_nid))
		new_nid = first_online_node;

	अगर (NODE_DATA(new_nid) == शून्य) अणु
#अगर_घोषित CONFIG_MEMORY_HOTPLUG
		/*
		 * Need to ensure that NODE_DATA is initialized क्रम a node from
		 * available memory (see memblock_alloc_try_nid). If unable to
		 * init the node, then शेष to nearest node that has memory
		 * installed. Skip onlining a node अगर the subप्रणालीs are not
		 * yet initialized.
		 */
		अगर (!topology_inited || try_online_node(new_nid))
			new_nid = first_online_node;
#अन्यथा
		/*
		 * Default to using the nearest node that has memory installed.
		 * Otherwise, it would be necessary to patch the kernel MM code
		 * to deal with more memoryless-node error conditions.
		 */
		new_nid = first_online_node;
#पूर्ण_अगर
	पूर्ण

	pr_debug("%s:%d cpu %d nid %d\n", __FUNCTION__, __LINE__,
		cpu, new_nid);
	वापस new_nid;
पूर्ण

पूर्णांक cpu_to_coregroup_id(पूर्णांक cpu)
अणु
	__be32 associativity[VPHN_ASSOC_बफ_मानE] = अणु0पूर्ण;
	पूर्णांक index;

	अगर (cpu < 0 || cpu > nr_cpu_ids)
		वापस -1;

	अगर (!coregroup_enabled)
		जाओ out;

	अगर (!firmware_has_feature(FW_FEATURE_VPHN))
		जाओ out;

	अगर (vphn_get_associativity(cpu, associativity))
		जाओ out;

	index = of_पढ़ो_number(associativity, 1);
	अगर (index > min_common_depth + 1)
		वापस of_पढ़ो_number(&associativity[index - 1], 1);

out:
	वापस cpu_to_core_id(cpu);
पूर्ण

अटल पूर्णांक topology_update_init(व्योम)
अणु
	topology_inited = 1;
	वापस 0;
पूर्ण
device_initcall(topology_update_init);
#पूर्ण_अगर /* CONFIG_PPC_SPLPAR */
