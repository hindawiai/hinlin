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
#समावेश "xfs_da_format.h"
#समावेश "xfs_da_btree.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_attr_remote.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_attr.h"
#समावेश "xfs_attr_leaf.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_dir2.h"
#समावेश "xfs_error.h"

/*
 * Invalidate any incore buffers associated with this remote attribute value
 * extent.   We never log remote attribute value buffers, which means that they
 * won't be attached to a transaction and are thereक्रमe safe to mark stale.
 * The actual bunmapi will be taken care of later.
 */
STATIC पूर्णांक
xfs_attr3_rmt_stale(
	काष्ठा xfs_inode	*dp,
	xfs_dablk_t		blkno,
	पूर्णांक			blkcnt)
अणु
	काष्ठा xfs_bmbt_irec	map;
	पूर्णांक			nmap;
	पूर्णांक			error;

	/*
	 * Roll through the "value", invalidating the attribute value's
	 * blocks.
	 */
	जबतक (blkcnt > 0) अणु
		/*
		 * Try to remember where we decided to put the value.
		 */
		nmap = 1;
		error = xfs_bmapi_पढ़ो(dp, (xfs_fileoff_t)blkno, blkcnt,
				       &map, &nmap, XFS_BMAPI_ATTRFORK);
		अगर (error)
			वापस error;
		अगर (XFS_IS_CORRUPT(dp->i_mount, nmap != 1))
			वापस -EFSCORRUPTED;

		/*
		 * Mark any incore buffers क्रम the remote value as stale.  We
		 * never log remote attr value buffers, so the buffer should be
		 * easy to समाप्त.
		 */
		error = xfs_attr_rmtval_stale(dp, &map, 0);
		अगर (error)
			वापस error;

		blkno += map.br_blockcount;
		blkcnt -= map.br_blockcount;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Invalidate all of the "remote" value regions poपूर्णांकed to by a particular
 * leaf block.
 * Note that we must release the lock on the buffer so that we are not
 * caught holding something that the logging code wants to flush to disk.
 */
STATIC पूर्णांक
xfs_attr3_leaf_inactive(
	काष्ठा xfs_trans		**trans,
	काष्ठा xfs_inode		*dp,
	काष्ठा xfs_buf			*bp)
अणु
	काष्ठा xfs_attr3_icleaf_hdr	ichdr;
	काष्ठा xfs_mount		*mp = bp->b_mount;
	काष्ठा xfs_attr_leafblock	*leaf = bp->b_addr;
	काष्ठा xfs_attr_leaf_entry	*entry;
	काष्ठा xfs_attr_leaf_name_remote *name_rmt;
	पूर्णांक				error = 0;
	पूर्णांक				i;

	xfs_attr3_leaf_hdr_from_disk(mp->m_attr_geo, &ichdr, leaf);

	/*
	 * Find the remote value extents क्रम this leaf and invalidate their
	 * incore buffers.
	 */
	entry = xfs_attr3_leaf_entryp(leaf);
	क्रम (i = 0; i < ichdr.count; entry++, i++) अणु
		पूर्णांक		blkcnt;

		अगर (!entry->nameidx || (entry->flags & XFS_ATTR_LOCAL))
			जारी;

		name_rmt = xfs_attr3_leaf_name_remote(leaf, i);
		अगर (!name_rmt->valueblk)
			जारी;

		blkcnt = xfs_attr3_rmt_blocks(dp->i_mount,
				be32_to_cpu(name_rmt->valuelen));
		error = xfs_attr3_rmt_stale(dp,
				be32_to_cpu(name_rmt->valueblk), blkcnt);
		अगर (error)
			जाओ err;
	पूर्ण

	xfs_trans_brअन्यथा(*trans, bp);
err:
	वापस error;
पूर्ण

/*
 * Recurse (gasp!) through the attribute nodes until we find leaves.
 * We're करोing a depth-first traversal in order to invalidate everything.
 */
STATIC पूर्णांक
xfs_attr3_node_inactive(
	काष्ठा xfs_trans	**trans,
	काष्ठा xfs_inode	*dp,
	काष्ठा xfs_buf		*bp,
	पूर्णांक			level)
अणु
	काष्ठा xfs_mount	*mp = dp->i_mount;
	काष्ठा xfs_da_blkinfo	*info;
	xfs_dablk_t		child_fsb;
	xfs_daddr_t		parent_blkno, child_blkno;
	काष्ठा xfs_buf		*child_bp;
	काष्ठा xfs_da3_icnode_hdr ichdr;
	पूर्णांक			error, i;

	/*
	 * Since this code is recursive (gasp!) we must protect ourselves.
	 */
	अगर (level > XFS_DA_NODE_MAXDEPTH) अणु
		xfs_buf_mark_corrupt(bp);
		xfs_trans_brअन्यथा(*trans, bp);	/* no locks क्रम later trans */
		वापस -EFSCORRUPTED;
	पूर्ण

	xfs_da3_node_hdr_from_disk(dp->i_mount, &ichdr, bp->b_addr);
	parent_blkno = bp->b_bn;
	अगर (!ichdr.count) अणु
		xfs_trans_brअन्यथा(*trans, bp);
		वापस 0;
	पूर्ण
	child_fsb = be32_to_cpu(ichdr.btree[0].beक्रमe);
	xfs_trans_brअन्यथा(*trans, bp);	/* no locks क्रम later trans */

	/*
	 * If this is the node level just above the leaves, simply loop
	 * over the leaves removing all of them.  If this is higher up
	 * in the tree, recurse करोwnward.
	 */
	क्रम (i = 0; i < ichdr.count; i++) अणु
		/*
		 * Read the subsidiary block to see what we have to work with.
		 * Don't करो this in a transaction.  This is a depth-first
		 * traversal of the tree so we may deal with many blocks
		 * beक्रमe we come back to this one.
		 */
		error = xfs_da3_node_पढ़ो(*trans, dp, child_fsb, &child_bp,
					  XFS_ATTR_FORK);
		अगर (error)
			वापस error;

		/* save क्रम re-पढ़ो later */
		child_blkno = XFS_BUF_ADDR(child_bp);

		/*
		 * Invalidate the subtree, however we have to.
		 */
		info = child_bp->b_addr;
		चयन (info->magic) अणु
		हाल cpu_to_be16(XFS_DA_NODE_MAGIC):
		हाल cpu_to_be16(XFS_DA3_NODE_MAGIC):
			error = xfs_attr3_node_inactive(trans, dp, child_bp,
							level + 1);
			अवरोध;
		हाल cpu_to_be16(XFS_ATTR_LEAF_MAGIC):
		हाल cpu_to_be16(XFS_ATTR3_LEAF_MAGIC):
			error = xfs_attr3_leaf_inactive(trans, dp, child_bp);
			अवरोध;
		शेष:
			xfs_buf_mark_corrupt(child_bp);
			xfs_trans_brअन्यथा(*trans, child_bp);
			error = -EFSCORRUPTED;
			अवरोध;
		पूर्ण
		अगर (error)
			वापस error;

		/*
		 * Remove the subsidiary block from the cache and from the log.
		 */
		error = xfs_trans_get_buf(*trans, mp->m_ddev_targp,
				child_blkno,
				XFS_FSB_TO_BB(mp, mp->m_attr_geo->fsbcount), 0,
				&child_bp);
		अगर (error)
			वापस error;
		error = bp->b_error;
		अगर (error) अणु
			xfs_trans_brअन्यथा(*trans, child_bp);
			वापस error;
		पूर्ण
		xfs_trans_binval(*trans, child_bp);

		/*
		 * If we're not करोne, re-पढ़ो the parent to get the next
		 * child block number.
		 */
		अगर (i + 1 < ichdr.count) अणु
			काष्ठा xfs_da3_icnode_hdr phdr;

			error = xfs_da3_node_पढ़ो_mapped(*trans, dp,
					parent_blkno, &bp, XFS_ATTR_FORK);
			अगर (error)
				वापस error;
			xfs_da3_node_hdr_from_disk(dp->i_mount, &phdr,
						  bp->b_addr);
			child_fsb = be32_to_cpu(phdr.btree[i + 1].beक्रमe);
			xfs_trans_brअन्यथा(*trans, bp);
		पूर्ण
		/*
		 * Atomically commit the whole invalidate stuff.
		 */
		error = xfs_trans_roll_inode(trans, dp);
		अगर (error)
			वापस  error;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Indiscriminately delete the entire attribute विभाजन
 *
 * Recurse (gasp!) through the attribute nodes until we find leaves.
 * We're करोing a depth-first traversal in order to invalidate everything.
 */
अटल पूर्णांक
xfs_attr3_root_inactive(
	काष्ठा xfs_trans	**trans,
	काष्ठा xfs_inode	*dp)
अणु
	काष्ठा xfs_mount	*mp = dp->i_mount;
	काष्ठा xfs_da_blkinfo	*info;
	काष्ठा xfs_buf		*bp;
	xfs_daddr_t		blkno;
	पूर्णांक			error;

	/*
	 * Read block 0 to see what we have to work with.
	 * We only get here अगर we have extents, since we हटाओ
	 * the extents in reverse order the extent containing
	 * block 0 must still be there.
	 */
	error = xfs_da3_node_पढ़ो(*trans, dp, 0, &bp, XFS_ATTR_FORK);
	अगर (error)
		वापस error;
	blkno = bp->b_bn;

	/*
	 * Invalidate the tree, even अगर the "tree" is only a single leaf block.
	 * This is a depth-first traversal!
	 */
	info = bp->b_addr;
	चयन (info->magic) अणु
	हाल cpu_to_be16(XFS_DA_NODE_MAGIC):
	हाल cpu_to_be16(XFS_DA3_NODE_MAGIC):
		error = xfs_attr3_node_inactive(trans, dp, bp, 1);
		अवरोध;
	हाल cpu_to_be16(XFS_ATTR_LEAF_MAGIC):
	हाल cpu_to_be16(XFS_ATTR3_LEAF_MAGIC):
		error = xfs_attr3_leaf_inactive(trans, dp, bp);
		अवरोध;
	शेष:
		error = -EFSCORRUPTED;
		xfs_buf_mark_corrupt(bp);
		xfs_trans_brअन्यथा(*trans, bp);
		अवरोध;
	पूर्ण
	अगर (error)
		वापस error;

	/*
	 * Invalidate the incore copy of the root block.
	 */
	error = xfs_trans_get_buf(*trans, mp->m_ddev_targp, blkno,
			XFS_FSB_TO_BB(mp, mp->m_attr_geo->fsbcount), 0, &bp);
	अगर (error)
		वापस error;
	error = bp->b_error;
	अगर (error) अणु
		xfs_trans_brअन्यथा(*trans, bp);
		वापस error;
	पूर्ण
	xfs_trans_binval(*trans, bp);	/* हटाओ from cache */
	/*
	 * Commit the invalidate and start the next transaction.
	 */
	error = xfs_trans_roll_inode(trans, dp);

	वापस error;
पूर्ण

/*
 * xfs_attr_inactive समाप्तs all traces of an attribute विभाजन on an inode. It
 * हटाओs both the on-disk and in-memory inode विभाजन. Note that this also has to
 * handle the condition of inodes without attributes but with an attribute विभाजन
 * configured, so we can't use xfs_inode_hasattr() here.
 *
 * The in-memory attribute विभाजन is हटाओd even on error.
 */
पूर्णांक
xfs_attr_inactive(
	काष्ठा xfs_inode	*dp)
अणु
	काष्ठा xfs_trans	*trans;
	काष्ठा xfs_mount	*mp;
	पूर्णांक			lock_mode = XFS_ILOCK_SHARED;
	पूर्णांक			error = 0;

	mp = dp->i_mount;
	ASSERT(! XFS_NOT_DQATTACHED(mp, dp));

	xfs_ilock(dp, lock_mode);
	अगर (!XFS_IFORK_Q(dp))
		जाओ out_destroy_विभाजन;
	xfs_iunlock(dp, lock_mode);

	lock_mode = 0;

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_attrinval, 0, 0, 0, &trans);
	अगर (error)
		जाओ out_destroy_विभाजन;

	lock_mode = XFS_ILOCK_EXCL;
	xfs_ilock(dp, lock_mode);

	अगर (!XFS_IFORK_Q(dp))
		जाओ out_cancel;

	/*
	 * No need to make quota reservations here. We expect to release some
	 * blocks, not allocate, in the common हाल.
	 */
	xfs_trans_ijoin(trans, dp, 0);

	/*
	 * Invalidate and truncate the attribute विभाजन extents. Make sure the
	 * विभाजन actually has attributes as otherwise the invalidation has no
	 * blocks to पढ़ो and वापसs an error. In this हाल, just करो the विभाजन
	 * removal below.
	 */
	अगर (xfs_inode_hasattr(dp) &&
	    dp->i_afp->अगर_क्रमmat != XFS_DINODE_FMT_LOCAL) अणु
		error = xfs_attr3_root_inactive(&trans, dp);
		अगर (error)
			जाओ out_cancel;

		error = xfs_itruncate_extents(&trans, dp, XFS_ATTR_FORK, 0);
		अगर (error)
			जाओ out_cancel;
	पूर्ण

	/* Reset the attribute विभाजन - this also destroys the in-core विभाजन */
	xfs_attr_विभाजन_हटाओ(dp, trans);

	error = xfs_trans_commit(trans);
	xfs_iunlock(dp, lock_mode);
	वापस error;

out_cancel:
	xfs_trans_cancel(trans);
out_destroy_विभाजन:
	/* समाप्त the in-core attr विभाजन beक्रमe we drop the inode lock */
	अगर (dp->i_afp) अणु
		xfs_idestroy_विभाजन(dp->i_afp);
		kmem_cache_मुक्त(xfs_अगरork_zone, dp->i_afp);
		dp->i_afp = शून्य;
	पूर्ण
	अगर (lock_mode)
		xfs_iunlock(dp, lock_mode);
	वापस error;
पूर्ण
