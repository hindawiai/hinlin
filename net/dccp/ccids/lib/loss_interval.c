<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) 2007   The University of Aberdeen, Scotland, UK
 *  Copyright (c) 2005-7 The University of Waikato, Hamilton, New Zealand.
 *  Copyright (c) 2005-7 Ian McDonald <ian.mcकरोnald@jandi.co.nz>
 *  Copyright (c) 2005 Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 */
#समावेश <net/sock.h>
#समावेश "tfrc.h"

अटल काष्ठा kmem_cache  *tfrc_lh_slab  __पढ़ो_mostly;
/* Loss Interval weights from [RFC 3448, 5.4], scaled by 10 */
अटल स्थिर पूर्णांक tfrc_lh_weights[NINTERVAL] = अणु 10, 10, 10, 10, 8, 6, 4, 2 पूर्ण;

/* implements LIFO semantics on the array */
अटल अंतरभूत u8 LIH_INDEX(स्थिर u8 ctr)
अणु
	वापस LIH_SIZE - 1 - (ctr % LIH_SIZE);
पूर्ण

/* the `counter' index always poपूर्णांकs at the next entry to be populated */
अटल अंतरभूत काष्ठा tfrc_loss_पूर्णांकerval *tfrc_lh_peek(काष्ठा tfrc_loss_hist *lh)
अणु
	वापस lh->counter ? lh->ring[LIH_INDEX(lh->counter - 1)] : शून्य;
पूर्ण

/* given i with 0 <= i <= k, वापस I_i as per the rfc3448bis notation */
अटल अंतरभूत u32 tfrc_lh_get_पूर्णांकerval(काष्ठा tfrc_loss_hist *lh, स्थिर u8 i)
अणु
	BUG_ON(i >= lh->counter);
	वापस lh->ring[LIH_INDEX(lh->counter - i - 1)]->li_length;
पूर्ण

/*
 *	On-demand allocation and de-allocation of entries
 */
अटल काष्ठा tfrc_loss_पूर्णांकerval *tfrc_lh_demand_next(काष्ठा tfrc_loss_hist *lh)
अणु
	अगर (lh->ring[LIH_INDEX(lh->counter)] == शून्य)
		lh->ring[LIH_INDEX(lh->counter)] = kmem_cache_alloc(tfrc_lh_slab,
								    GFP_ATOMIC);
	वापस lh->ring[LIH_INDEX(lh->counter)];
पूर्ण

व्योम tfrc_lh_cleanup(काष्ठा tfrc_loss_hist *lh)
अणु
	अगर (!tfrc_lh_is_initialised(lh))
		वापस;

	क्रम (lh->counter = 0; lh->counter < LIH_SIZE; lh->counter++)
		अगर (lh->ring[LIH_INDEX(lh->counter)] != शून्य) अणु
			kmem_cache_मुक्त(tfrc_lh_slab,
					lh->ring[LIH_INDEX(lh->counter)]);
			lh->ring[LIH_INDEX(lh->counter)] = शून्य;
		पूर्ण
पूर्ण

अटल व्योम tfrc_lh_calc_i_mean(काष्ठा tfrc_loss_hist *lh)
अणु
	u32 i_i, i_tot0 = 0, i_tot1 = 0, w_tot = 0;
	पूर्णांक i, k = tfrc_lh_length(lh) - 1; /* k is as in rfc3448bis, 5.4 */

	अगर (k <= 0)
		वापस;

	क्रम (i = 0; i <= k; i++) अणु
		i_i = tfrc_lh_get_पूर्णांकerval(lh, i);

		अगर (i < k) अणु
			i_tot0 += i_i * tfrc_lh_weights[i];
			w_tot  += tfrc_lh_weights[i];
		पूर्ण
		अगर (i > 0)
			i_tot1 += i_i * tfrc_lh_weights[i-1];
	पूर्ण

	lh->i_mean = max(i_tot0, i_tot1) / w_tot;
पूर्ण

/**
 * tfrc_lh_update_i_mean  -  Update the `खोलो' loss पूर्णांकerval I_0
 * @lh: histogram to update
 * @skb: received socket triggering loss पूर्णांकerval update
 *
 * For recomputing p: वापसs `true' अगर p > p_prev  <=>  1/p < 1/p_prev
 */
u8 tfrc_lh_update_i_mean(काष्ठा tfrc_loss_hist *lh, काष्ठा sk_buff *skb)
अणु
	काष्ठा tfrc_loss_पूर्णांकerval *cur = tfrc_lh_peek(lh);
	u32 old_i_mean = lh->i_mean;
	s64 len;

	अगर (cur == शून्य)			/* not initialised */
		वापस 0;

	len = dccp_delta_seqno(cur->li_seqno, DCCP_SKB_CB(skb)->dccpd_seq) + 1;

	अगर (len - (s64)cur->li_length <= 0)	/* duplicate or reordered */
		वापस 0;

	अगर (SUB16(dccp_hdr(skb)->dccph_ccval, cur->li_ccval) > 4)
		/*
		 * Implements RFC 4342, 10.2:
		 * If a packet S (skb) exists whose seqno comes `after' the one
		 * starting the current loss पूर्णांकerval (cur) and अगर the modulo-16
		 * distance from C(cur) to C(S) is greater than 4, consider all
		 * subsequent packets as beदीर्घing to a new loss पूर्णांकerval. This
		 * test is necessary since CCVal may wrap between पूर्णांकervals.
		 */
		cur->li_is_बंदd = 1;

	अगर (tfrc_lh_length(lh) == 1)		/* due to RFC 3448, 6.3.1 */
		वापस 0;

	cur->li_length = len;
	tfrc_lh_calc_i_mean(lh);

	वापस lh->i_mean < old_i_mean;
पूर्ण

/* Determine अगर `new_loss' करोes begin a new loss पूर्णांकerval [RFC 4342, 10.2] */
अटल अंतरभूत u8 tfrc_lh_is_new_loss(काष्ठा tfrc_loss_पूर्णांकerval *cur,
				     काष्ठा tfrc_rx_hist_entry *new_loss)
अणु
	वापस	dccp_delta_seqno(cur->li_seqno, new_loss->tfrchrx_seqno) > 0 &&
		(cur->li_is_बंदd || SUB16(new_loss->tfrchrx_ccval, cur->li_ccval) > 4);
पूर्ण

/**
 * tfrc_lh_पूर्णांकerval_add  -  Insert new record पूर्णांकo the Loss Interval database
 * @lh:		   Loss Interval database
 * @rh:		   Receive history containing a fresh loss event
 * @calc_first_li: Caller-dependent routine to compute length of first पूर्णांकerval
 * @sk:		   Used by @calc_first_li in caller-specअगरic way (subtyping)
 *
 * Updates I_mean and वापसs 1 अगर a new पूर्णांकerval has in fact been added to @lh.
 */
पूर्णांक tfrc_lh_पूर्णांकerval_add(काष्ठा tfrc_loss_hist *lh, काष्ठा tfrc_rx_hist *rh,
			 u32 (*calc_first_li)(काष्ठा sock *), काष्ठा sock *sk)
अणु
	काष्ठा tfrc_loss_पूर्णांकerval *cur = tfrc_lh_peek(lh), *new;

	अगर (cur != शून्य && !tfrc_lh_is_new_loss(cur, tfrc_rx_hist_loss_prev(rh)))
		वापस 0;

	new = tfrc_lh_demand_next(lh);
	अगर (unlikely(new == शून्य)) अणु
		DCCP_CRIT("Cannot allocate/add loss record.");
		वापस 0;
	पूर्ण

	new->li_seqno	  = tfrc_rx_hist_loss_prev(rh)->tfrchrx_seqno;
	new->li_ccval	  = tfrc_rx_hist_loss_prev(rh)->tfrchrx_ccval;
	new->li_is_बंदd = 0;

	अगर (++lh->counter == 1)
		lh->i_mean = new->li_length = (*calc_first_li)(sk);
	अन्यथा अणु
		cur->li_length = dccp_delta_seqno(cur->li_seqno, new->li_seqno);
		new->li_length = dccp_delta_seqno(new->li_seqno,
				  tfrc_rx_hist_last_rcv(rh)->tfrchrx_seqno) + 1;
		अगर (lh->counter > (2*LIH_SIZE))
			lh->counter -= LIH_SIZE;

		tfrc_lh_calc_i_mean(lh);
	पूर्ण
	वापस 1;
पूर्ण

पूर्णांक __init tfrc_li_init(व्योम)
अणु
	tfrc_lh_slab = kmem_cache_create("tfrc_li_hist",
					 माप(काष्ठा tfrc_loss_पूर्णांकerval), 0,
					 SLAB_HWCACHE_ALIGN, शून्य);
	वापस tfrc_lh_slab == शून्य ? -ENOBUFS : 0;
पूर्ण

व्योम tfrc_li_निकास(व्योम)
अणु
	अगर (tfrc_lh_slab != शून्य) अणु
		kmem_cache_destroy(tfrc_lh_slab);
		tfrc_lh_slab = शून्य;
	पूर्ण
पूर्ण
