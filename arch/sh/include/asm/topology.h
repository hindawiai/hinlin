<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_SH_TOPOLOGY_H
#घोषणा _ASM_SH_TOPOLOGY_H

#अगर_घोषित CONFIG_NUMA

#घोषणा cpu_to_node(cpu)	((व्योम)(cpu),0)

#घोषणा cpumask_of_node(node)	((व्योम)node, cpu_online_mask)

#घोषणा pcibus_to_node(bus)	((व्योम)(bus), -1)
#घोषणा cpumask_of_pcibus(bus)	(pcibus_to_node(bus) == -1 ? \
					cpu_all_mask : \
					cpumask_of_node(pcibus_to_node(bus)))

#पूर्ण_अगर

#घोषणा mc_capable()    (1)

स्थिर काष्ठा cpumask *cpu_coregroup_mask(पूर्णांक cpu);

बाह्य cpumask_t cpu_core_map[NR_CPUS];

#घोषणा topology_core_cpumask(cpu)	(&cpu_core_map[cpu])

#समावेश <यंत्र-generic/topology.h>

#पूर्ण_अगर /* _ASM_SH_TOPOLOGY_H */
