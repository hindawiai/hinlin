<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2003,2005 Silicon Graphics, Inc.
 * Copyright (c) 2013 Red Hat, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_dir2.h"
#समावेश "xfs_dir2_priv.h"
#समावेश "xfs_error.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_buf_item.h"

/*
 * Local function declarations.
 */
अटल पूर्णांक xfs_dir2_leaf_lookup_पूर्णांक(xfs_da_args_t *args, काष्ठा xfs_buf **lbpp,
				    पूर्णांक *indexp, काष्ठा xfs_buf **dbpp,
				    काष्ठा xfs_dir3_icleaf_hdr *leafhdr);
अटल व्योम xfs_dir3_leaf_log_bests(काष्ठा xfs_da_args *args,
				    काष्ठा xfs_buf *bp, पूर्णांक first, पूर्णांक last);
अटल व्योम xfs_dir3_leaf_log_tail(काष्ठा xfs_da_args *args,
				   काष्ठा xfs_buf *bp);

व्योम
xfs_dir2_leaf_hdr_from_disk(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_dir3_icleaf_hdr	*to,
	काष्ठा xfs_dir2_leaf		*from)
अणु
	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		काष्ठा xfs_dir3_leaf *from3 = (काष्ठा xfs_dir3_leaf *)from;

		to->क्रमw = be32_to_cpu(from3->hdr.info.hdr.क्रमw);
		to->back = be32_to_cpu(from3->hdr.info.hdr.back);
		to->magic = be16_to_cpu(from3->hdr.info.hdr.magic);
		to->count = be16_to_cpu(from3->hdr.count);
		to->stale = be16_to_cpu(from3->hdr.stale);
		to->ents = from3->__ents;

		ASSERT(to->magic == XFS_सूची3_LEAF1_MAGIC ||
		       to->magic == XFS_सूची3_LEAFN_MAGIC);
	पूर्ण अन्यथा अणु
		to->क्रमw = be32_to_cpu(from->hdr.info.क्रमw);
		to->back = be32_to_cpu(from->hdr.info.back);
		to->magic = be16_to_cpu(from->hdr.info.magic);
		to->count = be16_to_cpu(from->hdr.count);
		to->stale = be16_to_cpu(from->hdr.stale);
		to->ents = from->__ents;

		ASSERT(to->magic == XFS_सूची2_LEAF1_MAGIC ||
		       to->magic == XFS_सूची2_LEAFN_MAGIC);
	पूर्ण
पूर्ण

व्योम
xfs_dir2_leaf_hdr_to_disk(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_dir2_leaf		*to,
	काष्ठा xfs_dir3_icleaf_hdr	*from)
अणु
	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		काष्ठा xfs_dir3_leaf *to3 = (काष्ठा xfs_dir3_leaf *)to;

		ASSERT(from->magic == XFS_सूची3_LEAF1_MAGIC ||
		       from->magic == XFS_सूची3_LEAFN_MAGIC);

		to3->hdr.info.hdr.क्रमw = cpu_to_be32(from->क्रमw);
		to3->hdr.info.hdr.back = cpu_to_be32(from->back);
		to3->hdr.info.hdr.magic = cpu_to_be16(from->magic);
		to3->hdr.count = cpu_to_be16(from->count);
		to3->hdr.stale = cpu_to_be16(from->stale);
	पूर्ण अन्यथा अणु
		ASSERT(from->magic == XFS_सूची2_LEAF1_MAGIC ||
		       from->magic == XFS_सूची2_LEAFN_MAGIC);

		to->hdr.info.क्रमw = cpu_to_be32(from->क्रमw);
		to->hdr.info.back = cpu_to_be32(from->back);
		to->hdr.info.magic = cpu_to_be16(from->magic);
		to->hdr.count = cpu_to_be16(from->count);
		to->hdr.stale = cpu_to_be16(from->stale);
	पूर्ण
पूर्ण

/*
 * Check the पूर्णांकernal consistency of a leaf1 block.
 * Pop an निश्चित अगर something is wrong.
 */
#अगर_घोषित DEBUG
अटल xfs_failaddr_t
xfs_dir3_leaf1_check(
	काष्ठा xfs_inode	*dp,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_dir2_leaf	*leaf = bp->b_addr;
	काष्ठा xfs_dir3_icleaf_hdr leafhdr;

	xfs_dir2_leaf_hdr_from_disk(dp->i_mount, &leafhdr, leaf);

	अगर (leafhdr.magic == XFS_सूची3_LEAF1_MAGIC) अणु
		काष्ठा xfs_dir3_leaf_hdr *leaf3 = bp->b_addr;
		अगर (be64_to_cpu(leaf3->info.blkno) != bp->b_bn)
			वापस __this_address;
	पूर्ण अन्यथा अगर (leafhdr.magic != XFS_सूची2_LEAF1_MAGIC)
		वापस __this_address;

	वापस xfs_dir3_leaf_check_पूर्णांक(dp->i_mount, &leafhdr, leaf, false);
पूर्ण

अटल अंतरभूत व्योम
xfs_dir3_leaf_check(
	काष्ठा xfs_inode	*dp,
	काष्ठा xfs_buf		*bp)
अणु
	xfs_failaddr_t		fa;

	fa = xfs_dir3_leaf1_check(dp, bp);
	अगर (!fa)
		वापस;
	xfs_corruption_error(__func__, XFS_ERRLEVEL_LOW, dp->i_mount,
			bp->b_addr, BBTOB(bp->b_length), __खाता__, __LINE__,
			fa);
	ASSERT(0);
पूर्ण
#अन्यथा
#घोषणा	xfs_dir3_leaf_check(dp, bp)
#पूर्ण_अगर

xfs_failaddr_t
xfs_dir3_leaf_check_पूर्णांक(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_dir3_icleaf_hdr	*hdr,
	काष्ठा xfs_dir2_leaf		*leaf,
	bool				expensive_checking)
अणु
	काष्ठा xfs_da_geometry		*geo = mp->m_dir_geo;
	xfs_dir2_leaf_tail_t		*ltp;
	पूर्णांक				stale;
	पूर्णांक				i;

	ltp = xfs_dir2_leaf_tail_p(geo, leaf);

	/*
	 * XXX (dgc): This value is not restrictive enough.
	 * Should factor in the size of the bests table as well.
	 * We can deduce a value क्रम that from i_disk_size.
	 */
	अगर (hdr->count > geo->leaf_max_ents)
		वापस __this_address;

	/* Leaves and bests करोn't overlap in leaf क्रमmat. */
	अगर ((hdr->magic == XFS_सूची2_LEAF1_MAGIC ||
	     hdr->magic == XFS_सूची3_LEAF1_MAGIC) &&
	    (अक्षर *)&hdr->ents[hdr->count] > (अक्षर *)xfs_dir2_leaf_bests_p(ltp))
		वापस __this_address;

	अगर (!expensive_checking)
		वापस शून्य;

	/* Check hash value order, count stale entries.  */
	क्रम (i = stale = 0; i < hdr->count; i++) अणु
		अगर (i + 1 < hdr->count) अणु
			अगर (be32_to_cpu(hdr->ents[i].hashval) >
					be32_to_cpu(hdr->ents[i + 1].hashval))
				वापस __this_address;
		पूर्ण
		अगर (hdr->ents[i].address == cpu_to_be32(XFS_सूची2_शून्य_DATAPTR))
			stale++;
	पूर्ण
	अगर (hdr->stale != stale)
		वापस __this_address;
	वापस शून्य;
पूर्ण

/*
 * We verअगरy the magic numbers beक्रमe decoding the leaf header so that on debug
 * kernels we करोn't get निश्चितion failures in xfs_dir3_leaf_hdr_from_disk() due
 * to incorrect magic numbers.
 */
अटल xfs_failaddr_t
xfs_dir3_leaf_verअगरy(
	काष्ठा xfs_buf			*bp)
अणु
	काष्ठा xfs_mount		*mp = bp->b_mount;
	काष्ठा xfs_dir3_icleaf_hdr	leafhdr;
	xfs_failaddr_t			fa;

	fa = xfs_da3_blkinfo_verअगरy(bp, bp->b_addr);
	अगर (fa)
		वापस fa;

	xfs_dir2_leaf_hdr_from_disk(mp, &leafhdr, bp->b_addr);
	वापस xfs_dir3_leaf_check_पूर्णांक(mp, &leafhdr, bp->b_addr, true);
पूर्ण

अटल व्योम
xfs_dir3_leaf_पढ़ो_verअगरy(
	काष्ठा xfs_buf  *bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	xfs_failaddr_t		fa;

	अगर (xfs_sb_version_hascrc(&mp->m_sb) &&
	     !xfs_buf_verअगरy_cksum(bp, XFS_सूची3_LEAF_CRC_OFF))
		xfs_verअगरier_error(bp, -EFSBADCRC, __this_address);
	अन्यथा अणु
		fa = xfs_dir3_leaf_verअगरy(bp);
		अगर (fa)
			xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
	पूर्ण
पूर्ण

अटल व्योम
xfs_dir3_leaf_ग_लिखो_verअगरy(
	काष्ठा xfs_buf  *bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;
	काष्ठा xfs_dir3_leaf_hdr *hdr3 = bp->b_addr;
	xfs_failaddr_t		fa;

	fa = xfs_dir3_leaf_verअगरy(bp);
	अगर (fa) अणु
		xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
		वापस;
	पूर्ण

	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस;

	अगर (bip)
		hdr3->info.lsn = cpu_to_be64(bip->bli_item.li_lsn);

	xfs_buf_update_cksum(bp, XFS_सूची3_LEAF_CRC_OFF);
पूर्ण

स्थिर काष्ठा xfs_buf_ops xfs_dir3_leaf1_buf_ops = अणु
	.name = "xfs_dir3_leaf1",
	.magic16 = अणु cpu_to_be16(XFS_सूची2_LEAF1_MAGIC),
		     cpu_to_be16(XFS_सूची3_LEAF1_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_dir3_leaf_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_dir3_leaf_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा = xfs_dir3_leaf_verअगरy,
पूर्ण;

स्थिर काष्ठा xfs_buf_ops xfs_dir3_leafn_buf_ops = अणु
	.name = "xfs_dir3_leafn",
	.magic16 = अणु cpu_to_be16(XFS_सूची2_LEAFN_MAGIC),
		     cpu_to_be16(XFS_सूची3_LEAFN_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_dir3_leaf_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_dir3_leaf_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा = xfs_dir3_leaf_verअगरy,
पूर्ण;

पूर्णांक
xfs_dir3_leaf_पढ़ो(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*dp,
	xfs_dablk_t		fbno,
	काष्ठा xfs_buf		**bpp)
अणु
	पूर्णांक			err;

	err = xfs_da_पढ़ो_buf(tp, dp, fbno, 0, bpp, XFS_DATA_FORK,
			&xfs_dir3_leaf1_buf_ops);
	अगर (!err && tp && *bpp)
		xfs_trans_buf_set_type(tp, *bpp, XFS_BLFT_सूची_LEAF1_BUF);
	वापस err;
पूर्ण

पूर्णांक
xfs_dir3_leafn_पढ़ो(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*dp,
	xfs_dablk_t		fbno,
	काष्ठा xfs_buf		**bpp)
अणु
	पूर्णांक			err;

	err = xfs_da_पढ़ो_buf(tp, dp, fbno, 0, bpp, XFS_DATA_FORK,
			&xfs_dir3_leafn_buf_ops);
	अगर (!err && tp && *bpp)
		xfs_trans_buf_set_type(tp, *bpp, XFS_BLFT_सूची_LEAFN_BUF);
	वापस err;
पूर्ण

/*
 * Initialize a new leaf block, leaf1 or leafn magic accepted.
 */
अटल व्योम
xfs_dir3_leaf_init(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*bp,
	xfs_ino_t		owner,
	uपूर्णांक16_t		type)
अणु
	काष्ठा xfs_dir2_leaf	*leaf = bp->b_addr;

	ASSERT(type == XFS_सूची2_LEAF1_MAGIC || type == XFS_सूची2_LEAFN_MAGIC);

	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		काष्ठा xfs_dir3_leaf_hdr *leaf3 = bp->b_addr;

		स_रखो(leaf3, 0, माप(*leaf3));

		leaf3->info.hdr.magic = (type == XFS_सूची2_LEAF1_MAGIC)
					 ? cpu_to_be16(XFS_सूची3_LEAF1_MAGIC)
					 : cpu_to_be16(XFS_सूची3_LEAFN_MAGIC);
		leaf3->info.blkno = cpu_to_be64(bp->b_bn);
		leaf3->info.owner = cpu_to_be64(owner);
		uuid_copy(&leaf3->info.uuid, &mp->m_sb.sb_meta_uuid);
	पूर्ण अन्यथा अणु
		स_रखो(leaf, 0, माप(*leaf));
		leaf->hdr.info.magic = cpu_to_be16(type);
	पूर्ण

	/*
	 * If it's a leaf-क्रमmat directory initialize the tail.
	 * Caller is responsible क्रम initialising the bests table.
	 */
	अगर (type == XFS_सूची2_LEAF1_MAGIC) अणु
		काष्ठा xfs_dir2_leaf_tail *ltp;

		ltp = xfs_dir2_leaf_tail_p(mp->m_dir_geo, leaf);
		ltp->bestcount = 0;
		bp->b_ops = &xfs_dir3_leaf1_buf_ops;
		xfs_trans_buf_set_type(tp, bp, XFS_BLFT_सूची_LEAF1_BUF);
	पूर्ण अन्यथा अणु
		bp->b_ops = &xfs_dir3_leafn_buf_ops;
		xfs_trans_buf_set_type(tp, bp, XFS_BLFT_सूची_LEAFN_BUF);
	पूर्ण
पूर्ण

पूर्णांक
xfs_dir3_leaf_get_buf(
	xfs_da_args_t		*args,
	xfs_dir2_db_t		bno,
	काष्ठा xfs_buf		**bpp,
	uपूर्णांक16_t		magic)
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_trans	*tp = args->trans;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;

	ASSERT(magic == XFS_सूची2_LEAF1_MAGIC || magic == XFS_सूची2_LEAFN_MAGIC);
	ASSERT(bno >= xfs_dir2_byte_to_db(args->geo, XFS_सूची2_LEAF_OFFSET) &&
	       bno < xfs_dir2_byte_to_db(args->geo, XFS_सूची2_FREE_OFFSET));

	error = xfs_da_get_buf(tp, dp, xfs_dir2_db_to_da(args->geo, bno),
			       &bp, XFS_DATA_FORK);
	अगर (error)
		वापस error;

	xfs_dir3_leaf_init(mp, tp, bp, dp->i_ino, magic);
	xfs_dir3_leaf_log_header(args, bp);
	अगर (magic == XFS_सूची2_LEAF1_MAGIC)
		xfs_dir3_leaf_log_tail(args, bp);
	*bpp = bp;
	वापस 0;
पूर्ण

/*
 * Convert a block क्रमm directory to a leaf क्रमm directory.
 */
पूर्णांक						/* error */
xfs_dir2_block_to_leaf(
	xfs_da_args_t		*args,		/* operation arguments */
	काष्ठा xfs_buf		*dbp)		/* input block's buffer */
अणु
	__be16			*bestsp;	/* leaf's bestsp entries */
	xfs_dablk_t		blkno;		/* leaf block's bno */
	xfs_dir2_data_hdr_t	*hdr;		/* block header */
	xfs_dir2_leaf_entry_t	*blp;		/* block's leaf entries */
	xfs_dir2_block_tail_t	*btp;		/* block's tail */
	xfs_inode_t		*dp;		/* incore directory inode */
	पूर्णांक			error;		/* error वापस code */
	काष्ठा xfs_buf		*lbp;		/* leaf block's buffer */
	xfs_dir2_db_t		ldb;		/* leaf block's bno */
	xfs_dir2_leaf_t		*leaf;		/* leaf काष्ठाure */
	xfs_dir2_leaf_tail_t	*ltp;		/* leaf's tail */
	पूर्णांक			needlog;	/* need to log block header */
	पूर्णांक			needscan;	/* need to rescan bestमुक्त */
	xfs_trans_t		*tp;		/* transaction poपूर्णांकer */
	काष्ठा xfs_dir2_data_मुक्त *bf;
	काष्ठा xfs_dir3_icleaf_hdr leafhdr;

	trace_xfs_dir2_block_to_leaf(args);

	dp = args->dp;
	tp = args->trans;
	/*
	 * Add the leaf block to the inode.
	 * This पूर्णांकerface will only put blocks in the leaf/node range.
	 * Since that's empty now, we'll get the root (block 0 in range).
	 */
	अगर ((error = xfs_da_grow_inode(args, &blkno))) अणु
		वापस error;
	पूर्ण
	ldb = xfs_dir2_da_to_db(args->geo, blkno);
	ASSERT(ldb == xfs_dir2_byte_to_db(args->geo, XFS_सूची2_LEAF_OFFSET));
	/*
	 * Initialize the leaf block, get a buffer क्रम it.
	 */
	error = xfs_dir3_leaf_get_buf(args, ldb, &lbp, XFS_सूची2_LEAF1_MAGIC);
	अगर (error)
		वापस error;

	leaf = lbp->b_addr;
	hdr = dbp->b_addr;
	xfs_dir3_data_check(dp, dbp);
	btp = xfs_dir2_block_tail_p(args->geo, hdr);
	blp = xfs_dir2_block_leaf_p(btp);
	bf = xfs_dir2_data_bestमुक्त_p(dp->i_mount, hdr);

	/*
	 * Set the counts in the leaf header.
	 */
	xfs_dir2_leaf_hdr_from_disk(dp->i_mount, &leafhdr, leaf);
	leafhdr.count = be32_to_cpu(btp->count);
	leafhdr.stale = be32_to_cpu(btp->stale);
	xfs_dir2_leaf_hdr_to_disk(dp->i_mount, leaf, &leafhdr);
	xfs_dir3_leaf_log_header(args, lbp);

	/*
	 * Could compact these but I think we always करो the conversion
	 * after squeezing out stale entries.
	 */
	स_नकल(leafhdr.ents, blp,
		be32_to_cpu(btp->count) * माप(काष्ठा xfs_dir2_leaf_entry));
	xfs_dir3_leaf_log_ents(args, &leafhdr, lbp, 0, leafhdr.count - 1);
	needscan = 0;
	needlog = 1;
	/*
	 * Make the space क्रमmerly occupied by the leaf entries and block
	 * tail be मुक्त.
	 */
	xfs_dir2_data_make_मुक्त(args, dbp,
		(xfs_dir2_data_aoff_t)((अक्षर *)blp - (अक्षर *)hdr),
		(xfs_dir2_data_aoff_t)((अक्षर *)hdr + args->geo->blksize -
				       (अक्षर *)blp),
		&needlog, &needscan);
	/*
	 * Fix up the block header, make it a data block.
	 */
	dbp->b_ops = &xfs_dir3_data_buf_ops;
	xfs_trans_buf_set_type(tp, dbp, XFS_BLFT_सूची_DATA_BUF);
	अगर (hdr->magic == cpu_to_be32(XFS_सूची2_BLOCK_MAGIC))
		hdr->magic = cpu_to_be32(XFS_सूची2_DATA_MAGIC);
	अन्यथा
		hdr->magic = cpu_to_be32(XFS_सूची3_DATA_MAGIC);

	अगर (needscan)
		xfs_dir2_data_मुक्तscan(dp->i_mount, hdr, &needlog);
	/*
	 * Set up leaf tail and bests table.
	 */
	ltp = xfs_dir2_leaf_tail_p(args->geo, leaf);
	ltp->bestcount = cpu_to_be32(1);
	bestsp = xfs_dir2_leaf_bests_p(ltp);
	bestsp[0] =  bf[0].length;
	/*
	 * Log the data header and leaf bests table.
	 */
	अगर (needlog)
		xfs_dir2_data_log_header(args, dbp);
	xfs_dir3_leaf_check(dp, lbp);
	xfs_dir3_data_check(dp, dbp);
	xfs_dir3_leaf_log_bests(args, lbp, 0, 0);
	वापस 0;
पूर्ण

STATIC व्योम
xfs_dir3_leaf_find_stale(
	काष्ठा xfs_dir3_icleaf_hdr *leafhdr,
	काष्ठा xfs_dir2_leaf_entry *ents,
	पूर्णांक			index,
	पूर्णांक			*lowstale,
	पूर्णांक			*highstale)
अणु
	/*
	 * Find the first stale entry beक्रमe our index, अगर any.
	 */
	क्रम (*lowstale = index - 1; *lowstale >= 0; --*lowstale) अणु
		अगर (ents[*lowstale].address ==
		    cpu_to_be32(XFS_सूची2_शून्य_DATAPTR))
			अवरोध;
	पूर्ण

	/*
	 * Find the first stale entry at or after our index, अगर any.
	 * Stop अगर the result would require moving more entries than using
	 * lowstale.
	 */
	क्रम (*highstale = index; *highstale < leafhdr->count; ++*highstale) अणु
		अगर (ents[*highstale].address ==
		    cpu_to_be32(XFS_सूची2_शून्य_DATAPTR))
			अवरोध;
		अगर (*lowstale >= 0 && index - *lowstale <= *highstale - index)
			अवरोध;
	पूर्ण
पूर्ण

काष्ठा xfs_dir2_leaf_entry *
xfs_dir3_leaf_find_entry(
	काष्ठा xfs_dir3_icleaf_hdr *leafhdr,
	काष्ठा xfs_dir2_leaf_entry *ents,
	पूर्णांक			index,		/* leaf table position */
	पूर्णांक			compact,	/* need to compact leaves */
	पूर्णांक			lowstale,	/* index of prev stale leaf */
	पूर्णांक			highstale,	/* index of next stale leaf */
	पूर्णांक			*lfloglow,	/* low leaf logging index */
	पूर्णांक			*lfloghigh)	/* high leaf logging index */
अणु
	अगर (!leafhdr->stale) अणु
		xfs_dir2_leaf_entry_t	*lep;	/* leaf entry table poपूर्णांकer */

		/*
		 * Now we need to make room to insert the leaf entry.
		 *
		 * If there are no stale entries, just insert a hole at index.
		 */
		lep = &ents[index];
		अगर (index < leafhdr->count)
			स_हटाओ(lep + 1, lep,
				(leafhdr->count - index) * माप(*lep));

		/*
		 * Record low and high logging indices क्रम the leaf.
		 */
		*lfloglow = index;
		*lfloghigh = leafhdr->count++;
		वापस lep;
	पूर्ण

	/*
	 * There are stale entries.
	 *
	 * We will use one of them क्रम the new entry.  It's probably not at
	 * the right location, so we'll have to shअगरt some up or करोwn first.
	 *
	 * If we didn't compact beक्रमe, we need to find the nearest stale
	 * entries beक्रमe and after our insertion poपूर्णांक.
	 */
	अगर (compact == 0)
		xfs_dir3_leaf_find_stale(leafhdr, ents, index,
					 &lowstale, &highstale);

	/*
	 * If the low one is better, use it.
	 */
	अगर (lowstale >= 0 &&
	    (highstale == leafhdr->count ||
	     index - lowstale - 1 < highstale - index)) अणु
		ASSERT(index - lowstale - 1 >= 0);
		ASSERT(ents[lowstale].address ==
		       cpu_to_be32(XFS_सूची2_शून्य_DATAPTR));

		/*
		 * Copy entries up to cover the stale entry and make room
		 * क्रम the new entry.
		 */
		अगर (index - lowstale - 1 > 0) अणु
			स_हटाओ(&ents[lowstale], &ents[lowstale + 1],
				(index - lowstale - 1) *
					माप(xfs_dir2_leaf_entry_t));
		पूर्ण
		*lfloglow = min(lowstale, *lfloglow);
		*lfloghigh = max(index - 1, *lfloghigh);
		leafhdr->stale--;
		वापस &ents[index - 1];
	पूर्ण

	/*
	 * The high one is better, so use that one.
	 */
	ASSERT(highstale - index >= 0);
	ASSERT(ents[highstale].address == cpu_to_be32(XFS_सूची2_शून्य_DATAPTR));

	/*
	 * Copy entries करोwn to cover the stale entry and make room क्रम the
	 * new entry.
	 */
	अगर (highstale - index > 0) अणु
		स_हटाओ(&ents[index + 1], &ents[index],
			(highstale - index) * माप(xfs_dir2_leaf_entry_t));
	पूर्ण
	*lfloglow = min(index, *lfloglow);
	*lfloghigh = max(highstale, *lfloghigh);
	leafhdr->stale--;
	वापस &ents[index];
पूर्ण

/*
 * Add an entry to a leaf क्रमm directory.
 */
पूर्णांक						/* error */
xfs_dir2_leaf_addname(
	काष्ठा xfs_da_args	*args)		/* operation arguments */
अणु
	काष्ठा xfs_dir3_icleaf_hdr leafhdr;
	काष्ठा xfs_trans	*tp = args->trans;
	__be16			*bestsp;	/* मुक्तspace table in leaf */
	__be16			*tagp;		/* end of data entry */
	काष्ठा xfs_buf		*dbp;		/* data block buffer */
	काष्ठा xfs_buf		*lbp;		/* leaf's buffer */
	काष्ठा xfs_dir2_leaf	*leaf;		/* leaf काष्ठाure */
	काष्ठा xfs_inode	*dp = args->dp;	/* incore directory inode */
	काष्ठा xfs_dir2_data_hdr *hdr;		/* data block header */
	काष्ठा xfs_dir2_data_entry *dep;	/* data block entry */
	काष्ठा xfs_dir2_leaf_entry *lep;	/* leaf entry table poपूर्णांकer */
	काष्ठा xfs_dir2_leaf_entry *ents;
	काष्ठा xfs_dir2_data_unused *dup;	/* data unused entry */
	काष्ठा xfs_dir2_leaf_tail *ltp;		/* leaf tail poपूर्णांकer */
	काष्ठा xfs_dir2_data_मुक्त *bf;		/* bestमुक्त table */
	पूर्णांक			compact;	/* need to compact leaves */
	पूर्णांक			error;		/* error वापस value */
	पूर्णांक			grown;		/* allocated new data block */
	पूर्णांक			highstale = 0;	/* index of next stale leaf */
	पूर्णांक			i;		/* temporary, index */
	पूर्णांक			index;		/* leaf table position */
	पूर्णांक			length;		/* length of new entry */
	पूर्णांक			lfloglow;	/* low leaf logging index */
	पूर्णांक			lfloghigh;	/* high leaf logging index */
	पूर्णांक			lowstale = 0;	/* index of prev stale leaf */
	पूर्णांक			needbytes;	/* leaf block bytes needed */
	पूर्णांक			needlog;	/* need to log data header */
	पूर्णांक			needscan;	/* need to rescan data मुक्त */
	xfs_dir2_db_t		use_block;	/* data block number */

	trace_xfs_dir2_leaf_addname(args);

	error = xfs_dir3_leaf_पढ़ो(tp, dp, args->geo->leafblk, &lbp);
	अगर (error)
		वापस error;

	/*
	 * Look up the entry by hash value and name.
	 * We know it's not there, our caller has alपढ़ोy करोne a lookup.
	 * So the index is of the entry to insert in front of.
	 * But अगर there are dup hash values the index is of the first of those.
	 */
	index = xfs_dir2_leaf_search_hash(args, lbp);
	leaf = lbp->b_addr;
	ltp = xfs_dir2_leaf_tail_p(args->geo, leaf);
	xfs_dir2_leaf_hdr_from_disk(dp->i_mount, &leafhdr, leaf);
	ents = leafhdr.ents;
	bestsp = xfs_dir2_leaf_bests_p(ltp);
	length = xfs_dir2_data_entsize(dp->i_mount, args->namelen);

	/*
	 * See अगर there are any entries with the same hash value
	 * and space in their block क्रम the new entry.
	 * This is good because it माला_दो multiple same-hash value entries
	 * in a data block, improving the lookup of those entries.
	 */
	क्रम (use_block = -1, lep = &ents[index];
	     index < leafhdr.count && be32_to_cpu(lep->hashval) == args->hashval;
	     index++, lep++) अणु
		अगर (be32_to_cpu(lep->address) == XFS_सूची2_शून्य_DATAPTR)
			जारी;
		i = xfs_dir2_dataptr_to_db(args->geo, be32_to_cpu(lep->address));
		ASSERT(i < be32_to_cpu(ltp->bestcount));
		ASSERT(bestsp[i] != cpu_to_be16(शून्यDATAOFF));
		अगर (be16_to_cpu(bestsp[i]) >= length) अणु
			use_block = i;
			अवरोध;
		पूर्ण
	पूर्ण
	/*
	 * Didn't find a block yet, linear search all the data blocks.
	 */
	अगर (use_block == -1) अणु
		क्रम (i = 0; i < be32_to_cpu(ltp->bestcount); i++) अणु
			/*
			 * Remember a block we see that's missing.
			 */
			अगर (bestsp[i] == cpu_to_be16(शून्यDATAOFF) &&
			    use_block == -1)
				use_block = i;
			अन्यथा अगर (be16_to_cpu(bestsp[i]) >= length) अणु
				use_block = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	/*
	 * How many bytes करो we need in the leaf block?
	 */
	needbytes = 0;
	अगर (!leafhdr.stale)
		needbytes += माप(xfs_dir2_leaf_entry_t);
	अगर (use_block == -1)
		needbytes += माप(xfs_dir2_data_off_t);

	/*
	 * Now समाप्त use_block अगर it refers to a missing block, so we
	 * can use it as an indication of allocation needed.
	 */
	अगर (use_block != -1 && bestsp[use_block] == cpu_to_be16(शून्यDATAOFF))
		use_block = -1;
	/*
	 * If we करोn't have enough मुक्त bytes but we can make enough
	 * by compacting out stale entries, we'll करो that.
	 */
	अगर ((अक्षर *)bestsp - (अक्षर *)&ents[leafhdr.count] < needbytes &&
	    leafhdr.stale > 1)
		compact = 1;

	/*
	 * Otherwise अगर we करोn't have enough मुक्त bytes we need to
	 * convert to node क्रमm.
	 */
	अन्यथा अगर ((अक्षर *)bestsp - (अक्षर *)&ents[leafhdr.count] < needbytes) अणु
		/*
		 * Just checking or no space reservation, give up.
		 */
		अगर ((args->op_flags & XFS_DA_OP_JUSTCHECK) ||
							args->total == 0) अणु
			xfs_trans_brअन्यथा(tp, lbp);
			वापस -ENOSPC;
		पूर्ण
		/*
		 * Convert to node क्रमm.
		 */
		error = xfs_dir2_leaf_to_node(args, lbp);
		अगर (error)
			वापस error;
		/*
		 * Then add the new entry.
		 */
		वापस xfs_dir2_node_addname(args);
	पूर्ण
	/*
	 * Otherwise it will fit without compaction.
	 */
	अन्यथा
		compact = 0;
	/*
	 * If just checking, then it will fit unless we needed to allocate
	 * a new data block.
	 */
	अगर (args->op_flags & XFS_DA_OP_JUSTCHECK) अणु
		xfs_trans_brअन्यथा(tp, lbp);
		वापस use_block == -1 ? -ENOSPC : 0;
	पूर्ण
	/*
	 * If no allocations are allowed, वापस now beक्रमe we've
	 * changed anything.
	 */
	अगर (args->total == 0 && use_block == -1) अणु
		xfs_trans_brअन्यथा(tp, lbp);
		वापस -ENOSPC;
	पूर्ण
	/*
	 * Need to compact the leaf entries, removing stale ones.
	 * Leave one stale entry behind - the one बंदst to our
	 * insertion index - and we'll shअगरt that one to our insertion
	 * poपूर्णांक later.
	 */
	अगर (compact) अणु
		xfs_dir3_leaf_compact_x1(&leafhdr, ents, &index, &lowstale,
			&highstale, &lfloglow, &lfloghigh);
	पूर्ण
	/*
	 * There are stale entries, so we'll need log-low and log-high
	 * impossibly bad values later.
	 */
	अन्यथा अगर (leafhdr.stale) अणु
		lfloglow = leafhdr.count;
		lfloghigh = -1;
	पूर्ण
	/*
	 * If there was no data block space found, we need to allocate
	 * a new one.
	 */
	अगर (use_block == -1) अणु
		/*
		 * Add the new data block.
		 */
		अगर ((error = xfs_dir2_grow_inode(args, XFS_सूची2_DATA_SPACE,
				&use_block))) अणु
			xfs_trans_brअन्यथा(tp, lbp);
			वापस error;
		पूर्ण
		/*
		 * Initialize the block.
		 */
		अगर ((error = xfs_dir3_data_init(args, use_block, &dbp))) अणु
			xfs_trans_brअन्यथा(tp, lbp);
			वापस error;
		पूर्ण
		/*
		 * If we're adding a new data block on the end we need to
		 * extend the bests table.  Copy it up one entry.
		 */
		अगर (use_block >= be32_to_cpu(ltp->bestcount)) अणु
			bestsp--;
			स_हटाओ(&bestsp[0], &bestsp[1],
				be32_to_cpu(ltp->bestcount) * माप(bestsp[0]));
			be32_add_cpu(&ltp->bestcount, 1);
			xfs_dir3_leaf_log_tail(args, lbp);
			xfs_dir3_leaf_log_bests(args, lbp, 0,
						be32_to_cpu(ltp->bestcount) - 1);
		पूर्ण
		/*
		 * If we're filling in a previously empty block just log it.
		 */
		अन्यथा
			xfs_dir3_leaf_log_bests(args, lbp, use_block, use_block);
		hdr = dbp->b_addr;
		bf = xfs_dir2_data_bestमुक्त_p(dp->i_mount, hdr);
		bestsp[use_block] = bf[0].length;
		grown = 1;
	पूर्ण अन्यथा अणु
		/*
		 * Alपढ़ोy had space in some data block.
		 * Just पढ़ो that one in.
		 */
		error = xfs_dir3_data_पढ़ो(tp, dp,
				   xfs_dir2_db_to_da(args->geo, use_block),
				   0, &dbp);
		अगर (error) अणु
			xfs_trans_brअन्यथा(tp, lbp);
			वापस error;
		पूर्ण
		hdr = dbp->b_addr;
		bf = xfs_dir2_data_bestमुक्त_p(dp->i_mount, hdr);
		grown = 0;
	पूर्ण
	/*
	 * Poपूर्णांक to the biggest मुक्तspace in our data block.
	 */
	dup = (xfs_dir2_data_unused_t *)
	      ((अक्षर *)hdr + be16_to_cpu(bf[0].offset));
	needscan = needlog = 0;
	/*
	 * Mark the initial part of our मुक्तspace in use क्रम the new entry.
	 */
	error = xfs_dir2_data_use_मुक्त(args, dbp, dup,
			(xfs_dir2_data_aoff_t)((अक्षर *)dup - (अक्षर *)hdr),
			length, &needlog, &needscan);
	अगर (error) अणु
		xfs_trans_brअन्यथा(tp, lbp);
		वापस error;
	पूर्ण
	/*
	 * Initialize our new entry (at last).
	 */
	dep = (xfs_dir2_data_entry_t *)dup;
	dep->inumber = cpu_to_be64(args->inumber);
	dep->namelen = args->namelen;
	स_नकल(dep->name, args->name, dep->namelen);
	xfs_dir2_data_put_ftype(dp->i_mount, dep, args->filetype);
	tagp = xfs_dir2_data_entry_tag_p(dp->i_mount, dep);
	*tagp = cpu_to_be16((अक्षर *)dep - (अक्षर *)hdr);
	/*
	 * Need to scan fix up the bestमुक्त table.
	 */
	अगर (needscan)
		xfs_dir2_data_मुक्तscan(dp->i_mount, hdr, &needlog);
	/*
	 * Need to log the data block's header.
	 */
	अगर (needlog)
		xfs_dir2_data_log_header(args, dbp);
	xfs_dir2_data_log_entry(args, dbp, dep);
	/*
	 * If the bests table needs to be changed, करो it.
	 * Log the change unless we've alपढ़ोy करोne that.
	 */
	अगर (be16_to_cpu(bestsp[use_block]) != be16_to_cpu(bf[0].length)) अणु
		bestsp[use_block] = bf[0].length;
		अगर (!grown)
			xfs_dir3_leaf_log_bests(args, lbp, use_block, use_block);
	पूर्ण

	lep = xfs_dir3_leaf_find_entry(&leafhdr, ents, index, compact, lowstale,
				       highstale, &lfloglow, &lfloghigh);

	/*
	 * Fill in the new leaf entry.
	 */
	lep->hashval = cpu_to_be32(args->hashval);
	lep->address = cpu_to_be32(
				xfs_dir2_db_off_to_dataptr(args->geo, use_block,
				be16_to_cpu(*tagp)));
	/*
	 * Log the leaf fields and give up the buffers.
	 */
	xfs_dir2_leaf_hdr_to_disk(dp->i_mount, leaf, &leafhdr);
	xfs_dir3_leaf_log_header(args, lbp);
	xfs_dir3_leaf_log_ents(args, &leafhdr, lbp, lfloglow, lfloghigh);
	xfs_dir3_leaf_check(dp, lbp);
	xfs_dir3_data_check(dp, dbp);
	वापस 0;
पूर्ण

/*
 * Compact out any stale entries in the leaf.
 * Log the header and changed leaf entries, अगर any.
 */
व्योम
xfs_dir3_leaf_compact(
	xfs_da_args_t	*args,		/* operation arguments */
	काष्ठा xfs_dir3_icleaf_hdr *leafhdr,
	काष्ठा xfs_buf	*bp)		/* leaf buffer */
अणु
	पूर्णांक		from;		/* source leaf index */
	xfs_dir2_leaf_t	*leaf;		/* leaf काष्ठाure */
	पूर्णांक		loglow;		/* first leaf entry to log */
	पूर्णांक		to;		/* target leaf index */
	काष्ठा xfs_inode *dp = args->dp;

	leaf = bp->b_addr;
	अगर (!leafhdr->stale)
		वापस;

	/*
	 * Compress out the stale entries in place.
	 */
	क्रम (from = to = 0, loglow = -1; from < leafhdr->count; from++) अणु
		अगर (leafhdr->ents[from].address ==
		    cpu_to_be32(XFS_सूची2_शून्य_DATAPTR))
			जारी;
		/*
		 * Only actually copy the entries that are dअगरferent.
		 */
		अगर (from > to) अणु
			अगर (loglow == -1)
				loglow = to;
			leafhdr->ents[to] = leafhdr->ents[from];
		पूर्ण
		to++;
	पूर्ण
	/*
	 * Update and log the header, log the leaf entries.
	 */
	ASSERT(leafhdr->stale == from - to);
	leafhdr->count -= leafhdr->stale;
	leafhdr->stale = 0;

	xfs_dir2_leaf_hdr_to_disk(dp->i_mount, leaf, leafhdr);
	xfs_dir3_leaf_log_header(args, bp);
	अगर (loglow != -1)
		xfs_dir3_leaf_log_ents(args, leafhdr, bp, loglow, to - 1);
पूर्ण

/*
 * Compact the leaf entries, removing stale ones.
 * Leave one stale entry behind - the one बंदst to our
 * insertion index - and the caller will shअगरt that one to our insertion
 * poपूर्णांक later.
 * Return new insertion index, where the reमुख्यing stale entry is,
 * and leaf logging indices.
 */
व्योम
xfs_dir3_leaf_compact_x1(
	काष्ठा xfs_dir3_icleaf_hdr *leafhdr,
	काष्ठा xfs_dir2_leaf_entry *ents,
	पूर्णांक		*indexp,	/* insertion index */
	पूर्णांक		*lowstalep,	/* out: stale entry beक्रमe us */
	पूर्णांक		*highstalep,	/* out: stale entry after us */
	पूर्णांक		*lowlogp,	/* out: low log index */
	पूर्णांक		*highlogp)	/* out: high log index */
अणु
	पूर्णांक		from;		/* source copy index */
	पूर्णांक		highstale;	/* stale entry at/after index */
	पूर्णांक		index;		/* insertion index */
	पूर्णांक		keepstale;	/* source index of kept stale */
	पूर्णांक		lowstale;	/* stale entry beक्रमe index */
	पूर्णांक		newindex=0;	/* new insertion index */
	पूर्णांक		to;		/* destination copy index */

	ASSERT(leafhdr->stale > 1);
	index = *indexp;

	xfs_dir3_leaf_find_stale(leafhdr, ents, index, &lowstale, &highstale);

	/*
	 * Pick the better of lowstale and highstale.
	 */
	अगर (lowstale >= 0 &&
	    (highstale == leafhdr->count ||
	     index - lowstale <= highstale - index))
		keepstale = lowstale;
	अन्यथा
		keepstale = highstale;
	/*
	 * Copy the entries in place, removing all the stale entries
	 * except keepstale.
	 */
	क्रम (from = to = 0; from < leafhdr->count; from++) अणु
		/*
		 * Notice the new value of index.
		 */
		अगर (index == from)
			newindex = to;
		अगर (from != keepstale &&
		    ents[from].address == cpu_to_be32(XFS_सूची2_शून्य_DATAPTR)) अणु
			अगर (from == to)
				*lowlogp = to;
			जारी;
		पूर्ण
		/*
		 * Record the new keepstale value क्रम the insertion.
		 */
		अगर (from == keepstale)
			lowstale = highstale = to;
		/*
		 * Copy only the entries that have moved.
		 */
		अगर (from > to)
			ents[to] = ents[from];
		to++;
	पूर्ण
	ASSERT(from > to);
	/*
	 * If the insertion poपूर्णांक was past the last entry,
	 * set the new insertion poपूर्णांक accordingly.
	 */
	अगर (index == from)
		newindex = to;
	*indexp = newindex;
	/*
	 * Adjust the leaf header values.
	 */
	leafhdr->count -= from - to;
	leafhdr->stale = 1;
	/*
	 * Remember the low/high stale value only in the "right"
	 * direction.
	 */
	अगर (lowstale >= newindex)
		lowstale = -1;
	अन्यथा
		highstale = leafhdr->count;
	*highlogp = leafhdr->count - 1;
	*lowstalep = lowstale;
	*highstalep = highstale;
पूर्ण

/*
 * Log the bests entries indicated from a leaf1 block.
 */
अटल व्योम
xfs_dir3_leaf_log_bests(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_buf		*bp,		/* leaf buffer */
	पूर्णांक			first,		/* first entry to log */
	पूर्णांक			last)		/* last entry to log */
अणु
	__be16			*firstb;	/* poपूर्णांकer to first entry */
	__be16			*lastb;		/* poपूर्णांकer to last entry */
	काष्ठा xfs_dir2_leaf	*leaf = bp->b_addr;
	xfs_dir2_leaf_tail_t	*ltp;		/* leaf tail काष्ठाure */

	ASSERT(leaf->hdr.info.magic == cpu_to_be16(XFS_सूची2_LEAF1_MAGIC) ||
	       leaf->hdr.info.magic == cpu_to_be16(XFS_सूची3_LEAF1_MAGIC));

	ltp = xfs_dir2_leaf_tail_p(args->geo, leaf);
	firstb = xfs_dir2_leaf_bests_p(ltp) + first;
	lastb = xfs_dir2_leaf_bests_p(ltp) + last;
	xfs_trans_log_buf(args->trans, bp,
		(uपूर्णांक)((अक्षर *)firstb - (अक्षर *)leaf),
		(uपूर्णांक)((अक्षर *)lastb - (अक्षर *)leaf + माप(*lastb) - 1));
पूर्ण

/*
 * Log the leaf entries indicated from a leaf1 or leafn block.
 */
व्योम
xfs_dir3_leaf_log_ents(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_dir3_icleaf_hdr *hdr,
	काष्ठा xfs_buf		*bp,
	पूर्णांक			first,
	पूर्णांक			last)
अणु
	xfs_dir2_leaf_entry_t	*firstlep;	/* poपूर्णांकer to first entry */
	xfs_dir2_leaf_entry_t	*lastlep;	/* poपूर्णांकer to last entry */
	काष्ठा xfs_dir2_leaf	*leaf = bp->b_addr;

	ASSERT(leaf->hdr.info.magic == cpu_to_be16(XFS_सूची2_LEAF1_MAGIC) ||
	       leaf->hdr.info.magic == cpu_to_be16(XFS_सूची3_LEAF1_MAGIC) ||
	       leaf->hdr.info.magic == cpu_to_be16(XFS_सूची2_LEAFN_MAGIC) ||
	       leaf->hdr.info.magic == cpu_to_be16(XFS_सूची3_LEAFN_MAGIC));

	firstlep = &hdr->ents[first];
	lastlep = &hdr->ents[last];
	xfs_trans_log_buf(args->trans, bp,
		(uपूर्णांक)((अक्षर *)firstlep - (अक्षर *)leaf),
		(uपूर्णांक)((अक्षर *)lastlep - (अक्षर *)leaf + माप(*lastlep) - 1));
पूर्ण

/*
 * Log the header of the leaf1 or leafn block.
 */
व्योम
xfs_dir3_leaf_log_header(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_dir2_leaf	*leaf = bp->b_addr;

	ASSERT(leaf->hdr.info.magic == cpu_to_be16(XFS_सूची2_LEAF1_MAGIC) ||
	       leaf->hdr.info.magic == cpu_to_be16(XFS_सूची3_LEAF1_MAGIC) ||
	       leaf->hdr.info.magic == cpu_to_be16(XFS_सूची2_LEAFN_MAGIC) ||
	       leaf->hdr.info.magic == cpu_to_be16(XFS_सूची3_LEAFN_MAGIC));

	xfs_trans_log_buf(args->trans, bp,
			  (uपूर्णांक)((अक्षर *)&leaf->hdr - (अक्षर *)leaf),
			  args->geo->leaf_hdr_size - 1);
पूर्ण

/*
 * Log the tail of the leaf1 block.
 */
STATIC व्योम
xfs_dir3_leaf_log_tail(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_dir2_leaf	*leaf = bp->b_addr;
	xfs_dir2_leaf_tail_t	*ltp;		/* leaf tail काष्ठाure */

	ASSERT(leaf->hdr.info.magic == cpu_to_be16(XFS_सूची2_LEAF1_MAGIC) ||
	       leaf->hdr.info.magic == cpu_to_be16(XFS_सूची3_LEAF1_MAGIC) ||
	       leaf->hdr.info.magic == cpu_to_be16(XFS_सूची2_LEAFN_MAGIC) ||
	       leaf->hdr.info.magic == cpu_to_be16(XFS_सूची3_LEAFN_MAGIC));

	ltp = xfs_dir2_leaf_tail_p(args->geo, leaf);
	xfs_trans_log_buf(args->trans, bp, (uपूर्णांक)((अक्षर *)ltp - (अक्षर *)leaf),
		(uपूर्णांक)(args->geo->blksize - 1));
पूर्ण

/*
 * Look up the entry referred to by args in the leaf क्रमmat directory.
 * Most of the work is करोne by the xfs_dir2_leaf_lookup_पूर्णांक routine which
 * is also used by the node-क्रमmat code.
 */
पूर्णांक
xfs_dir2_leaf_lookup(
	xfs_da_args_t		*args)		/* operation arguments */
अणु
	काष्ठा xfs_buf		*dbp;		/* data block buffer */
	xfs_dir2_data_entry_t	*dep;		/* data block entry */
	xfs_inode_t		*dp;		/* incore directory inode */
	पूर्णांक			error;		/* error वापस code */
	पूर्णांक			index;		/* found entry index */
	काष्ठा xfs_buf		*lbp;		/* leaf buffer */
	xfs_dir2_leaf_entry_t	*lep;		/* leaf entry */
	xfs_trans_t		*tp;		/* transaction poपूर्णांकer */
	काष्ठा xfs_dir3_icleaf_hdr leafhdr;

	trace_xfs_dir2_leaf_lookup(args);

	/*
	 * Look up name in the leaf block, वापसing both buffers and index.
	 */
	error = xfs_dir2_leaf_lookup_पूर्णांक(args, &lbp, &index, &dbp, &leafhdr);
	अगर (error)
		वापस error;

	tp = args->trans;
	dp = args->dp;
	xfs_dir3_leaf_check(dp, lbp);

	/*
	 * Get to the leaf entry and contained data entry address.
	 */
	lep = &leafhdr.ents[index];

	/*
	 * Poपूर्णांक to the data entry.
	 */
	dep = (xfs_dir2_data_entry_t *)
	      ((अक्षर *)dbp->b_addr +
	       xfs_dir2_dataptr_to_off(args->geo, be32_to_cpu(lep->address)));
	/*
	 * Return the found inode number & CI name अगर appropriate
	 */
	args->inumber = be64_to_cpu(dep->inumber);
	args->filetype = xfs_dir2_data_get_ftype(dp->i_mount, dep);
	error = xfs_dir_cilookup_result(args, dep->name, dep->namelen);
	xfs_trans_brअन्यथा(tp, dbp);
	xfs_trans_brअन्यथा(tp, lbp);
	वापस error;
पूर्ण

/*
 * Look up name/hash in the leaf block.
 * Fill in indexp with the found index, and dbpp with the data buffer.
 * If not found dbpp will be शून्य, and ENOENT comes back.
 * lbpp will always be filled in with the leaf buffer unless there's an error.
 */
अटल पूर्णांक					/* error */
xfs_dir2_leaf_lookup_पूर्णांक(
	xfs_da_args_t		*args,		/* operation arguments */
	काष्ठा xfs_buf		**lbpp,		/* out: leaf buffer */
	पूर्णांक			*indexp,	/* out: index in leaf block */
	काष्ठा xfs_buf		**dbpp,		/* out: data buffer */
	काष्ठा xfs_dir3_icleaf_hdr *leafhdr)
अणु
	xfs_dir2_db_t		curdb = -1;	/* current data block number */
	काष्ठा xfs_buf		*dbp = शून्य;	/* data buffer */
	xfs_dir2_data_entry_t	*dep;		/* data entry */
	xfs_inode_t		*dp;		/* incore directory inode */
	पूर्णांक			error;		/* error वापस code */
	पूर्णांक			index;		/* index in leaf block */
	काष्ठा xfs_buf		*lbp;		/* leaf buffer */
	xfs_dir2_leaf_entry_t	*lep;		/* leaf entry */
	xfs_dir2_leaf_t		*leaf;		/* leaf काष्ठाure */
	xfs_mount_t		*mp;		/* fileप्रणाली mount poपूर्णांक */
	xfs_dir2_db_t		newdb;		/* new data block number */
	xfs_trans_t		*tp;		/* transaction poपूर्णांकer */
	xfs_dir2_db_t		cidb = -1;	/* हाल match data block no. */
	क्रमागत xfs_dacmp		cmp;		/* name compare result */

	dp = args->dp;
	tp = args->trans;
	mp = dp->i_mount;

	error = xfs_dir3_leaf_पढ़ो(tp, dp, args->geo->leafblk, &lbp);
	अगर (error)
		वापस error;

	*lbpp = lbp;
	leaf = lbp->b_addr;
	xfs_dir3_leaf_check(dp, lbp);
	xfs_dir2_leaf_hdr_from_disk(mp, leafhdr, leaf);

	/*
	 * Look क्रम the first leaf entry with our hash value.
	 */
	index = xfs_dir2_leaf_search_hash(args, lbp);
	/*
	 * Loop over all the entries with the right hash value
	 * looking to match the name.
	 */
	क्रम (lep = &leafhdr->ents[index];
	     index < leafhdr->count &&
			be32_to_cpu(lep->hashval) == args->hashval;
	     lep++, index++) अणु
		/*
		 * Skip over stale leaf entries.
		 */
		अगर (be32_to_cpu(lep->address) == XFS_सूची2_शून्य_DATAPTR)
			जारी;
		/*
		 * Get the new data block number.
		 */
		newdb = xfs_dir2_dataptr_to_db(args->geo,
					       be32_to_cpu(lep->address));
		/*
		 * If it's not the same as the old data block number,
		 * need to pitch the old one and पढ़ो the new one.
		 */
		अगर (newdb != curdb) अणु
			अगर (dbp)
				xfs_trans_brअन्यथा(tp, dbp);
			error = xfs_dir3_data_पढ़ो(tp, dp,
					   xfs_dir2_db_to_da(args->geo, newdb),
					   0, &dbp);
			अगर (error) अणु
				xfs_trans_brअन्यथा(tp, lbp);
				वापस error;
			पूर्ण
			curdb = newdb;
		पूर्ण
		/*
		 * Poपूर्णांक to the data entry.
		 */
		dep = (xfs_dir2_data_entry_t *)((अक्षर *)dbp->b_addr +
			xfs_dir2_dataptr_to_off(args->geo,
						be32_to_cpu(lep->address)));
		/*
		 * Compare name and अगर it's an exact match, वापस the index
		 * and buffer. If it's the first हाल-insensitive match, store
		 * the index and buffer and जारी looking क्रम an exact match.
		 */
		cmp = xfs_dir2_compname(args, dep->name, dep->namelen);
		अगर (cmp != XFS_CMP_DIFFERENT && cmp != args->cmpresult) अणु
			args->cmpresult = cmp;
			*indexp = index;
			/* हाल exact match: वापस the current buffer. */
			अगर (cmp == XFS_CMP_EXACT) अणु
				*dbpp = dbp;
				वापस 0;
			पूर्ण
			cidb = curdb;
		पूर्ण
	पूर्ण
	ASSERT(args->op_flags & XFS_DA_OP_OKNOENT);
	/*
	 * Here, we can only be करोing a lookup (not a नाम or हटाओ).
	 * If a हाल-insensitive match was found earlier, re-पढ़ो the
	 * appropriate data block अगर required and वापस it.
	 */
	अगर (args->cmpresult == XFS_CMP_CASE) अणु
		ASSERT(cidb != -1);
		अगर (cidb != curdb) अणु
			xfs_trans_brअन्यथा(tp, dbp);
			error = xfs_dir3_data_पढ़ो(tp, dp,
					   xfs_dir2_db_to_da(args->geo, cidb),
					   0, &dbp);
			अगर (error) अणु
				xfs_trans_brअन्यथा(tp, lbp);
				वापस error;
			पूर्ण
		पूर्ण
		*dbpp = dbp;
		वापस 0;
	पूर्ण
	/*
	 * No match found, वापस -ENOENT.
	 */
	ASSERT(cidb == -1);
	अगर (dbp)
		xfs_trans_brअन्यथा(tp, dbp);
	xfs_trans_brअन्यथा(tp, lbp);
	वापस -ENOENT;
पूर्ण

/*
 * Remove an entry from a leaf क्रमmat directory.
 */
पूर्णांक						/* error */
xfs_dir2_leaf_हटाओname(
	xfs_da_args_t		*args)		/* operation arguments */
अणु
	काष्ठा xfs_da_geometry	*geo = args->geo;
	__be16			*bestsp;	/* leaf block best मुक्तspace */
	xfs_dir2_data_hdr_t	*hdr;		/* data block header */
	xfs_dir2_db_t		db;		/* data block number */
	काष्ठा xfs_buf		*dbp;		/* data block buffer */
	xfs_dir2_data_entry_t	*dep;		/* data entry काष्ठाure */
	xfs_inode_t		*dp;		/* incore directory inode */
	पूर्णांक			error;		/* error वापस code */
	xfs_dir2_db_t		i;		/* temporary data block # */
	पूर्णांक			index;		/* index पूर्णांकo leaf entries */
	काष्ठा xfs_buf		*lbp;		/* leaf buffer */
	xfs_dir2_leaf_t		*leaf;		/* leaf काष्ठाure */
	xfs_dir2_leaf_entry_t	*lep;		/* leaf entry */
	xfs_dir2_leaf_tail_t	*ltp;		/* leaf tail काष्ठाure */
	पूर्णांक			needlog;	/* need to log data header */
	पूर्णांक			needscan;	/* need to rescan data मुक्तs */
	xfs_dir2_data_off_t	oldbest;	/* old value of best मुक्त */
	काष्ठा xfs_dir2_data_मुक्त *bf;		/* bestमुक्त table */
	काष्ठा xfs_dir3_icleaf_hdr leafhdr;

	trace_xfs_dir2_leaf_हटाओname(args);

	/*
	 * Lookup the leaf entry, get the leaf and data blocks पढ़ो in.
	 */
	error = xfs_dir2_leaf_lookup_पूर्णांक(args, &lbp, &index, &dbp, &leafhdr);
	अगर (error)
		वापस error;

	dp = args->dp;
	leaf = lbp->b_addr;
	hdr = dbp->b_addr;
	xfs_dir3_data_check(dp, dbp);
	bf = xfs_dir2_data_bestमुक्त_p(dp->i_mount, hdr);

	/*
	 * Poपूर्णांक to the leaf entry, use that to poपूर्णांक to the data entry.
	 */
	lep = &leafhdr.ents[index];
	db = xfs_dir2_dataptr_to_db(geo, be32_to_cpu(lep->address));
	dep = (xfs_dir2_data_entry_t *)((अक्षर *)hdr +
		xfs_dir2_dataptr_to_off(geo, be32_to_cpu(lep->address)));
	needscan = needlog = 0;
	oldbest = be16_to_cpu(bf[0].length);
	ltp = xfs_dir2_leaf_tail_p(geo, leaf);
	bestsp = xfs_dir2_leaf_bests_p(ltp);
	अगर (be16_to_cpu(bestsp[db]) != oldbest) अणु
		xfs_buf_mark_corrupt(lbp);
		वापस -EFSCORRUPTED;
	पूर्ण
	/*
	 * Mark the क्रमmer data entry unused.
	 */
	xfs_dir2_data_make_मुक्त(args, dbp,
		(xfs_dir2_data_aoff_t)((अक्षर *)dep - (अक्षर *)hdr),
		xfs_dir2_data_entsize(dp->i_mount, dep->namelen), &needlog,
		&needscan);
	/*
	 * We just mark the leaf entry stale by putting a null in it.
	 */
	leafhdr.stale++;
	xfs_dir2_leaf_hdr_to_disk(dp->i_mount, leaf, &leafhdr);
	xfs_dir3_leaf_log_header(args, lbp);

	lep->address = cpu_to_be32(XFS_सूची2_शून्य_DATAPTR);
	xfs_dir3_leaf_log_ents(args, &leafhdr, lbp, index, index);

	/*
	 * Scan the मुक्तspace in the data block again अगर necessary,
	 * log the data block header अगर necessary.
	 */
	अगर (needscan)
		xfs_dir2_data_मुक्तscan(dp->i_mount, hdr, &needlog);
	अगर (needlog)
		xfs_dir2_data_log_header(args, dbp);
	/*
	 * If the दीर्घest मुक्तspace in the data block has changed,
	 * put the new value in the bests table and log that.
	 */
	अगर (be16_to_cpu(bf[0].length) != oldbest) अणु
		bestsp[db] = bf[0].length;
		xfs_dir3_leaf_log_bests(args, lbp, db, db);
	पूर्ण
	xfs_dir3_data_check(dp, dbp);
	/*
	 * If the data block is now empty then get rid of the data block.
	 */
	अगर (be16_to_cpu(bf[0].length) ==
	    geo->blksize - geo->data_entry_offset) अणु
		ASSERT(db != geo->datablk);
		अगर ((error = xfs_dir2_shrink_inode(args, db, dbp))) अणु
			/*
			 * Nope, can't get rid of it because it caused
			 * allocation of a bmap btree block to करो so.
			 * Just go on, वापसing success, leaving the
			 * empty block in place.
			 */
			अगर (error == -ENOSPC && args->total == 0)
				error = 0;
			xfs_dir3_leaf_check(dp, lbp);
			वापस error;
		पूर्ण
		dbp = शून्य;
		/*
		 * If this is the last data block then compact the
		 * bests table by getting rid of entries.
		 */
		अगर (db == be32_to_cpu(ltp->bestcount) - 1) अणु
			/*
			 * Look क्रम the last active entry (i).
			 */
			क्रम (i = db - 1; i > 0; i--) अणु
				अगर (bestsp[i] != cpu_to_be16(शून्यDATAOFF))
					अवरोध;
			पूर्ण
			/*
			 * Copy the table करोwn so inactive entries at the
			 * end are हटाओd.
			 */
			स_हटाओ(&bestsp[db - i], bestsp,
				(be32_to_cpu(ltp->bestcount) - (db - i)) * माप(*bestsp));
			be32_add_cpu(&ltp->bestcount, -(db - i));
			xfs_dir3_leaf_log_tail(args, lbp);
			xfs_dir3_leaf_log_bests(args, lbp, 0,
						be32_to_cpu(ltp->bestcount) - 1);
		पूर्ण अन्यथा
			bestsp[db] = cpu_to_be16(शून्यDATAOFF);
	पूर्ण
	/*
	 * If the data block was not the first one, drop it.
	 */
	अन्यथा अगर (db != geo->datablk)
		dbp = शून्य;

	xfs_dir3_leaf_check(dp, lbp);
	/*
	 * See अगर we can convert to block क्रमm.
	 */
	वापस xfs_dir2_leaf_to_block(args, lbp, dbp);
पूर्ण

/*
 * Replace the inode number in a leaf क्रमmat directory entry.
 */
पूर्णांक						/* error */
xfs_dir2_leaf_replace(
	xfs_da_args_t		*args)		/* operation arguments */
अणु
	काष्ठा xfs_buf		*dbp;		/* data block buffer */
	xfs_dir2_data_entry_t	*dep;		/* data block entry */
	xfs_inode_t		*dp;		/* incore directory inode */
	पूर्णांक			error;		/* error वापस code */
	पूर्णांक			index;		/* index of leaf entry */
	काष्ठा xfs_buf		*lbp;		/* leaf buffer */
	xfs_dir2_leaf_entry_t	*lep;		/* leaf entry */
	xfs_trans_t		*tp;		/* transaction poपूर्णांकer */
	काष्ठा xfs_dir3_icleaf_hdr leafhdr;

	trace_xfs_dir2_leaf_replace(args);

	/*
	 * Look up the entry.
	 */
	error = xfs_dir2_leaf_lookup_पूर्णांक(args, &lbp, &index, &dbp, &leafhdr);
	अगर (error)
		वापस error;

	dp = args->dp;
	/*
	 * Poपूर्णांक to the leaf entry, get data address from it.
	 */
	lep = &leafhdr.ents[index];
	/*
	 * Poपूर्णांक to the data entry.
	 */
	dep = (xfs_dir2_data_entry_t *)
	      ((अक्षर *)dbp->b_addr +
	       xfs_dir2_dataptr_to_off(args->geo, be32_to_cpu(lep->address)));
	ASSERT(args->inumber != be64_to_cpu(dep->inumber));
	/*
	 * Put the new inode number in, log it.
	 */
	dep->inumber = cpu_to_be64(args->inumber);
	xfs_dir2_data_put_ftype(dp->i_mount, dep, args->filetype);
	tp = args->trans;
	xfs_dir2_data_log_entry(args, dbp, dep);
	xfs_dir3_leaf_check(dp, lbp);
	xfs_trans_brअन्यथा(tp, lbp);
	वापस 0;
पूर्ण

/*
 * Return index in the leaf block (lbp) which is either the first
 * one with this hash value, or अगर there are none, the insert poपूर्णांक
 * क्रम that hash value.
 */
पूर्णांक						/* index value */
xfs_dir2_leaf_search_hash(
	xfs_da_args_t		*args,		/* operation arguments */
	काष्ठा xfs_buf		*lbp)		/* leaf buffer */
अणु
	xfs_dahash_t		hash=0;		/* hash from this entry */
	xfs_dahash_t		hashwant;	/* hash value looking क्रम */
	पूर्णांक			high;		/* high leaf index */
	पूर्णांक			low;		/* low leaf index */
	xfs_dir2_leaf_entry_t	*lep;		/* leaf entry */
	पूर्णांक			mid=0;		/* current leaf index */
	काष्ठा xfs_dir3_icleaf_hdr leafhdr;

	xfs_dir2_leaf_hdr_from_disk(args->dp->i_mount, &leafhdr, lbp->b_addr);

	/*
	 * Note, the table cannot be empty, so we have to go through the loop.
	 * Binary search the leaf entries looking क्रम our hash value.
	 */
	क्रम (lep = leafhdr.ents, low = 0, high = leafhdr.count - 1,
		hashwant = args->hashval;
	     low <= high; ) अणु
		mid = (low + high) >> 1;
		अगर ((hash = be32_to_cpu(lep[mid].hashval)) == hashwant)
			अवरोध;
		अगर (hash < hashwant)
			low = mid + 1;
		अन्यथा
			high = mid - 1;
	पूर्ण
	/*
	 * Found one, back up through all the equal hash values.
	 */
	अगर (hash == hashwant) अणु
		जबतक (mid > 0 && be32_to_cpu(lep[mid - 1].hashval) == hashwant) अणु
			mid--;
		पूर्ण
	पूर्ण
	/*
	 * Need to poपूर्णांक to an entry higher than ours.
	 */
	अन्यथा अगर (hash < hashwant)
		mid++;
	वापस mid;
पूर्ण

/*
 * Trim off a trailing data block.  We know it's empty since the leaf
 * मुक्तspace table says so.
 */
पूर्णांक						/* error */
xfs_dir2_leaf_trim_data(
	xfs_da_args_t		*args,		/* operation arguments */
	काष्ठा xfs_buf		*lbp,		/* leaf buffer */
	xfs_dir2_db_t		db)		/* data block number */
अणु
	काष्ठा xfs_da_geometry	*geo = args->geo;
	__be16			*bestsp;	/* leaf bests table */
	काष्ठा xfs_buf		*dbp;		/* data block buffer */
	xfs_inode_t		*dp;		/* incore directory inode */
	पूर्णांक			error;		/* error वापस value */
	xfs_dir2_leaf_t		*leaf;		/* leaf काष्ठाure */
	xfs_dir2_leaf_tail_t	*ltp;		/* leaf tail काष्ठाure */
	xfs_trans_t		*tp;		/* transaction poपूर्णांकer */

	dp = args->dp;
	tp = args->trans;
	/*
	 * Read the offending data block.  We need its buffer.
	 */
	error = xfs_dir3_data_पढ़ो(tp, dp, xfs_dir2_db_to_da(geo, db), 0, &dbp);
	अगर (error)
		वापस error;

	leaf = lbp->b_addr;
	ltp = xfs_dir2_leaf_tail_p(geo, leaf);

#अगर_घोषित DEBUG
अणु
	काष्ठा xfs_dir2_data_hdr *hdr = dbp->b_addr;
	काष्ठा xfs_dir2_data_मुक्त *bf =
		xfs_dir2_data_bestमुक्त_p(dp->i_mount, hdr);

	ASSERT(hdr->magic == cpu_to_be32(XFS_सूची2_DATA_MAGIC) ||
	       hdr->magic == cpu_to_be32(XFS_सूची3_DATA_MAGIC));
	ASSERT(be16_to_cpu(bf[0].length) ==
	       geo->blksize - geo->data_entry_offset);
	ASSERT(db == be32_to_cpu(ltp->bestcount) - 1);
पूर्ण
#पूर्ण_अगर

	/*
	 * Get rid of the data block.
	 */
	अगर ((error = xfs_dir2_shrink_inode(args, db, dbp))) अणु
		ASSERT(error != -ENOSPC);
		xfs_trans_brअन्यथा(tp, dbp);
		वापस error;
	पूर्ण
	/*
	 * Eliminate the last bests entry from the table.
	 */
	bestsp = xfs_dir2_leaf_bests_p(ltp);
	be32_add_cpu(&ltp->bestcount, -1);
	स_हटाओ(&bestsp[1], &bestsp[0], be32_to_cpu(ltp->bestcount) * माप(*bestsp));
	xfs_dir3_leaf_log_tail(args, lbp);
	xfs_dir3_leaf_log_bests(args, lbp, 0, be32_to_cpu(ltp->bestcount) - 1);
	वापस 0;
पूर्ण

अटल अंतरभूत माप_प्रकार
xfs_dir3_leaf_size(
	काष्ठा xfs_dir3_icleaf_hdr	*hdr,
	पूर्णांक				counts)
अणु
	पूर्णांक	entries;
	पूर्णांक	hdrsize;

	entries = hdr->count - hdr->stale;
	अगर (hdr->magic == XFS_सूची2_LEAF1_MAGIC ||
	    hdr->magic == XFS_सूची2_LEAFN_MAGIC)
		hdrsize = माप(काष्ठा xfs_dir2_leaf_hdr);
	अन्यथा
		hdrsize = माप(काष्ठा xfs_dir3_leaf_hdr);

	वापस hdrsize + entries * माप(xfs_dir2_leaf_entry_t)
	               + counts * माप(xfs_dir2_data_off_t)
		       + माप(xfs_dir2_leaf_tail_t);
पूर्ण

/*
 * Convert node क्रमm directory to leaf क्रमm directory.
 * The root of the node क्रमm dir needs to alपढ़ोy be a LEAFN block.
 * Just वापस अगर we can't करो anything.
 */
पूर्णांक						/* error */
xfs_dir2_node_to_leaf(
	xfs_da_state_t		*state)		/* directory operation state */
अणु
	xfs_da_args_t		*args;		/* operation arguments */
	xfs_inode_t		*dp;		/* incore directory inode */
	पूर्णांक			error;		/* error वापस code */
	काष्ठा xfs_buf		*fbp;		/* buffer क्रम मुक्तspace block */
	xfs_fileoff_t		fo;		/* मुक्तspace file offset */
	काष्ठा xfs_buf		*lbp;		/* buffer क्रम leaf block */
	xfs_dir2_leaf_tail_t	*ltp;		/* tail of leaf काष्ठाure */
	xfs_dir2_leaf_t		*leaf;		/* leaf काष्ठाure */
	xfs_mount_t		*mp;		/* fileप्रणाली mount poपूर्णांक */
	पूर्णांक			rval;		/* successful मुक्त trim? */
	xfs_trans_t		*tp;		/* transaction poपूर्णांकer */
	काष्ठा xfs_dir3_icleaf_hdr leafhdr;
	काष्ठा xfs_dir3_icमुक्त_hdr मुक्तhdr;

	/*
	 * There's more than a leaf level in the btree, so there must
	 * be multiple leafn blocks.  Give up.
	 */
	अगर (state->path.active > 1)
		वापस 0;
	args = state->args;

	trace_xfs_dir2_node_to_leaf(args);

	mp = state->mp;
	dp = args->dp;
	tp = args->trans;
	/*
	 * Get the last offset in the file.
	 */
	अगर ((error = xfs_bmap_last_offset(dp, &fo, XFS_DATA_FORK))) अणु
		वापस error;
	पूर्ण
	fo -= args->geo->fsbcount;
	/*
	 * If there are मुक्तspace blocks other than the first one,
	 * take this opportunity to हटाओ trailing empty मुक्तspace blocks
	 * that may have been left behind during no-space-reservation
	 * operations.
	 */
	जबतक (fo > args->geo->मुक्तblk) अणु
		अगर ((error = xfs_dir2_node_trim_मुक्त(args, fo, &rval))) अणु
			वापस error;
		पूर्ण
		अगर (rval)
			fo -= args->geo->fsbcount;
		अन्यथा
			वापस 0;
	पूर्ण
	/*
	 * Now find the block just beक्रमe the मुक्तspace block.
	 */
	अगर ((error = xfs_bmap_last_beक्रमe(tp, dp, &fo, XFS_DATA_FORK))) अणु
		वापस error;
	पूर्ण
	/*
	 * If it's not the single leaf block, give up.
	 */
	अगर (XFS_FSB_TO_B(mp, fo) > XFS_सूची2_LEAF_OFFSET + args->geo->blksize)
		वापस 0;
	lbp = state->path.blk[0].bp;
	leaf = lbp->b_addr;
	xfs_dir2_leaf_hdr_from_disk(mp, &leafhdr, leaf);

	ASSERT(leafhdr.magic == XFS_सूची2_LEAFN_MAGIC ||
	       leafhdr.magic == XFS_सूची3_LEAFN_MAGIC);

	/*
	 * Read the मुक्तspace block.
	 */
	error = xfs_dir2_मुक्त_पढ़ो(tp, dp,  args->geo->मुक्तblk, &fbp);
	अगर (error)
		वापस error;
	xfs_dir2_मुक्त_hdr_from_disk(mp, &मुक्तhdr, fbp->b_addr);

	ASSERT(!मुक्तhdr.firstdb);

	/*
	 * Now see अगर the leafn and मुक्त data will fit in a leaf1.
	 * If not, release the buffer and give up.
	 */
	अगर (xfs_dir3_leaf_size(&leafhdr, मुक्तhdr.nvalid) > args->geo->blksize) अणु
		xfs_trans_brअन्यथा(tp, fbp);
		वापस 0;
	पूर्ण

	/*
	 * If the leaf has any stale entries in it, compress them out.
	 */
	अगर (leafhdr.stale)
		xfs_dir3_leaf_compact(args, &leafhdr, lbp);

	lbp->b_ops = &xfs_dir3_leaf1_buf_ops;
	xfs_trans_buf_set_type(tp, lbp, XFS_BLFT_सूची_LEAF1_BUF);
	leafhdr.magic = (leafhdr.magic == XFS_सूची2_LEAFN_MAGIC)
					? XFS_सूची2_LEAF1_MAGIC
					: XFS_सूची3_LEAF1_MAGIC;

	/*
	 * Set up the leaf tail from the मुक्तspace block.
	 */
	ltp = xfs_dir2_leaf_tail_p(args->geo, leaf);
	ltp->bestcount = cpu_to_be32(मुक्तhdr.nvalid);

	/*
	 * Set up the leaf bests table.
	 */
	स_नकल(xfs_dir2_leaf_bests_p(ltp), मुक्तhdr.bests,
		मुक्तhdr.nvalid * माप(xfs_dir2_data_off_t));

	xfs_dir2_leaf_hdr_to_disk(mp, leaf, &leafhdr);
	xfs_dir3_leaf_log_header(args, lbp);
	xfs_dir3_leaf_log_bests(args, lbp, 0, be32_to_cpu(ltp->bestcount) - 1);
	xfs_dir3_leaf_log_tail(args, lbp);
	xfs_dir3_leaf_check(dp, lbp);

	/*
	 * Get rid of the मुक्तspace block.
	 */
	error = xfs_dir2_shrink_inode(args,
			xfs_dir2_byte_to_db(args->geo, XFS_सूची2_FREE_OFFSET),
			fbp);
	अगर (error) अणु
		/*
		 * This can't fail here because it can only happen when
		 * punching out the middle of an extent, and this is an
		 * isolated block.
		 */
		ASSERT(error != -ENOSPC);
		वापस error;
	पूर्ण
	fbp = शून्य;
	/*
	 * Now see अगर we can convert the single-leaf directory
	 * करोwn to a block क्रमm directory.
	 * This routine always समाप्तs the dabuf क्रम the leaf, so
	 * eliminate it from the path.
	 */
	error = xfs_dir2_leaf_to_block(args, lbp, शून्य);
	state->path.blk[0].bp = शून्य;
	वापस error;
पूर्ण
