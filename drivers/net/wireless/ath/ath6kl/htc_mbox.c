<शैली गुरु>
/*
 * Copyright (c) 2007-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश "core.h"
#समावेश "hif.h"
#समावेश "debug.h"
#समावेश "hif-ops.h"
#समावेश "trace.h"

#समावेश <यंत्र/unaligned.h>

#घोषणा CALC_TXRX_PADDED_LEN(dev, len)  (__ALIGN_MASK((len), (dev)->block_mask))

अटल व्योम ath6kl_htc_mbox_cleanup(काष्ठा htc_target *target);
अटल व्योम ath6kl_htc_mbox_stop(काष्ठा htc_target *target);
अटल पूर्णांक ath6kl_htc_mbox_add_rxbuf_multiple(काष्ठा htc_target *target,
					      काष्ठा list_head *pkt_queue);
अटल व्योम ath6kl_htc_set_credit_dist(काष्ठा htc_target *target,
				       काष्ठा ath6kl_htc_credit_info *cred_info,
				       u16 svc_pri_order[], पूर्णांक len);

/* threshold to re-enable Tx bundling क्रम an AC*/
#घोषणा TX_RESUME_BUNDLE_THRESHOLD	1500

/* Functions क्रम Tx credit handling */
अटल व्योम ath6kl_credit_deposit(काष्ठा ath6kl_htc_credit_info *cred_info,
				  काष्ठा htc_endpoपूर्णांक_credit_dist *ep_dist,
				  पूर्णांक credits)
अणु
	ath6kl_dbg(ATH6KL_DBG_CREDIT, "credit deposit ep %d credits %d\n",
		   ep_dist->endpoपूर्णांक, credits);

	ep_dist->credits += credits;
	ep_dist->cred_assngd += credits;
	cred_info->cur_मुक्त_credits -= credits;
पूर्ण

अटल व्योम ath6kl_credit_init(काष्ठा ath6kl_htc_credit_info *cred_info,
			       काष्ठा list_head *ep_list,
			       पूर्णांक tot_credits)
अणु
	काष्ठा htc_endpoपूर्णांक_credit_dist *cur_ep_dist;
	पूर्णांक count;

	ath6kl_dbg(ATH6KL_DBG_CREDIT, "credit init total %d\n", tot_credits);

	cred_info->cur_मुक्त_credits = tot_credits;
	cred_info->total_avail_credits = tot_credits;

	list_क्रम_each_entry(cur_ep_dist, ep_list, list) अणु
		अगर (cur_ep_dist->endpoपूर्णांक == ENDPOINT_0)
			जारी;

		cur_ep_dist->cred_min = cur_ep_dist->cred_per_msg;

		अगर (tot_credits > 4) अणु
			अगर ((cur_ep_dist->svc_id == WMI_DATA_BK_SVC) ||
			    (cur_ep_dist->svc_id == WMI_DATA_BE_SVC)) अणु
				ath6kl_credit_deposit(cred_info,
						      cur_ep_dist,
						      cur_ep_dist->cred_min);
				cur_ep_dist->dist_flags |= HTC_EP_ACTIVE;
			पूर्ण
		पूर्ण

		अगर (cur_ep_dist->svc_id == WMI_CONTROL_SVC) अणु
			ath6kl_credit_deposit(cred_info, cur_ep_dist,
					      cur_ep_dist->cred_min);
			/*
			 * Control service is always marked active, it
			 * never goes inactive EVER.
			 */
			cur_ep_dist->dist_flags |= HTC_EP_ACTIVE;
		पूर्ण

		/*
		 * Streams have to be created (explicit | implicit) क्रम all
		 * kinds of traffic. BE endpoपूर्णांकs are also inactive in the
		 * beginning. When BE traffic starts it creates implicit
		 * streams that redistributes credits.
		 *
		 * Note: all other endpoपूर्णांकs have minimums set but are
		 * initially given NO credits. credits will be distributed
		 * as traffic activity demands
		 */
	पूर्ण

	/*
	 * For ath6kl_credit_seek function,
	 * it use list_क्रम_each_entry_reverse to walk around the whole ep list.
	 * Thereक्रमe assign this lowestpri_ep_dist after walk around the ep_list
	 */
	cred_info->lowestpri_ep_dist = cur_ep_dist->list;

	WARN_ON(cred_info->cur_मुक्त_credits <= 0);

	list_क्रम_each_entry(cur_ep_dist, ep_list, list) अणु
		अगर (cur_ep_dist->endpoपूर्णांक == ENDPOINT_0)
			जारी;

		अगर (cur_ep_dist->svc_id == WMI_CONTROL_SVC) अणु
			cur_ep_dist->cred_norm = cur_ep_dist->cred_per_msg;
		पूर्ण अन्यथा अणु
			/*
			 * For the reमुख्यing data endpoपूर्णांकs, we assume that
			 * each cred_per_msg are the same. We use a simple
			 * calculation here, we take the reमुख्यing credits
			 * and determine how many max messages this can
			 * cover and then set each endpoपूर्णांक's normal value
			 * equal to 3/4 this amount.
			 */
			count = (cred_info->cur_मुक्त_credits /
				 cur_ep_dist->cred_per_msg)
				* cur_ep_dist->cred_per_msg;
			count = (count * 3) >> 2;
			count = max(count, cur_ep_dist->cred_per_msg);
			cur_ep_dist->cred_norm = count;
		पूर्ण

		ath6kl_dbg(ATH6KL_DBG_CREDIT,
			   "credit ep %d svc_id %d credits %d per_msg %d norm %d min %d\n",
			   cur_ep_dist->endpoपूर्णांक,
			   cur_ep_dist->svc_id,
			   cur_ep_dist->credits,
			   cur_ep_dist->cred_per_msg,
			   cur_ep_dist->cred_norm,
			   cur_ep_dist->cred_min);
	पूर्ण
पूर्ण

/* initialize and setup credit distribution */
अटल पूर्णांक ath6kl_htc_mbox_credit_setup(काष्ठा htc_target *htc_target,
			       काष्ठा ath6kl_htc_credit_info *cred_info)
अणु
	u16 servicepriority[5];

	स_रखो(cred_info, 0, माप(काष्ठा ath6kl_htc_credit_info));

	servicepriority[0] = WMI_CONTROL_SVC;  /* highest */
	servicepriority[1] = WMI_DATA_VO_SVC;
	servicepriority[2] = WMI_DATA_VI_SVC;
	servicepriority[3] = WMI_DATA_BE_SVC;
	servicepriority[4] = WMI_DATA_BK_SVC; /* lowest */

	/* set priority list */
	ath6kl_htc_set_credit_dist(htc_target, cred_info, servicepriority, 5);

	वापस 0;
पूर्ण

/* reduce an ep's credits back to a set limit */
अटल व्योम ath6kl_credit_reduce(काष्ठा ath6kl_htc_credit_info *cred_info,
				 काष्ठा htc_endpoपूर्णांक_credit_dist *ep_dist,
				 पूर्णांक limit)
अणु
	पूर्णांक credits;

	ath6kl_dbg(ATH6KL_DBG_CREDIT, "credit reduce ep %d limit %d\n",
		   ep_dist->endpoपूर्णांक, limit);

	ep_dist->cred_assngd = limit;

	अगर (ep_dist->credits <= limit)
		वापस;

	credits = ep_dist->credits - limit;
	ep_dist->credits -= credits;
	cred_info->cur_मुक्त_credits += credits;
पूर्ण

अटल व्योम ath6kl_credit_update(काष्ठा ath6kl_htc_credit_info *cred_info,
				 काष्ठा list_head *epdist_list)
अणु
	काष्ठा htc_endpoपूर्णांक_credit_dist *cur_list;

	list_क्रम_each_entry(cur_list, epdist_list, list) अणु
		अगर (cur_list->endpoपूर्णांक == ENDPOINT_0)
			जारी;

		अगर (cur_list->cred_to_dist > 0) अणु
			cur_list->credits += cur_list->cred_to_dist;
			cur_list->cred_to_dist = 0;

			अगर (cur_list->credits > cur_list->cred_assngd)
				ath6kl_credit_reduce(cred_info,
						     cur_list,
						     cur_list->cred_assngd);

			अगर (cur_list->credits > cur_list->cred_norm)
				ath6kl_credit_reduce(cred_info, cur_list,
						     cur_list->cred_norm);

			अगर (!(cur_list->dist_flags & HTC_EP_ACTIVE)) अणु
				अगर (cur_list->txq_depth == 0)
					ath6kl_credit_reduce(cred_info,
							     cur_list, 0);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * HTC has an endpoपूर्णांक that needs credits, ep_dist is the endpoपूर्णांक in
 * question.
 */
अटल व्योम ath6kl_credit_seek(काष्ठा ath6kl_htc_credit_info *cred_info,
				काष्ठा htc_endpoपूर्णांक_credit_dist *ep_dist)
अणु
	काष्ठा htc_endpoपूर्णांक_credit_dist *curdist_list;
	पूर्णांक credits = 0;
	पूर्णांक need;

	अगर (ep_dist->svc_id == WMI_CONTROL_SVC)
		जाओ out;

	अगर ((ep_dist->svc_id == WMI_DATA_VI_SVC) ||
	    (ep_dist->svc_id == WMI_DATA_VO_SVC))
		अगर ((ep_dist->cred_assngd >= ep_dist->cred_norm))
			जाओ out;

	/*
	 * For all other services, we follow a simple algorithm of:
	 *
	 * 1. checking the मुक्त pool क्रम credits
	 * 2. checking lower priority endpoपूर्णांकs क्रम credits to take
	 */

	credits = min(cred_info->cur_मुक्त_credits, ep_dist->seek_cred);

	अगर (credits >= ep_dist->seek_cred)
		जाओ out;

	/*
	 * We करोn't have enough in the मुक्त pool, try taking away from
	 * lower priority services The rule क्रम taking away credits:
	 *
	 *   1. Only take from lower priority endpoपूर्णांकs
	 *   2. Only take what is allocated above the minimum (never
	 *      starve an endpoपूर्णांक completely)
	 *   3. Only take what you need.
	 */

	list_क्रम_each_entry_reverse(curdist_list,
				    &cred_info->lowestpri_ep_dist,
				    list) अणु
		अगर (curdist_list == ep_dist)
			अवरोध;

		need = ep_dist->seek_cred - cred_info->cur_मुक्त_credits;

		अगर ((curdist_list->cred_assngd - need) >=
		     curdist_list->cred_min) अणु
			/*
			 * The current one has been allocated more than
			 * it's minimum and it has enough credits asचिन्हित
			 * above it's minimum to fulfill our need try to
			 * take away just enough to fulfill our need.
			 */
			ath6kl_credit_reduce(cred_info, curdist_list,
					     curdist_list->cred_assngd - need);

			अगर (cred_info->cur_मुक्त_credits >=
			    ep_dist->seek_cred)
				अवरोध;
		पूर्ण

		अगर (curdist_list->endpoपूर्णांक == ENDPOINT_0)
			अवरोध;
	पूर्ण

	credits = min(cred_info->cur_मुक्त_credits, ep_dist->seek_cred);

out:
	/* did we find some credits? */
	अगर (credits)
		ath6kl_credit_deposit(cred_info, ep_dist, credits);

	ep_dist->seek_cred = 0;
पूर्ण

/* redistribute credits based on activity change */
अटल व्योम ath6kl_credit_redistribute(काष्ठा ath6kl_htc_credit_info *info,
				       काष्ठा list_head *ep_dist_list)
अणु
	काष्ठा htc_endpoपूर्णांक_credit_dist *curdist_list;

	list_क्रम_each_entry(curdist_list, ep_dist_list, list) अणु
		अगर (curdist_list->endpoपूर्णांक == ENDPOINT_0)
			जारी;

		अगर ((curdist_list->svc_id == WMI_DATA_BK_SVC)  ||
		    (curdist_list->svc_id == WMI_DATA_BE_SVC))
			curdist_list->dist_flags |= HTC_EP_ACTIVE;

		अगर ((curdist_list->svc_id != WMI_CONTROL_SVC) &&
		    !(curdist_list->dist_flags & HTC_EP_ACTIVE)) अणु
			अगर (curdist_list->txq_depth == 0)
				ath6kl_credit_reduce(info, curdist_list, 0);
			अन्यथा
				ath6kl_credit_reduce(info,
						     curdist_list,
						     curdist_list->cred_min);
		पूर्ण
	पूर्ण
पूर्ण

/*
 *
 * This function is invoked whenever endpoपूर्णांकs require credit
 * distributions. A lock is held जबतक this function is invoked, this
 * function shall NOT block. The ep_dist_list is a list of distribution
 * काष्ठाures in prioritized order as defined by the call to the
 * htc_set_credit_dist() api.
 */
अटल व्योम ath6kl_credit_distribute(काष्ठा ath6kl_htc_credit_info *cred_info,
				     काष्ठा list_head *ep_dist_list,
			      क्रमागत htc_credit_dist_reason reason)
अणु
	चयन (reason) अणु
	हाल HTC_CREDIT_DIST_SEND_COMPLETE:
		ath6kl_credit_update(cred_info, ep_dist_list);
		अवरोध;
	हाल HTC_CREDIT_DIST_ACTIVITY_CHANGE:
		ath6kl_credit_redistribute(cred_info, ep_dist_list);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	WARN_ON(cred_info->cur_मुक्त_credits > cred_info->total_avail_credits);
	WARN_ON(cred_info->cur_मुक्त_credits < 0);
पूर्ण

अटल व्योम ath6kl_htc_tx_buf_align(u8 **buf, अचिन्हित दीर्घ len)
अणु
	u8 *align_addr;

	अगर (!IS_ALIGNED((अचिन्हित दीर्घ) *buf, 4)) अणु
		align_addr = PTR_ALIGN(*buf - 4, 4);
		स_हटाओ(align_addr, *buf, len);
		*buf = align_addr;
	पूर्ण
पूर्ण

अटल व्योम ath6kl_htc_tx_prep_pkt(काष्ठा htc_packet *packet, u8 flags,
				   पूर्णांक ctrl0, पूर्णांक ctrl1)
अणु
	काष्ठा htc_frame_hdr *hdr;

	packet->buf -= HTC_HDR_LENGTH;
	hdr =  (काष्ठा htc_frame_hdr *)packet->buf;

	/* Endianess? */
	put_unaligned((u16)packet->act_len, &hdr->payld_len);
	hdr->flags = flags;
	hdr->eid = packet->endpoपूर्णांक;
	hdr->ctrl[0] = ctrl0;
	hdr->ctrl[1] = ctrl1;
पूर्ण

अटल व्योम htc_reclaim_txctrl_buf(काष्ठा htc_target *target,
				   काष्ठा htc_packet *pkt)
अणु
	spin_lock_bh(&target->htc_lock);
	list_add_tail(&pkt->list, &target->मुक्त_ctrl_txbuf);
	spin_unlock_bh(&target->htc_lock);
पूर्ण

अटल काष्ठा htc_packet *htc_get_control_buf(काष्ठा htc_target *target,
					      bool tx)
अणु
	काष्ठा htc_packet *packet = शून्य;
	काष्ठा list_head *buf_list;

	buf_list = tx ? &target->मुक्त_ctrl_txbuf : &target->मुक्त_ctrl_rxbuf;

	spin_lock_bh(&target->htc_lock);

	अगर (list_empty(buf_list)) अणु
		spin_unlock_bh(&target->htc_lock);
		वापस शून्य;
	पूर्ण

	packet = list_first_entry(buf_list, काष्ठा htc_packet, list);
	list_del(&packet->list);
	spin_unlock_bh(&target->htc_lock);

	अगर (tx)
		packet->buf = packet->buf_start + HTC_HDR_LENGTH;

	वापस packet;
पूर्ण

अटल व्योम htc_tx_comp_update(काष्ठा htc_target *target,
			       काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक,
			       काष्ठा htc_packet *packet)
अणु
	packet->completion = शून्य;
	packet->buf += HTC_HDR_LENGTH;

	अगर (!packet->status)
		वापस;

	ath6kl_err("req failed (status:%d, ep:%d, len:%d creds:%d)\n",
		   packet->status, packet->endpoपूर्णांक, packet->act_len,
		   packet->info.tx.cred_used);

	/* on failure to submit, reclaim credits क्रम this packet */
	spin_lock_bh(&target->tx_lock);
	endpoपूर्णांक->cred_dist.cred_to_dist +=
				packet->info.tx.cred_used;
	endpoपूर्णांक->cred_dist.txq_depth = get_queue_depth(&endpoपूर्णांक->txq);

	ath6kl_dbg(ATH6KL_DBG_HTC, "htc tx ctxt 0x%p dist 0x%p\n",
		   target->credit_info, &target->cred_dist_list);

	ath6kl_credit_distribute(target->credit_info,
				 &target->cred_dist_list,
				 HTC_CREDIT_DIST_SEND_COMPLETE);

	spin_unlock_bh(&target->tx_lock);
पूर्ण

अटल व्योम htc_tx_complete(काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक,
			    काष्ठा list_head *txq)
अणु
	अगर (list_empty(txq))
		वापस;

	ath6kl_dbg(ATH6KL_DBG_HTC,
		   "htc tx complete ep %d pkts %d\n",
		   endpoपूर्णांक->eid, get_queue_depth(txq));

	ath6kl_tx_complete(endpoपूर्णांक->target, txq);
पूर्ण

अटल व्योम htc_tx_comp_handler(काष्ठा htc_target *target,
				काष्ठा htc_packet *packet)
अणु
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक = &target->endpoपूर्णांक[packet->endpoपूर्णांक];
	काष्ठा list_head container;

	ath6kl_dbg(ATH6KL_DBG_HTC, "htc tx complete seqno %d\n",
		   packet->info.tx.seqno);

	htc_tx_comp_update(target, endpoपूर्णांक, packet);
	INIT_LIST_HEAD(&container);
	list_add_tail(&packet->list, &container);
	/* करो completion */
	htc_tx_complete(endpoपूर्णांक, &container);
पूर्ण

अटल व्योम htc_async_tx_scat_complete(काष्ठा htc_target *target,
				       काष्ठा hअगर_scatter_req *scat_req)
अणु
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक;
	काष्ठा htc_packet *packet;
	काष्ठा list_head tx_compq;
	पूर्णांक i;

	INIT_LIST_HEAD(&tx_compq);

	ath6kl_dbg(ATH6KL_DBG_HTC,
		   "htc tx scat complete len %d entries %d\n",
		   scat_req->len, scat_req->scat_entries);

	अगर (scat_req->status)
		ath6kl_err("send scatter req failed: %d\n", scat_req->status);

	packet = scat_req->scat_list[0].packet;
	endpoपूर्णांक = &target->endpoपूर्णांक[packet->endpoपूर्णांक];

	/* walk through the scatter list and process */
	क्रम (i = 0; i < scat_req->scat_entries; i++) अणु
		packet = scat_req->scat_list[i].packet;
		अगर (!packet) अणु
			WARN_ON(1);
			वापस;
		पूर्ण

		packet->status = scat_req->status;
		htc_tx_comp_update(target, endpoपूर्णांक, packet);
		list_add_tail(&packet->list, &tx_compq);
	पूर्ण

	/* मुक्त scatter request */
	hअगर_scatter_req_add(target->dev->ar, scat_req);

	/* complete all packets */
	htc_tx_complete(endpoपूर्णांक, &tx_compq);
पूर्ण

अटल पूर्णांक ath6kl_htc_tx_issue(काष्ठा htc_target *target,
			       काष्ठा htc_packet *packet)
अणु
	पूर्णांक status;
	bool sync = false;
	u32 padded_len, send_len;

	अगर (!packet->completion)
		sync = true;

	send_len = packet->act_len + HTC_HDR_LENGTH;

	padded_len = CALC_TXRX_PADDED_LEN(target, send_len);

	ath6kl_dbg(ATH6KL_DBG_HTC,
		   "htc tx issue len %d seqno %d padded_len %d mbox 0x%X %s\n",
		   send_len, packet->info.tx.seqno, padded_len,
		   target->dev->ar->mbox_info.htc_addr,
		   sync ? "sync" : "async");

	अगर (sync) अणु
		status = hअगर_पढ़ो_ग_लिखो_sync(target->dev->ar,
				target->dev->ar->mbox_info.htc_addr,
				 packet->buf, padded_len,
				 HIF_WR_SYNC_BLOCK_INC);

		packet->status = status;
		packet->buf += HTC_HDR_LENGTH;
	पूर्ण अन्यथा
		status = hअगर_ग_लिखो_async(target->dev->ar,
				target->dev->ar->mbox_info.htc_addr,
				packet->buf, padded_len,
				HIF_WR_ASYNC_BLOCK_INC, packet);

	trace_ath6kl_htc_tx(status, packet->endpoपूर्णांक, packet->buf, send_len);

	वापस status;
पूर्ण

अटल पूर्णांक htc_check_credits(काष्ठा htc_target *target,
			     काष्ठा htc_endpoपूर्णांक *ep, u8 *flags,
			     क्रमागत htc_endpoपूर्णांक_id eid, अचिन्हित पूर्णांक len,
			     पूर्णांक *req_cred)
अणु
	*req_cred = (len > target->tgt_cred_sz) ?
		     DIV_ROUND_UP(len, target->tgt_cred_sz) : 1;

	ath6kl_dbg(ATH6KL_DBG_CREDIT, "credit check need %d got %d\n",
		   *req_cred, ep->cred_dist.credits);

	अगर (ep->cred_dist.credits < *req_cred) अणु
		अगर (eid == ENDPOINT_0)
			वापस -EINVAL;

		/* Seek more credits */
		ep->cred_dist.seek_cred = *req_cred - ep->cred_dist.credits;

		ath6kl_credit_seek(target->credit_info, &ep->cred_dist);

		ep->cred_dist.seek_cred = 0;

		अगर (ep->cred_dist.credits < *req_cred) अणु
			ath6kl_dbg(ATH6KL_DBG_CREDIT,
				   "credit not found for ep %d\n",
				   eid);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ep->cred_dist.credits -= *req_cred;
	ep->ep_st.cred_cosumd += *req_cred;

	 /* When we are getting low on credits, ask क्रम more */
	अगर (ep->cred_dist.credits < ep->cred_dist.cred_per_msg) अणु
		ep->cred_dist.seek_cred =
		ep->cred_dist.cred_per_msg - ep->cred_dist.credits;

		ath6kl_credit_seek(target->credit_info, &ep->cred_dist);

		/* see अगर we were successful in getting more */
		अगर (ep->cred_dist.credits < ep->cred_dist.cred_per_msg) अणु
			/* tell the target we need credits ASAP! */
			*flags |= HTC_FLAGS_NEED_CREDIT_UPDATE;
			ep->ep_st.cred_low_indicate += 1;
			ath6kl_dbg(ATH6KL_DBG_CREDIT,
				   "credit we need credits asap\n");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath6kl_htc_tx_pkts_get(काष्ठा htc_target *target,
				   काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक,
				   काष्ठा list_head *queue)
अणु
	पूर्णांक req_cred;
	u8 flags;
	काष्ठा htc_packet *packet;
	अचिन्हित पूर्णांक len;

	जबतक (true) अणु
		flags = 0;

		अगर (list_empty(&endpoपूर्णांक->txq))
			अवरोध;
		packet = list_first_entry(&endpoपूर्णांक->txq, काष्ठा htc_packet,
					  list);

		ath6kl_dbg(ATH6KL_DBG_HTC,
			   "htc tx got packet 0x%p queue depth %d\n",
			   packet, get_queue_depth(&endpoपूर्णांक->txq));

		len = CALC_TXRX_PADDED_LEN(target,
					   packet->act_len + HTC_HDR_LENGTH);

		अगर (htc_check_credits(target, endpoपूर्णांक, &flags,
				      packet->endpoपूर्णांक, len, &req_cred))
			अवरोध;

		/* now we can fully move onto caller's queue */
		packet = list_first_entry(&endpoपूर्णांक->txq, काष्ठा htc_packet,
					  list);
		list_move_tail(&packet->list, queue);

		/* save the number of credits this packet consumed */
		packet->info.tx.cred_used = req_cred;

		/* all TX packets are handled asynchronously */
		packet->completion = htc_tx_comp_handler;
		packet->context = target;
		endpoपूर्णांक->ep_st.tx_issued += 1;

		/* save send flags */
		packet->info.tx.flags = flags;
		packet->info.tx.seqno = endpoपूर्णांक->seqno;
		endpoपूर्णांक->seqno++;
	पूर्ण
पूर्ण

/* See अगर the padded tx length falls on a credit boundary */
अटल पूर्णांक htc_get_credit_padding(अचिन्हित पूर्णांक cred_sz, पूर्णांक *len,
				  काष्ठा htc_endpoपूर्णांक *ep)
अणु
	पूर्णांक rem_cred, cred_pad;

	rem_cred = *len % cred_sz;

	/* No padding needed */
	अगर  (!rem_cred)
		वापस 0;

	अगर (!(ep->conn_flags & HTC_FLGS_TX_BNDL_PAD_EN))
		वापस -1;

	/*
	 * The transfer consumes a "partial" credit, this
	 * packet cannot be bundled unless we add
	 * additional "dummy" padding (max 255 bytes) to
	 * consume the entire credit.
	 */
	cred_pad = *len < cred_sz ? (cred_sz - *len) : rem_cred;

	अगर ((cred_pad > 0) && (cred_pad <= 255))
		*len += cred_pad;
	अन्यथा
		/* The amount of padding is too large, send as non-bundled */
		वापस -1;

	वापस cred_pad;
पूर्ण

अटल पूर्णांक ath6kl_htc_tx_setup_scat_list(काष्ठा htc_target *target,
					 काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक,
					 काष्ठा hअगर_scatter_req *scat_req,
					 पूर्णांक n_scat,
					 काष्ठा list_head *queue)
अणु
	काष्ठा htc_packet *packet;
	पूर्णांक i, len, rem_scat, cred_pad;
	पूर्णांक status = 0;
	u8 flags;

	rem_scat = target->max_tx_bndl_sz;

	क्रम (i = 0; i < n_scat; i++) अणु
		scat_req->scat_list[i].packet = शून्य;

		अगर (list_empty(queue))
			अवरोध;

		packet = list_first_entry(queue, काष्ठा htc_packet, list);
		len = CALC_TXRX_PADDED_LEN(target,
					   packet->act_len + HTC_HDR_LENGTH);

		cred_pad = htc_get_credit_padding(target->tgt_cred_sz,
						  &len, endpoपूर्णांक);
		अगर (cred_pad < 0 || rem_scat < len) अणु
			status = -ENOSPC;
			अवरोध;
		पूर्ण

		rem_scat -= len;
		/* now हटाओ it from the queue */
		list_del(&packet->list);

		scat_req->scat_list[i].packet = packet;
		/* prepare packet and flag message as part of a send bundle */
		flags = packet->info.tx.flags | HTC_FLAGS_SEND_BUNDLE;
		ath6kl_htc_tx_prep_pkt(packet, flags,
				       cred_pad, packet->info.tx.seqno);
		/* Make sure the buffer is 4-byte aligned */
		ath6kl_htc_tx_buf_align(&packet->buf,
					packet->act_len + HTC_HDR_LENGTH);
		scat_req->scat_list[i].buf = packet->buf;
		scat_req->scat_list[i].len = len;

		scat_req->len += len;
		scat_req->scat_entries++;
		ath6kl_dbg(ATH6KL_DBG_HTC,
			   "htc tx adding (%d) pkt 0x%p seqno %d len %d remaining %d\n",
			   i, packet, packet->info.tx.seqno, len, rem_scat);
	पूर्ण

	/* Roll back scatter setup in हाल of any failure */
	अगर (scat_req->scat_entries < HTC_MIN_HTC_MSGS_TO_BUNDLE) अणु
		क्रम (i = scat_req->scat_entries - 1; i >= 0; i--) अणु
			packet = scat_req->scat_list[i].packet;
			अगर (packet) अणु
				packet->buf += HTC_HDR_LENGTH;
				list_add(&packet->list, queue);
			पूर्ण
		पूर्ण
		वापस -EAGAIN;
	पूर्ण

	वापस status;
पूर्ण

/*
 * Drain a queue and send as bundles this function may वापस without fully
 * draining the queue when
 *
 *    1. scatter resources are exhausted
 *    2. a message that will consume a partial credit will stop the
 *    bundling process early
 *    3. we drop below the minimum number of messages क्रम a bundle
 */
अटल व्योम ath6kl_htc_tx_bundle(काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक,
				 काष्ठा list_head *queue,
				 पूर्णांक *sent_bundle, पूर्णांक *n_bundle_pkts)
अणु
	काष्ठा htc_target *target = endpoपूर्णांक->target;
	काष्ठा hअगर_scatter_req *scat_req = शून्य;
	पूर्णांक n_scat, n_sent_bundle = 0, tot_pkts_bundle = 0, i;
	काष्ठा htc_packet *packet;
	पूर्णांक status;
	u32 txb_mask;
	u8 ac = WMM_NUM_AC;

	अगर ((HTC_CTRL_RSVD_SVC != endpoपूर्णांक->svc_id) &&
	    (WMI_CONTROL_SVC != endpoपूर्णांक->svc_id))
		ac = target->dev->ar->ep2ac_map[endpoपूर्णांक->eid];

	जबतक (true) अणु
		status = 0;
		n_scat = get_queue_depth(queue);
		n_scat = min(n_scat, target->msg_per_bndl_max);

		अगर (n_scat < HTC_MIN_HTC_MSGS_TO_BUNDLE)
			/* not enough to bundle */
			अवरोध;

		scat_req = hअगर_scatter_req_get(target->dev->ar);

		अगर (!scat_req) अणु
			/* no scatter resources  */
			ath6kl_dbg(ATH6KL_DBG_HTC,
				   "htc tx no more scatter resources\n");
			अवरोध;
		पूर्ण

		अगर ((ac < WMM_NUM_AC) && (ac != WMM_AC_BK)) अणु
			अगर (WMM_AC_BE == ac)
				/*
				 * BE, BK have priorities and bit
				 * positions reversed
				 */
				txb_mask = (1 << WMM_AC_BK);
			अन्यथा
				/*
				 * any AC with priority lower than
				 * itself
				 */
				txb_mask = ((1 << ac) - 1);

			/*
			 * when the scatter request resources drop below a
			 * certain threshold, disable Tx bundling क्रम all
			 * AC's with priority lower than the current requesting
			 * AC. Otherwise re-enable Tx bundling क्रम them
			 */
			अगर (scat_req->scat_q_depth < ATH6KL_SCATTER_REQS)
				target->tx_bndl_mask &= ~txb_mask;
			अन्यथा
				target->tx_bndl_mask |= txb_mask;
		पूर्ण

		ath6kl_dbg(ATH6KL_DBG_HTC, "htc tx pkts to scatter: %d\n",
			   n_scat);

		scat_req->len = 0;
		scat_req->scat_entries = 0;

		status = ath6kl_htc_tx_setup_scat_list(target, endpoपूर्णांक,
						       scat_req, n_scat,
						       queue);
		अगर (status == -EAGAIN) अणु
			hअगर_scatter_req_add(target->dev->ar, scat_req);
			अवरोध;
		पूर्ण

		/* send path is always asynchronous */
		scat_req->complete = htc_async_tx_scat_complete;
		n_sent_bundle++;
		tot_pkts_bundle += scat_req->scat_entries;

		ath6kl_dbg(ATH6KL_DBG_HTC,
			   "htc tx scatter bytes %d entries %d\n",
			   scat_req->len, scat_req->scat_entries);

		क्रम (i = 0; i < scat_req->scat_entries; i++) अणु
			packet = scat_req->scat_list[i].packet;
			trace_ath6kl_htc_tx(packet->status, packet->endpoपूर्णांक,
					    packet->buf, packet->act_len);
		पूर्ण

		ath6kl_hअगर_submit_scat_req(target->dev, scat_req, false);

		अगर (status)
			अवरोध;
	पूर्ण

	*sent_bundle = n_sent_bundle;
	*n_bundle_pkts = tot_pkts_bundle;
	ath6kl_dbg(ATH6KL_DBG_HTC, "htc tx bundle sent %d pkts\n",
		   n_sent_bundle);

	वापस;
पूर्ण

अटल व्योम ath6kl_htc_tx_from_queue(काष्ठा htc_target *target,
				     काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक)
अणु
	काष्ठा list_head txq;
	काष्ठा htc_packet *packet;
	पूर्णांक bundle_sent;
	पूर्णांक n_pkts_bundle;
	u8 ac = WMM_NUM_AC;
	पूर्णांक status;

	spin_lock_bh(&target->tx_lock);

	endpoपूर्णांक->tx_proc_cnt++;
	अगर (endpoपूर्णांक->tx_proc_cnt > 1) अणु
		endpoपूर्णांक->tx_proc_cnt--;
		spin_unlock_bh(&target->tx_lock);
		ath6kl_dbg(ATH6KL_DBG_HTC, "htc tx busy\n");
		वापस;
	पूर्ण

	/*
	 * drain the endpoपूर्णांक TX queue क्रम transmission as दीर्घ
	 * as we have enough credits.
	 */
	INIT_LIST_HEAD(&txq);

	अगर ((HTC_CTRL_RSVD_SVC != endpoपूर्णांक->svc_id) &&
	    (WMI_CONTROL_SVC != endpoपूर्णांक->svc_id))
		ac = target->dev->ar->ep2ac_map[endpoपूर्णांक->eid];

	जबतक (true) अणु
		अगर (list_empty(&endpoपूर्णांक->txq))
			अवरोध;

		ath6kl_htc_tx_pkts_get(target, endpoपूर्णांक, &txq);

		अगर (list_empty(&txq))
			अवरोध;

		spin_unlock_bh(&target->tx_lock);

		bundle_sent = 0;
		n_pkts_bundle = 0;

		जबतक (true) अणु
			/* try to send a bundle on each pass */
			अगर ((target->tx_bndl_mask) &&
			    (get_queue_depth(&txq) >=
			    HTC_MIN_HTC_MSGS_TO_BUNDLE)) अणु
				पूर्णांक temp1 = 0, temp2 = 0;

				/* check अगर bundling is enabled क्रम an AC */
				अगर (target->tx_bndl_mask & (1 << ac)) अणु
					ath6kl_htc_tx_bundle(endpoपूर्णांक, &txq,
							     &temp1, &temp2);
					bundle_sent += temp1;
					n_pkts_bundle += temp2;
				पूर्ण
			पूर्ण

			अगर (list_empty(&txq))
				अवरोध;

			packet = list_first_entry(&txq, काष्ठा htc_packet,
						  list);
			list_del(&packet->list);

			ath6kl_htc_tx_prep_pkt(packet, packet->info.tx.flags,
					       0, packet->info.tx.seqno);
			status = ath6kl_htc_tx_issue(target, packet);

			अगर (status) अणु
				packet->status = status;
				packet->completion(packet->context, packet);
			पूर्ण
		पूर्ण

		spin_lock_bh(&target->tx_lock);

		endpoपूर्णांक->ep_st.tx_bundles += bundle_sent;
		endpoपूर्णांक->ep_st.tx_pkt_bundled += n_pkts_bundle;

		/*
		 * अगर an AC has bundling disabled and no tx bundling
		 * has occured continously क्रम a certain number of TX,
		 * enable tx bundling क्रम this AC
		 */
		अगर (!bundle_sent) अणु
			अगर (!(target->tx_bndl_mask & (1 << ac)) &&
			    (ac < WMM_NUM_AC)) अणु
				अगर (++target->ac_tx_count[ac] >=
					TX_RESUME_BUNDLE_THRESHOLD) अणु
					target->ac_tx_count[ac] = 0;
					target->tx_bndl_mask |= (1 << ac);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/* tx bundling will reset the counter */
			अगर (ac < WMM_NUM_AC)
				target->ac_tx_count[ac] = 0;
		पूर्ण
	पूर्ण

	endpoपूर्णांक->tx_proc_cnt = 0;
	spin_unlock_bh(&target->tx_lock);
पूर्ण

अटल bool ath6kl_htc_tx_try(काष्ठा htc_target *target,
			      काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक,
			      काष्ठा htc_packet *tx_pkt)
अणु
	काष्ठा htc_ep_callbacks ep_cb;
	पूर्णांक txq_depth;
	bool overflow = false;

	ep_cb = endpoपूर्णांक->ep_cb;

	spin_lock_bh(&target->tx_lock);
	txq_depth = get_queue_depth(&endpoपूर्णांक->txq);
	spin_unlock_bh(&target->tx_lock);

	अगर (txq_depth >= endpoपूर्णांक->max_txq_depth)
		overflow = true;

	अगर (overflow)
		ath6kl_dbg(ATH6KL_DBG_HTC,
			   "htc tx overflow ep %d depth %d max %d\n",
			   endpoपूर्णांक->eid, txq_depth,
			   endpoपूर्णांक->max_txq_depth);

	अगर (overflow && ep_cb.tx_full) अणु
		अगर (ep_cb.tx_full(endpoपूर्णांक->target, tx_pkt) ==
		    HTC_SEND_FULL_DROP) अणु
			endpoपूर्णांक->ep_st.tx_dropped += 1;
			वापस false;
		पूर्ण
	पूर्ण

	spin_lock_bh(&target->tx_lock);
	list_add_tail(&tx_pkt->list, &endpoपूर्णांक->txq);
	spin_unlock_bh(&target->tx_lock);

	ath6kl_htc_tx_from_queue(target, endpoपूर्णांक);

	वापस true;
पूर्ण

अटल व्योम htc_chk_ep_txq(काष्ठा htc_target *target)
अणु
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक;
	काष्ठा htc_endpoपूर्णांक_credit_dist *cred_dist;

	/*
	 * Run through the credit distribution list to see अगर there are
	 * packets queued. NOTE: no locks need to be taken since the
	 * distribution list is not dynamic (cannot be re-ordered) and we
	 * are not modअगरying any state.
	 */
	list_क्रम_each_entry(cred_dist, &target->cred_dist_list, list) अणु
		endpoपूर्णांक = cred_dist->htc_ep;

		spin_lock_bh(&target->tx_lock);
		अगर (!list_empty(&endpoपूर्णांक->txq)) अणु
			ath6kl_dbg(ATH6KL_DBG_HTC,
				   "htc creds ep %d credits %d pkts %d\n",
				   cred_dist->endpoपूर्णांक,
				   endpoपूर्णांक->cred_dist.credits,
				   get_queue_depth(&endpoपूर्णांक->txq));
			spin_unlock_bh(&target->tx_lock);
			/*
			 * Try to start the stalled queue, this list is
			 * ordered by priority. If there are credits
			 * available the highest priority queue will get a
			 * chance to reclaim credits from lower priority
			 * ones.
			 */
			ath6kl_htc_tx_from_queue(target, endpoपूर्णांक);
			spin_lock_bh(&target->tx_lock);
		पूर्ण
		spin_unlock_bh(&target->tx_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक htc_setup_tx_complete(काष्ठा htc_target *target)
अणु
	काष्ठा htc_packet *send_pkt = शून्य;
	पूर्णांक status;

	send_pkt = htc_get_control_buf(target, true);

	अगर (!send_pkt)
		वापस -ENOMEM;

	अगर (target->htc_tgt_ver >= HTC_VERSION_2P1) अणु
		काष्ठा htc_setup_comp_ext_msg *setup_comp_ext;
		u32 flags = 0;

		setup_comp_ext =
		    (काष्ठा htc_setup_comp_ext_msg *)send_pkt->buf;
		स_रखो(setup_comp_ext, 0, माप(*setup_comp_ext));
		setup_comp_ext->msg_id =
			cpu_to_le16(HTC_MSG_SETUP_COMPLETE_EX_ID);

		अगर (target->msg_per_bndl_max > 0) अणु
			/* Indicate HTC bundling to the target */
			flags |= HTC_SETUP_COMP_FLG_RX_BNDL_EN;
			setup_comp_ext->msg_per_rxbndl =
						target->msg_per_bndl_max;
		पूर्ण

		स_नकल(&setup_comp_ext->flags, &flags,
		       माप(setup_comp_ext->flags));
		set_htc_pkt_info(send_pkt, शून्य, (u8 *) setup_comp_ext,
				 माप(काष्ठा htc_setup_comp_ext_msg),
				 ENDPOINT_0, HTC_SERVICE_TX_PACKET_TAG);

	पूर्ण अन्यथा अणु
		काष्ठा htc_setup_comp_msg *setup_comp;
		setup_comp = (काष्ठा htc_setup_comp_msg *)send_pkt->buf;
		स_रखो(setup_comp, 0, माप(काष्ठा htc_setup_comp_msg));
		setup_comp->msg_id = cpu_to_le16(HTC_MSG_SETUP_COMPLETE_ID);
		set_htc_pkt_info(send_pkt, शून्य, (u8 *) setup_comp,
				 माप(काष्ठा htc_setup_comp_msg),
				 ENDPOINT_0, HTC_SERVICE_TX_PACKET_TAG);
	पूर्ण

	/* we want synchronous operation */
	send_pkt->completion = शून्य;
	ath6kl_htc_tx_prep_pkt(send_pkt, 0, 0, 0);
	status = ath6kl_htc_tx_issue(target, send_pkt);
	htc_reclaim_txctrl_buf(target, send_pkt);

	वापस status;
पूर्ण

अटल व्योम ath6kl_htc_set_credit_dist(काष्ठा htc_target *target,
				काष्ठा ath6kl_htc_credit_info *credit_info,
				u16 srvc_pri_order[], पूर्णांक list_len)
अणु
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक;
	पूर्णांक i, ep;

	target->credit_info = credit_info;

	list_add_tail(&target->endpoपूर्णांक[ENDPOINT_0].cred_dist.list,
		      &target->cred_dist_list);

	क्रम (i = 0; i < list_len; i++) अणु
		क्रम (ep = ENDPOINT_1; ep < ENDPOपूर्णांक_उच्च; ep++) अणु
			endpoपूर्णांक = &target->endpoपूर्णांक[ep];
			अगर (endpoपूर्णांक->svc_id == srvc_pri_order[i]) अणु
				list_add_tail(&endpoपूर्णांक->cred_dist.list,
					      &target->cred_dist_list);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (ep >= ENDPOपूर्णांक_उच्च) अणु
			WARN_ON(1);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ath6kl_htc_mbox_tx(काष्ठा htc_target *target,
			      काष्ठा htc_packet *packet)
अणु
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक;
	काष्ठा list_head queue;

	ath6kl_dbg(ATH6KL_DBG_HTC,
		   "htc tx ep id %d buf 0x%p len %d\n",
		   packet->endpoपूर्णांक, packet->buf, packet->act_len);

	अगर (packet->endpoपूर्णांक >= ENDPOपूर्णांक_उच्च) अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	endpoपूर्णांक = &target->endpoपूर्णांक[packet->endpoपूर्णांक];

	अगर (!ath6kl_htc_tx_try(target, endpoपूर्णांक, packet)) अणु
		packet->status = (target->htc_flags & HTC_OP_STATE_STOPPING) ?
				 -ECANCELED : -ENOSPC;
		INIT_LIST_HEAD(&queue);
		list_add(&packet->list, &queue);
		htc_tx_complete(endpoपूर्णांक, &queue);
	पूर्ण

	वापस 0;
पूर्ण

/* flush endpoपूर्णांक TX queue */
अटल व्योम ath6kl_htc_mbox_flush_txep(काष्ठा htc_target *target,
			   क्रमागत htc_endpoपूर्णांक_id eid, u16 tag)
अणु
	काष्ठा htc_packet *packet, *पंचांगp_pkt;
	काष्ठा list_head discard_q, container;
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक = &target->endpoपूर्णांक[eid];

	अगर (!endpoपूर्णांक->svc_id) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	/* initialize the discard queue */
	INIT_LIST_HEAD(&discard_q);

	spin_lock_bh(&target->tx_lock);

	list_क्रम_each_entry_safe(packet, पंचांगp_pkt, &endpoपूर्णांक->txq, list) अणु
		अगर ((tag == HTC_TX_PACKET_TAG_ALL) ||
		    (tag == packet->info.tx.tag))
			list_move_tail(&packet->list, &discard_q);
	पूर्ण

	spin_unlock_bh(&target->tx_lock);

	list_क्रम_each_entry_safe(packet, पंचांगp_pkt, &discard_q, list) अणु
		packet->status = -ECANCELED;
		list_del(&packet->list);
		ath6kl_dbg(ATH6KL_DBG_HTC,
			   "htc tx flushing pkt 0x%p len %d  ep %d tag 0x%x\n",
			   packet, packet->act_len,
			   packet->endpoपूर्णांक, packet->info.tx.tag);

		INIT_LIST_HEAD(&container);
		list_add_tail(&packet->list, &container);
		htc_tx_complete(endpoपूर्णांक, &container);
	पूर्ण
पूर्ण

अटल व्योम ath6kl_htc_flush_txep_all(काष्ठा htc_target *target)
अणु
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक;
	पूर्णांक i;

	dump_cred_dist_stats(target);

	क्रम (i = ENDPOINT_0; i < ENDPOपूर्णांक_उच्च; i++) अणु
		endpoपूर्णांक = &target->endpoपूर्णांक[i];
		अगर (endpoपूर्णांक->svc_id == 0)
			/* not in use.. */
			जारी;
		ath6kl_htc_mbox_flush_txep(target, i, HTC_TX_PACKET_TAG_ALL);
	पूर्ण
पूर्ण

अटल व्योम ath6kl_htc_mbox_activity_changed(काष्ठा htc_target *target,
					     क्रमागत htc_endpoपूर्णांक_id eid,
					     bool active)
अणु
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक = &target->endpoपूर्णांक[eid];
	bool dist = false;

	अगर (endpoपूर्णांक->svc_id == 0) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	spin_lock_bh(&target->tx_lock);

	अगर (active) अणु
		अगर (!(endpoपूर्णांक->cred_dist.dist_flags & HTC_EP_ACTIVE)) अणु
			endpoपूर्णांक->cred_dist.dist_flags |= HTC_EP_ACTIVE;
			dist = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (endpoपूर्णांक->cred_dist.dist_flags & HTC_EP_ACTIVE) अणु
			endpoपूर्णांक->cred_dist.dist_flags &= ~HTC_EP_ACTIVE;
			dist = true;
		पूर्ण
	पूर्ण

	अगर (dist) अणु
		endpoपूर्णांक->cred_dist.txq_depth =
			get_queue_depth(&endpoपूर्णांक->txq);

		ath6kl_dbg(ATH6KL_DBG_HTC,
			   "htc tx activity ctxt 0x%p dist 0x%p\n",
			   target->credit_info, &target->cred_dist_list);

		ath6kl_credit_distribute(target->credit_info,
					 &target->cred_dist_list,
					 HTC_CREDIT_DIST_ACTIVITY_CHANGE);
	पूर्ण

	spin_unlock_bh(&target->tx_lock);

	अगर (dist && !active)
		htc_chk_ep_txq(target);
पूर्ण

/* HTC Rx */

अटल अंतरभूत व्योम ath6kl_htc_rx_update_stats(काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक,
					      पूर्णांक n_look_ahds)
अणु
	endpoपूर्णांक->ep_st.rx_pkts++;
	अगर (n_look_ahds == 1)
		endpoपूर्णांक->ep_st.rx_lkahds++;
	अन्यथा अगर (n_look_ahds > 1)
		endpoपूर्णांक->ep_st.rx_bundle_lkahd++;
पूर्ण

अटल अंतरभूत bool htc_valid_rx_frame_len(काष्ठा htc_target *target,
					  क्रमागत htc_endpoपूर्णांक_id eid, पूर्णांक len)
अणु
	वापस (eid == target->dev->ar->ctrl_ep) ?
		len <= ATH6KL_BUFFER_SIZE : len <= ATH6KL_AMSDU_BUFFER_SIZE;
पूर्ण

अटल पूर्णांक htc_add_rxbuf(काष्ठा htc_target *target, काष्ठा htc_packet *packet)
अणु
	काष्ठा list_head queue;

	INIT_LIST_HEAD(&queue);
	list_add_tail(&packet->list, &queue);
	वापस ath6kl_htc_mbox_add_rxbuf_multiple(target, &queue);
पूर्ण

अटल व्योम htc_reclaim_rxbuf(काष्ठा htc_target *target,
			      काष्ठा htc_packet *packet,
			      काष्ठा htc_endpoपूर्णांक *ep)
अणु
	अगर (packet->info.rx.rx_flags & HTC_RX_PKT_NO_RECYCLE) अणु
		htc_rxpkt_reset(packet);
		packet->status = -ECANCELED;
		ep->ep_cb.rx(ep->target, packet);
	पूर्ण अन्यथा अणु
		htc_rxpkt_reset(packet);
		htc_add_rxbuf((व्योम *)(target), packet);
	पूर्ण
पूर्ण

अटल व्योम reclaim_rx_ctrl_buf(काष्ठा htc_target *target,
				काष्ठा htc_packet *packet)
अणु
	spin_lock_bh(&target->htc_lock);
	list_add_tail(&packet->list, &target->मुक्त_ctrl_rxbuf);
	spin_unlock_bh(&target->htc_lock);
पूर्ण

अटल पूर्णांक ath6kl_htc_rx_packet(काष्ठा htc_target *target,
				काष्ठा htc_packet *packet,
				u32 rx_len)
अणु
	काष्ठा ath6kl_device *dev = target->dev;
	u32 padded_len;
	पूर्णांक status;

	padded_len = CALC_TXRX_PADDED_LEN(target, rx_len);

	अगर (padded_len > packet->buf_len) अणु
		ath6kl_err("not enough receive space for packet - padlen %d recvlen %d bufferlen %d\n",
			   padded_len, rx_len, packet->buf_len);
		वापस -ENOMEM;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_HTC,
		   "htc rx 0x%p hdr 0x%x len %d mbox 0x%x\n",
		   packet, packet->info.rx.exp_hdr,
		   padded_len, dev->ar->mbox_info.htc_addr);

	status = hअगर_पढ़ो_ग_लिखो_sync(dev->ar,
				     dev->ar->mbox_info.htc_addr,
				     packet->buf, padded_len,
				     HIF_RD_SYNC_BLOCK_FIX);

	packet->status = status;

	वापस status;
पूर्ण

/*
 * optimization क्रम recv packets, we can indicate a
 * "hint" that there are more  single-packets to fetch
 * on this endpoपूर्णांक.
 */
अटल व्योम ath6kl_htc_rx_set_indicate(u32 lk_ahd,
				       काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक,
				       काष्ठा htc_packet *packet)
अणु
	काष्ठा htc_frame_hdr *htc_hdr = (काष्ठा htc_frame_hdr *)&lk_ahd;

	अगर (htc_hdr->eid == packet->endpoपूर्णांक) अणु
		अगर (!list_empty(&endpoपूर्णांक->rx_bufq))
			packet->info.rx.indicat_flags |=
					HTC_RX_FLAGS_INDICATE_MORE_PKTS;
	पूर्ण
पूर्ण

अटल व्योम ath6kl_htc_rx_chk_water_mark(काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक)
अणु
	काष्ठा htc_ep_callbacks ep_cb = endpoपूर्णांक->ep_cb;

	अगर (ep_cb.rx_refill_thresh > 0) अणु
		spin_lock_bh(&endpoपूर्णांक->target->rx_lock);
		अगर (get_queue_depth(&endpoपूर्णांक->rx_bufq)
		    < ep_cb.rx_refill_thresh) अणु
			spin_unlock_bh(&endpoपूर्णांक->target->rx_lock);
			ep_cb.rx_refill(endpoपूर्णांक->target, endpoपूर्णांक->eid);
			वापस;
		पूर्ण
		spin_unlock_bh(&endpoपूर्णांक->target->rx_lock);
	पूर्ण
पूर्ण

/* This function is called with rx_lock held */
अटल पूर्णांक ath6kl_htc_rx_setup(काष्ठा htc_target *target,
			       काष्ठा htc_endpoपूर्णांक *ep,
			       u32 *lk_ahds, काष्ठा list_head *queue, पूर्णांक n_msg)
अणु
	काष्ठा htc_packet *packet;
	/* FIXME: type of lk_ahds can't be right */
	काष्ठा htc_frame_hdr *htc_hdr = (काष्ठा htc_frame_hdr *)lk_ahds;
	काष्ठा htc_ep_callbacks ep_cb;
	पूर्णांक status = 0, j, full_len;
	bool no_recycle;

	full_len = CALC_TXRX_PADDED_LEN(target,
					le16_to_cpu(htc_hdr->payld_len) +
					माप(*htc_hdr));

	अगर (!htc_valid_rx_frame_len(target, ep->eid, full_len)) अणु
		ath6kl_warn("Rx buffer requested with invalid length htc_hdr:eid %d, flags 0x%x, len %d\n",
			    htc_hdr->eid, htc_hdr->flags,
			    le16_to_cpu(htc_hdr->payld_len));
		वापस -EINVAL;
	पूर्ण

	ep_cb = ep->ep_cb;
	क्रम (j = 0; j < n_msg; j++) अणु
		/*
		 * Reset flag, any packets allocated using the
		 * rx_alloc() API cannot be recycled on
		 * cleanup,they must be explicitly वापसed.
		 */
		no_recycle = false;

		अगर (ep_cb.rx_allocthresh &&
		    (full_len > ep_cb.rx_alloc_thresh)) अणु
			ep->ep_st.rx_alloc_thresh_hit += 1;
			ep->ep_st.rxalloc_thresh_byte +=
				le16_to_cpu(htc_hdr->payld_len);

			spin_unlock_bh(&target->rx_lock);
			no_recycle = true;

			packet = ep_cb.rx_allocthresh(ep->target, ep->eid,
						      full_len);
			spin_lock_bh(&target->rx_lock);
		पूर्ण अन्यथा अणु
			/* refill handler is being used */
			अगर (list_empty(&ep->rx_bufq)) अणु
				अगर (ep_cb.rx_refill) अणु
					spin_unlock_bh(&target->rx_lock);
					ep_cb.rx_refill(ep->target, ep->eid);
					spin_lock_bh(&target->rx_lock);
				पूर्ण
			पूर्ण

			अगर (list_empty(&ep->rx_bufq)) अणु
				packet = शून्य;
			पूर्ण अन्यथा अणु
				packet = list_first_entry(&ep->rx_bufq,
						काष्ठा htc_packet, list);
				list_del(&packet->list);
			पूर्ण
		पूर्ण

		अगर (!packet) अणु
			target->rx_st_flags |= HTC_RECV_WAIT_BUFFERS;
			target->ep_रुकोing = ep->eid;
			वापस -ENOSPC;
		पूर्ण

		/* clear flags */
		packet->info.rx.rx_flags = 0;
		packet->info.rx.indicat_flags = 0;
		packet->status = 0;

		अगर (no_recycle)
			/*
			 * flag that these packets cannot be
			 * recycled, they have to be वापसed to
			 * the user
			 */
			packet->info.rx.rx_flags |= HTC_RX_PKT_NO_RECYCLE;

		/* Caller needs to मुक्त this upon any failure */
		list_add_tail(&packet->list, queue);

		अगर (target->htc_flags & HTC_OP_STATE_STOPPING) अणु
			status = -ECANCELED;
			अवरोध;
		पूर्ण

		अगर (j) अणु
			packet->info.rx.rx_flags |= HTC_RX_PKT_REFRESH_HDR;
			packet->info.rx.exp_hdr = 0xFFFFFFFF;
		पूर्ण अन्यथा
			/* set expected look ahead */
			packet->info.rx.exp_hdr = *lk_ahds;

		packet->act_len = le16_to_cpu(htc_hdr->payld_len) +
			HTC_HDR_LENGTH;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक ath6kl_htc_rx_alloc(काष्ठा htc_target *target,
			       u32 lk_ahds[], पूर्णांक msg,
			       काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक,
			       काष्ठा list_head *queue)
अणु
	पूर्णांक status = 0;
	काष्ठा htc_packet *packet, *पंचांगp_pkt;
	काष्ठा htc_frame_hdr *htc_hdr;
	पूर्णांक i, n_msg;

	spin_lock_bh(&target->rx_lock);

	क्रम (i = 0; i < msg; i++) अणु
		htc_hdr = (काष्ठा htc_frame_hdr *)&lk_ahds[i];

		अगर (htc_hdr->eid >= ENDPOपूर्णांक_उच्च) अणु
			ath6kl_err("invalid ep in look-ahead: %d\n",
				   htc_hdr->eid);
			status = -ENOMEM;
			अवरोध;
		पूर्ण

		अगर (htc_hdr->eid != endpoपूर्णांक->eid) अणु
			ath6kl_err("invalid ep in look-ahead: %d should be : %d (index:%d)\n",
				   htc_hdr->eid, endpoपूर्णांक->eid, i);
			status = -ENOMEM;
			अवरोध;
		पूर्ण

		अगर (le16_to_cpu(htc_hdr->payld_len) > HTC_MAX_PAYLOAD_LENGTH) अणु
			ath6kl_err("payload len %d exceeds max htc : %d !\n",
				   htc_hdr->payld_len,
				   (u32) HTC_MAX_PAYLOAD_LENGTH);
			status = -ENOMEM;
			अवरोध;
		पूर्ण

		अगर (endpoपूर्णांक->svc_id == 0) अणु
			ath6kl_err("ep %d is not connected !\n", htc_hdr->eid);
			status = -ENOMEM;
			अवरोध;
		पूर्ण

		अगर (htc_hdr->flags & HTC_FLG_RX_BNDL_CNT) अणु
			/*
			 * HTC header indicates that every packet to follow
			 * has the same padded length so that it can be
			 * optimally fetched as a full bundle.
			 */
			n_msg = (htc_hdr->flags & HTC_FLG_RX_BNDL_CNT) >>
				HTC_FLG_RX_BNDL_CNT_S;

			/* the count करोesn't include the starter frame */
			n_msg++;
			अगर (n_msg > target->msg_per_bndl_max) अणु
				status = -ENOMEM;
				अवरोध;
			पूर्ण

			endpoपूर्णांक->ep_st.rx_bundle_from_hdr += 1;
			ath6kl_dbg(ATH6KL_DBG_HTC,
				   "htc rx bundle pkts %d\n",
				   n_msg);
		पूर्ण अन्यथा
			/* HTC header only indicates 1 message to fetch */
			n_msg = 1;

		/* Setup packet buffers क्रम each message */
		status = ath6kl_htc_rx_setup(target, endpoपूर्णांक, &lk_ahds[i],
					     queue, n_msg);

		/*
		 * This is due to unavailabilty of buffers to rx entire data.
		 * Return no error so that मुक्त buffers from queue can be used
		 * to receive partial data.
		 */
		अगर (status == -ENOSPC) अणु
			spin_unlock_bh(&target->rx_lock);
			वापस 0;
		पूर्ण

		अगर (status)
			अवरोध;
	पूर्ण

	spin_unlock_bh(&target->rx_lock);

	अगर (status) अणु
		list_क्रम_each_entry_safe(packet, पंचांगp_pkt, queue, list) अणु
			list_del(&packet->list);
			htc_reclaim_rxbuf(target, packet,
					  &target->endpoपूर्णांक[packet->endpoपूर्णांक]);
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम htc_ctrl_rx(काष्ठा htc_target *context, काष्ठा htc_packet *packets)
अणु
	अगर (packets->endpoपूर्णांक != ENDPOINT_0) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	अगर (packets->status == -ECANCELED) अणु
		reclaim_rx_ctrl_buf(context, packets);
		वापस;
	पूर्ण

	अगर (packets->act_len > 0) अणु
		ath6kl_err("htc_ctrl_rx, got message with len:%zu\n",
			   packets->act_len + HTC_HDR_LENGTH);

		ath6kl_dbg_dump(ATH6KL_DBG_HTC,
				"htc rx unexpected endpoint 0 message", "",
				packets->buf - HTC_HDR_LENGTH,
				packets->act_len + HTC_HDR_LENGTH);
	पूर्ण

	htc_reclaim_rxbuf(context, packets, &context->endpoपूर्णांक[0]);
पूर्ण

अटल व्योम htc_proc_cred_rpt(काष्ठा htc_target *target,
			      काष्ठा htc_credit_report *rpt,
			      पूर्णांक n_entries,
			      क्रमागत htc_endpoपूर्णांक_id from_ep)
अणु
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक;
	पूर्णांक tot_credits = 0, i;
	bool dist = false;

	spin_lock_bh(&target->tx_lock);

	क्रम (i = 0; i < n_entries; i++, rpt++) अणु
		अगर (rpt->eid >= ENDPOपूर्णांक_उच्च) अणु
			WARN_ON(1);
			spin_unlock_bh(&target->tx_lock);
			वापस;
		पूर्ण

		endpoपूर्णांक = &target->endpoपूर्णांक[rpt->eid];

		ath6kl_dbg(ATH6KL_DBG_CREDIT,
			   "credit report ep %d credits %d\n",
			   rpt->eid, rpt->credits);

		endpoपूर्णांक->ep_st.tx_cred_rpt += 1;
		endpoपूर्णांक->ep_st.cred_retnd += rpt->credits;

		अगर (from_ep == rpt->eid) अणु
			/*
			 * This credit report arrived on the same endpoपूर्णांक
			 * indicating it arrived in an RX packet.
			 */
			endpoपूर्णांक->ep_st.cred_from_rx += rpt->credits;
			endpoपूर्णांक->ep_st.cred_rpt_from_rx += 1;
		पूर्ण अन्यथा अगर (from_ep == ENDPOINT_0) अणु
			/* credit arrived on endpoपूर्णांक 0 as a शून्य message */
			endpoपूर्णांक->ep_st.cred_from_ep0 += rpt->credits;
			endpoपूर्णांक->ep_st.cred_rpt_ep0 += 1;
		पूर्ण अन्यथा अणु
			endpoपूर्णांक->ep_st.cred_from_other += rpt->credits;
			endpoपूर्णांक->ep_st.cred_rpt_from_other += 1;
		पूर्ण

		अगर (rpt->eid == ENDPOINT_0)
			/* always give endpoपूर्णांक 0 credits back */
			endpoपूर्णांक->cred_dist.credits += rpt->credits;
		अन्यथा अणु
			endpoपूर्णांक->cred_dist.cred_to_dist += rpt->credits;
			dist = true;
		पूर्ण

		/*
		 * Refresh tx depth क्रम distribution function that will
		 * recover these credits NOTE: this is only valid when
		 * there are credits to recover!
		 */
		endpoपूर्णांक->cred_dist.txq_depth =
			get_queue_depth(&endpoपूर्णांक->txq);

		tot_credits += rpt->credits;
	पूर्ण

	अगर (dist) अणु
		/*
		 * This was a credit वापस based on a completed send
		 * operations note, this is करोne with the lock held
		 */
		ath6kl_credit_distribute(target->credit_info,
					 &target->cred_dist_list,
					 HTC_CREDIT_DIST_SEND_COMPLETE);
	पूर्ण

	spin_unlock_bh(&target->tx_lock);

	अगर (tot_credits)
		htc_chk_ep_txq(target);
पूर्ण

अटल पूर्णांक htc_parse_trailer(काष्ठा htc_target *target,
			     काष्ठा htc_record_hdr *record,
			     u8 *record_buf, u32 *next_lk_ahds,
			     क्रमागत htc_endpoपूर्णांक_id endpoपूर्णांक,
			     पूर्णांक *n_lk_ahds)
अणु
	काष्ठा htc_bundle_lkahd_rpt *bundle_lkahd_rpt;
	काष्ठा htc_lookahead_report *lk_ahd;
	पूर्णांक len;

	चयन (record->rec_id) अणु
	हाल HTC_RECORD_CREDITS:
		len = record->len / माप(काष्ठा htc_credit_report);
		अगर (!len) अणु
			WARN_ON(1);
			वापस -EINVAL;
		पूर्ण

		htc_proc_cred_rpt(target,
				  (काष्ठा htc_credit_report *) record_buf,
				  len, endpoपूर्णांक);
		अवरोध;
	हाल HTC_RECORD_LOOKAHEAD:
		len = record->len / माप(*lk_ahd);
		अगर (!len) अणु
			WARN_ON(1);
			वापस -EINVAL;
		पूर्ण

		lk_ahd = (काष्ठा htc_lookahead_report *) record_buf;
		अगर ((lk_ahd->pre_valid == ((~lk_ahd->post_valid) & 0xFF)) &&
		    next_lk_ahds) अणु
			ath6kl_dbg(ATH6KL_DBG_HTC,
				   "htc rx lk_ahd found pre_valid 0x%x post_valid 0x%x\n",
				   lk_ahd->pre_valid, lk_ahd->post_valid);

			/* look ahead bytes are valid, copy them over */
			स_नकल((u8 *)&next_lk_ahds[0], lk_ahd->lk_ahd, 4);

			ath6kl_dbg_dump(ATH6KL_DBG_HTC,
					"htc rx next look ahead",
					"", next_lk_ahds, 4);

			*n_lk_ahds = 1;
		पूर्ण
		अवरोध;
	हाल HTC_RECORD_LOOKAHEAD_BUNDLE:
		len = record->len / माप(*bundle_lkahd_rpt);
		अगर (!len || (len > HTC_HOST_MAX_MSG_PER_BUNDLE)) अणु
			WARN_ON(1);
			वापस -EINVAL;
		पूर्ण

		अगर (next_lk_ahds) अणु
			पूर्णांक i;

			bundle_lkahd_rpt =
				(काष्ठा htc_bundle_lkahd_rpt *) record_buf;

			ath6kl_dbg_dump(ATH6KL_DBG_HTC, "htc rx bundle lk_ahd",
					"", record_buf, record->len);

			क्रम (i = 0; i < len; i++) अणु
				स_नकल((u8 *)&next_lk_ahds[i],
				       bundle_lkahd_rpt->lk_ahd, 4);
				bundle_lkahd_rpt++;
			पूर्ण

			*n_lk_ahds = i;
		पूर्ण
		अवरोध;
	शेष:
		ath6kl_err("unhandled record: id:%d len:%d\n",
			   record->rec_id, record->len);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक htc_proc_trailer(काष्ठा htc_target *target,
			    u8 *buf, पूर्णांक len, u32 *next_lk_ahds,
			    पूर्णांक *n_lk_ahds, क्रमागत htc_endpoपूर्णांक_id endpoपूर्णांक)
अणु
	काष्ठा htc_record_hdr *record;
	पूर्णांक orig_len;
	पूर्णांक status;
	u8 *record_buf;
	u8 *orig_buf;

	ath6kl_dbg(ATH6KL_DBG_HTC, "htc rx trailer len %d\n", len);
	ath6kl_dbg_dump(ATH6KL_DBG_HTC, शून्य, "", buf, len);

	orig_buf = buf;
	orig_len = len;
	status = 0;

	जबतक (len > 0) अणु
		अगर (len < माप(काष्ठा htc_record_hdr)) अणु
			status = -ENOMEM;
			अवरोध;
		पूर्ण
		/* these are byte aligned काष्ठाs */
		record = (काष्ठा htc_record_hdr *) buf;
		len -= माप(काष्ठा htc_record_hdr);
		buf += माप(काष्ठा htc_record_hdr);

		अगर (record->len > len) अणु
			ath6kl_err("invalid record len: %d (id:%d) buf has: %d bytes left\n",
				   record->len, record->rec_id, len);
			status = -ENOMEM;
			अवरोध;
		पूर्ण
		record_buf = buf;

		status = htc_parse_trailer(target, record, record_buf,
					   next_lk_ahds, endpoपूर्णांक, n_lk_ahds);

		अगर (status)
			अवरोध;

		/* advance buffer past this record क्रम next समय around */
		buf += record->len;
		len -= record->len;
	पूर्ण

	अगर (status)
		ath6kl_dbg_dump(ATH6KL_DBG_HTC, "htc rx bad trailer",
				"", orig_buf, orig_len);

	वापस status;
पूर्ण

अटल पूर्णांक ath6kl_htc_rx_process_hdr(काष्ठा htc_target *target,
				     काष्ठा htc_packet *packet,
				     u32 *next_lkahds, पूर्णांक *n_lkahds)
अणु
	पूर्णांक status = 0;
	u16 payload_len;
	u32 lk_ahd;
	काष्ठा htc_frame_hdr *htc_hdr = (काष्ठा htc_frame_hdr *)packet->buf;

	अगर (n_lkahds != शून्य)
		*n_lkahds = 0;

	/*
	 * NOTE: we cannot assume the alignment of buf, so we use the safe
	 * macros to retrieve 16 bit fields.
	 */
	payload_len = le16_to_cpu(get_unaligned(&htc_hdr->payld_len));

	स_नकल((u8 *)&lk_ahd, packet->buf, माप(lk_ahd));

	अगर (packet->info.rx.rx_flags & HTC_RX_PKT_REFRESH_HDR) अणु
		/*
		 * Refresh the expected header and the actual length as it
		 * was unknown when this packet was grabbed as part of the
		 * bundle.
		 */
		packet->info.rx.exp_hdr = lk_ahd;
		packet->act_len = payload_len + HTC_HDR_LENGTH;

		/* validate the actual header that was refreshed  */
		अगर (packet->act_len > packet->buf_len) अणु
			ath6kl_err("refreshed hdr payload len (%d) in bundled recv is invalid (hdr: 0x%X)\n",
				   payload_len, lk_ahd);
			/*
			 * Limit this to max buffer just to prपूर्णांक out some
			 * of the buffer.
			 */
			packet->act_len = min(packet->act_len, packet->buf_len);
			status = -ENOMEM;
			जाओ fail_rx;
		पूर्ण

		अगर (packet->endpoपूर्णांक != htc_hdr->eid) अणु
			ath6kl_err("refreshed hdr ep (%d) does not match expected ep (%d)\n",
				   htc_hdr->eid, packet->endpoपूर्णांक);
			status = -ENOMEM;
			जाओ fail_rx;
		पूर्ण
	पूर्ण

	अगर (lk_ahd != packet->info.rx.exp_hdr) अणु
		ath6kl_err("%s(): lk_ahd mismatch! (pPkt:0x%p flags:0x%X)\n",
			   __func__, packet, packet->info.rx.rx_flags);
		ath6kl_dbg_dump(ATH6KL_DBG_HTC, "htc rx expected lk_ahd",
				"", &packet->info.rx.exp_hdr, 4);
		ath6kl_dbg_dump(ATH6KL_DBG_HTC, "htc rx current header",
				"", (u8 *)&lk_ahd, माप(lk_ahd));
		status = -ENOMEM;
		जाओ fail_rx;
	पूर्ण

	अगर (htc_hdr->flags & HTC_FLG_RX_TRAILER) अणु
		अगर (htc_hdr->ctrl[0] < माप(काष्ठा htc_record_hdr) ||
		    htc_hdr->ctrl[0] > payload_len) अणु
			ath6kl_err("%s(): invalid hdr (payload len should be :%d, CB[0] is:%d)\n",
				   __func__, payload_len, htc_hdr->ctrl[0]);
			status = -ENOMEM;
			जाओ fail_rx;
		पूर्ण

		अगर (packet->info.rx.rx_flags & HTC_RX_PKT_IGNORE_LOOKAHEAD) अणु
			next_lkahds = शून्य;
			n_lkahds = शून्य;
		पूर्ण

		status = htc_proc_trailer(target, packet->buf + HTC_HDR_LENGTH
					  + payload_len - htc_hdr->ctrl[0],
					  htc_hdr->ctrl[0], next_lkahds,
					   n_lkahds, packet->endpoपूर्णांक);

		अगर (status)
			जाओ fail_rx;

		packet->act_len -= htc_hdr->ctrl[0];
	पूर्ण

	packet->buf += HTC_HDR_LENGTH;
	packet->act_len -= HTC_HDR_LENGTH;

fail_rx:
	अगर (status)
		ath6kl_dbg_dump(ATH6KL_DBG_HTC, "htc rx bad packet",
				"", packet->buf, packet->act_len);

	वापस status;
पूर्ण

अटल व्योम ath6kl_htc_rx_complete(काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक,
				   काष्ठा htc_packet *packet)
अणु
		ath6kl_dbg(ATH6KL_DBG_HTC,
			   "htc rx complete ep %d packet 0x%p\n",
			   endpoपूर्णांक->eid, packet);

		endpoपूर्णांक->ep_cb.rx(endpoपूर्णांक->target, packet);
पूर्ण

अटल पूर्णांक ath6kl_htc_rx_bundle(काष्ठा htc_target *target,
				काष्ठा list_head *rxq,
				काष्ठा list_head *sync_compq,
				पूर्णांक *n_pkt_fetched, bool part_bundle)
अणु
	काष्ठा hअगर_scatter_req *scat_req;
	काष्ठा htc_packet *packet;
	पूर्णांक rem_space = target->max_rx_bndl_sz;
	पूर्णांक n_scat_pkt, status = 0, i, len;

	n_scat_pkt = get_queue_depth(rxq);
	n_scat_pkt = min(n_scat_pkt, target->msg_per_bndl_max);

	अगर ((get_queue_depth(rxq) - n_scat_pkt) > 0) अणु
		/*
		 * We were क्रमced to split this bundle receive operation
		 * all packets in this partial bundle must have their
		 * lookaheads ignored.
		 */
		part_bundle = true;

		/*
		 * This would only happen अगर the target ignored our max
		 * bundle limit.
		 */
		ath6kl_warn("%s(): partial bundle detected num:%d , %d\n",
			    __func__, get_queue_depth(rxq), n_scat_pkt);
	पूर्ण

	len = 0;

	ath6kl_dbg(ATH6KL_DBG_HTC,
		   "htc rx bundle depth %d pkts %d\n",
		   get_queue_depth(rxq), n_scat_pkt);

	scat_req = hअगर_scatter_req_get(target->dev->ar);

	अगर (scat_req == शून्य)
		जाओ fail_rx_pkt;

	क्रम (i = 0; i < n_scat_pkt; i++) अणु
		पूर्णांक pad_len;

		packet = list_first_entry(rxq, काष्ठा htc_packet, list);
		list_del(&packet->list);

		pad_len = CALC_TXRX_PADDED_LEN(target,
						   packet->act_len);

		अगर ((rem_space - pad_len) < 0) अणु
			list_add(&packet->list, rxq);
			अवरोध;
		पूर्ण

		rem_space -= pad_len;

		अगर (part_bundle || (i < (n_scat_pkt - 1)))
			/*
			 * Packet 0..n-1 cannot be checked क्रम look-aheads
			 * since we are fetching a bundle the last packet
			 * however can have it's lookahead used
			 */
			packet->info.rx.rx_flags |=
			    HTC_RX_PKT_IGNORE_LOOKAHEAD;

		/* NOTE: 1 HTC packet per scatter entry */
		scat_req->scat_list[i].buf = packet->buf;
		scat_req->scat_list[i].len = pad_len;

		packet->info.rx.rx_flags |= HTC_RX_PKT_PART_OF_BUNDLE;

		list_add_tail(&packet->list, sync_compq);

		WARN_ON(!scat_req->scat_list[i].len);
		len += scat_req->scat_list[i].len;
	पूर्ण

	scat_req->len = len;
	scat_req->scat_entries = i;

	status = ath6kl_hअगर_submit_scat_req(target->dev, scat_req, true);

	अगर (!status)
		*n_pkt_fetched = i;

	/* मुक्त scatter request */
	hअगर_scatter_req_add(target->dev->ar, scat_req);

fail_rx_pkt:

	वापस status;
पूर्ण

अटल पूर्णांक ath6kl_htc_rx_process_packets(काष्ठा htc_target *target,
					 काष्ठा list_head *comp_pktq,
					 u32 lk_ahds[],
					 पूर्णांक *n_lk_ahd)
अणु
	काष्ठा htc_packet *packet, *पंचांगp_pkt;
	काष्ठा htc_endpoपूर्णांक *ep;
	पूर्णांक status = 0;

	list_क्रम_each_entry_safe(packet, पंचांगp_pkt, comp_pktq, list) अणु
		ep = &target->endpoपूर्णांक[packet->endpoपूर्णांक];

		trace_ath6kl_htc_rx(packet->status, packet->endpoपूर्णांक,
				    packet->buf, packet->act_len);

		/* process header क्रम each of the recv packet */
		status = ath6kl_htc_rx_process_hdr(target, packet, lk_ahds,
						   n_lk_ahd);
		अगर (status)
			वापस status;

		list_del(&packet->list);

		अगर (list_empty(comp_pktq)) अणु
			/*
			 * Last packet's more packet flag is set
			 * based on the lookahead.
			 */
			अगर (*n_lk_ahd > 0)
				ath6kl_htc_rx_set_indicate(lk_ahds[0],
							   ep, packet);
		पूर्ण अन्यथा
			/*
			 * Packets in a bundle स्वतःmatically have
			 * this flag set.
			 */
			packet->info.rx.indicat_flags |=
				HTC_RX_FLAGS_INDICATE_MORE_PKTS;

		ath6kl_htc_rx_update_stats(ep, *n_lk_ahd);

		अगर (packet->info.rx.rx_flags & HTC_RX_PKT_PART_OF_BUNDLE)
			ep->ep_st.rx_bundl += 1;

		ath6kl_htc_rx_complete(ep, packet);
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक ath6kl_htc_rx_fetch(काष्ठा htc_target *target,
			       काष्ठा list_head *rx_pktq,
			       काष्ठा list_head *comp_pktq)
अणु
	पूर्णांक fetched_pkts;
	bool part_bundle = false;
	पूर्णांक status = 0;
	काष्ठा list_head पंचांगp_rxq;
	काष्ठा htc_packet *packet, *पंचांगp_pkt;

	/* now go fetch the list of HTC packets */
	जबतक (!list_empty(rx_pktq)) अणु
		fetched_pkts = 0;

		INIT_LIST_HEAD(&पंचांगp_rxq);

		अगर (target->rx_bndl_enable && (get_queue_depth(rx_pktq) > 1)) अणु
			/*
			 * There are enough packets to attempt a
			 * bundle transfer and recv bundling is
			 * allowed.
			 */
			status = ath6kl_htc_rx_bundle(target, rx_pktq,
						      &पंचांगp_rxq,
						      &fetched_pkts,
						      part_bundle);
			अगर (status)
				जाओ fail_rx;

			अगर (!list_empty(rx_pktq))
				part_bundle = true;

			list_splice_tail_init(&पंचांगp_rxq, comp_pktq);
		पूर्ण

		अगर (!fetched_pkts) अणु
			packet = list_first_entry(rx_pktq, काष्ठा htc_packet,
						   list);

			/* fully synchronous */
			packet->completion = शून्य;

			अगर (!list_is_singular(rx_pktq))
				/*
				 * look_aheads in all packet
				 * except the last one in the
				 * bundle must be ignored
				 */
				packet->info.rx.rx_flags |=
					HTC_RX_PKT_IGNORE_LOOKAHEAD;

			/* go fetch the packet */
			status = ath6kl_htc_rx_packet(target, packet,
						      packet->act_len);

			list_move_tail(&packet->list, &पंचांगp_rxq);

			अगर (status)
				जाओ fail_rx;

			list_splice_tail_init(&पंचांगp_rxq, comp_pktq);
		पूर्ण
	पूर्ण

	वापस 0;

fail_rx:

	/*
	 * Cleanup any packets we allocated but didn't use to
	 * actually fetch any packets.
	 */

	list_क्रम_each_entry_safe(packet, पंचांगp_pkt, rx_pktq, list) अणु
		list_del(&packet->list);
		htc_reclaim_rxbuf(target, packet,
				  &target->endpoपूर्णांक[packet->endpoपूर्णांक]);
	पूर्ण

	list_क्रम_each_entry_safe(packet, पंचांगp_pkt, &पंचांगp_rxq, list) अणु
		list_del(&packet->list);
		htc_reclaim_rxbuf(target, packet,
				  &target->endpoपूर्णांक[packet->endpoपूर्णांक]);
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक ath6kl_htc_rxmsg_pending_handler(काष्ठा htc_target *target,
				     u32 msg_look_ahead, पूर्णांक *num_pkts)
अणु
	काष्ठा htc_packet *packets, *पंचांगp_pkt;
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक;
	काष्ठा list_head rx_pktq, comp_pktq;
	पूर्णांक status = 0;
	u32 look_aheads[HTC_HOST_MAX_MSG_PER_BUNDLE];
	पूर्णांक num_look_ahead = 1;
	क्रमागत htc_endpoपूर्णांक_id id;
	पूर्णांक n_fetched = 0;

	INIT_LIST_HEAD(&comp_pktq);
	*num_pkts = 0;

	/*
	 * On first entry copy the look_aheads पूर्णांकo our temp array क्रम
	 * processing
	 */
	look_aheads[0] = msg_look_ahead;

	जबतक (true) अणु
		/*
		 * First lookahead sets the expected endpoपूर्णांक IDs क्रम all
		 * packets in a bundle.
		 */
		id = ((काष्ठा htc_frame_hdr *)&look_aheads[0])->eid;
		endpoपूर्णांक = &target->endpoपूर्णांक[id];

		अगर (id >= ENDPOपूर्णांक_उच्च) अणु
			ath6kl_err("MsgPend, invalid endpoint in look-ahead: %d\n",
				   id);
			status = -ENOMEM;
			अवरोध;
		पूर्ण

		INIT_LIST_HEAD(&rx_pktq);
		INIT_LIST_HEAD(&comp_pktq);

		/*
		 * Try to allocate as many HTC RX packets indicated by the
		 * look_aheads.
		 */
		status = ath6kl_htc_rx_alloc(target, look_aheads,
					     num_look_ahead, endpoपूर्णांक,
					     &rx_pktq);
		अगर (status)
			अवरोध;

		अगर (get_queue_depth(&rx_pktq) >= 2)
			/*
			 * A recv bundle was detected, क्रमce IRQ status
			 * re-check again
			 */
			target->chk_irq_status_cnt = 1;

		n_fetched += get_queue_depth(&rx_pktq);

		num_look_ahead = 0;

		status = ath6kl_htc_rx_fetch(target, &rx_pktq, &comp_pktq);

		अगर (!status)
			ath6kl_htc_rx_chk_water_mark(endpoपूर्णांक);

		/* Process fetched packets */
		status = ath6kl_htc_rx_process_packets(target, &comp_pktq,
						       look_aheads,
						       &num_look_ahead);

		अगर (!num_look_ahead || status)
			अवरोध;

		/*
		 * For SYNCH processing, अगर we get here, we are running
		 * through the loop again due to a detected lookahead. Set
		 * flag that we should re-check IRQ status रेजिस्टरs again
		 * beक्रमe leaving IRQ processing, this can net better
		 * perक्रमmance in high throughput situations.
		 */
		target->chk_irq_status_cnt = 1;
	पूर्ण

	अगर (status) अणु
		अगर (status != -ECANCELED)
			ath6kl_err("failed to get pending recv messages: %d\n",
				   status);

		/* cleanup any packets in sync completion queue */
		list_क्रम_each_entry_safe(packets, पंचांगp_pkt, &comp_pktq, list) अणु
			list_del(&packets->list);
			htc_reclaim_rxbuf(target, packets,
					  &target->endpoपूर्णांक[packets->endpoपूर्णांक]);
		पूर्ण

		अगर (target->htc_flags & HTC_OP_STATE_STOPPING) अणु
			ath6kl_warn("host is going to stop blocking receiver for htc_stop\n");
			ath6kl_hअगर_rx_control(target->dev, false);
		पूर्ण
	पूर्ण

	/*
	 * Beक्रमe leaving, check to see अगर host ran out of buffers and
	 * needs to stop the receiver.
	 */
	अगर (target->rx_st_flags & HTC_RECV_WAIT_BUFFERS) अणु
		ath6kl_warn("host has no rx buffers blocking receiver to prevent overrun\n");
		ath6kl_hअगर_rx_control(target->dev, false);
	पूर्ण
	*num_pkts = n_fetched;

	वापस status;
पूर्ण

/*
 * Synchronously रुको क्रम a control message from the target,
 * This function is used at initialization समय ONLY.  At init messages
 * on ENDPOINT 0 are expected.
 */
अटल काष्ठा htc_packet *htc_रुको_क्रम_ctrl_msg(काष्ठा htc_target *target)
अणु
	काष्ठा htc_packet *packet = शून्य;
	काष्ठा htc_frame_hdr *htc_hdr;
	u32 look_ahead;

	अगर (ath6kl_hअगर_poll_mboxmsg_rx(target->dev, &look_ahead,
				       HTC_TARGET_RESPONSE_TIMEOUT))
		वापस शून्य;

	ath6kl_dbg(ATH6KL_DBG_HTC,
		   "htc rx wait ctrl look_ahead 0x%X\n", look_ahead);

	htc_hdr = (काष्ठा htc_frame_hdr *)&look_ahead;

	अगर (htc_hdr->eid != ENDPOINT_0)
		वापस शून्य;

	packet = htc_get_control_buf(target, false);

	अगर (!packet)
		वापस शून्य;

	packet->info.rx.rx_flags = 0;
	packet->info.rx.exp_hdr = look_ahead;
	packet->act_len = le16_to_cpu(htc_hdr->payld_len) + HTC_HDR_LENGTH;

	अगर (packet->act_len > packet->buf_len)
		जाओ fail_ctrl_rx;

	/* we want synchronous operation */
	packet->completion = शून्य;

	/* get the message from the device, this will block */
	अगर (ath6kl_htc_rx_packet(target, packet, packet->act_len))
		जाओ fail_ctrl_rx;

	trace_ath6kl_htc_rx(packet->status, packet->endpoपूर्णांक,
			    packet->buf, packet->act_len);

	/* process receive header */
	packet->status = ath6kl_htc_rx_process_hdr(target, packet, शून्य, शून्य);

	अगर (packet->status) अणु
		ath6kl_err("htc_wait_for_ctrl_msg, ath6kl_htc_rx_process_hdr failed (status = %d)\n",
			   packet->status);
		जाओ fail_ctrl_rx;
	पूर्ण

	वापस packet;

fail_ctrl_rx:
	अगर (packet != शून्य) अणु
		htc_rxpkt_reset(packet);
		reclaim_rx_ctrl_buf(target, packet);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक ath6kl_htc_mbox_add_rxbuf_multiple(काष्ठा htc_target *target,
				  काष्ठा list_head *pkt_queue)
अणु
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक;
	काष्ठा htc_packet *first_pkt;
	bool rx_unblock = false;
	पूर्णांक status = 0, depth;

	अगर (list_empty(pkt_queue))
		वापस -ENOMEM;

	first_pkt = list_first_entry(pkt_queue, काष्ठा htc_packet, list);

	अगर (first_pkt->endpoपूर्णांक >= ENDPOपूर्णांक_उच्च)
		वापस status;

	depth = get_queue_depth(pkt_queue);

	ath6kl_dbg(ATH6KL_DBG_HTC,
		   "htc rx add multiple ep id %d cnt %d len %d\n",
		first_pkt->endpoपूर्णांक, depth, first_pkt->buf_len);

	endpoपूर्णांक = &target->endpoपूर्णांक[first_pkt->endpoपूर्णांक];

	अगर (target->htc_flags & HTC_OP_STATE_STOPPING) अणु
		काष्ठा htc_packet *packet, *पंचांगp_pkt;

		/* walk through queue and mark each one canceled */
		list_क्रम_each_entry_safe(packet, पंचांगp_pkt, pkt_queue, list) अणु
			packet->status = -ECANCELED;
			list_del(&packet->list);
			ath6kl_htc_rx_complete(endpoपूर्णांक, packet);
		पूर्ण

		वापस status;
	पूर्ण

	spin_lock_bh(&target->rx_lock);

	list_splice_tail_init(pkt_queue, &endpoपूर्णांक->rx_bufq);

	/* check अगर we are blocked रुकोing क्रम a new buffer */
	अगर (target->rx_st_flags & HTC_RECV_WAIT_BUFFERS) अणु
		अगर (target->ep_रुकोing == first_pkt->endpoपूर्णांक) अणु
			ath6kl_dbg(ATH6KL_DBG_HTC,
				   "htc rx blocked on ep %d, unblocking\n",
				   target->ep_रुकोing);
			target->rx_st_flags &= ~HTC_RECV_WAIT_BUFFERS;
			target->ep_रुकोing = ENDPOपूर्णांक_उच्च;
			rx_unblock = true;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&target->rx_lock);

	अगर (rx_unblock && !(target->htc_flags & HTC_OP_STATE_STOPPING))
		/* TODO : implement a buffer threshold count? */
		ath6kl_hअगर_rx_control(target->dev, true);

	वापस status;
पूर्ण

अटल व्योम ath6kl_htc_mbox_flush_rx_buf(काष्ठा htc_target *target)
अणु
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक;
	काष्ठा htc_packet *packet, *पंचांगp_pkt;
	पूर्णांक i;

	क्रम (i = ENDPOINT_0; i < ENDPOपूर्णांक_उच्च; i++) अणु
		endpoपूर्णांक = &target->endpoपूर्णांक[i];
		अगर (!endpoपूर्णांक->svc_id)
			/* not in use.. */
			जारी;

		spin_lock_bh(&target->rx_lock);
		list_क्रम_each_entry_safe(packet, पंचांगp_pkt,
					 &endpoपूर्णांक->rx_bufq, list) अणु
			list_del(&packet->list);
			spin_unlock_bh(&target->rx_lock);
			ath6kl_dbg(ATH6KL_DBG_HTC,
				   "htc rx flush pkt 0x%p  len %d  ep %d\n",
				   packet, packet->buf_len,
				   packet->endpoपूर्णांक);
			/*
			 * packets in rx_bufq of endpoपूर्णांक 0 have originally
			 * been queued from target->मुक्त_ctrl_rxbuf where
			 * packet and packet->buf_start are allocated
			 * separately using kदो_स्मृति(). For other endpoपूर्णांक
			 * rx_bufq, it is allocated as skb where packet is
			 * skb->head. Take care of this dअगरference जबतक मुक्तing
			 * the memory.
			 */
			अगर (packet->endpoपूर्णांक == ENDPOINT_0) अणु
				kमुक्त(packet->buf_start);
				kमुक्त(packet);
			पूर्ण अन्यथा अणु
				dev_kमुक्त_skb(packet->pkt_cntxt);
			पूर्ण
			spin_lock_bh(&target->rx_lock);
		पूर्ण
		spin_unlock_bh(&target->rx_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक ath6kl_htc_mbox_conn_service(काष्ठा htc_target *target,
			    काष्ठा htc_service_connect_req *conn_req,
			    काष्ठा htc_service_connect_resp *conn_resp)
अणु
	काष्ठा htc_packet *rx_pkt = शून्य;
	काष्ठा htc_packet *tx_pkt = शून्य;
	काष्ठा htc_conn_service_resp *resp_msg;
	काष्ठा htc_conn_service_msg *conn_msg;
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक;
	क्रमागत htc_endpoपूर्णांक_id asचिन्हित_ep = ENDPOपूर्णांक_उच्च;
	अचिन्हित पूर्णांक max_msg_sz = 0;
	पूर्णांक status = 0;
	u16 msg_id;

	ath6kl_dbg(ATH6KL_DBG_HTC,
		   "htc connect service target 0x%p service id 0x%x\n",
		   target, conn_req->svc_id);

	अगर (conn_req->svc_id == HTC_CTRL_RSVD_SVC) अणु
		/* special हाल क्रम pseuकरो control service */
		asचिन्हित_ep = ENDPOINT_0;
		max_msg_sz = HTC_MAX_CTRL_MSG_LEN;
	पूर्ण अन्यथा अणु
		/* allocate a packet to send to the target */
		tx_pkt = htc_get_control_buf(target, true);

		अगर (!tx_pkt)
			वापस -ENOMEM;

		conn_msg = (काष्ठा htc_conn_service_msg *)tx_pkt->buf;
		स_रखो(conn_msg, 0, माप(*conn_msg));
		conn_msg->msg_id = cpu_to_le16(HTC_MSG_CONN_SVC_ID);
		conn_msg->svc_id = cpu_to_le16(conn_req->svc_id);
		conn_msg->conn_flags = cpu_to_le16(conn_req->conn_flags);

		set_htc_pkt_info(tx_pkt, शून्य, (u8 *) conn_msg,
				 माप(*conn_msg) + conn_msg->svc_meta_len,
				 ENDPOINT_0, HTC_SERVICE_TX_PACKET_TAG);

		/* we want synchronous operation */
		tx_pkt->completion = शून्य;
		ath6kl_htc_tx_prep_pkt(tx_pkt, 0, 0, 0);
		status = ath6kl_htc_tx_issue(target, tx_pkt);

		अगर (status)
			जाओ fail_tx;

		/* रुको क्रम response */
		rx_pkt = htc_रुको_क्रम_ctrl_msg(target);

		अगर (!rx_pkt) अणु
			status = -ENOMEM;
			जाओ fail_tx;
		पूर्ण

		resp_msg = (काष्ठा htc_conn_service_resp *)rx_pkt->buf;
		msg_id = le16_to_cpu(resp_msg->msg_id);

		अगर ((msg_id != HTC_MSG_CONN_SVC_RESP_ID) ||
		    (rx_pkt->act_len < माप(*resp_msg))) अणु
			status = -ENOMEM;
			जाओ fail_tx;
		पूर्ण

		conn_resp->resp_code = resp_msg->status;
		/* check response status */
		अगर (resp_msg->status != HTC_SERVICE_SUCCESS) अणु
			ath6kl_err("target failed service 0x%X connect request (status:%d)\n",
				   resp_msg->svc_id, resp_msg->status);
			status = -ENOMEM;
			जाओ fail_tx;
		पूर्ण

		asचिन्हित_ep = (क्रमागत htc_endpoपूर्णांक_id)resp_msg->eid;
		max_msg_sz = le16_to_cpu(resp_msg->max_msg_sz);
	पूर्ण

	अगर (WARN_ON_ONCE(asचिन्हित_ep == ENDPOINT_UNUSED ||
			 asचिन्हित_ep >= ENDPOपूर्णांक_उच्च || !max_msg_sz)) अणु
		status = -ENOMEM;
		जाओ fail_tx;
	पूर्ण

	endpoपूर्णांक = &target->endpoपूर्णांक[asचिन्हित_ep];
	endpoपूर्णांक->eid = asचिन्हित_ep;
	अगर (endpoपूर्णांक->svc_id) अणु
		status = -ENOMEM;
		जाओ fail_tx;
	पूर्ण

	/* वापस asचिन्हित endpoपूर्णांक to caller */
	conn_resp->endpoपूर्णांक = asचिन्हित_ep;
	conn_resp->len_max = max_msg_sz;

	/* setup the endpoपूर्णांक */

	/* this marks the endpoपूर्णांक in use */
	endpoपूर्णांक->svc_id = conn_req->svc_id;

	endpoपूर्णांक->max_txq_depth = conn_req->max_txq_depth;
	endpoपूर्णांक->len_max = max_msg_sz;
	endpoपूर्णांक->ep_cb = conn_req->ep_cb;
	endpoपूर्णांक->cred_dist.svc_id = conn_req->svc_id;
	endpoपूर्णांक->cred_dist.htc_ep = endpoपूर्णांक;
	endpoपूर्णांक->cred_dist.endpoपूर्णांक = asचिन्हित_ep;
	endpoपूर्णांक->cred_dist.cred_sz = target->tgt_cred_sz;

	चयन (endpoपूर्णांक->svc_id) अणु
	हाल WMI_DATA_BK_SVC:
		endpoपूर्णांक->tx_drop_packet_threshold = MAX_DEF_COOKIE_NUM / 3;
		अवरोध;
	शेष:
		endpoपूर्णांक->tx_drop_packet_threshold = MAX_HI_COOKIE_NUM;
		अवरोध;
	पूर्ण

	अगर (conn_req->max_rxmsg_sz) अणु
		/*
		 * Override cred_per_msg calculation, this optimizes
		 * the credit-low indications since the host will actually
		 * issue smaller messages in the Send path.
		 */
		अगर (conn_req->max_rxmsg_sz > max_msg_sz) अणु
			status = -ENOMEM;
			जाओ fail_tx;
		पूर्ण
		endpoपूर्णांक->cred_dist.cred_per_msg =
		    conn_req->max_rxmsg_sz / target->tgt_cred_sz;
	पूर्ण अन्यथा
		endpoपूर्णांक->cred_dist.cred_per_msg =
		    max_msg_sz / target->tgt_cred_sz;

	अगर (!endpoपूर्णांक->cred_dist.cred_per_msg)
		endpoपूर्णांक->cred_dist.cred_per_msg = 1;

	/* save local connection flags */
	endpoपूर्णांक->conn_flags = conn_req->flags;

fail_tx:
	अगर (tx_pkt)
		htc_reclaim_txctrl_buf(target, tx_pkt);

	अगर (rx_pkt) अणु
		htc_rxpkt_reset(rx_pkt);
		reclaim_rx_ctrl_buf(target, rx_pkt);
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम reset_ep_state(काष्ठा htc_target *target)
अणु
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक;
	पूर्णांक i;

	क्रम (i = ENDPOINT_0; i < ENDPOपूर्णांक_उच्च; i++) अणु
		endpoपूर्णांक = &target->endpoपूर्णांक[i];
		स_रखो(&endpoपूर्णांक->cred_dist, 0, माप(endpoपूर्णांक->cred_dist));
		endpoपूर्णांक->svc_id = 0;
		endpoपूर्णांक->len_max = 0;
		endpoपूर्णांक->max_txq_depth = 0;
		स_रखो(&endpoपूर्णांक->ep_st, 0,
		       माप(endpoपूर्णांक->ep_st));
		INIT_LIST_HEAD(&endpoपूर्णांक->rx_bufq);
		INIT_LIST_HEAD(&endpoपूर्णांक->txq);
		endpoपूर्णांक->target = target;
	पूर्ण

	/* reset distribution list */
	/* FIXME: मुक्त existing entries */
	INIT_LIST_HEAD(&target->cred_dist_list);
पूर्ण

अटल पूर्णांक ath6kl_htc_mbox_get_rxbuf_num(काष्ठा htc_target *target,
			     क्रमागत htc_endpoपूर्णांक_id endpoपूर्णांक)
अणु
	पूर्णांक num;

	spin_lock_bh(&target->rx_lock);
	num = get_queue_depth(&(target->endpoपूर्णांक[endpoपूर्णांक].rx_bufq));
	spin_unlock_bh(&target->rx_lock);
	वापस num;
पूर्ण

अटल व्योम htc_setup_msg_bndl(काष्ठा htc_target *target)
अणु
	/* limit what HTC can handle */
	target->msg_per_bndl_max = min(HTC_HOST_MAX_MSG_PER_BUNDLE,
				       target->msg_per_bndl_max);

	अगर (ath6kl_hअगर_enable_scatter(target->dev->ar)) अणु
		target->msg_per_bndl_max = 0;
		वापस;
	पूर्ण

	/* limit bundle what the device layer can handle */
	target->msg_per_bndl_max = min(target->max_scat_entries,
				       target->msg_per_bndl_max);

	ath6kl_dbg(ATH6KL_DBG_BOOT,
		   "htc bundling allowed msg_per_bndl_max %d\n",
		   target->msg_per_bndl_max);

	/* Max rx bundle size is limited by the max tx bundle size */
	target->max_rx_bndl_sz = target->max_xfer_szper_scatreq;
	/* Max tx bundle size अगर limited by the extended mbox address range */
	target->max_tx_bndl_sz = min(HIF_MBOX0_EXT_WIDTH,
				     target->max_xfer_szper_scatreq);

	ath6kl_dbg(ATH6KL_DBG_BOOT, "htc max_rx_bndl_sz %d max_tx_bndl_sz %d\n",
		   target->max_rx_bndl_sz, target->max_tx_bndl_sz);

	अगर (target->max_tx_bndl_sz)
		/* tx_bndl_mask is enabled per AC, each has 1 bit */
		target->tx_bndl_mask = (1 << WMM_NUM_AC) - 1;

	अगर (target->max_rx_bndl_sz)
		target->rx_bndl_enable = true;

	अगर ((target->tgt_cred_sz % target->block_sz) != 0) अणु
		ath6kl_warn("credit size: %d is not block aligned! Disabling send bundling\n",
			    target->tgt_cred_sz);

		/*
		 * Disallow send bundling since the credit size is
		 * not aligned to a block size the I/O block
		 * padding will spill पूर्णांकo the next credit buffer
		 * which is fatal.
		 */
		target->tx_bndl_mask = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ath6kl_htc_mbox_रुको_target(काष्ठा htc_target *target)
अणु
	काष्ठा htc_packet *packet = शून्य;
	काष्ठा htc_पढ़ोy_ext_msg *rdy_msg;
	काष्ठा htc_service_connect_req connect;
	काष्ठा htc_service_connect_resp resp;
	पूर्णांक status;

	/* we should be getting 1 control message that the target is पढ़ोy */
	packet = htc_रुको_क्रम_ctrl_msg(target);

	अगर (!packet)
		वापस -ENOMEM;

	/* we controlled the buffer creation so it's properly aligned */
	rdy_msg = (काष्ठा htc_पढ़ोy_ext_msg *)packet->buf;

	अगर ((le16_to_cpu(rdy_msg->ver2_0_info.msg_id) != HTC_MSG_READY_ID) ||
	    (packet->act_len < माप(काष्ठा htc_पढ़ोy_msg))) अणु
		status = -ENOMEM;
		जाओ fail_रुको_target;
	पूर्ण

	अगर (!rdy_msg->ver2_0_info.cred_cnt || !rdy_msg->ver2_0_info.cred_sz) अणु
		status = -ENOMEM;
		जाओ fail_रुको_target;
	पूर्ण

	target->tgt_creds = le16_to_cpu(rdy_msg->ver2_0_info.cred_cnt);
	target->tgt_cred_sz = le16_to_cpu(rdy_msg->ver2_0_info.cred_sz);

	ath6kl_dbg(ATH6KL_DBG_BOOT,
		   "htc target ready credits %d size %d\n",
		   target->tgt_creds, target->tgt_cred_sz);

	/* check अगर this is an extended पढ़ोy message */
	अगर (packet->act_len >= माप(काष्ठा htc_पढ़ोy_ext_msg)) अणु
		/* this is an extended message */
		target->htc_tgt_ver = rdy_msg->htc_ver;
		target->msg_per_bndl_max = rdy_msg->msg_per_htc_bndl;
	पूर्ण अन्यथा अणु
		/* legacy */
		target->htc_tgt_ver = HTC_VERSION_2P0;
		target->msg_per_bndl_max = 0;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_BOOT, "htc using protocol %s (%d)\n",
		   (target->htc_tgt_ver == HTC_VERSION_2P0) ? "2.0" : ">= 2.1",
		   target->htc_tgt_ver);

	अगर (target->msg_per_bndl_max > 0)
		htc_setup_msg_bndl(target);

	/* setup our pseuकरो HTC control endpoपूर्णांक connection */
	स_रखो(&connect, 0, माप(connect));
	स_रखो(&resp, 0, माप(resp));
	connect.ep_cb.rx = htc_ctrl_rx;
	connect.ep_cb.rx_refill = शून्य;
	connect.ep_cb.tx_full = शून्य;
	connect.max_txq_depth = NUM_CONTROL_BUFFERS;
	connect.svc_id = HTC_CTRL_RSVD_SVC;

	/* connect fake service */
	status = ath6kl_htc_mbox_conn_service((व्योम *)target, &connect, &resp);

	अगर (status)
		/*
		 * FIXME: this call करोesn't make sense, the caller should
		 * call ath6kl_htc_mbox_cleanup() when it wants हटाओ htc
		 */
		ath6kl_hअगर_cleanup_scatter(target->dev->ar);

fail_रुको_target:
	अगर (packet) अणु
		htc_rxpkt_reset(packet);
		reclaim_rx_ctrl_buf(target, packet);
	पूर्ण

	वापस status;
पूर्ण

/*
 * Start HTC, enable पूर्णांकerrupts and let the target know
 * host has finished setup.
 */
अटल पूर्णांक ath6kl_htc_mbox_start(काष्ठा htc_target *target)
अणु
	काष्ठा htc_packet *packet;
	पूर्णांक status;

	स_रखो(&target->dev->irq_proc_reg, 0,
	       माप(target->dev->irq_proc_reg));

	/* Disable पूर्णांकerrupts at the chip level */
	ath6kl_hअगर_disable_पूर्णांकrs(target->dev);

	target->htc_flags = 0;
	target->rx_st_flags = 0;

	/* Push control receive buffers पूर्णांकo htc control endpoपूर्णांक */
	जबतक ((packet = htc_get_control_buf(target, false)) != शून्य) अणु
		status = htc_add_rxbuf(target, packet);
		अगर (status)
			वापस status;
	पूर्ण

	/* NOTE: the first entry in the distribution list is ENDPOINT_0 */
	ath6kl_credit_init(target->credit_info, &target->cred_dist_list,
			   target->tgt_creds);

	dump_cred_dist_stats(target);

	/* Indicate to the target of the setup completion */
	status = htc_setup_tx_complete(target);

	अगर (status)
		वापस status;

	/* unmask पूर्णांकerrupts */
	status = ath6kl_hअगर_unmask_पूर्णांकrs(target->dev);

	अगर (status)
		ath6kl_htc_mbox_stop(target);

	वापस status;
पूर्ण

अटल पूर्णांक ath6kl_htc_reset(काष्ठा htc_target *target)
अणु
	u32 block_size, ctrl_bufsz;
	काष्ठा htc_packet *packet;
	पूर्णांक i;

	reset_ep_state(target);

	block_size = target->dev->ar->mbox_info.block_size;

	ctrl_bufsz = (block_size > HTC_MAX_CTRL_MSG_LEN) ?
		      (block_size + HTC_HDR_LENGTH) :
		      (HTC_MAX_CTRL_MSG_LEN + HTC_HDR_LENGTH);

	क्रम (i = 0; i < NUM_CONTROL_BUFFERS; i++) अणु
		packet = kzalloc(माप(*packet), GFP_KERNEL);
		अगर (!packet)
			वापस -ENOMEM;

		packet->buf_start = kzalloc(ctrl_bufsz, GFP_KERNEL);
		अगर (!packet->buf_start) अणु
			kमुक्त(packet);
			वापस -ENOMEM;
		पूर्ण

		packet->buf_len = ctrl_bufsz;
		अगर (i < NUM_CONTROL_RX_BUFFERS) अणु
			packet->act_len = 0;
			packet->buf = packet->buf_start;
			packet->endpoपूर्णांक = ENDPOINT_0;
			list_add_tail(&packet->list, &target->मुक्त_ctrl_rxbuf);
		पूर्ण अन्यथा अणु
			list_add_tail(&packet->list, &target->मुक्त_ctrl_txbuf);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* htc_stop: stop पूर्णांकerrupt reception, and flush all queued buffers */
अटल व्योम ath6kl_htc_mbox_stop(काष्ठा htc_target *target)
अणु
	spin_lock_bh(&target->htc_lock);
	target->htc_flags |= HTC_OP_STATE_STOPPING;
	spin_unlock_bh(&target->htc_lock);

	/*
	 * Masking पूर्णांकerrupts is a synchronous operation, when this
	 * function वापसs all pending HIF I/O has completed, we can
	 * safely flush the queues.
	 */
	ath6kl_hअगर_mask_पूर्णांकrs(target->dev);

	ath6kl_htc_flush_txep_all(target);

	ath6kl_htc_mbox_flush_rx_buf(target);

	ath6kl_htc_reset(target);
पूर्ण

अटल व्योम *ath6kl_htc_mbox_create(काष्ठा ath6kl *ar)
अणु
	काष्ठा htc_target *target = शून्य;
	पूर्णांक status = 0;

	target = kzalloc(माप(*target), GFP_KERNEL);
	अगर (!target) अणु
		ath6kl_err("unable to allocate memory\n");
		वापस शून्य;
	पूर्ण

	target->dev = kzalloc(माप(*target->dev), GFP_KERNEL);
	अगर (!target->dev) अणु
		ath6kl_err("unable to allocate memory\n");
		kमुक्त(target);
		वापस शून्य;
	पूर्ण

	spin_lock_init(&target->htc_lock);
	spin_lock_init(&target->rx_lock);
	spin_lock_init(&target->tx_lock);

	INIT_LIST_HEAD(&target->मुक्त_ctrl_txbuf);
	INIT_LIST_HEAD(&target->मुक्त_ctrl_rxbuf);
	INIT_LIST_HEAD(&target->cred_dist_list);

	target->dev->ar = ar;
	target->dev->htc_cnxt = target;
	target->ep_रुकोing = ENDPOपूर्णांक_उच्च;

	status = ath6kl_hअगर_setup(target->dev);
	अगर (status)
		जाओ err_htc_cleanup;

	status = ath6kl_htc_reset(target);
	अगर (status)
		जाओ err_htc_cleanup;

	वापस target;

err_htc_cleanup:
	ath6kl_htc_mbox_cleanup(target);

	वापस शून्य;
पूर्ण

/* cleanup the HTC instance */
अटल व्योम ath6kl_htc_mbox_cleanup(काष्ठा htc_target *target)
अणु
	काष्ठा htc_packet *packet, *पंचांगp_packet;

	ath6kl_hअगर_cleanup_scatter(target->dev->ar);

	list_क्रम_each_entry_safe(packet, पंचांगp_packet,
				 &target->मुक्त_ctrl_txbuf, list) अणु
		list_del(&packet->list);
		kमुक्त(packet->buf_start);
		kमुक्त(packet);
	पूर्ण

	list_क्रम_each_entry_safe(packet, पंचांगp_packet,
				 &target->मुक्त_ctrl_rxbuf, list) अणु
		list_del(&packet->list);
		kमुक्त(packet->buf_start);
		kमुक्त(packet);
	पूर्ण

	kमुक्त(target->dev);
	kमुक्त(target);
पूर्ण

अटल स्थिर काष्ठा ath6kl_htc_ops ath6kl_htc_mbox_ops = अणु
	.create = ath6kl_htc_mbox_create,
	.रुको_target = ath6kl_htc_mbox_रुको_target,
	.start = ath6kl_htc_mbox_start,
	.conn_service = ath6kl_htc_mbox_conn_service,
	.tx = ath6kl_htc_mbox_tx,
	.stop = ath6kl_htc_mbox_stop,
	.cleanup = ath6kl_htc_mbox_cleanup,
	.flush_txep = ath6kl_htc_mbox_flush_txep,
	.flush_rx_buf = ath6kl_htc_mbox_flush_rx_buf,
	.activity_changed = ath6kl_htc_mbox_activity_changed,
	.get_rxbuf_num = ath6kl_htc_mbox_get_rxbuf_num,
	.add_rxbuf_multiple = ath6kl_htc_mbox_add_rxbuf_multiple,
	.credit_setup = ath6kl_htc_mbox_credit_setup,
पूर्ण;

व्योम ath6kl_htc_mbox_attach(काष्ठा ath6kl *ar)
अणु
	ar->htc_ops = &ath6kl_htc_mbox_ops;
पूर्ण
