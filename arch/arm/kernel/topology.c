<शैली गुरु>
/*
 * arch/arm/kernel/topology.c
 *
 * Copyright (C) 2011 Linaro Limited.
 * Written by: Vincent Guittot
 *
 * based on arch/sh/kernel/topology.c
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/arch_topology.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/percpu.h>
#समावेश <linux/node.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/of.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/topology.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/topology.h>

/*
 * cpu capacity scale management
 */

/*
 * cpu capacity table
 * This per cpu data काष्ठाure describes the relative capacity of each core.
 * On a heteregenous प्रणाली, cores करोn't have the same computation capacity
 * and we reflect that dअगरference in the cpu_capacity field so the scheduler
 * can take this dअगरference पूर्णांकo account during load balance. A per cpu
 * काष्ठाure is preferred because each CPU updates its own cpu_capacity field
 * during the load balance except क्रम idle cores. One idle core is selected
 * to run the rebalance_करोमुख्यs क्रम all idle cores and the cpu_capacity can be
 * updated during this sequence.
 */

#अगर_घोषित CONFIG_OF
काष्ठा cpu_efficiency अणु
	स्थिर अक्षर *compatible;
	अचिन्हित दीर्घ efficiency;
पूर्ण;

/*
 * Table of relative efficiency of each processors
 * The efficiency value must fit in 20bit and the final
 * cpu_scale value must be in the range
 *   0 < cpu_scale < 3*SCHED_CAPACITY_SCALE/2
 * in order to वापस at most 1 when DIV_ROUND_CLOSEST
 * is used to compute the capacity of a CPU.
 * Processors that are not defined in the table,
 * use the शेष SCHED_CAPACITY_SCALE value क्रम cpu_scale.
 */
अटल स्थिर काष्ठा cpu_efficiency table_efficiency[] = अणु
	अणु"arm,cortex-a15", 3891पूर्ण,
	अणु"arm,cortex-a7",  2048पूर्ण,
	अणुशून्य, पूर्ण,
पूर्ण;

अटल अचिन्हित दीर्घ *__cpu_capacity;
#घोषणा cpu_capacity(cpu)	__cpu_capacity[cpu]

अटल अचिन्हित दीर्घ middle_capacity = 1;
अटल bool cap_from_dt = true;

/*
 * Iterate all CPUs' descriptor in DT and compute the efficiency
 * (as per table_efficiency). Also calculate a middle efficiency
 * as बंद as possible to  (maxअणुeff_iपूर्ण - minअणुeff_iपूर्ण) / 2
 * This is later used to scale the cpu_capacity field such that an
 * 'average' CPU is of middle capacity. Also see the comments near
 * table_efficiency[] and update_cpu_capacity().
 */
अटल व्योम __init parse_dt_topology(व्योम)
अणु
	स्थिर काष्ठा cpu_efficiency *cpu_eff;
	काष्ठा device_node *cn = शून्य;
	अचिन्हित दीर्घ min_capacity = अच_दीर्घ_उच्च;
	अचिन्हित दीर्घ max_capacity = 0;
	अचिन्हित दीर्घ capacity = 0;
	पूर्णांक cpu = 0;

	__cpu_capacity = kसुस्मृति(nr_cpu_ids, माप(*__cpu_capacity),
				 GFP_NOWAIT);

	क्रम_each_possible_cpu(cpu) अणु
		स्थिर __be32 *rate;
		पूर्णांक len;

		/* too early to use cpu->of_node */
		cn = of_get_cpu_node(cpu, शून्य);
		अगर (!cn) अणु
			pr_err("missing device node for CPU %d\n", cpu);
			जारी;
		पूर्ण

		अगर (topology_parse_cpu_capacity(cn, cpu)) अणु
			of_node_put(cn);
			जारी;
		पूर्ण

		cap_from_dt = false;

		क्रम (cpu_eff = table_efficiency; cpu_eff->compatible; cpu_eff++)
			अगर (of_device_is_compatible(cn, cpu_eff->compatible))
				अवरोध;

		अगर (cpu_eff->compatible == शून्य)
			जारी;

		rate = of_get_property(cn, "clock-frequency", &len);
		अगर (!rate || len != 4) अणु
			pr_err("%pOF missing clock-frequency property\n", cn);
			जारी;
		पूर्ण

		capacity = ((be32_to_cpup(rate)) >> 20) * cpu_eff->efficiency;

		/* Save min capacity of the प्रणाली */
		अगर (capacity < min_capacity)
			min_capacity = capacity;

		/* Save max capacity of the प्रणाली */
		अगर (capacity > max_capacity)
			max_capacity = capacity;

		cpu_capacity(cpu) = capacity;
	पूर्ण

	/* If min and max capacities are equals, we bypass the update of the
	 * cpu_scale because all CPUs have the same capacity. Otherwise, we
	 * compute a middle_capacity factor that will ensure that the capacity
	 * of an 'average' CPU of the प्रणाली will be as बंद as possible to
	 * SCHED_CAPACITY_SCALE, which is the शेष value, but with the
	 * स्थिरraपूर्णांक explained near table_efficiency[].
	 */
	अगर (4*max_capacity < (3*(max_capacity + min_capacity)))
		middle_capacity = (min_capacity + max_capacity)
				>> (SCHED_CAPACITY_SHIFT+1);
	अन्यथा
		middle_capacity = ((max_capacity / 3)
				>> (SCHED_CAPACITY_SHIFT-1)) + 1;

	अगर (cap_from_dt)
		topology_normalize_cpu_scale();
पूर्ण

/*
 * Look क्रम a customed capacity of a CPU in the cpu_capacity table during the
 * boot. The update of all CPUs is in O(n^2) क्रम heteregeneous प्रणाली but the
 * function वापसs directly क्रम SMP प्रणाली.
 */
अटल व्योम update_cpu_capacity(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!cpu_capacity(cpu) || cap_from_dt)
		वापस;

	topology_set_cpu_scale(cpu, cpu_capacity(cpu) / middle_capacity);

	pr_info("CPU%u: update cpu_capacity %lu\n",
		cpu, topology_get_cpu_scale(cpu));
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम parse_dt_topology(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम update_cpu_capacity(अचिन्हित पूर्णांक cpuid) अणुपूर्ण
#पूर्ण_अगर

/*
 * store_cpu_topology is called at boot when only one cpu is running
 * and with the mutex cpu_hotplug.lock locked, when several cpus have booted,
 * which prevents simultaneous ग_लिखो access to cpu_topology array
 */
व्योम store_cpu_topology(अचिन्हित पूर्णांक cpuid)
अणु
	काष्ठा cpu_topology *cpuid_topo = &cpu_topology[cpuid];
	अचिन्हित पूर्णांक mpidr;

	अगर (cpuid_topo->package_id != -1)
		जाओ topology_populated;

	mpidr = पढ़ो_cpuid_mpidr();

	/* create cpu topology mapping */
	अगर ((mpidr & MPIDR_SMP_BITMASK) == MPIDR_SMP_VALUE) अणु
		/*
		 * This is a multiprocessor प्रणाली
		 * multiprocessor क्रमmat & multiprocessor mode field are set
		 */

		अगर (mpidr & MPIDR_MT_BITMASK) अणु
			/* core perक्रमmance पूर्णांकerdependency */
			cpuid_topo->thपढ़ो_id = MPIDR_AFFINITY_LEVEL(mpidr, 0);
			cpuid_topo->core_id = MPIDR_AFFINITY_LEVEL(mpidr, 1);
			cpuid_topo->package_id = MPIDR_AFFINITY_LEVEL(mpidr, 2);
		पूर्ण अन्यथा अणु
			/* largely independent cores */
			cpuid_topo->thपढ़ो_id = -1;
			cpuid_topo->core_id = MPIDR_AFFINITY_LEVEL(mpidr, 0);
			cpuid_topo->package_id = MPIDR_AFFINITY_LEVEL(mpidr, 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * This is an uniprocessor प्रणाली
		 * we are in multiprocessor क्रमmat but uniprocessor प्रणाली
		 * or in the old uniprocessor क्रमmat
		 */
		cpuid_topo->thपढ़ो_id = -1;
		cpuid_topo->core_id = 0;
		cpuid_topo->package_id = -1;
	पूर्ण

	update_cpu_capacity(cpuid);

	pr_info("CPU%u: thread %d, cpu %d, socket %d, mpidr %x\n",
		cpuid, cpu_topology[cpuid].thपढ़ो_id,
		cpu_topology[cpuid].core_id,
		cpu_topology[cpuid].package_id, mpidr);

topology_populated:
	update_siblings_masks(cpuid);
पूर्ण

/*
 * init_cpu_topology is called at boot when only one cpu is running
 * which prevent simultaneous ग_लिखो access to cpu_topology array
 */
व्योम __init init_cpu_topology(व्योम)
अणु
	reset_cpu_topology();
	smp_wmb();

	parse_dt_topology();
पूर्ण
