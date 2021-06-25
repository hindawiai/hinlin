<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * linux/fs/jbd2/journal.c
 *
 * Written by Stephen C. Tweedie <sct@redhat.com>, 1998
 *
 * Copyright 1998 Red Hat corp --- All Rights Reserved
 *
 * Generic fileप्रणाली journal-writing code; part of the ext2fs
 * journaling प्रणाली.
 *
 * This file manages journals: areas of disk reserved क्रम logging
 * transactional updates.  This includes the kernel journaling thपढ़ो
 * which is responsible क्रम scheduling updates to the log.
 *
 * We करो not actually manage the physical storage of the journal in this
 * file: that is left to a per-journal policy function, which allows us
 * to store the journal within a fileप्रणाली-specअगरied area क्रम ext2
 * journaling (ext2 can use a reserved inode क्रम storing the log).
 */

#समावेश <linux/module.h>
#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/jbd2.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/poison.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/math64.h>
#समावेश <linux/hash.h>
#समावेश <linux/log2.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/bitops.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/sched/mm.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/jbd2.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/page.h>

#अगर_घोषित CONFIG_JBD2_DEBUG
uलघु jbd2_journal_enable_debug __पढ़ो_mostly;
EXPORT_SYMBOL(jbd2_journal_enable_debug);

module_param_named(jbd2_debug, jbd2_journal_enable_debug, uलघु, 0644);
MODULE_PARM_DESC(jbd2_debug, "Debugging level for jbd2");
#पूर्ण_अगर

EXPORT_SYMBOL(jbd2_journal_extend);
EXPORT_SYMBOL(jbd2_journal_stop);
EXPORT_SYMBOL(jbd2_journal_lock_updates);
EXPORT_SYMBOL(jbd2_journal_unlock_updates);
EXPORT_SYMBOL(jbd2_journal_get_ग_लिखो_access);
EXPORT_SYMBOL(jbd2_journal_get_create_access);
EXPORT_SYMBOL(jbd2_journal_get_unकरो_access);
EXPORT_SYMBOL(jbd2_journal_set_triggers);
EXPORT_SYMBOL(jbd2_journal_dirty_metadata);
EXPORT_SYMBOL(jbd2_journal_क्रमget);
EXPORT_SYMBOL(jbd2_journal_flush);
EXPORT_SYMBOL(jbd2_journal_revoke);

EXPORT_SYMBOL(jbd2_journal_init_dev);
EXPORT_SYMBOL(jbd2_journal_init_inode);
EXPORT_SYMBOL(jbd2_journal_check_used_features);
EXPORT_SYMBOL(jbd2_journal_check_available_features);
EXPORT_SYMBOL(jbd2_journal_set_features);
EXPORT_SYMBOL(jbd2_journal_load);
EXPORT_SYMBOL(jbd2_journal_destroy);
EXPORT_SYMBOL(jbd2_journal_पात);
EXPORT_SYMBOL(jbd2_journal_त्रुटि_सं);
EXPORT_SYMBOL(jbd2_journal_ack_err);
EXPORT_SYMBOL(jbd2_journal_clear_err);
EXPORT_SYMBOL(jbd2_log_रुको_commit);
EXPORT_SYMBOL(jbd2_log_start_commit);
EXPORT_SYMBOL(jbd2_journal_start_commit);
EXPORT_SYMBOL(jbd2_journal_क्रमce_commit_nested);
EXPORT_SYMBOL(jbd2_journal_wipe);
EXPORT_SYMBOL(jbd2_journal_blocks_per_page);
EXPORT_SYMBOL(jbd2_journal_invalidatepage);
EXPORT_SYMBOL(jbd2_journal_try_to_मुक्त_buffers);
EXPORT_SYMBOL(jbd2_journal_क्रमce_commit);
EXPORT_SYMBOL(jbd2_journal_inode_ranged_ग_लिखो);
EXPORT_SYMBOL(jbd2_journal_inode_ranged_रुको);
EXPORT_SYMBOL(jbd2_journal_submit_inode_data_buffers);
EXPORT_SYMBOL(jbd2_journal_finish_inode_data_buffers);
EXPORT_SYMBOL(jbd2_journal_init_jbd_inode);
EXPORT_SYMBOL(jbd2_journal_release_jbd_inode);
EXPORT_SYMBOL(jbd2_journal_begin_ordered_truncate);
EXPORT_SYMBOL(jbd2_inode_cache);

अटल पूर्णांक jbd2_journal_create_slab(माप_प्रकार slab_size);

#अगर_घोषित CONFIG_JBD2_DEBUG
व्योम __jbd2_debug(पूर्णांक level, स्थिर अक्षर *file, स्थिर अक्षर *func,
		  अचिन्हित पूर्णांक line, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर (level > jbd2_journal_enable_debug)
		वापस;
	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	prपूर्णांकk(KERN_DEBUG "%s: (%s, %u): %pV", file, func, line, &vaf);
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(__jbd2_debug);
#पूर्ण_अगर

/* Checksumming functions */
अटल पूर्णांक jbd2_verअगरy_csum_type(journal_t *j, journal_superblock_t *sb)
अणु
	अगर (!jbd2_journal_has_csum_v2or3_feature(j))
		वापस 1;

	वापस sb->s_checksum_type == JBD2_CRC32C_CHKSUM;
पूर्ण

अटल __be32 jbd2_superblock_csum(journal_t *j, journal_superblock_t *sb)
अणु
	__u32 csum;
	__be32 old_csum;

	old_csum = sb->s_checksum;
	sb->s_checksum = 0;
	csum = jbd2_chksum(j, ~0, (अक्षर *)sb, माप(journal_superblock_t));
	sb->s_checksum = old_csum;

	वापस cpu_to_be32(csum);
पूर्ण

/*
 * Helper function used to manage commit समयouts
 */

अटल व्योम commit_समयout(काष्ठा समयr_list *t)
अणु
	journal_t *journal = from_समयr(journal, t, j_commit_समयr);

	wake_up_process(journal->j_task);
पूर्ण

/*
 * kjournald2: The मुख्य thपढ़ो function used to manage a logging device
 * journal.
 *
 * This kernel thपढ़ो is responsible क्रम two things:
 *
 * 1) COMMIT:  Every so often we need to commit the current state of the
 *    fileप्रणाली to disk.  The journal thपढ़ो is responsible क्रम writing
 *    all of the metadata buffers to disk. If a fast commit is ongoing
 *    journal thपढ़ो रुकोs until it's करोne and then जारीs from
 *    there on.
 *
 * 2) CHECKPOINT: We cannot reuse a used section of the log file until all
 *    of the data in that part of the log has been rewritten अन्यथाwhere on
 *    the disk.  Flushing these old buffers to reclaim space in the log is
 *    known as checkpoपूर्णांकing, and this thपढ़ो is responsible क्रम that job.
 */

अटल पूर्णांक kjournald2(व्योम *arg)
अणु
	journal_t *journal = arg;
	transaction_t *transaction;

	/*
	 * Set up an पूर्णांकerval समयr which can be used to trigger a commit wakeup
	 * after the commit पूर्णांकerval expires
	 */
	समयr_setup(&journal->j_commit_समयr, commit_समयout, 0);

	set_मुक्तzable();

	/* Record that the journal thपढ़ो is running */
	journal->j_task = current;
	wake_up(&journal->j_रुको_करोne_commit);

	/*
	 * Make sure that no allocations from this kernel thपढ़ो will ever
	 * recurse to the fs layer because we are responsible क्रम the
	 * transaction commit and any fs involvement might get stuck रुकोing क्रम
	 * the trasn. commit.
	 */
	meदो_स्मृति_nofs_save();

	/*
	 * And now, रुको क्रमever क्रम commit wakeup events.
	 */
	ग_लिखो_lock(&journal->j_state_lock);

loop:
	अगर (journal->j_flags & JBD2_UNMOUNT)
		जाओ end_loop;

	jbd_debug(1, "commit_sequence=%u, commit_request=%u\n",
		journal->j_commit_sequence, journal->j_commit_request);

	अगर (journal->j_commit_sequence != journal->j_commit_request) अणु
		jbd_debug(1, "OK, requests differ\n");
		ग_लिखो_unlock(&journal->j_state_lock);
		del_समयr_sync(&journal->j_commit_समयr);
		jbd2_journal_commit_transaction(journal);
		ग_लिखो_lock(&journal->j_state_lock);
		जाओ loop;
	पूर्ण

	wake_up(&journal->j_रुको_करोne_commit);
	अगर (मुक्तzing(current)) अणु
		/*
		 * The simpler the better. Flushing journal isn't a
		 * good idea, because that depends on thपढ़ोs that may
		 * be alपढ़ोy stopped.
		 */
		jbd_debug(1, "Now suspending kjournald2\n");
		ग_लिखो_unlock(&journal->j_state_lock);
		try_to_मुक्तze();
		ग_लिखो_lock(&journal->j_state_lock);
	पूर्ण अन्यथा अणु
		/*
		 * We assume on resume that commits are alपढ़ोy there,
		 * so we करोn't sleep
		 */
		DEFINE_WAIT(रुको);
		पूर्णांक should_sleep = 1;

		prepare_to_रुको(&journal->j_रुको_commit, &रुको,
				TASK_INTERRUPTIBLE);
		अगर (journal->j_commit_sequence != journal->j_commit_request)
			should_sleep = 0;
		transaction = journal->j_running_transaction;
		अगर (transaction && समय_after_eq(jअगरfies,
						transaction->t_expires))
			should_sleep = 0;
		अगर (journal->j_flags & JBD2_UNMOUNT)
			should_sleep = 0;
		अगर (should_sleep) अणु
			ग_लिखो_unlock(&journal->j_state_lock);
			schedule();
			ग_लिखो_lock(&journal->j_state_lock);
		पूर्ण
		finish_रुको(&journal->j_रुको_commit, &रुको);
	पूर्ण

	jbd_debug(1, "kjournald2 wakes\n");

	/*
	 * Were we woken up by a commit wakeup event?
	 */
	transaction = journal->j_running_transaction;
	अगर (transaction && समय_after_eq(jअगरfies, transaction->t_expires)) अणु
		journal->j_commit_request = transaction->t_tid;
		jbd_debug(1, "woke because of timeout\n");
	पूर्ण
	जाओ loop;

end_loop:
	del_समयr_sync(&journal->j_commit_समयr);
	journal->j_task = शून्य;
	wake_up(&journal->j_रुको_करोne_commit);
	jbd_debug(1, "Journal thread exiting.\n");
	ग_लिखो_unlock(&journal->j_state_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक jbd2_journal_start_thपढ़ो(journal_t *journal)
अणु
	काष्ठा task_काष्ठा *t;

	t = kthपढ़ो_run(kjournald2, journal, "jbd2/%s",
			journal->j_devname);
	अगर (IS_ERR(t))
		वापस PTR_ERR(t);

	रुको_event(journal->j_रुको_करोne_commit, journal->j_task != शून्य);
	वापस 0;
पूर्ण

अटल व्योम journal_समाप्त_thपढ़ो(journal_t *journal)
अणु
	ग_लिखो_lock(&journal->j_state_lock);
	journal->j_flags |= JBD2_UNMOUNT;

	जबतक (journal->j_task) अणु
		ग_लिखो_unlock(&journal->j_state_lock);
		wake_up(&journal->j_रुको_commit);
		रुको_event(journal->j_रुको_करोne_commit, journal->j_task == शून्य);
		ग_लिखो_lock(&journal->j_state_lock);
	पूर्ण
	ग_लिखो_unlock(&journal->j_state_lock);
पूर्ण

/*
 * jbd2_journal_ग_लिखो_metadata_buffer: ग_लिखो a metadata buffer to the journal.
 *
 * Writes a metadata buffer to a given disk block.  The actual IO is not
 * perक्रमmed but a new buffer_head is स्थिरructed which labels the data
 * to be written with the correct destination disk block.
 *
 * Any magic-number escaping which needs to be करोne will cause a
 * copy-out here.  If the buffer happens to start with the
 * JBD2_MAGIC_NUMBER, then we can't ग_लिखो it to the log directly: the
 * magic number is only written to the log क्रम descripter blocks.  In
 * this हाल, we copy the data and replace the first word with 0, and we
 * वापस a result code which indicates that this buffer needs to be
 * marked as an escaped buffer in the corresponding log descriptor
 * block.  The missing word can then be restored when the block is पढ़ो
 * during recovery.
 *
 * If the source buffer has alपढ़ोy been modअगरied by a new transaction
 * since we took the last commit snapshot, we use the frozen copy of
 * that data क्रम IO. If we end up using the existing buffer_head's data
 * क्रम the ग_लिखो, then we have to make sure nobody modअगरies it जबतक the
 * IO is in progress. करो_get_ग_लिखो_access() handles this.
 *
 * The function वापसs a poपूर्णांकer to the buffer_head to be used क्रम IO.
 *
 *
 * Return value:
 *  <0: Error
 * >=0: Finished OK
 *
 * On success:
 * Bit 0 set == escape perक्रमmed on the data
 * Bit 1 set == buffer copy-out perक्रमmed (kमुक्त the data after IO)
 */

पूर्णांक jbd2_journal_ग_लिखो_metadata_buffer(transaction_t *transaction,
				  काष्ठा journal_head  *jh_in,
				  काष्ठा buffer_head **bh_out,
				  sector_t blocknr)
अणु
	पूर्णांक need_copy_out = 0;
	पूर्णांक करोne_copy_out = 0;
	पूर्णांक करो_escape = 0;
	अक्षर *mapped_data;
	काष्ठा buffer_head *new_bh;
	काष्ठा page *new_page;
	अचिन्हित पूर्णांक new_offset;
	काष्ठा buffer_head *bh_in = jh2bh(jh_in);
	journal_t *journal = transaction->t_journal;

	/*
	 * The buffer really shouldn't be locked: only the current committing
	 * transaction is allowed to ग_लिखो it, so nobody अन्यथा is allowed
	 * to करो any IO.
	 *
	 * akpm: except अगर we're journalling data, and ग_लिखो() output is
	 * also part of a shared mapping, and another thपढ़ो has
	 * decided to launch a ग_लिखोpage() against this buffer.
	 */
	J_ASSERT_BH(bh_in, buffer_jbddirty(bh_in));

	new_bh = alloc_buffer_head(GFP_NOFS|__GFP_NOFAIL);

	/* keep subsequent निश्चितions sane */
	atomic_set(&new_bh->b_count, 1);

	spin_lock(&jh_in->b_state_lock);
repeat:
	/*
	 * If a new transaction has alपढ़ोy करोne a buffer copy-out, then
	 * we use that version of the data क्रम the commit.
	 */
	अगर (jh_in->b_frozen_data) अणु
		करोne_copy_out = 1;
		new_page = virt_to_page(jh_in->b_frozen_data);
		new_offset = offset_in_page(jh_in->b_frozen_data);
	पूर्ण अन्यथा अणु
		new_page = jh2bh(jh_in)->b_page;
		new_offset = offset_in_page(jh2bh(jh_in)->b_data);
	पूर्ण

	mapped_data = kmap_atomic(new_page);
	/*
	 * Fire data frozen trigger अगर data alपढ़ोy wasn't frozen.  Do this
	 * beक्रमe checking क्रम escaping, as the trigger may modअगरy the magic
	 * offset.  If a copy-out happens afterwards, it will have the correct
	 * data in the buffer.
	 */
	अगर (!करोne_copy_out)
		jbd2_buffer_frozen_trigger(jh_in, mapped_data + new_offset,
					   jh_in->b_triggers);

	/*
	 * Check क्रम escaping
	 */
	अगर (*((__be32 *)(mapped_data + new_offset)) ==
				cpu_to_be32(JBD2_MAGIC_NUMBER)) अणु
		need_copy_out = 1;
		करो_escape = 1;
	पूर्ण
	kunmap_atomic(mapped_data);

	/*
	 * Do we need to करो a data copy?
	 */
	अगर (need_copy_out && !करोne_copy_out) अणु
		अक्षर *पंचांगp;

		spin_unlock(&jh_in->b_state_lock);
		पंचांगp = jbd2_alloc(bh_in->b_size, GFP_NOFS);
		अगर (!पंचांगp) अणु
			brअन्यथा(new_bh);
			वापस -ENOMEM;
		पूर्ण
		spin_lock(&jh_in->b_state_lock);
		अगर (jh_in->b_frozen_data) अणु
			jbd2_मुक्त(पंचांगp, bh_in->b_size);
			जाओ repeat;
		पूर्ण

		jh_in->b_frozen_data = पंचांगp;
		mapped_data = kmap_atomic(new_page);
		स_नकल(पंचांगp, mapped_data + new_offset, bh_in->b_size);
		kunmap_atomic(mapped_data);

		new_page = virt_to_page(पंचांगp);
		new_offset = offset_in_page(पंचांगp);
		करोne_copy_out = 1;

		/*
		 * This isn't strictly necessary, as we're using frozen
		 * data क्रम the escaping, but it keeps consistency with
		 * b_frozen_data usage.
		 */
		jh_in->b_frozen_triggers = jh_in->b_triggers;
	पूर्ण

	/*
	 * Did we need to करो an escaping?  Now we've करोne all the
	 * copying, we can finally करो so.
	 */
	अगर (करो_escape) अणु
		mapped_data = kmap_atomic(new_page);
		*((अचिन्हित पूर्णांक *)(mapped_data + new_offset)) = 0;
		kunmap_atomic(mapped_data);
	पूर्ण

	set_bh_page(new_bh, new_page, new_offset);
	new_bh->b_size = bh_in->b_size;
	new_bh->b_bdev = journal->j_dev;
	new_bh->b_blocknr = blocknr;
	new_bh->b_निजी = bh_in;
	set_buffer_mapped(new_bh);
	set_buffer_dirty(new_bh);

	*bh_out = new_bh;

	/*
	 * The to-be-written buffer needs to get moved to the io queue,
	 * and the original buffer whose contents we are shaकरोwing or
	 * copying is moved to the transaction's shaकरोw queue.
	 */
	JBUFFER_TRACE(jh_in, "file as BJ_Shadow");
	spin_lock(&journal->j_list_lock);
	__jbd2_journal_file_buffer(jh_in, transaction, BJ_Shaकरोw);
	spin_unlock(&journal->j_list_lock);
	set_buffer_shaकरोw(bh_in);
	spin_unlock(&jh_in->b_state_lock);

	वापस करो_escape | (करोne_copy_out << 1);
पूर्ण

/*
 * Allocation code क्रम the journal file.  Manage the space left in the
 * journal, so that we can begin checkpoपूर्णांकing when appropriate.
 */

/*
 * Called with j_state_lock locked क्रम writing.
 * Returns true अगर a transaction commit was started.
 */
पूर्णांक __jbd2_log_start_commit(journal_t *journal, tid_t target)
अणु
	/* Return अगर the txn has alपढ़ोy requested to be committed */
	अगर (journal->j_commit_request == target)
		वापस 0;

	/*
	 * The only transaction we can possibly रुको upon is the
	 * currently running transaction (अगर it exists).  Otherwise,
	 * the target tid must be an old one.
	 */
	अगर (journal->j_running_transaction &&
	    journal->j_running_transaction->t_tid == target) अणु
		/*
		 * We want a new commit: OK, mark the request and wakeup the
		 * commit thपढ़ो.  We करो _not_ करो the commit ourselves.
		 */

		journal->j_commit_request = target;
		jbd_debug(1, "JBD2: requesting commit %u/%u\n",
			  journal->j_commit_request,
			  journal->j_commit_sequence);
		journal->j_running_transaction->t_requested = jअगरfies;
		wake_up(&journal->j_रुको_commit);
		वापस 1;
	पूर्ण अन्यथा अगर (!tid_geq(journal->j_commit_request, target))
		/* This should never happen, but अगर it करोes, preserve
		   the evidence beक्रमe kjournald goes पूर्णांकo a loop and
		   increments j_commit_sequence beyond all recognition. */
		WARN_ONCE(1, "JBD2: bad log_start_commit: %u %u %u %u\n",
			  journal->j_commit_request,
			  journal->j_commit_sequence,
			  target, journal->j_running_transaction ?
			  journal->j_running_transaction->t_tid : 0);
	वापस 0;
पूर्ण

पूर्णांक jbd2_log_start_commit(journal_t *journal, tid_t tid)
अणु
	पूर्णांक ret;

	ग_लिखो_lock(&journal->j_state_lock);
	ret = __jbd2_log_start_commit(journal, tid);
	ग_लिखो_unlock(&journal->j_state_lock);
	वापस ret;
पूर्ण

/*
 * Force and रुको any uncommitted transactions.  We can only क्रमce the running
 * transaction अगर we करोn't have an active handle, otherwise, we will deadlock.
 * Returns: <0 in हाल of error,
 *           0 अगर nothing to commit,
 *           1 अगर transaction was successfully committed.
 */
अटल पूर्णांक __jbd2_journal_क्रमce_commit(journal_t *journal)
अणु
	transaction_t *transaction = शून्य;
	tid_t tid;
	पूर्णांक need_to_start = 0, ret = 0;

	पढ़ो_lock(&journal->j_state_lock);
	अगर (journal->j_running_transaction && !current->journal_info) अणु
		transaction = journal->j_running_transaction;
		अगर (!tid_geq(journal->j_commit_request, transaction->t_tid))
			need_to_start = 1;
	पूर्ण अन्यथा अगर (journal->j_committing_transaction)
		transaction = journal->j_committing_transaction;

	अगर (!transaction) अणु
		/* Nothing to commit */
		पढ़ो_unlock(&journal->j_state_lock);
		वापस 0;
	पूर्ण
	tid = transaction->t_tid;
	पढ़ो_unlock(&journal->j_state_lock);
	अगर (need_to_start)
		jbd2_log_start_commit(journal, tid);
	ret = jbd2_log_रुको_commit(journal, tid);
	अगर (!ret)
		ret = 1;

	वापस ret;
पूर्ण

/**
 * jbd2_journal_क्रमce_commit_nested - Force and रुको upon a commit अगर the
 * calling process is not within transaction.
 *
 * @journal: journal to क्रमce
 * Returns true अगर progress was made.
 *
 * This is used क्रम क्रमcing out unकरो-रक्षित data which contains
 * biपंचांगaps, when the fs is running out of space.
 */
पूर्णांक jbd2_journal_क्रमce_commit_nested(journal_t *journal)
अणु
	पूर्णांक ret;

	ret = __jbd2_journal_क्रमce_commit(journal);
	वापस ret > 0;
पूर्ण

/**
 * jbd2_journal_क्रमce_commit() - क्रमce any uncommitted transactions
 * @journal: journal to क्रमce
 *
 * Caller want unconditional commit. We can only क्रमce the running transaction
 * अगर we करोn't have an active handle, otherwise, we will deadlock.
 */
पूर्णांक jbd2_journal_क्रमce_commit(journal_t *journal)
अणु
	पूर्णांक ret;

	J_ASSERT(!current->journal_info);
	ret = __jbd2_journal_क्रमce_commit(journal);
	अगर (ret > 0)
		ret = 0;
	वापस ret;
पूर्ण

/*
 * Start a commit of the current running transaction (अगर any).  Returns true
 * अगर a transaction is going to be committed (or is currently alपढ़ोy
 * committing), and fills its tid in at *ptid
 */
पूर्णांक jbd2_journal_start_commit(journal_t *journal, tid_t *ptid)
अणु
	पूर्णांक ret = 0;

	ग_लिखो_lock(&journal->j_state_lock);
	अगर (journal->j_running_transaction) अणु
		tid_t tid = journal->j_running_transaction->t_tid;

		__jbd2_log_start_commit(journal, tid);
		/* There's a running transaction and we've just made sure
		 * it's commit has been scheduled. */
		अगर (ptid)
			*ptid = tid;
		ret = 1;
	पूर्ण अन्यथा अगर (journal->j_committing_transaction) अणु
		/*
		 * If commit has been started, then we have to रुको क्रम
		 * completion of that transaction.
		 */
		अगर (ptid)
			*ptid = journal->j_committing_transaction->t_tid;
		ret = 1;
	पूर्ण
	ग_लिखो_unlock(&journal->j_state_lock);
	वापस ret;
पूर्ण

/*
 * Return 1 अगर a given transaction has not yet sent barrier request
 * connected with a transaction commit. If 0 is वापसed, transaction
 * may or may not have sent the barrier. Used to aव्योम sending barrier
 * twice in common हालs.
 */
पूर्णांक jbd2_trans_will_send_data_barrier(journal_t *journal, tid_t tid)
अणु
	पूर्णांक ret = 0;
	transaction_t *commit_trans;

	अगर (!(journal->j_flags & JBD2_BARRIER))
		वापस 0;
	पढ़ो_lock(&journal->j_state_lock);
	/* Transaction alपढ़ोy committed? */
	अगर (tid_geq(journal->j_commit_sequence, tid))
		जाओ out;
	commit_trans = journal->j_committing_transaction;
	अगर (!commit_trans || commit_trans->t_tid != tid) अणु
		ret = 1;
		जाओ out;
	पूर्ण
	/*
	 * Transaction is being committed and we alपढ़ोy proceeded to
	 * submitting a flush to fs partition?
	 */
	अगर (journal->j_fs_dev != journal->j_dev) अणु
		अगर (!commit_trans->t_need_data_flush ||
		    commit_trans->t_state >= T_COMMIT_DFLUSH)
			जाओ out;
	पूर्ण अन्यथा अणु
		अगर (commit_trans->t_state >= T_COMMIT_JFLUSH)
			जाओ out;
	पूर्ण
	ret = 1;
out:
	पढ़ो_unlock(&journal->j_state_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(jbd2_trans_will_send_data_barrier);

/*
 * Wait क्रम a specअगरied commit to complete.
 * The caller may not hold the journal lock.
 */
पूर्णांक jbd2_log_रुको_commit(journal_t *journal, tid_t tid)
अणु
	पूर्णांक err = 0;

	पढ़ो_lock(&journal->j_state_lock);
#अगर_घोषित CONFIG_PROVE_LOCKING
	/*
	 * Some callers make sure transaction is alपढ़ोy committing and in that
	 * हाल we cannot block on खोलो handles anymore. So करोn't warn in that
	 * हाल.
	 */
	अगर (tid_gt(tid, journal->j_commit_sequence) &&
	    (!journal->j_committing_transaction ||
	     journal->j_committing_transaction->t_tid != tid)) अणु
		पढ़ो_unlock(&journal->j_state_lock);
		jbd2_might_रुको_क्रम_commit(journal);
		पढ़ो_lock(&journal->j_state_lock);
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_JBD2_DEBUG
	अगर (!tid_geq(journal->j_commit_request, tid)) अणु
		prपूर्णांकk(KERN_ERR
		       "%s: error: j_commit_request=%u, tid=%u\n",
		       __func__, journal->j_commit_request, tid);
	पूर्ण
#पूर्ण_अगर
	जबतक (tid_gt(tid, journal->j_commit_sequence)) अणु
		jbd_debug(1, "JBD2: want %u, j_commit_sequence=%u\n",
				  tid, journal->j_commit_sequence);
		पढ़ो_unlock(&journal->j_state_lock);
		wake_up(&journal->j_रुको_commit);
		रुको_event(journal->j_रुको_करोne_commit,
				!tid_gt(tid, journal->j_commit_sequence));
		पढ़ो_lock(&journal->j_state_lock);
	पूर्ण
	पढ़ो_unlock(&journal->j_state_lock);

	अगर (unlikely(is_journal_पातed(journal)))
		err = -EIO;
	वापस err;
पूर्ण

/*
 * Start a fast commit. If there's an ongoing fast or full commit रुको क्रम
 * it to complete. Returns 0 अगर a new fast commit was started. Returns -EALREADY
 * अगर a fast commit is not needed, either because there's an alपढ़ोy a commit
 * going on or this tid has alपढ़ोy been committed. Returns -EINVAL अगर no jbd2
 * commit has yet been perक्रमmed.
 */
पूर्णांक jbd2_fc_begin_commit(journal_t *journal, tid_t tid)
अणु
	अगर (unlikely(is_journal_पातed(journal)))
		वापस -EIO;
	/*
	 * Fast commits only allowed अगर at least one full commit has
	 * been processed.
	 */
	अगर (!journal->j_stats.ts_tid)
		वापस -EINVAL;

	ग_लिखो_lock(&journal->j_state_lock);
	अगर (tid <= journal->j_commit_sequence) अणु
		ग_लिखो_unlock(&journal->j_state_lock);
		वापस -EALREADY;
	पूर्ण

	अगर (journal->j_flags & JBD2_FULL_COMMIT_ONGOING ||
	    (journal->j_flags & JBD2_FAST_COMMIT_ONGOING)) अणु
		DEFINE_WAIT(रुको);

		prepare_to_रुको(&journal->j_fc_रुको, &रुको,
				TASK_UNINTERRUPTIBLE);
		ग_लिखो_unlock(&journal->j_state_lock);
		schedule();
		finish_रुको(&journal->j_fc_रुको, &रुको);
		वापस -EALREADY;
	पूर्ण
	journal->j_flags |= JBD2_FAST_COMMIT_ONGOING;
	ग_लिखो_unlock(&journal->j_state_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(jbd2_fc_begin_commit);

/*
 * Stop a fast commit. If fallback is set, this function starts commit of
 * TID tid beक्रमe any other fast commit can start.
 */
अटल पूर्णांक __jbd2_fc_end_commit(journal_t *journal, tid_t tid, bool fallback)
अणु
	अगर (journal->j_fc_cleanup_callback)
		journal->j_fc_cleanup_callback(journal, 0);
	ग_लिखो_lock(&journal->j_state_lock);
	journal->j_flags &= ~JBD2_FAST_COMMIT_ONGOING;
	अगर (fallback)
		journal->j_flags |= JBD2_FULL_COMMIT_ONGOING;
	ग_लिखो_unlock(&journal->j_state_lock);
	wake_up(&journal->j_fc_रुको);
	अगर (fallback)
		वापस jbd2_complete_transaction(journal, tid);
	वापस 0;
पूर्ण

पूर्णांक jbd2_fc_end_commit(journal_t *journal)
अणु
	वापस __jbd2_fc_end_commit(journal, 0, false);
पूर्ण
EXPORT_SYMBOL(jbd2_fc_end_commit);

पूर्णांक jbd2_fc_end_commit_fallback(journal_t *journal)
अणु
	tid_t tid;

	पढ़ो_lock(&journal->j_state_lock);
	tid = journal->j_running_transaction ?
		journal->j_running_transaction->t_tid : 0;
	पढ़ो_unlock(&journal->j_state_lock);
	वापस __jbd2_fc_end_commit(journal, tid, true);
पूर्ण
EXPORT_SYMBOL(jbd2_fc_end_commit_fallback);

/* Return 1 when transaction with given tid has alपढ़ोy committed. */
पूर्णांक jbd2_transaction_committed(journal_t *journal, tid_t tid)
अणु
	पूर्णांक ret = 1;

	पढ़ो_lock(&journal->j_state_lock);
	अगर (journal->j_running_transaction &&
	    journal->j_running_transaction->t_tid == tid)
		ret = 0;
	अगर (journal->j_committing_transaction &&
	    journal->j_committing_transaction->t_tid == tid)
		ret = 0;
	पढ़ो_unlock(&journal->j_state_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(jbd2_transaction_committed);

/*
 * When this function वापसs the transaction corresponding to tid
 * will be completed.  If the transaction has currently running, start
 * committing that transaction beक्रमe रुकोing क्रम it to complete.  If
 * the transaction id is stale, it is by definition alपढ़ोy completed,
 * so just वापस SUCCESS.
 */
पूर्णांक jbd2_complete_transaction(journal_t *journal, tid_t tid)
अणु
	पूर्णांक	need_to_रुको = 1;

	पढ़ो_lock(&journal->j_state_lock);
	अगर (journal->j_running_transaction &&
	    journal->j_running_transaction->t_tid == tid) अणु
		अगर (journal->j_commit_request != tid) अणु
			/* transaction not yet started, so request it */
			पढ़ो_unlock(&journal->j_state_lock);
			jbd2_log_start_commit(journal, tid);
			जाओ रुको_commit;
		पूर्ण
	पूर्ण अन्यथा अगर (!(journal->j_committing_transaction &&
		     journal->j_committing_transaction->t_tid == tid))
		need_to_रुको = 0;
	पढ़ो_unlock(&journal->j_state_lock);
	अगर (!need_to_रुको)
		वापस 0;
रुको_commit:
	वापस jbd2_log_रुको_commit(journal, tid);
पूर्ण
EXPORT_SYMBOL(jbd2_complete_transaction);

/*
 * Log buffer allocation routines:
 */

पूर्णांक jbd2_journal_next_log_block(journal_t *journal, अचिन्हित दीर्घ दीर्घ *retp)
अणु
	अचिन्हित दीर्घ blocknr;

	ग_लिखो_lock(&journal->j_state_lock);
	J_ASSERT(journal->j_मुक्त > 1);

	blocknr = journal->j_head;
	journal->j_head++;
	journal->j_मुक्त--;
	अगर (journal->j_head == journal->j_last)
		journal->j_head = journal->j_first;
	ग_लिखो_unlock(&journal->j_state_lock);
	वापस jbd2_journal_bmap(journal, blocknr, retp);
पूर्ण

/* Map one fast commit buffer क्रम use by the file प्रणाली */
पूर्णांक jbd2_fc_get_buf(journal_t *journal, काष्ठा buffer_head **bh_out)
अणु
	अचिन्हित दीर्घ दीर्घ pblock;
	अचिन्हित दीर्घ blocknr;
	पूर्णांक ret = 0;
	काष्ठा buffer_head *bh;
	पूर्णांक fc_off;

	*bh_out = शून्य;

	अगर (journal->j_fc_off + journal->j_fc_first < journal->j_fc_last) अणु
		fc_off = journal->j_fc_off;
		blocknr = journal->j_fc_first + fc_off;
		journal->j_fc_off++;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	अगर (ret)
		वापस ret;

	ret = jbd2_journal_bmap(journal, blocknr, &pblock);
	अगर (ret)
		वापस ret;

	bh = __getblk(journal->j_dev, pblock, journal->j_blocksize);
	अगर (!bh)
		वापस -ENOMEM;


	journal->j_fc_wbuf[fc_off] = bh;

	*bh_out = bh;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(jbd2_fc_get_buf);

/*
 * Wait on fast commit buffers that were allocated by jbd2_fc_get_buf
 * क्रम completion.
 */
पूर्णांक jbd2_fc_रुको_bufs(journal_t *journal, पूर्णांक num_blks)
अणु
	काष्ठा buffer_head *bh;
	पूर्णांक i, j_fc_off;

	j_fc_off = journal->j_fc_off;

	/*
	 * Wait in reverse order to minimize chances of us being woken up beक्रमe
	 * all IOs have completed
	 */
	क्रम (i = j_fc_off - 1; i >= j_fc_off - num_blks; i--) अणु
		bh = journal->j_fc_wbuf[i];
		रुको_on_buffer(bh);
		put_bh(bh);
		journal->j_fc_wbuf[i] = शून्य;
		अगर (unlikely(!buffer_uptodate(bh)))
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(jbd2_fc_रुको_bufs);

/*
 * Wait on fast commit buffers that were allocated by jbd2_fc_get_buf
 * क्रम completion.
 */
पूर्णांक jbd2_fc_release_bufs(journal_t *journal)
अणु
	काष्ठा buffer_head *bh;
	पूर्णांक i, j_fc_off;

	j_fc_off = journal->j_fc_off;

	/*
	 * Wait in reverse order to minimize chances of us being woken up beक्रमe
	 * all IOs have completed
	 */
	क्रम (i = j_fc_off - 1; i >= 0; i--) अणु
		bh = journal->j_fc_wbuf[i];
		अगर (!bh)
			अवरोध;
		put_bh(bh);
		journal->j_fc_wbuf[i] = शून्य;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(jbd2_fc_release_bufs);

/*
 * Conversion of logical to physical block numbers क्रम the journal
 *
 * On बाह्यal journals the journal blocks are identity-mapped, so
 * this is a no-op.  If needed, we can use j_blk_offset - everything is
 * पढ़ोy.
 */
पूर्णांक jbd2_journal_bmap(journal_t *journal, अचिन्हित दीर्घ blocknr,
		 अचिन्हित दीर्घ दीर्घ *retp)
अणु
	पूर्णांक err = 0;
	अचिन्हित दीर्घ दीर्घ ret;
	sector_t block = 0;

	अगर (journal->j_inode) अणु
		block = blocknr;
		ret = bmap(journal->j_inode, &block);

		अगर (ret || !block) अणु
			prपूर्णांकk(KERN_ALERT "%s: journal block not found "
					"at offset %lu on %s\n",
			       __func__, blocknr, journal->j_devname);
			err = -EIO;
			jbd2_journal_पात(journal, err);
		पूर्ण अन्यथा अणु
			*retp = block;
		पूर्ण

	पूर्ण अन्यथा अणु
		*retp = blocknr; /* +journal->j_blk_offset */
	पूर्ण
	वापस err;
पूर्ण

/*
 * We play buffer_head aliasing tricks to ग_लिखो data/metadata blocks to
 * the journal without copying their contents, but क्रम journal
 * descriptor blocks we करो need to generate bona fide buffers.
 *
 * After the caller of jbd2_journal_get_descriptor_buffer() has finished modअगरying
 * the buffer's contents they really should run flush_dcache_page(bh->b_page).
 * But we करोn't bother करोing that, so there will be coherency problems with
 * mmaps of blockdevs which hold live JBD-controlled fileप्रणालीs.
 */
काष्ठा buffer_head *
jbd2_journal_get_descriptor_buffer(transaction_t *transaction, पूर्णांक type)
अणु
	journal_t *journal = transaction->t_journal;
	काष्ठा buffer_head *bh;
	अचिन्हित दीर्घ दीर्घ blocknr;
	journal_header_t *header;
	पूर्णांक err;

	err = jbd2_journal_next_log_block(journal, &blocknr);

	अगर (err)
		वापस शून्य;

	bh = __getblk(journal->j_dev, blocknr, journal->j_blocksize);
	अगर (!bh)
		वापस शून्य;
	atomic_dec(&transaction->t_outstanding_credits);
	lock_buffer(bh);
	स_रखो(bh->b_data, 0, journal->j_blocksize);
	header = (journal_header_t *)bh->b_data;
	header->h_magic = cpu_to_be32(JBD2_MAGIC_NUMBER);
	header->h_blocktype = cpu_to_be32(type);
	header->h_sequence = cpu_to_be32(transaction->t_tid);
	set_buffer_uptodate(bh);
	unlock_buffer(bh);
	BUFFER_TRACE(bh, "return this buffer");
	वापस bh;
पूर्ण

व्योम jbd2_descriptor_block_csum_set(journal_t *j, काष्ठा buffer_head *bh)
अणु
	काष्ठा jbd2_journal_block_tail *tail;
	__u32 csum;

	अगर (!jbd2_journal_has_csum_v2or3(j))
		वापस;

	tail = (काष्ठा jbd2_journal_block_tail *)(bh->b_data + j->j_blocksize -
			माप(काष्ठा jbd2_journal_block_tail));
	tail->t_checksum = 0;
	csum = jbd2_chksum(j, j->j_csum_seed, bh->b_data, j->j_blocksize);
	tail->t_checksum = cpu_to_be32(csum);
पूर्ण

/*
 * Return tid of the oldest transaction in the journal and block in the journal
 * where the transaction starts.
 *
 * If the journal is now empty, वापस which will be the next transaction ID
 * we will ग_लिखो and where will that transaction start.
 *
 * The वापस value is 0 अगर journal tail cannot be pushed any further, 1 अगर
 * it can.
 */
पूर्णांक jbd2_journal_get_log_tail(journal_t *journal, tid_t *tid,
			      अचिन्हित दीर्घ *block)
अणु
	transaction_t *transaction;
	पूर्णांक ret;

	पढ़ो_lock(&journal->j_state_lock);
	spin_lock(&journal->j_list_lock);
	transaction = journal->j_checkpoपूर्णांक_transactions;
	अगर (transaction) अणु
		*tid = transaction->t_tid;
		*block = transaction->t_log_start;
	पूर्ण अन्यथा अगर ((transaction = journal->j_committing_transaction) != शून्य) अणु
		*tid = transaction->t_tid;
		*block = transaction->t_log_start;
	पूर्ण अन्यथा अगर ((transaction = journal->j_running_transaction) != शून्य) अणु
		*tid = transaction->t_tid;
		*block = journal->j_head;
	पूर्ण अन्यथा अणु
		*tid = journal->j_transaction_sequence;
		*block = journal->j_head;
	पूर्ण
	ret = tid_gt(*tid, journal->j_tail_sequence);
	spin_unlock(&journal->j_list_lock);
	पढ़ो_unlock(&journal->j_state_lock);

	वापस ret;
पूर्ण

/*
 * Update inक्रमmation in journal काष्ठाure and in on disk journal superblock
 * about log tail. This function करोes not check whether inक्रमmation passed in
 * really pushes log tail further. It's responsibility of the caller to make
 * sure provided log tail inक्रमmation is valid (e.g. by holding
 * j_checkpoपूर्णांक_mutex all the समय between computing log tail and calling this
 * function as is the हाल with jbd2_cleanup_journal_tail()).
 *
 * Requires j_checkpoपूर्णांक_mutex
 */
पूर्णांक __jbd2_update_log_tail(journal_t *journal, tid_t tid, अचिन्हित दीर्घ block)
अणु
	अचिन्हित दीर्घ मुक्तd;
	पूर्णांक ret;

	BUG_ON(!mutex_is_locked(&journal->j_checkpoपूर्णांक_mutex));

	/*
	 * We cannot afक्रमd क्रम ग_लिखो to reमुख्य in drive's caches since as
	 * soon as we update j_tail, next transaction can start reusing journal
	 * space and अगर we lose sb update during घातer failure we'd replay
	 * old transaction with possibly newly overwritten data.
	 */
	ret = jbd2_journal_update_sb_log_tail(journal, tid, block,
					      REQ_SYNC | REQ_FUA);
	अगर (ret)
		जाओ out;

	ग_लिखो_lock(&journal->j_state_lock);
	मुक्तd = block - journal->j_tail;
	अगर (block < journal->j_tail)
		मुक्तd += journal->j_last - journal->j_first;

	trace_jbd2_update_log_tail(journal, tid, block, मुक्तd);
	jbd_debug(1,
		  "Cleaning journal tail from %u to %u (offset %lu), "
		  "freeing %lu\n",
		  journal->j_tail_sequence, tid, block, मुक्तd);

	journal->j_मुक्त += मुक्तd;
	journal->j_tail_sequence = tid;
	journal->j_tail = block;
	ग_लिखो_unlock(&journal->j_state_lock);

out:
	वापस ret;
पूर्ण

/*
 * This is a variation of __jbd2_update_log_tail which checks क्रम validity of
 * provided log tail and locks j_checkpoपूर्णांक_mutex. So it is safe against races
 * with other thपढ़ोs updating log tail.
 */
व्योम jbd2_update_log_tail(journal_t *journal, tid_t tid, अचिन्हित दीर्घ block)
अणु
	mutex_lock_io(&journal->j_checkpoपूर्णांक_mutex);
	अगर (tid_gt(tid, journal->j_tail_sequence))
		__jbd2_update_log_tail(journal, tid, block);
	mutex_unlock(&journal->j_checkpoपूर्णांक_mutex);
पूर्ण

काष्ठा jbd2_stats_proc_session अणु
	journal_t *journal;
	काष्ठा transaction_stats_s *stats;
	पूर्णांक start;
	पूर्णांक max;
पूर्ण;

अटल व्योम *jbd2_seq_info_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	वापस *pos ? शून्य : SEQ_START_TOKEN;
पूर्ण

अटल व्योम *jbd2_seq_info_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	(*pos)++;
	वापस शून्य;
पूर्ण

अटल पूर्णांक jbd2_seq_info_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा jbd2_stats_proc_session *s = seq->निजी;

	अगर (v != SEQ_START_TOKEN)
		वापस 0;
	seq_म_लिखो(seq, "%lu transactions (%lu requested), "
		   "each up to %u blocks\n",
		   s->stats->ts_tid, s->stats->ts_requested,
		   s->journal->j_max_transaction_buffers);
	अगर (s->stats->ts_tid == 0)
		वापस 0;
	seq_म_लिखो(seq, "average: \n  %ums waiting for transaction\n",
	    jअगरfies_to_msecs(s->stats->run.rs_रुको / s->stats->ts_tid));
	seq_म_लिखो(seq, "  %ums request delay\n",
	    (s->stats->ts_requested == 0) ? 0 :
	    jअगरfies_to_msecs(s->stats->run.rs_request_delay /
			     s->stats->ts_requested));
	seq_म_लिखो(seq, "  %ums running transaction\n",
	    jअगरfies_to_msecs(s->stats->run.rs_running / s->stats->ts_tid));
	seq_म_लिखो(seq, "  %ums transaction was being locked\n",
	    jअगरfies_to_msecs(s->stats->run.rs_locked / s->stats->ts_tid));
	seq_म_लिखो(seq, "  %ums flushing data (in ordered mode)\n",
	    jअगरfies_to_msecs(s->stats->run.rs_flushing / s->stats->ts_tid));
	seq_म_लिखो(seq, "  %ums logging transaction\n",
	    jअगरfies_to_msecs(s->stats->run.rs_logging / s->stats->ts_tid));
	seq_म_लिखो(seq, "  %lluus average transaction commit time\n",
		   भाग_u64(s->journal->j_average_commit_समय, 1000));
	seq_म_लिखो(seq, "  %lu handles per transaction\n",
	    s->stats->run.rs_handle_count / s->stats->ts_tid);
	seq_म_लिखो(seq, "  %lu blocks per transaction\n",
	    s->stats->run.rs_blocks / s->stats->ts_tid);
	seq_म_लिखो(seq, "  %lu logged blocks per transaction\n",
	    s->stats->run.rs_blocks_logged / s->stats->ts_tid);
	वापस 0;
पूर्ण

अटल व्योम jbd2_seq_info_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल स्थिर काष्ठा seq_operations jbd2_seq_info_ops = अणु
	.start  = jbd2_seq_info_start,
	.next   = jbd2_seq_info_next,
	.stop   = jbd2_seq_info_stop,
	.show   = jbd2_seq_info_show,
पूर्ण;

अटल पूर्णांक jbd2_seq_info_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	journal_t *journal = PDE_DATA(inode);
	काष्ठा jbd2_stats_proc_session *s;
	पूर्णांक rc, size;

	s = kदो_स्मृति(माप(*s), GFP_KERNEL);
	अगर (s == शून्य)
		वापस -ENOMEM;
	size = माप(काष्ठा transaction_stats_s);
	s->stats = kदो_स्मृति(size, GFP_KERNEL);
	अगर (s->stats == शून्य) अणु
		kमुक्त(s);
		वापस -ENOMEM;
	पूर्ण
	spin_lock(&journal->j_history_lock);
	स_नकल(s->stats, &journal->j_stats, size);
	s->journal = journal;
	spin_unlock(&journal->j_history_lock);

	rc = seq_खोलो(file, &jbd2_seq_info_ops);
	अगर (rc == 0) अणु
		काष्ठा seq_file *m = file->निजी_data;
		m->निजी = s;
	पूर्ण अन्यथा अणु
		kमुक्त(s->stats);
		kमुक्त(s);
	पूर्ण
	वापस rc;

पूर्ण

अटल पूर्णांक jbd2_seq_info_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	काष्ठा jbd2_stats_proc_session *s = seq->निजी;
	kमुक्त(s->stats);
	kमुक्त(s);
	वापस seq_release(inode, file);
पूर्ण

अटल स्थिर काष्ठा proc_ops jbd2_info_proc_ops = अणु
	.proc_खोलो	= jbd2_seq_info_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= jbd2_seq_info_release,
पूर्ण;

अटल काष्ठा proc_dir_entry *proc_jbd2_stats;

अटल व्योम jbd2_stats_proc_init(journal_t *journal)
अणु
	journal->j_proc_entry = proc_सूची_गढ़ो(journal->j_devname, proc_jbd2_stats);
	अगर (journal->j_proc_entry) अणु
		proc_create_data("info", S_IRUGO, journal->j_proc_entry,
				 &jbd2_info_proc_ops, journal);
	पूर्ण
पूर्ण

अटल व्योम jbd2_stats_proc_निकास(journal_t *journal)
अणु
	हटाओ_proc_entry("info", journal->j_proc_entry);
	हटाओ_proc_entry(journal->j_devname, proc_jbd2_stats);
पूर्ण

/* Minimum size of descriptor tag */
अटल पूर्णांक jbd2_min_tag_size(व्योम)
अणु
	/*
	 * Tag with 32-bit block numbers करोes not use last four bytes of the
	 * काष्ठाure
	 */
	वापस माप(journal_block_tag_t) - 4;
पूर्ण

/*
 * Management क्रम journal control blocks: functions to create and
 * destroy journal_t काष्ठाures, and to initialise and पढ़ो existing
 * journal blocks from disk.  */

/* First: create and setup a journal_t object in memory.  We initialise
 * very few fields yet: that has to रुको until we have created the
 * journal काष्ठाures from from scratch, or loaded them from disk. */

अटल journal_t *journal_init_common(काष्ठा block_device *bdev,
			काष्ठा block_device *fs_dev,
			अचिन्हित दीर्घ दीर्घ start, पूर्णांक len, पूर्णांक blocksize)
अणु
	अटल काष्ठा lock_class_key jbd2_trans_commit_key;
	journal_t *journal;
	पूर्णांक err;
	काष्ठा buffer_head *bh;
	पूर्णांक n;

	journal = kzalloc(माप(*journal), GFP_KERNEL);
	अगर (!journal)
		वापस शून्य;

	init_रुकोqueue_head(&journal->j_रुको_transaction_locked);
	init_रुकोqueue_head(&journal->j_रुको_करोne_commit);
	init_रुकोqueue_head(&journal->j_रुको_commit);
	init_रुकोqueue_head(&journal->j_रुको_updates);
	init_रुकोqueue_head(&journal->j_रुको_reserved);
	init_रुकोqueue_head(&journal->j_fc_रुको);
	mutex_init(&journal->j_पात_mutex);
	mutex_init(&journal->j_barrier);
	mutex_init(&journal->j_checkpoपूर्णांक_mutex);
	spin_lock_init(&journal->j_revoke_lock);
	spin_lock_init(&journal->j_list_lock);
	rwlock_init(&journal->j_state_lock);

	journal->j_commit_पूर्णांकerval = (HZ * JBD2_DEFAULT_MAX_COMMIT_AGE);
	journal->j_min_batch_समय = 0;
	journal->j_max_batch_समय = 15000; /* 15ms */
	atomic_set(&journal->j_reserved_credits, 0);

	/* The journal is marked क्रम error until we succeed with recovery! */
	journal->j_flags = JBD2_ABORT;

	/* Set up a शेष-sized revoke table क्रम the new mount. */
	err = jbd2_journal_init_revoke(journal, JOURNAL_REVOKE_DEFAULT_HASH);
	अगर (err)
		जाओ err_cleanup;

	spin_lock_init(&journal->j_history_lock);

	lockdep_init_map(&journal->j_trans_commit_map, "jbd2_handle",
			 &jbd2_trans_commit_key, 0);

	/* journal descriptor can store up to n blocks -bzzz */
	journal->j_blocksize = blocksize;
	journal->j_dev = bdev;
	journal->j_fs_dev = fs_dev;
	journal->j_blk_offset = start;
	journal->j_total_len = len;
	/* We need enough buffers to ग_लिखो out full descriptor block. */
	n = journal->j_blocksize / jbd2_min_tag_size();
	journal->j_wbufsize = n;
	journal->j_fc_wbuf = शून्य;
	journal->j_wbuf = kदो_स्मृति_array(n, माप(काष्ठा buffer_head *),
					GFP_KERNEL);
	अगर (!journal->j_wbuf)
		जाओ err_cleanup;

	bh = getblk_unmovable(journal->j_dev, start, journal->j_blocksize);
	अगर (!bh) अणु
		pr_err("%s: Cannot get buffer for journal superblock\n",
			__func__);
		जाओ err_cleanup;
	पूर्ण
	journal->j_sb_buffer = bh;
	journal->j_superblock = (journal_superblock_t *)bh->b_data;

	वापस journal;

err_cleanup:
	kमुक्त(journal->j_wbuf);
	jbd2_journal_destroy_revoke(journal);
	kमुक्त(journal);
	वापस शून्य;
पूर्ण

/* jbd2_journal_init_dev and jbd2_journal_init_inode:
 *
 * Create a journal काष्ठाure asचिन्हित some fixed set of disk blocks to
 * the journal.  We करोn't actually touch those disk blocks yet, but we
 * need to set up all of the mapping inक्रमmation to tell the journaling
 * प्रणाली where the journal blocks are.
 *
 */

/**
 *  journal_t * jbd2_journal_init_dev() - creates and initialises a journal काष्ठाure
 *  @bdev: Block device on which to create the journal
 *  @fs_dev: Device which hold journalled fileप्रणाली क्रम this journal.
 *  @start: Block nr Start of journal.
 *  @len:  Length of the journal in blocks.
 *  @blocksize: blocksize of journalling device
 *
 *  Returns: a newly created journal_t *
 *
 *  jbd2_journal_init_dev creates a journal which maps a fixed contiguous
 *  range of blocks on an arbitrary block device.
 *
 */
journal_t *jbd2_journal_init_dev(काष्ठा block_device *bdev,
			काष्ठा block_device *fs_dev,
			अचिन्हित दीर्घ दीर्घ start, पूर्णांक len, पूर्णांक blocksize)
अणु
	journal_t *journal;

	journal = journal_init_common(bdev, fs_dev, start, len, blocksize);
	अगर (!journal)
		वापस शून्य;

	bdevname(journal->j_dev, journal->j_devname);
	strreplace(journal->j_devname, '/', '!');
	jbd2_stats_proc_init(journal);

	वापस journal;
पूर्ण

/**
 *  journal_t * jbd2_journal_init_inode () - creates a journal which maps to a inode.
 *  @inode: An inode to create the journal in
 *
 * jbd2_journal_init_inode creates a journal which maps an on-disk inode as
 * the journal.  The inode must exist alपढ़ोy, must support bmap() and
 * must have all data blocks pपुनः_स्मृतिated.
 */
journal_t *jbd2_journal_init_inode(काष्ठा inode *inode)
अणु
	journal_t *journal;
	sector_t blocknr;
	अक्षर *p;
	पूर्णांक err = 0;

	blocknr = 0;
	err = bmap(inode, &blocknr);

	अगर (err || !blocknr) अणु
		pr_err("%s: Cannot locate journal superblock\n",
			__func__);
		वापस शून्य;
	पूर्ण

	jbd_debug(1, "JBD2: inode %s/%ld, size %lld, bits %d, blksize %ld\n",
		  inode->i_sb->s_id, inode->i_ino, (दीर्घ दीर्घ) inode->i_size,
		  inode->i_sb->s_blocksize_bits, inode->i_sb->s_blocksize);

	journal = journal_init_common(inode->i_sb->s_bdev, inode->i_sb->s_bdev,
			blocknr, inode->i_size >> inode->i_sb->s_blocksize_bits,
			inode->i_sb->s_blocksize);
	अगर (!journal)
		वापस शून्य;

	journal->j_inode = inode;
	bdevname(journal->j_dev, journal->j_devname);
	p = strreplace(journal->j_devname, '/', '!');
	प्र_लिखो(p, "-%lu", journal->j_inode->i_ino);
	jbd2_stats_proc_init(journal);

	वापस journal;
पूर्ण

/*
 * If the journal init or create पातs, we need to mark the journal
 * superblock as being शून्य to prevent the journal destroy from writing
 * back a bogus superblock.
 */
अटल व्योम journal_fail_superblock(journal_t *journal)
अणु
	काष्ठा buffer_head *bh = journal->j_sb_buffer;
	brअन्यथा(bh);
	journal->j_sb_buffer = शून्य;
पूर्ण

/*
 * Given a journal_t काष्ठाure, initialise the various fields क्रम
 * startup of a new journaling session.  We use this both when creating
 * a journal, and after recovering an old journal to reset it क्रम
 * subsequent use.
 */

अटल पूर्णांक journal_reset(journal_t *journal)
अणु
	journal_superblock_t *sb = journal->j_superblock;
	अचिन्हित दीर्घ दीर्घ first, last;

	first = be32_to_cpu(sb->s_first);
	last = be32_to_cpu(sb->s_maxlen);
	अगर (first + JBD2_MIN_JOURNAL_BLOCKS > last + 1) अणु
		prपूर्णांकk(KERN_ERR "JBD2: Journal too short (blocks %llu-%llu).\n",
		       first, last);
		journal_fail_superblock(journal);
		वापस -EINVAL;
	पूर्ण

	journal->j_first = first;
	journal->j_last = last;

	journal->j_head = journal->j_first;
	journal->j_tail = journal->j_first;
	journal->j_मुक्त = journal->j_last - journal->j_first;

	journal->j_tail_sequence = journal->j_transaction_sequence;
	journal->j_commit_sequence = journal->j_transaction_sequence - 1;
	journal->j_commit_request = journal->j_commit_sequence;

	journal->j_max_transaction_buffers = jbd2_journal_get_max_txn_bufs(journal);

	/*
	 * Now that journal recovery is करोne, turn fast commits off here. This
	 * way, अगर fast commit was enabled beक्रमe the crash but अगर now FS has
	 * disabled it, we करोn't enable fast commits.
	 */
	jbd2_clear_feature_fast_commit(journal);

	/*
	 * As a special हाल, अगर the on-disk copy is alपढ़ोy marked as needing
	 * no recovery (s_start == 0), then we can safely defer the superblock
	 * update until the next commit by setting JBD2_FLUSHED.  This aव्योमs
	 * attempting a ग_लिखो to a potential-पढ़ोonly device.
	 */
	अगर (sb->s_start == 0) अणु
		jbd_debug(1, "JBD2: Skipping superblock update on recovered sb "
			"(start %ld, seq %u, errno %d)\n",
			journal->j_tail, journal->j_tail_sequence,
			journal->j_त्रुटि_सं);
		journal->j_flags |= JBD2_FLUSHED;
	पूर्ण अन्यथा अणु
		/* Lock here to make निश्चितions happy... */
		mutex_lock_io(&journal->j_checkpoपूर्णांक_mutex);
		/*
		 * Update log tail inक्रमmation. We use REQ_FUA since new
		 * transaction will start reusing journal space and so we
		 * must make sure inक्रमmation about current log tail is on
		 * disk beक्रमe that.
		 */
		jbd2_journal_update_sb_log_tail(journal,
						journal->j_tail_sequence,
						journal->j_tail,
						REQ_SYNC | REQ_FUA);
		mutex_unlock(&journal->j_checkpoपूर्णांक_mutex);
	पूर्ण
	वापस jbd2_journal_start_thपढ़ो(journal);
पूर्ण

/*
 * This function expects that the caller will have locked the journal
 * buffer head, and will वापस with it unlocked
 */
अटल पूर्णांक jbd2_ग_लिखो_superblock(journal_t *journal, पूर्णांक ग_लिखो_flags)
अणु
	काष्ठा buffer_head *bh = journal->j_sb_buffer;
	journal_superblock_t *sb = journal->j_superblock;
	पूर्णांक ret;

	/* Buffer got discarded which means block device got invalidated */
	अगर (!buffer_mapped(bh)) अणु
		unlock_buffer(bh);
		वापस -EIO;
	पूर्ण

	trace_jbd2_ग_लिखो_superblock(journal, ग_लिखो_flags);
	अगर (!(journal->j_flags & JBD2_BARRIER))
		ग_लिखो_flags &= ~(REQ_FUA | REQ_PREFLUSH);
	अगर (buffer_ग_लिखो_io_error(bh)) अणु
		/*
		 * Oh, dear.  A previous attempt to ग_लिखो the journal
		 * superblock failed.  This could happen because the
		 * USB device was yanked out.  Or it could happen to
		 * be a transient ग_लिखो error and maybe the block will
		 * be remapped.  Nothing we can करो but to retry the
		 * ग_लिखो and hope क्रम the best.
		 */
		prपूर्णांकk(KERN_ERR "JBD2: previous I/O error detected "
		       "for journal superblock update for %s.\n",
		       journal->j_devname);
		clear_buffer_ग_लिखो_io_error(bh);
		set_buffer_uptodate(bh);
	पूर्ण
	अगर (jbd2_journal_has_csum_v2or3(journal))
		sb->s_checksum = jbd2_superblock_csum(journal, sb);
	get_bh(bh);
	bh->b_end_io = end_buffer_ग_लिखो_sync;
	ret = submit_bh(REQ_OP_WRITE, ग_लिखो_flags, bh);
	रुको_on_buffer(bh);
	अगर (buffer_ग_लिखो_io_error(bh)) अणु
		clear_buffer_ग_लिखो_io_error(bh);
		set_buffer_uptodate(bh);
		ret = -EIO;
	पूर्ण
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "JBD2: Error %d detected when updating "
		       "journal superblock for %s.\n", ret,
		       journal->j_devname);
		अगर (!is_journal_पातed(journal))
			jbd2_journal_पात(journal, ret);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * jbd2_journal_update_sb_log_tail() - Update log tail in journal sb on disk.
 * @journal: The journal to update.
 * @tail_tid: TID of the new transaction at the tail of the log
 * @tail_block: The first block of the transaction at the tail of the log
 * @ग_लिखो_op: With which operation should we ग_लिखो the journal sb
 *
 * Update a journal's superblock inक्रमmation about log tail and ग_लिखो it to
 * disk, रुकोing क्रम the IO to complete.
 */
पूर्णांक jbd2_journal_update_sb_log_tail(journal_t *journal, tid_t tail_tid,
				     अचिन्हित दीर्घ tail_block, पूर्णांक ग_लिखो_op)
अणु
	journal_superblock_t *sb = journal->j_superblock;
	पूर्णांक ret;

	अगर (is_journal_पातed(journal))
		वापस -EIO;

	BUG_ON(!mutex_is_locked(&journal->j_checkpoपूर्णांक_mutex));
	jbd_debug(1, "JBD2: updating superblock (start %lu, seq %u)\n",
		  tail_block, tail_tid);

	lock_buffer(journal->j_sb_buffer);
	sb->s_sequence = cpu_to_be32(tail_tid);
	sb->s_start    = cpu_to_be32(tail_block);

	ret = jbd2_ग_लिखो_superblock(journal, ग_लिखो_op);
	अगर (ret)
		जाओ out;

	/* Log is no दीर्घer empty */
	ग_लिखो_lock(&journal->j_state_lock);
	WARN_ON(!sb->s_sequence);
	journal->j_flags &= ~JBD2_FLUSHED;
	ग_लिखो_unlock(&journal->j_state_lock);

out:
	वापस ret;
पूर्ण

/**
 * jbd2_mark_journal_empty() - Mark on disk journal as empty.
 * @journal: The journal to update.
 * @ग_लिखो_op: With which operation should we ग_लिखो the journal sb
 *
 * Update a journal's dynamic superblock fields to show that journal is empty.
 * Write updated superblock to disk रुकोing क्रम IO to complete.
 */
अटल व्योम jbd2_mark_journal_empty(journal_t *journal, पूर्णांक ग_लिखो_op)
अणु
	journal_superblock_t *sb = journal->j_superblock;
	bool had_fast_commit = false;

	BUG_ON(!mutex_is_locked(&journal->j_checkpoपूर्णांक_mutex));
	lock_buffer(journal->j_sb_buffer);
	अगर (sb->s_start == 0) अणु		/* Is it alपढ़ोy empty? */
		unlock_buffer(journal->j_sb_buffer);
		वापस;
	पूर्ण

	jbd_debug(1, "JBD2: Marking journal as empty (seq %u)\n",
		  journal->j_tail_sequence);

	sb->s_sequence = cpu_to_be32(journal->j_tail_sequence);
	sb->s_start    = cpu_to_be32(0);
	अगर (jbd2_has_feature_fast_commit(journal)) अणु
		/*
		 * When journal is clean, no need to commit fast commit flag and
		 * make file प्रणाली incompatible with older kernels.
		 */
		jbd2_clear_feature_fast_commit(journal);
		had_fast_commit = true;
	पूर्ण

	jbd2_ग_लिखो_superblock(journal, ग_लिखो_op);

	अगर (had_fast_commit)
		jbd2_set_feature_fast_commit(journal);

	/* Log is no दीर्घer empty */
	ग_लिखो_lock(&journal->j_state_lock);
	journal->j_flags |= JBD2_FLUSHED;
	ग_लिखो_unlock(&journal->j_state_lock);
पूर्ण


/**
 * jbd2_journal_update_sb_त्रुटि_सं() - Update error in the journal.
 * @journal: The journal to update.
 *
 * Update a journal's त्रुटि_सं.  Write updated superblock to disk रुकोing क्रम IO
 * to complete.
 */
व्योम jbd2_journal_update_sb_त्रुटि_सं(journal_t *journal)
अणु
	journal_superblock_t *sb = journal->j_superblock;
	पूर्णांक errcode;

	lock_buffer(journal->j_sb_buffer);
	errcode = journal->j_त्रुटि_सं;
	अगर (errcode == -ESHUTDOWN)
		errcode = 0;
	jbd_debug(1, "JBD2: updating superblock error (errno %d)\n", errcode);
	sb->s_त्रुटि_सं    = cpu_to_be32(errcode);

	jbd2_ग_लिखो_superblock(journal, REQ_SYNC | REQ_FUA);
पूर्ण
EXPORT_SYMBOL(jbd2_journal_update_sb_त्रुटि_सं);

अटल पूर्णांक journal_revoke_records_per_block(journal_t *journal)
अणु
	पूर्णांक record_size;
	पूर्णांक space = journal->j_blocksize - माप(jbd2_journal_revoke_header_t);

	अगर (jbd2_has_feature_64bit(journal))
		record_size = 8;
	अन्यथा
		record_size = 4;

	अगर (jbd2_journal_has_csum_v2or3(journal))
		space -= माप(काष्ठा jbd2_journal_block_tail);
	वापस space / record_size;
पूर्ण

/*
 * Read the superblock क्रम a given journal, perक्रमming initial
 * validation of the क्रमmat.
 */
अटल पूर्णांक journal_get_superblock(journal_t *journal)
अणु
	काष्ठा buffer_head *bh;
	journal_superblock_t *sb;
	पूर्णांक err = -EIO;

	bh = journal->j_sb_buffer;

	J_ASSERT(bh != शून्य);
	अगर (!buffer_uptodate(bh)) अणु
		ll_rw_block(REQ_OP_READ, 0, 1, &bh);
		रुको_on_buffer(bh);
		अगर (!buffer_uptodate(bh)) अणु
			prपूर्णांकk(KERN_ERR
				"JBD2: IO error reading journal superblock\n");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (buffer_verअगरied(bh))
		वापस 0;

	sb = journal->j_superblock;

	err = -EINVAL;

	अगर (sb->s_header.h_magic != cpu_to_be32(JBD2_MAGIC_NUMBER) ||
	    sb->s_blocksize != cpu_to_be32(journal->j_blocksize)) अणु
		prपूर्णांकk(KERN_WARNING "JBD2: no valid journal superblock found\n");
		जाओ out;
	पूर्ण

	चयन(be32_to_cpu(sb->s_header.h_blocktype)) अणु
	हाल JBD2_SUPERBLOCK_V1:
		journal->j_क्रमmat_version = 1;
		अवरोध;
	हाल JBD2_SUPERBLOCK_V2:
		journal->j_क्रमmat_version = 2;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "JBD2: unrecognised superblock format ID\n");
		जाओ out;
	पूर्ण

	अगर (be32_to_cpu(sb->s_maxlen) < journal->j_total_len)
		journal->j_total_len = be32_to_cpu(sb->s_maxlen);
	अन्यथा अगर (be32_to_cpu(sb->s_maxlen) > journal->j_total_len) अणु
		prपूर्णांकk(KERN_WARNING "JBD2: journal file too short\n");
		जाओ out;
	पूर्ण

	अगर (be32_to_cpu(sb->s_first) == 0 ||
	    be32_to_cpu(sb->s_first) >= journal->j_total_len) अणु
		prपूर्णांकk(KERN_WARNING
			"JBD2: Invalid start block of journal: %u\n",
			be32_to_cpu(sb->s_first));
		जाओ out;
	पूर्ण

	अगर (jbd2_has_feature_csum2(journal) &&
	    jbd2_has_feature_csum3(journal)) अणु
		/* Can't have checksum v2 and v3 at the same समय! */
		prपूर्णांकk(KERN_ERR "JBD2: Can't enable checksumming v2 and v3 "
		       "at the same time!\n");
		जाओ out;
	पूर्ण

	अगर (jbd2_journal_has_csum_v2or3_feature(journal) &&
	    jbd2_has_feature_checksum(journal)) अणु
		/* Can't have checksum v1 and v2 on at the same समय! */
		prपूर्णांकk(KERN_ERR "JBD2: Can't enable checksumming v1 and v2/3 "
		       "at the same time!\n");
		जाओ out;
	पूर्ण

	अगर (!jbd2_verअगरy_csum_type(journal, sb)) अणु
		prपूर्णांकk(KERN_ERR "JBD2: Unknown checksum type\n");
		जाओ out;
	पूर्ण

	/* Load the checksum driver */
	अगर (jbd2_journal_has_csum_v2or3_feature(journal)) अणु
		journal->j_chksum_driver = crypto_alloc_shash("crc32c", 0, 0);
		अगर (IS_ERR(journal->j_chksum_driver)) अणु
			prपूर्णांकk(KERN_ERR "JBD2: Cannot load crc32c driver.\n");
			err = PTR_ERR(journal->j_chksum_driver);
			journal->j_chksum_driver = शून्य;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (jbd2_journal_has_csum_v2or3(journal)) अणु
		/* Check superblock checksum */
		अगर (sb->s_checksum != jbd2_superblock_csum(journal, sb)) अणु
			prपूर्णांकk(KERN_ERR "JBD2: journal checksum error\n");
			err = -EFSBADCRC;
			जाओ out;
		पूर्ण

		/* Precompute checksum seed क्रम all metadata */
		journal->j_csum_seed = jbd2_chksum(journal, ~0, sb->s_uuid,
						   माप(sb->s_uuid));
	पूर्ण

	journal->j_revoke_records_per_block =
				journal_revoke_records_per_block(journal);
	set_buffer_verअगरied(bh);

	वापस 0;

out:
	journal_fail_superblock(journal);
	वापस err;
पूर्ण

/*
 * Load the on-disk journal superblock and पढ़ो the key fields पूर्णांकo the
 * journal_t.
 */

अटल पूर्णांक load_superblock(journal_t *journal)
अणु
	पूर्णांक err;
	journal_superblock_t *sb;
	पूर्णांक num_fc_blocks;

	err = journal_get_superblock(journal);
	अगर (err)
		वापस err;

	sb = journal->j_superblock;

	journal->j_tail_sequence = be32_to_cpu(sb->s_sequence);
	journal->j_tail = be32_to_cpu(sb->s_start);
	journal->j_first = be32_to_cpu(sb->s_first);
	journal->j_त्रुटि_सं = be32_to_cpu(sb->s_त्रुटि_सं);
	journal->j_last = be32_to_cpu(sb->s_maxlen);

	अगर (jbd2_has_feature_fast_commit(journal)) अणु
		journal->j_fc_last = be32_to_cpu(sb->s_maxlen);
		num_fc_blocks = jbd2_journal_get_num_fc_blks(sb);
		अगर (journal->j_last - num_fc_blocks >= JBD2_MIN_JOURNAL_BLOCKS)
			journal->j_last = journal->j_fc_last - num_fc_blocks;
		journal->j_fc_first = journal->j_last + 1;
		journal->j_fc_off = 0;
	पूर्ण

	वापस 0;
पूर्ण


/**
 * jbd2_journal_load() - Read journal from disk.
 * @journal: Journal to act on.
 *
 * Given a journal_t काष्ठाure which tells us which disk blocks contain
 * a journal, पढ़ो the journal from disk to initialise the in-memory
 * काष्ठाures.
 */
पूर्णांक jbd2_journal_load(journal_t *journal)
अणु
	पूर्णांक err;
	journal_superblock_t *sb;

	err = load_superblock(journal);
	अगर (err)
		वापस err;

	sb = journal->j_superblock;
	/* If this is a V2 superblock, then we have to check the
	 * features flags on it. */

	अगर (journal->j_क्रमmat_version >= 2) अणु
		अगर ((sb->s_feature_ro_compat &
		     ~cpu_to_be32(JBD2_KNOWN_ROCOMPAT_FEATURES)) ||
		    (sb->s_feature_incompat &
		     ~cpu_to_be32(JBD2_KNOWN_INCOMPAT_FEATURES))) अणु
			prपूर्णांकk(KERN_WARNING
				"JBD2: Unrecognised features on journal\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * Create a slab क्रम this blocksize
	 */
	err = jbd2_journal_create_slab(be32_to_cpu(sb->s_blocksize));
	अगर (err)
		वापस err;

	/* Let the recovery code check whether it needs to recover any
	 * data from the journal. */
	अगर (jbd2_journal_recover(journal))
		जाओ recovery_error;

	अगर (journal->j_failed_commit) अणु
		prपूर्णांकk(KERN_ERR "JBD2: journal transaction %u on %s "
		       "is corrupt.\n", journal->j_failed_commit,
		       journal->j_devname);
		वापस -EFSCORRUPTED;
	पूर्ण
	/*
	 * clear JBD2_ABORT flag initialized in journal_init_common
	 * here to update log tail inक्रमmation with the newest seq.
	 */
	journal->j_flags &= ~JBD2_ABORT;

	/* OK, we've finished with the dynamic journal bits:
	 * reinitialise the dynamic contents of the superblock in memory
	 * and reset them on disk. */
	अगर (journal_reset(journal))
		जाओ recovery_error;

	journal->j_flags |= JBD2_LOADED;
	वापस 0;

recovery_error:
	prपूर्णांकk(KERN_WARNING "JBD2: recovery failed\n");
	वापस -EIO;
पूर्ण

/**
 * jbd2_journal_destroy() - Release a journal_t काष्ठाure.
 * @journal: Journal to act on.
 *
 * Release a journal_t काष्ठाure once it is no दीर्घer in use by the
 * journaled object.
 * Return <0 अगर we couldn't clean up the journal.
 */
पूर्णांक jbd2_journal_destroy(journal_t *journal)
अणु
	पूर्णांक err = 0;

	/* Wait क्रम the commit thपढ़ो to wake up and die. */
	journal_समाप्त_thपढ़ो(journal);

	/* Force a final log commit */
	अगर (journal->j_running_transaction)
		jbd2_journal_commit_transaction(journal);

	/* Force any old transactions to disk */

	/* Totally anal locking here... */
	spin_lock(&journal->j_list_lock);
	जबतक (journal->j_checkpoपूर्णांक_transactions != शून्य) अणु
		spin_unlock(&journal->j_list_lock);
		mutex_lock_io(&journal->j_checkpoपूर्णांक_mutex);
		err = jbd2_log_करो_checkpoपूर्णांक(journal);
		mutex_unlock(&journal->j_checkpoपूर्णांक_mutex);
		/*
		 * If checkpoपूर्णांकing failed, just मुक्त the buffers to aव्योम
		 * looping क्रमever
		 */
		अगर (err) अणु
			jbd2_journal_destroy_checkpoपूर्णांक(journal);
			spin_lock(&journal->j_list_lock);
			अवरोध;
		पूर्ण
		spin_lock(&journal->j_list_lock);
	पूर्ण

	J_ASSERT(journal->j_running_transaction == शून्य);
	J_ASSERT(journal->j_committing_transaction == शून्य);
	J_ASSERT(journal->j_checkpoपूर्णांक_transactions == शून्य);
	spin_unlock(&journal->j_list_lock);

	अगर (journal->j_sb_buffer) अणु
		अगर (!is_journal_पातed(journal)) अणु
			mutex_lock_io(&journal->j_checkpoपूर्णांक_mutex);

			ग_लिखो_lock(&journal->j_state_lock);
			journal->j_tail_sequence =
				++journal->j_transaction_sequence;
			ग_लिखो_unlock(&journal->j_state_lock);

			jbd2_mark_journal_empty(journal,
					REQ_SYNC | REQ_PREFLUSH | REQ_FUA);
			mutex_unlock(&journal->j_checkpoपूर्णांक_mutex);
		पूर्ण अन्यथा
			err = -EIO;
		brअन्यथा(journal->j_sb_buffer);
	पूर्ण

	अगर (journal->j_proc_entry)
		jbd2_stats_proc_निकास(journal);
	iput(journal->j_inode);
	अगर (journal->j_revoke)
		jbd2_journal_destroy_revoke(journal);
	अगर (journal->j_chksum_driver)
		crypto_मुक्त_shash(journal->j_chksum_driver);
	kमुक्त(journal->j_fc_wbuf);
	kमुक्त(journal->j_wbuf);
	kमुक्त(journal);

	वापस err;
पूर्ण


/**
 * jbd2_journal_check_used_features() - Check अगर features specअगरied are used.
 * @journal: Journal to check.
 * @compat: biपंचांगask of compatible features
 * @ro: biपंचांगask of features that क्रमce पढ़ो-only mount
 * @incompat: biपंचांगask of incompatible features
 *
 * Check whether the journal uses all of a given set of
 * features.  Return true (non-zero) अगर it करोes.
 **/

पूर्णांक jbd2_journal_check_used_features(journal_t *journal, अचिन्हित दीर्घ compat,
				 अचिन्हित दीर्घ ro, अचिन्हित दीर्घ incompat)
अणु
	journal_superblock_t *sb;

	अगर (!compat && !ro && !incompat)
		वापस 1;
	/* Load journal superblock अगर it is not loaded yet. */
	अगर (journal->j_क्रमmat_version == 0 &&
	    journal_get_superblock(journal) != 0)
		वापस 0;
	अगर (journal->j_क्रमmat_version == 1)
		वापस 0;

	sb = journal->j_superblock;

	अगर (((be32_to_cpu(sb->s_feature_compat) & compat) == compat) &&
	    ((be32_to_cpu(sb->s_feature_ro_compat) & ro) == ro) &&
	    ((be32_to_cpu(sb->s_feature_incompat) & incompat) == incompat))
		वापस 1;

	वापस 0;
पूर्ण

/**
 * jbd2_journal_check_available_features() - Check feature set in journalling layer
 * @journal: Journal to check.
 * @compat: biपंचांगask of compatible features
 * @ro: biपंचांगask of features that क्रमce पढ़ो-only mount
 * @incompat: biपंचांगask of incompatible features
 *
 * Check whether the journaling code supports the use of
 * all of a given set of features on this journal.  Return true
 * (non-zero) अगर it can. */

पूर्णांक jbd2_journal_check_available_features(journal_t *journal, अचिन्हित दीर्घ compat,
				      अचिन्हित दीर्घ ro, अचिन्हित दीर्घ incompat)
अणु
	अगर (!compat && !ro && !incompat)
		वापस 1;

	/* We can support any known requested features अगरf the
	 * superblock is in version 2.  Otherwise we fail to support any
	 * extended sb features. */

	अगर (journal->j_क्रमmat_version != 2)
		वापस 0;

	अगर ((compat   & JBD2_KNOWN_COMPAT_FEATURES) == compat &&
	    (ro       & JBD2_KNOWN_ROCOMPAT_FEATURES) == ro &&
	    (incompat & JBD2_KNOWN_INCOMPAT_FEATURES) == incompat)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक
jbd2_journal_initialize_fast_commit(journal_t *journal)
अणु
	journal_superblock_t *sb = journal->j_superblock;
	अचिन्हित दीर्घ दीर्घ num_fc_blks;

	num_fc_blks = jbd2_journal_get_num_fc_blks(sb);
	अगर (journal->j_last - num_fc_blks < JBD2_MIN_JOURNAL_BLOCKS)
		वापस -ENOSPC;

	/* Are we called twice? */
	WARN_ON(journal->j_fc_wbuf != शून्य);
	journal->j_fc_wbuf = kदो_स्मृति_array(num_fc_blks,
				माप(काष्ठा buffer_head *), GFP_KERNEL);
	अगर (!journal->j_fc_wbuf)
		वापस -ENOMEM;

	journal->j_fc_wbufsize = num_fc_blks;
	journal->j_fc_last = journal->j_last;
	journal->j_last = journal->j_fc_last - num_fc_blks;
	journal->j_fc_first = journal->j_last + 1;
	journal->j_fc_off = 0;
	journal->j_मुक्त = journal->j_last - journal->j_first;
	journal->j_max_transaction_buffers =
		jbd2_journal_get_max_txn_bufs(journal);

	वापस 0;
पूर्ण

/**
 * jbd2_journal_set_features() - Mark a given journal feature in the superblock
 * @journal: Journal to act on.
 * @compat: biपंचांगask of compatible features
 * @ro: biपंचांगask of features that क्रमce पढ़ो-only mount
 * @incompat: biपंचांगask of incompatible features
 *
 * Mark a given journal feature as present on the
 * superblock.  Returns true अगर the requested features could be set.
 *
 */

पूर्णांक jbd2_journal_set_features(journal_t *journal, अचिन्हित दीर्घ compat,
			  अचिन्हित दीर्घ ro, अचिन्हित दीर्घ incompat)
अणु
#घोषणा INCOMPAT_FEATURE_ON(f) \
		((incompat & (f)) && !(sb->s_feature_incompat & cpu_to_be32(f)))
#घोषणा COMPAT_FEATURE_ON(f) \
		((compat & (f)) && !(sb->s_feature_compat & cpu_to_be32(f)))
	journal_superblock_t *sb;

	अगर (jbd2_journal_check_used_features(journal, compat, ro, incompat))
		वापस 1;

	अगर (!jbd2_journal_check_available_features(journal, compat, ro, incompat))
		वापस 0;

	/* If enabling v2 checksums, turn on v3 instead */
	अगर (incompat & JBD2_FEATURE_INCOMPAT_CSUM_V2) अणु
		incompat &= ~JBD2_FEATURE_INCOMPAT_CSUM_V2;
		incompat |= JBD2_FEATURE_INCOMPAT_CSUM_V3;
	पूर्ण

	/* Asking क्रम checksumming v3 and v1?  Only give them v3. */
	अगर (incompat & JBD2_FEATURE_INCOMPAT_CSUM_V3 &&
	    compat & JBD2_FEATURE_COMPAT_CHECKSUM)
		compat &= ~JBD2_FEATURE_COMPAT_CHECKSUM;

	jbd_debug(1, "Setting new features 0x%lx/0x%lx/0x%lx\n",
		  compat, ro, incompat);

	sb = journal->j_superblock;

	अगर (incompat & JBD2_FEATURE_INCOMPAT_FAST_COMMIT) अणु
		अगर (jbd2_journal_initialize_fast_commit(journal)) अणु
			pr_err("JBD2: Cannot enable fast commits.\n");
			वापस 0;
		पूर्ण
	पूर्ण

	/* Load the checksum driver अगर necessary */
	अगर ((journal->j_chksum_driver == शून्य) &&
	    INCOMPAT_FEATURE_ON(JBD2_FEATURE_INCOMPAT_CSUM_V3)) अणु
		journal->j_chksum_driver = crypto_alloc_shash("crc32c", 0, 0);
		अगर (IS_ERR(journal->j_chksum_driver)) अणु
			prपूर्णांकk(KERN_ERR "JBD2: Cannot load crc32c driver.\n");
			journal->j_chksum_driver = शून्य;
			वापस 0;
		पूर्ण
		/* Precompute checksum seed क्रम all metadata */
		journal->j_csum_seed = jbd2_chksum(journal, ~0, sb->s_uuid,
						   माप(sb->s_uuid));
	पूर्ण

	lock_buffer(journal->j_sb_buffer);

	/* If enabling v3 checksums, update superblock */
	अगर (INCOMPAT_FEATURE_ON(JBD2_FEATURE_INCOMPAT_CSUM_V3)) अणु
		sb->s_checksum_type = JBD2_CRC32C_CHKSUM;
		sb->s_feature_compat &=
			~cpu_to_be32(JBD2_FEATURE_COMPAT_CHECKSUM);
	पूर्ण

	/* If enabling v1 checksums, करोwngrade superblock */
	अगर (COMPAT_FEATURE_ON(JBD2_FEATURE_COMPAT_CHECKSUM))
		sb->s_feature_incompat &=
			~cpu_to_be32(JBD2_FEATURE_INCOMPAT_CSUM_V2 |
				     JBD2_FEATURE_INCOMPAT_CSUM_V3);

	sb->s_feature_compat    |= cpu_to_be32(compat);
	sb->s_feature_ro_compat |= cpu_to_be32(ro);
	sb->s_feature_incompat  |= cpu_to_be32(incompat);
	unlock_buffer(journal->j_sb_buffer);
	journal->j_revoke_records_per_block =
				journal_revoke_records_per_block(journal);

	वापस 1;
#अघोषित COMPAT_FEATURE_ON
#अघोषित INCOMPAT_FEATURE_ON
पूर्ण

/*
 * jbd2_journal_clear_features() - Clear a given journal feature in the
 * 				    superblock
 * @journal: Journal to act on.
 * @compat: biपंचांगask of compatible features
 * @ro: biपंचांगask of features that क्रमce पढ़ो-only mount
 * @incompat: biपंचांगask of incompatible features
 *
 * Clear a given journal feature as present on the
 * superblock.
 */
व्योम jbd2_journal_clear_features(journal_t *journal, अचिन्हित दीर्घ compat,
				अचिन्हित दीर्घ ro, अचिन्हित दीर्घ incompat)
अणु
	journal_superblock_t *sb;

	jbd_debug(1, "Clear features 0x%lx/0x%lx/0x%lx\n",
		  compat, ro, incompat);

	sb = journal->j_superblock;

	sb->s_feature_compat    &= ~cpu_to_be32(compat);
	sb->s_feature_ro_compat &= ~cpu_to_be32(ro);
	sb->s_feature_incompat  &= ~cpu_to_be32(incompat);
	journal->j_revoke_records_per_block =
				journal_revoke_records_per_block(journal);
पूर्ण
EXPORT_SYMBOL(jbd2_journal_clear_features);

/**
 * jbd2_journal_flush() - Flush journal
 * @journal: Journal to act on.
 *
 * Flush all data क्रम a given journal to disk and empty the journal.
 * Fileप्रणालीs can use this when remounting पढ़ोonly to ensure that
 * recovery करोes not need to happen on remount.
 */

पूर्णांक jbd2_journal_flush(journal_t *journal)
अणु
	पूर्णांक err = 0;
	transaction_t *transaction = शून्य;

	ग_लिखो_lock(&journal->j_state_lock);

	/* Force everything buffered to the log... */
	अगर (journal->j_running_transaction) अणु
		transaction = journal->j_running_transaction;
		__jbd2_log_start_commit(journal, transaction->t_tid);
	पूर्ण अन्यथा अगर (journal->j_committing_transaction)
		transaction = journal->j_committing_transaction;

	/* Wait क्रम the log commit to complete... */
	अगर (transaction) अणु
		tid_t tid = transaction->t_tid;

		ग_लिखो_unlock(&journal->j_state_lock);
		jbd2_log_रुको_commit(journal, tid);
	पूर्ण अन्यथा अणु
		ग_लिखो_unlock(&journal->j_state_lock);
	पूर्ण

	/* ...and flush everything in the log out to disk. */
	spin_lock(&journal->j_list_lock);
	जबतक (!err && journal->j_checkpoपूर्णांक_transactions != शून्य) अणु
		spin_unlock(&journal->j_list_lock);
		mutex_lock_io(&journal->j_checkpoपूर्णांक_mutex);
		err = jbd2_log_करो_checkpoपूर्णांक(journal);
		mutex_unlock(&journal->j_checkpoपूर्णांक_mutex);
		spin_lock(&journal->j_list_lock);
	पूर्ण
	spin_unlock(&journal->j_list_lock);

	अगर (is_journal_पातed(journal))
		वापस -EIO;

	mutex_lock_io(&journal->j_checkpoपूर्णांक_mutex);
	अगर (!err) अणु
		err = jbd2_cleanup_journal_tail(journal);
		अगर (err < 0) अणु
			mutex_unlock(&journal->j_checkpoपूर्णांक_mutex);
			जाओ out;
		पूर्ण
		err = 0;
	पूर्ण

	/* Finally, mark the journal as really needing no recovery.
	 * This sets s_start==0 in the underlying superblock, which is
	 * the magic code क्रम a fully-recovered superblock.  Any future
	 * commits of data to the journal will restore the current
	 * s_start value. */
	jbd2_mark_journal_empty(journal, REQ_SYNC | REQ_FUA);
	mutex_unlock(&journal->j_checkpoपूर्णांक_mutex);
	ग_लिखो_lock(&journal->j_state_lock);
	J_ASSERT(!journal->j_running_transaction);
	J_ASSERT(!journal->j_committing_transaction);
	J_ASSERT(!journal->j_checkpoपूर्णांक_transactions);
	J_ASSERT(journal->j_head == journal->j_tail);
	J_ASSERT(journal->j_tail_sequence == journal->j_transaction_sequence);
	ग_लिखो_unlock(&journal->j_state_lock);
out:
	वापस err;
पूर्ण

/**
 * jbd2_journal_wipe() - Wipe journal contents
 * @journal: Journal to act on.
 * @ग_लिखो: flag (see below)
 *
 * Wipe out all of the contents of a journal, safely.  This will produce
 * a warning अगर the journal contains any valid recovery inक्रमmation.
 * Must be called between journal_init_*() and jbd2_journal_load().
 *
 * If 'write' is non-zero, then we wipe out the journal on disk; otherwise
 * we merely suppress recovery.
 */

पूर्णांक jbd2_journal_wipe(journal_t *journal, पूर्णांक ग_लिखो)
अणु
	पूर्णांक err = 0;

	J_ASSERT (!(journal->j_flags & JBD2_LOADED));

	err = load_superblock(journal);
	अगर (err)
		वापस err;

	अगर (!journal->j_tail)
		जाओ no_recovery;

	prपूर्णांकk(KERN_WARNING "JBD2: %s recovery information on journal\n",
		ग_लिखो ? "Clearing" : "Ignoring");

	err = jbd2_journal_skip_recovery(journal);
	अगर (ग_लिखो) अणु
		/* Lock to make निश्चितions happy... */
		mutex_lock_io(&journal->j_checkpoपूर्णांक_mutex);
		jbd2_mark_journal_empty(journal, REQ_SYNC | REQ_FUA);
		mutex_unlock(&journal->j_checkpoपूर्णांक_mutex);
	पूर्ण

 no_recovery:
	वापस err;
पूर्ण

/**
 * jbd2_journal_पात () - Shutकरोwn the journal immediately.
 * @journal: the journal to shutकरोwn.
 * @त्रुटि_सं:   an error number to record in the journal indicating
 *           the reason क्रम the shutकरोwn.
 *
 * Perक्रमm a complete, immediate shutकरोwn of the ENTIRE
 * journal (not of a single transaction).  This operation cannot be
 * unकरोne without closing and reखोलोing the journal.
 *
 * The jbd2_journal_पात function is पूर्णांकended to support higher level error
 * recovery mechanisms such as the ext2/ext3 remount-पढ़ोonly error
 * mode.
 *
 * Journal पात has very specअगरic semantics.  Any existing dirty,
 * unjournaled buffers in the मुख्य fileप्रणाली will still be written to
 * disk by bdflush, but the journaling mechanism will be suspended
 * immediately and no further transaction commits will be honoured.
 *
 * Any dirty, journaled buffers will be written back to disk without
 * hitting the journal.  Atomicity cannot be guaranteed on an पातed
 * fileप्रणाली, but we _करो_ attempt to leave as much data as possible
 * behind क्रम fsck to use क्रम cleanup.
 *
 * Any attempt to get a new transaction handle on a journal which is in
 * ABORT state will just result in an -EROFS error वापस.  A
 * jbd2_journal_stop on an existing handle will वापस -EIO अगर we have
 * entered पात state during the update.
 *
 * Recursive transactions are not disturbed by journal पात until the
 * final jbd2_journal_stop, which will receive the -EIO error.
 *
 * Finally, the jbd2_journal_पात call allows the caller to supply an त्रुटि_सं
 * which will be recorded (अगर possible) in the journal superblock.  This
 * allows a client to record failure conditions in the middle of a
 * transaction without having to complete the transaction to record the
 * failure to disk.  ext3_error, क्रम example, now uses this
 * functionality.
 *
 */

व्योम jbd2_journal_पात(journal_t *journal, पूर्णांक त्रुटि_सं)
अणु
	transaction_t *transaction;

	/*
	 * Lock the पातing procedure until everything is करोne, this aव्योम
	 * races between fileप्रणाली's error handling flow (e.g. ext4_पात()),
	 * ensure panic after the error info is written पूर्णांकo journal's
	 * superblock.
	 */
	mutex_lock(&journal->j_पात_mutex);
	/*
	 * ESHUTDOWN always takes precedence because a file प्रणाली check
	 * caused by any other journal पात error is not required after
	 * a shutकरोwn triggered.
	 */
	ग_लिखो_lock(&journal->j_state_lock);
	अगर (journal->j_flags & JBD2_ABORT) अणु
		पूर्णांक old_त्रुटि_सं = journal->j_त्रुटि_सं;

		ग_लिखो_unlock(&journal->j_state_lock);
		अगर (old_त्रुटि_सं != -ESHUTDOWN && त्रुटि_सं == -ESHUTDOWN) अणु
			journal->j_त्रुटि_सं = त्रुटि_सं;
			jbd2_journal_update_sb_त्रुटि_सं(journal);
		पूर्ण
		mutex_unlock(&journal->j_पात_mutex);
		वापस;
	पूर्ण

	/*
	 * Mark the पात as occurred and start current running transaction
	 * to release all journaled buffer.
	 */
	pr_err("Aborting journal on device %s.\n", journal->j_devname);

	journal->j_flags |= JBD2_ABORT;
	journal->j_त्रुटि_सं = त्रुटि_सं;
	transaction = journal->j_running_transaction;
	अगर (transaction)
		__jbd2_log_start_commit(journal, transaction->t_tid);
	ग_लिखो_unlock(&journal->j_state_lock);

	/*
	 * Record त्रुटि_सं to the journal super block, so that fsck and jbd2
	 * layer could realise that a fileप्रणाली check is needed.
	 */
	jbd2_journal_update_sb_त्रुटि_सं(journal);
	mutex_unlock(&journal->j_पात_mutex);
पूर्ण

/**
 * jbd2_journal_त्रुटि_सं() - वापसs the journal's error state.
 * @journal: journal to examine.
 *
 * This is the त्रुटि_सं number set with jbd2_journal_पात(), the last
 * समय the journal was mounted - अगर the journal was stopped
 * without calling पात this will be 0.
 *
 * If the journal has been पातed on this mount समय -EROFS will
 * be वापसed.
 */
पूर्णांक jbd2_journal_त्रुटि_सं(journal_t *journal)
अणु
	पूर्णांक err;

	पढ़ो_lock(&journal->j_state_lock);
	अगर (journal->j_flags & JBD2_ABORT)
		err = -EROFS;
	अन्यथा
		err = journal->j_त्रुटि_सं;
	पढ़ो_unlock(&journal->j_state_lock);
	वापस err;
पूर्ण

/**
 * jbd2_journal_clear_err() - clears the journal's error state
 * @journal: journal to act on.
 *
 * An error must be cleared or acked to take a FS out of पढ़ोonly
 * mode.
 */
पूर्णांक jbd2_journal_clear_err(journal_t *journal)
अणु
	पूर्णांक err = 0;

	ग_लिखो_lock(&journal->j_state_lock);
	अगर (journal->j_flags & JBD2_ABORT)
		err = -EROFS;
	अन्यथा
		journal->j_त्रुटि_सं = 0;
	ग_लिखो_unlock(&journal->j_state_lock);
	वापस err;
पूर्ण

/**
 * jbd2_journal_ack_err() - Ack journal err.
 * @journal: journal to act on.
 *
 * An error must be cleared or acked to take a FS out of पढ़ोonly
 * mode.
 */
व्योम jbd2_journal_ack_err(journal_t *journal)
अणु
	ग_लिखो_lock(&journal->j_state_lock);
	अगर (journal->j_त्रुटि_सं)
		journal->j_flags |= JBD2_ACK_ERR;
	ग_लिखो_unlock(&journal->j_state_lock);
पूर्ण

पूर्णांक jbd2_journal_blocks_per_page(काष्ठा inode *inode)
अणु
	वापस 1 << (PAGE_SHIFT - inode->i_sb->s_blocksize_bits);
पूर्ण

/*
 * helper functions to deal with 32 or 64bit block numbers.
 */
माप_प्रकार journal_tag_bytes(journal_t *journal)
अणु
	माप_प्रकार sz;

	अगर (jbd2_has_feature_csum3(journal))
		वापस माप(journal_block_tag3_t);

	sz = माप(journal_block_tag_t);

	अगर (jbd2_has_feature_csum2(journal))
		sz += माप(__u16);

	अगर (jbd2_has_feature_64bit(journal))
		वापस sz;
	अन्यथा
		वापस sz - माप(__u32);
पूर्ण

/*
 * JBD memory management
 *
 * These functions are used to allocate block-sized chunks of memory
 * used क्रम making copies of buffer_head data.  Very often it will be
 * page-sized chunks of data, but someबार it will be in
 * sub-page-size chunks.  (For example, 16k pages on Power प्रणालीs
 * with a 4k block file प्रणाली.)  For blocks smaller than a page, we
 * use a SLAB allocator.  There are slab caches क्रम each block size,
 * which are allocated at mount समय, अगर necessary, and we only मुक्त
 * (all of) the slab caches when/अगर the jbd2 module is unloaded.  For
 * this reason we करोn't need to a mutex to protect access to
 * jbd2_slab[] allocating or releasing memory; only in
 * jbd2_journal_create_slab().
 */
#घोषणा JBD2_MAX_SLABS 8
अटल काष्ठा kmem_cache *jbd2_slab[JBD2_MAX_SLABS];

अटल स्थिर अक्षर *jbd2_slab_names[JBD2_MAX_SLABS] = अणु
	"jbd2_1k", "jbd2_2k", "jbd2_4k", "jbd2_8k",
	"jbd2_16k", "jbd2_32k", "jbd2_64k", "jbd2_128k"
पूर्ण;


अटल व्योम jbd2_journal_destroy_sद_असल(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < JBD2_MAX_SLABS; i++) अणु
		kmem_cache_destroy(jbd2_slab[i]);
		jbd2_slab[i] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक jbd2_journal_create_slab(माप_प्रकार size)
अणु
	अटल DEFINE_MUTEX(jbd2_slab_create_mutex);
	पूर्णांक i = order_base_2(size) - 10;
	माप_प्रकार slab_size;

	अगर (size == PAGE_SIZE)
		वापस 0;

	अगर (i >= JBD2_MAX_SLABS)
		वापस -EINVAL;

	अगर (unlikely(i < 0))
		i = 0;
	mutex_lock(&jbd2_slab_create_mutex);
	अगर (jbd2_slab[i]) अणु
		mutex_unlock(&jbd2_slab_create_mutex);
		वापस 0;	/* Alपढ़ोy created */
	पूर्ण

	slab_size = 1 << (i+10);
	jbd2_slab[i] = kmem_cache_create(jbd2_slab_names[i], slab_size,
					 slab_size, 0, शून्य);
	mutex_unlock(&jbd2_slab_create_mutex);
	अगर (!jbd2_slab[i]) अणु
		prपूर्णांकk(KERN_EMERG "JBD2: no memory for jbd2_slab cache\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा kmem_cache *get_slab(माप_प्रकार size)
अणु
	पूर्णांक i = order_base_2(size) - 10;

	BUG_ON(i >= JBD2_MAX_SLABS);
	अगर (unlikely(i < 0))
		i = 0;
	BUG_ON(jbd2_slab[i] == शून्य);
	वापस jbd2_slab[i];
पूर्ण

व्योम *jbd2_alloc(माप_प्रकार size, gfp_t flags)
अणु
	व्योम *ptr;

	BUG_ON(size & (size-1)); /* Must be a घातer of 2 */

	अगर (size < PAGE_SIZE)
		ptr = kmem_cache_alloc(get_slab(size), flags);
	अन्यथा
		ptr = (व्योम *)__get_मुक्त_pages(flags, get_order(size));

	/* Check alignment; SLUB has gotten this wrong in the past,
	 * and this can lead to user data corruption! */
	BUG_ON(((अचिन्हित दीर्घ) ptr) & (size-1));

	वापस ptr;
पूर्ण

व्योम jbd2_मुक्त(व्योम *ptr, माप_प्रकार size)
अणु
	अगर (size < PAGE_SIZE)
		kmem_cache_मुक्त(get_slab(size), ptr);
	अन्यथा
		मुक्त_pages((अचिन्हित दीर्घ)ptr, get_order(size));
पूर्ण;

/*
 * Journal_head storage management
 */
अटल काष्ठा kmem_cache *jbd2_journal_head_cache;
#अगर_घोषित CONFIG_JBD2_DEBUG
अटल atomic_t nr_journal_heads = ATOMIC_INIT(0);
#पूर्ण_अगर

अटल पूर्णांक __init jbd2_journal_init_journal_head_cache(व्योम)
अणु
	J_ASSERT(!jbd2_journal_head_cache);
	jbd2_journal_head_cache = kmem_cache_create("jbd2_journal_head",
				माप(काष्ठा journal_head),
				0,		/* offset */
				SLAB_TEMPORARY | SLAB_TYPESAFE_BY_RCU,
				शून्य);		/* ctor */
	अगर (!jbd2_journal_head_cache) अणु
		prपूर्णांकk(KERN_EMERG "JBD2: no memory for journal_head cache\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम jbd2_journal_destroy_journal_head_cache(व्योम)
अणु
	kmem_cache_destroy(jbd2_journal_head_cache);
	jbd2_journal_head_cache = शून्य;
पूर्ण

/*
 * journal_head splicing and dicing
 */
अटल काष्ठा journal_head *journal_alloc_journal_head(व्योम)
अणु
	काष्ठा journal_head *ret;

#अगर_घोषित CONFIG_JBD2_DEBUG
	atomic_inc(&nr_journal_heads);
#पूर्ण_अगर
	ret = kmem_cache_zalloc(jbd2_journal_head_cache, GFP_NOFS);
	अगर (!ret) अणु
		jbd_debug(1, "out of memory for journal_head\n");
		pr_notice_ratelimited("ENOMEM in %s, retrying.\n", __func__);
		ret = kmem_cache_zalloc(jbd2_journal_head_cache,
				GFP_NOFS | __GFP_NOFAIL);
	पूर्ण
	अगर (ret)
		spin_lock_init(&ret->b_state_lock);
	वापस ret;
पूर्ण

अटल व्योम journal_मुक्त_journal_head(काष्ठा journal_head *jh)
अणु
#अगर_घोषित CONFIG_JBD2_DEBUG
	atomic_dec(&nr_journal_heads);
	स_रखो(jh, JBD2_POISON_FREE, माप(*jh));
#पूर्ण_अगर
	kmem_cache_मुक्त(jbd2_journal_head_cache, jh);
पूर्ण

/*
 * A journal_head is attached to a buffer_head whenever JBD has an
 * पूर्णांकerest in the buffer.
 *
 * Whenever a buffer has an attached journal_head, its ->b_state:BH_JBD bit
 * is set.  This bit is tested in core kernel code where we need to take
 * JBD-specअगरic actions.  Testing the zeroness of ->b_निजी is not reliable
 * there.
 *
 * When a buffer has its BH_JBD bit set, its ->b_count is elevated by one.
 *
 * When a buffer has its BH_JBD bit set it is immune from being released by
 * core kernel code, मुख्यly via ->b_count.
 *
 * A journal_head is detached from its buffer_head when the journal_head's
 * b_jcount reaches zero. Running transaction (b_transaction) and checkpoपूर्णांक
 * transaction (b_cp_transaction) hold their references to b_jcount.
 *
 * Various places in the kernel want to attach a journal_head to a buffer_head
 * _beक्रमe_ attaching the journal_head to a transaction.  To protect the
 * journal_head in this situation, jbd2_journal_add_journal_head elevates the
 * journal_head's b_jcount refcount by one.  The caller must call
 * jbd2_journal_put_journal_head() to unकरो this.
 *
 * So the typical usage would be:
 *
 *	(Attach a journal_head अगर needed.  Increments b_jcount)
 *	काष्ठा journal_head *jh = jbd2_journal_add_journal_head(bh);
 *	...
 *      (Get another reference क्रम transaction)
 *	jbd2_journal_grab_journal_head(bh);
 *	jh->b_transaction = xxx;
 *	(Put original reference)
 *	jbd2_journal_put_journal_head(jh);
 */

/*
 * Give a buffer_head a journal_head.
 *
 * May sleep.
 */
काष्ठा journal_head *jbd2_journal_add_journal_head(काष्ठा buffer_head *bh)
अणु
	काष्ठा journal_head *jh;
	काष्ठा journal_head *new_jh = शून्य;

repeat:
	अगर (!buffer_jbd(bh))
		new_jh = journal_alloc_journal_head();

	jbd_lock_bh_journal_head(bh);
	अगर (buffer_jbd(bh)) अणु
		jh = bh2jh(bh);
	पूर्ण अन्यथा अणु
		J_ASSERT_BH(bh,
			(atomic_पढ़ो(&bh->b_count) > 0) ||
			(bh->b_page && bh->b_page->mapping));

		अगर (!new_jh) अणु
			jbd_unlock_bh_journal_head(bh);
			जाओ repeat;
		पूर्ण

		jh = new_jh;
		new_jh = शून्य;		/* We consumed it */
		set_buffer_jbd(bh);
		bh->b_निजी = jh;
		jh->b_bh = bh;
		get_bh(bh);
		BUFFER_TRACE(bh, "added journal_head");
	पूर्ण
	jh->b_jcount++;
	jbd_unlock_bh_journal_head(bh);
	अगर (new_jh)
		journal_मुक्त_journal_head(new_jh);
	वापस bh->b_निजी;
पूर्ण

/*
 * Grab a ref against this buffer_head's journal_head.  If it ended up not
 * having a journal_head, वापस शून्य
 */
काष्ठा journal_head *jbd2_journal_grab_journal_head(काष्ठा buffer_head *bh)
अणु
	काष्ठा journal_head *jh = शून्य;

	jbd_lock_bh_journal_head(bh);
	अगर (buffer_jbd(bh)) अणु
		jh = bh2jh(bh);
		jh->b_jcount++;
	पूर्ण
	jbd_unlock_bh_journal_head(bh);
	वापस jh;
पूर्ण

अटल व्योम __journal_हटाओ_journal_head(काष्ठा buffer_head *bh)
अणु
	काष्ठा journal_head *jh = bh2jh(bh);

	J_ASSERT_JH(jh, jh->b_transaction == शून्य);
	J_ASSERT_JH(jh, jh->b_next_transaction == शून्य);
	J_ASSERT_JH(jh, jh->b_cp_transaction == शून्य);
	J_ASSERT_JH(jh, jh->b_jlist == BJ_None);
	J_ASSERT_BH(bh, buffer_jbd(bh));
	J_ASSERT_BH(bh, jh2bh(jh) == bh);
	BUFFER_TRACE(bh, "remove journal_head");

	/* Unlink beक्रमe dropping the lock */
	bh->b_निजी = शून्य;
	jh->b_bh = शून्य;	/* debug, really */
	clear_buffer_jbd(bh);
पूर्ण

अटल व्योम journal_release_journal_head(काष्ठा journal_head *jh, माप_प्रकार b_size)
अणु
	अगर (jh->b_frozen_data) अणु
		prपूर्णांकk(KERN_WARNING "%s: freeing b_frozen_data\n", __func__);
		jbd2_मुक्त(jh->b_frozen_data, b_size);
	पूर्ण
	अगर (jh->b_committed_data) अणु
		prपूर्णांकk(KERN_WARNING "%s: freeing b_committed_data\n", __func__);
		jbd2_मुक्त(jh->b_committed_data, b_size);
	पूर्ण
	journal_मुक्त_journal_head(jh);
पूर्ण

/*
 * Drop a reference on the passed journal_head.  If it fell to zero then
 * release the journal_head from the buffer_head.
 */
व्योम jbd2_journal_put_journal_head(काष्ठा journal_head *jh)
अणु
	काष्ठा buffer_head *bh = jh2bh(jh);

	jbd_lock_bh_journal_head(bh);
	J_ASSERT_JH(jh, jh->b_jcount > 0);
	--jh->b_jcount;
	अगर (!jh->b_jcount) अणु
		__journal_हटाओ_journal_head(bh);
		jbd_unlock_bh_journal_head(bh);
		journal_release_journal_head(jh, bh->b_size);
		__brअन्यथा(bh);
	पूर्ण अन्यथा अणु
		jbd_unlock_bh_journal_head(bh);
	पूर्ण
पूर्ण

/*
 * Initialize jbd inode head
 */
व्योम jbd2_journal_init_jbd_inode(काष्ठा jbd2_inode *jinode, काष्ठा inode *inode)
अणु
	jinode->i_transaction = शून्य;
	jinode->i_next_transaction = शून्य;
	jinode->i_vfs_inode = inode;
	jinode->i_flags = 0;
	jinode->i_dirty_start = 0;
	jinode->i_dirty_end = 0;
	INIT_LIST_HEAD(&jinode->i_list);
पूर्ण

/*
 * Function to be called beक्रमe we start removing inode from memory (i.e.,
 * clear_inode() is a fine place to be called from). It हटाओs inode from
 * transaction's lists.
 */
व्योम jbd2_journal_release_jbd_inode(journal_t *journal,
				    काष्ठा jbd2_inode *jinode)
अणु
	अगर (!journal)
		वापस;
restart:
	spin_lock(&journal->j_list_lock);
	/* Is commit writing out inode - we have to रुको */
	अगर (jinode->i_flags & JI_COMMIT_RUNNING) अणु
		रुको_queue_head_t *wq;
		DEFINE_WAIT_BIT(रुको, &jinode->i_flags, __JI_COMMIT_RUNNING);
		wq = bit_रुकोqueue(&jinode->i_flags, __JI_COMMIT_RUNNING);
		prepare_to_रुको(wq, &रुको.wq_entry, TASK_UNINTERRUPTIBLE);
		spin_unlock(&journal->j_list_lock);
		schedule();
		finish_रुको(wq, &रुको.wq_entry);
		जाओ restart;
	पूर्ण

	अगर (jinode->i_transaction) अणु
		list_del(&jinode->i_list);
		jinode->i_transaction = शून्य;
	पूर्ण
	spin_unlock(&journal->j_list_lock);
पूर्ण


#अगर_घोषित CONFIG_PROC_FS

#घोषणा JBD2_STATS_PROC_NAME "fs/jbd2"

अटल व्योम __init jbd2_create_jbd_stats_proc_entry(व्योम)
अणु
	proc_jbd2_stats = proc_सूची_गढ़ो(JBD2_STATS_PROC_NAME, शून्य);
पूर्ण

अटल व्योम __निकास jbd2_हटाओ_jbd_stats_proc_entry(व्योम)
अणु
	अगर (proc_jbd2_stats)
		हटाओ_proc_entry(JBD2_STATS_PROC_NAME, शून्य);
पूर्ण

#अन्यथा

#घोषणा jbd2_create_jbd_stats_proc_entry() करो अणुपूर्ण जबतक (0)
#घोषणा jbd2_हटाओ_jbd_stats_proc_entry() करो अणुपूर्ण जबतक (0)

#पूर्ण_अगर

काष्ठा kmem_cache *jbd2_handle_cache, *jbd2_inode_cache;

अटल पूर्णांक __init jbd2_journal_init_inode_cache(व्योम)
अणु
	J_ASSERT(!jbd2_inode_cache);
	jbd2_inode_cache = KMEM_CACHE(jbd2_inode, 0);
	अगर (!jbd2_inode_cache) अणु
		pr_emerg("JBD2: failed to create inode cache\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init jbd2_journal_init_handle_cache(व्योम)
अणु
	J_ASSERT(!jbd2_handle_cache);
	jbd2_handle_cache = KMEM_CACHE(jbd2_journal_handle, SLAB_TEMPORARY);
	अगर (!jbd2_handle_cache) अणु
		prपूर्णांकk(KERN_EMERG "JBD2: failed to create handle cache\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम jbd2_journal_destroy_inode_cache(व्योम)
अणु
	kmem_cache_destroy(jbd2_inode_cache);
	jbd2_inode_cache = शून्य;
पूर्ण

अटल व्योम jbd2_journal_destroy_handle_cache(व्योम)
अणु
	kmem_cache_destroy(jbd2_handle_cache);
	jbd2_handle_cache = शून्य;
पूर्ण

/*
 * Module startup and shutकरोwn
 */

अटल पूर्णांक __init journal_init_caches(व्योम)
अणु
	पूर्णांक ret;

	ret = jbd2_journal_init_revoke_record_cache();
	अगर (ret == 0)
		ret = jbd2_journal_init_revoke_table_cache();
	अगर (ret == 0)
		ret = jbd2_journal_init_journal_head_cache();
	अगर (ret == 0)
		ret = jbd2_journal_init_handle_cache();
	अगर (ret == 0)
		ret = jbd2_journal_init_inode_cache();
	अगर (ret == 0)
		ret = jbd2_journal_init_transaction_cache();
	वापस ret;
पूर्ण

अटल व्योम jbd2_journal_destroy_caches(व्योम)
अणु
	jbd2_journal_destroy_revoke_record_cache();
	jbd2_journal_destroy_revoke_table_cache();
	jbd2_journal_destroy_journal_head_cache();
	jbd2_journal_destroy_handle_cache();
	jbd2_journal_destroy_inode_cache();
	jbd2_journal_destroy_transaction_cache();
	jbd2_journal_destroy_sद_असल();
पूर्ण

अटल पूर्णांक __init journal_init(व्योम)
अणु
	पूर्णांक ret;

	BUILD_BUG_ON(माप(काष्ठा journal_superblock_s) != 1024);

	ret = journal_init_caches();
	अगर (ret == 0) अणु
		jbd2_create_jbd_stats_proc_entry();
	पूर्ण अन्यथा अणु
		jbd2_journal_destroy_caches();
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम __निकास journal_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_JBD2_DEBUG
	पूर्णांक n = atomic_पढ़ो(&nr_journal_heads);
	अगर (n)
		prपूर्णांकk(KERN_ERR "JBD2: leaked %d journal_heads!\n", n);
#पूर्ण_अगर
	jbd2_हटाओ_jbd_stats_proc_entry();
	jbd2_journal_destroy_caches();
पूर्ण

MODULE_LICENSE("GPL");
module_init(journal_init);
module_निकास(journal_निकास);

