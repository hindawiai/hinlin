<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2002,2005 Silicon Graphics, Inc.
 * Copyright (c) 2010 David Chinner.
 * Copyright (c) 2011 Christoph Hellwig.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_extent_busy.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_log.h"

व्योम
xfs_extent_busy_insert(
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	xfs_agblock_t		bno,
	xfs_extlen_t		len,
	अचिन्हित पूर्णांक		flags)
अणु
	काष्ठा xfs_extent_busy	*new;
	काष्ठा xfs_extent_busy	*busyp;
	काष्ठा xfs_perag	*pag;
	काष्ठा rb_node		**rbp;
	काष्ठा rb_node		*parent = शून्य;

	new = kmem_zalloc(माप(काष्ठा xfs_extent_busy), 0);
	new->agno = agno;
	new->bno = bno;
	new->length = len;
	INIT_LIST_HEAD(&new->list);
	new->flags = flags;

	/* trace beक्रमe insert to be able to see failed inserts */
	trace_xfs_extent_busy(tp->t_mountp, agno, bno, len);

	pag = xfs_perag_get(tp->t_mountp, new->agno);
	spin_lock(&pag->pagb_lock);
	rbp = &pag->pagb_tree.rb_node;
	जबतक (*rbp) अणु
		parent = *rbp;
		busyp = rb_entry(parent, काष्ठा xfs_extent_busy, rb_node);

		अगर (new->bno < busyp->bno) अणु
			rbp = &(*rbp)->rb_left;
			ASSERT(new->bno + new->length <= busyp->bno);
		पूर्ण अन्यथा अगर (new->bno > busyp->bno) अणु
			rbp = &(*rbp)->rb_right;
			ASSERT(bno >= busyp->bno + busyp->length);
		पूर्ण अन्यथा अणु
			ASSERT(0);
		पूर्ण
	पूर्ण

	rb_link_node(&new->rb_node, parent, rbp);
	rb_insert_color(&new->rb_node, &pag->pagb_tree);

	list_add(&new->list, &tp->t_busy);
	spin_unlock(&pag->pagb_lock);
	xfs_perag_put(pag);
पूर्ण

/*
 * Search क्रम a busy extent within the range of the extent we are about to
 * allocate.  You need to be holding the busy extent tree lock when calling
 * xfs_extent_busy_search(). This function वापसs 0 क्रम no overlapping busy
 * extent, -1 क्रम an overlapping but not exact busy extent, and 1 क्रम an exact
 * match. This is करोne so that a non-zero वापस indicates an overlap that
 * will require a synchronous transaction, but it can still be
 * used to distinguish between a partial or exact match.
 */
पूर्णांक
xfs_extent_busy_search(
	काष्ठा xfs_mount	*mp,
	xfs_agnumber_t		agno,
	xfs_agblock_t		bno,
	xfs_extlen_t		len)
अणु
	काष्ठा xfs_perag	*pag;
	काष्ठा rb_node		*rbp;
	काष्ठा xfs_extent_busy	*busyp;
	पूर्णांक			match = 0;

	pag = xfs_perag_get(mp, agno);
	spin_lock(&pag->pagb_lock);

	rbp = pag->pagb_tree.rb_node;

	/* find बंदst start bno overlap */
	जबतक (rbp) अणु
		busyp = rb_entry(rbp, काष्ठा xfs_extent_busy, rb_node);
		अगर (bno < busyp->bno) अणु
			/* may overlap, but exact start block is lower */
			अगर (bno + len > busyp->bno)
				match = -1;
			rbp = rbp->rb_left;
		पूर्ण अन्यथा अगर (bno > busyp->bno) अणु
			/* may overlap, but exact start block is higher */
			अगर (bno < busyp->bno + busyp->length)
				match = -1;
			rbp = rbp->rb_right;
		पूर्ण अन्यथा अणु
			/* bno matches busyp, length determines exact match */
			match = (busyp->length == len) ? 1 : -1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&pag->pagb_lock);
	xfs_perag_put(pag);
	वापस match;
पूर्ण

/*
 * The found मुक्त extent [fbno, fend] overlaps part or all of the given busy
 * extent.  If the overlap covers the beginning, the end, or all of the busy
 * extent, the overlapping portion can be made unbusy and used क्रम the
 * allocation.  We can't split a busy extent because we can't modअगरy a
 * transaction/CIL context busy list, but we can update an entry's block
 * number or length.
 *
 * Returns true अगर the extent can safely be reused, or false अगर the search
 * needs to be restarted.
 */
STATIC bool
xfs_extent_busy_update_extent(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_perag	*pag,
	काष्ठा xfs_extent_busy	*busyp,
	xfs_agblock_t		fbno,
	xfs_extlen_t		flen,
	bool			userdata) __releases(&pag->pagb_lock)
					  __acquires(&pag->pagb_lock)
अणु
	xfs_agblock_t		fend = fbno + flen;
	xfs_agblock_t		bbno = busyp->bno;
	xfs_agblock_t		bend = bbno + busyp->length;

	/*
	 * This extent is currently being discarded.  Give the thपढ़ो
	 * perक्रमming the discard a chance to mark the extent unbusy
	 * and retry.
	 */
	अगर (busyp->flags & XFS_EXTENT_BUSY_DISCARDED) अणु
		spin_unlock(&pag->pagb_lock);
		delay(1);
		spin_lock(&pag->pagb_lock);
		वापस false;
	पूर्ण

	/*
	 * If there is a busy extent overlapping a user allocation, we have
	 * no choice but to क्रमce the log and retry the search.
	 *
	 * Fortunately this करोes not happen during normal operation, but
	 * only अगर the fileप्रणाली is very low on space and has to dip पूर्णांकo
	 * the AGFL क्रम normal allocations.
	 */
	अगर (userdata)
		जाओ out_क्रमce_log;

	अगर (bbno < fbno && bend > fend) अणु
		/*
		 * Case 1:
		 *    bbno           bend
		 *    +BBBBBBBBBBBBBBBBB+
		 *        +---------+
		 *        fbno   fend
		 */

		/*
		 * We would have to split the busy extent to be able to track
		 * it correct, which we cannot करो because we would have to
		 * modअगरy the list of busy extents attached to the transaction
		 * or CIL context, which is immutable.
		 *
		 * Force out the log to clear the busy extent and retry the
		 * search.
		 */
		जाओ out_क्रमce_log;
	पूर्ण अन्यथा अगर (bbno >= fbno && bend <= fend) अणु
		/*
		 * Case 2:
		 *    bbno           bend
		 *    +BBBBBBBBBBBBBBBBB+
		 *    +-----------------+
		 *    fbno           fend
		 *
		 * Case 3:
		 *    bbno           bend
		 *    +BBBBBBBBBBBBBBBBB+
		 *    +--------------------------+
		 *    fbno                    fend
		 *
		 * Case 4:
		 *             bbno           bend
		 *             +BBBBBBBBBBBBBBBBB+
		 *    +--------------------------+
		 *    fbno                    fend
		 *
		 * Case 5:
		 *             bbno           bend
		 *             +BBBBBBBBBBBBBBBBB+
		 *    +-----------------------------------+
		 *    fbno                             fend
		 *
		 */

		/*
		 * The busy extent is fully covered by the extent we are
		 * allocating, and can simply be हटाओd from the rbtree.
		 * However we cannot हटाओ it from the immutable list
		 * tracking busy extents in the transaction or CIL context,
		 * so set the length to zero to mark it invalid.
		 *
		 * We also need to restart the busy extent search from the
		 * tree root, because erasing the node can rearrange the
		 * tree topology.
		 */
		rb_erase(&busyp->rb_node, &pag->pagb_tree);
		busyp->length = 0;
		वापस false;
	पूर्ण अन्यथा अगर (fend < bend) अणु
		/*
		 * Case 6:
		 *              bbno           bend
		 *             +BBBBBBBBBBBBBBBBB+
		 *             +---------+
		 *             fbno   fend
		 *
		 * Case 7:
		 *             bbno           bend
		 *             +BBBBBBBBBBBBBBBBB+
		 *    +------------------+
		 *    fbno            fend
		 *
		 */
		busyp->bno = fend;
	पूर्ण अन्यथा अगर (bbno < fbno) अणु
		/*
		 * Case 8:
		 *    bbno           bend
		 *    +BBBBBBBBBBBBBBBBB+
		 *        +-------------+
		 *        fbno       fend
		 *
		 * Case 9:
		 *    bbno           bend
		 *    +BBBBBBBBBBBBBBBBB+
		 *        +----------------------+
		 *        fbno                fend
		 */
		busyp->length = fbno - busyp->bno;
	पूर्ण अन्यथा अणु
		ASSERT(0);
	पूर्ण

	trace_xfs_extent_busy_reuse(mp, pag->pag_agno, fbno, flen);
	वापस true;

out_क्रमce_log:
	spin_unlock(&pag->pagb_lock);
	xfs_log_क्रमce(mp, XFS_LOG_SYNC);
	trace_xfs_extent_busy_क्रमce(mp, pag->pag_agno, fbno, flen);
	spin_lock(&pag->pagb_lock);
	वापस false;
पूर्ण


/*
 * For a given extent [fbno, flen], make sure we can reuse it safely.
 */
व्योम
xfs_extent_busy_reuse(
	काष्ठा xfs_mount	*mp,
	xfs_agnumber_t		agno,
	xfs_agblock_t		fbno,
	xfs_extlen_t		flen,
	bool			userdata)
अणु
	काष्ठा xfs_perag	*pag;
	काष्ठा rb_node		*rbp;

	ASSERT(flen > 0);

	pag = xfs_perag_get(mp, agno);
	spin_lock(&pag->pagb_lock);
restart:
	rbp = pag->pagb_tree.rb_node;
	जबतक (rbp) अणु
		काष्ठा xfs_extent_busy *busyp =
			rb_entry(rbp, काष्ठा xfs_extent_busy, rb_node);
		xfs_agblock_t	bbno = busyp->bno;
		xfs_agblock_t	bend = bbno + busyp->length;

		अगर (fbno + flen <= bbno) अणु
			rbp = rbp->rb_left;
			जारी;
		पूर्ण अन्यथा अगर (fbno >= bend) अणु
			rbp = rbp->rb_right;
			जारी;
		पूर्ण

		अगर (!xfs_extent_busy_update_extent(mp, pag, busyp, fbno, flen,
						  userdata))
			जाओ restart;
	पूर्ण
	spin_unlock(&pag->pagb_lock);
	xfs_perag_put(pag);
पूर्ण

/*
 * For a given extent [fbno, flen], search the busy extent list to find a
 * subset of the extent that is not busy.  If *rlen is smaller than
 * args->minlen no suitable extent could be found, and the higher level
 * code needs to क्रमce out the log and retry the allocation.
 *
 * Return the current busy generation क्रम the AG अगर the extent is busy. This
 * value can be used to रुको क्रम at least one of the currently busy extents
 * to be cleared. Note that the busy list is not guaranteed to be empty after
 * the gen is woken. The state of a specअगरic extent must always be confirmed
 * with another call to xfs_extent_busy_trim() beक्रमe it can be used.
 */
bool
xfs_extent_busy_trim(
	काष्ठा xfs_alloc_arg	*args,
	xfs_agblock_t		*bno,
	xfs_extlen_t		*len,
	अचिन्हित		*busy_gen)
अणु
	xfs_agblock_t		fbno;
	xfs_extlen_t		flen;
	काष्ठा rb_node		*rbp;
	bool			ret = false;

	ASSERT(*len > 0);

	spin_lock(&args->pag->pagb_lock);
	fbno = *bno;
	flen = *len;
	rbp = args->pag->pagb_tree.rb_node;
	जबतक (rbp && flen >= args->minlen) अणु
		काष्ठा xfs_extent_busy *busyp =
			rb_entry(rbp, काष्ठा xfs_extent_busy, rb_node);
		xfs_agblock_t	fend = fbno + flen;
		xfs_agblock_t	bbno = busyp->bno;
		xfs_agblock_t	bend = bbno + busyp->length;

		अगर (fend <= bbno) अणु
			rbp = rbp->rb_left;
			जारी;
		पूर्ण अन्यथा अगर (fbno >= bend) अणु
			rbp = rbp->rb_right;
			जारी;
		पूर्ण

		अगर (bbno <= fbno) अणु
			/* start overlap */

			/*
			 * Case 1:
			 *    bbno           bend
			 *    +BBBBBBBBBBBBBBBBB+
			 *        +---------+
			 *        fbno   fend
			 *
			 * Case 2:
			 *    bbno           bend
			 *    +BBBBBBBBBBBBBBBBB+
			 *    +-------------+
			 *    fbno       fend
			 *
			 * Case 3:
			 *    bbno           bend
			 *    +BBBBBBBBBBBBBBBBB+
			 *        +-------------+
			 *        fbno       fend
			 *
			 * Case 4:
			 *    bbno           bend
			 *    +BBBBBBBBBBBBBBBBB+
			 *    +-----------------+
			 *    fbno           fend
			 *
			 * No unbusy region in extent, वापस failure.
			 */
			अगर (fend <= bend)
				जाओ fail;

			/*
			 * Case 5:
			 *    bbno           bend
			 *    +BBBBBBBBBBBBBBBBB+
			 *        +----------------------+
			 *        fbno                fend
			 *
			 * Case 6:
			 *    bbno           bend
			 *    +BBBBBBBBBBBBBBBBB+
			 *    +--------------------------+
			 *    fbno                    fend
			 *
			 * Needs to be trimmed to:
			 *                       +-------+
			 *                       fbno fend
			 */
			fbno = bend;
		पूर्ण अन्यथा अगर (bend >= fend) अणु
			/* end overlap */

			/*
			 * Case 7:
			 *             bbno           bend
			 *             +BBBBBBBBBBBBBBBBB+
			 *    +------------------+
			 *    fbno            fend
			 *
			 * Case 8:
			 *             bbno           bend
			 *             +BBBBBBBBBBBBBBBBB+
			 *    +--------------------------+
			 *    fbno                    fend
			 *
			 * Needs to be trimmed to:
			 *    +-------+
			 *    fbno fend
			 */
			fend = bbno;
		पूर्ण अन्यथा अणु
			/* middle overlap */

			/*
			 * Case 9:
			 *             bbno           bend
			 *             +BBBBBBBBBBBBBBBBB+
			 *    +-----------------------------------+
			 *    fbno                             fend
			 *
			 * Can be trimmed to:
			 *    +-------+        OR         +-------+
			 *    fbno fend                   fbno fend
			 *
			 * Backward allocation leads to signअगरicant
			 * fragmentation of directories, which degrades
			 * directory perक्रमmance, thereक्रमe we always want to
			 * choose the option that produces क्रमward allocation
			 * patterns.
			 * Preferring the lower bno extent will make the next
			 * request use "fend" as the start of the next
			 * allocation;  अगर the segment is no दीर्घer busy at
			 * that poपूर्णांक, we'll get a contiguous allocation, but
			 * even अगर it is still busy, we will get a क्रमward
			 * allocation.
			 * We try to aव्योम choosing the segment at "bend",
			 * because that can lead to the next allocation
			 * taking the segment at "fbno", which would be a
			 * backward allocation.  We only use the segment at
			 * "fbno" अगर it is much larger than the current
			 * requested size, because in that हाल there's a
			 * good chance subsequent allocations will be
			 * contiguous.
			 */
			अगर (bbno - fbno >= args->maxlen) अणु
				/* left candidate fits perfect */
				fend = bbno;
			पूर्ण अन्यथा अगर (fend - bend >= args->maxlen * 4) अणु
				/* right candidate has enough मुक्त space */
				fbno = bend;
			पूर्ण अन्यथा अगर (bbno - fbno >= args->minlen) अणु
				/* left candidate fits minimum requirement */
				fend = bbno;
			पूर्ण अन्यथा अणु
				जाओ fail;
			पूर्ण
		पूर्ण

		flen = fend - fbno;
	पूर्ण
out:

	अगर (fbno != *bno || flen != *len) अणु
		trace_xfs_extent_busy_trim(args->mp, args->agno, *bno, *len,
					  fbno, flen);
		*bno = fbno;
		*len = flen;
		*busy_gen = args->pag->pagb_gen;
		ret = true;
	पूर्ण
	spin_unlock(&args->pag->pagb_lock);
	वापस ret;
fail:
	/*
	 * Return a zero extent length as failure indications.  All callers
	 * re-check अगर the trimmed extent satisfies the minlen requirement.
	 */
	flen = 0;
	जाओ out;
पूर्ण

STATIC व्योम
xfs_extent_busy_clear_one(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_perag	*pag,
	काष्ठा xfs_extent_busy	*busyp)
अणु
	अगर (busyp->length) अणु
		trace_xfs_extent_busy_clear(mp, busyp->agno, busyp->bno,
						busyp->length);
		rb_erase(&busyp->rb_node, &pag->pagb_tree);
	पूर्ण

	list_del_init(&busyp->list);
	kmem_मुक्त(busyp);
पूर्ण

अटल व्योम
xfs_extent_busy_put_pag(
	काष्ठा xfs_perag	*pag,
	bool			wakeup)
		__releases(pag->pagb_lock)
अणु
	अगर (wakeup) अणु
		pag->pagb_gen++;
		wake_up_all(&pag->pagb_रुको);
	पूर्ण

	spin_unlock(&pag->pagb_lock);
	xfs_perag_put(pag);
पूर्ण

/*
 * Remove all extents on the passed in list from the busy extents tree.
 * If करो_discard is set skip extents that need to be discarded, and mark
 * these as undergoing a discard operation instead.
 */
व्योम
xfs_extent_busy_clear(
	काष्ठा xfs_mount	*mp,
	काष्ठा list_head	*list,
	bool			करो_discard)
अणु
	काष्ठा xfs_extent_busy	*busyp, *n;
	काष्ठा xfs_perag	*pag = शून्य;
	xfs_agnumber_t		agno = शून्यAGNUMBER;
	bool			wakeup = false;

	list_क्रम_each_entry_safe(busyp, n, list, list) अणु
		अगर (busyp->agno != agno) अणु
			अगर (pag)
				xfs_extent_busy_put_pag(pag, wakeup);
			agno = busyp->agno;
			pag = xfs_perag_get(mp, agno);
			spin_lock(&pag->pagb_lock);
			wakeup = false;
		पूर्ण

		अगर (करो_discard && busyp->length &&
		    !(busyp->flags & XFS_EXTENT_BUSY_SKIP_DISCARD)) अणु
			busyp->flags = XFS_EXTENT_BUSY_DISCARDED;
		पूर्ण अन्यथा अणु
			xfs_extent_busy_clear_one(mp, pag, busyp);
			wakeup = true;
		पूर्ण
	पूर्ण

	अगर (pag)
		xfs_extent_busy_put_pag(pag, wakeup);
पूर्ण

/*
 * Flush out all busy extents क्रम this AG.
 */
व्योम
xfs_extent_busy_flush(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_perag	*pag,
	अचिन्हित		busy_gen)
अणु
	DEFINE_WAIT		(रुको);
	पूर्णांक			error;

	error = xfs_log_क्रमce(mp, XFS_LOG_SYNC);
	अगर (error)
		वापस;

	करो अणु
		prepare_to_रुको(&pag->pagb_रुको, &रुको, TASK_KILLABLE);
		अगर  (busy_gen != READ_ONCE(pag->pagb_gen))
			अवरोध;
		schedule();
	पूर्ण जबतक (1);

	finish_रुको(&pag->pagb_रुको, &रुको);
पूर्ण

व्योम
xfs_extent_busy_रुको_all(
	काष्ठा xfs_mount	*mp)
अणु
	DEFINE_WAIT		(रुको);
	xfs_agnumber_t		agno;

	क्रम (agno = 0; agno < mp->m_sb.sb_agcount; agno++) अणु
		काष्ठा xfs_perag *pag = xfs_perag_get(mp, agno);

		करो अणु
			prepare_to_रुको(&pag->pagb_रुको, &रुको, TASK_KILLABLE);
			अगर  (RB_EMPTY_ROOT(&pag->pagb_tree))
				अवरोध;
			schedule();
		पूर्ण जबतक (1);
		finish_रुको(&pag->pagb_रुको, &रुको);

		xfs_perag_put(pag);
	पूर्ण
पूर्ण

/*
 * Callback क्रम list_sort to sort busy extents by the AG they reside in.
 */
पूर्णांक
xfs_extent_busy_ag_cmp(
	व्योम			*priv,
	स्थिर काष्ठा list_head	*l1,
	स्थिर काष्ठा list_head	*l2)
अणु
	काष्ठा xfs_extent_busy	*b1 =
		container_of(l1, काष्ठा xfs_extent_busy, list);
	काष्ठा xfs_extent_busy	*b2 =
		container_of(l2, काष्ठा xfs_extent_busy, list);
	s32 dअगरf;

	dअगरf = b1->agno - b2->agno;
	अगर (!dअगरf)
		dअगरf = b1->bno - b2->bno;
	वापस dअगरf;
पूर्ण
