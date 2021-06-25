<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014 Red Hat, Inc.
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
#समावेश "xfs_trans.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_btree_staging.h"
#समावेश "xfs_rmap.h"
#समावेश "xfs_rmap_btree.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_error.h"
#समावेश "xfs_extent_busy.h"
#समावेश "xfs_ag_resv.h"

/*
 * Reverse map btree.
 *
 * This is a per-ag tree used to track the owner(s) of a given extent. With
 * reflink it is possible क्रम there to be multiple owners, which is a departure
 * from classic XFS. Owner records क्रम data extents are inserted when the
 * extent is mapped and हटाओd when an extent is unmapped.  Owner records क्रम
 * all other block types (i.e. metadata) are inserted when an extent is
 * allocated and हटाओd when an extent is मुक्तd. There can only be one owner
 * of a metadata extent, usually an inode or some other metadata काष्ठाure like
 * an AG btree.
 *
 * The rmap btree is part of the मुक्त space management, so blocks क्रम the tree
 * are sourced from the agfl. Hence we need transaction reservation support क्रम
 * this tree so that the मुक्तlist is always large enough. This also impacts on
 * the minimum space we need to leave मुक्त in the AG.
 *
 * The tree is ordered by [ag block, owner, offset]. This is a large key size,
 * but it is the only way to enक्रमce unique keys when a block can be owned by
 * multiple files at any offset. There's no need to order/search by extent
 * size क्रम online updating/management of the tree. It is पूर्णांकended that most
 * reverse lookups will be to find the owner(s) of a particular block, or to
 * try to recover tree and file data from corrupt primary metadata.
 */

अटल काष्ठा xfs_btree_cur *
xfs_rmapbt_dup_cursor(
	काष्ठा xfs_btree_cur	*cur)
अणु
	वापस xfs_rmapbt_init_cursor(cur->bc_mp, cur->bc_tp,
			cur->bc_ag.agbp, cur->bc_ag.agno);
पूर्ण

STATIC व्योम
xfs_rmapbt_set_root(
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
xfs_rmapbt_alloc_block(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*start,
	जोड़ xfs_btree_ptr	*new,
	पूर्णांक			*stat)
अणु
	काष्ठा xfs_buf		*agbp = cur->bc_ag.agbp;
	काष्ठा xfs_agf		*agf = agbp->b_addr;
	पूर्णांक			error;
	xfs_agblock_t		bno;

	/* Allocate the new block from the मुक्तlist. If we can't, give up.  */
	error = xfs_alloc_get_मुक्तlist(cur->bc_tp, cur->bc_ag.agbp,
				       &bno, 1);
	अगर (error)
		वापस error;

	trace_xfs_rmapbt_alloc_block(cur->bc_mp, cur->bc_ag.agno,
			bno, 1);
	अगर (bno == शून्यAGBLOCK) अणु
		*stat = 0;
		वापस 0;
	पूर्ण

	xfs_extent_busy_reuse(cur->bc_mp, cur->bc_ag.agno, bno, 1,
			false);

	new->s = cpu_to_be32(bno);
	be32_add_cpu(&agf->agf_rmap_blocks, 1);
	xfs_alloc_log_agf(cur->bc_tp, agbp, XFS_AGF_RMAP_BLOCKS);

	xfs_ag_resv_rmapbt_alloc(cur->bc_mp, cur->bc_ag.agno);

	*stat = 1;
	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_rmapbt_मुक्त_block(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_buf		*agbp = cur->bc_ag.agbp;
	काष्ठा xfs_agf		*agf = agbp->b_addr;
	काष्ठा xfs_perag	*pag;
	xfs_agblock_t		bno;
	पूर्णांक			error;

	bno = xfs_daddr_to_agbno(cur->bc_mp, XFS_BUF_ADDR(bp));
	trace_xfs_rmapbt_मुक्त_block(cur->bc_mp, cur->bc_ag.agno,
			bno, 1);
	be32_add_cpu(&agf->agf_rmap_blocks, -1);
	xfs_alloc_log_agf(cur->bc_tp, agbp, XFS_AGF_RMAP_BLOCKS);
	error = xfs_alloc_put_मुक्तlist(cur->bc_tp, agbp, शून्य, bno, 1);
	अगर (error)
		वापस error;

	xfs_extent_busy_insert(cur->bc_tp, be32_to_cpu(agf->agf_seqno), bno, 1,
			      XFS_EXTENT_BUSY_SKIP_DISCARD);

	pag = cur->bc_ag.agbp->b_pag;
	xfs_ag_resv_मुक्त_extent(pag, XFS_AG_RESV_RMAPBT, शून्य, 1);
	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_rmapbt_get_minrecs(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level)
अणु
	वापस cur->bc_mp->m_rmap_mnr[level != 0];
पूर्ण

STATIC पूर्णांक
xfs_rmapbt_get_maxrecs(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level)
अणु
	वापस cur->bc_mp->m_rmap_mxr[level != 0];
पूर्ण

STATIC व्योम
xfs_rmapbt_init_key_from_rec(
	जोड़ xfs_btree_key	*key,
	जोड़ xfs_btree_rec	*rec)
अणु
	key->rmap.rm_startblock = rec->rmap.rm_startblock;
	key->rmap.rm_owner = rec->rmap.rm_owner;
	key->rmap.rm_offset = rec->rmap.rm_offset;
पूर्ण

/*
 * The high key क्रम a reverse mapping record can be computed by shअगरting
 * the startblock and offset to the highest value that would still map
 * to that record.  In practice this means that we add blockcount-1 to
 * the startblock क्रम all records, and अगर the record is क्रम a data/attr
 * विभाजन mapping, we add blockcount-1 to the offset too.
 */
STATIC व्योम
xfs_rmapbt_init_high_key_from_rec(
	जोड़ xfs_btree_key	*key,
	जोड़ xfs_btree_rec	*rec)
अणु
	uपूर्णांक64_t		off;
	पूर्णांक			adj;

	adj = be32_to_cpu(rec->rmap.rm_blockcount) - 1;

	key->rmap.rm_startblock = rec->rmap.rm_startblock;
	be32_add_cpu(&key->rmap.rm_startblock, adj);
	key->rmap.rm_owner = rec->rmap.rm_owner;
	key->rmap.rm_offset = rec->rmap.rm_offset;
	अगर (XFS_RMAP_NON_INODE_OWNER(be64_to_cpu(rec->rmap.rm_owner)) ||
	    XFS_RMAP_IS_BMBT_BLOCK(be64_to_cpu(rec->rmap.rm_offset)))
		वापस;
	off = be64_to_cpu(key->rmap.rm_offset);
	off = (XFS_RMAP_OFF(off) + adj) | (off & ~XFS_RMAP_OFF_MASK);
	key->rmap.rm_offset = cpu_to_be64(off);
पूर्ण

STATIC व्योम
xfs_rmapbt_init_rec_from_cur(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_rec	*rec)
अणु
	rec->rmap.rm_startblock = cpu_to_be32(cur->bc_rec.r.rm_startblock);
	rec->rmap.rm_blockcount = cpu_to_be32(cur->bc_rec.r.rm_blockcount);
	rec->rmap.rm_owner = cpu_to_be64(cur->bc_rec.r.rm_owner);
	rec->rmap.rm_offset = cpu_to_be64(
			xfs_rmap_irec_offset_pack(&cur->bc_rec.r));
पूर्ण

STATIC व्योम
xfs_rmapbt_init_ptr_from_cur(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*ptr)
अणु
	काष्ठा xfs_agf		*agf = cur->bc_ag.agbp->b_addr;

	ASSERT(cur->bc_ag.agno == be32_to_cpu(agf->agf_seqno));

	ptr->s = agf->agf_roots[cur->bc_btnum];
पूर्ण

STATIC पूर्णांक64_t
xfs_rmapbt_key_dअगरf(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*key)
अणु
	काष्ठा xfs_rmap_irec	*rec = &cur->bc_rec.r;
	काष्ठा xfs_rmap_key	*kp = &key->rmap;
	__u64			x, y;
	पूर्णांक64_t			d;

	d = (पूर्णांक64_t)be32_to_cpu(kp->rm_startblock) - rec->rm_startblock;
	अगर (d)
		वापस d;

	x = be64_to_cpu(kp->rm_owner);
	y = rec->rm_owner;
	अगर (x > y)
		वापस 1;
	अन्यथा अगर (y > x)
		वापस -1;

	x = XFS_RMAP_OFF(be64_to_cpu(kp->rm_offset));
	y = rec->rm_offset;
	अगर (x > y)
		वापस 1;
	अन्यथा अगर (y > x)
		वापस -1;
	वापस 0;
पूर्ण

STATIC पूर्णांक64_t
xfs_rmapbt_dअगरf_two_keys(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*k1,
	जोड़ xfs_btree_key	*k2)
अणु
	काष्ठा xfs_rmap_key	*kp1 = &k1->rmap;
	काष्ठा xfs_rmap_key	*kp2 = &k2->rmap;
	पूर्णांक64_t			d;
	__u64			x, y;

	d = (पूर्णांक64_t)be32_to_cpu(kp1->rm_startblock) -
		       be32_to_cpu(kp2->rm_startblock);
	अगर (d)
		वापस d;

	x = be64_to_cpu(kp1->rm_owner);
	y = be64_to_cpu(kp2->rm_owner);
	अगर (x > y)
		वापस 1;
	अन्यथा अगर (y > x)
		वापस -1;

	x = XFS_RMAP_OFF(be64_to_cpu(kp1->rm_offset));
	y = XFS_RMAP_OFF(be64_to_cpu(kp2->rm_offset));
	अगर (x > y)
		वापस 1;
	अन्यथा अगर (y > x)
		वापस -1;
	वापस 0;
पूर्ण

अटल xfs_failaddr_t
xfs_rmapbt_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_btree_block	*block = XFS_BUF_TO_BLOCK(bp);
	काष्ठा xfs_perag	*pag = bp->b_pag;
	xfs_failaddr_t		fa;
	अचिन्हित पूर्णांक		level;

	/*
	 * magic number and level verअगरication
	 *
	 * During growfs operations, we can't verअगरy the exact level or owner as
	 * the perag is not fully initialised and hence not attached to the
	 * buffer.  In this हाल, check against the maximum tree depth.
	 *
	 * Similarly, during log recovery we will have a perag काष्ठाure
	 * attached, but the agf inक्रमmation will not yet have been initialised
	 * from the on disk AGF. Again, we can only check against maximum limits
	 * in this हाल.
	 */
	अगर (!xfs_verअगरy_magic(bp, block->bb_magic))
		वापस __this_address;

	अगर (!xfs_sb_version_hasrmapbt(&mp->m_sb))
		वापस __this_address;
	fa = xfs_btree_sblock_v5hdr_verअगरy(bp);
	अगर (fa)
		वापस fa;

	level = be16_to_cpu(block->bb_level);
	अगर (pag && pag->pagf_init) अणु
		अगर (level >= pag->pagf_levels[XFS_BTNUM_RMAPi])
			वापस __this_address;
	पूर्ण अन्यथा अगर (level >= mp->m_rmap_maxlevels)
		वापस __this_address;

	वापस xfs_btree_sblock_verअगरy(bp, mp->m_rmap_mxr[level != 0]);
पूर्ण

अटल व्योम
xfs_rmapbt_पढ़ो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	xfs_failaddr_t	fa;

	अगर (!xfs_btree_sblock_verअगरy_crc(bp))
		xfs_verअगरier_error(bp, -EFSBADCRC, __this_address);
	अन्यथा अणु
		fa = xfs_rmapbt_verअगरy(bp);
		अगर (fa)
			xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
	पूर्ण

	अगर (bp->b_error)
		trace_xfs_btree_corrupt(bp, _RET_IP_);
पूर्ण

अटल व्योम
xfs_rmapbt_ग_लिखो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	xfs_failaddr_t	fa;

	fa = xfs_rmapbt_verअगरy(bp);
	अगर (fa) अणु
		trace_xfs_btree_corrupt(bp, _RET_IP_);
		xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
		वापस;
	पूर्ण
	xfs_btree_sblock_calc_crc(bp);

पूर्ण

स्थिर काष्ठा xfs_buf_ops xfs_rmapbt_buf_ops = अणु
	.name			= "xfs_rmapbt",
	.magic			= अणु 0, cpu_to_be32(XFS_RMAP_CRC_MAGIC) पूर्ण,
	.verअगरy_पढ़ो		= xfs_rmapbt_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो		= xfs_rmapbt_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा		= xfs_rmapbt_verअगरy,
पूर्ण;

STATIC पूर्णांक
xfs_rmapbt_keys_inorder(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*k1,
	जोड़ xfs_btree_key	*k2)
अणु
	uपूर्णांक32_t		x;
	uपूर्णांक32_t		y;
	uपूर्णांक64_t		a;
	uपूर्णांक64_t		b;

	x = be32_to_cpu(k1->rmap.rm_startblock);
	y = be32_to_cpu(k2->rmap.rm_startblock);
	अगर (x < y)
		वापस 1;
	अन्यथा अगर (x > y)
		वापस 0;
	a = be64_to_cpu(k1->rmap.rm_owner);
	b = be64_to_cpu(k2->rmap.rm_owner);
	अगर (a < b)
		वापस 1;
	अन्यथा अगर (a > b)
		वापस 0;
	a = XFS_RMAP_OFF(be64_to_cpu(k1->rmap.rm_offset));
	b = XFS_RMAP_OFF(be64_to_cpu(k2->rmap.rm_offset));
	अगर (a <= b)
		वापस 1;
	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_rmapbt_recs_inorder(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_rec	*r1,
	जोड़ xfs_btree_rec	*r2)
अणु
	uपूर्णांक32_t		x;
	uपूर्णांक32_t		y;
	uपूर्णांक64_t		a;
	uपूर्णांक64_t		b;

	x = be32_to_cpu(r1->rmap.rm_startblock);
	y = be32_to_cpu(r2->rmap.rm_startblock);
	अगर (x < y)
		वापस 1;
	अन्यथा अगर (x > y)
		वापस 0;
	a = be64_to_cpu(r1->rmap.rm_owner);
	b = be64_to_cpu(r2->rmap.rm_owner);
	अगर (a < b)
		वापस 1;
	अन्यथा अगर (a > b)
		वापस 0;
	a = XFS_RMAP_OFF(be64_to_cpu(r1->rmap.rm_offset));
	b = XFS_RMAP_OFF(be64_to_cpu(r2->rmap.rm_offset));
	अगर (a <= b)
		वापस 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा xfs_btree_ops xfs_rmapbt_ops = अणु
	.rec_len		= माप(काष्ठा xfs_rmap_rec),
	.key_len		= 2 * माप(काष्ठा xfs_rmap_key),

	.dup_cursor		= xfs_rmapbt_dup_cursor,
	.set_root		= xfs_rmapbt_set_root,
	.alloc_block		= xfs_rmapbt_alloc_block,
	.मुक्त_block		= xfs_rmapbt_मुक्त_block,
	.get_minrecs		= xfs_rmapbt_get_minrecs,
	.get_maxrecs		= xfs_rmapbt_get_maxrecs,
	.init_key_from_rec	= xfs_rmapbt_init_key_from_rec,
	.init_high_key_from_rec	= xfs_rmapbt_init_high_key_from_rec,
	.init_rec_from_cur	= xfs_rmapbt_init_rec_from_cur,
	.init_ptr_from_cur	= xfs_rmapbt_init_ptr_from_cur,
	.key_dअगरf		= xfs_rmapbt_key_dअगरf,
	.buf_ops		= &xfs_rmapbt_buf_ops,
	.dअगरf_two_keys		= xfs_rmapbt_dअगरf_two_keys,
	.keys_inorder		= xfs_rmapbt_keys_inorder,
	.recs_inorder		= xfs_rmapbt_recs_inorder,
पूर्ण;

अटल काष्ठा xfs_btree_cur *
xfs_rmapbt_init_common(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno)
अणु
	काष्ठा xfs_btree_cur	*cur;

	cur = kmem_cache_zalloc(xfs_btree_cur_zone, GFP_NOFS | __GFP_NOFAIL);
	cur->bc_tp = tp;
	cur->bc_mp = mp;
	/* Overlapping btree; 2 keys per poपूर्णांकer. */
	cur->bc_btnum = XFS_BTNUM_RMAP;
	cur->bc_flags = XFS_BTREE_CRC_BLOCKS | XFS_BTREE_OVERLAPPING;
	cur->bc_blocklog = mp->m_sb.sb_blocklog;
	cur->bc_stम_से_भf = XFS_STATS_CALC_INDEX(xs_rmap_2);
	cur->bc_ag.agno = agno;
	cur->bc_ops = &xfs_rmapbt_ops;

	वापस cur;
पूर्ण

/* Create a new reverse mapping btree cursor. */
काष्ठा xfs_btree_cur *
xfs_rmapbt_init_cursor(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*agbp,
	xfs_agnumber_t		agno)
अणु
	काष्ठा xfs_agf		*agf = agbp->b_addr;
	काष्ठा xfs_btree_cur	*cur;

	cur = xfs_rmapbt_init_common(mp, tp, agno);
	cur->bc_nlevels = be32_to_cpu(agf->agf_levels[XFS_BTNUM_RMAP]);
	cur->bc_ag.agbp = agbp;
	वापस cur;
पूर्ण

/* Create a new reverse mapping btree cursor with a fake root क्रम staging. */
काष्ठा xfs_btree_cur *
xfs_rmapbt_stage_cursor(
	काष्ठा xfs_mount	*mp,
	काष्ठा xbtree_afakeroot	*afake,
	xfs_agnumber_t		agno)
अणु
	काष्ठा xfs_btree_cur	*cur;

	cur = xfs_rmapbt_init_common(mp, शून्य, agno);
	xfs_btree_stage_afakeroot(cur, afake);
	वापस cur;
पूर्ण

/*
 * Install a new reverse mapping btree root.  Caller is responsible क्रम
 * invalidating and मुक्तing the old btree blocks.
 */
व्योम
xfs_rmapbt_commit_staged_btree(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*agbp)
अणु
	काष्ठा xfs_agf		*agf = agbp->b_addr;
	काष्ठा xbtree_afakeroot	*afake = cur->bc_ag.afake;

	ASSERT(cur->bc_flags & XFS_BTREE_STAGING);

	agf->agf_roots[cur->bc_btnum] = cpu_to_be32(afake->af_root);
	agf->agf_levels[cur->bc_btnum] = cpu_to_be32(afake->af_levels);
	agf->agf_rmap_blocks = cpu_to_be32(afake->af_blocks);
	xfs_alloc_log_agf(tp, agbp, XFS_AGF_ROOTS | XFS_AGF_LEVELS |
				    XFS_AGF_RMAP_BLOCKS);
	xfs_btree_commit_afakeroot(cur, tp, agbp, &xfs_rmapbt_ops);
पूर्ण

/*
 * Calculate number of records in an rmap btree block.
 */
पूर्णांक
xfs_rmapbt_maxrecs(
	पूर्णांक			blocklen,
	पूर्णांक			leaf)
अणु
	blocklen -= XFS_RMAP_BLOCK_LEN;

	अगर (leaf)
		वापस blocklen / माप(काष्ठा xfs_rmap_rec);
	वापस blocklen /
		(2 * माप(काष्ठा xfs_rmap_key) + माप(xfs_rmap_ptr_t));
पूर्ण

/* Compute the maximum height of an rmap btree. */
व्योम
xfs_rmapbt_compute_maxlevels(
	काष्ठा xfs_mount		*mp)
अणु
	/*
	 * On a non-reflink fileप्रणाली, the maximum number of rmap
	 * records is the number of blocks in the AG, hence the max
	 * rmapbt height is log_$maxrecs($agblocks).  However, with
	 * reflink each AG block can have up to 2^32 (per the refcount
	 * record क्रमmat) owners, which means that theoretically we
	 * could face up to 2^64 rmap records.
	 *
	 * That effectively means that the max rmapbt height must be
	 * XFS_BTREE_MAXLEVELS.  "Fortunately" we'll run out of AG
	 * blocks to feed the rmapbt दीर्घ beक्रमe the rmapbt reaches
	 * maximum height.  The reflink code uses ag_resv_critical to
	 * disallow reflinking when less than 10% of the per-AG metadata
	 * block reservation since the fallback is a regular file copy.
	 */
	अगर (xfs_sb_version_hasreflink(&mp->m_sb))
		mp->m_rmap_maxlevels = XFS_BTREE_MAXLEVELS;
	अन्यथा
		mp->m_rmap_maxlevels = xfs_btree_compute_maxlevels(
				mp->m_rmap_mnr, mp->m_sb.sb_agblocks);
पूर्ण

/* Calculate the refcount btree size क्रम some records. */
xfs_extlen_t
xfs_rmapbt_calc_size(
	काष्ठा xfs_mount	*mp,
	अचिन्हित दीर्घ दीर्घ	len)
अणु
	वापस xfs_btree_calc_size(mp->m_rmap_mnr, len);
पूर्ण

/*
 * Calculate the maximum refcount btree size.
 */
xfs_extlen_t
xfs_rmapbt_max_size(
	काष्ठा xfs_mount	*mp,
	xfs_agblock_t		agblocks)
अणु
	/* Bail out अगर we're uninitialized, which can happen in mkfs. */
	अगर (mp->m_rmap_mxr[0] == 0)
		वापस 0;

	वापस xfs_rmapbt_calc_size(mp, agblocks);
पूर्ण

/*
 * Figure out how many blocks to reserve and how many are used by this btree.
 */
पूर्णांक
xfs_rmapbt_calc_reserves(
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

	अगर (!xfs_sb_version_hasrmapbt(&mp->m_sb))
		वापस 0;

	error = xfs_alloc_पढ़ो_agf(mp, tp, agno, 0, &agbp);
	अगर (error)
		वापस error;

	agf = agbp->b_addr;
	agblocks = be32_to_cpu(agf->agf_length);
	tree_len = be32_to_cpu(agf->agf_rmap_blocks);
	xfs_trans_brअन्यथा(tp, agbp);

	/*
	 * The log is permanently allocated, so the space it occupies will
	 * never be available क्रम the kinds of things that would require btree
	 * expansion.  We thereक्रमe can pretend the space isn't there.
	 */
	अगर (mp->m_sb.sb_logstart &&
	    XFS_FSB_TO_AGNO(mp, mp->m_sb.sb_logstart) == agno)
		agblocks -= mp->m_sb.sb_logblocks;

	/* Reserve 1% of the AG or enough क्रम 1 block per record. */
	*ask += max(agblocks / 100, xfs_rmapbt_max_size(mp, agblocks));
	*used += tree_len;

	वापस error;
पूर्ण
