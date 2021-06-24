<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Perक्रमmance events core code:
 *
 *  Copyright (C) 2008 Thomas Gleixner <tglx@linutronix.de>
 *  Copyright (C) 2008-2011 Red Hat, Inc., Ingo Molnar
 *  Copyright (C) 2008-2011 Red Hat, Inc., Peter Zijlstra
 *  Copyright  तऊ  2009 Paul Mackerras, IBM Corp. <paulus@au1.ibm.com>
 */

#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/cpu.h>
#समावेश <linux/smp.h>
#समावेश <linux/idr.h>
#समावेश <linux/file.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/hash.h>
#समावेश <linux/tick.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/dcache.h>
#समावेश <linux/percpu.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/reboot.h>
#समावेश <linux/vmस्थिति.स>
#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/rculist.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/cgroup.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/trace_events.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/module.h>
#समावेश <linux/mman.h>
#समावेश <linux/compat.h>
#समावेश <linux/bpf.h>
#समावेश <linux/filter.h>
#समावेश <linux/namei.h>
#समावेश <linux/parser.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/proc_ns.h>
#समावेश <linux/mount.h>
#समावेश <linux/min_heap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pgtable.h>
#समावेश <linux/buildid.h>

#समावेश "internal.h"

#समावेश <यंत्र/irq_regs.h>

प्रकार पूर्णांक (*remote_function_f)(व्योम *);

काष्ठा remote_function_call अणु
	काष्ठा task_काष्ठा	*p;
	remote_function_f	func;
	व्योम			*info;
	पूर्णांक			ret;
पूर्ण;

अटल व्योम remote_function(व्योम *data)
अणु
	काष्ठा remote_function_call *tfc = data;
	काष्ठा task_काष्ठा *p = tfc->p;

	अगर (p) अणु
		/* -EAGAIN */
		अगर (task_cpu(p) != smp_processor_id())
			वापस;

		/*
		 * Now that we're on right CPU with IRQs disabled, we can test
		 * अगर we hit the right task without races.
		 */

		tfc->ret = -ESRCH; /* No such (running) process */
		अगर (p != current)
			वापस;
	पूर्ण

	tfc->ret = tfc->func(tfc->info);
पूर्ण

/**
 * task_function_call - call a function on the cpu on which a task runs
 * @p:		the task to evaluate
 * @func:	the function to be called
 * @info:	the function call argument
 *
 * Calls the function @func when the task is currently running. This might
 * be on the current CPU, which just calls the function directly.  This will
 * retry due to any failures in smp_call_function_single(), such as अगर the
 * task_cpu() goes offline concurrently.
 *
 * वापसs @func वापस value or -ESRCH or -ENXIO when the process isn't running
 */
अटल पूर्णांक
task_function_call(काष्ठा task_काष्ठा *p, remote_function_f func, व्योम *info)
अणु
	काष्ठा remote_function_call data = अणु
		.p	= p,
		.func	= func,
		.info	= info,
		.ret	= -EAGAIN,
	पूर्ण;
	पूर्णांक ret;

	क्रम (;;) अणु
		ret = smp_call_function_single(task_cpu(p), remote_function,
					       &data, 1);
		अगर (!ret)
			ret = data.ret;

		अगर (ret != -EAGAIN)
			अवरोध;

		cond_resched();
	पूर्ण

	वापस ret;
पूर्ण

/**
 * cpu_function_call - call a function on the cpu
 * @func:	the function to be called
 * @info:	the function call argument
 *
 * Calls the function @func on the remote cpu.
 *
 * वापसs: @func वापस value or -ENXIO when the cpu is offline
 */
अटल पूर्णांक cpu_function_call(पूर्णांक cpu, remote_function_f func, व्योम *info)
अणु
	काष्ठा remote_function_call data = अणु
		.p	= शून्य,
		.func	= func,
		.info	= info,
		.ret	= -ENXIO, /* No such CPU */
	पूर्ण;

	smp_call_function_single(cpu, remote_function, &data, 1);

	वापस data.ret;
पूर्ण

अटल अंतरभूत काष्ठा perf_cpu_context *
__get_cpu_context(काष्ठा perf_event_context *ctx)
अणु
	वापस this_cpu_ptr(ctx->pmu->pmu_cpu_context);
पूर्ण

अटल व्योम perf_ctx_lock(काष्ठा perf_cpu_context *cpuctx,
			  काष्ठा perf_event_context *ctx)
अणु
	raw_spin_lock(&cpuctx->ctx.lock);
	अगर (ctx)
		raw_spin_lock(&ctx->lock);
पूर्ण

अटल व्योम perf_ctx_unlock(काष्ठा perf_cpu_context *cpuctx,
			    काष्ठा perf_event_context *ctx)
अणु
	अगर (ctx)
		raw_spin_unlock(&ctx->lock);
	raw_spin_unlock(&cpuctx->ctx.lock);
पूर्ण

#घोषणा TASK_TOMBSTONE ((व्योम *)-1L)

अटल bool is_kernel_event(काष्ठा perf_event *event)
अणु
	वापस READ_ONCE(event->owner) == TASK_TOMBSTONE;
पूर्ण

/*
 * On task ctx scheduling...
 *
 * When !ctx->nr_events a task context will not be scheduled. This means
 * we can disable the scheduler hooks (क्रम perक्रमmance) without leaving
 * pending task ctx state.
 *
 * This however results in two special हालs:
 *
 *  - removing the last event from a task ctx; this is relatively straight
 *    क्रमward and is करोne in __perf_हटाओ_from_context.
 *
 *  - adding the first event to a task ctx; this is tricky because we cannot
 *    rely on ctx->is_active and thereक्रमe cannot use event_function_call().
 *    See perf_install_in_context().
 *
 * If ctx->nr_events, then ctx->is_active and cpuctx->task_ctx are set.
 */

प्रकार व्योम (*event_f)(काष्ठा perf_event *, काष्ठा perf_cpu_context *,
			काष्ठा perf_event_context *, व्योम *);

काष्ठा event_function_काष्ठा अणु
	काष्ठा perf_event *event;
	event_f func;
	व्योम *data;
पूर्ण;

अटल पूर्णांक event_function(व्योम *info)
अणु
	काष्ठा event_function_काष्ठा *efs = info;
	काष्ठा perf_event *event = efs->event;
	काष्ठा perf_event_context *ctx = event->ctx;
	काष्ठा perf_cpu_context *cpuctx = __get_cpu_context(ctx);
	काष्ठा perf_event_context *task_ctx = cpuctx->task_ctx;
	पूर्णांक ret = 0;

	lockdep_निश्चित_irqs_disabled();

	perf_ctx_lock(cpuctx, task_ctx);
	/*
	 * Since we करो the IPI call without holding ctx->lock things can have
	 * changed, द्विगुन check we hit the task we set out to hit.
	 */
	अगर (ctx->task) अणु
		अगर (ctx->task != current) अणु
			ret = -ESRCH;
			जाओ unlock;
		पूर्ण

		/*
		 * We only use event_function_call() on established contexts,
		 * and event_function() is only ever called when active (or
		 * rather, we'll have bailed in task_function_call() or the
		 * above ctx->task != current test), thereक्रमe we must have
		 * ctx->is_active here.
		 */
		WARN_ON_ONCE(!ctx->is_active);
		/*
		 * And since we have ctx->is_active, cpuctx->task_ctx must
		 * match.
		 */
		WARN_ON_ONCE(task_ctx != ctx);
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(&cpuctx->ctx != ctx);
	पूर्ण

	efs->func(event, cpuctx, ctx, efs->data);
unlock:
	perf_ctx_unlock(cpuctx, task_ctx);

	वापस ret;
पूर्ण

अटल व्योम event_function_call(काष्ठा perf_event *event, event_f func, व्योम *data)
अणु
	काष्ठा perf_event_context *ctx = event->ctx;
	काष्ठा task_काष्ठा *task = READ_ONCE(ctx->task); /* verअगरied in event_function */
	काष्ठा event_function_काष्ठा efs = अणु
		.event = event,
		.func = func,
		.data = data,
	पूर्ण;

	अगर (!event->parent) अणु
		/*
		 * If this is a !child event, we must hold ctx::mutex to
		 * stabilize the event->ctx relation. See
		 * perf_event_ctx_lock().
		 */
		lockdep_निश्चित_held(&ctx->mutex);
	पूर्ण

	अगर (!task) अणु
		cpu_function_call(event->cpu, event_function, &efs);
		वापस;
	पूर्ण

	अगर (task == TASK_TOMBSTONE)
		वापस;

again:
	अगर (!task_function_call(task, event_function, &efs))
		वापस;

	raw_spin_lock_irq(&ctx->lock);
	/*
	 * Reload the task poपूर्णांकer, it might have been changed by
	 * a concurrent perf_event_context_sched_out().
	 */
	task = ctx->task;
	अगर (task == TASK_TOMBSTONE) अणु
		raw_spin_unlock_irq(&ctx->lock);
		वापस;
	पूर्ण
	अगर (ctx->is_active) अणु
		raw_spin_unlock_irq(&ctx->lock);
		जाओ again;
	पूर्ण
	func(event, शून्य, ctx, data);
	raw_spin_unlock_irq(&ctx->lock);
पूर्ण

/*
 * Similar to event_function_call() + event_function(), but hard assumes IRQs
 * are alपढ़ोy disabled and we're on the right CPU.
 */
अटल व्योम event_function_local(काष्ठा perf_event *event, event_f func, व्योम *data)
अणु
	काष्ठा perf_event_context *ctx = event->ctx;
	काष्ठा perf_cpu_context *cpuctx = __get_cpu_context(ctx);
	काष्ठा task_काष्ठा *task = READ_ONCE(ctx->task);
	काष्ठा perf_event_context *task_ctx = शून्य;

	lockdep_निश्चित_irqs_disabled();

	अगर (task) अणु
		अगर (task == TASK_TOMBSTONE)
			वापस;

		task_ctx = ctx;
	पूर्ण

	perf_ctx_lock(cpuctx, task_ctx);

	task = ctx->task;
	अगर (task == TASK_TOMBSTONE)
		जाओ unlock;

	अगर (task) अणु
		/*
		 * We must be either inactive or active and the right task,
		 * otherwise we're screwed, since we cannot IPI to somewhere
		 * अन्यथा.
		 */
		अगर (ctx->is_active) अणु
			अगर (WARN_ON_ONCE(task != current))
				जाओ unlock;

			अगर (WARN_ON_ONCE(cpuctx->task_ctx != ctx))
				जाओ unlock;
		पूर्ण
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(&cpuctx->ctx != ctx);
	पूर्ण

	func(event, cpuctx, ctx, data);
unlock:
	perf_ctx_unlock(cpuctx, task_ctx);
पूर्ण

#घोषणा PERF_FLAG_ALL (PERF_FLAG_FD_NO_GROUP |\
		       PERF_FLAG_FD_OUTPUT  |\
		       PERF_FLAG_PID_CGROUP |\
		       PERF_FLAG_FD_CLOEXEC)

/*
 * branch priv levels that need permission checks
 */
#घोषणा PERF_SAMPLE_BRANCH_PERM_PLM \
	(PERF_SAMPLE_BRANCH_KERNEL |\
	 PERF_SAMPLE_BRANCH_HV)

क्रमागत event_type_t अणु
	EVENT_FLEXIBLE = 0x1,
	EVENT_PINNED = 0x2,
	EVENT_TIME = 0x4,
	/* see ctx_resched() क्रम details */
	EVENT_CPU = 0x8,
	EVENT_ALL = EVENT_FLEXIBLE | EVENT_PINNED,
पूर्ण;

/*
 * perf_sched_events : >0 events exist
 * perf_cgroup_events: >0 per-cpu cgroup events exist on this cpu
 */

अटल व्योम perf_sched_delayed(काष्ठा work_काष्ठा *work);
DEFINE_STATIC_KEY_FALSE(perf_sched_events);
अटल DECLARE_DELAYED_WORK(perf_sched_work, perf_sched_delayed);
अटल DEFINE_MUTEX(perf_sched_mutex);
अटल atomic_t perf_sched_count;

अटल DEFINE_PER_CPU(atomic_t, perf_cgroup_events);
अटल DEFINE_PER_CPU(पूर्णांक, perf_sched_cb_usages);
अटल DEFINE_PER_CPU(काष्ठा pmu_event_list, pmu_sb_events);

अटल atomic_t nr_mmap_events __पढ़ो_mostly;
अटल atomic_t nr_comm_events __पढ़ो_mostly;
अटल atomic_t nr_namespaces_events __पढ़ो_mostly;
अटल atomic_t nr_task_events __पढ़ो_mostly;
अटल atomic_t nr_freq_events __पढ़ो_mostly;
अटल atomic_t nr_चयन_events __पढ़ो_mostly;
अटल atomic_t nr_ksymbol_events __पढ़ो_mostly;
अटल atomic_t nr_bpf_events __पढ़ो_mostly;
अटल atomic_t nr_cgroup_events __पढ़ो_mostly;
अटल atomic_t nr_text_poke_events __पढ़ो_mostly;
अटल atomic_t nr_build_id_events __पढ़ो_mostly;

अटल LIST_HEAD(pmus);
अटल DEFINE_MUTEX(pmus_lock);
अटल काष्ठा srcu_काष्ठा pmus_srcu;
अटल cpumask_var_t perf_online_mask;
अटल काष्ठा kmem_cache *perf_event_cache;

/*
 * perf event paranoia level:
 *  -1 - not paranoid at all
 *   0 - disallow raw tracepoपूर्णांक access क्रम unpriv
 *   1 - disallow cpu events क्रम unpriv
 *   2 - disallow kernel profiling क्रम unpriv
 */
पूर्णांक sysctl_perf_event_paranoid __पढ़ो_mostly = 2;

/* Minimum क्रम 512 kiB + 1 user control page */
पूर्णांक sysctl_perf_event_mlock __पढ़ो_mostly = 512 + (PAGE_SIZE / 1024); /* 'free' kiB per user */

/*
 * max perf event sample rate
 */
#घोषणा DEFAULT_MAX_SAMPLE_RATE		100000
#घोषणा DEFAULT_SAMPLE_PERIOD_NS	(NSEC_PER_SEC / DEFAULT_MAX_SAMPLE_RATE)
#घोषणा DEFAULT_CPU_TIME_MAX_PERCENT	25

पूर्णांक sysctl_perf_event_sample_rate __पढ़ो_mostly	= DEFAULT_MAX_SAMPLE_RATE;

अटल पूर्णांक max_samples_per_tick __पढ़ो_mostly	= DIV_ROUND_UP(DEFAULT_MAX_SAMPLE_RATE, HZ);
अटल पूर्णांक perf_sample_period_ns __पढ़ो_mostly	= DEFAULT_SAMPLE_PERIOD_NS;

अटल पूर्णांक perf_sample_allowed_ns __पढ़ो_mostly =
	DEFAULT_SAMPLE_PERIOD_NS * DEFAULT_CPU_TIME_MAX_PERCENT / 100;

अटल व्योम update_perf_cpu_limits(व्योम)
अणु
	u64 पंचांगp = perf_sample_period_ns;

	पंचांगp *= sysctl_perf_cpu_समय_max_percent;
	पंचांगp = भाग_u64(पंचांगp, 100);
	अगर (!पंचांगp)
		पंचांगp = 1;

	WRITE_ONCE(perf_sample_allowed_ns, पंचांगp);
पूर्ण

अटल bool perf_rotate_context(काष्ठा perf_cpu_context *cpuctx);

पूर्णांक perf_proc_update_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret;
	पूर्णांक perf_cpu = sysctl_perf_cpu_समय_max_percent;
	/*
	 * If throttling is disabled करोn't allow the ग_लिखो:
	 */
	अगर (ग_लिखो && (perf_cpu == 100 || perf_cpu == 0))
		वापस -EINVAL;

	ret = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
	अगर (ret || !ग_लिखो)
		वापस ret;

	max_samples_per_tick = DIV_ROUND_UP(sysctl_perf_event_sample_rate, HZ);
	perf_sample_period_ns = NSEC_PER_SEC / sysctl_perf_event_sample_rate;
	update_perf_cpu_limits();

	वापस 0;
पूर्ण

पूर्णांक sysctl_perf_cpu_समय_max_percent __पढ़ो_mostly = DEFAULT_CPU_TIME_MAX_PERCENT;

पूर्णांक perf_cpu_समय_max_percent_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);

	अगर (ret || !ग_लिखो)
		वापस ret;

	अगर (sysctl_perf_cpu_समय_max_percent == 100 ||
	    sysctl_perf_cpu_समय_max_percent == 0) अणु
		prपूर्णांकk(KERN_WARNING
		       "perf: Dynamic interrupt throttling disabled, can hang your system!\n");
		WRITE_ONCE(perf_sample_allowed_ns, 0);
	पूर्ण अन्यथा अणु
		update_perf_cpu_limits();
	पूर्ण

	वापस 0;
पूर्ण

/*
 * perf samples are करोne in some very critical code paths (NMIs).
 * If they take too much CPU समय, the प्रणाली can lock up and not
 * get any real work करोne.  This will drop the sample rate when
 * we detect that events are taking too दीर्घ.
 */
#घोषणा NR_ACCUMULATED_SAMPLES 128
अटल DEFINE_PER_CPU(u64, running_sample_length);

अटल u64 __report_avg;
अटल u64 __report_allowed;

अटल व्योम perf_duration_warn(काष्ठा irq_work *w)
अणु
	prपूर्णांकk_ratelimited(KERN_INFO
		"perf: interrupt took too long (%lld > %lld), lowering "
		"kernel.perf_event_max_sample_rate to %d\n",
		__report_avg, __report_allowed,
		sysctl_perf_event_sample_rate);
पूर्ण

अटल DEFINE_IRQ_WORK(perf_duration_work, perf_duration_warn);

व्योम perf_sample_event_took(u64 sample_len_ns)
अणु
	u64 max_len = READ_ONCE(perf_sample_allowed_ns);
	u64 running_len;
	u64 avg_len;
	u32 max;

	अगर (max_len == 0)
		वापस;

	/* Decay the counter by 1 average sample. */
	running_len = __this_cpu_पढ़ो(running_sample_length);
	running_len -= running_len/NR_ACCUMULATED_SAMPLES;
	running_len += sample_len_ns;
	__this_cpu_ग_लिखो(running_sample_length, running_len);

	/*
	 * Note: this will be biased artअगरically low until we have
	 * seen NR_ACCUMULATED_SAMPLES. Doing it this way keeps us
	 * from having to मुख्यtain a count.
	 */
	avg_len = running_len/NR_ACCUMULATED_SAMPLES;
	अगर (avg_len <= max_len)
		वापस;

	__report_avg = avg_len;
	__report_allowed = max_len;

	/*
	 * Compute a throttle threshold 25% below the current duration.
	 */
	avg_len += avg_len / 4;
	max = (TICK_NSEC / 100) * sysctl_perf_cpu_समय_max_percent;
	अगर (avg_len < max)
		max /= (u32)avg_len;
	अन्यथा
		max = 1;

	WRITE_ONCE(perf_sample_allowed_ns, avg_len);
	WRITE_ONCE(max_samples_per_tick, max);

	sysctl_perf_event_sample_rate = max * HZ;
	perf_sample_period_ns = NSEC_PER_SEC / sysctl_perf_event_sample_rate;

	अगर (!irq_work_queue(&perf_duration_work)) अणु
		early_prपूर्णांकk("perf: interrupt took too long (%lld > %lld), lowering "
			     "kernel.perf_event_max_sample_rate to %d\n",
			     __report_avg, __report_allowed,
			     sysctl_perf_event_sample_rate);
	पूर्ण
पूर्ण

अटल atomic64_t perf_event_id;

अटल व्योम cpu_ctx_sched_out(काष्ठा perf_cpu_context *cpuctx,
			      क्रमागत event_type_t event_type);

अटल व्योम cpu_ctx_sched_in(काष्ठा perf_cpu_context *cpuctx,
			     क्रमागत event_type_t event_type,
			     काष्ठा task_काष्ठा *task);

अटल व्योम update_context_समय(काष्ठा perf_event_context *ctx);
अटल u64 perf_event_समय(काष्ठा perf_event *event);

व्योम __weak perf_event_prपूर्णांक_debug(व्योम)	अणु पूर्ण

अटल अंतरभूत u64 perf_घड़ी(व्योम)
अणु
	वापस local_घड़ी();
पूर्ण

अटल अंतरभूत u64 perf_event_घड़ी(काष्ठा perf_event *event)
अणु
	वापस event->घड़ी();
पूर्ण

/*
 * State based event समयkeeping...
 *
 * The basic idea is to use event->state to determine which (अगर any) समय
 * fields to increment with the current delta. This means we only need to
 * update बारtamps when we change state or when they are explicitly requested
 * (पढ़ो).
 *
 * Event groups make things a little more complicated, but not terribly so. The
 * rules क्रम a group are that अगर the group leader is OFF the entire group is
 * OFF, irrespecive of what the group member states are. This results in
 * __perf_effective_state().
 *
 * A futher ramअगरication is that when a group leader flips between OFF and
 * !OFF, we need to update all group member बार.
 *
 *
 * NOTE: perf_event_समय() is based on the (cgroup) context समय, and thus we
 * need to make sure the relevant context समय is updated beक्रमe we try and
 * update our बारtamps.
 */

अटल __always_अंतरभूत क्रमागत perf_event_state
__perf_effective_state(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event *leader = event->group_leader;

	अगर (leader->state <= PERF_EVENT_STATE_OFF)
		वापस leader->state;

	वापस event->state;
पूर्ण

अटल __always_अंतरभूत व्योम
__perf_update_बार(काष्ठा perf_event *event, u64 now, u64 *enabled, u64 *running)
अणु
	क्रमागत perf_event_state state = __perf_effective_state(event);
	u64 delta = now - event->tstamp;

	*enabled = event->total_समय_enabled;
	अगर (state >= PERF_EVENT_STATE_INACTIVE)
		*enabled += delta;

	*running = event->total_समय_running;
	अगर (state >= PERF_EVENT_STATE_ACTIVE)
		*running += delta;
पूर्ण

अटल व्योम perf_event_update_समय(काष्ठा perf_event *event)
अणु
	u64 now = perf_event_समय(event);

	__perf_update_बार(event, now, &event->total_समय_enabled,
					&event->total_समय_running);
	event->tstamp = now;
पूर्ण

अटल व्योम perf_event_update_sibling_समय(काष्ठा perf_event *leader)
अणु
	काष्ठा perf_event *sibling;

	क्रम_each_sibling_event(sibling, leader)
		perf_event_update_समय(sibling);
पूर्ण

अटल व्योम
perf_event_set_state(काष्ठा perf_event *event, क्रमागत perf_event_state state)
अणु
	अगर (event->state == state)
		वापस;

	perf_event_update_समय(event);
	/*
	 * If a group leader माला_लो enabled/disabled all its siblings
	 * are affected too.
	 */
	अगर ((event->state < 0) ^ (state < 0))
		perf_event_update_sibling_समय(event);

	WRITE_ONCE(event->state, state);
पूर्ण

#अगर_घोषित CONFIG_CGROUP_PERF

अटल अंतरभूत bool
perf_cgroup_match(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_context *ctx = event->ctx;
	काष्ठा perf_cpu_context *cpuctx = __get_cpu_context(ctx);

	/* @event करोesn't care about cgroup */
	अगर (!event->cgrp)
		वापस true;

	/* wants specअगरic cgroup scope but @cpuctx isn't associated with any */
	अगर (!cpuctx->cgrp)
		वापस false;

	/*
	 * Cgroup scoping is recursive.  An event enabled क्रम a cgroup is
	 * also enabled क्रम all its descendant cgroups.  If @cpuctx's
	 * cgroup is a descendant of @event's (the test covers identity
	 * हाल), it's a match.
	 */
	वापस cgroup_is_descendant(cpuctx->cgrp->css.cgroup,
				    event->cgrp->css.cgroup);
पूर्ण

अटल अंतरभूत व्योम perf_detach_cgroup(काष्ठा perf_event *event)
अणु
	css_put(&event->cgrp->css);
	event->cgrp = शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक is_cgroup_event(काष्ठा perf_event *event)
अणु
	वापस event->cgrp != शून्य;
पूर्ण

अटल अंतरभूत u64 perf_cgroup_event_समय(काष्ठा perf_event *event)
अणु
	काष्ठा perf_cgroup_info *t;

	t = per_cpu_ptr(event->cgrp->info, event->cpu);
	वापस t->समय;
पूर्ण

अटल अंतरभूत व्योम __update_cgrp_समय(काष्ठा perf_cgroup *cgrp)
अणु
	काष्ठा perf_cgroup_info *info;
	u64 now;

	now = perf_घड़ी();

	info = this_cpu_ptr(cgrp->info);

	info->समय += now - info->बारtamp;
	info->बारtamp = now;
पूर्ण

अटल अंतरभूत व्योम update_cgrp_समय_from_cpuctx(काष्ठा perf_cpu_context *cpuctx)
अणु
	काष्ठा perf_cgroup *cgrp = cpuctx->cgrp;
	काष्ठा cgroup_subsys_state *css;

	अगर (cgrp) अणु
		क्रम (css = &cgrp->css; css; css = css->parent) अणु
			cgrp = container_of(css, काष्ठा perf_cgroup, css);
			__update_cgrp_समय(cgrp);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम update_cgrp_समय_from_event(काष्ठा perf_event *event)
अणु
	काष्ठा perf_cgroup *cgrp;

	/*
	 * ensure we access cgroup data only when needed and
	 * when we know the cgroup is pinned (css_get)
	 */
	अगर (!is_cgroup_event(event))
		वापस;

	cgrp = perf_cgroup_from_task(current, event->ctx);
	/*
	 * Do not update समय when cgroup is not active
	 */
	अगर (cgroup_is_descendant(cgrp->css.cgroup, event->cgrp->css.cgroup))
		__update_cgrp_समय(event->cgrp);
पूर्ण

अटल अंतरभूत व्योम
perf_cgroup_set_बारtamp(काष्ठा task_काष्ठा *task,
			  काष्ठा perf_event_context *ctx)
अणु
	काष्ठा perf_cgroup *cgrp;
	काष्ठा perf_cgroup_info *info;
	काष्ठा cgroup_subsys_state *css;

	/*
	 * ctx->lock held by caller
	 * ensure we करो not access cgroup data
	 * unless we have the cgroup pinned (css_get)
	 */
	अगर (!task || !ctx->nr_cgroups)
		वापस;

	cgrp = perf_cgroup_from_task(task, ctx);

	क्रम (css = &cgrp->css; css; css = css->parent) अणु
		cgrp = container_of(css, काष्ठा perf_cgroup, css);
		info = this_cpu_ptr(cgrp->info);
		info->बारtamp = ctx->बारtamp;
	पूर्ण
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा list_head, cgrp_cpuctx_list);

#घोषणा PERF_CGROUP_SWOUT	0x1 /* cgroup चयन out every event */
#घोषणा PERF_CGROUP_SWIN	0x2 /* cgroup चयन in events based on task */

/*
 * reschedule events based on the cgroup स्थिरraपूर्णांक of task.
 *
 * mode SWOUT : schedule out everything
 * mode SWIN : schedule in based on cgroup क्रम next
 */
अटल व्योम perf_cgroup_चयन(काष्ठा task_काष्ठा *task, पूर्णांक mode)
अणु
	काष्ठा perf_cpu_context *cpuctx;
	काष्ठा list_head *list;
	अचिन्हित दीर्घ flags;

	/*
	 * Disable पूर्णांकerrupts and preemption to aव्योम this CPU's
	 * cgrp_cpuctx_entry to change under us.
	 */
	local_irq_save(flags);

	list = this_cpu_ptr(&cgrp_cpuctx_list);
	list_क्रम_each_entry(cpuctx, list, cgrp_cpuctx_entry) अणु
		WARN_ON_ONCE(cpuctx->ctx.nr_cgroups == 0);

		perf_ctx_lock(cpuctx, cpuctx->task_ctx);
		perf_pmu_disable(cpuctx->ctx.pmu);

		अगर (mode & PERF_CGROUP_SWOUT) अणु
			cpu_ctx_sched_out(cpuctx, EVENT_ALL);
			/*
			 * must not be करोne beक्रमe ctxswout due
			 * to event_filter_match() in event_sched_out()
			 */
			cpuctx->cgrp = शून्य;
		पूर्ण

		अगर (mode & PERF_CGROUP_SWIN) अणु
			WARN_ON_ONCE(cpuctx->cgrp);
			/*
			 * set cgrp beक्रमe ctxsw in to allow
			 * event_filter_match() to not have to pass
			 * task around
			 * we pass the cpuctx->ctx to perf_cgroup_from_task()
			 * because cgorup events are only per-cpu
			 */
			cpuctx->cgrp = perf_cgroup_from_task(task,
							     &cpuctx->ctx);
			cpu_ctx_sched_in(cpuctx, EVENT_ALL, task);
		पूर्ण
		perf_pmu_enable(cpuctx->ctx.pmu);
		perf_ctx_unlock(cpuctx, cpuctx->task_ctx);
	पूर्ण

	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत व्योम perf_cgroup_sched_out(काष्ठा task_काष्ठा *task,
					 काष्ठा task_काष्ठा *next)
अणु
	काष्ठा perf_cgroup *cgrp1;
	काष्ठा perf_cgroup *cgrp2 = शून्य;

	rcu_पढ़ो_lock();
	/*
	 * we come here when we know perf_cgroup_events > 0
	 * we करो not need to pass the ctx here because we know
	 * we are holding the rcu lock
	 */
	cgrp1 = perf_cgroup_from_task(task, शून्य);
	cgrp2 = perf_cgroup_from_task(next, शून्य);

	/*
	 * only schedule out current cgroup events अगर we know
	 * that we are चयनing to a dअगरferent cgroup. Otherwise,
	 * करो no touch the cgroup events.
	 */
	अगर (cgrp1 != cgrp2)
		perf_cgroup_चयन(task, PERF_CGROUP_SWOUT);

	rcu_पढ़ो_unlock();
पूर्ण

अटल अंतरभूत व्योम perf_cgroup_sched_in(काष्ठा task_काष्ठा *prev,
					काष्ठा task_काष्ठा *task)
अणु
	काष्ठा perf_cgroup *cgrp1;
	काष्ठा perf_cgroup *cgrp2 = शून्य;

	rcu_पढ़ो_lock();
	/*
	 * we come here when we know perf_cgroup_events > 0
	 * we करो not need to pass the ctx here because we know
	 * we are holding the rcu lock
	 */
	cgrp1 = perf_cgroup_from_task(task, शून्य);
	cgrp2 = perf_cgroup_from_task(prev, शून्य);

	/*
	 * only need to schedule in cgroup events अगर we are changing
	 * cgroup during ctxsw. Cgroup events were not scheduled
	 * out of ctxsw out अगर that was not the हाल.
	 */
	अगर (cgrp1 != cgrp2)
		perf_cgroup_चयन(task, PERF_CGROUP_SWIN);

	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक perf_cgroup_ensure_storage(काष्ठा perf_event *event,
				काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा perf_cpu_context *cpuctx;
	काष्ठा perf_event **storage;
	पूर्णांक cpu, heap_size, ret = 0;

	/*
	 * Allow storage to have sufficent space क्रम an iterator क्रम each
	 * possibly nested cgroup plus an iterator क्रम events with no cgroup.
	 */
	क्रम (heap_size = 1; css; css = css->parent)
		heap_size++;

	क्रम_each_possible_cpu(cpu) अणु
		cpuctx = per_cpu_ptr(event->pmu->pmu_cpu_context, cpu);
		अगर (heap_size <= cpuctx->heap_size)
			जारी;

		storage = kदो_स्मृति_node(heap_size * माप(काष्ठा perf_event *),
				       GFP_KERNEL, cpu_to_node(cpu));
		अगर (!storage) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		raw_spin_lock_irq(&cpuctx->ctx.lock);
		अगर (cpuctx->heap_size < heap_size) अणु
			swap(cpuctx->heap, storage);
			अगर (storage == cpuctx->heap_शेष)
				storage = शून्य;
			cpuctx->heap_size = heap_size;
		पूर्ण
		raw_spin_unlock_irq(&cpuctx->ctx.lock);

		kमुक्त(storage);
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक perf_cgroup_connect(पूर्णांक fd, काष्ठा perf_event *event,
				      काष्ठा perf_event_attr *attr,
				      काष्ठा perf_event *group_leader)
अणु
	काष्ठा perf_cgroup *cgrp;
	काष्ठा cgroup_subsys_state *css;
	काष्ठा fd f = fdget(fd);
	पूर्णांक ret = 0;

	अगर (!f.file)
		वापस -EBADF;

	css = css_tryget_online_from_dir(f.file->f_path.dentry,
					 &perf_event_cgrp_subsys);
	अगर (IS_ERR(css)) अणु
		ret = PTR_ERR(css);
		जाओ out;
	पूर्ण

	ret = perf_cgroup_ensure_storage(event, css);
	अगर (ret)
		जाओ out;

	cgrp = container_of(css, काष्ठा perf_cgroup, css);
	event->cgrp = cgrp;

	/*
	 * all events in a group must monitor
	 * the same cgroup because a task beदीर्घs
	 * to only one perf cgroup at a समय
	 */
	अगर (group_leader && group_leader->cgrp != cgrp) अणु
		perf_detach_cgroup(event);
		ret = -EINVAL;
	पूर्ण
out:
	fdput(f);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
perf_cgroup_set_shaकरोw_समय(काष्ठा perf_event *event, u64 now)
अणु
	काष्ठा perf_cgroup_info *t;
	t = per_cpu_ptr(event->cgrp->info, event->cpu);
	event->shaकरोw_ctx_समय = now - t->बारtamp;
पूर्ण

अटल अंतरभूत व्योम
perf_cgroup_event_enable(काष्ठा perf_event *event, काष्ठा perf_event_context *ctx)
अणु
	काष्ठा perf_cpu_context *cpuctx;

	अगर (!is_cgroup_event(event))
		वापस;

	/*
	 * Because cgroup events are always per-cpu events,
	 * @ctx == &cpuctx->ctx.
	 */
	cpuctx = container_of(ctx, काष्ठा perf_cpu_context, ctx);

	/*
	 * Since setting cpuctx->cgrp is conditional on the current @cgrp
	 * matching the event's cgroup, we must करो this क्रम every new event,
	 * because अगर the first would mismatch, the second would not try again
	 * and we would leave cpuctx->cgrp unset.
	 */
	अगर (ctx->is_active && !cpuctx->cgrp) अणु
		काष्ठा perf_cgroup *cgrp = perf_cgroup_from_task(current, ctx);

		अगर (cgroup_is_descendant(cgrp->css.cgroup, event->cgrp->css.cgroup))
			cpuctx->cgrp = cgrp;
	पूर्ण

	अगर (ctx->nr_cgroups++)
		वापस;

	list_add(&cpuctx->cgrp_cpuctx_entry,
			per_cpu_ptr(&cgrp_cpuctx_list, event->cpu));
पूर्ण

अटल अंतरभूत व्योम
perf_cgroup_event_disable(काष्ठा perf_event *event, काष्ठा perf_event_context *ctx)
अणु
	काष्ठा perf_cpu_context *cpuctx;

	अगर (!is_cgroup_event(event))
		वापस;

	/*
	 * Because cgroup events are always per-cpu events,
	 * @ctx == &cpuctx->ctx.
	 */
	cpuctx = container_of(ctx, काष्ठा perf_cpu_context, ctx);

	अगर (--ctx->nr_cgroups)
		वापस;

	अगर (ctx->is_active && cpuctx->cgrp)
		cpuctx->cgrp = शून्य;

	list_del(&cpuctx->cgrp_cpuctx_entry);
पूर्ण

#अन्यथा /* !CONFIG_CGROUP_PERF */

अटल अंतरभूत bool
perf_cgroup_match(काष्ठा perf_event *event)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत व्योम perf_detach_cgroup(काष्ठा perf_event *event)
अणुपूर्ण

अटल अंतरभूत पूर्णांक is_cgroup_event(काष्ठा perf_event *event)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम update_cgrp_समय_from_event(काष्ठा perf_event *event)
अणु
पूर्ण

अटल अंतरभूत व्योम update_cgrp_समय_from_cpuctx(काष्ठा perf_cpu_context *cpuctx)
अणु
पूर्ण

अटल अंतरभूत व्योम perf_cgroup_sched_out(काष्ठा task_काष्ठा *task,
					 काष्ठा task_काष्ठा *next)
अणु
पूर्ण

अटल अंतरभूत व्योम perf_cgroup_sched_in(काष्ठा task_काष्ठा *prev,
					काष्ठा task_काष्ठा *task)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक perf_cgroup_connect(pid_t pid, काष्ठा perf_event *event,
				      काष्ठा perf_event_attr *attr,
				      काष्ठा perf_event *group_leader)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम
perf_cgroup_set_बारtamp(काष्ठा task_काष्ठा *task,
			  काष्ठा perf_event_context *ctx)
अणु
पूर्ण

अटल अंतरभूत व्योम
perf_cgroup_चयन(काष्ठा task_काष्ठा *task, काष्ठा task_काष्ठा *next)
अणु
पूर्ण

अटल अंतरभूत व्योम
perf_cgroup_set_shaकरोw_समय(काष्ठा perf_event *event, u64 now)
अणु
पूर्ण

अटल अंतरभूत u64 perf_cgroup_event_समय(काष्ठा perf_event *event)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
perf_cgroup_event_enable(काष्ठा perf_event *event, काष्ठा perf_event_context *ctx)
अणु
पूर्ण

अटल अंतरभूत व्योम
perf_cgroup_event_disable(काष्ठा perf_event *event, काष्ठा perf_event_context *ctx)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * set शेष to be dependent on समयr tick just
 * like original code
 */
#घोषणा PERF_CPU_HRTIMER (1000 / HZ)
/*
 * function must be called with पूर्णांकerrupts disabled
 */
अटल क्रमागत hrसमयr_restart perf_mux_hrसमयr_handler(काष्ठा hrसमयr *hr)
अणु
	काष्ठा perf_cpu_context *cpuctx;
	bool rotations;

	lockdep_निश्चित_irqs_disabled();

	cpuctx = container_of(hr, काष्ठा perf_cpu_context, hrसमयr);
	rotations = perf_rotate_context(cpuctx);

	raw_spin_lock(&cpuctx->hrसमयr_lock);
	अगर (rotations)
		hrसमयr_क्रमward_now(hr, cpuctx->hrसमयr_पूर्णांकerval);
	अन्यथा
		cpuctx->hrसमयr_active = 0;
	raw_spin_unlock(&cpuctx->hrसमयr_lock);

	वापस rotations ? HRTIMER_RESTART : HRTIMER_NORESTART;
पूर्ण

अटल व्योम __perf_mux_hrसमयr_init(काष्ठा perf_cpu_context *cpuctx, पूर्णांक cpu)
अणु
	काष्ठा hrसमयr *समयr = &cpuctx->hrसमयr;
	काष्ठा pmu *pmu = cpuctx->ctx.pmu;
	u64 पूर्णांकerval;

	/* no multiplexing needed क्रम SW PMU */
	अगर (pmu->task_ctx_nr == perf_sw_context)
		वापस;

	/*
	 * check शेष is sane, अगर not set then क्रमce to
	 * शेष पूर्णांकerval (1/tick)
	 */
	पूर्णांकerval = pmu->hrसमयr_पूर्णांकerval_ms;
	अगर (पूर्णांकerval < 1)
		पूर्णांकerval = pmu->hrसमयr_पूर्णांकerval_ms = PERF_CPU_HRTIMER;

	cpuctx->hrसमयr_पूर्णांकerval = ns_to_kसमय(NSEC_PER_MSEC * पूर्णांकerval);

	raw_spin_lock_init(&cpuctx->hrसमयr_lock);
	hrसमयr_init(समयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS_PINNED_HARD);
	समयr->function = perf_mux_hrसमयr_handler;
पूर्ण

अटल पूर्णांक perf_mux_hrसमयr_restart(काष्ठा perf_cpu_context *cpuctx)
अणु
	काष्ठा hrसमयr *समयr = &cpuctx->hrसमयr;
	काष्ठा pmu *pmu = cpuctx->ctx.pmu;
	अचिन्हित दीर्घ flags;

	/* not क्रम SW PMU */
	अगर (pmu->task_ctx_nr == perf_sw_context)
		वापस 0;

	raw_spin_lock_irqsave(&cpuctx->hrसमयr_lock, flags);
	अगर (!cpuctx->hrसमयr_active) अणु
		cpuctx->hrसमयr_active = 1;
		hrसमयr_क्रमward_now(समयr, cpuctx->hrसमयr_पूर्णांकerval);
		hrसमयr_start_expires(समयr, HRTIMER_MODE_ABS_PINNED_HARD);
	पूर्ण
	raw_spin_unlock_irqrestore(&cpuctx->hrसमयr_lock, flags);

	वापस 0;
पूर्ण

व्योम perf_pmu_disable(काष्ठा pmu *pmu)
अणु
	पूर्णांक *count = this_cpu_ptr(pmu->pmu_disable_count);
	अगर (!(*count)++)
		pmu->pmu_disable(pmu);
पूर्ण

व्योम perf_pmu_enable(काष्ठा pmu *pmu)
अणु
	पूर्णांक *count = this_cpu_ptr(pmu->pmu_disable_count);
	अगर (!--(*count))
		pmu->pmu_enable(pmu);
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा list_head, active_ctx_list);

/*
 * perf_event_ctx_activate(), perf_event_ctx_deactivate(), and
 * perf_event_task_tick() are fully serialized because they're strictly cpu
 * affine and perf_event_ctxअणुactivate,deactivateपूर्ण are called with IRQs
 * disabled, जबतक perf_event_task_tick is called from IRQ context.
 */
अटल व्योम perf_event_ctx_activate(काष्ठा perf_event_context *ctx)
अणु
	काष्ठा list_head *head = this_cpu_ptr(&active_ctx_list);

	lockdep_निश्चित_irqs_disabled();

	WARN_ON(!list_empty(&ctx->active_ctx_list));

	list_add(&ctx->active_ctx_list, head);
पूर्ण

अटल व्योम perf_event_ctx_deactivate(काष्ठा perf_event_context *ctx)
अणु
	lockdep_निश्चित_irqs_disabled();

	WARN_ON(list_empty(&ctx->active_ctx_list));

	list_del_init(&ctx->active_ctx_list);
पूर्ण

अटल व्योम get_ctx(काष्ठा perf_event_context *ctx)
अणु
	refcount_inc(&ctx->refcount);
पूर्ण

अटल व्योम *alloc_task_ctx_data(काष्ठा pmu *pmu)
अणु
	अगर (pmu->task_ctx_cache)
		वापस kmem_cache_zalloc(pmu->task_ctx_cache, GFP_KERNEL);

	वापस शून्य;
पूर्ण

अटल व्योम मुक्त_task_ctx_data(काष्ठा pmu *pmu, व्योम *task_ctx_data)
अणु
	अगर (pmu->task_ctx_cache && task_ctx_data)
		kmem_cache_मुक्त(pmu->task_ctx_cache, task_ctx_data);
पूर्ण

अटल व्योम मुक्त_ctx(काष्ठा rcu_head *head)
अणु
	काष्ठा perf_event_context *ctx;

	ctx = container_of(head, काष्ठा perf_event_context, rcu_head);
	मुक्त_task_ctx_data(ctx->pmu, ctx->task_ctx_data);
	kमुक्त(ctx);
पूर्ण

अटल व्योम put_ctx(काष्ठा perf_event_context *ctx)
अणु
	अगर (refcount_dec_and_test(&ctx->refcount)) अणु
		अगर (ctx->parent_ctx)
			put_ctx(ctx->parent_ctx);
		अगर (ctx->task && ctx->task != TASK_TOMBSTONE)
			put_task_काष्ठा(ctx->task);
		call_rcu(&ctx->rcu_head, मुक्त_ctx);
	पूर्ण
पूर्ण

/*
 * Because of perf_event::ctx migration in sys_perf_event_खोलो::move_group and
 * perf_pmu_migrate_context() we need some magic.
 *
 * Those places that change perf_event::ctx will hold both
 * perf_event_ctx::mutex of the 'old' and 'new' ctx value.
 *
 * Lock ordering is by mutex address. There are two other sites where
 * perf_event_context::mutex nests and those are:
 *
 *  - perf_event_निकास_task_context()	[ child , 0 ]
 *      perf_event_निकास_event()
 *        put_event()			[ parent, 1 ]
 *
 *  - perf_event_init_context()		[ parent, 0 ]
 *      inherit_task_group()
 *        inherit_group()
 *          inherit_event()
 *            perf_event_alloc()
 *              perf_init_event()
 *                perf_try_init_event()	[ child , 1 ]
 *
 * While it appears there is an obvious deadlock here -- the parent and child
 * nesting levels are inverted between the two. This is in fact safe because
 * lअगरe-समय rules separate them. That is an निकासing task cannot विभाजन, and a
 * spawning task cannot (yet) निकास.
 *
 * But remember that these are parent<->child context relations, and
 * migration करोes not affect children, thereक्रमe these two orderings should not
 * पूर्णांकeract.
 *
 * The change in perf_event::ctx करोes not affect children (as claimed above)
 * because the sys_perf_event_खोलो() हाल will install a new event and अवरोध
 * the ctx parent<->child relation, and perf_pmu_migrate_context() is only
 * concerned with cpuctx and that करोesn't have children.
 *
 * The places that change perf_event::ctx will issue:
 *
 *   perf_हटाओ_from_context();
 *   synchronize_rcu();
 *   perf_install_in_context();
 *
 * to affect the change. The हटाओ_from_context() + synchronize_rcu() should
 * quiesce the event, after which we can install it in the new location. This
 * means that only बाह्यal vectors (perf_fops, prctl) can perturb the event
 * जबतक in transit. Thereक्रमe all such accessors should also acquire
 * perf_event_context::mutex to serialize against this.
 *
 * However; because event->ctx can change जबतक we're रुकोing to acquire
 * ctx->mutex we must be careful and use the below perf_event_ctx_lock()
 * function.
 *
 * Lock order:
 *    exec_update_lock
 *	task_काष्ठा::perf_event_mutex
 *	  perf_event_context::mutex
 *	    perf_event::child_mutex;
 *	      perf_event_context::lock
 *	    perf_event::mmap_mutex
 *	    mmap_lock
 *	      perf_addr_filters_head::lock
 *
 *    cpu_hotplug_lock
 *      pmus_lock
 *	  cpuctx->mutex / perf_event_context::mutex
 */
अटल काष्ठा perf_event_context *
perf_event_ctx_lock_nested(काष्ठा perf_event *event, पूर्णांक nesting)
अणु
	काष्ठा perf_event_context *ctx;

again:
	rcu_पढ़ो_lock();
	ctx = READ_ONCE(event->ctx);
	अगर (!refcount_inc_not_zero(&ctx->refcount)) अणु
		rcu_पढ़ो_unlock();
		जाओ again;
	पूर्ण
	rcu_पढ़ो_unlock();

	mutex_lock_nested(&ctx->mutex, nesting);
	अगर (event->ctx != ctx) अणु
		mutex_unlock(&ctx->mutex);
		put_ctx(ctx);
		जाओ again;
	पूर्ण

	वापस ctx;
पूर्ण

अटल अंतरभूत काष्ठा perf_event_context *
perf_event_ctx_lock(काष्ठा perf_event *event)
अणु
	वापस perf_event_ctx_lock_nested(event, 0);
पूर्ण

अटल व्योम perf_event_ctx_unlock(काष्ठा perf_event *event,
				  काष्ठा perf_event_context *ctx)
अणु
	mutex_unlock(&ctx->mutex);
	put_ctx(ctx);
पूर्ण

/*
 * This must be करोne under the ctx->lock, such as to serialize against
 * context_equiv(), thereक्रमe we cannot call put_ctx() since that might end up
 * calling scheduler related locks and ctx->lock nests inside those.
 */
अटल __must_check काष्ठा perf_event_context *
unclone_ctx(काष्ठा perf_event_context *ctx)
अणु
	काष्ठा perf_event_context *parent_ctx = ctx->parent_ctx;

	lockdep_निश्चित_held(&ctx->lock);

	अगर (parent_ctx)
		ctx->parent_ctx = शून्य;
	ctx->generation++;

	वापस parent_ctx;
पूर्ण

अटल u32 perf_event_pid_type(काष्ठा perf_event *event, काष्ठा task_काष्ठा *p,
				क्रमागत pid_type type)
अणु
	u32 nr;
	/*
	 * only top level events have the pid namespace they were created in
	 */
	अगर (event->parent)
		event = event->parent;

	nr = __task_pid_nr_ns(p, type, event->ns);
	/* aव्योम -1 अगर it is idle thपढ़ो or runs in another ns */
	अगर (!nr && !pid_alive(p))
		nr = -1;
	वापस nr;
पूर्ण

अटल u32 perf_event_pid(काष्ठा perf_event *event, काष्ठा task_काष्ठा *p)
अणु
	वापस perf_event_pid_type(event, p, PIDTYPE_TGID);
पूर्ण

अटल u32 perf_event_tid(काष्ठा perf_event *event, काष्ठा task_काष्ठा *p)
अणु
	वापस perf_event_pid_type(event, p, PIDTYPE_PID);
पूर्ण

/*
 * If we inherit events we want to वापस the parent event id
 * to userspace.
 */
अटल u64 primary_event_id(काष्ठा perf_event *event)
अणु
	u64 id = event->id;

	अगर (event->parent)
		id = event->parent->id;

	वापस id;
पूर्ण

/*
 * Get the perf_event_context क्रम a task and lock it.
 *
 * This has to cope with the fact that until it is locked,
 * the context could get moved to another task.
 */
अटल काष्ठा perf_event_context *
perf_lock_task_context(काष्ठा task_काष्ठा *task, पूर्णांक ctxn, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा perf_event_context *ctx;

retry:
	/*
	 * One of the few rules of preemptible RCU is that one cannot करो
	 * rcu_पढ़ो_unlock() जबतक holding a scheduler (or nested) lock when
	 * part of the पढ़ो side critical section was irqs-enabled -- see
	 * rcu_पढ़ो_unlock_special().
	 *
	 * Since ctx->lock nests under rq->lock we must ensure the entire पढ़ो
	 * side critical section has पूर्णांकerrupts disabled.
	 */
	local_irq_save(*flags);
	rcu_पढ़ो_lock();
	ctx = rcu_dereference(task->perf_event_ctxp[ctxn]);
	अगर (ctx) अणु
		/*
		 * If this context is a clone of another, it might
		 * get swapped क्रम another underneath us by
		 * perf_event_task_sched_out, though the
		 * rcu_पढ़ो_lock() protects us from any context
		 * getting मुक्तd.  Lock the context and check अगर it
		 * got swapped beक्रमe we could get the lock, and retry
		 * अगर so.  If we locked the right context, then it
		 * can't get swapped on us any more.
		 */
		raw_spin_lock(&ctx->lock);
		अगर (ctx != rcu_dereference(task->perf_event_ctxp[ctxn])) अणु
			raw_spin_unlock(&ctx->lock);
			rcu_पढ़ो_unlock();
			local_irq_restore(*flags);
			जाओ retry;
		पूर्ण

		अगर (ctx->task == TASK_TOMBSTONE ||
		    !refcount_inc_not_zero(&ctx->refcount)) अणु
			raw_spin_unlock(&ctx->lock);
			ctx = शून्य;
		पूर्ण अन्यथा अणु
			WARN_ON_ONCE(ctx->task != task);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (!ctx)
		local_irq_restore(*flags);
	वापस ctx;
पूर्ण

/*
 * Get the context क्रम a task and increment its pin_count so it
 * can't get swapped to another task.  This also increments its
 * reference count so that the context can't get मुक्तd.
 */
अटल काष्ठा perf_event_context *
perf_pin_task_context(काष्ठा task_काष्ठा *task, पूर्णांक ctxn)
अणु
	काष्ठा perf_event_context *ctx;
	अचिन्हित दीर्घ flags;

	ctx = perf_lock_task_context(task, ctxn, &flags);
	अगर (ctx) अणु
		++ctx->pin_count;
		raw_spin_unlock_irqrestore(&ctx->lock, flags);
	पूर्ण
	वापस ctx;
पूर्ण

अटल व्योम perf_unpin_context(काष्ठा perf_event_context *ctx)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&ctx->lock, flags);
	--ctx->pin_count;
	raw_spin_unlock_irqrestore(&ctx->lock, flags);
पूर्ण

/*
 * Update the record of the current समय in a context.
 */
अटल व्योम update_context_समय(काष्ठा perf_event_context *ctx)
अणु
	u64 now = perf_घड़ी();

	ctx->समय += now - ctx->बारtamp;
	ctx->बारtamp = now;
पूर्ण

अटल u64 perf_event_समय(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_context *ctx = event->ctx;

	अगर (is_cgroup_event(event))
		वापस perf_cgroup_event_समय(event);

	वापस ctx ? ctx->समय : 0;
पूर्ण

अटल क्रमागत event_type_t get_event_type(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_context *ctx = event->ctx;
	क्रमागत event_type_t event_type;

	lockdep_निश्चित_held(&ctx->lock);

	/*
	 * It's 'group type', really, because अगर our group leader is
	 * pinned, so are we.
	 */
	अगर (event->group_leader != event)
		event = event->group_leader;

	event_type = event->attr.pinned ? EVENT_PINNED : EVENT_FLEXIBLE;
	अगर (!ctx->task)
		event_type |= EVENT_CPU;

	वापस event_type;
पूर्ण

/*
 * Helper function to initialize event group nodes.
 */
अटल व्योम init_event_group(काष्ठा perf_event *event)
अणु
	RB_CLEAR_NODE(&event->group_node);
	event->group_index = 0;
पूर्ण

/*
 * Extract pinned or flexible groups from the context
 * based on event attrs bits.
 */
अटल काष्ठा perf_event_groups *
get_event_groups(काष्ठा perf_event *event, काष्ठा perf_event_context *ctx)
अणु
	अगर (event->attr.pinned)
		वापस &ctx->pinned_groups;
	अन्यथा
		वापस &ctx->flexible_groups;
पूर्ण

/*
 * Helper function to initializes perf_event_group trees.
 */
अटल व्योम perf_event_groups_init(काष्ठा perf_event_groups *groups)
अणु
	groups->tree = RB_ROOT;
	groups->index = 0;
पूर्ण

अटल अंतरभूत काष्ठा cgroup *event_cgroup(स्थिर काष्ठा perf_event *event)
अणु
	काष्ठा cgroup *cgroup = शून्य;

#अगर_घोषित CONFIG_CGROUP_PERF
	अगर (event->cgrp)
		cgroup = event->cgrp->css.cgroup;
#पूर्ण_अगर

	वापस cgroup;
पूर्ण

/*
 * Compare function क्रम event groups;
 *
 * Implements complex key that first sorts by CPU and then by भव index
 * which provides ordering when rotating groups क्रम the same CPU.
 */
अटल __always_अंतरभूत पूर्णांक
perf_event_groups_cmp(स्थिर पूर्णांक left_cpu, स्थिर काष्ठा cgroup *left_cgroup,
		      स्थिर u64 left_group_index, स्थिर काष्ठा perf_event *right)
अणु
	अगर (left_cpu < right->cpu)
		वापस -1;
	अगर (left_cpu > right->cpu)
		वापस 1;

#अगर_घोषित CONFIG_CGROUP_PERF
	अणु
		स्थिर काष्ठा cgroup *right_cgroup = event_cgroup(right);

		अगर (left_cgroup != right_cgroup) अणु
			अगर (!left_cgroup) अणु
				/*
				 * Left has no cgroup but right करोes, no
				 * cgroups come first.
				 */
				वापस -1;
			पूर्ण
			अगर (!right_cgroup) अणु
				/*
				 * Right has no cgroup but left करोes, no
				 * cgroups come first.
				 */
				वापस 1;
			पूर्ण
			/* Two dissimilar cgroups, order by id. */
			अगर (cgroup_id(left_cgroup) < cgroup_id(right_cgroup))
				वापस -1;

			वापस 1;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (left_group_index < right->group_index)
		वापस -1;
	अगर (left_group_index > right->group_index)
		वापस 1;

	वापस 0;
पूर्ण

#घोषणा __node_2_pe(node) \
	rb_entry((node), काष्ठा perf_event, group_node)

अटल अंतरभूत bool __group_less(काष्ठा rb_node *a, स्थिर काष्ठा rb_node *b)
अणु
	काष्ठा perf_event *e = __node_2_pe(a);
	वापस perf_event_groups_cmp(e->cpu, event_cgroup(e), e->group_index,
				     __node_2_pe(b)) < 0;
पूर्ण

काष्ठा __group_key अणु
	पूर्णांक cpu;
	काष्ठा cgroup *cgroup;
पूर्ण;

अटल अंतरभूत पूर्णांक __group_cmp(स्थिर व्योम *key, स्थिर काष्ठा rb_node *node)
अणु
	स्थिर काष्ठा __group_key *a = key;
	स्थिर काष्ठा perf_event *b = __node_2_pe(node);

	/* partial/subtree match: @cpu, @cgroup; ignore: @group_index */
	वापस perf_event_groups_cmp(a->cpu, a->cgroup, b->group_index, b);
पूर्ण

/*
 * Insert @event पूर्णांकo @groups' tree; using अणु@event->cpu, ++@groups->indexपूर्ण क्रम
 * key (see perf_event_groups_less). This places it last inside the CPU
 * subtree.
 */
अटल व्योम
perf_event_groups_insert(काष्ठा perf_event_groups *groups,
			 काष्ठा perf_event *event)
अणु
	event->group_index = ++groups->index;

	rb_add(&event->group_node, &groups->tree, __group_less);
पूर्ण

/*
 * Helper function to insert event पूर्णांकo the pinned or flexible groups.
 */
अटल व्योम
add_event_to_groups(काष्ठा perf_event *event, काष्ठा perf_event_context *ctx)
अणु
	काष्ठा perf_event_groups *groups;

	groups = get_event_groups(event, ctx);
	perf_event_groups_insert(groups, event);
पूर्ण

/*
 * Delete a group from a tree.
 */
अटल व्योम
perf_event_groups_delete(काष्ठा perf_event_groups *groups,
			 काष्ठा perf_event *event)
अणु
	WARN_ON_ONCE(RB_EMPTY_NODE(&event->group_node) ||
		     RB_EMPTY_ROOT(&groups->tree));

	rb_erase(&event->group_node, &groups->tree);
	init_event_group(event);
पूर्ण

/*
 * Helper function to delete event from its groups.
 */
अटल व्योम
del_event_from_groups(काष्ठा perf_event *event, काष्ठा perf_event_context *ctx)
अणु
	काष्ठा perf_event_groups *groups;

	groups = get_event_groups(event, ctx);
	perf_event_groups_delete(groups, event);
पूर्ण

/*
 * Get the lefपंचांगost event in the cpu/cgroup subtree.
 */
अटल काष्ठा perf_event *
perf_event_groups_first(काष्ठा perf_event_groups *groups, पूर्णांक cpu,
			काष्ठा cgroup *cgrp)
अणु
	काष्ठा __group_key key = अणु
		.cpu = cpu,
		.cgroup = cgrp,
	पूर्ण;
	काष्ठा rb_node *node;

	node = rb_find_first(&key, &groups->tree, __group_cmp);
	अगर (node)
		वापस __node_2_pe(node);

	वापस शून्य;
पूर्ण

/*
 * Like rb_entry_next_safe() क्रम the @cpu subtree.
 */
अटल काष्ठा perf_event *
perf_event_groups_next(काष्ठा perf_event *event)
अणु
	काष्ठा __group_key key = अणु
		.cpu = event->cpu,
		.cgroup = event_cgroup(event),
	पूर्ण;
	काष्ठा rb_node *next;

	next = rb_next_match(&key, &event->group_node, __group_cmp);
	अगर (next)
		वापस __node_2_pe(next);

	वापस शून्य;
पूर्ण

/*
 * Iterate through the whole groups tree.
 */
#घोषणा perf_event_groups_क्रम_each(event, groups)			\
	क्रम (event = rb_entry_safe(rb_first(&((groups)->tree)),		\
				typeof(*event), group_node); event;	\
		event = rb_entry_safe(rb_next(&event->group_node),	\
				typeof(*event), group_node))

/*
 * Add an event from the lists क्रम its context.
 * Must be called with ctx->mutex and ctx->lock held.
 */
अटल व्योम
list_add_event(काष्ठा perf_event *event, काष्ठा perf_event_context *ctx)
अणु
	lockdep_निश्चित_held(&ctx->lock);

	WARN_ON_ONCE(event->attach_state & PERF_ATTACH_CONTEXT);
	event->attach_state |= PERF_ATTACH_CONTEXT;

	event->tstamp = perf_event_समय(event);

	/*
	 * If we're a stand alone event or group leader, we go to the context
	 * list, group events are kept attached to the group so that
	 * perf_group_detach can, at all बार, locate all siblings.
	 */
	अगर (event->group_leader == event) अणु
		event->group_caps = event->event_caps;
		add_event_to_groups(event, ctx);
	पूर्ण

	list_add_rcu(&event->event_entry, &ctx->event_list);
	ctx->nr_events++;
	अगर (event->attr.inherit_stat)
		ctx->nr_stat++;

	अगर (event->state > PERF_EVENT_STATE_OFF)
		perf_cgroup_event_enable(event, ctx);

	ctx->generation++;
पूर्ण

/*
 * Initialize event state based on the perf_event_attr::disabled.
 */
अटल अंतरभूत व्योम perf_event__state_init(काष्ठा perf_event *event)
अणु
	event->state = event->attr.disabled ? PERF_EVENT_STATE_OFF :
					      PERF_EVENT_STATE_INACTIVE;
पूर्ण

अटल व्योम __perf_event_पढ़ो_size(काष्ठा perf_event *event, पूर्णांक nr_siblings)
अणु
	पूर्णांक entry = माप(u64); /* value */
	पूर्णांक size = 0;
	पूर्णांक nr = 1;

	अगर (event->attr.पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_ENABLED)
		size += माप(u64);

	अगर (event->attr.पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_RUNNING)
		size += माप(u64);

	अगर (event->attr.पढ़ो_क्रमmat & PERF_FORMAT_ID)
		entry += माप(u64);

	अगर (event->attr.पढ़ो_क्रमmat & PERF_FORMAT_GROUP) अणु
		nr += nr_siblings;
		size += माप(u64);
	पूर्ण

	size += entry * nr;
	event->पढ़ो_size = size;
पूर्ण

अटल व्योम __perf_event_header_size(काष्ठा perf_event *event, u64 sample_type)
अणु
	काष्ठा perf_sample_data *data;
	u16 size = 0;

	अगर (sample_type & PERF_SAMPLE_IP)
		size += माप(data->ip);

	अगर (sample_type & PERF_SAMPLE_ADDR)
		size += माप(data->addr);

	अगर (sample_type & PERF_SAMPLE_PERIOD)
		size += माप(data->period);

	अगर (sample_type & PERF_SAMPLE_WEIGHT_TYPE)
		size += माप(data->weight.full);

	अगर (sample_type & PERF_SAMPLE_READ)
		size += event->पढ़ो_size;

	अगर (sample_type & PERF_SAMPLE_DATA_SRC)
		size += माप(data->data_src.val);

	अगर (sample_type & PERF_SAMPLE_TRANSACTION)
		size += माप(data->txn);

	अगर (sample_type & PERF_SAMPLE_PHYS_ADDR)
		size += माप(data->phys_addr);

	अगर (sample_type & PERF_SAMPLE_CGROUP)
		size += माप(data->cgroup);

	अगर (sample_type & PERF_SAMPLE_DATA_PAGE_SIZE)
		size += माप(data->data_page_size);

	अगर (sample_type & PERF_SAMPLE_CODE_PAGE_SIZE)
		size += माप(data->code_page_size);

	event->header_size = size;
पूर्ण

/*
 * Called at perf_event creation and when events are attached/detached from a
 * group.
 */
अटल व्योम perf_event__header_size(काष्ठा perf_event *event)
अणु
	__perf_event_पढ़ो_size(event,
			       event->group_leader->nr_siblings);
	__perf_event_header_size(event, event->attr.sample_type);
पूर्ण

अटल व्योम perf_event__id_header_size(काष्ठा perf_event *event)
अणु
	काष्ठा perf_sample_data *data;
	u64 sample_type = event->attr.sample_type;
	u16 size = 0;

	अगर (sample_type & PERF_SAMPLE_TID)
		size += माप(data->tid_entry);

	अगर (sample_type & PERF_SAMPLE_TIME)
		size += माप(data->समय);

	अगर (sample_type & PERF_SAMPLE_IDENTIFIER)
		size += माप(data->id);

	अगर (sample_type & PERF_SAMPLE_ID)
		size += माप(data->id);

	अगर (sample_type & PERF_SAMPLE_STREAM_ID)
		size += माप(data->stream_id);

	अगर (sample_type & PERF_SAMPLE_CPU)
		size += माप(data->cpu_entry);

	event->id_header_size = size;
पूर्ण

अटल bool perf_event_validate_size(काष्ठा perf_event *event)
अणु
	/*
	 * The values computed here will be over-written when we actually
	 * attach the event.
	 */
	__perf_event_पढ़ो_size(event, event->group_leader->nr_siblings + 1);
	__perf_event_header_size(event, event->attr.sample_type & ~PERF_SAMPLE_READ);
	perf_event__id_header_size(event);

	/*
	 * Sum the lot; should not exceed the 64k limit we have on records.
	 * Conservative limit to allow क्रम callchains and other variable fields.
	 */
	अगर (event->पढ़ो_size + event->header_size +
	    event->id_header_size + माप(काष्ठा perf_event_header) >= 16*1024)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम perf_group_attach(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event *group_leader = event->group_leader, *pos;

	lockdep_निश्चित_held(&event->ctx->lock);

	/*
	 * We can have द्विगुन attach due to group movement in perf_event_खोलो.
	 */
	अगर (event->attach_state & PERF_ATTACH_GROUP)
		वापस;

	event->attach_state |= PERF_ATTACH_GROUP;

	अगर (group_leader == event)
		वापस;

	WARN_ON_ONCE(group_leader->ctx != event->ctx);

	group_leader->group_caps &= event->event_caps;

	list_add_tail(&event->sibling_list, &group_leader->sibling_list);
	group_leader->nr_siblings++;

	perf_event__header_size(group_leader);

	क्रम_each_sibling_event(pos, group_leader)
		perf_event__header_size(pos);
पूर्ण

/*
 * Remove an event from the lists क्रम its context.
 * Must be called with ctx->mutex and ctx->lock held.
 */
अटल व्योम
list_del_event(काष्ठा perf_event *event, काष्ठा perf_event_context *ctx)
अणु
	WARN_ON_ONCE(event->ctx != ctx);
	lockdep_निश्चित_held(&ctx->lock);

	/*
	 * We can have द्विगुन detach due to निकास/hot-unplug + बंद.
	 */
	अगर (!(event->attach_state & PERF_ATTACH_CONTEXT))
		वापस;

	event->attach_state &= ~PERF_ATTACH_CONTEXT;

	ctx->nr_events--;
	अगर (event->attr.inherit_stat)
		ctx->nr_stat--;

	list_del_rcu(&event->event_entry);

	अगर (event->group_leader == event)
		del_event_from_groups(event, ctx);

	/*
	 * If event was in error state, then keep it
	 * that way, otherwise bogus counts will be
	 * वापसed on पढ़ो(). The only way to get out
	 * of error state is by explicit re-enabling
	 * of the event
	 */
	अगर (event->state > PERF_EVENT_STATE_OFF) अणु
		perf_cgroup_event_disable(event, ctx);
		perf_event_set_state(event, PERF_EVENT_STATE_OFF);
	पूर्ण

	ctx->generation++;
पूर्ण

अटल पूर्णांक
perf_aux_output_match(काष्ठा perf_event *event, काष्ठा perf_event *aux_event)
अणु
	अगर (!has_aux(aux_event))
		वापस 0;

	अगर (!event->pmu->aux_output_match)
		वापस 0;

	वापस event->pmu->aux_output_match(aux_event);
पूर्ण

अटल व्योम put_event(काष्ठा perf_event *event);
अटल व्योम event_sched_out(काष्ठा perf_event *event,
			    काष्ठा perf_cpu_context *cpuctx,
			    काष्ठा perf_event_context *ctx);

अटल व्योम perf_put_aux_event(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_context *ctx = event->ctx;
	काष्ठा perf_cpu_context *cpuctx = __get_cpu_context(ctx);
	काष्ठा perf_event *iter;

	/*
	 * If event uses aux_event tear करोwn the link
	 */
	अगर (event->aux_event) अणु
		iter = event->aux_event;
		event->aux_event = शून्य;
		put_event(iter);
		वापस;
	पूर्ण

	/*
	 * If the event is an aux_event, tear करोwn all links to
	 * it from other events.
	 */
	क्रम_each_sibling_event(iter, event->group_leader) अणु
		अगर (iter->aux_event != event)
			जारी;

		iter->aux_event = शून्य;
		put_event(event);

		/*
		 * If it's ACTIVE, schedule it out and put it पूर्णांकo ERROR
		 * state so that we करोn't try to schedule it again. Note
		 * that perf_event_enable() will clear the ERROR status.
		 */
		event_sched_out(iter, cpuctx, ctx);
		perf_event_set_state(event, PERF_EVENT_STATE_ERROR);
	पूर्ण
पूर्ण

अटल bool perf_need_aux_event(काष्ठा perf_event *event)
अणु
	वापस !!event->attr.aux_output || !!event->attr.aux_sample_size;
पूर्ण

अटल पूर्णांक perf_get_aux_event(काष्ठा perf_event *event,
			      काष्ठा perf_event *group_leader)
अणु
	/*
	 * Our group leader must be an aux event अगर we want to be
	 * an aux_output. This way, the aux event will precede its
	 * aux_output events in the group, and thereक्रमe will always
	 * schedule first.
	 */
	अगर (!group_leader)
		वापस 0;

	/*
	 * aux_output and aux_sample_size are mutually exclusive.
	 */
	अगर (event->attr.aux_output && event->attr.aux_sample_size)
		वापस 0;

	अगर (event->attr.aux_output &&
	    !perf_aux_output_match(event, group_leader))
		वापस 0;

	अगर (event->attr.aux_sample_size && !group_leader->pmu->snapshot_aux)
		वापस 0;

	अगर (!atomic_दीर्घ_inc_not_zero(&group_leader->refcount))
		वापस 0;

	/*
	 * Link aux_outमाला_दो to their aux event; this is unकरोne in
	 * perf_group_detach() by perf_put_aux_event(). When the
	 * group in torn करोwn, the aux_output events loose their
	 * link to the aux_event and can't schedule any more.
	 */
	event->aux_event = group_leader;

	वापस 1;
पूर्ण

अटल अंतरभूत काष्ठा list_head *get_event_list(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_context *ctx = event->ctx;
	वापस event->attr.pinned ? &ctx->pinned_active : &ctx->flexible_active;
पूर्ण

/*
 * Events that have PERF_EV_CAP_SIBLING require being part of a group and
 * cannot exist on their own, schedule them out and move them पूर्णांकo the ERROR
 * state. Also see _perf_event_enable(), it will not be able to recover
 * this ERROR state.
 */
अटल अंतरभूत व्योम perf_हटाओ_sibling_event(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_context *ctx = event->ctx;
	काष्ठा perf_cpu_context *cpuctx = __get_cpu_context(ctx);

	event_sched_out(event, cpuctx, ctx);
	perf_event_set_state(event, PERF_EVENT_STATE_ERROR);
पूर्ण

अटल व्योम perf_group_detach(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event *leader = event->group_leader;
	काष्ठा perf_event *sibling, *पंचांगp;
	काष्ठा perf_event_context *ctx = event->ctx;

	lockdep_निश्चित_held(&ctx->lock);

	/*
	 * We can have द्विगुन detach due to निकास/hot-unplug + बंद.
	 */
	अगर (!(event->attach_state & PERF_ATTACH_GROUP))
		वापस;

	event->attach_state &= ~PERF_ATTACH_GROUP;

	perf_put_aux_event(event);

	/*
	 * If this is a sibling, हटाओ it from its group.
	 */
	अगर (leader != event) अणु
		list_del_init(&event->sibling_list);
		event->group_leader->nr_siblings--;
		जाओ out;
	पूर्ण

	/*
	 * If this was a group event with sibling events then
	 * upgrade the siblings to singleton events by adding them
	 * to whatever list we are on.
	 */
	list_क्रम_each_entry_safe(sibling, पंचांगp, &event->sibling_list, sibling_list) अणु

		अगर (sibling->event_caps & PERF_EV_CAP_SIBLING)
			perf_हटाओ_sibling_event(sibling);

		sibling->group_leader = sibling;
		list_del_init(&sibling->sibling_list);

		/* Inherit group flags from the previous leader */
		sibling->group_caps = event->group_caps;

		अगर (!RB_EMPTY_NODE(&event->group_node)) अणु
			add_event_to_groups(sibling, event->ctx);

			अगर (sibling->state == PERF_EVENT_STATE_ACTIVE)
				list_add_tail(&sibling->active_list, get_event_list(sibling));
		पूर्ण

		WARN_ON_ONCE(sibling->ctx != event->ctx);
	पूर्ण

out:
	क्रम_each_sibling_event(पंचांगp, leader)
		perf_event__header_size(पंचांगp);

	perf_event__header_size(leader);
पूर्ण

अटल व्योम sync_child_event(काष्ठा perf_event *child_event);

अटल व्योम perf_child_detach(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event *parent_event = event->parent;

	अगर (!(event->attach_state & PERF_ATTACH_CHILD))
		वापस;

	event->attach_state &= ~PERF_ATTACH_CHILD;

	अगर (WARN_ON_ONCE(!parent_event))
		वापस;

	lockdep_निश्चित_held(&parent_event->child_mutex);

	sync_child_event(event);
	list_del_init(&event->child_list);
पूर्ण

अटल bool is_orphaned_event(काष्ठा perf_event *event)
अणु
	वापस event->state == PERF_EVENT_STATE_DEAD;
पूर्ण

अटल अंतरभूत पूर्णांक __pmu_filter_match(काष्ठा perf_event *event)
अणु
	काष्ठा pmu *pmu = event->pmu;
	वापस pmu->filter_match ? pmu->filter_match(event) : 1;
पूर्ण

/*
 * Check whether we should attempt to schedule an event group based on
 * PMU-specअगरic filtering. An event group can consist of HW and SW events,
 * potentially with a SW leader, so we must check all the filters, to
 * determine whether a group is schedulable:
 */
अटल अंतरभूत पूर्णांक pmu_filter_match(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event *sibling;

	अगर (!__pmu_filter_match(event))
		वापस 0;

	क्रम_each_sibling_event(sibling, event) अणु
		अगर (!__pmu_filter_match(sibling))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक
event_filter_match(काष्ठा perf_event *event)
अणु
	वापस (event->cpu == -1 || event->cpu == smp_processor_id()) &&
	       perf_cgroup_match(event) && pmu_filter_match(event);
पूर्ण

अटल व्योम
event_sched_out(काष्ठा perf_event *event,
		  काष्ठा perf_cpu_context *cpuctx,
		  काष्ठा perf_event_context *ctx)
अणु
	क्रमागत perf_event_state state = PERF_EVENT_STATE_INACTIVE;

	WARN_ON_ONCE(event->ctx != ctx);
	lockdep_निश्चित_held(&ctx->lock);

	अगर (event->state != PERF_EVENT_STATE_ACTIVE)
		वापस;

	/*
	 * Asymmetry; we only schedule events _IN_ through ctx_sched_in(), but
	 * we can schedule events _OUT_ inभागidually through things like
	 * __perf_हटाओ_from_context().
	 */
	list_del_init(&event->active_list);

	perf_pmu_disable(event->pmu);

	event->pmu->del(event, 0);
	event->oncpu = -1;

	अगर (READ_ONCE(event->pending_disable) >= 0) अणु
		WRITE_ONCE(event->pending_disable, -1);
		perf_cgroup_event_disable(event, ctx);
		state = PERF_EVENT_STATE_OFF;
	पूर्ण
	perf_event_set_state(event, state);

	अगर (!is_software_event(event))
		cpuctx->active_oncpu--;
	अगर (!--ctx->nr_active)
		perf_event_ctx_deactivate(ctx);
	अगर (event->attr.freq && event->attr.sample_freq)
		ctx->nr_freq--;
	अगर (event->attr.exclusive || !cpuctx->active_oncpu)
		cpuctx->exclusive = 0;

	perf_pmu_enable(event->pmu);
पूर्ण

अटल व्योम
group_sched_out(काष्ठा perf_event *group_event,
		काष्ठा perf_cpu_context *cpuctx,
		काष्ठा perf_event_context *ctx)
अणु
	काष्ठा perf_event *event;

	अगर (group_event->state != PERF_EVENT_STATE_ACTIVE)
		वापस;

	perf_pmu_disable(ctx->pmu);

	event_sched_out(group_event, cpuctx, ctx);

	/*
	 * Schedule out siblings (अगर any):
	 */
	क्रम_each_sibling_event(event, group_event)
		event_sched_out(event, cpuctx, ctx);

	perf_pmu_enable(ctx->pmu);
पूर्ण

#घोषणा DETACH_GROUP	0x01UL
#घोषणा DETACH_CHILD	0x02UL

/*
 * Cross CPU call to हटाओ a perक्रमmance event
 *
 * We disable the event on the hardware level first. After that we
 * हटाओ it from the context list.
 */
अटल व्योम
__perf_हटाओ_from_context(काष्ठा perf_event *event,
			   काष्ठा perf_cpu_context *cpuctx,
			   काष्ठा perf_event_context *ctx,
			   व्योम *info)
अणु
	अचिन्हित दीर्घ flags = (अचिन्हित दीर्घ)info;

	अगर (ctx->is_active & EVENT_TIME) अणु
		update_context_समय(ctx);
		update_cgrp_समय_from_cpuctx(cpuctx);
	पूर्ण

	event_sched_out(event, cpuctx, ctx);
	अगर (flags & DETACH_GROUP)
		perf_group_detach(event);
	अगर (flags & DETACH_CHILD)
		perf_child_detach(event);
	list_del_event(event, ctx);

	अगर (!ctx->nr_events && ctx->is_active) अणु
		ctx->is_active = 0;
		ctx->rotate_necessary = 0;
		अगर (ctx->task) अणु
			WARN_ON_ONCE(cpuctx->task_ctx != ctx);
			cpuctx->task_ctx = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Remove the event from a task's (or a CPU's) list of events.
 *
 * If event->ctx is a cloned context, callers must make sure that
 * every task काष्ठा that event->ctx->task could possibly poपूर्णांक to
 * reमुख्यs valid.  This is OK when called from perf_release since
 * that only calls us on the top-level context, which can't be a clone.
 * When called from perf_event_निकास_task, it's OK because the
 * context has been detached from its task.
 */
अटल व्योम perf_हटाओ_from_context(काष्ठा perf_event *event, अचिन्हित दीर्घ flags)
अणु
	काष्ठा perf_event_context *ctx = event->ctx;

	lockdep_निश्चित_held(&ctx->mutex);

	/*
	 * Because of perf_event_निकास_task(), perf_हटाओ_from_context() ought
	 * to work in the face of TASK_TOMBSTONE, unlike every other
	 * event_function_call() user.
	 */
	raw_spin_lock_irq(&ctx->lock);
	अगर (!ctx->is_active) अणु
		__perf_हटाओ_from_context(event, __get_cpu_context(ctx),
					   ctx, (व्योम *)flags);
		raw_spin_unlock_irq(&ctx->lock);
		वापस;
	पूर्ण
	raw_spin_unlock_irq(&ctx->lock);

	event_function_call(event, __perf_हटाओ_from_context, (व्योम *)flags);
पूर्ण

/*
 * Cross CPU call to disable a perक्रमmance event
 */
अटल व्योम __perf_event_disable(काष्ठा perf_event *event,
				 काष्ठा perf_cpu_context *cpuctx,
				 काष्ठा perf_event_context *ctx,
				 व्योम *info)
अणु
	अगर (event->state < PERF_EVENT_STATE_INACTIVE)
		वापस;

	अगर (ctx->is_active & EVENT_TIME) अणु
		update_context_समय(ctx);
		update_cgrp_समय_from_event(event);
	पूर्ण

	अगर (event == event->group_leader)
		group_sched_out(event, cpuctx, ctx);
	अन्यथा
		event_sched_out(event, cpuctx, ctx);

	perf_event_set_state(event, PERF_EVENT_STATE_OFF);
	perf_cgroup_event_disable(event, ctx);
पूर्ण

/*
 * Disable an event.
 *
 * If event->ctx is a cloned context, callers must make sure that
 * every task काष्ठा that event->ctx->task could possibly poपूर्णांक to
 * reमुख्यs valid.  This condition is satisfied when called through
 * perf_event_क्रम_each_child or perf_event_क्रम_each because they
 * hold the top-level event's child_mutex, so any descendant that
 * goes to निकास will block in perf_event_निकास_event().
 *
 * When called from perf_pending_event it's OK because event->ctx
 * is the current context on this CPU and preemption is disabled,
 * hence we can't get पूर्णांकo perf_event_task_sched_out क्रम this context.
 */
अटल व्योम _perf_event_disable(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_context *ctx = event->ctx;

	raw_spin_lock_irq(&ctx->lock);
	अगर (event->state <= PERF_EVENT_STATE_OFF) अणु
		raw_spin_unlock_irq(&ctx->lock);
		वापस;
	पूर्ण
	raw_spin_unlock_irq(&ctx->lock);

	event_function_call(event, __perf_event_disable, शून्य);
पूर्ण

व्योम perf_event_disable_local(काष्ठा perf_event *event)
अणु
	event_function_local(event, __perf_event_disable, शून्य);
पूर्ण

/*
 * Strictly speaking kernel users cannot create groups and thereक्रमe this
 * पूर्णांकerface करोes not need the perf_event_ctx_lock() magic.
 */
व्योम perf_event_disable(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_context *ctx;

	ctx = perf_event_ctx_lock(event);
	_perf_event_disable(event);
	perf_event_ctx_unlock(event, ctx);
पूर्ण
EXPORT_SYMBOL_GPL(perf_event_disable);

व्योम perf_event_disable_inatomic(काष्ठा perf_event *event)
अणु
	WRITE_ONCE(event->pending_disable, smp_processor_id());
	/* can fail, see perf_pending_event_disable() */
	irq_work_queue(&event->pending);
पूर्ण

अटल व्योम perf_set_shaकरोw_समय(काष्ठा perf_event *event,
				 काष्ठा perf_event_context *ctx)
अणु
	/*
	 * use the correct समय source क्रम the समय snapshot
	 *
	 * We could get by without this by leveraging the
	 * fact that to get to this function, the caller
	 * has most likely alपढ़ोy called update_context_समय()
	 * and update_cgrp_समय_xx() and thus both बारtamp
	 * are identical (or very बंद). Given that tstamp is,
	 * alपढ़ोy adjusted क्रम cgroup, we could say that:
	 *    tstamp - ctx->बारtamp
	 * is equivalent to
	 *    tstamp - cgrp->बारtamp.
	 *
	 * Then, in perf_output_पढ़ो(), the calculation would
	 * work with no changes because:
	 * - event is guaranteed scheduled in
	 * - no scheduled out in between
	 * - thus the बारtamp would be the same
	 *
	 * But this is a bit hairy.
	 *
	 * So instead, we have an explicit cgroup call to reमुख्य
	 * within the समय source all aदीर्घ. We believe it
	 * is cleaner and simpler to understand.
	 */
	अगर (is_cgroup_event(event))
		perf_cgroup_set_shaकरोw_समय(event, event->tstamp);
	अन्यथा
		event->shaकरोw_ctx_समय = event->tstamp - ctx->बारtamp;
पूर्ण

#घोषणा MAX_INTERRUPTS (~0ULL)

अटल व्योम perf_log_throttle(काष्ठा perf_event *event, पूर्णांक enable);
अटल व्योम perf_log_itrace_start(काष्ठा perf_event *event);

अटल पूर्णांक
event_sched_in(काष्ठा perf_event *event,
		 काष्ठा perf_cpu_context *cpuctx,
		 काष्ठा perf_event_context *ctx)
अणु
	पूर्णांक ret = 0;

	WARN_ON_ONCE(event->ctx != ctx);

	lockdep_निश्चित_held(&ctx->lock);

	अगर (event->state <= PERF_EVENT_STATE_OFF)
		वापस 0;

	WRITE_ONCE(event->oncpu, smp_processor_id());
	/*
	 * Order event::oncpu ग_लिखो to happen beक्रमe the ACTIVE state is
	 * visible. This allows perf_event_अणुstop,पढ़ोपूर्ण() to observe the correct
	 * ->oncpu अगर it sees ACTIVE.
	 */
	smp_wmb();
	perf_event_set_state(event, PERF_EVENT_STATE_ACTIVE);

	/*
	 * Unthrottle events, since we scheduled we might have missed several
	 * ticks alपढ़ोy, also क्रम a heavily scheduling task there is little
	 * guarantee it'll get a tick in a समयly manner.
	 */
	अगर (unlikely(event->hw.पूर्णांकerrupts == MAX_INTERRUPTS)) अणु
		perf_log_throttle(event, 1);
		event->hw.पूर्णांकerrupts = 0;
	पूर्ण

	perf_pmu_disable(event->pmu);

	perf_set_shaकरोw_समय(event, ctx);

	perf_log_itrace_start(event);

	अगर (event->pmu->add(event, PERF_EF_START)) अणु
		perf_event_set_state(event, PERF_EVENT_STATE_INACTIVE);
		event->oncpu = -1;
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	अगर (!is_software_event(event))
		cpuctx->active_oncpu++;
	अगर (!ctx->nr_active++)
		perf_event_ctx_activate(ctx);
	अगर (event->attr.freq && event->attr.sample_freq)
		ctx->nr_freq++;

	अगर (event->attr.exclusive)
		cpuctx->exclusive = 1;

out:
	perf_pmu_enable(event->pmu);

	वापस ret;
पूर्ण

अटल पूर्णांक
group_sched_in(काष्ठा perf_event *group_event,
	       काष्ठा perf_cpu_context *cpuctx,
	       काष्ठा perf_event_context *ctx)
अणु
	काष्ठा perf_event *event, *partial_group = शून्य;
	काष्ठा pmu *pmu = ctx->pmu;

	अगर (group_event->state == PERF_EVENT_STATE_OFF)
		वापस 0;

	pmu->start_txn(pmu, PERF_PMU_TXN_ADD);

	अगर (event_sched_in(group_event, cpuctx, ctx))
		जाओ error;

	/*
	 * Schedule in siblings as one group (अगर any):
	 */
	क्रम_each_sibling_event(event, group_event) अणु
		अगर (event_sched_in(event, cpuctx, ctx)) अणु
			partial_group = event;
			जाओ group_error;
		पूर्ण
	पूर्ण

	अगर (!pmu->commit_txn(pmu))
		वापस 0;

group_error:
	/*
	 * Groups can be scheduled in as one unit only, so unकरो any
	 * partial group beक्रमe वापसing:
	 * The events up to the failed event are scheduled out normally.
	 */
	क्रम_each_sibling_event(event, group_event) अणु
		अगर (event == partial_group)
			अवरोध;

		event_sched_out(event, cpuctx, ctx);
	पूर्ण
	event_sched_out(group_event, cpuctx, ctx);

error:
	pmu->cancel_txn(pmu);
	वापस -EAGAIN;
पूर्ण

/*
 * Work out whether we can put this event group on the CPU now.
 */
अटल पूर्णांक group_can_go_on(काष्ठा perf_event *event,
			   काष्ठा perf_cpu_context *cpuctx,
			   पूर्णांक can_add_hw)
अणु
	/*
	 * Groups consisting entirely of software events can always go on.
	 */
	अगर (event->group_caps & PERF_EV_CAP_SOFTWARE)
		वापस 1;
	/*
	 * If an exclusive group is alपढ़ोy on, no other hardware
	 * events can go on.
	 */
	अगर (cpuctx->exclusive)
		वापस 0;
	/*
	 * If this group is exclusive and there are alपढ़ोy
	 * events on the CPU, it can't go on.
	 */
	अगर (event->attr.exclusive && !list_empty(get_event_list(event)))
		वापस 0;
	/*
	 * Otherwise, try to add it अगर all previous groups were able
	 * to go on.
	 */
	वापस can_add_hw;
पूर्ण

अटल व्योम add_event_to_ctx(काष्ठा perf_event *event,
			       काष्ठा perf_event_context *ctx)
अणु
	list_add_event(event, ctx);
	perf_group_attach(event);
पूर्ण

अटल व्योम ctx_sched_out(काष्ठा perf_event_context *ctx,
			  काष्ठा perf_cpu_context *cpuctx,
			  क्रमागत event_type_t event_type);
अटल व्योम
ctx_sched_in(काष्ठा perf_event_context *ctx,
	     काष्ठा perf_cpu_context *cpuctx,
	     क्रमागत event_type_t event_type,
	     काष्ठा task_काष्ठा *task);

अटल व्योम task_ctx_sched_out(काष्ठा perf_cpu_context *cpuctx,
			       काष्ठा perf_event_context *ctx,
			       क्रमागत event_type_t event_type)
अणु
	अगर (!cpuctx->task_ctx)
		वापस;

	अगर (WARN_ON_ONCE(ctx != cpuctx->task_ctx))
		वापस;

	ctx_sched_out(ctx, cpuctx, event_type);
पूर्ण

अटल व्योम perf_event_sched_in(काष्ठा perf_cpu_context *cpuctx,
				काष्ठा perf_event_context *ctx,
				काष्ठा task_काष्ठा *task)
अणु
	cpu_ctx_sched_in(cpuctx, EVENT_PINNED, task);
	अगर (ctx)
		ctx_sched_in(ctx, cpuctx, EVENT_PINNED, task);
	cpu_ctx_sched_in(cpuctx, EVENT_FLEXIBLE, task);
	अगर (ctx)
		ctx_sched_in(ctx, cpuctx, EVENT_FLEXIBLE, task);
पूर्ण

/*
 * We want to मुख्यtain the following priority of scheduling:
 *  - CPU pinned (EVENT_CPU | EVENT_PINNED)
 *  - task pinned (EVENT_PINNED)
 *  - CPU flexible (EVENT_CPU | EVENT_FLEXIBLE)
 *  - task flexible (EVENT_FLEXIBLE).
 *
 * In order to aव्योम unscheduling and scheduling back in everything every
 * समय an event is added, only करो it क्रम the groups of equal priority and
 * below.
 *
 * This can be called after a batch operation on task events, in which हाल
 * event_type is a bit mask of the types of events involved. For CPU events,
 * event_type is only either EVENT_PINNED or EVENT_FLEXIBLE.
 */
अटल व्योम ctx_resched(काष्ठा perf_cpu_context *cpuctx,
			काष्ठा perf_event_context *task_ctx,
			क्रमागत event_type_t event_type)
अणु
	क्रमागत event_type_t ctx_event_type;
	bool cpu_event = !!(event_type & EVENT_CPU);

	/*
	 * If pinned groups are involved, flexible groups also need to be
	 * scheduled out.
	 */
	अगर (event_type & EVENT_PINNED)
		event_type |= EVENT_FLEXIBLE;

	ctx_event_type = event_type & EVENT_ALL;

	perf_pmu_disable(cpuctx->ctx.pmu);
	अगर (task_ctx)
		task_ctx_sched_out(cpuctx, task_ctx, event_type);

	/*
	 * Decide which cpu ctx groups to schedule out based on the types
	 * of events that caused rescheduling:
	 *  - EVENT_CPU: schedule out corresponding groups;
	 *  - EVENT_PINNED task events: schedule out EVENT_FLEXIBLE groups;
	 *  - otherwise, करो nothing more.
	 */
	अगर (cpu_event)
		cpu_ctx_sched_out(cpuctx, ctx_event_type);
	अन्यथा अगर (ctx_event_type & EVENT_PINNED)
		cpu_ctx_sched_out(cpuctx, EVENT_FLEXIBLE);

	perf_event_sched_in(cpuctx, task_ctx, current);
	perf_pmu_enable(cpuctx->ctx.pmu);
पूर्ण

व्योम perf_pmu_resched(काष्ठा pmu *pmu)
अणु
	काष्ठा perf_cpu_context *cpuctx = this_cpu_ptr(pmu->pmu_cpu_context);
	काष्ठा perf_event_context *task_ctx = cpuctx->task_ctx;

	perf_ctx_lock(cpuctx, task_ctx);
	ctx_resched(cpuctx, task_ctx, EVENT_ALL|EVENT_CPU);
	perf_ctx_unlock(cpuctx, task_ctx);
पूर्ण

/*
 * Cross CPU call to install and enable a perक्रमmance event
 *
 * Very similar to remote_function() + event_function() but cannot assume that
 * things like ctx->is_active and cpuctx->task_ctx are set.
 */
अटल पूर्णांक  __perf_install_in_context(व्योम *info)
अणु
	काष्ठा perf_event *event = info;
	काष्ठा perf_event_context *ctx = event->ctx;
	काष्ठा perf_cpu_context *cpuctx = __get_cpu_context(ctx);
	काष्ठा perf_event_context *task_ctx = cpuctx->task_ctx;
	bool reprogram = true;
	पूर्णांक ret = 0;

	raw_spin_lock(&cpuctx->ctx.lock);
	अगर (ctx->task) अणु
		raw_spin_lock(&ctx->lock);
		task_ctx = ctx;

		reprogram = (ctx->task == current);

		/*
		 * If the task is running, it must be running on this CPU,
		 * otherwise we cannot reprogram things.
		 *
		 * If its not running, we करोn't care, ctx->lock will
		 * serialize against it becoming runnable.
		 */
		अगर (task_curr(ctx->task) && !reprogram) अणु
			ret = -ESRCH;
			जाओ unlock;
		पूर्ण

		WARN_ON_ONCE(reprogram && cpuctx->task_ctx && cpuctx->task_ctx != ctx);
	पूर्ण अन्यथा अगर (task_ctx) अणु
		raw_spin_lock(&task_ctx->lock);
	पूर्ण

#अगर_घोषित CONFIG_CGROUP_PERF
	अगर (event->state > PERF_EVENT_STATE_OFF && is_cgroup_event(event)) अणु
		/*
		 * If the current cgroup करोesn't match the event's
		 * cgroup, we should not try to schedule it.
		 */
		काष्ठा perf_cgroup *cgrp = perf_cgroup_from_task(current, ctx);
		reprogram = cgroup_is_descendant(cgrp->css.cgroup,
					event->cgrp->css.cgroup);
	पूर्ण
#पूर्ण_अगर

	अगर (reprogram) अणु
		ctx_sched_out(ctx, cpuctx, EVENT_TIME);
		add_event_to_ctx(event, ctx);
		ctx_resched(cpuctx, task_ctx, get_event_type(event));
	पूर्ण अन्यथा अणु
		add_event_to_ctx(event, ctx);
	पूर्ण

unlock:
	perf_ctx_unlock(cpuctx, task_ctx);

	वापस ret;
पूर्ण

अटल bool exclusive_event_installable(काष्ठा perf_event *event,
					काष्ठा perf_event_context *ctx);

/*
 * Attach a perक्रमmance event to a context.
 *
 * Very similar to event_function_call, see comment there.
 */
अटल व्योम
perf_install_in_context(काष्ठा perf_event_context *ctx,
			काष्ठा perf_event *event,
			पूर्णांक cpu)
अणु
	काष्ठा task_काष्ठा *task = READ_ONCE(ctx->task);

	lockdep_निश्चित_held(&ctx->mutex);

	WARN_ON_ONCE(!exclusive_event_installable(event, ctx));

	अगर (event->cpu != -1)
		event->cpu = cpu;

	/*
	 * Ensures that अगर we can observe event->ctx, both the event and ctx
	 * will be 'complete'. See perf_iterate_sb_cpu().
	 */
	smp_store_release(&event->ctx, ctx);

	/*
	 * perf_event_attr::disabled events will not run and can be initialized
	 * without IPI. Except when this is the first event क्रम the context, in
	 * that हाल we need the magic of the IPI to set ctx->is_active.
	 *
	 * The IOC_ENABLE that is sure to follow the creation of a disabled
	 * event will issue the IPI and reprogram the hardware.
	 */
	अगर (__perf_effective_state(event) == PERF_EVENT_STATE_OFF && ctx->nr_events) अणु
		raw_spin_lock_irq(&ctx->lock);
		अगर (ctx->task == TASK_TOMBSTONE) अणु
			raw_spin_unlock_irq(&ctx->lock);
			वापस;
		पूर्ण
		add_event_to_ctx(event, ctx);
		raw_spin_unlock_irq(&ctx->lock);
		वापस;
	पूर्ण

	अगर (!task) अणु
		cpu_function_call(cpu, __perf_install_in_context, event);
		वापस;
	पूर्ण

	/*
	 * Should not happen, we validate the ctx is still alive beक्रमe calling.
	 */
	अगर (WARN_ON_ONCE(task == TASK_TOMBSTONE))
		वापस;

	/*
	 * Installing events is tricky because we cannot rely on ctx->is_active
	 * to be set in हाल this is the nr_events 0 -> 1 transition.
	 *
	 * Instead we use task_curr(), which tells us अगर the task is running.
	 * However, since we use task_curr() outside of rq::lock, we can race
	 * against the actual state. This means the result can be wrong.
	 *
	 * If we get a false positive, we retry, this is harmless.
	 *
	 * If we get a false negative, things are complicated. If we are after
	 * perf_event_context_sched_in() ctx::lock will serialize us, and the
	 * value must be correct. If we're before, it doesn't matter since
	 * perf_event_context_sched_in() will program the counter.
	 *
	 * However, this hinges on the remote context चयन having observed
	 * our task->perf_event_ctxp[] store, such that it will in fact take
	 * ctx::lock in perf_event_context_sched_in().
	 *
	 * We करो this by task_function_call(), अगर the IPI fails to hit the task
	 * we know any future context चयन of task must see the
	 * perf_event_ctpx[] store.
	 */

	/*
	 * This smp_mb() orders the task->perf_event_ctxp[] store with the
	 * task_cpu() load, such that अगर the IPI then करोes not find the task
	 * running, a future context चयन of that task must observe the
	 * store.
	 */
	smp_mb();
again:
	अगर (!task_function_call(task, __perf_install_in_context, event))
		वापस;

	raw_spin_lock_irq(&ctx->lock);
	task = ctx->task;
	अगर (WARN_ON_ONCE(task == TASK_TOMBSTONE)) अणु
		/*
		 * Cannot happen because we alपढ़ोy checked above (which also
		 * cannot happen), and we hold ctx->mutex, which serializes us
		 * against perf_event_निकास_task_context().
		 */
		raw_spin_unlock_irq(&ctx->lock);
		वापस;
	पूर्ण
	/*
	 * If the task is not running, ctx->lock will aव्योम it becoming so,
	 * thus we can safely install the event.
	 */
	अगर (task_curr(task)) अणु
		raw_spin_unlock_irq(&ctx->lock);
		जाओ again;
	पूर्ण
	add_event_to_ctx(event, ctx);
	raw_spin_unlock_irq(&ctx->lock);
पूर्ण

/*
 * Cross CPU call to enable a perक्रमmance event
 */
अटल व्योम __perf_event_enable(काष्ठा perf_event *event,
				काष्ठा perf_cpu_context *cpuctx,
				काष्ठा perf_event_context *ctx,
				व्योम *info)
अणु
	काष्ठा perf_event *leader = event->group_leader;
	काष्ठा perf_event_context *task_ctx;

	अगर (event->state >= PERF_EVENT_STATE_INACTIVE ||
	    event->state <= PERF_EVENT_STATE_ERROR)
		वापस;

	अगर (ctx->is_active)
		ctx_sched_out(ctx, cpuctx, EVENT_TIME);

	perf_event_set_state(event, PERF_EVENT_STATE_INACTIVE);
	perf_cgroup_event_enable(event, ctx);

	अगर (!ctx->is_active)
		वापस;

	अगर (!event_filter_match(event)) अणु
		ctx_sched_in(ctx, cpuctx, EVENT_TIME, current);
		वापस;
	पूर्ण

	/*
	 * If the event is in a group and isn't the group leader,
	 * then करोn't put it on unless the group is on.
	 */
	अगर (leader != event && leader->state != PERF_EVENT_STATE_ACTIVE) अणु
		ctx_sched_in(ctx, cpuctx, EVENT_TIME, current);
		वापस;
	पूर्ण

	task_ctx = cpuctx->task_ctx;
	अगर (ctx->task)
		WARN_ON_ONCE(task_ctx != ctx);

	ctx_resched(cpuctx, task_ctx, get_event_type(event));
पूर्ण

/*
 * Enable an event.
 *
 * If event->ctx is a cloned context, callers must make sure that
 * every task काष्ठा that event->ctx->task could possibly poपूर्णांक to
 * reमुख्यs valid.  This condition is satisfied when called through
 * perf_event_क्रम_each_child or perf_event_क्रम_each as described
 * क्रम perf_event_disable.
 */
अटल व्योम _perf_event_enable(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_context *ctx = event->ctx;

	raw_spin_lock_irq(&ctx->lock);
	अगर (event->state >= PERF_EVENT_STATE_INACTIVE ||
	    event->state <  PERF_EVENT_STATE_ERROR) अणु
out:
		raw_spin_unlock_irq(&ctx->lock);
		वापस;
	पूर्ण

	/*
	 * If the event is in error state, clear that first.
	 *
	 * That way, अगर we see the event in error state below, we know that it
	 * has gone back पूर्णांकo error state, as distinct from the task having
	 * been scheduled away beक्रमe the cross-call arrived.
	 */
	अगर (event->state == PERF_EVENT_STATE_ERROR) अणु
		/*
		 * Detached SIBLING events cannot leave ERROR state.
		 */
		अगर (event->event_caps & PERF_EV_CAP_SIBLING &&
		    event->group_leader == event)
			जाओ out;

		event->state = PERF_EVENT_STATE_OFF;
	पूर्ण
	raw_spin_unlock_irq(&ctx->lock);

	event_function_call(event, __perf_event_enable, शून्य);
पूर्ण

/*
 * See perf_event_disable();
 */
व्योम perf_event_enable(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_context *ctx;

	ctx = perf_event_ctx_lock(event);
	_perf_event_enable(event);
	perf_event_ctx_unlock(event, ctx);
पूर्ण
EXPORT_SYMBOL_GPL(perf_event_enable);

काष्ठा stop_event_data अणु
	काष्ठा perf_event	*event;
	अचिन्हित पूर्णांक		restart;
पूर्ण;

अटल पूर्णांक __perf_event_stop(व्योम *info)
अणु
	काष्ठा stop_event_data *sd = info;
	काष्ठा perf_event *event = sd->event;

	/* अगर it's alपढ़ोy INACTIVE, करो nothing */
	अगर (READ_ONCE(event->state) != PERF_EVENT_STATE_ACTIVE)
		वापस 0;

	/* matches smp_wmb() in event_sched_in() */
	smp_rmb();

	/*
	 * There is a winकरोw with पूर्णांकerrupts enabled beक्रमe we get here,
	 * so we need to check again lest we try to stop another CPU's event.
	 */
	अगर (READ_ONCE(event->oncpu) != smp_processor_id())
		वापस -EAGAIN;

	event->pmu->stop(event, PERF_EF_UPDATE);

	/*
	 * May race with the actual stop (through perf_pmu_output_stop()),
	 * but it is only used क्रम events with AUX ring buffer, and such
	 * events will refuse to restart because of rb::aux_mmap_count==0,
	 * see comments in perf_aux_output_begin().
	 *
	 * Since this is happening on an event-local CPU, no trace is lost
	 * जबतक restarting.
	 */
	अगर (sd->restart)
		event->pmu->start(event, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक perf_event_stop(काष्ठा perf_event *event, पूर्णांक restart)
अणु
	काष्ठा stop_event_data sd = अणु
		.event		= event,
		.restart	= restart,
	पूर्ण;
	पूर्णांक ret = 0;

	करो अणु
		अगर (READ_ONCE(event->state) != PERF_EVENT_STATE_ACTIVE)
			वापस 0;

		/* matches smp_wmb() in event_sched_in() */
		smp_rmb();

		/*
		 * We only want to restart ACTIVE events, so अगर the event goes
		 * inactive here (event->oncpu==-1), there's nothing more to करो;
		 * fall through with ret==-ENXIO.
		 */
		ret = cpu_function_call(READ_ONCE(event->oncpu),
					__perf_event_stop, &sd);
	पूर्ण जबतक (ret == -EAGAIN);

	वापस ret;
पूर्ण

/*
 * In order to contain the amount of racy and tricky in the address filter
 * configuration management, it is a two part process:
 *
 * (p1) when userspace mappings change as a result of (1) or (2) or (3) below,
 *      we update the addresses of corresponding vmas in
 *	event::addr_filter_ranges array and bump the event::addr_filters_gen;
 * (p2) when an event is scheduled in (pmu::add), it calls
 *      perf_event_addr_filters_sync() which calls pmu::addr_filters_sync()
 *      अगर the generation has changed since the previous call.
 *
 * If (p1) happens जबतक the event is active, we restart it to क्रमce (p2).
 *
 * (1) perf_addr_filters_apply(): adjusting filters' offsets based on
 *     pre-existing mappings, called once when new filters arrive via SET_FILTER
 *     ioctl;
 * (2) perf_addr_filters_adjust(): adjusting filters' offsets based on newly
 *     रेजिस्टरed mapping, called क्रम every new mmap(), with mm::mmap_lock करोwn
 *     क्रम पढ़ोing;
 * (3) perf_event_addr_filters_exec(): clearing filters' offsets in the process
 *     of exec.
 */
व्योम perf_event_addr_filters_sync(काष्ठा perf_event *event)
अणु
	काष्ठा perf_addr_filters_head *अगरh = perf_event_addr_filters(event);

	अगर (!has_addr_filter(event))
		वापस;

	raw_spin_lock(&अगरh->lock);
	अगर (event->addr_filters_gen != event->hw.addr_filters_gen) अणु
		event->pmu->addr_filters_sync(event);
		event->hw.addr_filters_gen = event->addr_filters_gen;
	पूर्ण
	raw_spin_unlock(&अगरh->lock);
पूर्ण
EXPORT_SYMBOL_GPL(perf_event_addr_filters_sync);

अटल पूर्णांक _perf_event_refresh(काष्ठा perf_event *event, पूर्णांक refresh)
अणु
	/*
	 * not supported on inherited events
	 */
	अगर (event->attr.inherit || !is_sampling_event(event))
		वापस -EINVAL;

	atomic_add(refresh, &event->event_limit);
	_perf_event_enable(event);

	वापस 0;
पूर्ण

/*
 * See perf_event_disable()
 */
पूर्णांक perf_event_refresh(काष्ठा perf_event *event, पूर्णांक refresh)
अणु
	काष्ठा perf_event_context *ctx;
	पूर्णांक ret;

	ctx = perf_event_ctx_lock(event);
	ret = _perf_event_refresh(event, refresh);
	perf_event_ctx_unlock(event, ctx);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(perf_event_refresh);

अटल पूर्णांक perf_event_modअगरy_अवरोधpoपूर्णांक(काष्ठा perf_event *bp,
					 काष्ठा perf_event_attr *attr)
अणु
	पूर्णांक err;

	_perf_event_disable(bp);

	err = modअगरy_user_hw_अवरोधpoपूर्णांक_check(bp, attr, true);

	अगर (!bp->attr.disabled)
		_perf_event_enable(bp);

	वापस err;
पूर्ण

अटल पूर्णांक perf_event_modअगरy_attr(काष्ठा perf_event *event,
				  काष्ठा perf_event_attr *attr)
अणु
	पूर्णांक (*func)(काष्ठा perf_event *, काष्ठा perf_event_attr *);
	काष्ठा perf_event *child;
	पूर्णांक err;

	अगर (event->attr.type != attr->type)
		वापस -EINVAL;

	चयन (event->attr.type) अणु
	हाल PERF_TYPE_BREAKPOINT:
		func = perf_event_modअगरy_अवरोधpoपूर्णांक;
		अवरोध;
	शेष:
		/* Place holder क्रम future additions. */
		वापस -EOPNOTSUPP;
	पूर्ण

	WARN_ON_ONCE(event->ctx->parent_ctx);

	mutex_lock(&event->child_mutex);
	err = func(event, attr);
	अगर (err)
		जाओ out;
	list_क्रम_each_entry(child, &event->child_list, child_list) अणु
		err = func(child, attr);
		अगर (err)
			जाओ out;
	पूर्ण
out:
	mutex_unlock(&event->child_mutex);
	वापस err;
पूर्ण

अटल व्योम ctx_sched_out(काष्ठा perf_event_context *ctx,
			  काष्ठा perf_cpu_context *cpuctx,
			  क्रमागत event_type_t event_type)
अणु
	काष्ठा perf_event *event, *पंचांगp;
	पूर्णांक is_active = ctx->is_active;

	lockdep_निश्चित_held(&ctx->lock);

	अगर (likely(!ctx->nr_events)) अणु
		/*
		 * See __perf_हटाओ_from_context().
		 */
		WARN_ON_ONCE(ctx->is_active);
		अगर (ctx->task)
			WARN_ON_ONCE(cpuctx->task_ctx);
		वापस;
	पूर्ण

	ctx->is_active &= ~event_type;
	अगर (!(ctx->is_active & EVENT_ALL))
		ctx->is_active = 0;

	अगर (ctx->task) अणु
		WARN_ON_ONCE(cpuctx->task_ctx != ctx);
		अगर (!ctx->is_active)
			cpuctx->task_ctx = शून्य;
	पूर्ण

	/*
	 * Always update समय अगर it was set; not only when it changes.
	 * Otherwise we can 'forget' to update समय क्रम any but the last
	 * context we sched out. For example:
	 *
	 *   ctx_sched_out(.event_type = EVENT_FLEXIBLE)
	 *   ctx_sched_out(.event_type = EVENT_PINNED)
	 *
	 * would only update समय क्रम the pinned events.
	 */
	अगर (is_active & EVENT_TIME) अणु
		/* update (and stop) ctx समय */
		update_context_समय(ctx);
		update_cgrp_समय_from_cpuctx(cpuctx);
	पूर्ण

	is_active ^= ctx->is_active; /* changed bits */

	अगर (!ctx->nr_active || !(is_active & EVENT_ALL))
		वापस;

	perf_pmu_disable(ctx->pmu);
	अगर (is_active & EVENT_PINNED) अणु
		list_क्रम_each_entry_safe(event, पंचांगp, &ctx->pinned_active, active_list)
			group_sched_out(event, cpuctx, ctx);
	पूर्ण

	अगर (is_active & EVENT_FLEXIBLE) अणु
		list_क्रम_each_entry_safe(event, पंचांगp, &ctx->flexible_active, active_list)
			group_sched_out(event, cpuctx, ctx);

		/*
		 * Since we cleared EVENT_FLEXIBLE, also clear
		 * rotate_necessary, is will be reset by
		 * ctx_flexible_sched_in() when needed.
		 */
		ctx->rotate_necessary = 0;
	पूर्ण
	perf_pmu_enable(ctx->pmu);
पूर्ण

/*
 * Test whether two contexts are equivalent, i.e. whether they have both been
 * cloned from the same version of the same context.
 *
 * Equivalence is measured using a generation number in the context that is
 * incremented on each modअगरication to it; see unclone_ctx(), list_add_event()
 * and list_del_event().
 */
अटल पूर्णांक context_equiv(काष्ठा perf_event_context *ctx1,
			 काष्ठा perf_event_context *ctx2)
अणु
	lockdep_निश्चित_held(&ctx1->lock);
	lockdep_निश्चित_held(&ctx2->lock);

	/* Pinning disables the swap optimization */
	अगर (ctx1->pin_count || ctx2->pin_count)
		वापस 0;

	/* If ctx1 is the parent of ctx2 */
	अगर (ctx1 == ctx2->parent_ctx && ctx1->generation == ctx2->parent_gen)
		वापस 1;

	/* If ctx2 is the parent of ctx1 */
	अगर (ctx1->parent_ctx == ctx2 && ctx1->parent_gen == ctx2->generation)
		वापस 1;

	/*
	 * If ctx1 and ctx2 have the same parent; we flatten the parent
	 * hierarchy, see perf_event_init_context().
	 */
	अगर (ctx1->parent_ctx && ctx1->parent_ctx == ctx2->parent_ctx &&
			ctx1->parent_gen == ctx2->parent_gen)
		वापस 1;

	/* Unmatched */
	वापस 0;
पूर्ण

अटल व्योम __perf_event_sync_stat(काष्ठा perf_event *event,
				     काष्ठा perf_event *next_event)
अणु
	u64 value;

	अगर (!event->attr.inherit_stat)
		वापस;

	/*
	 * Update the event value, we cannot use perf_event_पढ़ो()
	 * because we're in the middle of a context चयन and have IRQs
	 * disabled, which upsets smp_call_function_single(), however
	 * we know the event must be on the current CPU, thereक्रमe we
	 * करोn't need to use it.
	 */
	अगर (event->state == PERF_EVENT_STATE_ACTIVE)
		event->pmu->पढ़ो(event);

	perf_event_update_समय(event);

	/*
	 * In order to keep per-task stats reliable we need to flip the event
	 * values when we flip the contexts.
	 */
	value = local64_पढ़ो(&next_event->count);
	value = local64_xchg(&event->count, value);
	local64_set(&next_event->count, value);

	swap(event->total_समय_enabled, next_event->total_समय_enabled);
	swap(event->total_समय_running, next_event->total_समय_running);

	/*
	 * Since we swizzled the values, update the user visible data too.
	 */
	perf_event_update_userpage(event);
	perf_event_update_userpage(next_event);
पूर्ण

अटल व्योम perf_event_sync_stat(काष्ठा perf_event_context *ctx,
				   काष्ठा perf_event_context *next_ctx)
अणु
	काष्ठा perf_event *event, *next_event;

	अगर (!ctx->nr_stat)
		वापस;

	update_context_समय(ctx);

	event = list_first_entry(&ctx->event_list,
				   काष्ठा perf_event, event_entry);

	next_event = list_first_entry(&next_ctx->event_list,
					काष्ठा perf_event, event_entry);

	जबतक (&event->event_entry != &ctx->event_list &&
	       &next_event->event_entry != &next_ctx->event_list) अणु

		__perf_event_sync_stat(event, next_event);

		event = list_next_entry(event, event_entry);
		next_event = list_next_entry(next_event, event_entry);
	पूर्ण
पूर्ण

अटल व्योम perf_event_context_sched_out(काष्ठा task_काष्ठा *task, पूर्णांक ctxn,
					 काष्ठा task_काष्ठा *next)
अणु
	काष्ठा perf_event_context *ctx = task->perf_event_ctxp[ctxn];
	काष्ठा perf_event_context *next_ctx;
	काष्ठा perf_event_context *parent, *next_parent;
	काष्ठा perf_cpu_context *cpuctx;
	पूर्णांक करो_चयन = 1;
	काष्ठा pmu *pmu;

	अगर (likely(!ctx))
		वापस;

	pmu = ctx->pmu;
	cpuctx = __get_cpu_context(ctx);
	अगर (!cpuctx->task_ctx)
		वापस;

	rcu_पढ़ो_lock();
	next_ctx = next->perf_event_ctxp[ctxn];
	अगर (!next_ctx)
		जाओ unlock;

	parent = rcu_dereference(ctx->parent_ctx);
	next_parent = rcu_dereference(next_ctx->parent_ctx);

	/* If neither context have a parent context; they cannot be clones. */
	अगर (!parent && !next_parent)
		जाओ unlock;

	अगर (next_parent == ctx || next_ctx == parent || next_parent == parent) अणु
		/*
		 * Looks like the two contexts are clones, so we might be
		 * able to optimize the context चयन.  We lock both
		 * contexts and check that they are clones under the
		 * lock (including re-checking that neither has been
		 * uncloned in the meanसमय).  It करोesn't matter which
		 * order we take the locks because no other cpu could
		 * be trying to lock both of these tasks.
		 */
		raw_spin_lock(&ctx->lock);
		raw_spin_lock_nested(&next_ctx->lock, SINGLE_DEPTH_NESTING);
		अगर (context_equiv(ctx, next_ctx)) अणु

			WRITE_ONCE(ctx->task, next);
			WRITE_ONCE(next_ctx->task, task);

			perf_pmu_disable(pmu);

			अगर (cpuctx->sched_cb_usage && pmu->sched_task)
				pmu->sched_task(ctx, false);

			/*
			 * PMU specअगरic parts of task perf context can require
			 * additional synchronization. As an example of such
			 * synchronization see implementation details of Intel
			 * LBR call stack data profiling;
			 */
			अगर (pmu->swap_task_ctx)
				pmu->swap_task_ctx(ctx, next_ctx);
			अन्यथा
				swap(ctx->task_ctx_data, next_ctx->task_ctx_data);

			perf_pmu_enable(pmu);

			/*
			 * RCU_INIT_POINTER here is safe because we've not
			 * modअगरied the ctx and the above modअगरication of
			 * ctx->task and ctx->task_ctx_data are immaterial
			 * since those values are always verअगरied under
			 * ctx->lock which we're now holding.
			 */
			RCU_INIT_POINTER(task->perf_event_ctxp[ctxn], next_ctx);
			RCU_INIT_POINTER(next->perf_event_ctxp[ctxn], ctx);

			करो_चयन = 0;

			perf_event_sync_stat(ctx, next_ctx);
		पूर्ण
		raw_spin_unlock(&next_ctx->lock);
		raw_spin_unlock(&ctx->lock);
	पूर्ण
unlock:
	rcu_पढ़ो_unlock();

	अगर (करो_चयन) अणु
		raw_spin_lock(&ctx->lock);
		perf_pmu_disable(pmu);

		अगर (cpuctx->sched_cb_usage && pmu->sched_task)
			pmu->sched_task(ctx, false);
		task_ctx_sched_out(cpuctx, ctx, EVENT_ALL);

		perf_pmu_enable(pmu);
		raw_spin_unlock(&ctx->lock);
	पूर्ण
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा list_head, sched_cb_list);

व्योम perf_sched_cb_dec(काष्ठा pmu *pmu)
अणु
	काष्ठा perf_cpu_context *cpuctx = this_cpu_ptr(pmu->pmu_cpu_context);

	this_cpu_dec(perf_sched_cb_usages);

	अगर (!--cpuctx->sched_cb_usage)
		list_del(&cpuctx->sched_cb_entry);
पूर्ण


व्योम perf_sched_cb_inc(काष्ठा pmu *pmu)
अणु
	काष्ठा perf_cpu_context *cpuctx = this_cpu_ptr(pmu->pmu_cpu_context);

	अगर (!cpuctx->sched_cb_usage++)
		list_add(&cpuctx->sched_cb_entry, this_cpu_ptr(&sched_cb_list));

	this_cpu_inc(perf_sched_cb_usages);
पूर्ण

/*
 * This function provides the context चयन callback to the lower code
 * layer. It is invoked ONLY when the context चयन callback is enabled.
 *
 * This callback is relevant even to per-cpu events; क्रम example multi event
 * PEBS requires this to provide PID/TID inक्रमmation. This requires we flush
 * all queued PEBS records beक्रमe we context चयन to a new task.
 */
अटल व्योम __perf_pmu_sched_task(काष्ठा perf_cpu_context *cpuctx, bool sched_in)
अणु
	काष्ठा pmu *pmu;

	pmu = cpuctx->ctx.pmu; /* software PMUs will not have sched_task */

	अगर (WARN_ON_ONCE(!pmu->sched_task))
		वापस;

	perf_ctx_lock(cpuctx, cpuctx->task_ctx);
	perf_pmu_disable(pmu);

	pmu->sched_task(cpuctx->task_ctx, sched_in);

	perf_pmu_enable(pmu);
	perf_ctx_unlock(cpuctx, cpuctx->task_ctx);
पूर्ण

अटल व्योम perf_pmu_sched_task(काष्ठा task_काष्ठा *prev,
				काष्ठा task_काष्ठा *next,
				bool sched_in)
अणु
	काष्ठा perf_cpu_context *cpuctx;

	अगर (prev == next)
		वापस;

	list_क्रम_each_entry(cpuctx, this_cpu_ptr(&sched_cb_list), sched_cb_entry) अणु
		/* will be handled in perf_event_context_sched_in/out */
		अगर (cpuctx->task_ctx)
			जारी;

		__perf_pmu_sched_task(cpuctx, sched_in);
	पूर्ण
पूर्ण

अटल व्योम perf_event_चयन(काष्ठा task_काष्ठा *task,
			      काष्ठा task_काष्ठा *next_prev, bool sched_in);

#घोषणा क्रम_each_task_context_nr(ctxn)					\
	क्रम ((ctxn) = 0; (ctxn) < perf_nr_task_contexts; (ctxn)++)

/*
 * Called from scheduler to हटाओ the events of the current task,
 * with पूर्णांकerrupts disabled.
 *
 * We stop each event and update the event value in event->count.
 *
 * This करोes not protect us against NMI, but disable()
 * sets the disabled bit in the control field of event _beक्रमe_
 * accessing the event control रेजिस्टर. If a NMI hits, then it will
 * not restart the event.
 */
व्योम __perf_event_task_sched_out(काष्ठा task_काष्ठा *task,
				 काष्ठा task_काष्ठा *next)
अणु
	पूर्णांक ctxn;

	अगर (__this_cpu_पढ़ो(perf_sched_cb_usages))
		perf_pmu_sched_task(task, next, false);

	अगर (atomic_पढ़ो(&nr_चयन_events))
		perf_event_चयन(task, next, false);

	क्रम_each_task_context_nr(ctxn)
		perf_event_context_sched_out(task, ctxn, next);

	/*
	 * अगर cgroup events exist on this CPU, then we need
	 * to check अगर we have to चयन out PMU state.
	 * cgroup event are प्रणाली-wide mode only
	 */
	अगर (atomic_पढ़ो(this_cpu_ptr(&perf_cgroup_events)))
		perf_cgroup_sched_out(task, next);
पूर्ण

/*
 * Called with IRQs disabled
 */
अटल व्योम cpu_ctx_sched_out(काष्ठा perf_cpu_context *cpuctx,
			      क्रमागत event_type_t event_type)
अणु
	ctx_sched_out(&cpuctx->ctx, cpuctx, event_type);
पूर्ण

अटल bool perf_less_group_idx(स्थिर व्योम *l, स्थिर व्योम *r)
अणु
	स्थिर काष्ठा perf_event *le = *(स्थिर काष्ठा perf_event **)l;
	स्थिर काष्ठा perf_event *re = *(स्थिर काष्ठा perf_event **)r;

	वापस le->group_index < re->group_index;
पूर्ण

अटल व्योम swap_ptr(व्योम *l, व्योम *r)
अणु
	व्योम **lp = l, **rp = r;

	swap(*lp, *rp);
पूर्ण

अटल स्थिर काष्ठा min_heap_callbacks perf_min_heap = अणु
	.elem_size = माप(काष्ठा perf_event *),
	.less = perf_less_group_idx,
	.swp = swap_ptr,
पूर्ण;

अटल व्योम __heap_add(काष्ठा min_heap *heap, काष्ठा perf_event *event)
अणु
	काष्ठा perf_event **itrs = heap->data;

	अगर (event) अणु
		itrs[heap->nr] = event;
		heap->nr++;
	पूर्ण
पूर्ण

अटल noअंतरभूत पूर्णांक visit_groups_merge(काष्ठा perf_cpu_context *cpuctx,
				काष्ठा perf_event_groups *groups, पूर्णांक cpu,
				पूर्णांक (*func)(काष्ठा perf_event *, व्योम *),
				व्योम *data)
अणु
#अगर_घोषित CONFIG_CGROUP_PERF
	काष्ठा cgroup_subsys_state *css = शून्य;
#पूर्ण_अगर
	/* Space क्रम per CPU and/or any CPU event iterators. */
	काष्ठा perf_event *itrs[2];
	काष्ठा min_heap event_heap;
	काष्ठा perf_event **evt;
	पूर्णांक ret;

	अगर (cpuctx) अणु
		event_heap = (काष्ठा min_heap)अणु
			.data = cpuctx->heap,
			.nr = 0,
			.size = cpuctx->heap_size,
		पूर्ण;

		lockdep_निश्चित_held(&cpuctx->ctx.lock);

#अगर_घोषित CONFIG_CGROUP_PERF
		अगर (cpuctx->cgrp)
			css = &cpuctx->cgrp->css;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		event_heap = (काष्ठा min_heap)अणु
			.data = itrs,
			.nr = 0,
			.size = ARRAY_SIZE(itrs),
		पूर्ण;
		/* Events not within a CPU context may be on any CPU. */
		__heap_add(&event_heap, perf_event_groups_first(groups, -1, शून्य));
	पूर्ण
	evt = event_heap.data;

	__heap_add(&event_heap, perf_event_groups_first(groups, cpu, शून्य));

#अगर_घोषित CONFIG_CGROUP_PERF
	क्रम (; css; css = css->parent)
		__heap_add(&event_heap, perf_event_groups_first(groups, cpu, css->cgroup));
#पूर्ण_अगर

	min_heapअगरy_all(&event_heap, &perf_min_heap);

	जबतक (event_heap.nr) अणु
		ret = func(*evt, data);
		अगर (ret)
			वापस ret;

		*evt = perf_event_groups_next(*evt);
		अगर (*evt)
			min_heapअगरy(&event_heap, 0, &perf_min_heap);
		अन्यथा
			min_heap_pop(&event_heap, &perf_min_heap);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक merge_sched_in(काष्ठा perf_event *event, व्योम *data)
अणु
	काष्ठा perf_event_context *ctx = event->ctx;
	काष्ठा perf_cpu_context *cpuctx = __get_cpu_context(ctx);
	पूर्णांक *can_add_hw = data;

	अगर (event->state <= PERF_EVENT_STATE_OFF)
		वापस 0;

	अगर (!event_filter_match(event))
		वापस 0;

	अगर (group_can_go_on(event, cpuctx, *can_add_hw)) अणु
		अगर (!group_sched_in(event, cpuctx, ctx))
			list_add_tail(&event->active_list, get_event_list(event));
	पूर्ण

	अगर (event->state == PERF_EVENT_STATE_INACTIVE) अणु
		अगर (event->attr.pinned) अणु
			perf_cgroup_event_disable(event, ctx);
			perf_event_set_state(event, PERF_EVENT_STATE_ERROR);
		पूर्ण

		*can_add_hw = 0;
		ctx->rotate_necessary = 1;
		perf_mux_hrसमयr_restart(cpuctx);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
ctx_pinned_sched_in(काष्ठा perf_event_context *ctx,
		    काष्ठा perf_cpu_context *cpuctx)
अणु
	पूर्णांक can_add_hw = 1;

	अगर (ctx != &cpuctx->ctx)
		cpuctx = शून्य;

	visit_groups_merge(cpuctx, &ctx->pinned_groups,
			   smp_processor_id(),
			   merge_sched_in, &can_add_hw);
पूर्ण

अटल व्योम
ctx_flexible_sched_in(काष्ठा perf_event_context *ctx,
		      काष्ठा perf_cpu_context *cpuctx)
अणु
	पूर्णांक can_add_hw = 1;

	अगर (ctx != &cpuctx->ctx)
		cpuctx = शून्य;

	visit_groups_merge(cpuctx, &ctx->flexible_groups,
			   smp_processor_id(),
			   merge_sched_in, &can_add_hw);
पूर्ण

अटल व्योम
ctx_sched_in(काष्ठा perf_event_context *ctx,
	     काष्ठा perf_cpu_context *cpuctx,
	     क्रमागत event_type_t event_type,
	     काष्ठा task_काष्ठा *task)
अणु
	पूर्णांक is_active = ctx->is_active;
	u64 now;

	lockdep_निश्चित_held(&ctx->lock);

	अगर (likely(!ctx->nr_events))
		वापस;

	ctx->is_active |= (event_type | EVENT_TIME);
	अगर (ctx->task) अणु
		अगर (!is_active)
			cpuctx->task_ctx = ctx;
		अन्यथा
			WARN_ON_ONCE(cpuctx->task_ctx != ctx);
	पूर्ण

	is_active ^= ctx->is_active; /* changed bits */

	अगर (is_active & EVENT_TIME) अणु
		/* start ctx समय */
		now = perf_घड़ी();
		ctx->बारtamp = now;
		perf_cgroup_set_बारtamp(task, ctx);
	पूर्ण

	/*
	 * First go through the list and put on any pinned groups
	 * in order to give them the best chance of going on.
	 */
	अगर (is_active & EVENT_PINNED)
		ctx_pinned_sched_in(ctx, cpuctx);

	/* Then walk through the lower prio flexible groups */
	अगर (is_active & EVENT_FLEXIBLE)
		ctx_flexible_sched_in(ctx, cpuctx);
पूर्ण

अटल व्योम cpu_ctx_sched_in(काष्ठा perf_cpu_context *cpuctx,
			     क्रमागत event_type_t event_type,
			     काष्ठा task_काष्ठा *task)
अणु
	काष्ठा perf_event_context *ctx = &cpuctx->ctx;

	ctx_sched_in(ctx, cpuctx, event_type, task);
पूर्ण

अटल व्योम perf_event_context_sched_in(काष्ठा perf_event_context *ctx,
					काष्ठा task_काष्ठा *task)
अणु
	काष्ठा perf_cpu_context *cpuctx;
	काष्ठा pmu *pmu = ctx->pmu;

	cpuctx = __get_cpu_context(ctx);
	अगर (cpuctx->task_ctx == ctx) अणु
		अगर (cpuctx->sched_cb_usage)
			__perf_pmu_sched_task(cpuctx, true);
		वापस;
	पूर्ण

	perf_ctx_lock(cpuctx, ctx);
	/*
	 * We must check ctx->nr_events जबतक holding ctx->lock, such
	 * that we serialize against perf_install_in_context().
	 */
	अगर (!ctx->nr_events)
		जाओ unlock;

	perf_pmu_disable(pmu);
	/*
	 * We want to keep the following priority order:
	 * cpu pinned (that करोn't need to move), task pinned,
	 * cpu flexible, task flexible.
	 *
	 * However, अगर task's ctx is not carrying any pinned
	 * events, no need to flip the cpuctx's events around.
	 */
	अगर (!RB_EMPTY_ROOT(&ctx->pinned_groups.tree))
		cpu_ctx_sched_out(cpuctx, EVENT_FLEXIBLE);
	perf_event_sched_in(cpuctx, ctx, task);

	अगर (cpuctx->sched_cb_usage && pmu->sched_task)
		pmu->sched_task(cpuctx->task_ctx, true);

	perf_pmu_enable(pmu);

unlock:
	perf_ctx_unlock(cpuctx, ctx);
पूर्ण

/*
 * Called from scheduler to add the events of the current task
 * with पूर्णांकerrupts disabled.
 *
 * We restore the event value and then enable it.
 *
 * This करोes not protect us against NMI, but enable()
 * sets the enabled bit in the control field of event _beक्रमe_
 * accessing the event control रेजिस्टर. If a NMI hits, then it will
 * keep the event running.
 */
व्योम __perf_event_task_sched_in(काष्ठा task_काष्ठा *prev,
				काष्ठा task_काष्ठा *task)
अणु
	काष्ठा perf_event_context *ctx;
	पूर्णांक ctxn;

	/*
	 * If cgroup events exist on this CPU, then we need to check अगर we have
	 * to चयन in PMU state; cgroup event are प्रणाली-wide mode only.
	 *
	 * Since cgroup events are CPU events, we must schedule these in beक्रमe
	 * we schedule in the task events.
	 */
	अगर (atomic_पढ़ो(this_cpu_ptr(&perf_cgroup_events)))
		perf_cgroup_sched_in(prev, task);

	क्रम_each_task_context_nr(ctxn) अणु
		ctx = task->perf_event_ctxp[ctxn];
		अगर (likely(!ctx))
			जारी;

		perf_event_context_sched_in(ctx, task);
	पूर्ण

	अगर (atomic_पढ़ो(&nr_चयन_events))
		perf_event_चयन(task, prev, true);

	अगर (__this_cpu_पढ़ो(perf_sched_cb_usages))
		perf_pmu_sched_task(prev, task, true);
पूर्ण

अटल u64 perf_calculate_period(काष्ठा perf_event *event, u64 nsec, u64 count)
अणु
	u64 frequency = event->attr.sample_freq;
	u64 sec = NSEC_PER_SEC;
	u64 भागisor, भागidend;

	पूर्णांक count_fls, nsec_fls, frequency_fls, sec_fls;

	count_fls = fls64(count);
	nsec_fls = fls64(nsec);
	frequency_fls = fls64(frequency);
	sec_fls = 30;

	/*
	 * We got @count in @nsec, with a target of sample_freq HZ
	 * the target period becomes:
	 *
	 *             @count * 10^9
	 * period = -------------------
	 *          @nsec * sample_freq
	 *
	 */

	/*
	 * Reduce accuracy by one bit such that @a and @b converge
	 * to a similar magnitude.
	 */
#घोषणा REDUCE_FLS(a, b)		\
करो अणु					\
	अगर (a##_fls > b##_fls) अणु	\
		a >>= 1;		\
		a##_fls--;		\
	पूर्ण अन्यथा अणु			\
		b >>= 1;		\
		b##_fls--;		\
	पूर्ण				\
पूर्ण जबतक (0)

	/*
	 * Reduce accuracy until either term fits in a u64, then proceed with
	 * the other, so that finally we can करो a u64/u64 भागision.
	 */
	जबतक (count_fls + sec_fls > 64 && nsec_fls + frequency_fls > 64) अणु
		REDUCE_FLS(nsec, frequency);
		REDUCE_FLS(sec, count);
	पूर्ण

	अगर (count_fls + sec_fls > 64) अणु
		भागisor = nsec * frequency;

		जबतक (count_fls + sec_fls > 64) अणु
			REDUCE_FLS(count, sec);
			भागisor >>= 1;
		पूर्ण

		भागidend = count * sec;
	पूर्ण अन्यथा अणु
		भागidend = count * sec;

		जबतक (nsec_fls + frequency_fls > 64) अणु
			REDUCE_FLS(nsec, frequency);
			भागidend >>= 1;
		पूर्ण

		भागisor = nsec * frequency;
	पूर्ण

	अगर (!भागisor)
		वापस भागidend;

	वापस भाग64_u64(भागidend, भागisor);
पूर्ण

अटल DEFINE_PER_CPU(पूर्णांक, perf_throttled_count);
अटल DEFINE_PER_CPU(u64, perf_throttled_seq);

अटल व्योम perf_adjust_period(काष्ठा perf_event *event, u64 nsec, u64 count, bool disable)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	s64 period, sample_period;
	s64 delta;

	period = perf_calculate_period(event, nsec, count);

	delta = (s64)(period - hwc->sample_period);
	delta = (delta + 7) / 8; /* low pass filter */

	sample_period = hwc->sample_period + delta;

	अगर (!sample_period)
		sample_period = 1;

	hwc->sample_period = sample_period;

	अगर (local64_पढ़ो(&hwc->period_left) > 8*sample_period) अणु
		अगर (disable)
			event->pmu->stop(event, PERF_EF_UPDATE);

		local64_set(&hwc->period_left, 0);

		अगर (disable)
			event->pmu->start(event, PERF_EF_RELOAD);
	पूर्ण
पूर्ण

/*
 * combine freq adjusपंचांगent with unthrottling to aव्योम two passes over the
 * events. At the same समय, make sure, having freq events करोes not change
 * the rate of unthrottling as that would पूर्णांकroduce bias.
 */
अटल व्योम perf_adjust_freq_unthr_context(काष्ठा perf_event_context *ctx,
					   पूर्णांक needs_unthr)
अणु
	काष्ठा perf_event *event;
	काष्ठा hw_perf_event *hwc;
	u64 now, period = TICK_NSEC;
	s64 delta;

	/*
	 * only need to iterate over all events अगरf:
	 * - context have events in frequency mode (needs freq adjust)
	 * - there are events to unthrottle on this cpu
	 */
	अगर (!(ctx->nr_freq || needs_unthr))
		वापस;

	raw_spin_lock(&ctx->lock);
	perf_pmu_disable(ctx->pmu);

	list_क्रम_each_entry_rcu(event, &ctx->event_list, event_entry) अणु
		अगर (event->state != PERF_EVENT_STATE_ACTIVE)
			जारी;

		अगर (!event_filter_match(event))
			जारी;

		perf_pmu_disable(event->pmu);

		hwc = &event->hw;

		अगर (hwc->पूर्णांकerrupts == MAX_INTERRUPTS) अणु
			hwc->पूर्णांकerrupts = 0;
			perf_log_throttle(event, 1);
			event->pmu->start(event, 0);
		पूर्ण

		अगर (!event->attr.freq || !event->attr.sample_freq)
			जाओ next;

		/*
		 * stop the event and update event->count
		 */
		event->pmu->stop(event, PERF_EF_UPDATE);

		now = local64_पढ़ो(&event->count);
		delta = now - hwc->freq_count_stamp;
		hwc->freq_count_stamp = now;

		/*
		 * restart the event
		 * reload only अगर value has changed
		 * we have stopped the event so tell that
		 * to perf_adjust_period() to aव्योम stopping it
		 * twice.
		 */
		अगर (delta > 0)
			perf_adjust_period(event, period, delta, false);

		event->pmu->start(event, delta > 0 ? PERF_EF_RELOAD : 0);
	next:
		perf_pmu_enable(event->pmu);
	पूर्ण

	perf_pmu_enable(ctx->pmu);
	raw_spin_unlock(&ctx->lock);
पूर्ण

/*
 * Move @event to the tail of the @ctx's elegible events.
 */
अटल व्योम rotate_ctx(काष्ठा perf_event_context *ctx, काष्ठा perf_event *event)
अणु
	/*
	 * Rotate the first entry last of non-pinned groups. Rotation might be
	 * disabled by the inheritance code.
	 */
	अगर (ctx->rotate_disable)
		वापस;

	perf_event_groups_delete(&ctx->flexible_groups, event);
	perf_event_groups_insert(&ctx->flexible_groups, event);
पूर्ण

/* pick an event from the flexible_groups to rotate */
अटल अंतरभूत काष्ठा perf_event *
ctx_event_to_rotate(काष्ठा perf_event_context *ctx)
अणु
	काष्ठा perf_event *event;

	/* pick the first active flexible event */
	event = list_first_entry_or_null(&ctx->flexible_active,
					 काष्ठा perf_event, active_list);

	/* अगर no active flexible event, pick the first event */
	अगर (!event) अणु
		event = rb_entry_safe(rb_first(&ctx->flexible_groups.tree),
				      typeof(*event), group_node);
	पूर्ण

	/*
	 * Unconditionally clear rotate_necessary; अगर ctx_flexible_sched_in()
	 * finds there are unschedulable events, it will set it again.
	 */
	ctx->rotate_necessary = 0;

	वापस event;
पूर्ण

अटल bool perf_rotate_context(काष्ठा perf_cpu_context *cpuctx)
अणु
	काष्ठा perf_event *cpu_event = शून्य, *task_event = शून्य;
	काष्ठा perf_event_context *task_ctx = शून्य;
	पूर्णांक cpu_rotate, task_rotate;

	/*
	 * Since we run this from IRQ context, nobody can install new
	 * events, thus the event count values are stable.
	 */

	cpu_rotate = cpuctx->ctx.rotate_necessary;
	task_ctx = cpuctx->task_ctx;
	task_rotate = task_ctx ? task_ctx->rotate_necessary : 0;

	अगर (!(cpu_rotate || task_rotate))
		वापस false;

	perf_ctx_lock(cpuctx, cpuctx->task_ctx);
	perf_pmu_disable(cpuctx->ctx.pmu);

	अगर (task_rotate)
		task_event = ctx_event_to_rotate(task_ctx);
	अगर (cpu_rotate)
		cpu_event = ctx_event_to_rotate(&cpuctx->ctx);

	/*
	 * As per the order given at ctx_resched() first 'pop' task flexible
	 * and then, अगर needed CPU flexible.
	 */
	अगर (task_event || (task_ctx && cpu_event))
		ctx_sched_out(task_ctx, cpuctx, EVENT_FLEXIBLE);
	अगर (cpu_event)
		cpu_ctx_sched_out(cpuctx, EVENT_FLEXIBLE);

	अगर (task_event)
		rotate_ctx(task_ctx, task_event);
	अगर (cpu_event)
		rotate_ctx(&cpuctx->ctx, cpu_event);

	perf_event_sched_in(cpuctx, task_ctx, current);

	perf_pmu_enable(cpuctx->ctx.pmu);
	perf_ctx_unlock(cpuctx, cpuctx->task_ctx);

	वापस true;
पूर्ण

व्योम perf_event_task_tick(व्योम)
अणु
	काष्ठा list_head *head = this_cpu_ptr(&active_ctx_list);
	काष्ठा perf_event_context *ctx, *पंचांगp;
	पूर्णांक throttled;

	lockdep_निश्चित_irqs_disabled();

	__this_cpu_inc(perf_throttled_seq);
	throttled = __this_cpu_xchg(perf_throttled_count, 0);
	tick_dep_clear_cpu(smp_processor_id(), TICK_DEP_BIT_PERF_EVENTS);

	list_क्रम_each_entry_safe(ctx, पंचांगp, head, active_ctx_list)
		perf_adjust_freq_unthr_context(ctx, throttled);
पूर्ण

अटल पूर्णांक event_enable_on_exec(काष्ठा perf_event *event,
				काष्ठा perf_event_context *ctx)
अणु
	अगर (!event->attr.enable_on_exec)
		वापस 0;

	event->attr.enable_on_exec = 0;
	अगर (event->state >= PERF_EVENT_STATE_INACTIVE)
		वापस 0;

	perf_event_set_state(event, PERF_EVENT_STATE_INACTIVE);

	वापस 1;
पूर्ण

/*
 * Enable all of a task's events that have been marked enable-on-exec.
 * This expects task == current.
 */
अटल व्योम perf_event_enable_on_exec(पूर्णांक ctxn)
अणु
	काष्ठा perf_event_context *ctx, *clone_ctx = शून्य;
	क्रमागत event_type_t event_type = 0;
	काष्ठा perf_cpu_context *cpuctx;
	काष्ठा perf_event *event;
	अचिन्हित दीर्घ flags;
	पूर्णांक enabled = 0;

	local_irq_save(flags);
	ctx = current->perf_event_ctxp[ctxn];
	अगर (!ctx || !ctx->nr_events)
		जाओ out;

	cpuctx = __get_cpu_context(ctx);
	perf_ctx_lock(cpuctx, ctx);
	ctx_sched_out(ctx, cpuctx, EVENT_TIME);
	list_क्रम_each_entry(event, &ctx->event_list, event_entry) अणु
		enabled |= event_enable_on_exec(event, ctx);
		event_type |= get_event_type(event);
	पूर्ण

	/*
	 * Unclone and reschedule this context अगर we enabled any event.
	 */
	अगर (enabled) अणु
		clone_ctx = unclone_ctx(ctx);
		ctx_resched(cpuctx, ctx, event_type);
	पूर्ण अन्यथा अणु
		ctx_sched_in(ctx, cpuctx, EVENT_TIME, current);
	पूर्ण
	perf_ctx_unlock(cpuctx, ctx);

out:
	local_irq_restore(flags);

	अगर (clone_ctx)
		put_ctx(clone_ctx);
पूर्ण

अटल व्योम perf_हटाओ_from_owner(काष्ठा perf_event *event);
अटल व्योम perf_event_निकास_event(काष्ठा perf_event *event,
				  काष्ठा perf_event_context *ctx);

/*
 * Removes all events from the current task that have been marked
 * हटाओ-on-exec, and feeds their values back to parent events.
 */
अटल व्योम perf_event_हटाओ_on_exec(पूर्णांक ctxn)
अणु
	काष्ठा perf_event_context *ctx, *clone_ctx = शून्य;
	काष्ठा perf_event *event, *next;
	LIST_HEAD(मुक्त_list);
	अचिन्हित दीर्घ flags;
	bool modअगरied = false;

	ctx = perf_pin_task_context(current, ctxn);
	अगर (!ctx)
		वापस;

	mutex_lock(&ctx->mutex);

	अगर (WARN_ON_ONCE(ctx->task != current))
		जाओ unlock;

	list_क्रम_each_entry_safe(event, next, &ctx->event_list, event_entry) अणु
		अगर (!event->attr.हटाओ_on_exec)
			जारी;

		अगर (!is_kernel_event(event))
			perf_हटाओ_from_owner(event);

		modअगरied = true;

		perf_event_निकास_event(event, ctx);
	पूर्ण

	raw_spin_lock_irqsave(&ctx->lock, flags);
	अगर (modअगरied)
		clone_ctx = unclone_ctx(ctx);
	--ctx->pin_count;
	raw_spin_unlock_irqrestore(&ctx->lock, flags);

unlock:
	mutex_unlock(&ctx->mutex);

	put_ctx(ctx);
	अगर (clone_ctx)
		put_ctx(clone_ctx);
पूर्ण

काष्ठा perf_पढ़ो_data अणु
	काष्ठा perf_event *event;
	bool group;
	पूर्णांक ret;
पूर्ण;

अटल पूर्णांक __perf_event_पढ़ो_cpu(काष्ठा perf_event *event, पूर्णांक event_cpu)
अणु
	u16 local_pkg, event_pkg;

	अगर (event->group_caps & PERF_EV_CAP_READ_ACTIVE_PKG) अणु
		पूर्णांक local_cpu = smp_processor_id();

		event_pkg = topology_physical_package_id(event_cpu);
		local_pkg = topology_physical_package_id(local_cpu);

		अगर (event_pkg == local_pkg)
			वापस local_cpu;
	पूर्ण

	वापस event_cpu;
पूर्ण

/*
 * Cross CPU call to पढ़ो the hardware event
 */
अटल व्योम __perf_event_पढ़ो(व्योम *info)
अणु
	काष्ठा perf_पढ़ो_data *data = info;
	काष्ठा perf_event *sub, *event = data->event;
	काष्ठा perf_event_context *ctx = event->ctx;
	काष्ठा perf_cpu_context *cpuctx = __get_cpu_context(ctx);
	काष्ठा pmu *pmu = event->pmu;

	/*
	 * If this is a task context, we need to check whether it is
	 * the current task context of this cpu.  If not it has been
	 * scheduled out beक्रमe the smp call arrived.  In that हाल
	 * event->count would have been updated to a recent sample
	 * when the event was scheduled out.
	 */
	अगर (ctx->task && cpuctx->task_ctx != ctx)
		वापस;

	raw_spin_lock(&ctx->lock);
	अगर (ctx->is_active & EVENT_TIME) अणु
		update_context_समय(ctx);
		update_cgrp_समय_from_event(event);
	पूर्ण

	perf_event_update_समय(event);
	अगर (data->group)
		perf_event_update_sibling_समय(event);

	अगर (event->state != PERF_EVENT_STATE_ACTIVE)
		जाओ unlock;

	अगर (!data->group) अणु
		pmu->पढ़ो(event);
		data->ret = 0;
		जाओ unlock;
	पूर्ण

	pmu->start_txn(pmu, PERF_PMU_TXN_READ);

	pmu->पढ़ो(event);

	क्रम_each_sibling_event(sub, event) अणु
		अगर (sub->state == PERF_EVENT_STATE_ACTIVE) अणु
			/*
			 * Use sibling's PMU rather than @event's since
			 * sibling could be on dअगरferent (eg: software) PMU.
			 */
			sub->pmu->पढ़ो(sub);
		पूर्ण
	पूर्ण

	data->ret = pmu->commit_txn(pmu);

unlock:
	raw_spin_unlock(&ctx->lock);
पूर्ण

अटल अंतरभूत u64 perf_event_count(काष्ठा perf_event *event)
अणु
	वापस local64_पढ़ो(&event->count) + atomic64_पढ़ो(&event->child_count);
पूर्ण

/*
 * NMI-safe method to पढ़ो a local event, that is an event that
 * is:
 *   - either क्रम the current task, or क्रम this CPU
 *   - करोes not have inherit set, क्रम inherited task events
 *     will not be local and we cannot पढ़ो them atomically
 *   - must not have a pmu::count method
 */
पूर्णांक perf_event_पढ़ो_local(काष्ठा perf_event *event, u64 *value,
			  u64 *enabled, u64 *running)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	/*
	 * Disabling पूर्णांकerrupts aव्योमs all counter scheduling (context
	 * चयनes, समयr based rotation and IPIs).
	 */
	local_irq_save(flags);

	/*
	 * It must not be an event with inherit set, we cannot पढ़ो
	 * all child counters from atomic context.
	 */
	अगर (event->attr.inherit) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	/* If this is a per-task event, it must be क्रम current */
	अगर ((event->attach_state & PERF_ATTACH_TASK) &&
	    event->hw.target != current) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* If this is a per-CPU event, it must be क्रम this CPU */
	अगर (!(event->attach_state & PERF_ATTACH_TASK) &&
	    event->cpu != smp_processor_id()) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* If this is a pinned event it must be running on this CPU */
	अगर (event->attr.pinned && event->oncpu != smp_processor_id()) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	/*
	 * If the event is currently on this CPU, its either a per-task event,
	 * or local to this CPU. Furthermore it means its ACTIVE (otherwise
	 * oncpu == -1).
	 */
	अगर (event->oncpu == smp_processor_id())
		event->pmu->पढ़ो(event);

	*value = local64_पढ़ो(&event->count);
	अगर (enabled || running) अणु
		u64 now = event->shaकरोw_ctx_समय + perf_घड़ी();
		u64 __enabled, __running;

		__perf_update_बार(event, now, &__enabled, &__running);
		अगर (enabled)
			*enabled = __enabled;
		अगर (running)
			*running = __running;
	पूर्ण
out:
	local_irq_restore(flags);

	वापस ret;
पूर्ण

अटल पूर्णांक perf_event_पढ़ो(काष्ठा perf_event *event, bool group)
अणु
	क्रमागत perf_event_state state = READ_ONCE(event->state);
	पूर्णांक event_cpu, ret = 0;

	/*
	 * If event is enabled and currently active on a CPU, update the
	 * value in the event काष्ठाure:
	 */
again:
	अगर (state == PERF_EVENT_STATE_ACTIVE) अणु
		काष्ठा perf_पढ़ो_data data;

		/*
		 * Orders the ->state and ->oncpu loads such that अगर we see
		 * ACTIVE we must also see the right ->oncpu.
		 *
		 * Matches the smp_wmb() from event_sched_in().
		 */
		smp_rmb();

		event_cpu = READ_ONCE(event->oncpu);
		अगर ((अचिन्हित)event_cpu >= nr_cpu_ids)
			वापस 0;

		data = (काष्ठा perf_पढ़ो_data)अणु
			.event = event,
			.group = group,
			.ret = 0,
		पूर्ण;

		preempt_disable();
		event_cpu = __perf_event_पढ़ो_cpu(event, event_cpu);

		/*
		 * Purposely ignore the smp_call_function_single() वापस
		 * value.
		 *
		 * If event_cpu isn't a valid CPU it means the event got
		 * scheduled out and that will have updated the event count.
		 *
		 * Thereक्रमe, either way, we'll have an up-to-date event count
		 * after this.
		 */
		(व्योम)smp_call_function_single(event_cpu, __perf_event_पढ़ो, &data, 1);
		preempt_enable();
		ret = data.ret;

	पूर्ण अन्यथा अगर (state == PERF_EVENT_STATE_INACTIVE) अणु
		काष्ठा perf_event_context *ctx = event->ctx;
		अचिन्हित दीर्घ flags;

		raw_spin_lock_irqsave(&ctx->lock, flags);
		state = event->state;
		अगर (state != PERF_EVENT_STATE_INACTIVE) अणु
			raw_spin_unlock_irqrestore(&ctx->lock, flags);
			जाओ again;
		पूर्ण

		/*
		 * May पढ़ो जबतक context is not active (e.g., thपढ़ो is
		 * blocked), in that हाल we cannot update context समय
		 */
		अगर (ctx->is_active & EVENT_TIME) अणु
			update_context_समय(ctx);
			update_cgrp_समय_from_event(event);
		पूर्ण

		perf_event_update_समय(event);
		अगर (group)
			perf_event_update_sibling_समय(event);
		raw_spin_unlock_irqrestore(&ctx->lock, flags);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Initialize the perf_event context in a task_काष्ठा:
 */
अटल व्योम __perf_event_init_context(काष्ठा perf_event_context *ctx)
अणु
	raw_spin_lock_init(&ctx->lock);
	mutex_init(&ctx->mutex);
	INIT_LIST_HEAD(&ctx->active_ctx_list);
	perf_event_groups_init(&ctx->pinned_groups);
	perf_event_groups_init(&ctx->flexible_groups);
	INIT_LIST_HEAD(&ctx->event_list);
	INIT_LIST_HEAD(&ctx->pinned_active);
	INIT_LIST_HEAD(&ctx->flexible_active);
	refcount_set(&ctx->refcount, 1);
पूर्ण

अटल काष्ठा perf_event_context *
alloc_perf_context(काष्ठा pmu *pmu, काष्ठा task_काष्ठा *task)
अणु
	काष्ठा perf_event_context *ctx;

	ctx = kzalloc(माप(काष्ठा perf_event_context), GFP_KERNEL);
	अगर (!ctx)
		वापस शून्य;

	__perf_event_init_context(ctx);
	अगर (task)
		ctx->task = get_task_काष्ठा(task);
	ctx->pmu = pmu;

	वापस ctx;
पूर्ण

अटल काष्ठा task_काष्ठा *
find_lively_task_by_vpid(pid_t vpid)
अणु
	काष्ठा task_काष्ठा *task;

	rcu_पढ़ो_lock();
	अगर (!vpid)
		task = current;
	अन्यथा
		task = find_task_by_vpid(vpid);
	अगर (task)
		get_task_काष्ठा(task);
	rcu_पढ़ो_unlock();

	अगर (!task)
		वापस ERR_PTR(-ESRCH);

	वापस task;
पूर्ण

/*
 * Returns a matching context with refcount and pincount.
 */
अटल काष्ठा perf_event_context *
find_get_context(काष्ठा pmu *pmu, काष्ठा task_काष्ठा *task,
		काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_context *ctx, *clone_ctx = शून्य;
	काष्ठा perf_cpu_context *cpuctx;
	व्योम *task_ctx_data = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक ctxn, err;
	पूर्णांक cpu = event->cpu;

	अगर (!task) अणु
		/* Must be root to operate on a CPU event: */
		err = perf_allow_cpu(&event->attr);
		अगर (err)
			वापस ERR_PTR(err);

		cpuctx = per_cpu_ptr(pmu->pmu_cpu_context, cpu);
		ctx = &cpuctx->ctx;
		get_ctx(ctx);
		raw_spin_lock_irqsave(&ctx->lock, flags);
		++ctx->pin_count;
		raw_spin_unlock_irqrestore(&ctx->lock, flags);

		वापस ctx;
	पूर्ण

	err = -EINVAL;
	ctxn = pmu->task_ctx_nr;
	अगर (ctxn < 0)
		जाओ errout;

	अगर (event->attach_state & PERF_ATTACH_TASK_DATA) अणु
		task_ctx_data = alloc_task_ctx_data(pmu);
		अगर (!task_ctx_data) अणु
			err = -ENOMEM;
			जाओ errout;
		पूर्ण
	पूर्ण

retry:
	ctx = perf_lock_task_context(task, ctxn, &flags);
	अगर (ctx) अणु
		clone_ctx = unclone_ctx(ctx);
		++ctx->pin_count;

		अगर (task_ctx_data && !ctx->task_ctx_data) अणु
			ctx->task_ctx_data = task_ctx_data;
			task_ctx_data = शून्य;
		पूर्ण
		raw_spin_unlock_irqrestore(&ctx->lock, flags);

		अगर (clone_ctx)
			put_ctx(clone_ctx);
	पूर्ण अन्यथा अणु
		ctx = alloc_perf_context(pmu, task);
		err = -ENOMEM;
		अगर (!ctx)
			जाओ errout;

		अगर (task_ctx_data) अणु
			ctx->task_ctx_data = task_ctx_data;
			task_ctx_data = शून्य;
		पूर्ण

		err = 0;
		mutex_lock(&task->perf_event_mutex);
		/*
		 * If it has alपढ़ोy passed perf_event_निकास_task().
		 * we must see PF_EXITING, it takes this mutex too.
		 */
		अगर (task->flags & PF_EXITING)
			err = -ESRCH;
		अन्यथा अगर (task->perf_event_ctxp[ctxn])
			err = -EAGAIN;
		अन्यथा अणु
			get_ctx(ctx);
			++ctx->pin_count;
			rcu_assign_poपूर्णांकer(task->perf_event_ctxp[ctxn], ctx);
		पूर्ण
		mutex_unlock(&task->perf_event_mutex);

		अगर (unlikely(err)) अणु
			put_ctx(ctx);

			अगर (err == -EAGAIN)
				जाओ retry;
			जाओ errout;
		पूर्ण
	पूर्ण

	मुक्त_task_ctx_data(pmu, task_ctx_data);
	वापस ctx;

errout:
	मुक्त_task_ctx_data(pmu, task_ctx_data);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम perf_event_मुक्त_filter(काष्ठा perf_event *event);
अटल व्योम perf_event_मुक्त_bpf_prog(काष्ठा perf_event *event);

अटल व्योम मुक्त_event_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा perf_event *event;

	event = container_of(head, काष्ठा perf_event, rcu_head);
	अगर (event->ns)
		put_pid_ns(event->ns);
	perf_event_मुक्त_filter(event);
	kmem_cache_मुक्त(perf_event_cache, event);
पूर्ण

अटल व्योम ring_buffer_attach(काष्ठा perf_event *event,
			       काष्ठा perf_buffer *rb);

अटल व्योम detach_sb_event(काष्ठा perf_event *event)
अणु
	काष्ठा pmu_event_list *pel = per_cpu_ptr(&pmu_sb_events, event->cpu);

	raw_spin_lock(&pel->lock);
	list_del_rcu(&event->sb_list);
	raw_spin_unlock(&pel->lock);
पूर्ण

अटल bool is_sb_event(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;

	अगर (event->parent)
		वापस false;

	अगर (event->attach_state & PERF_ATTACH_TASK)
		वापस false;

	अगर (attr->mmap || attr->mmap_data || attr->mmap2 ||
	    attr->comm || attr->comm_exec ||
	    attr->task || attr->ksymbol ||
	    attr->context_चयन || attr->text_poke ||
	    attr->bpf_event)
		वापस true;
	वापस false;
पूर्ण

अटल व्योम unaccount_pmu_sb_event(काष्ठा perf_event *event)
अणु
	अगर (is_sb_event(event))
		detach_sb_event(event);
पूर्ण

अटल व्योम unaccount_event_cpu(काष्ठा perf_event *event, पूर्णांक cpu)
अणु
	अगर (event->parent)
		वापस;

	अगर (is_cgroup_event(event))
		atomic_dec(&per_cpu(perf_cgroup_events, cpu));
पूर्ण

#अगर_घोषित CONFIG_NO_HZ_FULL
अटल DEFINE_SPINLOCK(nr_freq_lock);
#पूर्ण_अगर

अटल व्योम unaccount_freq_event_nohz(व्योम)
अणु
#अगर_घोषित CONFIG_NO_HZ_FULL
	spin_lock(&nr_freq_lock);
	अगर (atomic_dec_and_test(&nr_freq_events))
		tick_nohz_dep_clear(TICK_DEP_BIT_PERF_EVENTS);
	spin_unlock(&nr_freq_lock);
#पूर्ण_अगर
पूर्ण

अटल व्योम unaccount_freq_event(व्योम)
अणु
	अगर (tick_nohz_full_enabled())
		unaccount_freq_event_nohz();
	अन्यथा
		atomic_dec(&nr_freq_events);
पूर्ण

अटल व्योम unaccount_event(काष्ठा perf_event *event)
अणु
	bool dec = false;

	अगर (event->parent)
		वापस;

	अगर (event->attach_state & (PERF_ATTACH_TASK | PERF_ATTACH_SCHED_CB))
		dec = true;
	अगर (event->attr.mmap || event->attr.mmap_data)
		atomic_dec(&nr_mmap_events);
	अगर (event->attr.build_id)
		atomic_dec(&nr_build_id_events);
	अगर (event->attr.comm)
		atomic_dec(&nr_comm_events);
	अगर (event->attr.namespaces)
		atomic_dec(&nr_namespaces_events);
	अगर (event->attr.cgroup)
		atomic_dec(&nr_cgroup_events);
	अगर (event->attr.task)
		atomic_dec(&nr_task_events);
	अगर (event->attr.freq)
		unaccount_freq_event();
	अगर (event->attr.context_चयन) अणु
		dec = true;
		atomic_dec(&nr_चयन_events);
	पूर्ण
	अगर (is_cgroup_event(event))
		dec = true;
	अगर (has_branch_stack(event))
		dec = true;
	अगर (event->attr.ksymbol)
		atomic_dec(&nr_ksymbol_events);
	अगर (event->attr.bpf_event)
		atomic_dec(&nr_bpf_events);
	अगर (event->attr.text_poke)
		atomic_dec(&nr_text_poke_events);

	अगर (dec) अणु
		अगर (!atomic_add_unless(&perf_sched_count, -1, 1))
			schedule_delayed_work(&perf_sched_work, HZ);
	पूर्ण

	unaccount_event_cpu(event, event->cpu);

	unaccount_pmu_sb_event(event);
पूर्ण

अटल व्योम perf_sched_delayed(काष्ठा work_काष्ठा *work)
अणु
	mutex_lock(&perf_sched_mutex);
	अगर (atomic_dec_and_test(&perf_sched_count))
		अटल_branch_disable(&perf_sched_events);
	mutex_unlock(&perf_sched_mutex);
पूर्ण

/*
 * The following implement mutual exclusion of events on "exclusive" pmus
 * (PERF_PMU_CAP_EXCLUSIVE). Such pmus can only have one event scheduled
 * at a समय, so we disallow creating events that might conflict, namely:
 *
 *  1) cpu-wide events in the presence of per-task events,
 *  2) per-task events in the presence of cpu-wide events,
 *  3) two matching events on the same context.
 *
 * The क्रमmer two हालs are handled in the allocation path (perf_event_alloc(),
 * _मुक्त_event()), the latter -- beक्रमe the first perf_install_in_context().
 */
अटल पूर्णांक exclusive_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा pmu *pmu = event->pmu;

	अगर (!is_exclusive_pmu(pmu))
		वापस 0;

	/*
	 * Prevent co-existence of per-task and cpu-wide events on the
	 * same exclusive pmu.
	 *
	 * Negative pmu::exclusive_cnt means there are cpu-wide
	 * events on this "exclusive" pmu, positive means there are
	 * per-task events.
	 *
	 * Since this is called in perf_event_alloc() path, event::ctx
	 * करोesn't exist yet; it is, however, safe to use PERF_ATTACH_TASK
	 * to mean "per-task event", because unlike other attach states it
	 * never माला_लो cleared.
	 */
	अगर (event->attach_state & PERF_ATTACH_TASK) अणु
		अगर (!atomic_inc_unless_negative(&pmu->exclusive_cnt))
			वापस -EBUSY;
	पूर्ण अन्यथा अणु
		अगर (!atomic_dec_unless_positive(&pmu->exclusive_cnt))
			वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम exclusive_event_destroy(काष्ठा perf_event *event)
अणु
	काष्ठा pmu *pmu = event->pmu;

	अगर (!is_exclusive_pmu(pmu))
		वापस;

	/* see comment in exclusive_event_init() */
	अगर (event->attach_state & PERF_ATTACH_TASK)
		atomic_dec(&pmu->exclusive_cnt);
	अन्यथा
		atomic_inc(&pmu->exclusive_cnt);
पूर्ण

अटल bool exclusive_event_match(काष्ठा perf_event *e1, काष्ठा perf_event *e2)
अणु
	अगर ((e1->pmu == e2->pmu) &&
	    (e1->cpu == e2->cpu ||
	     e1->cpu == -1 ||
	     e2->cpu == -1))
		वापस true;
	वापस false;
पूर्ण

अटल bool exclusive_event_installable(काष्ठा perf_event *event,
					काष्ठा perf_event_context *ctx)
अणु
	काष्ठा perf_event *iter_event;
	काष्ठा pmu *pmu = event->pmu;

	lockdep_निश्चित_held(&ctx->mutex);

	अगर (!is_exclusive_pmu(pmu))
		वापस true;

	list_क्रम_each_entry(iter_event, &ctx->event_list, event_entry) अणु
		अगर (exclusive_event_match(iter_event, event))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम perf_addr_filters_splice(काष्ठा perf_event *event,
				       काष्ठा list_head *head);

अटल व्योम _मुक्त_event(काष्ठा perf_event *event)
अणु
	irq_work_sync(&event->pending);

	unaccount_event(event);

	security_perf_event_मुक्त(event);

	अगर (event->rb) अणु
		/*
		 * Can happen when we बंद an event with re-directed output.
		 *
		 * Since we have a 0 refcount, perf_mmap_बंद() will skip
		 * over us; possibly making our ring_buffer_put() the last.
		 */
		mutex_lock(&event->mmap_mutex);
		ring_buffer_attach(event, शून्य);
		mutex_unlock(&event->mmap_mutex);
	पूर्ण

	अगर (is_cgroup_event(event))
		perf_detach_cgroup(event);

	अगर (!event->parent) अणु
		अगर (event->attr.sample_type & PERF_SAMPLE_CALLCHAIN)
			put_callchain_buffers();
	पूर्ण

	perf_event_मुक्त_bpf_prog(event);
	perf_addr_filters_splice(event, शून्य);
	kमुक्त(event->addr_filter_ranges);

	अगर (event->destroy)
		event->destroy(event);

	/*
	 * Must be after ->destroy(), due to uprobe_perf_बंद() using
	 * hw.target.
	 */
	अगर (event->hw.target)
		put_task_काष्ठा(event->hw.target);

	/*
	 * perf_event_मुक्त_task() relies on put_ctx() being 'last', in particular
	 * all task references must be cleaned up.
	 */
	अगर (event->ctx)
		put_ctx(event->ctx);

	exclusive_event_destroy(event);
	module_put(event->pmu->module);

	call_rcu(&event->rcu_head, मुक्त_event_rcu);
पूर्ण

/*
 * Used to मुक्त events which have a known refcount of 1, such as in error paths
 * where the event isn't exposed yet and inherited events.
 */
अटल व्योम मुक्त_event(काष्ठा perf_event *event)
अणु
	अगर (WARN(atomic_दीर्घ_cmpxchg(&event->refcount, 1, 0) != 1,
				"unexpected event refcount: %ld; ptr=%p\n",
				atomic_दीर्घ_पढ़ो(&event->refcount), event)) अणु
		/* leak to aव्योम use-after-मुक्त */
		वापस;
	पूर्ण

	_मुक्त_event(event);
पूर्ण

/*
 * Remove user event from the owner task.
 */
अटल व्योम perf_हटाओ_from_owner(काष्ठा perf_event *event)
अणु
	काष्ठा task_काष्ठा *owner;

	rcu_पढ़ो_lock();
	/*
	 * Matches the smp_store_release() in perf_event_निकास_task(). If we
	 * observe !owner it means the list deletion is complete and we can
	 * indeed मुक्त this event, otherwise we need to serialize on
	 * owner->perf_event_mutex.
	 */
	owner = READ_ONCE(event->owner);
	अगर (owner) अणु
		/*
		 * Since delayed_put_task_काष्ठा() also drops the last
		 * task reference we can safely take a new reference
		 * जबतक holding the rcu_पढ़ो_lock().
		 */
		get_task_काष्ठा(owner);
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (owner) अणु
		/*
		 * If we're here through perf_event_exit_task() we're alपढ़ोy
		 * holding ctx->mutex which would be an inversion wrt. the
		 * normal lock order.
		 *
		 * However we can safely take this lock because its the child
		 * ctx->mutex.
		 */
		mutex_lock_nested(&owner->perf_event_mutex, SINGLE_DEPTH_NESTING);

		/*
		 * We have to re-check the event->owner field, अगर it is cleared
		 * we raced with perf_event_निकास_task(), acquiring the mutex
		 * ensured they're करोne, and we can proceed with मुक्तing the
		 * event.
		 */
		अगर (event->owner) अणु
			list_del_init(&event->owner_entry);
			smp_store_release(&event->owner, शून्य);
		पूर्ण
		mutex_unlock(&owner->perf_event_mutex);
		put_task_काष्ठा(owner);
	पूर्ण
पूर्ण

अटल व्योम put_event(काष्ठा perf_event *event)
अणु
	अगर (!atomic_दीर्घ_dec_and_test(&event->refcount))
		वापस;

	_मुक्त_event(event);
पूर्ण

/*
 * Kill an event dead; जबतक event:refcount will preserve the event
 * object, it will not preserve its functionality. Once the last 'user'
 * gives up the object, we'll destroy the thing.
 */
पूर्णांक perf_event_release_kernel(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_context *ctx = event->ctx;
	काष्ठा perf_event *child, *पंचांगp;
	LIST_HEAD(मुक्त_list);

	/*
	 * If we got here through err_file: fput(event_file); we will not have
	 * attached to a context yet.
	 */
	अगर (!ctx) अणु
		WARN_ON_ONCE(event->attach_state &
				(PERF_ATTACH_CONTEXT|PERF_ATTACH_GROUP));
		जाओ no_ctx;
	पूर्ण

	अगर (!is_kernel_event(event))
		perf_हटाओ_from_owner(event);

	ctx = perf_event_ctx_lock(event);
	WARN_ON_ONCE(ctx->parent_ctx);
	perf_हटाओ_from_context(event, DETACH_GROUP);

	raw_spin_lock_irq(&ctx->lock);
	/*
	 * Mark this event as STATE_DEAD, there is no बाह्यal reference to it
	 * anymore.
	 *
	 * Anybody acquiring event->child_mutex after the below loop _must_
	 * also see this, most importantly inherit_event() which will aव्योम
	 * placing more children on the list.
	 *
	 * Thus this guarantees that we will in fact observe and समाप्त _ALL_
	 * child events.
	 */
	event->state = PERF_EVENT_STATE_DEAD;
	raw_spin_unlock_irq(&ctx->lock);

	perf_event_ctx_unlock(event, ctx);

again:
	mutex_lock(&event->child_mutex);
	list_क्रम_each_entry(child, &event->child_list, child_list) अणु

		/*
		 * Cannot change, child events are not migrated, see the
		 * comment with perf_event_ctx_lock_nested().
		 */
		ctx = READ_ONCE(child->ctx);
		/*
		 * Since child_mutex nests inside ctx::mutex, we must jump
		 * through hoops. We start by grabbing a reference on the ctx.
		 *
		 * Since the event cannot get मुक्तd जबतक we hold the
		 * child_mutex, the context must also exist and have a !0
		 * reference count.
		 */
		get_ctx(ctx);

		/*
		 * Now that we have a ctx ref, we can drop child_mutex, and
		 * acquire ctx::mutex without fear of it going away. Then we
		 * can re-acquire child_mutex.
		 */
		mutex_unlock(&event->child_mutex);
		mutex_lock(&ctx->mutex);
		mutex_lock(&event->child_mutex);

		/*
		 * Now that we hold ctx::mutex and child_mutex, revalidate our
		 * state, अगर child is still the first entry, it didn't get मुक्तd
		 * and we can जारी करोing so.
		 */
		पंचांगp = list_first_entry_or_null(&event->child_list,
					       काष्ठा perf_event, child_list);
		अगर (पंचांगp == child) अणु
			perf_हटाओ_from_context(child, DETACH_GROUP);
			list_move(&child->child_list, &मुक्त_list);
			/*
			 * This matches the refcount bump in inherit_event();
			 * this can't be the last reference.
			 */
			put_event(event);
		पूर्ण

		mutex_unlock(&event->child_mutex);
		mutex_unlock(&ctx->mutex);
		put_ctx(ctx);
		जाओ again;
	पूर्ण
	mutex_unlock(&event->child_mutex);

	list_क्रम_each_entry_safe(child, पंचांगp, &मुक्त_list, child_list) अणु
		व्योम *var = &child->ctx->refcount;

		list_del(&child->child_list);
		मुक्त_event(child);

		/*
		 * Wake any perf_event_मुक्त_task() रुकोing क्रम this event to be
		 * मुक्तd.
		 */
		smp_mb(); /* pairs with रुको_var_event() */
		wake_up_var(var);
	पूर्ण

no_ctx:
	put_event(event); /* Must be the 'last' reference */
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(perf_event_release_kernel);

/*
 * Called when the last reference to the file is gone.
 */
अटल पूर्णांक perf_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	perf_event_release_kernel(file->निजी_data);
	वापस 0;
पूर्ण

अटल u64 __perf_event_पढ़ो_value(काष्ठा perf_event *event, u64 *enabled, u64 *running)
अणु
	काष्ठा perf_event *child;
	u64 total = 0;

	*enabled = 0;
	*running = 0;

	mutex_lock(&event->child_mutex);

	(व्योम)perf_event_पढ़ो(event, false);
	total += perf_event_count(event);

	*enabled += event->total_समय_enabled +
			atomic64_पढ़ो(&event->child_total_समय_enabled);
	*running += event->total_समय_running +
			atomic64_पढ़ो(&event->child_total_समय_running);

	list_क्रम_each_entry(child, &event->child_list, child_list) अणु
		(व्योम)perf_event_पढ़ो(child, false);
		total += perf_event_count(child);
		*enabled += child->total_समय_enabled;
		*running += child->total_समय_running;
	पूर्ण
	mutex_unlock(&event->child_mutex);

	वापस total;
पूर्ण

u64 perf_event_पढ़ो_value(काष्ठा perf_event *event, u64 *enabled, u64 *running)
अणु
	काष्ठा perf_event_context *ctx;
	u64 count;

	ctx = perf_event_ctx_lock(event);
	count = __perf_event_पढ़ो_value(event, enabled, running);
	perf_event_ctx_unlock(event, ctx);

	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(perf_event_पढ़ो_value);

अटल पूर्णांक __perf_पढ़ो_group_add(काष्ठा perf_event *leader,
					u64 पढ़ो_क्रमmat, u64 *values)
अणु
	काष्ठा perf_event_context *ctx = leader->ctx;
	काष्ठा perf_event *sub;
	अचिन्हित दीर्घ flags;
	पूर्णांक n = 1; /* skip @nr */
	पूर्णांक ret;

	ret = perf_event_पढ़ो(leader, true);
	अगर (ret)
		वापस ret;

	raw_spin_lock_irqsave(&ctx->lock, flags);

	/*
	 * Since we co-schedule groups, अणुenabled,runningपूर्ण बार of siblings
	 * will be identical to those of the leader, so we only publish one
	 * set.
	 */
	अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_ENABLED) अणु
		values[n++] += leader->total_समय_enabled +
			atomic64_पढ़ो(&leader->child_total_समय_enabled);
	पूर्ण

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_RUNNING) अणु
		values[n++] += leader->total_समय_running +
			atomic64_पढ़ो(&leader->child_total_समय_running);
	पूर्ण

	/*
	 * Write अणुcount,idपूर्ण tuples क्रम every sibling.
	 */
	values[n++] += perf_event_count(leader);
	अगर (पढ़ो_क्रमmat & PERF_FORMAT_ID)
		values[n++] = primary_event_id(leader);

	क्रम_each_sibling_event(sub, leader) अणु
		values[n++] += perf_event_count(sub);
		अगर (पढ़ो_क्रमmat & PERF_FORMAT_ID)
			values[n++] = primary_event_id(sub);
	पूर्ण

	raw_spin_unlock_irqrestore(&ctx->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक perf_पढ़ो_group(काष्ठा perf_event *event,
				   u64 पढ़ो_क्रमmat, अक्षर __user *buf)
अणु
	काष्ठा perf_event *leader = event->group_leader, *child;
	काष्ठा perf_event_context *ctx = leader->ctx;
	पूर्णांक ret;
	u64 *values;

	lockdep_निश्चित_held(&ctx->mutex);

	values = kzalloc(event->पढ़ो_size, GFP_KERNEL);
	अगर (!values)
		वापस -ENOMEM;

	values[0] = 1 + leader->nr_siblings;

	/*
	 * By locking the child_mutex of the leader we effectively
	 * lock the child list of all siblings.. XXX explain how.
	 */
	mutex_lock(&leader->child_mutex);

	ret = __perf_पढ़ो_group_add(leader, पढ़ो_क्रमmat, values);
	अगर (ret)
		जाओ unlock;

	list_क्रम_each_entry(child, &leader->child_list, child_list) अणु
		ret = __perf_पढ़ो_group_add(child, पढ़ो_क्रमmat, values);
		अगर (ret)
			जाओ unlock;
	पूर्ण

	mutex_unlock(&leader->child_mutex);

	ret = event->पढ़ो_size;
	अगर (copy_to_user(buf, values, event->पढ़ो_size))
		ret = -EFAULT;
	जाओ out;

unlock:
	mutex_unlock(&leader->child_mutex);
out:
	kमुक्त(values);
	वापस ret;
पूर्ण

अटल पूर्णांक perf_पढ़ो_one(काष्ठा perf_event *event,
				 u64 पढ़ो_क्रमmat, अक्षर __user *buf)
अणु
	u64 enabled, running;
	u64 values[4];
	पूर्णांक n = 0;

	values[n++] = __perf_event_पढ़ो_value(event, &enabled, &running);
	अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_ENABLED)
		values[n++] = enabled;
	अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_RUNNING)
		values[n++] = running;
	अगर (पढ़ो_क्रमmat & PERF_FORMAT_ID)
		values[n++] = primary_event_id(event);

	अगर (copy_to_user(buf, values, n * माप(u64)))
		वापस -EFAULT;

	वापस n * माप(u64);
पूर्ण

अटल bool is_event_hup(काष्ठा perf_event *event)
अणु
	bool no_children;

	अगर (event->state > PERF_EVENT_STATE_EXIT)
		वापस false;

	mutex_lock(&event->child_mutex);
	no_children = list_empty(&event->child_list);
	mutex_unlock(&event->child_mutex);
	वापस no_children;
पूर्ण

/*
 * Read the perक्रमmance event - simple non blocking version क्रम now
 */
अटल sमाप_प्रकार
__perf_पढ़ो(काष्ठा perf_event *event, अक्षर __user *buf, माप_प्रकार count)
अणु
	u64 पढ़ो_क्रमmat = event->attr.पढ़ो_क्रमmat;
	पूर्णांक ret;

	/*
	 * Return end-of-file क्रम a पढ़ो on an event that is in
	 * error state (i.e. because it was pinned but it couldn't be
	 * scheduled on to the CPU at some poपूर्णांक).
	 */
	अगर (event->state == PERF_EVENT_STATE_ERROR)
		वापस 0;

	अगर (count < event->पढ़ो_size)
		वापस -ENOSPC;

	WARN_ON_ONCE(event->ctx->parent_ctx);
	अगर (पढ़ो_क्रमmat & PERF_FORMAT_GROUP)
		ret = perf_पढ़ो_group(event, पढ़ो_क्रमmat, buf);
	अन्यथा
		ret = perf_पढ़ो_one(event, पढ़ो_क्रमmat, buf);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
perf_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा perf_event *event = file->निजी_data;
	काष्ठा perf_event_context *ctx;
	पूर्णांक ret;

	ret = security_perf_event_पढ़ो(event);
	अगर (ret)
		वापस ret;

	ctx = perf_event_ctx_lock(event);
	ret = __perf_पढ़ो(event, buf, count);
	perf_event_ctx_unlock(event, ctx);

	वापस ret;
पूर्ण

अटल __poll_t perf_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा perf_event *event = file->निजी_data;
	काष्ठा perf_buffer *rb;
	__poll_t events = EPOLLHUP;

	poll_रुको(file, &event->रुकोq, रुको);

	अगर (is_event_hup(event))
		वापस events;

	/*
	 * Pin the event->rb by taking event->mmap_mutex; otherwise
	 * perf_event_set_output() can swizzle our rb and make us miss wakeups.
	 */
	mutex_lock(&event->mmap_mutex);
	rb = event->rb;
	अगर (rb)
		events = atomic_xchg(&rb->poll, 0);
	mutex_unlock(&event->mmap_mutex);
	वापस events;
पूर्ण

अटल व्योम _perf_event_reset(काष्ठा perf_event *event)
अणु
	(व्योम)perf_event_पढ़ो(event, false);
	local64_set(&event->count, 0);
	perf_event_update_userpage(event);
पूर्ण

/* Assume it's not an event with inherit set. */
u64 perf_event_छोड़ो(काष्ठा perf_event *event, bool reset)
अणु
	काष्ठा perf_event_context *ctx;
	u64 count;

	ctx = perf_event_ctx_lock(event);
	WARN_ON_ONCE(event->attr.inherit);
	_perf_event_disable(event);
	count = local64_पढ़ो(&event->count);
	अगर (reset)
		local64_set(&event->count, 0);
	perf_event_ctx_unlock(event, ctx);

	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(perf_event_छोड़ो);

/*
 * Holding the top-level event's child_mutex means that any
 * descendant process that has inherited this event will block
 * in perf_event_निकास_event() अगर it goes to निकास, thus satisfying the
 * task existence requirements of perf_event_enable/disable.
 */
अटल व्योम perf_event_क्रम_each_child(काष्ठा perf_event *event,
					व्योम (*func)(काष्ठा perf_event *))
अणु
	काष्ठा perf_event *child;

	WARN_ON_ONCE(event->ctx->parent_ctx);

	mutex_lock(&event->child_mutex);
	func(event);
	list_क्रम_each_entry(child, &event->child_list, child_list)
		func(child);
	mutex_unlock(&event->child_mutex);
पूर्ण

अटल व्योम perf_event_क्रम_each(काष्ठा perf_event *event,
				  व्योम (*func)(काष्ठा perf_event *))
अणु
	काष्ठा perf_event_context *ctx = event->ctx;
	काष्ठा perf_event *sibling;

	lockdep_निश्चित_held(&ctx->mutex);

	event = event->group_leader;

	perf_event_क्रम_each_child(event, func);
	क्रम_each_sibling_event(sibling, event)
		perf_event_क्रम_each_child(sibling, func);
पूर्ण

अटल व्योम __perf_event_period(काष्ठा perf_event *event,
				काष्ठा perf_cpu_context *cpuctx,
				काष्ठा perf_event_context *ctx,
				व्योम *info)
अणु
	u64 value = *((u64 *)info);
	bool active;

	अगर (event->attr.freq) अणु
		event->attr.sample_freq = value;
	पूर्ण अन्यथा अणु
		event->attr.sample_period = value;
		event->hw.sample_period = value;
	पूर्ण

	active = (event->state == PERF_EVENT_STATE_ACTIVE);
	अगर (active) अणु
		perf_pmu_disable(ctx->pmu);
		/*
		 * We could be throttled; unthrottle now to aव्योम the tick
		 * trying to unthrottle जबतक we alपढ़ोy re-started the event.
		 */
		अगर (event->hw.पूर्णांकerrupts == MAX_INTERRUPTS) अणु
			event->hw.पूर्णांकerrupts = 0;
			perf_log_throttle(event, 1);
		पूर्ण
		event->pmu->stop(event, PERF_EF_UPDATE);
	पूर्ण

	local64_set(&event->hw.period_left, 0);

	अगर (active) अणु
		event->pmu->start(event, PERF_EF_RELOAD);
		perf_pmu_enable(ctx->pmu);
	पूर्ण
पूर्ण

अटल पूर्णांक perf_event_check_period(काष्ठा perf_event *event, u64 value)
अणु
	वापस event->pmu->check_period(event, value);
पूर्ण

अटल पूर्णांक _perf_event_period(काष्ठा perf_event *event, u64 value)
अणु
	अगर (!is_sampling_event(event))
		वापस -EINVAL;

	अगर (!value)
		वापस -EINVAL;

	अगर (event->attr.freq && value > sysctl_perf_event_sample_rate)
		वापस -EINVAL;

	अगर (perf_event_check_period(event, value))
		वापस -EINVAL;

	अगर (!event->attr.freq && (value & (1ULL << 63)))
		वापस -EINVAL;

	event_function_call(event, __perf_event_period, &value);

	वापस 0;
पूर्ण

पूर्णांक perf_event_period(काष्ठा perf_event *event, u64 value)
अणु
	काष्ठा perf_event_context *ctx;
	पूर्णांक ret;

	ctx = perf_event_ctx_lock(event);
	ret = _perf_event_period(event, value);
	perf_event_ctx_unlock(event, ctx);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(perf_event_period);

अटल स्थिर काष्ठा file_operations perf_fops;

अटल अंतरभूत पूर्णांक perf_fget_light(पूर्णांक fd, काष्ठा fd *p)
अणु
	काष्ठा fd f = fdget(fd);
	अगर (!f.file)
		वापस -EBADF;

	अगर (f.file->f_op != &perf_fops) अणु
		fdput(f);
		वापस -EBADF;
	पूर्ण
	*p = f;
	वापस 0;
पूर्ण

अटल पूर्णांक perf_event_set_output(काष्ठा perf_event *event,
				 काष्ठा perf_event *output_event);
अटल पूर्णांक perf_event_set_filter(काष्ठा perf_event *event, व्योम __user *arg);
अटल पूर्णांक perf_event_set_bpf_prog(काष्ठा perf_event *event, u32 prog_fd);
अटल पूर्णांक perf_copy_attr(काष्ठा perf_event_attr __user *uattr,
			  काष्ठा perf_event_attr *attr);

अटल दीर्घ _perf_ioctl(काष्ठा perf_event *event, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	व्योम (*func)(काष्ठा perf_event *);
	u32 flags = arg;

	चयन (cmd) अणु
	हाल PERF_EVENT_IOC_ENABLE:
		func = _perf_event_enable;
		अवरोध;
	हाल PERF_EVENT_IOC_DISABLE:
		func = _perf_event_disable;
		अवरोध;
	हाल PERF_EVENT_IOC_RESET:
		func = _perf_event_reset;
		अवरोध;

	हाल PERF_EVENT_IOC_REFRESH:
		वापस _perf_event_refresh(event, arg);

	हाल PERF_EVENT_IOC_PERIOD:
	अणु
		u64 value;

		अगर (copy_from_user(&value, (u64 __user *)arg, माप(value)))
			वापस -EFAULT;

		वापस _perf_event_period(event, value);
	पूर्ण
	हाल PERF_EVENT_IOC_ID:
	अणु
		u64 id = primary_event_id(event);

		अगर (copy_to_user((व्योम __user *)arg, &id, माप(id)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण

	हाल PERF_EVENT_IOC_SET_OUTPUT:
	अणु
		पूर्णांक ret;
		अगर (arg != -1) अणु
			काष्ठा perf_event *output_event;
			काष्ठा fd output;
			ret = perf_fget_light(arg, &output);
			अगर (ret)
				वापस ret;
			output_event = output.file->निजी_data;
			ret = perf_event_set_output(event, output_event);
			fdput(output);
		पूर्ण अन्यथा अणु
			ret = perf_event_set_output(event, शून्य);
		पूर्ण
		वापस ret;
	पूर्ण

	हाल PERF_EVENT_IOC_SET_FILTER:
		वापस perf_event_set_filter(event, (व्योम __user *)arg);

	हाल PERF_EVENT_IOC_SET_BPF:
		वापस perf_event_set_bpf_prog(event, arg);

	हाल PERF_EVENT_IOC_PAUSE_OUTPUT: अणु
		काष्ठा perf_buffer *rb;

		rcu_पढ़ो_lock();
		rb = rcu_dereference(event->rb);
		अगर (!rb || !rb->nr_pages) अणु
			rcu_पढ़ो_unlock();
			वापस -EINVAL;
		पूर्ण
		rb_toggle_छोड़ोd(rb, !!arg);
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण

	हाल PERF_EVENT_IOC_QUERY_BPF:
		वापस perf_event_query_prog_array(event, (व्योम __user *)arg);

	हाल PERF_EVENT_IOC_MODIFY_ATTRIBUTES: अणु
		काष्ठा perf_event_attr new_attr;
		पूर्णांक err = perf_copy_attr((काष्ठा perf_event_attr __user *)arg,
					 &new_attr);

		अगर (err)
			वापस err;

		वापस perf_event_modअगरy_attr(event,  &new_attr);
	पूर्ण
	शेष:
		वापस -ENOTTY;
	पूर्ण

	अगर (flags & PERF_IOC_FLAG_GROUP)
		perf_event_क्रम_each(event, func);
	अन्यथा
		perf_event_क्रम_each_child(event, func);

	वापस 0;
पूर्ण

अटल दीर्घ perf_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा perf_event *event = file->निजी_data;
	काष्ठा perf_event_context *ctx;
	दीर्घ ret;

	/* Treat ioctl like ग_लिखोs as it is likely a mutating operation. */
	ret = security_perf_event_ग_लिखो(event);
	अगर (ret)
		वापस ret;

	ctx = perf_event_ctx_lock(event);
	ret = _perf_ioctl(event, cmd, arg);
	perf_event_ctx_unlock(event, ctx);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ perf_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	चयन (_IOC_NR(cmd)) अणु
	हाल _IOC_NR(PERF_EVENT_IOC_SET_FILTER):
	हाल _IOC_NR(PERF_EVENT_IOC_ID):
	हाल _IOC_NR(PERF_EVENT_IOC_QUERY_BPF):
	हाल _IOC_NR(PERF_EVENT_IOC_MODIFY_ATTRIBUTES):
		/* Fix up poपूर्णांकer size (usually 4 -> 8 in 32-on-64-bit हाल */
		अगर (_IOC_SIZE(cmd) == माप(compat_uptr_t)) अणु
			cmd &= ~IOCSIZE_MASK;
			cmd |= माप(व्योम *) << IOCSIZE_SHIFT;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस perf_ioctl(file, cmd, arg);
पूर्ण
#अन्यथा
# define perf_compat_ioctl शून्य
#पूर्ण_अगर

पूर्णांक perf_event_task_enable(व्योम)
अणु
	काष्ठा perf_event_context *ctx;
	काष्ठा perf_event *event;

	mutex_lock(&current->perf_event_mutex);
	list_क्रम_each_entry(event, &current->perf_event_list, owner_entry) अणु
		ctx = perf_event_ctx_lock(event);
		perf_event_क्रम_each_child(event, _perf_event_enable);
		perf_event_ctx_unlock(event, ctx);
	पूर्ण
	mutex_unlock(&current->perf_event_mutex);

	वापस 0;
पूर्ण

पूर्णांक perf_event_task_disable(व्योम)
अणु
	काष्ठा perf_event_context *ctx;
	काष्ठा perf_event *event;

	mutex_lock(&current->perf_event_mutex);
	list_क्रम_each_entry(event, &current->perf_event_list, owner_entry) अणु
		ctx = perf_event_ctx_lock(event);
		perf_event_क्रम_each_child(event, _perf_event_disable);
		perf_event_ctx_unlock(event, ctx);
	पूर्ण
	mutex_unlock(&current->perf_event_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक perf_event_index(काष्ठा perf_event *event)
अणु
	अगर (event->hw.state & PERF_HES_STOPPED)
		वापस 0;

	अगर (event->state != PERF_EVENT_STATE_ACTIVE)
		वापस 0;

	वापस event->pmu->event_idx(event);
पूर्ण

अटल व्योम calc_समयr_values(काष्ठा perf_event *event,
				u64 *now,
				u64 *enabled,
				u64 *running)
अणु
	u64 ctx_समय;

	*now = perf_घड़ी();
	ctx_समय = event->shaकरोw_ctx_समय + *now;
	__perf_update_बार(event, ctx_समय, enabled, running);
पूर्ण

अटल व्योम perf_event_init_userpage(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_mmap_page *userpg;
	काष्ठा perf_buffer *rb;

	rcu_पढ़ो_lock();
	rb = rcu_dereference(event->rb);
	अगर (!rb)
		जाओ unlock;

	userpg = rb->user_page;

	/* Allow new userspace to detect that bit 0 is deprecated */
	userpg->cap_bit0_is_deprecated = 1;
	userpg->size = दुरत्व(काष्ठा perf_event_mmap_page, __reserved);
	userpg->data_offset = PAGE_SIZE;
	userpg->data_size = perf_data_size(rb);

unlock:
	rcu_पढ़ो_unlock();
पूर्ण

व्योम __weak arch_perf_update_userpage(
	काष्ठा perf_event *event, काष्ठा perf_event_mmap_page *userpg, u64 now)
अणु
पूर्ण

/*
 * Callers need to ensure there can be no nesting of this function, otherwise
 * the seqlock logic goes bad. We can not serialize this because the arch
 * code calls this from NMI context.
 */
व्योम perf_event_update_userpage(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_mmap_page *userpg;
	काष्ठा perf_buffer *rb;
	u64 enabled, running, now;

	rcu_पढ़ो_lock();
	rb = rcu_dereference(event->rb);
	अगर (!rb)
		जाओ unlock;

	/*
	 * compute total_समय_enabled, total_समय_running
	 * based on snapshot values taken when the event
	 * was last scheduled in.
	 *
	 * we cannot simply called update_context_समय()
	 * because of locking issue as we can be called in
	 * NMI context
	 */
	calc_समयr_values(event, &now, &enabled, &running);

	userpg = rb->user_page;
	/*
	 * Disable preemption to guarantee consistent समय stamps are stored to
	 * the user page.
	 */
	preempt_disable();
	++userpg->lock;
	barrier();
	userpg->index = perf_event_index(event);
	userpg->offset = perf_event_count(event);
	अगर (userpg->index)
		userpg->offset -= local64_पढ़ो(&event->hw.prev_count);

	userpg->समय_enabled = enabled +
			atomic64_पढ़ो(&event->child_total_समय_enabled);

	userpg->समय_running = running +
			atomic64_पढ़ो(&event->child_total_समय_running);

	arch_perf_update_userpage(event, userpg, now);

	barrier();
	++userpg->lock;
	preempt_enable();
unlock:
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(perf_event_update_userpage);

अटल vm_fault_t perf_mmap_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा perf_event *event = vmf->vma->vm_file->निजी_data;
	काष्ठा perf_buffer *rb;
	vm_fault_t ret = VM_FAULT_SIGBUS;

	अगर (vmf->flags & FAULT_FLAG_MKWRITE) अणु
		अगर (vmf->pgoff == 0)
			ret = 0;
		वापस ret;
	पूर्ण

	rcu_पढ़ो_lock();
	rb = rcu_dereference(event->rb);
	अगर (!rb)
		जाओ unlock;

	अगर (vmf->pgoff && (vmf->flags & FAULT_FLAG_WRITE))
		जाओ unlock;

	vmf->page = perf_mmap_to_page(rb, vmf->pgoff);
	अगर (!vmf->page)
		जाओ unlock;

	get_page(vmf->page);
	vmf->page->mapping = vmf->vma->vm_file->f_mapping;
	vmf->page->index   = vmf->pgoff;

	ret = 0;
unlock:
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल व्योम ring_buffer_attach(काष्ठा perf_event *event,
			       काष्ठा perf_buffer *rb)
अणु
	काष्ठा perf_buffer *old_rb = शून्य;
	अचिन्हित दीर्घ flags;

	अगर (event->rb) अणु
		/*
		 * Should be impossible, we set this when removing
		 * event->rb_entry and रुको/clear when adding event->rb_entry.
		 */
		WARN_ON_ONCE(event->rcu_pending);

		old_rb = event->rb;
		spin_lock_irqsave(&old_rb->event_lock, flags);
		list_del_rcu(&event->rb_entry);
		spin_unlock_irqrestore(&old_rb->event_lock, flags);

		event->rcu_batches = get_state_synchronize_rcu();
		event->rcu_pending = 1;
	पूर्ण

	अगर (rb) अणु
		अगर (event->rcu_pending) अणु
			cond_synchronize_rcu(event->rcu_batches);
			event->rcu_pending = 0;
		पूर्ण

		spin_lock_irqsave(&rb->event_lock, flags);
		list_add_rcu(&event->rb_entry, &rb->event_list);
		spin_unlock_irqrestore(&rb->event_lock, flags);
	पूर्ण

	/*
	 * Aव्योम racing with perf_mmap_बंद(AUX): stop the event
	 * beक्रमe swizzling the event::rb poपूर्णांकer; अगर it's getting
	 * unmapped, its aux_mmap_count will be 0 and it won't
	 * restart. See the comment in __perf_pmu_output_stop().
	 *
	 * Data will inevitably be lost when set_output is करोne in
	 * mid-air, but then again, whoever करोes it like this is
	 * not in क्रम the data anyway.
	 */
	अगर (has_aux(event))
		perf_event_stop(event, 0);

	rcu_assign_poपूर्णांकer(event->rb, rb);

	अगर (old_rb) अणु
		ring_buffer_put(old_rb);
		/*
		 * Since we detached beक्रमe setting the new rb, so that we
		 * could attach the new rb, we could have missed a wakeup.
		 * Provide it now.
		 */
		wake_up_all(&event->रुकोq);
	पूर्ण
पूर्ण

अटल व्योम ring_buffer_wakeup(काष्ठा perf_event *event)
अणु
	काष्ठा perf_buffer *rb;

	rcu_पढ़ो_lock();
	rb = rcu_dereference(event->rb);
	अगर (rb) अणु
		list_क्रम_each_entry_rcu(event, &rb->event_list, rb_entry)
			wake_up_all(&event->रुकोq);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

काष्ठा perf_buffer *ring_buffer_get(काष्ठा perf_event *event)
अणु
	काष्ठा perf_buffer *rb;

	rcu_पढ़ो_lock();
	rb = rcu_dereference(event->rb);
	अगर (rb) अणु
		अगर (!refcount_inc_not_zero(&rb->refcount))
			rb = शून्य;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस rb;
पूर्ण

व्योम ring_buffer_put(काष्ठा perf_buffer *rb)
अणु
	अगर (!refcount_dec_and_test(&rb->refcount))
		वापस;

	WARN_ON_ONCE(!list_empty(&rb->event_list));

	call_rcu(&rb->rcu_head, rb_मुक्त_rcu);
पूर्ण

अटल व्योम perf_mmap_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा perf_event *event = vma->vm_file->निजी_data;

	atomic_inc(&event->mmap_count);
	atomic_inc(&event->rb->mmap_count);

	अगर (vma->vm_pgoff)
		atomic_inc(&event->rb->aux_mmap_count);

	अगर (event->pmu->event_mapped)
		event->pmu->event_mapped(event, vma->vm_mm);
पूर्ण

अटल व्योम perf_pmu_output_stop(काष्ठा perf_event *event);

/*
 * A buffer can be mmap()ed multiple बार; either directly through the same
 * event, or through other events by use of perf_event_set_output().
 *
 * In order to unकरो the VM accounting करोne by perf_mmap() we need to destroy
 * the buffer here, where we still have a VM context. This means we need
 * to detach all events redirecting to us.
 */
अटल व्योम perf_mmap_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा perf_event *event = vma->vm_file->निजी_data;
	काष्ठा perf_buffer *rb = ring_buffer_get(event);
	काष्ठा user_काष्ठा *mmap_user = rb->mmap_user;
	पूर्णांक mmap_locked = rb->mmap_locked;
	अचिन्हित दीर्घ size = perf_data_size(rb);
	bool detach_rest = false;

	अगर (event->pmu->event_unmapped)
		event->pmu->event_unmapped(event, vma->vm_mm);

	/*
	 * rb->aux_mmap_count will always drop beक्रमe rb->mmap_count and
	 * event->mmap_count, so it is ok to use event->mmap_mutex to
	 * serialize with perf_mmap here.
	 */
	अगर (rb_has_aux(rb) && vma->vm_pgoff == rb->aux_pgoff &&
	    atomic_dec_and_mutex_lock(&rb->aux_mmap_count, &event->mmap_mutex)) अणु
		/*
		 * Stop all AUX events that are writing to this buffer,
		 * so that we can मुक्त its AUX pages and corresponding PMU
		 * data. Note that after rb::aux_mmap_count dropped to zero,
		 * they won't start any more (see perf_aux_output_begin()).
		 */
		perf_pmu_output_stop(event);

		/* now it's safe to मुक्त the pages */
		atomic_दीर्घ_sub(rb->aux_nr_pages - rb->aux_mmap_locked, &mmap_user->locked_vm);
		atomic64_sub(rb->aux_mmap_locked, &vma->vm_mm->pinned_vm);

		/* this has to be the last one */
		rb_मुक्त_aux(rb);
		WARN_ON_ONCE(refcount_पढ़ो(&rb->aux_refcount));

		mutex_unlock(&event->mmap_mutex);
	पूर्ण

	अगर (atomic_dec_and_test(&rb->mmap_count))
		detach_rest = true;

	अगर (!atomic_dec_and_mutex_lock(&event->mmap_count, &event->mmap_mutex))
		जाओ out_put;

	ring_buffer_attach(event, शून्य);
	mutex_unlock(&event->mmap_mutex);

	/* If there's still other mmap()s of this buffer, we're करोne. */
	अगर (!detach_rest)
		जाओ out_put;

	/*
	 * No other mmap()s, detach from all other events that might redirect
	 * पूर्णांकo the now unreachable buffer. Somewhat complicated by the
	 * fact that rb::event_lock otherwise nests inside mmap_mutex.
	 */
again:
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(event, &rb->event_list, rb_entry) अणु
		अगर (!atomic_दीर्घ_inc_not_zero(&event->refcount)) अणु
			/*
			 * This event is en-route to मुक्त_event() which will
			 * detach it and हटाओ it from the list.
			 */
			जारी;
		पूर्ण
		rcu_पढ़ो_unlock();

		mutex_lock(&event->mmap_mutex);
		/*
		 * Check we didn't race with perf_event_set_output() which can
		 * swizzle the rb from under us जबतक we were रुकोing to
		 * acquire mmap_mutex.
		 *
		 * If we find a dअगरferent rb; ignore this event, a next
		 * iteration will no दीर्घer find it on the list. We have to
		 * still restart the iteration to make sure we're not now
		 * iterating the wrong list.
		 */
		अगर (event->rb == rb)
			ring_buffer_attach(event, शून्य);

		mutex_unlock(&event->mmap_mutex);
		put_event(event);

		/*
		 * Restart the iteration; either we're on the wrong list or
		 * destroyed its पूर्णांकegrity by करोing a deletion.
		 */
		जाओ again;
	पूर्ण
	rcu_पढ़ो_unlock();

	/*
	 * It could be there's still a few 0-ref events on the list; they'll
	 * get cleaned up by मुक्त_event() -- they'll also still have their
	 * ref on the rb and will मुक्त it whenever they are करोne with it.
	 *
	 * Aside from that, this buffer is 'fully' detached and unmapped,
	 * unकरो the VM accounting.
	 */

	atomic_दीर्घ_sub((size >> PAGE_SHIFT) + 1 - mmap_locked,
			&mmap_user->locked_vm);
	atomic64_sub(mmap_locked, &vma->vm_mm->pinned_vm);
	मुक्त_uid(mmap_user);

out_put:
	ring_buffer_put(rb); /* could be last */
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा perf_mmap_vmops = अणु
	.खोलो		= perf_mmap_खोलो,
	.बंद		= perf_mmap_बंद, /* non mergeable */
	.fault		= perf_mmap_fault,
	.page_mkग_लिखो	= perf_mmap_fault,
पूर्ण;

अटल पूर्णांक perf_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा perf_event *event = file->निजी_data;
	अचिन्हित दीर्घ user_locked, user_lock_limit;
	काष्ठा user_काष्ठा *user = current_user();
	काष्ठा perf_buffer *rb = शून्य;
	अचिन्हित दीर्घ locked, lock_limit;
	अचिन्हित दीर्घ vma_size;
	अचिन्हित दीर्घ nr_pages;
	दीर्घ user_extra = 0, extra = 0;
	पूर्णांक ret = 0, flags = 0;

	/*
	 * Don't allow mmap() of inherited per-task counters. This would
	 * create a perक्रमmance issue due to all children writing to the
	 * same rb.
	 */
	अगर (event->cpu == -1 && event->attr.inherit)
		वापस -EINVAL;

	अगर (!(vma->vm_flags & VM_SHARED))
		वापस -EINVAL;

	ret = security_perf_event_पढ़ो(event);
	अगर (ret)
		वापस ret;

	vma_size = vma->vm_end - vma->vm_start;

	अगर (vma->vm_pgoff == 0) अणु
		nr_pages = (vma_size / PAGE_SIZE) - 1;
	पूर्ण अन्यथा अणु
		/*
		 * AUX area mapping: अगर rb->aux_nr_pages != 0, it's alपढ़ोy
		 * mapped, all subsequent mappings should have the same size
		 * and offset. Must be above the normal perf buffer.
		 */
		u64 aux_offset, aux_size;

		अगर (!event->rb)
			वापस -EINVAL;

		nr_pages = vma_size / PAGE_SIZE;

		mutex_lock(&event->mmap_mutex);
		ret = -EINVAL;

		rb = event->rb;
		अगर (!rb)
			जाओ aux_unlock;

		aux_offset = READ_ONCE(rb->user_page->aux_offset);
		aux_size = READ_ONCE(rb->user_page->aux_size);

		अगर (aux_offset < perf_data_size(rb) + PAGE_SIZE)
			जाओ aux_unlock;

		अगर (aux_offset != vma->vm_pgoff << PAGE_SHIFT)
			जाओ aux_unlock;

		/* alपढ़ोy mapped with a dअगरferent offset */
		अगर (rb_has_aux(rb) && rb->aux_pgoff != vma->vm_pgoff)
			जाओ aux_unlock;

		अगर (aux_size != vma_size || aux_size != nr_pages * PAGE_SIZE)
			जाओ aux_unlock;

		/* alपढ़ोy mapped with a dअगरferent size */
		अगर (rb_has_aux(rb) && rb->aux_nr_pages != nr_pages)
			जाओ aux_unlock;

		अगर (!is_घातer_of_2(nr_pages))
			जाओ aux_unlock;

		अगर (!atomic_inc_not_zero(&rb->mmap_count))
			जाओ aux_unlock;

		अगर (rb_has_aux(rb)) अणु
			atomic_inc(&rb->aux_mmap_count);
			ret = 0;
			जाओ unlock;
		पूर्ण

		atomic_set(&rb->aux_mmap_count, 1);
		user_extra = nr_pages;

		जाओ accounting;
	पूर्ण

	/*
	 * If we have rb pages ensure they're a घातer-of-two number, so we
	 * can करो biपंचांगasks instead of modulo.
	 */
	अगर (nr_pages != 0 && !is_घातer_of_2(nr_pages))
		वापस -EINVAL;

	अगर (vma_size != PAGE_SIZE * (1 + nr_pages))
		वापस -EINVAL;

	WARN_ON_ONCE(event->ctx->parent_ctx);
again:
	mutex_lock(&event->mmap_mutex);
	अगर (event->rb) अणु
		अगर (event->rb->nr_pages != nr_pages) अणु
			ret = -EINVAL;
			जाओ unlock;
		पूर्ण

		अगर (!atomic_inc_not_zero(&event->rb->mmap_count)) अणु
			/*
			 * Raced against perf_mmap_बंद() through
			 * perf_event_set_output(). Try again, hope क्रम better
			 * luck.
			 */
			mutex_unlock(&event->mmap_mutex);
			जाओ again;
		पूर्ण

		जाओ unlock;
	पूर्ण

	user_extra = nr_pages + 1;

accounting:
	user_lock_limit = sysctl_perf_event_mlock >> (PAGE_SHIFT - 10);

	/*
	 * Increase the limit linearly with more CPUs:
	 */
	user_lock_limit *= num_online_cpus();

	user_locked = atomic_दीर्घ_पढ़ो(&user->locked_vm);

	/*
	 * sysctl_perf_event_mlock may have changed, so that
	 *     user->locked_vm > user_lock_limit
	 */
	अगर (user_locked > user_lock_limit)
		user_locked = user_lock_limit;
	user_locked += user_extra;

	अगर (user_locked > user_lock_limit) अणु
		/*
		 * अक्षरge locked_vm until it hits user_lock_limit;
		 * अक्षरge the rest from pinned_vm
		 */
		extra = user_locked - user_lock_limit;
		user_extra -= extra;
	पूर्ण

	lock_limit = rlimit(RLIMIT_MEMLOCK);
	lock_limit >>= PAGE_SHIFT;
	locked = atomic64_पढ़ो(&vma->vm_mm->pinned_vm) + extra;

	अगर ((locked > lock_limit) && perf_is_paranoid() &&
		!capable(CAP_IPC_LOCK)) अणु
		ret = -EPERM;
		जाओ unlock;
	पूर्ण

	WARN_ON(!rb && event->rb);

	अगर (vma->vm_flags & VM_WRITE)
		flags |= RING_BUFFER_WRITABLE;

	अगर (!rb) अणु
		rb = rb_alloc(nr_pages,
			      event->attr.watermark ? event->attr.wakeup_watermark : 0,
			      event->cpu, flags);

		अगर (!rb) अणु
			ret = -ENOMEM;
			जाओ unlock;
		पूर्ण

		atomic_set(&rb->mmap_count, 1);
		rb->mmap_user = get_current_user();
		rb->mmap_locked = extra;

		ring_buffer_attach(event, rb);

		perf_event_init_userpage(event);
		perf_event_update_userpage(event);
	पूर्ण अन्यथा अणु
		ret = rb_alloc_aux(rb, event, vma->vm_pgoff, nr_pages,
				   event->attr.aux_watermark, flags);
		अगर (!ret)
			rb->aux_mmap_locked = extra;
	पूर्ण

unlock:
	अगर (!ret) अणु
		atomic_दीर्घ_add(user_extra, &user->locked_vm);
		atomic64_add(extra, &vma->vm_mm->pinned_vm);

		atomic_inc(&event->mmap_count);
	पूर्ण अन्यथा अगर (rb) अणु
		atomic_dec(&rb->mmap_count);
	पूर्ण
aux_unlock:
	mutex_unlock(&event->mmap_mutex);

	/*
	 * Since pinned accounting is per vm we cannot allow विभाजन() to copy our
	 * vma.
	 */
	vma->vm_flags |= VM_DONTCOPY | VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_ops = &perf_mmap_vmops;

	अगर (event->pmu->event_mapped)
		event->pmu->event_mapped(event, vma->vm_mm);

	वापस ret;
पूर्ण

अटल पूर्णांक perf_fasync(पूर्णांक fd, काष्ठा file *filp, पूर्णांक on)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा perf_event *event = filp->निजी_data;
	पूर्णांक retval;

	inode_lock(inode);
	retval = fasync_helper(fd, filp, on, &event->fasync);
	inode_unlock(inode);

	अगर (retval < 0)
		वापस retval;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations perf_fops = अणु
	.llseek			= no_llseek,
	.release		= perf_release,
	.पढ़ो			= perf_पढ़ो,
	.poll			= perf_poll,
	.unlocked_ioctl		= perf_ioctl,
	.compat_ioctl		= perf_compat_ioctl,
	.mmap			= perf_mmap,
	.fasync			= perf_fasync,
पूर्ण;

/*
 * Perf event wakeup
 *
 * If there's data, ensure we set the poll() state and publish everything
 * to user-space beक्रमe waking everybody up.
 */

अटल अंतरभूत काष्ठा fasync_काष्ठा **perf_event_fasync(काष्ठा perf_event *event)
अणु
	/* only the parent has fasync state */
	अगर (event->parent)
		event = event->parent;
	वापस &event->fasync;
पूर्ण

व्योम perf_event_wakeup(काष्ठा perf_event *event)
अणु
	ring_buffer_wakeup(event);

	अगर (event->pending_समाप्त) अणु
		समाप्त_fasync(perf_event_fasync(event), SIGIO, event->pending_समाप्त);
		event->pending_समाप्त = 0;
	पूर्ण
पूर्ण

अटल व्योम perf_sigtrap(काष्ठा perf_event *event)
अणु
	/*
	 * We'd expect this to only occur अगर the irq_work is delayed and either
	 * ctx->task or current has changed in the meanसमय. This can be the
	 * हाल on architectures that करो not implement arch_irq_work_उठाओ().
	 */
	अगर (WARN_ON_ONCE(event->ctx->task != current))
		वापस;

	/*
	 * perf_pending_event() can race with the task निकासing.
	 */
	अगर (current->flags & PF_EXITING)
		वापस;

	क्रमce_sig_perf((व्योम __user *)event->pending_addr,
		       event->attr.type, event->attr.sig_data);
पूर्ण

अटल व्योम perf_pending_event_disable(काष्ठा perf_event *event)
अणु
	पूर्णांक cpu = READ_ONCE(event->pending_disable);

	अगर (cpu < 0)
		वापस;

	अगर (cpu == smp_processor_id()) अणु
		WRITE_ONCE(event->pending_disable, -1);

		अगर (event->attr.sigtrap) अणु
			perf_sigtrap(event);
			atomic_set_release(&event->event_limit, 1); /* rearm event */
			वापस;
		पूर्ण

		perf_event_disable_local(event);
		वापस;
	पूर्ण

	/*
	 *  CPU-A			CPU-B
	 *
	 *  perf_event_disable_inatomic()
	 *    @pending_disable = CPU-A;
	 *    irq_work_queue();
	 *
	 *  sched-out
	 *    @pending_disable = -1;
	 *
	 *				sched-in
	 *				perf_event_disable_inatomic()
	 *				  @pending_disable = CPU-B;
	 *				  irq_work_queue(); // FAILS
	 *
	 *  irq_work_run()
	 *    perf_pending_event()
	 *
	 * But the event runs on CPU-B and wants disabling there.
	 */
	irq_work_queue_on(&event->pending, cpu);
पूर्ण

अटल व्योम perf_pending_event(काष्ठा irq_work *entry)
अणु
	काष्ठा perf_event *event = container_of(entry, काष्ठा perf_event, pending);
	पूर्णांक rctx;

	rctx = perf_swevent_get_recursion_context();
	/*
	 * If we 'fail' here, that's OK, it means recursion is alपढ़ोy disabled
	 * and we won't recurse 'further'.
	 */

	perf_pending_event_disable(event);

	अगर (event->pending_wakeup) अणु
		event->pending_wakeup = 0;
		perf_event_wakeup(event);
	पूर्ण

	अगर (rctx >= 0)
		perf_swevent_put_recursion_context(rctx);
पूर्ण

/*
 * We assume there is only KVM supporting the callbacks.
 * Later on, we might change it to a list अगर there is
 * another भवization implementation supporting the callbacks.
 */
काष्ठा perf_guest_info_callbacks *perf_guest_cbs;

पूर्णांक perf_रेजिस्टर_guest_info_callbacks(काष्ठा perf_guest_info_callbacks *cbs)
अणु
	perf_guest_cbs = cbs;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(perf_रेजिस्टर_guest_info_callbacks);

पूर्णांक perf_unरेजिस्टर_guest_info_callbacks(काष्ठा perf_guest_info_callbacks *cbs)
अणु
	perf_guest_cbs = शून्य;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(perf_unरेजिस्टर_guest_info_callbacks);

अटल व्योम
perf_output_sample_regs(काष्ठा perf_output_handle *handle,
			काष्ठा pt_regs *regs, u64 mask)
अणु
	पूर्णांक bit;
	DECLARE_BITMAP(_mask, 64);

	biपंचांगap_from_u64(_mask, mask);
	क्रम_each_set_bit(bit, _mask, माप(mask) * BITS_PER_BYTE) अणु
		u64 val;

		val = perf_reg_value(regs, bit);
		perf_output_put(handle, val);
	पूर्ण
पूर्ण

अटल व्योम perf_sample_regs_user(काष्ठा perf_regs *regs_user,
				  काष्ठा pt_regs *regs)
अणु
	अगर (user_mode(regs)) अणु
		regs_user->abi = perf_reg_abi(current);
		regs_user->regs = regs;
	पूर्ण अन्यथा अगर (!(current->flags & PF_KTHREAD)) अणु
		perf_get_regs_user(regs_user, regs);
	पूर्ण अन्यथा अणु
		regs_user->abi = PERF_SAMPLE_REGS_ABI_NONE;
		regs_user->regs = शून्य;
	पूर्ण
पूर्ण

अटल व्योम perf_sample_regs_पूर्णांकr(काष्ठा perf_regs *regs_पूर्णांकr,
				  काष्ठा pt_regs *regs)
अणु
	regs_पूर्णांकr->regs = regs;
	regs_पूर्णांकr->abi  = perf_reg_abi(current);
पूर्ण


/*
 * Get reमुख्यing task size from user stack poपूर्णांकer.
 *
 * It'd be better to take stack vma map and limit this more
 * precisely, but there's no way to get it safely under पूर्णांकerrupt,
 * so using TASK_SIZE as limit.
 */
अटल u64 perf_ustack_task_size(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ addr = perf_user_stack_poपूर्णांकer(regs);

	अगर (!addr || addr >= TASK_SIZE)
		वापस 0;

	वापस TASK_SIZE - addr;
पूर्ण

अटल u16
perf_sample_ustack_size(u16 stack_size, u16 header_size,
			काष्ठा pt_regs *regs)
अणु
	u64 task_size;

	/* No regs, no stack poपूर्णांकer, no dump. */
	अगर (!regs)
		वापस 0;

	/*
	 * Check अगर we fit in with the requested stack size पूर्णांकo the:
	 * - TASK_SIZE
	 *   If we करोn't, we limit the size to the TASK_SIZE.
	 *
	 * - reमुख्यing sample size
	 *   If we करोn't, we customize the stack size to
	 *   fit in to the reमुख्यing sample size.
	 */

	task_size  = min((u64) अच_लघु_उच्च, perf_ustack_task_size(regs));
	stack_size = min(stack_size, (u16) task_size);

	/* Current header size plus अटल size and dynamic size. */
	header_size += 2 * माप(u64);

	/* Do we fit in with the current stack dump size? */
	अगर ((u16) (header_size + stack_size) < header_size) अणु
		/*
		 * If we overflow the maximum size क्रम the sample,
		 * we customize the stack dump size to fit in.
		 */
		stack_size = अच_लघु_उच्च - header_size - माप(u64);
		stack_size = round_up(stack_size, माप(u64));
	पूर्ण

	वापस stack_size;
पूर्ण

अटल व्योम
perf_output_sample_ustack(काष्ठा perf_output_handle *handle, u64 dump_size,
			  काष्ठा pt_regs *regs)
अणु
	/* Case of a kernel thपढ़ो, nothing to dump */
	अगर (!regs) अणु
		u64 size = 0;
		perf_output_put(handle, size);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ sp;
		अचिन्हित पूर्णांक rem;
		u64 dyn_size;
		mm_segment_t fs;

		/*
		 * We dump:
		 * अटल size
		 *   - the size requested by user or the best one we can fit
		 *     in to the sample max size
		 * data
		 *   - user stack dump data
		 * dynamic size
		 *   - the actual dumped size
		 */

		/* Static size. */
		perf_output_put(handle, dump_size);

		/* Data. */
		sp = perf_user_stack_poपूर्णांकer(regs);
		fs = क्रमce_uaccess_begin();
		rem = __output_copy_user(handle, (व्योम *) sp, dump_size);
		क्रमce_uaccess_end(fs);
		dyn_size = dump_size - rem;

		perf_output_skip(handle, rem);

		/* Dynamic size. */
		perf_output_put(handle, dyn_size);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ perf_prepare_sample_aux(काष्ठा perf_event *event,
					  काष्ठा perf_sample_data *data,
					  माप_प्रकार size)
अणु
	काष्ठा perf_event *sampler = event->aux_event;
	काष्ठा perf_buffer *rb;

	data->aux_size = 0;

	अगर (!sampler)
		जाओ out;

	अगर (WARN_ON_ONCE(READ_ONCE(sampler->state) != PERF_EVENT_STATE_ACTIVE))
		जाओ out;

	अगर (WARN_ON_ONCE(READ_ONCE(sampler->oncpu) != smp_processor_id()))
		जाओ out;

	rb = ring_buffer_get(sampler->parent ? sampler->parent : sampler);
	अगर (!rb)
		जाओ out;

	/*
	 * If this is an NMI hit inside sampling code, करोn't take
	 * the sample. See also perf_aux_sample_output().
	 */
	अगर (READ_ONCE(rb->aux_in_sampling)) अणु
		data->aux_size = 0;
	पूर्ण अन्यथा अणु
		size = min_t(माप_प्रकार, size, perf_aux_size(rb));
		data->aux_size = ALIGN(size, माप(u64));
	पूर्ण
	ring_buffer_put(rb);

out:
	वापस data->aux_size;
पूर्ण

दीर्घ perf_pmu_snapshot_aux(काष्ठा perf_buffer *rb,
			   काष्ठा perf_event *event,
			   काष्ठा perf_output_handle *handle,
			   अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ flags;
	दीर्घ ret;

	/*
	 * Normal ->start()/->stop() callbacks run in IRQ mode in scheduler
	 * paths. If we start calling them in NMI context, they may race with
	 * the IRQ ones, that is, क्रम example, re-starting an event that's just
	 * been stopped, which is why we're using a separate callback that
	 * करोesn't change the event state.
	 *
	 * IRQs need to be disabled to prevent IPIs from racing with us.
	 */
	local_irq_save(flags);
	/*
	 * Guard against NMI hits inside the critical section;
	 * see also perf_prepare_sample_aux().
	 */
	WRITE_ONCE(rb->aux_in_sampling, 1);
	barrier();

	ret = event->pmu->snapshot_aux(event, handle, size);

	barrier();
	WRITE_ONCE(rb->aux_in_sampling, 0);
	local_irq_restore(flags);

	वापस ret;
पूर्ण

अटल व्योम perf_aux_sample_output(काष्ठा perf_event *event,
				   काष्ठा perf_output_handle *handle,
				   काष्ठा perf_sample_data *data)
अणु
	काष्ठा perf_event *sampler = event->aux_event;
	काष्ठा perf_buffer *rb;
	अचिन्हित दीर्घ pad;
	दीर्घ size;

	अगर (WARN_ON_ONCE(!sampler || !data->aux_size))
		वापस;

	rb = ring_buffer_get(sampler->parent ? sampler->parent : sampler);
	अगर (!rb)
		वापस;

	size = perf_pmu_snapshot_aux(rb, sampler, handle, data->aux_size);

	/*
	 * An error here means that perf_output_copy() failed (वापसed a
	 * non-zero surplus that it didn't copy), which in its current
	 * enlightened implementation is not possible. If that changes, we'd
	 * like to know.
	 */
	अगर (WARN_ON_ONCE(size < 0))
		जाओ out_put;

	/*
	 * The pad comes from ALIGN()ing data->aux_size up to u64 in
	 * perf_prepare_sample_aux(), so should not be more than that.
	 */
	pad = data->aux_size - size;
	अगर (WARN_ON_ONCE(pad >= माप(u64)))
		pad = 8;

	अगर (pad) अणु
		u64 zero = 0;
		perf_output_copy(handle, &zero, pad);
	पूर्ण

out_put:
	ring_buffer_put(rb);
पूर्ण

अटल व्योम __perf_event_header__init_id(काष्ठा perf_event_header *header,
					 काष्ठा perf_sample_data *data,
					 काष्ठा perf_event *event)
अणु
	u64 sample_type = event->attr.sample_type;

	data->type = sample_type;
	header->size += event->id_header_size;

	अगर (sample_type & PERF_SAMPLE_TID) अणु
		/* namespace issues */
		data->tid_entry.pid = perf_event_pid(event, current);
		data->tid_entry.tid = perf_event_tid(event, current);
	पूर्ण

	अगर (sample_type & PERF_SAMPLE_TIME)
		data->समय = perf_event_घड़ी(event);

	अगर (sample_type & (PERF_SAMPLE_ID | PERF_SAMPLE_IDENTIFIER))
		data->id = primary_event_id(event);

	अगर (sample_type & PERF_SAMPLE_STREAM_ID)
		data->stream_id = event->id;

	अगर (sample_type & PERF_SAMPLE_CPU) अणु
		data->cpu_entry.cpu	 = raw_smp_processor_id();
		data->cpu_entry.reserved = 0;
	पूर्ण
पूर्ण

व्योम perf_event_header__init_id(काष्ठा perf_event_header *header,
				काष्ठा perf_sample_data *data,
				काष्ठा perf_event *event)
अणु
	अगर (event->attr.sample_id_all)
		__perf_event_header__init_id(header, data, event);
पूर्ण

अटल व्योम __perf_event__output_id_sample(काष्ठा perf_output_handle *handle,
					   काष्ठा perf_sample_data *data)
अणु
	u64 sample_type = data->type;

	अगर (sample_type & PERF_SAMPLE_TID)
		perf_output_put(handle, data->tid_entry);

	अगर (sample_type & PERF_SAMPLE_TIME)
		perf_output_put(handle, data->समय);

	अगर (sample_type & PERF_SAMPLE_ID)
		perf_output_put(handle, data->id);

	अगर (sample_type & PERF_SAMPLE_STREAM_ID)
		perf_output_put(handle, data->stream_id);

	अगर (sample_type & PERF_SAMPLE_CPU)
		perf_output_put(handle, data->cpu_entry);

	अगर (sample_type & PERF_SAMPLE_IDENTIFIER)
		perf_output_put(handle, data->id);
पूर्ण

व्योम perf_event__output_id_sample(काष्ठा perf_event *event,
				  काष्ठा perf_output_handle *handle,
				  काष्ठा perf_sample_data *sample)
अणु
	अगर (event->attr.sample_id_all)
		__perf_event__output_id_sample(handle, sample);
पूर्ण

अटल व्योम perf_output_पढ़ो_one(काष्ठा perf_output_handle *handle,
				 काष्ठा perf_event *event,
				 u64 enabled, u64 running)
अणु
	u64 पढ़ो_क्रमmat = event->attr.पढ़ो_क्रमmat;
	u64 values[4];
	पूर्णांक n = 0;

	values[n++] = perf_event_count(event);
	अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_ENABLED) अणु
		values[n++] = enabled +
			atomic64_पढ़ो(&event->child_total_समय_enabled);
	पूर्ण
	अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_RUNNING) अणु
		values[n++] = running +
			atomic64_पढ़ो(&event->child_total_समय_running);
	पूर्ण
	अगर (पढ़ो_क्रमmat & PERF_FORMAT_ID)
		values[n++] = primary_event_id(event);

	__output_copy(handle, values, n * माप(u64));
पूर्ण

अटल व्योम perf_output_पढ़ो_group(काष्ठा perf_output_handle *handle,
			    काष्ठा perf_event *event,
			    u64 enabled, u64 running)
अणु
	काष्ठा perf_event *leader = event->group_leader, *sub;
	u64 पढ़ो_क्रमmat = event->attr.पढ़ो_क्रमmat;
	u64 values[5];
	पूर्णांक n = 0;

	values[n++] = 1 + leader->nr_siblings;

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_ENABLED)
		values[n++] = enabled;

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_RUNNING)
		values[n++] = running;

	अगर ((leader != event) &&
	    (leader->state == PERF_EVENT_STATE_ACTIVE))
		leader->pmu->पढ़ो(leader);

	values[n++] = perf_event_count(leader);
	अगर (पढ़ो_क्रमmat & PERF_FORMAT_ID)
		values[n++] = primary_event_id(leader);

	__output_copy(handle, values, n * माप(u64));

	क्रम_each_sibling_event(sub, leader) अणु
		n = 0;

		अगर ((sub != event) &&
		    (sub->state == PERF_EVENT_STATE_ACTIVE))
			sub->pmu->पढ़ो(sub);

		values[n++] = perf_event_count(sub);
		अगर (पढ़ो_क्रमmat & PERF_FORMAT_ID)
			values[n++] = primary_event_id(sub);

		__output_copy(handle, values, n * माप(u64));
	पूर्ण
पूर्ण

#घोषणा PERF_FORMAT_TOTAL_TIMES (PERF_FORMAT_TOTAL_TIME_ENABLED|\
				 PERF_FORMAT_TOTAL_TIME_RUNNING)

/*
 * XXX PERF_SAMPLE_READ vs inherited events seems dअगरficult.
 *
 * The problem is that its both hard and excessively expensive to iterate the
 * child list, not to mention that its impossible to IPI the children running
 * on another CPU, from पूर्णांकerrupt/NMI context.
 */
अटल व्योम perf_output_पढ़ो(काष्ठा perf_output_handle *handle,
			     काष्ठा perf_event *event)
अणु
	u64 enabled = 0, running = 0, now;
	u64 पढ़ो_क्रमmat = event->attr.पढ़ो_क्रमmat;

	/*
	 * compute total_समय_enabled, total_समय_running
	 * based on snapshot values taken when the event
	 * was last scheduled in.
	 *
	 * we cannot simply called update_context_समय()
	 * because of locking issue as we are called in
	 * NMI context
	 */
	अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIMES)
		calc_समयr_values(event, &now, &enabled, &running);

	अगर (event->attr.पढ़ो_क्रमmat & PERF_FORMAT_GROUP)
		perf_output_पढ़ो_group(handle, event, enabled, running);
	अन्यथा
		perf_output_पढ़ो_one(handle, event, enabled, running);
पूर्ण

अटल अंतरभूत bool perf_sample_save_hw_index(काष्ठा perf_event *event)
अणु
	वापस event->attr.branch_sample_type & PERF_SAMPLE_BRANCH_HW_INDEX;
पूर्ण

व्योम perf_output_sample(काष्ठा perf_output_handle *handle,
			काष्ठा perf_event_header *header,
			काष्ठा perf_sample_data *data,
			काष्ठा perf_event *event)
अणु
	u64 sample_type = data->type;

	perf_output_put(handle, *header);

	अगर (sample_type & PERF_SAMPLE_IDENTIFIER)
		perf_output_put(handle, data->id);

	अगर (sample_type & PERF_SAMPLE_IP)
		perf_output_put(handle, data->ip);

	अगर (sample_type & PERF_SAMPLE_TID)
		perf_output_put(handle, data->tid_entry);

	अगर (sample_type & PERF_SAMPLE_TIME)
		perf_output_put(handle, data->समय);

	अगर (sample_type & PERF_SAMPLE_ADDR)
		perf_output_put(handle, data->addr);

	अगर (sample_type & PERF_SAMPLE_ID)
		perf_output_put(handle, data->id);

	अगर (sample_type & PERF_SAMPLE_STREAM_ID)
		perf_output_put(handle, data->stream_id);

	अगर (sample_type & PERF_SAMPLE_CPU)
		perf_output_put(handle, data->cpu_entry);

	अगर (sample_type & PERF_SAMPLE_PERIOD)
		perf_output_put(handle, data->period);

	अगर (sample_type & PERF_SAMPLE_READ)
		perf_output_पढ़ो(handle, event);

	अगर (sample_type & PERF_SAMPLE_CALLCHAIN) अणु
		पूर्णांक size = 1;

		size += data->callchain->nr;
		size *= माप(u64);
		__output_copy(handle, data->callchain, size);
	पूर्ण

	अगर (sample_type & PERF_SAMPLE_RAW) अणु
		काष्ठा perf_raw_record *raw = data->raw;

		अगर (raw) अणु
			काष्ठा perf_raw_frag *frag = &raw->frag;

			perf_output_put(handle, raw->size);
			करो अणु
				अगर (frag->copy) अणु
					__output_custom(handle, frag->copy,
							frag->data, frag->size);
				पूर्ण अन्यथा अणु
					__output_copy(handle, frag->data,
						      frag->size);
				पूर्ण
				अगर (perf_raw_frag_last(frag))
					अवरोध;
				frag = frag->next;
			पूर्ण जबतक (1);
			अगर (frag->pad)
				__output_skip(handle, शून्य, frag->pad);
		पूर्ण अन्यथा अणु
			काष्ठा अणु
				u32	size;
				u32	data;
			पूर्ण raw = अणु
				.size = माप(u32),
				.data = 0,
			पूर्ण;
			perf_output_put(handle, raw);
		पूर्ण
	पूर्ण

	अगर (sample_type & PERF_SAMPLE_BRANCH_STACK) अणु
		अगर (data->br_stack) अणु
			माप_प्रकार size;

			size = data->br_stack->nr
			     * माप(काष्ठा perf_branch_entry);

			perf_output_put(handle, data->br_stack->nr);
			अगर (perf_sample_save_hw_index(event))
				perf_output_put(handle, data->br_stack->hw_idx);
			perf_output_copy(handle, data->br_stack->entries, size);
		पूर्ण अन्यथा अणु
			/*
			 * we always store at least the value of nr
			 */
			u64 nr = 0;
			perf_output_put(handle, nr);
		पूर्ण
	पूर्ण

	अगर (sample_type & PERF_SAMPLE_REGS_USER) अणु
		u64 abi = data->regs_user.abi;

		/*
		 * If there are no regs to dump, notice it through
		 * first u64 being zero (PERF_SAMPLE_REGS_ABI_NONE).
		 */
		perf_output_put(handle, abi);

		अगर (abi) अणु
			u64 mask = event->attr.sample_regs_user;
			perf_output_sample_regs(handle,
						data->regs_user.regs,
						mask);
		पूर्ण
	पूर्ण

	अगर (sample_type & PERF_SAMPLE_STACK_USER) अणु
		perf_output_sample_ustack(handle,
					  data->stack_user_size,
					  data->regs_user.regs);
	पूर्ण

	अगर (sample_type & PERF_SAMPLE_WEIGHT_TYPE)
		perf_output_put(handle, data->weight.full);

	अगर (sample_type & PERF_SAMPLE_DATA_SRC)
		perf_output_put(handle, data->data_src.val);

	अगर (sample_type & PERF_SAMPLE_TRANSACTION)
		perf_output_put(handle, data->txn);

	अगर (sample_type & PERF_SAMPLE_REGS_INTR) अणु
		u64 abi = data->regs_पूर्णांकr.abi;
		/*
		 * If there are no regs to dump, notice it through
		 * first u64 being zero (PERF_SAMPLE_REGS_ABI_NONE).
		 */
		perf_output_put(handle, abi);

		अगर (abi) अणु
			u64 mask = event->attr.sample_regs_पूर्णांकr;

			perf_output_sample_regs(handle,
						data->regs_पूर्णांकr.regs,
						mask);
		पूर्ण
	पूर्ण

	अगर (sample_type & PERF_SAMPLE_PHYS_ADDR)
		perf_output_put(handle, data->phys_addr);

	अगर (sample_type & PERF_SAMPLE_CGROUP)
		perf_output_put(handle, data->cgroup);

	अगर (sample_type & PERF_SAMPLE_DATA_PAGE_SIZE)
		perf_output_put(handle, data->data_page_size);

	अगर (sample_type & PERF_SAMPLE_CODE_PAGE_SIZE)
		perf_output_put(handle, data->code_page_size);

	अगर (sample_type & PERF_SAMPLE_AUX) अणु
		perf_output_put(handle, data->aux_size);

		अगर (data->aux_size)
			perf_aux_sample_output(event, handle, data);
	पूर्ण

	अगर (!event->attr.watermark) अणु
		पूर्णांक wakeup_events = event->attr.wakeup_events;

		अगर (wakeup_events) अणु
			काष्ठा perf_buffer *rb = handle->rb;
			पूर्णांक events = local_inc_वापस(&rb->events);

			अगर (events >= wakeup_events) अणु
				local_sub(wakeup_events, &rb->events);
				local_inc(&rb->wakeup);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल u64 perf_virt_to_phys(u64 virt)
अणु
	u64 phys_addr = 0;
	काष्ठा page *p = शून्य;

	अगर (!virt)
		वापस 0;

	अगर (virt >= TASK_SIZE) अणु
		/* If it's vदो_स्मृति()d memory, leave phys_addr as 0 */
		अगर (virt_addr_valid((व्योम *)(uपूर्णांकptr_t)virt) &&
		    !(virt >= VMALLOC_START && virt < VMALLOC_END))
			phys_addr = (u64)virt_to_phys((व्योम *)(uपूर्णांकptr_t)virt);
	पूर्ण अन्यथा अणु
		/*
		 * Walking the pages tables क्रम user address.
		 * Interrupts are disabled, so it prevents any tear करोwn
		 * of the page tables.
		 * Try IRQ-safe get_user_page_fast_only first.
		 * If failed, leave phys_addr as 0.
		 */
		अगर (current->mm != शून्य) अणु
			pagefault_disable();
			अगर (get_user_page_fast_only(virt, 0, &p))
				phys_addr = page_to_phys(p) + virt % PAGE_SIZE;
			pagefault_enable();
		पूर्ण

		अगर (p)
			put_page(p);
	पूर्ण

	वापस phys_addr;
पूर्ण

/*
 * Return the pagetable size of a given भव address.
 */
अटल u64 perf_get_pgtable_size(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	u64 size = 0;

#अगर_घोषित CONFIG_HAVE_FAST_GUP
	pgd_t *pgdp, pgd;
	p4d_t *p4dp, p4d;
	pud_t *pudp, pud;
	pmd_t *pmdp, pmd;
	pte_t *ptep, pte;

	pgdp = pgd_offset(mm, addr);
	pgd = READ_ONCE(*pgdp);
	अगर (pgd_none(pgd))
		वापस 0;

	अगर (pgd_leaf(pgd))
		वापस pgd_leaf_size(pgd);

	p4dp = p4d_offset_lockless(pgdp, pgd, addr);
	p4d = READ_ONCE(*p4dp);
	अगर (!p4d_present(p4d))
		वापस 0;

	अगर (p4d_leaf(p4d))
		वापस p4d_leaf_size(p4d);

	pudp = pud_offset_lockless(p4dp, p4d, addr);
	pud = READ_ONCE(*pudp);
	अगर (!pud_present(pud))
		वापस 0;

	अगर (pud_leaf(pud))
		वापस pud_leaf_size(pud);

	pmdp = pmd_offset_lockless(pudp, pud, addr);
	pmd = READ_ONCE(*pmdp);
	अगर (!pmd_present(pmd))
		वापस 0;

	अगर (pmd_leaf(pmd))
		वापस pmd_leaf_size(pmd);

	ptep = pte_offset_map(&pmd, addr);
	pte = ptep_get_lockless(ptep);
	अगर (pte_present(pte))
		size = pte_leaf_size(pte);
	pte_unmap(ptep);
#पूर्ण_अगर /* CONFIG_HAVE_FAST_GUP */

	वापस size;
पूर्ण

अटल u64 perf_get_page_size(अचिन्हित दीर्घ addr)
अणु
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ flags;
	u64 size;

	अगर (!addr)
		वापस 0;

	/*
	 * Software page-table walkers must disable IRQs,
	 * which prevents any tear करोwn of the page tables.
	 */
	local_irq_save(flags);

	mm = current->mm;
	अगर (!mm) अणु
		/*
		 * For kernel thपढ़ोs and the like, use init_mm so that
		 * we can find kernel memory.
		 */
		mm = &init_mm;
	पूर्ण

	size = perf_get_pgtable_size(mm, addr);

	local_irq_restore(flags);

	वापस size;
पूर्ण

अटल काष्ठा perf_callchain_entry __empty_callchain = अणु .nr = 0, पूर्ण;

काष्ठा perf_callchain_entry *
perf_callchain(काष्ठा perf_event *event, काष्ठा pt_regs *regs)
अणु
	bool kernel = !event->attr.exclude_callchain_kernel;
	bool user   = !event->attr.exclude_callchain_user;
	/* Disallow cross-task user callchains. */
	bool crosstask = event->ctx->task && event->ctx->task != current;
	स्थिर u32 max_stack = event->attr.sample_max_stack;
	काष्ठा perf_callchain_entry *callchain;

	अगर (!kernel && !user)
		वापस &__empty_callchain;

	callchain = get_perf_callchain(regs, 0, kernel, user,
				       max_stack, crosstask, true);
	वापस callchain ?: &__empty_callchain;
पूर्ण

व्योम perf_prepare_sample(काष्ठा perf_event_header *header,
			 काष्ठा perf_sample_data *data,
			 काष्ठा perf_event *event,
			 काष्ठा pt_regs *regs)
अणु
	u64 sample_type = event->attr.sample_type;

	header->type = PERF_RECORD_SAMPLE;
	header->size = माप(*header) + event->header_size;

	header->misc = 0;
	header->misc |= perf_misc_flags(regs);

	__perf_event_header__init_id(header, data, event);

	अगर (sample_type & (PERF_SAMPLE_IP | PERF_SAMPLE_CODE_PAGE_SIZE))
		data->ip = perf_inकाष्ठाion_poपूर्णांकer(regs);

	अगर (sample_type & PERF_SAMPLE_CALLCHAIN) अणु
		पूर्णांक size = 1;

		अगर (!(sample_type & __PERF_SAMPLE_CALLCHAIN_EARLY))
			data->callchain = perf_callchain(event, regs);

		size += data->callchain->nr;

		header->size += size * माप(u64);
	पूर्ण

	अगर (sample_type & PERF_SAMPLE_RAW) अणु
		काष्ठा perf_raw_record *raw = data->raw;
		पूर्णांक size;

		अगर (raw) अणु
			काष्ठा perf_raw_frag *frag = &raw->frag;
			u32 sum = 0;

			करो अणु
				sum += frag->size;
				अगर (perf_raw_frag_last(frag))
					अवरोध;
				frag = frag->next;
			पूर्ण जबतक (1);

			size = round_up(sum + माप(u32), माप(u64));
			raw->size = size - माप(u32);
			frag->pad = raw->size - sum;
		पूर्ण अन्यथा अणु
			size = माप(u64);
		पूर्ण

		header->size += size;
	पूर्ण

	अगर (sample_type & PERF_SAMPLE_BRANCH_STACK) अणु
		पूर्णांक size = माप(u64); /* nr */
		अगर (data->br_stack) अणु
			अगर (perf_sample_save_hw_index(event))
				size += माप(u64);

			size += data->br_stack->nr
			      * माप(काष्ठा perf_branch_entry);
		पूर्ण
		header->size += size;
	पूर्ण

	अगर (sample_type & (PERF_SAMPLE_REGS_USER | PERF_SAMPLE_STACK_USER))
		perf_sample_regs_user(&data->regs_user, regs);

	अगर (sample_type & PERF_SAMPLE_REGS_USER) अणु
		/* regs dump ABI info */
		पूर्णांक size = माप(u64);

		अगर (data->regs_user.regs) अणु
			u64 mask = event->attr.sample_regs_user;
			size += hweight64(mask) * माप(u64);
		पूर्ण

		header->size += size;
	पूर्ण

	अगर (sample_type & PERF_SAMPLE_STACK_USER) अणु
		/*
		 * Either we need PERF_SAMPLE_STACK_USER bit to be always
		 * processed as the last one or have additional check added
		 * in हाल new sample type is added, because we could eat
		 * up the rest of the sample size.
		 */
		u16 stack_size = event->attr.sample_stack_user;
		u16 size = माप(u64);

		stack_size = perf_sample_ustack_size(stack_size, header->size,
						     data->regs_user.regs);

		/*
		 * If there is something to dump, add space क्रम the dump
		 * itself and क्रम the field that tells the dynamic size,
		 * which is how many have been actually dumped.
		 */
		अगर (stack_size)
			size += माप(u64) + stack_size;

		data->stack_user_size = stack_size;
		header->size += size;
	पूर्ण

	अगर (sample_type & PERF_SAMPLE_REGS_INTR) अणु
		/* regs dump ABI info */
		पूर्णांक size = माप(u64);

		perf_sample_regs_पूर्णांकr(&data->regs_पूर्णांकr, regs);

		अगर (data->regs_पूर्णांकr.regs) अणु
			u64 mask = event->attr.sample_regs_पूर्णांकr;

			size += hweight64(mask) * माप(u64);
		पूर्ण

		header->size += size;
	पूर्ण

	अगर (sample_type & PERF_SAMPLE_PHYS_ADDR)
		data->phys_addr = perf_virt_to_phys(data->addr);

#अगर_घोषित CONFIG_CGROUP_PERF
	अगर (sample_type & PERF_SAMPLE_CGROUP) अणु
		काष्ठा cgroup *cgrp;

		/* रक्षित by RCU */
		cgrp = task_css_check(current, perf_event_cgrp_id, 1)->cgroup;
		data->cgroup = cgroup_id(cgrp);
	पूर्ण
#पूर्ण_अगर

	/*
	 * PERF_DATA_PAGE_SIZE requires PERF_SAMPLE_ADDR. If the user करोesn't
	 * require PERF_SAMPLE_ADDR, kernel implicitly retrieve the data->addr,
	 * but the value will not dump to the userspace.
	 */
	अगर (sample_type & PERF_SAMPLE_DATA_PAGE_SIZE)
		data->data_page_size = perf_get_page_size(data->addr);

	अगर (sample_type & PERF_SAMPLE_CODE_PAGE_SIZE)
		data->code_page_size = perf_get_page_size(data->ip);

	अगर (sample_type & PERF_SAMPLE_AUX) अणु
		u64 size;

		header->size += माप(u64); /* size */

		/*
		 * Given the 16bit nature of header::size, an AUX sample can
		 * easily overflow it, what with all the preceding sample bits.
		 * Make sure this करोesn't happen by using up to U16_MAX bytes
		 * per sample in total (rounded करोwn to 8 byte boundary).
		 */
		size = min_t(माप_प्रकार, U16_MAX - header->size,
			     event->attr.aux_sample_size);
		size = roundकरोwn(size, 8);
		size = perf_prepare_sample_aux(event, data, size);

		WARN_ON_ONCE(size + header->size > U16_MAX);
		header->size += size;
	पूर्ण
	/*
	 * If you're adding more sample types here, you likely need to करो
	 * something about the overflowing header::size, like repurpose the
	 * lowest 3 bits of size, which should be always zero at the moment.
	 * This उठाओs a more important question, करो we really need 512k sized
	 * samples and why, so good argumentation is in order क्रम whatever you
	 * करो here next.
	 */
	WARN_ON_ONCE(header->size & 7);
पूर्ण

अटल __always_अंतरभूत पूर्णांक
__perf_event_output(काष्ठा perf_event *event,
		    काष्ठा perf_sample_data *data,
		    काष्ठा pt_regs *regs,
		    पूर्णांक (*output_begin)(काष्ठा perf_output_handle *,
					काष्ठा perf_sample_data *,
					काष्ठा perf_event *,
					अचिन्हित पूर्णांक))
अणु
	काष्ठा perf_output_handle handle;
	काष्ठा perf_event_header header;
	पूर्णांक err;

	/* protect the callchain buffers */
	rcu_पढ़ो_lock();

	perf_prepare_sample(&header, data, event, regs);

	err = output_begin(&handle, data, event, header.size);
	अगर (err)
		जाओ निकास;

	perf_output_sample(&handle, &header, data, event);

	perf_output_end(&handle);

निकास:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

व्योम
perf_event_output_क्रमward(काष्ठा perf_event *event,
			 काष्ठा perf_sample_data *data,
			 काष्ठा pt_regs *regs)
अणु
	__perf_event_output(event, data, regs, perf_output_begin_क्रमward);
पूर्ण

व्योम
perf_event_output_backward(काष्ठा perf_event *event,
			   काष्ठा perf_sample_data *data,
			   काष्ठा pt_regs *regs)
अणु
	__perf_event_output(event, data, regs, perf_output_begin_backward);
पूर्ण

पूर्णांक
perf_event_output(काष्ठा perf_event *event,
		  काष्ठा perf_sample_data *data,
		  काष्ठा pt_regs *regs)
अणु
	वापस __perf_event_output(event, data, regs, perf_output_begin);
पूर्ण

/*
 * पढ़ो event_id
 */

काष्ठा perf_पढ़ो_event अणु
	काष्ठा perf_event_header	header;

	u32				pid;
	u32				tid;
पूर्ण;

अटल व्योम
perf_event_पढ़ो_event(काष्ठा perf_event *event,
			काष्ठा task_काष्ठा *task)
अणु
	काष्ठा perf_output_handle handle;
	काष्ठा perf_sample_data sample;
	काष्ठा perf_पढ़ो_event पढ़ो_event = अणु
		.header = अणु
			.type = PERF_RECORD_READ,
			.misc = 0,
			.size = माप(पढ़ो_event) + event->पढ़ो_size,
		पूर्ण,
		.pid = perf_event_pid(event, task),
		.tid = perf_event_tid(event, task),
	पूर्ण;
	पूर्णांक ret;

	perf_event_header__init_id(&पढ़ो_event.header, &sample, event);
	ret = perf_output_begin(&handle, &sample, event, पढ़ो_event.header.size);
	अगर (ret)
		वापस;

	perf_output_put(&handle, पढ़ो_event);
	perf_output_पढ़ो(&handle, event);
	perf_event__output_id_sample(event, &handle, &sample);

	perf_output_end(&handle);
पूर्ण

प्रकार व्योम (perf_iterate_f)(काष्ठा perf_event *event, व्योम *data);

अटल व्योम
perf_iterate_ctx(काष्ठा perf_event_context *ctx,
		   perf_iterate_f output,
		   व्योम *data, bool all)
अणु
	काष्ठा perf_event *event;

	list_क्रम_each_entry_rcu(event, &ctx->event_list, event_entry) अणु
		अगर (!all) अणु
			अगर (event->state < PERF_EVENT_STATE_INACTIVE)
				जारी;
			अगर (!event_filter_match(event))
				जारी;
		पूर्ण

		output(event, data);
	पूर्ण
पूर्ण

अटल व्योम perf_iterate_sb_cpu(perf_iterate_f output, व्योम *data)
अणु
	काष्ठा pmu_event_list *pel = this_cpu_ptr(&pmu_sb_events);
	काष्ठा perf_event *event;

	list_क्रम_each_entry_rcu(event, &pel->list, sb_list) अणु
		/*
		 * Skip events that are not fully क्रमmed yet; ensure that
		 * अगर we observe event->ctx, both event and ctx will be
		 * complete enough. See perf_install_in_context().
		 */
		अगर (!smp_load_acquire(&event->ctx))
			जारी;

		अगर (event->state < PERF_EVENT_STATE_INACTIVE)
			जारी;
		अगर (!event_filter_match(event))
			जारी;
		output(event, data);
	पूर्ण
पूर्ण

/*
 * Iterate all events that need to receive side-band events.
 *
 * For new callers; ensure that account_pmu_sb_event() includes
 * your event, otherwise it might not get delivered.
 */
अटल व्योम
perf_iterate_sb(perf_iterate_f output, व्योम *data,
	       काष्ठा perf_event_context *task_ctx)
अणु
	काष्ठा perf_event_context *ctx;
	पूर्णांक ctxn;

	rcu_पढ़ो_lock();
	preempt_disable();

	/*
	 * If we have task_ctx != शून्य we only notअगरy the task context itself.
	 * The task_ctx is set only क्रम EXIT events beक्रमe releasing task
	 * context.
	 */
	अगर (task_ctx) अणु
		perf_iterate_ctx(task_ctx, output, data, false);
		जाओ करोne;
	पूर्ण

	perf_iterate_sb_cpu(output, data);

	क्रम_each_task_context_nr(ctxn) अणु
		ctx = rcu_dereference(current->perf_event_ctxp[ctxn]);
		अगर (ctx)
			perf_iterate_ctx(ctx, output, data, false);
	पूर्ण
करोne:
	preempt_enable();
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * Clear all file-based filters at exec, they'll have to be
 * re-instated when/अगर these objects are mmapped again.
 */
अटल व्योम perf_event_addr_filters_exec(काष्ठा perf_event *event, व्योम *data)
अणु
	काष्ठा perf_addr_filters_head *अगरh = perf_event_addr_filters(event);
	काष्ठा perf_addr_filter *filter;
	अचिन्हित पूर्णांक restart = 0, count = 0;
	अचिन्हित दीर्घ flags;

	अगर (!has_addr_filter(event))
		वापस;

	raw_spin_lock_irqsave(&अगरh->lock, flags);
	list_क्रम_each_entry(filter, &अगरh->list, entry) अणु
		अगर (filter->path.dentry) अणु
			event->addr_filter_ranges[count].start = 0;
			event->addr_filter_ranges[count].size = 0;
			restart++;
		पूर्ण

		count++;
	पूर्ण

	अगर (restart)
		event->addr_filters_gen++;
	raw_spin_unlock_irqrestore(&अगरh->lock, flags);

	अगर (restart)
		perf_event_stop(event, 1);
पूर्ण

व्योम perf_event_exec(व्योम)
अणु
	काष्ठा perf_event_context *ctx;
	पूर्णांक ctxn;

	क्रम_each_task_context_nr(ctxn) अणु
		perf_event_enable_on_exec(ctxn);
		perf_event_हटाओ_on_exec(ctxn);

		rcu_पढ़ो_lock();
		ctx = rcu_dereference(current->perf_event_ctxp[ctxn]);
		अगर (ctx) अणु
			perf_iterate_ctx(ctx, perf_event_addr_filters_exec,
					 शून्य, true);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

काष्ठा remote_output अणु
	काष्ठा perf_buffer	*rb;
	पूर्णांक			err;
पूर्ण;

अटल व्योम __perf_event_output_stop(काष्ठा perf_event *event, व्योम *data)
अणु
	काष्ठा perf_event *parent = event->parent;
	काष्ठा remote_output *ro = data;
	काष्ठा perf_buffer *rb = ro->rb;
	काष्ठा stop_event_data sd = अणु
		.event	= event,
	पूर्ण;

	अगर (!has_aux(event))
		वापस;

	अगर (!parent)
		parent = event;

	/*
	 * In हाल of inheritance, it will be the parent that links to the
	 * ring-buffer, but it will be the child that's actually using it.
	 *
	 * We are using event::rb to determine अगर the event should be stopped,
	 * however this may race with ring_buffer_attach() (through set_output),
	 * which will make us skip the event that actually needs to be stopped.
	 * So ring_buffer_attach() has to stop an aux event beक्रमe re-assigning
	 * its rb poपूर्णांकer.
	 */
	अगर (rcu_dereference(parent->rb) == rb)
		ro->err = __perf_event_stop(&sd);
पूर्ण

अटल पूर्णांक __perf_pmu_output_stop(व्योम *info)
अणु
	काष्ठा perf_event *event = info;
	काष्ठा pmu *pmu = event->ctx->pmu;
	काष्ठा perf_cpu_context *cpuctx = this_cpu_ptr(pmu->pmu_cpu_context);
	काष्ठा remote_output ro = अणु
		.rb	= event->rb,
	पूर्ण;

	rcu_पढ़ो_lock();
	perf_iterate_ctx(&cpuctx->ctx, __perf_event_output_stop, &ro, false);
	अगर (cpuctx->task_ctx)
		perf_iterate_ctx(cpuctx->task_ctx, __perf_event_output_stop,
				   &ro, false);
	rcu_पढ़ो_unlock();

	वापस ro.err;
पूर्ण

अटल व्योम perf_pmu_output_stop(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event *iter;
	पूर्णांक err, cpu;

restart:
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(iter, &event->rb->event_list, rb_entry) अणु
		/*
		 * For per-CPU events, we need to make sure that neither they
		 * nor their children are running; क्रम cpu==-1 events it's
		 * sufficient to stop the event itself अगर it's active, since
		 * it can't have children.
		 */
		cpu = iter->cpu;
		अगर (cpu == -1)
			cpu = READ_ONCE(iter->oncpu);

		अगर (cpu == -1)
			जारी;

		err = cpu_function_call(cpu, __perf_pmu_output_stop, event);
		अगर (err == -EAGAIN) अणु
			rcu_पढ़ो_unlock();
			जाओ restart;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * task tracking -- विभाजन/निकास
 *
 * enabled by: attr.comm | attr.mmap | attr.mmap2 | attr.mmap_data | attr.task
 */

काष्ठा perf_task_event अणु
	काष्ठा task_काष्ठा		*task;
	काष्ठा perf_event_context	*task_ctx;

	काष्ठा अणु
		काष्ठा perf_event_header	header;

		u32				pid;
		u32				ppid;
		u32				tid;
		u32				ptid;
		u64				समय;
	पूर्ण event_id;
पूर्ण;

अटल पूर्णांक perf_event_task_match(काष्ठा perf_event *event)
अणु
	वापस event->attr.comm  || event->attr.mmap ||
	       event->attr.mmap2 || event->attr.mmap_data ||
	       event->attr.task;
पूर्ण

अटल व्योम perf_event_task_output(काष्ठा perf_event *event,
				   व्योम *data)
अणु
	काष्ठा perf_task_event *task_event = data;
	काष्ठा perf_output_handle handle;
	काष्ठा perf_sample_data	sample;
	काष्ठा task_काष्ठा *task = task_event->task;
	पूर्णांक ret, size = task_event->event_id.header.size;

	अगर (!perf_event_task_match(event))
		वापस;

	perf_event_header__init_id(&task_event->event_id.header, &sample, event);

	ret = perf_output_begin(&handle, &sample, event,
				task_event->event_id.header.size);
	अगर (ret)
		जाओ out;

	task_event->event_id.pid = perf_event_pid(event, task);
	task_event->event_id.tid = perf_event_tid(event, task);

	अगर (task_event->event_id.header.type == PERF_RECORD_EXIT) अणु
		task_event->event_id.ppid = perf_event_pid(event,
							task->real_parent);
		task_event->event_id.ptid = perf_event_pid(event,
							task->real_parent);
	पूर्ण अन्यथा अणु  /* PERF_RECORD_FORK */
		task_event->event_id.ppid = perf_event_pid(event, current);
		task_event->event_id.ptid = perf_event_tid(event, current);
	पूर्ण

	task_event->event_id.समय = perf_event_घड़ी(event);

	perf_output_put(&handle, task_event->event_id);

	perf_event__output_id_sample(event, &handle, &sample);

	perf_output_end(&handle);
out:
	task_event->event_id.header.size = size;
पूर्ण

अटल व्योम perf_event_task(काष्ठा task_काष्ठा *task,
			      काष्ठा perf_event_context *task_ctx,
			      पूर्णांक new)
अणु
	काष्ठा perf_task_event task_event;

	अगर (!atomic_पढ़ो(&nr_comm_events) &&
	    !atomic_पढ़ो(&nr_mmap_events) &&
	    !atomic_पढ़ो(&nr_task_events))
		वापस;

	task_event = (काष्ठा perf_task_event)अणु
		.task	  = task,
		.task_ctx = task_ctx,
		.event_id    = अणु
			.header = अणु
				.type = new ? PERF_RECORD_FORK : PERF_RECORD_EXIT,
				.misc = 0,
				.size = माप(task_event.event_id),
			पूर्ण,
			/* .pid  */
			/* .ppid */
			/* .tid  */
			/* .ptid */
			/* .समय */
		पूर्ण,
	पूर्ण;

	perf_iterate_sb(perf_event_task_output,
		       &task_event,
		       task_ctx);
पूर्ण

व्योम perf_event_विभाजन(काष्ठा task_काष्ठा *task)
अणु
	perf_event_task(task, शून्य, 1);
	perf_event_namespaces(task);
पूर्ण

/*
 * comm tracking
 */

काष्ठा perf_comm_event अणु
	काष्ठा task_काष्ठा	*task;
	अक्षर			*comm;
	पूर्णांक			comm_size;

	काष्ठा अणु
		काष्ठा perf_event_header	header;

		u32				pid;
		u32				tid;
	पूर्ण event_id;
पूर्ण;

अटल पूर्णांक perf_event_comm_match(काष्ठा perf_event *event)
अणु
	वापस event->attr.comm;
पूर्ण

अटल व्योम perf_event_comm_output(काष्ठा perf_event *event,
				   व्योम *data)
अणु
	काष्ठा perf_comm_event *comm_event = data;
	काष्ठा perf_output_handle handle;
	काष्ठा perf_sample_data sample;
	पूर्णांक size = comm_event->event_id.header.size;
	पूर्णांक ret;

	अगर (!perf_event_comm_match(event))
		वापस;

	perf_event_header__init_id(&comm_event->event_id.header, &sample, event);
	ret = perf_output_begin(&handle, &sample, event,
				comm_event->event_id.header.size);

	अगर (ret)
		जाओ out;

	comm_event->event_id.pid = perf_event_pid(event, comm_event->task);
	comm_event->event_id.tid = perf_event_tid(event, comm_event->task);

	perf_output_put(&handle, comm_event->event_id);
	__output_copy(&handle, comm_event->comm,
				   comm_event->comm_size);

	perf_event__output_id_sample(event, &handle, &sample);

	perf_output_end(&handle);
out:
	comm_event->event_id.header.size = size;
पूर्ण

अटल व्योम perf_event_comm_event(काष्ठा perf_comm_event *comm_event)
अणु
	अक्षर comm[TASK_COMM_LEN];
	अचिन्हित पूर्णांक size;

	स_रखो(comm, 0, माप(comm));
	strlcpy(comm, comm_event->task->comm, माप(comm));
	size = ALIGN(म_माप(comm)+1, माप(u64));

	comm_event->comm = comm;
	comm_event->comm_size = size;

	comm_event->event_id.header.size = माप(comm_event->event_id) + size;

	perf_iterate_sb(perf_event_comm_output,
		       comm_event,
		       शून्य);
पूर्ण

व्योम perf_event_comm(काष्ठा task_काष्ठा *task, bool exec)
अणु
	काष्ठा perf_comm_event comm_event;

	अगर (!atomic_पढ़ो(&nr_comm_events))
		वापस;

	comm_event = (काष्ठा perf_comm_event)अणु
		.task	= task,
		/* .comm      */
		/* .comm_size */
		.event_id  = अणु
			.header = अणु
				.type = PERF_RECORD_COMM,
				.misc = exec ? PERF_RECORD_MISC_COMM_EXEC : 0,
				/* .size */
			पूर्ण,
			/* .pid */
			/* .tid */
		पूर्ण,
	पूर्ण;

	perf_event_comm_event(&comm_event);
पूर्ण

/*
 * namespaces tracking
 */

काष्ठा perf_namespaces_event अणु
	काष्ठा task_काष्ठा		*task;

	काष्ठा अणु
		काष्ठा perf_event_header	header;

		u32				pid;
		u32				tid;
		u64				nr_namespaces;
		काष्ठा perf_ns_link_info	link_info[NR_NAMESPACES];
	पूर्ण event_id;
पूर्ण;

अटल पूर्णांक perf_event_namespaces_match(काष्ठा perf_event *event)
अणु
	वापस event->attr.namespaces;
पूर्ण

अटल व्योम perf_event_namespaces_output(काष्ठा perf_event *event,
					 व्योम *data)
अणु
	काष्ठा perf_namespaces_event *namespaces_event = data;
	काष्ठा perf_output_handle handle;
	काष्ठा perf_sample_data sample;
	u16 header_size = namespaces_event->event_id.header.size;
	पूर्णांक ret;

	अगर (!perf_event_namespaces_match(event))
		वापस;

	perf_event_header__init_id(&namespaces_event->event_id.header,
				   &sample, event);
	ret = perf_output_begin(&handle, &sample, event,
				namespaces_event->event_id.header.size);
	अगर (ret)
		जाओ out;

	namespaces_event->event_id.pid = perf_event_pid(event,
							namespaces_event->task);
	namespaces_event->event_id.tid = perf_event_tid(event,
							namespaces_event->task);

	perf_output_put(&handle, namespaces_event->event_id);

	perf_event__output_id_sample(event, &handle, &sample);

	perf_output_end(&handle);
out:
	namespaces_event->event_id.header.size = header_size;
पूर्ण

अटल व्योम perf_fill_ns_link_info(काष्ठा perf_ns_link_info *ns_link_info,
				   काष्ठा task_काष्ठा *task,
				   स्थिर काष्ठा proc_ns_operations *ns_ops)
अणु
	काष्ठा path ns_path;
	काष्ठा inode *ns_inode;
	पूर्णांक error;

	error = ns_get_path(&ns_path, task, ns_ops);
	अगर (!error) अणु
		ns_inode = ns_path.dentry->d_inode;
		ns_link_info->dev = new_encode_dev(ns_inode->i_sb->s_dev);
		ns_link_info->ino = ns_inode->i_ino;
		path_put(&ns_path);
	पूर्ण
पूर्ण

व्योम perf_event_namespaces(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा perf_namespaces_event namespaces_event;
	काष्ठा perf_ns_link_info *ns_link_info;

	अगर (!atomic_पढ़ो(&nr_namespaces_events))
		वापस;

	namespaces_event = (काष्ठा perf_namespaces_event)अणु
		.task	= task,
		.event_id  = अणु
			.header = अणु
				.type = PERF_RECORD_NAMESPACES,
				.misc = 0,
				.size = माप(namespaces_event.event_id),
			पूर्ण,
			/* .pid */
			/* .tid */
			.nr_namespaces = NR_NAMESPACES,
			/* .link_info[NR_NAMESPACES] */
		पूर्ण,
	पूर्ण;

	ns_link_info = namespaces_event.event_id.link_info;

	perf_fill_ns_link_info(&ns_link_info[MNT_NS_INDEX],
			       task, &mntns_operations);

#अगर_घोषित CONFIG_USER_NS
	perf_fill_ns_link_info(&ns_link_info[USER_NS_INDEX],
			       task, &userns_operations);
#पूर्ण_अगर
#अगर_घोषित CONFIG_NET_NS
	perf_fill_ns_link_info(&ns_link_info[NET_NS_INDEX],
			       task, &netns_operations);
#पूर्ण_अगर
#अगर_घोषित CONFIG_UTS_NS
	perf_fill_ns_link_info(&ns_link_info[UTS_NS_INDEX],
			       task, &utsns_operations);
#पूर्ण_अगर
#अगर_घोषित CONFIG_IPC_NS
	perf_fill_ns_link_info(&ns_link_info[IPC_NS_INDEX],
			       task, &ipcns_operations);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PID_NS
	perf_fill_ns_link_info(&ns_link_info[PID_NS_INDEX],
			       task, &pidns_operations);
#पूर्ण_अगर
#अगर_घोषित CONFIG_CGROUPS
	perf_fill_ns_link_info(&ns_link_info[CGROUP_NS_INDEX],
			       task, &cgroupns_operations);
#पूर्ण_अगर

	perf_iterate_sb(perf_event_namespaces_output,
			&namespaces_event,
			शून्य);
पूर्ण

/*
 * cgroup tracking
 */
#अगर_घोषित CONFIG_CGROUP_PERF

काष्ठा perf_cgroup_event अणु
	अक्षर				*path;
	पूर्णांक				path_size;
	काष्ठा अणु
		काष्ठा perf_event_header	header;
		u64				id;
		अक्षर				path[];
	पूर्ण event_id;
पूर्ण;

अटल पूर्णांक perf_event_cgroup_match(काष्ठा perf_event *event)
अणु
	वापस event->attr.cgroup;
पूर्ण

अटल व्योम perf_event_cgroup_output(काष्ठा perf_event *event, व्योम *data)
अणु
	काष्ठा perf_cgroup_event *cgroup_event = data;
	काष्ठा perf_output_handle handle;
	काष्ठा perf_sample_data sample;
	u16 header_size = cgroup_event->event_id.header.size;
	पूर्णांक ret;

	अगर (!perf_event_cgroup_match(event))
		वापस;

	perf_event_header__init_id(&cgroup_event->event_id.header,
				   &sample, event);
	ret = perf_output_begin(&handle, &sample, event,
				cgroup_event->event_id.header.size);
	अगर (ret)
		जाओ out;

	perf_output_put(&handle, cgroup_event->event_id);
	__output_copy(&handle, cgroup_event->path, cgroup_event->path_size);

	perf_event__output_id_sample(event, &handle, &sample);

	perf_output_end(&handle);
out:
	cgroup_event->event_id.header.size = header_size;
पूर्ण

अटल व्योम perf_event_cgroup(काष्ठा cgroup *cgrp)
अणु
	काष्ठा perf_cgroup_event cgroup_event;
	अक्षर path_enomem[16] = "//enomem";
	अक्षर *pathname;
	माप_प्रकार size;

	अगर (!atomic_पढ़ो(&nr_cgroup_events))
		वापस;

	cgroup_event = (काष्ठा perf_cgroup_event)अणु
		.event_id  = अणु
			.header = अणु
				.type = PERF_RECORD_CGROUP,
				.misc = 0,
				.size = माप(cgroup_event.event_id),
			पूर्ण,
			.id = cgroup_id(cgrp),
		पूर्ण,
	पूर्ण;

	pathname = kदो_स्मृति(PATH_MAX, GFP_KERNEL);
	अगर (pathname == शून्य) अणु
		cgroup_event.path = path_enomem;
	पूर्ण अन्यथा अणु
		/* just to be sure to have enough space क्रम alignment */
		cgroup_path(cgrp, pathname, PATH_MAX - माप(u64));
		cgroup_event.path = pathname;
	पूर्ण

	/*
	 * Since our buffer works in 8 byte units we need to align our string
	 * size to a multiple of 8. However, we must guarantee the tail end is
	 * zero'd out to aव्योम leaking अक्रमom bits to userspace.
	 */
	size = म_माप(cgroup_event.path) + 1;
	जबतक (!IS_ALIGNED(size, माप(u64)))
		cgroup_event.path[size++] = '\0';

	cgroup_event.event_id.header.size += size;
	cgroup_event.path_size = size;

	perf_iterate_sb(perf_event_cgroup_output,
			&cgroup_event,
			शून्य);

	kमुक्त(pathname);
पूर्ण

#पूर्ण_अगर

/*
 * mmap tracking
 */

काष्ठा perf_mmap_event अणु
	काष्ठा vm_area_काष्ठा	*vma;

	स्थिर अक्षर		*file_name;
	पूर्णांक			file_size;
	पूर्णांक			maj, min;
	u64			ino;
	u64			ino_generation;
	u32			prot, flags;
	u8			build_id[BUILD_ID_SIZE_MAX];
	u32			build_id_size;

	काष्ठा अणु
		काष्ठा perf_event_header	header;

		u32				pid;
		u32				tid;
		u64				start;
		u64				len;
		u64				pgoff;
	पूर्ण event_id;
पूर्ण;

अटल पूर्णांक perf_event_mmap_match(काष्ठा perf_event *event,
				 व्योम *data)
अणु
	काष्ठा perf_mmap_event *mmap_event = data;
	काष्ठा vm_area_काष्ठा *vma = mmap_event->vma;
	पूर्णांक executable = vma->vm_flags & VM_EXEC;

	वापस (!executable && event->attr.mmap_data) ||
	       (executable && (event->attr.mmap || event->attr.mmap2));
पूर्ण

अटल व्योम perf_event_mmap_output(काष्ठा perf_event *event,
				   व्योम *data)
अणु
	काष्ठा perf_mmap_event *mmap_event = data;
	काष्ठा perf_output_handle handle;
	काष्ठा perf_sample_data sample;
	पूर्णांक size = mmap_event->event_id.header.size;
	u32 type = mmap_event->event_id.header.type;
	bool use_build_id;
	पूर्णांक ret;

	अगर (!perf_event_mmap_match(event, data))
		वापस;

	अगर (event->attr.mmap2) अणु
		mmap_event->event_id.header.type = PERF_RECORD_MMAP2;
		mmap_event->event_id.header.size += माप(mmap_event->maj);
		mmap_event->event_id.header.size += माप(mmap_event->min);
		mmap_event->event_id.header.size += माप(mmap_event->ino);
		mmap_event->event_id.header.size += माप(mmap_event->ino_generation);
		mmap_event->event_id.header.size += माप(mmap_event->prot);
		mmap_event->event_id.header.size += माप(mmap_event->flags);
	पूर्ण

	perf_event_header__init_id(&mmap_event->event_id.header, &sample, event);
	ret = perf_output_begin(&handle, &sample, event,
				mmap_event->event_id.header.size);
	अगर (ret)
		जाओ out;

	mmap_event->event_id.pid = perf_event_pid(event, current);
	mmap_event->event_id.tid = perf_event_tid(event, current);

	use_build_id = event->attr.build_id && mmap_event->build_id_size;

	अगर (event->attr.mmap2 && use_build_id)
		mmap_event->event_id.header.misc |= PERF_RECORD_MISC_MMAP_BUILD_ID;

	perf_output_put(&handle, mmap_event->event_id);

	अगर (event->attr.mmap2) अणु
		अगर (use_build_id) अणु
			u8 size[4] = अणु (u8) mmap_event->build_id_size, 0, 0, 0 पूर्ण;

			__output_copy(&handle, size, 4);
			__output_copy(&handle, mmap_event->build_id, BUILD_ID_SIZE_MAX);
		पूर्ण अन्यथा अणु
			perf_output_put(&handle, mmap_event->maj);
			perf_output_put(&handle, mmap_event->min);
			perf_output_put(&handle, mmap_event->ino);
			perf_output_put(&handle, mmap_event->ino_generation);
		पूर्ण
		perf_output_put(&handle, mmap_event->prot);
		perf_output_put(&handle, mmap_event->flags);
	पूर्ण

	__output_copy(&handle, mmap_event->file_name,
				   mmap_event->file_size);

	perf_event__output_id_sample(event, &handle, &sample);

	perf_output_end(&handle);
out:
	mmap_event->event_id.header.size = size;
	mmap_event->event_id.header.type = type;
पूर्ण

अटल व्योम perf_event_mmap_event(काष्ठा perf_mmap_event *mmap_event)
अणु
	काष्ठा vm_area_काष्ठा *vma = mmap_event->vma;
	काष्ठा file *file = vma->vm_file;
	पूर्णांक maj = 0, min = 0;
	u64 ino = 0, gen = 0;
	u32 prot = 0, flags = 0;
	अचिन्हित पूर्णांक size;
	अक्षर पंचांगp[16];
	अक्षर *buf = शून्य;
	अक्षर *name;

	अगर (vma->vm_flags & VM_READ)
		prot |= PROT_READ;
	अगर (vma->vm_flags & VM_WRITE)
		prot |= PROT_WRITE;
	अगर (vma->vm_flags & VM_EXEC)
		prot |= PROT_EXEC;

	अगर (vma->vm_flags & VM_MAYSHARE)
		flags = MAP_SHARED;
	अन्यथा
		flags = MAP_PRIVATE;

	अगर (vma->vm_flags & VM_DENYWRITE)
		flags |= MAP_DENYWRITE;
	अगर (vma->vm_flags & VM_MAYEXEC)
		flags |= MAP_EXECUTABLE;
	अगर (vma->vm_flags & VM_LOCKED)
		flags |= MAP_LOCKED;
	अगर (is_vm_hugetlb_page(vma))
		flags |= MAP_HUGETLB;

	अगर (file) अणु
		काष्ठा inode *inode;
		dev_t dev;

		buf = kदो_स्मृति(PATH_MAX, GFP_KERNEL);
		अगर (!buf) अणु
			name = "//enomem";
			जाओ cpy_name;
		पूर्ण
		/*
		 * d_path() works from the end of the rb backwards, so we
		 * need to add enough zero bytes after the string to handle
		 * the 64bit alignment we करो later.
		 */
		name = file_path(file, buf, PATH_MAX - माप(u64));
		अगर (IS_ERR(name)) अणु
			name = "//toolong";
			जाओ cpy_name;
		पूर्ण
		inode = file_inode(vma->vm_file);
		dev = inode->i_sb->s_dev;
		ino = inode->i_ino;
		gen = inode->i_generation;
		maj = MAJOR(dev);
		min = MINOR(dev);

		जाओ got_name;
	पूर्ण अन्यथा अणु
		अगर (vma->vm_ops && vma->vm_ops->name) अणु
			name = (अक्षर *) vma->vm_ops->name(vma);
			अगर (name)
				जाओ cpy_name;
		पूर्ण

		name = (अक्षर *)arch_vma_name(vma);
		अगर (name)
			जाओ cpy_name;

		अगर (vma->vm_start <= vma->vm_mm->start_brk &&
				vma->vm_end >= vma->vm_mm->brk) अणु
			name = "[heap]";
			जाओ cpy_name;
		पूर्ण
		अगर (vma->vm_start <= vma->vm_mm->start_stack &&
				vma->vm_end >= vma->vm_mm->start_stack) अणु
			name = "[stack]";
			जाओ cpy_name;
		पूर्ण

		name = "//anon";
		जाओ cpy_name;
	पूर्ण

cpy_name:
	strlcpy(पंचांगp, name, माप(पंचांगp));
	name = पंचांगp;
got_name:
	/*
	 * Since our buffer works in 8 byte units we need to align our string
	 * size to a multiple of 8. However, we must guarantee the tail end is
	 * zero'd out to aव्योम leaking अक्रमom bits to userspace.
	 */
	size = म_माप(name)+1;
	जबतक (!IS_ALIGNED(size, माप(u64)))
		name[size++] = '\0';

	mmap_event->file_name = name;
	mmap_event->file_size = size;
	mmap_event->maj = maj;
	mmap_event->min = min;
	mmap_event->ino = ino;
	mmap_event->ino_generation = gen;
	mmap_event->prot = prot;
	mmap_event->flags = flags;

	अगर (!(vma->vm_flags & VM_EXEC))
		mmap_event->event_id.header.misc |= PERF_RECORD_MISC_MMAP_DATA;

	mmap_event->event_id.header.size = माप(mmap_event->event_id) + size;

	अगर (atomic_पढ़ो(&nr_build_id_events))
		build_id_parse(vma, mmap_event->build_id, &mmap_event->build_id_size);

	perf_iterate_sb(perf_event_mmap_output,
		       mmap_event,
		       शून्य);

	kमुक्त(buf);
पूर्ण

/*
 * Check whether inode and address range match filter criteria.
 */
अटल bool perf_addr_filter_match(काष्ठा perf_addr_filter *filter,
				     काष्ठा file *file, अचिन्हित दीर्घ offset,
				     अचिन्हित दीर्घ size)
अणु
	/* d_inode(शून्य) won't be equal to any mapped user-space file */
	अगर (!filter->path.dentry)
		वापस false;

	अगर (d_inode(filter->path.dentry) != file_inode(file))
		वापस false;

	अगर (filter->offset > offset + size)
		वापस false;

	अगर (filter->offset + filter->size < offset)
		वापस false;

	वापस true;
पूर्ण

अटल bool perf_addr_filter_vma_adjust(काष्ठा perf_addr_filter *filter,
					काष्ठा vm_area_काष्ठा *vma,
					काष्ठा perf_addr_filter_range *fr)
अणु
	अचिन्हित दीर्घ vma_size = vma->vm_end - vma->vm_start;
	अचिन्हित दीर्घ off = vma->vm_pgoff << PAGE_SHIFT;
	काष्ठा file *file = vma->vm_file;

	अगर (!perf_addr_filter_match(filter, file, off, vma_size))
		वापस false;

	अगर (filter->offset < off) अणु
		fr->start = vma->vm_start;
		fr->size = min(vma_size, filter->size - (off - filter->offset));
	पूर्ण अन्यथा अणु
		fr->start = vma->vm_start + filter->offset - off;
		fr->size = min(vma->vm_end - fr->start, filter->size);
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम __perf_addr_filters_adjust(काष्ठा perf_event *event, व्योम *data)
अणु
	काष्ठा perf_addr_filters_head *अगरh = perf_event_addr_filters(event);
	काष्ठा vm_area_काष्ठा *vma = data;
	काष्ठा perf_addr_filter *filter;
	अचिन्हित पूर्णांक restart = 0, count = 0;
	अचिन्हित दीर्घ flags;

	अगर (!has_addr_filter(event))
		वापस;

	अगर (!vma->vm_file)
		वापस;

	raw_spin_lock_irqsave(&अगरh->lock, flags);
	list_क्रम_each_entry(filter, &अगरh->list, entry) अणु
		अगर (perf_addr_filter_vma_adjust(filter, vma,
						&event->addr_filter_ranges[count]))
			restart++;

		count++;
	पूर्ण

	अगर (restart)
		event->addr_filters_gen++;
	raw_spin_unlock_irqrestore(&अगरh->lock, flags);

	अगर (restart)
		perf_event_stop(event, 1);
पूर्ण

/*
 * Adjust all task's events' filters to the new vma
 */
अटल व्योम perf_addr_filters_adjust(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा perf_event_context *ctx;
	पूर्णांक ctxn;

	/*
	 * Data tracing isn't supported yet and as such there is no need
	 * to keep track of anything that isn't related to executable code:
	 */
	अगर (!(vma->vm_flags & VM_EXEC))
		वापस;

	rcu_पढ़ो_lock();
	क्रम_each_task_context_nr(ctxn) अणु
		ctx = rcu_dereference(current->perf_event_ctxp[ctxn]);
		अगर (!ctx)
			जारी;

		perf_iterate_ctx(ctx, __perf_addr_filters_adjust, vma, true);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

व्योम perf_event_mmap(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा perf_mmap_event mmap_event;

	अगर (!atomic_पढ़ो(&nr_mmap_events))
		वापस;

	mmap_event = (काष्ठा perf_mmap_event)अणु
		.vma	= vma,
		/* .file_name */
		/* .file_size */
		.event_id  = अणु
			.header = अणु
				.type = PERF_RECORD_MMAP,
				.misc = PERF_RECORD_MISC_USER,
				/* .size */
			पूर्ण,
			/* .pid */
			/* .tid */
			.start  = vma->vm_start,
			.len    = vma->vm_end - vma->vm_start,
			.pgoff  = (u64)vma->vm_pgoff << PAGE_SHIFT,
		पूर्ण,
		/* .maj (attr_mmap2 only) */
		/* .min (attr_mmap2 only) */
		/* .ino (attr_mmap2 only) */
		/* .ino_generation (attr_mmap2 only) */
		/* .prot (attr_mmap2 only) */
		/* .flags (attr_mmap2 only) */
	पूर्ण;

	perf_addr_filters_adjust(vma);
	perf_event_mmap_event(&mmap_event);
पूर्ण

व्योम perf_event_aux_event(काष्ठा perf_event *event, अचिन्हित दीर्घ head,
			  अचिन्हित दीर्घ size, u64 flags)
अणु
	काष्ठा perf_output_handle handle;
	काष्ठा perf_sample_data sample;
	काष्ठा perf_aux_event अणु
		काष्ठा perf_event_header	header;
		u64				offset;
		u64				size;
		u64				flags;
	पूर्ण rec = अणु
		.header = अणु
			.type = PERF_RECORD_AUX,
			.misc = 0,
			.size = माप(rec),
		पूर्ण,
		.offset		= head,
		.size		= size,
		.flags		= flags,
	पूर्ण;
	पूर्णांक ret;

	perf_event_header__init_id(&rec.header, &sample, event);
	ret = perf_output_begin(&handle, &sample, event, rec.header.size);

	अगर (ret)
		वापस;

	perf_output_put(&handle, rec);
	perf_event__output_id_sample(event, &handle, &sample);

	perf_output_end(&handle);
पूर्ण

/*
 * Lost/dropped samples logging
 */
व्योम perf_log_lost_samples(काष्ठा perf_event *event, u64 lost)
अणु
	काष्ठा perf_output_handle handle;
	काष्ठा perf_sample_data sample;
	पूर्णांक ret;

	काष्ठा अणु
		काष्ठा perf_event_header	header;
		u64				lost;
	पूर्ण lost_samples_event = अणु
		.header = अणु
			.type = PERF_RECORD_LOST_SAMPLES,
			.misc = 0,
			.size = माप(lost_samples_event),
		पूर्ण,
		.lost		= lost,
	पूर्ण;

	perf_event_header__init_id(&lost_samples_event.header, &sample, event);

	ret = perf_output_begin(&handle, &sample, event,
				lost_samples_event.header.size);
	अगर (ret)
		वापस;

	perf_output_put(&handle, lost_samples_event);
	perf_event__output_id_sample(event, &handle, &sample);
	perf_output_end(&handle);
पूर्ण

/*
 * context_चयन tracking
 */

काष्ठा perf_चयन_event अणु
	काष्ठा task_काष्ठा	*task;
	काष्ठा task_काष्ठा	*next_prev;

	काष्ठा अणु
		काष्ठा perf_event_header	header;
		u32				next_prev_pid;
		u32				next_prev_tid;
	पूर्ण event_id;
पूर्ण;

अटल पूर्णांक perf_event_चयन_match(काष्ठा perf_event *event)
अणु
	वापस event->attr.context_चयन;
पूर्ण

अटल व्योम perf_event_चयन_output(काष्ठा perf_event *event, व्योम *data)
अणु
	काष्ठा perf_चयन_event *se = data;
	काष्ठा perf_output_handle handle;
	काष्ठा perf_sample_data sample;
	पूर्णांक ret;

	अगर (!perf_event_चयन_match(event))
		वापस;

	/* Only CPU-wide events are allowed to see next/prev pid/tid */
	अगर (event->ctx->task) अणु
		se->event_id.header.type = PERF_RECORD_SWITCH;
		se->event_id.header.size = माप(se->event_id.header);
	पूर्ण अन्यथा अणु
		se->event_id.header.type = PERF_RECORD_SWITCH_CPU_WIDE;
		se->event_id.header.size = माप(se->event_id);
		se->event_id.next_prev_pid =
					perf_event_pid(event, se->next_prev);
		se->event_id.next_prev_tid =
					perf_event_tid(event, se->next_prev);
	पूर्ण

	perf_event_header__init_id(&se->event_id.header, &sample, event);

	ret = perf_output_begin(&handle, &sample, event, se->event_id.header.size);
	अगर (ret)
		वापस;

	अगर (event->ctx->task)
		perf_output_put(&handle, se->event_id.header);
	अन्यथा
		perf_output_put(&handle, se->event_id);

	perf_event__output_id_sample(event, &handle, &sample);

	perf_output_end(&handle);
पूर्ण

अटल व्योम perf_event_चयन(काष्ठा task_काष्ठा *task,
			      काष्ठा task_काष्ठा *next_prev, bool sched_in)
अणु
	काष्ठा perf_चयन_event चयन_event;

	/* N.B. caller checks nr_चयन_events != 0 */

	चयन_event = (काष्ठा perf_चयन_event)अणु
		.task		= task,
		.next_prev	= next_prev,
		.event_id	= अणु
			.header = अणु
				/* .type */
				.misc = sched_in ? 0 : PERF_RECORD_MISC_SWITCH_OUT,
				/* .size */
			पूर्ण,
			/* .next_prev_pid */
			/* .next_prev_tid */
		पूर्ण,
	पूर्ण;

	अगर (!sched_in && task->state == TASK_RUNNING)
		चयन_event.event_id.header.misc |=
				PERF_RECORD_MISC_SWITCH_OUT_PREEMPT;

	perf_iterate_sb(perf_event_चयन_output,
		       &चयन_event,
		       शून्य);
पूर्ण

/*
 * IRQ throttle logging
 */

अटल व्योम perf_log_throttle(काष्ठा perf_event *event, पूर्णांक enable)
अणु
	काष्ठा perf_output_handle handle;
	काष्ठा perf_sample_data sample;
	पूर्णांक ret;

	काष्ठा अणु
		काष्ठा perf_event_header	header;
		u64				समय;
		u64				id;
		u64				stream_id;
	पूर्ण throttle_event = अणु
		.header = अणु
			.type = PERF_RECORD_THROTTLE,
			.misc = 0,
			.size = माप(throttle_event),
		पूर्ण,
		.समय		= perf_event_घड़ी(event),
		.id		= primary_event_id(event),
		.stream_id	= event->id,
	पूर्ण;

	अगर (enable)
		throttle_event.header.type = PERF_RECORD_UNTHROTTLE;

	perf_event_header__init_id(&throttle_event.header, &sample, event);

	ret = perf_output_begin(&handle, &sample, event,
				throttle_event.header.size);
	अगर (ret)
		वापस;

	perf_output_put(&handle, throttle_event);
	perf_event__output_id_sample(event, &handle, &sample);
	perf_output_end(&handle);
पूर्ण

/*
 * ksymbol रेजिस्टर/unरेजिस्टर tracking
 */

काष्ठा perf_ksymbol_event अणु
	स्थिर अक्षर	*name;
	पूर्णांक		name_len;
	काष्ठा अणु
		काष्ठा perf_event_header        header;
		u64				addr;
		u32				len;
		u16				ksym_type;
		u16				flags;
	पूर्ण event_id;
पूर्ण;

अटल पूर्णांक perf_event_ksymbol_match(काष्ठा perf_event *event)
अणु
	वापस event->attr.ksymbol;
पूर्ण

अटल व्योम perf_event_ksymbol_output(काष्ठा perf_event *event, व्योम *data)
अणु
	काष्ठा perf_ksymbol_event *ksymbol_event = data;
	काष्ठा perf_output_handle handle;
	काष्ठा perf_sample_data sample;
	पूर्णांक ret;

	अगर (!perf_event_ksymbol_match(event))
		वापस;

	perf_event_header__init_id(&ksymbol_event->event_id.header,
				   &sample, event);
	ret = perf_output_begin(&handle, &sample, event,
				ksymbol_event->event_id.header.size);
	अगर (ret)
		वापस;

	perf_output_put(&handle, ksymbol_event->event_id);
	__output_copy(&handle, ksymbol_event->name, ksymbol_event->name_len);
	perf_event__output_id_sample(event, &handle, &sample);

	perf_output_end(&handle);
पूर्ण

व्योम perf_event_ksymbol(u16 ksym_type, u64 addr, u32 len, bool unरेजिस्टर,
			स्थिर अक्षर *sym)
अणु
	काष्ठा perf_ksymbol_event ksymbol_event;
	अक्षर name[KSYM_NAME_LEN];
	u16 flags = 0;
	पूर्णांक name_len;

	अगर (!atomic_पढ़ो(&nr_ksymbol_events))
		वापस;

	अगर (ksym_type >= PERF_RECORD_KSYMBOL_TYPE_MAX ||
	    ksym_type == PERF_RECORD_KSYMBOL_TYPE_UNKNOWN)
		जाओ err;

	strlcpy(name, sym, KSYM_NAME_LEN);
	name_len = म_माप(name) + 1;
	जबतक (!IS_ALIGNED(name_len, माप(u64)))
		name[name_len++] = '\0';
	BUILD_BUG_ON(KSYM_NAME_LEN % माप(u64));

	अगर (unरेजिस्टर)
		flags |= PERF_RECORD_KSYMBOL_FLAGS_UNREGISTER;

	ksymbol_event = (काष्ठा perf_ksymbol_event)अणु
		.name = name,
		.name_len = name_len,
		.event_id = अणु
			.header = अणु
				.type = PERF_RECORD_KSYMBOL,
				.size = माप(ksymbol_event.event_id) +
					name_len,
			पूर्ण,
			.addr = addr,
			.len = len,
			.ksym_type = ksym_type,
			.flags = flags,
		पूर्ण,
	पूर्ण;

	perf_iterate_sb(perf_event_ksymbol_output, &ksymbol_event, शून्य);
	वापस;
err:
	WARN_ONCE(1, "%s: Invalid KSYMBOL type 0x%x\n", __func__, ksym_type);
पूर्ण

/*
 * bpf program load/unload tracking
 */

काष्ठा perf_bpf_event अणु
	काष्ठा bpf_prog	*prog;
	काष्ठा अणु
		काष्ठा perf_event_header        header;
		u16				type;
		u16				flags;
		u32				id;
		u8				tag[BPF_TAG_SIZE];
	पूर्ण event_id;
पूर्ण;

अटल पूर्णांक perf_event_bpf_match(काष्ठा perf_event *event)
अणु
	वापस event->attr.bpf_event;
पूर्ण

अटल व्योम perf_event_bpf_output(काष्ठा perf_event *event, व्योम *data)
अणु
	काष्ठा perf_bpf_event *bpf_event = data;
	काष्ठा perf_output_handle handle;
	काष्ठा perf_sample_data sample;
	पूर्णांक ret;

	अगर (!perf_event_bpf_match(event))
		वापस;

	perf_event_header__init_id(&bpf_event->event_id.header,
				   &sample, event);
	ret = perf_output_begin(&handle, data, event,
				bpf_event->event_id.header.size);
	अगर (ret)
		वापस;

	perf_output_put(&handle, bpf_event->event_id);
	perf_event__output_id_sample(event, &handle, &sample);

	perf_output_end(&handle);
पूर्ण

अटल व्योम perf_event_bpf_emit_ksymbols(काष्ठा bpf_prog *prog,
					 क्रमागत perf_bpf_event_type type)
अणु
	bool unरेजिस्टर = type == PERF_BPF_EVENT_PROG_UNLOAD;
	पूर्णांक i;

	अगर (prog->aux->func_cnt == 0) अणु
		perf_event_ksymbol(PERF_RECORD_KSYMBOL_TYPE_BPF,
				   (u64)(अचिन्हित दीर्घ)prog->bpf_func,
				   prog->jited_len, unरेजिस्टर,
				   prog->aux->ksym.name);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < prog->aux->func_cnt; i++) अणु
			काष्ठा bpf_prog *subprog = prog->aux->func[i];

			perf_event_ksymbol(
				PERF_RECORD_KSYMBOL_TYPE_BPF,
				(u64)(अचिन्हित दीर्घ)subprog->bpf_func,
				subprog->jited_len, unरेजिस्टर,
				prog->aux->ksym.name);
		पूर्ण
	पूर्ण
पूर्ण

व्योम perf_event_bpf_event(काष्ठा bpf_prog *prog,
			  क्रमागत perf_bpf_event_type type,
			  u16 flags)
अणु
	काष्ठा perf_bpf_event bpf_event;

	अगर (type <= PERF_BPF_EVENT_UNKNOWN ||
	    type >= PERF_BPF_EVENT_MAX)
		वापस;

	चयन (type) अणु
	हाल PERF_BPF_EVENT_PROG_LOAD:
	हाल PERF_BPF_EVENT_PROG_UNLOAD:
		अगर (atomic_पढ़ो(&nr_ksymbol_events))
			perf_event_bpf_emit_ksymbols(prog, type);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!atomic_पढ़ो(&nr_bpf_events))
		वापस;

	bpf_event = (काष्ठा perf_bpf_event)अणु
		.prog = prog,
		.event_id = अणु
			.header = अणु
				.type = PERF_RECORD_BPF_EVENT,
				.size = माप(bpf_event.event_id),
			पूर्ण,
			.type = type,
			.flags = flags,
			.id = prog->aux->id,
		पूर्ण,
	पूर्ण;

	BUILD_BUG_ON(BPF_TAG_SIZE % माप(u64));

	स_नकल(bpf_event.event_id.tag, prog->tag, BPF_TAG_SIZE);
	perf_iterate_sb(perf_event_bpf_output, &bpf_event, शून्य);
पूर्ण

काष्ठा perf_text_poke_event अणु
	स्थिर व्योम		*old_bytes;
	स्थिर व्योम		*new_bytes;
	माप_प्रकार			pad;
	u16			old_len;
	u16			new_len;

	काष्ठा अणु
		काष्ठा perf_event_header	header;

		u64				addr;
	पूर्ण event_id;
पूर्ण;

अटल पूर्णांक perf_event_text_poke_match(काष्ठा perf_event *event)
अणु
	वापस event->attr.text_poke;
पूर्ण

अटल व्योम perf_event_text_poke_output(काष्ठा perf_event *event, व्योम *data)
अणु
	काष्ठा perf_text_poke_event *text_poke_event = data;
	काष्ठा perf_output_handle handle;
	काष्ठा perf_sample_data sample;
	u64 padding = 0;
	पूर्णांक ret;

	अगर (!perf_event_text_poke_match(event))
		वापस;

	perf_event_header__init_id(&text_poke_event->event_id.header, &sample, event);

	ret = perf_output_begin(&handle, &sample, event,
				text_poke_event->event_id.header.size);
	अगर (ret)
		वापस;

	perf_output_put(&handle, text_poke_event->event_id);
	perf_output_put(&handle, text_poke_event->old_len);
	perf_output_put(&handle, text_poke_event->new_len);

	__output_copy(&handle, text_poke_event->old_bytes, text_poke_event->old_len);
	__output_copy(&handle, text_poke_event->new_bytes, text_poke_event->new_len);

	अगर (text_poke_event->pad)
		__output_copy(&handle, &padding, text_poke_event->pad);

	perf_event__output_id_sample(event, &handle, &sample);

	perf_output_end(&handle);
पूर्ण

व्योम perf_event_text_poke(स्थिर व्योम *addr, स्थिर व्योम *old_bytes,
			  माप_प्रकार old_len, स्थिर व्योम *new_bytes, माप_प्रकार new_len)
अणु
	काष्ठा perf_text_poke_event text_poke_event;
	माप_प्रकार tot, pad;

	अगर (!atomic_पढ़ो(&nr_text_poke_events))
		वापस;

	tot  = माप(text_poke_event.old_len) + old_len;
	tot += माप(text_poke_event.new_len) + new_len;
	pad  = ALIGN(tot, माप(u64)) - tot;

	text_poke_event = (काष्ठा perf_text_poke_event)अणु
		.old_bytes    = old_bytes,
		.new_bytes    = new_bytes,
		.pad          = pad,
		.old_len      = old_len,
		.new_len      = new_len,
		.event_id  = अणु
			.header = अणु
				.type = PERF_RECORD_TEXT_POKE,
				.misc = PERF_RECORD_MISC_KERNEL,
				.size = माप(text_poke_event.event_id) + tot + pad,
			पूर्ण,
			.addr = (अचिन्हित दीर्घ)addr,
		पूर्ण,
	पूर्ण;

	perf_iterate_sb(perf_event_text_poke_output, &text_poke_event, शून्य);
पूर्ण

व्योम perf_event_itrace_started(काष्ठा perf_event *event)
अणु
	event->attach_state |= PERF_ATTACH_ITRACE;
पूर्ण

अटल व्योम perf_log_itrace_start(काष्ठा perf_event *event)
अणु
	काष्ठा perf_output_handle handle;
	काष्ठा perf_sample_data sample;
	काष्ठा perf_aux_event अणु
		काष्ठा perf_event_header        header;
		u32				pid;
		u32				tid;
	पूर्ण rec;
	पूर्णांक ret;

	अगर (event->parent)
		event = event->parent;

	अगर (!(event->pmu->capabilities & PERF_PMU_CAP_ITRACE) ||
	    event->attach_state & PERF_ATTACH_ITRACE)
		वापस;

	rec.header.type	= PERF_RECORD_ITRACE_START;
	rec.header.misc	= 0;
	rec.header.size	= माप(rec);
	rec.pid	= perf_event_pid(event, current);
	rec.tid	= perf_event_tid(event, current);

	perf_event_header__init_id(&rec.header, &sample, event);
	ret = perf_output_begin(&handle, &sample, event, rec.header.size);

	अगर (ret)
		वापस;

	perf_output_put(&handle, rec);
	perf_event__output_id_sample(event, &handle, &sample);

	perf_output_end(&handle);
पूर्ण

अटल पूर्णांक
__perf_event_account_पूर्णांकerrupt(काष्ठा perf_event *event, पूर्णांक throttle)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक ret = 0;
	u64 seq;

	seq = __this_cpu_पढ़ो(perf_throttled_seq);
	अगर (seq != hwc->पूर्णांकerrupts_seq) अणु
		hwc->पूर्णांकerrupts_seq = seq;
		hwc->पूर्णांकerrupts = 1;
	पूर्ण अन्यथा अणु
		hwc->पूर्णांकerrupts++;
		अगर (unlikely(throttle
			     && hwc->पूर्णांकerrupts >= max_samples_per_tick)) अणु
			__this_cpu_inc(perf_throttled_count);
			tick_dep_set_cpu(smp_processor_id(), TICK_DEP_BIT_PERF_EVENTS);
			hwc->पूर्णांकerrupts = MAX_INTERRUPTS;
			perf_log_throttle(event, 0);
			ret = 1;
		पूर्ण
	पूर्ण

	अगर (event->attr.freq) अणु
		u64 now = perf_घड़ी();
		s64 delta = now - hwc->freq_समय_stamp;

		hwc->freq_समय_stamp = now;

		अगर (delta > 0 && delta < 2*TICK_NSEC)
			perf_adjust_period(event, delta, hwc->last_period, true);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक perf_event_account_पूर्णांकerrupt(काष्ठा perf_event *event)
अणु
	वापस __perf_event_account_पूर्णांकerrupt(event, 1);
पूर्ण

/*
 * Generic event overflow handling, sampling.
 */

अटल पूर्णांक __perf_event_overflow(काष्ठा perf_event *event,
				   पूर्णांक throttle, काष्ठा perf_sample_data *data,
				   काष्ठा pt_regs *regs)
अणु
	पूर्णांक events = atomic_पढ़ो(&event->event_limit);
	पूर्णांक ret = 0;

	/*
	 * Non-sampling counters might still use the PMI to fold लघु
	 * hardware counters, ignore those.
	 */
	अगर (unlikely(!is_sampling_event(event)))
		वापस 0;

	ret = __perf_event_account_पूर्णांकerrupt(event, throttle);

	/*
	 * XXX event_limit might not quite work as expected on inherited
	 * events
	 */

	event->pending_समाप्त = POLL_IN;
	अगर (events && atomic_dec_and_test(&event->event_limit)) अणु
		ret = 1;
		event->pending_समाप्त = POLL_HUP;
		event->pending_addr = data->addr;

		perf_event_disable_inatomic(event);
	पूर्ण

	READ_ONCE(event->overflow_handler)(event, data, regs);

	अगर (*perf_event_fasync(event) && event->pending_समाप्त) अणु
		event->pending_wakeup = 1;
		irq_work_queue(&event->pending);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक perf_event_overflow(काष्ठा perf_event *event,
			  काष्ठा perf_sample_data *data,
			  काष्ठा pt_regs *regs)
अणु
	वापस __perf_event_overflow(event, 1, data, regs);
पूर्ण

/*
 * Generic software event infraकाष्ठाure
 */

काष्ठा swevent_htable अणु
	काष्ठा swevent_hlist		*swevent_hlist;
	काष्ठा mutex			hlist_mutex;
	पूर्णांक				hlist_refcount;

	/* Recursion aव्योमance in each contexts */
	पूर्णांक				recursion[PERF_NR_CONTEXTS];
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा swevent_htable, swevent_htable);

/*
 * We directly increment event->count and keep a second value in
 * event->hw.period_left to count पूर्णांकervals. This period event
 * is kept in the range [-sample_period, 0] so that we can use the
 * sign as trigger.
 */

u64 perf_swevent_set_period(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 period = hwc->last_period;
	u64 nr, offset;
	s64 old, val;

	hwc->last_period = hwc->sample_period;

again:
	old = val = local64_पढ़ो(&hwc->period_left);
	अगर (val < 0)
		वापस 0;

	nr = भाग64_u64(period + val, period);
	offset = nr * period;
	val -= offset;
	अगर (local64_cmpxchg(&hwc->period_left, old, val) != old)
		जाओ again;

	वापस nr;
पूर्ण

अटल व्योम perf_swevent_overflow(काष्ठा perf_event *event, u64 overflow,
				    काष्ठा perf_sample_data *data,
				    काष्ठा pt_regs *regs)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक throttle = 0;

	अगर (!overflow)
		overflow = perf_swevent_set_period(event);

	अगर (hwc->पूर्णांकerrupts == MAX_INTERRUPTS)
		वापस;

	क्रम (; overflow; overflow--) अणु
		अगर (__perf_event_overflow(event, throttle,
					    data, regs)) अणु
			/*
			 * We inhibit the overflow from happening when
			 * hwc->पूर्णांकerrupts == MAX_INTERRUPTS.
			 */
			अवरोध;
		पूर्ण
		throttle = 1;
	पूर्ण
पूर्ण

अटल व्योम perf_swevent_event(काष्ठा perf_event *event, u64 nr,
			       काष्ठा perf_sample_data *data,
			       काष्ठा pt_regs *regs)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	local64_add(nr, &event->count);

	अगर (!regs)
		वापस;

	अगर (!is_sampling_event(event))
		वापस;

	अगर ((event->attr.sample_type & PERF_SAMPLE_PERIOD) && !event->attr.freq) अणु
		data->period = nr;
		वापस perf_swevent_overflow(event, 1, data, regs);
	पूर्ण अन्यथा
		data->period = event->hw.last_period;

	अगर (nr == 1 && hwc->sample_period == 1 && !event->attr.freq)
		वापस perf_swevent_overflow(event, 1, data, regs);

	अगर (local64_add_negative(nr, &hwc->period_left))
		वापस;

	perf_swevent_overflow(event, 0, data, regs);
पूर्ण

अटल पूर्णांक perf_exclude_event(काष्ठा perf_event *event,
			      काष्ठा pt_regs *regs)
अणु
	अगर (event->hw.state & PERF_HES_STOPPED)
		वापस 1;

	अगर (regs) अणु
		अगर (event->attr.exclude_user && user_mode(regs))
			वापस 1;

		अगर (event->attr.exclude_kernel && !user_mode(regs))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक perf_swevent_match(काष्ठा perf_event *event,
				क्रमागत perf_type_id type,
				u32 event_id,
				काष्ठा perf_sample_data *data,
				काष्ठा pt_regs *regs)
अणु
	अगर (event->attr.type != type)
		वापस 0;

	अगर (event->attr.config != event_id)
		वापस 0;

	अगर (perf_exclude_event(event, regs))
		वापस 0;

	वापस 1;
पूर्ण

अटल अंतरभूत u64 swevent_hash(u64 type, u32 event_id)
अणु
	u64 val = event_id | (type << 32);

	वापस hash_64(val, SWEVENT_HLIST_BITS);
पूर्ण

अटल अंतरभूत काष्ठा hlist_head *
__find_swevent_head(काष्ठा swevent_hlist *hlist, u64 type, u32 event_id)
अणु
	u64 hash = swevent_hash(type, event_id);

	वापस &hlist->heads[hash];
पूर्ण

/* For the पढ़ो side: events when they trigger */
अटल अंतरभूत काष्ठा hlist_head *
find_swevent_head_rcu(काष्ठा swevent_htable *swhash, u64 type, u32 event_id)
अणु
	काष्ठा swevent_hlist *hlist;

	hlist = rcu_dereference(swhash->swevent_hlist);
	अगर (!hlist)
		वापस शून्य;

	वापस __find_swevent_head(hlist, type, event_id);
पूर्ण

/* For the event head insertion and removal in the hlist */
अटल अंतरभूत काष्ठा hlist_head *
find_swevent_head(काष्ठा swevent_htable *swhash, काष्ठा perf_event *event)
अणु
	काष्ठा swevent_hlist *hlist;
	u32 event_id = event->attr.config;
	u64 type = event->attr.type;

	/*
	 * Event scheduling is always serialized against hlist allocation
	 * and release. Which makes the रक्षित version suitable here.
	 * The context lock guarantees that.
	 */
	hlist = rcu_dereference_रक्षित(swhash->swevent_hlist,
					  lockdep_is_held(&event->ctx->lock));
	अगर (!hlist)
		वापस शून्य;

	वापस __find_swevent_head(hlist, type, event_id);
पूर्ण

अटल व्योम करो_perf_sw_event(क्रमागत perf_type_id type, u32 event_id,
				    u64 nr,
				    काष्ठा perf_sample_data *data,
				    काष्ठा pt_regs *regs)
अणु
	काष्ठा swevent_htable *swhash = this_cpu_ptr(&swevent_htable);
	काष्ठा perf_event *event;
	काष्ठा hlist_head *head;

	rcu_पढ़ो_lock();
	head = find_swevent_head_rcu(swhash, type, event_id);
	अगर (!head)
		जाओ end;

	hlist_क्रम_each_entry_rcu(event, head, hlist_entry) अणु
		अगर (perf_swevent_match(event, type, event_id, data, regs))
			perf_swevent_event(event, nr, data, regs);
	पूर्ण
end:
	rcu_पढ़ो_unlock();
पूर्ण

DEFINE_PER_CPU(काष्ठा pt_regs, __perf_regs[4]);

पूर्णांक perf_swevent_get_recursion_context(व्योम)
अणु
	काष्ठा swevent_htable *swhash = this_cpu_ptr(&swevent_htable);

	वापस get_recursion_context(swhash->recursion);
पूर्ण
EXPORT_SYMBOL_GPL(perf_swevent_get_recursion_context);

व्योम perf_swevent_put_recursion_context(पूर्णांक rctx)
अणु
	काष्ठा swevent_htable *swhash = this_cpu_ptr(&swevent_htable);

	put_recursion_context(swhash->recursion, rctx);
पूर्ण

व्योम ___perf_sw_event(u32 event_id, u64 nr, काष्ठा pt_regs *regs, u64 addr)
अणु
	काष्ठा perf_sample_data data;

	अगर (WARN_ON_ONCE(!regs))
		वापस;

	perf_sample_data_init(&data, addr, 0);
	करो_perf_sw_event(PERF_TYPE_SOFTWARE, event_id, nr, &data, regs);
पूर्ण

व्योम __perf_sw_event(u32 event_id, u64 nr, काष्ठा pt_regs *regs, u64 addr)
अणु
	पूर्णांक rctx;

	preempt_disable_notrace();
	rctx = perf_swevent_get_recursion_context();
	अगर (unlikely(rctx < 0))
		जाओ fail;

	___perf_sw_event(event_id, nr, regs, addr);

	perf_swevent_put_recursion_context(rctx);
fail:
	preempt_enable_notrace();
पूर्ण

अटल व्योम perf_swevent_पढ़ो(काष्ठा perf_event *event)
अणु
पूर्ण

अटल पूर्णांक perf_swevent_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा swevent_htable *swhash = this_cpu_ptr(&swevent_htable);
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा hlist_head *head;

	अगर (is_sampling_event(event)) अणु
		hwc->last_period = hwc->sample_period;
		perf_swevent_set_period(event);
	पूर्ण

	hwc->state = !(flags & PERF_EF_START);

	head = find_swevent_head(swhash, event);
	अगर (WARN_ON_ONCE(!head))
		वापस -EINVAL;

	hlist_add_head_rcu(&event->hlist_entry, head);
	perf_event_update_userpage(event);

	वापस 0;
पूर्ण

अटल व्योम perf_swevent_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	hlist_del_rcu(&event->hlist_entry);
पूर्ण

अटल व्योम perf_swevent_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	event->hw.state = 0;
पूर्ण

अटल व्योम perf_swevent_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	event->hw.state = PERF_HES_STOPPED;
पूर्ण

/* Deref the hlist from the update side */
अटल अंतरभूत काष्ठा swevent_hlist *
swevent_hlist_deref(काष्ठा swevent_htable *swhash)
अणु
	वापस rcu_dereference_रक्षित(swhash->swevent_hlist,
					 lockdep_is_held(&swhash->hlist_mutex));
पूर्ण

अटल व्योम swevent_hlist_release(काष्ठा swevent_htable *swhash)
अणु
	काष्ठा swevent_hlist *hlist = swevent_hlist_deref(swhash);

	अगर (!hlist)
		वापस;

	RCU_INIT_POINTER(swhash->swevent_hlist, शून्य);
	kमुक्त_rcu(hlist, rcu_head);
पूर्ण

अटल व्योम swevent_hlist_put_cpu(पूर्णांक cpu)
अणु
	काष्ठा swevent_htable *swhash = &per_cpu(swevent_htable, cpu);

	mutex_lock(&swhash->hlist_mutex);

	अगर (!--swhash->hlist_refcount)
		swevent_hlist_release(swhash);

	mutex_unlock(&swhash->hlist_mutex);
पूर्ण

अटल व्योम swevent_hlist_put(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		swevent_hlist_put_cpu(cpu);
पूर्ण

अटल पूर्णांक swevent_hlist_get_cpu(पूर्णांक cpu)
अणु
	काष्ठा swevent_htable *swhash = &per_cpu(swevent_htable, cpu);
	पूर्णांक err = 0;

	mutex_lock(&swhash->hlist_mutex);
	अगर (!swevent_hlist_deref(swhash) &&
	    cpumask_test_cpu(cpu, perf_online_mask)) अणु
		काष्ठा swevent_hlist *hlist;

		hlist = kzalloc(माप(*hlist), GFP_KERNEL);
		अगर (!hlist) अणु
			err = -ENOMEM;
			जाओ निकास;
		पूर्ण
		rcu_assign_poपूर्णांकer(swhash->swevent_hlist, hlist);
	पूर्ण
	swhash->hlist_refcount++;
निकास:
	mutex_unlock(&swhash->hlist_mutex);

	वापस err;
पूर्ण

अटल पूर्णांक swevent_hlist_get(व्योम)
अणु
	पूर्णांक err, cpu, failed_cpu;

	mutex_lock(&pmus_lock);
	क्रम_each_possible_cpu(cpu) अणु
		err = swevent_hlist_get_cpu(cpu);
		अगर (err) अणु
			failed_cpu = cpu;
			जाओ fail;
		पूर्ण
	पूर्ण
	mutex_unlock(&pmus_lock);
	वापस 0;
fail:
	क्रम_each_possible_cpu(cpu) अणु
		अगर (cpu == failed_cpu)
			अवरोध;
		swevent_hlist_put_cpu(cpu);
	पूर्ण
	mutex_unlock(&pmus_lock);
	वापस err;
पूर्ण

काष्ठा अटल_key perf_swevent_enabled[PERF_COUNT_SW_MAX];

अटल व्योम sw_perf_event_destroy(काष्ठा perf_event *event)
अणु
	u64 event_id = event->attr.config;

	WARN_ON(event->parent);

	अटल_key_slow_dec(&perf_swevent_enabled[event_id]);
	swevent_hlist_put();
पूर्ण

अटल पूर्णांक perf_swevent_init(काष्ठा perf_event *event)
अणु
	u64 event_id = event->attr.config;

	अगर (event->attr.type != PERF_TYPE_SOFTWARE)
		वापस -ENOENT;

	/*
	 * no branch sampling क्रम software events
	 */
	अगर (has_branch_stack(event))
		वापस -EOPNOTSUPP;

	चयन (event_id) अणु
	हाल PERF_COUNT_SW_CPU_CLOCK:
	हाल PERF_COUNT_SW_TASK_CLOCK:
		वापस -ENOENT;

	शेष:
		अवरोध;
	पूर्ण

	अगर (event_id >= PERF_COUNT_SW_MAX)
		वापस -ENOENT;

	अगर (!event->parent) अणु
		पूर्णांक err;

		err = swevent_hlist_get();
		अगर (err)
			वापस err;

		अटल_key_slow_inc(&perf_swevent_enabled[event_id]);
		event->destroy = sw_perf_event_destroy;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा pmu perf_swevent = अणु
	.task_ctx_nr	= perf_sw_context,

	.capabilities	= PERF_PMU_CAP_NO_NMI,

	.event_init	= perf_swevent_init,
	.add		= perf_swevent_add,
	.del		= perf_swevent_del,
	.start		= perf_swevent_start,
	.stop		= perf_swevent_stop,
	.पढ़ो		= perf_swevent_पढ़ो,
पूर्ण;

#अगर_घोषित CONFIG_EVENT_TRACING

अटल पूर्णांक perf_tp_filter_match(काष्ठा perf_event *event,
				काष्ठा perf_sample_data *data)
अणु
	व्योम *record = data->raw->frag.data;

	/* only top level events have filters set */
	अगर (event->parent)
		event = event->parent;

	अगर (likely(!event->filter) || filter_match_preds(event->filter, record))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक perf_tp_event_match(काष्ठा perf_event *event,
				काष्ठा perf_sample_data *data,
				काष्ठा pt_regs *regs)
अणु
	अगर (event->hw.state & PERF_HES_STOPPED)
		वापस 0;
	/*
	 * If exclude_kernel, only trace user-space tracepoपूर्णांकs (uprobes)
	 */
	अगर (event->attr.exclude_kernel && !user_mode(regs))
		वापस 0;

	अगर (!perf_tp_filter_match(event, data))
		वापस 0;

	वापस 1;
पूर्ण

व्योम perf_trace_run_bpf_submit(व्योम *raw_data, पूर्णांक size, पूर्णांक rctx,
			       काष्ठा trace_event_call *call, u64 count,
			       काष्ठा pt_regs *regs, काष्ठा hlist_head *head,
			       काष्ठा task_काष्ठा *task)
अणु
	अगर (bpf_prog_array_valid(call)) अणु
		*(काष्ठा pt_regs **)raw_data = regs;
		अगर (!trace_call_bpf(call, raw_data) || hlist_empty(head)) अणु
			perf_swevent_put_recursion_context(rctx);
			वापस;
		पूर्ण
	पूर्ण
	perf_tp_event(call->event.type, count, raw_data, size, regs, head,
		      rctx, task);
पूर्ण
EXPORT_SYMBOL_GPL(perf_trace_run_bpf_submit);

व्योम perf_tp_event(u16 event_type, u64 count, व्योम *record, पूर्णांक entry_size,
		   काष्ठा pt_regs *regs, काष्ठा hlist_head *head, पूर्णांक rctx,
		   काष्ठा task_काष्ठा *task)
अणु
	काष्ठा perf_sample_data data;
	काष्ठा perf_event *event;

	काष्ठा perf_raw_record raw = अणु
		.frag = अणु
			.size = entry_size,
			.data = record,
		पूर्ण,
	पूर्ण;

	perf_sample_data_init(&data, 0, 0);
	data.raw = &raw;

	perf_trace_buf_update(record, event_type);

	hlist_क्रम_each_entry_rcu(event, head, hlist_entry) अणु
		अगर (perf_tp_event_match(event, &data, regs))
			perf_swevent_event(event, count, &data, regs);
	पूर्ण

	/*
	 * If we got specअगरied a target task, also iterate its context and
	 * deliver this event there too.
	 */
	अगर (task && task != current) अणु
		काष्ठा perf_event_context *ctx;
		काष्ठा trace_entry *entry = record;

		rcu_पढ़ो_lock();
		ctx = rcu_dereference(task->perf_event_ctxp[perf_sw_context]);
		अगर (!ctx)
			जाओ unlock;

		list_क्रम_each_entry_rcu(event, &ctx->event_list, event_entry) अणु
			अगर (event->cpu != smp_processor_id())
				जारी;
			अगर (event->attr.type != PERF_TYPE_TRACEPOINT)
				जारी;
			अगर (event->attr.config != entry->type)
				जारी;
			अगर (perf_tp_event_match(event, &data, regs))
				perf_swevent_event(event, count, &data, regs);
		पूर्ण
unlock:
		rcu_पढ़ो_unlock();
	पूर्ण

	perf_swevent_put_recursion_context(rctx);
पूर्ण
EXPORT_SYMBOL_GPL(perf_tp_event);

अटल व्योम tp_perf_event_destroy(काष्ठा perf_event *event)
अणु
	perf_trace_destroy(event);
पूर्ण

अटल पूर्णांक perf_tp_event_init(काष्ठा perf_event *event)
अणु
	पूर्णांक err;

	अगर (event->attr.type != PERF_TYPE_TRACEPOINT)
		वापस -ENOENT;

	/*
	 * no branch sampling क्रम tracepoपूर्णांक events
	 */
	अगर (has_branch_stack(event))
		वापस -EOPNOTSUPP;

	err = perf_trace_init(event);
	अगर (err)
		वापस err;

	event->destroy = tp_perf_event_destroy;

	वापस 0;
पूर्ण

अटल काष्ठा pmu perf_tracepoपूर्णांक = अणु
	.task_ctx_nr	= perf_sw_context,

	.event_init	= perf_tp_event_init,
	.add		= perf_trace_add,
	.del		= perf_trace_del,
	.start		= perf_swevent_start,
	.stop		= perf_swevent_stop,
	.पढ़ो		= perf_swevent_पढ़ो,
पूर्ण;

#अगर defined(CONFIG_KPROBE_EVENTS) || defined(CONFIG_UPROBE_EVENTS)
/*
 * Flags in config, used by dynamic PMU kprobe and uprobe
 * The flags should match following PMU_FORMAT_ATTR().
 *
 * PERF_PROBE_CONFIG_IS_RETPROBE अगर set, create kretprobe/uretprobe
 *                               अगर not set, create kprobe/uprobe
 *
 * The following values specअगरy a reference counter (or semaphore in the
 * terminology of tools like dtrace, प्रणालीtap, etc.) Userspace Statically
 * Defined Tracepoपूर्णांकs (USDT). Currently, we use 40 bit क्रम the offset.
 *
 * PERF_UPROBE_REF_CTR_OFFSET_BITS	# of bits in config as th offset
 * PERF_UPROBE_REF_CTR_OFFSET_SHIFT	# of bits to shअगरt left
 */
क्रमागत perf_probe_config अणु
	PERF_PROBE_CONFIG_IS_RETPROBE = 1U << 0,  /* [k,u]retprobe */
	PERF_UPROBE_REF_CTR_OFFSET_BITS = 32,
	PERF_UPROBE_REF_CTR_OFFSET_SHIFT = 64 - PERF_UPROBE_REF_CTR_OFFSET_BITS,
पूर्ण;

PMU_FORMAT_ATTR(retprobe, "config:0");
#पूर्ण_अगर

#अगर_घोषित CONFIG_KPROBE_EVENTS
अटल काष्ठा attribute *kprobe_attrs[] = अणु
	&क्रमmat_attr_retprobe.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group kprobe_क्रमmat_group = अणु
	.name = "format",
	.attrs = kprobe_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *kprobe_attr_groups[] = अणु
	&kprobe_क्रमmat_group,
	शून्य,
पूर्ण;

अटल पूर्णांक perf_kprobe_event_init(काष्ठा perf_event *event);
अटल काष्ठा pmu perf_kprobe = अणु
	.task_ctx_nr	= perf_sw_context,
	.event_init	= perf_kprobe_event_init,
	.add		= perf_trace_add,
	.del		= perf_trace_del,
	.start		= perf_swevent_start,
	.stop		= perf_swevent_stop,
	.पढ़ो		= perf_swevent_पढ़ो,
	.attr_groups	= kprobe_attr_groups,
पूर्ण;

अटल पूर्णांक perf_kprobe_event_init(काष्ठा perf_event *event)
अणु
	पूर्णांक err;
	bool is_retprobe;

	अगर (event->attr.type != perf_kprobe.type)
		वापस -ENOENT;

	अगर (!perfmon_capable())
		वापस -EACCES;

	/*
	 * no branch sampling क्रम probe events
	 */
	अगर (has_branch_stack(event))
		वापस -EOPNOTSUPP;

	is_retprobe = event->attr.config & PERF_PROBE_CONFIG_IS_RETPROBE;
	err = perf_kprobe_init(event, is_retprobe);
	अगर (err)
		वापस err;

	event->destroy = perf_kprobe_destroy;

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_KPROBE_EVENTS */

#अगर_घोषित CONFIG_UPROBE_EVENTS
PMU_FORMAT_ATTR(ref_ctr_offset, "config:32-63");

अटल काष्ठा attribute *uprobe_attrs[] = अणु
	&क्रमmat_attr_retprobe.attr,
	&क्रमmat_attr_ref_ctr_offset.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group uprobe_क्रमmat_group = अणु
	.name = "format",
	.attrs = uprobe_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *uprobe_attr_groups[] = अणु
	&uprobe_क्रमmat_group,
	शून्य,
पूर्ण;

अटल पूर्णांक perf_uprobe_event_init(काष्ठा perf_event *event);
अटल काष्ठा pmu perf_uprobe = अणु
	.task_ctx_nr	= perf_sw_context,
	.event_init	= perf_uprobe_event_init,
	.add		= perf_trace_add,
	.del		= perf_trace_del,
	.start		= perf_swevent_start,
	.stop		= perf_swevent_stop,
	.पढ़ो		= perf_swevent_पढ़ो,
	.attr_groups	= uprobe_attr_groups,
पूर्ण;

अटल पूर्णांक perf_uprobe_event_init(काष्ठा perf_event *event)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ ref_ctr_offset;
	bool is_retprobe;

	अगर (event->attr.type != perf_uprobe.type)
		वापस -ENOENT;

	अगर (!perfmon_capable())
		वापस -EACCES;

	/*
	 * no branch sampling क्रम probe events
	 */
	अगर (has_branch_stack(event))
		वापस -EOPNOTSUPP;

	is_retprobe = event->attr.config & PERF_PROBE_CONFIG_IS_RETPROBE;
	ref_ctr_offset = event->attr.config >> PERF_UPROBE_REF_CTR_OFFSET_SHIFT;
	err = perf_uprobe_init(event, ref_ctr_offset, is_retprobe);
	अगर (err)
		वापस err;

	event->destroy = perf_uprobe_destroy;

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_UPROBE_EVENTS */

अटल अंतरभूत व्योम perf_tp_रेजिस्टर(व्योम)
अणु
	perf_pmu_रेजिस्टर(&perf_tracepoपूर्णांक, "tracepoint", PERF_TYPE_TRACEPOINT);
#अगर_घोषित CONFIG_KPROBE_EVENTS
	perf_pmu_रेजिस्टर(&perf_kprobe, "kprobe", -1);
#पूर्ण_अगर
#अगर_घोषित CONFIG_UPROBE_EVENTS
	perf_pmu_रेजिस्टर(&perf_uprobe, "uprobe", -1);
#पूर्ण_अगर
पूर्ण

अटल व्योम perf_event_मुक्त_filter(काष्ठा perf_event *event)
अणु
	ftrace_profile_मुक्त_filter(event);
पूर्ण

#अगर_घोषित CONFIG_BPF_SYSCALL
अटल व्योम bpf_overflow_handler(काष्ठा perf_event *event,
				 काष्ठा perf_sample_data *data,
				 काष्ठा pt_regs *regs)
अणु
	काष्ठा bpf_perf_event_data_kern ctx = अणु
		.data = data,
		.event = event,
	पूर्ण;
	पूर्णांक ret = 0;

	ctx.regs = perf_arch_bpf_user_pt_regs(regs);
	अगर (unlikely(__this_cpu_inc_वापस(bpf_prog_active) != 1))
		जाओ out;
	rcu_पढ़ो_lock();
	ret = BPF_PROG_RUN(event->prog, &ctx);
	rcu_पढ़ो_unlock();
out:
	__this_cpu_dec(bpf_prog_active);
	अगर (!ret)
		वापस;

	event->orig_overflow_handler(event, data, regs);
पूर्ण

अटल पूर्णांक perf_event_set_bpf_handler(काष्ठा perf_event *event, u32 prog_fd)
अणु
	काष्ठा bpf_prog *prog;

	अगर (event->overflow_handler_context)
		/* hw अवरोधpoपूर्णांक or kernel counter */
		वापस -EINVAL;

	अगर (event->prog)
		वापस -EEXIST;

	prog = bpf_prog_get_type(prog_fd, BPF_PROG_TYPE_PERF_EVENT);
	अगर (IS_ERR(prog))
		वापस PTR_ERR(prog);

	अगर (event->attr.precise_ip &&
	    prog->call_get_stack &&
	    (!(event->attr.sample_type & __PERF_SAMPLE_CALLCHAIN_EARLY) ||
	     event->attr.exclude_callchain_kernel ||
	     event->attr.exclude_callchain_user)) अणु
		/*
		 * On perf_event with precise_ip, calling bpf_get_stack()
		 * may trigger unwinder warnings and occasional crashes.
		 * bpf_get_[stack|stackid] works around this issue by using
		 * callchain attached to perf_sample_data. If the
		 * perf_event करोes not full (kernel and user) callchain
		 * attached to perf_sample_data, करो not allow attaching BPF
		 * program that calls bpf_get_[stack|stackid].
		 */
		bpf_prog_put(prog);
		वापस -EPROTO;
	पूर्ण

	event->prog = prog;
	event->orig_overflow_handler = READ_ONCE(event->overflow_handler);
	WRITE_ONCE(event->overflow_handler, bpf_overflow_handler);
	वापस 0;
पूर्ण

अटल व्योम perf_event_मुक्त_bpf_handler(काष्ठा perf_event *event)
अणु
	काष्ठा bpf_prog *prog = event->prog;

	अगर (!prog)
		वापस;

	WRITE_ONCE(event->overflow_handler, event->orig_overflow_handler);
	event->prog = शून्य;
	bpf_prog_put(prog);
पूर्ण
#अन्यथा
अटल पूर्णांक perf_event_set_bpf_handler(काष्ठा perf_event *event, u32 prog_fd)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
अटल व्योम perf_event_मुक्त_bpf_handler(काष्ठा perf_event *event)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * वापसs true अगर the event is a tracepoपूर्णांक, or a kprobe/upprobe created
 * with perf_event_खोलो()
 */
अटल अंतरभूत bool perf_event_is_tracing(काष्ठा perf_event *event)
अणु
	अगर (event->pmu == &perf_tracepoपूर्णांक)
		वापस true;
#अगर_घोषित CONFIG_KPROBE_EVENTS
	अगर (event->pmu == &perf_kprobe)
		वापस true;
#पूर्ण_अगर
#अगर_घोषित CONFIG_UPROBE_EVENTS
	अगर (event->pmu == &perf_uprobe)
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल पूर्णांक perf_event_set_bpf_prog(काष्ठा perf_event *event, u32 prog_fd)
अणु
	bool is_kprobe, is_tracepoपूर्णांक, is_syscall_tp;
	काष्ठा bpf_prog *prog;
	पूर्णांक ret;

	अगर (!perf_event_is_tracing(event))
		वापस perf_event_set_bpf_handler(event, prog_fd);

	is_kprobe = event->tp_event->flags & TRACE_EVENT_FL_UKPROBE;
	is_tracepoपूर्णांक = event->tp_event->flags & TRACE_EVENT_FL_TRACEPOINT;
	is_syscall_tp = is_syscall_trace_event(event->tp_event);
	अगर (!is_kprobe && !is_tracepoपूर्णांक && !is_syscall_tp)
		/* bpf programs can only be attached to u/kprobe or tracepoपूर्णांक */
		वापस -EINVAL;

	prog = bpf_prog_get(prog_fd);
	अगर (IS_ERR(prog))
		वापस PTR_ERR(prog);

	अगर ((is_kprobe && prog->type != BPF_PROG_TYPE_KPROBE) ||
	    (is_tracepoपूर्णांक && prog->type != BPF_PROG_TYPE_TRACEPOINT) ||
	    (is_syscall_tp && prog->type != BPF_PROG_TYPE_TRACEPOINT)) अणु
		/* valid fd, but invalid bpf program type */
		bpf_prog_put(prog);
		वापस -EINVAL;
	पूर्ण

	/* Kprobe override only works क्रम kprobes, not uprobes. */
	अगर (prog->kprobe_override &&
	    !(event->tp_event->flags & TRACE_EVENT_FL_KPROBE)) अणु
		bpf_prog_put(prog);
		वापस -EINVAL;
	पूर्ण

	अगर (is_tracepoपूर्णांक || is_syscall_tp) अणु
		पूर्णांक off = trace_event_get_offsets(event->tp_event);

		अगर (prog->aux->max_ctx_offset > off) अणु
			bpf_prog_put(prog);
			वापस -EACCES;
		पूर्ण
	पूर्ण

	ret = perf_event_attach_bpf_prog(event, prog);
	अगर (ret)
		bpf_prog_put(prog);
	वापस ret;
पूर्ण

अटल व्योम perf_event_मुक्त_bpf_prog(काष्ठा perf_event *event)
अणु
	अगर (!perf_event_is_tracing(event)) अणु
		perf_event_मुक्त_bpf_handler(event);
		वापस;
	पूर्ण
	perf_event_detach_bpf_prog(event);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम perf_tp_रेजिस्टर(व्योम)
अणु
पूर्ण

अटल व्योम perf_event_मुक्त_filter(काष्ठा perf_event *event)
अणु
पूर्ण

अटल पूर्णांक perf_event_set_bpf_prog(काष्ठा perf_event *event, u32 prog_fd)
अणु
	वापस -ENOENT;
पूर्ण

अटल व्योम perf_event_मुक्त_bpf_prog(काष्ठा perf_event *event)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_EVENT_TRACING */

#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
व्योम perf_bp_event(काष्ठा perf_event *bp, व्योम *data)
अणु
	काष्ठा perf_sample_data sample;
	काष्ठा pt_regs *regs = data;

	perf_sample_data_init(&sample, bp->attr.bp_addr, 0);

	अगर (!bp->hw.state && !perf_exclude_event(bp, regs))
		perf_swevent_event(bp, 1, &sample, regs);
पूर्ण
#पूर्ण_अगर

/*
 * Allocate a new address filter
 */
अटल काष्ठा perf_addr_filter *
perf_addr_filter_new(काष्ठा perf_event *event, काष्ठा list_head *filters)
अणु
	पूर्णांक node = cpu_to_node(event->cpu == -1 ? 0 : event->cpu);
	काष्ठा perf_addr_filter *filter;

	filter = kzalloc_node(माप(*filter), GFP_KERNEL, node);
	अगर (!filter)
		वापस शून्य;

	INIT_LIST_HEAD(&filter->entry);
	list_add_tail(&filter->entry, filters);

	वापस filter;
पूर्ण

अटल व्योम मुक्त_filters_list(काष्ठा list_head *filters)
अणु
	काष्ठा perf_addr_filter *filter, *iter;

	list_क्रम_each_entry_safe(filter, iter, filters, entry) अणु
		path_put(&filter->path);
		list_del(&filter->entry);
		kमुक्त(filter);
	पूर्ण
पूर्ण

/*
 * Free existing address filters and optionally install new ones
 */
अटल व्योम perf_addr_filters_splice(काष्ठा perf_event *event,
				     काष्ठा list_head *head)
अणु
	अचिन्हित दीर्घ flags;
	LIST_HEAD(list);

	अगर (!has_addr_filter(event))
		वापस;

	/* करोn't bother with children, they don't have their own filters */
	अगर (event->parent)
		वापस;

	raw_spin_lock_irqsave(&event->addr_filters.lock, flags);

	list_splice_init(&event->addr_filters.list, &list);
	अगर (head)
		list_splice(head, &event->addr_filters.list);

	raw_spin_unlock_irqrestore(&event->addr_filters.lock, flags);

	मुक्त_filters_list(&list);
पूर्ण

/*
 * Scan through mm's vmas and see अगर one of them matches the
 * @filter; अगर so, adjust filter's address range.
 * Called with mm::mmap_lock करोwn क्रम पढ़ोing.
 */
अटल व्योम perf_addr_filter_apply(काष्ठा perf_addr_filter *filter,
				   काष्ठा mm_काष्ठा *mm,
				   काष्ठा perf_addr_filter_range *fr)
अणु
	काष्ठा vm_area_काष्ठा *vma;

	क्रम (vma = mm->mmap; vma; vma = vma->vm_next) अणु
		अगर (!vma->vm_file)
			जारी;

		अगर (perf_addr_filter_vma_adjust(filter, vma, fr))
			वापस;
	पूर्ण
पूर्ण

/*
 * Update event's address range filters based on the
 * task's existing mappings, अगर any.
 */
अटल व्योम perf_event_addr_filters_apply(काष्ठा perf_event *event)
अणु
	काष्ठा perf_addr_filters_head *अगरh = perf_event_addr_filters(event);
	काष्ठा task_काष्ठा *task = READ_ONCE(event->ctx->task);
	काष्ठा perf_addr_filter *filter;
	काष्ठा mm_काष्ठा *mm = शून्य;
	अचिन्हित पूर्णांक count = 0;
	अचिन्हित दीर्घ flags;

	/*
	 * We may observe TASK_TOMBSTONE, which means that the event tear-करोwn
	 * will stop on the parent's child_mutex that our caller is also holding
	 */
	अगर (task == TASK_TOMBSTONE)
		वापस;

	अगर (अगरh->nr_file_filters) अणु
		mm = get_task_mm(event->ctx->task);
		अगर (!mm)
			जाओ restart;

		mmap_पढ़ो_lock(mm);
	पूर्ण

	raw_spin_lock_irqsave(&अगरh->lock, flags);
	list_क्रम_each_entry(filter, &अगरh->list, entry) अणु
		अगर (filter->path.dentry) अणु
			/*
			 * Adjust base offset अगर the filter is associated to a
			 * binary that needs to be mapped:
			 */
			event->addr_filter_ranges[count].start = 0;
			event->addr_filter_ranges[count].size = 0;

			perf_addr_filter_apply(filter, mm, &event->addr_filter_ranges[count]);
		पूर्ण अन्यथा अणु
			event->addr_filter_ranges[count].start = filter->offset;
			event->addr_filter_ranges[count].size  = filter->size;
		पूर्ण

		count++;
	पूर्ण

	event->addr_filters_gen++;
	raw_spin_unlock_irqrestore(&अगरh->lock, flags);

	अगर (अगरh->nr_file_filters) अणु
		mmap_पढ़ो_unlock(mm);

		mmput(mm);
	पूर्ण

restart:
	perf_event_stop(event, 1);
पूर्ण

/*
 * Address range filtering: limiting the data to certain
 * inकाष्ठाion address ranges. Filters are ioctl()ed to us from
 * userspace as ascii strings.
 *
 * Filter string क्रमmat:
 *
 * ACTION RANGE_SPEC
 * where ACTION is one of the
 *  * "filter": limit the trace to this region
 *  * "start": start tracing from this address
 *  * "stop": stop tracing at this address/region;
 * RANGE_SPEC is
 *  * क्रम kernel addresses: <start address>[/<size>]
 *  * क्रम object files:     <start address>[/<size>]@</path/to/object/file>
 *
 * अगर <size> is not specअगरied or is zero, the range is treated as a single
 * address; not valid क्रम ACTION=="filter".
 */
क्रमागत अणु
	IF_ACT_NONE = -1,
	IF_ACT_FILTER,
	IF_ACT_START,
	IF_ACT_STOP,
	IF_SRC_खाता,
	IF_SRC_KERNEL,
	IF_SRC_खाताADDR,
	IF_SRC_KERNELADDR,
पूर्ण;

क्रमागत अणु
	IF_STATE_ACTION = 0,
	IF_STATE_SOURCE,
	IF_STATE_END,
पूर्ण;

अटल स्थिर match_table_t अगर_tokens = अणु
	अणु IF_ACT_FILTER,	"filter" पूर्ण,
	अणु IF_ACT_START,		"start" पूर्ण,
	अणु IF_ACT_STOP,		"stop" पूर्ण,
	अणु IF_SRC_खाता,		"%u/%u@%s" पूर्ण,
	अणु IF_SRC_KERNEL,	"%u/%u" पूर्ण,
	अणु IF_SRC_खाताADDR,	"%u@%s" पूर्ण,
	अणु IF_SRC_KERNELADDR,	"%u" पूर्ण,
	अणु IF_ACT_NONE,		शून्य पूर्ण,
पूर्ण;

/*
 * Address filter string parser
 */
अटल पूर्णांक
perf_event_parse_addr_filter(काष्ठा perf_event *event, अक्षर *fstr,
			     काष्ठा list_head *filters)
अणु
	काष्ठा perf_addr_filter *filter = शून्य;
	अक्षर *start, *orig, *filename = शून्य;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक state = IF_STATE_ACTION, token;
	अचिन्हित पूर्णांक kernel = 0;
	पूर्णांक ret = -EINVAL;

	orig = fstr = kstrdup(fstr, GFP_KERNEL);
	अगर (!fstr)
		वापस -ENOMEM;

	जबतक ((start = strsep(&fstr, " ,\n")) != शून्य) अणु
		अटल स्थिर क्रमागत perf_addr_filter_action_t actions[] = अणु
			[IF_ACT_FILTER]	= PERF_ADDR_FILTER_ACTION_FILTER,
			[IF_ACT_START]	= PERF_ADDR_FILTER_ACTION_START,
			[IF_ACT_STOP]	= PERF_ADDR_FILTER_ACTION_STOP,
		पूर्ण;
		ret = -EINVAL;

		अगर (!*start)
			जारी;

		/* filter definition begins */
		अगर (state == IF_STATE_ACTION) अणु
			filter = perf_addr_filter_new(event, filters);
			अगर (!filter)
				जाओ fail;
		पूर्ण

		token = match_token(start, अगर_tokens, args);
		चयन (token) अणु
		हाल IF_ACT_FILTER:
		हाल IF_ACT_START:
		हाल IF_ACT_STOP:
			अगर (state != IF_STATE_ACTION)
				जाओ fail;

			filter->action = actions[token];
			state = IF_STATE_SOURCE;
			अवरोध;

		हाल IF_SRC_KERNELADDR:
		हाल IF_SRC_KERNEL:
			kernel = 1;
			fallthrough;

		हाल IF_SRC_खाताADDR:
		हाल IF_SRC_खाता:
			अगर (state != IF_STATE_SOURCE)
				जाओ fail;

			*args[0].to = 0;
			ret = kम_से_अदीर्घ(args[0].from, 0, &filter->offset);
			अगर (ret)
				जाओ fail;

			अगर (token == IF_SRC_KERNEL || token == IF_SRC_खाता) अणु
				*args[1].to = 0;
				ret = kम_से_अदीर्घ(args[1].from, 0, &filter->size);
				अगर (ret)
					जाओ fail;
			पूर्ण

			अगर (token == IF_SRC_खाता || token == IF_SRC_खाताADDR) अणु
				पूर्णांक fpos = token == IF_SRC_खाता ? 2 : 1;

				kमुक्त(filename);
				filename = match_strdup(&args[fpos]);
				अगर (!filename) अणु
					ret = -ENOMEM;
					जाओ fail;
				पूर्ण
			पूर्ण

			state = IF_STATE_END;
			अवरोध;

		शेष:
			जाओ fail;
		पूर्ण

		/*
		 * Filter definition is fully parsed, validate and install it.
		 * Make sure that it करोesn't contradict itself or the event's
		 * attribute.
		 */
		अगर (state == IF_STATE_END) अणु
			ret = -EINVAL;
			अगर (kernel && event->attr.exclude_kernel)
				जाओ fail;

			/*
			 * ACTION "filter" must have a non-zero length region
			 * specअगरied.
			 */
			अगर (filter->action == PERF_ADDR_FILTER_ACTION_FILTER &&
			    !filter->size)
				जाओ fail;

			अगर (!kernel) अणु
				अगर (!filename)
					जाओ fail;

				/*
				 * For now, we only support file-based filters
				 * in per-task events; करोing so क्रम CPU-wide
				 * events requires additional context चयनing
				 * trickery, since same object code will be
				 * mapped at dअगरferent भव addresses in
				 * dअगरferent processes.
				 */
				ret = -EOPNOTSUPP;
				अगर (!event->ctx->task)
					जाओ fail;

				/* look up the path and grab its inode */
				ret = kern_path(filename, LOOKUP_FOLLOW,
						&filter->path);
				अगर (ret)
					जाओ fail;

				ret = -EINVAL;
				अगर (!filter->path.dentry ||
				    !S_ISREG(d_inode(filter->path.dentry)
					     ->i_mode))
					जाओ fail;

				event->addr_filters.nr_file_filters++;
			पूर्ण

			/* पढ़ोy to consume more filters */
			state = IF_STATE_ACTION;
			filter = शून्य;
		पूर्ण
	पूर्ण

	अगर (state != IF_STATE_ACTION)
		जाओ fail;

	kमुक्त(filename);
	kमुक्त(orig);

	वापस 0;

fail:
	kमुक्त(filename);
	मुक्त_filters_list(filters);
	kमुक्त(orig);

	वापस ret;
पूर्ण

अटल पूर्णांक
perf_event_set_addr_filter(काष्ठा perf_event *event, अक्षर *filter_str)
अणु
	LIST_HEAD(filters);
	पूर्णांक ret;

	/*
	 * Since this is called in perf_ioctl() path, we're alपढ़ोy holding
	 * ctx::mutex.
	 */
	lockdep_निश्चित_held(&event->ctx->mutex);

	अगर (WARN_ON_ONCE(event->parent))
		वापस -EINVAL;

	ret = perf_event_parse_addr_filter(event, filter_str, &filters);
	अगर (ret)
		जाओ fail_clear_files;

	ret = event->pmu->addr_filters_validate(&filters);
	अगर (ret)
		जाओ fail_मुक्त_filters;

	/* हटाओ existing filters, अगर any */
	perf_addr_filters_splice(event, &filters);

	/* install new filters */
	perf_event_क्रम_each_child(event, perf_event_addr_filters_apply);

	वापस ret;

fail_मुक्त_filters:
	मुक्त_filters_list(&filters);

fail_clear_files:
	event->addr_filters.nr_file_filters = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक perf_event_set_filter(काष्ठा perf_event *event, व्योम __user *arg)
अणु
	पूर्णांक ret = -EINVAL;
	अक्षर *filter_str;

	filter_str = strndup_user(arg, PAGE_SIZE);
	अगर (IS_ERR(filter_str))
		वापस PTR_ERR(filter_str);

#अगर_घोषित CONFIG_EVENT_TRACING
	अगर (perf_event_is_tracing(event)) अणु
		काष्ठा perf_event_context *ctx = event->ctx;

		/*
		 * Beware, here be dragons!!
		 *
		 * the tracepoपूर्णांक muck will deadlock against ctx->mutex, but
		 * the tracepoपूर्णांक stuff करोes not actually need it. So
		 * temporarily drop ctx->mutex. As per perf_event_ctx_lock() we
		 * alपढ़ोy have a reference on ctx.
		 *
		 * This can result in event getting moved to a dअगरferent ctx,
		 * but that करोes not affect the tracepoपूर्णांक state.
		 */
		mutex_unlock(&ctx->mutex);
		ret = ftrace_profile_set_filter(event, event->attr.config, filter_str);
		mutex_lock(&ctx->mutex);
	पूर्ण अन्यथा
#पूर्ण_अगर
	अगर (has_addr_filter(event))
		ret = perf_event_set_addr_filter(event, filter_str);

	kमुक्त(filter_str);
	वापस ret;
पूर्ण

/*
 * hrसमयr based swevent callback
 */

अटल क्रमागत hrसमयr_restart perf_swevent_hrसमयr(काष्ठा hrसमयr *hrसमयr)
अणु
	क्रमागत hrसमयr_restart ret = HRTIMER_RESTART;
	काष्ठा perf_sample_data data;
	काष्ठा pt_regs *regs;
	काष्ठा perf_event *event;
	u64 period;

	event = container_of(hrसमयr, काष्ठा perf_event, hw.hrसमयr);

	अगर (event->state != PERF_EVENT_STATE_ACTIVE)
		वापस HRTIMER_NORESTART;

	event->pmu->पढ़ो(event);

	perf_sample_data_init(&data, 0, event->hw.last_period);
	regs = get_irq_regs();

	अगर (regs && !perf_exclude_event(event, regs)) अणु
		अगर (!(event->attr.exclude_idle && is_idle_task(current)))
			अगर (__perf_event_overflow(event, 1, &data, regs))
				ret = HRTIMER_NORESTART;
	पूर्ण

	period = max_t(u64, 10000, event->hw.sample_period);
	hrसमयr_क्रमward_now(hrसमयr, ns_to_kसमय(period));

	वापस ret;
पूर्ण

अटल व्योम perf_swevent_start_hrसमयr(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	s64 period;

	अगर (!is_sampling_event(event))
		वापस;

	period = local64_पढ़ो(&hwc->period_left);
	अगर (period) अणु
		अगर (period < 0)
			period = 10000;

		local64_set(&hwc->period_left, 0);
	पूर्ण अन्यथा अणु
		period = max_t(u64, 10000, hwc->sample_period);
	पूर्ण
	hrसमयr_start(&hwc->hrसमयr, ns_to_kसमय(period),
		      HRTIMER_MODE_REL_PINNED_HARD);
पूर्ण

अटल व्योम perf_swevent_cancel_hrसमयr(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (is_sampling_event(event)) अणु
		kसमय_प्रकार reमुख्यing = hrसमयr_get_reमुख्यing(&hwc->hrसमयr);
		local64_set(&hwc->period_left, kसमय_प्रकारo_ns(reमुख्यing));

		hrसमयr_cancel(&hwc->hrसमयr);
	पूर्ण
पूर्ण

अटल व्योम perf_swevent_init_hrसमयr(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (!is_sampling_event(event))
		वापस;

	hrसमयr_init(&hwc->hrसमयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL_HARD);
	hwc->hrसमयr.function = perf_swevent_hrसमयr;

	/*
	 * Since hrसमयrs have a fixed rate, we can करो a अटल freq->period
	 * mapping and aव्योम the whole period adjust feedback stuff.
	 */
	अगर (event->attr.freq) अणु
		दीर्घ freq = event->attr.sample_freq;

		event->attr.sample_period = NSEC_PER_SEC / freq;
		hwc->sample_period = event->attr.sample_period;
		local64_set(&hwc->period_left, hwc->sample_period);
		hwc->last_period = hwc->sample_period;
		event->attr.freq = 0;
	पूर्ण
पूर्ण

/*
 * Software event: cpu wall समय घड़ी
 */

अटल व्योम cpu_घड़ी_event_update(काष्ठा perf_event *event)
अणु
	s64 prev;
	u64 now;

	now = local_घड़ी();
	prev = local64_xchg(&event->hw.prev_count, now);
	local64_add(now - prev, &event->count);
पूर्ण

अटल व्योम cpu_घड़ी_event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	local64_set(&event->hw.prev_count, local_घड़ी());
	perf_swevent_start_hrसमयr(event);
पूर्ण

अटल व्योम cpu_घड़ी_event_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	perf_swevent_cancel_hrसमयr(event);
	cpu_घड़ी_event_update(event);
पूर्ण

अटल पूर्णांक cpu_घड़ी_event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	अगर (flags & PERF_EF_START)
		cpu_घड़ी_event_start(event, flags);
	perf_event_update_userpage(event);

	वापस 0;
पूर्ण

अटल व्योम cpu_घड़ी_event_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	cpu_घड़ी_event_stop(event, flags);
पूर्ण

अटल व्योम cpu_घड़ी_event_पढ़ो(काष्ठा perf_event *event)
अणु
	cpu_घड़ी_event_update(event);
पूर्ण

अटल पूर्णांक cpu_घड़ी_event_init(काष्ठा perf_event *event)
अणु
	अगर (event->attr.type != PERF_TYPE_SOFTWARE)
		वापस -ENOENT;

	अगर (event->attr.config != PERF_COUNT_SW_CPU_CLOCK)
		वापस -ENOENT;

	/*
	 * no branch sampling क्रम software events
	 */
	अगर (has_branch_stack(event))
		वापस -EOPNOTSUPP;

	perf_swevent_init_hrसमयr(event);

	वापस 0;
पूर्ण

अटल काष्ठा pmu perf_cpu_घड़ी = अणु
	.task_ctx_nr	= perf_sw_context,

	.capabilities	= PERF_PMU_CAP_NO_NMI,

	.event_init	= cpu_घड़ी_event_init,
	.add		= cpu_घड़ी_event_add,
	.del		= cpu_घड़ी_event_del,
	.start		= cpu_घड़ी_event_start,
	.stop		= cpu_घड़ी_event_stop,
	.पढ़ो		= cpu_घड़ी_event_पढ़ो,
पूर्ण;

/*
 * Software event: task समय घड़ी
 */

अटल व्योम task_घड़ी_event_update(काष्ठा perf_event *event, u64 now)
अणु
	u64 prev;
	s64 delta;

	prev = local64_xchg(&event->hw.prev_count, now);
	delta = now - prev;
	local64_add(delta, &event->count);
पूर्ण

अटल व्योम task_घड़ी_event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	local64_set(&event->hw.prev_count, event->ctx->समय);
	perf_swevent_start_hrसमयr(event);
पूर्ण

अटल व्योम task_घड़ी_event_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	perf_swevent_cancel_hrसमयr(event);
	task_घड़ी_event_update(event, event->ctx->समय);
पूर्ण

अटल पूर्णांक task_घड़ी_event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	अगर (flags & PERF_EF_START)
		task_घड़ी_event_start(event, flags);
	perf_event_update_userpage(event);

	वापस 0;
पूर्ण

अटल व्योम task_घड़ी_event_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	task_घड़ी_event_stop(event, PERF_EF_UPDATE);
पूर्ण

अटल व्योम task_घड़ी_event_पढ़ो(काष्ठा perf_event *event)
अणु
	u64 now = perf_घड़ी();
	u64 delta = now - event->ctx->बारtamp;
	u64 समय = event->ctx->समय + delta;

	task_घड़ी_event_update(event, समय);
पूर्ण

अटल पूर्णांक task_घड़ी_event_init(काष्ठा perf_event *event)
अणु
	अगर (event->attr.type != PERF_TYPE_SOFTWARE)
		वापस -ENOENT;

	अगर (event->attr.config != PERF_COUNT_SW_TASK_CLOCK)
		वापस -ENOENT;

	/*
	 * no branch sampling क्रम software events
	 */
	अगर (has_branch_stack(event))
		वापस -EOPNOTSUPP;

	perf_swevent_init_hrसमयr(event);

	वापस 0;
पूर्ण

अटल काष्ठा pmu perf_task_घड़ी = अणु
	.task_ctx_nr	= perf_sw_context,

	.capabilities	= PERF_PMU_CAP_NO_NMI,

	.event_init	= task_घड़ी_event_init,
	.add		= task_घड़ी_event_add,
	.del		= task_घड़ी_event_del,
	.start		= task_घड़ी_event_start,
	.stop		= task_घड़ी_event_stop,
	.पढ़ो		= task_घड़ी_event_पढ़ो,
पूर्ण;

अटल व्योम perf_pmu_nop_व्योम(काष्ठा pmu *pmu)
अणु
पूर्ण

अटल व्योम perf_pmu_nop_txn(काष्ठा pmu *pmu, अचिन्हित पूर्णांक flags)
अणु
पूर्ण

अटल पूर्णांक perf_pmu_nop_पूर्णांक(काष्ठा pmu *pmu)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक perf_event_nop_पूर्णांक(काष्ठा perf_event *event, u64 value)
अणु
	वापस 0;
पूर्ण

अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, nop_txn_flags);

अटल व्योम perf_pmu_start_txn(काष्ठा pmu *pmu, अचिन्हित पूर्णांक flags)
अणु
	__this_cpu_ग_लिखो(nop_txn_flags, flags);

	अगर (flags & ~PERF_PMU_TXN_ADD)
		वापस;

	perf_pmu_disable(pmu);
पूर्ण

अटल पूर्णांक perf_pmu_commit_txn(काष्ठा pmu *pmu)
अणु
	अचिन्हित पूर्णांक flags = __this_cpu_पढ़ो(nop_txn_flags);

	__this_cpu_ग_लिखो(nop_txn_flags, 0);

	अगर (flags & ~PERF_PMU_TXN_ADD)
		वापस 0;

	perf_pmu_enable(pmu);
	वापस 0;
पूर्ण

अटल व्योम perf_pmu_cancel_txn(काष्ठा pmu *pmu)
अणु
	अचिन्हित पूर्णांक flags =  __this_cpu_पढ़ो(nop_txn_flags);

	__this_cpu_ग_लिखो(nop_txn_flags, 0);

	अगर (flags & ~PERF_PMU_TXN_ADD)
		वापस;

	perf_pmu_enable(pmu);
पूर्ण

अटल पूर्णांक perf_event_idx_शेष(काष्ठा perf_event *event)
अणु
	वापस 0;
पूर्ण

/*
 * Ensures all contexts with the same task_ctx_nr have the same
 * pmu_cpu_context too.
 */
अटल काष्ठा perf_cpu_context __percpu *find_pmu_context(पूर्णांक ctxn)
अणु
	काष्ठा pmu *pmu;

	अगर (ctxn < 0)
		वापस शून्य;

	list_क्रम_each_entry(pmu, &pmus, entry) अणु
		अगर (pmu->task_ctx_nr == ctxn)
			वापस pmu->pmu_cpu_context;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम मुक्त_pmu_context(काष्ठा pmu *pmu)
अणु
	/*
	 * Static contexts such as perf_sw_context have a global lअगरeसमय
	 * and may be shared between dअगरferent PMUs. Aव्योम मुक्तing them
	 * when a single PMU is going away.
	 */
	अगर (pmu->task_ctx_nr > perf_invalid_context)
		वापस;

	मुक्त_percpu(pmu->pmu_cpu_context);
पूर्ण

/*
 * Let userspace know that this PMU supports address range filtering:
 */
अटल sमाप_प्रकार nr_addr_filters_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *page)
अणु
	काष्ठा pmu *pmu = dev_get_drvdata(dev);

	वापस snम_लिखो(page, PAGE_SIZE - 1, "%d\n", pmu->nr_addr_filters);
पूर्ण
DEVICE_ATTR_RO(nr_addr_filters);

अटल काष्ठा idr pmu_idr;

अटल sमाप_प्रकार
type_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *page)
अणु
	काष्ठा pmu *pmu = dev_get_drvdata(dev);

	वापस snम_लिखो(page, PAGE_SIZE-1, "%d\n", pmu->type);
पूर्ण
अटल DEVICE_ATTR_RO(type);

अटल sमाप_प्रकार
perf_event_mux_पूर्णांकerval_ms_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *page)
अणु
	काष्ठा pmu *pmu = dev_get_drvdata(dev);

	वापस snम_लिखो(page, PAGE_SIZE-1, "%d\n", pmu->hrसमयr_पूर्णांकerval_ms);
पूर्ण

अटल DEFINE_MUTEX(mux_पूर्णांकerval_mutex);

अटल sमाप_प्रकार
perf_event_mux_पूर्णांकerval_ms_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pmu *pmu = dev_get_drvdata(dev);
	पूर्णांक समयr, cpu, ret;

	ret = kstrtoपूर्णांक(buf, 0, &समयr);
	अगर (ret)
		वापस ret;

	अगर (समयr < 1)
		वापस -EINVAL;

	/* same value, noting to करो */
	अगर (समयr == pmu->hrसमयr_पूर्णांकerval_ms)
		वापस count;

	mutex_lock(&mux_पूर्णांकerval_mutex);
	pmu->hrसमयr_पूर्णांकerval_ms = समयr;

	/* update all cpuctx क्रम this PMU */
	cpus_पढ़ो_lock();
	क्रम_each_online_cpu(cpu) अणु
		काष्ठा perf_cpu_context *cpuctx;
		cpuctx = per_cpu_ptr(pmu->pmu_cpu_context, cpu);
		cpuctx->hrसमयr_पूर्णांकerval = ns_to_kसमय(NSEC_PER_MSEC * समयr);

		cpu_function_call(cpu,
			(remote_function_f)perf_mux_hrसमयr_restart, cpuctx);
	पूर्ण
	cpus_पढ़ो_unlock();
	mutex_unlock(&mux_पूर्णांकerval_mutex);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(perf_event_mux_पूर्णांकerval_ms);

अटल काष्ठा attribute *pmu_dev_attrs[] = अणु
	&dev_attr_type.attr,
	&dev_attr_perf_event_mux_पूर्णांकerval_ms.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(pmu_dev);

अटल पूर्णांक pmu_bus_running;
अटल काष्ठा bus_type pmu_bus = अणु
	.name		= "event_source",
	.dev_groups	= pmu_dev_groups,
पूर्ण;

अटल व्योम pmu_dev_release(काष्ठा device *dev)
अणु
	kमुक्त(dev);
पूर्ण

अटल पूर्णांक pmu_dev_alloc(काष्ठा pmu *pmu)
अणु
	पूर्णांक ret = -ENOMEM;

	pmu->dev = kzalloc(माप(काष्ठा device), GFP_KERNEL);
	अगर (!pmu->dev)
		जाओ out;

	pmu->dev->groups = pmu->attr_groups;
	device_initialize(pmu->dev);
	ret = dev_set_name(pmu->dev, "%s", pmu->name);
	अगर (ret)
		जाओ मुक्त_dev;

	dev_set_drvdata(pmu->dev, pmu);
	pmu->dev->bus = &pmu_bus;
	pmu->dev->release = pmu_dev_release;
	ret = device_add(pmu->dev);
	अगर (ret)
		जाओ मुक्त_dev;

	/* For PMUs with address filters, throw in an extra attribute: */
	अगर (pmu->nr_addr_filters)
		ret = device_create_file(pmu->dev, &dev_attr_nr_addr_filters);

	अगर (ret)
		जाओ del_dev;

	अगर (pmu->attr_update)
		ret = sysfs_update_groups(&pmu->dev->kobj, pmu->attr_update);

	अगर (ret)
		जाओ del_dev;

out:
	वापस ret;

del_dev:
	device_del(pmu->dev);

मुक्त_dev:
	put_device(pmu->dev);
	जाओ out;
पूर्ण

अटल काष्ठा lock_class_key cpuctx_mutex;
अटल काष्ठा lock_class_key cpuctx_lock;

पूर्णांक perf_pmu_रेजिस्टर(काष्ठा pmu *pmu, स्थिर अक्षर *name, पूर्णांक type)
अणु
	पूर्णांक cpu, ret, max = PERF_TYPE_MAX;

	mutex_lock(&pmus_lock);
	ret = -ENOMEM;
	pmu->pmu_disable_count = alloc_percpu(पूर्णांक);
	अगर (!pmu->pmu_disable_count)
		जाओ unlock;

	pmu->type = -1;
	अगर (!name)
		जाओ skip_type;
	pmu->name = name;

	अगर (type != PERF_TYPE_SOFTWARE) अणु
		अगर (type >= 0)
			max = type;

		ret = idr_alloc(&pmu_idr, pmu, max, 0, GFP_KERNEL);
		अगर (ret < 0)
			जाओ मुक्त_pdc;

		WARN_ON(type >= 0 && ret != type);

		type = ret;
	पूर्ण
	pmu->type = type;

	अगर (pmu_bus_running) अणु
		ret = pmu_dev_alloc(pmu);
		अगर (ret)
			जाओ मुक्त_idr;
	पूर्ण

skip_type:
	अगर (pmu->task_ctx_nr == perf_hw_context) अणु
		अटल पूर्णांक hw_context_taken = 0;

		/*
		 * Other than प्रणालीs with heterogeneous CPUs, it never makes
		 * sense क्रम two PMUs to share perf_hw_context. PMUs which are
		 * uncore must use perf_invalid_context.
		 */
		अगर (WARN_ON_ONCE(hw_context_taken &&
		    !(pmu->capabilities & PERF_PMU_CAP_HETEROGENEOUS_CPUS)))
			pmu->task_ctx_nr = perf_invalid_context;

		hw_context_taken = 1;
	पूर्ण

	pmu->pmu_cpu_context = find_pmu_context(pmu->task_ctx_nr);
	अगर (pmu->pmu_cpu_context)
		जाओ got_cpu_context;

	ret = -ENOMEM;
	pmu->pmu_cpu_context = alloc_percpu(काष्ठा perf_cpu_context);
	अगर (!pmu->pmu_cpu_context)
		जाओ मुक्त_dev;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा perf_cpu_context *cpuctx;

		cpuctx = per_cpu_ptr(pmu->pmu_cpu_context, cpu);
		__perf_event_init_context(&cpuctx->ctx);
		lockdep_set_class(&cpuctx->ctx.mutex, &cpuctx_mutex);
		lockdep_set_class(&cpuctx->ctx.lock, &cpuctx_lock);
		cpuctx->ctx.pmu = pmu;
		cpuctx->online = cpumask_test_cpu(cpu, perf_online_mask);

		__perf_mux_hrसमयr_init(cpuctx, cpu);

		cpuctx->heap_size = ARRAY_SIZE(cpuctx->heap_शेष);
		cpuctx->heap = cpuctx->heap_शेष;
	पूर्ण

got_cpu_context:
	अगर (!pmu->start_txn) अणु
		अगर (pmu->pmu_enable) अणु
			/*
			 * If we have pmu_enable/pmu_disable calls, install
			 * transaction stubs that use that to try and batch
			 * hardware accesses.
			 */
			pmu->start_txn  = perf_pmu_start_txn;
			pmu->commit_txn = perf_pmu_commit_txn;
			pmu->cancel_txn = perf_pmu_cancel_txn;
		पूर्ण अन्यथा अणु
			pmu->start_txn  = perf_pmu_nop_txn;
			pmu->commit_txn = perf_pmu_nop_पूर्णांक;
			pmu->cancel_txn = perf_pmu_nop_व्योम;
		पूर्ण
	पूर्ण

	अगर (!pmu->pmu_enable) अणु
		pmu->pmu_enable  = perf_pmu_nop_व्योम;
		pmu->pmu_disable = perf_pmu_nop_व्योम;
	पूर्ण

	अगर (!pmu->check_period)
		pmu->check_period = perf_event_nop_पूर्णांक;

	अगर (!pmu->event_idx)
		pmu->event_idx = perf_event_idx_शेष;

	/*
	 * Ensure the TYPE_SOFTWARE PMUs are at the head of the list,
	 * since these cannot be in the IDR. This way the linear search
	 * is fast, provided a valid software event is provided.
	 */
	अगर (type == PERF_TYPE_SOFTWARE || !name)
		list_add_rcu(&pmu->entry, &pmus);
	अन्यथा
		list_add_tail_rcu(&pmu->entry, &pmus);

	atomic_set(&pmu->exclusive_cnt, 0);
	ret = 0;
unlock:
	mutex_unlock(&pmus_lock);

	वापस ret;

मुक्त_dev:
	device_del(pmu->dev);
	put_device(pmu->dev);

मुक्त_idr:
	अगर (pmu->type != PERF_TYPE_SOFTWARE)
		idr_हटाओ(&pmu_idr, pmu->type);

मुक्त_pdc:
	मुक्त_percpu(pmu->pmu_disable_count);
	जाओ unlock;
पूर्ण
EXPORT_SYMBOL_GPL(perf_pmu_रेजिस्टर);

व्योम perf_pmu_unरेजिस्टर(काष्ठा pmu *pmu)
अणु
	mutex_lock(&pmus_lock);
	list_del_rcu(&pmu->entry);

	/*
	 * We dereference the pmu list under both SRCU and regular RCU, so
	 * synchronize against both of those.
	 */
	synchronize_srcu(&pmus_srcu);
	synchronize_rcu();

	मुक्त_percpu(pmu->pmu_disable_count);
	अगर (pmu->type != PERF_TYPE_SOFTWARE)
		idr_हटाओ(&pmu_idr, pmu->type);
	अगर (pmu_bus_running) अणु
		अगर (pmu->nr_addr_filters)
			device_हटाओ_file(pmu->dev, &dev_attr_nr_addr_filters);
		device_del(pmu->dev);
		put_device(pmu->dev);
	पूर्ण
	मुक्त_pmu_context(pmu);
	mutex_unlock(&pmus_lock);
पूर्ण
EXPORT_SYMBOL_GPL(perf_pmu_unरेजिस्टर);

अटल अंतरभूत bool has_extended_regs(काष्ठा perf_event *event)
अणु
	वापस (event->attr.sample_regs_user & PERF_REG_EXTENDED_MASK) ||
	       (event->attr.sample_regs_पूर्णांकr & PERF_REG_EXTENDED_MASK);
पूर्ण

अटल पूर्णांक perf_try_init_event(काष्ठा pmu *pmu, काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_context *ctx = शून्य;
	पूर्णांक ret;

	अगर (!try_module_get(pmu->module))
		वापस -ENODEV;

	/*
	 * A number of pmu->event_init() methods iterate the sibling_list to,
	 * क्रम example, validate अगर the group fits on the PMU. Thereक्रमe,
	 * अगर this is a sibling event, acquire the ctx->mutex to protect
	 * the sibling_list.
	 */
	अगर (event->group_leader != event && pmu->task_ctx_nr != perf_sw_context) अणु
		/*
		 * This ctx->mutex can nest when we're called through
		 * inheritance. See the perf_event_ctx_lock_nested() comment.
		 */
		ctx = perf_event_ctx_lock_nested(event->group_leader,
						 SINGLE_DEPTH_NESTING);
		BUG_ON(!ctx);
	पूर्ण

	event->pmu = pmu;
	ret = pmu->event_init(event);

	अगर (ctx)
		perf_event_ctx_unlock(event->group_leader, ctx);

	अगर (!ret) अणु
		अगर (!(pmu->capabilities & PERF_PMU_CAP_EXTENDED_REGS) &&
		    has_extended_regs(event))
			ret = -EOPNOTSUPP;

		अगर (pmu->capabilities & PERF_PMU_CAP_NO_EXCLUDE &&
		    event_has_any_exclude_flag(event))
			ret = -EINVAL;

		अगर (ret && event->destroy)
			event->destroy(event);
	पूर्ण

	अगर (ret)
		module_put(pmu->module);

	वापस ret;
पूर्ण

अटल काष्ठा pmu *perf_init_event(काष्ठा perf_event *event)
अणु
	bool extended_type = false;
	पूर्णांक idx, type, ret;
	काष्ठा pmu *pmu;

	idx = srcu_पढ़ो_lock(&pmus_srcu);

	/* Try parent's PMU first: */
	अगर (event->parent && event->parent->pmu) अणु
		pmu = event->parent->pmu;
		ret = perf_try_init_event(pmu, event);
		अगर (!ret)
			जाओ unlock;
	पूर्ण

	/*
	 * PERF_TYPE_HARDWARE and PERF_TYPE_HW_CACHE
	 * are often aliases क्रम PERF_TYPE_RAW.
	 */
	type = event->attr.type;
	अगर (type == PERF_TYPE_HARDWARE || type == PERF_TYPE_HW_CACHE) अणु
		type = event->attr.config >> PERF_PMU_TYPE_SHIFT;
		अगर (!type) अणु
			type = PERF_TYPE_RAW;
		पूर्ण अन्यथा अणु
			extended_type = true;
			event->attr.config &= PERF_HW_EVENT_MASK;
		पूर्ण
	पूर्ण

again:
	rcu_पढ़ो_lock();
	pmu = idr_find(&pmu_idr, type);
	rcu_पढ़ो_unlock();
	अगर (pmu) अणु
		अगर (event->attr.type != type && type != PERF_TYPE_RAW &&
		    !(pmu->capabilities & PERF_PMU_CAP_EXTENDED_HW_TYPE))
			जाओ fail;

		ret = perf_try_init_event(pmu, event);
		अगर (ret == -ENOENT && event->attr.type != type && !extended_type) अणु
			type = event->attr.type;
			जाओ again;
		पूर्ण

		अगर (ret)
			pmu = ERR_PTR(ret);

		जाओ unlock;
	पूर्ण

	list_क्रम_each_entry_rcu(pmu, &pmus, entry, lockdep_is_held(&pmus_srcu)) अणु
		ret = perf_try_init_event(pmu, event);
		अगर (!ret)
			जाओ unlock;

		अगर (ret != -ENOENT) अणु
			pmu = ERR_PTR(ret);
			जाओ unlock;
		पूर्ण
	पूर्ण
fail:
	pmu = ERR_PTR(-ENOENT);
unlock:
	srcu_पढ़ो_unlock(&pmus_srcu, idx);

	वापस pmu;
पूर्ण

अटल व्योम attach_sb_event(काष्ठा perf_event *event)
अणु
	काष्ठा pmu_event_list *pel = per_cpu_ptr(&pmu_sb_events, event->cpu);

	raw_spin_lock(&pel->lock);
	list_add_rcu(&event->sb_list, &pel->list);
	raw_spin_unlock(&pel->lock);
पूर्ण

/*
 * We keep a list of all !task (and thereक्रमe per-cpu) events
 * that need to receive side-band records.
 *
 * This aव्योमs having to scan all the various PMU per-cpu contexts
 * looking क्रम them.
 */
अटल व्योम account_pmu_sb_event(काष्ठा perf_event *event)
अणु
	अगर (is_sb_event(event))
		attach_sb_event(event);
पूर्ण

अटल व्योम account_event_cpu(काष्ठा perf_event *event, पूर्णांक cpu)
अणु
	अगर (event->parent)
		वापस;

	अगर (is_cgroup_event(event))
		atomic_inc(&per_cpu(perf_cgroup_events, cpu));
पूर्ण

/* Freq events need the tick to stay alive (see perf_event_task_tick). */
अटल व्योम account_freq_event_nohz(व्योम)
अणु
#अगर_घोषित CONFIG_NO_HZ_FULL
	/* Lock so we करोn't race with concurrent unaccount */
	spin_lock(&nr_freq_lock);
	अगर (atomic_inc_वापस(&nr_freq_events) == 1)
		tick_nohz_dep_set(TICK_DEP_BIT_PERF_EVENTS);
	spin_unlock(&nr_freq_lock);
#पूर्ण_अगर
पूर्ण

अटल व्योम account_freq_event(व्योम)
अणु
	अगर (tick_nohz_full_enabled())
		account_freq_event_nohz();
	अन्यथा
		atomic_inc(&nr_freq_events);
पूर्ण


अटल व्योम account_event(काष्ठा perf_event *event)
अणु
	bool inc = false;

	अगर (event->parent)
		वापस;

	अगर (event->attach_state & (PERF_ATTACH_TASK | PERF_ATTACH_SCHED_CB))
		inc = true;
	अगर (event->attr.mmap || event->attr.mmap_data)
		atomic_inc(&nr_mmap_events);
	अगर (event->attr.build_id)
		atomic_inc(&nr_build_id_events);
	अगर (event->attr.comm)
		atomic_inc(&nr_comm_events);
	अगर (event->attr.namespaces)
		atomic_inc(&nr_namespaces_events);
	अगर (event->attr.cgroup)
		atomic_inc(&nr_cgroup_events);
	अगर (event->attr.task)
		atomic_inc(&nr_task_events);
	अगर (event->attr.freq)
		account_freq_event();
	अगर (event->attr.context_चयन) अणु
		atomic_inc(&nr_चयन_events);
		inc = true;
	पूर्ण
	अगर (has_branch_stack(event))
		inc = true;
	अगर (is_cgroup_event(event))
		inc = true;
	अगर (event->attr.ksymbol)
		atomic_inc(&nr_ksymbol_events);
	अगर (event->attr.bpf_event)
		atomic_inc(&nr_bpf_events);
	अगर (event->attr.text_poke)
		atomic_inc(&nr_text_poke_events);

	अगर (inc) अणु
		/*
		 * We need the mutex here because अटल_branch_enable()
		 * must complete *beक्रमe* the perf_sched_count increment
		 * becomes visible.
		 */
		अगर (atomic_inc_not_zero(&perf_sched_count))
			जाओ enabled;

		mutex_lock(&perf_sched_mutex);
		अगर (!atomic_पढ़ो(&perf_sched_count)) अणु
			अटल_branch_enable(&perf_sched_events);
			/*
			 * Guarantee that all CPUs observe they key change and
			 * call the perf scheduling hooks beक्रमe proceeding to
			 * install events that need them.
			 */
			synchronize_rcu();
		पूर्ण
		/*
		 * Now that we have रुकोed क्रम the sync_sched(), allow further
		 * increments to by-pass the mutex.
		 */
		atomic_inc(&perf_sched_count);
		mutex_unlock(&perf_sched_mutex);
	पूर्ण
enabled:

	account_event_cpu(event, event->cpu);

	account_pmu_sb_event(event);
पूर्ण

/*
 * Allocate and initialize an event काष्ठाure
 */
अटल काष्ठा perf_event *
perf_event_alloc(काष्ठा perf_event_attr *attr, पूर्णांक cpu,
		 काष्ठा task_काष्ठा *task,
		 काष्ठा perf_event *group_leader,
		 काष्ठा perf_event *parent_event,
		 perf_overflow_handler_t overflow_handler,
		 व्योम *context, पूर्णांक cgroup_fd)
अणु
	काष्ठा pmu *pmu;
	काष्ठा perf_event *event;
	काष्ठा hw_perf_event *hwc;
	दीर्घ err = -EINVAL;
	पूर्णांक node;

	अगर ((अचिन्हित)cpu >= nr_cpu_ids) अणु
		अगर (!task || cpu != -1)
			वापस ERR_PTR(-EINVAL);
	पूर्ण
	अगर (attr->sigtrap && !task) अणु
		/* Requires a task: aव्योम संकेतling अक्रमom tasks. */
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	node = (cpu >= 0) ? cpu_to_node(cpu) : -1;
	event = kmem_cache_alloc_node(perf_event_cache, GFP_KERNEL | __GFP_ZERO,
				      node);
	अगर (!event)
		वापस ERR_PTR(-ENOMEM);

	/*
	 * Single events are their own group leaders, with an
	 * empty sibling list:
	 */
	अगर (!group_leader)
		group_leader = event;

	mutex_init(&event->child_mutex);
	INIT_LIST_HEAD(&event->child_list);

	INIT_LIST_HEAD(&event->event_entry);
	INIT_LIST_HEAD(&event->sibling_list);
	INIT_LIST_HEAD(&event->active_list);
	init_event_group(event);
	INIT_LIST_HEAD(&event->rb_entry);
	INIT_LIST_HEAD(&event->active_entry);
	INIT_LIST_HEAD(&event->addr_filters.list);
	INIT_HLIST_NODE(&event->hlist_entry);


	init_रुकोqueue_head(&event->रुकोq);
	event->pending_disable = -1;
	init_irq_work(&event->pending, perf_pending_event);

	mutex_init(&event->mmap_mutex);
	raw_spin_lock_init(&event->addr_filters.lock);

	atomic_दीर्घ_set(&event->refcount, 1);
	event->cpu		= cpu;
	event->attr		= *attr;
	event->group_leader	= group_leader;
	event->pmu		= शून्य;
	event->oncpu		= -1;

	event->parent		= parent_event;

	event->ns		= get_pid_ns(task_active_pid_ns(current));
	event->id		= atomic64_inc_वापस(&perf_event_id);

	event->state		= PERF_EVENT_STATE_INACTIVE;

	अगर (event->attr.sigtrap)
		atomic_set(&event->event_limit, 1);

	अगर (task) अणु
		event->attach_state = PERF_ATTACH_TASK;
		/*
		 * XXX pmu::event_init needs to know what task to account to
		 * and we cannot use the ctx inक्रमmation because we need the
		 * pmu beक्रमe we get a ctx.
		 */
		event->hw.target = get_task_काष्ठा(task);
	पूर्ण

	event->घड़ी = &local_घड़ी;
	अगर (parent_event)
		event->घड़ी = parent_event->घड़ी;

	अगर (!overflow_handler && parent_event) अणु
		overflow_handler = parent_event->overflow_handler;
		context = parent_event->overflow_handler_context;
#अगर defined(CONFIG_BPF_SYSCALL) && defined(CONFIG_EVENT_TRACING)
		अगर (overflow_handler == bpf_overflow_handler) अणु
			काष्ठा bpf_prog *prog = parent_event->prog;

			bpf_prog_inc(prog);
			event->prog = prog;
			event->orig_overflow_handler =
				parent_event->orig_overflow_handler;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	अगर (overflow_handler) अणु
		event->overflow_handler	= overflow_handler;
		event->overflow_handler_context = context;
	पूर्ण अन्यथा अगर (is_ग_लिखो_backward(event))अणु
		event->overflow_handler = perf_event_output_backward;
		event->overflow_handler_context = शून्य;
	पूर्ण अन्यथा अणु
		event->overflow_handler = perf_event_output_क्रमward;
		event->overflow_handler_context = शून्य;
	पूर्ण

	perf_event__state_init(event);

	pmu = शून्य;

	hwc = &event->hw;
	hwc->sample_period = attr->sample_period;
	अगर (attr->freq && attr->sample_freq)
		hwc->sample_period = 1;
	hwc->last_period = hwc->sample_period;

	local64_set(&hwc->period_left, hwc->sample_period);

	/*
	 * We currently करो not support PERF_SAMPLE_READ on inherited events.
	 * See perf_output_पढ़ो().
	 */
	अगर (attr->inherit && (attr->sample_type & PERF_SAMPLE_READ))
		जाओ err_ns;

	अगर (!has_branch_stack(event))
		event->attr.branch_sample_type = 0;

	pmu = perf_init_event(event);
	अगर (IS_ERR(pmu)) अणु
		err = PTR_ERR(pmu);
		जाओ err_ns;
	पूर्ण

	/*
	 * Disallow uncore-cgroup events, they करोn't make sense as the cgroup will
	 * be dअगरferent on other CPUs in the uncore mask.
	 */
	अगर (pmu->task_ctx_nr == perf_invalid_context && cgroup_fd != -1) अणु
		err = -EINVAL;
		जाओ err_pmu;
	पूर्ण

	अगर (event->attr.aux_output &&
	    !(pmu->capabilities & PERF_PMU_CAP_AUX_OUTPUT)) अणु
		err = -EOPNOTSUPP;
		जाओ err_pmu;
	पूर्ण

	अगर (cgroup_fd != -1) अणु
		err = perf_cgroup_connect(cgroup_fd, event, attr, group_leader);
		अगर (err)
			जाओ err_pmu;
	पूर्ण

	err = exclusive_event_init(event);
	अगर (err)
		जाओ err_pmu;

	अगर (has_addr_filter(event)) अणु
		event->addr_filter_ranges = kसुस्मृति(pmu->nr_addr_filters,
						    माप(काष्ठा perf_addr_filter_range),
						    GFP_KERNEL);
		अगर (!event->addr_filter_ranges) अणु
			err = -ENOMEM;
			जाओ err_per_task;
		पूर्ण

		/*
		 * Clone the parent's vma offsets: they are valid until exec()
		 * even अगर the mm is not shared with the parent.
		 */
		अगर (event->parent) अणु
			काष्ठा perf_addr_filters_head *अगरh = perf_event_addr_filters(event);

			raw_spin_lock_irq(&अगरh->lock);
			स_नकल(event->addr_filter_ranges,
			       event->parent->addr_filter_ranges,
			       pmu->nr_addr_filters * माप(काष्ठा perf_addr_filter_range));
			raw_spin_unlock_irq(&अगरh->lock);
		पूर्ण

		/* क्रमce hw sync on the address filters */
		event->addr_filters_gen = 1;
	पूर्ण

	अगर (!event->parent) अणु
		अगर (event->attr.sample_type & PERF_SAMPLE_CALLCHAIN) अणु
			err = get_callchain_buffers(attr->sample_max_stack);
			अगर (err)
				जाओ err_addr_filters;
		पूर्ण
	पूर्ण

	err = security_perf_event_alloc(event);
	अगर (err)
		जाओ err_callchain_buffer;

	/* symmetric to unaccount_event() in _मुक्त_event() */
	account_event(event);

	वापस event;

err_callchain_buffer:
	अगर (!event->parent) अणु
		अगर (event->attr.sample_type & PERF_SAMPLE_CALLCHAIN)
			put_callchain_buffers();
	पूर्ण
err_addr_filters:
	kमुक्त(event->addr_filter_ranges);

err_per_task:
	exclusive_event_destroy(event);

err_pmu:
	अगर (is_cgroup_event(event))
		perf_detach_cgroup(event);
	अगर (event->destroy)
		event->destroy(event);
	module_put(pmu->module);
err_ns:
	अगर (event->ns)
		put_pid_ns(event->ns);
	अगर (event->hw.target)
		put_task_काष्ठा(event->hw.target);
	kmem_cache_मुक्त(perf_event_cache, event);

	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक perf_copy_attr(काष्ठा perf_event_attr __user *uattr,
			  काष्ठा perf_event_attr *attr)
अणु
	u32 size;
	पूर्णांक ret;

	/* Zero the full काष्ठाure, so that a लघु copy will be nice. */
	स_रखो(attr, 0, माप(*attr));

	ret = get_user(size, &uattr->size);
	अगर (ret)
		वापस ret;

	/* ABI compatibility quirk: */
	अगर (!size)
		size = PERF_ATTR_SIZE_VER0;
	अगर (size < PERF_ATTR_SIZE_VER0 || size > PAGE_SIZE)
		जाओ err_size;

	ret = copy_काष्ठा_from_user(attr, माप(*attr), uattr, size);
	अगर (ret) अणु
		अगर (ret == -E2BIG)
			जाओ err_size;
		वापस ret;
	पूर्ण

	attr->size = size;

	अगर (attr->__reserved_1 || attr->__reserved_2 || attr->__reserved_3)
		वापस -EINVAL;

	अगर (attr->sample_type & ~(PERF_SAMPLE_MAX-1))
		वापस -EINVAL;

	अगर (attr->पढ़ो_क्रमmat & ~(PERF_FORMAT_MAX-1))
		वापस -EINVAL;

	अगर (attr->sample_type & PERF_SAMPLE_BRANCH_STACK) अणु
		u64 mask = attr->branch_sample_type;

		/* only using defined bits */
		अगर (mask & ~(PERF_SAMPLE_BRANCH_MAX-1))
			वापस -EINVAL;

		/* at least one branch bit must be set */
		अगर (!(mask & ~PERF_SAMPLE_BRANCH_PLM_ALL))
			वापस -EINVAL;

		/* propagate priv level, when not set क्रम branch */
		अगर (!(mask & PERF_SAMPLE_BRANCH_PLM_ALL)) अणु

			/* exclude_kernel checked on syscall entry */
			अगर (!attr->exclude_kernel)
				mask |= PERF_SAMPLE_BRANCH_KERNEL;

			अगर (!attr->exclude_user)
				mask |= PERF_SAMPLE_BRANCH_USER;

			अगर (!attr->exclude_hv)
				mask |= PERF_SAMPLE_BRANCH_HV;
			/*
			 * adjust user setting (क्रम HW filter setup)
			 */
			attr->branch_sample_type = mask;
		पूर्ण
		/* privileged levels capture (kernel, hv): check permissions */
		अगर (mask & PERF_SAMPLE_BRANCH_PERM_PLM) अणु
			ret = perf_allow_kernel(attr);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	अगर (attr->sample_type & PERF_SAMPLE_REGS_USER) अणु
		ret = perf_reg_validate(attr->sample_regs_user);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (attr->sample_type & PERF_SAMPLE_STACK_USER) अणु
		अगर (!arch_perf_have_user_stack_dump())
			वापस -ENOSYS;

		/*
		 * We have __u32 type क्रम the size, but so far
		 * we can only use __u16 as maximum due to the
		 * __u16 sample size limit.
		 */
		अगर (attr->sample_stack_user >= अच_लघु_उच्च)
			वापस -EINVAL;
		अन्यथा अगर (!IS_ALIGNED(attr->sample_stack_user, माप(u64)))
			वापस -EINVAL;
	पूर्ण

	अगर (!attr->sample_max_stack)
		attr->sample_max_stack = sysctl_perf_event_max_stack;

	अगर (attr->sample_type & PERF_SAMPLE_REGS_INTR)
		ret = perf_reg_validate(attr->sample_regs_पूर्णांकr);

#अगर_अघोषित CONFIG_CGROUP_PERF
	अगर (attr->sample_type & PERF_SAMPLE_CGROUP)
		वापस -EINVAL;
#पूर्ण_अगर
	अगर ((attr->sample_type & PERF_SAMPLE_WEIGHT) &&
	    (attr->sample_type & PERF_SAMPLE_WEIGHT_STRUCT))
		वापस -EINVAL;

	अगर (!attr->inherit && attr->inherit_thपढ़ो)
		वापस -EINVAL;

	अगर (attr->हटाओ_on_exec && attr->enable_on_exec)
		वापस -EINVAL;

	अगर (attr->sigtrap && !attr->हटाओ_on_exec)
		वापस -EINVAL;

out:
	वापस ret;

err_size:
	put_user(माप(*attr), &uattr->size);
	ret = -E2BIG;
	जाओ out;
पूर्ण

अटल पूर्णांक
perf_event_set_output(काष्ठा perf_event *event, काष्ठा perf_event *output_event)
अणु
	काष्ठा perf_buffer *rb = शून्य;
	पूर्णांक ret = -EINVAL;

	अगर (!output_event)
		जाओ set;

	/* करोn't allow circular references */
	अगर (event == output_event)
		जाओ out;

	/*
	 * Don't allow cross-cpu buffers
	 */
	अगर (output_event->cpu != event->cpu)
		जाओ out;

	/*
	 * If its not a per-cpu rb, it must be the same task.
	 */
	अगर (output_event->cpu == -1 && output_event->ctx != event->ctx)
		जाओ out;

	/*
	 * Mixing घड़ीs in the same buffer is trouble you करोn't need.
	 */
	अगर (output_event->घड़ी != event->घड़ी)
		जाओ out;

	/*
	 * Either writing ring buffer from beginning or from end.
	 * Mixing is not allowed.
	 */
	अगर (is_ग_लिखो_backward(output_event) != is_ग_लिखो_backward(event))
		जाओ out;

	/*
	 * If both events generate aux data, they must be on the same PMU
	 */
	अगर (has_aux(event) && has_aux(output_event) &&
	    event->pmu != output_event->pmu)
		जाओ out;

set:
	mutex_lock(&event->mmap_mutex);
	/* Can't redirect output if we've got an active mmap() */
	अगर (atomic_पढ़ो(&event->mmap_count))
		जाओ unlock;

	अगर (output_event) अणु
		/* get the rb we want to redirect to */
		rb = ring_buffer_get(output_event);
		अगर (!rb)
			जाओ unlock;
	पूर्ण

	ring_buffer_attach(event, rb);

	ret = 0;
unlock:
	mutex_unlock(&event->mmap_mutex);

out:
	वापस ret;
पूर्ण

अटल व्योम mutex_lock_द्विगुन(काष्ठा mutex *a, काष्ठा mutex *b)
अणु
	अगर (b < a)
		swap(a, b);

	mutex_lock(a);
	mutex_lock_nested(b, SINGLE_DEPTH_NESTING);
पूर्ण

अटल पूर्णांक perf_event_set_घड़ी(काष्ठा perf_event *event, घड़ीid_t clk_id)
अणु
	bool nmi_safe = false;

	चयन (clk_id) अणु
	हाल CLOCK_MONOTONIC:
		event->घड़ी = &kसमय_get_mono_fast_ns;
		nmi_safe = true;
		अवरोध;

	हाल CLOCK_MONOTONIC_RAW:
		event->घड़ी = &kसमय_get_raw_fast_ns;
		nmi_safe = true;
		अवरोध;

	हाल CLOCK_REALTIME:
		event->घड़ी = &kसमय_get_real_ns;
		अवरोध;

	हाल CLOCK_BOOTTIME:
		event->घड़ी = &kसमय_get_bootसमय_ns;
		अवरोध;

	हाल CLOCK_TAI:
		event->घड़ी = &kसमय_get_घड़ीtai_ns;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!nmi_safe && !(event->pmu->capabilities & PERF_PMU_CAP_NO_NMI))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * Variation on perf_event_ctx_lock_nested(), except we take two context
 * mutexes.
 */
अटल काष्ठा perf_event_context *
__perf_event_ctx_lock_द्विगुन(काष्ठा perf_event *group_leader,
			     काष्ठा perf_event_context *ctx)
अणु
	काष्ठा perf_event_context *gctx;

again:
	rcu_पढ़ो_lock();
	gctx = READ_ONCE(group_leader->ctx);
	अगर (!refcount_inc_not_zero(&gctx->refcount)) अणु
		rcu_पढ़ो_unlock();
		जाओ again;
	पूर्ण
	rcu_पढ़ो_unlock();

	mutex_lock_द्विगुन(&gctx->mutex, &ctx->mutex);

	अगर (group_leader->ctx != gctx) अणु
		mutex_unlock(&ctx->mutex);
		mutex_unlock(&gctx->mutex);
		put_ctx(gctx);
		जाओ again;
	पूर्ण

	वापस gctx;
पूर्ण

/**
 * sys_perf_event_खोलो - खोलो a perक्रमmance event, associate it to a task/cpu
 *
 * @attr_uptr:	event_id type attributes क्रम monitoring/sampling
 * @pid:		target pid
 * @cpu:		target cpu
 * @group_fd:		group leader event fd
 */
SYSCALL_DEFINE5(perf_event_खोलो,
		काष्ठा perf_event_attr __user *, attr_uptr,
		pid_t, pid, पूर्णांक, cpu, पूर्णांक, group_fd, अचिन्हित दीर्घ, flags)
अणु
	काष्ठा perf_event *group_leader = शून्य, *output_event = शून्य;
	काष्ठा perf_event *event, *sibling;
	काष्ठा perf_event_attr attr;
	काष्ठा perf_event_context *ctx, *gctx;
	काष्ठा file *event_file = शून्य;
	काष्ठा fd group = अणुशून्य, 0पूर्ण;
	काष्ठा task_काष्ठा *task = शून्य;
	काष्ठा pmu *pmu;
	पूर्णांक event_fd;
	पूर्णांक move_group = 0;
	पूर्णांक err;
	पूर्णांक f_flags = O_RDWR;
	पूर्णांक cgroup_fd = -1;

	/* क्रम future expandability... */
	अगर (flags & ~PERF_FLAG_ALL)
		वापस -EINVAL;

	/* Do we allow access to perf_event_खोलो(2) ? */
	err = security_perf_event_खोलो(&attr, PERF_SECURITY_OPEN);
	अगर (err)
		वापस err;

	err = perf_copy_attr(attr_uptr, &attr);
	अगर (err)
		वापस err;

	अगर (!attr.exclude_kernel) अणु
		err = perf_allow_kernel(&attr);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (attr.namespaces) अणु
		अगर (!perfmon_capable())
			वापस -EACCES;
	पूर्ण

	अगर (attr.freq) अणु
		अगर (attr.sample_freq > sysctl_perf_event_sample_rate)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (attr.sample_period & (1ULL << 63))
			वापस -EINVAL;
	पूर्ण

	/* Only privileged users can get physical addresses */
	अगर ((attr.sample_type & PERF_SAMPLE_PHYS_ADDR)) अणु
		err = perf_allow_kernel(&attr);
		अगर (err)
			वापस err;
	पूर्ण

	/* REGS_INTR can leak data, lockकरोwn must prevent this */
	अगर (attr.sample_type & PERF_SAMPLE_REGS_INTR) अणु
		err = security_locked_करोwn(LOCKDOWN_PERF);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * In cgroup mode, the pid argument is used to pass the fd
	 * खोलोed to the cgroup directory in cgroupfs. The cpu argument
	 * designates the cpu on which to monitor thपढ़ोs from that
	 * cgroup.
	 */
	अगर ((flags & PERF_FLAG_PID_CGROUP) && (pid == -1 || cpu == -1))
		वापस -EINVAL;

	अगर (flags & PERF_FLAG_FD_CLOEXEC)
		f_flags |= O_CLOEXEC;

	event_fd = get_unused_fd_flags(f_flags);
	अगर (event_fd < 0)
		वापस event_fd;

	अगर (group_fd != -1) अणु
		err = perf_fget_light(group_fd, &group);
		अगर (err)
			जाओ err_fd;
		group_leader = group.file->निजी_data;
		अगर (flags & PERF_FLAG_FD_OUTPUT)
			output_event = group_leader;
		अगर (flags & PERF_FLAG_FD_NO_GROUP)
			group_leader = शून्य;
	पूर्ण

	अगर (pid != -1 && !(flags & PERF_FLAG_PID_CGROUP)) अणु
		task = find_lively_task_by_vpid(pid);
		अगर (IS_ERR(task)) अणु
			err = PTR_ERR(task);
			जाओ err_group_fd;
		पूर्ण
	पूर्ण

	अगर (task && group_leader &&
	    group_leader->attr.inherit != attr.inherit) अणु
		err = -EINVAL;
		जाओ err_task;
	पूर्ण

	अगर (flags & PERF_FLAG_PID_CGROUP)
		cgroup_fd = pid;

	event = perf_event_alloc(&attr, cpu, task, group_leader, शून्य,
				 शून्य, शून्य, cgroup_fd);
	अगर (IS_ERR(event)) अणु
		err = PTR_ERR(event);
		जाओ err_task;
	पूर्ण

	अगर (is_sampling_event(event)) अणु
		अगर (event->pmu->capabilities & PERF_PMU_CAP_NO_INTERRUPT) अणु
			err = -EOPNOTSUPP;
			जाओ err_alloc;
		पूर्ण
	पूर्ण

	/*
	 * Special हाल software events and allow them to be part of
	 * any hardware group.
	 */
	pmu = event->pmu;

	अगर (attr.use_घड़ीid) अणु
		err = perf_event_set_घड़ी(event, attr.घड़ीid);
		अगर (err)
			जाओ err_alloc;
	पूर्ण

	अगर (pmu->task_ctx_nr == perf_sw_context)
		event->event_caps |= PERF_EV_CAP_SOFTWARE;

	अगर (group_leader) अणु
		अगर (is_software_event(event) &&
		    !in_software_context(group_leader)) अणु
			/*
			 * If the event is a sw event, but the group_leader
			 * is on hw context.
			 *
			 * Allow the addition of software events to hw
			 * groups, this is safe because software events
			 * never fail to schedule.
			 */
			pmu = group_leader->ctx->pmu;
		पूर्ण अन्यथा अगर (!is_software_event(event) &&
			   is_software_event(group_leader) &&
			   (group_leader->group_caps & PERF_EV_CAP_SOFTWARE)) अणु
			/*
			 * In हाल the group is a pure software group, and we
			 * try to add a hardware event, move the whole group to
			 * the hardware context.
			 */
			move_group = 1;
		पूर्ण
	पूर्ण

	/*
	 * Get the target context (task or percpu):
	 */
	ctx = find_get_context(pmu, task, event);
	अगर (IS_ERR(ctx)) अणु
		err = PTR_ERR(ctx);
		जाओ err_alloc;
	पूर्ण

	/*
	 * Look up the group leader (we will attach this event to it):
	 */
	अगर (group_leader) अणु
		err = -EINVAL;

		/*
		 * Do not allow a recursive hierarchy (this new sibling
		 * becoming part of another group-sibling):
		 */
		अगर (group_leader->group_leader != group_leader)
			जाओ err_context;

		/* All events in a group should have the same घड़ी */
		अगर (group_leader->घड़ी != event->घड़ी)
			जाओ err_context;

		/*
		 * Make sure we're both events क्रम the same CPU;
		 * grouping events क्रम dअगरferent CPUs is broken; since
		 * you can never concurrently schedule them anyhow.
		 */
		अगर (group_leader->cpu != event->cpu)
			जाओ err_context;

		/*
		 * Make sure we're both on the same task, or both
		 * per-CPU events.
		 */
		अगर (group_leader->ctx->task != ctx->task)
			जाओ err_context;

		/*
		 * Do not allow to attach to a group in a dअगरferent task
		 * or CPU context. If we're moving SW events, we'll fix
		 * this up later, so allow that.
		 */
		अगर (!move_group && group_leader->ctx != ctx)
			जाओ err_context;

		/*
		 * Only a group leader can be exclusive or pinned
		 */
		अगर (attr.exclusive || attr.pinned)
			जाओ err_context;
	पूर्ण

	अगर (output_event) अणु
		err = perf_event_set_output(event, output_event);
		अगर (err)
			जाओ err_context;
	पूर्ण

	event_file = anon_inode_getfile("[perf_event]", &perf_fops, event,
					f_flags);
	अगर (IS_ERR(event_file)) अणु
		err = PTR_ERR(event_file);
		event_file = शून्य;
		जाओ err_context;
	पूर्ण

	अगर (task) अणु
		err = करोwn_पढ़ो_पूर्णांकerruptible(&task->संकेत->exec_update_lock);
		अगर (err)
			जाओ err_file;

		/*
		 * Preserve ptrace permission check क्रम backwards compatibility.
		 *
		 * We must hold exec_update_lock across this and any potential
		 * perf_install_in_context() call क्रम this new event to
		 * serialize against exec() altering our credentials (and the
		 * perf_event_निकास_task() that could imply).
		 */
		err = -EACCES;
		अगर (!perfmon_capable() && !ptrace_may_access(task, PTRACE_MODE_READ_REALCREDS))
			जाओ err_cred;
	पूर्ण

	अगर (move_group) अणु
		gctx = __perf_event_ctx_lock_द्विगुन(group_leader, ctx);

		अगर (gctx->task == TASK_TOMBSTONE) अणु
			err = -ESRCH;
			जाओ err_locked;
		पूर्ण

		/*
		 * Check अगर we raced against another sys_perf_event_खोलो() call
		 * moving the software group underneath us.
		 */
		अगर (!(group_leader->group_caps & PERF_EV_CAP_SOFTWARE)) अणु
			/*
			 * If someone moved the group out from under us, check
			 * अगर this new event wound up on the same ctx, अगर so
			 * its the regular !move_group हाल, otherwise fail.
			 */
			अगर (gctx != ctx) अणु
				err = -EINVAL;
				जाओ err_locked;
			पूर्ण अन्यथा अणु
				perf_event_ctx_unlock(group_leader, gctx);
				move_group = 0;
			पूर्ण
		पूर्ण

		/*
		 * Failure to create exclusive events वापसs -EBUSY.
		 */
		err = -EBUSY;
		अगर (!exclusive_event_installable(group_leader, ctx))
			जाओ err_locked;

		क्रम_each_sibling_event(sibling, group_leader) अणु
			अगर (!exclusive_event_installable(sibling, ctx))
				जाओ err_locked;
		पूर्ण
	पूर्ण अन्यथा अणु
		mutex_lock(&ctx->mutex);
	पूर्ण

	अगर (ctx->task == TASK_TOMBSTONE) अणु
		err = -ESRCH;
		जाओ err_locked;
	पूर्ण

	अगर (!perf_event_validate_size(event)) अणु
		err = -E2BIG;
		जाओ err_locked;
	पूर्ण

	अगर (!task) अणु
		/*
		 * Check अगर the @cpu we're creating an event क्रम is online.
		 *
		 * We use the perf_cpu_context::ctx::mutex to serialize against
		 * the hotplug notअगरiers. See perf_event_अणुinit,निकासपूर्ण_cpu().
		 */
		काष्ठा perf_cpu_context *cpuctx =
			container_of(ctx, काष्ठा perf_cpu_context, ctx);

		अगर (!cpuctx->online) अणु
			err = -ENODEV;
			जाओ err_locked;
		पूर्ण
	पूर्ण

	अगर (perf_need_aux_event(event) && !perf_get_aux_event(event, group_leader)) अणु
		err = -EINVAL;
		जाओ err_locked;
	पूर्ण

	/*
	 * Must be under the same ctx::mutex as perf_install_in_context(),
	 * because we need to serialize with concurrent event creation.
	 */
	अगर (!exclusive_event_installable(event, ctx)) अणु
		err = -EBUSY;
		जाओ err_locked;
	पूर्ण

	WARN_ON_ONCE(ctx->parent_ctx);

	/*
	 * This is the poपूर्णांक on no वापस; we cannot fail hereafter. This is
	 * where we start modअगरying current state.
	 */

	अगर (move_group) अणु
		/*
		 * See perf_event_ctx_lock() क्रम comments on the details
		 * of swizzling perf_event::ctx.
		 */
		perf_हटाओ_from_context(group_leader, 0);
		put_ctx(gctx);

		क्रम_each_sibling_event(sibling, group_leader) अणु
			perf_हटाओ_from_context(sibling, 0);
			put_ctx(gctx);
		पूर्ण

		/*
		 * Wait क्रम everybody to stop referencing the events through
		 * the old lists, beक्रमe installing it on new lists.
		 */
		synchronize_rcu();

		/*
		 * Install the group siblings beक्रमe the group leader.
		 *
		 * Because a group leader will try and install the entire group
		 * (through the sibling list, which is still in-tact), we can
		 * end up with siblings installed in the wrong context.
		 *
		 * By installing siblings first we NO-OP because they're not
		 * reachable through the group lists.
		 */
		क्रम_each_sibling_event(sibling, group_leader) अणु
			perf_event__state_init(sibling);
			perf_install_in_context(ctx, sibling, sibling->cpu);
			get_ctx(ctx);
		पूर्ण

		/*
		 * Removing from the context ends up with disabled
		 * event. What we want here is event in the initial
		 * startup state, पढ़ोy to be add पूर्णांकo new context.
		 */
		perf_event__state_init(group_leader);
		perf_install_in_context(ctx, group_leader, group_leader->cpu);
		get_ctx(ctx);
	पूर्ण

	/*
	 * Precalculate sample_data sizes; करो जबतक holding ctx::mutex such
	 * that we're serialized against further additions and beक्रमe
	 * perf_install_in_context() which is the poपूर्णांक the event is active and
	 * can use these values.
	 */
	perf_event__header_size(event);
	perf_event__id_header_size(event);

	event->owner = current;

	perf_install_in_context(ctx, event, event->cpu);
	perf_unpin_context(ctx);

	अगर (move_group)
		perf_event_ctx_unlock(group_leader, gctx);
	mutex_unlock(&ctx->mutex);

	अगर (task) अणु
		up_पढ़ो(&task->संकेत->exec_update_lock);
		put_task_काष्ठा(task);
	पूर्ण

	mutex_lock(&current->perf_event_mutex);
	list_add_tail(&event->owner_entry, &current->perf_event_list);
	mutex_unlock(&current->perf_event_mutex);

	/*
	 * Drop the reference on the group_event after placing the
	 * new event on the sibling_list. This ensures deकाष्ठाion
	 * of the group leader will find the poपूर्णांकer to itself in
	 * perf_group_detach().
	 */
	fdput(group);
	fd_install(event_fd, event_file);
	वापस event_fd;

err_locked:
	अगर (move_group)
		perf_event_ctx_unlock(group_leader, gctx);
	mutex_unlock(&ctx->mutex);
err_cred:
	अगर (task)
		up_पढ़ो(&task->संकेत->exec_update_lock);
err_file:
	fput(event_file);
err_context:
	perf_unpin_context(ctx);
	put_ctx(ctx);
err_alloc:
	/*
	 * If event_file is set, the fput() above will have called ->release()
	 * and that will take care of मुक्तing the event.
	 */
	अगर (!event_file)
		मुक्त_event(event);
err_task:
	अगर (task)
		put_task_काष्ठा(task);
err_group_fd:
	fdput(group);
err_fd:
	put_unused_fd(event_fd);
	वापस err;
पूर्ण

/**
 * perf_event_create_kernel_counter
 *
 * @attr: attributes of the counter to create
 * @cpu: cpu in which the counter is bound
 * @task: task to profile (शून्य क्रम percpu)
 */
काष्ठा perf_event *
perf_event_create_kernel_counter(काष्ठा perf_event_attr *attr, पूर्णांक cpu,
				 काष्ठा task_काष्ठा *task,
				 perf_overflow_handler_t overflow_handler,
				 व्योम *context)
अणु
	काष्ठा perf_event_context *ctx;
	काष्ठा perf_event *event;
	पूर्णांक err;

	/*
	 * Grouping is not supported क्रम kernel events, neither is 'AUX',
	 * make sure the caller's पूर्णांकentions are adjusted.
	 */
	अगर (attr->aux_output)
		वापस ERR_PTR(-EINVAL);

	event = perf_event_alloc(attr, cpu, task, शून्य, शून्य,
				 overflow_handler, context, -1);
	अगर (IS_ERR(event)) अणु
		err = PTR_ERR(event);
		जाओ err;
	पूर्ण

	/* Mark owner so we could distinguish it from user events. */
	event->owner = TASK_TOMBSTONE;

	/*
	 * Get the target context (task or percpu):
	 */
	ctx = find_get_context(event->pmu, task, event);
	अगर (IS_ERR(ctx)) अणु
		err = PTR_ERR(ctx);
		जाओ err_मुक्त;
	पूर्ण

	WARN_ON_ONCE(ctx->parent_ctx);
	mutex_lock(&ctx->mutex);
	अगर (ctx->task == TASK_TOMBSTONE) अणु
		err = -ESRCH;
		जाओ err_unlock;
	पूर्ण

	अगर (!task) अणु
		/*
		 * Check अगर the @cpu we're creating an event क्रम is online.
		 *
		 * We use the perf_cpu_context::ctx::mutex to serialize against
		 * the hotplug notअगरiers. See perf_event_अणुinit,निकासपूर्ण_cpu().
		 */
		काष्ठा perf_cpu_context *cpuctx =
			container_of(ctx, काष्ठा perf_cpu_context, ctx);
		अगर (!cpuctx->online) अणु
			err = -ENODEV;
			जाओ err_unlock;
		पूर्ण
	पूर्ण

	अगर (!exclusive_event_installable(event, ctx)) अणु
		err = -EBUSY;
		जाओ err_unlock;
	पूर्ण

	perf_install_in_context(ctx, event, event->cpu);
	perf_unpin_context(ctx);
	mutex_unlock(&ctx->mutex);

	वापस event;

err_unlock:
	mutex_unlock(&ctx->mutex);
	perf_unpin_context(ctx);
	put_ctx(ctx);
err_मुक्त:
	मुक्त_event(event);
err:
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(perf_event_create_kernel_counter);

व्योम perf_pmu_migrate_context(काष्ठा pmu *pmu, पूर्णांक src_cpu, पूर्णांक dst_cpu)
अणु
	काष्ठा perf_event_context *src_ctx;
	काष्ठा perf_event_context *dst_ctx;
	काष्ठा perf_event *event, *पंचांगp;
	LIST_HEAD(events);

	src_ctx = &per_cpu_ptr(pmu->pmu_cpu_context, src_cpu)->ctx;
	dst_ctx = &per_cpu_ptr(pmu->pmu_cpu_context, dst_cpu)->ctx;

	/*
	 * See perf_event_ctx_lock() क्रम comments on the details
	 * of swizzling perf_event::ctx.
	 */
	mutex_lock_द्विगुन(&src_ctx->mutex, &dst_ctx->mutex);
	list_क्रम_each_entry_safe(event, पंचांगp, &src_ctx->event_list,
				 event_entry) अणु
		perf_हटाओ_from_context(event, 0);
		unaccount_event_cpu(event, src_cpu);
		put_ctx(src_ctx);
		list_add(&event->migrate_entry, &events);
	पूर्ण

	/*
	 * Wait क्रम the events to quiesce beक्रमe re-instating them.
	 */
	synchronize_rcu();

	/*
	 * Re-instate events in 2 passes.
	 *
	 * Skip over group leaders and only install siblings on this first
	 * pass, siblings will not get enabled without a leader, however a
	 * leader will enable its siblings, even अगर those are still on the old
	 * context.
	 */
	list_क्रम_each_entry_safe(event, पंचांगp, &events, migrate_entry) अणु
		अगर (event->group_leader == event)
			जारी;

		list_del(&event->migrate_entry);
		अगर (event->state >= PERF_EVENT_STATE_OFF)
			event->state = PERF_EVENT_STATE_INACTIVE;
		account_event_cpu(event, dst_cpu);
		perf_install_in_context(dst_ctx, event, dst_cpu);
		get_ctx(dst_ctx);
	पूर्ण

	/*
	 * Once all the siblings are setup properly, install the group leaders
	 * to make it go.
	 */
	list_क्रम_each_entry_safe(event, पंचांगp, &events, migrate_entry) अणु
		list_del(&event->migrate_entry);
		अगर (event->state >= PERF_EVENT_STATE_OFF)
			event->state = PERF_EVENT_STATE_INACTIVE;
		account_event_cpu(event, dst_cpu);
		perf_install_in_context(dst_ctx, event, dst_cpu);
		get_ctx(dst_ctx);
	पूर्ण
	mutex_unlock(&dst_ctx->mutex);
	mutex_unlock(&src_ctx->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(perf_pmu_migrate_context);

अटल व्योम sync_child_event(काष्ठा perf_event *child_event)
अणु
	काष्ठा perf_event *parent_event = child_event->parent;
	u64 child_val;

	अगर (child_event->attr.inherit_stat) अणु
		काष्ठा task_काष्ठा *task = child_event->ctx->task;

		अगर (task && task != TASK_TOMBSTONE)
			perf_event_पढ़ो_event(child_event, task);
	पूर्ण

	child_val = perf_event_count(child_event);

	/*
	 * Add back the child's count to the parent's count:
	 */
	atomic64_add(child_val, &parent_event->child_count);
	atomic64_add(child_event->total_समय_enabled,
		     &parent_event->child_total_समय_enabled);
	atomic64_add(child_event->total_समय_running,
		     &parent_event->child_total_समय_running);
पूर्ण

अटल व्योम
perf_event_निकास_event(काष्ठा perf_event *event, काष्ठा perf_event_context *ctx)
अणु
	काष्ठा perf_event *parent_event = event->parent;
	अचिन्हित दीर्घ detach_flags = 0;

	अगर (parent_event) अणु
		/*
		 * Do not destroy the 'original' grouping; because of the
		 * context चयन optimization the original events could've
		 * ended up in a अक्रमom child task.
		 *
		 * If we were to destroy the original group, all group related
		 * operations would cease to function properly after this
		 * अक्रमom child dies.
		 *
		 * Do destroy all inherited groups, we करोn't care about those
		 * and being thorough is better.
		 */
		detach_flags = DETACH_GROUP | DETACH_CHILD;
		mutex_lock(&parent_event->child_mutex);
	पूर्ण

	perf_हटाओ_from_context(event, detach_flags);

	raw_spin_lock_irq(&ctx->lock);
	अगर (event->state > PERF_EVENT_STATE_EXIT)
		perf_event_set_state(event, PERF_EVENT_STATE_EXIT);
	raw_spin_unlock_irq(&ctx->lock);

	/*
	 * Child events can be मुक्तd.
	 */
	अगर (parent_event) अणु
		mutex_unlock(&parent_event->child_mutex);
		/*
		 * Kick perf_poll() क्रम is_event_hup();
		 */
		perf_event_wakeup(parent_event);
		मुक्त_event(event);
		put_event(parent_event);
		वापस;
	पूर्ण

	/*
	 * Parent events are governed by their filedesc, retain them.
	 */
	perf_event_wakeup(event);
पूर्ण

अटल व्योम perf_event_निकास_task_context(काष्ठा task_काष्ठा *child, पूर्णांक ctxn)
अणु
	काष्ठा perf_event_context *child_ctx, *clone_ctx = शून्य;
	काष्ठा perf_event *child_event, *next;

	WARN_ON_ONCE(child != current);

	child_ctx = perf_pin_task_context(child, ctxn);
	अगर (!child_ctx)
		वापस;

	/*
	 * In order to reduce the amount of tricky in ctx tear-करोwn, we hold
	 * ctx::mutex over the entire thing. This serializes against almost
	 * everything that wants to access the ctx.
	 *
	 * The exception is sys_perf_event_खोलो() /
	 * perf_event_create_kernel_count() which करोes find_get_context()
	 * without ctx::mutex (it cannot because of the move_group द्विगुन mutex
	 * lock thing). See the comments in perf_install_in_context().
	 */
	mutex_lock(&child_ctx->mutex);

	/*
	 * In a single ctx::lock section, de-schedule the events and detach the
	 * context from the task such that we cannot ever get it scheduled back
	 * in.
	 */
	raw_spin_lock_irq(&child_ctx->lock);
	task_ctx_sched_out(__get_cpu_context(child_ctx), child_ctx, EVENT_ALL);

	/*
	 * Now that the context is inactive, destroy the task <-> ctx relation
	 * and mark the context dead.
	 */
	RCU_INIT_POINTER(child->perf_event_ctxp[ctxn], शून्य);
	put_ctx(child_ctx); /* cannot be last */
	WRITE_ONCE(child_ctx->task, TASK_TOMBSTONE);
	put_task_काष्ठा(current); /* cannot be last */

	clone_ctx = unclone_ctx(child_ctx);
	raw_spin_unlock_irq(&child_ctx->lock);

	अगर (clone_ctx)
		put_ctx(clone_ctx);

	/*
	 * Report the task dead after unscheduling the events so that we
	 * won't get any samples after PERF_RECORD_EXIT. We can however still
	 * get a few PERF_RECORD_READ events.
	 */
	perf_event_task(child, child_ctx, 0);

	list_क्रम_each_entry_safe(child_event, next, &child_ctx->event_list, event_entry)
		perf_event_निकास_event(child_event, child_ctx);

	mutex_unlock(&child_ctx->mutex);

	put_ctx(child_ctx);
पूर्ण

/*
 * When a child task निकासs, feed back event values to parent events.
 *
 * Can be called with exec_update_lock held when called from
 * setup_new_exec().
 */
व्योम perf_event_निकास_task(काष्ठा task_काष्ठा *child)
अणु
	काष्ठा perf_event *event, *पंचांगp;
	पूर्णांक ctxn;

	mutex_lock(&child->perf_event_mutex);
	list_क्रम_each_entry_safe(event, पंचांगp, &child->perf_event_list,
				 owner_entry) अणु
		list_del_init(&event->owner_entry);

		/*
		 * Ensure the list deletion is visible beक्रमe we clear
		 * the owner, बंदs a race against perf_release() where
		 * we need to serialize on the owner->perf_event_mutex.
		 */
		smp_store_release(&event->owner, शून्य);
	पूर्ण
	mutex_unlock(&child->perf_event_mutex);

	क्रम_each_task_context_nr(ctxn)
		perf_event_निकास_task_context(child, ctxn);

	/*
	 * The perf_event_निकास_task_context calls perf_event_task
	 * with child's task_ctx, which generates EXIT events क्रम
	 * child contexts and sets child->perf_event_ctxp[] to शून्य.
	 * At this poपूर्णांक we need to send EXIT events to cpu contexts.
	 */
	perf_event_task(child, शून्य, 0);
पूर्ण

अटल व्योम perf_मुक्त_event(काष्ठा perf_event *event,
			    काष्ठा perf_event_context *ctx)
अणु
	काष्ठा perf_event *parent = event->parent;

	अगर (WARN_ON_ONCE(!parent))
		वापस;

	mutex_lock(&parent->child_mutex);
	list_del_init(&event->child_list);
	mutex_unlock(&parent->child_mutex);

	put_event(parent);

	raw_spin_lock_irq(&ctx->lock);
	perf_group_detach(event);
	list_del_event(event, ctx);
	raw_spin_unlock_irq(&ctx->lock);
	मुक्त_event(event);
पूर्ण

/*
 * Free a context as created by inheritance by perf_event_init_task() below,
 * used by विभाजन() in हाल of fail.
 *
 * Even though the task has never lived, the context and events have been
 * exposed through the child_list, so we must take care tearing it all करोwn.
 */
व्योम perf_event_मुक्त_task(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा perf_event_context *ctx;
	काष्ठा perf_event *event, *पंचांगp;
	पूर्णांक ctxn;

	क्रम_each_task_context_nr(ctxn) अणु
		ctx = task->perf_event_ctxp[ctxn];
		अगर (!ctx)
			जारी;

		mutex_lock(&ctx->mutex);
		raw_spin_lock_irq(&ctx->lock);
		/*
		 * Destroy the task <-> ctx relation and mark the context dead.
		 *
		 * This is important because even though the task hasn't been
		 * exposed yet the context has been (through child_list).
		 */
		RCU_INIT_POINTER(task->perf_event_ctxp[ctxn], शून्य);
		WRITE_ONCE(ctx->task, TASK_TOMBSTONE);
		put_task_काष्ठा(task); /* cannot be last */
		raw_spin_unlock_irq(&ctx->lock);

		list_क्रम_each_entry_safe(event, पंचांगp, &ctx->event_list, event_entry)
			perf_मुक्त_event(event, ctx);

		mutex_unlock(&ctx->mutex);

		/*
		 * perf_event_release_kernel() could've stolen some of our
		 * child events and still have them on its मुक्त_list. In that
		 * हाल we must रुको क्रम these events to have been मुक्तd (in
		 * particular all their references to this task must've been
		 * dropped).
		 *
		 * Without this copy_process() will unconditionally मुक्त this
		 * task (irrespective of its reference count) and
		 * _मुक्त_event()'s put_task_काष्ठा(event->hw.target) will be a
		 * use-after-मुक्त.
		 *
		 * Wait क्रम all events to drop their context reference.
		 */
		रुको_var_event(&ctx->refcount, refcount_पढ़ो(&ctx->refcount) == 1);
		put_ctx(ctx); /* must be last */
	पूर्ण
पूर्ण

व्योम perf_event_delayed_put(काष्ठा task_काष्ठा *task)
अणु
	पूर्णांक ctxn;

	क्रम_each_task_context_nr(ctxn)
		WARN_ON_ONCE(task->perf_event_ctxp[ctxn]);
पूर्ण

काष्ठा file *perf_event_get(अचिन्हित पूर्णांक fd)
अणु
	काष्ठा file *file = fget(fd);
	अगर (!file)
		वापस ERR_PTR(-EBADF);

	अगर (file->f_op != &perf_fops) अणु
		fput(file);
		वापस ERR_PTR(-EBADF);
	पूर्ण

	वापस file;
पूर्ण

स्थिर काष्ठा perf_event *perf_get_event(काष्ठा file *file)
अणु
	अगर (file->f_op != &perf_fops)
		वापस ERR_PTR(-EINVAL);

	वापस file->निजी_data;
पूर्ण

स्थिर काष्ठा perf_event_attr *perf_event_attrs(काष्ठा perf_event *event)
अणु
	अगर (!event)
		वापस ERR_PTR(-EINVAL);

	वापस &event->attr;
पूर्ण

/*
 * Inherit an event from parent task to child task.
 *
 * Returns:
 *  - valid poपूर्णांकer on success
 *  - शून्य क्रम orphaned events
 *  - IS_ERR() on error
 */
अटल काष्ठा perf_event *
inherit_event(काष्ठा perf_event *parent_event,
	      काष्ठा task_काष्ठा *parent,
	      काष्ठा perf_event_context *parent_ctx,
	      काष्ठा task_काष्ठा *child,
	      काष्ठा perf_event *group_leader,
	      काष्ठा perf_event_context *child_ctx)
अणु
	क्रमागत perf_event_state parent_state = parent_event->state;
	काष्ठा perf_event *child_event;
	अचिन्हित दीर्घ flags;

	/*
	 * Instead of creating recursive hierarchies of events,
	 * we link inherited events back to the original parent,
	 * which has a filp क्रम sure, which we use as the reference
	 * count:
	 */
	अगर (parent_event->parent)
		parent_event = parent_event->parent;

	child_event = perf_event_alloc(&parent_event->attr,
					   parent_event->cpu,
					   child,
					   group_leader, parent_event,
					   शून्य, शून्य, -1);
	अगर (IS_ERR(child_event))
		वापस child_event;


	अगर ((child_event->attach_state & PERF_ATTACH_TASK_DATA) &&
	    !child_ctx->task_ctx_data) अणु
		काष्ठा pmu *pmu = child_event->pmu;

		child_ctx->task_ctx_data = alloc_task_ctx_data(pmu);
		अगर (!child_ctx->task_ctx_data) अणु
			मुक्त_event(child_event);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
	पूर्ण

	/*
	 * is_orphaned_event() and list_add_tail(&parent_event->child_list)
	 * must be under the same lock in order to serialize against
	 * perf_event_release_kernel(), such that either we must observe
	 * is_orphaned_event() or they will observe us on the child_list.
	 */
	mutex_lock(&parent_event->child_mutex);
	अगर (is_orphaned_event(parent_event) ||
	    !atomic_दीर्घ_inc_not_zero(&parent_event->refcount)) अणु
		mutex_unlock(&parent_event->child_mutex);
		/* task_ctx_data is मुक्तd with child_ctx */
		मुक्त_event(child_event);
		वापस शून्य;
	पूर्ण

	get_ctx(child_ctx);

	/*
	 * Make the child state follow the state of the parent event,
	 * not its attr.disabled bit.  We hold the parent's mutex,
	 * so we won't race with perf_event_अणुen, disपूर्णable_family.
	 */
	अगर (parent_state >= PERF_EVENT_STATE_INACTIVE)
		child_event->state = PERF_EVENT_STATE_INACTIVE;
	अन्यथा
		child_event->state = PERF_EVENT_STATE_OFF;

	अगर (parent_event->attr.freq) अणु
		u64 sample_period = parent_event->hw.sample_period;
		काष्ठा hw_perf_event *hwc = &child_event->hw;

		hwc->sample_period = sample_period;
		hwc->last_period   = sample_period;

		local64_set(&hwc->period_left, sample_period);
	पूर्ण

	child_event->ctx = child_ctx;
	child_event->overflow_handler = parent_event->overflow_handler;
	child_event->overflow_handler_context
		= parent_event->overflow_handler_context;

	/*
	 * Precalculate sample_data sizes
	 */
	perf_event__header_size(child_event);
	perf_event__id_header_size(child_event);

	/*
	 * Link it up in the child's context:
	 */
	raw_spin_lock_irqsave(&child_ctx->lock, flags);
	add_event_to_ctx(child_event, child_ctx);
	child_event->attach_state |= PERF_ATTACH_CHILD;
	raw_spin_unlock_irqrestore(&child_ctx->lock, flags);

	/*
	 * Link this पूर्णांकo the parent event's child list
	 */
	list_add_tail(&child_event->child_list, &parent_event->child_list);
	mutex_unlock(&parent_event->child_mutex);

	वापस child_event;
पूर्ण

/*
 * Inherits an event group.
 *
 * This will quietly suppress orphaned events; !inherit_event() is not an error.
 * This matches with perf_event_release_kernel() removing all child events.
 *
 * Returns:
 *  - 0 on success
 *  - <0 on error
 */
अटल पूर्णांक inherit_group(काष्ठा perf_event *parent_event,
	      काष्ठा task_काष्ठा *parent,
	      काष्ठा perf_event_context *parent_ctx,
	      काष्ठा task_काष्ठा *child,
	      काष्ठा perf_event_context *child_ctx)
अणु
	काष्ठा perf_event *leader;
	काष्ठा perf_event *sub;
	काष्ठा perf_event *child_ctr;

	leader = inherit_event(parent_event, parent, parent_ctx,
				 child, शून्य, child_ctx);
	अगर (IS_ERR(leader))
		वापस PTR_ERR(leader);
	/*
	 * @leader can be शून्य here because of is_orphaned_event(). In this
	 * हाल inherit_event() will create inभागidual events, similar to what
	 * perf_group_detach() would करो anyway.
	 */
	क्रम_each_sibling_event(sub, parent_event) अणु
		child_ctr = inherit_event(sub, parent, parent_ctx,
					    child, leader, child_ctx);
		अगर (IS_ERR(child_ctr))
			वापस PTR_ERR(child_ctr);

		अगर (sub->aux_event == parent_event && child_ctr &&
		    !perf_get_aux_event(child_ctr, leader))
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Creates the child task context and tries to inherit the event-group.
 *
 * Clears @inherited_all on !attr.inherited or error. Note that we'll leave
 * inherited_all set when we 'fail' to inherit an orphaned event; this is
 * consistent with perf_event_release_kernel() removing all child events.
 *
 * Returns:
 *  - 0 on success
 *  - <0 on error
 */
अटल पूर्णांक
inherit_task_group(काष्ठा perf_event *event, काष्ठा task_काष्ठा *parent,
		   काष्ठा perf_event_context *parent_ctx,
		   काष्ठा task_काष्ठा *child, पूर्णांक ctxn,
		   u64 clone_flags, पूर्णांक *inherited_all)
अणु
	पूर्णांक ret;
	काष्ठा perf_event_context *child_ctx;

	अगर (!event->attr.inherit ||
	    (event->attr.inherit_thपढ़ो && !(clone_flags & CLONE_THREAD)) ||
	    /* Do not inherit अगर sigtrap and संकेत handlers were cleared. */
	    (event->attr.sigtrap && (clone_flags & CLONE_CLEAR_SIGHAND))) अणु
		*inherited_all = 0;
		वापस 0;
	पूर्ण

	child_ctx = child->perf_event_ctxp[ctxn];
	अगर (!child_ctx) अणु
		/*
		 * This is executed from the parent task context, so
		 * inherit events that have been marked क्रम cloning.
		 * First allocate and initialize a context क्रम the
		 * child.
		 */
		child_ctx = alloc_perf_context(parent_ctx->pmu, child);
		अगर (!child_ctx)
			वापस -ENOMEM;

		child->perf_event_ctxp[ctxn] = child_ctx;
	पूर्ण

	ret = inherit_group(event, parent, parent_ctx,
			    child, child_ctx);

	अगर (ret)
		*inherited_all = 0;

	वापस ret;
पूर्ण

/*
 * Initialize the perf_event context in task_काष्ठा
 */
अटल पूर्णांक perf_event_init_context(काष्ठा task_काष्ठा *child, पूर्णांक ctxn,
				   u64 clone_flags)
अणु
	काष्ठा perf_event_context *child_ctx, *parent_ctx;
	काष्ठा perf_event_context *cloned_ctx;
	काष्ठा perf_event *event;
	काष्ठा task_काष्ठा *parent = current;
	पूर्णांक inherited_all = 1;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (likely(!parent->perf_event_ctxp[ctxn]))
		वापस 0;

	/*
	 * If the parent's context is a clone, pin it so it won't get
	 * swapped under us.
	 */
	parent_ctx = perf_pin_task_context(parent, ctxn);
	अगर (!parent_ctx)
		वापस 0;

	/*
	 * No need to check अगर parent_ctx != शून्य here; since we saw
	 * it non-शून्य earlier, the only reason क्रम it to become शून्य
	 * is अगर we निकास, and since we're currently in the middle of
	 * a विभाजन we can't be निकासing at the same समय.
	 */

	/*
	 * Lock the parent list. No need to lock the child - not PID
	 * hashed yet and not running, so nobody can access it.
	 */
	mutex_lock(&parent_ctx->mutex);

	/*
	 * We करोnt have to disable NMIs - we are only looking at
	 * the list, not manipulating it:
	 */
	perf_event_groups_क्रम_each(event, &parent_ctx->pinned_groups) अणु
		ret = inherit_task_group(event, parent, parent_ctx,
					 child, ctxn, clone_flags,
					 &inherited_all);
		अगर (ret)
			जाओ out_unlock;
	पूर्ण

	/*
	 * We can't hold ctx->lock when iterating the ->flexible_group list due
	 * to allocations, but we need to prevent rotation because
	 * rotate_ctx() will change the list from पूर्णांकerrupt context.
	 */
	raw_spin_lock_irqsave(&parent_ctx->lock, flags);
	parent_ctx->rotate_disable = 1;
	raw_spin_unlock_irqrestore(&parent_ctx->lock, flags);

	perf_event_groups_क्रम_each(event, &parent_ctx->flexible_groups) अणु
		ret = inherit_task_group(event, parent, parent_ctx,
					 child, ctxn, clone_flags,
					 &inherited_all);
		अगर (ret)
			जाओ out_unlock;
	पूर्ण

	raw_spin_lock_irqsave(&parent_ctx->lock, flags);
	parent_ctx->rotate_disable = 0;

	child_ctx = child->perf_event_ctxp[ctxn];

	अगर (child_ctx && inherited_all) अणु
		/*
		 * Mark the child context as a clone of the parent
		 * context, or of whatever the parent is a clone of.
		 *
		 * Note that अगर the parent is a clone, the holding of
		 * parent_ctx->lock aव्योमs it from being uncloned.
		 */
		cloned_ctx = parent_ctx->parent_ctx;
		अगर (cloned_ctx) अणु
			child_ctx->parent_ctx = cloned_ctx;
			child_ctx->parent_gen = parent_ctx->parent_gen;
		पूर्ण अन्यथा अणु
			child_ctx->parent_ctx = parent_ctx;
			child_ctx->parent_gen = parent_ctx->generation;
		पूर्ण
		get_ctx(child_ctx->parent_ctx);
	पूर्ण

	raw_spin_unlock_irqrestore(&parent_ctx->lock, flags);
out_unlock:
	mutex_unlock(&parent_ctx->mutex);

	perf_unpin_context(parent_ctx);
	put_ctx(parent_ctx);

	वापस ret;
पूर्ण

/*
 * Initialize the perf_event context in task_काष्ठा
 */
पूर्णांक perf_event_init_task(काष्ठा task_काष्ठा *child, u64 clone_flags)
अणु
	पूर्णांक ctxn, ret;

	स_रखो(child->perf_event_ctxp, 0, माप(child->perf_event_ctxp));
	mutex_init(&child->perf_event_mutex);
	INIT_LIST_HEAD(&child->perf_event_list);

	क्रम_each_task_context_nr(ctxn) अणु
		ret = perf_event_init_context(child, ctxn, clone_flags);
		अगर (ret) अणु
			perf_event_मुक्त_task(child);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __init perf_event_init_all_cpus(व्योम)
अणु
	काष्ठा swevent_htable *swhash;
	पूर्णांक cpu;

	zalloc_cpumask_var(&perf_online_mask, GFP_KERNEL);

	क्रम_each_possible_cpu(cpu) अणु
		swhash = &per_cpu(swevent_htable, cpu);
		mutex_init(&swhash->hlist_mutex);
		INIT_LIST_HEAD(&per_cpu(active_ctx_list, cpu));

		INIT_LIST_HEAD(&per_cpu(pmu_sb_events.list, cpu));
		raw_spin_lock_init(&per_cpu(pmu_sb_events.lock, cpu));

#अगर_घोषित CONFIG_CGROUP_PERF
		INIT_LIST_HEAD(&per_cpu(cgrp_cpuctx_list, cpu));
#पूर्ण_अगर
		INIT_LIST_HEAD(&per_cpu(sched_cb_list, cpu));
	पूर्ण
पूर्ण

अटल व्योम perf_swevent_init_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा swevent_htable *swhash = &per_cpu(swevent_htable, cpu);

	mutex_lock(&swhash->hlist_mutex);
	अगर (swhash->hlist_refcount > 0 && !swevent_hlist_deref(swhash)) अणु
		काष्ठा swevent_hlist *hlist;

		hlist = kzalloc_node(माप(*hlist), GFP_KERNEL, cpu_to_node(cpu));
		WARN_ON(!hlist);
		rcu_assign_poपूर्णांकer(swhash->swevent_hlist, hlist);
	पूर्ण
	mutex_unlock(&swhash->hlist_mutex);
पूर्ण

#अगर defined CONFIG_HOTPLUG_CPU || defined CONFIG_KEXEC_CORE
अटल व्योम __perf_event_निकास_context(व्योम *__info)
अणु
	काष्ठा perf_event_context *ctx = __info;
	काष्ठा perf_cpu_context *cpuctx = __get_cpu_context(ctx);
	काष्ठा perf_event *event;

	raw_spin_lock(&ctx->lock);
	ctx_sched_out(ctx, cpuctx, EVENT_TIME);
	list_क्रम_each_entry(event, &ctx->event_list, event_entry)
		__perf_हटाओ_from_context(event, cpuctx, ctx, (व्योम *)DETACH_GROUP);
	raw_spin_unlock(&ctx->lock);
पूर्ण

अटल व्योम perf_event_निकास_cpu_context(पूर्णांक cpu)
अणु
	काष्ठा perf_cpu_context *cpuctx;
	काष्ठा perf_event_context *ctx;
	काष्ठा pmu *pmu;

	mutex_lock(&pmus_lock);
	list_क्रम_each_entry(pmu, &pmus, entry) अणु
		cpuctx = per_cpu_ptr(pmu->pmu_cpu_context, cpu);
		ctx = &cpuctx->ctx;

		mutex_lock(&ctx->mutex);
		smp_call_function_single(cpu, __perf_event_निकास_context, ctx, 1);
		cpuctx->online = 0;
		mutex_unlock(&ctx->mutex);
	पूर्ण
	cpumask_clear_cpu(cpu, perf_online_mask);
	mutex_unlock(&pmus_lock);
पूर्ण
#अन्यथा

अटल व्योम perf_event_निकास_cpu_context(पूर्णांक cpu) अणु पूर्ण

#पूर्ण_अगर

पूर्णांक perf_event_init_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा perf_cpu_context *cpuctx;
	काष्ठा perf_event_context *ctx;
	काष्ठा pmu *pmu;

	perf_swevent_init_cpu(cpu);

	mutex_lock(&pmus_lock);
	cpumask_set_cpu(cpu, perf_online_mask);
	list_क्रम_each_entry(pmu, &pmus, entry) अणु
		cpuctx = per_cpu_ptr(pmu->pmu_cpu_context, cpu);
		ctx = &cpuctx->ctx;

		mutex_lock(&ctx->mutex);
		cpuctx->online = 1;
		mutex_unlock(&ctx->mutex);
	पूर्ण
	mutex_unlock(&pmus_lock);

	वापस 0;
पूर्ण

पूर्णांक perf_event_निकास_cpu(अचिन्हित पूर्णांक cpu)
अणु
	perf_event_निकास_cpu_context(cpu);
	वापस 0;
पूर्ण

अटल पूर्णांक
perf_reboot(काष्ठा notअगरier_block *notअगरier, अचिन्हित दीर्घ val, व्योम *v)
अणु
	पूर्णांक cpu;

	क्रम_each_online_cpu(cpu)
		perf_event_निकास_cpu(cpu);

	वापस NOTIFY_OK;
पूर्ण

/*
 * Run the perf reboot notअगरier at the very last possible moment so that
 * the generic watchकरोg code runs as दीर्घ as possible.
 */
अटल काष्ठा notअगरier_block perf_reboot_notअगरier = अणु
	.notअगरier_call = perf_reboot,
	.priority = पूर्णांक_न्यून,
पूर्ण;

व्योम __init perf_event_init(व्योम)
अणु
	पूर्णांक ret;

	idr_init(&pmu_idr);

	perf_event_init_all_cpus();
	init_srcu_काष्ठा(&pmus_srcu);
	perf_pmu_रेजिस्टर(&perf_swevent, "software", PERF_TYPE_SOFTWARE);
	perf_pmu_रेजिस्टर(&perf_cpu_घड़ी, शून्य, -1);
	perf_pmu_रेजिस्टर(&perf_task_घड़ी, शून्य, -1);
	perf_tp_रेजिस्टर();
	perf_event_init_cpu(smp_processor_id());
	रेजिस्टर_reboot_notअगरier(&perf_reboot_notअगरier);

	ret = init_hw_अवरोधpoपूर्णांक();
	WARN(ret, "hw_breakpoint initialization failed with: %d", ret);

	perf_event_cache = KMEM_CACHE(perf_event, SLAB_PANIC);

	/*
	 * Build समय निश्चितion that we keep the data_head at the पूर्णांकended
	 * location.  IOW, validation we got the __reserved[] size right.
	 */
	BUILD_BUG_ON((दुरत्व(काष्ठा perf_event_mmap_page, data_head))
		     != 1024);
पूर्ण

sमाप_प्रकार perf_event_sysfs_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *page)
अणु
	काष्ठा perf_pmu_events_attr *pmu_attr =
		container_of(attr, काष्ठा perf_pmu_events_attr, attr);

	अगर (pmu_attr->event_str)
		वापस प्र_लिखो(page, "%s\n", pmu_attr->event_str);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(perf_event_sysfs_show);

अटल पूर्णांक __init perf_event_sysfs_init(व्योम)
अणु
	काष्ठा pmu *pmu;
	पूर्णांक ret;

	mutex_lock(&pmus_lock);

	ret = bus_रेजिस्टर(&pmu_bus);
	अगर (ret)
		जाओ unlock;

	list_क्रम_each_entry(pmu, &pmus, entry) अणु
		अगर (!pmu->name || pmu->type < 0)
			जारी;

		ret = pmu_dev_alloc(pmu);
		WARN(ret, "Failed to register pmu: %s, reason %d\n", pmu->name, ret);
	पूर्ण
	pmu_bus_running = 1;
	ret = 0;

unlock:
	mutex_unlock(&pmus_lock);

	वापस ret;
पूर्ण
device_initcall(perf_event_sysfs_init);

#अगर_घोषित CONFIG_CGROUP_PERF
अटल काष्ठा cgroup_subsys_state *
perf_cgroup_css_alloc(काष्ठा cgroup_subsys_state *parent_css)
अणु
	काष्ठा perf_cgroup *jc;

	jc = kzalloc(माप(*jc), GFP_KERNEL);
	अगर (!jc)
		वापस ERR_PTR(-ENOMEM);

	jc->info = alloc_percpu(काष्ठा perf_cgroup_info);
	अगर (!jc->info) अणु
		kमुक्त(jc);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस &jc->css;
पूर्ण

अटल व्योम perf_cgroup_css_मुक्त(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा perf_cgroup *jc = container_of(css, काष्ठा perf_cgroup, css);

	मुक्त_percpu(jc->info);
	kमुक्त(jc);
पूर्ण

अटल पूर्णांक perf_cgroup_css_online(काष्ठा cgroup_subsys_state *css)
अणु
	perf_event_cgroup(css->cgroup);
	वापस 0;
पूर्ण

अटल पूर्णांक __perf_cgroup_move(व्योम *info)
अणु
	काष्ठा task_काष्ठा *task = info;
	rcu_पढ़ो_lock();
	perf_cgroup_चयन(task, PERF_CGROUP_SWOUT | PERF_CGROUP_SWIN);
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

अटल व्योम perf_cgroup_attach(काष्ठा cgroup_taskset *tset)
अणु
	काष्ठा task_काष्ठा *task;
	काष्ठा cgroup_subsys_state *css;

	cgroup_taskset_क्रम_each(task, css, tset)
		task_function_call(task, __perf_cgroup_move, task);
पूर्ण

काष्ठा cgroup_subsys perf_event_cgrp_subsys = अणु
	.css_alloc	= perf_cgroup_css_alloc,
	.css_मुक्त	= perf_cgroup_css_मुक्त,
	.css_online	= perf_cgroup_css_online,
	.attach		= perf_cgroup_attach,
	/*
	 * Implicitly enable on dfl hierarchy so that perf events can
	 * always be filtered by cgroup2 path as दीर्घ as perf_event
	 * controller is not mounted on a legacy hierarchy.
	 */
	.implicit_on_dfl = true,
	.thपढ़ोed	= true,
पूर्ण;
#पूर्ण_अगर /* CONFIG_CGROUP_PERF */
