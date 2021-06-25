<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * linux/fs/jbd2/commit.c
 *
 * Written by Stephen C. Tweedie <sct@redhat.com>, 1998
 *
 * Copyright 1998 Red Hat corp --- All Rights Reserved
 *
 * Journal commit routines क्रम the generic fileप्रणाली journaling code;
 * part of the ext2fs journaling प्रणाली.
 */

#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/jbd2.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/crc32.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/bitops.h>
#समावेश <trace/events/jbd2.h>

/*
 * IO end handler क्रम temporary buffer_heads handling ग_लिखोs to the journal.
 */
अटल व्योम journal_end_buffer_io_sync(काष्ठा buffer_head *bh, पूर्णांक uptodate)
अणु
	काष्ठा buffer_head *orig_bh = bh->b_निजी;

	BUFFER_TRACE(bh, "");
	अगर (uptodate)
		set_buffer_uptodate(bh);
	अन्यथा
		clear_buffer_uptodate(bh);
	अगर (orig_bh) अणु
		clear_bit_unlock(BH_Shaकरोw, &orig_bh->b_state);
		smp_mb__after_atomic();
		wake_up_bit(&orig_bh->b_state, BH_Shaकरोw);
	पूर्ण
	unlock_buffer(bh);
पूर्ण

/*
 * When an ext4 file is truncated, it is possible that some pages are not
 * successfully मुक्तd, because they are attached to a committing transaction.
 * After the transaction commits, these pages are left on the LRU, with no
 * ->mapping, and with attached buffers.  These pages are trivially reclaimable
 * by the VM, but their apparent असलence upsets the VM accounting, and it makes
 * the numbers in /proc/meminfo look odd.
 *
 * So here, we have a buffer which has just come off the क्रमget list.  Look to
 * see अगर we can strip all buffers from the backing page.
 *
 * Called under lock_journal(), and possibly under journal_datalist_lock.  The
 * caller provided us with a ref against the buffer, and we drop that here.
 */
अटल व्योम release_buffer_page(काष्ठा buffer_head *bh)
अणु
	काष्ठा page *page;

	अगर (buffer_dirty(bh))
		जाओ nope;
	अगर (atomic_पढ़ो(&bh->b_count) != 1)
		जाओ nope;
	page = bh->b_page;
	अगर (!page)
		जाओ nope;
	अगर (page->mapping)
		जाओ nope;

	/* OK, it's a truncated page */
	अगर (!trylock_page(page))
		जाओ nope;

	get_page(page);
	__brअन्यथा(bh);
	try_to_मुक्त_buffers(page);
	unlock_page(page);
	put_page(page);
	वापस;

nope:
	__brअन्यथा(bh);
पूर्ण

अटल व्योम jbd2_commit_block_csum_set(journal_t *j, काष्ठा buffer_head *bh)
अणु
	काष्ठा commit_header *h;
	__u32 csum;

	अगर (!jbd2_journal_has_csum_v2or3(j))
		वापस;

	h = (काष्ठा commit_header *)(bh->b_data);
	h->h_chksum_type = 0;
	h->h_chksum_size = 0;
	h->h_chksum[0] = 0;
	csum = jbd2_chksum(j, j->j_csum_seed, bh->b_data, j->j_blocksize);
	h->h_chksum[0] = cpu_to_be32(csum);
पूर्ण

/*
 * Done it all: now submit the commit record.  We should have
 * cleaned up our previous buffers by now, so अगर we are in पात
 * mode we can now just skip the rest of the journal ग_लिखो
 * entirely.
 *
 * Returns 1 अगर the journal needs to be पातed or 0 on success
 */
अटल पूर्णांक journal_submit_commit_record(journal_t *journal,
					transaction_t *commit_transaction,
					काष्ठा buffer_head **cbh,
					__u32 crc32_sum)
अणु
	काष्ठा commit_header *पंचांगp;
	काष्ठा buffer_head *bh;
	पूर्णांक ret;
	काष्ठा बारpec64 now;

	*cbh = शून्य;

	अगर (is_journal_पातed(journal))
		वापस 0;

	bh = jbd2_journal_get_descriptor_buffer(commit_transaction,
						JBD2_COMMIT_BLOCK);
	अगर (!bh)
		वापस 1;

	पंचांगp = (काष्ठा commit_header *)bh->b_data;
	kसमय_get_coarse_real_ts64(&now);
	पंचांगp->h_commit_sec = cpu_to_be64(now.tv_sec);
	पंचांगp->h_commit_nsec = cpu_to_be32(now.tv_nsec);

	अगर (jbd2_has_feature_checksum(journal)) अणु
		पंचांगp->h_chksum_type 	= JBD2_CRC32_CHKSUM;
		पंचांगp->h_chksum_size 	= JBD2_CRC32_CHKSUM_SIZE;
		पंचांगp->h_chksum[0] 	= cpu_to_be32(crc32_sum);
	पूर्ण
	jbd2_commit_block_csum_set(journal, bh);

	BUFFER_TRACE(bh, "submit commit block");
	lock_buffer(bh);
	clear_buffer_dirty(bh);
	set_buffer_uptodate(bh);
	bh->b_end_io = journal_end_buffer_io_sync;

	अगर (journal->j_flags & JBD2_BARRIER &&
	    !jbd2_has_feature_async_commit(journal))
		ret = submit_bh(REQ_OP_WRITE,
			REQ_SYNC | REQ_PREFLUSH | REQ_FUA, bh);
	अन्यथा
		ret = submit_bh(REQ_OP_WRITE, REQ_SYNC, bh);

	*cbh = bh;
	वापस ret;
पूर्ण

/*
 * This function aदीर्घ with journal_submit_commit_record
 * allows to ग_लिखो the commit record asynchronously.
 */
अटल पूर्णांक journal_रुको_on_commit_record(journal_t *journal,
					 काष्ठा buffer_head *bh)
अणु
	पूर्णांक ret = 0;

	clear_buffer_dirty(bh);
	रुको_on_buffer(bh);

	अगर (unlikely(!buffer_uptodate(bh)))
		ret = -EIO;
	put_bh(bh);            /* One क्रम getblk() */

	वापस ret;
पूर्ण

/*
 * ग_लिखो the filemap data using ग_लिखोpage() address_space_operations.
 * We करोn't do block allocation here even for delalloc. We don't
 * use ग_लिखोpages() because with delayed allocation we may be करोing
 * block allocation in ग_लिखोpages().
 */
पूर्णांक jbd2_journal_submit_inode_data_buffers(काष्ठा jbd2_inode *jinode)
अणु
	काष्ठा address_space *mapping = jinode->i_vfs_inode->i_mapping;
	काष्ठा ग_लिखोback_control wbc = अणु
		.sync_mode =  WB_SYNC_ALL,
		.nr_to_ग_लिखो = mapping->nrpages * 2,
		.range_start = jinode->i_dirty_start,
		.range_end = jinode->i_dirty_end,
	पूर्ण;

	/*
	 * submit the inode data buffers. We use ग_लिखोpage
	 * instead of ग_लिखोpages. Because ग_लिखोpages can करो
	 * block allocation with delalloc. We need to ग_लिखो
	 * only allocated blocks here.
	 */
	वापस generic_ग_लिखोpages(mapping, &wbc);
पूर्ण

/* Send all the data buffers related to an inode */
पूर्णांक jbd2_submit_inode_data(काष्ठा jbd2_inode *jinode)
अणु

	अगर (!jinode || !(jinode->i_flags & JI_WRITE_DATA))
		वापस 0;

	trace_jbd2_submit_inode_data(jinode->i_vfs_inode);
	वापस jbd2_journal_submit_inode_data_buffers(jinode);

पूर्ण
EXPORT_SYMBOL(jbd2_submit_inode_data);

पूर्णांक jbd2_रुको_inode_data(journal_t *journal, काष्ठा jbd2_inode *jinode)
अणु
	अगर (!jinode || !(jinode->i_flags & JI_WAIT_DATA) ||
		!jinode->i_vfs_inode || !jinode->i_vfs_inode->i_mapping)
		वापस 0;
	वापस filemap_fdataरुको_range_keep_errors(
		jinode->i_vfs_inode->i_mapping, jinode->i_dirty_start,
		jinode->i_dirty_end);
पूर्ण
EXPORT_SYMBOL(jbd2_रुको_inode_data);

/*
 * Submit all the data buffers of inode associated with the transaction to
 * disk.
 *
 * We are in a committing transaction. Thereक्रमe no new inode can be added to
 * our inode list. We use JI_COMMIT_RUNNING flag to protect inode we currently
 * operate on from being released जबतक we ग_लिखो out pages.
 */
अटल पूर्णांक journal_submit_data_buffers(journal_t *journal,
		transaction_t *commit_transaction)
अणु
	काष्ठा jbd2_inode *jinode;
	पूर्णांक err, ret = 0;

	spin_lock(&journal->j_list_lock);
	list_क्रम_each_entry(jinode, &commit_transaction->t_inode_list, i_list) अणु
		अगर (!(jinode->i_flags & JI_WRITE_DATA))
			जारी;
		jinode->i_flags |= JI_COMMIT_RUNNING;
		spin_unlock(&journal->j_list_lock);
		/* submit the inode data buffers. */
		trace_jbd2_submit_inode_data(jinode->i_vfs_inode);
		अगर (journal->j_submit_inode_data_buffers) अणु
			err = journal->j_submit_inode_data_buffers(jinode);
			अगर (!ret)
				ret = err;
		पूर्ण
		spin_lock(&journal->j_list_lock);
		J_ASSERT(jinode->i_transaction == commit_transaction);
		jinode->i_flags &= ~JI_COMMIT_RUNNING;
		smp_mb();
		wake_up_bit(&jinode->i_flags, __JI_COMMIT_RUNNING);
	पूर्ण
	spin_unlock(&journal->j_list_lock);
	वापस ret;
पूर्ण

पूर्णांक jbd2_journal_finish_inode_data_buffers(काष्ठा jbd2_inode *jinode)
अणु
	काष्ठा address_space *mapping = jinode->i_vfs_inode->i_mapping;

	वापस filemap_fdataरुको_range_keep_errors(mapping,
						   jinode->i_dirty_start,
						   jinode->i_dirty_end);
पूर्ण

/*
 * Wait क्रम data submitted क्रम ग_लिखोout, refile inodes to proper
 * transaction अगर needed.
 *
 */
अटल पूर्णांक journal_finish_inode_data_buffers(journal_t *journal,
		transaction_t *commit_transaction)
अणु
	काष्ठा jbd2_inode *jinode, *next_i;
	पूर्णांक err, ret = 0;

	/* For locking, see the comment in journal_submit_data_buffers() */
	spin_lock(&journal->j_list_lock);
	list_क्रम_each_entry(jinode, &commit_transaction->t_inode_list, i_list) अणु
		अगर (!(jinode->i_flags & JI_WAIT_DATA))
			जारी;
		jinode->i_flags |= JI_COMMIT_RUNNING;
		spin_unlock(&journal->j_list_lock);
		/* रुको क्रम the inode data buffers ग_लिखोout. */
		अगर (journal->j_finish_inode_data_buffers) अणु
			err = journal->j_finish_inode_data_buffers(jinode);
			अगर (!ret)
				ret = err;
		पूर्ण
		spin_lock(&journal->j_list_lock);
		jinode->i_flags &= ~JI_COMMIT_RUNNING;
		smp_mb();
		wake_up_bit(&jinode->i_flags, __JI_COMMIT_RUNNING);
	पूर्ण

	/* Now refile inode to proper lists */
	list_क्रम_each_entry_safe(jinode, next_i,
				 &commit_transaction->t_inode_list, i_list) अणु
		list_del(&jinode->i_list);
		अगर (jinode->i_next_transaction) अणु
			jinode->i_transaction = jinode->i_next_transaction;
			jinode->i_next_transaction = शून्य;
			list_add(&jinode->i_list,
				&jinode->i_transaction->t_inode_list);
		पूर्ण अन्यथा अणु
			jinode->i_transaction = शून्य;
			jinode->i_dirty_start = 0;
			jinode->i_dirty_end = 0;
		पूर्ण
	पूर्ण
	spin_unlock(&journal->j_list_lock);

	वापस ret;
पूर्ण

अटल __u32 jbd2_checksum_data(__u32 crc32_sum, काष्ठा buffer_head *bh)
अणु
	काष्ठा page *page = bh->b_page;
	अक्षर *addr;
	__u32 checksum;

	addr = kmap_atomic(page);
	checksum = crc32_be(crc32_sum,
		(व्योम *)(addr + offset_in_page(bh->b_data)), bh->b_size);
	kunmap_atomic(addr);

	वापस checksum;
पूर्ण

अटल व्योम ग_लिखो_tag_block(journal_t *j, journal_block_tag_t *tag,
				   अचिन्हित दीर्घ दीर्घ block)
अणु
	tag->t_blocknr = cpu_to_be32(block & (u32)~0);
	अगर (jbd2_has_feature_64bit(j))
		tag->t_blocknr_high = cpu_to_be32((block >> 31) >> 1);
पूर्ण

अटल व्योम jbd2_block_tag_csum_set(journal_t *j, journal_block_tag_t *tag,
				    काष्ठा buffer_head *bh, __u32 sequence)
अणु
	journal_block_tag3_t *tag3 = (journal_block_tag3_t *)tag;
	काष्ठा page *page = bh->b_page;
	__u8 *addr;
	__u32 csum32;
	__be32 seq;

	अगर (!jbd2_journal_has_csum_v2or3(j))
		वापस;

	seq = cpu_to_be32(sequence);
	addr = kmap_atomic(page);
	csum32 = jbd2_chksum(j, j->j_csum_seed, (__u8 *)&seq, माप(seq));
	csum32 = jbd2_chksum(j, csum32, addr + offset_in_page(bh->b_data),
			     bh->b_size);
	kunmap_atomic(addr);

	अगर (jbd2_has_feature_csum3(j))
		tag3->t_checksum = cpu_to_be32(csum32);
	अन्यथा
		tag->t_checksum = cpu_to_be16(csum32);
पूर्ण
/*
 * jbd2_journal_commit_transaction
 *
 * The primary function क्रम committing a transaction to the log.  This
 * function is called by the journal thपढ़ो to begin a complete commit.
 */
व्योम jbd2_journal_commit_transaction(journal_t *journal)
अणु
	काष्ठा transaction_stats_s stats;
	transaction_t *commit_transaction;
	काष्ठा journal_head *jh;
	काष्ठा buffer_head *descriptor;
	काष्ठा buffer_head **wbuf = journal->j_wbuf;
	पूर्णांक bufs;
	पूर्णांक flags;
	पूर्णांक err;
	अचिन्हित दीर्घ दीर्घ blocknr;
	kसमय_प्रकार start_समय;
	u64 commit_समय;
	अक्षर *tagp = शून्य;
	journal_block_tag_t *tag = शून्य;
	पूर्णांक space_left = 0;
	पूर्णांक first_tag = 0;
	पूर्णांक tag_flag;
	पूर्णांक i;
	पूर्णांक tag_bytes = journal_tag_bytes(journal);
	काष्ठा buffer_head *cbh = शून्य; /* For transactional checksums */
	__u32 crc32_sum = ~0;
	काष्ठा blk_plug plug;
	/* Tail of the journal */
	अचिन्हित दीर्घ first_block;
	tid_t first_tid;
	पूर्णांक update_tail;
	पूर्णांक csum_size = 0;
	LIST_HEAD(io_bufs);
	LIST_HEAD(log_bufs);

	अगर (jbd2_journal_has_csum_v2or3(journal))
		csum_size = माप(काष्ठा jbd2_journal_block_tail);

	/*
	 * First job: lock करोwn the current transaction and रुको क्रम
	 * all outstanding updates to complete.
	 */

	/* Do we need to erase the effects of a prior jbd2_journal_flush? */
	अगर (journal->j_flags & JBD2_FLUSHED) अणु
		jbd_debug(3, "super block updated\n");
		mutex_lock_io(&journal->j_checkpoपूर्णांक_mutex);
		/*
		 * We hold j_checkpoपूर्णांक_mutex so tail cannot change under us.
		 * We करोn't need any special data guarantees क्रम writing sb
		 * since journal is empty and it is ok क्रम ग_लिखो to be
		 * flushed only with transaction commit.
		 */
		jbd2_journal_update_sb_log_tail(journal,
						journal->j_tail_sequence,
						journal->j_tail,
						REQ_SYNC);
		mutex_unlock(&journal->j_checkpoपूर्णांक_mutex);
	पूर्ण अन्यथा अणु
		jbd_debug(3, "superblock not updated\n");
	पूर्ण

	J_ASSERT(journal->j_running_transaction != शून्य);
	J_ASSERT(journal->j_committing_transaction == शून्य);

	ग_लिखो_lock(&journal->j_state_lock);
	journal->j_flags |= JBD2_FULL_COMMIT_ONGOING;
	जबतक (journal->j_flags & JBD2_FAST_COMMIT_ONGOING) अणु
		DEFINE_WAIT(रुको);

		prepare_to_रुको(&journal->j_fc_रुको, &रुको,
				TASK_UNINTERRUPTIBLE);
		ग_लिखो_unlock(&journal->j_state_lock);
		schedule();
		ग_लिखो_lock(&journal->j_state_lock);
		finish_रुको(&journal->j_fc_रुको, &रुको);
		/*
		 * TODO: by blocking fast commits here, we are increasing
		 * fsync() latency slightly. Strictly speaking, we करोn't need
		 * to block fast commits until the transaction enters T_FLUSH
		 * state. So an optimization is possible where we block new fast
		 * commits here and रुको क्रम existing ones to complete
		 * just beक्रमe we enter T_FLUSH. That way, the existing fast
		 * commits and this full commit can proceed parallely.
		 */
	पूर्ण
	ग_लिखो_unlock(&journal->j_state_lock);

	commit_transaction = journal->j_running_transaction;

	trace_jbd2_start_commit(journal, commit_transaction);
	jbd_debug(1, "JBD2: starting commit of transaction %d\n",
			commit_transaction->t_tid);

	ग_लिखो_lock(&journal->j_state_lock);
	journal->j_fc_off = 0;
	J_ASSERT(commit_transaction->t_state == T_RUNNING);
	commit_transaction->t_state = T_LOCKED;

	trace_jbd2_commit_locking(journal, commit_transaction);
	stats.run.rs_रुको = commit_transaction->t_max_रुको;
	stats.run.rs_request_delay = 0;
	stats.run.rs_locked = jअगरfies;
	अगर (commit_transaction->t_requested)
		stats.run.rs_request_delay =
			jbd2_समय_dअगरf(commit_transaction->t_requested,
				       stats.run.rs_locked);
	stats.run.rs_running = jbd2_समय_dअगरf(commit_transaction->t_start,
					      stats.run.rs_locked);

	spin_lock(&commit_transaction->t_handle_lock);
	जबतक (atomic_पढ़ो(&commit_transaction->t_updates)) अणु
		DEFINE_WAIT(रुको);

		prepare_to_रुको(&journal->j_रुको_updates, &रुको,
					TASK_UNINTERRUPTIBLE);
		अगर (atomic_पढ़ो(&commit_transaction->t_updates)) अणु
			spin_unlock(&commit_transaction->t_handle_lock);
			ग_लिखो_unlock(&journal->j_state_lock);
			schedule();
			ग_लिखो_lock(&journal->j_state_lock);
			spin_lock(&commit_transaction->t_handle_lock);
		पूर्ण
		finish_रुको(&journal->j_रुको_updates, &रुको);
	पूर्ण
	spin_unlock(&commit_transaction->t_handle_lock);
	commit_transaction->t_state = T_SWITCH;
	ग_लिखो_unlock(&journal->j_state_lock);

	J_ASSERT (atomic_पढ़ो(&commit_transaction->t_outstanding_credits) <=
			journal->j_max_transaction_buffers);

	/*
	 * First thing we are allowed to करो is to discard any reमुख्यing
	 * BJ_Reserved buffers.  Note, it is _not_ permissible to assume
	 * that there are no such buffers: अगर a large fileप्रणाली
	 * operation like a truncate needs to split itself over multiple
	 * transactions, then it may try to करो a jbd2_journal_restart() जबतक
	 * there are still BJ_Reserved buffers outstanding.  These must
	 * be released cleanly from the current transaction.
	 *
	 * In this हाल, the fileप्रणाली must still reserve ग_लिखो access
	 * again beक्रमe modअगरying the buffer in the new transaction, but
	 * we करो not require it to remember exactly which old buffers it
	 * has reserved.  This is consistent with the existing behaviour
	 * that multiple jbd2_journal_get_ग_लिखो_access() calls to the same
	 * buffer are perfectly permissible.
	 */
	जबतक (commit_transaction->t_reserved_list) अणु
		jh = commit_transaction->t_reserved_list;
		JBUFFER_TRACE(jh, "reserved, unused: refile");
		/*
		 * A jbd2_journal_get_unकरो_access()+jbd2_journal_release_buffer() may
		 * leave unकरो-committed data.
		 */
		अगर (jh->b_committed_data) अणु
			काष्ठा buffer_head *bh = jh2bh(jh);

			spin_lock(&jh->b_state_lock);
			jbd2_मुक्त(jh->b_committed_data, bh->b_size);
			jh->b_committed_data = शून्य;
			spin_unlock(&jh->b_state_lock);
		पूर्ण
		jbd2_journal_refile_buffer(journal, jh);
	पूर्ण

	/*
	 * Now try to drop any written-back buffers from the journal's
	 * checkpoपूर्णांक lists.  We करो this *beक्रमe* commit because it potentially
	 * मुक्तs some memory
	 */
	spin_lock(&journal->j_list_lock);
	__jbd2_journal_clean_checkpoपूर्णांक_list(journal, false);
	spin_unlock(&journal->j_list_lock);

	jbd_debug(3, "JBD2: commit phase 1\n");

	/*
	 * Clear revoked flag to reflect there is no revoked buffers
	 * in the next transaction which is going to be started.
	 */
	jbd2_clear_buffer_revoked_flags(journal);

	/*
	 * Switch to a new revoke table.
	 */
	jbd2_journal_चयन_revoke_table(journal);

	/*
	 * Reserved credits cannot be claimed anymore, मुक्त them
	 */
	atomic_sub(atomic_पढ़ो(&journal->j_reserved_credits),
		   &commit_transaction->t_outstanding_credits);

	ग_लिखो_lock(&journal->j_state_lock);
	trace_jbd2_commit_flushing(journal, commit_transaction);
	stats.run.rs_flushing = jअगरfies;
	stats.run.rs_locked = jbd2_समय_dअगरf(stats.run.rs_locked,
					     stats.run.rs_flushing);

	commit_transaction->t_state = T_FLUSH;
	journal->j_committing_transaction = commit_transaction;
	journal->j_running_transaction = शून्य;
	start_समय = kसमय_get();
	commit_transaction->t_log_start = journal->j_head;
	wake_up(&journal->j_रुको_transaction_locked);
	ग_लिखो_unlock(&journal->j_state_lock);

	jbd_debug(3, "JBD2: commit phase 2a\n");

	/*
	 * Now start flushing things to disk, in the order they appear
	 * on the transaction lists.  Data blocks go first.
	 */
	err = journal_submit_data_buffers(journal, commit_transaction);
	अगर (err)
		jbd2_journal_पात(journal, err);

	blk_start_plug(&plug);
	jbd2_journal_ग_लिखो_revoke_records(commit_transaction, &log_bufs);

	jbd_debug(3, "JBD2: commit phase 2b\n");

	/*
	 * Way to go: we have now written out all of the data क्रम a
	 * transaction!  Now comes the tricky part: we need to ग_लिखो out
	 * metadata.  Loop over the transaction's entire buffer list:
	 */
	ग_लिखो_lock(&journal->j_state_lock);
	commit_transaction->t_state = T_COMMIT;
	ग_लिखो_unlock(&journal->j_state_lock);

	trace_jbd2_commit_logging(journal, commit_transaction);
	stats.run.rs_logging = jअगरfies;
	stats.run.rs_flushing = jbd2_समय_dअगरf(stats.run.rs_flushing,
					       stats.run.rs_logging);
	stats.run.rs_blocks = commit_transaction->t_nr_buffers;
	stats.run.rs_blocks_logged = 0;

	J_ASSERT(commit_transaction->t_nr_buffers <=
		 atomic_पढ़ो(&commit_transaction->t_outstanding_credits));

	err = 0;
	bufs = 0;
	descriptor = शून्य;
	जबतक (commit_transaction->t_buffers) अणु

		/* Find the next buffer to be journaled... */

		jh = commit_transaction->t_buffers;

		/* If we're in पात mode, we just un-journal the buffer and
		   release it. */

		अगर (is_journal_पातed(journal)) अणु
			clear_buffer_jbddirty(jh2bh(jh));
			JBUFFER_TRACE(jh, "journal is aborting: refile");
			jbd2_buffer_पात_trigger(jh,
						  jh->b_frozen_data ?
						  jh->b_frozen_triggers :
						  jh->b_triggers);
			jbd2_journal_refile_buffer(journal, jh);
			/* If that was the last one, we need to clean up
			 * any descriptor buffers which may have been
			 * alपढ़ोy allocated, even अगर we are now
			 * पातing. */
			अगर (!commit_transaction->t_buffers)
				जाओ start_journal_io;
			जारी;
		पूर्ण

		/* Make sure we have a descriptor block in which to
		   record the metadata buffer. */

		अगर (!descriptor) अणु
			J_ASSERT (bufs == 0);

			jbd_debug(4, "JBD2: get descriptor\n");

			descriptor = jbd2_journal_get_descriptor_buffer(
							commit_transaction,
							JBD2_DESCRIPTOR_BLOCK);
			अगर (!descriptor) अणु
				jbd2_journal_पात(journal, -EIO);
				जारी;
			पूर्ण

			jbd_debug(4, "JBD2: got buffer %llu (%p)\n",
				(अचिन्हित दीर्घ दीर्घ)descriptor->b_blocknr,
				descriptor->b_data);
			tagp = &descriptor->b_data[माप(journal_header_t)];
			space_left = descriptor->b_size -
						माप(journal_header_t);
			first_tag = 1;
			set_buffer_jग_लिखो(descriptor);
			set_buffer_dirty(descriptor);
			wbuf[bufs++] = descriptor;

			/* Record it so that we can रुको क्रम IO
                           completion later */
			BUFFER_TRACE(descriptor, "ph3: file as descriptor");
			jbd2_file_log_bh(&log_bufs, descriptor);
		पूर्ण

		/* Where is the buffer to be written? */

		err = jbd2_journal_next_log_block(journal, &blocknr);
		/* If the block mapping failed, just abanकरोn the buffer
		   and repeat this loop: we'll fall पूर्णांकo the
		   refile-on-पात condition above. */
		अगर (err) अणु
			jbd2_journal_पात(journal, err);
			जारी;
		पूर्ण

		/*
		 * start_this_handle() uses t_outstanding_credits to determine
		 * the मुक्त space in the log.
		 */
		atomic_dec(&commit_transaction->t_outstanding_credits);

		/* Bump b_count to prevent truncate from stumbling over
                   the shaकरोwed buffer!  @@@ This can go अगर we ever get
                   rid of the shaकरोw pairing of buffers. */
		atomic_inc(&jh2bh(jh)->b_count);

		/*
		 * Make a temporary IO buffer with which to ग_लिखो it out
		 * (this will requeue the metadata buffer to BJ_Shaकरोw).
		 */
		set_bit(BH_JWrite, &jh2bh(jh)->b_state);
		JBUFFER_TRACE(jh, "ph3: write metadata");
		flags = jbd2_journal_ग_लिखो_metadata_buffer(commit_transaction,
						jh, &wbuf[bufs], blocknr);
		अगर (flags < 0) अणु
			jbd2_journal_पात(journal, flags);
			जारी;
		पूर्ण
		jbd2_file_log_bh(&io_bufs, wbuf[bufs]);

		/* Record the new block's tag in the current descriptor
                   buffer */

		tag_flag = 0;
		अगर (flags & 1)
			tag_flag |= JBD2_FLAG_ESCAPE;
		अगर (!first_tag)
			tag_flag |= JBD2_FLAG_SAME_UUID;

		tag = (journal_block_tag_t *) tagp;
		ग_लिखो_tag_block(journal, tag, jh2bh(jh)->b_blocknr);
		tag->t_flags = cpu_to_be16(tag_flag);
		jbd2_block_tag_csum_set(journal, tag, wbuf[bufs],
					commit_transaction->t_tid);
		tagp += tag_bytes;
		space_left -= tag_bytes;
		bufs++;

		अगर (first_tag) अणु
			स_नकल (tagp, journal->j_uuid, 16);
			tagp += 16;
			space_left -= 16;
			first_tag = 0;
		पूर्ण

		/* If there's no more to करो, or अगर the descriptor is full,
		   let the IO rip! */

		अगर (bufs == journal->j_wbufsize ||
		    commit_transaction->t_buffers == शून्य ||
		    space_left < tag_bytes + 16 + csum_size) अणु

			jbd_debug(4, "JBD2: Submit %d IOs\n", bufs);

			/* Write an end-of-descriptor marker beक्रमe
                           submitting the IOs.  "tag" still poपूर्णांकs to
                           the last tag we set up. */

			tag->t_flags |= cpu_to_be16(JBD2_FLAG_LAST_TAG);
start_journal_io:
			अगर (descriptor)
				jbd2_descriptor_block_csum_set(journal,
							descriptor);

			क्रम (i = 0; i < bufs; i++) अणु
				काष्ठा buffer_head *bh = wbuf[i];
				/*
				 * Compute checksum.
				 */
				अगर (jbd2_has_feature_checksum(journal)) अणु
					crc32_sum =
					    jbd2_checksum_data(crc32_sum, bh);
				पूर्ण

				lock_buffer(bh);
				clear_buffer_dirty(bh);
				set_buffer_uptodate(bh);
				bh->b_end_io = journal_end_buffer_io_sync;
				submit_bh(REQ_OP_WRITE, REQ_SYNC, bh);
			पूर्ण
			cond_resched();

			/* Force a new descriptor to be generated next
                           समय round the loop. */
			descriptor = शून्य;
			bufs = 0;
		पूर्ण
	पूर्ण

	err = journal_finish_inode_data_buffers(journal, commit_transaction);
	अगर (err) अणु
		prपूर्णांकk(KERN_WARNING
			"JBD2: Detected IO errors while flushing file data "
		       "on %s\n", journal->j_devname);
		अगर (journal->j_flags & JBD2_ABORT_ON_SYNCDATA_ERR)
			jbd2_journal_पात(journal, err);
		err = 0;
	पूर्ण

	/*
	 * Get current oldest transaction in the log beक्रमe we issue flush
	 * to the fileप्रणाली device. After the flush we can be sure that
	 * blocks of all older transactions are checkpoपूर्णांकed to persistent
	 * storage and we will be safe to update journal start in the
	 * superblock with the numbers we get here.
	 */
	update_tail =
		jbd2_journal_get_log_tail(journal, &first_tid, &first_block);

	ग_लिखो_lock(&journal->j_state_lock);
	अगर (update_tail) अणु
		दीर्घ मुक्तd = first_block - journal->j_tail;

		अगर (first_block < journal->j_tail)
			मुक्तd += journal->j_last - journal->j_first;
		/* Update tail only अगर we मुक्त signअगरicant amount of space */
		अगर (मुक्तd < jbd2_journal_get_max_txn_bufs(journal))
			update_tail = 0;
	पूर्ण
	J_ASSERT(commit_transaction->t_state == T_COMMIT);
	commit_transaction->t_state = T_COMMIT_DFLUSH;
	ग_लिखो_unlock(&journal->j_state_lock);

	/* 
	 * If the journal is not located on the file प्रणाली device,
	 * then we must flush the file प्रणाली device beक्रमe we issue
	 * the commit record
	 */
	अगर (commit_transaction->t_need_data_flush &&
	    (journal->j_fs_dev != journal->j_dev) &&
	    (journal->j_flags & JBD2_BARRIER))
		blkdev_issue_flush(journal->j_fs_dev);

	/* Done it all: now ग_लिखो the commit record asynchronously. */
	अगर (jbd2_has_feature_async_commit(journal)) अणु
		err = journal_submit_commit_record(journal, commit_transaction,
						 &cbh, crc32_sum);
		अगर (err)
			jbd2_journal_पात(journal, err);
	पूर्ण

	blk_finish_plug(&plug);

	/* Lo and behold: we have just managed to send a transaction to
           the log.  Beक्रमe we can commit it, रुको क्रम the IO so far to
           complete.  Control buffers being written are on the
           transaction's t_log_list queue, and metadata buffers are on
           the io_bufs list.

	   Wait क्रम the buffers in reverse order.  That way we are
	   less likely to be woken up until all IOs have completed, and
	   so we incur less scheduling load.
	*/

	jbd_debug(3, "JBD2: commit phase 3\n");

	जबतक (!list_empty(&io_bufs)) अणु
		काष्ठा buffer_head *bh = list_entry(io_bufs.prev,
						    काष्ठा buffer_head,
						    b_assoc_buffers);

		रुको_on_buffer(bh);
		cond_resched();

		अगर (unlikely(!buffer_uptodate(bh)))
			err = -EIO;
		jbd2_unfile_log_bh(bh);
		stats.run.rs_blocks_logged++;

		/*
		 * The list contains temporary buffer heads created by
		 * jbd2_journal_ग_लिखो_metadata_buffer().
		 */
		BUFFER_TRACE(bh, "dumping temporary bh");
		__brअन्यथा(bh);
		J_ASSERT_BH(bh, atomic_पढ़ो(&bh->b_count) == 0);
		मुक्त_buffer_head(bh);

		/* We also have to refile the corresponding shaकरोwed buffer */
		jh = commit_transaction->t_shaकरोw_list->b_tprev;
		bh = jh2bh(jh);
		clear_buffer_jग_लिखो(bh);
		J_ASSERT_BH(bh, buffer_jbddirty(bh));
		J_ASSERT_BH(bh, !buffer_shaकरोw(bh));

		/* The metadata is now released क्रम reuse, but we need
                   to remember it against this transaction so that when
                   we finally commit, we can करो any checkpoपूर्णांकing
                   required. */
		JBUFFER_TRACE(jh, "file as BJ_Forget");
		jbd2_journal_file_buffer(jh, commit_transaction, BJ_Forget);
		JBUFFER_TRACE(jh, "brelse shadowed buffer");
		__brअन्यथा(bh);
	पूर्ण

	J_ASSERT (commit_transaction->t_shaकरोw_list == शून्य);

	jbd_debug(3, "JBD2: commit phase 4\n");

	/* Here we रुको क्रम the revoke record and descriptor record buffers */
	जबतक (!list_empty(&log_bufs)) अणु
		काष्ठा buffer_head *bh;

		bh = list_entry(log_bufs.prev, काष्ठा buffer_head, b_assoc_buffers);
		रुको_on_buffer(bh);
		cond_resched();

		अगर (unlikely(!buffer_uptodate(bh)))
			err = -EIO;

		BUFFER_TRACE(bh, "ph5: control buffer writeout done: unfile");
		clear_buffer_jग_लिखो(bh);
		jbd2_unfile_log_bh(bh);
		stats.run.rs_blocks_logged++;
		__brअन्यथा(bh);		/* One क्रम getblk */
		/* AKPM: bक्रमget here */
	पूर्ण

	अगर (err)
		jbd2_journal_पात(journal, err);

	jbd_debug(3, "JBD2: commit phase 5\n");
	ग_लिखो_lock(&journal->j_state_lock);
	J_ASSERT(commit_transaction->t_state == T_COMMIT_DFLUSH);
	commit_transaction->t_state = T_COMMIT_JFLUSH;
	ग_लिखो_unlock(&journal->j_state_lock);

	अगर (!jbd2_has_feature_async_commit(journal)) अणु
		err = journal_submit_commit_record(journal, commit_transaction,
						&cbh, crc32_sum);
		अगर (err)
			jbd2_journal_पात(journal, err);
	पूर्ण
	अगर (cbh)
		err = journal_रुको_on_commit_record(journal, cbh);
	stats.run.rs_blocks_logged++;
	अगर (jbd2_has_feature_async_commit(journal) &&
	    journal->j_flags & JBD2_BARRIER) अणु
		blkdev_issue_flush(journal->j_dev);
	पूर्ण

	अगर (err)
		jbd2_journal_पात(journal, err);

	WARN_ON_ONCE(
		atomic_पढ़ो(&commit_transaction->t_outstanding_credits) < 0);

	/*
	 * Now disk caches क्रम fileप्रणाली device are flushed so we are safe to
	 * erase checkpoपूर्णांकed transactions from the log by updating journal
	 * superblock.
	 */
	अगर (update_tail)
		jbd2_update_log_tail(journal, first_tid, first_block);

	/* End of a transaction!  Finally, we can करो checkpoपूर्णांक
           processing: any buffers committed as a result of this
           transaction can be हटाओd from any checkpoपूर्णांक list it was on
           beक्रमe. */

	jbd_debug(3, "JBD2: commit phase 6\n");

	J_ASSERT(list_empty(&commit_transaction->t_inode_list));
	J_ASSERT(commit_transaction->t_buffers == शून्य);
	J_ASSERT(commit_transaction->t_checkpoपूर्णांक_list == शून्य);
	J_ASSERT(commit_transaction->t_shaकरोw_list == शून्य);

restart_loop:
	/*
	 * As there are other places (journal_unmap_buffer()) adding buffers
	 * to this list we have to be careful and hold the j_list_lock.
	 */
	spin_lock(&journal->j_list_lock);
	जबतक (commit_transaction->t_क्रमget) अणु
		transaction_t *cp_transaction;
		काष्ठा buffer_head *bh;
		पूर्णांक try_to_मुक्त = 0;
		bool drop_ref;

		jh = commit_transaction->t_क्रमget;
		spin_unlock(&journal->j_list_lock);
		bh = jh2bh(jh);
		/*
		 * Get a reference so that bh cannot be मुक्तd beक्रमe we are
		 * करोne with it.
		 */
		get_bh(bh);
		spin_lock(&jh->b_state_lock);
		J_ASSERT_JH(jh,	jh->b_transaction == commit_transaction);

		/*
		 * If there is unकरो-रक्षित committed data against
		 * this buffer, then we can हटाओ it now.  If it is a
		 * buffer needing such protection, the old frozen_data
		 * field now poपूर्णांकs to a committed version of the
		 * buffer, so rotate that field to the new committed
		 * data.
		 *
		 * Otherwise, we can just throw away the frozen data now.
		 *
		 * We also know that the frozen data has alपढ़ोy fired
		 * its triggers अगर they exist, so we can clear that too.
		 */
		अगर (jh->b_committed_data) अणु
			jbd2_मुक्त(jh->b_committed_data, bh->b_size);
			jh->b_committed_data = शून्य;
			अगर (jh->b_frozen_data) अणु
				jh->b_committed_data = jh->b_frozen_data;
				jh->b_frozen_data = शून्य;
				jh->b_frozen_triggers = शून्य;
			पूर्ण
		पूर्ण अन्यथा अगर (jh->b_frozen_data) अणु
			jbd2_मुक्त(jh->b_frozen_data, bh->b_size);
			jh->b_frozen_data = शून्य;
			jh->b_frozen_triggers = शून्य;
		पूर्ण

		spin_lock(&journal->j_list_lock);
		cp_transaction = jh->b_cp_transaction;
		अगर (cp_transaction) अणु
			JBUFFER_TRACE(jh, "remove from old cp transaction");
			cp_transaction->t_chp_stats.cs_dropped++;
			__jbd2_journal_हटाओ_checkpoपूर्णांक(jh);
		पूर्ण

		/* Only re-checkpoपूर्णांक the buffer_head अगर it is marked
		 * dirty.  If the buffer was added to the BJ_Forget list
		 * by jbd2_journal_क्रमget, it may no दीर्घer be dirty and
		 * there's no poपूर्णांक in keeping a checkpoपूर्णांक record क्रम
		 * it. */

		/*
		 * A buffer which has been मुक्तd जबतक still being journaled
		 * by a previous transaction, refile the buffer to BJ_Forget of
		 * the running transaction. If the just committed transaction
		 * contains "add to orphan" operation, we can completely
		 * invalidate the buffer now. We are rather through in that
		 * since the buffer may be still accessible when blocksize <
		 * pagesize and it is attached to the last partial page.
		 */
		अगर (buffer_मुक्तd(bh) && !jh->b_next_transaction) अणु
			काष्ठा address_space *mapping;

			clear_buffer_मुक्तd(bh);
			clear_buffer_jbddirty(bh);

			/*
			 * Block device buffers need to stay mapped all the
			 * समय, so it is enough to clear buffer_jbddirty and
			 * buffer_मुक्तd bits. For the file mapping buffers (i.e.
			 * journalled data) we need to unmap buffer and clear
			 * more bits. We also need to be careful about the check
			 * because the data page mapping can get cleared under
			 * our hands. Note that अगर mapping == शून्य, we करोn't
			 * need to make buffer unmapped because the page is
			 * alपढ़ोy detached from the mapping and buffers cannot
			 * get reused.
			 */
			mapping = READ_ONCE(bh->b_page->mapping);
			अगर (mapping && !sb_is_blkdev_sb(mapping->host->i_sb)) अणु
				clear_buffer_mapped(bh);
				clear_buffer_new(bh);
				clear_buffer_req(bh);
				bh->b_bdev = शून्य;
			पूर्ण
		पूर्ण

		अगर (buffer_jbddirty(bh)) अणु
			JBUFFER_TRACE(jh, "add to new checkpointing trans");
			__jbd2_journal_insert_checkpoपूर्णांक(jh, commit_transaction);
			अगर (is_journal_पातed(journal))
				clear_buffer_jbddirty(bh);
		पूर्ण अन्यथा अणु
			J_ASSERT_BH(bh, !buffer_dirty(bh));
			/*
			 * The buffer on BJ_Forget list and not jbddirty means
			 * it has been मुक्तd by this transaction and hence it
			 * could not have been पुनः_स्मृतिated until this
			 * transaction has committed. *BUT* it could be
			 * पुनः_स्मृतिated once we have written all the data to
			 * disk and beक्रमe we process the buffer on BJ_Forget
			 * list.
			 */
			अगर (!jh->b_next_transaction)
				try_to_मुक्त = 1;
		पूर्ण
		JBUFFER_TRACE(jh, "refile or unfile buffer");
		drop_ref = __jbd2_journal_refile_buffer(jh);
		spin_unlock(&jh->b_state_lock);
		अगर (drop_ref)
			jbd2_journal_put_journal_head(jh);
		अगर (try_to_मुक्त)
			release_buffer_page(bh);	/* Drops bh reference */
		अन्यथा
			__brअन्यथा(bh);
		cond_resched_lock(&journal->j_list_lock);
	पूर्ण
	spin_unlock(&journal->j_list_lock);
	/*
	 * This is a bit sleazy.  We use j_list_lock to protect transition
	 * of a transaction पूर्णांकo T_FINISHED state and calling
	 * __jbd2_journal_drop_transaction(). Otherwise we could race with
	 * other checkpoपूर्णांकing code processing the transaction...
	 */
	ग_लिखो_lock(&journal->j_state_lock);
	spin_lock(&journal->j_list_lock);
	/*
	 * Now recheck अगर some buffers did not get attached to the transaction
	 * जबतक the lock was dropped...
	 */
	अगर (commit_transaction->t_क्रमget) अणु
		spin_unlock(&journal->j_list_lock);
		ग_लिखो_unlock(&journal->j_state_lock);
		जाओ restart_loop;
	पूर्ण

	/* Add the transaction to the checkpoपूर्णांक list
	 * __journal_हटाओ_checkpoपूर्णांक() can not destroy transaction
	 * under us because it is not marked as T_FINISHED yet */
	अगर (journal->j_checkpoपूर्णांक_transactions == शून्य) अणु
		journal->j_checkpoपूर्णांक_transactions = commit_transaction;
		commit_transaction->t_cpnext = commit_transaction;
		commit_transaction->t_cpprev = commit_transaction;
	पूर्ण अन्यथा अणु
		commit_transaction->t_cpnext =
			journal->j_checkpoपूर्णांक_transactions;
		commit_transaction->t_cpprev =
			commit_transaction->t_cpnext->t_cpprev;
		commit_transaction->t_cpnext->t_cpprev =
			commit_transaction;
		commit_transaction->t_cpprev->t_cpnext =
				commit_transaction;
	पूर्ण
	spin_unlock(&journal->j_list_lock);

	/* Done with this transaction! */

	jbd_debug(3, "JBD2: commit phase 7\n");

	J_ASSERT(commit_transaction->t_state == T_COMMIT_JFLUSH);

	commit_transaction->t_start = jअगरfies;
	stats.run.rs_logging = jbd2_समय_dअगरf(stats.run.rs_logging,
					      commit_transaction->t_start);

	/*
	 * File the transaction statistics
	 */
	stats.ts_tid = commit_transaction->t_tid;
	stats.run.rs_handle_count =
		atomic_पढ़ो(&commit_transaction->t_handle_count);
	trace_jbd2_run_stats(journal->j_fs_dev->bd_dev,
			     commit_transaction->t_tid, &stats.run);
	stats.ts_requested = (commit_transaction->t_requested) ? 1 : 0;

	commit_transaction->t_state = T_COMMIT_CALLBACK;
	J_ASSERT(commit_transaction == journal->j_committing_transaction);
	journal->j_commit_sequence = commit_transaction->t_tid;
	journal->j_committing_transaction = शून्य;
	commit_समय = kसमय_प्रकारo_ns(kसमय_sub(kसमय_get(), start_समय));

	/*
	 * weight the commit समय higher than the average समय so we करोn't
	 * react too strongly to vast changes in the commit समय
	 */
	अगर (likely(journal->j_average_commit_समय))
		journal->j_average_commit_समय = (commit_समय +
				journal->j_average_commit_समय*3) / 4;
	अन्यथा
		journal->j_average_commit_समय = commit_समय;

	ग_लिखो_unlock(&journal->j_state_lock);

	अगर (journal->j_commit_callback)
		journal->j_commit_callback(journal, commit_transaction);
	अगर (journal->j_fc_cleanup_callback)
		journal->j_fc_cleanup_callback(journal, 1);

	trace_jbd2_end_commit(journal, commit_transaction);
	jbd_debug(1, "JBD2: commit %d complete, head %d\n",
		  journal->j_commit_sequence, journal->j_tail_sequence);

	ग_लिखो_lock(&journal->j_state_lock);
	journal->j_flags &= ~JBD2_FULL_COMMIT_ONGOING;
	journal->j_flags &= ~JBD2_FAST_COMMIT_ONGOING;
	spin_lock(&journal->j_list_lock);
	commit_transaction->t_state = T_FINISHED;
	/* Check अगर the transaction can be dropped now that we are finished */
	अगर (commit_transaction->t_checkpoपूर्णांक_list == शून्य &&
	    commit_transaction->t_checkpoपूर्णांक_io_list == शून्य) अणु
		__jbd2_journal_drop_transaction(journal, commit_transaction);
		jbd2_journal_मुक्त_transaction(commit_transaction);
	पूर्ण
	spin_unlock(&journal->j_list_lock);
	ग_लिखो_unlock(&journal->j_state_lock);
	wake_up(&journal->j_रुको_करोne_commit);
	wake_up(&journal->j_fc_रुको);

	/*
	 * Calculate overall stats
	 */
	spin_lock(&journal->j_history_lock);
	journal->j_stats.ts_tid++;
	journal->j_stats.ts_requested += stats.ts_requested;
	journal->j_stats.run.rs_रुको += stats.run.rs_रुको;
	journal->j_stats.run.rs_request_delay += stats.run.rs_request_delay;
	journal->j_stats.run.rs_running += stats.run.rs_running;
	journal->j_stats.run.rs_locked += stats.run.rs_locked;
	journal->j_stats.run.rs_flushing += stats.run.rs_flushing;
	journal->j_stats.run.rs_logging += stats.run.rs_logging;
	journal->j_stats.run.rs_handle_count += stats.run.rs_handle_count;
	journal->j_stats.run.rs_blocks += stats.run.rs_blocks;
	journal->j_stats.run.rs_blocks_logged += stats.run.rs_blocks_logged;
	spin_unlock(&journal->j_history_lock);
पूर्ण
