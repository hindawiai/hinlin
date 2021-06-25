<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_btree_staging.h"
#समावेश "xfs_refcount_btree.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_error.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_bit.h"
#समावेश "xfs_rmap.h"

अटल काष्ठा xfs_btree_cur *
xfs_refcountbt_dup_cursor(
	काष्ठा xfs_btree_cur	*cur)
अणु
	वापस xfs_refcountbt_init_cursor(cur->bc_mp, cur->bc_tp,
			cur->bc_ag.agbp, cur->bc_ag.agno);
पूर्ण

STATIC व्योम
xfs_refcountbt_set_root(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*ptr,
	पूर्णांक			inc)
अणु
	काष्ठा xfs_buf		*agbp = cur->bc_ag.agbp;
	काष्ठा xfs_agf		*agf = agbp->b_addr;
	काष्ठा xfs_perag	*pag = agbp->b_pag;

	ASSERT(ptr->s != 0);

	agf->agf_refcount_root = ptr->s;
	be32_add_cpu(&agf->agf_refcount_level, inc);
	pag->pagf_refcount_level += inc;

	xfs_alloc_log_agf(cur->bc_tp, agbp,
			XFS_AGF_REFCOUNT_ROOT | XFS_AGF_REFCOUNT_LEVEL);
पूर्ण

STATIC पूर्णांक
xfs_refcountbt_alloc_block(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*start,
	जोड़ xfs_btree_ptr	*new,
	पूर्णांक			*stat)
अणु
	काष्ठा xfs_buf		*agbp = cur->bc_ag.agbp;
	काष्ठा xfs_agf		*agf = agbp->b_addr;
	काष्ठा xfs_alloc_arg	args;		/* block allocation args */
	पूर्णांक			error;		/* error वापस value */

	स_रखो(&args, 0, माप(args));
	args.tp = cur->bc_tp;
	args.mp = cur->bc_mp;
	args.type = XFS_ALLOCTYPE_NEAR_BNO;
	args.fsbno = XFS_AGB_TO_FSB(cur->bc_mp, cur->bc_ag.agno,
			xfs_refc_block(args.mp));
	args.oinfo = XFS_RMAP_OINFO_REFC;
	args.minlen = args.maxlen = args.prod = 1;
	args.resv = XFS_AG_RESV_METADATA;

	error = xfs_alloc_vextent(&args);
	अगर (error)
		जाओ out_error;
	trace_xfs_refcountbt_alloc_block(cur->bc_mp, cur->bc_ag.agno,
			args.agbno, 1);
	अगर (args.fsbno == शून्यFSBLOCK) अणु
		*stat = 0;
		वापस 0;
	पूर्ण
	ASSERT(args.agno == cur->bc_ag.agno);
	ASSERT(args.len == 1);

	new->s = cpu_to_be32(args.agbno);
	be32_add_cpu(&agf->agf_refcount_blocks, 1);
	xfs_alloc_log_agf(cur->bc_tp, agbp, XFS_AGF_REFCOUNT_BLOCKS);

	*stat = 1;
	वापस 0;

out_error:
	वापस error;
पूर्ण

STATIC पूर्णांक
xfs_refcountbt_मुक्त_block(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = cur->bc_mp;
	काष्ठा xfs_buf		*agbp = cur->bc_ag.agbp;
	काष्ठा xfs_agf		*agf = agbp->b_addr;
	xfs_fsblock_t		fsbno = XFS_DADDR_TO_FSB(mp, XFS_BUF_ADDR(bp));
	पूर्णांक			error;

	trace_xfs_refcountbt_मुक्त_block(cur->bc_mp, cur->bc_ag.agno,
			XFS_FSB_TO_AGBNO(cur->bc_mp, fsbno), 1);
	be32_add_cpu(&agf->agf_refcount_blocks, -1);
	xfs_alloc_log_agf(cur->bc_tp, agbp, XFS_AGF_REFCOUNT_BLOCKS);
	error = xfs_मुक्त_extent(cur->bc_tp, fsbno, 1, &XFS_RMAP_OINFO_REFC,
			XFS_AG_RESV_METADATA);
	अगर (error)
		वापस error;

	वापस error;
पूर्ण

STATIC पूर्णांक
xfs_refcountbt_get_minrecs(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level)
अणु
	वापस cur->bc_mp->m_refc_mnr[level != 0];
पूर्ण

STATIC पूर्णांक
xfs_refcountbt_get_maxrecs(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level)
अणु
	वापस cur->bc_mp->m_refc_mxr[level != 0];
पूर्ण

STATIC व्योम
xfs_refcountbt_init_key_from_rec(
	जोड़ xfs_btree_key	*key,
	जोड़ xfs_btree_rec	*rec)
अणु
	key->refc.rc_startblock = rec->refc.rc_startblock;
पूर्ण

STATIC व्योम
xfs_refcountbt_init_high_key_from_rec(
	जोड़ xfs_btree_key	*key,
	जोड़ xfs_btree_rec	*rec)
अणु
	__u32			x;

	x = be32_to_cpu(rec->refc.rc_startblock);
	x += be32_to_cpu(rec->refc.rc_blockcount) - 1;
	key->refc.rc_startblock = cpu_to_be32(x);
पूर्ण

STATIC व्योम
xfs_refcountbt_init_rec_from_cur(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_rec	*rec)
अणु
	rec->refc.rc_startblock = cpu_to_be32(cur->bc_rec.rc.rc_startblock);
	rec->refc.rc_blockcount = cpu_to_be32(cur->bc_rec.rc.rc_blockcount);
	rec->refc.rc_refcount = cpu_to_be32(cur->bc_rec.rc.rc_refcount);
पूर्ण

STATIC व्योम
xfs_refcountbt_init_ptr_from_cur(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*ptr)
अणु
	काष्ठा xfs_agf		*agf = cur->bc_ag.agbp->b_addr;

	ASSERT(cur->bc_ag.agno == be32_to_cpu(agf->agf_seqno));

	ptr->s = agf->agf_refcount_root;
पूर्ण

STATIC पूर्णांक64_t
xfs_refcountbt_key_dअगरf(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*key)
अणु
	काष्ठा xfs_refcount_irec	*rec = &cur->bc_rec.rc;
	काष्ठा xfs_refcount_key		*kp = &key->refc;

	वापस (पूर्णांक64_t)be32_to_cpu(kp->rc_startblock) - rec->rc_startblock;
पूर्ण

STATIC पूर्णांक64_t
xfs_refcountbt_dअगरf_two_keys(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*k1,
	जोड़ xfs_btree_key	*k2)
अणु
	वापस (पूर्णांक64_t)be32_to_cpu(k1->refc.rc_startblock) -
			  be32_to_cpu(k2->refc.rc_startblock);
पूर्ण

STATIC xfs_failaddr_t
xfs_refcountbt_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_btree_block	*block = XFS_BUF_TO_BLOCK(bp);
	काष्ठा xfs_perag	*pag = bp->b_pag;
	xfs_failaddr_t		fa;
	अचिन्हित पूर्णांक		level;

	अगर (!xfs_verअगरy_magic(bp, block->bb_magic))
		वापस __this_address;

	अगर (!xfs_sb_version_hasreflink(&mp->m_sb))
		वापस __this_address;
	fa = xfs_btree_sblock_v5hdr_verअगरy(bp);
	अगर (fa)
		वापस fa;

	level = be16_to_cpu(block->bb_level);
	अगर (pag && pag->pagf_init) अणु
		अगर (level >= pag->pagf_refcount_level)
			वापस __this_address;
	पूर्ण अन्यथा अगर (level >= mp->m_refc_maxlevels)
		वापस __this_address;

	वापस xfs_btree_sblock_verअगरy(bp, mp->m_refc_mxr[level != 0]);
पूर्ण

STATIC व्योम
xfs_refcountbt_पढ़ो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	xfs_failaddr_t	fa;

	अगर (!xfs_btree_sblock_verअगरy_crc(bp))
		xfs_verअगरier_error(bp, -EFSBADCRC, __this_address);
	अन्यथा अणु
		fa = xfs_refcountbt_verअगरy(bp);
		अगर (fa)
			xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
	पूर्ण

	अगर (bp->b_error)
		trace_xfs_btree_corrupt(bp, _RET_IP_);
पूर्ण

STATIC व्योम
xfs_refcountbt_ग_लिखो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	xfs_failaddr_t	fa;

	fa = xfs_refcountbt_verअगरy(bp);
	अगर (fa) अणु
		trace_xfs_btree_corrupt(bp, _RET_IP_);
		xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
		वापस;
	पूर्ण
	xfs_btree_sblock_calc_crc(bp);

पूर्ण

स्थिर काष्ठा xfs_buf_ops xfs_refcountbt_buf_ops = अणु
	.name			= "xfs_refcountbt",
	.magic			= अणु 0, cpu_to_be32(XFS_REFC_CRC_MAGIC) पूर्ण,
	.verअगरy_पढ़ो		= xfs_refcountbt_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो		= xfs_refcountbt_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा		= xfs_refcountbt_verअगरy,
पूर्ण;

STATIC पूर्णांक
xfs_refcountbt_keys_inorder(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*k1,
	जोड़ xfs_btree_key	*k2)
अणु
	वापस be32_to_cpu(k1->refc.rc_startblock) <
	       be32_to_cpu(k2->refc.rc_startblock);
पूर्ण

STATIC पूर्णांक
xfs_refcountbt_recs_inorder(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_rec	*r1,
	जोड़ xfs_btree_rec	*r2)
अणु
	वापस  be32_to_cpu(r1->refc.rc_startblock) +
		be32_to_cpu(r1->refc.rc_blockcount) <=
		be32_to_cpu(r2->refc.rc_startblock);
पूर्ण

अटल स्थिर काष्ठा xfs_btree_ops xfs_refcountbt_ops = अणु
	.rec_len		= माप(काष्ठा xfs_refcount_rec),
	.key_len		= माप(काष्ठा xfs_refcount_key),

	.dup_cursor		= xfs_refcountbt_dup_cursor,
	.set_root		= xfs_refcountbt_set_root,
	.alloc_block		= xfs_refcountbt_alloc_block,
	.मुक्त_block		= xfs_refcountbt_मुक्त_block,
	.get_minrecs		= xfs_refcountbt_get_minrecs,
	.get_maxrecs		= xfs_refcountbt_get_maxrecs,
	.init_key_from_rec	= xfs_refcountbt_init_key_from_rec,
	.init_high_key_from_rec	= xfs_refcountbt_init_high_key_from_rec,
	.init_rec_from_cur	= xfs_refcountbt_init_rec_from_cur,
	.init_ptr_from_cur	= xfs_refcountbt_init_ptr_from_cur,
	.key_dअगरf		= xfs_refcountbt_key_dअगरf,
	.buf_ops		= &xfs_refcountbt_buf_ops,
	.dअगरf_two_keys		= xfs_refcountbt_dअगरf_two_keys,
	.keys_inorder		= xfs_refcountbt_keys_inorder,
	.recs_inorder		= xfs_refcountbt_recs_inorder,
पूर्ण;

/*
 * Initialize a new refcount btree cursor.
 */
अटल काष्ठा xfs_btree_cur *
xfs_refcountbt_init_common(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno)
अणु
	काष्ठा xfs_btree_cur	*cur;

	ASSERT(agno != शून्यAGNUMBER);
	ASSERT(agno < mp->m_sb.sb_agcount);

	cur = kmem_cache_zalloc(xfs_btree_cur_zone, GFP_NOFS | __GFP_NOFAIL);
	cur->bc_tp = tp;
	cur->bc_mp = mp;
	cur->bc_btnum = XFS_BTNUM_REFC;
	cur->bc_blocklog = mp->m_sb.sb_blocklog;
	cur->bc_stम_से_भf = XFS_STATS_CALC_INDEX(xs_refcbt_2);

	cur->bc_ag.agno = agno;
	cur->bc_flags |= XFS_BTREE_CRC_BLOCKS;

	cur->bc_ag.refc.nr_ops = 0;
	cur->bc_ag.refc.shape_changes = 0;
	cur->bc_ops = &xfs_refcountbt_ops;
	वापस cur;
पूर्ण

/* Create a btree cursor. */
काष्ठा xfs_btree_cur *
xfs_refcountbt_init_cursor(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*agbp,
	xfs_agnumber_t		agno)
अणु
	काष्ठा xfs_agf		*agf = agbp->b_addr;
	काष्ठा xfs_btree_cur	*cur;

	cur = xfs_refcountbt_init_common(mp, tp, agno);
	cur->bc_nlevels = be32_to_cpu(agf->agf_refcount_level);
	cur->bc_ag.agbp = agbp;
	वापस cur;
पूर्ण

/* Create a btree cursor with a fake root क्रम staging. */
काष्ठा xfs_btree_cur *
xfs_refcountbt_stage_cursor(
	काष्ठा xfs_mount	*mp,
	काष्ठा xbtree_afakeroot	*afake,
	xfs_agnumber_t		agno)
अणु
	काष्ठा xfs_btree_cur	*cur;

	cur = xfs_refcountbt_init_common(mp, शून्य, agno);
	xfs_btree_stage_afakeroot(cur, afake);
	वापस cur;
पूर्ण

/*
 * Swap in the new btree root.  Once we pass this poपूर्णांक the newly rebuilt btree
 * is in place and we have to समाप्त off all the old btree blocks.
 */
व्योम
xfs_refcountbt_commit_staged_btree(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*agbp)
अणु
	काष्ठा xfs_agf		*agf = agbp->b_addr;
	काष्ठा xbtree_afakeroot	*afake = cur->bc_ag.afake;

	ASSERT(cur->bc_flags & XFS_BTREE_STAGING);

	agf->agf_refcount_root = cpu_to_be32(afake->af_root);
	agf->agf_refcount_level = cpu_to_be32(afake->af_levels);
	agf->agf_refcount_blocks = cpu_to_be32(afake->af_blocks);
	xfs_alloc_log_agf(tp, agbp, XFS_AGF_REFCOUNT_BLOCKS |
				    XFS_AGF_REFCOUNT_ROOT |
				    XFS_AGF_REFCOUNT_LEVEL);
	xfs_btree_commit_afakeroot(cur, tp, agbp, &xfs_refcountbt_ops);
पूर्ण

/*
 * Calculate the number of records in a refcount btree block.
 */
पूर्णांक
xfs_refcountbt_maxrecs(
	पूर्णांक			blocklen,
	bool			leaf)
अणु
	blocklen -= XFS_REFCOUNT_BLOCK_LEN;

	अगर (leaf)
		वापस blocklen / माप(काष्ठा xfs_refcount_rec);
	वापस blocklen / (माप(काष्ठा xfs_refcount_key) +
			   माप(xfs_refcount_ptr_t));
पूर्ण

/* Compute the maximum height of a refcount btree. */
व्योम
xfs_refcountbt_compute_maxlevels(
	काष्ठा xfs_mount		*mp)
अणु
	mp->m_refc_maxlevels = xfs_btree_compute_maxlevels(
			mp->m_refc_mnr, mp->m_sb.sb_agblocks);
पूर्ण

/* Calculate the refcount btree size क्रम some records. */
xfs_extlen_t
xfs_refcountbt_calc_size(
	काष्ठा xfs_mount	*mp,
	अचिन्हित दीर्घ दीर्घ	len)
अणु
	वापस xfs_btree_calc_size(mp->m_refc_mnr, len);
पूर्ण

/*
 * Calculate the maximum refcount btree size.
 */
xfs_extlen_t
xfs_refcountbt_max_size(
	काष्ठा xfs_mount	*mp,
	xfs_agblock_t		agblocks)
अणु
	/* Bail out अगर we're uninitialized, which can happen in mkfs. */
	अगर (mp->m_refc_mxr[0] == 0)
		वापस 0;

	वापस xfs_refcountbt_calc_size(mp, agblocks);
पूर्ण

/*
 * Figure out how many blocks to reserve and how many are used by this btree.
 */
पूर्णांक
xfs_refcountbt_calc_reserves(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	xfs_extlen_t		*ask,
	xfs_extlen_t		*used)
अणु
	काष्ठा xfs_buf		*agbp;
	काष्ठा xfs_agf		*agf;
	xfs_agblock_t		agblocks;
	xfs_extlen_t		tree_len;
	पूर्णांक			error;

	अगर (!xfs_sb_version_hasreflink(&mp->m_sb))
		वापस 0;


	error = xfs_alloc_पढ़ो_agf(mp, tp, agno, 0, &agbp);
	अगर (error)
		वापस error;

	agf = agbp->b_addr;
	agblocks = be32_to_cpu(agf->agf_length);
	tree_len = be32_to_cpu(agf->agf_refcount_blocks);
	xfs_trans_brअन्यथा(tp, agbp);

	/*
	 * The log is permanently allocated, so the space it occupies will
	 * never be available क्रम the kinds of things that would require btree
	 * expansion.  We thereक्रमe can pretend the space isn't there.
	 */
	अगर (mp->m_sb.sb_logstart &&
	    XFS_FSB_TO_AGNO(mp, mp->m_sb.sb_logstart) == agno)
		agblocks -= mp->m_sb.sb_logblocks;

	*ask += xfs_refcountbt_max_size(mp, agblocks);
	*used += tree_len;

	वापस error;
पूर्ण
