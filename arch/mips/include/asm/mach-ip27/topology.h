<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_MACH_TOPOLOGY_H
#घोषणा _ASM_MACH_TOPOLOGY_H	1

#समावेश <यंत्र/sn/types.h>
#समावेश <यंत्र/mmzone.h>

काष्ठा cpuinfo_ip27 अणु
	nasid_t		p_nasid;	/* my node ID in numa-as-id-space */
	अचिन्हित लघु	p_speed;	/* cpu speed in MHz */
	अचिन्हित अक्षर	p_slice;	/* Physical position on node board */
पूर्ण;

बाह्य काष्ठा cpuinfo_ip27 sn_cpu_info[NR_CPUS];

#घोषणा cpu_to_node(cpu)	(cputonasid(cpu))
#घोषणा cpumask_of_node(node)	((node) == -1 ?				\
				 cpu_all_mask :				\
				 &hub_data(node)->h_cpus)
काष्ठा pci_bus;
बाह्य पूर्णांक pcibus_to_node(काष्ठा pci_bus *);

#घोषणा cpumask_of_pcibus(bus)	(cpumask_of_node(pcibus_to_node(bus)))

बाह्य अचिन्हित अक्षर __node_distances[MAX_NUMNODES][MAX_NUMNODES];

#घोषणा node_distance(from, to) (__node_distances[(from)][(to)])

#समावेश <यंत्र-generic/topology.h>

#पूर्ण_अगर /* _ASM_MACH_TOPOLOGY_H */
