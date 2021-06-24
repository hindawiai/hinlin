<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_MACH_TOPOLOGY_H
#घोषणा _ASM_MACH_TOPOLOGY_H

#अगर_घोषित CONFIG_NUMA

#घोषणा cpu_to_node(cpu)	(cpu_logical_map(cpu) >> 2)

बाह्य cpumask_t __node_cpumask[];
#घोषणा cpumask_of_node(node)	(&__node_cpumask[node])

काष्ठा pci_bus;
बाह्य पूर्णांक pcibus_to_node(काष्ठा pci_bus *);

#घोषणा cpumask_of_pcibus(bus)	(cpu_online_mask)

बाह्य अचिन्हित अक्षर __node_distances[MAX_NUMNODES][MAX_NUMNODES];

#घोषणा node_distance(from, to)	(__node_distances[(from)][(to)])

#पूर्ण_अगर

#समावेश <यंत्र-generic/topology.h>

#पूर्ण_अगर /* _ASM_MACH_TOPOLOGY_H */
