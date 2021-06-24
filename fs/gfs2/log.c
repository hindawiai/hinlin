<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2007 Red Hat, Inc.  All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/crc32.h>
#समावेश <linux/crc32c.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/list_sort.h>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "bmap.h"
#समावेश "glock.h"
#समावेश "log.h"
#समावेश "lops.h"
#समावेश "meta_io.h"
#समावेश "util.h"
#समावेश "dir.h"
#समावेश "trace_gfs2.h"
#समावेश "trans.h"

अटल व्योम gfs2_log_shutकरोwn(काष्ठा gfs2_sbd *sdp);

/**
 * gfs2_काष्ठा2blk - compute stuff
 * @sdp: the fileप्रणाली
 * @nकाष्ठा: the number of काष्ठाures
 *
 * Compute the number of log descriptor blocks needed to hold a certain number
 * of काष्ठाures of a certain size.
 *
 * Returns: the number of blocks needed (minimum is always 1)
 */

अचिन्हित पूर्णांक gfs2_काष्ठा2blk(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक nकाष्ठा)
अणु
	अचिन्हित पूर्णांक blks;
	अचिन्हित पूर्णांक first, second;

	/* The initial काष्ठा gfs2_log_descriptor block */
	blks = 1;
	first = sdp->sd_ldptrs;

	अगर (nकाष्ठा > first) अणु
		/* Subsequent काष्ठा gfs2_meta_header blocks */
		second = sdp->sd_inptrs;
		blks += DIV_ROUND_UP(nकाष्ठा - first, second);
	पूर्ण

	वापस blks;
पूर्ण

/**
 * gfs2_हटाओ_from_ail - Remove an entry from the ail lists, updating counters
 * @bd: The gfs2_bufdata to हटाओ
 *
 * The ail lock _must_ be held when calling this function
 *
 */

व्योम gfs2_हटाओ_from_ail(काष्ठा gfs2_bufdata *bd)
अणु
	bd->bd_tr = शून्य;
	list_del_init(&bd->bd_ail_st_list);
	list_del_init(&bd->bd_ail_gl_list);
	atomic_dec(&bd->bd_gl->gl_ail_count);
	brअन्यथा(bd->bd_bh);
पूर्ण

/**
 * gfs2_ail1_start_one - Start I/O on a transaction
 * @sdp: The superblock
 * @wbc: The ग_लिखोback control काष्ठाure
 * @tr: The transaction to start I/O on
 * @plug: The block plug currently active
 */

अटल पूर्णांक gfs2_ail1_start_one(काष्ठा gfs2_sbd *sdp,
			       काष्ठा ग_लिखोback_control *wbc,
			       काष्ठा gfs2_trans *tr, काष्ठा blk_plug *plug)
__releases(&sdp->sd_ail_lock)
__acquires(&sdp->sd_ail_lock)
अणु
	काष्ठा gfs2_glock *gl = शून्य;
	काष्ठा address_space *mapping;
	काष्ठा gfs2_bufdata *bd, *s;
	काष्ठा buffer_head *bh;
	पूर्णांक ret = 0;

	list_क्रम_each_entry_safe_reverse(bd, s, &tr->tr_ail1_list, bd_ail_st_list) अणु
		bh = bd->bd_bh;

		gfs2_निश्चित(sdp, bd->bd_tr == tr);

		अगर (!buffer_busy(bh)) अणु
			अगर (buffer_uptodate(bh)) अणु
				list_move(&bd->bd_ail_st_list,
					  &tr->tr_ail2_list);
				जारी;
			पूर्ण
			अगर (!cmpxchg(&sdp->sd_log_error, 0, -EIO)) अणु
				gfs2_io_error_bh(sdp, bh);
				gfs2_withdraw_delayed(sdp);
			पूर्ण
		पूर्ण

		अगर (gfs2_withdrawn(sdp)) अणु
			gfs2_हटाओ_from_ail(bd);
			जारी;
		पूर्ण
		अगर (!buffer_dirty(bh))
			जारी;
		अगर (gl == bd->bd_gl)
			जारी;
		gl = bd->bd_gl;
		list_move(&bd->bd_ail_st_list, &tr->tr_ail1_list);
		mapping = bh->b_page->mapping;
		अगर (!mapping)
			जारी;
		spin_unlock(&sdp->sd_ail_lock);
		ret = generic_ग_लिखोpages(mapping, wbc);
		अगर (need_resched()) अणु
			blk_finish_plug(plug);
			cond_resched();
			blk_start_plug(plug);
		पूर्ण
		spin_lock(&sdp->sd_ail_lock);
		अगर (ret == -ENODATA) /* अगर a jdata ग_लिखो पूर्णांकo a new hole */
			ret = 0; /* ignore it */
		अगर (ret || wbc->nr_to_ग_लिखो <= 0)
			अवरोध;
		वापस -EBUSY;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम dump_ail_list(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा gfs2_trans *tr;
	काष्ठा gfs2_bufdata *bd;
	काष्ठा buffer_head *bh;

	list_क्रम_each_entry_reverse(tr, &sdp->sd_ail1_list, tr_list) अणु
		list_क्रम_each_entry_reverse(bd, &tr->tr_ail1_list,
					    bd_ail_st_list) अणु
			bh = bd->bd_bh;
			fs_err(sdp, "bd %p: blk:0x%llx bh=%p ", bd,
			       (अचिन्हित दीर्घ दीर्घ)bd->bd_blkno, bh);
			अगर (!bh) अणु
				fs_err(sdp, "\n");
				जारी;
			पूर्ण
			fs_err(sdp, "0x%llx up2:%d dirt:%d lkd:%d req:%d "
			       "map:%d new:%d ar:%d aw:%d delay:%d "
			       "io err:%d unwritten:%d dfr:%d pin:%d esc:%d\n",
			       (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
			       buffer_uptodate(bh), buffer_dirty(bh),
			       buffer_locked(bh), buffer_req(bh),
			       buffer_mapped(bh), buffer_new(bh),
			       buffer_async_पढ़ो(bh), buffer_async_ग_लिखो(bh),
			       buffer_delay(bh), buffer_ग_लिखो_io_error(bh),
			       buffer_unwritten(bh),
			       buffer_defer_completion(bh),
			       buffer_pinned(bh), buffer_escaped(bh));
		पूर्ण
	पूर्ण
पूर्ण

/**
 * gfs2_ail1_flush - start ग_लिखोback of some ail1 entries 
 * @sdp: The super block
 * @wbc: The ग_लिखोback control काष्ठाure
 *
 * Writes back some ail1 entries, according to the limits in the
 * ग_लिखोback control काष्ठाure
 */

व्योम gfs2_ail1_flush(काष्ठा gfs2_sbd *sdp, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा list_head *head = &sdp->sd_ail1_list;
	काष्ठा gfs2_trans *tr;
	काष्ठा blk_plug plug;
	पूर्णांक ret;
	अचिन्हित दीर्घ flush_start = jअगरfies;

	trace_gfs2_ail_flush(sdp, wbc, 1);
	blk_start_plug(&plug);
	spin_lock(&sdp->sd_ail_lock);
restart:
	ret = 0;
	अगर (समय_after(jअगरfies, flush_start + (HZ * 600))) अणु
		fs_err(sdp, "Error: In %s for ten minutes! t=%d\n",
		       __func__, current->journal_info ? 1 : 0);
		dump_ail_list(sdp);
		जाओ out;
	पूर्ण
	list_क्रम_each_entry_reverse(tr, head, tr_list) अणु
		अगर (wbc->nr_to_ग_लिखो <= 0)
			अवरोध;
		ret = gfs2_ail1_start_one(sdp, wbc, tr, &plug);
		अगर (ret) अणु
			अगर (ret == -EBUSY)
				जाओ restart;
			अवरोध;
		पूर्ण
	पूर्ण
out:
	spin_unlock(&sdp->sd_ail_lock);
	blk_finish_plug(&plug);
	अगर (ret) अणु
		gfs2_lm(sdp, "gfs2_ail1_start_one (generic_writepages) "
			"returned: %d\n", ret);
		gfs2_withdraw(sdp);
	पूर्ण
	trace_gfs2_ail_flush(sdp, wbc, 0);
पूर्ण

/**
 * gfs2_ail1_start - start ग_लिखोback of all ail1 entries
 * @sdp: The superblock
 */

अटल व्योम gfs2_ail1_start(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा ग_लिखोback_control wbc = अणु
		.sync_mode = WB_SYNC_NONE,
		.nr_to_ग_लिखो = दीर्घ_उच्च,
		.range_start = 0,
		.range_end = Lदीर्घ_उच्च,
	पूर्ण;

	वापस gfs2_ail1_flush(sdp, &wbc);
पूर्ण

अटल व्योम gfs2_log_update_flush_tail(काष्ठा gfs2_sbd *sdp)
अणु
	अचिन्हित पूर्णांक new_flush_tail = sdp->sd_log_head;
	काष्ठा gfs2_trans *tr;

	अगर (!list_empty(&sdp->sd_ail1_list)) अणु
		tr = list_last_entry(&sdp->sd_ail1_list,
				     काष्ठा gfs2_trans, tr_list);
		new_flush_tail = tr->tr_first;
	पूर्ण
	sdp->sd_log_flush_tail = new_flush_tail;
पूर्ण

अटल व्योम gfs2_log_update_head(काष्ठा gfs2_sbd *sdp)
अणु
	अचिन्हित पूर्णांक new_head = sdp->sd_log_flush_head;

	अगर (sdp->sd_log_flush_tail == sdp->sd_log_head)
		sdp->sd_log_flush_tail = new_head;
	sdp->sd_log_head = new_head;
पूर्ण

/*
 * gfs2_ail_empty_tr - empty one of the ail lists of a transaction
 */

अटल व्योम gfs2_ail_empty_tr(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *tr,
			      काष्ठा list_head *head)
अणु
	काष्ठा gfs2_bufdata *bd;

	जबतक (!list_empty(head)) अणु
		bd = list_first_entry(head, काष्ठा gfs2_bufdata,
				      bd_ail_st_list);
		gfs2_निश्चित(sdp, bd->bd_tr == tr);
		gfs2_हटाओ_from_ail(bd);
	पूर्ण
पूर्ण

/**
 * gfs2_ail1_empty_one - Check whether or not a trans in the AIL has been synced
 * @sdp: the fileप्रणाली
 * @tr: the transaction
 * @max_revokes: If nonzero, issue revokes क्रम the bd items क्रम written buffers
 *
 * वापसs: the transaction's count of reमुख्यing active items
 */

अटल पूर्णांक gfs2_ail1_empty_one(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *tr,
				पूर्णांक *max_revokes)
अणु
	काष्ठा gfs2_bufdata *bd, *s;
	काष्ठा buffer_head *bh;
	पूर्णांक active_count = 0;

	list_क्रम_each_entry_safe_reverse(bd, s, &tr->tr_ail1_list,
					 bd_ail_st_list) अणु
		bh = bd->bd_bh;
		gfs2_निश्चित(sdp, bd->bd_tr == tr);
		/*
		 * If another process flagged an io error, e.g. writing to the
		 * journal, error all other bhs and move them off the ail1 to
		 * prevent a tight loop when unmount tries to flush ail1,
		 * regardless of whether they're still busy. If no outside
		 * errors were found and the buffer is busy, move to the next.
		 * If the ail buffer is not busy and caught an error, flag it
		 * क्रम others.
		 */
		अगर (!sdp->sd_log_error && buffer_busy(bh)) अणु
			active_count++;
			जारी;
		पूर्ण
		अगर (!buffer_uptodate(bh) &&
		    !cmpxchg(&sdp->sd_log_error, 0, -EIO)) अणु
			gfs2_io_error_bh(sdp, bh);
			gfs2_withdraw_delayed(sdp);
		पूर्ण
		/*
		 * If we have space क्रम revokes and the bd is no दीर्घer on any
		 * buf list, we can just add a revoke क्रम it immediately and
		 * aव्योम having to put it on the ail2 list, where it would need
		 * to be revoked later.
		 */
		अगर (*max_revokes && list_empty(&bd->bd_list)) अणु
			gfs2_add_revoke(sdp, bd);
			(*max_revokes)--;
			जारी;
		पूर्ण
		list_move(&bd->bd_ail_st_list, &tr->tr_ail2_list);
	पूर्ण
	वापस active_count;
पूर्ण

/**
 * gfs2_ail1_empty - Try to empty the ail1 lists
 * @sdp: The superblock
 * @max_revokes: If non-zero, add revokes where appropriate
 *
 * Tries to empty the ail1 lists, starting with the oldest first
 */

अटल पूर्णांक gfs2_ail1_empty(काष्ठा gfs2_sbd *sdp, पूर्णांक max_revokes)
अणु
	काष्ठा gfs2_trans *tr, *s;
	पूर्णांक oldest_tr = 1;
	पूर्णांक ret;

	spin_lock(&sdp->sd_ail_lock);
	list_क्रम_each_entry_safe_reverse(tr, s, &sdp->sd_ail1_list, tr_list) अणु
		अगर (!gfs2_ail1_empty_one(sdp, tr, &max_revokes) && oldest_tr)
			list_move(&tr->tr_list, &sdp->sd_ail2_list);
		अन्यथा
			oldest_tr = 0;
	पूर्ण
	gfs2_log_update_flush_tail(sdp);
	ret = list_empty(&sdp->sd_ail1_list);
	spin_unlock(&sdp->sd_ail_lock);

	अगर (test_bit(SDF_WITHDRAWING, &sdp->sd_flags)) अणु
		gfs2_lm(sdp, "fatal: I/O error(s)\n");
		gfs2_withdraw(sdp);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम gfs2_ail1_रुको(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा gfs2_trans *tr;
	काष्ठा gfs2_bufdata *bd;
	काष्ठा buffer_head *bh;

	spin_lock(&sdp->sd_ail_lock);
	list_क्रम_each_entry_reverse(tr, &sdp->sd_ail1_list, tr_list) अणु
		list_क्रम_each_entry(bd, &tr->tr_ail1_list, bd_ail_st_list) अणु
			bh = bd->bd_bh;
			अगर (!buffer_locked(bh))
				जारी;
			get_bh(bh);
			spin_unlock(&sdp->sd_ail_lock);
			रुको_on_buffer(bh);
			brअन्यथा(bh);
			वापस;
		पूर्ण
	पूर्ण
	spin_unlock(&sdp->sd_ail_lock);
पूर्ण

अटल व्योम __ail2_empty(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *tr)
अणु
	gfs2_ail_empty_tr(sdp, tr, &tr->tr_ail2_list);
	list_del(&tr->tr_list);
	gfs2_निश्चित_warn(sdp, list_empty(&tr->tr_ail1_list));
	gfs2_निश्चित_warn(sdp, list_empty(&tr->tr_ail2_list));
	gfs2_trans_मुक्त(sdp, tr);
पूर्ण

अटल व्योम ail2_empty(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक new_tail)
अणु
	काष्ठा list_head *ail2_list = &sdp->sd_ail2_list;
	अचिन्हित पूर्णांक old_tail = sdp->sd_log_tail;
	काष्ठा gfs2_trans *tr, *safe;

	spin_lock(&sdp->sd_ail_lock);
	अगर (old_tail <= new_tail) अणु
		list_क्रम_each_entry_safe(tr, safe, ail2_list, tr_list) अणु
			अगर (old_tail <= tr->tr_first && tr->tr_first < new_tail)
				__ail2_empty(sdp, tr);
		पूर्ण
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry_safe(tr, safe, ail2_list, tr_list) अणु
			अगर (old_tail <= tr->tr_first || tr->tr_first < new_tail)
				__ail2_empty(sdp, tr);
		पूर्ण
	पूर्ण
	spin_unlock(&sdp->sd_ail_lock);
पूर्ण

/**
 * gfs2_log_is_empty - Check अगर the log is empty
 * @sdp: The GFS2 superblock
 */

bool gfs2_log_is_empty(काष्ठा gfs2_sbd *sdp) अणु
	वापस atomic_पढ़ो(&sdp->sd_log_blks_मुक्त) == sdp->sd_jdesc->jd_blocks;
पूर्ण

अटल bool __gfs2_log_try_reserve_revokes(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक revokes)
अणु
	अचिन्हित पूर्णांक available;

	available = atomic_पढ़ो(&sdp->sd_log_revokes_available);
	जबतक (available >= revokes) अणु
		अगर (atomic_try_cmpxchg(&sdp->sd_log_revokes_available,
				       &available, available - revokes))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * gfs2_log_release_revokes - Release a given number of revokes
 * @sdp: The GFS2 superblock
 * @revokes: The number of revokes to release
 *
 * sdp->sd_log_flush_lock must be held.
 */
व्योम gfs2_log_release_revokes(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक revokes)
अणु
	अगर (revokes)
		atomic_add(revokes, &sdp->sd_log_revokes_available);
पूर्ण

/**
 * gfs2_log_release - Release a given number of log blocks
 * @sdp: The GFS2 superblock
 * @blks: The number of blocks
 *
 */

व्योम gfs2_log_release(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक blks)
अणु
	atomic_add(blks, &sdp->sd_log_blks_मुक्त);
	trace_gfs2_log_blocks(sdp, blks);
	gfs2_निश्चित_withdraw(sdp, atomic_पढ़ो(&sdp->sd_log_blks_मुक्त) <=
				  sdp->sd_jdesc->jd_blocks);
	अगर (atomic_पढ़ो(&sdp->sd_log_blks_needed))
		wake_up(&sdp->sd_log_रुकोq);
पूर्ण

/**
 * __gfs2_log_try_reserve - Try to make a log reservation
 * @sdp: The GFS2 superblock
 * @blks: The number of blocks to reserve
 * @taboo_blks: The number of blocks to leave मुक्त
 *
 * Try to करो the same as __gfs2_log_reserve(), but fail अगर no more log
 * space is immediately available.
 */
अटल bool __gfs2_log_try_reserve(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक blks,
				   अचिन्हित पूर्णांक taboo_blks)
अणु
	अचिन्हित wanted = blks + taboo_blks;
	अचिन्हित पूर्णांक मुक्त_blocks;

	मुक्त_blocks = atomic_पढ़ो(&sdp->sd_log_blks_मुक्त);
	जबतक (मुक्त_blocks >= wanted) अणु
		अगर (atomic_try_cmpxchg(&sdp->sd_log_blks_मुक्त, &मुक्त_blocks,
				       मुक्त_blocks - blks)) अणु
			trace_gfs2_log_blocks(sdp, -blks);
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

/**
 * __gfs2_log_reserve - Make a log reservation
 * @sdp: The GFS2 superblock
 * @blks: The number of blocks to reserve
 * @taboo_blks: The number of blocks to leave मुक्त
 *
 * @taboo_blks is set to 0 क्रम logd, and to GFS2_LOG_FLUSH_MIN_BLOCKS
 * क्रम all other processes.  This ensures that when the log is almost full,
 * logd will still be able to call gfs2_log_flush one more समय  without
 * blocking, which will advance the tail and make some more log space
 * available.
 *
 * We no दीर्घer flush the log here, instead we wake up logd to करो that
 * क्रम us. To aव्योम the thundering herd and to ensure that we deal fairly
 * with queued रुकोers, we use an exclusive रुको. This means that when we
 * get woken with enough journal space to get our reservation, we need to
 * wake the next रुकोer on the list.
 */

अटल व्योम __gfs2_log_reserve(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक blks,
			       अचिन्हित पूर्णांक taboo_blks)
अणु
	अचिन्हित wanted = blks + taboo_blks;
	अचिन्हित पूर्णांक मुक्त_blocks;

	atomic_add(blks, &sdp->sd_log_blks_needed);
	क्रम (;;) अणु
		अगर (current != sdp->sd_logd_process)
			wake_up(&sdp->sd_logd_रुकोq);
		io_रुको_event(sdp->sd_log_रुकोq,
			(मुक्त_blocks = atomic_पढ़ो(&sdp->sd_log_blks_मुक्त),
			 मुक्त_blocks >= wanted));
		करो अणु
			अगर (atomic_try_cmpxchg(&sdp->sd_log_blks_मुक्त,
					       &मुक्त_blocks,
					       मुक्त_blocks - blks))
				जाओ reserved;
		पूर्ण जबतक (मुक्त_blocks >= wanted);
	पूर्ण

reserved:
	trace_gfs2_log_blocks(sdp, -blks);
	अगर (atomic_sub_वापस(blks, &sdp->sd_log_blks_needed))
		wake_up(&sdp->sd_log_रुकोq);
पूर्ण

/**
 * gfs2_log_try_reserve - Try to make a log reservation
 * @sdp: The GFS2 superblock
 * @tr: The transaction
 * @extra_revokes: The number of additional revokes reserved (output)
 *
 * This is similar to gfs2_log_reserve, but sdp->sd_log_flush_lock must be
 * held क्रम correct revoke accounting.
 */

bool gfs2_log_try_reserve(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *tr,
			  अचिन्हित पूर्णांक *extra_revokes)
अणु
	अचिन्हित पूर्णांक blks = tr->tr_reserved;
	अचिन्हित पूर्णांक revokes = tr->tr_revokes;
	अचिन्हित पूर्णांक revoke_blks = 0;

	*extra_revokes = 0;
	अगर (revokes && !__gfs2_log_try_reserve_revokes(sdp, revokes)) अणु
		revoke_blks = DIV_ROUND_UP(revokes, sdp->sd_inptrs);
		*extra_revokes = revoke_blks * sdp->sd_inptrs - revokes;
		blks += revoke_blks;
	पूर्ण
	अगर (!blks)
		वापस true;
	अगर (__gfs2_log_try_reserve(sdp, blks, GFS2_LOG_FLUSH_MIN_BLOCKS))
		वापस true;
	अगर (!revoke_blks)
		gfs2_log_release_revokes(sdp, revokes);
	वापस false;
पूर्ण

/**
 * gfs2_log_reserve - Make a log reservation
 * @sdp: The GFS2 superblock
 * @tr: The transaction
 * @extra_revokes: The number of additional revokes reserved (output)
 *
 * sdp->sd_log_flush_lock must not be held.
 */

व्योम gfs2_log_reserve(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *tr,
		      अचिन्हित पूर्णांक *extra_revokes)
अणु
	अचिन्हित पूर्णांक blks = tr->tr_reserved;
	अचिन्हित पूर्णांक revokes = tr->tr_revokes;
	अचिन्हित पूर्णांक revoke_blks = 0;

	*extra_revokes = 0;
	अगर (revokes) अणु
		revoke_blks = DIV_ROUND_UP(revokes, sdp->sd_inptrs);
		*extra_revokes = revoke_blks * sdp->sd_inptrs - revokes;
		blks += revoke_blks;
	पूर्ण
	__gfs2_log_reserve(sdp, blks, GFS2_LOG_FLUSH_MIN_BLOCKS);
पूर्ण

/**
 * log_distance - Compute distance between two journal blocks
 * @sdp: The GFS2 superblock
 * @newer: The most recent journal block of the pair
 * @older: The older journal block of the pair
 *
 *   Compute the distance (in the journal direction) between two
 *   blocks in the journal
 *
 * Returns: the distance in blocks
 */

अटल अंतरभूत अचिन्हित पूर्णांक log_distance(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक newer,
					अचिन्हित पूर्णांक older)
अणु
	पूर्णांक dist;

	dist = newer - older;
	अगर (dist < 0)
		dist += sdp->sd_jdesc->jd_blocks;

	वापस dist;
पूर्ण

/**
 * calc_reserved - Calculate the number of blocks to keep reserved
 * @sdp: The GFS2 superblock
 *
 * This is complex.  We need to reserve room क्रम all our currently used
 * metadata blocks (e.g. normal file I/O rewriting file समय stamps) and
 * all our journaled data blocks क्रम journaled files (e.g. files in the
 * meta_fs like rindex, or files क्रम which chattr +j was करोne.)
 * If we करोn't reserve enough space, corruption will follow.
 *
 * We can have metadata blocks and jdata blocks in the same journal.  Each
 * type माला_लो its own log descriptor, क्रम which we need to reserve a block.
 * In fact, each type has the potential क्रम needing more than one log descriptor
 * in हालs where we have more blocks than will fit in a log descriptor.
 * Metadata journal entries take up half the space of journaled buffer entries.
 *
 * Also, we need to reserve blocks क्रम revoke journal entries and one क्रम an
 * overall header क्रम the lot.
 *
 * Returns: the number of blocks reserved
 */
अटल अचिन्हित पूर्णांक calc_reserved(काष्ठा gfs2_sbd *sdp)
अणु
	अचिन्हित पूर्णांक reserved = GFS2_LOG_FLUSH_MIN_BLOCKS;
	अचिन्हित पूर्णांक blocks;
	काष्ठा gfs2_trans *tr = sdp->sd_log_tr;

	अगर (tr) अणु
		blocks = tr->tr_num_buf_new - tr->tr_num_buf_rm;
		reserved += blocks + DIV_ROUND_UP(blocks, buf_limit(sdp));
		blocks = tr->tr_num_databuf_new - tr->tr_num_databuf_rm;
		reserved += blocks + DIV_ROUND_UP(blocks, databuf_limit(sdp));
	पूर्ण
	वापस reserved;
पूर्ण

अटल व्योम log_pull_tail(काष्ठा gfs2_sbd *sdp)
अणु
	अचिन्हित पूर्णांक new_tail = sdp->sd_log_flush_tail;
	अचिन्हित पूर्णांक dist;

	अगर (new_tail == sdp->sd_log_tail)
		वापस;
	dist = log_distance(sdp, new_tail, sdp->sd_log_tail);
	ail2_empty(sdp, new_tail);
	gfs2_log_release(sdp, dist);
	sdp->sd_log_tail = new_tail;
पूर्ण


व्योम log_flush_रुको(काष्ठा gfs2_sbd *sdp)
अणु
	DEFINE_WAIT(रुको);

	अगर (atomic_पढ़ो(&sdp->sd_log_in_flight)) अणु
		करो अणु
			prepare_to_रुको(&sdp->sd_log_flush_रुको, &रुको,
					TASK_UNINTERRUPTIBLE);
			अगर (atomic_पढ़ो(&sdp->sd_log_in_flight))
				io_schedule();
		पूर्ण जबतक(atomic_पढ़ो(&sdp->sd_log_in_flight));
		finish_रुको(&sdp->sd_log_flush_रुको, &रुको);
	पूर्ण
पूर्ण

अटल पूर्णांक ip_cmp(व्योम *priv, स्थिर काष्ठा list_head *a, स्थिर काष्ठा list_head *b)
अणु
	काष्ठा gfs2_inode *ipa, *ipb;

	ipa = list_entry(a, काष्ठा gfs2_inode, i_ordered);
	ipb = list_entry(b, काष्ठा gfs2_inode, i_ordered);

	अगर (ipa->i_no_addr < ipb->i_no_addr)
		वापस -1;
	अगर (ipa->i_no_addr > ipb->i_no_addr)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम __ordered_del_inode(काष्ठा gfs2_inode *ip)
अणु
	अगर (!list_empty(&ip->i_ordered))
		list_del_init(&ip->i_ordered);
पूर्ण

अटल व्योम gfs2_ordered_ग_लिखो(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा gfs2_inode *ip;
	LIST_HEAD(written);

	spin_lock(&sdp->sd_ordered_lock);
	list_sort(शून्य, &sdp->sd_log_ordered, &ip_cmp);
	जबतक (!list_empty(&sdp->sd_log_ordered)) अणु
		ip = list_first_entry(&sdp->sd_log_ordered, काष्ठा gfs2_inode, i_ordered);
		अगर (ip->i_inode.i_mapping->nrpages == 0) अणु
			__ordered_del_inode(ip);
			जारी;
		पूर्ण
		list_move(&ip->i_ordered, &written);
		spin_unlock(&sdp->sd_ordered_lock);
		filemap_fdataग_लिखो(ip->i_inode.i_mapping);
		spin_lock(&sdp->sd_ordered_lock);
	पूर्ण
	list_splice(&written, &sdp->sd_log_ordered);
	spin_unlock(&sdp->sd_ordered_lock);
पूर्ण

अटल व्योम gfs2_ordered_रुको(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा gfs2_inode *ip;

	spin_lock(&sdp->sd_ordered_lock);
	जबतक (!list_empty(&sdp->sd_log_ordered)) अणु
		ip = list_first_entry(&sdp->sd_log_ordered, काष्ठा gfs2_inode, i_ordered);
		__ordered_del_inode(ip);
		अगर (ip->i_inode.i_mapping->nrpages == 0)
			जारी;
		spin_unlock(&sdp->sd_ordered_lock);
		filemap_fdataरुको(ip->i_inode.i_mapping);
		spin_lock(&sdp->sd_ordered_lock);
	पूर्ण
	spin_unlock(&sdp->sd_ordered_lock);
पूर्ण

व्योम gfs2_ordered_del_inode(काष्ठा gfs2_inode *ip)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);

	spin_lock(&sdp->sd_ordered_lock);
	__ordered_del_inode(ip);
	spin_unlock(&sdp->sd_ordered_lock);
पूर्ण

व्योम gfs2_add_revoke(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_bufdata *bd)
अणु
	काष्ठा buffer_head *bh = bd->bd_bh;
	काष्ठा gfs2_glock *gl = bd->bd_gl;

	sdp->sd_log_num_revoke++;
	अगर (atomic_inc_वापस(&gl->gl_revokes) == 1)
		gfs2_glock_hold(gl);
	bh->b_निजी = शून्य;
	bd->bd_blkno = bh->b_blocknr;
	gfs2_हटाओ_from_ail(bd); /* drops ref on bh */
	bd->bd_bh = शून्य;
	set_bit(GLF_LFLUSH, &gl->gl_flags);
	list_add(&bd->bd_list, &sdp->sd_log_revokes);
पूर्ण

व्योम gfs2_glock_हटाओ_revoke(काष्ठा gfs2_glock *gl)
अणु
	अगर (atomic_dec_वापस(&gl->gl_revokes) == 0) अणु
		clear_bit(GLF_LFLUSH, &gl->gl_flags);
		gfs2_glock_queue_put(gl);
	पूर्ण
पूर्ण

/**
 * gfs2_flush_revokes - Add as many revokes to the प्रणाली transaction as we can
 * @sdp: The GFS2 superblock
 *
 * Our usual strategy is to defer writing revokes as much as we can in the hope
 * that we'll eventually overग_लिखो the journal, which will make those revokes
 * go away.  This changes when we flush the log: at that poपूर्णांक, there will
 * likely be some left-over space in the last revoke block of that transaction.
 * We can fill that space with additional revokes क्रम blocks that have alपढ़ोy
 * been written back.  This will basically come at no cost now, and will save
 * us from having to keep track of those blocks on the AIL2 list later.
 */
व्योम gfs2_flush_revokes(काष्ठा gfs2_sbd *sdp)
अणु
	/* number of revokes we still have room क्रम */
	अचिन्हित पूर्णांक max_revokes = atomic_पढ़ो(&sdp->sd_log_revokes_available);

	gfs2_log_lock(sdp);
	gfs2_ail1_empty(sdp, max_revokes);
	gfs2_log_unlock(sdp);
पूर्ण

/**
 * gfs2_ग_लिखो_log_header - Write a journal log header buffer at lblock
 * @sdp: The GFS2 superblock
 * @jd: journal descriptor of the journal to which we are writing
 * @seq: sequence number
 * @tail: tail of the log
 * @lblock: value क्रम lh_blkno (block number relative to start of journal)
 * @flags: log header flags GFS2_LOG_HEAD_*
 * @op_flags: flags to pass to the bio
 *
 * Returns: the initialized log buffer descriptor
 */

व्योम gfs2_ग_लिखो_log_header(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_jdesc *jd,
			   u64 seq, u32 tail, u32 lblock, u32 flags,
			   पूर्णांक op_flags)
अणु
	काष्ठा gfs2_log_header *lh;
	u32 hash, crc;
	काष्ठा page *page;
	काष्ठा gfs2_statfs_change_host *l_sc = &sdp->sd_statfs_local;
	काष्ठा बारpec64 tv;
	काष्ठा super_block *sb = sdp->sd_vfs;
	u64 dblock;

	अगर (gfs2_withdrawn(sdp))
		वापस;

	page = mempool_alloc(gfs2_page_pool, GFP_NOIO);
	lh = page_address(page);
	clear_page(lh);

	lh->lh_header.mh_magic = cpu_to_be32(GFS2_MAGIC);
	lh->lh_header.mh_type = cpu_to_be32(GFS2_METATYPE_LH);
	lh->lh_header.__pad0 = cpu_to_be64(0);
	lh->lh_header.mh_क्रमmat = cpu_to_be32(GFS2_FORMAT_LH);
	lh->lh_header.mh_jid = cpu_to_be32(sdp->sd_jdesc->jd_jid);
	lh->lh_sequence = cpu_to_be64(seq);
	lh->lh_flags = cpu_to_be32(flags);
	lh->lh_tail = cpu_to_be32(tail);
	lh->lh_blkno = cpu_to_be32(lblock);
	hash = ~crc32(~0, lh, LH_V1_SIZE);
	lh->lh_hash = cpu_to_be32(hash);

	kसमय_get_coarse_real_ts64(&tv);
	lh->lh_nsec = cpu_to_be32(tv.tv_nsec);
	lh->lh_sec = cpu_to_be64(tv.tv_sec);
	अगर (!list_empty(&jd->extent_list))
		dblock = gfs2_log_bmap(jd, lblock);
	अन्यथा अणु
		अचिन्हित पूर्णांक extlen;
		पूर्णांक ret;

		extlen = 1;
		ret = gfs2_get_extent(jd->jd_inode, lblock, &dblock, &extlen);
		अगर (gfs2_निश्चित_withdraw(sdp, ret == 0))
			वापस;
	पूर्ण
	lh->lh_addr = cpu_to_be64(dblock);
	lh->lh_jinode = cpu_to_be64(GFS2_I(jd->jd_inode)->i_no_addr);

	/* We may only ग_लिखो local statfs, quota, etc., when writing to our
	   own journal. The values are left 0 when recovering a journal
	   dअगरferent from our own. */
	अगर (!(flags & GFS2_LOG_HEAD_RECOVERY)) अणु
		lh->lh_statfs_addr =
			cpu_to_be64(GFS2_I(sdp->sd_sc_inode)->i_no_addr);
		lh->lh_quota_addr =
			cpu_to_be64(GFS2_I(sdp->sd_qc_inode)->i_no_addr);

		spin_lock(&sdp->sd_statfs_spin);
		lh->lh_local_total = cpu_to_be64(l_sc->sc_total);
		lh->lh_local_मुक्त = cpu_to_be64(l_sc->sc_मुक्त);
		lh->lh_local_dinodes = cpu_to_be64(l_sc->sc_dinodes);
		spin_unlock(&sdp->sd_statfs_spin);
	पूर्ण

	BUILD_BUG_ON(दुरत्व(काष्ठा gfs2_log_header, lh_crc) != LH_V1_SIZE);

	crc = crc32c(~0, (व्योम *)lh + LH_V1_SIZE + 4,
		     sb->s_blocksize - LH_V1_SIZE - 4);
	lh->lh_crc = cpu_to_be32(crc);

	gfs2_log_ग_लिखो(sdp, jd, page, sb->s_blocksize, 0, dblock);
	gfs2_log_submit_bio(&jd->jd_log_bio, REQ_OP_WRITE | op_flags);
पूर्ण

/**
 * log_ग_लिखो_header - Get and initialize a journal header buffer
 * @sdp: The GFS2 superblock
 * @flags: The log header flags, including log header origin
 *
 * Returns: the initialized log buffer descriptor
 */

अटल व्योम log_ग_लिखो_header(काष्ठा gfs2_sbd *sdp, u32 flags)
अणु
	पूर्णांक op_flags = REQ_PREFLUSH | REQ_FUA | REQ_META | REQ_SYNC;
	क्रमागत gfs2_मुक्तze_state state = atomic_पढ़ो(&sdp->sd_मुक्तze_state);

	gfs2_निश्चित_withdraw(sdp, (state != SFS_FROZEN));

	अगर (test_bit(SDF_NOBARRIERS, &sdp->sd_flags)) अणु
		gfs2_ordered_रुको(sdp);
		log_flush_रुको(sdp);
		op_flags = REQ_SYNC | REQ_META | REQ_PRIO;
	पूर्ण
	sdp->sd_log_idle = (sdp->sd_log_flush_tail == sdp->sd_log_flush_head);
	gfs2_ग_लिखो_log_header(sdp, sdp->sd_jdesc, sdp->sd_log_sequence++,
			      sdp->sd_log_flush_tail, sdp->sd_log_flush_head,
			      flags, op_flags);
	gfs2_log_incr_head(sdp);
	log_flush_रुको(sdp);
	log_pull_tail(sdp);
	gfs2_log_update_head(sdp);
पूर्ण

/**
 * gfs2_ail_drain - drain the ail lists after a withdraw
 * @sdp: Poपूर्णांकer to GFS2 superblock
 */
व्योम gfs2_ail_drain(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा gfs2_trans *tr;

	spin_lock(&sdp->sd_ail_lock);
	/*
	 * For transactions on the sd_ail1_list we need to drain both the
	 * ail1 and ail2 lists. That's because function gfs2_ail1_start_one
	 * (temporarily) moves items from its tr_ail1 list to tr_ail2 list
	 * beक्रमe revokes are sent क्रम that block. Items on the sd_ail2_list
	 * should have alपढ़ोy gotten beyond that poपूर्णांक, so no need.
	 */
	जबतक (!list_empty(&sdp->sd_ail1_list)) अणु
		tr = list_first_entry(&sdp->sd_ail1_list, काष्ठा gfs2_trans,
				      tr_list);
		gfs2_ail_empty_tr(sdp, tr, &tr->tr_ail1_list);
		gfs2_ail_empty_tr(sdp, tr, &tr->tr_ail2_list);
		list_del(&tr->tr_list);
		gfs2_trans_मुक्त(sdp, tr);
	पूर्ण
	जबतक (!list_empty(&sdp->sd_ail2_list)) अणु
		tr = list_first_entry(&sdp->sd_ail2_list, काष्ठा gfs2_trans,
				      tr_list);
		gfs2_ail_empty_tr(sdp, tr, &tr->tr_ail2_list);
		list_del(&tr->tr_list);
		gfs2_trans_मुक्त(sdp, tr);
	पूर्ण
	gfs2_drain_revokes(sdp);
	spin_unlock(&sdp->sd_ail_lock);
पूर्ण

/**
 * empty_ail1_list - try to start IO and empty the ail1 list
 * @sdp: Poपूर्णांकer to GFS2 superblock
 */
अटल व्योम empty_ail1_list(काष्ठा gfs2_sbd *sdp)
अणु
	अचिन्हित दीर्घ start = jअगरfies;

	क्रम (;;) अणु
		अगर (समय_after(jअगरfies, start + (HZ * 600))) अणु
			fs_err(sdp, "Error: In %s for 10 minutes! t=%d\n",
			       __func__, current->journal_info ? 1 : 0);
			dump_ail_list(sdp);
			वापस;
		पूर्ण
		gfs2_ail1_start(sdp);
		gfs2_ail1_रुको(sdp);
		अगर (gfs2_ail1_empty(sdp, 0))
			वापस;
	पूर्ण
पूर्ण

/**
 * trans_drain - drain the buf and databuf queue क्रम a failed transaction
 * @tr: the transaction to drain
 *
 * When this is called, we're taking an error निकास क्रम a log ग_लिखो that failed
 * but since we bypassed the after_commit functions, we need to हटाओ the
 * items from the buf and databuf queue.
 */
अटल व्योम trans_drain(काष्ठा gfs2_trans *tr)
अणु
	काष्ठा gfs2_bufdata *bd;
	काष्ठा list_head *head;

	अगर (!tr)
		वापस;

	head = &tr->tr_buf;
	जबतक (!list_empty(head)) अणु
		bd = list_first_entry(head, काष्ठा gfs2_bufdata, bd_list);
		list_del_init(&bd->bd_list);
		अगर (!list_empty(&bd->bd_ail_st_list))
			gfs2_हटाओ_from_ail(bd);
		kmem_cache_मुक्त(gfs2_bufdata_cachep, bd);
	पूर्ण
	head = &tr->tr_databuf;
	जबतक (!list_empty(head)) अणु
		bd = list_first_entry(head, काष्ठा gfs2_bufdata, bd_list);
		list_del_init(&bd->bd_list);
		अगर (!list_empty(&bd->bd_ail_st_list))
			gfs2_हटाओ_from_ail(bd);
		kmem_cache_मुक्त(gfs2_bufdata_cachep, bd);
	पूर्ण
पूर्ण

/**
 * gfs2_log_flush - flush incore transaction(s)
 * @sdp: The fileप्रणाली
 * @gl: The glock काष्ठाure to flush.  If शून्य, flush the whole incore log
 * @flags: The log header flags: GFS2_LOG_HEAD_FLUSH_* and debug flags
 *
 */

व्योम gfs2_log_flush(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_glock *gl, u32 flags)
अणु
	काष्ठा gfs2_trans *tr = शून्य;
	अचिन्हित पूर्णांक reserved_blocks = 0, used_blocks = 0;
	क्रमागत gfs2_मुक्तze_state state = atomic_पढ़ो(&sdp->sd_मुक्तze_state);
	अचिन्हित पूर्णांक first_log_head;
	अचिन्हित पूर्णांक reserved_revokes = 0;

	करोwn_ग_लिखो(&sdp->sd_log_flush_lock);
	trace_gfs2_log_flush(sdp, 1, flags);

repeat:
	/*
	 * Do this check जबतक holding the log_flush_lock to prevent new
	 * buffers from being added to the ail via gfs2_pin()
	 */
	अगर (gfs2_withdrawn(sdp) || !test_bit(SDF_JOURNAL_LIVE, &sdp->sd_flags))
		जाओ out;

	/* Log might have been flushed जबतक we रुकोed क्रम the flush lock */
	अगर (gl && !test_bit(GLF_LFLUSH, &gl->gl_flags))
		जाओ out;

	first_log_head = sdp->sd_log_head;
	sdp->sd_log_flush_head = first_log_head;

	tr = sdp->sd_log_tr;
	अगर (tr || sdp->sd_log_num_revoke) अणु
		अगर (reserved_blocks)
			gfs2_log_release(sdp, reserved_blocks);
		reserved_blocks = sdp->sd_log_blks_reserved;
		reserved_revokes = sdp->sd_log_num_revoke;
		अगर (tr) अणु
			sdp->sd_log_tr = शून्य;
			tr->tr_first = first_log_head;
			अगर (unlikely (state == SFS_FROZEN)) अणु
				अगर (gfs2_निश्चित_withdraw_delayed(sdp,
				       !tr->tr_num_buf_new && !tr->tr_num_databuf_new))
					जाओ out_withdraw;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (!reserved_blocks) अणु
		अचिन्हित पूर्णांक taboo_blocks = GFS2_LOG_FLUSH_MIN_BLOCKS;

		reserved_blocks = GFS2_LOG_FLUSH_MIN_BLOCKS;
		अगर (current == sdp->sd_logd_process)
			taboo_blocks = 0;

		अगर (!__gfs2_log_try_reserve(sdp, reserved_blocks, taboo_blocks)) अणु
			up_ग_लिखो(&sdp->sd_log_flush_lock);
			__gfs2_log_reserve(sdp, reserved_blocks, taboo_blocks);
			करोwn_ग_लिखो(&sdp->sd_log_flush_lock);
			जाओ repeat;
		पूर्ण
		BUG_ON(sdp->sd_log_num_revoke);
	पूर्ण

	अगर (flags & GFS2_LOG_HEAD_FLUSH_SHUTDOWN)
		clear_bit(SDF_JOURNAL_LIVE, &sdp->sd_flags);

	अगर (unlikely(state == SFS_FROZEN))
		अगर (gfs2_निश्चित_withdraw_delayed(sdp, !reserved_revokes))
			जाओ out_withdraw;

	gfs2_ordered_ग_लिखो(sdp);
	अगर (gfs2_withdrawn(sdp))
		जाओ out_withdraw;
	lops_beक्रमe_commit(sdp, tr);
	अगर (gfs2_withdrawn(sdp))
		जाओ out_withdraw;
	gfs2_log_submit_bio(&sdp->sd_jdesc->jd_log_bio, REQ_OP_WRITE);
	अगर (gfs2_withdrawn(sdp))
		जाओ out_withdraw;

	अगर (sdp->sd_log_head != sdp->sd_log_flush_head) अणु
		log_ग_लिखो_header(sdp, flags);
	पूर्ण अन्यथा अगर (sdp->sd_log_tail != sdp->sd_log_flush_tail && !sdp->sd_log_idle) अणु
		log_ग_लिखो_header(sdp, flags);
	पूर्ण
	अगर (gfs2_withdrawn(sdp))
		जाओ out_withdraw;
	lops_after_commit(sdp, tr);

	gfs2_log_lock(sdp);
	sdp->sd_log_blks_reserved = 0;

	spin_lock(&sdp->sd_ail_lock);
	अगर (tr && !list_empty(&tr->tr_ail1_list)) अणु
		list_add(&tr->tr_list, &sdp->sd_ail1_list);
		tr = शून्य;
	पूर्ण
	spin_unlock(&sdp->sd_ail_lock);
	gfs2_log_unlock(sdp);

	अगर (!(flags & GFS2_LOG_HEAD_FLUSH_NORMAL)) अणु
		अगर (!sdp->sd_log_idle) अणु
			empty_ail1_list(sdp);
			अगर (gfs2_withdrawn(sdp))
				जाओ out_withdraw;
			log_ग_लिखो_header(sdp, flags);
		पूर्ण
		अगर (flags & (GFS2_LOG_HEAD_FLUSH_SHUTDOWN |
			     GFS2_LOG_HEAD_FLUSH_FREEZE))
			gfs2_log_shutकरोwn(sdp);
		अगर (flags & GFS2_LOG_HEAD_FLUSH_FREEZE)
			atomic_set(&sdp->sd_मुक्तze_state, SFS_FROZEN);
	पूर्ण

out_end:
	used_blocks = log_distance(sdp, sdp->sd_log_flush_head, first_log_head);
	reserved_revokes += atomic_पढ़ो(&sdp->sd_log_revokes_available);
	atomic_set(&sdp->sd_log_revokes_available, sdp->sd_ldptrs);
	gfs2_निश्चित_withdraw(sdp, reserved_revokes % sdp->sd_inptrs == sdp->sd_ldptrs);
	अगर (reserved_revokes > sdp->sd_ldptrs)
		reserved_blocks += (reserved_revokes - sdp->sd_ldptrs) / sdp->sd_inptrs;
out:
	अगर (used_blocks != reserved_blocks) अणु
		gfs2_निश्चित_withdraw_delayed(sdp, used_blocks < reserved_blocks);
		gfs2_log_release(sdp, reserved_blocks - used_blocks);
	पूर्ण
	up_ग_लिखो(&sdp->sd_log_flush_lock);
	gfs2_trans_मुक्त(sdp, tr);
	अगर (gfs2_withdrawing(sdp))
		gfs2_withdraw(sdp);
	trace_gfs2_log_flush(sdp, 0, flags);
	वापस;

out_withdraw:
	trans_drain(tr);
	/**
	 * If the tr_list is empty, we're withdrawing during a log
	 * flush that tarमाला_लो a transaction, but the transaction was
	 * never queued onto any of the ail lists. Here we add it to
	 * ail1 just so that ail_drain() will find and मुक्त it.
	 */
	spin_lock(&sdp->sd_ail_lock);
	अगर (tr && list_empty(&tr->tr_list))
		list_add(&tr->tr_list, &sdp->sd_ail1_list);
	spin_unlock(&sdp->sd_ail_lock);
	tr = शून्य;
	जाओ out_end;
पूर्ण

/**
 * gfs2_merge_trans - Merge a new transaction पूर्णांकo a cached transaction
 * @sdp: the fileप्रणाली
 * @new: New transaction to be merged
 */

अटल व्योम gfs2_merge_trans(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *new)
अणु
	काष्ठा gfs2_trans *old = sdp->sd_log_tr;

	WARN_ON_ONCE(!test_bit(TR_ATTACHED, &old->tr_flags));

	old->tr_num_buf_new	+= new->tr_num_buf_new;
	old->tr_num_databuf_new	+= new->tr_num_databuf_new;
	old->tr_num_buf_rm	+= new->tr_num_buf_rm;
	old->tr_num_databuf_rm	+= new->tr_num_databuf_rm;
	old->tr_revokes		+= new->tr_revokes;
	old->tr_num_revoke	+= new->tr_num_revoke;

	list_splice_tail_init(&new->tr_databuf, &old->tr_databuf);
	list_splice_tail_init(&new->tr_buf, &old->tr_buf);

	spin_lock(&sdp->sd_ail_lock);
	list_splice_tail_init(&new->tr_ail1_list, &old->tr_ail1_list);
	list_splice_tail_init(&new->tr_ail2_list, &old->tr_ail2_list);
	spin_unlock(&sdp->sd_ail_lock);
पूर्ण

अटल व्योम log_refund(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *tr)
अणु
	अचिन्हित पूर्णांक reserved;
	अचिन्हित पूर्णांक unused;
	अचिन्हित पूर्णांक maxres;

	gfs2_log_lock(sdp);

	अगर (sdp->sd_log_tr) अणु
		gfs2_merge_trans(sdp, tr);
	पूर्ण अन्यथा अगर (tr->tr_num_buf_new || tr->tr_num_databuf_new) अणु
		gfs2_निश्चित_withdraw(sdp, !test_bit(TR_ONSTACK, &tr->tr_flags));
		sdp->sd_log_tr = tr;
		set_bit(TR_ATTACHED, &tr->tr_flags);
	पूर्ण

	reserved = calc_reserved(sdp);
	maxres = sdp->sd_log_blks_reserved + tr->tr_reserved;
	gfs2_निश्चित_withdraw(sdp, maxres >= reserved);
	unused = maxres - reserved;
	अगर (unused)
		gfs2_log_release(sdp, unused);
	sdp->sd_log_blks_reserved = reserved;

	gfs2_log_unlock(sdp);
पूर्ण

/**
 * gfs2_log_commit - Commit a transaction to the log
 * @sdp: the fileप्रणाली
 * @tr: the transaction
 *
 * We wake up gfs2_logd अगर the number of pinned blocks exceed thresh1
 * or the total number of used blocks (pinned blocks plus AIL blocks)
 * is greater than thresh2.
 *
 * At mount समय thresh1 is 2/5ths of journal size, thresh2 is 4/5ths of
 * journal size.
 *
 * Returns: त्रुटि_सं
 */

व्योम gfs2_log_commit(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *tr)
अणु
	log_refund(sdp, tr);

	अगर (atomic_पढ़ो(&sdp->sd_log_pinned) > atomic_पढ़ो(&sdp->sd_log_thresh1) ||
	    ((sdp->sd_jdesc->jd_blocks - atomic_पढ़ो(&sdp->sd_log_blks_मुक्त)) >
	    atomic_पढ़ो(&sdp->sd_log_thresh2)))
		wake_up(&sdp->sd_logd_रुकोq);
पूर्ण

/**
 * gfs2_log_shutकरोwn - ग_लिखो a shutकरोwn header पूर्णांकo a journal
 * @sdp: the fileप्रणाली
 *
 */

अटल व्योम gfs2_log_shutकरोwn(काष्ठा gfs2_sbd *sdp)
अणु
	gfs2_निश्चित_withdraw(sdp, !sdp->sd_log_blks_reserved);
	gfs2_निश्चित_withdraw(sdp, !sdp->sd_log_num_revoke);
	gfs2_निश्चित_withdraw(sdp, list_empty(&sdp->sd_ail1_list));

	log_ग_लिखो_header(sdp, GFS2_LOG_HEAD_UNMOUNT | GFS2_LFC_SHUTDOWN);
	log_pull_tail(sdp);

	gfs2_निश्चित_warn(sdp, sdp->sd_log_head == sdp->sd_log_tail);
	gfs2_निश्चित_warn(sdp, list_empty(&sdp->sd_ail2_list));
पूर्ण

अटल अंतरभूत पूर्णांक gfs2_jrnl_flush_reqd(काष्ठा gfs2_sbd *sdp)
अणु
	वापस (atomic_पढ़ो(&sdp->sd_log_pinned) +
		atomic_पढ़ो(&sdp->sd_log_blks_needed) >=
		atomic_पढ़ो(&sdp->sd_log_thresh1));
पूर्ण

अटल अंतरभूत पूर्णांक gfs2_ail_flush_reqd(काष्ठा gfs2_sbd *sdp)
अणु
	अचिन्हित पूर्णांक used_blocks = sdp->sd_jdesc->jd_blocks - atomic_पढ़ो(&sdp->sd_log_blks_मुक्त);

	अगर (test_and_clear_bit(SDF_FORCE_AIL_FLUSH, &sdp->sd_flags))
		वापस 1;

	वापस used_blocks + atomic_पढ़ो(&sdp->sd_log_blks_needed) >=
		atomic_पढ़ो(&sdp->sd_log_thresh2);
पूर्ण

/**
 * gfs2_logd - Update log tail as Active Items get flushed to in-place blocks
 * @data: Poपूर्णांकer to GFS2 superblock
 *
 * Also, periodically check to make sure that we're using the most recent
 * journal index.
 */

पूर्णांक gfs2_logd(व्योम *data)
अणु
	काष्ठा gfs2_sbd *sdp = data;
	अचिन्हित दीर्घ t = 1;
	DEFINE_WAIT(रुको);

	जबतक (!kthपढ़ो_should_stop()) अणु

		अगर (gfs2_withdrawn(sdp)) अणु
			msleep_पूर्णांकerruptible(HZ);
			जारी;
		पूर्ण
		/* Check क्रम errors writing to the journal */
		अगर (sdp->sd_log_error) अणु
			gfs2_lm(sdp,
				"GFS2: fsid=%s: error %d: "
				"withdrawing the file system to "
				"prevent further damage.\n",
				sdp->sd_fsname, sdp->sd_log_error);
			gfs2_withdraw(sdp);
			जारी;
		पूर्ण

		अगर (gfs2_jrnl_flush_reqd(sdp) || t == 0) अणु
			gfs2_ail1_empty(sdp, 0);
			gfs2_log_flush(sdp, शून्य, GFS2_LOG_HEAD_FLUSH_NORMAL |
						  GFS2_LFC_LOGD_JFLUSH_REQD);
		पूर्ण

		अगर (gfs2_ail_flush_reqd(sdp)) अणु
			gfs2_ail1_start(sdp);
			gfs2_ail1_रुको(sdp);
			gfs2_ail1_empty(sdp, 0);
			gfs2_log_flush(sdp, शून्य, GFS2_LOG_HEAD_FLUSH_NORMAL |
						  GFS2_LFC_LOGD_AIL_FLUSH_REQD);
		पूर्ण

		t = gfs2_tune_get(sdp, gt_logd_secs) * HZ;

		try_to_मुक्तze();

		करो अणु
			prepare_to_रुको(&sdp->sd_logd_रुकोq, &रुको,
					TASK_INTERRUPTIBLE);
			अगर (!gfs2_ail_flush_reqd(sdp) &&
			    !gfs2_jrnl_flush_reqd(sdp) &&
			    !kthपढ़ो_should_stop())
				t = schedule_समयout(t);
		पूर्ण जबतक(t && !gfs2_ail_flush_reqd(sdp) &&
			!gfs2_jrnl_flush_reqd(sdp) &&
			!kthपढ़ो_should_stop());
		finish_रुको(&sdp->sd_logd_रुकोq, &रुको);
	पूर्ण

	वापस 0;
पूर्ण

