<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_CLOSURE_H
#घोषणा _LINUX_CLOSURE_H

#समावेश <linux/llist.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/workqueue.h>

/*
 * Closure is perhaps the most overused and abused term in computer science, but
 * since I've been unable to come up with anything better you're stuck with it
 * again.
 *
 * What are closures?
 *
 * They embed a refcount. The basic idea is they count "things that are in
 * progress" - in flight bios, some other thपढ़ो that's करोing something अन्यथा -
 * anything you might want to रुको on.
 *
 * The refcount may be manipulated with closure_get() and closure_put().
 * closure_put() is where many of the पूर्णांकeresting things happen, when it causes
 * the refcount to go to 0.
 *
 * Closures can be used to रुको on things both synchronously and asynchronously,
 * and synchronous and asynchronous use can be mixed without restriction. To
 * रुको synchronously, use closure_sync() - you will sleep until your closure's
 * refcount hits 1.
 *
 * To रुको asynchronously, use
 *   जारी_at(cl, next_function, workqueue);
 *
 * passing it, as you might expect, the function to run when nothing is pending
 * and the workqueue to run that function out of.
 *
 * जारी_at() also, critically, requires a 'return' immediately following the
 * location where this macro is referenced, to वापस to the calling function.
 * There's good reason क्रम this.
 *
 * To use safely closures asynchronously, they must always have a refcount जबतक
 * they are running owned by the thपढ़ो that is running them. Otherwise, suppose
 * you submit some bios and wish to have a function run when they all complete:
 *
 * foo_endio(काष्ठा bio *bio)
 * अणु
 *	closure_put(cl);
 * पूर्ण
 *
 * closure_init(cl);
 *
 * करो_stuff();
 * closure_get(cl);
 * bio1->bi_endio = foo_endio;
 * bio_submit(bio1);
 *
 * करो_more_stuff();
 * closure_get(cl);
 * bio2->bi_endio = foo_endio;
 * bio_submit(bio2);
 *
 * जारी_at(cl, complete_some_पढ़ो, प्रणाली_wq);
 *
 * If closure's refcount started at 0, complete_some_पढ़ो() could run beक्रमe the
 * second bio was submitted - which is almost always not what you want! More
 * importantly, it wouldn't be possible to say whether the original thपढ़ो or
 * complete_some_पढ़ो()'s thपढ़ो owned the closure - and whatever state it was
 * associated with!
 *
 * So, closure_init() initializes a closure's refcount to 1 - and when a
 * closure_fn is run, the refcount will be reset to 1 first.
 *
 * Then, the rule is - अगर you got the refcount with closure_get(), release it
 * with closure_put() (i.e, in a bio->bi_endio function). If you have a refcount
 * on a closure because you called closure_init() or you were run out of a
 * closure - _always_ use जारी_at(). Doing so consistently will help
 * eliminate an entire class of particularly pernicious races.
 *
 * Lastly, you might have a रुको list dedicated to a specअगरic event, and have no
 * need क्रम specअगरying the condition - you just want to रुको until someone runs
 * closure_wake_up() on the appropriate रुको list. In that हाल, just use
 * closure_रुको(). It will वापस either true or false, depending on whether the
 * closure was alपढ़ोy on a रुको list or not - a closure can only be on one रुको
 * list at a समय.
 *
 * Parents:
 *
 * closure_init() takes two arguments - it takes the closure to initialize, and
 * a (possibly null) parent.
 *
 * If parent is non null, the new closure will have a refcount क्रम its lअगरeसमय;
 * a closure is considered to be "finished" when its refcount hits 0 and the
 * function to run is null. Hence
 *
 * जारी_at(cl, शून्य, शून्य);
 *
 * वापसs up the (spaghetti) stack of closures, precisely like normal वापस
 * वापसs up the C stack. जारी_at() with non null fn is better thought of
 * as करोing a tail call.
 *
 * All this implies that a closure should typically be embedded in a particular
 * काष्ठा (which its refcount will normally control the lअगरeसमय of), and that
 * काष्ठा can very much be thought of as a stack frame.
 */

काष्ठा closure;
काष्ठा closure_syncer;
प्रकार व्योम (closure_fn) (काष्ठा closure *);
बाह्य काष्ठा dentry *bcache_debug;

काष्ठा closure_रुकोlist अणु
	काष्ठा llist_head	list;
पूर्ण;

क्रमागत closure_state अणु
	/*
	 * CLOSURE_WAITING: Set अगरf the closure is on a रुकोlist. Must be set by
	 * the thपढ़ो that owns the closure, and cleared by the thपढ़ो that's
	 * waking up the closure.
	 *
	 * The rest are क्रम debugging and करोn't affect behaviour:
	 *
	 * CLOSURE_RUNNING: Set when a closure is running (i.e. by
	 * closure_init() and when closure_put() runs then next function), and
	 * must be cleared beक्रमe reमुख्यing hits 0. Primarily to help guard
	 * against incorrect usage and accidentally transferring references.
	 * जारी_at() and closure_वापस() clear it क्रम you, अगर you're करोing
	 * something unusual you can use closure_set_dead() which also helps
	 * annotate where references are being transferred.
	 */

	CLOSURE_BITS_START	= (1U << 26),
	CLOSURE_DESTRUCTOR	= (1U << 26),
	CLOSURE_WAITING		= (1U << 28),
	CLOSURE_RUNNING		= (1U << 30),
पूर्ण;

#घोषणा CLOSURE_GUARD_MASK					\
	((CLOSURE_DESTRUCTOR|CLOSURE_WAITING|CLOSURE_RUNNING) << 1)

#घोषणा CLOSURE_REMAINING_MASK		(CLOSURE_BITS_START - 1)
#घोषणा CLOSURE_REMAINING_INITIALIZER	(1|CLOSURE_RUNNING)

काष्ठा closure अणु
	जोड़ अणु
		काष्ठा अणु
			काष्ठा workqueue_काष्ठा *wq;
			काष्ठा closure_syncer	*s;
			काष्ठा llist_node	list;
			closure_fn		*fn;
		पूर्ण;
		काष्ठा work_काष्ठा	work;
	पूर्ण;

	काष्ठा closure		*parent;

	atomic_t		reमुख्यing;

#अगर_घोषित CONFIG_BCACHE_CLOSURES_DEBUG
#घोषणा CLOSURE_MAGIC_DEAD	0xc054dead
#घोषणा CLOSURE_MAGIC_ALIVE	0xc054a11e

	अचिन्हित पूर्णांक		magic;
	काष्ठा list_head	all;
	अचिन्हित दीर्घ		ip;
	अचिन्हित दीर्घ		रुकोing_on;
#पूर्ण_अगर
पूर्ण;

व्योम closure_sub(काष्ठा closure *cl, पूर्णांक v);
व्योम closure_put(काष्ठा closure *cl);
व्योम __closure_wake_up(काष्ठा closure_रुकोlist *list);
bool closure_रुको(काष्ठा closure_रुकोlist *list, काष्ठा closure *cl);
व्योम __closure_sync(काष्ठा closure *cl);

/**
 * closure_sync - sleep until a closure a closure has nothing left to रुको on
 *
 * Sleeps until the refcount hits 1 - the thपढ़ो that's running the closure owns
 * the last refcount.
 */
अटल अंतरभूत व्योम closure_sync(काष्ठा closure *cl)
अणु
	अगर ((atomic_पढ़ो(&cl->reमुख्यing) & CLOSURE_REMAINING_MASK) != 1)
		__closure_sync(cl);
पूर्ण

#अगर_घोषित CONFIG_BCACHE_CLOSURES_DEBUG

व्योम closure_debug_init(व्योम);
व्योम closure_debug_create(काष्ठा closure *cl);
व्योम closure_debug_destroy(काष्ठा closure *cl);

#अन्यथा

अटल अंतरभूत व्योम closure_debug_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम closure_debug_create(काष्ठा closure *cl) अणुपूर्ण
अटल अंतरभूत व्योम closure_debug_destroy(काष्ठा closure *cl) अणुपूर्ण

#पूर्ण_अगर

अटल अंतरभूत व्योम closure_set_ip(काष्ठा closure *cl)
अणु
#अगर_घोषित CONFIG_BCACHE_CLOSURES_DEBUG
	cl->ip = _THIS_IP_;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम closure_set_ret_ip(काष्ठा closure *cl)
अणु
#अगर_घोषित CONFIG_BCACHE_CLOSURES_DEBUG
	cl->ip = _RET_IP_;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम closure_set_रुकोing(काष्ठा closure *cl, अचिन्हित दीर्घ f)
अणु
#अगर_घोषित CONFIG_BCACHE_CLOSURES_DEBUG
	cl->रुकोing_on = f;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम closure_set_stopped(काष्ठा closure *cl)
अणु
	atomic_sub(CLOSURE_RUNNING, &cl->reमुख्यing);
पूर्ण

अटल अंतरभूत व्योम set_closure_fn(काष्ठा closure *cl, closure_fn *fn,
				  काष्ठा workqueue_काष्ठा *wq)
अणु
	closure_set_ip(cl);
	cl->fn = fn;
	cl->wq = wq;
	/* between atomic_dec() in closure_put() */
	smp_mb__beक्रमe_atomic();
पूर्ण

अटल अंतरभूत व्योम closure_queue(काष्ठा closure *cl)
अणु
	काष्ठा workqueue_काष्ठा *wq = cl->wq;
	/**
	 * Changes made to closure, work_काष्ठा, or a couple of other काष्ठाs
	 * may cause work.func not poपूर्णांकing to the right location.
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा closure, fn)
		     != दुरत्व(काष्ठा work_काष्ठा, func));
	अगर (wq) अणु
		INIT_WORK(&cl->work, cl->work.func);
		BUG_ON(!queue_work(wq, &cl->work));
	पूर्ण अन्यथा
		cl->fn(cl);
पूर्ण

/**
 * closure_get - increment a closure's refcount
 */
अटल अंतरभूत व्योम closure_get(काष्ठा closure *cl)
अणु
#अगर_घोषित CONFIG_BCACHE_CLOSURES_DEBUG
	BUG_ON((atomic_inc_वापस(&cl->reमुख्यing) &
		CLOSURE_REMAINING_MASK) <= 1);
#अन्यथा
	atomic_inc(&cl->reमुख्यing);
#पूर्ण_अगर
पूर्ण

/**
 * closure_init - Initialize a closure, setting the refcount to 1
 * @cl:		closure to initialize
 * @parent:	parent of the new closure. cl will take a refcount on it क्रम its
 *		lअगरeसमय; may be शून्य.
 */
अटल अंतरभूत व्योम closure_init(काष्ठा closure *cl, काष्ठा closure *parent)
अणु
	स_रखो(cl, 0, माप(काष्ठा closure));
	cl->parent = parent;
	अगर (parent)
		closure_get(parent);

	atomic_set(&cl->reमुख्यing, CLOSURE_REMAINING_INITIALIZER);

	closure_debug_create(cl);
	closure_set_ip(cl);
पूर्ण

अटल अंतरभूत व्योम closure_init_stack(काष्ठा closure *cl)
अणु
	स_रखो(cl, 0, माप(काष्ठा closure));
	atomic_set(&cl->reमुख्यing, CLOSURE_REMAINING_INITIALIZER);
पूर्ण

/**
 * closure_wake_up - wake up all closures on a रुको list,
 *		     with memory barrier
 */
अटल अंतरभूत व्योम closure_wake_up(काष्ठा closure_रुकोlist *list)
अणु
	/* Memory barrier क्रम the रुको list */
	smp_mb();
	__closure_wake_up(list);
पूर्ण

/**
 * जारी_at - jump to another function with barrier
 *
 * After @cl is no दीर्घer रुकोing on anything (i.e. all outstanding refs have
 * been dropped with closure_put()), it will resume execution at @fn running out
 * of @wq (or, अगर @wq is शून्य, @fn will be called by closure_put() directly).
 *
 * This is because after calling जारी_at() you no दीर्घer have a ref on @cl,
 * and whatever @cl owns may be मुक्तd out from under you - a running closure fn
 * has a ref on its own closure which जारी_at() drops.
 *
 * Note you are expected to immediately वापस after using this macro.
 */
#घोषणा जारी_at(_cl, _fn, _wq)					\
करो अणु									\
	set_closure_fn(_cl, _fn, _wq);					\
	closure_sub(_cl, CLOSURE_RUNNING + 1);				\
पूर्ण जबतक (0)

/**
 * closure_वापस - finish execution of a closure
 *
 * This is used to indicate that @cl is finished: when all outstanding refs on
 * @cl have been dropped @cl's ref on its parent closure (as passed to
 * closure_init()) will be dropped, अगर one was specअगरied - thus this can be
 * thought of as वापसing to the parent closure.
 */
#घोषणा closure_वापस(_cl)	जारी_at((_cl), शून्य, शून्य)

/**
 * जारी_at_nobarrier - jump to another function without barrier
 *
 * Causes @fn to be executed out of @cl, in @wq context (or called directly अगर
 * @wq is शून्य).
 *
 * The ref the caller of जारी_at_nobarrier() had on @cl is now owned by @fn,
 * thus it's not safe to touch anything रक्षित by @cl after a
 * जारी_at_nobarrier().
 */
#घोषणा जारी_at_nobarrier(_cl, _fn, _wq)				\
करो अणु									\
	set_closure_fn(_cl, _fn, _wq);					\
	closure_queue(_cl);						\
पूर्ण जबतक (0)

/**
 * closure_वापस_with_deकाष्ठाor - finish execution of a closure,
 *				    with deकाष्ठाor
 *
 * Works like closure_वापस(), except @deकाष्ठाor will be called when all
 * outstanding refs on @cl have been dropped; @deकाष्ठाor may be used to safely
 * मुक्त the memory occupied by @cl, and it is called with the ref on the parent
 * closure still held - so @deकाष्ठाor could safely वापस an item to a
 * मुक्तlist रक्षित by @cl's parent.
 */
#घोषणा closure_वापस_with_deकाष्ठाor(_cl, _deकाष्ठाor)		\
करो अणु									\
	set_closure_fn(_cl, _deकाष्ठाor, शून्य);				\
	closure_sub(_cl, CLOSURE_RUNNING - CLOSURE_DESTRUCTOR + 1);	\
पूर्ण जबतक (0)

/**
 * closure_call - execute @fn out of a new, uninitialized closure
 *
 * Typically used when running out of one closure, and we want to run @fn
 * asynchronously out of a new closure - @parent will then रुको क्रम @cl to
 * finish.
 */
अटल अंतरभूत व्योम closure_call(काष्ठा closure *cl, closure_fn fn,
				काष्ठा workqueue_काष्ठा *wq,
				काष्ठा closure *parent)
अणु
	closure_init(cl, parent);
	जारी_at_nobarrier(cl, fn, wq);
पूर्ण

#पूर्ण_अगर /* _LINUX_CLOSURE_H */
