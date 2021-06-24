<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * kernel/workqueue_पूर्णांकernal.h
 *
 * Workqueue पूर्णांकernal header file.  Only to be included by workqueue and
 * core kernel subप्रणालीs.
 */
#अगर_अघोषित _KERNEL_WORKQUEUE_INTERNAL_H
#घोषणा _KERNEL_WORKQUEUE_INTERNAL_H

#समावेश <linux/workqueue.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/preempt.h>

काष्ठा worker_pool;

/*
 * The poor guys करोing the actual heavy lअगरting.  All on-duty workers are
 * either serving the manager role, on idle list or on busy hash.  For
 * details on the locking annotation (L, I, X...), refer to workqueue.c.
 *
 * Only to be used in workqueue and async.
 */
काष्ठा worker अणु
	/* on idle list जबतक idle, on busy hash table जबतक busy */
	जोड़ अणु
		काष्ठा list_head	entry;	/* L: जबतक idle */
		काष्ठा hlist_node	hentry;	/* L: जबतक busy */
	पूर्ण;

	काष्ठा work_काष्ठा	*current_work;	/* L: work being processed */
	work_func_t		current_func;	/* L: current_work's fn */
	काष्ठा pool_workqueue	*current_pwq; /* L: current_work's pwq */
	काष्ठा list_head	scheduled;	/* L: scheduled works */

	/* 64 bytes boundary on 64bit, 32 on 32bit */

	काष्ठा task_काष्ठा	*task;		/* I: worker task */
	काष्ठा worker_pool	*pool;		/* A: the associated pool */
						/* L: क्रम rescuers */
	काष्ठा list_head	node;		/* A: anchored at pool->workers */
						/* A: runs through worker->node */

	अचिन्हित दीर्घ		last_active;	/* L: last active बारtamp */
	अचिन्हित पूर्णांक		flags;		/* X: flags */
	पूर्णांक			id;		/* I: worker id */
	पूर्णांक			sleeping;	/* None */

	/*
	 * Opaque string set with work_set_desc().  Prपूर्णांकed out with task
	 * dump क्रम debugging - WARN, BUG, panic or sysrq.
	 */
	अक्षर			desc[WORKER_DESC_LEN];

	/* used only by rescuers to poपूर्णांक to the target workqueue */
	काष्ठा workqueue_काष्ठा	*rescue_wq;	/* I: the workqueue to rescue */

	/* used by the scheduler to determine a worker's last known identity */
	work_func_t		last_func;
पूर्ण;

/**
 * current_wq_worker - वापस काष्ठा worker अगर %current is a workqueue worker
 */
अटल अंतरभूत काष्ठा worker *current_wq_worker(व्योम)
अणु
	अगर (in_task() && (current->flags & PF_WQ_WORKER))
		वापस kthपढ़ो_data(current);
	वापस शून्य;
पूर्ण

/*
 * Scheduler hooks क्रम concurrency managed workqueue.  Only to be used from
 * sched/ and workqueue.c.
 */
व्योम wq_worker_running(काष्ठा task_काष्ठा *task);
व्योम wq_worker_sleeping(काष्ठा task_काष्ठा *task);
work_func_t wq_worker_last_func(काष्ठा task_काष्ठा *task);

#पूर्ण_अगर /* _KERNEL_WORKQUEUE_INTERNAL_H */
