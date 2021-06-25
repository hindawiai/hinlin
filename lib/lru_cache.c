<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   lru_cache.c

   This file is part of DRBD by Philipp Reisner and Lars Ellenberg.

   Copyright (C) 2003-2008, LINBIT Inक्रमmation Technologies GmbH.
   Copyright (C) 2003-2008, Philipp Reisner <philipp.reisner@linbit.com>.
   Copyright (C) 2003-2008, Lars Ellenberg <lars.ellenberg@linbit.com>.


 */

#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स> /* क्रम स_रखो */
#समावेश <linux/seq_file.h> /* क्रम seq_म_लिखो */
#समावेश <linux/lru_cache.h>

MODULE_AUTHOR("Philipp Reisner <phil@linbit.com>, "
	      "Lars Ellenberg <lars@linbit.com>");
MODULE_DESCRIPTION("lru_cache - Track sets of hot objects");
MODULE_LICENSE("GPL");

/* this is developers aid only.
 * it catches concurrent access (lack of locking on the users part) */
#घोषणा PARANOIA_ENTRY() करो अणु		\
	BUG_ON(!lc);			\
	BUG_ON(!lc->nr_elements);	\
	BUG_ON(test_and_set_bit(__LC_PARANOIA, &lc->flags)); \
पूर्ण जबतक (0)

#घोषणा RETURN(x...)     करो अणु \
	clear_bit_unlock(__LC_PARANOIA, &lc->flags); \
	वापस x ; पूर्ण जबतक (0)

/* BUG() अगर e is not one of the elements tracked by lc */
#घोषणा PARANOIA_LC_ELEMENT(lc, e) करो अणु	\
	काष्ठा lru_cache *lc_ = (lc);	\
	काष्ठा lc_element *e_ = (e);	\
	अचिन्हित i = e_->lc_index;	\
	BUG_ON(i >= lc_->nr_elements);	\
	BUG_ON(lc_->lc_element[i] != e_); पूर्ण जबतक (0)


/* We need to atomically
 *  - try to grab the lock (set LC_LOCKED)
 *  - only अगर there is no pending transaction
 *    (neither LC_सूचीTY nor LC_STARVING is set)
 * Because of PARANOIA_ENTRY() above abusing lc->flags as well,
 * it is not sufficient to just say
 *	वापस 0 == cmpxchg(&lc->flags, 0, LC_LOCKED);
 */
पूर्णांक lc_try_lock(काष्ठा lru_cache *lc)
अणु
	अचिन्हित दीर्घ val;
	करो अणु
		val = cmpxchg(&lc->flags, 0, LC_LOCKED);
	पूर्ण जबतक (unlikely (val == LC_PARANOIA));
	/* Spin until no-one is inside a PARANOIA_ENTRY()/RETURN() section. */
	वापस 0 == val;
#अगर 0
	/* Alternative approach, spin in हाल someone enters or leaves a
	 * PARANOIA_ENTRY()/RETURN() section. */
	अचिन्हित दीर्घ old, new, val;
	करो अणु
		old = lc->flags & LC_PARANOIA;
		new = old | LC_LOCKED;
		val = cmpxchg(&lc->flags, old, new);
	पूर्ण जबतक (unlikely (val == (old ^ LC_PARANOIA)));
	वापस old == val;
#पूर्ण_अगर
पूर्ण

/**
 * lc_create - prepares to track objects in an active set
 * @name: descriptive name only used in lc_seq_म_लिखो_stats and lc_seq_dump_details
 * @cache: cache root poपूर्णांकer
 * @max_pending_changes: maximum changes to accumulate until a transaction is required
 * @e_count: number of elements allowed to be active simultaneously
 * @e_size: size of the tracked objects
 * @e_off: offset to the &काष्ठा lc_element member in a tracked object
 *
 * Returns a poपूर्णांकer to a newly initialized काष्ठा lru_cache on success,
 * or शून्य on (allocation) failure.
 */
काष्ठा lru_cache *lc_create(स्थिर अक्षर *name, काष्ठा kmem_cache *cache,
		अचिन्हित max_pending_changes,
		अचिन्हित e_count, माप_प्रकार e_size, माप_प्रकार e_off)
अणु
	काष्ठा hlist_head *slot = शून्य;
	काष्ठा lc_element **element = शून्य;
	काष्ठा lru_cache *lc;
	काष्ठा lc_element *e;
	अचिन्हित cache_obj_size = kmem_cache_size(cache);
	अचिन्हित i;

	WARN_ON(cache_obj_size < e_size);
	अगर (cache_obj_size < e_size)
		वापस शून्य;

	/* e_count too big; would probably fail the allocation below anyways.
	 * क्रम typical use हालs, e_count should be few thousand at most. */
	अगर (e_count > LC_MAX_ACTIVE)
		वापस शून्य;

	slot = kसुस्मृति(e_count, माप(काष्ठा hlist_head), GFP_KERNEL);
	अगर (!slot)
		जाओ out_fail;
	element = kसुस्मृति(e_count, माप(काष्ठा lc_element *), GFP_KERNEL);
	अगर (!element)
		जाओ out_fail;

	lc = kzalloc(माप(*lc), GFP_KERNEL);
	अगर (!lc)
		जाओ out_fail;

	INIT_LIST_HEAD(&lc->in_use);
	INIT_LIST_HEAD(&lc->lru);
	INIT_LIST_HEAD(&lc->मुक्त);
	INIT_LIST_HEAD(&lc->to_be_changed);

	lc->name = name;
	lc->element_size = e_size;
	lc->element_off = e_off;
	lc->nr_elements = e_count;
	lc->max_pending_changes = max_pending_changes;
	lc->lc_cache = cache;
	lc->lc_element = element;
	lc->lc_slot = slot;

	/* pपुनः_स्मृतिate all objects */
	क्रम (i = 0; i < e_count; i++) अणु
		व्योम *p = kmem_cache_alloc(cache, GFP_KERNEL);
		अगर (!p)
			अवरोध;
		स_रखो(p, 0, lc->element_size);
		e = p + e_off;
		e->lc_index = i;
		e->lc_number = LC_FREE;
		e->lc_new_number = LC_FREE;
		list_add(&e->list, &lc->मुक्त);
		element[i] = e;
	पूर्ण
	अगर (i == e_count)
		वापस lc;

	/* अन्यथा: could not allocate all elements, give up */
	क्रम (i--; i; i--) अणु
		व्योम *p = element[i];
		kmem_cache_मुक्त(cache, p - e_off);
	पूर्ण
	kमुक्त(lc);
out_fail:
	kमुक्त(element);
	kमुक्त(slot);
	वापस शून्य;
पूर्ण

अटल व्योम lc_मुक्त_by_index(काष्ठा lru_cache *lc, अचिन्हित i)
अणु
	व्योम *p = lc->lc_element[i];
	WARN_ON(!p);
	अगर (p) अणु
		p -= lc->element_off;
		kmem_cache_मुक्त(lc->lc_cache, p);
	पूर्ण
पूर्ण

/**
 * lc_destroy - मुक्तs memory allocated by lc_create()
 * @lc: the lru cache to destroy
 */
व्योम lc_destroy(काष्ठा lru_cache *lc)
अणु
	अचिन्हित i;
	अगर (!lc)
		वापस;
	क्रम (i = 0; i < lc->nr_elements; i++)
		lc_मुक्त_by_index(lc, i);
	kमुक्त(lc->lc_element);
	kमुक्त(lc->lc_slot);
	kमुक्त(lc);
पूर्ण

/**
 * lc_reset - करोes a full reset क्रम @lc and the hash table slots.
 * @lc: the lru cache to operate on
 *
 * It is roughly the equivalent of re-allocating a fresh lru_cache object,
 * basically a लघु cut to lc_destroy(lc); lc = lc_create(...);
 */
व्योम lc_reset(काष्ठा lru_cache *lc)
अणु
	अचिन्हित i;

	INIT_LIST_HEAD(&lc->in_use);
	INIT_LIST_HEAD(&lc->lru);
	INIT_LIST_HEAD(&lc->मुक्त);
	INIT_LIST_HEAD(&lc->to_be_changed);
	lc->used = 0;
	lc->hits = 0;
	lc->misses = 0;
	lc->starving = 0;
	lc->locked = 0;
	lc->changed = 0;
	lc->pending_changes = 0;
	lc->flags = 0;
	स_रखो(lc->lc_slot, 0, माप(काष्ठा hlist_head) * lc->nr_elements);

	क्रम (i = 0; i < lc->nr_elements; i++) अणु
		काष्ठा lc_element *e = lc->lc_element[i];
		व्योम *p = e;
		p -= lc->element_off;
		स_रखो(p, 0, lc->element_size);
		/* re-init it */
		e->lc_index = i;
		e->lc_number = LC_FREE;
		e->lc_new_number = LC_FREE;
		list_add(&e->list, &lc->मुक्त);
	पूर्ण
पूर्ण

/**
 * lc_seq_म_लिखो_stats - prपूर्णांक stats about @lc पूर्णांकo @seq
 * @seq: the seq_file to prपूर्णांक पूर्णांकo
 * @lc: the lru cache to prपूर्णांक statistics of
 */
व्योम lc_seq_म_लिखो_stats(काष्ठा seq_file *seq, काष्ठा lru_cache *lc)
अणु
	/* NOTE:
	 * total calls to lc_get are
	 * (starving + hits + misses)
	 * misses include "locked" count (update from an other thपढ़ो in
	 * progress) and "changed", when this in fact lead to an successful
	 * update of the cache.
	 */
	seq_म_लिखो(seq, "\t%s: used:%u/%u hits:%lu misses:%lu starving:%lu locked:%lu changed:%lu\n",
		   lc->name, lc->used, lc->nr_elements,
		   lc->hits, lc->misses, lc->starving, lc->locked, lc->changed);
पूर्ण

अटल काष्ठा hlist_head *lc_hash_slot(काष्ठा lru_cache *lc, अचिन्हित पूर्णांक enr)
अणु
	वापस  lc->lc_slot + (enr % lc->nr_elements);
पूर्ण


अटल काष्ठा lc_element *__lc_find(काष्ठा lru_cache *lc, अचिन्हित पूर्णांक enr,
		bool include_changing)
अणु
	काष्ठा lc_element *e;

	BUG_ON(!lc);
	BUG_ON(!lc->nr_elements);
	hlist_क्रम_each_entry(e, lc_hash_slot(lc, enr), colision) अणु
		/* "about to be changed" elements, pending transaction commit,
		 * are hashed by their "new number". "Normal" elements have
		 * lc_number == lc_new_number. */
		अगर (e->lc_new_number != enr)
			जारी;
		अगर (e->lc_new_number == e->lc_number || include_changing)
			वापस e;
		अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * lc_find - find element by label, अगर present in the hash table
 * @lc: The lru_cache object
 * @enr: element number
 *
 * Returns the poपूर्णांकer to an element, अगर the element with the requested
 * "label" or element number is present in the hash table,
 * or शून्य अगर not found. Does not change the refcnt.
 * Ignores elements that are "about to be used", i.e. not yet in the active
 * set, but still pending transaction commit.
 */
काष्ठा lc_element *lc_find(काष्ठा lru_cache *lc, अचिन्हित पूर्णांक enr)
अणु
	वापस __lc_find(lc, enr, 0);
पूर्ण

/**
 * lc_is_used - find element by label
 * @lc: The lru_cache object
 * @enr: element number
 *
 * Returns true, अगर the element with the requested "label" or element number is
 * present in the hash table, and is used (refcnt > 0).
 * Also finds elements that are not _currently_ used but only "about to be
 * used", i.e. on the "to_be_changed" list, pending transaction commit.
 */
bool lc_is_used(काष्ठा lru_cache *lc, अचिन्हित पूर्णांक enr)
अणु
	काष्ठा lc_element *e = __lc_find(lc, enr, 1);
	वापस e && e->refcnt;
पूर्ण

/**
 * lc_del - हटाओs an element from the cache
 * @lc: The lru_cache object
 * @e: The element to हटाओ
 *
 * @e must be unused (refcnt == 0). Moves @e from "lru" to "free" list,
 * sets @e->enr to %LC_FREE.
 */
व्योम lc_del(काष्ठा lru_cache *lc, काष्ठा lc_element *e)
अणु
	PARANOIA_ENTRY();
	PARANOIA_LC_ELEMENT(lc, e);
	BUG_ON(e->refcnt);

	e->lc_number = e->lc_new_number = LC_FREE;
	hlist_del_init(&e->colision);
	list_move(&e->list, &lc->मुक्त);
	RETURN();
पूर्ण

अटल काष्ठा lc_element *lc_prepare_क्रम_change(काष्ठा lru_cache *lc, अचिन्हित new_number)
अणु
	काष्ठा list_head *n;
	काष्ठा lc_element *e;

	अगर (!list_empty(&lc->मुक्त))
		n = lc->मुक्त.next;
	अन्यथा अगर (!list_empty(&lc->lru))
		n = lc->lru.prev;
	अन्यथा
		वापस शून्य;

	e = list_entry(n, काष्ठा lc_element, list);
	PARANOIA_LC_ELEMENT(lc, e);

	e->lc_new_number = new_number;
	अगर (!hlist_unhashed(&e->colision))
		__hlist_del(&e->colision);
	hlist_add_head(&e->colision, lc_hash_slot(lc, new_number));
	list_move(&e->list, &lc->to_be_changed);

	वापस e;
पूर्ण

अटल पूर्णांक lc_unused_element_available(काष्ठा lru_cache *lc)
अणु
	अगर (!list_empty(&lc->मुक्त))
		वापस 1; /* something on the मुक्त list */
	अगर (!list_empty(&lc->lru))
		वापस 1;  /* something to evict */

	वापस 0;
पूर्ण

/* used as पूर्णांकernal flags to __lc_get */
क्रमागत अणु
	LC_GET_MAY_CHANGE = 1,
	LC_GET_MAY_USE_UNCOMMITTED = 2,
पूर्ण;

अटल काष्ठा lc_element *__lc_get(काष्ठा lru_cache *lc, अचिन्हित पूर्णांक enr, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा lc_element *e;

	PARANOIA_ENTRY();
	अगर (lc->flags & LC_STARVING) अणु
		++lc->starving;
		RETURN(शून्य);
	पूर्ण

	e = __lc_find(lc, enr, 1);
	/* अगर lc_new_number != lc_number,
	 * this enr is currently being pulled in alपढ़ोy,
	 * and will be available once the pending transaction
	 * has been committed. */
	अगर (e) अणु
		अगर (e->lc_new_number != e->lc_number) अणु
			/* It has been found above, but on the "to_be_changed"
			 * list, not yet committed.  Don't pull it in twice,
			 * रुको क्रम the transaction, then try again...
			 */
			अगर (!(flags & LC_GET_MAY_USE_UNCOMMITTED))
				RETURN(शून्य);
			/* ... unless the caller is aware of the implications,
			 * probably preparing a cumulative transaction. */
			++e->refcnt;
			++lc->hits;
			RETURN(e);
		पूर्ण
		/* अन्यथा: lc_new_number == lc_number; a real hit. */
		++lc->hits;
		अगर (e->refcnt++ == 0)
			lc->used++;
		list_move(&e->list, &lc->in_use); /* Not evictable... */
		RETURN(e);
	पूर्ण
	/* e == शून्य */

	++lc->misses;
	अगर (!(flags & LC_GET_MAY_CHANGE))
		RETURN(शून्य);

	/* To aव्योम races with lc_try_lock(), first, mark us dirty
	 * (using test_and_set_bit, as it implies memory barriers), ... */
	test_and_set_bit(__LC_सूचीTY, &lc->flags);

	/* ... only then check अगर it is locked anyways. If lc_unlock clears
	 * the dirty bit again, that's not a problem, we will come here again.
	 */
	अगर (test_bit(__LC_LOCKED, &lc->flags)) अणु
		++lc->locked;
		RETURN(शून्य);
	पूर्ण

	/* In हाल there is nothing available and we can not kick out
	 * the LRU element, we have to रुको ...
	 */
	अगर (!lc_unused_element_available(lc)) अणु
		__set_bit(__LC_STARVING, &lc->flags);
		RETURN(शून्य);
	पूर्ण

	/* It was not present in the active set.  We are going to recycle an
	 * unused (or even "free") element, but we won't accumulate more than
	 * max_pending_changes changes.  */
	अगर (lc->pending_changes >= lc->max_pending_changes)
		RETURN(शून्य);

	e = lc_prepare_क्रम_change(lc, enr);
	BUG_ON(!e);

	clear_bit(__LC_STARVING, &lc->flags);
	BUG_ON(++e->refcnt != 1);
	lc->used++;
	lc->pending_changes++;

	RETURN(e);
पूर्ण

/**
 * lc_get - get element by label, maybe change the active set
 * @lc: the lru cache to operate on
 * @enr: the label to look up
 *
 * Finds an element in the cache, increases its usage count,
 * "touches" and वापसs it.
 *
 * In हाल the requested number is not present, it needs to be added to the
 * cache. Thereक्रमe it is possible that an other element becomes evicted from
 * the cache. In either हाल, the user is notअगरied so he is able to e.g. keep
 * a persistent log of the cache changes, and thereक्रमe the objects in use.
 *
 * Return values:
 *  शून्य
 *     The cache was marked %LC_STARVING,
 *     or the requested label was not in the active set
 *     and a changing transaction is still pending (@lc was marked %LC_सूचीTY).
 *     Or no unused or मुक्त element could be recycled (@lc will be marked as
 *     %LC_STARVING, blocking further lc_get() operations).
 *
 *  poपूर्णांकer to the element with the REQUESTED element number.
 *     In this हाल, it can be used right away
 *
 *  poपूर्णांकer to an UNUSED element with some dअगरferent element number,
 *          where that dअगरferent number may also be %LC_FREE.
 *
 *          In this हाल, the cache is marked %LC_सूचीTY,
 *          so lc_try_lock() will no दीर्घer succeed.
 *          The वापसed element poपूर्णांकer is moved to the "to_be_changed" list,
 *          and रेजिस्टरed with the new element number on the hash collision chains,
 *          so it is possible to pick it up from lc_is_used().
 *          Up to "max_pending_changes" (see lc_create()) can be accumulated.
 *          The user now should करो whatever housekeeping is necessary,
 *          typically serialize on lc_try_lock_क्रम_transaction(), then call
 *          lc_committed(lc) and lc_unlock(), to finish the change.
 *
 * NOTE: The user needs to check the lc_number on EACH use, so he recognizes
 *       any cache set change.
 */
काष्ठा lc_element *lc_get(काष्ठा lru_cache *lc, अचिन्हित पूर्णांक enr)
अणु
	वापस __lc_get(lc, enr, LC_GET_MAY_CHANGE);
पूर्ण

/**
 * lc_get_cumulative - like lc_get; also finds to-be-changed elements
 * @lc: the lru cache to operate on
 * @enr: the label to look up
 *
 * Unlike lc_get this also वापसs the element क्रम @enr, अगर it is beदीर्घing to
 * a pending transaction, so the वापस values are like क्रम lc_get(),
 * plus:
 *
 * poपूर्णांकer to an element alपढ़ोy on the "to_be_changed" list.
 * 	In this हाल, the cache was alपढ़ोy marked %LC_सूचीTY.
 *
 * Caller needs to make sure that the pending transaction is completed,
 * beक्रमe proceeding to actually use this element.
 */
काष्ठा lc_element *lc_get_cumulative(काष्ठा lru_cache *lc, अचिन्हित पूर्णांक enr)
अणु
	वापस __lc_get(lc, enr, LC_GET_MAY_CHANGE|LC_GET_MAY_USE_UNCOMMITTED);
पूर्ण

/**
 * lc_try_get - get element by label, अगर present; करो not change the active set
 * @lc: the lru cache to operate on
 * @enr: the label to look up
 *
 * Finds an element in the cache, increases its usage count,
 * "touches" and वापसs it.
 *
 * Return values:
 *  शून्य
 *     The cache was marked %LC_STARVING,
 *     or the requested label was not in the active set
 *
 *  poपूर्णांकer to the element with the REQUESTED element number.
 *     In this हाल, it can be used right away
 */
काष्ठा lc_element *lc_try_get(काष्ठा lru_cache *lc, अचिन्हित पूर्णांक enr)
अणु
	वापस __lc_get(lc, enr, 0);
पूर्ण

/**
 * lc_committed - tell @lc that pending changes have been recorded
 * @lc: the lru cache to operate on
 *
 * User is expected to serialize on explicit lc_try_lock_क्रम_transaction()
 * beक्रमe the transaction is started, and later needs to lc_unlock() explicitly
 * as well.
 */
व्योम lc_committed(काष्ठा lru_cache *lc)
अणु
	काष्ठा lc_element *e, *पंचांगp;

	PARANOIA_ENTRY();
	list_क्रम_each_entry_safe(e, पंचांगp, &lc->to_be_changed, list) अणु
		/* count number of changes, not number of transactions */
		++lc->changed;
		e->lc_number = e->lc_new_number;
		list_move(&e->list, &lc->in_use);
	पूर्ण
	lc->pending_changes = 0;
	RETURN();
पूर्ण


/**
 * lc_put - give up refcnt of @e
 * @lc: the lru cache to operate on
 * @e: the element to put
 *
 * If refcnt reaches zero, the element is moved to the lru list,
 * and a %LC_STARVING (अगर set) is cleared.
 * Returns the new (post-decrement) refcnt.
 */
अचिन्हित पूर्णांक lc_put(काष्ठा lru_cache *lc, काष्ठा lc_element *e)
अणु
	PARANOIA_ENTRY();
	PARANOIA_LC_ELEMENT(lc, e);
	BUG_ON(e->refcnt == 0);
	BUG_ON(e->lc_number != e->lc_new_number);
	अगर (--e->refcnt == 0) अणु
		/* move it to the front of LRU. */
		list_move(&e->list, &lc->lru);
		lc->used--;
		clear_bit_unlock(__LC_STARVING, &lc->flags);
	पूर्ण
	RETURN(e->refcnt);
पूर्ण

/**
 * lc_element_by_index
 * @lc: the lru cache to operate on
 * @i: the index of the element to वापस
 */
काष्ठा lc_element *lc_element_by_index(काष्ठा lru_cache *lc, अचिन्हित i)
अणु
	BUG_ON(i >= lc->nr_elements);
	BUG_ON(lc->lc_element[i] == शून्य);
	BUG_ON(lc->lc_element[i]->lc_index != i);
	वापस lc->lc_element[i];
पूर्ण

/**
 * lc_index_of
 * @lc: the lru cache to operate on
 * @e: the element to query क्रम its index position in lc->element
 */
अचिन्हित पूर्णांक lc_index_of(काष्ठा lru_cache *lc, काष्ठा lc_element *e)
अणु
	PARANOIA_LC_ELEMENT(lc, e);
	वापस e->lc_index;
पूर्ण

/**
 * lc_set - associate index with label
 * @lc: the lru cache to operate on
 * @enr: the label to set
 * @index: the element index to associate label with.
 *
 * Used to initialize the active set to some previously recorded state.
 */
व्योम lc_set(काष्ठा lru_cache *lc, अचिन्हित पूर्णांक enr, पूर्णांक index)
अणु
	काष्ठा lc_element *e;
	काष्ठा list_head *lh;

	अगर (index < 0 || index >= lc->nr_elements)
		वापस;

	e = lc_element_by_index(lc, index);
	BUG_ON(e->lc_number != e->lc_new_number);
	BUG_ON(e->refcnt != 0);

	e->lc_number = e->lc_new_number = enr;
	hlist_del_init(&e->colision);
	अगर (enr == LC_FREE)
		lh = &lc->मुक्त;
	अन्यथा अणु
		hlist_add_head(&e->colision, lc_hash_slot(lc, enr));
		lh = &lc->lru;
	पूर्ण
	list_move(&e->list, lh);
पूर्ण

/**
 * lc_seq_dump_details - Dump a complete LRU cache to seq in textual क्रमm.
 * @lc: the lru cache to operate on
 * @seq: the &काष्ठा seq_file poपूर्णांकer to seq_म_लिखो पूर्णांकo
 * @utext: user supplied additional "heading" or other info
 * @detail: function poपूर्णांकer the user may provide to dump further details
 * of the object the lc_element is embedded in. May be शून्य.
 * Note: a leading space ' ' and trailing newline '\n' is implied.
 */
व्योम lc_seq_dump_details(काष्ठा seq_file *seq, काष्ठा lru_cache *lc, अक्षर *utext,
	     व्योम (*detail) (काष्ठा seq_file *, काष्ठा lc_element *))
अणु
	अचिन्हित पूर्णांक nr_elements = lc->nr_elements;
	काष्ठा lc_element *e;
	पूर्णांक i;

	seq_म_लिखो(seq, "\tnn: lc_number (new nr) refcnt %s\n ", utext);
	क्रम (i = 0; i < nr_elements; i++) अणु
		e = lc_element_by_index(lc, i);
		अगर (e->lc_number != e->lc_new_number)
			seq_म_लिखो(seq, "\t%5d: %6d %8d %6d ",
				i, e->lc_number, e->lc_new_number, e->refcnt);
		अन्यथा
			seq_म_लिखो(seq, "\t%5d: %6d %-8s %6d ",
				i, e->lc_number, "-\"-", e->refcnt);
		अगर (detail)
			detail(seq, e);
		seq_अ_दो(seq, '\n');
	पूर्ण
पूर्ण

EXPORT_SYMBOL(lc_create);
EXPORT_SYMBOL(lc_reset);
EXPORT_SYMBOL(lc_destroy);
EXPORT_SYMBOL(lc_set);
EXPORT_SYMBOL(lc_del);
EXPORT_SYMBOL(lc_try_get);
EXPORT_SYMBOL(lc_find);
EXPORT_SYMBOL(lc_get);
EXPORT_SYMBOL(lc_put);
EXPORT_SYMBOL(lc_committed);
EXPORT_SYMBOL(lc_element_by_index);
EXPORT_SYMBOL(lc_index_of);
EXPORT_SYMBOL(lc_seq_म_लिखो_stats);
EXPORT_SYMBOL(lc_seq_dump_details);
EXPORT_SYMBOL(lc_try_lock);
EXPORT_SYMBOL(lc_is_used);
EXPORT_SYMBOL(lc_get_cumulative);
