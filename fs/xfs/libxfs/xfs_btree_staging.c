<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2020 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
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
#समावेश "xfs_btree.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_btree_staging.h"

/*
 * Staging Cursors and Fake Roots क्रम Btrees
 * =========================================
 *
 * A staging btree cursor is a special type of btree cursor that callers must
 * use to स्थिरruct a new btree index using the btree bulk loader code.  The
 * bulk loading code uses the staging btree cursor to असलtract the details of
 * initializing new btree blocks and filling them with records or key/ptr
 * pairs.  Regular btree operations (e.g. queries and modअगरications) are not
 * supported with staging cursors, and callers must not invoke them.
 *
 * Fake root काष्ठाures contain all the inक्रमmation about a btree that is under
 * स्थिरruction by the bulk loading code.  Staging btree cursors poपूर्णांक to fake
 * root काष्ठाures instead of the usual AG header or inode काष्ठाure.
 *
 * Callers are expected to initialize a fake root काष्ठाure and pass it पूर्णांकo
 * the _stage_cursor function क्रम a specअगरic btree type.  When bulk loading is
 * complete, callers should call the _commit_staged_btree function क्रम that
 * specअगरic btree type to commit the new btree पूर्णांकo the fileप्रणाली.
 */

/*
 * Don't allow staging cursors to be duplicated because they're supposed to be
 * kept निजी to a single thपढ़ो.
 */
STATIC काष्ठा xfs_btree_cur *
xfs_btree_fakeroot_dup_cursor(
	काष्ठा xfs_btree_cur	*cur)
अणु
	ASSERT(0);
	वापस शून्य;
पूर्ण

/*
 * Don't allow block allocation क्रम a staging cursor, because staging cursors
 * करो not support regular btree modअगरications.
 *
 * Bulk loading uses a separate callback to obtain new blocks from a
 * pपुनः_स्मृतिated list, which prevents ENOSPC failures during loading.
 */
STATIC पूर्णांक
xfs_btree_fakeroot_alloc_block(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*start_bno,
	जोड़ xfs_btree_ptr	*new_bno,
	पूर्णांक			*stat)
अणु
	ASSERT(0);
	वापस -EFSCORRUPTED;
पूर्ण

/*
 * Don't allow block मुक्तing क्रम a staging cursor, because staging cursors
 * करो not support regular btree modअगरications.
 */
STATIC पूर्णांक
xfs_btree_fakeroot_मुक्त_block(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_buf		*bp)
अणु
	ASSERT(0);
	वापस -EFSCORRUPTED;
पूर्ण

/* Initialize a poपूर्णांकer to the root block from the fakeroot. */
STATIC व्योम
xfs_btree_fakeroot_init_ptr_from_cur(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*ptr)
अणु
	काष्ठा xbtree_afakeroot	*afake;

	ASSERT(cur->bc_flags & XFS_BTREE_STAGING);

	afake = cur->bc_ag.afake;
	ptr->s = cpu_to_be32(afake->af_root);
पूर्ण

/*
 * Bulk Loading क्रम AG Btrees
 * ==========================
 *
 * For a btree rooted in an AG header, pass a xbtree_afakeroot काष्ठाure to the
 * staging cursor.  Callers should initialize this to zero.
 *
 * The _stage_cursor() function क्रम a specअगरic btree type should call
 * xfs_btree_stage_afakeroot to set up the in-memory cursor as a staging
 * cursor.  The corresponding _commit_staged_btree() function should log the
 * new root and call xfs_btree_commit_afakeroot() to transक्रमm the staging
 * cursor पूर्णांकo a regular btree cursor.
 */

/* Update the btree root inक्रमmation क्रम a per-AG fake root. */
STATIC व्योम
xfs_btree_afakeroot_set_root(
	काष्ठा xfs_btree_cur	*cur,
	जोड़ xfs_btree_ptr	*ptr,
	पूर्णांक			inc)
अणु
	काष्ठा xbtree_afakeroot	*afake = cur->bc_ag.afake;

	ASSERT(cur->bc_flags & XFS_BTREE_STAGING);
	afake->af_root = be32_to_cpu(ptr->s);
	afake->af_levels += inc;
पूर्ण

/*
 * Initialize a AG-rooted btree cursor with the given AG btree fake root.
 * The btree cursor's bc_ops will be overridden as needed to make the staging
 * functionality work.
 */
व्योम
xfs_btree_stage_afakeroot(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xbtree_afakeroot		*afake)
अणु
	काष्ठा xfs_btree_ops		*nops;

	ASSERT(!(cur->bc_flags & XFS_BTREE_STAGING));
	ASSERT(!(cur->bc_flags & XFS_BTREE_ROOT_IN_INODE));
	ASSERT(cur->bc_tp == शून्य);

	nops = kmem_alloc(माप(काष्ठा xfs_btree_ops), KM_NOFS);
	स_नकल(nops, cur->bc_ops, माप(काष्ठा xfs_btree_ops));
	nops->alloc_block = xfs_btree_fakeroot_alloc_block;
	nops->मुक्त_block = xfs_btree_fakeroot_मुक्त_block;
	nops->init_ptr_from_cur = xfs_btree_fakeroot_init_ptr_from_cur;
	nops->set_root = xfs_btree_afakeroot_set_root;
	nops->dup_cursor = xfs_btree_fakeroot_dup_cursor;

	cur->bc_ag.afake = afake;
	cur->bc_nlevels = afake->af_levels;
	cur->bc_ops = nops;
	cur->bc_flags |= XFS_BTREE_STAGING;
पूर्ण

/*
 * Transक्रमm an AG-rooted staging btree cursor back पूर्णांकo a regular cursor by
 * substituting a real btree root क्रम the fake one and restoring normal btree
 * cursor ops.  The caller must log the btree root change prior to calling
 * this.
 */
व्योम
xfs_btree_commit_afakeroot(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_buf			*agbp,
	स्थिर काष्ठा xfs_btree_ops	*ops)
अणु
	ASSERT(cur->bc_flags & XFS_BTREE_STAGING);
	ASSERT(cur->bc_tp == शून्य);

	trace_xfs_btree_commit_afakeroot(cur);

	kmem_मुक्त((व्योम *)cur->bc_ops);
	cur->bc_ag.agbp = agbp;
	cur->bc_ops = ops;
	cur->bc_flags &= ~XFS_BTREE_STAGING;
	cur->bc_tp = tp;
पूर्ण

/*
 * Bulk Loading क्रम Inode-Rooted Btrees
 * ====================================
 *
 * For a btree rooted in an inode विभाजन, pass a xbtree_अगरakeroot काष्ठाure to
 * the staging cursor.  This काष्ठाure should be initialized as follows:
 *
 * - अगर_विभाजन_size field should be set to the number of bytes available to the
 *   विभाजन in the inode.
 *
 * - अगर_विभाजन should poपूर्णांक to a freshly allocated काष्ठा xfs_अगरork.
 *
 * - अगर_क्रमmat should be set to the appropriate विभाजन type (e.g.
 *   XFS_DINODE_FMT_BTREE).
 *
 * All other fields must be zero.
 *
 * The _stage_cursor() function क्रम a specअगरic btree type should call
 * xfs_btree_stage_अगरakeroot to set up the in-memory cursor as a staging
 * cursor.  The corresponding _commit_staged_btree() function should log the
 * new root and call xfs_btree_commit_अगरakeroot() to transक्रमm the staging
 * cursor पूर्णांकo a regular btree cursor.
 */

/*
 * Initialize an inode-rooted btree cursor with the given inode btree fake
 * root.  The btree cursor's bc_ops will be overridden as needed to make the
 * staging functionality work.  If new_ops is not शून्य, these new ops will be
 * passed out to the caller क्रम further overriding.
 */
व्योम
xfs_btree_stage_अगरakeroot(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xbtree_अगरakeroot		*अगरake,
	काष्ठा xfs_btree_ops		**new_ops)
अणु
	काष्ठा xfs_btree_ops		*nops;

	ASSERT(!(cur->bc_flags & XFS_BTREE_STAGING));
	ASSERT(cur->bc_flags & XFS_BTREE_ROOT_IN_INODE);
	ASSERT(cur->bc_tp == शून्य);

	nops = kmem_alloc(माप(काष्ठा xfs_btree_ops), KM_NOFS);
	स_नकल(nops, cur->bc_ops, माप(काष्ठा xfs_btree_ops));
	nops->alloc_block = xfs_btree_fakeroot_alloc_block;
	nops->मुक्त_block = xfs_btree_fakeroot_मुक्त_block;
	nops->init_ptr_from_cur = xfs_btree_fakeroot_init_ptr_from_cur;
	nops->dup_cursor = xfs_btree_fakeroot_dup_cursor;

	cur->bc_ino.अगरake = अगरake;
	cur->bc_nlevels = अगरake->अगर_levels;
	cur->bc_ops = nops;
	cur->bc_flags |= XFS_BTREE_STAGING;

	अगर (new_ops)
		*new_ops = nops;
पूर्ण

/*
 * Transक्रमm an inode-rooted staging btree cursor back पूर्णांकo a regular cursor by
 * substituting a real btree root क्रम the fake one and restoring normal btree
 * cursor ops.  The caller must log the btree root change prior to calling
 * this.
 */
व्योम
xfs_btree_commit_अगरakeroot(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_trans		*tp,
	पूर्णांक				whichविभाजन,
	स्थिर काष्ठा xfs_btree_ops	*ops)
अणु
	ASSERT(cur->bc_flags & XFS_BTREE_STAGING);
	ASSERT(cur->bc_tp == शून्य);

	trace_xfs_btree_commit_अगरakeroot(cur);

	kmem_मुक्त((व्योम *)cur->bc_ops);
	cur->bc_ino.अगरake = शून्य;
	cur->bc_ino.whichविभाजन = whichविभाजन;
	cur->bc_ops = ops;
	cur->bc_flags &= ~XFS_BTREE_STAGING;
	cur->bc_tp = tp;
पूर्ण

/*
 * Bulk Loading of Staged Btrees
 * =============================
 *
 * This पूर्णांकerface is used with a staged btree cursor to create a totally new
 * btree with a large number of records (i.e. more than what would fit in a
 * single root block).  When the creation is complete, the new root can be
 * linked atomically पूर्णांकo the fileप्रणाली by committing the staged cursor.
 *
 * Creation of a new btree proceeds roughly as follows:
 *
 * The first step is to initialize an appropriate fake btree root काष्ठाure and
 * then स्थिरruct a staged btree cursor.  Refer to the block comments about
 * "Bulk Loading for AG Btrees" and "Bulk Loading for Inode-Rooted Btrees" क्रम
 * more inक्रमmation about how to करो this.
 *
 * The second step is to initialize a काष्ठा xfs_btree_bload context as
 * करोcumented in the काष्ठाure definition.
 *
 * The third step is to call xfs_btree_bload_compute_geometry to compute the
 * height of and the number of blocks needed to स्थिरruct the btree.  See the
 * section "Computing the Geometry of the New Btree" क्रम details about this
 * computation.
 *
 * In step four, the caller must allocate xfs_btree_bload.nr_blocks blocks and
 * save them क्रम later use by ->claim_block().  Bulk loading requires all
 * blocks to be allocated beक्रमehand to aव्योम ENOSPC failures midway through a
 * rebuild, and to minimize seek distances of the new btree.
 *
 * Step five is to call xfs_btree_bload() to start स्थिरructing the btree.
 *
 * The final step is to commit the staging btree cursor, which logs the new
 * btree root and turns the staging cursor पूर्णांकo a regular cursor.  The caller
 * is responsible क्रम cleaning up the previous btree blocks, अगर any.
 *
 * Computing the Geometry of the New Btree
 * =======================================
 *
 * The number of items placed in each btree block is computed via the following
 * algorithm: For leaf levels, the number of items क्रम the level is nr_records
 * in the bload काष्ठाure.  For node levels, the number of items क्रम the level
 * is the number of blocks in the next lower level of the tree.  For each
 * level, the desired number of items per block is defined as:
 *
 * desired = max(minrecs, maxrecs - slack factor)
 *
 * The number of blocks क्रम the level is defined to be:
 *
 * blocks = न्यूनमान(nr_items / desired)
 *
 * Note this is rounded करोwn so that the npb calculation below will never fall
 * below minrecs.  The number of items that will actually be loaded पूर्णांकo each
 * btree block is defined as:
 *
 * npb =  nr_items / blocks
 *
 * Some of the lefपंचांगost blocks in the level will contain one extra record as
 * needed to handle uneven भागision.  If the number of records in any block
 * would exceed maxrecs क्रम that level, blocks is incremented and npb is
 * recalculated.
 *
 * In other words, we compute the number of blocks needed to satisfy a given
 * loading level, then spपढ़ो the items as evenly as possible.
 *
 * The height and number of fs blocks required to create the btree are computed
 * and वापसed via btree_height and nr_blocks.
 */

/*
 * Put a btree block that we're loading onto the ordered list and release it.
 * The btree blocks will be written to disk when bulk loading is finished.
 */
अटल व्योम
xfs_btree_bload_drop_buf(
	काष्ठा list_head	*buffers_list,
	काष्ठा xfs_buf		**bpp)
अणु
	अगर (*bpp == शून्य)
		वापस;

	अगर (!xfs_buf_delwri_queue(*bpp, buffers_list))
		ASSERT(0);

	xfs_buf_rअन्यथा(*bpp);
	*bpp = शून्य;
पूर्ण

/*
 * Allocate and initialize one btree block क्रम bulk loading.
 *
 * The new btree block will have its level and numrecs fields set to the values
 * of the level and nr_this_block parameters, respectively.
 *
 * The caller should ensure that ptrp, bpp, and blockp refer to the left
 * sibling of the new block, अगर there is any.  On निकास, ptrp, bpp, and blockp
 * will all poपूर्णांक to the new block.
 */
STATIC पूर्णांक
xfs_btree_bload_prep_block(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_btree_bload		*bbl,
	काष्ठा list_head		*buffers_list,
	अचिन्हित पूर्णांक			level,
	अचिन्हित पूर्णांक			nr_this_block,
	जोड़ xfs_btree_ptr		*ptrp, /* in/out */
	काष्ठा xfs_buf			**bpp, /* in/out */
	काष्ठा xfs_btree_block		**blockp, /* in/out */
	व्योम				*priv)
अणु
	जोड़ xfs_btree_ptr		new_ptr;
	काष्ठा xfs_buf			*new_bp;
	काष्ठा xfs_btree_block		*new_block;
	पूर्णांक				ret;

	अगर ((cur->bc_flags & XFS_BTREE_ROOT_IN_INODE) &&
	    level == cur->bc_nlevels - 1) अणु
		काष्ठा xfs_अगरork	*अगरp = xfs_btree_अगरork_ptr(cur);
		माप_प्रकार			new_size;

		ASSERT(*bpp == शून्य);

		/* Allocate a new incore btree root block. */
		new_size = bbl->iroot_size(cur, nr_this_block, priv);
		अगरp->अगर_broot = kmem_zalloc(new_size, 0);
		अगरp->अगर_broot_bytes = (पूर्णांक)new_size;

		/* Initialize it and send it out. */
		xfs_btree_init_block_पूर्णांक(cur->bc_mp, अगरp->अगर_broot,
				XFS_BUF_DADDR_शून्य, cur->bc_btnum, level,
				nr_this_block, cur->bc_ino.ip->i_ino,
				cur->bc_flags);

		*bpp = शून्य;
		*blockp = अगरp->अगर_broot;
		xfs_btree_set_ptr_null(cur, ptrp);
		वापस 0;
	पूर्ण

	/* Claim one of the caller's pपुनः_स्मृतिated blocks. */
	xfs_btree_set_ptr_null(cur, &new_ptr);
	ret = bbl->claim_block(cur, &new_ptr, priv);
	अगर (ret)
		वापस ret;

	ASSERT(!xfs_btree_ptr_is_null(cur, &new_ptr));

	ret = xfs_btree_get_buf_block(cur, &new_ptr, &new_block, &new_bp);
	अगर (ret)
		वापस ret;

	/*
	 * The previous block (अगर any) is the left sibling of the new block,
	 * so set its right sibling poपूर्णांकer to the new block and drop it.
	 */
	अगर (*blockp)
		xfs_btree_set_sibling(cur, *blockp, &new_ptr, XFS_BB_RIGHTSIB);
	xfs_btree_bload_drop_buf(buffers_list, bpp);

	/* Initialize the new btree block. */
	xfs_btree_init_block_cur(cur, new_bp, level, nr_this_block);
	xfs_btree_set_sibling(cur, new_block, ptrp, XFS_BB_LEFTSIB);

	/* Set the out parameters. */
	*bpp = new_bp;
	*blockp = new_block;
	xfs_btree_copy_ptrs(cur, ptrp, &new_ptr, 1);
	वापस 0;
पूर्ण

/* Load one leaf block. */
STATIC पूर्णांक
xfs_btree_bload_leaf(
	काष्ठा xfs_btree_cur		*cur,
	अचिन्हित पूर्णांक			recs_this_block,
	xfs_btree_bload_get_record_fn	get_record,
	काष्ठा xfs_btree_block		*block,
	व्योम				*priv)
अणु
	अचिन्हित पूर्णांक			j;
	पूर्णांक				ret;

	/* Fill the leaf block with records. */
	क्रम (j = 1; j <= recs_this_block; j++) अणु
		जोड़ xfs_btree_rec	*block_rec;

		ret = get_record(cur, priv);
		अगर (ret)
			वापस ret;
		block_rec = xfs_btree_rec_addr(cur, j, block);
		cur->bc_ops->init_rec_from_cur(cur, block_rec);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Load one node block with key/ptr pairs.
 *
 * child_ptr must poपूर्णांक to a block within the next level करोwn in the tree.  A
 * key/ptr entry will be created in the new node block to the block poपूर्णांकed to
 * by child_ptr.  On निकास, child_ptr poपूर्णांकs to the next block on the child
 * level that needs processing.
 */
STATIC पूर्णांक
xfs_btree_bload_node(
	काष्ठा xfs_btree_cur	*cur,
	अचिन्हित पूर्णांक		recs_this_block,
	जोड़ xfs_btree_ptr	*child_ptr,
	काष्ठा xfs_btree_block	*block)
अणु
	अचिन्हित पूर्णांक		j;
	पूर्णांक			ret;

	/* Fill the node block with keys and poपूर्णांकers. */
	क्रम (j = 1; j <= recs_this_block; j++) अणु
		जोड़ xfs_btree_key	child_key;
		जोड़ xfs_btree_ptr	*block_ptr;
		जोड़ xfs_btree_key	*block_key;
		काष्ठा xfs_btree_block	*child_block;
		काष्ठा xfs_buf		*child_bp;

		ASSERT(!xfs_btree_ptr_is_null(cur, child_ptr));

		ret = xfs_btree_get_buf_block(cur, child_ptr, &child_block,
				&child_bp);
		अगर (ret)
			वापस ret;

		block_ptr = xfs_btree_ptr_addr(cur, j, block);
		xfs_btree_copy_ptrs(cur, block_ptr, child_ptr, 1);

		block_key = xfs_btree_key_addr(cur, j, block);
		xfs_btree_get_keys(cur, child_block, &child_key);
		xfs_btree_copy_keys(cur, block_key, &child_key, 1);

		xfs_btree_get_sibling(cur, child_block, child_ptr,
				XFS_BB_RIGHTSIB);
		xfs_buf_rअन्यथा(child_bp);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Compute the maximum number of records (or keyptrs) per block that we want to
 * install at this level in the btree.  Caller is responsible क्रम having set
 * @cur->bc_ino.विभाजनsize to the desired विभाजन size, अगर appropriate.
 */
STATIC अचिन्हित पूर्णांक
xfs_btree_bload_max_npb(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_btree_bload	*bbl,
	अचिन्हित पूर्णांक		level)
अणु
	अचिन्हित पूर्णांक		ret;

	अगर (level == cur->bc_nlevels - 1 && cur->bc_ops->get_dmaxrecs)
		वापस cur->bc_ops->get_dmaxrecs(cur, level);

	ret = cur->bc_ops->get_maxrecs(cur, level);
	अगर (level == 0)
		ret -= bbl->leaf_slack;
	अन्यथा
		ret -= bbl->node_slack;
	वापस ret;
पूर्ण

/*
 * Compute the desired number of records (or keyptrs) per block that we want to
 * install at this level in the btree, which must be somewhere between minrecs
 * and max_npb.  The caller is मुक्त to install fewer records per block.
 */
STATIC अचिन्हित पूर्णांक
xfs_btree_bload_desired_npb(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_btree_bload	*bbl,
	अचिन्हित पूर्णांक		level)
अणु
	अचिन्हित पूर्णांक		npb = xfs_btree_bload_max_npb(cur, bbl, level);

	/* Root blocks are not subject to minrecs rules. */
	अगर (level == cur->bc_nlevels - 1)
		वापस max(1U, npb);

	वापस max_t(अचिन्हित पूर्णांक, cur->bc_ops->get_minrecs(cur, level), npb);
पूर्ण

/*
 * Compute the number of records to be stored in each block at this level and
 * the number of blocks क्रम this level.  For leaf levels, we must populate an
 * empty root block even अगर there are no records, so we have to have at least
 * one block.
 */
STATIC व्योम
xfs_btree_bload_level_geometry(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_btree_bload	*bbl,
	अचिन्हित पूर्णांक		level,
	uपूर्णांक64_t		nr_this_level,
	अचिन्हित पूर्णांक		*avg_per_block,
	uपूर्णांक64_t		*blocks,
	uपूर्णांक64_t		*blocks_with_extra)
अणु
	uपूर्णांक64_t		npb;
	uपूर्णांक64_t		करोntcare;
	अचिन्हित पूर्णांक		desired_npb;
	अचिन्हित पूर्णांक		maxnr;

	maxnr = cur->bc_ops->get_maxrecs(cur, level);

	/*
	 * Compute the number of blocks we need to fill each block with the
	 * desired number of records/keyptrs per block.  Because desired_npb
	 * could be minrecs, we use regular पूर्णांकeger भागision (which rounds
	 * the block count करोwn) so that in the next step the effective # of
	 * items per block will never be less than desired_npb.
	 */
	desired_npb = xfs_btree_bload_desired_npb(cur, bbl, level);
	*blocks = भाग64_u64_rem(nr_this_level, desired_npb, &करोntcare);
	*blocks = max(1ULL, *blocks);

	/*
	 * Compute the number of records that we will actually put in each
	 * block, assuming that we want to spपढ़ो the records evenly between
	 * the blocks.  Take care that the effective # of items per block (npb)
	 * won't exceed maxrecs even क्रम the blocks that get an extra record,
	 * since desired_npb could be maxrecs, and in the previous step we
	 * rounded the block count करोwn.
	 */
	npb = भाग64_u64_rem(nr_this_level, *blocks, blocks_with_extra);
	अगर (npb > maxnr || (npb == maxnr && *blocks_with_extra > 0)) अणु
		(*blocks)++;
		npb = भाग64_u64_rem(nr_this_level, *blocks, blocks_with_extra);
	पूर्ण

	*avg_per_block = min_t(uपूर्णांक64_t, npb, nr_this_level);

	trace_xfs_btree_bload_level_geometry(cur, level, nr_this_level,
			*avg_per_block, desired_npb, *blocks,
			*blocks_with_extra);
पूर्ण

/*
 * Ensure a slack value is appropriate क्रम the btree.
 *
 * If the slack value is negative, set slack so that we fill the block to
 * halfway between minrecs and maxrecs.  Make sure the slack is never so large
 * that we can underflow minrecs.
 */
अटल व्योम
xfs_btree_bload_ensure_slack(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			*slack,
	पूर्णांक			level)
अणु
	पूर्णांक			maxr;
	पूर्णांक			minr;

	maxr = cur->bc_ops->get_maxrecs(cur, level);
	minr = cur->bc_ops->get_minrecs(cur, level);

	/*
	 * If slack is negative, स्वतःmatically set slack so that we load the
	 * btree block approximately halfway between minrecs and maxrecs.
	 * Generally, this will net us 75% loading.
	 */
	अगर (*slack < 0)
		*slack = maxr - ((maxr + minr) >> 1);

	*slack = min(*slack, maxr - minr);
पूर्ण

/*
 * Prepare a btree cursor क्रम a bulk load operation by computing the geometry
 * fields in bbl.  Caller must ensure that the btree cursor is a staging
 * cursor.  This function can be called multiple बार.
 */
पूर्णांक
xfs_btree_bload_compute_geometry(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_btree_bload	*bbl,
	uपूर्णांक64_t		nr_records)
अणु
	uपूर्णांक64_t		nr_blocks = 0;
	uपूर्णांक64_t		nr_this_level;

	ASSERT(cur->bc_flags & XFS_BTREE_STAGING);

	/*
	 * Make sure that the slack values make sense क्रम traditional leaf and
	 * node blocks.  Inode-rooted btrees will वापस dअगरferent minrecs and
	 * maxrecs values क्रम the root block (bc_nlevels == level - 1).  We're
	 * checking levels 0 and 1 here, so set bc_nlevels such that the btree
	 * code करोesn't पूर्णांकerpret either as the root level.
	 */
	cur->bc_nlevels = XFS_BTREE_MAXLEVELS - 1;
	xfs_btree_bload_ensure_slack(cur, &bbl->leaf_slack, 0);
	xfs_btree_bload_ensure_slack(cur, &bbl->node_slack, 1);

	bbl->nr_records = nr_this_level = nr_records;
	क्रम (cur->bc_nlevels = 1; cur->bc_nlevels < XFS_BTREE_MAXLEVELS;) अणु
		uपूर्णांक64_t	level_blocks;
		uपूर्णांक64_t	करोntcare64;
		अचिन्हित पूर्णांक	level = cur->bc_nlevels - 1;
		अचिन्हित पूर्णांक	avg_per_block;

		xfs_btree_bload_level_geometry(cur, bbl, level, nr_this_level,
				&avg_per_block, &level_blocks, &करोntcare64);

		अगर (cur->bc_flags & XFS_BTREE_ROOT_IN_INODE) अणु
			/*
			 * If all the items we want to store at this level
			 * would fit in the inode root block, then we have our
			 * btree root and are करोne.
			 *
			 * Note that bmap btrees क्रमbid records in the root.
			 */
			अगर (level != 0 && nr_this_level <= avg_per_block) अणु
				nr_blocks++;
				अवरोध;
			पूर्ण

			/*
			 * Otherwise, we have to store all the items क्रम this
			 * level in traditional btree blocks and thereक्रमe need
			 * another level of btree to poपूर्णांक to those blocks.
			 *
			 * We have to re-compute the geometry क्रम each level of
			 * an inode-rooted btree because the geometry dअगरfers
			 * between a btree root in an inode विभाजन and a
			 * traditional btree block.
			 *
			 * This distinction is made in the btree code based on
			 * whether level == bc_nlevels - 1.  Based on the
			 * previous root block size check against the root
			 * block geometry, we know that we aren't yet पढ़ोy to
			 * populate the root.  Increment bc_nevels and
			 * recalculate the geometry क्रम a traditional
			 * block-based btree level.
			 */
			cur->bc_nlevels++;
			xfs_btree_bload_level_geometry(cur, bbl, level,
					nr_this_level, &avg_per_block,
					&level_blocks, &करोntcare64);
		पूर्ण अन्यथा अणु
			/*
			 * If all the items we want to store at this level
			 * would fit in a single root block, we're करोne.
			 */
			अगर (nr_this_level <= avg_per_block) अणु
				nr_blocks++;
				अवरोध;
			पूर्ण

			/* Otherwise, we need another level of btree. */
			cur->bc_nlevels++;
		पूर्ण

		nr_blocks += level_blocks;
		nr_this_level = level_blocks;
	पूर्ण

	अगर (cur->bc_nlevels == XFS_BTREE_MAXLEVELS)
		वापस -EOVERFLOW;

	bbl->btree_height = cur->bc_nlevels;
	अगर (cur->bc_flags & XFS_BTREE_ROOT_IN_INODE)
		bbl->nr_blocks = nr_blocks - 1;
	अन्यथा
		bbl->nr_blocks = nr_blocks;
	वापस 0;
पूर्ण

/* Bulk load a btree given the parameters and geometry established in bbl. */
पूर्णांक
xfs_btree_bload(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_btree_bload		*bbl,
	व्योम				*priv)
अणु
	काष्ठा list_head		buffers_list;
	जोड़ xfs_btree_ptr		child_ptr;
	जोड़ xfs_btree_ptr		ptr;
	काष्ठा xfs_buf			*bp = शून्य;
	काष्ठा xfs_btree_block		*block = शून्य;
	uपूर्णांक64_t			nr_this_level = bbl->nr_records;
	uपूर्णांक64_t			blocks;
	uपूर्णांक64_t			i;
	uपूर्णांक64_t			blocks_with_extra;
	uपूर्णांक64_t			total_blocks = 0;
	अचिन्हित पूर्णांक			avg_per_block;
	अचिन्हित पूर्णांक			level = 0;
	पूर्णांक				ret;

	ASSERT(cur->bc_flags & XFS_BTREE_STAGING);

	INIT_LIST_HEAD(&buffers_list);
	cur->bc_nlevels = bbl->btree_height;
	xfs_btree_set_ptr_null(cur, &child_ptr);
	xfs_btree_set_ptr_null(cur, &ptr);

	xfs_btree_bload_level_geometry(cur, bbl, level, nr_this_level,
			&avg_per_block, &blocks, &blocks_with_extra);

	/* Load each leaf block. */
	क्रम (i = 0; i < blocks; i++) अणु
		अचिन्हित पूर्णांक		nr_this_block = avg_per_block;

		/*
		 * Due to rounding, btree blocks will not be evenly populated
		 * in most हालs.  blocks_with_extra tells us how many blocks
		 * will receive an extra record to distribute the excess across
		 * the current level as evenly as possible.
		 */
		अगर (i < blocks_with_extra)
			nr_this_block++;

		ret = xfs_btree_bload_prep_block(cur, bbl, &buffers_list, level,
				nr_this_block, &ptr, &bp, &block, priv);
		अगर (ret)
			जाओ out;

		trace_xfs_btree_bload_block(cur, level, i, blocks, &ptr,
				nr_this_block);

		ret = xfs_btree_bload_leaf(cur, nr_this_block, bbl->get_record,
				block, priv);
		अगर (ret)
			जाओ out;

		/*
		 * Record the lefपंचांगost leaf poपूर्णांकer so we know where to start
		 * with the first node level.
		 */
		अगर (i == 0)
			xfs_btree_copy_ptrs(cur, &child_ptr, &ptr, 1);
	पूर्ण
	total_blocks += blocks;
	xfs_btree_bload_drop_buf(&buffers_list, &bp);

	/* Populate the पूर्णांकernal btree nodes. */
	क्रम (level = 1; level < cur->bc_nlevels; level++) अणु
		जोड़ xfs_btree_ptr	first_ptr;

		nr_this_level = blocks;
		block = शून्य;
		xfs_btree_set_ptr_null(cur, &ptr);

		xfs_btree_bload_level_geometry(cur, bbl, level, nr_this_level,
				&avg_per_block, &blocks, &blocks_with_extra);

		/* Load each node block. */
		क्रम (i = 0; i < blocks; i++) अणु
			अचिन्हित पूर्णांक	nr_this_block = avg_per_block;

			अगर (i < blocks_with_extra)
				nr_this_block++;

			ret = xfs_btree_bload_prep_block(cur, bbl,
					&buffers_list, level, nr_this_block,
					&ptr, &bp, &block, priv);
			अगर (ret)
				जाओ out;

			trace_xfs_btree_bload_block(cur, level, i, blocks,
					&ptr, nr_this_block);

			ret = xfs_btree_bload_node(cur, nr_this_block,
					&child_ptr, block);
			अगर (ret)
				जाओ out;

			/*
			 * Record the lefपंचांगost node poपूर्णांकer so that we know
			 * where to start the next node level above this one.
			 */
			अगर (i == 0)
				xfs_btree_copy_ptrs(cur, &first_ptr, &ptr, 1);
		पूर्ण
		total_blocks += blocks;
		xfs_btree_bload_drop_buf(&buffers_list, &bp);
		xfs_btree_copy_ptrs(cur, &child_ptr, &first_ptr, 1);
	पूर्ण

	/* Initialize the new root. */
	अगर (cur->bc_flags & XFS_BTREE_ROOT_IN_INODE) अणु
		ASSERT(xfs_btree_ptr_is_null(cur, &ptr));
		cur->bc_ino.अगरake->अगर_levels = cur->bc_nlevels;
		cur->bc_ino.अगरake->अगर_blocks = total_blocks - 1;
	पूर्ण अन्यथा अणु
		cur->bc_ag.afake->af_root = be32_to_cpu(ptr.s);
		cur->bc_ag.afake->af_levels = cur->bc_nlevels;
		cur->bc_ag.afake->af_blocks = total_blocks;
	पूर्ण

	/*
	 * Write the new blocks to disk.  If the ordered list isn't empty after
	 * that, then something went wrong and we have to fail.  This should
	 * never happen, but we'll check anyway.
	 */
	ret = xfs_buf_delwri_submit(&buffers_list);
	अगर (ret)
		जाओ out;
	अगर (!list_empty(&buffers_list)) अणु
		ASSERT(list_empty(&buffers_list));
		ret = -EIO;
	पूर्ण

out:
	xfs_buf_delwri_cancel(&buffers_list);
	अगर (bp)
		xfs_buf_rअन्यथा(bp);
	वापस ret;
पूर्ण
