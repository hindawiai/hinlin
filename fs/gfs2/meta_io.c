<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2008 Red Hat, Inc.  All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/swap.h>
#समावेश <linux/delay.h>
#समावेश <linux/bपन.स>
#समावेश <linux/gfs2_ondisk.h>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "glock.h"
#समावेश "glops.h"
#समावेश "inode.h"
#समावेश "log.h"
#समावेश "lops.h"
#समावेश "meta_io.h"
#समावेश "rgrp.h"
#समावेश "trans.h"
#समावेश "util.h"
#समावेश "trace_gfs2.h"

अटल पूर्णांक gfs2_aspace_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा buffer_head *bh, *head;
	पूर्णांक nr_underway = 0;
	पूर्णांक ग_लिखो_flags = REQ_META | REQ_PRIO | wbc_to_ग_लिखो_flags(wbc);

	BUG_ON(!PageLocked(page));
	BUG_ON(!page_has_buffers(page));

	head = page_buffers(page);
	bh = head;

	करो अणु
		अगर (!buffer_mapped(bh))
			जारी;
		/*
		 * If it's a fully non-blocking ग_लिखो attempt and we cannot
		 * lock the buffer then redirty the page.  Note that this can
		 * potentially cause a busy-रुको loop from flusher thपढ़ो and kswapd
		 * activity, but those code paths have their own higher-level
		 * throttling.
		 */
		अगर (wbc->sync_mode != WB_SYNC_NONE) अणु
			lock_buffer(bh);
		पूर्ण अन्यथा अगर (!trylock_buffer(bh)) अणु
			redirty_page_क्रम_ग_लिखोpage(wbc, page);
			जारी;
		पूर्ण
		अगर (test_clear_buffer_dirty(bh)) अणु
			mark_buffer_async_ग_लिखो(bh);
		पूर्ण अन्यथा अणु
			unlock_buffer(bh);
		पूर्ण
	पूर्ण जबतक ((bh = bh->b_this_page) != head);

	/*
	 * The page and its buffers are रक्षित by PageWriteback(), so we can
	 * drop the bh refcounts early.
	 */
	BUG_ON(PageWriteback(page));
	set_page_ग_लिखोback(page);

	करो अणु
		काष्ठा buffer_head *next = bh->b_this_page;
		अगर (buffer_async_ग_लिखो(bh)) अणु
			submit_bh(REQ_OP_WRITE, ग_लिखो_flags, bh);
			nr_underway++;
		पूर्ण
		bh = next;
	पूर्ण जबतक (bh != head);
	unlock_page(page);

	अगर (nr_underway == 0)
		end_page_ग_लिखोback(page);

	वापस 0;
पूर्ण

स्थिर काष्ठा address_space_operations gfs2_meta_aops = अणु
	.ग_लिखोpage = gfs2_aspace_ग_लिखोpage,
	.releasepage = gfs2_releasepage,
पूर्ण;

स्थिर काष्ठा address_space_operations gfs2_rgrp_aops = अणु
	.ग_लिखोpage = gfs2_aspace_ग_लिखोpage,
	.releasepage = gfs2_releasepage,
पूर्ण;

/**
 * gfs2_getbuf - Get a buffer with a given address space
 * @gl: the glock
 * @blkno: the block number (fileप्रणाली scope)
 * @create: 1 अगर the buffer should be created
 *
 * Returns: the buffer
 */

काष्ठा buffer_head *gfs2_getbuf(काष्ठा gfs2_glock *gl, u64 blkno, पूर्णांक create)
अणु
	काष्ठा address_space *mapping = gfs2_glock2aspace(gl);
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	काष्ठा page *page;
	काष्ठा buffer_head *bh;
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित दीर्घ index;
	अचिन्हित पूर्णांक bufnum;

	अगर (mapping == शून्य)
		mapping = &sdp->sd_aspace;

	shअगरt = PAGE_SHIFT - sdp->sd_sb.sb_bsize_shअगरt;
	index = blkno >> shअगरt;             /* convert block to page */
	bufnum = blkno - (index << shअगरt);  /* block buf index within page */

	अगर (create) अणु
		क्रम (;;) अणु
			page = grab_cache_page(mapping, index);
			अगर (page)
				अवरोध;
			yield();
		पूर्ण
		अगर (!page_has_buffers(page))
			create_empty_buffers(page, sdp->sd_sb.sb_bsize, 0);
	पूर्ण अन्यथा अणु
		page = find_get_page_flags(mapping, index,
						FGP_LOCK|FGP_ACCESSED);
		अगर (!page)
			वापस शून्य;
		अगर (!page_has_buffers(page)) अणु
			bh = शून्य;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	/* Locate header क्रम our buffer within our page */
	क्रम (bh = page_buffers(page); bufnum--; bh = bh->b_this_page)
		/* Do nothing */;
	get_bh(bh);

	अगर (!buffer_mapped(bh))
		map_bh(bh, sdp->sd_vfs, blkno);

out_unlock:
	unlock_page(page);
	put_page(page);

	वापस bh;
पूर्ण

अटल व्योम meta_prep_new(काष्ठा buffer_head *bh)
अणु
	काष्ठा gfs2_meta_header *mh = (काष्ठा gfs2_meta_header *)bh->b_data;

	lock_buffer(bh);
	clear_buffer_dirty(bh);
	set_buffer_uptodate(bh);
	unlock_buffer(bh);

	mh->mh_magic = cpu_to_be32(GFS2_MAGIC);
पूर्ण

/**
 * gfs2_meta_new - Get a block
 * @gl: The glock associated with this block
 * @blkno: The block number
 *
 * Returns: The buffer
 */

काष्ठा buffer_head *gfs2_meta_new(काष्ठा gfs2_glock *gl, u64 blkno)
अणु
	काष्ठा buffer_head *bh;
	bh = gfs2_getbuf(gl, blkno, CREATE);
	meta_prep_new(bh);
	वापस bh;
पूर्ण

अटल व्योम gfs2_meta_पढ़ो_endio(काष्ठा bio *bio)
अणु
	काष्ठा bio_vec *bvec;
	काष्ठा bvec_iter_all iter_all;

	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		काष्ठा page *page = bvec->bv_page;
		काष्ठा buffer_head *bh = page_buffers(page);
		अचिन्हित पूर्णांक len = bvec->bv_len;

		जबतक (bh_offset(bh) < bvec->bv_offset)
			bh = bh->b_this_page;
		करो अणु
			काष्ठा buffer_head *next = bh->b_this_page;
			len -= bh->b_size;
			bh->b_end_io(bh, !bio->bi_status);
			bh = next;
		पूर्ण जबतक (bh && len);
	पूर्ण
	bio_put(bio);
पूर्ण

/*
 * Submit several consecutive buffer head I/O requests as a single bio I/O
 * request.  (See submit_bh_wbc.)
 */
अटल व्योम gfs2_submit_bhs(पूर्णांक op, पूर्णांक op_flags, काष्ठा buffer_head *bhs[],
			    पूर्णांक num)
अणु
	जबतक (num > 0) अणु
		काष्ठा buffer_head *bh = *bhs;
		काष्ठा bio *bio;

		bio = bio_alloc(GFP_NOIO, num);
		bio->bi_iter.bi_sector = bh->b_blocknr * (bh->b_size >> 9);
		bio_set_dev(bio, bh->b_bdev);
		जबतक (num > 0) अणु
			bh = *bhs;
			अगर (!bio_add_page(bio, bh->b_page, bh->b_size, bh_offset(bh))) अणु
				BUG_ON(bio->bi_iter.bi_size == 0);
				अवरोध;
			पूर्ण
			bhs++;
			num--;
		पूर्ण
		bio->bi_end_io = gfs2_meta_पढ़ो_endio;
		bio_set_op_attrs(bio, op, op_flags);
		submit_bio(bio);
	पूर्ण
पूर्ण

/**
 * gfs2_meta_पढ़ो - Read a block from disk
 * @gl: The glock covering the block
 * @blkno: The block number
 * @flags: flags
 * @rahead: Do पढ़ो-ahead
 * @bhp: the place where the buffer is वापसed (शून्य on failure)
 *
 * Returns: त्रुटि_सं
 */

पूर्णांक gfs2_meta_पढ़ो(काष्ठा gfs2_glock *gl, u64 blkno, पूर्णांक flags,
		   पूर्णांक rahead, काष्ठा buffer_head **bhp)
अणु
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	काष्ठा buffer_head *bh, *bhs[2];
	पूर्णांक num = 0;

	अगर (unlikely(gfs2_withdrawn(sdp)) &&
	    (!sdp->sd_jdesc || gl != sdp->sd_jinode_gl)) अणु
		*bhp = शून्य;
		वापस -EIO;
	पूर्ण

	*bhp = bh = gfs2_getbuf(gl, blkno, CREATE);

	lock_buffer(bh);
	अगर (buffer_uptodate(bh)) अणु
		unlock_buffer(bh);
		flags &= ~DIO_WAIT;
	पूर्ण अन्यथा अणु
		bh->b_end_io = end_buffer_पढ़ो_sync;
		get_bh(bh);
		bhs[num++] = bh;
	पूर्ण

	अगर (rahead) अणु
		bh = gfs2_getbuf(gl, blkno + 1, CREATE);

		lock_buffer(bh);
		अगर (buffer_uptodate(bh)) अणु
			unlock_buffer(bh);
			brअन्यथा(bh);
		पूर्ण अन्यथा अणु
			bh->b_end_io = end_buffer_पढ़ो_sync;
			bhs[num++] = bh;
		पूर्ण
	पूर्ण

	gfs2_submit_bhs(REQ_OP_READ, REQ_META | REQ_PRIO, bhs, num);
	अगर (!(flags & DIO_WAIT))
		वापस 0;

	bh = *bhp;
	रुको_on_buffer(bh);
	अगर (unlikely(!buffer_uptodate(bh))) अणु
		काष्ठा gfs2_trans *tr = current->journal_info;
		अगर (tr && test_bit(TR_TOUCHED, &tr->tr_flags))
			gfs2_io_error_bh_wd(sdp, bh);
		brअन्यथा(bh);
		*bhp = शून्य;
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * gfs2_meta_रुको - Reपढ़ो a block from disk
 * @sdp: the fileप्रणाली
 * @bh: The block to रुको क्रम
 *
 * Returns: त्रुटि_सं
 */

पूर्णांक gfs2_meta_रुको(काष्ठा gfs2_sbd *sdp, काष्ठा buffer_head *bh)
अणु
	अगर (unlikely(gfs2_withdrawn(sdp)))
		वापस -EIO;

	रुको_on_buffer(bh);

	अगर (!buffer_uptodate(bh)) अणु
		काष्ठा gfs2_trans *tr = current->journal_info;
		अगर (tr && test_bit(TR_TOUCHED, &tr->tr_flags))
			gfs2_io_error_bh_wd(sdp, bh);
		वापस -EIO;
	पूर्ण
	अगर (unlikely(gfs2_withdrawn(sdp)))
		वापस -EIO;

	वापस 0;
पूर्ण

व्योम gfs2_हटाओ_from_journal(काष्ठा buffer_head *bh, पूर्णांक meta)
अणु
	काष्ठा address_space *mapping = bh->b_page->mapping;
	काष्ठा gfs2_sbd *sdp = gfs2_mapping2sbd(mapping);
	काष्ठा gfs2_bufdata *bd = bh->b_निजी;
	काष्ठा gfs2_trans *tr = current->journal_info;
	पूर्णांक was_pinned = 0;

	अगर (test_clear_buffer_pinned(bh)) अणु
		trace_gfs2_pin(bd, 0);
		atomic_dec(&sdp->sd_log_pinned);
		list_del_init(&bd->bd_list);
		अगर (meta == REMOVE_META)
			tr->tr_num_buf_rm++;
		अन्यथा
			tr->tr_num_databuf_rm++;
		set_bit(TR_TOUCHED, &tr->tr_flags);
		was_pinned = 1;
		brअन्यथा(bh);
	पूर्ण
	अगर (bd) अणु
		अगर (bd->bd_tr) अणु
			gfs2_trans_add_revoke(sdp, bd);
		पूर्ण अन्यथा अगर (was_pinned) अणु
			bh->b_निजी = शून्य;
			kmem_cache_मुक्त(gfs2_bufdata_cachep, bd);
		पूर्ण अन्यथा अगर (!list_empty(&bd->bd_ail_st_list) &&
					!list_empty(&bd->bd_ail_gl_list)) अणु
			gfs2_हटाओ_from_ail(bd);
		पूर्ण
	पूर्ण
	clear_buffer_dirty(bh);
	clear_buffer_uptodate(bh);
पूर्ण

/**
 * gfs2_ail1_wipe - हटाओ deleted/मुक्तd buffers from the ail1 list
 * @sdp: superblock
 * @bstart: starting block address of buffers to हटाओ
 * @blen: length of buffers to be हटाओd
 *
 * This function is called from gfs2_journal wipe, whose job is to हटाओ
 * buffers, corresponding to deleted blocks, from the journal. If we find any
 * bufdata elements on the प्रणाली ail1 list, they haven't been written to
 * the journal yet. So we हटाओ them.
 */
अटल व्योम gfs2_ail1_wipe(काष्ठा gfs2_sbd *sdp, u64 bstart, u32 blen)
अणु
	काष्ठा gfs2_trans *tr, *s;
	काष्ठा gfs2_bufdata *bd, *bs;
	काष्ठा buffer_head *bh;
	u64 end = bstart + blen;

	gfs2_log_lock(sdp);
	spin_lock(&sdp->sd_ail_lock);
	list_क्रम_each_entry_safe(tr, s, &sdp->sd_ail1_list, tr_list) अणु
		list_क्रम_each_entry_safe(bd, bs, &tr->tr_ail1_list,
					 bd_ail_st_list) अणु
			bh = bd->bd_bh;
			अगर (bh->b_blocknr < bstart || bh->b_blocknr >= end)
				जारी;

			gfs2_हटाओ_from_journal(bh, REMOVE_JDATA);
		पूर्ण
	पूर्ण
	spin_unlock(&sdp->sd_ail_lock);
	gfs2_log_unlock(sdp);
पूर्ण

अटल काष्ठा buffer_head *gfs2_getjdatabuf(काष्ठा gfs2_inode *ip, u64 blkno)
अणु
	काष्ठा address_space *mapping = ip->i_inode.i_mapping;
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा page *page;
	काष्ठा buffer_head *bh;
	अचिन्हित पूर्णांक shअगरt = PAGE_SHIFT - sdp->sd_sb.sb_bsize_shअगरt;
	अचिन्हित दीर्घ index = blkno >> shअगरt; /* convert block to page */
	अचिन्हित पूर्णांक bufnum = blkno - (index << shअगरt);

	page = find_get_page_flags(mapping, index, FGP_LOCK|FGP_ACCESSED);
	अगर (!page)
		वापस शून्य;
	अगर (!page_has_buffers(page)) अणु
		unlock_page(page);
		put_page(page);
		वापस शून्य;
	पूर्ण
	/* Locate header क्रम our buffer within our page */
	क्रम (bh = page_buffers(page); bufnum--; bh = bh->b_this_page)
		/* Do nothing */;
	get_bh(bh);
	unlock_page(page);
	put_page(page);
	वापस bh;
पूर्ण

/**
 * gfs2_journal_wipe - make inode's buffers so they aren't dirty/pinned anymore
 * @ip: the inode who owns the buffers
 * @bstart: the first buffer in the run
 * @blen: the number of buffers in the run
 *
 */

व्योम gfs2_journal_wipe(काष्ठा gfs2_inode *ip, u64 bstart, u32 blen)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा buffer_head *bh;
	पूर्णांक ty;

	gfs2_ail1_wipe(sdp, bstart, blen);
	जबतक (blen) अणु
		ty = REMOVE_META;
		bh = gfs2_getbuf(ip->i_gl, bstart, NO_CREATE);
		अगर (!bh && gfs2_is_jdata(ip)) अणु
			bh = gfs2_getjdatabuf(ip, bstart);
			ty = REMOVE_JDATA;
		पूर्ण
		अगर (bh) अणु
			lock_buffer(bh);
			gfs2_log_lock(sdp);
			spin_lock(&sdp->sd_ail_lock);
			gfs2_हटाओ_from_journal(bh, ty);
			spin_unlock(&sdp->sd_ail_lock);
			gfs2_log_unlock(sdp);
			unlock_buffer(bh);
			brअन्यथा(bh);
		पूर्ण

		bstart++;
		blen--;
	पूर्ण
पूर्ण

/**
 * gfs2_meta_buffer - Get a metadata buffer
 * @ip: The GFS2 inode
 * @mtype: The block type (GFS2_METATYPE_*)
 * @num: The block number (device relative) of the buffer
 * @bhp: the buffer is वापसed here
 *
 * Returns: त्रुटि_सं
 */

पूर्णांक gfs2_meta_buffer(काष्ठा gfs2_inode *ip, u32 mtype, u64 num,
		     काष्ठा buffer_head **bhp)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा gfs2_glock *gl = ip->i_gl;
	काष्ठा buffer_head *bh;
	पूर्णांक ret = 0;
	पूर्णांक rahead = 0;

	अगर (num == ip->i_no_addr)
		rahead = ip->i_rahead;

	ret = gfs2_meta_पढ़ो(gl, num, DIO_WAIT, rahead, &bh);
	अगर (ret == 0 && gfs2_metatype_check(sdp, bh, mtype)) अणु
		brअन्यथा(bh);
		ret = -EIO;
	पूर्ण अन्यथा अणु
		*bhp = bh;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * gfs2_meta_ra - start पढ़ोahead on an extent of a file
 * @gl: the glock the blocks beदीर्घ to
 * @dblock: the starting disk block
 * @extlen: the number of blocks in the extent
 *
 * वापसs: the first buffer in the extent
 */

काष्ठा buffer_head *gfs2_meta_ra(काष्ठा gfs2_glock *gl, u64 dblock, u32 extlen)
अणु
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	काष्ठा buffer_head *first_bh, *bh;
	u32 max_ra = gfs2_tune_get(sdp, gt_max_पढ़ोahead) >>
			  sdp->sd_sb.sb_bsize_shअगरt;

	BUG_ON(!extlen);

	अगर (max_ra < 1)
		max_ra = 1;
	अगर (extlen > max_ra)
		extlen = max_ra;

	first_bh = gfs2_getbuf(gl, dblock, CREATE);

	अगर (buffer_uptodate(first_bh))
		जाओ out;
	अगर (!buffer_locked(first_bh))
		ll_rw_block(REQ_OP_READ, REQ_META | REQ_PRIO, 1, &first_bh);

	dblock++;
	extlen--;

	जबतक (extlen) अणु
		bh = gfs2_getbuf(gl, dblock, CREATE);

		अगर (!buffer_uptodate(bh) && !buffer_locked(bh))
			ll_rw_block(REQ_OP_READ,
				    REQ_RAHEAD | REQ_META | REQ_PRIO,
				    1, &bh);
		brअन्यथा(bh);
		dblock++;
		extlen--;
		अगर (!buffer_locked(first_bh) && buffer_uptodate(first_bh))
			जाओ out;
	पूर्ण

	रुको_on_buffer(first_bh);
out:
	वापस first_bh;
पूर्ण

