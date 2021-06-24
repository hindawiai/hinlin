<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_btree.h"
#समावेश "scrub/bitmap.h"

/*
 * Set a range of this biपंचांगap.  Caller must ensure the range is not set.
 *
 * This is the logical equivalent of biपंचांगap |= mask(start, len).
 */
पूर्णांक
xbiपंचांगap_set(
	काष्ठा xbiपंचांगap		*biपंचांगap,
	uपूर्णांक64_t		start,
	uपूर्णांक64_t		len)
अणु
	काष्ठा xbiपंचांगap_range	*bmr;

	bmr = kmem_alloc(माप(काष्ठा xbiपंचांगap_range), KM_MAYFAIL);
	अगर (!bmr)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&bmr->list);
	bmr->start = start;
	bmr->len = len;
	list_add_tail(&bmr->list, &biपंचांगap->list);

	वापस 0;
पूर्ण

/* Free everything related to this biपंचांगap. */
व्योम
xbiपंचांगap_destroy(
	काष्ठा xbiपंचांगap		*biपंचांगap)
अणु
	काष्ठा xbiपंचांगap_range	*bmr;
	काष्ठा xbiपंचांगap_range	*n;

	क्रम_each_xbiपंचांगap_extent(bmr, n, biपंचांगap) अणु
		list_del(&bmr->list);
		kmem_मुक्त(bmr);
	पूर्ण
पूर्ण

/* Set up a per-AG block biपंचांगap. */
व्योम
xbiपंचांगap_init(
	काष्ठा xbiपंचांगap		*biपंचांगap)
अणु
	INIT_LIST_HEAD(&biपंचांगap->list);
पूर्ण

/* Compare two btree extents. */
अटल पूर्णांक
xbiपंचांगap_range_cmp(
	व्योम			*priv,
	स्थिर काष्ठा list_head	*a,
	स्थिर काष्ठा list_head	*b)
अणु
	काष्ठा xbiपंचांगap_range	*ap;
	काष्ठा xbiपंचांगap_range	*bp;

	ap = container_of(a, काष्ठा xbiपंचांगap_range, list);
	bp = container_of(b, काष्ठा xbiपंचांगap_range, list);

	अगर (ap->start > bp->start)
		वापस 1;
	अगर (ap->start < bp->start)
		वापस -1;
	वापस 0;
पूर्ण

/*
 * Remove all the blocks mentioned in @sub from the extents in @biपंचांगap.
 *
 * The पूर्णांकent is that callers will iterate the rmapbt क्रम all of its records
 * क्रम a given owner to generate @biपंचांगap; and iterate all the blocks of the
 * metadata काष्ठाures that are not being rebuilt and have the same rmapbt
 * owner to generate @sub.  This routine subtracts all the extents
 * mentioned in sub from all the extents linked in @biपंचांगap, which leaves
 * @biपंचांगap as the list of blocks that are not accounted क्रम, which we assume
 * are the dead blocks of the old metadata काष्ठाure.  The blocks mentioned in
 * @biपंचांगap can be reaped.
 *
 * This is the logical equivalent of biपंचांगap &= ~sub.
 */
#घोषणा LEFT_ALIGNED	(1 << 0)
#घोषणा RIGHT_ALIGNED	(1 << 1)
पूर्णांक
xbiपंचांगap_disजोड़(
	काष्ठा xbiपंचांगap		*biपंचांगap,
	काष्ठा xbiपंचांगap		*sub)
अणु
	काष्ठा list_head	*lp;
	काष्ठा xbiपंचांगap_range	*br;
	काष्ठा xbiपंचांगap_range	*new_br;
	काष्ठा xbiपंचांगap_range	*sub_br;
	uपूर्णांक64_t		sub_start;
	uपूर्णांक64_t		sub_len;
	पूर्णांक			state;
	पूर्णांक			error = 0;

	अगर (list_empty(&biपंचांगap->list) || list_empty(&sub->list))
		वापस 0;
	ASSERT(!list_empty(&sub->list));

	list_sort(शून्य, &biपंचांगap->list, xbiपंचांगap_range_cmp);
	list_sort(शून्य, &sub->list, xbiपंचांगap_range_cmp);

	/*
	 * Now that we've sorted both lists, we iterate biपंचांगap once, rolling
	 * क्रमward through sub and/or biपंचांगap as necessary until we find an
	 * overlap or reach the end of either list.  We करो not reset lp to the
	 * head of biपंचांगap nor करो we reset sub_br to the head of sub.  The
	 * list traversal is similar to merge sort, but we're deleting
	 * instead.  In this manner we aव्योम O(n^2) operations.
	 */
	sub_br = list_first_entry(&sub->list, काष्ठा xbiपंचांगap_range,
			list);
	lp = biपंचांगap->list.next;
	जबतक (lp != &biपंचांगap->list) अणु
		br = list_entry(lp, काष्ठा xbiपंचांगap_range, list);

		/*
		 * Advance sub_br and/or br until we find a pair that
		 * पूर्णांकersect or we run out of extents.
		 */
		जबतक (sub_br->start + sub_br->len <= br->start) अणु
			अगर (list_is_last(&sub_br->list, &sub->list))
				जाओ out;
			sub_br = list_next_entry(sub_br, list);
		पूर्ण
		अगर (sub_br->start >= br->start + br->len) अणु
			lp = lp->next;
			जारी;
		पूर्ण

		/* trim sub_br to fit the extent we have */
		sub_start = sub_br->start;
		sub_len = sub_br->len;
		अगर (sub_br->start < br->start) अणु
			sub_len -= br->start - sub_br->start;
			sub_start = br->start;
		पूर्ण
		अगर (sub_len > br->len)
			sub_len = br->len;

		state = 0;
		अगर (sub_start == br->start)
			state |= LEFT_ALIGNED;
		अगर (sub_start + sub_len == br->start + br->len)
			state |= RIGHT_ALIGNED;
		चयन (state) अणु
		हाल LEFT_ALIGNED:
			/* Coincides with only the left. */
			br->start += sub_len;
			br->len -= sub_len;
			अवरोध;
		हाल RIGHT_ALIGNED:
			/* Coincides with only the right. */
			br->len -= sub_len;
			lp = lp->next;
			अवरोध;
		हाल LEFT_ALIGNED | RIGHT_ALIGNED:
			/* Total overlap, just delete ex. */
			lp = lp->next;
			list_del(&br->list);
			kmem_मुक्त(br);
			अवरोध;
		हाल 0:
			/*
			 * Deleting from the middle: add the new right extent
			 * and then shrink the left extent.
			 */
			new_br = kmem_alloc(माप(काष्ठा xbiपंचांगap_range),
					KM_MAYFAIL);
			अगर (!new_br) अणु
				error = -ENOMEM;
				जाओ out;
			पूर्ण
			INIT_LIST_HEAD(&new_br->list);
			new_br->start = sub_start + sub_len;
			new_br->len = br->start + br->len - new_br->start;
			list_add(&new_br->list, &br->list);
			br->len = sub_start - br->start;
			lp = lp->next;
			अवरोध;
		शेष:
			ASSERT(0);
			अवरोध;
		पूर्ण
	पूर्ण

out:
	वापस error;
पूर्ण
#अघोषित LEFT_ALIGNED
#अघोषित RIGHT_ALIGNED

/*
 * Record all btree blocks seen जबतक iterating all records of a btree.
 *
 * We know that the btree query_all function starts at the left edge and walks
 * towards the right edge of the tree.  Thereक्रमe, we know that we can walk up
 * the btree cursor towards the root; अगर the poपूर्णांकer क्रम a given level poपूर्णांकs
 * to the first record/key in that block, we haven't seen this block beक्रमe;
 * and thereक्रमe we need to remember that we saw this block in the btree.
 *
 * So अगर our btree is:
 *
 *    4
 *  / | \
 * 1  2  3
 *
 * Pretend क्रम this example that each leaf block has 100 btree records.  For
 * the first btree record, we'll observe that bc_ptrs[0] == 1, so we record
 * that we saw block 1.  Then we observe that bc_ptrs[1] == 1, so we record
 * block 4.  The list is [1, 4].
 *
 * For the second btree record, we see that bc_ptrs[0] == 2, so we निकास the
 * loop.  The list reमुख्यs [1, 4].
 *
 * For the 101st btree record, we've moved onto leaf block 2.  Now
 * bc_ptrs[0] == 1 again, so we record that we saw block 2.  We see that
 * bc_ptrs[1] == 2, so we निकास the loop.  The list is now [1, 4, 2].
 *
 * For the 102nd record, bc_ptrs[0] == 2, so we जारी.
 *
 * For the 201st record, we've moved on to leaf block 3.  bc_ptrs[0] == 1, so
 * we add 3 to the list.  Now it is [1, 4, 2, 3].
 *
 * For the 300th record we just निकास, with the list being [1, 4, 2, 3].
 */

/*
 * Record all the buffers poपूर्णांकed to by the btree cursor.  Callers alपढ़ोy
 * engaged in a btree walk should call this function to capture the list of
 * blocks going from the leaf towards the root.
 */
पूर्णांक
xbiपंचांगap_set_btcur_path(
	काष्ठा xbiपंचांगap		*biपंचांगap,
	काष्ठा xfs_btree_cur	*cur)
अणु
	काष्ठा xfs_buf		*bp;
	xfs_fsblock_t		fsb;
	पूर्णांक			i;
	पूर्णांक			error;

	क्रम (i = 0; i < cur->bc_nlevels && cur->bc_ptrs[i] == 1; i++) अणु
		xfs_btree_get_block(cur, i, &bp);
		अगर (!bp)
			जारी;
		fsb = XFS_DADDR_TO_FSB(cur->bc_mp, bp->b_bn);
		error = xbiपंचांगap_set(biपंचांगap, fsb, 1);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/* Collect a btree's block in the biपंचांगap. */
STATIC पूर्णांक
xbiपंचांगap_collect_btblock(
	काष्ठा xfs_btree_cur	*cur,
	पूर्णांक			level,
	व्योम			*priv)
अणु
	काष्ठा xbiपंचांगap		*biपंचांगap = priv;
	काष्ठा xfs_buf		*bp;
	xfs_fsblock_t		fsbno;

	xfs_btree_get_block(cur, level, &bp);
	अगर (!bp)
		वापस 0;

	fsbno = XFS_DADDR_TO_FSB(cur->bc_mp, bp->b_bn);
	वापस xbiपंचांगap_set(biपंचांगap, fsbno, 1);
पूर्ण

/* Walk the btree and mark the biपंचांगap wherever a btree block is found. */
पूर्णांक
xbiपंचांगap_set_btblocks(
	काष्ठा xbiपंचांगap		*biपंचांगap,
	काष्ठा xfs_btree_cur	*cur)
अणु
	वापस xfs_btree_visit_blocks(cur, xbiपंचांगap_collect_btblock,
			XFS_BTREE_VISIT_ALL, biपंचांगap);
पूर्ण

/* How many bits are set in this biपंचांगap? */
uपूर्णांक64_t
xbiपंचांगap_hweight(
	काष्ठा xbiपंचांगap		*biपंचांगap)
अणु
	काष्ठा xbiपंचांगap_range	*bmr;
	काष्ठा xbiपंचांगap_range	*n;
	uपूर्णांक64_t		ret = 0;

	क्रम_each_xbiपंचांगap_extent(bmr, n, biपंचांगap)
		ret += bmr->len;

	वापस ret;
पूर्ण
