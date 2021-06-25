<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2010 Loongson Inc. & Lemote Inc. &
 *                    Institute of Computing Technology
 * Author:  Xiang Gao, gaoxiang@ict.ac.cn
 *          Huacai Chen, chenhc@lemote.com
 *          Xiaofu Meng, Shuangshuang Zhang
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/export.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/swap.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pfn.h>
#समावेश <linux/highस्मृति.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/sections.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/mc146818-समय.स>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/wbflush.h>
#समावेश <boot_param.h>
#समावेश <loongson.h>

अचिन्हित अक्षर __node_distances[MAX_NUMNODES][MAX_NUMNODES];
EXPORT_SYMBOL(__node_distances);
काष्ठा pglist_data *__node_data[MAX_NUMNODES];
EXPORT_SYMBOL(__node_data);

cpumask_t __node_cpumask[MAX_NUMNODES];
EXPORT_SYMBOL(__node_cpumask);

अटल व्योम cpu_node_probe(व्योम)
अणु
	पूर्णांक i;

	nodes_clear(node_possible_map);
	nodes_clear(node_online_map);
	क्रम (i = 0; i < loongson_sysconf.nr_nodes; i++) अणु
		node_set_state(num_online_nodes(), N_POSSIBLE);
		node_set_online(num_online_nodes());
	पूर्ण

	pr_info("NUMA: Discovered %d cpus on %d nodes\n",
		loongson_sysconf.nr_cpus, num_online_nodes());
पूर्ण

अटल पूर्णांक __init compute_node_distance(पूर्णांक row, पूर्णांक col)
अणु
	पूर्णांक package_row = row * loongson_sysconf.cores_per_node /
				loongson_sysconf.cores_per_package;
	पूर्णांक package_col = col * loongson_sysconf.cores_per_node /
				loongson_sysconf.cores_per_package;

	अगर (col == row)
		वापस LOCAL_DISTANCE;
	अन्यथा अगर (package_row == package_col)
		वापस 40;
	अन्यथा
		वापस 100;
पूर्ण

अटल व्योम __init init_topology_matrix(व्योम)
अणु
	पूर्णांक row, col;

	क्रम (row = 0; row < MAX_NUMNODES; row++)
		क्रम (col = 0; col < MAX_NUMNODES; col++)
			__node_distances[row][col] = -1;

	क्रम_each_online_node(row) अणु
		क्रम_each_online_node(col) अणु
			__node_distances[row][col] =
				compute_node_distance(row, col);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init node_mem_init(अचिन्हित पूर्णांक node)
अणु
	काष्ठा pglist_data *nd;
	अचिन्हित दीर्घ node_addrspace_offset;
	अचिन्हित दीर्घ start_pfn, end_pfn;
	अचिन्हित दीर्घ nd_pa;
	पूर्णांक tnid;
	स्थिर माप_प्रकार nd_size = roundup(माप(pg_data_t), SMP_CACHE_BYTES);

	node_addrspace_offset = nid_to_addrbase(node);
	pr_info("Node%d's addrspace_offset is 0x%lx\n",
			node, node_addrspace_offset);

	get_pfn_range_क्रम_nid(node, &start_pfn, &end_pfn);
	pr_info("Node%d: start_pfn=0x%lx, end_pfn=0x%lx\n",
		node, start_pfn, end_pfn);

	nd_pa = memblock_phys_alloc_try_nid(nd_size, SMP_CACHE_BYTES, node);
	अगर (!nd_pa)
		panic("Cannot allocate %zu bytes for node %d data\n",
		      nd_size, node);
	nd = __va(nd_pa);
	स_रखो(nd, 0, माप(काष्ठा pglist_data));
	tnid = early_pfn_to_nid(nd_pa >> PAGE_SHIFT);
	अगर (tnid != node)
		pr_info("NODE_DATA(%d) on node %d\n", node, tnid);
	__node_data[node] = nd;
	NODE_DATA(node)->node_start_pfn = start_pfn;
	NODE_DATA(node)->node_spanned_pages = end_pfn - start_pfn;

	अगर (node == 0) अणु
		/* kernel start address */
		अचिन्हित दीर्घ kernel_start_pfn = PFN_DOWN(__pa_symbol(&_text));

		/* kernel end address */
		अचिन्हित दीर्घ kernel_end_pfn = PFN_UP(__pa_symbol(&_end));

		/* used by finalize_initrd() */
		max_low_pfn = end_pfn;

		/* Reserve the kernel text/data/bss */
		memblock_reserve(kernel_start_pfn << PAGE_SHIFT,
				 ((kernel_end_pfn - kernel_start_pfn) << PAGE_SHIFT));

		/* Reserve 0xfe000000~0xffffffff क्रम RS780E पूर्णांकegrated GPU */
		अगर (node_end_pfn(0) >= (0xffffffff >> PAGE_SHIFT))
			memblock_reserve((node_addrspace_offset | 0xfe000000),
					 32 << 20);
	पूर्ण
पूर्ण

अटल __init व्योम prom_meminit(व्योम)
अणु
	अचिन्हित पूर्णांक node, cpu, active_cpu = 0;

	cpu_node_probe();
	init_topology_matrix();

	क्रम (node = 0; node < loongson_sysconf.nr_nodes; node++) अणु
		अगर (node_online(node)) अणु
			szmem(node);
			node_mem_init(node);
			cpumask_clear(&__node_cpumask[node]);
		पूर्ण
	पूर्ण
	max_low_pfn = PHYS_PFN(memblock_end_of_DRAM());

	क्रम (cpu = 0; cpu < loongson_sysconf.nr_cpus; cpu++) अणु
		node = cpu / loongson_sysconf.cores_per_node;
		अगर (node >= num_online_nodes())
			node = 0;

		अगर (loongson_sysconf.reserved_cpus_mask & (1<<cpu))
			जारी;

		cpumask_set_cpu(active_cpu, &__node_cpumask[node]);
		pr_info("NUMA: set cpumask cpu %d on node %d\n", active_cpu, node);

		active_cpu++;
	पूर्ण
पूर्ण

व्योम __init paging_init(व्योम)
अणु
	अचिन्हित दीर्घ zones_size[MAX_NR_ZONES] = अणु0, पूर्ण;

	pagetable_init();
	zones_size[ZONE_DMA32] = MAX_DMA32_PFN;
	zones_size[ZONE_NORMAL] = max_low_pfn;
	मुक्त_area_init(zones_size);
पूर्ण

व्योम __init mem_init(व्योम)
अणु
	high_memory = (व्योम *) __va(get_num_physpages() << PAGE_SHIFT);
	memblock_मुक्त_all();
	setup_zero_pages();	/* This comes from node 0 */
पूर्ण

/* All PCI device beदीर्घs to logical Node-0 */
पूर्णांक pcibus_to_node(काष्ठा pci_bus *bus)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL(pcibus_to_node);

व्योम __init prom_init_numa_memory(व्योम)
अणु
	pr_info("CP0_Config3: CP0 16.3 (0x%x)\n", पढ़ो_c0_config3());
	pr_info("CP0_PageGrain: CP0 5.1 (0x%x)\n", पढ़ो_c0_pagegrain());
	prom_meminit();
पूर्ण
EXPORT_SYMBOL(prom_init_numa_memory);
