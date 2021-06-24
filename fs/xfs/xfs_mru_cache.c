<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2006-2007 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_mru_cache.h"

/*
 * The MRU Cache data काष्ठाure consists of a data store, an array of lists and
 * a lock to protect its पूर्णांकernal state.  At initialisation समय, the client
 * supplies an element lअगरeसमय in milliseconds and a group count, as well as a
 * function poपूर्णांकer to call when deleting elements.  A data काष्ठाure क्रम
 * queueing up work in the क्रमm of समयd callbacks is also included.
 *
 * The group count controls how many lists are created, and thereby how finely
 * the elements are grouped in समय.  When reaping occurs, all the elements in
 * all the lists whose समय has expired are deleted.
 *
 * To give an example of how this works in practice, consider a client that
 * initialises an MRU Cache with a lअगरeसमय of ten seconds and a group count of
 * five.  Five पूर्णांकernal lists will be created, each representing a two second
 * period in समय.  When the first element is added, समय zero क्रम the data
 * काष्ठाure is initialised to the current समय.
 *
 * All the elements added in the first two seconds are appended to the first
 * list.  Elements added in the third second go पूर्णांकo the second list, and so on.
 * If an element is accessed at any poपूर्णांक, it is हटाओd from its list and
 * inserted at the head of the current most-recently-used list.
 *
 * The reaper function will have nothing to करो until at least twelve seconds
 * have elapsed since the first element was added.  The reason क्रम this is that
 * अगर it were called at t=11s, there could be elements in the first list that
 * have only been inactive क्रम nine seconds, so it still करोes nothing.  If it is
 * called anywhere between t=12 and t=14 seconds, it will delete all the
 * elements that reमुख्य in the first list.  It's thereक्रमe possible क्रम elements
 * to reमुख्य in the data store even after they've been inactive क्रम up to
 * (t + t/g) seconds, where t is the inactive element lअगरeसमय and g is the
 * number of groups.
 *
 * The above example assumes that the reaper function माला_लो called at least once
 * every (t/g) seconds.  If it is called less frequently, unused elements will
 * accumulate in the reap list until the reaper function is eventually called.
 * The current implementation uses work queue callbacks to carefully समय the
 * reaper function calls, so this should happen rarely, अगर at all.
 *
 * From a design perspective, the primary reason क्रम the choice of a list array
 * representing discrete समय पूर्णांकervals is that it's only practical to reap
 * expired elements in groups of some appreciable size.  This स्वतःmatically
 * पूर्णांकroduces a granularity to element lअगरeबार, so there's no poपूर्णांक storing an
 * inभागidual समयout with each element that specअगरies a more precise reap समय.
 * The bonus is a saving of माप(दीर्घ) bytes of memory per element stored.
 *
 * The elements could have been stored in just one list, but an array of
 * counters or poपूर्णांकers would need to be मुख्यtained to allow them to be भागided
 * up पूर्णांकo discrete समय groups.  More critically, the process of touching or
 * removing an element would involve walking large portions of the entire list,
 * which would have a detrimental effect on perक्रमmance.  The additional memory
 * requirement क्रम the array of list heads is minimal.
 *
 * When an element is touched or deleted, it needs to be हटाओd from its
 * current list.  Doubly linked lists are used to make the list मुख्यtenance
 * portion of these operations O(1).  Since reaper timing can be imprecise,
 * inserts and lookups can occur when there are no मुक्त lists available.  When
 * this happens, all the elements on the LRU list need to be migrated to the end
 * of the reap list.  To keep the list मुख्यtenance portion of these operations
 * O(1) also, list tails need to be accessible without walking the entire list.
 * This is the reason why करोubly linked list heads are used.
 */

/*
 * An MRU Cache is a dynamic data काष्ठाure that stores its elements in a way
 * that allows efficient lookups, but also groups them पूर्णांकo discrete समय
 * पूर्णांकervals based on insertion समय.  This allows elements to be efficiently
 * and स्वतःmatically reaped after a fixed period of inactivity.
 *
 * When a client data poपूर्णांकer is stored in the MRU Cache it needs to be added to
 * both the data store and to one of the lists.  It must also be possible to
 * access each of these entries via the other, i.e. to:
 *
 *    a) Walk a list, removing the corresponding data store entry क्रम each item.
 *    b) Look up a data store entry, then access its list entry directly.
 *
 * To achieve both of these goals, each entry must contain both a list entry and
 * a key, in addition to the user's data pointer.  Note that it's not a good
 * idea to have the client embed one of these काष्ठाures at the top of their own
 * data काष्ठाure, because inserting the same item more than once would most
 * likely result in a loop in one of the lists.  That's a sure-fire recipe क्रम
 * an infinite loop in the code.
 */
काष्ठा xfs_mru_cache अणु
	काष्ठा radix_tree_root	store;     /* Core storage data काष्ठाure.  */
	काष्ठा list_head	*lists;    /* Array of lists, one per grp.  */
	काष्ठा list_head	reap_list; /* Elements overdue क्रम reaping. */
	spinlock_t		lock;      /* Lock to protect this काष्ठा.  */
	अचिन्हित पूर्णांक		grp_count; /* Number of discrete groups.    */
	अचिन्हित पूर्णांक		grp_समय;  /* Time period spanned by grps.  */
	अचिन्हित पूर्णांक		lru_grp;   /* Group containing समय zero.   */
	अचिन्हित दीर्घ		समय_zero; /* Time first element was added. */
	xfs_mru_cache_मुक्त_func_t मुक्त_func; /* Function poपूर्णांकer क्रम मुक्तing. */
	काष्ठा delayed_work	work;      /* Workqueue data क्रम reaping.   */
	अचिन्हित पूर्णांक		queued;	   /* work has been queued */
	व्योम			*data;
पूर्ण;

अटल काष्ठा workqueue_काष्ठा	*xfs_mru_reap_wq;

/*
 * When inserting, destroying or reaping, it's first necessary to update the
 * lists relative to a particular समय.  In the हाल of destroying, that समय
 * will be well in the future to ensure that all items are moved to the reap
 * list.  In all other हालs though, the समय will be the current समय.
 *
 * This function enters a loop, moving the contents of the LRU list to the reap
 * list again and again until either a) the lists are all empty, or b) समय zero
 * has been advanced sufficiently to be within the immediate element lअगरeसमय.
 *
 * Case a) above is detected by counting how many groups are migrated and
 * stopping when they've all been moved.  Case b) is detected by monitoring the
 * समय_zero field, which is updated as each group is migrated.
 *
 * The वापस value is the earliest समय that more migration could be needed, or
 * zero अगर there's no need to schedule more work because the lists are empty.
 */
STATIC अचिन्हित दीर्घ
_xfs_mru_cache_migrate(
	काष्ठा xfs_mru_cache	*mru,
	अचिन्हित दीर्घ		now)
अणु
	अचिन्हित पूर्णांक		grp;
	अचिन्हित पूर्णांक		migrated = 0;
	काष्ठा list_head	*lru_list;

	/* Nothing to करो अगर the data store is empty. */
	अगर (!mru->समय_zero)
		वापस 0;

	/* While समय zero is older than the समय spanned by all the lists. */
	जबतक (mru->समय_zero <= now - mru->grp_count * mru->grp_समय) अणु

		/*
		 * If the LRU list isn't empty, migrate its elements to the tail
		 * of the reap list.
		 */
		lru_list = mru->lists + mru->lru_grp;
		अगर (!list_empty(lru_list))
			list_splice_init(lru_list, mru->reap_list.prev);

		/*
		 * Advance the LRU group number, मुक्तing the old LRU list to
		 * become the new MRU list; advance समय zero accordingly.
		 */
		mru->lru_grp = (mru->lru_grp + 1) % mru->grp_count;
		mru->समय_zero += mru->grp_समय;

		/*
		 * If reaping is so far behind that all the elements on all the
		 * lists have been migrated to the reap list, it's now empty.
		 */
		अगर (++migrated == mru->grp_count) अणु
			mru->lru_grp = 0;
			mru->समय_zero = 0;
			वापस 0;
		पूर्ण
	पूर्ण

	/* Find the first non-empty list from the LRU end. */
	क्रम (grp = 0; grp < mru->grp_count; grp++) अणु

		/* Check the grp'th list from the LRU end. */
		lru_list = mru->lists + ((mru->lru_grp + grp) % mru->grp_count);
		अगर (!list_empty(lru_list))
			वापस mru->समय_zero +
			       (mru->grp_count + grp) * mru->grp_समय;
	पूर्ण

	/* All the lists must be empty. */
	mru->lru_grp = 0;
	mru->समय_zero = 0;
	वापस 0;
पूर्ण

/*
 * When inserting or करोing a lookup, an element needs to be inserted पूर्णांकo the
 * MRU list.  The lists must be migrated first to ensure that they're
 * up-to-date, otherwise the new element could be given a लघुer lअगरeसमय in
 * the cache than it should.
 */
STATIC व्योम
_xfs_mru_cache_list_insert(
	काष्ठा xfs_mru_cache	*mru,
	काष्ठा xfs_mru_cache_elem *elem)
अणु
	अचिन्हित पूर्णांक		grp = 0;
	अचिन्हित दीर्घ		now = jअगरfies;

	/*
	 * If the data store is empty, initialise समय zero, leave grp set to
	 * zero and start the work queue समयr अगर necessary.  Otherwise, set grp
	 * to the number of group बार that have elapsed since समय zero.
	 */
	अगर (!_xfs_mru_cache_migrate(mru, now)) अणु
		mru->समय_zero = now;
		अगर (!mru->queued) अणु
			mru->queued = 1;
			queue_delayed_work(xfs_mru_reap_wq, &mru->work,
			                   mru->grp_count * mru->grp_समय);
		पूर्ण
	पूर्ण अन्यथा अणु
		grp = (now - mru->समय_zero) / mru->grp_समय;
		grp = (mru->lru_grp + grp) % mru->grp_count;
	पूर्ण

	/* Insert the element at the tail of the corresponding list. */
	list_add_tail(&elem->list_node, mru->lists + grp);
पूर्ण

/*
 * When destroying or reaping, all the elements that were migrated to the reap
 * list need to be deleted.  For each element this involves removing it from the
 * data store, removing it from the reap list, calling the client's मुक्त
 * function and deleting the element from the element zone.
 *
 * We get called holding the mru->lock, which we drop and then reacquire.
 * Sparse need special help with this to tell it we know what we are करोing.
 */
STATIC व्योम
_xfs_mru_cache_clear_reap_list(
	काष्ठा xfs_mru_cache	*mru)
		__releases(mru->lock) __acquires(mru->lock)
अणु
	काष्ठा xfs_mru_cache_elem *elem, *next;
	काष्ठा list_head	पंचांगp;

	INIT_LIST_HEAD(&पंचांगp);
	list_क्रम_each_entry_safe(elem, next, &mru->reap_list, list_node) अणु

		/* Remove the element from the data store. */
		radix_tree_delete(&mru->store, elem->key);

		/*
		 * हटाओ to temp list so it can be मुक्तd without
		 * needing to hold the lock
		 */
		list_move(&elem->list_node, &पंचांगp);
	पूर्ण
	spin_unlock(&mru->lock);

	list_क्रम_each_entry_safe(elem, next, &पंचांगp, list_node) अणु
		list_del_init(&elem->list_node);
		mru->मुक्त_func(mru->data, elem);
	पूर्ण

	spin_lock(&mru->lock);
पूर्ण

/*
 * We fire the reap समयr every group expiry पूर्णांकerval so
 * we always have a reaper पढ़ोy to run. This makes shutकरोwn
 * and flushing of the reaper easy to करो. Hence we need to
 * keep when the next reap must occur so we can determine
 * at each पूर्णांकerval whether there is anything we need to करो.
 */
STATIC व्योम
_xfs_mru_cache_reap(
	काष्ठा work_काष्ठा	*work)
अणु
	काष्ठा xfs_mru_cache	*mru =
		container_of(work, काष्ठा xfs_mru_cache, work.work);
	अचिन्हित दीर्घ		now, next;

	ASSERT(mru && mru->lists);
	अगर (!mru || !mru->lists)
		वापस;

	spin_lock(&mru->lock);
	next = _xfs_mru_cache_migrate(mru, jअगरfies);
	_xfs_mru_cache_clear_reap_list(mru);

	mru->queued = next;
	अगर ((mru->queued > 0)) अणु
		now = jअगरfies;
		अगर (next <= now)
			next = 0;
		अन्यथा
			next -= now;
		queue_delayed_work(xfs_mru_reap_wq, &mru->work, next);
	पूर्ण

	spin_unlock(&mru->lock);
पूर्ण

पूर्णांक
xfs_mru_cache_init(व्योम)
अणु
	xfs_mru_reap_wq = alloc_workqueue("xfs_mru_cache",
			XFS_WQFLAGS(WQ_MEM_RECLAIM | WQ_FREEZABLE), 1);
	अगर (!xfs_mru_reap_wq)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम
xfs_mru_cache_uninit(व्योम)
अणु
	destroy_workqueue(xfs_mru_reap_wq);
पूर्ण

/*
 * To initialise a काष्ठा xfs_mru_cache poपूर्णांकer, call xfs_mru_cache_create()
 * with the address of the poपूर्णांकer, a lअगरeसमय value in milliseconds, a group
 * count and a मुक्त function to use when deleting elements.  This function
 * वापसs 0 अगर the initialisation was successful.
 */
पूर्णांक
xfs_mru_cache_create(
	काष्ठा xfs_mru_cache	**mrup,
	व्योम			*data,
	अचिन्हित पूर्णांक		lअगरeसमय_ms,
	अचिन्हित पूर्णांक		grp_count,
	xfs_mru_cache_मुक्त_func_t मुक्त_func)
अणु
	काष्ठा xfs_mru_cache	*mru = शून्य;
	पूर्णांक			err = 0, grp;
	अचिन्हित पूर्णांक		grp_समय;

	अगर (mrup)
		*mrup = शून्य;

	अगर (!mrup || !grp_count || !lअगरeसमय_ms || !मुक्त_func)
		वापस -EINVAL;

	अगर (!(grp_समय = msecs_to_jअगरfies(lअगरeसमय_ms) / grp_count))
		वापस -EINVAL;

	अगर (!(mru = kmem_zalloc(माप(*mru), 0)))
		वापस -ENOMEM;

	/* An extra list is needed to aव्योम reaping up to a grp_समय early. */
	mru->grp_count = grp_count + 1;
	mru->lists = kmem_zalloc(mru->grp_count * माप(*mru->lists), 0);

	अगर (!mru->lists) अणु
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण

	क्रम (grp = 0; grp < mru->grp_count; grp++)
		INIT_LIST_HEAD(mru->lists + grp);

	/*
	 * We use GFP_KERNEL radix tree preload and करो inserts under a
	 * spinlock so GFP_ATOMIC is appropriate क्रम the radix tree itself.
	 */
	INIT_RADIX_TREE(&mru->store, GFP_ATOMIC);
	INIT_LIST_HEAD(&mru->reap_list);
	spin_lock_init(&mru->lock);
	INIT_DELAYED_WORK(&mru->work, _xfs_mru_cache_reap);

	mru->grp_समय  = grp_समय;
	mru->मुक्त_func = मुक्त_func;
	mru->data = data;
	*mrup = mru;

निकास:
	अगर (err && mru && mru->lists)
		kmem_मुक्त(mru->lists);
	अगर (err && mru)
		kmem_मुक्त(mru);

	वापस err;
पूर्ण

/*
 * Call xfs_mru_cache_flush() to flush out all cached entries, calling their
 * मुक्त functions as they're deleted.  When this function वापसs, the caller is
 * guaranteed that all the मुक्त functions क्रम all the elements have finished
 * executing and the reaper is not running.
 */
अटल व्योम
xfs_mru_cache_flush(
	काष्ठा xfs_mru_cache	*mru)
अणु
	अगर (!mru || !mru->lists)
		वापस;

	spin_lock(&mru->lock);
	अगर (mru->queued) अणु
		spin_unlock(&mru->lock);
		cancel_delayed_work_sync(&mru->work);
		spin_lock(&mru->lock);
	पूर्ण

	_xfs_mru_cache_migrate(mru, jअगरfies + mru->grp_count * mru->grp_समय);
	_xfs_mru_cache_clear_reap_list(mru);

	spin_unlock(&mru->lock);
पूर्ण

व्योम
xfs_mru_cache_destroy(
	काष्ठा xfs_mru_cache	*mru)
अणु
	अगर (!mru || !mru->lists)
		वापस;

	xfs_mru_cache_flush(mru);

	kmem_मुक्त(mru->lists);
	kmem_मुक्त(mru);
पूर्ण

/*
 * To insert an element, call xfs_mru_cache_insert() with the data store, the
 * element's key and the client data poपूर्णांकer.  This function वापसs 0 on
 * success or ENOMEM अगर memory क्रम the data element couldn't be allocated.
 */
पूर्णांक
xfs_mru_cache_insert(
	काष्ठा xfs_mru_cache	*mru,
	अचिन्हित दीर्घ		key,
	काष्ठा xfs_mru_cache_elem *elem)
अणु
	पूर्णांक			error;

	ASSERT(mru && mru->lists);
	अगर (!mru || !mru->lists)
		वापस -EINVAL;

	अगर (radix_tree_preload(GFP_NOFS))
		वापस -ENOMEM;

	INIT_LIST_HEAD(&elem->list_node);
	elem->key = key;

	spin_lock(&mru->lock);
	error = radix_tree_insert(&mru->store, key, elem);
	radix_tree_preload_end();
	अगर (!error)
		_xfs_mru_cache_list_insert(mru, elem);
	spin_unlock(&mru->lock);

	वापस error;
पूर्ण

/*
 * To हटाओ an element without calling the मुक्त function, call
 * xfs_mru_cache_हटाओ() with the data store and the element's key.  On success
 * the client data poपूर्णांकer क्रम the हटाओd element is वापसed, otherwise this
 * function will वापस a शून्य poपूर्णांकer.
 */
काष्ठा xfs_mru_cache_elem *
xfs_mru_cache_हटाओ(
	काष्ठा xfs_mru_cache	*mru,
	अचिन्हित दीर्घ		key)
अणु
	काष्ठा xfs_mru_cache_elem *elem;

	ASSERT(mru && mru->lists);
	अगर (!mru || !mru->lists)
		वापस शून्य;

	spin_lock(&mru->lock);
	elem = radix_tree_delete(&mru->store, key);
	अगर (elem)
		list_del(&elem->list_node);
	spin_unlock(&mru->lock);

	वापस elem;
पूर्ण

/*
 * To हटाओ and element and call the मुक्त function, call xfs_mru_cache_delete()
 * with the data store and the element's key.
 */
व्योम
xfs_mru_cache_delete(
	काष्ठा xfs_mru_cache	*mru,
	अचिन्हित दीर्घ		key)
अणु
	काष्ठा xfs_mru_cache_elem *elem;

	elem = xfs_mru_cache_हटाओ(mru, key);
	अगर (elem)
		mru->मुक्त_func(mru->data, elem);
पूर्ण

/*
 * To look up an element using its key, call xfs_mru_cache_lookup() with the
 * data store and the element's key.  If found, the element will be moved to the
 * head of the MRU list to indicate that it's been touched.
 *
 * The पूर्णांकernal data काष्ठाures are रक्षित by a spinlock that is STILL HELD
 * when this function वापसs.  Call xfs_mru_cache_करोne() to release it.  Note
 * that it is not safe to call any function that might sleep in the पूर्णांकerim.
 *
 * The implementation could have used reference counting to aव्योम this
 * restriction, but since most clients simply want to get, set or test a member
 * of the वापसed data काष्ठाure, the extra per-element memory isn't warranted.
 *
 * If the element isn't found, this function वापसs शून्य and the spinlock is
 * released.  xfs_mru_cache_करोne() should NOT be called when this occurs.
 *
 * Because sparse isn't smart enough to know about conditional lock वापस
 * status, we need to help it get it right by annotating the path that करोes
 * not release the lock.
 */
काष्ठा xfs_mru_cache_elem *
xfs_mru_cache_lookup(
	काष्ठा xfs_mru_cache	*mru,
	अचिन्हित दीर्घ		key)
अणु
	काष्ठा xfs_mru_cache_elem *elem;

	ASSERT(mru && mru->lists);
	अगर (!mru || !mru->lists)
		वापस शून्य;

	spin_lock(&mru->lock);
	elem = radix_tree_lookup(&mru->store, key);
	अगर (elem) अणु
		list_del(&elem->list_node);
		_xfs_mru_cache_list_insert(mru, elem);
		__release(mru_lock); /* help sparse not be stupid */
	पूर्ण अन्यथा
		spin_unlock(&mru->lock);

	वापस elem;
पूर्ण

/*
 * To release the पूर्णांकernal data काष्ठाure spinlock after having perक्रमmed an
 * xfs_mru_cache_lookup() or an xfs_mru_cache_peek(), call xfs_mru_cache_करोne()
 * with the data store poपूर्णांकer.
 */
व्योम
xfs_mru_cache_करोne(
	काष्ठा xfs_mru_cache	*mru)
		__releases(mru->lock)
अणु
	spin_unlock(&mru->lock);
पूर्ण
