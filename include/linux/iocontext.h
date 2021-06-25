<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित IOCONTEXT_H
#घोषणा IOCONTEXT_H

#समावेश <linux/radix-tree.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/workqueue.h>

क्रमागत अणु
	ICQ_EXITED		= 1 << 2,
	ICQ_DESTROYED		= 1 << 3,
पूर्ण;

/*
 * An io_cq (icq) is association between an io_context (ioc) and a
 * request_queue (q).  This is used by elevators which need to track
 * inक्रमmation per ioc - q pair.
 *
 * Elevator can request use of icq by setting elevator_type->icq_size and
 * ->icq_align.  Both size and align must be larger than that of काष्ठा
 * io_cq and elevator can use the tail area क्रम निजी inक्रमmation.  The
 * recommended way to करो this is defining a काष्ठा which contains io_cq as
 * the first member followed by निजी members and using its size and
 * align.  For example,
 *
 *	काष्ठा snail_io_cq अणु
 *		काष्ठा io_cq	icq;
 *		पूर्णांक		poke_snail;
 *		पूर्णांक		feed_snail;
 *	पूर्ण;
 *
 *	काष्ठा elevator_type snail_elv_type अणु
 *		.ops =		अणु ... पूर्ण,
 *		.icq_size =	माप(काष्ठा snail_io_cq),
 *		.icq_align =	__alignof__(काष्ठा snail_io_cq),
 *		...
 *	पूर्ण;
 *
 * If icq_size is set, block core will manage icq's.  All requests will
 * have its ->elv.icq field set beक्रमe elevator_ops->elevator_set_req_fn()
 * is called and be holding a reference to the associated io_context.
 *
 * Whenever a new icq is created, elevator_ops->elevator_init_icq_fn() is
 * called and, on deकाष्ठाion, ->elevator_निकास_icq_fn().  Both functions
 * are called with both the associated io_context and queue locks held.
 *
 * Elevator is allowed to lookup icq using ioc_lookup_icq() जबतक holding
 * queue lock but the वापसed icq is valid only until the queue lock is
 * released.  Elevators can not and should not try to create or destroy
 * icq's.
 *
 * As icq's are linked from both ioc and q, the locking rules are a bit
 * complex.
 *
 * - ioc lock nests inside q lock.
 *
 * - ioc->icq_list and icq->ioc_node are रक्षित by ioc lock.
 *   q->icq_list and icq->q_node by q lock.
 *
 * - ioc->icq_tree and ioc->icq_hपूर्णांक are रक्षित by ioc lock, जबतक icq
 *   itself is रक्षित by q lock.  However, both the indexes and icq
 *   itself are also RCU managed and lookup can be perक्रमmed holding only
 *   the q lock.
 *
 * - icq's are not reference counted.  They are destroyed when either the
 *   ioc or q goes away.  Each request with icq set holds an extra
 *   reference to ioc to ensure it stays until the request is completed.
 *
 * - Linking and unlinking icq's are perक्रमmed जबतक holding both ioc and q
 *   locks.  Due to the lock ordering, q निकास is simple but ioc निकास
 *   requires reverse-order द्विगुन lock dance.
 */
काष्ठा io_cq अणु
	काष्ठा request_queue	*q;
	काष्ठा io_context	*ioc;

	/*
	 * q_node and ioc_node link io_cq through icq_list of q and ioc
	 * respectively.  Both fields are unused once ioc_निकास_icq() is
	 * called and shared with __rcu_icq_cache and __rcu_head which are
	 * used क्रम RCU मुक्त of io_cq.
	 */
	जोड़ अणु
		काष्ठा list_head	q_node;
		काष्ठा kmem_cache	*__rcu_icq_cache;
	पूर्ण;
	जोड़ अणु
		काष्ठा hlist_node	ioc_node;
		काष्ठा rcu_head		__rcu_head;
	पूर्ण;

	अचिन्हित पूर्णांक		flags;
पूर्ण;

/*
 * I/O subप्रणाली state of the associated processes.  It is refcounted
 * and kदो_स्मृति'ed. These could be shared between processes.
 */
काष्ठा io_context अणु
	atomic_दीर्घ_t refcount;
	atomic_t active_ref;
	atomic_t nr_tasks;

	/* all the fields below are रक्षित by this lock */
	spinlock_t lock;

	अचिन्हित लघु ioprio;

	काष्ठा radix_tree_root	icq_tree;
	काष्ठा io_cq __rcu	*icq_hपूर्णांक;
	काष्ठा hlist_head	icq_list;

	काष्ठा work_काष्ठा release_work;
पूर्ण;

/**
 * get_io_context_active - get active reference on ioc
 * @ioc: ioc of पूर्णांकerest
 *
 * Only iocs with active reference can issue new IOs.  This function
 * acquires an active reference on @ioc.  The caller must alपढ़ोy have an
 * active reference on @ioc.
 */
अटल अंतरभूत व्योम get_io_context_active(काष्ठा io_context *ioc)
अणु
	WARN_ON_ONCE(atomic_दीर्घ_पढ़ो(&ioc->refcount) <= 0);
	WARN_ON_ONCE(atomic_पढ़ो(&ioc->active_ref) <= 0);
	atomic_दीर्घ_inc(&ioc->refcount);
	atomic_inc(&ioc->active_ref);
पूर्ण

अटल अंतरभूत व्योम ioc_task_link(काष्ठा io_context *ioc)
अणु
	get_io_context_active(ioc);

	WARN_ON_ONCE(atomic_पढ़ो(&ioc->nr_tasks) <= 0);
	atomic_inc(&ioc->nr_tasks);
पूर्ण

काष्ठा task_काष्ठा;
#अगर_घोषित CONFIG_BLOCK
व्योम put_io_context(काष्ठा io_context *ioc);
व्योम put_io_context_active(काष्ठा io_context *ioc);
व्योम निकास_io_context(काष्ठा task_काष्ठा *task);
काष्ठा io_context *get_task_io_context(काष्ठा task_काष्ठा *task,
				       gfp_t gfp_flags, पूर्णांक node);
#अन्यथा
काष्ठा io_context;
अटल अंतरभूत व्योम put_io_context(काष्ठा io_context *ioc) अणु पूर्ण
अटल अंतरभूत व्योम निकास_io_context(काष्ठा task_काष्ठा *task) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
