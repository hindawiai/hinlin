<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * Copyright (c) 2018 Red Hat, Inc.
 * All rights reserved.
 */

#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_bit.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_alloc_btree.h"
#समावेश "xfs_rmap_btree.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_ialloc.h"
#समावेश "xfs_rmap.h"
#समावेश "xfs_ag.h"
#समावेश "xfs_ag_resv.h"
#समावेश "xfs_health.h"
#समावेश "xfs_error.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_defer.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans.h"

अटल पूर्णांक
xfs_get_aghdr_buf(
	काष्ठा xfs_mount	*mp,
	xfs_daddr_t		blkno,
	माप_प्रकार			numblks,
	काष्ठा xfs_buf		**bpp,
	स्थिर काष्ठा xfs_buf_ops *ops)
अणु
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;

	error = xfs_buf_get_uncached(mp->m_ddev_targp, numblks, 0, &bp);
	अगर (error)
		वापस error;

	xfs_buf_zero(bp, 0, BBTOB(bp->b_length));
	bp->b_bn = blkno;
	bp->b_maps[0].bm_bn = blkno;
	bp->b_ops = ops;

	*bpp = bp;
	वापस 0;
पूर्ण

अटल अंतरभूत bool is_log_ag(काष्ठा xfs_mount *mp, काष्ठा aghdr_init_data *id)
अणु
	वापस mp->m_sb.sb_logstart > 0 &&
	       id->agno == XFS_FSB_TO_AGNO(mp, mp->m_sb.sb_logstart);
पूर्ण

/*
 * Generic btree root block init function
 */
अटल व्योम
xfs_btroot_init(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_buf		*bp,
	काष्ठा aghdr_init_data	*id)
अणु
	xfs_btree_init_block(mp, bp, id->type, 0, 0, id->agno);
पूर्ण

/* Finish initializing a मुक्त space btree. */
अटल व्योम
xfs_मुक्तsp_init_recs(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_buf		*bp,
	काष्ठा aghdr_init_data	*id)
अणु
	काष्ठा xfs_alloc_rec	*arec;
	काष्ठा xfs_btree_block	*block = XFS_BUF_TO_BLOCK(bp);

	arec = XFS_ALLOC_REC_ADDR(mp, XFS_BUF_TO_BLOCK(bp), 1);
	arec->ar_startblock = cpu_to_be32(mp->m_ag_pपुनः_स्मृति_blocks);

	अगर (is_log_ag(mp, id)) अणु
		काष्ठा xfs_alloc_rec	*nrec;
		xfs_agblock_t		start = XFS_FSB_TO_AGBNO(mp,
							mp->m_sb.sb_logstart);

		ASSERT(start >= mp->m_ag_pपुनः_स्मृति_blocks);
		अगर (start != mp->m_ag_pपुनः_स्मृति_blocks) अणु
			/*
			 * Modअगरy first record to pad stripe align of log
			 */
			arec->ar_blockcount = cpu_to_be32(start -
						mp->m_ag_pपुनः_स्मृति_blocks);
			nrec = arec + 1;

			/*
			 * Insert second record at start of पूर्णांकernal log
			 * which then माला_लो trimmed.
			 */
			nrec->ar_startblock = cpu_to_be32(
					be32_to_cpu(arec->ar_startblock) +
					be32_to_cpu(arec->ar_blockcount));
			arec = nrec;
			be16_add_cpu(&block->bb_numrecs, 1);
		पूर्ण
		/*
		 * Change record start to after the पूर्णांकernal log
		 */
		be32_add_cpu(&arec->ar_startblock, mp->m_sb.sb_logblocks);
	पूर्ण

	/*
	 * Calculate the record block count and check क्रम the हाल where
	 * the log might have consumed all available space in the AG. If
	 * so, reset the record count to 0 to aव्योम exposure of an invalid
	 * record start block.
	 */
	arec->ar_blockcount = cpu_to_be32(id->agsize -
					  be32_to_cpu(arec->ar_startblock));
	अगर (!arec->ar_blockcount)
		block->bb_numrecs = 0;
पूर्ण

/*
 * Alloc btree root block init functions
 */
अटल व्योम
xfs_bnoroot_init(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_buf		*bp,
	काष्ठा aghdr_init_data	*id)
अणु
	xfs_btree_init_block(mp, bp, XFS_BTNUM_BNO, 0, 1, id->agno);
	xfs_मुक्तsp_init_recs(mp, bp, id);
पूर्ण

अटल व्योम
xfs_cntroot_init(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_buf		*bp,
	काष्ठा aghdr_init_data	*id)
अणु
	xfs_btree_init_block(mp, bp, XFS_BTNUM_CNT, 0, 1, id->agno);
	xfs_मुक्तsp_init_recs(mp, bp, id);
पूर्ण

/*
 * Reverse map root block init
 */
अटल व्योम
xfs_rmaproot_init(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_buf		*bp,
	काष्ठा aghdr_init_data	*id)
अणु
	काष्ठा xfs_btree_block	*block = XFS_BUF_TO_BLOCK(bp);
	काष्ठा xfs_rmap_rec	*rrec;

	xfs_btree_init_block(mp, bp, XFS_BTNUM_RMAP, 0, 4, id->agno);

	/*
	 * mark the AG header regions as अटल metadata The BNO
	 * btree block is the first block after the headers, so
	 * it's location defines the size of region the अटल
	 * metadata consumes.
	 *
	 * Note: unlike mkfs, we never have to account क्रम log
	 * space when growing the data regions
	 */
	rrec = XFS_RMAP_REC_ADDR(block, 1);
	rrec->rm_startblock = 0;
	rrec->rm_blockcount = cpu_to_be32(XFS_BNO_BLOCK(mp));
	rrec->rm_owner = cpu_to_be64(XFS_RMAP_OWN_FS);
	rrec->rm_offset = 0;

	/* account मुक्तspace btree root blocks */
	rrec = XFS_RMAP_REC_ADDR(block, 2);
	rrec->rm_startblock = cpu_to_be32(XFS_BNO_BLOCK(mp));
	rrec->rm_blockcount = cpu_to_be32(2);
	rrec->rm_owner = cpu_to_be64(XFS_RMAP_OWN_AG);
	rrec->rm_offset = 0;

	/* account inode btree root blocks */
	rrec = XFS_RMAP_REC_ADDR(block, 3);
	rrec->rm_startblock = cpu_to_be32(XFS_IBT_BLOCK(mp));
	rrec->rm_blockcount = cpu_to_be32(XFS_RMAP_BLOCK(mp) -
					  XFS_IBT_BLOCK(mp));
	rrec->rm_owner = cpu_to_be64(XFS_RMAP_OWN_INOBT);
	rrec->rm_offset = 0;

	/* account क्रम rmap btree root */
	rrec = XFS_RMAP_REC_ADDR(block, 4);
	rrec->rm_startblock = cpu_to_be32(XFS_RMAP_BLOCK(mp));
	rrec->rm_blockcount = cpu_to_be32(1);
	rrec->rm_owner = cpu_to_be64(XFS_RMAP_OWN_AG);
	rrec->rm_offset = 0;

	/* account क्रम refc btree root */
	अगर (xfs_sb_version_hasreflink(&mp->m_sb)) अणु
		rrec = XFS_RMAP_REC_ADDR(block, 5);
		rrec->rm_startblock = cpu_to_be32(xfs_refc_block(mp));
		rrec->rm_blockcount = cpu_to_be32(1);
		rrec->rm_owner = cpu_to_be64(XFS_RMAP_OWN_REFC);
		rrec->rm_offset = 0;
		be16_add_cpu(&block->bb_numrecs, 1);
	पूर्ण

	/* account क्रम the log space */
	अगर (is_log_ag(mp, id)) अणु
		rrec = XFS_RMAP_REC_ADDR(block,
				be16_to_cpu(block->bb_numrecs) + 1);
		rrec->rm_startblock = cpu_to_be32(
				XFS_FSB_TO_AGBNO(mp, mp->m_sb.sb_logstart));
		rrec->rm_blockcount = cpu_to_be32(mp->m_sb.sb_logblocks);
		rrec->rm_owner = cpu_to_be64(XFS_RMAP_OWN_LOG);
		rrec->rm_offset = 0;
		be16_add_cpu(&block->bb_numrecs, 1);
	पूर्ण
पूर्ण

/*
 * Initialise new secondary superblocks with the pre-grow geometry, but mark
 * them as "in progress" so we know they haven't yet been activated. This will
 * get cleared when the update with the new geometry inक्रमmation is करोne after
 * changes to the primary are committed. This isn't strictly necessary, but we
 * get it क्रम मुक्त with the delayed buffer ग_लिखो lists and it means we can tell
 * अगर a grow operation didn't complete properly after the fact.
 */
अटल व्योम
xfs_sbblock_init(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_buf		*bp,
	काष्ठा aghdr_init_data	*id)
अणु
	काष्ठा xfs_dsb		*dsb = bp->b_addr;

	xfs_sb_to_disk(dsb, &mp->m_sb);
	dsb->sb_inprogress = 1;
पूर्ण

अटल व्योम
xfs_agfblock_init(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_buf		*bp,
	काष्ठा aghdr_init_data	*id)
अणु
	काष्ठा xfs_agf		*agf = bp->b_addr;
	xfs_extlen_t		पंचांगpsize;

	agf->agf_magicnum = cpu_to_be32(XFS_AGF_MAGIC);
	agf->agf_versionnum = cpu_to_be32(XFS_AGF_VERSION);
	agf->agf_seqno = cpu_to_be32(id->agno);
	agf->agf_length = cpu_to_be32(id->agsize);
	agf->agf_roots[XFS_BTNUM_BNOi] = cpu_to_be32(XFS_BNO_BLOCK(mp));
	agf->agf_roots[XFS_BTNUM_CNTi] = cpu_to_be32(XFS_CNT_BLOCK(mp));
	agf->agf_levels[XFS_BTNUM_BNOi] = cpu_to_be32(1);
	agf->agf_levels[XFS_BTNUM_CNTi] = cpu_to_be32(1);
	अगर (xfs_sb_version_hasrmapbt(&mp->m_sb)) अणु
		agf->agf_roots[XFS_BTNUM_RMAPi] =
					cpu_to_be32(XFS_RMAP_BLOCK(mp));
		agf->agf_levels[XFS_BTNUM_RMAPi] = cpu_to_be32(1);
		agf->agf_rmap_blocks = cpu_to_be32(1);
	पूर्ण

	agf->agf_flfirst = cpu_to_be32(1);
	agf->agf_fllast = 0;
	agf->agf_flcount = 0;
	पंचांगpsize = id->agsize - mp->m_ag_pपुनः_स्मृति_blocks;
	agf->agf_मुक्तblks = cpu_to_be32(पंचांगpsize);
	agf->agf_दीर्घest = cpu_to_be32(पंचांगpsize);
	अगर (xfs_sb_version_hascrc(&mp->m_sb))
		uuid_copy(&agf->agf_uuid, &mp->m_sb.sb_meta_uuid);
	अगर (xfs_sb_version_hasreflink(&mp->m_sb)) अणु
		agf->agf_refcount_root = cpu_to_be32(
				xfs_refc_block(mp));
		agf->agf_refcount_level = cpu_to_be32(1);
		agf->agf_refcount_blocks = cpu_to_be32(1);
	पूर्ण

	अगर (is_log_ag(mp, id)) अणु
		पूर्णांक64_t	logblocks = mp->m_sb.sb_logblocks;

		be32_add_cpu(&agf->agf_मुक्तblks, -logblocks);
		agf->agf_दीर्घest = cpu_to_be32(id->agsize -
			XFS_FSB_TO_AGBNO(mp, mp->m_sb.sb_logstart) - logblocks);
	पूर्ण
पूर्ण

अटल व्योम
xfs_agflblock_init(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_buf		*bp,
	काष्ठा aghdr_init_data	*id)
अणु
	काष्ठा xfs_agfl		*agfl = XFS_BUF_TO_AGFL(bp);
	__be32			*agfl_bno;
	पूर्णांक			bucket;

	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		agfl->agfl_magicnum = cpu_to_be32(XFS_AGFL_MAGIC);
		agfl->agfl_seqno = cpu_to_be32(id->agno);
		uuid_copy(&agfl->agfl_uuid, &mp->m_sb.sb_meta_uuid);
	पूर्ण

	agfl_bno = xfs_buf_to_agfl_bno(bp);
	क्रम (bucket = 0; bucket < xfs_agfl_size(mp); bucket++)
		agfl_bno[bucket] = cpu_to_be32(शून्यAGBLOCK);
पूर्ण

अटल व्योम
xfs_agiblock_init(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_buf		*bp,
	काष्ठा aghdr_init_data	*id)
अणु
	काष्ठा xfs_agi		*agi = bp->b_addr;
	पूर्णांक			bucket;

	agi->agi_magicnum = cpu_to_be32(XFS_AGI_MAGIC);
	agi->agi_versionnum = cpu_to_be32(XFS_AGI_VERSION);
	agi->agi_seqno = cpu_to_be32(id->agno);
	agi->agi_length = cpu_to_be32(id->agsize);
	agi->agi_count = 0;
	agi->agi_root = cpu_to_be32(XFS_IBT_BLOCK(mp));
	agi->agi_level = cpu_to_be32(1);
	agi->agi_मुक्तcount = 0;
	agi->agi_newino = cpu_to_be32(शून्यAGINO);
	agi->agi_dirino = cpu_to_be32(शून्यAGINO);
	अगर (xfs_sb_version_hascrc(&mp->m_sb))
		uuid_copy(&agi->agi_uuid, &mp->m_sb.sb_meta_uuid);
	अगर (xfs_sb_version_hasfinobt(&mp->m_sb)) अणु
		agi->agi_मुक्त_root = cpu_to_be32(XFS_FIBT_BLOCK(mp));
		agi->agi_मुक्त_level = cpu_to_be32(1);
	पूर्ण
	क्रम (bucket = 0; bucket < XFS_AGI_UNLINKED_BUCKETS; bucket++)
		agi->agi_unlinked[bucket] = cpu_to_be32(शून्यAGINO);
	अगर (xfs_sb_version_hasinobtcounts(&mp->m_sb)) अणु
		agi->agi_iblocks = cpu_to_be32(1);
		अगर (xfs_sb_version_hasfinobt(&mp->m_sb))
			agi->agi_fblocks = cpu_to_be32(1);
	पूर्ण
पूर्ण

प्रकार व्योम (*aghdr_init_work_f)(काष्ठा xfs_mount *mp, काष्ठा xfs_buf *bp,
				  काष्ठा aghdr_init_data *id);
अटल पूर्णांक
xfs_ag_init_hdr(
	काष्ठा xfs_mount	*mp,
	काष्ठा aghdr_init_data	*id,
	aghdr_init_work_f	work,
	स्थिर काष्ठा xfs_buf_ops *ops)
अणु
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;

	error = xfs_get_aghdr_buf(mp, id->daddr, id->numblks, &bp, ops);
	अगर (error)
		वापस error;

	(*work)(mp, bp, id);

	xfs_buf_delwri_queue(bp, &id->buffer_list);
	xfs_buf_rअन्यथा(bp);
	वापस 0;
पूर्ण

काष्ठा xfs_aghdr_grow_data अणु
	xfs_daddr_t		daddr;
	माप_प्रकार			numblks;
	स्थिर काष्ठा xfs_buf_ops *ops;
	aghdr_init_work_f	work;
	xfs_btnum_t		type;
	bool			need_init;
पूर्ण;

/*
 * Prepare new AG headers to be written to disk. We use uncached buffers here,
 * as it is assumed these new AG headers are currently beyond the currently
 * valid fileप्रणाली address space. Using cached buffers would trip over खातापूर्णS
 * corruption detection alogrithms in the buffer cache lookup routines.
 *
 * This is a non-transactional function, but the prepared buffers are added to a
 * delayed ग_लिखो buffer list supplied by the caller so they can submit them to
 * disk and रुको on them as required.
 */
पूर्णांक
xfs_ag_init_headers(
	काष्ठा xfs_mount	*mp,
	काष्ठा aghdr_init_data	*id)

अणु
	काष्ठा xfs_aghdr_grow_data aghdr_data[] = अणु
	अणु /* SB */
		.daddr = XFS_AG_DADDR(mp, id->agno, XFS_SB_DADDR),
		.numblks = XFS_FSS_TO_BB(mp, 1),
		.ops = &xfs_sb_buf_ops,
		.work = &xfs_sbblock_init,
		.need_init = true
	पूर्ण,
	अणु /* AGF */
		.daddr = XFS_AG_DADDR(mp, id->agno, XFS_AGF_DADDR(mp)),
		.numblks = XFS_FSS_TO_BB(mp, 1),
		.ops = &xfs_agf_buf_ops,
		.work = &xfs_agfblock_init,
		.need_init = true
	पूर्ण,
	अणु /* AGFL */
		.daddr = XFS_AG_DADDR(mp, id->agno, XFS_AGFL_DADDR(mp)),
		.numblks = XFS_FSS_TO_BB(mp, 1),
		.ops = &xfs_agfl_buf_ops,
		.work = &xfs_agflblock_init,
		.need_init = true
	पूर्ण,
	अणु /* AGI */
		.daddr = XFS_AG_DADDR(mp, id->agno, XFS_AGI_DADDR(mp)),
		.numblks = XFS_FSS_TO_BB(mp, 1),
		.ops = &xfs_agi_buf_ops,
		.work = &xfs_agiblock_init,
		.need_init = true
	पूर्ण,
	अणु /* BNO root block */
		.daddr = XFS_AGB_TO_DADDR(mp, id->agno, XFS_BNO_BLOCK(mp)),
		.numblks = BTOBB(mp->m_sb.sb_blocksize),
		.ops = &xfs_bnobt_buf_ops,
		.work = &xfs_bnoroot_init,
		.need_init = true
	पूर्ण,
	अणु /* CNT root block */
		.daddr = XFS_AGB_TO_DADDR(mp, id->agno, XFS_CNT_BLOCK(mp)),
		.numblks = BTOBB(mp->m_sb.sb_blocksize),
		.ops = &xfs_cntbt_buf_ops,
		.work = &xfs_cntroot_init,
		.need_init = true
	पूर्ण,
	अणु /* INO root block */
		.daddr = XFS_AGB_TO_DADDR(mp, id->agno, XFS_IBT_BLOCK(mp)),
		.numblks = BTOBB(mp->m_sb.sb_blocksize),
		.ops = &xfs_inobt_buf_ops,
		.work = &xfs_btroot_init,
		.type = XFS_BTNUM_INO,
		.need_init = true
	पूर्ण,
	अणु /* FINO root block */
		.daddr = XFS_AGB_TO_DADDR(mp, id->agno, XFS_FIBT_BLOCK(mp)),
		.numblks = BTOBB(mp->m_sb.sb_blocksize),
		.ops = &xfs_finobt_buf_ops,
		.work = &xfs_btroot_init,
		.type = XFS_BTNUM_FINO,
		.need_init =  xfs_sb_version_hasfinobt(&mp->m_sb)
	पूर्ण,
	अणु /* RMAP root block */
		.daddr = XFS_AGB_TO_DADDR(mp, id->agno, XFS_RMAP_BLOCK(mp)),
		.numblks = BTOBB(mp->m_sb.sb_blocksize),
		.ops = &xfs_rmapbt_buf_ops,
		.work = &xfs_rmaproot_init,
		.need_init = xfs_sb_version_hasrmapbt(&mp->m_sb)
	पूर्ण,
	अणु /* REFC root block */
		.daddr = XFS_AGB_TO_DADDR(mp, id->agno, xfs_refc_block(mp)),
		.numblks = BTOBB(mp->m_sb.sb_blocksize),
		.ops = &xfs_refcountbt_buf_ops,
		.work = &xfs_btroot_init,
		.type = XFS_BTNUM_REFC,
		.need_init = xfs_sb_version_hasreflink(&mp->m_sb)
	पूर्ण,
	अणु /* शून्य terminating block */
		.daddr = XFS_BUF_DADDR_शून्य,
	पूर्ण
	पूर्ण;
	काष्ठा  xfs_aghdr_grow_data *dp;
	पूर्णांक			error = 0;

	/* Account क्रम AG मुक्त space in new AG */
	id->nमुक्त += id->agsize - mp->m_ag_pपुनः_स्मृति_blocks;
	क्रम (dp = &aghdr_data[0]; dp->daddr != XFS_BUF_DADDR_शून्य; dp++) अणु
		अगर (!dp->need_init)
			जारी;

		id->daddr = dp->daddr;
		id->numblks = dp->numblks;
		id->type = dp->type;
		error = xfs_ag_init_hdr(mp, id, dp->work, dp->ops);
		अगर (error)
			अवरोध;
	पूर्ण
	वापस error;
पूर्ण

पूर्णांक
xfs_ag_shrink_space(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	**tpp,
	xfs_agnumber_t		agno,
	xfs_extlen_t		delta)
अणु
	काष्ठा xfs_alloc_arg	args = अणु
		.tp	= *tpp,
		.mp	= mp,
		.type	= XFS_ALLOCTYPE_THIS_BNO,
		.minlen = delta,
		.maxlen = delta,
		.oinfo	= XFS_RMAP_OINFO_SKIP_UPDATE,
		.resv	= XFS_AG_RESV_NONE,
		.prod	= 1
	पूर्ण;
	काष्ठा xfs_buf		*agibp, *agfbp;
	काष्ठा xfs_agi		*agi;
	काष्ठा xfs_agf		*agf;
	पूर्णांक			error, err2;

	ASSERT(agno == mp->m_sb.sb_agcount - 1);
	error = xfs_ialloc_पढ़ो_agi(mp, *tpp, agno, &agibp);
	अगर (error)
		वापस error;

	agi = agibp->b_addr;

	error = xfs_alloc_पढ़ो_agf(mp, *tpp, agno, 0, &agfbp);
	अगर (error)
		वापस error;

	agf = agfbp->b_addr;
	/* some extra paranoid checks beक्रमe we shrink the ag */
	अगर (XFS_IS_CORRUPT(mp, agf->agf_length != agi->agi_length))
		वापस -EFSCORRUPTED;
	अगर (delta >= agi->agi_length)
		वापस -EINVAL;

	args.fsbno = XFS_AGB_TO_FSB(mp, agno,
				    be32_to_cpu(agi->agi_length) - delta);

	/*
	 * Disable perag reservations so it करोesn't cause the allocation request
	 * to fail. We'll reestablish reservation beक्रमe we वापस.
	 */
	error = xfs_ag_resv_मुक्त(agibp->b_pag);
	अगर (error)
		वापस error;

	/* पूर्णांकernal log shouldn't also show up in the मुक्त space btrees */
	error = xfs_alloc_vextent(&args);
	अगर (!error && args.agbno == शून्यAGBLOCK)
		error = -ENOSPC;

	अगर (error) अणु
		/*
		 * अगर extent allocation fails, need to roll the transaction to
		 * ensure that the AGFL fixup has been committed anyway.
		 */
		xfs_trans_bhold(*tpp, agfbp);
		err2 = xfs_trans_roll(tpp);
		अगर (err2)
			वापस err2;
		xfs_trans_bjoin(*tpp, agfbp);
		जाओ resv_init_out;
	पूर्ण

	/*
	 * अगर successfully deleted from मुक्तspace btrees, need to confirm
	 * per-AG reservation works as expected.
	 */
	be32_add_cpu(&agi->agi_length, -delta);
	be32_add_cpu(&agf->agf_length, -delta);

	err2 = xfs_ag_resv_init(agibp->b_pag, *tpp);
	अगर (err2) अणु
		be32_add_cpu(&agi->agi_length, delta);
		be32_add_cpu(&agf->agf_length, delta);
		अगर (err2 != -ENOSPC)
			जाओ resv_err;

		__xfs_bmap_add_मुक्त(*tpp, args.fsbno, delta, शून्य, true);

		/*
		 * Roll the transaction beक्रमe trying to re-init the per-ag
		 * reservation. The new transaction is clean so it will cancel
		 * without any side effects.
		 */
		error = xfs_defer_finish(tpp);
		अगर (error)
			वापस error;

		error = -ENOSPC;
		जाओ resv_init_out;
	पूर्ण
	xfs_ialloc_log_agi(*tpp, agibp, XFS_AGI_LENGTH);
	xfs_alloc_log_agf(*tpp, agfbp, XFS_AGF_LENGTH);
	वापस 0;
resv_init_out:
	err2 = xfs_ag_resv_init(agibp->b_pag, *tpp);
	अगर (!err2)
		वापस error;
resv_err:
	xfs_warn(mp, "Error %d reserving per-AG metadata reserve pool.", err2);
	xfs_क्रमce_shutकरोwn(mp, SHUTDOWN_CORRUPT_INCORE);
	वापस err2;
पूर्ण

/*
 * Extent the AG indicated by the @id by the length passed in
 */
पूर्णांक
xfs_ag_extend_space(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	काष्ठा aghdr_init_data	*id,
	xfs_extlen_t		len)
अणु
	काष्ठा xfs_buf		*bp;
	काष्ठा xfs_agi		*agi;
	काष्ठा xfs_agf		*agf;
	पूर्णांक			error;

	/*
	 * Change the agi length.
	 */
	error = xfs_ialloc_पढ़ो_agi(mp, tp, id->agno, &bp);
	अगर (error)
		वापस error;

	agi = bp->b_addr;
	be32_add_cpu(&agi->agi_length, len);
	ASSERT(id->agno == mp->m_sb.sb_agcount - 1 ||
	       be32_to_cpu(agi->agi_length) == mp->m_sb.sb_agblocks);
	xfs_ialloc_log_agi(tp, bp, XFS_AGI_LENGTH);

	/*
	 * Change agf length.
	 */
	error = xfs_alloc_पढ़ो_agf(mp, tp, id->agno, 0, &bp);
	अगर (error)
		वापस error;

	agf = bp->b_addr;
	be32_add_cpu(&agf->agf_length, len);
	ASSERT(agf->agf_length == agi->agi_length);
	xfs_alloc_log_agf(tp, bp, XFS_AGF_LENGTH);

	/*
	 * Free the new space.
	 *
	 * XFS_RMAP_OINFO_SKIP_UPDATE is used here to tell the rmap btree that
	 * this करोesn't actually exist in the rmap btree.
	 */
	error = xfs_rmap_मुक्त(tp, bp, id->agno,
				be32_to_cpu(agf->agf_length) - len,
				len, &XFS_RMAP_OINFO_SKIP_UPDATE);
	अगर (error)
		वापस error;

	वापस  xfs_मुक्त_extent(tp, XFS_AGB_TO_FSB(mp, id->agno,
					be32_to_cpu(agf->agf_length) - len),
				len, &XFS_RMAP_OINFO_SKIP_UPDATE,
				XFS_AG_RESV_NONE);
पूर्ण

/* Retrieve AG geometry. */
पूर्णांक
xfs_ag_get_geometry(
	काष्ठा xfs_mount	*mp,
	xfs_agnumber_t		agno,
	काष्ठा xfs_ag_geometry	*ageo)
अणु
	काष्ठा xfs_buf		*agi_bp;
	काष्ठा xfs_buf		*agf_bp;
	काष्ठा xfs_agi		*agi;
	काष्ठा xfs_agf		*agf;
	काष्ठा xfs_perag	*pag;
	अचिन्हित पूर्णांक		मुक्तblks;
	पूर्णांक			error;

	अगर (agno >= mp->m_sb.sb_agcount)
		वापस -EINVAL;

	/* Lock the AG headers. */
	error = xfs_ialloc_पढ़ो_agi(mp, शून्य, agno, &agi_bp);
	अगर (error)
		वापस error;
	error = xfs_alloc_पढ़ो_agf(mp, शून्य, agno, 0, &agf_bp);
	अगर (error)
		जाओ out_agi;

	pag = agi_bp->b_pag;

	/* Fill out क्रमm. */
	स_रखो(ageo, 0, माप(*ageo));
	ageo->ag_number = agno;

	agi = agi_bp->b_addr;
	ageo->ag_icount = be32_to_cpu(agi->agi_count);
	ageo->ag_अगरree = be32_to_cpu(agi->agi_मुक्तcount);

	agf = agf_bp->b_addr;
	ageo->ag_length = be32_to_cpu(agf->agf_length);
	मुक्तblks = pag->pagf_मुक्तblks +
		   pag->pagf_flcount +
		   pag->pagf_btreeblks -
		   xfs_ag_resv_needed(pag, XFS_AG_RESV_NONE);
	ageo->ag_मुक्तblks = मुक्तblks;
	xfs_ag_geom_health(pag, ageo);

	/* Release resources. */
	xfs_buf_rअन्यथा(agf_bp);
out_agi:
	xfs_buf_rअन्यथा(agi_bp);
	वापस error;
पूर्ण
