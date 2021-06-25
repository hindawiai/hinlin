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
#समावेश "xfs_sb.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_ialloc.h"
#समावेश "xfs_rmap.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/common.h"

/* Superblock */

/* Cross-reference with the other btrees. */
STATIC व्योम
xchk_superblock_xref(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	xfs_agnumber_t		agno = sc->sm->sm_agno;
	xfs_agblock_t		agbno;
	पूर्णांक			error;

	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		वापस;

	agbno = XFS_SB_BLOCK(mp);

	error = xchk_ag_init(sc, agno, &sc->sa);
	अगर (!xchk_xref_process_error(sc, agno, agbno, &error))
		वापस;

	xchk_xref_is_used_space(sc, agbno, 1);
	xchk_xref_is_not_inode_chunk(sc, agbno, 1);
	xchk_xref_is_owned_by(sc, agbno, 1, &XFS_RMAP_OINFO_FS);
	xchk_xref_is_not_shared(sc, agbno, 1);

	/* scrub tearकरोwn will take care of sc->sa क्रम us */
पूर्ण

/*
 * Scrub the fileप्रणाली superblock.
 *
 * Note: We करो /not/ attempt to check AG 0's superblock.  Mount is
 * responsible क्रम validating all the geometry inक्रमmation in sb 0, so
 * अगर the fileप्रणाली is capable of initiating online scrub, then clearly
 * sb 0 is ok and we can use its inक्रमmation to check everything अन्यथा.
 */
पूर्णांक
xchk_superblock(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	काष्ठा xfs_buf		*bp;
	काष्ठा xfs_dsb		*sb;
	xfs_agnumber_t		agno;
	uपूर्णांक32_t		v2_ok;
	__be32			features_mask;
	पूर्णांक			error;
	__be16			vernum_mask;

	agno = sc->sm->sm_agno;
	अगर (agno == 0)
		वापस 0;

	error = xfs_sb_पढ़ो_secondary(mp, sc->tp, agno, &bp);
	/*
	 * The superblock verअगरier can वापस several dअगरferent error codes
	 * अगर it thinks the superblock करोesn't look right.  For a mount these
	 * would all get bounced back to userspace, but अगर we're here then the
	 * fs mounted successfully, which means that this secondary superblock
	 * is simply incorrect.  Treat all these codes the same way we treat
	 * any corruption.
	 */
	चयन (error) अणु
	हाल -EINVAL:	/* also -EWRONGFS */
	हाल -ENOSYS:
	हाल -EFBIG:
		error = -EFSCORRUPTED;
	शेष:
		अवरोध;
	पूर्ण
	अगर (!xchk_process_error(sc, agno, XFS_SB_BLOCK(mp), &error))
		वापस error;

	sb = bp->b_addr;

	/*
	 * Verअगरy the geometries match.  Fields that are permanently
	 * set by mkfs are checked; fields that can be updated later
	 * (and are not propagated to backup superblocks) are preen
	 * checked.
	 */
	अगर (sb->sb_blocksize != cpu_to_be32(mp->m_sb.sb_blocksize))
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_dblocks != cpu_to_be64(mp->m_sb.sb_dblocks))
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_rblocks != cpu_to_be64(mp->m_sb.sb_rblocks))
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_rextents != cpu_to_be64(mp->m_sb.sb_rextents))
		xchk_block_set_corrupt(sc, bp);

	अगर (!uuid_equal(&sb->sb_uuid, &mp->m_sb.sb_uuid))
		xchk_block_set_preen(sc, bp);

	अगर (sb->sb_logstart != cpu_to_be64(mp->m_sb.sb_logstart))
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_rootino != cpu_to_be64(mp->m_sb.sb_rootino))
		xchk_block_set_preen(sc, bp);

	अगर (sb->sb_rbmino != cpu_to_be64(mp->m_sb.sb_rbmino))
		xchk_block_set_preen(sc, bp);

	अगर (sb->sb_rsumino != cpu_to_be64(mp->m_sb.sb_rsumino))
		xchk_block_set_preen(sc, bp);

	अगर (sb->sb_rextsize != cpu_to_be32(mp->m_sb.sb_rextsize))
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_agblocks != cpu_to_be32(mp->m_sb.sb_agblocks))
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_agcount != cpu_to_be32(mp->m_sb.sb_agcount))
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_rbmblocks != cpu_to_be32(mp->m_sb.sb_rbmblocks))
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_logblocks != cpu_to_be32(mp->m_sb.sb_logblocks))
		xchk_block_set_corrupt(sc, bp);

	/* Check sb_versionnum bits that are set at mkfs समय. */
	vernum_mask = cpu_to_be16(~XFS_SB_VERSION_OKBITS |
				  XFS_SB_VERSION_NUMBITS |
				  XFS_SB_VERSION_ALIGNBIT |
				  XFS_SB_VERSION_DALIGNBIT |
				  XFS_SB_VERSION_SHAREDBIT |
				  XFS_SB_VERSION_LOGV2BIT |
				  XFS_SB_VERSION_SECTORBIT |
				  XFS_SB_VERSION_EXTFLGBIT |
				  XFS_SB_VERSION_सूचीV2BIT);
	अगर ((sb->sb_versionnum & vernum_mask) !=
	    (cpu_to_be16(mp->m_sb.sb_versionnum) & vernum_mask))
		xchk_block_set_corrupt(sc, bp);

	/* Check sb_versionnum bits that can be set after mkfs समय. */
	vernum_mask = cpu_to_be16(XFS_SB_VERSION_ATTRBIT |
				  XFS_SB_VERSION_NLINKBIT |
				  XFS_SB_VERSION_QUOTABIT);
	अगर ((sb->sb_versionnum & vernum_mask) !=
	    (cpu_to_be16(mp->m_sb.sb_versionnum) & vernum_mask))
		xchk_block_set_preen(sc, bp);

	अगर (sb->sb_sectsize != cpu_to_be16(mp->m_sb.sb_sectsize))
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_inodesize != cpu_to_be16(mp->m_sb.sb_inodesize))
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_inopblock != cpu_to_be16(mp->m_sb.sb_inopblock))
		xchk_block_set_corrupt(sc, bp);

	अगर (स_भेद(sb->sb_fname, mp->m_sb.sb_fname, माप(sb->sb_fname)))
		xchk_block_set_preen(sc, bp);

	अगर (sb->sb_blocklog != mp->m_sb.sb_blocklog)
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_sectlog != mp->m_sb.sb_sectlog)
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_inodelog != mp->m_sb.sb_inodelog)
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_inopblog != mp->m_sb.sb_inopblog)
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_agblklog != mp->m_sb.sb_agblklog)
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_rextslog != mp->m_sb.sb_rextslog)
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_imax_pct != mp->m_sb.sb_imax_pct)
		xchk_block_set_preen(sc, bp);

	/*
	 * Skip the summary counters since we track them in memory anyway.
	 * sb_icount, sb_अगरree, sb_fdblocks, sb_frexents
	 */

	अगर (sb->sb_uquotino != cpu_to_be64(mp->m_sb.sb_uquotino))
		xchk_block_set_preen(sc, bp);

	अगर (sb->sb_gquotino != cpu_to_be64(mp->m_sb.sb_gquotino))
		xchk_block_set_preen(sc, bp);

	/*
	 * Skip the quota flags since repair will क्रमce quotacheck.
	 * sb_qflags
	 */

	अगर (sb->sb_flags != mp->m_sb.sb_flags)
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_shared_vn != mp->m_sb.sb_shared_vn)
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_inoalignmt != cpu_to_be32(mp->m_sb.sb_inoalignmt))
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_unit != cpu_to_be32(mp->m_sb.sb_unit))
		xchk_block_set_preen(sc, bp);

	अगर (sb->sb_width != cpu_to_be32(mp->m_sb.sb_width))
		xchk_block_set_preen(sc, bp);

	अगर (sb->sb_dirblklog != mp->m_sb.sb_dirblklog)
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_logsectlog != mp->m_sb.sb_logsectlog)
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_logsectsize != cpu_to_be16(mp->m_sb.sb_logsectsize))
		xchk_block_set_corrupt(sc, bp);

	अगर (sb->sb_logsunit != cpu_to_be32(mp->m_sb.sb_logsunit))
		xchk_block_set_corrupt(sc, bp);

	/* Do we see any invalid bits in sb_features2? */
	अगर (!xfs_sb_version_hयंत्रorebits(&mp->m_sb)) अणु
		अगर (sb->sb_features2 != 0)
			xchk_block_set_corrupt(sc, bp);
	पूर्ण अन्यथा अणु
		v2_ok = XFS_SB_VERSION2_OKBITS;
		अगर (XFS_SB_VERSION_NUM(&mp->m_sb) >= XFS_SB_VERSION_5)
			v2_ok |= XFS_SB_VERSION2_CRCBIT;

		अगर (!!(sb->sb_features2 & cpu_to_be32(~v2_ok)))
			xchk_block_set_corrupt(sc, bp);

		अगर (sb->sb_features2 != sb->sb_bad_features2)
			xchk_block_set_preen(sc, bp);
	पूर्ण

	/* Check sb_features2 flags that are set at mkfs समय. */
	features_mask = cpu_to_be32(XFS_SB_VERSION2_LAZYSBCOUNTBIT |
				    XFS_SB_VERSION2_PROJID32BIT |
				    XFS_SB_VERSION2_CRCBIT |
				    XFS_SB_VERSION2_FTYPE);
	अगर ((sb->sb_features2 & features_mask) !=
	    (cpu_to_be32(mp->m_sb.sb_features2) & features_mask))
		xchk_block_set_corrupt(sc, bp);

	/* Check sb_features2 flags that can be set after mkfs समय. */
	features_mask = cpu_to_be32(XFS_SB_VERSION2_ATTR2BIT);
	अगर ((sb->sb_features2 & features_mask) !=
	    (cpu_to_be32(mp->m_sb.sb_features2) & features_mask))
		xchk_block_set_corrupt(sc, bp);

	अगर (!xfs_sb_version_hascrc(&mp->m_sb)) अणु
		/* all v5 fields must be zero */
		अगर (स_प्रथम_inv(&sb->sb_features_compat, 0,
				माप(काष्ठा xfs_dsb) -
				दुरत्व(काष्ठा xfs_dsb, sb_features_compat)))
			xchk_block_set_corrupt(sc, bp);
	पूर्ण अन्यथा अणु
		/* Check compat flags; all are set at mkfs समय. */
		features_mask = cpu_to_be32(XFS_SB_FEAT_COMPAT_UNKNOWN);
		अगर ((sb->sb_features_compat & features_mask) !=
		    (cpu_to_be32(mp->m_sb.sb_features_compat) & features_mask))
			xchk_block_set_corrupt(sc, bp);

		/* Check ro compat flags; all are set at mkfs समय. */
		features_mask = cpu_to_be32(XFS_SB_FEAT_RO_COMPAT_UNKNOWN |
					    XFS_SB_FEAT_RO_COMPAT_FINOBT |
					    XFS_SB_FEAT_RO_COMPAT_RMAPBT |
					    XFS_SB_FEAT_RO_COMPAT_REFLINK);
		अगर ((sb->sb_features_ro_compat & features_mask) !=
		    (cpu_to_be32(mp->m_sb.sb_features_ro_compat) &
		     features_mask))
			xchk_block_set_corrupt(sc, bp);

		/* Check incompat flags; all are set at mkfs समय. */
		features_mask = cpu_to_be32(XFS_SB_FEAT_INCOMPAT_UNKNOWN |
					    XFS_SB_FEAT_INCOMPAT_FTYPE |
					    XFS_SB_FEAT_INCOMPAT_SPINODES |
					    XFS_SB_FEAT_INCOMPAT_META_UUID);
		अगर ((sb->sb_features_incompat & features_mask) !=
		    (cpu_to_be32(mp->m_sb.sb_features_incompat) &
		     features_mask))
			xchk_block_set_corrupt(sc, bp);

		/* Check log incompat flags; all are set at mkfs समय. */
		features_mask = cpu_to_be32(XFS_SB_FEAT_INCOMPAT_LOG_UNKNOWN);
		अगर ((sb->sb_features_log_incompat & features_mask) !=
		    (cpu_to_be32(mp->m_sb.sb_features_log_incompat) &
		     features_mask))
			xchk_block_set_corrupt(sc, bp);

		/* Don't care about sb_crc */

		अगर (sb->sb_spino_align != cpu_to_be32(mp->m_sb.sb_spino_align))
			xchk_block_set_corrupt(sc, bp);

		अगर (sb->sb_pquotino != cpu_to_be64(mp->m_sb.sb_pquotino))
			xchk_block_set_preen(sc, bp);

		/* Don't care about sb_lsn */
	पूर्ण

	अगर (xfs_sb_version_hयंत्रetauuid(&mp->m_sb)) अणु
		/* The metadata UUID must be the same क्रम all supers */
		अगर (!uuid_equal(&sb->sb_meta_uuid, &mp->m_sb.sb_meta_uuid))
			xchk_block_set_corrupt(sc, bp);
	पूर्ण

	/* Everything अन्यथा must be zero. */
	अगर (स_प्रथम_inv(sb + 1, 0,
			BBTOB(bp->b_length) - माप(काष्ठा xfs_dsb)))
		xchk_block_set_corrupt(sc, bp);

	xchk_superblock_xref(sc, bp);

	वापस error;
पूर्ण

/* AGF */

/* Tally मुक्तspace record lengths. */
STATIC पूर्णांक
xchk_agf_record_bno_lengths(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_alloc_rec_incore	*rec,
	व्योम				*priv)
अणु
	xfs_extlen_t			*blocks = priv;

	(*blocks) += rec->ar_blockcount;
	वापस 0;
पूर्ण

/* Check agf_मुक्तblks */
अटल अंतरभूत व्योम
xchk_agf_xref_मुक्तblks(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_agf		*agf = sc->sa.agf_bp->b_addr;
	xfs_extlen_t		blocks = 0;
	पूर्णांक			error;

	अगर (!sc->sa.bno_cur)
		वापस;

	error = xfs_alloc_query_all(sc->sa.bno_cur,
			xchk_agf_record_bno_lengths, &blocks);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.bno_cur))
		वापस;
	अगर (blocks != be32_to_cpu(agf->agf_मुक्तblks))
		xchk_block_xref_set_corrupt(sc, sc->sa.agf_bp);
पूर्ण

/* Cross reference the AGF with the cntbt (मुक्तspace by length btree) */
अटल अंतरभूत व्योम
xchk_agf_xref_cntbt(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_agf		*agf = sc->sa.agf_bp->b_addr;
	xfs_agblock_t		agbno;
	xfs_extlen_t		blocks;
	पूर्णांक			have;
	पूर्णांक			error;

	अगर (!sc->sa.cnt_cur)
		वापस;

	/* Any मुक्तspace at all? */
	error = xfs_alloc_lookup_le(sc->sa.cnt_cur, 0, -1U, &have);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.cnt_cur))
		वापस;
	अगर (!have) अणु
		अगर (agf->agf_मुक्तblks != cpu_to_be32(0))
			xchk_block_xref_set_corrupt(sc, sc->sa.agf_bp);
		वापस;
	पूर्ण

	/* Check agf_दीर्घest */
	error = xfs_alloc_get_rec(sc->sa.cnt_cur, &agbno, &blocks, &have);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.cnt_cur))
		वापस;
	अगर (!have || blocks != be32_to_cpu(agf->agf_दीर्घest))
		xchk_block_xref_set_corrupt(sc, sc->sa.agf_bp);
पूर्ण

/* Check the btree block counts in the AGF against the btrees. */
STATIC व्योम
xchk_agf_xref_btreeblks(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_agf		*agf = sc->sa.agf_bp->b_addr;
	काष्ठा xfs_mount	*mp = sc->mp;
	xfs_agblock_t		blocks;
	xfs_agblock_t		btreeblks;
	पूर्णांक			error;

	/* agf_btreeblks didn't exist beक्रमe lazysbcount */
	अगर (!xfs_sb_version_haslazysbcount(&sc->mp->m_sb))
		वापस;

	/* Check agf_rmap_blocks; set up क्रम agf_btreeblks check */
	अगर (sc->sa.rmap_cur) अणु
		error = xfs_btree_count_blocks(sc->sa.rmap_cur, &blocks);
		अगर (!xchk_should_check_xref(sc, &error, &sc->sa.rmap_cur))
			वापस;
		btreeblks = blocks - 1;
		अगर (blocks != be32_to_cpu(agf->agf_rmap_blocks))
			xchk_block_xref_set_corrupt(sc, sc->sa.agf_bp);
	पूर्ण अन्यथा अणु
		btreeblks = 0;
	पूर्ण

	/*
	 * No rmap cursor; we can't xref अगर we have the rmapbt feature.
	 * We also can't do it if we're missing the मुक्त space btree cursors.
	 */
	अगर ((xfs_sb_version_hasrmapbt(&mp->m_sb) && !sc->sa.rmap_cur) ||
	    !sc->sa.bno_cur || !sc->sa.cnt_cur)
		वापस;

	/* Check agf_btreeblks */
	error = xfs_btree_count_blocks(sc->sa.bno_cur, &blocks);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.bno_cur))
		वापस;
	btreeblks += blocks - 1;

	error = xfs_btree_count_blocks(sc->sa.cnt_cur, &blocks);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.cnt_cur))
		वापस;
	btreeblks += blocks - 1;

	अगर (btreeblks != be32_to_cpu(agf->agf_btreeblks))
		xchk_block_xref_set_corrupt(sc, sc->sa.agf_bp);
पूर्ण

/* Check agf_refcount_blocks against tree size */
अटल अंतरभूत व्योम
xchk_agf_xref_refcblks(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_agf		*agf = sc->sa.agf_bp->b_addr;
	xfs_agblock_t		blocks;
	पूर्णांक			error;

	अगर (!sc->sa.refc_cur)
		वापस;

	error = xfs_btree_count_blocks(sc->sa.refc_cur, &blocks);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.refc_cur))
		वापस;
	अगर (blocks != be32_to_cpu(agf->agf_refcount_blocks))
		xchk_block_xref_set_corrupt(sc, sc->sa.agf_bp);
पूर्ण

/* Cross-reference with the other btrees. */
STATIC व्योम
xchk_agf_xref(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	xfs_agblock_t		agbno;

	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		वापस;

	agbno = XFS_AGF_BLOCK(mp);

	xchk_ag_btcur_init(sc, &sc->sa);

	xchk_xref_is_used_space(sc, agbno, 1);
	xchk_agf_xref_मुक्तblks(sc);
	xchk_agf_xref_cntbt(sc);
	xchk_xref_is_not_inode_chunk(sc, agbno, 1);
	xchk_xref_is_owned_by(sc, agbno, 1, &XFS_RMAP_OINFO_FS);
	xchk_agf_xref_btreeblks(sc);
	xchk_xref_is_not_shared(sc, agbno, 1);
	xchk_agf_xref_refcblks(sc);

	/* scrub tearकरोwn will take care of sc->sa क्रम us */
पूर्ण

/* Scrub the AGF. */
पूर्णांक
xchk_agf(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	काष्ठा xfs_agf		*agf;
	काष्ठा xfs_perag	*pag;
	xfs_agnumber_t		agno = sc->sm->sm_agno;
	xfs_agblock_t		agbno;
	xfs_agblock_t		eoag;
	xfs_agblock_t		agfl_first;
	xfs_agblock_t		agfl_last;
	xfs_agblock_t		agfl_count;
	xfs_agblock_t		fl_count;
	पूर्णांक			level;
	पूर्णांक			error = 0;

	error = xchk_ag_पढ़ो_headers(sc, agno, &sc->sa);
	अगर (!xchk_process_error(sc, agno, XFS_AGF_BLOCK(sc->mp), &error))
		जाओ out;
	xchk_buffer_recheck(sc, sc->sa.agf_bp);

	agf = sc->sa.agf_bp->b_addr;

	/* Check the AG length */
	eoag = be32_to_cpu(agf->agf_length);
	अगर (eoag != xfs_ag_block_count(mp, agno))
		xchk_block_set_corrupt(sc, sc->sa.agf_bp);

	/* Check the AGF btree roots and levels */
	agbno = be32_to_cpu(agf->agf_roots[XFS_BTNUM_BNO]);
	अगर (!xfs_verअगरy_agbno(mp, agno, agbno))
		xchk_block_set_corrupt(sc, sc->sa.agf_bp);

	agbno = be32_to_cpu(agf->agf_roots[XFS_BTNUM_CNT]);
	अगर (!xfs_verअगरy_agbno(mp, agno, agbno))
		xchk_block_set_corrupt(sc, sc->sa.agf_bp);

	level = be32_to_cpu(agf->agf_levels[XFS_BTNUM_BNO]);
	अगर (level <= 0 || level > XFS_BTREE_MAXLEVELS)
		xchk_block_set_corrupt(sc, sc->sa.agf_bp);

	level = be32_to_cpu(agf->agf_levels[XFS_BTNUM_CNT]);
	अगर (level <= 0 || level > XFS_BTREE_MAXLEVELS)
		xchk_block_set_corrupt(sc, sc->sa.agf_bp);

	अगर (xfs_sb_version_hasrmapbt(&mp->m_sb)) अणु
		agbno = be32_to_cpu(agf->agf_roots[XFS_BTNUM_RMAP]);
		अगर (!xfs_verअगरy_agbno(mp, agno, agbno))
			xchk_block_set_corrupt(sc, sc->sa.agf_bp);

		level = be32_to_cpu(agf->agf_levels[XFS_BTNUM_RMAP]);
		अगर (level <= 0 || level > XFS_BTREE_MAXLEVELS)
			xchk_block_set_corrupt(sc, sc->sa.agf_bp);
	पूर्ण

	अगर (xfs_sb_version_hasreflink(&mp->m_sb)) अणु
		agbno = be32_to_cpu(agf->agf_refcount_root);
		अगर (!xfs_verअगरy_agbno(mp, agno, agbno))
			xchk_block_set_corrupt(sc, sc->sa.agf_bp);

		level = be32_to_cpu(agf->agf_refcount_level);
		अगर (level <= 0 || level > XFS_BTREE_MAXLEVELS)
			xchk_block_set_corrupt(sc, sc->sa.agf_bp);
	पूर्ण

	/* Check the AGFL counters */
	agfl_first = be32_to_cpu(agf->agf_flfirst);
	agfl_last = be32_to_cpu(agf->agf_fllast);
	agfl_count = be32_to_cpu(agf->agf_flcount);
	अगर (agfl_last > agfl_first)
		fl_count = agfl_last - agfl_first + 1;
	अन्यथा
		fl_count = xfs_agfl_size(mp) - agfl_first + agfl_last + 1;
	अगर (agfl_count != 0 && fl_count != agfl_count)
		xchk_block_set_corrupt(sc, sc->sa.agf_bp);

	/* Do the incore counters match? */
	pag = xfs_perag_get(mp, agno);
	अगर (pag->pagf_मुक्तblks != be32_to_cpu(agf->agf_मुक्तblks))
		xchk_block_set_corrupt(sc, sc->sa.agf_bp);
	अगर (pag->pagf_flcount != be32_to_cpu(agf->agf_flcount))
		xchk_block_set_corrupt(sc, sc->sa.agf_bp);
	अगर (xfs_sb_version_haslazysbcount(&sc->mp->m_sb) &&
	    pag->pagf_btreeblks != be32_to_cpu(agf->agf_btreeblks))
		xchk_block_set_corrupt(sc, sc->sa.agf_bp);
	xfs_perag_put(pag);

	xchk_agf_xref(sc);
out:
	वापस error;
पूर्ण

/* AGFL */

काष्ठा xchk_agfl_info अणु
	अचिन्हित पूर्णांक		sz_entries;
	अचिन्हित पूर्णांक		nr_entries;
	xfs_agblock_t		*entries;
	काष्ठा xfs_scrub	*sc;
पूर्ण;

/* Cross-reference with the other btrees. */
STATIC व्योम
xchk_agfl_block_xref(
	काष्ठा xfs_scrub	*sc,
	xfs_agblock_t		agbno)
अणु
	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		वापस;

	xchk_xref_is_used_space(sc, agbno, 1);
	xchk_xref_is_not_inode_chunk(sc, agbno, 1);
	xchk_xref_is_owned_by(sc, agbno, 1, &XFS_RMAP_OINFO_AG);
	xchk_xref_is_not_shared(sc, agbno, 1);
पूर्ण

/* Scrub an AGFL block. */
STATIC पूर्णांक
xchk_agfl_block(
	काष्ठा xfs_mount	*mp,
	xfs_agblock_t		agbno,
	व्योम			*priv)
अणु
	काष्ठा xchk_agfl_info	*sai = priv;
	काष्ठा xfs_scrub	*sc = sai->sc;
	xfs_agnumber_t		agno = sc->sa.agno;

	अगर (xfs_verअगरy_agbno(mp, agno, agbno) &&
	    sai->nr_entries < sai->sz_entries)
		sai->entries[sai->nr_entries++] = agbno;
	अन्यथा
		xchk_block_set_corrupt(sc, sc->sa.agfl_bp);

	xchk_agfl_block_xref(sc, agbno);

	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		वापस -ECANCELED;

	वापस 0;
पूर्ण

अटल पूर्णांक
xchk_agblock_cmp(
	स्थिर व्योम		*pa,
	स्थिर व्योम		*pb)
अणु
	स्थिर xfs_agblock_t	*a = pa;
	स्थिर xfs_agblock_t	*b = pb;

	वापस (पूर्णांक)*a - (पूर्णांक)*b;
पूर्ण

/* Cross-reference with the other btrees. */
STATIC व्योम
xchk_agfl_xref(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	xfs_agblock_t		agbno;

	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		वापस;

	agbno = XFS_AGFL_BLOCK(mp);

	xchk_ag_btcur_init(sc, &sc->sa);

	xchk_xref_is_used_space(sc, agbno, 1);
	xchk_xref_is_not_inode_chunk(sc, agbno, 1);
	xchk_xref_is_owned_by(sc, agbno, 1, &XFS_RMAP_OINFO_FS);
	xchk_xref_is_not_shared(sc, agbno, 1);

	/*
	 * Scrub tearकरोwn will take care of sc->sa क्रम us.  Leave sc->sa
	 * active so that the agfl block xref can use it too.
	 */
पूर्ण

/* Scrub the AGFL. */
पूर्णांक
xchk_agfl(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xchk_agfl_info	sai;
	काष्ठा xfs_agf		*agf;
	xfs_agnumber_t		agno = sc->sm->sm_agno;
	अचिन्हित पूर्णांक		agflcount;
	अचिन्हित पूर्णांक		i;
	पूर्णांक			error;

	error = xchk_ag_पढ़ो_headers(sc, agno, &sc->sa);
	अगर (!xchk_process_error(sc, agno, XFS_AGFL_BLOCK(sc->mp), &error))
		जाओ out;
	अगर (!sc->sa.agf_bp)
		वापस -EFSCORRUPTED;
	xchk_buffer_recheck(sc, sc->sa.agfl_bp);

	xchk_agfl_xref(sc);

	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		जाओ out;

	/* Allocate buffer to ensure uniqueness of AGFL entries. */
	agf = sc->sa.agf_bp->b_addr;
	agflcount = be32_to_cpu(agf->agf_flcount);
	अगर (agflcount > xfs_agfl_size(sc->mp)) अणु
		xchk_block_set_corrupt(sc, sc->sa.agf_bp);
		जाओ out;
	पूर्ण
	स_रखो(&sai, 0, माप(sai));
	sai.sc = sc;
	sai.sz_entries = agflcount;
	sai.entries = kmem_zalloc(माप(xfs_agblock_t) * agflcount,
			KM_MAYFAIL);
	अगर (!sai.entries) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Check the blocks in the AGFL. */
	error = xfs_agfl_walk(sc->mp, sc->sa.agf_bp->b_addr,
			sc->sa.agfl_bp, xchk_agfl_block, &sai);
	अगर (error == -ECANCELED) अणु
		error = 0;
		जाओ out_मुक्त;
	पूर्ण
	अगर (error)
		जाओ out_मुक्त;

	अगर (agflcount != sai.nr_entries) अणु
		xchk_block_set_corrupt(sc, sc->sa.agf_bp);
		जाओ out_मुक्त;
	पूर्ण

	/* Sort entries, check क्रम duplicates. */
	sort(sai.entries, sai.nr_entries, माप(sai.entries[0]),
			xchk_agblock_cmp, शून्य);
	क्रम (i = 1; i < sai.nr_entries; i++) अणु
		अगर (sai.entries[i] == sai.entries[i - 1]) अणु
			xchk_block_set_corrupt(sc, sc->sa.agf_bp);
			अवरोध;
		पूर्ण
	पूर्ण

out_मुक्त:
	kmem_मुक्त(sai.entries);
out:
	वापस error;
पूर्ण

/* AGI */

/* Check agi_count/agi_मुक्तcount */
अटल अंतरभूत व्योम
xchk_agi_xref_icounts(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_agi		*agi = sc->sa.agi_bp->b_addr;
	xfs_agino_t		icount;
	xfs_agino_t		मुक्तcount;
	पूर्णांक			error;

	अगर (!sc->sa.ino_cur)
		वापस;

	error = xfs_ialloc_count_inodes(sc->sa.ino_cur, &icount, &मुक्तcount);
	अगर (!xchk_should_check_xref(sc, &error, &sc->sa.ino_cur))
		वापस;
	अगर (be32_to_cpu(agi->agi_count) != icount ||
	    be32_to_cpu(agi->agi_मुक्तcount) != मुक्तcount)
		xchk_block_xref_set_corrupt(sc, sc->sa.agi_bp);
पूर्ण

/* Check agi_[fi]blocks against tree size */
अटल अंतरभूत व्योम
xchk_agi_xref_fiblocks(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_agi		*agi = sc->sa.agi_bp->b_addr;
	xfs_agblock_t		blocks;
	पूर्णांक			error = 0;

	अगर (!xfs_sb_version_hasinobtcounts(&sc->mp->m_sb))
		वापस;

	अगर (sc->sa.ino_cur) अणु
		error = xfs_btree_count_blocks(sc->sa.ino_cur, &blocks);
		अगर (!xchk_should_check_xref(sc, &error, &sc->sa.ino_cur))
			वापस;
		अगर (blocks != be32_to_cpu(agi->agi_iblocks))
			xchk_block_xref_set_corrupt(sc, sc->sa.agi_bp);
	पूर्ण

	अगर (sc->sa.fino_cur) अणु
		error = xfs_btree_count_blocks(sc->sa.fino_cur, &blocks);
		अगर (!xchk_should_check_xref(sc, &error, &sc->sa.fino_cur))
			वापस;
		अगर (blocks != be32_to_cpu(agi->agi_fblocks))
			xchk_block_xref_set_corrupt(sc, sc->sa.agi_bp);
	पूर्ण
पूर्ण

/* Cross-reference with the other btrees. */
STATIC व्योम
xchk_agi_xref(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	xfs_agblock_t		agbno;

	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		वापस;

	agbno = XFS_AGI_BLOCK(mp);

	xchk_ag_btcur_init(sc, &sc->sa);

	xchk_xref_is_used_space(sc, agbno, 1);
	xchk_xref_is_not_inode_chunk(sc, agbno, 1);
	xchk_agi_xref_icounts(sc);
	xchk_xref_is_owned_by(sc, agbno, 1, &XFS_RMAP_OINFO_FS);
	xchk_xref_is_not_shared(sc, agbno, 1);
	xchk_agi_xref_fiblocks(sc);

	/* scrub tearकरोwn will take care of sc->sa क्रम us */
पूर्ण

/* Scrub the AGI. */
पूर्णांक
xchk_agi(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	काष्ठा xfs_agi		*agi;
	काष्ठा xfs_perag	*pag;
	xfs_agnumber_t		agno = sc->sm->sm_agno;
	xfs_agblock_t		agbno;
	xfs_agblock_t		eoag;
	xfs_agino_t		agino;
	xfs_agino_t		first_agino;
	xfs_agino_t		last_agino;
	xfs_agino_t		icount;
	पूर्णांक			i;
	पूर्णांक			level;
	पूर्णांक			error = 0;

	error = xchk_ag_पढ़ो_headers(sc, agno, &sc->sa);
	अगर (!xchk_process_error(sc, agno, XFS_AGI_BLOCK(sc->mp), &error))
		जाओ out;
	xchk_buffer_recheck(sc, sc->sa.agi_bp);

	agi = sc->sa.agi_bp->b_addr;

	/* Check the AG length */
	eoag = be32_to_cpu(agi->agi_length);
	अगर (eoag != xfs_ag_block_count(mp, agno))
		xchk_block_set_corrupt(sc, sc->sa.agi_bp);

	/* Check btree roots and levels */
	agbno = be32_to_cpu(agi->agi_root);
	अगर (!xfs_verअगरy_agbno(mp, agno, agbno))
		xchk_block_set_corrupt(sc, sc->sa.agi_bp);

	level = be32_to_cpu(agi->agi_level);
	अगर (level <= 0 || level > XFS_BTREE_MAXLEVELS)
		xchk_block_set_corrupt(sc, sc->sa.agi_bp);

	अगर (xfs_sb_version_hasfinobt(&mp->m_sb)) अणु
		agbno = be32_to_cpu(agi->agi_मुक्त_root);
		अगर (!xfs_verअगरy_agbno(mp, agno, agbno))
			xchk_block_set_corrupt(sc, sc->sa.agi_bp);

		level = be32_to_cpu(agi->agi_मुक्त_level);
		अगर (level <= 0 || level > XFS_BTREE_MAXLEVELS)
			xchk_block_set_corrupt(sc, sc->sa.agi_bp);
	पूर्ण

	/* Check inode counters */
	xfs_agino_range(mp, agno, &first_agino, &last_agino);
	icount = be32_to_cpu(agi->agi_count);
	अगर (icount > last_agino - first_agino + 1 ||
	    icount < be32_to_cpu(agi->agi_मुक्तcount))
		xchk_block_set_corrupt(sc, sc->sa.agi_bp);

	/* Check inode poपूर्णांकers */
	agino = be32_to_cpu(agi->agi_newino);
	अगर (!xfs_verअगरy_agino_or_null(mp, agno, agino))
		xchk_block_set_corrupt(sc, sc->sa.agi_bp);

	agino = be32_to_cpu(agi->agi_dirino);
	अगर (!xfs_verअगरy_agino_or_null(mp, agno, agino))
		xchk_block_set_corrupt(sc, sc->sa.agi_bp);

	/* Check unlinked inode buckets */
	क्रम (i = 0; i < XFS_AGI_UNLINKED_BUCKETS; i++) अणु
		agino = be32_to_cpu(agi->agi_unlinked[i]);
		अगर (!xfs_verअगरy_agino_or_null(mp, agno, agino))
			xchk_block_set_corrupt(sc, sc->sa.agi_bp);
	पूर्ण

	अगर (agi->agi_pad32 != cpu_to_be32(0))
		xchk_block_set_corrupt(sc, sc->sa.agi_bp);

	/* Do the incore counters match? */
	pag = xfs_perag_get(mp, agno);
	अगर (pag->pagi_count != be32_to_cpu(agi->agi_count))
		xchk_block_set_corrupt(sc, sc->sa.agi_bp);
	अगर (pag->pagi_मुक्तcount != be32_to_cpu(agi->agi_मुक्तcount))
		xchk_block_set_corrupt(sc, sc->sa.agi_bp);
	xfs_perag_put(pag);

	xchk_agi_xref(sc);
out:
	वापस error;
पूर्ण
