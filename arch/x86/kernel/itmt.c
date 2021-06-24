<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * iपंचांगt.c: Support Intel Turbo Boost Max Technology 3.0
 *
 * (C) Copyright 2016 Intel Corporation
 * Author: Tim Chen <tim.c.chen@linux.पूर्णांकel.com>
 *
 * On platक्रमms supporting Intel Turbo Boost Max Technology 3.0, (ITMT),
 * the maximum turbo frequencies of some cores in a CPU package may be
 * higher than क्रम the other cores in the same package.  In that हाल,
 * better perक्रमmance can be achieved by making the scheduler prefer
 * to run tasks on the CPUs with higher max turbo frequencies.
 *
 * This file provides functions and data काष्ठाures क्रम enabling the
 * scheduler to favor scheduling on cores can be boosted to a higher
 * frequency under ITMT.
 */

#समावेश <linux/sched.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/cpuset.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/nodemask.h>

अटल DEFINE_MUTEX(iपंचांगt_update_mutex);
DEFINE_PER_CPU_READ_MOSTLY(पूर्णांक, sched_core_priority);

/* Boolean to track अगर प्रणाली has ITMT capabilities */
अटल bool __पढ़ो_mostly sched_iपंचांगt_capable;

/*
 * Boolean to control whether we want to move processes to cpu capable
 * of higher turbo frequency क्रम cpus supporting Intel Turbo Boost Max
 * Technology 3.0.
 *
 * It can be set via /proc/sys/kernel/sched_iपंचांगt_enabled
 */
अचिन्हित पूर्णांक __पढ़ो_mostly sysctl_sched_iपंचांगt_enabled;

अटल पूर्णांक sched_iपंचांगt_update_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				     व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	अचिन्हित पूर्णांक old_sysctl;
	पूर्णांक ret;

	mutex_lock(&iपंचांगt_update_mutex);

	अगर (!sched_iपंचांगt_capable) अणु
		mutex_unlock(&iपंचांगt_update_mutex);
		वापस -EINVAL;
	पूर्ण

	old_sysctl = sysctl_sched_iपंचांगt_enabled;
	ret = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);

	अगर (!ret && ग_लिखो && old_sysctl != sysctl_sched_iपंचांगt_enabled) अणु
		x86_topology_update = true;
		rebuild_sched_करोमुख्यs();
	पूर्ण

	mutex_unlock(&iपंचांगt_update_mutex);

	वापस ret;
पूर्ण

अटल काष्ठा ctl_table iपंचांगt_kern_table[] = अणु
	अणु
		.procname	= "sched_itmt_enabled",
		.data		= &sysctl_sched_iपंचांगt_enabled,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= sched_iपंचांगt_update_handler,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table iपंचांगt_root_table[] = अणु
	अणु
		.procname	= "kernel",
		.mode		= 0555,
		.child		= iपंचांगt_kern_table,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table_header *iपंचांगt_sysctl_header;

/**
 * sched_set_iपंचांगt_support() - Indicate platक्रमm supports ITMT
 *
 * This function is used by the OS to indicate to scheduler that the platक्रमm
 * is capable of supporting the ITMT feature.
 *
 * The current scheme has the pstate driver detects अगर the प्रणाली
 * is ITMT capable and call sched_set_iपंचांगt_support.
 *
 * This must be करोne only after sched_set_iपंचांगt_core_prio
 * has been called to set the cpus' priorities.
 * It must not be called with cpu hot plug lock
 * held as we need to acquire the lock to rebuild sched करोमुख्यs
 * later.
 *
 * Return: 0 on success
 */
पूर्णांक sched_set_iपंचांगt_support(व्योम)
अणु
	mutex_lock(&iपंचांगt_update_mutex);

	अगर (sched_iपंचांगt_capable) अणु
		mutex_unlock(&iपंचांगt_update_mutex);
		वापस 0;
	पूर्ण

	iपंचांगt_sysctl_header = रेजिस्टर_sysctl_table(iपंचांगt_root_table);
	अगर (!iपंचांगt_sysctl_header) अणु
		mutex_unlock(&iपंचांगt_update_mutex);
		वापस -ENOMEM;
	पूर्ण

	sched_iपंचांगt_capable = true;

	sysctl_sched_iपंचांगt_enabled = 1;

	x86_topology_update = true;
	rebuild_sched_करोमुख्यs();

	mutex_unlock(&iपंचांगt_update_mutex);

	वापस 0;
पूर्ण

/**
 * sched_clear_iपंचांगt_support() - Revoke platक्रमm's support of ITMT
 *
 * This function is used by the OS to indicate that it has
 * revoked the platक्रमm's support of ITMT feature.
 *
 * It must not be called with cpu hot plug lock
 * held as we need to acquire the lock to rebuild sched करोमुख्यs
 * later.
 */
व्योम sched_clear_iपंचांगt_support(व्योम)
अणु
	mutex_lock(&iपंचांगt_update_mutex);

	अगर (!sched_iपंचांगt_capable) अणु
		mutex_unlock(&iपंचांगt_update_mutex);
		वापस;
	पूर्ण
	sched_iपंचांगt_capable = false;

	अगर (iपंचांगt_sysctl_header) अणु
		unरेजिस्टर_sysctl_table(iपंचांगt_sysctl_header);
		iपंचांगt_sysctl_header = शून्य;
	पूर्ण

	अगर (sysctl_sched_iपंचांगt_enabled) अणु
		/* disable sched_iपंचांगt अगर we are no दीर्घer ITMT capable */
		sysctl_sched_iपंचांगt_enabled = 0;
		x86_topology_update = true;
		rebuild_sched_करोमुख्यs();
	पूर्ण

	mutex_unlock(&iपंचांगt_update_mutex);
पूर्ण

पूर्णांक arch_asym_cpu_priority(पूर्णांक cpu)
अणु
	वापस per_cpu(sched_core_priority, cpu);
पूर्ण

/**
 * sched_set_iपंचांगt_core_prio() - Set CPU priority based on ITMT
 * @prio:	Priority of cpu core
 * @core_cpu:	The cpu number associated with the core
 *
 * The pstate driver will find out the max boost frequency
 * and call this function to set a priority proportional
 * to the max boost frequency. CPU with higher boost
 * frequency will receive higher priority.
 *
 * No need to rebuild sched करोमुख्य after updating
 * the CPU priorities. The sched करोमुख्यs have no
 * dependency on CPU priorities.
 */
व्योम sched_set_iपंचांगt_core_prio(पूर्णांक prio, पूर्णांक core_cpu)
अणु
	पूर्णांक cpu, i = 1;

	क्रम_each_cpu(cpu, topology_sibling_cpumask(core_cpu)) अणु
		पूर्णांक smt_prio;

		/*
		 * Ensure that the siblings are moved to the end
		 * of the priority chain and only used when
		 * all other high priority cpus are out of capacity.
		 */
		smt_prio = prio * smp_num_siblings / i;
		per_cpu(sched_core_priority, cpu) = smt_prio;
		i++;
	पूर्ण
पूर्ण
