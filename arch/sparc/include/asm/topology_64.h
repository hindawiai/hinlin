<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_SPARC64_TOPOLOGY_H
#घोषणा _ASM_SPARC64_TOPOLOGY_H

#अगर_घोषित CONFIG_NUMA

#समावेश <यंत्र/mmzone.h>

अटल अंतरभूत पूर्णांक cpu_to_node(पूर्णांक cpu)
अणु
	वापस numa_cpu_lookup_table[cpu];
पूर्ण

#घोषणा cpumask_of_node(node) ((node) == -1 ?				\
			       cpu_all_mask :				\
			       &numa_cpumask_lookup_table[node])

काष्ठा pci_bus;
#अगर_घोषित CONFIG_PCI
पूर्णांक pcibus_to_node(काष्ठा pci_bus *pbus);
#अन्यथा
अटल अंतरभूत पूर्णांक pcibus_to_node(काष्ठा pci_bus *pbus)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर

#घोषणा cpumask_of_pcibus(bus)	\
	(pcibus_to_node(bus) == -1 ? \
	 cpu_all_mask : \
	 cpumask_of_node(pcibus_to_node(bus)))

पूर्णांक __node_distance(पूर्णांक, पूर्णांक);
#घोषणा node_distance(a, b) __node_distance(a, b)

#अन्यथा /* CONFIG_NUMA */

#समावेश <यंत्र-generic/topology.h>

#पूर्ण_अगर /* !(CONFIG_NUMA) */

#अगर_घोषित CONFIG_SMP

#समावेश <यंत्र/cpudata.h>

#घोषणा topology_physical_package_id(cpu)	(cpu_data(cpu).proc_id)
#घोषणा topology_core_id(cpu)			(cpu_data(cpu).core_id)
#घोषणा topology_core_cpumask(cpu)		(&cpu_core_sib_map[cpu])
#घोषणा topology_core_cache_cpumask(cpu)	(&cpu_core_sib_cache_map[cpu])
#घोषणा topology_sibling_cpumask(cpu)		(&per_cpu(cpu_sibling_map, cpu))
#पूर्ण_अगर /* CONFIG_SMP */

बाह्य cpumask_t cpu_core_map[NR_CPUS];
बाह्य cpumask_t cpu_core_sib_map[NR_CPUS];
बाह्य cpumask_t cpu_core_sib_cache_map[NR_CPUS];

/**
 * Return cores that shares the last level cache.
 */
अटल अंतरभूत स्थिर काष्ठा cpumask *cpu_coregroup_mask(पूर्णांक cpu)
अणु
	वापस &cpu_core_sib_cache_map[cpu];
पूर्ण

#पूर्ण_अगर /* _ASM_SPARC64_TOPOLOGY_H */
