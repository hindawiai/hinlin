<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  fs/eventpoll.c (Efficient event retrieval implementation)
 *  Copyright (C) 2001,...,2009	 Davide Libenzi
 *
 *  Davide Libenzi <davidel@xmailserver.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/माला.स>
#समावेश <linux/list.h>
#समावेश <linux/hash.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/रुको.h>
#समावेश <linux/eventpoll.h>
#समावेश <linux/mount.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mutex.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/device.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mman.h>
#समावेश <linux/atomic.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/compat.h>
#समावेश <linux/rculist.h>
#समावेश <net/busy_poll.h>

/*
 * LOCKING:
 * There are three level of locking required by epoll :
 *
 * 1) epmutex (mutex)
 * 2) ep->mtx (mutex)
 * 3) ep->lock (rwlock)
 *
 * The acquire order is the one listed above, from 1 to 3.
 * We need a rwlock (ep->lock) because we manipulate objects
 * from inside the poll callback, that might be triggered from
 * a wake_up() that in turn might be called from IRQ context.
 * So we can't sleep inside the poll callback and hence we need
 * a spinlock. During the event transfer loop (from kernel to
 * user space) we could end up sleeping due a copy_to_user(), so
 * we need a lock that will allow us to sleep. This lock is a
 * mutex (ep->mtx). It is acquired during the event transfer loop,
 * during epoll_ctl(EPOLL_CTL_DEL) and during eventpoll_release_file().
 * Then we also need a global mutex to serialize eventpoll_release_file()
 * and ep_मुक्त().
 * This mutex is acquired by ep_मुक्त() during the epoll file
 * cleanup path and it is also acquired by eventpoll_release_file()
 * अगर a file has been pushed inside an epoll set and it is then
 * बंद()d without a previous call to epoll_ctl(EPOLL_CTL_DEL).
 * It is also acquired when inserting an epoll fd onto another epoll
 * fd. We करो this so that we walk the epoll tree and ensure that this
 * insertion करोes not create a cycle of epoll file descriptors, which
 * could lead to deadlock. We need a global mutex to prevent two
 * simultaneous inserts (A पूर्णांकo B and B पूर्णांकo A) from racing and
 * स्थिरructing a cycle without either insert observing that it is
 * going to.
 * It is necessary to acquire multiple "ep->mtx"es at once in the
 * हाल when one epoll fd is added to another. In this हाल, we
 * always acquire the locks in the order of nesting (i.e. after
 * epoll_ctl(e1, EPOLL_CTL_ADD, e2), e1->mtx will always be acquired
 * beक्रमe e2->mtx). Since we disallow cycles of epoll file
 * descriptors, this ensures that the mutexes are well-ordered. In
 * order to communicate this nesting to lockdep, when walking a tree
 * of epoll file descriptors, we use the current recursion depth as
 * the lockdep subkey.
 * It is possible to drop the "ep->mtx" and to use the global
 * mutex "epmutex" (together with "ep->lock") to have it working,
 * but having "ep->mtx" will make the पूर्णांकerface more scalable.
 * Events that require holding "epmutex" are very rare, जबतक क्रम
 * normal operations the epoll निजी "ep->mtx" will guarantee
 * a better scalability.
 */

/* Epoll निजी bits inside the event mask */
#घोषणा EP_PRIVATE_BITS (EPOLLWAKEUP | EPOLLONESHOT | EPOLLET | EPOLLEXCLUSIVE)

#घोषणा EPOLLINOUT_BITS (EPOLLIN | EPOLLOUT)

#घोषणा EPOLLEXCLUSIVE_OK_BITS (EPOLLINOUT_BITS | EPOLLERR | EPOLLHUP | \
				EPOLLWAKEUP | EPOLLET | EPOLLEXCLUSIVE)

/* Maximum number of nesting allowed inside epoll sets */
#घोषणा EP_MAX_NESTS 4

#घोषणा EP_MAX_EVENTS (पूर्णांक_उच्च / माप(काष्ठा epoll_event))

#घोषणा EP_UNACTIVE_PTR ((व्योम *) -1L)

#घोषणा EP_ITEM_COST (माप(काष्ठा epitem) + माप(काष्ठा eppoll_entry))

काष्ठा epoll_filefd अणु
	काष्ठा file *file;
	पूर्णांक fd;
पूर्ण __packed;

/* Wait काष्ठाure used by the poll hooks */
काष्ठा eppoll_entry अणु
	/* List header used to link this काष्ठाure to the "struct epitem" */
	काष्ठा eppoll_entry *next;

	/* The "base" poपूर्णांकer is set to the container "struct epitem" */
	काष्ठा epitem *base;

	/*
	 * Wait queue item that will be linked to the target file रुको
	 * queue head.
	 */
	रुको_queue_entry_t रुको;

	/* The रुको queue head that linked the "wait" रुको queue item */
	रुको_queue_head_t *whead;
पूर्ण;

/*
 * Each file descriptor added to the eventpoll पूर्णांकerface will
 * have an entry of this type linked to the "rbr" RB tree.
 * Aव्योम increasing the size of this काष्ठा, there can be many thousands
 * of these on a server and we करो not want this to take another cache line.
 */
काष्ठा epitem अणु
	जोड़ अणु
		/* RB tree node links this काष्ठाure to the eventpoll RB tree */
		काष्ठा rb_node rbn;
		/* Used to मुक्त the काष्ठा epitem */
		काष्ठा rcu_head rcu;
	पूर्ण;

	/* List header used to link this काष्ठाure to the eventpoll पढ़ोy list */
	काष्ठा list_head rdllink;

	/*
	 * Works together "struct eventpoll"->ovflist in keeping the
	 * single linked chain of items.
	 */
	काष्ठा epitem *next;

	/* The file descriptor inक्रमmation this item refers to */
	काष्ठा epoll_filefd ffd;

	/* List containing poll रुको queues */
	काष्ठा eppoll_entry *pwqlist;

	/* The "container" of this item */
	काष्ठा eventpoll *ep;

	/* List header used to link this item to the "struct file" items list */
	काष्ठा hlist_node fllink;

	/* wakeup_source used when EPOLLWAKEUP is set */
	काष्ठा wakeup_source __rcu *ws;

	/* The काष्ठाure that describe the पूर्णांकerested events and the source fd */
	काष्ठा epoll_event event;
पूर्ण;

/*
 * This काष्ठाure is stored inside the "private_data" member of the file
 * काष्ठाure and represents the मुख्य data काष्ठाure क्रम the eventpoll
 * पूर्णांकerface.
 */
काष्ठा eventpoll अणु
	/*
	 * This mutex is used to ensure that files are not हटाओd
	 * जबतक epoll is using them. This is held during the event
	 * collection loop, the file cleanup path, the epoll file निकास
	 * code and the ctl operations.
	 */
	काष्ठा mutex mtx;

	/* Wait queue used by sys_epoll_रुको() */
	रुको_queue_head_t wq;

	/* Wait queue used by file->poll() */
	रुको_queue_head_t poll_रुको;

	/* List of पढ़ोy file descriptors */
	काष्ठा list_head rdllist;

	/* Lock which protects rdllist and ovflist */
	rwlock_t lock;

	/* RB tree root used to store monitored fd काष्ठाs */
	काष्ठा rb_root_cached rbr;

	/*
	 * This is a single linked list that chains all the "struct epitem" that
	 * happened जबतक transferring पढ़ोy events to userspace w/out
	 * holding ->lock.
	 */
	काष्ठा epitem *ovflist;

	/* wakeup_source used when ep_scan_पढ़ोy_list is running */
	काष्ठा wakeup_source *ws;

	/* The user that created the eventpoll descriptor */
	काष्ठा user_काष्ठा *user;

	काष्ठा file *file;

	/* used to optimize loop detection check */
	u64 gen;
	काष्ठा hlist_head refs;

#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
	/* used to track busy poll napi_id */
	अचिन्हित पूर्णांक napi_id;
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	/* tracks wakeup nests क्रम lockdep validation */
	u8 nests;
#पूर्ण_अगर
पूर्ण;

/* Wrapper काष्ठा used by poll queueing */
काष्ठा ep_pqueue अणु
	poll_table pt;
	काष्ठा epitem *epi;
पूर्ण;

/*
 * Configuration options available inside /proc/sys/fs/epoll/
 */
/* Maximum number of epoll watched descriptors, per user */
अटल दीर्घ max_user_watches __पढ़ो_mostly;

/*
 * This mutex is used to serialize ep_मुक्त() and eventpoll_release_file().
 */
अटल DEFINE_MUTEX(epmutex);

अटल u64 loop_check_gen = 0;

/* Used to check क्रम epoll file descriptor inclusion loops */
अटल काष्ठा eventpoll *inserting_पूर्णांकo;

/* Slab cache used to allocate "struct epitem" */
अटल काष्ठा kmem_cache *epi_cache __पढ़ो_mostly;

/* Slab cache used to allocate "struct eppoll_entry" */
अटल काष्ठा kmem_cache *pwq_cache __पढ़ो_mostly;

/*
 * List of files with newly added links, where we may need to limit the number
 * of emanating paths. Protected by the epmutex.
 */
काष्ठा epitems_head अणु
	काष्ठा hlist_head epitems;
	काष्ठा epitems_head *next;
पूर्ण;
अटल काष्ठा epitems_head *tfile_check_list = EP_UNACTIVE_PTR;

अटल काष्ठा kmem_cache *ephead_cache __पढ़ो_mostly;

अटल अंतरभूत व्योम मुक्त_ephead(काष्ठा epitems_head *head)
अणु
	अगर (head)
		kmem_cache_मुक्त(ephead_cache, head);
पूर्ण

अटल व्योम list_file(काष्ठा file *file)
अणु
	काष्ठा epitems_head *head;

	head = container_of(file->f_ep, काष्ठा epitems_head, epitems);
	अगर (!head->next) अणु
		head->next = tfile_check_list;
		tfile_check_list = head;
	पूर्ण
पूर्ण

अटल व्योम unlist_file(काष्ठा epitems_head *head)
अणु
	काष्ठा epitems_head *to_मुक्त = head;
	काष्ठा hlist_node *p = rcu_dereference(hlist_first_rcu(&head->epitems));
	अगर (p) अणु
		काष्ठा epitem *epi= container_of(p, काष्ठा epitem, fllink);
		spin_lock(&epi->ffd.file->f_lock);
		अगर (!hlist_empty(&head->epitems))
			to_मुक्त = शून्य;
		head->next = शून्य;
		spin_unlock(&epi->ffd.file->f_lock);
	पूर्ण
	मुक्त_ephead(to_मुक्त);
पूर्ण

#अगर_घोषित CONFIG_SYSCTL

#समावेश <linux/sysctl.h>

अटल दीर्घ दीर्घ_zero;
अटल दीर्घ दीर्घ_max = दीर्घ_उच्च;

काष्ठा ctl_table epoll_table[] = अणु
	अणु
		.procname	= "max_user_watches",
		.data		= &max_user_watches,
		.maxlen		= माप(max_user_watches),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
		.extra1		= &दीर्घ_zero,
		.extra2		= &दीर्घ_max,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
#पूर्ण_अगर /* CONFIG_SYSCTL */

अटल स्थिर काष्ठा file_operations eventpoll_fops;

अटल अंतरभूत पूर्णांक is_file_epoll(काष्ठा file *f)
अणु
	वापस f->f_op == &eventpoll_fops;
पूर्ण

/* Setup the काष्ठाure that is used as key क्रम the RB tree */
अटल अंतरभूत व्योम ep_set_ffd(काष्ठा epoll_filefd *ffd,
			      काष्ठा file *file, पूर्णांक fd)
अणु
	ffd->file = file;
	ffd->fd = fd;
पूर्ण

/* Compare RB tree keys */
अटल अंतरभूत पूर्णांक ep_cmp_ffd(काष्ठा epoll_filefd *p1,
			     काष्ठा epoll_filefd *p2)
अणु
	वापस (p1->file > p2->file ? +1:
	        (p1->file < p2->file ? -1 : p1->fd - p2->fd));
पूर्ण

/* Tells us अगर the item is currently linked */
अटल अंतरभूत पूर्णांक ep_is_linked(काष्ठा epitem *epi)
अणु
	वापस !list_empty(&epi->rdllink);
पूर्ण

अटल अंतरभूत काष्ठा eppoll_entry *ep_pwq_from_रुको(रुको_queue_entry_t *p)
अणु
	वापस container_of(p, काष्ठा eppoll_entry, रुको);
पूर्ण

/* Get the "struct epitem" from a रुको queue poपूर्णांकer */
अटल अंतरभूत काष्ठा epitem *ep_item_from_रुको(रुको_queue_entry_t *p)
अणु
	वापस container_of(p, काष्ठा eppoll_entry, रुको)->base;
पूर्ण

/**
 * ep_events_available - Checks अगर पढ़ोy events might be available.
 *
 * @ep: Poपूर्णांकer to the eventpoll context.
 *
 * Return: a value dअगरferent than %zero अगर पढ़ोy events are available,
 *          or %zero otherwise.
 */
अटल अंतरभूत पूर्णांक ep_events_available(काष्ठा eventpoll *ep)
अणु
	वापस !list_empty_careful(&ep->rdllist) ||
		READ_ONCE(ep->ovflist) != EP_UNACTIVE_PTR;
पूर्ण

#अगर_घोषित CONFIG_NET_RX_BUSY_POLL
अटल bool ep_busy_loop_end(व्योम *p, अचिन्हित दीर्घ start_समय)
अणु
	काष्ठा eventpoll *ep = p;

	वापस ep_events_available(ep) || busy_loop_समयout(start_समय);
पूर्ण

/*
 * Busy poll अगर globally on and supporting sockets found && no events,
 * busy loop will वापस अगर need_resched or ep_events_available.
 *
 * we must करो our busy polling with irqs enabled
 */
अटल bool ep_busy_loop(काष्ठा eventpoll *ep, पूर्णांक nonblock)
अणु
	अचिन्हित पूर्णांक napi_id = READ_ONCE(ep->napi_id);

	अगर ((napi_id >= MIN_NAPI_ID) && net_busy_loop_on()) अणु
		napi_busy_loop(napi_id, nonblock ? शून्य : ep_busy_loop_end, ep, false,
			       BUSY_POLL_BUDGET);
		अगर (ep_events_available(ep))
			वापस true;
		/*
		 * Busy poll समयd out.  Drop NAPI ID क्रम now, we can add
		 * it back in when we have moved a socket with a valid NAPI
		 * ID onto the पढ़ोy list.
		 */
		ep->napi_id = 0;
		वापस false;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Set epoll busy poll NAPI ID from sk.
 */
अटल अंतरभूत व्योम ep_set_busy_poll_napi_id(काष्ठा epitem *epi)
अणु
	काष्ठा eventpoll *ep;
	अचिन्हित पूर्णांक napi_id;
	काष्ठा socket *sock;
	काष्ठा sock *sk;

	अगर (!net_busy_loop_on())
		वापस;

	sock = sock_from_file(epi->ffd.file);
	अगर (!sock)
		वापस;

	sk = sock->sk;
	अगर (!sk)
		वापस;

	napi_id = READ_ONCE(sk->sk_napi_id);
	ep = epi->ep;

	/* Non-NAPI IDs can be rejected
	 *	or
	 * Nothing to करो अगर we alपढ़ोy have this ID
	 */
	अगर (napi_id < MIN_NAPI_ID || napi_id == ep->napi_id)
		वापस;

	/* record NAPI ID क्रम use in next busy poll */
	ep->napi_id = napi_id;
पूर्ण

#अन्यथा

अटल अंतरभूत bool ep_busy_loop(काष्ठा eventpoll *ep, पूर्णांक nonblock)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम ep_set_busy_poll_napi_id(काष्ठा epitem *epi)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_NET_RX_BUSY_POLL */

/*
 * As described in commit 0ccf831cb lockdep: annotate epoll
 * the use of रुको queues used by epoll is करोne in a very controlled
 * manner. Wake ups can nest inside each other, but are never करोne
 * with the same locking. For example:
 *
 *   dfd = socket(...);
 *   efd1 = epoll_create();
 *   efd2 = epoll_create();
 *   epoll_ctl(efd1, EPOLL_CTL_ADD, dfd, ...);
 *   epoll_ctl(efd2, EPOLL_CTL_ADD, efd1, ...);
 *
 * When a packet arrives to the device underneath "dfd", the net code will
 * issue a wake_up() on its poll wake list. Epoll (efd1) has installed a
 * callback wakeup entry on that queue, and the wake_up() perक्रमmed by the
 * "dfd" net code will end up in ep_poll_callback(). At this poपूर्णांक epoll
 * (efd1) notices that it may have some event पढ़ोy, so it needs to wake up
 * the रुकोers on its poll रुको list (efd2). So it calls ep_poll_safewake()
 * that ends up in another wake_up(), after having checked about the
 * recursion स्थिरraपूर्णांकs. That are, no more than EP_MAX_POLLWAKE_NESTS, to
 * aव्योम stack blasting.
 *
 * When CONFIG_DEBUG_LOCK_ALLOC is enabled, make sure lockdep can handle
 * this special हाल of epoll.
 */
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC

अटल व्योम ep_poll_safewake(काष्ठा eventpoll *ep, काष्ठा epitem *epi)
अणु
	काष्ठा eventpoll *ep_src;
	अचिन्हित दीर्घ flags;
	u8 nests = 0;

	/*
	 * To set the subclass or nesting level क्रम spin_lock_irqsave_nested()
	 * it might be natural to create a per-cpu nest count. However, since
	 * we can recurse on ep->poll_रुको.lock, and a non-raw spinlock can
	 * schedule() in the -rt kernel, the per-cpu variable are no दीर्घer
	 * रक्षित. Thus, we are पूर्णांकroducing a per eventpoll nest field.
	 * If we are not being call from ep_poll_callback(), epi is शून्य and
	 * we are at the first level of nesting, 0. Otherwise, we are being
	 * called from ep_poll_callback() and अगर a previous wakeup source is
	 * not an epoll file itself, we are at depth 1 since the wakeup source
	 * is depth 0. If the wakeup source is a previous epoll file in the
	 * wakeup chain then we use its nests value and record ours as
	 * nests + 1. The previous epoll file nests value is stable since its
	 * alपढ़ोy holding its own poll_रुको.lock.
	 */
	अगर (epi) अणु
		अगर ((is_file_epoll(epi->ffd.file))) अणु
			ep_src = epi->ffd.file->निजी_data;
			nests = ep_src->nests;
		पूर्ण अन्यथा अणु
			nests = 1;
		पूर्ण
	पूर्ण
	spin_lock_irqsave_nested(&ep->poll_रुको.lock, flags, nests);
	ep->nests = nests + 1;
	wake_up_locked_poll(&ep->poll_रुको, EPOLLIN);
	ep->nests = 0;
	spin_unlock_irqrestore(&ep->poll_रुको.lock, flags);
पूर्ण

#अन्यथा

अटल व्योम ep_poll_safewake(काष्ठा eventpoll *ep, काष्ठा epitem *epi)
अणु
	wake_up_poll(&ep->poll_रुको, EPOLLIN);
पूर्ण

#पूर्ण_अगर

अटल व्योम ep_हटाओ_रुको_queue(काष्ठा eppoll_entry *pwq)
अणु
	रुको_queue_head_t *whead;

	rcu_पढ़ो_lock();
	/*
	 * If it is cleared by POLLFREE, it should be rcu-safe.
	 * If we पढ़ो शून्य we need a barrier paired with
	 * smp_store_release() in ep_poll_callback(), otherwise
	 * we rely on whead->lock.
	 */
	whead = smp_load_acquire(&pwq->whead);
	अगर (whead)
		हटाओ_रुको_queue(whead, &pwq->रुको);
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * This function unरेजिस्टरs poll callbacks from the associated file
 * descriptor.  Must be called with "mtx" held (or "epmutex" अगर called from
 * ep_मुक्त).
 */
अटल व्योम ep_unरेजिस्टर_pollरुको(काष्ठा eventpoll *ep, काष्ठा epitem *epi)
अणु
	काष्ठा eppoll_entry **p = &epi->pwqlist;
	काष्ठा eppoll_entry *pwq;

	जबतक ((pwq = *p) != शून्य) अणु
		*p = pwq->next;
		ep_हटाओ_रुको_queue(pwq);
		kmem_cache_मुक्त(pwq_cache, pwq);
	पूर्ण
पूर्ण

/* call only when ep->mtx is held */
अटल अंतरभूत काष्ठा wakeup_source *ep_wakeup_source(काष्ठा epitem *epi)
अणु
	वापस rcu_dereference_check(epi->ws, lockdep_is_held(&epi->ep->mtx));
पूर्ण

/* call only when ep->mtx is held */
अटल अंतरभूत व्योम ep_pm_stay_awake(काष्ठा epitem *epi)
अणु
	काष्ठा wakeup_source *ws = ep_wakeup_source(epi);

	अगर (ws)
		__pm_stay_awake(ws);
पूर्ण

अटल अंतरभूत bool ep_has_wakeup_source(काष्ठा epitem *epi)
अणु
	वापस rcu_access_poपूर्णांकer(epi->ws) ? true : false;
पूर्ण

/* call when ep->mtx cannot be held (ep_poll_callback) */
अटल अंतरभूत व्योम ep_pm_stay_awake_rcu(काष्ठा epitem *epi)
अणु
	काष्ठा wakeup_source *ws;

	rcu_पढ़ो_lock();
	ws = rcu_dereference(epi->ws);
	अगर (ws)
		__pm_stay_awake(ws);
	rcu_पढ़ो_unlock();
पूर्ण


/*
 * ep->mutex needs to be held because we could be hit by
 * eventpoll_release_file() and epoll_ctl().
 */
अटल व्योम ep_start_scan(काष्ठा eventpoll *ep, काष्ठा list_head *txlist)
अणु
	/*
	 * Steal the पढ़ोy list, and re-init the original one to the
	 * empty list. Also, set ep->ovflist to शून्य so that events
	 * happening जबतक looping w/out locks, are not lost. We cannot
	 * have the poll callback to queue directly on ep->rdllist,
	 * because we want the "sproc" callback to be able to करो it
	 * in a lockless way.
	 */
	lockdep_निश्चित_irqs_enabled();
	ग_लिखो_lock_irq(&ep->lock);
	list_splice_init(&ep->rdllist, txlist);
	WRITE_ONCE(ep->ovflist, शून्य);
	ग_लिखो_unlock_irq(&ep->lock);
पूर्ण

अटल व्योम ep_करोne_scan(काष्ठा eventpoll *ep,
			 काष्ठा list_head *txlist)
अणु
	काष्ठा epitem *epi, *nepi;

	ग_लिखो_lock_irq(&ep->lock);
	/*
	 * During the समय we spent inside the "sproc" callback, some
	 * other events might have been queued by the poll callback.
	 * We re-insert them inside the मुख्य पढ़ोy-list here.
	 */
	क्रम (nepi = READ_ONCE(ep->ovflist); (epi = nepi) != शून्य;
	     nepi = epi->next, epi->next = EP_UNACTIVE_PTR) अणु
		/*
		 * We need to check अगर the item is alपढ़ोy in the list.
		 * During the "sproc" callback execution समय, items are
		 * queued पूर्णांकo ->ovflist but the "txlist" might alपढ़ोy
		 * contain them, and the list_splice() below takes care of them.
		 */
		अगर (!ep_is_linked(epi)) अणु
			/*
			 * ->ovflist is LIFO, so we have to reverse it in order
			 * to keep in FIFO.
			 */
			list_add(&epi->rdllink, &ep->rdllist);
			ep_pm_stay_awake(epi);
		पूर्ण
	पूर्ण
	/*
	 * We need to set back ep->ovflist to EP_UNACTIVE_PTR, so that after
	 * releasing the lock, events will be queued in the normal way inside
	 * ep->rdllist.
	 */
	WRITE_ONCE(ep->ovflist, EP_UNACTIVE_PTR);

	/*
	 * Quickly re-inject items left on "txlist".
	 */
	list_splice(txlist, &ep->rdllist);
	__pm_relax(ep->ws);

	अगर (!list_empty(&ep->rdllist)) अणु
		अगर (रुकोqueue_active(&ep->wq))
			wake_up(&ep->wq);
	पूर्ण

	ग_लिखो_unlock_irq(&ep->lock);
पूर्ण

अटल व्योम epi_rcu_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा epitem *epi = container_of(head, काष्ठा epitem, rcu);
	kmem_cache_मुक्त(epi_cache, epi);
पूर्ण

/*
 * Removes a "struct epitem" from the eventpoll RB tree and deallocates
 * all the associated resources. Must be called with "mtx" held.
 */
अटल पूर्णांक ep_हटाओ(काष्ठा eventpoll *ep, काष्ठा epitem *epi)
अणु
	काष्ठा file *file = epi->ffd.file;
	काष्ठा epitems_head *to_मुक्त;
	काष्ठा hlist_head *head;

	lockdep_निश्चित_irqs_enabled();

	/*
	 * Removes poll रुको queue hooks.
	 */
	ep_unरेजिस्टर_pollरुको(ep, epi);

	/* Remove the current item from the list of epoll hooks */
	spin_lock(&file->f_lock);
	to_मुक्त = शून्य;
	head = file->f_ep;
	अगर (head->first == &epi->fllink && !epi->fllink.next) अणु
		file->f_ep = शून्य;
		अगर (!is_file_epoll(file)) अणु
			काष्ठा epitems_head *v;
			v = container_of(head, काष्ठा epitems_head, epitems);
			अगर (!smp_load_acquire(&v->next))
				to_मुक्त = v;
		पूर्ण
	पूर्ण
	hlist_del_rcu(&epi->fllink);
	spin_unlock(&file->f_lock);
	मुक्त_ephead(to_मुक्त);

	rb_erase_cached(&epi->rbn, &ep->rbr);

	ग_लिखो_lock_irq(&ep->lock);
	अगर (ep_is_linked(epi))
		list_del_init(&epi->rdllink);
	ग_लिखो_unlock_irq(&ep->lock);

	wakeup_source_unरेजिस्टर(ep_wakeup_source(epi));
	/*
	 * At this poपूर्णांक it is safe to मुक्त the eventpoll item. Use the जोड़
	 * field epi->rcu, since we are trying to minimize the size of
	 * 'struct epitem'. The 'rbn' field is no दीर्घer in use. Protected by
	 * ep->mtx. The rcu पढ़ो side, reverse_path_check_proc(), करोes not make
	 * use of the rbn field.
	 */
	call_rcu(&epi->rcu, epi_rcu_मुक्त);

	atomic_दीर्घ_dec(&ep->user->epoll_watches);

	वापस 0;
पूर्ण

अटल व्योम ep_मुक्त(काष्ठा eventpoll *ep)
अणु
	काष्ठा rb_node *rbp;
	काष्ठा epitem *epi;

	/* We need to release all tasks रुकोing क्रम these file */
	अगर (रुकोqueue_active(&ep->poll_रुको))
		ep_poll_safewake(ep, शून्य);

	/*
	 * We need to lock this because we could be hit by
	 * eventpoll_release_file() जबतक we're मुक्तing the "struct eventpoll".
	 * We करो not need to hold "ep->mtx" here because the epoll file
	 * is on the way to be हटाओd and no one has references to it
	 * anymore. The only hit might come from eventpoll_release_file() but
	 * holding "epmutex" is sufficient here.
	 */
	mutex_lock(&epmutex);

	/*
	 * Walks through the whole tree by unरेजिस्टरing poll callbacks.
	 */
	क्रम (rbp = rb_first_cached(&ep->rbr); rbp; rbp = rb_next(rbp)) अणु
		epi = rb_entry(rbp, काष्ठा epitem, rbn);

		ep_unरेजिस्टर_pollरुको(ep, epi);
		cond_resched();
	पूर्ण

	/*
	 * Walks through the whole tree by मुक्तing each "struct epitem". At this
	 * poपूर्णांक we are sure no poll callbacks will be lingering around, and also by
	 * holding "epmutex" we can be sure that no file cleanup code will hit
	 * us during this operation. So we can aव्योम the lock on "ep->lock".
	 * We करो not need to lock ep->mtx, either, we only करो it to prevent
	 * a lockdep warning.
	 */
	mutex_lock(&ep->mtx);
	जबतक ((rbp = rb_first_cached(&ep->rbr)) != शून्य) अणु
		epi = rb_entry(rbp, काष्ठा epitem, rbn);
		ep_हटाओ(ep, epi);
		cond_resched();
	पूर्ण
	mutex_unlock(&ep->mtx);

	mutex_unlock(&epmutex);
	mutex_destroy(&ep->mtx);
	मुक्त_uid(ep->user);
	wakeup_source_unरेजिस्टर(ep->ws);
	kमुक्त(ep);
पूर्ण

अटल पूर्णांक ep_eventpoll_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा eventpoll *ep = file->निजी_data;

	अगर (ep)
		ep_मुक्त(ep);

	वापस 0;
पूर्ण

अटल __poll_t ep_item_poll(स्थिर काष्ठा epitem *epi, poll_table *pt, पूर्णांक depth);

अटल __poll_t __ep_eventpoll_poll(काष्ठा file *file, poll_table *रुको, पूर्णांक depth)
अणु
	काष्ठा eventpoll *ep = file->निजी_data;
	LIST_HEAD(txlist);
	काष्ठा epitem *epi, *पंचांगp;
	poll_table pt;
	__poll_t res = 0;

	init_poll_funcptr(&pt, शून्य);

	/* Insert inside our poll रुको queue */
	poll_रुको(file, &ep->poll_रुको, रुको);

	/*
	 * Proceed to find out अगर wanted events are really available inside
	 * the पढ़ोy list.
	 */
	mutex_lock_nested(&ep->mtx, depth);
	ep_start_scan(ep, &txlist);
	list_क्रम_each_entry_safe(epi, पंचांगp, &txlist, rdllink) अणु
		अगर (ep_item_poll(epi, &pt, depth + 1)) अणु
			res = EPOLLIN | EPOLLRDNORM;
			अवरोध;
		पूर्ण अन्यथा अणु
			/*
			 * Item has been dropped पूर्णांकo the पढ़ोy list by the poll
			 * callback, but it's not actually पढ़ोy, as far as
			 * caller requested events goes. We can हटाओ it here.
			 */
			__pm_relax(ep_wakeup_source(epi));
			list_del_init(&epi->rdllink);
		पूर्ण
	पूर्ण
	ep_करोne_scan(ep, &txlist);
	mutex_unlock(&ep->mtx);
	वापस res;
पूर्ण

/*
 * Dअगरfers from ep_eventpoll_poll() in that पूर्णांकernal callers alपढ़ोy have
 * the ep->mtx so we need to start from depth=1, such that mutex_lock_nested()
 * is correctly annotated.
 */
अटल __poll_t ep_item_poll(स्थिर काष्ठा epitem *epi, poll_table *pt,
				 पूर्णांक depth)
अणु
	काष्ठा file *file = epi->ffd.file;
	__poll_t res;

	pt->_key = epi->event.events;
	अगर (!is_file_epoll(file))
		res = vfs_poll(file, pt);
	अन्यथा
		res = __ep_eventpoll_poll(file, pt, depth);
	वापस res & epi->event.events;
पूर्ण

अटल __poll_t ep_eventpoll_poll(काष्ठा file *file, poll_table *रुको)
अणु
	वापस __ep_eventpoll_poll(file, रुको, 0);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम ep_show_fdinfo(काष्ठा seq_file *m, काष्ठा file *f)
अणु
	काष्ठा eventpoll *ep = f->निजी_data;
	काष्ठा rb_node *rbp;

	mutex_lock(&ep->mtx);
	क्रम (rbp = rb_first_cached(&ep->rbr); rbp; rbp = rb_next(rbp)) अणु
		काष्ठा epitem *epi = rb_entry(rbp, काष्ठा epitem, rbn);
		काष्ठा inode *inode = file_inode(epi->ffd.file);

		seq_म_लिखो(m, "tfd: %8d events: %8x data: %16llx "
			   " pos:%lli ino:%lx sdev:%x\n",
			   epi->ffd.fd, epi->event.events,
			   (दीर्घ दीर्घ)epi->event.data,
			   (दीर्घ दीर्घ)epi->ffd.file->f_pos,
			   inode->i_ino, inode->i_sb->s_dev);
		अगर (seq_has_overflowed(m))
			अवरोध;
	पूर्ण
	mutex_unlock(&ep->mtx);
पूर्ण
#पूर्ण_अगर

/* File callbacks that implement the eventpoll file behaviour */
अटल स्थिर काष्ठा file_operations eventpoll_fops = अणु
#अगर_घोषित CONFIG_PROC_FS
	.show_fdinfo	= ep_show_fdinfo,
#पूर्ण_अगर
	.release	= ep_eventpoll_release,
	.poll		= ep_eventpoll_poll,
	.llseek		= noop_llseek,
पूर्ण;

/*
 * This is called from eventpoll_release() to unlink files from the eventpoll
 * पूर्णांकerface. We need to have this facility to cleanup correctly files that are
 * बंदd without being हटाओd from the eventpoll पूर्णांकerface.
 */
व्योम eventpoll_release_file(काष्ठा file *file)
अणु
	काष्ठा eventpoll *ep;
	काष्ठा epitem *epi;
	काष्ठा hlist_node *next;

	/*
	 * We करोn't want to get "file->f_lock" because it is not
	 * necessary. It is not necessary because we're in the "struct file"
	 * cleanup path, and this means that no one is using this file anymore.
	 * So, क्रम example, epoll_ctl() cannot hit here since अगर we reach this
	 * poपूर्णांक, the file counter alपढ़ोy went to zero and fget() would fail.
	 * The only hit might come from ep_मुक्त() but by holding the mutex
	 * will correctly serialize the operation. We करो need to acquire
	 * "ep->mtx" after "epmutex" because ep_हटाओ() requires it when called
	 * from anywhere but ep_मुक्त().
	 *
	 * Besides, ep_हटाओ() acquires the lock, so we can't hold it here.
	 */
	mutex_lock(&epmutex);
	अगर (unlikely(!file->f_ep)) अणु
		mutex_unlock(&epmutex);
		वापस;
	पूर्ण
	hlist_क्रम_each_entry_safe(epi, next, file->f_ep, fllink) अणु
		ep = epi->ep;
		mutex_lock_nested(&ep->mtx, 0);
		ep_हटाओ(ep, epi);
		mutex_unlock(&ep->mtx);
	पूर्ण
	mutex_unlock(&epmutex);
पूर्ण

अटल पूर्णांक ep_alloc(काष्ठा eventpoll **pep)
अणु
	पूर्णांक error;
	काष्ठा user_काष्ठा *user;
	काष्ठा eventpoll *ep;

	user = get_current_user();
	error = -ENOMEM;
	ep = kzalloc(माप(*ep), GFP_KERNEL);
	अगर (unlikely(!ep))
		जाओ मुक्त_uid;

	mutex_init(&ep->mtx);
	rwlock_init(&ep->lock);
	init_रुकोqueue_head(&ep->wq);
	init_रुकोqueue_head(&ep->poll_रुको);
	INIT_LIST_HEAD(&ep->rdllist);
	ep->rbr = RB_ROOT_CACHED;
	ep->ovflist = EP_UNACTIVE_PTR;
	ep->user = user;

	*pep = ep;

	वापस 0;

मुक्त_uid:
	मुक्त_uid(user);
	वापस error;
पूर्ण

/*
 * Search the file inside the eventpoll tree. The RB tree operations
 * are रक्षित by the "mtx" mutex, and ep_find() must be called with
 * "mtx" held.
 */
अटल काष्ठा epitem *ep_find(काष्ठा eventpoll *ep, काष्ठा file *file, पूर्णांक fd)
अणु
	पूर्णांक kcmp;
	काष्ठा rb_node *rbp;
	काष्ठा epitem *epi, *epir = शून्य;
	काष्ठा epoll_filefd ffd;

	ep_set_ffd(&ffd, file, fd);
	क्रम (rbp = ep->rbr.rb_root.rb_node; rbp; ) अणु
		epi = rb_entry(rbp, काष्ठा epitem, rbn);
		kcmp = ep_cmp_ffd(&ffd, &epi->ffd);
		अगर (kcmp > 0)
			rbp = rbp->rb_right;
		अन्यथा अगर (kcmp < 0)
			rbp = rbp->rb_left;
		अन्यथा अणु
			epir = epi;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस epir;
पूर्ण

#अगर_घोषित CONFIG_KCMP
अटल काष्ठा epitem *ep_find_tfd(काष्ठा eventpoll *ep, पूर्णांक tfd, अचिन्हित दीर्घ toff)
अणु
	काष्ठा rb_node *rbp;
	काष्ठा epitem *epi;

	क्रम (rbp = rb_first_cached(&ep->rbr); rbp; rbp = rb_next(rbp)) अणु
		epi = rb_entry(rbp, काष्ठा epitem, rbn);
		अगर (epi->ffd.fd == tfd) अणु
			अगर (toff == 0)
				वापस epi;
			अन्यथा
				toff--;
		पूर्ण
		cond_resched();
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा file *get_epoll_tfile_raw_ptr(काष्ठा file *file, पूर्णांक tfd,
				     अचिन्हित दीर्घ toff)
अणु
	काष्ठा file *file_raw;
	काष्ठा eventpoll *ep;
	काष्ठा epitem *epi;

	अगर (!is_file_epoll(file))
		वापस ERR_PTR(-EINVAL);

	ep = file->निजी_data;

	mutex_lock(&ep->mtx);
	epi = ep_find_tfd(ep, tfd, toff);
	अगर (epi)
		file_raw = epi->ffd.file;
	अन्यथा
		file_raw = ERR_PTR(-ENOENT);
	mutex_unlock(&ep->mtx);

	वापस file_raw;
पूर्ण
#पूर्ण_अगर /* CONFIG_KCMP */

/*
 * Adds a new entry to the tail of the list in a lockless way, i.e.
 * multiple CPUs are allowed to call this function concurrently.
 *
 * Beware: it is necessary to prevent any other modअगरications of the
 *         existing list until all changes are completed, in other words
 *         concurrent list_add_tail_lockless() calls should be रक्षित
 *         with a पढ़ो lock, where ग_लिखो lock acts as a barrier which
 *         makes sure all list_add_tail_lockless() calls are fully
 *         completed.
 *
 *        Also an element can be locklessly added to the list only in one
 *        direction i.e. either to the tail or to the head, otherwise
 *        concurrent access will corrupt the list.
 *
 * Return: %false अगर element has been alपढ़ोy added to the list, %true
 * otherwise.
 */
अटल अंतरभूत bool list_add_tail_lockless(काष्ठा list_head *new,
					  काष्ठा list_head *head)
अणु
	काष्ठा list_head *prev;

	/*
	 * This is simple 'new->next = head' operation, but cmpxchg()
	 * is used in order to detect that same element has been just
	 * added to the list from another CPU: the winner observes
	 * new->next == new.
	 */
	अगर (cmpxchg(&new->next, new, head) != new)
		वापस false;

	/*
	 * Initially ->next of a new element must be updated with the head
	 * (we are inserting to the tail) and only then poपूर्णांकers are atomically
	 * exchanged.  XCHG guarantees memory ordering, thus ->next should be
	 * updated beक्रमe poपूर्णांकers are actually swapped and poपूर्णांकers are
	 * swapped beक्रमe prev->next is updated.
	 */

	prev = xchg(&head->prev, new);

	/*
	 * It is safe to modअगरy prev->next and new->prev, because a new element
	 * is added only to the tail and new->next is updated beक्रमe XCHG.
	 */

	prev->next = new;
	new->prev = prev;

	वापस true;
पूर्ण

/*
 * Chains a new epi entry to the tail of the ep->ovflist in a lockless way,
 * i.e. multiple CPUs are allowed to call this function concurrently.
 *
 * Return: %false अगर epi element has been alपढ़ोy chained, %true otherwise.
 */
अटल अंतरभूत bool chain_epi_lockless(काष्ठा epitem *epi)
अणु
	काष्ठा eventpoll *ep = epi->ep;

	/* Fast preliminary check */
	अगर (epi->next != EP_UNACTIVE_PTR)
		वापस false;

	/* Check that the same epi has not been just chained from another CPU */
	अगर (cmpxchg(&epi->next, EP_UNACTIVE_PTR, शून्य) != EP_UNACTIVE_PTR)
		वापस false;

	/* Atomically exchange tail */
	epi->next = xchg(&ep->ovflist, epi);

	वापस true;
पूर्ण

/*
 * This is the callback that is passed to the रुको queue wakeup
 * mechanism. It is called by the stored file descriptors when they
 * have events to report.
 *
 * This callback takes a पढ़ो lock in order not to contend with concurrent
 * events from another file descriptor, thus all modअगरications to ->rdllist
 * or ->ovflist are lockless.  Read lock is paired with the ग_लिखो lock from
 * ep_scan_पढ़ोy_list(), which stops all list modअगरications and guarantees
 * that lists state is seen correctly.
 *
 * Another thing worth to mention is that ep_poll_callback() can be called
 * concurrently क्रम the same @epi from dअगरferent CPUs अगर poll table was inited
 * with several रुको queues entries.  Plural wakeup from dअगरferent CPUs of a
 * single रुको queue is serialized by wq.lock, but the हाल when multiple रुको
 * queues are used should be detected accordingly.  This is detected using
 * cmpxchg() operation.
 */
अटल पूर्णांक ep_poll_callback(रुको_queue_entry_t *रुको, अचिन्हित mode, पूर्णांक sync, व्योम *key)
अणु
	पूर्णांक pwake = 0;
	काष्ठा epitem *epi = ep_item_from_रुको(रुको);
	काष्ठा eventpoll *ep = epi->ep;
	__poll_t pollflags = key_to_poll(key);
	अचिन्हित दीर्घ flags;
	पूर्णांक ewake = 0;

	पढ़ो_lock_irqsave(&ep->lock, flags);

	ep_set_busy_poll_napi_id(epi);

	/*
	 * If the event mask करोes not contain any poll(2) event, we consider the
	 * descriptor to be disabled. This condition is likely the effect of the
	 * EPOLLONESHOT bit that disables the descriptor when an event is received,
	 * until the next EPOLL_CTL_MOD will be issued.
	 */
	अगर (!(epi->event.events & ~EP_PRIVATE_BITS))
		जाओ out_unlock;

	/*
	 * Check the events coming with the callback. At this stage, not
	 * every device reports the events in the "key" parameter of the
	 * callback. We need to be able to handle both हालs here, hence the
	 * test क्रम "key" != शून्य beक्रमe the event match test.
	 */
	अगर (pollflags && !(pollflags & epi->event.events))
		जाओ out_unlock;

	/*
	 * If we are transferring events to userspace, we can hold no locks
	 * (because we're accessing user memory, and because of linux f_op->poll()
	 * semantics). All the events that happen during that period of समय are
	 * chained in ep->ovflist and requeued later on.
	 */
	अगर (READ_ONCE(ep->ovflist) != EP_UNACTIVE_PTR) अणु
		अगर (chain_epi_lockless(epi))
			ep_pm_stay_awake_rcu(epi);
	पूर्ण अन्यथा अगर (!ep_is_linked(epi)) अणु
		/* In the usual हाल, add event to पढ़ोy list. */
		अगर (list_add_tail_lockless(&epi->rdllink, &ep->rdllist))
			ep_pm_stay_awake_rcu(epi);
	पूर्ण

	/*
	 * Wake up ( अगर active ) both the eventpoll रुको list and the ->poll()
	 * रुको list.
	 */
	अगर (रुकोqueue_active(&ep->wq)) अणु
		अगर ((epi->event.events & EPOLLEXCLUSIVE) &&
					!(pollflags & POLLFREE)) अणु
			चयन (pollflags & EPOLLINOUT_BITS) अणु
			हाल EPOLLIN:
				अगर (epi->event.events & EPOLLIN)
					ewake = 1;
				अवरोध;
			हाल EPOLLOUT:
				अगर (epi->event.events & EPOLLOUT)
					ewake = 1;
				अवरोध;
			हाल 0:
				ewake = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		wake_up(&ep->wq);
	पूर्ण
	अगर (रुकोqueue_active(&ep->poll_रुको))
		pwake++;

out_unlock:
	पढ़ो_unlock_irqrestore(&ep->lock, flags);

	/* We have to call this outside the lock */
	अगर (pwake)
		ep_poll_safewake(ep, epi);

	अगर (!(epi->event.events & EPOLLEXCLUSIVE))
		ewake = 1;

	अगर (pollflags & POLLFREE) अणु
		/*
		 * If we race with ep_हटाओ_रुको_queue() it can miss
		 * ->whead = शून्य and करो another हटाओ_रुको_queue() after
		 * us, so we can't use __हटाओ_रुको_queue().
		 */
		list_del_init(&रुको->entry);
		/*
		 * ->whead != शून्य protects us from the race with ep_मुक्त()
		 * or ep_हटाओ(), ep_हटाओ_रुको_queue() takes whead->lock
		 * held by the caller. Once we nullअगरy it, nothing protects
		 * ep/epi or even रुको.
		 */
		smp_store_release(&ep_pwq_from_रुको(रुको)->whead, शून्य);
	पूर्ण

	वापस ewake;
पूर्ण

/*
 * This is the callback that is used to add our रुको queue to the
 * target file wakeup lists.
 */
अटल व्योम ep_ptable_queue_proc(काष्ठा file *file, रुको_queue_head_t *whead,
				 poll_table *pt)
अणु
	काष्ठा ep_pqueue *epq = container_of(pt, काष्ठा ep_pqueue, pt);
	काष्ठा epitem *epi = epq->epi;
	काष्ठा eppoll_entry *pwq;

	अगर (unlikely(!epi))	// an earlier allocation has failed
		वापस;

	pwq = kmem_cache_alloc(pwq_cache, GFP_KERNEL);
	अगर (unlikely(!pwq)) अणु
		epq->epi = शून्य;
		वापस;
	पूर्ण

	init_रुकोqueue_func_entry(&pwq->रुको, ep_poll_callback);
	pwq->whead = whead;
	pwq->base = epi;
	अगर (epi->event.events & EPOLLEXCLUSIVE)
		add_रुको_queue_exclusive(whead, &pwq->रुको);
	अन्यथा
		add_रुको_queue(whead, &pwq->रुको);
	pwq->next = epi->pwqlist;
	epi->pwqlist = pwq;
पूर्ण

अटल व्योम ep_rbtree_insert(काष्ठा eventpoll *ep, काष्ठा epitem *epi)
अणु
	पूर्णांक kcmp;
	काष्ठा rb_node **p = &ep->rbr.rb_root.rb_node, *parent = शून्य;
	काष्ठा epitem *epic;
	bool lefपंचांगost = true;

	जबतक (*p) अणु
		parent = *p;
		epic = rb_entry(parent, काष्ठा epitem, rbn);
		kcmp = ep_cmp_ffd(&epi->ffd, &epic->ffd);
		अगर (kcmp > 0) अणु
			p = &parent->rb_right;
			lefपंचांगost = false;
		पूर्ण अन्यथा
			p = &parent->rb_left;
	पूर्ण
	rb_link_node(&epi->rbn, parent, p);
	rb_insert_color_cached(&epi->rbn, &ep->rbr, lefपंचांगost);
पूर्ण



#घोषणा PATH_ARR_SIZE 5
/*
 * These are the number paths of length 1 to 5, that we are allowing to emanate
 * from a single file of पूर्णांकerest. For example, we allow 1000 paths of length
 * 1, to emanate from each file of पूर्णांकerest. This essentially represents the
 * potential wakeup paths, which need to be limited in order to aव्योम massive
 * uncontrolled wakeup storms. The common use हाल should be a single ep which
 * is connected to n file sources. In this हाल each file source has 1 path
 * of length 1. Thus, the numbers below should be more than sufficient. These
 * path limits are enक्रमced during an EPOLL_CTL_ADD operation, since a modअगरy
 * and delete can't add additional paths. Protected by the epmutex.
 */
अटल स्थिर पूर्णांक path_limits[PATH_ARR_SIZE] = अणु 1000, 500, 100, 50, 10 पूर्ण;
अटल पूर्णांक path_count[PATH_ARR_SIZE];

अटल पूर्णांक path_count_inc(पूर्णांक nests)
अणु
	/* Allow an arbitrary number of depth 1 paths */
	अगर (nests == 0)
		वापस 0;

	अगर (++path_count[nests] > path_limits[nests])
		वापस -1;
	वापस 0;
पूर्ण

अटल व्योम path_count_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PATH_ARR_SIZE; i++)
		path_count[i] = 0;
पूर्ण

अटल पूर्णांक reverse_path_check_proc(काष्ठा hlist_head *refs, पूर्णांक depth)
अणु
	पूर्णांक error = 0;
	काष्ठा epitem *epi;

	अगर (depth > EP_MAX_NESTS) /* too deep nesting */
		वापस -1;

	/* CTL_DEL can हटाओ links here, but that can't increase our count */
	hlist_क्रम_each_entry_rcu(epi, refs, fllink) अणु
		काष्ठा hlist_head *refs = &epi->ep->refs;
		अगर (hlist_empty(refs))
			error = path_count_inc(depth);
		अन्यथा
			error = reverse_path_check_proc(refs, depth + 1);
		अगर (error != 0)
			अवरोध;
	पूर्ण
	वापस error;
पूर्ण

/**
 * reverse_path_check - The tfile_check_list is list of epitem_head, which have
 *                      links that are proposed to be newly added. We need to
 *                      make sure that those added links करोn't add too many
 *                      paths such that we will spend all our समय waking up
 *                      eventpoll objects.
 *
 * Return: %zero अगर the proposed links करोn't create too many paths,
 *	    %-1 otherwise.
 */
अटल पूर्णांक reverse_path_check(व्योम)
अणु
	काष्ठा epitems_head *p;

	क्रम (p = tfile_check_list; p != EP_UNACTIVE_PTR; p = p->next) अणु
		पूर्णांक error;
		path_count_init();
		rcu_पढ़ो_lock();
		error = reverse_path_check_proc(&p->epitems, 0);
		rcu_पढ़ो_unlock();
		अगर (error)
			वापस error;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ep_create_wakeup_source(काष्ठा epitem *epi)
अणु
	काष्ठा name_snapshot n;
	काष्ठा wakeup_source *ws;

	अगर (!epi->ep->ws) अणु
		epi->ep->ws = wakeup_source_रेजिस्टर(शून्य, "eventpoll");
		अगर (!epi->ep->ws)
			वापस -ENOMEM;
	पूर्ण

	take_dentry_name_snapshot(&n, epi->ffd.file->f_path.dentry);
	ws = wakeup_source_रेजिस्टर(शून्य, n.name.name);
	release_dentry_name_snapshot(&n);

	अगर (!ws)
		वापस -ENOMEM;
	rcu_assign_poपूर्णांकer(epi->ws, ws);

	वापस 0;
पूर्ण

/* rare code path, only used when EPOLL_CTL_MOD हटाओs a wakeup source */
अटल noअंतरभूत व्योम ep_destroy_wakeup_source(काष्ठा epitem *epi)
अणु
	काष्ठा wakeup_source *ws = ep_wakeup_source(epi);

	RCU_INIT_POINTER(epi->ws, शून्य);

	/*
	 * रुको क्रम ep_pm_stay_awake_rcu to finish, synchronize_rcu is
	 * used पूर्णांकernally by wakeup_source_हटाओ, too (called by
	 * wakeup_source_unरेजिस्टर), so we cannot use call_rcu
	 */
	synchronize_rcu();
	wakeup_source_unरेजिस्टर(ws);
पूर्ण

अटल पूर्णांक attach_epitem(काष्ठा file *file, काष्ठा epitem *epi)
अणु
	काष्ठा epitems_head *to_मुक्त = शून्य;
	काष्ठा hlist_head *head = शून्य;
	काष्ठा eventpoll *ep = शून्य;

	अगर (is_file_epoll(file))
		ep = file->निजी_data;

	अगर (ep) अणु
		head = &ep->refs;
	पूर्ण अन्यथा अगर (!READ_ONCE(file->f_ep)) अणु
allocate:
		to_मुक्त = kmem_cache_zalloc(ephead_cache, GFP_KERNEL);
		अगर (!to_मुक्त)
			वापस -ENOMEM;
		head = &to_मुक्त->epitems;
	पूर्ण
	spin_lock(&file->f_lock);
	अगर (!file->f_ep) अणु
		अगर (unlikely(!head)) अणु
			spin_unlock(&file->f_lock);
			जाओ allocate;
		पूर्ण
		file->f_ep = head;
		to_मुक्त = शून्य;
	पूर्ण
	hlist_add_head_rcu(&epi->fllink, file->f_ep);
	spin_unlock(&file->f_lock);
	मुक्त_ephead(to_मुक्त);
	वापस 0;
पूर्ण

/*
 * Must be called with "mtx" held.
 */
अटल पूर्णांक ep_insert(काष्ठा eventpoll *ep, स्थिर काष्ठा epoll_event *event,
		     काष्ठा file *tfile, पूर्णांक fd, पूर्णांक full_check)
अणु
	पूर्णांक error, pwake = 0;
	__poll_t revents;
	दीर्घ user_watches;
	काष्ठा epitem *epi;
	काष्ठा ep_pqueue epq;
	काष्ठा eventpoll *tep = शून्य;

	अगर (is_file_epoll(tfile))
		tep = tfile->निजी_data;

	lockdep_निश्चित_irqs_enabled();

	user_watches = atomic_दीर्घ_पढ़ो(&ep->user->epoll_watches);
	अगर (unlikely(user_watches >= max_user_watches))
		वापस -ENOSPC;
	अगर (!(epi = kmem_cache_zalloc(epi_cache, GFP_KERNEL)))
		वापस -ENOMEM;

	/* Item initialization follow here ... */
	INIT_LIST_HEAD(&epi->rdllink);
	epi->ep = ep;
	ep_set_ffd(&epi->ffd, tfile, fd);
	epi->event = *event;
	epi->next = EP_UNACTIVE_PTR;

	अगर (tep)
		mutex_lock_nested(&tep->mtx, 1);
	/* Add the current item to the list of active epoll hook क्रम this file */
	अगर (unlikely(attach_epitem(tfile, epi) < 0)) अणु
		kmem_cache_मुक्त(epi_cache, epi);
		अगर (tep)
			mutex_unlock(&tep->mtx);
		वापस -ENOMEM;
	पूर्ण

	अगर (full_check && !tep)
		list_file(tfile);

	atomic_दीर्घ_inc(&ep->user->epoll_watches);

	/*
	 * Add the current item to the RB tree. All RB tree operations are
	 * रक्षित by "mtx", and ep_insert() is called with "mtx" held.
	 */
	ep_rbtree_insert(ep, epi);
	अगर (tep)
		mutex_unlock(&tep->mtx);

	/* now check अगर we've created too many backpaths */
	अगर (unlikely(full_check && reverse_path_check())) अणु
		ep_हटाओ(ep, epi);
		वापस -EINVAL;
	पूर्ण

	अगर (epi->event.events & EPOLLWAKEUP) अणु
		error = ep_create_wakeup_source(epi);
		अगर (error) अणु
			ep_हटाओ(ep, epi);
			वापस error;
		पूर्ण
	पूर्ण

	/* Initialize the poll table using the queue callback */
	epq.epi = epi;
	init_poll_funcptr(&epq.pt, ep_ptable_queue_proc);

	/*
	 * Attach the item to the poll hooks and get current event bits.
	 * We can safely use the file* here because its usage count has
	 * been increased by the caller of this function. Note that after
	 * this operation completes, the poll callback can start hitting
	 * the new item.
	 */
	revents = ep_item_poll(epi, &epq.pt, 1);

	/*
	 * We have to check अगर something went wrong during the poll रुको queue
	 * install process. Namely an allocation क्रम a रुको queue failed due
	 * high memory pressure.
	 */
	अगर (unlikely(!epq.epi)) अणु
		ep_हटाओ(ep, epi);
		वापस -ENOMEM;
	पूर्ण

	/* We have to drop the new item inside our item list to keep track of it */
	ग_लिखो_lock_irq(&ep->lock);

	/* record NAPI ID of new item अगर present */
	ep_set_busy_poll_napi_id(epi);

	/* If the file is alपढ़ोy "ready" we drop it inside the पढ़ोy list */
	अगर (revents && !ep_is_linked(epi)) अणु
		list_add_tail(&epi->rdllink, &ep->rdllist);
		ep_pm_stay_awake(epi);

		/* Notअगरy रुकोing tasks that events are available */
		अगर (रुकोqueue_active(&ep->wq))
			wake_up(&ep->wq);
		अगर (रुकोqueue_active(&ep->poll_रुको))
			pwake++;
	पूर्ण

	ग_लिखो_unlock_irq(&ep->lock);

	/* We have to call this outside the lock */
	अगर (pwake)
		ep_poll_safewake(ep, शून्य);

	वापस 0;
पूर्ण

/*
 * Modअगरy the पूर्णांकerest event mask by dropping an event अगर the new mask
 * has a match in the current file status. Must be called with "mtx" held.
 */
अटल पूर्णांक ep_modअगरy(काष्ठा eventpoll *ep, काष्ठा epitem *epi,
		     स्थिर काष्ठा epoll_event *event)
अणु
	पूर्णांक pwake = 0;
	poll_table pt;

	lockdep_निश्चित_irqs_enabled();

	init_poll_funcptr(&pt, शून्य);

	/*
	 * Set the new event पूर्णांकerest mask beक्रमe calling f_op->poll();
	 * otherwise we might miss an event that happens between the
	 * f_op->poll() call and the new event set रेजिस्टरing.
	 */
	epi->event.events = event->events; /* need barrier below */
	epi->event.data = event->data; /* रक्षित by mtx */
	अगर (epi->event.events & EPOLLWAKEUP) अणु
		अगर (!ep_has_wakeup_source(epi))
			ep_create_wakeup_source(epi);
	पूर्ण अन्यथा अगर (ep_has_wakeup_source(epi)) अणु
		ep_destroy_wakeup_source(epi);
	पूर्ण

	/*
	 * The following barrier has two effects:
	 *
	 * 1) Flush epi changes above to other CPUs.  This ensures
	 *    we करो not miss events from ep_poll_callback अगर an
	 *    event occurs immediately after we call f_op->poll().
	 *    We need this because we did not take ep->lock जबतक
	 *    changing epi above (but ep_poll_callback करोes take
	 *    ep->lock).
	 *
	 * 2) We also need to ensure we करो not miss _past_ events
	 *    when calling f_op->poll().  This barrier also
	 *    pairs with the barrier in wq_has_sleeper (see
	 *    comments क्रम wq_has_sleeper).
	 *
	 * This barrier will now guarantee ep_poll_callback or f_op->poll
	 * (or both) will notice the पढ़ोiness of an item.
	 */
	smp_mb();

	/*
	 * Get current event bits. We can safely use the file* here because
	 * its usage count has been increased by the caller of this function.
	 * If the item is "hot" and it is not रेजिस्टरed inside the पढ़ोy
	 * list, push it inside.
	 */
	अगर (ep_item_poll(epi, &pt, 1)) अणु
		ग_लिखो_lock_irq(&ep->lock);
		अगर (!ep_is_linked(epi)) अणु
			list_add_tail(&epi->rdllink, &ep->rdllist);
			ep_pm_stay_awake(epi);

			/* Notअगरy रुकोing tasks that events are available */
			अगर (रुकोqueue_active(&ep->wq))
				wake_up(&ep->wq);
			अगर (रुकोqueue_active(&ep->poll_रुको))
				pwake++;
		पूर्ण
		ग_लिखो_unlock_irq(&ep->lock);
	पूर्ण

	/* We have to call this outside the lock */
	अगर (pwake)
		ep_poll_safewake(ep, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक ep_send_events(काष्ठा eventpoll *ep,
			  काष्ठा epoll_event __user *events, पूर्णांक maxevents)
अणु
	काष्ठा epitem *epi, *पंचांगp;
	LIST_HEAD(txlist);
	poll_table pt;
	पूर्णांक res = 0;

	/*
	 * Always लघु-circuit क्रम fatal संकेतs to allow thपढ़ोs to make a
	 * समयly निकास without the chance of finding more events available and
	 * fetching repeatedly.
	 */
	अगर (fatal_संकेत_pending(current))
		वापस -EINTR;

	init_poll_funcptr(&pt, शून्य);

	mutex_lock(&ep->mtx);
	ep_start_scan(ep, &txlist);

	/*
	 * We can loop without lock because we are passed a task निजी list.
	 * Items cannot vanish during the loop we are holding ep->mtx.
	 */
	list_क्रम_each_entry_safe(epi, पंचांगp, &txlist, rdllink) अणु
		काष्ठा wakeup_source *ws;
		__poll_t revents;

		अगर (res >= maxevents)
			अवरोध;

		/*
		 * Activate ep->ws beक्रमe deactivating epi->ws to prevent
		 * triggering स्वतः-suspend here (in हाल we reactive epi->ws
		 * below).
		 *
		 * This could be rearranged to delay the deactivation of epi->ws
		 * instead, but then epi->ws would temporarily be out of sync
		 * with ep_is_linked().
		 */
		ws = ep_wakeup_source(epi);
		अगर (ws) अणु
			अगर (ws->active)
				__pm_stay_awake(ep->ws);
			__pm_relax(ws);
		पूर्ण

		list_del_init(&epi->rdllink);

		/*
		 * If the event mask पूर्णांकersect the caller-requested one,
		 * deliver the event to userspace. Again, we are holding ep->mtx,
		 * so no operations coming from userspace can change the item.
		 */
		revents = ep_item_poll(epi, &pt, 1);
		अगर (!revents)
			जारी;

		अगर (__put_user(revents, &events->events) ||
		    __put_user(epi->event.data, &events->data)) अणु
			list_add(&epi->rdllink, &txlist);
			ep_pm_stay_awake(epi);
			अगर (!res)
				res = -EFAULT;
			अवरोध;
		पूर्ण
		res++;
		events++;
		अगर (epi->event.events & EPOLLONESHOT)
			epi->event.events &= EP_PRIVATE_BITS;
		अन्यथा अगर (!(epi->event.events & EPOLLET)) अणु
			/*
			 * If this file has been added with Level
			 * Trigger mode, we need to insert back inside
			 * the पढ़ोy list, so that the next call to
			 * epoll_रुको() will check again the events
			 * availability. At this poपूर्णांक, no one can insert
			 * पूर्णांकo ep->rdllist besides us. The epoll_ctl()
			 * callers are locked out by
			 * ep_scan_पढ़ोy_list() holding "mtx" and the
			 * poll callback will queue them in ep->ovflist.
			 */
			list_add_tail(&epi->rdllink, &ep->rdllist);
			ep_pm_stay_awake(epi);
		पूर्ण
	पूर्ण
	ep_करोne_scan(ep, &txlist);
	mutex_unlock(&ep->mtx);

	वापस res;
पूर्ण

अटल काष्ठा बारpec64 *ep_समयout_to_बारpec(काष्ठा बारpec64 *to, दीर्घ ms)
अणु
	काष्ठा बारpec64 now;

	अगर (ms < 0)
		वापस शून्य;

	अगर (!ms) अणु
		to->tv_sec = 0;
		to->tv_nsec = 0;
		वापस to;
	पूर्ण

	to->tv_sec = ms / MSEC_PER_SEC;
	to->tv_nsec = NSEC_PER_MSEC * (ms % MSEC_PER_SEC);

	kसमय_get_ts64(&now);
	*to = बारpec64_add_safe(now, *to);
	वापस to;
पूर्ण

/**
 * ep_poll - Retrieves पढ़ोy events, and delivers them to the caller-supplied
 *           event buffer.
 *
 * @ep: Poपूर्णांकer to the eventpoll context.
 * @events: Poपूर्णांकer to the userspace buffer where the पढ़ोy events should be
 *          stored.
 * @maxevents: Size (in terms of number of events) of the caller event buffer.
 * @समयout: Maximum समयout क्रम the पढ़ोy events fetch operation, in
 *           बारpec. If the समयout is zero, the function will not block,
 *           जबतक अगर the @समयout ptr is शून्य, the function will block
 *           until at least one event has been retrieved (or an error
 *           occurred).
 *
 * Return: the number of पढ़ोy events which have been fetched, or an
 *          error code, in हाल of error.
 */
अटल पूर्णांक ep_poll(काष्ठा eventpoll *ep, काष्ठा epoll_event __user *events,
		   पूर्णांक maxevents, काष्ठा बारpec64 *समयout)
अणु
	पूर्णांक res, eavail, समयd_out = 0;
	u64 slack = 0;
	रुको_queue_entry_t रुको;
	kसमय_प्रकार expires, *to = शून्य;

	lockdep_निश्चित_irqs_enabled();

	अगर (समयout && (समयout->tv_sec | समयout->tv_nsec)) अणु
		slack = select_estimate_accuracy(समयout);
		to = &expires;
		*to = बारpec64_to_kसमय(*समयout);
	पूर्ण अन्यथा अगर (समयout) अणु
		/*
		 * Aव्योम the unnecessary trip to the रुको queue loop, अगर the
		 * caller specअगरied a non blocking operation.
		 */
		समयd_out = 1;
	पूर्ण

	/*
	 * This call is racy: We may or may not see events that are being added
	 * to the पढ़ोy list under the lock (e.g., in IRQ callbacks). For हालs
	 * with a non-zero समयout, this thपढ़ो will check the पढ़ोy list under
	 * lock and will add to the रुको queue.  For हालs with a zero
	 * समयout, the user by definition should not care and will have to
	 * recheck again.
	 */
	eavail = ep_events_available(ep);

	जबतक (1) अणु
		अगर (eavail) अणु
			/*
			 * Try to transfer events to user space. In हाल we get
			 * 0 events and there's still समयout left over, we go
			 * trying again in search of more luck.
			 */
			res = ep_send_events(ep, events, maxevents);
			अगर (res)
				वापस res;
		पूर्ण

		अगर (समयd_out)
			वापस 0;

		eavail = ep_busy_loop(ep, समयd_out);
		अगर (eavail)
			जारी;

		अगर (संकेत_pending(current))
			वापस -EINTR;

		/*
		 * Internally init_रुको() uses स्वतःहटाओ_wake_function(),
		 * thus रुको entry is हटाओd from the रुको queue on each
		 * wakeup. Why it is important? In हाल of several रुकोers
		 * each new wakeup will hit the next रुकोer, giving it the
		 * chance to harvest new event. Otherwise wakeup can be
		 * lost. This is also good perक्रमmance-wise, because on
		 * normal wakeup path no need to call __हटाओ_रुको_queue()
		 * explicitly, thus ep->lock is not taken, which halts the
		 * event delivery.
		 */
		init_रुको(&रुको);

		ग_लिखो_lock_irq(&ep->lock);
		/*
		 * Barrierless variant, रुकोqueue_active() is called under
		 * the same lock on wakeup ep_poll_callback() side, so it
		 * is safe to aव्योम an explicit barrier.
		 */
		__set_current_state(TASK_INTERRUPTIBLE);

		/*
		 * Do the final check under the lock. ep_scan_पढ़ोy_list()
		 * plays with two lists (->rdllist and ->ovflist) and there
		 * is always a race when both lists are empty क्रम लघु
		 * period of समय although events are pending, so lock is
		 * important.
		 */
		eavail = ep_events_available(ep);
		अगर (!eavail)
			__add_रुको_queue_exclusive(&ep->wq, &रुको);

		ग_लिखो_unlock_irq(&ep->lock);

		अगर (!eavail)
			समयd_out = !schedule_hrसमयout_range(to, slack,
							      HRTIMER_MODE_ABS);
		__set_current_state(TASK_RUNNING);

		/*
		 * We were woken up, thus go and try to harvest some events.
		 * If समयd out and still on the रुको queue, recheck eavail
		 * carefully under lock, below.
		 */
		eavail = 1;

		अगर (!list_empty_careful(&रुको.entry)) अणु
			ग_लिखो_lock_irq(&ep->lock);
			/*
			 * If the thपढ़ो समयd out and is not on the रुको queue,
			 * it means that the thपढ़ो was woken up after its
			 * समयout expired beक्रमe it could reacquire the lock.
			 * Thus, when रुको.entry is empty, it needs to harvest
			 * events.
			 */
			अगर (समयd_out)
				eavail = list_empty(&रुको.entry);
			__हटाओ_रुको_queue(&ep->wq, &रुको);
			ग_लिखो_unlock_irq(&ep->lock);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ep_loop_check_proc - verअगरy that adding an epoll file inside another
 *                      epoll काष्ठाure करोes not violate the स्थिरraपूर्णांकs, in
 *                      terms of बंदd loops, or too deep chains (which can
 *                      result in excessive stack usage).
 *
 * @ep: the &काष्ठा eventpoll to be currently checked.
 * @depth: Current depth of the path being checked.
 *
 * Return: %zero अगर adding the epoll @file inside current epoll
 *          काष्ठाure @ep करोes not violate the स्थिरraपूर्णांकs, or %-1 otherwise.
 */
अटल पूर्णांक ep_loop_check_proc(काष्ठा eventpoll *ep, पूर्णांक depth)
अणु
	पूर्णांक error = 0;
	काष्ठा rb_node *rbp;
	काष्ठा epitem *epi;

	mutex_lock_nested(&ep->mtx, depth + 1);
	ep->gen = loop_check_gen;
	क्रम (rbp = rb_first_cached(&ep->rbr); rbp; rbp = rb_next(rbp)) अणु
		epi = rb_entry(rbp, काष्ठा epitem, rbn);
		अगर (unlikely(is_file_epoll(epi->ffd.file))) अणु
			काष्ठा eventpoll *ep_tovisit;
			ep_tovisit = epi->ffd.file->निजी_data;
			अगर (ep_tovisit->gen == loop_check_gen)
				जारी;
			अगर (ep_tovisit == inserting_पूर्णांकo || depth > EP_MAX_NESTS)
				error = -1;
			अन्यथा
				error = ep_loop_check_proc(ep_tovisit, depth + 1);
			अगर (error != 0)
				अवरोध;
		पूर्ण अन्यथा अणु
			/*
			 * If we've reached a file that is not associated with
			 * an ep, then we need to check अगर the newly added
			 * links are going to add too many wakeup paths. We करो
			 * this by adding it to the tfile_check_list, अगर it's
			 * not alपढ़ोy there, and calling reverse_path_check()
			 * during ep_insert().
			 */
			list_file(epi->ffd.file);
		पूर्ण
	पूर्ण
	mutex_unlock(&ep->mtx);

	वापस error;
पूर्ण

/**
 * ep_loop_check - Perक्रमms a check to verअगरy that adding an epoll file (@to)
 *                 पूर्णांकo another epoll file (represented by @ep) करोes not create
 *                 बंदd loops or too deep chains.
 *
 * @ep: Poपूर्णांकer to the epoll we are inserting पूर्णांकo.
 * @to: Poपूर्णांकer to the epoll to be inserted.
 *
 * Return: %zero अगर adding the epoll @to inside the epoll @from
 * करोes not violate the स्थिरraपूर्णांकs, or %-1 otherwise.
 */
अटल पूर्णांक ep_loop_check(काष्ठा eventpoll *ep, काष्ठा eventpoll *to)
अणु
	inserting_पूर्णांकo = ep;
	वापस ep_loop_check_proc(to, 0);
पूर्ण

अटल व्योम clear_tfile_check_list(व्योम)
अणु
	rcu_पढ़ो_lock();
	जबतक (tfile_check_list != EP_UNACTIVE_PTR) अणु
		काष्ठा epitems_head *head = tfile_check_list;
		tfile_check_list = head->next;
		unlist_file(head);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * Open an eventpoll file descriptor.
 */
अटल पूर्णांक करो_epoll_create(पूर्णांक flags)
अणु
	पूर्णांक error, fd;
	काष्ठा eventpoll *ep = शून्य;
	काष्ठा file *file;

	/* Check the EPOLL_* स्थिरant क्रम consistency.  */
	BUILD_BUG_ON(EPOLL_CLOEXEC != O_CLOEXEC);

	अगर (flags & ~EPOLL_CLOEXEC)
		वापस -EINVAL;
	/*
	 * Create the पूर्णांकernal data काष्ठाure ("struct eventpoll").
	 */
	error = ep_alloc(&ep);
	अगर (error < 0)
		वापस error;
	/*
	 * Creates all the items needed to setup an eventpoll file. That is,
	 * a file काष्ठाure and a मुक्त file descriptor.
	 */
	fd = get_unused_fd_flags(O_RDWR | (flags & O_CLOEXEC));
	अगर (fd < 0) अणु
		error = fd;
		जाओ out_मुक्त_ep;
	पूर्ण
	file = anon_inode_getfile("[eventpoll]", &eventpoll_fops, ep,
				 O_RDWR | (flags & O_CLOEXEC));
	अगर (IS_ERR(file)) अणु
		error = PTR_ERR(file);
		जाओ out_मुक्त_fd;
	पूर्ण
	ep->file = file;
	fd_install(fd, file);
	वापस fd;

out_मुक्त_fd:
	put_unused_fd(fd);
out_मुक्त_ep:
	ep_मुक्त(ep);
	वापस error;
पूर्ण

SYSCALL_DEFINE1(epoll_create1, पूर्णांक, flags)
अणु
	वापस करो_epoll_create(flags);
पूर्ण

SYSCALL_DEFINE1(epoll_create, पूर्णांक, size)
अणु
	अगर (size <= 0)
		वापस -EINVAL;

	वापस करो_epoll_create(0);
पूर्ण

अटल अंतरभूत पूर्णांक epoll_mutex_lock(काष्ठा mutex *mutex, पूर्णांक depth,
				   bool nonblock)
अणु
	अगर (!nonblock) अणु
		mutex_lock_nested(mutex, depth);
		वापस 0;
	पूर्ण
	अगर (mutex_trylock(mutex))
		वापस 0;
	वापस -EAGAIN;
पूर्ण

पूर्णांक करो_epoll_ctl(पूर्णांक epfd, पूर्णांक op, पूर्णांक fd, काष्ठा epoll_event *epds,
		 bool nonblock)
अणु
	पूर्णांक error;
	पूर्णांक full_check = 0;
	काष्ठा fd f, tf;
	काष्ठा eventpoll *ep;
	काष्ठा epitem *epi;
	काष्ठा eventpoll *tep = शून्य;

	error = -EBADF;
	f = fdget(epfd);
	अगर (!f.file)
		जाओ error_वापस;

	/* Get the "struct file *" क्रम the target file */
	tf = fdget(fd);
	अगर (!tf.file)
		जाओ error_fput;

	/* The target file descriptor must support poll */
	error = -EPERM;
	अगर (!file_can_poll(tf.file))
		जाओ error_tgt_fput;

	/* Check अगर EPOLLWAKEUP is allowed */
	अगर (ep_op_has_event(op))
		ep_take_care_of_epollwakeup(epds);

	/*
	 * We have to check that the file काष्ठाure underneath the file descriptor
	 * the user passed to us _is_ an eventpoll file. And also we करो not permit
	 * adding an epoll file descriptor inside itself.
	 */
	error = -EINVAL;
	अगर (f.file == tf.file || !is_file_epoll(f.file))
		जाओ error_tgt_fput;

	/*
	 * epoll adds to the wakeup queue at EPOLL_CTL_ADD समय only,
	 * so EPOLLEXCLUSIVE is not allowed क्रम a EPOLL_CTL_MOD operation.
	 * Also, we करो not currently supported nested exclusive wakeups.
	 */
	अगर (ep_op_has_event(op) && (epds->events & EPOLLEXCLUSIVE)) अणु
		अगर (op == EPOLL_CTL_MOD)
			जाओ error_tgt_fput;
		अगर (op == EPOLL_CTL_ADD && (is_file_epoll(tf.file) ||
				(epds->events & ~EPOLLEXCLUSIVE_OK_BITS)))
			जाओ error_tgt_fput;
	पूर्ण

	/*
	 * At this poपूर्णांक it is safe to assume that the "private_data" contains
	 * our own data काष्ठाure.
	 */
	ep = f.file->निजी_data;

	/*
	 * When we insert an epoll file descriptor inside another epoll file
	 * descriptor, there is the chance of creating बंदd loops, which are
	 * better be handled here, than in more critical paths. While we are
	 * checking क्रम loops we also determine the list of files reachable
	 * and hang them on the tfile_check_list, so we can check that we
	 * haven't created too many possible wakeup paths.
	 *
	 * We करो not need to take the global 'epumutex' on EPOLL_CTL_ADD when
	 * the epoll file descriptor is attaching directly to a wakeup source,
	 * unless the epoll file descriptor is nested. The purpose of taking the
	 * 'epmutex' on add is to prevent complex toplogies such as loops and
	 * deep wakeup paths from क्रमming in parallel through multiple
	 * EPOLL_CTL_ADD operations.
	 */
	error = epoll_mutex_lock(&ep->mtx, 0, nonblock);
	अगर (error)
		जाओ error_tgt_fput;
	अगर (op == EPOLL_CTL_ADD) अणु
		अगर (READ_ONCE(f.file->f_ep) || ep->gen == loop_check_gen ||
		    is_file_epoll(tf.file)) अणु
			mutex_unlock(&ep->mtx);
			error = epoll_mutex_lock(&epmutex, 0, nonblock);
			अगर (error)
				जाओ error_tgt_fput;
			loop_check_gen++;
			full_check = 1;
			अगर (is_file_epoll(tf.file)) अणु
				tep = tf.file->निजी_data;
				error = -ELOOP;
				अगर (ep_loop_check(ep, tep) != 0)
					जाओ error_tgt_fput;
			पूर्ण
			error = epoll_mutex_lock(&ep->mtx, 0, nonblock);
			अगर (error)
				जाओ error_tgt_fput;
		पूर्ण
	पूर्ण

	/*
	 * Try to lookup the file inside our RB tree. Since we grabbed "mtx"
	 * above, we can be sure to be able to use the item looked up by
	 * ep_find() till we release the mutex.
	 */
	epi = ep_find(ep, tf.file, fd);

	error = -EINVAL;
	चयन (op) अणु
	हाल EPOLL_CTL_ADD:
		अगर (!epi) अणु
			epds->events |= EPOLLERR | EPOLLHUP;
			error = ep_insert(ep, epds, tf.file, fd, full_check);
		पूर्ण अन्यथा
			error = -EEXIST;
		अवरोध;
	हाल EPOLL_CTL_DEL:
		अगर (epi)
			error = ep_हटाओ(ep, epi);
		अन्यथा
			error = -ENOENT;
		अवरोध;
	हाल EPOLL_CTL_MOD:
		अगर (epi) अणु
			अगर (!(epi->event.events & EPOLLEXCLUSIVE)) अणु
				epds->events |= EPOLLERR | EPOLLHUP;
				error = ep_modअगरy(ep, epi, epds);
			पूर्ण
		पूर्ण अन्यथा
			error = -ENOENT;
		अवरोध;
	पूर्ण
	mutex_unlock(&ep->mtx);

error_tgt_fput:
	अगर (full_check) अणु
		clear_tfile_check_list();
		loop_check_gen++;
		mutex_unlock(&epmutex);
	पूर्ण

	fdput(tf);
error_fput:
	fdput(f);
error_वापस:

	वापस error;
पूर्ण

/*
 * The following function implements the controller पूर्णांकerface क्रम
 * the eventpoll file that enables the insertion/removal/change of
 * file descriptors inside the पूर्णांकerest set.
 */
SYSCALL_DEFINE4(epoll_ctl, पूर्णांक, epfd, पूर्णांक, op, पूर्णांक, fd,
		काष्ठा epoll_event __user *, event)
अणु
	काष्ठा epoll_event epds;

	अगर (ep_op_has_event(op) &&
	    copy_from_user(&epds, event, माप(काष्ठा epoll_event)))
		वापस -EFAULT;

	वापस करो_epoll_ctl(epfd, op, fd, &epds, false);
पूर्ण

/*
 * Implement the event रुको पूर्णांकerface क्रम the eventpoll file. It is the kernel
 * part of the user space epoll_रुको(2).
 */
अटल पूर्णांक करो_epoll_रुको(पूर्णांक epfd, काष्ठा epoll_event __user *events,
			 पूर्णांक maxevents, काष्ठा बारpec64 *to)
अणु
	पूर्णांक error;
	काष्ठा fd f;
	काष्ठा eventpoll *ep;

	/* The maximum number of event must be greater than zero */
	अगर (maxevents <= 0 || maxevents > EP_MAX_EVENTS)
		वापस -EINVAL;

	/* Verअगरy that the area passed by the user is ग_लिखोable */
	अगर (!access_ok(events, maxevents * माप(काष्ठा epoll_event)))
		वापस -EFAULT;

	/* Get the "struct file *" क्रम the eventpoll file */
	f = fdget(epfd);
	अगर (!f.file)
		वापस -EBADF;

	/*
	 * We have to check that the file काष्ठाure underneath the fd
	 * the user passed to us _is_ an eventpoll file.
	 */
	error = -EINVAL;
	अगर (!is_file_epoll(f.file))
		जाओ error_fput;

	/*
	 * At this poपूर्णांक it is safe to assume that the "private_data" contains
	 * our own data काष्ठाure.
	 */
	ep = f.file->निजी_data;

	/* Time to fish क्रम events ... */
	error = ep_poll(ep, events, maxevents, to);

error_fput:
	fdput(f);
	वापस error;
पूर्ण

SYSCALL_DEFINE4(epoll_रुको, पूर्णांक, epfd, काष्ठा epoll_event __user *, events,
		पूर्णांक, maxevents, पूर्णांक, समयout)
अणु
	काष्ठा बारpec64 to;

	वापस करो_epoll_रुको(epfd, events, maxevents,
			     ep_समयout_to_बारpec(&to, समयout));
पूर्ण

/*
 * Implement the event रुको पूर्णांकerface क्रम the eventpoll file. It is the kernel
 * part of the user space epoll_pरुको(2).
 */
अटल पूर्णांक करो_epoll_pरुको(पूर्णांक epfd, काष्ठा epoll_event __user *events,
			  पूर्णांक maxevents, काष्ठा बारpec64 *to,
			  स्थिर sigset_t __user *sigmask, माप_प्रकार sigsetsize)
अणु
	पूर्णांक error;

	/*
	 * If the caller wants a certain संकेत mask to be set during the रुको,
	 * we apply it here.
	 */
	error = set_user_sigmask(sigmask, sigsetsize);
	अगर (error)
		वापस error;

	error = करो_epoll_रुको(epfd, events, maxevents, to);

	restore_saved_sigmask_unless(error == -EINTR);

	वापस error;
पूर्ण

SYSCALL_DEFINE6(epoll_pरुको, पूर्णांक, epfd, काष्ठा epoll_event __user *, events,
		पूर्णांक, maxevents, पूर्णांक, समयout, स्थिर sigset_t __user *, sigmask,
		माप_प्रकार, sigsetsize)
अणु
	काष्ठा बारpec64 to;

	वापस करो_epoll_pरुको(epfd, events, maxevents,
			      ep_समयout_to_बारpec(&to, समयout),
			      sigmask, sigsetsize);
पूर्ण

SYSCALL_DEFINE6(epoll_pरुको2, पूर्णांक, epfd, काष्ठा epoll_event __user *, events,
		पूर्णांक, maxevents, स्थिर काष्ठा __kernel_बारpec __user *, समयout,
		स्थिर sigset_t __user *, sigmask, माप_प्रकार, sigsetsize)
अणु
	काष्ठा बारpec64 ts, *to = शून्य;

	अगर (समयout) अणु
		अगर (get_बारpec64(&ts, समयout))
			वापस -EFAULT;
		to = &ts;
		अगर (poll_select_set_समयout(to, ts.tv_sec, ts.tv_nsec))
			वापस -EINVAL;
	पूर्ण

	वापस करो_epoll_pरुको(epfd, events, maxevents, to,
			      sigmask, sigsetsize);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक करो_compat_epoll_pरुको(पूर्णांक epfd, काष्ठा epoll_event __user *events,
				 पूर्णांक maxevents, काष्ठा बारpec64 *समयout,
				 स्थिर compat_sigset_t __user *sigmask,
				 compat_माप_प्रकार sigsetsize)
अणु
	दीर्घ err;

	/*
	 * If the caller wants a certain संकेत mask to be set during the रुको,
	 * we apply it here.
	 */
	err = set_compat_user_sigmask(sigmask, sigsetsize);
	अगर (err)
		वापस err;

	err = करो_epoll_रुको(epfd, events, maxevents, समयout);

	restore_saved_sigmask_unless(err == -EINTR);

	वापस err;
पूर्ण

COMPAT_SYSCALL_DEFINE6(epoll_pरुको, पूर्णांक, epfd,
		       काष्ठा epoll_event __user *, events,
		       पूर्णांक, maxevents, पूर्णांक, समयout,
		       स्थिर compat_sigset_t __user *, sigmask,
		       compat_माप_प्रकार, sigsetsize)
अणु
	काष्ठा बारpec64 to;

	वापस करो_compat_epoll_pरुको(epfd, events, maxevents,
				     ep_समयout_to_बारpec(&to, समयout),
				     sigmask, sigsetsize);
पूर्ण

COMPAT_SYSCALL_DEFINE6(epoll_pरुको2, पूर्णांक, epfd,
		       काष्ठा epoll_event __user *, events,
		       पूर्णांक, maxevents,
		       स्थिर काष्ठा __kernel_बारpec __user *, समयout,
		       स्थिर compat_sigset_t __user *, sigmask,
		       compat_माप_प्रकार, sigsetsize)
अणु
	काष्ठा बारpec64 ts, *to = शून्य;

	अगर (समयout) अणु
		अगर (get_बारpec64(&ts, समयout))
			वापस -EFAULT;
		to = &ts;
		अगर (poll_select_set_समयout(to, ts.tv_sec, ts.tv_nsec))
			वापस -EINVAL;
	पूर्ण

	वापस करो_compat_epoll_pरुको(epfd, events, maxevents, to,
				     sigmask, sigsetsize);
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक __init eventpoll_init(व्योम)
अणु
	काष्ठा sysinfo si;

	si_meminfo(&si);
	/*
	 * Allows top 4% of lomem to be allocated क्रम epoll watches (per user).
	 */
	max_user_watches = (((si.totalram - si.totalhigh) / 25) << PAGE_SHIFT) /
		EP_ITEM_COST;
	BUG_ON(max_user_watches < 0);

	/*
	 * We can have many thousands of epitems, so prevent this from
	 * using an extra cache line on 64-bit (and smaller) CPUs
	 */
	BUILD_BUG_ON(माप(व्योम *) <= 8 && माप(काष्ठा epitem) > 128);

	/* Allocates slab cache used to allocate "struct epitem" items */
	epi_cache = kmem_cache_create("eventpoll_epi", माप(काष्ठा epitem),
			0, SLAB_HWCACHE_ALIGN|SLAB_PANIC|SLAB_ACCOUNT, शून्य);

	/* Allocates slab cache used to allocate "struct eppoll_entry" */
	pwq_cache = kmem_cache_create("eventpoll_pwq",
		माप(काष्ठा eppoll_entry), 0, SLAB_PANIC|SLAB_ACCOUNT, शून्य);

	ephead_cache = kmem_cache_create("ep_head",
		माप(काष्ठा epitems_head), 0, SLAB_PANIC|SLAB_ACCOUNT, शून्य);

	वापस 0;
पूर्ण
fs_initcall(eventpoll_init);
