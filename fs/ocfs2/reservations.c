<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * reservations.c
 *
 * Allocation reservations implementation
 *
 * Some code borrowed from fs/ext3/balloc.c and is:
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 * The rest is copyright (C) 2010 Novell.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/bitops.h>
#समावेश <linux/list.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"
#समावेश "ocfs2_trace.h"

#अगर_घोषित CONFIG_OCFS2_DEBUG_FS
#घोषणा OCFS2_CHECK_RESERVATIONS
#पूर्ण_अगर

अटल DEFINE_SPINLOCK(resv_lock);

पूर्णांक ocfs2_dir_resv_allowed(काष्ठा ocfs2_super *osb)
अणु
	वापस (osb->osb_resv_level && osb->osb_dir_resv_level);
पूर्ण

अटल अचिन्हित पूर्णांक ocfs2_resv_winकरोw_bits(काष्ठा ocfs2_reservation_map *resmap,
					   काष्ठा ocfs2_alloc_reservation *resv)
अणु
	काष्ठा ocfs2_super *osb = resmap->m_osb;
	अचिन्हित पूर्णांक bits;

	अगर (!(resv->r_flags & OCFS2_RESV_FLAG_सूची)) अणु
		/* 8, 16, 32, 64, 128, 256, 512, 1024 */
		bits = 4 << osb->osb_resv_level;
	पूर्ण अन्यथा अणु
		bits = 4 << osb->osb_dir_resv_level;
	पूर्ण
	वापस bits;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ocfs2_resv_end(काष्ठा ocfs2_alloc_reservation *resv)
अणु
	अगर (resv->r_len)
		वापस resv->r_start + resv->r_len - 1;
	वापस resv->r_start;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_resv_empty(काष्ठा ocfs2_alloc_reservation *resv)
अणु
	वापस !!(resv->r_len == 0);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_resmap_disabled(काष्ठा ocfs2_reservation_map *resmap)
अणु
	अगर (resmap->m_osb->osb_resv_level == 0)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम ocfs2_dump_resv(काष्ठा ocfs2_reservation_map *resmap)
अणु
	काष्ठा ocfs2_super *osb = resmap->m_osb;
	काष्ठा rb_node *node;
	काष्ठा ocfs2_alloc_reservation *resv;
	पूर्णांक i = 0;

	mlog(ML_NOTICE, "Dumping resmap for device %s. Bitmap length: %u\n",
	     osb->dev_str, resmap->m_biपंचांगap_len);

	node = rb_first(&resmap->m_reservations);
	जबतक (node) अणु
		resv = rb_entry(node, काष्ठा ocfs2_alloc_reservation, r_node);

		mlog(ML_NOTICE, "start: %u\tend: %u\tlen: %u\tlast_start: %u"
		     "\tlast_len: %u\n", resv->r_start,
		     ocfs2_resv_end(resv), resv->r_len, resv->r_last_start,
		     resv->r_last_len);

		node = rb_next(node);
		i++;
	पूर्ण

	mlog(ML_NOTICE, "%d reservations found. LRU follows\n", i);

	i = 0;
	list_क्रम_each_entry(resv, &resmap->m_lru, r_lru) अणु
		mlog(ML_NOTICE, "LRU(%d) start: %u\tend: %u\tlen: %u\t"
		     "last_start: %u\tlast_len: %u\n", i, resv->r_start,
		     ocfs2_resv_end(resv), resv->r_len, resv->r_last_start,
		     resv->r_last_len);

		i++;
	पूर्ण
पूर्ण

#अगर_घोषित OCFS2_CHECK_RESERVATIONS
अटल पूर्णांक ocfs2_validate_resmap_bits(काष्ठा ocfs2_reservation_map *resmap,
				      पूर्णांक i,
				      काष्ठा ocfs2_alloc_reservation *resv)
अणु
	अक्षर *disk_biपंचांगap = resmap->m_disk_biपंचांगap;
	अचिन्हित पूर्णांक start = resv->r_start;
	अचिन्हित पूर्णांक end = ocfs2_resv_end(resv);

	जबतक (start <= end) अणु
		अगर (ocfs2_test_bit(start, disk_biपंचांगap)) अणु
			mlog(ML_ERROR,
			     "reservation %d covers an allocated area "
			     "starting at bit %u!\n", i, start);
			वापस 1;
		पूर्ण

		start++;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ocfs2_check_resmap(काष्ठा ocfs2_reservation_map *resmap)
अणु
	अचिन्हित पूर्णांक off = 0;
	पूर्णांक i = 0;
	काष्ठा rb_node *node;
	काष्ठा ocfs2_alloc_reservation *resv;

	node = rb_first(&resmap->m_reservations);
	जबतक (node) अणु
		resv = rb_entry(node, काष्ठा ocfs2_alloc_reservation, r_node);

		अगर (i > 0 && resv->r_start <= off) अणु
			mlog(ML_ERROR, "reservation %d has bad start off!\n",
			     i);
			जाओ bad;
		पूर्ण

		अगर (resv->r_len == 0) अणु
			mlog(ML_ERROR, "reservation %d has no length!\n",
			     i);
			जाओ bad;
		पूर्ण

		अगर (resv->r_start > ocfs2_resv_end(resv)) अणु
			mlog(ML_ERROR, "reservation %d has invalid range!\n",
			     i);
			जाओ bad;
		पूर्ण

		अगर (ocfs2_resv_end(resv) >= resmap->m_biपंचांगap_len) अणु
			mlog(ML_ERROR, "reservation %d extends past bitmap!\n",
			     i);
			जाओ bad;
		पूर्ण

		अगर (ocfs2_validate_resmap_bits(resmap, i, resv))
			जाओ bad;

		off = ocfs2_resv_end(resv);
		node = rb_next(node);

		i++;
	पूर्ण
	वापस;

bad:
	ocfs2_dump_resv(resmap);
	BUG();
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम ocfs2_check_resmap(काष्ठा ocfs2_reservation_map *resmap)
अणु

पूर्ण
#पूर्ण_अगर

व्योम ocfs2_resv_init_once(काष्ठा ocfs2_alloc_reservation *resv)
अणु
	स_रखो(resv, 0, माप(*resv));
	INIT_LIST_HEAD(&resv->r_lru);
पूर्ण

व्योम ocfs2_resv_set_type(काष्ठा ocfs2_alloc_reservation *resv,
			 अचिन्हित पूर्णांक flags)
अणु
	BUG_ON(flags & ~OCFS2_RESV_TYPES);

	resv->r_flags |= flags;
पूर्ण

पूर्णांक ocfs2_resmap_init(काष्ठा ocfs2_super *osb,
		      काष्ठा ocfs2_reservation_map *resmap)
अणु
	स_रखो(resmap, 0, माप(*resmap));

	resmap->m_osb = osb;
	resmap->m_reservations = RB_ROOT;
	/* m_biपंचांगap_len is initialized to zero by the above स_रखो. */
	INIT_LIST_HEAD(&resmap->m_lru);

	वापस 0;
पूर्ण

अटल व्योम ocfs2_resv_mark_lru(काष्ठा ocfs2_reservation_map *resmap,
				काष्ठा ocfs2_alloc_reservation *resv)
अणु
	निश्चित_spin_locked(&resv_lock);

	अगर (!list_empty(&resv->r_lru))
		list_del_init(&resv->r_lru);

	list_add_tail(&resv->r_lru, &resmap->m_lru);
पूर्ण

अटल व्योम __ocfs2_resv_trunc(काष्ठा ocfs2_alloc_reservation *resv)
अणु
	resv->r_len = 0;
	resv->r_start = 0;
पूर्ण

अटल व्योम ocfs2_resv_हटाओ(काष्ठा ocfs2_reservation_map *resmap,
			      काष्ठा ocfs2_alloc_reservation *resv)
अणु
	अगर (resv->r_flags & OCFS2_RESV_FLAG_INUSE) अणु
		list_del_init(&resv->r_lru);
		rb_erase(&resv->r_node, &resmap->m_reservations);
		resv->r_flags &= ~OCFS2_RESV_FLAG_INUSE;
	पूर्ण
पूर्ण

अटल व्योम __ocfs2_resv_discard(काष्ठा ocfs2_reservation_map *resmap,
				 काष्ठा ocfs2_alloc_reservation *resv)
अणु
	निश्चित_spin_locked(&resv_lock);

	__ocfs2_resv_trunc(resv);
	/*
	 * last_len and last_start no दीर्घer make sense अगर
	 * we're changing the range of our allocations.
	 */
	resv->r_last_len = resv->r_last_start = 0;

	ocfs2_resv_हटाओ(resmap, resv);
पूर्ण

/* करोes nothing अगर 'resv' is null */
व्योम ocfs2_resv_discard(काष्ठा ocfs2_reservation_map *resmap,
			काष्ठा ocfs2_alloc_reservation *resv)
अणु
	अगर (resv) अणु
		spin_lock(&resv_lock);
		__ocfs2_resv_discard(resmap, resv);
		spin_unlock(&resv_lock);
	पूर्ण
पूर्ण

अटल व्योम ocfs2_resmap_clear_all_resv(काष्ठा ocfs2_reservation_map *resmap)
अणु
	काष्ठा rb_node *node;
	काष्ठा ocfs2_alloc_reservation *resv;

	निश्चित_spin_locked(&resv_lock);

	जबतक ((node = rb_last(&resmap->m_reservations)) != शून्य) अणु
		resv = rb_entry(node, काष्ठा ocfs2_alloc_reservation, r_node);

		__ocfs2_resv_discard(resmap, resv);
	पूर्ण
पूर्ण

व्योम ocfs2_resmap_restart(काष्ठा ocfs2_reservation_map *resmap,
			  अचिन्हित पूर्णांक clen, अक्षर *disk_biपंचांगap)
अणु
	अगर (ocfs2_resmap_disabled(resmap))
		वापस;

	spin_lock(&resv_lock);

	ocfs2_resmap_clear_all_resv(resmap);
	resmap->m_biपंचांगap_len = clen;
	resmap->m_disk_biपंचांगap = disk_biपंचांगap;

	spin_unlock(&resv_lock);
पूर्ण

व्योम ocfs2_resmap_uninit(काष्ठा ocfs2_reservation_map *resmap)
अणु
	/* Does nothing क्रम now. Keep this around क्रम API symmetry */
पूर्ण

अटल व्योम ocfs2_resv_insert(काष्ठा ocfs2_reservation_map *resmap,
			      काष्ठा ocfs2_alloc_reservation *new)
अणु
	काष्ठा rb_root *root = &resmap->m_reservations;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा ocfs2_alloc_reservation *पंचांगp;

	निश्चित_spin_locked(&resv_lock);

	trace_ocfs2_resv_insert(new->r_start, new->r_len);

	जबतक (*p) अणु
		parent = *p;

		पंचांगp = rb_entry(parent, काष्ठा ocfs2_alloc_reservation, r_node);

		अगर (new->r_start < पंचांगp->r_start) अणु
			p = &(*p)->rb_left;

			/*
			 * This is a good place to check क्रम
			 * overlapping reservations.
			 */
			BUG_ON(ocfs2_resv_end(new) >= पंचांगp->r_start);
		पूर्ण अन्यथा अगर (new->r_start > ocfs2_resv_end(पंचांगp)) अणु
			p = &(*p)->rb_right;
		पूर्ण अन्यथा अणु
			/* This should never happen! */
			mlog(ML_ERROR, "Duplicate reservation window!\n");
			BUG();
		पूर्ण
	पूर्ण

	rb_link_node(&new->r_node, parent, p);
	rb_insert_color(&new->r_node, root);
	new->r_flags |= OCFS2_RESV_FLAG_INUSE;

	ocfs2_resv_mark_lru(resmap, new);

	ocfs2_check_resmap(resmap);
पूर्ण

/**
 * ocfs2_find_resv_lhs() - find the winकरोw which contains goal
 * @resmap: reservation map to search
 * @goal: which bit to search क्रम
 *
 * If a winकरोw containing that goal is not found, we वापस the winकरोw
 * which comes beक्रमe goal. Returns शून्य on empty rbtree or no winकरोw
 * beक्रमe goal.
 */
अटल काष्ठा ocfs2_alloc_reservation *
ocfs2_find_resv_lhs(काष्ठा ocfs2_reservation_map *resmap, अचिन्हित पूर्णांक goal)
अणु
	काष्ठा ocfs2_alloc_reservation *resv = शून्य;
	काष्ठा ocfs2_alloc_reservation *prev_resv = शून्य;
	काष्ठा rb_node *node = resmap->m_reservations.rb_node;

	निश्चित_spin_locked(&resv_lock);

	अगर (!node)
		वापस शून्य;

	node = rb_first(&resmap->m_reservations);
	जबतक (node) अणु
		resv = rb_entry(node, काष्ठा ocfs2_alloc_reservation, r_node);

		अगर (resv->r_start <= goal && ocfs2_resv_end(resv) >= goal)
			अवरोध;

		/* Check अगर we overshot the reservation just beक्रमe goal? */
		अगर (resv->r_start > goal) अणु
			resv = prev_resv;
			अवरोध;
		पूर्ण

		prev_resv = resv;
		node = rb_next(node);
	पूर्ण

	वापस resv;
पूर्ण

/*
 * We are given a range within the biपंचांगap, which corresponds to a gap
 * inside the reservations tree (search_start, search_len). The range
 * can be anything from the whole biपंचांगap, to a gap between
 * reservations.
 *
 * The start value of *rstart is insignअगरicant.
 *
 * This function searches the biपंचांगap range starting at search_start
 * with length search_len क्रम a set of contiguous मुक्त bits. We try
 * to find up to 'wanted' bits, but can someबार वापस less.
 *
 * Returns the length of allocation, 0 अगर no मुक्त bits are found.
 *
 * *cstart and *clen will also be populated with the result.
 */
अटल पूर्णांक ocfs2_resmap_find_मुक्त_bits(काष्ठा ocfs2_reservation_map *resmap,
				       अचिन्हित पूर्णांक wanted,
				       अचिन्हित पूर्णांक search_start,
				       अचिन्हित पूर्णांक search_len,
				       अचिन्हित पूर्णांक *rstart,
				       अचिन्हित पूर्णांक *rlen)
अणु
	व्योम *biपंचांगap = resmap->m_disk_biपंचांगap;
	अचिन्हित पूर्णांक best_start, best_len = 0;
	पूर्णांक offset, start, found;

	trace_ocfs2_resmap_find_मुक्त_bits_begin(search_start, search_len,
						wanted, resmap->m_biपंचांगap_len);

	found = best_start = best_len = 0;

	start = search_start;
	जबतक ((offset = ocfs2_find_next_zero_bit(biपंचांगap, resmap->m_biपंचांगap_len,
						 start)) != -1) अणु
		/* Search reached end of the region */
		अगर (offset >= (search_start + search_len))
			अवरोध;

		अगर (offset == start) अणु
			/* we found a zero */
			found++;
			/* move start to the next bit to test */
			start++;
		पूर्ण अन्यथा अणु
			/* got a zero after some ones */
			found = 1;
			start = offset + 1;
		पूर्ण
		अगर (found > best_len) अणु
			best_len = found;
			best_start = start - found;
		पूर्ण

		अगर (found >= wanted)
			अवरोध;
	पूर्ण

	अगर (best_len == 0)
		वापस 0;

	अगर (best_len >= wanted)
		best_len = wanted;

	*rlen = best_len;
	*rstart = best_start;

	trace_ocfs2_resmap_find_मुक्त_bits_end(best_start, best_len);

	वापस *rlen;
पूर्ण

अटल व्योम __ocfs2_resv_find_winकरोw(काष्ठा ocfs2_reservation_map *resmap,
				     काष्ठा ocfs2_alloc_reservation *resv,
				     अचिन्हित पूर्णांक goal, अचिन्हित पूर्णांक wanted)
अणु
	काष्ठा rb_root *root = &resmap->m_reservations;
	अचिन्हित पूर्णांक gap_start, gap_end, gap_len;
	काष्ठा ocfs2_alloc_reservation *prev_resv, *next_resv;
	काष्ठा rb_node *prev, *next;
	अचिन्हित पूर्णांक cstart, clen;
	अचिन्हित पूर्णांक best_start = 0, best_len = 0;

	/*
	 * Nasty हालs to consider:
	 *
	 * - rbtree is empty
	 * - our winकरोw should be first in all reservations
	 * - our winकरोw should be last in all reservations
	 * - need to make sure we करोn't go past end of biपंचांगap
	 */
	trace_ocfs2_resv_find_winकरोw_begin(resv->r_start, ocfs2_resv_end(resv),
					   goal, wanted, RB_EMPTY_ROOT(root));

	निश्चित_spin_locked(&resv_lock);

	अगर (RB_EMPTY_ROOT(root)) अणु
		/*
		 * Easiest हाल - empty tree. We can just take
		 * whatever winकरोw of मुक्त bits we want.
		 */
		clen = ocfs2_resmap_find_मुक्त_bits(resmap, wanted, goal,
						   resmap->m_biपंचांगap_len - goal,
						   &cstart, &clen);

		/*
		 * This should never happen - the local alloc winकरोw
		 * will always have मुक्त bits when we're called.
		 */
		BUG_ON(goal == 0 && clen == 0);

		अगर (clen == 0)
			वापस;

		resv->r_start = cstart;
		resv->r_len = clen;

		ocfs2_resv_insert(resmap, resv);
		वापस;
	पूर्ण

	prev_resv = ocfs2_find_resv_lhs(resmap, goal);

	अगर (prev_resv == शून्य) अणु
		/*
		 * A शून्य here means that the search code couldn't
		 * find a winकरोw that starts beक्रमe goal.
		 *
		 * However, we can take the first winकरोw after goal,
		 * which is also by definition, the lefपंचांगost winकरोw in
		 * the entire tree. If we can find मुक्त bits in the
		 * gap between goal and the LHS winकरोw, then the
		 * reservation can safely be placed there.
		 *
		 * Otherwise we fall back to a linear search, checking
		 * the gaps in between winकरोws क्रम a place to
		 * allocate.
		 */

		next = rb_first(root);
		next_resv = rb_entry(next, काष्ठा ocfs2_alloc_reservation,
				     r_node);

		/*
		 * The search should never वापस such a winकरोw. (see
		 * comment above
		 */
		अगर (next_resv->r_start <= goal) अणु
			mlog(ML_ERROR, "goal: %u next_resv: start %u len %u\n",
			     goal, next_resv->r_start, next_resv->r_len);
			ocfs2_dump_resv(resmap);
			BUG();
		पूर्ण

		clen = ocfs2_resmap_find_मुक्त_bits(resmap, wanted, goal,
						   next_resv->r_start - goal,
						   &cstart, &clen);
		अगर (clen) अणु
			best_len = clen;
			best_start = cstart;
			अगर (best_len == wanted)
				जाओ out_insert;
		पूर्ण

		prev_resv = next_resv;
		next_resv = शून्य;
	पूर्ण

	trace_ocfs2_resv_find_winकरोw_prev(prev_resv->r_start,
					  ocfs2_resv_end(prev_resv));

	prev = &prev_resv->r_node;

	/* Now we करो a linear search क्रम a winकरोw, starting at 'prev_rsv' */
	जबतक (1) अणु
		next = rb_next(prev);
		अगर (next) अणु
			next_resv = rb_entry(next,
					     काष्ठा ocfs2_alloc_reservation,
					     r_node);

			gap_start = ocfs2_resv_end(prev_resv) + 1;
			gap_end = next_resv->r_start - 1;
			gap_len = gap_end - gap_start + 1;
		पूर्ण अन्यथा अणु
			/*
			 * We're at the righपंचांगost edge of the
			 * tree. See अगर a reservation between this
			 * winकरोw and the end of the biपंचांगap will work.
			 */
			gap_start = ocfs2_resv_end(prev_resv) + 1;
			gap_len = resmap->m_biपंचांगap_len - gap_start;
			gap_end = resmap->m_biपंचांगap_len - 1;
		पूर्ण

		trace_ocfs2_resv_find_winकरोw_next(next ? next_resv->r_start: -1,
					next ? ocfs2_resv_end(next_resv) : -1);
		/*
		 * No need to check this gap अगर we have alपढ़ोy found
		 * a larger region of मुक्त bits.
		 */
		अगर (gap_len <= best_len)
			जाओ next_resv;

		clen = ocfs2_resmap_find_मुक्त_bits(resmap, wanted, gap_start,
						   gap_len, &cstart, &clen);
		अगर (clen == wanted) अणु
			best_len = clen;
			best_start = cstart;
			जाओ out_insert;
		पूर्ण अन्यथा अगर (clen > best_len) अणु
			best_len = clen;
			best_start = cstart;
		पूर्ण

next_resv:
		अगर (!next)
			अवरोध;

		prev = next;
		prev_resv = rb_entry(prev, काष्ठा ocfs2_alloc_reservation,
				     r_node);
	पूर्ण

out_insert:
	अगर (best_len) अणु
		resv->r_start = best_start;
		resv->r_len = best_len;
		ocfs2_resv_insert(resmap, resv);
	पूर्ण
पूर्ण

अटल व्योम ocfs2_cannibalize_resv(काष्ठा ocfs2_reservation_map *resmap,
				   काष्ठा ocfs2_alloc_reservation *resv,
				   अचिन्हित पूर्णांक wanted)
अणु
	काष्ठा ocfs2_alloc_reservation *lru_resv;
	पूर्णांक पंचांगpwinकरोw = !!(resv->r_flags & OCFS2_RESV_FLAG_TMP);
	अचिन्हित पूर्णांक min_bits;

	अगर (!पंचांगpwinकरोw)
		min_bits = ocfs2_resv_winकरोw_bits(resmap, resv) >> 1;
	अन्यथा
		min_bits = wanted; /* We at know the temp winकरोw will use all
				    * of these bits */

	/*
	 * Take the first reservation off the LRU as our 'target'. We
	 * करोn't try to be smart about it. There might be a हाल क्रम
	 * searching based on size but I करोn't have enough data to be
	 * sure. --Mark (3/16/2010)
	 */
	lru_resv = list_first_entry(&resmap->m_lru,
				    काष्ठा ocfs2_alloc_reservation, r_lru);

	trace_ocfs2_cannibalize_resv_begin(lru_resv->r_start,
					   lru_resv->r_len,
					   ocfs2_resv_end(lru_resv));

	/*
	 * Cannibalize (some or all) of the target reservation and
	 * feed it to the current winकरोw.
	 */
	अगर (lru_resv->r_len <= min_bits) अणु
		/*
		 * Discard completely अगर size is less than or equal to a
		 * reasonable threshold - 50% of winकरोw bits क्रम non temporary
		 * winकरोws.
		 */
		resv->r_start = lru_resv->r_start;
		resv->r_len = lru_resv->r_len;

		__ocfs2_resv_discard(resmap, lru_resv);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक shrink;
		अगर (पंचांगpwinकरोw)
			shrink = min_bits;
		अन्यथा
			shrink = lru_resv->r_len / 2;

		lru_resv->r_len -= shrink;

		resv->r_start = ocfs2_resv_end(lru_resv) + 1;
		resv->r_len = shrink;
	पूर्ण

	trace_ocfs2_cannibalize_resv_end(resv->r_start, ocfs2_resv_end(resv),
					 resv->r_len, resv->r_last_start,
					 resv->r_last_len);

	ocfs2_resv_insert(resmap, resv);
पूर्ण

अटल व्योम ocfs2_resv_find_winकरोw(काष्ठा ocfs2_reservation_map *resmap,
				   काष्ठा ocfs2_alloc_reservation *resv,
				   अचिन्हित पूर्णांक wanted)
अणु
	अचिन्हित पूर्णांक goal = 0;

	BUG_ON(!ocfs2_resv_empty(resv));

	/*
	 * Begin by trying to get a winकरोw as बंद to the previous
	 * one as possible. Using the most recent allocation as a
	 * start goal makes sense.
	 */
	अगर (resv->r_last_len) अणु
		goal = resv->r_last_start + resv->r_last_len;
		अगर (goal >= resmap->m_biपंचांगap_len)
			goal = 0;
	पूर्ण

	__ocfs2_resv_find_winकरोw(resmap, resv, goal, wanted);

	/* Search from last alloc didn't work, try once more from beginning. */
	अगर (ocfs2_resv_empty(resv) && goal != 0)
		__ocfs2_resv_find_winकरोw(resmap, resv, 0, wanted);

	अगर (ocfs2_resv_empty(resv)) अणु
		/*
		 * Still empty? Pull oldest one off the LRU, हटाओ it from
		 * tree, put this one in it's place.
		 */
		ocfs2_cannibalize_resv(resmap, resv, wanted);
	पूर्ण

	BUG_ON(ocfs2_resv_empty(resv));
पूर्ण

पूर्णांक ocfs2_resmap_resv_bits(काष्ठा ocfs2_reservation_map *resmap,
			   काष्ठा ocfs2_alloc_reservation *resv,
			   पूर्णांक *cstart, पूर्णांक *clen)
अणु
	अगर (resv == शून्य || ocfs2_resmap_disabled(resmap))
		वापस -ENOSPC;

	spin_lock(&resv_lock);

	अगर (ocfs2_resv_empty(resv)) अणु
		/*
		 * We करोn't want to over-allocate क्रम temporary
		 * winकरोws. Otherwise, we run the risk of fragmenting the
		 * allocation space.
		 */
		अचिन्हित पूर्णांक wanted = ocfs2_resv_winकरोw_bits(resmap, resv);

		अगर ((resv->r_flags & OCFS2_RESV_FLAG_TMP) || wanted < *clen)
			wanted = *clen;

		/*
		 * Try to get a winकरोw here. If it works, we must fall
		 * through and test the biपंचांगap . This aव्योमs some
		 * ping-ponging of winकरोws due to non-reserved space
		 * being allocation beक्रमe we initialize a winकरोw क्रम
		 * that inode.
		 */
		ocfs2_resv_find_winकरोw(resmap, resv, wanted);
		trace_ocfs2_resmap_resv_bits(resv->r_start, resv->r_len);
	पूर्ण

	BUG_ON(ocfs2_resv_empty(resv));

	*cstart = resv->r_start;
	*clen = resv->r_len;

	spin_unlock(&resv_lock);
	वापस 0;
पूर्ण

अटल व्योम
	ocfs2_adjust_resv_from_alloc(काष्ठा ocfs2_reservation_map *resmap,
				     काष्ठा ocfs2_alloc_reservation *resv,
				     अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक end)
अणु
	अचिन्हित पूर्णांक rhs = 0;
	अचिन्हित पूर्णांक old_end = ocfs2_resv_end(resv);

	BUG_ON(start != resv->r_start || old_end < end);

	/*
	 * Completely used? We can हटाओ it then.
	 */
	अगर (old_end == end) अणु
		__ocfs2_resv_discard(resmap, resv);
		वापस;
	पूर्ण

	rhs = old_end - end;

	/*
	 * This should have been trapped above.
	 */
	BUG_ON(rhs == 0);

	resv->r_start = end + 1;
	resv->r_len = old_end - resv->r_start + 1;
पूर्ण

व्योम ocfs2_resmap_claimed_bits(काष्ठा ocfs2_reservation_map *resmap,
			       काष्ठा ocfs2_alloc_reservation *resv,
			       u32 cstart, u32 clen)
अणु
	अचिन्हित पूर्णांक cend = cstart + clen - 1;

	अगर (resmap == शून्य || ocfs2_resmap_disabled(resmap))
		वापस;

	अगर (resv == शून्य)
		वापस;

	BUG_ON(cstart != resv->r_start);

	spin_lock(&resv_lock);

	trace_ocfs2_resmap_claimed_bits_begin(cstart, cend, clen, resv->r_start,
					      ocfs2_resv_end(resv), resv->r_len,
					      resv->r_last_start,
					      resv->r_last_len);

	BUG_ON(cstart < resv->r_start);
	BUG_ON(cstart > ocfs2_resv_end(resv));
	BUG_ON(cend > ocfs2_resv_end(resv));

	ocfs2_adjust_resv_from_alloc(resmap, resv, cstart, cend);
	resv->r_last_start = cstart;
	resv->r_last_len = clen;

	/*
	 * May have been discarded above from
	 * ocfs2_adjust_resv_from_alloc().
	 */
	अगर (!ocfs2_resv_empty(resv))
		ocfs2_resv_mark_lru(resmap, resv);

	trace_ocfs2_resmap_claimed_bits_end(resv->r_start, ocfs2_resv_end(resv),
					    resv->r_len, resv->r_last_start,
					    resv->r_last_len);

	ocfs2_check_resmap(resmap);

	spin_unlock(&resv_lock);
पूर्ण
