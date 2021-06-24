<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_dir2.h"
#समावेश "xfs_dir2_priv.h"
#समावेश "xfs_attr_leaf.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/common.h"
#समावेश "scrub/trace.h"
#समावेश "scrub/dabtree.h"

/* Directory/Attribute Btree */

/*
 * Check क्रम da btree operation errors.  See the section about handling
 * operational errors in common.c.
 */
bool
xchk_da_process_error(
	काष्ठा xchk_da_btree	*ds,
	पूर्णांक			level,
	पूर्णांक			*error)
अणु
	काष्ठा xfs_scrub	*sc = ds->sc;

	अगर (*error == 0)
		वापस true;

	चयन (*error) अणु
	हाल -EDEADLOCK:
		/* Used to restart an op with deadlock aव्योमance. */
		trace_xchk_deadlock_retry(sc->ip, sc->sm, *error);
		अवरोध;
	हाल -EFSBADCRC:
	हाल -EFSCORRUPTED:
		/* Note the badness but करोn't पात. */
		sc->sm->sm_flags |= XFS_SCRUB_OFLAG_CORRUPT;
		*error = 0;
		/* fall through */
	शेष:
		trace_xchk_file_op_error(sc, ds->dargs.whichविभाजन,
				xfs_dir2_da_to_db(ds->dargs.geo,
					ds->state->path.blk[level].blkno),
				*error, __वापस_address);
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Check क्रम da btree corruption.  See the section about handling
 * operational errors in common.c.
 */
व्योम
xchk_da_set_corrupt(
	काष्ठा xchk_da_btree	*ds,
	पूर्णांक			level)
अणु
	काष्ठा xfs_scrub	*sc = ds->sc;

	sc->sm->sm_flags |= XFS_SCRUB_OFLAG_CORRUPT;

	trace_xchk_fblock_error(sc, ds->dargs.whichविभाजन,
			xfs_dir2_da_to_db(ds->dargs.geo,
				ds->state->path.blk[level].blkno),
			__वापस_address);
पूर्ण

अटल काष्ठा xfs_da_node_entry *
xchk_da_btree_node_entry(
	काष्ठा xchk_da_btree		*ds,
	पूर्णांक				level)
अणु
	काष्ठा xfs_da_state_blk		*blk = &ds->state->path.blk[level];
	काष्ठा xfs_da3_icnode_hdr	hdr;

	ASSERT(blk->magic == XFS_DA_NODE_MAGIC);

	xfs_da3_node_hdr_from_disk(ds->sc->mp, &hdr, blk->bp->b_addr);
	वापस hdr.btree + blk->index;
पूर्ण

/* Scrub a da btree hash (key). */
पूर्णांक
xchk_da_btree_hash(
	काष्ठा xchk_da_btree		*ds,
	पूर्णांक				level,
	__be32				*hashp)
अणु
	काष्ठा xfs_da_node_entry	*entry;
	xfs_dahash_t			hash;
	xfs_dahash_t			parent_hash;

	/* Is this hash in order? */
	hash = be32_to_cpu(*hashp);
	अगर (hash < ds->hashes[level])
		xchk_da_set_corrupt(ds, level);
	ds->hashes[level] = hash;

	अगर (level == 0)
		वापस 0;

	/* Is this hash no larger than the parent hash? */
	entry = xchk_da_btree_node_entry(ds, level - 1);
	parent_hash = be32_to_cpu(entry->hashval);
	अगर (parent_hash < hash)
		xchk_da_set_corrupt(ds, level);

	वापस 0;
पूर्ण

/*
 * Check a da btree poपूर्णांकer.  Returns true अगर it's ok to use this
 * poपूर्णांकer.
 */
STATIC bool
xchk_da_btree_ptr_ok(
	काष्ठा xchk_da_btree	*ds,
	पूर्णांक			level,
	xfs_dablk_t		blkno)
अणु
	अगर (blkno < ds->lowest || (ds->highest != 0 && blkno >= ds->highest)) अणु
		xchk_da_set_corrupt(ds, level);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * The da btree scrubber can handle leaf1 blocks as a degenerate
 * क्रमm of leafn blocks.  Since the regular da code करोesn't handle
 * leaf1, we must multiplex the verअगरiers.
 */
अटल व्योम
xchk_da_btree_पढ़ो_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_da_blkinfo	*info = bp->b_addr;

	चयन (be16_to_cpu(info->magic)) अणु
	हाल XFS_सूची2_LEAF1_MAGIC:
	हाल XFS_सूची3_LEAF1_MAGIC:
		bp->b_ops = &xfs_dir3_leaf1_buf_ops;
		bp->b_ops->verअगरy_पढ़ो(bp);
		वापस;
	शेष:
		/*
		 * xfs_da3_node_buf_ops alपढ़ोy know how to handle
		 * DA*_NODE, ATTR*_LEAF, and सूची*_LEAFN blocks.
		 */
		bp->b_ops = &xfs_da3_node_buf_ops;
		bp->b_ops->verअगरy_पढ़ो(bp);
		वापस;
	पूर्ण
पूर्ण
अटल व्योम
xchk_da_btree_ग_लिखो_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_da_blkinfo	*info = bp->b_addr;

	चयन (be16_to_cpu(info->magic)) अणु
	हाल XFS_सूची2_LEAF1_MAGIC:
	हाल XFS_सूची3_LEAF1_MAGIC:
		bp->b_ops = &xfs_dir3_leaf1_buf_ops;
		bp->b_ops->verअगरy_ग_लिखो(bp);
		वापस;
	शेष:
		/*
		 * xfs_da3_node_buf_ops alपढ़ोy know how to handle
		 * DA*_NODE, ATTR*_LEAF, and सूची*_LEAFN blocks.
		 */
		bp->b_ops = &xfs_da3_node_buf_ops;
		bp->b_ops->verअगरy_ग_लिखो(bp);
		वापस;
	पूर्ण
पूर्ण
अटल व्योम *
xchk_da_btree_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_da_blkinfo	*info = bp->b_addr;

	चयन (be16_to_cpu(info->magic)) अणु
	हाल XFS_सूची2_LEAF1_MAGIC:
	हाल XFS_सूची3_LEAF1_MAGIC:
		bp->b_ops = &xfs_dir3_leaf1_buf_ops;
		वापस bp->b_ops->verअगरy_काष्ठा(bp);
	शेष:
		bp->b_ops = &xfs_da3_node_buf_ops;
		वापस bp->b_ops->verअगरy_काष्ठा(bp);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा xfs_buf_ops xchk_da_btree_buf_ops = अणु
	.name = "xchk_da_btree",
	.verअगरy_पढ़ो = xchk_da_btree_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xchk_da_btree_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा = xchk_da_btree_verअगरy,
पूर्ण;

/* Check a block's sibling. */
STATIC पूर्णांक
xchk_da_btree_block_check_sibling(
	काष्ठा xchk_da_btree	*ds,
	पूर्णांक			level,
	पूर्णांक			direction,
	xfs_dablk_t		sibling)
अणु
	काष्ठा xfs_da_state_path *path = &ds->state->path;
	काष्ठा xfs_da_state_path *altpath = &ds->state->altpath;
	पूर्णांक			retval;
	पूर्णांक			plevel;
	पूर्णांक			error;

	स_नकल(altpath, path, माप(ds->state->altpath));

	/*
	 * If the poपूर्णांकer is null, we shouldn't be able to move the upper
	 * level poपूर्णांकer anywhere.
	 */
	अगर (sibling == 0) अणु
		error = xfs_da3_path_shअगरt(ds->state, altpath, direction,
				false, &retval);
		अगर (error == 0 && retval == 0)
			xchk_da_set_corrupt(ds, level);
		error = 0;
		जाओ out;
	पूर्ण

	/* Move the alternate cursor one block in the direction given. */
	error = xfs_da3_path_shअगरt(ds->state, altpath, direction, false,
			&retval);
	अगर (!xchk_da_process_error(ds, level, &error))
		जाओ out;
	अगर (retval) अणु
		xchk_da_set_corrupt(ds, level);
		जाओ out;
	पूर्ण
	अगर (altpath->blk[level].bp)
		xchk_buffer_recheck(ds->sc, altpath->blk[level].bp);

	/* Compare upper level poपूर्णांकer to sibling poपूर्णांकer. */
	अगर (altpath->blk[level].blkno != sibling)
		xchk_da_set_corrupt(ds, level);

out:
	/* Free all buffers in the altpath that aren't referenced from path. */
	क्रम (plevel = 0; plevel < altpath->active; plevel++) अणु
		अगर (altpath->blk[plevel].bp == शून्य ||
		    (plevel < path->active &&
		     altpath->blk[plevel].bp == path->blk[plevel].bp))
			जारी;

		xfs_trans_brअन्यथा(ds->dargs.trans, altpath->blk[plevel].bp);
		altpath->blk[plevel].bp = शून्य;
	पूर्ण

	वापस error;
पूर्ण

/* Check a block's sibling poपूर्णांकers. */
STATIC पूर्णांक
xchk_da_btree_block_check_siblings(
	काष्ठा xchk_da_btree	*ds,
	पूर्णांक			level,
	काष्ठा xfs_da_blkinfo	*hdr)
अणु
	xfs_dablk_t		क्रमw;
	xfs_dablk_t		back;
	पूर्णांक			error = 0;

	क्रमw = be32_to_cpu(hdr->क्रमw);
	back = be32_to_cpu(hdr->back);

	/* Top level blocks should not have sibling poपूर्णांकers. */
	अगर (level == 0) अणु
		अगर (क्रमw != 0 || back != 0)
			xchk_da_set_corrupt(ds, level);
		वापस 0;
	पूर्ण

	/*
	 * Check back (left) and क्रमw (right) poपूर्णांकers.  These functions
	 * असलorb error codes क्रम us.
	 */
	error = xchk_da_btree_block_check_sibling(ds, level, 0, back);
	अगर (error)
		जाओ out;
	error = xchk_da_btree_block_check_sibling(ds, level, 1, क्रमw);

out:
	स_रखो(&ds->state->altpath, 0, माप(ds->state->altpath));
	वापस error;
पूर्ण

/* Load a dir/attribute block from a btree. */
STATIC पूर्णांक
xchk_da_btree_block(
	काष्ठा xchk_da_btree		*ds,
	पूर्णांक				level,
	xfs_dablk_t			blkno)
अणु
	काष्ठा xfs_da_state_blk		*blk;
	काष्ठा xfs_da_पूर्णांकnode		*node;
	काष्ठा xfs_da_node_entry	*btree;
	काष्ठा xfs_da3_blkinfo		*hdr3;
	काष्ठा xfs_da_args		*dargs = &ds->dargs;
	काष्ठा xfs_inode		*ip = ds->dargs.dp;
	xfs_ino_t			owner;
	पूर्णांक				*pmaxrecs;
	काष्ठा xfs_da3_icnode_hdr	nodehdr;
	पूर्णांक				error = 0;

	blk = &ds->state->path.blk[level];
	ds->state->path.active = level + 1;

	/* Release old block. */
	अगर (blk->bp) अणु
		xfs_trans_brअन्यथा(dargs->trans, blk->bp);
		blk->bp = शून्य;
	पूर्ण

	/* Check the poपूर्णांकer. */
	blk->blkno = blkno;
	अगर (!xchk_da_btree_ptr_ok(ds, level, blkno))
		जाओ out_nobuf;

	/* Read the buffer. */
	error = xfs_da_पढ़ो_buf(dargs->trans, dargs->dp, blk->blkno,
			XFS_DABUF_MAP_HOLE_OK, &blk->bp, dargs->whichविभाजन,
			&xchk_da_btree_buf_ops);
	अगर (!xchk_da_process_error(ds, level, &error))
		जाओ out_nobuf;
	अगर (blk->bp)
		xchk_buffer_recheck(ds->sc, blk->bp);

	/*
	 * We didn't find a dir btree root block, which means that
	 * there's no LEAF1/LEAFN tree (at least not where it's supposed
	 * to be), so jump out now.
	 */
	अगर (ds->dargs.whichविभाजन == XFS_DATA_FORK && level == 0 &&
			blk->bp == शून्य)
		जाओ out_nobuf;

	/* It's /not/ ok क्रम attr trees not to have a da btree. */
	अगर (blk->bp == शून्य) अणु
		xchk_da_set_corrupt(ds, level);
		जाओ out_nobuf;
	पूर्ण

	hdr3 = blk->bp->b_addr;
	blk->magic = be16_to_cpu(hdr3->hdr.magic);
	pmaxrecs = &ds->maxrecs[level];

	/* We only started zeroing the header on v5 fileप्रणालीs. */
	अगर (xfs_sb_version_hascrc(&ds->sc->mp->m_sb) && hdr3->hdr.pad)
		xchk_da_set_corrupt(ds, level);

	/* Check the owner. */
	अगर (xfs_sb_version_hascrc(&ip->i_mount->m_sb)) अणु
		owner = be64_to_cpu(hdr3->owner);
		अगर (owner != ip->i_ino)
			xchk_da_set_corrupt(ds, level);
	पूर्ण

	/* Check the siblings. */
	error = xchk_da_btree_block_check_siblings(ds, level, &hdr3->hdr);
	अगर (error)
		जाओ out;

	/* Interpret the buffer. */
	चयन (blk->magic) अणु
	हाल XFS_ATTR_LEAF_MAGIC:
	हाल XFS_ATTR3_LEAF_MAGIC:
		xfs_trans_buf_set_type(dargs->trans, blk->bp,
				XFS_BLFT_ATTR_LEAF_BUF);
		blk->magic = XFS_ATTR_LEAF_MAGIC;
		blk->hashval = xfs_attr_leaf_lasthash(blk->bp, pmaxrecs);
		अगर (ds->tree_level != 0)
			xchk_da_set_corrupt(ds, level);
		अवरोध;
	हाल XFS_सूची2_LEAFN_MAGIC:
	हाल XFS_सूची3_LEAFN_MAGIC:
		xfs_trans_buf_set_type(dargs->trans, blk->bp,
				XFS_BLFT_सूची_LEAFN_BUF);
		blk->magic = XFS_सूची2_LEAFN_MAGIC;
		blk->hashval = xfs_dir2_leaf_lasthash(ip, blk->bp, pmaxrecs);
		अगर (ds->tree_level != 0)
			xchk_da_set_corrupt(ds, level);
		अवरोध;
	हाल XFS_सूची2_LEAF1_MAGIC:
	हाल XFS_सूची3_LEAF1_MAGIC:
		xfs_trans_buf_set_type(dargs->trans, blk->bp,
				XFS_BLFT_सूची_LEAF1_BUF);
		blk->magic = XFS_सूची2_LEAF1_MAGIC;
		blk->hashval = xfs_dir2_leaf_lasthash(ip, blk->bp, pmaxrecs);
		अगर (ds->tree_level != 0)
			xchk_da_set_corrupt(ds, level);
		अवरोध;
	हाल XFS_DA_NODE_MAGIC:
	हाल XFS_DA3_NODE_MAGIC:
		xfs_trans_buf_set_type(dargs->trans, blk->bp,
				XFS_BLFT_DA_NODE_BUF);
		blk->magic = XFS_DA_NODE_MAGIC;
		node = blk->bp->b_addr;
		xfs_da3_node_hdr_from_disk(ip->i_mount, &nodehdr, node);
		btree = nodehdr.btree;
		*pmaxrecs = nodehdr.count;
		blk->hashval = be32_to_cpu(btree[*pmaxrecs - 1].hashval);
		अगर (level == 0) अणु
			अगर (nodehdr.level >= XFS_DA_NODE_MAXDEPTH) अणु
				xchk_da_set_corrupt(ds, level);
				जाओ out_मुक्तbp;
			पूर्ण
			ds->tree_level = nodehdr.level;
		पूर्ण अन्यथा अणु
			अगर (ds->tree_level != nodehdr.level) अणु
				xchk_da_set_corrupt(ds, level);
				जाओ out_मुक्तbp;
			पूर्ण
		पूर्ण

		/* XXX: Check hdr3.pad32 once we know how to fix it. */
		अवरोध;
	शेष:
		xchk_da_set_corrupt(ds, level);
		जाओ out_मुक्तbp;
	पूर्ण

	/*
	 * If we've been handed a block that is below the dabtree root, करोes
	 * its hashval match what the parent block expected to see?
	 */
	अगर (level > 0) अणु
		काष्ठा xfs_da_node_entry	*key;

		key = xchk_da_btree_node_entry(ds, level - 1);
		अगर (be32_to_cpu(key->hashval) != blk->hashval) अणु
			xchk_da_set_corrupt(ds, level);
			जाओ out_मुक्तbp;
		पूर्ण
	पूर्ण

out:
	वापस error;
out_मुक्तbp:
	xfs_trans_brअन्यथा(dargs->trans, blk->bp);
	blk->bp = शून्य;
out_nobuf:
	blk->blkno = 0;
	वापस error;
पूर्ण

/* Visit all nodes and leaves of a da btree. */
पूर्णांक
xchk_da_btree(
	काष्ठा xfs_scrub		*sc,
	पूर्णांक				whichविभाजन,
	xchk_da_btree_rec_fn		scrub_fn,
	व्योम				*निजी)
अणु
	काष्ठा xchk_da_btree		ds = अणुपूर्ण;
	काष्ठा xfs_mount		*mp = sc->mp;
	काष्ठा xfs_da_state_blk		*blks;
	काष्ठा xfs_da_node_entry	*key;
	xfs_dablk_t			blkno;
	पूर्णांक				level;
	पूर्णांक				error;

	/* Skip लघु क्रमmat data काष्ठाures; no btree to scan. */
	अगर (!xfs_अगरork_has_extents(XFS_IFORK_PTR(sc->ip, whichविभाजन)))
		वापस 0;

	/* Set up initial da state. */
	ds.dargs.dp = sc->ip;
	ds.dargs.whichविभाजन = whichविभाजन;
	ds.dargs.trans = sc->tp;
	ds.dargs.op_flags = XFS_DA_OP_OKNOENT;
	ds.state = xfs_da_state_alloc(&ds.dargs);
	ds.sc = sc;
	ds.निजी = निजी;
	अगर (whichविभाजन == XFS_ATTR_FORK) अणु
		ds.dargs.geo = mp->m_attr_geo;
		ds.lowest = 0;
		ds.highest = 0;
	पूर्ण अन्यथा अणु
		ds.dargs.geo = mp->m_dir_geo;
		ds.lowest = ds.dargs.geo->leafblk;
		ds.highest = ds.dargs.geo->मुक्तblk;
	पूर्ण
	blkno = ds.lowest;
	level = 0;

	/* Find the root of the da tree, अगर present. */
	blks = ds.state->path.blk;
	error = xchk_da_btree_block(&ds, level, blkno);
	अगर (error)
		जाओ out_state;
	/*
	 * We didn't find a block at ds.lowest, which means that there's
	 * no LEAF1/LEAFN tree (at least not where it's supposed to be),
	 * so jump out now.
	 */
	अगर (blks[level].bp == शून्य)
		जाओ out_state;

	blks[level].index = 0;
	जबतक (level >= 0 && level < XFS_DA_NODE_MAXDEPTH) अणु
		/* Handle leaf block. */
		अगर (blks[level].magic != XFS_DA_NODE_MAGIC) अणु
			/* End of leaf, pop back towards the root. */
			अगर (blks[level].index >= ds.maxrecs[level]) अणु
				अगर (level > 0)
					blks[level - 1].index++;
				ds.tree_level++;
				level--;
				जारी;
			पूर्ण

			/* Dispatch record scrubbing. */
			error = scrub_fn(&ds, level);
			अगर (error)
				अवरोध;
			अगर (xchk_should_terminate(sc, &error) ||
			    (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT))
				अवरोध;

			blks[level].index++;
			जारी;
		पूर्ण


		/* End of node, pop back towards the root. */
		अगर (blks[level].index >= ds.maxrecs[level]) अणु
			अगर (level > 0)
				blks[level - 1].index++;
			ds.tree_level++;
			level--;
			जारी;
		पूर्ण

		/* Hashes in order क्रम scrub? */
		key = xchk_da_btree_node_entry(&ds, level);
		error = xchk_da_btree_hash(&ds, level, &key->hashval);
		अगर (error)
			जाओ out;

		/* Drill another level deeper. */
		blkno = be32_to_cpu(key->beक्रमe);
		level++;
		अगर (level >= XFS_DA_NODE_MAXDEPTH) अणु
			/* Too deep! */
			xchk_da_set_corrupt(&ds, level - 1);
			अवरोध;
		पूर्ण
		ds.tree_level--;
		error = xchk_da_btree_block(&ds, level, blkno);
		अगर (error)
			जाओ out;
		अगर (blks[level].bp == शून्य)
			जाओ out;

		blks[level].index = 0;
	पूर्ण

out:
	/* Release all the buffers we're tracking. */
	क्रम (level = 0; level < XFS_DA_NODE_MAXDEPTH; level++) अणु
		अगर (blks[level].bp == शून्य)
			जारी;
		xfs_trans_brअन्यथा(sc->tp, blks[level].bp);
		blks[level].bp = शून्य;
	पूर्ण

out_state:
	xfs_da_state_मुक्त(ds.state);
	वापस error;
पूर्ण
