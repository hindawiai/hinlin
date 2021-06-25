<शैली गुरु>
/*
 * arch/parisc/kernel/topology.c
 *
 * Copyright (C) 2017 Helge Deller <deller@gmx.de>
 *
 * based on arch/arm/kernel/topology.c
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/percpu.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/topology.h>

#समावेश <यंत्र/topology.h>

 /*
  * cpu topology table
  */
काष्ठा cputopo_parisc cpu_topology[NR_CPUS] __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(cpu_topology);

स्थिर काष्ठा cpumask *cpu_coregroup_mask(पूर्णांक cpu)
अणु
	वापस &cpu_topology[cpu].core_sibling;
पूर्ण

अटल व्योम update_siblings_masks(अचिन्हित पूर्णांक cpuid)
अणु
	काष्ठा cputopo_parisc *cpu_topo, *cpuid_topo = &cpu_topology[cpuid];
	पूर्णांक cpu;

	/* update core and thपढ़ो sibling masks */
	क्रम_each_possible_cpu(cpu) अणु
		cpu_topo = &cpu_topology[cpu];

		अगर (cpuid_topo->socket_id != cpu_topo->socket_id)
			जारी;

		cpumask_set_cpu(cpuid, &cpu_topo->core_sibling);
		अगर (cpu != cpuid)
			cpumask_set_cpu(cpu, &cpuid_topo->core_sibling);

		अगर (cpuid_topo->core_id != cpu_topo->core_id)
			जारी;

		cpumask_set_cpu(cpuid, &cpu_topo->thपढ़ो_sibling);
		अगर (cpu != cpuid)
			cpumask_set_cpu(cpu, &cpuid_topo->thपढ़ो_sibling);
	पूर्ण
	smp_wmb();
पूर्ण

अटल पूर्णांक dualcores_found __initdata;

/*
 * store_cpu_topology is called at boot when only one cpu is running
 * and with the mutex cpu_hotplug.lock locked, when several cpus have booted,
 * which prevents simultaneous ग_लिखो access to cpu_topology array
 */
व्योम __init store_cpu_topology(अचिन्हित पूर्णांक cpuid)
अणु
	काष्ठा cputopo_parisc *cpuid_topo = &cpu_topology[cpuid];
	काष्ठा cpuinfo_parisc *p;
	पूर्णांक max_socket = -1;
	अचिन्हित दीर्घ cpu;

	/* If the cpu topology has been alपढ़ोy set, just वापस */
	अगर (cpuid_topo->core_id != -1)
		वापस;

	/* create cpu topology mapping */
	cpuid_topo->thपढ़ो_id = -1;
	cpuid_topo->core_id = 0;

	p = &per_cpu(cpu_data, cpuid);
	क्रम_each_online_cpu(cpu) अणु
		स्थिर काष्ठा cpuinfo_parisc *cpuinfo = &per_cpu(cpu_data, cpu);

		अगर (cpu == cpuid) /* ignore current cpu */
			जारी;

		अगर (cpuinfo->cpu_loc == p->cpu_loc) अणु
			cpuid_topo->core_id = cpu_topology[cpu].core_id;
			अगर (p->cpu_loc) अणु
				cpuid_topo->core_id++;
				cpuid_topo->socket_id = cpu_topology[cpu].socket_id;
				dualcores_found = 1;
				जारी;
			पूर्ण
		पूर्ण

		अगर (cpuid_topo->socket_id == -1)
			max_socket = max(max_socket, cpu_topology[cpu].socket_id);
	पूर्ण

	अगर (cpuid_topo->socket_id == -1)
		cpuid_topo->socket_id = max_socket + 1;

	update_siblings_masks(cpuid);

	pr_info("CPU%u: thread %d, cpu %d, socket %d\n",
		cpuid, cpu_topology[cpuid].thपढ़ो_id,
		cpu_topology[cpuid].core_id,
		cpu_topology[cpuid].socket_id);
पूर्ण

अटल काष्ठा sched_करोमुख्य_topology_level parisc_mc_topology[] = अणु
#अगर_घोषित CONFIG_SCHED_MC
	अणु cpu_coregroup_mask, cpu_core_flags, SD_INIT_NAME(MC) पूर्ण,
#पूर्ण_अगर

	अणु cpu_cpu_mask, SD_INIT_NAME(DIE) पूर्ण,
	अणु शून्य, पूर्ण,
पूर्ण;

/*
 * init_cpu_topology is called at boot when only one cpu is running
 * which prevent simultaneous ग_लिखो access to cpu_topology array
 */
व्योम __init init_cpu_topology(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;

	/* init core mask and capacity */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा cputopo_parisc *cpu_topo = &(cpu_topology[cpu]);

		cpu_topo->thपढ़ो_id = -1;
		cpu_topo->core_id =  -1;
		cpu_topo->socket_id = -1;
		cpumask_clear(&cpu_topo->core_sibling);
		cpumask_clear(&cpu_topo->thपढ़ो_sibling);
	पूर्ण
	smp_wmb();

	/* Set scheduler topology descriptor */
	अगर (dualcores_found)
		set_sched_topology(parisc_mc_topology);
पूर्ण
