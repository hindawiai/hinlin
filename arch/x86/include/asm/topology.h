<शैली गुरु>
/*
 * Written by: Matthew Dobson, IBM Corporation
 *
 * Copyright (C) 2002, IBM Corp.
 *
 * All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Send feedback to <colpatch@us.ibm.com>
 */
#अगर_अघोषित _ASM_X86_TOPOLOGY_H
#घोषणा _ASM_X86_TOPOLOGY_H

/*
 * to preserve the visibility of NUMA_NO_NODE definition,
 * moved to there from here.  May be used independent of
 * CONFIG_NUMA.
 */
#समावेश <linux/numa.h>

#अगर_घोषित CONFIG_NUMA
#समावेश <linux/cpumask.h>

#समावेश <यंत्र/mpspec.h>
#समावेश <यंत्र/percpu.h>

/* Mappings between logical cpu number and node number */
DECLARE_EARLY_PER_CPU(पूर्णांक, x86_cpu_to_node_map);

#अगर_घोषित CONFIG_DEBUG_PER_CPU_MAPS
/*
 * override generic percpu implementation of cpu_to_node
 */
बाह्य पूर्णांक __cpu_to_node(पूर्णांक cpu);
#घोषणा cpu_to_node __cpu_to_node

बाह्य पूर्णांक early_cpu_to_node(पूर्णांक cpu);

#अन्यथा	/* !CONFIG_DEBUG_PER_CPU_MAPS */

/* Same function but used अगर called beक्रमe per_cpu areas are setup */
अटल अंतरभूत पूर्णांक early_cpu_to_node(पूर्णांक cpu)
अणु
	वापस early_per_cpu(x86_cpu_to_node_map, cpu);
पूर्ण

#पूर्ण_अगर /* !CONFIG_DEBUG_PER_CPU_MAPS */

/* Mappings between node number and cpus on that node. */
बाह्य cpumask_var_t node_to_cpumask_map[MAX_NUMNODES];

#अगर_घोषित CONFIG_DEBUG_PER_CPU_MAPS
बाह्य स्थिर काष्ठा cpumask *cpumask_of_node(पूर्णांक node);
#अन्यथा
/* Returns a poपूर्णांकer to the cpumask of CPUs on Node 'node'. */
अटल अंतरभूत स्थिर काष्ठा cpumask *cpumask_of_node(पूर्णांक node)
अणु
	वापस node_to_cpumask_map[node];
पूर्ण
#पूर्ण_अगर

बाह्य व्योम setup_node_to_cpumask_map(व्योम);

#घोषणा pcibus_to_node(bus) __pcibus_to_node(bus)

बाह्य पूर्णांक __node_distance(पूर्णांक, पूर्णांक);
#घोषणा node_distance(a, b) __node_distance(a, b)

#अन्यथा /* !CONFIG_NUMA */

अटल अंतरभूत पूर्णांक numa_node_id(व्योम)
अणु
	वापस 0;
पूर्ण
/*
 * indicate override:
 */
#घोषणा numa_node_id numa_node_id

अटल अंतरभूत पूर्णांक early_cpu_to_node(पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम setup_node_to_cpumask_map(व्योम) अणु पूर्ण

#पूर्ण_अगर

#समावेश <यंत्र-generic/topology.h>

बाह्य स्थिर काष्ठा cpumask *cpu_coregroup_mask(पूर्णांक cpu);

#घोषणा topology_logical_package_id(cpu)	(cpu_data(cpu).logical_proc_id)
#घोषणा topology_physical_package_id(cpu)	(cpu_data(cpu).phys_proc_id)
#घोषणा topology_logical_die_id(cpu)		(cpu_data(cpu).logical_die_id)
#घोषणा topology_die_id(cpu)			(cpu_data(cpu).cpu_die_id)
#घोषणा topology_core_id(cpu)			(cpu_data(cpu).cpu_core_id)

बाह्य अचिन्हित पूर्णांक __max_die_per_package;

#अगर_घोषित CONFIG_SMP
#घोषणा topology_die_cpumask(cpu)		(per_cpu(cpu_die_map, cpu))
#घोषणा topology_core_cpumask(cpu)		(per_cpu(cpu_core_map, cpu))
#घोषणा topology_sibling_cpumask(cpu)		(per_cpu(cpu_sibling_map, cpu))

बाह्य अचिन्हित पूर्णांक __max_logical_packages;
#घोषणा topology_max_packages()			(__max_logical_packages)

अटल अंतरभूत पूर्णांक topology_max_die_per_package(व्योम)
अणु
	वापस __max_die_per_package;
पूर्ण

बाह्य पूर्णांक __max_smt_thपढ़ोs;

अटल अंतरभूत पूर्णांक topology_max_smt_thपढ़ोs(व्योम)
अणु
	वापस __max_smt_thपढ़ोs;
पूर्ण

पूर्णांक topology_update_package_map(अचिन्हित पूर्णांक apicid, अचिन्हित पूर्णांक cpu);
पूर्णांक topology_update_die_map(अचिन्हित पूर्णांक dieid, अचिन्हित पूर्णांक cpu);
पूर्णांक topology_phys_to_logical_pkg(अचिन्हित पूर्णांक pkg);
पूर्णांक topology_phys_to_logical_die(अचिन्हित पूर्णांक die, अचिन्हित पूर्णांक cpu);
bool topology_is_primary_thपढ़ो(अचिन्हित पूर्णांक cpu);
bool topology_smt_supported(व्योम);
#अन्यथा
#घोषणा topology_max_packages()			(1)
अटल अंतरभूत पूर्णांक
topology_update_package_map(अचिन्हित पूर्णांक apicid, अचिन्हित पूर्णांक cpu) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक
topology_update_die_map(अचिन्हित पूर्णांक dieid, अचिन्हित पूर्णांक cpu) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक topology_phys_to_logical_pkg(अचिन्हित पूर्णांक pkg) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक topology_phys_to_logical_die(अचिन्हित पूर्णांक die,
		अचिन्हित पूर्णांक cpu) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक topology_max_die_per_package(व्योम) अणु वापस 1; पूर्ण
अटल अंतरभूत पूर्णांक topology_max_smt_thपढ़ोs(व्योम) अणु वापस 1; पूर्ण
अटल अंतरभूत bool topology_is_primary_thपढ़ो(अचिन्हित पूर्णांक cpu) अणु वापस true; पूर्ण
अटल अंतरभूत bool topology_smt_supported(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम arch_fix_phys_package_id(पूर्णांक num, u32 slot)
अणु
पूर्ण

काष्ठा pci_bus;
पूर्णांक x86_pci_root_bus_node(पूर्णांक bus);
व्योम x86_pci_root_bus_resources(पूर्णांक bus, काष्ठा list_head *resources);

बाह्य bool x86_topology_update;

#अगर_घोषित CONFIG_SCHED_MC_PRIO
#समावेश <यंत्र/percpu.h>

DECLARE_PER_CPU_READ_MOSTLY(पूर्णांक, sched_core_priority);
बाह्य अचिन्हित पूर्णांक __पढ़ो_mostly sysctl_sched_iपंचांगt_enabled;

/* Interface to set priority of a cpu */
व्योम sched_set_iपंचांगt_core_prio(पूर्णांक prio, पूर्णांक core_cpu);

/* Interface to notअगरy scheduler that प्रणाली supports ITMT */
पूर्णांक sched_set_iपंचांगt_support(व्योम);

/* Interface to notअगरy scheduler that प्रणाली revokes ITMT support */
व्योम sched_clear_iपंचांगt_support(व्योम);

#अन्यथा /* CONFIG_SCHED_MC_PRIO */

#घोषणा sysctl_sched_iपंचांगt_enabled	0
अटल अंतरभूत व्योम sched_set_iपंचांगt_core_prio(पूर्णांक prio, पूर्णांक core_cpu)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक sched_set_iपंचांगt_support(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम sched_clear_iपंचांगt_support(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SCHED_MC_PRIO */

#अगर defined(CONFIG_SMP) && defined(CONFIG_X86_64)
#समावेश <यंत्र/cpufeature.h>

DECLARE_STATIC_KEY_FALSE(arch_scale_freq_key);

#घोषणा arch_scale_freq_invariant() अटल_branch_likely(&arch_scale_freq_key)

DECLARE_PER_CPU(अचिन्हित दीर्घ, arch_freq_scale);

अटल अंतरभूत दीर्घ arch_scale_freq_capacity(पूर्णांक cpu)
अणु
	वापस per_cpu(arch_freq_scale, cpu);
पूर्ण
#घोषणा arch_scale_freq_capacity arch_scale_freq_capacity

बाह्य व्योम arch_scale_freq_tick(व्योम);
#घोषणा arch_scale_freq_tick arch_scale_freq_tick

बाह्य व्योम arch_set_max_freq_ratio(bool turbo_disabled);
#अन्यथा
अटल अंतरभूत व्योम arch_set_max_freq_ratio(bool turbo_disabled)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI_CPPC_LIB
व्योम init_freq_invariance_cppc(व्योम);
#घोषणा init_freq_invariance_cppc init_freq_invariance_cppc
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_TOPOLOGY_H */
