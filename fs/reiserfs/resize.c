<शैली गुरु>
/*
 * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README
 */

/*
 * Written by Alexander Zarochentcev.
 *
 * The kernel part of the (on-line) reiserfs resizer.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश "reiserfs.h"
#समावेश <linux/buffer_head.h>

पूर्णांक reiserfs_resize(काष्ठा super_block *s, अचिन्हित दीर्घ block_count_new)
अणु
	पूर्णांक err = 0;
	काष्ठा reiserfs_super_block *sb;
	काष्ठा reiserfs_biपंचांगap_info *biपंचांगap;
	काष्ठा reiserfs_biपंचांगap_info *info;
	काष्ठा reiserfs_biपंचांगap_info *old_biपंचांगap = SB_AP_BITMAP(s);
	काष्ठा buffer_head *bh;
	काष्ठा reiserfs_transaction_handle th;
	अचिन्हित पूर्णांक bmap_nr_new, bmap_nr;
	अचिन्हित पूर्णांक block_r_new, block_r;

	काष्ठा reiserfs_list_biपंचांगap *jb;
	काष्ठा reiserfs_list_biपंचांगap jbiपंचांगap[JOURNAL_NUM_BITMAPS];

	अचिन्हित दीर्घ पूर्णांक block_count, मुक्त_blocks;
	पूर्णांक i;
	पूर्णांक copy_size;
	पूर्णांक depth;

	sb = SB_DISK_SUPER_BLOCK(s);

	अगर (SB_BLOCK_COUNT(s) >= block_count_new) अणु
		prपूर्णांकk("can\'t shrink filesystem on-line\n");
		वापस -EINVAL;
	पूर्ण

	/* check the device size */
	depth = reiserfs_ग_लिखो_unlock_nested(s);
	bh = sb_bपढ़ो(s, block_count_new - 1);
	reiserfs_ग_लिखो_lock_nested(s, depth);
	अगर (!bh) अणु
		prपूर्णांकk("reiserfs_resize: can\'t read last block\n");
		वापस -EINVAL;
	पूर्ण
	bक्रमget(bh);

	/*
	 * old disk layout detection; those partitions can be mounted, but
	 * cannot be resized
	 */
	अगर (SB_BUFFER_WITH_SB(s)->b_blocknr * SB_BUFFER_WITH_SB(s)->b_size
	    != REISERFS_DISK_OFFSET_IN_BYTES) अणु
		prपूर्णांकk
		    ("reiserfs_resize: unable to resize a reiserfs without distributed bitmap (fs version < 3.5.12)\n");
		वापस -ENOTSUPP;
	पूर्ण

	/* count used bits in last biपंचांगap block */
	block_r = SB_BLOCK_COUNT(s) -
			(reiserfs_bmap_count(s) - 1) * s->s_blocksize * 8;

	/* count biपंचांगap blocks in new fs */
	bmap_nr_new = block_count_new / (s->s_blocksize * 8);
	block_r_new = block_count_new - bmap_nr_new * s->s_blocksize * 8;
	अगर (block_r_new)
		bmap_nr_new++;
	अन्यथा
		block_r_new = s->s_blocksize * 8;

	/* save old values */
	block_count = SB_BLOCK_COUNT(s);
	bmap_nr = reiserfs_bmap_count(s);

	/* resizing of reiserfs biपंचांगaps (journal and real), अगर needed */
	अगर (bmap_nr_new > bmap_nr) अणु
		/* पुनः_स्मृतिate journal biपंचांगaps */
		अगर (reiserfs_allocate_list_biपंचांगaps(s, jbiपंचांगap, bmap_nr_new) < 0) अणु
			prपूर्णांकk
			    ("reiserfs_resize: unable to allocate memory for journal bitmaps\n");
			वापस -ENOMEM;
		पूर्ण
		/*
		 * the new journal biपंचांगaps are zero filled, now we copy i
		 * the biपंचांगap node poपूर्णांकers from the old journal biपंचांगap
		 * काष्ठाs, and then transfer the new data काष्ठाures
		 * पूर्णांकo the journal काष्ठा.
		 *
		 * using the copy_size var below allows this code to work क्रम
		 * both shrinking and expanding the FS.
		 */
		copy_size = bmap_nr_new < bmap_nr ? bmap_nr_new : bmap_nr;
		copy_size =
		    copy_size * माप(काष्ठा reiserfs_list_biपंचांगap_node *);
		क्रम (i = 0; i < JOURNAL_NUM_BITMAPS; i++) अणु
			काष्ठा reiserfs_biपंचांगap_node **node_पंचांगp;
			jb = SB_JOURNAL(s)->j_list_biपंचांगap + i;
			स_नकल(jbiपंचांगap[i].biपंचांगaps, jb->biपंचांगaps, copy_size);

			/*
			 * just in हाल vमुक्त schedules on us, copy the new
			 * poपूर्णांकer पूर्णांकo the journal काष्ठा beक्रमe मुक्तing the
			 * old one
			 */
			node_पंचांगp = jb->biपंचांगaps;
			jb->biपंचांगaps = jbiपंचांगap[i].biपंचांगaps;
			vमुक्त(node_पंचांगp);
		पूर्ण

		/*
		 * allocate additional biपंचांगap blocks, पुनः_स्मृतिate
		 * array of biपंचांगap block poपूर्णांकers
		 */
		biपंचांगap =
		    vzalloc(array_size(bmap_nr_new,
				       माप(काष्ठा reiserfs_biपंचांगap_info)));
		अगर (!biपंचांगap) अणु
			/*
			 * Journal biपंचांगaps are still supersized, but the
			 * memory isn't leaked, so I guess it's ok
			 */
			prपूर्णांकk("reiserfs_resize: unable to allocate memory.\n");
			वापस -ENOMEM;
		पूर्ण
		क्रम (i = 0; i < bmap_nr; i++)
			biपंचांगap[i] = old_biपंचांगap[i];

		/*
		 * This करोesn't go through the journal, but it doesn't have to.
		 * The changes are still atomic: We're synced up when the
		 * journal transaction begins, and the new biपंचांगaps करोn't
		 * matter अगर the transaction fails.
		 */
		क्रम (i = bmap_nr; i < bmap_nr_new; i++) अणु
			पूर्णांक depth;
			/*
			 * करोn't use पढ़ो_biपंचांगap_block since it will cache
			 * the uninitialized biपंचांगap
			 */
			depth = reiserfs_ग_लिखो_unlock_nested(s);
			bh = sb_bपढ़ो(s, i * s->s_blocksize * 8);
			reiserfs_ग_लिखो_lock_nested(s, depth);
			अगर (!bh) अणु
				vमुक्त(biपंचांगap);
				वापस -EIO;
			पूर्ण
			स_रखो(bh->b_data, 0, sb_blocksize(sb));
			reiserfs_set_le_bit(0, bh->b_data);
			reiserfs_cache_biपंचांगap_metadata(s, bh, biपंचांगap + i);

			set_buffer_uptodate(bh);
			mark_buffer_dirty(bh);
			depth = reiserfs_ग_लिखो_unlock_nested(s);
			sync_dirty_buffer(bh);
			reiserfs_ग_लिखो_lock_nested(s, depth);
			/* update biपंचांगap_info stuff */
			biपंचांगap[i].मुक्त_count = sb_blocksize(sb) * 8 - 1;
			brअन्यथा(bh);
		पूर्ण
		/* मुक्त old biपंचांगap blocks array */
		SB_AP_BITMAP(s) = biपंचांगap;
		vमुक्त(old_biपंचांगap);
	पूर्ण

	/*
	 * begin transaction, अगर there was an error, it's fine. Yes, we have
	 * incorrect biपंचांगaps now, but none of it is ever going to touch the
	 * disk anyway.
	 */
	err = journal_begin(&th, s, 10);
	अगर (err)
		वापस err;

	/* Extend old last biपंचांगap block - new blocks have been made available */
	info = SB_AP_BITMAP(s) + bmap_nr - 1;
	bh = reiserfs_पढ़ो_biपंचांगap_block(s, bmap_nr - 1);
	अगर (!bh) अणु
		पूर्णांक jerr = journal_end(&th);
		अगर (jerr)
			वापस jerr;
		वापस -EIO;
	पूर्ण

	reiserfs_prepare_क्रम_journal(s, bh, 1);
	क्रम (i = block_r; i < s->s_blocksize * 8; i++)
		reiserfs_clear_le_bit(i, bh->b_data);
	info->मुक्त_count += s->s_blocksize * 8 - block_r;

	journal_mark_dirty(&th, bh);
	brअन्यथा(bh);

	/* Correct new last biपंचांगap block - It may not be full */
	info = SB_AP_BITMAP(s) + bmap_nr_new - 1;
	bh = reiserfs_पढ़ो_biपंचांगap_block(s, bmap_nr_new - 1);
	अगर (!bh) अणु
		पूर्णांक jerr = journal_end(&th);
		अगर (jerr)
			वापस jerr;
		वापस -EIO;
	पूर्ण

	reiserfs_prepare_क्रम_journal(s, bh, 1);
	क्रम (i = block_r_new; i < s->s_blocksize * 8; i++)
		reiserfs_set_le_bit(i, bh->b_data);
	journal_mark_dirty(&th, bh);
	brअन्यथा(bh);

	info->मुक्त_count -= s->s_blocksize * 8 - block_r_new;
	/* update super */
	reiserfs_prepare_क्रम_journal(s, SB_BUFFER_WITH_SB(s), 1);
	मुक्त_blocks = SB_FREE_BLOCKS(s);
	PUT_SB_FREE_BLOCKS(s,
			   मुक्त_blocks + (block_count_new - block_count -
					  (bmap_nr_new - bmap_nr)));
	PUT_SB_BLOCK_COUNT(s, block_count_new);
	PUT_SB_BMAP_NR(s, bmap_would_wrap(bmap_nr_new) ? : bmap_nr_new);

	journal_mark_dirty(&th, SB_BUFFER_WITH_SB(s));

	SB_JOURNAL(s)->j_must_रुको = 1;
	वापस journal_end(&th);
पूर्ण
