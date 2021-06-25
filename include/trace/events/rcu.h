<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM rcu

#अगर !defined(_TRACE_RCU_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_RCU_H

#समावेश <linux/tracepoपूर्णांक.h>

#अगर_घोषित CONFIG_RCU_TRACE
#घोषणा TRACE_EVENT_RCU TRACE_EVENT
#अन्यथा
#घोषणा TRACE_EVENT_RCU TRACE_EVENT_NOP
#पूर्ण_अगर

/*
 * Tracepoपूर्णांक क्रम start/end markers used क्रम utilization calculations.
 * By convention, the string is of the following क्रमms:
 *
 * "Start <activity>" -- Mark the start of the specअगरied activity,
 *			 such as "context switch".  Nesting is permitted.
 * "End <activity>" -- Mark the end of the specअगरied activity.
 *
 * An "@" अक्षरacter within "<activity>" is a comment अक्षरacter: Data
 * reduction scripts will ignore the "@" and the reमुख्यder of the line.
 */
TRACE_EVENT(rcu_utilization,

	TP_PROTO(स्थिर अक्षर *s),

	TP_ARGS(s),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, s)
	),

	TP_fast_assign(
		__entry->s = s;
	),

	TP_prपूर्णांकk("%s", __entry->s)
);

#अगर defined(CONFIG_TREE_RCU)

/*
 * Tracepoपूर्णांक क्रम grace-period events.  Takes a string identअगरying the
 * RCU flavor, the grace-period number, and a string identअगरying the
 * grace-period-related event as follows:
 *
 *	"AccReadyCB": CPU accelerates new callbacks to RCU_NEXT_READY_TAIL.
 *	"AccWaitCB": CPU accelerates new callbacks to RCU_WAIT_TAIL.
 *	"newreq": Request a new grace period.
 *	"start": Start a grace period.
 *	"cpustart": CPU first notices a grace-period start.
 *	"cpuqs": CPU passes through a quiescent state.
 *	"cpuonl": CPU comes online.
 *	"cpuofl": CPU goes offline.
 *	"cpuofl-bgp": CPU goes offline जबतक blocking a grace period.
 *	"reqwait": GP kthपढ़ो sleeps रुकोing क्रम grace-period request.
 *	"reqwaitsig": GP kthपढ़ो awakened by संकेत from reqरुको state.
 *	"fqswait": GP kthपढ़ो रुकोing until समय to क्रमce quiescent states.
 *	"fqsstart": GP kthपढ़ो starts क्रमcing quiescent states.
 *	"fqsend": GP kthपढ़ो करोne क्रमcing quiescent states.
 *	"fqswaitsig": GP kthपढ़ो awakened by संकेत from fqsरुको state.
 *	"end": End a grace period.
 *	"cpuend": CPU first notices a grace-period end.
 */
TRACE_EVENT_RCU(rcu_grace_period,

	TP_PROTO(स्थिर अक्षर *rcuname, अचिन्हित दीर्घ gp_seq, स्थिर अक्षर *gpevent),

	TP_ARGS(rcuname, gp_seq, gpevent),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, rcuname)
		__field(दीर्घ, gp_seq)
		__field(स्थिर अक्षर *, gpevent)
	),

	TP_fast_assign(
		__entry->rcuname = rcuname;
		__entry->gp_seq = (दीर्घ)gp_seq;
		__entry->gpevent = gpevent;
	),

	TP_prपूर्णांकk("%s %ld %s",
		  __entry->rcuname, __entry->gp_seq, __entry->gpevent)
);

/*
 * Tracepoपूर्णांक क्रम future grace-period events.  The caller should pull
 * the data from the rcu_node काष्ठाure, other than rcuname, which comes
 * from the rcu_state काष्ठाure, and event, which is one of the following:
 *
 * "Cleanup": Clean up rcu_node काष्ठाure after previous GP.
 * "CleanupMore": Clean up, and another GP is needed.
 * "EndWait": Complete रुको.
 * "NoGPkthread": The RCU grace-period kthपढ़ो has not yet started.
 * "Prestarted": Someone beat us to the request
 * "Startedleaf": Leaf node marked क्रम future GP.
 * "Startedleafroot": All nodes from leaf to root marked क्रम future GP.
 * "Startedroot": Requested a nocb grace period based on root-node data.
 * "Startleaf": Request a grace period based on leaf-node data.
 * "StartWait": Start रुकोing क्रम the requested grace period.
 */
TRACE_EVENT_RCU(rcu_future_grace_period,

	TP_PROTO(स्थिर अक्षर *rcuname, अचिन्हित दीर्घ gp_seq,
		 अचिन्हित दीर्घ gp_seq_req, u8 level, पूर्णांक grplo, पूर्णांक grphi,
		 स्थिर अक्षर *gpevent),

	TP_ARGS(rcuname, gp_seq, gp_seq_req, level, grplo, grphi, gpevent),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, rcuname)
		__field(दीर्घ, gp_seq)
		__field(दीर्घ, gp_seq_req)
		__field(u8, level)
		__field(पूर्णांक, grplo)
		__field(पूर्णांक, grphi)
		__field(स्थिर अक्षर *, gpevent)
	),

	TP_fast_assign(
		__entry->rcuname = rcuname;
		__entry->gp_seq = (दीर्घ)gp_seq;
		__entry->gp_seq_req = (दीर्घ)gp_seq_req;
		__entry->level = level;
		__entry->grplo = grplo;
		__entry->grphi = grphi;
		__entry->gpevent = gpevent;
	),

	TP_prपूर्णांकk("%s %ld %ld %u %d %d %s",
		  __entry->rcuname, (दीर्घ)__entry->gp_seq, (दीर्घ)__entry->gp_seq_req, __entry->level,
		  __entry->grplo, __entry->grphi, __entry->gpevent)
);

/*
 * Tracepoपूर्णांक क्रम grace-period-initialization events.  These are
 * distinguished by the type of RCU, the new grace-period number, the
 * rcu_node काष्ठाure level, the starting and ending CPU covered by the
 * rcu_node काष्ठाure, and the mask of CPUs that will be रुकोed क्रम.
 * All but the type of RCU are extracted from the rcu_node काष्ठाure.
 */
TRACE_EVENT_RCU(rcu_grace_period_init,

	TP_PROTO(स्थिर अक्षर *rcuname, अचिन्हित दीर्घ gp_seq, u8 level,
		 पूर्णांक grplo, पूर्णांक grphi, अचिन्हित दीर्घ qsmask),

	TP_ARGS(rcuname, gp_seq, level, grplo, grphi, qsmask),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, rcuname)
		__field(दीर्घ, gp_seq)
		__field(u8, level)
		__field(पूर्णांक, grplo)
		__field(पूर्णांक, grphi)
		__field(अचिन्हित दीर्घ, qsmask)
	),

	TP_fast_assign(
		__entry->rcuname = rcuname;
		__entry->gp_seq = (दीर्घ)gp_seq;
		__entry->level = level;
		__entry->grplo = grplo;
		__entry->grphi = grphi;
		__entry->qsmask = qsmask;
	),

	TP_prपूर्णांकk("%s %ld %u %d %d %lx",
		  __entry->rcuname, __entry->gp_seq, __entry->level,
		  __entry->grplo, __entry->grphi, __entry->qsmask)
);

/*
 * Tracepoपूर्णांक क्रम expedited grace-period events.  Takes a string identअगरying
 * the RCU flavor, the expedited grace-period sequence number, and a string
 * identअगरying the grace-period-related event as follows:
 *
 *	"snap": Captured snapshot of expedited grace period sequence number.
 *	"start": Started a real expedited grace period.
 *	"reset": Started resetting the tree
 *	"select": Started selecting the CPUs to रुको on.
 *	"selectofl": Selected CPU partially offline.
 *	"startwait": Started रुकोing on selected CPUs.
 *	"end": Ended a real expedited grace period.
 *	"endwake": Woke piggybackers up.
 *	"done": Someone अन्यथा did the expedited grace period क्रम us.
 */
TRACE_EVENT_RCU(rcu_exp_grace_period,

	TP_PROTO(स्थिर अक्षर *rcuname, अचिन्हित दीर्घ gpseq, स्थिर अक्षर *gpevent),

	TP_ARGS(rcuname, gpseq, gpevent),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, rcuname)
		__field(दीर्घ, gpseq)
		__field(स्थिर अक्षर *, gpevent)
	),

	TP_fast_assign(
		__entry->rcuname = rcuname;
		__entry->gpseq = (दीर्घ)gpseq;
		__entry->gpevent = gpevent;
	),

	TP_prपूर्णांकk("%s %ld %s",
		  __entry->rcuname, __entry->gpseq, __entry->gpevent)
);

/*
 * Tracepoपूर्णांक क्रम expedited grace-period funnel-locking events.  Takes a
 * string identअगरying the RCU flavor, an पूर्णांकeger identअगरying the rcu_node
 * combining-tree level, another pair of पूर्णांकegers identअगरying the lowest-
 * and highest-numbered CPU associated with the current rcu_node काष्ठाure,
 * and a string.  identअगरying the grace-period-related event as follows:
 *
 *	"nxtlvl": Advance to next level of rcu_node funnel
 *	"wait": Wait क्रम someone अन्यथा to करो expedited GP
 */
TRACE_EVENT_RCU(rcu_exp_funnel_lock,

	TP_PROTO(स्थिर अक्षर *rcuname, u8 level, पूर्णांक grplo, पूर्णांक grphi,
		 स्थिर अक्षर *gpevent),

	TP_ARGS(rcuname, level, grplo, grphi, gpevent),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, rcuname)
		__field(u8, level)
		__field(पूर्णांक, grplo)
		__field(पूर्णांक, grphi)
		__field(स्थिर अक्षर *, gpevent)
	),

	TP_fast_assign(
		__entry->rcuname = rcuname;
		__entry->level = level;
		__entry->grplo = grplo;
		__entry->grphi = grphi;
		__entry->gpevent = gpevent;
	),

	TP_prपूर्णांकk("%s %d %d %d %s",
		  __entry->rcuname, __entry->level, __entry->grplo,
		  __entry->grphi, __entry->gpevent)
);

#अगर_घोषित CONFIG_RCU_NOCB_CPU
/*
 * Tracepoपूर्णांक क्रम RCU no-CBs CPU callback hanकरोffs.  This event is पूर्णांकended
 * to assist debugging of these hanकरोffs.
 *
 * The first argument is the name of the RCU flavor, and the second is
 * the number of the offloaded CPU are extracted.  The third and final
 * argument is a string as follows:
 *
 * "AlreadyAwake": The to-be-awakened rcuo kthपढ़ो is alपढ़ोy awake.
 * "Bypass": rcuo GP kthपढ़ो sees non-empty ->nocb_bypass.
 * "CBSleep": rcuo CB kthपढ़ो sleeping रुकोing क्रम CBs.
 * "Check": rcuo GP kthपढ़ो checking specअगरied CPU क्रम work.
 * "DeferredWake": Timer expired or polled check, समय to wake.
 * "DoWake": The to-be-awakened rcuo kthपढ़ो needs to be awakened.
 * "EndSleep": Done रुकोing क्रम GP क्रम !rcu_nocb_poll.
 * "FirstBQ": New CB to empty ->nocb_bypass (->cblist maybe non-empty).
 * "FirstBQnoWake": FirstBQ plus rcuo kthपढ़ो need not be awakened.
 * "FirstBQwake": FirstBQ plus rcuo kthपढ़ो must be awakened.
 * "FirstQ": New CB to empty ->cblist (->nocb_bypass maybe non-empty).
 * "NeedWaitGP": rcuo GP kthपढ़ो must रुको on a grace period.
 * "Poll": Start of new polling cycle क्रम rcu_nocb_poll.
 * "Sleep": Sleep रुकोing क्रम GP क्रम !rcu_nocb_poll.
 * "Timer": Deferred-wake समयr expired.
 * "WakeEmptyIsDeferred": Wake rcuo kthपढ़ो later, first CB to empty list.
 * "WakeEmpty": Wake rcuo kthपढ़ो, first CB to empty list.
 * "WakeNot": Don't wake rcuo kthपढ़ो.
 * "WakeNotPoll": Don't wake rcuo kthपढ़ो because it is polling.
 * "WakeOvfIsDeferred": Wake rcuo kthपढ़ो later, CB list is huge.
 * "WokeEmpty": rcuo CB kthपढ़ो woke to find empty list.
 */
TRACE_EVENT_RCU(rcu_nocb_wake,

	TP_PROTO(स्थिर अक्षर *rcuname, पूर्णांक cpu, स्थिर अक्षर *reason),

	TP_ARGS(rcuname, cpu, reason),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, rcuname)
		__field(पूर्णांक, cpu)
		__field(स्थिर अक्षर *, reason)
	),

	TP_fast_assign(
		__entry->rcuname = rcuname;
		__entry->cpu = cpu;
		__entry->reason = reason;
	),

	TP_prपूर्णांकk("%s %d %s", __entry->rcuname, __entry->cpu, __entry->reason)
);
#पूर्ण_अगर

/*
 * Tracepoपूर्णांक क्रम tasks blocking within preemptible-RCU पढ़ो-side
 * critical sections.  Track the type of RCU (which one day might
 * include SRCU), the grace-period number that the task is blocking
 * (the current or the next), and the task's PID.
 */
TRACE_EVENT_RCU(rcu_preempt_task,

	TP_PROTO(स्थिर अक्षर *rcuname, पूर्णांक pid, अचिन्हित दीर्घ gp_seq),

	TP_ARGS(rcuname, pid, gp_seq),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, rcuname)
		__field(दीर्घ, gp_seq)
		__field(पूर्णांक, pid)
	),

	TP_fast_assign(
		__entry->rcuname = rcuname;
		__entry->gp_seq = (दीर्घ)gp_seq;
		__entry->pid = pid;
	),

	TP_prपूर्णांकk("%s %ld %d",
		  __entry->rcuname, __entry->gp_seq, __entry->pid)
);

/*
 * Tracepoपूर्णांक क्रम tasks that blocked within a given preemptible-RCU
 * पढ़ो-side critical section निकासing that critical section.  Track the
 * type of RCU (which one day might include SRCU) and the task's PID.
 */
TRACE_EVENT_RCU(rcu_unlock_preempted_task,

	TP_PROTO(स्थिर अक्षर *rcuname, अचिन्हित दीर्घ gp_seq, पूर्णांक pid),

	TP_ARGS(rcuname, gp_seq, pid),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, rcuname)
		__field(दीर्घ, gp_seq)
		__field(पूर्णांक, pid)
	),

	TP_fast_assign(
		__entry->rcuname = rcuname;
		__entry->gp_seq = (दीर्घ)gp_seq;
		__entry->pid = pid;
	),

	TP_prपूर्णांकk("%s %ld %d", __entry->rcuname, __entry->gp_seq, __entry->pid)
);

/*
 * Tracepoपूर्णांक क्रम quiescent-state-reporting events.  These are
 * distinguished by the type of RCU, the grace-period number, the
 * mask of quiescent lower-level entities, the rcu_node काष्ठाure level,
 * the starting and ending CPU covered by the rcu_node काष्ठाure, and
 * whether there are any blocked tasks blocking the current grace period.
 * All but the type of RCU are extracted from the rcu_node काष्ठाure.
 */
TRACE_EVENT_RCU(rcu_quiescent_state_report,

	TP_PROTO(स्थिर अक्षर *rcuname, अचिन्हित दीर्घ gp_seq,
		 अचिन्हित दीर्घ mask, अचिन्हित दीर्घ qsmask,
		 u8 level, पूर्णांक grplo, पूर्णांक grphi, पूर्णांक gp_tasks),

	TP_ARGS(rcuname, gp_seq, mask, qsmask, level, grplo, grphi, gp_tasks),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, rcuname)
		__field(दीर्घ, gp_seq)
		__field(अचिन्हित दीर्घ, mask)
		__field(अचिन्हित दीर्घ, qsmask)
		__field(u8, level)
		__field(पूर्णांक, grplo)
		__field(पूर्णांक, grphi)
		__field(u8, gp_tasks)
	),

	TP_fast_assign(
		__entry->rcuname = rcuname;
		__entry->gp_seq = (दीर्घ)gp_seq;
		__entry->mask = mask;
		__entry->qsmask = qsmask;
		__entry->level = level;
		__entry->grplo = grplo;
		__entry->grphi = grphi;
		__entry->gp_tasks = gp_tasks;
	),

	TP_prपूर्णांकk("%s %ld %lx>%lx %u %d %d %u",
		  __entry->rcuname, __entry->gp_seq,
		  __entry->mask, __entry->qsmask, __entry->level,
		  __entry->grplo, __entry->grphi, __entry->gp_tasks)
);

/*
 * Tracepoपूर्णांक क्रम quiescent states detected by क्रमce_quiescent_state().
 * These trace events include the type of RCU, the grace-period number
 * that was blocked by the CPU, the CPU itself, and the type of quiescent
 * state, which can be "dti" क्रम dyntick-idle mode or "kick" when kicking
 * a CPU that has been in dyntick-idle mode क्रम too दीर्घ.
 */
TRACE_EVENT_RCU(rcu_fqs,

	TP_PROTO(स्थिर अक्षर *rcuname, अचिन्हित दीर्घ gp_seq, पूर्णांक cpu, स्थिर अक्षर *qsevent),

	TP_ARGS(rcuname, gp_seq, cpu, qsevent),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, rcuname)
		__field(दीर्घ, gp_seq)
		__field(पूर्णांक, cpu)
		__field(स्थिर अक्षर *, qsevent)
	),

	TP_fast_assign(
		__entry->rcuname = rcuname;
		__entry->gp_seq = (दीर्घ)gp_seq;
		__entry->cpu = cpu;
		__entry->qsevent = qsevent;
	),

	TP_prपूर्णांकk("%s %ld %d %s",
		  __entry->rcuname, __entry->gp_seq,
		  __entry->cpu, __entry->qsevent)
);

/*
 * Tracepoपूर्णांक क्रम RCU stall events. Takes a string identअगरying the RCU flavor
 * and a string identअगरying which function detected the RCU stall as follows:
 *
 *	"StallDetected": Scheduler-tick detects other CPU's stalls.
 *	"SelfDetected": Scheduler-tick detects a current CPU's stall.
 *	"ExpeditedStall": Expedited grace period detects stalls.
 */
TRACE_EVENT(rcu_stall_warning,

	TP_PROTO(स्थिर अक्षर *rcuname, स्थिर अक्षर *msg),

	TP_ARGS(rcuname, msg),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, rcuname)
		__field(स्थिर अक्षर *, msg)
	),

	TP_fast_assign(
		__entry->rcuname = rcuname;
		__entry->msg = msg;
	),

	TP_prपूर्णांकk("%s %s",
		  __entry->rcuname, __entry->msg)
);

#पूर्ण_अगर /* #अगर defined(CONFIG_TREE_RCU) */

/*
 * Tracepoपूर्णांक क्रम dyntick-idle entry/निकास events.  These take 2 strings
 * as argument:
 * polarity: "Start", "End", "StillNonIdle" क्रम entering, निकासing or still not
 *            being in dyntick-idle mode.
 * context: "USER" or "IDLE" or "IRQ".
 * NMIs nested in IRQs are inferred with dynticks_nesting > 1 in IRQ context.
 *
 * These events also take a pair of numbers, which indicate the nesting
 * depth beक्रमe and after the event of पूर्णांकerest, and a third number that is
 * the ->dynticks counter.  Note that task-related and पूर्णांकerrupt-related
 * events use two separate counters, and that the "++=" and "--=" events
 * क्रम irq/NMI will change the counter by two, otherwise by one.
 */
TRACE_EVENT_RCU(rcu_dyntick,

	TP_PROTO(स्थिर अक्षर *polarity, दीर्घ oldnesting, दीर्घ newnesting, पूर्णांक dynticks),

	TP_ARGS(polarity, oldnesting, newnesting, dynticks),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, polarity)
		__field(दीर्घ, oldnesting)
		__field(दीर्घ, newnesting)
		__field(पूर्णांक, dynticks)
	),

	TP_fast_assign(
		__entry->polarity = polarity;
		__entry->oldnesting = oldnesting;
		__entry->newnesting = newnesting;
		__entry->dynticks = dynticks;
	),

	TP_prपूर्णांकk("%s %lx %lx %#3x", __entry->polarity,
		  __entry->oldnesting, __entry->newnesting,
		  __entry->dynticks & 0xfff)
);

/*
 * Tracepoपूर्णांक क्रम the registration of a single RCU callback function.
 * The first argument is the type of RCU, the second argument is
 * a poपूर्णांकer to the RCU callback itself, the third element is the
 * number of lazy callbacks queued, and the fourth element is the
 * total number of callbacks queued.
 */
TRACE_EVENT_RCU(rcu_callback,

	TP_PROTO(स्थिर अक्षर *rcuname, काष्ठा rcu_head *rhp, दीर्घ qlen),

	TP_ARGS(rcuname, rhp, qlen),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, rcuname)
		__field(व्योम *, rhp)
		__field(व्योम *, func)
		__field(दीर्घ, qlen)
	),

	TP_fast_assign(
		__entry->rcuname = rcuname;
		__entry->rhp = rhp;
		__entry->func = rhp->func;
		__entry->qlen = qlen;
	),

	TP_prपूर्णांकk("%s rhp=%p func=%ps %ld",
		  __entry->rcuname, __entry->rhp, __entry->func,
		  __entry->qlen)
);

TRACE_EVENT_RCU(rcu_segcb_stats,

		TP_PROTO(काष्ठा rcu_segcblist *rs, स्थिर अक्षर *ctx),

		TP_ARGS(rs, ctx),

		TP_STRUCT__entry(
			__field(स्थिर अक्षर *, ctx)
			__array(अचिन्हित दीर्घ, gp_seq, RCU_CBLIST_NSEGS)
			__array(दीर्घ, seglen, RCU_CBLIST_NSEGS)
		),

		TP_fast_assign(
			__entry->ctx = ctx;
			स_नकल(__entry->seglen, rs->seglen, RCU_CBLIST_NSEGS * माप(दीर्घ));
			स_नकल(__entry->gp_seq, rs->gp_seq, RCU_CBLIST_NSEGS * माप(अचिन्हित दीर्घ));

		),

		TP_prपूर्णांकk("%s seglen: (DONE=%ld, WAIT=%ld, NEXT_READY=%ld, NEXT=%ld) "
			  "gp_seq: (DONE=%lu, WAIT=%lu, NEXT_READY=%lu, NEXT=%lu)", __entry->ctx,
			  __entry->seglen[0], __entry->seglen[1], __entry->seglen[2], __entry->seglen[3],
			  __entry->gp_seq[0], __entry->gp_seq[1], __entry->gp_seq[2], __entry->gp_seq[3])

);

/*
 * Tracepoपूर्णांक क्रम the registration of a single RCU callback of the special
 * kvमुक्त() क्रमm.  The first argument is the RCU type, the second argument
 * is a poपूर्णांकer to the RCU callback, the third argument is the offset
 * of the callback within the enclosing RCU-रक्षित data काष्ठाure,
 * the fourth argument is the number of lazy callbacks queued, and the
 * fअगरth argument is the total number of callbacks queued.
 */
TRACE_EVENT_RCU(rcu_kvमुक्त_callback,

	TP_PROTO(स्थिर अक्षर *rcuname, काष्ठा rcu_head *rhp, अचिन्हित दीर्घ offset,
		 दीर्घ qlen),

	TP_ARGS(rcuname, rhp, offset, qlen),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, rcuname)
		__field(व्योम *, rhp)
		__field(अचिन्हित दीर्घ, offset)
		__field(दीर्घ, qlen)
	),

	TP_fast_assign(
		__entry->rcuname = rcuname;
		__entry->rhp = rhp;
		__entry->offset = offset;
		__entry->qlen = qlen;
	),

	TP_prपूर्णांकk("%s rhp=%p func=%ld %ld",
		  __entry->rcuname, __entry->rhp, __entry->offset,
		  __entry->qlen)
);

/*
 * Tracepoपूर्णांक क्रम marking the beginning rcu_करो_batch, perक्रमmed to start
 * RCU callback invocation.  The first argument is the RCU flavor,
 * the second is the number of lazy callbacks queued, the third is
 * the total number of callbacks queued, and the fourth argument is
 * the current RCU-callback batch limit.
 */
TRACE_EVENT_RCU(rcu_batch_start,

	TP_PROTO(स्थिर अक्षर *rcuname, दीर्घ qlen, दीर्घ blimit),

	TP_ARGS(rcuname, qlen, blimit),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, rcuname)
		__field(दीर्घ, qlen)
		__field(दीर्घ, blimit)
	),

	TP_fast_assign(
		__entry->rcuname = rcuname;
		__entry->qlen = qlen;
		__entry->blimit = blimit;
	),

	TP_prपूर्णांकk("%s CBs=%ld bl=%ld",
		  __entry->rcuname, __entry->qlen, __entry->blimit)
);

/*
 * Tracepoपूर्णांक क्रम the invocation of a single RCU callback function.
 * The first argument is the type of RCU, and the second argument is
 * a poपूर्णांकer to the RCU callback itself.
 */
TRACE_EVENT_RCU(rcu_invoke_callback,

	TP_PROTO(स्थिर अक्षर *rcuname, काष्ठा rcu_head *rhp),

	TP_ARGS(rcuname, rhp),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, rcuname)
		__field(व्योम *, rhp)
		__field(व्योम *, func)
	),

	TP_fast_assign(
		__entry->rcuname = rcuname;
		__entry->rhp = rhp;
		__entry->func = rhp->func;
	),

	TP_prपूर्णांकk("%s rhp=%p func=%ps",
		  __entry->rcuname, __entry->rhp, __entry->func)
);

/*
 * Tracepoपूर्णांक क्रम the invocation of a single RCU callback of the special
 * kvमुक्त() क्रमm.  The first argument is the RCU flavor, the second
 * argument is a poपूर्णांकer to the RCU callback, and the third argument
 * is the offset of the callback within the enclosing RCU-रक्षित
 * data काष्ठाure.
 */
TRACE_EVENT_RCU(rcu_invoke_kvमुक्त_callback,

	TP_PROTO(स्थिर अक्षर *rcuname, काष्ठा rcu_head *rhp, अचिन्हित दीर्घ offset),

	TP_ARGS(rcuname, rhp, offset),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, rcuname)
		__field(व्योम *, rhp)
		__field(अचिन्हित दीर्घ, offset)
	),

	TP_fast_assign(
		__entry->rcuname = rcuname;
		__entry->rhp = rhp;
		__entry->offset	= offset;
	),

	TP_prपूर्णांकk("%s rhp=%p func=%ld",
		  __entry->rcuname, __entry->rhp, __entry->offset)
);

/*
 * Tracepoपूर्णांक क्रम the invocation of a single RCU callback of the special
 * kमुक्त_bulk() क्रमm. The first argument is the RCU flavor, the second
 * argument is a number of elements in array to मुक्त, the third is an
 * address of the array holding nr_records entries.
 */
TRACE_EVENT_RCU(rcu_invoke_kमुक्त_bulk_callback,

	TP_PROTO(स्थिर अक्षर *rcuname, अचिन्हित दीर्घ nr_records, व्योम **p),

	TP_ARGS(rcuname, nr_records, p),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, rcuname)
		__field(अचिन्हित दीर्घ, nr_records)
		__field(व्योम **, p)
	),

	TP_fast_assign(
		__entry->rcuname = rcuname;
		__entry->nr_records = nr_records;
		__entry->p = p;
	),

	TP_prपूर्णांकk("%s bulk=0x%p nr_records=%lu",
		__entry->rcuname, __entry->p, __entry->nr_records)
);

/*
 * Tracepoपूर्णांक क्रम निकासing rcu_करो_batch after RCU callbacks have been
 * invoked.  The first argument is the name of the RCU flavor,
 * the second argument is number of callbacks actually invoked,
 * the third argument (cb) is whether or not any of the callbacks that
 * were पढ़ोy to invoke at the beginning of this batch are still
 * queued, the fourth argument (nr) is the वापस value of need_resched(),
 * the fअगरth argument (iit) is 1 अगर the current task is the idle task,
 * and the sixth argument (risk) is the वापस value from
 * rcu_is_callbacks_kthपढ़ो().
 */
TRACE_EVENT_RCU(rcu_batch_end,

	TP_PROTO(स्थिर अक्षर *rcuname, पूर्णांक callbacks_invoked,
		 अक्षर cb, अक्षर nr, अक्षर iit, अक्षर risk),

	TP_ARGS(rcuname, callbacks_invoked, cb, nr, iit, risk),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, rcuname)
		__field(पूर्णांक, callbacks_invoked)
		__field(अक्षर, cb)
		__field(अक्षर, nr)
		__field(अक्षर, iit)
		__field(अक्षर, risk)
	),

	TP_fast_assign(
		__entry->rcuname = rcuname;
		__entry->callbacks_invoked = callbacks_invoked;
		__entry->cb = cb;
		__entry->nr = nr;
		__entry->iit = iit;
		__entry->risk = risk;
	),

	TP_prपूर्णांकk("%s CBs-invoked=%d idle=%c%c%c%c",
		  __entry->rcuname, __entry->callbacks_invoked,
		  __entry->cb ? 'C' : '.',
		  __entry->nr ? 'S' : '.',
		  __entry->iit ? 'I' : '.',
		  __entry->risk ? 'R' : '.')
);

/*
 * Tracepoपूर्णांक क्रम rcutorture पढ़ोers.  The first argument is the name
 * of the RCU flavor from rcutorture's viewpoपूर्णांक and the second argument
 * is the callback address.  The third argument is the start समय in
 * seconds, and the last two arguments are the grace period numbers
 * at the beginning and end of the पढ़ो, respectively.  Note that the
 * callback address can be शून्य.
 */
#घोषणा RCUTORTURENAME_LEN 8
TRACE_EVENT_RCU(rcu_torture_पढ़ो,

	TP_PROTO(स्थिर अक्षर *rcutortuनाम, काष्ठा rcu_head *rhp,
		 अचिन्हित दीर्घ secs, अचिन्हित दीर्घ c_old, अचिन्हित दीर्घ c),

	TP_ARGS(rcutortuनाम, rhp, secs, c_old, c),

	TP_STRUCT__entry(
		__field(अक्षर, rcutortuनाम[RCUTORTURENAME_LEN])
		__field(काष्ठा rcu_head *, rhp)
		__field(अचिन्हित दीर्घ, secs)
		__field(अचिन्हित दीर्घ, c_old)
		__field(अचिन्हित दीर्घ, c)
	),

	TP_fast_assign(
		म_नकलन(__entry->rcutortuनाम, rcutortuनाम,
			RCUTORTURENAME_LEN);
		__entry->rcutortuनाम[RCUTORTURENAME_LEN - 1] = 0;
		__entry->rhp = rhp;
		__entry->secs = secs;
		__entry->c_old = c_old;
		__entry->c = c;
	),

	TP_prपूर्णांकk("%s torture read %p %luus c: %lu %lu",
		  __entry->rcutortuनाम, __entry->rhp,
		  __entry->secs, __entry->c_old, __entry->c)
);

/*
 * Tracepoपूर्णांक क्रम rcu_barrier() execution.  The string "s" describes
 * the rcu_barrier phase:
 *	"Begin": rcu_barrier() started.
 *	"EarlyExit": rcu_barrier() piggybacked, thus early निकास.
 *	"Inc1": rcu_barrier() piggyback check counter incremented.
 *	"OfflineNoCBQ": rcu_barrier() found offline no-CBs CPU with callbacks.
 *	"OnlineQ": rcu_barrier() found online CPU with callbacks.
 *	"OnlineNQ": rcu_barrier() found online CPU, no callbacks.
 *	"IRQ": An rcu_barrier_callback() callback posted on remote CPU.
 *	"IRQNQ": An rcu_barrier_callback() callback found no callbacks.
 *	"CB": An rcu_barrier_callback() invoked a callback, not the last.
 *	"LastCB": An rcu_barrier_callback() invoked the last callback.
 *	"Inc2": rcu_barrier() piggyback check counter incremented.
 * The "cpu" argument is the CPU or -1 अगर meaningless, the "cnt" argument
 * is the count of reमुख्यing callbacks, and "done" is the piggybacking count.
 */
TRACE_EVENT_RCU(rcu_barrier,

	TP_PROTO(स्थिर अक्षर *rcuname, स्थिर अक्षर *s, पूर्णांक cpu, पूर्णांक cnt, अचिन्हित दीर्घ करोne),

	TP_ARGS(rcuname, s, cpu, cnt, करोne),

	TP_STRUCT__entry(
		__field(स्थिर अक्षर *, rcuname)
		__field(स्थिर अक्षर *, s)
		__field(पूर्णांक, cpu)
		__field(पूर्णांक, cnt)
		__field(अचिन्हित दीर्घ, करोne)
	),

	TP_fast_assign(
		__entry->rcuname = rcuname;
		__entry->s = s;
		__entry->cpu = cpu;
		__entry->cnt = cnt;
		__entry->करोne = करोne;
	),

	TP_prपूर्णांकk("%s %s cpu %d remaining %d # %lu",
		  __entry->rcuname, __entry->s, __entry->cpu, __entry->cnt,
		  __entry->करोne)
);

#पूर्ण_अगर /* _TRACE_RCU_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
