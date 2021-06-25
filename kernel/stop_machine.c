<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * kernel/stop_machine.c
 *
 * Copyright (C) 2008, 2005	IBM Corporation.
 * Copyright (C) 2008, 2005	Rusty Russell rusty@rustcorp.com.au
 * Copyright (C) 2010		SUSE Linux Products GmbH
 * Copyright (C) 2010		Tejun Heo <tj@kernel.org>
 */
#समावेश <linux/compiler.h>
#समावेश <linux/completion.h>
#समावेश <linux/cpu.h>
#समावेश <linux/init.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/export.h>
#समावेश <linux/percpu.h>
#समावेश <linux/sched.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/smpboot.h>
#समावेश <linux/atomic.h>
#समावेश <linux/nmi.h>
#समावेश <linux/sched/wake_q.h>

/*
 * Structure to determine completion condition and record errors.  May
 * be shared by works on dअगरferent cpus.
 */
काष्ठा cpu_stop_करोne अणु
	atomic_t		nr_toकरो;	/* nr left to execute */
	पूर्णांक			ret;		/* collected वापस value */
	काष्ठा completion	completion;	/* fired अगर nr_toकरो reaches 0 */
पूर्ण;

/* the actual stopper, one per every possible cpu, enabled on online cpus */
काष्ठा cpu_stopper अणु
	काष्ठा task_काष्ठा	*thपढ़ो;

	raw_spinlock_t		lock;
	bool			enabled;	/* is this stopper enabled? */
	काष्ठा list_head	works;		/* list of pending works */

	काष्ठा cpu_stop_work	stop_work;	/* क्रम stop_cpus */
	अचिन्हित दीर्घ		caller;
	cpu_stop_fn_t		fn;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा cpu_stopper, cpu_stopper);
अटल bool stop_machine_initialized = false;

व्योम prपूर्णांक_stop_info(स्थिर अक्षर *log_lvl, काष्ठा task_काष्ठा *task)
अणु
	/*
	 * If @task is a stopper task, it cannot migrate and task_cpu() is
	 * stable.
	 */
	काष्ठा cpu_stopper *stopper = per_cpu_ptr(&cpu_stopper, task_cpu(task));

	अगर (task != stopper->thपढ़ो)
		वापस;

	prपूर्णांकk("%sStopper: %pS <- %pS\n", log_lvl, stopper->fn, (व्योम *)stopper->caller);
पूर्ण

/* अटल data क्रम stop_cpus */
अटल DEFINE_MUTEX(stop_cpus_mutex);
अटल bool stop_cpus_in_progress;

अटल व्योम cpu_stop_init_करोne(काष्ठा cpu_stop_करोne *करोne, अचिन्हित पूर्णांक nr_toकरो)
अणु
	स_रखो(करोne, 0, माप(*करोne));
	atomic_set(&करोne->nr_toकरो, nr_toकरो);
	init_completion(&करोne->completion);
पूर्ण

/* संकेत completion unless @करोne is शून्य */
अटल व्योम cpu_stop_संकेत_करोne(काष्ठा cpu_stop_करोne *करोne)
अणु
	अगर (atomic_dec_and_test(&करोne->nr_toकरो))
		complete(&करोne->completion);
पूर्ण

अटल व्योम __cpu_stop_queue_work(काष्ठा cpu_stopper *stopper,
					काष्ठा cpu_stop_work *work,
					काष्ठा wake_q_head *wakeq)
अणु
	list_add_tail(&work->list, &stopper->works);
	wake_q_add(wakeq, stopper->thपढ़ो);
पूर्ण

/* queue @work to @stopper.  अगर offline, @work is completed immediately */
अटल bool cpu_stop_queue_work(अचिन्हित पूर्णांक cpu, काष्ठा cpu_stop_work *work)
अणु
	काष्ठा cpu_stopper *stopper = &per_cpu(cpu_stopper, cpu);
	DEFINE_WAKE_Q(wakeq);
	अचिन्हित दीर्घ flags;
	bool enabled;

	preempt_disable();
	raw_spin_lock_irqsave(&stopper->lock, flags);
	enabled = stopper->enabled;
	अगर (enabled)
		__cpu_stop_queue_work(stopper, work, &wakeq);
	अन्यथा अगर (work->करोne)
		cpu_stop_संकेत_करोne(work->करोne);
	raw_spin_unlock_irqrestore(&stopper->lock, flags);

	wake_up_q(&wakeq);
	preempt_enable();

	वापस enabled;
पूर्ण

/**
 * stop_one_cpu - stop a cpu
 * @cpu: cpu to stop
 * @fn: function to execute
 * @arg: argument to @fn
 *
 * Execute @fn(@arg) on @cpu.  @fn is run in a process context with
 * the highest priority preempting any task on the cpu and
 * monopolizing it.  This function वापसs after the execution is
 * complete.
 *
 * This function करोesn't guarantee @cpu stays online till @fn
 * completes.  If @cpu goes करोwn in the middle, execution may happen
 * partially or fully on dअगरferent cpus.  @fn should either be पढ़ोy
 * क्रम that or the caller should ensure that @cpu stays online until
 * this function completes.
 *
 * CONTEXT:
 * Might sleep.
 *
 * RETURNS:
 * -ENOENT अगर @fn(@arg) was not executed because @cpu was offline;
 * otherwise, the वापस value of @fn.
 */
पूर्णांक stop_one_cpu(अचिन्हित पूर्णांक cpu, cpu_stop_fn_t fn, व्योम *arg)
अणु
	काष्ठा cpu_stop_करोne करोne;
	काष्ठा cpu_stop_work work = अणु .fn = fn, .arg = arg, .करोne = &करोne, .caller = _RET_IP_ पूर्ण;

	cpu_stop_init_करोne(&करोne, 1);
	अगर (!cpu_stop_queue_work(cpu, &work))
		वापस -ENOENT;
	/*
	 * In हाल @cpu == smp_proccessor_id() we can aव्योम a sleep+wakeup
	 * cycle by करोing a preemption:
	 */
	cond_resched();
	रुको_क्रम_completion(&करोne.completion);
	वापस करोne.ret;
पूर्ण

/* This controls the thपढ़ोs on each CPU. */
क्रमागत multi_stop_state अणु
	/* Dummy starting state क्रम thपढ़ो. */
	MULTI_STOP_NONE,
	/* Aरुकोing everyone to be scheduled. */
	MULTI_STOP_PREPARE,
	/* Disable पूर्णांकerrupts. */
	MULTI_STOP_DISABLE_IRQ,
	/* Run the function */
	MULTI_STOP_RUN,
	/* Exit */
	MULTI_STOP_EXIT,
पूर्ण;

काष्ठा multi_stop_data अणु
	cpu_stop_fn_t		fn;
	व्योम			*data;
	/* Like num_online_cpus(), but hotplug cpu uses us, so we need this. */
	अचिन्हित पूर्णांक		num_thपढ़ोs;
	स्थिर काष्ठा cpumask	*active_cpus;

	क्रमागत multi_stop_state	state;
	atomic_t		thपढ़ो_ack;
पूर्ण;

अटल व्योम set_state(काष्ठा multi_stop_data *msdata,
		      क्रमागत multi_stop_state newstate)
अणु
	/* Reset ack counter. */
	atomic_set(&msdata->thपढ़ो_ack, msdata->num_thपढ़ोs);
	smp_wmb();
	WRITE_ONCE(msdata->state, newstate);
पूर्ण

/* Last one to ack a state moves to the next state. */
अटल व्योम ack_state(काष्ठा multi_stop_data *msdata)
अणु
	अगर (atomic_dec_and_test(&msdata->thपढ़ो_ack))
		set_state(msdata, msdata->state + 1);
पूर्ण

notrace व्योम __weak stop_machine_yield(स्थिर काष्ठा cpumask *cpumask)
अणु
	cpu_relax();
पूर्ण

/* This is the cpu_stop function which stops the CPU. */
अटल पूर्णांक multi_cpu_stop(व्योम *data)
अणु
	काष्ठा multi_stop_data *msdata = data;
	क्रमागत multi_stop_state newstate, curstate = MULTI_STOP_NONE;
	पूर्णांक cpu = smp_processor_id(), err = 0;
	स्थिर काष्ठा cpumask *cpumask;
	अचिन्हित दीर्घ flags;
	bool is_active;

	/*
	 * When called from stop_machine_from_inactive_cpu(), irq might
	 * alपढ़ोy be disabled.  Save the state and restore it on निकास.
	 */
	local_save_flags(flags);

	अगर (!msdata->active_cpus) अणु
		cpumask = cpu_online_mask;
		is_active = cpu == cpumask_first(cpumask);
	पूर्ण अन्यथा अणु
		cpumask = msdata->active_cpus;
		is_active = cpumask_test_cpu(cpu, cpumask);
	पूर्ण

	/* Simple state machine */
	करो अणु
		/* Chill out and ensure we re-पढ़ो multi_stop_state. */
		stop_machine_yield(cpumask);
		newstate = READ_ONCE(msdata->state);
		अगर (newstate != curstate) अणु
			curstate = newstate;
			चयन (curstate) अणु
			हाल MULTI_STOP_DISABLE_IRQ:
				local_irq_disable();
				hard_irq_disable();
				अवरोध;
			हाल MULTI_STOP_RUN:
				अगर (is_active)
					err = msdata->fn(msdata->data);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			ack_state(msdata);
		पूर्ण अन्यथा अगर (curstate > MULTI_STOP_PREPARE) अणु
			/*
			 * At this stage all other CPUs we depend on must spin
			 * in the same loop. Any reason क्रम hard-lockup should
			 * be detected and reported on their side.
			 */
			touch_nmi_watchकरोg();
		पूर्ण
		rcu_momentary_dyntick_idle();
	पूर्ण जबतक (curstate != MULTI_STOP_EXIT);

	local_irq_restore(flags);
	वापस err;
पूर्ण

अटल पूर्णांक cpu_stop_queue_two_works(पूर्णांक cpu1, काष्ठा cpu_stop_work *work1,
				    पूर्णांक cpu2, काष्ठा cpu_stop_work *work2)
अणु
	काष्ठा cpu_stopper *stopper1 = per_cpu_ptr(&cpu_stopper, cpu1);
	काष्ठा cpu_stopper *stopper2 = per_cpu_ptr(&cpu_stopper, cpu2);
	DEFINE_WAKE_Q(wakeq);
	पूर्णांक err;

retry:
	/*
	 * The waking up of stopper thपढ़ोs has to happen in the same
	 * scheduling context as the queueing.  Otherwise, there is a
	 * possibility of one of the above stoppers being woken up by another
	 * CPU, and preempting us. This will cause us to not wake up the other
	 * stopper क्रमever.
	 */
	preempt_disable();
	raw_spin_lock_irq(&stopper1->lock);
	raw_spin_lock_nested(&stopper2->lock, SINGLE_DEPTH_NESTING);

	अगर (!stopper1->enabled || !stopper2->enabled) अणु
		err = -ENOENT;
		जाओ unlock;
	पूर्ण

	/*
	 * Ensure that अगर we race with __stop_cpus() the stoppers won't get
	 * queued up in reverse order leading to प्रणाली deadlock.
	 *
	 * We can't miss stop_cpus_in_progress अगर queue_stop_cpus_work() has
	 * queued a work on cpu1 but not on cpu2, we hold both locks.
	 *
	 * It can be falsely true but it is safe to spin until it is cleared,
	 * queue_stop_cpus_work() करोes everything under preempt_disable().
	 */
	अगर (unlikely(stop_cpus_in_progress)) अणु
		err = -EDEADLK;
		जाओ unlock;
	पूर्ण

	err = 0;
	__cpu_stop_queue_work(stopper1, work1, &wakeq);
	__cpu_stop_queue_work(stopper2, work2, &wakeq);

unlock:
	raw_spin_unlock(&stopper2->lock);
	raw_spin_unlock_irq(&stopper1->lock);

	अगर (unlikely(err == -EDEADLK)) अणु
		preempt_enable();

		जबतक (stop_cpus_in_progress)
			cpu_relax();

		जाओ retry;
	पूर्ण

	wake_up_q(&wakeq);
	preempt_enable();

	वापस err;
पूर्ण
/**
 * stop_two_cpus - stops two cpus
 * @cpu1: the cpu to stop
 * @cpu2: the other cpu to stop
 * @fn: function to execute
 * @arg: argument to @fn
 *
 * Stops both the current and specअगरied CPU and runs @fn on one of them.
 *
 * वापसs when both are completed.
 */
पूर्णांक stop_two_cpus(अचिन्हित पूर्णांक cpu1, अचिन्हित पूर्णांक cpu2, cpu_stop_fn_t fn, व्योम *arg)
अणु
	काष्ठा cpu_stop_करोne करोne;
	काष्ठा cpu_stop_work work1, work2;
	काष्ठा multi_stop_data msdata;

	msdata = (काष्ठा multi_stop_data)अणु
		.fn = fn,
		.data = arg,
		.num_thपढ़ोs = 2,
		.active_cpus = cpumask_of(cpu1),
	पूर्ण;

	work1 = work2 = (काष्ठा cpu_stop_work)अणु
		.fn = multi_cpu_stop,
		.arg = &msdata,
		.करोne = &करोne,
		.caller = _RET_IP_,
	पूर्ण;

	cpu_stop_init_करोne(&करोne, 2);
	set_state(&msdata, MULTI_STOP_PREPARE);

	अगर (cpu1 > cpu2)
		swap(cpu1, cpu2);
	अगर (cpu_stop_queue_two_works(cpu1, &work1, cpu2, &work2))
		वापस -ENOENT;

	रुको_क्रम_completion(&करोne.completion);
	वापस करोne.ret;
पूर्ण

/**
 * stop_one_cpu_noरुको - stop a cpu but करोn't रुको क्रम completion
 * @cpu: cpu to stop
 * @fn: function to execute
 * @arg: argument to @fn
 * @work_buf: poपूर्णांकer to cpu_stop_work काष्ठाure
 *
 * Similar to stop_one_cpu() but करोesn't रुको क्रम completion.  The
 * caller is responsible क्रम ensuring @work_buf is currently unused
 * and will reमुख्य untouched until stopper starts executing @fn.
 *
 * CONTEXT:
 * Don't care.
 *
 * RETURNS:
 * true अगर cpu_stop_work was queued successfully and @fn will be called,
 * false otherwise.
 */
bool stop_one_cpu_noरुको(अचिन्हित पूर्णांक cpu, cpu_stop_fn_t fn, व्योम *arg,
			काष्ठा cpu_stop_work *work_buf)
अणु
	*work_buf = (काष्ठा cpu_stop_work)अणु .fn = fn, .arg = arg, .caller = _RET_IP_, पूर्ण;
	वापस cpu_stop_queue_work(cpu, work_buf);
पूर्ण

अटल bool queue_stop_cpus_work(स्थिर काष्ठा cpumask *cpumask,
				 cpu_stop_fn_t fn, व्योम *arg,
				 काष्ठा cpu_stop_करोne *करोne)
अणु
	काष्ठा cpu_stop_work *work;
	अचिन्हित पूर्णांक cpu;
	bool queued = false;

	/*
	 * Disable preemption जबतक queueing to aव्योम getting
	 * preempted by a stopper which might रुको क्रम other stoppers
	 * to enter @fn which can lead to deadlock.
	 */
	preempt_disable();
	stop_cpus_in_progress = true;
	barrier();
	क्रम_each_cpu(cpu, cpumask) अणु
		work = &per_cpu(cpu_stopper.stop_work, cpu);
		work->fn = fn;
		work->arg = arg;
		work->करोne = करोne;
		work->caller = _RET_IP_;
		अगर (cpu_stop_queue_work(cpu, work))
			queued = true;
	पूर्ण
	barrier();
	stop_cpus_in_progress = false;
	preempt_enable();

	वापस queued;
पूर्ण

अटल पूर्णांक __stop_cpus(स्थिर काष्ठा cpumask *cpumask,
		       cpu_stop_fn_t fn, व्योम *arg)
अणु
	काष्ठा cpu_stop_करोne करोne;

	cpu_stop_init_करोne(&करोne, cpumask_weight(cpumask));
	अगर (!queue_stop_cpus_work(cpumask, fn, arg, &करोne))
		वापस -ENOENT;
	रुको_क्रम_completion(&करोne.completion);
	वापस करोne.ret;
पूर्ण

/**
 * stop_cpus - stop multiple cpus
 * @cpumask: cpus to stop
 * @fn: function to execute
 * @arg: argument to @fn
 *
 * Execute @fn(@arg) on online cpus in @cpumask.  On each target cpu,
 * @fn is run in a process context with the highest priority
 * preempting any task on the cpu and monopolizing it.  This function
 * वापसs after all executions are complete.
 *
 * This function करोesn't guarantee the cpus in @cpumask stay online
 * till @fn completes.  If some cpus go करोwn in the middle, execution
 * on the cpu may happen partially or fully on dअगरferent cpus.  @fn
 * should either be पढ़ोy क्रम that or the caller should ensure that
 * the cpus stay online until this function completes.
 *
 * All stop_cpus() calls are serialized making it safe क्रम @fn to रुको
 * क्रम all cpus to start executing it.
 *
 * CONTEXT:
 * Might sleep.
 *
 * RETURNS:
 * -ENOENT अगर @fn(@arg) was not executed at all because all cpus in
 * @cpumask were offline; otherwise, 0 अगर all executions of @fn
 * वापसed 0, any non zero वापस value अगर any वापसed non zero.
 */
अटल पूर्णांक stop_cpus(स्थिर काष्ठा cpumask *cpumask, cpu_stop_fn_t fn, व्योम *arg)
अणु
	पूर्णांक ret;

	/* अटल works are used, process one request at a समय */
	mutex_lock(&stop_cpus_mutex);
	ret = __stop_cpus(cpumask, fn, arg);
	mutex_unlock(&stop_cpus_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक cpu_stop_should_run(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu_stopper *stopper = &per_cpu(cpu_stopper, cpu);
	अचिन्हित दीर्घ flags;
	पूर्णांक run;

	raw_spin_lock_irqsave(&stopper->lock, flags);
	run = !list_empty(&stopper->works);
	raw_spin_unlock_irqrestore(&stopper->lock, flags);
	वापस run;
पूर्ण

अटल व्योम cpu_stopper_thपढ़ो(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu_stopper *stopper = &per_cpu(cpu_stopper, cpu);
	काष्ठा cpu_stop_work *work;

repeat:
	work = शून्य;
	raw_spin_lock_irq(&stopper->lock);
	अगर (!list_empty(&stopper->works)) अणु
		work = list_first_entry(&stopper->works,
					काष्ठा cpu_stop_work, list);
		list_del_init(&work->list);
	पूर्ण
	raw_spin_unlock_irq(&stopper->lock);

	अगर (work) अणु
		cpu_stop_fn_t fn = work->fn;
		व्योम *arg = work->arg;
		काष्ठा cpu_stop_करोne *करोne = work->करोne;
		पूर्णांक ret;

		/* cpu stop callbacks must not sleep, make in_atomic() == T */
		stopper->caller = work->caller;
		stopper->fn = fn;
		preempt_count_inc();
		ret = fn(arg);
		अगर (करोne) अणु
			अगर (ret)
				करोne->ret = ret;
			cpu_stop_संकेत_करोne(करोne);
		पूर्ण
		preempt_count_dec();
		stopper->fn = शून्य;
		stopper->caller = 0;
		WARN_ONCE(preempt_count(),
			  "cpu_stop: %ps(%p) leaked preempt count\n", fn, arg);
		जाओ repeat;
	पूर्ण
पूर्ण

व्योम stop_machine_park(पूर्णांक cpu)
अणु
	काष्ठा cpu_stopper *stopper = &per_cpu(cpu_stopper, cpu);
	/*
	 * Lockless. cpu_stopper_thपढ़ो() will take stopper->lock and flush
	 * the pending works beक्रमe it parks, until then it is fine to queue
	 * the new works.
	 */
	stopper->enabled = false;
	kthपढ़ो_park(stopper->thपढ़ो);
पूर्ण

बाह्य व्योम sched_set_stop_task(पूर्णांक cpu, काष्ठा task_काष्ठा *stop);

अटल व्योम cpu_stop_create(अचिन्हित पूर्णांक cpu)
अणु
	sched_set_stop_task(cpu, per_cpu(cpu_stopper.thपढ़ो, cpu));
पूर्ण

अटल व्योम cpu_stop_park(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu_stopper *stopper = &per_cpu(cpu_stopper, cpu);

	WARN_ON(!list_empty(&stopper->works));
पूर्ण

व्योम stop_machine_unpark(पूर्णांक cpu)
अणु
	काष्ठा cpu_stopper *stopper = &per_cpu(cpu_stopper, cpu);

	stopper->enabled = true;
	kthपढ़ो_unpark(stopper->thपढ़ो);
पूर्ण

अटल काष्ठा smp_hotplug_thपढ़ो cpu_stop_thपढ़ोs = अणु
	.store			= &cpu_stopper.thपढ़ो,
	.thपढ़ो_should_run	= cpu_stop_should_run,
	.thपढ़ो_fn		= cpu_stopper_thपढ़ो,
	.thपढ़ो_comm		= "migration/%u",
	.create			= cpu_stop_create,
	.park			= cpu_stop_park,
	.selfparking		= true,
पूर्ण;

अटल पूर्णांक __init cpu_stop_init(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा cpu_stopper *stopper = &per_cpu(cpu_stopper, cpu);

		raw_spin_lock_init(&stopper->lock);
		INIT_LIST_HEAD(&stopper->works);
	पूर्ण

	BUG_ON(smpboot_रेजिस्टर_percpu_thपढ़ो(&cpu_stop_thपढ़ोs));
	stop_machine_unpark(raw_smp_processor_id());
	stop_machine_initialized = true;
	वापस 0;
पूर्ण
early_initcall(cpu_stop_init);

पूर्णांक stop_machine_cpuslocked(cpu_stop_fn_t fn, व्योम *data,
			    स्थिर काष्ठा cpumask *cpus)
अणु
	काष्ठा multi_stop_data msdata = अणु
		.fn = fn,
		.data = data,
		.num_thपढ़ोs = num_online_cpus(),
		.active_cpus = cpus,
	पूर्ण;

	lockdep_निश्चित_cpus_held();

	अगर (!stop_machine_initialized) अणु
		/*
		 * Handle the हाल where stop_machine() is called
		 * early in boot beक्रमe stop_machine() has been
		 * initialized.
		 */
		अचिन्हित दीर्घ flags;
		पूर्णांक ret;

		WARN_ON_ONCE(msdata.num_thपढ़ोs != 1);

		local_irq_save(flags);
		hard_irq_disable();
		ret = (*fn)(data);
		local_irq_restore(flags);

		वापस ret;
	पूर्ण

	/* Set the initial state and stop all online cpus. */
	set_state(&msdata, MULTI_STOP_PREPARE);
	वापस stop_cpus(cpu_online_mask, multi_cpu_stop, &msdata);
पूर्ण

पूर्णांक stop_machine(cpu_stop_fn_t fn, व्योम *data, स्थिर काष्ठा cpumask *cpus)
अणु
	पूर्णांक ret;

	/* No CPUs can come up or करोwn during this. */
	cpus_पढ़ो_lock();
	ret = stop_machine_cpuslocked(fn, data, cpus);
	cpus_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(stop_machine);

/**
 * stop_machine_from_inactive_cpu - stop_machine() from inactive CPU
 * @fn: the function to run
 * @data: the data ptr क्रम the @fn()
 * @cpus: the cpus to run the @fn() on (शून्य = any online cpu)
 *
 * This is identical to stop_machine() but can be called from a CPU which
 * is not active.  The local CPU is in the process of hotplug (so no other
 * CPU hotplug can start) and not marked active and करोesn't have enough
 * context to sleep.
 *
 * This function provides stop_machine() functionality क्रम such state by
 * using busy-रुको क्रम synchronization and executing @fn directly क्रम local
 * CPU.
 *
 * CONTEXT:
 * Local CPU is inactive.  Temporarily stops all active CPUs.
 *
 * RETURNS:
 * 0 अगर all executions of @fn वापसed 0, any non zero वापस value अगर any
 * वापसed non zero.
 */
पूर्णांक stop_machine_from_inactive_cpu(cpu_stop_fn_t fn, व्योम *data,
				  स्थिर काष्ठा cpumask *cpus)
अणु
	काष्ठा multi_stop_data msdata = अणु .fn = fn, .data = data,
					    .active_cpus = cpus पूर्ण;
	काष्ठा cpu_stop_करोne करोne;
	पूर्णांक ret;

	/* Local CPU must be inactive and CPU hotplug in progress. */
	BUG_ON(cpu_active(raw_smp_processor_id()));
	msdata.num_thपढ़ोs = num_active_cpus() + 1;	/* +1 क्रम local */

	/* No proper task established and can't sleep - busy रुको क्रम lock. */
	जबतक (!mutex_trylock(&stop_cpus_mutex))
		cpu_relax();

	/* Schedule work on other CPUs and execute directly क्रम local CPU */
	set_state(&msdata, MULTI_STOP_PREPARE);
	cpu_stop_init_करोne(&करोne, num_active_cpus());
	queue_stop_cpus_work(cpu_active_mask, multi_cpu_stop, &msdata,
			     &करोne);
	ret = multi_cpu_stop(&msdata);

	/* Busy रुको क्रम completion. */
	जबतक (!completion_करोne(&करोne.completion))
		cpu_relax();

	mutex_unlock(&stop_cpus_mutex);
	वापस ret ?: करोne.ret;
पूर्ण
