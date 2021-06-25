<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2002, Erich Focht, NEC
 *
 * All rights reserved.
 */
#अगर_अघोषित _ASM_IA64_TOPOLOGY_H
#घोषणा _ASM_IA64_TOPOLOGY_H

#समावेश <यंत्र/acpi.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/smp.h>

#अगर_घोषित CONFIG_NUMA

/* Nodes w/o CPUs are preferred क्रम memory allocations, see build_zonelists */
#घोषणा PENALTY_FOR_NODE_WITH_CPUS 255

/*
 * Nodes within this distance are eligible क्रम reclaim by zone_reclaim() when
 * zone_reclaim_mode is enabled.
 */
#घोषणा RECLAIM_DISTANCE 15

/*
 * Returns a biपंचांगask of CPUs on Node 'node'.
 */
#घोषणा cpumask_of_node(node) ((node) == -1 ?				\
			       cpu_all_mask :				\
			       &node_to_cpu_mask[node])

/*
 * Determines the node क्रम a given pci bus
 */
#घोषणा pcibus_to_node(bus) PCI_CONTROLLER(bus)->node

व्योम build_cpu_to_node_map(व्योम);

#पूर्ण_अगर /* CONFIG_NUMA */

#अगर_घोषित CONFIG_SMP
#घोषणा topology_physical_package_id(cpu)	(cpu_data(cpu)->socket_id)
#घोषणा topology_core_id(cpu)			(cpu_data(cpu)->core_id)
#घोषणा topology_core_cpumask(cpu)		(&cpu_core_map[cpu])
#घोषणा topology_sibling_cpumask(cpu)		(&per_cpu(cpu_sibling_map, cpu))
#पूर्ण_अगर

बाह्य व्योम arch_fix_phys_package_id(पूर्णांक num, u32 slot);

#घोषणा cpumask_of_pcibus(bus)	(pcibus_to_node(bus) == -1 ?		\
				 cpu_all_mask :				\
				 cpumask_of_node(pcibus_to_node(bus)))

#समावेश <यंत्र-generic/topology.h>

#पूर्ण_अगर /* _ASM_IA64_TOPOLOGY_H */
