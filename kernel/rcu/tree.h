<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Read-Copy Update mechanism क्रम mutual exclusion (tree-based version)
 * Internal non-खुला definitions.
 *
 * Copyright IBM Corporation, 2008
 *
 * Author: Ingo Molnar <mingo@elte.hu>
 *	   Paul E. McKenney <paulmck@linux.ibm.com>
 */

#समावेश <linux/cache.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/rपंचांगutex.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/sरुको.h>
#समावेश <linux/rcu_node_tree.h>

#समावेश "rcu_segcblist.h"

/* Communicate arguments to a workqueue handler. */
काष्ठा rcu_exp_work अणु
	अचिन्हित दीर्घ rew_s;
	काष्ठा work_काष्ठा rew_work;
पूर्ण;

/* RCU's kthपढ़ो states क्रम tracing. */
#घोषणा RCU_KTHREAD_STOPPED  0
#घोषणा RCU_KTHREAD_RUNNING  1
#घोषणा RCU_KTHREAD_WAITING  2
#घोषणा RCU_KTHREAD_OFFCPU   3
#घोषणा RCU_KTHREAD_YIELDING 4
#घोषणा RCU_KTHREAD_MAX      4

/*
 * Definition क्रम node within the RCU grace-period-detection hierarchy.
 */
काष्ठा rcu_node अणु
	raw_spinlock_t __निजी lock;	/* Root rcu_node's lock protects */
					/*  some rcu_state fields as well as */
					/*  following. */
	अचिन्हित दीर्घ gp_seq;	/* Track rsp->gp_seq. */
	अचिन्हित दीर्घ gp_seq_needed; /* Track furthest future GP request. */
	अचिन्हित दीर्घ completedqs; /* All QSes करोne क्रम this node. */
	अचिन्हित दीर्घ qsmask;	/* CPUs or groups that need to चयन in */
				/*  order क्रम current grace period to proceed.*/
				/*  In leaf rcu_node, each bit corresponds to */
				/*  an rcu_data काष्ठाure, otherwise, each */
				/*  bit corresponds to a child rcu_node */
				/*  काष्ठाure. */
	अचिन्हित दीर्घ rcu_gp_init_mask;	/* Mask of offline CPUs at GP init. */
	अचिन्हित दीर्घ qsmaskinit;
				/* Per-GP initial value क्रम qsmask. */
				/*  Initialized from ->qsmaskinitnext at the */
				/*  beginning of each grace period. */
	अचिन्हित दीर्घ qsmaskinitnext;
	अचिन्हित दीर्घ ofl_seq;	/* CPU-hotplug operation sequence count. */
				/* Online CPUs क्रम next grace period. */
	अचिन्हित दीर्घ expmask;	/* CPUs or groups that need to check in */
				/*  to allow the current expedited GP */
				/*  to complete. */
	अचिन्हित दीर्घ expmaskinit;
				/* Per-GP initial values क्रम expmask. */
				/*  Initialized from ->expmaskinitnext at the */
				/*  beginning of each expedited GP. */
	अचिन्हित दीर्घ expmaskinitnext;
				/* Online CPUs क्रम next expedited GP. */
				/*  Any CPU that has ever been online will */
				/*  have its bit set. */
	अचिन्हित दीर्घ cbovldmask;
				/* CPUs experiencing callback overload. */
	अचिन्हित दीर्घ ffmask;	/* Fully functional CPUs. */
	अचिन्हित दीर्घ grpmask;	/* Mask to apply to parent qsmask. */
				/*  Only one bit will be set in this mask. */
	पूर्णांक	grplo;		/* lowest-numbered CPU here. */
	पूर्णांक	grphi;		/* highest-numbered CPU here. */
	u8	grpnum;		/* group number क्रम next level up. */
	u8	level;		/* root is at level 0. */
	bool	रुको_blkd_tasks;/* Necessary to रुको क्रम blocked tasks to */
				/*  निकास RCU पढ़ो-side critical sections */
				/*  beक्रमe propagating offline up the */
				/*  rcu_node tree? */
	काष्ठा rcu_node *parent;
	काष्ठा list_head blkd_tasks;
				/* Tasks blocked in RCU पढ़ो-side critical */
				/*  section.  Tasks are placed at the head */
				/*  of this list and age towards the tail. */
	काष्ठा list_head *gp_tasks;
				/* Poपूर्णांकer to the first task blocking the */
				/*  current grace period, or शून्य अगर there */
				/*  is no such task. */
	काष्ठा list_head *exp_tasks;
				/* Poपूर्णांकer to the first task blocking the */
				/*  current expedited grace period, or शून्य */
				/*  अगर there is no such task.  If there */
				/*  is no current expedited grace period, */
				/*  then there can cannot be any such task. */
	काष्ठा list_head *boost_tasks;
				/* Poपूर्णांकer to first task that needs to be */
				/*  priority boosted, or शून्य अगर no priority */
				/*  boosting is needed क्रम this rcu_node */
				/*  काष्ठाure.  If there are no tasks */
				/*  queued on this rcu_node काष्ठाure that */
				/*  are blocking the current grace period, */
				/*  there can be no such task. */
	काष्ठा rt_mutex boost_mtx;
				/* Used only क्रम the priority-boosting */
				/*  side effect, not as a lock. */
	अचिन्हित दीर्घ boost_समय;
				/* When to start boosting (jअगरfies). */
	काष्ठा task_काष्ठा *boost_kthपढ़ो_task;
				/* kthपढ़ो that takes care of priority */
				/*  boosting क्रम this rcu_node काष्ठाure. */
	अचिन्हित पूर्णांक boost_kthपढ़ो_status;
				/* State of boost_kthपढ़ो_task क्रम tracing. */
#अगर_घोषित CONFIG_RCU_NOCB_CPU
	काष्ठा sरुको_queue_head nocb_gp_wq[2];
				/* Place क्रम rcu_nocb_kthपढ़ो() to रुको GP. */
#पूर्ण_अगर /* #अगर_घोषित CONFIG_RCU_NOCB_CPU */
	raw_spinlock_t fqslock ____cacheline_पूर्णांकernodealigned_in_smp;

	spinlock_t exp_lock ____cacheline_पूर्णांकernodealigned_in_smp;
	अचिन्हित दीर्घ exp_seq_rq;
	रुको_queue_head_t exp_wq[4];
	काष्ठा rcu_exp_work rew;
	bool exp_need_flush;	/* Need to flush workitem? */
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

/*
 * Biपंचांगasks in an rcu_node cover the पूर्णांकerval [grplo, grphi] of CPU IDs, and
 * are indexed relative to this पूर्णांकerval rather than the global CPU ID space.
 * This generates the bit क्रम a CPU in node-local masks.
 */
#घोषणा leaf_node_cpu_bit(rnp, cpu) (BIT((cpu) - (rnp)->grplo))

/*
 * Union to allow "aggregate OR" operation on the need क्रम a quiescent
 * state by the normal and expedited grace periods.
 */
जोड़ rcu_noqs अणु
	काष्ठा अणु
		u8 norm;
		u8 exp;
	पूर्ण b; /* Bits. */
	u16 s; /* Set of bits, aggregate OR here. */
पूर्ण;

/* Per-CPU data क्रम पढ़ो-copy update. */
काष्ठा rcu_data अणु
	/* 1) quiescent-state and grace-period handling : */
	अचिन्हित दीर्घ	gp_seq;		/* Track rsp->gp_seq counter. */
	अचिन्हित दीर्घ	gp_seq_needed;	/* Track furthest future GP request. */
	जोड़ rcu_noqs	cpu_no_qs;	/* No QSes yet क्रम this CPU. */
	bool		core_needs_qs;	/* Core रुकोs क्रम quiesc state. */
	bool		beenonline;	/* CPU online at least once. */
	bool		gpwrap;		/* Possible ->gp_seq wrap. */
	bool		exp_deferred_qs; /* This CPU aरुकोing a deferred QS? */
	bool		cpu_started;	/* RCU watching this onlining CPU. */
	काष्ठा rcu_node *mynode;	/* This CPU's leaf of hierarchy */
	अचिन्हित दीर्घ grpmask;		/* Mask to apply to leaf qsmask. */
	अचिन्हित दीर्घ	ticks_this_gp;	/* The number of scheduling-घड़ी */
					/*  ticks this CPU has handled */
					/*  during and after the last grace */
					/* period it is aware of. */
	काष्ठा irq_work defer_qs_iw;	/* Obtain later scheduler attention. */
	bool defer_qs_iw_pending;	/* Scheduler attention pending? */
	काष्ठा work_काष्ठा strict_work;	/* Schedule पढ़ोers क्रम strict GPs. */

	/* 2) batch handling */
	काष्ठा rcu_segcblist cblist;	/* Segmented callback list, with */
					/* dअगरferent callbacks रुकोing क्रम */
					/* dअगरferent grace periods. */
	दीर्घ		qlen_last_fqs_check;
					/* qlen at last check क्रम QS क्रमcing */
	अचिन्हित दीर्घ	n_cbs_invoked;	/* # callbacks invoked since boot. */
	अचिन्हित दीर्घ	n_क्रमce_qs_snap;
					/* did other CPU क्रमce QS recently? */
	दीर्घ		blimit;		/* Upper limit on a processed batch */

	/* 3) dynticks पूर्णांकerface. */
	पूर्णांक dynticks_snap;		/* Per-GP tracking क्रम dynticks. */
	दीर्घ dynticks_nesting;		/* Track process nesting level. */
	दीर्घ dynticks_nmi_nesting;	/* Track irq/NMI nesting level. */
	atomic_t dynticks;		/* Even value क्रम idle, अन्यथा odd. */
	bool rcu_need_heavy_qs;		/* GP old, so heavy quiescent state! */
	bool rcu_urgent_qs;		/* GP old need light quiescent state. */
	bool rcu_क्रमced_tick;		/* Forced tick to provide QS. */
	bool rcu_क्रमced_tick_exp;	/*   ... provide QS to expedited GP. */
#अगर_घोषित CONFIG_RCU_FAST_NO_HZ
	अचिन्हित दीर्घ last_accelerate;	/* Last jअगरfy CBs were accelerated. */
	अचिन्हित दीर्घ last_advance_all;	/* Last jअगरfy CBs were all advanced. */
	पूर्णांक tick_nohz_enabled_snap;	/* Previously seen value from sysfs. */
#पूर्ण_अगर /* #अगर_घोषित CONFIG_RCU_FAST_NO_HZ */

	/* 4) rcu_barrier(), OOM callbacks, and expediting. */
	काष्ठा rcu_head barrier_head;
	पूर्णांक exp_dynticks_snap;		/* Double-check need क्रम IPI. */

	/* 5) Callback offloading. */
#अगर_घोषित CONFIG_RCU_NOCB_CPU
	काष्ठा sरुको_queue_head nocb_cb_wq; /* For nocb kthपढ़ोs to sleep on. */
	काष्ठा sरुको_queue_head nocb_state_wq; /* For offloading state changes */
	काष्ठा task_काष्ठा *nocb_gp_kthपढ़ो;
	raw_spinlock_t nocb_lock;	/* Guard following pair of fields. */
	atomic_t nocb_lock_contended;	/* Contention experienced. */
	पूर्णांक nocb_defer_wakeup;		/* Defer wakeup of nocb_kthपढ़ो. */
	काष्ठा समयr_list nocb_समयr;	/* Enक्रमce finite deferral. */
	अचिन्हित दीर्घ nocb_gp_adv_समय;	/* Last call_rcu() CB adv (jअगरfies). */

	/* The following fields are used by call_rcu, hence own cacheline. */
	raw_spinlock_t nocb_bypass_lock ____cacheline_पूर्णांकernodealigned_in_smp;
	काष्ठा rcu_cblist nocb_bypass;	/* Lock-contention-bypass CB list. */
	अचिन्हित दीर्घ nocb_bypass_first; /* Time (jअगरfies) of first enqueue. */
	अचिन्हित दीर्घ nocb_nobypass_last; /* Last ->cblist enqueue (jअगरfies). */
	पूर्णांक nocb_nobypass_count;	/* # ->cblist enqueues at ^^^ समय. */

	/* The following fields are used by GP kthपढ़ो, hence own cacheline. */
	raw_spinlock_t nocb_gp_lock ____cacheline_पूर्णांकernodealigned_in_smp;
	काष्ठा समयr_list nocb_bypass_समयr; /* Force nocb_bypass flush. */
	u8 nocb_gp_sleep;		/* Is the nocb GP thपढ़ो asleep? */
	u8 nocb_gp_bypass;		/* Found a bypass on last scan? */
	u8 nocb_gp_gp;			/* GP to रुको क्रम on last scan? */
	अचिन्हित दीर्घ nocb_gp_seq;	/*  If so, ->gp_seq to रुको क्रम. */
	अचिन्हित दीर्घ nocb_gp_loops;	/* # passes through रुको code. */
	काष्ठा sरुको_queue_head nocb_gp_wq; /* For nocb kthपढ़ोs to sleep on. */
	bool nocb_cb_sleep;		/* Is the nocb CB thपढ़ो asleep? */
	काष्ठा task_काष्ठा *nocb_cb_kthपढ़ो;
	काष्ठा rcu_data *nocb_next_cb_rdp;
					/* Next rcu_data in wakeup chain. */

	/* The following fields are used by CB kthपढ़ो, hence new cacheline. */
	काष्ठा rcu_data *nocb_gp_rdp ____cacheline_पूर्णांकernodealigned_in_smp;
					/* GP rdp takes GP-end wakeups. */
#पूर्ण_अगर /* #अगर_घोषित CONFIG_RCU_NOCB_CPU */

	/* 6) RCU priority boosting. */
	काष्ठा task_काष्ठा *rcu_cpu_kthपढ़ो_task;
					/* rcuc per-CPU kthपढ़ो or शून्य. */
	अचिन्हित पूर्णांक rcu_cpu_kthपढ़ो_status;
	अक्षर rcu_cpu_has_work;

	/* 7) Diagnostic data, including RCU CPU stall warnings. */
	अचिन्हित पूर्णांक softirq_snap;	/* Snapshot of softirq activity. */
	/* ->rcu_iw* fields रक्षित by leaf rcu_node ->lock. */
	काष्ठा irq_work rcu_iw;		/* Check क्रम non-irq activity. */
	bool rcu_iw_pending;		/* Is ->rcu_iw pending? */
	अचिन्हित दीर्घ rcu_iw_gp_seq;	/* ->gp_seq associated with ->rcu_iw. */
	अचिन्हित दीर्घ rcu_ofl_gp_seq;	/* ->gp_seq at last offline. */
	लघु rcu_ofl_gp_flags;		/* ->gp_flags at last offline. */
	अचिन्हित दीर्घ rcu_onl_gp_seq;	/* ->gp_seq at last online. */
	लघु rcu_onl_gp_flags;		/* ->gp_flags at last online. */
	अचिन्हित दीर्घ last_fqs_resched;	/* Time of last rcu_resched(). */

	पूर्णांक cpu;
पूर्ण;

/* Values क्रम nocb_defer_wakeup field in काष्ठा rcu_data. */
#घोषणा RCU_NOCB_WAKE_OFF	-1
#घोषणा RCU_NOCB_WAKE_NOT	0
#घोषणा RCU_NOCB_WAKE		1
#घोषणा RCU_NOCB_WAKE_FORCE	2

#घोषणा RCU_JIFFIES_TILL_FORCE_QS (1 + (HZ > 250) + (HZ > 500))
					/* For jअगरfies_till_first_fqs and */
					/*  and jअगरfies_till_next_fqs. */

#घोषणा RCU_JIFFIES_FQS_DIV	256	/* Very large प्रणालीs need more */
					/*  delay between bouts of */
					/*  quiescent-state क्रमcing. */

#घोषणा RCU_STALL_RAT_DELAY	2	/* Allow other CPUs समय to take */
					/*  at least one scheduling घड़ी */
					/*  irq beक्रमe ratting on them. */

#घोषणा rcu_रुको(cond)							\
करो अणु									\
	क्रम (;;) अणु							\
		set_current_state(TASK_INTERRUPTIBLE);			\
		अगर (cond)						\
			अवरोध;						\
		schedule();						\
	पूर्ण								\
	__set_current_state(TASK_RUNNING);				\
पूर्ण जबतक (0)

/*
 * RCU global state, including node hierarchy.  This hierarchy is
 * represented in "heap" क्रमm in a dense array.  The root (first level)
 * of the hierarchy is in ->node[0] (referenced by ->level[0]), the second
 * level in ->node[1] through ->node[m] (->node[1] referenced by ->level[1]),
 * and the third level in ->node[m+1] and following (->node[m+1] referenced
 * by ->level[2]).  The number of levels is determined by the number of
 * CPUs and by CONFIG_RCU_FANOUT.  Small प्रणालीs will have a "hierarchy"
 * consisting of a single rcu_node.
 */
काष्ठा rcu_state अणु
	काष्ठा rcu_node node[NUM_RCU_NODES];	/* Hierarchy. */
	काष्ठा rcu_node *level[RCU_NUM_LVLS + 1];
						/* Hierarchy levels (+1 to */
						/*  shut bogus gcc warning) */
	पूर्णांक ncpus;				/* # CPUs seen so far. */
	पूर्णांक n_online_cpus;			/* # CPUs online क्रम RCU. */

	/* The following fields are guarded by the root rcu_node's lock. */

	u8	boost ____cacheline_पूर्णांकernodealigned_in_smp;
						/* Subject to priority boost. */
	अचिन्हित दीर्घ gp_seq;			/* Grace-period sequence #. */
	अचिन्हित दीर्घ gp_max;			/* Maximum GP duration in */
						/*  jअगरfies. */
	काष्ठा task_काष्ठा *gp_kthपढ़ो;		/* Task क्रम grace periods. */
	काष्ठा sरुको_queue_head gp_wq;		/* Where GP task रुकोs. */
	लघु gp_flags;				/* Commands क्रम GP task. */
	लघु gp_state;				/* GP kthपढ़ो sleep state. */
	अचिन्हित दीर्घ gp_wake_समय;		/* Last GP kthपढ़ो wake. */
	अचिन्हित दीर्घ gp_wake_seq;		/* ->gp_seq at ^^^. */

	/* End of fields guarded by root rcu_node's lock. */

	काष्ठा mutex barrier_mutex;		/* Guards barrier fields. */
	atomic_t barrier_cpu_count;		/* # CPUs रुकोing on. */
	काष्ठा completion barrier_completion;	/* Wake at barrier end. */
	अचिन्हित दीर्घ barrier_sequence;		/* ++ at start and end of */
						/*  rcu_barrier(). */
	/* End of fields guarded by barrier_mutex. */

	काष्ठा mutex exp_mutex;			/* Serialize expedited GP. */
	काष्ठा mutex exp_wake_mutex;		/* Serialize wakeup. */
	अचिन्हित दीर्घ expedited_sequence;	/* Take a ticket. */
	atomic_t expedited_need_qs;		/* # CPUs left to check in. */
	काष्ठा sरुको_queue_head expedited_wq;	/* Wait क्रम check-ins. */
	पूर्णांक ncpus_snap;				/* # CPUs seen last समय. */
	u8 cbovld;				/* Callback overload now? */
	u8 cbovldnext;				/* ^        ^  next समय? */

	अचिन्हित दीर्घ jअगरfies_क्रमce_qs;		/* Time at which to invoke */
						/*  क्रमce_quiescent_state(). */
	अचिन्हित दीर्घ jअगरfies_kick_kthपढ़ोs;	/* Time at which to kick */
						/*  kthपढ़ोs, अगर configured. */
	अचिन्हित दीर्घ n_क्रमce_qs;		/* Number of calls to */
						/*  क्रमce_quiescent_state(). */
	अचिन्हित दीर्घ gp_start;			/* Time at which GP started, */
						/*  but in jअगरfies. */
	अचिन्हित दीर्घ gp_end;			/* Time last GP ended, again */
						/*  in jअगरfies. */
	अचिन्हित दीर्घ gp_activity;		/* Time of last GP kthपढ़ो */
						/*  activity in jअगरfies. */
	अचिन्हित दीर्घ gp_req_activity;		/* Time of last GP request */
						/*  in jअगरfies. */
	अचिन्हित दीर्घ jअगरfies_stall;		/* Time at which to check */
						/*  क्रम CPU stalls. */
	अचिन्हित दीर्घ jअगरfies_resched;		/* Time at which to resched */
						/*  a reluctant CPU. */
	अचिन्हित दीर्घ n_क्रमce_qs_gpstart;	/* Snapshot of n_क्रमce_qs at */
						/*  GP start. */
	स्थिर अक्षर *name;			/* Name of काष्ठाure. */
	अक्षर abbr;				/* Abbreviated name. */

	raw_spinlock_t ofl_lock ____cacheline_पूर्णांकernodealigned_in_smp;
						/* Synchronize offline with */
						/*  GP pre-initialization. */
पूर्ण;

/* Values क्रम rcu_state काष्ठाure's gp_flags field. */
#घोषणा RCU_GP_FLAG_INIT 0x1	/* Need grace-period initialization. */
#घोषणा RCU_GP_FLAG_FQS  0x2	/* Need grace-period quiescent-state क्रमcing. */
#घोषणा RCU_GP_FLAG_OVLD 0x4	/* Experiencing callback overload. */

/* Values क्रम rcu_state काष्ठाure's gp_state field. */
#घोषणा RCU_GP_IDLE	 0	/* Initial state and no GP in progress. */
#घोषणा RCU_GP_WAIT_GPS  1	/* Wait क्रम grace-period start. */
#घोषणा RCU_GP_DONE_GPS  2	/* Wait करोne क्रम grace-period start. */
#घोषणा RCU_GP_ONOFF     3	/* Grace-period initialization hotplug. */
#घोषणा RCU_GP_INIT      4	/* Grace-period initialization. */
#घोषणा RCU_GP_WAIT_FQS  5	/* Wait क्रम क्रमce-quiescent-state समय. */
#घोषणा RCU_GP_DOING_FQS 6	/* Wait करोne क्रम क्रमce-quiescent-state समय. */
#घोषणा RCU_GP_CLEANUP   7	/* Grace-period cleanup started. */
#घोषणा RCU_GP_CLEANED   8	/* Grace-period cleanup complete. */

/*
 * In order to export the rcu_state name to the tracing tools, it
 * needs to be added in the __tracepoपूर्णांक_string section.
 * This requires defining a separate variable tp_<sname>_varname
 * that poपूर्णांकs to the string being used, and this will allow
 * the tracing userspace tools to be able to decipher the string
 * address to the matching string.
 */
#अगर_घोषित CONFIG_PREEMPT_RCU
#घोषणा RCU_ABBR 'p'
#घोषणा RCU_NAME_RAW "rcu_preempt"
#अन्यथा /* #अगर_घोषित CONFIG_PREEMPT_RCU */
#घोषणा RCU_ABBR 's'
#घोषणा RCU_NAME_RAW "rcu_sched"
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_PREEMPT_RCU */
#अगर_अघोषित CONFIG_TRACING
#घोषणा RCU_NAME RCU_NAME_RAW
#अन्यथा /* #अगर_घोषित CONFIG_TRACING */
अटल अक्षर rcu_name[] = RCU_NAME_RAW;
अटल स्थिर अक्षर *tp_rcu_varname __used __tracepoपूर्णांक_string = rcu_name;
#घोषणा RCU_NAME rcu_name
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_TRACING */

/* Forward declarations क्रम tree_plugin.h */
अटल व्योम rcu_bootup_announce(व्योम);
अटल व्योम rcu_qs(व्योम);
अटल पूर्णांक rcu_preempt_blocked_पढ़ोers_cgp(काष्ठा rcu_node *rnp);
#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल bool rcu_preempt_has_tasks(काष्ठा rcu_node *rnp);
#पूर्ण_अगर /* #अगर_घोषित CONFIG_HOTPLUG_CPU */
अटल पूर्णांक rcu_prपूर्णांक_task_exp_stall(काष्ठा rcu_node *rnp);
अटल व्योम rcu_preempt_check_blocked_tasks(काष्ठा rcu_node *rnp);
अटल व्योम rcu_flavor_sched_घड़ी_irq(पूर्णांक user);
अटल व्योम dump_blkd_tasks(काष्ठा rcu_node *rnp, पूर्णांक ncheck);
अटल व्योम rcu_initiate_boost(काष्ठा rcu_node *rnp, अचिन्हित दीर्घ flags);
अटल व्योम rcu_preempt_boost_start_gp(काष्ठा rcu_node *rnp);
अटल bool rcu_is_callbacks_kthपढ़ो(व्योम);
अटल व्योम rcu_cpu_kthपढ़ो_setup(अचिन्हित पूर्णांक cpu);
अटल व्योम __init rcu_spawn_boost_kthपढ़ोs(व्योम);
अटल व्योम rcu_prepare_kthपढ़ोs(पूर्णांक cpu);
अटल व्योम rcu_cleanup_after_idle(व्योम);
अटल व्योम rcu_prepare_क्रम_idle(व्योम);
अटल bool rcu_preempt_has_tasks(काष्ठा rcu_node *rnp);
अटल bool rcu_preempt_need_deferred_qs(काष्ठा task_काष्ठा *t);
अटल व्योम rcu_preempt_deferred_qs(काष्ठा task_काष्ठा *t);
अटल व्योम zero_cpu_stall_ticks(काष्ठा rcu_data *rdp);
अटल काष्ठा sरुको_queue_head *rcu_nocb_gp_get(काष्ठा rcu_node *rnp);
अटल व्योम rcu_nocb_gp_cleanup(काष्ठा sरुको_queue_head *sq);
अटल व्योम rcu_init_one_nocb(काष्ठा rcu_node *rnp);
अटल bool rcu_nocb_flush_bypass(काष्ठा rcu_data *rdp, काष्ठा rcu_head *rhp,
				  अचिन्हित दीर्घ j);
अटल bool rcu_nocb_try_bypass(काष्ठा rcu_data *rdp, काष्ठा rcu_head *rhp,
				bool *was_allकरोne, अचिन्हित दीर्घ flags);
अटल व्योम __call_rcu_nocb_wake(काष्ठा rcu_data *rdp, bool was_empty,
				 अचिन्हित दीर्घ flags);
अटल पूर्णांक rcu_nocb_need_deferred_wakeup(काष्ठा rcu_data *rdp);
अटल bool करो_nocb_deferred_wakeup(काष्ठा rcu_data *rdp);
अटल व्योम rcu_boot_init_nocb_percpu_data(काष्ठा rcu_data *rdp);
अटल व्योम rcu_spawn_cpu_nocb_kthपढ़ो(पूर्णांक cpu);
अटल व्योम __init rcu_spawn_nocb_kthपढ़ोs(व्योम);
अटल व्योम show_rcu_nocb_state(काष्ठा rcu_data *rdp);
अटल व्योम rcu_nocb_lock(काष्ठा rcu_data *rdp);
अटल व्योम rcu_nocb_unlock(काष्ठा rcu_data *rdp);
अटल व्योम rcu_nocb_unlock_irqrestore(काष्ठा rcu_data *rdp,
				       अचिन्हित दीर्घ flags);
अटल व्योम rcu_lockdep_निश्चित_cblist_रक्षित(काष्ठा rcu_data *rdp);
#अगर_घोषित CONFIG_RCU_NOCB_CPU
अटल व्योम __init rcu_organize_nocb_kthपढ़ोs(व्योम);
#घोषणा rcu_nocb_lock_irqsave(rdp, flags)				\
करो अणु									\
	अगर (!rcu_segcblist_is_offloaded(&(rdp)->cblist))		\
		local_irq_save(flags);					\
	अन्यथा								\
		raw_spin_lock_irqsave(&(rdp)->nocb_lock, (flags));	\
पूर्ण जबतक (0)
#अन्यथा /* #अगर_घोषित CONFIG_RCU_NOCB_CPU */
#घोषणा rcu_nocb_lock_irqsave(rdp, flags) local_irq_save(flags)
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_RCU_NOCB_CPU */

अटल व्योम rcu_bind_gp_kthपढ़ो(व्योम);
अटल bool rcu_nohz_full_cpu(व्योम);
अटल व्योम rcu_dynticks_task_enter(व्योम);
अटल व्योम rcu_dynticks_task_निकास(व्योम);
अटल व्योम rcu_dynticks_task_trace_enter(व्योम);
अटल व्योम rcu_dynticks_task_trace_निकास(व्योम);

/* Forward declarations क्रम tree_stall.h */
अटल व्योम record_gp_stall_check_समय(व्योम);
अटल व्योम rcu_iw_handler(काष्ठा irq_work *iwp);
अटल व्योम check_cpu_stall(काष्ठा rcu_data *rdp);
अटल व्योम rcu_check_gp_start_stall(काष्ठा rcu_node *rnp, काष्ठा rcu_data *rdp,
				     स्थिर अचिन्हित दीर्घ gpssdelay);
