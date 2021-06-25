<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2006 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_bit.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_defer.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_log.h"
#समावेश "xfs_log_priv.h"
#समावेश "xfs_log_recover.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_ialloc.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_error.h"
#समावेश "xfs_buf_item.h"

#घोषणा BLK_AVG(blk1, blk2)	((blk1+blk2) >> 1)

STATIC पूर्णांक
xlog_find_zeroed(
	काष्ठा xlog	*,
	xfs_daddr_t	*);
STATIC पूर्णांक
xlog_clear_stale_blocks(
	काष्ठा xlog	*,
	xfs_lsn_t);
#अगर defined(DEBUG)
STATIC व्योम
xlog_recover_check_summary(
	काष्ठा xlog *);
#अन्यथा
#घोषणा	xlog_recover_check_summary(log)
#पूर्ण_अगर
STATIC पूर्णांक
xlog_करो_recovery_pass(
        काष्ठा xlog *, xfs_daddr_t, xfs_daddr_t, पूर्णांक, xfs_daddr_t *);

/*
 * Sector aligned buffer routines क्रम buffer create/पढ़ो/ग_लिखो/access
 */

/*
 * Verअगरy the log-relative block number and length in basic blocks are valid क्रम
 * an operation involving the given XFS log buffer. Returns true अगर the fields
 * are valid, false otherwise.
 */
अटल अंतरभूत bool
xlog_verअगरy_bno(
	काष्ठा xlog	*log,
	xfs_daddr_t	blk_no,
	पूर्णांक		bbcount)
अणु
	अगर (blk_no < 0 || blk_no >= log->l_logBBsize)
		वापस false;
	अगर (bbcount <= 0 || (blk_no + bbcount) > log->l_logBBsize)
		वापस false;
	वापस true;
पूर्ण

/*
 * Allocate a buffer to hold log data.  The buffer needs to be able to map to
 * a range of nbblks basic blocks at any valid offset within the log.
 */
अटल अक्षर *
xlog_alloc_buffer(
	काष्ठा xlog	*log,
	पूर्णांक		nbblks)
अणु
	पूर्णांक align_mask = xfs_buftarg_dma_alignment(log->l_targ);

	/*
	 * Pass log block 0 since we करोn't have an addr yet, buffer will be
	 * verअगरied on पढ़ो.
	 */
	अगर (XFS_IS_CORRUPT(log->l_mp, !xlog_verअगरy_bno(log, 0, nbblks))) अणु
		xfs_warn(log->l_mp, "Invalid block length (0x%x) for buffer",
			nbblks);
		वापस शून्य;
	पूर्ण

	/*
	 * We करो log I/O in units of log sectors (a घातer-of-2 multiple of the
	 * basic block size), so we round up the requested size to accommodate
	 * the basic blocks required क्रम complete log sectors.
	 *
	 * In addition, the buffer may be used क्रम a non-sector-aligned block
	 * offset, in which हाल an I/O of the requested size could extend
	 * beyond the end of the buffer.  If the requested size is only 1 basic
	 * block it will never straddle a sector boundary, so this won't be an
	 * issue.  Nor will this be a problem अगर the log I/O is करोne in basic
	 * blocks (sector size 1).  But otherwise we extend the buffer by one
	 * extra log sector to ensure there's space to accommodate this
	 * possibility.
	 */
	अगर (nbblks > 1 && log->l_sectBBsize > 1)
		nbblks += log->l_sectBBsize;
	nbblks = round_up(nbblks, log->l_sectBBsize);
	वापस kmem_alloc_io(BBTOB(nbblks), align_mask, KM_MAYFAIL | KM_ZERO);
पूर्ण

/*
 * Return the address of the start of the given block number's data
 * in a log buffer.  The buffer covers a log sector-aligned region.
 */
अटल अंतरभूत अचिन्हित पूर्णांक
xlog_align(
	काष्ठा xlog	*log,
	xfs_daddr_t	blk_no)
अणु
	वापस BBTOB(blk_no & ((xfs_daddr_t)log->l_sectBBsize - 1));
पूर्ण

अटल पूर्णांक
xlog_करो_io(
	काष्ठा xlog		*log,
	xfs_daddr_t		blk_no,
	अचिन्हित पूर्णांक		nbblks,
	अक्षर			*data,
	अचिन्हित पूर्णांक		op)
अणु
	पूर्णांक			error;

	अगर (XFS_IS_CORRUPT(log->l_mp, !xlog_verअगरy_bno(log, blk_no, nbblks))) अणु
		xfs_warn(log->l_mp,
			 "Invalid log block/length (0x%llx, 0x%x) for buffer",
			 blk_no, nbblks);
		वापस -EFSCORRUPTED;
	पूर्ण

	blk_no = round_करोwn(blk_no, log->l_sectBBsize);
	nbblks = round_up(nbblks, log->l_sectBBsize);
	ASSERT(nbblks > 0);

	error = xfs_rw_bdev(log->l_targ->bt_bdev, log->l_logBBstart + blk_no,
			BBTOB(nbblks), data, op);
	अगर (error && !XFS_FORCED_SHUTDOWN(log->l_mp)) अणु
		xfs_alert(log->l_mp,
			  "log recovery %s I/O error at daddr 0x%llx len %d error %d",
			  op == REQ_OP_WRITE ? "write" : "read",
			  blk_no, nbblks, error);
	पूर्ण
	वापस error;
पूर्ण

STATIC पूर्णांक
xlog_bपढ़ो_noalign(
	काष्ठा xlog	*log,
	xfs_daddr_t	blk_no,
	पूर्णांक		nbblks,
	अक्षर		*data)
अणु
	वापस xlog_करो_io(log, blk_no, nbblks, data, REQ_OP_READ);
पूर्ण

STATIC पूर्णांक
xlog_bपढ़ो(
	काष्ठा xlog	*log,
	xfs_daddr_t	blk_no,
	पूर्णांक		nbblks,
	अक्षर		*data,
	अक्षर		**offset)
अणु
	पूर्णांक		error;

	error = xlog_करो_io(log, blk_no, nbblks, data, REQ_OP_READ);
	अगर (!error)
		*offset = data + xlog_align(log, blk_no);
	वापस error;
पूर्ण

STATIC पूर्णांक
xlog_bग_लिखो(
	काष्ठा xlog	*log,
	xfs_daddr_t	blk_no,
	पूर्णांक		nbblks,
	अक्षर		*data)
अणु
	वापस xlog_करो_io(log, blk_no, nbblks, data, REQ_OP_WRITE);
पूर्ण

#अगर_घोषित DEBUG
/*
 * dump debug superblock and log record inक्रमmation
 */
STATIC व्योम
xlog_header_check_dump(
	xfs_mount_t		*mp,
	xlog_rec_header_t	*head)
अणु
	xfs_debug(mp, "%s:  SB : uuid = %pU, fmt = %d",
		__func__, &mp->m_sb.sb_uuid, XLOG_FMT);
	xfs_debug(mp, "    log : uuid = %pU, fmt = %d",
		&head->h_fs_uuid, be32_to_cpu(head->h_fmt));
पूर्ण
#अन्यथा
#घोषणा xlog_header_check_dump(mp, head)
#पूर्ण_अगर

/*
 * check log record header क्रम recovery
 */
STATIC पूर्णांक
xlog_header_check_recover(
	xfs_mount_t		*mp,
	xlog_rec_header_t	*head)
अणु
	ASSERT(head->h_magicno == cpu_to_be32(XLOG_HEADER_MAGIC_NUM));

	/*
	 * IRIX करोesn't ग_लिखो the h_fmt field and leaves it zeroed
	 * (XLOG_FMT_UNKNOWN). This stops us from trying to recover
	 * a dirty log created in IRIX.
	 */
	अगर (XFS_IS_CORRUPT(mp, head->h_fmt != cpu_to_be32(XLOG_FMT))) अणु
		xfs_warn(mp,
	"dirty log written in incompatible format - can't recover");
		xlog_header_check_dump(mp, head);
		वापस -EFSCORRUPTED;
	पूर्ण
	अगर (XFS_IS_CORRUPT(mp, !uuid_equal(&mp->m_sb.sb_uuid,
					   &head->h_fs_uuid))) अणु
		xfs_warn(mp,
	"dirty log entry has mismatched uuid - can't recover");
		xlog_header_check_dump(mp, head);
		वापस -EFSCORRUPTED;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * पढ़ो the head block of the log and check the header
 */
STATIC पूर्णांक
xlog_header_check_mount(
	xfs_mount_t		*mp,
	xlog_rec_header_t	*head)
अणु
	ASSERT(head->h_magicno == cpu_to_be32(XLOG_HEADER_MAGIC_NUM));

	अगर (uuid_is_null(&head->h_fs_uuid)) अणु
		/*
		 * IRIX करोesn't ग_लिखो the h_fs_uuid or h_fmt fields. If
		 * h_fs_uuid is null, we assume this log was last mounted
		 * by IRIX and जारी.
		 */
		xfs_warn(mp, "null uuid in log - IRIX style log");
	पूर्ण अन्यथा अगर (XFS_IS_CORRUPT(mp, !uuid_equal(&mp->m_sb.sb_uuid,
						  &head->h_fs_uuid))) अणु
		xfs_warn(mp, "log has mismatched uuid - can't recover");
		xlog_header_check_dump(mp, head);
		वापस -EFSCORRUPTED;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This routine finds (to an approximation) the first block in the physical
 * log which contains the given cycle.  It uses a binary search algorithm.
 * Note that the algorithm can not be perfect because the disk will not
 * necessarily be perfect.
 */
STATIC पूर्णांक
xlog_find_cycle_start(
	काष्ठा xlog	*log,
	अक्षर		*buffer,
	xfs_daddr_t	first_blk,
	xfs_daddr_t	*last_blk,
	uपूर्णांक		cycle)
अणु
	अक्षर		*offset;
	xfs_daddr_t	mid_blk;
	xfs_daddr_t	end_blk;
	uपूर्णांक		mid_cycle;
	पूर्णांक		error;

	end_blk = *last_blk;
	mid_blk = BLK_AVG(first_blk, end_blk);
	जबतक (mid_blk != first_blk && mid_blk != end_blk) अणु
		error = xlog_bपढ़ो(log, mid_blk, 1, buffer, &offset);
		अगर (error)
			वापस error;
		mid_cycle = xlog_get_cycle(offset);
		अगर (mid_cycle == cycle)
			end_blk = mid_blk;   /* last_half_cycle == mid_cycle */
		अन्यथा
			first_blk = mid_blk; /* first_half_cycle == mid_cycle */
		mid_blk = BLK_AVG(first_blk, end_blk);
	पूर्ण
	ASSERT((mid_blk == first_blk && mid_blk+1 == end_blk) ||
	       (mid_blk == end_blk && mid_blk-1 == first_blk));

	*last_blk = end_blk;

	वापस 0;
पूर्ण

/*
 * Check that a range of blocks करोes not contain stop_on_cycle_no.
 * Fill in *new_blk with the block offset where such a block is
 * found, or with -1 (an invalid block number) अगर there is no such
 * block in the range.  The scan needs to occur from front to back
 * and the poपूर्णांकer पूर्णांकo the region must be updated since a later
 * routine will need to perक्रमm another test.
 */
STATIC पूर्णांक
xlog_find_verअगरy_cycle(
	काष्ठा xlog	*log,
	xfs_daddr_t	start_blk,
	पूर्णांक		nbblks,
	uपूर्णांक		stop_on_cycle_no,
	xfs_daddr_t	*new_blk)
अणु
	xfs_daddr_t	i, j;
	uपूर्णांक		cycle;
	अक्षर		*buffer;
	xfs_daddr_t	bufblks;
	अक्षर		*buf = शून्य;
	पूर्णांक		error = 0;

	/*
	 * Greedily allocate a buffer big enough to handle the full
	 * range of basic blocks we'll be examining.  If that fails,
	 * try a smaller size.  We need to be able to पढ़ो at least
	 * a log sector, or we're out of luck.
	 */
	bufblks = 1 << ffs(nbblks);
	जबतक (bufblks > log->l_logBBsize)
		bufblks >>= 1;
	जबतक (!(buffer = xlog_alloc_buffer(log, bufblks))) अणु
		bufblks >>= 1;
		अगर (bufblks < log->l_sectBBsize)
			वापस -ENOMEM;
	पूर्ण

	क्रम (i = start_blk; i < start_blk + nbblks; i += bufblks) अणु
		पूर्णांक	bcount;

		bcount = min(bufblks, (start_blk + nbblks - i));

		error = xlog_bपढ़ो(log, i, bcount, buffer, &buf);
		अगर (error)
			जाओ out;

		क्रम (j = 0; j < bcount; j++) अणु
			cycle = xlog_get_cycle(buf);
			अगर (cycle == stop_on_cycle_no) अणु
				*new_blk = i+j;
				जाओ out;
			पूर्ण

			buf += BBSIZE;
		पूर्ण
	पूर्ण

	*new_blk = -1;

out:
	kmem_मुक्त(buffer);
	वापस error;
पूर्ण

अटल अंतरभूत पूर्णांक
xlog_logrec_hblks(काष्ठा xlog *log, काष्ठा xlog_rec_header *rh)
अणु
	अगर (xfs_sb_version_haslogv2(&log->l_mp->m_sb)) अणु
		पूर्णांक	h_size = be32_to_cpu(rh->h_size);

		अगर ((be32_to_cpu(rh->h_version) & XLOG_VERSION_2) &&
		    h_size > XLOG_HEADER_CYCLE_SIZE)
			वापस DIV_ROUND_UP(h_size, XLOG_HEADER_CYCLE_SIZE);
	पूर्ण
	वापस 1;
पूर्ण

/*
 * Potentially backup over partial log record ग_लिखो.
 *
 * In the typical हाल, last_blk is the number of the block directly after
 * a good log record.  Thereक्रमe, we subtract one to get the block number
 * of the last block in the given buffer.  extra_bblks contains the number
 * of blocks we would have पढ़ो on a previous पढ़ो.  This happens when the
 * last log record is split over the end of the physical log.
 *
 * extra_bblks is the number of blocks potentially verअगरied on a previous
 * call to this routine.
 */
STATIC पूर्णांक
xlog_find_verअगरy_log_record(
	काष्ठा xlog		*log,
	xfs_daddr_t		start_blk,
	xfs_daddr_t		*last_blk,
	पूर्णांक			extra_bblks)
अणु
	xfs_daddr_t		i;
	अक्षर			*buffer;
	अक्षर			*offset = शून्य;
	xlog_rec_header_t	*head = शून्य;
	पूर्णांक			error = 0;
	पूर्णांक			smallmem = 0;
	पूर्णांक			num_blks = *last_blk - start_blk;
	पूर्णांक			xhdrs;

	ASSERT(start_blk != 0 || *last_blk != start_blk);

	buffer = xlog_alloc_buffer(log, num_blks);
	अगर (!buffer) अणु
		buffer = xlog_alloc_buffer(log, 1);
		अगर (!buffer)
			वापस -ENOMEM;
		smallmem = 1;
	पूर्ण अन्यथा अणु
		error = xlog_bपढ़ो(log, start_blk, num_blks, buffer, &offset);
		अगर (error)
			जाओ out;
		offset += ((num_blks - 1) << BBSHIFT);
	पूर्ण

	क्रम (i = (*last_blk) - 1; i >= 0; i--) अणु
		अगर (i < start_blk) अणु
			/* valid log record not found */
			xfs_warn(log->l_mp,
		"Log inconsistent (didn't find previous header)");
			ASSERT(0);
			error = -EFSCORRUPTED;
			जाओ out;
		पूर्ण

		अगर (smallmem) अणु
			error = xlog_bपढ़ो(log, i, 1, buffer, &offset);
			अगर (error)
				जाओ out;
		पूर्ण

		head = (xlog_rec_header_t *)offset;

		अगर (head->h_magicno == cpu_to_be32(XLOG_HEADER_MAGIC_NUM))
			अवरोध;

		अगर (!smallmem)
			offset -= BBSIZE;
	पूर्ण

	/*
	 * We hit the beginning of the physical log & still no header.  Return
	 * to caller.  If caller can handle a वापस of -1, then this routine
	 * will be called again क्रम the end of the physical log.
	 */
	अगर (i == -1) अणु
		error = 1;
		जाओ out;
	पूर्ण

	/*
	 * We have the final block of the good log (the first block
	 * of the log record _beक्रमe_ the head. So we check the uuid.
	 */
	अगर ((error = xlog_header_check_mount(log->l_mp, head)))
		जाओ out;

	/*
	 * We may have found a log record header beक्रमe we expected one.
	 * last_blk will be the 1st block # with a given cycle #.  We may end
	 * up पढ़ोing an entire log record.  In this हाल, we करोn't want to
	 * reset last_blk.  Only when last_blk poपूर्णांकs in the middle of a log
	 * record करो we update last_blk.
	 */
	xhdrs = xlog_logrec_hblks(log, head);

	अगर (*last_blk - i + extra_bblks !=
	    BTOBB(be32_to_cpu(head->h_len)) + xhdrs)
		*last_blk = i;

out:
	kmem_मुक्त(buffer);
	वापस error;
पूर्ण

/*
 * Head is defined to be the poपूर्णांक of the log where the next log ग_लिखो
 * could go.  This means that incomplete LR ग_लिखोs at the end are
 * eliminated when calculating the head.  We aren't guaranteed that previous
 * LR have complete transactions.  We only know that a cycle number of
 * current cycle number -1 won't be present in the log अगर we start writing
 * from our current block number.
 *
 * last_blk contains the block number of the first block with a given
 * cycle number.
 *
 * Return: zero अगर normal, non-zero अगर error.
 */
STATIC पूर्णांक
xlog_find_head(
	काष्ठा xlog	*log,
	xfs_daddr_t	*वापस_head_blk)
अणु
	अक्षर		*buffer;
	अक्षर		*offset;
	xfs_daddr_t	new_blk, first_blk, start_blk, last_blk, head_blk;
	पूर्णांक		num_scan_bblks;
	uपूर्णांक		first_half_cycle, last_half_cycle;
	uपूर्णांक		stop_on_cycle;
	पूर्णांक		error, log_bbnum = log->l_logBBsize;

	/* Is the end of the log device zeroed? */
	error = xlog_find_zeroed(log, &first_blk);
	अगर (error < 0) अणु
		xfs_warn(log->l_mp, "empty log check failed");
		वापस error;
	पूर्ण
	अगर (error == 1) अणु
		*वापस_head_blk = first_blk;

		/* Is the whole lot zeroed? */
		अगर (!first_blk) अणु
			/* Linux XFS shouldn't generate totally zeroed logs -
			 * mkfs etc ग_लिखो a dummy unmount record to a fresh
			 * log so we can store the uuid in there
			 */
			xfs_warn(log->l_mp, "totally zeroed log");
		पूर्ण

		वापस 0;
	पूर्ण

	first_blk = 0;			/* get cycle # of 1st block */
	buffer = xlog_alloc_buffer(log, 1);
	अगर (!buffer)
		वापस -ENOMEM;

	error = xlog_bपढ़ो(log, 0, 1, buffer, &offset);
	अगर (error)
		जाओ out_मुक्त_buffer;

	first_half_cycle = xlog_get_cycle(offset);

	last_blk = head_blk = log_bbnum - 1;	/* get cycle # of last block */
	error = xlog_bपढ़ो(log, last_blk, 1, buffer, &offset);
	अगर (error)
		जाओ out_मुक्त_buffer;

	last_half_cycle = xlog_get_cycle(offset);
	ASSERT(last_half_cycle != 0);

	/*
	 * If the 1st half cycle number is equal to the last half cycle number,
	 * then the entire log is stamped with the same cycle number.  In this
	 * हाल, head_blk can't be set to zero (which makes sense).  The below
	 * math करोesn't work out properly with head_blk equal to zero.  Instead,
	 * we set it to log_bbnum which is an invalid block number, but this
	 * value makes the math correct.  If head_blk करोesn't changed through
	 * all the tests below, *head_blk is set to zero at the very end rather
	 * than log_bbnum.  In a sense, log_bbnum and zero are the same block
	 * in a circular file.
	 */
	अगर (first_half_cycle == last_half_cycle) अणु
		/*
		 * In this हाल we believe that the entire log should have
		 * cycle number last_half_cycle.  We need to scan backwards
		 * from the end verअगरying that there are no holes still
		 * containing last_half_cycle - 1.  If we find such a hole,
		 * then the start of that hole will be the new head.  The
		 * simple हाल looks like
		 *        x | x ... | x - 1 | x
		 * Another हाल that fits this picture would be
		 *        x | x + 1 | x ... | x
		 * In this हाल the head really is somewhere at the end of the
		 * log, as one of the latest ग_लिखोs at the beginning was
		 * incomplete.
		 * One more हाल is
		 *        x | x + 1 | x ... | x - 1 | x
		 * This is really the combination of the above two हालs, and
		 * the head has to end up at the start of the x-1 hole at the
		 * end of the log.
		 *
		 * In the 256k log हाल, we will पढ़ो from the beginning to the
		 * end of the log and search क्रम cycle numbers equal to x-1.
		 * We करोn't worry about the x+1 blocks that we encounter,
		 * because we know that they cannot be the head since the log
		 * started with x.
		 */
		head_blk = log_bbnum;
		stop_on_cycle = last_half_cycle - 1;
	पूर्ण अन्यथा अणु
		/*
		 * In this हाल we want to find the first block with cycle
		 * number matching last_half_cycle.  We expect the log to be
		 * some variation on
		 *        x + 1 ... | x ... | x
		 * The first block with cycle number x (last_half_cycle) will
		 * be where the new head beदीर्घs.  First we करो a binary search
		 * क्रम the first occurrence of last_half_cycle.  The binary
		 * search may not be totally accurate, so then we scan back
		 * from there looking क्रम occurrences of last_half_cycle beक्रमe
		 * us.  If that backwards scan wraps around the beginning of
		 * the log, then we look क्रम occurrences of last_half_cycle - 1
		 * at the end of the log.  The हालs we're looking क्रम look
		 * like
		 *                               v binary search stopped here
		 *        x + 1 ... | x | x + 1 | x ... | x
		 *                   ^ but we want to locate this spot
		 * or
		 *        <---------> less than scan distance
		 *        x + 1 ... | x ... | x - 1 | x
		 *                           ^ we want to locate this spot
		 */
		stop_on_cycle = last_half_cycle;
		error = xlog_find_cycle_start(log, buffer, first_blk, &head_blk,
				last_half_cycle);
		अगर (error)
			जाओ out_मुक्त_buffer;
	पूर्ण

	/*
	 * Now validate the answer.  Scan back some number of maximum possible
	 * blocks and make sure each one has the expected cycle number.  The
	 * maximum is determined by the total possible amount of buffering
	 * in the in-core log.  The following number can be made tighter अगर
	 * we actually look at the block size of the fileप्रणाली.
	 */
	num_scan_bblks = min_t(पूर्णांक, log_bbnum, XLOG_TOTAL_REC_SHIFT(log));
	अगर (head_blk >= num_scan_bblks) अणु
		/*
		 * We are guaranteed that the entire check can be perक्रमmed
		 * in one buffer.
		 */
		start_blk = head_blk - num_scan_bblks;
		अगर ((error = xlog_find_verअगरy_cycle(log,
						start_blk, num_scan_bblks,
						stop_on_cycle, &new_blk)))
			जाओ out_मुक्त_buffer;
		अगर (new_blk != -1)
			head_blk = new_blk;
	पूर्ण अन्यथा अणु		/* need to पढ़ो 2 parts of log */
		/*
		 * We are going to scan backwards in the log in two parts.
		 * First we scan the physical end of the log.  In this part
		 * of the log, we are looking क्रम blocks with cycle number
		 * last_half_cycle - 1.
		 * If we find one, then we know that the log starts there, as
		 * we've found a hole that didn't get written in going around
		 * the end of the physical log.  The simple हाल क्रम this is
		 *        x + 1 ... | x ... | x - 1 | x
		 *        <---------> less than scan distance
		 * If all of the blocks at the end of the log have cycle number
		 * last_half_cycle, then we check the blocks at the start of
		 * the log looking क्रम occurrences of last_half_cycle.  If we
		 * find one, then our current estimate क्रम the location of the
		 * first occurrence of last_half_cycle is wrong and we move
		 * back to the hole we've found.  This हाल looks like
		 *        x + 1 ... | x | x + 1 | x ...
		 *                               ^ binary search stopped here
		 * Another हाल we need to handle that only occurs in 256k
		 * logs is
		 *        x + 1 ... | x ... | x+1 | x ...
		 *                   ^ binary search stops here
		 * In a 256k log, the scan at the end of the log will see the
		 * x + 1 blocks.  We need to skip past those since that is
		 * certainly not the head of the log.  By searching क्रम
		 * last_half_cycle-1 we accomplish that.
		 */
		ASSERT(head_blk <= पूर्णांक_उच्च &&
			(xfs_daddr_t) num_scan_bblks >= head_blk);
		start_blk = log_bbnum - (num_scan_bblks - head_blk);
		अगर ((error = xlog_find_verअगरy_cycle(log, start_blk,
					num_scan_bblks - (पूर्णांक)head_blk,
					(stop_on_cycle - 1), &new_blk)))
			जाओ out_मुक्त_buffer;
		अगर (new_blk != -1) अणु
			head_blk = new_blk;
			जाओ validate_head;
		पूर्ण

		/*
		 * Scan beginning of log now.  The last part of the physical
		 * log is good.  This scan needs to verअगरy that it करोesn't find
		 * the last_half_cycle.
		 */
		start_blk = 0;
		ASSERT(head_blk <= पूर्णांक_उच्च);
		अगर ((error = xlog_find_verअगरy_cycle(log,
					start_blk, (पूर्णांक)head_blk,
					stop_on_cycle, &new_blk)))
			जाओ out_मुक्त_buffer;
		अगर (new_blk != -1)
			head_blk = new_blk;
	पूर्ण

validate_head:
	/*
	 * Now we need to make sure head_blk is not poपूर्णांकing to a block in
	 * the middle of a log record.
	 */
	num_scan_bblks = XLOG_REC_SHIFT(log);
	अगर (head_blk >= num_scan_bblks) अणु
		start_blk = head_blk - num_scan_bblks; /* करोn't पढ़ो head_blk */

		/* start ptr at last block ptr beक्रमe head_blk */
		error = xlog_find_verअगरy_log_record(log, start_blk, &head_blk, 0);
		अगर (error == 1)
			error = -EIO;
		अगर (error)
			जाओ out_मुक्त_buffer;
	पूर्ण अन्यथा अणु
		start_blk = 0;
		ASSERT(head_blk <= पूर्णांक_उच्च);
		error = xlog_find_verअगरy_log_record(log, start_blk, &head_blk, 0);
		अगर (error < 0)
			जाओ out_मुक्त_buffer;
		अगर (error == 1) अणु
			/* We hit the beginning of the log during our search */
			start_blk = log_bbnum - (num_scan_bblks - head_blk);
			new_blk = log_bbnum;
			ASSERT(start_blk <= पूर्णांक_उच्च &&
				(xfs_daddr_t) log_bbnum-start_blk >= 0);
			ASSERT(head_blk <= पूर्णांक_उच्च);
			error = xlog_find_verअगरy_log_record(log, start_blk,
							&new_blk, (पूर्णांक)head_blk);
			अगर (error == 1)
				error = -EIO;
			अगर (error)
				जाओ out_मुक्त_buffer;
			अगर (new_blk != log_bbnum)
				head_blk = new_blk;
		पूर्ण अन्यथा अगर (error)
			जाओ out_मुक्त_buffer;
	पूर्ण

	kmem_मुक्त(buffer);
	अगर (head_blk == log_bbnum)
		*वापस_head_blk = 0;
	अन्यथा
		*वापस_head_blk = head_blk;
	/*
	 * When वापसing here, we have a good block number.  Bad block
	 * means that during a previous crash, we didn't have a clean अवरोध
	 * from cycle number N to cycle number N-1.  In this हाल, we need
	 * to find the first block with cycle number N-1.
	 */
	वापस 0;

out_मुक्त_buffer:
	kmem_मुक्त(buffer);
	अगर (error)
		xfs_warn(log->l_mp, "failed to find log head");
	वापस error;
पूर्ण

/*
 * Seek backwards in the log क्रम log record headers.
 *
 * Given a starting log block, walk backwards until we find the provided number
 * of records or hit the provided tail block. The वापस value is the number of
 * records encountered or a negative error code. The log block and buffer
 * poपूर्णांकer of the last record seen are वापसed in rblk and rhead respectively.
 */
STATIC पूर्णांक
xlog_rseek_logrec_hdr(
	काष्ठा xlog		*log,
	xfs_daddr_t		head_blk,
	xfs_daddr_t		tail_blk,
	पूर्णांक			count,
	अक्षर			*buffer,
	xfs_daddr_t		*rblk,
	काष्ठा xlog_rec_header	**rhead,
	bool			*wrapped)
अणु
	पूर्णांक			i;
	पूर्णांक			error;
	पूर्णांक			found = 0;
	अक्षर			*offset = शून्य;
	xfs_daddr_t		end_blk;

	*wrapped = false;

	/*
	 * Walk backwards from the head block until we hit the tail or the first
	 * block in the log.
	 */
	end_blk = head_blk > tail_blk ? tail_blk : 0;
	क्रम (i = (पूर्णांक) head_blk - 1; i >= end_blk; i--) अणु
		error = xlog_bपढ़ो(log, i, 1, buffer, &offset);
		अगर (error)
			जाओ out_error;

		अगर (*(__be32 *) offset == cpu_to_be32(XLOG_HEADER_MAGIC_NUM)) अणु
			*rblk = i;
			*rhead = (काष्ठा xlog_rec_header *) offset;
			अगर (++found == count)
				अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * If we haven't hit the tail block or the log record header count,
	 * start looking again from the end of the physical log. Note that
	 * callers can pass head == tail अगर the tail is not yet known.
	 */
	अगर (tail_blk >= head_blk && found != count) अणु
		क्रम (i = log->l_logBBsize - 1; i >= (पूर्णांक) tail_blk; i--) अणु
			error = xlog_bपढ़ो(log, i, 1, buffer, &offset);
			अगर (error)
				जाओ out_error;

			अगर (*(__be32 *)offset ==
			    cpu_to_be32(XLOG_HEADER_MAGIC_NUM)) अणु
				*wrapped = true;
				*rblk = i;
				*rhead = (काष्ठा xlog_rec_header *) offset;
				अगर (++found == count)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस found;

out_error:
	वापस error;
पूर्ण

/*
 * Seek क्रमward in the log क्रम log record headers.
 *
 * Given head and tail blocks, walk क्रमward from the tail block until we find
 * the provided number of records or hit the head block. The वापस value is the
 * number of records encountered or a negative error code. The log block and
 * buffer poपूर्णांकer of the last record seen are वापसed in rblk and rhead
 * respectively.
 */
STATIC पूर्णांक
xlog_seek_logrec_hdr(
	काष्ठा xlog		*log,
	xfs_daddr_t		head_blk,
	xfs_daddr_t		tail_blk,
	पूर्णांक			count,
	अक्षर			*buffer,
	xfs_daddr_t		*rblk,
	काष्ठा xlog_rec_header	**rhead,
	bool			*wrapped)
अणु
	पूर्णांक			i;
	पूर्णांक			error;
	पूर्णांक			found = 0;
	अक्षर			*offset = शून्य;
	xfs_daddr_t		end_blk;

	*wrapped = false;

	/*
	 * Walk क्रमward from the tail block until we hit the head or the last
	 * block in the log.
	 */
	end_blk = head_blk > tail_blk ? head_blk : log->l_logBBsize - 1;
	क्रम (i = (पूर्णांक) tail_blk; i <= end_blk; i++) अणु
		error = xlog_bपढ़ो(log, i, 1, buffer, &offset);
		अगर (error)
			जाओ out_error;

		अगर (*(__be32 *) offset == cpu_to_be32(XLOG_HEADER_MAGIC_NUM)) अणु
			*rblk = i;
			*rhead = (काष्ठा xlog_rec_header *) offset;
			अगर (++found == count)
				अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * If we haven't hit the head block or the log record header count,
	 * start looking again from the start of the physical log.
	 */
	अगर (tail_blk > head_blk && found != count) अणु
		क्रम (i = 0; i < (पूर्णांक) head_blk; i++) अणु
			error = xlog_bपढ़ो(log, i, 1, buffer, &offset);
			अगर (error)
				जाओ out_error;

			अगर (*(__be32 *)offset ==
			    cpu_to_be32(XLOG_HEADER_MAGIC_NUM)) अणु
				*wrapped = true;
				*rblk = i;
				*rhead = (काष्ठा xlog_rec_header *) offset;
				अगर (++found == count)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस found;

out_error:
	वापस error;
पूर्ण

/*
 * Calculate distance from head to tail (i.e., unused space in the log).
 */
अटल अंतरभूत पूर्णांक
xlog_tail_distance(
	काष्ठा xlog	*log,
	xfs_daddr_t	head_blk,
	xfs_daddr_t	tail_blk)
अणु
	अगर (head_blk < tail_blk)
		वापस tail_blk - head_blk;

	वापस tail_blk + (log->l_logBBsize - head_blk);
पूर्ण

/*
 * Verअगरy the log tail. This is particularly important when torn or incomplete
 * ग_लिखोs have been detected near the front of the log and the head has been
 * walked back accordingly.
 *
 * We also have to handle the हाल where the tail was pinned and the head
 * blocked behind the tail right beक्रमe a crash. If the tail had been pushed
 * immediately prior to the crash and the subsequent checkpoपूर्णांक was only
 * partially written, it's possible it overwrote the last referenced tail in the
 * log with garbage. This is not a coherency problem because the tail must have
 * been pushed beक्रमe it can be overwritten, but appears as log corruption to
 * recovery because we have no way to know the tail was updated अगर the
 * subsequent checkpoपूर्णांक didn't ग_लिखो successfully.
 *
 * Thereक्रमe, CRC check the log from tail to head. If a failure occurs and the
 * offending record is within max iclog bufs from the head, walk the tail
 * क्रमward and retry until a valid tail is found or corruption is detected out
 * of the range of a possible overग_लिखो.
 */
STATIC पूर्णांक
xlog_verअगरy_tail(
	काष्ठा xlog		*log,
	xfs_daddr_t		head_blk,
	xfs_daddr_t		*tail_blk,
	पूर्णांक			hsize)
अणु
	काष्ठा xlog_rec_header	*thead;
	अक्षर			*buffer;
	xfs_daddr_t		first_bad;
	पूर्णांक			error = 0;
	bool			wrapped;
	xfs_daddr_t		पंचांगp_tail;
	xfs_daddr_t		orig_tail = *tail_blk;

	buffer = xlog_alloc_buffer(log, 1);
	अगर (!buffer)
		वापस -ENOMEM;

	/*
	 * Make sure the tail poपूर्णांकs to a record (वापसs positive count on
	 * success).
	 */
	error = xlog_seek_logrec_hdr(log, head_blk, *tail_blk, 1, buffer,
			&पंचांगp_tail, &thead, &wrapped);
	अगर (error < 0)
		जाओ out;
	अगर (*tail_blk != पंचांगp_tail)
		*tail_blk = पंचांगp_tail;

	/*
	 * Run a CRC check from the tail to the head. We can't just check
	 * MAX_ICLOGS records past the tail because the tail may poपूर्णांक to stale
	 * blocks cleared during the search क्रम the head/tail. These blocks are
	 * overwritten with zero-length records and thus record count is not a
	 * reliable indicator of the iclog state beक्रमe a crash.
	 */
	first_bad = 0;
	error = xlog_करो_recovery_pass(log, head_blk, *tail_blk,
				      XLOG_RECOVER_CRCPASS, &first_bad);
	जबतक ((error == -EFSBADCRC || error == -EFSCORRUPTED) && first_bad) अणु
		पूर्णांक	tail_distance;

		/*
		 * Is corruption within range of the head? If so, retry from
		 * the next record. Otherwise वापस an error.
		 */
		tail_distance = xlog_tail_distance(log, head_blk, first_bad);
		अगर (tail_distance > BTOBB(XLOG_MAX_ICLOGS * hsize))
			अवरोध;

		/* skip to the next record; वापसs positive count on success */
		error = xlog_seek_logrec_hdr(log, head_blk, first_bad, 2,
				buffer, &पंचांगp_tail, &thead, &wrapped);
		अगर (error < 0)
			जाओ out;

		*tail_blk = पंचांगp_tail;
		first_bad = 0;
		error = xlog_करो_recovery_pass(log, head_blk, *tail_blk,
					      XLOG_RECOVER_CRCPASS, &first_bad);
	पूर्ण

	अगर (!error && *tail_blk != orig_tail)
		xfs_warn(log->l_mp,
		"Tail block (0x%llx) overwrite detected. Updated to 0x%llx",
			 orig_tail, *tail_blk);
out:
	kmem_मुक्त(buffer);
	वापस error;
पूर्ण

/*
 * Detect and trim torn ग_लिखोs from the head of the log.
 *
 * Storage without sector atomicity guarantees can result in torn ग_लिखोs in the
 * log in the event of a crash. Our only means to detect this scenario is via
 * CRC verअगरication. While we can't always be certain that CRC verअगरication
 * failure is due to a torn ग_लिखो vs. an unrelated corruption, we करो know that
 * only a certain number (XLOG_MAX_ICLOGS) of log records can be written out at
 * one समय. Thereक्रमe, CRC verअगरy up to XLOG_MAX_ICLOGS records at the head of
 * the log and treat failures in this range as torn ग_लिखोs as a matter of
 * policy. In the event of CRC failure, the head is walked back to the last good
 * record in the log and the tail is updated from that record and verअगरied.
 */
STATIC पूर्णांक
xlog_verअगरy_head(
	काष्ठा xlog		*log,
	xfs_daddr_t		*head_blk,	/* in/out: unverअगरied head */
	xfs_daddr_t		*tail_blk,	/* out: tail block */
	अक्षर			*buffer,
	xfs_daddr_t		*rhead_blk,	/* start blk of last record */
	काष्ठा xlog_rec_header	**rhead,	/* ptr to last record */
	bool			*wrapped)	/* last rec. wraps phys. log */
अणु
	काष्ठा xlog_rec_header	*पंचांगp_rhead;
	अक्षर			*पंचांगp_buffer;
	xfs_daddr_t		first_bad;
	xfs_daddr_t		पंचांगp_rhead_blk;
	पूर्णांक			found;
	पूर्णांक			error;
	bool			पंचांगp_wrapped;

	/*
	 * Check the head of the log क्रम torn ग_लिखोs. Search backwards from the
	 * head until we hit the tail or the maximum number of log record I/Os
	 * that could have been in flight at one समय. Use a temporary buffer so
	 * we करोn't trash the rhead/buffer poपूर्णांकers from the caller.
	 */
	पंचांगp_buffer = xlog_alloc_buffer(log, 1);
	अगर (!पंचांगp_buffer)
		वापस -ENOMEM;
	error = xlog_rseek_logrec_hdr(log, *head_blk, *tail_blk,
				      XLOG_MAX_ICLOGS, पंचांगp_buffer,
				      &पंचांगp_rhead_blk, &पंचांगp_rhead, &पंचांगp_wrapped);
	kmem_मुक्त(पंचांगp_buffer);
	अगर (error < 0)
		वापस error;

	/*
	 * Now run a CRC verअगरication pass over the records starting at the
	 * block found above to the current head. If a CRC failure occurs, the
	 * log block of the first bad record is saved in first_bad.
	 */
	error = xlog_करो_recovery_pass(log, *head_blk, पंचांगp_rhead_blk,
				      XLOG_RECOVER_CRCPASS, &first_bad);
	अगर ((error == -EFSBADCRC || error == -EFSCORRUPTED) && first_bad) अणु
		/*
		 * We've hit a potential torn ग_लिखो. Reset the error and warn
		 * about it.
		 */
		error = 0;
		xfs_warn(log->l_mp,
"Torn write (CRC failure) detected at log block 0x%llx. Truncating head block from 0x%llx.",
			 first_bad, *head_blk);

		/*
		 * Get the header block and buffer poपूर्णांकer क्रम the last good
		 * record beक्रमe the bad record.
		 *
		 * Note that xlog_find_tail() clears the blocks at the new head
		 * (i.e., the records with invalid CRC) अगर the cycle number
		 * matches the current cycle.
		 */
		found = xlog_rseek_logrec_hdr(log, first_bad, *tail_blk, 1,
				buffer, rhead_blk, rhead, wrapped);
		अगर (found < 0)
			वापस found;
		अगर (found == 0)		/* XXX: right thing to करो here? */
			वापस -EIO;

		/*
		 * Reset the head block to the starting block of the first bad
		 * log record and set the tail block based on the last good
		 * record.
		 *
		 * Bail out अगर the updated head/tail match as this indicates
		 * possible corruption outside of the acceptable
		 * (XLOG_MAX_ICLOGS) range. This is a job क्रम xfs_repair...
		 */
		*head_blk = first_bad;
		*tail_blk = BLOCK_LSN(be64_to_cpu((*rhead)->h_tail_lsn));
		अगर (*head_blk == *tail_blk) अणु
			ASSERT(0);
			वापस 0;
		पूर्ण
	पूर्ण
	अगर (error)
		वापस error;

	वापस xlog_verअगरy_tail(log, *head_blk, tail_blk,
				be32_to_cpu((*rhead)->h_size));
पूर्ण

/*
 * We need to make sure we handle log wrapping properly, so we can't use the
 * calculated logbno directly. Make sure it wraps to the correct bno inside the
 * log.
 *
 * The log is limited to 32 bit sizes, so we use the appropriate modulus
 * operation here and cast it back to a 64 bit daddr on वापस.
 */
अटल अंतरभूत xfs_daddr_t
xlog_wrap_logbno(
	काष्ठा xlog		*log,
	xfs_daddr_t		bno)
अणु
	पूर्णांक			mod;

	भाग_s64_rem(bno, log->l_logBBsize, &mod);
	वापस mod;
पूर्ण

/*
 * Check whether the head of the log poपूर्णांकs to an unmount record. In other
 * words, determine whether the log is clean. If so, update the in-core state
 * appropriately.
 */
अटल पूर्णांक
xlog_check_unmount_rec(
	काष्ठा xlog		*log,
	xfs_daddr_t		*head_blk,
	xfs_daddr_t		*tail_blk,
	काष्ठा xlog_rec_header	*rhead,
	xfs_daddr_t		rhead_blk,
	अक्षर			*buffer,
	bool			*clean)
अणु
	काष्ठा xlog_op_header	*op_head;
	xfs_daddr_t		umount_data_blk;
	xfs_daddr_t		after_umount_blk;
	पूर्णांक			hblks;
	पूर्णांक			error;
	अक्षर			*offset;

	*clean = false;

	/*
	 * Look क्रम unmount record. If we find it, then we know there was a
	 * clean unmount. Since 'i' could be the last block in the physical
	 * log, we convert to a log block beक्रमe comparing to the head_blk.
	 *
	 * Save the current tail lsn to use to pass to xlog_clear_stale_blocks()
	 * below. We won't want to clear the unmount record अगर there is one, so
	 * we pass the lsn of the unmount record rather than the block after it.
	 */
	hblks = xlog_logrec_hblks(log, rhead);
	after_umount_blk = xlog_wrap_logbno(log,
			rhead_blk + hblks + BTOBB(be32_to_cpu(rhead->h_len)));

	अगर (*head_blk == after_umount_blk &&
	    be32_to_cpu(rhead->h_num_logops) == 1) अणु
		umount_data_blk = xlog_wrap_logbno(log, rhead_blk + hblks);
		error = xlog_bपढ़ो(log, umount_data_blk, 1, buffer, &offset);
		अगर (error)
			वापस error;

		op_head = (काष्ठा xlog_op_header *)offset;
		अगर (op_head->oh_flags & XLOG_UNMOUNT_TRANS) अणु
			/*
			 * Set tail and last sync so that newly written log
			 * records will poपूर्णांक recovery to after the current
			 * unmount record.
			 */
			xlog_assign_atomic_lsn(&log->l_tail_lsn,
					log->l_curr_cycle, after_umount_blk);
			xlog_assign_atomic_lsn(&log->l_last_sync_lsn,
					log->l_curr_cycle, after_umount_blk);
			*tail_blk = after_umount_blk;

			*clean = true;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
xlog_set_state(
	काष्ठा xlog		*log,
	xfs_daddr_t		head_blk,
	काष्ठा xlog_rec_header	*rhead,
	xfs_daddr_t		rhead_blk,
	bool			bump_cycle)
अणु
	/*
	 * Reset log values according to the state of the log when we
	 * crashed.  In the हाल where head_blk == 0, we bump curr_cycle
	 * one because the next ग_लिखो starts a new cycle rather than
	 * continuing the cycle of the last good log record.  At this
	 * poपूर्णांक we have guaranteed that all partial log records have been
	 * accounted क्रम.  Thereक्रमe, we know that the last good log record
	 * written was complete and ended exactly on the end boundary
	 * of the physical log.
	 */
	log->l_prev_block = rhead_blk;
	log->l_curr_block = (पूर्णांक)head_blk;
	log->l_curr_cycle = be32_to_cpu(rhead->h_cycle);
	अगर (bump_cycle)
		log->l_curr_cycle++;
	atomic64_set(&log->l_tail_lsn, be64_to_cpu(rhead->h_tail_lsn));
	atomic64_set(&log->l_last_sync_lsn, be64_to_cpu(rhead->h_lsn));
	xlog_assign_grant_head(&log->l_reserve_head.grant, log->l_curr_cycle,
					BBTOB(log->l_curr_block));
	xlog_assign_grant_head(&log->l_ग_लिखो_head.grant, log->l_curr_cycle,
					BBTOB(log->l_curr_block));
पूर्ण

/*
 * Find the sync block number or the tail of the log.
 *
 * This will be the block number of the last record to have its
 * associated buffers synced to disk.  Every log record header has
 * a sync lsn embedded in it.  LSNs hold block numbers, so it is easy
 * to get a sync block number.  The only concern is to figure out which
 * log record header to believe.
 *
 * The following algorithm uses the log record header with the largest
 * lsn.  The entire log record करोes not need to be valid.  We only care
 * that the header is valid.
 *
 * We could speed up search by using current head_blk buffer, but it is not
 * available.
 */
STATIC पूर्णांक
xlog_find_tail(
	काष्ठा xlog		*log,
	xfs_daddr_t		*head_blk,
	xfs_daddr_t		*tail_blk)
अणु
	xlog_rec_header_t	*rhead;
	अक्षर			*offset = शून्य;
	अक्षर			*buffer;
	पूर्णांक			error;
	xfs_daddr_t		rhead_blk;
	xfs_lsn_t		tail_lsn;
	bool			wrapped = false;
	bool			clean = false;

	/*
	 * Find previous log record
	 */
	अगर ((error = xlog_find_head(log, head_blk)))
		वापस error;
	ASSERT(*head_blk < पूर्णांक_उच्च);

	buffer = xlog_alloc_buffer(log, 1);
	अगर (!buffer)
		वापस -ENOMEM;
	अगर (*head_blk == 0) अणु				/* special हाल */
		error = xlog_bपढ़ो(log, 0, 1, buffer, &offset);
		अगर (error)
			जाओ करोne;

		अगर (xlog_get_cycle(offset) == 0) अणु
			*tail_blk = 0;
			/* leave all other log inited values alone */
			जाओ करोne;
		पूर्ण
	पूर्ण

	/*
	 * Search backwards through the log looking क्रम the log record header
	 * block. This wraps all the way back around to the head so something is
	 * seriously wrong अगर we can't find it.
	 */
	error = xlog_rseek_logrec_hdr(log, *head_blk, *head_blk, 1, buffer,
				      &rhead_blk, &rhead, &wrapped);
	अगर (error < 0)
		जाओ करोne;
	अगर (!error) अणु
		xfs_warn(log->l_mp, "%s: couldn't find sync record", __func__);
		error = -EFSCORRUPTED;
		जाओ करोne;
	पूर्ण
	*tail_blk = BLOCK_LSN(be64_to_cpu(rhead->h_tail_lsn));

	/*
	 * Set the log state based on the current head record.
	 */
	xlog_set_state(log, *head_blk, rhead, rhead_blk, wrapped);
	tail_lsn = atomic64_पढ़ो(&log->l_tail_lsn);

	/*
	 * Look क्रम an unmount record at the head of the log. This sets the log
	 * state to determine whether recovery is necessary.
	 */
	error = xlog_check_unmount_rec(log, head_blk, tail_blk, rhead,
				       rhead_blk, buffer, &clean);
	अगर (error)
		जाओ करोne;

	/*
	 * Verअगरy the log head अगर the log is not clean (e.g., we have anything
	 * but an unmount record at the head). This uses CRC verअगरication to
	 * detect and trim torn ग_लिखोs. If discovered, CRC failures are
	 * considered torn ग_लिखोs and the log head is trimmed accordingly.
	 *
	 * Note that we can only run CRC verअगरication when the log is dirty
	 * because there's no guarantee that the log data behind an unmount
	 * record is compatible with the current architecture.
	 */
	अगर (!clean) अणु
		xfs_daddr_t	orig_head = *head_blk;

		error = xlog_verअगरy_head(log, head_blk, tail_blk, buffer,
					 &rhead_blk, &rhead, &wrapped);
		अगर (error)
			जाओ करोne;

		/* update in-core state again अगर the head changed */
		अगर (*head_blk != orig_head) अणु
			xlog_set_state(log, *head_blk, rhead, rhead_blk,
				       wrapped);
			tail_lsn = atomic64_पढ़ो(&log->l_tail_lsn);
			error = xlog_check_unmount_rec(log, head_blk, tail_blk,
						       rhead, rhead_blk, buffer,
						       &clean);
			अगर (error)
				जाओ करोne;
		पूर्ण
	पूर्ण

	/*
	 * Note that the unmount was clean. If the unmount was not clean, we
	 * need to know this to rebuild the superblock counters from the perag
	 * headers अगर we have a fileप्रणाली using non-persistent counters.
	 */
	अगर (clean)
		log->l_mp->m_flags |= XFS_MOUNT_WAS_CLEAN;

	/*
	 * Make sure that there are no blocks in front of the head
	 * with the same cycle number as the head.  This can happen
	 * because we allow multiple outstanding log ग_लिखोs concurrently,
	 * and the later ग_लिखोs might make it out beक्रमe earlier ones.
	 *
	 * We use the lsn from beक्रमe modअगरying it so that we'll never
	 * overग_लिखो the unmount record after a clean unmount.
	 *
	 * Do this only अगर we are going to recover the fileप्रणाली
	 *
	 * NOTE: This used to say "if (!readonly)"
	 * However on Linux, we can & करो recover a पढ़ो-only fileप्रणाली.
	 * We only skip recovery अगर NORECOVERY is specअगरied on mount,
	 * in which हाल we would not be here.
	 *
	 * But... अगर the -device- itself is पढ़ोonly, just skip this.
	 * We can't recover this device anyway, so it won't matter.
	 */
	अगर (!xfs_पढ़ोonly_buftarg(log->l_targ))
		error = xlog_clear_stale_blocks(log, tail_lsn);

करोne:
	kmem_मुक्त(buffer);

	अगर (error)
		xfs_warn(log->l_mp, "failed to locate log tail");
	वापस error;
पूर्ण

/*
 * Is the log zeroed at all?
 *
 * The last binary search should be changed to perक्रमm an X block पढ़ो
 * once X becomes small enough.  You can then search linearly through
 * the X blocks.  This will cut करोwn on the number of पढ़ोs we need to करो.
 *
 * If the log is partially zeroed, this routine will pass back the blkno
 * of the first block with cycle number 0.  It won't have a complete LR
 * preceding it.
 *
 * Return:
 *	0  => the log is completely written to
 *	1 => use *blk_no as the first block of the log
 *	<0 => error has occurred
 */
STATIC पूर्णांक
xlog_find_zeroed(
	काष्ठा xlog	*log,
	xfs_daddr_t	*blk_no)
अणु
	अक्षर		*buffer;
	अक्षर		*offset;
	uपूर्णांक	        first_cycle, last_cycle;
	xfs_daddr_t	new_blk, last_blk, start_blk;
	xfs_daddr_t     num_scan_bblks;
	पूर्णांक	        error, log_bbnum = log->l_logBBsize;

	*blk_no = 0;

	/* check totally zeroed log */
	buffer = xlog_alloc_buffer(log, 1);
	अगर (!buffer)
		वापस -ENOMEM;
	error = xlog_bपढ़ो(log, 0, 1, buffer, &offset);
	अगर (error)
		जाओ out_मुक्त_buffer;

	first_cycle = xlog_get_cycle(offset);
	अगर (first_cycle == 0) अणु		/* completely zeroed log */
		*blk_no = 0;
		kmem_मुक्त(buffer);
		वापस 1;
	पूर्ण

	/* check partially zeroed log */
	error = xlog_bपढ़ो(log, log_bbnum-1, 1, buffer, &offset);
	अगर (error)
		जाओ out_मुक्त_buffer;

	last_cycle = xlog_get_cycle(offset);
	अगर (last_cycle != 0) अणु		/* log completely written to */
		kmem_मुक्त(buffer);
		वापस 0;
	पूर्ण

	/* we have a partially zeroed log */
	last_blk = log_bbnum-1;
	error = xlog_find_cycle_start(log, buffer, 0, &last_blk, 0);
	अगर (error)
		जाओ out_मुक्त_buffer;

	/*
	 * Validate the answer.  Because there is no way to guarantee that
	 * the entire log is made up of log records which are the same size,
	 * we scan over the defined maximum blocks.  At this poपूर्णांक, the maximum
	 * is not chosen to mean anything special.   XXXmiken
	 */
	num_scan_bblks = XLOG_TOTAL_REC_SHIFT(log);
	ASSERT(num_scan_bblks <= पूर्णांक_उच्च);

	अगर (last_blk < num_scan_bblks)
		num_scan_bblks = last_blk;
	start_blk = last_blk - num_scan_bblks;

	/*
	 * We search क्रम any instances of cycle number 0 that occur beक्रमe
	 * our current estimate of the head.  What we're trying to detect is
	 *        1 ... | 0 | 1 | 0...
	 *                       ^ binary search ends here
	 */
	अगर ((error = xlog_find_verअगरy_cycle(log, start_blk,
					 (पूर्णांक)num_scan_bblks, 0, &new_blk)))
		जाओ out_मुक्त_buffer;
	अगर (new_blk != -1)
		last_blk = new_blk;

	/*
	 * Potentially backup over partial log record ग_लिखो.  We करोn't need
	 * to search the end of the log because we know it is zero.
	 */
	error = xlog_find_verअगरy_log_record(log, start_blk, &last_blk, 0);
	अगर (error == 1)
		error = -EIO;
	अगर (error)
		जाओ out_मुक्त_buffer;

	*blk_no = last_blk;
out_मुक्त_buffer:
	kmem_मुक्त(buffer);
	अगर (error)
		वापस error;
	वापस 1;
पूर्ण

/*
 * These are simple subroutines used by xlog_clear_stale_blocks() below
 * to initialize a buffer full of empty log record headers and ग_लिखो
 * them पूर्णांकo the log.
 */
STATIC व्योम
xlog_add_record(
	काष्ठा xlog		*log,
	अक्षर			*buf,
	पूर्णांक			cycle,
	पूर्णांक			block,
	पूर्णांक			tail_cycle,
	पूर्णांक			tail_block)
अणु
	xlog_rec_header_t	*recp = (xlog_rec_header_t *)buf;

	स_रखो(buf, 0, BBSIZE);
	recp->h_magicno = cpu_to_be32(XLOG_HEADER_MAGIC_NUM);
	recp->h_cycle = cpu_to_be32(cycle);
	recp->h_version = cpu_to_be32(
			xfs_sb_version_haslogv2(&log->l_mp->m_sb) ? 2 : 1);
	recp->h_lsn = cpu_to_be64(xlog_assign_lsn(cycle, block));
	recp->h_tail_lsn = cpu_to_be64(xlog_assign_lsn(tail_cycle, tail_block));
	recp->h_fmt = cpu_to_be32(XLOG_FMT);
	स_नकल(&recp->h_fs_uuid, &log->l_mp->m_sb.sb_uuid, माप(uuid_t));
पूर्ण

STATIC पूर्णांक
xlog_ग_लिखो_log_records(
	काष्ठा xlog	*log,
	पूर्णांक		cycle,
	पूर्णांक		start_block,
	पूर्णांक		blocks,
	पूर्णांक		tail_cycle,
	पूर्णांक		tail_block)
अणु
	अक्षर		*offset;
	अक्षर		*buffer;
	पूर्णांक		balign, ealign;
	पूर्णांक		sectbb = log->l_sectBBsize;
	पूर्णांक		end_block = start_block + blocks;
	पूर्णांक		bufblks;
	पूर्णांक		error = 0;
	पूर्णांक		i, j = 0;

	/*
	 * Greedily allocate a buffer big enough to handle the full
	 * range of basic blocks to be written.  If that fails, try
	 * a smaller size.  We need to be able to ग_लिखो at least a
	 * log sector, or we're out of luck.
	 */
	bufblks = 1 << ffs(blocks);
	जबतक (bufblks > log->l_logBBsize)
		bufblks >>= 1;
	जबतक (!(buffer = xlog_alloc_buffer(log, bufblks))) अणु
		bufblks >>= 1;
		अगर (bufblks < sectbb)
			वापस -ENOMEM;
	पूर्ण

	/* We may need to करो a पढ़ो at the start to fill in part of
	 * the buffer in the starting sector not covered by the first
	 * ग_लिखो below.
	 */
	balign = round_करोwn(start_block, sectbb);
	अगर (balign != start_block) अणु
		error = xlog_bपढ़ो_noalign(log, start_block, 1, buffer);
		अगर (error)
			जाओ out_मुक्त_buffer;

		j = start_block - balign;
	पूर्ण

	क्रम (i = start_block; i < end_block; i += bufblks) अणु
		पूर्णांक		bcount, endcount;

		bcount = min(bufblks, end_block - start_block);
		endcount = bcount - j;

		/* We may need to करो a पढ़ो at the end to fill in part of
		 * the buffer in the final sector not covered by the ग_लिखो.
		 * If this is the same sector as the above पढ़ो, skip it.
		 */
		ealign = round_करोwn(end_block, sectbb);
		अगर (j == 0 && (start_block + endcount > ealign)) अणु
			error = xlog_bपढ़ो_noalign(log, ealign, sectbb,
					buffer + BBTOB(ealign - start_block));
			अगर (error)
				अवरोध;

		पूर्ण

		offset = buffer + xlog_align(log, start_block);
		क्रम (; j < endcount; j++) अणु
			xlog_add_record(log, offset, cycle, i+j,
					tail_cycle, tail_block);
			offset += BBSIZE;
		पूर्ण
		error = xlog_bग_लिखो(log, start_block, endcount, buffer);
		अगर (error)
			अवरोध;
		start_block += endcount;
		j = 0;
	पूर्ण

out_मुक्त_buffer:
	kmem_मुक्त(buffer);
	वापस error;
पूर्ण

/*
 * This routine is called to blow away any incomplete log ग_लिखोs out
 * in front of the log head.  We करो this so that we won't become confused
 * अगर we come up, ग_लिखो only a little bit more, and then crash again.
 * If we leave the partial log records out there, this situation could
 * cause us to think those partial ग_लिखोs are valid blocks since they
 * have the current cycle number.  We get rid of them by overwriting them
 * with empty log records with the old cycle number rather than the
 * current one.
 *
 * The tail lsn is passed in rather than taken from
 * the log so that we will not ग_लिखो over the unmount record after a
 * clean unmount in a 512 block log.  Doing so would leave the log without
 * any valid log records in it until a new one was written.  If we crashed
 * during that समय we would not be able to recover.
 */
STATIC पूर्णांक
xlog_clear_stale_blocks(
	काष्ठा xlog	*log,
	xfs_lsn_t	tail_lsn)
अणु
	पूर्णांक		tail_cycle, head_cycle;
	पूर्णांक		tail_block, head_block;
	पूर्णांक		tail_distance, max_distance;
	पूर्णांक		distance;
	पूर्णांक		error;

	tail_cycle = CYCLE_LSN(tail_lsn);
	tail_block = BLOCK_LSN(tail_lsn);
	head_cycle = log->l_curr_cycle;
	head_block = log->l_curr_block;

	/*
	 * Figure out the distance between the new head of the log
	 * and the tail.  We want to ग_लिखो over any blocks beyond the
	 * head that we may have written just beक्रमe the crash, but
	 * we करोn't want to overग_लिखो the tail of the log.
	 */
	अगर (head_cycle == tail_cycle) अणु
		/*
		 * The tail is behind the head in the physical log,
		 * so the distance from the head to the tail is the
		 * distance from the head to the end of the log plus
		 * the distance from the beginning of the log to the
		 * tail.
		 */
		अगर (XFS_IS_CORRUPT(log->l_mp,
				   head_block < tail_block ||
				   head_block >= log->l_logBBsize))
			वापस -EFSCORRUPTED;
		tail_distance = tail_block + (log->l_logBBsize - head_block);
	पूर्ण अन्यथा अणु
		/*
		 * The head is behind the tail in the physical log,
		 * so the distance from the head to the tail is just
		 * the tail block minus the head block.
		 */
		अगर (XFS_IS_CORRUPT(log->l_mp,
				   head_block >= tail_block ||
				   head_cycle != tail_cycle + 1))
			वापस -EFSCORRUPTED;
		tail_distance = tail_block - head_block;
	पूर्ण

	/*
	 * If the head is right up against the tail, we can't clear
	 * anything.
	 */
	अगर (tail_distance <= 0) अणु
		ASSERT(tail_distance == 0);
		वापस 0;
	पूर्ण

	max_distance = XLOG_TOTAL_REC_SHIFT(log);
	/*
	 * Take the smaller of the maximum amount of outstanding I/O
	 * we could have and the distance to the tail to clear out.
	 * We take the smaller so that we करोn't overग_लिखो the tail and
	 * we करोn't waste all day writing from the head to the tail
	 * क्रम no reason.
	 */
	max_distance = min(max_distance, tail_distance);

	अगर ((head_block + max_distance) <= log->l_logBBsize) अणु
		/*
		 * We can stomp all the blocks we need to without
		 * wrapping around the end of the log.  Just करो it
		 * in a single ग_लिखो.  Use the cycle number of the
		 * current cycle minus one so that the log will look like:
		 *     n ... | n - 1 ...
		 */
		error = xlog_ग_लिखो_log_records(log, (head_cycle - 1),
				head_block, max_distance, tail_cycle,
				tail_block);
		अगर (error)
			वापस error;
	पूर्ण अन्यथा अणु
		/*
		 * We need to wrap around the end of the physical log in
		 * order to clear all the blocks.  Do it in two separate
		 * I/Os.  The first ग_लिखो should be from the head to the
		 * end of the physical log, and it should use the current
		 * cycle number minus one just like above.
		 */
		distance = log->l_logBBsize - head_block;
		error = xlog_ग_लिखो_log_records(log, (head_cycle - 1),
				head_block, distance, tail_cycle,
				tail_block);

		अगर (error)
			वापस error;

		/*
		 * Now ग_लिखो the blocks at the start of the physical log.
		 * This ग_लिखोs the reमुख्यder of the blocks we want to clear.
		 * It uses the current cycle number since we're now on the
		 * same cycle as the head so that we get:
		 *    n ... n ... | n - 1 ...
		 *    ^^^^^ blocks we're writing
		 */
		distance = max_distance - (log->l_logBBsize - head_block);
		error = xlog_ग_लिखो_log_records(log, head_cycle, 0, distance,
				tail_cycle, tail_block);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Release the recovered पूर्णांकent item in the AIL that matches the given पूर्णांकent
 * type and पूर्णांकent id.
 */
व्योम
xlog_recover_release_पूर्णांकent(
	काष्ठा xlog		*log,
	अचिन्हित लघु		पूर्णांकent_type,
	uपूर्णांक64_t		पूर्णांकent_id)
अणु
	काष्ठा xfs_ail_cursor	cur;
	काष्ठा xfs_log_item	*lip;
	काष्ठा xfs_ail		*ailp = log->l_ailp;

	spin_lock(&ailp->ail_lock);
	क्रम (lip = xfs_trans_ail_cursor_first(ailp, &cur, 0); lip != शून्य;
	     lip = xfs_trans_ail_cursor_next(ailp, &cur)) अणु
		अगर (lip->li_type != पूर्णांकent_type)
			जारी;
		अगर (!lip->li_ops->iop_match(lip, पूर्णांकent_id))
			जारी;

		spin_unlock(&ailp->ail_lock);
		lip->li_ops->iop_release(lip);
		spin_lock(&ailp->ail_lock);
		अवरोध;
	पूर्ण

	xfs_trans_ail_cursor_करोne(&cur);
	spin_unlock(&ailp->ail_lock);
पूर्ण

/******************************************************************************
 *
 *		Log recover routines
 *
 ******************************************************************************
 */
अटल स्थिर काष्ठा xlog_recover_item_ops *xlog_recover_item_ops[] = अणु
	&xlog_buf_item_ops,
	&xlog_inode_item_ops,
	&xlog_dquot_item_ops,
	&xlog_quotaoff_item_ops,
	&xlog_icreate_item_ops,
	&xlog_efi_item_ops,
	&xlog_efd_item_ops,
	&xlog_rui_item_ops,
	&xlog_rud_item_ops,
	&xlog_cui_item_ops,
	&xlog_cud_item_ops,
	&xlog_bui_item_ops,
	&xlog_bud_item_ops,
पूर्ण;

अटल स्थिर काष्ठा xlog_recover_item_ops *
xlog_find_item_ops(
	काष्ठा xlog_recover_item		*item)
अणु
	अचिन्हित पूर्णांक				i;

	क्रम (i = 0; i < ARRAY_SIZE(xlog_recover_item_ops); i++)
		अगर (ITEM_TYPE(item) == xlog_recover_item_ops[i]->item_type)
			वापस xlog_recover_item_ops[i];

	वापस शून्य;
पूर्ण

/*
 * Sort the log items in the transaction.
 *
 * The ordering स्थिरraपूर्णांकs are defined by the inode allocation and unlink
 * behaviour. The rules are:
 *
 *	1. Every item is only logged once in a given transaction. Hence it
 *	   represents the last logged state of the item. Hence ordering is
 *	   dependent on the order in which operations need to be perक्रमmed so
 *	   required initial conditions are always met.
 *
 *	2. Cancelled buffers are recorded in pass 1 in a separate table and
 *	   there's nothing to replay from them so we can simply cull them
 *	   from the transaction. However, we can't do that until after we've
 *	   replayed all the other items because they may be dependent on the
 *	   cancelled buffer and replaying the cancelled buffer can हटाओ it
 *	   क्रमm the cancelled buffer table. Hence they have tobe करोne last.
 *
 *	3. Inode allocation buffers must be replayed beक्रमe inode items that
 *	   पढ़ो the buffer and replay changes पूर्णांकo it. For fileप्रणालीs using the
 *	   ICREATE transactions, this means XFS_LI_ICREATE objects need to get
 *	   treated the same as inode allocation buffers as they create and
 *	   initialise the buffers directly.
 *
 *	4. Inode unlink buffers must be replayed after inode items are replayed.
 *	   This ensures that inodes are completely flushed to the inode buffer
 *	   in a "free" state beक्रमe we हटाओ the unlinked inode list poपूर्णांकer.
 *
 * Hence the ordering needs to be inode allocation buffers first, inode items
 * second, inode unlink buffers third and cancelled buffers last.
 *
 * But there's a problem with that - we can't tell an inode allocation buffer
 * apart from a regular buffer, so we can't separate them. We can, however,
 * tell an inode unlink buffer from the others, and so we can separate them out
 * from all the other buffers and move them to last.
 *
 * Hence, 4 lists, in order from head to tail:
 *	- buffer_list क्रम all buffers except cancelled/inode unlink buffers
 *	- item_list क्रम all non-buffer items
 *	- inode_buffer_list क्रम inode unlink buffers
 *	- cancel_list क्रम the cancelled buffers
 *
 * Note that we add objects to the tail of the lists so that first-to-last
 * ordering is preserved within the lists. Adding objects to the head of the
 * list means when we traverse from the head we walk them in last-to-first
 * order. For cancelled buffers and inode unlink buffers this करोesn't matter,
 * but क्रम all other items there may be specअगरic ordering that we need to
 * preserve.
 */
STATIC पूर्णांक
xlog_recover_reorder_trans(
	काष्ठा xlog		*log,
	काष्ठा xlog_recover	*trans,
	पूर्णांक			pass)
अणु
	काष्ठा xlog_recover_item *item, *n;
	पूर्णांक			error = 0;
	LIST_HEAD(sort_list);
	LIST_HEAD(cancel_list);
	LIST_HEAD(buffer_list);
	LIST_HEAD(inode_buffer_list);
	LIST_HEAD(item_list);

	list_splice_init(&trans->r_itemq, &sort_list);
	list_क्रम_each_entry_safe(item, n, &sort_list, ri_list) अणु
		क्रमागत xlog_recover_reorder	fate = XLOG_REORDER_ITEM_LIST;

		item->ri_ops = xlog_find_item_ops(item);
		अगर (!item->ri_ops) अणु
			xfs_warn(log->l_mp,
				"%s: unrecognized type of log operation (%d)",
				__func__, ITEM_TYPE(item));
			ASSERT(0);
			/*
			 * वापस the reमुख्यing items back to the transaction
			 * item list so they can be मुक्तd in caller.
			 */
			अगर (!list_empty(&sort_list))
				list_splice_init(&sort_list, &trans->r_itemq);
			error = -EFSCORRUPTED;
			अवरोध;
		पूर्ण

		अगर (item->ri_ops->reorder)
			fate = item->ri_ops->reorder(item);

		चयन (fate) अणु
		हाल XLOG_REORDER_BUFFER_LIST:
			list_move_tail(&item->ri_list, &buffer_list);
			अवरोध;
		हाल XLOG_REORDER_CANCEL_LIST:
			trace_xfs_log_recover_item_reorder_head(log,
					trans, item, pass);
			list_move(&item->ri_list, &cancel_list);
			अवरोध;
		हाल XLOG_REORDER_INODE_BUFFER_LIST:
			list_move(&item->ri_list, &inode_buffer_list);
			अवरोध;
		हाल XLOG_REORDER_ITEM_LIST:
			trace_xfs_log_recover_item_reorder_tail(log,
							trans, item, pass);
			list_move_tail(&item->ri_list, &item_list);
			अवरोध;
		पूर्ण
	पूर्ण

	ASSERT(list_empty(&sort_list));
	अगर (!list_empty(&buffer_list))
		list_splice(&buffer_list, &trans->r_itemq);
	अगर (!list_empty(&item_list))
		list_splice_tail(&item_list, &trans->r_itemq);
	अगर (!list_empty(&inode_buffer_list))
		list_splice_tail(&inode_buffer_list, &trans->r_itemq);
	अगर (!list_empty(&cancel_list))
		list_splice_tail(&cancel_list, &trans->r_itemq);
	वापस error;
पूर्ण

व्योम
xlog_buf_पढ़ोahead(
	काष्ठा xlog		*log,
	xfs_daddr_t		blkno,
	uपूर्णांक			len,
	स्थिर काष्ठा xfs_buf_ops *ops)
अणु
	अगर (!xlog_is_buffer_cancelled(log, blkno, len))
		xfs_buf_पढ़ोahead(log->l_mp->m_ddev_targp, blkno, len, ops);
पूर्ण

STATIC पूर्णांक
xlog_recover_items_pass2(
	काष्ठा xlog                     *log,
	काष्ठा xlog_recover             *trans,
	काष्ठा list_head                *buffer_list,
	काष्ठा list_head                *item_list)
अणु
	काष्ठा xlog_recover_item	*item;
	पूर्णांक				error = 0;

	list_क्रम_each_entry(item, item_list, ri_list) अणु
		trace_xfs_log_recover_item_recover(log, trans, item,
				XLOG_RECOVER_PASS2);

		अगर (item->ri_ops->commit_pass2)
			error = item->ri_ops->commit_pass2(log, buffer_list,
					item, trans->r_lsn);
		अगर (error)
			वापस error;
	पूर्ण

	वापस error;
पूर्ण

/*
 * Perक्रमm the transaction.
 *
 * If the transaction modअगरies a buffer or inode, करो it now.  Otherwise,
 * EFIs and EFDs get queued up by adding entries पूर्णांकo the AIL क्रम them.
 */
STATIC पूर्णांक
xlog_recover_commit_trans(
	काष्ठा xlog		*log,
	काष्ठा xlog_recover	*trans,
	पूर्णांक			pass,
	काष्ठा list_head	*buffer_list)
अणु
	पूर्णांक				error = 0;
	पूर्णांक				items_queued = 0;
	काष्ठा xlog_recover_item	*item;
	काष्ठा xlog_recover_item	*next;
	LIST_HEAD			(ra_list);
	LIST_HEAD			(करोne_list);

	#घोषणा XLOG_RECOVER_COMMIT_QUEUE_MAX 100

	hlist_del_init(&trans->r_list);

	error = xlog_recover_reorder_trans(log, trans, pass);
	अगर (error)
		वापस error;

	list_क्रम_each_entry_safe(item, next, &trans->r_itemq, ri_list) अणु
		trace_xfs_log_recover_item_recover(log, trans, item, pass);

		चयन (pass) अणु
		हाल XLOG_RECOVER_PASS1:
			अगर (item->ri_ops->commit_pass1)
				error = item->ri_ops->commit_pass1(log, item);
			अवरोध;
		हाल XLOG_RECOVER_PASS2:
			अगर (item->ri_ops->ra_pass2)
				item->ri_ops->ra_pass2(log, item);
			list_move_tail(&item->ri_list, &ra_list);
			items_queued++;
			अगर (items_queued >= XLOG_RECOVER_COMMIT_QUEUE_MAX) अणु
				error = xlog_recover_items_pass2(log, trans,
						buffer_list, &ra_list);
				list_splice_tail_init(&ra_list, &करोne_list);
				items_queued = 0;
			पूर्ण

			अवरोध;
		शेष:
			ASSERT(0);
		पूर्ण

		अगर (error)
			जाओ out;
	पूर्ण

out:
	अगर (!list_empty(&ra_list)) अणु
		अगर (!error)
			error = xlog_recover_items_pass2(log, trans,
					buffer_list, &ra_list);
		list_splice_tail_init(&ra_list, &करोne_list);
	पूर्ण

	अगर (!list_empty(&करोne_list))
		list_splice_init(&करोne_list, &trans->r_itemq);

	वापस error;
पूर्ण

STATIC व्योम
xlog_recover_add_item(
	काष्ठा list_head	*head)
अणु
	काष्ठा xlog_recover_item *item;

	item = kmem_zalloc(माप(काष्ठा xlog_recover_item), 0);
	INIT_LIST_HEAD(&item->ri_list);
	list_add_tail(&item->ri_list, head);
पूर्ण

STATIC पूर्णांक
xlog_recover_add_to_cont_trans(
	काष्ठा xlog		*log,
	काष्ठा xlog_recover	*trans,
	अक्षर			*dp,
	पूर्णांक			len)
अणु
	काष्ठा xlog_recover_item *item;
	अक्षर			*ptr, *old_ptr;
	पूर्णांक			old_len;

	/*
	 * If the transaction is empty, the header was split across this and the
	 * previous record. Copy the rest of the header.
	 */
	अगर (list_empty(&trans->r_itemq)) अणु
		ASSERT(len <= माप(काष्ठा xfs_trans_header));
		अगर (len > माप(काष्ठा xfs_trans_header)) अणु
			xfs_warn(log->l_mp, "%s: bad header length", __func__);
			वापस -EFSCORRUPTED;
		पूर्ण

		xlog_recover_add_item(&trans->r_itemq);
		ptr = (अक्षर *)&trans->r_theader +
				माप(काष्ठा xfs_trans_header) - len;
		स_नकल(ptr, dp, len);
		वापस 0;
	पूर्ण

	/* take the tail entry */
	item = list_entry(trans->r_itemq.prev, काष्ठा xlog_recover_item,
			  ri_list);

	old_ptr = item->ri_buf[item->ri_cnt-1].i_addr;
	old_len = item->ri_buf[item->ri_cnt-1].i_len;

	ptr = kपुनः_स्मृति(old_ptr, len + old_len, GFP_KERNEL | __GFP_NOFAIL);
	स_नकल(&ptr[old_len], dp, len);
	item->ri_buf[item->ri_cnt-1].i_len += len;
	item->ri_buf[item->ri_cnt-1].i_addr = ptr;
	trace_xfs_log_recover_item_add_cont(log, trans, item, 0);
	वापस 0;
पूर्ण

/*
 * The next region to add is the start of a new region.  It could be
 * a whole region or it could be the first part of a new region.  Because
 * of this, the assumption here is that the type and size fields of all
 * क्रमmat काष्ठाures fit पूर्णांकo the first 32 bits of the काष्ठाure.
 *
 * This works because all regions must be 32 bit aligned.  Thereक्रमe, we
 * either have both fields or we have neither field.  In the हाल we have
 * neither field, the data part of the region is zero length.  We only have
 * a log_op_header and can throw away the header since a new one will appear
 * later.  If we have at least 4 bytes, then we can determine how many regions
 * will appear in the current log item.
 */
STATIC पूर्णांक
xlog_recover_add_to_trans(
	काष्ठा xlog		*log,
	काष्ठा xlog_recover	*trans,
	अक्षर			*dp,
	पूर्णांक			len)
अणु
	काष्ठा xfs_inode_log_क्रमmat	*in_f;			/* any will करो */
	काष्ठा xlog_recover_item *item;
	अक्षर			*ptr;

	अगर (!len)
		वापस 0;
	अगर (list_empty(&trans->r_itemq)) अणु
		/* we need to catch log corruptions here */
		अगर (*(uपूर्णांक *)dp != XFS_TRANS_HEADER_MAGIC) अणु
			xfs_warn(log->l_mp, "%s: bad header magic number",
				__func__);
			ASSERT(0);
			वापस -EFSCORRUPTED;
		पूर्ण

		अगर (len > माप(काष्ठा xfs_trans_header)) अणु
			xfs_warn(log->l_mp, "%s: bad header length", __func__);
			ASSERT(0);
			वापस -EFSCORRUPTED;
		पूर्ण

		/*
		 * The transaction header can be arbitrarily split across op
		 * records. If we करोn't have the whole thing here, copy what we
		 * करो have and handle the rest in the next record.
		 */
		अगर (len == माप(काष्ठा xfs_trans_header))
			xlog_recover_add_item(&trans->r_itemq);
		स_नकल(&trans->r_theader, dp, len);
		वापस 0;
	पूर्ण

	ptr = kmem_alloc(len, 0);
	स_नकल(ptr, dp, len);
	in_f = (काष्ठा xfs_inode_log_क्रमmat *)ptr;

	/* take the tail entry */
	item = list_entry(trans->r_itemq.prev, काष्ठा xlog_recover_item,
			  ri_list);
	अगर (item->ri_total != 0 &&
	     item->ri_total == item->ri_cnt) अणु
		/* tail item is in use, get a new one */
		xlog_recover_add_item(&trans->r_itemq);
		item = list_entry(trans->r_itemq.prev,
					काष्ठा xlog_recover_item, ri_list);
	पूर्ण

	अगर (item->ri_total == 0) अणु		/* first region to be added */
		अगर (in_f->ilf_size == 0 ||
		    in_f->ilf_size > XLOG_MAX_REGIONS_IN_ITEM) अणु
			xfs_warn(log->l_mp,
		"bad number of regions (%d) in inode log format",
				  in_f->ilf_size);
			ASSERT(0);
			kmem_मुक्त(ptr);
			वापस -EFSCORRUPTED;
		पूर्ण

		item->ri_total = in_f->ilf_size;
		item->ri_buf =
			kmem_zalloc(item->ri_total * माप(xfs_log_iovec_t),
				    0);
	पूर्ण

	अगर (item->ri_total <= item->ri_cnt) अणु
		xfs_warn(log->l_mp,
	"log item region count (%d) overflowed size (%d)",
				item->ri_cnt, item->ri_total);
		ASSERT(0);
		kmem_मुक्त(ptr);
		वापस -EFSCORRUPTED;
	पूर्ण

	/* Description region is ri_buf[0] */
	item->ri_buf[item->ri_cnt].i_addr = ptr;
	item->ri_buf[item->ri_cnt].i_len  = len;
	item->ri_cnt++;
	trace_xfs_log_recover_item_add(log, trans, item, 0);
	वापस 0;
पूर्ण

/*
 * Free up any resources allocated by the transaction
 *
 * Remember that EFIs, EFDs, and IUNLINKs are handled later.
 */
STATIC व्योम
xlog_recover_मुक्त_trans(
	काष्ठा xlog_recover	*trans)
अणु
	काष्ठा xlog_recover_item *item, *n;
	पूर्णांक			i;

	hlist_del_init(&trans->r_list);

	list_क्रम_each_entry_safe(item, n, &trans->r_itemq, ri_list) अणु
		/* Free the regions in the item. */
		list_del(&item->ri_list);
		क्रम (i = 0; i < item->ri_cnt; i++)
			kmem_मुक्त(item->ri_buf[i].i_addr);
		/* Free the item itself */
		kmem_मुक्त(item->ri_buf);
		kmem_मुक्त(item);
	पूर्ण
	/* Free the transaction recover काष्ठाure */
	kmem_मुक्त(trans);
पूर्ण

/*
 * On error or completion, trans is मुक्तd.
 */
STATIC पूर्णांक
xlog_recovery_process_trans(
	काष्ठा xlog		*log,
	काष्ठा xlog_recover	*trans,
	अक्षर			*dp,
	अचिन्हित पूर्णांक		len,
	अचिन्हित पूर्णांक		flags,
	पूर्णांक			pass,
	काष्ठा list_head	*buffer_list)
अणु
	पूर्णांक			error = 0;
	bool			मुक्तit = false;

	/* mask off ophdr transaction container flags */
	flags &= ~XLOG_END_TRANS;
	अगर (flags & XLOG_WAS_CONT_TRANS)
		flags &= ~XLOG_CONTINUE_TRANS;

	/*
	 * Callees must not मुक्त the trans काष्ठाure. We'll decide अगर we need to
	 * मुक्त it or not based on the operation being करोne and it's result.
	 */
	चयन (flags) अणु
	/* expected flag values */
	हाल 0:
	हाल XLOG_CONTINUE_TRANS:
		error = xlog_recover_add_to_trans(log, trans, dp, len);
		अवरोध;
	हाल XLOG_WAS_CONT_TRANS:
		error = xlog_recover_add_to_cont_trans(log, trans, dp, len);
		अवरोध;
	हाल XLOG_COMMIT_TRANS:
		error = xlog_recover_commit_trans(log, trans, pass,
						  buffer_list);
		/* success or fail, we are now करोne with this transaction. */
		मुक्तit = true;
		अवरोध;

	/* unexpected flag values */
	हाल XLOG_UNMOUNT_TRANS:
		/* just skip trans */
		xfs_warn(log->l_mp, "%s: Unmount LR", __func__);
		मुक्तit = true;
		अवरोध;
	हाल XLOG_START_TRANS:
	शेष:
		xfs_warn(log->l_mp, "%s: bad flag 0x%x", __func__, flags);
		ASSERT(0);
		error = -EFSCORRUPTED;
		अवरोध;
	पूर्ण
	अगर (error || मुक्तit)
		xlog_recover_मुक्त_trans(trans);
	वापस error;
पूर्ण

/*
 * Lookup the transaction recovery काष्ठाure associated with the ID in the
 * current ophdr. If the transaction करोesn't exist and the start flag is set in
 * the ophdr, then allocate a new transaction क्रम future ID matches to find.
 * Either way, वापस what we found during the lookup - an existing transaction
 * or nothing.
 */
STATIC काष्ठा xlog_recover *
xlog_recover_ophdr_to_trans(
	काष्ठा hlist_head	rhash[],
	काष्ठा xlog_rec_header	*rhead,
	काष्ठा xlog_op_header	*ohead)
अणु
	काष्ठा xlog_recover	*trans;
	xlog_tid_t		tid;
	काष्ठा hlist_head	*rhp;

	tid = be32_to_cpu(ohead->oh_tid);
	rhp = &rhash[XLOG_RHASH(tid)];
	hlist_क्रम_each_entry(trans, rhp, r_list) अणु
		अगर (trans->r_log_tid == tid)
			वापस trans;
	पूर्ण

	/*
	 * skip over non-start transaction headers - we could be
	 * processing slack space beक्रमe the next transaction starts
	 */
	अगर (!(ohead->oh_flags & XLOG_START_TRANS))
		वापस शून्य;

	ASSERT(be32_to_cpu(ohead->oh_len) == 0);

	/*
	 * This is a new transaction so allocate a new recovery container to
	 * hold the recovery ops that will follow.
	 */
	trans = kmem_zalloc(माप(काष्ठा xlog_recover), 0);
	trans->r_log_tid = tid;
	trans->r_lsn = be64_to_cpu(rhead->h_lsn);
	INIT_LIST_HEAD(&trans->r_itemq);
	INIT_HLIST_NODE(&trans->r_list);
	hlist_add_head(&trans->r_list, rhp);

	/*
	 * Nothing more to करो क्रम this ophdr. Items to be added to this new
	 * transaction will be in subsequent ophdr containers.
	 */
	वापस शून्य;
पूर्ण

STATIC पूर्णांक
xlog_recover_process_ophdr(
	काष्ठा xlog		*log,
	काष्ठा hlist_head	rhash[],
	काष्ठा xlog_rec_header	*rhead,
	काष्ठा xlog_op_header	*ohead,
	अक्षर			*dp,
	अक्षर			*end,
	पूर्णांक			pass,
	काष्ठा list_head	*buffer_list)
अणु
	काष्ठा xlog_recover	*trans;
	अचिन्हित पूर्णांक		len;
	पूर्णांक			error;

	/* Do we understand who wrote this op? */
	अगर (ohead->oh_clientid != XFS_TRANSACTION &&
	    ohead->oh_clientid != XFS_LOG) अणु
		xfs_warn(log->l_mp, "%s: bad clientid 0x%x",
			__func__, ohead->oh_clientid);
		ASSERT(0);
		वापस -EFSCORRUPTED;
	पूर्ण

	/*
	 * Check the ophdr contains all the data it is supposed to contain.
	 */
	len = be32_to_cpu(ohead->oh_len);
	अगर (dp + len > end) अणु
		xfs_warn(log->l_mp, "%s: bad length 0x%x", __func__, len);
		WARN_ON(1);
		वापस -EFSCORRUPTED;
	पूर्ण

	trans = xlog_recover_ophdr_to_trans(rhash, rhead, ohead);
	अगर (!trans) अणु
		/* nothing to करो, so skip over this ophdr */
		वापस 0;
	पूर्ण

	/*
	 * The recovered buffer queue is drained only once we know that all
	 * recovery items क्रम the current LSN have been processed. This is
	 * required because:
	 *
	 * - Buffer ग_लिखो submission updates the metadata LSN of the buffer.
	 * - Log recovery skips items with a metadata LSN >= the current LSN of
	 *   the recovery item.
	 * - Separate recovery items against the same metadata buffer can share
	 *   a current LSN. I.e., consider that the LSN of a recovery item is
	 *   defined as the starting LSN of the first record in which its
	 *   transaction appears, that a record can hold multiple transactions,
	 *   and/or that a transaction can span multiple records.
	 *
	 * In other words, we are allowed to submit a buffer from log recovery
	 * once per current LSN. Otherwise, we may incorrectly skip recovery
	 * items and cause corruption.
	 *
	 * We करोn't know up front whether buffers are updated multiple बार per
	 * LSN. Thereक्रमe, track the current LSN of each commit log record as it
	 * is processed and drain the queue when it changes. Use commit records
	 * because they are ordered correctly by the logging code.
	 */
	अगर (log->l_recovery_lsn != trans->r_lsn &&
	    ohead->oh_flags & XLOG_COMMIT_TRANS) अणु
		error = xfs_buf_delwri_submit(buffer_list);
		अगर (error)
			वापस error;
		log->l_recovery_lsn = trans->r_lsn;
	पूर्ण

	वापस xlog_recovery_process_trans(log, trans, dp, len,
					   ohead->oh_flags, pass, buffer_list);
पूर्ण

/*
 * There are two valid states of the r_state field.  0 indicates that the
 * transaction काष्ठाure is in a normal state.  We have either seen the
 * start of the transaction or the last operation we added was not a partial
 * operation.  If the last operation we added to the transaction was a
 * partial operation, we need to mark r_state with XLOG_WAS_CONT_TRANS.
 *
 * NOTE: skip LRs with 0 data length.
 */
STATIC पूर्णांक
xlog_recover_process_data(
	काष्ठा xlog		*log,
	काष्ठा hlist_head	rhash[],
	काष्ठा xlog_rec_header	*rhead,
	अक्षर			*dp,
	पूर्णांक			pass,
	काष्ठा list_head	*buffer_list)
अणु
	काष्ठा xlog_op_header	*ohead;
	अक्षर			*end;
	पूर्णांक			num_logops;
	पूर्णांक			error;

	end = dp + be32_to_cpu(rhead->h_len);
	num_logops = be32_to_cpu(rhead->h_num_logops);

	/* check the log क्रमmat matches our own - अन्यथा we can't recover */
	अगर (xlog_header_check_recover(log->l_mp, rhead))
		वापस -EIO;

	trace_xfs_log_recover_record(log, rhead, pass);
	जबतक ((dp < end) && num_logops) अणु

		ohead = (काष्ठा xlog_op_header *)dp;
		dp += माप(*ohead);
		ASSERT(dp <= end);

		/* errors will पात recovery */
		error = xlog_recover_process_ophdr(log, rhash, rhead, ohead,
						   dp, end, pass, buffer_list);
		अगर (error)
			वापस error;

		dp += be32_to_cpu(ohead->oh_len);
		num_logops--;
	पूर्ण
	वापस 0;
पूर्ण

/* Take all the collected deferred ops and finish them in order. */
अटल पूर्णांक
xlog_finish_defer_ops(
	काष्ठा xfs_mount	*mp,
	काष्ठा list_head	*capture_list)
अणु
	काष्ठा xfs_defer_capture *dfc, *next;
	काष्ठा xfs_trans	*tp;
	काष्ठा xfs_inode	*ip;
	पूर्णांक			error = 0;

	list_क्रम_each_entry_safe(dfc, next, capture_list, dfc_list) अणु
		काष्ठा xfs_trans_res	resv;

		/*
		 * Create a new transaction reservation from the captured
		 * inक्रमmation.  Set logcount to 1 to क्रमce the new transaction
		 * to regrant every roll so that we can make क्रमward progress
		 * in recovery no matter how full the log might be.
		 */
		resv.tr_logres = dfc->dfc_logres;
		resv.tr_logcount = 1;
		resv.tr_logflags = XFS_TRANS_PERM_LOG_RES;

		error = xfs_trans_alloc(mp, &resv, dfc->dfc_blkres,
				dfc->dfc_rtxres, XFS_TRANS_RESERVE, &tp);
		अगर (error)
			वापस error;

		/*
		 * Transfer to this new transaction all the dfops we captured
		 * from recovering a single पूर्णांकent item.
		 */
		list_del_init(&dfc->dfc_list);
		xfs_defer_ops_जारी(dfc, tp, &ip);

		error = xfs_trans_commit(tp);
		अगर (ip) अणु
			xfs_iunlock(ip, XFS_ILOCK_EXCL);
			xfs_irele(ip);
		पूर्ण
		अगर (error)
			वापस error;
	पूर्ण

	ASSERT(list_empty(capture_list));
	वापस 0;
पूर्ण

/* Release all the captured defer ops and capture काष्ठाures in this list. */
अटल व्योम
xlog_पात_defer_ops(
	काष्ठा xfs_mount		*mp,
	काष्ठा list_head		*capture_list)
अणु
	काष्ठा xfs_defer_capture	*dfc;
	काष्ठा xfs_defer_capture	*next;

	list_क्रम_each_entry_safe(dfc, next, capture_list, dfc_list) अणु
		list_del_init(&dfc->dfc_list);
		xfs_defer_ops_release(mp, dfc);
	पूर्ण
पूर्ण
/*
 * When this is called, all of the log पूर्णांकent items which did not have
 * corresponding log करोne items should be in the AIL.  What we करो now
 * is update the data काष्ठाures associated with each one.
 *
 * Since we process the log पूर्णांकent items in normal transactions, they
 * will be हटाओd at some poपूर्णांक after the commit.  This prevents us
 * from just walking करोwn the list processing each one.  We'll use a
 * flag in the पूर्णांकent item to skip those that we've alपढ़ोy processed
 * and use the AIL iteration mechanism's generation count to try to
 * speed this up at least a bit.
 *
 * When we start, we know that the पूर्णांकents are the only things in the
 * AIL.  As we process them, however, other items are added to the
 * AIL.
 */
STATIC पूर्णांक
xlog_recover_process_पूर्णांकents(
	काष्ठा xlog		*log)
अणु
	LIST_HEAD(capture_list);
	काष्ठा xfs_ail_cursor	cur;
	काष्ठा xfs_log_item	*lip;
	काष्ठा xfs_ail		*ailp;
	पूर्णांक			error = 0;
#अगर defined(DEBUG) || defined(XFS_WARN)
	xfs_lsn_t		last_lsn;
#पूर्ण_अगर

	ailp = log->l_ailp;
	spin_lock(&ailp->ail_lock);
#अगर defined(DEBUG) || defined(XFS_WARN)
	last_lsn = xlog_assign_lsn(log->l_curr_cycle, log->l_curr_block);
#पूर्ण_अगर
	क्रम (lip = xfs_trans_ail_cursor_first(ailp, &cur, 0);
	     lip != शून्य;
	     lip = xfs_trans_ail_cursor_next(ailp, &cur)) अणु
		/*
		 * We're करोne when we see something other than an पूर्णांकent.
		 * There should be no पूर्णांकents left in the AIL now.
		 */
		अगर (!xlog_item_is_पूर्णांकent(lip)) अणु
#अगर_घोषित DEBUG
			क्रम (; lip; lip = xfs_trans_ail_cursor_next(ailp, &cur))
				ASSERT(!xlog_item_is_पूर्णांकent(lip));
#पूर्ण_अगर
			अवरोध;
		पूर्ण

		/*
		 * We should never see a reकरो item with a LSN higher than
		 * the last transaction we found in the log at the start
		 * of recovery.
		 */
		ASSERT(XFS_LSN_CMP(last_lsn, lip->li_lsn) >= 0);

		/*
		 * NOTE: If your पूर्णांकent processing routine can create more
		 * deferred ops, you /must/ attach them to the capture list in
		 * the recover routine or अन्यथा those subsequent पूर्णांकents will be
		 * replayed in the wrong order!
		 */
		spin_unlock(&ailp->ail_lock);
		error = lip->li_ops->iop_recover(lip, &capture_list);
		spin_lock(&ailp->ail_lock);
		अगर (error) अणु
			trace_xlog_पूर्णांकent_recovery_failed(log->l_mp, error,
					lip->li_ops->iop_recover);
			अवरोध;
		पूर्ण
	पूर्ण

	xfs_trans_ail_cursor_करोne(&cur);
	spin_unlock(&ailp->ail_lock);
	अगर (error)
		जाओ err;

	error = xlog_finish_defer_ops(log->l_mp, &capture_list);
	अगर (error)
		जाओ err;

	वापस 0;
err:
	xlog_पात_defer_ops(log->l_mp, &capture_list);
	वापस error;
पूर्ण

/*
 * A cancel occurs when the mount has failed and we're bailing out.
 * Release all pending log पूर्णांकent items so they करोn't pin the AIL.
 */
STATIC व्योम
xlog_recover_cancel_पूर्णांकents(
	काष्ठा xlog		*log)
अणु
	काष्ठा xfs_log_item	*lip;
	काष्ठा xfs_ail_cursor	cur;
	काष्ठा xfs_ail		*ailp;

	ailp = log->l_ailp;
	spin_lock(&ailp->ail_lock);
	lip = xfs_trans_ail_cursor_first(ailp, &cur, 0);
	जबतक (lip != शून्य) अणु
		/*
		 * We're करोne when we see something other than an पूर्णांकent.
		 * There should be no पूर्णांकents left in the AIL now.
		 */
		अगर (!xlog_item_is_पूर्णांकent(lip)) अणु
#अगर_घोषित DEBUG
			क्रम (; lip; lip = xfs_trans_ail_cursor_next(ailp, &cur))
				ASSERT(!xlog_item_is_पूर्णांकent(lip));
#पूर्ण_अगर
			अवरोध;
		पूर्ण

		spin_unlock(&ailp->ail_lock);
		lip->li_ops->iop_release(lip);
		spin_lock(&ailp->ail_lock);
		lip = xfs_trans_ail_cursor_next(ailp, &cur);
	पूर्ण

	xfs_trans_ail_cursor_करोne(&cur);
	spin_unlock(&ailp->ail_lock);
पूर्ण

/*
 * This routine perक्रमms a transaction to null out a bad inode poपूर्णांकer
 * in an agi unlinked inode hash bucket.
 */
STATIC व्योम
xlog_recover_clear_agi_bucket(
	xfs_mount_t	*mp,
	xfs_agnumber_t	agno,
	पूर्णांक		bucket)
अणु
	xfs_trans_t	*tp;
	xfs_agi_t	*agi;
	काष्ठा xfs_buf	*agibp;
	पूर्णांक		offset;
	पूर्णांक		error;

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_clearagi, 0, 0, 0, &tp);
	अगर (error)
		जाओ out_error;

	error = xfs_पढ़ो_agi(mp, tp, agno, &agibp);
	अगर (error)
		जाओ out_पात;

	agi = agibp->b_addr;
	agi->agi_unlinked[bucket] = cpu_to_be32(शून्यAGINO);
	offset = दुरत्व(xfs_agi_t, agi_unlinked) +
		 (माप(xfs_agino_t) * bucket);
	xfs_trans_log_buf(tp, agibp, offset,
			  (offset + माप(xfs_agino_t) - 1));

	error = xfs_trans_commit(tp);
	अगर (error)
		जाओ out_error;
	वापस;

out_पात:
	xfs_trans_cancel(tp);
out_error:
	xfs_warn(mp, "%s: failed to clear agi %d. Continuing.", __func__, agno);
	वापस;
पूर्ण

STATIC xfs_agino_t
xlog_recover_process_one_iunlink(
	काष्ठा xfs_mount		*mp,
	xfs_agnumber_t			agno,
	xfs_agino_t			agino,
	पूर्णांक				bucket)
अणु
	काष्ठा xfs_buf			*ibp;
	काष्ठा xfs_dinode		*dip;
	काष्ठा xfs_inode		*ip;
	xfs_ino_t			ino;
	पूर्णांक				error;

	ino = XFS_AGINO_TO_INO(mp, agno, agino);
	error = xfs_iget(mp, शून्य, ino, 0, 0, &ip);
	अगर (error)
		जाओ fail;

	/*
	 * Get the on disk inode to find the next inode in the bucket.
	 */
	error = xfs_imap_to_bp(mp, शून्य, &ip->i_imap, &ibp);
	अगर (error)
		जाओ fail_iput;
	dip = xfs_buf_offset(ibp, ip->i_imap.im_boffset);

	xfs_अगरlags_clear(ip, XFS_IRECOVERY);
	ASSERT(VFS_I(ip)->i_nlink == 0);
	ASSERT(VFS_I(ip)->i_mode != 0);

	/* setup क्रम the next pass */
	agino = be32_to_cpu(dip->di_next_unlinked);
	xfs_buf_rअन्यथा(ibp);

	xfs_irele(ip);
	वापस agino;

 fail_iput:
	xfs_irele(ip);
 fail:
	/*
	 * We can't पढ़ो in the inode this bucket poपूर्णांकs to, or this inode
	 * is messed up.  Just ditch this bucket of inodes.  We will lose
	 * some inodes and space, but at least we won't hang.
	 *
	 * Call xlog_recover_clear_agi_bucket() to perक्रमm a transaction to
	 * clear the inode poपूर्णांकer in the bucket.
	 */
	xlog_recover_clear_agi_bucket(mp, agno, bucket);
	वापस शून्यAGINO;
पूर्ण

/*
 * Recover AGI unlinked lists
 *
 * This is called during recovery to process any inodes which we unlinked but
 * not मुक्तd when the प्रणाली crashed.  These inodes will be on the lists in the
 * AGI blocks. What we करो here is scan all the AGIs and fully truncate and मुक्त
 * any inodes found on the lists. Each inode is हटाओd from the lists when it
 * has been fully truncated and is मुक्तd. The मुक्तing of the inode and its
 * removal from the list must be atomic.
 *
 * If everything we touch in the agi processing loop is alपढ़ोy in memory, this
 * loop can hold the cpu क्रम a दीर्घ समय. It runs without lock contention,
 * memory allocation contention, the need रुको क्रम IO, etc, and so will run
 * until we either run out of inodes to process, run low on memory or we run out
 * of log space.
 *
 * This behaviour is bad क्रम latency on single CPU and non-preemptible kernels,
 * and can prevent other fileप्रणाली work (such as CIL pushes) from running. This
 * can lead to deadlocks अगर the recovery process runs out of log reservation
 * space. Hence we need to yield the CPU when there is other kernel work
 * scheduled on this CPU to ensure other scheduled work can run without undue
 * latency.
 */
STATIC व्योम
xlog_recover_process_iunlinks(
	काष्ठा xlog	*log)
अणु
	xfs_mount_t	*mp;
	xfs_agnumber_t	agno;
	xfs_agi_t	*agi;
	काष्ठा xfs_buf	*agibp;
	xfs_agino_t	agino;
	पूर्णांक		bucket;
	पूर्णांक		error;

	mp = log->l_mp;

	क्रम (agno = 0; agno < mp->m_sb.sb_agcount; agno++) अणु
		/*
		 * Find the agi क्रम this ag.
		 */
		error = xfs_पढ़ो_agi(mp, शून्य, agno, &agibp);
		अगर (error) अणु
			/*
			 * AGI is b0rked. Don't process it.
			 *
			 * We should probably mark the fileप्रणाली as corrupt
			 * after we've recovered all the ag's we can....
			 */
			जारी;
		पूर्ण
		/*
		 * Unlock the buffer so that it can be acquired in the normal
		 * course of the transaction to truncate and मुक्त each inode.
		 * Because we are not racing with anyone अन्यथा here क्रम the AGI
		 * buffer, we करोn't even need to hold it locked to पढ़ो the
		 * initial unlinked bucket entries out of the buffer. We keep
		 * buffer reference though, so that it stays pinned in memory
		 * जबतक we need the buffer.
		 */
		agi = agibp->b_addr;
		xfs_buf_unlock(agibp);

		क्रम (bucket = 0; bucket < XFS_AGI_UNLINKED_BUCKETS; bucket++) अणु
			agino = be32_to_cpu(agi->agi_unlinked[bucket]);
			जबतक (agino != शून्यAGINO) अणु
				agino = xlog_recover_process_one_iunlink(mp,
							agno, agino, bucket);
				cond_resched();
			पूर्ण
		पूर्ण
		xfs_buf_rele(agibp);
	पूर्ण
पूर्ण

STATIC व्योम
xlog_unpack_data(
	काष्ठा xlog_rec_header	*rhead,
	अक्षर			*dp,
	काष्ठा xlog		*log)
अणु
	पूर्णांक			i, j, k;

	क्रम (i = 0; i < BTOBB(be32_to_cpu(rhead->h_len)) &&
		  i < (XLOG_HEADER_CYCLE_SIZE / BBSIZE); i++) अणु
		*(__be32 *)dp = *(__be32 *)&rhead->h_cycle_data[i];
		dp += BBSIZE;
	पूर्ण

	अगर (xfs_sb_version_haslogv2(&log->l_mp->m_sb)) अणु
		xlog_in_core_2_t *xhdr = (xlog_in_core_2_t *)rhead;
		क्रम ( ; i < BTOBB(be32_to_cpu(rhead->h_len)); i++) अणु
			j = i / (XLOG_HEADER_CYCLE_SIZE / BBSIZE);
			k = i % (XLOG_HEADER_CYCLE_SIZE / BBSIZE);
			*(__be32 *)dp = xhdr[j].hic_xheader.xh_cycle_data[k];
			dp += BBSIZE;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * CRC check, unpack and process a log record.
 */
STATIC पूर्णांक
xlog_recover_process(
	काष्ठा xlog		*log,
	काष्ठा hlist_head	rhash[],
	काष्ठा xlog_rec_header	*rhead,
	अक्षर			*dp,
	पूर्णांक			pass,
	काष्ठा list_head	*buffer_list)
अणु
	__le32			old_crc = rhead->h_crc;
	__le32			crc;

	crc = xlog_cksum(log, rhead, dp, be32_to_cpu(rhead->h_len));

	/*
	 * Nothing अन्यथा to करो अगर this is a CRC verअगरication pass. Just वापस
	 * अगर this a record with a non-zero crc. Unक्रमtunately, mkfs always
	 * sets old_crc to 0 so we must consider this valid even on v5 supers.
	 * Otherwise, वापस EFSBADCRC on failure so the callers up the stack
	 * know precisely what failed.
	 */
	अगर (pass == XLOG_RECOVER_CRCPASS) अणु
		अगर (old_crc && crc != old_crc)
			वापस -EFSBADCRC;
		वापस 0;
	पूर्ण

	/*
	 * We're in the normal recovery path. Issue a warning अगर and only अगर the
	 * CRC in the header is non-zero. This is an advisory warning and the
	 * zero CRC check prevents warnings from being emitted when upgrading
	 * the kernel from one that करोes not add CRCs by शेष.
	 */
	अगर (crc != old_crc) अणु
		अगर (old_crc || xfs_sb_version_hascrc(&log->l_mp->m_sb)) अणु
			xfs_alert(log->l_mp,
		"log record CRC mismatch: found 0x%x, expected 0x%x.",
					le32_to_cpu(old_crc),
					le32_to_cpu(crc));
			xfs_hex_dump(dp, 32);
		पूर्ण

		/*
		 * If the fileप्रणाली is CRC enabled, this mismatch becomes a
		 * fatal log corruption failure.
		 */
		अगर (xfs_sb_version_hascrc(&log->l_mp->m_sb)) अणु
			XFS_ERROR_REPORT(__func__, XFS_ERRLEVEL_LOW, log->l_mp);
			वापस -EFSCORRUPTED;
		पूर्ण
	पूर्ण

	xlog_unpack_data(rhead, dp, log);

	वापस xlog_recover_process_data(log, rhash, rhead, dp, pass,
					 buffer_list);
पूर्ण

STATIC पूर्णांक
xlog_valid_rec_header(
	काष्ठा xlog		*log,
	काष्ठा xlog_rec_header	*rhead,
	xfs_daddr_t		blkno,
	पूर्णांक			bufsize)
अणु
	पूर्णांक			hlen;

	अगर (XFS_IS_CORRUPT(log->l_mp,
			   rhead->h_magicno != cpu_to_be32(XLOG_HEADER_MAGIC_NUM)))
		वापस -EFSCORRUPTED;
	अगर (XFS_IS_CORRUPT(log->l_mp,
			   (!rhead->h_version ||
			   (be32_to_cpu(rhead->h_version) &
			    (~XLOG_VERSION_OKBITS))))) अणु
		xfs_warn(log->l_mp, "%s: unrecognised log version (%d).",
			__func__, be32_to_cpu(rhead->h_version));
		वापस -EFSCORRUPTED;
	पूर्ण

	/*
	 * LR body must have data (or it wouldn't have been written)
	 * and h_len must not be greater than LR buffer size.
	 */
	hlen = be32_to_cpu(rhead->h_len);
	अगर (XFS_IS_CORRUPT(log->l_mp, hlen <= 0 || hlen > bufsize))
		वापस -EFSCORRUPTED;

	अगर (XFS_IS_CORRUPT(log->l_mp,
			   blkno > log->l_logBBsize || blkno > पूर्णांक_उच्च))
		वापस -EFSCORRUPTED;
	वापस 0;
पूर्ण

/*
 * Read the log from tail to head and process the log records found.
 * Handle the two हालs where the tail and head are in the same cycle
 * and where the active portion of the log wraps around the end of
 * the physical log separately.  The pass parameter is passed through
 * to the routines called to process the data and is not looked at
 * here.
 */
STATIC पूर्णांक
xlog_करो_recovery_pass(
	काष्ठा xlog		*log,
	xfs_daddr_t		head_blk,
	xfs_daddr_t		tail_blk,
	पूर्णांक			pass,
	xfs_daddr_t		*first_bad)	/* out: first bad log rec */
अणु
	xlog_rec_header_t	*rhead;
	xfs_daddr_t		blk_no, rblk_no;
	xfs_daddr_t		rhead_blk;
	अक्षर			*offset;
	अक्षर			*hbp, *dbp;
	पूर्णांक			error = 0, h_size, h_len;
	पूर्णांक			error2 = 0;
	पूर्णांक			bblks, split_bblks;
	पूर्णांक			hblks, split_hblks, wrapped_hblks;
	पूर्णांक			i;
	काष्ठा hlist_head	rhash[XLOG_RHASH_SIZE];
	LIST_HEAD		(buffer_list);

	ASSERT(head_blk != tail_blk);
	blk_no = rhead_blk = tail_blk;

	क्रम (i = 0; i < XLOG_RHASH_SIZE; i++)
		INIT_HLIST_HEAD(&rhash[i]);

	/*
	 * Read the header of the tail block and get the iclog buffer size from
	 * h_size.  Use this to tell how many sectors make up the log header.
	 */
	अगर (xfs_sb_version_haslogv2(&log->l_mp->m_sb)) अणु
		/*
		 * When using variable length iclogs, पढ़ो first sector of
		 * iclog header and extract the header size from it.  Get a
		 * new hbp that is the correct size.
		 */
		hbp = xlog_alloc_buffer(log, 1);
		अगर (!hbp)
			वापस -ENOMEM;

		error = xlog_bपढ़ो(log, tail_blk, 1, hbp, &offset);
		अगर (error)
			जाओ bपढ़ो_err1;

		rhead = (xlog_rec_header_t *)offset;

		/*
		 * xfsprogs has a bug where record length is based on lsunit but
		 * h_size (iclog size) is hardcoded to 32k. Now that we
		 * unconditionally CRC verअगरy the unmount record, this means the
		 * log buffer can be too small क्रम the record and cause an
		 * overrun.
		 *
		 * Detect this condition here. Use lsunit क्रम the buffer size as
		 * दीर्घ as this looks like the mkfs हाल. Otherwise, वापस an
		 * error to aव्योम a buffer overrun.
		 */
		h_size = be32_to_cpu(rhead->h_size);
		h_len = be32_to_cpu(rhead->h_len);
		अगर (h_len > h_size && h_len <= log->l_mp->m_logbsize &&
		    rhead->h_num_logops == cpu_to_be32(1)) अणु
			xfs_warn(log->l_mp,
		"invalid iclog size (%d bytes), using lsunit (%d bytes)",
				 h_size, log->l_mp->m_logbsize);
			h_size = log->l_mp->m_logbsize;
		पूर्ण

		error = xlog_valid_rec_header(log, rhead, tail_blk, h_size);
		अगर (error)
			जाओ bपढ़ो_err1;

		hblks = xlog_logrec_hblks(log, rhead);
		अगर (hblks != 1) अणु
			kmem_मुक्त(hbp);
			hbp = xlog_alloc_buffer(log, hblks);
		पूर्ण
	पूर्ण अन्यथा अणु
		ASSERT(log->l_sectBBsize == 1);
		hblks = 1;
		hbp = xlog_alloc_buffer(log, 1);
		h_size = XLOG_BIG_RECORD_BSIZE;
	पूर्ण

	अगर (!hbp)
		वापस -ENOMEM;
	dbp = xlog_alloc_buffer(log, BTOBB(h_size));
	अगर (!dbp) अणु
		kmem_मुक्त(hbp);
		वापस -ENOMEM;
	पूर्ण

	स_रखो(rhash, 0, माप(rhash));
	अगर (tail_blk > head_blk) अणु
		/*
		 * Perक्रमm recovery around the end of the physical log.
		 * When the head is not on the same cycle number as the tail,
		 * we can't करो a sequential recovery.
		 */
		जबतक (blk_no < log->l_logBBsize) अणु
			/*
			 * Check क्रम header wrapping around physical end-of-log
			 */
			offset = hbp;
			split_hblks = 0;
			wrapped_hblks = 0;
			अगर (blk_no + hblks <= log->l_logBBsize) अणु
				/* Read header in one पढ़ो */
				error = xlog_bपढ़ो(log, blk_no, hblks, hbp,
						   &offset);
				अगर (error)
					जाओ bपढ़ो_err2;
			पूर्ण अन्यथा अणु
				/* This LR is split across physical log end */
				अगर (blk_no != log->l_logBBsize) अणु
					/* some data beक्रमe physical log end */
					ASSERT(blk_no <= पूर्णांक_उच्च);
					split_hblks = log->l_logBBsize - (पूर्णांक)blk_no;
					ASSERT(split_hblks > 0);
					error = xlog_bपढ़ो(log, blk_no,
							   split_hblks, hbp,
							   &offset);
					अगर (error)
						जाओ bपढ़ो_err2;
				पूर्ण

				/*
				 * Note: this black magic still works with
				 * large sector sizes (non-512) only because:
				 * - we increased the buffer size originally
				 *   by 1 sector giving us enough extra space
				 *   क्रम the second पढ़ो;
				 * - the log start is guaranteed to be sector
				 *   aligned;
				 * - we पढ़ो the log end (LR header start)
				 *   _first_, then the log start (LR header end)
				 *   - order is important.
				 */
				wrapped_hblks = hblks - split_hblks;
				error = xlog_bपढ़ो_noalign(log, 0,
						wrapped_hblks,
						offset + BBTOB(split_hblks));
				अगर (error)
					जाओ bपढ़ो_err2;
			पूर्ण
			rhead = (xlog_rec_header_t *)offset;
			error = xlog_valid_rec_header(log, rhead,
					split_hblks ? blk_no : 0, h_size);
			अगर (error)
				जाओ bपढ़ो_err2;

			bblks = (पूर्णांक)BTOBB(be32_to_cpu(rhead->h_len));
			blk_no += hblks;

			/*
			 * Read the log record data in multiple पढ़ोs अगर it
			 * wraps around the end of the log. Note that अगर the
			 * header alपढ़ोy wrapped, blk_no could poपूर्णांक past the
			 * end of the log. The record data is contiguous in
			 * that हाल.
			 */
			अगर (blk_no + bblks <= log->l_logBBsize ||
			    blk_no >= log->l_logBBsize) अणु
				rblk_no = xlog_wrap_logbno(log, blk_no);
				error = xlog_bपढ़ो(log, rblk_no, bblks, dbp,
						   &offset);
				अगर (error)
					जाओ bपढ़ो_err2;
			पूर्ण अन्यथा अणु
				/* This log record is split across the
				 * physical end of log */
				offset = dbp;
				split_bblks = 0;
				अगर (blk_no != log->l_logBBsize) अणु
					/* some data is beक्रमe the physical
					 * end of log */
					ASSERT(!wrapped_hblks);
					ASSERT(blk_no <= पूर्णांक_उच्च);
					split_bblks =
						log->l_logBBsize - (पूर्णांक)blk_no;
					ASSERT(split_bblks > 0);
					error = xlog_bपढ़ो(log, blk_no,
							split_bblks, dbp,
							&offset);
					अगर (error)
						जाओ bपढ़ो_err2;
				पूर्ण

				/*
				 * Note: this black magic still works with
				 * large sector sizes (non-512) only because:
				 * - we increased the buffer size originally
				 *   by 1 sector giving us enough extra space
				 *   क्रम the second पढ़ो;
				 * - the log start is guaranteed to be sector
				 *   aligned;
				 * - we पढ़ो the log end (LR header start)
				 *   _first_, then the log start (LR header end)
				 *   - order is important.
				 */
				error = xlog_bपढ़ो_noalign(log, 0,
						bblks - split_bblks,
						offset + BBTOB(split_bblks));
				अगर (error)
					जाओ bपढ़ो_err2;
			पूर्ण

			error = xlog_recover_process(log, rhash, rhead, offset,
						     pass, &buffer_list);
			अगर (error)
				जाओ bपढ़ो_err2;

			blk_no += bblks;
			rhead_blk = blk_no;
		पूर्ण

		ASSERT(blk_no >= log->l_logBBsize);
		blk_no -= log->l_logBBsize;
		rhead_blk = blk_no;
	पूर्ण

	/* पढ़ो first part of physical log */
	जबतक (blk_no < head_blk) अणु
		error = xlog_bपढ़ो(log, blk_no, hblks, hbp, &offset);
		अगर (error)
			जाओ bपढ़ो_err2;

		rhead = (xlog_rec_header_t *)offset;
		error = xlog_valid_rec_header(log, rhead, blk_no, h_size);
		अगर (error)
			जाओ bपढ़ो_err2;

		/* blocks in data section */
		bblks = (पूर्णांक)BTOBB(be32_to_cpu(rhead->h_len));
		error = xlog_bपढ़ो(log, blk_no+hblks, bblks, dbp,
				   &offset);
		अगर (error)
			जाओ bपढ़ो_err2;

		error = xlog_recover_process(log, rhash, rhead, offset, pass,
					     &buffer_list);
		अगर (error)
			जाओ bपढ़ो_err2;

		blk_no += bblks + hblks;
		rhead_blk = blk_no;
	पूर्ण

 bपढ़ो_err2:
	kmem_मुक्त(dbp);
 bपढ़ो_err1:
	kmem_मुक्त(hbp);

	/*
	 * Submit buffers that have been added from the last record processed,
	 * regardless of error status.
	 */
	अगर (!list_empty(&buffer_list))
		error2 = xfs_buf_delwri_submit(&buffer_list);

	अगर (error && first_bad)
		*first_bad = rhead_blk;

	/*
	 * Transactions are मुक्तd at commit समय but transactions without commit
	 * records on disk are never committed. Free any that may be left in the
	 * hash table.
	 */
	क्रम (i = 0; i < XLOG_RHASH_SIZE; i++) अणु
		काष्ठा hlist_node	*पंचांगp;
		काष्ठा xlog_recover	*trans;

		hlist_क्रम_each_entry_safe(trans, पंचांगp, &rhash[i], r_list)
			xlog_recover_मुक्त_trans(trans);
	पूर्ण

	वापस error ? error : error2;
पूर्ण

/*
 * Do the recovery of the log.  We actually करो this in two phases.
 * The two passes are necessary in order to implement the function
 * of cancelling a record written पूर्णांकo the log.  The first pass
 * determines those things which have been cancelled, and the
 * second pass replays log items normally except क्रम those which
 * have been cancelled.  The handling of the replay and cancellations
 * takes place in the log item type specअगरic routines.
 *
 * The table of items which have cancel records in the log is allocated
 * and मुक्तd at this level, since only here करो we know when all of
 * the log recovery has been completed.
 */
STATIC पूर्णांक
xlog_करो_log_recovery(
	काष्ठा xlog	*log,
	xfs_daddr_t	head_blk,
	xfs_daddr_t	tail_blk)
अणु
	पूर्णांक		error, i;

	ASSERT(head_blk != tail_blk);

	/*
	 * First करो a pass to find all of the cancelled buf log items.
	 * Store them in the buf_cancel_table क्रम use in the second pass.
	 */
	log->l_buf_cancel_table = kmem_zalloc(XLOG_BC_TABLE_SIZE *
						 माप(काष्ठा list_head),
						 0);
	क्रम (i = 0; i < XLOG_BC_TABLE_SIZE; i++)
		INIT_LIST_HEAD(&log->l_buf_cancel_table[i]);

	error = xlog_करो_recovery_pass(log, head_blk, tail_blk,
				      XLOG_RECOVER_PASS1, शून्य);
	अगर (error != 0) अणु
		kmem_मुक्त(log->l_buf_cancel_table);
		log->l_buf_cancel_table = शून्य;
		वापस error;
	पूर्ण
	/*
	 * Then करो a second pass to actually recover the items in the log.
	 * When it is complete मुक्त the table of buf cancel items.
	 */
	error = xlog_करो_recovery_pass(log, head_blk, tail_blk,
				      XLOG_RECOVER_PASS2, शून्य);
#अगर_घोषित DEBUG
	अगर (!error) अणु
		पूर्णांक	i;

		क्रम (i = 0; i < XLOG_BC_TABLE_SIZE; i++)
			ASSERT(list_empty(&log->l_buf_cancel_table[i]));
	पूर्ण
#पूर्ण_अगर	/* DEBUG */

	kmem_मुक्त(log->l_buf_cancel_table);
	log->l_buf_cancel_table = शून्य;

	वापस error;
पूर्ण

/*
 * Do the actual recovery
 */
STATIC पूर्णांक
xlog_करो_recover(
	काष्ठा xlog		*log,
	xfs_daddr_t		head_blk,
	xfs_daddr_t		tail_blk)
अणु
	काष्ठा xfs_mount	*mp = log->l_mp;
	काष्ठा xfs_buf		*bp = mp->m_sb_bp;
	काष्ठा xfs_sb		*sbp = &mp->m_sb;
	पूर्णांक			error;

	trace_xfs_log_recover(log, head_blk, tail_blk);

	/*
	 * First replay the images in the log.
	 */
	error = xlog_करो_log_recovery(log, head_blk, tail_blk);
	अगर (error)
		वापस error;

	/*
	 * If IO errors happened during recovery, bail out.
	 */
	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	/*
	 * We now update the tail_lsn since much of the recovery has completed
	 * and there may be space available to use.  If there were no extent
	 * or iunlinks, we can मुक्त up the entire log and set the tail_lsn to
	 * be the last_sync_lsn.  This was set in xlog_find_tail to be the
	 * lsn of the last known good LR on disk.  If there are extent मुक्तs
	 * or iunlinks they will have some entries in the AIL; so we look at
	 * the AIL to determine how to set the tail_lsn.
	 */
	xlog_assign_tail_lsn(mp);

	/*
	 * Now that we've finished replaying all buffer and inode updates,
	 * re-पढ़ो the superblock and reverअगरy it.
	 */
	xfs_buf_lock(bp);
	xfs_buf_hold(bp);
	error = _xfs_buf_पढ़ो(bp, XBF_READ);
	अगर (error) अणु
		अगर (!XFS_FORCED_SHUTDOWN(mp)) अणु
			xfs_buf_ioerror_alert(bp, __this_address);
			ASSERT(0);
		पूर्ण
		xfs_buf_rअन्यथा(bp);
		वापस error;
	पूर्ण

	/* Convert superblock from on-disk क्रमmat */
	xfs_sb_from_disk(sbp, bp->b_addr);
	xfs_buf_rअन्यथा(bp);

	/* re-initialise in-core superblock and geometry काष्ठाures */
	xfs_reinit_percpu_counters(mp);
	error = xfs_initialize_perag(mp, sbp->sb_agcount, &mp->m_maxagi);
	अगर (error) अणु
		xfs_warn(mp, "Failed post-recovery per-ag init: %d", error);
		वापस error;
	पूर्ण
	mp->m_alloc_set_aside = xfs_alloc_set_aside(mp);

	xlog_recover_check_summary(log);

	/* Normal transactions can now occur */
	log->l_flags &= ~XLOG_ACTIVE_RECOVERY;
	वापस 0;
पूर्ण

/*
 * Perक्रमm recovery and re-initialize some log variables in xlog_find_tail.
 *
 * Return error or zero.
 */
पूर्णांक
xlog_recover(
	काष्ठा xlog	*log)
अणु
	xfs_daddr_t	head_blk, tail_blk;
	पूर्णांक		error;

	/* find the tail of the log */
	error = xlog_find_tail(log, &head_blk, &tail_blk);
	अगर (error)
		वापस error;

	/*
	 * The superblock was पढ़ो beक्रमe the log was available and thus the LSN
	 * could not be verअगरied. Check the superblock LSN against the current
	 * LSN now that it's known.
	 */
	अगर (xfs_sb_version_hascrc(&log->l_mp->m_sb) &&
	    !xfs_log_check_lsn(log->l_mp, log->l_mp->m_sb.sb_lsn))
		वापस -EINVAL;

	अगर (tail_blk != head_blk) अणु
		/* There used to be a comment here:
		 *
		 * disallow recovery on पढ़ो-only mounts.  note -- mount
		 * checks क्रम ENOSPC and turns it पूर्णांकo an पूर्णांकelligent
		 * error message.
		 * ...but this is no दीर्घer true.  Now, unless you specअगरy
		 * NORECOVERY (in which हाल this function would never be
		 * called), we just go ahead and recover.  We करो this all
		 * under the vfs layer, so we can get away with it unless
		 * the device itself is पढ़ो-only, in which हाल we fail.
		 */
		अगर ((error = xfs_dev_is_पढ़ो_only(log->l_mp, "recovery"))) अणु
			वापस error;
		पूर्ण

		/*
		 * Version 5 superblock log feature mask validation. We know the
		 * log is dirty so check अगर there are any unknown log features
		 * in what we need to recover. If there are unknown features
		 * (e.g. unsupported transactions, then simply reject the
		 * attempt at recovery beक्रमe touching anything.
		 */
		अगर (XFS_SB_VERSION_NUM(&log->l_mp->m_sb) == XFS_SB_VERSION_5 &&
		    xfs_sb_has_incompat_log_feature(&log->l_mp->m_sb,
					XFS_SB_FEAT_INCOMPAT_LOG_UNKNOWN)) अणु
			xfs_warn(log->l_mp,
"Superblock has unknown incompatible log features (0x%x) enabled.",
				(log->l_mp->m_sb.sb_features_log_incompat &
					XFS_SB_FEAT_INCOMPAT_LOG_UNKNOWN));
			xfs_warn(log->l_mp,
"The log can not be fully and/or safely recovered by this kernel.");
			xfs_warn(log->l_mp,
"Please recover the log on a kernel that supports the unknown features.");
			वापस -EINVAL;
		पूर्ण

		/*
		 * Delay log recovery अगर the debug hook is set. This is debug
		 * instrumentation to coordinate simulation of I/O failures with
		 * log recovery.
		 */
		अगर (xfs_globals.log_recovery_delay) अणु
			xfs_notice(log->l_mp,
				"Delaying log recovery for %d seconds.",
				xfs_globals.log_recovery_delay);
			msleep(xfs_globals.log_recovery_delay * 1000);
		पूर्ण

		xfs_notice(log->l_mp, "Starting recovery (logdev: %s)",
				log->l_mp->m_logname ? log->l_mp->m_logname
						     : "internal");

		error = xlog_करो_recover(log, head_blk, tail_blk);
		log->l_flags |= XLOG_RECOVERY_NEEDED;
	पूर्ण
	वापस error;
पूर्ण

/*
 * In the first part of recovery we replay inodes and buffers and build
 * up the list of extent मुक्त items which need to be processed.  Here
 * we process the extent मुक्त items and clean up the on disk unlinked
 * inode lists.  This is separated from the first part of recovery so
 * that the root and real-समय biपंचांगap inodes can be पढ़ो in from disk in
 * between the two stages.  This is necessary so that we can मुक्त space
 * in the real-समय portion of the file प्रणाली.
 */
पूर्णांक
xlog_recover_finish(
	काष्ठा xlog	*log)
अणु
	/*
	 * Now we're पढ़ोy to करो the transactions needed क्रम the
	 * rest of recovery.  Start with completing all the extent
	 * मुक्त पूर्णांकent records and then process the unlinked inode
	 * lists.  At this poपूर्णांक, we essentially run in normal mode
	 * except that we're still perक्रमming recovery actions
	 * rather than accepting new requests.
	 */
	अगर (log->l_flags & XLOG_RECOVERY_NEEDED) अणु
		पूर्णांक	error;
		error = xlog_recover_process_पूर्णांकents(log);
		अगर (error) अणु
			/*
			 * Cancel all the unprocessed पूर्णांकent items now so that
			 * we करोn't leave them pinned in the AIL.  This can
			 * cause the AIL to livelock on the pinned item अगर
			 * anyone tries to push the AIL (inode reclaim करोes
			 * this) beक्रमe we get around to xfs_log_mount_cancel.
			 */
			xlog_recover_cancel_पूर्णांकents(log);
			xfs_alert(log->l_mp, "Failed to recover intents");
			वापस error;
		पूर्ण

		/*
		 * Sync the log to get all the पूर्णांकents out of the AIL.
		 * This isn't असलolutely necessary, but it helps in
		 * हाल the unlink transactions would have problems
		 * pushing the पूर्णांकents out of the way.
		 */
		xfs_log_क्रमce(log->l_mp, XFS_LOG_SYNC);

		xlog_recover_process_iunlinks(log);

		xlog_recover_check_summary(log);

		xfs_notice(log->l_mp, "Ending recovery (logdev: %s)",
				log->l_mp->m_logname ? log->l_mp->m_logname
						     : "internal");
		log->l_flags &= ~XLOG_RECOVERY_NEEDED;
	पूर्ण अन्यथा अणु
		xfs_info(log->l_mp, "Ending clean mount");
	पूर्ण
	वापस 0;
पूर्ण

व्योम
xlog_recover_cancel(
	काष्ठा xlog	*log)
अणु
	अगर (log->l_flags & XLOG_RECOVERY_NEEDED)
		xlog_recover_cancel_पूर्णांकents(log);
पूर्ण

#अगर defined(DEBUG)
/*
 * Read all of the agf and agi counters and check that they
 * are consistent with the superblock counters.
 */
STATIC व्योम
xlog_recover_check_summary(
	काष्ठा xlog	*log)
अणु
	xfs_mount_t	*mp;
	काष्ठा xfs_buf	*agfbp;
	काष्ठा xfs_buf	*agibp;
	xfs_agnumber_t	agno;
	uपूर्णांक64_t	मुक्तblks;
	uपूर्णांक64_t	itotal;
	uपूर्णांक64_t	अगरree;
	पूर्णांक		error;

	mp = log->l_mp;

	मुक्तblks = 0LL;
	itotal = 0LL;
	अगरree = 0LL;
	क्रम (agno = 0; agno < mp->m_sb.sb_agcount; agno++) अणु
		error = xfs_पढ़ो_agf(mp, शून्य, agno, 0, &agfbp);
		अगर (error) अणु
			xfs_alert(mp, "%s agf read failed agno %d error %d",
						__func__, agno, error);
		पूर्ण अन्यथा अणु
			काष्ठा xfs_agf	*agfp = agfbp->b_addr;

			मुक्तblks += be32_to_cpu(agfp->agf_मुक्तblks) +
				    be32_to_cpu(agfp->agf_flcount);
			xfs_buf_rअन्यथा(agfbp);
		पूर्ण

		error = xfs_पढ़ो_agi(mp, शून्य, agno, &agibp);
		अगर (error) अणु
			xfs_alert(mp, "%s agi read failed agno %d error %d",
						__func__, agno, error);
		पूर्ण अन्यथा अणु
			काष्ठा xfs_agi	*agi = agibp->b_addr;

			itotal += be32_to_cpu(agi->agi_count);
			अगरree += be32_to_cpu(agi->agi_मुक्तcount);
			xfs_buf_rअन्यथा(agibp);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* DEBUG */
