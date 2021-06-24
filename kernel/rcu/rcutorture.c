<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Read-Copy Update module-based torture test facility
 *
 * Copyright (C) IBM Corporation, 2005, 2006
 *
 * Authors: Paul E. McKenney <paulmck@linux.ibm.com>
 *	  Josh Triplett <josh@joshtriplett.org>
 *
 * See also:  Documentation/RCU/torture.rst
 */

#घोषणा pr_fmt(fmt) fmt

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/err.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/smp.h>
#समावेश <linux/rcupdate_रुको.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched/संकेत.स>
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
#समावेश <linux/trace_घड़ी.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/torture.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/sysctl.h>
#समावेश <linux/oom.h>
#समावेश <linux/tick.h>
#समावेश <linux/rcupdate_trace.h>

#समावेश "rcu.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Paul E. McKenney <paulmck@linux.ibm.com> and Josh Triplett <josh@joshtriplett.org>");

/* Bits क्रम ->extendables field, extendables param, and related definitions. */
#घोषणा RCUTORTURE_RDR_SHIFT	 8	/* Put SRCU index in upper bits. */
#घोषणा RCUTORTURE_RDR_MASK	 ((1 << RCUTORTURE_RDR_SHIFT) - 1)
#घोषणा RCUTORTURE_RDR_BH	 0x01	/* Extend पढ़ोers by disabling bh. */
#घोषणा RCUTORTURE_RDR_IRQ	 0x02	/*  ... disabling पूर्णांकerrupts. */
#घोषणा RCUTORTURE_RDR_PREEMPT	 0x04	/*  ... disabling preemption. */
#घोषणा RCUTORTURE_RDR_RBH	 0x08	/*  ... rcu_पढ़ो_lock_bh(). */
#घोषणा RCUTORTURE_RDR_SCHED	 0x10	/*  ... rcu_पढ़ो_lock_sched(). */
#घोषणा RCUTORTURE_RDR_RCU	 0x20	/*  ... entering another RCU पढ़ोer. */
#घोषणा RCUTORTURE_RDR_NBITS	 6	/* Number of bits defined above. */
#घोषणा RCUTORTURE_MAX_EXTEND	 \
	(RCUTORTURE_RDR_BH | RCUTORTURE_RDR_IRQ | RCUTORTURE_RDR_PREEMPT | \
	 RCUTORTURE_RDR_RBH | RCUTORTURE_RDR_SCHED)
#घोषणा RCUTORTURE_RDR_MAX_LOOPS 0x7	/* Maximum पढ़ोer extensions. */
					/* Must be घातer of two minus one. */
#घोषणा RCUTORTURE_RDR_MAX_SEGS (RCUTORTURE_RDR_MAX_LOOPS + 3)

torture_param(पूर्णांक, extendables, RCUTORTURE_MAX_EXTEND,
	      "Extend readers by disabling bh (1), irqs (2), or preempt (4)");
torture_param(पूर्णांक, fqs_duration, 0,
	      "Duration of fqs bursts (us), 0 to disable");
torture_param(पूर्णांक, fqs_holकरोff, 0, "Holdoff time within fqs bursts (us)");
torture_param(पूर्णांक, fqs_stutter, 3, "Wait time between fqs bursts (s)");
torture_param(bool, fwd_progress, 1, "Test grace-period forward progress");
torture_param(पूर्णांक, fwd_progress_भाग, 4, "Fraction of CPU stall to wait");
torture_param(पूर्णांक, fwd_progress_holकरोff, 60,
	      "Time between forward-progress tests (s)");
torture_param(bool, fwd_progress_need_resched, 1,
	      "Hide cond_resched() behind need_resched()");
torture_param(bool, gp_cond, false, "Use conditional/async GP wait primitives");
torture_param(bool, gp_exp, false, "Use expedited GP wait primitives");
torture_param(bool, gp_normal, false,
	     "Use normal (non-expedited) GP wait primitives");
torture_param(bool, gp_poll, false, "Use polling GP wait primitives");
torture_param(bool, gp_sync, false, "Use synchronous GP wait primitives");
torture_param(पूर्णांक, irqपढ़ोer, 1, "Allow RCU readers from irq handlers");
torture_param(पूर्णांक, leakpoपूर्णांकer, 0, "Leak pointer dereferences from readers");
torture_param(पूर्णांक, n_barrier_cbs, 0,
	     "# of callbacks/kthreads for barrier testing");
torture_param(पूर्णांक, nfakeग_लिखोrs, 4, "Number of RCU fake writer threads");
torture_param(पूर्णांक, nपढ़ोers, -1, "Number of RCU reader threads");
torture_param(पूर्णांक, object_debug, 0,
	     "Enable debug-object double call_rcu() testing");
torture_param(पूर्णांक, onoff_holकरोff, 0, "Time after boot before CPU hotplugs (s)");
torture_param(पूर्णांक, onoff_पूर्णांकerval, 0,
	     "Time between CPU hotplugs (jiffies), 0=disable");
torture_param(पूर्णांक, nocbs_nthपढ़ोs, 0, "Number of NOCB toggle threads, 0 to disable");
torture_param(पूर्णांक, nocbs_toggle, 1000, "Time between toggling nocb state (ms)");
torture_param(पूर्णांक, पढ़ो_निकास_delay, 13,
	      "Delay between read-then-exit episodes (s)");
torture_param(पूर्णांक, पढ़ो_निकास_burst, 16,
	      "# of read-then-exit bursts per episode, zero to disable");
torture_param(पूर्णांक, shuffle_पूर्णांकerval, 3, "Number of seconds between shuffles");
torture_param(पूर्णांक, shutकरोwn_secs, 0, "Shutdown time (s), <= zero to disable.");
torture_param(पूर्णांक, stall_cpu, 0, "Stall duration (s), zero to disable.");
torture_param(पूर्णांक, stall_cpu_holकरोff, 10,
	     "Time to wait before starting stall (s).");
torture_param(पूर्णांक, stall_cpu_irqsoff, 0, "Disable interrupts while stalling.");
torture_param(पूर्णांक, stall_cpu_block, 0, "Sleep while stalling.");
torture_param(पूर्णांक, stall_gp_kthपढ़ो, 0,
	      "Grace-period kthread stall duration (s).");
torture_param(पूर्णांक, stat_पूर्णांकerval, 60,
	     "Number of seconds between stats printk()s");
torture_param(पूर्णांक, stutter, 5, "Number of seconds to run/halt test");
torture_param(पूर्णांक, test_boost, 1, "Test RCU prio boost: 0=no, 1=maybe, 2=yes.");
torture_param(पूर्णांक, test_boost_duration, 4,
	     "Duration of each boost test, seconds.");
torture_param(पूर्णांक, test_boost_पूर्णांकerval, 7,
	     "Interval between boost tests, seconds.");
torture_param(bool, test_no_idle_hz, true,
	     "Test support for tickless idle CPUs");
torture_param(पूर्णांक, verbose, 1,
	     "Enable verbose debugging printk()s");

अटल अक्षर *torture_type = "rcu";
module_param(torture_type, अक्षरp, 0444);
MODULE_PARM_DESC(torture_type, "Type of RCU to torture (rcu, srcu, ...)");

अटल पूर्णांक nrealnocbers;
अटल पूर्णांक nrealपढ़ोers;
अटल काष्ठा task_काष्ठा *ग_लिखोr_task;
अटल काष्ठा task_काष्ठा **fakeग_लिखोr_tasks;
अटल काष्ठा task_काष्ठा **पढ़ोer_tasks;
अटल काष्ठा task_काष्ठा **nocb_tasks;
अटल काष्ठा task_काष्ठा *stats_task;
अटल काष्ठा task_काष्ठा *fqs_task;
अटल काष्ठा task_काष्ठा *boost_tasks[NR_CPUS];
अटल काष्ठा task_काष्ठा *stall_task;
अटल काष्ठा task_काष्ठा *fwd_prog_task;
अटल काष्ठा task_काष्ठा **barrier_cbs_tasks;
अटल काष्ठा task_काष्ठा *barrier_task;
अटल काष्ठा task_काष्ठा *पढ़ो_निकास_task;

#घोषणा RCU_TORTURE_PIPE_LEN 10

// Mailbox-like काष्ठाure to check RCU global memory ordering.
काष्ठा rcu_torture_पढ़ोer_check अणु
	अचिन्हित दीर्घ rtc_myloops;
	पूर्णांक rtc_chkrdr;
	अचिन्हित दीर्घ rtc_chkloops;
	पूर्णांक rtc_पढ़ोy;
	काष्ठा rcu_torture_पढ़ोer_check *rtc_assigner;
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

// Update-side data काष्ठाure used to check RCU पढ़ोers.
काष्ठा rcu_torture अणु
	काष्ठा rcu_head rtort_rcu;
	पूर्णांक rtort_pipe_count;
	काष्ठा list_head rtort_मुक्त;
	पूर्णांक rtort_mbtest;
	काष्ठा rcu_torture_पढ़ोer_check *rtort_chkp;
पूर्ण;

अटल LIST_HEAD(rcu_torture_मुक्तlist);
अटल काष्ठा rcu_torture __rcu *rcu_torture_current;
अटल अचिन्हित दीर्घ rcu_torture_current_version;
अटल काष्ठा rcu_torture rcu_tortures[10 * RCU_TORTURE_PIPE_LEN];
अटल DEFINE_SPINLOCK(rcu_torture_lock);
अटल DEFINE_PER_CPU(दीर्घ [RCU_TORTURE_PIPE_LEN + 1], rcu_torture_count);
अटल DEFINE_PER_CPU(दीर्घ [RCU_TORTURE_PIPE_LEN + 1], rcu_torture_batch);
अटल atomic_t rcu_torture_wcount[RCU_TORTURE_PIPE_LEN + 1];
अटल काष्ठा rcu_torture_पढ़ोer_check *rcu_torture_पढ़ोer_mbchk;
अटल atomic_t n_rcu_torture_alloc;
अटल atomic_t n_rcu_torture_alloc_fail;
अटल atomic_t n_rcu_torture_मुक्त;
अटल atomic_t n_rcu_torture_mberror;
अटल atomic_t n_rcu_torture_mbchk_fail;
अटल atomic_t n_rcu_torture_mbchk_tries;
अटल atomic_t n_rcu_torture_error;
अटल दीर्घ n_rcu_torture_barrier_error;
अटल दीर्घ n_rcu_torture_boost_ktrerror;
अटल दीर्घ n_rcu_torture_boost_rterror;
अटल दीर्घ n_rcu_torture_boost_failure;
अटल दीर्घ n_rcu_torture_boosts;
अटल atomic_दीर्घ_t n_rcu_torture_समयrs;
अटल दीर्घ n_barrier_attempts;
अटल दीर्घ n_barrier_successes; /* did rcu_barrier test succeed? */
अटल अचिन्हित दीर्घ n_पढ़ो_निकासs;
अटल काष्ठा list_head rcu_torture_हटाओd;
अटल अचिन्हित दीर्घ shutकरोwn_jअगरfies;
अटल अचिन्हित दीर्घ start_gp_seq;
अटल atomic_दीर्घ_t n_nocb_offload;
अटल atomic_दीर्घ_t n_nocb_deoffload;

अटल पूर्णांक rcu_torture_ग_लिखोr_state;
#घोषणा RTWS_FIXED_DELAY	0
#घोषणा RTWS_DELAY		1
#घोषणा RTWS_REPLACE		2
#घोषणा RTWS_DEF_FREE		3
#घोषणा RTWS_EXP_SYNC		4
#घोषणा RTWS_COND_GET		5
#घोषणा RTWS_COND_SYNC		6
#घोषणा RTWS_POLL_GET		7
#घोषणा RTWS_POLL_WAIT		8
#घोषणा RTWS_SYNC		9
#घोषणा RTWS_STUTTER		10
#घोषणा RTWS_STOPPING		11
अटल स्थिर अक्षर * स्थिर rcu_torture_ग_लिखोr_state_names[] = अणु
	"RTWS_FIXED_DELAY",
	"RTWS_DELAY",
	"RTWS_REPLACE",
	"RTWS_DEF_FREE",
	"RTWS_EXP_SYNC",
	"RTWS_COND_GET",
	"RTWS_COND_SYNC",
	"RTWS_POLL_GET",
	"RTWS_POLL_WAIT",
	"RTWS_SYNC",
	"RTWS_STUTTER",
	"RTWS_STOPPING",
पूर्ण;

/* Record पढ़ोer segment types and duration क्रम first failing पढ़ो. */
काष्ठा rt_पढ़ो_seg अणु
	पूर्णांक rt_पढ़ोstate;
	अचिन्हित दीर्घ rt_delay_jअगरfies;
	अचिन्हित दीर्घ rt_delay_ms;
	अचिन्हित दीर्घ rt_delay_us;
	bool rt_preempted;
पूर्ण;
अटल पूर्णांक err_segs_recorded;
अटल काष्ठा rt_पढ़ो_seg err_segs[RCUTORTURE_RDR_MAX_SEGS];
अटल पूर्णांक rt_पढ़ो_nsegs;

अटल स्थिर अक्षर *rcu_torture_ग_लिखोr_state_getname(व्योम)
अणु
	अचिन्हित पूर्णांक i = READ_ONCE(rcu_torture_ग_लिखोr_state);

	अगर (i >= ARRAY_SIZE(rcu_torture_ग_लिखोr_state_names))
		वापस "???";
	वापस rcu_torture_ग_लिखोr_state_names[i];
पूर्ण

#अगर defined(CONFIG_RCU_BOOST) && defined(CONFIG_PREEMPT_RT)
# define rcu_can_boost() 1
#अन्यथा
# define rcu_can_boost() 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_RCU_TRACE
अटल u64 notrace rcu_trace_घड़ी_local(व्योम)
अणु
	u64 ts = trace_घड़ी_local();

	(व्योम)करो_भाग(ts, NSEC_PER_USEC);
	वापस ts;
पूर्ण
#अन्यथा /* #अगर_घोषित CONFIG_RCU_TRACE */
अटल u64 notrace rcu_trace_घड़ी_local(व्योम)
अणु
	वापस 0ULL;
पूर्ण
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_RCU_TRACE */

/*
 * Stop aggressive CPU-hog tests a bit beक्रमe the end of the test in order
 * to aव्योम पूर्णांकerfering with test shutकरोwn.
 */
अटल bool shutकरोwn_समय_arrived(व्योम)
अणु
	वापस shutकरोwn_secs && समय_after(jअगरfies, shutकरोwn_jअगरfies - 30 * HZ);
पूर्ण

अटल अचिन्हित दीर्घ boost_startसमय;	/* jअगरfies of next boost test start. */
अटल DEFINE_MUTEX(boost_mutex);	/* protect setting boost_startसमय */
					/*  and boost task create/destroy. */
अटल atomic_t barrier_cbs_count;	/* Barrier callbacks रेजिस्टरed. */
अटल bool barrier_phase;		/* Test phase. */
अटल atomic_t barrier_cbs_invoked;	/* Barrier callbacks invoked. */
अटल रुको_queue_head_t *barrier_cbs_wq; /* Coordinate barrier testing. */
अटल DECLARE_WAIT_QUEUE_HEAD(barrier_wq);

अटल bool rcu_fwd_cb_nodelay;		/* Short rcu_torture_delay() delays. */

/*
 * Allocate an element from the rcu_tortures pool.
 */
अटल काष्ठा rcu_torture *
rcu_torture_alloc(व्योम)
अणु
	काष्ठा list_head *p;

	spin_lock_bh(&rcu_torture_lock);
	अगर (list_empty(&rcu_torture_मुक्तlist)) अणु
		atomic_inc(&n_rcu_torture_alloc_fail);
		spin_unlock_bh(&rcu_torture_lock);
		वापस शून्य;
	पूर्ण
	atomic_inc(&n_rcu_torture_alloc);
	p = rcu_torture_मुक्तlist.next;
	list_del_init(p);
	spin_unlock_bh(&rcu_torture_lock);
	वापस container_of(p, काष्ठा rcu_torture, rtort_मुक्त);
पूर्ण

/*
 * Free an element to the rcu_tortures pool.
 */
अटल व्योम
rcu_torture_मुक्त(काष्ठा rcu_torture *p)
अणु
	atomic_inc(&n_rcu_torture_मुक्त);
	spin_lock_bh(&rcu_torture_lock);
	list_add_tail(&p->rtort_मुक्त, &rcu_torture_मुक्तlist);
	spin_unlock_bh(&rcu_torture_lock);
पूर्ण

/*
 * Operations vector क्रम selecting dअगरferent types of tests.
 */

काष्ठा rcu_torture_ops अणु
	पूर्णांक ttype;
	व्योम (*init)(व्योम);
	व्योम (*cleanup)(व्योम);
	पूर्णांक (*पढ़ोlock)(व्योम);
	व्योम (*पढ़ो_delay)(काष्ठा torture_अक्रमom_state *rrsp,
			   काष्ठा rt_पढ़ो_seg *rtrsp);
	व्योम (*पढ़ोunlock)(पूर्णांक idx);
	अचिन्हित दीर्घ (*get_gp_seq)(व्योम);
	अचिन्हित दीर्घ (*gp_dअगरf)(अचिन्हित दीर्घ new, अचिन्हित दीर्घ old);
	व्योम (*deferred_मुक्त)(काष्ठा rcu_torture *p);
	व्योम (*sync)(व्योम);
	व्योम (*exp_sync)(व्योम);
	अचिन्हित दीर्घ (*get_gp_state)(व्योम);
	अचिन्हित दीर्घ (*start_gp_poll)(व्योम);
	bool (*poll_gp_state)(अचिन्हित दीर्घ oldstate);
	व्योम (*cond_sync)(अचिन्हित दीर्घ oldstate);
	call_rcu_func_t call;
	व्योम (*cb_barrier)(व्योम);
	व्योम (*fqs)(व्योम);
	व्योम (*stats)(व्योम);
	व्योम (*gp_kthपढ़ो_dbg)(व्योम);
	पूर्णांक (*stall_dur)(व्योम);
	पूर्णांक irq_capable;
	पूर्णांक can_boost;
	पूर्णांक extendables;
	पूर्णांक slow_gps;
	स्थिर अक्षर *name;
पूर्ण;

अटल काष्ठा rcu_torture_ops *cur_ops;

/*
 * Definitions क्रम rcu torture testing.
 */

अटल पूर्णांक rcu_torture_पढ़ो_lock(व्योम) __acquires(RCU)
अणु
	rcu_पढ़ो_lock();
	वापस 0;
पूर्ण

अटल व्योम
rcu_पढ़ो_delay(काष्ठा torture_अक्रमom_state *rrsp, काष्ठा rt_पढ़ो_seg *rtrsp)
अणु
	अचिन्हित दीर्घ started;
	अचिन्हित दीर्घ completed;
	स्थिर अचिन्हित दीर्घ लघुdelay_us = 200;
	अचिन्हित दीर्घ दीर्घdelay_ms = 300;
	अचिन्हित दीर्घ दीर्घ ts;

	/* We want a लघु delay someबार to make a पढ़ोer delay the grace
	 * period, and we want a दीर्घ delay occasionally to trigger
	 * क्रमce_quiescent_state. */

	अगर (!READ_ONCE(rcu_fwd_cb_nodelay) &&
	    !(torture_अक्रमom(rrsp) % (nrealपढ़ोers * 2000 * दीर्घdelay_ms))) अणु
		started = cur_ops->get_gp_seq();
		ts = rcu_trace_घड़ी_local();
		अगर (preempt_count() & (SOFTIRQ_MASK | HARसूचीQ_MASK))
			दीर्घdelay_ms = 5; /* Aव्योम triggering BH limits. */
		mdelay(दीर्घdelay_ms);
		rtrsp->rt_delay_ms = दीर्घdelay_ms;
		completed = cur_ops->get_gp_seq();
		करो_trace_rcu_torture_पढ़ो(cur_ops->name, शून्य, ts,
					  started, completed);
	पूर्ण
	अगर (!(torture_अक्रमom(rrsp) % (nrealपढ़ोers * 2 * लघुdelay_us))) अणु
		udelay(लघुdelay_us);
		rtrsp->rt_delay_us = लघुdelay_us;
	पूर्ण
	अगर (!preempt_count() &&
	    !(torture_अक्रमom(rrsp) % (nrealपढ़ोers * 500))) अणु
		torture_preempt_schedule();  /* QS only अगर preemptible. */
		rtrsp->rt_preempted = true;
	पूर्ण
पूर्ण

अटल व्योम rcu_torture_पढ़ो_unlock(पूर्णांक idx) __releases(RCU)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * Update callback in the pipe.  This should be invoked after a grace period.
 */
अटल bool
rcu_torture_pipe_update_one(काष्ठा rcu_torture *rp)
अणु
	पूर्णांक i;
	काष्ठा rcu_torture_पढ़ोer_check *rtrcp = READ_ONCE(rp->rtort_chkp);

	अगर (rtrcp) अणु
		WRITE_ONCE(rp->rtort_chkp, शून्य);
		smp_store_release(&rtrcp->rtc_पढ़ोy, 1); // Pair with smp_load_acquire().
	पूर्ण
	i = READ_ONCE(rp->rtort_pipe_count);
	अगर (i > RCU_TORTURE_PIPE_LEN)
		i = RCU_TORTURE_PIPE_LEN;
	atomic_inc(&rcu_torture_wcount[i]);
	WRITE_ONCE(rp->rtort_pipe_count, i + 1);
	अगर (rp->rtort_pipe_count >= RCU_TORTURE_PIPE_LEN) अणु
		rp->rtort_mbtest = 0;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Update all callbacks in the pipe.  Suitable क्रम synchronous grace-period
 * primitives.
 */
अटल व्योम
rcu_torture_pipe_update(काष्ठा rcu_torture *old_rp)
अणु
	काष्ठा rcu_torture *rp;
	काष्ठा rcu_torture *rp1;

	अगर (old_rp)
		list_add(&old_rp->rtort_मुक्त, &rcu_torture_हटाओd);
	list_क्रम_each_entry_safe(rp, rp1, &rcu_torture_हटाओd, rtort_मुक्त) अणु
		अगर (rcu_torture_pipe_update_one(rp)) अणु
			list_del(&rp->rtort_मुक्त);
			rcu_torture_मुक्त(rp);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
rcu_torture_cb(काष्ठा rcu_head *p)
अणु
	काष्ठा rcu_torture *rp = container_of(p, काष्ठा rcu_torture, rtort_rcu);

	अगर (torture_must_stop_irq()) अणु
		/* Test is ending, just drop callbacks on the न्यूनमान. */
		/* The next initialization will pick up the pieces. */
		वापस;
	पूर्ण
	अगर (rcu_torture_pipe_update_one(rp))
		rcu_torture_मुक्त(rp);
	अन्यथा
		cur_ops->deferred_मुक्त(rp);
पूर्ण

अटल अचिन्हित दीर्घ rcu_no_completed(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम rcu_torture_deferred_मुक्त(काष्ठा rcu_torture *p)
अणु
	call_rcu(&p->rtort_rcu, rcu_torture_cb);
पूर्ण

अटल व्योम rcu_sync_torture_init(व्योम)
अणु
	INIT_LIST_HEAD(&rcu_torture_हटाओd);
पूर्ण

अटल काष्ठा rcu_torture_ops rcu_ops = अणु
	.ttype		= RCU_FLAVOR,
	.init		= rcu_sync_torture_init,
	.पढ़ोlock	= rcu_torture_पढ़ो_lock,
	.पढ़ो_delay	= rcu_पढ़ो_delay,
	.पढ़ोunlock	= rcu_torture_पढ़ो_unlock,
	.get_gp_seq	= rcu_get_gp_seq,
	.gp_dअगरf	= rcu_seq_dअगरf,
	.deferred_मुक्त	= rcu_torture_deferred_मुक्त,
	.sync		= synchronize_rcu,
	.exp_sync	= synchronize_rcu_expedited,
	.get_gp_state	= get_state_synchronize_rcu,
	.start_gp_poll	= start_poll_synchronize_rcu,
	.poll_gp_state	= poll_state_synchronize_rcu,
	.cond_sync	= cond_synchronize_rcu,
	.call		= call_rcu,
	.cb_barrier	= rcu_barrier,
	.fqs		= rcu_क्रमce_quiescent_state,
	.stats		= शून्य,
	.gp_kthपढ़ो_dbg	= show_rcu_gp_kthपढ़ोs,
	.stall_dur	= rcu_jअगरfies_till_stall_check,
	.irq_capable	= 1,
	.can_boost	= rcu_can_boost(),
	.extendables	= RCUTORTURE_MAX_EXTEND,
	.name		= "rcu"
पूर्ण;

/*
 * Don't even think about trying any of these in real lअगरe!!!
 * The names includes "busted", and they really means it!
 * The only purpose of these functions is to provide a buggy RCU
 * implementation to make sure that rcutorture correctly emits
 * buggy-RCU error messages.
 */
अटल व्योम rcu_busted_torture_deferred_मुक्त(काष्ठा rcu_torture *p)
अणु
	/* This is a deliberate bug क्रम testing purposes only! */
	rcu_torture_cb(&p->rtort_rcu);
पूर्ण

अटल व्योम synchronize_rcu_busted(व्योम)
अणु
	/* This is a deliberate bug क्रम testing purposes only! */
पूर्ण

अटल व्योम
call_rcu_busted(काष्ठा rcu_head *head, rcu_callback_t func)
अणु
	/* This is a deliberate bug क्रम testing purposes only! */
	func(head);
पूर्ण

अटल काष्ठा rcu_torture_ops rcu_busted_ops = अणु
	.ttype		= INVALID_RCU_FLAVOR,
	.init		= rcu_sync_torture_init,
	.पढ़ोlock	= rcu_torture_पढ़ो_lock,
	.पढ़ो_delay	= rcu_पढ़ो_delay,  /* just reuse rcu's version. */
	.पढ़ोunlock	= rcu_torture_पढ़ो_unlock,
	.get_gp_seq	= rcu_no_completed,
	.deferred_मुक्त	= rcu_busted_torture_deferred_मुक्त,
	.sync		= synchronize_rcu_busted,
	.exp_sync	= synchronize_rcu_busted,
	.call		= call_rcu_busted,
	.cb_barrier	= शून्य,
	.fqs		= शून्य,
	.stats		= शून्य,
	.irq_capable	= 1,
	.name		= "busted"
पूर्ण;

/*
 * Definitions क्रम srcu torture testing.
 */

DEFINE_STATIC_SRCU(srcu_ctl);
अटल काष्ठा srcu_काष्ठा srcu_ctld;
अटल काष्ठा srcu_काष्ठा *srcu_ctlp = &srcu_ctl;

अटल पूर्णांक srcu_torture_पढ़ो_lock(व्योम) __acquires(srcu_ctlp)
अणु
	वापस srcu_पढ़ो_lock(srcu_ctlp);
पूर्ण

अटल व्योम
srcu_पढ़ो_delay(काष्ठा torture_अक्रमom_state *rrsp, काष्ठा rt_पढ़ो_seg *rtrsp)
अणु
	दीर्घ delay;
	स्थिर दीर्घ uspertick = 1000000 / HZ;
	स्थिर दीर्घ दीर्घdelay = 10;

	/* We want there to be दीर्घ-running पढ़ोers, but not all the समय. */

	delay = torture_अक्रमom(rrsp) %
		(nrealपढ़ोers * 2 * दीर्घdelay * uspertick);
	अगर (!delay && in_task()) अणु
		schedule_समयout_पूर्णांकerruptible(दीर्घdelay);
		rtrsp->rt_delay_jअगरfies = दीर्घdelay;
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_delay(rrsp, rtrsp);
	पूर्ण
पूर्ण

अटल व्योम srcu_torture_पढ़ो_unlock(पूर्णांक idx) __releases(srcu_ctlp)
अणु
	srcu_पढ़ो_unlock(srcu_ctlp, idx);
पूर्ण

अटल अचिन्हित दीर्घ srcu_torture_completed(व्योम)
अणु
	वापस srcu_batches_completed(srcu_ctlp);
पूर्ण

अटल व्योम srcu_torture_deferred_मुक्त(काष्ठा rcu_torture *rp)
अणु
	call_srcu(srcu_ctlp, &rp->rtort_rcu, rcu_torture_cb);
पूर्ण

अटल व्योम srcu_torture_synchronize(व्योम)
अणु
	synchronize_srcu(srcu_ctlp);
पूर्ण

अटल अचिन्हित दीर्घ srcu_torture_get_gp_state(व्योम)
अणु
	वापस get_state_synchronize_srcu(srcu_ctlp);
पूर्ण

अटल अचिन्हित दीर्घ srcu_torture_start_gp_poll(व्योम)
अणु
	वापस start_poll_synchronize_srcu(srcu_ctlp);
पूर्ण

अटल bool srcu_torture_poll_gp_state(अचिन्हित दीर्घ oldstate)
अणु
	वापस poll_state_synchronize_srcu(srcu_ctlp, oldstate);
पूर्ण

अटल व्योम srcu_torture_call(काष्ठा rcu_head *head,
			      rcu_callback_t func)
अणु
	call_srcu(srcu_ctlp, head, func);
पूर्ण

अटल व्योम srcu_torture_barrier(व्योम)
अणु
	srcu_barrier(srcu_ctlp);
पूर्ण

अटल व्योम srcu_torture_stats(व्योम)
अणु
	srcu_torture_stats_prपूर्णांक(srcu_ctlp, torture_type, TORTURE_FLAG);
पूर्ण

अटल व्योम srcu_torture_synchronize_expedited(व्योम)
अणु
	synchronize_srcu_expedited(srcu_ctlp);
पूर्ण

अटल काष्ठा rcu_torture_ops srcu_ops = अणु
	.ttype		= SRCU_FLAVOR,
	.init		= rcu_sync_torture_init,
	.पढ़ोlock	= srcu_torture_पढ़ो_lock,
	.पढ़ो_delay	= srcu_पढ़ो_delay,
	.पढ़ोunlock	= srcu_torture_पढ़ो_unlock,
	.get_gp_seq	= srcu_torture_completed,
	.deferred_मुक्त	= srcu_torture_deferred_मुक्त,
	.sync		= srcu_torture_synchronize,
	.exp_sync	= srcu_torture_synchronize_expedited,
	.get_gp_state	= srcu_torture_get_gp_state,
	.start_gp_poll	= srcu_torture_start_gp_poll,
	.poll_gp_state	= srcu_torture_poll_gp_state,
	.call		= srcu_torture_call,
	.cb_barrier	= srcu_torture_barrier,
	.stats		= srcu_torture_stats,
	.irq_capable	= 1,
	.name		= "srcu"
पूर्ण;

अटल व्योम srcu_torture_init(व्योम)
अणु
	rcu_sync_torture_init();
	WARN_ON(init_srcu_काष्ठा(&srcu_ctld));
	srcu_ctlp = &srcu_ctld;
पूर्ण

अटल व्योम srcu_torture_cleanup(व्योम)
अणु
	cleanup_srcu_काष्ठा(&srcu_ctld);
	srcu_ctlp = &srcu_ctl; /* In हाल of a later rcutorture run. */
पूर्ण

/* As above, but dynamically allocated. */
अटल काष्ठा rcu_torture_ops srcud_ops = अणु
	.ttype		= SRCU_FLAVOR,
	.init		= srcu_torture_init,
	.cleanup	= srcu_torture_cleanup,
	.पढ़ोlock	= srcu_torture_पढ़ो_lock,
	.पढ़ो_delay	= srcu_पढ़ो_delay,
	.पढ़ोunlock	= srcu_torture_पढ़ो_unlock,
	.get_gp_seq	= srcu_torture_completed,
	.deferred_मुक्त	= srcu_torture_deferred_मुक्त,
	.sync		= srcu_torture_synchronize,
	.exp_sync	= srcu_torture_synchronize_expedited,
	.call		= srcu_torture_call,
	.cb_barrier	= srcu_torture_barrier,
	.stats		= srcu_torture_stats,
	.irq_capable	= 1,
	.name		= "srcud"
पूर्ण;

/* As above, but broken due to inappropriate पढ़ोer extension. */
अटल काष्ठा rcu_torture_ops busted_srcud_ops = अणु
	.ttype		= SRCU_FLAVOR,
	.init		= srcu_torture_init,
	.cleanup	= srcu_torture_cleanup,
	.पढ़ोlock	= srcu_torture_पढ़ो_lock,
	.पढ़ो_delay	= rcu_पढ़ो_delay,
	.पढ़ोunlock	= srcu_torture_पढ़ो_unlock,
	.get_gp_seq	= srcu_torture_completed,
	.deferred_मुक्त	= srcu_torture_deferred_मुक्त,
	.sync		= srcu_torture_synchronize,
	.exp_sync	= srcu_torture_synchronize_expedited,
	.call		= srcu_torture_call,
	.cb_barrier	= srcu_torture_barrier,
	.stats		= srcu_torture_stats,
	.irq_capable	= 1,
	.extendables	= RCUTORTURE_MAX_EXTEND,
	.name		= "busted_srcud"
पूर्ण;

/*
 * Definitions क्रम RCU-tasks torture testing.
 */

अटल पूर्णांक tasks_torture_पढ़ो_lock(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम tasks_torture_पढ़ो_unlock(पूर्णांक idx)
अणु
पूर्ण

अटल व्योम rcu_tasks_torture_deferred_मुक्त(काष्ठा rcu_torture *p)
अणु
	call_rcu_tasks(&p->rtort_rcu, rcu_torture_cb);
पूर्ण

अटल व्योम synchronize_rcu_mult_test(व्योम)
अणु
	synchronize_rcu_mult(call_rcu_tasks, call_rcu);
पूर्ण

अटल काष्ठा rcu_torture_ops tasks_ops = अणु
	.ttype		= RCU_TASKS_FLAVOR,
	.init		= rcu_sync_torture_init,
	.पढ़ोlock	= tasks_torture_पढ़ो_lock,
	.पढ़ो_delay	= rcu_पढ़ो_delay,  /* just reuse rcu's version. */
	.पढ़ोunlock	= tasks_torture_पढ़ो_unlock,
	.get_gp_seq	= rcu_no_completed,
	.deferred_मुक्त	= rcu_tasks_torture_deferred_मुक्त,
	.sync		= synchronize_rcu_tasks,
	.exp_sync	= synchronize_rcu_mult_test,
	.call		= call_rcu_tasks,
	.cb_barrier	= rcu_barrier_tasks,
	.gp_kthपढ़ो_dbg	= show_rcu_tasks_classic_gp_kthपढ़ो,
	.fqs		= शून्य,
	.stats		= शून्य,
	.irq_capable	= 1,
	.slow_gps	= 1,
	.name		= "tasks"
पूर्ण;

/*
 * Definitions क्रम trivial CONFIG_PREEMPT=n-only torture testing.
 * This implementation करोes not necessarily work well with CPU hotplug.
 */

अटल व्योम synchronize_rcu_trivial(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_online_cpu(cpu) अणु
		rcutorture_sched_setaffinity(current->pid, cpumask_of(cpu));
		WARN_ON_ONCE(raw_smp_processor_id() != cpu);
	पूर्ण
पूर्ण

अटल पूर्णांक rcu_torture_पढ़ो_lock_trivial(व्योम) __acquires(RCU)
अणु
	preempt_disable();
	वापस 0;
पूर्ण

अटल व्योम rcu_torture_पढ़ो_unlock_trivial(पूर्णांक idx) __releases(RCU)
अणु
	preempt_enable();
पूर्ण

अटल काष्ठा rcu_torture_ops trivial_ops = अणु
	.ttype		= RCU_TRIVIAL_FLAVOR,
	.init		= rcu_sync_torture_init,
	.पढ़ोlock	= rcu_torture_पढ़ो_lock_trivial,
	.पढ़ो_delay	= rcu_पढ़ो_delay,  /* just reuse rcu's version. */
	.पढ़ोunlock	= rcu_torture_पढ़ो_unlock_trivial,
	.get_gp_seq	= rcu_no_completed,
	.sync		= synchronize_rcu_trivial,
	.exp_sync	= synchronize_rcu_trivial,
	.fqs		= शून्य,
	.stats		= शून्य,
	.irq_capable	= 1,
	.name		= "trivial"
पूर्ण;

/*
 * Definitions क्रम rude RCU-tasks torture testing.
 */

अटल व्योम rcu_tasks_rude_torture_deferred_मुक्त(काष्ठा rcu_torture *p)
अणु
	call_rcu_tasks_rude(&p->rtort_rcu, rcu_torture_cb);
पूर्ण

अटल काष्ठा rcu_torture_ops tasks_rude_ops = अणु
	.ttype		= RCU_TASKS_RUDE_FLAVOR,
	.init		= rcu_sync_torture_init,
	.पढ़ोlock	= rcu_torture_पढ़ो_lock_trivial,
	.पढ़ो_delay	= rcu_पढ़ो_delay,  /* just reuse rcu's version. */
	.पढ़ोunlock	= rcu_torture_पढ़ो_unlock_trivial,
	.get_gp_seq	= rcu_no_completed,
	.deferred_मुक्त	= rcu_tasks_rude_torture_deferred_मुक्त,
	.sync		= synchronize_rcu_tasks_rude,
	.exp_sync	= synchronize_rcu_tasks_rude,
	.call		= call_rcu_tasks_rude,
	.cb_barrier	= rcu_barrier_tasks_rude,
	.gp_kthपढ़ो_dbg	= show_rcu_tasks_rude_gp_kthपढ़ो,
	.fqs		= शून्य,
	.stats		= शून्य,
	.irq_capable	= 1,
	.name		= "tasks-rude"
पूर्ण;

/*
 * Definitions क्रम tracing RCU-tasks torture testing.
 */

अटल पूर्णांक tasks_tracing_torture_पढ़ो_lock(व्योम)
अणु
	rcu_पढ़ो_lock_trace();
	वापस 0;
पूर्ण

अटल व्योम tasks_tracing_torture_पढ़ो_unlock(पूर्णांक idx)
अणु
	rcu_पढ़ो_unlock_trace();
पूर्ण

अटल व्योम rcu_tasks_tracing_torture_deferred_मुक्त(काष्ठा rcu_torture *p)
अणु
	call_rcu_tasks_trace(&p->rtort_rcu, rcu_torture_cb);
पूर्ण

अटल काष्ठा rcu_torture_ops tasks_tracing_ops = अणु
	.ttype		= RCU_TASKS_TRACING_FLAVOR,
	.init		= rcu_sync_torture_init,
	.पढ़ोlock	= tasks_tracing_torture_पढ़ो_lock,
	.पढ़ो_delay	= srcu_पढ़ो_delay,  /* just reuse srcu's version. */
	.पढ़ोunlock	= tasks_tracing_torture_पढ़ो_unlock,
	.get_gp_seq	= rcu_no_completed,
	.deferred_मुक्त	= rcu_tasks_tracing_torture_deferred_मुक्त,
	.sync		= synchronize_rcu_tasks_trace,
	.exp_sync	= synchronize_rcu_tasks_trace,
	.call		= call_rcu_tasks_trace,
	.cb_barrier	= rcu_barrier_tasks_trace,
	.gp_kthपढ़ो_dbg	= show_rcu_tasks_trace_gp_kthपढ़ो,
	.fqs		= शून्य,
	.stats		= शून्य,
	.irq_capable	= 1,
	.slow_gps	= 1,
	.name		= "tasks-tracing"
पूर्ण;

अटल अचिन्हित दीर्घ rcutorture_seq_dअगरf(अचिन्हित दीर्घ new, अचिन्हित दीर्घ old)
अणु
	अगर (!cur_ops->gp_dअगरf)
		वापस new - old;
	वापस cur_ops->gp_dअगरf(new, old);
पूर्ण

अटल bool __maybe_unused torturing_tasks(व्योम)
अणु
	वापस cur_ops == &tasks_ops || cur_ops == &tasks_rude_ops;
पूर्ण

/*
 * RCU torture priority-boost testing.  Runs one real-समय thपढ़ो per
 * CPU क्रम moderate bursts, repeatedly रेजिस्टरing RCU callbacks and
 * spinning रुकोing क्रम them to be invoked.  If a given callback takes
 * too दीर्घ to be invoked, we assume that priority inversion has occurred.
 */

काष्ठा rcu_boost_inflight अणु
	काष्ठा rcu_head rcu;
	पूर्णांक inflight;
पूर्ण;

अटल व्योम rcu_torture_boost_cb(काष्ठा rcu_head *head)
अणु
	काष्ठा rcu_boost_inflight *rbip =
		container_of(head, काष्ठा rcu_boost_inflight, rcu);

	/* Ensure RCU-core accesses precede clearing ->inflight */
	smp_store_release(&rbip->inflight, 0);
पूर्ण

अटल पूर्णांक old_rt_runसमय = -1;

अटल व्योम rcu_torture_disable_rt_throttle(व्योम)
अणु
	/*
	 * Disable RT throttling so that rcutorture's boost threads don't get
	 * throttled. Only possible अगर rcutorture is built-in otherwise the
	 * user should manually करो this by setting the sched_rt_period_us and
	 * sched_rt_runसमय sysctls.
	 */
	अगर (!IS_BUILTIN(CONFIG_RCU_TORTURE_TEST) || old_rt_runसमय != -1)
		वापस;

	old_rt_runसमय = sysctl_sched_rt_runसमय;
	sysctl_sched_rt_runसमय = -1;
पूर्ण

अटल व्योम rcu_torture_enable_rt_throttle(व्योम)
अणु
	अगर (!IS_BUILTIN(CONFIG_RCU_TORTURE_TEST) || old_rt_runसमय == -1)
		वापस;

	sysctl_sched_rt_runसमय = old_rt_runसमय;
	old_rt_runसमय = -1;
पूर्ण

अटल bool rcu_torture_boost_failed(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अटल पूर्णांक dbg_करोne;

	अगर (end - start > test_boost_duration * HZ - HZ / 2) अणु
		VERBOSE_TOROUT_STRING("rcu_torture_boost boosting failed");
		n_rcu_torture_boost_failure++;
		अगर (!xchg(&dbg_करोne, 1) && cur_ops->gp_kthपढ़ो_dbg)
			cur_ops->gp_kthपढ़ो_dbg();

		वापस true; /* failed */
	पूर्ण

	वापस false; /* passed */
पूर्ण

अटल पूर्णांक rcu_torture_boost(व्योम *arg)
अणु
	अचिन्हित दीर्घ call_rcu_समय;
	अचिन्हित दीर्घ endसमय;
	अचिन्हित दीर्घ oldstartसमय;
	काष्ठा rcu_boost_inflight rbi = अणु .inflight = 0 पूर्ण;

	VERBOSE_TOROUT_STRING("rcu_torture_boost started");

	/* Set real-समय priority. */
	sched_set_fअगरo_low(current);

	init_rcu_head_on_stack(&rbi.rcu);
	/* Each pass through the following loop करोes one boost-test cycle. */
	करो अणु
		bool failed = false; // Test failed alपढ़ोy in this test पूर्णांकerval
		bool firstसमय = true;

		/* Increment n_rcu_torture_boosts once per boost-test */
		जबतक (!kthपढ़ो_should_stop()) अणु
			अगर (mutex_trylock(&boost_mutex)) अणु
				n_rcu_torture_boosts++;
				mutex_unlock(&boost_mutex);
				अवरोध;
			पूर्ण
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण
		अगर (kthपढ़ो_should_stop())
			जाओ checkरुको;

		/* Wait क्रम the next test पूर्णांकerval. */
		oldstartसमय = boost_startसमय;
		जबतक (समय_beक्रमe(jअगरfies, oldstartसमय)) अणु
			schedule_समयout_पूर्णांकerruptible(oldstartसमय - jअगरfies);
			अगर (stutter_रुको("rcu_torture_boost"))
				sched_set_fअगरo_low(current);
			अगर (torture_must_stop())
				जाओ checkरुको;
		पूर्ण

		/* Do one boost-test पूर्णांकerval. */
		endसमय = oldstartसमय + test_boost_duration * HZ;
		जबतक (समय_beक्रमe(jअगरfies, endसमय)) अणु
			/* If we करोn't have a callback in flight, post one. */
			अगर (!smp_load_acquire(&rbi.inflight)) अणु
				/* RCU core beक्रमe ->inflight = 1. */
				smp_store_release(&rbi.inflight, 1);
				cur_ops->call(&rbi.rcu, rcu_torture_boost_cb);
				/* Check अगर the boost test failed */
				अगर (!firstसमय && !failed)
					failed = rcu_torture_boost_failed(call_rcu_समय, jअगरfies);
				call_rcu_समय = jअगरfies;
				firstसमय = false;
			पूर्ण
			अगर (stutter_रुको("rcu_torture_boost"))
				sched_set_fअगरo_low(current);
			अगर (torture_must_stop())
				जाओ checkरुको;
		पूर्ण

		/*
		 * If boost never happened, then inflight will always be 1, in
		 * this हाल the boost check would never happen in the above
		 * loop so करो another one here.
		 */
		अगर (!firstसमय && !failed && smp_load_acquire(&rbi.inflight))
			rcu_torture_boost_failed(call_rcu_समय, jअगरfies);

		/*
		 * Set the start समय of the next test पूर्णांकerval.
		 * Yes, this is vulnerable to दीर्घ delays, but such
		 * delays simply cause a false negative क्रम the next
		 * पूर्णांकerval.  Besides, we are running at RT priority,
		 * so delays should be relatively rare.
		 */
		जबतक (oldstartसमय == boost_startसमय &&
		       !kthपढ़ो_should_stop()) अणु
			अगर (mutex_trylock(&boost_mutex)) अणु
				boost_startसमय = jअगरfies +
						  test_boost_पूर्णांकerval * HZ;
				mutex_unlock(&boost_mutex);
				अवरोध;
			पूर्ण
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण

		/* Go करो the stutter. */
checkरुको:	अगर (stutter_रुको("rcu_torture_boost"))
			sched_set_fअगरo_low(current);
	पूर्ण जबतक (!torture_must_stop());

	जबतक (smp_load_acquire(&rbi.inflight))
		schedule_समयout_unपूर्णांकerruptible(1); // rcu_barrier() deadlocks.

	/* Clean up and निकास. */
	जबतक (!kthपढ़ो_should_stop() || smp_load_acquire(&rbi.inflight)) अणु
		torture_shutकरोwn_असलorb("rcu_torture_boost");
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण
	destroy_rcu_head_on_stack(&rbi.rcu);
	torture_kthपढ़ो_stopping("rcu_torture_boost");
	वापस 0;
पूर्ण

/*
 * RCU torture क्रमce-quiescent-state kthपढ़ो.  Repeatedly induces
 * bursts of calls to क्रमce_quiescent_state(), increasing the probability
 * of occurrence of some important types of race conditions.
 */
अटल पूर्णांक
rcu_torture_fqs(व्योम *arg)
अणु
	अचिन्हित दीर्घ fqs_resume_समय;
	पूर्णांक fqs_burst_reमुख्यing;
	पूर्णांक oldnice = task_nice(current);

	VERBOSE_TOROUT_STRING("rcu_torture_fqs task started");
	करो अणु
		fqs_resume_समय = jअगरfies + fqs_stutter * HZ;
		जबतक (समय_beक्रमe(jअगरfies, fqs_resume_समय) &&
		       !kthपढ़ो_should_stop()) अणु
			schedule_समयout_पूर्णांकerruptible(1);
		पूर्ण
		fqs_burst_reमुख्यing = fqs_duration;
		जबतक (fqs_burst_reमुख्यing > 0 &&
		       !kthपढ़ो_should_stop()) अणु
			cur_ops->fqs();
			udelay(fqs_holकरोff);
			fqs_burst_reमुख्यing -= fqs_holकरोff;
		पूर्ण
		अगर (stutter_रुको("rcu_torture_fqs"))
			sched_set_normal(current, oldnice);
	पूर्ण जबतक (!torture_must_stop());
	torture_kthपढ़ो_stopping("rcu_torture_fqs");
	वापस 0;
पूर्ण

// Used by ग_लिखोrs to अक्रमomly choose from the available grace-period
// primitives.  The only purpose of the initialization is to size the array.
अटल पूर्णांक synctype[] = अणु RTWS_DEF_FREE, RTWS_EXP_SYNC, RTWS_COND_GET, RTWS_POLL_GET, RTWS_SYNC पूर्ण;
अटल पूर्णांक nsynctypes;

/*
 * Determine which grace-period primitives are available.
 */
अटल व्योम rcu_torture_ग_लिखो_types(व्योम)
अणु
	bool gp_cond1 = gp_cond, gp_exp1 = gp_exp, gp_normal1 = gp_normal;
	bool gp_poll1 = gp_poll, gp_sync1 = gp_sync;

	/* Initialize synctype[] array.  If none set, take शेष. */
	अगर (!gp_cond1 && !gp_exp1 && !gp_normal1 && !gp_poll1 && !gp_sync1)
		gp_cond1 = gp_exp1 = gp_normal1 = gp_poll1 = gp_sync1 = true;
	अगर (gp_cond1 && cur_ops->get_gp_state && cur_ops->cond_sync) अणु
		synctype[nsynctypes++] = RTWS_COND_GET;
		pr_info("%s: Testing conditional GPs.\n", __func__);
	पूर्ण अन्यथा अगर (gp_cond && (!cur_ops->get_gp_state || !cur_ops->cond_sync)) अणु
		pr_alert("%s: gp_cond without primitives.\n", __func__);
	पूर्ण
	अगर (gp_exp1 && cur_ops->exp_sync) अणु
		synctype[nsynctypes++] = RTWS_EXP_SYNC;
		pr_info("%s: Testing expedited GPs.\n", __func__);
	पूर्ण अन्यथा अगर (gp_exp && !cur_ops->exp_sync) अणु
		pr_alert("%s: gp_exp without primitives.\n", __func__);
	पूर्ण
	अगर (gp_normal1 && cur_ops->deferred_मुक्त) अणु
		synctype[nsynctypes++] = RTWS_DEF_FREE;
		pr_info("%s: Testing asynchronous GPs.\n", __func__);
	पूर्ण अन्यथा अगर (gp_normal && !cur_ops->deferred_मुक्त) अणु
		pr_alert("%s: gp_normal without primitives.\n", __func__);
	पूर्ण
	अगर (gp_poll1 && cur_ops->start_gp_poll && cur_ops->poll_gp_state) अणु
		synctype[nsynctypes++] = RTWS_POLL_GET;
		pr_info("%s: Testing polling GPs.\n", __func__);
	पूर्ण अन्यथा अगर (gp_poll && (!cur_ops->start_gp_poll || !cur_ops->poll_gp_state)) अणु
		pr_alert("%s: gp_poll without primitives.\n", __func__);
	पूर्ण
	अगर (gp_sync1 && cur_ops->sync) अणु
		synctype[nsynctypes++] = RTWS_SYNC;
		pr_info("%s: Testing normal GPs.\n", __func__);
	पूर्ण अन्यथा अगर (gp_sync && !cur_ops->sync) अणु
		pr_alert("%s: gp_sync without primitives.\n", __func__);
	पूर्ण
पूर्ण

/*
 * RCU torture ग_लिखोr kthपढ़ो.  Repeatedly substitutes a new काष्ठाure
 * क्रम that poपूर्णांकed to by rcu_torture_current, मुक्तing the old काष्ठाure
 * after a series of grace periods (the "pipeline").
 */
अटल पूर्णांक
rcu_torture_ग_लिखोr(व्योम *arg)
अणु
	bool boot_ended;
	bool can_expedite = !rcu_gp_is_expedited() && !rcu_gp_is_normal();
	अचिन्हित दीर्घ cookie;
	पूर्णांक expediting = 0;
	अचिन्हित दीर्घ gp_snap;
	पूर्णांक i;
	पूर्णांक idx;
	पूर्णांक oldnice = task_nice(current);
	काष्ठा rcu_torture *rp;
	काष्ठा rcu_torture *old_rp;
	अटल DEFINE_TORTURE_RANDOM(अक्रम);
	bool stutter_रुकोed;

	VERBOSE_TOROUT_STRING("rcu_torture_writer task started");
	अगर (!can_expedite)
		pr_alert("%s" TORTURE_FLAG
			 " GP expediting controlled from boot/sysfs for %s.\n",
			 torture_type, cur_ops->name);
	अगर (WARN_ONCE(nsynctypes == 0,
		      "rcu_torture_writer: No update-side primitives.\n")) अणु
		/*
		 * No updates primitives, so करोn't try updating.
		 * The resulting test won't be testing much, hence the
		 * above WARN_ONCE().
		 */
		rcu_torture_ग_लिखोr_state = RTWS_STOPPING;
		torture_kthपढ़ो_stopping("rcu_torture_writer");
	पूर्ण

	करो अणु
		rcu_torture_ग_लिखोr_state = RTWS_FIXED_DELAY;
		torture_hrसमयout_us(500, 1000, &अक्रम);
		rp = rcu_torture_alloc();
		अगर (rp == शून्य)
			जारी;
		rp->rtort_pipe_count = 0;
		rcu_torture_ग_लिखोr_state = RTWS_DELAY;
		udelay(torture_अक्रमom(&अक्रम) & 0x3ff);
		rcu_torture_ग_लिखोr_state = RTWS_REPLACE;
		old_rp = rcu_dereference_check(rcu_torture_current,
					       current == ग_लिखोr_task);
		rp->rtort_mbtest = 1;
		rcu_assign_poपूर्णांकer(rcu_torture_current, rp);
		smp_wmb(); /* Mods to old_rp must follow rcu_assign_poपूर्णांकer() */
		अगर (old_rp) अणु
			i = old_rp->rtort_pipe_count;
			अगर (i > RCU_TORTURE_PIPE_LEN)
				i = RCU_TORTURE_PIPE_LEN;
			atomic_inc(&rcu_torture_wcount[i]);
			WRITE_ONCE(old_rp->rtort_pipe_count,
				   old_rp->rtort_pipe_count + 1);
			अगर (cur_ops->get_gp_state && cur_ops->poll_gp_state) अणु
				idx = cur_ops->पढ़ोlock();
				cookie = cur_ops->get_gp_state();
				WARN_ONCE(rcu_torture_ग_लिखोr_state != RTWS_DEF_FREE &&
					  cur_ops->poll_gp_state(cookie),
					  "%s: Cookie check 1 failed %s(%d) %lu->%lu\n",
					  __func__,
					  rcu_torture_ग_लिखोr_state_getname(),
					  rcu_torture_ग_लिखोr_state,
					  cookie, cur_ops->get_gp_state());
				cur_ops->पढ़ोunlock(idx);
			पूर्ण
			चयन (synctype[torture_अक्रमom(&अक्रम) % nsynctypes]) अणु
			हाल RTWS_DEF_FREE:
				rcu_torture_ग_लिखोr_state = RTWS_DEF_FREE;
				cur_ops->deferred_मुक्त(old_rp);
				अवरोध;
			हाल RTWS_EXP_SYNC:
				rcu_torture_ग_लिखोr_state = RTWS_EXP_SYNC;
				cur_ops->exp_sync();
				rcu_torture_pipe_update(old_rp);
				अवरोध;
			हाल RTWS_COND_GET:
				rcu_torture_ग_लिखोr_state = RTWS_COND_GET;
				gp_snap = cur_ops->get_gp_state();
				torture_hrसमयout_jअगरfies(torture_अक्रमom(&अक्रम) % 16, &अक्रम);
				rcu_torture_ग_लिखोr_state = RTWS_COND_SYNC;
				cur_ops->cond_sync(gp_snap);
				rcu_torture_pipe_update(old_rp);
				अवरोध;
			हाल RTWS_POLL_GET:
				rcu_torture_ग_लिखोr_state = RTWS_POLL_GET;
				gp_snap = cur_ops->start_gp_poll();
				rcu_torture_ग_लिखोr_state = RTWS_POLL_WAIT;
				जबतक (!cur_ops->poll_gp_state(gp_snap))
					torture_hrसमयout_jअगरfies(torture_अक्रमom(&अक्रम) % 16,
								  &अक्रम);
				rcu_torture_pipe_update(old_rp);
				अवरोध;
			हाल RTWS_SYNC:
				rcu_torture_ग_लिखोr_state = RTWS_SYNC;
				cur_ops->sync();
				rcu_torture_pipe_update(old_rp);
				अवरोध;
			शेष:
				WARN_ON_ONCE(1);
				अवरोध;
			पूर्ण
		पूर्ण
		WRITE_ONCE(rcu_torture_current_version,
			   rcu_torture_current_version + 1);
		/* Cycle through nesting levels of rcu_expedite_gp() calls. */
		अगर (can_expedite &&
		    !(torture_अक्रमom(&अक्रम) & 0xff & (!!expediting - 1))) अणु
			WARN_ON_ONCE(expediting == 0 && rcu_gp_is_expedited());
			अगर (expediting >= 0)
				rcu_expedite_gp();
			अन्यथा
				rcu_unexpedite_gp();
			अगर (++expediting > 3)
				expediting = -expediting;
		पूर्ण अन्यथा अगर (!can_expedite) अणु /* Disabled during boot, recheck. */
			can_expedite = !rcu_gp_is_expedited() &&
				       !rcu_gp_is_normal();
		पूर्ण
		rcu_torture_ग_लिखोr_state = RTWS_STUTTER;
		boot_ended = rcu_inkernel_boot_has_ended();
		stutter_रुकोed = stutter_रुको("rcu_torture_writer");
		अगर (stutter_रुकोed &&
		    !READ_ONCE(rcu_fwd_cb_nodelay) &&
		    !cur_ops->slow_gps &&
		    !torture_must_stop() &&
		    boot_ended)
			क्रम (i = 0; i < ARRAY_SIZE(rcu_tortures); i++)
				अगर (list_empty(&rcu_tortures[i].rtort_मुक्त) &&
				    rcu_access_poपूर्णांकer(rcu_torture_current) !=
				    &rcu_tortures[i]) अणु
					rcu_ftrace_dump(DUMP_ALL);
					WARN(1, "%s: rtort_pipe_count: %d\n", __func__, rcu_tortures[i].rtort_pipe_count);
				पूर्ण
		अगर (stutter_रुकोed)
			sched_set_normal(current, oldnice);
	पूर्ण जबतक (!torture_must_stop());
	rcu_torture_current = शून्य;  // Let stats task know that we are करोne.
	/* Reset expediting back to unexpedited. */
	अगर (expediting > 0)
		expediting = -expediting;
	जबतक (can_expedite && expediting++ < 0)
		rcu_unexpedite_gp();
	WARN_ON_ONCE(can_expedite && rcu_gp_is_expedited());
	अगर (!can_expedite)
		pr_alert("%s" TORTURE_FLAG
			 " Dynamic grace-period expediting was disabled.\n",
			 torture_type);
	rcu_torture_ग_लिखोr_state = RTWS_STOPPING;
	torture_kthपढ़ो_stopping("rcu_torture_writer");
	वापस 0;
पूर्ण

/*
 * RCU torture fake ग_लिखोr kthपढ़ो.  Repeatedly calls sync, with a अक्रमom
 * delay between calls.
 */
अटल पूर्णांक
rcu_torture_fakeग_लिखोr(व्योम *arg)
अणु
	अचिन्हित दीर्घ gp_snap;
	DEFINE_TORTURE_RANDOM(अक्रम);

	VERBOSE_TOROUT_STRING("rcu_torture_fakewriter task started");
	set_user_nice(current, MAX_NICE);

	करो अणु
		torture_hrसमयout_jअगरfies(torture_अक्रमom(&अक्रम) % 10, &अक्रम);
		अगर (cur_ops->cb_barrier != शून्य &&
		    torture_अक्रमom(&अक्रम) % (nfakeग_लिखोrs * 8) == 0) अणु
			cur_ops->cb_barrier();
		पूर्ण अन्यथा अणु
			चयन (synctype[torture_अक्रमom(&अक्रम) % nsynctypes]) अणु
			हाल RTWS_DEF_FREE:
				अवरोध;
			हाल RTWS_EXP_SYNC:
				cur_ops->exp_sync();
				अवरोध;
			हाल RTWS_COND_GET:
				gp_snap = cur_ops->get_gp_state();
				torture_hrसमयout_jअगरfies(torture_अक्रमom(&अक्रम) % 16, &अक्रम);
				cur_ops->cond_sync(gp_snap);
				अवरोध;
			हाल RTWS_POLL_GET:
				gp_snap = cur_ops->start_gp_poll();
				जबतक (!cur_ops->poll_gp_state(gp_snap)) अणु
					torture_hrसमयout_jअगरfies(torture_अक्रमom(&अक्रम) % 16,
								  &अक्रम);
				पूर्ण
				अवरोध;
			हाल RTWS_SYNC:
				cur_ops->sync();
				अवरोध;
			शेष:
				WARN_ON_ONCE(1);
				अवरोध;
			पूर्ण
		पूर्ण
		stutter_रुको("rcu_torture_fakewriter");
	पूर्ण जबतक (!torture_must_stop());

	torture_kthपढ़ो_stopping("rcu_torture_fakewriter");
	वापस 0;
पूर्ण

अटल व्योम rcu_torture_समयr_cb(काष्ठा rcu_head *rhp)
अणु
	kमुक्त(rhp);
पूर्ण

// Set up and carry out testing of RCU's global memory ordering
अटल व्योम rcu_torture_पढ़ोer_करो_mbchk(दीर्घ myid, काष्ठा rcu_torture *rtp,
					काष्ठा torture_अक्रमom_state *trsp)
अणु
	अचिन्हित दीर्घ loops;
	पूर्णांक noc = torture_num_online_cpus();
	पूर्णांक rdrchked;
	पूर्णांक rdrchker;
	काष्ठा rcu_torture_पढ़ोer_check *rtrcp; // Me.
	काष्ठा rcu_torture_पढ़ोer_check *rtrcp_assigner; // Asचिन्हित us to करो checking.
	काष्ठा rcu_torture_पढ़ोer_check *rtrcp_chked; // Reader being checked.
	काष्ठा rcu_torture_पढ़ोer_check *rtrcp_chker; // Reader करोing checking when not me.

	अगर (myid < 0)
		वापस; // Don't try this from समयr handlers.

	// Increment my counter.
	rtrcp = &rcu_torture_पढ़ोer_mbchk[myid];
	WRITE_ONCE(rtrcp->rtc_myloops, rtrcp->rtc_myloops + 1);

	// Attempt to assign someone अन्यथा some checking work.
	rdrchked = torture_अक्रमom(trsp) % nrealपढ़ोers;
	rtrcp_chked = &rcu_torture_पढ़ोer_mbchk[rdrchked];
	rdrchker = torture_अक्रमom(trsp) % nrealपढ़ोers;
	rtrcp_chker = &rcu_torture_पढ़ोer_mbchk[rdrchker];
	अगर (rdrchked != myid && rdrchked != rdrchker && noc >= rdrchked && noc >= rdrchker &&
	    smp_load_acquire(&rtrcp->rtc_chkrdr) < 0 && // Pairs with smp_store_release below.
	    !READ_ONCE(rtp->rtort_chkp) &&
	    !smp_load_acquire(&rtrcp_chker->rtc_assigner)) अणु // Pairs with smp_store_release below.
		rtrcp->rtc_chkloops = READ_ONCE(rtrcp_chked->rtc_myloops);
		WARN_ON_ONCE(rtrcp->rtc_chkrdr >= 0);
		rtrcp->rtc_chkrdr = rdrchked;
		WARN_ON_ONCE(rtrcp->rtc_पढ़ोy); // This माला_लो set after the grace period ends.
		अगर (cmpxchg_relaxed(&rtrcp_chker->rtc_assigner, शून्य, rtrcp) ||
		    cmpxchg_relaxed(&rtp->rtort_chkp, शून्य, rtrcp))
			(व्योम)cmpxchg_relaxed(&rtrcp_chker->rtc_assigner, rtrcp, शून्य); // Back out.
	पूर्ण

	// If asचिन्हित some completed work, करो it!
	rtrcp_assigner = READ_ONCE(rtrcp->rtc_assigner);
	अगर (!rtrcp_assigner || !smp_load_acquire(&rtrcp_assigner->rtc_पढ़ोy))
		वापस; // No work or work not yet पढ़ोy.
	rdrchked = rtrcp_assigner->rtc_chkrdr;
	अगर (WARN_ON_ONCE(rdrchked < 0))
		वापस;
	rtrcp_chked = &rcu_torture_पढ़ोer_mbchk[rdrchked];
	loops = READ_ONCE(rtrcp_chked->rtc_myloops);
	atomic_inc(&n_rcu_torture_mbchk_tries);
	अगर (ULONG_CMP_LT(loops, rtrcp_assigner->rtc_chkloops))
		atomic_inc(&n_rcu_torture_mbchk_fail);
	rtrcp_assigner->rtc_chkloops = loops + अच_दीर्घ_उच्च / 2;
	rtrcp_assigner->rtc_पढ़ोy = 0;
	smp_store_release(&rtrcp->rtc_assigner, शून्य); // Someone अन्यथा can assign us work.
	smp_store_release(&rtrcp_assigner->rtc_chkrdr, -1); // Assigner can again assign.
पूर्ण

/*
 * Do one extension of an RCU पढ़ो-side critical section using the
 * current पढ़ोer state in पढ़ोstate (set to zero क्रम initial entry
 * to extended critical section), set the new state as specअगरied by
 * newstate (set to zero क्रम final निकास from extended critical section),
 * and अक्रमom-number-generator state in trsp.  If this is neither the
 * beginning or end of the critical section and अगर there was actually a
 * change, करो a ->पढ़ो_delay().
 */
अटल व्योम rcutorture_one_extend(पूर्णांक *पढ़ोstate, पूर्णांक newstate,
				  काष्ठा torture_अक्रमom_state *trsp,
				  काष्ठा rt_पढ़ो_seg *rtrsp)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक idxnew = -1;
	पूर्णांक idxold = *पढ़ोstate;
	पूर्णांक statesnew = ~*पढ़ोstate & newstate;
	पूर्णांक statesold = *पढ़ोstate & ~newstate;

	WARN_ON_ONCE(idxold < 0);
	WARN_ON_ONCE((idxold >> RCUTORTURE_RDR_SHIFT) > 1);
	rtrsp->rt_पढ़ोstate = newstate;

	/* First, put new protection in place to aव्योम critical-section gap. */
	अगर (statesnew & RCUTORTURE_RDR_BH)
		local_bh_disable();
	अगर (statesnew & RCUTORTURE_RDR_IRQ)
		local_irq_disable();
	अगर (statesnew & RCUTORTURE_RDR_PREEMPT)
		preempt_disable();
	अगर (statesnew & RCUTORTURE_RDR_RBH)
		rcu_पढ़ो_lock_bh();
	अगर (statesnew & RCUTORTURE_RDR_SCHED)
		rcu_पढ़ो_lock_sched();
	अगर (statesnew & RCUTORTURE_RDR_RCU)
		idxnew = cur_ops->पढ़ोlock() << RCUTORTURE_RDR_SHIFT;

	/* Next, हटाओ old protection, irq first due to bh conflict. */
	अगर (statesold & RCUTORTURE_RDR_IRQ)
		local_irq_enable();
	अगर (statesold & RCUTORTURE_RDR_BH)
		local_bh_enable();
	अगर (statesold & RCUTORTURE_RDR_PREEMPT)
		preempt_enable();
	अगर (statesold & RCUTORTURE_RDR_RBH)
		rcu_पढ़ो_unlock_bh();
	अगर (statesold & RCUTORTURE_RDR_SCHED)
		rcu_पढ़ो_unlock_sched();
	अगर (statesold & RCUTORTURE_RDR_RCU) अणु
		bool lockit = !statesnew && !(torture_अक्रमom(trsp) & 0xffff);

		अगर (lockit)
			raw_spin_lock_irqsave(&current->pi_lock, flags);
		cur_ops->पढ़ोunlock(idxold >> RCUTORTURE_RDR_SHIFT);
		अगर (lockit)
			raw_spin_unlock_irqrestore(&current->pi_lock, flags);
	पूर्ण

	/* Delay अगर neither beginning nor end and there was a change. */
	अगर ((statesnew || statesold) && *पढ़ोstate && newstate)
		cur_ops->पढ़ो_delay(trsp, rtrsp);

	/* Update the पढ़ोer state. */
	अगर (idxnew == -1)
		idxnew = idxold & ~RCUTORTURE_RDR_MASK;
	WARN_ON_ONCE(idxnew < 0);
	WARN_ON_ONCE((idxnew >> RCUTORTURE_RDR_SHIFT) > 1);
	*पढ़ोstate = idxnew | newstate;
	WARN_ON_ONCE((*पढ़ोstate >> RCUTORTURE_RDR_SHIFT) < 0);
	WARN_ON_ONCE((*पढ़ोstate >> RCUTORTURE_RDR_SHIFT) > 1);
पूर्ण

/* Return the biggest extendables mask given current RCU and boot parameters. */
अटल पूर्णांक rcutorture_extend_mask_max(व्योम)
अणु
	पूर्णांक mask;

	WARN_ON_ONCE(extendables & ~RCUTORTURE_MAX_EXTEND);
	mask = extendables & RCUTORTURE_MAX_EXTEND & cur_ops->extendables;
	mask = mask | RCUTORTURE_RDR_RCU;
	वापस mask;
पूर्ण

/* Return a अक्रमom protection state mask, but with at least one bit set. */
अटल पूर्णांक
rcutorture_extend_mask(पूर्णांक oldmask, काष्ठा torture_अक्रमom_state *trsp)
अणु
	पूर्णांक mask = rcutorture_extend_mask_max();
	अचिन्हित दीर्घ अक्रमmask1 = torture_अक्रमom(trsp) >> 8;
	अचिन्हित दीर्घ अक्रमmask2 = अक्रमmask1 >> 3;

	WARN_ON_ONCE(mask >> RCUTORTURE_RDR_SHIFT);
	/* Mostly only one bit (need preemption!), someबार lots of bits. */
	अगर (!(अक्रमmask1 & 0x7))
		mask = mask & अक्रमmask2;
	अन्यथा
		mask = mask & (1 << (अक्रमmask2 % RCUTORTURE_RDR_NBITS));
	/* Can't enable bh w/irq disabled. */
	अगर ((mask & RCUTORTURE_RDR_IRQ) &&
	    ((!(mask & RCUTORTURE_RDR_BH) && (oldmask & RCUTORTURE_RDR_BH)) ||
	     (!(mask & RCUTORTURE_RDR_RBH) && (oldmask & RCUTORTURE_RDR_RBH))))
		mask |= RCUTORTURE_RDR_BH | RCUTORTURE_RDR_RBH;
	वापस mask ?: RCUTORTURE_RDR_RCU;
पूर्ण

/*
 * Do a अक्रमomly selected number of extensions of an existing RCU पढ़ो-side
 * critical section.
 */
अटल काष्ठा rt_पढ़ो_seg *
rcutorture_loop_extend(पूर्णांक *पढ़ोstate, काष्ठा torture_अक्रमom_state *trsp,
		       काष्ठा rt_पढ़ो_seg *rtrsp)
अणु
	पूर्णांक i;
	पूर्णांक j;
	पूर्णांक mask = rcutorture_extend_mask_max();

	WARN_ON_ONCE(!*पढ़ोstate); /* -Existing- RCU पढ़ो-side critsect! */
	अगर (!((mask - 1) & mask))
		वापस rtrsp;  /* Current RCU पढ़ोer not extendable. */
	/* Bias towards larger numbers of loops. */
	i = (torture_अक्रमom(trsp) >> 3);
	i = ((i | (i >> 3)) & RCUTORTURE_RDR_MAX_LOOPS) + 1;
	क्रम (j = 0; j < i; j++) अणु
		mask = rcutorture_extend_mask(*पढ़ोstate, trsp);
		rcutorture_one_extend(पढ़ोstate, mask, trsp, &rtrsp[j]);
	पूर्ण
	वापस &rtrsp[j];
पूर्ण

/*
 * Do one पढ़ो-side critical section, वापसing false अगर there was
 * no data to पढ़ो.  Can be invoked both from process context and
 * from a समयr handler.
 */
अटल bool rcu_torture_one_पढ़ो(काष्ठा torture_अक्रमom_state *trsp, दीर्घ myid)
अणु
	अचिन्हित दीर्घ cookie;
	पूर्णांक i;
	अचिन्हित दीर्घ started;
	अचिन्हित दीर्घ completed;
	पूर्णांक newstate;
	काष्ठा rcu_torture *p;
	पूर्णांक pipe_count;
	पूर्णांक पढ़ोstate = 0;
	काष्ठा rt_पढ़ो_seg rtseg[RCUTORTURE_RDR_MAX_SEGS] = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा rt_पढ़ो_seg *rtrsp = &rtseg[0];
	काष्ठा rt_पढ़ो_seg *rtrsp1;
	अचिन्हित दीर्घ दीर्घ ts;

	WARN_ON_ONCE(!rcu_is_watching());
	newstate = rcutorture_extend_mask(पढ़ोstate, trsp);
	rcutorture_one_extend(&पढ़ोstate, newstate, trsp, rtrsp++);
	अगर (cur_ops->get_gp_state && cur_ops->poll_gp_state)
		cookie = cur_ops->get_gp_state();
	started = cur_ops->get_gp_seq();
	ts = rcu_trace_घड़ी_local();
	p = rcu_dereference_check(rcu_torture_current,
				  rcu_पढ़ो_lock_bh_held() ||
				  rcu_पढ़ो_lock_sched_held() ||
				  srcu_पढ़ो_lock_held(srcu_ctlp) ||
				  rcu_पढ़ो_lock_trace_held() ||
				  torturing_tasks());
	अगर (p == शून्य) अणु
		/* Wait क्रम rcu_torture_ग_लिखोr to get underway */
		rcutorture_one_extend(&पढ़ोstate, 0, trsp, rtrsp);
		वापस false;
	पूर्ण
	अगर (p->rtort_mbtest == 0)
		atomic_inc(&n_rcu_torture_mberror);
	rcu_torture_पढ़ोer_करो_mbchk(myid, p, trsp);
	rtrsp = rcutorture_loop_extend(&पढ़ोstate, trsp, rtrsp);
	preempt_disable();
	pipe_count = READ_ONCE(p->rtort_pipe_count);
	अगर (pipe_count > RCU_TORTURE_PIPE_LEN) अणु
		/* Should not happen, but... */
		pipe_count = RCU_TORTURE_PIPE_LEN;
	पूर्ण
	completed = cur_ops->get_gp_seq();
	अगर (pipe_count > 1) अणु
		करो_trace_rcu_torture_पढ़ो(cur_ops->name, &p->rtort_rcu,
					  ts, started, completed);
		rcu_ftrace_dump(DUMP_ALL);
	पूर्ण
	__this_cpu_inc(rcu_torture_count[pipe_count]);
	completed = rcutorture_seq_dअगरf(completed, started);
	अगर (completed > RCU_TORTURE_PIPE_LEN) अणु
		/* Should not happen, but... */
		completed = RCU_TORTURE_PIPE_LEN;
	पूर्ण
	__this_cpu_inc(rcu_torture_batch[completed]);
	preempt_enable();
	अगर (cur_ops->get_gp_state && cur_ops->poll_gp_state)
		WARN_ONCE(cur_ops->poll_gp_state(cookie),
			  "%s: Cookie check 2 failed %s(%d) %lu->%lu\n",
			  __func__,
			  rcu_torture_ग_लिखोr_state_getname(),
			  rcu_torture_ग_लिखोr_state,
			  cookie, cur_ops->get_gp_state());
	rcutorture_one_extend(&पढ़ोstate, 0, trsp, rtrsp);
	WARN_ON_ONCE(पढ़ोstate & RCUTORTURE_RDR_MASK);
	// This next splat is expected behavior अगर leakpoपूर्णांकer, especially
	// क्रम CONFIG_RCU_STRICT_GRACE_PERIOD=y kernels.
	WARN_ON_ONCE(leakpoपूर्णांकer && READ_ONCE(p->rtort_pipe_count) > 1);

	/* If error or बंद call, record the sequence of पढ़ोer protections. */
	अगर ((pipe_count > 1 || completed > 1) && !xchg(&err_segs_recorded, 1)) अणु
		i = 0;
		क्रम (rtrsp1 = &rtseg[0]; rtrsp1 < rtrsp; rtrsp1++)
			err_segs[i++] = *rtrsp1;
		rt_पढ़ो_nsegs = i;
	पूर्ण

	वापस true;
पूर्ण

अटल DEFINE_TORTURE_RANDOM_PERCPU(rcu_torture_समयr_अक्रम);

/*
 * RCU torture पढ़ोer from समयr handler.  Dereferences rcu_torture_current,
 * incrementing the corresponding element of the pipeline array.  The
 * counter in the element should never be greater than 1, otherwise, the
 * RCU implementation is broken.
 */
अटल व्योम rcu_torture_समयr(काष्ठा समयr_list *unused)
अणु
	atomic_दीर्घ_inc(&n_rcu_torture_समयrs);
	(व्योम)rcu_torture_one_पढ़ो(this_cpu_ptr(&rcu_torture_समयr_अक्रम), -1);

	/* Test call_rcu() invocation from पूर्णांकerrupt handler. */
	अगर (cur_ops->call) अणु
		काष्ठा rcu_head *rhp = kदो_स्मृति(माप(*rhp), GFP_NOWAIT);

		अगर (rhp)
			cur_ops->call(rhp, rcu_torture_समयr_cb);
	पूर्ण
पूर्ण

/*
 * RCU torture पढ़ोer kthपढ़ो.  Repeatedly dereferences rcu_torture_current,
 * incrementing the corresponding element of the pipeline array.  The
 * counter in the element should never be greater than 1, otherwise, the
 * RCU implementation is broken.
 */
अटल पूर्णांक
rcu_torture_पढ़ोer(व्योम *arg)
अणु
	अचिन्हित दीर्घ lastsleep = jअगरfies;
	दीर्घ myid = (दीर्घ)arg;
	पूर्णांक mynumonline = myid;
	DEFINE_TORTURE_RANDOM(अक्रम);
	काष्ठा समयr_list t;

	VERBOSE_TOROUT_STRING("rcu_torture_reader task started");
	set_user_nice(current, MAX_NICE);
	अगर (irqपढ़ोer && cur_ops->irq_capable)
		समयr_setup_on_stack(&t, rcu_torture_समयr, 0);
	tick_dep_set_task(current, TICK_DEP_BIT_RCU);
	करो अणु
		अगर (irqपढ़ोer && cur_ops->irq_capable) अणु
			अगर (!समयr_pending(&t))
				mod_समयr(&t, jअगरfies + 1);
		पूर्ण
		अगर (!rcu_torture_one_पढ़ो(&अक्रम, myid) && !torture_must_stop())
			schedule_समयout_पूर्णांकerruptible(HZ);
		अगर (समय_after(jअगरfies, lastsleep) && !torture_must_stop()) अणु
			torture_hrसमयout_us(500, 1000, &अक्रम);
			lastsleep = jअगरfies + 10;
		पूर्ण
		जबतक (torture_num_online_cpus() < mynumonline && !torture_must_stop())
			schedule_समयout_पूर्णांकerruptible(HZ / 5);
		stutter_रुको("rcu_torture_reader");
	पूर्ण जबतक (!torture_must_stop());
	अगर (irqपढ़ोer && cur_ops->irq_capable) अणु
		del_समयr_sync(&t);
		destroy_समयr_on_stack(&t);
	पूर्ण
	tick_dep_clear_task(current, TICK_DEP_BIT_RCU);
	torture_kthपढ़ो_stopping("rcu_torture_reader");
	वापस 0;
पूर्ण

/*
 * Ranकरोmly Toggle CPUs' callback-offload state.  This uses hrसमयrs to
 * increase race probabilities and fuzzes the पूर्णांकerval between toggling.
 */
अटल पूर्णांक rcu_nocb_toggle(व्योम *arg)
अणु
	पूर्णांक cpu;
	पूर्णांक maxcpu = -1;
	पूर्णांक oldnice = task_nice(current);
	दीर्घ r;
	DEFINE_TORTURE_RANDOM(अक्रम);
	kसमय_प्रकार toggle_delay;
	अचिन्हित दीर्घ toggle_fuzz;
	kसमय_प्रकार toggle_पूर्णांकerval = ms_to_kसमय(nocbs_toggle);

	VERBOSE_TOROUT_STRING("rcu_nocb_toggle task started");
	जबतक (!rcu_inkernel_boot_has_ended())
		schedule_समयout_पूर्णांकerruptible(HZ / 10);
	क्रम_each_online_cpu(cpu)
		maxcpu = cpu;
	WARN_ON(maxcpu < 0);
	अगर (toggle_पूर्णांकerval > अच_दीर्घ_उच्च)
		toggle_fuzz = अच_दीर्घ_उच्च >> 3;
	अन्यथा
		toggle_fuzz = toggle_पूर्णांकerval >> 3;
	अगर (toggle_fuzz <= 0)
		toggle_fuzz = NSEC_PER_USEC;
	करो अणु
		r = torture_अक्रमom(&अक्रम);
		cpu = (r >> 4) % (maxcpu + 1);
		अगर (r & 0x1) अणु
			rcu_nocb_cpu_offload(cpu);
			atomic_दीर्घ_inc(&n_nocb_offload);
		पूर्ण अन्यथा अणु
			rcu_nocb_cpu_deoffload(cpu);
			atomic_दीर्घ_inc(&n_nocb_deoffload);
		पूर्ण
		toggle_delay = torture_अक्रमom(&अक्रम) % toggle_fuzz + toggle_पूर्णांकerval;
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_hrसमयout(&toggle_delay, HRTIMER_MODE_REL);
		अगर (stutter_रुको("rcu_nocb_toggle"))
			sched_set_normal(current, oldnice);
	पूर्ण जबतक (!torture_must_stop());
	torture_kthपढ़ो_stopping("rcu_nocb_toggle");
	वापस 0;
पूर्ण

/*
 * Prपूर्णांक torture statistics.  Caller must ensure that there is only
 * one call to this function at a given समय!!!  This is normally
 * accomplished by relying on the module प्रणाली to only have one copy
 * of the module loaded, and then by giving the rcu_torture_stats
 * kthपढ़ो full control (or the init/cleanup functions when rcu_torture_stats
 * thपढ़ो is not running).
 */
अटल व्योम
rcu_torture_stats_prपूर्णांक(व्योम)
अणु
	पूर्णांक cpu;
	पूर्णांक i;
	दीर्घ pipesummary[RCU_TORTURE_PIPE_LEN + 1] = अणु 0 पूर्ण;
	दीर्घ batchsummary[RCU_TORTURE_PIPE_LEN + 1] = अणु 0 पूर्ण;
	काष्ठा rcu_torture *rtcp;
	अटल अचिन्हित दीर्घ rtcv_snap = अच_दीर्घ_उच्च;
	अटल bool splatted;
	काष्ठा task_काष्ठा *wtp;

	क्रम_each_possible_cpu(cpu) अणु
		क्रम (i = 0; i < RCU_TORTURE_PIPE_LEN + 1; i++) अणु
			pipesummary[i] += READ_ONCE(per_cpu(rcu_torture_count, cpu)[i]);
			batchsummary[i] += READ_ONCE(per_cpu(rcu_torture_batch, cpu)[i]);
		पूर्ण
	पूर्ण
	क्रम (i = RCU_TORTURE_PIPE_LEN - 1; i >= 0; i--) अणु
		अगर (pipesummary[i] != 0)
			अवरोध;
	पूर्ण

	pr_alert("%s%s ", torture_type, TORTURE_FLAG);
	rtcp = rcu_access_poपूर्णांकer(rcu_torture_current);
	pr_cont("rtc: %p %s: %lu tfle: %d rta: %d rtaf: %d rtf: %d ",
		rtcp,
		rtcp && !rcu_stall_is_suppressed_at_boot() ? "ver" : "VER",
		rcu_torture_current_version,
		list_empty(&rcu_torture_मुक्तlist),
		atomic_पढ़ो(&n_rcu_torture_alloc),
		atomic_पढ़ो(&n_rcu_torture_alloc_fail),
		atomic_पढ़ो(&n_rcu_torture_मुक्त));
	pr_cont("rtmbe: %d rtmbkf: %d/%d rtbe: %ld rtbke: %ld rtbre: %ld ",
		atomic_पढ़ो(&n_rcu_torture_mberror),
		atomic_पढ़ो(&n_rcu_torture_mbchk_fail), atomic_पढ़ो(&n_rcu_torture_mbchk_tries),
		n_rcu_torture_barrier_error,
		n_rcu_torture_boost_ktrerror,
		n_rcu_torture_boost_rterror);
	pr_cont("rtbf: %ld rtb: %ld nt: %ld ",
		n_rcu_torture_boost_failure,
		n_rcu_torture_boosts,
		atomic_दीर्घ_पढ़ो(&n_rcu_torture_समयrs));
	torture_onoff_stats();
	pr_cont("barrier: %ld/%ld:%ld ",
		data_race(n_barrier_successes),
		data_race(n_barrier_attempts),
		data_race(n_rcu_torture_barrier_error));
	pr_cont("read-exits: %ld ", data_race(n_पढ़ो_निकासs)); // Statistic.
	pr_cont("nocb-toggles: %ld:%ld\n",
		atomic_दीर्घ_पढ़ो(&n_nocb_offload), atomic_दीर्घ_पढ़ो(&n_nocb_deoffload));

	pr_alert("%s%s ", torture_type, TORTURE_FLAG);
	अगर (atomic_पढ़ो(&n_rcu_torture_mberror) ||
	    atomic_पढ़ो(&n_rcu_torture_mbchk_fail) ||
	    n_rcu_torture_barrier_error || n_rcu_torture_boost_ktrerror ||
	    n_rcu_torture_boost_rterror || n_rcu_torture_boost_failure ||
	    i > 1) अणु
		pr_cont("%s", "!!! ");
		atomic_inc(&n_rcu_torture_error);
		WARN_ON_ONCE(atomic_पढ़ो(&n_rcu_torture_mberror));
		WARN_ON_ONCE(atomic_पढ़ो(&n_rcu_torture_mbchk_fail));
		WARN_ON_ONCE(n_rcu_torture_barrier_error);  // rcu_barrier()
		WARN_ON_ONCE(n_rcu_torture_boost_ktrerror); // no boost kthपढ़ो
		WARN_ON_ONCE(n_rcu_torture_boost_rterror); // can't set RT prio
		WARN_ON_ONCE(n_rcu_torture_boost_failure); // boost failed (TIMER_SOFTIRQ RT prio?)
		WARN_ON_ONCE(i > 1); // Too-लघु grace period
	पूर्ण
	pr_cont("Reader Pipe: ");
	क्रम (i = 0; i < RCU_TORTURE_PIPE_LEN + 1; i++)
		pr_cont(" %ld", pipesummary[i]);
	pr_cont("\n");

	pr_alert("%s%s ", torture_type, TORTURE_FLAG);
	pr_cont("Reader Batch: ");
	क्रम (i = 0; i < RCU_TORTURE_PIPE_LEN + 1; i++)
		pr_cont(" %ld", batchsummary[i]);
	pr_cont("\n");

	pr_alert("%s%s ", torture_type, TORTURE_FLAG);
	pr_cont("Free-Block Circulation: ");
	क्रम (i = 0; i < RCU_TORTURE_PIPE_LEN + 1; i++) अणु
		pr_cont(" %d", atomic_पढ़ो(&rcu_torture_wcount[i]));
	पूर्ण
	pr_cont("\n");

	अगर (cur_ops->stats)
		cur_ops->stats();
	अगर (rtcv_snap == rcu_torture_current_version &&
	    rcu_access_poपूर्णांकer(rcu_torture_current) &&
	    !rcu_stall_is_suppressed()) अणु
		पूर्णांक __maybe_unused flags = 0;
		अचिन्हित दीर्घ __maybe_unused gp_seq = 0;

		rcutorture_get_gp_data(cur_ops->ttype,
				       &flags, &gp_seq);
		srcutorture_get_gp_data(cur_ops->ttype, srcu_ctlp,
					&flags, &gp_seq);
		wtp = READ_ONCE(ग_लिखोr_task);
		pr_alert("??? Writer stall state %s(%d) g%lu f%#x ->state %#lx cpu %d\n",
			 rcu_torture_ग_लिखोr_state_getname(),
			 rcu_torture_ग_लिखोr_state, gp_seq, flags,
			 wtp == शून्य ? ~0UL : wtp->state,
			 wtp == शून्य ? -1 : (पूर्णांक)task_cpu(wtp));
		अगर (!splatted && wtp) अणु
			sched_show_task(wtp);
			splatted = true;
		पूर्ण
		अगर (cur_ops->gp_kthपढ़ो_dbg)
			cur_ops->gp_kthपढ़ो_dbg();
		rcu_ftrace_dump(DUMP_ALL);
	पूर्ण
	rtcv_snap = rcu_torture_current_version;
पूर्ण

/*
 * Periodically prपूर्णांकs torture statistics, अगर periodic statistics prपूर्णांकing
 * was specअगरied via the stat_पूर्णांकerval module parameter.
 */
अटल पूर्णांक
rcu_torture_stats(व्योम *arg)
अणु
	VERBOSE_TOROUT_STRING("rcu_torture_stats task started");
	करो अणु
		schedule_समयout_पूर्णांकerruptible(stat_पूर्णांकerval * HZ);
		rcu_torture_stats_prपूर्णांक();
		torture_shutकरोwn_असलorb("rcu_torture_stats");
	पूर्ण जबतक (!torture_must_stop());
	torture_kthपढ़ो_stopping("rcu_torture_stats");

	अणु
		काष्ठा rcu_head *rhp;
		काष्ठा kmem_cache *kcp;
		अटल पूर्णांक z;

		kcp = kmem_cache_create("rcuscale", 136, 8, SLAB_STORE_USER, शून्य);
		rhp = kmem_cache_alloc(kcp, GFP_KERNEL);
		pr_alert("mem_dump_obj() slab test: rcu_torture_stats = %px, &rhp = %px, rhp = %px, &z = %px\n", stats_task, &rhp, rhp, &z);
		pr_alert("mem_dump_obj(ZERO_SIZE_PTR):");
		mem_dump_obj(ZERO_SIZE_PTR);
		pr_alert("mem_dump_obj(NULL):");
		mem_dump_obj(शून्य);
		pr_alert("mem_dump_obj(%px):", &rhp);
		mem_dump_obj(&rhp);
		pr_alert("mem_dump_obj(%px):", rhp);
		mem_dump_obj(rhp);
		pr_alert("mem_dump_obj(%px):", &rhp->func);
		mem_dump_obj(&rhp->func);
		pr_alert("mem_dump_obj(%px):", &z);
		mem_dump_obj(&z);
		kmem_cache_मुक्त(kcp, rhp);
		kmem_cache_destroy(kcp);
		rhp = kदो_स्मृति(माप(*rhp), GFP_KERNEL);
		pr_alert("mem_dump_obj() kmalloc test: rcu_torture_stats = %px, &rhp = %px, rhp = %px\n", stats_task, &rhp, rhp);
		pr_alert("mem_dump_obj(kmalloc %px):", rhp);
		mem_dump_obj(rhp);
		pr_alert("mem_dump_obj(kmalloc %px):", &rhp->func);
		mem_dump_obj(&rhp->func);
		kमुक्त(rhp);
		rhp = vदो_स्मृति(4096);
		pr_alert("mem_dump_obj() vmalloc test: rcu_torture_stats = %px, &rhp = %px, rhp = %px\n", stats_task, &rhp, rhp);
		pr_alert("mem_dump_obj(vmalloc %px):", rhp);
		mem_dump_obj(rhp);
		pr_alert("mem_dump_obj(vmalloc %px):", &rhp->func);
		mem_dump_obj(&rhp->func);
		vमुक्त(rhp);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
rcu_torture_prपूर्णांक_module_parms(काष्ठा rcu_torture_ops *cur_ops, स्थिर अक्षर *tag)
अणु
	pr_alert("%s" TORTURE_FLAG
		 "--- %s: nreaders=%d nfakewriters=%d "
		 "stat_interval=%d verbose=%d test_no_idle_hz=%d "
		 "shuffle_interval=%d stutter=%d irqreader=%d "
		 "fqs_duration=%d fqs_holdoff=%d fqs_stutter=%d "
		 "test_boost=%d/%d test_boost_interval=%d "
		 "test_boost_duration=%d shutdown_secs=%d "
		 "stall_cpu=%d stall_cpu_holdoff=%d stall_cpu_irqsoff=%d "
		 "stall_cpu_block=%d "
		 "n_barrier_cbs=%d "
		 "onoff_interval=%d onoff_holdoff=%d "
		 "read_exit_delay=%d read_exit_burst=%d "
		 "nocbs_nthreads=%d nocbs_toggle=%d\n",
		 torture_type, tag, nrealपढ़ोers, nfakeग_लिखोrs,
		 stat_पूर्णांकerval, verbose, test_no_idle_hz, shuffle_पूर्णांकerval,
		 stutter, irqपढ़ोer, fqs_duration, fqs_holकरोff, fqs_stutter,
		 test_boost, cur_ops->can_boost,
		 test_boost_पूर्णांकerval, test_boost_duration, shutकरोwn_secs,
		 stall_cpu, stall_cpu_holकरोff, stall_cpu_irqsoff,
		 stall_cpu_block,
		 n_barrier_cbs,
		 onoff_पूर्णांकerval, onoff_holकरोff,
		 पढ़ो_निकास_delay, पढ़ो_निकास_burst,
		 nocbs_nthपढ़ोs, nocbs_toggle);
पूर्ण

अटल पूर्णांक rcutorture_booster_cleanup(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा task_काष्ठा *t;

	अगर (boost_tasks[cpu] == शून्य)
		वापस 0;
	mutex_lock(&boost_mutex);
	t = boost_tasks[cpu];
	boost_tasks[cpu] = शून्य;
	rcu_torture_enable_rt_throttle();
	mutex_unlock(&boost_mutex);

	/* This must be outside of the mutex, otherwise deadlock! */
	torture_stop_kthपढ़ो(rcu_torture_boost, t);
	वापस 0;
पूर्ण

अटल पूर्णांक rcutorture_booster_init(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक retval;

	अगर (boost_tasks[cpu] != शून्य)
		वापस 0;  /* Alपढ़ोy created, nothing more to करो. */

	/* Don't allow समय recalculation जबतक creating a new task. */
	mutex_lock(&boost_mutex);
	rcu_torture_disable_rt_throttle();
	VERBOSE_TOROUT_STRING("Creating rcu_torture_boost task");
	boost_tasks[cpu] = kthपढ़ो_create_on_node(rcu_torture_boost, शून्य,
						  cpu_to_node(cpu),
						  "rcu_torture_boost");
	अगर (IS_ERR(boost_tasks[cpu])) अणु
		retval = PTR_ERR(boost_tasks[cpu]);
		VERBOSE_TOROUT_STRING("rcu_torture_boost task create failed");
		n_rcu_torture_boost_ktrerror++;
		boost_tasks[cpu] = शून्य;
		mutex_unlock(&boost_mutex);
		वापस retval;
	पूर्ण
	kthपढ़ो_bind(boost_tasks[cpu], cpu);
	wake_up_process(boost_tasks[cpu]);
	mutex_unlock(&boost_mutex);
	वापस 0;
पूर्ण

/*
 * CPU-stall kthपढ़ो.  It रुकोs as specअगरied by stall_cpu_holकरोff, then
 * induces a CPU stall क्रम the समय specअगरied by stall_cpu.
 */
अटल पूर्णांक rcu_torture_stall(व्योम *args)
अणु
	पूर्णांक idx;
	अचिन्हित दीर्घ stop_at;

	VERBOSE_TOROUT_STRING("rcu_torture_stall task started");
	अगर (stall_cpu_holकरोff > 0) अणु
		VERBOSE_TOROUT_STRING("rcu_torture_stall begin holdoff");
		schedule_समयout_पूर्णांकerruptible(stall_cpu_holकरोff * HZ);
		VERBOSE_TOROUT_STRING("rcu_torture_stall end holdoff");
	पूर्ण
	अगर (!kthपढ़ो_should_stop() && stall_gp_kthपढ़ो > 0) अणु
		VERBOSE_TOROUT_STRING("rcu_torture_stall begin GP stall");
		rcu_gp_set_torture_रुको(stall_gp_kthपढ़ो * HZ);
		क्रम (idx = 0; idx < stall_gp_kthपढ़ो + 2; idx++) अणु
			अगर (kthपढ़ो_should_stop())
				अवरोध;
			schedule_समयout_unपूर्णांकerruptible(HZ);
		पूर्ण
	पूर्ण
	अगर (!kthपढ़ो_should_stop() && stall_cpu > 0) अणु
		VERBOSE_TOROUT_STRING("rcu_torture_stall begin CPU stall");
		stop_at = kसमय_get_seconds() + stall_cpu;
		/* RCU CPU stall is expected behavior in following code. */
		idx = cur_ops->पढ़ोlock();
		अगर (stall_cpu_irqsoff)
			local_irq_disable();
		अन्यथा अगर (!stall_cpu_block)
			preempt_disable();
		pr_alert("%s start on CPU %d.\n",
			  __func__, raw_smp_processor_id());
		जबतक (ULONG_CMP_LT((अचिन्हित दीर्घ)kसमय_get_seconds(),
				    stop_at))
			अगर (stall_cpu_block)
				schedule_समयout_unपूर्णांकerruptible(HZ);
		अगर (stall_cpu_irqsoff)
			local_irq_enable();
		अन्यथा अगर (!stall_cpu_block)
			preempt_enable();
		cur_ops->पढ़ोunlock(idx);
	पूर्ण
	pr_alert("%s end.\n", __func__);
	torture_shutकरोwn_असलorb("rcu_torture_stall");
	जबतक (!kthपढ़ो_should_stop())
		schedule_समयout_पूर्णांकerruptible(10 * HZ);
	वापस 0;
पूर्ण

/* Spawn CPU-stall kthपढ़ो, अगर stall_cpu specअगरied. */
अटल पूर्णांक __init rcu_torture_stall_init(व्योम)
अणु
	अगर (stall_cpu <= 0 && stall_gp_kthपढ़ो <= 0)
		वापस 0;
	वापस torture_create_kthपढ़ो(rcu_torture_stall, शून्य, stall_task);
पूर्ण

/* State काष्ठाure क्रम क्रमward-progress self-propagating RCU callback. */
काष्ठा fwd_cb_state अणु
	काष्ठा rcu_head rh;
	पूर्णांक stop;
पूर्ण;

/*
 * Forward-progress self-propagating RCU callback function.  Because
 * callbacks run from softirq, this function is an implicit RCU पढ़ो-side
 * critical section.
 */
अटल व्योम rcu_torture_fwd_prog_cb(काष्ठा rcu_head *rhp)
अणु
	काष्ठा fwd_cb_state *fcsp = container_of(rhp, काष्ठा fwd_cb_state, rh);

	अगर (READ_ONCE(fcsp->stop)) अणु
		WRITE_ONCE(fcsp->stop, 2);
		वापस;
	पूर्ण
	cur_ops->call(&fcsp->rh, rcu_torture_fwd_prog_cb);
पूर्ण

/* State क्रम continuous-flood RCU callbacks. */
काष्ठा rcu_fwd_cb अणु
	काष्ठा rcu_head rh;
	काष्ठा rcu_fwd_cb *rfc_next;
	काष्ठा rcu_fwd *rfc_rfp;
	पूर्णांक rfc_gps;
पूर्ण;

#घोषणा MAX_FWD_CB_JIFFIES	(8 * HZ) /* Maximum CB test duration. */
#घोषणा MIN_FWD_CB_LAUNDERS	3	/* This many CB invocations to count. */
#घोषणा MIN_FWD_CBS_LAUNDERED	100	/* Number of counted CBs. */
#घोषणा FWD_CBS_HIST_DIV	10	/* Histogram buckets/second. */
#घोषणा N_LAUNDERS_HIST (2 * MAX_FWD_CB_JIFFIES / (HZ / FWD_CBS_HIST_DIV))

काष्ठा rcu_launder_hist अणु
	दीर्घ n_launders;
	अचिन्हित दीर्घ launder_gp_seq;
पूर्ण;

काष्ठा rcu_fwd अणु
	spinlock_t rcu_fwd_lock;
	काष्ठा rcu_fwd_cb *rcu_fwd_cb_head;
	काष्ठा rcu_fwd_cb **rcu_fwd_cb_tail;
	दीर्घ n_launders_cb;
	अचिन्हित दीर्घ rcu_fwd_startat;
	काष्ठा rcu_launder_hist n_launders_hist[N_LAUNDERS_HIST];
	अचिन्हित दीर्घ rcu_launder_gp_seq_start;
पूर्ण;

अटल DEFINE_MUTEX(rcu_fwd_mutex);
अटल काष्ठा rcu_fwd *rcu_fwds;
अटल bool rcu_fwd_emergency_stop;

अटल व्योम rcu_torture_fwd_cb_hist(काष्ठा rcu_fwd *rfp)
अणु
	अचिन्हित दीर्घ gps;
	अचिन्हित दीर्घ gps_old;
	पूर्णांक i;
	पूर्णांक j;

	क्रम (i = ARRAY_SIZE(rfp->n_launders_hist) - 1; i > 0; i--)
		अगर (rfp->n_launders_hist[i].n_launders > 0)
			अवरोध;
	pr_alert("%s: Callback-invocation histogram (duration %lu jiffies):",
		 __func__, jअगरfies - rfp->rcu_fwd_startat);
	gps_old = rfp->rcu_launder_gp_seq_start;
	क्रम (j = 0; j <= i; j++) अणु
		gps = rfp->n_launders_hist[j].launder_gp_seq;
		pr_cont(" %ds/%d: %ld:%ld",
			j + 1, FWD_CBS_HIST_DIV,
			rfp->n_launders_hist[j].n_launders,
			rcutorture_seq_dअगरf(gps, gps_old));
		gps_old = gps;
	पूर्ण
	pr_cont("\n");
पूर्ण

/* Callback function क्रम continuous-flood RCU callbacks. */
अटल व्योम rcu_torture_fwd_cb_cr(काष्ठा rcu_head *rhp)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	काष्ठा rcu_fwd_cb *rfcp = container_of(rhp, काष्ठा rcu_fwd_cb, rh);
	काष्ठा rcu_fwd_cb **rfcpp;
	काष्ठा rcu_fwd *rfp = rfcp->rfc_rfp;

	rfcp->rfc_next = शून्य;
	rfcp->rfc_gps++;
	spin_lock_irqsave(&rfp->rcu_fwd_lock, flags);
	rfcpp = rfp->rcu_fwd_cb_tail;
	rfp->rcu_fwd_cb_tail = &rfcp->rfc_next;
	WRITE_ONCE(*rfcpp, rfcp);
	WRITE_ONCE(rfp->n_launders_cb, rfp->n_launders_cb + 1);
	i = ((jअगरfies - rfp->rcu_fwd_startat) / (HZ / FWD_CBS_HIST_DIV));
	अगर (i >= ARRAY_SIZE(rfp->n_launders_hist))
		i = ARRAY_SIZE(rfp->n_launders_hist) - 1;
	rfp->n_launders_hist[i].n_launders++;
	rfp->n_launders_hist[i].launder_gp_seq = cur_ops->get_gp_seq();
	spin_unlock_irqrestore(&rfp->rcu_fwd_lock, flags);
पूर्ण

// Give the scheduler a chance, even on nohz_full CPUs.
अटल व्योम rcu_torture_fwd_prog_cond_resched(अचिन्हित दीर्घ iter)
अणु
	अगर (IS_ENABLED(CONFIG_PREEMPTION) && IS_ENABLED(CONFIG_NO_HZ_FULL)) अणु
		// Real call_rcu() floods hit userspace, so emulate that.
		अगर (need_resched() || (iter & 0xfff))
			schedule();
		वापस;
	पूर्ण
	// No userspace emulation: CB invocation throttles call_rcu()
	cond_resched();
पूर्ण

/*
 * Free all callbacks on the rcu_fwd_cb_head list, either because the
 * test is over or because we hit an OOM event.
 */
अटल अचिन्हित दीर्घ rcu_torture_fwd_prog_cbमुक्त(काष्ठा rcu_fwd *rfp)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ मुक्तd = 0;
	काष्ठा rcu_fwd_cb *rfcp;

	क्रम (;;) अणु
		spin_lock_irqsave(&rfp->rcu_fwd_lock, flags);
		rfcp = rfp->rcu_fwd_cb_head;
		अगर (!rfcp) अणु
			spin_unlock_irqrestore(&rfp->rcu_fwd_lock, flags);
			अवरोध;
		पूर्ण
		rfp->rcu_fwd_cb_head = rfcp->rfc_next;
		अगर (!rfp->rcu_fwd_cb_head)
			rfp->rcu_fwd_cb_tail = &rfp->rcu_fwd_cb_head;
		spin_unlock_irqrestore(&rfp->rcu_fwd_lock, flags);
		kमुक्त(rfcp);
		मुक्तd++;
		rcu_torture_fwd_prog_cond_resched(मुक्तd);
		अगर (tick_nohz_full_enabled()) अणु
			local_irq_save(flags);
			rcu_momentary_dyntick_idle();
			local_irq_restore(flags);
		पूर्ण
	पूर्ण
	वापस मुक्तd;
पूर्ण

/* Carry out need_resched()/cond_resched() क्रमward-progress testing. */
अटल व्योम rcu_torture_fwd_prog_nr(काष्ठा rcu_fwd *rfp,
				    पूर्णांक *tested, पूर्णांक *tested_tries)
अणु
	अचिन्हित दीर्घ cver;
	अचिन्हित दीर्घ dur;
	काष्ठा fwd_cb_state fcs;
	अचिन्हित दीर्घ gps;
	पूर्णांक idx;
	पूर्णांक sd;
	पूर्णांक sd4;
	bool selfpropcb = false;
	अचिन्हित दीर्घ stopat;
	अटल DEFINE_TORTURE_RANDOM(trs);

	अगर (!cur_ops->sync)
		वापस; // Cannot करो need_resched() क्रमward progress testing without ->sync.
	अगर (cur_ops->call && cur_ops->cb_barrier) अणु
		init_rcu_head_on_stack(&fcs.rh);
		selfpropcb = true;
	पूर्ण

	/* Tight loop containing cond_resched(). */
	WRITE_ONCE(rcu_fwd_cb_nodelay, true);
	cur_ops->sync(); /* Later पढ़ोers see above ग_लिखो. */
	अगर  (selfpropcb) अणु
		WRITE_ONCE(fcs.stop, 0);
		cur_ops->call(&fcs.rh, rcu_torture_fwd_prog_cb);
	पूर्ण
	cver = READ_ONCE(rcu_torture_current_version);
	gps = cur_ops->get_gp_seq();
	sd = cur_ops->stall_dur() + 1;
	sd4 = (sd + fwd_progress_भाग - 1) / fwd_progress_भाग;
	dur = sd4 + torture_अक्रमom(&trs) % (sd - sd4);
	WRITE_ONCE(rfp->rcu_fwd_startat, jअगरfies);
	stopat = rfp->rcu_fwd_startat + dur;
	जबतक (समय_beक्रमe(jअगरfies, stopat) &&
	       !shutकरोwn_समय_arrived() &&
	       !READ_ONCE(rcu_fwd_emergency_stop) && !torture_must_stop()) अणु
		idx = cur_ops->पढ़ोlock();
		udelay(10);
		cur_ops->पढ़ोunlock(idx);
		अगर (!fwd_progress_need_resched || need_resched())
			cond_resched();
	पूर्ण
	(*tested_tries)++;
	अगर (!समय_beक्रमe(jअगरfies, stopat) &&
	    !shutकरोwn_समय_arrived() &&
	    !READ_ONCE(rcu_fwd_emergency_stop) && !torture_must_stop()) अणु
		(*tested)++;
		cver = READ_ONCE(rcu_torture_current_version) - cver;
		gps = rcutorture_seq_dअगरf(cur_ops->get_gp_seq(), gps);
		WARN_ON(!cver && gps < 2);
		pr_alert("%s: Duration %ld cver %ld gps %ld\n", __func__, dur, cver, gps);
	पूर्ण
	अगर (selfpropcb) अणु
		WRITE_ONCE(fcs.stop, 1);
		cur_ops->sync(); /* Wait क्रम running CB to complete. */
		cur_ops->cb_barrier(); /* Wait क्रम queued callbacks. */
	पूर्ण

	अगर (selfpropcb) अणु
		WARN_ON(READ_ONCE(fcs.stop) != 2);
		destroy_rcu_head_on_stack(&fcs.rh);
	पूर्ण
	schedule_समयout_unपूर्णांकerruptible(HZ / 10); /* Let kthपढ़ोs recover. */
	WRITE_ONCE(rcu_fwd_cb_nodelay, false);
पूर्ण

/* Carry out call_rcu() क्रमward-progress testing. */
अटल व्योम rcu_torture_fwd_prog_cr(काष्ठा rcu_fwd *rfp)
अणु
	अचिन्हित दीर्घ cver;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ gps;
	पूर्णांक i;
	दीर्घ n_launders;
	दीर्घ n_launders_cb_snap;
	दीर्घ n_launders_sa;
	दीर्घ n_max_cbs;
	दीर्घ n_max_gps;
	काष्ठा rcu_fwd_cb *rfcp;
	काष्ठा rcu_fwd_cb *rfcpn;
	अचिन्हित दीर्घ stopat;
	अचिन्हित दीर्घ stoppedat;

	अगर (READ_ONCE(rcu_fwd_emergency_stop))
		वापस; /* Get out of the way quickly, no GP रुको! */
	अगर (!cur_ops->call)
		वापस; /* Can't करो call_rcu() fwd prog without ->call. */

	/* Loop continuously posting RCU callbacks. */
	WRITE_ONCE(rcu_fwd_cb_nodelay, true);
	cur_ops->sync(); /* Later पढ़ोers see above ग_लिखो. */
	WRITE_ONCE(rfp->rcu_fwd_startat, jअगरfies);
	stopat = rfp->rcu_fwd_startat + MAX_FWD_CB_JIFFIES;
	n_launders = 0;
	rfp->n_launders_cb = 0; // Hoist initialization क्रम multi-kthपढ़ो
	n_launders_sa = 0;
	n_max_cbs = 0;
	n_max_gps = 0;
	क्रम (i = 0; i < ARRAY_SIZE(rfp->n_launders_hist); i++)
		rfp->n_launders_hist[i].n_launders = 0;
	cver = READ_ONCE(rcu_torture_current_version);
	gps = cur_ops->get_gp_seq();
	rfp->rcu_launder_gp_seq_start = gps;
	tick_dep_set_task(current, TICK_DEP_BIT_RCU);
	जबतक (समय_beक्रमe(jअगरfies, stopat) &&
	       !shutकरोwn_समय_arrived() &&
	       !READ_ONCE(rcu_fwd_emergency_stop) && !torture_must_stop()) अणु
		rfcp = READ_ONCE(rfp->rcu_fwd_cb_head);
		rfcpn = शून्य;
		अगर (rfcp)
			rfcpn = READ_ONCE(rfcp->rfc_next);
		अगर (rfcpn) अणु
			अगर (rfcp->rfc_gps >= MIN_FWD_CB_LAUNDERS &&
			    ++n_max_gps >= MIN_FWD_CBS_LAUNDERED)
				अवरोध;
			rfp->rcu_fwd_cb_head = rfcpn;
			n_launders++;
			n_launders_sa++;
		पूर्ण अन्यथा अणु
			rfcp = kदो_स्मृति(माप(*rfcp), GFP_KERNEL);
			अगर (WARN_ON_ONCE(!rfcp)) अणु
				schedule_समयout_पूर्णांकerruptible(1);
				जारी;
			पूर्ण
			n_max_cbs++;
			n_launders_sa = 0;
			rfcp->rfc_gps = 0;
			rfcp->rfc_rfp = rfp;
		पूर्ण
		cur_ops->call(&rfcp->rh, rcu_torture_fwd_cb_cr);
		rcu_torture_fwd_prog_cond_resched(n_launders + n_max_cbs);
		अगर (tick_nohz_full_enabled()) अणु
			local_irq_save(flags);
			rcu_momentary_dyntick_idle();
			local_irq_restore(flags);
		पूर्ण
	पूर्ण
	stoppedat = jअगरfies;
	n_launders_cb_snap = READ_ONCE(rfp->n_launders_cb);
	cver = READ_ONCE(rcu_torture_current_version) - cver;
	gps = rcutorture_seq_dअगरf(cur_ops->get_gp_seq(), gps);
	cur_ops->cb_barrier(); /* Wait क्रम callbacks to be invoked. */
	(व्योम)rcu_torture_fwd_prog_cbमुक्त(rfp);

	अगर (!torture_must_stop() && !READ_ONCE(rcu_fwd_emergency_stop) &&
	    !shutकरोwn_समय_arrived()) अणु
		WARN_ON(n_max_gps < MIN_FWD_CBS_LAUNDERED);
		pr_alert("%s Duration %lu barrier: %lu pending %ld n_launders: %ld n_launders_sa: %ld n_max_gps: %ld n_max_cbs: %ld cver %ld gps %ld\n",
			 __func__,
			 stoppedat - rfp->rcu_fwd_startat, jअगरfies - stoppedat,
			 n_launders + n_max_cbs - n_launders_cb_snap,
			 n_launders, n_launders_sa,
			 n_max_gps, n_max_cbs, cver, gps);
		rcu_torture_fwd_cb_hist(rfp);
	पूर्ण
	schedule_समयout_unपूर्णांकerruptible(HZ); /* Let CBs drain. */
	tick_dep_clear_task(current, TICK_DEP_BIT_RCU);
	WRITE_ONCE(rcu_fwd_cb_nodelay, false);
पूर्ण


/*
 * OOM notअगरier, but this only prपूर्णांकs diagnostic inक्रमmation क्रम the
 * current क्रमward-progress test.
 */
अटल पूर्णांक rcutorture_oom_notअगरy(काष्ठा notअगरier_block *self,
				 अचिन्हित दीर्घ notused, व्योम *nमुक्तd)
अणु
	काष्ठा rcu_fwd *rfp;

	mutex_lock(&rcu_fwd_mutex);
	rfp = rcu_fwds;
	अगर (!rfp) अणु
		mutex_unlock(&rcu_fwd_mutex);
		वापस NOTIFY_OK;
	पूर्ण
	WARN(1, "%s invoked upon OOM during forward-progress testing.\n",
	     __func__);
	rcu_torture_fwd_cb_hist(rfp);
	rcu_fwd_progress_check(1 + (jअगरfies - READ_ONCE(rfp->rcu_fwd_startat)) / 2);
	WRITE_ONCE(rcu_fwd_emergency_stop, true);
	smp_mb(); /* Emergency stop beक्रमe मुक्त and रुको to aव्योम hangs. */
	pr_info("%s: Freed %lu RCU callbacks.\n",
		__func__, rcu_torture_fwd_prog_cbमुक्त(rfp));
	rcu_barrier();
	pr_info("%s: Freed %lu RCU callbacks.\n",
		__func__, rcu_torture_fwd_prog_cbमुक्त(rfp));
	rcu_barrier();
	pr_info("%s: Freed %lu RCU callbacks.\n",
		__func__, rcu_torture_fwd_prog_cbमुक्त(rfp));
	smp_mb(); /* Frees beक्रमe वापस to aव्योम reकरोing OOM. */
	(*(अचिन्हित दीर्घ *)nमुक्तd)++; /* Forward progress CBs मुक्तd! */
	pr_info("%s returning after OOM processing.\n", __func__);
	mutex_unlock(&rcu_fwd_mutex);
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block rcutorture_oom_nb = अणु
	.notअगरier_call = rcutorture_oom_notअगरy
पूर्ण;

/* Carry out grace-period क्रमward-progress testing. */
अटल पूर्णांक rcu_torture_fwd_prog(व्योम *args)
अणु
	पूर्णांक oldnice = task_nice(current);
	काष्ठा rcu_fwd *rfp = args;
	पूर्णांक tested = 0;
	पूर्णांक tested_tries = 0;

	VERBOSE_TOROUT_STRING("rcu_torture_fwd_progress task started");
	rcu_bind_current_to_nocb();
	अगर (!IS_ENABLED(CONFIG_SMP) || !IS_ENABLED(CONFIG_RCU_BOOST))
		set_user_nice(current, MAX_NICE);
	करो अणु
		schedule_समयout_पूर्णांकerruptible(fwd_progress_holकरोff * HZ);
		WRITE_ONCE(rcu_fwd_emergency_stop, false);
		अगर (!IS_ENABLED(CONFIG_TINY_RCU) ||
		    rcu_inkernel_boot_has_ended())
			rcu_torture_fwd_prog_nr(rfp, &tested, &tested_tries);
		अगर (rcu_inkernel_boot_has_ended())
			rcu_torture_fwd_prog_cr(rfp);

		/* Aव्योम slow periods, better to test when busy. */
		अगर (stutter_रुको("rcu_torture_fwd_prog"))
			sched_set_normal(current, oldnice);
	पूर्ण जबतक (!torture_must_stop());
	/* Short runs might not contain a valid क्रमward-progress attempt. */
	WARN_ON(!tested && tested_tries >= 5);
	pr_alert("%s: tested %d tested_tries %d\n", __func__, tested, tested_tries);
	torture_kthपढ़ो_stopping("rcu_torture_fwd_prog");
	वापस 0;
पूर्ण

/* If क्रमward-progress checking is requested and feasible, spawn the thपढ़ो. */
अटल पूर्णांक __init rcu_torture_fwd_prog_init(व्योम)
अणु
	काष्ठा rcu_fwd *rfp;

	अगर (!fwd_progress)
		वापस 0; /* Not requested, so करोn't करो it. */
	अगर ((!cur_ops->sync && !cur_ops->call) ||
	    !cur_ops->stall_dur || cur_ops->stall_dur() <= 0 || cur_ops == &rcu_busted_ops) अणु
		VERBOSE_TOROUT_STRING("rcu_torture_fwd_prog_init: Disabled, unsupported by RCU flavor under test");
		वापस 0;
	पूर्ण
	अगर (stall_cpu > 0) अणु
		VERBOSE_TOROUT_STRING("rcu_torture_fwd_prog_init: Disabled, conflicts with CPU-stall testing");
		अगर (IS_MODULE(CONFIG_RCU_TORTURE_TESTS))
			वापस -EINVAL; /* In module, can fail back to user. */
		WARN_ON(1); /* Make sure rcutorture notices conflict. */
		वापस 0;
	पूर्ण
	अगर (fwd_progress_holकरोff <= 0)
		fwd_progress_holकरोff = 1;
	अगर (fwd_progress_भाग <= 0)
		fwd_progress_भाग = 4;
	rfp = kzalloc(माप(*rfp), GFP_KERNEL);
	अगर (!rfp)
		वापस -ENOMEM;
	spin_lock_init(&rfp->rcu_fwd_lock);
	rfp->rcu_fwd_cb_tail = &rfp->rcu_fwd_cb_head;
	mutex_lock(&rcu_fwd_mutex);
	rcu_fwds = rfp;
	mutex_unlock(&rcu_fwd_mutex);
	रेजिस्टर_oom_notअगरier(&rcutorture_oom_nb);
	वापस torture_create_kthपढ़ो(rcu_torture_fwd_prog, rfp, fwd_prog_task);
पूर्ण

अटल व्योम rcu_torture_fwd_prog_cleanup(व्योम)
अणु
	काष्ठा rcu_fwd *rfp;

	torture_stop_kthपढ़ो(rcu_torture_fwd_prog, fwd_prog_task);
	rfp = rcu_fwds;
	mutex_lock(&rcu_fwd_mutex);
	rcu_fwds = शून्य;
	mutex_unlock(&rcu_fwd_mutex);
	unरेजिस्टर_oom_notअगरier(&rcutorture_oom_nb);
	kमुक्त(rfp);
पूर्ण

/* Callback function क्रम RCU barrier testing. */
अटल व्योम rcu_torture_barrier_cbf(काष्ठा rcu_head *rcu)
अणु
	atomic_inc(&barrier_cbs_invoked);
पूर्ण

/* IPI handler to get callback posted on desired CPU, अगर online. */
अटल व्योम rcu_torture_barrier1cb(व्योम *rcu_व्योम)
अणु
	काष्ठा rcu_head *rhp = rcu_व्योम;

	cur_ops->call(rhp, rcu_torture_barrier_cbf);
पूर्ण

/* kthपढ़ो function to रेजिस्टर callbacks used to test RCU barriers. */
अटल पूर्णांक rcu_torture_barrier_cbs(व्योम *arg)
अणु
	दीर्घ myid = (दीर्घ)arg;
	bool lastphase = false;
	bool newphase;
	काष्ठा rcu_head rcu;

	init_rcu_head_on_stack(&rcu);
	VERBOSE_TOROUT_STRING("rcu_torture_barrier_cbs task started");
	set_user_nice(current, MAX_NICE);
	करो अणु
		रुको_event(barrier_cbs_wq[myid],
			   (newphase =
			    smp_load_acquire(&barrier_phase)) != lastphase ||
			   torture_must_stop());
		lastphase = newphase;
		अगर (torture_must_stop())
			अवरोध;
		/*
		 * The above smp_load_acquire() ensures barrier_phase load
		 * is ordered beक्रमe the following ->call().
		 */
		अगर (smp_call_function_single(myid, rcu_torture_barrier1cb,
					     &rcu, 1)) अणु
			// IPI failed, so use direct call from current CPU.
			cur_ops->call(&rcu, rcu_torture_barrier_cbf);
		पूर्ण
		अगर (atomic_dec_and_test(&barrier_cbs_count))
			wake_up(&barrier_wq);
	पूर्ण जबतक (!torture_must_stop());
	अगर (cur_ops->cb_barrier != शून्य)
		cur_ops->cb_barrier();
	destroy_rcu_head_on_stack(&rcu);
	torture_kthपढ़ो_stopping("rcu_torture_barrier_cbs");
	वापस 0;
पूर्ण

/* kthपढ़ो function to drive and coordinate RCU barrier testing. */
अटल पूर्णांक rcu_torture_barrier(व्योम *arg)
अणु
	पूर्णांक i;

	VERBOSE_TOROUT_STRING("rcu_torture_barrier task starting");
	करो अणु
		atomic_set(&barrier_cbs_invoked, 0);
		atomic_set(&barrier_cbs_count, n_barrier_cbs);
		/* Ensure barrier_phase ordered after prior assignments. */
		smp_store_release(&barrier_phase, !barrier_phase);
		क्रम (i = 0; i < n_barrier_cbs; i++)
			wake_up(&barrier_cbs_wq[i]);
		रुको_event(barrier_wq,
			   atomic_पढ़ो(&barrier_cbs_count) == 0 ||
			   torture_must_stop());
		अगर (torture_must_stop())
			अवरोध;
		n_barrier_attempts++;
		cur_ops->cb_barrier(); /* Implies smp_mb() क्रम रुको_event(). */
		अगर (atomic_पढ़ो(&barrier_cbs_invoked) != n_barrier_cbs) अणु
			n_rcu_torture_barrier_error++;
			pr_err("barrier_cbs_invoked = %d, n_barrier_cbs = %d\n",
			       atomic_पढ़ो(&barrier_cbs_invoked),
			       n_barrier_cbs);
			WARN_ON(1);
			// Wait manually क्रम the reमुख्यing callbacks
			i = 0;
			करो अणु
				अगर (WARN_ON(i++ > HZ))
					i = पूर्णांक_न्यून;
				schedule_समयout_पूर्णांकerruptible(1);
				cur_ops->cb_barrier();
			पूर्ण जबतक (atomic_पढ़ो(&barrier_cbs_invoked) !=
				 n_barrier_cbs &&
				 !torture_must_stop());
			smp_mb(); // Can't trust ordering अगर broken.
			अगर (!torture_must_stop())
				pr_err("Recovered: barrier_cbs_invoked = %d\n",
				       atomic_पढ़ो(&barrier_cbs_invoked));
		पूर्ण अन्यथा अणु
			n_barrier_successes++;
		पूर्ण
		schedule_समयout_पूर्णांकerruptible(HZ / 10);
	पूर्ण जबतक (!torture_must_stop());
	torture_kthपढ़ो_stopping("rcu_torture_barrier");
	वापस 0;
पूर्ण

/* Initialize RCU barrier testing. */
अटल पूर्णांक rcu_torture_barrier_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	अगर (n_barrier_cbs <= 0)
		वापस 0;
	अगर (cur_ops->call == शून्य || cur_ops->cb_barrier == शून्य) अणु
		pr_alert("%s" TORTURE_FLAG
			 " Call or barrier ops missing for %s,\n",
			 torture_type, cur_ops->name);
		pr_alert("%s" TORTURE_FLAG
			 " RCU barrier testing omitted from run.\n",
			 torture_type);
		वापस 0;
	पूर्ण
	atomic_set(&barrier_cbs_count, 0);
	atomic_set(&barrier_cbs_invoked, 0);
	barrier_cbs_tasks =
		kसुस्मृति(n_barrier_cbs, माप(barrier_cbs_tasks[0]),
			GFP_KERNEL);
	barrier_cbs_wq =
		kसुस्मृति(n_barrier_cbs, माप(barrier_cbs_wq[0]), GFP_KERNEL);
	अगर (barrier_cbs_tasks == शून्य || !barrier_cbs_wq)
		वापस -ENOMEM;
	क्रम (i = 0; i < n_barrier_cbs; i++) अणु
		init_रुकोqueue_head(&barrier_cbs_wq[i]);
		ret = torture_create_kthपढ़ो(rcu_torture_barrier_cbs,
					     (व्योम *)(दीर्घ)i,
					     barrier_cbs_tasks[i]);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस torture_create_kthपढ़ो(rcu_torture_barrier, शून्य, barrier_task);
पूर्ण

/* Clean up after RCU barrier testing. */
अटल व्योम rcu_torture_barrier_cleanup(व्योम)
अणु
	पूर्णांक i;

	torture_stop_kthपढ़ो(rcu_torture_barrier, barrier_task);
	अगर (barrier_cbs_tasks != शून्य) अणु
		क्रम (i = 0; i < n_barrier_cbs; i++)
			torture_stop_kthपढ़ो(rcu_torture_barrier_cbs,
					     barrier_cbs_tasks[i]);
		kमुक्त(barrier_cbs_tasks);
		barrier_cbs_tasks = शून्य;
	पूर्ण
	अगर (barrier_cbs_wq != शून्य) अणु
		kमुक्त(barrier_cbs_wq);
		barrier_cbs_wq = शून्य;
	पूर्ण
पूर्ण

अटल bool rcu_torture_can_boost(व्योम)
अणु
	अटल पूर्णांक boost_warn_once;
	पूर्णांक prio;

	अगर (!(test_boost == 1 && cur_ops->can_boost) && test_boost != 2)
		वापस false;
	अगर (!cur_ops->call)
		वापस false;

	prio = rcu_get_gp_kthपढ़ोs_prio();
	अगर (!prio)
		वापस false;

	अगर (prio < 2) अणु
		अगर (boost_warn_once  == 1)
			वापस false;

		pr_alert("%s: WARN: RCU kthread priority too low to test boosting.  Skipping RCU boost test. Try passing rcutree.kthread_prio > 1 on the kernel command line.\n", KBUILD_MODNAME);
		boost_warn_once = 1;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool पढ़ो_निकास_child_stop;
अटल bool पढ़ो_निकास_child_stopped;
अटल रुको_queue_head_t पढ़ो_निकास_wq;

// Child kthपढ़ो which just करोes an rcutorture पढ़ोer and निकासs.
अटल पूर्णांक rcu_torture_पढ़ो_निकास_child(व्योम *trsp_in)
अणु
	काष्ठा torture_अक्रमom_state *trsp = trsp_in;

	set_user_nice(current, MAX_NICE);
	// Minimize समय between पढ़ोing and निकासing.
	जबतक (!kthपढ़ो_should_stop())
		schedule_समयout_unपूर्णांकerruptible(1);
	(व्योम)rcu_torture_one_पढ़ो(trsp, -1);
	वापस 0;
पूर्ण

// Parent kthपढ़ो which creates and destroys पढ़ो-निकास child kthपढ़ोs.
अटल पूर्णांक rcu_torture_पढ़ो_निकास(व्योम *unused)
अणु
	पूर्णांक count = 0;
	bool errनिकास = false;
	पूर्णांक i;
	काष्ठा task_काष्ठा *tsp;
	DEFINE_TORTURE_RANDOM(trs);

	// Allocate and initialize.
	set_user_nice(current, MAX_NICE);
	VERBOSE_TOROUT_STRING("rcu_torture_read_exit: Start of test");

	// Each pass through this loop करोes one पढ़ो-निकास episode.
	करो अणु
		अगर (++count > पढ़ो_निकास_burst) अणु
			VERBOSE_TOROUT_STRING("rcu_torture_read_exit: End of episode");
			rcu_barrier(); // Wait क्रम task_काष्ठा मुक्त, aव्योम OOM.
			क्रम (i = 0; i < पढ़ो_निकास_delay; i++) अणु
				schedule_समयout_unपूर्णांकerruptible(HZ);
				अगर (READ_ONCE(पढ़ो_निकास_child_stop))
					अवरोध;
			पूर्ण
			अगर (!READ_ONCE(पढ़ो_निकास_child_stop))
				VERBOSE_TOROUT_STRING("rcu_torture_read_exit: Start of episode");
			count = 0;
		पूर्ण
		अगर (READ_ONCE(पढ़ो_निकास_child_stop))
			अवरोध;
		// Spawn child.
		tsp = kthपढ़ो_run(rcu_torture_पढ़ो_निकास_child,
				     &trs, "%s",
				     "rcu_torture_read_exit_child");
		अगर (IS_ERR(tsp)) अणु
			VERBOSE_TOROUT_ERRSTRING("out of memory");
			errनिकास = true;
			tsp = शून्य;
			अवरोध;
		पूर्ण
		cond_resched();
		kthपढ़ो_stop(tsp);
		n_पढ़ो_निकासs ++;
		stutter_रुको("rcu_torture_read_exit");
	पूर्ण जबतक (!errनिकास && !READ_ONCE(पढ़ो_निकास_child_stop));

	// Clean up and निकास.
	smp_store_release(&पढ़ो_निकास_child_stopped, true); // After reaping.
	smp_mb(); // Store beक्रमe wakeup.
	wake_up(&पढ़ो_निकास_wq);
	जबतक (!torture_must_stop())
		schedule_समयout_unपूर्णांकerruptible(1);
	torture_kthपढ़ो_stopping("rcu_torture_read_exit");
	वापस 0;
पूर्ण

अटल पूर्णांक rcu_torture_पढ़ो_निकास_init(व्योम)
अणु
	अगर (पढ़ो_निकास_burst <= 0)
		वापस -EINVAL;
	init_रुकोqueue_head(&पढ़ो_निकास_wq);
	पढ़ो_निकास_child_stop = false;
	पढ़ो_निकास_child_stopped = false;
	वापस torture_create_kthपढ़ो(rcu_torture_पढ़ो_निकास, शून्य,
				      पढ़ो_निकास_task);
पूर्ण

अटल व्योम rcu_torture_पढ़ो_निकास_cleanup(व्योम)
अणु
	अगर (!पढ़ो_निकास_task)
		वापस;
	WRITE_ONCE(पढ़ो_निकास_child_stop, true);
	smp_mb(); // Above ग_लिखो beक्रमe रुको.
	रुको_event(पढ़ो_निकास_wq, smp_load_acquire(&पढ़ो_निकास_child_stopped));
	torture_stop_kthपढ़ो(rcutorture_पढ़ो_निकास, पढ़ो_निकास_task);
पूर्ण

अटल क्रमागत cpuhp_state rcutor_hp;

अटल व्योम
rcu_torture_cleanup(व्योम)
अणु
	पूर्णांक firstसमय;
	पूर्णांक flags = 0;
	अचिन्हित दीर्घ gp_seq = 0;
	पूर्णांक i;

	अगर (torture_cleanup_begin()) अणु
		अगर (cur_ops->cb_barrier != शून्य)
			cur_ops->cb_barrier();
		वापस;
	पूर्ण
	अगर (!cur_ops) अणु
		torture_cleanup_end();
		वापस;
	पूर्ण

	अगर (cur_ops->gp_kthपढ़ो_dbg)
		cur_ops->gp_kthपढ़ो_dbg();
	rcu_torture_पढ़ो_निकास_cleanup();
	rcu_torture_barrier_cleanup();
	rcu_torture_fwd_prog_cleanup();
	torture_stop_kthपढ़ो(rcu_torture_stall, stall_task);
	torture_stop_kthपढ़ो(rcu_torture_ग_लिखोr, ग_लिखोr_task);

	अगर (nocb_tasks) अणु
		क्रम (i = 0; i < nrealnocbers; i++)
			torture_stop_kthपढ़ो(rcu_nocb_toggle, nocb_tasks[i]);
		kमुक्त(nocb_tasks);
		nocb_tasks = शून्य;
	पूर्ण

	अगर (पढ़ोer_tasks) अणु
		क्रम (i = 0; i < nrealपढ़ोers; i++)
			torture_stop_kthपढ़ो(rcu_torture_पढ़ोer,
					     पढ़ोer_tasks[i]);
		kमुक्त(पढ़ोer_tasks);
		पढ़ोer_tasks = शून्य;
	पूर्ण
	kमुक्त(rcu_torture_पढ़ोer_mbchk);
	rcu_torture_पढ़ोer_mbchk = शून्य;

	अगर (fakeग_लिखोr_tasks) अणु
		क्रम (i = 0; i < nfakeग_लिखोrs; i++)
			torture_stop_kthपढ़ो(rcu_torture_fakeग_लिखोr,
					     fakeग_लिखोr_tasks[i]);
		kमुक्त(fakeग_लिखोr_tasks);
		fakeग_लिखोr_tasks = शून्य;
	पूर्ण

	rcutorture_get_gp_data(cur_ops->ttype, &flags, &gp_seq);
	srcutorture_get_gp_data(cur_ops->ttype, srcu_ctlp, &flags, &gp_seq);
	pr_alert("%s:  End-test grace-period state: g%ld f%#x total-gps=%ld\n",
		 cur_ops->name, (दीर्घ)gp_seq, flags,
		 rcutorture_seq_dअगरf(gp_seq, start_gp_seq));
	torture_stop_kthपढ़ो(rcu_torture_stats, stats_task);
	torture_stop_kthपढ़ो(rcu_torture_fqs, fqs_task);
	अगर (rcu_torture_can_boost())
		cpuhp_हटाओ_state(rcutor_hp);

	/*
	 * Wait क्रम all RCU callbacks to fire, then करो torture-type-specअगरic
	 * cleanup operations.
	 */
	अगर (cur_ops->cb_barrier != शून्य)
		cur_ops->cb_barrier();
	अगर (cur_ops->cleanup != शून्य)
		cur_ops->cleanup();

	rcu_torture_stats_prपूर्णांक();  /* -After- the stats thपढ़ो is stopped! */

	अगर (err_segs_recorded) अणु
		pr_alert("Failure/close-call rcutorture reader segments:\n");
		अगर (rt_पढ़ो_nsegs == 0)
			pr_alert("\t: No segments recorded!!!\n");
		firstसमय = 1;
		क्रम (i = 0; i < rt_पढ़ो_nsegs; i++) अणु
			pr_alert("\t%d: %#x ", i, err_segs[i].rt_पढ़ोstate);
			अगर (err_segs[i].rt_delay_jअगरfies != 0) अणु
				pr_cont("%s%ldjiffies", firstसमय ? "" : "+",
					err_segs[i].rt_delay_jअगरfies);
				firstसमय = 0;
			पूर्ण
			अगर (err_segs[i].rt_delay_ms != 0) अणु
				pr_cont("%s%ldms", firstसमय ? "" : "+",
					err_segs[i].rt_delay_ms);
				firstसमय = 0;
			पूर्ण
			अगर (err_segs[i].rt_delay_us != 0) अणु
				pr_cont("%s%ldus", firstसमय ? "" : "+",
					err_segs[i].rt_delay_us);
				firstसमय = 0;
			पूर्ण
			pr_cont("%s\n",
				err_segs[i].rt_preempted ? "preempted" : "");

		पूर्ण
	पूर्ण
	अगर (atomic_पढ़ो(&n_rcu_torture_error) || n_rcu_torture_barrier_error)
		rcu_torture_prपूर्णांक_module_parms(cur_ops, "End of test: FAILURE");
	अन्यथा अगर (torture_onoff_failures())
		rcu_torture_prपूर्णांक_module_parms(cur_ops,
					       "End of test: RCU_HOTPLUG");
	अन्यथा
		rcu_torture_prपूर्णांक_module_parms(cur_ops, "End of test: SUCCESS");
	torture_cleanup_end();
पूर्ण

#अगर_घोषित CONFIG_DEBUG_OBJECTS_RCU_HEAD
अटल व्योम rcu_torture_leak_cb(काष्ठा rcu_head *rhp)
अणु
पूर्ण

अटल व्योम rcu_torture_err_cb(काष्ठा rcu_head *rhp)
अणु
	/*
	 * This -might- happen due to race conditions, but is unlikely.
	 * The scenario that leads to this happening is that the
	 * first of the pair of duplicate callbacks is queued,
	 * someone अन्यथा starts a grace period that includes that
	 * callback, then the second of the pair must रुको क्रम the
	 * next grace period.  Unlikely, but can happen.  If it
	 * करोes happen, the debug-objects subप्रणाली won't have splatted.
	 */
	pr_alert("%s: duplicated callback was invoked.\n", KBUILD_MODNAME);
पूर्ण
#पूर्ण_अगर /* #अगर_घोषित CONFIG_DEBUG_OBJECTS_RCU_HEAD */

/*
 * Verअगरy that द्विगुन-मुक्त causes debug-objects to complain, but only
 * अगर CONFIG_DEBUG_OBJECTS_RCU_HEAD=y.  Otherwise, say that the test
 * cannot be carried out.
 */
अटल व्योम rcu_test_debug_objects(व्योम)
अणु
#अगर_घोषित CONFIG_DEBUG_OBJECTS_RCU_HEAD
	काष्ठा rcu_head rh1;
	काष्ठा rcu_head rh2;
	काष्ठा rcu_head *rhp = kदो_स्मृति(माप(*rhp), GFP_KERNEL);

	init_rcu_head_on_stack(&rh1);
	init_rcu_head_on_stack(&rh2);
	pr_alert("%s: WARN: Duplicate call_rcu() test starting.\n", KBUILD_MODNAME);

	/* Try to queue the rh2 pair of callbacks क्रम the same grace period. */
	preempt_disable(); /* Prevent preemption from पूर्णांकerrupting test. */
	rcu_पढ़ो_lock(); /* Make it impossible to finish a grace period. */
	call_rcu(&rh1, rcu_torture_leak_cb); /* Start grace period. */
	local_irq_disable(); /* Make it harder to start a new grace period. */
	call_rcu(&rh2, rcu_torture_leak_cb);
	call_rcu(&rh2, rcu_torture_err_cb); /* Duplicate callback. */
	अगर (rhp) अणु
		call_rcu(rhp, rcu_torture_leak_cb);
		call_rcu(rhp, rcu_torture_err_cb); /* Another duplicate callback. */
	पूर्ण
	local_irq_enable();
	rcu_पढ़ो_unlock();
	preempt_enable();

	/* Wait क्रम them all to get करोne so we can safely वापस. */
	rcu_barrier();
	pr_alert("%s: WARN: Duplicate call_rcu() test complete.\n", KBUILD_MODNAME);
	destroy_rcu_head_on_stack(&rh1);
	destroy_rcu_head_on_stack(&rh2);
#अन्यथा /* #अगर_घोषित CONFIG_DEBUG_OBJECTS_RCU_HEAD */
	pr_alert("%s: !CONFIG_DEBUG_OBJECTS_RCU_HEAD, not testing duplicate call_rcu()\n", KBUILD_MODNAME);
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_DEBUG_OBJECTS_RCU_HEAD */
पूर्ण

अटल व्योम rcutorture_sync(व्योम)
अणु
	अटल अचिन्हित दीर्घ n;

	अगर (cur_ops->sync && !(++n & 0xfff))
		cur_ops->sync();
पूर्ण

अटल पूर्णांक __init
rcu_torture_init(व्योम)
अणु
	दीर्घ i;
	पूर्णांक cpu;
	पूर्णांक firsterr = 0;
	पूर्णांक flags = 0;
	अचिन्हित दीर्घ gp_seq = 0;
	अटल काष्ठा rcu_torture_ops *torture_ops[] = अणु
		&rcu_ops, &rcu_busted_ops, &srcu_ops, &srcud_ops,
		&busted_srcud_ops, &tasks_ops, &tasks_rude_ops,
		&tasks_tracing_ops, &trivial_ops,
	पूर्ण;

	अगर (!torture_init_begin(torture_type, verbose))
		वापस -EBUSY;

	/* Process args and tell the world that the torturer is on the job. */
	क्रम (i = 0; i < ARRAY_SIZE(torture_ops); i++) अणु
		cur_ops = torture_ops[i];
		अगर (म_भेद(torture_type, cur_ops->name) == 0)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(torture_ops)) अणु
		pr_alert("rcu-torture: invalid torture type: \"%s\"\n",
			 torture_type);
		pr_alert("rcu-torture types:");
		क्रम (i = 0; i < ARRAY_SIZE(torture_ops); i++)
			pr_cont(" %s", torture_ops[i]->name);
		pr_cont("\n");
		firsterr = -EINVAL;
		cur_ops = शून्य;
		जाओ unwind;
	पूर्ण
	अगर (cur_ops->fqs == शून्य && fqs_duration != 0) अणु
		pr_alert("rcu-torture: ->fqs NULL and non-zero fqs_duration, fqs disabled.\n");
		fqs_duration = 0;
	पूर्ण
	अगर (cur_ops->init)
		cur_ops->init();

	अगर (nपढ़ोers >= 0) अणु
		nrealपढ़ोers = nपढ़ोers;
	पूर्ण अन्यथा अणु
		nrealपढ़ोers = num_online_cpus() - 2 - nपढ़ोers;
		अगर (nrealपढ़ोers <= 0)
			nrealपढ़ोers = 1;
	पूर्ण
	rcu_torture_prपूर्णांक_module_parms(cur_ops, "Start of test");
	rcutorture_get_gp_data(cur_ops->ttype, &flags, &gp_seq);
	srcutorture_get_gp_data(cur_ops->ttype, srcu_ctlp, &flags, &gp_seq);
	start_gp_seq = gp_seq;
	pr_alert("%s:  Start-test grace-period state: g%ld f%#x\n",
		 cur_ops->name, (दीर्घ)gp_seq, flags);

	/* Set up the मुक्तlist. */

	INIT_LIST_HEAD(&rcu_torture_मुक्तlist);
	क्रम (i = 0; i < ARRAY_SIZE(rcu_tortures); i++) अणु
		rcu_tortures[i].rtort_mbtest = 0;
		list_add_tail(&rcu_tortures[i].rtort_मुक्त,
			      &rcu_torture_मुक्तlist);
	पूर्ण

	/* Initialize the statistics so that each run माला_लो its own numbers. */

	rcu_torture_current = शून्य;
	rcu_torture_current_version = 0;
	atomic_set(&n_rcu_torture_alloc, 0);
	atomic_set(&n_rcu_torture_alloc_fail, 0);
	atomic_set(&n_rcu_torture_मुक्त, 0);
	atomic_set(&n_rcu_torture_mberror, 0);
	atomic_set(&n_rcu_torture_mbchk_fail, 0);
	atomic_set(&n_rcu_torture_mbchk_tries, 0);
	atomic_set(&n_rcu_torture_error, 0);
	n_rcu_torture_barrier_error = 0;
	n_rcu_torture_boost_ktrerror = 0;
	n_rcu_torture_boost_rterror = 0;
	n_rcu_torture_boost_failure = 0;
	n_rcu_torture_boosts = 0;
	क्रम (i = 0; i < RCU_TORTURE_PIPE_LEN + 1; i++)
		atomic_set(&rcu_torture_wcount[i], 0);
	क्रम_each_possible_cpu(cpu) अणु
		क्रम (i = 0; i < RCU_TORTURE_PIPE_LEN + 1; i++) अणु
			per_cpu(rcu_torture_count, cpu)[i] = 0;
			per_cpu(rcu_torture_batch, cpu)[i] = 0;
		पूर्ण
	पूर्ण
	err_segs_recorded = 0;
	rt_पढ़ो_nsegs = 0;

	/* Start up the kthपढ़ोs. */

	rcu_torture_ग_लिखो_types();
	firsterr = torture_create_kthपढ़ो(rcu_torture_ग_लिखोr, शून्य,
					  ग_लिखोr_task);
	अगर (firsterr)
		जाओ unwind;
	अगर (nfakeग_लिखोrs > 0) अणु
		fakeग_लिखोr_tasks = kसुस्मृति(nfakeग_लिखोrs,
					   माप(fakeग_लिखोr_tasks[0]),
					   GFP_KERNEL);
		अगर (fakeग_लिखोr_tasks == शून्य) अणु
			VERBOSE_TOROUT_ERRSTRING("out of memory");
			firsterr = -ENOMEM;
			जाओ unwind;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < nfakeग_लिखोrs; i++) अणु
		firsterr = torture_create_kthपढ़ो(rcu_torture_fakeग_लिखोr,
						  शून्य, fakeग_लिखोr_tasks[i]);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण
	पढ़ोer_tasks = kसुस्मृति(nrealपढ़ोers, माप(पढ़ोer_tasks[0]),
			       GFP_KERNEL);
	rcu_torture_पढ़ोer_mbchk = kसुस्मृति(nrealपढ़ोers, माप(*rcu_torture_पढ़ोer_mbchk),
					   GFP_KERNEL);
	अगर (!पढ़ोer_tasks || !rcu_torture_पढ़ोer_mbchk) अणु
		VERBOSE_TOROUT_ERRSTRING("out of memory");
		firsterr = -ENOMEM;
		जाओ unwind;
	पूर्ण
	क्रम (i = 0; i < nrealपढ़ोers; i++) अणु
		rcu_torture_पढ़ोer_mbchk[i].rtc_chkrdr = -1;
		firsterr = torture_create_kthपढ़ो(rcu_torture_पढ़ोer, (व्योम *)i,
						  पढ़ोer_tasks[i]);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण
	nrealnocbers = nocbs_nthपढ़ोs;
	अगर (WARN_ON(nrealnocbers < 0))
		nrealnocbers = 1;
	अगर (WARN_ON(nocbs_toggle < 0))
		nocbs_toggle = HZ;
	अगर (nrealnocbers > 0) अणु
		nocb_tasks = kसुस्मृति(nrealnocbers, माप(nocb_tasks[0]), GFP_KERNEL);
		अगर (nocb_tasks == शून्य) अणु
			VERBOSE_TOROUT_ERRSTRING("out of memory");
			firsterr = -ENOMEM;
			जाओ unwind;
		पूर्ण
	पूर्ण अन्यथा अणु
		nocb_tasks = शून्य;
	पूर्ण
	क्रम (i = 0; i < nrealnocbers; i++) अणु
		firsterr = torture_create_kthपढ़ो(rcu_nocb_toggle, शून्य, nocb_tasks[i]);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण
	अगर (stat_पूर्णांकerval > 0) अणु
		firsterr = torture_create_kthपढ़ो(rcu_torture_stats, शून्य,
						  stats_task);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण
	अगर (test_no_idle_hz && shuffle_पूर्णांकerval > 0) अणु
		firsterr = torture_shuffle_init(shuffle_पूर्णांकerval * HZ);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण
	अगर (stutter < 0)
		stutter = 0;
	अगर (stutter) अणु
		पूर्णांक t;

		t = cur_ops->stall_dur ? cur_ops->stall_dur() : stutter * HZ;
		firsterr = torture_stutter_init(stutter * HZ, t);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण
	अगर (fqs_duration < 0)
		fqs_duration = 0;
	अगर (fqs_duration) अणु
		/* Create the fqs thपढ़ो */
		firsterr = torture_create_kthपढ़ो(rcu_torture_fqs, शून्य,
						  fqs_task);
		अगर (firsterr)
			जाओ unwind;
	पूर्ण
	अगर (test_boost_पूर्णांकerval < 1)
		test_boost_पूर्णांकerval = 1;
	अगर (test_boost_duration < 2)
		test_boost_duration = 2;
	अगर (rcu_torture_can_boost()) अणु

		boost_startसमय = jअगरfies + test_boost_पूर्णांकerval * HZ;

		firsterr = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "RCU_TORTURE",
					     rcutorture_booster_init,
					     rcutorture_booster_cleanup);
		अगर (firsterr < 0)
			जाओ unwind;
		rcutor_hp = firsterr;
	पूर्ण
	shutकरोwn_jअगरfies = jअगरfies + shutकरोwn_secs * HZ;
	firsterr = torture_shutकरोwn_init(shutकरोwn_secs, rcu_torture_cleanup);
	अगर (firsterr)
		जाओ unwind;
	firsterr = torture_onoff_init(onoff_holकरोff * HZ, onoff_पूर्णांकerval,
				      rcutorture_sync);
	अगर (firsterr)
		जाओ unwind;
	firsterr = rcu_torture_stall_init();
	अगर (firsterr)
		जाओ unwind;
	firsterr = rcu_torture_fwd_prog_init();
	अगर (firsterr)
		जाओ unwind;
	firsterr = rcu_torture_barrier_init();
	अगर (firsterr)
		जाओ unwind;
	firsterr = rcu_torture_पढ़ो_निकास_init();
	अगर (firsterr)
		जाओ unwind;
	अगर (object_debug)
		rcu_test_debug_objects();
	torture_init_end();
	वापस 0;

unwind:
	torture_init_end();
	rcu_torture_cleanup();
	अगर (shutकरोwn_secs) अणु
		WARN_ON(!IS_MODULE(CONFIG_RCU_TORTURE_TEST));
		kernel_घातer_off();
	पूर्ण
	वापस firsterr;
पूर्ण

module_init(rcu_torture_init);
module_निकास(rcu_torture_cleanup);
