<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2006 Silicon Graphics, Inc.
 * Copyright (c) 2012 Red Hat, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_bit.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_defer.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_bmap_util.h"
#समावेश "xfs_bmap_btree.h"
#समावेश "xfs_rtalloc.h"
#समावेश "xfs_error.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_trans_space.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_iomap.h"
#समावेश "xfs_reflink.h"

/* Kernel only BMAP related definitions and functions */

/*
 * Convert the given file प्रणाली block to a disk block.  We have to treat it
 * dअगरferently based on whether the file is a real समय file or not, because the
 * bmap code करोes.
 */
xfs_daddr_t
xfs_fsb_to_db(काष्ठा xfs_inode *ip, xfs_fsblock_t fsb)
अणु
	अगर (XFS_IS_REALTIME_INODE(ip))
		वापस XFS_FSB_TO_BB(ip->i_mount, fsb);
	वापस XFS_FSB_TO_DADDR(ip->i_mount, fsb);
पूर्ण

/*
 * Routine to zero an extent on disk allocated to the specअगरic inode.
 *
 * The VFS functions take a linearised fileप्रणाली block offset, so we have to
 * convert the sparse xfs fsb to the right क्रमmat first.
 * VFS types are real funky, too.
 */
पूर्णांक
xfs_zero_extent(
	काष्ठा xfs_inode	*ip,
	xfs_fsblock_t		start_fsb,
	xfs_off_t		count_fsb)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_buftarg	*target = xfs_inode_buftarg(ip);
	xfs_daddr_t		sector = xfs_fsb_to_db(ip, start_fsb);
	sector_t		block = XFS_BB_TO_FSBT(mp, sector);

	वापस blkdev_issue_zeroout(target->bt_bdev,
		block << (mp->m_super->s_blocksize_bits - 9),
		count_fsb << (mp->m_super->s_blocksize_bits - 9),
		GFP_NOFS, 0);
पूर्ण

#अगर_घोषित CONFIG_XFS_RT
पूर्णांक
xfs_bmap_rtalloc(
	काष्ठा xfs_bदो_स्मृतिa	*ap)
अणु
	काष्ठा xfs_mount	*mp = ap->ip->i_mount;
	xfs_fileoff_t		orig_offset = ap->offset;
	xfs_rtblock_t		rtb;
	xfs_extlen_t		prod = 0;  /* product factor क्रम allocators */
	xfs_extlen_t		mod = 0;   /* product factor क्रम allocators */
	xfs_extlen_t		ralen = 0; /* realसमय allocation length */
	xfs_extlen_t		align;     /* minimum allocation alignment */
	xfs_extlen_t		orig_length = ap->length;
	xfs_extlen_t		minlen = mp->m_sb.sb_rextsize;
	xfs_extlen_t		raminlen;
	bool			rtlocked = false;
	bool			ignore_locality = false;
	पूर्णांक			error;

	align = xfs_get_extsz_hपूर्णांक(ap->ip);
retry:
	prod = align / mp->m_sb.sb_rextsize;
	error = xfs_bmap_extsize_align(mp, &ap->got, &ap->prev,
					align, 1, ap->eof, 0,
					ap->conv, &ap->offset, &ap->length);
	अगर (error)
		वापस error;
	ASSERT(ap->length);
	ASSERT(ap->length % mp->m_sb.sb_rextsize == 0);

	/*
	 * If we shअगरted the file offset करोwnward to satisfy an extent size
	 * hपूर्णांक, increase minlen by that amount so that the allocator won't
	 * give us an allocation that's too लघु to cover at least one of the
	 * blocks that the caller asked क्रम.
	 */
	अगर (ap->offset != orig_offset)
		minlen += orig_offset - ap->offset;

	/*
	 * If the offset & length are not perfectly aligned
	 * then समाप्त prod, it will just get us in trouble.
	 */
	भाग_u64_rem(ap->offset, align, &mod);
	अगर (mod || ap->length % align)
		prod = 1;
	/*
	 * Set ralen to be the actual requested length in rtextents.
	 */
	ralen = ap->length / mp->m_sb.sb_rextsize;
	/*
	 * If the old value was बंद enough to MAXEXTLEN that
	 * we rounded up to it, cut it back so it's valid again.
	 * Note that अगर it's a really large request (bigger than
	 * MAXEXTLEN), we करोn't hear about that number, and can't
	 * adjust the starting poपूर्णांक to match it.
	 */
	अगर (ralen * mp->m_sb.sb_rextsize >= MAXEXTLEN)
		ralen = MAXEXTLEN / mp->m_sb.sb_rextsize;

	/*
	 * Lock out modअगरications to both the RT biपंचांगap and summary inodes
	 */
	अगर (!rtlocked) अणु
		xfs_ilock(mp->m_rbmip, XFS_ILOCK_EXCL|XFS_ILOCK_RTBITMAP);
		xfs_trans_ijoin(ap->tp, mp->m_rbmip, XFS_ILOCK_EXCL);
		xfs_ilock(mp->m_rsumip, XFS_ILOCK_EXCL|XFS_ILOCK_RTSUM);
		xfs_trans_ijoin(ap->tp, mp->m_rsumip, XFS_ILOCK_EXCL);
		rtlocked = true;
	पूर्ण

	/*
	 * If it's an allocation to an empty file at offset 0,
	 * pick an extent that will space things out in the rt area.
	 */
	अगर (ap->eof && ap->offset == 0) अणु
		xfs_rtblock_t rtx; /* realसमय extent no */

		error = xfs_rtpick_extent(mp, ap->tp, ralen, &rtx);
		अगर (error)
			वापस error;
		ap->blkno = rtx * mp->m_sb.sb_rextsize;
	पूर्ण अन्यथा अणु
		ap->blkno = 0;
	पूर्ण

	xfs_bmap_adjacent(ap);

	/*
	 * Realसमय allocation, करोne through xfs_rtallocate_extent.
	 */
	अगर (ignore_locality)
		ap->blkno = 0;
	अन्यथा
		करो_भाग(ap->blkno, mp->m_sb.sb_rextsize);
	rtb = ap->blkno;
	ap->length = ralen;
	raminlen = max_t(xfs_extlen_t, 1, minlen / mp->m_sb.sb_rextsize);
	error = xfs_rtallocate_extent(ap->tp, ap->blkno, raminlen, ap->length,
			&ralen, ap->wasdel, prod, &rtb);
	अगर (error)
		वापस error;

	अगर (rtb != शून्यRTBLOCK) अणु
		ap->blkno = rtb * mp->m_sb.sb_rextsize;
		ap->length = ralen * mp->m_sb.sb_rextsize;
		ap->ip->i_nblocks += ap->length;
		xfs_trans_log_inode(ap->tp, ap->ip, XFS_ILOG_CORE);
		अगर (ap->wasdel)
			ap->ip->i_delayed_blks -= ap->length;
		/*
		 * Adjust the disk quota also. This was reserved
		 * earlier.
		 */
		xfs_trans_mod_dquot_byino(ap->tp, ap->ip,
			ap->wasdel ? XFS_TRANS_DQ_DELRTBCOUNT :
					XFS_TRANS_DQ_RTBCOUNT, ap->length);
		वापस 0;
	पूर्ण

	अगर (align > mp->m_sb.sb_rextsize) अणु
		/*
		 * We previously enlarged the request length to try to satisfy
		 * an extent size hपूर्णांक.  The allocator didn't वापस anything,
		 * so reset the parameters to the original values and try again
		 * without alignment criteria.
		 */
		ap->offset = orig_offset;
		ap->length = orig_length;
		minlen = align = mp->m_sb.sb_rextsize;
		जाओ retry;
	पूर्ण

	अगर (!ignore_locality && ap->blkno != 0) अणु
		/*
		 * If we can't allocate near a specअगरic rt extent, try again
		 * without locality criteria.
		 */
		ignore_locality = true;
		जाओ retry;
	पूर्ण

	ap->blkno = शून्यFSBLOCK;
	ap->length = 0;
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_XFS_RT */

/*
 * Extent tree block counting routines.
 */

/*
 * Count leaf blocks given a range of extent records.  Delayed allocation
 * extents are not counted towards the totals.
 */
xfs_extnum_t
xfs_bmap_count_leaves(
	काष्ठा xfs_अगरork	*अगरp,
	xfs_filblks_t		*count)
अणु
	काष्ठा xfs_iext_cursor	icur;
	काष्ठा xfs_bmbt_irec	got;
	xfs_extnum_t		numrecs = 0;

	क्रम_each_xfs_iext(अगरp, &icur, &got) अणु
		अगर (!isnullstartblock(got.br_startblock)) अणु
			*count += got.br_blockcount;
			numrecs++;
		पूर्ण
	पूर्ण

	वापस numrecs;
पूर्ण

/*
 * Count fsblocks of the given विभाजन.  Delayed allocation extents are
 * not counted towards the totals.
 */
पूर्णांक
xfs_bmap_count_blocks(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन,
	xfs_extnum_t		*nextents,
	xfs_filblks_t		*count)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	काष्ठा xfs_btree_cur	*cur;
	xfs_extlen_t		btblocks = 0;
	पूर्णांक			error;

	*nextents = 0;
	*count = 0;

	अगर (!अगरp)
		वापस 0;

	चयन (अगरp->अगर_क्रमmat) अणु
	हाल XFS_DINODE_FMT_BTREE:
		error = xfs_iपढ़ो_extents(tp, ip, whichविभाजन);
		अगर (error)
			वापस error;

		cur = xfs_bmbt_init_cursor(mp, tp, ip, whichविभाजन);
		error = xfs_btree_count_blocks(cur, &btblocks);
		xfs_btree_del_cursor(cur, error);
		अगर (error)
			वापस error;

		/*
		 * xfs_btree_count_blocks includes the root block contained in
		 * the inode विभाजन in @btblocks, so subtract one because we're
		 * only पूर्णांकerested in allocated disk blocks.
		 */
		*count += btblocks - 1;

		/* fall through */
	हाल XFS_DINODE_FMT_EXTENTS:
		*nextents = xfs_bmap_count_leaves(अगरp, count);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
xfs_getbmap_report_one(
	काष्ठा xfs_inode	*ip,
	काष्ठा getbmapx		*bmv,
	काष्ठा kgetbmap		*out,
	पूर्णांक64_t			bmv_end,
	काष्ठा xfs_bmbt_irec	*got)
अणु
	काष्ठा kgetbmap		*p = out + bmv->bmv_entries;
	bool			shared = false;
	पूर्णांक			error;

	error = xfs_reflink_trim_around_shared(ip, got, &shared);
	अगर (error)
		वापस error;

	अगर (isnullstartblock(got->br_startblock) ||
	    got->br_startblock == DELAYSTARTBLOCK) अणु
		/*
		 * Delalloc extents that start beyond खातापूर्ण can occur due to
		 * speculative खातापूर्ण allocation when the delalloc extent is larger
		 * than the largest मुक्तspace extent at conversion समय.  These
		 * extents cannot be converted by data ग_लिखोback, so can exist
		 * here even अगर we are not supposed to be finding delalloc
		 * extents.
		 */
		अगर (got->br_startoff < XFS_B_TO_FSB(ip->i_mount, XFS_ISIZE(ip)))
			ASSERT((bmv->bmv_अगरlags & BMV_IF_DELALLOC) != 0);

		p->bmv_oflags |= BMV_OF_DELALLOC;
		p->bmv_block = -2;
	पूर्ण अन्यथा अणु
		p->bmv_block = xfs_fsb_to_db(ip, got->br_startblock);
	पूर्ण

	अगर (got->br_state == XFS_EXT_UNWRITTEN &&
	    (bmv->bmv_अगरlags & BMV_IF_PREALLOC))
		p->bmv_oflags |= BMV_OF_PREALLOC;

	अगर (shared)
		p->bmv_oflags |= BMV_OF_SHARED;

	p->bmv_offset = XFS_FSB_TO_BB(ip->i_mount, got->br_startoff);
	p->bmv_length = XFS_FSB_TO_BB(ip->i_mount, got->br_blockcount);

	bmv->bmv_offset = p->bmv_offset + p->bmv_length;
	bmv->bmv_length = max(0LL, bmv_end - bmv->bmv_offset);
	bmv->bmv_entries++;
	वापस 0;
पूर्ण

अटल व्योम
xfs_getbmap_report_hole(
	काष्ठा xfs_inode	*ip,
	काष्ठा getbmapx		*bmv,
	काष्ठा kgetbmap		*out,
	पूर्णांक64_t			bmv_end,
	xfs_fileoff_t		bno,
	xfs_fileoff_t		end)
अणु
	काष्ठा kgetbmap		*p = out + bmv->bmv_entries;

	अगर (bmv->bmv_अगरlags & BMV_IF_NO_HOLES)
		वापस;

	p->bmv_block = -1;
	p->bmv_offset = XFS_FSB_TO_BB(ip->i_mount, bno);
	p->bmv_length = XFS_FSB_TO_BB(ip->i_mount, end - bno);

	bmv->bmv_offset = p->bmv_offset + p->bmv_length;
	bmv->bmv_length = max(0LL, bmv_end - bmv->bmv_offset);
	bmv->bmv_entries++;
पूर्ण

अटल अंतरभूत bool
xfs_getbmap_full(
	काष्ठा getbmapx		*bmv)
अणु
	वापस bmv->bmv_length == 0 || bmv->bmv_entries >= bmv->bmv_count - 1;
पूर्ण

अटल bool
xfs_getbmap_next_rec(
	काष्ठा xfs_bmbt_irec	*rec,
	xfs_fileoff_t		total_end)
अणु
	xfs_fileoff_t		end = rec->br_startoff + rec->br_blockcount;

	अगर (end == total_end)
		वापस false;

	rec->br_startoff += rec->br_blockcount;
	अगर (!isnullstartblock(rec->br_startblock) &&
	    rec->br_startblock != DELAYSTARTBLOCK)
		rec->br_startblock += rec->br_blockcount;
	rec->br_blockcount = total_end - end;
	वापस true;
पूर्ण

/*
 * Get inode's extents as described in bmv, and क्रमmat क्रम output.
 * Calls क्रमmatter to fill the user's buffer until all extents
 * are mapped, until the passed-in bmv->bmv_count slots have
 * been filled, or until the क्रमmatter लघु-circuits the loop,
 * अगर it is tracking filled-in extents on its own.
 */
पूर्णांक						/* error code */
xfs_getbmap(
	काष्ठा xfs_inode	*ip,
	काष्ठा getbmapx		*bmv,		/* user bmap काष्ठाure */
	काष्ठा kgetbmap		*out)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	पूर्णांक			अगरlags = bmv->bmv_अगरlags;
	पूर्णांक			whichविभाजन, lock, error = 0;
	पूर्णांक64_t			bmv_end, max_len;
	xfs_fileoff_t		bno, first_bno;
	काष्ठा xfs_अगरork	*अगरp;
	काष्ठा xfs_bmbt_irec	got, rec;
	xfs_filblks_t		len;
	काष्ठा xfs_iext_cursor	icur;

	अगर (bmv->bmv_अगरlags & ~BMV_IF_VALID)
		वापस -EINVAL;
#अगर_अघोषित DEBUG
	/* Only allow CoW विभाजन queries अगर we're debugging. */
	अगर (अगरlags & BMV_IF_COWFORK)
		वापस -EINVAL;
#पूर्ण_अगर
	अगर ((अगरlags & BMV_IF_ATTRFORK) && (अगरlags & BMV_IF_COWFORK))
		वापस -EINVAL;

	अगर (bmv->bmv_length < -1)
		वापस -EINVAL;
	bmv->bmv_entries = 0;
	अगर (bmv->bmv_length == 0)
		वापस 0;

	अगर (अगरlags & BMV_IF_ATTRFORK)
		whichविभाजन = XFS_ATTR_FORK;
	अन्यथा अगर (अगरlags & BMV_IF_COWFORK)
		whichविभाजन = XFS_COW_FORK;
	अन्यथा
		whichविभाजन = XFS_DATA_FORK;
	अगरp = XFS_IFORK_PTR(ip, whichविभाजन);

	xfs_ilock(ip, XFS_IOLOCK_SHARED);
	चयन (whichविभाजन) अणु
	हाल XFS_ATTR_FORK:
		अगर (!XFS_IFORK_Q(ip))
			जाओ out_unlock_iolock;

		max_len = 1LL << 32;
		lock = xfs_ilock_attr_map_shared(ip);
		अवरोध;
	हाल XFS_COW_FORK:
		/* No CoW विभाजन? Just वापस */
		अगर (!अगरp)
			जाओ out_unlock_iolock;

		अगर (xfs_get_cowextsz_hपूर्णांक(ip))
			max_len = mp->m_super->s_maxbytes;
		अन्यथा
			max_len = XFS_ISIZE(ip);

		lock = XFS_ILOCK_SHARED;
		xfs_ilock(ip, lock);
		अवरोध;
	हाल XFS_DATA_FORK:
		अगर (!(अगरlags & BMV_IF_DELALLOC) &&
		    (ip->i_delayed_blks || XFS_ISIZE(ip) > ip->i_disk_size)) अणु
			error = filemap_ग_लिखो_and_रुको(VFS_I(ip)->i_mapping);
			अगर (error)
				जाओ out_unlock_iolock;

			/*
			 * Even after flushing the inode, there can still be
			 * delalloc blocks on the inode beyond खातापूर्ण due to
			 * speculative pपुनः_स्मृतिation.  These are not हटाओd
			 * until the release function is called or the inode
			 * is inactivated.  Hence we cannot निश्चित here that
			 * ip->i_delayed_blks == 0.
			 */
		पूर्ण

		अगर (xfs_get_extsz_hपूर्णांक(ip) ||
		    (ip->i_dअगरlags &
		     (XFS_DIFLAG_PREALLOC | XFS_DIFLAG_APPEND)))
			max_len = mp->m_super->s_maxbytes;
		अन्यथा
			max_len = XFS_ISIZE(ip);

		lock = xfs_ilock_data_map_shared(ip);
		अवरोध;
	पूर्ण

	चयन (अगरp->अगर_क्रमmat) अणु
	हाल XFS_DINODE_FMT_EXTENTS:
	हाल XFS_DINODE_FMT_BTREE:
		अवरोध;
	हाल XFS_DINODE_FMT_LOCAL:
		/* Local क्रमmat inode विभाजनs report no extents. */
		जाओ out_unlock_ilock;
	शेष:
		error = -EINVAL;
		जाओ out_unlock_ilock;
	पूर्ण

	अगर (bmv->bmv_length == -1) अणु
		max_len = XFS_FSB_TO_BB(mp, XFS_B_TO_FSB(mp, max_len));
		bmv->bmv_length = max(0LL, max_len - bmv->bmv_offset);
	पूर्ण

	bmv_end = bmv->bmv_offset + bmv->bmv_length;

	first_bno = bno = XFS_BB_TO_FSBT(mp, bmv->bmv_offset);
	len = XFS_BB_TO_FSB(mp, bmv->bmv_length);

	error = xfs_iपढ़ो_extents(शून्य, ip, whichविभाजन);
	अगर (error)
		जाओ out_unlock_ilock;

	अगर (!xfs_iext_lookup_extent(ip, अगरp, bno, &icur, &got)) अणु
		/*
		 * Report a whole-file hole अगर the delalloc flag is set to
		 * stay compatible with the old implementation.
		 */
		अगर (अगरlags & BMV_IF_DELALLOC)
			xfs_getbmap_report_hole(ip, bmv, out, bmv_end, bno,
					XFS_B_TO_FSB(mp, XFS_ISIZE(ip)));
		जाओ out_unlock_ilock;
	पूर्ण

	जबतक (!xfs_getbmap_full(bmv)) अणु
		xfs_trim_extent(&got, first_bno, len);

		/*
		 * Report an entry क्रम a hole अगर this extent करोesn't directly
		 * follow the previous one.
		 */
		अगर (got.br_startoff > bno) अणु
			xfs_getbmap_report_hole(ip, bmv, out, bmv_end, bno,
					got.br_startoff);
			अगर (xfs_getbmap_full(bmv))
				अवरोध;
		पूर्ण

		/*
		 * In order to report shared extents accurately, we report each
		 * distinct shared / unshared part of a single bmbt record with
		 * an inभागidual getbmapx record.
		 */
		bno = got.br_startoff + got.br_blockcount;
		rec = got;
		करो अणु
			error = xfs_getbmap_report_one(ip, bmv, out, bmv_end,
					&rec);
			अगर (error || xfs_getbmap_full(bmv))
				जाओ out_unlock_ilock;
		पूर्ण जबतक (xfs_getbmap_next_rec(&rec, bno));

		अगर (!xfs_iext_next_extent(अगरp, &icur, &got)) अणु
			xfs_fileoff_t	end = XFS_B_TO_FSB(mp, XFS_ISIZE(ip));

			out[bmv->bmv_entries - 1].bmv_oflags |= BMV_OF_LAST;

			अगर (whichविभाजन != XFS_ATTR_FORK && bno < end &&
			    !xfs_getbmap_full(bmv)) अणु
				xfs_getbmap_report_hole(ip, bmv, out, bmv_end,
						bno, end);
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (bno >= first_bno + len)
			अवरोध;
	पूर्ण

out_unlock_ilock:
	xfs_iunlock(ip, lock);
out_unlock_iolock:
	xfs_iunlock(ip, XFS_IOLOCK_SHARED);
	वापस error;
पूर्ण

/*
 * Dead simple method of punching delalyed allocation blocks from a range in
 * the inode.  This will always punch out both the start and end blocks, even
 * अगर the ranges only partially overlap them, so it is up to the caller to
 * ensure that partial blocks are not passed in.
 */
पूर्णांक
xfs_bmap_punch_delalloc_range(
	काष्ठा xfs_inode	*ip,
	xfs_fileoff_t		start_fsb,
	xfs_fileoff_t		length)
अणु
	काष्ठा xfs_अगरork	*अगरp = &ip->i_df;
	xfs_fileoff_t		end_fsb = start_fsb + length;
	काष्ठा xfs_bmbt_irec	got, del;
	काष्ठा xfs_iext_cursor	icur;
	पूर्णांक			error = 0;

	ASSERT(!xfs_need_iपढ़ो_extents(अगरp));

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	अगर (!xfs_iext_lookup_extent_beक्रमe(ip, अगरp, &end_fsb, &icur, &got))
		जाओ out_unlock;

	जबतक (got.br_startoff + got.br_blockcount > start_fsb) अणु
		del = got;
		xfs_trim_extent(&del, start_fsb, length);

		/*
		 * A delete can push the cursor क्रमward. Step back to the
		 * previous extent on non-delalloc or extents outside the
		 * target range.
		 */
		अगर (!del.br_blockcount ||
		    !isnullstartblock(del.br_startblock)) अणु
			अगर (!xfs_iext_prev_extent(अगरp, &icur, &got))
				अवरोध;
			जारी;
		पूर्ण

		error = xfs_bmap_del_extent_delay(ip, XFS_DATA_FORK, &icur,
						  &got, &del);
		अगर (error || !xfs_iext_get_extent(अगरp, &icur, &got))
			अवरोध;
	पूर्ण

out_unlock:
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;
पूर्ण

/*
 * Test whether it is appropriate to check an inode क्रम and मुक्त post खातापूर्ण
 * blocks. The 'force' parameter determines whether we should also consider
 * regular files that are marked pपुनः_स्मृतिated or append-only.
 */
bool
xfs_can_मुक्त_eofblocks(
	काष्ठा xfs_inode	*ip,
	bool			क्रमce)
अणु
	काष्ठा xfs_bmbt_irec	imap;
	काष्ठा xfs_mount	*mp = ip->i_mount;
	xfs_fileoff_t		end_fsb;
	xfs_fileoff_t		last_fsb;
	पूर्णांक			nimaps = 1;
	पूर्णांक			error;

	/*
	 * Caller must either hold the exclusive io lock; or be inactivating
	 * the inode, which guarantees there are no other users of the inode.
	 */
	ASSERT(xfs_isilocked(ip, XFS_IOLOCK_EXCL) ||
	       (VFS_I(ip)->i_state & I_FREEING));

	/* pपुनः_स्मृति/delalloc exists only on regular files */
	अगर (!S_ISREG(VFS_I(ip)->i_mode))
		वापस false;

	/*
	 * Zero sized files with no cached pages and delalloc blocks will not
	 * have speculative pपुनः_स्मृति/delalloc blocks to हटाओ.
	 */
	अगर (VFS_I(ip)->i_size == 0 &&
	    VFS_I(ip)->i_mapping->nrpages == 0 &&
	    ip->i_delayed_blks == 0)
		वापस false;

	/* If we haven't read in the extent list, then don't करो it now. */
	अगर (xfs_need_iपढ़ो_extents(&ip->i_df))
		वापस false;

	/*
	 * Do not मुक्त real pपुनः_स्मृतिated or append-only files unless the file
	 * has delalloc blocks and we are क्रमced to हटाओ them.
	 */
	अगर (ip->i_dअगरlags & (XFS_DIFLAG_PREALLOC | XFS_DIFLAG_APPEND))
		अगर (!क्रमce || ip->i_delayed_blks == 0)
			वापस false;

	/*
	 * Do not try to मुक्त post-खातापूर्ण blocks अगर खातापूर्ण is beyond the end of the
	 * range supported by the page cache, because the truncation will loop
	 * क्रमever.
	 */
	end_fsb = XFS_B_TO_FSB(mp, (xfs_ufमाप_प्रकार)XFS_ISIZE(ip));
	last_fsb = XFS_B_TO_FSB(mp, mp->m_super->s_maxbytes);
	अगर (last_fsb <= end_fsb)
		वापस false;

	/*
	 * Look up the mapping क्रम the first block past खातापूर्ण.  If we can't find
	 * it, there's nothing to मुक्त.
	 */
	xfs_ilock(ip, XFS_ILOCK_SHARED);
	error = xfs_bmapi_पढ़ो(ip, end_fsb, last_fsb - end_fsb, &imap, &nimaps,
			0);
	xfs_iunlock(ip, XFS_ILOCK_SHARED);
	अगर (error || nimaps == 0)
		वापस false;

	/*
	 * If there's a real mapping there or there are delayed allocation
	 * reservations, then we have post-खातापूर्ण blocks to try to मुक्त.
	 */
	वापस imap.br_startblock != HOLESTARTBLOCK || ip->i_delayed_blks;
पूर्ण

/*
 * This is called to मुक्त any blocks beyond eof. The caller must hold
 * IOLOCK_EXCL unless we are in the inode reclaim path and have the only
 * reference to the inode.
 */
पूर्णांक
xfs_मुक्त_eofblocks(
	काष्ठा xfs_inode	*ip)
अणु
	काष्ठा xfs_trans	*tp;
	काष्ठा xfs_mount	*mp = ip->i_mount;
	पूर्णांक			error;

	/* Attach the dquots to the inode up front. */
	error = xfs_qm_dqattach(ip);
	अगर (error)
		वापस error;

	/* Wait on dio to ensure i_size has settled. */
	inode_dio_रुको(VFS_I(ip));

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_itruncate, 0, 0, 0, &tp);
	अगर (error) अणु
		ASSERT(XFS_FORCED_SHUTDOWN(mp));
		वापस error;
	पूर्ण

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, 0);

	/*
	 * Do not update the on-disk file size.  If we update the on-disk file
	 * size and then the प्रणाली crashes beक्रमe the contents of the file are
	 * flushed to disk then the files may be full of holes (ie शून्य files
	 * bug).
	 */
	error = xfs_itruncate_extents_flags(&tp, ip, XFS_DATA_FORK,
				XFS_ISIZE(ip), XFS_BMAPI_NODISCARD);
	अगर (error)
		जाओ err_cancel;

	error = xfs_trans_commit(tp);
	अगर (error)
		जाओ out_unlock;

	xfs_inode_clear_eofblocks_tag(ip);
	जाओ out_unlock;

err_cancel:
	/*
	 * If we get an error at this poपूर्णांक we simply करोn't
	 * bother truncating the file.
	 */
	xfs_trans_cancel(tp);
out_unlock:
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;
पूर्ण

पूर्णांक
xfs_alloc_file_space(
	काष्ठा xfs_inode	*ip,
	xfs_off_t		offset,
	xfs_off_t		len,
	पूर्णांक			alloc_type)
अणु
	xfs_mount_t		*mp = ip->i_mount;
	xfs_off_t		count;
	xfs_filblks_t		allocated_fsb;
	xfs_filblks_t		allocatesize_fsb;
	xfs_extlen_t		extsz, temp;
	xfs_fileoff_t		startoffset_fsb;
	xfs_fileoff_t		enकरोffset_fsb;
	पूर्णांक			nimaps;
	पूर्णांक			rt;
	xfs_trans_t		*tp;
	xfs_bmbt_irec_t		imaps[1], *imapp;
	पूर्णांक			error;

	trace_xfs_alloc_file_space(ip);

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	error = xfs_qm_dqattach(ip);
	अगर (error)
		वापस error;

	अगर (len <= 0)
		वापस -EINVAL;

	rt = XFS_IS_REALTIME_INODE(ip);
	extsz = xfs_get_extsz_hपूर्णांक(ip);

	count = len;
	imapp = &imaps[0];
	nimaps = 1;
	startoffset_fsb	= XFS_B_TO_FSBT(mp, offset);
	enकरोffset_fsb = XFS_B_TO_FSB(mp, offset + count);
	allocatesize_fsb = enकरोffset_fsb - startoffset_fsb;

	/*
	 * Allocate file space until करोne or until there is an error
	 */
	जबतक (allocatesize_fsb && !error) अणु
		xfs_fileoff_t	s, e;
		अचिन्हित पूर्णांक	dblocks, rblocks, resblks;

		/*
		 * Determine space reservations क्रम data/realसमय.
		 */
		अगर (unlikely(extsz)) अणु
			s = startoffset_fsb;
			करो_भाग(s, extsz);
			s *= extsz;
			e = startoffset_fsb + allocatesize_fsb;
			भाग_u64_rem(startoffset_fsb, extsz, &temp);
			अगर (temp)
				e += temp;
			भाग_u64_rem(e, extsz, &temp);
			अगर (temp)
				e += extsz - temp;
		पूर्ण अन्यथा अणु
			s = 0;
			e = allocatesize_fsb;
		पूर्ण

		/*
		 * The transaction reservation is limited to a 32-bit block
		 * count, hence we need to limit the number of blocks we are
		 * trying to reserve to aव्योम an overflow. We can't allocate
		 * more than @nimaps extents, and an extent is limited on disk
		 * to MAXEXTLEN (21 bits), so use that to enक्रमce the limit.
		 */
		resblks = min_t(xfs_fileoff_t, (e - s), (MAXEXTLEN * nimaps));
		अगर (unlikely(rt)) अणु
			dblocks = XFS_DIOSTRAT_SPACE_RES(mp, 0);
			rblocks = resblks;
		पूर्ण अन्यथा अणु
			dblocks = XFS_DIOSTRAT_SPACE_RES(mp, resblks);
			rblocks = 0;
		पूर्ण

		/*
		 * Allocate and setup the transaction.
		 */
		error = xfs_trans_alloc_inode(ip, &M_RES(mp)->tr_ग_लिखो,
				dblocks, rblocks, false, &tp);
		अगर (error)
			अवरोध;

		error = xfs_iext_count_may_overflow(ip, XFS_DATA_FORK,
				XFS_IEXT_ADD_NOSPLIT_CNT);
		अगर (error)
			जाओ error;

		error = xfs_bmapi_ग_लिखो(tp, ip, startoffset_fsb,
					allocatesize_fsb, alloc_type, 0, imapp,
					&nimaps);
		अगर (error)
			जाओ error;

		/*
		 * Complete the transaction
		 */
		error = xfs_trans_commit(tp);
		xfs_iunlock(ip, XFS_ILOCK_EXCL);
		अगर (error)
			अवरोध;

		allocated_fsb = imapp->br_blockcount;

		अगर (nimaps == 0) अणु
			error = -ENOSPC;
			अवरोध;
		पूर्ण

		startoffset_fsb += allocated_fsb;
		allocatesize_fsb -= allocated_fsb;
	पूर्ण

	वापस error;

error:
	xfs_trans_cancel(tp);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;
पूर्ण

अटल पूर्णांक
xfs_unmap_extent(
	काष्ठा xfs_inode	*ip,
	xfs_fileoff_t		startoffset_fsb,
	xfs_filblks_t		len_fsb,
	पूर्णांक			*करोne)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_trans	*tp;
	uपूर्णांक			resblks = XFS_DIOSTRAT_SPACE_RES(mp, 0);
	पूर्णांक			error;

	error = xfs_trans_alloc_inode(ip, &M_RES(mp)->tr_ग_लिखो, resblks, 0,
			false, &tp);
	अगर (error)
		वापस error;

	error = xfs_iext_count_may_overflow(ip, XFS_DATA_FORK,
			XFS_IEXT_PUNCH_HOLE_CNT);
	अगर (error)
		जाओ out_trans_cancel;

	error = xfs_bunmapi(tp, ip, startoffset_fsb, len_fsb, 0, 2, करोne);
	अगर (error)
		जाओ out_trans_cancel;

	error = xfs_trans_commit(tp);
out_unlock:
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;

out_trans_cancel:
	xfs_trans_cancel(tp);
	जाओ out_unlock;
पूर्ण

/* Caller must first रुको क्रम the completion of any pending DIOs अगर required. */
पूर्णांक
xfs_flush_unmap_range(
	काष्ठा xfs_inode	*ip,
	xfs_off_t		offset,
	xfs_off_t		len)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा inode		*inode = VFS_I(ip);
	xfs_off_t		rounding, start, end;
	पूर्णांक			error;

	rounding = max_t(xfs_off_t, 1 << mp->m_sb.sb_blocklog, PAGE_SIZE);
	start = round_करोwn(offset, rounding);
	end = round_up(offset + len, rounding) - 1;

	error = filemap_ग_लिखो_and_रुको_range(inode->i_mapping, start, end);
	अगर (error)
		वापस error;
	truncate_pagecache_range(inode, start, end);
	वापस 0;
पूर्ण

पूर्णांक
xfs_मुक्त_file_space(
	काष्ठा xfs_inode	*ip,
	xfs_off_t		offset,
	xfs_off_t		len)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	xfs_fileoff_t		startoffset_fsb;
	xfs_fileoff_t		enकरोffset_fsb;
	पूर्णांक			करोne = 0, error;

	trace_xfs_मुक्त_file_space(ip);

	error = xfs_qm_dqattach(ip);
	अगर (error)
		वापस error;

	अगर (len <= 0)	/* अगर nothing being मुक्तd */
		वापस 0;

	startoffset_fsb = XFS_B_TO_FSB(mp, offset);
	enकरोffset_fsb = XFS_B_TO_FSBT(mp, offset + len);

	/* We can only मुक्त complete realसमय extents. */
	अगर (XFS_IS_REALTIME_INODE(ip) && mp->m_sb.sb_rextsize > 1) अणु
		startoffset_fsb = roundup_64(startoffset_fsb,
					     mp->m_sb.sb_rextsize);
		enकरोffset_fsb = roundकरोwn_64(enकरोffset_fsb,
					     mp->m_sb.sb_rextsize);
	पूर्ण

	/*
	 * Need to zero the stuff we're not मुक्तing, on disk.
	 */
	अगर (enकरोffset_fsb > startoffset_fsb) अणु
		जबतक (!करोne) अणु
			error = xfs_unmap_extent(ip, startoffset_fsb,
					enकरोffset_fsb - startoffset_fsb, &करोne);
			अगर (error)
				वापस error;
		पूर्ण
	पूर्ण

	/*
	 * Now that we've unmap all full blocks we'll have to zero out any
	 * partial block at the beginning and/or end.  iomap_zero_range is smart
	 * enough to skip any holes, including those we just created, but we
	 * must take care not to zero beyond खातापूर्ण and enlarge i_size.
	 */
	अगर (offset >= XFS_ISIZE(ip))
		वापस 0;
	अगर (offset + len > XFS_ISIZE(ip))
		len = XFS_ISIZE(ip) - offset;
	error = iomap_zero_range(VFS_I(ip), offset, len, शून्य,
			&xfs_buffered_ग_लिखो_iomap_ops);
	अगर (error)
		वापस error;

	/*
	 * If we zeroed right up to खातापूर्ण and खातापूर्ण straddles a page boundary we
	 * must make sure that the post-खातापूर्ण area is also zeroed because the
	 * page could be mmap'd and iomap_zero_range doesn't करो that क्रम us.
	 * Writeback of the eof page will करो this, albeit clumsily.
	 */
	अगर (offset + len >= XFS_ISIZE(ip) && offset_in_page(offset + len) > 0) अणु
		error = filemap_ग_लिखो_and_रुको_range(VFS_I(ip)->i_mapping,
				round_करोwn(offset + len, PAGE_SIZE), Lदीर्घ_उच्च);
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक
xfs_prepare_shअगरt(
	काष्ठा xfs_inode	*ip,
	loff_t			offset)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	पूर्णांक			error;

	/*
	 * Trim eofblocks to aव्योम shअगरting uninitialized post-eof pपुनः_स्मृतिation
	 * पूर्णांकo the accessible region of the file.
	 */
	अगर (xfs_can_मुक्त_eofblocks(ip, true)) अणु
		error = xfs_मुक्त_eofblocks(ip);
		अगर (error)
			वापस error;
	पूर्ण

	/*
	 * Shअगरt operations must stabilize the start block offset boundary aदीर्घ
	 * with the full range of the operation. If we करोn't, a COW ग_लिखोback
	 * completion could race with an insert, front merge with the start
	 * extent (after split) during the shअगरt and corrupt the file. Start
	 * with the block just prior to the start to stabilize the boundary.
	 */
	offset = round_करोwn(offset, 1 << mp->m_sb.sb_blocklog);
	अगर (offset)
		offset -= (1 << mp->m_sb.sb_blocklog);

	/*
	 * Writeback and invalidate cache क्रम the reमुख्यder of the file as we're
	 * about to shअगरt करोwn every extent from offset to खातापूर्ण.
	 */
	error = xfs_flush_unmap_range(ip, offset, XFS_ISIZE(ip));
	अगर (error)
		वापस error;

	/*
	 * Clean out anything hanging around in the cow विभाजन now that
	 * we've flushed all the dirty data out to disk to aव्योम having
	 * CoW extents at the wrong offsets.
	 */
	अगर (xfs_inode_has_cow_data(ip)) अणु
		error = xfs_reflink_cancel_cow_range(ip, offset, शून्यखाताOFF,
				true);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * xfs_collapse_file_space()
 *	This routine मुक्तs disk space and shअगरt extent क्रम the given file.
 *	The first thing we करो is to मुक्त data blocks in the specअगरied range
 *	by calling xfs_मुक्त_file_space(). It would also sync dirty data
 *	and invalidate page cache over the region on which collapse range
 *	is working. And Shअगरt extent records to the left to cover a hole.
 * RETURNS:
 *	0 on success
 *	त्रुटि_सं on error
 *
 */
पूर्णांक
xfs_collapse_file_space(
	काष्ठा xfs_inode	*ip,
	xfs_off_t		offset,
	xfs_off_t		len)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_trans	*tp;
	पूर्णांक			error;
	xfs_fileoff_t		next_fsb = XFS_B_TO_FSB(mp, offset + len);
	xfs_fileoff_t		shअगरt_fsb = XFS_B_TO_FSB(mp, len);
	bool			करोne = false;

	ASSERT(xfs_isilocked(ip, XFS_IOLOCK_EXCL));
	ASSERT(xfs_isilocked(ip, XFS_MMAPLOCK_EXCL));

	trace_xfs_collapse_file_space(ip);

	error = xfs_मुक्त_file_space(ip, offset, len);
	अगर (error)
		वापस error;

	error = xfs_prepare_shअगरt(ip, offset);
	अगर (error)
		वापस error;

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_ग_लिखो, 0, 0, 0, &tp);
	अगर (error)
		वापस error;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, 0);

	जबतक (!करोne) अणु
		error = xfs_bmap_collapse_extents(tp, ip, &next_fsb, shअगरt_fsb,
				&करोne);
		अगर (error)
			जाओ out_trans_cancel;
		अगर (करोne)
			अवरोध;

		/* finish any deferred मुक्तs and roll the transaction */
		error = xfs_defer_finish(&tp);
		अगर (error)
			जाओ out_trans_cancel;
	पूर्ण

	error = xfs_trans_commit(tp);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;

out_trans_cancel:
	xfs_trans_cancel(tp);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;
पूर्ण

/*
 * xfs_insert_file_space()
 *	This routine create hole space by shअगरting extents क्रम the given file.
 *	The first thing we करो is to sync dirty data and invalidate page cache
 *	over the region on which insert range is working. And split an extent
 *	to two extents at given offset by calling xfs_bmap_split_extent.
 *	And shअगरt all extent records which are laying between [offset,
 *	last allocated extent] to the right to reserve hole range.
 * RETURNS:
 *	0 on success
 *	त्रुटि_सं on error
 */
पूर्णांक
xfs_insert_file_space(
	काष्ठा xfs_inode	*ip,
	loff_t			offset,
	loff_t			len)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_trans	*tp;
	पूर्णांक			error;
	xfs_fileoff_t		stop_fsb = XFS_B_TO_FSB(mp, offset);
	xfs_fileoff_t		next_fsb = शून्यFSBLOCK;
	xfs_fileoff_t		shअगरt_fsb = XFS_B_TO_FSB(mp, len);
	bool			करोne = false;

	ASSERT(xfs_isilocked(ip, XFS_IOLOCK_EXCL));
	ASSERT(xfs_isilocked(ip, XFS_MMAPLOCK_EXCL));

	trace_xfs_insert_file_space(ip);

	error = xfs_bmap_can_insert_extents(ip, stop_fsb, shअगरt_fsb);
	अगर (error)
		वापस error;

	error = xfs_prepare_shअगरt(ip, offset);
	अगर (error)
		वापस error;

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_ग_लिखो,
			XFS_DIOSTRAT_SPACE_RES(mp, 0), 0, 0, &tp);
	अगर (error)
		वापस error;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, 0);

	error = xfs_iext_count_may_overflow(ip, XFS_DATA_FORK,
			XFS_IEXT_PUNCH_HOLE_CNT);
	अगर (error)
		जाओ out_trans_cancel;

	/*
	 * The extent shअगरting code works on extent granularity. So, अगर stop_fsb
	 * is not the starting block of extent, we need to split the extent at
	 * stop_fsb.
	 */
	error = xfs_bmap_split_extent(tp, ip, stop_fsb);
	अगर (error)
		जाओ out_trans_cancel;

	करो अणु
		error = xfs_defer_finish(&tp);
		अगर (error)
			जाओ out_trans_cancel;

		error = xfs_bmap_insert_extents(tp, ip, &next_fsb, shअगरt_fsb,
				&करोne, stop_fsb);
		अगर (error)
			जाओ out_trans_cancel;
	पूर्ण जबतक (!करोne);

	error = xfs_trans_commit(tp);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;

out_trans_cancel:
	xfs_trans_cancel(tp);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;
पूर्ण

/*
 * We need to check that the क्रमmat of the data विभाजन in the temporary inode is
 * valid क्रम the target inode beक्रमe करोing the swap. This is not a problem with
 * attr1 because of the fixed विभाजन offset, but attr2 has a dynamically sized
 * data विभाजन depending on the space the attribute विभाजन is taking so we can get
 * invalid क्रमmats on the target inode.
 *
 * E.g. target has space क्रम 7 extents in extent क्रमmat, temp inode only has
 * space क्रम 6.  If we defragment करोwn to 7 extents, then the पंचांगp क्रमmat is a
 * btree, but when swapped it needs to be in extent क्रमmat. Hence we can't just
 * blindly swap data विभाजनs on attr2 fileप्रणालीs.
 *
 * Note that we check the swap in both directions so that we करोn't end up with
 * a corrupt temporary inode, either.
 *
 * Note that fixing the way xfs_fsr sets up the attribute विभाजन in the source
 * inode will prevent this situation from occurring, so all we करो here is
 * reject and log the attempt. basically we are putting the responsibility on
 * userspace to get this right.
 */
अटल पूर्णांक
xfs_swap_extents_check_क्रमmat(
	काष्ठा xfs_inode	*ip,	/* target inode */
	काष्ठा xfs_inode	*tip)	/* पंचांगp inode */
अणु
	काष्ठा xfs_अगरork	*अगरp = &ip->i_df;
	काष्ठा xfs_अगरork	*tअगरp = &tip->i_df;

	/* User/group/project quota ids must match अगर quotas are enक्रमced. */
	अगर (XFS_IS_QUOTA_ON(ip->i_mount) &&
	    (!uid_eq(VFS_I(ip)->i_uid, VFS_I(tip)->i_uid) ||
	     !gid_eq(VFS_I(ip)->i_gid, VFS_I(tip)->i_gid) ||
	     ip->i_projid != tip->i_projid))
		वापस -EINVAL;

	/* Should never get a local क्रमmat */
	अगर (अगरp->अगर_क्रमmat == XFS_DINODE_FMT_LOCAL ||
	    tअगरp->अगर_क्रमmat == XFS_DINODE_FMT_LOCAL)
		वापस -EINVAL;

	/*
	 * अगर the target inode has less extents that then temporary inode then
	 * why did userspace call us?
	 */
	अगर (अगरp->अगर_nextents < tअगरp->अगर_nextents)
		वापस -EINVAL;

	/*
	 * If we have to use the (expensive) rmap swap method, we can
	 * handle any number of extents and any क्रमmat.
	 */
	अगर (xfs_sb_version_hasrmapbt(&ip->i_mount->m_sb))
		वापस 0;

	/*
	 * अगर the target inode is in extent क्रमm and the temp inode is in btree
	 * क्रमm then we will end up with the target inode in the wrong क्रमmat
	 * as we alपढ़ोy know there are less extents in the temp inode.
	 */
	अगर (अगरp->अगर_क्रमmat == XFS_DINODE_FMT_EXTENTS &&
	    tअगरp->अगर_क्रमmat == XFS_DINODE_FMT_BTREE)
		वापस -EINVAL;

	/* Check temp in extent क्रमm to max in target */
	अगर (tअगरp->अगर_क्रमmat == XFS_DINODE_FMT_EXTENTS &&
	    tअगरp->अगर_nextents > XFS_IFORK_MAXEXT(ip, XFS_DATA_FORK))
		वापस -EINVAL;

	/* Check target in extent क्रमm to max in temp */
	अगर (अगरp->अगर_क्रमmat == XFS_DINODE_FMT_EXTENTS &&
	    अगरp->अगर_nextents > XFS_IFORK_MAXEXT(tip, XFS_DATA_FORK))
		वापस -EINVAL;

	/*
	 * If we are in a btree क्रमmat, check that the temp root block will fit
	 * in the target and that it has enough extents to be in btree क्रमmat
	 * in the target.
	 *
	 * Note that we have to be careful to allow btree->extent conversions
	 * (a common defrag हाल) which will occur when the temp inode is in
	 * extent क्रमmat...
	 */
	अगर (tअगरp->अगर_क्रमmat == XFS_DINODE_FMT_BTREE) अणु
		अगर (XFS_IFORK_Q(ip) &&
		    XFS_BMAP_BMDR_SPACE(tअगरp->अगर_broot) > XFS_IFORK_BOFF(ip))
			वापस -EINVAL;
		अगर (tअगरp->अगर_nextents <= XFS_IFORK_MAXEXT(ip, XFS_DATA_FORK))
			वापस -EINVAL;
	पूर्ण

	/* Reciprocal target->temp btree क्रमmat checks */
	अगर (अगरp->अगर_क्रमmat == XFS_DINODE_FMT_BTREE) अणु
		अगर (XFS_IFORK_Q(tip) &&
		    XFS_BMAP_BMDR_SPACE(ip->i_df.अगर_broot) > XFS_IFORK_BOFF(tip))
			वापस -EINVAL;
		अगर (अगरp->अगर_nextents <= XFS_IFORK_MAXEXT(tip, XFS_DATA_FORK))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
xfs_swap_extent_flush(
	काष्ठा xfs_inode	*ip)
अणु
	पूर्णांक	error;

	error = filemap_ग_लिखो_and_रुको(VFS_I(ip)->i_mapping);
	अगर (error)
		वापस error;
	truncate_pagecache_range(VFS_I(ip), 0, -1);

	/* Verअगरy O_सूचीECT क्रम fपंचांगp */
	अगर (VFS_I(ip)->i_mapping->nrpages)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 * Move extents from one file to another, when rmap is enabled.
 */
STATIC पूर्णांक
xfs_swap_extent_rmap(
	काष्ठा xfs_trans		**tpp,
	काष्ठा xfs_inode		*ip,
	काष्ठा xfs_inode		*tip)
अणु
	काष्ठा xfs_trans		*tp = *tpp;
	काष्ठा xfs_bmbt_irec		irec;
	काष्ठा xfs_bmbt_irec		uirec;
	काष्ठा xfs_bmbt_irec		tirec;
	xfs_fileoff_t			offset_fsb;
	xfs_fileoff_t			end_fsb;
	xfs_filblks_t			count_fsb;
	पूर्णांक				error;
	xfs_filblks_t			ilen;
	xfs_filblks_t			rlen;
	पूर्णांक				nimaps;
	uपूर्णांक64_t			tip_flags2;

	/*
	 * If the source file has shared blocks, we must flag the करोnor
	 * file as having shared blocks so that we get the shared-block
	 * rmap functions when we go to fix up the rmaps.  The flags
	 * will be चयन क्रम reals later.
	 */
	tip_flags2 = tip->i_dअगरlags2;
	अगर (ip->i_dअगरlags2 & XFS_DIFLAG2_REFLINK)
		tip->i_dअगरlags2 |= XFS_DIFLAG2_REFLINK;

	offset_fsb = 0;
	end_fsb = XFS_B_TO_FSB(ip->i_mount, i_size_पढ़ो(VFS_I(ip)));
	count_fsb = (xfs_filblks_t)(end_fsb - offset_fsb);

	जबतक (count_fsb) अणु
		/* Read extent from the करोnor file */
		nimaps = 1;
		error = xfs_bmapi_पढ़ो(tip, offset_fsb, count_fsb, &tirec,
				&nimaps, 0);
		अगर (error)
			जाओ out;
		ASSERT(nimaps == 1);
		ASSERT(tirec.br_startblock != DELAYSTARTBLOCK);

		trace_xfs_swap_extent_rmap_remap(tip, &tirec);
		ilen = tirec.br_blockcount;

		/* Unmap the old blocks in the source file. */
		जबतक (tirec.br_blockcount) अणु
			ASSERT(tp->t_firstblock == शून्यFSBLOCK);
			trace_xfs_swap_extent_rmap_remap_piece(tip, &tirec);

			/* Read extent from the source file */
			nimaps = 1;
			error = xfs_bmapi_पढ़ो(ip, tirec.br_startoff,
					tirec.br_blockcount, &irec,
					&nimaps, 0);
			अगर (error)
				जाओ out;
			ASSERT(nimaps == 1);
			ASSERT(tirec.br_startoff == irec.br_startoff);
			trace_xfs_swap_extent_rmap_remap_piece(ip, &irec);

			/* Trim the extent. */
			uirec = tirec;
			uirec.br_blockcount = rlen = min_t(xfs_filblks_t,
					tirec.br_blockcount,
					irec.br_blockcount);
			trace_xfs_swap_extent_rmap_remap_piece(tip, &uirec);

			अगर (xfs_bmap_is_real_extent(&uirec)) अणु
				error = xfs_iext_count_may_overflow(ip,
						XFS_DATA_FORK,
						XFS_IEXT_SWAP_RMAP_CNT);
				अगर (error)
					जाओ out;
			पूर्ण

			अगर (xfs_bmap_is_real_extent(&irec)) अणु
				error = xfs_iext_count_may_overflow(tip,
						XFS_DATA_FORK,
						XFS_IEXT_SWAP_RMAP_CNT);
				अगर (error)
					जाओ out;
			पूर्ण

			/* Remove the mapping from the करोnor file. */
			xfs_bmap_unmap_extent(tp, tip, &uirec);

			/* Remove the mapping from the source file. */
			xfs_bmap_unmap_extent(tp, ip, &irec);

			/* Map the करोnor file's blocks पूर्णांकo the source file. */
			xfs_bmap_map_extent(tp, ip, &uirec);

			/* Map the source file's blocks पूर्णांकo the करोnor file. */
			xfs_bmap_map_extent(tp, tip, &irec);

			error = xfs_defer_finish(tpp);
			tp = *tpp;
			अगर (error)
				जाओ out;

			tirec.br_startoff += rlen;
			अगर (tirec.br_startblock != HOLESTARTBLOCK &&
			    tirec.br_startblock != DELAYSTARTBLOCK)
				tirec.br_startblock += rlen;
			tirec.br_blockcount -= rlen;
		पूर्ण

		/* Roll on... */
		count_fsb -= ilen;
		offset_fsb += ilen;
	पूर्ण

	tip->i_dअगरlags2 = tip_flags2;
	वापस 0;

out:
	trace_xfs_swap_extent_rmap_error(ip, error, _RET_IP_);
	tip->i_dअगरlags2 = tip_flags2;
	वापस error;
पूर्ण

/* Swap the extents of two files by swapping data विभाजनs. */
STATIC पूर्णांक
xfs_swap_extent_विभाजनs(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_inode	*tip,
	पूर्णांक			*src_log_flags,
	पूर्णांक			*target_log_flags)
अणु
	xfs_filblks_t		aविभाजनblks = 0;
	xfs_filblks_t		taविभाजनblks = 0;
	xfs_extnum_t		junk;
	uपूर्णांक64_t		पंचांगp;
	पूर्णांक			error;

	/*
	 * Count the number of extended attribute blocks
	 */
	अगर (XFS_IFORK_Q(ip) && ip->i_afp->अगर_nextents > 0 &&
	    ip->i_afp->अगर_क्रमmat != XFS_DINODE_FMT_LOCAL) अणु
		error = xfs_bmap_count_blocks(tp, ip, XFS_ATTR_FORK, &junk,
				&aविभाजनblks);
		अगर (error)
			वापस error;
	पूर्ण
	अगर (XFS_IFORK_Q(tip) && tip->i_afp->अगर_nextents > 0 &&
	    tip->i_afp->अगर_क्रमmat != XFS_DINODE_FMT_LOCAL) अणु
		error = xfs_bmap_count_blocks(tp, tip, XFS_ATTR_FORK, &junk,
				&taविभाजनblks);
		अगर (error)
			वापस error;
	पूर्ण

	/*
	 * Btree क्रमmat (v3) inodes have the inode number stamped in the bmbt
	 * block headers. We can't start changing the bmbt blocks until the
	 * inode owner change is logged so recovery करोes the right thing in the
	 * event of a crash. Set the owner change log flags now and leave the
	 * bmbt scan as the last step.
	 */
	अगर (xfs_sb_version_has_v3inode(&ip->i_mount->m_sb)) अणु
		अगर (ip->i_df.अगर_क्रमmat == XFS_DINODE_FMT_BTREE)
			(*target_log_flags) |= XFS_ILOG_DOWNER;
		अगर (tip->i_df.अगर_क्रमmat == XFS_DINODE_FMT_BTREE)
			(*src_log_flags) |= XFS_ILOG_DOWNER;
	पूर्ण

	/*
	 * Swap the data विभाजनs of the inodes
	 */
	swap(ip->i_df, tip->i_df);

	/*
	 * Fix the on-disk inode values
	 */
	पंचांगp = (uपूर्णांक64_t)ip->i_nblocks;
	ip->i_nblocks = tip->i_nblocks - taविभाजनblks + aविभाजनblks;
	tip->i_nblocks = पंचांगp + taविभाजनblks - aविभाजनblks;

	/*
	 * The extents in the source inode could still contain speculative
	 * pपुनः_स्मृतिation beyond खातापूर्ण (e.g. the file is खोलो but not modअगरied
	 * जबतक defrag is in progress). In that हाल, we need to copy over the
	 * number of delalloc blocks the data विभाजन in the source inode is
	 * tracking beyond खातापूर्ण so that when the विभाजन is truncated away when the
	 * temporary inode is unlinked we करोn't underrun the i_delayed_blks
	 * counter on that inode.
	 */
	ASSERT(tip->i_delayed_blks == 0);
	tip->i_delayed_blks = ip->i_delayed_blks;
	ip->i_delayed_blks = 0;

	चयन (ip->i_df.अगर_क्रमmat) अणु
	हाल XFS_DINODE_FMT_EXTENTS:
		(*src_log_flags) |= XFS_ILOG_DEXT;
		अवरोध;
	हाल XFS_DINODE_FMT_BTREE:
		ASSERT(!xfs_sb_version_has_v3inode(&ip->i_mount->m_sb) ||
		       (*src_log_flags & XFS_ILOG_DOWNER));
		(*src_log_flags) |= XFS_ILOG_DBROOT;
		अवरोध;
	पूर्ण

	चयन (tip->i_df.अगर_क्रमmat) अणु
	हाल XFS_DINODE_FMT_EXTENTS:
		(*target_log_flags) |= XFS_ILOG_DEXT;
		अवरोध;
	हाल XFS_DINODE_FMT_BTREE:
		(*target_log_flags) |= XFS_ILOG_DBROOT;
		ASSERT(!xfs_sb_version_has_v3inode(&ip->i_mount->m_sb) ||
		       (*target_log_flags & XFS_ILOG_DOWNER));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Fix up the owners of the bmbt blocks to refer to the current inode. The
 * change owner scan attempts to order all modअगरied buffers in the current
 * transaction. In the event of ordered buffer failure, the offending buffer is
 * physically logged as a fallback and the scan वापसs -EAGAIN. We must roll
 * the transaction in this हाल to replenish the fallback log reservation and
 * restart the scan. This process repeats until the scan completes.
 */
अटल पूर्णांक
xfs_swap_change_owner(
	काष्ठा xfs_trans	**tpp,
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_inode	*पंचांगpip)
अणु
	पूर्णांक			error;
	काष्ठा xfs_trans	*tp = *tpp;

	करो अणु
		error = xfs_bmbt_change_owner(tp, ip, XFS_DATA_FORK, ip->i_ino,
					      शून्य);
		/* success or fatal error */
		अगर (error != -EAGAIN)
			अवरोध;

		error = xfs_trans_roll(tpp);
		अगर (error)
			अवरोध;
		tp = *tpp;

		/*
		 * Redirty both inodes so they can relog and keep the log tail
		 * moving क्रमward.
		 */
		xfs_trans_ijoin(tp, ip, 0);
		xfs_trans_ijoin(tp, पंचांगpip, 0);
		xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);
		xfs_trans_log_inode(tp, पंचांगpip, XFS_ILOG_CORE);
	पूर्ण जबतक (true);

	वापस error;
पूर्ण

पूर्णांक
xfs_swap_extents(
	काष्ठा xfs_inode	*ip,	/* target inode */
	काष्ठा xfs_inode	*tip,	/* पंचांगp inode */
	काष्ठा xfs_swapext	*sxp)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_trans	*tp;
	काष्ठा xfs_bstat	*sbp = &sxp->sx_stat;
	पूर्णांक			src_log_flags, target_log_flags;
	पूर्णांक			error = 0;
	पूर्णांक			lock_flags;
	uपूर्णांक64_t		f;
	पूर्णांक			resblks = 0;
	अचिन्हित पूर्णांक		flags = 0;

	/*
	 * Lock the inodes against other IO, page faults and truncate to
	 * begin with.  Then we can ensure the inodes are flushed and have no
	 * page cache safely. Once we have करोne this we can take the ilocks and
	 * करो the rest of the checks.
	 */
	lock_two_nondirectories(VFS_I(ip), VFS_I(tip));
	lock_flags = XFS_MMAPLOCK_EXCL;
	xfs_lock_two_inodes(ip, XFS_MMAPLOCK_EXCL, tip, XFS_MMAPLOCK_EXCL);

	/* Verअगरy that both files have the same क्रमmat */
	अगर ((VFS_I(ip)->i_mode & S_IFMT) != (VFS_I(tip)->i_mode & S_IFMT)) अणु
		error = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	/* Verअगरy both files are either real-समय or non-realसमय */
	अगर (XFS_IS_REALTIME_INODE(ip) != XFS_IS_REALTIME_INODE(tip)) अणु
		error = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	error = xfs_qm_dqattach(ip);
	अगर (error)
		जाओ out_unlock;

	error = xfs_qm_dqattach(tip);
	अगर (error)
		जाओ out_unlock;

	error = xfs_swap_extent_flush(ip);
	अगर (error)
		जाओ out_unlock;
	error = xfs_swap_extent_flush(tip);
	अगर (error)
		जाओ out_unlock;

	अगर (xfs_inode_has_cow_data(tip)) अणु
		error = xfs_reflink_cancel_cow_range(tip, 0, शून्यखाताOFF, true);
		अगर (error)
			जाओ out_unlock;
	पूर्ण

	/*
	 * Extent "swapping" with rmap requires a permanent reservation and
	 * a block reservation because it's really just a remap operation
	 * perक्रमmed with log reकरो items!
	 */
	अगर (xfs_sb_version_hasrmapbt(&mp->m_sb)) अणु
		पूर्णांक		w = XFS_DATA_FORK;
		uपूर्णांक32_t	ipnext = ip->i_df.अगर_nextents;
		uपूर्णांक32_t	tipnext	= tip->i_df.अगर_nextents;

		/*
		 * Conceptually this shouldn't affect the shape of either bmbt,
		 * but since we atomically move extents one by one, we reserve
		 * enough space to rebuild both trees.
		 */
		resblks = XFS_SWAP_RMAP_SPACE_RES(mp, ipnext, w);
		resblks +=  XFS_SWAP_RMAP_SPACE_RES(mp, tipnext, w);

		/*
		 * If either inode straddles a bmapbt block allocation boundary,
		 * the rmapbt algorithm triggers repeated allocs and मुक्तs as
		 * extents are remapped. This can exhaust the block reservation
		 * prematurely and cause shutकरोwn. Return मुक्तd blocks to the
		 * transaction reservation to counter this behavior.
		 */
		flags |= XFS_TRANS_RES_FDBLKS;
	पूर्ण
	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_ग_लिखो, resblks, 0, flags,
				&tp);
	अगर (error)
		जाओ out_unlock;

	/*
	 * Lock and join the inodes to the tansaction so that transaction commit
	 * or cancel will unlock the inodes from this poपूर्णांक onwards.
	 */
	xfs_lock_two_inodes(ip, XFS_ILOCK_EXCL, tip, XFS_ILOCK_EXCL);
	lock_flags |= XFS_ILOCK_EXCL;
	xfs_trans_ijoin(tp, ip, 0);
	xfs_trans_ijoin(tp, tip, 0);


	/* Verअगरy all data are being swapped */
	अगर (sxp->sx_offset != 0 ||
	    sxp->sx_length != ip->i_disk_size ||
	    sxp->sx_length != tip->i_disk_size) अणु
		error = -EFAULT;
		जाओ out_trans_cancel;
	पूर्ण

	trace_xfs_swap_extent_beक्रमe(ip, 0);
	trace_xfs_swap_extent_beक्रमe(tip, 1);

	/* check inode क्रमmats now that data is flushed */
	error = xfs_swap_extents_check_क्रमmat(ip, tip);
	अगर (error) अणु
		xfs_notice(mp,
		    "%s: inode 0x%llx format is incompatible for exchanging.",
				__func__, ip->i_ino);
		जाओ out_trans_cancel;
	पूर्ण

	/*
	 * Compare the current change & modअगरy बार with that
	 * passed in.  If they dअगरfer, we पात this swap.
	 * This is the mechanism used to ensure the calling
	 * process that the file was not changed out from
	 * under it.
	 */
	अगर ((sbp->bs_स_समय.tv_sec != VFS_I(ip)->i_स_समय.tv_sec) ||
	    (sbp->bs_स_समय.tv_nsec != VFS_I(ip)->i_स_समय.tv_nsec) ||
	    (sbp->bs_mसमय.tv_sec != VFS_I(ip)->i_mसमय.tv_sec) ||
	    (sbp->bs_mसमय.tv_nsec != VFS_I(ip)->i_mसमय.tv_nsec)) अणु
		error = -EBUSY;
		जाओ out_trans_cancel;
	पूर्ण

	/*
	 * Note the trickiness in setting the log flags - we set the owner log
	 * flag on the opposite inode (i.e. the inode we are setting the new
	 * owner to be) because once we swap the विभाजनs and log that, log
	 * recovery is going to see the विभाजन as owned by the swapped inode,
	 * not the pre-swapped inodes.
	 */
	src_log_flags = XFS_ILOG_CORE;
	target_log_flags = XFS_ILOG_CORE;

	अगर (xfs_sb_version_hasrmapbt(&mp->m_sb))
		error = xfs_swap_extent_rmap(&tp, ip, tip);
	अन्यथा
		error = xfs_swap_extent_विभाजनs(tp, ip, tip, &src_log_flags,
				&target_log_flags);
	अगर (error)
		जाओ out_trans_cancel;

	/* Do we have to swap reflink flags? */
	अगर ((ip->i_dअगरlags2 & XFS_DIFLAG2_REFLINK) ^
	    (tip->i_dअगरlags2 & XFS_DIFLAG2_REFLINK)) अणु
		f = ip->i_dअगरlags2 & XFS_DIFLAG2_REFLINK;
		ip->i_dअगरlags2 &= ~XFS_DIFLAG2_REFLINK;
		ip->i_dअगरlags2 |= tip->i_dअगरlags2 & XFS_DIFLAG2_REFLINK;
		tip->i_dअगरlags2 &= ~XFS_DIFLAG2_REFLINK;
		tip->i_dअगरlags2 |= f & XFS_DIFLAG2_REFLINK;
	पूर्ण

	/* Swap the cow विभाजनs. */
	अगर (xfs_sb_version_hasreflink(&mp->m_sb)) अणु
		ASSERT(!ip->i_cowfp ||
		       ip->i_cowfp->अगर_क्रमmat == XFS_DINODE_FMT_EXTENTS);
		ASSERT(!tip->i_cowfp ||
		       tip->i_cowfp->अगर_क्रमmat == XFS_DINODE_FMT_EXTENTS);

		swap(ip->i_cowfp, tip->i_cowfp);

		अगर (ip->i_cowfp && ip->i_cowfp->अगर_bytes)
			xfs_inode_set_cowblocks_tag(ip);
		अन्यथा
			xfs_inode_clear_cowblocks_tag(ip);
		अगर (tip->i_cowfp && tip->i_cowfp->अगर_bytes)
			xfs_inode_set_cowblocks_tag(tip);
		अन्यथा
			xfs_inode_clear_cowblocks_tag(tip);
	पूर्ण

	xfs_trans_log_inode(tp, ip,  src_log_flags);
	xfs_trans_log_inode(tp, tip, target_log_flags);

	/*
	 * The extent विभाजनs have been swapped, but crc=1,rmapbt=0 fileप्रणालीs
	 * have inode number owner values in the bmbt blocks that still refer to
	 * the old inode. Scan each bmbt to fix up the owner values with the
	 * inode number of the current inode.
	 */
	अगर (src_log_flags & XFS_ILOG_DOWNER) अणु
		error = xfs_swap_change_owner(&tp, ip, tip);
		अगर (error)
			जाओ out_trans_cancel;
	पूर्ण
	अगर (target_log_flags & XFS_ILOG_DOWNER) अणु
		error = xfs_swap_change_owner(&tp, tip, ip);
		अगर (error)
			जाओ out_trans_cancel;
	पूर्ण

	/*
	 * If this is a synchronous mount, make sure that the
	 * transaction goes to disk beक्रमe वापसing to the user.
	 */
	अगर (mp->m_flags & XFS_MOUNT_WSYNC)
		xfs_trans_set_sync(tp);

	error = xfs_trans_commit(tp);

	trace_xfs_swap_extent_after(ip, 0);
	trace_xfs_swap_extent_after(tip, 1);

out_unlock:
	xfs_iunlock(ip, lock_flags);
	xfs_iunlock(tip, lock_flags);
	unlock_two_nondirectories(VFS_I(ip), VFS_I(tip));
	वापस error;

out_trans_cancel:
	xfs_trans_cancel(tp);
	जाओ out_unlock;
पूर्ण
