<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/linux/arch_topology.h - arch specअगरic cpu topology inक्रमmation
 */
#अगर_अघोषित _LINUX_ARCH_TOPOLOGY_H_
#घोषणा _LINUX_ARCH_TOPOLOGY_H_

#समावेश <linux/types.h>
#समावेश <linux/percpu.h>

व्योम topology_normalize_cpu_scale(व्योम);
पूर्णांक topology_update_cpu_topology(व्योम);

काष्ठा device_node;
bool topology_parse_cpu_capacity(काष्ठा device_node *cpu_node, पूर्णांक cpu);

DECLARE_PER_CPU(अचिन्हित दीर्घ, cpu_scale);

अटल अंतरभूत अचिन्हित दीर्घ topology_get_cpu_scale(पूर्णांक cpu)
अणु
	वापस per_cpu(cpu_scale, cpu);
पूर्ण

व्योम topology_set_cpu_scale(अचिन्हित पूर्णांक cpu, अचिन्हित दीर्घ capacity);

DECLARE_PER_CPU(अचिन्हित दीर्घ, arch_freq_scale);

अटल अंतरभूत अचिन्हित दीर्घ topology_get_freq_scale(पूर्णांक cpu)
अणु
	वापस per_cpu(arch_freq_scale, cpu);
पूर्ण

व्योम topology_set_freq_scale(स्थिर काष्ठा cpumask *cpus, अचिन्हित दीर्घ cur_freq,
			     अचिन्हित दीर्घ max_freq);
bool topology_scale_freq_invariant(व्योम);

क्रमागत scale_freq_source अणु
	SCALE_FREQ_SOURCE_CPUFREQ = 0,
	SCALE_FREQ_SOURCE_ARCH,
पूर्ण;

काष्ठा scale_freq_data अणु
	क्रमागत scale_freq_source source;
	व्योम (*set_freq_scale)(व्योम);
पूर्ण;

व्योम topology_scale_freq_tick(व्योम);
व्योम topology_set_scale_freq_source(काष्ठा scale_freq_data *data, स्थिर काष्ठा cpumask *cpus);
व्योम topology_clear_scale_freq_source(क्रमागत scale_freq_source source, स्थिर काष्ठा cpumask *cpus);

DECLARE_PER_CPU(अचिन्हित दीर्घ, thermal_pressure);

अटल अंतरभूत अचिन्हित दीर्घ topology_get_thermal_pressure(पूर्णांक cpu)
अणु
	वापस per_cpu(thermal_pressure, cpu);
पूर्ण

व्योम topology_set_thermal_pressure(स्थिर काष्ठा cpumask *cpus,
				   अचिन्हित दीर्घ th_pressure);

काष्ठा cpu_topology अणु
	पूर्णांक thपढ़ो_id;
	पूर्णांक core_id;
	पूर्णांक package_id;
	पूर्णांक llc_id;
	cpumask_t thपढ़ो_sibling;
	cpumask_t core_sibling;
	cpumask_t llc_sibling;
पूर्ण;

#अगर_घोषित CONFIG_GENERIC_ARCH_TOPOLOGY
बाह्य काष्ठा cpu_topology cpu_topology[NR_CPUS];

#घोषणा topology_physical_package_id(cpu)	(cpu_topology[cpu].package_id)
#घोषणा topology_core_id(cpu)		(cpu_topology[cpu].core_id)
#घोषणा topology_core_cpumask(cpu)	(&cpu_topology[cpu].core_sibling)
#घोषणा topology_sibling_cpumask(cpu)	(&cpu_topology[cpu].thपढ़ो_sibling)
#घोषणा topology_llc_cpumask(cpu)	(&cpu_topology[cpu].llc_sibling)
व्योम init_cpu_topology(व्योम);
व्योम store_cpu_topology(अचिन्हित पूर्णांक cpuid);
स्थिर काष्ठा cpumask *cpu_coregroup_mask(पूर्णांक cpu);
व्योम update_siblings_masks(अचिन्हित पूर्णांक cpu);
व्योम हटाओ_cpu_topology(अचिन्हित पूर्णांक cpuid);
व्योम reset_cpu_topology(व्योम);
पूर्णांक parse_acpi_topology(व्योम);
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_ARCH_TOPOLOGY_H_ */
