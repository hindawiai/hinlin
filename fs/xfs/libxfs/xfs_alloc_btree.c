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
#समावेश "xfs_sb.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_btree_staging.h"
#समावेश "xfs_alloc_btree.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_extent_busy.h"
#समावेश "xfs_error.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_trans.h"


STATIC काष्ठा xfs_btree_cur *
xfs_allocbt_dup_cursor(
	काष्ठा xfs_btree_cur	*cur)
अणु
	वापस xfs_allocbt_init_cursor(cur->bc_mp, cur->bc_tp,
			cur->bc_ag.agbp, cur->bc_ag.agno,
			cur->bc_btnum);
पूर्ण

STATIC व्योम
xfs_allocbt_set_root(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*ptr,
	पूर्णांक			inc)
अणु
	काष्ठा xfs_buf		*agbp = cur->bc_ag.agbp;
	काष्ठा xfs_agf		*agf = agbp->b_addr;
	पूर्णांक			btnum = cur->bc_btnum;
	काष्ठा xfs_perag	*pag = agbp->b_pag;

	ASSERT(ptr->s != 0);

	agf->agf_roots[btnum] = ptr->s;
	be32_add_cpu(&agf->agf_levels[btnum], inc);
	pag->pagf_levels[btnum] += inc;

	xfs_alloc_log_agf(cur->bc_tp, agbp, XFS_AGF_ROOTS | XFS_AGF_LEVELS);
पूर्ण

STATIC पूर्णांक
xfs_allocbt_alloc_block(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*start,
	जोड़ xfs_btree_ptr	*new,
	पूर्णांक			*stat)
अणु
	पूर्णांक			error;
	xfs_agblock_t		bno;

	/* Allocate the new block from the मुक्तlist. If we can't, give up.  */
	error = xfs_alloc_get_मुक्तlist(cur->bc_tp, cur->bc_ag.agbp,
				       &bno, 1);
	अगर (error)
		वापस error;

	अगर (bno == शून्यAGBLOCK) अणु
		*stat = 0;
		वापस 0;
	पूर्ण

	atomic64_inc(&cur->bc_mp->m_allocbt_blks);
	xfs_extent_busy_reuse(cur->bc_mp, cur->bc_ag.agno, bno, 1, false);

	new->s = cpu_to_be32(bno);

	*stat = 1;
	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_allocbt_मुक्त_block(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_buf		*agbp = cur->bc_ag.agbp;
	काष्ठा xfs_agf		*agf = agbp->b_addr;
	xfs_agblock_t		bno;
	पूर्णांक			error;

	bno = xfs_daddr_to_agbno(cur->bc_mp, XFS_BUF_ADDR(bp));
	error = xfs_alloc_put_मुक्तlist(cur->bc_tp, agbp, शून्य, bno, 1);
	अगर (error)
		वापस error;

	atomic64_dec(&cur->bc_mp->m_allocbt_blks);
	xfs_extent_busy_insert(cur->bc_tp, be32_to_cpu(agf->agf_seqno), bno, 1,
			      XFS_EXTENT_BUSY_SKIP_DISCARD);
	वापस 0;
पूर्ण

/*
 * Update the दीर्घest extent in the AGF
 */
STATIC व्योम
xfs_allocbt_update_lastrec(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_btree_block	*block,
	जोड़ xfs_btree_rec	*rec,
	पूर्णांक			ptr,
	पूर्णांक			reason)
अणु
	काष्ठा xfs_agf		*agf = cur->bc_ag.agbp->b_addr;
	काष्ठा xfs_perag	*pag;
	__be32			len;
	पूर्णांक			numrecs;

	ASSERT(cur->bc_btnum == XFS_BTNUM_CNT);

	चयन (reason) अणु
	हाल LASTREC_UPDATE:
		/*
		 * If this is the last leaf block and it's the last record,
		 * then update the size of the दीर्घest extent in the AG.
		 */
		अगर (ptr != xfs_btree_get_numrecs(block))
			वापस;
		len = rec->alloc.ar_blockcount;
		अवरोध;
	हाल LASTREC_INSREC:
		अगर (be32_to_cpu(rec->alloc.ar_blockcount) <=
		    be32_to_cpu(agf->agf_दीर्घest))
			वापस;
		len = rec->alloc.ar_blockcount;
		अवरोध;
	हाल LASTREC_DELREC:
		numrecs = xfs_btree_get_numrecs(block);
		अगर (ptr <= numrecs)
			वापस;
		ASSERT(ptr == numrecs + 1);

		अगर (numrecs) अणु
			xfs_alloc_rec_t *rrp;

			rrp = XFS_ALLOC_REC_ADDR(cur->bc_mp, block, numrecs);
			len = rrp->ar_blockcount;
		पूर्ण अन्यथा अणु
			len = 0;
		पूर्ण

		अवरोध;
	शेष:
		ASSERT(0);
		वापस;
	पूर्ण

	agf->agf_दीर्घest = len;
	pag = cur->bc_ag.agbp->b_pag;
	pag->pagf_दीर्घest = be32_to_cpu(len);
	xfs_alloc_log_agf(cur->bc_tp, cur->bc_ag.agbp, XFS_AGF_LONGEST);
पूर्ण

STATIC पूर्णांक
xfs_allocbt_get_minrecs(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level)
अणु
	वापस cur->bc_mp->m_alloc_mnr[level != 0];
पूर्ण

STATIC पूर्णांक
xfs_allocbt_get_maxrecs(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level)
अणु
	वापस cur->bc_mp->m_alloc_mxr[level != 0];
पूर्ण

STATIC व्योम
xfs_allocbt_init_key_from_rec(
	जोड़ xfs_btree_key	*key,
	जोड़ xfs_btree_rec	*rec)
अणु
	key->alloc.ar_startblock = rec->alloc.ar_startblock;
	key->alloc.ar_blockcount = rec->alloc.ar_blockcount;
पूर्ण

STATIC व्योम
xfs_bnobt_init_high_key_from_rec(
	जोड़ xfs_btree_key	*key,
	जोड़ xfs_btree_rec	*rec)
अणु
	__u32			x;

	x = be32_to_cpu(rec->alloc.ar_startblock);
	x += be32_to_cpu(rec->alloc.ar_blockcount) - 1;
	key->alloc.ar_startblock = cpu_to_be32(x);
	key->alloc.ar_blockcount = 0;
पूर्ण

STATIC व्योम
xfs_cntbt_init_high_key_from_rec(
	जोड़ xfs_btree_key	*key,
	जोड़ xfs_btree_rec	*rec)
अणु
	key->alloc.ar_blockcount = rec->alloc.ar_blockcount;
	key->alloc.ar_startblock = 0;
पूर्ण

STATIC व्योम
xfs_allocbt_init_rec_from_cur(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_rec	*rec)
अणु
	rec->alloc.ar_startblock = cpu_to_be32(cur->bc_rec.a.ar_startblock);
	rec->alloc.ar_blockcount = cpu_to_be32(cur->bc_rec.a.ar_blockcount);
पूर्ण

STATIC व्योम
xfs_allocbt_init_ptr_from_cur(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*ptr)
अणु
	काष्ठा xfs_agf		*agf = cur->bc_ag.agbp->b_addr;

	ASSERT(cur->bc_ag.agno == be32_to_cpu(agf->agf_seqno));

	ptr->s = agf->agf_roots[cur->bc_btnum];
पूर्ण

STATIC पूर्णांक64_t
xfs_bnobt_key_dअगरf(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*key)
अणु
	xfs_alloc_rec_incore_t	*rec = &cur->bc_rec.a;
	xfs_alloc_key_t		*kp = &key->alloc;

	वापस (पूर्णांक64_t)be32_to_cpu(kp->ar_startblock) - rec->ar_startblock;
पूर्ण

STATIC पूर्णांक64_t
xfs_cntbt_key_dअगरf(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*key)
अणु
	xfs_alloc_rec_incore_t	*rec = &cur->bc_rec.a;
	xfs_alloc_key_t		*kp = &key->alloc;
	पूर्णांक64_t			dअगरf;

	dअगरf = (पूर्णांक64_t)be32_to_cpu(kp->ar_blockcount) - rec->ar_blockcount;
	अगर (dअगरf)
		वापस dअगरf;

	वापस (पूर्णांक64_t)be32_to_cpu(kp->ar_startblock) - rec->ar_startblock;
पूर्ण

STATIC पूर्णांक64_t
xfs_bnobt_dअगरf_two_keys(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*k1,
	जोड़ xfs_btree_key	*k2)
अणु
	वापस (पूर्णांक64_t)be32_to_cpu(k1->alloc.ar_startblock) -
			  be32_to_cpu(k2->alloc.ar_startblock);
पूर्ण

STATIC पूर्णांक64_t
xfs_cntbt_dअगरf_two_keys(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*k1,
	जोड़ xfs_btree_key	*k2)
अणु
	पूर्णांक64_t			dअगरf;

	dअगरf =  be32_to_cpu(k1->alloc.ar_blockcount) -
		be32_to_cpu(k2->alloc.ar_blockcount);
	अगर (dअगरf)
		वापस dअगरf;

	वापस  be32_to_cpu(k1->alloc.ar_startblock) -
		be32_to_cpu(k2->alloc.ar_startblock);
पूर्ण

अटल xfs_failaddr_t
xfs_allocbt_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_btree_block	*block = XFS_BUF_TO_BLOCK(bp);
	काष्ठा xfs_perag	*pag = bp->b_pag;
	xfs_failaddr_t		fa;
	अचिन्हित पूर्णांक		level;
	xfs_btnum_t		btnum = XFS_BTNUM_BNOi;

	अगर (!xfs_verअगरy_magic(bp, block->bb_magic))
		वापस __this_address;

	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		fa = xfs_btree_sblock_v5hdr_verअगरy(bp);
		अगर (fa)
			वापस fa;
	पूर्ण

	/*
	 * The perag may not be attached during grow operations or fully
	 * initialized from the AGF during log recovery. Thereक्रमe we can only
	 * check against maximum tree depth from those contexts.
	 *
	 * Otherwise check against the per-tree limit. Peek at one of the
	 * verअगरier magic values to determine the type of tree we're verअगरying
	 * against.
	 */
	level = be16_to_cpu(block->bb_level);
	अगर (bp->b_ops->magic[0] == cpu_to_be32(XFS_ABTC_MAGIC))
		btnum = XFS_BTNUM_CNTi;
	अगर (pag && pag->pagf_init) अणु
		अगर (level >= pag->pagf_levels[btnum])
			वापस __this_address;
	पूर्ण अन्यथा अगर (level >= mp->m_ag_maxlevels)
		वापस __this_address;

	वापस xfs_btree_sblock_verअगरy(bp, mp->m_alloc_mxr[level != 0]);
पूर्ण

अटल व्योम
xfs_allocbt_पढ़ो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	xfs_failaddr_t	fa;

	अगर (!xfs_btree_sblock_verअगरy_crc(bp))
		xfs_verअगरier_error(bp, -EFSBADCRC, __this_address);
	अन्यथा अणु
		fa = xfs_allocbt_verअगरy(bp);
		अगर (fa)
			xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
	पूर्ण

	अगर (bp->b_error)
		trace_xfs_btree_corrupt(bp, _RET_IP_);
पूर्ण

अटल व्योम
xfs_allocbt_ग_लिखो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	xfs_failaddr_t	fa;

	fa = xfs_allocbt_verअगरy(bp);
	अगर (fa) अणु
		trace_xfs_btree_corrupt(bp, _RET_IP_);
		xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
		वापस;
	पूर्ण
	xfs_btree_sblock_calc_crc(bp);

पूर्ण

स्थिर काष्ठा xfs_buf_ops xfs_bnobt_buf_ops = अणु
	.name = "xfs_bnobt",
	.magic = अणु cpu_to_be32(XFS_ABTB_MAGIC),
		   cpu_to_be32(XFS_ABTB_CRC_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_allocbt_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_allocbt_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा = xfs_allocbt_verअगरy,
पूर्ण;

स्थिर काष्ठा xfs_buf_ops xfs_cntbt_buf_ops = अणु
	.name = "xfs_cntbt",
	.magic = अणु cpu_to_be32(XFS_ABTC_MAGIC),
		   cpu_to_be32(XFS_ABTC_CRC_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_allocbt_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_allocbt_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा = xfs_allocbt_verअगरy,
पूर्ण;

STATIC पूर्णांक
xfs_bnobt_keys_inorder(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*k1,
	जोड़ xfs_btree_key	*k2)
अणु
	वापस be32_to_cpu(k1->alloc.ar_startblock) <
	       be32_to_cpu(k2->alloc.ar_startblock);
पूर्ण

STATIC पूर्णांक
xfs_bnobt_recs_inorder(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_rec	*r1,
	जोड़ xfs_btree_rec	*r2)
अणु
	वापस be32_to_cpu(r1->alloc.ar_startblock) +
		be32_to_cpu(r1->alloc.ar_blockcount) <=
		be32_to_cpu(r2->alloc.ar_startblock);
पूर्ण

STATIC पूर्णांक
xfs_cntbt_keys_inorder(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*k1,
	जोड़ xfs_btree_key	*k2)
अणु
	वापस be32_to_cpu(k1->alloc.ar_blockcount) <
		be32_to_cpu(k2->alloc.ar_blockcount) ||
		(k1->alloc.ar_blockcount == k2->alloc.ar_blockcount &&
		 be32_to_cpu(k1->alloc.ar_startblock) <
		 be32_to_cpu(k2->alloc.ar_startblock));
पूर्ण

STATIC पूर्णांक
xfs_cntbt_recs_inorder(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_rec	*r1,
	जोड़ xfs_btree_rec	*r2)
अणु
	वापस be32_to_cpu(r1->alloc.ar_blockcount) <
		be32_to_cpu(r2->alloc.ar_blockcount) ||
		(r1->alloc.ar_blockcount == r2->alloc.ar_blockcount &&
		 be32_to_cpu(r1->alloc.ar_startblock) <
		 be32_to_cpu(r2->alloc.ar_startblock));
पूर्ण

अटल स्थिर काष्ठा xfs_btree_ops xfs_bnobt_ops = अणु
	.rec_len		= माप(xfs_alloc_rec_t),
	.key_len		= माप(xfs_alloc_key_t),

	.dup_cursor		= xfs_allocbt_dup_cursor,
	.set_root		= xfs_allocbt_set_root,
	.alloc_block		= xfs_allocbt_alloc_block,
	.मुक्त_block		= xfs_allocbt_मुक्त_block,
	.update_lastrec		= xfs_allocbt_update_lastrec,
	.get_minrecs		= xfs_allocbt_get_minrecs,
	.get_maxrecs		= xfs_allocbt_get_maxrecs,
	.init_key_from_rec	= xfs_allocbt_init_key_from_rec,
	.init_high_key_from_rec	= xfs_bnobt_init_high_key_from_rec,
	.init_rec_from_cur	= xfs_allocbt_init_rec_from_cur,
	.init_ptr_from_cur	= xfs_allocbt_init_ptr_from_cur,
	.key_dअगरf		= xfs_bnobt_key_dअगरf,
	.buf_ops		= &xfs_bnobt_buf_ops,
	.dअगरf_two_keys		= xfs_bnobt_dअगरf_two_keys,
	.keys_inorder		= xfs_bnobt_keys_inorder,
	.recs_inorder		= xfs_bnobt_recs_inorder,
पूर्ण;

अटल स्थिर काष्ठा xfs_btree_ops xfs_cntbt_ops = अणु
	.rec_len		= माप(xfs_alloc_rec_t),
	.key_len		= माप(xfs_alloc_key_t),

	.dup_cursor		= xfs_allocbt_dup_cursor,
	.set_root		= xfs_allocbt_set_root,
	.alloc_block		= xfs_allocbt_alloc_block,
	.मुक्त_block		= xfs_allocbt_मुक्त_block,
	.update_lastrec		= xfs_allocbt_update_lastrec,
	.get_minrecs		= xfs_allocbt_get_minrecs,
	.get_maxrecs		= xfs_allocbt_get_maxrecs,
	.init_key_from_rec	= xfs_allocbt_init_key_from_rec,
	.init_high_key_from_rec	= xfs_cntbt_init_high_key_from_rec,
	.init_rec_from_cur	= xfs_allocbt_init_rec_from_cur,
	.init_ptr_from_cur	= xfs_allocbt_init_ptr_from_cur,
	.key_dअगरf		= xfs_cntbt_key_dअगरf,
	.buf_ops		= &xfs_cntbt_buf_ops,
	.dअगरf_two_keys		= xfs_cntbt_dअगरf_two_keys,
	.keys_inorder		= xfs_cntbt_keys_inorder,
	.recs_inorder		= xfs_cntbt_recs_inorder,
पूर्ण;

/* Allocate most of a new allocation btree cursor. */
STATIC काष्ठा xfs_btree_cur *
xfs_allocbt_init_common(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	xfs_btnum_t		btnum)
अणु
	काष्ठा xfs_btree_cur	*cur;

	ASSERT(btnum == XFS_BTNUM_BNO || btnum == XFS_BTNUM_CNT);

	cur = kmem_cache_zalloc(xfs_btree_cur_zone, GFP_NOFS | __GFP_NOFAIL);

	cur->bc_tp = tp;
	cur->bc_mp = mp;
	cur->bc_btnum = btnum;
	cur->bc_blocklog = mp->m_sb.sb_blocklog;

	अगर (btnum == XFS_BTNUM_CNT) अणु
		cur->bc_ops = &xfs_cntbt_ops;
		cur->bc_stम_से_भf = XFS_STATS_CALC_INDEX(xs_abtc_2);
		cur->bc_flags = XFS_BTREE_LASTREC_UPDATE;
	पूर्ण अन्यथा अणु
		cur->bc_ops = &xfs_bnobt_ops;
		cur->bc_stम_से_भf = XFS_STATS_CALC_INDEX(xs_abtb_2);
	पूर्ण

	cur->bc_ag.agno = agno;
	cur->bc_ag.abt.active = false;

	अगर (xfs_sb_version_hascrc(&mp->m_sb))
		cur->bc_flags |= XFS_BTREE_CRC_BLOCKS;

	वापस cur;
पूर्ण

/*
 * Allocate a new allocation btree cursor.
 */
काष्ठा xfs_btree_cur *			/* new alloc btree cursor */
xfs_allocbt_init_cursor(
	काष्ठा xfs_mount	*mp,		/* file प्रणाली mount poपूर्णांक */
	काष्ठा xfs_trans	*tp,		/* transaction poपूर्णांकer */
	काष्ठा xfs_buf		*agbp,		/* buffer क्रम agf काष्ठाure */
	xfs_agnumber_t		agno,		/* allocation group number */
	xfs_btnum_t		btnum)		/* btree identअगरier */
अणु
	काष्ठा xfs_agf		*agf = agbp->b_addr;
	काष्ठा xfs_btree_cur	*cur;

	cur = xfs_allocbt_init_common(mp, tp, agno, btnum);
	अगर (btnum == XFS_BTNUM_CNT)
		cur->bc_nlevels = be32_to_cpu(agf->agf_levels[XFS_BTNUM_CNT]);
	अन्यथा
		cur->bc_nlevels = be32_to_cpu(agf->agf_levels[XFS_BTNUM_BNO]);

	cur->bc_ag.agbp = agbp;

	वापस cur;
पूर्ण

/* Create a मुक्त space btree cursor with a fake root क्रम staging. */
काष्ठा xfs_btree_cur *
xfs_allocbt_stage_cursor(
	काष्ठा xfs_mount	*mp,
	काष्ठा xbtree_afakeroot	*afake,
	xfs_agnumber_t		agno,
	xfs_btnum_t		btnum)
अणु
	काष्ठा xfs_btree_cur	*cur;

	cur = xfs_allocbt_init_common(mp, शून्य, agno, btnum);
	xfs_btree_stage_afakeroot(cur, afake);
	वापस cur;
पूर्ण

/*
 * Install a new मुक्त space btree root.  Caller is responsible क्रम invalidating
 * and मुक्तing the old btree blocks.
 */
व्योम
xfs_allocbt_commit_staged_btree(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*agbp)
अणु
	काष्ठा xfs_agf		*agf = agbp->b_addr;
	काष्ठा xbtree_afakeroot	*afake = cur->bc_ag.afake;

	ASSERT(cur->bc_flags & XFS_BTREE_STAGING);

	agf->agf_roots[cur->bc_btnum] = cpu_to_be32(afake->af_root);
	agf->agf_levels[cur->bc_btnum] = cpu_to_be32(afake->af_levels);
	xfs_alloc_log_agf(tp, agbp, XFS_AGF_ROOTS | XFS_AGF_LEVELS);

	अगर (cur->bc_btnum == XFS_BTNUM_BNO) अणु
		xfs_btree_commit_afakeroot(cur, tp, agbp, &xfs_bnobt_ops);
	पूर्ण अन्यथा अणु
		cur->bc_flags |= XFS_BTREE_LASTREC_UPDATE;
		xfs_btree_commit_afakeroot(cur, tp, agbp, &xfs_cntbt_ops);
	पूर्ण
पूर्ण

/*
 * Calculate number of records in an alloc btree block.
 */
पूर्णांक
xfs_allocbt_maxrecs(
	काष्ठा xfs_mount	*mp,
	पूर्णांक			blocklen,
	पूर्णांक			leaf)
अणु
	blocklen -= XFS_ALLOC_BLOCK_LEN(mp);

	अगर (leaf)
		वापस blocklen / माप(xfs_alloc_rec_t);
	वापस blocklen / (माप(xfs_alloc_key_t) + माप(xfs_alloc_ptr_t));
पूर्ण

/* Calculate the मुक्तspace btree size क्रम some records. */
xfs_extlen_t
xfs_allocbt_calc_size(
	काष्ठा xfs_mount	*mp,
	अचिन्हित दीर्घ दीर्घ	len)
अणु
	वापस xfs_btree_calc_size(mp->m_alloc_mnr, len);
पूर्ण
