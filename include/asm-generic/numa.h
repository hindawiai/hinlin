<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_NUMA_H
#घोषणा __ASM_GENERIC_NUMA_H

#अगर_घोषित CONFIG_NUMA

#घोषणा NR_NODE_MEMBLKS		(MAX_NUMNODES * 2)

पूर्णांक __node_distance(पूर्णांक from, पूर्णांक to);
#घोषणा node_distance(a, b) __node_distance(a, b)

बाह्य nodemask_t numa_nodes_parsed __initdata;

बाह्य bool numa_off;

/* Mappings between node number and cpus on that node. */
बाह्य cpumask_var_t node_to_cpumask_map[MAX_NUMNODES];
व्योम numa_clear_node(अचिन्हित पूर्णांक cpu);

#अगर_घोषित CONFIG_DEBUG_PER_CPU_MAPS
स्थिर काष्ठा cpumask *cpumask_of_node(पूर्णांक node);
#अन्यथा
/* Returns a poपूर्णांकer to the cpumask of CPUs on Node 'node'. */
अटल अंतरभूत स्थिर काष्ठा cpumask *cpumask_of_node(पूर्णांक node)
अणु
	अगर (node == NUMA_NO_NODE)
		वापस cpu_all_mask;

	वापस node_to_cpumask_map[node];
पूर्ण
#पूर्ण_अगर

व्योम __init arch_numa_init(व्योम);
पूर्णांक __init numa_add_memblk(पूर्णांक nodeid, u64 start, u64 end);
व्योम __init numa_set_distance(पूर्णांक from, पूर्णांक to, पूर्णांक distance);
व्योम __init numa_मुक्त_distance(व्योम);
व्योम __init early_map_cpu_to_node(अचिन्हित पूर्णांक cpu, पूर्णांक nid);
व्योम numa_store_cpu_info(अचिन्हित पूर्णांक cpu);
व्योम numa_add_cpu(अचिन्हित पूर्णांक cpu);
व्योम numa_हटाओ_cpu(अचिन्हित पूर्णांक cpu);

#अन्यथा	/* CONFIG_NUMA */

अटल अंतरभूत व्योम numa_store_cpu_info(अचिन्हित पूर्णांक cpu) अणु पूर्ण
अटल अंतरभूत व्योम numa_add_cpu(अचिन्हित पूर्णांक cpu) अणु पूर्ण
अटल अंतरभूत व्योम numa_हटाओ_cpu(अचिन्हित पूर्णांक cpu) अणु पूर्ण
अटल अंतरभूत व्योम arch_numa_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम early_map_cpu_to_node(अचिन्हित पूर्णांक cpu, पूर्णांक nid) अणु पूर्ण

#पूर्ण_अगर	/* CONFIG_NUMA */

#पूर्ण_अगर	/* __ASM_GENERIC_NUMA_H */
