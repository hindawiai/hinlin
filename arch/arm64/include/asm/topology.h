<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_TOPOLOGY_H
#घोषणा __ASM_TOPOLOGY_H

#समावेश <linux/cpumask.h>

#अगर_घोषित CONFIG_NUMA

काष्ठा pci_bus;
पूर्णांक pcibus_to_node(काष्ठा pci_bus *bus);
#घोषणा cpumask_of_pcibus(bus)	(pcibus_to_node(bus) == -1 ?		\
				 cpu_all_mask :				\
				 cpumask_of_node(pcibus_to_node(bus)))

#पूर्ण_अगर /* CONFIG_NUMA */

#समावेश <linux/arch_topology.h>

व्योम update_freq_counters_refs(व्योम);

/* Replace task scheduler's शेष frequency-invariant accounting */
#घोषणा arch_scale_freq_tick topology_scale_freq_tick
#घोषणा arch_set_freq_scale topology_set_freq_scale
#घोषणा arch_scale_freq_capacity topology_get_freq_scale
#घोषणा arch_scale_freq_invariant topology_scale_freq_invariant

/* Replace task scheduler's शेष cpu-invariant accounting */
#घोषणा arch_scale_cpu_capacity topology_get_cpu_scale

/* Enable topology flag updates */
#घोषणा arch_update_cpu_topology topology_update_cpu_topology

/* Replace task scheduler's शेष thermal pressure API */
#घोषणा arch_scale_thermal_pressure topology_get_thermal_pressure
#घोषणा arch_set_thermal_pressure   topology_set_thermal_pressure

#समावेश <यंत्र-generic/topology.h>

#पूर्ण_अगर /* _ASM_ARM_TOPOLOGY_H */
