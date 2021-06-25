<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2019 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_ialloc.h"
#समावेश "xfs_ialloc_btree.h"
#समावेश "xfs_iwalk.h"
#समावेश "xfs_error.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_health.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_pwork.h"

/*
 * Walking Inodes in the Fileप्रणाली
 * ================================
 *
 * This iterator function walks a subset of fileप्रणाली inodes in increasing
 * order from @startino until there are no more inodes.  For each allocated
 * inode it finds, it calls a walk function with the relevant inode number and
 * a poपूर्णांकer to caller-provided data.  The walk function can वापस the usual
 * negative error code to stop the iteration; 0 to जारी the iteration; or
 * -ECANCELED to stop the iteration.  This वापस value is वापसed to the
 * caller.
 *
 * Internally, we allow the walk function to करो anything, which means that we
 * cannot मुख्यtain the inobt cursor or our lock on the AGI buffer.  We
 * thereक्रमe cache the inobt records in kernel memory and only call the walk
 * function when our memory buffer is full.  @nr_recs is the number of records
 * that we've cached, and @sz_recs is the size of our cache.
 *
 * It is the responsibility of the walk function to ensure it accesses
 * allocated inodes, as the inobt records may be stale by the समय they are
 * acted upon.
 */

काष्ठा xfs_iwalk_ag अणु
	/* parallel work control data; will be null अगर single thपढ़ोed */
	काष्ठा xfs_pwork		pwork;

	काष्ठा xfs_mount		*mp;
	काष्ठा xfs_trans		*tp;

	/* Where करो we start the traversal? */
	xfs_ino_t			startino;

	/* What was the last inode number we saw when iterating the inobt? */
	xfs_ino_t			lastino;

	/* Array of inobt records we cache. */
	काष्ठा xfs_inobt_rec_incore	*recs;

	/* Number of entries allocated क्रम the @recs array. */
	अचिन्हित पूर्णांक			sz_recs;

	/* Number of entries in the @recs array that are in use. */
	अचिन्हित पूर्णांक			nr_recs;

	/* Inode walk function and data poपूर्णांकer. */
	xfs_iwalk_fn			iwalk_fn;
	xfs_inobt_walk_fn		inobt_walk_fn;
	व्योम				*data;

	/*
	 * Make it look like the inodes up to startino are मुक्त so that
	 * bulkstat can start its inode iteration at the correct place without
	 * needing to special हाल everywhere.
	 */
	अचिन्हित पूर्णांक			trim_start:1;

	/* Skip empty inobt records? */
	अचिन्हित पूर्णांक			skip_empty:1;
पूर्ण;

/*
 * Loop over all clusters in a chunk क्रम a given incore inode allocation btree
 * record.  Do a पढ़ोahead अगर there are any allocated inodes in that cluster.
 */
STATIC व्योम
xfs_iwalk_ichunk_ra(
	काष्ठा xfs_mount		*mp,
	xfs_agnumber_t			agno,
	काष्ठा xfs_inobt_rec_incore	*irec)
अणु
	काष्ठा xfs_ino_geometry		*igeo = M_IGEO(mp);
	xfs_agblock_t			agbno;
	काष्ठा blk_plug			plug;
	पूर्णांक				i;	/* inode chunk index */

	agbno = XFS_AGINO_TO_AGBNO(mp, irec->ir_startino);

	blk_start_plug(&plug);
	क्रम (i = 0; i < XFS_INODES_PER_CHUNK; i += igeo->inodes_per_cluster) अणु
		xfs_inoमुक्त_t	imask;

		imask = xfs_inobt_maskn(i, igeo->inodes_per_cluster);
		अगर (imask & ~irec->ir_मुक्त) अणु
			xfs_btree_पढ़ोa_bufs(mp, agno, agbno,
					igeo->blocks_per_cluster,
					&xfs_inode_buf_ops);
		पूर्ण
		agbno += igeo->blocks_per_cluster;
	पूर्ण
	blk_finish_plug(&plug);
पूर्ण

/*
 * Set the bits in @irec's मुक्त mask that correspond to the inodes beक्रमe
 * @agino so that we skip them.  This is how we restart an inode walk that was
 * पूर्णांकerrupted in the middle of an inode record.
 */
STATIC व्योम
xfs_iwalk_adjust_start(
	xfs_agino_t			agino,	/* starting inode of chunk */
	काष्ठा xfs_inobt_rec_incore	*irec)	/* btree record */
अणु
	पूर्णांक				idx;	/* index पूर्णांकo inode chunk */
	पूर्णांक				i;

	idx = agino - irec->ir_startino;

	/*
	 * We got a right chunk with some left inodes allocated at it.  Grab
	 * the chunk record.  Mark all the unपूर्णांकeresting inodes मुक्त because
	 * they're beक्रमe our start poपूर्णांक.
	 */
	क्रम (i = 0; i < idx; i++) अणु
		अगर (XFS_INOBT_MASK(i) & ~irec->ir_मुक्त)
			irec->ir_मुक्तcount++;
	पूर्ण

	irec->ir_मुक्त |= xfs_inobt_maskn(0, idx);
पूर्ण

/* Allocate memory क्रम a walk. */
STATIC पूर्णांक
xfs_iwalk_alloc(
	काष्ठा xfs_iwalk_ag	*iwag)
अणु
	माप_प्रकार			size;

	ASSERT(iwag->recs == शून्य);
	iwag->nr_recs = 0;

	/* Allocate a prefetch buffer क्रम inobt records. */
	size = iwag->sz_recs * माप(काष्ठा xfs_inobt_rec_incore);
	iwag->recs = kmem_alloc(size, KM_MAYFAIL);
	अगर (iwag->recs == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/* Free memory we allocated क्रम a walk. */
STATIC व्योम
xfs_iwalk_मुक्त(
	काष्ठा xfs_iwalk_ag	*iwag)
अणु
	kmem_मुक्त(iwag->recs);
	iwag->recs = शून्य;
पूर्ण

/* For each inuse inode in each cached inobt record, call our function. */
STATIC पूर्णांक
xfs_iwalk_ag_recs(
	काष्ठा xfs_iwalk_ag		*iwag)
अणु
	काष्ठा xfs_mount		*mp = iwag->mp;
	काष्ठा xfs_trans		*tp = iwag->tp;
	xfs_ino_t			ino;
	अचिन्हित पूर्णांक			i, j;
	xfs_agnumber_t			agno;
	पूर्णांक				error;

	agno = XFS_INO_TO_AGNO(mp, iwag->startino);
	क्रम (i = 0; i < iwag->nr_recs; i++) अणु
		काष्ठा xfs_inobt_rec_incore	*irec = &iwag->recs[i];

		trace_xfs_iwalk_ag_rec(mp, agno, irec);

		अगर (xfs_pwork_want_पात(&iwag->pwork))
			वापस 0;

		अगर (iwag->inobt_walk_fn) अणु
			error = iwag->inobt_walk_fn(mp, tp, agno, irec,
					iwag->data);
			अगर (error)
				वापस error;
		पूर्ण

		अगर (!iwag->iwalk_fn)
			जारी;

		क्रम (j = 0; j < XFS_INODES_PER_CHUNK; j++) अणु
			अगर (xfs_pwork_want_पात(&iwag->pwork))
				वापस 0;

			/* Skip अगर this inode is मुक्त */
			अगर (XFS_INOBT_MASK(j) & irec->ir_मुक्त)
				जारी;

			/* Otherwise call our function. */
			ino = XFS_AGINO_TO_INO(mp, agno, irec->ir_startino + j);
			error = iwag->iwalk_fn(mp, tp, ino, iwag->data);
			अगर (error)
				वापस error;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Delete cursor and let go of AGI. */
अटल अंतरभूत व्योम
xfs_iwalk_del_inobt(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_btree_cur	**curpp,
	काष्ठा xfs_buf		**agi_bpp,
	पूर्णांक			error)
अणु
	अगर (*curpp) अणु
		xfs_btree_del_cursor(*curpp, error);
		*curpp = शून्य;
	पूर्ण
	अगर (*agi_bpp) अणु
		xfs_trans_brअन्यथा(tp, *agi_bpp);
		*agi_bpp = शून्य;
	पूर्ण
पूर्ण

/*
 * Set ourselves up क्रम walking inobt records starting from a given poपूर्णांक in
 * the fileप्रणाली.
 *
 * If caller passed in a nonzero start inode number, load the record from the
 * inobt and make the record look like all the inodes beक्रमe agino are मुक्त so
 * that we skip them, and then move the cursor to the next inobt record.  This
 * is how we support starting an iwalk in the middle of an inode chunk.
 *
 * If the caller passed in a start number of zero, move the cursor to the first
 * inobt record.
 *
 * The caller is responsible क्रम cleaning up the cursor and buffer poपूर्णांकer
 * regardless of the error status.
 */
STATIC पूर्णांक
xfs_iwalk_ag_start(
	काष्ठा xfs_iwalk_ag	*iwag,
	xfs_agnumber_t		agno,
	xfs_agino_t		agino,
	काष्ठा xfs_btree_cur	**curpp,
	काष्ठा xfs_buf		**agi_bpp,
	पूर्णांक			*has_more)
अणु
	काष्ठा xfs_mount	*mp = iwag->mp;
	काष्ठा xfs_trans	*tp = iwag->tp;
	काष्ठा xfs_inobt_rec_incore *irec;
	पूर्णांक			error;

	/* Set up a fresh cursor and empty the inobt cache. */
	iwag->nr_recs = 0;
	error = xfs_inobt_cur(mp, tp, agno, XFS_BTNUM_INO, curpp, agi_bpp);
	अगर (error)
		वापस error;

	/* Starting at the beginning of the AG?  That's easy! */
	अगर (agino == 0)
		वापस xfs_inobt_lookup(*curpp, 0, XFS_LOOKUP_GE, has_more);

	/*
	 * Otherwise, we have to grab the inobt record where we left off, stuff
	 * the record पूर्णांकo our cache, and then see अगर there are more records.
	 * We require a lookup cache of at least two elements so that the
	 * caller करोesn't have to deal with tearing करोwn the cursor to walk the
	 * records.
	 */
	error = xfs_inobt_lookup(*curpp, agino, XFS_LOOKUP_LE, has_more);
	अगर (error)
		वापस error;

	/*
	 * If the LE lookup at @agino yields no records, jump ahead to the
	 * inobt cursor increment to see अगर there are more records to process.
	 */
	अगर (!*has_more)
		जाओ out_advance;

	/* Get the record, should always work */
	irec = &iwag->recs[iwag->nr_recs];
	error = xfs_inobt_get_rec(*curpp, irec, has_more);
	अगर (error)
		वापस error;
	अगर (XFS_IS_CORRUPT(mp, *has_more != 1))
		वापस -EFSCORRUPTED;

	iwag->lastino = XFS_AGINO_TO_INO(mp, agno,
				irec->ir_startino + XFS_INODES_PER_CHUNK - 1);

	/*
	 * If the LE lookup yielded an inobt record beक्रमe the cursor position,
	 * skip it and see अगर there's another one after it.
	 */
	अगर (irec->ir_startino + XFS_INODES_PER_CHUNK <= agino)
		जाओ out_advance;

	/*
	 * If agino fell in the middle of the inode record, make it look like
	 * the inodes up to agino are मुक्त so that we करोn't वापस them again.
	 */
	अगर (iwag->trim_start)
		xfs_iwalk_adjust_start(agino, irec);

	/*
	 * The prefetch calculation is supposed to give us a large enough inobt
	 * record cache that grab_ichunk can stage a partial first record and
	 * the loop body can cache a record without having to check क्रम cache
	 * space until after it पढ़ोs an inobt record.
	 */
	iwag->nr_recs++;
	ASSERT(iwag->nr_recs < iwag->sz_recs);

out_advance:
	वापस xfs_btree_increment(*curpp, 0, has_more);
पूर्ण

/*
 * The inobt record cache is full, so preserve the inobt cursor state and
 * run callbacks on the cached inobt records.  When we're करोne, restore the
 * cursor state to wherever the cursor would have been had the cache not been
 * full (and thereक्रमe we could've just incremented the cursor) अगर *@has_more
 * is true.  On निकास, *@has_more will indicate whether or not the caller should
 * try क्रम more inode records.
 */
STATIC पूर्णांक
xfs_iwalk_run_callbacks(
	काष्ठा xfs_iwalk_ag		*iwag,
	xfs_agnumber_t			agno,
	काष्ठा xfs_btree_cur		**curpp,
	काष्ठा xfs_buf			**agi_bpp,
	पूर्णांक				*has_more)
अणु
	काष्ठा xfs_mount		*mp = iwag->mp;
	काष्ठा xfs_trans		*tp = iwag->tp;
	काष्ठा xfs_inobt_rec_incore	*irec;
	xfs_agino_t			next_agino;
	पूर्णांक				error;

	next_agino = XFS_INO_TO_AGINO(mp, iwag->lastino) + 1;

	ASSERT(iwag->nr_recs > 0);

	/* Delete cursor but remember the last record we cached... */
	xfs_iwalk_del_inobt(tp, curpp, agi_bpp, 0);
	irec = &iwag->recs[iwag->nr_recs - 1];
	ASSERT(next_agino >= irec->ir_startino + XFS_INODES_PER_CHUNK);

	error = xfs_iwalk_ag_recs(iwag);
	अगर (error)
		वापस error;

	/* ...empty the cache... */
	iwag->nr_recs = 0;

	अगर (!has_more)
		वापस 0;

	/* ...and recreate the cursor just past where we left off. */
	error = xfs_inobt_cur(mp, tp, agno, XFS_BTNUM_INO, curpp, agi_bpp);
	अगर (error)
		वापस error;

	वापस xfs_inobt_lookup(*curpp, next_agino, XFS_LOOKUP_GE, has_more);
पूर्ण

/* Walk all inodes in a single AG, from @iwag->startino to the end of the AG. */
STATIC पूर्णांक
xfs_iwalk_ag(
	काष्ठा xfs_iwalk_ag		*iwag)
अणु
	काष्ठा xfs_mount		*mp = iwag->mp;
	काष्ठा xfs_trans		*tp = iwag->tp;
	काष्ठा xfs_buf			*agi_bp = शून्य;
	काष्ठा xfs_btree_cur		*cur = शून्य;
	xfs_agnumber_t			agno;
	xfs_agino_t			agino;
	पूर्णांक				has_more;
	पूर्णांक				error = 0;

	/* Set up our cursor at the right place in the inode btree. */
	agno = XFS_INO_TO_AGNO(mp, iwag->startino);
	agino = XFS_INO_TO_AGINO(mp, iwag->startino);
	error = xfs_iwalk_ag_start(iwag, agno, agino, &cur, &agi_bp, &has_more);

	जबतक (!error && has_more) अणु
		काष्ठा xfs_inobt_rec_incore	*irec;
		xfs_ino_t			rec_fsino;

		cond_resched();
		अगर (xfs_pwork_want_पात(&iwag->pwork))
			जाओ out;

		/* Fetch the inobt record. */
		irec = &iwag->recs[iwag->nr_recs];
		error = xfs_inobt_get_rec(cur, irec, &has_more);
		अगर (error || !has_more)
			अवरोध;

		/* Make sure that we always move क्रमward. */
		rec_fsino = XFS_AGINO_TO_INO(mp, agno, irec->ir_startino);
		अगर (iwag->lastino != शून्यFSINO &&
		    XFS_IS_CORRUPT(mp, iwag->lastino >= rec_fsino)) अणु
			error = -EFSCORRUPTED;
			जाओ out;
		पूर्ण
		iwag->lastino = rec_fsino + XFS_INODES_PER_CHUNK - 1;

		/* No allocated inodes in this chunk; skip it. */
		अगर (iwag->skip_empty && irec->ir_मुक्तcount == irec->ir_count) अणु
			error = xfs_btree_increment(cur, 0, &has_more);
			अगर (error)
				अवरोध;
			जारी;
		पूर्ण

		/*
		 * Start पढ़ोahead क्रम this inode chunk in anticipation of
		 * walking the inodes.
		 */
		अगर (iwag->iwalk_fn)
			xfs_iwalk_ichunk_ra(mp, agno, irec);

		/*
		 * If there's space in the buffer क्रम more records, increment
		 * the btree cursor and grab more.
		 */
		अगर (++iwag->nr_recs < iwag->sz_recs) अणु
			error = xfs_btree_increment(cur, 0, &has_more);
			अगर (error || !has_more)
				अवरोध;
			जारी;
		पूर्ण

		/*
		 * Otherwise, we need to save cursor state and run the callback
		 * function on the cached records.  The run_callbacks function
		 * is supposed to वापस a cursor poपूर्णांकing to the record where
		 * we would be अगर we had been able to increment like above.
		 */
		ASSERT(has_more);
		error = xfs_iwalk_run_callbacks(iwag, agno, &cur, &agi_bp,
				&has_more);
	पूर्ण

	अगर (iwag->nr_recs == 0 || error)
		जाओ out;

	/* Walk the unprocessed records in the cache. */
	error = xfs_iwalk_run_callbacks(iwag, agno, &cur, &agi_bp, &has_more);

out:
	xfs_iwalk_del_inobt(tp, &cur, &agi_bp, error);
	वापस error;
पूर्ण

/*
 * We experimentally determined that the reduction in ioctl call overhead
 * diminishes when userspace asks क्रम more than 2048 inodes, so we'll cap
 * prefetch at this poपूर्णांक.
 */
#घोषणा IWALK_MAX_INODE_PREFETCH	(2048U)

/*
 * Given the number of inodes to prefetch, set the number of inobt records that
 * we cache in memory, which controls the number of inodes we try to पढ़ो
 * ahead.  Set the maximum अगर @inodes == 0.
 */
अटल अंतरभूत अचिन्हित पूर्णांक
xfs_iwalk_prefetch(
	अचिन्हित पूर्णांक		inodes)
अणु
	अचिन्हित पूर्णांक		inobt_records;

	/*
	 * If the caller didn't tell us the number of inodes they wanted,
	 * assume the maximum prefetch possible क्रम best perक्रमmance.
	 * Otherwise, cap prefetch at that maximum so that we करोn't start an
	 * असलurd amount of prefetch.
	 */
	अगर (inodes == 0)
		inodes = IWALK_MAX_INODE_PREFETCH;
	inodes = min(inodes, IWALK_MAX_INODE_PREFETCH);

	/* Round the inode count up to a full chunk. */
	inodes = round_up(inodes, XFS_INODES_PER_CHUNK);

	/*
	 * In order to convert the number of inodes to prefetch पूर्णांकo an
	 * estimate of the number of inobt records to cache, we require a
	 * conversion factor that reflects our expectations of the average
	 * loading factor of an inode chunk.  Based on data gathered, most
	 * (but not all) fileप्रणालीs manage to keep the inode chunks totally
	 * full, so we'll underestimate slightly so that our पढ़ोahead will
	 * still deliver the perक्रमmance we want on aging fileप्रणालीs:
	 *
	 * inobt = inodes / (INODES_PER_CHUNK * (4 / 5));
	 *
	 * The funny math is to aव्योम पूर्णांकeger भागision.
	 */
	inobt_records = (inodes * 5) / (4 * XFS_INODES_PER_CHUNK);

	/*
	 * Allocate enough space to prefetch at least two inobt records so that
	 * we can cache both the record where the iwalk started and the next
	 * record.  This simplअगरies the AG inode walk loop setup code.
	 */
	वापस max(inobt_records, 2U);
पूर्ण

/*
 * Walk all inodes in the fileप्रणाली starting from @startino.  The @iwalk_fn
 * will be called क्रम each allocated inode, being passed the inode's number and
 * @data.  @max_prefetch controls how many inobt records' worth of inodes we
 * try to पढ़ोahead.
 */
पूर्णांक
xfs_iwalk(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	xfs_ino_t		startino,
	अचिन्हित पूर्णांक		flags,
	xfs_iwalk_fn		iwalk_fn,
	अचिन्हित पूर्णांक		inode_records,
	व्योम			*data)
अणु
	काष्ठा xfs_iwalk_ag	iwag = अणु
		.mp		= mp,
		.tp		= tp,
		.iwalk_fn	= iwalk_fn,
		.data		= data,
		.startino	= startino,
		.sz_recs	= xfs_iwalk_prefetch(inode_records),
		.trim_start	= 1,
		.skip_empty	= 1,
		.pwork		= XFS_PWORK_SINGLE_THREADED,
		.lastino	= शून्यFSINO,
	पूर्ण;
	xfs_agnumber_t		agno = XFS_INO_TO_AGNO(mp, startino);
	पूर्णांक			error;

	ASSERT(agno < mp->m_sb.sb_agcount);
	ASSERT(!(flags & ~XFS_IWALK_FLAGS_ALL));

	error = xfs_iwalk_alloc(&iwag);
	अगर (error)
		वापस error;

	क्रम (; agno < mp->m_sb.sb_agcount; agno++) अणु
		error = xfs_iwalk_ag(&iwag);
		अगर (error)
			अवरोध;
		iwag.startino = XFS_AGINO_TO_INO(mp, agno + 1, 0);
		अगर (flags & XFS_INOBT_WALK_SAME_AG)
			अवरोध;
	पूर्ण

	xfs_iwalk_मुक्त(&iwag);
	वापस error;
पूर्ण

/* Run per-thपढ़ो iwalk work. */
अटल पूर्णांक
xfs_iwalk_ag_work(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_pwork	*pwork)
अणु
	काष्ठा xfs_iwalk_ag	*iwag;
	पूर्णांक			error = 0;

	iwag = container_of(pwork, काष्ठा xfs_iwalk_ag, pwork);
	अगर (xfs_pwork_want_पात(pwork))
		जाओ out;

	error = xfs_iwalk_alloc(iwag);
	अगर (error)
		जाओ out;

	error = xfs_iwalk_ag(iwag);
	xfs_iwalk_मुक्त(iwag);
out:
	kmem_मुक्त(iwag);
	वापस error;
पूर्ण

/*
 * Walk all the inodes in the fileप्रणाली using multiple thपढ़ोs to process each
 * AG.
 */
पूर्णांक
xfs_iwalk_thपढ़ोed(
	काष्ठा xfs_mount	*mp,
	xfs_ino_t		startino,
	अचिन्हित पूर्णांक		flags,
	xfs_iwalk_fn		iwalk_fn,
	अचिन्हित पूर्णांक		inode_records,
	bool			polled,
	व्योम			*data)
अणु
	काष्ठा xfs_pwork_ctl	pctl;
	xfs_agnumber_t		agno = XFS_INO_TO_AGNO(mp, startino);
	पूर्णांक			error;

	ASSERT(agno < mp->m_sb.sb_agcount);
	ASSERT(!(flags & ~XFS_IWALK_FLAGS_ALL));

	error = xfs_pwork_init(mp, &pctl, xfs_iwalk_ag_work, "xfs_iwalk");
	अगर (error)
		वापस error;

	क्रम (; agno < mp->m_sb.sb_agcount; agno++) अणु
		काष्ठा xfs_iwalk_ag	*iwag;

		अगर (xfs_pwork_ctl_want_पात(&pctl))
			अवरोध;

		iwag = kmem_zalloc(माप(काष्ठा xfs_iwalk_ag), 0);
		iwag->mp = mp;
		iwag->iwalk_fn = iwalk_fn;
		iwag->data = data;
		iwag->startino = startino;
		iwag->sz_recs = xfs_iwalk_prefetch(inode_records);
		iwag->lastino = शून्यFSINO;
		xfs_pwork_queue(&pctl, &iwag->pwork);
		startino = XFS_AGINO_TO_INO(mp, agno + 1, 0);
		अगर (flags & XFS_INOBT_WALK_SAME_AG)
			अवरोध;
	पूर्ण

	अगर (polled)
		xfs_pwork_poll(&pctl);
	वापस xfs_pwork_destroy(&pctl);
पूर्ण

/*
 * Allow callers to cache up to a page's worth of inobt records.  This reflects
 * the existing inumbers prefetching behavior.  Since the inobt walk करोes not
 * itself करो anything with the inobt records, we can set a fairly high limit
 * here.
 */
#घोषणा MAX_INOBT_WALK_PREFETCH	\
	(PAGE_SIZE / माप(काष्ठा xfs_inobt_rec_incore))

/*
 * Given the number of records that the user wanted, set the number of inobt
 * records that we buffer in memory.  Set the maximum अगर @inobt_records == 0.
 */
अटल अंतरभूत अचिन्हित पूर्णांक
xfs_inobt_walk_prefetch(
	अचिन्हित पूर्णांक		inobt_records)
अणु
	/*
	 * If the caller didn't tell us the number of inobt records they
	 * wanted, assume the maximum prefetch possible क्रम best perक्रमmance.
	 */
	अगर (inobt_records == 0)
		inobt_records = MAX_INOBT_WALK_PREFETCH;

	/*
	 * Allocate enough space to prefetch at least two inobt records so that
	 * we can cache both the record where the iwalk started and the next
	 * record.  This simplअगरies the AG inode walk loop setup code.
	 */
	inobt_records = max(inobt_records, 2U);

	/*
	 * Cap prefetch at that maximum so that we करोn't use an असलurd amount
	 * of memory.
	 */
	वापस min_t(अचिन्हित पूर्णांक, inobt_records, MAX_INOBT_WALK_PREFETCH);
पूर्ण

/*
 * Walk all inode btree records in the fileप्रणाली starting from @startino.  The
 * @inobt_walk_fn will be called क्रम each btree record, being passed the incore
 * record and @data.  @max_prefetch controls how many inobt records we try to
 * cache ahead of समय.
 */
पूर्णांक
xfs_inobt_walk(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	xfs_ino_t		startino,
	अचिन्हित पूर्णांक		flags,
	xfs_inobt_walk_fn	inobt_walk_fn,
	अचिन्हित पूर्णांक		inobt_records,
	व्योम			*data)
अणु
	काष्ठा xfs_iwalk_ag	iwag = अणु
		.mp		= mp,
		.tp		= tp,
		.inobt_walk_fn	= inobt_walk_fn,
		.data		= data,
		.startino	= startino,
		.sz_recs	= xfs_inobt_walk_prefetch(inobt_records),
		.pwork		= XFS_PWORK_SINGLE_THREADED,
		.lastino	= शून्यFSINO,
	पूर्ण;
	xfs_agnumber_t		agno = XFS_INO_TO_AGNO(mp, startino);
	पूर्णांक			error;

	ASSERT(agno < mp->m_sb.sb_agcount);
	ASSERT(!(flags & ~XFS_INOBT_WALK_FLAGS_ALL));

	error = xfs_iwalk_alloc(&iwag);
	अगर (error)
		वापस error;

	क्रम (; agno < mp->m_sb.sb_agcount; agno++) अणु
		error = xfs_iwalk_ag(&iwag);
		अगर (error)
			अवरोध;
		iwag.startino = XFS_AGINO_TO_INO(mp, agno + 1, 0);
		अगर (flags & XFS_INOBT_WALK_SAME_AG)
			अवरोध;
	पूर्ण

	xfs_iwalk_मुक्त(&iwag);
	वापस error;
पूर्ण
