<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * linux/fs/jbd2/recovery.c
 *
 * Written by Stephen C. Tweedie <sct@redhat.com>, 1999
 *
 * Copyright 1999-2000 Red Hat Software --- All Rights Reserved
 *
 * Journal recovery routines क्रम the generic fileप्रणाली journaling code;
 * part of the ext2fs journaling प्रणाली.
 */

#अगर_अघोषित __KERNEL__
#समावेश "jfs_user.h"
#अन्यथा
#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/jbd2.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/crc32.h>
#समावेश <linux/blkdev.h>
#पूर्ण_अगर

/*
 * Maपूर्णांकain inक्रमmation about the progress of the recovery job, so that
 * the dअगरferent passes can carry inक्रमmation between them.
 */
काष्ठा recovery_info
अणु
	tid_t		start_transaction;
	tid_t		end_transaction;

	पूर्णांक		nr_replays;
	पूर्णांक		nr_revokes;
	पूर्णांक		nr_revoke_hits;
पूर्ण;

अटल पूर्णांक करो_one_pass(journal_t *journal,
				काष्ठा recovery_info *info, क्रमागत passtype pass);
अटल पूर्णांक scan_revoke_records(journal_t *, काष्ठा buffer_head *,
				tid_t, काष्ठा recovery_info *);

#अगर_घोषित __KERNEL__

/* Release पढ़ोahead buffers after use */
अटल व्योम journal_brअन्यथा_array(काष्ठा buffer_head *b[], पूर्णांक n)
अणु
	जबतक (--n >= 0)
		brअन्यथा (b[n]);
पूर्ण


/*
 * When पढ़ोing from the journal, we are going through the block device
 * layer directly and so there is no पढ़ोahead being करोne क्रम us.  We
 * need to implement any पढ़ोahead ourselves अगर we want it to happen at
 * all.  Recovery is basically one दीर्घ sequential पढ़ो, so make sure we
 * करो the IO in reasonably large chunks.
 *
 * This is not so critical that we need to be enormously clever about
 * the पढ़ोahead size, though.  128K is a purely arbitrary, good-enough
 * fixed value.
 */

#घोषणा MAXBUF 8
अटल पूर्णांक करो_पढ़ोahead(journal_t *journal, अचिन्हित पूर्णांक start)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक max, nbufs, next;
	अचिन्हित दीर्घ दीर्घ blocknr;
	काष्ठा buffer_head *bh;

	काष्ठा buffer_head * bufs[MAXBUF];

	/* Do up to 128K of पढ़ोahead */
	max = start + (128 * 1024 / journal->j_blocksize);
	अगर (max > journal->j_total_len)
		max = journal->j_total_len;

	/* Do the पढ़ोahead itself.  We'll submit MAXBUF buffer_heads at
	 * a समय to the block device IO layer. */

	nbufs = 0;

	क्रम (next = start; next < max; next++) अणु
		err = jbd2_journal_bmap(journal, next, &blocknr);

		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "JBD2: bad block at offset %u\n",
				next);
			जाओ failed;
		पूर्ण

		bh = __getblk(journal->j_dev, blocknr, journal->j_blocksize);
		अगर (!bh) अणु
			err = -ENOMEM;
			जाओ failed;
		पूर्ण

		अगर (!buffer_uptodate(bh) && !buffer_locked(bh)) अणु
			bufs[nbufs++] = bh;
			अगर (nbufs == MAXBUF) अणु
				ll_rw_block(REQ_OP_READ, 0, nbufs, bufs);
				journal_brअन्यथा_array(bufs, nbufs);
				nbufs = 0;
			पूर्ण
		पूर्ण अन्यथा
			brअन्यथा(bh);
	पूर्ण

	अगर (nbufs)
		ll_rw_block(REQ_OP_READ, 0, nbufs, bufs);
	err = 0;

failed:
	अगर (nbufs)
		journal_brअन्यथा_array(bufs, nbufs);
	वापस err;
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */


/*
 * Read a block from the journal
 */

अटल पूर्णांक jपढ़ो(काष्ठा buffer_head **bhp, journal_t *journal,
		 अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ दीर्घ blocknr;
	काष्ठा buffer_head *bh;

	*bhp = शून्य;

	अगर (offset >= journal->j_total_len) अणु
		prपूर्णांकk(KERN_ERR "JBD2: corrupted journal superblock\n");
		वापस -EFSCORRUPTED;
	पूर्ण

	err = jbd2_journal_bmap(journal, offset, &blocknr);

	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "JBD2: bad block at offset %u\n",
			offset);
		वापस err;
	पूर्ण

	bh = __getblk(journal->j_dev, blocknr, journal->j_blocksize);
	अगर (!bh)
		वापस -ENOMEM;

	अगर (!buffer_uptodate(bh)) अणु
		/* If this is a bअक्रम new buffer, start पढ़ोahead.
                   Otherwise, we assume we are alपढ़ोy पढ़ोing it.  */
		अगर (!buffer_req(bh))
			करो_पढ़ोahead(journal, offset);
		रुको_on_buffer(bh);
	पूर्ण

	अगर (!buffer_uptodate(bh)) अणु
		prपूर्णांकk(KERN_ERR "JBD2: Failed to read block at offset %u\n",
			offset);
		brअन्यथा(bh);
		वापस -EIO;
	पूर्ण

	*bhp = bh;
	वापस 0;
पूर्ण

अटल पूर्णांक jbd2_descriptor_block_csum_verअगरy(journal_t *j, व्योम *buf)
अणु
	काष्ठा jbd2_journal_block_tail *tail;
	__be32 provided;
	__u32 calculated;

	अगर (!jbd2_journal_has_csum_v2or3(j))
		वापस 1;

	tail = (काष्ठा jbd2_journal_block_tail *)(buf + j->j_blocksize -
			माप(काष्ठा jbd2_journal_block_tail));
	provided = tail->t_checksum;
	tail->t_checksum = 0;
	calculated = jbd2_chksum(j, j->j_csum_seed, buf, j->j_blocksize);
	tail->t_checksum = provided;

	वापस provided == cpu_to_be32(calculated);
पूर्ण

/*
 * Count the number of in-use tags in a journal descriptor block.
 */

अटल पूर्णांक count_tags(journal_t *journal, काष्ठा buffer_head *bh)
अणु
	अक्षर *			tagp;
	journal_block_tag_t *	tag;
	पूर्णांक			nr = 0, size = journal->j_blocksize;
	पूर्णांक			tag_bytes = journal_tag_bytes(journal);

	अगर (jbd2_journal_has_csum_v2or3(journal))
		size -= माप(काष्ठा jbd2_journal_block_tail);

	tagp = &bh->b_data[माप(journal_header_t)];

	जबतक ((tagp - bh->b_data + tag_bytes) <= size) अणु
		tag = (journal_block_tag_t *) tagp;

		nr++;
		tagp += tag_bytes;
		अगर (!(tag->t_flags & cpu_to_be16(JBD2_FLAG_SAME_UUID)))
			tagp += 16;

		अगर (tag->t_flags & cpu_to_be16(JBD2_FLAG_LAST_TAG))
			अवरोध;
	पूर्ण

	वापस nr;
पूर्ण


/* Make sure we wrap around the log correctly! */
#घोषणा wrap(journal, var)						\
करो अणु									\
	अचिन्हित दीर्घ _wrap_last =					\
		jbd2_has_feature_fast_commit(journal) ?			\
			(journal)->j_fc_last : (journal)->j_last;	\
									\
	अगर (var >= _wrap_last)						\
		var -= (_wrap_last - (journal)->j_first);		\
पूर्ण जबतक (0)

अटल पूर्णांक fc_करो_one_pass(journal_t *journal,
			  काष्ठा recovery_info *info, क्रमागत passtype pass)
अणु
	अचिन्हित पूर्णांक expected_commit_id = info->end_transaction;
	अचिन्हित दीर्घ next_fc_block;
	काष्ठा buffer_head *bh;
	पूर्णांक err = 0;

	next_fc_block = journal->j_fc_first;
	अगर (!journal->j_fc_replay_callback)
		वापस 0;

	जबतक (next_fc_block <= journal->j_fc_last) अणु
		jbd_debug(3, "Fast commit replay: next block %ld\n",
			  next_fc_block);
		err = jपढ़ो(&bh, journal, next_fc_block);
		अगर (err) अणु
			jbd_debug(3, "Fast commit replay: read error\n");
			अवरोध;
		पूर्ण

		err = journal->j_fc_replay_callback(journal, bh, pass,
					next_fc_block - journal->j_fc_first,
					expected_commit_id);
		next_fc_block++;
		अगर (err < 0 || err == JBD2_FC_REPLAY_STOP)
			अवरोध;
		err = 0;
	पूर्ण

	अगर (err)
		jbd_debug(3, "Fast commit replay failed, err = %d\n", err);

	वापस err;
पूर्ण

/**
 * jbd2_journal_recover - recovers a on-disk journal
 * @journal: the journal to recover
 *
 * The primary function क्रम recovering the log contents when mounting a
 * journaled device.
 *
 * Recovery is करोne in three passes.  In the first pass, we look क्रम the
 * end of the log.  In the second, we assemble the list of revoke
 * blocks.  In the third and final pass, we replay any un-revoked blocks
 * in the log.
 */
पूर्णांक jbd2_journal_recover(journal_t *journal)
अणु
	पूर्णांक			err, err2;
	journal_superblock_t *	sb;

	काष्ठा recovery_info	info;

	स_रखो(&info, 0, माप(info));
	sb = journal->j_superblock;

	/*
	 * The journal superblock's s_start field (the current log head)
	 * is always zero अगर, and only अगर, the journal was cleanly
	 * unmounted.
	 */

	अगर (!sb->s_start) अणु
		jbd_debug(1, "No recovery required, last transaction %d\n",
			  be32_to_cpu(sb->s_sequence));
		journal->j_transaction_sequence = be32_to_cpu(sb->s_sequence) + 1;
		वापस 0;
	पूर्ण

	err = करो_one_pass(journal, &info, PASS_SCAN);
	अगर (!err)
		err = करो_one_pass(journal, &info, PASS_REVOKE);
	अगर (!err)
		err = करो_one_pass(journal, &info, PASS_REPLAY);

	jbd_debug(1, "JBD2: recovery, exit status %d, "
		  "recovered transactions %u to %u\n",
		  err, info.start_transaction, info.end_transaction);
	jbd_debug(1, "JBD2: Replayed %d and revoked %d/%d blocks\n",
		  info.nr_replays, info.nr_revoke_hits, info.nr_revokes);

	/* Restart the log at the next transaction ID, thus invalidating
	 * any existing commit records in the log. */
	journal->j_transaction_sequence = ++info.end_transaction;

	jbd2_journal_clear_revoke(journal);
	err2 = sync_blockdev(journal->j_fs_dev);
	अगर (!err)
		err = err2;
	/* Make sure all replayed data is on permanent storage */
	अगर (journal->j_flags & JBD2_BARRIER) अणु
		err2 = blkdev_issue_flush(journal->j_fs_dev);
		अगर (!err)
			err = err2;
	पूर्ण
	वापस err;
पूर्ण

/**
 * jbd2_journal_skip_recovery - Start journal and wipe निकासing records
 * @journal: journal to startup
 *
 * Locate any valid recovery inक्रमmation from the journal and set up the
 * journal काष्ठाures in memory to ignore it (presumably because the
 * caller has evidence that it is out of date).
 * This function करोesn't appear to be exported..
 *
 * We perक्रमm one pass over the journal to allow us to tell the user how
 * much recovery inक्रमmation is being erased, and to let us initialise
 * the journal transaction sequence numbers to the next unused ID.
 */
पूर्णांक jbd2_journal_skip_recovery(journal_t *journal)
अणु
	पूर्णांक			err;

	काष्ठा recovery_info	info;

	स_रखो (&info, 0, माप(info));

	err = करो_one_pass(journal, &info, PASS_SCAN);

	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "JBD2: error %d scanning journal\n", err);
		++journal->j_transaction_sequence;
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_JBD2_DEBUG
		पूर्णांक dropped = info.end_transaction - 
			be32_to_cpu(journal->j_superblock->s_sequence);
		jbd_debug(1,
			  "JBD2: ignoring %d transaction%s from the journal.\n",
			  dropped, (dropped == 1) ? "" : "s");
#पूर्ण_अगर
		journal->j_transaction_sequence = ++info.end_transaction;
	पूर्ण

	journal->j_tail = 0;
	वापस err;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ दीर्घ पढ़ो_tag_block(journal_t *journal,
						journal_block_tag_t *tag)
अणु
	अचिन्हित दीर्घ दीर्घ block = be32_to_cpu(tag->t_blocknr);
	अगर (jbd2_has_feature_64bit(journal))
		block |= (u64)be32_to_cpu(tag->t_blocknr_high) << 32;
	वापस block;
पूर्ण

/*
 * calc_chksums calculates the checksums क्रम the blocks described in the
 * descriptor block.
 */
अटल पूर्णांक calc_chksums(journal_t *journal, काष्ठा buffer_head *bh,
			अचिन्हित दीर्घ *next_log_block, __u32 *crc32_sum)
अणु
	पूर्णांक i, num_blks, err;
	अचिन्हित दीर्घ io_block;
	काष्ठा buffer_head *obh;

	num_blks = count_tags(journal, bh);
	/* Calculate checksum of the descriptor block. */
	*crc32_sum = crc32_be(*crc32_sum, (व्योम *)bh->b_data, bh->b_size);

	क्रम (i = 0; i < num_blks; i++) अणु
		io_block = (*next_log_block)++;
		wrap(journal, *next_log_block);
		err = jपढ़ो(&obh, journal, io_block);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "JBD2: IO error %d recovering block "
				"%lu in log\n", err, io_block);
			वापस 1;
		पूर्ण अन्यथा अणु
			*crc32_sum = crc32_be(*crc32_sum, (व्योम *)obh->b_data,
				     obh->b_size);
		पूर्ण
		put_bh(obh);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक jbd2_commit_block_csum_verअगरy(journal_t *j, व्योम *buf)
अणु
	काष्ठा commit_header *h;
	__be32 provided;
	__u32 calculated;

	अगर (!jbd2_journal_has_csum_v2or3(j))
		वापस 1;

	h = buf;
	provided = h->h_chksum[0];
	h->h_chksum[0] = 0;
	calculated = jbd2_chksum(j, j->j_csum_seed, buf, j->j_blocksize);
	h->h_chksum[0] = provided;

	वापस provided == cpu_to_be32(calculated);
पूर्ण

अटल पूर्णांक jbd2_block_tag_csum_verअगरy(journal_t *j, journal_block_tag_t *tag,
				      व्योम *buf, __u32 sequence)
अणु
	journal_block_tag3_t *tag3 = (journal_block_tag3_t *)tag;
	__u32 csum32;
	__be32 seq;

	अगर (!jbd2_journal_has_csum_v2or3(j))
		वापस 1;

	seq = cpu_to_be32(sequence);
	csum32 = jbd2_chksum(j, j->j_csum_seed, (__u8 *)&seq, माप(seq));
	csum32 = jbd2_chksum(j, csum32, buf, j->j_blocksize);

	अगर (jbd2_has_feature_csum3(j))
		वापस tag3->t_checksum == cpu_to_be32(csum32);
	अन्यथा
		वापस tag->t_checksum == cpu_to_be16(csum32);
पूर्ण

अटल पूर्णांक करो_one_pass(journal_t *journal,
			काष्ठा recovery_info *info, क्रमागत passtype pass)
अणु
	अचिन्हित पूर्णांक		first_commit_ID, next_commit_ID;
	अचिन्हित दीर्घ		next_log_block;
	पूर्णांक			err, success = 0;
	journal_superblock_t *	sb;
	journal_header_t *	पंचांगp;
	काष्ठा buffer_head *	bh;
	अचिन्हित पूर्णांक		sequence;
	पूर्णांक			blocktype;
	पूर्णांक			tag_bytes = journal_tag_bytes(journal);
	__u32			crc32_sum = ~0; /* Transactional Checksums */
	पूर्णांक			descr_csum_size = 0;
	पूर्णांक			block_error = 0;
	bool			need_check_commit_समय = false;
	__u64			last_trans_commit_समय = 0, commit_समय;

	/*
	 * First thing is to establish what we expect to find in the log
	 * (in terms of transaction IDs), and where (in terms of log
	 * block offsets): query the superblock.
	 */

	sb = journal->j_superblock;
	next_commit_ID = be32_to_cpu(sb->s_sequence);
	next_log_block = be32_to_cpu(sb->s_start);

	first_commit_ID = next_commit_ID;
	अगर (pass == PASS_SCAN)
		info->start_transaction = first_commit_ID;

	jbd_debug(1, "Starting recovery pass %d\n", pass);

	/*
	 * Now we walk through the log, transaction by transaction,
	 * making sure that each transaction has a commit block in the
	 * expected place.  Each complete transaction माला_लो replayed back
	 * पूर्णांकo the मुख्य fileप्रणाली.
	 */

	जबतक (1) अणु
		पूर्णांक			flags;
		अक्षर *			tagp;
		journal_block_tag_t *	tag;
		काष्ठा buffer_head *	obh;
		काष्ठा buffer_head *	nbh;

		cond_resched();

		/* If we alपढ़ोy know where to stop the log traversal,
		 * check right now that we haven't gone past the end of
		 * the log. */

		अगर (pass != PASS_SCAN)
			अगर (tid_geq(next_commit_ID, info->end_transaction))
				अवरोध;

		jbd_debug(2, "Scanning for sequence ID %u at %lu/%lu\n",
			  next_commit_ID, next_log_block,
			  jbd2_has_feature_fast_commit(journal) ?
			  journal->j_fc_last : journal->j_last);

		/* Skip over each chunk of the transaction looking
		 * either the next descriptor block or the final commit
		 * record. */

		jbd_debug(3, "JBD2: checking block %ld\n", next_log_block);
		err = jपढ़ो(&bh, journal, next_log_block);
		अगर (err)
			जाओ failed;

		next_log_block++;
		wrap(journal, next_log_block);

		/* What kind of buffer is it?
		 *
		 * If it is a descriptor block, check that it has the
		 * expected sequence number.  Otherwise, we're all करोne
		 * here. */

		पंचांगp = (journal_header_t *)bh->b_data;

		अगर (पंचांगp->h_magic != cpu_to_be32(JBD2_MAGIC_NUMBER)) अणु
			brअन्यथा(bh);
			अवरोध;
		पूर्ण

		blocktype = be32_to_cpu(पंचांगp->h_blocktype);
		sequence = be32_to_cpu(पंचांगp->h_sequence);
		jbd_debug(3, "Found magic %d, sequence %d\n",
			  blocktype, sequence);

		अगर (sequence != next_commit_ID) अणु
			brअन्यथा(bh);
			अवरोध;
		पूर्ण

		/* OK, we have a valid descriptor block which matches
		 * all of the sequence number checks.  What are we going
		 * to करो with it?  That depends on the pass... */

		चयन(blocktype) अणु
		हाल JBD2_DESCRIPTOR_BLOCK:
			/* Verअगरy checksum first */
			अगर (jbd2_journal_has_csum_v2or3(journal))
				descr_csum_size =
					माप(काष्ठा jbd2_journal_block_tail);
			अगर (descr_csum_size > 0 &&
			    !jbd2_descriptor_block_csum_verअगरy(journal,
							       bh->b_data)) अणु
				/*
				 * PASS_SCAN can see stale blocks due to lazy
				 * journal init. Don't error out on those yet.
				 */
				अगर (pass != PASS_SCAN) अणु
					pr_err("JBD2: Invalid checksum recovering block %lu in log\n",
					       next_log_block);
					err = -EFSBADCRC;
					brअन्यथा(bh);
					जाओ failed;
				पूर्ण
				need_check_commit_समय = true;
				jbd_debug(1,
					"invalid descriptor block found in %lu\n",
					next_log_block);
			पूर्ण

			/* If it is a valid descriptor block, replay it
			 * in pass REPLAY; अगर journal_checksums enabled, then
			 * calculate checksums in PASS_SCAN, otherwise,
			 * just skip over the blocks it describes. */
			अगर (pass != PASS_REPLAY) अणु
				अगर (pass == PASS_SCAN &&
				    jbd2_has_feature_checksum(journal) &&
				    !need_check_commit_समय &&
				    !info->end_transaction) अणु
					अगर (calc_chksums(journal, bh,
							&next_log_block,
							&crc32_sum)) अणु
						put_bh(bh);
						अवरोध;
					पूर्ण
					put_bh(bh);
					जारी;
				पूर्ण
				next_log_block += count_tags(journal, bh);
				wrap(journal, next_log_block);
				put_bh(bh);
				जारी;
			पूर्ण

			/* A descriptor block: we can now ग_लिखो all of
			 * the data blocks.  Yay, useful work is finally
			 * getting करोne here! */

			tagp = &bh->b_data[माप(journal_header_t)];
			जबतक ((tagp - bh->b_data + tag_bytes)
			       <= journal->j_blocksize - descr_csum_size) अणु
				अचिन्हित दीर्घ io_block;

				tag = (journal_block_tag_t *) tagp;
				flags = be16_to_cpu(tag->t_flags);

				io_block = next_log_block++;
				wrap(journal, next_log_block);
				err = jपढ़ो(&obh, journal, io_block);
				अगर (err) अणु
					/* Recover what we can, but
					 * report failure at the end. */
					success = err;
					prपूर्णांकk(KERN_ERR
						"JBD2: IO error %d recovering "
						"block %ld in log\n",
						err, io_block);
				पूर्ण अन्यथा अणु
					अचिन्हित दीर्घ दीर्घ blocknr;

					J_ASSERT(obh != शून्य);
					blocknr = पढ़ो_tag_block(journal,
								 tag);

					/* If the block has been
					 * revoked, then we're all करोne
					 * here. */
					अगर (jbd2_journal_test_revoke
					    (journal, blocknr,
					     next_commit_ID)) अणु
						brअन्यथा(obh);
						++info->nr_revoke_hits;
						जाओ skip_ग_लिखो;
					पूर्ण

					/* Look क्रम block corruption */
					अगर (!jbd2_block_tag_csum_verअगरy(
						journal, tag, obh->b_data,
						be32_to_cpu(पंचांगp->h_sequence))) अणु
						brअन्यथा(obh);
						success = -EFSBADCRC;
						prपूर्णांकk(KERN_ERR "JBD2: Invalid "
						       "checksum recovering "
						       "data block %llu in "
						       "log\n", blocknr);
						block_error = 1;
						जाओ skip_ग_लिखो;
					पूर्ण

					/* Find a buffer क्रम the new
					 * data being restored */
					nbh = __getblk(journal->j_fs_dev,
							blocknr,
							journal->j_blocksize);
					अगर (nbh == शून्य) अणु
						prपूर्णांकk(KERN_ERR
						       "JBD2: Out of memory "
						       "during recovery.\n");
						err = -ENOMEM;
						brअन्यथा(bh);
						brअन्यथा(obh);
						जाओ failed;
					पूर्ण

					lock_buffer(nbh);
					स_नकल(nbh->b_data, obh->b_data,
							journal->j_blocksize);
					अगर (flags & JBD2_FLAG_ESCAPE) अणु
						*((__be32 *)nbh->b_data) =
						cpu_to_be32(JBD2_MAGIC_NUMBER);
					पूर्ण

					BUFFER_TRACE(nbh, "marking dirty");
					set_buffer_uptodate(nbh);
					mark_buffer_dirty(nbh);
					BUFFER_TRACE(nbh, "marking uptodate");
					++info->nr_replays;
					/* ll_rw_block(WRITE, 1, &nbh); */
					unlock_buffer(nbh);
					brअन्यथा(obh);
					brअन्यथा(nbh);
				पूर्ण

			skip_ग_लिखो:
				tagp += tag_bytes;
				अगर (!(flags & JBD2_FLAG_SAME_UUID))
					tagp += 16;

				अगर (flags & JBD2_FLAG_LAST_TAG)
					अवरोध;
			पूर्ण

			brअन्यथा(bh);
			जारी;

		हाल JBD2_COMMIT_BLOCK:
			/*     How to dअगरferentiate between पूर्णांकerrupted commit
			 *               and journal corruption ?
			 *
			 * अणुnth transactionपूर्ण
			 *        Checksum Verअगरication Failed
			 *			 |
			 *		 ____________________
			 *		|		     |
			 * 	async_commit             sync_commit
			 *     		|                    |
			 *		| GO TO NEXT    "Journal Corruption"
			 *		| TRANSACTION
			 *		|
			 * अणु(n+1)th transanctionपूर्ण
			 *		|
			 * 	 _______|______________
			 * 	|	 	      |
			 * Commit block found	Commit block not found
			 *      |		      |
			 * "Journal Corruption"       |
			 *		 _____________|_________
			 *     		|	           	|
			 *	nth trans corrupt	OR   nth trans
			 *	and (n+1)th पूर्णांकerrupted     पूर्णांकerrupted
			 *	beक्रमe commit block
			 *      could reach the disk.
			 *	(Cannot find the dअगरference in above
			 *	 mentioned conditions. Hence assume
			 *	 "Interrupted Commit".)
			 */
			commit_समय = be64_to_cpu(
				((काष्ठा commit_header *)bh->b_data)->h_commit_sec);
			/*
			 * If need_check_commit_समय is set, it means we are in
			 * PASS_SCAN and csum verअगरy failed beक्रमe. If
			 * commit_समय is increasing, it's the same journal,
			 * otherwise it is stale journal block, just end this
			 * recovery.
			 */
			अगर (need_check_commit_समय) अणु
				अगर (commit_समय >= last_trans_commit_समय) अणु
					pr_err("JBD2: Invalid checksum found in transaction %u\n",
					       next_commit_ID);
					err = -EFSBADCRC;
					brअन्यथा(bh);
					जाओ failed;
				पूर्ण
			ignore_crc_mismatch:
				/*
				 * It likely करोes not beदीर्घ to same journal,
				 * just end this recovery with success.
				 */
				jbd_debug(1, "JBD2: Invalid checksum ignored in transaction %u, likely stale data\n",
					  next_commit_ID);
				err = 0;
				brअन्यथा(bh);
				जाओ करोne;
			पूर्ण

			/*
			 * Found an expected commit block: अगर checksums
			 * are present, verअगरy them in PASS_SCAN; अन्यथा not
			 * much to करो other than move on to the next sequence
			 * number.
			 */
			अगर (pass == PASS_SCAN &&
			    jbd2_has_feature_checksum(journal)) अणु
				काष्ठा commit_header *cbh =
					(काष्ठा commit_header *)bh->b_data;
				अचिन्हित found_chksum =
					be32_to_cpu(cbh->h_chksum[0]);

				अगर (info->end_transaction) अणु
					journal->j_failed_commit =
						info->end_transaction;
					brअन्यथा(bh);
					अवरोध;
				पूर्ण

				/* Neither checksum match nor unused? */
				अगर (!((crc32_sum == found_chksum &&
				       cbh->h_chksum_type ==
						JBD2_CRC32_CHKSUM &&
				       cbh->h_chksum_size ==
						JBD2_CRC32_CHKSUM_SIZE) ||
				      (cbh->h_chksum_type == 0 &&
				       cbh->h_chksum_size == 0 &&
				       found_chksum == 0)))
					जाओ chksum_error;

				crc32_sum = ~0;
			पूर्ण
			अगर (pass == PASS_SCAN &&
			    !jbd2_commit_block_csum_verअगरy(journal,
							   bh->b_data)) अणु
			chksum_error:
				अगर (commit_समय < last_trans_commit_समय)
					जाओ ignore_crc_mismatch;
				info->end_transaction = next_commit_ID;

				अगर (!jbd2_has_feature_async_commit(journal)) अणु
					journal->j_failed_commit =
						next_commit_ID;
					brअन्यथा(bh);
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (pass == PASS_SCAN)
				last_trans_commit_समय = commit_समय;
			brअन्यथा(bh);
			next_commit_ID++;
			जारी;

		हाल JBD2_REVOKE_BLOCK:
			/*
			 * Check revoke block crc in pass_scan, अगर csum verअगरy
			 * failed, check commit block समय later.
			 */
			अगर (pass == PASS_SCAN &&
			    !jbd2_descriptor_block_csum_verअगरy(journal,
							       bh->b_data)) अणु
				jbd_debug(1, "JBD2: invalid revoke block found in %lu\n",
					  next_log_block);
				need_check_commit_समय = true;
			पूर्ण
			/* If we aren't in the REVOKE pass, then we can
			 * just skip over this block. */
			अगर (pass != PASS_REVOKE) अणु
				brअन्यथा(bh);
				जारी;
			पूर्ण

			err = scan_revoke_records(journal, bh,
						  next_commit_ID, info);
			brअन्यथा(bh);
			अगर (err)
				जाओ failed;
			जारी;

		शेष:
			jbd_debug(3, "Unrecognised magic %d, end of scan.\n",
				  blocktype);
			brअन्यथा(bh);
			जाओ करोne;
		पूर्ण
	पूर्ण

 करोne:
	/*
	 * We broke out of the log scan loop: either we came to the
	 * known end of the log or we found an unexpected block in the
	 * log.  If the latter happened, then we know that the "current"
	 * transaction marks the end of the valid log.
	 */

	अगर (pass == PASS_SCAN) अणु
		अगर (!info->end_transaction)
			info->end_transaction = next_commit_ID;
	पूर्ण अन्यथा अणु
		/* It's really bad news अगर dअगरferent passes end up at
		 * dअगरferent places (but possible due to IO errors). */
		अगर (info->end_transaction != next_commit_ID) अणु
			prपूर्णांकk(KERN_ERR "JBD2: recovery pass %d ended at "
				"transaction %u, expected %u\n",
				pass, next_commit_ID, info->end_transaction);
			अगर (!success)
				success = -EIO;
		पूर्ण
	पूर्ण

	अगर (jbd2_has_feature_fast_commit(journal) &&  pass != PASS_REVOKE) अणु
		err = fc_करो_one_pass(journal, info, pass);
		अगर (err)
			success = err;
	पूर्ण

	अगर (block_error && success == 0)
		success = -EIO;
	वापस success;

 failed:
	वापस err;
पूर्ण

/* Scan a revoke record, marking all blocks mentioned as revoked. */

अटल पूर्णांक scan_revoke_records(journal_t *journal, काष्ठा buffer_head *bh,
			       tid_t sequence, काष्ठा recovery_info *info)
अणु
	jbd2_journal_revoke_header_t *header;
	पूर्णांक offset, max;
	पूर्णांक csum_size = 0;
	__u32 rcount;
	पूर्णांक record_len = 4;

	header = (jbd2_journal_revoke_header_t *) bh->b_data;
	offset = माप(jbd2_journal_revoke_header_t);
	rcount = be32_to_cpu(header->r_count);

	अगर (jbd2_journal_has_csum_v2or3(journal))
		csum_size = माप(काष्ठा jbd2_journal_block_tail);
	अगर (rcount > journal->j_blocksize - csum_size)
		वापस -EINVAL;
	max = rcount;

	अगर (jbd2_has_feature_64bit(journal))
		record_len = 8;

	जबतक (offset + record_len <= max) अणु
		अचिन्हित दीर्घ दीर्घ blocknr;
		पूर्णांक err;

		अगर (record_len == 4)
			blocknr = be32_to_cpu(* ((__be32 *) (bh->b_data+offset)));
		अन्यथा
			blocknr = be64_to_cpu(* ((__be64 *) (bh->b_data+offset)));
		offset += record_len;
		err = jbd2_journal_set_revoke(journal, blocknr, sequence);
		अगर (err)
			वापस err;
		++info->nr_revokes;
	पूर्ण
	वापस 0;
पूर्ण
