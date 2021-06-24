<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/smp.h>
#समावेश <linux/reboot.h>
#समावेश <linux/kexec.h>
#समावेश <linux/memblock.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>

/* This keeps a track of which one is crashing cpu. */
अटल पूर्णांक crashing_cpu = -1;
अटल cpumask_t cpus_in_crash = CPU_MASK_NONE;

#अगर_घोषित CONFIG_SMP
अटल व्योम crash_shutकरोwn_secondary(व्योम *passed_regs)
अणु
	काष्ठा pt_regs *regs = passed_regs;
	पूर्णांक cpu = smp_processor_id();

	/*
	 * If we are passed रेजिस्टरs, use those.  Otherwise get the
	 * regs from the last पूर्णांकerrupt, which should be correct, as
	 * we are in an पूर्णांकerrupt.  But अगर the regs are not there,
	 * pull them from the top of the stack.  They are probably
	 * wrong, but we need something to keep from crashing again.
	 */
	अगर (!regs)
		regs = get_irq_regs();
	अगर (!regs)
		regs = task_pt_regs(current);

	अगर (!cpu_online(cpu))
		वापस;

	/* We won't be sent IPIs any more. */
	set_cpu_online(cpu, false);

	local_irq_disable();
	अगर (!cpumask_test_cpu(cpu, &cpus_in_crash))
		crash_save_cpu(regs, cpu);
	cpumask_set_cpu(cpu, &cpus_in_crash);

	जबतक (!atomic_पढ़ो(&kexec_पढ़ोy_to_reboot))
		cpu_relax();

	kexec_reboot();

	/* NOTREACHED */
पूर्ण

अटल व्योम crash_kexec_prepare_cpus(व्योम)
अणु
	अटल पूर्णांक cpus_stopped;
	अचिन्हित पूर्णांक msecs;
	अचिन्हित पूर्णांक ncpus;

	अगर (cpus_stopped)
		वापस;

	ncpus = num_online_cpus() - 1;/* Excluding the panic cpu */

	smp_call_function(crash_shutकरोwn_secondary, शून्य, 0);
	smp_wmb();

	/*
	 * The crash CPU sends an IPI and रुको क्रम other CPUs to
	 * respond. Delay of at least 10 seconds.
	 */
	pr_emerg("Sending IPI to other cpus...\n");
	msecs = 10000;
	जबतक ((cpumask_weight(&cpus_in_crash) < ncpus) && (--msecs > 0)) अणु
		cpu_relax();
		mdelay(1);
	पूर्ण

	cpus_stopped = 1;
पूर्ण

/* Override the weak function in kernel/panic.c */
व्योम crash_smp_send_stop(व्योम)
अणु
	अगर (_crash_smp_send_stop)
		_crash_smp_send_stop();

	crash_kexec_prepare_cpus();
पूर्ण

#अन्यथा /* !defined(CONFIG_SMP)  */
अटल व्योम crash_kexec_prepare_cpus(व्योम) अणुपूर्ण
#पूर्ण_अगर /* !defined(CONFIG_SMP)	*/

व्योम शेष_machine_crash_shutकरोwn(काष्ठा pt_regs *regs)
अणु
	local_irq_disable();
	crashing_cpu = smp_processor_id();
	crash_save_cpu(regs, crashing_cpu);
	crash_kexec_prepare_cpus();
	cpumask_set_cpu(crashing_cpu, &cpus_in_crash);
पूर्ण
