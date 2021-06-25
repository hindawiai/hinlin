<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * klist.c - Routines क्रम manipulating klists.
 *
 * Copyright (C) 2005 Patrick Mochel
 *
 * This klist पूर्णांकerface provides a couple of काष्ठाures that wrap around
 * काष्ठा list_head to provide explicit list "head" (काष्ठा klist) and list
 * "node" (काष्ठा klist_node) objects. For काष्ठा klist, a spinlock is
 * included that protects access to the actual list itself. काष्ठा
 * klist_node provides a poपूर्णांकer to the klist that owns it and a kref
 * reference count that indicates the number of current users of that node
 * in the list.
 *
 * The entire poपूर्णांक is to provide an पूर्णांकerface क्रम iterating over a list
 * that is safe and allows क्रम modअगरication of the list during the
 * iteration (e.g. insertion and removal), including modअगरication of the
 * current node on the list.
 *
 * It works using a 3rd object type - काष्ठा klist_iter - that is declared
 * and initialized beक्रमe an iteration. klist_next() is used to acquire the
 * next element in the list. It वापसs शून्य अगर there are no more items.
 * Internally, that routine takes the klist's lock, decrements the
 * reference count of the previous klist_node and increments the count of
 * the next klist_node. It then drops the lock and वापसs.
 *
 * There are primitives क्रम adding and removing nodes to/from a klist.
 * When deleting, klist_del() will simply decrement the reference count.
 * Only when the count goes to 0 is the node हटाओd from the list.
 * klist_हटाओ() will try to delete the node from the list and block until
 * it is actually हटाओd. This is useful क्रम objects (like devices) that
 * have been हटाओd from the प्रणाली and must be मुक्तd (but must रुको until
 * all accessors have finished).
 */

#समावेश <linux/klist.h>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>

/*
 * Use the lowest bit of n_klist to mark deleted nodes and exclude
 * dead ones from iteration.
 */
#घोषणा KNODE_DEAD		1LU
#घोषणा KNODE_KLIST_MASK	~KNODE_DEAD

अटल काष्ठा klist *knode_klist(काष्ठा klist_node *knode)
अणु
	वापस (काष्ठा klist *)
		((अचिन्हित दीर्घ)knode->n_klist & KNODE_KLIST_MASK);
पूर्ण

अटल bool knode_dead(काष्ठा klist_node *knode)
अणु
	वापस (अचिन्हित दीर्घ)knode->n_klist & KNODE_DEAD;
पूर्ण

अटल व्योम knode_set_klist(काष्ठा klist_node *knode, काष्ठा klist *klist)
अणु
	knode->n_klist = klist;
	/* no knode deserves to start its lअगरe dead */
	WARN_ON(knode_dead(knode));
पूर्ण

अटल व्योम knode_समाप्त(काष्ठा klist_node *knode)
अणु
	/* and no knode should die twice ever either, see we're very humane */
	WARN_ON(knode_dead(knode));
	*(अचिन्हित दीर्घ *)&knode->n_klist |= KNODE_DEAD;
पूर्ण

/**
 * klist_init - Initialize a klist काष्ठाure.
 * @k: The klist we're initializing.
 * @get: The get function क्रम the embedding object (शून्य अगर none)
 * @put: The put function क्रम the embedding object (शून्य अगर none)
 *
 * Initialises the klist काष्ठाure.  If the klist_node काष्ठाures are
 * going to be embedded in refcounted objects (necessary क्रम safe
 * deletion) then the get/put arguments are used to initialise
 * functions that take and release references on the embedding
 * objects.
 */
व्योम klist_init(काष्ठा klist *k, व्योम (*get)(काष्ठा klist_node *),
		व्योम (*put)(काष्ठा klist_node *))
अणु
	INIT_LIST_HEAD(&k->k_list);
	spin_lock_init(&k->k_lock);
	k->get = get;
	k->put = put;
पूर्ण
EXPORT_SYMBOL_GPL(klist_init);

अटल व्योम add_head(काष्ठा klist *k, काष्ठा klist_node *n)
अणु
	spin_lock(&k->k_lock);
	list_add(&n->n_node, &k->k_list);
	spin_unlock(&k->k_lock);
पूर्ण

अटल व्योम add_tail(काष्ठा klist *k, काष्ठा klist_node *n)
अणु
	spin_lock(&k->k_lock);
	list_add_tail(&n->n_node, &k->k_list);
	spin_unlock(&k->k_lock);
पूर्ण

अटल व्योम klist_node_init(काष्ठा klist *k, काष्ठा klist_node *n)
अणु
	INIT_LIST_HEAD(&n->n_node);
	kref_init(&n->n_ref);
	knode_set_klist(n, k);
	अगर (k->get)
		k->get(n);
पूर्ण

/**
 * klist_add_head - Initialize a klist_node and add it to front.
 * @n: node we're adding.
 * @k: klist it's going on.
 */
व्योम klist_add_head(काष्ठा klist_node *n, काष्ठा klist *k)
अणु
	klist_node_init(k, n);
	add_head(k, n);
पूर्ण
EXPORT_SYMBOL_GPL(klist_add_head);

/**
 * klist_add_tail - Initialize a klist_node and add it to back.
 * @n: node we're adding.
 * @k: klist it's going on.
 */
व्योम klist_add_tail(काष्ठा klist_node *n, काष्ठा klist *k)
अणु
	klist_node_init(k, n);
	add_tail(k, n);
पूर्ण
EXPORT_SYMBOL_GPL(klist_add_tail);

/**
 * klist_add_behind - Init a klist_node and add it after an existing node
 * @n: node we're adding.
 * @pos: node to put @n after
 */
व्योम klist_add_behind(काष्ठा klist_node *n, काष्ठा klist_node *pos)
अणु
	काष्ठा klist *k = knode_klist(pos);

	klist_node_init(k, n);
	spin_lock(&k->k_lock);
	list_add(&n->n_node, &pos->n_node);
	spin_unlock(&k->k_lock);
पूर्ण
EXPORT_SYMBOL_GPL(klist_add_behind);

/**
 * klist_add_beक्रमe - Init a klist_node and add it beक्रमe an existing node
 * @n: node we're adding.
 * @pos: node to put @n after
 */
व्योम klist_add_beक्रमe(काष्ठा klist_node *n, काष्ठा klist_node *pos)
अणु
	काष्ठा klist *k = knode_klist(pos);

	klist_node_init(k, n);
	spin_lock(&k->k_lock);
	list_add_tail(&n->n_node, &pos->n_node);
	spin_unlock(&k->k_lock);
पूर्ण
EXPORT_SYMBOL_GPL(klist_add_beक्रमe);

काष्ठा klist_रुकोer अणु
	काष्ठा list_head list;
	काष्ठा klist_node *node;
	काष्ठा task_काष्ठा *process;
	पूर्णांक woken;
पूर्ण;

अटल DEFINE_SPINLOCK(klist_हटाओ_lock);
अटल LIST_HEAD(klist_हटाओ_रुकोers);

अटल व्योम klist_release(काष्ठा kref *kref)
अणु
	काष्ठा klist_रुकोer *रुकोer, *पंचांगp;
	काष्ठा klist_node *n = container_of(kref, काष्ठा klist_node, n_ref);

	WARN_ON(!knode_dead(n));
	list_del(&n->n_node);
	spin_lock(&klist_हटाओ_lock);
	list_क्रम_each_entry_safe(रुकोer, पंचांगp, &klist_हटाओ_रुकोers, list) अणु
		अगर (रुकोer->node != n)
			जारी;

		list_del(&रुकोer->list);
		रुकोer->woken = 1;
		mb();
		wake_up_process(रुकोer->process);
	पूर्ण
	spin_unlock(&klist_हटाओ_lock);
	knode_set_klist(n, शून्य);
पूर्ण

अटल पूर्णांक klist_dec_and_del(काष्ठा klist_node *n)
अणु
	वापस kref_put(&n->n_ref, klist_release);
पूर्ण

अटल व्योम klist_put(काष्ठा klist_node *n, bool समाप्त)
अणु
	काष्ठा klist *k = knode_klist(n);
	व्योम (*put)(काष्ठा klist_node *) = k->put;

	spin_lock(&k->k_lock);
	अगर (समाप्त)
		knode_समाप्त(n);
	अगर (!klist_dec_and_del(n))
		put = शून्य;
	spin_unlock(&k->k_lock);
	अगर (put)
		put(n);
पूर्ण

/**
 * klist_del - Decrement the reference count of node and try to हटाओ.
 * @n: node we're deleting.
 */
व्योम klist_del(काष्ठा klist_node *n)
अणु
	klist_put(n, true);
पूर्ण
EXPORT_SYMBOL_GPL(klist_del);

/**
 * klist_हटाओ - Decrement the refcount of node and रुको क्रम it to go away.
 * @n: node we're removing.
 */
व्योम klist_हटाओ(काष्ठा klist_node *n)
अणु
	काष्ठा klist_रुकोer रुकोer;

	रुकोer.node = n;
	रुकोer.process = current;
	रुकोer.woken = 0;
	spin_lock(&klist_हटाओ_lock);
	list_add(&रुकोer.list, &klist_हटाओ_रुकोers);
	spin_unlock(&klist_हटाओ_lock);

	klist_del(n);

	क्रम (;;) अणु
		set_current_state(TASK_UNINTERRUPTIBLE);
		अगर (रुकोer.woken)
			अवरोध;
		schedule();
	पूर्ण
	__set_current_state(TASK_RUNNING);
पूर्ण
EXPORT_SYMBOL_GPL(klist_हटाओ);

/**
 * klist_node_attached - Say whether a node is bound to a list or not.
 * @n: Node that we're testing.
 */
पूर्णांक klist_node_attached(काष्ठा klist_node *n)
अणु
	वापस (n->n_klist != शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(klist_node_attached);

/**
 * klist_iter_init_node - Initialize a klist_iter काष्ठाure.
 * @k: klist we're iterating.
 * @i: klist_iter we're filling.
 * @n: node to start with.
 *
 * Similar to klist_iter_init(), but starts the action off with @n,
 * instead of with the list head.
 */
व्योम klist_iter_init_node(काष्ठा klist *k, काष्ठा klist_iter *i,
			  काष्ठा klist_node *n)
अणु
	i->i_klist = k;
	i->i_cur = शून्य;
	अगर (n && kref_get_unless_zero(&n->n_ref))
		i->i_cur = n;
पूर्ण
EXPORT_SYMBOL_GPL(klist_iter_init_node);

/**
 * klist_iter_init - Iniitalize a klist_iter काष्ठाure.
 * @k: klist we're iterating.
 * @i: klist_iter काष्ठाure we're filling.
 *
 * Similar to klist_iter_init_node(), but start with the list head.
 */
व्योम klist_iter_init(काष्ठा klist *k, काष्ठा klist_iter *i)
अणु
	klist_iter_init_node(k, i, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(klist_iter_init);

/**
 * klist_iter_निकास - Finish a list iteration.
 * @i: Iterator काष्ठाure.
 *
 * Must be called when करोne iterating over list, as it decrements the
 * refcount of the current node. Necessary in हाल iteration निकासed beक्रमe
 * the end of the list was reached, and always good क्रमm.
 */
व्योम klist_iter_निकास(काष्ठा klist_iter *i)
अणु
	अगर (i->i_cur) अणु
		klist_put(i->i_cur, false);
		i->i_cur = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(klist_iter_निकास);

अटल काष्ठा klist_node *to_klist_node(काष्ठा list_head *n)
अणु
	वापस container_of(n, काष्ठा klist_node, n_node);
पूर्ण

/**
 * klist_prev - Ante up prev node in list.
 * @i: Iterator काष्ठाure.
 *
 * First grab list lock. Decrement the reference count of the previous
 * node, अगर there was one. Grab the prev node, increment its reference
 * count, drop the lock, and वापस that prev node.
 */
काष्ठा klist_node *klist_prev(काष्ठा klist_iter *i)
अणु
	व्योम (*put)(काष्ठा klist_node *) = i->i_klist->put;
	काष्ठा klist_node *last = i->i_cur;
	काष्ठा klist_node *prev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&i->i_klist->k_lock, flags);

	अगर (last) अणु
		prev = to_klist_node(last->n_node.prev);
		अगर (!klist_dec_and_del(last))
			put = शून्य;
	पूर्ण अन्यथा
		prev = to_klist_node(i->i_klist->k_list.prev);

	i->i_cur = शून्य;
	जबतक (prev != to_klist_node(&i->i_klist->k_list)) अणु
		अगर (likely(!knode_dead(prev))) अणु
			kref_get(&prev->n_ref);
			i->i_cur = prev;
			अवरोध;
		पूर्ण
		prev = to_klist_node(prev->n_node.prev);
	पूर्ण

	spin_unlock_irqrestore(&i->i_klist->k_lock, flags);

	अगर (put && last)
		put(last);
	वापस i->i_cur;
पूर्ण
EXPORT_SYMBOL_GPL(klist_prev);

/**
 * klist_next - Ante up next node in list.
 * @i: Iterator काष्ठाure.
 *
 * First grab list lock. Decrement the reference count of the previous
 * node, अगर there was one. Grab the next node, increment its reference
 * count, drop the lock, and वापस that next node.
 */
काष्ठा klist_node *klist_next(काष्ठा klist_iter *i)
अणु
	व्योम (*put)(काष्ठा klist_node *) = i->i_klist->put;
	काष्ठा klist_node *last = i->i_cur;
	काष्ठा klist_node *next;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&i->i_klist->k_lock, flags);

	अगर (last) अणु
		next = to_klist_node(last->n_node.next);
		अगर (!klist_dec_and_del(last))
			put = शून्य;
	पूर्ण अन्यथा
		next = to_klist_node(i->i_klist->k_list.next);

	i->i_cur = शून्य;
	जबतक (next != to_klist_node(&i->i_klist->k_list)) अणु
		अगर (likely(!knode_dead(next))) अणु
			kref_get(&next->n_ref);
			i->i_cur = next;
			अवरोध;
		पूर्ण
		next = to_klist_node(next->n_node.next);
	पूर्ण

	spin_unlock_irqrestore(&i->i_klist->k_lock, flags);

	अगर (put && last)
		put(last);
	वापस i->i_cur;
पूर्ण
EXPORT_SYMBOL_GPL(klist_next);
