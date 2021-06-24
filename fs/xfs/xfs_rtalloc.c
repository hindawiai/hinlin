<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
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
#समावेश "xfs_inode.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_bmap_btree.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_trans_space.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_rtalloc.h"
#समावेश "xfs_sb.h"

/*
 * Read and वापस the summary inक्रमmation क्रम a given extent size,
 * biपंचांगap block combination.
 * Keeps track of a current summary block, so we करोn't keep पढ़ोing
 * it from the buffer cache.
 */
अटल पूर्णांक
xfs_rtget_summary(
	xfs_mount_t	*mp,		/* file प्रणाली mount काष्ठाure */
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	पूर्णांक		log,		/* log2 of extent size */
	xfs_rtblock_t	bbno,		/* biपंचांगap block number */
	काष्ठा xfs_buf	**rbpp,		/* in/out: summary block buffer */
	xfs_fsblock_t	*rsb,		/* in/out: summary block number */
	xfs_suminfo_t	*sum)		/* out: summary info क्रम this block */
अणु
	वापस xfs_rपंचांगodअगरy_summary_पूर्णांक(mp, tp, log, bbno, 0, rbpp, rsb, sum);
पूर्ण

/*
 * Return whether there are any मुक्त extents in the size range given
 * by low and high, क्रम the biपंचांगap block bbno.
 */
STATIC पूर्णांक				/* error */
xfs_rtany_summary(
	xfs_mount_t	*mp,		/* file प्रणाली mount काष्ठाure */
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	पूर्णांक		low,		/* low log2 extent size */
	पूर्णांक		high,		/* high log2 extent size */
	xfs_rtblock_t	bbno,		/* biपंचांगap block number */
	काष्ठा xfs_buf	**rbpp,		/* in/out: summary block buffer */
	xfs_fsblock_t	*rsb,		/* in/out: summary block number */
	पूर्णांक		*stat)		/* out: any good extents here? */
अणु
	पूर्णांक		error;		/* error value */
	पूर्णांक		log;		/* loop counter, log2 of ext. size */
	xfs_suminfo_t	sum;		/* summary data */

	/* There are no extents at levels < m_rsum_cache[bbno]. */
	अगर (mp->m_rsum_cache && low < mp->m_rsum_cache[bbno])
		low = mp->m_rsum_cache[bbno];

	/*
	 * Loop over logs of extent sizes.
	 */
	क्रम (log = low; log <= high; log++) अणु
		/*
		 * Get one summary datum.
		 */
		error = xfs_rtget_summary(mp, tp, log, bbno, rbpp, rsb, &sum);
		अगर (error) अणु
			वापस error;
		पूर्ण
		/*
		 * If there are any, वापस success.
		 */
		अगर (sum) अणु
			*stat = 1;
			जाओ out;
		पूर्ण
	पूर्ण
	/*
	 * Found nothing, वापस failure.
	 */
	*stat = 0;
out:
	/* There were no extents at levels < log. */
	अगर (mp->m_rsum_cache && log > mp->m_rsum_cache[bbno])
		mp->m_rsum_cache[bbno] = log;
	वापस 0;
पूर्ण


/*
 * Copy and transक्रमm the summary file, given the old and new
 * parameters in the mount काष्ठाures.
 */
STATIC पूर्णांक				/* error */
xfs_rtcopy_summary(
	xfs_mount_t	*omp,		/* old file प्रणाली mount poपूर्णांक */
	xfs_mount_t	*nmp,		/* new file प्रणाली mount poपूर्णांक */
	xfs_trans_t	*tp)		/* transaction poपूर्णांकer */
अणु
	xfs_rtblock_t	bbno;		/* biपंचांगap block number */
	काष्ठा xfs_buf	*bp;		/* summary buffer */
	पूर्णांक		error;		/* error वापस value */
	पूर्णांक		log;		/* summary level number (log length) */
	xfs_suminfo_t	sum;		/* summary data */
	xfs_fsblock_t	sumbno;		/* summary block number */

	bp = शून्य;
	क्रम (log = omp->m_rsumlevels - 1; log >= 0; log--) अणु
		क्रम (bbno = omp->m_sb.sb_rbmblocks - 1;
		     (xfs_srtblock_t)bbno >= 0;
		     bbno--) अणु
			error = xfs_rtget_summary(omp, tp, log, bbno, &bp,
				&sumbno, &sum);
			अगर (error)
				वापस error;
			अगर (sum == 0)
				जारी;
			error = xfs_rपंचांगodअगरy_summary(omp, tp, log, bbno, -sum,
				&bp, &sumbno);
			अगर (error)
				वापस error;
			error = xfs_rपंचांगodअगरy_summary(nmp, tp, log, bbno, sum,
				&bp, &sumbno);
			अगर (error)
				वापस error;
			ASSERT(sum > 0);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
/*
 * Mark an extent specअगरied by start and len allocated.
 * Updates all the summary inक्रमmation as well as the biपंचांगap.
 */
STATIC पूर्णांक				/* error */
xfs_rtallocate_range(
	xfs_mount_t	*mp,		/* file प्रणाली mount poपूर्णांक */
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	xfs_rtblock_t	start,		/* start block to allocate */
	xfs_extlen_t	len,		/* length to allocate */
	काष्ठा xfs_buf	**rbpp,		/* in/out: summary block buffer */
	xfs_fsblock_t	*rsb)		/* in/out: summary block number */
अणु
	xfs_rtblock_t	end;		/* end of the allocated extent */
	पूर्णांक		error;		/* error value */
	xfs_rtblock_t	postblock = 0;	/* first block allocated > end */
	xfs_rtblock_t	preblock = 0;	/* first block allocated < start */

	end = start + len - 1;
	/*
	 * Assume we're allocating out of the middle of a मुक्त extent.
	 * We need to find the beginning and end of the extent so we can
	 * properly update the summary.
	 */
	error = xfs_rtfind_back(mp, tp, start, 0, &preblock);
	अगर (error) अणु
		वापस error;
	पूर्ण
	/*
	 * Find the next allocated block (end of मुक्त extent).
	 */
	error = xfs_rtfind_क्रमw(mp, tp, end, mp->m_sb.sb_rextents - 1,
		&postblock);
	अगर (error) अणु
		वापस error;
	पूर्ण
	/*
	 * Decrement the summary inक्रमmation corresponding to the entire
	 * (old) मुक्त extent.
	 */
	error = xfs_rपंचांगodअगरy_summary(mp, tp,
		XFS_RTBLOCKLOG(postblock + 1 - preblock),
		XFS_BITTOBLOCK(mp, preblock), -1, rbpp, rsb);
	अगर (error) अणु
		वापस error;
	पूर्ण
	/*
	 * If there are blocks not being allocated at the front of the
	 * old extent, add summary data क्रम them to be मुक्त.
	 */
	अगर (preblock < start) अणु
		error = xfs_rपंचांगodअगरy_summary(mp, tp,
			XFS_RTBLOCKLOG(start - preblock),
			XFS_BITTOBLOCK(mp, preblock), 1, rbpp, rsb);
		अगर (error) अणु
			वापस error;
		पूर्ण
	पूर्ण
	/*
	 * If there are blocks not being allocated at the end of the
	 * old extent, add summary data क्रम them to be मुक्त.
	 */
	अगर (postblock > end) अणु
		error = xfs_rपंचांगodअगरy_summary(mp, tp,
			XFS_RTBLOCKLOG(postblock - end),
			XFS_BITTOBLOCK(mp, end + 1), 1, rbpp, rsb);
		अगर (error) अणु
			वापस error;
		पूर्ण
	पूर्ण
	/*
	 * Modअगरy the biपंचांगap to mark this extent allocated.
	 */
	error = xfs_rपंचांगodअगरy_range(mp, tp, start, len, 0);
	वापस error;
पूर्ण

/*
 * Attempt to allocate an extent minlen<=len<=maxlen starting from
 * biपंचांगap block bbno.  If we करोn't get maxlen then use prod to trim
 * the length, अगर given.  Returns error; वापसs starting block in *rtblock.
 * The lengths are all in rtextents.
 */
STATIC पूर्णांक				/* error */
xfs_rtallocate_extent_block(
	xfs_mount_t	*mp,		/* file प्रणाली mount poपूर्णांक */
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	xfs_rtblock_t	bbno,		/* biपंचांगap block number */
	xfs_extlen_t	minlen,		/* minimum length to allocate */
	xfs_extlen_t	maxlen,		/* maximum length to allocate */
	xfs_extlen_t	*len,		/* out: actual length allocated */
	xfs_rtblock_t	*nextp,		/* out: next block to try */
	काष्ठा xfs_buf	**rbpp,		/* in/out: summary block buffer */
	xfs_fsblock_t	*rsb,		/* in/out: summary block number */
	xfs_extlen_t	prod,		/* extent product factor */
	xfs_rtblock_t	*rtblock)	/* out: start block allocated */
अणु
	xfs_rtblock_t	besti;		/* best rtblock found so far */
	xfs_rtblock_t	bestlen;	/* best length found so far */
	xfs_rtblock_t	end;		/* last rtblock in chunk */
	पूर्णांक		error;		/* error value */
	xfs_rtblock_t	i;		/* current rtblock trying */
	xfs_rtblock_t	next;		/* next rtblock to try */
	पूर्णांक		stat;		/* status from पूर्णांकernal calls */

	/*
	 * Loop over all the extents starting in this biपंचांगap block,
	 * looking क्रम one that's दीर्घ enough.
	 */
	क्रम (i = XFS_BLOCKTOBIT(mp, bbno), besti = -1, bestlen = 0,
		end = XFS_BLOCKTOBIT(mp, bbno + 1) - 1;
	     i <= end;
	     i++) अणु
		/* Make sure we करोn't scan off the end of the rt volume. */
		maxlen = min(mp->m_sb.sb_rextents, i + maxlen) - i;

		/*
		 * See अगर there's a मुक्त extent of maxlen starting at i.
		 * If it's not so then next will contain the first non-मुक्त.
		 */
		error = xfs_rtcheck_range(mp, tp, i, maxlen, 1, &next, &stat);
		अगर (error) अणु
			वापस error;
		पूर्ण
		अगर (stat) अणु
			/*
			 * i क्रम maxlen is all मुक्त, allocate and वापस that.
			 */
			error = xfs_rtallocate_range(mp, tp, i, maxlen, rbpp,
				rsb);
			अगर (error) अणु
				वापस error;
			पूर्ण
			*len = maxlen;
			*rtblock = i;
			वापस 0;
		पूर्ण
		/*
		 * In the हाल where we have a variable-sized allocation
		 * request, figure out how big this मुक्त piece is,
		 * and अगर it's big enough क्रम the minimum, and the best
		 * so far, remember it.
		 */
		अगर (minlen < maxlen) अणु
			xfs_rtblock_t	thislen;	/* this extent size */

			thislen = next - i;
			अगर (thislen >= minlen && thislen > bestlen) अणु
				besti = i;
				bestlen = thislen;
			पूर्ण
		पूर्ण
		/*
		 * If not करोne yet, find the start of the next मुक्त space.
		 */
		अगर (next < end) अणु
			error = xfs_rtfind_क्रमw(mp, tp, next, end, &i);
			अगर (error) अणु
				वापस error;
			पूर्ण
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण
	/*
	 * Searched the whole thing & didn't find a maxlen मुक्त extent.
	 */
	अगर (minlen < maxlen && besti != -1) अणु
		xfs_extlen_t	p;	/* amount to trim length by */

		/*
		 * If size should be a multiple of prod, make that so.
		 */
		अगर (prod > 1) अणु
			भाग_u64_rem(bestlen, prod, &p);
			अगर (p)
				bestlen -= p;
		पूर्ण

		/*
		 * Allocate besti क्रम bestlen & वापस that.
		 */
		error = xfs_rtallocate_range(mp, tp, besti, bestlen, rbpp, rsb);
		अगर (error) अणु
			वापस error;
		पूर्ण
		*len = bestlen;
		*rtblock = besti;
		वापस 0;
	पूर्ण
	/*
	 * Allocation failed.  Set *nextp to the next block to try.
	 */
	*nextp = next;
	*rtblock = शून्यRTBLOCK;
	वापस 0;
पूर्ण

/*
 * Allocate an extent of length minlen<=len<=maxlen, starting at block
 * bno.  If we करोn't get maxlen then use prod to trim the length, अगर given.
 * Returns error; वापसs starting block in *rtblock.
 * The lengths are all in rtextents.
 */
STATIC पूर्णांक				/* error */
xfs_rtallocate_extent_exact(
	xfs_mount_t	*mp,		/* file प्रणाली mount poपूर्णांक */
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	xfs_rtblock_t	bno,		/* starting block number to allocate */
	xfs_extlen_t	minlen,		/* minimum length to allocate */
	xfs_extlen_t	maxlen,		/* maximum length to allocate */
	xfs_extlen_t	*len,		/* out: actual length allocated */
	काष्ठा xfs_buf	**rbpp,		/* in/out: summary block buffer */
	xfs_fsblock_t	*rsb,		/* in/out: summary block number */
	xfs_extlen_t	prod,		/* extent product factor */
	xfs_rtblock_t	*rtblock)	/* out: start block allocated */
अणु
	पूर्णांक		error;		/* error value */
	xfs_extlen_t	i;		/* extent length trimmed due to prod */
	पूर्णांक		isमुक्त;		/* extent is मुक्त */
	xfs_rtblock_t	next;		/* next block to try (dummy) */

	ASSERT(minlen % prod == 0 && maxlen % prod == 0);
	/*
	 * Check अगर the range in question (क्रम maxlen) is मुक्त.
	 */
	error = xfs_rtcheck_range(mp, tp, bno, maxlen, 1, &next, &isमुक्त);
	अगर (error) अणु
		वापस error;
	पूर्ण
	अगर (isमुक्त) अणु
		/*
		 * If it is, allocate it and वापस success.
		 */
		error = xfs_rtallocate_range(mp, tp, bno, maxlen, rbpp, rsb);
		अगर (error) अणु
			वापस error;
		पूर्ण
		*len = maxlen;
		*rtblock = bno;
		वापस 0;
	पूर्ण
	/*
	 * If not, allocate what there is, अगर it's at least minlen.
	 */
	maxlen = next - bno;
	अगर (maxlen < minlen) अणु
		/*
		 * Failed, वापस failure status.
		 */
		*rtblock = शून्यRTBLOCK;
		वापस 0;
	पूर्ण
	/*
	 * Trim off tail of extent, अगर prod is specअगरied.
	 */
	अगर (prod > 1 && (i = maxlen % prod)) अणु
		maxlen -= i;
		अगर (maxlen < minlen) अणु
			/*
			 * Now we can't करो it, वापस failure status.
			 */
			*rtblock = शून्यRTBLOCK;
			वापस 0;
		पूर्ण
	पूर्ण
	/*
	 * Allocate what we can and वापस it.
	 */
	error = xfs_rtallocate_range(mp, tp, bno, maxlen, rbpp, rsb);
	अगर (error) अणु
		वापस error;
	पूर्ण
	*len = maxlen;
	*rtblock = bno;
	वापस 0;
पूर्ण

/*
 * Allocate an extent of length minlen<=len<=maxlen, starting as near
 * to bno as possible.  If we करोn't get maxlen then use prod to trim
 * the length, अगर given.  The lengths are all in rtextents.
 */
STATIC पूर्णांक				/* error */
xfs_rtallocate_extent_near(
	xfs_mount_t	*mp,		/* file प्रणाली mount poपूर्णांक */
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	xfs_rtblock_t	bno,		/* starting block number to allocate */
	xfs_extlen_t	minlen,		/* minimum length to allocate */
	xfs_extlen_t	maxlen,		/* maximum length to allocate */
	xfs_extlen_t	*len,		/* out: actual length allocated */
	काष्ठा xfs_buf	**rbpp,		/* in/out: summary block buffer */
	xfs_fsblock_t	*rsb,		/* in/out: summary block number */
	xfs_extlen_t	prod,		/* extent product factor */
	xfs_rtblock_t	*rtblock)	/* out: start block allocated */
अणु
	पूर्णांक		any;		/* any useful extents from summary */
	xfs_rtblock_t	bbno;		/* biपंचांगap block number */
	पूर्णांक		error;		/* error value */
	पूर्णांक		i;		/* biपंचांगap block offset (loop control) */
	पूर्णांक		j;		/* secondary loop control */
	पूर्णांक		log2len;	/* log2 of minlen */
	xfs_rtblock_t	n;		/* next block to try */
	xfs_rtblock_t	r;		/* result block */

	ASSERT(minlen % prod == 0 && maxlen % prod == 0);
	/*
	 * If the block number given is off the end, silently set it to
	 * the last block.
	 */
	अगर (bno >= mp->m_sb.sb_rextents)
		bno = mp->m_sb.sb_rextents - 1;

	/* Make sure we करोn't run off the end of the rt volume. */
	maxlen = min(mp->m_sb.sb_rextents, bno + maxlen) - bno;
	अगर (maxlen < minlen) अणु
		*rtblock = शून्यRTBLOCK;
		वापस 0;
	पूर्ण

	/*
	 * Try the exact allocation first.
	 */
	error = xfs_rtallocate_extent_exact(mp, tp, bno, minlen, maxlen, len,
		rbpp, rsb, prod, &r);
	अगर (error) अणु
		वापस error;
	पूर्ण
	/*
	 * If the exact allocation worked, वापस that.
	 */
	अगर (r != शून्यRTBLOCK) अणु
		*rtblock = r;
		वापस 0;
	पूर्ण
	bbno = XFS_BITTOBLOCK(mp, bno);
	i = 0;
	ASSERT(minlen != 0);
	log2len = xfs_highbit32(minlen);
	/*
	 * Loop over all biपंचांगap blocks (bbno + i is current block).
	 */
	क्रम (;;) अणु
		/*
		 * Get summary inक्रमmation of extents of all useful levels
		 * starting in this biपंचांगap block.
		 */
		error = xfs_rtany_summary(mp, tp, log2len, mp->m_rsumlevels - 1,
			bbno + i, rbpp, rsb, &any);
		अगर (error) अणु
			वापस error;
		पूर्ण
		/*
		 * If there are any useful extents starting here, try
		 * allocating one.
		 */
		अगर (any) अणु
			/*
			 * On the positive side of the starting location.
			 */
			अगर (i >= 0) अणु
				/*
				 * Try to allocate an extent starting in
				 * this block.
				 */
				error = xfs_rtallocate_extent_block(mp, tp,
					bbno + i, minlen, maxlen, len, &n, rbpp,
					rsb, prod, &r);
				अगर (error) अणु
					वापस error;
				पूर्ण
				/*
				 * If it worked, वापस it.
				 */
				अगर (r != शून्यRTBLOCK) अणु
					*rtblock = r;
					वापस 0;
				पूर्ण
			पूर्ण
			/*
			 * On the negative side of the starting location.
			 */
			अन्यथा अणु		/* i < 0 */
				/*
				 * Loop backwards through the biपंचांगap blocks from
				 * the starting poपूर्णांक-1 up to where we are now.
				 * There should be an extent which ends in this
				 * biपंचांगap block and is दीर्घ enough.
				 */
				क्रम (j = -1; j > i; j--) अणु
					/*
					 * Grab the summary inक्रमmation क्रम
					 * this biपंचांगap block.
					 */
					error = xfs_rtany_summary(mp, tp,
						log2len, mp->m_rsumlevels - 1,
						bbno + j, rbpp, rsb, &any);
					अगर (error) अणु
						वापस error;
					पूर्ण
					/*
					 * If there's no extent given in the
					 * summary that means the extent we
					 * found must carry over from an
					 * earlier block.  If there is an
					 * extent given, we've alपढ़ोy tried
					 * that allocation, करोn't करो it again.
					 */
					अगर (any)
						जारी;
					error = xfs_rtallocate_extent_block(mp,
						tp, bbno + j, minlen, maxlen,
						len, &n, rbpp, rsb, prod, &r);
					अगर (error) अणु
						वापस error;
					पूर्ण
					/*
					 * If it works, वापस the extent.
					 */
					अगर (r != शून्यRTBLOCK) अणु
						*rtblock = r;
						वापस 0;
					पूर्ण
				पूर्ण
				/*
				 * There weren't पूर्णांकervening biपंचांगap blocks
				 * with a दीर्घ enough extent, or the
				 * allocation didn't work क्रम some reason
				 * (i.e. it's a little * too लघु).
				 * Try to allocate from the summary block
				 * that we found.
				 */
				error = xfs_rtallocate_extent_block(mp, tp,
					bbno + i, minlen, maxlen, len, &n, rbpp,
					rsb, prod, &r);
				अगर (error) अणु
					वापस error;
				पूर्ण
				/*
				 * If it works, वापस the extent.
				 */
				अगर (r != शून्यRTBLOCK) अणु
					*rtblock = r;
					वापस 0;
				पूर्ण
			पूर्ण
		पूर्ण
		/*
		 * Loop control.  If we were on the positive side, and there's
		 * still more blocks on the negative side, go there.
		 */
		अगर (i > 0 && (पूर्णांक)bbno - i >= 0)
			i = -i;
		/*
		 * If positive, and no more negative, but there are more
		 * positive, go there.
		 */
		अन्यथा अगर (i > 0 && (पूर्णांक)bbno + i < mp->m_sb.sb_rbmblocks - 1)
			i++;
		/*
		 * If negative or 0 (just started), and there are positive
		 * blocks to go, go there.  The 0 हाल moves to block 1.
		 */
		अन्यथा अगर (i <= 0 && (पूर्णांक)bbno - i < mp->m_sb.sb_rbmblocks - 1)
			i = 1 - i;
		/*
		 * If negative or 0 and there are more negative blocks,
		 * go there.
		 */
		अन्यथा अगर (i <= 0 && (पूर्णांक)bbno + i > 0)
			i--;
		/*
		 * Must be करोne.  Return failure.
		 */
		अन्यथा
			अवरोध;
	पूर्ण
	*rtblock = शून्यRTBLOCK;
	वापस 0;
पूर्ण

/*
 * Allocate an extent of length minlen<=len<=maxlen, with no position
 * specअगरied.  If we करोn't get maxlen then use prod to trim
 * the length, अगर given.  The lengths are all in rtextents.
 */
STATIC पूर्णांक				/* error */
xfs_rtallocate_extent_size(
	xfs_mount_t	*mp,		/* file प्रणाली mount poपूर्णांक */
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	xfs_extlen_t	minlen,		/* minimum length to allocate */
	xfs_extlen_t	maxlen,		/* maximum length to allocate */
	xfs_extlen_t	*len,		/* out: actual length allocated */
	काष्ठा xfs_buf	**rbpp,		/* in/out: summary block buffer */
	xfs_fsblock_t	*rsb,		/* in/out: summary block number */
	xfs_extlen_t	prod,		/* extent product factor */
	xfs_rtblock_t	*rtblock)	/* out: start block allocated */
अणु
	पूर्णांक		error;		/* error value */
	पूर्णांक		i;		/* biपंचांगap block number */
	पूर्णांक		l;		/* level number (loop control) */
	xfs_rtblock_t	n;		/* next block to be tried */
	xfs_rtblock_t	r;		/* result block number */
	xfs_suminfo_t	sum;		/* summary inक्रमmation क्रम extents */

	ASSERT(minlen % prod == 0 && maxlen % prod == 0);
	ASSERT(maxlen != 0);

	/*
	 * Loop over all the levels starting with maxlen.
	 * At each level, look at all the biपंचांगap blocks, to see अगर there
	 * are extents starting there that are दीर्घ enough (>= maxlen).
	 * Note, only on the initial level can the allocation fail अगर
	 * the summary says there's an extent.
	 */
	क्रम (l = xfs_highbit32(maxlen); l < mp->m_rsumlevels; l++) अणु
		/*
		 * Loop over all the biपंचांगap blocks.
		 */
		क्रम (i = 0; i < mp->m_sb.sb_rbmblocks; i++) अणु
			/*
			 * Get the summary क्रम this level/block.
			 */
			error = xfs_rtget_summary(mp, tp, l, i, rbpp, rsb,
				&sum);
			अगर (error) अणु
				वापस error;
			पूर्ण
			/*
			 * Nothing there, on to the next block.
			 */
			अगर (!sum)
				जारी;
			/*
			 * Try allocating the extent.
			 */
			error = xfs_rtallocate_extent_block(mp, tp, i, maxlen,
				maxlen, len, &n, rbpp, rsb, prod, &r);
			अगर (error) अणु
				वापस error;
			पूर्ण
			/*
			 * If it worked, वापस that.
			 */
			अगर (r != शून्यRTBLOCK) अणु
				*rtblock = r;
				वापस 0;
			पूर्ण
			/*
			 * If the "next block to try" वापसed from the
			 * allocator is beyond the next biपंचांगap block,
			 * skip to that biपंचांगap block.
			 */
			अगर (XFS_BITTOBLOCK(mp, n) > i + 1)
				i = XFS_BITTOBLOCK(mp, n) - 1;
		पूर्ण
	पूर्ण
	/*
	 * Didn't find any maxlen blocks.  Try smaller ones, unless
	 * we're asking क्रम a fixed size extent.
	 */
	अगर (minlen > --maxlen) अणु
		*rtblock = शून्यRTBLOCK;
		वापस 0;
	पूर्ण
	ASSERT(minlen != 0);
	ASSERT(maxlen != 0);

	/*
	 * Loop over sizes, from maxlen करोwn to minlen.
	 * This समय, when we करो the allocations, allow smaller ones
	 * to succeed.
	 */
	क्रम (l = xfs_highbit32(maxlen); l >= xfs_highbit32(minlen); l--) अणु
		/*
		 * Loop over all the biपंचांगap blocks, try an allocation
		 * starting in that block.
		 */
		क्रम (i = 0; i < mp->m_sb.sb_rbmblocks; i++) अणु
			/*
			 * Get the summary inक्रमmation क्रम this level/block.
			 */
			error =	xfs_rtget_summary(mp, tp, l, i, rbpp, rsb,
						  &sum);
			अगर (error) अणु
				वापस error;
			पूर्ण
			/*
			 * If nothing there, go on to next.
			 */
			अगर (!sum)
				जारी;
			/*
			 * Try the allocation.  Make sure the specअगरied
			 * minlen/maxlen are in the possible range क्रम
			 * this summary level.
			 */
			error = xfs_rtallocate_extent_block(mp, tp, i,
					XFS_RTMAX(minlen, 1 << l),
					XFS_RTMIN(maxlen, (1 << (l + 1)) - 1),
					len, &n, rbpp, rsb, prod, &r);
			अगर (error) अणु
				वापस error;
			पूर्ण
			/*
			 * If it worked, वापस that extent.
			 */
			अगर (r != शून्यRTBLOCK) अणु
				*rtblock = r;
				वापस 0;
			पूर्ण
			/*
			 * If the "next block to try" वापसed from the
			 * allocator is beyond the next biपंचांगap block,
			 * skip to that biपंचांगap block.
			 */
			अगर (XFS_BITTOBLOCK(mp, n) > i + 1)
				i = XFS_BITTOBLOCK(mp, n) - 1;
		पूर्ण
	पूर्ण
	/*
	 * Got nothing, वापस failure.
	 */
	*rtblock = शून्यRTBLOCK;
	वापस 0;
पूर्ण

/*
 * Allocate space to the biपंचांगap or summary file, and zero it, क्रम growfs.
 */
STATIC पूर्णांक
xfs_growfs_rt_alloc(
	काष्ठा xfs_mount	*mp,		/* file प्रणाली mount poपूर्णांक */
	xfs_extlen_t		oblocks,	/* old count of blocks */
	xfs_extlen_t		nblocks,	/* new count of blocks */
	काष्ठा xfs_inode	*ip)		/* inode (biपंचांगap/summary) */
अणु
	xfs_fileoff_t		bno;		/* block number in file */
	काष्ठा xfs_buf		*bp;	/* temporary buffer क्रम zeroing */
	xfs_daddr_t		d;		/* disk block address */
	पूर्णांक			error;		/* error वापस value */
	xfs_fsblock_t		fsbno;		/* fileप्रणाली block क्रम bno */
	काष्ठा xfs_bmbt_irec	map;		/* block map output */
	पूर्णांक			nmap;		/* number of block maps */
	पूर्णांक			resblks;	/* space reservation */
	क्रमागत xfs_blft		buf_type;
	काष्ठा xfs_trans	*tp;

	अगर (ip == mp->m_rsumip)
		buf_type = XFS_BLFT_RTSUMMARY_BUF;
	अन्यथा
		buf_type = XFS_BLFT_RTBITMAP_BUF;

	/*
	 * Allocate space to the file, as necessary.
	 */
	जबतक (oblocks < nblocks) अणु
		resblks = XFS_GROWFSRT_SPACE_RES(mp, nblocks - oblocks);
		/*
		 * Reserve space & log क्रम one extent added to the file.
		 */
		error = xfs_trans_alloc(mp, &M_RES(mp)->tr_growrtalloc, resblks,
				0, 0, &tp);
		अगर (error)
			वापस error;
		/*
		 * Lock the inode.
		 */
		xfs_ilock(ip, XFS_ILOCK_EXCL);
		xfs_trans_ijoin(tp, ip, XFS_ILOCK_EXCL);

		error = xfs_iext_count_may_overflow(ip, XFS_DATA_FORK,
				XFS_IEXT_ADD_NOSPLIT_CNT);
		अगर (error)
			जाओ out_trans_cancel;

		/*
		 * Allocate blocks to the biपंचांगap file.
		 */
		nmap = 1;
		error = xfs_bmapi_ग_लिखो(tp, ip, oblocks, nblocks - oblocks,
					XFS_BMAPI_METADATA, 0, &map, &nmap);
		अगर (!error && nmap < 1)
			error = -ENOSPC;
		अगर (error)
			जाओ out_trans_cancel;
		/*
		 * Free any blocks मुक्तd up in the transaction, then commit.
		 */
		error = xfs_trans_commit(tp);
		अगर (error)
			वापस error;
		/*
		 * Now we need to clear the allocated blocks.
		 * Do this one block per transaction, to keep it simple.
		 */
		क्रम (bno = map.br_startoff, fsbno = map.br_startblock;
		     bno < map.br_startoff + map.br_blockcount;
		     bno++, fsbno++) अणु
			/*
			 * Reserve log क्रम one block zeroing.
			 */
			error = xfs_trans_alloc(mp, &M_RES(mp)->tr_growrtzero,
					0, 0, 0, &tp);
			अगर (error)
				वापस error;
			/*
			 * Lock the biपंचांगap inode.
			 */
			xfs_ilock(ip, XFS_ILOCK_EXCL);
			xfs_trans_ijoin(tp, ip, XFS_ILOCK_EXCL);
			/*
			 * Get a buffer क्रम the block.
			 */
			d = XFS_FSB_TO_DADDR(mp, fsbno);
			error = xfs_trans_get_buf(tp, mp->m_ddev_targp, d,
					mp->m_bsize, 0, &bp);
			अगर (error)
				जाओ out_trans_cancel;

			xfs_trans_buf_set_type(tp, bp, buf_type);
			bp->b_ops = &xfs_rtbuf_ops;
			स_रखो(bp->b_addr, 0, mp->m_sb.sb_blocksize);
			xfs_trans_log_buf(tp, bp, 0, mp->m_sb.sb_blocksize - 1);
			/*
			 * Commit the transaction.
			 */
			error = xfs_trans_commit(tp);
			अगर (error)
				वापस error;
		पूर्ण
		/*
		 * Go on to the next extent, अगर any.
		 */
		oblocks = map.br_startoff + map.br_blockcount;
	पूर्ण

	वापस 0;

out_trans_cancel:
	xfs_trans_cancel(tp);
	वापस error;
पूर्ण

अटल व्योम
xfs_alloc_rsum_cache(
	xfs_mount_t	*mp,		/* file प्रणाली mount काष्ठाure */
	xfs_extlen_t	rbmblocks)	/* number of rt biपंचांगap blocks */
अणु
	/*
	 * The rsum cache is initialized to all zeroes, which is trivially a
	 * lower bound on the minimum level with any मुक्त extents. We can
	 * जारी without the cache अगर it couldn't be allocated.
	 */
	mp->m_rsum_cache = kvzalloc(rbmblocks, GFP_KERNEL);
	अगर (!mp->m_rsum_cache)
		xfs_warn(mp, "could not allocate realtime summary cache");
पूर्ण

/*
 * Visible (exported) functions.
 */

/*
 * Grow the realसमय area of the fileप्रणाली.
 */
पूर्णांक
xfs_growfs_rt(
	xfs_mount_t	*mp,		/* mount poपूर्णांक क्रम fileप्रणाली */
	xfs_growfs_rt_t	*in)		/* growfs rt input काष्ठा */
अणु
	xfs_rtblock_t	bmbno;		/* biपंचांगap block number */
	काष्ठा xfs_buf	*bp;		/* temporary buffer */
	पूर्णांक		error;		/* error वापस value */
	xfs_mount_t	*nmp;		/* new (fake) mount काष्ठाure */
	xfs_rfsblock_t	nrblocks;	/* new number of realसमय blocks */
	xfs_extlen_t	nrbmblocks;	/* new number of rt biपंचांगap blocks */
	xfs_rtblock_t	nrextents;	/* new number of realसमय extents */
	uपूर्णांक8_t		nrextslog;	/* new log2 of sb_rextents */
	xfs_extlen_t	nrsumblocks;	/* new number of summary blocks */
	uपूर्णांक		nrsumlevels;	/* new rt summary levels */
	uपूर्णांक		nrsumsize;	/* new size of rt summary, bytes */
	xfs_sb_t	*nsbp;		/* new superblock */
	xfs_extlen_t	rbmblocks;	/* current number of rt biपंचांगap blocks */
	xfs_extlen_t	rsumblocks;	/* current number of rt summary blks */
	xfs_sb_t	*sbp;		/* old superblock */
	xfs_fsblock_t	sumbno;		/* summary block number */
	uपूर्णांक8_t		*rsum_cache;	/* old summary cache */

	sbp = &mp->m_sb;
	/*
	 * Initial error checking.
	 */
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	अगर (mp->m_rtdev_targp == शून्य || mp->m_rbmip == शून्य ||
	    (nrblocks = in->newblocks) <= sbp->sb_rblocks ||
	    (sbp->sb_rblocks && (in->extsize != sbp->sb_rextsize)))
		वापस -EINVAL;
	अगर ((error = xfs_sb_validate_fsb_count(sbp, nrblocks)))
		वापस error;
	/*
	 * Read in the last block of the device, make sure it exists.
	 */
	error = xfs_buf_पढ़ो_uncached(mp->m_rtdev_targp,
				XFS_FSB_TO_BB(mp, nrblocks - 1),
				XFS_FSB_TO_BB(mp, 1), 0, &bp, शून्य);
	अगर (error)
		वापस error;
	xfs_buf_rअन्यथा(bp);

	/*
	 * Calculate new parameters.  These are the final values to be reached.
	 */
	nrextents = nrblocks;
	करो_भाग(nrextents, in->extsize);
	nrbmblocks = howmany_64(nrextents, NBBY * sbp->sb_blocksize);
	nrextslog = xfs_highbit32(nrextents);
	nrsumlevels = nrextslog + 1;
	nrsumsize = (uपूर्णांक)माप(xfs_suminfo_t) * nrsumlevels * nrbmblocks;
	nrsumblocks = XFS_B_TO_FSB(mp, nrsumsize);
	nrsumsize = XFS_FSB_TO_B(mp, nrsumblocks);
	/*
	 * New summary size can't be more than half the size of
	 * the log.  This prevents us from getting a log overflow,
	 * since we'll log basically the whole summary file at once.
	 */
	अगर (nrsumblocks > (mp->m_sb.sb_logblocks >> 1))
		वापस -EINVAL;
	/*
	 * Get the old block counts क्रम biपंचांगap and summary inodes.
	 * These can't change since other growfs callers are locked out.
	 */
	rbmblocks = XFS_B_TO_FSB(mp, mp->m_rbmip->i_disk_size);
	rsumblocks = XFS_B_TO_FSB(mp, mp->m_rsumip->i_disk_size);
	/*
	 * Allocate space to the biपंचांगap and summary files, as necessary.
	 */
	error = xfs_growfs_rt_alloc(mp, rbmblocks, nrbmblocks, mp->m_rbmip);
	अगर (error)
		वापस error;
	error = xfs_growfs_rt_alloc(mp, rsumblocks, nrsumblocks, mp->m_rsumip);
	अगर (error)
		वापस error;

	rsum_cache = mp->m_rsum_cache;
	अगर (nrbmblocks != sbp->sb_rbmblocks)
		xfs_alloc_rsum_cache(mp, nrbmblocks);

	/*
	 * Allocate a new (fake) mount/sb.
	 */
	nmp = kmem_alloc(माप(*nmp), 0);
	/*
	 * Loop over the biपंचांगap blocks.
	 * We will करो everything one biपंचांगap block at a समय.
	 * Skip the current block अगर it is exactly full.
	 * This also deals with the हाल where there were no rtextents beक्रमe.
	 */
	क्रम (bmbno = sbp->sb_rbmblocks -
		     ((sbp->sb_rextents & ((1 << mp->m_blkbit_log) - 1)) != 0);
	     bmbno < nrbmblocks;
	     bmbno++) अणु
		xfs_trans_t	*tp;

		*nmp = *mp;
		nsbp = &nmp->m_sb;
		/*
		 * Calculate new sb and mount fields क्रम this round.
		 */
		nsbp->sb_rextsize = in->extsize;
		nsbp->sb_rbmblocks = bmbno + 1;
		nsbp->sb_rblocks =
			XFS_RTMIN(nrblocks,
				  nsbp->sb_rbmblocks * NBBY *
				  nsbp->sb_blocksize * nsbp->sb_rextsize);
		nsbp->sb_rextents = nsbp->sb_rblocks;
		करो_भाग(nsbp->sb_rextents, nsbp->sb_rextsize);
		ASSERT(nsbp->sb_rextents != 0);
		nsbp->sb_rextslog = xfs_highbit32(nsbp->sb_rextents);
		nrsumlevels = nmp->m_rsumlevels = nsbp->sb_rextslog + 1;
		nrsumsize =
			(uपूर्णांक)माप(xfs_suminfo_t) * nrsumlevels *
			nsbp->sb_rbmblocks;
		nrsumblocks = XFS_B_TO_FSB(mp, nrsumsize);
		nmp->m_rsumsize = nrsumsize = XFS_FSB_TO_B(mp, nrsumblocks);
		/*
		 * Start a transaction, get the log reservation.
		 */
		error = xfs_trans_alloc(mp, &M_RES(mp)->tr_growrtमुक्त, 0, 0, 0,
				&tp);
		अगर (error)
			अवरोध;
		/*
		 * Lock out other callers by grabbing the biपंचांगap inode lock.
		 */
		xfs_ilock(mp->m_rbmip, XFS_ILOCK_EXCL | XFS_ILOCK_RTBITMAP);
		xfs_trans_ijoin(tp, mp->m_rbmip, XFS_ILOCK_EXCL);
		/*
		 * Update the biपंचांगap inode's size ondisk and incore.  We need
		 * to update the incore size so that inode inactivation won't
		 * punch what it thinks are "posteof" blocks.
		 */
		mp->m_rbmip->i_disk_size =
			nsbp->sb_rbmblocks * nsbp->sb_blocksize;
		i_size_ग_लिखो(VFS_I(mp->m_rbmip), mp->m_rbmip->i_disk_size);
		xfs_trans_log_inode(tp, mp->m_rbmip, XFS_ILOG_CORE);
		/*
		 * Get the summary inode पूर्णांकo the transaction.
		 */
		xfs_ilock(mp->m_rsumip, XFS_ILOCK_EXCL | XFS_ILOCK_RTSUM);
		xfs_trans_ijoin(tp, mp->m_rsumip, XFS_ILOCK_EXCL);
		/*
		 * Update the summary inode's size.  We need to update the
		 * incore size so that inode inactivation won't punch what it
		 * thinks are "posteof" blocks.
		 */
		mp->m_rsumip->i_disk_size = nmp->m_rsumsize;
		i_size_ग_लिखो(VFS_I(mp->m_rsumip), mp->m_rsumip->i_disk_size);
		xfs_trans_log_inode(tp, mp->m_rsumip, XFS_ILOG_CORE);
		/*
		 * Copy summary data from old to new sizes.
		 * Do this when the real size (not block-aligned) changes.
		 */
		अगर (sbp->sb_rbmblocks != nsbp->sb_rbmblocks ||
		    mp->m_rsumlevels != nmp->m_rsumlevels) अणु
			error = xfs_rtcopy_summary(mp, nmp, tp);
			अगर (error)
				जाओ error_cancel;
		पूर्ण
		/*
		 * Update superblock fields.
		 */
		अगर (nsbp->sb_rextsize != sbp->sb_rextsize)
			xfs_trans_mod_sb(tp, XFS_TRANS_SB_REXTSIZE,
				nsbp->sb_rextsize - sbp->sb_rextsize);
		अगर (nsbp->sb_rbmblocks != sbp->sb_rbmblocks)
			xfs_trans_mod_sb(tp, XFS_TRANS_SB_RBMBLOCKS,
				nsbp->sb_rbmblocks - sbp->sb_rbmblocks);
		अगर (nsbp->sb_rblocks != sbp->sb_rblocks)
			xfs_trans_mod_sb(tp, XFS_TRANS_SB_RBLOCKS,
				nsbp->sb_rblocks - sbp->sb_rblocks);
		अगर (nsbp->sb_rextents != sbp->sb_rextents)
			xfs_trans_mod_sb(tp, XFS_TRANS_SB_REXTENTS,
				nsbp->sb_rextents - sbp->sb_rextents);
		अगर (nsbp->sb_rextslog != sbp->sb_rextslog)
			xfs_trans_mod_sb(tp, XFS_TRANS_SB_REXTSLOG,
				nsbp->sb_rextslog - sbp->sb_rextslog);
		/*
		 * Free new extent.
		 */
		bp = शून्य;
		error = xfs_rtमुक्त_range(nmp, tp, sbp->sb_rextents,
			nsbp->sb_rextents - sbp->sb_rextents, &bp, &sumbno);
		अगर (error) अणु
error_cancel:
			xfs_trans_cancel(tp);
			अवरोध;
		पूर्ण
		/*
		 * Mark more blocks मुक्त in the superblock.
		 */
		xfs_trans_mod_sb(tp, XFS_TRANS_SB_FREXTENTS,
			nsbp->sb_rextents - sbp->sb_rextents);
		/*
		 * Update mp values पूर्णांकo the real mp काष्ठाure.
		 */
		mp->m_rsumlevels = nrsumlevels;
		mp->m_rsumsize = nrsumsize;

		error = xfs_trans_commit(tp);
		अगर (error)
			अवरोध;
	पूर्ण
	अगर (error)
		जाओ out_मुक्त;

	/* Update secondary superblocks now the physical grow has completed */
	error = xfs_update_secondary_sbs(mp);

out_मुक्त:
	/*
	 * Free the fake mp काष्ठाure.
	 */
	kmem_मुक्त(nmp);

	/*
	 * If we had to allocate a new rsum_cache, we either need to मुक्त the
	 * old one (अगर we succeeded) or मुक्त the new one and restore the old one
	 * (अगर there was an error).
	 */
	अगर (rsum_cache != mp->m_rsum_cache) अणु
		अगर (error) अणु
			kmem_मुक्त(mp->m_rsum_cache);
			mp->m_rsum_cache = rsum_cache;
		पूर्ण अन्यथा अणु
			kmem_मुक्त(rsum_cache);
		पूर्ण
	पूर्ण

	वापस error;
पूर्ण

/*
 * Allocate an extent in the realसमय subvolume, with the usual allocation
 * parameters.  The length units are all in realसमय extents, as is the
 * result block number.
 */
पूर्णांक					/* error */
xfs_rtallocate_extent(
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	xfs_rtblock_t	bno,		/* starting block number to allocate */
	xfs_extlen_t	minlen,		/* minimum length to allocate */
	xfs_extlen_t	maxlen,		/* maximum length to allocate */
	xfs_extlen_t	*len,		/* out: actual length allocated */
	पूर्णांक		wasdel,		/* was a delayed allocation extent */
	xfs_extlen_t	prod,		/* extent product factor */
	xfs_rtblock_t	*rtblock)	/* out: start block allocated */
अणु
	xfs_mount_t	*mp = tp->t_mountp;
	पूर्णांक		error;		/* error value */
	xfs_rtblock_t	r;		/* result allocated block */
	xfs_fsblock_t	sb;		/* summary file block number */
	काष्ठा xfs_buf	*sumbp;		/* summary file block buffer */

	ASSERT(xfs_isilocked(mp->m_rbmip, XFS_ILOCK_EXCL));
	ASSERT(minlen > 0 && minlen <= maxlen);

	/*
	 * If prod is set then figure out what to करो to minlen and maxlen.
	 */
	अगर (prod > 1) अणु
		xfs_extlen_t	i;

		अगर ((i = maxlen % prod))
			maxlen -= i;
		अगर ((i = minlen % prod))
			minlen += prod - i;
		अगर (maxlen < minlen) अणु
			*rtblock = शून्यRTBLOCK;
			वापस 0;
		पूर्ण
	पूर्ण

retry:
	sumbp = शून्य;
	अगर (bno == 0) अणु
		error = xfs_rtallocate_extent_size(mp, tp, minlen, maxlen, len,
				&sumbp,	&sb, prod, &r);
	पूर्ण अन्यथा अणु
		error = xfs_rtallocate_extent_near(mp, tp, bno, minlen, maxlen,
				len, &sumbp, &sb, prod, &r);
	पूर्ण

	अगर (error)
		वापस error;

	/*
	 * If it worked, update the superblock.
	 */
	अगर (r != शून्यRTBLOCK) अणु
		दीर्घ	slen = (दीर्घ)*len;

		ASSERT(*len >= minlen && *len <= maxlen);
		अगर (wasdel)
			xfs_trans_mod_sb(tp, XFS_TRANS_SB_RES_FREXTENTS, -slen);
		अन्यथा
			xfs_trans_mod_sb(tp, XFS_TRANS_SB_FREXTENTS, -slen);
	पूर्ण अन्यथा अगर (prod > 1) अणु
		prod = 1;
		जाओ retry;
	पूर्ण

	*rtblock = r;
	वापस 0;
पूर्ण

/*
 * Initialize realसमय fields in the mount काष्ठाure.
 */
पूर्णांक				/* error */
xfs_rपंचांगount_init(
	काष्ठा xfs_mount	*mp)	/* file प्रणाली mount काष्ठाure */
अणु
	काष्ठा xfs_buf		*bp;	/* buffer क्रम last block of subvolume */
	काष्ठा xfs_sb		*sbp;	/* fileप्रणाली superblock copy in mount */
	xfs_daddr_t		d;	/* address of last block of subvolume */
	पूर्णांक			error;

	sbp = &mp->m_sb;
	अगर (sbp->sb_rblocks == 0)
		वापस 0;
	अगर (mp->m_rtdev_targp == शून्य) अणु
		xfs_warn(mp,
	"Filesystem has a realtime volume, use rtdev=device option");
		वापस -ENODEV;
	पूर्ण
	mp->m_rsumlevels = sbp->sb_rextslog + 1;
	mp->m_rsumsize =
		(uपूर्णांक)माप(xfs_suminfo_t) * mp->m_rsumlevels *
		sbp->sb_rbmblocks;
	mp->m_rsumsize = roundup(mp->m_rsumsize, sbp->sb_blocksize);
	mp->m_rbmip = mp->m_rsumip = शून्य;
	/*
	 * Check that the realसमय section is an ok size.
	 */
	d = (xfs_daddr_t)XFS_FSB_TO_BB(mp, mp->m_sb.sb_rblocks);
	अगर (XFS_BB_TO_FSB(mp, d) != mp->m_sb.sb_rblocks) अणु
		xfs_warn(mp, "realtime mount -- %llu != %llu",
			(अचिन्हित दीर्घ दीर्घ) XFS_BB_TO_FSB(mp, d),
			(अचिन्हित दीर्घ दीर्घ) mp->m_sb.sb_rblocks);
		वापस -EFBIG;
	पूर्ण
	error = xfs_buf_पढ़ो_uncached(mp->m_rtdev_targp,
					d - XFS_FSB_TO_BB(mp, 1),
					XFS_FSB_TO_BB(mp, 1), 0, &bp, शून्य);
	अगर (error) अणु
		xfs_warn(mp, "realtime device size check failed");
		वापस error;
	पूर्ण
	xfs_buf_rअन्यथा(bp);
	वापस 0;
पूर्ण

/*
 * Get the biपंचांगap and summary inodes and the summary cache पूर्णांकo the mount
 * काष्ठाure at mount समय.
 */
पूर्णांक					/* error */
xfs_rपंचांगount_inodes(
	xfs_mount_t	*mp)		/* file प्रणाली mount काष्ठाure */
अणु
	पूर्णांक		error;		/* error वापस value */
	xfs_sb_t	*sbp;

	sbp = &mp->m_sb;
	error = xfs_iget(mp, शून्य, sbp->sb_rbmino, 0, 0, &mp->m_rbmip);
	अगर (error)
		वापस error;
	ASSERT(mp->m_rbmip != शून्य);

	error = xfs_iget(mp, शून्य, sbp->sb_rsumino, 0, 0, &mp->m_rsumip);
	अगर (error) अणु
		xfs_irele(mp->m_rbmip);
		वापस error;
	पूर्ण
	ASSERT(mp->m_rsumip != शून्य);
	xfs_alloc_rsum_cache(mp, sbp->sb_rbmblocks);
	वापस 0;
पूर्ण

व्योम
xfs_rtunmount_inodes(
	काष्ठा xfs_mount	*mp)
अणु
	kmem_मुक्त(mp->m_rsum_cache);
	अगर (mp->m_rbmip)
		xfs_irele(mp->m_rbmip);
	अगर (mp->m_rsumip)
		xfs_irele(mp->m_rsumip);
पूर्ण

/*
 * Pick an extent क्रम allocation at the start of a new realसमय file.
 * Use the sequence number stored in the aसमय field of the biपंचांगap inode.
 * Translate this to a fraction of the rtextents, and वापस the product
 * of rtextents and the fraction.
 * The fraction sequence is 0, 1/2, 1/4, 3/4, 1/8, ..., 7/8, 1/16, ...
 */
पूर्णांक					/* error */
xfs_rtpick_extent(
	xfs_mount_t	*mp,		/* file प्रणाली mount poपूर्णांक */
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	xfs_extlen_t	len,		/* allocation length (rtextents) */
	xfs_rtblock_t	*pick)		/* result rt extent */
अणु
	xfs_rtblock_t	b;		/* result block */
	पूर्णांक		log2;		/* log of sequence number */
	uपूर्णांक64_t	resid;		/* residual after log हटाओd */
	uपूर्णांक64_t	seq;		/* sequence number of file creation */
	uपूर्णांक64_t	*seqp;		/* poपूर्णांकer to seqno in inode */

	ASSERT(xfs_isilocked(mp->m_rbmip, XFS_ILOCK_EXCL));

	seqp = (uपूर्णांक64_t *)&VFS_I(mp->m_rbmip)->i_aसमय;
	अगर (!(mp->m_rbmip->i_dअगरlags & XFS_DIFLAG_NEWRTBM)) अणु
		mp->m_rbmip->i_dअगरlags |= XFS_DIFLAG_NEWRTBM;
		*seqp = 0;
	पूर्ण
	seq = *seqp;
	अगर ((log2 = xfs_highbit64(seq)) == -1)
		b = 0;
	अन्यथा अणु
		resid = seq - (1ULL << log2);
		b = (mp->m_sb.sb_rextents * ((resid << 1) + 1ULL)) >>
		    (log2 + 1);
		अगर (b >= mp->m_sb.sb_rextents)
			भाग64_u64_rem(b, mp->m_sb.sb_rextents, &b);
		अगर (b + len > mp->m_sb.sb_rextents)
			b = mp->m_sb.sb_rextents - len;
	पूर्ण
	*seqp = seq + 1;
	xfs_trans_log_inode(tp, mp->m_rbmip, XFS_ILOG_CORE);
	*pick = b;
	वापस 0;
पूर्ण
