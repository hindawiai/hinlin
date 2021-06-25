<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2008 Oracle.  All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/page-flags.h>
#समावेश <यंत्र/bug.h>
#समावेश "misc.h"
#समावेश "ctree.h"
#समावेश "extent_io.h"
#समावेश "locking.h"

/*
 * Extent buffer locking
 * =====================
 *
 * We use a rw_semaphore क्रम tree locking, and the semantics are exactly the
 * same:
 *
 * - पढ़ोer/ग_लिखोr exclusion
 * - ग_लिखोr/ग_लिखोr exclusion
 * - पढ़ोer/पढ़ोer sharing
 * - try-lock semantics क्रम पढ़ोers and ग_लिखोrs
 *
 * The rwsem implementation करोes opportunistic spinning which reduces number of
 * बार the locking task needs to sleep.
 */

/*
 * __btrfs_tree_पढ़ो_lock - lock extent buffer क्रम पढ़ो
 * @eb:		the eb to be locked
 * @nest:	the nesting level to be used क्रम lockdep
 *
 * This takes the पढ़ो lock on the extent buffer, using the specअगरied nesting
 * level क्रम lockdep purposes.
 */
व्योम __btrfs_tree_पढ़ो_lock(काष्ठा extent_buffer *eb, क्रमागत btrfs_lock_nesting nest)
अणु
	u64 start_ns = 0;

	अगर (trace_btrfs_tree_पढ़ो_lock_enabled())
		start_ns = kसमय_get_ns();

	करोwn_पढ़ो_nested(&eb->lock, nest);
	eb->lock_owner = current->pid;
	trace_btrfs_tree_पढ़ो_lock(eb, start_ns);
पूर्ण

व्योम btrfs_tree_पढ़ो_lock(काष्ठा extent_buffer *eb)
अणु
	__btrfs_tree_पढ़ो_lock(eb, BTRFS_NESTING_NORMAL);
पूर्ण

/*
 * Try-lock क्रम पढ़ो.
 *
 * Retrun 1 अगर the rwlock has been taken, 0 otherwise
 */
पूर्णांक btrfs_try_tree_पढ़ो_lock(काष्ठा extent_buffer *eb)
अणु
	अगर (करोwn_पढ़ो_trylock(&eb->lock)) अणु
		eb->lock_owner = current->pid;
		trace_btrfs_try_tree_पढ़ो_lock(eb);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Try-lock क्रम ग_लिखो.
 *
 * Retrun 1 अगर the rwlock has been taken, 0 otherwise
 */
पूर्णांक btrfs_try_tree_ग_लिखो_lock(काष्ठा extent_buffer *eb)
अणु
	अगर (करोwn_ग_लिखो_trylock(&eb->lock)) अणु
		eb->lock_owner = current->pid;
		trace_btrfs_try_tree_ग_लिखो_lock(eb);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Release पढ़ो lock.
 */
व्योम btrfs_tree_पढ़ो_unlock(काष्ठा extent_buffer *eb)
अणु
	trace_btrfs_tree_पढ़ो_unlock(eb);
	eb->lock_owner = 0;
	up_पढ़ो(&eb->lock);
पूर्ण

/*
 * __btrfs_tree_lock - lock eb क्रम ग_लिखो
 * @eb:		the eb to lock
 * @nest:	the nesting to use क्रम the lock
 *
 * Returns with the eb->lock ग_लिखो locked.
 */
व्योम __btrfs_tree_lock(काष्ठा extent_buffer *eb, क्रमागत btrfs_lock_nesting nest)
	__acquires(&eb->lock)
अणु
	u64 start_ns = 0;

	अगर (trace_btrfs_tree_lock_enabled())
		start_ns = kसमय_get_ns();

	करोwn_ग_लिखो_nested(&eb->lock, nest);
	eb->lock_owner = current->pid;
	trace_btrfs_tree_lock(eb, start_ns);
पूर्ण

व्योम btrfs_tree_lock(काष्ठा extent_buffer *eb)
अणु
	__btrfs_tree_lock(eb, BTRFS_NESTING_NORMAL);
पूर्ण

/*
 * Release the ग_लिखो lock.
 */
व्योम btrfs_tree_unlock(काष्ठा extent_buffer *eb)
अणु
	trace_btrfs_tree_unlock(eb);
	eb->lock_owner = 0;
	up_ग_लिखो(&eb->lock);
पूर्ण

/*
 * This releases any locks held in the path starting at level and going all the
 * way up to the root.
 *
 * btrfs_search_slot will keep the lock held on higher nodes in a few corner
 * हालs, such as COW of the block at slot zero in the node.  This ignores
 * those rules, and it should only be called when there are no more updates to
 * be करोne higher up in the tree.
 */
व्योम btrfs_unlock_up_safe(काष्ठा btrfs_path *path, पूर्णांक level)
अणु
	पूर्णांक i;

	अगर (path->keep_locks)
		वापस;

	क्रम (i = level; i < BTRFS_MAX_LEVEL; i++) अणु
		अगर (!path->nodes[i])
			जारी;
		अगर (!path->locks[i])
			जारी;
		btrfs_tree_unlock_rw(path->nodes[i], path->locks[i]);
		path->locks[i] = 0;
	पूर्ण
पूर्ण

/*
 * Loop around taking references on and locking the root node of the tree until
 * we end up with a lock on the root node.
 *
 * Return: root extent buffer with ग_लिखो lock held
 */
काष्ठा extent_buffer *btrfs_lock_root_node(काष्ठा btrfs_root *root)
अणु
	काष्ठा extent_buffer *eb;

	जबतक (1) अणु
		eb = btrfs_root_node(root);
		btrfs_tree_lock(eb);
		अगर (eb == root->node)
			अवरोध;
		btrfs_tree_unlock(eb);
		मुक्त_extent_buffer(eb);
	पूर्ण
	वापस eb;
पूर्ण

/*
 * Loop around taking references on and locking the root node of the tree until
 * we end up with a lock on the root node.
 *
 * Return: root extent buffer with पढ़ो lock held
 */
काष्ठा extent_buffer *btrfs_पढ़ो_lock_root_node(काष्ठा btrfs_root *root)
अणु
	काष्ठा extent_buffer *eb;

	जबतक (1) अणु
		eb = btrfs_root_node(root);
		btrfs_tree_पढ़ो_lock(eb);
		अगर (eb == root->node)
			अवरोध;
		btrfs_tree_पढ़ो_unlock(eb);
		मुक्त_extent_buffer(eb);
	पूर्ण
	वापस eb;
पूर्ण

/*
 * DREW locks
 * ==========
 *
 * DREW stands क्रम द्विगुन-पढ़ोer-ग_लिखोr-exclusion lock. It's used in situation
 * where you want to provide A-B exclusion but not AA or BB.
 *
 * Currently implementation gives more priority to पढ़ोer. If a पढ़ोer and a
 * ग_लिखोr both race to acquire their respective sides of the lock the ग_लिखोr
 * would yield its lock as soon as it detects a concurrent पढ़ोer. Additionally
 * अगर there are pending पढ़ोers no new ग_लिखोrs would be allowed to come in and
 * acquire the lock.
 */

पूर्णांक btrfs_drew_lock_init(काष्ठा btrfs_drew_lock *lock)
अणु
	पूर्णांक ret;

	ret = percpu_counter_init(&lock->ग_लिखोrs, 0, GFP_KERNEL);
	अगर (ret)
		वापस ret;

	atomic_set(&lock->पढ़ोers, 0);
	init_रुकोqueue_head(&lock->pending_पढ़ोers);
	init_रुकोqueue_head(&lock->pending_ग_लिखोrs);

	वापस 0;
पूर्ण

व्योम btrfs_drew_lock_destroy(काष्ठा btrfs_drew_lock *lock)
अणु
	percpu_counter_destroy(&lock->ग_लिखोrs);
पूर्ण

/* Return true अगर acquisition is successful, false otherwise */
bool btrfs_drew_try_ग_लिखो_lock(काष्ठा btrfs_drew_lock *lock)
अणु
	अगर (atomic_पढ़ो(&lock->पढ़ोers))
		वापस false;

	percpu_counter_inc(&lock->ग_लिखोrs);

	/* Ensure ग_लिखोrs count is updated beक्रमe we check क्रम pending पढ़ोers */
	smp_mb();
	अगर (atomic_पढ़ो(&lock->पढ़ोers)) अणु
		btrfs_drew_ग_लिखो_unlock(lock);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम btrfs_drew_ग_लिखो_lock(काष्ठा btrfs_drew_lock *lock)
अणु
	जबतक (true) अणु
		अगर (btrfs_drew_try_ग_लिखो_lock(lock))
			वापस;
		रुको_event(lock->pending_ग_लिखोrs, !atomic_पढ़ो(&lock->पढ़ोers));
	पूर्ण
पूर्ण

व्योम btrfs_drew_ग_लिखो_unlock(काष्ठा btrfs_drew_lock *lock)
अणु
	percpu_counter_dec(&lock->ग_लिखोrs);
	cond_wake_up(&lock->pending_पढ़ोers);
पूर्ण

व्योम btrfs_drew_पढ़ो_lock(काष्ठा btrfs_drew_lock *lock)
अणु
	atomic_inc(&lock->पढ़ोers);

	/*
	 * Ensure the pending पढ़ोer count is perceieved BEFORE this पढ़ोer
	 * goes to sleep in हाल of active ग_लिखोrs. This guarantees new ग_लिखोrs
	 * won't be allowed and that the current पढ़ोer will be woken up when
	 * the last active ग_लिखोr finishes its jobs.
	 */
	smp_mb__after_atomic();

	रुको_event(lock->pending_पढ़ोers,
		   percpu_counter_sum(&lock->ग_लिखोrs) == 0);
पूर्ण

व्योम btrfs_drew_पढ़ो_unlock(काष्ठा btrfs_drew_lock *lock)
अणु
	/*
	 * atomic_dec_and_test implies a full barrier, so woken up ग_लिखोrs
	 * are guaranteed to see the decrement
	 */
	अगर (atomic_dec_and_test(&lock->पढ़ोers))
		wake_up(&lock->pending_ग_लिखोrs);
पूर्ण
