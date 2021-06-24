<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * ia64 kernel NUMA specअगरic stuff
 *
 * Copyright (C) 2002 Erich Focht <efocht@ess.nec.de>
 * Copyright (C) 2004 Silicon Graphics, Inc.
 *   Jesse Barnes <jbarnes@sgi.com>
 */
#समावेश <linux/topology.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/smp.h>

u16 cpu_to_node_map[NR_CPUS] __cacheline_aligned;
EXPORT_SYMBOL(cpu_to_node_map);

cpumask_t node_to_cpu_mask[MAX_NUMNODES] __cacheline_aligned;
EXPORT_SYMBOL(node_to_cpu_mask);

व्योम map_cpu_to_node(पूर्णांक cpu, पूर्णांक nid)
अणु
	पूर्णांक oldnid;
	अगर (nid < 0) अणु /* just initialize by zero */
		cpu_to_node_map[cpu] = 0;
		वापस;
	पूर्ण
	/* sanity check first */
	oldnid = cpu_to_node_map[cpu];
	अगर (cpumask_test_cpu(cpu, &node_to_cpu_mask[oldnid])) अणु
		वापस; /* nothing to करो */
	पूर्ण
	/* we करोn't have cpu-driven node hot add yet...
	   In usual हाल, node is created from SRAT at boot समय. */
	अगर (!node_online(nid))
		nid = first_online_node;
	cpu_to_node_map[cpu] = nid;
	cpumask_set_cpu(cpu, &node_to_cpu_mask[nid]);
	वापस;
पूर्ण

व्योम unmap_cpu_from_node(पूर्णांक cpu, पूर्णांक nid)
अणु
	WARN_ON(!cpumask_test_cpu(cpu, &node_to_cpu_mask[nid]));
	WARN_ON(cpu_to_node_map[cpu] != nid);
	cpu_to_node_map[cpu] = 0;
	cpumask_clear_cpu(cpu, &node_to_cpu_mask[nid]);
पूर्ण


/**
 * build_cpu_to_node_map - setup cpu to node and node to cpumask arrays
 *
 * Build cpu to node mapping and initialize the per node cpu masks using
 * info from the node_cpuid array handed to us by ACPI.
 */
व्योम __init build_cpu_to_node_map(व्योम)
अणु
	पूर्णांक cpu, i, node;

	क्रम(node=0; node < MAX_NUMNODES; node++)
		cpumask_clear(&node_to_cpu_mask[node]);

	क्रम_each_possible_early_cpu(cpu) अणु
		node = NUMA_NO_NODE;
		क्रम (i = 0; i < NR_CPUS; ++i)
			अगर (cpu_physical_id(cpu) == node_cpuid[i].phys_id) अणु
				node = node_cpuid[i].nid;
				अवरोध;
			पूर्ण
		map_cpu_to_node(cpu, node);
	पूर्ण
पूर्ण
