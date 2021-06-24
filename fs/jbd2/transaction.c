<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * linux/fs/jbd2/transaction.c
 *
 * Written by Stephen C. Tweedie <sct@redhat.com>, 1998
 *
 * Copyright 1998 Red Hat corp --- All Rights Reserved
 *
 * Generic fileप्रणाली transaction handling code; part of the ext2fs
 * journaling प्रणाली.
 *
 * This file manages transactions (compound commits managed by the
 * journaling code) and handles (inभागidual atomic operations by the
 * fileप्रणाली).
 */

#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/jbd2.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/bug.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/mm.h>

#समावेश <trace/events/jbd2.h>

अटल व्योम __jbd2_journal_temp_unlink_buffer(काष्ठा journal_head *jh);
अटल व्योम __jbd2_journal_unfile_buffer(काष्ठा journal_head *jh);

अटल काष्ठा kmem_cache *transaction_cache;
पूर्णांक __init jbd2_journal_init_transaction_cache(व्योम)
अणु
	J_ASSERT(!transaction_cache);
	transaction_cache = kmem_cache_create("jbd2_transaction_s",
					माप(transaction_t),
					0,
					SLAB_HWCACHE_ALIGN|SLAB_TEMPORARY,
					शून्य);
	अगर (!transaction_cache) अणु
		pr_emerg("JBD2: failed to create transaction cache\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

व्योम jbd2_journal_destroy_transaction_cache(व्योम)
अणु
	kmem_cache_destroy(transaction_cache);
	transaction_cache = शून्य;
पूर्ण

व्योम jbd2_journal_मुक्त_transaction(transaction_t *transaction)
अणु
	अगर (unlikely(ZERO_OR_शून्य_PTR(transaction)))
		वापस;
	kmem_cache_मुक्त(transaction_cache, transaction);
पूर्ण

/*
 * Base amount of descriptor blocks we reserve क्रम each transaction.
 */
अटल पूर्णांक jbd2_descriptor_blocks_per_trans(journal_t *journal)
अणु
	पूर्णांक tag_space = journal->j_blocksize - माप(journal_header_t);
	पूर्णांक tags_per_block;

	/* Subtract UUID */
	tag_space -= 16;
	अगर (jbd2_journal_has_csum_v2or3(journal))
		tag_space -= माप(काष्ठा jbd2_journal_block_tail);
	/* Commit code leaves a slack space of 16 bytes at the end of block */
	tags_per_block = (tag_space - 16) / journal_tag_bytes(journal);
	/*
	 * Revoke descriptors are accounted separately so we need to reserve
	 * space क्रम commit block and normal transaction descriptor blocks.
	 */
	वापस 1 + DIV_ROUND_UP(journal->j_max_transaction_buffers,
				tags_per_block);
पूर्ण

/*
 * jbd2_get_transaction: obtain a new transaction_t object.
 *
 * Simply initialise a new transaction. Initialize it in
 * RUNNING state and add it to the current journal (which should not
 * have an existing running transaction: we only make a new transaction
 * once we have started to commit the old one).
 *
 * Preconditions:
 *	The journal MUST be locked.  We करोn't perक्रमm atomic दो_स्मृतिs on the
 *	new transaction	and we can't block without protecting against other
 *	processes trying to touch the journal जबतक it is in transition.
 *
 */

अटल व्योम jbd2_get_transaction(journal_t *journal,
				transaction_t *transaction)
अणु
	transaction->t_journal = journal;
	transaction->t_state = T_RUNNING;
	transaction->t_start_समय = kसमय_get();
	transaction->t_tid = journal->j_transaction_sequence++;
	transaction->t_expires = jअगरfies + journal->j_commit_पूर्णांकerval;
	spin_lock_init(&transaction->t_handle_lock);
	atomic_set(&transaction->t_updates, 0);
	atomic_set(&transaction->t_outstanding_credits,
		   jbd2_descriptor_blocks_per_trans(journal) +
		   atomic_पढ़ो(&journal->j_reserved_credits));
	atomic_set(&transaction->t_outstanding_revokes, 0);
	atomic_set(&transaction->t_handle_count, 0);
	INIT_LIST_HEAD(&transaction->t_inode_list);
	INIT_LIST_HEAD(&transaction->t_निजी_list);

	/* Set up the commit समयr क्रम the new transaction. */
	journal->j_commit_समयr.expires = round_jअगरfies_up(transaction->t_expires);
	add_समयr(&journal->j_commit_समयr);

	J_ASSERT(journal->j_running_transaction == शून्य);
	journal->j_running_transaction = transaction;
	transaction->t_max_रुको = 0;
	transaction->t_start = jअगरfies;
	transaction->t_requested = 0;
पूर्ण

/*
 * Handle management.
 *
 * A handle_t is an object which represents a single atomic update to a
 * fileप्रणाली, and which tracks all of the modअगरications which क्रमm part
 * of that one update.
 */

/*
 * Update transaction's maximum रुको समय, अगर debugging is enabled.
 *
 * In order क्रम t_max_रुको to be reliable, it must be रक्षित by a
 * lock.  But करोing so will mean that start_this_handle() can not be
 * run in parallel on SMP प्रणालीs, which limits our scalability.  So
 * unless debugging is enabled, we no दीर्घer update t_max_रुको, which
 * means that maximum रुको समय reported by the jbd2_run_stats
 * tracepoपूर्णांक will always be zero.
 */
अटल अंतरभूत व्योम update_t_max_रुको(transaction_t *transaction,
				     अचिन्हित दीर्घ ts)
अणु
#अगर_घोषित CONFIG_JBD2_DEBUG
	अगर (jbd2_journal_enable_debug &&
	    समय_after(transaction->t_start, ts)) अणु
		ts = jbd2_समय_dअगरf(ts, transaction->t_start);
		spin_lock(&transaction->t_handle_lock);
		अगर (ts > transaction->t_max_रुको)
			transaction->t_max_रुको = ts;
		spin_unlock(&transaction->t_handle_lock);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Wait until running transaction passes to T_FLUSH state and new transaction
 * can thus be started. Also starts the commit अगर needed. The function expects
 * running transaction to exist and releases j_state_lock.
 */
अटल व्योम रुको_transaction_locked(journal_t *journal)
	__releases(journal->j_state_lock)
अणु
	DEFINE_WAIT(रुको);
	पूर्णांक need_to_start;
	tid_t tid = journal->j_running_transaction->t_tid;

	prepare_to_रुको(&journal->j_रुको_transaction_locked, &रुको,
			TASK_UNINTERRUPTIBLE);
	need_to_start = !tid_geq(journal->j_commit_request, tid);
	पढ़ो_unlock(&journal->j_state_lock);
	अगर (need_to_start)
		jbd2_log_start_commit(journal, tid);
	jbd2_might_रुको_क्रम_commit(journal);
	schedule();
	finish_रुको(&journal->j_रुको_transaction_locked, &रुको);
पूर्ण

/*
 * Wait until running transaction transitions from T_SWITCH to T_FLUSH
 * state and new transaction can thus be started. The function releases
 * j_state_lock.
 */
अटल व्योम रुको_transaction_चयनing(journal_t *journal)
	__releases(journal->j_state_lock)
अणु
	DEFINE_WAIT(रुको);

	अगर (WARN_ON(!journal->j_running_transaction ||
		    journal->j_running_transaction->t_state != T_SWITCH)) अणु
		पढ़ो_unlock(&journal->j_state_lock);
		वापस;
	पूर्ण
	prepare_to_रुको(&journal->j_रुको_transaction_locked, &रुको,
			TASK_UNINTERRUPTIBLE);
	पढ़ो_unlock(&journal->j_state_lock);
	/*
	 * We करोn't call jbd2_might_wait_for_commit() here as there's no
	 * रुकोing क्रम outstanding handles happening anymore in T_SWITCH state
	 * and handling of reserved handles actually relies on that क्रम
	 * correctness.
	 */
	schedule();
	finish_रुको(&journal->j_रुको_transaction_locked, &रुको);
पूर्ण

अटल व्योम sub_reserved_credits(journal_t *journal, पूर्णांक blocks)
अणु
	atomic_sub(blocks, &journal->j_reserved_credits);
	wake_up(&journal->j_रुको_reserved);
पूर्ण

/*
 * Wait until we can add credits क्रम handle to the running transaction.  Called
 * with j_state_lock held क्रम पढ़ोing. Returns 0 अगर handle joined the running
 * transaction. Returns 1 अगर we had to रुको, j_state_lock is dropped, and
 * caller must retry.
 */
अटल पूर्णांक add_transaction_credits(journal_t *journal, पूर्णांक blocks,
				   पूर्णांक rsv_blocks)
अणु
	transaction_t *t = journal->j_running_transaction;
	पूर्णांक needed;
	पूर्णांक total = blocks + rsv_blocks;

	/*
	 * If the current transaction is locked करोwn क्रम commit, रुको
	 * क्रम the lock to be released.
	 */
	अगर (t->t_state != T_RUNNING) अणु
		WARN_ON_ONCE(t->t_state >= T_FLUSH);
		रुको_transaction_locked(journal);
		वापस 1;
	पूर्ण

	/*
	 * If there is not enough space left in the log to ग_लिखो all
	 * potential buffers requested by this operation, we need to
	 * stall pending a log checkpoपूर्णांक to मुक्त some more log space.
	 */
	needed = atomic_add_वापस(total, &t->t_outstanding_credits);
	अगर (needed > journal->j_max_transaction_buffers) अणु
		/*
		 * If the current transaction is alपढ़ोy too large,
		 * then start to commit it: we can then go back and
		 * attach this handle to a new transaction.
		 */
		atomic_sub(total, &t->t_outstanding_credits);

		/*
		 * Is the number of reserved credits in the current transaction too
		 * big to fit this handle? Wait until reserved credits are मुक्तd.
		 */
		अगर (atomic_पढ़ो(&journal->j_reserved_credits) + total >
		    journal->j_max_transaction_buffers) अणु
			पढ़ो_unlock(&journal->j_state_lock);
			jbd2_might_रुको_क्रम_commit(journal);
			रुको_event(journal->j_रुको_reserved,
				   atomic_पढ़ो(&journal->j_reserved_credits) + total <=
				   journal->j_max_transaction_buffers);
			वापस 1;
		पूर्ण

		रुको_transaction_locked(journal);
		वापस 1;
	पूर्ण

	/*
	 * The commit code assumes that it can get enough log space
	 * without क्रमcing a checkpoपूर्णांक.  This is *critical* क्रम
	 * correctness: a checkpoपूर्णांक of a buffer which is also
	 * associated with a committing transaction creates a deadlock,
	 * so commit simply cannot क्रमce through checkpoपूर्णांकs.
	 *
	 * We must thereक्रमe ensure the necessary space in the journal
	 * *beक्रमe* starting to dirty potentially checkpoपूर्णांकed buffers
	 * in the new transaction.
	 */
	अगर (jbd2_log_space_left(journal) < journal->j_max_transaction_buffers) अणु
		atomic_sub(total, &t->t_outstanding_credits);
		पढ़ो_unlock(&journal->j_state_lock);
		jbd2_might_रुको_क्रम_commit(journal);
		ग_लिखो_lock(&journal->j_state_lock);
		अगर (jbd2_log_space_left(journal) <
					journal->j_max_transaction_buffers)
			__jbd2_log_रुको_क्रम_space(journal);
		ग_लिखो_unlock(&journal->j_state_lock);
		वापस 1;
	पूर्ण

	/* No reservation? We are करोne... */
	अगर (!rsv_blocks)
		वापस 0;

	needed = atomic_add_वापस(rsv_blocks, &journal->j_reserved_credits);
	/* We allow at most half of a transaction to be reserved */
	अगर (needed > journal->j_max_transaction_buffers / 2) अणु
		sub_reserved_credits(journal, rsv_blocks);
		atomic_sub(total, &t->t_outstanding_credits);
		पढ़ो_unlock(&journal->j_state_lock);
		jbd2_might_रुको_क्रम_commit(journal);
		रुको_event(journal->j_रुको_reserved,
			 atomic_पढ़ो(&journal->j_reserved_credits) + rsv_blocks
			 <= journal->j_max_transaction_buffers / 2);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * start_this_handle: Given a handle, deal with any locking or stalling
 * needed to make sure that there is enough journal space क्रम the handle
 * to begin.  Attach the handle to a transaction and set up the
 * transaction's buffer credits.
 */

अटल पूर्णांक start_this_handle(journal_t *journal, handle_t *handle,
			     gfp_t gfp_mask)
अणु
	transaction_t	*transaction, *new_transaction = शून्य;
	पूर्णांक		blocks = handle->h_total_credits;
	पूर्णांक		rsv_blocks = 0;
	अचिन्हित दीर्घ ts = jअगरfies;

	अगर (handle->h_rsv_handle)
		rsv_blocks = handle->h_rsv_handle->h_total_credits;

	/*
	 * Limit the number of reserved credits to 1/2 of maximum transaction
	 * size and limit the number of total credits to not exceed maximum
	 * transaction size per operation.
	 */
	अगर ((rsv_blocks > journal->j_max_transaction_buffers / 2) ||
	    (rsv_blocks + blocks > journal->j_max_transaction_buffers)) अणु
		prपूर्णांकk(KERN_ERR "JBD2: %s wants too many credits "
		       "credits:%d rsv_credits:%d max:%d\n",
		       current->comm, blocks, rsv_blocks,
		       journal->j_max_transaction_buffers);
		WARN_ON(1);
		वापस -ENOSPC;
	पूर्ण

alloc_transaction:
	/*
	 * This check is racy but it is just an optimization of allocating new
	 * transaction early अगर there are high chances we'll need it. If we
	 * guess wrong, we'll retry or मुक्त unused transaction.
	 */
	अगर (!data_race(journal->j_running_transaction)) अणु
		/*
		 * If __GFP_FS is not present, then we may be being called from
		 * inside the fs ग_लिखोback layer, so we MUST NOT fail.
		 */
		अगर ((gfp_mask & __GFP_FS) == 0)
			gfp_mask |= __GFP_NOFAIL;
		new_transaction = kmem_cache_zalloc(transaction_cache,
						    gfp_mask);
		अगर (!new_transaction)
			वापस -ENOMEM;
	पूर्ण

	jbd_debug(3, "New handle %p going live.\n", handle);

	/*
	 * We need to hold j_state_lock until t_updates has been incremented,
	 * क्रम proper journal barrier handling
	 */
repeat:
	पढ़ो_lock(&journal->j_state_lock);
	BUG_ON(journal->j_flags & JBD2_UNMOUNT);
	अगर (is_journal_पातed(journal) ||
	    (journal->j_त्रुटि_सं != 0 && !(journal->j_flags & JBD2_ACK_ERR))) अणु
		पढ़ो_unlock(&journal->j_state_lock);
		jbd2_journal_मुक्त_transaction(new_transaction);
		वापस -EROFS;
	पूर्ण

	/*
	 * Wait on the journal's transaction barrier अगर necessary. Specअगरically
	 * we allow reserved handles to proceed because otherwise commit could
	 * deadlock on page ग_लिखोback not being able to complete.
	 */
	अगर (!handle->h_reserved && journal->j_barrier_count) अणु
		पढ़ो_unlock(&journal->j_state_lock);
		रुको_event(journal->j_रुको_transaction_locked,
				journal->j_barrier_count == 0);
		जाओ repeat;
	पूर्ण

	अगर (!journal->j_running_transaction) अणु
		पढ़ो_unlock(&journal->j_state_lock);
		अगर (!new_transaction)
			जाओ alloc_transaction;
		ग_लिखो_lock(&journal->j_state_lock);
		अगर (!journal->j_running_transaction &&
		    (handle->h_reserved || !journal->j_barrier_count)) अणु
			jbd2_get_transaction(journal, new_transaction);
			new_transaction = शून्य;
		पूर्ण
		ग_लिखो_unlock(&journal->j_state_lock);
		जाओ repeat;
	पूर्ण

	transaction = journal->j_running_transaction;

	अगर (!handle->h_reserved) अणु
		/* We may have dropped j_state_lock - restart in that हाल */
		अगर (add_transaction_credits(journal, blocks, rsv_blocks))
			जाओ repeat;
	पूर्ण अन्यथा अणु
		/*
		 * We have handle reserved so we are allowed to join T_LOCKED
		 * transaction and we करोn't have to check क्रम transaction size
		 * and journal space. But we still have to रुको जबतक running
		 * transaction is being चयनed to a committing one as it
		 * won't रुको क्रम any handles anymore.
		 */
		अगर (transaction->t_state == T_SWITCH) अणु
			रुको_transaction_चयनing(journal);
			जाओ repeat;
		पूर्ण
		sub_reserved_credits(journal, blocks);
		handle->h_reserved = 0;
	पूर्ण

	/* OK, account क्रम the buffers that this operation expects to
	 * use and add the handle to the running transaction. 
	 */
	update_t_max_रुको(transaction, ts);
	handle->h_transaction = transaction;
	handle->h_requested_credits = blocks;
	handle->h_revoke_credits_requested = handle->h_revoke_credits;
	handle->h_start_jअगरfies = jअगरfies;
	atomic_inc(&transaction->t_updates);
	atomic_inc(&transaction->t_handle_count);
	jbd_debug(4, "Handle %p given %d credits (total %d, free %lu)\n",
		  handle, blocks,
		  atomic_पढ़ो(&transaction->t_outstanding_credits),
		  jbd2_log_space_left(journal));
	पढ़ो_unlock(&journal->j_state_lock);
	current->journal_info = handle;

	rwsem_acquire_पढ़ो(&journal->j_trans_commit_map, 0, 0, _THIS_IP_);
	jbd2_journal_मुक्त_transaction(new_transaction);
	/*
	 * Ensure that no allocations करोne जबतक the transaction is खोलो are
	 * going to recurse back to the fs layer.
	 */
	handle->saved_alloc_context = meदो_स्मृति_nofs_save();
	वापस 0;
पूर्ण

/* Allocate a new handle.  This should probably be in a slab... */
अटल handle_t *new_handle(पूर्णांक nblocks)
अणु
	handle_t *handle = jbd2_alloc_handle(GFP_NOFS);
	अगर (!handle)
		वापस शून्य;
	handle->h_total_credits = nblocks;
	handle->h_ref = 1;

	वापस handle;
पूर्ण

handle_t *jbd2__journal_start(journal_t *journal, पूर्णांक nblocks, पूर्णांक rsv_blocks,
			      पूर्णांक revoke_records, gfp_t gfp_mask,
			      अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक line_no)
अणु
	handle_t *handle = journal_current_handle();
	पूर्णांक err;

	अगर (!journal)
		वापस ERR_PTR(-EROFS);

	अगर (handle) अणु
		J_ASSERT(handle->h_transaction->t_journal == journal);
		handle->h_ref++;
		वापस handle;
	पूर्ण

	nblocks += DIV_ROUND_UP(revoke_records,
				journal->j_revoke_records_per_block);
	handle = new_handle(nblocks);
	अगर (!handle)
		वापस ERR_PTR(-ENOMEM);
	अगर (rsv_blocks) अणु
		handle_t *rsv_handle;

		rsv_handle = new_handle(rsv_blocks);
		अगर (!rsv_handle) अणु
			jbd2_मुक्त_handle(handle);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
		rsv_handle->h_reserved = 1;
		rsv_handle->h_journal = journal;
		handle->h_rsv_handle = rsv_handle;
	पूर्ण
	handle->h_revoke_credits = revoke_records;

	err = start_this_handle(journal, handle, gfp_mask);
	अगर (err < 0) अणु
		अगर (handle->h_rsv_handle)
			jbd2_मुक्त_handle(handle->h_rsv_handle);
		jbd2_मुक्त_handle(handle);
		वापस ERR_PTR(err);
	पूर्ण
	handle->h_type = type;
	handle->h_line_no = line_no;
	trace_jbd2_handle_start(journal->j_fs_dev->bd_dev,
				handle->h_transaction->t_tid, type,
				line_no, nblocks);

	वापस handle;
पूर्ण
EXPORT_SYMBOL(jbd2__journal_start);


/**
 * jbd2_journal_start() - Obtain a new handle.
 * @journal: Journal to start transaction on.
 * @nblocks: number of block buffer we might modअगरy
 *
 * We make sure that the transaction can guarantee at least nblocks of
 * modअगरied buffers in the log.  We block until the log can guarantee
 * that much space. Additionally, अगर rsv_blocks > 0, we also create another
 * handle with rsv_blocks reserved blocks in the journal. This handle is
 * stored in h_rsv_handle. It is not attached to any particular transaction
 * and thus करोesn't block transaction commit. If the caller uses this reserved
 * handle, it has to set h_rsv_handle to शून्य as otherwise jbd2_journal_stop()
 * on the parent handle will dispose the reserved one. Reserved handle has to
 * be converted to a normal handle using jbd2_journal_start_reserved() beक्रमe
 * it can be used.
 *
 * Return a poपूर्णांकer to a newly allocated handle, or an ERR_PTR() value
 * on failure.
 */
handle_t *jbd2_journal_start(journal_t *journal, पूर्णांक nblocks)
अणु
	वापस jbd2__journal_start(journal, nblocks, 0, 0, GFP_NOFS, 0, 0);
पूर्ण
EXPORT_SYMBOL(jbd2_journal_start);

अटल व्योम __jbd2_journal_unreserve_handle(handle_t *handle, transaction_t *t)
अणु
	journal_t *journal = handle->h_journal;

	WARN_ON(!handle->h_reserved);
	sub_reserved_credits(journal, handle->h_total_credits);
	अगर (t)
		atomic_sub(handle->h_total_credits, &t->t_outstanding_credits);
पूर्ण

व्योम jbd2_journal_मुक्त_reserved(handle_t *handle)
अणु
	journal_t *journal = handle->h_journal;

	/* Get j_state_lock to pin running transaction अगर it exists */
	पढ़ो_lock(&journal->j_state_lock);
	__jbd2_journal_unreserve_handle(handle, journal->j_running_transaction);
	पढ़ो_unlock(&journal->j_state_lock);
	jbd2_मुक्त_handle(handle);
पूर्ण
EXPORT_SYMBOL(jbd2_journal_मुक्त_reserved);

/**
 * jbd2_journal_start_reserved() - start reserved handle
 * @handle: handle to start
 * @type: क्रम handle statistics
 * @line_no: क्रम handle statistics
 *
 * Start handle that has been previously reserved with jbd2_journal_reserve().
 * This attaches @handle to the running transaction (or creates one अगर there's
 * not transaction running). Unlike jbd2_journal_start() this function cannot
 * block on journal commit, checkpoपूर्णांकing, or similar stuff. It can block on
 * memory allocation or frozen journal though.
 *
 * Return 0 on success, non-zero on error - handle is मुक्तd in that हाल.
 */
पूर्णांक jbd2_journal_start_reserved(handle_t *handle, अचिन्हित पूर्णांक type,
				अचिन्हित पूर्णांक line_no)
अणु
	journal_t *journal = handle->h_journal;
	पूर्णांक ret = -EIO;

	अगर (WARN_ON(!handle->h_reserved)) अणु
		/* Someone passed in normal handle? Just stop it. */
		jbd2_journal_stop(handle);
		वापस ret;
	पूर्ण
	/*
	 * Usefulness of mixing of reserved and unreserved handles is
	 * questionable. So far nobody seems to need it so just error out.
	 */
	अगर (WARN_ON(current->journal_info)) अणु
		jbd2_journal_मुक्त_reserved(handle);
		वापस ret;
	पूर्ण

	handle->h_journal = शून्य;
	/*
	 * GFP_NOFS is here because callers are likely from ग_लिखोback or
	 * similarly स्थिरrained call sites
	 */
	ret = start_this_handle(journal, handle, GFP_NOFS);
	अगर (ret < 0) अणु
		handle->h_journal = journal;
		jbd2_journal_मुक्त_reserved(handle);
		वापस ret;
	पूर्ण
	handle->h_type = type;
	handle->h_line_no = line_no;
	trace_jbd2_handle_start(journal->j_fs_dev->bd_dev,
				handle->h_transaction->t_tid, type,
				line_no, handle->h_total_credits);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(jbd2_journal_start_reserved);

/**
 * jbd2_journal_extend() - extend buffer credits.
 * @handle:  handle to 'extend'
 * @nblocks: nr blocks to try to extend by.
 * @revoke_records: number of revoke records to try to extend by.
 *
 * Some transactions, such as large extends and truncates, can be करोne
 * atomically all at once or in several stages.  The operation requests
 * a credit क्रम a number of buffer modअगरications in advance, but can
 * extend its credit अगर it needs more.
 *
 * jbd2_journal_extend tries to give the running handle more buffer credits.
 * It करोes not guarantee that allocation - this is a best-efक्रमt only.
 * The calling process MUST be able to deal cleanly with a failure to
 * extend here.
 *
 * Return 0 on success, non-zero on failure.
 *
 * वापस code < 0 implies an error
 * वापस code > 0 implies normal transaction-full status.
 */
पूर्णांक jbd2_journal_extend(handle_t *handle, पूर्णांक nblocks, पूर्णांक revoke_records)
अणु
	transaction_t *transaction = handle->h_transaction;
	journal_t *journal;
	पूर्णांक result;
	पूर्णांक wanted;

	अगर (is_handle_पातed(handle))
		वापस -EROFS;
	journal = transaction->t_journal;

	result = 1;

	पढ़ो_lock(&journal->j_state_lock);

	/* Don't extend a locked-करोwn transaction! */
	अगर (transaction->t_state != T_RUNNING) अणु
		jbd_debug(3, "denied handle %p %d blocks: "
			  "transaction not running\n", handle, nblocks);
		जाओ error_out;
	पूर्ण

	nblocks += DIV_ROUND_UP(
			handle->h_revoke_credits_requested + revoke_records,
			journal->j_revoke_records_per_block) -
		DIV_ROUND_UP(
			handle->h_revoke_credits_requested,
			journal->j_revoke_records_per_block);
	spin_lock(&transaction->t_handle_lock);
	wanted = atomic_add_वापस(nblocks,
				   &transaction->t_outstanding_credits);

	अगर (wanted > journal->j_max_transaction_buffers) अणु
		jbd_debug(3, "denied handle %p %d blocks: "
			  "transaction too large\n", handle, nblocks);
		atomic_sub(nblocks, &transaction->t_outstanding_credits);
		जाओ unlock;
	पूर्ण

	trace_jbd2_handle_extend(journal->j_fs_dev->bd_dev,
				 transaction->t_tid,
				 handle->h_type, handle->h_line_no,
				 handle->h_total_credits,
				 nblocks);

	handle->h_total_credits += nblocks;
	handle->h_requested_credits += nblocks;
	handle->h_revoke_credits += revoke_records;
	handle->h_revoke_credits_requested += revoke_records;
	result = 0;

	jbd_debug(3, "extended handle %p by %d\n", handle, nblocks);
unlock:
	spin_unlock(&transaction->t_handle_lock);
error_out:
	पढ़ो_unlock(&journal->j_state_lock);
	वापस result;
पूर्ण

अटल व्योम stop_this_handle(handle_t *handle)
अणु
	transaction_t *transaction = handle->h_transaction;
	journal_t *journal = transaction->t_journal;
	पूर्णांक revokes;

	J_ASSERT(journal_current_handle() == handle);
	J_ASSERT(atomic_पढ़ो(&transaction->t_updates) > 0);
	current->journal_info = शून्य;
	/*
	 * Subtract necessary revoke descriptor blocks from handle credits. We
	 * take care to account only क्रम revoke descriptor blocks the
	 * transaction will really need as large sequences of transactions with
	 * small numbers of revokes are relatively common.
	 */
	revokes = handle->h_revoke_credits_requested - handle->h_revoke_credits;
	अगर (revokes) अणु
		पूर्णांक t_revokes, revoke_descriptors;
		पूर्णांक rr_per_blk = journal->j_revoke_records_per_block;

		WARN_ON_ONCE(DIV_ROUND_UP(revokes, rr_per_blk)
				> handle->h_total_credits);
		t_revokes = atomic_add_वापस(revokes,
				&transaction->t_outstanding_revokes);
		revoke_descriptors =
			DIV_ROUND_UP(t_revokes, rr_per_blk) -
			DIV_ROUND_UP(t_revokes - revokes, rr_per_blk);
		handle->h_total_credits -= revoke_descriptors;
	पूर्ण
	atomic_sub(handle->h_total_credits,
		   &transaction->t_outstanding_credits);
	अगर (handle->h_rsv_handle)
		__jbd2_journal_unreserve_handle(handle->h_rsv_handle,
						transaction);
	अगर (atomic_dec_and_test(&transaction->t_updates))
		wake_up(&journal->j_रुको_updates);

	rwsem_release(&journal->j_trans_commit_map, _THIS_IP_);
	/*
	 * Scope of the GFP_NOFS context is over here and so we can restore the
	 * original alloc context.
	 */
	meदो_स्मृति_nofs_restore(handle->saved_alloc_context);
पूर्ण

/**
 * jbd2__journal_restart() - restart a handle .
 * @handle:  handle to restart
 * @nblocks: nr credits requested
 * @revoke_records: number of revoke record credits requested
 * @gfp_mask: memory allocation flags (क्रम start_this_handle)
 *
 * Restart a handle क्रम a multi-transaction fileप्रणाली
 * operation.
 *
 * If the jbd2_journal_extend() call above fails to grant new buffer credits
 * to a running handle, a call to jbd2_journal_restart will commit the
 * handle's transaction so far and reattach the handle to a new
 * transaction capable of guaranteeing the requested number of
 * credits. We preserve reserved handle अगर there's any attached to the
 * passed in handle.
 */
पूर्णांक jbd2__journal_restart(handle_t *handle, पूर्णांक nblocks, पूर्णांक revoke_records,
			  gfp_t gfp_mask)
अणु
	transaction_t *transaction = handle->h_transaction;
	journal_t *journal;
	tid_t		tid;
	पूर्णांक		need_to_start;
	पूर्णांक		ret;

	/* If we've had an abort of any type, don't even think about
	 * actually करोing the restart! */
	अगर (is_handle_पातed(handle))
		वापस 0;
	journal = transaction->t_journal;
	tid = transaction->t_tid;

	/*
	 * First unlink the handle from its current transaction, and start the
	 * commit on that.
	 */
	jbd_debug(2, "restarting handle %p\n", handle);
	stop_this_handle(handle);
	handle->h_transaction = शून्य;

	/*
	 * TODO: If we use READ_ONCE / WRITE_ONCE क्रम j_commit_request we can
 	 * get rid of poपूर्णांकless j_state_lock traffic like this.
	 */
	पढ़ो_lock(&journal->j_state_lock);
	need_to_start = !tid_geq(journal->j_commit_request, tid);
	पढ़ो_unlock(&journal->j_state_lock);
	अगर (need_to_start)
		jbd2_log_start_commit(journal, tid);
	handle->h_total_credits = nblocks +
		DIV_ROUND_UP(revoke_records,
			     journal->j_revoke_records_per_block);
	handle->h_revoke_credits = revoke_records;
	ret = start_this_handle(journal, handle, gfp_mask);
	trace_jbd2_handle_restart(journal->j_fs_dev->bd_dev,
				 ret ? 0 : handle->h_transaction->t_tid,
				 handle->h_type, handle->h_line_no,
				 handle->h_total_credits);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(jbd2__journal_restart);


पूर्णांक jbd2_journal_restart(handle_t *handle, पूर्णांक nblocks)
अणु
	वापस jbd2__journal_restart(handle, nblocks, 0, GFP_NOFS);
पूर्ण
EXPORT_SYMBOL(jbd2_journal_restart);

/**
 * jbd2_journal_lock_updates () - establish a transaction barrier.
 * @journal:  Journal to establish a barrier on.
 *
 * This locks out any further updates from being started, and blocks
 * until all existing updates have completed, वापसing only once the
 * journal is in a quiescent state with no updates running.
 *
 * The journal lock should not be held on entry.
 */
व्योम jbd2_journal_lock_updates(journal_t *journal)
अणु
	DEFINE_WAIT(रुको);

	jbd2_might_रुको_क्रम_commit(journal);

	ग_लिखो_lock(&journal->j_state_lock);
	++journal->j_barrier_count;

	/* Wait until there are no reserved handles */
	अगर (atomic_पढ़ो(&journal->j_reserved_credits)) अणु
		ग_लिखो_unlock(&journal->j_state_lock);
		रुको_event(journal->j_रुको_reserved,
			   atomic_पढ़ो(&journal->j_reserved_credits) == 0);
		ग_लिखो_lock(&journal->j_state_lock);
	पूर्ण

	/* Wait until there are no running updates */
	जबतक (1) अणु
		transaction_t *transaction = journal->j_running_transaction;

		अगर (!transaction)
			अवरोध;

		spin_lock(&transaction->t_handle_lock);
		prepare_to_रुको(&journal->j_रुको_updates, &रुको,
				TASK_UNINTERRUPTIBLE);
		अगर (!atomic_पढ़ो(&transaction->t_updates)) अणु
			spin_unlock(&transaction->t_handle_lock);
			finish_रुको(&journal->j_रुको_updates, &रुको);
			अवरोध;
		पूर्ण
		spin_unlock(&transaction->t_handle_lock);
		ग_लिखो_unlock(&journal->j_state_lock);
		schedule();
		finish_रुको(&journal->j_रुको_updates, &रुको);
		ग_लिखो_lock(&journal->j_state_lock);
	पूर्ण
	ग_लिखो_unlock(&journal->j_state_lock);

	/*
	 * We have now established a barrier against other normal updates, but
	 * we also need to barrier against other jbd2_journal_lock_updates() calls
	 * to make sure that we serialise special journal-locked operations
	 * too.
	 */
	mutex_lock(&journal->j_barrier);
पूर्ण

/**
 * jbd2_journal_unlock_updates () - release barrier
 * @journal:  Journal to release the barrier on.
 *
 * Release a transaction barrier obtained with jbd2_journal_lock_updates().
 *
 * Should be called without the journal lock held.
 */
व्योम jbd2_journal_unlock_updates (journal_t *journal)
अणु
	J_ASSERT(journal->j_barrier_count != 0);

	mutex_unlock(&journal->j_barrier);
	ग_लिखो_lock(&journal->j_state_lock);
	--journal->j_barrier_count;
	ग_लिखो_unlock(&journal->j_state_lock);
	wake_up(&journal->j_रुको_transaction_locked);
पूर्ण

अटल व्योम warn_dirty_buffer(काष्ठा buffer_head *bh)
अणु
	prपूर्णांकk(KERN_WARNING
	       "JBD2: Spotted dirty metadata buffer (dev = %pg, blocknr = %llu). "
	       "There's a risk of filesystem corruption in case of system "
	       "crash.\n",
	       bh->b_bdev, (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
पूर्ण

/* Call t_frozen trigger and copy buffer data पूर्णांकo jh->b_frozen_data. */
अटल व्योम jbd2_मुक्तze_jh_data(काष्ठा journal_head *jh)
अणु
	काष्ठा page *page;
	पूर्णांक offset;
	अक्षर *source;
	काष्ठा buffer_head *bh = jh2bh(jh);

	J_EXPECT_JH(jh, buffer_uptodate(bh), "Possible IO failure.\n");
	page = bh->b_page;
	offset = offset_in_page(bh->b_data);
	source = kmap_atomic(page);
	/* Fire data frozen trigger just beक्रमe we copy the data */
	jbd2_buffer_frozen_trigger(jh, source + offset, jh->b_triggers);
	स_नकल(jh->b_frozen_data, source + offset, bh->b_size);
	kunmap_atomic(source);

	/*
	 * Now that the frozen data is saved off, we need to store any matching
	 * triggers.
	 */
	jh->b_frozen_triggers = jh->b_triggers;
पूर्ण

/*
 * If the buffer is alपढ़ोy part of the current transaction, then there
 * is nothing we need to करो.  If it is alपढ़ोy part of a prior
 * transaction which we are still committing to disk, then we need to
 * make sure that we करो not overग_लिखो the old copy: we करो copy-out to
 * preserve the copy going to disk.  We also account the buffer against
 * the handle's metadata buffer credits (unless the buffer is alपढ़ोy
 * part of the transaction, that is).
 *
 */
अटल पूर्णांक
करो_get_ग_लिखो_access(handle_t *handle, काष्ठा journal_head *jh,
			पूर्णांक क्रमce_copy)
अणु
	काष्ठा buffer_head *bh;
	transaction_t *transaction = handle->h_transaction;
	journal_t *journal;
	पूर्णांक error;
	अक्षर *frozen_buffer = शून्य;
	अचिन्हित दीर्घ start_lock, समय_lock;

	journal = transaction->t_journal;

	jbd_debug(5, "journal_head %p, force_copy %d\n", jh, क्रमce_copy);

	JBUFFER_TRACE(jh, "entry");
repeat:
	bh = jh2bh(jh);

	/* @@@ Need to check क्रम errors here at some poपूर्णांक. */

 	start_lock = jअगरfies;
	lock_buffer(bh);
	spin_lock(&jh->b_state_lock);

	/* If it takes too दीर्घ to lock the buffer, trace it */
	समय_lock = jbd2_समय_dअगरf(start_lock, jअगरfies);
	अगर (समय_lock > HZ/10)
		trace_jbd2_lock_buffer_stall(bh->b_bdev->bd_dev,
			jअगरfies_to_msecs(समय_lock));

	/* We now hold the buffer lock so it is safe to query the buffer
	 * state.  Is the buffer dirty?
	 *
	 * If so, there are two possibilities.  The buffer may be
	 * non-journaled, and undergoing a quite legitimate ग_लिखोback.
	 * Otherwise, it is journaled, and we करोn't expect dirty buffers
	 * in that state (the buffers should be marked JBD_Dirty
	 * instead.)  So either the IO is being करोne under our own
	 * control and this is a bug, or it's a third party IO such as
	 * dump(8) (which may leave the buffer scheduled क्रम पढ़ो ---
	 * ie. locked but not dirty) or tune2fs (which may actually have
	 * the buffer dirtied, ugh.)  */

	अगर (buffer_dirty(bh)) अणु
		/*
		 * First question: is this buffer alपढ़ोy part of the current
		 * transaction or the existing committing transaction?
		 */
		अगर (jh->b_transaction) अणु
			J_ASSERT_JH(jh,
				jh->b_transaction == transaction ||
				jh->b_transaction ==
					journal->j_committing_transaction);
			अगर (jh->b_next_transaction)
				J_ASSERT_JH(jh, jh->b_next_transaction ==
							transaction);
			warn_dirty_buffer(bh);
		पूर्ण
		/*
		 * In any हाल we need to clean the dirty flag and we must
		 * करो it under the buffer lock to be sure we करोn't race
		 * with running ग_लिखो-out.
		 */
		JBUFFER_TRACE(jh, "Journalling dirty buffer");
		clear_buffer_dirty(bh);
		set_buffer_jbddirty(bh);
	पूर्ण

	unlock_buffer(bh);

	error = -EROFS;
	अगर (is_handle_पातed(handle)) अणु
		spin_unlock(&jh->b_state_lock);
		जाओ out;
	पूर्ण
	error = 0;

	/*
	 * The buffer is alपढ़ोy part of this transaction अगर b_transaction or
	 * b_next_transaction poपूर्णांकs to it
	 */
	अगर (jh->b_transaction == transaction ||
	    jh->b_next_transaction == transaction)
		जाओ करोne;

	/*
	 * this is the first समय this transaction is touching this buffer,
	 * reset the modअगरied flag
	 */
	jh->b_modअगरied = 0;

	/*
	 * If the buffer is not journaled right now, we need to make sure it
	 * करोesn't get written to disk beक्रमe the caller actually commits the
	 * new data
	 */
	अगर (!jh->b_transaction) अणु
		JBUFFER_TRACE(jh, "no transaction");
		J_ASSERT_JH(jh, !jh->b_next_transaction);
		JBUFFER_TRACE(jh, "file as BJ_Reserved");
		/*
		 * Make sure all stores to jh (b_modअगरied, b_frozen_data) are
		 * visible beक्रमe attaching it to the running transaction.
		 * Paired with barrier in jbd2_ग_लिखो_access_granted()
		 */
		smp_wmb();
		spin_lock(&journal->j_list_lock);
		__jbd2_journal_file_buffer(jh, transaction, BJ_Reserved);
		spin_unlock(&journal->j_list_lock);
		जाओ करोne;
	पूर्ण
	/*
	 * If there is alपढ़ोy a copy-out version of this buffer, then we करोn't
	 * need to make another one
	 */
	अगर (jh->b_frozen_data) अणु
		JBUFFER_TRACE(jh, "has frozen data");
		J_ASSERT_JH(jh, jh->b_next_transaction == शून्य);
		जाओ attach_next;
	पूर्ण

	JBUFFER_TRACE(jh, "owned by older transaction");
	J_ASSERT_JH(jh, jh->b_next_transaction == शून्य);
	J_ASSERT_JH(jh, jh->b_transaction == journal->j_committing_transaction);

	/*
	 * There is one हाल we have to be very careful about.  If the
	 * committing transaction is currently writing this buffer out to disk
	 * and has NOT made a copy-out, then we cannot modअगरy the buffer
	 * contents at all right now.  The essence of copy-out is that it is
	 * the extra copy, not the primary copy, which माला_लो journaled.  If the
	 * primary copy is alपढ़ोy going to disk then we cannot करो copy-out
	 * here.
	 */
	अगर (buffer_shaकरोw(bh)) अणु
		JBUFFER_TRACE(jh, "on shadow: sleep");
		spin_unlock(&jh->b_state_lock);
		रुको_on_bit_io(&bh->b_state, BH_Shaकरोw, TASK_UNINTERRUPTIBLE);
		जाओ repeat;
	पूर्ण

	/*
	 * Only करो the copy अगर the currently-owning transaction still needs it.
	 * If buffer isn't on BJ_Metadata list, the committing transaction is
	 * past that stage (here we use the fact that BH_Shaकरोw is set under
	 * bh_state lock together with refiling to BJ_Shaकरोw list and at this
	 * poपूर्णांक we know the buffer करोesn't have BH_Shaकरोw set).
	 *
	 * Subtle poपूर्णांक, though: अगर this is a get_unकरो_access, then we will be
	 * relying on the frozen_data to contain the new value of the
	 * committed_data record after the transaction, so we HAVE to क्रमce the
	 * frozen_data copy in that हाल.
	 */
	अगर (jh->b_jlist == BJ_Metadata || क्रमce_copy) अणु
		JBUFFER_TRACE(jh, "generate frozen data");
		अगर (!frozen_buffer) अणु
			JBUFFER_TRACE(jh, "allocate memory for buffer");
			spin_unlock(&jh->b_state_lock);
			frozen_buffer = jbd2_alloc(jh2bh(jh)->b_size,
						   GFP_NOFS | __GFP_NOFAIL);
			जाओ repeat;
		पूर्ण
		jh->b_frozen_data = frozen_buffer;
		frozen_buffer = शून्य;
		jbd2_मुक्तze_jh_data(jh);
	पूर्ण
attach_next:
	/*
	 * Make sure all stores to jh (b_modअगरied, b_frozen_data) are visible
	 * beक्रमe attaching it to the running transaction. Paired with barrier
	 * in jbd2_ग_लिखो_access_granted()
	 */
	smp_wmb();
	jh->b_next_transaction = transaction;

करोne:
	spin_unlock(&jh->b_state_lock);

	/*
	 * If we are about to journal a buffer, then any revoke pending on it is
	 * no दीर्घer valid
	 */
	jbd2_journal_cancel_revoke(handle, jh);

out:
	अगर (unlikely(frozen_buffer))	/* It's usually शून्य */
		jbd2_मुक्त(frozen_buffer, bh->b_size);

	JBUFFER_TRACE(jh, "exit");
	वापस error;
पूर्ण

/* Fast check whether buffer is alपढ़ोy attached to the required transaction */
अटल bool jbd2_ग_लिखो_access_granted(handle_t *handle, काष्ठा buffer_head *bh,
							bool unकरो)
अणु
	काष्ठा journal_head *jh;
	bool ret = false;

	/* Dirty buffers require special handling... */
	अगर (buffer_dirty(bh))
		वापस false;

	/*
	 * RCU protects us from dereferencing मुक्तd pages. So the checks we करो
	 * are guaranteed not to oops. However the jh slab object can get मुक्तd
	 * & पुनः_स्मृतिated जबतक we work with it. So we have to be careful. When
	 * we see jh attached to the running transaction, we know it must stay
	 * so until the transaction is committed. Thus jh won't be मुक्तd and
	 * will be attached to the same bh जबतक we run.  However it can
	 * happen jh माला_लो मुक्तd, पुनः_स्मृतिated, and attached to the transaction
	 * just after we get poपूर्णांकer to it from bh. So we have to be careful
	 * and recheck jh still beदीर्घs to our bh beक्रमe we वापस success.
	 */
	rcu_पढ़ो_lock();
	अगर (!buffer_jbd(bh))
		जाओ out;
	/* This should be bh2jh() but that करोesn't work with अंतरभूत functions */
	jh = READ_ONCE(bh->b_निजी);
	अगर (!jh)
		जाओ out;
	/* For unकरो access buffer must have data copied */
	अगर (unकरो && !jh->b_committed_data)
		जाओ out;
	अगर (READ_ONCE(jh->b_transaction) != handle->h_transaction &&
	    READ_ONCE(jh->b_next_transaction) != handle->h_transaction)
		जाओ out;
	/*
	 * There are two reasons क्रम the barrier here:
	 * 1) Make sure to fetch b_bh after we did previous checks so that we
	 * detect when jh went through मुक्त, पुनः_स्मृति, attach to transaction
	 * जबतक we were checking. Paired with implicit barrier in that path.
	 * 2) So that access to bh करोne after jbd2_ग_लिखो_access_granted()
	 * करोesn't get reordered and see inconsistent state of concurrent
	 * करो_get_ग_लिखो_access().
	 */
	smp_mb();
	अगर (unlikely(jh->b_bh != bh))
		जाओ out;
	ret = true;
out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/**
 * jbd2_journal_get_ग_लिखो_access() - notअगरy पूर्णांकent to modअगरy a buffer
 *				     क्रम metadata (not data) update.
 * @handle: transaction to add buffer modअगरications to
 * @bh:     bh to be used क्रम metadata ग_लिखोs
 *
 * Returns: error code or 0 on success.
 *
 * In full data journalling mode the buffer may be of type BJ_AsyncData,
 * because we're ``ग_लिखो()ing`` a buffer which is also part of a shared mapping.
 */

पूर्णांक jbd2_journal_get_ग_लिखो_access(handle_t *handle, काष्ठा buffer_head *bh)
अणु
	काष्ठा journal_head *jh;
	पूर्णांक rc;

	अगर (is_handle_पातed(handle))
		वापस -EROFS;

	अगर (jbd2_ग_लिखो_access_granted(handle, bh, false))
		वापस 0;

	jh = jbd2_journal_add_journal_head(bh);
	/* We करो not want to get caught playing with fields which the
	 * log thपढ़ो also manipulates.  Make sure that the buffer
	 * completes any outstanding IO beक्रमe proceeding. */
	rc = करो_get_ग_लिखो_access(handle, jh, 0);
	jbd2_journal_put_journal_head(jh);
	वापस rc;
पूर्ण


/*
 * When the user wants to journal a newly created buffer_head
 * (ie. getblk() वापसed a new buffer and we are going to populate it
 * manually rather than पढ़ोing off disk), then we need to keep the
 * buffer_head locked until it has been completely filled with new
 * data.  In this हाल, we should be able to make the निश्चितion that
 * the bh is not alपढ़ोy part of an existing transaction.
 *
 * The buffer should alपढ़ोy be locked by the caller by this poपूर्णांक.
 * There is no lock ranking violation: it was a newly created,
 * unlocked buffer beक्रमehand. */

/**
 * jbd2_journal_get_create_access () - notअगरy पूर्णांकent to use newly created bh
 * @handle: transaction to new buffer to
 * @bh: new buffer.
 *
 * Call this अगर you create a new bh.
 */
पूर्णांक jbd2_journal_get_create_access(handle_t *handle, काष्ठा buffer_head *bh)
अणु
	transaction_t *transaction = handle->h_transaction;
	journal_t *journal;
	काष्ठा journal_head *jh = jbd2_journal_add_journal_head(bh);
	पूर्णांक err;

	jbd_debug(5, "journal_head %p\n", jh);
	err = -EROFS;
	अगर (is_handle_पातed(handle))
		जाओ out;
	journal = transaction->t_journal;
	err = 0;

	JBUFFER_TRACE(jh, "entry");
	/*
	 * The buffer may alपढ़ोy beदीर्घ to this transaction due to pre-zeroing
	 * in the fileप्रणाली's new_block code.  It may also be on the previous,
	 * committing transaction's lists, but it HAS to be in Forget state in
	 * that हाल: the transaction must have deleted the buffer क्रम it to be
	 * reused here.
	 */
	spin_lock(&jh->b_state_lock);
	J_ASSERT_JH(jh, (jh->b_transaction == transaction ||
		jh->b_transaction == शून्य ||
		(jh->b_transaction == journal->j_committing_transaction &&
			  jh->b_jlist == BJ_Forget)));

	J_ASSERT_JH(jh, jh->b_next_transaction == शून्य);
	J_ASSERT_JH(jh, buffer_locked(jh2bh(jh)));

	अगर (jh->b_transaction == शून्य) अणु
		/*
		 * Previous jbd2_journal_क्रमget() could have left the buffer
		 * with jbddirty bit set because it was being committed. When
		 * the commit finished, we've filed the buffer क्रम
		 * checkpoपूर्णांकing and marked it dirty. Now we are पुनः_स्मृतिating
		 * the buffer so the transaction मुक्तing it must have
		 * committed and so it's safe to clear the dirty bit.
		 */
		clear_buffer_dirty(jh2bh(jh));
		/* first access by this transaction */
		jh->b_modअगरied = 0;

		JBUFFER_TRACE(jh, "file as BJ_Reserved");
		spin_lock(&journal->j_list_lock);
		__jbd2_journal_file_buffer(jh, transaction, BJ_Reserved);
		spin_unlock(&journal->j_list_lock);
	पूर्ण अन्यथा अगर (jh->b_transaction == journal->j_committing_transaction) अणु
		/* first access by this transaction */
		jh->b_modअगरied = 0;

		JBUFFER_TRACE(jh, "set next transaction");
		spin_lock(&journal->j_list_lock);
		jh->b_next_transaction = transaction;
		spin_unlock(&journal->j_list_lock);
	पूर्ण
	spin_unlock(&jh->b_state_lock);

	/*
	 * akpm: I added this.  ext3_alloc_branch can pick up new indirect
	 * blocks which contain मुक्तd but then revoked metadata.  We need
	 * to cancel the revoke in हाल we end up मुक्तing it yet again
	 * and the पुनः_स्मृतिating as data - this would cause a second revoke,
	 * which hits an निश्चितion error.
	 */
	JBUFFER_TRACE(jh, "cancelling revoke");
	jbd2_journal_cancel_revoke(handle, jh);
out:
	jbd2_journal_put_journal_head(jh);
	वापस err;
पूर्ण

/**
 * jbd2_journal_get_unकरो_access() -  Notअगरy पूर्णांकent to modअगरy metadata with
 *     non-शुरुआतable consequences
 * @handle: transaction
 * @bh: buffer to unकरो
 *
 * Someबार there is a need to distinguish between metadata which has
 * been committed to disk and that which has not.  The ext3fs code uses
 * this क्रम मुक्तing and allocating space, we have to make sure that we
 * करो not reuse मुक्तd space until the deallocation has been committed,
 * since अगर we overwrote that space we would make the delete
 * un-शुरुआतable in हाल of a crash.
 *
 * To deal with that, jbd2_journal_get_unकरो_access requests ग_लिखो access to a
 * buffer क्रम parts of non-शुरुआतable operations such as delete
 * operations on the biपंचांगaps.  The journaling code must keep a copy of
 * the buffer's contents prior to the unकरो_access call until such समय
 * as we know that the buffer has definitely been committed to disk.
 *
 * We never need to know which transaction the committed data is part
 * of, buffers touched here are guaranteed to be dirtied later and so
 * will be committed to a new transaction in due course, at which poपूर्णांक
 * we can discard the old committed data poपूर्णांकer.
 *
 * Returns error number or 0 on success.
 */
पूर्णांक jbd2_journal_get_unकरो_access(handle_t *handle, काष्ठा buffer_head *bh)
अणु
	पूर्णांक err;
	काष्ठा journal_head *jh;
	अक्षर *committed_data = शून्य;

	अगर (is_handle_पातed(handle))
		वापस -EROFS;

	अगर (jbd2_ग_लिखो_access_granted(handle, bh, true))
		वापस 0;

	jh = jbd2_journal_add_journal_head(bh);
	JBUFFER_TRACE(jh, "entry");

	/*
	 * Do this first --- it can drop the journal lock, so we want to
	 * make sure that obtaining the committed_data is करोne
	 * atomically wrt. completion of any outstanding commits.
	 */
	err = करो_get_ग_लिखो_access(handle, jh, 1);
	अगर (err)
		जाओ out;

repeat:
	अगर (!jh->b_committed_data)
		committed_data = jbd2_alloc(jh2bh(jh)->b_size,
					    GFP_NOFS|__GFP_NOFAIL);

	spin_lock(&jh->b_state_lock);
	अगर (!jh->b_committed_data) अणु
		/* Copy out the current buffer contents पूर्णांकo the
		 * preserved, committed copy. */
		JBUFFER_TRACE(jh, "generate b_committed data");
		अगर (!committed_data) अणु
			spin_unlock(&jh->b_state_lock);
			जाओ repeat;
		पूर्ण

		jh->b_committed_data = committed_data;
		committed_data = शून्य;
		स_नकल(jh->b_committed_data, bh->b_data, bh->b_size);
	पूर्ण
	spin_unlock(&jh->b_state_lock);
out:
	jbd2_journal_put_journal_head(jh);
	अगर (unlikely(committed_data))
		jbd2_मुक्त(committed_data, bh->b_size);
	वापस err;
पूर्ण

/**
 * jbd2_journal_set_triggers() - Add triggers क्रम commit ग_लिखोout
 * @bh: buffer to trigger on
 * @type: काष्ठा jbd2_buffer_trigger_type containing the trigger(s).
 *
 * Set any triggers on this journal_head.  This is always safe, because
 * triggers क्रम a committing buffer will be saved off, and triggers क्रम
 * a running transaction will match the buffer in that transaction.
 *
 * Call with शून्य to clear the triggers.
 */
व्योम jbd2_journal_set_triggers(काष्ठा buffer_head *bh,
			       काष्ठा jbd2_buffer_trigger_type *type)
अणु
	काष्ठा journal_head *jh = jbd2_journal_grab_journal_head(bh);

	अगर (WARN_ON(!jh))
		वापस;
	jh->b_triggers = type;
	jbd2_journal_put_journal_head(jh);
पूर्ण

व्योम jbd2_buffer_frozen_trigger(काष्ठा journal_head *jh, व्योम *mapped_data,
				काष्ठा jbd2_buffer_trigger_type *triggers)
अणु
	काष्ठा buffer_head *bh = jh2bh(jh);

	अगर (!triggers || !triggers->t_frozen)
		वापस;

	triggers->t_frozen(triggers, bh, mapped_data, bh->b_size);
पूर्ण

व्योम jbd2_buffer_पात_trigger(काष्ठा journal_head *jh,
			       काष्ठा jbd2_buffer_trigger_type *triggers)
अणु
	अगर (!triggers || !triggers->t_पात)
		वापस;

	triggers->t_पात(triggers, jh2bh(jh));
पूर्ण

/**
 * jbd2_journal_dirty_metadata() -  mark a buffer as containing dirty metadata
 * @handle: transaction to add buffer to.
 * @bh: buffer to mark
 *
 * mark dirty metadata which needs to be journaled as part of the current
 * transaction.
 *
 * The buffer must have previously had jbd2_journal_get_ग_लिखो_access()
 * called so that it has a valid journal_head attached to the buffer
 * head.
 *
 * The buffer is placed on the transaction's metadata list and is marked
 * as beदीर्घing to the transaction.
 *
 * Returns error number or 0 on success.
 *
 * Special care needs to be taken अगर the buffer alपढ़ोy beदीर्घs to the
 * current committing transaction (in which हाल we should have frozen
 * data present क्रम that commit).  In that हाल, we करोn't relink the
 * buffer: that only माला_लो करोne when the old transaction finally
 * completes its commit.
 */
पूर्णांक jbd2_journal_dirty_metadata(handle_t *handle, काष्ठा buffer_head *bh)
अणु
	transaction_t *transaction = handle->h_transaction;
	journal_t *journal;
	काष्ठा journal_head *jh;
	पूर्णांक ret = 0;

	अगर (is_handle_पातed(handle))
		वापस -EROFS;
	अगर (!buffer_jbd(bh))
		वापस -EUCLEAN;

	/*
	 * We करोn't grab jh reference here since the buffer must be part
	 * of the running transaction.
	 */
	jh = bh2jh(bh);
	jbd_debug(5, "journal_head %p\n", jh);
	JBUFFER_TRACE(jh, "entry");

	/*
	 * This and the following निश्चितions are unreliable since we may see jh
	 * in inconsistent state unless we grab bh_state lock. But this is
	 * crucial to catch bugs so let's करो a reliable check until the
	 * lockless handling is fully proven.
	 */
	अगर (data_race(jh->b_transaction != transaction &&
	    jh->b_next_transaction != transaction)) अणु
		spin_lock(&jh->b_state_lock);
		J_ASSERT_JH(jh, jh->b_transaction == transaction ||
				jh->b_next_transaction == transaction);
		spin_unlock(&jh->b_state_lock);
	पूर्ण
	अगर (jh->b_modअगरied == 1) अणु
		/* If it's in our transaction it must be in BJ_Metadata list. */
		अगर (data_race(jh->b_transaction == transaction &&
		    jh->b_jlist != BJ_Metadata)) अणु
			spin_lock(&jh->b_state_lock);
			अगर (jh->b_transaction == transaction &&
			    jh->b_jlist != BJ_Metadata)
				pr_err("JBD2: assertion failure: h_type=%u "
				       "h_line_no=%u block_no=%llu jlist=%u\n",
				       handle->h_type, handle->h_line_no,
				       (अचिन्हित दीर्घ दीर्घ) bh->b_blocknr,
				       jh->b_jlist);
			J_ASSERT_JH(jh, jh->b_transaction != transaction ||
					jh->b_jlist == BJ_Metadata);
			spin_unlock(&jh->b_state_lock);
		पूर्ण
		जाओ out;
	पूर्ण

	journal = transaction->t_journal;
	spin_lock(&jh->b_state_lock);

	अगर (jh->b_modअगरied == 0) अणु
		/*
		 * This buffer's got modअगरied and becoming part
		 * of the transaction. This needs to be करोne
		 * once a transaction -bzzz
		 */
		अगर (WARN_ON_ONCE(jbd2_handle_buffer_credits(handle) <= 0)) अणु
			ret = -ENOSPC;
			जाओ out_unlock_bh;
		पूर्ण
		jh->b_modअगरied = 1;
		handle->h_total_credits--;
	पूर्ण

	/*
	 * fastpath, to aव्योम expensive locking.  If this buffer is alपढ़ोy
	 * on the running transaction's metadata list there is nothing to करो.
	 * Nobody can take it off again because there is a handle खोलो.
	 * I _think_ we're OK here with SMP barriers - a mistaken decision will
	 * result in this test being false, so we go in and take the locks.
	 */
	अगर (jh->b_transaction == transaction && jh->b_jlist == BJ_Metadata) अणु
		JBUFFER_TRACE(jh, "fastpath");
		अगर (unlikely(jh->b_transaction !=
			     journal->j_running_transaction)) अणु
			prपूर्णांकk(KERN_ERR "JBD2: %s: "
			       "jh->b_transaction (%llu, %p, %u) != "
			       "journal->j_running_transaction (%p, %u)\n",
			       journal->j_devname,
			       (अचिन्हित दीर्घ दीर्घ) bh->b_blocknr,
			       jh->b_transaction,
			       jh->b_transaction ? jh->b_transaction->t_tid : 0,
			       journal->j_running_transaction,
			       journal->j_running_transaction ?
			       journal->j_running_transaction->t_tid : 0);
			ret = -EINVAL;
		पूर्ण
		जाओ out_unlock_bh;
	पूर्ण

	set_buffer_jbddirty(bh);

	/*
	 * Metadata alपढ़ोy on the current transaction list करोesn't
	 * need to be filed.  Metadata on another transaction's list must
	 * be committing, and will be refiled once the commit completes:
	 * leave it alone क्रम now.
	 */
	अगर (jh->b_transaction != transaction) अणु
		JBUFFER_TRACE(jh, "already on other transaction");
		अगर (unlikely(((jh->b_transaction !=
			       journal->j_committing_transaction)) ||
			     (jh->b_next_transaction != transaction))) अणु
			prपूर्णांकk(KERN_ERR "jbd2_journal_dirty_metadata: %s: "
			       "bad jh for block %llu: "
			       "transaction (%p, %u), "
			       "jh->b_transaction (%p, %u), "
			       "jh->b_next_transaction (%p, %u), jlist %u\n",
			       journal->j_devname,
			       (अचिन्हित दीर्घ दीर्घ) bh->b_blocknr,
			       transaction, transaction->t_tid,
			       jh->b_transaction,
			       jh->b_transaction ?
			       jh->b_transaction->t_tid : 0,
			       jh->b_next_transaction,
			       jh->b_next_transaction ?
			       jh->b_next_transaction->t_tid : 0,
			       jh->b_jlist);
			WARN_ON(1);
			ret = -EINVAL;
		पूर्ण
		/* And this हाल is illegal: we can't reuse another
		 * transaction's data buffer, ever. */
		जाओ out_unlock_bh;
	पूर्ण

	/* That test should have eliminated the following हाल: */
	J_ASSERT_JH(jh, jh->b_frozen_data == शून्य);

	JBUFFER_TRACE(jh, "file as BJ_Metadata");
	spin_lock(&journal->j_list_lock);
	__jbd2_journal_file_buffer(jh, transaction, BJ_Metadata);
	spin_unlock(&journal->j_list_lock);
out_unlock_bh:
	spin_unlock(&jh->b_state_lock);
out:
	JBUFFER_TRACE(jh, "exit");
	वापस ret;
पूर्ण

/**
 * jbd2_journal_क्रमget() - bक्रमget() क्रम potentially-journaled buffers.
 * @handle: transaction handle
 * @bh:     bh to 'forget'
 *
 * We can only करो the bक्रमget अगर there are no commits pending against the
 * buffer.  If the buffer is dirty in the current running transaction we
 * can safely unlink it.
 *
 * bh may not be a journalled buffer at all - it may be a non-JBD
 * buffer which came off the hashtable.  Check क्रम this.
 *
 * Decrements bh->b_count by one.
 *
 * Allow this call even अगर the handle has पातed --- it may be part of
 * the caller's cleanup after an पात.
 */
पूर्णांक jbd2_journal_क्रमget(handle_t *handle, काष्ठा buffer_head *bh)
अणु
	transaction_t *transaction = handle->h_transaction;
	journal_t *journal;
	काष्ठा journal_head *jh;
	पूर्णांक drop_reserve = 0;
	पूर्णांक err = 0;
	पूर्णांक was_modअगरied = 0;

	अगर (is_handle_पातed(handle))
		वापस -EROFS;
	journal = transaction->t_journal;

	BUFFER_TRACE(bh, "entry");

	jh = jbd2_journal_grab_journal_head(bh);
	अगर (!jh) अणु
		__bक्रमget(bh);
		वापस 0;
	पूर्ण

	spin_lock(&jh->b_state_lock);

	/* Critical error: attempting to delete a biपंचांगap buffer, maybe?
	 * Don't करो any jbd operations, and वापस an error. */
	अगर (!J_EXPECT_JH(jh, !jh->b_committed_data,
			 "inconsistent data on disk")) अणु
		err = -EIO;
		जाओ drop;
	पूर्ण

	/* keep track of whether or not this transaction modअगरied us */
	was_modअगरied = jh->b_modअगरied;

	/*
	 * The buffer's going from the transaction, we must drop
	 * all references -bzzz
	 */
	jh->b_modअगरied = 0;

	अगर (jh->b_transaction == transaction) अणु
		J_ASSERT_JH(jh, !jh->b_frozen_data);

		/* If we are क्रमgetting a buffer which is alपढ़ोy part
		 * of this transaction, then we can just drop it from
		 * the transaction immediately. */
		clear_buffer_dirty(bh);
		clear_buffer_jbddirty(bh);

		JBUFFER_TRACE(jh, "belongs to current transaction: unfile");

		/*
		 * we only want to drop a reference अगर this transaction
		 * modअगरied the buffer
		 */
		अगर (was_modअगरied)
			drop_reserve = 1;

		/*
		 * We are no दीर्घer going to journal this buffer.
		 * However, the commit of this transaction is still
		 * important to the buffer: the delete that we are now
		 * processing might obsolete an old log entry, so by
		 * committing, we can satisfy the buffer's checkpoपूर्णांक.
		 *
		 * So, अगर we have a checkpoपूर्णांक on the buffer, we should
		 * now refile the buffer on our BJ_Forget list so that
		 * we know to हटाओ the checkpoपूर्णांक after we commit.
		 */

		spin_lock(&journal->j_list_lock);
		अगर (jh->b_cp_transaction) अणु
			__jbd2_journal_temp_unlink_buffer(jh);
			__jbd2_journal_file_buffer(jh, transaction, BJ_Forget);
		पूर्ण अन्यथा अणु
			__jbd2_journal_unfile_buffer(jh);
			jbd2_journal_put_journal_head(jh);
		पूर्ण
		spin_unlock(&journal->j_list_lock);
	पूर्ण अन्यथा अगर (jh->b_transaction) अणु
		J_ASSERT_JH(jh, (jh->b_transaction ==
				 journal->j_committing_transaction));
		/* However, अगर the buffer is still owned by a prior
		 * (committing) transaction, we can't drop it yet... */
		JBUFFER_TRACE(jh, "belongs to older transaction");
		/* ... but we CAN drop it from the new transaction through
		 * marking the buffer as मुक्तd and set j_next_transaction to
		 * the new transaction, so that not only the commit code
		 * knows it should clear dirty bits when it is करोne with the
		 * buffer, but also the buffer can be checkpoपूर्णांकed only
		 * after the new transaction commits. */

		set_buffer_मुक्तd(bh);

		अगर (!jh->b_next_transaction) अणु
			spin_lock(&journal->j_list_lock);
			jh->b_next_transaction = transaction;
			spin_unlock(&journal->j_list_lock);
		पूर्ण अन्यथा अणु
			J_ASSERT(jh->b_next_transaction == transaction);

			/*
			 * only drop a reference अगर this transaction modअगरied
			 * the buffer
			 */
			अगर (was_modअगरied)
				drop_reserve = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Finally, अगर the buffer is not beदीर्घs to any
		 * transaction, we can just drop it now अगर it has no
		 * checkpoपूर्णांक.
		 */
		spin_lock(&journal->j_list_lock);
		अगर (!jh->b_cp_transaction) अणु
			JBUFFER_TRACE(jh, "belongs to none transaction");
			spin_unlock(&journal->j_list_lock);
			जाओ drop;
		पूर्ण

		/*
		 * Otherwise, अगर the buffer has been written to disk,
		 * it is safe to हटाओ the checkpoपूर्णांक and drop it.
		 */
		अगर (!buffer_dirty(bh)) अणु
			__jbd2_journal_हटाओ_checkpoपूर्णांक(jh);
			spin_unlock(&journal->j_list_lock);
			जाओ drop;
		पूर्ण

		/*
		 * The buffer is still not written to disk, we should
		 * attach this buffer to current transaction so that the
		 * buffer can be checkpoपूर्णांकed only after the current
		 * transaction commits.
		 */
		clear_buffer_dirty(bh);
		__jbd2_journal_file_buffer(jh, transaction, BJ_Forget);
		spin_unlock(&journal->j_list_lock);
	पूर्ण
drop:
	__brअन्यथा(bh);
	spin_unlock(&jh->b_state_lock);
	jbd2_journal_put_journal_head(jh);
	अगर (drop_reserve) अणु
		/* no need to reserve log space क्रम this block -bzzz */
		handle->h_total_credits++;
	पूर्ण
	वापस err;
पूर्ण

/**
 * jbd2_journal_stop() - complete a transaction
 * @handle: transaction to complete.
 *
 * All करोne क्रम a particular handle.
 *
 * There is not much action needed here.  We just वापस any reमुख्यing
 * buffer credits to the transaction and हटाओ the handle.  The only
 * complication is that we need to start a commit operation अगर the
 * fileप्रणाली is marked क्रम synchronous update.
 *
 * jbd2_journal_stop itself will not usually वापस an error, but it may
 * करो so in unusual circumstances.  In particular, expect it to
 * वापस -EIO अगर a jbd2_journal_पात has been executed since the
 * transaction began.
 */
पूर्णांक jbd2_journal_stop(handle_t *handle)
अणु
	transaction_t *transaction = handle->h_transaction;
	journal_t *journal;
	पूर्णांक err = 0, रुको_क्रम_commit = 0;
	tid_t tid;
	pid_t pid;

	अगर (--handle->h_ref > 0) अणु
		jbd_debug(4, "h_ref %d -> %d\n", handle->h_ref + 1,
						 handle->h_ref);
		अगर (is_handle_पातed(handle))
			वापस -EIO;
		वापस 0;
	पूर्ण
	अगर (!transaction) अणु
		/*
		 * Handle is alपढ़ोy detached from the transaction so there is
		 * nothing to करो other than मुक्त the handle.
		 */
		meदो_स्मृति_nofs_restore(handle->saved_alloc_context);
		जाओ मुक्त_and_निकास;
	पूर्ण
	journal = transaction->t_journal;
	tid = transaction->t_tid;

	अगर (is_handle_पातed(handle))
		err = -EIO;

	jbd_debug(4, "Handle %p going down\n", handle);
	trace_jbd2_handle_stats(journal->j_fs_dev->bd_dev,
				tid, handle->h_type, handle->h_line_no,
				jअगरfies - handle->h_start_jअगरfies,
				handle->h_sync, handle->h_requested_credits,
				(handle->h_requested_credits -
				 handle->h_total_credits));

	/*
	 * Implement synchronous transaction batching.  If the handle
	 * was synchronous, करोn't force a commit immediately.  Let's
	 * yield and let another thपढ़ो piggyback onto this
	 * transaction.  Keep करोing that जबतक new thपढ़ोs जारी to
	 * arrive.  It करोesn't cost much - we're about to run a commit
	 * and sleep on IO anyway.  Speeds up many-thपढ़ोed, many-dir
	 * operations by 30x or more...
	 *
	 * We try and optimize the sleep समय against what the
	 * underlying disk can करो, instead of having a अटल sleep
	 * समय.  This is useful क्रम the हाल where our storage is so
	 * fast that it is more optimal to go ahead and क्रमce a flush
	 * and रुको क्रम the transaction to be committed than it is to
	 * रुको क्रम an arbitrary amount of समय क्रम new ग_लिखोrs to
	 * join the transaction.  We achieve this by measuring how
	 * दीर्घ it takes to commit a transaction, and compare it with
	 * how दीर्घ this transaction has been running, and अगर run समय
	 * < commit समय then we sleep क्रम the delta and commit.  This
	 * greatly helps super fast disks that would see slowकरोwns as
	 * more thपढ़ोs started करोing fsyncs.
	 *
	 * But करोn't करो this अगर this process was the most recent one
	 * to perक्रमm a synchronous ग_लिखो.  We करो this to detect the
	 * हाल where a single process is करोing a stream of sync
	 * ग_लिखोs.  No poपूर्णांक in रुकोing क्रम joiners in that हाल.
	 *
	 * Setting max_batch_समय to 0 disables this completely.
	 */
	pid = current->pid;
	अगर (handle->h_sync && journal->j_last_sync_ग_लिखोr != pid &&
	    journal->j_max_batch_समय) अणु
		u64 commit_समय, trans_समय;

		journal->j_last_sync_ग_लिखोr = pid;

		पढ़ो_lock(&journal->j_state_lock);
		commit_समय = journal->j_average_commit_समय;
		पढ़ो_unlock(&journal->j_state_lock);

		trans_समय = kसमय_प्रकारo_ns(kसमय_sub(kसमय_get(),
						   transaction->t_start_समय));

		commit_समय = max_t(u64, commit_समय,
				    1000*journal->j_min_batch_समय);
		commit_समय = min_t(u64, commit_समय,
				    1000*journal->j_max_batch_समय);

		अगर (trans_समय < commit_समय) अणु
			kसमय_प्रकार expires = kसमय_add_ns(kसमय_get(),
						       commit_समय);
			set_current_state(TASK_UNINTERRUPTIBLE);
			schedule_hrसमयout(&expires, HRTIMER_MODE_ABS);
		पूर्ण
	पूर्ण

	अगर (handle->h_sync)
		transaction->t_synchronous_commit = 1;

	/*
	 * If the handle is marked SYNC, we need to set another commit
	 * going!  We also want to क्रमce a commit अगर the transaction is too
	 * old now.
	 */
	अगर (handle->h_sync ||
	    समय_after_eq(jअगरfies, transaction->t_expires)) अणु
		/* Do this even क्रम पातed journals: an पात still
		 * completes the commit thपढ़ो, it just करोesn't ग_लिखो
		 * anything to disk. */

		jbd_debug(2, "transaction too old, requesting commit for "
					"handle %p\n", handle);
		/* This is non-blocking */
		jbd2_log_start_commit(journal, tid);

		/*
		 * Special हाल: JBD2_SYNC synchronous updates require us
		 * to रुको क्रम the commit to complete.
		 */
		अगर (handle->h_sync && !(current->flags & PF_MEMALLOC))
			रुको_क्रम_commit = 1;
	पूर्ण

	/*
	 * Once stop_this_handle() drops t_updates, the transaction could start
	 * committing on us and eventually disappear.  So we must not
	 * dereference transaction poपूर्णांकer again after calling
	 * stop_this_handle().
	 */
	stop_this_handle(handle);

	अगर (रुको_क्रम_commit)
		err = jbd2_log_रुको_commit(journal, tid);

मुक्त_and_निकास:
	अगर (handle->h_rsv_handle)
		jbd2_मुक्त_handle(handle->h_rsv_handle);
	jbd2_मुक्त_handle(handle);
	वापस err;
पूर्ण

/*
 *
 * List management code snippets: various functions क्रम manipulating the
 * transaction buffer lists.
 *
 */

/*
 * Append a buffer to a transaction list, given the transaction's list head
 * poपूर्णांकer.
 *
 * j_list_lock is held.
 *
 * jh->b_state_lock is held.
 */

अटल अंतरभूत व्योम
__blist_add_buffer(काष्ठा journal_head **list, काष्ठा journal_head *jh)
अणु
	अगर (!*list) अणु
		jh->b_tnext = jh->b_tprev = jh;
		*list = jh;
	पूर्ण अन्यथा अणु
		/* Insert at the tail of the list to preserve order */
		काष्ठा journal_head *first = *list, *last = first->b_tprev;
		jh->b_tprev = last;
		jh->b_tnext = first;
		last->b_tnext = first->b_tprev = jh;
	पूर्ण
पूर्ण

/*
 * Remove a buffer from a transaction list, given the transaction's list
 * head poपूर्णांकer.
 *
 * Called with j_list_lock held, and the journal may not be locked.
 *
 * jh->b_state_lock is held.
 */

अटल अंतरभूत व्योम
__blist_del_buffer(काष्ठा journal_head **list, काष्ठा journal_head *jh)
अणु
	अगर (*list == jh) अणु
		*list = jh->b_tnext;
		अगर (*list == jh)
			*list = शून्य;
	पूर्ण
	jh->b_tprev->b_tnext = jh->b_tnext;
	jh->b_tnext->b_tprev = jh->b_tprev;
पूर्ण

/*
 * Remove a buffer from the appropriate transaction list.
 *
 * Note that this function can *change* the value of
 * bh->b_transaction->t_buffers, t_क्रमget, t_shaकरोw_list, t_log_list or
 * t_reserved_list.  If the caller is holding onto a copy of one of these
 * poपूर्णांकers, it could go bad.  Generally the caller needs to re-पढ़ो the
 * poपूर्णांकer from the transaction_t.
 *
 * Called under j_list_lock.
 */
अटल व्योम __jbd2_journal_temp_unlink_buffer(काष्ठा journal_head *jh)
अणु
	काष्ठा journal_head **list = शून्य;
	transaction_t *transaction;
	काष्ठा buffer_head *bh = jh2bh(jh);

	lockdep_निश्चित_held(&jh->b_state_lock);
	transaction = jh->b_transaction;
	अगर (transaction)
		निश्चित_spin_locked(&transaction->t_journal->j_list_lock);

	J_ASSERT_JH(jh, jh->b_jlist < BJ_Types);
	अगर (jh->b_jlist != BJ_None)
		J_ASSERT_JH(jh, transaction != शून्य);

	चयन (jh->b_jlist) अणु
	हाल BJ_None:
		वापस;
	हाल BJ_Metadata:
		transaction->t_nr_buffers--;
		J_ASSERT_JH(jh, transaction->t_nr_buffers >= 0);
		list = &transaction->t_buffers;
		अवरोध;
	हाल BJ_Forget:
		list = &transaction->t_क्रमget;
		अवरोध;
	हाल BJ_Shaकरोw:
		list = &transaction->t_shaकरोw_list;
		अवरोध;
	हाल BJ_Reserved:
		list = &transaction->t_reserved_list;
		अवरोध;
	पूर्ण

	__blist_del_buffer(list, jh);
	jh->b_jlist = BJ_None;
	अगर (transaction && is_journal_पातed(transaction->t_journal))
		clear_buffer_jbddirty(bh);
	अन्यथा अगर (test_clear_buffer_jbddirty(bh))
		mark_buffer_dirty(bh);	/* Expose it to the VM */
पूर्ण

/*
 * Remove buffer from all transactions. The caller is responsible क्रम dropping
 * the jh reference that beदीर्घed to the transaction.
 *
 * Called with bh_state lock and j_list_lock
 */
अटल व्योम __jbd2_journal_unfile_buffer(काष्ठा journal_head *jh)
अणु
	J_ASSERT_JH(jh, jh->b_transaction != शून्य);
	J_ASSERT_JH(jh, jh->b_next_transaction == शून्य);

	__jbd2_journal_temp_unlink_buffer(jh);
	jh->b_transaction = शून्य;
पूर्ण

व्योम jbd2_journal_unfile_buffer(journal_t *journal, काष्ठा journal_head *jh)
अणु
	काष्ठा buffer_head *bh = jh2bh(jh);

	/* Get reference so that buffer cannot be मुक्तd beक्रमe we unlock it */
	get_bh(bh);
	spin_lock(&jh->b_state_lock);
	spin_lock(&journal->j_list_lock);
	__jbd2_journal_unfile_buffer(jh);
	spin_unlock(&journal->j_list_lock);
	spin_unlock(&jh->b_state_lock);
	jbd2_journal_put_journal_head(jh);
	__brअन्यथा(bh);
पूर्ण

/*
 * Called from jbd2_journal_try_to_मुक्त_buffers().
 *
 * Called under jh->b_state_lock
 */
अटल व्योम
__journal_try_to_मुक्त_buffer(journal_t *journal, काष्ठा buffer_head *bh)
अणु
	काष्ठा journal_head *jh;

	jh = bh2jh(bh);

	अगर (buffer_locked(bh) || buffer_dirty(bh))
		जाओ out;

	अगर (jh->b_next_transaction != शून्य || jh->b_transaction != शून्य)
		जाओ out;

	spin_lock(&journal->j_list_lock);
	अगर (jh->b_cp_transaction != शून्य) अणु
		/* written-back checkpoपूर्णांकed metadata buffer */
		JBUFFER_TRACE(jh, "remove from checkpoint list");
		__jbd2_journal_हटाओ_checkpoपूर्णांक(jh);
	पूर्ण
	spin_unlock(&journal->j_list_lock);
out:
	वापस;
पूर्ण

/**
 * jbd2_journal_try_to_मुक्त_buffers() - try to मुक्त page buffers.
 * @journal: journal क्रम operation
 * @page: to try and मुक्त
 *
 * For all the buffers on this page,
 * अगर they are fully written out ordered data, move them onto BUF_CLEAN
 * so try_to_मुक्त_buffers() can reap them.
 *
 * This function वापसs non-zero अगर we wish try_to_मुक्त_buffers()
 * to be called. We करो this अगर the page is releasable by try_to_मुक्त_buffers().
 * We also करो it अगर the page has locked or dirty buffers and the caller wants
 * us to perक्रमm sync or async ग_लिखोout.
 *
 * This complicates JBD locking somewhat.  We aren't रक्षित by the
 * BKL here.  We wish to हटाओ the buffer from its committing or
 * running transaction's ->t_datalist via __jbd2_journal_unfile_buffer.
 *
 * This may *change* the value of transaction_t->t_datalist, so anyone
 * who looks at t_datalist needs to lock against this function.
 *
 * Even worse, someone may be करोing a jbd2_journal_dirty_data on this
 * buffer.  So we need to lock against that.  jbd2_journal_dirty_data()
 * will come out of the lock with the buffer dirty, which makes it
 * ineligible क्रम release here.
 *
 * Who अन्यथा is affected by this?  hmm...  Really the only contender
 * is करो_get_ग_लिखो_access() - it could be looking at the buffer जबतक
 * journal_try_to_मुक्त_buffer() is changing its state.  But that
 * cannot happen because we never पुनः_स्मृतिate मुक्तd data as metadata
 * जबतक the data is part of a transaction.  Yes?
 *
 * Return 0 on failure, 1 on success
 */
पूर्णांक jbd2_journal_try_to_मुक्त_buffers(journal_t *journal, काष्ठा page *page)
अणु
	काष्ठा buffer_head *head;
	काष्ठा buffer_head *bh;
	bool has_ग_लिखो_io_error = false;
	पूर्णांक ret = 0;

	J_ASSERT(PageLocked(page));

	head = page_buffers(page);
	bh = head;
	करो अणु
		काष्ठा journal_head *jh;

		/*
		 * We take our own ref against the journal_head here to aव्योम
		 * having to add tons of locking around each instance of
		 * jbd2_journal_put_journal_head().
		 */
		jh = jbd2_journal_grab_journal_head(bh);
		अगर (!jh)
			जारी;

		spin_lock(&jh->b_state_lock);
		__journal_try_to_मुक्त_buffer(journal, bh);
		spin_unlock(&jh->b_state_lock);
		jbd2_journal_put_journal_head(jh);
		अगर (buffer_jbd(bh))
			जाओ busy;

		/*
		 * If we मुक्त a metadata buffer which has been failed to
		 * ग_लिखो out, the jbd2 checkpoपूर्णांक procedure will not detect
		 * this failure and may lead to fileप्रणाली inconsistency
		 * after cleanup journal tail.
		 */
		अगर (buffer_ग_लिखो_io_error(bh)) अणु
			pr_err("JBD2: Error while async write back metadata bh %llu.",
			       (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
			has_ग_लिखो_io_error = true;
		पूर्ण
	पूर्ण जबतक ((bh = bh->b_this_page) != head);

	ret = try_to_मुक्त_buffers(page);

busy:
	अगर (has_ग_लिखो_io_error)
		jbd2_journal_पात(journal, -EIO);

	वापस ret;
पूर्ण

/*
 * This buffer is no दीर्घer needed.  If it is on an older transaction's
 * checkpoपूर्णांक list we need to record it on this transaction's क्रमget list
 * to pin this buffer (and hence its checkpoपूर्णांकing transaction) करोwn until
 * this transaction commits.  If the buffer isn't on a checkpoपूर्णांक list, we
 * release it.
 * Returns non-zero अगर JBD no दीर्घer has an पूर्णांकerest in the buffer.
 *
 * Called under j_list_lock.
 *
 * Called under jh->b_state_lock.
 */
अटल पूर्णांक __dispose_buffer(काष्ठा journal_head *jh, transaction_t *transaction)
अणु
	पूर्णांक may_मुक्त = 1;
	काष्ठा buffer_head *bh = jh2bh(jh);

	अगर (jh->b_cp_transaction) अणु
		JBUFFER_TRACE(jh, "on running+cp transaction");
		__jbd2_journal_temp_unlink_buffer(jh);
		/*
		 * We करोn't want to ग_लिखो the buffer anymore, clear the
		 * bit so that we करोn't confuse checks in
		 * __journal_file_buffer
		 */
		clear_buffer_dirty(bh);
		__jbd2_journal_file_buffer(jh, transaction, BJ_Forget);
		may_मुक्त = 0;
	पूर्ण अन्यथा अणु
		JBUFFER_TRACE(jh, "on running transaction");
		__jbd2_journal_unfile_buffer(jh);
		jbd2_journal_put_journal_head(jh);
	पूर्ण
	वापस may_मुक्त;
पूर्ण

/*
 * jbd2_journal_invalidatepage
 *
 * This code is tricky.  It has a number of हालs to deal with.
 *
 * There are two invariants which this code relies on:
 *
 * i_size must be updated on disk beक्रमe we start calling invalidatepage on the
 * data.
 *
 *  This is करोne in ext3 by defining an ext3_setattr method which
 *  updates i_size beक्रमe truncate माला_लो going.  By मुख्यtaining this
 *  invariant, we can be sure that it is safe to throw away any buffers
 *  attached to the current transaction: once the transaction commits,
 *  we know that the data will not be needed.
 *
 *  Note however that we can *not* throw away data beदीर्घing to the
 *  previous, committing transaction!
 *
 * Any disk blocks which *are* part of the previous, committing
 * transaction (and which thereक्रमe cannot be discarded immediately) are
 * not going to be reused in the new running transaction
 *
 *  The biपंचांगap committed_data images guarantee this: any block which is
 *  allocated in one transaction and हटाओd in the next will be marked
 *  as in-use in the committed_data biपंचांगap, so cannot be reused until
 *  the next transaction to delete the block commits.  This means that
 *  leaving committing buffers dirty is quite safe: the disk blocks
 *  cannot be पुनः_स्मृतिated to a dअगरferent file and so buffer aliasing is
 *  not possible.
 *
 *
 * The above applies मुख्यly to ordered data mode.  In ग_लिखोback mode we
 * करोn't make guarantees about the order in which data hits disk --- in
 * particular we करोn't guarantee that new dirty data is flushed beक्रमe
 * transaction commit --- so it is always safe just to discard data
 * immediately in that mode.  --sct
 */

/*
 * The journal_unmap_buffer helper function वापसs zero अगर the buffer
 * concerned reमुख्यs pinned as an anonymous buffer beदीर्घing to an older
 * transaction.
 *
 * We're outside-transaction here.  Either or both of j_running_transaction
 * and j_committing_transaction may be शून्य.
 */
अटल पूर्णांक journal_unmap_buffer(journal_t *journal, काष्ठा buffer_head *bh,
				पूर्णांक partial_page)
अणु
	transaction_t *transaction;
	काष्ठा journal_head *jh;
	पूर्णांक may_मुक्त = 1;

	BUFFER_TRACE(bh, "entry");

	/*
	 * It is safe to proceed here without the j_list_lock because the
	 * buffers cannot be stolen by try_to_मुक्त_buffers as दीर्घ as we are
	 * holding the page lock. --sct
	 */

	jh = jbd2_journal_grab_journal_head(bh);
	अगर (!jh)
		जाओ zap_buffer_unlocked;

	/* OK, we have data buffer in journaled mode */
	ग_लिखो_lock(&journal->j_state_lock);
	spin_lock(&jh->b_state_lock);
	spin_lock(&journal->j_list_lock);

	/*
	 * We cannot हटाओ the buffer from checkpoपूर्णांक lists until the
	 * transaction adding inode to orphan list (let's call it T)
	 * is committed.  Otherwise अगर the transaction changing the
	 * buffer would be cleaned from the journal beक्रमe T is
	 * committed, a crash will cause that the correct contents of
	 * the buffer will be lost.  On the other hand we have to
	 * clear the buffer dirty bit at latest at the moment when the
	 * transaction marking the buffer as मुक्तd in the fileप्रणाली
	 * काष्ठाures is committed because from that moment on the
	 * block can be पुनः_स्मृतिated and used by a dअगरferent page.
	 * Since the block hasn't been मुक्तd yet but the inode has
	 * alपढ़ोy been added to orphan list, it is safe क्रम us to add
	 * the buffer to BJ_Forget list of the newest transaction.
	 *
	 * Also we have to clear buffer_mapped flag of a truncated buffer
	 * because the buffer_head may be attached to the page straddling
	 * i_size (can happen only when blocksize < pagesize) and thus the
	 * buffer_head can be reused when the file is extended again. So we end
	 * up keeping around invalidated buffers attached to transactions'
	 * BJ_Forget list just to stop checkpoपूर्णांकing code from cleaning up
	 * the transaction this buffer was modअगरied in.
	 */
	transaction = jh->b_transaction;
	अगर (transaction == शून्य) अणु
		/* First हाल: not on any transaction.  If it
		 * has no checkpoपूर्णांक link, then we can zap it:
		 * it's a writeback-mode buffer so we don't care
		 * अगर it hits disk safely. */
		अगर (!jh->b_cp_transaction) अणु
			JBUFFER_TRACE(jh, "not on any transaction: zap");
			जाओ zap_buffer;
		पूर्ण

		अगर (!buffer_dirty(bh)) अणु
			/* bdflush has written it.  We can drop it now */
			__jbd2_journal_हटाओ_checkpoपूर्णांक(jh);
			जाओ zap_buffer;
		पूर्ण

		/* OK, it must be in the journal but still not
		 * written fully to disk: it's metadata or
		 * journaled data... */

		अगर (journal->j_running_transaction) अणु
			/* ... and once the current transaction has
			 * committed, the buffer won't be needed any
			 * दीर्घer. */
			JBUFFER_TRACE(jh, "checkpointed: add to BJ_Forget");
			may_मुक्त = __dispose_buffer(jh,
					journal->j_running_transaction);
			जाओ zap_buffer;
		पूर्ण अन्यथा अणु
			/* There is no currently-running transaction. So the
			 * orphan record which we wrote क्रम this file must have
			 * passed पूर्णांकo commit.  We must attach this buffer to
			 * the committing transaction, अगर it exists. */
			अगर (journal->j_committing_transaction) अणु
				JBUFFER_TRACE(jh, "give to committing trans");
				may_मुक्त = __dispose_buffer(jh,
					journal->j_committing_transaction);
				जाओ zap_buffer;
			पूर्ण अन्यथा अणु
				/* The orphan record's transaction has
				 * committed.  We can cleanse this buffer */
				clear_buffer_jbddirty(bh);
				__jbd2_journal_हटाओ_checkpoपूर्णांक(jh);
				जाओ zap_buffer;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (transaction == journal->j_committing_transaction) अणु
		JBUFFER_TRACE(jh, "on committing transaction");
		/*
		 * The buffer is committing, we simply cannot touch
		 * it. If the page is straddling i_size we have to रुको
		 * क्रम commit and try again.
		 */
		अगर (partial_page) अणु
			spin_unlock(&journal->j_list_lock);
			spin_unlock(&jh->b_state_lock);
			ग_लिखो_unlock(&journal->j_state_lock);
			jbd2_journal_put_journal_head(jh);
			वापस -EBUSY;
		पूर्ण
		/*
		 * OK, buffer won't be reachable after truncate. We just clear
		 * b_modअगरied to not confuse transaction credit accounting, and
		 * set j_next_transaction to the running transaction (अगर there
		 * is one) and mark buffer as मुक्तd so that commit code knows
		 * it should clear dirty bits when it is करोne with the buffer.
		 */
		set_buffer_मुक्तd(bh);
		अगर (journal->j_running_transaction && buffer_jbddirty(bh))
			jh->b_next_transaction = journal->j_running_transaction;
		jh->b_modअगरied = 0;
		spin_unlock(&journal->j_list_lock);
		spin_unlock(&jh->b_state_lock);
		ग_लिखो_unlock(&journal->j_state_lock);
		jbd2_journal_put_journal_head(jh);
		वापस 0;
	पूर्ण अन्यथा अणु
		/* Good, the buffer beदीर्घs to the running transaction.
		 * We are writing our own transaction's data, not any
		 * previous one's, so it is safe to throw it away
		 * (remember that we expect the fileप्रणाली to have set
		 * i_size alपढ़ोy क्रम this truncate so recovery will not
		 * expose the disk blocks we are discarding here.) */
		J_ASSERT_JH(jh, transaction == journal->j_running_transaction);
		JBUFFER_TRACE(jh, "on running transaction");
		may_मुक्त = __dispose_buffer(jh, transaction);
	पूर्ण

zap_buffer:
	/*
	 * This is tricky. Although the buffer is truncated, it may be reused
	 * अगर blocksize < pagesize and it is attached to the page straddling
	 * खातापूर्ण. Since the buffer might have been added to BJ_Forget list of the
	 * running transaction, journal_get_ग_लिखो_access() won't clear
	 * b_modअगरied and credit accounting माला_लो confused. So clear b_modअगरied
	 * here.
	 */
	jh->b_modअगरied = 0;
	spin_unlock(&journal->j_list_lock);
	spin_unlock(&jh->b_state_lock);
	ग_लिखो_unlock(&journal->j_state_lock);
	jbd2_journal_put_journal_head(jh);
zap_buffer_unlocked:
	clear_buffer_dirty(bh);
	J_ASSERT_BH(bh, !buffer_jbddirty(bh));
	clear_buffer_mapped(bh);
	clear_buffer_req(bh);
	clear_buffer_new(bh);
	clear_buffer_delay(bh);
	clear_buffer_unwritten(bh);
	bh->b_bdev = शून्य;
	वापस may_मुक्त;
पूर्ण

/**
 * jbd2_journal_invalidatepage()
 * @journal: journal to use क्रम flush...
 * @page:    page to flush
 * @offset:  start of the range to invalidate
 * @length:  length of the range to invalidate
 *
 * Reap page buffers containing data after in the specअगरied range in page.
 * Can वापस -EBUSY अगर buffers are part of the committing transaction and
 * the page is straddling i_size. Caller then has to रुको क्रम current commit
 * and try again.
 */
पूर्णांक jbd2_journal_invalidatepage(journal_t *journal,
				काष्ठा page *page,
				अचिन्हित पूर्णांक offset,
				अचिन्हित पूर्णांक length)
अणु
	काष्ठा buffer_head *head, *bh, *next;
	अचिन्हित पूर्णांक stop = offset + length;
	अचिन्हित पूर्णांक curr_off = 0;
	पूर्णांक partial_page = (offset || length < PAGE_SIZE);
	पूर्णांक may_मुक्त = 1;
	पूर्णांक ret = 0;

	अगर (!PageLocked(page))
		BUG();
	अगर (!page_has_buffers(page))
		वापस 0;

	BUG_ON(stop > PAGE_SIZE || stop < length);

	/* We will potentially be playing with lists other than just the
	 * data lists (especially क्रम journaled data mode), so be
	 * cautious in our locking. */

	head = bh = page_buffers(page);
	करो अणु
		अचिन्हित पूर्णांक next_off = curr_off + bh->b_size;
		next = bh->b_this_page;

		अगर (next_off > stop)
			वापस 0;

		अगर (offset <= curr_off) अणु
			/* This block is wholly outside the truncation poपूर्णांक */
			lock_buffer(bh);
			ret = journal_unmap_buffer(journal, bh, partial_page);
			unlock_buffer(bh);
			अगर (ret < 0)
				वापस ret;
			may_मुक्त &= ret;
		पूर्ण
		curr_off = next_off;
		bh = next;

	पूर्ण जबतक (bh != head);

	अगर (!partial_page) अणु
		अगर (may_मुक्त && try_to_मुक्त_buffers(page))
			J_ASSERT(!page_has_buffers(page));
	पूर्ण
	वापस 0;
पूर्ण

/*
 * File a buffer on the given transaction list.
 */
व्योम __jbd2_journal_file_buffer(काष्ठा journal_head *jh,
			transaction_t *transaction, पूर्णांक jlist)
अणु
	काष्ठा journal_head **list = शून्य;
	पूर्णांक was_dirty = 0;
	काष्ठा buffer_head *bh = jh2bh(jh);

	lockdep_निश्चित_held(&jh->b_state_lock);
	निश्चित_spin_locked(&transaction->t_journal->j_list_lock);

	J_ASSERT_JH(jh, jh->b_jlist < BJ_Types);
	J_ASSERT_JH(jh, jh->b_transaction == transaction ||
				jh->b_transaction == शून्य);

	अगर (jh->b_transaction && jh->b_jlist == jlist)
		वापस;

	अगर (jlist == BJ_Metadata || jlist == BJ_Reserved ||
	    jlist == BJ_Shaकरोw || jlist == BJ_Forget) अणु
		/*
		 * For metadata buffers, we track dirty bit in buffer_jbddirty
		 * instead of buffer_dirty. We should not see a dirty bit set
		 * here because we clear it in करो_get_ग_लिखो_access but e.g.
		 * tune2fs can modअगरy the sb and set the dirty bit at any समय
		 * so we try to gracefully handle that.
		 */
		अगर (buffer_dirty(bh))
			warn_dirty_buffer(bh);
		अगर (test_clear_buffer_dirty(bh) ||
		    test_clear_buffer_jbddirty(bh))
			was_dirty = 1;
	पूर्ण

	अगर (jh->b_transaction)
		__jbd2_journal_temp_unlink_buffer(jh);
	अन्यथा
		jbd2_journal_grab_journal_head(bh);
	jh->b_transaction = transaction;

	चयन (jlist) अणु
	हाल BJ_None:
		J_ASSERT_JH(jh, !jh->b_committed_data);
		J_ASSERT_JH(jh, !jh->b_frozen_data);
		वापस;
	हाल BJ_Metadata:
		transaction->t_nr_buffers++;
		list = &transaction->t_buffers;
		अवरोध;
	हाल BJ_Forget:
		list = &transaction->t_क्रमget;
		अवरोध;
	हाल BJ_Shaकरोw:
		list = &transaction->t_shaकरोw_list;
		अवरोध;
	हाल BJ_Reserved:
		list = &transaction->t_reserved_list;
		अवरोध;
	पूर्ण

	__blist_add_buffer(list, jh);
	jh->b_jlist = jlist;

	अगर (was_dirty)
		set_buffer_jbddirty(bh);
पूर्ण

व्योम jbd2_journal_file_buffer(काष्ठा journal_head *jh,
				transaction_t *transaction, पूर्णांक jlist)
अणु
	spin_lock(&jh->b_state_lock);
	spin_lock(&transaction->t_journal->j_list_lock);
	__jbd2_journal_file_buffer(jh, transaction, jlist);
	spin_unlock(&transaction->t_journal->j_list_lock);
	spin_unlock(&jh->b_state_lock);
पूर्ण

/*
 * Remove a buffer from its current buffer list in preparation क्रम
 * dropping it from its current transaction entirely.  If the buffer has
 * alपढ़ोy started to be used by a subsequent transaction, refile the
 * buffer on that transaction's metadata list.
 *
 * Called under j_list_lock
 * Called under jh->b_state_lock
 *
 * When this function वापसs true, there's no next transaction to refile to
 * and the caller has to drop jh reference through
 * jbd2_journal_put_journal_head().
 */
bool __jbd2_journal_refile_buffer(काष्ठा journal_head *jh)
अणु
	पूर्णांक was_dirty, jlist;
	काष्ठा buffer_head *bh = jh2bh(jh);

	lockdep_निश्चित_held(&jh->b_state_lock);
	अगर (jh->b_transaction)
		निश्चित_spin_locked(&jh->b_transaction->t_journal->j_list_lock);

	/* If the buffer is now unused, just drop it. */
	अगर (jh->b_next_transaction == शून्य) अणु
		__jbd2_journal_unfile_buffer(jh);
		वापस true;
	पूर्ण

	/*
	 * It has been modअगरied by a later transaction: add it to the new
	 * transaction's metadata list.
	 */

	was_dirty = test_clear_buffer_jbddirty(bh);
	__jbd2_journal_temp_unlink_buffer(jh);

	/*
	 * b_transaction must be set, otherwise the new b_transaction won't
	 * be holding jh reference
	 */
	J_ASSERT_JH(jh, jh->b_transaction != शून्य);

	/*
	 * We set b_transaction here because b_next_transaction will inherit
	 * our jh reference and thus __jbd2_journal_file_buffer() must not
	 * take a new one.
	 */
	WRITE_ONCE(jh->b_transaction, jh->b_next_transaction);
	WRITE_ONCE(jh->b_next_transaction, शून्य);
	अगर (buffer_मुक्तd(bh))
		jlist = BJ_Forget;
	अन्यथा अगर (jh->b_modअगरied)
		jlist = BJ_Metadata;
	अन्यथा
		jlist = BJ_Reserved;
	__jbd2_journal_file_buffer(jh, jh->b_transaction, jlist);
	J_ASSERT_JH(jh, jh->b_transaction->t_state == T_RUNNING);

	अगर (was_dirty)
		set_buffer_jbddirty(bh);
	वापस false;
पूर्ण

/*
 * __jbd2_journal_refile_buffer() with necessary locking added. We take our
 * bh reference so that we can safely unlock bh.
 *
 * The jh and bh may be मुक्तd by this call.
 */
व्योम jbd2_journal_refile_buffer(journal_t *journal, काष्ठा journal_head *jh)
अणु
	bool drop;

	spin_lock(&jh->b_state_lock);
	spin_lock(&journal->j_list_lock);
	drop = __jbd2_journal_refile_buffer(jh);
	spin_unlock(&jh->b_state_lock);
	spin_unlock(&journal->j_list_lock);
	अगर (drop)
		jbd2_journal_put_journal_head(jh);
पूर्ण

/*
 * File inode in the inode list of the handle's transaction
 */
अटल पूर्णांक jbd2_journal_file_inode(handle_t *handle, काष्ठा jbd2_inode *jinode,
		अचिन्हित दीर्घ flags, loff_t start_byte, loff_t end_byte)
अणु
	transaction_t *transaction = handle->h_transaction;
	journal_t *journal;

	अगर (is_handle_पातed(handle))
		वापस -EROFS;
	journal = transaction->t_journal;

	jbd_debug(4, "Adding inode %lu, tid:%d\n", jinode->i_vfs_inode->i_ino,
			transaction->t_tid);

	spin_lock(&journal->j_list_lock);
	jinode->i_flags |= flags;

	अगर (jinode->i_dirty_end) अणु
		jinode->i_dirty_start = min(jinode->i_dirty_start, start_byte);
		jinode->i_dirty_end = max(jinode->i_dirty_end, end_byte);
	पूर्ण अन्यथा अणु
		jinode->i_dirty_start = start_byte;
		jinode->i_dirty_end = end_byte;
	पूर्ण

	/* Is inode alपढ़ोy attached where we need it? */
	अगर (jinode->i_transaction == transaction ||
	    jinode->i_next_transaction == transaction)
		जाओ करोne;

	/*
	 * We only ever set this variable to 1 so the test is safe. Since
	 * t_need_data_flush is likely to be set, we करो the test to save some
	 * cacheline bouncing
	 */
	अगर (!transaction->t_need_data_flush)
		transaction->t_need_data_flush = 1;
	/* On some dअगरferent transaction's list - should be
	 * the committing one */
	अगर (jinode->i_transaction) अणु
		J_ASSERT(jinode->i_next_transaction == शून्य);
		J_ASSERT(jinode->i_transaction ==
					journal->j_committing_transaction);
		jinode->i_next_transaction = transaction;
		जाओ करोne;
	पूर्ण
	/* Not on any transaction list... */
	J_ASSERT(!jinode->i_next_transaction);
	jinode->i_transaction = transaction;
	list_add(&jinode->i_list, &transaction->t_inode_list);
करोne:
	spin_unlock(&journal->j_list_lock);

	वापस 0;
पूर्ण

पूर्णांक jbd2_journal_inode_ranged_ग_लिखो(handle_t *handle,
		काष्ठा jbd2_inode *jinode, loff_t start_byte, loff_t length)
अणु
	वापस jbd2_journal_file_inode(handle, jinode,
			JI_WRITE_DATA | JI_WAIT_DATA, start_byte,
			start_byte + length - 1);
पूर्ण

पूर्णांक jbd2_journal_inode_ranged_रुको(handle_t *handle, काष्ठा jbd2_inode *jinode,
		loff_t start_byte, loff_t length)
अणु
	वापस jbd2_journal_file_inode(handle, jinode, JI_WAIT_DATA,
			start_byte, start_byte + length - 1);
पूर्ण

/*
 * File truncate and transaction commit पूर्णांकeract with each other in a
 * non-trivial way.  If a transaction writing data block A is
 * committing, we cannot discard the data by truncate until we have
 * written them.  Otherwise अगर we crashed after the transaction with
 * ग_लिखो has committed but beक्रमe the transaction with truncate has
 * committed, we could see stale data in block A.  This function is a
 * helper to solve this problem.  It starts ग_लिखोout of the truncated
 * part in हाल it is in the committing transaction.
 *
 * Fileप्रणाली code must call this function when inode is journaled in
 * ordered mode beक्रमe truncation happens and after the inode has been
 * placed on orphan list with the new inode size. The second condition
 * aव्योमs the race that someone ग_लिखोs new data and we start
 * committing the transaction after this function has been called but
 * beक्रमe a transaction क्रम truncate is started (and furthermore it
 * allows us to optimize the हाल where the addition to orphan list
 * happens in the same transaction as ग_लिखो --- we करोn't have to ग_लिखो
 * any data in such हाल).
 */
पूर्णांक jbd2_journal_begin_ordered_truncate(journal_t *journal,
					काष्ठा jbd2_inode *jinode,
					loff_t new_size)
अणु
	transaction_t *inode_trans, *commit_trans;
	पूर्णांक ret = 0;

	/* This is a quick check to aव्योम locking अगर not necessary */
	अगर (!jinode->i_transaction)
		जाओ out;
	/* Locks are here just to क्रमce पढ़ोing of recent values, it is
	 * enough that the transaction was not committing beक्रमe we started
	 * a transaction adding the inode to orphan list */
	पढ़ो_lock(&journal->j_state_lock);
	commit_trans = journal->j_committing_transaction;
	पढ़ो_unlock(&journal->j_state_lock);
	spin_lock(&journal->j_list_lock);
	inode_trans = jinode->i_transaction;
	spin_unlock(&journal->j_list_lock);
	अगर (inode_trans == commit_trans) अणु
		ret = filemap_fdataग_लिखो_range(jinode->i_vfs_inode->i_mapping,
			new_size, Lदीर्घ_उच्च);
		अगर (ret)
			jbd2_journal_पात(journal, ret);
	पूर्ण
out:
	वापस ret;
पूर्ण
