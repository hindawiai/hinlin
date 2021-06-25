<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2003,2005 Silicon Graphics, Inc.
 * Copyright (c) 2013 Red Hat, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_dir2.h"
#समावेश "xfs_dir2_priv.h"
#समावेश "xfs_error.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_log.h"

/*
 * Local function prototypes.
 */
अटल व्योम xfs_dir2_block_log_leaf(xfs_trans_t *tp, काष्ठा xfs_buf *bp,
				    पूर्णांक first, पूर्णांक last);
अटल व्योम xfs_dir2_block_log_tail(xfs_trans_t *tp, काष्ठा xfs_buf *bp);
अटल पूर्णांक xfs_dir2_block_lookup_पूर्णांक(xfs_da_args_t *args, काष्ठा xfs_buf **bpp,
				     पूर्णांक *entno);
अटल पूर्णांक xfs_dir2_block_sort(स्थिर व्योम *a, स्थिर व्योम *b);

अटल xfs_dahash_t xfs_dir_hash_करोt, xfs_dir_hash_करोtकरोt;

/*
 * One-समय startup routine called from xfs_init().
 */
व्योम
xfs_dir_startup(व्योम)
अणु
	xfs_dir_hash_करोt = xfs_da_hashname((अचिन्हित अक्षर *)".", 1);
	xfs_dir_hash_करोtकरोt = xfs_da_hashname((अचिन्हित अक्षर *)"..", 2);
पूर्ण

अटल xfs_failaddr_t
xfs_dir3_block_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_dir3_blk_hdr	*hdr3 = bp->b_addr;

	अगर (!xfs_verअगरy_magic(bp, hdr3->magic))
		वापस __this_address;

	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		अगर (!uuid_equal(&hdr3->uuid, &mp->m_sb.sb_meta_uuid))
			वापस __this_address;
		अगर (be64_to_cpu(hdr3->blkno) != bp->b_bn)
			वापस __this_address;
		अगर (!xfs_log_check_lsn(mp, be64_to_cpu(hdr3->lsn)))
			वापस __this_address;
	पूर्ण
	वापस __xfs_dir3_data_check(शून्य, bp);
पूर्ण

अटल व्योम
xfs_dir3_block_पढ़ो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	xfs_failaddr_t		fa;

	अगर (xfs_sb_version_hascrc(&mp->m_sb) &&
	     !xfs_buf_verअगरy_cksum(bp, XFS_सूची3_DATA_CRC_OFF))
		xfs_verअगरier_error(bp, -EFSBADCRC, __this_address);
	अन्यथा अणु
		fa = xfs_dir3_block_verअगरy(bp);
		अगर (fa)
			xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
	पूर्ण
पूर्ण

अटल व्योम
xfs_dir3_block_ग_लिखो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;
	काष्ठा xfs_dir3_blk_hdr	*hdr3 = bp->b_addr;
	xfs_failaddr_t		fa;

	fa = xfs_dir3_block_verअगरy(bp);
	अगर (fa) अणु
		xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
		वापस;
	पूर्ण

	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस;

	अगर (bip)
		hdr3->lsn = cpu_to_be64(bip->bli_item.li_lsn);

	xfs_buf_update_cksum(bp, XFS_सूची3_DATA_CRC_OFF);
पूर्ण

स्थिर काष्ठा xfs_buf_ops xfs_dir3_block_buf_ops = अणु
	.name = "xfs_dir3_block",
	.magic = अणु cpu_to_be32(XFS_सूची2_BLOCK_MAGIC),
		   cpu_to_be32(XFS_सूची3_BLOCK_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_dir3_block_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_dir3_block_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा = xfs_dir3_block_verअगरy,
पूर्ण;

अटल xfs_failaddr_t
xfs_dir3_block_header_check(
	काष्ठा xfs_inode	*dp,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = dp->i_mount;

	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		काष्ठा xfs_dir3_blk_hdr *hdr3 = bp->b_addr;

		अगर (be64_to_cpu(hdr3->owner) != dp->i_ino)
			वापस __this_address;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक
xfs_dir3_block_पढ़ो(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*dp,
	काष्ठा xfs_buf		**bpp)
अणु
	काष्ठा xfs_mount	*mp = dp->i_mount;
	xfs_failaddr_t		fa;
	पूर्णांक			err;

	err = xfs_da_पढ़ो_buf(tp, dp, mp->m_dir_geo->datablk, 0, bpp,
				XFS_DATA_FORK, &xfs_dir3_block_buf_ops);
	अगर (err || !*bpp)
		वापस err;

	/* Check things that we can't करो in the verअगरier. */
	fa = xfs_dir3_block_header_check(dp, *bpp);
	अगर (fa) अणु
		__xfs_buf_mark_corrupt(*bpp, fa);
		xfs_trans_brअन्यथा(tp, *bpp);
		*bpp = शून्य;
		वापस -EFSCORRUPTED;
	पूर्ण

	xfs_trans_buf_set_type(tp, *bpp, XFS_BLFT_सूची_BLOCK_BUF);
	वापस err;
पूर्ण

अटल व्योम
xfs_dir3_block_init(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*bp,
	काष्ठा xfs_inode	*dp)
अणु
	काष्ठा xfs_dir3_blk_hdr *hdr3 = bp->b_addr;

	bp->b_ops = &xfs_dir3_block_buf_ops;
	xfs_trans_buf_set_type(tp, bp, XFS_BLFT_सूची_BLOCK_BUF);

	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		स_रखो(hdr3, 0, माप(*hdr3));
		hdr3->magic = cpu_to_be32(XFS_सूची3_BLOCK_MAGIC);
		hdr3->blkno = cpu_to_be64(bp->b_bn);
		hdr3->owner = cpu_to_be64(dp->i_ino);
		uuid_copy(&hdr3->uuid, &mp->m_sb.sb_meta_uuid);
		वापस;

	पूर्ण
	hdr3->magic = cpu_to_be32(XFS_सूची2_BLOCK_MAGIC);
पूर्ण

अटल व्योम
xfs_dir2_block_need_space(
	काष्ठा xfs_inode		*dp,
	काष्ठा xfs_dir2_data_hdr	*hdr,
	काष्ठा xfs_dir2_block_tail	*btp,
	काष्ठा xfs_dir2_leaf_entry	*blp,
	__be16				**tagpp,
	काष्ठा xfs_dir2_data_unused	**dupp,
	काष्ठा xfs_dir2_data_unused	**enddupp,
	पूर्णांक				*compact,
	पूर्णांक				len)
अणु
	काष्ठा xfs_dir2_data_मुक्त	*bf;
	__be16				*tagp = शून्य;
	काष्ठा xfs_dir2_data_unused	*dup = शून्य;
	काष्ठा xfs_dir2_data_unused	*enddup = शून्य;

	*compact = 0;
	bf = xfs_dir2_data_bestमुक्त_p(dp->i_mount, hdr);

	/*
	 * If there are stale entries we'll use one क्रम the leaf.
	 */
	अगर (btp->stale) अणु
		अगर (be16_to_cpu(bf[0].length) >= len) अणु
			/*
			 * The biggest entry enough to aव्योम compaction.
			 */
			dup = (xfs_dir2_data_unused_t *)
			      ((अक्षर *)hdr + be16_to_cpu(bf[0].offset));
			जाओ out;
		पूर्ण

		/*
		 * Will need to compact to make this work.
		 * Tag just beक्रमe the first leaf entry.
		 */
		*compact = 1;
		tagp = (__be16 *)blp - 1;

		/* Data object just beक्रमe the first leaf entry.  */
		dup = (xfs_dir2_data_unused_t *)((अक्षर *)hdr + be16_to_cpu(*tagp));

		/*
		 * If it's not मुक्त then the data will go where the
		 * leaf data starts now, अगर it works at all.
		 */
		अगर (be16_to_cpu(dup->मुक्तtag) == XFS_सूची2_DATA_FREE_TAG) अणु
			अगर (be16_to_cpu(dup->length) + (be32_to_cpu(btp->stale) - 1) *
			    (uपूर्णांक)माप(*blp) < len)
				dup = शून्य;
		पूर्ण अन्यथा अगर ((be32_to_cpu(btp->stale) - 1) * (uपूर्णांक)माप(*blp) < len)
			dup = शून्य;
		अन्यथा
			dup = (xfs_dir2_data_unused_t *)blp;
		जाओ out;
	पूर्ण

	/*
	 * no stale entries, so just use मुक्त space.
	 * Tag just beक्रमe the first leaf entry.
	 */
	tagp = (__be16 *)blp - 1;

	/* Data object just beक्रमe the first leaf entry.  */
	enddup = (xfs_dir2_data_unused_t *)((अक्षर *)hdr + be16_to_cpu(*tagp));

	/*
	 * If it's not free then can't करो this add without cleaning up:
	 * the space beक्रमe the first leaf entry needs to be मुक्त so it
	 * can be expanded to hold the poपूर्णांकer to the new entry.
	 */
	अगर (be16_to_cpu(enddup->मुक्तtag) == XFS_सूची2_DATA_FREE_TAG) अणु
		/*
		 * Check out the biggest मुक्तspace and see अगर it's the same one.
		 */
		dup = (xfs_dir2_data_unused_t *)
		      ((अक्षर *)hdr + be16_to_cpu(bf[0].offset));
		अगर (dup != enddup) अणु
			/*
			 * Not the same मुक्त entry, just check its length.
			 */
			अगर (be16_to_cpu(dup->length) < len)
				dup = शून्य;
			जाओ out;
		पूर्ण

		/*
		 * It is the biggest मुक्तspace, can it hold the leaf too?
		 */
		अगर (be16_to_cpu(dup->length) < len + (uपूर्णांक)माप(*blp)) अणु
			/*
			 * Yes, use the second-largest entry instead अगर it works.
			 */
			अगर (be16_to_cpu(bf[1].length) >= len)
				dup = (xfs_dir2_data_unused_t *)
				      ((अक्षर *)hdr + be16_to_cpu(bf[1].offset));
			अन्यथा
				dup = शून्य;
		पूर्ण
	पूर्ण
out:
	*tagpp = tagp;
	*dupp = dup;
	*enddupp = enddup;
पूर्ण

/*
 * compact the leaf entries.
 * Leave the highest-numbered stale entry stale.
 * XXX should be the one बंदst to mid but mid is not yet computed.
 */
अटल व्योम
xfs_dir2_block_compact(
	काष्ठा xfs_da_args		*args,
	काष्ठा xfs_buf			*bp,
	काष्ठा xfs_dir2_data_hdr	*hdr,
	काष्ठा xfs_dir2_block_tail	*btp,
	काष्ठा xfs_dir2_leaf_entry	*blp,
	पूर्णांक				*needlog,
	पूर्णांक				*lfloghigh,
	पूर्णांक				*lfloglow)
अणु
	पूर्णांक			fromidx;	/* source leaf index */
	पूर्णांक			toidx;		/* target leaf index */
	पूर्णांक			needscan = 0;
	पूर्णांक			highstale;	/* high stale index */

	fromidx = toidx = be32_to_cpu(btp->count) - 1;
	highstale = *lfloghigh = -1;
	क्रम (; fromidx >= 0; fromidx--) अणु
		अगर (blp[fromidx].address == cpu_to_be32(XFS_सूची2_शून्य_DATAPTR)) अणु
			अगर (highstale == -1)
				highstale = toidx;
			अन्यथा अणु
				अगर (*lfloghigh == -1)
					*lfloghigh = toidx;
				जारी;
			पूर्ण
		पूर्ण
		अगर (fromidx < toidx)
			blp[toidx] = blp[fromidx];
		toidx--;
	पूर्ण
	*lfloglow = toidx + 1 - (be32_to_cpu(btp->stale) - 1);
	*lfloghigh -= be32_to_cpu(btp->stale) - 1;
	be32_add_cpu(&btp->count, -(be32_to_cpu(btp->stale) - 1));
	xfs_dir2_data_make_मुक्त(args, bp,
		(xfs_dir2_data_aoff_t)((अक्षर *)blp - (अक्षर *)hdr),
		(xfs_dir2_data_aoff_t)((be32_to_cpu(btp->stale) - 1) * माप(*blp)),
		needlog, &needscan);
	btp->stale = cpu_to_be32(1);
	/*
	 * If we now need to rebuild the bestमुक्त map, करो so.
	 * This needs to happen beक्रमe the next call to use_मुक्त.
	 */
	अगर (needscan)
		xfs_dir2_data_मुक्तscan(args->dp->i_mount, hdr, needlog);
पूर्ण

/*
 * Add an entry to a block directory.
 */
पूर्णांक						/* error */
xfs_dir2_block_addname(
	xfs_da_args_t		*args)		/* directory op arguments */
अणु
	xfs_dir2_data_hdr_t	*hdr;		/* block header */
	xfs_dir2_leaf_entry_t	*blp;		/* block leaf entries */
	काष्ठा xfs_buf		*bp;		/* buffer क्रम block */
	xfs_dir2_block_tail_t	*btp;		/* block tail */
	पूर्णांक			compact;	/* need to compact leaf ents */
	xfs_dir2_data_entry_t	*dep;		/* block data entry */
	xfs_inode_t		*dp;		/* directory inode */
	xfs_dir2_data_unused_t	*dup;		/* block unused entry */
	पूर्णांक			error;		/* error वापस value */
	xfs_dir2_data_unused_t	*enddup=शून्य;	/* unused at end of data */
	xfs_dahash_t		hash;		/* hash value of found entry */
	पूर्णांक			high;		/* high index क्रम binary srch */
	पूर्णांक			highstale;	/* high stale index */
	पूर्णांक			lfloghigh=0;	/* last final leaf to log */
	पूर्णांक			lfloglow=0;	/* first final leaf to log */
	पूर्णांक			len;		/* length of the new entry */
	पूर्णांक			low;		/* low index क्रम binary srch */
	पूर्णांक			lowstale;	/* low stale index */
	पूर्णांक			mid=0;		/* midpoपूर्णांक क्रम binary srch */
	पूर्णांक			needlog;	/* need to log header */
	पूर्णांक			needscan;	/* need to rescan मुक्तspace */
	__be16			*tagp;		/* poपूर्णांकer to tag value */
	xfs_trans_t		*tp;		/* transaction काष्ठाure */

	trace_xfs_dir2_block_addname(args);

	dp = args->dp;
	tp = args->trans;

	/* Read the (one and only) directory block पूर्णांकo bp. */
	error = xfs_dir3_block_पढ़ो(tp, dp, &bp);
	अगर (error)
		वापस error;

	len = xfs_dir2_data_entsize(dp->i_mount, args->namelen);

	/*
	 * Set up poपूर्णांकers to parts of the block.
	 */
	hdr = bp->b_addr;
	btp = xfs_dir2_block_tail_p(args->geo, hdr);
	blp = xfs_dir2_block_leaf_p(btp);

	/*
	 * Find out अगर we can reuse stale entries or whether we need extra
	 * space क्रम entry and new leaf.
	 */
	xfs_dir2_block_need_space(dp, hdr, btp, blp, &tagp, &dup,
				  &enddup, &compact, len);

	/*
	 * Done everything we need क्रम a space check now.
	 */
	अगर (args->op_flags & XFS_DA_OP_JUSTCHECK) अणु
		xfs_trans_brअन्यथा(tp, bp);
		अगर (!dup)
			वापस -ENOSPC;
		वापस 0;
	पूर्ण

	/*
	 * If we करोn't have space क्रम the new entry & leaf ...
	 */
	अगर (!dup) अणु
		/* Don't have a space reservation: वापस no-space.  */
		अगर (args->total == 0)
			वापस -ENOSPC;
		/*
		 * Convert to the next larger क्रमmat.
		 * Then add the new entry in that क्रमmat.
		 */
		error = xfs_dir2_block_to_leaf(args, bp);
		अगर (error)
			वापस error;
		वापस xfs_dir2_leaf_addname(args);
	पूर्ण

	needlog = needscan = 0;

	/*
	 * If need to compact the leaf entries, करो it now.
	 */
	अगर (compact) अणु
		xfs_dir2_block_compact(args, bp, hdr, btp, blp, &needlog,
				      &lfloghigh, &lfloglow);
		/* recalculate blp post-compaction */
		blp = xfs_dir2_block_leaf_p(btp);
	पूर्ण अन्यथा अगर (btp->stale) अणु
		/*
		 * Set leaf logging boundaries to impossible state.
		 * For the no-stale हाल they're set explicitly.
		 */
		lfloglow = be32_to_cpu(btp->count);
		lfloghigh = -1;
	पूर्ण

	/*
	 * Find the slot that's first lower than our hash value, -1 अगर none.
	 */
	क्रम (low = 0, high = be32_to_cpu(btp->count) - 1; low <= high; ) अणु
		mid = (low + high) >> 1;
		अगर ((hash = be32_to_cpu(blp[mid].hashval)) == args->hashval)
			अवरोध;
		अगर (hash < args->hashval)
			low = mid + 1;
		अन्यथा
			high = mid - 1;
	पूर्ण
	जबतक (mid >= 0 && be32_to_cpu(blp[mid].hashval) >= args->hashval) अणु
		mid--;
	पूर्ण
	/*
	 * No stale entries, will use enddup space to hold new leaf.
	 */
	अगर (!btp->stale) अणु
		xfs_dir2_data_aoff_t	aoff;

		/*
		 * Mark the space needed क्रम the new leaf entry, now in use.
		 */
		aoff = (xfs_dir2_data_aoff_t)((अक्षर *)enddup - (अक्षर *)hdr +
				be16_to_cpu(enddup->length) - माप(*blp));
		error = xfs_dir2_data_use_मुक्त(args, bp, enddup, aoff,
				(xfs_dir2_data_aoff_t)माप(*blp), &needlog,
				&needscan);
		अगर (error)
			वापस error;

		/*
		 * Update the tail (entry count).
		 */
		be32_add_cpu(&btp->count, 1);
		/*
		 * If we now need to rebuild the bestमुक्त map, करो so.
		 * This needs to happen beक्रमe the next call to use_मुक्त.
		 */
		अगर (needscan) अणु
			xfs_dir2_data_मुक्तscan(dp->i_mount, hdr, &needlog);
			needscan = 0;
		पूर्ण
		/*
		 * Adjust poपूर्णांकer to the first leaf entry, we're about to move
		 * the table up one to खोलो up space क्रम the new leaf entry.
		 * Then adjust our index to match.
		 */
		blp--;
		mid++;
		अगर (mid)
			स_हटाओ(blp, &blp[1], mid * माप(*blp));
		lfloglow = 0;
		lfloghigh = mid;
	पूर्ण
	/*
	 * Use a stale leaf क्रम our new entry.
	 */
	अन्यथा अणु
		क्रम (lowstale = mid;
		     lowstale >= 0 &&
			blp[lowstale].address !=
			cpu_to_be32(XFS_सूची2_शून्य_DATAPTR);
		     lowstale--)
			जारी;
		क्रम (highstale = mid + 1;
		     highstale < be32_to_cpu(btp->count) &&
			blp[highstale].address !=
			cpu_to_be32(XFS_सूची2_शून्य_DATAPTR) &&
			(lowstale < 0 || mid - lowstale > highstale - mid);
		     highstale++)
			जारी;
		/*
		 * Move entries toward the low-numbered stale entry.
		 */
		अगर (lowstale >= 0 &&
		    (highstale == be32_to_cpu(btp->count) ||
		     mid - lowstale <= highstale - mid)) अणु
			अगर (mid - lowstale)
				स_हटाओ(&blp[lowstale], &blp[lowstale + 1],
					(mid - lowstale) * माप(*blp));
			lfloglow = min(lowstale, lfloglow);
			lfloghigh = max(mid, lfloghigh);
		पूर्ण
		/*
		 * Move entries toward the high-numbered stale entry.
		 */
		अन्यथा अणु
			ASSERT(highstale < be32_to_cpu(btp->count));
			mid++;
			अगर (highstale - mid)
				स_हटाओ(&blp[mid + 1], &blp[mid],
					(highstale - mid) * माप(*blp));
			lfloglow = min(mid, lfloglow);
			lfloghigh = max(highstale, lfloghigh);
		पूर्ण
		be32_add_cpu(&btp->stale, -1);
	पूर्ण
	/*
	 * Poपूर्णांक to the new data entry.
	 */
	dep = (xfs_dir2_data_entry_t *)dup;
	/*
	 * Fill in the leaf entry.
	 */
	blp[mid].hashval = cpu_to_be32(args->hashval);
	blp[mid].address = cpu_to_be32(xfs_dir2_byte_to_dataptr(
				(अक्षर *)dep - (अक्षर *)hdr));
	xfs_dir2_block_log_leaf(tp, bp, lfloglow, lfloghigh);
	/*
	 * Mark space क्रम the data entry used.
	 */
	error = xfs_dir2_data_use_मुक्त(args, bp, dup,
			(xfs_dir2_data_aoff_t)((अक्षर *)dup - (अक्षर *)hdr),
			(xfs_dir2_data_aoff_t)len, &needlog, &needscan);
	अगर (error)
		वापस error;
	/*
	 * Create the new data entry.
	 */
	dep->inumber = cpu_to_be64(args->inumber);
	dep->namelen = args->namelen;
	स_नकल(dep->name, args->name, args->namelen);
	xfs_dir2_data_put_ftype(dp->i_mount, dep, args->filetype);
	tagp = xfs_dir2_data_entry_tag_p(dp->i_mount, dep);
	*tagp = cpu_to_be16((अक्षर *)dep - (अक्षर *)hdr);
	/*
	 * Clean up the bestमुक्त array and log the header, tail, and entry.
	 */
	अगर (needscan)
		xfs_dir2_data_मुक्तscan(dp->i_mount, hdr, &needlog);
	अगर (needlog)
		xfs_dir2_data_log_header(args, bp);
	xfs_dir2_block_log_tail(tp, bp);
	xfs_dir2_data_log_entry(args, bp, dep);
	xfs_dir3_data_check(dp, bp);
	वापस 0;
पूर्ण

/*
 * Log leaf entries from the block.
 */
अटल व्योम
xfs_dir2_block_log_leaf(
	xfs_trans_t		*tp,		/* transaction काष्ठाure */
	काष्ठा xfs_buf		*bp,		/* block buffer */
	पूर्णांक			first,		/* index of first logged leaf */
	पूर्णांक			last)		/* index of last logged leaf */
अणु
	xfs_dir2_data_hdr_t	*hdr = bp->b_addr;
	xfs_dir2_leaf_entry_t	*blp;
	xfs_dir2_block_tail_t	*btp;

	btp = xfs_dir2_block_tail_p(tp->t_mountp->m_dir_geo, hdr);
	blp = xfs_dir2_block_leaf_p(btp);
	xfs_trans_log_buf(tp, bp, (uपूर्णांक)((अक्षर *)&blp[first] - (अक्षर *)hdr),
		(uपूर्णांक)((अक्षर *)&blp[last + 1] - (अक्षर *)hdr - 1));
पूर्ण

/*
 * Log the block tail.
 */
अटल व्योम
xfs_dir2_block_log_tail(
	xfs_trans_t		*tp,		/* transaction काष्ठाure */
	काष्ठा xfs_buf		*bp)		/* block buffer */
अणु
	xfs_dir2_data_hdr_t	*hdr = bp->b_addr;
	xfs_dir2_block_tail_t	*btp;

	btp = xfs_dir2_block_tail_p(tp->t_mountp->m_dir_geo, hdr);
	xfs_trans_log_buf(tp, bp, (uपूर्णांक)((अक्षर *)btp - (अक्षर *)hdr),
		(uपूर्णांक)((अक्षर *)(btp + 1) - (अक्षर *)hdr - 1));
पूर्ण

/*
 * Look up an entry in the block.  This is the बाह्यal routine,
 * xfs_dir2_block_lookup_पूर्णांक करोes the real work.
 */
पूर्णांक						/* error */
xfs_dir2_block_lookup(
	xfs_da_args_t		*args)		/* dir lookup arguments */
अणु
	xfs_dir2_data_hdr_t	*hdr;		/* block header */
	xfs_dir2_leaf_entry_t	*blp;		/* block leaf entries */
	काष्ठा xfs_buf		*bp;		/* block buffer */
	xfs_dir2_block_tail_t	*btp;		/* block tail */
	xfs_dir2_data_entry_t	*dep;		/* block data entry */
	xfs_inode_t		*dp;		/* incore inode */
	पूर्णांक			ent;		/* entry index */
	पूर्णांक			error;		/* error वापस value */

	trace_xfs_dir2_block_lookup(args);

	/*
	 * Get the buffer, look up the entry.
	 * If not found (ENOENT) then वापस, have no buffer.
	 */
	अगर ((error = xfs_dir2_block_lookup_पूर्णांक(args, &bp, &ent)))
		वापस error;
	dp = args->dp;
	hdr = bp->b_addr;
	xfs_dir3_data_check(dp, bp);
	btp = xfs_dir2_block_tail_p(args->geo, hdr);
	blp = xfs_dir2_block_leaf_p(btp);
	/*
	 * Get the offset from the leaf entry, to poपूर्णांक to the data.
	 */
	dep = (xfs_dir2_data_entry_t *)((अक्षर *)hdr +
			xfs_dir2_dataptr_to_off(args->geo,
						be32_to_cpu(blp[ent].address)));
	/*
	 * Fill in inode number, CI name अगर appropriate, release the block.
	 */
	args->inumber = be64_to_cpu(dep->inumber);
	args->filetype = xfs_dir2_data_get_ftype(dp->i_mount, dep);
	error = xfs_dir_cilookup_result(args, dep->name, dep->namelen);
	xfs_trans_brअन्यथा(args->trans, bp);
	वापस error;
पूर्ण

/*
 * Internal block lookup routine.
 */
अटल पूर्णांक					/* error */
xfs_dir2_block_lookup_पूर्णांक(
	xfs_da_args_t		*args,		/* dir lookup arguments */
	काष्ठा xfs_buf		**bpp,		/* वापसed block buffer */
	पूर्णांक			*entno)		/* वापसed entry number */
अणु
	xfs_dir2_dataptr_t	addr;		/* data entry address */
	xfs_dir2_data_hdr_t	*hdr;		/* block header */
	xfs_dir2_leaf_entry_t	*blp;		/* block leaf entries */
	काष्ठा xfs_buf		*bp;		/* block buffer */
	xfs_dir2_block_tail_t	*btp;		/* block tail */
	xfs_dir2_data_entry_t	*dep;		/* block data entry */
	xfs_inode_t		*dp;		/* incore inode */
	पूर्णांक			error;		/* error वापस value */
	xfs_dahash_t		hash;		/* found hash value */
	पूर्णांक			high;		/* binary search high index */
	पूर्णांक			low;		/* binary search low index */
	पूर्णांक			mid;		/* binary search current idx */
	xfs_trans_t		*tp;		/* transaction poपूर्णांकer */
	क्रमागत xfs_dacmp		cmp;		/* comparison result */

	dp = args->dp;
	tp = args->trans;

	error = xfs_dir3_block_पढ़ो(tp, dp, &bp);
	अगर (error)
		वापस error;

	hdr = bp->b_addr;
	xfs_dir3_data_check(dp, bp);
	btp = xfs_dir2_block_tail_p(args->geo, hdr);
	blp = xfs_dir2_block_leaf_p(btp);
	/*
	 * Loop करोing a binary search क्रम our hash value.
	 * Find our entry, ENOENT अगर it's not there.
	 */
	क्रम (low = 0, high = be32_to_cpu(btp->count) - 1; ; ) अणु
		ASSERT(low <= high);
		mid = (low + high) >> 1;
		अगर ((hash = be32_to_cpu(blp[mid].hashval)) == args->hashval)
			अवरोध;
		अगर (hash < args->hashval)
			low = mid + 1;
		अन्यथा
			high = mid - 1;
		अगर (low > high) अणु
			ASSERT(args->op_flags & XFS_DA_OP_OKNOENT);
			xfs_trans_brअन्यथा(tp, bp);
			वापस -ENOENT;
		पूर्ण
	पूर्ण
	/*
	 * Back up to the first one with the right hash value.
	 */
	जबतक (mid > 0 && be32_to_cpu(blp[mid - 1].hashval) == args->hashval) अणु
		mid--;
	पूर्ण
	/*
	 * Now loop क्रमward through all the entries with the
	 * right hash value looking क्रम our name.
	 */
	करो अणु
		अगर ((addr = be32_to_cpu(blp[mid].address)) == XFS_सूची2_शून्य_DATAPTR)
			जारी;
		/*
		 * Get poपूर्णांकer to the entry from the leaf.
		 */
		dep = (xfs_dir2_data_entry_t *)
			((अक्षर *)hdr + xfs_dir2_dataptr_to_off(args->geo, addr));
		/*
		 * Compare name and अगर it's an exact match, वापस the index
		 * and buffer. If it's the first हाल-insensitive match, store
		 * the index and buffer and जारी looking क्रम an exact match.
		 */
		cmp = xfs_dir2_compname(args, dep->name, dep->namelen);
		अगर (cmp != XFS_CMP_DIFFERENT && cmp != args->cmpresult) अणु
			args->cmpresult = cmp;
			*bpp = bp;
			*entno = mid;
			अगर (cmp == XFS_CMP_EXACT)
				वापस 0;
		पूर्ण
	पूर्ण जबतक (++mid < be32_to_cpu(btp->count) &&
			be32_to_cpu(blp[mid].hashval) == hash);

	ASSERT(args->op_flags & XFS_DA_OP_OKNOENT);
	/*
	 * Here, we can only be करोing a lookup (not a नाम or replace).
	 * If a हाल-insensitive match was found earlier, वापस success.
	 */
	अगर (args->cmpresult == XFS_CMP_CASE)
		वापस 0;
	/*
	 * No match, release the buffer and वापस ENOENT.
	 */
	xfs_trans_brअन्यथा(tp, bp);
	वापस -ENOENT;
पूर्ण

/*
 * Remove an entry from a block क्रमmat directory.
 * If that makes the block small enough to fit in लघुक्रमm, transक्रमm it.
 */
पूर्णांक						/* error */
xfs_dir2_block_हटाओname(
	xfs_da_args_t		*args)		/* directory operation args */
अणु
	xfs_dir2_data_hdr_t	*hdr;		/* block header */
	xfs_dir2_leaf_entry_t	*blp;		/* block leaf poपूर्णांकer */
	काष्ठा xfs_buf		*bp;		/* block buffer */
	xfs_dir2_block_tail_t	*btp;		/* block tail */
	xfs_dir2_data_entry_t	*dep;		/* block data entry */
	xfs_inode_t		*dp;		/* incore inode */
	पूर्णांक			ent;		/* block leaf entry index */
	पूर्णांक			error;		/* error वापस value */
	पूर्णांक			needlog;	/* need to log block header */
	पूर्णांक			needscan;	/* need to fixup bestमुक्त */
	xfs_dir2_sf_hdr_t	sfh;		/* लघुक्रमm header */
	पूर्णांक			size;		/* लघुक्रमm size */
	xfs_trans_t		*tp;		/* transaction poपूर्णांकer */

	trace_xfs_dir2_block_हटाओname(args);

	/*
	 * Look up the entry in the block.  Gets the buffer and entry index.
	 * It will always be there, the vnodeops level करोes a lookup first.
	 */
	अगर ((error = xfs_dir2_block_lookup_पूर्णांक(args, &bp, &ent))) अणु
		वापस error;
	पूर्ण
	dp = args->dp;
	tp = args->trans;
	hdr = bp->b_addr;
	btp = xfs_dir2_block_tail_p(args->geo, hdr);
	blp = xfs_dir2_block_leaf_p(btp);
	/*
	 * Poपूर्णांक to the data entry using the leaf entry.
	 */
	dep = (xfs_dir2_data_entry_t *)((अक्षर *)hdr +
			xfs_dir2_dataptr_to_off(args->geo,
						be32_to_cpu(blp[ent].address)));
	/*
	 * Mark the data entry's space मुक्त.
	 */
	needlog = needscan = 0;
	xfs_dir2_data_make_मुक्त(args, bp,
		(xfs_dir2_data_aoff_t)((अक्षर *)dep - (अक्षर *)hdr),
		xfs_dir2_data_entsize(dp->i_mount, dep->namelen), &needlog,
		&needscan);
	/*
	 * Fix up the block tail.
	 */
	be32_add_cpu(&btp->stale, 1);
	xfs_dir2_block_log_tail(tp, bp);
	/*
	 * Remove the leaf entry by marking it stale.
	 */
	blp[ent].address = cpu_to_be32(XFS_सूची2_शून्य_DATAPTR);
	xfs_dir2_block_log_leaf(tp, bp, ent, ent);
	/*
	 * Fix up bestमुक्त, log the header अगर necessary.
	 */
	अगर (needscan)
		xfs_dir2_data_मुक्तscan(dp->i_mount, hdr, &needlog);
	अगर (needlog)
		xfs_dir2_data_log_header(args, bp);
	xfs_dir3_data_check(dp, bp);
	/*
	 * See अगर the size as a लघुक्रमm is good enough.
	 */
	size = xfs_dir2_block_sfsize(dp, hdr, &sfh);
	अगर (size > XFS_IFORK_DSIZE(dp))
		वापस 0;

	/*
	 * If it works, करो the conversion.
	 */
	वापस xfs_dir2_block_to_sf(args, bp, size, &sfh);
पूर्ण

/*
 * Replace an entry in a V2 block directory.
 * Change the inode number to the new value.
 */
पूर्णांक						/* error */
xfs_dir2_block_replace(
	xfs_da_args_t		*args)		/* directory operation args */
अणु
	xfs_dir2_data_hdr_t	*hdr;		/* block header */
	xfs_dir2_leaf_entry_t	*blp;		/* block leaf entries */
	काष्ठा xfs_buf		*bp;		/* block buffer */
	xfs_dir2_block_tail_t	*btp;		/* block tail */
	xfs_dir2_data_entry_t	*dep;		/* block data entry */
	xfs_inode_t		*dp;		/* incore inode */
	पूर्णांक			ent;		/* leaf entry index */
	पूर्णांक			error;		/* error वापस value */

	trace_xfs_dir2_block_replace(args);

	/*
	 * Lookup the entry in the directory.  Get buffer and entry index.
	 * This will always succeed since the caller has alपढ़ोy करोne a lookup.
	 */
	अगर ((error = xfs_dir2_block_lookup_पूर्णांक(args, &bp, &ent))) अणु
		वापस error;
	पूर्ण
	dp = args->dp;
	hdr = bp->b_addr;
	btp = xfs_dir2_block_tail_p(args->geo, hdr);
	blp = xfs_dir2_block_leaf_p(btp);
	/*
	 * Poपूर्णांक to the data entry we need to change.
	 */
	dep = (xfs_dir2_data_entry_t *)((अक्षर *)hdr +
			xfs_dir2_dataptr_to_off(args->geo,
						be32_to_cpu(blp[ent].address)));
	ASSERT(be64_to_cpu(dep->inumber) != args->inumber);
	/*
	 * Change the inode number to the new value.
	 */
	dep->inumber = cpu_to_be64(args->inumber);
	xfs_dir2_data_put_ftype(dp->i_mount, dep, args->filetype);
	xfs_dir2_data_log_entry(args, bp, dep);
	xfs_dir3_data_check(dp, bp);
	वापस 0;
पूर्ण

/*
 * Qsort comparison routine क्रम the block leaf entries.
 */
अटल पूर्णांक					/* sort order */
xfs_dir2_block_sort(
	स्थिर व्योम			*a,	/* first leaf entry */
	स्थिर व्योम			*b)	/* second leaf entry */
अणु
	स्थिर xfs_dir2_leaf_entry_t	*la;	/* first leaf entry */
	स्थिर xfs_dir2_leaf_entry_t	*lb;	/* second leaf entry */

	la = a;
	lb = b;
	वापस be32_to_cpu(la->hashval) < be32_to_cpu(lb->hashval) ? -1 :
		(be32_to_cpu(la->hashval) > be32_to_cpu(lb->hashval) ? 1 : 0);
पूर्ण

/*
 * Convert a V2 leaf directory to a V2 block directory अगर possible.
 */
पूर्णांक						/* error */
xfs_dir2_leaf_to_block(
	xfs_da_args_t		*args,		/* operation arguments */
	काष्ठा xfs_buf		*lbp,		/* leaf buffer */
	काष्ठा xfs_buf		*dbp)		/* data buffer */
अणु
	__be16			*bestsp;	/* leaf bests table */
	xfs_dir2_data_hdr_t	*hdr;		/* block header */
	xfs_dir2_block_tail_t	*btp;		/* block tail */
	xfs_inode_t		*dp;		/* incore directory inode */
	xfs_dir2_data_unused_t	*dup;		/* unused data entry */
	पूर्णांक			error;		/* error वापस value */
	पूर्णांक			from;		/* leaf from index */
	xfs_dir2_leaf_t		*leaf;		/* leaf काष्ठाure */
	xfs_dir2_leaf_entry_t	*lep;		/* leaf entry */
	xfs_dir2_leaf_tail_t	*ltp;		/* leaf tail काष्ठाure */
	xfs_mount_t		*mp;		/* file प्रणाली mount poपूर्णांक */
	पूर्णांक			needlog;	/* need to log data header */
	पूर्णांक			needscan;	/* need to scan क्रम bestमुक्त */
	xfs_dir2_sf_hdr_t	sfh;		/* लघुक्रमm header */
	पूर्णांक			size;		/* bytes used */
	__be16			*tagp;		/* end of entry (tag) */
	पूर्णांक			to;		/* block/leaf to index */
	xfs_trans_t		*tp;		/* transaction poपूर्णांकer */
	काष्ठा xfs_dir3_icleaf_hdr leafhdr;

	trace_xfs_dir2_leaf_to_block(args);

	dp = args->dp;
	tp = args->trans;
	mp = dp->i_mount;
	leaf = lbp->b_addr;
	xfs_dir2_leaf_hdr_from_disk(mp, &leafhdr, leaf);
	ltp = xfs_dir2_leaf_tail_p(args->geo, leaf);

	ASSERT(leafhdr.magic == XFS_सूची2_LEAF1_MAGIC ||
	       leafhdr.magic == XFS_सूची3_LEAF1_MAGIC);
	/*
	 * If there are data blocks other than the first one, take this
	 * opportunity to हटाओ trailing empty data blocks that may have
	 * been left behind during no-space-reservation operations.
	 * These will show up in the leaf bests table.
	 */
	जबतक (dp->i_disk_size > args->geo->blksize) अणु
		पूर्णांक hdrsz;

		hdrsz = args->geo->data_entry_offset;
		bestsp = xfs_dir2_leaf_bests_p(ltp);
		अगर (be16_to_cpu(bestsp[be32_to_cpu(ltp->bestcount) - 1]) ==
					    args->geo->blksize - hdrsz) अणु
			अगर ((error =
			    xfs_dir2_leaf_trim_data(args, lbp,
				    (xfs_dir2_db_t)(be32_to_cpu(ltp->bestcount) - 1))))
				वापस error;
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण
	/*
	 * Read the data block अगर we करोn't alपढ़ोy have it, give up अगर it fails.
	 */
	अगर (!dbp) अणु
		error = xfs_dir3_data_पढ़ो(tp, dp, args->geo->datablk, 0, &dbp);
		अगर (error)
			वापस error;
	पूर्ण
	hdr = dbp->b_addr;
	ASSERT(hdr->magic == cpu_to_be32(XFS_सूची2_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_सूची3_DATA_MAGIC));

	/*
	 * Size of the "leaf" area in the block.
	 */
	size = (uपूर्णांक)माप(xfs_dir2_block_tail_t) +
	       (uपूर्णांक)माप(*lep) * (leafhdr.count - leafhdr.stale);
	/*
	 * Look at the last data entry.
	 */
	tagp = (__be16 *)((अक्षर *)hdr + args->geo->blksize) - 1;
	dup = (xfs_dir2_data_unused_t *)((अक्षर *)hdr + be16_to_cpu(*tagp));
	/*
	 * If it's not free or is too short we can't करो it.
	 */
	अगर (be16_to_cpu(dup->मुक्तtag) != XFS_सूची2_DATA_FREE_TAG ||
	    be16_to_cpu(dup->length) < size)
		वापस 0;

	/*
	 * Start converting it to block क्रमm.
	 */
	xfs_dir3_block_init(mp, tp, dbp, dp);

	needlog = 1;
	needscan = 0;
	/*
	 * Use up the space at the end of the block (blp/btp).
	 */
	error = xfs_dir2_data_use_मुक्त(args, dbp, dup,
			args->geo->blksize - size, size, &needlog, &needscan);
	अगर (error)
		वापस error;
	/*
	 * Initialize the block tail.
	 */
	btp = xfs_dir2_block_tail_p(args->geo, hdr);
	btp->count = cpu_to_be32(leafhdr.count - leafhdr.stale);
	btp->stale = 0;
	xfs_dir2_block_log_tail(tp, dbp);
	/*
	 * Initialize the block leaf area.  We compact out stale entries.
	 */
	lep = xfs_dir2_block_leaf_p(btp);
	क्रम (from = to = 0; from < leafhdr.count; from++) अणु
		अगर (leafhdr.ents[from].address ==
		    cpu_to_be32(XFS_सूची2_शून्य_DATAPTR))
			जारी;
		lep[to++] = leafhdr.ents[from];
	पूर्ण
	ASSERT(to == be32_to_cpu(btp->count));
	xfs_dir2_block_log_leaf(tp, dbp, 0, be32_to_cpu(btp->count) - 1);
	/*
	 * Scan the bestमुक्त अगर we need it and log the data block header.
	 */
	अगर (needscan)
		xfs_dir2_data_मुक्तscan(dp->i_mount, hdr, &needlog);
	अगर (needlog)
		xfs_dir2_data_log_header(args, dbp);
	/*
	 * Pitch the old leaf block.
	 */
	error = xfs_da_shrink_inode(args, args->geo->leafblk, lbp);
	अगर (error)
		वापस error;

	/*
	 * Now see अगर the resulting block can be shrunken to लघुक्रमm.
	 */
	size = xfs_dir2_block_sfsize(dp, hdr, &sfh);
	अगर (size > XFS_IFORK_DSIZE(dp))
		वापस 0;

	वापस xfs_dir2_block_to_sf(args, dbp, size, &sfh);
पूर्ण

/*
 * Convert the लघुक्रमm directory to block क्रमm.
 */
पूर्णांक						/* error */
xfs_dir2_sf_to_block(
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_trans	*tp = args->trans;
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(dp, XFS_DATA_FORK);
	काष्ठा xfs_da_geometry	*geo = args->geo;
	xfs_dir2_db_t		blkno;		/* dir-relative block # (0) */
	xfs_dir2_data_hdr_t	*hdr;		/* block header */
	xfs_dir2_leaf_entry_t	*blp;		/* block leaf entries */
	काष्ठा xfs_buf		*bp;		/* block buffer */
	xfs_dir2_block_tail_t	*btp;		/* block tail poपूर्णांकer */
	xfs_dir2_data_entry_t	*dep;		/* data entry poपूर्णांकer */
	पूर्णांक			dummy;		/* trash */
	xfs_dir2_data_unused_t	*dup;		/* unused entry poपूर्णांकer */
	पूर्णांक			enकरोffset;	/* end of data objects */
	पूर्णांक			error;		/* error वापस value */
	पूर्णांक			i;		/* index */
	पूर्णांक			needlog;	/* need to log block header */
	पूर्णांक			needscan;	/* need to scan block मुक्तspc */
	पूर्णांक			newoffset;	/* offset from current entry */
	अचिन्हित पूर्णांक		offset = geo->data_entry_offset;
	xfs_dir2_sf_entry_t	*sfep;		/* sf entry poपूर्णांकer */
	xfs_dir2_sf_hdr_t	*oldsfp;	/* old लघुक्रमm header  */
	xfs_dir2_sf_hdr_t	*sfp;		/* लघुक्रमm header  */
	__be16			*tagp;		/* end of data entry */
	काष्ठा xfs_name		name;

	trace_xfs_dir2_sf_to_block(args);

	ASSERT(अगरp->अगर_क्रमmat == XFS_DINODE_FMT_LOCAL);
	ASSERT(dp->i_disk_size >= दुरत्व(काष्ठा xfs_dir2_sf_hdr, parent));

	oldsfp = (xfs_dir2_sf_hdr_t *)अगरp->अगर_u1.अगर_data;

	ASSERT(अगरp->अगर_bytes == dp->i_disk_size);
	ASSERT(अगरp->अगर_u1.अगर_data != शून्य);
	ASSERT(dp->i_disk_size >= xfs_dir2_sf_hdr_size(oldsfp->i8count));
	ASSERT(dp->i_df.अगर_nextents == 0);

	/*
	 * Copy the directory पूर्णांकo a temporary buffer.
	 * Then pitch the incore inode data so we can make extents.
	 */
	sfp = kmem_alloc(अगरp->अगर_bytes, 0);
	स_नकल(sfp, oldsfp, अगरp->अगर_bytes);

	xfs_idata_पुनः_स्मृति(dp, -अगरp->अगर_bytes, XFS_DATA_FORK);
	xfs_bmap_local_to_extents_empty(tp, dp, XFS_DATA_FORK);
	dp->i_disk_size = 0;

	/*
	 * Add block 0 to the inode.
	 */
	error = xfs_dir2_grow_inode(args, XFS_सूची2_DATA_SPACE, &blkno);
	अगर (error)
		जाओ out_मुक्त;
	/*
	 * Initialize the data block, then convert it to block क्रमmat.
	 */
	error = xfs_dir3_data_init(args, blkno, &bp);
	अगर (error)
		जाओ out_मुक्त;
	xfs_dir3_block_init(mp, tp, bp, dp);
	hdr = bp->b_addr;

	/*
	 * Compute size of block "tail" area.
	 */
	i = (uपूर्णांक)माप(*btp) +
	    (sfp->count + 2) * (uपूर्णांक)माप(xfs_dir2_leaf_entry_t);
	/*
	 * The whole thing is initialized to मुक्त by the init routine.
	 * Say we're using the leaf and tail area.
	 */
	dup = bp->b_addr + offset;
	needlog = needscan = 0;
	error = xfs_dir2_data_use_मुक्त(args, bp, dup, args->geo->blksize - i,
			i, &needlog, &needscan);
	अगर (error)
		जाओ out_मुक्त;
	ASSERT(needscan == 0);
	/*
	 * Fill in the tail.
	 */
	btp = xfs_dir2_block_tail_p(args->geo, hdr);
	btp->count = cpu_to_be32(sfp->count + 2);	/* ., .. */
	btp->stale = 0;
	blp = xfs_dir2_block_leaf_p(btp);
	enकरोffset = (uपूर्णांक)((अक्षर *)blp - (अक्षर *)hdr);
	/*
	 * Remove the मुक्तspace, we'll manage it.
	 */
	error = xfs_dir2_data_use_मुक्त(args, bp, dup,
			(xfs_dir2_data_aoff_t)((अक्षर *)dup - (अक्षर *)hdr),
			be16_to_cpu(dup->length), &needlog, &needscan);
	अगर (error)
		जाओ out_मुक्त;

	/*
	 * Create entry क्रम .
	 */
	dep = bp->b_addr + offset;
	dep->inumber = cpu_to_be64(dp->i_ino);
	dep->namelen = 1;
	dep->name[0] = '.';
	xfs_dir2_data_put_ftype(mp, dep, XFS_सूची3_FT_सूची);
	tagp = xfs_dir2_data_entry_tag_p(mp, dep);
	*tagp = cpu_to_be16(offset);
	xfs_dir2_data_log_entry(args, bp, dep);
	blp[0].hashval = cpu_to_be32(xfs_dir_hash_करोt);
	blp[0].address = cpu_to_be32(xfs_dir2_byte_to_dataptr(offset));
	offset += xfs_dir2_data_entsize(mp, dep->namelen);

	/*
	 * Create entry क्रम ..
	 */
	dep = bp->b_addr + offset;
	dep->inumber = cpu_to_be64(xfs_dir2_sf_get_parent_ino(sfp));
	dep->namelen = 2;
	dep->name[0] = dep->name[1] = '.';
	xfs_dir2_data_put_ftype(mp, dep, XFS_सूची3_FT_सूची);
	tagp = xfs_dir2_data_entry_tag_p(mp, dep);
	*tagp = cpu_to_be16(offset);
	xfs_dir2_data_log_entry(args, bp, dep);
	blp[1].hashval = cpu_to_be32(xfs_dir_hash_करोtकरोt);
	blp[1].address = cpu_to_be32(xfs_dir2_byte_to_dataptr(offset));
	offset += xfs_dir2_data_entsize(mp, dep->namelen);

	/*
	 * Loop over existing entries, stuff them in.
	 */
	i = 0;
	अगर (!sfp->count)
		sfep = शून्य;
	अन्यथा
		sfep = xfs_dir2_sf_firstentry(sfp);

	/*
	 * Need to preserve the existing offset values in the sf directory.
	 * Insert holes (unused entries) where necessary.
	 */
	जबतक (offset < enकरोffset) अणु
		/*
		 * sfep is null when we reach the end of the list.
		 */
		अगर (sfep == शून्य)
			newoffset = enकरोffset;
		अन्यथा
			newoffset = xfs_dir2_sf_get_offset(sfep);
		/*
		 * There should be a hole here, make one.
		 */
		अगर (offset < newoffset) अणु
			dup = bp->b_addr + offset;
			dup->मुक्तtag = cpu_to_be16(XFS_सूची2_DATA_FREE_TAG);
			dup->length = cpu_to_be16(newoffset - offset);
			*xfs_dir2_data_unused_tag_p(dup) = cpu_to_be16(offset);
			xfs_dir2_data_log_unused(args, bp, dup);
			xfs_dir2_data_मुक्तinsert(hdr,
					xfs_dir2_data_bestमुक्त_p(mp, hdr),
					dup, &dummy);
			offset += be16_to_cpu(dup->length);
			जारी;
		पूर्ण
		/*
		 * Copy a real entry.
		 */
		dep = bp->b_addr + newoffset;
		dep->inumber = cpu_to_be64(xfs_dir2_sf_get_ino(mp, sfp, sfep));
		dep->namelen = sfep->namelen;
		xfs_dir2_data_put_ftype(mp, dep,
				xfs_dir2_sf_get_ftype(mp, sfep));
		स_नकल(dep->name, sfep->name, dep->namelen);
		tagp = xfs_dir2_data_entry_tag_p(mp, dep);
		*tagp = cpu_to_be16(newoffset);
		xfs_dir2_data_log_entry(args, bp, dep);
		name.name = sfep->name;
		name.len = sfep->namelen;
		blp[2 + i].hashval = cpu_to_be32(xfs_dir2_hashname(mp, &name));
		blp[2 + i].address =
			cpu_to_be32(xfs_dir2_byte_to_dataptr(newoffset));
		offset = (पूर्णांक)((अक्षर *)(tagp + 1) - (अक्षर *)hdr);
		अगर (++i == sfp->count)
			sfep = शून्य;
		अन्यथा
			sfep = xfs_dir2_sf_nextentry(mp, sfp, sfep);
	पूर्ण
	/* Done with the temporary buffer */
	kmem_मुक्त(sfp);
	/*
	 * Sort the leaf entries by hash value.
	 */
	xfs_sort(blp, be32_to_cpu(btp->count), माप(*blp), xfs_dir2_block_sort);
	/*
	 * Log the leaf entry area and tail.
	 * Alपढ़ोy logged the header in data_init, ignore needlog.
	 */
	ASSERT(needscan == 0);
	xfs_dir2_block_log_leaf(tp, bp, 0, be32_to_cpu(btp->count) - 1);
	xfs_dir2_block_log_tail(tp, bp);
	xfs_dir3_data_check(dp, bp);
	वापस 0;
out_मुक्त:
	kmem_मुक्त(sfp);
	वापस error;
पूर्ण
