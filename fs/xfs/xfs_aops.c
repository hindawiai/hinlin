<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * Copyright (c) 2016-2018 Christoph Hellwig.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_iomap.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_bmap_util.h"
#समावेश "xfs_reflink.h"

काष्ठा xfs_ग_लिखोpage_ctx अणु
	काष्ठा iomap_ग_लिखोpage_ctx ctx;
	अचिन्हित पूर्णांक		data_seq;
	अचिन्हित पूर्णांक		cow_seq;
पूर्ण;

अटल अंतरभूत काष्ठा xfs_ग_लिखोpage_ctx *
XFS_WPC(काष्ठा iomap_ग_लिखोpage_ctx *ctx)
अणु
	वापस container_of(ctx, काष्ठा xfs_ग_लिखोpage_ctx, ctx);
पूर्ण

/*
 * Fast and loose check अगर this ग_लिखो could update the on-disk inode size.
 */
अटल अंतरभूत bool xfs_ioend_is_append(काष्ठा iomap_ioend *ioend)
अणु
	वापस ioend->io_offset + ioend->io_size >
		XFS_I(ioend->io_inode)->i_disk_size;
पूर्ण

/*
 * Update on-disk file size now that data has been written to disk.
 */
पूर्णांक
xfs_setfilesize(
	काष्ठा xfs_inode	*ip,
	xfs_off_t		offset,
	माप_प्रकार			size)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_trans	*tp;
	xfs_fमाप_प्रकार		isize;
	पूर्णांक			error;

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_fsyncts, 0, 0, 0, &tp);
	अगर (error)
		वापस error;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	isize = xfs_new_eof(ip, offset + size);
	अगर (!isize) अणु
		xfs_iunlock(ip, XFS_ILOCK_EXCL);
		xfs_trans_cancel(tp);
		वापस 0;
	पूर्ण

	trace_xfs_setfilesize(ip, offset, size);

	ip->i_disk_size = isize;
	xfs_trans_ijoin(tp, ip, XFS_ILOCK_EXCL);
	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);

	वापस xfs_trans_commit(tp);
पूर्ण

/*
 * IO ग_लिखो completion.
 */
STATIC व्योम
xfs_end_ioend(
	काष्ठा iomap_ioend	*ioend)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(ioend->io_inode);
	xfs_off_t		offset = ioend->io_offset;
	माप_प्रकार			size = ioend->io_size;
	अचिन्हित पूर्णांक		nofs_flag;
	पूर्णांक			error;

	/*
	 * We can allocate memory here जबतक करोing ग_लिखोback on behalf of
	 * memory reclaim.  To aव्योम memory allocation deadlocks set the
	 * task-wide nofs context क्रम the following operations.
	 */
	nofs_flag = meदो_स्मृति_nofs_save();

	/*
	 * Just clean up the in-memory काष्ठाures अगर the fs has been shut करोwn.
	 */
	अगर (XFS_FORCED_SHUTDOWN(ip->i_mount)) अणु
		error = -EIO;
		जाओ करोne;
	पूर्ण

	/*
	 * Clean up any COW blocks on an I/O error.
	 */
	error = blk_status_to_त्रुटि_सं(ioend->io_bio->bi_status);
	अगर (unlikely(error)) अणु
		अगर (ioend->io_flags & IOMAP_F_SHARED)
			xfs_reflink_cancel_cow_range(ip, offset, size, true);
		जाओ करोne;
	पूर्ण

	/*
	 * Success: commit the COW or unwritten blocks अगर needed.
	 */
	अगर (ioend->io_flags & IOMAP_F_SHARED)
		error = xfs_reflink_end_cow(ip, offset, size);
	अन्यथा अगर (ioend->io_type == IOMAP_UNWRITTEN)
		error = xfs_iomap_ग_लिखो_unwritten(ip, offset, size, false);

	अगर (!error && xfs_ioend_is_append(ioend))
		error = xfs_setfilesize(ip, ioend->io_offset, ioend->io_size);
करोne:
	iomap_finish_ioends(ioend, error);
	meदो_स्मृति_nofs_restore(nofs_flag);
पूर्ण

/* Finish all pending io completions. */
व्योम
xfs_end_io(
	काष्ठा work_काष्ठा	*work)
अणु
	काष्ठा xfs_inode	*ip =
		container_of(work, काष्ठा xfs_inode, i_ioend_work);
	काष्ठा iomap_ioend	*ioend;
	काष्ठा list_head	पंचांगp;
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&ip->i_ioend_lock, flags);
	list_replace_init(&ip->i_ioend_list, &पंचांगp);
	spin_unlock_irqrestore(&ip->i_ioend_lock, flags);

	iomap_sort_ioends(&पंचांगp);
	जबतक ((ioend = list_first_entry_or_null(&पंचांगp, काष्ठा iomap_ioend,
			io_list))) अणु
		list_del_init(&ioend->io_list);
		iomap_ioend_try_merge(ioend, &पंचांगp);
		xfs_end_ioend(ioend);
	पूर्ण
पूर्ण

STATIC व्योम
xfs_end_bio(
	काष्ठा bio		*bio)
अणु
	काष्ठा iomap_ioend	*ioend = bio->bi_निजी;
	काष्ठा xfs_inode	*ip = XFS_I(ioend->io_inode);
	अचिन्हित दीर्घ		flags;

	spin_lock_irqsave(&ip->i_ioend_lock, flags);
	अगर (list_empty(&ip->i_ioend_list))
		WARN_ON_ONCE(!queue_work(ip->i_mount->m_unwritten_workqueue,
					 &ip->i_ioend_work));
	list_add_tail(&ioend->io_list, &ip->i_ioend_list);
	spin_unlock_irqrestore(&ip->i_ioend_lock, flags);
पूर्ण

/*
 * Fast revalidation of the cached ग_लिखोback mapping. Return true अगर the current
 * mapping is valid, false otherwise.
 */
अटल bool
xfs_imap_valid(
	काष्ठा iomap_ग_लिखोpage_ctx	*wpc,
	काष्ठा xfs_inode		*ip,
	loff_t				offset)
अणु
	अगर (offset < wpc->iomap.offset ||
	    offset >= wpc->iomap.offset + wpc->iomap.length)
		वापस false;
	/*
	 * If this is a COW mapping, it is sufficient to check that the mapping
	 * covers the offset. Be careful to check this first because the caller
	 * can revalidate a COW mapping without updating the data seqno.
	 */
	अगर (wpc->iomap.flags & IOMAP_F_SHARED)
		वापस true;

	/*
	 * This is not a COW mapping. Check the sequence number of the data विभाजन
	 * because concurrent changes could have invalidated the extent. Check
	 * the COW विभाजन because concurrent changes since the last समय we
	 * checked (and found nothing at this offset) could have added
	 * overlapping blocks.
	 */
	अगर (XFS_WPC(wpc)->data_seq != READ_ONCE(ip->i_df.अगर_seq))
		वापस false;
	अगर (xfs_inode_has_cow_data(ip) &&
	    XFS_WPC(wpc)->cow_seq != READ_ONCE(ip->i_cowfp->अगर_seq))
		वापस false;
	वापस true;
पूर्ण

/*
 * Pass in a dellalloc extent and convert it to real extents, वापस the real
 * extent that maps offset_fsb in wpc->iomap.
 *
 * The current page is held locked so nothing could have हटाओd the block
 * backing offset_fsb, although it could have moved from the COW to the data
 * विभाजन by another thपढ़ो.
 */
अटल पूर्णांक
xfs_convert_blocks(
	काष्ठा iomap_ग_लिखोpage_ctx *wpc,
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन,
	loff_t			offset)
अणु
	पूर्णांक			error;
	अचिन्हित		*seq;

	अगर (whichविभाजन == XFS_COW_FORK)
		seq = &XFS_WPC(wpc)->cow_seq;
	अन्यथा
		seq = &XFS_WPC(wpc)->data_seq;

	/*
	 * Attempt to allocate whatever delalloc extent currently backs offset
	 * and put the result पूर्णांकo wpc->iomap.  Allocate in a loop because it
	 * may take several attempts to allocate real blocks क्रम a contiguous
	 * delalloc extent अगर मुक्त space is sufficiently fragmented.
	 */
	करो अणु
		error = xfs_bmapi_convert_delalloc(ip, whichविभाजन, offset,
				&wpc->iomap, seq);
		अगर (error)
			वापस error;
	पूर्ण जबतक (wpc->iomap.offset + wpc->iomap.length <= offset);

	वापस 0;
पूर्ण

अटल पूर्णांक
xfs_map_blocks(
	काष्ठा iomap_ग_लिखोpage_ctx *wpc,
	काष्ठा inode		*inode,
	loff_t			offset)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	sमाप_प्रकार			count = i_blocksize(inode);
	xfs_fileoff_t		offset_fsb = XFS_B_TO_FSBT(mp, offset);
	xfs_fileoff_t		end_fsb = XFS_B_TO_FSB(mp, offset + count);
	xfs_fileoff_t		cow_fsb;
	पूर्णांक			whichविभाजन;
	काष्ठा xfs_bmbt_irec	imap;
	काष्ठा xfs_iext_cursor	icur;
	पूर्णांक			retries = 0;
	पूर्णांक			error = 0;

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	/*
	 * COW विभाजन blocks can overlap data विभाजन blocks even अगर the blocks
	 * aren't shared.  COW I/O always takes precedent, so we must always
	 * check क्रम overlap on reflink inodes unless the mapping is alपढ़ोy a
	 * COW one, or the COW विभाजन hasn't changed from the last समय we looked
	 * at it.
	 *
	 * It's safe to check the COW विभाजन अगर_seq here without the ILOCK because
	 * we've indirectly रक्षित against concurrent updates: ग_लिखोback has
	 * the page locked, which prevents concurrent invalidations by reflink
	 * and directio and prevents concurrent buffered ग_लिखोs to the same
	 * page.  Changes to अगर_seq always happen under i_lock, which protects
	 * against concurrent updates and provides a memory barrier on the way
	 * out that ensures that we always see the current value.
	 */
	अगर (xfs_imap_valid(wpc, ip, offset))
		वापस 0;

	/*
	 * If we करोn't have a valid map, now it's समय to get a new one क्रम this
	 * offset.  This will convert delayed allocations (including COW ones)
	 * पूर्णांकo real extents.  If we वापस without a valid map, it means we
	 * landed in a hole and we skip the block.
	 */
retry:
	cow_fsb = शून्यखाताOFF;
	whichविभाजन = XFS_DATA_FORK;
	xfs_ilock(ip, XFS_ILOCK_SHARED);
	ASSERT(!xfs_need_iपढ़ो_extents(&ip->i_df));

	/*
	 * Check अगर this is offset is covered by a COW extents, and अगर yes use
	 * it directly instead of looking up anything in the data विभाजन.
	 */
	अगर (xfs_inode_has_cow_data(ip) &&
	    xfs_iext_lookup_extent(ip, ip->i_cowfp, offset_fsb, &icur, &imap))
		cow_fsb = imap.br_startoff;
	अगर (cow_fsb != शून्यखाताOFF && cow_fsb <= offset_fsb) अणु
		XFS_WPC(wpc)->cow_seq = READ_ONCE(ip->i_cowfp->अगर_seq);
		xfs_iunlock(ip, XFS_ILOCK_SHARED);

		whichविभाजन = XFS_COW_FORK;
		जाओ allocate_blocks;
	पूर्ण

	/*
	 * No COW extent overlap. Revalidate now that we may have updated
	 * ->cow_seq. If the data mapping is still valid, we're करोne.
	 */
	अगर (xfs_imap_valid(wpc, ip, offset)) अणु
		xfs_iunlock(ip, XFS_ILOCK_SHARED);
		वापस 0;
	पूर्ण

	/*
	 * If we करोn't have a valid map, now it's समय to get a new one क्रम this
	 * offset.  This will convert delayed allocations (including COW ones)
	 * पूर्णांकo real extents.
	 */
	अगर (!xfs_iext_lookup_extent(ip, &ip->i_df, offset_fsb, &icur, &imap))
		imap.br_startoff = end_fsb;	/* fake a hole past खातापूर्ण */
	XFS_WPC(wpc)->data_seq = READ_ONCE(ip->i_df.अगर_seq);
	xfs_iunlock(ip, XFS_ILOCK_SHARED);

	/* landed in a hole or beyond खातापूर्ण? */
	अगर (imap.br_startoff > offset_fsb) अणु
		imap.br_blockcount = imap.br_startoff - offset_fsb;
		imap.br_startoff = offset_fsb;
		imap.br_startblock = HOLESTARTBLOCK;
		imap.br_state = XFS_EXT_NORM;
	पूर्ण

	/*
	 * Truncate to the next COW extent अगर there is one.  This is the only
	 * opportunity to करो this because we can skip COW विभाजन lookups क्रम the
	 * subsequent blocks in the mapping; however, the requirement to treat
	 * the COW range separately reमुख्यs.
	 */
	अगर (cow_fsb != शून्यखाताOFF &&
	    cow_fsb < imap.br_startoff + imap.br_blockcount)
		imap.br_blockcount = cow_fsb - imap.br_startoff;

	/* got a delalloc extent? */
	अगर (imap.br_startblock != HOLESTARTBLOCK &&
	    isnullstartblock(imap.br_startblock))
		जाओ allocate_blocks;

	xfs_bmbt_to_iomap(ip, &wpc->iomap, &imap, 0);
	trace_xfs_map_blocks_found(ip, offset, count, whichविभाजन, &imap);
	वापस 0;
allocate_blocks:
	error = xfs_convert_blocks(wpc, ip, whichविभाजन, offset);
	अगर (error) अणु
		/*
		 * If we failed to find the extent in the COW विभाजन we might have
		 * raced with a COW to data विभाजन conversion or truncate.
		 * Restart the lookup to catch the extent in the data विभाजन क्रम
		 * the क्रमmer हाल, but prevent additional retries to aव्योम
		 * looping क्रमever क्रम the latter हाल.
		 */
		अगर (error == -EAGAIN && whichविभाजन == XFS_COW_FORK && !retries++)
			जाओ retry;
		ASSERT(error != -EAGAIN);
		वापस error;
	पूर्ण

	/*
	 * Due to merging the वापस real extent might be larger than the
	 * original delalloc one.  Trim the वापस extent to the next COW
	 * boundary again to क्रमce a re-lookup.
	 */
	अगर (whichविभाजन != XFS_COW_FORK && cow_fsb != शून्यखाताOFF) अणु
		loff_t		cow_offset = XFS_FSB_TO_B(mp, cow_fsb);

		अगर (cow_offset < wpc->iomap.offset + wpc->iomap.length)
			wpc->iomap.length = cow_offset - wpc->iomap.offset;
	पूर्ण

	ASSERT(wpc->iomap.offset <= offset);
	ASSERT(wpc->iomap.offset + wpc->iomap.length > offset);
	trace_xfs_map_blocks_alloc(ip, offset, count, whichविभाजन, &imap);
	वापस 0;
पूर्ण

अटल पूर्णांक
xfs_prepare_ioend(
	काष्ठा iomap_ioend	*ioend,
	पूर्णांक			status)
अणु
	अचिन्हित पूर्णांक		nofs_flag;

	/*
	 * We can allocate memory here जबतक करोing ग_लिखोback on behalf of
	 * memory reclaim.  To aव्योम memory allocation deadlocks set the
	 * task-wide nofs context क्रम the following operations.
	 */
	nofs_flag = meदो_स्मृति_nofs_save();

	/* Convert CoW extents to regular */
	अगर (!status && (ioend->io_flags & IOMAP_F_SHARED)) अणु
		status = xfs_reflink_convert_cow(XFS_I(ioend->io_inode),
				ioend->io_offset, ioend->io_size);
	पूर्ण

	meदो_स्मृति_nofs_restore(nofs_flag);

	/* send ioends that might require a transaction to the completion wq */
	अगर (xfs_ioend_is_append(ioend) || ioend->io_type == IOMAP_UNWRITTEN ||
	    (ioend->io_flags & IOMAP_F_SHARED))
		ioend->io_bio->bi_end_io = xfs_end_bio;
	वापस status;
पूर्ण

/*
 * If the page has delalloc blocks on it, we need to punch them out beक्रमe we
 * invalidate the page.  If we करोn't, we leave a stale delalloc mapping on the
 * inode that can trip up a later direct I/O पढ़ो operation on the same region.
 *
 * We prevent this by truncating away the delalloc regions on the page.  Because
 * they are delalloc, we can करो this without needing a transaction. Indeed - अगर
 * we get ENOSPC errors, we have to be able to करो this truncation without a
 * transaction as there is no space left क्रम block reservation (typically why we
 * see a ENOSPC in ग_लिखोback).
 */
अटल व्योम
xfs_discard_page(
	काष्ठा page		*page,
	loff_t			fileoff)
अणु
	काष्ठा inode		*inode = page->mapping->host;
	काष्ठा xfs_inode	*ip = XFS_I(inode);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	अचिन्हित पूर्णांक		pageoff = offset_in_page(fileoff);
	xfs_fileoff_t		start_fsb = XFS_B_TO_FSBT(mp, fileoff);
	xfs_fileoff_t		pageoff_fsb = XFS_B_TO_FSBT(mp, pageoff);
	पूर्णांक			error;

	अगर (XFS_FORCED_SHUTDOWN(mp))
		जाओ out_invalidate;

	xfs_alert_ratelimited(mp,
		"page discard on page "PTR_FMT", inode 0x%llx, offset %llu.",
			page, ip->i_ino, fileoff);

	error = xfs_bmap_punch_delalloc_range(ip, start_fsb,
			i_blocks_per_page(inode, page) - pageoff_fsb);
	अगर (error && !XFS_FORCED_SHUTDOWN(mp))
		xfs_alert(mp, "page discard unable to remove delalloc mapping.");
out_invalidate:
	iomap_invalidatepage(page, pageoff, PAGE_SIZE - pageoff);
पूर्ण

अटल स्थिर काष्ठा iomap_ग_लिखोback_ops xfs_ग_लिखोback_ops = अणु
	.map_blocks		= xfs_map_blocks,
	.prepare_ioend		= xfs_prepare_ioend,
	.discard_page		= xfs_discard_page,
पूर्ण;

STATIC पूर्णांक
xfs_vm_ग_लिखोpage(
	काष्ठा page		*page,
	काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा xfs_ग_लिखोpage_ctx wpc = अणु पूर्ण;

	अगर (WARN_ON_ONCE(current->journal_info)) अणु
		redirty_page_क्रम_ग_लिखोpage(wbc, page);
		unlock_page(page);
		वापस 0;
	पूर्ण

	वापस iomap_ग_लिखोpage(page, wbc, &wpc.ctx, &xfs_ग_लिखोback_ops);
पूर्ण

STATIC पूर्णांक
xfs_vm_ग_लिखोpages(
	काष्ठा address_space	*mapping,
	काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा xfs_ग_लिखोpage_ctx wpc = अणु पूर्ण;

	/*
	 * Writing back data in a transaction context can result in recursive
	 * transactions. This is bad, so issue a warning and get out of here.
	 */
	अगर (WARN_ON_ONCE(current->journal_info))
		वापस 0;

	xfs_अगरlags_clear(XFS_I(mapping->host), XFS_ITRUNCATED);
	वापस iomap_ग_लिखोpages(mapping, wbc, &wpc.ctx, &xfs_ग_लिखोback_ops);
पूर्ण

STATIC पूर्णांक
xfs_dax_ग_लिखोpages(
	काष्ठा address_space	*mapping,
	काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(mapping->host);

	xfs_अगरlags_clear(ip, XFS_ITRUNCATED);
	वापस dax_ग_लिखोback_mapping_range(mapping,
			xfs_inode_buftarg(ip)->bt_daxdev, wbc);
पूर्ण

STATIC sector_t
xfs_vm_bmap(
	काष्ठा address_space	*mapping,
	sector_t		block)
अणु
	काष्ठा xfs_inode	*ip = XFS_I(mapping->host);

	trace_xfs_vm_bmap(ip);

	/*
	 * The swap code (ab-)uses ->bmap to get a block mapping and then
	 * bypasses the file प्रणाली क्रम actual I/O.  We really can't allow
	 * that on reflinks inodes, so we have to skip out here.  And yes,
	 * 0 is the magic code क्रम a bmap error.
	 *
	 * Since we करोn't pass back blockdev info, we can't वापस bmap
	 * inक्रमmation क्रम rt files either.
	 */
	अगर (xfs_is_cow_inode(ip) || XFS_IS_REALTIME_INODE(ip))
		वापस 0;
	वापस iomap_bmap(mapping, block, &xfs_पढ़ो_iomap_ops);
पूर्ण

STATIC पूर्णांक
xfs_vm_पढ़ोpage(
	काष्ठा file		*unused,
	काष्ठा page		*page)
अणु
	वापस iomap_पढ़ोpage(page, &xfs_पढ़ो_iomap_ops);
पूर्ण

STATIC व्योम
xfs_vm_पढ़ोahead(
	काष्ठा पढ़ोahead_control	*rac)
अणु
	iomap_पढ़ोahead(rac, &xfs_पढ़ो_iomap_ops);
पूर्ण

अटल पूर्णांक
xfs_iomap_swapfile_activate(
	काष्ठा swap_info_काष्ठा		*sis,
	काष्ठा file			*swap_file,
	sector_t			*span)
अणु
	sis->bdev = xfs_inode_buftarg(XFS_I(file_inode(swap_file)))->bt_bdev;
	वापस iomap_swapfile_activate(sis, swap_file, span,
			&xfs_पढ़ो_iomap_ops);
पूर्ण

स्थिर काष्ठा address_space_operations xfs_address_space_operations = अणु
	.पढ़ोpage		= xfs_vm_पढ़ोpage,
	.पढ़ोahead		= xfs_vm_पढ़ोahead,
	.ग_लिखोpage		= xfs_vm_ग_लिखोpage,
	.ग_लिखोpages		= xfs_vm_ग_लिखोpages,
	.set_page_dirty		= iomap_set_page_dirty,
	.releasepage		= iomap_releasepage,
	.invalidatepage		= iomap_invalidatepage,
	.bmap			= xfs_vm_bmap,
	.direct_IO		= noop_direct_IO,
	.migratepage		= iomap_migrate_page,
	.is_partially_uptodate  = iomap_is_partially_uptodate,
	.error_हटाओ_page	= generic_error_हटाओ_page,
	.swap_activate		= xfs_iomap_swapfile_activate,
पूर्ण;

स्थिर काष्ठा address_space_operations xfs_dax_aops = अणु
	.ग_लिखोpages		= xfs_dax_ग_लिखोpages,
	.direct_IO		= noop_direct_IO,
	.set_page_dirty		= noop_set_page_dirty,
	.invalidatepage		= noop_invalidatepage,
	.swap_activate		= xfs_iomap_swapfile_activate,
पूर्ण;
