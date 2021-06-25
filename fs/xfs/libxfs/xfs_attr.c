<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_defer.h"
#समावेश "xfs_da_format.h"
#समावेश "xfs_da_btree.h"
#समावेश "xfs_attr_sf.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_bmap_btree.h"
#समावेश "xfs_attr.h"
#समावेश "xfs_attr_leaf.h"
#समावेश "xfs_attr_remote.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_trans_space.h"
#समावेश "xfs_trace.h"

/*
 * xfs_attr.c
 *
 * Provide the बाह्यal पूर्णांकerfaces to manage attribute lists.
 */

/*========================================================================
 * Function prototypes क्रम the kernel.
 *========================================================================*/

/*
 * Internal routines when attribute list fits inside the inode.
 */
STATIC पूर्णांक xfs_attr_लघुक्रमm_addname(xfs_da_args_t *args);

/*
 * Internal routines when attribute list is one block.
 */
STATIC पूर्णांक xfs_attr_leaf_get(xfs_da_args_t *args);
STATIC पूर्णांक xfs_attr_leaf_addname(xfs_da_args_t *args);
STATIC पूर्णांक xfs_attr_leaf_हटाओname(xfs_da_args_t *args);
STATIC पूर्णांक xfs_attr_leaf_hasname(काष्ठा xfs_da_args *args, काष्ठा xfs_buf **bp);

/*
 * Internal routines when attribute list is more than one block.
 */
STATIC पूर्णांक xfs_attr_node_get(xfs_da_args_t *args);
STATIC पूर्णांक xfs_attr_node_addname(xfs_da_args_t *args);
STATIC पूर्णांक xfs_attr_node_हटाओname(xfs_da_args_t *args);
STATIC पूर्णांक xfs_attr_node_hasname(xfs_da_args_t *args,
				 काष्ठा xfs_da_state **state);
STATIC पूर्णांक xfs_attr_fillstate(xfs_da_state_t *state);
STATIC पूर्णांक xfs_attr_refillstate(xfs_da_state_t *state);

पूर्णांक
xfs_inode_hasattr(
	काष्ठा xfs_inode	*ip)
अणु
	अगर (!XFS_IFORK_Q(ip) ||
	    (ip->i_afp->अगर_क्रमmat == XFS_DINODE_FMT_EXTENTS &&
	     ip->i_afp->अगर_nextents == 0))
		वापस 0;
	वापस 1;
पूर्ण

/*
 * Returns true अगर the there is exactly only block in the attr विभाजन, in which
 * हाल the attribute विभाजन consists of a single leaf block entry.
 */
bool
xfs_attr_is_leaf(
	काष्ठा xfs_inode	*ip)
अणु
	काष्ठा xfs_अगरork	*अगरp = ip->i_afp;
	काष्ठा xfs_iext_cursor	icur;
	काष्ठा xfs_bmbt_irec	imap;

	अगर (अगरp->अगर_nextents != 1 || अगरp->अगर_क्रमmat != XFS_DINODE_FMT_EXTENTS)
		वापस false;

	xfs_iext_first(अगरp, &icur);
	xfs_iext_get_extent(अगरp, &icur, &imap);
	वापस imap.br_startoff == 0 && imap.br_blockcount == 1;
पूर्ण

/*========================================================================
 * Overall बाह्यal पूर्णांकerface routines.
 *========================================================================*/

/*
 * Retrieve an extended attribute and its value.  Must have ilock.
 * Returns 0 on successful retrieval, otherwise an error.
 */
पूर्णांक
xfs_attr_get_ilocked(
	काष्ठा xfs_da_args	*args)
अणु
	ASSERT(xfs_isilocked(args->dp, XFS_ILOCK_SHARED | XFS_ILOCK_EXCL));

	अगर (!xfs_inode_hasattr(args->dp))
		वापस -ENOATTR;

	अगर (args->dp->i_afp->अगर_क्रमmat == XFS_DINODE_FMT_LOCAL)
		वापस xfs_attr_लघुक्रमm_getvalue(args);
	अगर (xfs_attr_is_leaf(args->dp))
		वापस xfs_attr_leaf_get(args);
	वापस xfs_attr_node_get(args);
पूर्ण

/*
 * Retrieve an extended attribute by name, and its value अगर requested.
 *
 * If args->valuelen is zero, then the caller करोes not want the value, just an
 * indication whether the attribute exists and the size of the value अगर it
 * exists. The size is वापसed in args.valuelen.
 *
 * If args->value is शून्य but args->valuelen is non-zero, allocate the buffer
 * क्रम the value after existence of the attribute has been determined. The
 * caller always has to मुक्त args->value अगर it is set, no matter अगर this
 * function was successful or not.
 *
 * If the attribute is found, but exceeds the size limit set by the caller in
 * args->valuelen, वापस -दुस्फल with the size of the attribute that was found
 * in args->valuelen.
 */
पूर्णांक
xfs_attr_get(
	काष्ठा xfs_da_args	*args)
अणु
	uपूर्णांक			lock_mode;
	पूर्णांक			error;

	XFS_STATS_INC(args->dp->i_mount, xs_attr_get);

	अगर (XFS_FORCED_SHUTDOWN(args->dp->i_mount))
		वापस -EIO;

	args->geo = args->dp->i_mount->m_attr_geo;
	args->whichविभाजन = XFS_ATTR_FORK;
	args->hashval = xfs_da_hashname(args->name, args->namelen);

	/* Entirely possible to look up a name which करोesn't exist */
	args->op_flags = XFS_DA_OP_OKNOENT;

	lock_mode = xfs_ilock_attr_map_shared(args->dp);
	error = xfs_attr_get_ilocked(args);
	xfs_iunlock(args->dp, lock_mode);

	वापस error;
पूर्ण

/*
 * Calculate how many blocks we need क्रम the new attribute,
 */
STATIC पूर्णांक
xfs_attr_calc_size(
	काष्ठा xfs_da_args	*args,
	पूर्णांक			*local)
अणु
	काष्ठा xfs_mount	*mp = args->dp->i_mount;
	पूर्णांक			size;
	पूर्णांक			nblks;

	/*
	 * Determine space new attribute will use, and अगर it would be
	 * "local" or "remote" (note: local != अंतरभूत).
	 */
	size = xfs_attr_leaf_newentsize(args, local);
	nblks = XFS_DAENTER_SPACE_RES(mp, XFS_ATTR_FORK);
	अगर (*local) अणु
		अगर (size > (args->geo->blksize / 2)) अणु
			/* Double split possible */
			nblks *= 2;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Out of line attribute, cannot द्विगुन split, but
		 * make room क्रम the attribute value itself.
		 */
		uपूर्णांक	dblocks = xfs_attr3_rmt_blocks(mp, args->valuelen);
		nblks += dblocks;
		nblks += XFS_NEXTENTADD_SPACE_RES(mp, dblocks, XFS_ATTR_FORK);
	पूर्ण

	वापस nblks;
पूर्ण

STATIC पूर्णांक
xfs_attr_try_sf_addname(
	काष्ठा xfs_inode	*dp,
	काष्ठा xfs_da_args	*args)
अणु

	पूर्णांक			error;

	/*
	 * Build initial attribute list (अगर required).
	 */
	अगर (dp->i_afp->अगर_क्रमmat == XFS_DINODE_FMT_EXTENTS)
		xfs_attr_लघुक्रमm_create(args);

	error = xfs_attr_लघुक्रमm_addname(args);
	अगर (error == -ENOSPC)
		वापस error;

	/*
	 * Commit the लघुक्रमm mods, and we're करोne.
	 * NOTE: this is also the error path (EEXIST, etc).
	 */
	अगर (!error && !(args->op_flags & XFS_DA_OP_NOTIME))
		xfs_trans_ichgसमय(args->trans, dp, XFS_ICHGTIME_CHG);

	अगर (dp->i_mount->m_flags & XFS_MOUNT_WSYNC)
		xfs_trans_set_sync(args->trans);

	वापस error;
पूर्ण

/*
 * Check to see अगर the attr should be upgraded from non-existent or लघुक्रमm to
 * single-leaf-block attribute list.
 */
अटल अंतरभूत bool
xfs_attr_is_लघुक्रमm(
	काष्ठा xfs_inode    *ip)
अणु
	वापस ip->i_afp->अगर_क्रमmat == XFS_DINODE_FMT_LOCAL ||
	       (ip->i_afp->अगर_क्रमmat == XFS_DINODE_FMT_EXTENTS &&
		ip->i_afp->अगर_nextents == 0);
पूर्ण

/*
 * Attempts to set an attr in लघुक्रमm, or converts लघु क्रमm to leaf क्रमm अगर
 * there is not enough room.  If the attr is set, the transaction is committed
 * and set to शून्य.
 */
STATIC पूर्णांक
xfs_attr_set_लघुक्रमm(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_buf		**leaf_bp)
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	पूर्णांक			error, error2 = 0;

	/*
	 * Try to add the attr to the attribute list in the inode.
	 */
	error = xfs_attr_try_sf_addname(dp, args);
	अगर (error != -ENOSPC) अणु
		error2 = xfs_trans_commit(args->trans);
		args->trans = शून्य;
		वापस error ? error : error2;
	पूर्ण
	/*
	 * It won't fit in the लघुक्रमm, transक्रमm to a leaf block.  GROT:
	 * another possible req'mt क्रम a द्विगुन-split btree op.
	 */
	error = xfs_attr_लघुक्रमm_to_leaf(args, leaf_bp);
	अगर (error)
		वापस error;

	/*
	 * Prevent the leaf buffer from being unlocked so that a concurrent AIL
	 * push cannot grab the half-baked leaf buffer and run पूर्णांकo problems
	 * with the ग_लिखो verअगरier. Once we're करोne rolling the transaction we
	 * can release the hold and add the attr to the leaf.
	 */
	xfs_trans_bhold(args->trans, *leaf_bp);
	error = xfs_defer_finish(&args->trans);
	xfs_trans_bhold_release(args->trans, *leaf_bp);
	अगर (error) अणु
		xfs_trans_brअन्यथा(args->trans, *leaf_bp);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Set the attribute specअगरied in @args.
 */
पूर्णांक
xfs_attr_set_args(
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_buf          *leaf_bp = शून्य;
	पूर्णांक			error = 0;

	/*
	 * If the attribute list is alपढ़ोy in leaf क्रमmat, jump straight to
	 * leaf handling.  Otherwise, try to add the attribute to the लघुक्रमm
	 * list; अगर there's no room then convert the list to leaf क्रमmat and try
	 * again.
	 */
	अगर (xfs_attr_is_लघुक्रमm(dp)) अणु

		/*
		 * If the attr was successfully set in लघुक्रमm, the
		 * transaction is committed and set to शून्य.  Otherwise, is it
		 * converted from लघुक्रमm to leaf, and the transaction is
		 * retained.
		 */
		error = xfs_attr_set_लघुक्रमm(args, &leaf_bp);
		अगर (error || !args->trans)
			वापस error;
	पूर्ण

	अगर (xfs_attr_is_leaf(dp)) अणु
		error = xfs_attr_leaf_addname(args);
		अगर (error != -ENOSPC)
			वापस error;

		/*
		 * Promote the attribute list to the Btree क्रमmat.
		 */
		error = xfs_attr3_leaf_to_node(args);
		अगर (error)
			वापस error;

		/*
		 * Finish any deferred work items and roll the transaction once
		 * more.  The goal here is to call node_addname with the inode
		 * and transaction in the same state (inode locked and joined,
		 * transaction clean) no matter how we got to this step.
		 */
		error = xfs_defer_finish(&args->trans);
		अगर (error)
			वापस error;

		/*
		 * Commit the current trans (including the inode) and
		 * start a new one.
		 */
		error = xfs_trans_roll_inode(&args->trans, dp);
		अगर (error)
			वापस error;
	पूर्ण

	error = xfs_attr_node_addname(args);
	वापस error;
पूर्ण

/*
 * Return EEXIST अगर attr is found, or ENOATTR अगर not
 */
पूर्णांक
xfs_has_attr(
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_buf		*bp = शून्य;
	पूर्णांक			error;

	अगर (!xfs_inode_hasattr(dp))
		वापस -ENOATTR;

	अगर (dp->i_afp->अगर_क्रमmat == XFS_DINODE_FMT_LOCAL)
		वापस xfs_attr_sf_findname(args, शून्य, शून्य);

	अगर (xfs_attr_is_leaf(dp)) अणु
		error = xfs_attr_leaf_hasname(args, &bp);

		अगर (bp)
			xfs_trans_brअन्यथा(args->trans, bp);

		वापस error;
	पूर्ण

	वापस xfs_attr_node_hasname(args, शून्य);
पूर्ण

/*
 * Remove the attribute specअगरied in @args.
 */
पूर्णांक
xfs_attr_हटाओ_args(
	काष्ठा xfs_da_args      *args)
अणु
	अगर (!xfs_inode_hasattr(args->dp))
		वापस -ENOATTR;

	अगर (args->dp->i_afp->अगर_क्रमmat == XFS_DINODE_FMT_LOCAL)
		वापस xfs_attr_लघुक्रमm_हटाओ(args);
	अगर (xfs_attr_is_leaf(args->dp))
		वापस xfs_attr_leaf_हटाओname(args);
	वापस xfs_attr_node_हटाओname(args);
पूर्ण

/*
 * Note: If args->value is शून्य the attribute will be हटाओd, just like the
 * Linux ->setattr API.
 */
पूर्णांक
xfs_attr_set(
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	काष्ठा xfs_trans_res	tres;
	bool			rsvd = (args->attr_filter & XFS_ATTR_ROOT);
	पूर्णांक			error, local;
	पूर्णांक			rmt_blks = 0;
	अचिन्हित पूर्णांक		total;

	अगर (XFS_FORCED_SHUTDOWN(dp->i_mount))
		वापस -EIO;

	error = xfs_qm_dqattach(dp);
	अगर (error)
		वापस error;

	args->geo = mp->m_attr_geo;
	args->whichविभाजन = XFS_ATTR_FORK;
	args->hashval = xfs_da_hashname(args->name, args->namelen);

	/*
	 * We have no control over the attribute names that userspace passes us
	 * to हटाओ, so we have to allow the name lookup prior to attribute
	 * removal to fail as well.
	 */
	args->op_flags = XFS_DA_OP_OKNOENT;

	अगर (args->value) अणु
		XFS_STATS_INC(mp, xs_attr_set);

		args->op_flags |= XFS_DA_OP_ADDNAME;
		args->total = xfs_attr_calc_size(args, &local);

		/*
		 * If the inode करोesn't have an attribute विभाजन, add one.
		 * (inode must not be locked when we call this routine)
		 */
		अगर (XFS_IFORK_Q(dp) == 0) अणु
			पूर्णांक sf_size = माप(काष्ठा xfs_attr_sf_hdr) +
				xfs_attr_sf_entsize_byname(args->namelen,
						args->valuelen);

			error = xfs_bmap_add_attrविभाजन(dp, sf_size, rsvd);
			अगर (error)
				वापस error;
		पूर्ण

		tres.tr_logres = M_RES(mp)->tr_attrseपंचांग.tr_logres +
				 M_RES(mp)->tr_attrsetrt.tr_logres *
					args->total;
		tres.tr_logcount = XFS_ATTRSET_LOG_COUNT;
		tres.tr_logflags = XFS_TRANS_PERM_LOG_RES;
		total = args->total;

		अगर (!local)
			rmt_blks = xfs_attr3_rmt_blocks(mp, args->valuelen);
	पूर्ण अन्यथा अणु
		XFS_STATS_INC(mp, xs_attr_हटाओ);

		tres = M_RES(mp)->tr_attrrm;
		total = XFS_ATTRRM_SPACE_RES(mp);
		rmt_blks = xfs_attr3_rmt_blocks(mp, XFS_XATTR_SIZE_MAX);
	पूर्ण

	/*
	 * Root विभाजन attributes can use reserved data blocks क्रम this
	 * operation अगर necessary
	 */
	error = xfs_trans_alloc_inode(dp, &tres, total, 0, rsvd, &args->trans);
	अगर (error)
		वापस error;

	अगर (args->value || xfs_inode_hasattr(dp)) अणु
		error = xfs_iext_count_may_overflow(dp, XFS_ATTR_FORK,
				XFS_IEXT_ATTR_MANIP_CNT(rmt_blks));
		अगर (error)
			जाओ out_trans_cancel;
	पूर्ण

	अगर (args->value) अणु
		error = xfs_has_attr(args);
		अगर (error == -EEXIST && (args->attr_flags & XATTR_CREATE))
			जाओ out_trans_cancel;
		अगर (error == -ENOATTR && (args->attr_flags & XATTR_REPLACE))
			जाओ out_trans_cancel;
		अगर (error != -ENOATTR && error != -EEXIST)
			जाओ out_trans_cancel;

		error = xfs_attr_set_args(args);
		अगर (error)
			जाओ out_trans_cancel;
		/* लघुक्रमm attribute has alपढ़ोy been committed */
		अगर (!args->trans)
			जाओ out_unlock;
	पूर्ण अन्यथा अणु
		error = xfs_has_attr(args);
		अगर (error != -EEXIST)
			जाओ out_trans_cancel;

		error = xfs_attr_हटाओ_args(args);
		अगर (error)
			जाओ out_trans_cancel;
	पूर्ण

	/*
	 * If this is a synchronous mount, make sure that the
	 * transaction goes to disk beक्रमe वापसing to the user.
	 */
	अगर (mp->m_flags & XFS_MOUNT_WSYNC)
		xfs_trans_set_sync(args->trans);

	अगर (!(args->op_flags & XFS_DA_OP_NOTIME))
		xfs_trans_ichgसमय(args->trans, dp, XFS_ICHGTIME_CHG);

	/*
	 * Commit the last in the sequence of transactions.
	 */
	xfs_trans_log_inode(args->trans, dp, XFS_ILOG_CORE);
	error = xfs_trans_commit(args->trans);
out_unlock:
	xfs_iunlock(dp, XFS_ILOCK_EXCL);
	वापस error;

out_trans_cancel:
	अगर (args->trans)
		xfs_trans_cancel(args->trans);
	जाओ out_unlock;
पूर्ण

/*========================================================================
 * External routines when attribute list is inside the inode
 *========================================================================*/

अटल अंतरभूत पूर्णांक xfs_attr_sf_totsize(काष्ठा xfs_inode *dp)
अणु
	काष्ठा xfs_attr_लघुक्रमm *sf;

	sf = (काष्ठा xfs_attr_लघुक्रमm *)dp->i_afp->अगर_u1.अगर_data;
	वापस be16_to_cpu(sf->hdr.totsize);
पूर्ण

/*
 * Add a name to the लघुक्रमm attribute list काष्ठाure
 * This is the बाह्यal routine.
 */
STATIC पूर्णांक
xfs_attr_लघुक्रमm_addname(xfs_da_args_t *args)
अणु
	पूर्णांक newsize, विभाजनoff, retval;

	trace_xfs_attr_sf_addname(args);

	retval = xfs_attr_लघुक्रमm_lookup(args);
	अगर (retval == -ENOATTR && (args->attr_flags & XATTR_REPLACE))
		वापस retval;
	अगर (retval == -EEXIST) अणु
		अगर (args->attr_flags & XATTR_CREATE)
			वापस retval;
		retval = xfs_attr_लघुक्रमm_हटाओ(args);
		अगर (retval)
			वापस retval;
		/*
		 * Since we have हटाओd the old attr, clear ATTR_REPLACE so
		 * that the leaf क्रमmat add routine won't trip over the attr
		 * not being around.
		 */
		args->attr_flags &= ~XATTR_REPLACE;
	पूर्ण

	अगर (args->namelen >= XFS_ATTR_SF_ENTSIZE_MAX ||
	    args->valuelen >= XFS_ATTR_SF_ENTSIZE_MAX)
		वापस -ENOSPC;

	newsize = xfs_attr_sf_totsize(args->dp);
	newsize += xfs_attr_sf_entsize_byname(args->namelen, args->valuelen);

	विभाजनoff = xfs_attr_लघुक्रमm_bytesfit(args->dp, newsize);
	अगर (!विभाजनoff)
		वापस -ENOSPC;

	xfs_attr_लघुक्रमm_add(args, विभाजनoff);
	वापस 0;
पूर्ण


/*========================================================================
 * External routines when attribute list is one block
 *========================================================================*/

/* Store info about a remote block */
STATIC व्योम
xfs_attr_save_rmt_blk(
	काष्ठा xfs_da_args	*args)
अणु
	args->blkno2 = args->blkno;
	args->index2 = args->index;
	args->rmtblkno2 = args->rmtblkno;
	args->rmtblkcnt2 = args->rmtblkcnt;
	args->rmtvaluelen2 = args->rmtvaluelen;
पूर्ण

/* Set stored info about a remote block */
STATIC व्योम
xfs_attr_restore_rmt_blk(
	काष्ठा xfs_da_args	*args)
अणु
	args->blkno = args->blkno2;
	args->index = args->index2;
	args->rmtblkno = args->rmtblkno2;
	args->rmtblkcnt = args->rmtblkcnt2;
	args->rmtvaluelen = args->rmtvaluelen2;
पूर्ण

/*
 * Tries to add an attribute to an inode in leaf क्रमm
 *
 * This function is meant to execute as part of a delayed operation and leaves
 * the transaction handling to the caller.  On success the attribute is added
 * and the inode and transaction are left dirty.  If there is not enough space,
 * the attr data is converted to node क्रमmat and -ENOSPC is वापसed. Caller is
 * responsible क्रम handling the dirty inode and transaction or adding the attr
 * in node क्रमmat.
 */
STATIC पूर्णांक
xfs_attr_leaf_try_add(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_buf		*bp)
अणु
	पूर्णांक			retval;

	/*
	 * Look up the given attribute in the leaf block.  Figure out अगर
	 * the given flags produce an error or call क्रम an atomic नाम.
	 */
	retval = xfs_attr_leaf_hasname(args, &bp);
	अगर (retval != -ENOATTR && retval != -EEXIST)
		वापस retval;
	अगर (retval == -ENOATTR && (args->attr_flags & XATTR_REPLACE))
		जाओ out_brअन्यथा;
	अगर (retval == -EEXIST) अणु
		अगर (args->attr_flags & XATTR_CREATE)
			जाओ out_brअन्यथा;

		trace_xfs_attr_leaf_replace(args);

		/* save the attribute state क्रम later removal*/
		args->op_flags |= XFS_DA_OP_RENAME;	/* an atomic नाम */
		xfs_attr_save_rmt_blk(args);

		/*
		 * clear the remote attr state now that it is saved so that the
		 * values reflect the state of the attribute we are about to
		 * add, not the attribute we just found and will हटाओ later.
		 */
		args->rmtblkno = 0;
		args->rmtblkcnt = 0;
		args->rmtvaluelen = 0;
	पूर्ण

	/*
	 * Add the attribute to the leaf block
	 */
	वापस xfs_attr3_leaf_add(bp, args);

out_brअन्यथा:
	xfs_trans_brअन्यथा(args->trans, bp);
	वापस retval;
पूर्ण


/*
 * Add a name to the leaf attribute list काष्ठाure
 *
 * This leaf block cannot have a "remote" value, we only call this routine
 * अगर bmap_one_block() says there is only one block (ie: no remote blks).
 */
STATIC पूर्णांक
xfs_attr_leaf_addname(
	काष्ठा xfs_da_args	*args)
अणु
	पूर्णांक			error, विभाजनoff;
	काष्ठा xfs_buf		*bp = शून्य;
	काष्ठा xfs_inode	*dp = args->dp;

	trace_xfs_attr_leaf_addname(args);

	error = xfs_attr_leaf_try_add(args, bp);
	अगर (error)
		वापस error;

	/*
	 * Commit the transaction that added the attr name so that
	 * later routines can manage their own transactions.
	 */
	error = xfs_trans_roll_inode(&args->trans, dp);
	अगर (error)
		वापस error;

	/*
	 * If there was an out-of-line value, allocate the blocks we
	 * identअगरied क्रम its storage and copy the value.  This is करोne
	 * after we create the attribute so that we करोn't overflow the
	 * maximum size of a transaction and/or hit a deadlock.
	 */
	अगर (args->rmtblkno > 0) अणु
		error = xfs_attr_rmtval_set(args);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (!(args->op_flags & XFS_DA_OP_RENAME)) अणु
		/*
		 * Added a "remote" value, just clear the incomplete flag.
		 */
		अगर (args->rmtblkno > 0)
			error = xfs_attr3_leaf_clearflag(args);

		वापस error;
	पूर्ण

	/*
	 * If this is an atomic नाम operation, we must "flip" the incomplete
	 * flags on the "new" and "old" attribute/value pairs so that one
	 * disappears and one appears atomically.  Then we must हटाओ the "old"
	 * attribute/value pair.
	 *
	 * In a separate transaction, set the incomplete flag on the "old" attr
	 * and clear the incomplete flag on the "new" attr.
	 */

	error = xfs_attr3_leaf_flipflags(args);
	अगर (error)
		वापस error;
	/*
	 * Commit the flag value change and start the next trans in series.
	 */
	error = xfs_trans_roll_inode(&args->trans, args->dp);
	अगर (error)
		वापस error;

	/*
	 * Dismantle the "old" attribute/value pair by removing a "remote" value
	 * (अगर it exists).
	 */
	xfs_attr_restore_rmt_blk(args);

	अगर (args->rmtblkno) अणु
		error = xfs_attr_rmtval_invalidate(args);
		अगर (error)
			वापस error;

		error = xfs_attr_rmtval_हटाओ(args);
		अगर (error)
			वापस error;
	पूर्ण

	/*
	 * Read in the block containing the "old" attr, then हटाओ the "old"
	 * attr from that block (neat, huh!)
	 */
	error = xfs_attr3_leaf_पढ़ो(args->trans, args->dp, args->blkno,
				   &bp);
	अगर (error)
		वापस error;

	xfs_attr3_leaf_हटाओ(bp, args);

	/*
	 * If the result is small enough, shrink it all पूर्णांकo the inode.
	 */
	विभाजनoff = xfs_attr_लघुक्रमm_allfit(bp, dp);
	अगर (विभाजनoff)
		error = xfs_attr3_leaf_to_लघुक्रमm(bp, args, विभाजनoff);
		/* bp is gone due to xfs_da_shrink_inode */

	वापस error;
पूर्ण

/*
 * Return EEXIST अगर attr is found, or ENOATTR अगर not
 */
STATIC पूर्णांक
xfs_attr_leaf_hasname(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_buf		**bp)
अणु
	पूर्णांक                     error = 0;

	error = xfs_attr3_leaf_पढ़ो(args->trans, args->dp, 0, bp);
	अगर (error)
		वापस error;

	error = xfs_attr3_leaf_lookup_पूर्णांक(*bp, args);
	अगर (error != -ENOATTR && error != -EEXIST)
		xfs_trans_brअन्यथा(args->trans, *bp);

	वापस error;
पूर्ण

/*
 * Remove a name from the leaf attribute list काष्ठाure
 *
 * This leaf block cannot have a "remote" value, we only call this routine
 * अगर bmap_one_block() says there is only one block (ie: no remote blks).
 */
STATIC पूर्णांक
xfs_attr_leaf_हटाओname(
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_inode	*dp;
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error, विभाजनoff;

	trace_xfs_attr_leaf_हटाओname(args);

	/*
	 * Remove the attribute.
	 */
	dp = args->dp;

	error = xfs_attr_leaf_hasname(args, &bp);

	अगर (error == -ENOATTR) अणु
		xfs_trans_brअन्यथा(args->trans, bp);
		वापस error;
	पूर्ण अन्यथा अगर (error != -EEXIST)
		वापस error;

	xfs_attr3_leaf_हटाओ(bp, args);

	/*
	 * If the result is small enough, shrink it all पूर्णांकo the inode.
	 */
	विभाजनoff = xfs_attr_लघुक्रमm_allfit(bp, dp);
	अगर (विभाजनoff)
		वापस xfs_attr3_leaf_to_लघुक्रमm(bp, args, विभाजनoff);
		/* bp is gone due to xfs_da_shrink_inode */

	वापस 0;
पूर्ण

/*
 * Look up a name in a leaf attribute list काष्ठाure.
 *
 * This leaf block cannot have a "remote" value, we only call this routine
 * अगर bmap_one_block() says there is only one block (ie: no remote blks).
 *
 * Returns 0 on successful retrieval, otherwise an error.
 */
STATIC पूर्णांक
xfs_attr_leaf_get(xfs_da_args_t *args)
अणु
	काष्ठा xfs_buf *bp;
	पूर्णांक error;

	trace_xfs_attr_leaf_get(args);

	error = xfs_attr_leaf_hasname(args, &bp);

	अगर (error == -ENOATTR)  अणु
		xfs_trans_brअन्यथा(args->trans, bp);
		वापस error;
	पूर्ण अन्यथा अगर (error != -EEXIST)
		वापस error;


	error = xfs_attr3_leaf_getvalue(bp, args);
	xfs_trans_brअन्यथा(args->trans, bp);
	वापस error;
पूर्ण

/*
 * Return EEXIST अगर attr is found, or ENOATTR अगर not
 * statep: If not null is set to poपूर्णांक at the found state.  Caller will
 *         be responsible क्रम मुक्तing the state in this हाल.
 */
STATIC पूर्णांक
xfs_attr_node_hasname(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_da_state	**statep)
अणु
	काष्ठा xfs_da_state	*state;
	पूर्णांक			retval, error;

	state = xfs_da_state_alloc(args);
	अगर (statep != शून्य)
		*statep = शून्य;

	/*
	 * Search to see अगर name exists, and get back a poपूर्णांकer to it.
	 */
	error = xfs_da3_node_lookup_पूर्णांक(state, &retval);
	अगर (error) अणु
		xfs_da_state_मुक्त(state);
		वापस error;
	पूर्ण

	अगर (statep != शून्य)
		*statep = state;
	अन्यथा
		xfs_da_state_मुक्त(state);
	वापस retval;
पूर्ण

/*========================================================================
 * External routines when attribute list size > geo->blksize
 *========================================================================*/

/*
 * Add a name to a Btree-क्रमmat attribute list.
 *
 * This will involve walking करोwn the Btree, and may involve splitting
 * leaf nodes and even splitting पूर्णांकermediate nodes up to and including
 * the root node (a special हाल of an पूर्णांकermediate node).
 *
 * "Remote" attribute values confuse the issue and atomic नाम operations
 * add a whole extra layer of confusion on top of that.
 */
STATIC पूर्णांक
xfs_attr_node_addname(
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_da_state	*state;
	काष्ठा xfs_da_state_blk	*blk;
	काष्ठा xfs_inode	*dp;
	पूर्णांक			retval, error;

	trace_xfs_attr_node_addname(args);

	/*
	 * Fill in bucket of arguments/results/context to carry around.
	 */
	dp = args->dp;
restart:
	/*
	 * Search to see अगर name alपढ़ोy exists, and get back a poपूर्णांकer
	 * to where it should go.
	 */
	error = 0;
	retval = xfs_attr_node_hasname(args, &state);
	अगर (retval != -ENOATTR && retval != -EEXIST)
		जाओ out;

	blk = &state->path.blk[ state->path.active-1 ];
	ASSERT(blk->magic == XFS_ATTR_LEAF_MAGIC);
	अगर (retval == -ENOATTR && (args->attr_flags & XATTR_REPLACE))
		जाओ out;
	अगर (retval == -EEXIST) अणु
		अगर (args->attr_flags & XATTR_CREATE)
			जाओ out;

		trace_xfs_attr_node_replace(args);

		/* save the attribute state क्रम later removal*/
		args->op_flags |= XFS_DA_OP_RENAME;	/* atomic नाम op */
		xfs_attr_save_rmt_blk(args);

		/*
		 * clear the remote attr state now that it is saved so that the
		 * values reflect the state of the attribute we are about to
		 * add, not the attribute we just found and will हटाओ later.
		 */
		args->rmtblkno = 0;
		args->rmtblkcnt = 0;
		args->rmtvaluelen = 0;
	पूर्ण

	retval = xfs_attr3_leaf_add(blk->bp, state->args);
	अगर (retval == -ENOSPC) अणु
		अगर (state->path.active == 1) अणु
			/*
			 * Its really a single leaf node, but it had
			 * out-of-line values so it looked like it *might*
			 * have been a b-tree.
			 */
			xfs_da_state_मुक्त(state);
			state = शून्य;
			error = xfs_attr3_leaf_to_node(args);
			अगर (error)
				जाओ out;
			error = xfs_defer_finish(&args->trans);
			अगर (error)
				जाओ out;

			/*
			 * Commit the node conversion and start the next
			 * trans in the chain.
			 */
			error = xfs_trans_roll_inode(&args->trans, dp);
			अगर (error)
				जाओ out;

			जाओ restart;
		पूर्ण

		/*
		 * Split as many Btree elements as required.
		 * This code tracks the new and old attr's location
		 * in the index/blkno/rmtblkno/rmtblkcnt fields and
		 * in the index2/blkno2/rmtblkno2/rmtblkcnt2 fields.
		 */
		error = xfs_da3_split(state);
		अगर (error)
			जाओ out;
		error = xfs_defer_finish(&args->trans);
		अगर (error)
			जाओ out;
	पूर्ण अन्यथा अणु
		/*
		 * Addition succeeded, update Btree hashvals.
		 */
		xfs_da3_fixhashpath(state, &state->path);
	पूर्ण

	/*
	 * Kill the state काष्ठाure, we're करोne with it and need to
	 * allow the buffers to come back later.
	 */
	xfs_da_state_मुक्त(state);
	state = शून्य;

	/*
	 * Commit the leaf addition or btree split and start the next
	 * trans in the chain.
	 */
	error = xfs_trans_roll_inode(&args->trans, dp);
	अगर (error)
		जाओ out;

	/*
	 * If there was an out-of-line value, allocate the blocks we
	 * identअगरied क्रम its storage and copy the value.  This is करोne
	 * after we create the attribute so that we करोn't overflow the
	 * maximum size of a transaction and/or hit a deadlock.
	 */
	अगर (args->rmtblkno > 0) अणु
		error = xfs_attr_rmtval_set(args);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (!(args->op_flags & XFS_DA_OP_RENAME)) अणु
		/*
		 * Added a "remote" value, just clear the incomplete flag.
		 */
		अगर (args->rmtblkno > 0)
			error = xfs_attr3_leaf_clearflag(args);
		retval = error;
		जाओ out;
	पूर्ण

	/*
	 * If this is an atomic नाम operation, we must "flip" the incomplete
	 * flags on the "new" and "old" attribute/value pairs so that one
	 * disappears and one appears atomically.  Then we must हटाओ the "old"
	 * attribute/value pair.
	 *
	 * In a separate transaction, set the incomplete flag on the "old" attr
	 * and clear the incomplete flag on the "new" attr.
	 */
	error = xfs_attr3_leaf_flipflags(args);
	अगर (error)
		जाओ out;
	/*
	 * Commit the flag value change and start the next trans in series
	 */
	error = xfs_trans_roll_inode(&args->trans, args->dp);
	अगर (error)
		जाओ out;

	/*
	 * Dismantle the "old" attribute/value pair by removing a "remote" value
	 * (अगर it exists).
	 */
	xfs_attr_restore_rmt_blk(args);

	अगर (args->rmtblkno) अणु
		error = xfs_attr_rmtval_invalidate(args);
		अगर (error)
			वापस error;

		error = xfs_attr_rmtval_हटाओ(args);
		अगर (error)
			वापस error;
	पूर्ण

	/*
	 * Re-find the "old" attribute entry after any split ops. The INCOMPLETE
	 * flag means that we will find the "old" attr, not the "new" one.
	 */
	args->attr_filter |= XFS_ATTR_INCOMPLETE;
	state = xfs_da_state_alloc(args);
	state->inleaf = 0;
	error = xfs_da3_node_lookup_पूर्णांक(state, &retval);
	अगर (error)
		जाओ out;

	/*
	 * Remove the name and update the hashvals in the tree.
	 */
	blk = &state->path.blk[state->path.active-1];
	ASSERT(blk->magic == XFS_ATTR_LEAF_MAGIC);
	error = xfs_attr3_leaf_हटाओ(blk->bp, args);
	xfs_da3_fixhashpath(state, &state->path);

	/*
	 * Check to see अगर the tree needs to be collapsed.
	 */
	अगर (retval && (state->path.active > 1)) अणु
		error = xfs_da3_join(state);
		अगर (error)
			जाओ out;
	पूर्ण
	retval = error = 0;

out:
	अगर (state)
		xfs_da_state_मुक्त(state);
	अगर (error)
		वापस error;
	वापस retval;
पूर्ण

/*
 * Shrink an attribute from leaf to लघुक्रमm
 */
STATIC पूर्णांक
xfs_attr_node_shrink(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_da_state     *state)
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	पूर्णांक			error, विभाजनoff;
	काष्ठा xfs_buf		*bp;

	/*
	 * Have to get rid of the copy of this dabuf in the state.
	 */
	ASSERT(state->path.active == 1);
	ASSERT(state->path.blk[0].bp);
	state->path.blk[0].bp = शून्य;

	error = xfs_attr3_leaf_पढ़ो(args->trans, args->dp, 0, &bp);
	अगर (error)
		वापस error;

	विभाजनoff = xfs_attr_लघुक्रमm_allfit(bp, dp);
	अगर (विभाजनoff) अणु
		error = xfs_attr3_leaf_to_लघुक्रमm(bp, args, विभाजनoff);
		/* bp is gone due to xfs_da_shrink_inode */
	पूर्ण अन्यथा
		xfs_trans_brअन्यथा(args->trans, bp);

	वापस error;
पूर्ण

/*
 * Mark an attribute entry INCOMPLETE and save poपूर्णांकers to the relevant buffers
 * क्रम later deletion of the entry.
 */
STATIC पूर्णांक
xfs_attr_leaf_mark_incomplete(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_da_state	*state)
अणु
	पूर्णांक			error;

	/*
	 * Fill in disk block numbers in the state काष्ठाure
	 * so that we can get the buffers back after we commit
	 * several transactions in the following calls.
	 */
	error = xfs_attr_fillstate(state);
	अगर (error)
		वापस error;

	/*
	 * Mark the attribute as INCOMPLETE
	 */
	वापस xfs_attr3_leaf_setflag(args);
पूर्ण

/*
 * Initial setup क्रम xfs_attr_node_हटाओname.  Make sure the attr is there and
 * the blocks are valid.  Attr keys with remote blocks will be marked
 * incomplete.
 */
STATIC
पूर्णांक xfs_attr_node_हटाओname_setup(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_da_state	**state)
अणु
	पूर्णांक			error;

	error = xfs_attr_node_hasname(args, state);
	अगर (error != -EEXIST)
		वापस error;

	ASSERT((*state)->path.blk[(*state)->path.active - 1].bp != शून्य);
	ASSERT((*state)->path.blk[(*state)->path.active - 1].magic ==
		XFS_ATTR_LEAF_MAGIC);

	अगर (args->rmtblkno > 0) अणु
		error = xfs_attr_leaf_mark_incomplete(args, *state);
		अगर (error)
			वापस error;

		वापस xfs_attr_rmtval_invalidate(args);
	पूर्ण

	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_attr_node_हटाओ_rmt(
	काष्ठा xfs_da_args	*args,
	काष्ठा xfs_da_state	*state)
अणु
	पूर्णांक			error = 0;

	error = xfs_attr_rmtval_हटाओ(args);
	अगर (error)
		वापस error;

	/*
	 * Refill the state काष्ठाure with buffers, the prior calls released our
	 * buffers.
	 */
	वापस xfs_attr_refillstate(state);
पूर्ण

/*
 * Remove a name from a B-tree attribute list.
 *
 * This will involve walking करोwn the Btree, and may involve joining
 * leaf nodes and even joining पूर्णांकermediate nodes up to and including
 * the root node (a special हाल of an पूर्णांकermediate node).
 */
STATIC पूर्णांक
xfs_attr_node_हटाओname(
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_da_state	*state;
	काष्ठा xfs_da_state_blk	*blk;
	पूर्णांक			retval, error;
	काष्ठा xfs_inode	*dp = args->dp;

	trace_xfs_attr_node_हटाओname(args);

	error = xfs_attr_node_हटाओname_setup(args, &state);
	अगर (error)
		जाओ out;

	/*
	 * If there is an out-of-line value, de-allocate the blocks.
	 * This is करोne beक्रमe we हटाओ the attribute so that we करोn't
	 * overflow the maximum size of a transaction and/or hit a deadlock.
	 */
	अगर (args->rmtblkno > 0) अणु
		error = xfs_attr_node_हटाओ_rmt(args, state);
		अगर (error)
			जाओ out;
	पूर्ण

	/*
	 * Remove the name and update the hashvals in the tree.
	 */
	blk = &state->path.blk[ state->path.active-1 ];
	ASSERT(blk->magic == XFS_ATTR_LEAF_MAGIC);
	retval = xfs_attr3_leaf_हटाओ(blk->bp, args);
	xfs_da3_fixhashpath(state, &state->path);

	/*
	 * Check to see अगर the tree needs to be collapsed.
	 */
	अगर (retval && (state->path.active > 1)) अणु
		error = xfs_da3_join(state);
		अगर (error)
			जाओ out;
		error = xfs_defer_finish(&args->trans);
		अगर (error)
			जाओ out;
		/*
		 * Commit the Btree join operation and start a new trans.
		 */
		error = xfs_trans_roll_inode(&args->trans, dp);
		अगर (error)
			जाओ out;
	पूर्ण

	/*
	 * If the result is small enough, push it all पूर्णांकo the inode.
	 */
	अगर (xfs_attr_is_leaf(dp))
		error = xfs_attr_node_shrink(args, state);

out:
	अगर (state)
		xfs_da_state_मुक्त(state);
	वापस error;
पूर्ण

/*
 * Fill in the disk block numbers in the state काष्ठाure क्रम the buffers
 * that are attached to the state काष्ठाure.
 * This is करोne so that we can quickly reattach ourselves to those buffers
 * after some set of transaction commits have released these buffers.
 */
STATIC पूर्णांक
xfs_attr_fillstate(xfs_da_state_t *state)
अणु
	xfs_da_state_path_t *path;
	xfs_da_state_blk_t *blk;
	पूर्णांक level;

	trace_xfs_attr_fillstate(state->args);

	/*
	 * Roll करोwn the "path" in the state काष्ठाure, storing the on-disk
	 * block number क्रम those buffers in the "path".
	 */
	path = &state->path;
	ASSERT((path->active >= 0) && (path->active < XFS_DA_NODE_MAXDEPTH));
	क्रम (blk = path->blk, level = 0; level < path->active; blk++, level++) अणु
		अगर (blk->bp) अणु
			blk->disk_blkno = XFS_BUF_ADDR(blk->bp);
			blk->bp = शून्य;
		पूर्ण अन्यथा अणु
			blk->disk_blkno = 0;
		पूर्ण
	पूर्ण

	/*
	 * Roll करोwn the "altpath" in the state काष्ठाure, storing the on-disk
	 * block number क्रम those buffers in the "altpath".
	 */
	path = &state->altpath;
	ASSERT((path->active >= 0) && (path->active < XFS_DA_NODE_MAXDEPTH));
	क्रम (blk = path->blk, level = 0; level < path->active; blk++, level++) अणु
		अगर (blk->bp) अणु
			blk->disk_blkno = XFS_BUF_ADDR(blk->bp);
			blk->bp = शून्य;
		पूर्ण अन्यथा अणु
			blk->disk_blkno = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Reattach the buffers to the state काष्ठाure based on the disk block
 * numbers stored in the state काष्ठाure.
 * This is करोne after some set of transaction commits have released those
 * buffers from our grip.
 */
STATIC पूर्णांक
xfs_attr_refillstate(xfs_da_state_t *state)
अणु
	xfs_da_state_path_t *path;
	xfs_da_state_blk_t *blk;
	पूर्णांक level, error;

	trace_xfs_attr_refillstate(state->args);

	/*
	 * Roll करोwn the "path" in the state काष्ठाure, storing the on-disk
	 * block number क्रम those buffers in the "path".
	 */
	path = &state->path;
	ASSERT((path->active >= 0) && (path->active < XFS_DA_NODE_MAXDEPTH));
	क्रम (blk = path->blk, level = 0; level < path->active; blk++, level++) अणु
		अगर (blk->disk_blkno) अणु
			error = xfs_da3_node_पढ़ो_mapped(state->args->trans,
					state->args->dp, blk->disk_blkno,
					&blk->bp, XFS_ATTR_FORK);
			अगर (error)
				वापस error;
		पूर्ण अन्यथा अणु
			blk->bp = शून्य;
		पूर्ण
	पूर्ण

	/*
	 * Roll करोwn the "altpath" in the state काष्ठाure, storing the on-disk
	 * block number क्रम those buffers in the "altpath".
	 */
	path = &state->altpath;
	ASSERT((path->active >= 0) && (path->active < XFS_DA_NODE_MAXDEPTH));
	क्रम (blk = path->blk, level = 0; level < path->active; blk++, level++) अणु
		अगर (blk->disk_blkno) अणु
			error = xfs_da3_node_पढ़ो_mapped(state->args->trans,
					state->args->dp, blk->disk_blkno,
					&blk->bp, XFS_ATTR_FORK);
			अगर (error)
				वापस error;
		पूर्ण अन्यथा अणु
			blk->bp = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Retrieve the attribute data from a node attribute list.
 *
 * This routine माला_लो called क्रम any attribute विभाजन that has more than one
 * block, ie: both true Btree attr lists and क्रम single-leaf-blocks with
 * "remote" values taking up more blocks.
 *
 * Returns 0 on successful retrieval, otherwise an error.
 */
STATIC पूर्णांक
xfs_attr_node_get(
	काष्ठा xfs_da_args	*args)
अणु
	काष्ठा xfs_da_state	*state;
	काष्ठा xfs_da_state_blk	*blk;
	पूर्णांक			i;
	पूर्णांक			error;

	trace_xfs_attr_node_get(args);

	/*
	 * Search to see अगर name exists, and get back a poपूर्णांकer to it.
	 */
	error = xfs_attr_node_hasname(args, &state);
	अगर (error != -EEXIST)
		जाओ out_release;

	/*
	 * Get the value, local or "remote"
	 */
	blk = &state->path.blk[state->path.active - 1];
	error = xfs_attr3_leaf_getvalue(blk->bp, args);

	/*
	 * If not in a transaction, we have to release all the buffers.
	 */
out_release:
	क्रम (i = 0; state != शून्य && i < state->path.active; i++) अणु
		xfs_trans_brअन्यथा(args->trans, state->path.blk[i].bp);
		state->path.blk[i].bp = शून्य;
	पूर्ण

	अगर (state)
		xfs_da_state_मुक्त(state);
	वापस error;
पूर्ण

/* Returns true अगर the attribute entry name is valid. */
bool
xfs_attr_namecheck(
	स्थिर व्योम	*name,
	माप_प्रकार		length)
अणु
	/*
	 * MAXNAMELEN includes the trailing null, but (name/length) leave it
	 * out, so use >= क्रम the length check.
	 */
	अगर (length >= MAXNAMELEN)
		वापस false;

	/* There shouldn't be any nulls here */
	वापस !स_प्रथम(name, 0, length);
पूर्ण
