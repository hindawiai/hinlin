<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_STOP_MACHINE
#घोषणा _LINUX_STOP_MACHINE

#समावेश <linux/cpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/smp.h>
#समावेश <linux/list.h>

/*
 * stop_cpu[s]() is simplistic per-cpu maximum priority cpu
 * monopolization mechanism.  The caller can specअगरy a non-sleeping
 * function to be executed on a single or multiple cpus preempting all
 * other processes and monopolizing those cpus until it finishes.
 *
 * Resources क्रम this mechanism are pपुनः_स्मृतिated when a cpu is brought
 * up and requests are guaranteed to be served as दीर्घ as the target
 * cpus are online.
 */
प्रकार पूर्णांक (*cpu_stop_fn_t)(व्योम *arg);

#अगर_घोषित CONFIG_SMP

काष्ठा cpu_stop_work अणु
	काष्ठा list_head	list;		/* cpu_stopper->works */
	cpu_stop_fn_t		fn;
	अचिन्हित दीर्घ		caller;
	व्योम			*arg;
	काष्ठा cpu_stop_करोne	*करोne;
पूर्ण;

पूर्णांक stop_one_cpu(अचिन्हित पूर्णांक cpu, cpu_stop_fn_t fn, व्योम *arg);
पूर्णांक stop_two_cpus(अचिन्हित पूर्णांक cpu1, अचिन्हित पूर्णांक cpu2, cpu_stop_fn_t fn, व्योम *arg);
bool stop_one_cpu_noरुको(अचिन्हित पूर्णांक cpu, cpu_stop_fn_t fn, व्योम *arg,
			 काष्ठा cpu_stop_work *work_buf);
व्योम stop_machine_park(पूर्णांक cpu);
व्योम stop_machine_unpark(पूर्णांक cpu);
व्योम stop_machine_yield(स्थिर काष्ठा cpumask *cpumask);

बाह्य व्योम prपूर्णांक_stop_info(स्थिर अक्षर *log_lvl, काष्ठा task_काष्ठा *task);

#अन्यथा	/* CONFIG_SMP */

#समावेश <linux/workqueue.h>

काष्ठा cpu_stop_work अणु
	काष्ठा work_काष्ठा	work;
	cpu_stop_fn_t		fn;
	व्योम			*arg;
पूर्ण;

अटल अंतरभूत पूर्णांक stop_one_cpu(अचिन्हित पूर्णांक cpu, cpu_stop_fn_t fn, व्योम *arg)
अणु
	पूर्णांक ret = -ENOENT;
	preempt_disable();
	अगर (cpu == smp_processor_id())
		ret = fn(arg);
	preempt_enable();
	वापस ret;
पूर्ण

अटल व्योम stop_one_cpu_noरुको_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cpu_stop_work *stwork =
		container_of(work, काष्ठा cpu_stop_work, work);
	preempt_disable();
	stwork->fn(stwork->arg);
	preempt_enable();
पूर्ण

अटल अंतरभूत bool stop_one_cpu_noरुको(अचिन्हित पूर्णांक cpu,
				       cpu_stop_fn_t fn, व्योम *arg,
				       काष्ठा cpu_stop_work *work_buf)
अणु
	अगर (cpu == smp_processor_id()) अणु
		INIT_WORK(&work_buf->work, stop_one_cpu_noरुको_workfn);
		work_buf->fn = fn;
		work_buf->arg = arg;
		schedule_work(&work_buf->work);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत व्योम prपूर्णांक_stop_info(स्थिर अक्षर *log_lvl, काष्ठा task_काष्ठा *task) अणु पूर्ण

#पूर्ण_अगर	/* CONFIG_SMP */

/*
 * stop_machine "Bogolock": stop the entire machine, disable
 * पूर्णांकerrupts.  This is a very heavy lock, which is equivalent to
 * grabbing every spinlock (and more).  So the "read" side to such a
 * lock is anything which disables preemption.
 */
#अगर defined(CONFIG_SMP) || defined(CONFIG_HOTPLUG_CPU)

/**
 * stop_machine: मुक्तze the machine on all CPUs and run this function
 * @fn: the function to run
 * @data: the data ptr क्रम the @fn()
 * @cpus: the cpus to run the @fn() on (शून्य = any online cpu)
 *
 * Description: This causes a thपढ़ो to be scheduled on every cpu,
 * each of which disables पूर्णांकerrupts.  The result is that no one is
 * holding a spinlock or inside any other preempt-disabled region when
 * @fn() runs.
 *
 * This can be thought of as a very heavy ग_लिखो lock, equivalent to
 * grabbing every spinlock in the kernel.
 *
 * Protects against CPU hotplug.
 */
पूर्णांक stop_machine(cpu_stop_fn_t fn, व्योम *data, स्थिर काष्ठा cpumask *cpus);

/**
 * stop_machine_cpuslocked: मुक्तze the machine on all CPUs and run this function
 * @fn: the function to run
 * @data: the data ptr क्रम the @fn()
 * @cpus: the cpus to run the @fn() on (शून्य = any online cpu)
 *
 * Same as above. Must be called from with in a cpus_पढ़ो_lock() रक्षित
 * region. Aव्योमs nested calls to cpus_पढ़ो_lock().
 */
पूर्णांक stop_machine_cpuslocked(cpu_stop_fn_t fn, व्योम *data, स्थिर काष्ठा cpumask *cpus);

पूर्णांक stop_machine_from_inactive_cpu(cpu_stop_fn_t fn, व्योम *data,
				   स्थिर काष्ठा cpumask *cpus);
#अन्यथा	/* CONFIG_SMP || CONFIG_HOTPLUG_CPU */

अटल __always_अंतरभूत पूर्णांक stop_machine_cpuslocked(cpu_stop_fn_t fn, व्योम *data,
					  स्थिर काष्ठा cpumask *cpus)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	local_irq_save(flags);
	ret = fn(data);
	local_irq_restore(flags);
	वापस ret;
पूर्ण

अटल __always_अंतरभूत पूर्णांक
stop_machine(cpu_stop_fn_t fn, व्योम *data, स्थिर काष्ठा cpumask *cpus)
अणु
	वापस stop_machine_cpuslocked(fn, data, cpus);
पूर्ण

अटल __always_अंतरभूत पूर्णांक
stop_machine_from_inactive_cpu(cpu_stop_fn_t fn, व्योम *data,
			       स्थिर काष्ठा cpumask *cpus)
अणु
	वापस stop_machine(fn, data, cpus);
पूर्ण

#पूर्ण_अगर	/* CONFIG_SMP || CONFIG_HOTPLUG_CPU */
#पूर्ण_अगर	/* _LINUX_STOP_MACHINE */
