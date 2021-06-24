<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
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
#समावेश "xfs_log.h"

/*
 * Function declarations.
 */
अटल पूर्णांक xfs_dir2_leafn_add(काष्ठा xfs_buf *bp, xfs_da_args_t *args,
			      पूर्णांक index);
अटल व्योम xfs_dir2_leafn_rebalance(xfs_da_state_t *state,
				     xfs_da_state_blk_t *blk1,
				     xfs_da_state_blk_t *blk2);
अटल पूर्णांक xfs_dir2_leafn_हटाओ(xfs_da_args_t *args, काष्ठा xfs_buf *bp,
				 पूर्णांक index, xfs_da_state_blk_t *dblk,
				 पूर्णांक *rval);

/*
 * Convert data space db to the corresponding मुक्त db.
 */
अटल xfs_dir2_db_t
xfs_dir2_db_to_fdb(काष्ठा xfs_da_geometry *geo, xfs_dir2_db_t db)
अणु
	वापस xfs_dir2_byte_to_db(geo, XFS_सूची2_FREE_OFFSET) +
			(db / geo->मुक्त_max_bests);
पूर्ण

/*
 * Convert data space db to the corresponding index in a मुक्त db.
 */
अटल पूर्णांक
xfs_dir2_db_to_fdindex(काष्ठा xfs_da_geometry *geo, xfs_dir2_db_t db)
अणु
	वापस db % geo->मुक्त_max_bests;
पूर्ण

/*
 * Check पूर्णांकernal consistency of a leafn block.
 */
#अगर_घोषित DEBUG
अटल xfs_failaddr_t
xfs_dir3_leafn_check(
	काष्ठा xfs_inode	*dp,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_dir2_leaf	*leaf = bp->b_addr;
	काष्ठा xfs_dir3_icleaf_hdr leafhdr;

	xfs_dir2_leaf_hdr_from_disk(dp->i_mount, &leafhdr, leaf);

	अगर (leafhdr.magic == XFS_सूची3_LEAFN_MAGIC) अणु
		काष्ठा xfs_dir3_leaf_hdr *leaf3 = bp->b_addr;
		अगर (be64_to_cpu(leaf3->info.blkno) != bp->b_bn)
			वापस __this_address;
	पूर्ण अन्यथा अगर (leafhdr.magic != XFS_सूची2_LEAFN_MAGIC)
		वापस __this_address;

	वापस xfs_dir3_leaf_check_पूर्णांक(dp->i_mount, &leafhdr, leaf, false);
पूर्ण

अटल अंतरभूत व्योम
xfs_dir3_leaf_check(
	काष्ठा xfs_inode	*dp,
	काष्ठा xfs_buf		*bp)
अणु
	xfs_failaddr_t		fa;

	fa = xfs_dir3_leafn_check(dp, bp);
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

अटल xfs_failaddr_t
xfs_dir3_मुक्त_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_dir2_मुक्त_hdr *hdr = bp->b_addr;

	अगर (!xfs_verअगरy_magic(bp, hdr->magic))
		वापस __this_address;

	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		काष्ठा xfs_dir3_blk_hdr *hdr3 = bp->b_addr;

		अगर (!uuid_equal(&hdr3->uuid, &mp->m_sb.sb_meta_uuid))
			वापस __this_address;
		अगर (be64_to_cpu(hdr3->blkno) != bp->b_bn)
			वापस __this_address;
		अगर (!xfs_log_check_lsn(mp, be64_to_cpu(hdr3->lsn)))
			वापस __this_address;
	पूर्ण

	/* XXX: should bounds check the xfs_dir3_icमुक्त_hdr here */

	वापस शून्य;
पूर्ण

अटल व्योम
xfs_dir3_मुक्त_पढ़ो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	xfs_failaddr_t		fa;

	अगर (xfs_sb_version_hascrc(&mp->m_sb) &&
	    !xfs_buf_verअगरy_cksum(bp, XFS_सूची3_FREE_CRC_OFF))
		xfs_verअगरier_error(bp, -EFSBADCRC, __this_address);
	अन्यथा अणु
		fa = xfs_dir3_मुक्त_verअगरy(bp);
		अगर (fa)
			xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
	पूर्ण
पूर्ण

अटल व्योम
xfs_dir3_मुक्त_ग_लिखो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;
	काष्ठा xfs_dir3_blk_hdr	*hdr3 = bp->b_addr;
	xfs_failaddr_t		fa;

	fa = xfs_dir3_मुक्त_verअगरy(bp);
	अगर (fa) अणु
		xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
		वापस;
	पूर्ण

	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस;

	अगर (bip)
		hdr3->lsn = cpu_to_be64(bip->bli_item.li_lsn);

	xfs_buf_update_cksum(bp, XFS_सूची3_FREE_CRC_OFF);
पूर्ण

स्थिर काष्ठा xfs_buf_ops xfs_dir3_मुक्त_buf_ops = अणु
	.name = "xfs_dir3_free",
	.magic = अणु cpu_to_be32(XFS_सूची2_FREE_MAGIC),
		   cpu_to_be32(XFS_सूची3_FREE_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_dir3_मुक्त_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_dir3_मुक्त_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा = xfs_dir3_मुक्त_verअगरy,
पूर्ण;

/* Everything ok in the मुक्त block header? */
अटल xfs_failaddr_t
xfs_dir3_मुक्त_header_check(
	काष्ठा xfs_inode	*dp,
	xfs_dablk_t		fbno,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = dp->i_mount;
	पूर्णांक			maxbests = mp->m_dir_geo->मुक्त_max_bests;
	अचिन्हित पूर्णांक		firstdb;

	firstdb = (xfs_dir2_da_to_db(mp->m_dir_geo, fbno) -
		   xfs_dir2_byte_to_db(mp->m_dir_geo, XFS_सूची2_FREE_OFFSET)) *
			maxbests;
	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		काष्ठा xfs_dir3_मुक्त_hdr *hdr3 = bp->b_addr;

		अगर (be32_to_cpu(hdr3->firstdb) != firstdb)
			वापस __this_address;
		अगर (be32_to_cpu(hdr3->nvalid) > maxbests)
			वापस __this_address;
		अगर (be32_to_cpu(hdr3->nvalid) < be32_to_cpu(hdr3->nused))
			वापस __this_address;
		अगर (be64_to_cpu(hdr3->hdr.owner) != dp->i_ino)
			वापस __this_address;
	पूर्ण अन्यथा अणु
		काष्ठा xfs_dir2_मुक्त_hdr *hdr = bp->b_addr;

		अगर (be32_to_cpu(hdr->firstdb) != firstdb)
			वापस __this_address;
		अगर (be32_to_cpu(hdr->nvalid) > maxbests)
			वापस __this_address;
		अगर (be32_to_cpu(hdr->nvalid) < be32_to_cpu(hdr->nused))
			वापस __this_address;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक
__xfs_dir3_मुक्त_पढ़ो(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*dp,
	xfs_dablk_t		fbno,
	अचिन्हित पूर्णांक		flags,
	काष्ठा xfs_buf		**bpp)
अणु
	xfs_failaddr_t		fa;
	पूर्णांक			err;

	err = xfs_da_पढ़ो_buf(tp, dp, fbno, flags, bpp, XFS_DATA_FORK,
			&xfs_dir3_मुक्त_buf_ops);
	अगर (err || !*bpp)
		वापस err;

	/* Check things that we can't करो in the verअगरier. */
	fa = xfs_dir3_मुक्त_header_check(dp, fbno, *bpp);
	अगर (fa) अणु
		__xfs_buf_mark_corrupt(*bpp, fa);
		xfs_trans_brअन्यथा(tp, *bpp);
		*bpp = शून्य;
		वापस -EFSCORRUPTED;
	पूर्ण

	/* try पढ़ो वापसs without an error or *bpp अगर it lands in a hole */
	अगर (tp)
		xfs_trans_buf_set_type(tp, *bpp, XFS_BLFT_सूची_FREE_BUF);

	वापस 0;
पूर्ण

व्योम
xfs_dir2_मुक्त_hdr_from_disk(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_dir3_icमुक्त_hdr	*to,
	काष्ठा xfs_dir2_मुक्त		*from)
अणु
	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		काष्ठा xfs_dir3_मुक्त	*from3 = (काष्ठा xfs_dir3_मुक्त *)from;

		to->magic = be32_to_cpu(from3->hdr.hdr.magic);
		to->firstdb = be32_to_cpu(from3->hdr.firstdb);
		to->nvalid = be32_to_cpu(from3->hdr.nvalid);
		to->nused = be32_to_cpu(from3->hdr.nused);
		to->bests = from3->bests;

		ASSERT(to->magic == XFS_सूची3_FREE_MAGIC);
	पूर्ण अन्यथा अणु
		to->magic = be32_to_cpu(from->hdr.magic);
		to->firstdb = be32_to_cpu(from->hdr.firstdb);
		to->nvalid = be32_to_cpu(from->hdr.nvalid);
		to->nused = be32_to_cpu(from->hdr.nused);
		to->bests = from->bests;

		ASSERT(to->magic == XFS_सूची2_FREE_MAGIC);
	पूर्ण
पूर्ण

अटल व्योम
xfs_dir2_मुक्त_hdr_to_disk(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_dir2_मुक्त		*to,
	काष्ठा xfs_dir3_icमुक्त_hdr	*from)
अणु
	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		काष्ठा xfs_dir3_मुक्त	*to3 = (काष्ठा xfs_dir3_मुक्त *)to;

		ASSERT(from->magic == XFS_सूची3_FREE_MAGIC);

		to3->hdr.hdr.magic = cpu_to_be32(from->magic);
		to3->hdr.firstdb = cpu_to_be32(from->firstdb);
		to3->hdr.nvalid = cpu_to_be32(from->nvalid);
		to3->hdr.nused = cpu_to_be32(from->nused);
	पूर्ण अन्यथा अणु
		ASSERT(from->magic == XFS_सूची2_FREE_MAGIC);

		to->hdr.magic = cpu_to_be32(from->magic);
		to->hdr.firstdb = cpu_to_be32(from->firstdb);
		to->hdr.nvalid = cpu_to_be32(from->nvalid);
		to->hdr.nused = cpu_to_be32(from->nused);
	पूर्ण
पूर्ण

पूर्णांक
xfs_dir2_मुक्त_पढ़ो(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*dp,
	xfs_dablk_t		fbno,
	काष्ठा xfs_buf		**bpp)
अणु
	वापस __xfs_dir3_मुक्त_पढ़ो(tp, dp, fbno, 0, bpp);
पूर्ण

अटल पूर्णांक
xfs_dir2_मुक्त_try_पढ़ो(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*dp,
	xfs_dablk_t		fbno,
	काष्ठा xfs_buf		**bpp)
अणु
	वापस __xfs_dir3_मुक्त_पढ़ो(tp, dp, fbno, XFS_DABUF_MAP_HOLE_OK, bpp);
पूर्ण

अटल पूर्णांक
xfs_dir3_मुक्त_get_buf(
	xfs_da_args_t		*args,
	xfs_dir2_db_t		fbno,
	काष्ठा xfs_buf		**bpp)
अणु
	काष्ठा xfs_trans	*tp = args->trans;
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;
	काष्ठा xfs_dir3_icमुक्त_hdr hdr;

	error = xfs_da_get_buf(tp, dp, xfs_dir2_db_to_da(args->geo, fbno),
			&bp, XFS_DATA_FORK);
	अगर (error)
		वापस error;

	xfs_trans_buf_set_type(tp, bp, XFS_BLFT_सूची_FREE_BUF);
	bp->b_ops = &xfs_dir3_मुक्त_buf_ops;

	/*
	 * Initialize the new block to be empty, and remember
	 * its first slot as our empty slot.
	 */
	स_रखो(bp->b_addr, 0, माप(काष्ठा xfs_dir3_मुक्त_hdr));
	स_रखो(&hdr, 0, माप(hdr));

	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		काष्ठा xfs_dir3_मुक्त_hdr *hdr3 = bp->b_addr;

		hdr.magic = XFS_सूची3_FREE_MAGIC;

		hdr3->hdr.blkno = cpu_to_be64(bp->b_bn);
		hdr3->hdr.owner = cpu_to_be64(dp->i_ino);
		uuid_copy(&hdr3->hdr.uuid, &mp->m_sb.sb_meta_uuid);
	पूर्ण अन्यथा
		hdr.magic = XFS_सूची2_FREE_MAGIC;
	xfs_dir2_मुक्त_hdr_to_disk(mp, bp->b_addr, &hdr);
	*bpp = bp;
	वापस 0;
पूर्ण

/*
 * Log entries from a मुक्तspace block.
 */
STATIC व्योम
xfs_dir2_मुक्त_log_bests(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_dir3_icमुक्त_hdr *hdr,
	काष्ठा xfs_buf		*bp,
	पूर्णांक			first,		/* first entry to log */
	पूर्णांक			last)		/* last entry to log */
अणु
	काष्ठा xfs_dir2_मुक्त	*मुक्त = bp->b_addr;

	ASSERT(मुक्त->hdr.magic == cpu_to_be32(XFS_सूची2_FREE_MAGIC) ||
	       मुक्त->hdr.magic == cpu_to_be32(XFS_सूची3_FREE_MAGIC));
	xfs_trans_log_buf(args->trans, bp,
			  (अक्षर *)&hdr->bests[first] - (अक्षर *)मुक्त,
			  (अक्षर *)&hdr->bests[last] - (अक्षर *)मुक्त +
			   माप(hdr->bests[0]) - 1);
पूर्ण

/*
 * Log header from a मुक्तspace block.
 */
अटल व्योम
xfs_dir2_मुक्त_log_header(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_buf		*bp)
अणु
#अगर_घोषित DEBUG
	xfs_dir2_मुक्त_t		*मुक्त;		/* मुक्तspace काष्ठाure */

	मुक्त = bp->b_addr;
	ASSERT(मुक्त->hdr.magic == cpu_to_be32(XFS_सूची2_FREE_MAGIC) ||
	       मुक्त->hdr.magic == cpu_to_be32(XFS_सूची3_FREE_MAGIC));
#पूर्ण_अगर
	xfs_trans_log_buf(args->trans, bp, 0,
			  args->geo->मुक्त_hdr_size - 1);
पूर्ण

/*
 * Convert a leaf-क्रमmat directory to a node-क्रमmat directory.
 * We need to change the magic number of the leaf block, and copy
 * the मुक्तspace table out of the leaf block पूर्णांकo its own block.
 */
पूर्णांक						/* error */
xfs_dir2_leaf_to_node(
	xfs_da_args_t		*args,		/* operation arguments */
	काष्ठा xfs_buf		*lbp)		/* leaf buffer */
अणु
	xfs_inode_t		*dp;		/* incore directory inode */
	पूर्णांक			error;		/* error वापस value */
	काष्ठा xfs_buf		*fbp;		/* मुक्तspace buffer */
	xfs_dir2_db_t		fdb;		/* मुक्तspace block number */
	__be16			*from;		/* poपूर्णांकer to मुक्तspace entry */
	पूर्णांक			i;		/* leaf मुक्तspace index */
	xfs_dir2_leaf_t		*leaf;		/* leaf काष्ठाure */
	xfs_dir2_leaf_tail_t	*ltp;		/* leaf tail काष्ठाure */
	पूर्णांक			n;		/* count of live मुक्तspc ents */
	xfs_dir2_data_off_t	off;		/* मुक्तspace entry value */
	xfs_trans_t		*tp;		/* transaction poपूर्णांकer */
	काष्ठा xfs_dir3_icमुक्त_hdr मुक्तhdr;

	trace_xfs_dir2_leaf_to_node(args);

	dp = args->dp;
	tp = args->trans;
	/*
	 * Add a मुक्तspace block to the directory.
	 */
	अगर ((error = xfs_dir2_grow_inode(args, XFS_सूची2_FREE_SPACE, &fdb))) अणु
		वापस error;
	पूर्ण
	ASSERT(fdb == xfs_dir2_byte_to_db(args->geo, XFS_सूची2_FREE_OFFSET));
	/*
	 * Get the buffer क्रम the new मुक्तspace block.
	 */
	error = xfs_dir3_मुक्त_get_buf(args, fdb, &fbp);
	अगर (error)
		वापस error;

	xfs_dir2_मुक्त_hdr_from_disk(dp->i_mount, &मुक्तhdr, fbp->b_addr);
	leaf = lbp->b_addr;
	ltp = xfs_dir2_leaf_tail_p(args->geo, leaf);
	अगर (be32_to_cpu(ltp->bestcount) >
				(uपूर्णांक)dp->i_disk_size / args->geo->blksize) अणु
		xfs_buf_mark_corrupt(lbp);
		वापस -EFSCORRUPTED;
	पूर्ण

	/*
	 * Copy मुक्तspace entries from the leaf block to the new block.
	 * Count active entries.
	 */
	from = xfs_dir2_leaf_bests_p(ltp);
	क्रम (i = n = 0; i < be32_to_cpu(ltp->bestcount); i++, from++) अणु
		off = be16_to_cpu(*from);
		अगर (off != शून्यDATAOFF)
			n++;
		मुक्तhdr.bests[i] = cpu_to_be16(off);
	पूर्ण

	/*
	 * Now initialize the मुक्तspace block header.
	 */
	मुक्तhdr.nused = n;
	मुक्तhdr.nvalid = be32_to_cpu(ltp->bestcount);

	xfs_dir2_मुक्त_hdr_to_disk(dp->i_mount, fbp->b_addr, &मुक्तhdr);
	xfs_dir2_मुक्त_log_bests(args, &मुक्तhdr, fbp, 0, मुक्तhdr.nvalid - 1);
	xfs_dir2_मुक्त_log_header(args, fbp);

	/*
	 * Converting the leaf to a leafnode is just a matter of changing the
	 * magic number and the ops. Do the change directly to the buffer as
	 * it's less work (and less code) than decoding the header to host
	 * क्रमmat and back again.
	 */
	अगर (leaf->hdr.info.magic == cpu_to_be16(XFS_सूची2_LEAF1_MAGIC))
		leaf->hdr.info.magic = cpu_to_be16(XFS_सूची2_LEAFN_MAGIC);
	अन्यथा
		leaf->hdr.info.magic = cpu_to_be16(XFS_सूची3_LEAFN_MAGIC);
	lbp->b_ops = &xfs_dir3_leafn_buf_ops;
	xfs_trans_buf_set_type(tp, lbp, XFS_BLFT_सूची_LEAFN_BUF);
	xfs_dir3_leaf_log_header(args, lbp);
	xfs_dir3_leaf_check(dp, lbp);
	वापस 0;
पूर्ण

/*
 * Add a leaf entry to a leaf block in a node-क्रमm directory.
 * The other work necessary is करोne from the caller.
 */
अटल पूर्णांक					/* error */
xfs_dir2_leafn_add(
	काष्ठा xfs_buf		*bp,		/* leaf buffer */
	काष्ठा xfs_da_args	*args,		/* operation arguments */
	पूर्णांक			index)		/* insertion pt क्रम new entry */
अणु
	काष्ठा xfs_dir3_icleaf_hdr leafhdr;
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_dir2_leaf	*leaf = bp->b_addr;
	काष्ठा xfs_dir2_leaf_entry *lep;
	काष्ठा xfs_dir2_leaf_entry *ents;
	पूर्णांक			compact;	/* compacting stale leaves */
	पूर्णांक			highstale = 0;	/* next stale entry */
	पूर्णांक			lfloghigh;	/* high leaf entry logging */
	पूर्णांक			lfloglow;	/* low leaf entry logging */
	पूर्णांक			lowstale = 0;	/* previous stale entry */

	trace_xfs_dir2_leafn_add(args, index);

	xfs_dir2_leaf_hdr_from_disk(dp->i_mount, &leafhdr, leaf);
	ents = leafhdr.ents;

	/*
	 * Quick check just to make sure we are not going to index
	 * पूर्णांकo other peoples memory
	 */
	अगर (index < 0) अणु
		xfs_buf_mark_corrupt(bp);
		वापस -EFSCORRUPTED;
	पूर्ण

	/*
	 * If there are alपढ़ोy the maximum number of leaf entries in
	 * the block, अगर there are no stale entries it won't fit.
	 * Caller will करो a split.  If there are stale entries we'll करो
	 * a compact.
	 */

	अगर (leafhdr.count == args->geo->leaf_max_ents) अणु
		अगर (!leafhdr.stale)
			वापस -ENOSPC;
		compact = leafhdr.stale > 1;
	पूर्ण अन्यथा
		compact = 0;
	ASSERT(index == 0 || be32_to_cpu(ents[index - 1].hashval) <= args->hashval);
	ASSERT(index == leafhdr.count ||
	       be32_to_cpu(ents[index].hashval) >= args->hashval);

	अगर (args->op_flags & XFS_DA_OP_JUSTCHECK)
		वापस 0;

	/*
	 * Compact out all but one stale leaf entry.  Leaves behind
	 * the entry बंदst to index.
	 */
	अगर (compact)
		xfs_dir3_leaf_compact_x1(&leafhdr, ents, &index, &lowstale,
					 &highstale, &lfloglow, &lfloghigh);
	अन्यथा अगर (leafhdr.stale) अणु
		/*
		 * Set impossible logging indices क्रम this हाल.
		 */
		lfloglow = leafhdr.count;
		lfloghigh = -1;
	पूर्ण

	/*
	 * Insert the new entry, log everything.
	 */
	lep = xfs_dir3_leaf_find_entry(&leafhdr, ents, index, compact, lowstale,
				       highstale, &lfloglow, &lfloghigh);

	lep->hashval = cpu_to_be32(args->hashval);
	lep->address = cpu_to_be32(xfs_dir2_db_off_to_dataptr(args->geo,
				args->blkno, args->index));

	xfs_dir2_leaf_hdr_to_disk(dp->i_mount, leaf, &leafhdr);
	xfs_dir3_leaf_log_header(args, bp);
	xfs_dir3_leaf_log_ents(args, &leafhdr, bp, lfloglow, lfloghigh);
	xfs_dir3_leaf_check(dp, bp);
	वापस 0;
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम
xfs_dir2_मुक्त_hdr_check(
	काष्ठा xfs_inode *dp,
	काष्ठा xfs_buf	*bp,
	xfs_dir2_db_t	db)
अणु
	काष्ठा xfs_dir3_icमुक्त_hdr hdr;

	xfs_dir2_मुक्त_hdr_from_disk(dp->i_mount, &hdr, bp->b_addr);

	ASSERT((hdr.firstdb % dp->i_mount->m_dir_geo->मुक्त_max_bests) == 0);
	ASSERT(hdr.firstdb <= db);
	ASSERT(db < hdr.firstdb + hdr.nvalid);
पूर्ण
#अन्यथा
#घोषणा xfs_dir2_मुक्त_hdr_check(dp, bp, db)
#पूर्ण_अगर	/* DEBUG */

/*
 * Return the last hash value in the leaf.
 * Stale entries are ok.
 */
xfs_dahash_t					/* hash value */
xfs_dir2_leaf_lasthash(
	काष्ठा xfs_inode *dp,
	काष्ठा xfs_buf	*bp,			/* leaf buffer */
	पूर्णांक		*count)			/* count of entries in leaf */
अणु
	काष्ठा xfs_dir3_icleaf_hdr leafhdr;

	xfs_dir2_leaf_hdr_from_disk(dp->i_mount, &leafhdr, bp->b_addr);

	ASSERT(leafhdr.magic == XFS_सूची2_LEAFN_MAGIC ||
	       leafhdr.magic == XFS_सूची3_LEAFN_MAGIC ||
	       leafhdr.magic == XFS_सूची2_LEAF1_MAGIC ||
	       leafhdr.magic == XFS_सूची3_LEAF1_MAGIC);

	अगर (count)
		*count = leafhdr.count;
	अगर (!leafhdr.count)
		वापस 0;
	वापस be32_to_cpu(leafhdr.ents[leafhdr.count - 1].hashval);
पूर्ण

/*
 * Look up a leaf entry क्रम space to add a name in a node-क्रमmat leaf block.
 * The extrablk in state is a मुक्तspace block.
 */
STATIC पूर्णांक
xfs_dir2_leafn_lookup_क्रम_addname(
	काष्ठा xfs_buf		*bp,		/* leaf buffer */
	xfs_da_args_t		*args,		/* operation arguments */
	पूर्णांक			*indexp,	/* out: leaf entry index */
	xfs_da_state_t		*state)		/* state to fill in */
अणु
	काष्ठा xfs_buf		*curbp = शून्य;	/* current data/मुक्त buffer */
	xfs_dir2_db_t		curdb = -1;	/* current data block number */
	xfs_dir2_db_t		curfdb = -1;	/* current मुक्त block number */
	xfs_inode_t		*dp;		/* incore directory inode */
	पूर्णांक			error;		/* error वापस value */
	पूर्णांक			fi;		/* मुक्त entry index */
	xfs_dir2_मुक्त_t		*मुक्त = शून्य;	/* मुक्त block काष्ठाure */
	पूर्णांक			index;		/* leaf entry index */
	xfs_dir2_leaf_t		*leaf;		/* leaf काष्ठाure */
	पूर्णांक			length;		/* length of new data entry */
	xfs_dir2_leaf_entry_t	*lep;		/* leaf entry */
	xfs_mount_t		*mp;		/* fileप्रणाली mount poपूर्णांक */
	xfs_dir2_db_t		newdb;		/* new data block number */
	xfs_dir2_db_t		newfdb;		/* new मुक्त block number */
	xfs_trans_t		*tp;		/* transaction poपूर्णांकer */
	काष्ठा xfs_dir3_icleaf_hdr leafhdr;

	dp = args->dp;
	tp = args->trans;
	mp = dp->i_mount;
	leaf = bp->b_addr;
	xfs_dir2_leaf_hdr_from_disk(mp, &leafhdr, leaf);

	xfs_dir3_leaf_check(dp, bp);
	ASSERT(leafhdr.count > 0);

	/*
	 * Look up the hash value in the leaf entries.
	 */
	index = xfs_dir2_leaf_search_hash(args, bp);
	/*
	 * Do we have a buffer coming in?
	 */
	अगर (state->extravalid) अणु
		/* If so, it's a मुक्त block buffer, get the block number. */
		curbp = state->extrablk.bp;
		curfdb = state->extrablk.blkno;
		मुक्त = curbp->b_addr;
		ASSERT(मुक्त->hdr.magic == cpu_to_be32(XFS_सूची2_FREE_MAGIC) ||
		       मुक्त->hdr.magic == cpu_to_be32(XFS_सूची3_FREE_MAGIC));
	पूर्ण
	length = xfs_dir2_data_entsize(mp, args->namelen);
	/*
	 * Loop over leaf entries with the right hash value.
	 */
	क्रम (lep = &leafhdr.ents[index];
	     index < leafhdr.count && be32_to_cpu(lep->hashval) == args->hashval;
	     lep++, index++) अणु
		/*
		 * Skip stale leaf entries.
		 */
		अगर (be32_to_cpu(lep->address) == XFS_सूची2_शून्य_DATAPTR)
			जारी;
		/*
		 * Pull the data block number from the entry.
		 */
		newdb = xfs_dir2_dataptr_to_db(args->geo,
					       be32_to_cpu(lep->address));
		/*
		 * For addname, we're looking क्रम a place to put the new entry.
		 * We want to use a data block with an entry of equal
		 * hash value to ours अगर there is one with room.
		 *
		 * If this block isn't the data block we alपढ़ोy have
		 * in hand, take a look at it.
		 */
		अगर (newdb != curdb) अणु
			काष्ठा xfs_dir3_icमुक्त_hdr मुक्तhdr;

			curdb = newdb;
			/*
			 * Convert the data block to the मुक्त block
			 * holding its मुक्तspace inक्रमmation.
			 */
			newfdb = xfs_dir2_db_to_fdb(args->geo, newdb);
			/*
			 * If it's not the one we have in hand, पढ़ो it in.
			 */
			अगर (newfdb != curfdb) अणु
				/*
				 * If we had one beक्रमe, drop it.
				 */
				अगर (curbp)
					xfs_trans_brअन्यथा(tp, curbp);

				error = xfs_dir2_मुक्त_पढ़ो(tp, dp,
						xfs_dir2_db_to_da(args->geo,
								  newfdb),
						&curbp);
				अगर (error)
					वापस error;
				मुक्त = curbp->b_addr;

				xfs_dir2_मुक्त_hdr_check(dp, curbp, curdb);
			पूर्ण
			/*
			 * Get the index क्रम our entry.
			 */
			fi = xfs_dir2_db_to_fdindex(args->geo, curdb);
			/*
			 * If it has room, वापस it.
			 */
			xfs_dir2_मुक्त_hdr_from_disk(mp, &मुक्तhdr, मुक्त);
			अगर (XFS_IS_CORRUPT(mp,
					   मुक्तhdr.bests[fi] ==
					   cpu_to_be16(शून्यDATAOFF))) अणु
				अगर (curfdb != newfdb)
					xfs_trans_brअन्यथा(tp, curbp);
				वापस -EFSCORRUPTED;
			पूर्ण
			curfdb = newfdb;
			अगर (be16_to_cpu(मुक्तhdr.bests[fi]) >= length)
				जाओ out;
		पूर्ण
	पूर्ण
	/* Didn't find any space */
	fi = -1;
out:
	ASSERT(args->op_flags & XFS_DA_OP_OKNOENT);
	अगर (curbp) अणु
		/* Giving back a मुक्त block. */
		state->extravalid = 1;
		state->extrablk.bp = curbp;
		state->extrablk.index = fi;
		state->extrablk.blkno = curfdb;

		/*
		 * Important: this magic number is not in the buffer - it's क्रम
		 * buffer type inक्रमmation and thereक्रमe only the मुक्त/data type
		 * matters here, not whether CRCs are enabled or not.
		 */
		state->extrablk.magic = XFS_सूची2_FREE_MAGIC;
	पूर्ण अन्यथा अणु
		state->extravalid = 0;
	पूर्ण
	/*
	 * Return the index, that will be the insertion poपूर्णांक.
	 */
	*indexp = index;
	वापस -ENOENT;
पूर्ण

/*
 * Look up a leaf entry in a node-क्रमmat leaf block.
 * The extrablk in state a data block.
 */
STATIC पूर्णांक
xfs_dir2_leafn_lookup_क्रम_entry(
	काष्ठा xfs_buf		*bp,		/* leaf buffer */
	xfs_da_args_t		*args,		/* operation arguments */
	पूर्णांक			*indexp,	/* out: leaf entry index */
	xfs_da_state_t		*state)		/* state to fill in */
अणु
	काष्ठा xfs_buf		*curbp = शून्य;	/* current data/मुक्त buffer */
	xfs_dir2_db_t		curdb = -1;	/* current data block number */
	xfs_dir2_data_entry_t	*dep;		/* data block entry */
	xfs_inode_t		*dp;		/* incore directory inode */
	पूर्णांक			error;		/* error वापस value */
	पूर्णांक			index;		/* leaf entry index */
	xfs_dir2_leaf_t		*leaf;		/* leaf काष्ठाure */
	xfs_dir2_leaf_entry_t	*lep;		/* leaf entry */
	xfs_mount_t		*mp;		/* fileप्रणाली mount poपूर्णांक */
	xfs_dir2_db_t		newdb;		/* new data block number */
	xfs_trans_t		*tp;		/* transaction poपूर्णांकer */
	क्रमागत xfs_dacmp		cmp;		/* comparison result */
	काष्ठा xfs_dir3_icleaf_hdr leafhdr;

	dp = args->dp;
	tp = args->trans;
	mp = dp->i_mount;
	leaf = bp->b_addr;
	xfs_dir2_leaf_hdr_from_disk(mp, &leafhdr, leaf);

	xfs_dir3_leaf_check(dp, bp);
	अगर (leafhdr.count <= 0) अणु
		xfs_buf_mark_corrupt(bp);
		वापस -EFSCORRUPTED;
	पूर्ण

	/*
	 * Look up the hash value in the leaf entries.
	 */
	index = xfs_dir2_leaf_search_hash(args, bp);
	/*
	 * Do we have a buffer coming in?
	 */
	अगर (state->extravalid) अणु
		curbp = state->extrablk.bp;
		curdb = state->extrablk.blkno;
	पूर्ण
	/*
	 * Loop over leaf entries with the right hash value.
	 */
	क्रम (lep = &leafhdr.ents[index];
	     index < leafhdr.count && be32_to_cpu(lep->hashval) == args->hashval;
	     lep++, index++) अणु
		/*
		 * Skip stale leaf entries.
		 */
		अगर (be32_to_cpu(lep->address) == XFS_सूची2_शून्य_DATAPTR)
			जारी;
		/*
		 * Pull the data block number from the entry.
		 */
		newdb = xfs_dir2_dataptr_to_db(args->geo,
					       be32_to_cpu(lep->address));
		/*
		 * Not adding a new entry, so we really want to find
		 * the name given to us.
		 *
		 * If it's a dअगरferent data block, go get it.
		 */
		अगर (newdb != curdb) अणु
			/*
			 * If we had a block beक्रमe that we aren't saving
			 * क्रम a CI name, drop it
			 */
			अगर (curbp && (args->cmpresult == XFS_CMP_DIFFERENT ||
						curdb != state->extrablk.blkno))
				xfs_trans_brअन्यथा(tp, curbp);
			/*
			 * If needing the block that is saved with a CI match,
			 * use it otherwise पढ़ो in the new data block.
			 */
			अगर (args->cmpresult != XFS_CMP_DIFFERENT &&
					newdb == state->extrablk.blkno) अणु
				ASSERT(state->extravalid);
				curbp = state->extrablk.bp;
			पूर्ण अन्यथा अणु
				error = xfs_dir3_data_पढ़ो(tp, dp,
						xfs_dir2_db_to_da(args->geo,
								  newdb),
						0, &curbp);
				अगर (error)
					वापस error;
			पूर्ण
			xfs_dir3_data_check(dp, curbp);
			curdb = newdb;
		पूर्ण
		/*
		 * Poपूर्णांक to the data entry.
		 */
		dep = (xfs_dir2_data_entry_t *)((अक्षर *)curbp->b_addr +
			xfs_dir2_dataptr_to_off(args->geo,
						be32_to_cpu(lep->address)));
		/*
		 * Compare the entry and अगर it's an exact match, वापस
		 * EEXIST immediately. If it's the first हाल-insensitive
		 * match, store the block & inode number and जारी looking.
		 */
		cmp = xfs_dir2_compname(args, dep->name, dep->namelen);
		अगर (cmp != XFS_CMP_DIFFERENT && cmp != args->cmpresult) अणु
			/* If there is a CI match block, drop it */
			अगर (args->cmpresult != XFS_CMP_DIFFERENT &&
						curdb != state->extrablk.blkno)
				xfs_trans_brअन्यथा(tp, state->extrablk.bp);
			args->cmpresult = cmp;
			args->inumber = be64_to_cpu(dep->inumber);
			args->filetype = xfs_dir2_data_get_ftype(mp, dep);
			*indexp = index;
			state->extravalid = 1;
			state->extrablk.bp = curbp;
			state->extrablk.blkno = curdb;
			state->extrablk.index = (पूर्णांक)((अक्षर *)dep -
							(अक्षर *)curbp->b_addr);
			state->extrablk.magic = XFS_सूची2_DATA_MAGIC;
			curbp->b_ops = &xfs_dir3_data_buf_ops;
			xfs_trans_buf_set_type(tp, curbp, XFS_BLFT_सूची_DATA_BUF);
			अगर (cmp == XFS_CMP_EXACT)
				वापस -EEXIST;
		पूर्ण
	पूर्ण
	ASSERT(index == leafhdr.count || (args->op_flags & XFS_DA_OP_OKNOENT));
	अगर (curbp) अणु
		अगर (args->cmpresult == XFS_CMP_DIFFERENT) अणु
			/* Giving back last used data block. */
			state->extravalid = 1;
			state->extrablk.bp = curbp;
			state->extrablk.index = -1;
			state->extrablk.blkno = curdb;
			state->extrablk.magic = XFS_सूची2_DATA_MAGIC;
			curbp->b_ops = &xfs_dir3_data_buf_ops;
			xfs_trans_buf_set_type(tp, curbp, XFS_BLFT_सूची_DATA_BUF);
		पूर्ण अन्यथा अणु
			/* If the curbp is not the CI match block, drop it */
			अगर (state->extrablk.bp != curbp)
				xfs_trans_brअन्यथा(tp, curbp);
		पूर्ण
	पूर्ण अन्यथा अणु
		state->extravalid = 0;
	पूर्ण
	*indexp = index;
	वापस -ENOENT;
पूर्ण

/*
 * Look up a leaf entry in a node-क्रमmat leaf block.
 * If this is an addname then the extrablk in state is a मुक्तspace block,
 * otherwise it's a data block.
 */
पूर्णांक
xfs_dir2_leafn_lookup_पूर्णांक(
	काष्ठा xfs_buf		*bp,		/* leaf buffer */
	xfs_da_args_t		*args,		/* operation arguments */
	पूर्णांक			*indexp,	/* out: leaf entry index */
	xfs_da_state_t		*state)		/* state to fill in */
अणु
	अगर (args->op_flags & XFS_DA_OP_ADDNAME)
		वापस xfs_dir2_leafn_lookup_क्रम_addname(bp, args, indexp,
							state);
	वापस xfs_dir2_leafn_lookup_क्रम_entry(bp, args, indexp, state);
पूर्ण

/*
 * Move count leaf entries from source to destination leaf.
 * Log entries and headers.  Stale entries are preserved.
 */
अटल व्योम
xfs_dir3_leafn_moveents(
	xfs_da_args_t			*args,	/* operation arguments */
	काष्ठा xfs_buf			*bp_s,	/* source */
	काष्ठा xfs_dir3_icleaf_hdr	*shdr,
	काष्ठा xfs_dir2_leaf_entry	*sents,
	पूर्णांक				start_s,/* source leaf index */
	काष्ठा xfs_buf			*bp_d,	/* destination */
	काष्ठा xfs_dir3_icleaf_hdr	*dhdr,
	काष्ठा xfs_dir2_leaf_entry	*dents,
	पूर्णांक				start_d,/* destination leaf index */
	पूर्णांक				count)	/* count of leaves to copy */
अणु
	पूर्णांक				stale;	/* count stale leaves copied */

	trace_xfs_dir2_leafn_moveents(args, start_s, start_d, count);

	/*
	 * Silently वापस अगर nothing to करो.
	 */
	अगर (count == 0)
		वापस;

	/*
	 * If the destination index is not the end of the current
	 * destination leaf entries, खोलो up a hole in the destination
	 * to hold the new entries.
	 */
	अगर (start_d < dhdr->count) अणु
		स_हटाओ(&dents[start_d + count], &dents[start_d],
			(dhdr->count - start_d) * माप(xfs_dir2_leaf_entry_t));
		xfs_dir3_leaf_log_ents(args, dhdr, bp_d, start_d + count,
				       count + dhdr->count - 1);
	पूर्ण
	/*
	 * If the source has stale leaves, count the ones in the copy range
	 * so we can update the header correctly.
	 */
	अगर (shdr->stale) अणु
		पूर्णांक	i;			/* temp leaf index */

		क्रम (i = start_s, stale = 0; i < start_s + count; i++) अणु
			अगर (sents[i].address ==
					cpu_to_be32(XFS_सूची2_शून्य_DATAPTR))
				stale++;
		पूर्ण
	पूर्ण अन्यथा
		stale = 0;
	/*
	 * Copy the leaf entries from source to destination.
	 */
	स_नकल(&dents[start_d], &sents[start_s],
		count * माप(xfs_dir2_leaf_entry_t));
	xfs_dir3_leaf_log_ents(args, dhdr, bp_d, start_d, start_d + count - 1);

	/*
	 * If there are source entries after the ones we copied,
	 * delete the ones we copied by sliding the next ones करोwn.
	 */
	अगर (start_s + count < shdr->count) अणु
		स_हटाओ(&sents[start_s], &sents[start_s + count],
			count * माप(xfs_dir2_leaf_entry_t));
		xfs_dir3_leaf_log_ents(args, shdr, bp_s, start_s,
				       start_s + count - 1);
	पूर्ण

	/*
	 * Update the headers and log them.
	 */
	shdr->count -= count;
	shdr->stale -= stale;
	dhdr->count += count;
	dhdr->stale += stale;
पूर्ण

/*
 * Determine the sort order of two leaf blocks.
 * Returns 1 अगर both are valid and leaf2 should be beक्रमe leaf1, अन्यथा 0.
 */
पूर्णांक						/* sort order */
xfs_dir2_leafn_order(
	काष्ठा xfs_inode	*dp,
	काष्ठा xfs_buf		*leaf1_bp,		/* leaf1 buffer */
	काष्ठा xfs_buf		*leaf2_bp)		/* leaf2 buffer */
अणु
	काष्ठा xfs_dir2_leaf	*leaf1 = leaf1_bp->b_addr;
	काष्ठा xfs_dir2_leaf	*leaf2 = leaf2_bp->b_addr;
	काष्ठा xfs_dir2_leaf_entry *ents1;
	काष्ठा xfs_dir2_leaf_entry *ents2;
	काष्ठा xfs_dir3_icleaf_hdr hdr1;
	काष्ठा xfs_dir3_icleaf_hdr hdr2;

	xfs_dir2_leaf_hdr_from_disk(dp->i_mount, &hdr1, leaf1);
	xfs_dir2_leaf_hdr_from_disk(dp->i_mount, &hdr2, leaf2);
	ents1 = hdr1.ents;
	ents2 = hdr2.ents;

	अगर (hdr1.count > 0 && hdr2.count > 0 &&
	    (be32_to_cpu(ents2[0].hashval) < be32_to_cpu(ents1[0].hashval) ||
	     be32_to_cpu(ents2[hdr2.count - 1].hashval) <
				be32_to_cpu(ents1[hdr1.count - 1].hashval)))
		वापस 1;
	वापस 0;
पूर्ण

/*
 * Rebalance leaf entries between two leaf blocks.
 * This is actually only called when the second block is new,
 * though the code deals with the general हाल.
 * A new entry will be inserted in one of the blocks, and that
 * entry is taken पूर्णांकo account when balancing.
 */
अटल व्योम
xfs_dir2_leafn_rebalance(
	xfs_da_state_t		*state,		/* btree cursor */
	xfs_da_state_blk_t	*blk1,		/* first btree block */
	xfs_da_state_blk_t	*blk2)		/* second btree block */
अणु
	xfs_da_args_t		*args;		/* operation arguments */
	पूर्णांक			count;		/* count (& direction) leaves */
	पूर्णांक			isleft;		/* new goes in left leaf */
	xfs_dir2_leaf_t		*leaf1;		/* first leaf काष्ठाure */
	xfs_dir2_leaf_t		*leaf2;		/* second leaf काष्ठाure */
	पूर्णांक			mid;		/* midpoपूर्णांक leaf index */
#अगर defined(DEBUG) || defined(XFS_WARN)
	पूर्णांक			oldstale;	/* old count of stale leaves */
#पूर्ण_अगर
	पूर्णांक			oldsum;		/* old total leaf count */
	पूर्णांक			swap_blocks;	/* swapped leaf blocks */
	काष्ठा xfs_dir2_leaf_entry *ents1;
	काष्ठा xfs_dir2_leaf_entry *ents2;
	काष्ठा xfs_dir3_icleaf_hdr hdr1;
	काष्ठा xfs_dir3_icleaf_hdr hdr2;
	काष्ठा xfs_inode	*dp = state->args->dp;

	args = state->args;
	/*
	 * If the block order is wrong, swap the arguments.
	 */
	swap_blocks = xfs_dir2_leafn_order(dp, blk1->bp, blk2->bp);
	अगर (swap_blocks)
		swap(blk1, blk2);

	leaf1 = blk1->bp->b_addr;
	leaf2 = blk2->bp->b_addr;
	xfs_dir2_leaf_hdr_from_disk(dp->i_mount, &hdr1, leaf1);
	xfs_dir2_leaf_hdr_from_disk(dp->i_mount, &hdr2, leaf2);
	ents1 = hdr1.ents;
	ents2 = hdr2.ents;

	oldsum = hdr1.count + hdr2.count;
#अगर defined(DEBUG) || defined(XFS_WARN)
	oldstale = hdr1.stale + hdr2.stale;
#पूर्ण_अगर
	mid = oldsum >> 1;

	/*
	 * If the old leaf count was odd then the new one will be even,
	 * so we need to भागide the new count evenly.
	 */
	अगर (oldsum & 1) अणु
		xfs_dahash_t	midhash;	/* middle entry hash value */

		अगर (mid >= hdr1.count)
			midhash = be32_to_cpu(ents2[mid - hdr1.count].hashval);
		अन्यथा
			midhash = be32_to_cpu(ents1[mid].hashval);
		isleft = args->hashval <= midhash;
	पूर्ण
	/*
	 * If the old count is even then the new count is odd, so there's
	 * no preferred side क्रम the new entry.
	 * Pick the left one.
	 */
	अन्यथा
		isleft = 1;
	/*
	 * Calculate moved entry count.  Positive means left-to-right,
	 * negative means right-to-left.  Then move the entries.
	 */
	count = hdr1.count - mid + (isleft == 0);
	अगर (count > 0)
		xfs_dir3_leafn_moveents(args, blk1->bp, &hdr1, ents1,
					hdr1.count - count, blk2->bp,
					&hdr2, ents2, 0, count);
	अन्यथा अगर (count < 0)
		xfs_dir3_leafn_moveents(args, blk2->bp, &hdr2, ents2, 0,
					blk1->bp, &hdr1, ents1,
					hdr1.count, count);

	ASSERT(hdr1.count + hdr2.count == oldsum);
	ASSERT(hdr1.stale + hdr2.stale == oldstale);

	/* log the changes made when moving the entries */
	xfs_dir2_leaf_hdr_to_disk(dp->i_mount, leaf1, &hdr1);
	xfs_dir2_leaf_hdr_to_disk(dp->i_mount, leaf2, &hdr2);
	xfs_dir3_leaf_log_header(args, blk1->bp);
	xfs_dir3_leaf_log_header(args, blk2->bp);

	xfs_dir3_leaf_check(dp, blk1->bp);
	xfs_dir3_leaf_check(dp, blk2->bp);

	/*
	 * Mark whether we're inserting पूर्णांकo the old or new leaf.
	 */
	अगर (hdr1.count < hdr2.count)
		state->inleaf = swap_blocks;
	अन्यथा अगर (hdr1.count > hdr2.count)
		state->inleaf = !swap_blocks;
	अन्यथा
		state->inleaf = swap_blocks ^ (blk1->index <= hdr1.count);
	/*
	 * Adjust the expected index क्रम insertion.
	 */
	अगर (!state->inleaf)
		blk2->index = blk1->index - hdr1.count;

	/*
	 * Finally sanity check just to make sure we are not वापसing a
	 * negative index
	 */
	अगर (blk2->index < 0) अणु
		state->inleaf = 1;
		blk2->index = 0;
		xfs_alert(dp->i_mount,
	"%s: picked the wrong leaf? reverting original leaf: blk1->index %d",
			__func__, blk1->index);
	पूर्ण
पूर्ण

अटल पूर्णांक
xfs_dir3_data_block_मुक्त(
	xfs_da_args_t		*args,
	काष्ठा xfs_dir2_data_hdr *hdr,
	काष्ठा xfs_dir2_मुक्त	*मुक्त,
	xfs_dir2_db_t		fdb,
	पूर्णांक			findex,
	काष्ठा xfs_buf		*fbp,
	पूर्णांक			दीर्घest)
अणु
	पूर्णांक			logमुक्त = 0;
	काष्ठा xfs_dir3_icमुक्त_hdr मुक्तhdr;
	काष्ठा xfs_inode	*dp = args->dp;

	xfs_dir2_मुक्त_hdr_from_disk(dp->i_mount, &मुक्तhdr, मुक्त);
	अगर (hdr) अणु
		/*
		 * Data block is not empty, just set the मुक्त entry to the new
		 * value.
		 */
		मुक्तhdr.bests[findex] = cpu_to_be16(दीर्घest);
		xfs_dir2_मुक्त_log_bests(args, &मुक्तhdr, fbp, findex, findex);
		वापस 0;
	पूर्ण

	/* One less used entry in the मुक्त table. */
	मुक्तhdr.nused--;

	/*
	 * If this was the last entry in the table, we can trim the table size
	 * back.  There might be other entries at the end referring to
	 * non-existent data blocks, get those too.
	 */
	अगर (findex == मुक्तhdr.nvalid - 1) अणु
		पूर्णांक	i;		/* मुक्त entry index */

		क्रम (i = findex - 1; i >= 0; i--) अणु
			अगर (मुक्तhdr.bests[i] != cpu_to_be16(शून्यDATAOFF))
				अवरोध;
		पूर्ण
		मुक्तhdr.nvalid = i + 1;
		logमुक्त = 0;
	पूर्ण अन्यथा अणु
		/* Not the last entry, just punch it out.  */
		मुक्तhdr.bests[findex] = cpu_to_be16(शून्यDATAOFF);
		logमुक्त = 1;
	पूर्ण

	xfs_dir2_मुक्त_hdr_to_disk(dp->i_mount, मुक्त, &मुक्तhdr);
	xfs_dir2_मुक्त_log_header(args, fbp);

	/*
	 * If there are no useful entries left in the block, get rid of the
	 * block अगर we can.
	 */
	अगर (!मुक्तhdr.nused) अणु
		पूर्णांक error;

		error = xfs_dir2_shrink_inode(args, fdb, fbp);
		अगर (error == 0) अणु
			fbp = शून्य;
			logमुक्त = 0;
		पूर्ण अन्यथा अगर (error != -ENOSPC || args->total != 0)
			वापस error;
		/*
		 * It's possible to get ENOSPC अगर there is no
		 * space reservation.  In this हाल some one
		 * अन्यथा will eventually get rid of this block.
		 */
	पूर्ण

	/* Log the मुक्त entry that changed, unless we got rid of it.  */
	अगर (logमुक्त)
		xfs_dir2_मुक्त_log_bests(args, &मुक्तhdr, fbp, findex, findex);
	वापस 0;
पूर्ण

/*
 * Remove an entry from a node directory.
 * This हटाओs the leaf entry and the data entry,
 * and updates the मुक्त block अगर necessary.
 */
अटल पूर्णांक					/* error */
xfs_dir2_leafn_हटाओ(
	xfs_da_args_t		*args,		/* operation arguments */
	काष्ठा xfs_buf		*bp,		/* leaf buffer */
	पूर्णांक			index,		/* leaf entry index */
	xfs_da_state_blk_t	*dblk,		/* data block */
	पूर्णांक			*rval)		/* resulting block needs join */
अणु
	काष्ठा xfs_da_geometry	*geo = args->geo;
	xfs_dir2_data_hdr_t	*hdr;		/* data block header */
	xfs_dir2_db_t		db;		/* data block number */
	काष्ठा xfs_buf		*dbp;		/* data block buffer */
	xfs_dir2_data_entry_t	*dep;		/* data block entry */
	xfs_inode_t		*dp;		/* incore directory inode */
	xfs_dir2_leaf_t		*leaf;		/* leaf काष्ठाure */
	xfs_dir2_leaf_entry_t	*lep;		/* leaf entry */
	पूर्णांक			दीर्घest;	/* दीर्घest data मुक्त entry */
	पूर्णांक			off;		/* data block entry offset */
	पूर्णांक			needlog;	/* need to log data header */
	पूर्णांक			needscan;	/* need to rescan data मुक्तs */
	xfs_trans_t		*tp;		/* transaction poपूर्णांकer */
	काष्ठा xfs_dir2_data_मुक्त *bf;		/* bestमुक्त table */
	काष्ठा xfs_dir3_icleaf_hdr leafhdr;

	trace_xfs_dir2_leafn_हटाओ(args, index);

	dp = args->dp;
	tp = args->trans;
	leaf = bp->b_addr;
	xfs_dir2_leaf_hdr_from_disk(dp->i_mount, &leafhdr, leaf);

	/*
	 * Poपूर्णांक to the entry we're removing.
	 */
	lep = &leafhdr.ents[index];

	/*
	 * Extract the data block and offset from the entry.
	 */
	db = xfs_dir2_dataptr_to_db(geo, be32_to_cpu(lep->address));
	ASSERT(dblk->blkno == db);
	off = xfs_dir2_dataptr_to_off(geo, be32_to_cpu(lep->address));
	ASSERT(dblk->index == off);

	/*
	 * Kill the leaf entry by marking it stale.
	 * Log the leaf block changes.
	 */
	leafhdr.stale++;
	xfs_dir2_leaf_hdr_to_disk(dp->i_mount, leaf, &leafhdr);
	xfs_dir3_leaf_log_header(args, bp);

	lep->address = cpu_to_be32(XFS_सूची2_शून्य_DATAPTR);
	xfs_dir3_leaf_log_ents(args, &leafhdr, bp, index, index);

	/*
	 * Make the data entry मुक्त.  Keep track of the दीर्घest मुक्तspace
	 * in the data block in हाल it changes.
	 */
	dbp = dblk->bp;
	hdr = dbp->b_addr;
	dep = (xfs_dir2_data_entry_t *)((अक्षर *)hdr + off);
	bf = xfs_dir2_data_bestमुक्त_p(dp->i_mount, hdr);
	दीर्घest = be16_to_cpu(bf[0].length);
	needlog = needscan = 0;
	xfs_dir2_data_make_मुक्त(args, dbp, off,
		xfs_dir2_data_entsize(dp->i_mount, dep->namelen), &needlog,
		&needscan);
	/*
	 * Rescan the data block मुक्तspaces क्रम bestमुक्त.
	 * Log the data block header अगर needed.
	 */
	अगर (needscan)
		xfs_dir2_data_मुक्तscan(dp->i_mount, hdr, &needlog);
	अगर (needlog)
		xfs_dir2_data_log_header(args, dbp);
	xfs_dir3_data_check(dp, dbp);
	/*
	 * If the दीर्घest data block मुक्तspace changes, need to update
	 * the corresponding मुक्तblock entry.
	 */
	अगर (दीर्घest < be16_to_cpu(bf[0].length)) अणु
		पूर्णांक		error;		/* error वापस value */
		काष्ठा xfs_buf	*fbp;		/* मुक्तblock buffer */
		xfs_dir2_db_t	fdb;		/* मुक्तblock block number */
		पूर्णांक		findex;		/* index in मुक्तblock entries */
		xfs_dir2_मुक्त_t	*मुक्त;		/* मुक्तblock काष्ठाure */

		/*
		 * Convert the data block number to a मुक्त block,
		 * पढ़ो in the मुक्त block.
		 */
		fdb = xfs_dir2_db_to_fdb(geo, db);
		error = xfs_dir2_मुक्त_पढ़ो(tp, dp, xfs_dir2_db_to_da(geo, fdb),
					   &fbp);
		अगर (error)
			वापस error;
		मुक्त = fbp->b_addr;
#अगर_घोषित DEBUG
	अणु
		काष्ठा xfs_dir3_icमुक्त_hdr मुक्तhdr;

		xfs_dir2_मुक्त_hdr_from_disk(dp->i_mount, &मुक्तhdr, मुक्त);
		ASSERT(मुक्तhdr.firstdb == geo->मुक्त_max_bests *
			(fdb - xfs_dir2_byte_to_db(geo, XFS_सूची2_FREE_OFFSET)));
	पूर्ण
#पूर्ण_अगर
		/*
		 * Calculate which entry we need to fix.
		 */
		findex = xfs_dir2_db_to_fdindex(geo, db);
		दीर्घest = be16_to_cpu(bf[0].length);
		/*
		 * If the data block is now empty we can get rid of it
		 * (usually).
		 */
		अगर (दीर्घest == geo->blksize - geo->data_entry_offset) अणु
			/*
			 * Try to punch out the data block.
			 */
			error = xfs_dir2_shrink_inode(args, db, dbp);
			अगर (error == 0) अणु
				dblk->bp = शून्य;
				hdr = शून्य;
			पूर्ण
			/*
			 * We can get ENOSPC अगर there's no space reservation.
			 * In this हाल just drop the buffer and some one अन्यथा
			 * will eventually get rid of the empty block.
			 */
			अन्यथा अगर (!(error == -ENOSPC && args->total == 0))
				वापस error;
		पूर्ण
		/*
		 * If we got rid of the data block, we can eliminate that entry
		 * in the मुक्त block.
		 */
		error = xfs_dir3_data_block_मुक्त(args, hdr, मुक्त,
						 fdb, findex, fbp, दीर्घest);
		अगर (error)
			वापस error;
	पूर्ण

	xfs_dir3_leaf_check(dp, bp);
	/*
	 * Return indication of whether this leaf block is empty enough
	 * to justअगरy trying to join it with a neighbor.
	 */
	*rval = (geo->leaf_hdr_size +
		 (uपूर्णांक)माप(leafhdr.ents) * (leafhdr.count - leafhdr.stale)) <
		geo->magicpct;
	वापस 0;
पूर्ण

/*
 * Split the leaf entries in the old block पूर्णांकo old and new blocks.
 */
पूर्णांक						/* error */
xfs_dir2_leafn_split(
	xfs_da_state_t		*state,		/* btree cursor */
	xfs_da_state_blk_t	*oldblk,	/* original block */
	xfs_da_state_blk_t	*newblk)	/* newly created block */
अणु
	xfs_da_args_t		*args;		/* operation arguments */
	xfs_dablk_t		blkno;		/* new leaf block number */
	पूर्णांक			error;		/* error वापस value */
	काष्ठा xfs_inode	*dp;

	/*
	 * Allocate space क्रम a new leaf node.
	 */
	args = state->args;
	dp = args->dp;
	ASSERT(oldblk->magic == XFS_सूची2_LEAFN_MAGIC);
	error = xfs_da_grow_inode(args, &blkno);
	अगर (error) अणु
		वापस error;
	पूर्ण
	/*
	 * Initialize the new leaf block.
	 */
	error = xfs_dir3_leaf_get_buf(args, xfs_dir2_da_to_db(args->geo, blkno),
				      &newblk->bp, XFS_सूची2_LEAFN_MAGIC);
	अगर (error)
		वापस error;

	newblk->blkno = blkno;
	newblk->magic = XFS_सूची2_LEAFN_MAGIC;
	/*
	 * Rebalance the entries across the two leaves, link the new
	 * block पूर्णांकo the leaves.
	 */
	xfs_dir2_leafn_rebalance(state, oldblk, newblk);
	error = xfs_da3_blk_link(state, oldblk, newblk);
	अगर (error) अणु
		वापस error;
	पूर्ण
	/*
	 * Insert the new entry in the correct block.
	 */
	अगर (state->inleaf)
		error = xfs_dir2_leafn_add(oldblk->bp, args, oldblk->index);
	अन्यथा
		error = xfs_dir2_leafn_add(newblk->bp, args, newblk->index);
	/*
	 * Update last hashval in each block since we added the name.
	 */
	oldblk->hashval = xfs_dir2_leaf_lasthash(dp, oldblk->bp, शून्य);
	newblk->hashval = xfs_dir2_leaf_lasthash(dp, newblk->bp, शून्य);
	xfs_dir3_leaf_check(dp, oldblk->bp);
	xfs_dir3_leaf_check(dp, newblk->bp);
	वापस error;
पूर्ण

/*
 * Check a leaf block and its neighbors to see अगर the block should be
 * collapsed पूर्णांकo one or the other neighbor.  Always keep the block
 * with the smaller block number.
 * If the current block is over 50% full, करोn't try to join it, वापस 0.
 * If the block is empty, fill in the state काष्ठाure and वापस 2.
 * If it can be collapsed, fill in the state काष्ठाure and वापस 1.
 * If nothing can be करोne, वापस 0.
 */
पूर्णांक						/* error */
xfs_dir2_leafn_toosmall(
	xfs_da_state_t		*state,		/* btree cursor */
	पूर्णांक			*action)	/* resulting action to take */
अणु
	xfs_da_state_blk_t	*blk;		/* leaf block */
	xfs_dablk_t		blkno;		/* leaf block number */
	काष्ठा xfs_buf		*bp;		/* leaf buffer */
	पूर्णांक			bytes;		/* bytes in use */
	पूर्णांक			count;		/* leaf live entry count */
	पूर्णांक			error;		/* error वापस value */
	पूर्णांक			क्रमward;	/* sibling block direction */
	पूर्णांक			i;		/* sibling counter */
	xfs_dir2_leaf_t		*leaf;		/* leaf काष्ठाure */
	पूर्णांक			rval;		/* result from path_shअगरt */
	काष्ठा xfs_dir3_icleaf_hdr leafhdr;
	काष्ठा xfs_dir2_leaf_entry *ents;
	काष्ठा xfs_inode	*dp = state->args->dp;

	/*
	 * Check क्रम the degenerate हाल of the block being over 50% full.
	 * If so, it's not worth even looking to see अगर we might be able
	 * to coalesce with a sibling.
	 */
	blk = &state->path.blk[state->path.active - 1];
	leaf = blk->bp->b_addr;
	xfs_dir2_leaf_hdr_from_disk(dp->i_mount, &leafhdr, leaf);
	ents = leafhdr.ents;
	xfs_dir3_leaf_check(dp, blk->bp);

	count = leafhdr.count - leafhdr.stale;
	bytes = state->args->geo->leaf_hdr_size + count * माप(ents[0]);
	अगर (bytes > (state->args->geo->blksize >> 1)) अणु
		/*
		 * Blk over 50%, करोn't try to join.
		 */
		*action = 0;
		वापस 0;
	पूर्ण
	/*
	 * Check क्रम the degenerate हाल of the block being empty.
	 * If the block is empty, we'll simply delete it, no need to
	 * coalesce it with a sibling block.  We choose (arbitrarily)
	 * to merge with the क्रमward block unless it is शून्य.
	 */
	अगर (count == 0) अणु
		/*
		 * Make altpath poपूर्णांक to the block we want to keep and
		 * path poपूर्णांक to the block we want to drop (this one).
		 */
		क्रमward = (leafhdr.क्रमw != 0);
		स_नकल(&state->altpath, &state->path, माप(state->path));
		error = xfs_da3_path_shअगरt(state, &state->altpath, क्रमward, 0,
			&rval);
		अगर (error)
			वापस error;
		*action = rval ? 2 : 0;
		वापस 0;
	पूर्ण
	/*
	 * Examine each sibling block to see अगर we can coalesce with
	 * at least 25% मुक्त space to spare.  We need to figure out
	 * whether to merge with the क्रमward or the backward block.
	 * We prefer coalescing with the lower numbered sibling so as
	 * to shrink a directory over समय.
	 */
	क्रमward = leafhdr.क्रमw < leafhdr.back;
	क्रम (i = 0, bp = शून्य; i < 2; क्रमward = !क्रमward, i++) अणु
		काष्ठा xfs_dir3_icleaf_hdr hdr2;

		blkno = क्रमward ? leafhdr.क्रमw : leafhdr.back;
		अगर (blkno == 0)
			जारी;
		/*
		 * Read the sibling leaf block.
		 */
		error = xfs_dir3_leafn_पढ़ो(state->args->trans, dp, blkno, &bp);
		अगर (error)
			वापस error;

		/*
		 * Count bytes in the two blocks combined.
		 */
		count = leafhdr.count - leafhdr.stale;
		bytes = state->args->geo->blksize -
			(state->args->geo->blksize >> 2);

		leaf = bp->b_addr;
		xfs_dir2_leaf_hdr_from_disk(dp->i_mount, &hdr2, leaf);
		ents = hdr2.ents;
		count += hdr2.count - hdr2.stale;
		bytes -= count * माप(ents[0]);

		/*
		 * Fits with at least 25% to spare.
		 */
		अगर (bytes >= 0)
			अवरोध;
		xfs_trans_brअन्यथा(state->args->trans, bp);
	पूर्ण
	/*
	 * Didn't like either block, give up.
	 */
	अगर (i >= 2) अणु
		*action = 0;
		वापस 0;
	पूर्ण

	/*
	 * Make altpath poपूर्णांक to the block we want to keep (the lower
	 * numbered block) and path poपूर्णांक to the block we want to drop.
	 */
	स_नकल(&state->altpath, &state->path, माप(state->path));
	अगर (blkno < blk->blkno)
		error = xfs_da3_path_shअगरt(state, &state->altpath, क्रमward, 0,
			&rval);
	अन्यथा
		error = xfs_da3_path_shअगरt(state, &state->path, क्रमward, 0,
			&rval);
	अगर (error) अणु
		वापस error;
	पूर्ण
	*action = rval ? 0 : 1;
	वापस 0;
पूर्ण

/*
 * Move all the leaf entries from drop_blk to save_blk.
 * This is करोne as part of a join operation.
 */
व्योम
xfs_dir2_leafn_unbalance(
	xfs_da_state_t		*state,		/* cursor */
	xfs_da_state_blk_t	*drop_blk,	/* dead block */
	xfs_da_state_blk_t	*save_blk)	/* surviving block */
अणु
	xfs_da_args_t		*args;		/* operation arguments */
	xfs_dir2_leaf_t		*drop_leaf;	/* dead leaf काष्ठाure */
	xfs_dir2_leaf_t		*save_leaf;	/* surviving leaf काष्ठाure */
	काष्ठा xfs_dir3_icleaf_hdr savehdr;
	काष्ठा xfs_dir3_icleaf_hdr drophdr;
	काष्ठा xfs_dir2_leaf_entry *sents;
	काष्ठा xfs_dir2_leaf_entry *dents;
	काष्ठा xfs_inode	*dp = state->args->dp;

	args = state->args;
	ASSERT(drop_blk->magic == XFS_सूची2_LEAFN_MAGIC);
	ASSERT(save_blk->magic == XFS_सूची2_LEAFN_MAGIC);
	drop_leaf = drop_blk->bp->b_addr;
	save_leaf = save_blk->bp->b_addr;

	xfs_dir2_leaf_hdr_from_disk(dp->i_mount, &savehdr, save_leaf);
	xfs_dir2_leaf_hdr_from_disk(dp->i_mount, &drophdr, drop_leaf);
	sents = savehdr.ents;
	dents = drophdr.ents;

	/*
	 * If there are any stale leaf entries, take this opportunity
	 * to purge them.
	 */
	अगर (drophdr.stale)
		xfs_dir3_leaf_compact(args, &drophdr, drop_blk->bp);
	अगर (savehdr.stale)
		xfs_dir3_leaf_compact(args, &savehdr, save_blk->bp);

	/*
	 * Move the entries from drop to the appropriate end of save.
	 */
	drop_blk->hashval = be32_to_cpu(dents[drophdr.count - 1].hashval);
	अगर (xfs_dir2_leafn_order(dp, save_blk->bp, drop_blk->bp))
		xfs_dir3_leafn_moveents(args, drop_blk->bp, &drophdr, dents, 0,
					save_blk->bp, &savehdr, sents, 0,
					drophdr.count);
	अन्यथा
		xfs_dir3_leafn_moveents(args, drop_blk->bp, &drophdr, dents, 0,
					save_blk->bp, &savehdr, sents,
					savehdr.count, drophdr.count);
	save_blk->hashval = be32_to_cpu(sents[savehdr.count - 1].hashval);

	/* log the changes made when moving the entries */
	xfs_dir2_leaf_hdr_to_disk(dp->i_mount, save_leaf, &savehdr);
	xfs_dir2_leaf_hdr_to_disk(dp->i_mount, drop_leaf, &drophdr);
	xfs_dir3_leaf_log_header(args, save_blk->bp);
	xfs_dir3_leaf_log_header(args, drop_blk->bp);

	xfs_dir3_leaf_check(dp, save_blk->bp);
	xfs_dir3_leaf_check(dp, drop_blk->bp);
पूर्ण

/*
 * Add a new data block to the directory at the मुक्त space index that the caller
 * has specअगरied.
 */
अटल पूर्णांक
xfs_dir2_node_add_datablk(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_da_state_blk	*fblk,
	xfs_dir2_db_t		*dbno,
	काष्ठा xfs_buf		**dbpp,
	काष्ठा xfs_buf		**fbpp,
	काष्ठा xfs_dir3_icमुक्त_hdr *hdr,
	पूर्णांक			*findex)
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_trans	*tp = args->trans;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	काष्ठा xfs_dir2_data_मुक्त *bf;
	xfs_dir2_db_t		fbno;
	काष्ठा xfs_buf		*fbp;
	काष्ठा xfs_buf		*dbp;
	पूर्णांक			error;

	/* Not allowed to allocate, वापस failure. */
	अगर (args->total == 0)
		वापस -ENOSPC;

	/* Allocate and initialize the new data block.  */
	error = xfs_dir2_grow_inode(args, XFS_सूची2_DATA_SPACE, dbno);
	अगर (error)
		वापस error;
	error = xfs_dir3_data_init(args, *dbno, &dbp);
	अगर (error)
		वापस error;

	/*
	 * Get the मुक्तspace block corresponding to the data block
	 * that was just allocated.
	 */
	fbno = xfs_dir2_db_to_fdb(args->geo, *dbno);
	error = xfs_dir2_मुक्त_try_पढ़ो(tp, dp,
			       xfs_dir2_db_to_da(args->geo, fbno), &fbp);
	अगर (error)
		वापस error;

	/*
	 * If there wasn't a मुक्तspace block, the पढ़ो will
	 * वापस a शून्य fbp.  Allocate and initialize a new one.
	 */
	अगर (!fbp) अणु
		error = xfs_dir2_grow_inode(args, XFS_सूची2_FREE_SPACE, &fbno);
		अगर (error)
			वापस error;

		अगर (XFS_IS_CORRUPT(mp,
				   xfs_dir2_db_to_fdb(args->geo, *dbno) !=
				   fbno)) अणु
			xfs_alert(mp,
"%s: dir ino %llu needed freesp block %lld for data block %lld, got %lld",
				__func__, (अचिन्हित दीर्घ दीर्घ)dp->i_ino,
				(दीर्घ दीर्घ)xfs_dir2_db_to_fdb(args->geo, *dbno),
				(दीर्घ दीर्घ)*dbno, (दीर्घ दीर्घ)fbno);
			अगर (fblk) अणु
				xfs_alert(mp,
			" fblk "PTR_FMT" blkno %llu index %d magic 0x%x",
					fblk, (अचिन्हित दीर्घ दीर्घ)fblk->blkno,
					fblk->index, fblk->magic);
			पूर्ण अन्यथा अणु
				xfs_alert(mp, " ... fblk is NULL");
			पूर्ण
			वापस -EFSCORRUPTED;
		पूर्ण

		/* Get a buffer क्रम the new block. */
		error = xfs_dir3_मुक्त_get_buf(args, fbno, &fbp);
		अगर (error)
			वापस error;
		xfs_dir2_मुक्त_hdr_from_disk(mp, hdr, fbp->b_addr);

		/* Remember the first slot as our empty slot. */
		hdr->firstdb = (fbno - xfs_dir2_byte_to_db(args->geo,
							XFS_सूची2_FREE_OFFSET)) *
				args->geo->मुक्त_max_bests;
	पूर्ण अन्यथा अणु
		xfs_dir2_मुक्त_hdr_from_disk(mp, hdr, fbp->b_addr);
	पूर्ण

	/* Set the मुक्तspace block index from the data block number. */
	*findex = xfs_dir2_db_to_fdindex(args->geo, *dbno);

	/* Extend the मुक्तspace table अगर the new data block is off the end. */
	अगर (*findex >= hdr->nvalid) अणु
		ASSERT(*findex < args->geo->मुक्त_max_bests);
		hdr->nvalid = *findex + 1;
		hdr->bests[*findex] = cpu_to_be16(शून्यDATAOFF);
	पूर्ण

	/*
	 * If this entry was क्रम an empty data block (this should always be
	 * true) then update the header.
	 */
	अगर (hdr->bests[*findex] == cpu_to_be16(शून्यDATAOFF)) अणु
		hdr->nused++;
		xfs_dir2_मुक्त_hdr_to_disk(mp, fbp->b_addr, hdr);
		xfs_dir2_मुक्त_log_header(args, fbp);
	पूर्ण

	/* Update the मुक्तspace value क्रम the new block in the table. */
	bf = xfs_dir2_data_bestमुक्त_p(mp, dbp->b_addr);
	hdr->bests[*findex] = bf[0].length;

	*dbpp = dbp;
	*fbpp = fbp;
	वापस 0;
पूर्ण

अटल पूर्णांक
xfs_dir2_node_find_मुक्तblk(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_da_state_blk	*fblk,
	xfs_dir2_db_t		*dbnop,
	काष्ठा xfs_buf		**fbpp,
	काष्ठा xfs_dir3_icमुक्त_hdr *hdr,
	पूर्णांक			*findexp,
	पूर्णांक			length)
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_trans	*tp = args->trans;
	काष्ठा xfs_buf		*fbp = शून्य;
	xfs_dir2_db_t		firstfbno;
	xfs_dir2_db_t		lastfbno;
	xfs_dir2_db_t		अगरbno = -1;
	xfs_dir2_db_t		dbno = -1;
	xfs_dir2_db_t		fbno;
	xfs_fileoff_t		fo;
	पूर्णांक			findex = 0;
	पूर्णांक			error;

	/*
	 * If we came in with a मुक्तspace block that means that lookup
	 * found an entry with our hash value.  This is the मुक्तspace
	 * block क्रम that data entry.
	 */
	अगर (fblk) अणु
		fbp = fblk->bp;
		findex = fblk->index;
		xfs_dir2_मुक्त_hdr_from_disk(dp->i_mount, hdr, fbp->b_addr);
		अगर (findex >= 0) अणु
			/* caller alपढ़ोy found the मुक्तspace क्रम us. */
			ASSERT(findex < hdr->nvalid);
			ASSERT(be16_to_cpu(hdr->bests[findex]) != शून्यDATAOFF);
			ASSERT(be16_to_cpu(hdr->bests[findex]) >= length);
			dbno = hdr->firstdb + findex;
			जाओ found_block;
		पूर्ण

		/*
		 * The data block looked at didn't have enough room.
		 * We'll start at the beginning of the मुक्तspace entries.
		 */
		अगरbno = fblk->blkno;
		xfs_trans_brअन्यथा(tp, fbp);
		fbp = शून्य;
		fblk->bp = शून्य;
	पूर्ण

	/*
	 * If we करोn't have a data block yet, we're going to scan the मुक्तspace
	 * data क्रम a data block with enough मुक्त space in it.
	 */
	error = xfs_bmap_last_offset(dp, &fo, XFS_DATA_FORK);
	अगर (error)
		वापस error;
	lastfbno = xfs_dir2_da_to_db(args->geo, (xfs_dablk_t)fo);
	firstfbno = xfs_dir2_byte_to_db(args->geo, XFS_सूची2_FREE_OFFSET);

	क्रम (fbno = lastfbno - 1; fbno >= firstfbno; fbno--) अणु
		/* If it's अगरbno we alपढ़ोy looked at it. */
		अगर (fbno == अगरbno)
			जारी;

		/*
		 * Read the block.  There can be holes in the मुक्तspace blocks,
		 * so this might not succeed.  This should be really rare, so
		 * there's no reason to aव्योम it.
		 */
		error = xfs_dir2_मुक्त_try_पढ़ो(tp, dp,
				xfs_dir2_db_to_da(args->geo, fbno),
				&fbp);
		अगर (error)
			वापस error;
		अगर (!fbp)
			जारी;

		xfs_dir2_मुक्त_hdr_from_disk(dp->i_mount, hdr, fbp->b_addr);

		/* Scan the मुक्त entry array क्रम a large enough मुक्त space. */
		क्रम (findex = hdr->nvalid - 1; findex >= 0; findex--) अणु
			अगर (be16_to_cpu(hdr->bests[findex]) != शून्यDATAOFF &&
			    be16_to_cpu(hdr->bests[findex]) >= length) अणु
				dbno = hdr->firstdb + findex;
				जाओ found_block;
			पूर्ण
		पूर्ण

		/* Didn't find मुक्त space, go on to next मुक्त block */
		xfs_trans_brअन्यथा(tp, fbp);
	पूर्ण

found_block:
	*dbnop = dbno;
	*fbpp = fbp;
	*findexp = findex;
	वापस 0;
पूर्ण

/*
 * Add the data entry क्रम a node-क्रमmat directory name addition.
 * The leaf entry is added in xfs_dir2_leafn_add.
 * We may enter with a मुक्तspace block that the lookup found.
 */
अटल पूर्णांक
xfs_dir2_node_addname_पूर्णांक(
	काष्ठा xfs_da_args	*args,		/* operation arguments */
	काष्ठा xfs_da_state_blk	*fblk)		/* optional मुक्तspace block */
अणु
	काष्ठा xfs_dir2_data_unused *dup;	/* data unused entry poपूर्णांकer */
	काष्ठा xfs_dir2_data_entry *dep;	/* data entry poपूर्णांकer */
	काष्ठा xfs_dir2_data_hdr *hdr;		/* data block header */
	काष्ठा xfs_dir2_data_मुक्त *bf;
	काष्ठा xfs_trans	*tp = args->trans;
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_dir3_icमुक्त_hdr मुक्तhdr;
	काष्ठा xfs_buf		*dbp;		/* data block buffer */
	काष्ठा xfs_buf		*fbp;		/* मुक्तspace buffer */
	xfs_dir2_data_aoff_t	aoff;
	xfs_dir2_db_t		dbno;		/* data block number */
	पूर्णांक			error;		/* error वापस value */
	पूर्णांक			findex;		/* मुक्तspace entry index */
	पूर्णांक			length;		/* length of the new entry */
	पूर्णांक			logमुक्त = 0;	/* need to log मुक्त entry */
	पूर्णांक			needlog = 0;	/* need to log data header */
	पूर्णांक			needscan = 0;	/* need to rescan data मुक्तs */
	__be16			*tagp;		/* data entry tag poपूर्णांकer */

	length = xfs_dir2_data_entsize(dp->i_mount, args->namelen);
	error = xfs_dir2_node_find_मुक्तblk(args, fblk, &dbno, &fbp, &मुक्तhdr,
					   &findex, length);
	अगर (error)
		वापस error;

	/*
	 * Now we know अगर we must allocate blocks, so अगर we are checking whether
	 * we can insert without allocation then we can वापस now.
	 */
	अगर (args->op_flags & XFS_DA_OP_JUSTCHECK) अणु
		अगर (dbno == -1)
			वापस -ENOSPC;
		वापस 0;
	पूर्ण

	/*
	 * If we करोn't have a data block, we need to allocate one and make
	 * the मुक्तspace entries refer to it.
	 */
	अगर (dbno == -1) अणु
		/* we're going to have to log the मुक्त block index later */
		logमुक्त = 1;
		error = xfs_dir2_node_add_datablk(args, fblk, &dbno, &dbp, &fbp,
						  &मुक्तhdr, &findex);
	पूर्ण अन्यथा अणु
		/* Read the data block in. */
		error = xfs_dir3_data_पढ़ो(tp, dp,
					   xfs_dir2_db_to_da(args->geo, dbno),
					   0, &dbp);
	पूर्ण
	अगर (error)
		वापस error;

	/* setup क्रम data block up now */
	hdr = dbp->b_addr;
	bf = xfs_dir2_data_bestमुक्त_p(dp->i_mount, hdr);
	ASSERT(be16_to_cpu(bf[0].length) >= length);

	/* Poपूर्णांक to the existing unused space. */
	dup = (xfs_dir2_data_unused_t *)
	      ((अक्षर *)hdr + be16_to_cpu(bf[0].offset));

	/* Mark the first part of the unused space, inuse क्रम us. */
	aoff = (xfs_dir2_data_aoff_t)((अक्षर *)dup - (अक्षर *)hdr);
	error = xfs_dir2_data_use_मुक्त(args, dbp, dup, aoff, length,
			&needlog, &needscan);
	अगर (error) अणु
		xfs_trans_brअन्यथा(tp, dbp);
		वापस error;
	पूर्ण

	/* Fill in the new entry and log it. */
	dep = (xfs_dir2_data_entry_t *)dup;
	dep->inumber = cpu_to_be64(args->inumber);
	dep->namelen = args->namelen;
	स_नकल(dep->name, args->name, dep->namelen);
	xfs_dir2_data_put_ftype(dp->i_mount, dep, args->filetype);
	tagp = xfs_dir2_data_entry_tag_p(dp->i_mount, dep);
	*tagp = cpu_to_be16((अक्षर *)dep - (अक्षर *)hdr);
	xfs_dir2_data_log_entry(args, dbp, dep);

	/* Rescan the मुक्तspace and log the data block अगर needed. */
	अगर (needscan)
		xfs_dir2_data_मुक्तscan(dp->i_mount, hdr, &needlog);
	अगर (needlog)
		xfs_dir2_data_log_header(args, dbp);

	/* If the मुक्तspace block entry is now wrong, update it. */
	अगर (मुक्तhdr.bests[findex] != bf[0].length) अणु
		मुक्तhdr.bests[findex] = bf[0].length;
		logमुक्त = 1;
	पूर्ण

	/* Log the मुक्तspace entry अगर needed. */
	अगर (logमुक्त)
		xfs_dir2_मुक्त_log_bests(args, &मुक्तhdr, fbp, findex, findex);

	/* Return the data block and offset in args. */
	args->blkno = (xfs_dablk_t)dbno;
	args->index = be16_to_cpu(*tagp);
	वापस 0;
पूर्ण

/*
 * Top-level node क्रमm directory addname routine.
 */
पूर्णांक						/* error */
xfs_dir2_node_addname(
	xfs_da_args_t		*args)		/* operation arguments */
अणु
	xfs_da_state_blk_t	*blk;		/* leaf block क्रम insert */
	पूर्णांक			error;		/* error वापस value */
	पूर्णांक			rval;		/* sub-वापस value */
	xfs_da_state_t		*state;		/* btree cursor */

	trace_xfs_dir2_node_addname(args);

	/*
	 * Allocate and initialize the state (btree cursor).
	 */
	state = xfs_da_state_alloc(args);
	/*
	 * Look up the name.  We're not supposed to find it, but
	 * this gives us the insertion poपूर्णांक.
	 */
	error = xfs_da3_node_lookup_पूर्णांक(state, &rval);
	अगर (error)
		rval = error;
	अगर (rval != -ENOENT) अणु
		जाओ करोne;
	पूर्ण
	/*
	 * Add the data entry to a data block.
	 * Extravalid is set to a मुक्तblock found by lookup.
	 */
	rval = xfs_dir2_node_addname_पूर्णांक(args,
		state->extravalid ? &state->extrablk : शून्य);
	अगर (rval) अणु
		जाओ करोne;
	पूर्ण
	blk = &state->path.blk[state->path.active - 1];
	ASSERT(blk->magic == XFS_सूची2_LEAFN_MAGIC);
	/*
	 * Add the new leaf entry.
	 */
	rval = xfs_dir2_leafn_add(blk->bp, args, blk->index);
	अगर (rval == 0) अणु
		/*
		 * It worked, fix the hash values up the btree.
		 */
		अगर (!(args->op_flags & XFS_DA_OP_JUSTCHECK))
			xfs_da3_fixhashpath(state, &state->path);
	पूर्ण अन्यथा अणु
		/*
		 * It didn't work, we need to split the leaf block.
		 */
		अगर (args->total == 0) अणु
			ASSERT(rval == -ENOSPC);
			जाओ करोne;
		पूर्ण
		/*
		 * Split the leaf block and insert the new entry.
		 */
		rval = xfs_da3_split(state);
	पूर्ण
करोne:
	xfs_da_state_मुक्त(state);
	वापस rval;
पूर्ण

/*
 * Lookup an entry in a node-क्रमmat directory.
 * All the real work happens in xfs_da3_node_lookup_पूर्णांक.
 * The only real output is the inode number of the entry.
 */
पूर्णांक						/* error */
xfs_dir2_node_lookup(
	xfs_da_args_t	*args)			/* operation arguments */
अणु
	पूर्णांक		error;			/* error वापस value */
	पूर्णांक		i;			/* btree level */
	पूर्णांक		rval;			/* operation वापस value */
	xfs_da_state_t	*state;			/* btree cursor */

	trace_xfs_dir2_node_lookup(args);

	/*
	 * Allocate and initialize the btree cursor.
	 */
	state = xfs_da_state_alloc(args);

	/*
	 * Fill in the path to the entry in the cursor.
	 */
	error = xfs_da3_node_lookup_पूर्णांक(state, &rval);
	अगर (error)
		rval = error;
	अन्यथा अगर (rval == -ENOENT && args->cmpresult == XFS_CMP_CASE) अणु
		/* If a CI match, dup the actual name and वापस -EEXIST */
		xfs_dir2_data_entry_t	*dep;

		dep = (xfs_dir2_data_entry_t *)
			((अक्षर *)state->extrablk.bp->b_addr +
						 state->extrablk.index);
		rval = xfs_dir_cilookup_result(args, dep->name, dep->namelen);
	पूर्ण
	/*
	 * Release the btree blocks and leaf block.
	 */
	क्रम (i = 0; i < state->path.active; i++) अणु
		xfs_trans_brअन्यथा(args->trans, state->path.blk[i].bp);
		state->path.blk[i].bp = शून्य;
	पूर्ण
	/*
	 * Release the data block अगर we have it.
	 */
	अगर (state->extravalid && state->extrablk.bp) अणु
		xfs_trans_brअन्यथा(args->trans, state->extrablk.bp);
		state->extrablk.bp = शून्य;
	पूर्ण
	xfs_da_state_मुक्त(state);
	वापस rval;
पूर्ण

/*
 * Remove an entry from a node-क्रमmat directory.
 */
पूर्णांक						/* error */
xfs_dir2_node_हटाओname(
	काष्ठा xfs_da_args	*args)		/* operation arguments */
अणु
	काष्ठा xfs_da_state_blk	*blk;		/* leaf block */
	पूर्णांक			error;		/* error वापस value */
	पूर्णांक			rval;		/* operation वापस value */
	काष्ठा xfs_da_state	*state;		/* btree cursor */

	trace_xfs_dir2_node_हटाओname(args);

	/*
	 * Allocate and initialize the btree cursor.
	 */
	state = xfs_da_state_alloc(args);

	/* Look up the entry we're deleting, set up the cursor. */
	error = xfs_da3_node_lookup_पूर्णांक(state, &rval);
	अगर (error)
		जाओ out_मुक्त;

	/* Didn't find it, upper layer screwed up. */
	अगर (rval != -EEXIST) अणु
		error = rval;
		जाओ out_मुक्त;
	पूर्ण

	blk = &state->path.blk[state->path.active - 1];
	ASSERT(blk->magic == XFS_सूची2_LEAFN_MAGIC);
	ASSERT(state->extravalid);
	/*
	 * Remove the leaf and data entries.
	 * Extrablk refers to the data block.
	 */
	error = xfs_dir2_leafn_हटाओ(args, blk->bp, blk->index,
		&state->extrablk, &rval);
	अगर (error)
		जाओ out_मुक्त;
	/*
	 * Fix the hash values up the btree.
	 */
	xfs_da3_fixhashpath(state, &state->path);
	/*
	 * If we need to join leaf blocks, करो it.
	 */
	अगर (rval && state->path.active > 1)
		error = xfs_da3_join(state);
	/*
	 * If no errors so far, try conversion to leaf क्रमmat.
	 */
	अगर (!error)
		error = xfs_dir2_node_to_leaf(state);
out_मुक्त:
	xfs_da_state_मुक्त(state);
	वापस error;
पूर्ण

/*
 * Replace an entry's inode number in a node-क्रमmat directory.
 */
पूर्णांक						/* error */
xfs_dir2_node_replace(
	xfs_da_args_t		*args)		/* operation arguments */
अणु
	xfs_da_state_blk_t	*blk;		/* leaf block */
	xfs_dir2_data_hdr_t	*hdr;		/* data block header */
	xfs_dir2_data_entry_t	*dep;		/* data entry changed */
	पूर्णांक			error;		/* error वापस value */
	पूर्णांक			i;		/* btree level */
	xfs_ino_t		inum;		/* new inode number */
	पूर्णांक			ftype;		/* new file type */
	पूर्णांक			rval;		/* पूर्णांकernal वापस value */
	xfs_da_state_t		*state;		/* btree cursor */

	trace_xfs_dir2_node_replace(args);

	/*
	 * Allocate and initialize the btree cursor.
	 */
	state = xfs_da_state_alloc(args);

	/*
	 * We have to save new inode number and ftype since
	 * xfs_da3_node_lookup_पूर्णांक() is going to overग_लिखो them
	 */
	inum = args->inumber;
	ftype = args->filetype;

	/*
	 * Lookup the entry to change in the btree.
	 */
	error = xfs_da3_node_lookup_पूर्णांक(state, &rval);
	अगर (error) अणु
		rval = error;
	पूर्ण
	/*
	 * It should be found, since the vnodeops layer has looked it up
	 * and locked it.  But paranoia is good.
	 */
	अगर (rval == -EEXIST) अणु
		काष्ठा xfs_dir3_icleaf_hdr	leafhdr;

		/*
		 * Find the leaf entry.
		 */
		blk = &state->path.blk[state->path.active - 1];
		ASSERT(blk->magic == XFS_सूची2_LEAFN_MAGIC);
		ASSERT(state->extravalid);

		xfs_dir2_leaf_hdr_from_disk(state->mp, &leafhdr,
					    blk->bp->b_addr);
		/*
		 * Poपूर्णांक to the data entry.
		 */
		hdr = state->extrablk.bp->b_addr;
		ASSERT(hdr->magic == cpu_to_be32(XFS_सूची2_DATA_MAGIC) ||
		       hdr->magic == cpu_to_be32(XFS_सूची3_DATA_MAGIC));
		dep = (xfs_dir2_data_entry_t *)
		      ((अक्षर *)hdr +
		       xfs_dir2_dataptr_to_off(args->geo,
				be32_to_cpu(leafhdr.ents[blk->index].address)));
		ASSERT(inum != be64_to_cpu(dep->inumber));
		/*
		 * Fill in the new inode number and log the entry.
		 */
		dep->inumber = cpu_to_be64(inum);
		xfs_dir2_data_put_ftype(state->mp, dep, ftype);
		xfs_dir2_data_log_entry(args, state->extrablk.bp, dep);
		rval = 0;
	पूर्ण
	/*
	 * Didn't find it, and we're holding a data block.  Drop it.
	 */
	अन्यथा अगर (state->extravalid) अणु
		xfs_trans_brअन्यथा(args->trans, state->extrablk.bp);
		state->extrablk.bp = शून्य;
	पूर्ण
	/*
	 * Release all the buffers in the cursor.
	 */
	क्रम (i = 0; i < state->path.active; i++) अणु
		xfs_trans_brअन्यथा(args->trans, state->path.blk[i].bp);
		state->path.blk[i].bp = शून्य;
	पूर्ण
	xfs_da_state_मुक्त(state);
	वापस rval;
पूर्ण

/*
 * Trim off a trailing empty मुक्तspace block.
 * Return (in rvalp) 1 अगर we did it, 0 अगर not.
 */
पूर्णांक						/* error */
xfs_dir2_node_trim_मुक्त(
	xfs_da_args_t		*args,		/* operation arguments */
	xfs_fileoff_t		fo,		/* मुक्त block number */
	पूर्णांक			*rvalp)		/* out: did something */
अणु
	काष्ठा xfs_buf		*bp;		/* मुक्तspace buffer */
	xfs_inode_t		*dp;		/* incore directory inode */
	पूर्णांक			error;		/* error वापस code */
	xfs_dir2_मुक्त_t		*मुक्त;		/* मुक्तspace काष्ठाure */
	xfs_trans_t		*tp;		/* transaction poपूर्णांकer */
	काष्ठा xfs_dir3_icमुक्त_hdr मुक्तhdr;

	dp = args->dp;
	tp = args->trans;

	*rvalp = 0;

	/*
	 * Read the मुक्तspace block.
	 */
	error = xfs_dir2_मुक्त_try_पढ़ो(tp, dp, fo, &bp);
	अगर (error)
		वापस error;
	/*
	 * There can be holes in मुक्तspace.  If fo is a hole, there's
	 * nothing to करो.
	 */
	अगर (!bp)
		वापस 0;
	मुक्त = bp->b_addr;
	xfs_dir2_मुक्त_hdr_from_disk(dp->i_mount, &मुक्तhdr, मुक्त);

	/*
	 * If there are used entries, there's nothing to करो.
	 */
	अगर (मुक्तhdr.nused > 0) अणु
		xfs_trans_brअन्यथा(tp, bp);
		वापस 0;
	पूर्ण
	/*
	 * Blow the block away.
	 */
	error = xfs_dir2_shrink_inode(args,
			xfs_dir2_da_to_db(args->geo, (xfs_dablk_t)fo), bp);
	अगर (error) अणु
		/*
		 * Can't fail with ENOSPC since that only happens with no
		 * space reservation, when अवरोधing up an extent पूर्णांकo two
		 * pieces.  This is the last block of an extent.
		 */
		ASSERT(error != -ENOSPC);
		xfs_trans_brअन्यथा(tp, bp);
		वापस error;
	पूर्ण
	/*
	 * Return that we succeeded.
	 */
	*rvalp = 1;
	वापस 0;
पूर्ण
