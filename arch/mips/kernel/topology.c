<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/cpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/init.h>
#समावेश <linux/node.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/percpu.h>

अटल DEFINE_PER_CPU(काष्ठा cpu, cpu_devices);

अटल पूर्णांक __init topology_init(व्योम)
अणु
	पूर्णांक i, ret;

#अगर_घोषित CONFIG_NUMA
	क्रम_each_online_node(i)
		रेजिस्टर_one_node(i);
#पूर्ण_अगर /* CONFIG_NUMA */

	क्रम_each_present_cpu(i) अणु
		काष्ठा cpu *c = &per_cpu(cpu_devices, i);

		c->hotpluggable = !!i;
		ret = रेजिस्टर_cpu(c, i);
		अगर (ret)
			prपूर्णांकk(KERN_WARNING "topology_init: register_cpu %d "
			       "failed (%d)\n", i, ret);
	पूर्ण

	वापस 0;
पूर्ण

subsys_initcall(topology_init);
