<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * segment.c - NILFS segment स्थिरructor.
 *
 * Copyright (C) 2005-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Ryusuke Konishi.
 *
 */

#समावेश <linux/pagemap.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bपन.स>
#समावेश <linux/completion.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/crc32.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>

#समावेश "nilfs.h"
#समावेश "btnode.h"
#समावेश "page.h"
#समावेश "segment.h"
#समावेश "sufile.h"
#समावेश "cpfile.h"
#समावेश "ifile.h"
#समावेश "segbuf.h"


/*
 * Segment स्थिरructor
 */
#घोषणा SC_N_INODEVEC	16   /* Size of locally allocated inode vector */

#घोषणा SC_MAX_SEGDELTA 64   /*
			      * Upper limit of the number of segments
			      * appended in collection retry loop
			      */

/* Conकाष्ठाion mode */
क्रमागत अणु
	SC_LSEG_SR = 1,	/* Make a logical segment having a super root */
	SC_LSEG_DSYNC,	/*
			 * Flush data blocks of a given file and make
			 * a logical segment without a super root.
			 */
	SC_FLUSH_खाता,	/*
			 * Flush data files, leads to segment ग_लिखोs without
			 * creating a checkpoपूर्णांक.
			 */
	SC_FLUSH_DAT,	/*
			 * Flush DAT file.  This also creates segments
			 * without a checkpoपूर्णांक.
			 */
पूर्ण;

/* Stage numbers of dirty block collection */
क्रमागत अणु
	NILFS_ST_INIT = 0,
	NILFS_ST_GC,		/* Collecting dirty blocks क्रम GC */
	NILFS_ST_खाता,
	NILFS_ST_Iखाता,
	NILFS_ST_CPखाता,
	NILFS_ST_SUखाता,
	NILFS_ST_DAT,
	NILFS_ST_SR,		/* Super root */
	NILFS_ST_DSYNC,		/* Data sync blocks */
	NILFS_ST_DONE,
पूर्ण;

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/nilfs2.h>

/*
 * nilfs_sc_cstage_inc(), nilfs_sc_cstage_set(), nilfs_sc_cstage_get() are
 * wrapper functions of stage count (nilfs_sc_info->sc_stage.scnt). Users of
 * the variable must use them because transition of stage count must involve
 * trace events (trace_nilfs2_collection_stage_transition).
 *
 * nilfs_sc_cstage_get() isn't required for the above purpose because it doesn't
 * produce tracepoपूर्णांक events. It is provided just क्रम making the पूर्णांकention
 * clear.
 */
अटल अंतरभूत व्योम nilfs_sc_cstage_inc(काष्ठा nilfs_sc_info *sci)
अणु
	sci->sc_stage.scnt++;
	trace_nilfs2_collection_stage_transition(sci);
पूर्ण

अटल अंतरभूत व्योम nilfs_sc_cstage_set(काष्ठा nilfs_sc_info *sci, पूर्णांक next_scnt)
अणु
	sci->sc_stage.scnt = next_scnt;
	trace_nilfs2_collection_stage_transition(sci);
पूर्ण

अटल अंतरभूत पूर्णांक nilfs_sc_cstage_get(काष्ठा nilfs_sc_info *sci)
अणु
	वापस sci->sc_stage.scnt;
पूर्ण

/* State flags of collection */
#घोषणा NILFS_CF_NODE		0x0001	/* Collecting node blocks */
#घोषणा NILFS_CF_Iखाता_STARTED	0x0002	/* Iखाता stage has started */
#घोषणा NILFS_CF_SUFREED	0x0004	/* segment usages has been मुक्तd */
#घोषणा NILFS_CF_HISTORY_MASK	(NILFS_CF_Iखाता_STARTED | NILFS_CF_SUFREED)

/* Operations depending on the स्थिरruction mode and file type */
काष्ठा nilfs_sc_operations अणु
	पूर्णांक (*collect_data)(काष्ठा nilfs_sc_info *, काष्ठा buffer_head *,
			    काष्ठा inode *);
	पूर्णांक (*collect_node)(काष्ठा nilfs_sc_info *, काष्ठा buffer_head *,
			    काष्ठा inode *);
	पूर्णांक (*collect_bmap)(काष्ठा nilfs_sc_info *, काष्ठा buffer_head *,
			    काष्ठा inode *);
	व्योम (*ग_लिखो_data_binfo)(काष्ठा nilfs_sc_info *,
				 काष्ठा nilfs_segsum_poपूर्णांकer *,
				 जोड़ nilfs_binfo *);
	व्योम (*ग_लिखो_node_binfo)(काष्ठा nilfs_sc_info *,
				 काष्ठा nilfs_segsum_poपूर्णांकer *,
				 जोड़ nilfs_binfo *);
पूर्ण;

/*
 * Other definitions
 */
अटल व्योम nilfs_segctor_start_समयr(काष्ठा nilfs_sc_info *);
अटल व्योम nilfs_segctor_करो_flush(काष्ठा nilfs_sc_info *, पूर्णांक);
अटल व्योम nilfs_segctor_करो_immediate_flush(काष्ठा nilfs_sc_info *);
अटल व्योम nilfs_dispose_list(काष्ठा the_nilfs *, काष्ठा list_head *, पूर्णांक);

#घोषणा nilfs_cnt32_ge(a, b)   \
	(typecheck(__u32, a) && typecheck(__u32, b) && \
	 ((__s32)(a) - (__s32)(b) >= 0))

अटल पूर्णांक nilfs_prepare_segment_lock(काष्ठा super_block *sb,
				      काष्ठा nilfs_transaction_info *ti)
अणु
	काष्ठा nilfs_transaction_info *cur_ti = current->journal_info;
	व्योम *save = शून्य;

	अगर (cur_ti) अणु
		अगर (cur_ti->ti_magic == NILFS_TI_MAGIC)
			वापस ++cur_ti->ti_count;

		/*
		 * If journal_info field is occupied by other FS,
		 * it is saved and will be restored on
		 * nilfs_transaction_commit().
		 */
		nilfs_warn(sb, "journal info from a different FS");
		save = current->journal_info;
	पूर्ण
	अगर (!ti) अणु
		ti = kmem_cache_alloc(nilfs_transaction_cachep, GFP_NOFS);
		अगर (!ti)
			वापस -ENOMEM;
		ti->ti_flags = NILFS_TI_DYNAMIC_ALLOC;
	पूर्ण अन्यथा अणु
		ti->ti_flags = 0;
	पूर्ण
	ti->ti_count = 0;
	ti->ti_save = save;
	ti->ti_magic = NILFS_TI_MAGIC;
	current->journal_info = ti;
	वापस 0;
पूर्ण

/**
 * nilfs_transaction_begin - start inभागisible file operations.
 * @sb: super block
 * @ti: nilfs_transaction_info
 * @vacancy_check: flags क्रम vacancy rate checks
 *
 * nilfs_transaction_begin() acquires a पढ़ोer/ग_लिखोr semaphore, called
 * the segment semaphore, to make a segment स्थिरruction and ग_लिखो tasks
 * exclusive.  The function is used with nilfs_transaction_commit() in pairs.
 * The region enबंदd by these two functions can be nested.  To aव्योम a
 * deadlock, the semaphore is only acquired or released in the outermost call.
 *
 * This function allocates a nilfs_transaction_info काष्ठा to keep context
 * inक्रमmation on it.  It is initialized and hooked onto the current task in
 * the outermost call.  If a pre-allocated काष्ठा is given to @ti, it is used
 * instead; otherwise a new काष्ठा is asचिन्हित from a slab.
 *
 * When @vacancy_check flag is set, this function will check the amount of
 * मुक्त space, and will रुको क्रम the GC to reclaim disk space अगर low capacity.
 *
 * Return Value: On success, 0 is वापसed. On error, one of the following
 * negative error code is वापसed.
 *
 * %-ENOMEM - Insufficient memory available.
 *
 * %-ENOSPC - No space left on device
 */
पूर्णांक nilfs_transaction_begin(काष्ठा super_block *sb,
			    काष्ठा nilfs_transaction_info *ti,
			    पूर्णांक vacancy_check)
अणु
	काष्ठा the_nilfs *nilfs;
	पूर्णांक ret = nilfs_prepare_segment_lock(sb, ti);
	काष्ठा nilfs_transaction_info *trace_ti;

	अगर (unlikely(ret < 0))
		वापस ret;
	अगर (ret > 0) अणु
		trace_ti = current->journal_info;

		trace_nilfs2_transaction_transition(sb, trace_ti,
				    trace_ti->ti_count, trace_ti->ti_flags,
				    TRACE_NILFS2_TRANSACTION_BEGIN);
		वापस 0;
	पूर्ण

	sb_start_पूर्णांकग_लिखो(sb);

	nilfs = sb->s_fs_info;
	करोwn_पढ़ो(&nilfs->ns_segctor_sem);
	अगर (vacancy_check && nilfs_near_disk_full(nilfs)) अणु
		up_पढ़ो(&nilfs->ns_segctor_sem);
		ret = -ENOSPC;
		जाओ failed;
	पूर्ण

	trace_ti = current->journal_info;
	trace_nilfs2_transaction_transition(sb, trace_ti, trace_ti->ti_count,
					    trace_ti->ti_flags,
					    TRACE_NILFS2_TRANSACTION_BEGIN);
	वापस 0;

 failed:
	ti = current->journal_info;
	current->journal_info = ti->ti_save;
	अगर (ti->ti_flags & NILFS_TI_DYNAMIC_ALLOC)
		kmem_cache_मुक्त(nilfs_transaction_cachep, ti);
	sb_end_पूर्णांकग_लिखो(sb);
	वापस ret;
पूर्ण

/**
 * nilfs_transaction_commit - commit inभागisible file operations.
 * @sb: super block
 *
 * nilfs_transaction_commit() releases the पढ़ो semaphore which is
 * acquired by nilfs_transaction_begin(). This is only perक्रमmed
 * in outermost call of this function.  If a commit flag is set,
 * nilfs_transaction_commit() sets a समयr to start the segment
 * स्थिरructor.  If a sync flag is set, it starts स्थिरruction
 * directly.
 */
पूर्णांक nilfs_transaction_commit(काष्ठा super_block *sb)
अणु
	काष्ठा nilfs_transaction_info *ti = current->journal_info;
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	पूर्णांक err = 0;

	BUG_ON(ti == शून्य || ti->ti_magic != NILFS_TI_MAGIC);
	ti->ti_flags |= NILFS_TI_COMMIT;
	अगर (ti->ti_count > 0) अणु
		ti->ti_count--;
		trace_nilfs2_transaction_transition(sb, ti, ti->ti_count,
			    ti->ti_flags, TRACE_NILFS2_TRANSACTION_COMMIT);
		वापस 0;
	पूर्ण
	अगर (nilfs->ns_ग_लिखोr) अणु
		काष्ठा nilfs_sc_info *sci = nilfs->ns_ग_लिखोr;

		अगर (ti->ti_flags & NILFS_TI_COMMIT)
			nilfs_segctor_start_समयr(sci);
		अगर (atomic_पढ़ो(&nilfs->ns_ndirtyblks) > sci->sc_watermark)
			nilfs_segctor_करो_flush(sci, 0);
	पूर्ण
	up_पढ़ो(&nilfs->ns_segctor_sem);
	trace_nilfs2_transaction_transition(sb, ti, ti->ti_count,
			    ti->ti_flags, TRACE_NILFS2_TRANSACTION_COMMIT);

	current->journal_info = ti->ti_save;

	अगर (ti->ti_flags & NILFS_TI_SYNC)
		err = nilfs_स्थिरruct_segment(sb);
	अगर (ti->ti_flags & NILFS_TI_DYNAMIC_ALLOC)
		kmem_cache_मुक्त(nilfs_transaction_cachep, ti);
	sb_end_पूर्णांकग_लिखो(sb);
	वापस err;
पूर्ण

व्योम nilfs_transaction_पात(काष्ठा super_block *sb)
अणु
	काष्ठा nilfs_transaction_info *ti = current->journal_info;
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;

	BUG_ON(ti == शून्य || ti->ti_magic != NILFS_TI_MAGIC);
	अगर (ti->ti_count > 0) अणु
		ti->ti_count--;
		trace_nilfs2_transaction_transition(sb, ti, ti->ti_count,
			    ti->ti_flags, TRACE_NILFS2_TRANSACTION_ABORT);
		वापस;
	पूर्ण
	up_पढ़ो(&nilfs->ns_segctor_sem);

	trace_nilfs2_transaction_transition(sb, ti, ti->ti_count,
		    ti->ti_flags, TRACE_NILFS2_TRANSACTION_ABORT);

	current->journal_info = ti->ti_save;
	अगर (ti->ti_flags & NILFS_TI_DYNAMIC_ALLOC)
		kmem_cache_मुक्त(nilfs_transaction_cachep, ti);
	sb_end_पूर्णांकग_लिखो(sb);
पूर्ण

व्योम nilfs_relax_pressure_in_lock(काष्ठा super_block *sb)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा nilfs_sc_info *sci = nilfs->ns_ग_लिखोr;

	अगर (!sci || !sci->sc_flush_request)
		वापस;

	set_bit(NILFS_SC_PRIOR_FLUSH, &sci->sc_flags);
	up_पढ़ो(&nilfs->ns_segctor_sem);

	करोwn_ग_लिखो(&nilfs->ns_segctor_sem);
	अगर (sci->sc_flush_request &&
	    test_bit(NILFS_SC_PRIOR_FLUSH, &sci->sc_flags)) अणु
		काष्ठा nilfs_transaction_info *ti = current->journal_info;

		ti->ti_flags |= NILFS_TI_WRITER;
		nilfs_segctor_करो_immediate_flush(sci);
		ti->ti_flags &= ~NILFS_TI_WRITER;
	पूर्ण
	करोwngrade_ग_लिखो(&nilfs->ns_segctor_sem);
पूर्ण

अटल व्योम nilfs_transaction_lock(काष्ठा super_block *sb,
				   काष्ठा nilfs_transaction_info *ti,
				   पूर्णांक gcflag)
अणु
	काष्ठा nilfs_transaction_info *cur_ti = current->journal_info;
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा nilfs_sc_info *sci = nilfs->ns_ग_लिखोr;

	WARN_ON(cur_ti);
	ti->ti_flags = NILFS_TI_WRITER;
	ti->ti_count = 0;
	ti->ti_save = cur_ti;
	ti->ti_magic = NILFS_TI_MAGIC;
	current->journal_info = ti;

	क्रम (;;) अणु
		trace_nilfs2_transaction_transition(sb, ti, ti->ti_count,
			    ti->ti_flags, TRACE_NILFS2_TRANSACTION_TRYLOCK);

		करोwn_ग_लिखो(&nilfs->ns_segctor_sem);
		अगर (!test_bit(NILFS_SC_PRIOR_FLUSH, &sci->sc_flags))
			अवरोध;

		nilfs_segctor_करो_immediate_flush(sci);

		up_ग_लिखो(&nilfs->ns_segctor_sem);
		cond_resched();
	पूर्ण
	अगर (gcflag)
		ti->ti_flags |= NILFS_TI_GC;

	trace_nilfs2_transaction_transition(sb, ti, ti->ti_count,
			    ti->ti_flags, TRACE_NILFS2_TRANSACTION_LOCK);
पूर्ण

अटल व्योम nilfs_transaction_unlock(काष्ठा super_block *sb)
अणु
	काष्ठा nilfs_transaction_info *ti = current->journal_info;
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;

	BUG_ON(ti == शून्य || ti->ti_magic != NILFS_TI_MAGIC);
	BUG_ON(ti->ti_count > 0);

	up_ग_लिखो(&nilfs->ns_segctor_sem);
	current->journal_info = ti->ti_save;

	trace_nilfs2_transaction_transition(sb, ti, ti->ti_count,
			    ti->ti_flags, TRACE_NILFS2_TRANSACTION_UNLOCK);
पूर्ण

अटल व्योम *nilfs_segctor_map_segsum_entry(काष्ठा nilfs_sc_info *sci,
					    काष्ठा nilfs_segsum_poपूर्णांकer *ssp,
					    अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा nilfs_segment_buffer *segbuf = sci->sc_curseg;
	अचिन्हित पूर्णांक blocksize = sci->sc_super->s_blocksize;
	व्योम *p;

	अगर (unlikely(ssp->offset + bytes > blocksize)) अणु
		ssp->offset = 0;
		BUG_ON(NILFS_SEGBUF_BH_IS_LAST(ssp->bh,
					       &segbuf->sb_segsum_buffers));
		ssp->bh = NILFS_SEGBUF_NEXT_BH(ssp->bh);
	पूर्ण
	p = ssp->bh->b_data + ssp->offset;
	ssp->offset += bytes;
	वापस p;
पूर्ण

/**
 * nilfs_segctor_reset_segment_buffer - reset the current segment buffer
 * @sci: nilfs_sc_info
 */
अटल पूर्णांक nilfs_segctor_reset_segment_buffer(काष्ठा nilfs_sc_info *sci)
अणु
	काष्ठा nilfs_segment_buffer *segbuf = sci->sc_curseg;
	काष्ठा buffer_head *sumbh;
	अचिन्हित पूर्णांक sumbytes;
	अचिन्हित पूर्णांक flags = 0;
	पूर्णांक err;

	अगर (nilfs_करोing_gc())
		flags = NILFS_SS_GC;
	err = nilfs_segbuf_reset(segbuf, flags, sci->sc_seg_स_समय, sci->sc_cno);
	अगर (unlikely(err))
		वापस err;

	sumbh = NILFS_SEGBUF_FIRST_BH(&segbuf->sb_segsum_buffers);
	sumbytes = segbuf->sb_sum.sumbytes;
	sci->sc_finfo_ptr.bh = sumbh;  sci->sc_finfo_ptr.offset = sumbytes;
	sci->sc_binfo_ptr.bh = sumbh;  sci->sc_binfo_ptr.offset = sumbytes;
	sci->sc_blk_cnt = sci->sc_datablk_cnt = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_segctor_feed_segment(काष्ठा nilfs_sc_info *sci)
अणु
	sci->sc_nblk_this_inc += sci->sc_curseg->sb_sum.nblocks;
	अगर (NILFS_SEGBUF_IS_LAST(sci->sc_curseg, &sci->sc_segbufs))
		वापस -E2BIG; /*
				* The current segment is filled up
				* (पूर्णांकernal code)
				*/
	sci->sc_curseg = NILFS_NEXT_SEGBUF(sci->sc_curseg);
	वापस nilfs_segctor_reset_segment_buffer(sci);
पूर्ण

अटल पूर्णांक nilfs_segctor_add_super_root(काष्ठा nilfs_sc_info *sci)
अणु
	काष्ठा nilfs_segment_buffer *segbuf = sci->sc_curseg;
	पूर्णांक err;

	अगर (segbuf->sb_sum.nblocks >= segbuf->sb_rest_blocks) अणु
		err = nilfs_segctor_feed_segment(sci);
		अगर (err)
			वापस err;
		segbuf = sci->sc_curseg;
	पूर्ण
	err = nilfs_segbuf_extend_payload(segbuf, &segbuf->sb_super_root);
	अगर (likely(!err))
		segbuf->sb_sum.flags |= NILFS_SS_SR;
	वापस err;
पूर्ण

/*
 * Functions क्रम making segment summary and payloads
 */
अटल पूर्णांक nilfs_segctor_segsum_block_required(
	काष्ठा nilfs_sc_info *sci, स्थिर काष्ठा nilfs_segsum_poपूर्णांकer *ssp,
	अचिन्हित पूर्णांक binfo_size)
अणु
	अचिन्हित पूर्णांक blocksize = sci->sc_super->s_blocksize;
	/* Size of finfo and binfo is enough small against blocksize */

	वापस ssp->offset + binfo_size +
		(!sci->sc_blk_cnt ? माप(काष्ठा nilfs_finfo) : 0) >
		blocksize;
पूर्ण

अटल व्योम nilfs_segctor_begin_finfo(काष्ठा nilfs_sc_info *sci,
				      काष्ठा inode *inode)
अणु
	sci->sc_curseg->sb_sum.nfinfo++;
	sci->sc_binfo_ptr = sci->sc_finfo_ptr;
	nilfs_segctor_map_segsum_entry(
		sci, &sci->sc_binfo_ptr, माप(काष्ठा nilfs_finfo));

	अगर (NILFS_I(inode)->i_root &&
	    !test_bit(NILFS_SC_HAVE_DELTA, &sci->sc_flags))
		set_bit(NILFS_SC_HAVE_DELTA, &sci->sc_flags);
	/* skip finfo */
पूर्ण

अटल व्योम nilfs_segctor_end_finfo(काष्ठा nilfs_sc_info *sci,
				    काष्ठा inode *inode)
अणु
	काष्ठा nilfs_finfo *finfo;
	काष्ठा nilfs_inode_info *ii;
	काष्ठा nilfs_segment_buffer *segbuf;
	__u64 cno;

	अगर (sci->sc_blk_cnt == 0)
		वापस;

	ii = NILFS_I(inode);

	अगर (test_bit(NILFS_I_GCINODE, &ii->i_state))
		cno = ii->i_cno;
	अन्यथा अगर (NILFS_ROOT_METADATA_खाता(inode->i_ino))
		cno = 0;
	अन्यथा
		cno = sci->sc_cno;

	finfo = nilfs_segctor_map_segsum_entry(sci, &sci->sc_finfo_ptr,
						 माप(*finfo));
	finfo->fi_ino = cpu_to_le64(inode->i_ino);
	finfo->fi_nblocks = cpu_to_le32(sci->sc_blk_cnt);
	finfo->fi_ndatablk = cpu_to_le32(sci->sc_datablk_cnt);
	finfo->fi_cno = cpu_to_le64(cno);

	segbuf = sci->sc_curseg;
	segbuf->sb_sum.sumbytes = sci->sc_binfo_ptr.offset +
		sci->sc_super->s_blocksize * (segbuf->sb_sum.nsumblk - 1);
	sci->sc_finfo_ptr = sci->sc_binfo_ptr;
	sci->sc_blk_cnt = sci->sc_datablk_cnt = 0;
पूर्ण

अटल पूर्णांक nilfs_segctor_add_file_block(काष्ठा nilfs_sc_info *sci,
					काष्ठा buffer_head *bh,
					काष्ठा inode *inode,
					अचिन्हित पूर्णांक binfo_size)
अणु
	काष्ठा nilfs_segment_buffer *segbuf;
	पूर्णांक required, err = 0;

 retry:
	segbuf = sci->sc_curseg;
	required = nilfs_segctor_segsum_block_required(
		sci, &sci->sc_binfo_ptr, binfo_size);
	अगर (segbuf->sb_sum.nblocks + required + 1 > segbuf->sb_rest_blocks) अणु
		nilfs_segctor_end_finfo(sci, inode);
		err = nilfs_segctor_feed_segment(sci);
		अगर (err)
			वापस err;
		जाओ retry;
	पूर्ण
	अगर (unlikely(required)) अणु
		err = nilfs_segbuf_extend_segsum(segbuf);
		अगर (unlikely(err))
			जाओ failed;
	पूर्ण
	अगर (sci->sc_blk_cnt == 0)
		nilfs_segctor_begin_finfo(sci, inode);

	nilfs_segctor_map_segsum_entry(sci, &sci->sc_binfo_ptr, binfo_size);
	/* Substitution to vblocknr is delayed until update_blocknr() */
	nilfs_segbuf_add_file_buffer(segbuf, bh);
	sci->sc_blk_cnt++;
 failed:
	वापस err;
पूर्ण

/*
 * Callback functions that क्रमागतerate, mark, and collect dirty blocks
 */
अटल पूर्णांक nilfs_collect_file_data(काष्ठा nilfs_sc_info *sci,
				   काष्ठा buffer_head *bh, काष्ठा inode *inode)
अणु
	पूर्णांक err;

	err = nilfs_bmap_propagate(NILFS_I(inode)->i_bmap, bh);
	अगर (err < 0)
		वापस err;

	err = nilfs_segctor_add_file_block(sci, bh, inode,
					   माप(काष्ठा nilfs_binfo_v));
	अगर (!err)
		sci->sc_datablk_cnt++;
	वापस err;
पूर्ण

अटल पूर्णांक nilfs_collect_file_node(काष्ठा nilfs_sc_info *sci,
				   काष्ठा buffer_head *bh,
				   काष्ठा inode *inode)
अणु
	वापस nilfs_bmap_propagate(NILFS_I(inode)->i_bmap, bh);
पूर्ण

अटल पूर्णांक nilfs_collect_file_bmap(काष्ठा nilfs_sc_info *sci,
				   काष्ठा buffer_head *bh,
				   काष्ठा inode *inode)
अणु
	WARN_ON(!buffer_dirty(bh));
	वापस nilfs_segctor_add_file_block(sci, bh, inode, माप(__le64));
पूर्ण

अटल व्योम nilfs_ग_लिखो_file_data_binfo(काष्ठा nilfs_sc_info *sci,
					काष्ठा nilfs_segsum_poपूर्णांकer *ssp,
					जोड़ nilfs_binfo *binfo)
अणु
	काष्ठा nilfs_binfo_v *binfo_v = nilfs_segctor_map_segsum_entry(
		sci, ssp, माप(*binfo_v));
	*binfo_v = binfo->bi_v;
पूर्ण

अटल व्योम nilfs_ग_लिखो_file_node_binfo(काष्ठा nilfs_sc_info *sci,
					काष्ठा nilfs_segsum_poपूर्णांकer *ssp,
					जोड़ nilfs_binfo *binfo)
अणु
	__le64 *vblocknr = nilfs_segctor_map_segsum_entry(
		sci, ssp, माप(*vblocknr));
	*vblocknr = binfo->bi_v.bi_vblocknr;
पूर्ण

अटल स्थिर काष्ठा nilfs_sc_operations nilfs_sc_file_ops = अणु
	.collect_data = nilfs_collect_file_data,
	.collect_node = nilfs_collect_file_node,
	.collect_bmap = nilfs_collect_file_bmap,
	.ग_लिखो_data_binfo = nilfs_ग_लिखो_file_data_binfo,
	.ग_लिखो_node_binfo = nilfs_ग_लिखो_file_node_binfo,
पूर्ण;

अटल पूर्णांक nilfs_collect_dat_data(काष्ठा nilfs_sc_info *sci,
				  काष्ठा buffer_head *bh, काष्ठा inode *inode)
अणु
	पूर्णांक err;

	err = nilfs_bmap_propagate(NILFS_I(inode)->i_bmap, bh);
	अगर (err < 0)
		वापस err;

	err = nilfs_segctor_add_file_block(sci, bh, inode, माप(__le64));
	अगर (!err)
		sci->sc_datablk_cnt++;
	वापस err;
पूर्ण

अटल पूर्णांक nilfs_collect_dat_bmap(काष्ठा nilfs_sc_info *sci,
				  काष्ठा buffer_head *bh, काष्ठा inode *inode)
अणु
	WARN_ON(!buffer_dirty(bh));
	वापस nilfs_segctor_add_file_block(sci, bh, inode,
					    माप(काष्ठा nilfs_binfo_dat));
पूर्ण

अटल व्योम nilfs_ग_लिखो_dat_data_binfo(काष्ठा nilfs_sc_info *sci,
				       काष्ठा nilfs_segsum_poपूर्णांकer *ssp,
				       जोड़ nilfs_binfo *binfo)
अणु
	__le64 *blkoff = nilfs_segctor_map_segsum_entry(sci, ssp,
							  माप(*blkoff));
	*blkoff = binfo->bi_dat.bi_blkoff;
पूर्ण

अटल व्योम nilfs_ग_लिखो_dat_node_binfo(काष्ठा nilfs_sc_info *sci,
				       काष्ठा nilfs_segsum_poपूर्णांकer *ssp,
				       जोड़ nilfs_binfo *binfo)
अणु
	काष्ठा nilfs_binfo_dat *binfo_dat =
		nilfs_segctor_map_segsum_entry(sci, ssp, माप(*binfo_dat));
	*binfo_dat = binfo->bi_dat;
पूर्ण

अटल स्थिर काष्ठा nilfs_sc_operations nilfs_sc_dat_ops = अणु
	.collect_data = nilfs_collect_dat_data,
	.collect_node = nilfs_collect_file_node,
	.collect_bmap = nilfs_collect_dat_bmap,
	.ग_लिखो_data_binfo = nilfs_ग_लिखो_dat_data_binfo,
	.ग_लिखो_node_binfo = nilfs_ग_लिखो_dat_node_binfo,
पूर्ण;

अटल स्थिर काष्ठा nilfs_sc_operations nilfs_sc_dsync_ops = अणु
	.collect_data = nilfs_collect_file_data,
	.collect_node = शून्य,
	.collect_bmap = शून्य,
	.ग_लिखो_data_binfo = nilfs_ग_लिखो_file_data_binfo,
	.ग_लिखो_node_binfo = शून्य,
पूर्ण;

अटल माप_प्रकार nilfs_lookup_dirty_data_buffers(काष्ठा inode *inode,
					      काष्ठा list_head *listp,
					      माप_प्रकार nlimit,
					      loff_t start, loff_t end)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा pagevec pvec;
	pgoff_t index = 0, last = अच_दीर्घ_उच्च;
	माप_प्रकार ndirties = 0;
	पूर्णांक i;

	अगर (unlikely(start != 0 || end != Lदीर्घ_उच्च)) अणु
		/*
		 * A valid range is given क्रम sync-ing data pages. The
		 * range is rounded to per-page; extra dirty buffers
		 * may be included अगर blocksize < pagesize.
		 */
		index = start >> PAGE_SHIFT;
		last = end >> PAGE_SHIFT;
	पूर्ण
	pagevec_init(&pvec);
 repeat:
	अगर (unlikely(index > last) ||
	    !pagevec_lookup_range_tag(&pvec, mapping, &index, last,
				PAGECACHE_TAG_सूचीTY))
		वापस ndirties;

	क्रम (i = 0; i < pagevec_count(&pvec); i++) अणु
		काष्ठा buffer_head *bh, *head;
		काष्ठा page *page = pvec.pages[i];

		lock_page(page);
		अगर (!page_has_buffers(page))
			create_empty_buffers(page, i_blocksize(inode), 0);
		unlock_page(page);

		bh = head = page_buffers(page);
		करो अणु
			अगर (!buffer_dirty(bh) || buffer_async_ग_लिखो(bh))
				जारी;
			get_bh(bh);
			list_add_tail(&bh->b_assoc_buffers, listp);
			ndirties++;
			अगर (unlikely(ndirties >= nlimit)) अणु
				pagevec_release(&pvec);
				cond_resched();
				वापस ndirties;
			पूर्ण
		पूर्ण जबतक (bh = bh->b_this_page, bh != head);
	पूर्ण
	pagevec_release(&pvec);
	cond_resched();
	जाओ repeat;
पूर्ण

अटल व्योम nilfs_lookup_dirty_node_buffers(काष्ठा inode *inode,
					    काष्ठा list_head *listp)
अणु
	काष्ठा nilfs_inode_info *ii = NILFS_I(inode);
	काष्ठा address_space *mapping = &ii->i_btnode_cache;
	काष्ठा pagevec pvec;
	काष्ठा buffer_head *bh, *head;
	अचिन्हित पूर्णांक i;
	pgoff_t index = 0;

	pagevec_init(&pvec);

	जबतक (pagevec_lookup_tag(&pvec, mapping, &index,
					PAGECACHE_TAG_सूचीTY)) अणु
		क्रम (i = 0; i < pagevec_count(&pvec); i++) अणु
			bh = head = page_buffers(pvec.pages[i]);
			करो अणु
				अगर (buffer_dirty(bh) &&
						!buffer_async_ग_लिखो(bh)) अणु
					get_bh(bh);
					list_add_tail(&bh->b_assoc_buffers,
						      listp);
				पूर्ण
				bh = bh->b_this_page;
			पूर्ण जबतक (bh != head);
		पूर्ण
		pagevec_release(&pvec);
		cond_resched();
	पूर्ण
पूर्ण

अटल व्योम nilfs_dispose_list(काष्ठा the_nilfs *nilfs,
			       काष्ठा list_head *head, पूर्णांक क्रमce)
अणु
	काष्ठा nilfs_inode_info *ii, *n;
	काष्ठा nilfs_inode_info *ivec[SC_N_INODEVEC], **pii;
	अचिन्हित पूर्णांक nv = 0;

	जबतक (!list_empty(head)) अणु
		spin_lock(&nilfs->ns_inode_lock);
		list_क्रम_each_entry_safe(ii, n, head, i_dirty) अणु
			list_del_init(&ii->i_dirty);
			अगर (क्रमce) अणु
				अगर (unlikely(ii->i_bh)) अणु
					brअन्यथा(ii->i_bh);
					ii->i_bh = शून्य;
				पूर्ण
			पूर्ण अन्यथा अगर (test_bit(NILFS_I_सूचीTY, &ii->i_state)) अणु
				set_bit(NILFS_I_QUEUED, &ii->i_state);
				list_add_tail(&ii->i_dirty,
					      &nilfs->ns_dirty_files);
				जारी;
			पूर्ण
			ivec[nv++] = ii;
			अगर (nv == SC_N_INODEVEC)
				अवरोध;
		पूर्ण
		spin_unlock(&nilfs->ns_inode_lock);

		क्रम (pii = ivec; nv > 0; pii++, nv--)
			iput(&(*pii)->vfs_inode);
	पूर्ण
पूर्ण

अटल व्योम nilfs_iput_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nilfs_sc_info *sci = container_of(work, काष्ठा nilfs_sc_info,
						 sc_iput_work);
	काष्ठा the_nilfs *nilfs = sci->sc_super->s_fs_info;

	nilfs_dispose_list(nilfs, &sci->sc_iput_queue, 0);
पूर्ण

अटल पूर्णांक nilfs_test_metadata_dirty(काष्ठा the_nilfs *nilfs,
				     काष्ठा nilfs_root *root)
अणु
	पूर्णांक ret = 0;

	अगर (nilfs_mdt_fetch_dirty(root->अगरile))
		ret++;
	अगर (nilfs_mdt_fetch_dirty(nilfs->ns_cpfile))
		ret++;
	अगर (nilfs_mdt_fetch_dirty(nilfs->ns_sufile))
		ret++;
	अगर ((ret || nilfs_करोing_gc()) && nilfs_mdt_fetch_dirty(nilfs->ns_dat))
		ret++;
	वापस ret;
पूर्ण

अटल पूर्णांक nilfs_segctor_clean(काष्ठा nilfs_sc_info *sci)
अणु
	वापस list_empty(&sci->sc_dirty_files) &&
		!test_bit(NILFS_SC_सूचीTY, &sci->sc_flags) &&
		sci->sc_nमुक्तsegs == 0 &&
		(!nilfs_करोing_gc() || list_empty(&sci->sc_gc_inodes));
पूर्ण

अटल पूर्णांक nilfs_segctor_confirm(काष्ठा nilfs_sc_info *sci)
अणु
	काष्ठा the_nilfs *nilfs = sci->sc_super->s_fs_info;
	पूर्णांक ret = 0;

	अगर (nilfs_test_metadata_dirty(nilfs, sci->sc_root))
		set_bit(NILFS_SC_सूचीTY, &sci->sc_flags);

	spin_lock(&nilfs->ns_inode_lock);
	अगर (list_empty(&nilfs->ns_dirty_files) && nilfs_segctor_clean(sci))
		ret++;

	spin_unlock(&nilfs->ns_inode_lock);
	वापस ret;
पूर्ण

अटल व्योम nilfs_segctor_clear_metadata_dirty(काष्ठा nilfs_sc_info *sci)
अणु
	काष्ठा the_nilfs *nilfs = sci->sc_super->s_fs_info;

	nilfs_mdt_clear_dirty(sci->sc_root->अगरile);
	nilfs_mdt_clear_dirty(nilfs->ns_cpfile);
	nilfs_mdt_clear_dirty(nilfs->ns_sufile);
	nilfs_mdt_clear_dirty(nilfs->ns_dat);
पूर्ण

अटल पूर्णांक nilfs_segctor_create_checkpoपूर्णांक(काष्ठा nilfs_sc_info *sci)
अणु
	काष्ठा the_nilfs *nilfs = sci->sc_super->s_fs_info;
	काष्ठा buffer_head *bh_cp;
	काष्ठा nilfs_checkpoपूर्णांक *raw_cp;
	पूर्णांक err;

	/* XXX: this पूर्णांकerface will be changed */
	err = nilfs_cpfile_get_checkpoपूर्णांक(nilfs->ns_cpfile, nilfs->ns_cno, 1,
					  &raw_cp, &bh_cp);
	अगर (likely(!err)) अणु
		/*
		 * The following code is duplicated with cpfile.  But, it is
		 * needed to collect the checkpoपूर्णांक even अगर it was not newly
		 * created.
		 */
		mark_buffer_dirty(bh_cp);
		nilfs_mdt_mark_dirty(nilfs->ns_cpfile);
		nilfs_cpfile_put_checkpoपूर्णांक(
			nilfs->ns_cpfile, nilfs->ns_cno, bh_cp);
	पूर्ण अन्यथा
		WARN_ON(err == -EINVAL || err == -ENOENT);

	वापस err;
पूर्ण

अटल पूर्णांक nilfs_segctor_fill_in_checkpoपूर्णांक(काष्ठा nilfs_sc_info *sci)
अणु
	काष्ठा the_nilfs *nilfs = sci->sc_super->s_fs_info;
	काष्ठा buffer_head *bh_cp;
	काष्ठा nilfs_checkpoपूर्णांक *raw_cp;
	पूर्णांक err;

	err = nilfs_cpfile_get_checkpoपूर्णांक(nilfs->ns_cpfile, nilfs->ns_cno, 0,
					  &raw_cp, &bh_cp);
	अगर (unlikely(err)) अणु
		WARN_ON(err == -EINVAL || err == -ENOENT);
		जाओ failed_ibh;
	पूर्ण
	raw_cp->cp_snapshot_list.ssl_next = 0;
	raw_cp->cp_snapshot_list.ssl_prev = 0;
	raw_cp->cp_inodes_count =
		cpu_to_le64(atomic64_पढ़ो(&sci->sc_root->inodes_count));
	raw_cp->cp_blocks_count =
		cpu_to_le64(atomic64_पढ़ो(&sci->sc_root->blocks_count));
	raw_cp->cp_nblk_inc =
		cpu_to_le64(sci->sc_nblk_inc + sci->sc_nblk_this_inc);
	raw_cp->cp_create = cpu_to_le64(sci->sc_seg_स_समय);
	raw_cp->cp_cno = cpu_to_le64(nilfs->ns_cno);

	अगर (test_bit(NILFS_SC_HAVE_DELTA, &sci->sc_flags))
		nilfs_checkpoपूर्णांक_clear_minor(raw_cp);
	अन्यथा
		nilfs_checkpoपूर्णांक_set_minor(raw_cp);

	nilfs_ग_लिखो_inode_common(sci->sc_root->अगरile,
				 &raw_cp->cp_अगरile_inode, 1);
	nilfs_cpfile_put_checkpoपूर्णांक(nilfs->ns_cpfile, nilfs->ns_cno, bh_cp);
	वापस 0;

 failed_ibh:
	वापस err;
पूर्ण

अटल व्योम nilfs_fill_in_file_bmap(काष्ठा inode *अगरile,
				    काष्ठा nilfs_inode_info *ii)

अणु
	काष्ठा buffer_head *ibh;
	काष्ठा nilfs_inode *raw_inode;

	अगर (test_bit(NILFS_I_BMAP, &ii->i_state)) अणु
		ibh = ii->i_bh;
		BUG_ON(!ibh);
		raw_inode = nilfs_अगरile_map_inode(अगरile, ii->vfs_inode.i_ino,
						  ibh);
		nilfs_bmap_ग_लिखो(ii->i_bmap, raw_inode);
		nilfs_अगरile_unmap_inode(अगरile, ii->vfs_inode.i_ino, ibh);
	पूर्ण
पूर्ण

अटल व्योम nilfs_segctor_fill_in_file_bmap(काष्ठा nilfs_sc_info *sci)
अणु
	काष्ठा nilfs_inode_info *ii;

	list_क्रम_each_entry(ii, &sci->sc_dirty_files, i_dirty) अणु
		nilfs_fill_in_file_bmap(sci->sc_root->अगरile, ii);
		set_bit(NILFS_I_COLLECTED, &ii->i_state);
	पूर्ण
पूर्ण

अटल व्योम nilfs_segctor_fill_in_super_root(काष्ठा nilfs_sc_info *sci,
					     काष्ठा the_nilfs *nilfs)
अणु
	काष्ठा buffer_head *bh_sr;
	काष्ठा nilfs_super_root *raw_sr;
	अचिन्हित पूर्णांक isz, srsz;

	bh_sr = NILFS_LAST_SEGBUF(&sci->sc_segbufs)->sb_super_root;
	raw_sr = (काष्ठा nilfs_super_root *)bh_sr->b_data;
	isz = nilfs->ns_inode_size;
	srsz = NILFS_SR_BYTES(isz);

	raw_sr->sr_bytes = cpu_to_le16(srsz);
	raw_sr->sr_nongc_स_समय
		= cpu_to_le64(nilfs_करोing_gc() ?
			      nilfs->ns_nongc_स_समय : sci->sc_seg_स_समय);
	raw_sr->sr_flags = 0;

	nilfs_ग_लिखो_inode_common(nilfs->ns_dat, (व्योम *)raw_sr +
				 NILFS_SR_DAT_OFFSET(isz), 1);
	nilfs_ग_लिखो_inode_common(nilfs->ns_cpfile, (व्योम *)raw_sr +
				 NILFS_SR_CPखाता_OFFSET(isz), 1);
	nilfs_ग_लिखो_inode_common(nilfs->ns_sufile, (व्योम *)raw_sr +
				 NILFS_SR_SUखाता_OFFSET(isz), 1);
	स_रखो((व्योम *)raw_sr + srsz, 0, nilfs->ns_blocksize - srsz);
पूर्ण

अटल व्योम nilfs_redirty_inodes(काष्ठा list_head *head)
अणु
	काष्ठा nilfs_inode_info *ii;

	list_क्रम_each_entry(ii, head, i_dirty) अणु
		अगर (test_bit(NILFS_I_COLLECTED, &ii->i_state))
			clear_bit(NILFS_I_COLLECTED, &ii->i_state);
	पूर्ण
पूर्ण

अटल व्योम nilfs_drop_collected_inodes(काष्ठा list_head *head)
अणु
	काष्ठा nilfs_inode_info *ii;

	list_क्रम_each_entry(ii, head, i_dirty) अणु
		अगर (!test_and_clear_bit(NILFS_I_COLLECTED, &ii->i_state))
			जारी;

		clear_bit(NILFS_I_INODE_SYNC, &ii->i_state);
		set_bit(NILFS_I_UPDATED, &ii->i_state);
	पूर्ण
पूर्ण

अटल पूर्णांक nilfs_segctor_apply_buffers(काष्ठा nilfs_sc_info *sci,
				       काष्ठा inode *inode,
				       काष्ठा list_head *listp,
				       पूर्णांक (*collect)(काष्ठा nilfs_sc_info *,
						      काष्ठा buffer_head *,
						      काष्ठा inode *))
अणु
	काष्ठा buffer_head *bh, *n;
	पूर्णांक err = 0;

	अगर (collect) अणु
		list_क्रम_each_entry_safe(bh, n, listp, b_assoc_buffers) अणु
			list_del_init(&bh->b_assoc_buffers);
			err = collect(sci, bh, inode);
			brअन्यथा(bh);
			अगर (unlikely(err))
				जाओ dispose_buffers;
		पूर्ण
		वापस 0;
	पूर्ण

 dispose_buffers:
	जबतक (!list_empty(listp)) अणु
		bh = list_first_entry(listp, काष्ठा buffer_head,
				      b_assoc_buffers);
		list_del_init(&bh->b_assoc_buffers);
		brअन्यथा(bh);
	पूर्ण
	वापस err;
पूर्ण

अटल माप_प्रकार nilfs_segctor_buffer_rest(काष्ठा nilfs_sc_info *sci)
अणु
	/* Reमुख्यing number of blocks within segment buffer */
	वापस sci->sc_segbuf_nblocks -
		(sci->sc_nblk_this_inc + sci->sc_curseg->sb_sum.nblocks);
पूर्ण

अटल पूर्णांक nilfs_segctor_scan_file(काष्ठा nilfs_sc_info *sci,
				   काष्ठा inode *inode,
				   स्थिर काष्ठा nilfs_sc_operations *sc_ops)
अणु
	LIST_HEAD(data_buffers);
	LIST_HEAD(node_buffers);
	पूर्णांक err;

	अगर (!(sci->sc_stage.flags & NILFS_CF_NODE)) अणु
		माप_प्रकार n, rest = nilfs_segctor_buffer_rest(sci);

		n = nilfs_lookup_dirty_data_buffers(
			inode, &data_buffers, rest + 1, 0, Lदीर्घ_उच्च);
		अगर (n > rest) अणु
			err = nilfs_segctor_apply_buffers(
				sci, inode, &data_buffers,
				sc_ops->collect_data);
			BUG_ON(!err); /* always receive -E2BIG or true error */
			जाओ अवरोध_or_fail;
		पूर्ण
	पूर्ण
	nilfs_lookup_dirty_node_buffers(inode, &node_buffers);

	अगर (!(sci->sc_stage.flags & NILFS_CF_NODE)) अणु
		err = nilfs_segctor_apply_buffers(
			sci, inode, &data_buffers, sc_ops->collect_data);
		अगर (unlikely(err)) अणु
			/* dispose node list */
			nilfs_segctor_apply_buffers(
				sci, inode, &node_buffers, शून्य);
			जाओ अवरोध_or_fail;
		पूर्ण
		sci->sc_stage.flags |= NILFS_CF_NODE;
	पूर्ण
	/* Collect node */
	err = nilfs_segctor_apply_buffers(
		sci, inode, &node_buffers, sc_ops->collect_node);
	अगर (unlikely(err))
		जाओ अवरोध_or_fail;

	nilfs_bmap_lookup_dirty_buffers(NILFS_I(inode)->i_bmap, &node_buffers);
	err = nilfs_segctor_apply_buffers(
		sci, inode, &node_buffers, sc_ops->collect_bmap);
	अगर (unlikely(err))
		जाओ अवरोध_or_fail;

	nilfs_segctor_end_finfo(sci, inode);
	sci->sc_stage.flags &= ~NILFS_CF_NODE;

 अवरोध_or_fail:
	वापस err;
पूर्ण

अटल पूर्णांक nilfs_segctor_scan_file_dsync(काष्ठा nilfs_sc_info *sci,
					 काष्ठा inode *inode)
अणु
	LIST_HEAD(data_buffers);
	माप_प्रकार n, rest = nilfs_segctor_buffer_rest(sci);
	पूर्णांक err;

	n = nilfs_lookup_dirty_data_buffers(inode, &data_buffers, rest + 1,
					    sci->sc_dsync_start,
					    sci->sc_dsync_end);

	err = nilfs_segctor_apply_buffers(sci, inode, &data_buffers,
					  nilfs_collect_file_data);
	अगर (!err) अणु
		nilfs_segctor_end_finfo(sci, inode);
		BUG_ON(n > rest);
		/* always receive -E2BIG or true error अगर n > rest */
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक nilfs_segctor_collect_blocks(काष्ठा nilfs_sc_info *sci, पूर्णांक mode)
अणु
	काष्ठा the_nilfs *nilfs = sci->sc_super->s_fs_info;
	काष्ठा list_head *head;
	काष्ठा nilfs_inode_info *ii;
	माप_प्रकार nकरोne;
	पूर्णांक err = 0;

	चयन (nilfs_sc_cstage_get(sci)) अणु
	हाल NILFS_ST_INIT:
		/* Pre-processes */
		sci->sc_stage.flags = 0;

		अगर (!test_bit(NILFS_SC_UNCLOSED, &sci->sc_flags)) अणु
			sci->sc_nblk_inc = 0;
			sci->sc_curseg->sb_sum.flags = NILFS_SS_LOGBGN;
			अगर (mode == SC_LSEG_DSYNC) अणु
				nilfs_sc_cstage_set(sci, NILFS_ST_DSYNC);
				जाओ dsync_mode;
			पूर्ण
		पूर्ण

		sci->sc_stage.dirty_file_ptr = शून्य;
		sci->sc_stage.gc_inode_ptr = शून्य;
		अगर (mode == SC_FLUSH_DAT) अणु
			nilfs_sc_cstage_set(sci, NILFS_ST_DAT);
			जाओ dat_stage;
		पूर्ण
		nilfs_sc_cstage_inc(sci);
		fallthrough;
	हाल NILFS_ST_GC:
		अगर (nilfs_करोing_gc()) अणु
			head = &sci->sc_gc_inodes;
			ii = list_prepare_entry(sci->sc_stage.gc_inode_ptr,
						head, i_dirty);
			list_क्रम_each_entry_जारी(ii, head, i_dirty) अणु
				err = nilfs_segctor_scan_file(
					sci, &ii->vfs_inode,
					&nilfs_sc_file_ops);
				अगर (unlikely(err)) अणु
					sci->sc_stage.gc_inode_ptr = list_entry(
						ii->i_dirty.prev,
						काष्ठा nilfs_inode_info,
						i_dirty);
					जाओ अवरोध_or_fail;
				पूर्ण
				set_bit(NILFS_I_COLLECTED, &ii->i_state);
			पूर्ण
			sci->sc_stage.gc_inode_ptr = शून्य;
		पूर्ण
		nilfs_sc_cstage_inc(sci);
		fallthrough;
	हाल NILFS_ST_खाता:
		head = &sci->sc_dirty_files;
		ii = list_prepare_entry(sci->sc_stage.dirty_file_ptr, head,
					i_dirty);
		list_क्रम_each_entry_जारी(ii, head, i_dirty) अणु
			clear_bit(NILFS_I_सूचीTY, &ii->i_state);

			err = nilfs_segctor_scan_file(sci, &ii->vfs_inode,
						      &nilfs_sc_file_ops);
			अगर (unlikely(err)) अणु
				sci->sc_stage.dirty_file_ptr =
					list_entry(ii->i_dirty.prev,
						   काष्ठा nilfs_inode_info,
						   i_dirty);
				जाओ अवरोध_or_fail;
			पूर्ण
			/* sci->sc_stage.dirty_file_ptr = NILFS_I(inode); */
			/* XXX: required ? */
		पूर्ण
		sci->sc_stage.dirty_file_ptr = शून्य;
		अगर (mode == SC_FLUSH_खाता) अणु
			nilfs_sc_cstage_set(sci, NILFS_ST_DONE);
			वापस 0;
		पूर्ण
		nilfs_sc_cstage_inc(sci);
		sci->sc_stage.flags |= NILFS_CF_Iखाता_STARTED;
		fallthrough;
	हाल NILFS_ST_Iखाता:
		err = nilfs_segctor_scan_file(sci, sci->sc_root->अगरile,
					      &nilfs_sc_file_ops);
		अगर (unlikely(err))
			अवरोध;
		nilfs_sc_cstage_inc(sci);
		/* Creating a checkpoपूर्णांक */
		err = nilfs_segctor_create_checkpoपूर्णांक(sci);
		अगर (unlikely(err))
			अवरोध;
		fallthrough;
	हाल NILFS_ST_CPखाता:
		err = nilfs_segctor_scan_file(sci, nilfs->ns_cpfile,
					      &nilfs_sc_file_ops);
		अगर (unlikely(err))
			अवरोध;
		nilfs_sc_cstage_inc(sci);
		fallthrough;
	हाल NILFS_ST_SUखाता:
		err = nilfs_sufile_मुक्तv(nilfs->ns_sufile, sci->sc_मुक्तsegs,
					 sci->sc_nमुक्तsegs, &nकरोne);
		अगर (unlikely(err)) अणु
			nilfs_sufile_cancel_मुक्तv(nilfs->ns_sufile,
						  sci->sc_मुक्तsegs, nकरोne,
						  शून्य);
			अवरोध;
		पूर्ण
		sci->sc_stage.flags |= NILFS_CF_SUFREED;

		err = nilfs_segctor_scan_file(sci, nilfs->ns_sufile,
					      &nilfs_sc_file_ops);
		अगर (unlikely(err))
			अवरोध;
		nilfs_sc_cstage_inc(sci);
		fallthrough;
	हाल NILFS_ST_DAT:
 dat_stage:
		err = nilfs_segctor_scan_file(sci, nilfs->ns_dat,
					      &nilfs_sc_dat_ops);
		अगर (unlikely(err))
			अवरोध;
		अगर (mode == SC_FLUSH_DAT) अणु
			nilfs_sc_cstage_set(sci, NILFS_ST_DONE);
			वापस 0;
		पूर्ण
		nilfs_sc_cstage_inc(sci);
		fallthrough;
	हाल NILFS_ST_SR:
		अगर (mode == SC_LSEG_SR) अणु
			/* Appending a super root */
			err = nilfs_segctor_add_super_root(sci);
			अगर (unlikely(err))
				अवरोध;
		पूर्ण
		/* End of a logical segment */
		sci->sc_curseg->sb_sum.flags |= NILFS_SS_LOGEND;
		nilfs_sc_cstage_set(sci, NILFS_ST_DONE);
		वापस 0;
	हाल NILFS_ST_DSYNC:
 dsync_mode:
		sci->sc_curseg->sb_sum.flags |= NILFS_SS_SYNDT;
		ii = sci->sc_dsync_inode;
		अगर (!test_bit(NILFS_I_BUSY, &ii->i_state))
			अवरोध;

		err = nilfs_segctor_scan_file_dsync(sci, &ii->vfs_inode);
		अगर (unlikely(err))
			अवरोध;
		sci->sc_curseg->sb_sum.flags |= NILFS_SS_LOGEND;
		nilfs_sc_cstage_set(sci, NILFS_ST_DONE);
		वापस 0;
	हाल NILFS_ST_DONE:
		वापस 0;
	शेष:
		BUG();
	पूर्ण

 अवरोध_or_fail:
	वापस err;
पूर्ण

/**
 * nilfs_segctor_begin_स्थिरruction - setup segment buffer to make a new log
 * @sci: nilfs_sc_info
 * @nilfs: nilfs object
 */
अटल पूर्णांक nilfs_segctor_begin_स्थिरruction(काष्ठा nilfs_sc_info *sci,
					    काष्ठा the_nilfs *nilfs)
अणु
	काष्ठा nilfs_segment_buffer *segbuf, *prev;
	__u64 nextnum;
	पूर्णांक err, alloc = 0;

	segbuf = nilfs_segbuf_new(sci->sc_super);
	अगर (unlikely(!segbuf))
		वापस -ENOMEM;

	अगर (list_empty(&sci->sc_ग_लिखो_logs)) अणु
		nilfs_segbuf_map(segbuf, nilfs->ns_segnum,
				 nilfs->ns_pseg_offset, nilfs);
		अगर (segbuf->sb_rest_blocks < NILFS_PSEG_MIN_BLOCKS) अणु
			nilfs_shअगरt_to_next_segment(nilfs);
			nilfs_segbuf_map(segbuf, nilfs->ns_segnum, 0, nilfs);
		पूर्ण

		segbuf->sb_sum.seg_seq = nilfs->ns_seg_seq;
		nextnum = nilfs->ns_nextnum;

		अगर (nilfs->ns_segnum == nilfs->ns_nextnum)
			/* Start from the head of a new full segment */
			alloc++;
	पूर्ण अन्यथा अणु
		/* Continue logs */
		prev = NILFS_LAST_SEGBUF(&sci->sc_ग_लिखो_logs);
		nilfs_segbuf_map_cont(segbuf, prev);
		segbuf->sb_sum.seg_seq = prev->sb_sum.seg_seq;
		nextnum = prev->sb_nextnum;

		अगर (segbuf->sb_rest_blocks < NILFS_PSEG_MIN_BLOCKS) अणु
			nilfs_segbuf_map(segbuf, prev->sb_nextnum, 0, nilfs);
			segbuf->sb_sum.seg_seq++;
			alloc++;
		पूर्ण
	पूर्ण

	err = nilfs_sufile_mark_dirty(nilfs->ns_sufile, segbuf->sb_segnum);
	अगर (err)
		जाओ failed;

	अगर (alloc) अणु
		err = nilfs_sufile_alloc(nilfs->ns_sufile, &nextnum);
		अगर (err)
			जाओ failed;
	पूर्ण
	nilfs_segbuf_set_next_segnum(segbuf, nextnum, nilfs);

	BUG_ON(!list_empty(&sci->sc_segbufs));
	list_add_tail(&segbuf->sb_list, &sci->sc_segbufs);
	sci->sc_segbuf_nblocks = segbuf->sb_rest_blocks;
	वापस 0;

 failed:
	nilfs_segbuf_मुक्त(segbuf);
	वापस err;
पूर्ण

अटल पूर्णांक nilfs_segctor_extend_segments(काष्ठा nilfs_sc_info *sci,
					 काष्ठा the_nilfs *nilfs, पूर्णांक nadd)
अणु
	काष्ठा nilfs_segment_buffer *segbuf, *prev;
	काष्ठा inode *sufile = nilfs->ns_sufile;
	__u64 nextnextnum;
	LIST_HEAD(list);
	पूर्णांक err, ret, i;

	prev = NILFS_LAST_SEGBUF(&sci->sc_segbufs);
	/*
	 * Since the segment specअगरied with nextnum might be allocated during
	 * the previous स्थिरruction, the buffer including its segusage may
	 * not be dirty.  The following call ensures that the buffer is dirty
	 * and will pin the buffer on memory until the sufile is written.
	 */
	err = nilfs_sufile_mark_dirty(sufile, prev->sb_nextnum);
	अगर (unlikely(err))
		वापस err;

	क्रम (i = 0; i < nadd; i++) अणु
		/* extend segment info */
		err = -ENOMEM;
		segbuf = nilfs_segbuf_new(sci->sc_super);
		अगर (unlikely(!segbuf))
			जाओ failed;

		/* map this buffer to region of segment on-disk */
		nilfs_segbuf_map(segbuf, prev->sb_nextnum, 0, nilfs);
		sci->sc_segbuf_nblocks += segbuf->sb_rest_blocks;

		/* allocate the next next full segment */
		err = nilfs_sufile_alloc(sufile, &nextnextnum);
		अगर (unlikely(err))
			जाओ failed_segbuf;

		segbuf->sb_sum.seg_seq = prev->sb_sum.seg_seq + 1;
		nilfs_segbuf_set_next_segnum(segbuf, nextnextnum, nilfs);

		list_add_tail(&segbuf->sb_list, &list);
		prev = segbuf;
	पूर्ण
	list_splice_tail(&list, &sci->sc_segbufs);
	वापस 0;

 failed_segbuf:
	nilfs_segbuf_मुक्त(segbuf);
 failed:
	list_क्रम_each_entry(segbuf, &list, sb_list) अणु
		ret = nilfs_sufile_मुक्त(sufile, segbuf->sb_nextnum);
		WARN_ON(ret); /* never fails */
	पूर्ण
	nilfs_destroy_logs(&list);
	वापस err;
पूर्ण

अटल व्योम nilfs_मुक्त_incomplete_logs(काष्ठा list_head *logs,
				       काष्ठा the_nilfs *nilfs)
अणु
	काष्ठा nilfs_segment_buffer *segbuf, *prev;
	काष्ठा inode *sufile = nilfs->ns_sufile;
	पूर्णांक ret;

	segbuf = NILFS_FIRST_SEGBUF(logs);
	अगर (nilfs->ns_nextnum != segbuf->sb_nextnum) अणु
		ret = nilfs_sufile_मुक्त(sufile, segbuf->sb_nextnum);
		WARN_ON(ret); /* never fails */
	पूर्ण
	अगर (atomic_पढ़ो(&segbuf->sb_err)) अणु
		/* Case 1: The first segment failed */
		अगर (segbuf->sb_pseg_start != segbuf->sb_fseg_start)
			/*
			 * Case 1a:  Partial segment appended पूर्णांकo an existing
			 * segment
			 */
			nilfs_terminate_segment(nilfs, segbuf->sb_fseg_start,
						segbuf->sb_fseg_end);
		अन्यथा /* Case 1b:  New full segment */
			set_nilfs_disजारीd(nilfs);
	पूर्ण

	prev = segbuf;
	list_क्रम_each_entry_जारी(segbuf, logs, sb_list) अणु
		अगर (prev->sb_nextnum != segbuf->sb_nextnum) अणु
			ret = nilfs_sufile_मुक्त(sufile, segbuf->sb_nextnum);
			WARN_ON(ret); /* never fails */
		पूर्ण
		अगर (atomic_पढ़ो(&segbuf->sb_err) &&
		    segbuf->sb_segnum != nilfs->ns_nextnum)
			/* Case 2: extended segment (!= next) failed */
			nilfs_sufile_set_error(sufile, segbuf->sb_segnum);
		prev = segbuf;
	पूर्ण
पूर्ण

अटल व्योम nilfs_segctor_update_segusage(काष्ठा nilfs_sc_info *sci,
					  काष्ठा inode *sufile)
अणु
	काष्ठा nilfs_segment_buffer *segbuf;
	अचिन्हित दीर्घ live_blocks;
	पूर्णांक ret;

	list_क्रम_each_entry(segbuf, &sci->sc_segbufs, sb_list) अणु
		live_blocks = segbuf->sb_sum.nblocks +
			(segbuf->sb_pseg_start - segbuf->sb_fseg_start);
		ret = nilfs_sufile_set_segment_usage(sufile, segbuf->sb_segnum,
						     live_blocks,
						     sci->sc_seg_स_समय);
		WARN_ON(ret); /* always succeed because the segusage is dirty */
	पूर्ण
पूर्ण

अटल व्योम nilfs_cancel_segusage(काष्ठा list_head *logs, काष्ठा inode *sufile)
अणु
	काष्ठा nilfs_segment_buffer *segbuf;
	पूर्णांक ret;

	segbuf = NILFS_FIRST_SEGBUF(logs);
	ret = nilfs_sufile_set_segment_usage(sufile, segbuf->sb_segnum,
					     segbuf->sb_pseg_start -
					     segbuf->sb_fseg_start, 0);
	WARN_ON(ret); /* always succeed because the segusage is dirty */

	list_क्रम_each_entry_जारी(segbuf, logs, sb_list) अणु
		ret = nilfs_sufile_set_segment_usage(sufile, segbuf->sb_segnum,
						     0, 0);
		WARN_ON(ret); /* always succeed */
	पूर्ण
पूर्ण

अटल व्योम nilfs_segctor_truncate_segments(काष्ठा nilfs_sc_info *sci,
					    काष्ठा nilfs_segment_buffer *last,
					    काष्ठा inode *sufile)
अणु
	काष्ठा nilfs_segment_buffer *segbuf = last;
	पूर्णांक ret;

	list_क्रम_each_entry_जारी(segbuf, &sci->sc_segbufs, sb_list) अणु
		sci->sc_segbuf_nblocks -= segbuf->sb_rest_blocks;
		ret = nilfs_sufile_मुक्त(sufile, segbuf->sb_nextnum);
		WARN_ON(ret);
	पूर्ण
	nilfs_truncate_logs(&sci->sc_segbufs, last);
पूर्ण


अटल पूर्णांक nilfs_segctor_collect(काष्ठा nilfs_sc_info *sci,
				 काष्ठा the_nilfs *nilfs, पूर्णांक mode)
अणु
	काष्ठा nilfs_cstage prev_stage = sci->sc_stage;
	पूर्णांक err, nadd = 1;

	/* Collection retry loop */
	क्रम (;;) अणु
		sci->sc_nblk_this_inc = 0;
		sci->sc_curseg = NILFS_FIRST_SEGBUF(&sci->sc_segbufs);

		err = nilfs_segctor_reset_segment_buffer(sci);
		अगर (unlikely(err))
			जाओ failed;

		err = nilfs_segctor_collect_blocks(sci, mode);
		sci->sc_nblk_this_inc += sci->sc_curseg->sb_sum.nblocks;
		अगर (!err)
			अवरोध;

		अगर (unlikely(err != -E2BIG))
			जाओ failed;

		/* The current segment is filled up */
		अगर (mode != SC_LSEG_SR ||
		    nilfs_sc_cstage_get(sci) < NILFS_ST_CPखाता)
			अवरोध;

		nilfs_clear_logs(&sci->sc_segbufs);

		अगर (sci->sc_stage.flags & NILFS_CF_SUFREED) अणु
			err = nilfs_sufile_cancel_मुक्तv(nilfs->ns_sufile,
							sci->sc_मुक्तsegs,
							sci->sc_nमुक्तsegs,
							शून्य);
			WARN_ON(err); /* करो not happen */
			sci->sc_stage.flags &= ~NILFS_CF_SUFREED;
		पूर्ण

		err = nilfs_segctor_extend_segments(sci, nilfs, nadd);
		अगर (unlikely(err))
			वापस err;

		nadd = min_t(पूर्णांक, nadd << 1, SC_MAX_SEGDELTA);
		sci->sc_stage = prev_stage;
	पूर्ण
	nilfs_segctor_truncate_segments(sci, sci->sc_curseg, nilfs->ns_sufile);
	वापस 0;

 failed:
	वापस err;
पूर्ण

अटल व्योम nilfs_list_replace_buffer(काष्ठा buffer_head *old_bh,
				      काष्ठा buffer_head *new_bh)
अणु
	BUG_ON(!list_empty(&new_bh->b_assoc_buffers));

	list_replace_init(&old_bh->b_assoc_buffers, &new_bh->b_assoc_buffers);
	/* The caller must release old_bh */
पूर्ण

अटल पूर्णांक
nilfs_segctor_update_payload_blocknr(काष्ठा nilfs_sc_info *sci,
				     काष्ठा nilfs_segment_buffer *segbuf,
				     पूर्णांक mode)
अणु
	काष्ठा inode *inode = शून्य;
	sector_t blocknr;
	अचिन्हित दीर्घ nfinfo = segbuf->sb_sum.nfinfo;
	अचिन्हित दीर्घ nblocks = 0, ndatablk = 0;
	स्थिर काष्ठा nilfs_sc_operations *sc_op = शून्य;
	काष्ठा nilfs_segsum_poपूर्णांकer ssp;
	काष्ठा nilfs_finfo *finfo = शून्य;
	जोड़ nilfs_binfo binfo;
	काष्ठा buffer_head *bh, *bh_org;
	ino_t ino = 0;
	पूर्णांक err = 0;

	अगर (!nfinfo)
		जाओ out;

	blocknr = segbuf->sb_pseg_start + segbuf->sb_sum.nsumblk;
	ssp.bh = NILFS_SEGBUF_FIRST_BH(&segbuf->sb_segsum_buffers);
	ssp.offset = माप(काष्ठा nilfs_segment_summary);

	list_क्रम_each_entry(bh, &segbuf->sb_payload_buffers, b_assoc_buffers) अणु
		अगर (bh == segbuf->sb_super_root)
			अवरोध;
		अगर (!finfo) अणु
			finfo =	nilfs_segctor_map_segsum_entry(
				sci, &ssp, माप(*finfo));
			ino = le64_to_cpu(finfo->fi_ino);
			nblocks = le32_to_cpu(finfo->fi_nblocks);
			ndatablk = le32_to_cpu(finfo->fi_ndatablk);

			inode = bh->b_page->mapping->host;

			अगर (mode == SC_LSEG_DSYNC)
				sc_op = &nilfs_sc_dsync_ops;
			अन्यथा अगर (ino == NILFS_DAT_INO)
				sc_op = &nilfs_sc_dat_ops;
			अन्यथा /* file blocks */
				sc_op = &nilfs_sc_file_ops;
		पूर्ण
		bh_org = bh;
		get_bh(bh_org);
		err = nilfs_bmap_assign(NILFS_I(inode)->i_bmap, &bh, blocknr,
					&binfo);
		अगर (bh != bh_org)
			nilfs_list_replace_buffer(bh_org, bh);
		brअन्यथा(bh_org);
		अगर (unlikely(err))
			जाओ failed_bmap;

		अगर (ndatablk > 0)
			sc_op->ग_लिखो_data_binfo(sci, &ssp, &binfo);
		अन्यथा
			sc_op->ग_लिखो_node_binfo(sci, &ssp, &binfo);

		blocknr++;
		अगर (--nblocks == 0) अणु
			finfo = शून्य;
			अगर (--nfinfo == 0)
				अवरोध;
		पूर्ण अन्यथा अगर (ndatablk > 0)
			ndatablk--;
	पूर्ण
 out:
	वापस 0;

 failed_bmap:
	वापस err;
पूर्ण

अटल पूर्णांक nilfs_segctor_assign(काष्ठा nilfs_sc_info *sci, पूर्णांक mode)
अणु
	काष्ठा nilfs_segment_buffer *segbuf;
	पूर्णांक err;

	list_क्रम_each_entry(segbuf, &sci->sc_segbufs, sb_list) अणु
		err = nilfs_segctor_update_payload_blocknr(sci, segbuf, mode);
		अगर (unlikely(err))
			वापस err;
		nilfs_segbuf_fill_in_segsum(segbuf);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम nilfs_begin_page_io(काष्ठा page *page)
अणु
	अगर (!page || PageWriteback(page))
		/*
		 * For split b-tree node pages, this function may be called
		 * twice.  We ignore the 2nd or later calls by this check.
		 */
		वापस;

	lock_page(page);
	clear_page_dirty_क्रम_io(page);
	set_page_ग_लिखोback(page);
	unlock_page(page);
पूर्ण

अटल व्योम nilfs_segctor_prepare_ग_लिखो(काष्ठा nilfs_sc_info *sci)
अणु
	काष्ठा nilfs_segment_buffer *segbuf;
	काष्ठा page *bd_page = शून्य, *fs_page = शून्य;

	list_क्रम_each_entry(segbuf, &sci->sc_segbufs, sb_list) अणु
		काष्ठा buffer_head *bh;

		list_क्रम_each_entry(bh, &segbuf->sb_segsum_buffers,
				    b_assoc_buffers) अणु
			अगर (bh->b_page != bd_page) अणु
				अगर (bd_page) अणु
					lock_page(bd_page);
					clear_page_dirty_क्रम_io(bd_page);
					set_page_ग_लिखोback(bd_page);
					unlock_page(bd_page);
				पूर्ण
				bd_page = bh->b_page;
			पूर्ण
		पूर्ण

		list_क्रम_each_entry(bh, &segbuf->sb_payload_buffers,
				    b_assoc_buffers) अणु
			set_buffer_async_ग_लिखो(bh);
			अगर (bh == segbuf->sb_super_root) अणु
				अगर (bh->b_page != bd_page) अणु
					lock_page(bd_page);
					clear_page_dirty_क्रम_io(bd_page);
					set_page_ग_लिखोback(bd_page);
					unlock_page(bd_page);
					bd_page = bh->b_page;
				पूर्ण
				अवरोध;
			पूर्ण
			अगर (bh->b_page != fs_page) अणु
				nilfs_begin_page_io(fs_page);
				fs_page = bh->b_page;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (bd_page) अणु
		lock_page(bd_page);
		clear_page_dirty_क्रम_io(bd_page);
		set_page_ग_लिखोback(bd_page);
		unlock_page(bd_page);
	पूर्ण
	nilfs_begin_page_io(fs_page);
पूर्ण

अटल पूर्णांक nilfs_segctor_ग_लिखो(काष्ठा nilfs_sc_info *sci,
			       काष्ठा the_nilfs *nilfs)
अणु
	पूर्णांक ret;

	ret = nilfs_ग_लिखो_logs(&sci->sc_segbufs, nilfs);
	list_splice_tail_init(&sci->sc_segbufs, &sci->sc_ग_लिखो_logs);
	वापस ret;
पूर्ण

अटल व्योम nilfs_end_page_io(काष्ठा page *page, पूर्णांक err)
अणु
	अगर (!page)
		वापस;

	अगर (buffer_nilfs_node(page_buffers(page)) && !PageWriteback(page)) अणु
		/*
		 * For b-tree node pages, this function may be called twice
		 * or more because they might be split in a segment.
		 */
		अगर (PageDirty(page)) अणु
			/*
			 * For pages holding split b-tree node buffers, dirty
			 * flag on the buffers may be cleared discretely.
			 * In that हाल, the page is once redirtied क्रम
			 * reमुख्यing buffers, and it must be cancelled अगर
			 * all the buffers get cleaned later.
			 */
			lock_page(page);
			अगर (nilfs_page_buffers_clean(page))
				__nilfs_clear_page_dirty(page);
			unlock_page(page);
		पूर्ण
		वापस;
	पूर्ण

	अगर (!err) अणु
		अगर (!nilfs_page_buffers_clean(page))
			__set_page_dirty_nobuffers(page);
		ClearPageError(page);
	पूर्ण अन्यथा अणु
		__set_page_dirty_nobuffers(page);
		SetPageError(page);
	पूर्ण

	end_page_ग_लिखोback(page);
पूर्ण

अटल व्योम nilfs_पात_logs(काष्ठा list_head *logs, पूर्णांक err)
अणु
	काष्ठा nilfs_segment_buffer *segbuf;
	काष्ठा page *bd_page = शून्य, *fs_page = शून्य;
	काष्ठा buffer_head *bh;

	अगर (list_empty(logs))
		वापस;

	list_क्रम_each_entry(segbuf, logs, sb_list) अणु
		list_क्रम_each_entry(bh, &segbuf->sb_segsum_buffers,
				    b_assoc_buffers) अणु
			अगर (bh->b_page != bd_page) अणु
				अगर (bd_page)
					end_page_ग_लिखोback(bd_page);
				bd_page = bh->b_page;
			पूर्ण
		पूर्ण

		list_क्रम_each_entry(bh, &segbuf->sb_payload_buffers,
				    b_assoc_buffers) अणु
			clear_buffer_async_ग_लिखो(bh);
			अगर (bh == segbuf->sb_super_root) अणु
				अगर (bh->b_page != bd_page) अणु
					end_page_ग_लिखोback(bd_page);
					bd_page = bh->b_page;
				पूर्ण
				अवरोध;
			पूर्ण
			अगर (bh->b_page != fs_page) अणु
				nilfs_end_page_io(fs_page, err);
				fs_page = bh->b_page;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (bd_page)
		end_page_ग_लिखोback(bd_page);

	nilfs_end_page_io(fs_page, err);
पूर्ण

अटल व्योम nilfs_segctor_पात_स्थिरruction(काष्ठा nilfs_sc_info *sci,
					     काष्ठा the_nilfs *nilfs, पूर्णांक err)
अणु
	LIST_HEAD(logs);
	पूर्णांक ret;

	list_splice_tail_init(&sci->sc_ग_लिखो_logs, &logs);
	ret = nilfs_रुको_on_logs(&logs);
	nilfs_पात_logs(&logs, ret ? : err);

	list_splice_tail_init(&sci->sc_segbufs, &logs);
	nilfs_cancel_segusage(&logs, nilfs->ns_sufile);
	nilfs_मुक्त_incomplete_logs(&logs, nilfs);

	अगर (sci->sc_stage.flags & NILFS_CF_SUFREED) अणु
		ret = nilfs_sufile_cancel_मुक्तv(nilfs->ns_sufile,
						sci->sc_मुक्तsegs,
						sci->sc_nमुक्तsegs,
						शून्य);
		WARN_ON(ret); /* करो not happen */
	पूर्ण

	nilfs_destroy_logs(&logs);
पूर्ण

अटल व्योम nilfs_set_next_segment(काष्ठा the_nilfs *nilfs,
				   काष्ठा nilfs_segment_buffer *segbuf)
अणु
	nilfs->ns_segnum = segbuf->sb_segnum;
	nilfs->ns_nextnum = segbuf->sb_nextnum;
	nilfs->ns_pseg_offset = segbuf->sb_pseg_start - segbuf->sb_fseg_start
		+ segbuf->sb_sum.nblocks;
	nilfs->ns_seg_seq = segbuf->sb_sum.seg_seq;
	nilfs->ns_स_समय = segbuf->sb_sum.स_समय;
पूर्ण

अटल व्योम nilfs_segctor_complete_ग_लिखो(काष्ठा nilfs_sc_info *sci)
अणु
	काष्ठा nilfs_segment_buffer *segbuf;
	काष्ठा page *bd_page = शून्य, *fs_page = शून्य;
	काष्ठा the_nilfs *nilfs = sci->sc_super->s_fs_info;
	पूर्णांक update_sr = false;

	list_क्रम_each_entry(segbuf, &sci->sc_ग_लिखो_logs, sb_list) अणु
		काष्ठा buffer_head *bh;

		list_क्रम_each_entry(bh, &segbuf->sb_segsum_buffers,
				    b_assoc_buffers) अणु
			set_buffer_uptodate(bh);
			clear_buffer_dirty(bh);
			अगर (bh->b_page != bd_page) अणु
				अगर (bd_page)
					end_page_ग_लिखोback(bd_page);
				bd_page = bh->b_page;
			पूर्ण
		पूर्ण
		/*
		 * We assume that the buffers which beदीर्घ to the same page
		 * जारी over the buffer list.
		 * Under this assumption, the last BHs of pages is
		 * identअगरiable by the discontinuity of bh->b_page
		 * (page != fs_page).
		 *
		 * For B-tree node blocks, however, this assumption is not
		 * guaranteed.  The cleanup code of B-tree node pages needs
		 * special care.
		 */
		list_क्रम_each_entry(bh, &segbuf->sb_payload_buffers,
				    b_assoc_buffers) अणु
			स्थिर अचिन्हित दीर्घ set_bits = BIT(BH_Uptodate);
			स्थिर अचिन्हित दीर्घ clear_bits =
				(BIT(BH_Dirty) | BIT(BH_Async_Write) |
				 BIT(BH_Delay) | BIT(BH_NILFS_Volatile) |
				 BIT(BH_NILFS_Redirected));

			set_mask_bits(&bh->b_state, clear_bits, set_bits);
			अगर (bh == segbuf->sb_super_root) अणु
				अगर (bh->b_page != bd_page) अणु
					end_page_ग_लिखोback(bd_page);
					bd_page = bh->b_page;
				पूर्ण
				update_sr = true;
				अवरोध;
			पूर्ण
			अगर (bh->b_page != fs_page) अणु
				nilfs_end_page_io(fs_page, 0);
				fs_page = bh->b_page;
			पूर्ण
		पूर्ण

		अगर (!nilfs_segbuf_simplex(segbuf)) अणु
			अगर (segbuf->sb_sum.flags & NILFS_SS_LOGBGN) अणु
				set_bit(NILFS_SC_UNCLOSED, &sci->sc_flags);
				sci->sc_lseg_sसमय = jअगरfies;
			पूर्ण
			अगर (segbuf->sb_sum.flags & NILFS_SS_LOGEND)
				clear_bit(NILFS_SC_UNCLOSED, &sci->sc_flags);
		पूर्ण
	पूर्ण
	/*
	 * Since pages may जारी over multiple segment buffers,
	 * end of the last page must be checked outside of the loop.
	 */
	अगर (bd_page)
		end_page_ग_लिखोback(bd_page);

	nilfs_end_page_io(fs_page, 0);

	nilfs_drop_collected_inodes(&sci->sc_dirty_files);

	अगर (nilfs_करोing_gc())
		nilfs_drop_collected_inodes(&sci->sc_gc_inodes);
	अन्यथा
		nilfs->ns_nongc_स_समय = sci->sc_seg_स_समय;

	sci->sc_nblk_inc += sci->sc_nblk_this_inc;

	segbuf = NILFS_LAST_SEGBUF(&sci->sc_ग_लिखो_logs);
	nilfs_set_next_segment(nilfs, segbuf);

	अगर (update_sr) अणु
		nilfs->ns_flushed_device = 0;
		nilfs_set_last_segment(nilfs, segbuf->sb_pseg_start,
				       segbuf->sb_sum.seg_seq, nilfs->ns_cno++);

		clear_bit(NILFS_SC_HAVE_DELTA, &sci->sc_flags);
		clear_bit(NILFS_SC_सूचीTY, &sci->sc_flags);
		set_bit(NILFS_SC_SUPER_ROOT, &sci->sc_flags);
		nilfs_segctor_clear_metadata_dirty(sci);
	पूर्ण अन्यथा
		clear_bit(NILFS_SC_SUPER_ROOT, &sci->sc_flags);
पूर्ण

अटल पूर्णांक nilfs_segctor_रुको(काष्ठा nilfs_sc_info *sci)
अणु
	पूर्णांक ret;

	ret = nilfs_रुको_on_logs(&sci->sc_ग_लिखो_logs);
	अगर (!ret) अणु
		nilfs_segctor_complete_ग_लिखो(sci);
		nilfs_destroy_logs(&sci->sc_ग_लिखो_logs);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक nilfs_segctor_collect_dirty_files(काष्ठा nilfs_sc_info *sci,
					     काष्ठा the_nilfs *nilfs)
अणु
	काष्ठा nilfs_inode_info *ii, *n;
	काष्ठा inode *अगरile = sci->sc_root->अगरile;

	spin_lock(&nilfs->ns_inode_lock);
 retry:
	list_क्रम_each_entry_safe(ii, n, &nilfs->ns_dirty_files, i_dirty) अणु
		अगर (!ii->i_bh) अणु
			काष्ठा buffer_head *ibh;
			पूर्णांक err;

			spin_unlock(&nilfs->ns_inode_lock);
			err = nilfs_अगरile_get_inode_block(
				अगरile, ii->vfs_inode.i_ino, &ibh);
			अगर (unlikely(err)) अणु
				nilfs_warn(sci->sc_super,
					   "log writer: error %d getting inode block (ino=%lu)",
					   err, ii->vfs_inode.i_ino);
				वापस err;
			पूर्ण
			spin_lock(&nilfs->ns_inode_lock);
			अगर (likely(!ii->i_bh))
				ii->i_bh = ibh;
			अन्यथा
				brअन्यथा(ibh);
			जाओ retry;
		पूर्ण

		// Always redirty the buffer to aव्योम race condition
		mark_buffer_dirty(ii->i_bh);
		nilfs_mdt_mark_dirty(अगरile);

		clear_bit(NILFS_I_QUEUED, &ii->i_state);
		set_bit(NILFS_I_BUSY, &ii->i_state);
		list_move_tail(&ii->i_dirty, &sci->sc_dirty_files);
	पूर्ण
	spin_unlock(&nilfs->ns_inode_lock);

	वापस 0;
पूर्ण

अटल व्योम nilfs_segctor_drop_written_files(काष्ठा nilfs_sc_info *sci,
					     काष्ठा the_nilfs *nilfs)
अणु
	काष्ठा nilfs_inode_info *ii, *n;
	पूर्णांक during_mount = !(sci->sc_super->s_flags & SB_ACTIVE);
	पूर्णांक defer_iput = false;

	spin_lock(&nilfs->ns_inode_lock);
	list_क्रम_each_entry_safe(ii, n, &sci->sc_dirty_files, i_dirty) अणु
		अगर (!test_and_clear_bit(NILFS_I_UPDATED, &ii->i_state) ||
		    test_bit(NILFS_I_सूचीTY, &ii->i_state))
			जारी;

		clear_bit(NILFS_I_BUSY, &ii->i_state);
		brअन्यथा(ii->i_bh);
		ii->i_bh = शून्य;
		list_del_init(&ii->i_dirty);
		अगर (!ii->vfs_inode.i_nlink || during_mount) अणु
			/*
			 * Defer calling iput() to aव्योम deadlocks अगर
			 * i_nlink == 0 or mount is not yet finished.
			 */
			list_add_tail(&ii->i_dirty, &sci->sc_iput_queue);
			defer_iput = true;
		पूर्ण अन्यथा अणु
			spin_unlock(&nilfs->ns_inode_lock);
			iput(&ii->vfs_inode);
			spin_lock(&nilfs->ns_inode_lock);
		पूर्ण
	पूर्ण
	spin_unlock(&nilfs->ns_inode_lock);

	अगर (defer_iput)
		schedule_work(&sci->sc_iput_work);
पूर्ण

/*
 * Main procedure of segment स्थिरructor
 */
अटल पूर्णांक nilfs_segctor_करो_स्थिरruct(काष्ठा nilfs_sc_info *sci, पूर्णांक mode)
अणु
	काष्ठा the_nilfs *nilfs = sci->sc_super->s_fs_info;
	पूर्णांक err;

	nilfs_sc_cstage_set(sci, NILFS_ST_INIT);
	sci->sc_cno = nilfs->ns_cno;

	err = nilfs_segctor_collect_dirty_files(sci, nilfs);
	अगर (unlikely(err))
		जाओ out;

	अगर (nilfs_test_metadata_dirty(nilfs, sci->sc_root))
		set_bit(NILFS_SC_सूचीTY, &sci->sc_flags);

	अगर (nilfs_segctor_clean(sci))
		जाओ out;

	करो अणु
		sci->sc_stage.flags &= ~NILFS_CF_HISTORY_MASK;

		err = nilfs_segctor_begin_स्थिरruction(sci, nilfs);
		अगर (unlikely(err))
			जाओ out;

		/* Update समय stamp */
		sci->sc_seg_स_समय = kसमय_get_real_seconds();

		err = nilfs_segctor_collect(sci, nilfs, mode);
		अगर (unlikely(err))
			जाओ failed;

		/* Aव्योम empty segment */
		अगर (nilfs_sc_cstage_get(sci) == NILFS_ST_DONE &&
		    nilfs_segbuf_empty(sci->sc_curseg)) अणु
			nilfs_segctor_पात_स्थिरruction(sci, nilfs, 1);
			जाओ out;
		पूर्ण

		err = nilfs_segctor_assign(sci, mode);
		अगर (unlikely(err))
			जाओ failed;

		अगर (sci->sc_stage.flags & NILFS_CF_Iखाता_STARTED)
			nilfs_segctor_fill_in_file_bmap(sci);

		अगर (mode == SC_LSEG_SR &&
		    nilfs_sc_cstage_get(sci) >= NILFS_ST_CPखाता) अणु
			err = nilfs_segctor_fill_in_checkpoपूर्णांक(sci);
			अगर (unlikely(err))
				जाओ failed_to_ग_लिखो;

			nilfs_segctor_fill_in_super_root(sci, nilfs);
		पूर्ण
		nilfs_segctor_update_segusage(sci, nilfs->ns_sufile);

		/* Write partial segments */
		nilfs_segctor_prepare_ग_लिखो(sci);

		nilfs_add_checksums_on_logs(&sci->sc_segbufs,
					    nilfs->ns_crc_seed);

		err = nilfs_segctor_ग_लिखो(sci, nilfs);
		अगर (unlikely(err))
			जाओ failed_to_ग_लिखो;

		अगर (nilfs_sc_cstage_get(sci) == NILFS_ST_DONE ||
		    nilfs->ns_blocksize_bits != PAGE_SHIFT) अणु
			/*
			 * At this poपूर्णांक, we aव्योम द्विगुन buffering
			 * क्रम blocksize < pagesize because page dirty
			 * flag is turned off during ग_लिखो and dirty
			 * buffers are not properly collected क्रम
			 * pages crossing over segments.
			 */
			err = nilfs_segctor_रुको(sci);
			अगर (err)
				जाओ failed_to_ग_लिखो;
		पूर्ण
	पूर्ण जबतक (nilfs_sc_cstage_get(sci) != NILFS_ST_DONE);

 out:
	nilfs_segctor_drop_written_files(sci, nilfs);
	वापस err;

 failed_to_ग_लिखो:
	अगर (sci->sc_stage.flags & NILFS_CF_Iखाता_STARTED)
		nilfs_redirty_inodes(&sci->sc_dirty_files);

 failed:
	अगर (nilfs_करोing_gc())
		nilfs_redirty_inodes(&sci->sc_gc_inodes);
	nilfs_segctor_पात_स्थिरruction(sci, nilfs, err);
	जाओ out;
पूर्ण

/**
 * nilfs_segctor_start_समयr - set समयr of background ग_लिखो
 * @sci: nilfs_sc_info
 *
 * If the समयr has alपढ़ोy been set, it ignores the new request.
 * This function MUST be called within a section locking the segment
 * semaphore.
 */
अटल व्योम nilfs_segctor_start_समयr(काष्ठा nilfs_sc_info *sci)
अणु
	spin_lock(&sci->sc_state_lock);
	अगर (!(sci->sc_state & NILFS_SEGCTOR_COMMIT)) अणु
		sci->sc_समयr.expires = jअगरfies + sci->sc_पूर्णांकerval;
		add_समयr(&sci->sc_समयr);
		sci->sc_state |= NILFS_SEGCTOR_COMMIT;
	पूर्ण
	spin_unlock(&sci->sc_state_lock);
पूर्ण

अटल व्योम nilfs_segctor_करो_flush(काष्ठा nilfs_sc_info *sci, पूर्णांक bn)
अणु
	spin_lock(&sci->sc_state_lock);
	अगर (!(sci->sc_flush_request & BIT(bn))) अणु
		अचिन्हित दीर्घ prev_req = sci->sc_flush_request;

		sci->sc_flush_request |= BIT(bn);
		अगर (!prev_req)
			wake_up(&sci->sc_रुको_daemon);
	पूर्ण
	spin_unlock(&sci->sc_state_lock);
पूर्ण

/**
 * nilfs_flush_segment - trigger a segment स्थिरruction क्रम resource control
 * @sb: super block
 * @ino: inode number of the file to be flushed out.
 */
व्योम nilfs_flush_segment(काष्ठा super_block *sb, ino_t ino)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा nilfs_sc_info *sci = nilfs->ns_ग_लिखोr;

	अगर (!sci || nilfs_करोing_स्थिरruction())
		वापस;
	nilfs_segctor_करो_flush(sci, NILFS_MDT_INODE(sb, ino) ? ino : 0);
					/* assign bit 0 to data files */
पूर्ण

काष्ठा nilfs_segctor_रुको_request अणु
	रुको_queue_entry_t	wq;
	__u32		seq;
	पूर्णांक		err;
	atomic_t	करोne;
पूर्ण;

अटल पूर्णांक nilfs_segctor_sync(काष्ठा nilfs_sc_info *sci)
अणु
	काष्ठा nilfs_segctor_रुको_request रुको_req;
	पूर्णांक err = 0;

	spin_lock(&sci->sc_state_lock);
	init_रुको(&रुको_req.wq);
	रुको_req.err = 0;
	atomic_set(&रुको_req.करोne, 0);
	रुको_req.seq = ++sci->sc_seq_request;
	spin_unlock(&sci->sc_state_lock);

	init_रुकोqueue_entry(&रुको_req.wq, current);
	add_रुको_queue(&sci->sc_रुको_request, &रुको_req.wq);
	set_current_state(TASK_INTERRUPTIBLE);
	wake_up(&sci->sc_रुको_daemon);

	क्रम (;;) अणु
		अगर (atomic_पढ़ो(&रुको_req.करोne)) अणु
			err = रुको_req.err;
			अवरोध;
		पूर्ण
		अगर (!संकेत_pending(current)) अणु
			schedule();
			जारी;
		पूर्ण
		err = -ERESTARTSYS;
		अवरोध;
	पूर्ण
	finish_रुको(&sci->sc_रुको_request, &रुको_req.wq);
	वापस err;
पूर्ण

अटल व्योम nilfs_segctor_wakeup(काष्ठा nilfs_sc_info *sci, पूर्णांक err)
अणु
	काष्ठा nilfs_segctor_रुको_request *wrq, *n;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sci->sc_रुको_request.lock, flags);
	list_क्रम_each_entry_safe(wrq, n, &sci->sc_रुको_request.head, wq.entry) अणु
		अगर (!atomic_पढ़ो(&wrq->करोne) &&
		    nilfs_cnt32_ge(sci->sc_seq_करोne, wrq->seq)) अणु
			wrq->err = err;
			atomic_set(&wrq->करोne, 1);
		पूर्ण
		अगर (atomic_पढ़ो(&wrq->करोne)) अणु
			wrq->wq.func(&wrq->wq,
				     TASK_UNINTERRUPTIBLE | TASK_INTERRUPTIBLE,
				     0, शून्य);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&sci->sc_रुको_request.lock, flags);
पूर्ण

/**
 * nilfs_स्थिरruct_segment - स्थिरruct a logical segment
 * @sb: super block
 *
 * Return Value: On success, 0 is वापसed. On errors, one of the following
 * negative error code is वापसed.
 *
 * %-EROFS - Read only fileप्रणाली.
 *
 * %-EIO - I/O error
 *
 * %-ENOSPC - No space left on device (only in a panic state).
 *
 * %-ERESTARTSYS - Interrupted.
 *
 * %-ENOMEM - Insufficient memory available.
 */
पूर्णांक nilfs_स्थिरruct_segment(काष्ठा super_block *sb)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा nilfs_sc_info *sci = nilfs->ns_ग_लिखोr;
	काष्ठा nilfs_transaction_info *ti;
	पूर्णांक err;

	अगर (!sci)
		वापस -EROFS;

	/* A call inside transactions causes a deadlock. */
	BUG_ON((ti = current->journal_info) && ti->ti_magic == NILFS_TI_MAGIC);

	err = nilfs_segctor_sync(sci);
	वापस err;
पूर्ण

/**
 * nilfs_स्थिरruct_dsync_segment - स्थिरruct a data-only logical segment
 * @sb: super block
 * @inode: inode whose data blocks should be written out
 * @start: start byte offset
 * @end: end byte offset (inclusive)
 *
 * Return Value: On success, 0 is वापसed. On errors, one of the following
 * negative error code is वापसed.
 *
 * %-EROFS - Read only fileप्रणाली.
 *
 * %-EIO - I/O error
 *
 * %-ENOSPC - No space left on device (only in a panic state).
 *
 * %-ERESTARTSYS - Interrupted.
 *
 * %-ENOMEM - Insufficient memory available.
 */
पूर्णांक nilfs_स्थिरruct_dsync_segment(काष्ठा super_block *sb, काष्ठा inode *inode,
				  loff_t start, loff_t end)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा nilfs_sc_info *sci = nilfs->ns_ग_लिखोr;
	काष्ठा nilfs_inode_info *ii;
	काष्ठा nilfs_transaction_info ti;
	पूर्णांक err = 0;

	अगर (!sci)
		वापस -EROFS;

	nilfs_transaction_lock(sb, &ti, 0);

	ii = NILFS_I(inode);
	अगर (test_bit(NILFS_I_INODE_SYNC, &ii->i_state) ||
	    nilfs_test_opt(nilfs, STRICT_ORDER) ||
	    test_bit(NILFS_SC_UNCLOSED, &sci->sc_flags) ||
	    nilfs_disजारीd(nilfs)) अणु
		nilfs_transaction_unlock(sb);
		err = nilfs_segctor_sync(sci);
		वापस err;
	पूर्ण

	spin_lock(&nilfs->ns_inode_lock);
	अगर (!test_bit(NILFS_I_QUEUED, &ii->i_state) &&
	    !test_bit(NILFS_I_BUSY, &ii->i_state)) अणु
		spin_unlock(&nilfs->ns_inode_lock);
		nilfs_transaction_unlock(sb);
		वापस 0;
	पूर्ण
	spin_unlock(&nilfs->ns_inode_lock);
	sci->sc_dsync_inode = ii;
	sci->sc_dsync_start = start;
	sci->sc_dsync_end = end;

	err = nilfs_segctor_करो_स्थिरruct(sci, SC_LSEG_DSYNC);
	अगर (!err)
		nilfs->ns_flushed_device = 0;

	nilfs_transaction_unlock(sb);
	वापस err;
पूर्ण

#घोषणा FLUSH_खाता_BIT	(0x1) /* data file only */
#घोषणा FLUSH_DAT_BIT	BIT(NILFS_DAT_INO) /* DAT only */

/**
 * nilfs_segctor_accept - record accepted sequence count of log-ग_लिखो requests
 * @sci: segment स्थिरructor object
 */
अटल व्योम nilfs_segctor_accept(काष्ठा nilfs_sc_info *sci)
अणु
	spin_lock(&sci->sc_state_lock);
	sci->sc_seq_accepted = sci->sc_seq_request;
	spin_unlock(&sci->sc_state_lock);
	del_समयr_sync(&sci->sc_समयr);
पूर्ण

/**
 * nilfs_segctor_notअगरy - notअगरy the result of request to caller thपढ़ोs
 * @sci: segment स्थिरructor object
 * @mode: mode of log क्रमming
 * @err: error code to be notअगरied
 */
अटल व्योम nilfs_segctor_notअगरy(काष्ठा nilfs_sc_info *sci, पूर्णांक mode, पूर्णांक err)
अणु
	/* Clear requests (even when the स्थिरruction failed) */
	spin_lock(&sci->sc_state_lock);

	अगर (mode == SC_LSEG_SR) अणु
		sci->sc_state &= ~NILFS_SEGCTOR_COMMIT;
		sci->sc_seq_करोne = sci->sc_seq_accepted;
		nilfs_segctor_wakeup(sci, err);
		sci->sc_flush_request = 0;
	पूर्ण अन्यथा अणु
		अगर (mode == SC_FLUSH_खाता)
			sci->sc_flush_request &= ~FLUSH_खाता_BIT;
		अन्यथा अगर (mode == SC_FLUSH_DAT)
			sci->sc_flush_request &= ~FLUSH_DAT_BIT;

		/* re-enable समयr अगर checkpoपूर्णांक creation was not करोne */
		अगर ((sci->sc_state & NILFS_SEGCTOR_COMMIT) &&
		    समय_beक्रमe(jअगरfies, sci->sc_समयr.expires))
			add_समयr(&sci->sc_समयr);
	पूर्ण
	spin_unlock(&sci->sc_state_lock);
पूर्ण

/**
 * nilfs_segctor_स्थिरruct - क्रमm logs and ग_लिखो them to disk
 * @sci: segment स्थिरructor object
 * @mode: mode of log क्रमming
 */
अटल पूर्णांक nilfs_segctor_स्थिरruct(काष्ठा nilfs_sc_info *sci, पूर्णांक mode)
अणु
	काष्ठा the_nilfs *nilfs = sci->sc_super->s_fs_info;
	काष्ठा nilfs_super_block **sbp;
	पूर्णांक err = 0;

	nilfs_segctor_accept(sci);

	अगर (nilfs_disजारीd(nilfs))
		mode = SC_LSEG_SR;
	अगर (!nilfs_segctor_confirm(sci))
		err = nilfs_segctor_करो_स्थिरruct(sci, mode);

	अगर (likely(!err)) अणु
		अगर (mode != SC_FLUSH_DAT)
			atomic_set(&nilfs->ns_ndirtyblks, 0);
		अगर (test_bit(NILFS_SC_SUPER_ROOT, &sci->sc_flags) &&
		    nilfs_disजारीd(nilfs)) अणु
			करोwn_ग_लिखो(&nilfs->ns_sem);
			err = -EIO;
			sbp = nilfs_prepare_super(sci->sc_super,
						  nilfs_sb_will_flip(nilfs));
			अगर (likely(sbp)) अणु
				nilfs_set_log_cursor(sbp[0], nilfs);
				err = nilfs_commit_super(sci->sc_super,
							 NILFS_SB_COMMIT);
			पूर्ण
			up_ग_लिखो(&nilfs->ns_sem);
		पूर्ण
	पूर्ण

	nilfs_segctor_notअगरy(sci, mode, err);
	वापस err;
पूर्ण

अटल व्योम nilfs_स्थिरruction_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा nilfs_sc_info *sci = from_समयr(sci, t, sc_समयr);

	wake_up_process(sci->sc_समयr_task);
पूर्ण

अटल व्योम
nilfs_हटाओ_written_gcinodes(काष्ठा the_nilfs *nilfs, काष्ठा list_head *head)
अणु
	काष्ठा nilfs_inode_info *ii, *n;

	list_क्रम_each_entry_safe(ii, n, head, i_dirty) अणु
		अगर (!test_bit(NILFS_I_UPDATED, &ii->i_state))
			जारी;
		list_del_init(&ii->i_dirty);
		truncate_inode_pages(&ii->vfs_inode.i_data, 0);
		nilfs_btnode_cache_clear(&ii->i_btnode_cache);
		iput(&ii->vfs_inode);
	पूर्ण
पूर्ण

पूर्णांक nilfs_clean_segments(काष्ठा super_block *sb, काष्ठा nilfs_argv *argv,
			 व्योम **kbufs)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा nilfs_sc_info *sci = nilfs->ns_ग_लिखोr;
	काष्ठा nilfs_transaction_info ti;
	पूर्णांक err;

	अगर (unlikely(!sci))
		वापस -EROFS;

	nilfs_transaction_lock(sb, &ti, 1);

	err = nilfs_mdt_save_to_shaकरोw_map(nilfs->ns_dat);
	अगर (unlikely(err))
		जाओ out_unlock;

	err = nilfs_ioctl_prepare_clean_segments(nilfs, argv, kbufs);
	अगर (unlikely(err)) अणु
		nilfs_mdt_restore_from_shaकरोw_map(nilfs->ns_dat);
		जाओ out_unlock;
	पूर्ण

	sci->sc_मुक्तsegs = kbufs[4];
	sci->sc_nमुक्तsegs = argv[4].v_nmembs;
	list_splice_tail_init(&nilfs->ns_gc_inodes, &sci->sc_gc_inodes);

	क्रम (;;) अणु
		err = nilfs_segctor_स्थिरruct(sci, SC_LSEG_SR);
		nilfs_हटाओ_written_gcinodes(nilfs, &sci->sc_gc_inodes);

		अगर (likely(!err))
			अवरोध;

		nilfs_warn(sb, "error %d cleaning segments", err);
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_समयout(sci->sc_पूर्णांकerval);
	पूर्ण
	अगर (nilfs_test_opt(nilfs, DISCARD)) अणु
		पूर्णांक ret = nilfs_discard_segments(nilfs, sci->sc_मुक्तsegs,
						 sci->sc_nमुक्तsegs);
		अगर (ret) अणु
			nilfs_warn(sb,
				   "error %d on discard request, turning discards off for the device",
				   ret);
			nilfs_clear_opt(nilfs, DISCARD);
		पूर्ण
	पूर्ण

 out_unlock:
	sci->sc_मुक्तsegs = शून्य;
	sci->sc_nमुक्तsegs = 0;
	nilfs_mdt_clear_shaकरोw_map(nilfs->ns_dat);
	nilfs_transaction_unlock(sb);
	वापस err;
पूर्ण

अटल व्योम nilfs_segctor_thपढ़ो_स्थिरruct(काष्ठा nilfs_sc_info *sci, पूर्णांक mode)
अणु
	काष्ठा nilfs_transaction_info ti;

	nilfs_transaction_lock(sci->sc_super, &ti, 0);
	nilfs_segctor_स्थिरruct(sci, mode);

	/*
	 * Unबंदd segment should be retried.  We करो this using sc_समयr.
	 * Timeout of sc_समयr will invoke complete स्थिरruction which leads
	 * to बंद the current logical segment.
	 */
	अगर (test_bit(NILFS_SC_UNCLOSED, &sci->sc_flags))
		nilfs_segctor_start_समयr(sci);

	nilfs_transaction_unlock(sci->sc_super);
पूर्ण

अटल व्योम nilfs_segctor_करो_immediate_flush(काष्ठा nilfs_sc_info *sci)
अणु
	पूर्णांक mode = 0;

	spin_lock(&sci->sc_state_lock);
	mode = (sci->sc_flush_request & FLUSH_DAT_BIT) ?
		SC_FLUSH_DAT : SC_FLUSH_खाता;
	spin_unlock(&sci->sc_state_lock);

	अगर (mode) अणु
		nilfs_segctor_करो_स्थिरruct(sci, mode);

		spin_lock(&sci->sc_state_lock);
		sci->sc_flush_request &= (mode == SC_FLUSH_खाता) ?
			~FLUSH_खाता_BIT : ~FLUSH_DAT_BIT;
		spin_unlock(&sci->sc_state_lock);
	पूर्ण
	clear_bit(NILFS_SC_PRIOR_FLUSH, &sci->sc_flags);
पूर्ण

अटल पूर्णांक nilfs_segctor_flush_mode(काष्ठा nilfs_sc_info *sci)
अणु
	अगर (!test_bit(NILFS_SC_UNCLOSED, &sci->sc_flags) ||
	    समय_beक्रमe(jअगरfies, sci->sc_lseg_sसमय + sci->sc_mjcp_freq)) अणु
		अगर (!(sci->sc_flush_request & ~FLUSH_खाता_BIT))
			वापस SC_FLUSH_खाता;
		अन्यथा अगर (!(sci->sc_flush_request & ~FLUSH_DAT_BIT))
			वापस SC_FLUSH_DAT;
	पूर्ण
	वापस SC_LSEG_SR;
पूर्ण

/**
 * nilfs_segctor_thपढ़ो - मुख्य loop of the segment स्थिरructor thपढ़ो.
 * @arg: poपूर्णांकer to a काष्ठा nilfs_sc_info.
 *
 * nilfs_segctor_thपढ़ो() initializes a समयr and serves as a daemon
 * to execute segment स्थिरructions.
 */
अटल पूर्णांक nilfs_segctor_thपढ़ो(व्योम *arg)
अणु
	काष्ठा nilfs_sc_info *sci = (काष्ठा nilfs_sc_info *)arg;
	काष्ठा the_nilfs *nilfs = sci->sc_super->s_fs_info;
	पूर्णांक समयout = 0;

	sci->sc_समयr_task = current;

	/* start sync. */
	sci->sc_task = current;
	wake_up(&sci->sc_रुको_task); /* क्रम nilfs_segctor_start_thपढ़ो() */
	nilfs_info(sci->sc_super,
		   "segctord starting. Construction interval = %lu seconds, CP frequency < %lu seconds",
		   sci->sc_पूर्णांकerval / HZ, sci->sc_mjcp_freq / HZ);

	spin_lock(&sci->sc_state_lock);
 loop:
	क्रम (;;) अणु
		पूर्णांक mode;

		अगर (sci->sc_state & NILFS_SEGCTOR_QUIT)
			जाओ end_thपढ़ो;

		अगर (समयout || sci->sc_seq_request != sci->sc_seq_करोne)
			mode = SC_LSEG_SR;
		अन्यथा अगर (sci->sc_flush_request)
			mode = nilfs_segctor_flush_mode(sci);
		अन्यथा
			अवरोध;

		spin_unlock(&sci->sc_state_lock);
		nilfs_segctor_thपढ़ो_स्थिरruct(sci, mode);
		spin_lock(&sci->sc_state_lock);
		समयout = 0;
	पूर्ण


	अगर (मुक्तzing(current)) अणु
		spin_unlock(&sci->sc_state_lock);
		try_to_मुक्तze();
		spin_lock(&sci->sc_state_lock);
	पूर्ण अन्यथा अणु
		DEFINE_WAIT(रुको);
		पूर्णांक should_sleep = 1;

		prepare_to_रुको(&sci->sc_रुको_daemon, &रुको,
				TASK_INTERRUPTIBLE);

		अगर (sci->sc_seq_request != sci->sc_seq_करोne)
			should_sleep = 0;
		अन्यथा अगर (sci->sc_flush_request)
			should_sleep = 0;
		अन्यथा अगर (sci->sc_state & NILFS_SEGCTOR_COMMIT)
			should_sleep = समय_beक्रमe(jअगरfies,
					sci->sc_समयr.expires);

		अगर (should_sleep) अणु
			spin_unlock(&sci->sc_state_lock);
			schedule();
			spin_lock(&sci->sc_state_lock);
		पूर्ण
		finish_रुको(&sci->sc_रुको_daemon, &रुको);
		समयout = ((sci->sc_state & NILFS_SEGCTOR_COMMIT) &&
			   समय_after_eq(jअगरfies, sci->sc_समयr.expires));

		अगर (nilfs_sb_dirty(nilfs) && nilfs_sb_need_update(nilfs))
			set_nilfs_disजारीd(nilfs);
	पूर्ण
	जाओ loop;

 end_thपढ़ो:
	spin_unlock(&sci->sc_state_lock);

	/* end sync. */
	sci->sc_task = शून्य;
	wake_up(&sci->sc_रुको_task); /* क्रम nilfs_segctor_समाप्त_thपढ़ो() */
	वापस 0;
पूर्ण

अटल पूर्णांक nilfs_segctor_start_thपढ़ो(काष्ठा nilfs_sc_info *sci)
अणु
	काष्ठा task_काष्ठा *t;

	t = kthपढ़ो_run(nilfs_segctor_thपढ़ो, sci, "segctord");
	अगर (IS_ERR(t)) अणु
		पूर्णांक err = PTR_ERR(t);

		nilfs_err(sci->sc_super, "error %d creating segctord thread",
			  err);
		वापस err;
	पूर्ण
	रुको_event(sci->sc_रुको_task, sci->sc_task != शून्य);
	वापस 0;
पूर्ण

अटल व्योम nilfs_segctor_समाप्त_thपढ़ो(काष्ठा nilfs_sc_info *sci)
	__acquires(&sci->sc_state_lock)
	__releases(&sci->sc_state_lock)
अणु
	sci->sc_state |= NILFS_SEGCTOR_QUIT;

	जबतक (sci->sc_task) अणु
		wake_up(&sci->sc_रुको_daemon);
		spin_unlock(&sci->sc_state_lock);
		रुको_event(sci->sc_रुको_task, sci->sc_task == शून्य);
		spin_lock(&sci->sc_state_lock);
	पूर्ण
पूर्ण

/*
 * Setup & clean-up functions
 */
अटल काष्ठा nilfs_sc_info *nilfs_segctor_new(काष्ठा super_block *sb,
					       काष्ठा nilfs_root *root)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	काष्ठा nilfs_sc_info *sci;

	sci = kzalloc(माप(*sci), GFP_KERNEL);
	अगर (!sci)
		वापस शून्य;

	sci->sc_super = sb;

	nilfs_get_root(root);
	sci->sc_root = root;

	init_रुकोqueue_head(&sci->sc_रुको_request);
	init_रुकोqueue_head(&sci->sc_रुको_daemon);
	init_रुकोqueue_head(&sci->sc_रुको_task);
	spin_lock_init(&sci->sc_state_lock);
	INIT_LIST_HEAD(&sci->sc_dirty_files);
	INIT_LIST_HEAD(&sci->sc_segbufs);
	INIT_LIST_HEAD(&sci->sc_ग_लिखो_logs);
	INIT_LIST_HEAD(&sci->sc_gc_inodes);
	INIT_LIST_HEAD(&sci->sc_iput_queue);
	INIT_WORK(&sci->sc_iput_work, nilfs_iput_work_func);
	समयr_setup(&sci->sc_समयr, nilfs_स्थिरruction_समयout, 0);

	sci->sc_पूर्णांकerval = HZ * NILFS_SC_DEFAULT_TIMEOUT;
	sci->sc_mjcp_freq = HZ * NILFS_SC_DEFAULT_SR_FREQ;
	sci->sc_watermark = NILFS_SC_DEFAULT_WATERMARK;

	अगर (nilfs->ns_पूर्णांकerval)
		sci->sc_पूर्णांकerval = HZ * nilfs->ns_पूर्णांकerval;
	अगर (nilfs->ns_watermark)
		sci->sc_watermark = nilfs->ns_watermark;
	वापस sci;
पूर्ण

अटल व्योम nilfs_segctor_ग_लिखो_out(काष्ठा nilfs_sc_info *sci)
अणु
	पूर्णांक ret, retrycount = NILFS_SC_CLEANUP_RETRY;

	/*
	 * The segctord thपढ़ो was stopped and its समयr was हटाओd.
	 * But some tasks reमुख्य.
	 */
	करो अणु
		काष्ठा nilfs_transaction_info ti;

		nilfs_transaction_lock(sci->sc_super, &ti, 0);
		ret = nilfs_segctor_स्थिरruct(sci, SC_LSEG_SR);
		nilfs_transaction_unlock(sci->sc_super);

		flush_work(&sci->sc_iput_work);

	पूर्ण जबतक (ret && retrycount-- > 0);
पूर्ण

/**
 * nilfs_segctor_destroy - destroy the segment स्थिरructor.
 * @sci: nilfs_sc_info
 *
 * nilfs_segctor_destroy() समाप्तs the segctord thपढ़ो and मुक्तs
 * the nilfs_sc_info काष्ठा.
 * Caller must hold the segment semaphore.
 */
अटल व्योम nilfs_segctor_destroy(काष्ठा nilfs_sc_info *sci)
अणु
	काष्ठा the_nilfs *nilfs = sci->sc_super->s_fs_info;
	पूर्णांक flag;

	up_ग_लिखो(&nilfs->ns_segctor_sem);

	spin_lock(&sci->sc_state_lock);
	nilfs_segctor_समाप्त_thपढ़ो(sci);
	flag = ((sci->sc_state & NILFS_SEGCTOR_COMMIT) || sci->sc_flush_request
		|| sci->sc_seq_request != sci->sc_seq_करोne);
	spin_unlock(&sci->sc_state_lock);

	अगर (flush_work(&sci->sc_iput_work))
		flag = true;

	अगर (flag || !nilfs_segctor_confirm(sci))
		nilfs_segctor_ग_लिखो_out(sci);

	अगर (!list_empty(&sci->sc_dirty_files)) अणु
		nilfs_warn(sci->sc_super,
			   "disposed unprocessed dirty file(s) when stopping log writer");
		nilfs_dispose_list(nilfs, &sci->sc_dirty_files, 1);
	पूर्ण

	अगर (!list_empty(&sci->sc_iput_queue)) अणु
		nilfs_warn(sci->sc_super,
			   "disposed unprocessed inode(s) in iput queue when stopping log writer");
		nilfs_dispose_list(nilfs, &sci->sc_iput_queue, 1);
	पूर्ण

	WARN_ON(!list_empty(&sci->sc_segbufs));
	WARN_ON(!list_empty(&sci->sc_ग_लिखो_logs));

	nilfs_put_root(sci->sc_root);

	करोwn_ग_लिखो(&nilfs->ns_segctor_sem);

	del_समयr_sync(&sci->sc_समयr);
	kमुक्त(sci);
पूर्ण

/**
 * nilfs_attach_log_ग_लिखोr - attach log ग_लिखोr
 * @sb: super block instance
 * @root: root object of the current fileप्रणाली tree
 *
 * This allocates a log ग_लिखोr object, initializes it, and starts the
 * log ग_लिखोr.
 *
 * Return Value: On success, 0 is वापसed. On error, one of the following
 * negative error code is वापसed.
 *
 * %-ENOMEM - Insufficient memory available.
 */
पूर्णांक nilfs_attach_log_ग_लिखोr(काष्ठा super_block *sb, काष्ठा nilfs_root *root)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	पूर्णांक err;

	अगर (nilfs->ns_ग_लिखोr) अणु
		/*
		 * This happens अगर the fileप्रणाली was remounted
		 * पढ़ो/ग_लिखो after nilfs_error degenerated it पूर्णांकo a
		 * पढ़ो-only mount.
		 */
		nilfs_detach_log_ग_लिखोr(sb);
	पूर्ण

	nilfs->ns_ग_लिखोr = nilfs_segctor_new(sb, root);
	अगर (!nilfs->ns_ग_लिखोr)
		वापस -ENOMEM;

	inode_attach_wb(nilfs->ns_bdev->bd_inode, शून्य);

	err = nilfs_segctor_start_thपढ़ो(nilfs->ns_ग_लिखोr);
	अगर (err) अणु
		kमुक्त(nilfs->ns_ग_लिखोr);
		nilfs->ns_ग_लिखोr = शून्य;
	पूर्ण
	वापस err;
पूर्ण

/**
 * nilfs_detach_log_ग_लिखोr - destroy log ग_लिखोr
 * @sb: super block instance
 *
 * This समाप्तs log ग_लिखोr daemon, मुक्तs the log ग_लिखोr object, and
 * destroys list of dirty files.
 */
व्योम nilfs_detach_log_ग_लिखोr(काष्ठा super_block *sb)
अणु
	काष्ठा the_nilfs *nilfs = sb->s_fs_info;
	LIST_HEAD(garbage_list);

	करोwn_ग_लिखो(&nilfs->ns_segctor_sem);
	अगर (nilfs->ns_ग_लिखोr) अणु
		nilfs_segctor_destroy(nilfs->ns_ग_लिखोr);
		nilfs->ns_ग_लिखोr = शून्य;
	पूर्ण

	/* Force to मुक्त the list of dirty files */
	spin_lock(&nilfs->ns_inode_lock);
	अगर (!list_empty(&nilfs->ns_dirty_files)) अणु
		list_splice_init(&nilfs->ns_dirty_files, &garbage_list);
		nilfs_warn(sb,
			   "disposed unprocessed dirty file(s) when detaching log writer");
	पूर्ण
	spin_unlock(&nilfs->ns_inode_lock);
	up_ग_लिखो(&nilfs->ns_segctor_sem);

	nilfs_dispose_list(nilfs, &garbage_list, 1);
पूर्ण
