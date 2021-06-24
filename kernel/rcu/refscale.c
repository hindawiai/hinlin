<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Scalability test comparing RCU vs other mechanisms
// क्रम acquiring references on objects.
//
// Copyright (C) Google, 2020.
//
// Author: Joel Fernandes <joel@joelfernandes.org>

#घोषणा pr_fmt(fmt) fmt

#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/completion.h>
#समावेश <linux/cpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/percpu.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/rcupdate_trace.h>
#समावेश <linux/reboot.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/smp.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/srcu.h>
#समावेश <linux/slab.h>
#समावेश <linux/torture.h>
#समावेश <linux/types.h>

#समावेश "rcu.h"

#घोषणा SCALE_FLAG "-ref-scale: "

#घोषणा SCALEOUT(s, x...) \
	pr_alert("%s" SCALE_FLAG s, scale_type, ## x)

#घोषणा VERBOSE_SCALEOUT(s, x...) \
	करो अणु अगर (verbose) pr_alert("%s" SCALE_FLAG s, scale_type, ## x); पूर्ण जबतक (0)

अटल atomic_t verbose_batch_ctr;

#घोषणा VERBOSE_SCALEOUT_BATCH(s, x...)							\
करो अणु											\
	अगर (verbose &&									\
	    (verbose_batched <= 0 ||							\
	     !(atomic_inc_वापस(&verbose_batch_ctr) % verbose_batched))) अणु		\
		schedule_समयout_unपूर्णांकerruptible(1);					\
		pr_alert("%s" SCALE_FLAG s, scale_type, ## x);				\
	पूर्ण										\
पूर्ण जबतक (0)

#घोषणा VERBOSE_SCALEOUT_ERRSTRING(s, x...) \
	करो अणु अगर (verbose) pr_alert("%s" SCALE_FLAG "!!! " s, scale_type, ## x); पूर्ण जबतक (0)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Joel Fernandes (Google) <joel@joelfernandes.org>");

अटल अक्षर *scale_type = "rcu";
module_param(scale_type, अक्षरp, 0444);
MODULE_PARM_DESC(scale_type, "Type of test (rcu, srcu, refcnt, rwsem, rwlock.");

torture_param(पूर्णांक, verbose, 0, "Enable verbose debugging printk()s");
torture_param(पूर्णांक, verbose_batched, 0, "Batch verbose debugging printk()s");

// Wait until there are multiple CPUs beक्रमe starting test.
torture_param(पूर्णांक, holकरोff, IS_BUILTIN(CONFIG_RCU_REF_SCALE_TEST) ? 10 : 0,
	      "Holdoff time before test start (s)");
// Number of loops per experiment, all पढ़ोers execute operations concurrently.
torture_param(दीर्घ, loops, 10000, "Number of loops per experiment.");
// Number of पढ़ोers, with -1 शेषing to about 75% of the CPUs.
torture_param(पूर्णांक, nपढ़ोers, -1, "Number of readers, -1 for 75% of CPUs.");
// Number of runs.
torture_param(पूर्णांक, nruns, 30, "Number of experiments to run.");
// Reader delay in nanoseconds, 0 क्रम no delay.
torture_param(पूर्णांक, पढ़ोdelay, 0, "Read-side delay in nanoseconds.");

#अगर_घोषित MODULE
# define REFSCALE_SHUTDOWN 0
#अन्यथा
# define REFSCALE_SHUTDOWN 1
#पूर्ण_अगर

torture_param(bool, shutकरोwn, REFSCALE_SHUTDOWN,
	      "Shutdown at end of scalability tests.");

काष्ठा पढ़ोer_task अणु
	काष्ठा task_काष्ठा *task;
	पूर्णांक start_पढ़ोer;
	रुको_queue_head_t wq;
	u64 last_duration_ns;
पूर्ण;

अटल काष्ठा task_काष्ठा *shutकरोwn_task;
अटल रुको_queue_head_t shutकरोwn_wq;

अटल काष्ठा task_काष्ठा *मुख्य_task;
अटल रुको_queue_head_t मुख्य_wq;
अटल पूर्णांक shutकरोwn_start;

अटल काष्ठा पढ़ोer_task *पढ़ोer_tasks;

// Number of पढ़ोers that are part of the current experiment.
अटल atomic_t nपढ़ोers_exp;

// Use to रुको क्रम all thपढ़ोs to start.
अटल atomic_t n_init;
अटल atomic_t n_started;
अटल atomic_t n_warmedup;
अटल atomic_t n_cooledकरोwn;

// Track which experiment is currently running.
अटल पूर्णांक exp_idx;

// Operations vector क्रम selecting dअगरferent types of tests.
काष्ठा ref_scale_ops अणु
	व्योम (*init)(व्योम);
	व्योम (*cleanup)(व्योम);
	व्योम (*पढ़ोsection)(स्थिर पूर्णांक nloops);
	व्योम (*delaysection)(स्थिर पूर्णांक nloops, स्थिर पूर्णांक udl, स्थिर पूर्णांक ndl);
	स्थिर अक्षर *name;
पूर्ण;

अटल काष्ठा ref_scale_ops *cur_ops;

अटल व्योम un_delay(स्थिर पूर्णांक udl, स्थिर पूर्णांक ndl)
अणु
	अगर (udl)
		udelay(udl);
	अगर (ndl)
		ndelay(ndl);
पूर्ण

अटल व्योम ref_rcu_पढ़ो_section(स्थिर पूर्णांक nloops)
अणु
	पूर्णांक i;

	क्रम (i = nloops; i >= 0; i--) अणु
		rcu_पढ़ो_lock();
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

अटल व्योम ref_rcu_delay_section(स्थिर पूर्णांक nloops, स्थिर पूर्णांक udl, स्थिर पूर्णांक ndl)
अणु
	पूर्णांक i;

	क्रम (i = nloops; i >= 0; i--) अणु
		rcu_पढ़ो_lock();
		un_delay(udl, ndl);
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

अटल व्योम rcu_sync_scale_init(व्योम)
अणु
पूर्ण

अटल काष्ठा ref_scale_ops rcu_ops = अणु
	.init		= rcu_sync_scale_init,
	.पढ़ोsection	= ref_rcu_पढ़ो_section,
	.delaysection	= ref_rcu_delay_section,
	.name		= "rcu"
पूर्ण;

// Definitions क्रम SRCU ref scale testing.
DEFINE_STATIC_SRCU(srcu_refctl_scale);
अटल काष्ठा srcu_काष्ठा *srcu_ctlp = &srcu_refctl_scale;

अटल व्योम srcu_ref_scale_पढ़ो_section(स्थिर पूर्णांक nloops)
अणु
	पूर्णांक i;
	पूर्णांक idx;

	क्रम (i = nloops; i >= 0; i--) अणु
		idx = srcu_पढ़ो_lock(srcu_ctlp);
		srcu_पढ़ो_unlock(srcu_ctlp, idx);
	पूर्ण
पूर्ण

अटल व्योम srcu_ref_scale_delay_section(स्थिर पूर्णांक nloops, स्थिर पूर्णांक udl, स्थिर पूर्णांक ndl)
अणु
	पूर्णांक i;
	पूर्णांक idx;

	क्रम (i = nloops; i >= 0; i--) अणु
		idx = srcu_पढ़ो_lock(srcu_ctlp);
		un_delay(udl, ndl);
		srcu_पढ़ो_unlock(srcu_ctlp, idx);
	पूर्ण
पूर्ण

अटल काष्ठा ref_scale_ops srcu_ops = अणु
	.init		= rcu_sync_scale_init,
	.पढ़ोsection	= srcu_ref_scale_पढ़ो_section,
	.delaysection	= srcu_ref_scale_delay_section,
	.name		= "srcu"
पूर्ण;

// Definitions क्रम RCU Tasks ref scale testing: Empty पढ़ो markers.
// These definitions also work क्रम RCU Rude पढ़ोers.
अटल व्योम rcu_tasks_ref_scale_पढ़ो_section(स्थिर पूर्णांक nloops)
अणु
	पूर्णांक i;

	क्रम (i = nloops; i >= 0; i--)
		जारी;
पूर्ण

अटल व्योम rcu_tasks_ref_scale_delay_section(स्थिर पूर्णांक nloops, स्थिर पूर्णांक udl, स्थिर पूर्णांक ndl)
अणु
	पूर्णांक i;

	क्रम (i = nloops; i >= 0; i--)
		un_delay(udl, ndl);
पूर्ण

अटल काष्ठा ref_scale_ops rcu_tasks_ops = अणु
	.init		= rcu_sync_scale_init,
	.पढ़ोsection	= rcu_tasks_ref_scale_पढ़ो_section,
	.delaysection	= rcu_tasks_ref_scale_delay_section,
	.name		= "rcu-tasks"
पूर्ण;

// Definitions क्रम RCU Tasks Trace ref scale testing.
अटल व्योम rcu_trace_ref_scale_पढ़ो_section(स्थिर पूर्णांक nloops)
अणु
	पूर्णांक i;

	क्रम (i = nloops; i >= 0; i--) अणु
		rcu_पढ़ो_lock_trace();
		rcu_पढ़ो_unlock_trace();
	पूर्ण
पूर्ण

अटल व्योम rcu_trace_ref_scale_delay_section(स्थिर पूर्णांक nloops, स्थिर पूर्णांक udl, स्थिर पूर्णांक ndl)
अणु
	पूर्णांक i;

	क्रम (i = nloops; i >= 0; i--) अणु
		rcu_पढ़ो_lock_trace();
		un_delay(udl, ndl);
		rcu_पढ़ो_unlock_trace();
	पूर्ण
पूर्ण

अटल काष्ठा ref_scale_ops rcu_trace_ops = अणु
	.init		= rcu_sync_scale_init,
	.पढ़ोsection	= rcu_trace_ref_scale_पढ़ो_section,
	.delaysection	= rcu_trace_ref_scale_delay_section,
	.name		= "rcu-trace"
पूर्ण;

// Definitions क्रम reference count
अटल atomic_t refcnt;

अटल व्योम ref_refcnt_section(स्थिर पूर्णांक nloops)
अणु
	पूर्णांक i;

	क्रम (i = nloops; i >= 0; i--) अणु
		atomic_inc(&refcnt);
		atomic_dec(&refcnt);
	पूर्ण
पूर्ण

अटल व्योम ref_refcnt_delay_section(स्थिर पूर्णांक nloops, स्थिर पूर्णांक udl, स्थिर पूर्णांक ndl)
अणु
	पूर्णांक i;

	क्रम (i = nloops; i >= 0; i--) अणु
		atomic_inc(&refcnt);
		un_delay(udl, ndl);
		atomic_dec(&refcnt);
	पूर्ण
पूर्ण

अटल काष्ठा ref_scale_ops refcnt_ops = अणु
	.init		= rcu_sync_scale_init,
	.पढ़ोsection	= ref_refcnt_section,
	.delaysection	= ref_refcnt_delay_section,
	.name		= "refcnt"
पूर्ण;

// Definitions क्रम rwlock
अटल rwlock_t test_rwlock;

अटल व्योम ref_rwlock_init(व्योम)
अणु
	rwlock_init(&test_rwlock);
पूर्ण

अटल व्योम ref_rwlock_section(स्थिर पूर्णांक nloops)
अणु
	पूर्णांक i;

	क्रम (i = nloops; i >= 0; i--) अणु
		पढ़ो_lock(&test_rwlock);
		पढ़ो_unlock(&test_rwlock);
	पूर्ण
पूर्ण

अटल व्योम ref_rwlock_delay_section(स्थिर पूर्णांक nloops, स्थिर पूर्णांक udl, स्थिर पूर्णांक ndl)
अणु
	पूर्णांक i;

	क्रम (i = nloops; i >= 0; i--) अणु
		पढ़ो_lock(&test_rwlock);
		un_delay(udl, ndl);
		पढ़ो_unlock(&test_rwlock);
	पूर्ण
पूर्ण

अटल काष्ठा ref_scale_ops rwlock_ops = अणु
	.init		= ref_rwlock_init,
	.पढ़ोsection	= ref_rwlock_section,
	.delaysection	= ref_rwlock_delay_section,
	.name		= "rwlock"
पूर्ण;

// Definitions क्रम rwsem
अटल काष्ठा rw_semaphore test_rwsem;

अटल व्योम ref_rwsem_init(व्योम)
अणु
	init_rwsem(&test_rwsem);
पूर्ण

अटल व्योम ref_rwsem_section(स्थिर पूर्णांक nloops)
अणु
	पूर्णांक i;

	क्रम (i = nloops; i >= 0; i--) अणु
		करोwn_पढ़ो(&test_rwsem);
		up_पढ़ो(&test_rwsem);
	पूर्ण
पूर्ण

अटल व्योम ref_rwsem_delay_section(स्थिर पूर्णांक nloops, स्थिर पूर्णांक udl, स्थिर पूर्णांक ndl)
अणु
	पूर्णांक i;

	क्रम (i = nloops; i >= 0; i--) अणु
		करोwn_पढ़ो(&test_rwsem);
		un_delay(udl, ndl);
		up_पढ़ो(&test_rwsem);
	पूर्ण
पूर्ण

अटल काष्ठा ref_scale_ops rwsem_ops = अणु
	.init		= ref_rwsem_init,
	.पढ़ोsection	= ref_rwsem_section,
	.delaysection	= ref_rwsem_delay_section,
	.name		= "rwsem"
पूर्ण;

अटल व्योम rcu_scale_one_पढ़ोer(व्योम)
अणु
	अगर (पढ़ोdelay <= 0)
		cur_ops->पढ़ोsection(loops);
	अन्यथा
		cur_ops->delaysection(loops, पढ़ोdelay / 1000, पढ़ोdelay % 1000);
पूर्ण

// Reader kthपढ़ो.  Repeatedly करोes empty RCU पढ़ो-side
// critical section, minimizing update-side पूर्णांकerference.
अटल पूर्णांक
ref_scale_पढ़ोer(व्योम *arg)
अणु
	अचिन्हित दीर्घ flags;
	दीर्घ me = (दीर्घ)arg;
	काष्ठा पढ़ोer_task *rt = &(पढ़ोer_tasks[me]);
	u64 start;
	s64 duration;

	VERBOSE_SCALEOUT_BATCH("ref_scale_reader %ld: task started", me);
	set_cpus_allowed_ptr(current, cpumask_of(me % nr_cpu_ids));
	set_user_nice(current, MAX_NICE);
	atomic_inc(&n_init);
	अगर (holकरोff)
		schedule_समयout_पूर्णांकerruptible(holकरोff * HZ);
repeat:
	VERBOSE_SCALEOUT_BATCH("ref_scale_reader %ld: waiting to start next experiment on cpu %d", me, smp_processor_id());

	// Wait क्रम संकेत that this पढ़ोer can start.
	रुको_event(rt->wq, (atomic_पढ़ो(&nपढ़ोers_exp) && smp_load_acquire(&rt->start_पढ़ोer)) ||
			   torture_must_stop());

	अगर (torture_must_stop())
		जाओ end;

	// Make sure that the CPU is affinitized appropriately during testing.
	WARN_ON_ONCE(smp_processor_id() != me);

	WRITE_ONCE(rt->start_पढ़ोer, 0);
	अगर (!atomic_dec_वापस(&n_started))
		जबतक (atomic_पढ़ो_acquire(&n_started))
			cpu_relax();

	VERBOSE_SCALEOUT_BATCH("ref_scale_reader %ld: experiment %d started", me, exp_idx);


	// To reduce noise, करो an initial cache-warming invocation, check
	// in, and then keep warming until everyone has checked in.
	rcu_scale_one_पढ़ोer();
	अगर (!atomic_dec_वापस(&n_warmedup))
		जबतक (atomic_पढ़ो_acquire(&n_warmedup))
			rcu_scale_one_पढ़ोer();
	// Also keep पूर्णांकerrupts disabled.  This also has the effect
	// of preventing entries पूर्णांकo slow path क्रम rcu_पढ़ो_unlock().
	local_irq_save(flags);
	start = kसमय_get_mono_fast_ns();

	rcu_scale_one_पढ़ोer();

	duration = kसमय_get_mono_fast_ns() - start;
	local_irq_restore(flags);

	rt->last_duration_ns = WARN_ON_ONCE(duration < 0) ? 0 : duration;
	// To reduce runसमय-skew noise, करो मुख्यtain-load invocations until
	// everyone is करोne.
	अगर (!atomic_dec_वापस(&n_cooledकरोwn))
		जबतक (atomic_पढ़ो_acquire(&n_cooledकरोwn))
			rcu_scale_one_पढ़ोer();

	अगर (atomic_dec_and_test(&nपढ़ोers_exp))
		wake_up(&मुख्य_wq);

	VERBOSE_SCALEOUT_BATCH("ref_scale_reader %ld: experiment %d ended, (readers remaining=%d)",
				me, exp_idx, atomic_पढ़ो(&nपढ़ोers_exp));

	अगर (!torture_must_stop())
		जाओ repeat;
end:
	torture_kthपढ़ो_stopping("ref_scale_reader");
	वापस 0;
पूर्ण

अटल व्योम reset_पढ़ोers(व्योम)
अणु
	पूर्णांक i;
	काष्ठा पढ़ोer_task *rt;

	क्रम (i = 0; i < nपढ़ोers; i++) अणु
		rt = &(पढ़ोer_tasks[i]);

		rt->last_duration_ns = 0;
	पूर्ण
पूर्ण

// Prपूर्णांक the results of each पढ़ोer and वापस the sum of all their durations.
अटल u64 process_durations(पूर्णांक n)
अणु
	पूर्णांक i;
	काष्ठा पढ़ोer_task *rt;
	अक्षर buf1[64];
	अक्षर *buf;
	u64 sum = 0;

	buf = kदो_स्मृति(128 + nपढ़ोers * 32, GFP_KERNEL);
	अगर (!buf)
		वापस 0;
	buf[0] = 0;
	प्र_लिखो(buf, "Experiment #%d (Format: <THREAD-NUM>:<Total loop time in ns>)",
		exp_idx);

	क्रम (i = 0; i < n && !torture_must_stop(); i++) अणु
		rt = &(पढ़ोer_tasks[i]);
		प्र_लिखो(buf1, "%d: %llu\t", i, rt->last_duration_ns);

		अगर (i % 5 == 0)
			म_जोड़ो(buf, "\n");
		म_जोड़ो(buf, buf1);

		sum += rt->last_duration_ns;
	पूर्ण
	म_जोड़ो(buf, "\n");

	SCALEOUT("%s\n", buf);

	kमुक्त(buf);
	वापस sum;
पूर्ण

// The मुख्य_func is the मुख्य orchestrator, it perक्रमms a bunch of
// experiments.  For every experiment, it orders all the पढ़ोers
// involved to start and रुकोs क्रम them to finish the experiment. It
// then पढ़ोs their बारtamps and starts the next experiment. Each
// experiment progresses from 1 concurrent पढ़ोer to N of them at which
// poपूर्णांक all the बारtamps are prपूर्णांकed.
अटल पूर्णांक मुख्य_func(व्योम *arg)
अणु
	bool errनिकास = false;
	पूर्णांक exp, r;
	अक्षर buf1[64];
	अक्षर *buf;
	u64 *result_avg;

	set_cpus_allowed_ptr(current, cpumask_of(nपढ़ोers % nr_cpu_ids));
	set_user_nice(current, MAX_NICE);

	VERBOSE_SCALEOUT("main_func task started");
	result_avg = kzalloc(nruns * माप(*result_avg), GFP_KERNEL);
	buf = kzalloc(64 + nruns * 32, GFP_KERNEL);
	अगर (!result_avg || !buf) अणु
		VERBOSE_SCALEOUT_ERRSTRING("out of memory");
		errनिकास = true;
	पूर्ण
	अगर (holकरोff)
		schedule_समयout_पूर्णांकerruptible(holकरोff * HZ);

	// Wait क्रम all thपढ़ोs to start.
	atomic_inc(&n_init);
	जबतक (atomic_पढ़ो(&n_init) < nपढ़ोers + 1)
		schedule_समयout_unपूर्णांकerruptible(1);

	// Start exp पढ़ोers up per experiment
	क्रम (exp = 0; exp < nruns && !torture_must_stop(); exp++) अणु
		अगर (errनिकास)
			अवरोध;
		अगर (torture_must_stop())
			जाओ end;

		reset_पढ़ोers();
		atomic_set(&nपढ़ोers_exp, nपढ़ोers);
		atomic_set(&n_started, nपढ़ोers);
		atomic_set(&n_warmedup, nपढ़ोers);
		atomic_set(&n_cooledकरोwn, nपढ़ोers);

		exp_idx = exp;

		क्रम (r = 0; r < nपढ़ोers; r++) अणु
			smp_store_release(&पढ़ोer_tasks[r].start_पढ़ोer, 1);
			wake_up(&पढ़ोer_tasks[r].wq);
		पूर्ण

		VERBOSE_SCALEOUT("main_func: experiment started, waiting for %d readers",
				nपढ़ोers);

		रुको_event(मुख्य_wq,
			   !atomic_पढ़ो(&nपढ़ोers_exp) || torture_must_stop());

		VERBOSE_SCALEOUT("main_func: experiment ended");

		अगर (torture_must_stop())
			जाओ end;

		result_avg[exp] = भाग_u64(1000 * process_durations(nपढ़ोers), nपढ़ोers * loops);
	पूर्ण

	// Prपूर्णांक the average of all experiments
	SCALEOUT("END OF TEST. Calculating average duration per loop (nanoseconds)...\n");

	अगर (!errनिकास) अणु
		buf[0] = 0;
		म_जोड़ो(buf, "\n");
		म_जोड़ो(buf, "Runs\tTime(ns)\n");
	पूर्ण

	क्रम (exp = 0; exp < nruns; exp++) अणु
		u64 avg;
		u32 rem;

		अगर (errनिकास)
			अवरोध;
		avg = भाग_u64_rem(result_avg[exp], 1000, &rem);
		प्र_लिखो(buf1, "%d\t%llu.%03u\n", exp + 1, avg, rem);
		म_जोड़ो(buf, buf1);
	पूर्ण

	अगर (!errनिकास)
		SCALEOUT("%s", buf);

	// This will shutकरोwn everything including us.
	अगर (shutकरोwn) अणु
		shutकरोwn_start = 1;
		wake_up(&shutकरोwn_wq);
	पूर्ण

	// Wait क्रम torture to stop us
	जबतक (!torture_must_stop())
		schedule_समयout_unपूर्णांकerruptible(1);

end:
	torture_kthपढ़ो_stopping("main_func");
	kमुक्त(result_avg);
	kमुक्त(buf);
	वापस 0;
पूर्ण

अटल व्योम
ref_scale_prपूर्णांक_module_parms(काष्ठा ref_scale_ops *cur_ops, स्थिर अक्षर *tag)
अणु
	pr_alert("%s" SCALE_FLAG
		 "--- %s:  verbose=%d shutdown=%d holdoff=%d loops=%ld nreaders=%d nruns=%d readdelay=%d\n", scale_type, tag,
		 verbose, shutकरोwn, holकरोff, loops, nपढ़ोers, nruns, पढ़ोdelay);
पूर्ण

अटल व्योम
ref_scale_cleanup(व्योम)
अणु
	पूर्णांक i;

	अगर (torture_cleanup_begin())
		वापस;

	अगर (!cur_ops) अणु
		torture_cleanup_end();
		वापस;
	पूर्ण

	अगर (पढ़ोer_tasks) अणु
		क्रम (i = 0; i < nपढ़ोers; i++)
			torture_stop_kthपढ़ो("ref_scale_reader",
					     पढ़ोer_tasks[i].task);
	पूर्ण
	kमुक्त(पढ़ोer_tasks);

	torture_stop_kthपढ़ो("main_task", मुख्य_task);
	kमुक्त(मुख्य_task);

	// Do scale-type-specअगरic cleanup operations.
	अगर (cur_ops->cleanup != शून्य)
		cur_ops->cleanup();

	torture_cleanup_end();
पूर्ण

// Shutकरोwn kthपढ़ो.  Just रुकोs to be awakened, then shuts करोwn प्रणाली.
अटल पूर्णांक
ref_scale_shutकरोwn(व्योम *arg)
अणु
	रुको_event(shutकरोwn_wq, shutकरोwn_start);

	smp_mb(); // Wake beक्रमe output.
	ref_scale_cleanup();
	kernel_घातer_off();

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __init
ref_scale_init(व्योम)
अणु
	दीर्घ i;
	पूर्णांक firsterr = 0;
	अटल काष्ठा ref_scale_ops *scale_ops[] = अणु
		&rcu_ops, &srcu_ops, &rcu_trace_ops, &rcu_tasks_ops,
		&refcnt_ops, &rwlock_ops, &rwsem_ops,
	पूर्ण;

	अगर (!torture_init_begin(scale_type, verbose))
		वापस -EBUSY;

	क्रम (i = 0; i < ARRAY_SIZE(scale_ops); i++) अणु
		cur_ops = scale_ops[i];
		अगर (म_भेद(scale_type, cur_ops->name) == 0)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(scale_ops)) अणु
		pr_alert("rcu-scale: invalid scale type: \"%s\"\n", scale_type);
		pr_alert("rcu-scale types:");
		क्रम (i = 0; i < ARRAY_SIZE(scale_ops); i++)
			pr_cont(" %s", scale_ops[i]->name);
		pr_cont("\n");
		firsterr = -EINVAL;
		cur_ops = शून्य;
		जाओ unwind;
	पूर्ण
	अगर (cur_ops->init)
		cur_ops->init();

	ref_scale_prपूर्णांक_module_parms(cur_ops, "Start of test");

	// Shutकरोwn task
	अगर (shutकरोwn) अणु
		init_रुकोqueue_head(&shutकरोwn_wq);
		firsterr = torture_create_kthपढ़ो(ref_scale_shutकरोwn, शून्य,
						  shutकरोwn_task);
		अगर (firsterr)
			जाओ unwind;
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण

	// Reader tasks (शेष to ~75% of online CPUs).
	अगर (nपढ़ोers < 0)
		nपढ़ोers = (num_online_cpus() >> 1) + (num_online_cpus() >> 2);
	अगर (WARN_ONCE(loops <= 0, "%s: loops = %ld, adjusted to 1\n", __func__, loops))
		loops = 1;
	अगर (WARN_ONCE(nपढ़ोers <= 0, "%s: nreaders = %d, adjusted to 1\n", __func__, nपढ़ोers))
		nपढ़ोers = 1;
	अगर (WARN_ONCE(nruns <= 0, "%s: nruns = %d, adjusted to 1\n", __func__, nruns))
		nruns = 1;
	पढ़ोer_tasks = kसुस्मृति(nपढ़ोers, माप(पढ़ोer_tasks[0]),
			       GFP_KERNEL);
	अगर (!पढ़ोer_tasks) अणु
		VERBOSE_SCALEOUT_ERRSTRING("out of memory");
		firsterr = -ENOMEM;
		जाओ unwind;
	पूर्ण

	VERBOSE_SCALEOUT("Starting %d reader threads\n", nपढ़ोers);

	क्रम (i = 0; i < nपढ़ोers; i++) अणु
		firsterr = torture_create_kthपढ़ो(ref_scale_पढ़ोer, (व्योम *)i,
						  पढ़ोer_tasks[i].task);
		अगर (firsterr)
			जाओ unwind;

		init_रुकोqueue_head(&(पढ़ोer_tasks[i].wq));
	पूर्ण

	// Main Task
	init_रुकोqueue_head(&मुख्य_wq);
	firsterr = torture_create_kthपढ़ो(मुख्य_func, शून्य, मुख्य_task);
	अगर (firsterr)
		जाओ unwind;

	torture_init_end();
	वापस 0;

unwind:
	torture_init_end();
	ref_scale_cleanup();
	अगर (shutकरोwn) अणु
		WARN_ON(!IS_MODULE(CONFIG_RCU_REF_SCALE_TEST));
		kernel_घातer_off();
	पूर्ण
	वापस firsterr;
पूर्ण

module_init(ref_scale_init);
module_निकास(ref_scale_cleanup);
