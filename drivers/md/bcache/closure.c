<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Asynchronous refcounty things
 *
 * Copyright 2010, 2011 Kent Overstreet <kent.overstreet@gmail.com>
 * Copyright 2012 Google, Inc.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/sched/debug.h>

#समावेश "closure.h"

अटल अंतरभूत व्योम closure_put_after_sub(काष्ठा closure *cl, पूर्णांक flags)
अणु
	पूर्णांक r = flags & CLOSURE_REMAINING_MASK;

	BUG_ON(flags & CLOSURE_GUARD_MASK);
	BUG_ON(!r && (flags & ~CLOSURE_DESTRUCTOR));

	अगर (!r) अणु
		अगर (cl->fn && !(flags & CLOSURE_DESTRUCTOR)) अणु
			atomic_set(&cl->reमुख्यing,
				   CLOSURE_REMAINING_INITIALIZER);
			closure_queue(cl);
		पूर्ण अन्यथा अणु
			काष्ठा closure *parent = cl->parent;
			closure_fn *deकाष्ठाor = cl->fn;

			closure_debug_destroy(cl);

			अगर (deकाष्ठाor)
				deकाष्ठाor(cl);

			अगर (parent)
				closure_put(parent);
		पूर्ण
	पूर्ण
पूर्ण

/* For clearing flags with the same atomic op as a put */
व्योम closure_sub(काष्ठा closure *cl, पूर्णांक v)
अणु
	closure_put_after_sub(cl, atomic_sub_वापस(v, &cl->reमुख्यing));
पूर्ण

/*
 * closure_put - decrement a closure's refcount
 */
व्योम closure_put(काष्ठा closure *cl)
अणु
	closure_put_after_sub(cl, atomic_dec_वापस(&cl->reमुख्यing));
पूर्ण

/*
 * closure_wake_up - wake up all closures on a रुको list, without memory barrier
 */
व्योम __closure_wake_up(काष्ठा closure_रुकोlist *रुको_list)
अणु
	काष्ठा llist_node *list;
	काष्ठा closure *cl, *t;
	काष्ठा llist_node *reverse = शून्य;

	list = llist_del_all(&रुको_list->list);

	/* We first reverse the list to preserve FIFO ordering and fairness */
	reverse = llist_reverse_order(list);

	/* Then करो the wakeups */
	llist_क्रम_each_entry_safe(cl, t, reverse, list) अणु
		closure_set_रुकोing(cl, 0);
		closure_sub(cl, CLOSURE_WAITING + 1);
	पूर्ण
पूर्ण

/**
 * closure_रुको - add a closure to a रुकोlist
 * @रुकोlist: will own a ref on @cl, which will be released when
 * closure_wake_up() is called on @रुकोlist.
 * @cl: closure poपूर्णांकer.
 *
 */
bool closure_रुको(काष्ठा closure_रुकोlist *रुकोlist, काष्ठा closure *cl)
अणु
	अगर (atomic_पढ़ो(&cl->reमुख्यing) & CLOSURE_WAITING)
		वापस false;

	closure_set_रुकोing(cl, _RET_IP_);
	atomic_add(CLOSURE_WAITING + 1, &cl->reमुख्यing);
	llist_add(&cl->list, &रुकोlist->list);

	वापस true;
पूर्ण

काष्ठा closure_syncer अणु
	काष्ठा task_काष्ठा	*task;
	पूर्णांक			करोne;
पूर्ण;

अटल व्योम closure_sync_fn(काष्ठा closure *cl)
अणु
	काष्ठा closure_syncer *s = cl->s;
	काष्ठा task_काष्ठा *p;

	rcu_पढ़ो_lock();
	p = READ_ONCE(s->task);
	s->करोne = 1;
	wake_up_process(p);
	rcu_पढ़ो_unlock();
पूर्ण

व्योम __sched __closure_sync(काष्ठा closure *cl)
अणु
	काष्ठा closure_syncer s = अणु .task = current पूर्ण;

	cl->s = &s;
	जारी_at(cl, closure_sync_fn, शून्य);

	जबतक (1) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		अगर (s.करोne)
			अवरोध;
		schedule();
	पूर्ण

	__set_current_state(TASK_RUNNING);
पूर्ण

#अगर_घोषित CONFIG_BCACHE_CLOSURES_DEBUG

अटल LIST_HEAD(closure_list);
अटल DEFINE_SPINLOCK(closure_list_lock);

व्योम closure_debug_create(काष्ठा closure *cl)
अणु
	अचिन्हित दीर्घ flags;

	BUG_ON(cl->magic == CLOSURE_MAGIC_ALIVE);
	cl->magic = CLOSURE_MAGIC_ALIVE;

	spin_lock_irqsave(&closure_list_lock, flags);
	list_add(&cl->all, &closure_list);
	spin_unlock_irqrestore(&closure_list_lock, flags);
पूर्ण

व्योम closure_debug_destroy(काष्ठा closure *cl)
अणु
	अचिन्हित दीर्घ flags;

	BUG_ON(cl->magic != CLOSURE_MAGIC_ALIVE);
	cl->magic = CLOSURE_MAGIC_DEAD;

	spin_lock_irqsave(&closure_list_lock, flags);
	list_del(&cl->all);
	spin_unlock_irqrestore(&closure_list_lock, flags);
पूर्ण

अटल काष्ठा dentry *closure_debug;

अटल पूर्णांक debug_show(काष्ठा seq_file *f, व्योम *data)
अणु
	काष्ठा closure *cl;

	spin_lock_irq(&closure_list_lock);

	list_क्रम_each_entry(cl, &closure_list, all) अणु
		पूर्णांक r = atomic_पढ़ो(&cl->reमुख्यing);

		seq_म_लिखो(f, "%p: %pS -> %pS p %p r %i ",
			   cl, (व्योम *) cl->ip, cl->fn, cl->parent,
			   r & CLOSURE_REMAINING_MASK);

		seq_म_लिखो(f, "%s%s\n",
			   test_bit(WORK_STRUCT_PENDING_BIT,
				    work_data_bits(&cl->work)) ? "Q" : "",
			   r & CLOSURE_RUNNING	? "R" : "");

		अगर (r & CLOSURE_WAITING)
			seq_म_लिखो(f, " W %pS\n",
				   (व्योम *) cl->रुकोing_on);

		seq_म_लिखो(f, "\n");
	पूर्ण

	spin_unlock_irq(&closure_list_lock);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(debug);

व्योम  __init closure_debug_init(व्योम)
अणु
	अगर (!IS_ERR_OR_शून्य(bcache_debug))
		/*
		 * it is unnecessary to check वापस value of
		 * debugfs_create_file(), we should not care
		 * about this.
		 */
		closure_debug = debugfs_create_file(
			"closures", 0400, bcache_debug, शून्य, &debug_fops);
पूर्ण
#पूर्ण_अगर

MODULE_AUTHOR("Kent Overstreet <koverstreet@google.com>");
MODULE_LICENSE("GPL");
