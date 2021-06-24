<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/mempool.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/bपन.स>
#समावेश <linux/fs.h>
#समावेश <linux/list_sort.h>
#समावेश <linux/blkdev.h>

#समावेश "bmap.h"
#समावेश "dir.h"
#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "inode.h"
#समावेश "glock.h"
#समावेश "glops.h"
#समावेश "log.h"
#समावेश "lops.h"
#समावेश "meta_io.h"
#समावेश "recovery.h"
#समावेश "rgrp.h"
#समावेश "trans.h"
#समावेश "util.h"
#समावेश "trace_gfs2.h"

/**
 * gfs2_pin - Pin a buffer in memory
 * @sdp: The superblock
 * @bh: The buffer to be pinned
 *
 * The log lock must be held when calling this function
 */
व्योम gfs2_pin(काष्ठा gfs2_sbd *sdp, काष्ठा buffer_head *bh)
अणु
	काष्ठा gfs2_bufdata *bd;

	BUG_ON(!current->journal_info);

	clear_buffer_dirty(bh);
	अगर (test_set_buffer_pinned(bh))
		gfs2_निश्चित_withdraw(sdp, 0);
	अगर (!buffer_uptodate(bh))
		gfs2_io_error_bh_wd(sdp, bh);
	bd = bh->b_निजी;
	/* If this buffer is in the AIL and it has alपढ़ोy been written
	 * to in-place disk block, हटाओ it from the AIL.
	 */
	spin_lock(&sdp->sd_ail_lock);
	अगर (bd->bd_tr)
		list_move(&bd->bd_ail_st_list, &bd->bd_tr->tr_ail2_list);
	spin_unlock(&sdp->sd_ail_lock);
	get_bh(bh);
	atomic_inc(&sdp->sd_log_pinned);
	trace_gfs2_pin(bd, 1);
पूर्ण

अटल bool buffer_is_rgrp(स्थिर काष्ठा gfs2_bufdata *bd)
अणु
	वापस bd->bd_gl->gl_name.ln_type == LM_TYPE_RGRP;
पूर्ण

अटल व्योम maybe_release_space(काष्ठा gfs2_bufdata *bd)
अणु
	काष्ठा gfs2_glock *gl = bd->bd_gl;
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	काष्ठा gfs2_rgrpd *rgd = gfs2_glock2rgrp(gl);
	अचिन्हित पूर्णांक index = bd->bd_bh->b_blocknr - gl->gl_name.ln_number;
	काष्ठा gfs2_biपंचांगap *bi = rgd->rd_bits + index;

	rgrp_lock_local(rgd);
	अगर (bi->bi_clone == शून्य)
		जाओ out;
	अगर (sdp->sd_args.ar_discard)
		gfs2_rgrp_send_discards(sdp, rgd->rd_data0, bd->bd_bh, bi, 1, शून्य);
	स_नकल(bi->bi_clone + bi->bi_offset,
	       bd->bd_bh->b_data + bi->bi_offset, bi->bi_bytes);
	clear_bit(GBF_FULL, &bi->bi_flags);
	rgd->rd_मुक्त_clone = rgd->rd_मुक्त;
	BUG_ON(rgd->rd_मुक्त_clone < rgd->rd_reserved);
	rgd->rd_extfail_pt = rgd->rd_मुक्त;

out:
	rgrp_unlock_local(rgd);
पूर्ण

/**
 * gfs2_unpin - Unpin a buffer
 * @sdp: the fileप्रणाली the buffer beदीर्घs to
 * @bh: The buffer to unpin
 * @tr: The प्रणाली transaction being flushed
 */

अटल व्योम gfs2_unpin(काष्ठा gfs2_sbd *sdp, काष्ठा buffer_head *bh,
		       काष्ठा gfs2_trans *tr)
अणु
	काष्ठा gfs2_bufdata *bd = bh->b_निजी;

	BUG_ON(!buffer_uptodate(bh));
	BUG_ON(!buffer_pinned(bh));

	lock_buffer(bh);
	mark_buffer_dirty(bh);
	clear_buffer_pinned(bh);

	अगर (buffer_is_rgrp(bd))
		maybe_release_space(bd);

	spin_lock(&sdp->sd_ail_lock);
	अगर (bd->bd_tr) अणु
		list_del(&bd->bd_ail_st_list);
		brअन्यथा(bh);
	पूर्ण अन्यथा अणु
		काष्ठा gfs2_glock *gl = bd->bd_gl;
		list_add(&bd->bd_ail_gl_list, &gl->gl_ail_list);
		atomic_inc(&gl->gl_ail_count);
	पूर्ण
	bd->bd_tr = tr;
	list_add(&bd->bd_ail_st_list, &tr->tr_ail1_list);
	spin_unlock(&sdp->sd_ail_lock);

	clear_bit(GLF_LFLUSH, &bd->bd_gl->gl_flags);
	trace_gfs2_pin(bd, 0);
	unlock_buffer(bh);
	atomic_dec(&sdp->sd_log_pinned);
पूर्ण

व्योम gfs2_log_incr_head(काष्ठा gfs2_sbd *sdp)
अणु
	BUG_ON((sdp->sd_log_flush_head == sdp->sd_log_tail) &&
	       (sdp->sd_log_flush_head != sdp->sd_log_head));

	अगर (++sdp->sd_log_flush_head == sdp->sd_jdesc->jd_blocks)
		sdp->sd_log_flush_head = 0;
पूर्ण

u64 gfs2_log_bmap(काष्ठा gfs2_jdesc *jd, अचिन्हित पूर्णांक lblock)
अणु
	काष्ठा gfs2_journal_extent *je;

	list_क्रम_each_entry(je, &jd->extent_list, list) अणु
		अगर (lblock >= je->lblock && lblock < je->lblock + je->blocks)
			वापस je->dblock + lblock - je->lblock;
	पूर्ण

	वापस -1;
पूर्ण

/**
 * gfs2_end_log_ग_लिखो_bh - end log ग_लिखो of pagecache data with buffers
 * @sdp: The superblock
 * @bvec: The bio_vec
 * @error: The i/o status
 *
 * This finds the relevant buffers and unlocks them and sets the
 * error flag according to the status of the i/o request. This is
 * used when the log is writing data which has an in-place version
 * that is pinned in the pagecache.
 */

अटल व्योम gfs2_end_log_ग_लिखो_bh(काष्ठा gfs2_sbd *sdp,
				  काष्ठा bio_vec *bvec,
				  blk_status_t error)
अणु
	काष्ठा buffer_head *bh, *next;
	काष्ठा page *page = bvec->bv_page;
	अचिन्हित size;

	bh = page_buffers(page);
	size = bvec->bv_len;
	जबतक (bh_offset(bh) < bvec->bv_offset)
		bh = bh->b_this_page;
	करो अणु
		अगर (error)
			mark_buffer_ग_लिखो_io_error(bh);
		unlock_buffer(bh);
		next = bh->b_this_page;
		size -= bh->b_size;
		brअन्यथा(bh);
		bh = next;
	पूर्ण जबतक(bh && size);
पूर्ण

/**
 * gfs2_end_log_ग_लिखो - end of i/o to the log
 * @bio: The bio
 *
 * Each bio_vec contains either data from the pagecache or data
 * relating to the log itself. Here we iterate over the bio_vec
 * array, processing both kinds of data.
 *
 */

अटल व्योम gfs2_end_log_ग_लिखो(काष्ठा bio *bio)
अणु
	काष्ठा gfs2_sbd *sdp = bio->bi_निजी;
	काष्ठा bio_vec *bvec;
	काष्ठा page *page;
	काष्ठा bvec_iter_all iter_all;

	अगर (bio->bi_status) अणु
		अगर (!cmpxchg(&sdp->sd_log_error, 0, (पूर्णांक)bio->bi_status))
			fs_err(sdp, "Error %d writing to journal, jid=%u\n",
			       bio->bi_status, sdp->sd_jdesc->jd_jid);
		gfs2_withdraw_delayed(sdp);
		/* prevent more ग_लिखोs to the journal */
		clear_bit(SDF_JOURNAL_LIVE, &sdp->sd_flags);
		wake_up(&sdp->sd_logd_रुकोq);
	पूर्ण

	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		page = bvec->bv_page;
		अगर (page_has_buffers(page))
			gfs2_end_log_ग_लिखो_bh(sdp, bvec, bio->bi_status);
		अन्यथा
			mempool_मुक्त(page, gfs2_page_pool);
	पूर्ण

	bio_put(bio);
	अगर (atomic_dec_and_test(&sdp->sd_log_in_flight))
		wake_up(&sdp->sd_log_flush_रुको);
पूर्ण

/**
 * gfs2_log_submit_bio - Submit any pending log bio
 * @biop: Address of the bio poपूर्णांकer
 * @opf: REQ_OP | op_flags
 *
 * Submit any pending part-built or full bio to the block device. If
 * there is no pending bio, then this is a no-op.
 */

व्योम gfs2_log_submit_bio(काष्ठा bio **biop, पूर्णांक opf)
अणु
	काष्ठा bio *bio = *biop;
	अगर (bio) अणु
		काष्ठा gfs2_sbd *sdp = bio->bi_निजी;
		atomic_inc(&sdp->sd_log_in_flight);
		bio->bi_opf = opf;
		submit_bio(bio);
		*biop = शून्य;
	पूर्ण
पूर्ण

/**
 * gfs2_log_alloc_bio - Allocate a bio
 * @sdp: The super block
 * @blkno: The device block number we want to ग_लिखो to
 * @end_io: The bi_end_io callback
 *
 * Allocate a new bio, initialize it with the given parameters and वापस it.
 *
 * Returns: The newly allocated bio
 */

अटल काष्ठा bio *gfs2_log_alloc_bio(काष्ठा gfs2_sbd *sdp, u64 blkno,
				      bio_end_io_t *end_io)
अणु
	काष्ठा super_block *sb = sdp->sd_vfs;
	काष्ठा bio *bio = bio_alloc(GFP_NOIO, BIO_MAX_VECS);

	bio->bi_iter.bi_sector = blkno << sdp->sd_fsb2bb_shअगरt;
	bio_set_dev(bio, sb->s_bdev);
	bio->bi_end_io = end_io;
	bio->bi_निजी = sdp;

	वापस bio;
पूर्ण

/**
 * gfs2_log_get_bio - Get cached log bio, or allocate a new one
 * @sdp: The super block
 * @blkno: The device block number we want to ग_लिखो to
 * @biop: The bio to get or allocate
 * @op: REQ_OP
 * @end_io: The bi_end_io callback
 * @flush: Always flush the current bio and allocate a new one?
 *
 * If there is a cached bio, then अगर the next block number is sequential
 * with the previous one, वापस it, otherwise flush the bio to the
 * device. If there is no cached bio, or we just flushed it, then
 * allocate a new one.
 *
 * Returns: The bio to use क्रम log ग_लिखोs
 */

अटल काष्ठा bio *gfs2_log_get_bio(काष्ठा gfs2_sbd *sdp, u64 blkno,
				    काष्ठा bio **biop, पूर्णांक op,
				    bio_end_io_t *end_io, bool flush)
अणु
	काष्ठा bio *bio = *biop;

	अगर (bio) अणु
		u64 nblk;

		nblk = bio_end_sector(bio);
		nblk >>= sdp->sd_fsb2bb_shअगरt;
		अगर (blkno == nblk && !flush)
			वापस bio;
		gfs2_log_submit_bio(biop, op);
	पूर्ण

	*biop = gfs2_log_alloc_bio(sdp, blkno, end_io);
	वापस *biop;
पूर्ण

/**
 * gfs2_log_ग_लिखो - ग_लिखो to log
 * @sdp: the fileप्रणाली
 * @jd: The journal descriptor
 * @page: the page to ग_लिखो
 * @size: the size of the data to ग_लिखो
 * @offset: the offset within the page 
 * @blkno: block number of the log entry
 *
 * Try and add the page segment to the current bio. If that fails,
 * submit the current bio to the device and create a new one, and
 * then add the page segment to that.
 */

व्योम gfs2_log_ग_लिखो(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_jdesc *jd,
		    काष्ठा page *page, अचिन्हित size, अचिन्हित offset,
		    u64 blkno)
अणु
	काष्ठा bio *bio;
	पूर्णांक ret;

	bio = gfs2_log_get_bio(sdp, blkno, &jd->jd_log_bio, REQ_OP_WRITE,
			       gfs2_end_log_ग_लिखो, false);
	ret = bio_add_page(bio, page, size, offset);
	अगर (ret == 0) अणु
		bio = gfs2_log_get_bio(sdp, blkno, &jd->jd_log_bio,
				       REQ_OP_WRITE, gfs2_end_log_ग_लिखो, true);
		ret = bio_add_page(bio, page, size, offset);
		WARN_ON(ret == 0);
	पूर्ण
पूर्ण

/**
 * gfs2_log_ग_लिखो_bh - ग_लिखो a buffer's content to the log
 * @sdp: The super block
 * @bh: The buffer poपूर्णांकing to the in-place location
 * 
 * This ग_लिखोs the content of the buffer to the next available location
 * in the log. The buffer will be unlocked once the i/o to the log has
 * completed.
 */

अटल व्योम gfs2_log_ग_लिखो_bh(काष्ठा gfs2_sbd *sdp, काष्ठा buffer_head *bh)
अणु
	u64 dblock;

	dblock = gfs2_log_bmap(sdp->sd_jdesc, sdp->sd_log_flush_head);
	gfs2_log_incr_head(sdp);
	gfs2_log_ग_लिखो(sdp, sdp->sd_jdesc, bh->b_page, bh->b_size,
		       bh_offset(bh), dblock);
पूर्ण

/**
 * gfs2_log_ग_लिखो_page - ग_लिखो one block stored in a page, पूर्णांकo the log
 * @sdp: The superblock
 * @page: The काष्ठा page
 *
 * This ग_लिखोs the first block-sized part of the page पूर्णांकo the log. Note
 * that the page must have been allocated from the gfs2_page_pool mempool
 * and that after this has been called, ownership has been transferred and
 * the page may be मुक्तd at any समय.
 */

अटल व्योम gfs2_log_ग_लिखो_page(काष्ठा gfs2_sbd *sdp, काष्ठा page *page)
अणु
	काष्ठा super_block *sb = sdp->sd_vfs;
	u64 dblock;

	dblock = gfs2_log_bmap(sdp->sd_jdesc, sdp->sd_log_flush_head);
	gfs2_log_incr_head(sdp);
	gfs2_log_ग_लिखो(sdp, sdp->sd_jdesc, page, sb->s_blocksize, 0, dblock);
पूर्ण

/**
 * gfs2_end_log_पढ़ो - end I/O callback क्रम पढ़ोs from the log
 * @bio: The bio
 *
 * Simply unlock the pages in the bio. The मुख्य thपढ़ो will रुको on them and
 * process them in order as necessary.
 */

अटल व्योम gfs2_end_log_पढ़ो(काष्ठा bio *bio)
अणु
	काष्ठा page *page;
	काष्ठा bio_vec *bvec;
	काष्ठा bvec_iter_all iter_all;

	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		page = bvec->bv_page;
		अगर (bio->bi_status) अणु
			पूर्णांक err = blk_status_to_त्रुटि_सं(bio->bi_status);

			SetPageError(page);
			mapping_set_error(page->mapping, err);
		पूर्ण
		unlock_page(page);
	पूर्ण

	bio_put(bio);
पूर्ण

/**
 * gfs2_jhead_pg_srch - Look क्रम the journal head in a given page.
 * @jd: The journal descriptor
 * @head: The journal head to start from
 * @page: The page to look in
 *
 * Returns: 1 अगर found, 0 otherwise.
 */

अटल bool gfs2_jhead_pg_srch(काष्ठा gfs2_jdesc *jd,
			      काष्ठा gfs2_log_header_host *head,
			      काष्ठा page *page)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	काष्ठा gfs2_log_header_host lh;
	व्योम *kaddr = kmap_atomic(page);
	अचिन्हित पूर्णांक offset;
	bool ret = false;

	क्रम (offset = 0; offset < PAGE_SIZE; offset += sdp->sd_sb.sb_bsize) अणु
		अगर (!__get_log_header(sdp, kaddr + offset, 0, &lh)) अणु
			अगर (lh.lh_sequence >= head->lh_sequence)
				*head = lh;
			अन्यथा अणु
				ret = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	kunmap_atomic(kaddr);
	वापस ret;
पूर्ण

/**
 * gfs2_jhead_process_page - Search/cleanup a page
 * @jd: The journal descriptor
 * @index: Index of the page to look पूर्णांकo
 * @head: The journal head to start from
 * @करोne: If set, perक्रमm only cleanup, अन्यथा search and set अगर found.
 *
 * Find the page with 'index' in the journal's mapping. Search the page क्रम
 * the journal head अगर requested (cleanup == false). Release refs on the
 * page so the page cache can reclaim it (put_page() twice). We grabbed a
 * reference on this page two बार, first when we did a find_or_create_page()
 * to obtain the page to add it to the bio and second when we करो a
 * find_get_page() here to get the page to रुको on जबतक I/O on it is being
 * completed.
 * This function is also used to मुक्त up a page we might've grabbed but not
 * used. Maybe we added it to a bio, but not submitted it क्रम I/O. Or we
 * submitted the I/O, but we alपढ़ोy found the jhead so we only need to drop
 * our references to the page.
 */

अटल व्योम gfs2_jhead_process_page(काष्ठा gfs2_jdesc *jd, अचिन्हित दीर्घ index,
				    काष्ठा gfs2_log_header_host *head,
				    bool *करोne)
अणु
	काष्ठा page *page;

	page = find_get_page(jd->jd_inode->i_mapping, index);
	रुको_on_page_locked(page);

	अगर (PageError(page))
		*करोne = true;

	अगर (!*करोne)
		*करोne = gfs2_jhead_pg_srch(jd, head, page);

	put_page(page); /* Once क्रम find_get_page */
	put_page(page); /* Once more क्रम find_or_create_page */
पूर्ण

अटल काष्ठा bio *gfs2_chain_bio(काष्ठा bio *prev, अचिन्हित पूर्णांक nr_iovecs)
अणु
	काष्ठा bio *new;

	new = bio_alloc(GFP_NOIO, nr_iovecs);
	bio_copy_dev(new, prev);
	new->bi_iter.bi_sector = bio_end_sector(prev);
	new->bi_opf = prev->bi_opf;
	new->bi_ग_लिखो_hपूर्णांक = prev->bi_ग_लिखो_hपूर्णांक;
	bio_chain(new, prev);
	submit_bio(prev);
	वापस new;
पूर्ण

/**
 * gfs2_find_jhead - find the head of a log
 * @jd: The journal descriptor
 * @head: The log descriptor क्रम the head of the log is वापसed here
 * @keep_cache: If set inode pages will not be truncated
 *
 * Do a search of a journal by पढ़ोing it in large chunks using bios and find
 * the valid log entry with the highest sequence number.  (i.e. the log head)
 *
 * Returns: 0 on success, त्रुटि_सं otherwise
 */
पूर्णांक gfs2_find_jhead(काष्ठा gfs2_jdesc *jd, काष्ठा gfs2_log_header_host *head,
		    bool keep_cache)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	काष्ठा address_space *mapping = jd->jd_inode->i_mapping;
	अचिन्हित पूर्णांक block = 0, blocks_submitted = 0, blocks_पढ़ो = 0;
	अचिन्हित पूर्णांक bsize = sdp->sd_sb.sb_bsize, off;
	अचिन्हित पूर्णांक bsize_shअगरt = sdp->sd_sb.sb_bsize_shअगरt;
	अचिन्हित पूर्णांक shअगरt = PAGE_SHIFT - bsize_shअगरt;
	अचिन्हित पूर्णांक max_blocks = 2 * 1024 * 1024 >> bsize_shअगरt;
	काष्ठा gfs2_journal_extent *je;
	पूर्णांक sz, ret = 0;
	काष्ठा bio *bio = शून्य;
	काष्ठा page *page = शून्य;
	bool करोne = false;
	errseq_t since;

	स_रखो(head, 0, माप(*head));
	अगर (list_empty(&jd->extent_list))
		gfs2_map_journal_extents(sdp, jd);

	since = filemap_sample_wb_err(mapping);
	list_क्रम_each_entry(je, &jd->extent_list, list) अणु
		u64 dblock = je->dblock;

		क्रम (; block < je->lblock + je->blocks; block++, dblock++) अणु
			अगर (!page) अणु
				page = find_or_create_page(mapping,
						block >> shअगरt, GFP_NOFS);
				अगर (!page) अणु
					ret = -ENOMEM;
					करोne = true;
					जाओ out;
				पूर्ण
				off = 0;
			पूर्ण

			अगर (bio && (off || block < blocks_submitted + max_blocks)) अणु
				sector_t sector = dblock << sdp->sd_fsb2bb_shअगरt;

				अगर (bio_end_sector(bio) == sector) अणु
					sz = bio_add_page(bio, page, bsize, off);
					अगर (sz == bsize)
						जाओ block_added;
				पूर्ण
				अगर (off) अणु
					अचिन्हित पूर्णांक blocks =
						(PAGE_SIZE - off) >> bsize_shअगरt;

					bio = gfs2_chain_bio(bio, blocks);
					जाओ add_block_to_new_bio;
				पूर्ण
			पूर्ण

			अगर (bio) अणु
				blocks_submitted = block;
				submit_bio(bio);
			पूर्ण

			bio = gfs2_log_alloc_bio(sdp, dblock, gfs2_end_log_पढ़ो);
			bio->bi_opf = REQ_OP_READ;
add_block_to_new_bio:
			sz = bio_add_page(bio, page, bsize, off);
			BUG_ON(sz != bsize);
block_added:
			off += bsize;
			अगर (off == PAGE_SIZE)
				page = शून्य;
			अगर (blocks_submitted <= blocks_पढ़ो + max_blocks) अणु
				/* Keep at least one bio in flight */
				जारी;
			पूर्ण

			gfs2_jhead_process_page(jd, blocks_पढ़ो >> shअगरt, head, &करोne);
			blocks_पढ़ो += PAGE_SIZE >> bsize_shअगरt;
			अगर (करोne)
				जाओ out;  /* found */
		पूर्ण
	पूर्ण

out:
	अगर (bio)
		submit_bio(bio);
	जबतक (blocks_पढ़ो < block) अणु
		gfs2_jhead_process_page(jd, blocks_पढ़ो >> shअगरt, head, &करोne);
		blocks_पढ़ो += PAGE_SIZE >> bsize_shअगरt;
	पूर्ण

	अगर (!ret)
		ret = filemap_check_wb_err(mapping, since);

	अगर (!keep_cache)
		truncate_inode_pages(mapping, 0);

	वापस ret;
पूर्ण

अटल काष्ठा page *gfs2_get_log_desc(काष्ठा gfs2_sbd *sdp, u32 ld_type,
				      u32 ld_length, u32 ld_data1)
अणु
	काष्ठा page *page = mempool_alloc(gfs2_page_pool, GFP_NOIO);
	काष्ठा gfs2_log_descriptor *ld = page_address(page);
	clear_page(ld);
	ld->ld_header.mh_magic = cpu_to_be32(GFS2_MAGIC);
	ld->ld_header.mh_type = cpu_to_be32(GFS2_METATYPE_LD);
	ld->ld_header.mh_क्रमmat = cpu_to_be32(GFS2_FORMAT_LD);
	ld->ld_type = cpu_to_be32(ld_type);
	ld->ld_length = cpu_to_be32(ld_length);
	ld->ld_data1 = cpu_to_be32(ld_data1);
	ld->ld_data2 = 0;
	वापस page;
पूर्ण

अटल व्योम gfs2_check_magic(काष्ठा buffer_head *bh)
अणु
	व्योम *kaddr;
	__be32 *ptr;

	clear_buffer_escaped(bh);
	kaddr = kmap_atomic(bh->b_page);
	ptr = kaddr + bh_offset(bh);
	अगर (*ptr == cpu_to_be32(GFS2_MAGIC))
		set_buffer_escaped(bh);
	kunmap_atomic(kaddr);
पूर्ण

अटल पूर्णांक blocknr_cmp(व्योम *priv, स्थिर काष्ठा list_head *a,
		       स्थिर काष्ठा list_head *b)
अणु
	काष्ठा gfs2_bufdata *bda, *bdb;

	bda = list_entry(a, काष्ठा gfs2_bufdata, bd_list);
	bdb = list_entry(b, काष्ठा gfs2_bufdata, bd_list);

	अगर (bda->bd_bh->b_blocknr < bdb->bd_bh->b_blocknr)
		वापस -1;
	अगर (bda->bd_bh->b_blocknr > bdb->bd_bh->b_blocknr)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम gfs2_beक्रमe_commit(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक limit,
				अचिन्हित पूर्णांक total, काष्ठा list_head *blist,
				bool is_databuf)
अणु
	काष्ठा gfs2_log_descriptor *ld;
	काष्ठा gfs2_bufdata *bd1 = शून्य, *bd2;
	काष्ठा page *page;
	अचिन्हित पूर्णांक num;
	अचिन्हित n;
	__be64 *ptr;

	gfs2_log_lock(sdp);
	list_sort(शून्य, blist, blocknr_cmp);
	bd1 = bd2 = list_prepare_entry(bd1, blist, bd_list);
	जबतक(total) अणु
		num = total;
		अगर (total > limit)
			num = limit;
		gfs2_log_unlock(sdp);
		page = gfs2_get_log_desc(sdp,
					 is_databuf ? GFS2_LOG_DESC_JDATA :
					 GFS2_LOG_DESC_METADATA, num + 1, num);
		ld = page_address(page);
		gfs2_log_lock(sdp);
		ptr = (__be64 *)(ld + 1);

		n = 0;
		list_क्रम_each_entry_जारी(bd1, blist, bd_list) अणु
			*ptr++ = cpu_to_be64(bd1->bd_bh->b_blocknr);
			अगर (is_databuf) अणु
				gfs2_check_magic(bd1->bd_bh);
				*ptr++ = cpu_to_be64(buffer_escaped(bd1->bd_bh) ? 1 : 0);
			पूर्ण
			अगर (++n >= num)
				अवरोध;
		पूर्ण

		gfs2_log_unlock(sdp);
		gfs2_log_ग_लिखो_page(sdp, page);
		gfs2_log_lock(sdp);

		n = 0;
		list_क्रम_each_entry_जारी(bd2, blist, bd_list) अणु
			get_bh(bd2->bd_bh);
			gfs2_log_unlock(sdp);
			lock_buffer(bd2->bd_bh);

			अगर (buffer_escaped(bd2->bd_bh)) अणु
				व्योम *kaddr;
				page = mempool_alloc(gfs2_page_pool, GFP_NOIO);
				ptr = page_address(page);
				kaddr = kmap_atomic(bd2->bd_bh->b_page);
				स_नकल(ptr, kaddr + bh_offset(bd2->bd_bh),
				       bd2->bd_bh->b_size);
				kunmap_atomic(kaddr);
				*(__be32 *)ptr = 0;
				clear_buffer_escaped(bd2->bd_bh);
				unlock_buffer(bd2->bd_bh);
				brअन्यथा(bd2->bd_bh);
				gfs2_log_ग_लिखो_page(sdp, page);
			पूर्ण अन्यथा अणु
				gfs2_log_ग_लिखो_bh(sdp, bd2->bd_bh);
			पूर्ण
			gfs2_log_lock(sdp);
			अगर (++n >= num)
				अवरोध;
		पूर्ण

		BUG_ON(total < num);
		total -= num;
	पूर्ण
	gfs2_log_unlock(sdp);
पूर्ण

अटल व्योम buf_lo_beक्रमe_commit(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *tr)
अणु
	अचिन्हित पूर्णांक limit = buf_limit(sdp); /* 503 क्रम 4k blocks */
	अचिन्हित पूर्णांक nbuf;
	अगर (tr == शून्य)
		वापस;
	nbuf = tr->tr_num_buf_new - tr->tr_num_buf_rm;
	gfs2_beक्रमe_commit(sdp, limit, nbuf, &tr->tr_buf, 0);
पूर्ण

अटल व्योम buf_lo_after_commit(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *tr)
अणु
	काष्ठा list_head *head;
	काष्ठा gfs2_bufdata *bd;

	अगर (tr == शून्य)
		वापस;

	head = &tr->tr_buf;
	जबतक (!list_empty(head)) अणु
		bd = list_first_entry(head, काष्ठा gfs2_bufdata, bd_list);
		list_del_init(&bd->bd_list);
		gfs2_unpin(sdp, bd->bd_bh, tr);
	पूर्ण
पूर्ण

अटल व्योम buf_lo_beक्रमe_scan(काष्ठा gfs2_jdesc *jd,
			       काष्ठा gfs2_log_header_host *head, पूर्णांक pass)
अणु
	अगर (pass != 0)
		वापस;

	jd->jd_found_blocks = 0;
	jd->jd_replayed_blocks = 0;
पूर्ण

अटल पूर्णांक buf_lo_scan_elements(काष्ठा gfs2_jdesc *jd, u32 start,
				काष्ठा gfs2_log_descriptor *ld, __be64 *ptr,
				पूर्णांक pass)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(jd->jd_inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	काष्ठा gfs2_glock *gl = ip->i_gl;
	अचिन्हित पूर्णांक blks = be32_to_cpu(ld->ld_data1);
	काष्ठा buffer_head *bh_log, *bh_ip;
	u64 blkno;
	पूर्णांक error = 0;

	अगर (pass != 1 || be32_to_cpu(ld->ld_type) != GFS2_LOG_DESC_METADATA)
		वापस 0;

	gfs2_replay_incr_blk(jd, &start);

	क्रम (; blks; gfs2_replay_incr_blk(jd, &start), blks--) अणु
		blkno = be64_to_cpu(*ptr++);

		jd->jd_found_blocks++;

		अगर (gfs2_revoke_check(jd, blkno, start))
			जारी;

		error = gfs2_replay_पढ़ो_block(jd, start, &bh_log);
		अगर (error)
			वापस error;

		bh_ip = gfs2_meta_new(gl, blkno);
		स_नकल(bh_ip->b_data, bh_log->b_data, bh_log->b_size);

		अगर (gfs2_meta_check(sdp, bh_ip))
			error = -EIO;
		अन्यथा अणु
			काष्ठा gfs2_meta_header *mh =
				(काष्ठा gfs2_meta_header *)bh_ip->b_data;

			अगर (mh->mh_type == cpu_to_be32(GFS2_METATYPE_RG)) अणु
				काष्ठा gfs2_rgrpd *rgd;

				rgd = gfs2_blk2rgrpd(sdp, blkno, false);
				अगर (rgd && rgd->rd_addr == blkno &&
				    rgd->rd_bits && rgd->rd_bits->bi_bh) अणु
					fs_info(sdp, "Replaying 0x%llx but we "
						"already have a bh!\n",
						(अचिन्हित दीर्घ दीर्घ)blkno);
					fs_info(sdp, "busy:%d, pinned:%d\n",
						buffer_busy(rgd->rd_bits->bi_bh) ? 1 : 0,
						buffer_pinned(rgd->rd_bits->bi_bh));
					gfs2_dump_glock(शून्य, rgd->rd_gl, true);
				पूर्ण
			पूर्ण
			mark_buffer_dirty(bh_ip);
		पूर्ण
		brअन्यथा(bh_log);
		brअन्यथा(bh_ip);

		अगर (error)
			अवरोध;

		jd->jd_replayed_blocks++;
	पूर्ण

	वापस error;
पूर्ण

अटल व्योम buf_lo_after_scan(काष्ठा gfs2_jdesc *jd, पूर्णांक error, पूर्णांक pass)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(jd->jd_inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);

	अगर (error) अणु
		gfs2_inode_metasync(ip->i_gl);
		वापस;
	पूर्ण
	अगर (pass != 1)
		वापस;

	gfs2_inode_metasync(ip->i_gl);

	fs_info(sdp, "jid=%u: Replayed %u of %u blocks\n",
	        jd->jd_jid, jd->jd_replayed_blocks, jd->jd_found_blocks);
पूर्ण

अटल व्योम revoke_lo_beक्रमe_commit(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *tr)
अणु
	काष्ठा gfs2_meta_header *mh;
	अचिन्हित पूर्णांक offset;
	काष्ठा list_head *head = &sdp->sd_log_revokes;
	काष्ठा gfs2_bufdata *bd;
	काष्ठा page *page;
	अचिन्हित पूर्णांक length;

	gfs2_flush_revokes(sdp);
	अगर (!sdp->sd_log_num_revoke)
		वापस;

	length = gfs2_काष्ठा2blk(sdp, sdp->sd_log_num_revoke);
	page = gfs2_get_log_desc(sdp, GFS2_LOG_DESC_REVOKE, length, sdp->sd_log_num_revoke);
	offset = माप(काष्ठा gfs2_log_descriptor);

	list_क्रम_each_entry(bd, head, bd_list) अणु
		sdp->sd_log_num_revoke--;

		अगर (offset + माप(u64) > sdp->sd_sb.sb_bsize) अणु
			gfs2_log_ग_लिखो_page(sdp, page);
			page = mempool_alloc(gfs2_page_pool, GFP_NOIO);
			mh = page_address(page);
			clear_page(mh);
			mh->mh_magic = cpu_to_be32(GFS2_MAGIC);
			mh->mh_type = cpu_to_be32(GFS2_METATYPE_LB);
			mh->mh_क्रमmat = cpu_to_be32(GFS2_FORMAT_LB);
			offset = माप(काष्ठा gfs2_meta_header);
		पूर्ण

		*(__be64 *)(page_address(page) + offset) = cpu_to_be64(bd->bd_blkno);
		offset += माप(u64);
	पूर्ण
	gfs2_निश्चित_withdraw(sdp, !sdp->sd_log_num_revoke);

	gfs2_log_ग_लिखो_page(sdp, page);
पूर्ण

व्योम gfs2_drain_revokes(काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा list_head *head = &sdp->sd_log_revokes;
	काष्ठा gfs2_bufdata *bd;
	काष्ठा gfs2_glock *gl;

	जबतक (!list_empty(head)) अणु
		bd = list_first_entry(head, काष्ठा gfs2_bufdata, bd_list);
		list_del_init(&bd->bd_list);
		gl = bd->bd_gl;
		gfs2_glock_हटाओ_revoke(gl);
		kmem_cache_मुक्त(gfs2_bufdata_cachep, bd);
	पूर्ण
पूर्ण

अटल व्योम revoke_lo_after_commit(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *tr)
अणु
	gfs2_drain_revokes(sdp);
पूर्ण

अटल व्योम revoke_lo_beक्रमe_scan(काष्ठा gfs2_jdesc *jd,
				  काष्ठा gfs2_log_header_host *head, पूर्णांक pass)
अणु
	अगर (pass != 0)
		वापस;

	jd->jd_found_revokes = 0;
	jd->jd_replay_tail = head->lh_tail;
पूर्ण

अटल पूर्णांक revoke_lo_scan_elements(काष्ठा gfs2_jdesc *jd, u32 start,
				   काष्ठा gfs2_log_descriptor *ld, __be64 *ptr,
				   पूर्णांक pass)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	अचिन्हित पूर्णांक blks = be32_to_cpu(ld->ld_length);
	अचिन्हित पूर्णांक revokes = be32_to_cpu(ld->ld_data1);
	काष्ठा buffer_head *bh;
	अचिन्हित पूर्णांक offset;
	u64 blkno;
	पूर्णांक first = 1;
	पूर्णांक error;

	अगर (pass != 0 || be32_to_cpu(ld->ld_type) != GFS2_LOG_DESC_REVOKE)
		वापस 0;

	offset = माप(काष्ठा gfs2_log_descriptor);

	क्रम (; blks; gfs2_replay_incr_blk(jd, &start), blks--) अणु
		error = gfs2_replay_पढ़ो_block(jd, start, &bh);
		अगर (error)
			वापस error;

		अगर (!first)
			gfs2_metatype_check(sdp, bh, GFS2_METATYPE_LB);

		जबतक (offset + माप(u64) <= sdp->sd_sb.sb_bsize) अणु
			blkno = be64_to_cpu(*(__be64 *)(bh->b_data + offset));

			error = gfs2_revoke_add(jd, blkno, start);
			अगर (error < 0) अणु
				brअन्यथा(bh);
				वापस error;
			पूर्ण
			अन्यथा अगर (error)
				jd->jd_found_revokes++;

			अगर (!--revokes)
				अवरोध;
			offset += माप(u64);
		पूर्ण

		brअन्यथा(bh);
		offset = माप(काष्ठा gfs2_meta_header);
		first = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम revoke_lo_after_scan(काष्ठा gfs2_jdesc *jd, पूर्णांक error, पूर्णांक pass)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);

	अगर (error) अणु
		gfs2_revoke_clean(jd);
		वापस;
	पूर्ण
	अगर (pass != 1)
		वापस;

	fs_info(sdp, "jid=%u: Found %u revoke tags\n",
	        jd->jd_jid, jd->jd_found_revokes);

	gfs2_revoke_clean(jd);
पूर्ण

/**
 * databuf_lo_beक्रमe_commit - Scan the data buffers, writing as we go
 * @sdp: The fileप्रणाली
 * @tr: The प्रणाली transaction being flushed
 */

अटल व्योम databuf_lo_beक्रमe_commit(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *tr)
अणु
	अचिन्हित पूर्णांक limit = databuf_limit(sdp);
	अचिन्हित पूर्णांक nbuf;
	अगर (tr == शून्य)
		वापस;
	nbuf = tr->tr_num_databuf_new - tr->tr_num_databuf_rm;
	gfs2_beक्रमe_commit(sdp, limit, nbuf, &tr->tr_databuf, 1);
पूर्ण

अटल पूर्णांक databuf_lo_scan_elements(काष्ठा gfs2_jdesc *jd, u32 start,
				    काष्ठा gfs2_log_descriptor *ld,
				    __be64 *ptr, पूर्णांक pass)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(jd->jd_inode);
	काष्ठा gfs2_glock *gl = ip->i_gl;
	अचिन्हित पूर्णांक blks = be32_to_cpu(ld->ld_data1);
	काष्ठा buffer_head *bh_log, *bh_ip;
	u64 blkno;
	u64 esc;
	पूर्णांक error = 0;

	अगर (pass != 1 || be32_to_cpu(ld->ld_type) != GFS2_LOG_DESC_JDATA)
		वापस 0;

	gfs2_replay_incr_blk(jd, &start);
	क्रम (; blks; gfs2_replay_incr_blk(jd, &start), blks--) अणु
		blkno = be64_to_cpu(*ptr++);
		esc = be64_to_cpu(*ptr++);

		jd->jd_found_blocks++;

		अगर (gfs2_revoke_check(jd, blkno, start))
			जारी;

		error = gfs2_replay_पढ़ो_block(jd, start, &bh_log);
		अगर (error)
			वापस error;

		bh_ip = gfs2_meta_new(gl, blkno);
		स_नकल(bh_ip->b_data, bh_log->b_data, bh_log->b_size);

		/* Unescape */
		अगर (esc) अणु
			__be32 *eptr = (__be32 *)bh_ip->b_data;
			*eptr = cpu_to_be32(GFS2_MAGIC);
		पूर्ण
		mark_buffer_dirty(bh_ip);

		brअन्यथा(bh_log);
		brअन्यथा(bh_ip);

		jd->jd_replayed_blocks++;
	पूर्ण

	वापस error;
पूर्ण

/* FIXME: sort out accounting क्रम log blocks etc. */

अटल व्योम databuf_lo_after_scan(काष्ठा gfs2_jdesc *jd, पूर्णांक error, पूर्णांक pass)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(jd->jd_inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);

	अगर (error) अणु
		gfs2_inode_metasync(ip->i_gl);
		वापस;
	पूर्ण
	अगर (pass != 1)
		वापस;

	/* data sync? */
	gfs2_inode_metasync(ip->i_gl);

	fs_info(sdp, "jid=%u: Replayed %u of %u data blocks\n",
		jd->jd_jid, jd->jd_replayed_blocks, jd->jd_found_blocks);
पूर्ण

अटल व्योम databuf_lo_after_commit(काष्ठा gfs2_sbd *sdp, काष्ठा gfs2_trans *tr)
अणु
	काष्ठा list_head *head;
	काष्ठा gfs2_bufdata *bd;

	अगर (tr == शून्य)
		वापस;

	head = &tr->tr_databuf;
	जबतक (!list_empty(head)) अणु
		bd = list_first_entry(head, काष्ठा gfs2_bufdata, bd_list);
		list_del_init(&bd->bd_list);
		gfs2_unpin(sdp, bd->bd_bh, tr);
	पूर्ण
पूर्ण


अटल स्थिर काष्ठा gfs2_log_operations gfs2_buf_lops = अणु
	.lo_beक्रमe_commit = buf_lo_beक्रमe_commit,
	.lo_after_commit = buf_lo_after_commit,
	.lo_beक्रमe_scan = buf_lo_beक्रमe_scan,
	.lo_scan_elements = buf_lo_scan_elements,
	.lo_after_scan = buf_lo_after_scan,
	.lo_name = "buf",
पूर्ण;

अटल स्थिर काष्ठा gfs2_log_operations gfs2_revoke_lops = अणु
	.lo_beक्रमe_commit = revoke_lo_beक्रमe_commit,
	.lo_after_commit = revoke_lo_after_commit,
	.lo_beक्रमe_scan = revoke_lo_beक्रमe_scan,
	.lo_scan_elements = revoke_lo_scan_elements,
	.lo_after_scan = revoke_lo_after_scan,
	.lo_name = "revoke",
पूर्ण;

अटल स्थिर काष्ठा gfs2_log_operations gfs2_databuf_lops = अणु
	.lo_beक्रमe_commit = databuf_lo_beक्रमe_commit,
	.lo_after_commit = databuf_lo_after_commit,
	.lo_scan_elements = databuf_lo_scan_elements,
	.lo_after_scan = databuf_lo_after_scan,
	.lo_name = "databuf",
पूर्ण;

स्थिर काष्ठा gfs2_log_operations *gfs2_log_ops[] = अणु
	&gfs2_databuf_lops,
	&gfs2_buf_lops,
	&gfs2_revoke_lops,
	शून्य,
पूर्ण;

