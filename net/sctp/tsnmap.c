<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001 Intel Corp.
 *
 * This file is part of the SCTP kernel implementation
 *
 * These functions manipulate sctp tsn mapping array.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Jon Grimm             <jgrimm@us.ibm.com>
 *    Karl Knutson          <karl@athena.chicago.il.us>
 *    Sridhar Samudrala     <sri@us.ibm.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>

अटल व्योम sctp_tsnmap_update(काष्ठा sctp_tsnmap *map);
अटल व्योम sctp_tsnmap_find_gap_ack(अचिन्हित दीर्घ *map, __u16 off,
				     __u16 len, __u16 *start, __u16 *end);
अटल पूर्णांक sctp_tsnmap_grow(काष्ठा sctp_tsnmap *map, u16 size);

/* Initialize a block of memory as a tsnmap.  */
काष्ठा sctp_tsnmap *sctp_tsnmap_init(काष्ठा sctp_tsnmap *map, __u16 len,
				     __u32 initial_tsn, gfp_t gfp)
अणु
	अगर (!map->tsn_map) अणु
		map->tsn_map = kzalloc(len>>3, gfp);
		अगर (map->tsn_map == शून्य)
			वापस शून्य;

		map->len = len;
	पूर्ण अन्यथा अणु
		biपंचांगap_zero(map->tsn_map, map->len);
	पूर्ण

	/* Keep track of TSNs represented by tsn_map.  */
	map->base_tsn = initial_tsn;
	map->cumulative_tsn_ack_poपूर्णांक = initial_tsn - 1;
	map->max_tsn_seen = map->cumulative_tsn_ack_poपूर्णांक;
	map->num_dup_tsns = 0;

	वापस map;
पूर्ण

व्योम sctp_tsnmap_मुक्त(काष्ठा sctp_tsnmap *map)
अणु
	map->len = 0;
	kमुक्त(map->tsn_map);
पूर्ण

/* Test the tracking state of this TSN.
 * Returns:
 *   0 अगर the TSN has not yet been seen
 *  >0 अगर the TSN has been seen (duplicate)
 *  <0 अगर the TSN is invalid (too large to track)
 */
पूर्णांक sctp_tsnmap_check(स्थिर काष्ठा sctp_tsnmap *map, __u32 tsn)
अणु
	u32 gap;

	/* Check to see अगर this is an old TSN */
	अगर (TSN_lte(tsn, map->cumulative_tsn_ack_poपूर्णांक))
		वापस 1;

	/* Verअगरy that we can hold this TSN and that it will not
	 * overflow our map
	 */
	अगर (!TSN_lt(tsn, map->base_tsn + SCTP_TSN_MAP_SIZE))
		वापस -1;

	/* Calculate the index पूर्णांकo the mapping arrays.  */
	gap = tsn - map->base_tsn;

	/* Check to see अगर TSN has alपढ़ोy been recorded.  */
	अगर (gap < map->len && test_bit(gap, map->tsn_map))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण


/* Mark this TSN as seen.  */
पूर्णांक sctp_tsnmap_mark(काष्ठा sctp_tsnmap *map, __u32 tsn,
		     काष्ठा sctp_transport *trans)
अणु
	u16 gap;

	अगर (TSN_lt(tsn, map->base_tsn))
		वापस 0;

	gap = tsn - map->base_tsn;

	अगर (gap >= map->len && !sctp_tsnmap_grow(map, gap + 1))
		वापस -ENOMEM;

	अगर (!sctp_tsnmap_has_gap(map) && gap == 0) अणु
		/* In this हाल the map has no gaps and the tsn we are
		 * recording is the next expected tsn.  We करोn't touch
		 * the map but simply bump the values.
		 */
		map->max_tsn_seen++;
		map->cumulative_tsn_ack_poपूर्णांक++;
		अगर (trans)
			trans->sack_generation =
				trans->asoc->peer.sack_generation;
		map->base_tsn++;
	पूर्ण अन्यथा अणु
		/* Either we alपढ़ोy have a gap, or about to record a gap, so
		 * have work to करो.
		 *
		 * Bump the max.
		 */
		अगर (TSN_lt(map->max_tsn_seen, tsn))
			map->max_tsn_seen = tsn;

		/* Mark the TSN as received.  */
		set_bit(gap, map->tsn_map);

		/* Go fixup any पूर्णांकernal TSN mapping variables including
		 * cumulative_tsn_ack_poपूर्णांक.
		 */
		sctp_tsnmap_update(map);
	पूर्ण

	वापस 0;
पूर्ण


/* Initialize a Gap Ack Block iterator from memory being provided.  */
अटल व्योम sctp_tsnmap_iter_init(स्थिर काष्ठा sctp_tsnmap *map,
				  काष्ठा sctp_tsnmap_iter *iter)
अणु
	/* Only start looking one past the Cumulative TSN Ack Poपूर्णांक.  */
	iter->start = map->cumulative_tsn_ack_poपूर्णांक + 1;
पूर्ण

/* Get the next Gap Ack Blocks. Returns 0 अगर there was not another block
 * to get.
 */
अटल पूर्णांक sctp_tsnmap_next_gap_ack(स्थिर काष्ठा sctp_tsnmap *map,
				    काष्ठा sctp_tsnmap_iter *iter,
				    __u16 *start, __u16 *end)
अणु
	पूर्णांक ended = 0;
	__u16 start_ = 0, end_ = 0, offset;

	/* If there are no more gap acks possible, get out fast.  */
	अगर (TSN_lte(map->max_tsn_seen, iter->start))
		वापस 0;

	offset = iter->start - map->base_tsn;
	sctp_tsnmap_find_gap_ack(map->tsn_map, offset, map->len,
				 &start_, &end_);

	/* The Gap Ack Block happens to end at the end of the map. */
	अगर (start_ && !end_)
		end_ = map->len - 1;

	/* If we found a Gap Ack Block, वापस the start and end and
	 * bump the iterator क्रमward.
	 */
	अगर (end_) अणु
		/* Fix up the start and end based on the
		 * Cumulative TSN Ack which is always 1 behind base.
		 */
		*start = start_ + 1;
		*end = end_ + 1;

		/* Move the iterator क्रमward.  */
		iter->start = map->cumulative_tsn_ack_poपूर्णांक + *end + 1;
		ended = 1;
	पूर्ण

	वापस ended;
पूर्ण

/* Mark this and any lower TSN as seen.  */
व्योम sctp_tsnmap_skip(काष्ठा sctp_tsnmap *map, __u32 tsn)
अणु
	u32 gap;

	अगर (TSN_lt(tsn, map->base_tsn))
		वापस;
	अगर (!TSN_lt(tsn, map->base_tsn + SCTP_TSN_MAP_SIZE))
		वापस;

	/* Bump the max.  */
	अगर (TSN_lt(map->max_tsn_seen, tsn))
		map->max_tsn_seen = tsn;

	gap = tsn - map->base_tsn + 1;

	map->base_tsn += gap;
	map->cumulative_tsn_ack_poपूर्णांक += gap;
	अगर (gap >= map->len) अणु
		/* If our gap is larger then the map size, just
		 * zero out the map.
		 */
		biपंचांगap_zero(map->tsn_map, map->len);
	पूर्ण अन्यथा अणु
		/* If the gap is smaller than the map size,
		 * shअगरt the map by 'gap' bits and update further.
		 */
		biपंचांगap_shअगरt_right(map->tsn_map, map->tsn_map, gap, map->len);
		sctp_tsnmap_update(map);
	पूर्ण
पूर्ण

/********************************************************************
 * 2nd Level Abstractions
 ********************************************************************/

/* This निजी helper function updates the tsnmap buffers and
 * the Cumulative TSN Ack Poपूर्णांक.
 */
अटल व्योम sctp_tsnmap_update(काष्ठा sctp_tsnmap *map)
अणु
	u16 len;
	अचिन्हित दीर्घ zero_bit;


	len = map->max_tsn_seen - map->cumulative_tsn_ack_poपूर्णांक;
	zero_bit = find_first_zero_bit(map->tsn_map, len);
	अगर (!zero_bit)
		वापस;		/* The first 0-bit is bit 0.  nothing to करो */

	map->base_tsn += zero_bit;
	map->cumulative_tsn_ack_poपूर्णांक += zero_bit;

	biपंचांगap_shअगरt_right(map->tsn_map, map->tsn_map, zero_bit, map->len);
पूर्ण

/* How many data chunks  are we missing from our peer?
 */
__u16 sctp_tsnmap_pending(काष्ठा sctp_tsnmap *map)
अणु
	__u32 cum_tsn = map->cumulative_tsn_ack_poपूर्णांक;
	__u32 max_tsn = map->max_tsn_seen;
	__u32 base_tsn = map->base_tsn;
	__u16 pending_data;
	u32 gap;

	pending_data = max_tsn - cum_tsn;
	gap = max_tsn - base_tsn;

	अगर (gap == 0 || gap >= map->len)
		जाओ out;

	pending_data -= biपंचांगap_weight(map->tsn_map, gap + 1);
out:
	वापस pending_data;
पूर्ण

/* This is a निजी helper क्रम finding Gap Ack Blocks.  It searches a
 * single array क्रम the start and end of a Gap Ack Block.
 *
 * The flags "started" and "ended" tell is अगर we found the beginning
 * or (respectively) the end of a Gap Ack Block.
 */
अटल व्योम sctp_tsnmap_find_gap_ack(अचिन्हित दीर्घ *map, __u16 off,
				     __u16 len, __u16 *start, __u16 *end)
अणु
	पूर्णांक i = off;

	/* Look through the entire array, but अवरोध out
	 * early अगर we have found the end of the Gap Ack Block.
	 */

	/* Also, stop looking past the maximum TSN seen. */

	/* Look क्रम the start. */
	i = find_next_bit(map, len, off);
	अगर (i < len)
		*start = i;

	/* Look क्रम the end.  */
	अगर (*start) अणु
		/* We have found the start, let's find the
		 * end.  If we find the end, अवरोध out.
		 */
		i = find_next_zero_bit(map, len, i);
		अगर (i < len)
			*end = i - 1;
	पूर्ण
पूर्ण

/* Renege that we have seen a TSN.  */
व्योम sctp_tsnmap_renege(काष्ठा sctp_tsnmap *map, __u32 tsn)
अणु
	u32 gap;

	अगर (TSN_lt(tsn, map->base_tsn))
		वापस;
	/* Assert: TSN is in range.  */
	अगर (!TSN_lt(tsn, map->base_tsn + map->len))
		वापस;

	gap = tsn - map->base_tsn;

	/* Pretend we never saw the TSN.  */
	clear_bit(gap, map->tsn_map);
पूर्ण

/* How many gap ack blocks करो we have recorded? */
__u16 sctp_tsnmap_num_gअसल(काष्ठा sctp_tsnmap *map,
			   काष्ठा sctp_gap_ack_block *gअसल)
अणु
	काष्ठा sctp_tsnmap_iter iter;
	पूर्णांक ngaps = 0;

	/* Refresh the gap ack inक्रमmation. */
	अगर (sctp_tsnmap_has_gap(map)) अणु
		__u16 start = 0, end = 0;
		sctp_tsnmap_iter_init(map, &iter);
		जबतक (sctp_tsnmap_next_gap_ack(map, &iter,
						&start,
						&end)) अणु

			gअसल[ngaps].start = htons(start);
			gअसल[ngaps].end = htons(end);
			ngaps++;
			अगर (ngaps >= SCTP_MAX_GABS)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस ngaps;
पूर्ण

अटल पूर्णांक sctp_tsnmap_grow(काष्ठा sctp_tsnmap *map, u16 size)
अणु
	अचिन्हित दीर्घ *new;
	अचिन्हित दीर्घ inc;
	u16  len;

	अगर (size > SCTP_TSN_MAP_SIZE)
		वापस 0;

	inc = ALIGN((size - map->len), BITS_PER_LONG) + SCTP_TSN_MAP_INCREMENT;
	len = min_t(u16, map->len + inc, SCTP_TSN_MAP_SIZE);

	new = kzalloc(len>>3, GFP_ATOMIC);
	अगर (!new)
		वापस 0;

	biपंचांगap_copy(new, map->tsn_map,
		map->max_tsn_seen - map->cumulative_tsn_ack_poपूर्णांक);
	kमुक्त(map->tsn_map);
	map->tsn_map = new;
	map->len = len;

	वापस 1;
पूर्ण
