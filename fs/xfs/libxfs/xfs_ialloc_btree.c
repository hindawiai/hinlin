<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2001,2005 Silicon Graphics, Inc.
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
#समावेश "xfs_btree.h"
#समावेश "xfs_btree_staging.h"
#समावेश "xfs_ialloc.h"
#समावेश "xfs_ialloc_btree.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_error.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_rmap.h"

STATIC पूर्णांक
xfs_inobt_get_minrecs(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level)
अणु
	वापस M_IGEO(cur->bc_mp)->inobt_mnr[level != 0];
पूर्ण

STATIC काष्ठा xfs_btree_cur *
xfs_inobt_dup_cursor(
	काष्ठा xfs_btree_cur	*cur)
अणु
	वापस xfs_inobt_init_cursor(cur->bc_mp, cur->bc_tp,
			cur->bc_ag.agbp, cur->bc_ag.agno,
			cur->bc_btnum);
पूर्ण

STATIC व्योम
xfs_inobt_set_root(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*nptr,
	पूर्णांक			inc)	/* level change */
अणु
	काष्ठा xfs_buf		*agbp = cur->bc_ag.agbp;
	काष्ठा xfs_agi		*agi = agbp->b_addr;

	agi->agi_root = nptr->s;
	be32_add_cpu(&agi->agi_level, inc);
	xfs_ialloc_log_agi(cur->bc_tp, agbp, XFS_AGI_ROOT | XFS_AGI_LEVEL);
पूर्ण

STATIC व्योम
xfs_finobt_set_root(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*nptr,
	पूर्णांक			inc)	/* level change */
अणु
	काष्ठा xfs_buf		*agbp = cur->bc_ag.agbp;
	काष्ठा xfs_agi		*agi = agbp->b_addr;

	agi->agi_मुक्त_root = nptr->s;
	be32_add_cpu(&agi->agi_मुक्त_level, inc);
	xfs_ialloc_log_agi(cur->bc_tp, agbp,
			   XFS_AGI_FREE_ROOT | XFS_AGI_FREE_LEVEL);
पूर्ण

/* Update the inode btree block counter क्रम this btree. */
अटल अंतरभूत व्योम
xfs_inobt_mod_blockcount(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			howmuch)
अणु
	काष्ठा xfs_buf		*agbp = cur->bc_ag.agbp;
	काष्ठा xfs_agi		*agi = agbp->b_addr;

	अगर (!xfs_sb_version_hasinobtcounts(&cur->bc_mp->m_sb))
		वापस;

	अगर (cur->bc_btnum == XFS_BTNUM_FINO)
		be32_add_cpu(&agi->agi_fblocks, howmuch);
	अन्यथा अगर (cur->bc_btnum == XFS_BTNUM_INO)
		be32_add_cpu(&agi->agi_iblocks, howmuch);
	xfs_ialloc_log_agi(cur->bc_tp, agbp, XFS_AGI_IBLOCKS);
पूर्ण

STATIC पूर्णांक
__xfs_inobt_alloc_block(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*start,
	जोड़ xfs_btree_ptr	*new,
	पूर्णांक			*stat,
	क्रमागत xfs_ag_resv_type	resv)
अणु
	xfs_alloc_arg_t		args;		/* block allocation args */
	पूर्णांक			error;		/* error वापस value */
	xfs_agblock_t		sbno = be32_to_cpu(start->s);

	स_रखो(&args, 0, माप(args));
	args.tp = cur->bc_tp;
	args.mp = cur->bc_mp;
	args.oinfo = XFS_RMAP_OINFO_INOBT;
	args.fsbno = XFS_AGB_TO_FSB(args.mp, cur->bc_ag.agno, sbno);
	args.minlen = 1;
	args.maxlen = 1;
	args.prod = 1;
	args.type = XFS_ALLOCTYPE_NEAR_BNO;
	args.resv = resv;

	error = xfs_alloc_vextent(&args);
	अगर (error)
		वापस error;

	अगर (args.fsbno == शून्यFSBLOCK) अणु
		*stat = 0;
		वापस 0;
	पूर्ण
	ASSERT(args.len == 1);

	new->s = cpu_to_be32(XFS_FSB_TO_AGBNO(args.mp, args.fsbno));
	*stat = 1;
	xfs_inobt_mod_blockcount(cur, 1);
	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_inobt_alloc_block(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*start,
	जोड़ xfs_btree_ptr	*new,
	पूर्णांक			*stat)
अणु
	वापस __xfs_inobt_alloc_block(cur, start, new, stat, XFS_AG_RESV_NONE);
पूर्ण

STATIC पूर्णांक
xfs_finobt_alloc_block(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*start,
	जोड़ xfs_btree_ptr	*new,
	पूर्णांक			*stat)
अणु
	अगर (cur->bc_mp->m_finobt_nores)
		वापस xfs_inobt_alloc_block(cur, start, new, stat);
	वापस __xfs_inobt_alloc_block(cur, start, new, stat,
			XFS_AG_RESV_METADATA);
पूर्ण

STATIC पूर्णांक
__xfs_inobt_मुक्त_block(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_buf		*bp,
	क्रमागत xfs_ag_resv_type	resv)
अणु
	xfs_inobt_mod_blockcount(cur, -1);
	वापस xfs_मुक्त_extent(cur->bc_tp,
			XFS_DADDR_TO_FSB(cur->bc_mp, XFS_BUF_ADDR(bp)), 1,
			&XFS_RMAP_OINFO_INOBT, resv);
पूर्ण

STATIC पूर्णांक
xfs_inobt_मुक्त_block(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_buf		*bp)
अणु
	वापस __xfs_inobt_मुक्त_block(cur, bp, XFS_AG_RESV_NONE);
पूर्ण

STATIC पूर्णांक
xfs_finobt_मुक्त_block(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_buf		*bp)
अणु
	अगर (cur->bc_mp->m_finobt_nores)
		वापस xfs_inobt_मुक्त_block(cur, bp);
	वापस __xfs_inobt_मुक्त_block(cur, bp, XFS_AG_RESV_METADATA);
पूर्ण

STATIC पूर्णांक
xfs_inobt_get_maxrecs(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level)
अणु
	वापस M_IGEO(cur->bc_mp)->inobt_mxr[level != 0];
पूर्ण

STATIC व्योम
xfs_inobt_init_key_from_rec(
	जोड़ xfs_btree_key	*key,
	जोड़ xfs_btree_rec	*rec)
अणु
	key->inobt.ir_startino = rec->inobt.ir_startino;
पूर्ण

STATIC व्योम
xfs_inobt_init_high_key_from_rec(
	जोड़ xfs_btree_key	*key,
	जोड़ xfs_btree_rec	*rec)
अणु
	__u32			x;

	x = be32_to_cpu(rec->inobt.ir_startino);
	x += XFS_INODES_PER_CHUNK - 1;
	key->inobt.ir_startino = cpu_to_be32(x);
पूर्ण

STATIC व्योम
xfs_inobt_init_rec_from_cur(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_rec	*rec)
अणु
	rec->inobt.ir_startino = cpu_to_be32(cur->bc_rec.i.ir_startino);
	अगर (xfs_sb_version_hassparseinodes(&cur->bc_mp->m_sb)) अणु
		rec->inobt.ir_u.sp.ir_holemask =
					cpu_to_be16(cur->bc_rec.i.ir_holemask);
		rec->inobt.ir_u.sp.ir_count = cur->bc_rec.i.ir_count;
		rec->inobt.ir_u.sp.ir_मुक्तcount = cur->bc_rec.i.ir_मुक्तcount;
	पूर्ण अन्यथा अणु
		/* ir_holemask/ir_count not supported on-disk */
		rec->inobt.ir_u.f.ir_मुक्तcount =
					cpu_to_be32(cur->bc_rec.i.ir_मुक्तcount);
	पूर्ण
	rec->inobt.ir_मुक्त = cpu_to_be64(cur->bc_rec.i.ir_मुक्त);
पूर्ण

/*
 * initial value of ptr क्रम lookup
 */
STATIC व्योम
xfs_inobt_init_ptr_from_cur(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*ptr)
अणु
	काष्ठा xfs_agi		*agi = cur->bc_ag.agbp->b_addr;

	ASSERT(cur->bc_ag.agno == be32_to_cpu(agi->agi_seqno));

	ptr->s = agi->agi_root;
पूर्ण

STATIC व्योम
xfs_finobt_init_ptr_from_cur(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*ptr)
अणु
	काष्ठा xfs_agi		*agi = cur->bc_ag.agbp->b_addr;

	ASSERT(cur->bc_ag.agno == be32_to_cpu(agi->agi_seqno));
	ptr->s = agi->agi_मुक्त_root;
पूर्ण

STATIC पूर्णांक64_t
xfs_inobt_key_dअगरf(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*key)
अणु
	वापस (पूर्णांक64_t)be32_to_cpu(key->inobt.ir_startino) -
			  cur->bc_rec.i.ir_startino;
पूर्ण

STATIC पूर्णांक64_t
xfs_inobt_dअगरf_two_keys(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*k1,
	जोड़ xfs_btree_key	*k2)
अणु
	वापस (पूर्णांक64_t)be32_to_cpu(k1->inobt.ir_startino) -
			  be32_to_cpu(k2->inobt.ir_startino);
पूर्ण

अटल xfs_failaddr_t
xfs_inobt_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_btree_block	*block = XFS_BUF_TO_BLOCK(bp);
	xfs_failaddr_t		fa;
	अचिन्हित पूर्णांक		level;

	अगर (!xfs_verअगरy_magic(bp, block->bb_magic))
		वापस __this_address;

	/*
	 * During growfs operations, we can't verअगरy the exact owner as the
	 * perag is not fully initialised and hence not attached to the buffer.
	 *
	 * Similarly, during log recovery we will have a perag काष्ठाure
	 * attached, but the agi inक्रमmation will not yet have been initialised
	 * from the on disk AGI. We करोn't currently use any of this inक्रमmation,
	 * but beware of the landmine (i.e. need to check pag->pagi_init) अगर we
	 * ever करो.
	 */
	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		fa = xfs_btree_sblock_v5hdr_verअगरy(bp);
		अगर (fa)
			वापस fa;
	पूर्ण

	/* level verअगरication */
	level = be16_to_cpu(block->bb_level);
	अगर (level >= M_IGEO(mp)->inobt_maxlevels)
		वापस __this_address;

	वापस xfs_btree_sblock_verअगरy(bp,
			M_IGEO(mp)->inobt_mxr[level != 0]);
पूर्ण

अटल व्योम
xfs_inobt_पढ़ो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	xfs_failaddr_t	fa;

	अगर (!xfs_btree_sblock_verअगरy_crc(bp))
		xfs_verअगरier_error(bp, -EFSBADCRC, __this_address);
	अन्यथा अणु
		fa = xfs_inobt_verअगरy(bp);
		अगर (fa)
			xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
	पूर्ण

	अगर (bp->b_error)
		trace_xfs_btree_corrupt(bp, _RET_IP_);
पूर्ण

अटल व्योम
xfs_inobt_ग_लिखो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	xfs_failaddr_t	fa;

	fa = xfs_inobt_verअगरy(bp);
	अगर (fa) अणु
		trace_xfs_btree_corrupt(bp, _RET_IP_);
		xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
		वापस;
	पूर्ण
	xfs_btree_sblock_calc_crc(bp);

पूर्ण

स्थिर काष्ठा xfs_buf_ops xfs_inobt_buf_ops = अणु
	.name = "xfs_inobt",
	.magic = अणु cpu_to_be32(XFS_IBT_MAGIC), cpu_to_be32(XFS_IBT_CRC_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_inobt_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_inobt_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा = xfs_inobt_verअगरy,
पूर्ण;

स्थिर काष्ठा xfs_buf_ops xfs_finobt_buf_ops = अणु
	.name = "xfs_finobt",
	.magic = अणु cpu_to_be32(XFS_FIBT_MAGIC),
		   cpu_to_be32(XFS_FIBT_CRC_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_inobt_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_inobt_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा = xfs_inobt_verअगरy,
पूर्ण;

STATIC पूर्णांक
xfs_inobt_keys_inorder(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*k1,
	जोड़ xfs_btree_key	*k2)
अणु
	वापस be32_to_cpu(k1->inobt.ir_startino) <
		be32_to_cpu(k2->inobt.ir_startino);
पूर्ण

STATIC पूर्णांक
xfs_inobt_recs_inorder(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_rec	*r1,
	जोड़ xfs_btree_rec	*r2)
अणु
	वापस be32_to_cpu(r1->inobt.ir_startino) + XFS_INODES_PER_CHUNK <=
		be32_to_cpu(r2->inobt.ir_startino);
पूर्ण

अटल स्थिर काष्ठा xfs_btree_ops xfs_inobt_ops = अणु
	.rec_len		= माप(xfs_inobt_rec_t),
	.key_len		= माप(xfs_inobt_key_t),

	.dup_cursor		= xfs_inobt_dup_cursor,
	.set_root		= xfs_inobt_set_root,
	.alloc_block		= xfs_inobt_alloc_block,
	.मुक्त_block		= xfs_inobt_मुक्त_block,
	.get_minrecs		= xfs_inobt_get_minrecs,
	.get_maxrecs		= xfs_inobt_get_maxrecs,
	.init_key_from_rec	= xfs_inobt_init_key_from_rec,
	.init_high_key_from_rec	= xfs_inobt_init_high_key_from_rec,
	.init_rec_from_cur	= xfs_inobt_init_rec_from_cur,
	.init_ptr_from_cur	= xfs_inobt_init_ptr_from_cur,
	.key_dअगरf		= xfs_inobt_key_dअगरf,
	.buf_ops		= &xfs_inobt_buf_ops,
	.dअगरf_two_keys		= xfs_inobt_dअगरf_two_keys,
	.keys_inorder		= xfs_inobt_keys_inorder,
	.recs_inorder		= xfs_inobt_recs_inorder,
पूर्ण;

अटल स्थिर काष्ठा xfs_btree_ops xfs_finobt_ops = अणु
	.rec_len		= माप(xfs_inobt_rec_t),
	.key_len		= माप(xfs_inobt_key_t),

	.dup_cursor		= xfs_inobt_dup_cursor,
	.set_root		= xfs_finobt_set_root,
	.alloc_block		= xfs_finobt_alloc_block,
	.मुक्त_block		= xfs_finobt_मुक्त_block,
	.get_minrecs		= xfs_inobt_get_minrecs,
	.get_maxrecs		= xfs_inobt_get_maxrecs,
	.init_key_from_rec	= xfs_inobt_init_key_from_rec,
	.init_high_key_from_rec	= xfs_inobt_init_high_key_from_rec,
	.init_rec_from_cur	= xfs_inobt_init_rec_from_cur,
	.init_ptr_from_cur	= xfs_finobt_init_ptr_from_cur,
	.key_dअगरf		= xfs_inobt_key_dअगरf,
	.buf_ops		= &xfs_finobt_buf_ops,
	.dअगरf_two_keys		= xfs_inobt_dअगरf_two_keys,
	.keys_inorder		= xfs_inobt_keys_inorder,
	.recs_inorder		= xfs_inobt_recs_inorder,
पूर्ण;

/*
 * Initialize a new inode btree cursor.
 */
अटल काष्ठा xfs_btree_cur *
xfs_inobt_init_common(
	काष्ठा xfs_mount	*mp,		/* file प्रणाली mount poपूर्णांक */
	काष्ठा xfs_trans	*tp,		/* transaction poपूर्णांकer */
	xfs_agnumber_t		agno,		/* allocation group number */
	xfs_btnum_t		btnum)		/* ialloc or मुक्त ino btree */
अणु
	काष्ठा xfs_btree_cur	*cur;

	cur = kmem_cache_zalloc(xfs_btree_cur_zone, GFP_NOFS | __GFP_NOFAIL);
	cur->bc_tp = tp;
	cur->bc_mp = mp;
	cur->bc_btnum = btnum;
	अगर (btnum == XFS_BTNUM_INO) अणु
		cur->bc_stम_से_भf = XFS_STATS_CALC_INDEX(xs_ibt_2);
		cur->bc_ops = &xfs_inobt_ops;
	पूर्ण अन्यथा अणु
		cur->bc_stम_से_भf = XFS_STATS_CALC_INDEX(xs_fibt_2);
		cur->bc_ops = &xfs_finobt_ops;
	पूर्ण

	cur->bc_blocklog = mp->m_sb.sb_blocklog;

	अगर (xfs_sb_version_hascrc(&mp->m_sb))
		cur->bc_flags |= XFS_BTREE_CRC_BLOCKS;

	cur->bc_ag.agno = agno;
	वापस cur;
पूर्ण

/* Create an inode btree cursor. */
काष्ठा xfs_btree_cur *
xfs_inobt_init_cursor(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*agbp,
	xfs_agnumber_t		agno,
	xfs_btnum_t		btnum)
अणु
	काष्ठा xfs_btree_cur	*cur;
	काष्ठा xfs_agi		*agi = agbp->b_addr;

	cur = xfs_inobt_init_common(mp, tp, agno, btnum);
	अगर (btnum == XFS_BTNUM_INO)
		cur->bc_nlevels = be32_to_cpu(agi->agi_level);
	अन्यथा
		cur->bc_nlevels = be32_to_cpu(agi->agi_मुक्त_level);
	cur->bc_ag.agbp = agbp;
	वापस cur;
पूर्ण

/* Create an inode btree cursor with a fake root क्रम staging. */
काष्ठा xfs_btree_cur *
xfs_inobt_stage_cursor(
	काष्ठा xfs_mount	*mp,
	काष्ठा xbtree_afakeroot	*afake,
	xfs_agnumber_t		agno,
	xfs_btnum_t		btnum)
अणु
	काष्ठा xfs_btree_cur	*cur;

	cur = xfs_inobt_init_common(mp, शून्य, agno, btnum);
	xfs_btree_stage_afakeroot(cur, afake);
	वापस cur;
पूर्ण

/*
 * Install a new inobt btree root.  Caller is responsible क्रम invalidating
 * and मुक्तing the old btree blocks.
 */
व्योम
xfs_inobt_commit_staged_btree(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*agbp)
अणु
	काष्ठा xfs_agi		*agi = agbp->b_addr;
	काष्ठा xbtree_afakeroot	*afake = cur->bc_ag.afake;
	पूर्णांक			fields;

	ASSERT(cur->bc_flags & XFS_BTREE_STAGING);

	अगर (cur->bc_btnum == XFS_BTNUM_INO) अणु
		fields = XFS_AGI_ROOT | XFS_AGI_LEVEL;
		agi->agi_root = cpu_to_be32(afake->af_root);
		agi->agi_level = cpu_to_be32(afake->af_levels);
		अगर (xfs_sb_version_hasinobtcounts(&cur->bc_mp->m_sb)) अणु
			agi->agi_iblocks = cpu_to_be32(afake->af_blocks);
			fields |= XFS_AGI_IBLOCKS;
		पूर्ण
		xfs_ialloc_log_agi(tp, agbp, fields);
		xfs_btree_commit_afakeroot(cur, tp, agbp, &xfs_inobt_ops);
	पूर्ण अन्यथा अणु
		fields = XFS_AGI_FREE_ROOT | XFS_AGI_FREE_LEVEL;
		agi->agi_मुक्त_root = cpu_to_be32(afake->af_root);
		agi->agi_मुक्त_level = cpu_to_be32(afake->af_levels);
		अगर (xfs_sb_version_hasinobtcounts(&cur->bc_mp->m_sb)) अणु
			agi->agi_fblocks = cpu_to_be32(afake->af_blocks);
			fields |= XFS_AGI_IBLOCKS;
		पूर्ण
		xfs_ialloc_log_agi(tp, agbp, fields);
		xfs_btree_commit_afakeroot(cur, tp, agbp, &xfs_finobt_ops);
	पूर्ण
पूर्ण

/*
 * Calculate number of records in an inobt btree block.
 */
पूर्णांक
xfs_inobt_maxrecs(
	काष्ठा xfs_mount	*mp,
	पूर्णांक			blocklen,
	पूर्णांक			leaf)
अणु
	blocklen -= XFS_INOBT_BLOCK_LEN(mp);

	अगर (leaf)
		वापस blocklen / माप(xfs_inobt_rec_t);
	वापस blocklen / (माप(xfs_inobt_key_t) + माप(xfs_inobt_ptr_t));
पूर्ण

/*
 * Convert the inode record holemask to an inode allocation biपंचांगap. The inode
 * allocation biपंचांगap is inode granularity and specअगरies whether an inode is
 * physically allocated on disk (not whether the inode is considered allocated
 * or मुक्त by the fs).
 *
 * A bit value of 1 means the inode is allocated, a value of 0 means it is मुक्त.
 */
uपूर्णांक64_t
xfs_inobt_irec_to_allocmask(
	काष्ठा xfs_inobt_rec_incore	*rec)
अणु
	uपूर्णांक64_t			biपंचांगap = 0;
	uपूर्णांक64_t			inodespbit;
	पूर्णांक				nextbit;
	uपूर्णांक				allocbiपंचांगap;

	/*
	 * The holemask has 16-bits क्रम a 64 inode record. Thereक्रमe each
	 * holemask bit represents multiple inodes. Create a mask of bits to set
	 * in the allocmask क्रम each holemask bit.
	 */
	inodespbit = (1 << XFS_INODES_PER_HOLEMASK_BIT) - 1;

	/*
	 * Allocated inodes are represented by 0 bits in holemask. Invert the 0
	 * bits to 1 and convert to a uपूर्णांक so we can use xfs_next_bit(). Mask
	 * anything beyond the 16 holemask bits since this casts to a larger
	 * type.
	 */
	allocbiपंचांगap = ~rec->ir_holemask & ((1 << XFS_INOBT_HOLEMASK_BITS) - 1);

	/*
	 * allocbiपंचांगap is the inverted holemask so every set bit represents
	 * allocated inodes. To expand from 16-bit holemask granularity to
	 * 64-bit (e.g., bit-per-inode), set inodespbit bits in the target
	 * biपंचांगap क्रम every holemask bit.
	 */
	nextbit = xfs_next_bit(&allocbiपंचांगap, 1, 0);
	जबतक (nextbit != -1) अणु
		ASSERT(nextbit < (माप(rec->ir_holemask) * NBBY));

		biपंचांगap |= (inodespbit <<
			   (nextbit * XFS_INODES_PER_HOLEMASK_BIT));

		nextbit = xfs_next_bit(&allocbiपंचांगap, 1, nextbit + 1);
	पूर्ण

	वापस biपंचांगap;
पूर्ण

#अगर defined(DEBUG) || defined(XFS_WARN)
/*
 * Verअगरy that an in-core inode record has a valid inode count.
 */
पूर्णांक
xfs_inobt_rec_check_count(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_inobt_rec_incore	*rec)
अणु
	पूर्णांक				inocount = 0;
	पूर्णांक				nextbit = 0;
	uपूर्णांक64_t			allocbmap;
	पूर्णांक				wordsz;

	wordsz = माप(allocbmap) / माप(अचिन्हित पूर्णांक);
	allocbmap = xfs_inobt_irec_to_allocmask(rec);

	nextbit = xfs_next_bit((uपूर्णांक *) &allocbmap, wordsz, nextbit);
	जबतक (nextbit != -1) अणु
		inocount++;
		nextbit = xfs_next_bit((uपूर्णांक *) &allocbmap, wordsz,
				       nextbit + 1);
	पूर्ण

	अगर (inocount != rec->ir_count)
		वापस -EFSCORRUPTED;

	वापस 0;
पूर्ण
#पूर्ण_अगर	/* DEBUG */

अटल xfs_extlen_t
xfs_inobt_max_size(
	काष्ठा xfs_mount	*mp,
	xfs_agnumber_t		agno)
अणु
	xfs_agblock_t		agblocks = xfs_ag_block_count(mp, agno);

	/* Bail out अगर we're uninitialized, which can happen in mkfs. */
	अगर (M_IGEO(mp)->inobt_mxr[0] == 0)
		वापस 0;

	/*
	 * The log is permanently allocated, so the space it occupies will
	 * never be available क्रम the kinds of things that would require btree
	 * expansion.  We thereक्रमe can pretend the space isn't there.
	 */
	अगर (mp->m_sb.sb_logstart &&
	    XFS_FSB_TO_AGNO(mp, mp->m_sb.sb_logstart) == agno)
		agblocks -= mp->m_sb.sb_logblocks;

	वापस xfs_btree_calc_size(M_IGEO(mp)->inobt_mnr,
				(uपूर्णांक64_t)agblocks * mp->m_sb.sb_inopblock /
					XFS_INODES_PER_CHUNK);
पूर्ण

/* Read AGI and create inobt cursor. */
पूर्णांक
xfs_inobt_cur(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	xfs_btnum_t		which,
	काष्ठा xfs_btree_cur	**curpp,
	काष्ठा xfs_buf		**agi_bpp)
अणु
	काष्ठा xfs_btree_cur	*cur;
	पूर्णांक			error;

	ASSERT(*agi_bpp == शून्य);
	ASSERT(*curpp == शून्य);

	error = xfs_ialloc_पढ़ो_agi(mp, tp, agno, agi_bpp);
	अगर (error)
		वापस error;

	cur = xfs_inobt_init_cursor(mp, tp, *agi_bpp, agno, which);
	*curpp = cur;
	वापस 0;
पूर्ण

अटल पूर्णांक
xfs_inobt_count_blocks(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	xfs_btnum_t		btnum,
	xfs_extlen_t		*tree_blocks)
अणु
	काष्ठा xfs_buf		*agbp = शून्य;
	काष्ठा xfs_btree_cur	*cur = शून्य;
	पूर्णांक			error;

	error = xfs_inobt_cur(mp, tp, agno, btnum, &cur, &agbp);
	अगर (error)
		वापस error;

	error = xfs_btree_count_blocks(cur, tree_blocks);
	xfs_btree_del_cursor(cur, error);
	xfs_trans_brअन्यथा(tp, agbp);

	वापस error;
पूर्ण

/* Read finobt block count from AGI header. */
अटल पूर्णांक
xfs_finobt_पढ़ो_blocks(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	xfs_extlen_t		*tree_blocks)
अणु
	काष्ठा xfs_buf		*agbp;
	काष्ठा xfs_agi		*agi;
	पूर्णांक			error;

	error = xfs_ialloc_पढ़ो_agi(mp, tp, agno, &agbp);
	अगर (error)
		वापस error;

	agi = agbp->b_addr;
	*tree_blocks = be32_to_cpu(agi->agi_fblocks);
	xfs_trans_brअन्यथा(tp, agbp);
	वापस 0;
पूर्ण

/*
 * Figure out how many blocks to reserve and how many are used by this btree.
 */
पूर्णांक
xfs_finobt_calc_reserves(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	xfs_extlen_t		*ask,
	xfs_extlen_t		*used)
अणु
	xfs_extlen_t		tree_len = 0;
	पूर्णांक			error;

	अगर (!xfs_sb_version_hasfinobt(&mp->m_sb))
		वापस 0;

	अगर (xfs_sb_version_hasinobtcounts(&mp->m_sb))
		error = xfs_finobt_पढ़ो_blocks(mp, tp, agno, &tree_len);
	अन्यथा
		error = xfs_inobt_count_blocks(mp, tp, agno, XFS_BTNUM_FINO,
				&tree_len);
	अगर (error)
		वापस error;

	*ask += xfs_inobt_max_size(mp, agno);
	*used += tree_len;
	वापस 0;
पूर्ण

/* Calculate the inobt btree size क्रम some records. */
xfs_extlen_t
xfs_iallocbt_calc_size(
	काष्ठा xfs_mount	*mp,
	अचिन्हित दीर्घ दीर्घ	len)
अणु
	वापस xfs_btree_calc_size(M_IGEO(mp)->inobt_mnr, len);
पूर्ण
