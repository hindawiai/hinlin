<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2007   The University of Aberdeen, Scotland, UK
 *  Copyright (c) 2005-7 The University of Waikato, Hamilton, New Zealand.
 *
 *  An implementation of the DCCP protocol
 *
 *  This code has been developed by the University of Waikato WAND
 *  research group. For further inक्रमmation please see https://www.wand.net.nz/
 *  or e-mail Ian McDonald - ian.mcकरोnald@jandi.co.nz
 *
 *  This code also uses code from Lulea University, rereleased as GPL by its
 *  authors:
 *  Copyright (c) 2003 Nils-Erik Mattsson, Joacim Haggmark, Magnus Erixzon
 *
 *  Changes to meet Linux coding standards, to make it meet latest ccid3 draft
 *  and to make it work as a loadable module in the DCCP stack written by
 *  Arnalकरो Carvalho de Melo <acme@conectiva.com.br>.
 *
 *  Copyright (c) 2005 Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 */

#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश "packet_history.h"
#समावेश "../../dccp.h"

/*
 * Transmitter History Routines
 */
अटल काष्ठा kmem_cache *tfrc_tx_hist_slab;

पूर्णांक __init tfrc_tx_packet_history_init(व्योम)
अणु
	tfrc_tx_hist_slab = kmem_cache_create("tfrc_tx_hist",
					      माप(काष्ठा tfrc_tx_hist_entry),
					      0, SLAB_HWCACHE_ALIGN, शून्य);
	वापस tfrc_tx_hist_slab == शून्य ? -ENOBUFS : 0;
पूर्ण

व्योम tfrc_tx_packet_history_निकास(व्योम)
अणु
	अगर (tfrc_tx_hist_slab != शून्य) अणु
		kmem_cache_destroy(tfrc_tx_hist_slab);
		tfrc_tx_hist_slab = शून्य;
	पूर्ण
पूर्ण

पूर्णांक tfrc_tx_hist_add(काष्ठा tfrc_tx_hist_entry **headp, u64 seqno)
अणु
	काष्ठा tfrc_tx_hist_entry *entry = kmem_cache_alloc(tfrc_tx_hist_slab, gfp_any());

	अगर (entry == शून्य)
		वापस -ENOBUFS;
	entry->seqno = seqno;
	entry->stamp = kसमय_get_real();
	entry->next  = *headp;
	*headp	     = entry;
	वापस 0;
पूर्ण

व्योम tfrc_tx_hist_purge(काष्ठा tfrc_tx_hist_entry **headp)
अणु
	काष्ठा tfrc_tx_hist_entry *head = *headp;

	जबतक (head != शून्य) अणु
		काष्ठा tfrc_tx_hist_entry *next = head->next;

		kmem_cache_मुक्त(tfrc_tx_hist_slab, head);
		head = next;
	पूर्ण

	*headp = शून्य;
पूर्ण

/*
 *	Receiver History Routines
 */
अटल काष्ठा kmem_cache *tfrc_rx_hist_slab;

पूर्णांक __init tfrc_rx_packet_history_init(व्योम)
अणु
	tfrc_rx_hist_slab = kmem_cache_create("tfrc_rxh_cache",
					      माप(काष्ठा tfrc_rx_hist_entry),
					      0, SLAB_HWCACHE_ALIGN, शून्य);
	वापस tfrc_rx_hist_slab == शून्य ? -ENOBUFS : 0;
पूर्ण

व्योम tfrc_rx_packet_history_निकास(व्योम)
अणु
	अगर (tfrc_rx_hist_slab != शून्य) अणु
		kmem_cache_destroy(tfrc_rx_hist_slab);
		tfrc_rx_hist_slab = शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम tfrc_rx_hist_entry_from_skb(काष्ठा tfrc_rx_hist_entry *entry,
					       स्थिर काष्ठा sk_buff *skb,
					       स्थिर u64 ndp)
अणु
	स्थिर काष्ठा dccp_hdr *dh = dccp_hdr(skb);

	entry->tfrchrx_seqno = DCCP_SKB_CB(skb)->dccpd_seq;
	entry->tfrchrx_ccval = dh->dccph_ccval;
	entry->tfrchrx_type  = dh->dccph_type;
	entry->tfrchrx_ndp   = ndp;
	entry->tfrchrx_tstamp = kसमय_get_real();
पूर्ण

व्योम tfrc_rx_hist_add_packet(काष्ठा tfrc_rx_hist *h,
			     स्थिर काष्ठा sk_buff *skb,
			     स्थिर u64 ndp)
अणु
	काष्ठा tfrc_rx_hist_entry *entry = tfrc_rx_hist_last_rcv(h);

	tfrc_rx_hist_entry_from_skb(entry, skb, ndp);
पूर्ण

/* has the packet contained in skb been seen beक्रमe? */
पूर्णांक tfrc_rx_hist_duplicate(काष्ठा tfrc_rx_hist *h, काष्ठा sk_buff *skb)
अणु
	स्थिर u64 seq = DCCP_SKB_CB(skb)->dccpd_seq;
	पूर्णांक i;

	अगर (dccp_delta_seqno(tfrc_rx_hist_loss_prev(h)->tfrchrx_seqno, seq) <= 0)
		वापस 1;

	क्रम (i = 1; i <= h->loss_count; i++)
		अगर (tfrc_rx_hist_entry(h, i)->tfrchrx_seqno == seq)
			वापस 1;

	वापस 0;
पूर्ण

अटल व्योम tfrc_rx_hist_swap(काष्ठा tfrc_rx_hist *h, स्थिर u8 a, स्थिर u8 b)
अणु
	स्थिर u8 idx_a = tfrc_rx_hist_index(h, a),
		 idx_b = tfrc_rx_hist_index(h, b);

	swap(h->ring[idx_a], h->ring[idx_b]);
पूर्ण

/*
 * Private helper functions क्रम loss detection.
 *
 * In the descriptions, `Si' refers to the sequence number of entry number i,
 * whose NDP count is `Ni' (lower हाल is used क्रम variables).
 * Note: All __xxx_loss functions expect that a test against duplicates has been
 *       perक्रमmed alपढ़ोy: the seqno of the skb must not be less than the seqno
 *       of loss_prev; and it must not equal that of any valid history entry.
 */
अटल व्योम __करो_track_loss(काष्ठा tfrc_rx_hist *h, काष्ठा sk_buff *skb, u64 n1)
अणु
	u64 s0 = tfrc_rx_hist_loss_prev(h)->tfrchrx_seqno,
	    s1 = DCCP_SKB_CB(skb)->dccpd_seq;

	अगर (!dccp_loss_मुक्त(s0, s1, n1)) अणु	/* gap between S0 and S1 */
		h->loss_count = 1;
		tfrc_rx_hist_entry_from_skb(tfrc_rx_hist_entry(h, 1), skb, n1);
	पूर्ण
पूर्ण

अटल व्योम __one_after_loss(काष्ठा tfrc_rx_hist *h, काष्ठा sk_buff *skb, u32 n2)
अणु
	u64 s0 = tfrc_rx_hist_loss_prev(h)->tfrchrx_seqno,
	    s1 = tfrc_rx_hist_entry(h, 1)->tfrchrx_seqno,
	    s2 = DCCP_SKB_CB(skb)->dccpd_seq;

	अगर (likely(dccp_delta_seqno(s1, s2) > 0)) अणु	/* S1  <  S2 */
		h->loss_count = 2;
		tfrc_rx_hist_entry_from_skb(tfrc_rx_hist_entry(h, 2), skb, n2);
		वापस;
	पूर्ण

	/* S0  <  S2  <  S1 */

	अगर (dccp_loss_मुक्त(s0, s2, n2)) अणु
		u64 n1 = tfrc_rx_hist_entry(h, 1)->tfrchrx_ndp;

		अगर (dccp_loss_मुक्त(s2, s1, n1)) अणु
			/* hole is filled: S0, S2, and S1 are consecutive */
			h->loss_count = 0;
			h->loss_start = tfrc_rx_hist_index(h, 1);
		पूर्ण अन्यथा
			/* gap between S2 and S1: just update loss_prev */
			tfrc_rx_hist_entry_from_skb(tfrc_rx_hist_loss_prev(h), skb, n2);

	पूर्ण अन्यथा अणु	/* gap between S0 and S2 */
		/*
		 * Reorder history to insert S2 between S0 and S1
		 */
		tfrc_rx_hist_swap(h, 0, 3);
		h->loss_start = tfrc_rx_hist_index(h, 3);
		tfrc_rx_hist_entry_from_skb(tfrc_rx_hist_entry(h, 1), skb, n2);
		h->loss_count = 2;
	पूर्ण
पूर्ण

/* वापस 1 अगर a new loss event has been identअगरied */
अटल पूर्णांक __two_after_loss(काष्ठा tfrc_rx_hist *h, काष्ठा sk_buff *skb, u32 n3)
अणु
	u64 s0 = tfrc_rx_hist_loss_prev(h)->tfrchrx_seqno,
	    s1 = tfrc_rx_hist_entry(h, 1)->tfrchrx_seqno,
	    s2 = tfrc_rx_hist_entry(h, 2)->tfrchrx_seqno,
	    s3 = DCCP_SKB_CB(skb)->dccpd_seq;

	अगर (likely(dccp_delta_seqno(s2, s3) > 0)) अणु	/* S2  <  S3 */
		h->loss_count = 3;
		tfrc_rx_hist_entry_from_skb(tfrc_rx_hist_entry(h, 3), skb, n3);
		वापस 1;
	पूर्ण

	/* S3  <  S2 */

	अगर (dccp_delta_seqno(s1, s3) > 0) अणु		/* S1  <  S3  <  S2 */
		/*
		 * Reorder history to insert S3 between S1 and S2
		 */
		tfrc_rx_hist_swap(h, 2, 3);
		tfrc_rx_hist_entry_from_skb(tfrc_rx_hist_entry(h, 2), skb, n3);
		h->loss_count = 3;
		वापस 1;
	पूर्ण

	/* S0  <  S3  <  S1 */

	अगर (dccp_loss_मुक्त(s0, s3, n3)) अणु
		u64 n1 = tfrc_rx_hist_entry(h, 1)->tfrchrx_ndp;

		अगर (dccp_loss_मुक्त(s3, s1, n1)) अणु
			/* hole between S0 and S1 filled by S3 */
			u64 n2 = tfrc_rx_hist_entry(h, 2)->tfrchrx_ndp;

			अगर (dccp_loss_मुक्त(s1, s2, n2)) अणु
				/* entire hole filled by S0, S3, S1, S2 */
				h->loss_start = tfrc_rx_hist_index(h, 2);
				h->loss_count = 0;
			पूर्ण अन्यथा अणु
				/* gap reमुख्यs between S1 and S2 */
				h->loss_start = tfrc_rx_hist_index(h, 1);
				h->loss_count = 1;
			पूर्ण

		पूर्ण अन्यथा /* gap exists between S3 and S1, loss_count stays at 2 */
			tfrc_rx_hist_entry_from_skb(tfrc_rx_hist_loss_prev(h), skb, n3);

		वापस 0;
	पूर्ण

	/*
	 * The reमुख्यing हाल:  S0  <  S3  <  S1  <  S2;  gap between S0 and S3
	 * Reorder history to insert S3 between S0 and S1.
	 */
	tfrc_rx_hist_swap(h, 0, 3);
	h->loss_start = tfrc_rx_hist_index(h, 3);
	tfrc_rx_hist_entry_from_skb(tfrc_rx_hist_entry(h, 1), skb, n3);
	h->loss_count = 3;

	वापस 1;
पूर्ण

/* recycle RX history records to जारी loss detection अगर necessary */
अटल व्योम __three_after_loss(काष्ठा tfrc_rx_hist *h)
अणु
	/*
	 * At this stage we know alपढ़ोy that there is a gap between S0 and S1
	 * (since S0 was the highest sequence number received beक्रमe detecting
	 * the loss). To recycle the loss record, it is	thus only necessary to
	 * check क्रम other possible gaps between S1/S2 and between S2/S3.
	 */
	u64 s1 = tfrc_rx_hist_entry(h, 1)->tfrchrx_seqno,
	    s2 = tfrc_rx_hist_entry(h, 2)->tfrchrx_seqno,
	    s3 = tfrc_rx_hist_entry(h, 3)->tfrchrx_seqno;
	u64 n2 = tfrc_rx_hist_entry(h, 2)->tfrchrx_ndp,
	    n3 = tfrc_rx_hist_entry(h, 3)->tfrchrx_ndp;

	अगर (dccp_loss_मुक्त(s1, s2, n2)) अणु

		अगर (dccp_loss_मुक्त(s2, s3, n3)) अणु
			/* no gap between S2 and S3: entire hole is filled */
			h->loss_start = tfrc_rx_hist_index(h, 3);
			h->loss_count = 0;
		पूर्ण अन्यथा अणु
			/* gap between S2 and S3 */
			h->loss_start = tfrc_rx_hist_index(h, 2);
			h->loss_count = 1;
		पूर्ण

	पूर्ण अन्यथा अणु	/* gap between S1 and S2 */
		h->loss_start = tfrc_rx_hist_index(h, 1);
		h->loss_count = 2;
	पूर्ण
पूर्ण

/**
 *  tfrc_rx_handle_loss  -  Loss detection and further processing
 *  @h:		    The non-empty RX history object
 *  @lh:	    Loss Intervals database to update
 *  @skb:	    Currently received packet
 *  @ndp:	    The NDP count beदीर्घing to @skb
 *  @calc_first_li: Caller-dependent computation of first loss पूर्णांकerval in @lh
 *  @sk:	    Used by @calc_first_li (see tfrc_lh_पूर्णांकerval_add)
 *
 *  Chooses action according to pending loss, updates LI database when a new
 *  loss was detected, and करोes required post-processing. Returns 1 when caller
 *  should send feedback, 0 otherwise.
 *  Since it also takes care of reordering during loss detection and updates the
 *  records accordingly, the caller should not perक्रमm any more RX history
 *  operations when loss_count is greater than 0 after calling this function.
 */
पूर्णांक tfrc_rx_handle_loss(काष्ठा tfrc_rx_hist *h,
			काष्ठा tfrc_loss_hist *lh,
			काष्ठा sk_buff *skb, स्थिर u64 ndp,
			u32 (*calc_first_li)(काष्ठा sock *), काष्ठा sock *sk)
अणु
	पूर्णांक is_new_loss = 0;

	अगर (h->loss_count == 0) अणु
		__करो_track_loss(h, skb, ndp);
	पूर्ण अन्यथा अगर (h->loss_count == 1) अणु
		__one_after_loss(h, skb, ndp);
	पूर्ण अन्यथा अगर (h->loss_count != 2) अणु
		DCCP_BUG("invalid loss_count %d", h->loss_count);
	पूर्ण अन्यथा अगर (__two_after_loss(h, skb, ndp)) अणु
		/*
		 * Update Loss Interval database and recycle RX records
		 */
		is_new_loss = tfrc_lh_पूर्णांकerval_add(lh, h, calc_first_li, sk);
		__three_after_loss(h);
	पूर्ण
	वापस is_new_loss;
पूर्ण

पूर्णांक tfrc_rx_hist_alloc(काष्ठा tfrc_rx_hist *h)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= TFRC_NDUPACK; i++) अणु
		h->ring[i] = kmem_cache_alloc(tfrc_rx_hist_slab, GFP_ATOMIC);
		अगर (h->ring[i] == शून्य)
			जाओ out_मुक्त;
	पूर्ण

	h->loss_count = h->loss_start = 0;
	वापस 0;

out_मुक्त:
	जबतक (i-- != 0) अणु
		kmem_cache_मुक्त(tfrc_rx_hist_slab, h->ring[i]);
		h->ring[i] = शून्य;
	पूर्ण
	वापस -ENOBUFS;
पूर्ण

व्योम tfrc_rx_hist_purge(काष्ठा tfrc_rx_hist *h)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= TFRC_NDUPACK; ++i)
		अगर (h->ring[i] != शून्य) अणु
			kmem_cache_मुक्त(tfrc_rx_hist_slab, h->ring[i]);
			h->ring[i] = शून्य;
		पूर्ण
पूर्ण

/**
 * tfrc_rx_hist_rtt_last_s - reference entry to compute RTT samples against
 * @h:	The non-empty RX history object
 */
अटल अंतरभूत काष्ठा tfrc_rx_hist_entry *
			tfrc_rx_hist_rtt_last_s(स्थिर काष्ठा tfrc_rx_hist *h)
अणु
	वापस h->ring[0];
पूर्ण

/**
 * tfrc_rx_hist_rtt_prev_s - previously suitable (wrt rtt_last_s) RTT-sampling entry
 * @h:	The non-empty RX history object
 */
अटल अंतरभूत काष्ठा tfrc_rx_hist_entry *
			tfrc_rx_hist_rtt_prev_s(स्थिर काष्ठा tfrc_rx_hist *h)
अणु
	वापस h->ring[h->rtt_sample_prev];
पूर्ण

/**
 * tfrc_rx_hist_sample_rtt  -  Sample RTT from बारtamp / CCVal
 * @h: receive histogram
 * @skb: packet containing बारtamp.
 *
 * Based on ideas presented in RFC 4342, 8.1. Returns 0 अगर it was not able
 * to compute a sample with given data - calling function should check this.
 */
u32 tfrc_rx_hist_sample_rtt(काष्ठा tfrc_rx_hist *h, स्थिर काष्ठा sk_buff *skb)
अणु
	u32 sample = 0,
	    delta_v = SUB16(dccp_hdr(skb)->dccph_ccval,
			    tfrc_rx_hist_rtt_last_s(h)->tfrchrx_ccval);

	अगर (delta_v < 1 || delta_v > 4) अणु	/* unsuitable CCVal delta */
		अगर (h->rtt_sample_prev == 2) अणु	/* previous candidate stored */
			sample = SUB16(tfrc_rx_hist_rtt_prev_s(h)->tfrchrx_ccval,
				       tfrc_rx_hist_rtt_last_s(h)->tfrchrx_ccval);
			अगर (sample)
				sample = 4 / sample *
				         kसमय_us_delta(tfrc_rx_hist_rtt_prev_s(h)->tfrchrx_tstamp,
							tfrc_rx_hist_rtt_last_s(h)->tfrchrx_tstamp);
			अन्यथा    /*
				 * FIXME: This condition is in principle not
				 * possible but occurs when CCID is used क्रम
				 * two-way data traffic. I have tried to trace
				 * it, but the cause करोes not seem to be here.
				 */
				DCCP_BUG("please report to dccp@vger.kernel.org"
					 " => prev = %u, last = %u",
					 tfrc_rx_hist_rtt_prev_s(h)->tfrchrx_ccval,
					 tfrc_rx_hist_rtt_last_s(h)->tfrchrx_ccval);
		पूर्ण अन्यथा अगर (delta_v < 1) अणु
			h->rtt_sample_prev = 1;
			जाओ keep_ref_क्रम_next_समय;
		पूर्ण

	पूर्ण अन्यथा अगर (delta_v == 4) /* optimal match */
		sample = kसमय_प्रकारo_us(net_समयdelta(tfrc_rx_hist_rtt_last_s(h)->tfrchrx_tstamp));
	अन्यथा अणु			 /* suboptimal match */
		h->rtt_sample_prev = 2;
		जाओ keep_ref_क्रम_next_समय;
	पूर्ण

	अगर (unlikely(sample > DCCP_SANE_RTT_MAX)) अणु
		DCCP_WARN("RTT sample %u too large, using max\n", sample);
		sample = DCCP_SANE_RTT_MAX;
	पूर्ण

	h->rtt_sample_prev = 0;	       /* use current entry as next reference */
keep_ref_क्रम_next_समय:

	वापस sample;
पूर्ण
