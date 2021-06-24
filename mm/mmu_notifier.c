<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/mm/mmu_notअगरier.c
 *
 *  Copyright (C) 2008  Qumranet, Inc.
 *  Copyright (C) 2008  SGI
 *             Christoph Lameter <cl@linux.com>
 */

#समावेश <linux/rculist.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerval_tree.h>
#समावेश <linux/srcu.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/slab.h>

/* global SRCU क्रम all MMs */
DEFINE_STATIC_SRCU(srcu);

#अगर_घोषित CONFIG_LOCKDEP
काष्ठा lockdep_map __mmu_notअगरier_invalidate_range_start_map = अणु
	.name = "mmu_notifier_invalidate_range_start"
पूर्ण;
#पूर्ण_अगर

/*
 * The mmu_notअगरier_subscriptions काष्ठाure is allocated and installed in
 * mm->notअगरier_subscriptions inside the mm_take_all_locks() रक्षित
 * critical section and it's released only when mm_count reaches zero
 * in mmdrop().
 */
काष्ठा mmu_notअगरier_subscriptions अणु
	/* all mmu notअगरiers रेजिस्टरed in this mm are queued in this list */
	काष्ठा hlist_head list;
	bool has_itree;
	/* to serialize the list modअगरications and hlist_unhashed */
	spinlock_t lock;
	अचिन्हित दीर्घ invalidate_seq;
	अचिन्हित दीर्घ active_invalidate_ranges;
	काष्ठा rb_root_cached itree;
	रुको_queue_head_t wq;
	काष्ठा hlist_head deferred_list;
पूर्ण;

/*
 * This is a collision-retry पढ़ो-side/ग_लिखो-side 'lock', a lot like a
 * seqcount, however this allows multiple ग_लिखो-sides to hold it at
 * once. Conceptually the ग_लिखो side is protecting the values of the PTEs in
 * this mm, such that PTES cannot be पढ़ो पूर्णांकo SPTEs (shaकरोw PTEs) जबतक any
 * ग_लिखोr exists.
 *
 * Note that the core mm creates nested invalidate_range_start()/end() regions
 * within the same thपढ़ो, and runs invalidate_range_start()/end() in parallel
 * on multiple CPUs. This is deचिन्हित to not reduce concurrency or block
 * progress on the mm side.
 *
 * As a secondary function, holding the full ग_लिखो side also serves to prevent
 * ग_लिखोrs क्रम the itree, this is an optimization to aव्योम extra locking
 * during invalidate_range_start/end notअगरiers.
 *
 * The ग_लिखो side has two states, fully excluded:
 *  - mm->active_invalidate_ranges != 0
 *  - subscriptions->invalidate_seq & 1 == True (odd)
 *  - some range on the mm_काष्ठा is being invalidated
 *  - the itree is not allowed to change
 *
 * And partially excluded:
 *  - mm->active_invalidate_ranges != 0
 *  - subscriptions->invalidate_seq & 1 == False (even)
 *  - some range on the mm_काष्ठा is being invalidated
 *  - the itree is allowed to change
 *
 * Operations on notअगरier_subscriptions->invalidate_seq (under spinlock):
 *    seq |= 1  # Begin writing
 *    seq++     # Release the writing state
 *    seq & 1   # True अगर a ग_लिखोr exists
 *
 * The later state aव्योमs some expensive work on inv_end in the common हाल of
 * no mmu_पूर्णांकerval_notअगरier monitoring the VA.
 */
अटल bool
mn_itree_is_invalidating(काष्ठा mmu_notअगरier_subscriptions *subscriptions)
अणु
	lockdep_निश्चित_held(&subscriptions->lock);
	वापस subscriptions->invalidate_seq & 1;
पूर्ण

अटल काष्ठा mmu_पूर्णांकerval_notअगरier *
mn_itree_inv_start_range(काष्ठा mmu_notअगरier_subscriptions *subscriptions,
			 स्थिर काष्ठा mmu_notअगरier_range *range,
			 अचिन्हित दीर्घ *seq)
अणु
	काष्ठा पूर्णांकerval_tree_node *node;
	काष्ठा mmu_पूर्णांकerval_notअगरier *res = शून्य;

	spin_lock(&subscriptions->lock);
	subscriptions->active_invalidate_ranges++;
	node = पूर्णांकerval_tree_iter_first(&subscriptions->itree, range->start,
					range->end - 1);
	अगर (node) अणु
		subscriptions->invalidate_seq |= 1;
		res = container_of(node, काष्ठा mmu_पूर्णांकerval_notअगरier,
				   पूर्णांकerval_tree);
	पूर्ण

	*seq = subscriptions->invalidate_seq;
	spin_unlock(&subscriptions->lock);
	वापस res;
पूर्ण

अटल काष्ठा mmu_पूर्णांकerval_notअगरier *
mn_itree_inv_next(काष्ठा mmu_पूर्णांकerval_notअगरier *पूर्णांकerval_sub,
		  स्थिर काष्ठा mmu_notअगरier_range *range)
अणु
	काष्ठा पूर्णांकerval_tree_node *node;

	node = पूर्णांकerval_tree_iter_next(&पूर्णांकerval_sub->पूर्णांकerval_tree,
				       range->start, range->end - 1);
	अगर (!node)
		वापस शून्य;
	वापस container_of(node, काष्ठा mmu_पूर्णांकerval_notअगरier, पूर्णांकerval_tree);
पूर्ण

अटल व्योम mn_itree_inv_end(काष्ठा mmu_notअगरier_subscriptions *subscriptions)
अणु
	काष्ठा mmu_पूर्णांकerval_notअगरier *पूर्णांकerval_sub;
	काष्ठा hlist_node *next;

	spin_lock(&subscriptions->lock);
	अगर (--subscriptions->active_invalidate_ranges ||
	    !mn_itree_is_invalidating(subscriptions)) अणु
		spin_unlock(&subscriptions->lock);
		वापस;
	पूर्ण

	/* Make invalidate_seq even */
	subscriptions->invalidate_seq++;

	/*
	 * The inv_end incorporates a deferred mechanism like rtnl_unlock().
	 * Adds and हटाओs are queued until the final inv_end happens then
	 * they are progressed. This arrangement क्रम tree updates is used to
	 * aव्योम using a blocking lock during invalidate_range_start.
	 */
	hlist_क्रम_each_entry_safe(पूर्णांकerval_sub, next,
				  &subscriptions->deferred_list,
				  deferred_item) अणु
		अगर (RB_EMPTY_NODE(&पूर्णांकerval_sub->पूर्णांकerval_tree.rb))
			पूर्णांकerval_tree_insert(&पूर्णांकerval_sub->पूर्णांकerval_tree,
					     &subscriptions->itree);
		अन्यथा
			पूर्णांकerval_tree_हटाओ(&पूर्णांकerval_sub->पूर्णांकerval_tree,
					     &subscriptions->itree);
		hlist_del(&पूर्णांकerval_sub->deferred_item);
	पूर्ण
	spin_unlock(&subscriptions->lock);

	wake_up_all(&subscriptions->wq);
पूर्ण

/**
 * mmu_पूर्णांकerval_पढ़ो_begin - Begin a पढ़ो side critical section against a VA
 *                           range
 * @पूर्णांकerval_sub: The पूर्णांकerval subscription
 *
 * mmu_iterval_पढ़ो_begin()/mmu_iterval_पढ़ो_retry() implement a
 * collision-retry scheme similar to seqcount क्रम the VA range under
 * subscription. If the mm invokes invalidation during the critical section
 * then mmu_पूर्णांकerval_पढ़ो_retry() will वापस true.
 *
 * This is useful to obtain shaकरोw PTEs where tearकरोwn or setup of the SPTEs
 * require a blocking context.  The critical region क्रमmed by this can sleep,
 * and the required 'user_lock' can also be a sleeping lock.
 *
 * The caller is required to provide a 'user_lock' to serialize both tearकरोwn
 * and setup.
 *
 * The वापस value should be passed to mmu_पूर्णांकerval_पढ़ो_retry().
 */
अचिन्हित दीर्घ
mmu_पूर्णांकerval_पढ़ो_begin(काष्ठा mmu_पूर्णांकerval_notअगरier *पूर्णांकerval_sub)
अणु
	काष्ठा mmu_notअगरier_subscriptions *subscriptions =
		पूर्णांकerval_sub->mm->notअगरier_subscriptions;
	अचिन्हित दीर्घ seq;
	bool is_invalidating;

	/*
	 * If the subscription has a dअगरferent seq value under the user_lock
	 * than we started with then it has collided.
	 *
	 * If the subscription currently has the same seq value as the
	 * subscriptions seq, then it is currently between
	 * invalidate_start/end and is colliding.
	 *
	 * The locking looks broadly like this:
	 *   mn_tree_invalidate_start():          mmu_पूर्णांकerval_पढ़ो_begin():
	 *                                         spin_lock
	 *                                          seq = READ_ONCE(पूर्णांकerval_sub->invalidate_seq);
	 *                                          seq == subs->invalidate_seq
	 *                                         spin_unlock
	 *    spin_lock
	 *     seq = ++subscriptions->invalidate_seq
	 *    spin_unlock
	 *     op->invalidate_range():
	 *       user_lock
	 *        mmu_पूर्णांकerval_set_seq()
	 *         पूर्णांकerval_sub->invalidate_seq = seq
	 *       user_unlock
	 *
	 *                          [Required: mmu_पूर्णांकerval_पढ़ो_retry() == true]
	 *
	 *   mn_itree_inv_end():
	 *    spin_lock
	 *     seq = ++subscriptions->invalidate_seq
	 *    spin_unlock
	 *
	 *                                        user_lock
	 *                                         mmu_पूर्णांकerval_पढ़ो_retry():
	 *                                          पूर्णांकerval_sub->invalidate_seq != seq
	 *                                        user_unlock
	 *
	 * Barriers are not needed here as any races here are बंदd by an
	 * eventual mmu_पूर्णांकerval_पढ़ो_retry(), which provides a barrier via the
	 * user_lock.
	 */
	spin_lock(&subscriptions->lock);
	/* Pairs with the WRITE_ONCE in mmu_पूर्णांकerval_set_seq() */
	seq = READ_ONCE(पूर्णांकerval_sub->invalidate_seq);
	is_invalidating = seq == subscriptions->invalidate_seq;
	spin_unlock(&subscriptions->lock);

	/*
	 * पूर्णांकerval_sub->invalidate_seq must always be set to an odd value via
	 * mmu_पूर्णांकerval_set_seq() using the provided cur_seq from
	 * mn_itree_inv_start_range(). This ensures that अगर seq करोes wrap we
	 * will always clear the below sleep in some reasonable समय as
	 * subscriptions->invalidate_seq is even in the idle state.
	 */
	lock_map_acquire(&__mmu_notअगरier_invalidate_range_start_map);
	lock_map_release(&__mmu_notअगरier_invalidate_range_start_map);
	अगर (is_invalidating)
		रुको_event(subscriptions->wq,
			   READ_ONCE(subscriptions->invalidate_seq) != seq);

	/*
	 * Notice that mmu_पूर्णांकerval_पढ़ो_retry() can alपढ़ोy be true at this
	 * poपूर्णांक, aव्योमing loops here allows the caller to provide a global
	 * समय bound.
	 */

	वापस seq;
पूर्ण
EXPORT_SYMBOL_GPL(mmu_पूर्णांकerval_पढ़ो_begin);

अटल व्योम mn_itree_release(काष्ठा mmu_notअगरier_subscriptions *subscriptions,
			     काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा mmu_notअगरier_range range = अणु
		.flags = MMU_NOTIFIER_RANGE_BLOCKABLE,
		.event = MMU_NOTIFY_RELEASE,
		.mm = mm,
		.start = 0,
		.end = अच_दीर्घ_उच्च,
	पूर्ण;
	काष्ठा mmu_पूर्णांकerval_notअगरier *पूर्णांकerval_sub;
	अचिन्हित दीर्घ cur_seq;
	bool ret;

	क्रम (पूर्णांकerval_sub =
		     mn_itree_inv_start_range(subscriptions, &range, &cur_seq);
	     पूर्णांकerval_sub;
	     पूर्णांकerval_sub = mn_itree_inv_next(पूर्णांकerval_sub, &range)) अणु
		ret = पूर्णांकerval_sub->ops->invalidate(पूर्णांकerval_sub, &range,
						    cur_seq);
		WARN_ON(!ret);
	पूर्ण

	mn_itree_inv_end(subscriptions);
पूर्ण

/*
 * This function can't run concurrently against mmu_notअगरier_रेजिस्टर
 * because mm->mm_users > 0 during mmu_notअगरier_रेजिस्टर and निकास_mmap
 * runs with mm_users == 0. Other tasks may still invoke mmu notअगरiers
 * in parallel despite there being no task using this mm any more,
 * through the vmas outside of the निकास_mmap context, such as with
 * vmtruncate. This serializes against mmu_notअगरier_unरेजिस्टर with
 * the notअगरier_subscriptions->lock in addition to SRCU and it serializes
 * against the other mmu notअगरiers with SRCU. काष्ठा mmu_notअगरier_subscriptions
 * can't go away from under us as निकास_mmap holds an mm_count pin
 * itself.
 */
अटल व्योम mn_hlist_release(काष्ठा mmu_notअगरier_subscriptions *subscriptions,
			     काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा mmu_notअगरier *subscription;
	पूर्णांक id;

	/*
	 * SRCU here will block mmu_notअगरier_unरेजिस्टर until
	 * ->release वापसs.
	 */
	id = srcu_पढ़ो_lock(&srcu);
	hlist_क्रम_each_entry_rcu(subscription, &subscriptions->list, hlist,
				 srcu_पढ़ो_lock_held(&srcu))
		/*
		 * If ->release runs beक्रमe mmu_notअगरier_unरेजिस्टर it must be
		 * handled, as it's the only way क्रम the driver to flush all
		 * existing sptes and stop the driver from establishing any more
		 * sptes beक्रमe all the pages in the mm are मुक्तd.
		 */
		अगर (subscription->ops->release)
			subscription->ops->release(subscription, mm);

	spin_lock(&subscriptions->lock);
	जबतक (unlikely(!hlist_empty(&subscriptions->list))) अणु
		subscription = hlist_entry(subscriptions->list.first,
					   काष्ठा mmu_notअगरier, hlist);
		/*
		 * We arrived beक्रमe mmu_notअगरier_unरेजिस्टर so
		 * mmu_notअगरier_unरेजिस्टर will करो nothing other than to रुको
		 * क्रम ->release to finish and क्रम mmu_notअगरier_unरेजिस्टर to
		 * वापस.
		 */
		hlist_del_init_rcu(&subscription->hlist);
	पूर्ण
	spin_unlock(&subscriptions->lock);
	srcu_पढ़ो_unlock(&srcu, id);

	/*
	 * synchronize_srcu here prevents mmu_notअगरier_release from वापसing to
	 * निकास_mmap (which would proceed with मुक्तing all pages in the mm)
	 * until the ->release method वापसs, अगर it was invoked by
	 * mmu_notअगरier_unरेजिस्टर.
	 *
	 * The notअगरier_subscriptions can't go away from under us because
	 * one mm_count is held by निकास_mmap.
	 */
	synchronize_srcu(&srcu);
पूर्ण

व्योम __mmu_notअगरier_release(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा mmu_notअगरier_subscriptions *subscriptions =
		mm->notअगरier_subscriptions;

	अगर (subscriptions->has_itree)
		mn_itree_release(subscriptions, mm);

	अगर (!hlist_empty(&subscriptions->list))
		mn_hlist_release(subscriptions, mm);
पूर्ण

/*
 * If no young bitflag is supported by the hardware, ->clear_flush_young can
 * unmap the address and वापस 1 or 0 depending अगर the mapping previously
 * existed or not.
 */
पूर्णांक __mmu_notअगरier_clear_flush_young(काष्ठा mm_काष्ठा *mm,
					अचिन्हित दीर्घ start,
					अचिन्हित दीर्घ end)
अणु
	काष्ठा mmu_notअगरier *subscription;
	पूर्णांक young = 0, id;

	id = srcu_पढ़ो_lock(&srcu);
	hlist_क्रम_each_entry_rcu(subscription,
				 &mm->notअगरier_subscriptions->list, hlist,
				 srcu_पढ़ो_lock_held(&srcu)) अणु
		अगर (subscription->ops->clear_flush_young)
			young |= subscription->ops->clear_flush_young(
				subscription, mm, start, end);
	पूर्ण
	srcu_पढ़ो_unlock(&srcu, id);

	वापस young;
पूर्ण

पूर्णांक __mmu_notअगरier_clear_young(काष्ठा mm_काष्ठा *mm,
			       अचिन्हित दीर्घ start,
			       अचिन्हित दीर्घ end)
अणु
	काष्ठा mmu_notअगरier *subscription;
	पूर्णांक young = 0, id;

	id = srcu_पढ़ो_lock(&srcu);
	hlist_क्रम_each_entry_rcu(subscription,
				 &mm->notअगरier_subscriptions->list, hlist,
				 srcu_पढ़ो_lock_held(&srcu)) अणु
		अगर (subscription->ops->clear_young)
			young |= subscription->ops->clear_young(subscription,
								mm, start, end);
	पूर्ण
	srcu_पढ़ो_unlock(&srcu, id);

	वापस young;
पूर्ण

पूर्णांक __mmu_notअगरier_test_young(काष्ठा mm_काष्ठा *mm,
			      अचिन्हित दीर्घ address)
अणु
	काष्ठा mmu_notअगरier *subscription;
	पूर्णांक young = 0, id;

	id = srcu_पढ़ो_lock(&srcu);
	hlist_क्रम_each_entry_rcu(subscription,
				 &mm->notअगरier_subscriptions->list, hlist,
				 srcu_पढ़ो_lock_held(&srcu)) अणु
		अगर (subscription->ops->test_young) अणु
			young = subscription->ops->test_young(subscription, mm,
							      address);
			अगर (young)
				अवरोध;
		पूर्ण
	पूर्ण
	srcu_पढ़ो_unlock(&srcu, id);

	वापस young;
पूर्ण

व्योम __mmu_notअगरier_change_pte(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address,
			       pte_t pte)
अणु
	काष्ठा mmu_notअगरier *subscription;
	पूर्णांक id;

	id = srcu_पढ़ो_lock(&srcu);
	hlist_क्रम_each_entry_rcu(subscription,
				 &mm->notअगरier_subscriptions->list, hlist,
				 srcu_पढ़ो_lock_held(&srcu)) अणु
		अगर (subscription->ops->change_pte)
			subscription->ops->change_pte(subscription, mm, address,
						      pte);
	पूर्ण
	srcu_पढ़ो_unlock(&srcu, id);
पूर्ण

अटल पूर्णांक mn_itree_invalidate(काष्ठा mmu_notअगरier_subscriptions *subscriptions,
			       स्थिर काष्ठा mmu_notअगरier_range *range)
अणु
	काष्ठा mmu_पूर्णांकerval_notअगरier *पूर्णांकerval_sub;
	अचिन्हित दीर्घ cur_seq;

	क्रम (पूर्णांकerval_sub =
		     mn_itree_inv_start_range(subscriptions, range, &cur_seq);
	     पूर्णांकerval_sub;
	     पूर्णांकerval_sub = mn_itree_inv_next(पूर्णांकerval_sub, range)) अणु
		bool ret;

		ret = पूर्णांकerval_sub->ops->invalidate(पूर्णांकerval_sub, range,
						    cur_seq);
		अगर (!ret) अणु
			अगर (WARN_ON(mmu_notअगरier_range_blockable(range)))
				जारी;
			जाओ out_would_block;
		पूर्ण
	पूर्ण
	वापस 0;

out_would_block:
	/*
	 * On -EAGAIN the non-blocking caller is not allowed to call
	 * invalidate_range_end()
	 */
	mn_itree_inv_end(subscriptions);
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक mn_hlist_invalidate_range_start(
	काष्ठा mmu_notअगरier_subscriptions *subscriptions,
	काष्ठा mmu_notअगरier_range *range)
अणु
	काष्ठा mmu_notअगरier *subscription;
	पूर्णांक ret = 0;
	पूर्णांक id;

	id = srcu_पढ़ो_lock(&srcu);
	hlist_क्रम_each_entry_rcu(subscription, &subscriptions->list, hlist,
				 srcu_पढ़ो_lock_held(&srcu)) अणु
		स्थिर काष्ठा mmu_notअगरier_ops *ops = subscription->ops;

		अगर (ops->invalidate_range_start) अणु
			पूर्णांक _ret;

			अगर (!mmu_notअगरier_range_blockable(range))
				non_block_start();
			_ret = ops->invalidate_range_start(subscription, range);
			अगर (!mmu_notअगरier_range_blockable(range))
				non_block_end();
			अगर (_ret) अणु
				pr_info("%pS callback failed with %d in %sblockable context.\n",
					ops->invalidate_range_start, _ret,
					!mmu_notअगरier_range_blockable(range) ?
						"non-" :
						"");
				WARN_ON(mmu_notअगरier_range_blockable(range) ||
					_ret != -EAGAIN);
				/*
				 * We call all the notअगरiers on any EAGAIN,
				 * there is no way क्रम a notअगरier to know अगर
				 * its start method failed, thus a start that
				 * करोes EAGAIN can't also करो end.
				 */
				WARN_ON(ops->invalidate_range_end);
				ret = _ret;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ret) अणु
		/*
		 * Must be non-blocking to get here.  If there are multiple
		 * notअगरiers and one or more failed start, any that succeeded
		 * start are expecting their end to be called.  Do so now.
		 */
		hlist_क्रम_each_entry_rcu(subscription, &subscriptions->list,
					 hlist, srcu_पढ़ो_lock_held(&srcu)) अणु
			अगर (!subscription->ops->invalidate_range_end)
				जारी;

			subscription->ops->invalidate_range_end(subscription,
								range);
		पूर्ण
	पूर्ण
	srcu_पढ़ो_unlock(&srcu, id);

	वापस ret;
पूर्ण

पूर्णांक __mmu_notअगरier_invalidate_range_start(काष्ठा mmu_notअगरier_range *range)
अणु
	काष्ठा mmu_notअगरier_subscriptions *subscriptions =
		range->mm->notअगरier_subscriptions;
	पूर्णांक ret;

	अगर (subscriptions->has_itree) अणु
		ret = mn_itree_invalidate(subscriptions, range);
		अगर (ret)
			वापस ret;
	पूर्ण
	अगर (!hlist_empty(&subscriptions->list))
		वापस mn_hlist_invalidate_range_start(subscriptions, range);
	वापस 0;
पूर्ण

अटल व्योम
mn_hlist_invalidate_end(काष्ठा mmu_notअगरier_subscriptions *subscriptions,
			काष्ठा mmu_notअगरier_range *range, bool only_end)
अणु
	काष्ठा mmu_notअगरier *subscription;
	पूर्णांक id;

	id = srcu_पढ़ो_lock(&srcu);
	hlist_क्रम_each_entry_rcu(subscription, &subscriptions->list, hlist,
				 srcu_पढ़ो_lock_held(&srcu)) अणु
		/*
		 * Call invalidate_range here too to aव्योम the need क्रम the
		 * subप्रणाली of having to रेजिस्टर an invalidate_range_end
		 * call-back when there is invalidate_range alपढ़ोy. Usually a
		 * subप्रणाली रेजिस्टरs either invalidate_range_start()/end() or
		 * invalidate_range(), so this will be no additional overhead
		 * (besides the poपूर्णांकer check).
		 *
		 * We skip call to invalidate_range() अगर we know it is safe ie
		 * call site use mmu_notअगरier_invalidate_range_only_end() which
		 * is safe to करो when we know that a call to invalidate_range()
		 * alपढ़ोy happen under page table lock.
		 */
		अगर (!only_end && subscription->ops->invalidate_range)
			subscription->ops->invalidate_range(subscription,
							    range->mm,
							    range->start,
							    range->end);
		अगर (subscription->ops->invalidate_range_end) अणु
			अगर (!mmu_notअगरier_range_blockable(range))
				non_block_start();
			subscription->ops->invalidate_range_end(subscription,
								range);
			अगर (!mmu_notअगरier_range_blockable(range))
				non_block_end();
		पूर्ण
	पूर्ण
	srcu_पढ़ो_unlock(&srcu, id);
पूर्ण

व्योम __mmu_notअगरier_invalidate_range_end(काष्ठा mmu_notअगरier_range *range,
					 bool only_end)
अणु
	काष्ठा mmu_notअगरier_subscriptions *subscriptions =
		range->mm->notअगरier_subscriptions;

	lock_map_acquire(&__mmu_notअगरier_invalidate_range_start_map);
	अगर (subscriptions->has_itree)
		mn_itree_inv_end(subscriptions);

	अगर (!hlist_empty(&subscriptions->list))
		mn_hlist_invalidate_end(subscriptions, range, only_end);
	lock_map_release(&__mmu_notअगरier_invalidate_range_start_map);
पूर्ण

व्योम __mmu_notअगरier_invalidate_range(काष्ठा mm_काष्ठा *mm,
				  अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	काष्ठा mmu_notअगरier *subscription;
	पूर्णांक id;

	id = srcu_पढ़ो_lock(&srcu);
	hlist_क्रम_each_entry_rcu(subscription,
				 &mm->notअगरier_subscriptions->list, hlist,
				 srcu_पढ़ो_lock_held(&srcu)) अणु
		अगर (subscription->ops->invalidate_range)
			subscription->ops->invalidate_range(subscription, mm,
							    start, end);
	पूर्ण
	srcu_पढ़ो_unlock(&srcu, id);
पूर्ण

/*
 * Same as mmu_notअगरier_रेजिस्टर but here the caller must hold the mmap_lock in
 * ग_लिखो mode. A शून्य mn संकेतs the notअगरier is being रेजिस्टरed क्रम itree
 * mode.
 */
पूर्णांक __mmu_notअगरier_रेजिस्टर(काष्ठा mmu_notअगरier *subscription,
			    काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा mmu_notअगरier_subscriptions *subscriptions = शून्य;
	पूर्णांक ret;

	mmap_निश्चित_ग_लिखो_locked(mm);
	BUG_ON(atomic_पढ़ो(&mm->mm_users) <= 0);

	अगर (!mm->notअगरier_subscriptions) अणु
		/*
		 * kदो_स्मृति cannot be called under mm_take_all_locks(), but we
		 * know that mm->notअगरier_subscriptions can't change जबतक we
		 * hold the ग_लिखो side of the mmap_lock.
		 */
		subscriptions = kzalloc(
			माप(काष्ठा mmu_notअगरier_subscriptions), GFP_KERNEL);
		अगर (!subscriptions)
			वापस -ENOMEM;

		INIT_HLIST_HEAD(&subscriptions->list);
		spin_lock_init(&subscriptions->lock);
		subscriptions->invalidate_seq = 2;
		subscriptions->itree = RB_ROOT_CACHED;
		init_रुकोqueue_head(&subscriptions->wq);
		INIT_HLIST_HEAD(&subscriptions->deferred_list);
	पूर्ण

	ret = mm_take_all_locks(mm);
	अगर (unlikely(ret))
		जाओ out_clean;

	/*
	 * Serialize the update against mmu_notअगरier_unरेजिस्टर. A
	 * side note: mmu_notअगरier_release can't run concurrently with
	 * us because we hold the mm_users pin (either implicitly as
	 * current->mm or explicitly with get_task_mm() or similar).
	 * We can't race against any other mmu notअगरier method either
	 * thanks to mm_take_all_locks().
	 *
	 * release semantics on the initialization of the
	 * mmu_notअगरier_subscriptions's contents are provided क्रम unlocked
	 * पढ़ोers.  acquire can only be used जबतक holding the mmgrab or
	 * mmget, and is safe because once created the
	 * mmu_notअगरier_subscriptions is not मुक्तd until the mm is destroyed.
	 * As above, users holding the mmap_lock or one of the
	 * mm_take_all_locks() करो not need to use acquire semantics.
	 */
	अगर (subscriptions)
		smp_store_release(&mm->notअगरier_subscriptions, subscriptions);

	अगर (subscription) अणु
		/* Pairs with the mmdrop in mmu_notअगरier_unरेजिस्टर_* */
		mmgrab(mm);
		subscription->mm = mm;
		subscription->users = 1;

		spin_lock(&mm->notअगरier_subscriptions->lock);
		hlist_add_head_rcu(&subscription->hlist,
				   &mm->notअगरier_subscriptions->list);
		spin_unlock(&mm->notअगरier_subscriptions->lock);
	पूर्ण अन्यथा
		mm->notअगरier_subscriptions->has_itree = true;

	mm_drop_all_locks(mm);
	BUG_ON(atomic_पढ़ो(&mm->mm_users) <= 0);
	वापस 0;

out_clean:
	kमुक्त(subscriptions);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__mmu_notअगरier_रेजिस्टर);

/**
 * mmu_notअगरier_रेजिस्टर - Register a notअगरier on a mm
 * @subscription: The notअगरier to attach
 * @mm: The mm to attach the notअगरier to
 *
 * Must not hold mmap_lock nor any other VM related lock when calling
 * this registration function. Must also ensure mm_users can't go करोwn
 * to zero जबतक this runs to aव्योम races with mmu_notअगरier_release,
 * so mm has to be current->mm or the mm should be pinned safely such
 * as with get_task_mm(). If the mm is not current->mm, the mm_users
 * pin should be released by calling mmput after mmu_notअगरier_रेजिस्टर
 * वापसs.
 *
 * mmu_notअगरier_unरेजिस्टर() or mmu_notअगरier_put() must be always called to
 * unरेजिस्टर the notअगरier.
 *
 * While the caller has a mmu_notअगरier get the subscription->mm poपूर्णांकer will reमुख्य
 * valid, and can be converted to an active mm poपूर्णांकer via mmget_not_zero().
 */
पूर्णांक mmu_notअगरier_रेजिस्टर(काष्ठा mmu_notअगरier *subscription,
			  काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक ret;

	mmap_ग_लिखो_lock(mm);
	ret = __mmu_notअगरier_रेजिस्टर(subscription, mm);
	mmap_ग_लिखो_unlock(mm);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mmu_notअगरier_रेजिस्टर);

अटल काष्ठा mmu_notअगरier *
find_get_mmu_notअगरier(काष्ठा mm_काष्ठा *mm, स्थिर काष्ठा mmu_notअगरier_ops *ops)
अणु
	काष्ठा mmu_notअगरier *subscription;

	spin_lock(&mm->notअगरier_subscriptions->lock);
	hlist_क्रम_each_entry_rcu(subscription,
				 &mm->notअगरier_subscriptions->list, hlist,
				 lockdep_is_held(&mm->notअगरier_subscriptions->lock)) अणु
		अगर (subscription->ops != ops)
			जारी;

		अगर (likely(subscription->users != अच_पूर्णांक_उच्च))
			subscription->users++;
		अन्यथा
			subscription = ERR_PTR(-EOVERFLOW);
		spin_unlock(&mm->notअगरier_subscriptions->lock);
		वापस subscription;
	पूर्ण
	spin_unlock(&mm->notअगरier_subscriptions->lock);
	वापस शून्य;
पूर्ण

/**
 * mmu_notअगरier_get_locked - Return the single काष्ठा mmu_notअगरier क्रम
 *                           the mm & ops
 * @ops: The operations काष्ठा being subscribe with
 * @mm : The mm to attach notअगरiers too
 *
 * This function either allocates a new mmu_notअगरier via
 * ops->alloc_notअगरier(), or वापसs an alपढ़ोy existing notअगरier on the
 * list. The value of the ops poपूर्णांकer is used to determine when two notअगरiers
 * are the same.
 *
 * Each call to mmu_notअगरier_get() must be paired with a call to
 * mmu_notअगरier_put(). The caller must hold the ग_लिखो side of mm->mmap_lock.
 *
 * While the caller has a mmu_notअगरier get the mm poपूर्णांकer will reमुख्य valid,
 * and can be converted to an active mm poपूर्णांकer via mmget_not_zero().
 */
काष्ठा mmu_notअगरier *mmu_notअगरier_get_locked(स्थिर काष्ठा mmu_notअगरier_ops *ops,
					     काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा mmu_notअगरier *subscription;
	पूर्णांक ret;

	mmap_निश्चित_ग_लिखो_locked(mm);

	अगर (mm->notअगरier_subscriptions) अणु
		subscription = find_get_mmu_notअगरier(mm, ops);
		अगर (subscription)
			वापस subscription;
	पूर्ण

	subscription = ops->alloc_notअगरier(mm);
	अगर (IS_ERR(subscription))
		वापस subscription;
	subscription->ops = ops;
	ret = __mmu_notअगरier_रेजिस्टर(subscription, mm);
	अगर (ret)
		जाओ out_मुक्त;
	वापस subscription;
out_मुक्त:
	subscription->ops->मुक्त_notअगरier(subscription);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(mmu_notअगरier_get_locked);

/* this is called after the last mmu_notअगरier_unरेजिस्टर() वापसed */
व्योम __mmu_notअगरier_subscriptions_destroy(काष्ठा mm_काष्ठा *mm)
अणु
	BUG_ON(!hlist_empty(&mm->notअगरier_subscriptions->list));
	kमुक्त(mm->notअगरier_subscriptions);
	mm->notअगरier_subscriptions = LIST_POISON1; /* debug */
पूर्ण

/*
 * This releases the mm_count pin स्वतःmatically and मुक्तs the mm
 * काष्ठाure अगर it was the last user of it. It serializes against
 * running mmu notअगरiers with SRCU and against mmu_notअगरier_unरेजिस्टर
 * with the unरेजिस्टर lock + SRCU. All sptes must be dropped beक्रमe
 * calling mmu_notअगरier_unरेजिस्टर. ->release or any other notअगरier
 * method may be invoked concurrently with mmu_notअगरier_unरेजिस्टर,
 * and only after mmu_notअगरier_unरेजिस्टर वापसed we're guaranteed
 * that ->release or any other method can't run anymore.
 */
व्योम mmu_notअगरier_unरेजिस्टर(काष्ठा mmu_notअगरier *subscription,
			     काष्ठा mm_काष्ठा *mm)
अणु
	BUG_ON(atomic_पढ़ो(&mm->mm_count) <= 0);

	अगर (!hlist_unhashed(&subscription->hlist)) अणु
		/*
		 * SRCU here will क्रमce निकास_mmap to रुको क्रम ->release to
		 * finish beक्रमe मुक्तing the pages.
		 */
		पूर्णांक id;

		id = srcu_पढ़ो_lock(&srcu);
		/*
		 * निकास_mmap will block in mmu_notअगरier_release to guarantee
		 * that ->release is called beक्रमe मुक्तing the pages.
		 */
		अगर (subscription->ops->release)
			subscription->ops->release(subscription, mm);
		srcu_पढ़ो_unlock(&srcu, id);

		spin_lock(&mm->notअगरier_subscriptions->lock);
		/*
		 * Can not use list_del_rcu() since __mmu_notअगरier_release
		 * can delete it beक्रमe we hold the lock.
		 */
		hlist_del_init_rcu(&subscription->hlist);
		spin_unlock(&mm->notअगरier_subscriptions->lock);
	पूर्ण

	/*
	 * Wait क्रम any running method to finish, of course including
	 * ->release अगर it was run by mmu_notअगरier_release instead of us.
	 */
	synchronize_srcu(&srcu);

	BUG_ON(atomic_पढ़ो(&mm->mm_count) <= 0);

	mmdrop(mm);
पूर्ण
EXPORT_SYMBOL_GPL(mmu_notअगरier_unरेजिस्टर);

अटल व्योम mmu_notअगरier_मुक्त_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा mmu_notअगरier *subscription =
		container_of(rcu, काष्ठा mmu_notअगरier, rcu);
	काष्ठा mm_काष्ठा *mm = subscription->mm;

	subscription->ops->मुक्त_notअगरier(subscription);
	/* Pairs with the get in __mmu_notअगरier_रेजिस्टर() */
	mmdrop(mm);
पूर्ण

/**
 * mmu_notअगरier_put - Release the reference on the notअगरier
 * @subscription: The notअगरier to act on
 *
 * This function must be paired with each mmu_notअगरier_get(), it releases the
 * reference obtained by the get. If this is the last reference then process
 * to मुक्त the notअगरier will be run asynchronously.
 *
 * Unlike mmu_notअगरier_unरेजिस्टर() the get/put flow only calls ops->release
 * when the mm_काष्ठा is destroyed. Instead मुक्त_notअगरier is always called to
 * release any resources held by the user.
 *
 * As ops->release is not guaranteed to be called, the user must ensure that
 * all sptes are dropped, and no new sptes can be established beक्रमe
 * mmu_notअगरier_put() is called.
 *
 * This function can be called from the ops->release callback, however the
 * caller must still ensure it is called pairwise with mmu_notअगरier_get().
 *
 * Modules calling this function must call mmu_notअगरier_synchronize() in
 * their __निकास functions to ensure the async work is completed.
 */
व्योम mmu_notअगरier_put(काष्ठा mmu_notअगरier *subscription)
अणु
	काष्ठा mm_काष्ठा *mm = subscription->mm;

	spin_lock(&mm->notअगरier_subscriptions->lock);
	अगर (WARN_ON(!subscription->users) || --subscription->users)
		जाओ out_unlock;
	hlist_del_init_rcu(&subscription->hlist);
	spin_unlock(&mm->notअगरier_subscriptions->lock);

	call_srcu(&srcu, &subscription->rcu, mmu_notअगरier_मुक्त_rcu);
	वापस;

out_unlock:
	spin_unlock(&mm->notअगरier_subscriptions->lock);
पूर्ण
EXPORT_SYMBOL_GPL(mmu_notअगरier_put);

अटल पूर्णांक __mmu_पूर्णांकerval_notअगरier_insert(
	काष्ठा mmu_पूर्णांकerval_notअगरier *पूर्णांकerval_sub, काष्ठा mm_काष्ठा *mm,
	काष्ठा mmu_notअगरier_subscriptions *subscriptions, अचिन्हित दीर्घ start,
	अचिन्हित दीर्घ length, स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops *ops)
अणु
	पूर्णांकerval_sub->mm = mm;
	पूर्णांकerval_sub->ops = ops;
	RB_CLEAR_NODE(&पूर्णांकerval_sub->पूर्णांकerval_tree.rb);
	पूर्णांकerval_sub->पूर्णांकerval_tree.start = start;
	/*
	 * Note that the representation of the पूर्णांकervals in the पूर्णांकerval tree
	 * considers the ending poपूर्णांक as contained in the पूर्णांकerval.
	 */
	अगर (length == 0 ||
	    check_add_overflow(start, length - 1,
			       &पूर्णांकerval_sub->पूर्णांकerval_tree.last))
		वापस -EOVERFLOW;

	/* Must call with a mmget() held */
	अगर (WARN_ON(atomic_पढ़ो(&mm->mm_users) <= 0))
		वापस -EINVAL;

	/* pairs with mmdrop in mmu_पूर्णांकerval_notअगरier_हटाओ() */
	mmgrab(mm);

	/*
	 * If some invalidate_range_start/end region is going on in parallel
	 * we करोn't know what VA ranges are affected, so we must assume this
	 * new range is included.
	 *
	 * If the itree is invalidating then we are not allowed to change
	 * it. Retrying until invalidation is करोne is tricky due to the
	 * possibility क्रम live lock, instead defer the add to
	 * mn_itree_inv_end() so this algorithm is deterministic.
	 *
	 * In all हालs the value क्रम the पूर्णांकerval_sub->invalidate_seq should be
	 * odd, see mmu_पूर्णांकerval_पढ़ो_begin()
	 */
	spin_lock(&subscriptions->lock);
	अगर (subscriptions->active_invalidate_ranges) अणु
		अगर (mn_itree_is_invalidating(subscriptions))
			hlist_add_head(&पूर्णांकerval_sub->deferred_item,
				       &subscriptions->deferred_list);
		अन्यथा अणु
			subscriptions->invalidate_seq |= 1;
			पूर्णांकerval_tree_insert(&पूर्णांकerval_sub->पूर्णांकerval_tree,
					     &subscriptions->itree);
		पूर्ण
		पूर्णांकerval_sub->invalidate_seq = subscriptions->invalidate_seq;
	पूर्ण अन्यथा अणु
		WARN_ON(mn_itree_is_invalidating(subscriptions));
		/*
		 * The starting seq क्रम a subscription not under invalidation
		 * should be odd, not equal to the current invalidate_seq and
		 * invalidate_seq should not 'wrap' to the new seq any समय
		 * soon.
		 */
		पूर्णांकerval_sub->invalidate_seq =
			subscriptions->invalidate_seq - 1;
		पूर्णांकerval_tree_insert(&पूर्णांकerval_sub->पूर्णांकerval_tree,
				     &subscriptions->itree);
	पूर्ण
	spin_unlock(&subscriptions->lock);
	वापस 0;
पूर्ण

/**
 * mmu_पूर्णांकerval_notअगरier_insert - Insert an पूर्णांकerval notअगरier
 * @पूर्णांकerval_sub: Interval subscription to रेजिस्टर
 * @start: Starting भव address to monitor
 * @length: Length of the range to monitor
 * @mm: mm_काष्ठा to attach to
 * @ops: Interval notअगरier operations to be called on matching events
 *
 * This function subscribes the पूर्णांकerval notअगरier क्रम notअगरications from the
 * mm.  Upon वापस the ops related to mmu_पूर्णांकerval_notअगरier will be called
 * whenever an event that पूर्णांकersects with the given range occurs.
 *
 * Upon वापस the range_notअगरier may not be present in the पूर्णांकerval tree yet.
 * The caller must use the normal पूर्णांकerval notअगरier पढ़ो flow via
 * mmu_पूर्णांकerval_पढ़ो_begin() to establish SPTEs क्रम this range.
 */
पूर्णांक mmu_पूर्णांकerval_notअगरier_insert(काष्ठा mmu_पूर्णांकerval_notअगरier *पूर्णांकerval_sub,
				 काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start,
				 अचिन्हित दीर्घ length,
				 स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops *ops)
अणु
	काष्ठा mmu_notअगरier_subscriptions *subscriptions;
	पूर्णांक ret;

	might_lock(&mm->mmap_lock);

	subscriptions = smp_load_acquire(&mm->notअगरier_subscriptions);
	अगर (!subscriptions || !subscriptions->has_itree) अणु
		ret = mmu_notअगरier_रेजिस्टर(शून्य, mm);
		अगर (ret)
			वापस ret;
		subscriptions = mm->notअगरier_subscriptions;
	पूर्ण
	वापस __mmu_पूर्णांकerval_notअगरier_insert(पूर्णांकerval_sub, mm, subscriptions,
					      start, length, ops);
पूर्ण
EXPORT_SYMBOL_GPL(mmu_पूर्णांकerval_notअगरier_insert);

पूर्णांक mmu_पूर्णांकerval_notअगरier_insert_locked(
	काष्ठा mmu_पूर्णांकerval_notअगरier *पूर्णांकerval_sub, काष्ठा mm_काष्ठा *mm,
	अचिन्हित दीर्घ start, अचिन्हित दीर्घ length,
	स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops *ops)
अणु
	काष्ठा mmu_notअगरier_subscriptions *subscriptions =
		mm->notअगरier_subscriptions;
	पूर्णांक ret;

	mmap_निश्चित_ग_लिखो_locked(mm);

	अगर (!subscriptions || !subscriptions->has_itree) अणु
		ret = __mmu_notअगरier_रेजिस्टर(शून्य, mm);
		अगर (ret)
			वापस ret;
		subscriptions = mm->notअगरier_subscriptions;
	पूर्ण
	वापस __mmu_पूर्णांकerval_notअगरier_insert(पूर्णांकerval_sub, mm, subscriptions,
					      start, length, ops);
पूर्ण
EXPORT_SYMBOL_GPL(mmu_पूर्णांकerval_notअगरier_insert_locked);

/**
 * mmu_पूर्णांकerval_notअगरier_हटाओ - Remove a पूर्णांकerval notअगरier
 * @पूर्णांकerval_sub: Interval subscription to unरेजिस्टर
 *
 * This function must be paired with mmu_पूर्णांकerval_notअगरier_insert(). It cannot
 * be called from any ops callback.
 *
 * Once this वापसs ops callbacks are no दीर्घer running on other CPUs and
 * will not be called in future.
 */
व्योम mmu_पूर्णांकerval_notअगरier_हटाओ(काष्ठा mmu_पूर्णांकerval_notअगरier *पूर्णांकerval_sub)
अणु
	काष्ठा mm_काष्ठा *mm = पूर्णांकerval_sub->mm;
	काष्ठा mmu_notअगरier_subscriptions *subscriptions =
		mm->notअगरier_subscriptions;
	अचिन्हित दीर्घ seq = 0;

	might_sleep();

	spin_lock(&subscriptions->lock);
	अगर (mn_itree_is_invalidating(subscriptions)) अणु
		/*
		 * हटाओ is being called after insert put this on the
		 * deferred list, but beक्रमe the deferred list was processed.
		 */
		अगर (RB_EMPTY_NODE(&पूर्णांकerval_sub->पूर्णांकerval_tree.rb)) अणु
			hlist_del(&पूर्णांकerval_sub->deferred_item);
		पूर्ण अन्यथा अणु
			hlist_add_head(&पूर्णांकerval_sub->deferred_item,
				       &subscriptions->deferred_list);
			seq = subscriptions->invalidate_seq;
		पूर्ण
	पूर्ण अन्यथा अणु
		WARN_ON(RB_EMPTY_NODE(&पूर्णांकerval_sub->पूर्णांकerval_tree.rb));
		पूर्णांकerval_tree_हटाओ(&पूर्णांकerval_sub->पूर्णांकerval_tree,
				     &subscriptions->itree);
	पूर्ण
	spin_unlock(&subscriptions->lock);

	/*
	 * The possible sleep on progress in the invalidation requires the
	 * caller not hold any locks held by invalidation callbacks.
	 */
	lock_map_acquire(&__mmu_notअगरier_invalidate_range_start_map);
	lock_map_release(&__mmu_notअगरier_invalidate_range_start_map);
	अगर (seq)
		रुको_event(subscriptions->wq,
			   READ_ONCE(subscriptions->invalidate_seq) != seq);

	/* pairs with mmgrab in mmu_पूर्णांकerval_notअगरier_insert() */
	mmdrop(mm);
पूर्ण
EXPORT_SYMBOL_GPL(mmu_पूर्णांकerval_notअगरier_हटाओ);

/**
 * mmu_notअगरier_synchronize - Ensure all mmu_notअगरiers are मुक्तd
 *
 * This function ensures that all outstanding async SRU work from
 * mmu_notअगरier_put() is completed. After it वापसs any mmu_notअगरier_ops
 * associated with an unused mmu_notअगरier will no दीर्घer be called.
 *
 * Beक्रमe using the caller must ensure that all of its mmu_notअगरiers have been
 * fully released via mmu_notअगरier_put().
 *
 * Modules using the mmu_notअगरier_put() API should call this in their __निकास
 * function to aव्योम module unloading races.
 */
व्योम mmu_notअगरier_synchronize(व्योम)
अणु
	synchronize_srcu(&srcu);
पूर्ण
EXPORT_SYMBOL_GPL(mmu_notअगरier_synchronize);

bool
mmu_notअगरier_range_update_to_पढ़ो_only(स्थिर काष्ठा mmu_notअगरier_range *range)
अणु
	अगर (!range->vma || range->event != MMU_NOTIFY_PROTECTION_VMA)
		वापस false;
	/* Return true अगर the vma still have the पढ़ो flag set. */
	वापस range->vma->vm_flags & VM_READ;
पूर्ण
EXPORT_SYMBOL_GPL(mmu_notअगरier_range_update_to_पढ़ो_only);
