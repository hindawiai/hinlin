<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _linux_POSIX_TIMERS_H
#घोषणा _linux_POSIX_TIMERS_H

#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/alarmसमयr.h>
#समावेश <linux/समयrqueue.h>
#समावेश <linux/task_work.h>

काष्ठा kernel_siginfo;
काष्ठा task_काष्ठा;

/*
 * Bit fields within a घड़ीid:
 *
 * The most signअगरicant 29 bits hold either a pid or a file descriptor.
 *
 * Bit 2 indicates whether a cpu घड़ी refers to a thपढ़ो or a process.
 *
 * Bits 1 and 0 give the type: PROF=0, VIRT=1, SCHED=2, or FD=3.
 *
 * A घड़ीid is invalid अगर bits 2, 1, and 0 are all set.
 */
#घोषणा CPUCLOCK_PID(घड़ी)		((pid_t) ~((घड़ी) >> 3))
#घोषणा CPUCLOCK_PERTHREAD(घड़ी) \
	(((घड़ी) & (घड़ीid_t) CPUCLOCK_PERTHREAD_MASK) != 0)

#घोषणा CPUCLOCK_PERTHREAD_MASK	4
#घोषणा CPUCLOCK_WHICH(घड़ी)	((घड़ी) & (घड़ीid_t) CPUCLOCK_CLOCK_MASK)
#घोषणा CPUCLOCK_CLOCK_MASK	3
#घोषणा CPUCLOCK_PROF		0
#घोषणा CPUCLOCK_VIRT		1
#घोषणा CPUCLOCK_SCHED		2
#घोषणा CPUCLOCK_MAX		3
#घोषणा CLOCKFD			CPUCLOCK_MAX
#घोषणा CLOCKFD_MASK		(CPUCLOCK_PERTHREAD_MASK|CPUCLOCK_CLOCK_MASK)

अटल अंतरभूत घड़ीid_t make_process_cpuघड़ी(स्थिर अचिन्हित पूर्णांक pid,
		स्थिर घड़ीid_t घड़ी)
अणु
	वापस ((~pid) << 3) | घड़ी;
पूर्ण
अटल अंतरभूत घड़ीid_t make_thपढ़ो_cpuघड़ी(स्थिर अचिन्हित पूर्णांक tid,
		स्थिर घड़ीid_t घड़ी)
अणु
	वापस make_process_cpuघड़ी(tid, घड़ी | CPUCLOCK_PERTHREAD_MASK);
पूर्ण

अटल अंतरभूत घड़ीid_t fd_to_घड़ीid(स्थिर पूर्णांक fd)
अणु
	वापस make_process_cpuघड़ी((अचिन्हित पूर्णांक) fd, CLOCKFD);
पूर्ण

अटल अंतरभूत पूर्णांक घड़ीid_to_fd(स्थिर घड़ीid_t clk)
अणु
	वापस ~(clk >> 3);
पूर्ण

#अगर_घोषित CONFIG_POSIX_TIMERS

/**
 * cpu_समयr - Posix CPU समयr representation क्रम k_iसमयr
 * @node:	समयrqueue node to queue in the task/sig
 * @head:	समयrqueue head on which this समयr is queued
 * @task:	Poपूर्णांकer to target task
 * @elist:	List head क्रम the expiry list
 * @firing:	Timer is currently firing
 */
काष्ठा cpu_समयr अणु
	काष्ठा समयrqueue_node	node;
	काष्ठा समयrqueue_head	*head;
	काष्ठा pid		*pid;
	काष्ठा list_head	elist;
	पूर्णांक			firing;
पूर्ण;

अटल अंतरभूत bool cpu_समयr_enqueue(काष्ठा समयrqueue_head *head,
				     काष्ठा cpu_समयr *cपंचांगr)
अणु
	cपंचांगr->head = head;
	वापस समयrqueue_add(head, &cपंचांगr->node);
पूर्ण

अटल अंतरभूत व्योम cpu_समयr_dequeue(काष्ठा cpu_समयr *cपंचांगr)
अणु
	अगर (cपंचांगr->head) अणु
		समयrqueue_del(cपंचांगr->head, &cपंचांगr->node);
		cपंचांगr->head = शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत u64 cpu_समयr_getexpires(काष्ठा cpu_समयr *cपंचांगr)
अणु
	वापस cपंचांगr->node.expires;
पूर्ण

अटल अंतरभूत व्योम cpu_समयr_setexpires(काष्ठा cpu_समयr *cपंचांगr, u64 exp)
अणु
	cपंचांगr->node.expires = exp;
पूर्ण

/**
 * posix_cpuसमयr_base - Container per posix CPU घड़ी
 * @nextevt:		Earliest-expiration cache
 * @tqhead:		समयrqueue head क्रम cpu_समयrs
 */
काष्ठा posix_cpuसमयr_base अणु
	u64			nextevt;
	काष्ठा समयrqueue_head	tqhead;
पूर्ण;

/**
 * posix_cpuसमयrs - Container क्रम posix CPU समयr related data
 * @bases:		Base container क्रम posix CPU घड़ीs
 * @समयrs_active:	Timers are queued.
 * @expiry_active:	Timer expiry is active. Used क्रम
 *			process wide समयrs to aव्योम multiple
 *			task trying to handle expiry concurrently
 *
 * Used in task_काष्ठा and संकेत_काष्ठा
 */
काष्ठा posix_cpuसमयrs अणु
	काष्ठा posix_cpuसमयr_base	bases[CPUCLOCK_MAX];
	अचिन्हित पूर्णांक			समयrs_active;
	अचिन्हित पूर्णांक			expiry_active;
पूर्ण;

/**
 * posix_cpuसमयrs_work - Container क्रम task work based posix CPU समयr expiry
 * @work:	The task work to be scheduled
 * @scheduled:  @work has been scheduled alपढ़ोy, no further processing
 */
काष्ठा posix_cpuसमयrs_work अणु
	काष्ठा callback_head	work;
	अचिन्हित पूर्णांक		scheduled;
पूर्ण;

अटल अंतरभूत व्योम posix_cpuसमयrs_init(काष्ठा posix_cpuसमयrs *pct)
अणु
	स_रखो(pct, 0, माप(*pct));
	pct->bases[0].nextevt = U64_MAX;
	pct->bases[1].nextevt = U64_MAX;
	pct->bases[2].nextevt = U64_MAX;
पूर्ण

व्योम posix_cpuसमयrs_group_init(काष्ठा posix_cpuसमयrs *pct, u64 cpu_limit);

अटल अंतरभूत व्योम posix_cpuसमयrs_rt_watchकरोg(काष्ठा posix_cpuसमयrs *pct,
					       u64 runसमय)
अणु
	pct->bases[CPUCLOCK_SCHED].nextevt = runसमय;
पूर्ण

/* Init task अटल initializer */
#घोषणा INIT_CPU_TIMERBASE(b) अणु						\
	.nextevt	= U64_MAX,					\
पूर्ण

#घोषणा INIT_CPU_TIMERBASES(b) अणु					\
	INIT_CPU_TIMERBASE(b[0]),					\
	INIT_CPU_TIMERBASE(b[1]),					\
	INIT_CPU_TIMERBASE(b[2]),					\
पूर्ण

#घोषणा INIT_CPU_TIMERS(s)						\
	.posix_cpuसमयrs = अणु						\
		.bases = INIT_CPU_TIMERBASES(s.posix_cpuसमयrs.bases),	\
	पूर्ण,
#अन्यथा
काष्ठा posix_cpuसमयrs अणु पूर्ण;
काष्ठा cpu_समयr अणु पूर्ण;
#घोषणा INIT_CPU_TIMERS(s)
अटल अंतरभूत व्योम posix_cpuसमयrs_init(काष्ठा posix_cpuसमयrs *pct) अणु पूर्ण
अटल अंतरभूत व्योम posix_cpuसमयrs_group_init(काष्ठा posix_cpuसमयrs *pct,
					      u64 cpu_limit) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_POSIX_CPU_TIMERS_TASK_WORK
व्योम posix_cpuसमयrs_init_work(व्योम);
#अन्यथा
अटल अंतरभूत व्योम posix_cpuसमयrs_init_work(व्योम) अणु पूर्ण
#पूर्ण_अगर

#घोषणा REQUEUE_PENDING 1

/**
 * काष्ठा k_iसमयr - POSIX.1b पूर्णांकerval समयr काष्ठाure.
 * @list:		List head क्रम binding the समयr to संकेतs->posix_समयrs
 * @t_hash:		Entry in the posix समयr hash table
 * @it_lock:		Lock protecting the समयr
 * @kघड़ी:		Poपूर्णांकer to the k_घड़ी काष्ठा handling this समयr
 * @it_घड़ी:		The posix समयr घड़ी id
 * @it_id:		The posix समयr id क्रम identअगरying the समयr
 * @it_active:		Marker that समयr is active
 * @it_overrun:		The overrun counter क्रम pending संकेतs
 * @it_overrun_last:	The overrun at the समय of the last delivered संकेत
 * @it_requeue_pending:	Indicator that समयr रुकोs क्रम being requeued on
 *			संकेत delivery
 * @it_sigev_notअगरy:	The notअगरy word of sigevent काष्ठा क्रम संकेत delivery
 * @it_पूर्णांकerval:	The पूर्णांकerval क्रम periodic समयrs
 * @it_संकेत:		Poपूर्णांकer to the creators संकेत काष्ठा
 * @it_pid:		The pid of the process/task targeted by the संकेत
 * @it_process:		The task to wakeup on घड़ी_nanosleep (CPU समयrs)
 * @sigq:		Poपूर्णांकer to pपुनः_स्मृतिated sigqueue
 * @it:			Union representing the various posix समयr type
 *			पूर्णांकernals.
 * @rcu:		RCU head क्रम मुक्तing the समयr.
 */
काष्ठा k_iसमयr अणु
	काष्ठा list_head	list;
	काष्ठा hlist_node	t_hash;
	spinlock_t		it_lock;
	स्थिर काष्ठा k_घड़ी	*kघड़ी;
	घड़ीid_t		it_घड़ी;
	समयr_t			it_id;
	पूर्णांक			it_active;
	s64			it_overrun;
	s64			it_overrun_last;
	पूर्णांक			it_requeue_pending;
	पूर्णांक			it_sigev_notअगरy;
	kसमय_प्रकार			it_पूर्णांकerval;
	काष्ठा संकेत_काष्ठा	*it_संकेत;
	जोड़ अणु
		काष्ठा pid		*it_pid;
		काष्ठा task_काष्ठा	*it_process;
	पूर्ण;
	काष्ठा sigqueue		*sigq;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा hrसमयr	समयr;
		पूर्ण real;
		काष्ठा cpu_समयr	cpu;
		काष्ठा अणु
			काष्ठा alarm	alarmसमयr;
		पूर्ण alarm;
	पूर्ण it;
	काष्ठा rcu_head		rcu;
पूर्ण;

व्योम run_posix_cpu_समयrs(व्योम);
व्योम posix_cpu_समयrs_निकास(काष्ठा task_काष्ठा *task);
व्योम posix_cpu_समयrs_निकास_group(काष्ठा task_काष्ठा *task);
व्योम set_process_cpu_समयr(काष्ठा task_काष्ठा *task, अचिन्हित पूर्णांक घड़ी_idx,
			   u64 *newval, u64 *oldval);

व्योम update_rlimit_cpu(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ rlim_new);

व्योम posixसमयr_rearm(काष्ठा kernel_siginfo *info);
#पूर्ण_अगर
