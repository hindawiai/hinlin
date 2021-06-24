<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * linux/fs/jbd2/revoke.c
 *
 * Written by Stephen C. Tweedie <sct@redhat.com>, 2000
 *
 * Copyright 2000 Red Hat corp --- All Rights Reserved
 *
 * Journal revoke routines क्रम the generic fileप्रणाली journaling code;
 * part of the ext2fs journaling प्रणाली.
 *
 * Revoke is the mechanism used to prevent old log records क्रम deleted
 * metadata from being replayed on top of newer data using the same
 * blocks.  The revoke mechanism is used in two separate places:
 *
 * + Commit: during commit we ग_लिखो the entire list of the current
 *   transaction's revoked blocks to the journal
 *
 * + Recovery: during recovery we record the transaction ID of all
 *   revoked blocks.  If there are multiple revoke records in the log
 *   क्रम a single block, only the last one counts, and अगर there is a log
 *   entry क्रम a block beyond the last revoke, then that log entry still
 *   माला_लो replayed.
 *
 * We can get पूर्णांकeractions between revokes and new log data within a
 * single transaction:
 *
 * Block is revoked and then journaled:
 *   The desired end result is the journaling of the new block, so we
 *   cancel the revoke beक्रमe the transaction commits.
 *
 * Block is journaled and then revoked:
 *   The revoke must take precedence over the ग_लिखो of the block, so we
 *   need either to cancel the journal entry or to ग_लिखो the revoke
 *   later in the log than the log block.  In this हाल, we choose the
 *   latter: journaling a block cancels any revoke record क्रम that block
 *   in the current transaction, so any revoke क्रम that block in the
 *   transaction must have happened after the block was journaled and so
 *   the revoke must take precedence.
 *
 * Block is revoked and then written as data:
 *   The data ग_लिखो is allowed to succeed, but the revoke is _not_
 *   cancelled.  We still need to prevent old log records from
 *   overwriting the new data.  We करोn't even need to clear the revoke
 *   bit here.
 *
 * We cache revoke status of a buffer in the current transaction in b_states
 * bits.  As the name says, revokevalid flag indicates that the cached revoke
 * status of a buffer is valid and we can rely on the cached status.
 *
 * Revoke inक्रमmation on buffers is a tri-state value:
 *
 * RevokeValid clear:	no cached revoke status, need to look it up
 * RevokeValid set, Revoked clear:
 *			buffer has not been revoked, and cancel_revoke
 *			need करो nothing.
 * RevokeValid set, Revoked set:
 *			buffer has been revoked.
 *
 * Locking rules:
 * We keep two hash tables of revoke records. One hashtable beदीर्घs to the
 * running transaction (is poपूर्णांकed to by journal->j_revoke), the other one
 * beदीर्घs to the committing transaction. Accesses to the second hash table
 * happen only from the kjournald and no other thपढ़ो touches this table.  Also
 * journal_चयन_revoke_table() which चयनes which hashtable beदीर्घs to the
 * running and which to the committing transaction is called only from
 * kjournald. Thereक्रमe we need no locks when accessing the hashtable beदीर्घing
 * to the committing transaction.
 *
 * All users operating on the hash table beदीर्घing to the running transaction
 * have a handle to the transaction. Thereक्रमe they are safe from kjournald
 * चयनing hash tables under them. For operations on the lists of entries in
 * the hash table j_revoke_lock is used.
 *
 * Finally, also replay code uses the hash tables but at this moment no one अन्यथा
 * can touch them (fileप्रणाली isn't mounted yet) and hence no locking is
 * needed.
 */

#अगर_अघोषित __KERNEL__
#समावेश "jfs_user.h"
#अन्यथा
#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/jbd2.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/init.h>
#समावेश <linux/bपन.स>
#समावेश <linux/log2.h>
#समावेश <linux/hash.h>
#पूर्ण_अगर

अटल काष्ठा kmem_cache *jbd2_revoke_record_cache;
अटल काष्ठा kmem_cache *jbd2_revoke_table_cache;

/* Each revoke record represents one single revoked block.  During
   journal replay, this involves recording the transaction ID of the
   last transaction to revoke this block. */

काष्ठा jbd2_revoke_record_s
अणु
	काष्ठा list_head  hash;
	tid_t		  sequence;	/* Used क्रम recovery only */
	अचिन्हित दीर्घ दीर्घ	  blocknr;
पूर्ण;


/* The revoke table is just a simple hash table of revoke records. */
काष्ठा jbd2_revoke_table_s
अणु
	/* It is conceivable that we might want a larger hash table
	 * क्रम recovery.  Must be a घातer of two. */
	पूर्णांक		  hash_size;
	पूर्णांक		  hash_shअगरt;
	काष्ठा list_head *hash_table;
पूर्ण;


#अगर_घोषित __KERNEL__
अटल व्योम ग_लिखो_one_revoke_record(transaction_t *,
				    काष्ठा list_head *,
				    काष्ठा buffer_head **, पूर्णांक *,
				    काष्ठा jbd2_revoke_record_s *);
अटल व्योम flush_descriptor(journal_t *, काष्ठा buffer_head *, पूर्णांक);
#पूर्ण_अगर

/* Utility functions to मुख्यtain the revoke table */

अटल अंतरभूत पूर्णांक hash(journal_t *journal, अचिन्हित दीर्घ दीर्घ block)
अणु
	वापस hash_64(block, journal->j_revoke->hash_shअगरt);
पूर्ण

अटल पूर्णांक insert_revoke_hash(journal_t *journal, अचिन्हित दीर्घ दीर्घ blocknr,
			      tid_t seq)
अणु
	काष्ठा list_head *hash_list;
	काष्ठा jbd2_revoke_record_s *record;
	gfp_t gfp_mask = GFP_NOFS;

	अगर (journal_oom_retry)
		gfp_mask |= __GFP_NOFAIL;
	record = kmem_cache_alloc(jbd2_revoke_record_cache, gfp_mask);
	अगर (!record)
		वापस -ENOMEM;

	record->sequence = seq;
	record->blocknr = blocknr;
	hash_list = &journal->j_revoke->hash_table[hash(journal, blocknr)];
	spin_lock(&journal->j_revoke_lock);
	list_add(&record->hash, hash_list);
	spin_unlock(&journal->j_revoke_lock);
	वापस 0;
पूर्ण

/* Find a revoke record in the journal's hash table. */

अटल काष्ठा jbd2_revoke_record_s *find_revoke_record(journal_t *journal,
						      अचिन्हित दीर्घ दीर्घ blocknr)
अणु
	काष्ठा list_head *hash_list;
	काष्ठा jbd2_revoke_record_s *record;

	hash_list = &journal->j_revoke->hash_table[hash(journal, blocknr)];

	spin_lock(&journal->j_revoke_lock);
	record = (काष्ठा jbd2_revoke_record_s *) hash_list->next;
	जबतक (&(record->hash) != hash_list) अणु
		अगर (record->blocknr == blocknr) अणु
			spin_unlock(&journal->j_revoke_lock);
			वापस record;
		पूर्ण
		record = (काष्ठा jbd2_revoke_record_s *) record->hash.next;
	पूर्ण
	spin_unlock(&journal->j_revoke_lock);
	वापस शून्य;
पूर्ण

व्योम jbd2_journal_destroy_revoke_record_cache(व्योम)
अणु
	kmem_cache_destroy(jbd2_revoke_record_cache);
	jbd2_revoke_record_cache = शून्य;
पूर्ण

व्योम jbd2_journal_destroy_revoke_table_cache(व्योम)
अणु
	kmem_cache_destroy(jbd2_revoke_table_cache);
	jbd2_revoke_table_cache = शून्य;
पूर्ण

पूर्णांक __init jbd2_journal_init_revoke_record_cache(व्योम)
अणु
	J_ASSERT(!jbd2_revoke_record_cache);
	jbd2_revoke_record_cache = KMEM_CACHE(jbd2_revoke_record_s,
					SLAB_HWCACHE_ALIGN|SLAB_TEMPORARY);

	अगर (!jbd2_revoke_record_cache) अणु
		pr_emerg("JBD2: failed to create revoke_record cache\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक __init jbd2_journal_init_revoke_table_cache(व्योम)
अणु
	J_ASSERT(!jbd2_revoke_table_cache);
	jbd2_revoke_table_cache = KMEM_CACHE(jbd2_revoke_table_s,
					     SLAB_TEMPORARY);
	अगर (!jbd2_revoke_table_cache) अणु
		pr_emerg("JBD2: failed to create revoke_table cache\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा jbd2_revoke_table_s *jbd2_journal_init_revoke_table(पूर्णांक hash_size)
अणु
	पूर्णांक shअगरt = 0;
	पूर्णांक पंचांगp = hash_size;
	काष्ठा jbd2_revoke_table_s *table;

	table = kmem_cache_alloc(jbd2_revoke_table_cache, GFP_KERNEL);
	अगर (!table)
		जाओ out;

	जबतक((पंचांगp >>= 1UL) != 0UL)
		shअगरt++;

	table->hash_size = hash_size;
	table->hash_shअगरt = shअगरt;
	table->hash_table =
		kदो_स्मृति_array(hash_size, माप(काष्ठा list_head), GFP_KERNEL);
	अगर (!table->hash_table) अणु
		kmem_cache_मुक्त(jbd2_revoke_table_cache, table);
		table = शून्य;
		जाओ out;
	पूर्ण

	क्रम (पंचांगp = 0; पंचांगp < hash_size; पंचांगp++)
		INIT_LIST_HEAD(&table->hash_table[पंचांगp]);

out:
	वापस table;
पूर्ण

अटल व्योम jbd2_journal_destroy_revoke_table(काष्ठा jbd2_revoke_table_s *table)
अणु
	पूर्णांक i;
	काष्ठा list_head *hash_list;

	क्रम (i = 0; i < table->hash_size; i++) अणु
		hash_list = &table->hash_table[i];
		J_ASSERT(list_empty(hash_list));
	पूर्ण

	kमुक्त(table->hash_table);
	kmem_cache_मुक्त(jbd2_revoke_table_cache, table);
पूर्ण

/* Initialise the revoke table क्रम a given journal to a given size. */
पूर्णांक jbd2_journal_init_revoke(journal_t *journal, पूर्णांक hash_size)
अणु
	J_ASSERT(journal->j_revoke_table[0] == शून्य);
	J_ASSERT(is_घातer_of_2(hash_size));

	journal->j_revoke_table[0] = jbd2_journal_init_revoke_table(hash_size);
	अगर (!journal->j_revoke_table[0])
		जाओ fail0;

	journal->j_revoke_table[1] = jbd2_journal_init_revoke_table(hash_size);
	अगर (!journal->j_revoke_table[1])
		जाओ fail1;

	journal->j_revoke = journal->j_revoke_table[1];

	spin_lock_init(&journal->j_revoke_lock);

	वापस 0;

fail1:
	jbd2_journal_destroy_revoke_table(journal->j_revoke_table[0]);
	journal->j_revoke_table[0] = शून्य;
fail0:
	वापस -ENOMEM;
पूर्ण

/* Destroy a journal's revoke table.  The table must alपढ़ोy be empty! */
व्योम jbd2_journal_destroy_revoke(journal_t *journal)
अणु
	journal->j_revoke = शून्य;
	अगर (journal->j_revoke_table[0])
		jbd2_journal_destroy_revoke_table(journal->j_revoke_table[0]);
	अगर (journal->j_revoke_table[1])
		jbd2_journal_destroy_revoke_table(journal->j_revoke_table[1]);
पूर्ण


#अगर_घोषित __KERNEL__

/*
 * jbd2_journal_revoke: revoke a given buffer_head from the journal.  This
 * prevents the block from being replayed during recovery अगर we take a
 * crash after this current transaction commits.  Any subsequent
 * metadata ग_लिखोs of the buffer in this transaction cancel the
 * revoke.
 *
 * Note that this call may block --- it is up to the caller to make
 * sure that there are no further calls to journal_ग_लिखो_metadata
 * beक्रमe the revoke is complete.  In ext3, this implies calling the
 * revoke beक्रमe clearing the block biपंचांगap when we are deleting
 * metadata.
 *
 * Revoke perक्रमms a jbd2_journal_क्रमget on any buffer_head passed in as a
 * parameter, but करोes _not_ क्रमget the buffer_head अगर the bh was only
 * found implicitly.
 *
 * bh_in may not be a journalled buffer - it may have come off
 * the hash tables without an attached journal_head.
 *
 * If bh_in is non-zero, jbd2_journal_revoke() will decrement its b_count
 * by one.
 */

पूर्णांक jbd2_journal_revoke(handle_t *handle, अचिन्हित दीर्घ दीर्घ blocknr,
		   काष्ठा buffer_head *bh_in)
अणु
	काष्ठा buffer_head *bh = शून्य;
	journal_t *journal;
	काष्ठा block_device *bdev;
	पूर्णांक err;

	might_sleep();
	अगर (bh_in)
		BUFFER_TRACE(bh_in, "enter");

	journal = handle->h_transaction->t_journal;
	अगर (!jbd2_journal_set_features(journal, 0, 0, JBD2_FEATURE_INCOMPAT_REVOKE))अणु
		J_ASSERT (!"Cannot set revoke feature!");
		वापस -EINVAL;
	पूर्ण

	bdev = journal->j_fs_dev;
	bh = bh_in;

	अगर (!bh) अणु
		bh = __find_get_block(bdev, blocknr, journal->j_blocksize);
		अगर (bh)
			BUFFER_TRACE(bh, "found on hash");
	पूर्ण
#अगर_घोषित JBD2_EXPENSIVE_CHECKING
	अन्यथा अणु
		काष्ठा buffer_head *bh2;

		/* If there is a dअगरferent buffer_head lying around in
		 * memory anywhere... */
		bh2 = __find_get_block(bdev, blocknr, journal->j_blocksize);
		अगर (bh2) अणु
			/* ... and it has RevokeValid status... */
			अगर (bh2 != bh && buffer_revokevalid(bh2))
				/* ...then it better be revoked too,
				 * since it's illegal to create a revoke
				 * record against a buffer_head which is
				 * not marked revoked --- that would
				 * risk missing a subsequent revoke
				 * cancel. */
				J_ASSERT_BH(bh2, buffer_revoked(bh2));
			put_bh(bh2);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (WARN_ON_ONCE(handle->h_revoke_credits <= 0)) अणु
		अगर (!bh_in)
			brअन्यथा(bh);
		वापस -EIO;
	पूर्ण
	/* We really ought not ever to revoke twice in a row without
           first having the revoke cancelled: it's illegal to मुक्त a
           block twice without allocating it in between! */
	अगर (bh) अणु
		अगर (!J_EXPECT_BH(bh, !buffer_revoked(bh),
				 "inconsistent data on disk")) अणु
			अगर (!bh_in)
				brअन्यथा(bh);
			वापस -EIO;
		पूर्ण
		set_buffer_revoked(bh);
		set_buffer_revokevalid(bh);
		अगर (bh_in) अणु
			BUFFER_TRACE(bh_in, "call jbd2_journal_forget");
			jbd2_journal_क्रमget(handle, bh_in);
		पूर्ण अन्यथा अणु
			BUFFER_TRACE(bh, "call brelse");
			__brअन्यथा(bh);
		पूर्ण
	पूर्ण
	handle->h_revoke_credits--;

	jbd_debug(2, "insert revoke for block %llu, bh_in=%p\n",blocknr, bh_in);
	err = insert_revoke_hash(journal, blocknr,
				handle->h_transaction->t_tid);
	BUFFER_TRACE(bh_in, "exit");
	वापस err;
पूर्ण

/*
 * Cancel an outstanding revoke.  For use only पूर्णांकernally by the
 * journaling code (called from jbd2_journal_get_ग_लिखो_access).
 *
 * We trust buffer_revoked() on the buffer अगर the buffer is alपढ़ोy
 * being journaled: अगर there is no revoke pending on the buffer, then we
 * करोn't करो anything here.
 *
 * This would अवरोध अगर it were possible क्रम a buffer to be revoked and
 * discarded, and then पुनः_स्मृतिated within the same transaction.  In such
 * a हाल we would have lost the revoked bit, but when we arrived here
 * the second समय we would still have a pending revoke to cancel.  So,
 * करो not trust the Revoked bit on buffers unless RevokeValid is also
 * set.
 */
पूर्णांक jbd2_journal_cancel_revoke(handle_t *handle, काष्ठा journal_head *jh)
अणु
	काष्ठा jbd2_revoke_record_s *record;
	journal_t *journal = handle->h_transaction->t_journal;
	पूर्णांक need_cancel;
	पूर्णांक did_revoke = 0;	/* akpm: debug */
	काष्ठा buffer_head *bh = jh2bh(jh);

	jbd_debug(4, "journal_head %p, cancelling revoke\n", jh);

	/* Is the existing Revoke bit valid?  If so, we trust it, and
	 * only perक्रमm the full cancel अगर the revoke bit is set.  If
	 * not, we can't trust the revoke bit, and we need to करो the
	 * full search क्रम a revoke record. */
	अगर (test_set_buffer_revokevalid(bh)) अणु
		need_cancel = test_clear_buffer_revoked(bh);
	पूर्ण अन्यथा अणु
		need_cancel = 1;
		clear_buffer_revoked(bh);
	पूर्ण

	अगर (need_cancel) अणु
		record = find_revoke_record(journal, bh->b_blocknr);
		अगर (record) अणु
			jbd_debug(4, "cancelled existing revoke on "
				  "blocknr %llu\n", (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
			spin_lock(&journal->j_revoke_lock);
			list_del(&record->hash);
			spin_unlock(&journal->j_revoke_lock);
			kmem_cache_मुक्त(jbd2_revoke_record_cache, record);
			did_revoke = 1;
		पूर्ण
	पूर्ण

#अगर_घोषित JBD2_EXPENSIVE_CHECKING
	/* There better not be one left behind by now! */
	record = find_revoke_record(journal, bh->b_blocknr);
	J_ASSERT_JH(jh, record == शून्य);
#पूर्ण_अगर

	/* Finally, have we just cleared revoke on an unhashed
	 * buffer_head?  If so, we'd better make sure we clear the
	 * revoked status on any hashed alias too, otherwise the revoke
	 * state machine will get very upset later on. */
	अगर (need_cancel) अणु
		काष्ठा buffer_head *bh2;
		bh2 = __find_get_block(bh->b_bdev, bh->b_blocknr, bh->b_size);
		अगर (bh2) अणु
			अगर (bh2 != bh)
				clear_buffer_revoked(bh2);
			__brअन्यथा(bh2);
		पूर्ण
	पूर्ण
	वापस did_revoke;
पूर्ण

/*
 * journal_clear_revoked_flag clears revoked flag of buffers in
 * revoke table to reflect there is no revoked buffers in the next
 * transaction which is going to be started.
 */
व्योम jbd2_clear_buffer_revoked_flags(journal_t *journal)
अणु
	काष्ठा jbd2_revoke_table_s *revoke = journal->j_revoke;
	पूर्णांक i = 0;

	क्रम (i = 0; i < revoke->hash_size; i++) अणु
		काष्ठा list_head *hash_list;
		काष्ठा list_head *list_entry;
		hash_list = &revoke->hash_table[i];

		list_क्रम_each(list_entry, hash_list) अणु
			काष्ठा jbd2_revoke_record_s *record;
			काष्ठा buffer_head *bh;
			record = (काष्ठा jbd2_revoke_record_s *)list_entry;
			bh = __find_get_block(journal->j_fs_dev,
					      record->blocknr,
					      journal->j_blocksize);
			अगर (bh) अणु
				clear_buffer_revoked(bh);
				__brअन्यथा(bh);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* journal_चयन_revoke table select j_revoke क्रम next transaction
 * we करो not want to suspend any processing until all revokes are
 * written -bzzz
 */
व्योम jbd2_journal_चयन_revoke_table(journal_t *journal)
अणु
	पूर्णांक i;

	अगर (journal->j_revoke == journal->j_revoke_table[0])
		journal->j_revoke = journal->j_revoke_table[1];
	अन्यथा
		journal->j_revoke = journal->j_revoke_table[0];

	क्रम (i = 0; i < journal->j_revoke->hash_size; i++)
		INIT_LIST_HEAD(&journal->j_revoke->hash_table[i]);
पूर्ण

/*
 * Write revoke records to the journal क्रम all entries in the current
 * revoke hash, deleting the entries as we go.
 */
व्योम jbd2_journal_ग_लिखो_revoke_records(transaction_t *transaction,
				       काष्ठा list_head *log_bufs)
अणु
	journal_t *journal = transaction->t_journal;
	काष्ठा buffer_head *descriptor;
	काष्ठा jbd2_revoke_record_s *record;
	काष्ठा jbd2_revoke_table_s *revoke;
	काष्ठा list_head *hash_list;
	पूर्णांक i, offset, count;

	descriptor = शून्य;
	offset = 0;
	count = 0;

	/* select revoke table क्रम committing transaction */
	revoke = journal->j_revoke == journal->j_revoke_table[0] ?
		journal->j_revoke_table[1] : journal->j_revoke_table[0];

	क्रम (i = 0; i < revoke->hash_size; i++) अणु
		hash_list = &revoke->hash_table[i];

		जबतक (!list_empty(hash_list)) अणु
			record = (काष्ठा jbd2_revoke_record_s *)
				hash_list->next;
			ग_लिखो_one_revoke_record(transaction, log_bufs,
						&descriptor, &offset, record);
			count++;
			list_del(&record->hash);
			kmem_cache_मुक्त(jbd2_revoke_record_cache, record);
		पूर्ण
	पूर्ण
	अगर (descriptor)
		flush_descriptor(journal, descriptor, offset);
	jbd_debug(1, "Wrote %d revoke records\n", count);
पूर्ण

/*
 * Write out one revoke record.  We need to create a new descriptor
 * block अगर the old one is full or अगर we have not alपढ़ोy created one.
 */

अटल व्योम ग_लिखो_one_revoke_record(transaction_t *transaction,
				    काष्ठा list_head *log_bufs,
				    काष्ठा buffer_head **descriptorp,
				    पूर्णांक *offsetp,
				    काष्ठा jbd2_revoke_record_s *record)
अणु
	journal_t *journal = transaction->t_journal;
	पूर्णांक csum_size = 0;
	काष्ठा buffer_head *descriptor;
	पूर्णांक sz, offset;

	/* If we are alपढ़ोy पातing, this all becomes a noop.  We
           still need to go round the loop in
           jbd2_journal_ग_लिखो_revoke_records in order to मुक्त all of the
           revoke records: only the IO to the journal is omitted. */
	अगर (is_journal_पातed(journal))
		वापस;

	descriptor = *descriptorp;
	offset = *offsetp;

	/* Do we need to leave space at the end क्रम a checksum? */
	अगर (jbd2_journal_has_csum_v2or3(journal))
		csum_size = माप(काष्ठा jbd2_journal_block_tail);

	अगर (jbd2_has_feature_64bit(journal))
		sz = 8;
	अन्यथा
		sz = 4;

	/* Make sure we have a descriptor with space left क्रम the record */
	अगर (descriptor) अणु
		अगर (offset + sz > journal->j_blocksize - csum_size) अणु
			flush_descriptor(journal, descriptor, offset);
			descriptor = शून्य;
		पूर्ण
	पूर्ण

	अगर (!descriptor) अणु
		descriptor = jbd2_journal_get_descriptor_buffer(transaction,
							JBD2_REVOKE_BLOCK);
		अगर (!descriptor)
			वापस;

		/* Record it so that we can रुको क्रम IO completion later */
		BUFFER_TRACE(descriptor, "file in log_bufs");
		jbd2_file_log_bh(log_bufs, descriptor);

		offset = माप(jbd2_journal_revoke_header_t);
		*descriptorp = descriptor;
	पूर्ण

	अगर (jbd2_has_feature_64bit(journal))
		* ((__be64 *)(&descriptor->b_data[offset])) =
			cpu_to_be64(record->blocknr);
	अन्यथा
		* ((__be32 *)(&descriptor->b_data[offset])) =
			cpu_to_be32(record->blocknr);
	offset += sz;

	*offsetp = offset;
पूर्ण

/*
 * Flush a revoke descriptor out to the journal.  If we are पातing,
 * this is a noop; otherwise we are generating a buffer which needs to
 * be रुकोed क्रम during commit, so it has to go onto the appropriate
 * journal buffer list.
 */

अटल व्योम flush_descriptor(journal_t *journal,
			     काष्ठा buffer_head *descriptor,
			     पूर्णांक offset)
अणु
	jbd2_journal_revoke_header_t *header;

	अगर (is_journal_पातed(journal))
		वापस;

	header = (jbd2_journal_revoke_header_t *)descriptor->b_data;
	header->r_count = cpu_to_be32(offset);
	jbd2_descriptor_block_csum_set(journal, descriptor);

	set_buffer_jग_लिखो(descriptor);
	BUFFER_TRACE(descriptor, "write");
	set_buffer_dirty(descriptor);
	ग_लिखो_dirty_buffer(descriptor, REQ_SYNC);
पूर्ण
#पूर्ण_अगर

/*
 * Revoke support क्रम recovery.
 *
 * Recovery needs to be able to:
 *
 *  record all revoke records, including the tid of the latest instance
 *  of each revoke in the journal
 *
 *  check whether a given block in a given transaction should be replayed
 *  (ie. has not been revoked by a revoke record in that or a subsequent
 *  transaction)
 *
 *  empty the revoke table after recovery.
 */

/*
 * First, setting revoke records.  We create a new revoke record क्रम
 * every block ever revoked in the log as we scan it क्रम recovery, and
 * we update the existing records अगर we find multiple revokes क्रम a
 * single block.
 */

पूर्णांक jbd2_journal_set_revoke(journal_t *journal,
		       अचिन्हित दीर्घ दीर्घ blocknr,
		       tid_t sequence)
अणु
	काष्ठा jbd2_revoke_record_s *record;

	record = find_revoke_record(journal, blocknr);
	अगर (record) अणु
		/* If we have multiple occurrences, only record the
		 * latest sequence number in the hashed record */
		अगर (tid_gt(sequence, record->sequence))
			record->sequence = sequence;
		वापस 0;
	पूर्ण
	वापस insert_revoke_hash(journal, blocknr, sequence);
पूर्ण

/*
 * Test revoke records.  For a given block referenced in the log, has
 * that block been revoked?  A revoke record with a given transaction
 * sequence number revokes all blocks in that transaction and earlier
 * ones, but later transactions still need replayed.
 */

पूर्णांक jbd2_journal_test_revoke(journal_t *journal,
			अचिन्हित दीर्घ दीर्घ blocknr,
			tid_t sequence)
अणु
	काष्ठा jbd2_revoke_record_s *record;

	record = find_revoke_record(journal, blocknr);
	अगर (!record)
		वापस 0;
	अगर (tid_gt(sequence, record->sequence))
		वापस 0;
	वापस 1;
पूर्ण

/*
 * Finally, once recovery is over, we need to clear the revoke table so
 * that it can be reused by the running fileप्रणाली.
 */

व्योम jbd2_journal_clear_revoke(journal_t *journal)
अणु
	पूर्णांक i;
	काष्ठा list_head *hash_list;
	काष्ठा jbd2_revoke_record_s *record;
	काष्ठा jbd2_revoke_table_s *revoke;

	revoke = journal->j_revoke;

	क्रम (i = 0; i < revoke->hash_size; i++) अणु
		hash_list = &revoke->hash_table[i];
		जबतक (!list_empty(hash_list)) अणु
			record = (काष्ठा jbd2_revoke_record_s*) hash_list->next;
			list_del(&record->hash);
			kmem_cache_मुक्त(jbd2_revoke_record_cache, record);
		पूर्ण
	पूर्ण
पूर्ण
