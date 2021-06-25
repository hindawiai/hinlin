<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* SCTP kernel implementation
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 * Copyright (c) 2001 Intel Corp.
 *
 * This file is part of the SCTP kernel implementation
 *
 * These are the definitions needed क्रम the tsnmap type.  The tsnmap is used
 * to track out of order TSNs received.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *   Jon Grimm             <jgrimm@us.ibm.com>
 *   La Monte H.P. Yarroll <piggy@acm.org>
 *   Karl Knutson          <karl@athena.chicago.il.us>
 *   Sridhar Samudrala     <sri@us.ibm.com>
 */
#समावेश <net/sctp/स्थिरants.h>

#अगर_अघोषित __sctp_tsnmap_h__
#घोषणा __sctp_tsnmap_h__

/* RFC 2960 12.2 Parameters necessary per association (i.e. the TCB)
 * Mapping  An array of bits or bytes indicating which out of
 * Array    order TSN's have been received (relative to the
 *          Last Rcvd TSN). If no gaps exist, i.e. no out of
 *          order packets have been received, this array
 *          will be set to all zero. This काष्ठाure may be
 *          in the क्रमm of a circular buffer or bit array.
 */
काष्ठा sctp_tsnmap अणु
	/* This array counts the number of chunks with each TSN.
	 * It poपूर्णांकs at one of the two buffers with which we will
	 * ping-pong between.
	 */
	अचिन्हित दीर्घ *tsn_map;

	/* This is the TSN at tsn_map[0].  */
	__u32 base_tsn;

	/* Last Rcvd   : This is the last TSN received in
	 * TSN	       : sequence. This value is set initially by
	 *             : taking the peer's Initial TSN, received in
	 *             : the INIT or INIT ACK chunk, and subtracting
	 *             : one from it.
	 *
	 * Throughout most of the specअगरication this is called the
	 * "Cumulative TSN ACK Point".  In this हाल, we
	 * ignore the advice in 12.2 in favour of the term
	 * used in the bulk of the text.
	 */
	__u32 cumulative_tsn_ack_poपूर्णांक;

	/* This is the highest TSN we've marked.  */
	__u32 max_tsn_seen;

	/* This is the minimum number of TSNs we can track.  This corresponds
	 * to the size of tsn_map.   Note: the overflow_map allows us to
	 * potentially track more than this quantity.
	 */
	__u16 len;

	/* Data chunks pending receipt. used by SCTP_STATUS sockopt */
	__u16 pending_data;

	/* Record duplicate TSNs here.  We clear this after
	 * every SACK.  Store up to SCTP_MAX_DUP_TSNS worth of
	 * inक्रमmation.
	 */
	__u16 num_dup_tsns;
	__be32 dup_tsns[SCTP_MAX_DUP_TSNS];
पूर्ण;

काष्ठा sctp_tsnmap_iter अणु
	__u32 start;
पूर्ण;

/* Initialize a block of memory as a tsnmap.  */
काष्ठा sctp_tsnmap *sctp_tsnmap_init(काष्ठा sctp_tsnmap *, __u16 len,
				     __u32 initial_tsn, gfp_t gfp);

व्योम sctp_tsnmap_मुक्त(काष्ठा sctp_tsnmap *map);

/* Test the tracking state of this TSN.
 * Returns:
 *   0 अगर the TSN has not yet been seen
 *  >0 अगर the TSN has been seen (duplicate)
 *  <0 अगर the TSN is invalid (too large to track)
 */
पूर्णांक sctp_tsnmap_check(स्थिर काष्ठा sctp_tsnmap *, __u32 tsn);

/* Mark this TSN as seen.  */
पूर्णांक sctp_tsnmap_mark(काष्ठा sctp_tsnmap *, __u32 tsn,
		     काष्ठा sctp_transport *trans);

/* Mark this TSN and all lower as seen. */
व्योम sctp_tsnmap_skip(काष्ठा sctp_tsnmap *map, __u32 tsn);

/* Retrieve the Cumulative TSN ACK Poपूर्णांक.  */
अटल अंतरभूत __u32 sctp_tsnmap_get_ctsn(स्थिर काष्ठा sctp_tsnmap *map)
अणु
	वापस map->cumulative_tsn_ack_poपूर्णांक;
पूर्ण

/* Retrieve the highest TSN we've seen.  */
अटल अंतरभूत __u32 sctp_tsnmap_get_max_tsn_seen(स्थिर काष्ठा sctp_tsnmap *map)
अणु
	वापस map->max_tsn_seen;
पूर्ण

/* How many duplicate TSNs are stored? */
अटल अंतरभूत __u16 sctp_tsnmap_num_dups(काष्ठा sctp_tsnmap *map)
अणु
	वापस map->num_dup_tsns;
पूर्ण

/* Return poपूर्णांकer to duplicate tsn array as needed by SACK. */
अटल अंतरभूत __be32 *sctp_tsnmap_get_dups(काष्ठा sctp_tsnmap *map)
अणु
	map->num_dup_tsns = 0;
	वापस map->dup_tsns;
पूर्ण

/* How many gap ack blocks करो we have recorded? */
__u16 sctp_tsnmap_num_gअसल(काष्ठा sctp_tsnmap *map,
			   काष्ठा sctp_gap_ack_block *gअसल);

/* Refresh the count on pending data. */
__u16 sctp_tsnmap_pending(काष्ठा sctp_tsnmap *map);

/* Is there a gap in the TSN map?  */
अटल अंतरभूत पूर्णांक sctp_tsnmap_has_gap(स्थिर काष्ठा sctp_tsnmap *map)
अणु
	वापस map->cumulative_tsn_ack_poपूर्णांक != map->max_tsn_seen;
पूर्ण

/* Mark a duplicate TSN.  Note:  limit the storage of duplicate TSN
 * inक्रमmation.
 */
अटल अंतरभूत व्योम sctp_tsnmap_mark_dup(काष्ठा sctp_tsnmap *map, __u32 tsn)
अणु
	अगर (map->num_dup_tsns < SCTP_MAX_DUP_TSNS)
		map->dup_tsns[map->num_dup_tsns++] = htonl(tsn);
पूर्ण

/* Renege a TSN that was seen.  */
व्योम sctp_tsnmap_renege(काष्ठा sctp_tsnmap *, __u32 tsn);

/* Is there a gap in the TSN map? */
पूर्णांक sctp_tsnmap_has_gap(स्थिर काष्ठा sctp_tsnmap *);

#पूर्ण_अगर /* __sctp_tsnmap_h__ */
