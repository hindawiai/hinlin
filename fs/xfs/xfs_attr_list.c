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
#समावेश "xfs_da_format.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_attr.h"
#समावेश "xfs_attr_sf.h"
#समावेश "xfs_attr_leaf.h"
#समावेश "xfs_error.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_dir2.h"

STATIC पूर्णांक
xfs_attr_लघुक्रमm_compare(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	xfs_attr_sf_sort_t *sa, *sb;

	sa = (xfs_attr_sf_sort_t *)a;
	sb = (xfs_attr_sf_sort_t *)b;
	अगर (sa->hash < sb->hash) अणु
		वापस -1;
	पूर्ण अन्यथा अगर (sa->hash > sb->hash) अणु
		वापस 1;
	पूर्ण अन्यथा अणु
		वापस sa->entno - sb->entno;
	पूर्ण
पूर्ण

#घोषणा XFS_ISRESET_CURSOR(cursor) \
	(!((cursor)->initted) && !((cursor)->hashval) && \
	 !((cursor)->blkno) && !((cursor)->offset))
/*
 * Copy out entries of लघुक्रमm attribute lists क्रम attr_list().
 * Shortक्रमm attribute lists are not stored in hashval sorted order.
 * If the output buffer is not large enough to hold them all, then
 * we have to calculate each entries' hashvalue and sort them beक्रमe
 * we can begin वापसing them to the user.
 */
अटल पूर्णांक
xfs_attr_लघुक्रमm_list(
	काष्ठा xfs_attr_list_context	*context)
अणु
	काष्ठा xfs_attrlist_cursor_kern	*cursor = &context->cursor;
	काष्ठा xfs_inode		*dp = context->dp;
	काष्ठा xfs_attr_sf_sort		*sbuf, *sbp;
	काष्ठा xfs_attr_लघुक्रमm	*sf;
	काष्ठा xfs_attr_sf_entry	*sfe;
	पूर्णांक				sbsize, nsbuf, count, i;
	पूर्णांक				error = 0;

	ASSERT(dp->i_afp != शून्य);
	sf = (काष्ठा xfs_attr_लघुक्रमm *)dp->i_afp->अगर_u1.अगर_data;
	ASSERT(sf != शून्य);
	अगर (!sf->hdr.count)
		वापस 0;

	trace_xfs_attr_list_sf(context);

	/*
	 * If the buffer is large enough and the cursor is at the start,
	 * करो not bother with sorting since we will वापस everything in
	 * one buffer and another call using the cursor won't need to be
	 * made.
	 * Note the generous fudge factor of 16 overhead bytes per entry.
	 * If bufsize is zero then put_listent must be a search function
	 * and can just scan through what we have.
	 */
	अगर (context->bufsize == 0 ||
	    (XFS_ISRESET_CURSOR(cursor) &&
	     (dp->i_afp->अगर_bytes + sf->hdr.count * 16) < context->bufsize)) अणु
		क्रम (i = 0, sfe = &sf->list[0]; i < sf->hdr.count; i++) अणु
			अगर (XFS_IS_CORRUPT(context->dp->i_mount,
					   !xfs_attr_namecheck(sfe->nameval,
							       sfe->namelen)))
				वापस -EFSCORRUPTED;
			context->put_listent(context,
					     sfe->flags,
					     sfe->nameval,
					     (पूर्णांक)sfe->namelen,
					     (पूर्णांक)sfe->valuelen);
			/*
			 * Either search callback finished early or
			 * didn't fit it all in the buffer after all.
			 */
			अगर (context->seen_enough)
				अवरोध;
			sfe = xfs_attr_sf_nextentry(sfe);
		पूर्ण
		trace_xfs_attr_list_sf_all(context);
		वापस 0;
	पूर्ण

	/* करो no more क्रम a search callback */
	अगर (context->bufsize == 0)
		वापस 0;

	/*
	 * It didn't all fit, so we have to sort everything on hashval.
	 */
	sbsize = sf->hdr.count * माप(*sbuf);
	sbp = sbuf = kmem_alloc(sbsize, KM_NOFS);

	/*
	 * Scan the attribute list क्रम the rest of the entries, storing
	 * the relevant info from only those that match पूर्णांकo a buffer.
	 */
	nsbuf = 0;
	क्रम (i = 0, sfe = &sf->list[0]; i < sf->hdr.count; i++) अणु
		अगर (unlikely(
		    ((अक्षर *)sfe < (अक्षर *)sf) ||
		    ((अक्षर *)sfe >= ((अक्षर *)sf + dp->i_afp->अगर_bytes)))) अणु
			XFS_CORRUPTION_ERROR("xfs_attr_shortform_list",
					     XFS_ERRLEVEL_LOW,
					     context->dp->i_mount, sfe,
					     माप(*sfe));
			kmem_मुक्त(sbuf);
			वापस -EFSCORRUPTED;
		पूर्ण

		sbp->entno = i;
		sbp->hash = xfs_da_hashname(sfe->nameval, sfe->namelen);
		sbp->name = sfe->nameval;
		sbp->namelen = sfe->namelen;
		/* These are bytes, and both on-disk, करोn't endian-flip */
		sbp->valuelen = sfe->valuelen;
		sbp->flags = sfe->flags;
		sfe = xfs_attr_sf_nextentry(sfe);
		sbp++;
		nsbuf++;
	पूर्ण

	/*
	 * Sort the entries on hash then entno.
	 */
	xfs_sort(sbuf, nsbuf, माप(*sbuf), xfs_attr_लघुक्रमm_compare);

	/*
	 * Re-find our place IN THE SORTED LIST.
	 */
	count = 0;
	cursor->initted = 1;
	cursor->blkno = 0;
	क्रम (sbp = sbuf, i = 0; i < nsbuf; i++, sbp++) अणु
		अगर (sbp->hash == cursor->hashval) अणु
			अगर (cursor->offset == count) अणु
				अवरोध;
			पूर्ण
			count++;
		पूर्ण अन्यथा अगर (sbp->hash > cursor->hashval) अणु
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == nsbuf)
		जाओ out;

	/*
	 * Loop putting entries पूर्णांकo the user buffer.
	 */
	क्रम ( ; i < nsbuf; i++, sbp++) अणु
		अगर (cursor->hashval != sbp->hash) अणु
			cursor->hashval = sbp->hash;
			cursor->offset = 0;
		पूर्ण
		अगर (XFS_IS_CORRUPT(context->dp->i_mount,
				   !xfs_attr_namecheck(sbp->name,
						       sbp->namelen))) अणु
			error = -EFSCORRUPTED;
			जाओ out;
		पूर्ण
		context->put_listent(context,
				     sbp->flags,
				     sbp->name,
				     sbp->namelen,
				     sbp->valuelen);
		अगर (context->seen_enough)
			अवरोध;
		cursor->offset++;
	पूर्ण
out:
	kmem_मुक्त(sbuf);
	वापस error;
पूर्ण

/*
 * We didn't find the block & hash mentioned in the cursor state, so
 * walk करोwn the attr btree looking क्रम the hash.
 */
STATIC पूर्णांक
xfs_attr_node_list_lookup(
	काष्ठा xfs_attr_list_context	*context,
	काष्ठा xfs_attrlist_cursor_kern	*cursor,
	काष्ठा xfs_buf			**pbp)
अणु
	काष्ठा xfs_da3_icnode_hdr	nodehdr;
	काष्ठा xfs_da_पूर्णांकnode		*node;
	काष्ठा xfs_da_node_entry	*btree;
	काष्ठा xfs_inode		*dp = context->dp;
	काष्ठा xfs_mount		*mp = dp->i_mount;
	काष्ठा xfs_trans		*tp = context->tp;
	काष्ठा xfs_buf			*bp;
	पूर्णांक				i;
	पूर्णांक				error = 0;
	अचिन्हित पूर्णांक			expected_level = 0;
	uपूर्णांक16_t			magic;

	ASSERT(*pbp == शून्य);
	cursor->blkno = 0;
	क्रम (;;) अणु
		error = xfs_da3_node_पढ़ो(tp, dp, cursor->blkno, &bp,
				XFS_ATTR_FORK);
		अगर (error)
			वापस error;
		node = bp->b_addr;
		magic = be16_to_cpu(node->hdr.info.magic);
		अगर (magic == XFS_ATTR_LEAF_MAGIC ||
		    magic == XFS_ATTR3_LEAF_MAGIC)
			अवरोध;
		अगर (magic != XFS_DA_NODE_MAGIC &&
		    magic != XFS_DA3_NODE_MAGIC) अणु
			XFS_CORRUPTION_ERROR(__func__, XFS_ERRLEVEL_LOW, mp,
					node, माप(*node));
			जाओ out_corruptbuf;
		पूर्ण

		xfs_da3_node_hdr_from_disk(mp, &nodehdr, node);

		/* Tree taller than we can handle; bail out! */
		अगर (nodehdr.level >= XFS_DA_NODE_MAXDEPTH)
			जाओ out_corruptbuf;

		/* Check the level from the root node. */
		अगर (cursor->blkno == 0)
			expected_level = nodehdr.level - 1;
		अन्यथा अगर (expected_level != nodehdr.level)
			जाओ out_corruptbuf;
		अन्यथा
			expected_level--;

		btree = nodehdr.btree;
		क्रम (i = 0; i < nodehdr.count; btree++, i++) अणु
			अगर (cursor->hashval <= be32_to_cpu(btree->hashval)) अणु
				cursor->blkno = be32_to_cpu(btree->beक्रमe);
				trace_xfs_attr_list_node_descend(context,
						btree);
				अवरोध;
			पूर्ण
		पूर्ण
		xfs_trans_brअन्यथा(tp, bp);

		अगर (i == nodehdr.count)
			वापस 0;

		/* We can't poपूर्णांक back to the root. */
		अगर (XFS_IS_CORRUPT(mp, cursor->blkno == 0))
			वापस -EFSCORRUPTED;
	पूर्ण

	अगर (expected_level != 0)
		जाओ out_corruptbuf;

	*pbp = bp;
	वापस 0;

out_corruptbuf:
	xfs_buf_mark_corrupt(bp);
	xfs_trans_brअन्यथा(tp, bp);
	वापस -EFSCORRUPTED;
पूर्ण

STATIC पूर्णांक
xfs_attr_node_list(
	काष्ठा xfs_attr_list_context	*context)
अणु
	काष्ठा xfs_attrlist_cursor_kern	*cursor = &context->cursor;
	काष्ठा xfs_attr3_icleaf_hdr	leafhdr;
	काष्ठा xfs_attr_leafblock	*leaf;
	काष्ठा xfs_da_पूर्णांकnode		*node;
	काष्ठा xfs_buf			*bp;
	काष्ठा xfs_inode		*dp = context->dp;
	काष्ठा xfs_mount		*mp = dp->i_mount;
	पूर्णांक				error = 0;

	trace_xfs_attr_node_list(context);

	cursor->initted = 1;

	/*
	 * Do all sorts of validation on the passed-in cursor काष्ठाure.
	 * If anything is amiss, ignore the cursor and look up the hashval
	 * starting from the btree root.
	 */
	bp = शून्य;
	अगर (cursor->blkno > 0) अणु
		error = xfs_da3_node_पढ़ो(context->tp, dp, cursor->blkno, &bp,
				XFS_ATTR_FORK);
		अगर ((error != 0) && (error != -EFSCORRUPTED))
			वापस error;
		अगर (bp) अणु
			काष्ठा xfs_attr_leaf_entry *entries;

			node = bp->b_addr;
			चयन (be16_to_cpu(node->hdr.info.magic)) अणु
			हाल XFS_DA_NODE_MAGIC:
			हाल XFS_DA3_NODE_MAGIC:
				trace_xfs_attr_list_wrong_blk(context);
				xfs_trans_brअन्यथा(context->tp, bp);
				bp = शून्य;
				अवरोध;
			हाल XFS_ATTR_LEAF_MAGIC:
			हाल XFS_ATTR3_LEAF_MAGIC:
				leaf = bp->b_addr;
				xfs_attr3_leaf_hdr_from_disk(mp->m_attr_geo,
							     &leafhdr, leaf);
				entries = xfs_attr3_leaf_entryp(leaf);
				अगर (cursor->hashval > be32_to_cpu(
						entries[leafhdr.count - 1].hashval)) अणु
					trace_xfs_attr_list_wrong_blk(context);
					xfs_trans_brअन्यथा(context->tp, bp);
					bp = शून्य;
				पूर्ण अन्यथा अगर (cursor->hashval <= be32_to_cpu(
						entries[0].hashval)) अणु
					trace_xfs_attr_list_wrong_blk(context);
					xfs_trans_brअन्यथा(context->tp, bp);
					bp = शून्य;
				पूर्ण
				अवरोध;
			शेष:
				trace_xfs_attr_list_wrong_blk(context);
				xfs_trans_brअन्यथा(context->tp, bp);
				bp = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * We did not find what we expected given the cursor's contents,
	 * so we start from the top and work करोwn based on the hash value.
	 * Note that start of node block is same as start of leaf block.
	 */
	अगर (bp == शून्य) अणु
		error = xfs_attr_node_list_lookup(context, cursor, &bp);
		अगर (error || !bp)
			वापस error;
	पूर्ण
	ASSERT(bp != शून्य);

	/*
	 * Roll upward through the blocks, processing each leaf block in
	 * order.  As दीर्घ as there is space in the result buffer, keep
	 * adding the inक्रमmation.
	 */
	क्रम (;;) अणु
		leaf = bp->b_addr;
		error = xfs_attr3_leaf_list_पूर्णांक(bp, context);
		अगर (error)
			अवरोध;
		xfs_attr3_leaf_hdr_from_disk(mp->m_attr_geo, &leafhdr, leaf);
		अगर (context->seen_enough || leafhdr.क्रमw == 0)
			अवरोध;
		cursor->blkno = leafhdr.क्रमw;
		xfs_trans_brअन्यथा(context->tp, bp);
		error = xfs_attr3_leaf_पढ़ो(context->tp, dp, cursor->blkno,
					    &bp);
		अगर (error)
			वापस error;
	पूर्ण
	xfs_trans_brअन्यथा(context->tp, bp);
	वापस error;
पूर्ण

/*
 * Copy out attribute list entries क्रम attr_list(), क्रम leaf attribute lists.
 */
पूर्णांक
xfs_attr3_leaf_list_पूर्णांक(
	काष्ठा xfs_buf			*bp,
	काष्ठा xfs_attr_list_context	*context)
अणु
	काष्ठा xfs_attrlist_cursor_kern	*cursor = &context->cursor;
	काष्ठा xfs_attr_leafblock	*leaf;
	काष्ठा xfs_attr3_icleaf_hdr	ichdr;
	काष्ठा xfs_attr_leaf_entry	*entries;
	काष्ठा xfs_attr_leaf_entry	*entry;
	पूर्णांक				i;
	काष्ठा xfs_mount		*mp = context->dp->i_mount;

	trace_xfs_attr_list_leaf(context);

	leaf = bp->b_addr;
	xfs_attr3_leaf_hdr_from_disk(mp->m_attr_geo, &ichdr, leaf);
	entries = xfs_attr3_leaf_entryp(leaf);

	cursor->initted = 1;

	/*
	 * Re-find our place in the leaf block अगर this is a new syscall.
	 */
	अगर (context->resynch) अणु
		entry = &entries[0];
		क्रम (i = 0; i < ichdr.count; entry++, i++) अणु
			अगर (be32_to_cpu(entry->hashval) == cursor->hashval) अणु
				अगर (cursor->offset == context->dupcnt) अणु
					context->dupcnt = 0;
					अवरोध;
				पूर्ण
				context->dupcnt++;
			पूर्ण अन्यथा अगर (be32_to_cpu(entry->hashval) >
					cursor->hashval) अणु
				context->dupcnt = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == ichdr.count) अणु
			trace_xfs_attr_list_notfound(context);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		entry = &entries[0];
		i = 0;
	पूर्ण
	context->resynch = 0;

	/*
	 * We have found our place, start copying out the new attributes.
	 */
	क्रम (; i < ichdr.count; entry++, i++) अणु
		अक्षर *name;
		पूर्णांक namelen, valuelen;

		अगर (be32_to_cpu(entry->hashval) != cursor->hashval) अणु
			cursor->hashval = be32_to_cpu(entry->hashval);
			cursor->offset = 0;
		पूर्ण

		अगर ((entry->flags & XFS_ATTR_INCOMPLETE) &&
		    !context->allow_incomplete)
			जारी;

		अगर (entry->flags & XFS_ATTR_LOCAL) अणु
			xfs_attr_leaf_name_local_t *name_loc;

			name_loc = xfs_attr3_leaf_name_local(leaf, i);
			name = name_loc->nameval;
			namelen = name_loc->namelen;
			valuelen = be16_to_cpu(name_loc->valuelen);
		पूर्ण अन्यथा अणु
			xfs_attr_leaf_name_remote_t *name_rmt;

			name_rmt = xfs_attr3_leaf_name_remote(leaf, i);
			name = name_rmt->name;
			namelen = name_rmt->namelen;
			valuelen = be32_to_cpu(name_rmt->valuelen);
		पूर्ण

		अगर (XFS_IS_CORRUPT(context->dp->i_mount,
				   !xfs_attr_namecheck(name, namelen)))
			वापस -EFSCORRUPTED;
		context->put_listent(context, entry->flags,
					      name, namelen, valuelen);
		अगर (context->seen_enough)
			अवरोध;
		cursor->offset++;
	पूर्ण
	trace_xfs_attr_list_leaf_end(context);
	वापस 0;
पूर्ण

/*
 * Copy out attribute entries क्रम attr_list(), क्रम leaf attribute lists.
 */
STATIC पूर्णांक
xfs_attr_leaf_list(
	काष्ठा xfs_attr_list_context	*context)
अणु
	काष्ठा xfs_buf			*bp;
	पूर्णांक				error;

	trace_xfs_attr_leaf_list(context);

	context->cursor.blkno = 0;
	error = xfs_attr3_leaf_पढ़ो(context->tp, context->dp, 0, &bp);
	अगर (error)
		वापस error;

	error = xfs_attr3_leaf_list_पूर्णांक(bp, context);
	xfs_trans_brअन्यथा(context->tp, bp);
	वापस error;
पूर्ण

पूर्णांक
xfs_attr_list_ilocked(
	काष्ठा xfs_attr_list_context	*context)
अणु
	काष्ठा xfs_inode		*dp = context->dp;

	ASSERT(xfs_isilocked(dp, XFS_ILOCK_SHARED | XFS_ILOCK_EXCL));

	/*
	 * Decide on what work routines to call based on the inode size.
	 */
	अगर (!xfs_inode_hasattr(dp))
		वापस 0;
	अगर (dp->i_afp->अगर_क्रमmat == XFS_DINODE_FMT_LOCAL)
		वापस xfs_attr_लघुक्रमm_list(context);
	अगर (xfs_attr_is_leaf(dp))
		वापस xfs_attr_leaf_list(context);
	वापस xfs_attr_node_list(context);
पूर्ण

पूर्णांक
xfs_attr_list(
	काष्ठा xfs_attr_list_context	*context)
अणु
	काष्ठा xfs_inode		*dp = context->dp;
	uपूर्णांक				lock_mode;
	पूर्णांक				error;

	XFS_STATS_INC(dp->i_mount, xs_attr_list);

	अगर (XFS_FORCED_SHUTDOWN(dp->i_mount))
		वापस -EIO;

	lock_mode = xfs_ilock_attr_map_shared(dp);
	error = xfs_attr_list_ilocked(context);
	xfs_iunlock(dp, lock_mode);
	वापस error;
पूर्ण
