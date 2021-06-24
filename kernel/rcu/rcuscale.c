<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Read-Copy Update module-based scalability-test facility
 *
 * Copyright (C) IBM Corporation, 2015
 *
 * Authors: Paul E. McKenney <paulmck@linux.ibm.com>
 */

#घोषणा pr_fmt(fmt) fmt

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/err.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/smp.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <uapi/linux/sched/types.h>
#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/completion.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/percpu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/cpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/srcu.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/torture.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/rcupdate_trace.h>

#समावेश "rcu.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Paul E. McKenney <paulmck@linux.ibm.com>");

#घोषणा SCALE_FLAG "-scale:"
#घोषणा SCALEOUT_STRING(s) \
	pr_alert("%s" SCALE_FLAG " %s\n", scale_type, s)
#घोषणा VERBOSE_SCALEOUT_STRING(s) \
	करो अणु अगर (verbose) pr_alert("%s" SCALE_FLAG " %s\n", scale_type, s); पूर्ण जबतक (0)
#घोषणा VERBOSE_SCALEOUT_ERRSTRING(s) \
	करो अणु अगर (verbose) pr_alert("%s" SCALE_FLAG "!!! %s\n", scale_type, s); पूर्ण जबतक (0)

/*
 * The पूर्णांकended use हालs क्रम the nपढ़ोers and nग_लिखोrs module parameters
 * are as follows:
 *
 * 1.	Specअगरy only the nr_cpus kernel boot parameter.  This will
 *	set both nपढ़ोers and nग_लिखोrs to the value specअगरied by
 *	nr_cpus क्रम a mixed पढ़ोer/ग_लिखोr test.
 *
 * 2.	Specअगरy the nr_cpus kernel boot parameter, but set
 *	rcuscale.nपढ़ोers to zero.  This will set nग_लिखोrs to the
 *	value specअगरied by nr_cpus क्रम an update-only test.
 *
 * 3.	Specअगरy the nr_cpus kernel boot parameter, but set
 *	rcuscale.nग_लिखोrs to zero.  This will set nपढ़ोers to the
 *	value specअगरied by nr_cpus क्रम a पढ़ो-only test.
 *
 * Various other use हालs may of course be specअगरied.
 *
 * Note that this test's पढ़ोers are पूर्णांकended only as a test load क्रम
 * the ग_लिखोrs.  The पढ़ोer scalability statistics will be overly
 * pessimistic due to the per-critical-section पूर्णांकerrupt disabling,
 * test-end checks, and the pair of calls through poपूर्णांकers.
 */

#अगर_घोषित MODULE
# define RCUSCALE_SHUTDOWN 0
#अन्यथा
# define RCUSCALE_SHUTDOWN 1
#पूर्ण_अगर

torture_param(bool, gp_async, false, "Use asynchronous GP wait primitives");
torture_param(पूर्णांक, gp_async_max, 1000, "Max # outstanding waits per reader");
torture_param(bool, gp_exp, false, "Use expedited GP wait primitives");
torture_param(पूर्णांक, holकरोff, 10, "Holdoff time before test start (s)");
torture_param(पूर्णांक, nपढ़ोers, -1, "Number of RCU reader threads");
torture_param(पूर्णांक, nग_लिखोrs, -1, "Number of RCU updater threads");
torture_param(bool, shutकरोwn, RCUSCALE_SHUTDOWN,
	      "Shutdown at end of scalability tests.");
torture_param(पूर्णांक, verbose, 1, "Enable verbose debugging printk()s");
torture_param(पूर्णांक, ग_लिखोr_holकरोff, 0, "Holdoff (us) between GPs, zero to disable");
torture_param(पूर्णांक, kमुक्त_rcu_test, 0, "Do we run a kfree_rcu() scale test?");
torture_param(पूर्णांक, kमुक्त_mult, 1, "Multiple of kfree_obj size to allocate.");

अटल अक्षर *scale_type = "rcu";
module_param(scale_type, अक्षरp, 0444);
MODULE_PARM_DESC(scale_type, "Type of RCU to scalability-test (rcu, srcu, ...)");

अटल पूर्णांक nrealपढ़ोers;
अटल पूर्णांक nrealग_लिखोrs;
अटल काष्ठा task_काष्ठा **ग_लिखोr_tasks;
अटल काष्ठा task_काष्ठा **पढ़ोer_tasks;
अटल काष्ठा task_काष्ठा *shutकरोwn_task;

अटल u64 **ग_लिखोr_durations;
अटल पूर्णांक *ग_लिखोr_n_durations;
अटल atomic_t n_rcu_scale_पढ़ोer_started;
अटल atomic_t n_rcu_scale_ग_लिखोr_started;
अटल atomic_t n_rcu_scale_ग_लिखोr_finished;
अटल रुको_queue_head_t shutकरोwn_wq;
अटल u64 t_rcu_scale_ग_लिखोr_started;
अटल u64 t_rcu_scale_ग_लिखोr_finished;
अटल अचिन्हित दीर्घ b_rcu_gp_test_started;
अटल अचिन्हित दीर्घ b_rcu_gp_test_finished;
अटल DEFINE_PER_CPU(atomic_t, n_async_inflight);

#घोषणा MAX_MEAS 10000
#घोषणा MIN_MEAS 100

/*
 * Operations vector क्रम selecting dअगरferent types of tests.
 */

काष्ठा rcu_scale_ops अणु
	पूर्णांक ptype;
	व्योम (*init)(व्योम);
	व्योम (*cleanup)(व्योम);
	पूर्णांक (*पढ़ोlock)(व्योम);
	व्योम (*पढ़ोunlock)(पूर्णांक idx);
	अचिन्हित दीर्घ (*get_gp_seq)(व्योम);
	अचिन्हित दीर्घ (*gp_dअगरf)(अचिन्हित दीर्घ new, अचिन्हित दीर्घ old);
	अचिन्हित दीर्घ (*exp_completed)(व्योम);
	व्योम (*async)(काष्ठा rcu_head *head, rcu_callback_t func);
	व्योम (*gp_barrier)(व्योम);
	व्योम (*sync)(व्योम);
	व्योम (*exp_sync)(व्योम);
	स्थिर अक्षर *name;
पूर्ण;

अटल काष्ठा rcu_scale_ops *cur_ops;

/*
 * Definitions क्रम rcu scalability testing.
 */

अटल पूर्णांक rcu_scale_पढ़ो_lock(व्योम) __acquires(RCU)
अणु
	rcu_पढ़ो_lock();
	वापस 0;
पूर्ण

अटल व्योम rcu_scale_पढ़ो_unlock(पूर्णांक idx) __releases(RCU)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल अचिन्हित दीर्घ __maybe_unused rcu_no_completed(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम rcu_sync_scale_init(व्योम)
अणु
पूर्ण

अटल काष्ठा rcu_scale_ops rcu_ops = अणु
	.ptype		= RCU_FLAVOR,
	.init		= rcu_sync_scale_init,
	.पढ़ोlock	= rcu_scale_पढ़ो_lock,
	.पढ़ोunlock	= rcu_scale_पढ़ो_unlock,
	.get_gp_seq	= rcu_get_gp_seq,
	.gp_dअगरf	= rcu_seq_dअगरf,
	.exp_completed	= rcu_exp_batches_completed,
	.async		= call_rcu,
	.gp_barrier	= rcu_barrier,
	.sync		= synchronize_rcu,
	.exp_sync	= synchronize_rcu_expedited,
	.name		= "rcu"
पूर्ण;

/*
 * Definitions क्रम srcu scalability testing.
 */

DEFINE_STATIC_SRCU(srcu_ctl_scale);
अटल काष्ठा srcu_काष्ठा *srcu_ctlp = &srcu_ctl_scale;

अटल पूर्णांक srcu_scale_पढ़ो_lock(व्योम) __acquires(srcu_ctlp)
अणु
	वापस srcu_पढ़ो_lock(srcu_ctlp);
पूर्ण

अटल व्योम srcu_scale_पढ़ो_unlock(पूर्णांक idx) __releases(srcu_ctlp)
अणु
	srcu_पढ़ो_unlock(srcu_ctlp, idx);
पूर्ण

अटल अचिन्हित दीर्घ srcu_scale_completed(व्योम)
अणु
	वापस srcu_batches_completed(srcu_ctlp);
पूर्ण

अटल व्योम srcu_call_rcu(काष्ठा rcu_head *head, rcu_callback_t func)
अणु
	call_srcu(srcu_ctlp, head, func);
पूर्ण

अटल व्योम srcu_rcu_barrier(व्योम)
अणु
	srcu_barrier(srcu_ctlp);
पूर्ण

अटल व्योम srcu_scale_synchronize(व्योम)
अणु
	synchronize_srcu(srcu_ctlp);
पूर्ण

अटल व्योम srcu_scale_synchronize_expedited(व्योम)
अणु
	synchronize_srcu_expedited(srcu_ctlp);
पूर्ण

अटल काष्ठा rcu_scale_ops srcu_ops = अणु
	.ptype		= SRCU_FLAVOR,
	.init		= rcu_sync_scale_init,
	.पढ़ोlock	= srcu_scale_पढ़ो_lock,
	.पढ़ोunlock	= srcu_scale_पढ़ो_unlock,
	.get_gp_seq	= srcu_scale_completed,
	.gp_dअगरf	= rcu_seq_dअगरf,
	.exp_completed	= srcu_scale_completed,
	.async		= srcu_call_rcu,
	.gp_barrier	= srcu_rcu_barrier,
	.sync		= srcu_scale_synchronize,
	.exp_sync	= srcu_scale_synchronize_expedited,
	.name		= "srcu"
पूर्ण;

अटल काष्ठा srcu_काष्ठा srcud;

अटल व्योम srcu_sync_scale_init(व्योम)
अणु
	srcu_ctlp = &srcud;
	init_srcu_काष्ठा(srcu_ctlp);
पूर्ण

अटल व्योम srcu_sync_scale_cleanup(व्योम)
अणु
	cleanup_srcu_काष्ठा(srcu_ctlp);
पूर्ण

अटल काष्ठा rcu_scale_ops srcud_ops = अणु
	.ptype		= SRCU_FLAVOR,
	.init		= srcu_sync_scale_init,
	.cleanup	= srcu_sync_scale_cleanup,
	.पढ़ोlock	= srcu_scale_पढ़ो_lock,
	.पढ़ोunlock	= srcu_scale_पढ़ो_unlock,
	.get_gp_seq	= srcu_scale_completed,
	.gp_dअगरf	= rcu_seq_dअगरf,
	.exp_completed	= srcu_scale_completed,
	.async		= srcu_call_rcu,
	.gp_barrier	= srcu_rcu_barrier,
	.sync		= srcu_scale_synchronize,
	.exp_sync	= srcu_scale_synchronize_expedited,
	.name		= "srcud"
पूर्ण;

/*
 * Definitions क्रम RCU-tasks scalability testing.
 */

अटल पूर्णांक tasks_scale_पढ़ो_lock(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम tasks_scale_पढ़ो_unlock(पूर्णांक idx)
अणु
पूर्ण

अटल काष्ठा rcu_scale_ops tasks_ops = अणु
	.ptype		= RCU_TASKS_FLAVOR,
	.init		= rcu_sync_scale_init,
	.पढ़ोlock	= tasks_scale_पढ़ो_lock,
	.पढ़ोunlock	= tasks_scale_पढ़ो_unlock,
	.get_gp_seq	= rcu_no_completed,
	.gp_dअगरf	= rcu_seq_dअगरf,
	.async		= call_rcu_tasks,
	.gp_barrier	= rcu_barrier_tasks,
	.sync		= synchronize_rcu_tasks,
	.exp_sync	= synchronize_rcu_tasks,
	.name		= "tasks"
पूर्ण;

/*
 * Definitions क्रम RCU-tasks-trace scalability testing.
 */

अटल पूर्णांक tasks_trace_scale_पढ़ो_lock(व्योम)
अणु
	rcu_पढ़ो_lock_trace();
	वापस 0;
पूर्ण

अटल व्योम tasks_trace_scale_पढ़ो_unlock(पूर्णांक idx)
अणु
	rcu_पढ़ो_unlock_trace();
पूर्ण

अटल काष्ठा rcu_scale_ops tasks_tracing_ops = अणु
	.ptype		= RCU_TASKS_FLAVOR,
	.init		= rcu_sync_scale_init,
	.पढ़ोlock	= tasks_trace_scale_पढ़ो_lock,
	.पढ़ोunlock	= tasks_trace_scale_पढ़ो_unlock,
	.get_gp_seq	= rcu_no_completed,
	.gp_dअगरf	= rcu_seq_dअगरf,
	.async		= call_rcu_tasks_trace,
	.gp_barrier	= rcu_barrier_tasks_trace,
	.sync		= synchronize_rcu_tasks_trace,
	.exp_sync	= synchronize_rcu_tasks_trace,
	.name		= "tasks-tracing"
पूर्ण;

अटल अचिन्हित दीर्घ rcuscale_seq_dअगरf(अचिन्हित दीर्घ new, अचिन्हित दीर्घ old)
अणु
	अगर (!cur_ops->gp_dअगरf)
		वापस new - old;
	वापस cur_ops->gp_dअगरf(new, old);
पूर्ण

/*
 * If scalability tests complete, रुको क्रम shutकरोwn to commence.
 */
अटल व्योम rcu_scale_रुको_shutकरोwn(व्योम)
अणु
	cond_resched_tasks_rcu_qs();
	अगर (atomic_पढ़ो(&n_rcu_scale_ग_लिखोr_finished) < nrealग_लिखोrs)
		वापस;
	जबतक (!torture_must_stop())
		schedule_समयout_unपूर्णांकerruptible(1);
पूर्ण

/*
 * RCU scalability पढ़ोer kthपढ़ो.  Repeatedly करोes empty RCU पढ़ो-side
 * critical section, minimizing update-side पूर्णांकerference.  However, the
 * poपूर्णांक of this test is not to evaluate पढ़ोer scalability, but instead
 * to serve as a test load क्रम update-side scalability testing.
 */
अटल पूर्णांक
rcu_scale_पढ़ोer(व्योम *arg)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक idx;
	दीर्घ me = (दीर्घ)arg;

	VERBOSE_SCALEOUT_STRING("rcu_scale_reader task started");
	set_cpus_allowed_ptr(current, cpumask_of(me % nr_cpu_ids));
	set_user_nice(current, MAX_NICE);
	atomic_inc(&n_rcu_scale_पढ़ोer_started);

	करो अणु
		local_irq_save(flags);
		idx = cur_ops->पढ़ोlock();
		cur_ops->पढ़ोunlock(idx);
		local_irq_restore(flags);
		rcu_scale_रुको_shutकरोwn();
	पूर्ण जबतक (!torture_must_stop());
	torture_kthपढ़ो_stopping("rcu_scale_reader");
	वापस 0;
पूर्ण

/*
 * Callback function क्रम asynchronous grace periods from rcu_scale_ग_लिखोr().
 */
अटल व्योम rcu_scale_async_cb(काष्ठा rcu_head *rhp)
अणु
	atomic_dec(this_cpu_ptr(&n_async_inflight));
	kमुक्त(rhp);
पूर्ण

/*
 * RCU scale ग_लिखोr kthपढ़ो.  Repeatedly करोes a grace period.
 */
अटल पूर्णांक
rcu_scale_ग_लिखोr(व्योम *arg)
अणु
	पूर्णांक i = 0;
	पूर्णांक i_max;
	दीर्घ me = (दीर्घ)arg;
	काष्ठा rcu_head *rhp = शून्य;
	bool started = false, करोne = false, allकरोne = false;
	u64 t;
	u64 *wdp;
	u64 *wdpp = ग_लिखोr_durations[me];

	VERBOSE_SCALEOUT_STRING("rcu_scale_writer task started");
	WARN_ON(!wdpp);
	set_cpus_allowed_ptr(current, cpumask_of(me % nr_cpu_ids));
	sched_set_fअगरo_low(current);

	अगर (holकरोff)
		schedule_समयout_unपूर्णांकerruptible(holकरोff * HZ);

	/*
	 * Wait until rcu_end_inkernel_boot() is called क्रम normal GP tests
	 * so that RCU is not always expedited क्रम normal GP tests.
	 * The प्रणाली_state test is approximate, but works well in practice.
	 */
	जबतक (!gp_exp && प्रणाली_state != SYSTEM_RUNNING)
		schedule_समयout_unपूर्णांकerruptible(1);

	t = kसमय_get_mono_fast_ns();
	अगर (atomic_inc_वापस(&n_rcu_scale_ग_लिखोr_started) >= nrealग_लिखोrs) अणु
		t_rcu_scale_ग_लिखोr_started = t;
		अगर (gp_exp) अणु
			b_rcu_gp_test_started =
				cur_ops->exp_completed() / 2;
		पूर्ण अन्यथा अणु
			b_rcu_gp_test_started = cur_ops->get_gp_seq();
		पूर्ण
	पूर्ण

	करो अणु
		अगर (ग_लिखोr_holकरोff)
			udelay(ग_लिखोr_holकरोff);
		wdp = &wdpp[i];
		*wdp = kसमय_get_mono_fast_ns();
		अगर (gp_async) अणु
retry:
			अगर (!rhp)
				rhp = kदो_स्मृति(माप(*rhp), GFP_KERNEL);
			अगर (rhp && atomic_पढ़ो(this_cpu_ptr(&n_async_inflight)) < gp_async_max) अणु
				atomic_inc(this_cpu_ptr(&n_async_inflight));
				cur_ops->async(rhp, rcu_scale_async_cb);
				rhp = शून्य;
			पूर्ण अन्यथा अगर (!kthपढ़ो_should_stop()) अणु
				cur_ops->gp_barrier();
				जाओ retry;
			पूर्ण अन्यथा अणु
				kमुक्त(rhp); /* Because we are stopping. */
			पूर्ण
		पूर्ण अन्यथा अगर (gp_exp) अणु
			cur_ops->exp_sync();
		पूर्ण अन्यथा अणु
			cur_ops->sync();
		पूर्ण
		t = kसमय_get_mono_fast_ns();
		*wdp = t - *wdp;
		i_max = i;
		अगर (!started &&
		    atomic_पढ़ो(&n_rcu_scale_ग_लिखोr_started) >= nrealग_लिखोrs)
			started = true;
		अगर (!करोne && i >= MIN_MEAS) अणु
			करोne = true;
			sched_set_normal(current, 0);
			pr_alert("%s%s rcu_scale_writer %ld has %d measurements\n",
				 scale_type, SCALE_FLAG, me, MIN_MEAS);
			अगर (atomic_inc_वापस(&n_rcu_scale_ग_लिखोr_finished) >=
			    nrealग_लिखोrs) अणु
				schedule_समयout_पूर्णांकerruptible(10);
				rcu_ftrace_dump(DUMP_ALL);
				SCALEOUT_STRING("Test complete");
				t_rcu_scale_ग_लिखोr_finished = t;
				अगर (gp_exp) अणु
					b_rcu_gp_test_finished =
						cur_ops->exp_completed() / 2;
				पूर्ण अन्यथा अणु
					b_rcu_gp_test_finished =
						cur_ops->get_gp_seq();
				पूर्ण
				अगर (shutकरोwn) अणु
					smp_mb(); /* Assign beक्रमe wake. */
					wake_up(&shutकरोwn_wq);
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (करोne && !allकरोne &&
		    atomic_पढ़ो(&n_rcu_scale_ग_लिखोr_finished) >= nrealग_लिखोrs)
			allकरोne = true;
		अगर (started && !allकरोne && i < MAX_MEAS - 1)
			i++;
		rcu_scale_रुको_shutकरोwn();
	पूर्ण जबतक (!torture_must_stop());
	अगर (gp_async) अणु
		cur_ops->gp_barrier();
	पूर्ण
	ग_लिखोr_n_durations[me] = i_max;
	torture_kthपढ़ो_stopping("rcu_scale_writer");
	वापस 0;
पूर्ण

अटल व्योम
rcu_scale_prपूर्णांक_module_parms(काष्ठा rcu_scale_ops *cur_ops, स्थिर अक्षर *tag)
अणु
	pr_alert("%s" SCALE_FLAG
		 "--- %s: nreaders=%d nwriters=%d verbose=%d shutdown=%d\n",
		 scale_type, tag, nrealपढ़ोers, nrealग_लिखोrs, verbose, shutकरोwn);
पूर्ण

अटल व्योम
rcu_scale_cleanup(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक j;
	पूर्णांक ngps = 0;
	u64 *wdp;
	u64 *wdpp;

	/*
	 * Would like warning at start, but everything is expedited
	 * during the mid-boot phase, so have to रुको till the end.
	 */
	अगर (rcu_gp_is_expedited() && !rcu_gp_is_normal() && !gp_exp)
		VERBOSE_SCALEOUT_ERRSTRING("All grace periods expedited, no normal ones to measure!");
	अगर (rcu_gp_is_normal() && gp_exp)
		VERBOSE_SCALEOUT_ERRSTRING("All grace periods normal, no expedited ones to measure!");
	अगर (gp_exp && gp_async)
		VERBOSE_SCALEOUT_ERRSTRING("No expedited async GPs, so went with async!");

	अगर (torture_cleanup_begin())
		वापस;
	अगर (!cur_ops) अणु
		torture_cleanup_end();
		वापस;
	पूर्ण

	अगर (पढ़ोer_tasks) अणु
		क्रम (i = 0; i < nrealपढ़ोers; i++)
			torture_stop_kthपढ़ो(rcu_scale_पढ़ोer,
					     पढ़ोer_tasks[i]);
		kमुक्त(पढ़ोer_tasks);
	पूर्ण

	अगर (ग_लिखोr_tasks) अणु
		क्रम (i = 0; i < nrealग_लिखोrs; i++) अणु
			torture_stop_kthपढ़ो(rcu_scale_ग_लिखोr,
					     ग_लिखोr_tasks[i]);
			अगर (!ग_लिखोr_n_durations)
				जारी;
			j = ग_लिखोr_n_durations[i];
			pr_alert("%s%s writer %d gps: %d\n",
				 scale_type, SCALE_FLAG, i, j);
			ngps += j;
		पूर्ण
		pr_alert("%s%s start: %llu end: %llu duration: %llu gps: %d batches: %ld\n",
			 scale_type, SCALE_FLAG,
			 t_rcu_scale_ग_लिखोr_started, t_rcu_scale_ग_लिखोr_finished,
			 t_rcu_scale_ग_लिखोr_finished -
			 t_rcu_scale_ग_लिखोr_started,
			 ngps,
			 rcuscale_seq_dअगरf(b_rcu_gp_test_finished,
					   b_rcu_gp_test_started));
		क्रम (i = 0; i < nrealग_लिखोrs; i++) अणु
			अगर (!ग_लिखोr_durations)
				अवरोध;
			अगर (!ग_लिखोr_n_durations)
				जारी;
			wdpp = ग_लिखोr_durations[i];
			अगर (!wdpp)
				जारी;
			क्रम (j = 0; j <= ग_लिखोr_n_durations[i]; j++) अणु
				wdp = &wdpp[j];
				pr_alert("%s%s %4d writer-duration: %5d %llu\n",
					scale_type, SCALE_FLAG,
					i, j, *wdp);
				अगर (j % 100 == 0)
					schedule_समयout_unपूर्णांकerruptible(1);
			पूर्ण
			kमुक्त(ग_लिखोr_durations[i]);
		पूर्ण
		kमुक्त(ग_लिखोr_tasks);
		kमुक्त(ग_लिखोr_durations);
		kमुक्त(ग_लिखोr_n_durations);
	पूर्ण

	/* Do torture-type-specअगरic cleanup operations.  */
	अगर (cur_ops->cleanup != शून्य)
		cur_ops->cleanup();

	torture_cleanup_end();
पूर्ण

/*
 * Return the number अगर non-negative.  If -1, the number of CPUs.
 * If less than -1, that much less than the number of CPUs, but
 * at least one.
 */
अटल पूर्णांक compute_real(पूर्णांक n)
अणु
	पूर्णांक nr;

	अगर (n >= 0) अणु
		nr = n;
	पूर्ण अन्यथा अणु
		nr = num_online_cpus() + 1 + n;
		अगर (nr <= 0)
			nr = 1;
	पूर्ण
	वापस nr;
पूर्ण

/*
 * RCU scalability shutकरोwn kthपढ़ो.  Just रुकोs to be awakened, then shuts
 * करोwn प्रणाली.
 */
अटल पूर्णांक
rcu_scale_shutकरोwn(व्योम *arg)
अणु
	रुको_event(shutकरोwn_wq,
		   atomic_पढ़ो(&n_rcu_scale_ग_लिखोr_finished) >= nrealग_लिखोrs);
	smp_mb(); /* Wake beक्रमe output. */
	rcu_scale_cleanup();
	kernel_घातer_off();
	वापस -EINVAL;
पूर्ण

/*
 * kमुक्त_rcu() scalability tests: Start a kमुक्त_rcu() loop on all CPUs क्रम number
 * of iterations and measure total समय and number of GP क्रम all iterations to complete.
 */

torture_param(पूर्णांक, kमुक्त_nthपढ़ोs, -1, "Number of threads running loops of kfree_rcu().");
torture_param(पूर्णांक, kमुक्त_alloc_num, 8000, "Number of allocations and frees done in an iteration.");
torture_param(पूर्णांक, kमुक्त_loops, 10, "Number of loops doing kfree_alloc_num allocations and frees.");
torture_param(bool, kमुक्त_rcu_test_द्विगुन, false, "Do we run a kfree_rcu() double-argument scale test?");
torture_param(bool, kमुक्त_rcu_test_single, false, "Do we run a kfree_rcu() single-argument scale test?");

अटल काष्ठा task_काष्ठा **kमुक्त_पढ़ोer_tasks;
अटल पूर्णांक kमुक्त_nrealthपढ़ोs;
अटल atomic_t n_kमुक्त_scale_thपढ़ो_started;
अटल atomic_t n_kमुक्त_scale_thपढ़ो_ended;

काष्ठा kमुक्त_obj अणु
	अक्षर kमुक्त_obj[8];
	काष्ठा rcu_head rh;
पूर्ण;

अटल पूर्णांक
kमुक्त_scale_thपढ़ो(व्योम *arg)
अणु
	पूर्णांक i, loop = 0;
	दीर्घ me = (दीर्घ)arg;
	काष्ठा kमुक्त_obj *alloc_ptr;
	u64 start_समय, end_समय;
	दीर्घ दीर्घ mem_begin, mem_during = 0;
	bool kमुक्त_rcu_test_both;
	DEFINE_TORTURE_RANDOM(tr);

	VERBOSE_SCALEOUT_STRING("kfree_scale_thread task started");
	set_cpus_allowed_ptr(current, cpumask_of(me % nr_cpu_ids));
	set_user_nice(current, MAX_NICE);
	kमुक्त_rcu_test_both = (kमुक्त_rcu_test_single == kमुक्त_rcu_test_द्विगुन);

	start_समय = kसमय_get_mono_fast_ns();

	अगर (atomic_inc_वापस(&n_kमुक्त_scale_thपढ़ो_started) >= kमुक्त_nrealthपढ़ोs) अणु
		अगर (gp_exp)
			b_rcu_gp_test_started = cur_ops->exp_completed() / 2;
		अन्यथा
			b_rcu_gp_test_started = cur_ops->get_gp_seq();
	पूर्ण

	करो अणु
		अगर (!mem_during) अणु
			mem_during = mem_begin = si_mem_available();
		पूर्ण अन्यथा अगर (loop % (kमुक्त_loops / 4) == 0) अणु
			mem_during = (mem_during + si_mem_available()) / 2;
		पूर्ण

		क्रम (i = 0; i < kमुक्त_alloc_num; i++) अणु
			alloc_ptr = kदो_स्मृति(kमुक्त_mult * माप(काष्ठा kमुक्त_obj), GFP_KERNEL);
			अगर (!alloc_ptr)
				वापस -ENOMEM;

			// By शेष kमुक्त_rcu_test_single and kमुक्त_rcu_test_द्विगुन are
			// initialized to false. If both have the same value (false or true)
			// both are अक्रमomly tested, otherwise only the one with value true
			// is tested.
			अगर ((kमुक्त_rcu_test_single && !kमुक्त_rcu_test_द्विगुन) ||
					(kमुक्त_rcu_test_both && torture_अक्रमom(&tr) & 0x800))
				kमुक्त_rcu(alloc_ptr);
			अन्यथा
				kमुक्त_rcu(alloc_ptr, rh);
		पूर्ण

		cond_resched();
	पूर्ण जबतक (!torture_must_stop() && ++loop < kमुक्त_loops);

	अगर (atomic_inc_वापस(&n_kमुक्त_scale_thपढ़ो_ended) >= kमुक्त_nrealthपढ़ोs) अणु
		end_समय = kसमय_get_mono_fast_ns();

		अगर (gp_exp)
			b_rcu_gp_test_finished = cur_ops->exp_completed() / 2;
		अन्यथा
			b_rcu_gp_test_finished = cur_ops->get_gp_seq();

		pr_alert("Total time taken by all kfree'ers: %llu ns, loops: %d, batches: %ld, memory footprint: %lldMB\n",
		       (अचिन्हित दीर्घ दीर्घ)(end_समय - start_समय), kमुक्त_loops,
		       rcuscale_seq_dअगरf(b_rcu_gp_test_finished, b_rcu_gp_test_started),
		       (mem_begin - mem_during) >> (20 - PAGE_SHIFT));

		अगर (shutकरोwn) अणु
			smp_mb(); /* Assign beक्रमe wake. */
			wake_up(&shutकरोwn_wq);
		पूर्ण
	पूर्ण

	torture_kthपढ़ो_stopping("kfree_scale_thread");
	वापस 0;
पूर्ण

अटल व्योम
kमुक्त_scale_cleanup(व्योम)
अणु
	पूर्णांक i;

	अगर (torture_cleanup_begin())
		वापस;

	अगर (kमुक्त_पढ़ोer_tasks) अणु
		क्रम (i = 0; i < kमुक्त_nrealthपढ़ोs; i++)
			torture_stop_kthपढ़ो(kमुक्त_scale_thपढ़ो,
					     kमुक्त_पढ़ोer_tasks[i]);
		kमुक्त(kमुक्त_पढ़ोer_tasks);
	पूर्ण

	torture_cleanup_end();
पूर्ण

/*
 * shutकरोwn kthपढ़ो.  Just रुकोs to be awakened, then shuts करोwn प्रणाली.
 */
अटल पूर्णांक
kमुक्त_scale_shutकरोwn(व्योम *arg)
अणु
	रुको_event(shutकरोwn_wq,
		   atomic_पढ़ो(&n_kमुक्त_scale_thपढ़ो_ended) >= kमुक्त_nrealthपढ़ोs);

	smp_mb(); /* Wake beक्रमe output. */

	kमुक्त_scale_cleanup();
	kernel_घातer_off();
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __init
kमुक्त_scale_init(व्योम)
अणु
	दीर्घ i;
	पूर्णांक firsterr = 0;

	kमुक्त_nrealthपढ़ोs = compute_real(kमुक्त_nthपढ़ोs);
	/* Start up the kthपढ़ोs. */
	अगर (shutकरोwn) अणु
		init_रुकोqueue_head(&shutकरोwn_wq);
		firsterr = torture_create_kthपढ़ो(kमुक्त_scale_shutकरोwn, शून्य,
						  shutकरोwn_task);
		अगर (firsterr)
			जाओ unwind;
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण

	pr_alert("kfree object size=%zu\n", kमुक्त_mult * माप(काष्ठा kमुक्त_obj));

	kमुक्त_पढ़ोer_tasks = kसुस्मृति(kमुक्त_nrealthपढ़ोs, माप(kमुक्त_पढ़ोer_tasks[0]),
			       GFP_KERNEL);
	अगर (kमुक्त_पढ़ोer_tasks == शून्य) अणु
		firsterr = -ENOMEM;
		जाओ unwind;
	पूर्ण

	क्रम (i = 0; i < kमुक्त_nrealthपढ़ोs; i++) अणु
		firsterr = torture_create_kthपढ़ो(kमुक्त_scale_thपढ़ो, (व्योम *)i,
						  kमुक्त_पढ़ोer_tasks[i]);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण

	जबतक (atomic_पढ़ो(&n_kमुक्त_scale_thपढ़ो_started) < kमुक्त_nrealthपढ़ोs)
		schedule_समयout_unपूर्णांकerruptible(1);

	torture_init_end();
	वापस 0;

unwind:
	torture_init_end();
	kमुक्त_scale_cleanup();
	वापस firsterr;
पूर्ण

अटल पूर्णांक __init
rcu_scale_init(व्योम)
अणु
	दीर्घ i;
	पूर्णांक firsterr = 0;
	अटल काष्ठा rcu_scale_ops *scale_ops[] = अणु
		&rcu_ops, &srcu_ops, &srcud_ops, &tasks_ops, &tasks_tracing_ops
	पूर्ण;

	अगर (!torture_init_begin(scale_type, verbose))
		वापस -EBUSY;

	/* Process args and announce that the scalability'er is on the job. */
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

	अगर (kमुक्त_rcu_test)
		वापस kमुक्त_scale_init();

	nrealग_लिखोrs = compute_real(nग_लिखोrs);
	nrealपढ़ोers = compute_real(nपढ़ोers);
	atomic_set(&n_rcu_scale_पढ़ोer_started, 0);
	atomic_set(&n_rcu_scale_ग_लिखोr_started, 0);
	atomic_set(&n_rcu_scale_ग_लिखोr_finished, 0);
	rcu_scale_prपूर्णांक_module_parms(cur_ops, "Start of test");

	/* Start up the kthपढ़ोs. */

	अगर (shutकरोwn) अणु
		init_रुकोqueue_head(&shutकरोwn_wq);
		firsterr = torture_create_kthपढ़ो(rcu_scale_shutकरोwn, शून्य,
						  shutकरोwn_task);
		अगर (firsterr)
			जाओ unwind;
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण
	पढ़ोer_tasks = kसुस्मृति(nrealपढ़ोers, माप(पढ़ोer_tasks[0]),
			       GFP_KERNEL);
	अगर (पढ़ोer_tasks == शून्य) अणु
		VERBOSE_SCALEOUT_ERRSTRING("out of memory");
		firsterr = -ENOMEM;
		जाओ unwind;
	पूर्ण
	क्रम (i = 0; i < nrealपढ़ोers; i++) अणु
		firsterr = torture_create_kthपढ़ो(rcu_scale_पढ़ोer, (व्योम *)i,
						  पढ़ोer_tasks[i]);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण
	जबतक (atomic_पढ़ो(&n_rcu_scale_पढ़ोer_started) < nrealपढ़ोers)
		schedule_समयout_unपूर्णांकerruptible(1);
	ग_लिखोr_tasks = kसुस्मृति(nrealग_लिखोrs, माप(पढ़ोer_tasks[0]),
			       GFP_KERNEL);
	ग_लिखोr_durations = kसुस्मृति(nrealग_लिखोrs, माप(*ग_लिखोr_durations),
				   GFP_KERNEL);
	ग_लिखोr_n_durations =
		kसुस्मृति(nrealग_लिखोrs, माप(*ग_लिखोr_n_durations),
			GFP_KERNEL);
	अगर (!ग_लिखोr_tasks || !ग_लिखोr_durations || !ग_लिखोr_n_durations) अणु
		VERBOSE_SCALEOUT_ERRSTRING("out of memory");
		firsterr = -ENOMEM;
		जाओ unwind;
	पूर्ण
	क्रम (i = 0; i < nrealग_लिखोrs; i++) अणु
		ग_लिखोr_durations[i] =
			kसुस्मृति(MAX_MEAS, माप(*ग_लिखोr_durations[i]),
				GFP_KERNEL);
		अगर (!ग_लिखोr_durations[i]) अणु
			firsterr = -ENOMEM;
			जाओ unwind;
		पूर्ण
		firsterr = torture_create_kthपढ़ो(rcu_scale_ग_लिखोr, (व्योम *)i,
						  ग_लिखोr_tasks[i]);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण
	torture_init_end();
	वापस 0;

unwind:
	torture_init_end();
	rcu_scale_cleanup();
	अगर (shutकरोwn) अणु
		WARN_ON(!IS_MODULE(CONFIG_RCU_SCALE_TEST));
		kernel_घातer_off();
	पूर्ण
	वापस firsterr;
पूर्ण

module_init(rcu_scale_init);
module_निकास(rcu_scale_cleanup);
