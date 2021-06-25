<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 Western Digital Corporation or its affiliates.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/err.h>
#समावेश <linux/irq.h>
#समावेश <linux/cpu.h>
#समावेश <linux/sched/hotplug.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/cpu_ops.h>
#समावेश <यंत्र/sbi.h>

व्योम cpu_stop(व्योम);
व्योम arch_cpu_idle_dead(व्योम)
अणु
	cpu_stop();
पूर्ण

bool cpu_has_hotplug(अचिन्हित पूर्णांक cpu)
अणु
	अगर (cpu_ops[cpu]->cpu_stop)
		वापस true;

	वापस false;
पूर्ण

/*
 * __cpu_disable runs on the processor to be shutकरोwn.
 */
पूर्णांक __cpu_disable(व्योम)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	अगर (!cpu_ops[cpu] || !cpu_ops[cpu]->cpu_stop)
		वापस -EOPNOTSUPP;

	अगर (cpu_ops[cpu]->cpu_disable)
		ret = cpu_ops[cpu]->cpu_disable(cpu);

	अगर (ret)
		वापस ret;

	हटाओ_cpu_topology(cpu);
	set_cpu_online(cpu, false);
	irq_migrate_all_off_this_cpu();

	वापस ret;
पूर्ण

/*
 * Called on the thपढ़ो which is asking क्रम a CPU to be shutकरोwn.
 */
व्योम __cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक ret = 0;

	अगर (!cpu_रुको_death(cpu, 5)) अणु
		pr_err("CPU %u: didn't die\n", cpu);
		वापस;
	पूर्ण
	pr_notice("CPU%u: off\n", cpu);

	/* Verअगरy from the firmware अगर the cpu is really stopped*/
	अगर (cpu_ops[cpu]->cpu_is_stopped)
		ret = cpu_ops[cpu]->cpu_is_stopped(cpu);
	अगर (ret)
		pr_warn("CPU%d may not have stopped: %d\n", cpu, ret);
पूर्ण

/*
 * Called from the idle thपढ़ो क्रम the CPU which has been shutकरोwn.
 */
व्योम cpu_stop(व्योम)
अणु
	idle_task_निकास();

	(व्योम)cpu_report_death();

	cpu_ops[smp_processor_id()]->cpu_stop();
	/* It should never reach here */
	BUG();
पूर्ण
