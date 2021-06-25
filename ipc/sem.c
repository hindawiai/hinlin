<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/ipc/sem.c
 * Copyright (C) 1992 Krishna Balasubramanian
 * Copyright (C) 1995 Eric Schenk, Bruno Haible
 *
 * /proc/sysvipc/sem support (c) 1999 Dragos Acostachioaie <dragos@iname.com>
 *
 * SMP-thपढ़ोed, sysctl's added
 * (c) 1999 Manfred Spraul <manfred@colorfullअगरe.com>
 * Enक्रमced range limit on SEM_UNDO
 * (c) 2001 Red Hat Inc
 * Lockless wakeup
 * (c) 2003 Manfred Spraul <manfred@colorfullअगरe.com>
 * (c) 2016 Davidlohr Bueso <dave@stgoद_असल.net>
 * Further wakeup optimizations, करोcumentation
 * (c) 2010 Manfred Spraul <manfred@colorfullअगरe.com>
 *
 * support क्रम audit of ipc object properties and permission changes
 * Dustin Kirkland <dustin.kirkland@us.ibm.com>
 *
 * namespaces support
 * OpenVZ, SWsoft Inc.
 * Pavel Emelianov <xemul@खोलोvz.org>
 *
 * Implementation notes: (May 2010)
 * This file implements System V semaphores.
 *
 * User space visible behavior:
 * - FIFO ordering क्रम semop() operations (just FIFO, not starvation
 *   protection)
 * - multiple semaphore operations that alter the same semaphore in
 *   one semop() are handled.
 * - sem_स_समय (समय of last semctl()) is updated in the IPC_SET, SETVAL and
 *   SETALL calls.
 * - two Linux specअगरic semctl() commands: SEM_STAT, SEM_INFO.
 * - unकरो adjusपंचांगents at process निकास are limited to 0..SEMVMX.
 * - namespace are supported.
 * - SEMMSL, SEMMNS, SEMOPM and SEMMNI can be configured at runसमय by writing
 *   to /proc/sys/kernel/sem.
 * - statistics about the usage are reported in /proc/sysvipc/sem.
 *
 * Internals:
 * - scalability:
 *   - all global variables are पढ़ो-mostly.
 *   - semop() calls and semctl(RMID) are synchronized by RCU.
 *   - most operations करो ग_लिखो operations (actually: spin_lock calls) to
 *     the per-semaphore array काष्ठाure.
 *   Thus: Perfect SMP scaling between independent semaphore arrays.
 *         If multiple semaphores in one array are used, then cache line
 *         trashing on the semaphore array spinlock will limit the scaling.
 * - semncnt and semzcnt are calculated on demand in count_semcnt()
 * - the task that perक्रमms a successful semop() scans the list of all
 *   sleeping tasks and completes any pending operations that can be fulfilled.
 *   Semaphores are actively given to रुकोing tasks (necessary क्रम FIFO).
 *   (see update_queue())
 * - To improve the scalability, the actual wake-up calls are perक्रमmed after
 *   dropping all locks. (see wake_up_sem_queue_prepare())
 * - All work is करोne by the waker, the woken up task करोes not have to करो
 *   anything - not even acquiring a lock or dropping a refcount.
 * - A woken up task may not even touch the semaphore array anymore, it may
 *   have been destroyed alपढ़ोy by a semctl(RMID).
 * - UNDO values are stored in an array (one per process and per
 *   semaphore array, lazily allocated). For backwards compatibility, multiple
 *   modes क्रम the UNDO variables are supported (per process, per thपढ़ो)
 *   (see copy_semunकरो, CLONE_SYSVSEM)
 * - There are two lists of the pending operations: a per-array list
 *   and per-semaphore list (stored in the array). This allows to achieve FIFO
 *   ordering without always scanning all pending operations.
 *   The worst-हाल behavior is nevertheless O(N^2) क्रम N wakeups.
 */

#समावेश <linux/compat.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/समय.स>
#समावेश <linux/security.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/audit.h>
#समावेश <linux/capability.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/ipc_namespace.h>
#समावेश <linux/sched/wake_q.h>
#समावेश <linux/nospec.h>
#समावेश <linux/rhashtable.h>

#समावेश <linux/uaccess.h>
#समावेश "util.h"

/* One semaphore काष्ठाure क्रम each semaphore in the प्रणाली. */
काष्ठा sem अणु
	पूर्णांक	semval;		/* current value */
	/*
	 * PID of the process that last modअगरied the semaphore. For
	 * Linux, specअगरically these are:
	 *  - semop
	 *  - semctl, via SETVAL and SETALL.
	 *  - at task निकास when perक्रमming unकरो adjusपंचांगents (see निकास_sem).
	 */
	काष्ठा pid *sempid;
	spinlock_t	lock;	/* spinlock क्रम fine-grained semसमयकरोp */
	काष्ठा list_head pending_alter; /* pending single-sop operations */
					/* that alter the semaphore */
	काष्ठा list_head pending_स्थिर; /* pending single-sop operations */
					/* that करो not alter the semaphore*/
	समय64_t	 sem_oसमय;	/* candidate क्रम sem_oसमय */
पूर्ण ____cacheline_aligned_in_smp;

/* One sem_array data काष्ठाure क्रम each set of semaphores in the प्रणाली. */
काष्ठा sem_array अणु
	काष्ठा kern_ipc_perm	sem_perm;	/* permissions .. see ipc.h */
	समय64_t		sem_स_समय;	/* create/last semctl() समय */
	काष्ठा list_head	pending_alter;	/* pending operations */
						/* that alter the array */
	काष्ठा list_head	pending_स्थिर;	/* pending complex operations */
						/* that करो not alter semvals */
	काष्ठा list_head	list_id;	/* unकरो requests on this array */
	पूर्णांक			sem_nsems;	/* no. of semaphores in array */
	पूर्णांक			complex_count;	/* pending complex operations */
	अचिन्हित पूर्णांक		use_global_lock;/* >0: global lock required */

	काष्ठा sem		sems[];
पूर्ण __अक्रमomize_layout;

/* One queue क्रम each sleeping process in the प्रणाली. */
काष्ठा sem_queue अणु
	काष्ठा list_head	list;	 /* queue of pending operations */
	काष्ठा task_काष्ठा	*sleeper; /* this process */
	काष्ठा sem_unकरो		*unकरो;	 /* unकरो काष्ठाure */
	काष्ठा pid		*pid;	 /* process id of requesting process */
	पूर्णांक			status;	 /* completion status of operation */
	काष्ठा sembuf		*sops;	 /* array of pending operations */
	काष्ठा sembuf		*blocking; /* the operation that blocked */
	पूर्णांक			nsops;	 /* number of operations */
	bool			alter;	 /* करोes *sops alter the array? */
	bool                    dupsop;	 /* sops on more than one sem_num */
पूर्ण;

/* Each task has a list of unकरो requests. They are executed स्वतःmatically
 * when the process निकासs.
 */
काष्ठा sem_unकरो अणु
	काष्ठा list_head	list_proc;	/* per-process list: *
						 * all unकरोs from one process
						 * rcu रक्षित */
	काष्ठा rcu_head		rcu;		/* rcu काष्ठा क्रम sem_unकरो */
	काष्ठा sem_unकरो_list	*ulp;		/* back ptr to sem_unकरो_list */
	काष्ठा list_head	list_id;	/* per semaphore array list:
						 * all unकरोs क्रम one array */
	पूर्णांक			semid;		/* semaphore set identअगरier */
	लघु			*semadj;	/* array of adjusपंचांगents */
						/* one per semaphore */
पूर्ण;

/* sem_unकरो_list controls shared access to the list of sem_unकरो काष्ठाures
 * that may be shared among all a CLONE_SYSVSEM task group.
 */
काष्ठा sem_unकरो_list अणु
	refcount_t		refcnt;
	spinlock_t		lock;
	काष्ठा list_head	list_proc;
पूर्ण;


#घोषणा sem_ids(ns)	((ns)->ids[IPC_SEM_IDS])

अटल पूर्णांक newary(काष्ठा ipc_namespace *, काष्ठा ipc_params *);
अटल व्योम मुक्तary(काष्ठा ipc_namespace *, काष्ठा kern_ipc_perm *);
#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक sysvipc_sem_proc_show(काष्ठा seq_file *s, व्योम *it);
#पूर्ण_अगर

#घोषणा SEMMSL_FAST	256 /* 512 bytes on stack */
#घोषणा SEMOPM_FAST	64  /* ~ 372 bytes on stack */

/*
 * Switching from the mode suitable क्रम simple ops
 * to the mode क्रम complex ops is costly. Thereक्रमe:
 * use some hysteresis
 */
#घोषणा USE_GLOBAL_LOCK_HYSTERESIS	10

/*
 * Locking:
 * a) global sem_lock() क्रम पढ़ो/ग_लिखो
 *	sem_unकरो.id_next,
 *	sem_array.complex_count,
 *	sem_array.pendingअणु_alter,_स्थिरपूर्ण,
 *	sem_array.sem_unकरो
 *
 * b) global or semaphore sem_lock() क्रम पढ़ो/ग_लिखो:
 *	sem_array.sems[i].pending_अणुस्थिर,alterपूर्ण:
 *
 * c) special:
 *	sem_unकरो_list.list_proc:
 *	* unकरो_list->lock क्रम ग_लिखो
 *	* rcu क्रम पढ़ो
 *	use_global_lock:
 *	* global sem_lock() क्रम ग_लिखो
 *	* either local or global sem_lock() क्रम पढ़ो.
 *
 * Memory ordering:
 * Most ordering is enक्रमced by using spin_lock() and spin_unlock().
 *
 * Exceptions:
 * 1) use_global_lock: (SEM_BARRIER_1)
 * Setting it from non-zero to 0 is a RELEASE, this is ensured by
 * using smp_store_release(): Immediately after setting it to 0,
 * a simple op can start.
 * Testing अगर it is non-zero is an ACQUIRE, this is ensured by using
 * smp_load_acquire().
 * Setting it from 0 to non-zero must be ordered with regards to
 * this smp_load_acquire(), this is guaranteed because the smp_load_acquire()
 * is inside a spin_lock() and after a ग_लिखो from 0 to non-zero a
 * spin_lock()+spin_unlock() is करोne.
 *
 * 2) queue.status: (SEM_BARRIER_2)
 * Initialization is करोne जबतक holding sem_lock(), so no further barrier is
 * required.
 * Setting it to a result code is a RELEASE, this is ensured by both a
 * smp_store_release() (क्रम हाल a) and जबतक holding sem_lock()
 * (क्रम हाल b).
 * The ACQUIRE when पढ़ोing the result code without holding sem_lock() is
 * achieved by using READ_ONCE() + smp_acquire__after_ctrl_dep().
 * (हाल a above).
 * Reading the result code जबतक holding sem_lock() needs no further barriers,
 * the locks inside sem_lock() enक्रमce ordering (हाल b above)
 *
 * 3) current->state:
 * current->state is set to TASK_INTERRUPTIBLE जबतक holding sem_lock().
 * The wakeup is handled using the wake_q infraकाष्ठाure. wake_q wakeups may
 * happen immediately after calling wake_q_add. As wake_q_add_safe() is called
 * when holding sem_lock(), no further barriers are required.
 *
 * See also ipc/mqueue.c क्रम more details on the covered races.
 */

#घोषणा sc_semmsl	sem_ctls[0]
#घोषणा sc_semmns	sem_ctls[1]
#घोषणा sc_semopm	sem_ctls[2]
#घोषणा sc_semmni	sem_ctls[3]

व्योम sem_init_ns(काष्ठा ipc_namespace *ns)
अणु
	ns->sc_semmsl = SEMMSL;
	ns->sc_semmns = SEMMNS;
	ns->sc_semopm = SEMOPM;
	ns->sc_semmni = SEMMNI;
	ns->used_sems = 0;
	ipc_init_ids(&ns->ids[IPC_SEM_IDS]);
पूर्ण

#अगर_घोषित CONFIG_IPC_NS
व्योम sem_निकास_ns(काष्ठा ipc_namespace *ns)
अणु
	मुक्त_ipcs(ns, &sem_ids(ns), मुक्तary);
	idr_destroy(&ns->ids[IPC_SEM_IDS].ipcs_idr);
	rhashtable_destroy(&ns->ids[IPC_SEM_IDS].key_ht);
पूर्ण
#पूर्ण_अगर

व्योम __init sem_init(व्योम)
अणु
	sem_init_ns(&init_ipc_ns);
	ipc_init_proc_पूर्णांकerface("sysvipc/sem",
				"       key      semid perms      nsems   uid   gid  cuid  cgid      otime      ctime\n",
				IPC_SEM_IDS, sysvipc_sem_proc_show);
पूर्ण

/**
 * unmerge_queues - unmerge queues, अगर possible.
 * @sma: semaphore array
 *
 * The function unmerges the रुको queues अगर complex_count is 0.
 * It must be called prior to dropping the global semaphore array lock.
 */
अटल व्योम unmerge_queues(काष्ठा sem_array *sma)
अणु
	काष्ठा sem_queue *q, *tq;

	/* complex operations still around? */
	अगर (sma->complex_count)
		वापस;
	/*
	 * We will चयन back to simple mode.
	 * Move all pending operation back पूर्णांकo the per-semaphore
	 * queues.
	 */
	list_क्रम_each_entry_safe(q, tq, &sma->pending_alter, list) अणु
		काष्ठा sem *curr;
		curr = &sma->sems[q->sops[0].sem_num];

		list_add_tail(&q->list, &curr->pending_alter);
	पूर्ण
	INIT_LIST_HEAD(&sma->pending_alter);
पूर्ण

/**
 * merge_queues - merge single semop queues पूर्णांकo global queue
 * @sma: semaphore array
 *
 * This function merges all per-semaphore queues पूर्णांकo the global queue.
 * It is necessary to achieve FIFO ordering क्रम the pending single-sop
 * operations when a multi-semop operation must sleep.
 * Only the alter operations must be moved, the स्थिर operations can stay.
 */
अटल व्योम merge_queues(काष्ठा sem_array *sma)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < sma->sem_nsems; i++) अणु
		काष्ठा sem *sem = &sma->sems[i];

		list_splice_init(&sem->pending_alter, &sma->pending_alter);
	पूर्ण
पूर्ण

अटल व्योम sem_rcu_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा kern_ipc_perm *p = container_of(head, काष्ठा kern_ipc_perm, rcu);
	काष्ठा sem_array *sma = container_of(p, काष्ठा sem_array, sem_perm);

	security_sem_मुक्त(&sma->sem_perm);
	kvमुक्त(sma);
पूर्ण

/*
 * Enter the mode suitable क्रम non-simple operations:
 * Caller must own sem_perm.lock.
 */
अटल व्योम complexmode_enter(काष्ठा sem_array *sma)
अणु
	पूर्णांक i;
	काष्ठा sem *sem;

	अगर (sma->use_global_lock > 0)  अणु
		/*
		 * We are alपढ़ोy in global lock mode.
		 * Nothing to करो, just reset the
		 * counter until we वापस to simple mode.
		 */
		sma->use_global_lock = USE_GLOBAL_LOCK_HYSTERESIS;
		वापस;
	पूर्ण
	sma->use_global_lock = USE_GLOBAL_LOCK_HYSTERESIS;

	क्रम (i = 0; i < sma->sem_nsems; i++) अणु
		sem = &sma->sems[i];
		spin_lock(&sem->lock);
		spin_unlock(&sem->lock);
	पूर्ण
पूर्ण

/*
 * Try to leave the mode that disallows simple operations:
 * Caller must own sem_perm.lock.
 */
अटल व्योम complexmode_tryleave(काष्ठा sem_array *sma)
अणु
	अगर (sma->complex_count)  अणु
		/* Complex ops are sleeping.
		 * We must stay in complex mode
		 */
		वापस;
	पूर्ण
	अगर (sma->use_global_lock == 1) अणु

		/* See SEM_BARRIER_1 क्रम purpose/pairing */
		smp_store_release(&sma->use_global_lock, 0);
	पूर्ण अन्यथा अणु
		sma->use_global_lock--;
	पूर्ण
पूर्ण

#घोषणा SEM_GLOBAL_LOCK	(-1)
/*
 * If the request contains only one semaphore operation, and there are
 * no complex transactions pending, lock only the semaphore involved.
 * Otherwise, lock the entire semaphore array, since we either have
 * multiple semaphores in our own semops, or we need to look at
 * semaphores from other pending complex operations.
 */
अटल अंतरभूत पूर्णांक sem_lock(काष्ठा sem_array *sma, काष्ठा sembuf *sops,
			      पूर्णांक nsops)
अणु
	काष्ठा sem *sem;
	पूर्णांक idx;

	अगर (nsops != 1) अणु
		/* Complex operation - acquire a full lock */
		ipc_lock_object(&sma->sem_perm);

		/* Prevent parallel simple ops */
		complexmode_enter(sma);
		वापस SEM_GLOBAL_LOCK;
	पूर्ण

	/*
	 * Only one semaphore affected - try to optimize locking.
	 * Optimized locking is possible अगर no complex operation
	 * is either enqueued or processed right now.
	 *
	 * Both facts are tracked by use_global_mode.
	 */
	idx = array_index_nospec(sops->sem_num, sma->sem_nsems);
	sem = &sma->sems[idx];

	/*
	 * Initial check क्रम use_global_lock. Just an optimization,
	 * no locking, no memory barrier.
	 */
	अगर (!sma->use_global_lock) अणु
		/*
		 * It appears that no complex operation is around.
		 * Acquire the per-semaphore lock.
		 */
		spin_lock(&sem->lock);

		/* see SEM_BARRIER_1 क्रम purpose/pairing */
		अगर (!smp_load_acquire(&sma->use_global_lock)) अणु
			/* fast path successful! */
			वापस sops->sem_num;
		पूर्ण
		spin_unlock(&sem->lock);
	पूर्ण

	/* slow path: acquire the full lock */
	ipc_lock_object(&sma->sem_perm);

	अगर (sma->use_global_lock == 0) अणु
		/*
		 * The use_global_lock mode ended जबतक we रुकोed क्रम
		 * sma->sem_perm.lock. Thus we must चयन to locking
		 * with sem->lock.
		 * Unlike in the fast path, there is no need to recheck
		 * sma->use_global_lock after we have acquired sem->lock:
		 * We own sma->sem_perm.lock, thus use_global_lock cannot
		 * change.
		 */
		spin_lock(&sem->lock);

		ipc_unlock_object(&sma->sem_perm);
		वापस sops->sem_num;
	पूर्ण अन्यथा अणु
		/*
		 * Not a false alarm, thus जारी to use the global lock
		 * mode. No need क्रम complexmode_enter(), this was करोne by
		 * the caller that has set use_global_mode to non-zero.
		 */
		वापस SEM_GLOBAL_LOCK;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम sem_unlock(काष्ठा sem_array *sma, पूर्णांक locknum)
अणु
	अगर (locknum == SEM_GLOBAL_LOCK) अणु
		unmerge_queues(sma);
		complexmode_tryleave(sma);
		ipc_unlock_object(&sma->sem_perm);
	पूर्ण अन्यथा अणु
		काष्ठा sem *sem = &sma->sems[locknum];
		spin_unlock(&sem->lock);
	पूर्ण
पूर्ण

/*
 * sem_lock_(check_) routines are called in the paths where the rwsem
 * is not held.
 *
 * The caller holds the RCU पढ़ो lock.
 */
अटल अंतरभूत काष्ठा sem_array *sem_obtain_object(काष्ठा ipc_namespace *ns, पूर्णांक id)
अणु
	काष्ठा kern_ipc_perm *ipcp = ipc_obtain_object_idr(&sem_ids(ns), id);

	अगर (IS_ERR(ipcp))
		वापस ERR_CAST(ipcp);

	वापस container_of(ipcp, काष्ठा sem_array, sem_perm);
पूर्ण

अटल अंतरभूत काष्ठा sem_array *sem_obtain_object_check(काष्ठा ipc_namespace *ns,
							पूर्णांक id)
अणु
	काष्ठा kern_ipc_perm *ipcp = ipc_obtain_object_check(&sem_ids(ns), id);

	अगर (IS_ERR(ipcp))
		वापस ERR_CAST(ipcp);

	वापस container_of(ipcp, काष्ठा sem_array, sem_perm);
पूर्ण

अटल अंतरभूत व्योम sem_lock_and_putref(काष्ठा sem_array *sma)
अणु
	sem_lock(sma, शून्य, -1);
	ipc_rcu_putref(&sma->sem_perm, sem_rcu_मुक्त);
पूर्ण

अटल अंतरभूत व्योम sem_rmid(काष्ठा ipc_namespace *ns, काष्ठा sem_array *s)
अणु
	ipc_rmid(&sem_ids(ns), &s->sem_perm);
पूर्ण

अटल काष्ठा sem_array *sem_alloc(माप_प्रकार nsems)
अणु
	काष्ठा sem_array *sma;

	अगर (nsems > (पूर्णांक_उच्च - माप(*sma)) / माप(sma->sems[0]))
		वापस शून्य;

	sma = kvzalloc(काष्ठा_size(sma, sems, nsems), GFP_KERNEL);
	अगर (unlikely(!sma))
		वापस शून्य;

	वापस sma;
पूर्ण

/**
 * newary - Create a new semaphore set
 * @ns: namespace
 * @params: ptr to the काष्ठाure that contains key, semflg and nsems
 *
 * Called with sem_ids.rwsem held (as a ग_लिखोr)
 */
अटल पूर्णांक newary(काष्ठा ipc_namespace *ns, काष्ठा ipc_params *params)
अणु
	पूर्णांक retval;
	काष्ठा sem_array *sma;
	key_t key = params->key;
	पूर्णांक nsems = params->u.nsems;
	पूर्णांक semflg = params->flg;
	पूर्णांक i;

	अगर (!nsems)
		वापस -EINVAL;
	अगर (ns->used_sems + nsems > ns->sc_semmns)
		वापस -ENOSPC;

	sma = sem_alloc(nsems);
	अगर (!sma)
		वापस -ENOMEM;

	sma->sem_perm.mode = (semflg & S_IRWXUGO);
	sma->sem_perm.key = key;

	sma->sem_perm.security = शून्य;
	retval = security_sem_alloc(&sma->sem_perm);
	अगर (retval) अणु
		kvमुक्त(sma);
		वापस retval;
	पूर्ण

	क्रम (i = 0; i < nsems; i++) अणु
		INIT_LIST_HEAD(&sma->sems[i].pending_alter);
		INIT_LIST_HEAD(&sma->sems[i].pending_स्थिर);
		spin_lock_init(&sma->sems[i].lock);
	पूर्ण

	sma->complex_count = 0;
	sma->use_global_lock = USE_GLOBAL_LOCK_HYSTERESIS;
	INIT_LIST_HEAD(&sma->pending_alter);
	INIT_LIST_HEAD(&sma->pending_स्थिर);
	INIT_LIST_HEAD(&sma->list_id);
	sma->sem_nsems = nsems;
	sma->sem_स_समय = kसमय_get_real_seconds();

	/* ipc_addid() locks sma upon success. */
	retval = ipc_addid(&sem_ids(ns), &sma->sem_perm, ns->sc_semmni);
	अगर (retval < 0) अणु
		ipc_rcu_putref(&sma->sem_perm, sem_rcu_मुक्त);
		वापस retval;
	पूर्ण
	ns->used_sems += nsems;

	sem_unlock(sma, -1);
	rcu_पढ़ो_unlock();

	वापस sma->sem_perm.id;
पूर्ण


/*
 * Called with sem_ids.rwsem and ipcp locked.
 */
अटल पूर्णांक sem_more_checks(काष्ठा kern_ipc_perm *ipcp, काष्ठा ipc_params *params)
अणु
	काष्ठा sem_array *sma;

	sma = container_of(ipcp, काष्ठा sem_array, sem_perm);
	अगर (params->u.nsems > sma->sem_nsems)
		वापस -EINVAL;

	वापस 0;
पूर्ण

दीर्घ ksys_semget(key_t key, पूर्णांक nsems, पूर्णांक semflg)
अणु
	काष्ठा ipc_namespace *ns;
	अटल स्थिर काष्ठा ipc_ops sem_ops = अणु
		.getnew = newary,
		.associate = security_sem_associate,
		.more_checks = sem_more_checks,
	पूर्ण;
	काष्ठा ipc_params sem_params;

	ns = current->nsproxy->ipc_ns;

	अगर (nsems < 0 || nsems > ns->sc_semmsl)
		वापस -EINVAL;

	sem_params.key = key;
	sem_params.flg = semflg;
	sem_params.u.nsems = nsems;

	वापस ipcget(ns, &sem_ids(ns), &sem_ops, &sem_params);
पूर्ण

SYSCALL_DEFINE3(semget, key_t, key, पूर्णांक, nsems, पूर्णांक, semflg)
अणु
	वापस ksys_semget(key, nsems, semflg);
पूर्ण

/**
 * perक्रमm_atomic_semop[_slow] - Attempt to perक्रमm semaphore
 *                               operations on a given array.
 * @sma: semaphore array
 * @q: काष्ठा sem_queue that describes the operation
 *
 * Caller blocking are as follows, based the value
 * indicated by the semaphore operation (sem_op):
 *
 *  (1) >0 never blocks.
 *  (2)  0 (रुको-क्रम-zero operation): semval is non-zero.
 *  (3) <0 attempting to decrement semval to a value smaller than zero.
 *
 * Returns 0 अगर the operation was possible.
 * Returns 1 अगर the operation is impossible, the caller must sleep.
 * Returns <0 क्रम error codes.
 */
अटल पूर्णांक perक्रमm_atomic_semop_slow(काष्ठा sem_array *sma, काष्ठा sem_queue *q)
अणु
	पूर्णांक result, sem_op, nsops;
	काष्ठा pid *pid;
	काष्ठा sembuf *sop;
	काष्ठा sem *curr;
	काष्ठा sembuf *sops;
	काष्ठा sem_unकरो *un;

	sops = q->sops;
	nsops = q->nsops;
	un = q->unकरो;

	क्रम (sop = sops; sop < sops + nsops; sop++) अणु
		पूर्णांक idx = array_index_nospec(sop->sem_num, sma->sem_nsems);
		curr = &sma->sems[idx];
		sem_op = sop->sem_op;
		result = curr->semval;

		अगर (!sem_op && result)
			जाओ would_block;

		result += sem_op;
		अगर (result < 0)
			जाओ would_block;
		अगर (result > SEMVMX)
			जाओ out_of_range;

		अगर (sop->sem_flg & SEM_UNDO) अणु
			पूर्णांक unकरो = un->semadj[sop->sem_num] - sem_op;
			/* Exceeding the unकरो range is an error. */
			अगर (unकरो < (-SEMAEM - 1) || unकरो > SEMAEM)
				जाओ out_of_range;
			un->semadj[sop->sem_num] = unकरो;
		पूर्ण

		curr->semval = result;
	पूर्ण

	sop--;
	pid = q->pid;
	जबतक (sop >= sops) अणु
		ipc_update_pid(&sma->sems[sop->sem_num].sempid, pid);
		sop--;
	पूर्ण

	वापस 0;

out_of_range:
	result = -दुस्फल;
	जाओ unकरो;

would_block:
	q->blocking = sop;

	अगर (sop->sem_flg & IPC_NOWAIT)
		result = -EAGAIN;
	अन्यथा
		result = 1;

unकरो:
	sop--;
	जबतक (sop >= sops) अणु
		sem_op = sop->sem_op;
		sma->sems[sop->sem_num].semval -= sem_op;
		अगर (sop->sem_flg & SEM_UNDO)
			un->semadj[sop->sem_num] += sem_op;
		sop--;
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक perक्रमm_atomic_semop(काष्ठा sem_array *sma, काष्ठा sem_queue *q)
अणु
	पूर्णांक result, sem_op, nsops;
	काष्ठा sembuf *sop;
	काष्ठा sem *curr;
	काष्ठा sembuf *sops;
	काष्ठा sem_unकरो *un;

	sops = q->sops;
	nsops = q->nsops;
	un = q->unकरो;

	अगर (unlikely(q->dupsop))
		वापस perक्रमm_atomic_semop_slow(sma, q);

	/*
	 * We scan the semaphore set twice, first to ensure that the entire
	 * operation can succeed, thereक्रमe aव्योमing any poपूर्णांकless ग_लिखोs
	 * to shared memory and having to unकरो such changes in order to block
	 * until the operations can go through.
	 */
	क्रम (sop = sops; sop < sops + nsops; sop++) अणु
		पूर्णांक idx = array_index_nospec(sop->sem_num, sma->sem_nsems);

		curr = &sma->sems[idx];
		sem_op = sop->sem_op;
		result = curr->semval;

		अगर (!sem_op && result)
			जाओ would_block; /* रुको-क्रम-zero */

		result += sem_op;
		अगर (result < 0)
			जाओ would_block;

		अगर (result > SEMVMX)
			वापस -दुस्फल;

		अगर (sop->sem_flg & SEM_UNDO) अणु
			पूर्णांक unकरो = un->semadj[sop->sem_num] - sem_op;

			/* Exceeding the unकरो range is an error. */
			अगर (unकरो < (-SEMAEM - 1) || unकरो > SEMAEM)
				वापस -दुस्फल;
		पूर्ण
	पूर्ण

	क्रम (sop = sops; sop < sops + nsops; sop++) अणु
		curr = &sma->sems[sop->sem_num];
		sem_op = sop->sem_op;
		result = curr->semval;

		अगर (sop->sem_flg & SEM_UNDO) अणु
			पूर्णांक unकरो = un->semadj[sop->sem_num] - sem_op;

			un->semadj[sop->sem_num] = unकरो;
		पूर्ण
		curr->semval += sem_op;
		ipc_update_pid(&curr->sempid, q->pid);
	पूर्ण

	वापस 0;

would_block:
	q->blocking = sop;
	वापस sop->sem_flg & IPC_NOWAIT ? -EAGAIN : 1;
पूर्ण

अटल अंतरभूत व्योम wake_up_sem_queue_prepare(काष्ठा sem_queue *q, पूर्णांक error,
					     काष्ठा wake_q_head *wake_q)
अणु
	काष्ठा task_काष्ठा *sleeper;

	sleeper = get_task_काष्ठा(q->sleeper);

	/* see SEM_BARRIER_2 क्रम purpose/pairing */
	smp_store_release(&q->status, error);

	wake_q_add_safe(wake_q, sleeper);
पूर्ण

अटल व्योम unlink_queue(काष्ठा sem_array *sma, काष्ठा sem_queue *q)
अणु
	list_del(&q->list);
	अगर (q->nsops > 1)
		sma->complex_count--;
पूर्ण

/** check_restart(sma, q)
 * @sma: semaphore array
 * @q: the operation that just completed
 *
 * update_queue is O(N^2) when it restarts scanning the whole queue of
 * रुकोing operations. Thereक्रमe this function checks अगर the restart is
 * really necessary. It is called after a previously रुकोing operation
 * modअगरied the array.
 * Note that रुको-क्रम-zero operations are handled without restart.
 */
अटल अंतरभूत पूर्णांक check_restart(काष्ठा sem_array *sma, काष्ठा sem_queue *q)
अणु
	/* pending complex alter operations are too dअगरficult to analyse */
	अगर (!list_empty(&sma->pending_alter))
		वापस 1;

	/* we were a sleeping complex operation. Too dअगरficult */
	अगर (q->nsops > 1)
		वापस 1;

	/* It is impossible that someone रुकोs क्रम the new value:
	 * - complex operations always restart.
	 * - रुको-क्रम-zero are handled separately.
	 * - q is a previously sleeping simple operation that
	 *   altered the array. It must be a decrement, because
	 *   simple increments never sleep.
	 * - If there are older (higher priority) decrements
	 *   in the queue, then they have observed the original
	 *   semval value and couldn't proceed. The operation
	 *   decremented to value - thus they won't proceed either.
	 */
	वापस 0;
पूर्ण

/**
 * wake_स्थिर_ops - wake up non-alter tasks
 * @sma: semaphore array.
 * @semnum: semaphore that was modअगरied.
 * @wake_q: lockless wake-queue head.
 *
 * wake_स्थिर_ops must be called after a semaphore in a semaphore array
 * was set to 0. If complex स्थिर operations are pending, wake_स्थिर_ops must
 * be called with semnum = -1, as well as with the number of each modअगरied
 * semaphore.
 * The tasks that must be woken up are added to @wake_q. The वापस code
 * is stored in q->pid.
 * The function वापसs 1 अगर at least one operation was completed successfully.
 */
अटल पूर्णांक wake_स्थिर_ops(काष्ठा sem_array *sma, पूर्णांक semnum,
			  काष्ठा wake_q_head *wake_q)
अणु
	काष्ठा sem_queue *q, *पंचांगp;
	काष्ठा list_head *pending_list;
	पूर्णांक semop_completed = 0;

	अगर (semnum == -1)
		pending_list = &sma->pending_स्थिर;
	अन्यथा
		pending_list = &sma->sems[semnum].pending_स्थिर;

	list_क्रम_each_entry_safe(q, पंचांगp, pending_list, list) अणु
		पूर्णांक error = perक्रमm_atomic_semop(sma, q);

		अगर (error > 0)
			जारी;
		/* operation completed, हटाओ from queue & wakeup */
		unlink_queue(sma, q);

		wake_up_sem_queue_prepare(q, error, wake_q);
		अगर (error == 0)
			semop_completed = 1;
	पूर्ण

	वापस semop_completed;
पूर्ण

/**
 * करो_smart_wakeup_zero - wakeup all रुको क्रम zero tasks
 * @sma: semaphore array
 * @sops: operations that were perक्रमmed
 * @nsops: number of operations
 * @wake_q: lockless wake-queue head
 *
 * Checks all required queue क्रम रुको-क्रम-zero operations, based
 * on the actual changes that were perक्रमmed on the semaphore array.
 * The function वापसs 1 अगर at least one operation was completed successfully.
 */
अटल पूर्णांक करो_smart_wakeup_zero(काष्ठा sem_array *sma, काष्ठा sembuf *sops,
				पूर्णांक nsops, काष्ठा wake_q_head *wake_q)
अणु
	पूर्णांक i;
	पूर्णांक semop_completed = 0;
	पूर्णांक got_zero = 0;

	/* first: the per-semaphore queues, अगर known */
	अगर (sops) अणु
		क्रम (i = 0; i < nsops; i++) अणु
			पूर्णांक num = sops[i].sem_num;

			अगर (sma->sems[num].semval == 0) अणु
				got_zero = 1;
				semop_completed |= wake_स्थिर_ops(sma, num, wake_q);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * No sops means modअगरied semaphores not known.
		 * Assume all were changed.
		 */
		क्रम (i = 0; i < sma->sem_nsems; i++) अणु
			अगर (sma->sems[i].semval == 0) अणु
				got_zero = 1;
				semop_completed |= wake_स्थिर_ops(sma, i, wake_q);
			पूर्ण
		पूर्ण
	पूर्ण
	/*
	 * If one of the modअगरied semaphores got 0,
	 * then check the global queue, too.
	 */
	अगर (got_zero)
		semop_completed |= wake_स्थिर_ops(sma, -1, wake_q);

	वापस semop_completed;
पूर्ण


/**
 * update_queue - look क्रम tasks that can be completed.
 * @sma: semaphore array.
 * @semnum: semaphore that was modअगरied.
 * @wake_q: lockless wake-queue head.
 *
 * update_queue must be called after a semaphore in a semaphore array
 * was modअगरied. If multiple semaphores were modअगरied, update_queue must
 * be called with semnum = -1, as well as with the number of each modअगरied
 * semaphore.
 * The tasks that must be woken up are added to @wake_q. The वापस code
 * is stored in q->pid.
 * The function पूर्णांकernally checks अगर स्थिर operations can now succeed.
 *
 * The function वापस 1 अगर at least one semop was completed successfully.
 */
अटल पूर्णांक update_queue(काष्ठा sem_array *sma, पूर्णांक semnum, काष्ठा wake_q_head *wake_q)
अणु
	काष्ठा sem_queue *q, *पंचांगp;
	काष्ठा list_head *pending_list;
	पूर्णांक semop_completed = 0;

	अगर (semnum == -1)
		pending_list = &sma->pending_alter;
	अन्यथा
		pending_list = &sma->sems[semnum].pending_alter;

again:
	list_क्रम_each_entry_safe(q, पंचांगp, pending_list, list) अणु
		पूर्णांक error, restart;

		/* If we are scanning the single sop, per-semaphore list of
		 * one semaphore and that semaphore is 0, then it is not
		 * necessary to scan further: simple increments
		 * that affect only one entry succeed immediately and cannot
		 * be in the  per semaphore pending queue, and decrements
		 * cannot be successful अगर the value is alपढ़ोy 0.
		 */
		अगर (semnum != -1 && sma->sems[semnum].semval == 0)
			अवरोध;

		error = perक्रमm_atomic_semop(sma, q);

		/* Does q->sleeper still need to sleep? */
		अगर (error > 0)
			जारी;

		unlink_queue(sma, q);

		अगर (error) अणु
			restart = 0;
		पूर्ण अन्यथा अणु
			semop_completed = 1;
			करो_smart_wakeup_zero(sma, q->sops, q->nsops, wake_q);
			restart = check_restart(sma, q);
		पूर्ण

		wake_up_sem_queue_prepare(q, error, wake_q);
		अगर (restart)
			जाओ again;
	पूर्ण
	वापस semop_completed;
पूर्ण

/**
 * set_semoसमय - set sem_oसमय
 * @sma: semaphore array
 * @sops: operations that modअगरied the array, may be शून्य
 *
 * sem_oसमय is replicated to aव्योम cache line trashing.
 * This function sets one instance to the current समय.
 */
अटल व्योम set_semoसमय(काष्ठा sem_array *sma, काष्ठा sembuf *sops)
अणु
	अगर (sops == शून्य) अणु
		sma->sems[0].sem_oसमय = kसमय_get_real_seconds();
	पूर्ण अन्यथा अणु
		sma->sems[sops[0].sem_num].sem_oसमय =
						kसमय_get_real_seconds();
	पूर्ण
पूर्ण

/**
 * करो_smart_update - optimized update_queue
 * @sma: semaphore array
 * @sops: operations that were perक्रमmed
 * @nsops: number of operations
 * @oसमय: क्रमce setting oसमय
 * @wake_q: lockless wake-queue head
 *
 * करो_smart_update() करोes the required calls to update_queue and wakeup_zero,
 * based on the actual changes that were perक्रमmed on the semaphore array.
 * Note that the function करोes not करो the actual wake-up: the caller is
 * responsible क्रम calling wake_up_q().
 * It is safe to perक्रमm this call after dropping all locks.
 */
अटल व्योम करो_smart_update(काष्ठा sem_array *sma, काष्ठा sembuf *sops, पूर्णांक nsops,
			    पूर्णांक oसमय, काष्ठा wake_q_head *wake_q)
अणु
	पूर्णांक i;

	oसमय |= करो_smart_wakeup_zero(sma, sops, nsops, wake_q);

	अगर (!list_empty(&sma->pending_alter)) अणु
		/* semaphore array uses the global queue - just process it. */
		oसमय |= update_queue(sma, -1, wake_q);
	पूर्ण अन्यथा अणु
		अगर (!sops) अणु
			/*
			 * No sops, thus the modअगरied semaphores are not
			 * known. Check all.
			 */
			क्रम (i = 0; i < sma->sem_nsems; i++)
				oसमय |= update_queue(sma, i, wake_q);
		पूर्ण अन्यथा अणु
			/*
			 * Check the semaphores that were increased:
			 * - No complex ops, thus all sleeping ops are
			 *   decrease.
			 * - अगर we decreased the value, then any sleeping
			 *   semaphore ops won't be able to run: If the
			 *   previous value was too small, then the new
			 *   value will be too small, too.
			 */
			क्रम (i = 0; i < nsops; i++) अणु
				अगर (sops[i].sem_op > 0) अणु
					oसमय |= update_queue(sma,
							      sops[i].sem_num, wake_q);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (oसमय)
		set_semoसमय(sma, sops);
पूर्ण

/*
 * check_qop: Test अगर a queued operation sleeps on the semaphore semnum
 */
अटल पूर्णांक check_qop(काष्ठा sem_array *sma, पूर्णांक semnum, काष्ठा sem_queue *q,
			bool count_zero)
अणु
	काष्ठा sembuf *sop = q->blocking;

	/*
	 * Linux always (since 0.99.10) reported a task as sleeping on all
	 * semaphores. This violates SUS, thereक्रमe it was changed to the
	 * standard compliant behavior.
	 * Give the administrators a chance to notice that an application
	 * might misbehave because it relies on the Linux behavior.
	 */
	pr_info_once("semctl(GETNCNT/GETZCNT) is since 3.16 Single Unix Specification compliant.\n"
			"The task %s (%d) triggered the difference, watch for misbehavior.\n",
			current->comm, task_pid_nr(current));

	अगर (sop->sem_num != semnum)
		वापस 0;

	अगर (count_zero && sop->sem_op == 0)
		वापस 1;
	अगर (!count_zero && sop->sem_op < 0)
		वापस 1;

	वापस 0;
पूर्ण

/* The following counts are associated to each semaphore:
 *   semncnt        number of tasks रुकोing on semval being nonzero
 *   semzcnt        number of tasks रुकोing on semval being zero
 *
 * Per definition, a task रुकोs only on the semaphore of the first semop
 * that cannot proceed, even अगर additional operation would block, too.
 */
अटल पूर्णांक count_semcnt(काष्ठा sem_array *sma, uलघु semnum,
			bool count_zero)
अणु
	काष्ठा list_head *l;
	काष्ठा sem_queue *q;
	पूर्णांक semcnt;

	semcnt = 0;
	/* First: check the simple operations. They are easy to evaluate */
	अगर (count_zero)
		l = &sma->sems[semnum].pending_स्थिर;
	अन्यथा
		l = &sma->sems[semnum].pending_alter;

	list_क्रम_each_entry(q, l, list) अणु
		/* all task on a per-semaphore list sleep on exactly
		 * that semaphore
		 */
		semcnt++;
	पूर्ण

	/* Then: check the complex operations. */
	list_क्रम_each_entry(q, &sma->pending_alter, list) अणु
		semcnt += check_qop(sma, semnum, q, count_zero);
	पूर्ण
	अगर (count_zero) अणु
		list_क्रम_each_entry(q, &sma->pending_स्थिर, list) अणु
			semcnt += check_qop(sma, semnum, q, count_zero);
		पूर्ण
	पूर्ण
	वापस semcnt;
पूर्ण

/* Free a semaphore set. मुक्तary() is called with sem_ids.rwsem locked
 * as a ग_लिखोr and the spinlock क्रम this semaphore set hold. sem_ids.rwsem
 * reमुख्यs locked on निकास.
 */
अटल व्योम मुक्तary(काष्ठा ipc_namespace *ns, काष्ठा kern_ipc_perm *ipcp)
अणु
	काष्ठा sem_unकरो *un, *tu;
	काष्ठा sem_queue *q, *tq;
	काष्ठा sem_array *sma = container_of(ipcp, काष्ठा sem_array, sem_perm);
	पूर्णांक i;
	DEFINE_WAKE_Q(wake_q);

	/* Free the existing unकरो काष्ठाures क्रम this semaphore set.  */
	ipc_निश्चित_locked_object(&sma->sem_perm);
	list_क्रम_each_entry_safe(un, tu, &sma->list_id, list_id) अणु
		list_del(&un->list_id);
		spin_lock(&un->ulp->lock);
		un->semid = -1;
		list_del_rcu(&un->list_proc);
		spin_unlock(&un->ulp->lock);
		kमुक्त_rcu(un, rcu);
	पूर्ण

	/* Wake up all pending processes and let them fail with EIDRM. */
	list_क्रम_each_entry_safe(q, tq, &sma->pending_स्थिर, list) अणु
		unlink_queue(sma, q);
		wake_up_sem_queue_prepare(q, -EIDRM, &wake_q);
	पूर्ण

	list_क्रम_each_entry_safe(q, tq, &sma->pending_alter, list) अणु
		unlink_queue(sma, q);
		wake_up_sem_queue_prepare(q, -EIDRM, &wake_q);
	पूर्ण
	क्रम (i = 0; i < sma->sem_nsems; i++) अणु
		काष्ठा sem *sem = &sma->sems[i];
		list_क्रम_each_entry_safe(q, tq, &sem->pending_स्थिर, list) अणु
			unlink_queue(sma, q);
			wake_up_sem_queue_prepare(q, -EIDRM, &wake_q);
		पूर्ण
		list_क्रम_each_entry_safe(q, tq, &sem->pending_alter, list) अणु
			unlink_queue(sma, q);
			wake_up_sem_queue_prepare(q, -EIDRM, &wake_q);
		पूर्ण
		ipc_update_pid(&sem->sempid, शून्य);
	पूर्ण

	/* Remove the semaphore set from the IDR */
	sem_rmid(ns, sma);
	sem_unlock(sma, -1);
	rcu_पढ़ो_unlock();

	wake_up_q(&wake_q);
	ns->used_sems -= sma->sem_nsems;
	ipc_rcu_putref(&sma->sem_perm, sem_rcu_मुक्त);
पूर्ण

अटल अचिन्हित दीर्घ copy_semid_to_user(व्योम __user *buf, काष्ठा semid64_ds *in, पूर्णांक version)
अणु
	चयन (version) अणु
	हाल IPC_64:
		वापस copy_to_user(buf, in, माप(*in));
	हाल IPC_OLD:
	    अणु
		काष्ठा semid_ds out;

		स_रखो(&out, 0, माप(out));

		ipc64_perm_to_ipc_perm(&in->sem_perm, &out.sem_perm);

		out.sem_oसमय	= in->sem_oसमय;
		out.sem_स_समय	= in->sem_स_समय;
		out.sem_nsems	= in->sem_nsems;

		वापस copy_to_user(buf, &out, माप(out));
	    पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल समय64_t get_semoसमय(काष्ठा sem_array *sma)
अणु
	पूर्णांक i;
	समय64_t res;

	res = sma->sems[0].sem_oसमय;
	क्रम (i = 1; i < sma->sem_nsems; i++) अणु
		समय64_t to = sma->sems[i].sem_oसमय;

		अगर (to > res)
			res = to;
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक semctl_stat(काष्ठा ipc_namespace *ns, पूर्णांक semid,
			 पूर्णांक cmd, काष्ठा semid64_ds *semid64)
अणु
	काष्ठा sem_array *sma;
	समय64_t semoसमय;
	पूर्णांक err;

	स_रखो(semid64, 0, माप(*semid64));

	rcu_पढ़ो_lock();
	अगर (cmd == SEM_STAT || cmd == SEM_STAT_ANY) अणु
		sma = sem_obtain_object(ns, semid);
		अगर (IS_ERR(sma)) अणु
			err = PTR_ERR(sma);
			जाओ out_unlock;
		पूर्ण
	पूर्ण अन्यथा अणु /* IPC_STAT */
		sma = sem_obtain_object_check(ns, semid);
		अगर (IS_ERR(sma)) अणु
			err = PTR_ERR(sma);
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	/* see comment क्रम SHM_STAT_ANY */
	अगर (cmd == SEM_STAT_ANY)
		audit_ipc_obj(&sma->sem_perm);
	अन्यथा अणु
		err = -EACCES;
		अगर (ipcperms(ns, &sma->sem_perm, S_IRUGO))
			जाओ out_unlock;
	पूर्ण

	err = security_sem_semctl(&sma->sem_perm, cmd);
	अगर (err)
		जाओ out_unlock;

	ipc_lock_object(&sma->sem_perm);

	अगर (!ipc_valid_object(&sma->sem_perm)) अणु
		ipc_unlock_object(&sma->sem_perm);
		err = -EIDRM;
		जाओ out_unlock;
	पूर्ण

	kernel_to_ipc64_perm(&sma->sem_perm, &semid64->sem_perm);
	semoसमय = get_semoसमय(sma);
	semid64->sem_oसमय = semoसमय;
	semid64->sem_स_समय = sma->sem_स_समय;
#अगर_अघोषित CONFIG_64BIT
	semid64->sem_oसमय_high = semoसमय >> 32;
	semid64->sem_स_समय_high = sma->sem_स_समय >> 32;
#पूर्ण_अगर
	semid64->sem_nsems = sma->sem_nsems;

	अगर (cmd == IPC_STAT) अणु
		/*
		 * As defined in SUS:
		 * Return 0 on success
		 */
		err = 0;
	पूर्ण अन्यथा अणु
		/*
		 * SEM_STAT and SEM_STAT_ANY (both Linux specअगरic)
		 * Return the full id, including the sequence number
		 */
		err = sma->sem_perm.id;
	पूर्ण
	ipc_unlock_object(&sma->sem_perm);
out_unlock:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक semctl_info(काष्ठा ipc_namespace *ns, पूर्णांक semid,
			 पूर्णांक cmd, व्योम __user *p)
अणु
	काष्ठा seminfo seminfo;
	पूर्णांक max_idx;
	पूर्णांक err;

	err = security_sem_semctl(शून्य, cmd);
	अगर (err)
		वापस err;

	स_रखो(&seminfo, 0, माप(seminfo));
	seminfo.semmni = ns->sc_semmni;
	seminfo.semmns = ns->sc_semmns;
	seminfo.semmsl = ns->sc_semmsl;
	seminfo.semopm = ns->sc_semopm;
	seminfo.semvmx = SEMVMX;
	seminfo.semmnu = SEMMNU;
	seminfo.semmap = SEMMAP;
	seminfo.semume = SEMUME;
	करोwn_पढ़ो(&sem_ids(ns).rwsem);
	अगर (cmd == SEM_INFO) अणु
		seminfo.semusz = sem_ids(ns).in_use;
		seminfo.semaem = ns->used_sems;
	पूर्ण अन्यथा अणु
		seminfo.semusz = SEMUSZ;
		seminfo.semaem = SEMAEM;
	पूर्ण
	max_idx = ipc_get_maxidx(&sem_ids(ns));
	up_पढ़ो(&sem_ids(ns).rwsem);
	अगर (copy_to_user(p, &seminfo, माप(काष्ठा seminfo)))
		वापस -EFAULT;
	वापस (max_idx < 0) ? 0 : max_idx;
पूर्ण

अटल पूर्णांक semctl_setval(काष्ठा ipc_namespace *ns, पूर्णांक semid, पूर्णांक semnum,
		पूर्णांक val)
अणु
	काष्ठा sem_unकरो *un;
	काष्ठा sem_array *sma;
	काष्ठा sem *curr;
	पूर्णांक err;
	DEFINE_WAKE_Q(wake_q);

	अगर (val > SEMVMX || val < 0)
		वापस -दुस्फल;

	rcu_पढ़ो_lock();
	sma = sem_obtain_object_check(ns, semid);
	अगर (IS_ERR(sma)) अणु
		rcu_पढ़ो_unlock();
		वापस PTR_ERR(sma);
	पूर्ण

	अगर (semnum < 0 || semnum >= sma->sem_nsems) अणु
		rcu_पढ़ो_unlock();
		वापस -EINVAL;
	पूर्ण


	अगर (ipcperms(ns, &sma->sem_perm, S_IWUGO)) अणु
		rcu_पढ़ो_unlock();
		वापस -EACCES;
	पूर्ण

	err = security_sem_semctl(&sma->sem_perm, SETVAL);
	अगर (err) अणु
		rcu_पढ़ो_unlock();
		वापस -EACCES;
	पूर्ण

	sem_lock(sma, शून्य, -1);

	अगर (!ipc_valid_object(&sma->sem_perm)) अणु
		sem_unlock(sma, -1);
		rcu_पढ़ो_unlock();
		वापस -EIDRM;
	पूर्ण

	semnum = array_index_nospec(semnum, sma->sem_nsems);
	curr = &sma->sems[semnum];

	ipc_निश्चित_locked_object(&sma->sem_perm);
	list_क्रम_each_entry(un, &sma->list_id, list_id)
		un->semadj[semnum] = 0;

	curr->semval = val;
	ipc_update_pid(&curr->sempid, task_tgid(current));
	sma->sem_स_समय = kसमय_get_real_seconds();
	/* maybe some queued-up processes were रुकोing क्रम this */
	करो_smart_update(sma, शून्य, 0, 0, &wake_q);
	sem_unlock(sma, -1);
	rcu_पढ़ो_unlock();
	wake_up_q(&wake_q);
	वापस 0;
पूर्ण

अटल पूर्णांक semctl_मुख्य(काष्ठा ipc_namespace *ns, पूर्णांक semid, पूर्णांक semnum,
		पूर्णांक cmd, व्योम __user *p)
अणु
	काष्ठा sem_array *sma;
	काष्ठा sem *curr;
	पूर्णांक err, nsems;
	uलघु fast_sem_io[SEMMSL_FAST];
	uलघु *sem_io = fast_sem_io;
	DEFINE_WAKE_Q(wake_q);

	rcu_पढ़ो_lock();
	sma = sem_obtain_object_check(ns, semid);
	अगर (IS_ERR(sma)) अणु
		rcu_पढ़ो_unlock();
		वापस PTR_ERR(sma);
	पूर्ण

	nsems = sma->sem_nsems;

	err = -EACCES;
	अगर (ipcperms(ns, &sma->sem_perm, cmd == SETALL ? S_IWUGO : S_IRUGO))
		जाओ out_rcu_wakeup;

	err = security_sem_semctl(&sma->sem_perm, cmd);
	अगर (err)
		जाओ out_rcu_wakeup;

	err = -EACCES;
	चयन (cmd) अणु
	हाल GETALL:
	अणु
		uलघु __user *array = p;
		पूर्णांक i;

		sem_lock(sma, शून्य, -1);
		अगर (!ipc_valid_object(&sma->sem_perm)) अणु
			err = -EIDRM;
			जाओ out_unlock;
		पूर्ण
		अगर (nsems > SEMMSL_FAST) अणु
			अगर (!ipc_rcu_getref(&sma->sem_perm)) अणु
				err = -EIDRM;
				जाओ out_unlock;
			पूर्ण
			sem_unlock(sma, -1);
			rcu_पढ़ो_unlock();
			sem_io = kvदो_स्मृति_array(nsems, माप(uलघु),
						GFP_KERNEL);
			अगर (sem_io == शून्य) अणु
				ipc_rcu_putref(&sma->sem_perm, sem_rcu_मुक्त);
				वापस -ENOMEM;
			पूर्ण

			rcu_पढ़ो_lock();
			sem_lock_and_putref(sma);
			अगर (!ipc_valid_object(&sma->sem_perm)) अणु
				err = -EIDRM;
				जाओ out_unlock;
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < sma->sem_nsems; i++)
			sem_io[i] = sma->sems[i].semval;
		sem_unlock(sma, -1);
		rcu_पढ़ो_unlock();
		err = 0;
		अगर (copy_to_user(array, sem_io, nsems*माप(uलघु)))
			err = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण
	हाल SETALL:
	अणु
		पूर्णांक i;
		काष्ठा sem_unकरो *un;

		अगर (!ipc_rcu_getref(&sma->sem_perm)) अणु
			err = -EIDRM;
			जाओ out_rcu_wakeup;
		पूर्ण
		rcu_पढ़ो_unlock();

		अगर (nsems > SEMMSL_FAST) अणु
			sem_io = kvदो_स्मृति_array(nsems, माप(uलघु),
						GFP_KERNEL);
			अगर (sem_io == शून्य) अणु
				ipc_rcu_putref(&sma->sem_perm, sem_rcu_मुक्त);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		अगर (copy_from_user(sem_io, p, nsems*माप(uलघु))) अणु
			ipc_rcu_putref(&sma->sem_perm, sem_rcu_मुक्त);
			err = -EFAULT;
			जाओ out_मुक्त;
		पूर्ण

		क्रम (i = 0; i < nsems; i++) अणु
			अगर (sem_io[i] > SEMVMX) अणु
				ipc_rcu_putref(&sma->sem_perm, sem_rcu_मुक्त);
				err = -दुस्फल;
				जाओ out_मुक्त;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_lock();
		sem_lock_and_putref(sma);
		अगर (!ipc_valid_object(&sma->sem_perm)) अणु
			err = -EIDRM;
			जाओ out_unlock;
		पूर्ण

		क्रम (i = 0; i < nsems; i++) अणु
			sma->sems[i].semval = sem_io[i];
			ipc_update_pid(&sma->sems[i].sempid, task_tgid(current));
		पूर्ण

		ipc_निश्चित_locked_object(&sma->sem_perm);
		list_क्रम_each_entry(un, &sma->list_id, list_id) अणु
			क्रम (i = 0; i < nsems; i++)
				un->semadj[i] = 0;
		पूर्ण
		sma->sem_स_समय = kसमय_get_real_seconds();
		/* maybe some queued-up processes were रुकोing क्रम this */
		करो_smart_update(sma, शून्य, 0, 0, &wake_q);
		err = 0;
		जाओ out_unlock;
	पूर्ण
	/* GETVAL, GETPID, GETNCTN, GETZCNT: fall-through */
	पूर्ण
	err = -EINVAL;
	अगर (semnum < 0 || semnum >= nsems)
		जाओ out_rcu_wakeup;

	sem_lock(sma, शून्य, -1);
	अगर (!ipc_valid_object(&sma->sem_perm)) अणु
		err = -EIDRM;
		जाओ out_unlock;
	पूर्ण

	semnum = array_index_nospec(semnum, nsems);
	curr = &sma->sems[semnum];

	चयन (cmd) अणु
	हाल GETVAL:
		err = curr->semval;
		जाओ out_unlock;
	हाल GETPID:
		err = pid_vnr(curr->sempid);
		जाओ out_unlock;
	हाल GETNCNT:
		err = count_semcnt(sma, semnum, 0);
		जाओ out_unlock;
	हाल GETZCNT:
		err = count_semcnt(sma, semnum, 1);
		जाओ out_unlock;
	पूर्ण

out_unlock:
	sem_unlock(sma, -1);
out_rcu_wakeup:
	rcu_पढ़ो_unlock();
	wake_up_q(&wake_q);
out_मुक्त:
	अगर (sem_io != fast_sem_io)
		kvमुक्त(sem_io);
	वापस err;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
copy_semid_from_user(काष्ठा semid64_ds *out, व्योम __user *buf, पूर्णांक version)
अणु
	चयन (version) अणु
	हाल IPC_64:
		अगर (copy_from_user(out, buf, माप(*out)))
			वापस -EFAULT;
		वापस 0;
	हाल IPC_OLD:
	    अणु
		काष्ठा semid_ds tbuf_old;

		अगर (copy_from_user(&tbuf_old, buf, माप(tbuf_old)))
			वापस -EFAULT;

		out->sem_perm.uid	= tbuf_old.sem_perm.uid;
		out->sem_perm.gid	= tbuf_old.sem_perm.gid;
		out->sem_perm.mode	= tbuf_old.sem_perm.mode;

		वापस 0;
	    पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * This function handles some semctl commands which require the rwsem
 * to be held in ग_लिखो mode.
 * NOTE: no locks must be held, the rwsem is taken inside this function.
 */
अटल पूर्णांक semctl_करोwn(काष्ठा ipc_namespace *ns, पूर्णांक semid,
		       पूर्णांक cmd, काष्ठा semid64_ds *semid64)
अणु
	काष्ठा sem_array *sma;
	पूर्णांक err;
	काष्ठा kern_ipc_perm *ipcp;

	करोwn_ग_लिखो(&sem_ids(ns).rwsem);
	rcu_पढ़ो_lock();

	ipcp = ipcctl_obtain_check(ns, &sem_ids(ns), semid, cmd,
				      &semid64->sem_perm, 0);
	अगर (IS_ERR(ipcp)) अणु
		err = PTR_ERR(ipcp);
		जाओ out_unlock1;
	पूर्ण

	sma = container_of(ipcp, काष्ठा sem_array, sem_perm);

	err = security_sem_semctl(&sma->sem_perm, cmd);
	अगर (err)
		जाओ out_unlock1;

	चयन (cmd) अणु
	हाल IPC_RMID:
		sem_lock(sma, शून्य, -1);
		/* मुक्तary unlocks the ipc object and rcu */
		मुक्तary(ns, ipcp);
		जाओ out_up;
	हाल IPC_SET:
		sem_lock(sma, शून्य, -1);
		err = ipc_update_perm(&semid64->sem_perm, ipcp);
		अगर (err)
			जाओ out_unlock0;
		sma->sem_स_समय = kसमय_get_real_seconds();
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ out_unlock1;
	पूर्ण

out_unlock0:
	sem_unlock(sma, -1);
out_unlock1:
	rcu_पढ़ो_unlock();
out_up:
	up_ग_लिखो(&sem_ids(ns).rwsem);
	वापस err;
पूर्ण

अटल दीर्घ ksys_semctl(पूर्णांक semid, पूर्णांक semnum, पूर्णांक cmd, अचिन्हित दीर्घ arg, पूर्णांक version)
अणु
	काष्ठा ipc_namespace *ns;
	व्योम __user *p = (व्योम __user *)arg;
	काष्ठा semid64_ds semid64;
	पूर्णांक err;

	अगर (semid < 0)
		वापस -EINVAL;

	ns = current->nsproxy->ipc_ns;

	चयन (cmd) अणु
	हाल IPC_INFO:
	हाल SEM_INFO:
		वापस semctl_info(ns, semid, cmd, p);
	हाल IPC_STAT:
	हाल SEM_STAT:
	हाल SEM_STAT_ANY:
		err = semctl_stat(ns, semid, cmd, &semid64);
		अगर (err < 0)
			वापस err;
		अगर (copy_semid_to_user(p, &semid64, version))
			err = -EFAULT;
		वापस err;
	हाल GETALL:
	हाल GETVAL:
	हाल GETPID:
	हाल GETNCNT:
	हाल GETZCNT:
	हाल SETALL:
		वापस semctl_मुख्य(ns, semid, semnum, cmd, p);
	हाल SETVAL: अणु
		पूर्णांक val;
#अगर defined(CONFIG_64BIT) && defined(__BIG_ENDIAN)
		/* big-endian 64bit */
		val = arg >> 32;
#अन्यथा
		/* 32bit or little-endian 64bit */
		val = arg;
#पूर्ण_अगर
		वापस semctl_setval(ns, semid, semnum, val);
	पूर्ण
	हाल IPC_SET:
		अगर (copy_semid_from_user(&semid64, p, version))
			वापस -EFAULT;
		fallthrough;
	हाल IPC_RMID:
		वापस semctl_करोwn(ns, semid, cmd, &semid64);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

SYSCALL_DEFINE4(semctl, पूर्णांक, semid, पूर्णांक, semnum, पूर्णांक, cmd, अचिन्हित दीर्घ, arg)
अणु
	वापस ksys_semctl(semid, semnum, cmd, arg, IPC_64);
पूर्ण

#अगर_घोषित CONFIG_ARCH_WANT_IPC_PARSE_VERSION
दीर्घ ksys_old_semctl(पूर्णांक semid, पूर्णांक semnum, पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक version = ipc_parse_version(&cmd);

	वापस ksys_semctl(semid, semnum, cmd, arg, version);
पूर्ण

SYSCALL_DEFINE4(old_semctl, पूर्णांक, semid, पूर्णांक, semnum, पूर्णांक, cmd, अचिन्हित दीर्घ, arg)
अणु
	वापस ksys_old_semctl(semid, semnum, cmd, arg);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPAT

काष्ठा compat_semid_ds अणु
	काष्ठा compat_ipc_perm sem_perm;
	old_समय32_t sem_oसमय;
	old_समय32_t sem_स_समय;
	compat_uptr_t sem_base;
	compat_uptr_t sem_pending;
	compat_uptr_t sem_pending_last;
	compat_uptr_t unकरो;
	अचिन्हित लघु sem_nsems;
पूर्ण;

अटल पूर्णांक copy_compat_semid_from_user(काष्ठा semid64_ds *out, व्योम __user *buf,
					पूर्णांक version)
अणु
	स_रखो(out, 0, माप(*out));
	अगर (version == IPC_64) अणु
		काष्ठा compat_semid64_ds __user *p = buf;
		वापस get_compat_ipc64_perm(&out->sem_perm, &p->sem_perm);
	पूर्ण अन्यथा अणु
		काष्ठा compat_semid_ds __user *p = buf;
		वापस get_compat_ipc_perm(&out->sem_perm, &p->sem_perm);
	पूर्ण
पूर्ण

अटल पूर्णांक copy_compat_semid_to_user(व्योम __user *buf, काष्ठा semid64_ds *in,
					पूर्णांक version)
अणु
	अगर (version == IPC_64) अणु
		काष्ठा compat_semid64_ds v;
		स_रखो(&v, 0, माप(v));
		to_compat_ipc64_perm(&v.sem_perm, &in->sem_perm);
		v.sem_oसमय	 = lower_32_bits(in->sem_oसमय);
		v.sem_oसमय_high = upper_32_bits(in->sem_oसमय);
		v.sem_स_समय	 = lower_32_bits(in->sem_स_समय);
		v.sem_स_समय_high = upper_32_bits(in->sem_स_समय);
		v.sem_nsems = in->sem_nsems;
		वापस copy_to_user(buf, &v, माप(v));
	पूर्ण अन्यथा अणु
		काष्ठा compat_semid_ds v;
		स_रखो(&v, 0, माप(v));
		to_compat_ipc_perm(&v.sem_perm, &in->sem_perm);
		v.sem_oसमय = in->sem_oसमय;
		v.sem_स_समय = in->sem_स_समय;
		v.sem_nsems = in->sem_nsems;
		वापस copy_to_user(buf, &v, माप(v));
	पूर्ण
पूर्ण

अटल दीर्घ compat_ksys_semctl(पूर्णांक semid, पूर्णांक semnum, पूर्णांक cmd, पूर्णांक arg, पूर्णांक version)
अणु
	व्योम __user *p = compat_ptr(arg);
	काष्ठा ipc_namespace *ns;
	काष्ठा semid64_ds semid64;
	पूर्णांक err;

	ns = current->nsproxy->ipc_ns;

	अगर (semid < 0)
		वापस -EINVAL;

	चयन (cmd & (~IPC_64)) अणु
	हाल IPC_INFO:
	हाल SEM_INFO:
		वापस semctl_info(ns, semid, cmd, p);
	हाल IPC_STAT:
	हाल SEM_STAT:
	हाल SEM_STAT_ANY:
		err = semctl_stat(ns, semid, cmd, &semid64);
		अगर (err < 0)
			वापस err;
		अगर (copy_compat_semid_to_user(p, &semid64, version))
			err = -EFAULT;
		वापस err;
	हाल GETVAL:
	हाल GETPID:
	हाल GETNCNT:
	हाल GETZCNT:
	हाल GETALL:
	हाल SETALL:
		वापस semctl_मुख्य(ns, semid, semnum, cmd, p);
	हाल SETVAL:
		वापस semctl_setval(ns, semid, semnum, arg);
	हाल IPC_SET:
		अगर (copy_compat_semid_from_user(&semid64, p, version))
			वापस -EFAULT;
		fallthrough;
	हाल IPC_RMID:
		वापस semctl_करोwn(ns, semid, cmd, &semid64);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

COMPAT_SYSCALL_DEFINE4(semctl, पूर्णांक, semid, पूर्णांक, semnum, पूर्णांक, cmd, पूर्णांक, arg)
अणु
	वापस compat_ksys_semctl(semid, semnum, cmd, arg, IPC_64);
पूर्ण

#अगर_घोषित CONFIG_ARCH_WANT_COMPAT_IPC_PARSE_VERSION
दीर्घ compat_ksys_old_semctl(पूर्णांक semid, पूर्णांक semnum, पूर्णांक cmd, पूर्णांक arg)
अणु
	पूर्णांक version = compat_ipc_parse_version(&cmd);

	वापस compat_ksys_semctl(semid, semnum, cmd, arg, version);
पूर्ण

COMPAT_SYSCALL_DEFINE4(old_semctl, पूर्णांक, semid, पूर्णांक, semnum, पूर्णांक, cmd, पूर्णांक, arg)
अणु
	वापस compat_ksys_old_semctl(semid, semnum, cmd, arg);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

/* If the task करोesn't alपढ़ोy have a unकरो_list, then allocate one
 * here.  We guarantee there is only one thपढ़ो using this unकरो list,
 * and current is THE ONE
 *
 * If this allocation and assignment succeeds, but later
 * portions of this code fail, there is no need to मुक्त the sem_unकरो_list.
 * Just let it stay associated with the task, and it'll be मुक्तd later
 * at निकास समय.
 *
 * This can block, so callers must hold no locks.
 */
अटल अंतरभूत पूर्णांक get_unकरो_list(काष्ठा sem_unकरो_list **unकरो_listp)
अणु
	काष्ठा sem_unकरो_list *unकरो_list;

	unकरो_list = current->sysvsem.unकरो_list;
	अगर (!unकरो_list) अणु
		unकरो_list = kzalloc(माप(*unकरो_list), GFP_KERNEL);
		अगर (unकरो_list == शून्य)
			वापस -ENOMEM;
		spin_lock_init(&unकरो_list->lock);
		refcount_set(&unकरो_list->refcnt, 1);
		INIT_LIST_HEAD(&unकरो_list->list_proc);

		current->sysvsem.unकरो_list = unकरो_list;
	पूर्ण
	*unकरो_listp = unकरो_list;
	वापस 0;
पूर्ण

अटल काष्ठा sem_unकरो *__lookup_unकरो(काष्ठा sem_unकरो_list *ulp, पूर्णांक semid)
अणु
	काष्ठा sem_unकरो *un;

	list_क्रम_each_entry_rcu(un, &ulp->list_proc, list_proc,
				spin_is_locked(&ulp->lock)) अणु
		अगर (un->semid == semid)
			वापस un;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा sem_unकरो *lookup_unकरो(काष्ठा sem_unकरो_list *ulp, पूर्णांक semid)
अणु
	काष्ठा sem_unकरो *un;

	निश्चित_spin_locked(&ulp->lock);

	un = __lookup_unकरो(ulp, semid);
	अगर (un) अणु
		list_del_rcu(&un->list_proc);
		list_add_rcu(&un->list_proc, &ulp->list_proc);
	पूर्ण
	वापस un;
पूर्ण

/**
 * find_alloc_unकरो - lookup (and अगर not present create) unकरो array
 * @ns: namespace
 * @semid: semaphore array id
 *
 * The function looks up (and अगर not present creates) the unकरो काष्ठाure.
 * The size of the unकरो काष्ठाure depends on the size of the semaphore
 * array, thus the alloc path is not that straightक्रमward.
 * Lअगरeसमय-rules: sem_unकरो is rcu-रक्षित, on success, the function
 * perक्रमms a rcu_पढ़ो_lock().
 */
अटल काष्ठा sem_unकरो *find_alloc_unकरो(काष्ठा ipc_namespace *ns, पूर्णांक semid)
अणु
	काष्ठा sem_array *sma;
	काष्ठा sem_unकरो_list *ulp;
	काष्ठा sem_unकरो *un, *new;
	पूर्णांक nsems, error;

	error = get_unकरो_list(&ulp);
	अगर (error)
		वापस ERR_PTR(error);

	rcu_पढ़ो_lock();
	spin_lock(&ulp->lock);
	un = lookup_unकरो(ulp, semid);
	spin_unlock(&ulp->lock);
	अगर (likely(un != शून्य))
		जाओ out;

	/* no unकरो काष्ठाure around - allocate one. */
	/* step 1: figure out the size of the semaphore array */
	sma = sem_obtain_object_check(ns, semid);
	अगर (IS_ERR(sma)) अणु
		rcu_पढ़ो_unlock();
		वापस ERR_CAST(sma);
	पूर्ण

	nsems = sma->sem_nsems;
	अगर (!ipc_rcu_getref(&sma->sem_perm)) अणु
		rcu_पढ़ो_unlock();
		un = ERR_PTR(-EIDRM);
		जाओ out;
	पूर्ण
	rcu_पढ़ो_unlock();

	/* step 2: allocate new unकरो काष्ठाure */
	new = kzalloc(माप(काष्ठा sem_unकरो) + माप(लघु)*nsems, GFP_KERNEL);
	अगर (!new) अणु
		ipc_rcu_putref(&sma->sem_perm, sem_rcu_मुक्त);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* step 3: Acquire the lock on semaphore array */
	rcu_पढ़ो_lock();
	sem_lock_and_putref(sma);
	अगर (!ipc_valid_object(&sma->sem_perm)) अणु
		sem_unlock(sma, -1);
		rcu_पढ़ो_unlock();
		kमुक्त(new);
		un = ERR_PTR(-EIDRM);
		जाओ out;
	पूर्ण
	spin_lock(&ulp->lock);

	/*
	 * step 4: check क्रम races: did someone अन्यथा allocate the unकरो काष्ठा?
	 */
	un = lookup_unकरो(ulp, semid);
	अगर (un) अणु
		kमुक्त(new);
		जाओ success;
	पूर्ण
	/* step 5: initialize & link new unकरो काष्ठाure */
	new->semadj = (लघु *) &new[1];
	new->ulp = ulp;
	new->semid = semid;
	निश्चित_spin_locked(&ulp->lock);
	list_add_rcu(&new->list_proc, &ulp->list_proc);
	ipc_निश्चित_locked_object(&sma->sem_perm);
	list_add(&new->list_id, &sma->list_id);
	un = new;

success:
	spin_unlock(&ulp->lock);
	sem_unlock(sma, -1);
out:
	वापस un;
पूर्ण

अटल दीर्घ करो_semसमयकरोp(पूर्णांक semid, काष्ठा sembuf __user *tsops,
		अचिन्हित nsops, स्थिर काष्ठा बारpec64 *समयout)
अणु
	पूर्णांक error = -EINVAL;
	काष्ठा sem_array *sma;
	काष्ठा sembuf fast_sops[SEMOPM_FAST];
	काष्ठा sembuf *sops = fast_sops, *sop;
	काष्ठा sem_unकरो *un;
	पूर्णांक max, locknum;
	bool unकरोs = false, alter = false, dupsop = false;
	काष्ठा sem_queue queue;
	अचिन्हित दीर्घ dup = 0, jअगरfies_left = 0;
	काष्ठा ipc_namespace *ns;

	ns = current->nsproxy->ipc_ns;

	अगर (nsops < 1 || semid < 0)
		वापस -EINVAL;
	अगर (nsops > ns->sc_semopm)
		वापस -E2BIG;
	अगर (nsops > SEMOPM_FAST) अणु
		sops = kvदो_स्मृति_array(nsops, माप(*sops), GFP_KERNEL);
		अगर (sops == शून्य)
			वापस -ENOMEM;
	पूर्ण

	अगर (copy_from_user(sops, tsops, nsops * माप(*tsops))) अणु
		error =  -EFAULT;
		जाओ out_मुक्त;
	पूर्ण

	अगर (समयout) अणु
		अगर (समयout->tv_sec < 0 || समयout->tv_nsec < 0 ||
			समयout->tv_nsec >= 1000000000L) अणु
			error = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
		jअगरfies_left = बारpec64_to_jअगरfies(समयout);
	पूर्ण

	max = 0;
	क्रम (sop = sops; sop < sops + nsops; sop++) अणु
		अचिन्हित दीर्घ mask = 1ULL << ((sop->sem_num) % BITS_PER_LONG);

		अगर (sop->sem_num >= max)
			max = sop->sem_num;
		अगर (sop->sem_flg & SEM_UNDO)
			unकरोs = true;
		अगर (dup & mask) अणु
			/*
			 * There was a previous alter access that appears
			 * to have accessed the same semaphore, thus use
			 * the dupsop logic. "appears", because the detection
			 * can only check % BITS_PER_LONG.
			 */
			dupsop = true;
		पूर्ण
		अगर (sop->sem_op != 0) अणु
			alter = true;
			dup |= mask;
		पूर्ण
	पूर्ण

	अगर (unकरोs) अणु
		/* On success, find_alloc_unकरो takes the rcu_पढ़ो_lock */
		un = find_alloc_unकरो(ns, semid);
		अगर (IS_ERR(un)) अणु
			error = PTR_ERR(un);
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण अन्यथा अणु
		un = शून्य;
		rcu_पढ़ो_lock();
	पूर्ण

	sma = sem_obtain_object_check(ns, semid);
	अगर (IS_ERR(sma)) अणु
		rcu_पढ़ो_unlock();
		error = PTR_ERR(sma);
		जाओ out_मुक्त;
	पूर्ण

	error = -EFBIG;
	अगर (max >= sma->sem_nsems) अणु
		rcu_पढ़ो_unlock();
		जाओ out_मुक्त;
	पूर्ण

	error = -EACCES;
	अगर (ipcperms(ns, &sma->sem_perm, alter ? S_IWUGO : S_IRUGO)) अणु
		rcu_पढ़ो_unlock();
		जाओ out_मुक्त;
	पूर्ण

	error = security_sem_semop(&sma->sem_perm, sops, nsops, alter);
	अगर (error) अणु
		rcu_पढ़ो_unlock();
		जाओ out_मुक्त;
	पूर्ण

	error = -EIDRM;
	locknum = sem_lock(sma, sops, nsops);
	/*
	 * We eventually might perक्रमm the following check in a lockless
	 * fashion, considering ipc_valid_object() locking स्थिरraपूर्णांकs.
	 * If nsops == 1 and there is no contention क्रम sem_perm.lock, then
	 * only a per-semaphore lock is held and it's OK to proceed with the
	 * check below. More details on the fine grained locking scheme
	 * entangled here and why it's RMID race safe on comments at sem_lock()
	 */
	अगर (!ipc_valid_object(&sma->sem_perm))
		जाओ out_unlock_मुक्त;
	/*
	 * semid identअगरiers are not unique - find_alloc_unकरो may have
	 * allocated an unकरो काष्ठाure, it was invalidated by an RMID
	 * and now a new array with received the same id. Check and fail.
	 * This हाल can be detected checking un->semid. The existence of
	 * "un" itself is guaranteed by rcu.
	 */
	अगर (un && un->semid == -1)
		जाओ out_unlock_मुक्त;

	queue.sops = sops;
	queue.nsops = nsops;
	queue.unकरो = un;
	queue.pid = task_tgid(current);
	queue.alter = alter;
	queue.dupsop = dupsop;

	error = perक्रमm_atomic_semop(sma, &queue);
	अगर (error == 0) अणु /* non-blocking successful path */
		DEFINE_WAKE_Q(wake_q);

		/*
		 * If the operation was successful, then करो
		 * the required updates.
		 */
		अगर (alter)
			करो_smart_update(sma, sops, nsops, 1, &wake_q);
		अन्यथा
			set_semoसमय(sma, sops);

		sem_unlock(sma, locknum);
		rcu_पढ़ो_unlock();
		wake_up_q(&wake_q);

		जाओ out_मुक्त;
	पूर्ण
	अगर (error < 0) /* non-blocking error path */
		जाओ out_unlock_मुक्त;

	/*
	 * We need to sleep on this operation, so we put the current
	 * task पूर्णांकo the pending queue and go to sleep.
	 */
	अगर (nsops == 1) अणु
		काष्ठा sem *curr;
		पूर्णांक idx = array_index_nospec(sops->sem_num, sma->sem_nsems);
		curr = &sma->sems[idx];

		अगर (alter) अणु
			अगर (sma->complex_count) अणु
				list_add_tail(&queue.list,
						&sma->pending_alter);
			पूर्ण अन्यथा अणु

				list_add_tail(&queue.list,
						&curr->pending_alter);
			पूर्ण
		पूर्ण अन्यथा अणु
			list_add_tail(&queue.list, &curr->pending_स्थिर);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!sma->complex_count)
			merge_queues(sma);

		अगर (alter)
			list_add_tail(&queue.list, &sma->pending_alter);
		अन्यथा
			list_add_tail(&queue.list, &sma->pending_स्थिर);

		sma->complex_count++;
	पूर्ण

	करो अणु
		/* memory ordering ensured by the lock in sem_lock() */
		WRITE_ONCE(queue.status, -EINTR);
		queue.sleeper = current;

		/* memory ordering is ensured by the lock in sem_lock() */
		__set_current_state(TASK_INTERRUPTIBLE);
		sem_unlock(sma, locknum);
		rcu_पढ़ो_unlock();

		अगर (समयout)
			jअगरfies_left = schedule_समयout(jअगरfies_left);
		अन्यथा
			schedule();

		/*
		 * fastpath: the semop has completed, either successfully or
		 * not, from the syscall pov, is quite irrelevant to us at this
		 * poपूर्णांक; we're करोne.
		 *
		 * We _करो_ care, nonetheless, about being awoken by a संकेत or
		 * spuriously.  The queue.status is checked again in the
		 * slowpath (aka after taking sem_lock), such that we can detect
		 * scenarios where we were awakened बाह्यally, during the
		 * winकरोw between wake_q_add() and wake_up_q().
		 */
		error = READ_ONCE(queue.status);
		अगर (error != -EINTR) अणु
			/* see SEM_BARRIER_2 क्रम purpose/pairing */
			smp_acquire__after_ctrl_dep();
			जाओ out_मुक्त;
		पूर्ण

		rcu_पढ़ो_lock();
		locknum = sem_lock(sma, sops, nsops);

		अगर (!ipc_valid_object(&sma->sem_perm))
			जाओ out_unlock_मुक्त;

		/*
		 * No necessity क्रम any barrier: We are protect by sem_lock()
		 */
		error = READ_ONCE(queue.status);

		/*
		 * If queue.status != -EINTR we are woken up by another process.
		 * Leave without unlink_queue(), but with sem_unlock().
		 */
		अगर (error != -EINTR)
			जाओ out_unlock_मुक्त;

		/*
		 * If an पूर्णांकerrupt occurred we have to clean up the queue.
		 */
		अगर (समयout && jअगरfies_left == 0)
			error = -EAGAIN;
	पूर्ण जबतक (error == -EINTR && !संकेत_pending(current)); /* spurious */

	unlink_queue(sma, &queue);

out_unlock_मुक्त:
	sem_unlock(sma, locknum);
	rcu_पढ़ो_unlock();
out_मुक्त:
	अगर (sops != fast_sops)
		kvमुक्त(sops);
	वापस error;
पूर्ण

दीर्घ ksys_semसमयकरोp(पूर्णांक semid, काष्ठा sembuf __user *tsops,
		     अचिन्हित पूर्णांक nsops, स्थिर काष्ठा __kernel_बारpec __user *समयout)
अणु
	अगर (समयout) अणु
		काष्ठा बारpec64 ts;
		अगर (get_बारpec64(&ts, समयout))
			वापस -EFAULT;
		वापस करो_semसमयकरोp(semid, tsops, nsops, &ts);
	पूर्ण
	वापस करो_semसमयकरोp(semid, tsops, nsops, शून्य);
पूर्ण

SYSCALL_DEFINE4(semसमयकरोp, पूर्णांक, semid, काष्ठा sembuf __user *, tsops,
		अचिन्हित पूर्णांक, nsops, स्थिर काष्ठा __kernel_बारpec __user *, समयout)
अणु
	वापस ksys_semसमयकरोp(semid, tsops, nsops, समयout);
पूर्ण

#अगर_घोषित CONFIG_COMPAT_32BIT_TIME
दीर्घ compat_ksys_semसमयकरोp(पूर्णांक semid, काष्ठा sembuf __user *tsems,
			    अचिन्हित पूर्णांक nsops,
			    स्थिर काष्ठा old_बारpec32 __user *समयout)
अणु
	अगर (समयout) अणु
		काष्ठा बारpec64 ts;
		अगर (get_old_बारpec32(&ts, समयout))
			वापस -EFAULT;
		वापस करो_semसमयकरोp(semid, tsems, nsops, &ts);
	पूर्ण
	वापस करो_semसमयकरोp(semid, tsems, nsops, शून्य);
पूर्ण

SYSCALL_DEFINE4(semसमयकरोp_समय32, पूर्णांक, semid, काष्ठा sembuf __user *, tsems,
		       अचिन्हित पूर्णांक, nsops,
		       स्थिर काष्ठा old_बारpec32 __user *, समयout)
अणु
	वापस compat_ksys_semसमयकरोp(semid, tsems, nsops, समयout);
पूर्ण
#पूर्ण_अगर

SYSCALL_DEFINE3(semop, पूर्णांक, semid, काष्ठा sembuf __user *, tsops,
		अचिन्हित, nsops)
अणु
	वापस करो_semसमयकरोp(semid, tsops, nsops, शून्य);
पूर्ण

/* If CLONE_SYSVSEM is set, establish sharing of SEM_UNDO state between
 * parent and child tasks.
 */

पूर्णांक copy_semunकरो(अचिन्हित दीर्घ clone_flags, काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा sem_unकरो_list *unकरो_list;
	पूर्णांक error;

	अगर (clone_flags & CLONE_SYSVSEM) अणु
		error = get_unकरो_list(&unकरो_list);
		अगर (error)
			वापस error;
		refcount_inc(&unकरो_list->refcnt);
		tsk->sysvsem.unकरो_list = unकरो_list;
	पूर्ण अन्यथा
		tsk->sysvsem.unकरो_list = शून्य;

	वापस 0;
पूर्ण

/*
 * add semadj values to semaphores, मुक्त unकरो काष्ठाures.
 * unकरो काष्ठाures are not मुक्तd when semaphore arrays are destroyed
 * so some of them may be out of date.
 * IMPLEMENTATION NOTE: There is some confusion over whether the
 * set of adjusपंचांगents that needs to be करोne should be करोne in an atomic
 * manner or not. That is, अगर we are attempting to decrement the semval
 * should we queue up and रुको until we can करो so legally?
 * The original implementation attempted to करो this (queue and रुको).
 * The current implementation करोes not करो so. The POSIX standard
 * and SVID should be consulted to determine what behavior is mandated.
 */
व्योम निकास_sem(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा sem_unकरो_list *ulp;

	ulp = tsk->sysvsem.unकरो_list;
	अगर (!ulp)
		वापस;
	tsk->sysvsem.unकरो_list = शून्य;

	अगर (!refcount_dec_and_test(&ulp->refcnt))
		वापस;

	क्रम (;;) अणु
		काष्ठा sem_array *sma;
		काष्ठा sem_unकरो *un;
		पूर्णांक semid, i;
		DEFINE_WAKE_Q(wake_q);

		cond_resched();

		rcu_पढ़ो_lock();
		un = list_entry_rcu(ulp->list_proc.next,
				    काष्ठा sem_unकरो, list_proc);
		अगर (&un->list_proc == &ulp->list_proc) अणु
			/*
			 * We must रुको क्रम मुक्तary() beक्रमe मुक्तing this ulp,
			 * in हाल we raced with last sem_unकरो. There is a small
			 * possibility where we निकास जबतक मुक्तary() didn't
			 * finish unlocking sem_unकरो_list.
			 */
			spin_lock(&ulp->lock);
			spin_unlock(&ulp->lock);
			rcu_पढ़ो_unlock();
			अवरोध;
		पूर्ण
		spin_lock(&ulp->lock);
		semid = un->semid;
		spin_unlock(&ulp->lock);

		/* निकास_sem raced with IPC_RMID, nothing to करो */
		अगर (semid == -1) अणु
			rcu_पढ़ो_unlock();
			जारी;
		पूर्ण

		sma = sem_obtain_object_check(tsk->nsproxy->ipc_ns, semid);
		/* निकास_sem raced with IPC_RMID, nothing to करो */
		अगर (IS_ERR(sma)) अणु
			rcu_पढ़ो_unlock();
			जारी;
		पूर्ण

		sem_lock(sma, शून्य, -1);
		/* निकास_sem raced with IPC_RMID, nothing to करो */
		अगर (!ipc_valid_object(&sma->sem_perm)) अणु
			sem_unlock(sma, -1);
			rcu_पढ़ो_unlock();
			जारी;
		पूर्ण
		un = __lookup_unकरो(ulp, semid);
		अगर (un == शून्य) अणु
			/* निकास_sem raced with IPC_RMID+semget() that created
			 * exactly the same semid. Nothing to करो.
			 */
			sem_unlock(sma, -1);
			rcu_पढ़ो_unlock();
			जारी;
		पूर्ण

		/* हटाओ un from the linked lists */
		ipc_निश्चित_locked_object(&sma->sem_perm);
		list_del(&un->list_id);

		spin_lock(&ulp->lock);
		list_del_rcu(&un->list_proc);
		spin_unlock(&ulp->lock);

		/* perक्रमm adjusपंचांगents रेजिस्टरed in un */
		क्रम (i = 0; i < sma->sem_nsems; i++) अणु
			काष्ठा sem *semaphore = &sma->sems[i];
			अगर (un->semadj[i]) अणु
				semaphore->semval += un->semadj[i];
				/*
				 * Range checks of the new semaphore value,
				 * not defined by sus:
				 * - Some unices ignore the unकरो entirely
				 *   (e.g. HP UX 11i 11.22, Tru64 V5.1)
				 * - some cap the value (e.g. FreeBSD caps
				 *   at 0, but करोesn't enक्रमce SEMVMX)
				 *
				 * Linux caps the semaphore value, both at 0
				 * and at SEMVMX.
				 *
				 *	Manfred <manfred@colorfullअगरe.com>
				 */
				अगर (semaphore->semval < 0)
					semaphore->semval = 0;
				अगर (semaphore->semval > SEMVMX)
					semaphore->semval = SEMVMX;
				ipc_update_pid(&semaphore->sempid, task_tgid(current));
			पूर्ण
		पूर्ण
		/* maybe some queued-up processes were रुकोing क्रम this */
		करो_smart_update(sma, शून्य, 0, 1, &wake_q);
		sem_unlock(sma, -1);
		rcu_पढ़ो_unlock();
		wake_up_q(&wake_q);

		kमुक्त_rcu(un, rcu);
	पूर्ण
	kमुक्त(ulp);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक sysvipc_sem_proc_show(काष्ठा seq_file *s, व्योम *it)
अणु
	काष्ठा user_namespace *user_ns = seq_user_ns(s);
	काष्ठा kern_ipc_perm *ipcp = it;
	काष्ठा sem_array *sma = container_of(ipcp, काष्ठा sem_array, sem_perm);
	समय64_t sem_oसमय;

	/*
	 * The proc पूर्णांकerface isn't aware of sem_lock(), it calls
	 * ipc_lock_object() directly (in sysvipc_find_ipc).
	 * In order to stay compatible with sem_lock(), we must
	 * enter / leave complex_mode.
	 */
	complexmode_enter(sma);

	sem_oसमय = get_semoसमय(sma);

	seq_म_लिखो(s,
		   "%10d %10d  %4o %10u %5u %5u %5u %5u %10llu %10llu\n",
		   sma->sem_perm.key,
		   sma->sem_perm.id,
		   sma->sem_perm.mode,
		   sma->sem_nsems,
		   from_kuid_munged(user_ns, sma->sem_perm.uid),
		   from_kgid_munged(user_ns, sma->sem_perm.gid),
		   from_kuid_munged(user_ns, sma->sem_perm.cuid),
		   from_kgid_munged(user_ns, sma->sem_perm.cgid),
		   sem_oसमय,
		   sma->sem_स_समय);

	complexmode_tryleave(sma);

	वापस 0;
पूर्ण
#पूर्ण_अगर
