<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_TOPOLOGY_H
#घोषणा _ASM_POWERPC_TOPOLOGY_H
#अगर_घोषित __KERNEL__


काष्ठा device;
काष्ठा device_node;
काष्ठा drmem_lmb;

#अगर_घोषित CONFIG_NUMA

/*
 * If zone_reclaim_mode is enabled, a RECLAIM_DISTANCE of 10 will mean that
 * all zones on all nodes will be eligible क्रम zone_reclaim().
 */
#घोषणा RECLAIM_DISTANCE 10

#समावेश <यंत्र/mmzone.h>

#घोषणा cpumask_of_node(node) ((node) == -1 ?				\
			       cpu_all_mask :				\
			       node_to_cpumask_map[node])

काष्ठा pci_bus;
#अगर_घोषित CONFIG_PCI
बाह्य पूर्णांक pcibus_to_node(काष्ठा pci_bus *bus);
#अन्यथा
अटल अंतरभूत पूर्णांक pcibus_to_node(काष्ठा pci_bus *bus)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर

#घोषणा cpumask_of_pcibus(bus)	(pcibus_to_node(bus) == -1 ?		\
				 cpu_all_mask :				\
				 cpumask_of_node(pcibus_to_node(bus)))

बाह्य पूर्णांक cpu_distance(__be32 *cpu1_assoc, __be32 *cpu2_assoc);
बाह्य पूर्णांक __node_distance(पूर्णांक, पूर्णांक);
#घोषणा node_distance(a, b) __node_distance(a, b)

बाह्य व्योम __init dump_numa_cpu_topology(व्योम);

बाह्य पूर्णांक sysfs_add_device_to_node(काष्ठा device *dev, पूर्णांक nid);
बाह्य व्योम sysfs_हटाओ_device_from_node(काष्ठा device *dev, पूर्णांक nid);

अटल अंतरभूत व्योम update_numa_cpu_lookup_table(अचिन्हित पूर्णांक cpu, पूर्णांक node)
अणु
	numa_cpu_lookup_table[cpu] = node;
पूर्ण

अटल अंतरभूत पूर्णांक early_cpu_to_node(पूर्णांक cpu)
अणु
	पूर्णांक nid;

	nid = numa_cpu_lookup_table[cpu];

	/*
	 * Fall back to node 0 अगर nid is unset (it should be, except bugs).
	 * This allows callers to safely करो NODE_DATA(early_cpu_to_node(cpu)).
	 */
	वापस (nid < 0) ? 0 : nid;
पूर्ण

पूर्णांक of_drconf_to_nid_single(काष्ठा drmem_lmb *lmb);

#अन्यथा

अटल अंतरभूत पूर्णांक early_cpu_to_node(पूर्णांक cpu) अणु वापस 0; पूर्ण

अटल अंतरभूत व्योम dump_numa_cpu_topology(व्योम) अणुपूर्ण

अटल अंतरभूत पूर्णांक sysfs_add_device_to_node(काष्ठा device *dev, पूर्णांक nid)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम sysfs_हटाओ_device_from_node(काष्ठा device *dev,
						पूर्णांक nid)
अणु
पूर्ण

अटल अंतरभूत व्योम update_numa_cpu_lookup_table(अचिन्हित पूर्णांक cpu, पूर्णांक node) अणुपूर्ण

अटल अंतरभूत पूर्णांक cpu_distance(__be32 *cpu1_assoc, __be32 *cpu2_assoc)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक of_drconf_to_nid_single(काष्ठा drmem_lmb *lmb)
अणु
	वापस first_online_node;
पूर्ण

#पूर्ण_अगर /* CONFIG_NUMA */

#अगर defined(CONFIG_NUMA) && defined(CONFIG_PPC_SPLPAR)
बाह्य पूर्णांक find_and_online_cpu_nid(पूर्णांक cpu);
बाह्य पूर्णांक cpu_to_coregroup_id(पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत पूर्णांक find_and_online_cpu_nid(पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cpu_to_coregroup_id(पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_SMP
	वापस cpu_to_core_id(cpu);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* CONFIG_NUMA && CONFIG_PPC_SPLPAR */

#समावेश <यंत्र-generic/topology.h>

#अगर_घोषित CONFIG_SMP
#समावेश <यंत्र/cputable.h>

#अगर_घोषित CONFIG_PPC64
#समावेश <यंत्र/smp.h>

#घोषणा topology_physical_package_id(cpu)	(cpu_to_chip_id(cpu))

#घोषणा topology_sibling_cpumask(cpu)	(per_cpu(cpu_sibling_map, cpu))
#घोषणा topology_core_cpumask(cpu)	(per_cpu(cpu_core_map, cpu))
#घोषणा topology_core_id(cpu)		(cpu_to_core_id(cpu))

#पूर्ण_अगर
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर	/* _ASM_POWERPC_TOPOLOGY_H */
