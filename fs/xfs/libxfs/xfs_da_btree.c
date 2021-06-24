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
#समावेश "xfs_bit.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_dir2.h"
#समावेश "xfs_dir2_priv.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_attr_leaf.h"
#समावेश "xfs_error.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_log.h"

/*
 * xfs_da_btree.c
 *
 * Routines to implement directories as Btrees of hashed names.
 */

/*========================================================================
 * Function prototypes क्रम the kernel.
 *========================================================================*/

/*
 * Routines used क्रम growing the Btree.
 */
STATIC पूर्णांक xfs_da3_root_split(xfs_da_state_t *state,
					    xfs_da_state_blk_t *existing_root,
					    xfs_da_state_blk_t *new_child);
STATIC पूर्णांक xfs_da3_node_split(xfs_da_state_t *state,
					    xfs_da_state_blk_t *existing_blk,
					    xfs_da_state_blk_t *split_blk,
					    xfs_da_state_blk_t *blk_to_add,
					    पूर्णांक treelevel,
					    पूर्णांक *result);
STATIC व्योम xfs_da3_node_rebalance(xfs_da_state_t *state,
					 xfs_da_state_blk_t *node_blk_1,
					 xfs_da_state_blk_t *node_blk_2);
STATIC व्योम xfs_da3_node_add(xfs_da_state_t *state,
				   xfs_da_state_blk_t *old_node_blk,
				   xfs_da_state_blk_t *new_node_blk);

/*
 * Routines used क्रम shrinking the Btree.
 */
STATIC पूर्णांक xfs_da3_root_join(xfs_da_state_t *state,
					   xfs_da_state_blk_t *root_blk);
STATIC पूर्णांक xfs_da3_node_toosmall(xfs_da_state_t *state, पूर्णांक *retval);
STATIC व्योम xfs_da3_node_हटाओ(xfs_da_state_t *state,
					      xfs_da_state_blk_t *drop_blk);
STATIC व्योम xfs_da3_node_unbalance(xfs_da_state_t *state,
					 xfs_da_state_blk_t *src_node_blk,
					 xfs_da_state_blk_t *dst_node_blk);

/*
 * Utility routines.
 */
STATIC पूर्णांक	xfs_da3_blk_unlink(xfs_da_state_t *state,
				  xfs_da_state_blk_t *drop_blk,
				  xfs_da_state_blk_t *save_blk);


kmem_zone_t *xfs_da_state_zone;	/* anchor क्रम state काष्ठा zone */

/*
 * Allocate a dir-state काष्ठाure.
 * We करोn't put them on the stack since they're large.
 */
काष्ठा xfs_da_state *
xfs_da_state_alloc(
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_da_state	*state;

	state = kmem_cache_zalloc(xfs_da_state_zone, GFP_NOFS | __GFP_NOFAIL);
	state->args = args;
	state->mp = args->dp->i_mount;
	वापस state;
पूर्ण

/*
 * Kill the altpath contents of a da-state काष्ठाure.
 */
STATIC व्योम
xfs_da_state_समाप्त_altpath(xfs_da_state_t *state)
अणु
	पूर्णांक	i;

	क्रम (i = 0; i < state->altpath.active; i++)
		state->altpath.blk[i].bp = शून्य;
	state->altpath.active = 0;
पूर्ण

/*
 * Free a da-state काष्ठाure.
 */
व्योम
xfs_da_state_मुक्त(xfs_da_state_t *state)
अणु
	xfs_da_state_समाप्त_altpath(state);
#अगर_घोषित DEBUG
	स_रखो((अक्षर *)state, 0, माप(*state));
#पूर्ण_अगर /* DEBUG */
	kmem_cache_मुक्त(xfs_da_state_zone, state);
पूर्ण

अटल अंतरभूत पूर्णांक xfs_dabuf_nfsb(काष्ठा xfs_mount *mp, पूर्णांक whichविभाजन)
अणु
	अगर (whichविभाजन == XFS_DATA_FORK)
		वापस mp->m_dir_geo->fsbcount;
	वापस mp->m_attr_geo->fsbcount;
पूर्ण

व्योम
xfs_da3_node_hdr_from_disk(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_da3_icnode_hdr	*to,
	काष्ठा xfs_da_पूर्णांकnode		*from)
अणु
	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		काष्ठा xfs_da3_पूर्णांकnode	*from3 = (काष्ठा xfs_da3_पूर्णांकnode *)from;

		to->क्रमw = be32_to_cpu(from3->hdr.info.hdr.क्रमw);
		to->back = be32_to_cpu(from3->hdr.info.hdr.back);
		to->magic = be16_to_cpu(from3->hdr.info.hdr.magic);
		to->count = be16_to_cpu(from3->hdr.__count);
		to->level = be16_to_cpu(from3->hdr.__level);
		to->btree = from3->__btree;
		ASSERT(to->magic == XFS_DA3_NODE_MAGIC);
	पूर्ण अन्यथा अणु
		to->क्रमw = be32_to_cpu(from->hdr.info.क्रमw);
		to->back = be32_to_cpu(from->hdr.info.back);
		to->magic = be16_to_cpu(from->hdr.info.magic);
		to->count = be16_to_cpu(from->hdr.__count);
		to->level = be16_to_cpu(from->hdr.__level);
		to->btree = from->__btree;
		ASSERT(to->magic == XFS_DA_NODE_MAGIC);
	पूर्ण
पूर्ण

व्योम
xfs_da3_node_hdr_to_disk(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_da_पूर्णांकnode		*to,
	काष्ठा xfs_da3_icnode_hdr	*from)
अणु
	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		काष्ठा xfs_da3_पूर्णांकnode	*to3 = (काष्ठा xfs_da3_पूर्णांकnode *)to;

		ASSERT(from->magic == XFS_DA3_NODE_MAGIC);
		to3->hdr.info.hdr.क्रमw = cpu_to_be32(from->क्रमw);
		to3->hdr.info.hdr.back = cpu_to_be32(from->back);
		to3->hdr.info.hdr.magic = cpu_to_be16(from->magic);
		to3->hdr.__count = cpu_to_be16(from->count);
		to3->hdr.__level = cpu_to_be16(from->level);
	पूर्ण अन्यथा अणु
		ASSERT(from->magic == XFS_DA_NODE_MAGIC);
		to->hdr.info.क्रमw = cpu_to_be32(from->क्रमw);
		to->hdr.info.back = cpu_to_be32(from->back);
		to->hdr.info.magic = cpu_to_be16(from->magic);
		to->hdr.__count = cpu_to_be16(from->count);
		to->hdr.__level = cpu_to_be16(from->level);
	पूर्ण
पूर्ण

/*
 * Verअगरy an xfs_da3_blkinfo काष्ठाure. Note that the da3 fields are only
 * accessible on v5 fileप्रणालीs. This header क्रमmat is common across da node,
 * attr leaf and dir leaf blocks.
 */
xfs_failaddr_t
xfs_da3_blkinfo_verअगरy(
	काष्ठा xfs_buf		*bp,
	काष्ठा xfs_da3_blkinfo	*hdr3)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_da_blkinfo	*hdr = &hdr3->hdr;

	अगर (!xfs_verअगरy_magic16(bp, hdr->magic))
		वापस __this_address;

	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		अगर (!uuid_equal(&hdr3->uuid, &mp->m_sb.sb_meta_uuid))
			वापस __this_address;
		अगर (be64_to_cpu(hdr3->blkno) != bp->b_bn)
			वापस __this_address;
		अगर (!xfs_log_check_lsn(mp, be64_to_cpu(hdr3->lsn)))
			वापस __this_address;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल xfs_failaddr_t
xfs_da3_node_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_da_पूर्णांकnode	*hdr = bp->b_addr;
	काष्ठा xfs_da3_icnode_hdr ichdr;
	xfs_failaddr_t		fa;

	xfs_da3_node_hdr_from_disk(mp, &ichdr, hdr);

	fa = xfs_da3_blkinfo_verअगरy(bp, bp->b_addr);
	अगर (fa)
		वापस fa;

	अगर (ichdr.level == 0)
		वापस __this_address;
	अगर (ichdr.level > XFS_DA_NODE_MAXDEPTH)
		वापस __this_address;
	अगर (ichdr.count == 0)
		वापस __this_address;

	/*
	 * we करोn't know अगर the node is क्रम and attribute or directory tree,
	 * so only fail अगर the count is outside both bounds
	 */
	अगर (ichdr.count > mp->m_dir_geo->node_ents &&
	    ichdr.count > mp->m_attr_geo->node_ents)
		वापस __this_address;

	/* XXX: hash order check? */

	वापस शून्य;
पूर्ण

अटल व्योम
xfs_da3_node_ग_लिखो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;
	काष्ठा xfs_da3_node_hdr *hdr3 = bp->b_addr;
	xfs_failaddr_t		fa;

	fa = xfs_da3_node_verअगरy(bp);
	अगर (fa) अणु
		xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
		वापस;
	पूर्ण

	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस;

	अगर (bip)
		hdr3->info.lsn = cpu_to_be64(bip->bli_item.li_lsn);

	xfs_buf_update_cksum(bp, XFS_DA3_NODE_CRC_OFF);
पूर्ण

/*
 * leaf/node क्रमmat detection on trees is sketchy, so a node पढ़ो can be करोne on
 * leaf level blocks when detection identअगरies the tree as a node क्रमmat tree
 * incorrectly. In this हाल, we need to swap the verअगरier to match the correct
 * क्रमmat of the block being पढ़ो.
 */
अटल व्योम
xfs_da3_node_पढ़ो_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_da_blkinfo	*info = bp->b_addr;
	xfs_failaddr_t		fa;

	चयन (be16_to_cpu(info->magic)) अणु
		हाल XFS_DA3_NODE_MAGIC:
			अगर (!xfs_buf_verअगरy_cksum(bp, XFS_DA3_NODE_CRC_OFF)) अणु
				xfs_verअगरier_error(bp, -EFSBADCRC,
						__this_address);
				अवरोध;
			पूर्ण
			/* fall through */
		हाल XFS_DA_NODE_MAGIC:
			fa = xfs_da3_node_verअगरy(bp);
			अगर (fa)
				xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
			वापस;
		हाल XFS_ATTR_LEAF_MAGIC:
		हाल XFS_ATTR3_LEAF_MAGIC:
			bp->b_ops = &xfs_attr3_leaf_buf_ops;
			bp->b_ops->verअगरy_पढ़ो(bp);
			वापस;
		हाल XFS_सूची2_LEAFN_MAGIC:
		हाल XFS_सूची3_LEAFN_MAGIC:
			bp->b_ops = &xfs_dir3_leafn_buf_ops;
			bp->b_ops->verअगरy_पढ़ो(bp);
			वापस;
		शेष:
			xfs_verअगरier_error(bp, -EFSCORRUPTED, __this_address);
			अवरोध;
	पूर्ण
पूर्ण

/* Verअगरy the काष्ठाure of a da3 block. */
अटल xfs_failaddr_t
xfs_da3_node_verअगरy_काष्ठा(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_da_blkinfo	*info = bp->b_addr;

	चयन (be16_to_cpu(info->magic)) अणु
	हाल XFS_DA3_NODE_MAGIC:
	हाल XFS_DA_NODE_MAGIC:
		वापस xfs_da3_node_verअगरy(bp);
	हाल XFS_ATTR_LEAF_MAGIC:
	हाल XFS_ATTR3_LEAF_MAGIC:
		bp->b_ops = &xfs_attr3_leaf_buf_ops;
		वापस bp->b_ops->verअगरy_काष्ठा(bp);
	हाल XFS_सूची2_LEAFN_MAGIC:
	हाल XFS_सूची3_LEAFN_MAGIC:
		bp->b_ops = &xfs_dir3_leafn_buf_ops;
		वापस bp->b_ops->verअगरy_काष्ठा(bp);
	शेष:
		वापस __this_address;
	पूर्ण
पूर्ण

स्थिर काष्ठा xfs_buf_ops xfs_da3_node_buf_ops = अणु
	.name = "xfs_da3_node",
	.magic16 = अणु cpu_to_be16(XFS_DA_NODE_MAGIC),
		     cpu_to_be16(XFS_DA3_NODE_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_da3_node_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_da3_node_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा = xfs_da3_node_verअगरy_काष्ठा,
पूर्ण;

अटल पूर्णांक
xfs_da3_node_set_type(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_da_blkinfo	*info = bp->b_addr;

	चयन (be16_to_cpu(info->magic)) अणु
	हाल XFS_DA_NODE_MAGIC:
	हाल XFS_DA3_NODE_MAGIC:
		xfs_trans_buf_set_type(tp, bp, XFS_BLFT_DA_NODE_BUF);
		वापस 0;
	हाल XFS_ATTR_LEAF_MAGIC:
	हाल XFS_ATTR3_LEAF_MAGIC:
		xfs_trans_buf_set_type(tp, bp, XFS_BLFT_ATTR_LEAF_BUF);
		वापस 0;
	हाल XFS_सूची2_LEAFN_MAGIC:
	हाल XFS_सूची3_LEAFN_MAGIC:
		xfs_trans_buf_set_type(tp, bp, XFS_BLFT_सूची_LEAFN_BUF);
		वापस 0;
	शेष:
		XFS_CORRUPTION_ERROR(__func__, XFS_ERRLEVEL_LOW, tp->t_mountp,
				info, माप(*info));
		xfs_trans_brअन्यथा(tp, bp);
		वापस -EFSCORRUPTED;
	पूर्ण
पूर्ण

पूर्णांक
xfs_da3_node_पढ़ो(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*dp,
	xfs_dablk_t		bno,
	काष्ठा xfs_buf		**bpp,
	पूर्णांक			whichविभाजन)
अणु
	पूर्णांक			error;

	error = xfs_da_पढ़ो_buf(tp, dp, bno, 0, bpp, whichविभाजन,
			&xfs_da3_node_buf_ops);
	अगर (error || !*bpp || !tp)
		वापस error;
	वापस xfs_da3_node_set_type(tp, *bpp);
पूर्ण

पूर्णांक
xfs_da3_node_पढ़ो_mapped(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*dp,
	xfs_daddr_t		mappedbno,
	काष्ठा xfs_buf		**bpp,
	पूर्णांक			whichविभाजन)
अणु
	काष्ठा xfs_mount	*mp = dp->i_mount;
	पूर्णांक			error;

	error = xfs_trans_पढ़ो_buf(mp, tp, mp->m_ddev_targp, mappedbno,
			XFS_FSB_TO_BB(mp, xfs_dabuf_nfsb(mp, whichविभाजन)), 0,
			bpp, &xfs_da3_node_buf_ops);
	अगर (error || !*bpp)
		वापस error;

	अगर (whichविभाजन == XFS_ATTR_FORK)
		xfs_buf_set_ref(*bpp, XFS_ATTR_BTREE_REF);
	अन्यथा
		xfs_buf_set_ref(*bpp, XFS_सूची_BTREE_REF);

	अगर (!tp)
		वापस 0;
	वापस xfs_da3_node_set_type(tp, *bpp);
पूर्ण

/*========================================================================
 * Routines used क्रम growing the Btree.
 *========================================================================*/

/*
 * Create the initial contents of an पूर्णांकermediate node.
 */
पूर्णांक
xfs_da3_node_create(
	काष्ठा xfs_da_args	*args,
	xfs_dablk_t		blkno,
	पूर्णांक			level,
	काष्ठा xfs_buf		**bpp,
	पूर्णांक			whichविभाजन)
अणु
	काष्ठा xfs_da_पूर्णांकnode	*node;
	काष्ठा xfs_trans	*tp = args->trans;
	काष्ठा xfs_mount	*mp = tp->t_mountp;
	काष्ठा xfs_da3_icnode_hdr ichdr = अणु0पूर्ण;
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;
	काष्ठा xfs_inode	*dp = args->dp;

	trace_xfs_da_node_create(args);
	ASSERT(level <= XFS_DA_NODE_MAXDEPTH);

	error = xfs_da_get_buf(tp, dp, blkno, &bp, whichविभाजन);
	अगर (error)
		वापस error;
	bp->b_ops = &xfs_da3_node_buf_ops;
	xfs_trans_buf_set_type(tp, bp, XFS_BLFT_DA_NODE_BUF);
	node = bp->b_addr;

	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		काष्ठा xfs_da3_node_hdr *hdr3 = bp->b_addr;

		स_रखो(hdr3, 0, माप(काष्ठा xfs_da3_node_hdr));
		ichdr.magic = XFS_DA3_NODE_MAGIC;
		hdr3->info.blkno = cpu_to_be64(bp->b_bn);
		hdr3->info.owner = cpu_to_be64(args->dp->i_ino);
		uuid_copy(&hdr3->info.uuid, &mp->m_sb.sb_meta_uuid);
	पूर्ण अन्यथा अणु
		ichdr.magic = XFS_DA_NODE_MAGIC;
	पूर्ण
	ichdr.level = level;

	xfs_da3_node_hdr_to_disk(dp->i_mount, node, &ichdr);
	xfs_trans_log_buf(tp, bp,
		XFS_DA_LOGRANGE(node, &node->hdr, args->geo->node_hdr_size));

	*bpp = bp;
	वापस 0;
पूर्ण

/*
 * Split a leaf node, rebalance, then possibly split
 * पूर्णांकermediate nodes, rebalance, etc.
 */
पूर्णांक							/* error */
xfs_da3_split(
	काष्ठा xfs_da_state	*state)
अणु
	काष्ठा xfs_da_state_blk	*oldblk;
	काष्ठा xfs_da_state_blk	*newblk;
	काष्ठा xfs_da_state_blk	*addblk;
	काष्ठा xfs_da_पूर्णांकnode	*node;
	पूर्णांक			max;
	पूर्णांक			action = 0;
	पूर्णांक			error;
	पूर्णांक			i;

	trace_xfs_da_split(state->args);

	/*
	 * Walk back up the tree splitting/inserting/adjusting as necessary.
	 * If we need to insert and there isn't room, split the node, then
	 * decide which fragment to insert the new block from below पूर्णांकo.
	 * Note that we may split the root this way, but we need more fixup.
	 */
	max = state->path.active - 1;
	ASSERT((max >= 0) && (max < XFS_DA_NODE_MAXDEPTH));
	ASSERT(state->path.blk[max].magic == XFS_ATTR_LEAF_MAGIC ||
	       state->path.blk[max].magic == XFS_सूची2_LEAFN_MAGIC);

	addblk = &state->path.blk[max];		/* initial dummy value */
	क्रम (i = max; (i >= 0) && addblk; state->path.active--, i--) अणु
		oldblk = &state->path.blk[i];
		newblk = &state->altpath.blk[i];

		/*
		 * If a leaf node then
		 *     Allocate a new leaf node, then rebalance across them.
		 * अन्यथा अगर an पूर्णांकermediate node then
		 *     We split on the last layer, must we split the node?
		 */
		चयन (oldblk->magic) अणु
		हाल XFS_ATTR_LEAF_MAGIC:
			error = xfs_attr3_leaf_split(state, oldblk, newblk);
			अगर ((error != 0) && (error != -ENOSPC)) अणु
				वापस error;	/* GROT: attr is inconsistent */
			पूर्ण
			अगर (!error) अणु
				addblk = newblk;
				अवरोध;
			पूर्ण
			/*
			 * Entry wouldn't fit, split the leaf again. The new
			 * extrablk will be consumed by xfs_da3_node_split अगर
			 * the node is split.
			 */
			state->extravalid = 1;
			अगर (state->inleaf) अणु
				state->extraafter = 0;	/* beक्रमe newblk */
				trace_xfs_attr_leaf_split_beक्रमe(state->args);
				error = xfs_attr3_leaf_split(state, oldblk,
							    &state->extrablk);
			पूर्ण अन्यथा अणु
				state->extraafter = 1;	/* after newblk */
				trace_xfs_attr_leaf_split_after(state->args);
				error = xfs_attr3_leaf_split(state, newblk,
							    &state->extrablk);
			पूर्ण
			अगर (error)
				वापस error;	/* GROT: attr inconsistent */
			addblk = newblk;
			अवरोध;
		हाल XFS_सूची2_LEAFN_MAGIC:
			error = xfs_dir2_leafn_split(state, oldblk, newblk);
			अगर (error)
				वापस error;
			addblk = newblk;
			अवरोध;
		हाल XFS_DA_NODE_MAGIC:
			error = xfs_da3_node_split(state, oldblk, newblk, addblk,
							 max - i, &action);
			addblk->bp = शून्य;
			अगर (error)
				वापस error;	/* GROT: dir is inconsistent */
			/*
			 * Record the newly split block क्रम the next समय thru?
			 */
			अगर (action)
				addblk = newblk;
			अन्यथा
				addblk = शून्य;
			अवरोध;
		पूर्ण

		/*
		 * Update the btree to show the new hashval क्रम this child.
		 */
		xfs_da3_fixhashpath(state, &state->path);
	पूर्ण
	अगर (!addblk)
		वापस 0;

	/*
	 * xfs_da3_node_split() should have consumed any extra blocks we added
	 * during a द्विगुन leaf split in the attr विभाजन. This is guaranteed as
	 * we can't be here अगर the attr विभाजन only has a single leaf block.
	 */
	ASSERT(state->extravalid == 0 ||
	       state->path.blk[max].magic == XFS_सूची2_LEAFN_MAGIC);

	/*
	 * Split the root node.
	 */
	ASSERT(state->path.active == 0);
	oldblk = &state->path.blk[0];
	error = xfs_da3_root_split(state, oldblk, addblk);
	अगर (error)
		जाओ out;

	/*
	 * Update poपूर्णांकers to the node which used to be block 0 and just got
	 * bumped because of the addition of a new root node.  Note that the
	 * original block 0 could be at any position in the list of blocks in
	 * the tree.
	 *
	 * Note: the magic numbers and sibling poपूर्णांकers are in the same physical
	 * place क्रम both v2 and v3 headers (by design). Hence it करोesn't matter
	 * which version of the xfs_da_पूर्णांकnode काष्ठाure we use here as the
	 * result will be the same using either काष्ठाure.
	 */
	node = oldblk->bp->b_addr;
	अगर (node->hdr.info.क्रमw) अणु
		अगर (be32_to_cpu(node->hdr.info.क्रमw) != addblk->blkno) अणु
			xfs_buf_mark_corrupt(oldblk->bp);
			error = -EFSCORRUPTED;
			जाओ out;
		पूर्ण
		node = addblk->bp->b_addr;
		node->hdr.info.back = cpu_to_be32(oldblk->blkno);
		xfs_trans_log_buf(state->args->trans, addblk->bp,
				  XFS_DA_LOGRANGE(node, &node->hdr.info,
				  माप(node->hdr.info)));
	पूर्ण
	node = oldblk->bp->b_addr;
	अगर (node->hdr.info.back) अणु
		अगर (be32_to_cpu(node->hdr.info.back) != addblk->blkno) अणु
			xfs_buf_mark_corrupt(oldblk->bp);
			error = -EFSCORRUPTED;
			जाओ out;
		पूर्ण
		node = addblk->bp->b_addr;
		node->hdr.info.क्रमw = cpu_to_be32(oldblk->blkno);
		xfs_trans_log_buf(state->args->trans, addblk->bp,
				  XFS_DA_LOGRANGE(node, &node->hdr.info,
				  माप(node->hdr.info)));
	पूर्ण
out:
	addblk->bp = शून्य;
	वापस error;
पूर्ण

/*
 * Split the root.  We have to create a new root and poपूर्णांक to the two
 * parts (the split old root) that we just created.  Copy block zero to
 * the खातापूर्ण, extending the inode in process.
 */
STATIC पूर्णांक						/* error */
xfs_da3_root_split(
	काष्ठा xfs_da_state	*state,
	काष्ठा xfs_da_state_blk	*blk1,
	काष्ठा xfs_da_state_blk	*blk2)
अणु
	काष्ठा xfs_da_पूर्णांकnode	*node;
	काष्ठा xfs_da_पूर्णांकnode	*oldroot;
	काष्ठा xfs_da_node_entry *btree;
	काष्ठा xfs_da3_icnode_hdr nodehdr;
	काष्ठा xfs_da_args	*args;
	काष्ठा xfs_buf		*bp;
	काष्ठा xfs_inode	*dp;
	काष्ठा xfs_trans	*tp;
	काष्ठा xfs_dir2_leaf	*leaf;
	xfs_dablk_t		blkno;
	पूर्णांक			level;
	पूर्णांक			error;
	पूर्णांक			size;

	trace_xfs_da_root_split(state->args);

	/*
	 * Copy the existing (incorrect) block from the root node position
	 * to a मुक्त space somewhere.
	 */
	args = state->args;
	error = xfs_da_grow_inode(args, &blkno);
	अगर (error)
		वापस error;

	dp = args->dp;
	tp = args->trans;
	error = xfs_da_get_buf(tp, dp, blkno, &bp, args->whichविभाजन);
	अगर (error)
		वापस error;
	node = bp->b_addr;
	oldroot = blk1->bp->b_addr;
	अगर (oldroot->hdr.info.magic == cpu_to_be16(XFS_DA_NODE_MAGIC) ||
	    oldroot->hdr.info.magic == cpu_to_be16(XFS_DA3_NODE_MAGIC)) अणु
		काष्ठा xfs_da3_icnode_hdr icnodehdr;

		xfs_da3_node_hdr_from_disk(dp->i_mount, &icnodehdr, oldroot);
		btree = icnodehdr.btree;
		size = (पूर्णांक)((अक्षर *)&btree[icnodehdr.count] - (अक्षर *)oldroot);
		level = icnodehdr.level;

		/*
		 * we are about to copy oldroot to bp, so set up the type
		 * of bp जबतक we know exactly what it will be.
		 */
		xfs_trans_buf_set_type(tp, bp, XFS_BLFT_DA_NODE_BUF);
	पूर्ण अन्यथा अणु
		काष्ठा xfs_dir3_icleaf_hdr leafhdr;

		leaf = (xfs_dir2_leaf_t *)oldroot;
		xfs_dir2_leaf_hdr_from_disk(dp->i_mount, &leafhdr, leaf);

		ASSERT(leafhdr.magic == XFS_सूची2_LEAFN_MAGIC ||
		       leafhdr.magic == XFS_सूची3_LEAFN_MAGIC);
		size = (पूर्णांक)((अक्षर *)&leafhdr.ents[leafhdr.count] -
			(अक्षर *)leaf);
		level = 0;

		/*
		 * we are about to copy oldroot to bp, so set up the type
		 * of bp जबतक we know exactly what it will be.
		 */
		xfs_trans_buf_set_type(tp, bp, XFS_BLFT_सूची_LEAFN_BUF);
	पूर्ण

	/*
	 * we can copy most of the inक्रमmation in the node from one block to
	 * another, but क्रम CRC enabled headers we have to make sure that the
	 * block specअगरic identअगरiers are kept पूर्णांकact. We update the buffer
	 * directly क्रम this.
	 */
	स_नकल(node, oldroot, size);
	अगर (oldroot->hdr.info.magic == cpu_to_be16(XFS_DA3_NODE_MAGIC) ||
	    oldroot->hdr.info.magic == cpu_to_be16(XFS_सूची3_LEAFN_MAGIC)) अणु
		काष्ठा xfs_da3_पूर्णांकnode *node3 = (काष्ठा xfs_da3_पूर्णांकnode *)node;

		node3->hdr.info.blkno = cpu_to_be64(bp->b_bn);
	पूर्ण
	xfs_trans_log_buf(tp, bp, 0, size - 1);

	bp->b_ops = blk1->bp->b_ops;
	xfs_trans_buf_copy_type(bp, blk1->bp);
	blk1->bp = bp;
	blk1->blkno = blkno;

	/*
	 * Set up the new root node.
	 */
	error = xfs_da3_node_create(args,
		(args->whichविभाजन == XFS_DATA_FORK) ? args->geo->leafblk : 0,
		level + 1, &bp, args->whichविभाजन);
	अगर (error)
		वापस error;

	node = bp->b_addr;
	xfs_da3_node_hdr_from_disk(dp->i_mount, &nodehdr, node);
	btree = nodehdr.btree;
	btree[0].hashval = cpu_to_be32(blk1->hashval);
	btree[0].beक्रमe = cpu_to_be32(blk1->blkno);
	btree[1].hashval = cpu_to_be32(blk2->hashval);
	btree[1].beक्रमe = cpu_to_be32(blk2->blkno);
	nodehdr.count = 2;
	xfs_da3_node_hdr_to_disk(dp->i_mount, node, &nodehdr);

#अगर_घोषित DEBUG
	अगर (oldroot->hdr.info.magic == cpu_to_be16(XFS_सूची2_LEAFN_MAGIC) ||
	    oldroot->hdr.info.magic == cpu_to_be16(XFS_सूची3_LEAFN_MAGIC)) अणु
		ASSERT(blk1->blkno >= args->geo->leafblk &&
		       blk1->blkno < args->geo->मुक्तblk);
		ASSERT(blk2->blkno >= args->geo->leafblk &&
		       blk2->blkno < args->geo->मुक्तblk);
	पूर्ण
#पूर्ण_अगर

	/* Header is alपढ़ोy logged by xfs_da_node_create */
	xfs_trans_log_buf(tp, bp,
		XFS_DA_LOGRANGE(node, btree, माप(xfs_da_node_entry_t) * 2));

	वापस 0;
पूर्ण

/*
 * Split the node, rebalance, then add the new entry.
 */
STATIC पूर्णांक						/* error */
xfs_da3_node_split(
	काष्ठा xfs_da_state	*state,
	काष्ठा xfs_da_state_blk	*oldblk,
	काष्ठा xfs_da_state_blk	*newblk,
	काष्ठा xfs_da_state_blk	*addblk,
	पूर्णांक			treelevel,
	पूर्णांक			*result)
अणु
	काष्ठा xfs_da_पूर्णांकnode	*node;
	काष्ठा xfs_da3_icnode_hdr nodehdr;
	xfs_dablk_t		blkno;
	पूर्णांक			newcount;
	पूर्णांक			error;
	पूर्णांक			useextra;
	काष्ठा xfs_inode	*dp = state->args->dp;

	trace_xfs_da_node_split(state->args);

	node = oldblk->bp->b_addr;
	xfs_da3_node_hdr_from_disk(dp->i_mount, &nodehdr, node);

	/*
	 * With V2 dirs the extra block is data or मुक्तspace.
	 */
	useextra = state->extravalid && state->args->whichविभाजन == XFS_ATTR_FORK;
	newcount = 1 + useextra;
	/*
	 * Do we have to split the node?
	 */
	अगर (nodehdr.count + newcount > state->args->geo->node_ents) अणु
		/*
		 * Allocate a new node, add to the करोubly linked chain of
		 * nodes, then move some of our excess entries पूर्णांकo it.
		 */
		error = xfs_da_grow_inode(state->args, &blkno);
		अगर (error)
			वापस error;	/* GROT: dir is inconsistent */

		error = xfs_da3_node_create(state->args, blkno, treelevel,
					   &newblk->bp, state->args->whichविभाजन);
		अगर (error)
			वापस error;	/* GROT: dir is inconsistent */
		newblk->blkno = blkno;
		newblk->magic = XFS_DA_NODE_MAGIC;
		xfs_da3_node_rebalance(state, oldblk, newblk);
		error = xfs_da3_blk_link(state, oldblk, newblk);
		अगर (error)
			वापस error;
		*result = 1;
	पूर्ण अन्यथा अणु
		*result = 0;
	पूर्ण

	/*
	 * Insert the new entry(s) पूर्णांकo the correct block
	 * (updating last hashval in the process).
	 *
	 * xfs_da3_node_add() inserts BEFORE the given index,
	 * and as a result of using node_lookup_पूर्णांक() we always
	 * poपूर्णांक to a valid entry (not after one), but a split
	 * operation always results in a new block whose hashvals
	 * FOLLOW the current block.
	 *
	 * If we had द्विगुन-split op below us, then add the extra block too.
	 */
	node = oldblk->bp->b_addr;
	xfs_da3_node_hdr_from_disk(dp->i_mount, &nodehdr, node);
	अगर (oldblk->index <= nodehdr.count) अणु
		oldblk->index++;
		xfs_da3_node_add(state, oldblk, addblk);
		अगर (useextra) अणु
			अगर (state->extraafter)
				oldblk->index++;
			xfs_da3_node_add(state, oldblk, &state->extrablk);
			state->extravalid = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		newblk->index++;
		xfs_da3_node_add(state, newblk, addblk);
		अगर (useextra) अणु
			अगर (state->extraafter)
				newblk->index++;
			xfs_da3_node_add(state, newblk, &state->extrablk);
			state->extravalid = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Balance the btree elements between two पूर्णांकermediate nodes,
 * usually one full and one empty.
 *
 * NOTE: अगर blk2 is empty, then it will get the upper half of blk1.
 */
STATIC व्योम
xfs_da3_node_rebalance(
	काष्ठा xfs_da_state	*state,
	काष्ठा xfs_da_state_blk	*blk1,
	काष्ठा xfs_da_state_blk	*blk2)
अणु
	काष्ठा xfs_da_पूर्णांकnode	*node1;
	काष्ठा xfs_da_पूर्णांकnode	*node2;
	काष्ठा xfs_da_पूर्णांकnode	*पंचांगpnode;
	काष्ठा xfs_da_node_entry *btree1;
	काष्ठा xfs_da_node_entry *btree2;
	काष्ठा xfs_da_node_entry *btree_s;
	काष्ठा xfs_da_node_entry *btree_d;
	काष्ठा xfs_da3_icnode_hdr nodehdr1;
	काष्ठा xfs_da3_icnode_hdr nodehdr2;
	काष्ठा xfs_trans	*tp;
	पूर्णांक			count;
	पूर्णांक			पंचांगp;
	पूर्णांक			swap = 0;
	काष्ठा xfs_inode	*dp = state->args->dp;

	trace_xfs_da_node_rebalance(state->args);

	node1 = blk1->bp->b_addr;
	node2 = blk2->bp->b_addr;
	xfs_da3_node_hdr_from_disk(dp->i_mount, &nodehdr1, node1);
	xfs_da3_node_hdr_from_disk(dp->i_mount, &nodehdr2, node2);
	btree1 = nodehdr1.btree;
	btree2 = nodehdr2.btree;

	/*
	 * Figure out how many entries need to move, and in which direction.
	 * Swap the nodes around अगर that makes it simpler.
	 */
	अगर (nodehdr1.count > 0 && nodehdr2.count > 0 &&
	    ((be32_to_cpu(btree2[0].hashval) < be32_to_cpu(btree1[0].hashval)) ||
	     (be32_to_cpu(btree2[nodehdr2.count - 1].hashval) <
			be32_to_cpu(btree1[nodehdr1.count - 1].hashval)))) अणु
		पंचांगpnode = node1;
		node1 = node2;
		node2 = पंचांगpnode;
		xfs_da3_node_hdr_from_disk(dp->i_mount, &nodehdr1, node1);
		xfs_da3_node_hdr_from_disk(dp->i_mount, &nodehdr2, node2);
		btree1 = nodehdr1.btree;
		btree2 = nodehdr2.btree;
		swap = 1;
	पूर्ण

	count = (nodehdr1.count - nodehdr2.count) / 2;
	अगर (count == 0)
		वापस;
	tp = state->args->trans;
	/*
	 * Two हालs: high-to-low and low-to-high.
	 */
	अगर (count > 0) अणु
		/*
		 * Move elements in node2 up to make a hole.
		 */
		पंचांगp = nodehdr2.count;
		अगर (पंचांगp > 0) अणु
			पंचांगp *= (uपूर्णांक)माप(xfs_da_node_entry_t);
			btree_s = &btree2[0];
			btree_d = &btree2[count];
			स_हटाओ(btree_d, btree_s, पंचांगp);
		पूर्ण

		/*
		 * Move the req'd B-tree elements from high in node1 to
		 * low in node2.
		 */
		nodehdr2.count += count;
		पंचांगp = count * (uपूर्णांक)माप(xfs_da_node_entry_t);
		btree_s = &btree1[nodehdr1.count - count];
		btree_d = &btree2[0];
		स_नकल(btree_d, btree_s, पंचांगp);
		nodehdr1.count -= count;
	पूर्ण अन्यथा अणु
		/*
		 * Move the req'd B-tree elements from low in node2 to
		 * high in node1.
		 */
		count = -count;
		पंचांगp = count * (uपूर्णांक)माप(xfs_da_node_entry_t);
		btree_s = &btree2[0];
		btree_d = &btree1[nodehdr1.count];
		स_नकल(btree_d, btree_s, पंचांगp);
		nodehdr1.count += count;

		xfs_trans_log_buf(tp, blk1->bp,
			XFS_DA_LOGRANGE(node1, btree_d, पंचांगp));

		/*
		 * Move elements in node2 करोwn to fill the hole.
		 */
		पंचांगp  = nodehdr2.count - count;
		पंचांगp *= (uपूर्णांक)माप(xfs_da_node_entry_t);
		btree_s = &btree2[count];
		btree_d = &btree2[0];
		स_हटाओ(btree_d, btree_s, पंचांगp);
		nodehdr2.count -= count;
	पूर्ण

	/*
	 * Log header of node 1 and all current bits of node 2.
	 */
	xfs_da3_node_hdr_to_disk(dp->i_mount, node1, &nodehdr1);
	xfs_trans_log_buf(tp, blk1->bp,
		XFS_DA_LOGRANGE(node1, &node1->hdr,
				state->args->geo->node_hdr_size));

	xfs_da3_node_hdr_to_disk(dp->i_mount, node2, &nodehdr2);
	xfs_trans_log_buf(tp, blk2->bp,
		XFS_DA_LOGRANGE(node2, &node2->hdr,
				state->args->geo->node_hdr_size +
				(माप(btree2[0]) * nodehdr2.count)));

	/*
	 * Record the last hashval from each block क्रम upward propagation.
	 * (note: करोn't use the swapped node poपूर्णांकers)
	 */
	अगर (swap) अणु
		node1 = blk1->bp->b_addr;
		node2 = blk2->bp->b_addr;
		xfs_da3_node_hdr_from_disk(dp->i_mount, &nodehdr1, node1);
		xfs_da3_node_hdr_from_disk(dp->i_mount, &nodehdr2, node2);
		btree1 = nodehdr1.btree;
		btree2 = nodehdr2.btree;
	पूर्ण
	blk1->hashval = be32_to_cpu(btree1[nodehdr1.count - 1].hashval);
	blk2->hashval = be32_to_cpu(btree2[nodehdr2.count - 1].hashval);

	/*
	 * Adjust the expected index क्रम insertion.
	 */
	अगर (blk1->index >= nodehdr1.count) अणु
		blk2->index = blk1->index - nodehdr1.count;
		blk1->index = nodehdr1.count + 1;	/* make it invalid */
	पूर्ण
पूर्ण

/*
 * Add a new entry to an पूर्णांकermediate node.
 */
STATIC व्योम
xfs_da3_node_add(
	काष्ठा xfs_da_state	*state,
	काष्ठा xfs_da_state_blk	*oldblk,
	काष्ठा xfs_da_state_blk	*newblk)
अणु
	काष्ठा xfs_da_पूर्णांकnode	*node;
	काष्ठा xfs_da3_icnode_hdr nodehdr;
	काष्ठा xfs_da_node_entry *btree;
	पूर्णांक			पंचांगp;
	काष्ठा xfs_inode	*dp = state->args->dp;

	trace_xfs_da_node_add(state->args);

	node = oldblk->bp->b_addr;
	xfs_da3_node_hdr_from_disk(dp->i_mount, &nodehdr, node);
	btree = nodehdr.btree;

	ASSERT(oldblk->index >= 0 && oldblk->index <= nodehdr.count);
	ASSERT(newblk->blkno != 0);
	अगर (state->args->whichविभाजन == XFS_DATA_FORK)
		ASSERT(newblk->blkno >= state->args->geo->leafblk &&
		       newblk->blkno < state->args->geo->मुक्तblk);

	/*
	 * We may need to make some room beक्रमe we insert the new node.
	 */
	पंचांगp = 0;
	अगर (oldblk->index < nodehdr.count) अणु
		पंचांगp = (nodehdr.count - oldblk->index) * (uपूर्णांक)माप(*btree);
		स_हटाओ(&btree[oldblk->index + 1], &btree[oldblk->index], पंचांगp);
	पूर्ण
	btree[oldblk->index].hashval = cpu_to_be32(newblk->hashval);
	btree[oldblk->index].beक्रमe = cpu_to_be32(newblk->blkno);
	xfs_trans_log_buf(state->args->trans, oldblk->bp,
		XFS_DA_LOGRANGE(node, &btree[oldblk->index],
				पंचांगp + माप(*btree)));

	nodehdr.count += 1;
	xfs_da3_node_hdr_to_disk(dp->i_mount, node, &nodehdr);
	xfs_trans_log_buf(state->args->trans, oldblk->bp,
		XFS_DA_LOGRANGE(node, &node->hdr,
				state->args->geo->node_hdr_size));

	/*
	 * Copy the last hash value from the oldblk to propagate upwards.
	 */
	oldblk->hashval = be32_to_cpu(btree[nodehdr.count - 1].hashval);
पूर्ण

/*========================================================================
 * Routines used क्रम shrinking the Btree.
 *========================================================================*/

/*
 * Deallocate an empty leaf node, हटाओ it from its parent,
 * possibly deallocating that block, etc...
 */
पूर्णांक
xfs_da3_join(
	काष्ठा xfs_da_state	*state)
अणु
	काष्ठा xfs_da_state_blk	*drop_blk;
	काष्ठा xfs_da_state_blk	*save_blk;
	पूर्णांक			action = 0;
	पूर्णांक			error;

	trace_xfs_da_join(state->args);

	drop_blk = &state->path.blk[ state->path.active-1 ];
	save_blk = &state->altpath.blk[ state->path.active-1 ];
	ASSERT(state->path.blk[0].magic == XFS_DA_NODE_MAGIC);
	ASSERT(drop_blk->magic == XFS_ATTR_LEAF_MAGIC ||
	       drop_blk->magic == XFS_सूची2_LEAFN_MAGIC);

	/*
	 * Walk back up the tree joining/deallocating as necessary.
	 * When we stop dropping blocks, अवरोध out.
	 */
	क्रम (  ; state->path.active >= 2; drop_blk--, save_blk--,
		 state->path.active--) अणु
		/*
		 * See अगर we can combine the block with a neighbor.
		 *   (action == 0) => no options, just leave
		 *   (action == 1) => coalesce, then unlink
		 *   (action == 2) => block empty, unlink it
		 */
		चयन (drop_blk->magic) अणु
		हाल XFS_ATTR_LEAF_MAGIC:
			error = xfs_attr3_leaf_toosmall(state, &action);
			अगर (error)
				वापस error;
			अगर (action == 0)
				वापस 0;
			xfs_attr3_leaf_unbalance(state, drop_blk, save_blk);
			अवरोध;
		हाल XFS_सूची2_LEAFN_MAGIC:
			error = xfs_dir2_leafn_toosmall(state, &action);
			अगर (error)
				वापस error;
			अगर (action == 0)
				वापस 0;
			xfs_dir2_leafn_unbalance(state, drop_blk, save_blk);
			अवरोध;
		हाल XFS_DA_NODE_MAGIC:
			/*
			 * Remove the offending node, fixup hashvals,
			 * check क्रम a toosmall neighbor.
			 */
			xfs_da3_node_हटाओ(state, drop_blk);
			xfs_da3_fixhashpath(state, &state->path);
			error = xfs_da3_node_toosmall(state, &action);
			अगर (error)
				वापस error;
			अगर (action == 0)
				वापस 0;
			xfs_da3_node_unbalance(state, drop_blk, save_blk);
			अवरोध;
		पूर्ण
		xfs_da3_fixhashpath(state, &state->altpath);
		error = xfs_da3_blk_unlink(state, drop_blk, save_blk);
		xfs_da_state_समाप्त_altpath(state);
		अगर (error)
			वापस error;
		error = xfs_da_shrink_inode(state->args, drop_blk->blkno,
							 drop_blk->bp);
		drop_blk->bp = शून्य;
		अगर (error)
			वापस error;
	पूर्ण
	/*
	 * We joined all the way to the top.  If it turns out that
	 * we only have one entry in the root, make the child block
	 * the new root.
	 */
	xfs_da3_node_हटाओ(state, drop_blk);
	xfs_da3_fixhashpath(state, &state->path);
	error = xfs_da3_root_join(state, &state->path.blk[0]);
	वापस error;
पूर्ण

#अगर_घोषित	DEBUG
अटल व्योम
xfs_da_blkinfo_onlychild_validate(काष्ठा xfs_da_blkinfo *blkinfo, __u16 level)
अणु
	__be16	magic = blkinfo->magic;

	अगर (level == 1) अणु
		ASSERT(magic == cpu_to_be16(XFS_सूची2_LEAFN_MAGIC) ||
		       magic == cpu_to_be16(XFS_सूची3_LEAFN_MAGIC) ||
		       magic == cpu_to_be16(XFS_ATTR_LEAF_MAGIC) ||
		       magic == cpu_to_be16(XFS_ATTR3_LEAF_MAGIC));
	पूर्ण अन्यथा अणु
		ASSERT(magic == cpu_to_be16(XFS_DA_NODE_MAGIC) ||
		       magic == cpu_to_be16(XFS_DA3_NODE_MAGIC));
	पूर्ण
	ASSERT(!blkinfo->क्रमw);
	ASSERT(!blkinfo->back);
पूर्ण
#अन्यथा	/* !DEBUG */
#घोषणा	xfs_da_blkinfo_onlychild_validate(blkinfo, level)
#पूर्ण_अगर	/* !DEBUG */

/*
 * We have only one entry in the root.  Copy the only reमुख्यing child of
 * the old root to block 0 as the new root node.
 */
STATIC पूर्णांक
xfs_da3_root_join(
	काष्ठा xfs_da_state	*state,
	काष्ठा xfs_da_state_blk	*root_blk)
अणु
	काष्ठा xfs_da_पूर्णांकnode	*oldroot;
	काष्ठा xfs_da_args	*args;
	xfs_dablk_t		child;
	काष्ठा xfs_buf		*bp;
	काष्ठा xfs_da3_icnode_hdr oldroothdr;
	पूर्णांक			error;
	काष्ठा xfs_inode	*dp = state->args->dp;

	trace_xfs_da_root_join(state->args);

	ASSERT(root_blk->magic == XFS_DA_NODE_MAGIC);

	args = state->args;
	oldroot = root_blk->bp->b_addr;
	xfs_da3_node_hdr_from_disk(dp->i_mount, &oldroothdr, oldroot);
	ASSERT(oldroothdr.क्रमw == 0);
	ASSERT(oldroothdr.back == 0);

	/*
	 * If the root has more than one child, then करोn't करो anything.
	 */
	अगर (oldroothdr.count > 1)
		वापस 0;

	/*
	 * Read in the (only) child block, then copy those bytes पूर्णांकo
	 * the root block's buffer and मुक्त the original child block.
	 */
	child = be32_to_cpu(oldroothdr.btree[0].beक्रमe);
	ASSERT(child != 0);
	error = xfs_da3_node_पढ़ो(args->trans, dp, child, &bp, args->whichविभाजन);
	अगर (error)
		वापस error;
	xfs_da_blkinfo_onlychild_validate(bp->b_addr, oldroothdr.level);

	/*
	 * This could be copying a leaf back पूर्णांकo the root block in the हाल of
	 * there only being a single leaf block left in the tree. Hence we have
	 * to update the b_ops poपूर्णांकer as well to match the buffer type change
	 * that could occur. For dir3 blocks we also need to update the block
	 * number in the buffer header.
	 */
	स_नकल(root_blk->bp->b_addr, bp->b_addr, args->geo->blksize);
	root_blk->bp->b_ops = bp->b_ops;
	xfs_trans_buf_copy_type(root_blk->bp, bp);
	अगर (oldroothdr.magic == XFS_DA3_NODE_MAGIC) अणु
		काष्ठा xfs_da3_blkinfo *da3 = root_blk->bp->b_addr;
		da3->blkno = cpu_to_be64(root_blk->bp->b_bn);
	पूर्ण
	xfs_trans_log_buf(args->trans, root_blk->bp, 0,
			  args->geo->blksize - 1);
	error = xfs_da_shrink_inode(args, child, bp);
	वापस error;
पूर्ण

/*
 * Check a node block and its neighbors to see अगर the block should be
 * collapsed पूर्णांकo one or the other neighbor.  Always keep the block
 * with the smaller block number.
 * If the current block is over 50% full, करोn't try to join it, वापस 0.
 * If the block is empty, fill in the state काष्ठाure and वापस 2.
 * If it can be collapsed, fill in the state काष्ठाure and वापस 1.
 * If nothing can be करोne, वापस 0.
 */
STATIC पूर्णांक
xfs_da3_node_toosmall(
	काष्ठा xfs_da_state	*state,
	पूर्णांक			*action)
अणु
	काष्ठा xfs_da_पूर्णांकnode	*node;
	काष्ठा xfs_da_state_blk	*blk;
	काष्ठा xfs_da_blkinfo	*info;
	xfs_dablk_t		blkno;
	काष्ठा xfs_buf		*bp;
	काष्ठा xfs_da3_icnode_hdr nodehdr;
	पूर्णांक			count;
	पूर्णांक			क्रमward;
	पूर्णांक			error;
	पूर्णांक			retval;
	पूर्णांक			i;
	काष्ठा xfs_inode	*dp = state->args->dp;

	trace_xfs_da_node_toosmall(state->args);

	/*
	 * Check क्रम the degenerate हाल of the block being over 50% full.
	 * If so, it's not worth even looking to see अगर we might be able
	 * to coalesce with a sibling.
	 */
	blk = &state->path.blk[ state->path.active-1 ];
	info = blk->bp->b_addr;
	node = (xfs_da_पूर्णांकnode_t *)info;
	xfs_da3_node_hdr_from_disk(dp->i_mount, &nodehdr, node);
	अगर (nodehdr.count > (state->args->geo->node_ents >> 1)) अणु
		*action = 0;	/* blk over 50%, करोn't try to join */
		वापस 0;	/* blk over 50%, करोn't try to join */
	पूर्ण

	/*
	 * Check क्रम the degenerate हाल of the block being empty.
	 * If the block is empty, we'll simply delete it, no need to
	 * coalesce it with a sibling block.  We choose (arbitrarily)
	 * to merge with the क्रमward block unless it is शून्य.
	 */
	अगर (nodehdr.count == 0) अणु
		/*
		 * Make altpath poपूर्णांक to the block we want to keep and
		 * path poपूर्णांक to the block we want to drop (this one).
		 */
		क्रमward = (info->क्रमw != 0);
		स_नकल(&state->altpath, &state->path, माप(state->path));
		error = xfs_da3_path_shअगरt(state, &state->altpath, क्रमward,
						 0, &retval);
		अगर (error)
			वापस error;
		अगर (retval) अणु
			*action = 0;
		पूर्ण अन्यथा अणु
			*action = 2;
		पूर्ण
		वापस 0;
	पूर्ण

	/*
	 * Examine each sibling block to see अगर we can coalesce with
	 * at least 25% मुक्त space to spare.  We need to figure out
	 * whether to merge with the क्रमward or the backward block.
	 * We prefer coalescing with the lower numbered sibling so as
	 * to shrink a directory over समय.
	 */
	count  = state->args->geo->node_ents;
	count -= state->args->geo->node_ents >> 2;
	count -= nodehdr.count;

	/* start with smaller blk num */
	क्रमward = nodehdr.क्रमw < nodehdr.back;
	क्रम (i = 0; i < 2; क्रमward = !क्रमward, i++) अणु
		काष्ठा xfs_da3_icnode_hdr thdr;
		अगर (क्रमward)
			blkno = nodehdr.क्रमw;
		अन्यथा
			blkno = nodehdr.back;
		अगर (blkno == 0)
			जारी;
		error = xfs_da3_node_पढ़ो(state->args->trans, dp, blkno, &bp,
				state->args->whichविभाजन);
		अगर (error)
			वापस error;

		node = bp->b_addr;
		xfs_da3_node_hdr_from_disk(dp->i_mount, &thdr, node);
		xfs_trans_brअन्यथा(state->args->trans, bp);

		अगर (count - thdr.count >= 0)
			अवरोध;	/* fits with at least 25% to spare */
	पूर्ण
	अगर (i >= 2) अणु
		*action = 0;
		वापस 0;
	पूर्ण

	/*
	 * Make altpath poपूर्णांक to the block we want to keep (the lower
	 * numbered block) and path poपूर्णांक to the block we want to drop.
	 */
	स_नकल(&state->altpath, &state->path, माप(state->path));
	अगर (blkno < blk->blkno) अणु
		error = xfs_da3_path_shअगरt(state, &state->altpath, क्रमward,
						 0, &retval);
	पूर्ण अन्यथा अणु
		error = xfs_da3_path_shअगरt(state, &state->path, क्रमward,
						 0, &retval);
	पूर्ण
	अगर (error)
		वापस error;
	अगर (retval) अणु
		*action = 0;
		वापस 0;
	पूर्ण
	*action = 1;
	वापस 0;
पूर्ण

/*
 * Pick up the last hashvalue from an पूर्णांकermediate node.
 */
STATIC uपूर्णांक
xfs_da3_node_lasthash(
	काष्ठा xfs_inode	*dp,
	काष्ठा xfs_buf		*bp,
	पूर्णांक			*count)
अणु
	काष्ठा xfs_da3_icnode_hdr nodehdr;

	xfs_da3_node_hdr_from_disk(dp->i_mount, &nodehdr, bp->b_addr);
	अगर (count)
		*count = nodehdr.count;
	अगर (!nodehdr.count)
		वापस 0;
	वापस be32_to_cpu(nodehdr.btree[nodehdr.count - 1].hashval);
पूर्ण

/*
 * Walk back up the tree adjusting hash values as necessary,
 * when we stop making changes, वापस.
 */
व्योम
xfs_da3_fixhashpath(
	काष्ठा xfs_da_state	*state,
	काष्ठा xfs_da_state_path *path)
अणु
	काष्ठा xfs_da_state_blk	*blk;
	काष्ठा xfs_da_पूर्णांकnode	*node;
	काष्ठा xfs_da_node_entry *btree;
	xfs_dahash_t		lasthash=0;
	पूर्णांक			level;
	पूर्णांक			count;
	काष्ठा xfs_inode	*dp = state->args->dp;

	trace_xfs_da_fixhashpath(state->args);

	level = path->active-1;
	blk = &path->blk[ level ];
	चयन (blk->magic) अणु
	हाल XFS_ATTR_LEAF_MAGIC:
		lasthash = xfs_attr_leaf_lasthash(blk->bp, &count);
		अगर (count == 0)
			वापस;
		अवरोध;
	हाल XFS_सूची2_LEAFN_MAGIC:
		lasthash = xfs_dir2_leaf_lasthash(dp, blk->bp, &count);
		अगर (count == 0)
			वापस;
		अवरोध;
	हाल XFS_DA_NODE_MAGIC:
		lasthash = xfs_da3_node_lasthash(dp, blk->bp, &count);
		अगर (count == 0)
			वापस;
		अवरोध;
	पूर्ण
	क्रम (blk--, level--; level >= 0; blk--, level--) अणु
		काष्ठा xfs_da3_icnode_hdr nodehdr;

		node = blk->bp->b_addr;
		xfs_da3_node_hdr_from_disk(dp->i_mount, &nodehdr, node);
		btree = nodehdr.btree;
		अगर (be32_to_cpu(btree[blk->index].hashval) == lasthash)
			अवरोध;
		blk->hashval = lasthash;
		btree[blk->index].hashval = cpu_to_be32(lasthash);
		xfs_trans_log_buf(state->args->trans, blk->bp,
				  XFS_DA_LOGRANGE(node, &btree[blk->index],
						  माप(*btree)));

		lasthash = be32_to_cpu(btree[nodehdr.count - 1].hashval);
	पूर्ण
पूर्ण

/*
 * Remove an entry from an पूर्णांकermediate node.
 */
STATIC व्योम
xfs_da3_node_हटाओ(
	काष्ठा xfs_da_state	*state,
	काष्ठा xfs_da_state_blk	*drop_blk)
अणु
	काष्ठा xfs_da_पूर्णांकnode	*node;
	काष्ठा xfs_da3_icnode_hdr nodehdr;
	काष्ठा xfs_da_node_entry *btree;
	पूर्णांक			index;
	पूर्णांक			पंचांगp;
	काष्ठा xfs_inode	*dp = state->args->dp;

	trace_xfs_da_node_हटाओ(state->args);

	node = drop_blk->bp->b_addr;
	xfs_da3_node_hdr_from_disk(dp->i_mount, &nodehdr, node);
	ASSERT(drop_blk->index < nodehdr.count);
	ASSERT(drop_blk->index >= 0);

	/*
	 * Copy over the offending entry, or just zero it out.
	 */
	index = drop_blk->index;
	btree = nodehdr.btree;
	अगर (index < nodehdr.count - 1) अणु
		पंचांगp  = nodehdr.count - index - 1;
		पंचांगp *= (uपूर्णांक)माप(xfs_da_node_entry_t);
		स_हटाओ(&btree[index], &btree[index + 1], पंचांगp);
		xfs_trans_log_buf(state->args->trans, drop_blk->bp,
		    XFS_DA_LOGRANGE(node, &btree[index], पंचांगp));
		index = nodehdr.count - 1;
	पूर्ण
	स_रखो(&btree[index], 0, माप(xfs_da_node_entry_t));
	xfs_trans_log_buf(state->args->trans, drop_blk->bp,
	    XFS_DA_LOGRANGE(node, &btree[index], माप(btree[index])));
	nodehdr.count -= 1;
	xfs_da3_node_hdr_to_disk(dp->i_mount, node, &nodehdr);
	xfs_trans_log_buf(state->args->trans, drop_blk->bp,
	    XFS_DA_LOGRANGE(node, &node->hdr, state->args->geo->node_hdr_size));

	/*
	 * Copy the last hash value from the block to propagate upwards.
	 */
	drop_blk->hashval = be32_to_cpu(btree[index - 1].hashval);
पूर्ण

/*
 * Unbalance the elements between two पूर्णांकermediate nodes,
 * move all Btree elements from one node पूर्णांकo another.
 */
STATIC व्योम
xfs_da3_node_unbalance(
	काष्ठा xfs_da_state	*state,
	काष्ठा xfs_da_state_blk	*drop_blk,
	काष्ठा xfs_da_state_blk	*save_blk)
अणु
	काष्ठा xfs_da_पूर्णांकnode	*drop_node;
	काष्ठा xfs_da_पूर्णांकnode	*save_node;
	काष्ठा xfs_da_node_entry *drop_btree;
	काष्ठा xfs_da_node_entry *save_btree;
	काष्ठा xfs_da3_icnode_hdr drop_hdr;
	काष्ठा xfs_da3_icnode_hdr save_hdr;
	काष्ठा xfs_trans	*tp;
	पूर्णांक			sindex;
	पूर्णांक			पंचांगp;
	काष्ठा xfs_inode	*dp = state->args->dp;

	trace_xfs_da_node_unbalance(state->args);

	drop_node = drop_blk->bp->b_addr;
	save_node = save_blk->bp->b_addr;
	xfs_da3_node_hdr_from_disk(dp->i_mount, &drop_hdr, drop_node);
	xfs_da3_node_hdr_from_disk(dp->i_mount, &save_hdr, save_node);
	drop_btree = drop_hdr.btree;
	save_btree = save_hdr.btree;
	tp = state->args->trans;

	/*
	 * If the dying block has lower hashvals, then move all the
	 * elements in the reमुख्यing block up to make a hole.
	 */
	अगर ((be32_to_cpu(drop_btree[0].hashval) <
			be32_to_cpu(save_btree[0].hashval)) ||
	    (be32_to_cpu(drop_btree[drop_hdr.count - 1].hashval) <
			be32_to_cpu(save_btree[save_hdr.count - 1].hashval))) अणु
		/* XXX: check this - is स_हटाओ dst correct? */
		पंचांगp = save_hdr.count * माप(xfs_da_node_entry_t);
		स_हटाओ(&save_btree[drop_hdr.count], &save_btree[0], पंचांगp);

		sindex = 0;
		xfs_trans_log_buf(tp, save_blk->bp,
			XFS_DA_LOGRANGE(save_node, &save_btree[0],
				(save_hdr.count + drop_hdr.count) *
						माप(xfs_da_node_entry_t)));
	पूर्ण अन्यथा अणु
		sindex = save_hdr.count;
		xfs_trans_log_buf(tp, save_blk->bp,
			XFS_DA_LOGRANGE(save_node, &save_btree[sindex],
				drop_hdr.count * माप(xfs_da_node_entry_t)));
	पूर्ण

	/*
	 * Move all the B-tree elements from drop_blk to save_blk.
	 */
	पंचांगp = drop_hdr.count * (uपूर्णांक)माप(xfs_da_node_entry_t);
	स_नकल(&save_btree[sindex], &drop_btree[0], पंचांगp);
	save_hdr.count += drop_hdr.count;

	xfs_da3_node_hdr_to_disk(dp->i_mount, save_node, &save_hdr);
	xfs_trans_log_buf(tp, save_blk->bp,
		XFS_DA_LOGRANGE(save_node, &save_node->hdr,
				state->args->geo->node_hdr_size));

	/*
	 * Save the last hashval in the reमुख्यing block क्रम upward propagation.
	 */
	save_blk->hashval = be32_to_cpu(save_btree[save_hdr.count - 1].hashval);
पूर्ण

/*========================================================================
 * Routines used क्रम finding things in the Btree.
 *========================================================================*/

/*
 * Walk करोwn the Btree looking क्रम a particular filename, filling
 * in the state काष्ठाure as we go.
 *
 * We will set the state काष्ठाure to poपूर्णांक to each of the elements
 * in each of the nodes where either the hashval is or should be.
 *
 * We support duplicate hashval's so क्रम each entry in the current
 * node that could contain the desired hashval, descend.  This is a
 * pruned depth-first tree search.
 */
पूर्णांक							/* error */
xfs_da3_node_lookup_पूर्णांक(
	काष्ठा xfs_da_state	*state,
	पूर्णांक			*result)
अणु
	काष्ठा xfs_da_state_blk	*blk;
	काष्ठा xfs_da_blkinfo	*curr;
	काष्ठा xfs_da_पूर्णांकnode	*node;
	काष्ठा xfs_da_node_entry *btree;
	काष्ठा xfs_da3_icnode_hdr nodehdr;
	काष्ठा xfs_da_args	*args;
	xfs_dablk_t		blkno;
	xfs_dahash_t		hashval;
	xfs_dahash_t		btreehashval;
	पूर्णांक			probe;
	पूर्णांक			span;
	पूर्णांक			max;
	पूर्णांक			error;
	पूर्णांक			retval;
	अचिन्हित पूर्णांक		expected_level = 0;
	uपूर्णांक16_t		magic;
	काष्ठा xfs_inode	*dp = state->args->dp;

	args = state->args;

	/*
	 * Descend thru the B-tree searching each level क्रम the right
	 * node to use, until the right hashval is found.
	 */
	blkno = args->geo->leafblk;
	क्रम (blk = &state->path.blk[0], state->path.active = 1;
			 state->path.active <= XFS_DA_NODE_MAXDEPTH;
			 blk++, state->path.active++) अणु
		/*
		 * Read the next node करोwn in the tree.
		 */
		blk->blkno = blkno;
		error = xfs_da3_node_पढ़ो(args->trans, args->dp, blkno,
					&blk->bp, args->whichविभाजन);
		अगर (error) अणु
			blk->blkno = 0;
			state->path.active--;
			वापस error;
		पूर्ण
		curr = blk->bp->b_addr;
		magic = be16_to_cpu(curr->magic);

		अगर (magic == XFS_ATTR_LEAF_MAGIC ||
		    magic == XFS_ATTR3_LEAF_MAGIC) अणु
			blk->magic = XFS_ATTR_LEAF_MAGIC;
			blk->hashval = xfs_attr_leaf_lasthash(blk->bp, शून्य);
			अवरोध;
		पूर्ण

		अगर (magic == XFS_सूची2_LEAFN_MAGIC ||
		    magic == XFS_सूची3_LEAFN_MAGIC) अणु
			blk->magic = XFS_सूची2_LEAFN_MAGIC;
			blk->hashval = xfs_dir2_leaf_lasthash(args->dp,
							      blk->bp, शून्य);
			अवरोध;
		पूर्ण

		अगर (magic != XFS_DA_NODE_MAGIC && magic != XFS_DA3_NODE_MAGIC) अणु
			xfs_buf_mark_corrupt(blk->bp);
			वापस -EFSCORRUPTED;
		पूर्ण

		blk->magic = XFS_DA_NODE_MAGIC;

		/*
		 * Search an पूर्णांकermediate node क्रम a match.
		 */
		node = blk->bp->b_addr;
		xfs_da3_node_hdr_from_disk(dp->i_mount, &nodehdr, node);
		btree = nodehdr.btree;

		/* Tree taller than we can handle; bail out! */
		अगर (nodehdr.level >= XFS_DA_NODE_MAXDEPTH) अणु
			xfs_buf_mark_corrupt(blk->bp);
			वापस -EFSCORRUPTED;
		पूर्ण

		/* Check the level from the root. */
		अगर (blkno == args->geo->leafblk)
			expected_level = nodehdr.level - 1;
		अन्यथा अगर (expected_level != nodehdr.level) अणु
			xfs_buf_mark_corrupt(blk->bp);
			वापस -EFSCORRUPTED;
		पूर्ण अन्यथा
			expected_level--;

		max = nodehdr.count;
		blk->hashval = be32_to_cpu(btree[max - 1].hashval);

		/*
		 * Binary search.  (note: small blocks will skip loop)
		 */
		probe = span = max / 2;
		hashval = args->hashval;
		जबतक (span > 4) अणु
			span /= 2;
			btreehashval = be32_to_cpu(btree[probe].hashval);
			अगर (btreehashval < hashval)
				probe += span;
			अन्यथा अगर (btreehashval > hashval)
				probe -= span;
			अन्यथा
				अवरोध;
		पूर्ण
		ASSERT((probe >= 0) && (probe < max));
		ASSERT((span <= 4) ||
			(be32_to_cpu(btree[probe].hashval) == hashval));

		/*
		 * Since we may have duplicate hashval's, find the first
		 * matching hashval in the node.
		 */
		जबतक (probe > 0 &&
		       be32_to_cpu(btree[probe].hashval) >= hashval) अणु
			probe--;
		पूर्ण
		जबतक (probe < max &&
		       be32_to_cpu(btree[probe].hashval) < hashval) अणु
			probe++;
		पूर्ण

		/*
		 * Pick the right block to descend on.
		 */
		अगर (probe == max) अणु
			blk->index = max - 1;
			blkno = be32_to_cpu(btree[max - 1].beक्रमe);
		पूर्ण अन्यथा अणु
			blk->index = probe;
			blkno = be32_to_cpu(btree[probe].beक्रमe);
		पूर्ण

		/* We can't poपूर्णांक back to the root. */
		अगर (XFS_IS_CORRUPT(dp->i_mount, blkno == args->geo->leafblk))
			वापस -EFSCORRUPTED;
	पूर्ण

	अगर (XFS_IS_CORRUPT(dp->i_mount, expected_level != 0))
		वापस -EFSCORRUPTED;

	/*
	 * A leaf block that ends in the hashval that we are पूर्णांकerested in
	 * (final hashval == search hashval) means that the next block may
	 * contain more entries with the same hashval, shअगरt upward to the
	 * next leaf and keep searching.
	 */
	क्रम (;;) अणु
		अगर (blk->magic == XFS_सूची2_LEAFN_MAGIC) अणु
			retval = xfs_dir2_leafn_lookup_पूर्णांक(blk->bp, args,
							&blk->index, state);
		पूर्ण अन्यथा अगर (blk->magic == XFS_ATTR_LEAF_MAGIC) अणु
			retval = xfs_attr3_leaf_lookup_पूर्णांक(blk->bp, args);
			blk->index = args->index;
			args->blkno = blk->blkno;
		पूर्ण अन्यथा अणु
			ASSERT(0);
			वापस -EFSCORRUPTED;
		पूर्ण
		अगर (((retval == -ENOENT) || (retval == -ENOATTR)) &&
		    (blk->hashval == args->hashval)) अणु
			error = xfs_da3_path_shअगरt(state, &state->path, 1, 1,
							 &retval);
			अगर (error)
				वापस error;
			अगर (retval == 0) अणु
				जारी;
			पूर्ण अन्यथा अगर (blk->magic == XFS_ATTR_LEAF_MAGIC) अणु
				/* path_shअगरt() gives ENOENT */
				retval = -ENOATTR;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	*result = retval;
	वापस 0;
पूर्ण

/*========================================================================
 * Utility routines.
 *========================================================================*/

/*
 * Compare two पूर्णांकermediate nodes क्रम "order".
 */
STATIC पूर्णांक
xfs_da3_node_order(
	काष्ठा xfs_inode *dp,
	काष्ठा xfs_buf	*node1_bp,
	काष्ठा xfs_buf	*node2_bp)
अणु
	काष्ठा xfs_da_पूर्णांकnode	*node1;
	काष्ठा xfs_da_पूर्णांकnode	*node2;
	काष्ठा xfs_da_node_entry *btree1;
	काष्ठा xfs_da_node_entry *btree2;
	काष्ठा xfs_da3_icnode_hdr node1hdr;
	काष्ठा xfs_da3_icnode_hdr node2hdr;

	node1 = node1_bp->b_addr;
	node2 = node2_bp->b_addr;
	xfs_da3_node_hdr_from_disk(dp->i_mount, &node1hdr, node1);
	xfs_da3_node_hdr_from_disk(dp->i_mount, &node2hdr, node2);
	btree1 = node1hdr.btree;
	btree2 = node2hdr.btree;

	अगर (node1hdr.count > 0 && node2hdr.count > 0 &&
	    ((be32_to_cpu(btree2[0].hashval) < be32_to_cpu(btree1[0].hashval)) ||
	     (be32_to_cpu(btree2[node2hdr.count - 1].hashval) <
	      be32_to_cpu(btree1[node1hdr.count - 1].hashval)))) अणु
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Link a new block पूर्णांकo a करोubly linked list of blocks (of whatever type).
 */
पूर्णांक							/* error */
xfs_da3_blk_link(
	काष्ठा xfs_da_state	*state,
	काष्ठा xfs_da_state_blk	*old_blk,
	काष्ठा xfs_da_state_blk	*new_blk)
अणु
	काष्ठा xfs_da_blkinfo	*old_info;
	काष्ठा xfs_da_blkinfo	*new_info;
	काष्ठा xfs_da_blkinfo	*पंचांगp_info;
	काष्ठा xfs_da_args	*args;
	काष्ठा xfs_buf		*bp;
	पूर्णांक			beक्रमe = 0;
	पूर्णांक			error;
	काष्ठा xfs_inode	*dp = state->args->dp;

	/*
	 * Set up environment.
	 */
	args = state->args;
	ASSERT(args != शून्य);
	old_info = old_blk->bp->b_addr;
	new_info = new_blk->bp->b_addr;
	ASSERT(old_blk->magic == XFS_DA_NODE_MAGIC ||
	       old_blk->magic == XFS_सूची2_LEAFN_MAGIC ||
	       old_blk->magic == XFS_ATTR_LEAF_MAGIC);

	चयन (old_blk->magic) अणु
	हाल XFS_ATTR_LEAF_MAGIC:
		beक्रमe = xfs_attr_leaf_order(old_blk->bp, new_blk->bp);
		अवरोध;
	हाल XFS_सूची2_LEAFN_MAGIC:
		beक्रमe = xfs_dir2_leafn_order(dp, old_blk->bp, new_blk->bp);
		अवरोध;
	हाल XFS_DA_NODE_MAGIC:
		beक्रमe = xfs_da3_node_order(dp, old_blk->bp, new_blk->bp);
		अवरोध;
	पूर्ण

	/*
	 * Link blocks in appropriate order.
	 */
	अगर (beक्रमe) अणु
		/*
		 * Link new block in beक्रमe existing block.
		 */
		trace_xfs_da_link_beक्रमe(args);
		new_info->क्रमw = cpu_to_be32(old_blk->blkno);
		new_info->back = old_info->back;
		अगर (old_info->back) अणु
			error = xfs_da3_node_पढ़ो(args->trans, dp,
						be32_to_cpu(old_info->back),
						&bp, args->whichविभाजन);
			अगर (error)
				वापस error;
			ASSERT(bp != शून्य);
			पंचांगp_info = bp->b_addr;
			ASSERT(पंचांगp_info->magic == old_info->magic);
			ASSERT(be32_to_cpu(पंचांगp_info->क्रमw) == old_blk->blkno);
			पंचांगp_info->क्रमw = cpu_to_be32(new_blk->blkno);
			xfs_trans_log_buf(args->trans, bp, 0, माप(*पंचांगp_info)-1);
		पूर्ण
		old_info->back = cpu_to_be32(new_blk->blkno);
	पूर्ण अन्यथा अणु
		/*
		 * Link new block in after existing block.
		 */
		trace_xfs_da_link_after(args);
		new_info->क्रमw = old_info->क्रमw;
		new_info->back = cpu_to_be32(old_blk->blkno);
		अगर (old_info->क्रमw) अणु
			error = xfs_da3_node_पढ़ो(args->trans, dp,
						be32_to_cpu(old_info->क्रमw),
						&bp, args->whichविभाजन);
			अगर (error)
				वापस error;
			ASSERT(bp != शून्य);
			पंचांगp_info = bp->b_addr;
			ASSERT(पंचांगp_info->magic == old_info->magic);
			ASSERT(be32_to_cpu(पंचांगp_info->back) == old_blk->blkno);
			पंचांगp_info->back = cpu_to_be32(new_blk->blkno);
			xfs_trans_log_buf(args->trans, bp, 0, माप(*पंचांगp_info)-1);
		पूर्ण
		old_info->क्रमw = cpu_to_be32(new_blk->blkno);
	पूर्ण

	xfs_trans_log_buf(args->trans, old_blk->bp, 0, माप(*पंचांगp_info) - 1);
	xfs_trans_log_buf(args->trans, new_blk->bp, 0, माप(*पंचांगp_info) - 1);
	वापस 0;
पूर्ण

/*
 * Unlink a block from a करोubly linked list of blocks.
 */
STATIC पूर्णांक						/* error */
xfs_da3_blk_unlink(
	काष्ठा xfs_da_state	*state,
	काष्ठा xfs_da_state_blk	*drop_blk,
	काष्ठा xfs_da_state_blk	*save_blk)
अणु
	काष्ठा xfs_da_blkinfo	*drop_info;
	काष्ठा xfs_da_blkinfo	*save_info;
	काष्ठा xfs_da_blkinfo	*पंचांगp_info;
	काष्ठा xfs_da_args	*args;
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;

	/*
	 * Set up environment.
	 */
	args = state->args;
	ASSERT(args != शून्य);
	save_info = save_blk->bp->b_addr;
	drop_info = drop_blk->bp->b_addr;
	ASSERT(save_blk->magic == XFS_DA_NODE_MAGIC ||
	       save_blk->magic == XFS_सूची2_LEAFN_MAGIC ||
	       save_blk->magic == XFS_ATTR_LEAF_MAGIC);
	ASSERT(save_blk->magic == drop_blk->magic);
	ASSERT((be32_to_cpu(save_info->क्रमw) == drop_blk->blkno) ||
	       (be32_to_cpu(save_info->back) == drop_blk->blkno));
	ASSERT((be32_to_cpu(drop_info->क्रमw) == save_blk->blkno) ||
	       (be32_to_cpu(drop_info->back) == save_blk->blkno));

	/*
	 * Unlink the leaf block from the करोubly linked chain of leaves.
	 */
	अगर (be32_to_cpu(save_info->back) == drop_blk->blkno) अणु
		trace_xfs_da_unlink_back(args);
		save_info->back = drop_info->back;
		अगर (drop_info->back) अणु
			error = xfs_da3_node_पढ़ो(args->trans, args->dp,
						be32_to_cpu(drop_info->back),
						&bp, args->whichविभाजन);
			अगर (error)
				वापस error;
			ASSERT(bp != शून्य);
			पंचांगp_info = bp->b_addr;
			ASSERT(पंचांगp_info->magic == save_info->magic);
			ASSERT(be32_to_cpu(पंचांगp_info->क्रमw) == drop_blk->blkno);
			पंचांगp_info->क्रमw = cpu_to_be32(save_blk->blkno);
			xfs_trans_log_buf(args->trans, bp, 0,
						    माप(*पंचांगp_info) - 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		trace_xfs_da_unlink_क्रमward(args);
		save_info->क्रमw = drop_info->क्रमw;
		अगर (drop_info->क्रमw) अणु
			error = xfs_da3_node_पढ़ो(args->trans, args->dp,
						be32_to_cpu(drop_info->क्रमw),
						&bp, args->whichविभाजन);
			अगर (error)
				वापस error;
			ASSERT(bp != शून्य);
			पंचांगp_info = bp->b_addr;
			ASSERT(पंचांगp_info->magic == save_info->magic);
			ASSERT(be32_to_cpu(पंचांगp_info->back) == drop_blk->blkno);
			पंचांगp_info->back = cpu_to_be32(save_blk->blkno);
			xfs_trans_log_buf(args->trans, bp, 0,
						    माप(*पंचांगp_info) - 1);
		पूर्ण
	पूर्ण

	xfs_trans_log_buf(args->trans, save_blk->bp, 0, माप(*save_info) - 1);
	वापस 0;
पूर्ण

/*
 * Move a path "forward" or "!forward" one block at the current level.
 *
 * This routine will adjust a "path" to poपूर्णांक to the next block
 * "forward" (higher hashvalues) or "!forward" (lower hashvals) in the
 * Btree, including updating poपूर्णांकers to the पूर्णांकermediate nodes between
 * the new bottom and the root.
 */
पूर्णांक							/* error */
xfs_da3_path_shअगरt(
	काष्ठा xfs_da_state	*state,
	काष्ठा xfs_da_state_path *path,
	पूर्णांक			क्रमward,
	पूर्णांक			release,
	पूर्णांक			*result)
अणु
	काष्ठा xfs_da_state_blk	*blk;
	काष्ठा xfs_da_blkinfo	*info;
	काष्ठा xfs_da_args	*args;
	काष्ठा xfs_da_node_entry *btree;
	काष्ठा xfs_da3_icnode_hdr nodehdr;
	काष्ठा xfs_buf		*bp;
	xfs_dablk_t		blkno = 0;
	पूर्णांक			level;
	पूर्णांक			error;
	काष्ठा xfs_inode	*dp = state->args->dp;

	trace_xfs_da_path_shअगरt(state->args);

	/*
	 * Roll up the Btree looking क्रम the first block where our
	 * current index is not at the edge of the block.  Note that
	 * we skip the bottom layer because we want the sibling block.
	 */
	args = state->args;
	ASSERT(args != शून्य);
	ASSERT(path != शून्य);
	ASSERT((path->active > 0) && (path->active < XFS_DA_NODE_MAXDEPTH));
	level = (path->active-1) - 1;	/* skip bottom layer in path */
	क्रम (; level >= 0; level--) अणु
		blk = &path->blk[level];
		xfs_da3_node_hdr_from_disk(dp->i_mount, &nodehdr,
					   blk->bp->b_addr);

		अगर (क्रमward && (blk->index < nodehdr.count - 1)) अणु
			blk->index++;
			blkno = be32_to_cpu(nodehdr.btree[blk->index].beक्रमe);
			अवरोध;
		पूर्ण अन्यथा अगर (!क्रमward && (blk->index > 0)) अणु
			blk->index--;
			blkno = be32_to_cpu(nodehdr.btree[blk->index].beक्रमe);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (level < 0) अणु
		*result = -ENOENT;	/* we're out of our tree */
		ASSERT(args->op_flags & XFS_DA_OP_OKNOENT);
		वापस 0;
	पूर्ण

	/*
	 * Roll करोwn the edge of the subtree until we reach the
	 * same depth we were at originally.
	 */
	क्रम (blk++, level++; level < path->active; blk++, level++) अणु
		/*
		 * Read the next child block पूर्णांकo a local buffer.
		 */
		error = xfs_da3_node_पढ़ो(args->trans, dp, blkno, &bp,
					  args->whichविभाजन);
		अगर (error)
			वापस error;

		/*
		 * Release the old block (अगर it's dirty, the trans doesn't
		 * actually let go) and swap the local buffer पूर्णांकo the path
		 * काष्ठाure. This ensures failure of the above पढ़ो करोesn't set
		 * a शून्य buffer in an active slot in the path.
		 */
		अगर (release)
			xfs_trans_brअन्यथा(args->trans, blk->bp);
		blk->blkno = blkno;
		blk->bp = bp;

		info = blk->bp->b_addr;
		ASSERT(info->magic == cpu_to_be16(XFS_DA_NODE_MAGIC) ||
		       info->magic == cpu_to_be16(XFS_DA3_NODE_MAGIC) ||
		       info->magic == cpu_to_be16(XFS_सूची2_LEAFN_MAGIC) ||
		       info->magic == cpu_to_be16(XFS_सूची3_LEAFN_MAGIC) ||
		       info->magic == cpu_to_be16(XFS_ATTR_LEAF_MAGIC) ||
		       info->magic == cpu_to_be16(XFS_ATTR3_LEAF_MAGIC));


		/*
		 * Note: we flatten the magic number to a single type so we
		 * करोn't have to compare against crc/non-crc types अन्यथाwhere.
		 */
		चयन (be16_to_cpu(info->magic)) अणु
		हाल XFS_DA_NODE_MAGIC:
		हाल XFS_DA3_NODE_MAGIC:
			blk->magic = XFS_DA_NODE_MAGIC;
			xfs_da3_node_hdr_from_disk(dp->i_mount, &nodehdr,
						   bp->b_addr);
			btree = nodehdr.btree;
			blk->hashval = be32_to_cpu(btree[nodehdr.count - 1].hashval);
			अगर (क्रमward)
				blk->index = 0;
			अन्यथा
				blk->index = nodehdr.count - 1;
			blkno = be32_to_cpu(btree[blk->index].beक्रमe);
			अवरोध;
		हाल XFS_ATTR_LEAF_MAGIC:
		हाल XFS_ATTR3_LEAF_MAGIC:
			blk->magic = XFS_ATTR_LEAF_MAGIC;
			ASSERT(level == path->active-1);
			blk->index = 0;
			blk->hashval = xfs_attr_leaf_lasthash(blk->bp, शून्य);
			अवरोध;
		हाल XFS_सूची2_LEAFN_MAGIC:
		हाल XFS_सूची3_LEAFN_MAGIC:
			blk->magic = XFS_सूची2_LEAFN_MAGIC;
			ASSERT(level == path->active-1);
			blk->index = 0;
			blk->hashval = xfs_dir2_leaf_lasthash(args->dp,
							      blk->bp, शून्य);
			अवरोध;
		शेष:
			ASSERT(0);
			अवरोध;
		पूर्ण
	पूर्ण
	*result = 0;
	वापस 0;
पूर्ण


/*========================================================================
 * Utility routines.
 *========================================================================*/

/*
 * Implement a simple hash on a अक्षरacter string.
 * Rotate the hash value by 7 bits, then XOR each अक्षरacter in.
 * This is implemented with some source-level loop unrolling.
 */
xfs_dahash_t
xfs_da_hashname(स्थिर uपूर्णांक8_t *name, पूर्णांक namelen)
अणु
	xfs_dahash_t hash;

	/*
	 * Do four अक्षरacters at a समय as दीर्घ as we can.
	 */
	क्रम (hash = 0; namelen >= 4; namelen -= 4, name += 4)
		hash = (name[0] << 21) ^ (name[1] << 14) ^ (name[2] << 7) ^
		       (name[3] << 0) ^ rol32(hash, 7 * 4);

	/*
	 * Now करो the rest of the अक्षरacters.
	 */
	चयन (namelen) अणु
	हाल 3:
		वापस (name[0] << 14) ^ (name[1] << 7) ^ (name[2] << 0) ^
		       rol32(hash, 7 * 3);
	हाल 2:
		वापस (name[0] << 7) ^ (name[1] << 0) ^ rol32(hash, 7 * 2);
	हाल 1:
		वापस (name[0] << 0) ^ rol32(hash, 7 * 1);
	शेष: /* हाल 0: */
		वापस hash;
	पूर्ण
पूर्ण

क्रमागत xfs_dacmp
xfs_da_compname(
	काष्ठा xfs_da_args *args,
	स्थिर अचिन्हित अक्षर *name,
	पूर्णांक		len)
अणु
	वापस (args->namelen == len && स_भेद(args->name, name, len) == 0) ?
					XFS_CMP_EXACT : XFS_CMP_DIFFERENT;
पूर्ण

पूर्णांक
xfs_da_grow_inode_पूर्णांक(
	काष्ठा xfs_da_args	*args,
	xfs_fileoff_t		*bno,
	पूर्णांक			count)
अणु
	काष्ठा xfs_trans	*tp = args->trans;
	काष्ठा xfs_inode	*dp = args->dp;
	पूर्णांक			w = args->whichविभाजन;
	xfs_rfsblock_t		nblks = dp->i_nblocks;
	काष्ठा xfs_bmbt_irec	map, *mapp;
	पूर्णांक			nmap, error, got, i, mapi;

	/*
	 * Find a spot in the file space to put the new block.
	 */
	error = xfs_bmap_first_unused(tp, dp, count, bno, w);
	अगर (error)
		वापस error;

	/*
	 * Try mapping it in one fileप्रणाली block.
	 */
	nmap = 1;
	error = xfs_bmapi_ग_लिखो(tp, dp, *bno, count,
			xfs_bmapi_aflag(w)|XFS_BMAPI_METADATA|XFS_BMAPI_CONTIG,
			args->total, &map, &nmap);
	अगर (error)
		वापस error;

	ASSERT(nmap <= 1);
	अगर (nmap == 1) अणु
		mapp = &map;
		mapi = 1;
	पूर्ण अन्यथा अगर (nmap == 0 && count > 1) अणु
		xfs_fileoff_t		b;
		पूर्णांक			c;

		/*
		 * If we didn't get it and the block might work अगर fragmented,
		 * try without the CONTIG flag.  Loop until we get it all.
		 */
		mapp = kmem_alloc(माप(*mapp) * count, 0);
		क्रम (b = *bno, mapi = 0; b < *bno + count; ) अणु
			nmap = min(XFS_BMAP_MAX_NMAP, count);
			c = (पूर्णांक)(*bno + count - b);
			error = xfs_bmapi_ग_लिखो(tp, dp, b, c,
					xfs_bmapi_aflag(w)|XFS_BMAPI_METADATA,
					args->total, &mapp[mapi], &nmap);
			अगर (error)
				जाओ out_मुक्त_map;
			अगर (nmap < 1)
				अवरोध;
			mapi += nmap;
			b = mapp[mapi - 1].br_startoff +
			    mapp[mapi - 1].br_blockcount;
		पूर्ण
	पूर्ण अन्यथा अणु
		mapi = 0;
		mapp = शून्य;
	पूर्ण

	/*
	 * Count the blocks we got, make sure it matches the total.
	 */
	क्रम (i = 0, got = 0; i < mapi; i++)
		got += mapp[i].br_blockcount;
	अगर (got != count || mapp[0].br_startoff != *bno ||
	    mapp[mapi - 1].br_startoff + mapp[mapi - 1].br_blockcount !=
	    *bno + count) अणु
		error = -ENOSPC;
		जाओ out_मुक्त_map;
	पूर्ण

	/* account क्रम newly allocated blocks in reserved blocks total */
	args->total -= dp->i_nblocks - nblks;

out_मुक्त_map:
	अगर (mapp != &map)
		kmem_मुक्त(mapp);
	वापस error;
पूर्ण

/*
 * Add a block to the btree ahead of the file.
 * Return the new block number to the caller.
 */
पूर्णांक
xfs_da_grow_inode(
	काष्ठा xfs_da_args	*args,
	xfs_dablk_t		*new_blkno)
अणु
	xfs_fileoff_t		bno;
	पूर्णांक			error;

	trace_xfs_da_grow_inode(args);

	bno = args->geo->leafblk;
	error = xfs_da_grow_inode_पूर्णांक(args, &bno, args->geo->fsbcount);
	अगर (!error)
		*new_blkno = (xfs_dablk_t)bno;
	वापस error;
पूर्ण

/*
 * Ick.  We need to always be able to हटाओ a btree block, even
 * अगर there's no space reservation because the fileप्रणाली is full.
 * This is called अगर xfs_bunmapi on a btree block fails due to ENOSPC.
 * It swaps the target block with the last block in the file.  The
 * last block in the file can always be हटाओd since it can't cause
 * a bmap btree split to करो that.
 */
STATIC पूर्णांक
xfs_da3_swap_lastblock(
	काष्ठा xfs_da_args	*args,
	xfs_dablk_t		*dead_blknop,
	काष्ठा xfs_buf		**dead_bufp)
अणु
	काष्ठा xfs_da_blkinfo	*dead_info;
	काष्ठा xfs_da_blkinfo	*sib_info;
	काष्ठा xfs_da_पूर्णांकnode	*par_node;
	काष्ठा xfs_da_पूर्णांकnode	*dead_node;
	काष्ठा xfs_dir2_leaf	*dead_leaf2;
	काष्ठा xfs_da_node_entry *btree;
	काष्ठा xfs_da3_icnode_hdr par_hdr;
	काष्ठा xfs_inode	*dp;
	काष्ठा xfs_trans	*tp;
	काष्ठा xfs_mount	*mp;
	काष्ठा xfs_buf		*dead_buf;
	काष्ठा xfs_buf		*last_buf;
	काष्ठा xfs_buf		*sib_buf;
	काष्ठा xfs_buf		*par_buf;
	xfs_dahash_t		dead_hash;
	xfs_fileoff_t		lastoff;
	xfs_dablk_t		dead_blkno;
	xfs_dablk_t		last_blkno;
	xfs_dablk_t		sib_blkno;
	xfs_dablk_t		par_blkno;
	पूर्णांक			error;
	पूर्णांक			w;
	पूर्णांक			entno;
	पूर्णांक			level;
	पूर्णांक			dead_level;

	trace_xfs_da_swap_lastblock(args);

	dead_buf = *dead_bufp;
	dead_blkno = *dead_blknop;
	tp = args->trans;
	dp = args->dp;
	w = args->whichविभाजन;
	ASSERT(w == XFS_DATA_FORK);
	mp = dp->i_mount;
	lastoff = args->geo->मुक्तblk;
	error = xfs_bmap_last_beक्रमe(tp, dp, &lastoff, w);
	अगर (error)
		वापस error;
	अगर (XFS_IS_CORRUPT(mp, lastoff == 0))
		वापस -EFSCORRUPTED;
	/*
	 * Read the last block in the btree space.
	 */
	last_blkno = (xfs_dablk_t)lastoff - args->geo->fsbcount;
	error = xfs_da3_node_पढ़ो(tp, dp, last_blkno, &last_buf, w);
	अगर (error)
		वापस error;
	/*
	 * Copy the last block पूर्णांकo the dead buffer and log it.
	 */
	स_नकल(dead_buf->b_addr, last_buf->b_addr, args->geo->blksize);
	xfs_trans_log_buf(tp, dead_buf, 0, args->geo->blksize - 1);
	dead_info = dead_buf->b_addr;
	/*
	 * Get values from the moved block.
	 */
	अगर (dead_info->magic == cpu_to_be16(XFS_सूची2_LEAFN_MAGIC) ||
	    dead_info->magic == cpu_to_be16(XFS_सूची3_LEAFN_MAGIC)) अणु
		काष्ठा xfs_dir3_icleaf_hdr leafhdr;
		काष्ठा xfs_dir2_leaf_entry *ents;

		dead_leaf2 = (xfs_dir2_leaf_t *)dead_info;
		xfs_dir2_leaf_hdr_from_disk(dp->i_mount, &leafhdr,
					    dead_leaf2);
		ents = leafhdr.ents;
		dead_level = 0;
		dead_hash = be32_to_cpu(ents[leafhdr.count - 1].hashval);
	पूर्ण अन्यथा अणु
		काष्ठा xfs_da3_icnode_hdr deadhdr;

		dead_node = (xfs_da_पूर्णांकnode_t *)dead_info;
		xfs_da3_node_hdr_from_disk(dp->i_mount, &deadhdr, dead_node);
		btree = deadhdr.btree;
		dead_level = deadhdr.level;
		dead_hash = be32_to_cpu(btree[deadhdr.count - 1].hashval);
	पूर्ण
	sib_buf = par_buf = शून्य;
	/*
	 * If the moved block has a left sibling, fix up the poपूर्णांकers.
	 */
	अगर ((sib_blkno = be32_to_cpu(dead_info->back))) अणु
		error = xfs_da3_node_पढ़ो(tp, dp, sib_blkno, &sib_buf, w);
		अगर (error)
			जाओ करोne;
		sib_info = sib_buf->b_addr;
		अगर (XFS_IS_CORRUPT(mp,
				   be32_to_cpu(sib_info->क्रमw) != last_blkno ||
				   sib_info->magic != dead_info->magic)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		sib_info->क्रमw = cpu_to_be32(dead_blkno);
		xfs_trans_log_buf(tp, sib_buf,
			XFS_DA_LOGRANGE(sib_info, &sib_info->क्रमw,
					माप(sib_info->क्रमw)));
		sib_buf = शून्य;
	पूर्ण
	/*
	 * If the moved block has a right sibling, fix up the poपूर्णांकers.
	 */
	अगर ((sib_blkno = be32_to_cpu(dead_info->क्रमw))) अणु
		error = xfs_da3_node_पढ़ो(tp, dp, sib_blkno, &sib_buf, w);
		अगर (error)
			जाओ करोne;
		sib_info = sib_buf->b_addr;
		अगर (XFS_IS_CORRUPT(mp,
				   be32_to_cpu(sib_info->back) != last_blkno ||
				   sib_info->magic != dead_info->magic)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		sib_info->back = cpu_to_be32(dead_blkno);
		xfs_trans_log_buf(tp, sib_buf,
			XFS_DA_LOGRANGE(sib_info, &sib_info->back,
					माप(sib_info->back)));
		sib_buf = शून्य;
	पूर्ण
	par_blkno = args->geo->leafblk;
	level = -1;
	/*
	 * Walk करोwn the tree looking क्रम the parent of the moved block.
	 */
	क्रम (;;) अणु
		error = xfs_da3_node_पढ़ो(tp, dp, par_blkno, &par_buf, w);
		अगर (error)
			जाओ करोne;
		par_node = par_buf->b_addr;
		xfs_da3_node_hdr_from_disk(dp->i_mount, &par_hdr, par_node);
		अगर (XFS_IS_CORRUPT(mp,
				   level >= 0 && level != par_hdr.level + 1)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		level = par_hdr.level;
		btree = par_hdr.btree;
		क्रम (entno = 0;
		     entno < par_hdr.count &&
		     be32_to_cpu(btree[entno].hashval) < dead_hash;
		     entno++)
			जारी;
		अगर (XFS_IS_CORRUPT(mp, entno == par_hdr.count)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		par_blkno = be32_to_cpu(btree[entno].beक्रमe);
		अगर (level == dead_level + 1)
			अवरोध;
		xfs_trans_brअन्यथा(tp, par_buf);
		par_buf = शून्य;
	पूर्ण
	/*
	 * We're in the right parent block.
	 * Look क्रम the right entry.
	 */
	क्रम (;;) अणु
		क्रम (;
		     entno < par_hdr.count &&
		     be32_to_cpu(btree[entno].beक्रमe) != last_blkno;
		     entno++)
			जारी;
		अगर (entno < par_hdr.count)
			अवरोध;
		par_blkno = par_hdr.क्रमw;
		xfs_trans_brअन्यथा(tp, par_buf);
		par_buf = शून्य;
		अगर (XFS_IS_CORRUPT(mp, par_blkno == 0)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		error = xfs_da3_node_पढ़ो(tp, dp, par_blkno, &par_buf, w);
		अगर (error)
			जाओ करोne;
		par_node = par_buf->b_addr;
		xfs_da3_node_hdr_from_disk(dp->i_mount, &par_hdr, par_node);
		अगर (XFS_IS_CORRUPT(mp, par_hdr.level != level)) अणु
			error = -EFSCORRUPTED;
			जाओ करोne;
		पूर्ण
		btree = par_hdr.btree;
		entno = 0;
	पूर्ण
	/*
	 * Update the parent entry poपूर्णांकing to the moved block.
	 */
	btree[entno].beक्रमe = cpu_to_be32(dead_blkno);
	xfs_trans_log_buf(tp, par_buf,
		XFS_DA_LOGRANGE(par_node, &btree[entno].beक्रमe,
				माप(btree[entno].beक्रमe)));
	*dead_blknop = last_blkno;
	*dead_bufp = last_buf;
	वापस 0;
करोne:
	अगर (par_buf)
		xfs_trans_brअन्यथा(tp, par_buf);
	अगर (sib_buf)
		xfs_trans_brअन्यथा(tp, sib_buf);
	xfs_trans_brअन्यथा(tp, last_buf);
	वापस error;
पूर्ण

/*
 * Remove a btree block from a directory or attribute.
 */
पूर्णांक
xfs_da_shrink_inode(
	काष्ठा xfs_da_args	*args,
	xfs_dablk_t		dead_blkno,
	काष्ठा xfs_buf		*dead_buf)
अणु
	काष्ठा xfs_inode	*dp;
	पूर्णांक			करोne, error, w, count;
	काष्ठा xfs_trans	*tp;

	trace_xfs_da_shrink_inode(args);

	dp = args->dp;
	w = args->whichविभाजन;
	tp = args->trans;
	count = args->geo->fsbcount;
	क्रम (;;) अणु
		/*
		 * Remove extents.  If we get ENOSPC क्रम a dir we have to move
		 * the last block to the place we want to समाप्त.
		 */
		error = xfs_bunmapi(tp, dp, dead_blkno, count,
				    xfs_bmapi_aflag(w), 0, &करोne);
		अगर (error == -ENOSPC) अणु
			अगर (w != XFS_DATA_FORK)
				अवरोध;
			error = xfs_da3_swap_lastblock(args, &dead_blkno,
						      &dead_buf);
			अगर (error)
				अवरोध;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण
	xfs_trans_binval(tp, dead_buf);
	वापस error;
पूर्ण

अटल पूर्णांक
xfs_dabuf_map(
	काष्ठा xfs_inode	*dp,
	xfs_dablk_t		bno,
	अचिन्हित पूर्णांक		flags,
	पूर्णांक			whichविभाजन,
	काष्ठा xfs_buf_map	**mapp,
	पूर्णांक			*nmaps)
अणु
	काष्ठा xfs_mount	*mp = dp->i_mount;
	पूर्णांक			nfsb = xfs_dabuf_nfsb(mp, whichविभाजन);
	काष्ठा xfs_bmbt_irec	irec, *irecs = &irec;
	काष्ठा xfs_buf_map	*map = *mapp;
	xfs_fileoff_t		off = bno;
	पूर्णांक			error = 0, nirecs, i;

	अगर (nfsb > 1)
		irecs = kmem_zalloc(माप(irec) * nfsb, KM_NOFS);

	nirecs = nfsb;
	error = xfs_bmapi_पढ़ो(dp, bno, nfsb, irecs, &nirecs,
			xfs_bmapi_aflag(whichविभाजन));
	अगर (error)
		जाओ out_मुक्त_irecs;

	/*
	 * Use the caller provided map क्रम the single map हाल, अन्यथा allocate a
	 * larger one that needs to be मुक्त by the caller.
	 */
	अगर (nirecs > 1) अणु
		map = kmem_zalloc(nirecs * माप(काष्ठा xfs_buf_map), KM_NOFS);
		अगर (!map) अणु
			error = -ENOMEM;
			जाओ out_मुक्त_irecs;
		पूर्ण
		*mapp = map;
	पूर्ण

	क्रम (i = 0; i < nirecs; i++) अणु
		अगर (irecs[i].br_startblock == HOLESTARTBLOCK ||
		    irecs[i].br_startblock == DELAYSTARTBLOCK)
			जाओ invalid_mapping;
		अगर (off != irecs[i].br_startoff)
			जाओ invalid_mapping;

		map[i].bm_bn = XFS_FSB_TO_DADDR(mp, irecs[i].br_startblock);
		map[i].bm_len = XFS_FSB_TO_BB(mp, irecs[i].br_blockcount);
		off += irecs[i].br_blockcount;
	पूर्ण

	अगर (off != bno + nfsb)
		जाओ invalid_mapping;

	*nmaps = nirecs;
out_मुक्त_irecs:
	अगर (irecs != &irec)
		kmem_मुक्त(irecs);
	वापस error;

invalid_mapping:
	/* Caller ok with no mapping. */
	अगर (XFS_IS_CORRUPT(mp, !(flags & XFS_DABUF_MAP_HOLE_OK))) अणु
		error = -EFSCORRUPTED;
		अगर (xfs_error_level >= XFS_ERRLEVEL_LOW) अणु
			xfs_alert(mp, "%s: bno %u inode %llu",
					__func__, bno, dp->i_ino);

			क्रम (i = 0; i < nirecs; i++) अणु
				xfs_alert(mp,
"[%02d] br_startoff %lld br_startblock %lld br_blockcount %lld br_state %d",
					i, irecs[i].br_startoff,
					irecs[i].br_startblock,
					irecs[i].br_blockcount,
					irecs[i].br_state);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		*nmaps = 0;
	पूर्ण
	जाओ out_मुक्त_irecs;
पूर्ण

/*
 * Get a buffer क्रम the dir/attr block.
 */
पूर्णांक
xfs_da_get_buf(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*dp,
	xfs_dablk_t		bno,
	काष्ठा xfs_buf		**bpp,
	पूर्णांक			whichविभाजन)
अणु
	काष्ठा xfs_mount	*mp = dp->i_mount;
	काष्ठा xfs_buf		*bp;
	काष्ठा xfs_buf_map	map, *mapp = &map;
	पूर्णांक			nmap = 1;
	पूर्णांक			error;

	*bpp = शून्य;
	error = xfs_dabuf_map(dp, bno, 0, whichविभाजन, &mapp, &nmap);
	अगर (error || nmap == 0)
		जाओ out_मुक्त;

	error = xfs_trans_get_buf_map(tp, mp->m_ddev_targp, mapp, nmap, 0, &bp);
	अगर (error)
		जाओ out_मुक्त;

	*bpp = bp;

out_मुक्त:
	अगर (mapp != &map)
		kmem_मुक्त(mapp);

	वापस error;
पूर्ण

/*
 * Get a buffer क्रम the dir/attr block, fill in the contents.
 */
पूर्णांक
xfs_da_पढ़ो_buf(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*dp,
	xfs_dablk_t		bno,
	अचिन्हित पूर्णांक		flags,
	काष्ठा xfs_buf		**bpp,
	पूर्णांक			whichविभाजन,
	स्थिर काष्ठा xfs_buf_ops *ops)
अणु
	काष्ठा xfs_mount	*mp = dp->i_mount;
	काष्ठा xfs_buf		*bp;
	काष्ठा xfs_buf_map	map, *mapp = &map;
	पूर्णांक			nmap = 1;
	पूर्णांक			error;

	*bpp = शून्य;
	error = xfs_dabuf_map(dp, bno, flags, whichविभाजन, &mapp, &nmap);
	अगर (error || !nmap)
		जाओ out_मुक्त;

	error = xfs_trans_पढ़ो_buf_map(mp, tp, mp->m_ddev_targp, mapp, nmap, 0,
			&bp, ops);
	अगर (error)
		जाओ out_मुक्त;

	अगर (whichविभाजन == XFS_ATTR_FORK)
		xfs_buf_set_ref(bp, XFS_ATTR_BTREE_REF);
	अन्यथा
		xfs_buf_set_ref(bp, XFS_सूची_BTREE_REF);
	*bpp = bp;
out_मुक्त:
	अगर (mapp != &map)
		kmem_मुक्त(mapp);

	वापस error;
पूर्ण

/*
 * Readahead the dir/attr block.
 */
पूर्णांक
xfs_da_पढ़ोa_buf(
	काष्ठा xfs_inode	*dp,
	xfs_dablk_t		bno,
	अचिन्हित पूर्णांक		flags,
	पूर्णांक			whichविभाजन,
	स्थिर काष्ठा xfs_buf_ops *ops)
अणु
	काष्ठा xfs_buf_map	map;
	काष्ठा xfs_buf_map	*mapp;
	पूर्णांक			nmap;
	पूर्णांक			error;

	mapp = &map;
	nmap = 1;
	error = xfs_dabuf_map(dp, bno, flags, whichविभाजन, &mapp, &nmap);
	अगर (error || !nmap)
		जाओ out_मुक्त;

	xfs_buf_पढ़ोahead_map(dp->i_mount->m_ddev_targp, mapp, nmap, ops);

out_मुक्त:
	अगर (mapp != &map)
		kmem_मुक्त(mapp);

	वापस error;
पूर्ण
