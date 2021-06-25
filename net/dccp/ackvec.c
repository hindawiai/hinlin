<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  net/dccp/ackvec.c
 *
 *  An implementation of Ack Vectors क्रम the DCCP protocol
 *  Copyright (c) 2007 University of Aberdeen, Scotland, UK
 *  Copyright (c) 2005 Arnalकरो Carvalho de Melo <acme@ghostprotocols.net>
 */
#समावेश "dccp.h"
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>

अटल काष्ठा kmem_cache *dccp_ackvec_slab;
अटल काष्ठा kmem_cache *dccp_ackvec_record_slab;

काष्ठा dccp_ackvec *dccp_ackvec_alloc(स्थिर gfp_t priority)
अणु
	काष्ठा dccp_ackvec *av = kmem_cache_zalloc(dccp_ackvec_slab, priority);

	अगर (av != शून्य) अणु
		av->av_buf_head	= av->av_buf_tail = DCCPAV_MAX_ACKVEC_LEN - 1;
		INIT_LIST_HEAD(&av->av_records);
	पूर्ण
	वापस av;
पूर्ण

अटल व्योम dccp_ackvec_purge_records(काष्ठा dccp_ackvec *av)
अणु
	काष्ठा dccp_ackvec_record *cur, *next;

	list_क्रम_each_entry_safe(cur, next, &av->av_records, avr_node)
		kmem_cache_मुक्त(dccp_ackvec_record_slab, cur);
	INIT_LIST_HEAD(&av->av_records);
पूर्ण

व्योम dccp_ackvec_मुक्त(काष्ठा dccp_ackvec *av)
अणु
	अगर (likely(av != शून्य)) अणु
		dccp_ackvec_purge_records(av);
		kmem_cache_मुक्त(dccp_ackvec_slab, av);
	पूर्ण
पूर्ण

/**
 * dccp_ackvec_update_records  -  Record inक्रमmation about sent Ack Vectors
 * @av:		Ack Vector records to update
 * @seqno:	Sequence number of the packet carrying the Ack Vector just sent
 * @nonce_sum:	The sum of all buffer nonces contained in the Ack Vector
 */
पूर्णांक dccp_ackvec_update_records(काष्ठा dccp_ackvec *av, u64 seqno, u8 nonce_sum)
अणु
	काष्ठा dccp_ackvec_record *avr;

	avr = kmem_cache_alloc(dccp_ackvec_record_slab, GFP_ATOMIC);
	अगर (avr == शून्य)
		वापस -ENOBUFS;

	avr->avr_ack_seqno  = seqno;
	avr->avr_ack_ptr    = av->av_buf_head;
	avr->avr_ack_ackno  = av->av_buf_ackno;
	avr->avr_ack_nonce  = nonce_sum;
	avr->avr_ack_runlen = dccp_ackvec_runlen(av->av_buf + av->av_buf_head);
	/*
	 * When the buffer overflows, we keep no more than one record. This is
	 * the simplest way of disambiguating sender-Acks dating from beक्रमe the
	 * overflow from sender-Acks which refer to after the overflow; a simple
	 * solution is preferable here since we are handling an exception.
	 */
	अगर (av->av_overflow)
		dccp_ackvec_purge_records(av);
	/*
	 * Since GSS is incremented क्रम each packet, the list is स्वतःmatically
	 * arranged in descending order of @ack_seqno.
	 */
	list_add(&avr->avr_node, &av->av_records);

	dccp_pr_debug("Added Vector, ack_seqno=%llu, ack_ackno=%llu (rl=%u)\n",
		      (अचिन्हित दीर्घ दीर्घ)avr->avr_ack_seqno,
		      (अचिन्हित दीर्घ दीर्घ)avr->avr_ack_ackno,
		      avr->avr_ack_runlen);
	वापस 0;
पूर्ण

अटल काष्ठा dccp_ackvec_record *dccp_ackvec_lookup(काष्ठा list_head *av_list,
						     स्थिर u64 ackno)
अणु
	काष्ठा dccp_ackvec_record *avr;
	/*
	 * Exploit that records are inserted in descending order of sequence
	 * number, start with the oldest record first. If @ackno is `beक्रमe'
	 * the earliest ack_ackno, the packet is too old to be considered.
	 */
	list_क्रम_each_entry_reverse(avr, av_list, avr_node) अणु
		अगर (avr->avr_ack_seqno == ackno)
			वापस avr;
		अगर (beक्रमe48(ackno, avr->avr_ack_seqno))
			अवरोध;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Buffer index and length computation using modulo-buffersize arithmetic.
 * Note that, as poपूर्णांकers move from right to left, head is `beक्रमe' tail.
 */
अटल अंतरभूत u16 __ackvec_idx_add(स्थिर u16 a, स्थिर u16 b)
अणु
	वापस (a + b) % DCCPAV_MAX_ACKVEC_LEN;
पूर्ण

अटल अंतरभूत u16 __ackvec_idx_sub(स्थिर u16 a, स्थिर u16 b)
अणु
	वापस __ackvec_idx_add(a, DCCPAV_MAX_ACKVEC_LEN - b);
पूर्ण

u16 dccp_ackvec_buflen(स्थिर काष्ठा dccp_ackvec *av)
अणु
	अगर (unlikely(av->av_overflow))
		वापस DCCPAV_MAX_ACKVEC_LEN;
	वापस __ackvec_idx_sub(av->av_buf_tail, av->av_buf_head);
पूर्ण

/**
 * dccp_ackvec_update_old  -  Update previous state as per RFC 4340, 11.4.1
 * @av:		non-empty buffer to update
 * @distance:   negative or zero distance of @seqno from buf_ackno करोwnward
 * @seqno:	the (old) sequence number whose record is to be updated
 * @state:	state in which packet carrying @seqno was received
 */
अटल व्योम dccp_ackvec_update_old(काष्ठा dccp_ackvec *av, s64 distance,
				   u64 seqno, क्रमागत dccp_ackvec_states state)
अणु
	u16 ptr = av->av_buf_head;

	BUG_ON(distance > 0);
	अगर (unlikely(dccp_ackvec_is_empty(av)))
		वापस;

	करो अणु
		u8 runlen = dccp_ackvec_runlen(av->av_buf + ptr);

		अगर (distance + runlen >= 0) अणु
			/*
			 * Only update the state अगर packet has not been received
			 * yet. This is OK as per the second table in RFC 4340,
			 * 11.4.1; i.e. here we are using the following table:
			 *                     RECEIVED
			 *                      0   1   3
			 *              S     +---+---+---+
			 *              T   0 | 0 | 0 | 0 |
			 *              O     +---+---+---+
			 *              R   1 | 1 | 1 | 1 |
			 *              E     +---+---+---+
			 *              D   3 | 0 | 1 | 3 |
			 *                    +---+---+---+
			 * The "Not Received" state was set by reserve_seats().
			 */
			अगर (av->av_buf[ptr] == DCCPAV_NOT_RECEIVED)
				av->av_buf[ptr] = state;
			अन्यथा
				dccp_pr_debug("Not changing %llu state to %u\n",
					      (अचिन्हित दीर्घ दीर्घ)seqno, state);
			अवरोध;
		पूर्ण

		distance += runlen + 1;
		ptr	  = __ackvec_idx_add(ptr, 1);

	पूर्ण जबतक (ptr != av->av_buf_tail);
पूर्ण

/* Mark @num entries after buf_head as "Not yet received". */
अटल व्योम dccp_ackvec_reserve_seats(काष्ठा dccp_ackvec *av, u16 num)
अणु
	u16 start = __ackvec_idx_add(av->av_buf_head, 1),
	    len	  = DCCPAV_MAX_ACKVEC_LEN - start;

	/* check क्रम buffer wrap-around */
	अगर (num > len) अणु
		स_रखो(av->av_buf + start, DCCPAV_NOT_RECEIVED, len);
		start = 0;
		num  -= len;
	पूर्ण
	अगर (num)
		स_रखो(av->av_buf + start, DCCPAV_NOT_RECEIVED, num);
पूर्ण

/**
 * dccp_ackvec_add_new  -  Record one or more new entries in Ack Vector buffer
 * @av:		 container of buffer to update (can be empty or non-empty)
 * @num_packets: number of packets to रेजिस्टर (must be >= 1)
 * @seqno:	 sequence number of the first packet in @num_packets
 * @state:	 state in which packet carrying @seqno was received
 */
अटल व्योम dccp_ackvec_add_new(काष्ठा dccp_ackvec *av, u32 num_packets,
				u64 seqno, क्रमागत dccp_ackvec_states state)
अणु
	u32 num_cells = num_packets;

	अगर (num_packets > DCCPAV_BURST_THRESH) अणु
		u32 lost_packets = num_packets - 1;

		DCCP_WARN("Warning: large burst loss (%u)\n", lost_packets);
		/*
		 * We received 1 packet and have a loss of size "num_packets-1"
		 * which we squeeze पूर्णांकo num_cells-1 rather than reserving an
		 * entire byte क्रम each lost packet.
		 * The reason is that the vector grows in O(burst_length); when
		 * it grows too large there will no room left क्रम the payload.
		 * This is a trade-off: अगर a few packets out of the burst show
		 * up later, their state will not be changed; it is simply too
		 * costly to reshuffle/पुनः_स्मृतिate/copy the buffer each समय.
		 * Should such problems persist, we will need to चयन to a
		 * dअगरferent underlying data काष्ठाure.
		 */
		क्रम (num_packets = num_cells = 1; lost_packets; ++num_cells) अणु
			u8 len = min_t(u32, lost_packets, DCCPAV_MAX_RUNLEN);

			av->av_buf_head = __ackvec_idx_sub(av->av_buf_head, 1);
			av->av_buf[av->av_buf_head] = DCCPAV_NOT_RECEIVED | len;

			lost_packets -= len;
		पूर्ण
	पूर्ण

	अगर (num_cells + dccp_ackvec_buflen(av) >= DCCPAV_MAX_ACKVEC_LEN) अणु
		DCCP_CRIT("Ack Vector buffer overflow: dropping old entries");
		av->av_overflow = true;
	पूर्ण

	av->av_buf_head = __ackvec_idx_sub(av->av_buf_head, num_packets);
	अगर (av->av_overflow)
		av->av_buf_tail = av->av_buf_head;

	av->av_buf[av->av_buf_head] = state;
	av->av_buf_ackno	    = seqno;

	अगर (num_packets > 1)
		dccp_ackvec_reserve_seats(av, num_packets - 1);
पूर्ण

/**
 * dccp_ackvec_input  -  Register incoming packet in the buffer
 * @av: Ack Vector to रेजिस्टर packet to
 * @skb: Packet to रेजिस्टर
 */
व्योम dccp_ackvec_input(काष्ठा dccp_ackvec *av, काष्ठा sk_buff *skb)
अणु
	u64 seqno = DCCP_SKB_CB(skb)->dccpd_seq;
	क्रमागत dccp_ackvec_states state = DCCPAV_RECEIVED;

	अगर (dccp_ackvec_is_empty(av)) अणु
		dccp_ackvec_add_new(av, 1, seqno, state);
		av->av_tail_ackno = seqno;

	पूर्ण अन्यथा अणु
		s64 num_packets = dccp_delta_seqno(av->av_buf_ackno, seqno);
		u8 *current_head = av->av_buf + av->av_buf_head;

		अगर (num_packets == 1 &&
		    dccp_ackvec_state(current_head) == state &&
		    dccp_ackvec_runlen(current_head) < DCCPAV_MAX_RUNLEN) अणु

			*current_head   += 1;
			av->av_buf_ackno = seqno;

		पूर्ण अन्यथा अगर (num_packets > 0) अणु
			dccp_ackvec_add_new(av, num_packets, seqno, state);
		पूर्ण अन्यथा अणु
			dccp_ackvec_update_old(av, num_packets, seqno, state);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * dccp_ackvec_clear_state  -  Perक्रमm house-keeping / garbage-collection
 * @av: Ack Vector record to clean
 * @ackno: last Ack Vector which has been acknowledged
 *
 * This routine is called when the peer acknowledges the receipt of Ack Vectors
 * up to and including @ackno. While based on section A.3 of RFC 4340, here
 * are additional precautions to prevent corrupted buffer state. In particular,
 * we use tail_ackno to identअगरy outdated records; it always marks the earliest
 * packet of group (2) in 11.4.2.
 */
व्योम dccp_ackvec_clear_state(काष्ठा dccp_ackvec *av, स्थिर u64 ackno)
अणु
	काष्ठा dccp_ackvec_record *avr, *next;
	u8 runlen_now, eff_runlen;
	s64 delta;

	avr = dccp_ackvec_lookup(&av->av_records, ackno);
	अगर (avr == शून्य)
		वापस;
	/*
	 * Deal with outdated acknowledgments: this arises when e.g. there are
	 * several old records and the acks from the peer come in slowly. In
	 * that हाल we may still have records that pre-date tail_ackno.
	 */
	delta = dccp_delta_seqno(av->av_tail_ackno, avr->avr_ack_ackno);
	अगर (delta < 0)
		जाओ मुक्त_records;
	/*
	 * Deal with overlapping Ack Vectors: करोn't subtract more than the
	 * number of packets between tail_ackno and ack_ackno.
	 */
	eff_runlen = delta < avr->avr_ack_runlen ? delta : avr->avr_ack_runlen;

	runlen_now = dccp_ackvec_runlen(av->av_buf + avr->avr_ack_ptr);
	/*
	 * The run length of Ack Vector cells करोes not decrease over समय. If
	 * the run length is the same as at the समय the Ack Vector was sent, we
	 * मुक्त the ack_ptr cell. That cell can however not be मुक्तd अगर the run
	 * length has increased: in this हाल we need to move the tail poपूर्णांकer
	 * backwards (towards higher indices), to its next-oldest neighbour.
	 */
	अगर (runlen_now > eff_runlen) अणु

		av->av_buf[avr->avr_ack_ptr] -= eff_runlen + 1;
		av->av_buf_tail = __ackvec_idx_add(avr->avr_ack_ptr, 1);

		/* This move may not have cleared the overflow flag. */
		अगर (av->av_overflow)
			av->av_overflow = (av->av_buf_head == av->av_buf_tail);
	पूर्ण अन्यथा अणु
		av->av_buf_tail	= avr->avr_ack_ptr;
		/*
		 * We have made sure that avr poपूर्णांकs to a valid cell within the
		 * buffer. This cell is either older than head, or equals head
		 * (empty buffer): in both हालs we no दीर्घer have any overflow.
		 */
		av->av_overflow	= 0;
	पूर्ण

	/*
	 * The peer has acknowledged up to and including ack_ackno. Hence the
	 * first packet in group (2) of 11.4.2 is the successor of ack_ackno.
	 */
	av->av_tail_ackno = ADD48(avr->avr_ack_ackno, 1);

मुक्त_records:
	list_क्रम_each_entry_safe_from(avr, next, &av->av_records, avr_node) अणु
		list_del(&avr->avr_node);
		kmem_cache_मुक्त(dccp_ackvec_record_slab, avr);
	पूर्ण
पूर्ण

/*
 *	Routines to keep track of Ack Vectors received in an skb
 */
पूर्णांक dccp_ackvec_parsed_add(काष्ठा list_head *head, u8 *vec, u8 len, u8 nonce)
अणु
	काष्ठा dccp_ackvec_parsed *new = kदो_स्मृति(माप(*new), GFP_ATOMIC);

	अगर (new == शून्य)
		वापस -ENOBUFS;
	new->vec   = vec;
	new->len   = len;
	new->nonce = nonce;

	list_add_tail(&new->node, head);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dccp_ackvec_parsed_add);

व्योम dccp_ackvec_parsed_cleanup(काष्ठा list_head *parsed_chunks)
अणु
	काष्ठा dccp_ackvec_parsed *cur, *next;

	list_क्रम_each_entry_safe(cur, next, parsed_chunks, node)
		kमुक्त(cur);
	INIT_LIST_HEAD(parsed_chunks);
पूर्ण
EXPORT_SYMBOL_GPL(dccp_ackvec_parsed_cleanup);

पूर्णांक __init dccp_ackvec_init(व्योम)
अणु
	dccp_ackvec_slab = kmem_cache_create("dccp_ackvec",
					     माप(काष्ठा dccp_ackvec), 0,
					     SLAB_HWCACHE_ALIGN, शून्य);
	अगर (dccp_ackvec_slab == शून्य)
		जाओ out_err;

	dccp_ackvec_record_slab = kmem_cache_create("dccp_ackvec_record",
					     माप(काष्ठा dccp_ackvec_record),
					     0, SLAB_HWCACHE_ALIGN, शून्य);
	अगर (dccp_ackvec_record_slab == शून्य)
		जाओ out_destroy_slab;

	वापस 0;

out_destroy_slab:
	kmem_cache_destroy(dccp_ackvec_slab);
	dccp_ackvec_slab = शून्य;
out_err:
	DCCP_CRIT("Unable to create Ack Vector slab cache");
	वापस -ENOBUFS;
पूर्ण

व्योम dccp_ackvec_निकास(व्योम)
अणु
	kmem_cache_destroy(dccp_ackvec_slab);
	dccp_ackvec_slab = शून्य;
	kmem_cache_destroy(dccp_ackvec_record_slab);
	dccp_ackvec_record_slab = शून्य;
पूर्ण
