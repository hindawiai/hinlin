<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/topology.c
 *
 *  Copyright (C) 2007  Paul Mundt
 */
#समावेश <linux/cpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/init.h>
#समावेश <linux/percpu.h>
#समावेश <linux/topology.h>
#समावेश <linux/node.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/export.h>

अटल DEFINE_PER_CPU(काष्ठा cpu, cpu_devices);

cpumask_t cpu_core_map[NR_CPUS];
EXPORT_SYMBOL(cpu_core_map);

अटल cpumask_t cpu_coregroup_map(पूर्णांक cpu)
अणु
	/*
	 * Presently all SH-X3 SMP cores are multi-cores, so just keep it
	 * simple until we have a method क्रम determining topology..
	 */
	वापस *cpu_possible_mask;
पूर्ण

स्थिर काष्ठा cpumask *cpu_coregroup_mask(पूर्णांक cpu)
अणु
	वापस &cpu_core_map[cpu];
पूर्ण

पूर्णांक arch_update_cpu_topology(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		cpu_core_map[cpu] = cpu_coregroup_map(cpu);

	वापस 0;
पूर्ण

अटल पूर्णांक __init topology_init(व्योम)
अणु
	पूर्णांक i, ret;

#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
	क्रम_each_online_node(i)
		रेजिस्टर_one_node(i);
#पूर्ण_अगर

	क्रम_each_present_cpu(i) अणु
		काष्ठा cpu *c = &per_cpu(cpu_devices, i);

		c->hotpluggable = 1;

		ret = रेजिस्टर_cpu(c, i);
		अगर (unlikely(ret))
			prपूर्णांकk(KERN_WARNING "%s: register_cpu %d failed (%d)\n",
			       __func__, i, ret);
	पूर्ण

#अगर defined(CONFIG_NUMA) && !defined(CONFIG_SMP)
	/*
	 * In the UP हाल, make sure the CPU association is still
	 * रेजिस्टरed under each node. Without this, sysfs fails
	 * to make the connection between nodes other than node0
	 * and cpu0.
	 */
	क्रम_each_online_node(i)
		अगर (i != numa_node_id())
			रेजिस्टर_cpu_under_node(raw_smp_processor_id(), i);
#पूर्ण_अगर

	वापस 0;
पूर्ण
subsys_initcall(topology_init);
