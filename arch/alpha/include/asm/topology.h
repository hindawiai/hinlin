<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_ALPHA_TOPOLOGY_H
#घोषणा _ASM_ALPHA_TOPOLOGY_H

#समावेश <linux/smp.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/numa.h>
#समावेश <यंत्र/machvec.h>

#अगर_घोषित CONFIG_NUMA
अटल अंतरभूत पूर्णांक cpu_to_node(पूर्णांक cpu)
अणु
	पूर्णांक node;
	
	अगर (!alpha_mv.cpuid_to_nid)
		वापस 0;

	node = alpha_mv.cpuid_to_nid(cpu);

#अगर_घोषित DEBUG_NUMA
	BUG_ON(node < 0);
#पूर्ण_अगर

	वापस node;
पूर्ण

बाह्य काष्ठा cpumask node_to_cpumask_map[];
/* FIXME: This is dumb, recalculating every समय.  But simple. */
अटल स्थिर काष्ठा cpumask *cpumask_of_node(पूर्णांक node)
अणु
	पूर्णांक cpu;

	अगर (node == NUMA_NO_NODE)
		वापस cpu_all_mask;

	cpumask_clear(&node_to_cpumask_map[node]);

	क्रम_each_online_cpu(cpu) अणु
		अगर (cpu_to_node(cpu) == node)
			cpumask_set_cpu(cpu, node_to_cpumask_map[node]);
	पूर्ण

	वापस &node_to_cpumask_map[node];
पूर्ण

#घोषणा cpumask_of_pcibus(bus)	(cpu_online_mask)

#पूर्ण_अगर /* !CONFIG_NUMA */
# include <यंत्र-generic/topology.h>

#पूर्ण_अगर /* _ASM_ALPHA_TOPOLOGY_H */
