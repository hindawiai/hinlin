<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_TOPOLOGY_H
#घोषणा _ASM_S390_TOPOLOGY_H

#समावेश <linux/cpumask.h>
#समावेश <यंत्र/numa.h>

काष्ठा sysinfo_15_1_x;
काष्ठा cpu;

#अगर_घोषित CONFIG_SCHED_TOPOLOGY

काष्ठा cpu_topology_s390 अणु
	अचिन्हित लघु thपढ़ो_id;
	अचिन्हित लघु core_id;
	अचिन्हित लघु socket_id;
	अचिन्हित लघु book_id;
	अचिन्हित लघु drawer_id;
	अचिन्हित लघु dedicated : 1;
	पूर्णांक booted_cores;
	cpumask_t thपढ़ो_mask;
	cpumask_t core_mask;
	cpumask_t book_mask;
	cpumask_t drawer_mask;
पूर्ण;

बाह्य काष्ठा cpu_topology_s390 cpu_topology[NR_CPUS];

#घोषणा topology_physical_package_id(cpu) (cpu_topology[cpu].socket_id)
#घोषणा topology_thपढ़ो_id(cpu)		  (cpu_topology[cpu].thपढ़ो_id)
#घोषणा topology_sibling_cpumask(cpu)	  (&cpu_topology[cpu].thपढ़ो_mask)
#घोषणा topology_core_id(cpu)		  (cpu_topology[cpu].core_id)
#घोषणा topology_core_cpumask(cpu)	  (&cpu_topology[cpu].core_mask)
#घोषणा topology_book_id(cpu)		  (cpu_topology[cpu].book_id)
#घोषणा topology_book_cpumask(cpu)	  (&cpu_topology[cpu].book_mask)
#घोषणा topology_drawer_id(cpu)		  (cpu_topology[cpu].drawer_id)
#घोषणा topology_drawer_cpumask(cpu)	  (&cpu_topology[cpu].drawer_mask)
#घोषणा topology_cpu_dedicated(cpu)	  (cpu_topology[cpu].dedicated)
#घोषणा topology_booted_cores(cpu)	  (cpu_topology[cpu].booted_cores)

#घोषणा mc_capable() 1

व्योम topology_init_early(व्योम);
पूर्णांक topology_cpu_init(काष्ठा cpu *);
पूर्णांक topology_set_cpu_management(पूर्णांक fc);
व्योम topology_schedule_update(व्योम);
व्योम store_topology(काष्ठा sysinfo_15_1_x *info);
व्योम update_cpu_masks(व्योम);
व्योम topology_expect_change(व्योम);
स्थिर काष्ठा cpumask *cpu_coregroup_mask(पूर्णांक cpu);

#अन्यथा /* CONFIG_SCHED_TOPOLOGY */

अटल अंतरभूत व्योम topology_init_early(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम topology_schedule_update(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक topology_cpu_init(काष्ठा cpu *cpu) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक topology_cpu_dedicated(पूर्णांक cpu_nr) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक topology_booted_cores(पूर्णांक cpu_nr) अणु वापस 1; पूर्ण
अटल अंतरभूत व्योम update_cpu_masks(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम topology_expect_change(व्योम) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_SCHED_TOPOLOGY */

#घोषणा POLARIZATION_UNKNOWN	(-1)
#घोषणा POLARIZATION_HRZ	(0)
#घोषणा POLARIZATION_VL		(1)
#घोषणा POLARIZATION_VM		(2)
#घोषणा POLARIZATION_VH		(3)

#घोषणा SD_BOOK_INIT	SD_CPU_INIT

#अगर_घोषित CONFIG_NUMA

#घोषणा cpu_to_node cpu_to_node
अटल अंतरभूत पूर्णांक cpu_to_node(पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण

/* Returns a poपूर्णांकer to the cpumask of CPUs on node 'node'. */
#घोषणा cpumask_of_node cpumask_of_node
अटल अंतरभूत स्थिर काष्ठा cpumask *cpumask_of_node(पूर्णांक node)
अणु
	वापस cpu_possible_mask;
पूर्ण

#घोषणा pcibus_to_node(bus) __pcibus_to_node(bus)

#अन्यथा /* !CONFIG_NUMA */

#घोषणा numa_node_id numa_node_id
अटल अंतरभूत पूर्णांक numa_node_id(व्योम)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_NUMA */

#समावेश <यंत्र-generic/topology.h>

#पूर्ण_अगर /* _ASM_S390_TOPOLOGY_H */
