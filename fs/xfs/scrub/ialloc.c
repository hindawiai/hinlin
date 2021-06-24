<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_ialloc.h"
#समावेश "xfs_ialloc_btree.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_rmap.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/common.h"
#समावेश "scrub/btree.h"
#समावेश "scrub/trace.h"

/*
 * Set us up to scrub inode btrees.
 * If we detect a discrepancy between the inobt and the inode,
 * try again after क्रमcing logged inode cores out to disk.
 */
पूर्णांक
xchk_setup_ag_iallocbt(
	काष्ठा xfs_scrub	*sc)
अणु
	वापस xchk_setup_ag_btree(sc, sc->flags & XCHK_TRY_HARDER);
पूर्ण

/* Inode btree scrubber. */

काष्ठा xchk_iallocbt अणु
	/* Number of inodes we see जबतक scanning inobt. */
	अचिन्हित दीर्घ दीर्घ	inodes;

	/* Expected next startino, क्रम big block fileप्रणालीs. */
	xfs_agino_t		next_startino;

	/* Expected end of the current inode cluster. */
	xfs_agino_t		next_cluster_ino;
पूर्ण;

/*
 * If we're checking the finobt, cross-reference with the inobt.
 * Otherwise we're checking the inobt; अगर there is an finobt, make sure
 * we have a record or not depending on मुक्तcount.
 */
अटल अंतरभूत व्योम
xchk_iallocbt_chunk_xref_other(
	काष्ठा xfs_scrub		*sc,
	काष्ठा xfs_inobt_rec_incore	*irec,
	xfs_agino_t			agino)
अणु
	काष्ठा xfs_btree_cur		**pcur;
	bool				has_irec;
	पूर्णांक				error;

	अगर (sc->sm->sm_type == XFS_SCRUB_TYPE_FINOBT)
		pcur = &sc->sa.ino_cur;
	अन्यथा
		pcur = &sc->sa.fino_cur;
	अगर (!(*pcur))
		वापस;
	error = xfs_ialloc_has_inode_record(*pcur, agino, agino, &has_irec);
	अगर (!xchk_should_check_xref(sc, &error, pcur))
		वापस;
	अगर (((irec->ir_मुक्तcount > 0 && !has_irec) ||
	     (irec->ir_मुक्तcount == 0 && has_irec)))
		xchk_btree_xref_set_corrupt(sc, *pcur, 0);
पूर्ण

/* Cross-reference with the other btrees. */
STATIC व्योम
xchk_iallocbt_chunk_xref(
	काष्ठा xfs_scrub		*sc,
	काष्ठा xfs_inobt_rec_incore	*irec,
	xfs_agino_t			agino,
	xfs_agblock_t			agbno,
	xfs_extlen_t			len)
अणु
	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		वापस;

	xchk_xref_is_used_space(sc, agbno, len);
	xchk_iallocbt_chunk_xref_other(sc, irec, agino);
	xchk_xref_is_owned_by(sc, agbno, len, &XFS_RMAP_OINFO_INODES);
	xchk_xref_is_not_shared(sc, agbno, len);
पूर्ण

/* Is this chunk worth checking? */
STATIC bool
xchk_iallocbt_chunk(
	काष्ठा xchk_btree		*bs,
	काष्ठा xfs_inobt_rec_incore	*irec,
	xfs_agino_t			agino,
	xfs_extlen_t			len)
अणु
	काष्ठा xfs_mount		*mp = bs->cur->bc_mp;
	xfs_agnumber_t			agno = bs->cur->bc_ag.agno;
	xfs_agblock_t			bno;

	bno = XFS_AGINO_TO_AGBNO(mp, agino);
	अगर (bno + len <= bno ||
	    !xfs_verअगरy_agbno(mp, agno, bno) ||
	    !xfs_verअगरy_agbno(mp, agno, bno + len - 1))
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);

	xchk_iallocbt_chunk_xref(bs->sc, irec, agino, bno, len);

	वापस true;
पूर्ण

/* Count the number of मुक्त inodes. */
अटल अचिन्हित पूर्णांक
xchk_iallocbt_मुक्तcount(
	xfs_inoमुक्त_t			मुक्तmask)
अणु
	BUILD_BUG_ON(माप(मुक्तmask) != माप(__u64));
	वापस hweight64(मुक्तmask);
पूर्ण

/*
 * Check that an inode's allocation status matches ir_मुक्त in the inobt
 * record.  First we try querying the in-core inode state, and अगर the inode
 * isn't loaded we examine the on-disk inode directly.
 *
 * Since there can be 1:M and M:1 mappings between inobt records and inode
 * clusters, we pass in the inode location inक्रमmation as an inobt record;
 * the index of an inode cluster within the inobt record (as well as the
 * cluster buffer itself); and the index of the inode within the cluster.
 *
 * @irec is the inobt record.
 * @irec_ino is the inode offset from the start of the record.
 * @dip is the on-disk inode.
 */
STATIC पूर्णांक
xchk_iallocbt_check_cluster_अगरree(
	काष्ठा xchk_btree		*bs,
	काष्ठा xfs_inobt_rec_incore	*irec,
	अचिन्हित पूर्णांक			irec_ino,
	काष्ठा xfs_dinode		*dip)
अणु
	काष्ठा xfs_mount		*mp = bs->cur->bc_mp;
	xfs_ino_t			fsino;
	xfs_agino_t			agino;
	bool				irec_मुक्त;
	bool				ino_inuse;
	bool				मुक्तmask_ok;
	पूर्णांक				error = 0;

	अगर (xchk_should_terminate(bs->sc, &error))
		वापस error;

	/*
	 * Given an inobt record and the offset of an inode from the start of
	 * the record, compute which fs inode we're talking about.
	 */
	agino = irec->ir_startino + irec_ino;
	fsino = XFS_AGINO_TO_INO(mp, bs->cur->bc_ag.agno, agino);
	irec_मुक्त = (irec->ir_मुक्त & XFS_INOBT_MASK(irec_ino));

	अगर (be16_to_cpu(dip->di_magic) != XFS_DINODE_MAGIC ||
	    (dip->di_version >= 3 && be64_to_cpu(dip->di_ino) != fsino)) अणु
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);
		जाओ out;
	पूर्ण

	error = xfs_icache_inode_is_allocated(mp, bs->cur->bc_tp, fsino,
			&ino_inuse);
	अगर (error == -ENODATA) अणु
		/* Not cached, just पढ़ो the disk buffer */
		मुक्तmask_ok = irec_मुक्त ^ !!(dip->di_mode);
		अगर (!(bs->sc->flags & XCHK_TRY_HARDER) && !मुक्तmask_ok)
			वापस -EDEADLOCK;
	पूर्ण अन्यथा अगर (error < 0) अणु
		/*
		 * Inode is only half assembled, or there was an IO error,
		 * or the verअगरier failed, so करोn't bother trying to check.
		 * The inode scrubber can deal with this.
		 */
		जाओ out;
	पूर्ण अन्यथा अणु
		/* Inode is all there. */
		मुक्तmask_ok = irec_मुक्त ^ ino_inuse;
	पूर्ण
	अगर (!मुक्तmask_ok)
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);
out:
	वापस 0;
पूर्ण

/*
 * Check that the holemask and मुक्तmask of a hypothetical inode cluster match
 * what's actually on disk.  If sparse inodes are enabled, the cluster करोes
 * not actually have to map to inodes अगर the corresponding holemask bit is set.
 *
 * @cluster_base is the first inode in the cluster within the @irec.
 */
STATIC पूर्णांक
xchk_iallocbt_check_cluster(
	काष्ठा xchk_btree		*bs,
	काष्ठा xfs_inobt_rec_incore	*irec,
	अचिन्हित पूर्णांक			cluster_base)
अणु
	काष्ठा xfs_imap			imap;
	काष्ठा xfs_mount		*mp = bs->cur->bc_mp;
	काष्ठा xfs_buf			*cluster_bp;
	अचिन्हित पूर्णांक			nr_inodes;
	xfs_agnumber_t			agno = bs->cur->bc_ag.agno;
	xfs_agblock_t			agbno;
	अचिन्हित पूर्णांक			cluster_index;
	uपूर्णांक16_t			cluster_mask = 0;
	uपूर्णांक16_t			ir_holemask;
	पूर्णांक				error = 0;

	nr_inodes = min_t(अचिन्हित पूर्णांक, XFS_INODES_PER_CHUNK,
			M_IGEO(mp)->inodes_per_cluster);

	/* Map this inode cluster */
	agbno = XFS_AGINO_TO_AGBNO(mp, irec->ir_startino + cluster_base);

	/* Compute a biपंचांगask क्रम this cluster that can be used क्रम holemask. */
	क्रम (cluster_index = 0;
	     cluster_index < nr_inodes;
	     cluster_index += XFS_INODES_PER_HOLEMASK_BIT)
		cluster_mask |= XFS_INOBT_MASK((cluster_base + cluster_index) /
				XFS_INODES_PER_HOLEMASK_BIT);

	/*
	 * Map the first inode of this cluster to a buffer and offset.
	 * Be careful about inobt records that करोn't align with the start of
	 * the inode buffer when block sizes are large enough to hold multiple
	 * inode chunks.  When this happens, cluster_base will be zero but
	 * ir_startino can be large enough to make im_boffset nonzero.
	 */
	ir_holemask = (irec->ir_holemask & cluster_mask);
	imap.im_blkno = XFS_AGB_TO_DADDR(mp, agno, agbno);
	imap.im_len = XFS_FSB_TO_BB(mp, M_IGEO(mp)->blocks_per_cluster);
	imap.im_boffset = XFS_INO_TO_OFFSET(mp, irec->ir_startino) <<
			mp->m_sb.sb_inodelog;

	अगर (imap.im_boffset != 0 && cluster_base != 0) अणु
		ASSERT(imap.im_boffset == 0 || cluster_base == 0);
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);
		वापस 0;
	पूर्ण

	trace_xchk_iallocbt_check_cluster(mp, agno, irec->ir_startino,
			imap.im_blkno, imap.im_len, cluster_base, nr_inodes,
			cluster_mask, ir_holemask,
			XFS_INO_TO_OFFSET(mp, irec->ir_startino +
					  cluster_base));

	/* The whole cluster must be a hole or not a hole. */
	अगर (ir_holemask != cluster_mask && ir_holemask != 0) अणु
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);
		वापस 0;
	पूर्ण

	/* If any part of this is a hole, skip it. */
	अगर (ir_holemask) अणु
		xchk_xref_is_not_owned_by(bs->sc, agbno,
				M_IGEO(mp)->blocks_per_cluster,
				&XFS_RMAP_OINFO_INODES);
		वापस 0;
	पूर्ण

	xchk_xref_is_owned_by(bs->sc, agbno, M_IGEO(mp)->blocks_per_cluster,
			&XFS_RMAP_OINFO_INODES);

	/* Grab the inode cluster buffer. */
	error = xfs_imap_to_bp(mp, bs->cur->bc_tp, &imap, &cluster_bp);
	अगर (!xchk_btree_xref_process_error(bs->sc, bs->cur, 0, &error))
		वापस error;

	/* Check मुक्त status of each inode within this cluster. */
	क्रम (cluster_index = 0; cluster_index < nr_inodes; cluster_index++) अणु
		काष्ठा xfs_dinode	*dip;

		अगर (imap.im_boffset >= BBTOB(cluster_bp->b_length)) अणु
			xchk_btree_set_corrupt(bs->sc, bs->cur, 0);
			अवरोध;
		पूर्ण

		dip = xfs_buf_offset(cluster_bp, imap.im_boffset);
		error = xchk_iallocbt_check_cluster_अगरree(bs, irec,
				cluster_base + cluster_index, dip);
		अगर (error)
			अवरोध;
		imap.im_boffset += mp->m_sb.sb_inodesize;
	पूर्ण

	xfs_trans_brअन्यथा(bs->cur->bc_tp, cluster_bp);
	वापस error;
पूर्ण

/*
 * For all the inode clusters that could map to this inobt record, make sure
 * that the holemask makes sense and that the allocation status of each inode
 * matches the मुक्तmask.
 */
STATIC पूर्णांक
xchk_iallocbt_check_clusters(
	काष्ठा xchk_btree		*bs,
	काष्ठा xfs_inobt_rec_incore	*irec)
अणु
	अचिन्हित पूर्णांक			cluster_base;
	पूर्णांक				error = 0;

	/*
	 * For the common हाल where this inobt record maps to multiple inode
	 * clusters this will call _check_cluster क्रम each cluster.
	 *
	 * For the हाल that multiple inobt records map to a single cluster,
	 * this will call _check_cluster once.
	 */
	क्रम (cluster_base = 0;
	     cluster_base < XFS_INODES_PER_CHUNK;
	     cluster_base += M_IGEO(bs->sc->mp)->inodes_per_cluster) अणु
		error = xchk_iallocbt_check_cluster(bs, irec, cluster_base);
		अगर (error)
			अवरोध;
	पूर्ण

	वापस error;
पूर्ण

/*
 * Make sure this inode btree record is aligned properly.  Because a fs block
 * contains multiple inodes, we check that the inobt record is aligned to the
 * correct inode, not just the correct block on disk.  This results in a finer
 * grained corruption check.
 */
STATIC व्योम
xchk_iallocbt_rec_alignment(
	काष्ठा xchk_btree		*bs,
	काष्ठा xfs_inobt_rec_incore	*irec)
अणु
	काष्ठा xfs_mount		*mp = bs->sc->mp;
	काष्ठा xchk_iallocbt		*iabt = bs->निजी;
	काष्ठा xfs_ino_geometry		*igeo = M_IGEO(mp);

	/*
	 * finobt records have dअगरferent positioning requirements than inobt
	 * records: each finobt record must have a corresponding inobt record.
	 * That is checked in the xref function, so क्रम now we only catch the
	 * obvious हाल where the record isn't at all aligned properly.
	 *
	 * Note that अगर a fs block contains more than a single chunk of inodes,
	 * we will have finobt records only क्रम those chunks containing मुक्त
	 * inodes, and thereक्रमe expect chunk alignment of finobt records.
	 * Otherwise, we expect that the finobt record is aligned to the
	 * cluster alignment as told by the superblock.
	 */
	अगर (bs->cur->bc_btnum == XFS_BTNUM_FINO) अणु
		अचिन्हित पूर्णांक	imask;

		imask = min_t(अचिन्हित पूर्णांक, XFS_INODES_PER_CHUNK,
				igeo->cluster_align_inodes) - 1;
		अगर (irec->ir_startino & imask)
			xchk_btree_set_corrupt(bs->sc, bs->cur, 0);
		वापस;
	पूर्ण

	अगर (iabt->next_startino != शून्यAGINO) अणु
		/*
		 * We're midway through a cluster of inodes that is mapped by
		 * multiple inobt records.  Did we get the record क्रम the next
		 * irec in the sequence?
		 */
		अगर (irec->ir_startino != iabt->next_startino) अणु
			xchk_btree_set_corrupt(bs->sc, bs->cur, 0);
			वापस;
		पूर्ण

		iabt->next_startino += XFS_INODES_PER_CHUNK;

		/* Are we करोne with the cluster? */
		अगर (iabt->next_startino >= iabt->next_cluster_ino) अणु
			iabt->next_startino = शून्यAGINO;
			iabt->next_cluster_ino = शून्यAGINO;
		पूर्ण
		वापस;
	पूर्ण

	/* inobt records must be aligned to cluster and inoalignmnt size. */
	अगर (irec->ir_startino & (igeo->cluster_align_inodes - 1)) अणु
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);
		वापस;
	पूर्ण

	अगर (irec->ir_startino & (igeo->inodes_per_cluster - 1)) अणु
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);
		वापस;
	पूर्ण

	अगर (igeo->inodes_per_cluster <= XFS_INODES_PER_CHUNK)
		वापस;

	/*
	 * If this is the start of an inode cluster that can be mapped by
	 * multiple inobt records, the next inobt record must follow exactly
	 * after this one.
	 */
	iabt->next_startino = irec->ir_startino + XFS_INODES_PER_CHUNK;
	iabt->next_cluster_ino = irec->ir_startino + igeo->inodes_per_cluster;
पूर्ण

/* Scrub an inobt/finobt record. */
STATIC पूर्णांक
xchk_iallocbt_rec(
	काष्ठा xchk_btree		*bs,
	जोड़ xfs_btree_rec		*rec)
अणु
	काष्ठा xfs_mount		*mp = bs->cur->bc_mp;
	काष्ठा xchk_iallocbt		*iabt = bs->निजी;
	काष्ठा xfs_inobt_rec_incore	irec;
	uपूर्णांक64_t			holes;
	xfs_agnumber_t			agno = bs->cur->bc_ag.agno;
	xfs_agino_t			agino;
	xfs_extlen_t			len;
	पूर्णांक				holecount;
	पूर्णांक				i;
	पूर्णांक				error = 0;
	अचिन्हित पूर्णांक			real_मुक्तcount;
	uपूर्णांक16_t			holemask;

	xfs_inobt_btrec_to_irec(mp, rec, &irec);

	अगर (irec.ir_count > XFS_INODES_PER_CHUNK ||
	    irec.ir_मुक्तcount > XFS_INODES_PER_CHUNK)
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);

	real_मुक्तcount = irec.ir_मुक्तcount +
			(XFS_INODES_PER_CHUNK - irec.ir_count);
	अगर (real_मुक्तcount != xchk_iallocbt_मुक्तcount(irec.ir_मुक्त))
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);

	agino = irec.ir_startino;
	/* Record has to be properly aligned within the AG. */
	अगर (!xfs_verअगरy_agino(mp, agno, agino) ||
	    !xfs_verअगरy_agino(mp, agno, agino + XFS_INODES_PER_CHUNK - 1)) अणु
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);
		जाओ out;
	पूर्ण

	xchk_iallocbt_rec_alignment(bs, &irec);
	अगर (bs->sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		जाओ out;

	iabt->inodes += irec.ir_count;

	/* Handle non-sparse inodes */
	अगर (!xfs_inobt_issparse(irec.ir_holemask)) अणु
		len = XFS_B_TO_FSB(mp,
				XFS_INODES_PER_CHUNK * mp->m_sb.sb_inodesize);
		अगर (irec.ir_count != XFS_INODES_PER_CHUNK)
			xchk_btree_set_corrupt(bs->sc, bs->cur, 0);

		अगर (!xchk_iallocbt_chunk(bs, &irec, agino, len))
			जाओ out;
		जाओ check_clusters;
	पूर्ण

	/* Check each chunk of a sparse inode cluster. */
	holemask = irec.ir_holemask;
	holecount = 0;
	len = XFS_B_TO_FSB(mp,
			XFS_INODES_PER_HOLEMASK_BIT * mp->m_sb.sb_inodesize);
	holes = ~xfs_inobt_irec_to_allocmask(&irec);
	अगर ((holes & irec.ir_मुक्त) != holes ||
	    irec.ir_मुक्तcount > irec.ir_count)
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);

	क्रम (i = 0; i < XFS_INOBT_HOLEMASK_BITS; i++) अणु
		अगर (holemask & 1)
			holecount += XFS_INODES_PER_HOLEMASK_BIT;
		अन्यथा अगर (!xchk_iallocbt_chunk(bs, &irec, agino, len))
			अवरोध;
		holemask >>= 1;
		agino += XFS_INODES_PER_HOLEMASK_BIT;
	पूर्ण

	अगर (holecount > XFS_INODES_PER_CHUNK ||
	    holecount + irec.ir_count != XFS_INODES_PER_CHUNK)
		xchk_btree_set_corrupt(bs->sc, bs->cur, 0);

check_clusters:
	error = xchk_iallocbt_check_clusters(bs, &irec);
	अगर (error)
		जाओ out;

out:
	वापस error;
पूर्ण

/*
 * Make sure the inode btrees are as large as the rmap thinks they are.
 * Don't bother if we're missing btree cursors, as we're alपढ़ोy corrupt.
 */
STATIC व्योम
xchk_iallocbt_xref_rmap_btreeblks(
	काष्ठा xfs_scrub	*sc,
	पूर्णांक			which)
अणु
	xfs_filblks_t		blocks;
	xfs_extlen_t		inobt_blocks = 0;
	xfs_extlen_t		finobt_blocks = 0;
	पूर्णांक			error;

	अगर (!sc->sa.ino_cur || !sc->sa.rmap_cur ||
	    (xfs_sb_version_hasfinobt(&sc->mp->m_sb) && !sc->sa.fino_cur) ||
	    xchk_skip_xref(sc->sm))
		वापस;

	/* Check that we saw as many inobt blocks as the rmap says. */
	error = xfs_btree_count_blocks(sc->sa.ino_cur, &inobt_blocks);
	अगर (!xchk_process_error(sc, 0, 0, &error))
		वापस;

	अगर (sc->sa.fino_cur) अणु
		error = xfs_btree_count_blocks(sc->sa.fino_cur, &finobt_blocks);
		अगर (!xchk_process_error(sc, 0, 0, &error))
			वापस;
	पूर्ण

	error = xchk_count_rmap_ownedby_ag(sc, sc->sa.rmap_cur,
			&XFS_RMAP_OINFO_INOBT, &blocks);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.rmap_cur))
		वापस;
	अगर (blocks != inobt_blocks + finobt_blocks)
		xchk_btree_set_corrupt(sc, sc->sa.ino_cur, 0);
पूर्ण

/*
 * Make sure that the inobt records poपूर्णांक to the same number of blocks as
 * the rmap says are owned by inodes.
 */
STATIC व्योम
xchk_iallocbt_xref_rmap_inodes(
	काष्ठा xfs_scrub	*sc,
	पूर्णांक			which,
	अचिन्हित दीर्घ दीर्घ	inodes)
अणु
	xfs_filblks_t		blocks;
	xfs_filblks_t		inode_blocks;
	पूर्णांक			error;

	अगर (!sc->sa.rmap_cur || xchk_skip_xref(sc->sm))
		वापस;

	/* Check that we saw as many inode blocks as the rmap knows about. */
	error = xchk_count_rmap_ownedby_ag(sc, sc->sa.rmap_cur,
			&XFS_RMAP_OINFO_INODES, &blocks);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.rmap_cur))
		वापस;
	inode_blocks = XFS_B_TO_FSB(sc->mp, inodes * sc->mp->m_sb.sb_inodesize);
	अगर (blocks != inode_blocks)
		xchk_btree_xref_set_corrupt(sc, sc->sa.rmap_cur, 0);
पूर्ण

/* Scrub the inode btrees क्रम some AG. */
STATIC पूर्णांक
xchk_iallocbt(
	काष्ठा xfs_scrub	*sc,
	xfs_btnum_t		which)
अणु
	काष्ठा xfs_btree_cur	*cur;
	काष्ठा xchk_iallocbt	iabt = अणु
		.inodes		= 0,
		.next_startino	= शून्यAGINO,
		.next_cluster_ino = शून्यAGINO,
	पूर्ण;
	पूर्णांक			error;

	cur = which == XFS_BTNUM_INO ? sc->sa.ino_cur : sc->sa.fino_cur;
	error = xchk_btree(sc, cur, xchk_iallocbt_rec, &XFS_RMAP_OINFO_INOBT,
			&iabt);
	अगर (error)
		वापस error;

	xchk_iallocbt_xref_rmap_btreeblks(sc, which);

	/*
	 * If we're scrubbing the inode btree, inode_blocks is the number of
	 * blocks poपूर्णांकed to by all the inode chunk records.  Thereक्रमe, we
	 * should compare to the number of inode chunk blocks that the rmap
	 * knows about.  We can't करो this क्रम the finobt since it only poपूर्णांकs
	 * to inode chunks with मुक्त inodes.
	 */
	अगर (which == XFS_BTNUM_INO)
		xchk_iallocbt_xref_rmap_inodes(sc, which, iabt.inodes);

	वापस error;
पूर्ण

पूर्णांक
xchk_inobt(
	काष्ठा xfs_scrub	*sc)
अणु
	वापस xchk_iallocbt(sc, XFS_BTNUM_INO);
पूर्ण

पूर्णांक
xchk_finobt(
	काष्ठा xfs_scrub	*sc)
अणु
	वापस xchk_iallocbt(sc, XFS_BTNUM_FINO);
पूर्ण

/* See अगर an inode btree has (or करोesn't have) an inode chunk record. */
अटल अंतरभूत व्योम
xchk_xref_inode_check(
	काष्ठा xfs_scrub	*sc,
	xfs_agblock_t		agbno,
	xfs_extlen_t		len,
	काष्ठा xfs_btree_cur	**icur,
	bool			should_have_inodes)
अणु
	bool			has_inodes;
	पूर्णांक			error;

	अगर (!(*icur) || xchk_skip_xref(sc->sm))
		वापस;

	error = xfs_ialloc_has_inodes_at_extent(*icur, agbno, len, &has_inodes);
	अगर (!xchk_should_check_xref(sc, &error, icur))
		वापस;
	अगर (has_inodes != should_have_inodes)
		xchk_btree_xref_set_corrupt(sc, *icur, 0);
पूर्ण

/* xref check that the extent is not covered by inodes */
व्योम
xchk_xref_is_not_inode_chunk(
	काष्ठा xfs_scrub	*sc,
	xfs_agblock_t		agbno,
	xfs_extlen_t		len)
अणु
	xchk_xref_inode_check(sc, agbno, len, &sc->sa.ino_cur, false);
	xchk_xref_inode_check(sc, agbno, len, &sc->sa.fino_cur, false);
पूर्ण

/* xref check that the extent is covered by inodes */
व्योम
xchk_xref_is_inode_chunk(
	काष्ठा xfs_scrub	*sc,
	xfs_agblock_t		agbno,
	xfs_extlen_t		len)
अणु
	xchk_xref_inode_check(sc, agbno, len, &sc->sa.ino_cur, true);
पूर्ण
