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
#समावेश "xfs_trans.h"
#समावेश "xfs_rtalloc.h"
#समावेश "xfs_error.h"

/*
 * Realसमय allocator biपंचांगap functions shared with userspace.
 */

/*
 * Real समय buffers need verअगरiers to aव्योम runसमय warnings during IO.
 * We करोn't have anything to verअगरy, however, so these are just dummy
 * operations.
 */
अटल व्योम
xfs_rtbuf_verअगरy_पढ़ो(
	काष्ठा xfs_buf	*bp)
अणु
	वापस;
पूर्ण

अटल व्योम
xfs_rtbuf_verअगरy_ग_लिखो(
	काष्ठा xfs_buf	*bp)
अणु
	वापस;
पूर्ण

स्थिर काष्ठा xfs_buf_ops xfs_rtbuf_ops = अणु
	.name = "rtbuf",
	.verअगरy_पढ़ो = xfs_rtbuf_verअगरy_पढ़ो,
	.verअगरy_ग_लिखो = xfs_rtbuf_verअगरy_ग_लिखो,
पूर्ण;

/*
 * Get a buffer क्रम the biपंचांगap or summary file block specअगरied.
 * The buffer is वापसed पढ़ो and locked.
 */
पूर्णांक
xfs_rtbuf_get(
	xfs_mount_t	*mp,		/* file प्रणाली mount काष्ठाure */
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	xfs_rtblock_t	block,		/* block number in biपंचांगap or summary */
	पूर्णांक		issum,		/* is summary not biपंचांगap */
	काष्ठा xfs_buf	**bpp)		/* output: buffer क्रम the block */
अणु
	काष्ठा xfs_buf	*bp;		/* block buffer, result */
	xfs_inode_t	*ip;		/* biपंचांगap or summary inode */
	xfs_bmbt_irec_t	map;
	पूर्णांक		nmap = 1;
	पूर्णांक		error;		/* error value */

	ip = issum ? mp->m_rsumip : mp->m_rbmip;

	error = xfs_bmapi_पढ़ो(ip, block, 1, &map, &nmap, 0);
	अगर (error)
		वापस error;

	अगर (XFS_IS_CORRUPT(mp, nmap == 0 || !xfs_bmap_is_written_extent(&map)))
		वापस -EFSCORRUPTED;

	ASSERT(map.br_startblock != शून्यFSBLOCK);
	error = xfs_trans_पढ़ो_buf(mp, tp, mp->m_ddev_targp,
				   XFS_FSB_TO_DADDR(mp, map.br_startblock),
				   mp->m_bsize, 0, &bp, &xfs_rtbuf_ops);
	अगर (error)
		वापस error;

	xfs_trans_buf_set_type(tp, bp, issum ? XFS_BLFT_RTSUMMARY_BUF
					     : XFS_BLFT_RTBITMAP_BUF);
	*bpp = bp;
	वापस 0;
पूर्ण

/*
 * Searching backward from start to limit, find the first block whose
 * allocated/मुक्त state is dअगरferent from start's.
 */
पूर्णांक
xfs_rtfind_back(
	xfs_mount_t	*mp,		/* file प्रणाली mount poपूर्णांक */
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	xfs_rtblock_t	start,		/* starting block to look at */
	xfs_rtblock_t	limit,		/* last block to look at */
	xfs_rtblock_t	*rtblock)	/* out: start block found */
अणु
	xfs_rtword_t	*b;		/* current word in buffer */
	पूर्णांक		bit;		/* bit number in the word */
	xfs_rtblock_t	block;		/* biपंचांगap block number */
	काष्ठा xfs_buf	*bp;		/* buf क्रम the block */
	xfs_rtword_t	*bufp;		/* starting word in buffer */
	पूर्णांक		error;		/* error value */
	xfs_rtblock_t	firstbit;	/* first useful bit in the word */
	xfs_rtblock_t	i;		/* current bit number rel. to start */
	xfs_rtblock_t	len;		/* length of inspected area */
	xfs_rtword_t	mask;		/* mask of relevant bits क्रम value */
	xfs_rtword_t	want;		/* mask क्रम "good" values */
	xfs_rtword_t	wdअगरf;		/* dअगरference from wanted value */
	पूर्णांक		word;		/* word number in the buffer */

	/*
	 * Compute and पढ़ो in starting biपंचांगap block क्रम starting block.
	 */
	block = XFS_BITTOBLOCK(mp, start);
	error = xfs_rtbuf_get(mp, tp, block, 0, &bp);
	अगर (error) अणु
		वापस error;
	पूर्ण
	bufp = bp->b_addr;
	/*
	 * Get the first word's index & poपूर्णांक to it.
	 */
	word = XFS_BITTOWORD(mp, start);
	b = &bufp[word];
	bit = (पूर्णांक)(start & (XFS_NBWORD - 1));
	len = start - limit + 1;
	/*
	 * Compute match value, based on the bit at start: अगर 1 (मुक्त)
	 * then all-ones, अन्यथा all-zeroes.
	 */
	want = (*b & ((xfs_rtword_t)1 << bit)) ? -1 : 0;
	/*
	 * If the starting position is not word-aligned, deal with the
	 * partial word.
	 */
	अगर (bit < XFS_NBWORD - 1) अणु
		/*
		 * Calculate first (lefपंचांगost) bit number to look at,
		 * and mask क्रम all the relevant bits in this word.
		 */
		firstbit = XFS_RTMAX((xfs_srtblock_t)(bit - len + 1), 0);
		mask = (((xfs_rtword_t)1 << (bit - firstbit + 1)) - 1) <<
			firstbit;
		/*
		 * Calculate the dअगरference between the value there
		 * and what we're looking क्रम.
		 */
		अगर ((wdअगरf = (*b ^ want) & mask)) अणु
			/*
			 * Dअगरferent.  Mark where we are and वापस.
			 */
			xfs_trans_brअन्यथा(tp, bp);
			i = bit - XFS_RTHIBIT(wdअगरf);
			*rtblock = start - i + 1;
			वापस 0;
		पूर्ण
		i = bit - firstbit + 1;
		/*
		 * Go on to previous block अगर that's where the previous word is
		 * and we need the previous word.
		 */
		अगर (--word == -1 && i < len) अणु
			/*
			 * If करोne with this block, get the previous one.
			 */
			xfs_trans_brअन्यथा(tp, bp);
			error = xfs_rtbuf_get(mp, tp, --block, 0, &bp);
			अगर (error) अणु
				वापस error;
			पूर्ण
			bufp = bp->b_addr;
			word = XFS_BLOCKWMASK(mp);
			b = &bufp[word];
		पूर्ण अन्यथा अणु
			/*
			 * Go on to the previous word in the buffer.
			 */
			b--;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Starting on a word boundary, no partial word.
		 */
		i = 0;
	पूर्ण
	/*
	 * Loop over whole words in buffers.  When we use up one buffer
	 * we move on to the previous one.
	 */
	जबतक (len - i >= XFS_NBWORD) अणु
		/*
		 * Compute dअगरference between actual and desired value.
		 */
		अगर ((wdअगरf = *b ^ want)) अणु
			/*
			 * Dअगरferent, mark where we are and वापस.
			 */
			xfs_trans_brअन्यथा(tp, bp);
			i += XFS_NBWORD - 1 - XFS_RTHIBIT(wdअगरf);
			*rtblock = start - i + 1;
			वापस 0;
		पूर्ण
		i += XFS_NBWORD;
		/*
		 * Go on to previous block अगर that's where the previous word is
		 * and we need the previous word.
		 */
		अगर (--word == -1 && i < len) अणु
			/*
			 * If करोne with this block, get the previous one.
			 */
			xfs_trans_brअन्यथा(tp, bp);
			error = xfs_rtbuf_get(mp, tp, --block, 0, &bp);
			अगर (error) अणु
				वापस error;
			पूर्ण
			bufp = bp->b_addr;
			word = XFS_BLOCKWMASK(mp);
			b = &bufp[word];
		पूर्ण अन्यथा अणु
			/*
			 * Go on to the previous word in the buffer.
			 */
			b--;
		पूर्ण
	पूर्ण
	/*
	 * If not ending on a word boundary, deal with the last
	 * (partial) word.
	 */
	अगर (len - i) अणु
		/*
		 * Calculate first (lefपंचांगost) bit number to look at,
		 * and mask क्रम all the relevant bits in this word.
		 */
		firstbit = XFS_NBWORD - (len - i);
		mask = (((xfs_rtword_t)1 << (len - i)) - 1) << firstbit;
		/*
		 * Compute dअगरference between actual and desired value.
		 */
		अगर ((wdअगरf = (*b ^ want) & mask)) अणु
			/*
			 * Dअगरferent, mark where we are and वापस.
			 */
			xfs_trans_brअन्यथा(tp, bp);
			i += XFS_NBWORD - 1 - XFS_RTHIBIT(wdअगरf);
			*rtblock = start - i + 1;
			वापस 0;
		पूर्ण अन्यथा
			i = len;
	पूर्ण
	/*
	 * No match, वापस that we scanned the whole area.
	 */
	xfs_trans_brअन्यथा(tp, bp);
	*rtblock = start - i + 1;
	वापस 0;
पूर्ण

/*
 * Searching क्रमward from start to limit, find the first block whose
 * allocated/मुक्त state is dअगरferent from start's.
 */
पूर्णांक
xfs_rtfind_क्रमw(
	xfs_mount_t	*mp,		/* file प्रणाली mount poपूर्णांक */
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	xfs_rtblock_t	start,		/* starting block to look at */
	xfs_rtblock_t	limit,		/* last block to look at */
	xfs_rtblock_t	*rtblock)	/* out: start block found */
अणु
	xfs_rtword_t	*b;		/* current word in buffer */
	पूर्णांक		bit;		/* bit number in the word */
	xfs_rtblock_t	block;		/* biपंचांगap block number */
	काष्ठा xfs_buf	*bp;		/* buf क्रम the block */
	xfs_rtword_t	*bufp;		/* starting word in buffer */
	पूर्णांक		error;		/* error value */
	xfs_rtblock_t	i;		/* current bit number rel. to start */
	xfs_rtblock_t	lastbit;	/* last useful bit in the word */
	xfs_rtblock_t	len;		/* length of inspected area */
	xfs_rtword_t	mask;		/* mask of relevant bits क्रम value */
	xfs_rtword_t	want;		/* mask क्रम "good" values */
	xfs_rtword_t	wdअगरf;		/* dअगरference from wanted value */
	पूर्णांक		word;		/* word number in the buffer */

	/*
	 * Compute and पढ़ो in starting biपंचांगap block क्रम starting block.
	 */
	block = XFS_BITTOBLOCK(mp, start);
	error = xfs_rtbuf_get(mp, tp, block, 0, &bp);
	अगर (error) अणु
		वापस error;
	पूर्ण
	bufp = bp->b_addr;
	/*
	 * Get the first word's index & poपूर्णांक to it.
	 */
	word = XFS_BITTOWORD(mp, start);
	b = &bufp[word];
	bit = (पूर्णांक)(start & (XFS_NBWORD - 1));
	len = limit - start + 1;
	/*
	 * Compute match value, based on the bit at start: अगर 1 (मुक्त)
	 * then all-ones, अन्यथा all-zeroes.
	 */
	want = (*b & ((xfs_rtword_t)1 << bit)) ? -1 : 0;
	/*
	 * If the starting position is not word-aligned, deal with the
	 * partial word.
	 */
	अगर (bit) अणु
		/*
		 * Calculate last (righपंचांगost) bit number to look at,
		 * and mask क्रम all the relevant bits in this word.
		 */
		lastbit = XFS_RTMIN(bit + len, XFS_NBWORD);
		mask = (((xfs_rtword_t)1 << (lastbit - bit)) - 1) << bit;
		/*
		 * Calculate the dअगरference between the value there
		 * and what we're looking क्रम.
		 */
		अगर ((wdअगरf = (*b ^ want) & mask)) अणु
			/*
			 * Dअगरferent.  Mark where we are and वापस.
			 */
			xfs_trans_brअन्यथा(tp, bp);
			i = XFS_RTLOBIT(wdअगरf) - bit;
			*rtblock = start + i - 1;
			वापस 0;
		पूर्ण
		i = lastbit - bit;
		/*
		 * Go on to next block अगर that's where the next word is
		 * and we need the next word.
		 */
		अगर (++word == XFS_BLOCKWSIZE(mp) && i < len) अणु
			/*
			 * If करोne with this block, get the previous one.
			 */
			xfs_trans_brअन्यथा(tp, bp);
			error = xfs_rtbuf_get(mp, tp, ++block, 0, &bp);
			अगर (error) अणु
				वापस error;
			पूर्ण
			b = bufp = bp->b_addr;
			word = 0;
		पूर्ण अन्यथा अणु
			/*
			 * Go on to the previous word in the buffer.
			 */
			b++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Starting on a word boundary, no partial word.
		 */
		i = 0;
	पूर्ण
	/*
	 * Loop over whole words in buffers.  When we use up one buffer
	 * we move on to the next one.
	 */
	जबतक (len - i >= XFS_NBWORD) अणु
		/*
		 * Compute dअगरference between actual and desired value.
		 */
		अगर ((wdअगरf = *b ^ want)) अणु
			/*
			 * Dअगरferent, mark where we are and वापस.
			 */
			xfs_trans_brअन्यथा(tp, bp);
			i += XFS_RTLOBIT(wdअगरf);
			*rtblock = start + i - 1;
			वापस 0;
		पूर्ण
		i += XFS_NBWORD;
		/*
		 * Go on to next block अगर that's where the next word is
		 * and we need the next word.
		 */
		अगर (++word == XFS_BLOCKWSIZE(mp) && i < len) अणु
			/*
			 * If करोne with this block, get the next one.
			 */
			xfs_trans_brअन्यथा(tp, bp);
			error = xfs_rtbuf_get(mp, tp, ++block, 0, &bp);
			अगर (error) अणु
				वापस error;
			पूर्ण
			b = bufp = bp->b_addr;
			word = 0;
		पूर्ण अन्यथा अणु
			/*
			 * Go on to the next word in the buffer.
			 */
			b++;
		पूर्ण
	पूर्ण
	/*
	 * If not ending on a word boundary, deal with the last
	 * (partial) word.
	 */
	अगर ((lastbit = len - i)) अणु
		/*
		 * Calculate mask क्रम all the relevant bits in this word.
		 */
		mask = ((xfs_rtword_t)1 << lastbit) - 1;
		/*
		 * Compute dअगरference between actual and desired value.
		 */
		अगर ((wdअगरf = (*b ^ want) & mask)) अणु
			/*
			 * Dअगरferent, mark where we are and वापस.
			 */
			xfs_trans_brअन्यथा(tp, bp);
			i += XFS_RTLOBIT(wdअगरf);
			*rtblock = start + i - 1;
			वापस 0;
		पूर्ण अन्यथा
			i = len;
	पूर्ण
	/*
	 * No match, वापस that we scanned the whole area.
	 */
	xfs_trans_brअन्यथा(tp, bp);
	*rtblock = start + i - 1;
	वापस 0;
पूर्ण

/*
 * Read and/or modअगरy the summary inक्रमmation क्रम a given extent size,
 * biपंचांगap block combination.
 * Keeps track of a current summary block, so we करोn't keep पढ़ोing
 * it from the buffer cache.
 *
 * Summary inक्रमmation is वापसed in *sum अगर specअगरied.
 * If no delta is specअगरied, वापसs summary only.
 */
पूर्णांक
xfs_rपंचांगodअगरy_summary_पूर्णांक(
	xfs_mount_t	*mp,		/* file प्रणाली mount काष्ठाure */
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	पूर्णांक		log,		/* log2 of extent size */
	xfs_rtblock_t	bbno,		/* biपंचांगap block number */
	पूर्णांक		delta,		/* change to make to summary info */
	काष्ठा xfs_buf	**rbpp,		/* in/out: summary block buffer */
	xfs_fsblock_t	*rsb,		/* in/out: summary block number */
	xfs_suminfo_t	*sum)		/* out: summary info क्रम this block */
अणु
	काष्ठा xfs_buf	*bp;		/* buffer क्रम the summary block */
	पूर्णांक		error;		/* error value */
	xfs_fsblock_t	sb;		/* summary fsblock */
	पूर्णांक		so;		/* index पूर्णांकo the summary file */
	xfs_suminfo_t	*sp;		/* poपूर्णांकer to वापसed data */

	/*
	 * Compute entry number in the summary file.
	 */
	so = XFS_SUMOFFS(mp, log, bbno);
	/*
	 * Compute the block number in the summary file.
	 */
	sb = XFS_SUMOFFSTOBLOCK(mp, so);
	/*
	 * If we have an old buffer, and the block number matches, use that.
	 */
	अगर (*rbpp && *rsb == sb)
		bp = *rbpp;
	/*
	 * Otherwise we have to get the buffer.
	 */
	अन्यथा अणु
		/*
		 * If there was an old one, get rid of it first.
		 */
		अगर (*rbpp)
			xfs_trans_brअन्यथा(tp, *rbpp);
		error = xfs_rtbuf_get(mp, tp, sb, 1, &bp);
		अगर (error) अणु
			वापस error;
		पूर्ण
		/*
		 * Remember this buffer and block क्रम the next call.
		 */
		*rbpp = bp;
		*rsb = sb;
	पूर्ण
	/*
	 * Poपूर्णांक to the summary inक्रमmation, modअगरy/log it, and/or copy it out.
	 */
	sp = XFS_SUMPTR(mp, bp, so);
	अगर (delta) अणु
		uपूर्णांक first = (uपूर्णांक)((अक्षर *)sp - (अक्षर *)bp->b_addr);

		*sp += delta;
		अगर (mp->m_rsum_cache) अणु
			अगर (*sp == 0 && log == mp->m_rsum_cache[bbno])
				mp->m_rsum_cache[bbno]++;
			अगर (*sp != 0 && log < mp->m_rsum_cache[bbno])
				mp->m_rsum_cache[bbno] = log;
		पूर्ण
		xfs_trans_log_buf(tp, bp, first, first + माप(*sp) - 1);
	पूर्ण
	अगर (sum)
		*sum = *sp;
	वापस 0;
पूर्ण

पूर्णांक
xfs_rपंचांगodअगरy_summary(
	xfs_mount_t	*mp,		/* file प्रणाली mount काष्ठाure */
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	पूर्णांक		log,		/* log2 of extent size */
	xfs_rtblock_t	bbno,		/* biपंचांगap block number */
	पूर्णांक		delta,		/* change to make to summary info */
	काष्ठा xfs_buf	**rbpp,		/* in/out: summary block buffer */
	xfs_fsblock_t	*rsb)		/* in/out: summary block number */
अणु
	वापस xfs_rपंचांगodअगरy_summary_पूर्णांक(mp, tp, log, bbno,
					delta, rbpp, rsb, शून्य);
पूर्ण

/*
 * Set the given range of biपंचांगap bits to the given value.
 * Do whatever I/O and logging is required.
 */
पूर्णांक
xfs_rपंचांगodअगरy_range(
	xfs_mount_t	*mp,		/* file प्रणाली mount poपूर्णांक */
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	xfs_rtblock_t	start,		/* starting block to modअगरy */
	xfs_extlen_t	len,		/* length of extent to modअगरy */
	पूर्णांक		val)		/* 1 क्रम मुक्त, 0 क्रम allocated */
अणु
	xfs_rtword_t	*b;		/* current word in buffer */
	पूर्णांक		bit;		/* bit number in the word */
	xfs_rtblock_t	block;		/* biपंचांगap block number */
	काष्ठा xfs_buf	*bp;		/* buf क्रम the block */
	xfs_rtword_t	*bufp;		/* starting word in buffer */
	पूर्णांक		error;		/* error value */
	xfs_rtword_t	*first;		/* first used word in the buffer */
	पूर्णांक		i;		/* current bit number rel. to start */
	पूर्णांक		lastbit;	/* last useful bit in word */
	xfs_rtword_t	mask;		/* mask o frelevant bits क्रम value */
	पूर्णांक		word;		/* word number in the buffer */

	/*
	 * Compute starting biपंचांगap block number.
	 */
	block = XFS_BITTOBLOCK(mp, start);
	/*
	 * Read the biपंचांगap block, and poपूर्णांक to its data.
	 */
	error = xfs_rtbuf_get(mp, tp, block, 0, &bp);
	अगर (error) अणु
		वापस error;
	पूर्ण
	bufp = bp->b_addr;
	/*
	 * Compute the starting word's address, and starting bit.
	 */
	word = XFS_BITTOWORD(mp, start);
	first = b = &bufp[word];
	bit = (पूर्णांक)(start & (XFS_NBWORD - 1));
	/*
	 * 0 (allocated) => all zeroes; 1 (मुक्त) => all ones.
	 */
	val = -val;
	/*
	 * If not starting on a word boundary, deal with the first
	 * (partial) word.
	 */
	अगर (bit) अणु
		/*
		 * Compute first bit not changed and mask of relevant bits.
		 */
		lastbit = XFS_RTMIN(bit + len, XFS_NBWORD);
		mask = (((xfs_rtword_t)1 << (lastbit - bit)) - 1) << bit;
		/*
		 * Set/clear the active bits.
		 */
		अगर (val)
			*b |= mask;
		अन्यथा
			*b &= ~mask;
		i = lastbit - bit;
		/*
		 * Go on to the next block अगर that's where the next word is
		 * and we need the next word.
		 */
		अगर (++word == XFS_BLOCKWSIZE(mp) && i < len) अणु
			/*
			 * Log the changed part of this block.
			 * Get the next one.
			 */
			xfs_trans_log_buf(tp, bp,
				(uपूर्णांक)((अक्षर *)first - (अक्षर *)bufp),
				(uपूर्णांक)((अक्षर *)b - (अक्षर *)bufp));
			error = xfs_rtbuf_get(mp, tp, ++block, 0, &bp);
			अगर (error) अणु
				वापस error;
			पूर्ण
			first = b = bufp = bp->b_addr;
			word = 0;
		पूर्ण अन्यथा अणु
			/*
			 * Go on to the next word in the buffer
			 */
			b++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Starting on a word boundary, no partial word.
		 */
		i = 0;
	पूर्ण
	/*
	 * Loop over whole words in buffers.  When we use up one buffer
	 * we move on to the next one.
	 */
	जबतक (len - i >= XFS_NBWORD) अणु
		/*
		 * Set the word value correctly.
		 */
		*b = val;
		i += XFS_NBWORD;
		/*
		 * Go on to the next block अगर that's where the next word is
		 * and we need the next word.
		 */
		अगर (++word == XFS_BLOCKWSIZE(mp) && i < len) अणु
			/*
			 * Log the changed part of this block.
			 * Get the next one.
			 */
			xfs_trans_log_buf(tp, bp,
				(uपूर्णांक)((अक्षर *)first - (अक्षर *)bufp),
				(uपूर्णांक)((अक्षर *)b - (अक्षर *)bufp));
			error = xfs_rtbuf_get(mp, tp, ++block, 0, &bp);
			अगर (error) अणु
				वापस error;
			पूर्ण
			first = b = bufp = bp->b_addr;
			word = 0;
		पूर्ण अन्यथा अणु
			/*
			 * Go on to the next word in the buffer
			 */
			b++;
		पूर्ण
	पूर्ण
	/*
	 * If not ending on a word boundary, deal with the last
	 * (partial) word.
	 */
	अगर ((lastbit = len - i)) अणु
		/*
		 * Compute a mask of relevant bits.
		 */
		mask = ((xfs_rtword_t)1 << lastbit) - 1;
		/*
		 * Set/clear the active bits.
		 */
		अगर (val)
			*b |= mask;
		अन्यथा
			*b &= ~mask;
		b++;
	पूर्ण
	/*
	 * Log any reमुख्यing changed bytes.
	 */
	अगर (b > first)
		xfs_trans_log_buf(tp, bp, (uपूर्णांक)((अक्षर *)first - (अक्षर *)bufp),
			(uपूर्णांक)((अक्षर *)b - (अक्षर *)bufp - 1));
	वापस 0;
पूर्ण

/*
 * Mark an extent specअगरied by start and len मुक्तd.
 * Updates all the summary inक्रमmation as well as the biपंचांगap.
 */
पूर्णांक
xfs_rtमुक्त_range(
	xfs_mount_t	*mp,		/* file प्रणाली mount poपूर्णांक */
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	xfs_rtblock_t	start,		/* starting block to मुक्त */
	xfs_extlen_t	len,		/* length to मुक्त */
	काष्ठा xfs_buf	**rbpp,		/* in/out: summary block buffer */
	xfs_fsblock_t	*rsb)		/* in/out: summary block number */
अणु
	xfs_rtblock_t	end;		/* end of the मुक्तd extent */
	पूर्णांक		error;		/* error value */
	xfs_rtblock_t	postblock;	/* first block मुक्तd > end */
	xfs_rtblock_t	preblock;	/* first block मुक्तd < start */

	end = start + len - 1;
	/*
	 * Modअगरy the biपंचांगap to mark this extent मुक्तd.
	 */
	error = xfs_rपंचांगodअगरy_range(mp, tp, start, len, 1);
	अगर (error) अणु
		वापस error;
	पूर्ण
	/*
	 * Assume we're मुक्तing out of the middle of an allocated extent.
	 * We need to find the beginning and end of the extent so we can
	 * properly update the summary.
	 */
	error = xfs_rtfind_back(mp, tp, start, 0, &preblock);
	अगर (error) अणु
		वापस error;
	पूर्ण
	/*
	 * Find the next allocated block (end of allocated extent).
	 */
	error = xfs_rtfind_क्रमw(mp, tp, end, mp->m_sb.sb_rextents - 1,
		&postblock);
	अगर (error)
		वापस error;
	/*
	 * If there are blocks not being मुक्तd at the front of the
	 * old extent, add summary data क्रम them to be allocated.
	 */
	अगर (preblock < start) अणु
		error = xfs_rपंचांगodअगरy_summary(mp, tp,
			XFS_RTBLOCKLOG(start - preblock),
			XFS_BITTOBLOCK(mp, preblock), -1, rbpp, rsb);
		अगर (error) अणु
			वापस error;
		पूर्ण
	पूर्ण
	/*
	 * If there are blocks not being मुक्तd at the end of the
	 * old extent, add summary data क्रम them to be allocated.
	 */
	अगर (postblock > end) अणु
		error = xfs_rपंचांगodअगरy_summary(mp, tp,
			XFS_RTBLOCKLOG(postblock - end),
			XFS_BITTOBLOCK(mp, end + 1), -1, rbpp, rsb);
		अगर (error) अणु
			वापस error;
		पूर्ण
	पूर्ण
	/*
	 * Increment the summary inक्रमmation corresponding to the entire
	 * (new) मुक्त extent.
	 */
	error = xfs_rपंचांगodअगरy_summary(mp, tp,
		XFS_RTBLOCKLOG(postblock + 1 - preblock),
		XFS_BITTOBLOCK(mp, preblock), 1, rbpp, rsb);
	वापस error;
पूर्ण

/*
 * Check that the given range is either all allocated (val = 0) or
 * all मुक्त (val = 1).
 */
पूर्णांक
xfs_rtcheck_range(
	xfs_mount_t	*mp,		/* file प्रणाली mount poपूर्णांक */
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	xfs_rtblock_t	start,		/* starting block number of extent */
	xfs_extlen_t	len,		/* length of extent */
	पूर्णांक		val,		/* 1 क्रम मुक्त, 0 क्रम allocated */
	xfs_rtblock_t	*new,		/* out: first block not matching */
	पूर्णांक		*stat)		/* out: 1 क्रम matches, 0 क्रम not */
अणु
	xfs_rtword_t	*b;		/* current word in buffer */
	पूर्णांक		bit;		/* bit number in the word */
	xfs_rtblock_t	block;		/* biपंचांगap block number */
	काष्ठा xfs_buf	*bp;		/* buf क्रम the block */
	xfs_rtword_t	*bufp;		/* starting word in buffer */
	पूर्णांक		error;		/* error value */
	xfs_rtblock_t	i;		/* current bit number rel. to start */
	xfs_rtblock_t	lastbit;	/* last useful bit in word */
	xfs_rtword_t	mask;		/* mask of relevant bits क्रम value */
	xfs_rtword_t	wdअगरf;		/* dअगरference from wanted value */
	पूर्णांक		word;		/* word number in the buffer */

	/*
	 * Compute starting biपंचांगap block number
	 */
	block = XFS_BITTOBLOCK(mp, start);
	/*
	 * Read the biपंचांगap block.
	 */
	error = xfs_rtbuf_get(mp, tp, block, 0, &bp);
	अगर (error) अणु
		वापस error;
	पूर्ण
	bufp = bp->b_addr;
	/*
	 * Compute the starting word's address, and starting bit.
	 */
	word = XFS_BITTOWORD(mp, start);
	b = &bufp[word];
	bit = (पूर्णांक)(start & (XFS_NBWORD - 1));
	/*
	 * 0 (allocated) => all zero's; 1 (free) => all one's.
	 */
	val = -val;
	/*
	 * If not starting on a word boundary, deal with the first
	 * (partial) word.
	 */
	अगर (bit) अणु
		/*
		 * Compute first bit not examined.
		 */
		lastbit = XFS_RTMIN(bit + len, XFS_NBWORD);
		/*
		 * Mask of relevant bits.
		 */
		mask = (((xfs_rtword_t)1 << (lastbit - bit)) - 1) << bit;
		/*
		 * Compute dअगरference between actual and desired value.
		 */
		अगर ((wdअगरf = (*b ^ val) & mask)) अणु
			/*
			 * Dअगरferent, compute first wrong bit and वापस.
			 */
			xfs_trans_brअन्यथा(tp, bp);
			i = XFS_RTLOBIT(wdअगरf) - bit;
			*new = start + i;
			*stat = 0;
			वापस 0;
		पूर्ण
		i = lastbit - bit;
		/*
		 * Go on to next block अगर that's where the next word is
		 * and we need the next word.
		 */
		अगर (++word == XFS_BLOCKWSIZE(mp) && i < len) अणु
			/*
			 * If करोne with this block, get the next one.
			 */
			xfs_trans_brअन्यथा(tp, bp);
			error = xfs_rtbuf_get(mp, tp, ++block, 0, &bp);
			अगर (error) अणु
				वापस error;
			पूर्ण
			b = bufp = bp->b_addr;
			word = 0;
		पूर्ण अन्यथा अणु
			/*
			 * Go on to the next word in the buffer.
			 */
			b++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Starting on a word boundary, no partial word.
		 */
		i = 0;
	पूर्ण
	/*
	 * Loop over whole words in buffers.  When we use up one buffer
	 * we move on to the next one.
	 */
	जबतक (len - i >= XFS_NBWORD) अणु
		/*
		 * Compute dअगरference between actual and desired value.
		 */
		अगर ((wdअगरf = *b ^ val)) अणु
			/*
			 * Dअगरferent, compute first wrong bit and वापस.
			 */
			xfs_trans_brअन्यथा(tp, bp);
			i += XFS_RTLOBIT(wdअगरf);
			*new = start + i;
			*stat = 0;
			वापस 0;
		पूर्ण
		i += XFS_NBWORD;
		/*
		 * Go on to next block अगर that's where the next word is
		 * and we need the next word.
		 */
		अगर (++word == XFS_BLOCKWSIZE(mp) && i < len) अणु
			/*
			 * If करोne with this block, get the next one.
			 */
			xfs_trans_brअन्यथा(tp, bp);
			error = xfs_rtbuf_get(mp, tp, ++block, 0, &bp);
			अगर (error) अणु
				वापस error;
			पूर्ण
			b = bufp = bp->b_addr;
			word = 0;
		पूर्ण अन्यथा अणु
			/*
			 * Go on to the next word in the buffer.
			 */
			b++;
		पूर्ण
	पूर्ण
	/*
	 * If not ending on a word boundary, deal with the last
	 * (partial) word.
	 */
	अगर ((lastbit = len - i)) अणु
		/*
		 * Mask of relevant bits.
		 */
		mask = ((xfs_rtword_t)1 << lastbit) - 1;
		/*
		 * Compute dअगरference between actual and desired value.
		 */
		अगर ((wdअगरf = (*b ^ val) & mask)) अणु
			/*
			 * Dअगरferent, compute first wrong bit and वापस.
			 */
			xfs_trans_brअन्यथा(tp, bp);
			i += XFS_RTLOBIT(wdअगरf);
			*new = start + i;
			*stat = 0;
			वापस 0;
		पूर्ण अन्यथा
			i = len;
	पूर्ण
	/*
	 * Successful, वापस.
	 */
	xfs_trans_brअन्यथा(tp, bp);
	*new = start + i;
	*stat = 1;
	वापस 0;
पूर्ण

#अगर_घोषित DEBUG
/*
 * Check that the given extent (block range) is allocated alपढ़ोy.
 */
STATIC पूर्णांक				/* error */
xfs_rtcheck_alloc_range(
	xfs_mount_t	*mp,		/* file प्रणाली mount poपूर्णांक */
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	xfs_rtblock_t	bno,		/* starting block number of extent */
	xfs_extlen_t	len)		/* length of extent */
अणु
	xfs_rtblock_t	new;		/* dummy क्रम xfs_rtcheck_range */
	पूर्णांक		stat;
	पूर्णांक		error;

	error = xfs_rtcheck_range(mp, tp, bno, len, 0, &new, &stat);
	अगर (error)
		वापस error;
	ASSERT(stat);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा xfs_rtcheck_alloc_range(m,t,b,l)	(0)
#पूर्ण_अगर
/*
 * Free an extent in the realसमय subvolume.  Length is expressed in
 * realसमय extents, as is the block number.
 */
पूर्णांक					/* error */
xfs_rtमुक्त_extent(
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	xfs_rtblock_t	bno,		/* starting block number to मुक्त */
	xfs_extlen_t	len)		/* length of extent मुक्तd */
अणु
	पूर्णांक		error;		/* error value */
	xfs_mount_t	*mp;		/* file प्रणाली mount काष्ठाure */
	xfs_fsblock_t	sb;		/* summary file block number */
	काष्ठा xfs_buf	*sumbp = शून्य;	/* summary file block buffer */

	mp = tp->t_mountp;

	ASSERT(mp->m_rbmip->i_itemp != शून्य);
	ASSERT(xfs_isilocked(mp->m_rbmip, XFS_ILOCK_EXCL));

	error = xfs_rtcheck_alloc_range(mp, tp, bno, len);
	अगर (error)
		वापस error;

	/*
	 * Free the range of realसमय blocks.
	 */
	error = xfs_rtमुक्त_range(mp, tp, bno, len, &sumbp, &sb);
	अगर (error) अणु
		वापस error;
	पूर्ण
	/*
	 * Mark more blocks मुक्त in the superblock.
	 */
	xfs_trans_mod_sb(tp, XFS_TRANS_SB_FREXTENTS, (दीर्घ)len);
	/*
	 * If we've now मुक्तd all the blocks, reset the file sequence
	 * number to 0.
	 */
	अगर (tp->t_frextents_delta + mp->m_sb.sb_frextents ==
	    mp->m_sb.sb_rextents) अणु
		अगर (!(mp->m_rbmip->i_dअगरlags & XFS_DIFLAG_NEWRTBM))
			mp->m_rbmip->i_dअगरlags |= XFS_DIFLAG_NEWRTBM;
		*(uपूर्णांक64_t *)&VFS_I(mp->m_rbmip)->i_aसमय = 0;
		xfs_trans_log_inode(tp, mp->m_rbmip, XFS_ILOG_CORE);
	पूर्ण
	वापस 0;
पूर्ण

/* Find all the मुक्त records within a given range. */
पूर्णांक
xfs_rtalloc_query_range(
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_rtalloc_rec		*low_rec,
	काष्ठा xfs_rtalloc_rec		*high_rec,
	xfs_rtalloc_query_range_fn	fn,
	व्योम				*priv)
अणु
	काष्ठा xfs_rtalloc_rec		rec;
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	xfs_rtblock_t			rtstart;
	xfs_rtblock_t			rtend;
	पूर्णांक				is_मुक्त;
	पूर्णांक				error = 0;

	अगर (low_rec->ar_startext > high_rec->ar_startext)
		वापस -EINVAL;
	अगर (low_rec->ar_startext >= mp->m_sb.sb_rextents ||
	    low_rec->ar_startext == high_rec->ar_startext)
		वापस 0;
	high_rec->ar_startext = min(high_rec->ar_startext,
			mp->m_sb.sb_rextents - 1);

	/* Iterate the biपंचांगap, looking क्रम discrepancies. */
	rtstart = low_rec->ar_startext;
	जबतक (rtstart <= high_rec->ar_startext) अणु
		/* Is the first block मुक्त? */
		error = xfs_rtcheck_range(mp, tp, rtstart, 1, 1, &rtend,
				&is_मुक्त);
		अगर (error)
			अवरोध;

		/* How दीर्घ करोes the extent go क्रम? */
		error = xfs_rtfind_क्रमw(mp, tp, rtstart,
				high_rec->ar_startext, &rtend);
		अगर (error)
			अवरोध;

		अगर (is_मुक्त) अणु
			rec.ar_startext = rtstart;
			rec.ar_extcount = rtend - rtstart + 1;

			error = fn(tp, &rec, priv);
			अगर (error)
				अवरोध;
		पूर्ण

		rtstart = rtend + 1;
	पूर्ण

	वापस error;
पूर्ण

/* Find all the मुक्त records. */
पूर्णांक
xfs_rtalloc_query_all(
	काष्ठा xfs_trans		*tp,
	xfs_rtalloc_query_range_fn	fn,
	व्योम				*priv)
अणु
	काष्ठा xfs_rtalloc_rec		keys[2];

	keys[0].ar_startext = 0;
	keys[1].ar_startext = tp->t_mountp->m_sb.sb_rextents - 1;
	keys[0].ar_extcount = keys[1].ar_extcount = 0;

	वापस xfs_rtalloc_query_range(tp, &keys[0], &keys[1], fn, priv);
पूर्ण

/* Is the given extent all मुक्त? */
पूर्णांक
xfs_rtalloc_extent_is_मुक्त(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_trans		*tp,
	xfs_rtblock_t			start,
	xfs_extlen_t			len,
	bool				*is_मुक्त)
अणु
	xfs_rtblock_t			end;
	पूर्णांक				matches;
	पूर्णांक				error;

	error = xfs_rtcheck_range(mp, tp, start, len, 1, &end, &matches);
	अगर (error)
		वापस error;

	*is_मुक्त = matches;
	वापस 0;
पूर्ण
