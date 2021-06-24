<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2018 Linaro Limited
 *
 * Author: Daniel Lezcano <daniel.lezcano@linaro.org>
 *
 * The idle injection framework provides a way to क्रमce CPUs to enter idle
 * states क्रम a specअगरied fraction of समय over a specअगरied period.
 *
 * It relies on the smpboot kthपढ़ोs feature providing common code क्रम CPU
 * hotplug and thपढ़ो [un]parking.
 *
 * All of the kthपढ़ोs used क्रम idle injection are created at init समय.
 *
 * Next, the users of the the idle injection framework provide a cpumask via
 * its रेजिस्टर function. The kthपढ़ोs will be synchronized with respect to
 * this cpumask.
 *
 * The idle + run duration is specअगरied via separate helpers and that allows
 * idle injection to be started.
 *
 * The idle injection kthपढ़ोs will call play_idle_precise() with the idle
 * duration and max allowed latency specअगरied as per the above.
 *
 * After all of them have been woken up, a समयr is set to start the next idle
 * injection cycle.
 *
 * The समयr पूर्णांकerrupt handler will wake up the idle injection kthपढ़ोs क्रम
 * all of the CPUs in the cpumask provided by the user.
 *
 * Idle injection is stopped synchronously and no leftover idle injection
 * kthपढ़ो activity after its completion is guaranteed.
 *
 * It is up to the user of this framework to provide a lock क्रम higher-level
 * synchronization to prevent race conditions like starting idle injection
 * जबतक unरेजिस्टरing from the framework.
 */
#घोषणा pr_fmt(fmt) "ii_dev: " fmt

#समावेश <linux/cpu.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/smpboot.h>
#समावेश <linux/idle_inject.h>

#समावेश <uapi/linux/sched/types.h>

/**
 * काष्ठा idle_inject_thपढ़ो - task on/off चयन काष्ठाure
 * @tsk: task injecting the idle cycles
 * @should_run: whether or not to run the task (क्रम the smpboot kthपढ़ो API)
 */
काष्ठा idle_inject_thपढ़ो अणु
	काष्ठा task_काष्ठा *tsk;
	पूर्णांक should_run;
पूर्ण;

/**
 * काष्ठा idle_inject_device - idle injection data
 * @समयr: idle injection period समयr
 * @idle_duration_us: duration of CPU idle समय to inject
 * @run_duration_us: duration of CPU run समय to allow
 * @latency_us: max allowed latency
 * @cpumask: mask of CPUs affected by idle injection
 */
काष्ठा idle_inject_device अणु
	काष्ठा hrसमयr समयr;
	अचिन्हित पूर्णांक idle_duration_us;
	अचिन्हित पूर्णांक run_duration_us;
	अचिन्हित पूर्णांक latency_us;
	अचिन्हित दीर्घ cpumask[];
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा idle_inject_thपढ़ो, idle_inject_thपढ़ो);
अटल DEFINE_PER_CPU(काष्ठा idle_inject_device *, idle_inject_device);

/**
 * idle_inject_wakeup - Wake up idle injection thपढ़ोs
 * @ii_dev: target idle injection device
 *
 * Every idle injection task associated with the given idle injection device
 * and running on an online CPU will be woken up.
 */
अटल व्योम idle_inject_wakeup(काष्ठा idle_inject_device *ii_dev)
अणु
	काष्ठा idle_inject_thपढ़ो *iit;
	अचिन्हित पूर्णांक cpu;

	क्रम_each_cpu_and(cpu, to_cpumask(ii_dev->cpumask), cpu_online_mask) अणु
		iit = per_cpu_ptr(&idle_inject_thपढ़ो, cpu);
		iit->should_run = 1;
		wake_up_process(iit->tsk);
	पूर्ण
पूर्ण

/**
 * idle_inject_समयr_fn - idle injection समयr function
 * @समयr: idle injection hrसमयr
 *
 * This function is called when the idle injection समयr expires.  It wakes up
 * idle injection tasks associated with the समयr and they, in turn, invoke
 * play_idle_precise() to inject a specअगरied amount of CPU idle समय.
 *
 * Return: HRTIMER_RESTART.
 */
अटल क्रमागत hrसमयr_restart idle_inject_समयr_fn(काष्ठा hrसमयr *समयr)
अणु
	अचिन्हित पूर्णांक duration_us;
	काष्ठा idle_inject_device *ii_dev =
		container_of(समयr, काष्ठा idle_inject_device, समयr);

	duration_us = READ_ONCE(ii_dev->run_duration_us);
	duration_us += READ_ONCE(ii_dev->idle_duration_us);

	idle_inject_wakeup(ii_dev);

	hrसमयr_क्रमward_now(समयr, ns_to_kसमय(duration_us * NSEC_PER_USEC));

	वापस HRTIMER_RESTART;
पूर्ण

/**
 * idle_inject_fn - idle injection work function
 * @cpu: the CPU owning the task
 *
 * This function calls play_idle_precise() to inject a specअगरied amount of CPU
 * idle समय.
 */
अटल व्योम idle_inject_fn(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा idle_inject_device *ii_dev;
	काष्ठा idle_inject_thपढ़ो *iit;

	ii_dev = per_cpu(idle_inject_device, cpu);
	iit = per_cpu_ptr(&idle_inject_thपढ़ो, cpu);

	/*
	 * Let the smpboot मुख्य loop know that the task should not run again.
	 */
	iit->should_run = 0;

	play_idle_precise(READ_ONCE(ii_dev->idle_duration_us) * NSEC_PER_USEC,
			  READ_ONCE(ii_dev->latency_us) * NSEC_PER_USEC);
पूर्ण

/**
 * idle_inject_set_duration - idle and run duration update helper
 * @run_duration_us: CPU run समय to allow in microseconds
 * @idle_duration_us: CPU idle समय to inject in microseconds
 */
व्योम idle_inject_set_duration(काष्ठा idle_inject_device *ii_dev,
			      अचिन्हित पूर्णांक run_duration_us,
			      अचिन्हित पूर्णांक idle_duration_us)
अणु
	अगर (run_duration_us && idle_duration_us) अणु
		WRITE_ONCE(ii_dev->run_duration_us, run_duration_us);
		WRITE_ONCE(ii_dev->idle_duration_us, idle_duration_us);
	पूर्ण
पूर्ण

/**
 * idle_inject_get_duration - idle and run duration retrieval helper
 * @run_duration_us: memory location to store the current CPU run समय
 * @idle_duration_us: memory location to store the current CPU idle समय
 */
व्योम idle_inject_get_duration(काष्ठा idle_inject_device *ii_dev,
			      अचिन्हित पूर्णांक *run_duration_us,
			      अचिन्हित पूर्णांक *idle_duration_us)
अणु
	*run_duration_us = READ_ONCE(ii_dev->run_duration_us);
	*idle_duration_us = READ_ONCE(ii_dev->idle_duration_us);
पूर्ण

/**
 * idle_inject_set_latency - set the maximum latency allowed
 * @latency_us: set the latency requirement क्रम the idle state
 */
व्योम idle_inject_set_latency(काष्ठा idle_inject_device *ii_dev,
			     अचिन्हित पूर्णांक latency_us)
अणु
	WRITE_ONCE(ii_dev->latency_us, latency_us);
पूर्ण

/**
 * idle_inject_start - start idle injections
 * @ii_dev: idle injection control device काष्ठाure
 *
 * The function starts idle injection by first waking up all of the idle
 * injection kthपढ़ोs associated with @ii_dev to let them inject CPU idle समय
 * sets up a समयr to start the next idle injection period.
 *
 * Return: -EINVAL अगर the CPU idle or CPU run समय is not set or 0 on success.
 */
पूर्णांक idle_inject_start(काष्ठा idle_inject_device *ii_dev)
अणु
	अचिन्हित पूर्णांक idle_duration_us = READ_ONCE(ii_dev->idle_duration_us);
	अचिन्हित पूर्णांक run_duration_us = READ_ONCE(ii_dev->run_duration_us);

	अगर (!idle_duration_us || !run_duration_us)
		वापस -EINVAL;

	pr_debug("Starting injecting idle cycles on CPUs '%*pbl'\n",
		 cpumask_pr_args(to_cpumask(ii_dev->cpumask)));

	idle_inject_wakeup(ii_dev);

	hrसमयr_start(&ii_dev->समयr,
		      ns_to_kसमय((idle_duration_us + run_duration_us) *
				  NSEC_PER_USEC),
		      HRTIMER_MODE_REL);

	वापस 0;
पूर्ण

/**
 * idle_inject_stop - stops idle injections
 * @ii_dev: idle injection control device काष्ठाure
 *
 * The function stops idle injection and रुकोs क्रम the thपढ़ोs to finish work.
 * If CPU idle समय is being injected when this function runs, then it will
 * रुको until the end of the cycle.
 *
 * When it वापसs, there is no more idle injection kthपढ़ो activity.  The
 * kthपढ़ोs are scheduled out and the periodic समयr is off.
 */
व्योम idle_inject_stop(काष्ठा idle_inject_device *ii_dev)
अणु
	काष्ठा idle_inject_thपढ़ो *iit;
	अचिन्हित पूर्णांक cpu;

	pr_debug("Stopping idle injection on CPUs '%*pbl'\n",
		 cpumask_pr_args(to_cpumask(ii_dev->cpumask)));

	hrसमयr_cancel(&ii_dev->समयr);

	/*
	 * Stopping idle injection requires all of the idle injection kthपढ़ोs
	 * associated with the given cpumask to be parked and stay that way, so
	 * prevent CPUs from going online at this poपूर्णांक.  Any CPUs going online
	 * after the loop below will be covered by clearing the should_run flag
	 * that will cause the smpboot मुख्य loop to schedule them out.
	 */
	cpu_hotplug_disable();

	/*
	 * Iterate over all (online + offline) CPUs here in हाल one of them
	 * goes offline with the should_run flag set so as to prevent its idle
	 * injection kthपढ़ो from running when the CPU goes online again after
	 * the ii_dev has been मुक्तd.
	 */
	क्रम_each_cpu(cpu, to_cpumask(ii_dev->cpumask)) अणु
		iit = per_cpu_ptr(&idle_inject_thपढ़ो, cpu);
		iit->should_run = 0;

		रुको_task_inactive(iit->tsk, 0);
	पूर्ण

	cpu_hotplug_enable();
पूर्ण

/**
 * idle_inject_setup - prepare the current task क्रम idle injection
 * @cpu: not used
 *
 * Called once, this function is in अक्षरge of setting the current task's
 * scheduler parameters to make it an RT task.
 */
अटल व्योम idle_inject_setup(अचिन्हित पूर्णांक cpu)
अणु
	sched_set_fअगरo(current);
पूर्ण

/**
 * idle_inject_should_run - function helper क्रम the smpboot API
 * @cpu: CPU the kthपढ़ो is running on
 *
 * Return: whether or not the thपढ़ो can run.
 */
अटल पूर्णांक idle_inject_should_run(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा idle_inject_thपढ़ो *iit =
		per_cpu_ptr(&idle_inject_thपढ़ो, cpu);

	वापस iit->should_run;
पूर्ण

/**
 * idle_inject_रेजिस्टर - initialize idle injection on a set of CPUs
 * @cpumask: CPUs to be affected by idle injection
 *
 * This function creates an idle injection control device काष्ठाure क्रम the
 * given set of CPUs and initializes the समयr associated with it.  It करोes not
 * start any injection cycles.
 *
 * Return: शून्य अगर memory allocation fails, idle injection control device
 * poपूर्णांकer on success.
 */
काष्ठा idle_inject_device *idle_inject_रेजिस्टर(काष्ठा cpumask *cpumask)
अणु
	काष्ठा idle_inject_device *ii_dev;
	पूर्णांक cpu, cpu_rb;

	ii_dev = kzalloc(माप(*ii_dev) + cpumask_size(), GFP_KERNEL);
	अगर (!ii_dev)
		वापस शून्य;

	cpumask_copy(to_cpumask(ii_dev->cpumask), cpumask);
	hrसमयr_init(&ii_dev->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	ii_dev->समयr.function = idle_inject_समयr_fn;
	ii_dev->latency_us = अच_पूर्णांक_उच्च;

	क्रम_each_cpu(cpu, to_cpumask(ii_dev->cpumask)) अणु

		अगर (per_cpu(idle_inject_device, cpu)) अणु
			pr_err("cpu%d is already registered\n", cpu);
			जाओ out_rollback;
		पूर्ण

		per_cpu(idle_inject_device, cpu) = ii_dev;
	पूर्ण

	वापस ii_dev;

out_rollback:
	क्रम_each_cpu(cpu_rb, to_cpumask(ii_dev->cpumask)) अणु
		अगर (cpu == cpu_rb)
			अवरोध;
		per_cpu(idle_inject_device, cpu_rb) = शून्य;
	पूर्ण

	kमुक्त(ii_dev);

	वापस शून्य;
पूर्ण

/**
 * idle_inject_unरेजिस्टर - unरेजिस्टर idle injection control device
 * @ii_dev: idle injection control device to unरेजिस्टर
 *
 * The function stops idle injection क्रम the given control device,
 * unरेजिस्टरs its kthपढ़ोs and मुक्तs memory allocated when that device was
 * created.
 */
व्योम idle_inject_unरेजिस्टर(काष्ठा idle_inject_device *ii_dev)
अणु
	अचिन्हित पूर्णांक cpu;

	idle_inject_stop(ii_dev);

	क्रम_each_cpu(cpu, to_cpumask(ii_dev->cpumask))
		per_cpu(idle_inject_device, cpu) = शून्य;

	kमुक्त(ii_dev);
पूर्ण

अटल काष्ठा smp_hotplug_thपढ़ो idle_inject_thपढ़ोs = अणु
	.store = &idle_inject_thपढ़ो.tsk,
	.setup = idle_inject_setup,
	.thपढ़ो_fn = idle_inject_fn,
	.thपढ़ो_comm = "idle_inject/%u",
	.thपढ़ो_should_run = idle_inject_should_run,
पूर्ण;

अटल पूर्णांक __init idle_inject_init(व्योम)
अणु
	वापस smpboot_रेजिस्टर_percpu_thपढ़ो(&idle_inject_thपढ़ोs);
पूर्ण
early_initcall(idle_inject_init);
