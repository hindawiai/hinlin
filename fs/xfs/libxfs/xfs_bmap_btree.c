<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2003,2005 Silicon Graphics, Inc.
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
#समावेश "xfs_trans.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_bmap_btree.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_error.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_rmap.h"

/*
 * Convert on-disk क्रमm of btree root to in-memory क्रमm.
 */
व्योम
xfs_bmdr_to_bmbt(
	काष्ठा xfs_inode	*ip,
	xfs_bmdr_block_t	*dblock,
	पूर्णांक			dblocklen,
	काष्ठा xfs_btree_block	*rblock,
	पूर्णांक			rblocklen)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	पूर्णांक			dmxr;
	xfs_bmbt_key_t		*fkp;
	__be64			*fpp;
	xfs_bmbt_key_t		*tkp;
	__be64			*tpp;

	xfs_btree_init_block_पूर्णांक(mp, rblock, XFS_BUF_DADDR_शून्य,
				 XFS_BTNUM_BMAP, 0, 0, ip->i_ino,
				 XFS_BTREE_LONG_PTRS);
	rblock->bb_level = dblock->bb_level;
	ASSERT(be16_to_cpu(rblock->bb_level) > 0);
	rblock->bb_numrecs = dblock->bb_numrecs;
	dmxr = xfs_bmdr_maxrecs(dblocklen, 0);
	fkp = XFS_BMDR_KEY_ADDR(dblock, 1);
	tkp = XFS_BMBT_KEY_ADDR(mp, rblock, 1);
	fpp = XFS_BMDR_PTR_ADDR(dblock, 1, dmxr);
	tpp = XFS_BMAP_BROOT_PTR_ADDR(mp, rblock, 1, rblocklen);
	dmxr = be16_to_cpu(dblock->bb_numrecs);
	स_नकल(tkp, fkp, माप(*fkp) * dmxr);
	स_नकल(tpp, fpp, माप(*fpp) * dmxr);
पूर्ण

व्योम
xfs_bmbt_disk_get_all(
	काष्ठा xfs_bmbt_rec	*rec,
	काष्ठा xfs_bmbt_irec	*irec)
अणु
	uपूर्णांक64_t		l0 = get_unaligned_be64(&rec->l0);
	uपूर्णांक64_t		l1 = get_unaligned_be64(&rec->l1);

	irec->br_startoff = (l0 & xfs_mask64lo(64 - BMBT_EXNTFLAG_BITLEN)) >> 9;
	irec->br_startblock = ((l0 & xfs_mask64lo(9)) << 43) | (l1 >> 21);
	irec->br_blockcount = l1 & xfs_mask64lo(21);
	अगर (l0 >> (64 - BMBT_EXNTFLAG_BITLEN))
		irec->br_state = XFS_EXT_UNWRITTEN;
	अन्यथा
		irec->br_state = XFS_EXT_NORM;
पूर्ण

/*
 * Extract the blockcount field from an on disk bmap extent record.
 */
xfs_filblks_t
xfs_bmbt_disk_get_blockcount(
	xfs_bmbt_rec_t	*r)
अणु
	वापस (xfs_filblks_t)(be64_to_cpu(r->l1) & xfs_mask64lo(21));
पूर्ण

/*
 * Extract the startoff field from a disk क्रमmat bmap extent record.
 */
xfs_fileoff_t
xfs_bmbt_disk_get_startoff(
	xfs_bmbt_rec_t	*r)
अणु
	वापस ((xfs_fileoff_t)be64_to_cpu(r->l0) &
		 xfs_mask64lo(64 - BMBT_EXNTFLAG_BITLEN)) >> 9;
पूर्ण

/*
 * Set all the fields in a bmap extent record from the uncompressed क्रमm.
 */
व्योम
xfs_bmbt_disk_set_all(
	काष्ठा xfs_bmbt_rec	*r,
	काष्ठा xfs_bmbt_irec	*s)
अणु
	पूर्णांक			extent_flag = (s->br_state != XFS_EXT_NORM);

	ASSERT(s->br_state == XFS_EXT_NORM || s->br_state == XFS_EXT_UNWRITTEN);
	ASSERT(!(s->br_startoff & xfs_mask64hi(64-BMBT_STARTOFF_BITLEN)));
	ASSERT(!(s->br_blockcount & xfs_mask64hi(64-BMBT_BLOCKCOUNT_BITLEN)));
	ASSERT(!(s->br_startblock & xfs_mask64hi(64-BMBT_STARTBLOCK_BITLEN)));

	put_unaligned_be64(
		((xfs_bmbt_rec_base_t)extent_flag << 63) |
		 ((xfs_bmbt_rec_base_t)s->br_startoff << 9) |
		 ((xfs_bmbt_rec_base_t)s->br_startblock >> 43), &r->l0);
	put_unaligned_be64(
		((xfs_bmbt_rec_base_t)s->br_startblock << 21) |
		 ((xfs_bmbt_rec_base_t)s->br_blockcount &
		  (xfs_bmbt_rec_base_t)xfs_mask64lo(21)), &r->l1);
पूर्ण

/*
 * Convert in-memory क्रमm of btree root to on-disk क्रमm.
 */
व्योम
xfs_bmbt_to_bmdr(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_btree_block	*rblock,
	पूर्णांक			rblocklen,
	xfs_bmdr_block_t	*dblock,
	पूर्णांक			dblocklen)
अणु
	पूर्णांक			dmxr;
	xfs_bmbt_key_t		*fkp;
	__be64			*fpp;
	xfs_bmbt_key_t		*tkp;
	__be64			*tpp;

	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		ASSERT(rblock->bb_magic == cpu_to_be32(XFS_BMAP_CRC_MAGIC));
		ASSERT(uuid_equal(&rblock->bb_u.l.bb_uuid,
		       &mp->m_sb.sb_meta_uuid));
		ASSERT(rblock->bb_u.l.bb_blkno ==
		       cpu_to_be64(XFS_BUF_DADDR_शून्य));
	पूर्ण अन्यथा
		ASSERT(rblock->bb_magic == cpu_to_be32(XFS_BMAP_MAGIC));
	ASSERT(rblock->bb_u.l.bb_leftsib == cpu_to_be64(शून्यFSBLOCK));
	ASSERT(rblock->bb_u.l.bb_rightsib == cpu_to_be64(शून्यFSBLOCK));
	ASSERT(rblock->bb_level != 0);
	dblock->bb_level = rblock->bb_level;
	dblock->bb_numrecs = rblock->bb_numrecs;
	dmxr = xfs_bmdr_maxrecs(dblocklen, 0);
	fkp = XFS_BMBT_KEY_ADDR(mp, rblock, 1);
	tkp = XFS_BMDR_KEY_ADDR(dblock, 1);
	fpp = XFS_BMAP_BROOT_PTR_ADDR(mp, rblock, 1, rblocklen);
	tpp = XFS_BMDR_PTR_ADDR(dblock, 1, dmxr);
	dmxr = be16_to_cpu(dblock->bb_numrecs);
	स_नकल(tkp, fkp, माप(*fkp) * dmxr);
	स_नकल(tpp, fpp, माप(*fpp) * dmxr);
पूर्ण

STATIC काष्ठा xfs_btree_cur *
xfs_bmbt_dup_cursor(
	काष्ठा xfs_btree_cur	*cur)
अणु
	काष्ठा xfs_btree_cur	*new;

	new = xfs_bmbt_init_cursor(cur->bc_mp, cur->bc_tp,
			cur->bc_ino.ip, cur->bc_ino.whichविभाजन);

	/*
	 * Copy the firstblock, dfops, and flags values,
	 * since init cursor करोesn't get them.
	 */
	new->bc_ino.flags = cur->bc_ino.flags;

	वापस new;
पूर्ण

STATIC व्योम
xfs_bmbt_update_cursor(
	काष्ठा xfs_btree_cur	*src,
	काष्ठा xfs_btree_cur	*dst)
अणु
	ASSERT((dst->bc_tp->t_firstblock != शून्यFSBLOCK) ||
	       (dst->bc_ino.ip->i_dअगरlags & XFS_DIFLAG_REALTIME));

	dst->bc_ino.allocated += src->bc_ino.allocated;
	dst->bc_tp->t_firstblock = src->bc_tp->t_firstblock;

	src->bc_ino.allocated = 0;
पूर्ण

STATIC पूर्णांक
xfs_bmbt_alloc_block(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*start,
	जोड़ xfs_btree_ptr	*new,
	पूर्णांक			*stat)
अणु
	xfs_alloc_arg_t		args;		/* block allocation args */
	पूर्णांक			error;		/* error वापस value */

	स_रखो(&args, 0, माप(args));
	args.tp = cur->bc_tp;
	args.mp = cur->bc_mp;
	args.fsbno = cur->bc_tp->t_firstblock;
	xfs_rmap_ino_bmbt_owner(&args.oinfo, cur->bc_ino.ip->i_ino,
			cur->bc_ino.whichविभाजन);

	अगर (args.fsbno == शून्यFSBLOCK) अणु
		args.fsbno = be64_to_cpu(start->l);
		args.type = XFS_ALLOCTYPE_START_BNO;
		/*
		 * Make sure there is sufficient room left in the AG to
		 * complete a full tree split क्रम an extent insert.  If
		 * we are converting the middle part of an extent then
		 * we may need space क्रम two tree splits.
		 *
		 * We are relying on the caller to make the correct block
		 * reservation क्रम this operation to succeed.  If the
		 * reservation amount is insufficient then we may fail a
		 * block allocation here and corrupt the fileप्रणाली.
		 */
		args.minleft = args.tp->t_blk_res;
	पूर्ण अन्यथा अगर (cur->bc_tp->t_flags & XFS_TRANS_LOWMODE) अणु
		args.type = XFS_ALLOCTYPE_START_BNO;
	पूर्ण अन्यथा अणु
		args.type = XFS_ALLOCTYPE_NEAR_BNO;
	पूर्ण

	args.minlen = args.maxlen = args.prod = 1;
	args.wasdel = cur->bc_ino.flags & XFS_BTCUR_BMBT_WASDEL;
	अगर (!args.wasdel && args.tp->t_blk_res == 0) अणु
		error = -ENOSPC;
		जाओ error0;
	पूर्ण
	error = xfs_alloc_vextent(&args);
	अगर (error)
		जाओ error0;

	अगर (args.fsbno == शून्यFSBLOCK && args.minleft) अणु
		/*
		 * Could not find an AG with enough मुक्त space to satisfy
		 * a full btree split.  Try again and अगर
		 * successful activate the lowspace algorithm.
		 */
		args.fsbno = 0;
		args.type = XFS_ALLOCTYPE_FIRST_AG;
		error = xfs_alloc_vextent(&args);
		अगर (error)
			जाओ error0;
		cur->bc_tp->t_flags |= XFS_TRANS_LOWMODE;
	पूर्ण
	अगर (WARN_ON_ONCE(args.fsbno == शून्यFSBLOCK)) अणु
		*stat = 0;
		वापस 0;
	पूर्ण

	ASSERT(args.len == 1);
	cur->bc_tp->t_firstblock = args.fsbno;
	cur->bc_ino.allocated++;
	cur->bc_ino.ip->i_nblocks++;
	xfs_trans_log_inode(args.tp, cur->bc_ino.ip, XFS_ILOG_CORE);
	xfs_trans_mod_dquot_byino(args.tp, cur->bc_ino.ip,
			XFS_TRANS_DQ_BCOUNT, 1L);

	new->l = cpu_to_be64(args.fsbno);

	*stat = 1;
	वापस 0;

 error0:
	वापस error;
पूर्ण

STATIC पूर्णांक
xfs_bmbt_मुक्त_block(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = cur->bc_mp;
	काष्ठा xfs_inode	*ip = cur->bc_ino.ip;
	काष्ठा xfs_trans	*tp = cur->bc_tp;
	xfs_fsblock_t		fsbno = XFS_DADDR_TO_FSB(mp, XFS_BUF_ADDR(bp));
	काष्ठा xfs_owner_info	oinfo;

	xfs_rmap_ino_bmbt_owner(&oinfo, ip->i_ino, cur->bc_ino.whichविभाजन);
	xfs_bmap_add_मुक्त(cur->bc_tp, fsbno, 1, &oinfo);
	ip->i_nblocks--;

	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);
	xfs_trans_mod_dquot_byino(tp, ip, XFS_TRANS_DQ_BCOUNT, -1L);
	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_bmbt_get_minrecs(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level)
अणु
	अगर (level == cur->bc_nlevels - 1) अणु
		काष्ठा xfs_अगरork	*अगरp;

		अगरp = XFS_IFORK_PTR(cur->bc_ino.ip,
				    cur->bc_ino.whichविभाजन);

		वापस xfs_bmbt_maxrecs(cur->bc_mp,
					अगरp->अगर_broot_bytes, level == 0) / 2;
	पूर्ण

	वापस cur->bc_mp->m_bmap_dmnr[level != 0];
पूर्ण

पूर्णांक
xfs_bmbt_get_maxrecs(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level)
अणु
	अगर (level == cur->bc_nlevels - 1) अणु
		काष्ठा xfs_अगरork	*अगरp;

		अगरp = XFS_IFORK_PTR(cur->bc_ino.ip,
				    cur->bc_ino.whichविभाजन);

		वापस xfs_bmbt_maxrecs(cur->bc_mp,
					अगरp->अगर_broot_bytes, level == 0);
	पूर्ण

	वापस cur->bc_mp->m_bmap_dmxr[level != 0];

पूर्ण

/*
 * Get the maximum records we could store in the on-disk क्रमmat.
 *
 * For non-root nodes this is equivalent to xfs_bmbt_get_maxrecs, but
 * क्रम the root node this checks the available space in the dinode विभाजन
 * so that we can resize the in-memory buffer to match it.  After a
 * resize to the maximum size this function वापसs the same value
 * as xfs_bmbt_get_maxrecs क्रम the root node, too.
 */
STATIC पूर्णांक
xfs_bmbt_get_dmaxrecs(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level)
अणु
	अगर (level != cur->bc_nlevels - 1)
		वापस cur->bc_mp->m_bmap_dmxr[level != 0];
	वापस xfs_bmdr_maxrecs(cur->bc_ino.विभाजनsize, level == 0);
पूर्ण

STATIC व्योम
xfs_bmbt_init_key_from_rec(
	जोड़ xfs_btree_key	*key,
	जोड़ xfs_btree_rec	*rec)
अणु
	key->bmbt.br_startoff =
		cpu_to_be64(xfs_bmbt_disk_get_startoff(&rec->bmbt));
पूर्ण

STATIC व्योम
xfs_bmbt_init_high_key_from_rec(
	जोड़ xfs_btree_key	*key,
	जोड़ xfs_btree_rec	*rec)
अणु
	key->bmbt.br_startoff = cpu_to_be64(
			xfs_bmbt_disk_get_startoff(&rec->bmbt) +
			xfs_bmbt_disk_get_blockcount(&rec->bmbt) - 1);
पूर्ण

STATIC व्योम
xfs_bmbt_init_rec_from_cur(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_rec	*rec)
अणु
	xfs_bmbt_disk_set_all(&rec->bmbt, &cur->bc_rec.b);
पूर्ण

STATIC व्योम
xfs_bmbt_init_ptr_from_cur(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*ptr)
अणु
	ptr->l = 0;
पूर्ण

STATIC पूर्णांक64_t
xfs_bmbt_key_dअगरf(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*key)
अणु
	वापस (पूर्णांक64_t)be64_to_cpu(key->bmbt.br_startoff) -
				      cur->bc_rec.b.br_startoff;
पूर्ण

STATIC पूर्णांक64_t
xfs_bmbt_dअगरf_two_keys(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*k1,
	जोड़ xfs_btree_key	*k2)
अणु
	uपूर्णांक64_t		a = be64_to_cpu(k1->bmbt.br_startoff);
	uपूर्णांक64_t		b = be64_to_cpu(k2->bmbt.br_startoff);

	/*
	 * Note: This routine previously casted a and b to पूर्णांक64 and subtracted
	 * them to generate a result.  This lead to problems अगर b was the
	 * "maximum" key value (all ones) being चिन्हित incorrectly, hence this
	 * somewhat less efficient version.
	 */
	अगर (a > b)
		वापस 1;
	अगर (b > a)
		वापस -1;
	वापस 0;
पूर्ण

अटल xfs_failaddr_t
xfs_bmbt_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_btree_block	*block = XFS_BUF_TO_BLOCK(bp);
	xfs_failaddr_t		fa;
	अचिन्हित पूर्णांक		level;

	अगर (!xfs_verअगरy_magic(bp, block->bb_magic))
		वापस __this_address;

	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		/*
		 * XXX: need a better way of verअगरying the owner here. Right now
		 * just make sure there has been one set.
		 */
		fa = xfs_btree_lblock_v5hdr_verअगरy(bp, XFS_RMAP_OWN_UNKNOWN);
		अगर (fa)
			वापस fa;
	पूर्ण

	/*
	 * numrecs and level verअगरication.
	 *
	 * We करोn't know what विभाजन we beदीर्घ to, so just verअगरy that the level
	 * is less than the maximum of the two. Later checks will be more
	 * precise.
	 */
	level = be16_to_cpu(block->bb_level);
	अगर (level > max(mp->m_bm_maxlevels[0], mp->m_bm_maxlevels[1]))
		वापस __this_address;

	वापस xfs_btree_lblock_verअगरy(bp, mp->m_bmap_dmxr[level != 0]);
पूर्ण

अटल व्योम
xfs_bmbt_पढ़ो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	xfs_failaddr_t	fa;

	अगर (!xfs_btree_lblock_verअगरy_crc(bp))
		xfs_verअगरier_error(bp, -EFSBADCRC, __this_address);
	अन्यथा अणु
		fa = xfs_bmbt_verअगरy(bp);
		अगर (fa)
			xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
	पूर्ण

	अगर (bp->b_error)
		trace_xfs_btree_corrupt(bp, _RET_IP_);
पूर्ण

अटल व्योम
xfs_bmbt_ग_लिखो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	xfs_failaddr_t	fa;

	fa = xfs_bmbt_verअगरy(bp);
	अगर (fa) अणु
		trace_xfs_btree_corrupt(bp, _RET_IP_);
		xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
		वापस;
	पूर्ण
	xfs_btree_lblock_calc_crc(bp);
पूर्ण

स्थिर काष्ठा xfs_buf_ops xfs_bmbt_buf_ops = अणु
	.name = "xfs_bmbt",
	.magic = अणु cpu_to_be32(XFS_BMAP_MAGIC),
		   cpu_to_be32(XFS_BMAP_CRC_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_bmbt_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_bmbt_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा = xfs_bmbt_verअगरy,
पूर्ण;


STATIC पूर्णांक
xfs_bmbt_keys_inorder(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_key	*k1,
	जोड़ xfs_btree_key	*k2)
अणु
	वापस be64_to_cpu(k1->bmbt.br_startoff) <
		be64_to_cpu(k2->bmbt.br_startoff);
पूर्ण

STATIC पूर्णांक
xfs_bmbt_recs_inorder(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_rec	*r1,
	जोड़ xfs_btree_rec	*r2)
अणु
	वापस xfs_bmbt_disk_get_startoff(&r1->bmbt) +
		xfs_bmbt_disk_get_blockcount(&r1->bmbt) <=
		xfs_bmbt_disk_get_startoff(&r2->bmbt);
पूर्ण

अटल स्थिर काष्ठा xfs_btree_ops xfs_bmbt_ops = अणु
	.rec_len		= माप(xfs_bmbt_rec_t),
	.key_len		= माप(xfs_bmbt_key_t),

	.dup_cursor		= xfs_bmbt_dup_cursor,
	.update_cursor		= xfs_bmbt_update_cursor,
	.alloc_block		= xfs_bmbt_alloc_block,
	.मुक्त_block		= xfs_bmbt_मुक्त_block,
	.get_maxrecs		= xfs_bmbt_get_maxrecs,
	.get_minrecs		= xfs_bmbt_get_minrecs,
	.get_dmaxrecs		= xfs_bmbt_get_dmaxrecs,
	.init_key_from_rec	= xfs_bmbt_init_key_from_rec,
	.init_high_key_from_rec	= xfs_bmbt_init_high_key_from_rec,
	.init_rec_from_cur	= xfs_bmbt_init_rec_from_cur,
	.init_ptr_from_cur	= xfs_bmbt_init_ptr_from_cur,
	.key_dअगरf		= xfs_bmbt_key_dअगरf,
	.dअगरf_two_keys		= xfs_bmbt_dअगरf_two_keys,
	.buf_ops		= &xfs_bmbt_buf_ops,
	.keys_inorder		= xfs_bmbt_keys_inorder,
	.recs_inorder		= xfs_bmbt_recs_inorder,
पूर्ण;

/*
 * Allocate a new bmap btree cursor.
 */
काष्ठा xfs_btree_cur *				/* new bmap btree cursor */
xfs_bmbt_init_cursor(
	काष्ठा xfs_mount	*mp,		/* file प्रणाली mount poपूर्णांक */
	काष्ठा xfs_trans	*tp,		/* transaction poपूर्णांकer */
	काष्ठा xfs_inode	*ip,		/* inode owning the btree */
	पूर्णांक			whichविभाजन)	/* data or attr विभाजन */
अणु
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	काष्ठा xfs_btree_cur	*cur;
	ASSERT(whichविभाजन != XFS_COW_FORK);

	cur = kmem_cache_zalloc(xfs_btree_cur_zone, GFP_NOFS | __GFP_NOFAIL);

	cur->bc_tp = tp;
	cur->bc_mp = mp;
	cur->bc_nlevels = be16_to_cpu(अगरp->अगर_broot->bb_level) + 1;
	cur->bc_btnum = XFS_BTNUM_BMAP;
	cur->bc_blocklog = mp->m_sb.sb_blocklog;
	cur->bc_stम_से_भf = XFS_STATS_CALC_INDEX(xs_bmbt_2);

	cur->bc_ops = &xfs_bmbt_ops;
	cur->bc_flags = XFS_BTREE_LONG_PTRS | XFS_BTREE_ROOT_IN_INODE;
	अगर (xfs_sb_version_hascrc(&mp->m_sb))
		cur->bc_flags |= XFS_BTREE_CRC_BLOCKS;

	cur->bc_ino.विभाजनsize = XFS_IFORK_SIZE(ip, whichविभाजन);
	cur->bc_ino.ip = ip;
	cur->bc_ino.allocated = 0;
	cur->bc_ino.flags = 0;
	cur->bc_ino.whichविभाजन = whichविभाजन;

	वापस cur;
पूर्ण

/*
 * Calculate number of records in a bmap btree block.
 */
पूर्णांक
xfs_bmbt_maxrecs(
	काष्ठा xfs_mount	*mp,
	पूर्णांक			blocklen,
	पूर्णांक			leaf)
अणु
	blocklen -= XFS_BMBT_BLOCK_LEN(mp);

	अगर (leaf)
		वापस blocklen / माप(xfs_bmbt_rec_t);
	वापस blocklen / (माप(xfs_bmbt_key_t) + माप(xfs_bmbt_ptr_t));
पूर्ण

/*
 * Calculate number of records in a bmap btree inode root.
 */
पूर्णांक
xfs_bmdr_maxrecs(
	पूर्णांक			blocklen,
	पूर्णांक			leaf)
अणु
	blocklen -= माप(xfs_bmdr_block_t);

	अगर (leaf)
		वापस blocklen / माप(xfs_bmdr_rec_t);
	वापस blocklen / (माप(xfs_bmdr_key_t) + माप(xfs_bmdr_ptr_t));
पूर्ण

/*
 * Change the owner of a btree क्रमmat विभाजन fo the inode passed in. Change it to
 * the owner of that is passed in so that we can change owners beक्रमe or after
 * we चयन विभाजनs between inodes. The operation that the caller is करोing will
 * determine whether is needs to change owner beक्रमe or after the चयन.
 *
 * For demand paged transactional modअगरication, the विभाजन चयन should be करोne
 * after पढ़ोing in all the blocks, modअगरying them and pinning them in the
 * transaction. For modअगरication when the buffers are alपढ़ोy pinned in memory,
 * the विभाजन चयन can be करोne beक्रमe changing the owner as we won't need to
 * validate the owner until the btree buffers are unpinned and ग_लिखोs can occur
 * again.
 *
 * For recovery based ownership change, there is no transactional context and
 * so a buffer list must be supplied so that we can record the buffers that we
 * modअगरied क्रम the caller to issue IO on.
 */
पूर्णांक
xfs_bmbt_change_owner(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन,
	xfs_ino_t		new_owner,
	काष्ठा list_head	*buffer_list)
अणु
	काष्ठा xfs_btree_cur	*cur;
	पूर्णांक			error;

	ASSERT(tp || buffer_list);
	ASSERT(!(tp && buffer_list));
	ASSERT(XFS_IFORK_PTR(ip, whichविभाजन)->अगर_क्रमmat == XFS_DINODE_FMT_BTREE);

	cur = xfs_bmbt_init_cursor(ip->i_mount, tp, ip, whichविभाजन);
	cur->bc_ino.flags |= XFS_BTCUR_BMBT_INVALID_OWNER;

	error = xfs_btree_change_owner(cur, new_owner, buffer_list);
	xfs_btree_del_cursor(cur, error);
	वापस error;
पूर्ण

/* Calculate the bmap btree size क्रम some records. */
अचिन्हित दीर्घ दीर्घ
xfs_bmbt_calc_size(
	काष्ठा xfs_mount	*mp,
	अचिन्हित दीर्घ दीर्घ	len)
अणु
	वापस xfs_btree_calc_size(mp->m_bmap_dmnr, len);
पूर्ण
