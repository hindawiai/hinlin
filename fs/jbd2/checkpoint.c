<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * linux/fs/jbd2/checkpoपूर्णांक.c
 *
 * Written by Stephen C. Tweedie <sct@redhat.com>, 1999
 *
 * Copyright 1999 Red Hat Software --- All Rights Reserved
 *
 * Checkpoपूर्णांक routines क्रम the generic fileप्रणाली journaling code.
 * Part of the ext2fs journaling प्रणाली.
 *
 * Checkpoपूर्णांकing is the process of ensuring that a section of the log is
 * committed fully to disk, so that that portion of the log can be
 * reused.
 */

#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/jbd2.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <trace/events/jbd2.h>

/*
 * Unlink a buffer from a transaction checkpoपूर्णांक list.
 *
 * Called with j_list_lock held.
 */
अटल अंतरभूत व्योम __buffer_unlink_first(काष्ठा journal_head *jh)
अणु
	transaction_t *transaction = jh->b_cp_transaction;

	jh->b_cpnext->b_cpprev = jh->b_cpprev;
	jh->b_cpprev->b_cpnext = jh->b_cpnext;
	अगर (transaction->t_checkpoपूर्णांक_list == jh) अणु
		transaction->t_checkpoपूर्णांक_list = jh->b_cpnext;
		अगर (transaction->t_checkpoपूर्णांक_list == jh)
			transaction->t_checkpoपूर्णांक_list = शून्य;
	पूर्ण
पूर्ण

/*
 * Unlink a buffer from a transaction checkpoपूर्णांक(io) list.
 *
 * Called with j_list_lock held.
 */
अटल अंतरभूत व्योम __buffer_unlink(काष्ठा journal_head *jh)
अणु
	transaction_t *transaction = jh->b_cp_transaction;

	__buffer_unlink_first(jh);
	अगर (transaction->t_checkpoपूर्णांक_io_list == jh) अणु
		transaction->t_checkpoपूर्णांक_io_list = jh->b_cpnext;
		अगर (transaction->t_checkpoपूर्णांक_io_list == jh)
			transaction->t_checkpoपूर्णांक_io_list = शून्य;
	पूर्ण
पूर्ण

/*
 * Move a buffer from the checkpoपूर्णांक list to the checkpoपूर्णांक io list
 *
 * Called with j_list_lock held
 */
अटल अंतरभूत व्योम __buffer_relink_io(काष्ठा journal_head *jh)
अणु
	transaction_t *transaction = jh->b_cp_transaction;

	__buffer_unlink_first(jh);

	अगर (!transaction->t_checkpoपूर्णांक_io_list) अणु
		jh->b_cpnext = jh->b_cpprev = jh;
	पूर्ण अन्यथा अणु
		jh->b_cpnext = transaction->t_checkpoपूर्णांक_io_list;
		jh->b_cpprev = transaction->t_checkpoपूर्णांक_io_list->b_cpprev;
		jh->b_cpprev->b_cpnext = jh;
		jh->b_cpnext->b_cpprev = jh;
	पूर्ण
	transaction->t_checkpoपूर्णांक_io_list = jh;
पूर्ण

/*
 * Try to release a checkpoपूर्णांकed buffer from its transaction.
 * Returns 1 अगर we released it and 2 अगर we also released the
 * whole transaction.
 *
 * Requires j_list_lock
 */
अटल पूर्णांक __try_to_मुक्त_cp_buf(काष्ठा journal_head *jh)
अणु
	पूर्णांक ret = 0;
	काष्ठा buffer_head *bh = jh2bh(jh);

	अगर (jh->b_transaction == शून्य && !buffer_locked(bh) &&
	    !buffer_dirty(bh) && !buffer_ग_लिखो_io_error(bh)) अणु
		JBUFFER_TRACE(jh, "remove from checkpoint list");
		ret = __jbd2_journal_हटाओ_checkpoपूर्णांक(jh) + 1;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * __jbd2_log_रुको_क्रम_space: रुको until there is space in the journal.
 *
 * Called under j-state_lock *only*.  It will be unlocked अगर we have to रुको
 * क्रम a checkpoपूर्णांक to मुक्त up some space in the log.
 */
व्योम __jbd2_log_रुको_क्रम_space(journal_t *journal)
__acquires(&journal->j_state_lock)
__releases(&journal->j_state_lock)
अणु
	पूर्णांक nblocks, space_left;
	/* निश्चित_spin_locked(&journal->j_state_lock); */

	nblocks = journal->j_max_transaction_buffers;
	जबतक (jbd2_log_space_left(journal) < nblocks) अणु
		ग_लिखो_unlock(&journal->j_state_lock);
		mutex_lock_io(&journal->j_checkpoपूर्णांक_mutex);

		/*
		 * Test again, another process may have checkpoपूर्णांकed जबतक we
		 * were रुकोing क्रम the checkpoपूर्णांक lock. If there are no
		 * transactions पढ़ोy to be checkpoपूर्णांकed, try to recover
		 * journal space by calling cleanup_journal_tail(), and अगर
		 * that करोesn't work, by रुकोing क्रम the currently committing
		 * transaction to complete.  If there is असलolutely no way
		 * to make progress, this is either a BUG or corrupted
		 * fileप्रणाली, so पात the journal and leave a stack
		 * trace क्रम क्रमensic evidence.
		 */
		ग_लिखो_lock(&journal->j_state_lock);
		अगर (journal->j_flags & JBD2_ABORT) अणु
			mutex_unlock(&journal->j_checkpoपूर्णांक_mutex);
			वापस;
		पूर्ण
		spin_lock(&journal->j_list_lock);
		space_left = jbd2_log_space_left(journal);
		अगर (space_left < nblocks) अणु
			पूर्णांक chkpt = journal->j_checkpoपूर्णांक_transactions != शून्य;
			tid_t tid = 0;

			अगर (journal->j_committing_transaction)
				tid = journal->j_committing_transaction->t_tid;
			spin_unlock(&journal->j_list_lock);
			ग_लिखो_unlock(&journal->j_state_lock);
			अगर (chkpt) अणु
				jbd2_log_करो_checkpoपूर्णांक(journal);
			पूर्ण अन्यथा अगर (jbd2_cleanup_journal_tail(journal) == 0) अणु
				/* We were able to recover space; yay! */
				;
			पूर्ण अन्यथा अगर (tid) अणु
				/*
				 * jbd2_journal_commit_transaction() may want
				 * to take the checkpoपूर्णांक_mutex अगर JBD2_FLUSHED
				 * is set.  So we need to temporarily drop it.
				 */
				mutex_unlock(&journal->j_checkpoपूर्णांक_mutex);
				jbd2_log_रुको_commit(journal, tid);
				ग_लिखो_lock(&journal->j_state_lock);
				जारी;
			पूर्ण अन्यथा अणु
				prपूर्णांकk(KERN_ERR "%s: needed %d blocks and "
				       "only had %d space available\n",
				       __func__, nblocks, space_left);
				prपूर्णांकk(KERN_ERR "%s: no way to get more "
				       "journal space in %s\n", __func__,
				       journal->j_devname);
				WARN_ON(1);
				jbd2_journal_पात(journal, -EIO);
			पूर्ण
			ग_लिखो_lock(&journal->j_state_lock);
		पूर्ण अन्यथा अणु
			spin_unlock(&journal->j_list_lock);
		पूर्ण
		mutex_unlock(&journal->j_checkpoपूर्णांक_mutex);
	पूर्ण
पूर्ण

अटल व्योम
__flush_batch(journal_t *journal, पूर्णांक *batch_count)
अणु
	पूर्णांक i;
	काष्ठा blk_plug plug;

	blk_start_plug(&plug);
	क्रम (i = 0; i < *batch_count; i++)
		ग_लिखो_dirty_buffer(journal->j_chkpt_bhs[i], REQ_SYNC);
	blk_finish_plug(&plug);

	क्रम (i = 0; i < *batch_count; i++) अणु
		काष्ठा buffer_head *bh = journal->j_chkpt_bhs[i];
		BUFFER_TRACE(bh, "brelse");
		__brअन्यथा(bh);
	पूर्ण
	*batch_count = 0;
पूर्ण

/*
 * Perक्रमm an actual checkpoपूर्णांक. We take the first transaction on the
 * list of transactions to be checkpoपूर्णांकed and send all its buffers
 * to disk. We submit larger chunks of data at once.
 *
 * The journal should be locked beक्रमe calling this function.
 * Called with j_checkpoपूर्णांक_mutex held.
 */
पूर्णांक jbd2_log_करो_checkpoपूर्णांक(journal_t *journal)
अणु
	काष्ठा journal_head	*jh;
	काष्ठा buffer_head	*bh;
	transaction_t		*transaction;
	tid_t			this_tid;
	पूर्णांक			result, batch_count = 0;

	jbd_debug(1, "Start checkpoint\n");

	/*
	 * First thing: अगर there are any transactions in the log which
	 * करोn't need checkpoपूर्णांकing, just eliminate them from the
	 * journal straight away.
	 */
	result = jbd2_cleanup_journal_tail(journal);
	trace_jbd2_checkpoपूर्णांक(journal, result);
	jbd_debug(1, "cleanup_journal_tail returned %d\n", result);
	अगर (result <= 0)
		वापस result;

	/*
	 * OK, we need to start writing disk blocks.  Take one transaction
	 * and ग_लिखो it.
	 */
	result = 0;
	spin_lock(&journal->j_list_lock);
	अगर (!journal->j_checkpoपूर्णांक_transactions)
		जाओ out;
	transaction = journal->j_checkpoपूर्णांक_transactions;
	अगर (transaction->t_chp_stats.cs_chp_समय == 0)
		transaction->t_chp_stats.cs_chp_समय = jअगरfies;
	this_tid = transaction->t_tid;
restart:
	/*
	 * If someone cleaned up this transaction जबतक we slept, we're
	 * करोne (maybe it's a new transaction, but it fell at the same
	 * address).
	 */
	अगर (journal->j_checkpoपूर्णांक_transactions != transaction ||
	    transaction->t_tid != this_tid)
		जाओ out;

	/* checkpoपूर्णांक all of the transaction's buffers */
	जबतक (transaction->t_checkpoपूर्णांक_list) अणु
		jh = transaction->t_checkpoपूर्णांक_list;
		bh = jh2bh(jh);

		अगर (buffer_locked(bh)) अणु
			get_bh(bh);
			spin_unlock(&journal->j_list_lock);
			रुको_on_buffer(bh);
			/* the journal_head may have gone by now */
			BUFFER_TRACE(bh, "brelse");
			__brअन्यथा(bh);
			जाओ retry;
		पूर्ण
		अगर (jh->b_transaction != शून्य) अणु
			transaction_t *t = jh->b_transaction;
			tid_t tid = t->t_tid;

			transaction->t_chp_stats.cs_क्रमced_to_बंद++;
			spin_unlock(&journal->j_list_lock);
			अगर (unlikely(journal->j_flags & JBD2_UNMOUNT))
				/*
				 * The journal thपढ़ो is dead; so
				 * starting and रुकोing क्रम a commit
				 * to finish will cause us to रुको क्रम
				 * a _very_ दीर्घ समय.
				 */
				prपूर्णांकk(KERN_ERR
		"JBD2: %s: Waiting for Godot: block %llu\n",
		journal->j_devname, (अचिन्हित दीर्घ दीर्घ) bh->b_blocknr);

			अगर (batch_count)
				__flush_batch(journal, &batch_count);
			jbd2_log_start_commit(journal, tid);
			/*
			 * jbd2_journal_commit_transaction() may want
			 * to take the checkpoपूर्णांक_mutex अगर JBD2_FLUSHED
			 * is set, jbd2_update_log_tail() called by
			 * jbd2_journal_commit_transaction() may also take
			 * checkpoपूर्णांक_mutex.  So we need to temporarily
			 * drop it.
			 */
			mutex_unlock(&journal->j_checkpoपूर्णांक_mutex);
			jbd2_log_रुको_commit(journal, tid);
			mutex_lock_io(&journal->j_checkpoपूर्णांक_mutex);
			spin_lock(&journal->j_list_lock);
			जाओ restart;
		पूर्ण
		अगर (!buffer_dirty(bh)) अणु
			अगर (unlikely(buffer_ग_लिखो_io_error(bh)) && !result)
				result = -EIO;
			BUFFER_TRACE(bh, "remove from checkpoint");
			अगर (__jbd2_journal_हटाओ_checkpoपूर्णांक(jh))
				/* The transaction was released; we're करोne */
				जाओ out;
			जारी;
		पूर्ण
		/*
		 * Important: we are about to ग_लिखो the buffer, and
		 * possibly block, जबतक still holding the journal
		 * lock.  We cannot afक्रमd to let the transaction
		 * logic start messing around with this buffer beक्रमe
		 * we ग_लिखो it to disk, as that would अवरोध
		 * recoverability.
		 */
		BUFFER_TRACE(bh, "queue");
		get_bh(bh);
		J_ASSERT_BH(bh, !buffer_jग_लिखो(bh));
		journal->j_chkpt_bhs[batch_count++] = bh;
		__buffer_relink_io(jh);
		transaction->t_chp_stats.cs_written++;
		अगर ((batch_count == JBD2_NR_BATCH) ||
		    need_resched() ||
		    spin_needअवरोध(&journal->j_list_lock))
			जाओ unlock_and_flush;
	पूर्ण

	अगर (batch_count) अणु
		unlock_and_flush:
			spin_unlock(&journal->j_list_lock);
		retry:
			अगर (batch_count)
				__flush_batch(journal, &batch_count);
			spin_lock(&journal->j_list_lock);
			जाओ restart;
	पूर्ण

	/*
	 * Now we issued all of the transaction's buffers, let's deal
	 * with the buffers that are out क्रम I/O.
	 */
restart2:
	/* Did somebody clean up the transaction in the meanजबतक? */
	अगर (journal->j_checkpoपूर्णांक_transactions != transaction ||
	    transaction->t_tid != this_tid)
		जाओ out;

	जबतक (transaction->t_checkpoपूर्णांक_io_list) अणु
		jh = transaction->t_checkpoपूर्णांक_io_list;
		bh = jh2bh(jh);
		अगर (buffer_locked(bh)) अणु
			get_bh(bh);
			spin_unlock(&journal->j_list_lock);
			रुको_on_buffer(bh);
			/* the journal_head may have gone by now */
			BUFFER_TRACE(bh, "brelse");
			__brअन्यथा(bh);
			spin_lock(&journal->j_list_lock);
			जाओ restart2;
		पूर्ण
		अगर (unlikely(buffer_ग_लिखो_io_error(bh)) && !result)
			result = -EIO;

		/*
		 * Now in whatever state the buffer currently is, we
		 * know that it has been written out and so we can
		 * drop it from the list
		 */
		अगर (__jbd2_journal_हटाओ_checkpoपूर्णांक(jh))
			अवरोध;
	पूर्ण
out:
	spin_unlock(&journal->j_list_lock);
	अगर (result < 0)
		jbd2_journal_पात(journal, result);
	अन्यथा
		result = jbd2_cleanup_journal_tail(journal);

	वापस (result < 0) ? result : 0;
पूर्ण

/*
 * Check the list of checkpoपूर्णांक transactions क्रम the journal to see अगर
 * we have alपढ़ोy got rid of any since the last update of the log tail
 * in the journal superblock.  If so, we can instantly roll the
 * superblock क्रमward to हटाओ those transactions from the log.
 *
 * Return <0 on error, 0 on success, 1 अगर there was nothing to clean up.
 *
 * Called with the journal lock held.
 *
 * This is the only part of the journaling code which really needs to be
 * aware of transaction पातs.  Checkpoपूर्णांकing involves writing to the
 * मुख्य fileप्रणाली area rather than to the journal, so it can proceed
 * even in पात state, but we must not update the super block अगर
 * checkpoपूर्णांकing may have failed.  Otherwise, we would lose some metadata
 * buffers which should be written-back to the fileप्रणाली.
 */

पूर्णांक jbd2_cleanup_journal_tail(journal_t *journal)
अणु
	tid_t		first_tid;
	अचिन्हित दीर्घ	blocknr;

	अगर (is_journal_पातed(journal))
		वापस -EIO;

	अगर (!jbd2_journal_get_log_tail(journal, &first_tid, &blocknr))
		वापस 1;
	J_ASSERT(blocknr != 0);

	/*
	 * We need to make sure that any blocks that were recently written out
	 * --- perhaps by jbd2_log_करो_checkpoपूर्णांक() --- are flushed out beक्रमe
	 * we drop the transactions from the journal. It's unlikely this will
	 * be necessary, especially with an appropriately sized journal, but we
	 * need this to guarantee correctness.  Fortunately
	 * jbd2_cleanup_journal_tail() करोesn't get called all that often.
	 */
	अगर (journal->j_flags & JBD2_BARRIER)
		blkdev_issue_flush(journal->j_fs_dev);

	वापस __jbd2_update_log_tail(journal, first_tid, blocknr);
पूर्ण


/* Checkpoपूर्णांक list management */

/*
 * journal_clean_one_cp_list
 *
 * Find all the written-back checkpoपूर्णांक buffers in the given list and
 * release them. If 'destroy' is set, clean all buffers unconditionally.
 *
 * Called with j_list_lock held.
 * Returns 1 अगर we मुक्तd the transaction, 0 otherwise.
 */
अटल पूर्णांक journal_clean_one_cp_list(काष्ठा journal_head *jh, bool destroy)
अणु
	काष्ठा journal_head *last_jh;
	काष्ठा journal_head *next_jh = jh;
	पूर्णांक ret;

	अगर (!jh)
		वापस 0;

	last_jh = jh->b_cpprev;
	करो अणु
		jh = next_jh;
		next_jh = jh->b_cpnext;
		अगर (!destroy)
			ret = __try_to_मुक्त_cp_buf(jh);
		अन्यथा
			ret = __jbd2_journal_हटाओ_checkpoपूर्णांक(jh) + 1;
		अगर (!ret)
			वापस 0;
		अगर (ret == 2)
			वापस 1;
		/*
		 * This function only मुक्तs up some memory
		 * अगर possible so we करोnt have an obligation
		 * to finish processing. Bail out अगर preemption
		 * requested:
		 */
		अगर (need_resched())
			वापस 0;
	पूर्ण जबतक (jh != last_jh);

	वापस 0;
पूर्ण

/*
 * journal_clean_checkpoपूर्णांक_list
 *
 * Find all the written-back checkpoपूर्णांक buffers in the journal and release them.
 * If 'destroy' is set, release all buffers unconditionally.
 *
 * Called with j_list_lock held.
 */
व्योम __jbd2_journal_clean_checkpoपूर्णांक_list(journal_t *journal, bool destroy)
अणु
	transaction_t *transaction, *last_transaction, *next_transaction;
	पूर्णांक ret;

	transaction = journal->j_checkpoपूर्णांक_transactions;
	अगर (!transaction)
		वापस;

	last_transaction = transaction->t_cpprev;
	next_transaction = transaction;
	करो अणु
		transaction = next_transaction;
		next_transaction = transaction->t_cpnext;
		ret = journal_clean_one_cp_list(transaction->t_checkpoपूर्णांक_list,
						destroy);
		/*
		 * This function only मुक्तs up some memory अगर possible so we
		 * करोnt have an obligation to finish processing. Bail out अगर
		 * preemption requested:
		 */
		अगर (need_resched())
			वापस;
		अगर (ret)
			जारी;
		/*
		 * It is essential that we are as careful as in the हाल of
		 * t_checkpoपूर्णांक_list with removing the buffer from the list as
		 * we can possibly see not yet submitted buffers on io_list
		 */
		ret = journal_clean_one_cp_list(transaction->
				t_checkpoपूर्णांक_io_list, destroy);
		अगर (need_resched())
			वापस;
		/*
		 * Stop scanning अगर we couldn't मुक्त the transaction. This
		 * aव्योमs poपूर्णांकless scanning of transactions which still
		 * weren't checkpoपूर्णांकed.
		 */
		अगर (!ret)
			वापस;
	पूर्ण जबतक (transaction != last_transaction);
पूर्ण

/*
 * Remove buffers from all checkpoपूर्णांक lists as journal is पातed and we just
 * need to मुक्त memory
 */
व्योम jbd2_journal_destroy_checkpoपूर्णांक(journal_t *journal)
अणु
	/*
	 * We loop because __jbd2_journal_clean_checkpoपूर्णांक_list() may पात
	 * early due to a need of rescheduling.
	 */
	जबतक (1) अणु
		spin_lock(&journal->j_list_lock);
		अगर (!journal->j_checkpoपूर्णांक_transactions) अणु
			spin_unlock(&journal->j_list_lock);
			अवरोध;
		पूर्ण
		__jbd2_journal_clean_checkpoपूर्णांक_list(journal, true);
		spin_unlock(&journal->j_list_lock);
		cond_resched();
	पूर्ण
पूर्ण

/*
 * journal_हटाओ_checkpoपूर्णांक: called after a buffer has been committed
 * to disk (either by being ग_लिखो-back flushed to disk, or being
 * committed to the log).
 *
 * We cannot safely clean a transaction out of the log until all of the
 * buffer updates committed in that transaction have safely been stored
 * अन्यथाwhere on disk.  To achieve this, all of the buffers in a
 * transaction need to be मुख्यtained on the transaction's checkpoपूर्णांक
 * lists until they have been rewritten, at which poपूर्णांक this function is
 * called to हटाओ the buffer from the existing transaction's
 * checkpoपूर्णांक lists.
 *
 * The function वापसs 1 अगर it मुक्तs the transaction, 0 otherwise.
 * The function can मुक्त jh and bh.
 *
 * This function is called with j_list_lock held.
 */
पूर्णांक __jbd2_journal_हटाओ_checkpoपूर्णांक(काष्ठा journal_head *jh)
अणु
	काष्ठा transaction_chp_stats_s *stats;
	transaction_t *transaction;
	journal_t *journal;
	पूर्णांक ret = 0;

	JBUFFER_TRACE(jh, "entry");

	अगर ((transaction = jh->b_cp_transaction) == शून्य) अणु
		JBUFFER_TRACE(jh, "not on transaction");
		जाओ out;
	पूर्ण
	journal = transaction->t_journal;

	JBUFFER_TRACE(jh, "removing from transaction");
	__buffer_unlink(jh);
	jh->b_cp_transaction = शून्य;
	jbd2_journal_put_journal_head(jh);

	अगर (transaction->t_checkpoपूर्णांक_list != शून्य ||
	    transaction->t_checkpoपूर्णांक_io_list != शून्य)
		जाओ out;

	/*
	 * There is one special हाल to worry about: अगर we have just pulled the
	 * buffer off a running or committing transaction's checkpoing list,
	 * then even अगर the checkpoपूर्णांक list is empty, the transaction obviously
	 * cannot be dropped!
	 *
	 * The locking here around t_state is a bit sleazy.
	 * See the comment at the end of jbd2_journal_commit_transaction().
	 */
	अगर (transaction->t_state != T_FINISHED)
		जाओ out;

	/* OK, that was the last buffer क्रम the transaction: we can now
	   safely हटाओ this transaction from the log */
	stats = &transaction->t_chp_stats;
	अगर (stats->cs_chp_समय)
		stats->cs_chp_समय = jbd2_समय_dअगरf(stats->cs_chp_समय,
						    jअगरfies);
	trace_jbd2_checkpoपूर्णांक_stats(journal->j_fs_dev->bd_dev,
				    transaction->t_tid, stats);

	__jbd2_journal_drop_transaction(journal, transaction);
	jbd2_journal_मुक्त_transaction(transaction);
	ret = 1;
out:
	वापस ret;
पूर्ण

/*
 * journal_insert_checkpoपूर्णांक: put a committed buffer onto a checkpoपूर्णांक
 * list so that we know when it is safe to clean the transaction out of
 * the log.
 *
 * Called with the journal locked.
 * Called with j_list_lock held.
 */
व्योम __jbd2_journal_insert_checkpoपूर्णांक(काष्ठा journal_head *jh,
			       transaction_t *transaction)
अणु
	JBUFFER_TRACE(jh, "entry");
	J_ASSERT_JH(jh, buffer_dirty(jh2bh(jh)) || buffer_jbddirty(jh2bh(jh)));
	J_ASSERT_JH(jh, jh->b_cp_transaction == शून्य);

	/* Get reference क्रम checkpoपूर्णांकing transaction */
	jbd2_journal_grab_journal_head(jh2bh(jh));
	jh->b_cp_transaction = transaction;

	अगर (!transaction->t_checkpoपूर्णांक_list) अणु
		jh->b_cpnext = jh->b_cpprev = jh;
	पूर्ण अन्यथा अणु
		jh->b_cpnext = transaction->t_checkpoपूर्णांक_list;
		jh->b_cpprev = transaction->t_checkpoपूर्णांक_list->b_cpprev;
		jh->b_cpprev->b_cpnext = jh;
		jh->b_cpnext->b_cpprev = jh;
	पूर्ण
	transaction->t_checkpoपूर्णांक_list = jh;
पूर्ण

/*
 * We've finished with this transaction काष्ठाure: adios...
 *
 * The transaction must have no links except क्रम the checkpoपूर्णांक by this
 * poपूर्णांक.
 *
 * Called with the journal locked.
 * Called with j_list_lock held.
 */

व्योम __jbd2_journal_drop_transaction(journal_t *journal, transaction_t *transaction)
अणु
	निश्चित_spin_locked(&journal->j_list_lock);
	अगर (transaction->t_cpnext) अणु
		transaction->t_cpnext->t_cpprev = transaction->t_cpprev;
		transaction->t_cpprev->t_cpnext = transaction->t_cpnext;
		अगर (journal->j_checkpoपूर्णांक_transactions == transaction)
			journal->j_checkpoपूर्णांक_transactions =
				transaction->t_cpnext;
		अगर (journal->j_checkpoपूर्णांक_transactions == transaction)
			journal->j_checkpoपूर्णांक_transactions = शून्य;
	पूर्ण

	J_ASSERT(transaction->t_state == T_FINISHED);
	J_ASSERT(transaction->t_buffers == शून्य);
	J_ASSERT(transaction->t_क्रमget == शून्य);
	J_ASSERT(transaction->t_shaकरोw_list == शून्य);
	J_ASSERT(transaction->t_checkpoपूर्णांक_list == शून्य);
	J_ASSERT(transaction->t_checkpoपूर्णांक_io_list == शून्य);
	J_ASSERT(atomic_पढ़ो(&transaction->t_updates) == 0);
	J_ASSERT(journal->j_committing_transaction != transaction);
	J_ASSERT(journal->j_running_transaction != transaction);

	trace_jbd2_drop_transaction(journal, transaction);

	jbd_debug(1, "Dropping transaction %d, all done\n", transaction->t_tid);
पूर्ण
