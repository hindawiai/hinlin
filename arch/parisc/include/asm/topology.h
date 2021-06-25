<शैली गुरु>
#अगर_अघोषित _ASM_PARISC_TOPOLOGY_H
#घोषणा _ASM_PARISC_TOPOLOGY_H

#अगर_घोषित CONFIG_PARISC_CPU_TOPOLOGY

#समावेश <linux/cpumask.h>

काष्ठा cputopo_parisc अणु
	पूर्णांक thपढ़ो_id;
	पूर्णांक core_id;
	पूर्णांक socket_id;
	cpumask_t thपढ़ो_sibling;
	cpumask_t core_sibling;
पूर्ण;

बाह्य काष्ठा cputopo_parisc cpu_topology[NR_CPUS];

#घोषणा topology_physical_package_id(cpu)	(cpu_topology[cpu].socket_id)
#घोषणा topology_core_id(cpu)		(cpu_topology[cpu].core_id)
#घोषणा topology_core_cpumask(cpu)	(&cpu_topology[cpu].core_sibling)
#घोषणा topology_sibling_cpumask(cpu)	(&cpu_topology[cpu].thपढ़ो_sibling)

व्योम init_cpu_topology(व्योम);
व्योम store_cpu_topology(अचिन्हित पूर्णांक cpuid);
स्थिर काष्ठा cpumask *cpu_coregroup_mask(पूर्णांक cpu);

#अन्यथा

अटल अंतरभूत व्योम init_cpu_topology(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम store_cpu_topology(अचिन्हित पूर्णांक cpuid) अणु पूर्ण

#पूर्ण_अगर

#समावेश <यंत्र-generic/topology.h>

#पूर्ण_अगर /* _ASM_ARM_TOPOLOGY_H */
