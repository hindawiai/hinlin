<शैली गुरु>
/*
 * Copyright (c) 2007-2011 Atheros Communications Inc.
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
#समावेश "debug.h"
#समावेश "hif-ops.h"

#घोषणा HTC_PACKET_CONTAINER_ALLOCATION 32
#घोषणा HTC_CONTROL_BUFFER_SIZE (HTC_MAX_CTRL_MSG_LEN + HTC_HDR_LENGTH)

अटल पूर्णांक ath6kl_htc_pipe_tx(काष्ठा htc_target *handle,
			      काष्ठा htc_packet *packet);
अटल व्योम ath6kl_htc_pipe_cleanup(काष्ठा htc_target *handle);

/* htc pipe tx path */
अटल अंतरभूत व्योम restore_tx_packet(काष्ठा htc_packet *packet)
अणु
	अगर (packet->info.tx.flags & HTC_FLAGS_TX_FIXUP_NETBUF) अणु
		skb_pull(packet->skb, माप(काष्ठा htc_frame_hdr));
		packet->info.tx.flags &= ~HTC_FLAGS_TX_FIXUP_NETBUF;
	पूर्ण
पूर्ण

अटल व्योम करो_send_completion(काष्ठा htc_endpoपूर्णांक *ep,
			       काष्ठा list_head *queue_to_indicate)
अणु
	काष्ठा htc_packet *packet;

	अगर (list_empty(queue_to_indicate)) अणु
		/* nothing to indicate */
		वापस;
	पूर्ण

	अगर (ep->ep_cb.tx_comp_multi != शून्य) अणु
		ath6kl_dbg(ATH6KL_DBG_HTC,
			   "%s: calling ep %d, send complete multiple callback (%d pkts)\n",
			   __func__, ep->eid,
			   get_queue_depth(queue_to_indicate));
		/*
		 * a multiple send complete handler is being used,
		 * pass the queue to the handler
		 */
		ep->ep_cb.tx_comp_multi(ep->target, queue_to_indicate);
		/*
		 * all packets are now owned by the callback,
		 * reset queue to be safe
		 */
		INIT_LIST_HEAD(queue_to_indicate);
	पूर्ण अन्यथा अणु
		/* using legacy EpTxComplete */
		करो अणु
			packet = list_first_entry(queue_to_indicate,
						  काष्ठा htc_packet, list);

			list_del(&packet->list);
			ath6kl_dbg(ATH6KL_DBG_HTC,
				   "%s: calling ep %d send complete callback on packet 0x%p\n",
				   __func__, ep->eid, packet);
			ep->ep_cb.tx_complete(ep->target, packet);
		पूर्ण जबतक (!list_empty(queue_to_indicate));
	पूर्ण
पूर्ण

अटल व्योम send_packet_completion(काष्ठा htc_target *target,
				   काष्ठा htc_packet *packet)
अणु
	काष्ठा htc_endpoपूर्णांक *ep = &target->endpoपूर्णांक[packet->endpoपूर्णांक];
	काष्ठा list_head container;

	restore_tx_packet(packet);
	INIT_LIST_HEAD(&container);
	list_add_tail(&packet->list, &container);

	/* करो completion */
	करो_send_completion(ep, &container);
पूर्ण

अटल व्योम get_htc_packet_credit_based(काष्ठा htc_target *target,
					काष्ठा htc_endpoपूर्णांक *ep,
					काष्ठा list_head *queue)
अणु
	पूर्णांक credits_required;
	पूर्णांक reमुख्यder;
	u8 send_flags;
	काष्ठा htc_packet *packet;
	अचिन्हित पूर्णांक transfer_len;

	/* NOTE : the TX lock is held when this function is called */

	/* loop until we can grab as many packets out of the queue as we can */
	जबतक (true) अणु
		send_flags = 0;
		अगर (list_empty(&ep->txq))
			अवरोध;

		/* get packet at head, but करोn't हटाओ it */
		packet = list_first_entry(&ep->txq, काष्ठा htc_packet, list);

		ath6kl_dbg(ATH6KL_DBG_HTC,
			   "%s: got head packet:0x%p , queue depth: %d\n",
			   __func__, packet, get_queue_depth(&ep->txq));

		transfer_len = packet->act_len + HTC_HDR_LENGTH;

		अगर (transfer_len <= target->tgt_cred_sz) अणु
			credits_required = 1;
		पूर्ण अन्यथा अणु
			/* figure out how many credits this message requires */
			credits_required = transfer_len / target->tgt_cred_sz;
			reमुख्यder = transfer_len % target->tgt_cred_sz;

			अगर (reमुख्यder)
				credits_required++;
		पूर्ण

		ath6kl_dbg(ATH6KL_DBG_HTC, "%s: creds required:%d got:%d\n",
			   __func__, credits_required, ep->cred_dist.credits);

		अगर (ep->eid == ENDPOINT_0) अणु
			/*
			 * endpoपूर्णांक 0 is special, it always has a credit and
			 * करोes not require credit based flow control
			 */
			credits_required = 0;

		पूर्ण अन्यथा अणु
			अगर (ep->cred_dist.credits < credits_required)
				अवरोध;

			ep->cred_dist.credits -= credits_required;
			ep->ep_st.cred_cosumd += credits_required;

			/* check अगर we need credits back from the target */
			अगर (ep->cred_dist.credits <
					ep->cred_dist.cred_per_msg) अणु
				/* tell the target we need credits ASAP! */
				send_flags |= HTC_FLAGS_NEED_CREDIT_UPDATE;
				ep->ep_st.cred_low_indicate += 1;
				ath6kl_dbg(ATH6KL_DBG_HTC,
					   "%s: host needs credits\n",
					   __func__);
			पूर्ण
		पूर्ण

		/* now we can fully dequeue */
		packet = list_first_entry(&ep->txq, काष्ठा htc_packet, list);

		list_del(&packet->list);
		/* save the number of credits this packet consumed */
		packet->info.tx.cred_used = credits_required;
		/* save send flags */
		packet->info.tx.flags = send_flags;
		packet->info.tx.seqno = ep->seqno;
		ep->seqno++;
		/* queue this packet पूर्णांकo the caller's queue */
		list_add_tail(&packet->list, queue);
	पूर्ण
पूर्ण

अटल व्योम get_htc_packet(काष्ठा htc_target *target,
			   काष्ठा htc_endpoपूर्णांक *ep,
			   काष्ठा list_head *queue, पूर्णांक resources)
अणु
	काष्ठा htc_packet *packet;

	/* NOTE : the TX lock is held when this function is called */

	/* loop until we can grab as many packets out of the queue as we can */
	जबतक (resources) अणु
		अगर (list_empty(&ep->txq))
			अवरोध;

		packet = list_first_entry(&ep->txq, काष्ठा htc_packet, list);
		list_del(&packet->list);

		ath6kl_dbg(ATH6KL_DBG_HTC,
			   "%s: got packet:0x%p , new queue depth: %d\n",
			   __func__, packet, get_queue_depth(&ep->txq));
		packet->info.tx.seqno = ep->seqno;
		packet->info.tx.flags = 0;
		packet->info.tx.cred_used = 0;
		ep->seqno++;

		/* queue this packet पूर्णांकo the caller's queue */
		list_add_tail(&packet->list, queue);
		resources--;
	पूर्ण
पूर्ण

अटल पूर्णांक htc_issue_packets(काष्ठा htc_target *target,
			     काष्ठा htc_endpoपूर्णांक *ep,
			     काष्ठा list_head *pkt_queue)
अणु
	पूर्णांक status = 0;
	u16 payload_len;
	काष्ठा sk_buff *skb;
	काष्ठा htc_frame_hdr *htc_hdr;
	काष्ठा htc_packet *packet;

	ath6kl_dbg(ATH6KL_DBG_HTC,
		   "%s: queue: 0x%p, pkts %d\n", __func__,
		   pkt_queue, get_queue_depth(pkt_queue));

	जबतक (!list_empty(pkt_queue)) अणु
		packet = list_first_entry(pkt_queue, काष्ठा htc_packet, list);
		list_del(&packet->list);

		skb = packet->skb;
		अगर (!skb) अणु
			WARN_ON_ONCE(1);
			status = -EINVAL;
			अवरोध;
		पूर्ण

		payload_len = packet->act_len;

		/* setup HTC frame header */
		htc_hdr = skb_push(skb, माप(*htc_hdr));
		अगर (!htc_hdr) अणु
			WARN_ON_ONCE(1);
			status = -EINVAL;
			अवरोध;
		पूर्ण

		packet->info.tx.flags |= HTC_FLAGS_TX_FIXUP_NETBUF;

		/* Endianess? */
		put_unaligned((u16) payload_len, &htc_hdr->payld_len);
		htc_hdr->flags = packet->info.tx.flags;
		htc_hdr->eid = (u8) packet->endpoपूर्णांक;
		htc_hdr->ctrl[0] = 0;
		htc_hdr->ctrl[1] = (u8) packet->info.tx.seqno;

		spin_lock_bh(&target->tx_lock);

		/* store in look up queue to match completions */
		list_add_tail(&packet->list, &ep->pipe.tx_lookup_queue);
		ep->ep_st.tx_issued += 1;
		spin_unlock_bh(&target->tx_lock);

		status = ath6kl_hअगर_pipe_send(target->dev->ar,
					      ep->pipe.pipeid_ul, शून्य, skb);

		अगर (status != 0) अणु
			अगर (status != -ENOMEM) अणु
				/* TODO: अगर more than 1 endpoपूर्णांक maps to the
				 * same PipeID, it is possible to run out of
				 * resources in the HIF layer.
				 * Don't emit the error
				 */
				ath6kl_dbg(ATH6KL_DBG_HTC,
					   "%s: failed status:%d\n",
					   __func__, status);
			पूर्ण
			spin_lock_bh(&target->tx_lock);
			list_del(&packet->list);

			/* reclaim credits */
			ep->cred_dist.credits += packet->info.tx.cred_used;
			spin_unlock_bh(&target->tx_lock);

			/* put it back पूर्णांकo the callers queue */
			list_add(&packet->list, pkt_queue);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (status != 0) अणु
		जबतक (!list_empty(pkt_queue)) अणु
			अगर (status != -ENOMEM) अणु
				ath6kl_dbg(ATH6KL_DBG_HTC,
					   "%s: failed pkt:0x%p status:%d\n",
					   __func__, packet, status);
			पूर्ण

			packet = list_first_entry(pkt_queue,
						  काष्ठा htc_packet, list);
			list_del(&packet->list);
			packet->status = status;
			send_packet_completion(target, packet);
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल क्रमागत htc_send_queue_result htc_try_send(काष्ठा htc_target *target,
					       काष्ठा htc_endpoपूर्णांक *ep,
					       काष्ठा list_head *txq)
अणु
	काष्ठा list_head send_queue;	/* temp queue to hold packets */
	काष्ठा htc_packet *packet, *पंचांगp_pkt;
	काष्ठा ath6kl *ar = target->dev->ar;
	क्रमागत htc_send_full_action action;
	पूर्णांक tx_resources, overflow, txqueue_depth, i, good_pkts;
	u8 pipeid;

	ath6kl_dbg(ATH6KL_DBG_HTC, "%s: (queue:0x%p depth:%d)\n",
		   __func__, txq,
		   (txq == शून्य) ? 0 : get_queue_depth(txq));

	/* init the local send queue */
	INIT_LIST_HEAD(&send_queue);

	/*
	 * txq equals to शून्य means
	 * caller didn't provide a queue, just wants us to
	 * check queues and send
	 */
	अगर (txq != शून्य) अणु
		अगर (list_empty(txq)) अणु
			/* empty queue */
			वापस HTC_SEND_QUEUE_DROP;
		पूर्ण

		spin_lock_bh(&target->tx_lock);
		txqueue_depth = get_queue_depth(&ep->txq);
		spin_unlock_bh(&target->tx_lock);

		अगर (txqueue_depth >= ep->max_txq_depth) अणु
			/* we've alपढ़ोy overflowed */
			overflow = get_queue_depth(txq);
		पूर्ण अन्यथा अणु
			/* get how much we will overflow by */
			overflow = txqueue_depth;
			overflow += get_queue_depth(txq);
			/* get how much we will overflow the TX queue by */
			overflow -= ep->max_txq_depth;
		पूर्ण

		/* अगर overflow is negative or zero, we are okay */
		अगर (overflow > 0) अणु
			ath6kl_dbg(ATH6KL_DBG_HTC,
				   "%s: Endpoint %d, TX queue will overflow :%d, Tx Depth:%d, Max:%d\n",
				   __func__, ep->eid, overflow, txqueue_depth,
				   ep->max_txq_depth);
		पूर्ण
		अगर ((overflow <= 0) ||
		    (ep->ep_cb.tx_full == शून्य)) अणु
			/*
			 * all packets will fit or caller did not provide send
			 * full indication handler -- just move all of them
			 * to the local send_queue object
			 */
			list_splice_tail_init(txq, &send_queue);
		पूर्ण अन्यथा अणु
			good_pkts = get_queue_depth(txq) - overflow;
			अगर (good_pkts < 0) अणु
				WARN_ON_ONCE(1);
				वापस HTC_SEND_QUEUE_DROP;
			पूर्ण

			/* we have overflowed, and a callback is provided */
			/* dequeue all non-overflow packets to the sendqueue */
			क्रम (i = 0; i < good_pkts; i++) अणु
				/* pop off caller's queue */
				packet = list_first_entry(txq,
							  काष्ठा htc_packet,
							  list);
				/* move to local queue */
				list_move_tail(&packet->list, &send_queue);
			पूर्ण

			/*
			 * the caller's queue has all the packets that won't fit
			 * walk through the caller's queue and indicate each to
			 * the send full handler
			 */
			list_क्रम_each_entry_safe(packet, पंचांगp_pkt,
						 txq, list) अणु
				ath6kl_dbg(ATH6KL_DBG_HTC,
					   "%s: Indicate overflowed TX pkts: %p\n",
					   __func__, packet);
				action = ep->ep_cb.tx_full(ep->target, packet);
				अगर (action == HTC_SEND_FULL_DROP) अणु
					/* callback wants the packet dropped */
					ep->ep_st.tx_dropped += 1;

					/* leave this one in the caller's queue
					 * क्रम cleanup */
				पूर्ण अन्यथा अणु
					/* callback wants to keep this packet,
					 * move from caller's queue to the send
					 * queue */
					list_move_tail(&packet->list,
						       &send_queue);
				पूर्ण
			पूर्ण

			अगर (list_empty(&send_queue)) अणु
				/* no packets made it in, caller will cleanup */
				वापस HTC_SEND_QUEUE_DROP;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!ep->pipe.tx_credit_flow_enabled) अणु
		tx_resources =
		    ath6kl_hअगर_pipe_get_मुक्त_queue_number(ar,
							  ep->pipe.pipeid_ul);
	पूर्ण अन्यथा अणु
		tx_resources = 0;
	पूर्ण

	spin_lock_bh(&target->tx_lock);
	अगर (!list_empty(&send_queue)) अणु
		/* transfer packets to tail */
		list_splice_tail_init(&send_queue, &ep->txq);
		अगर (!list_empty(&send_queue)) अणु
			WARN_ON_ONCE(1);
			spin_unlock_bh(&target->tx_lock);
			वापस HTC_SEND_QUEUE_DROP;
		पूर्ण
		INIT_LIST_HEAD(&send_queue);
	पूर्ण

	/* increment tx processing count on entry */
	ep->tx_proc_cnt++;

	अगर (ep->tx_proc_cnt > 1) अणु
		/*
		 * Another thपढ़ो or task is draining the TX queues on this
		 * endpoपूर्णांक that thपढ़ो will reset the tx processing count
		 * when the queue is drained.
		 */
		ep->tx_proc_cnt--;
		spin_unlock_bh(&target->tx_lock);
		वापस HTC_SEND_QUEUE_OK;
	पूर्ण

	/***** beyond this poपूर्णांक only 1 thपढ़ो may enter ******/

	/*
	 * Now drain the endpoपूर्णांक TX queue क्रम transmission as दीर्घ as we have
	 * enough transmit resources.
	 */
	जबतक (true) अणु
		अगर (get_queue_depth(&ep->txq) == 0)
			अवरोध;

		अगर (ep->pipe.tx_credit_flow_enabled) अणु
			/*
			 * Credit based mechanism provides flow control
			 * based on target transmit resource availability,
			 * we assume that the HIF layer will always have
			 * bus resources greater than target transmit
			 * resources.
			 */
			get_htc_packet_credit_based(target, ep, &send_queue);
		पूर्ण अन्यथा अणु
			/*
			 * Get all packets क्रम this endpoपूर्णांक that we can
			 * क्रम this pass.
			 */
			get_htc_packet(target, ep, &send_queue, tx_resources);
		पूर्ण

		अगर (get_queue_depth(&send_queue) == 0) अणु
			/*
			 * Didn't get packets due to out of resources or TX
			 * queue was drained.
			 */
			अवरोध;
		पूर्ण

		spin_unlock_bh(&target->tx_lock);

		/* send what we can */
		htc_issue_packets(target, ep, &send_queue);

		अगर (!ep->pipe.tx_credit_flow_enabled) अणु
			pipeid = ep->pipe.pipeid_ul;
			tx_resources =
			    ath6kl_hअगर_pipe_get_मुक्त_queue_number(ar, pipeid);
		पूर्ण

		spin_lock_bh(&target->tx_lock);
	पूर्ण

	/* करोne with this endpoपूर्णांक, we can clear the count */
	ep->tx_proc_cnt = 0;
	spin_unlock_bh(&target->tx_lock);

	वापस HTC_SEND_QUEUE_OK;
पूर्ण

/* htc control packet manipulation */
अटल व्योम destroy_htc_txctrl_packet(काष्ठा htc_packet *packet)
अणु
	काष्ठा sk_buff *skb;
	skb = packet->skb;
	dev_kमुक्त_skb(skb);
	kमुक्त(packet);
पूर्ण

अटल काष्ठा htc_packet *build_htc_txctrl_packet(व्योम)
अणु
	काष्ठा htc_packet *packet = शून्य;
	काष्ठा sk_buff *skb;

	packet = kzalloc(माप(काष्ठा htc_packet), GFP_KERNEL);
	अगर (packet == शून्य)
		वापस शून्य;

	skb = __dev_alloc_skb(HTC_CONTROL_BUFFER_SIZE, GFP_KERNEL);

	अगर (skb == शून्य) अणु
		kमुक्त(packet);
		वापस शून्य;
	पूर्ण
	packet->skb = skb;

	वापस packet;
पूर्ण

अटल व्योम htc_मुक्त_txctrl_packet(काष्ठा htc_target *target,
				   काष्ठा htc_packet *packet)
अणु
	destroy_htc_txctrl_packet(packet);
पूर्ण

अटल काष्ठा htc_packet *htc_alloc_txctrl_packet(काष्ठा htc_target *target)
अणु
	वापस build_htc_txctrl_packet();
पूर्ण

अटल व्योम htc_txctrl_complete(काष्ठा htc_target *target,
				काष्ठा htc_packet *packet)
अणु
	htc_मुक्त_txctrl_packet(target, packet);
पूर्ण

#घोषणा MAX_MESSAGE_SIZE 1536

अटल पूर्णांक htc_setup_target_buffer_assignments(काष्ठा htc_target *target)
अणु
	पूर्णांक status, credits, credit_per_maxmsg, i;
	काष्ठा htc_pipe_txcredit_alloc *entry;
	अचिन्हित पूर्णांक hअगर_usbaudioclass = 0;

	credit_per_maxmsg = MAX_MESSAGE_SIZE / target->tgt_cred_sz;
	अगर (MAX_MESSAGE_SIZE % target->tgt_cred_sz)
		credit_per_maxmsg++;

	/* TODO, this should be configured by the caller! */

	credits = target->tgt_creds;
	entry = &target->pipe.txcredit_alloc[0];

	status = -ENOMEM;

	/* FIXME: hअगर_usbaudioclass is always zero */
	अगर (hअगर_usbaudioclass) अणु
		ath6kl_dbg(ATH6KL_DBG_HTC,
			   "%s: For USB Audio Class- Total:%d\n",
			   __func__, credits);
		entry++;
		entry++;
		/* Setup VO Service To have Max Credits */
		entry->service_id = WMI_DATA_VO_SVC;
		entry->credit_alloc = (credits - 6);
		अगर (entry->credit_alloc == 0)
			entry->credit_alloc++;

		credits -= (पूर्णांक) entry->credit_alloc;
		अगर (credits <= 0)
			वापस status;

		entry++;
		entry->service_id = WMI_CONTROL_SVC;
		entry->credit_alloc = credit_per_maxmsg;
		credits -= (पूर्णांक) entry->credit_alloc;
		अगर (credits <= 0)
			वापस status;

		/* leftovers go to best efक्रमt */
		entry++;
		entry++;
		entry->service_id = WMI_DATA_BE_SVC;
		entry->credit_alloc = (u8) credits;
		status = 0;
	पूर्ण अन्यथा अणु
		entry++;
		entry->service_id = WMI_DATA_VI_SVC;
		entry->credit_alloc = credits / 4;
		अगर (entry->credit_alloc == 0)
			entry->credit_alloc++;

		credits -= (पूर्णांक) entry->credit_alloc;
		अगर (credits <= 0)
			वापस status;

		entry++;
		entry->service_id = WMI_DATA_VO_SVC;
		entry->credit_alloc = credits / 4;
		अगर (entry->credit_alloc == 0)
			entry->credit_alloc++;

		credits -= (पूर्णांक) entry->credit_alloc;
		अगर (credits <= 0)
			वापस status;

		entry++;
		entry->service_id = WMI_CONTROL_SVC;
		entry->credit_alloc = credit_per_maxmsg;
		credits -= (पूर्णांक) entry->credit_alloc;
		अगर (credits <= 0)
			वापस status;

		entry++;
		entry->service_id = WMI_DATA_BK_SVC;
		entry->credit_alloc = credit_per_maxmsg;
		credits -= (पूर्णांक) entry->credit_alloc;
		अगर (credits <= 0)
			वापस status;

		/* leftovers go to best efक्रमt */
		entry++;
		entry->service_id = WMI_DATA_BE_SVC;
		entry->credit_alloc = (u8) credits;
		status = 0;
	पूर्ण

	अगर (status == 0) अणु
		क्रम (i = 0; i < ENDPOपूर्णांक_उच्च; i++) अणु
			अगर (target->pipe.txcredit_alloc[i].service_id != 0) अणु
				ath6kl_dbg(ATH6KL_DBG_HTC,
					   "HTC Service Index : %d TX : 0x%2.2X : alloc:%d\n",
					   i,
					   target->pipe.txcredit_alloc[i].
					   service_id,
					   target->pipe.txcredit_alloc[i].
					   credit_alloc);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

/* process credit reports and call distribution function */
अटल व्योम htc_process_credit_report(काष्ठा htc_target *target,
				      काष्ठा htc_credit_report *rpt,
				      पूर्णांक num_entries,
				      क्रमागत htc_endpoपूर्णांक_id from_ep)
अणु
	पूर्णांक total_credits = 0, i;
	काष्ठा htc_endpoपूर्णांक *ep;

	/* lock out TX जबतक we update credits */
	spin_lock_bh(&target->tx_lock);

	क्रम (i = 0; i < num_entries; i++, rpt++) अणु
		अगर (rpt->eid >= ENDPOपूर्णांक_उच्च) अणु
			WARN_ON_ONCE(1);
			spin_unlock_bh(&target->tx_lock);
			वापस;
		पूर्ण

		ep = &target->endpoपूर्णांक[rpt->eid];
		ep->cred_dist.credits += rpt->credits;

		अगर (ep->cred_dist.credits && get_queue_depth(&ep->txq)) अणु
			spin_unlock_bh(&target->tx_lock);
			htc_try_send(target, ep, शून्य);
			spin_lock_bh(&target->tx_lock);
		पूर्ण

		total_credits += rpt->credits;
	पूर्ण
	ath6kl_dbg(ATH6KL_DBG_HTC,
		   "Report indicated %d credits to distribute\n",
		   total_credits);

	spin_unlock_bh(&target->tx_lock);
पूर्ण

/* flush endpoपूर्णांक TX queue */
अटल व्योम htc_flush_tx_endpoपूर्णांक(काष्ठा htc_target *target,
				  काष्ठा htc_endpoपूर्णांक *ep, u16 tag)
अणु
	काष्ठा htc_packet *packet;

	spin_lock_bh(&target->tx_lock);
	जबतक (get_queue_depth(&ep->txq)) अणु
		packet = list_first_entry(&ep->txq, काष्ठा htc_packet, list);
		list_del(&packet->list);
		packet->status = 0;
		send_packet_completion(target, packet);
	पूर्ण
	spin_unlock_bh(&target->tx_lock);
पूर्ण

/*
 * In the adapted HIF layer, काष्ठा sk_buff * are passed between HIF and HTC,
 * since upper layers expects काष्ठा htc_packet containers we use the completed
 * skb and lookup it's corresponding HTC packet buffer from a lookup list.
 * This is extra overhead that can be fixed by re-aligning HIF पूर्णांकerfaces with
 * HTC.
 */
अटल काष्ठा htc_packet *htc_lookup_tx_packet(काष्ठा htc_target *target,
					       काष्ठा htc_endpoपूर्णांक *ep,
					       काष्ठा sk_buff *skb)
अणु
	काष्ठा htc_packet *packet, *पंचांगp_pkt, *found_packet = शून्य;

	spin_lock_bh(&target->tx_lock);

	/*
	 * पूर्णांकerate from the front of tx lookup queue
	 * this lookup should be fast since lower layers completes in-order and
	 * so the completed packet should be at the head of the list generally
	 */
	list_क्रम_each_entry_safe(packet, पंचांगp_pkt, &ep->pipe.tx_lookup_queue,
				 list) अणु
		/* check क्रम removal */
		अगर (skb == packet->skb) अणु
			/* found it */
			list_del(&packet->list);
			found_packet = packet;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&target->tx_lock);

	वापस found_packet;
पूर्ण

अटल पूर्णांक ath6kl_htc_pipe_tx_complete(काष्ठा ath6kl *ar, काष्ठा sk_buff *skb)
अणु
	काष्ठा htc_target *target = ar->htc_target;
	काष्ठा htc_frame_hdr *htc_hdr;
	काष्ठा htc_endpoपूर्णांक *ep;
	काष्ठा htc_packet *packet;
	u8 ep_id, *netdata;

	netdata = skb->data;

	htc_hdr = (काष्ठा htc_frame_hdr *) netdata;

	ep_id = htc_hdr->eid;
	ep = &target->endpoपूर्णांक[ep_id];

	packet = htc_lookup_tx_packet(target, ep, skb);
	अगर (packet == शून्य) अणु
		/* may have alपढ़ोy been flushed and मुक्तd */
		ath6kl_err("HTC TX lookup failed!\n");
	पूर्ण अन्यथा अणु
		/* will be giving this buffer back to upper layers */
		packet->status = 0;
		send_packet_completion(target, packet);
	पूर्ण
	skb = शून्य;

	अगर (!ep->pipe.tx_credit_flow_enabled) अणु
		/*
		 * note: when using TX credit flow, the re-checking of queues
		 * happens when credits flow back from the target. in the
		 * non-TX credit हाल, we recheck after the packet completes
		 */
		htc_try_send(target, ep, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक htc_send_packets_multiple(काष्ठा htc_target *target,
				     काष्ठा list_head *pkt_queue)
अणु
	काष्ठा htc_endpoपूर्णांक *ep;
	काष्ठा htc_packet *packet, *पंचांगp_pkt;

	अगर (list_empty(pkt_queue))
		वापस -EINVAL;

	/* get first packet to find out which ep the packets will go पूर्णांकo */
	packet = list_first_entry(pkt_queue, काष्ठा htc_packet, list);

	अगर (packet->endpoपूर्णांक >= ENDPOपूर्णांक_उच्च) अणु
		WARN_ON_ONCE(1);
		वापस -EINVAL;
	पूर्ण
	ep = &target->endpoपूर्णांक[packet->endpoपूर्णांक];

	htc_try_send(target, ep, pkt_queue);

	/* करो completion on any packets that couldn't get in */
	अगर (!list_empty(pkt_queue)) अणु
		list_क्रम_each_entry_safe(packet, पंचांगp_pkt, pkt_queue, list) अणु
			packet->status = -ENOMEM;
		पूर्ण

		करो_send_completion(ep, pkt_queue);
	पूर्ण

	वापस 0;
पूर्ण

/* htc pipe rx path */
अटल काष्ठा htc_packet *alloc_htc_packet_container(काष्ठा htc_target *target)
अणु
	काष्ठा htc_packet *packet;
	spin_lock_bh(&target->rx_lock);

	अगर (target->pipe.htc_packet_pool == शून्य) अणु
		spin_unlock_bh(&target->rx_lock);
		वापस शून्य;
	पूर्ण

	packet = target->pipe.htc_packet_pool;
	target->pipe.htc_packet_pool = (काष्ठा htc_packet *) packet->list.next;

	spin_unlock_bh(&target->rx_lock);

	packet->list.next = शून्य;
	वापस packet;
पूर्ण

अटल व्योम मुक्त_htc_packet_container(काष्ठा htc_target *target,
				      काष्ठा htc_packet *packet)
अणु
	काष्ठा list_head *lh;

	spin_lock_bh(&target->rx_lock);

	अगर (target->pipe.htc_packet_pool == शून्य) अणु
		target->pipe.htc_packet_pool = packet;
		packet->list.next = शून्य;
	पूर्ण अन्यथा अणु
		lh = (काष्ठा list_head *) target->pipe.htc_packet_pool;
		packet->list.next = lh;
		target->pipe.htc_packet_pool = packet;
	पूर्ण

	spin_unlock_bh(&target->rx_lock);
पूर्ण

अटल पूर्णांक htc_process_trailer(काष्ठा htc_target *target, u8 *buffer,
			       पूर्णांक len, क्रमागत htc_endpoपूर्णांक_id from_ep)
अणु
	काष्ठा htc_credit_report *report;
	काष्ठा htc_record_hdr *record;
	u8 *record_buf;
	पूर्णांक status = 0;

	जबतक (len > 0) अणु
		अगर (len < माप(काष्ठा htc_record_hdr)) अणु
			status = -EINVAL;
			अवरोध;
		पूर्ण

		/* these are byte aligned काष्ठाs */
		record = (काष्ठा htc_record_hdr *) buffer;
		len -= माप(काष्ठा htc_record_hdr);
		buffer += माप(काष्ठा htc_record_hdr);

		अगर (record->len > len) अणु
			/* no room left in buffer क्रम record */
			ath6kl_dbg(ATH6KL_DBG_HTC,
				   "invalid length: %d (id:%d) buffer has: %d bytes left\n",
				   record->len, record->rec_id, len);
			status = -EINVAL;
			अवरोध;
		पूर्ण

		/* start of record follows the header */
		record_buf = buffer;

		चयन (record->rec_id) अणु
		हाल HTC_RECORD_CREDITS:
			अगर (record->len < माप(काष्ठा htc_credit_report)) अणु
				WARN_ON_ONCE(1);
				वापस -EINVAL;
			पूर्ण

			report = (काष्ठा htc_credit_report *) record_buf;
			htc_process_credit_report(target, report,
						  record->len / माप(*report),
						  from_ep);
			अवरोध;
		शेष:
			ath6kl_dbg(ATH6KL_DBG_HTC,
				   "unhandled record: id:%d length:%d\n",
				   record->rec_id, record->len);
			अवरोध;
		पूर्ण

		/* advance buffer past this record क्रम next समय around */
		buffer += record->len;
		len -= record->len;
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम करो_recv_completion(काष्ठा htc_endpoपूर्णांक *ep,
			       काष्ठा list_head *queue_to_indicate)
अणु
	काष्ठा htc_packet *packet;

	अगर (list_empty(queue_to_indicate)) अणु
		/* nothing to indicate */
		वापस;
	पूर्ण

	/* using legacy EpRecv */
	जबतक (!list_empty(queue_to_indicate)) अणु
		packet = list_first_entry(queue_to_indicate,
					  काष्ठा htc_packet, list);
		list_del(&packet->list);
		ep->ep_cb.rx(ep->target, packet);
	पूर्ण

	वापस;
पूर्ण

अटल व्योम recv_packet_completion(काष्ठा htc_target *target,
				   काष्ठा htc_endpoपूर्णांक *ep,
				   काष्ठा htc_packet *packet)
अणु
	काष्ठा list_head container;
	INIT_LIST_HEAD(&container);
	list_add_tail(&packet->list, &container);

	/* करो completion */
	करो_recv_completion(ep, &container);
पूर्ण

अटल पूर्णांक ath6kl_htc_pipe_rx_complete(काष्ठा ath6kl *ar, काष्ठा sk_buff *skb,
				       u8 pipeid)
अणु
	काष्ठा htc_target *target = ar->htc_target;
	u8 *netdata, *trailer, hdr_info;
	काष्ठा htc_frame_hdr *htc_hdr;
	u32 netlen, trailerlen = 0;
	काष्ठा htc_packet *packet;
	काष्ठा htc_endpoपूर्णांक *ep;
	u16 payload_len;
	पूर्णांक status = 0;

	/*
	 * ar->htc_target can be शून्य due to a race condition that can occur
	 * during driver initialization(we करो 'ath6kl_hif_power_on' beक्रमe
	 * initializing 'ar->htc_target' via 'ath6kl_htc_create').
	 * 'ath6kl_hif_power_on' assigns 'ath6kl_recv_complete' as
	 * usb_complete_t/callback function क्रम 'usb_fill_bulk_urb'.
	 * Thus the possibility of ar->htc_target being शून्य
	 * via ath6kl_recv_complete -> ath6kl_usb_io_comp_work.
	 */
	अगर (WARN_ON_ONCE(!target)) अणु
		ath6kl_err("Target not yet initialized\n");
		status = -EINVAL;
		जाओ मुक्त_skb;
	पूर्ण


	netdata = skb->data;
	netlen = skb->len;

	htc_hdr = (काष्ठा htc_frame_hdr *) netdata;

	अगर (htc_hdr->eid >= ENDPOपूर्णांक_उच्च) अणु
		ath6kl_dbg(ATH6KL_DBG_HTC,
			   "HTC Rx: invalid EndpointID=%d\n",
			   htc_hdr->eid);
		status = -EINVAL;
		जाओ मुक्त_skb;
	पूर्ण
	ep = &target->endpoपूर्णांक[htc_hdr->eid];

	payload_len = le16_to_cpu(get_unaligned(&htc_hdr->payld_len));

	अगर (netlen < (payload_len + HTC_HDR_LENGTH)) अणु
		ath6kl_dbg(ATH6KL_DBG_HTC,
			   "HTC Rx: insufficient length, got:%d expected =%zu\n",
			   netlen, payload_len + HTC_HDR_LENGTH);
		status = -EINVAL;
		जाओ मुक्त_skb;
	पूर्ण

	/* get flags to check क्रम trailer */
	hdr_info = htc_hdr->flags;
	अगर (hdr_info & HTC_FLG_RX_TRAILER) अणु
		/* extract the trailer length */
		hdr_info = htc_hdr->ctrl[0];
		अगर ((hdr_info < माप(काष्ठा htc_record_hdr)) ||
		    (hdr_info > payload_len)) अणु
			ath6kl_dbg(ATH6KL_DBG_HTC,
				   "invalid header: payloadlen should be %d, CB[0]: %d\n",
				   payload_len, hdr_info);
			status = -EINVAL;
			जाओ मुक्त_skb;
		पूर्ण

		trailerlen = hdr_info;
		/* process trailer after hdr/apps payload */
		trailer = (u8 *) htc_hdr + HTC_HDR_LENGTH +
			payload_len - hdr_info;
		status = htc_process_trailer(target, trailer, hdr_info,
					     htc_hdr->eid);
		अगर (status != 0)
			जाओ मुक्त_skb;
	पूर्ण

	अगर (((पूर्णांक) payload_len - (पूर्णांक) trailerlen) <= 0) अणु
		/* zero length packet with trailer, just drop these */
		जाओ मुक्त_skb;
	पूर्ण

	अगर (htc_hdr->eid == ENDPOINT_0) अणु
		/* handle HTC control message */
		अगर (target->htc_flags & HTC_OP_STATE_SETUP_COMPLETE) अणु
			/*
			 * fatal: target should not send unsolicited
			 * messageson the endpoपूर्णांक 0
			 */
			ath6kl_dbg(ATH6KL_DBG_HTC,
				   "HTC ignores Rx Ctrl after setup complete\n");
			status = -EINVAL;
			जाओ मुक्त_skb;
		पूर्ण

		/* हटाओ HTC header */
		skb_pull(skb, HTC_HDR_LENGTH);

		netdata = skb->data;
		netlen = skb->len;

		spin_lock_bh(&target->rx_lock);

		target->pipe.ctrl_response_valid = true;
		target->pipe.ctrl_response_len = min_t(पूर्णांक, netlen,
						       HTC_MAX_CTRL_MSG_LEN);
		स_नकल(target->pipe.ctrl_response_buf, netdata,
		       target->pipe.ctrl_response_len);

		spin_unlock_bh(&target->rx_lock);

		dev_kमुक्त_skb(skb);
		skb = शून्य;

		जाओ मुक्त_skb;
	पूर्ण

	/*
	 * TODO: the message based HIF architecture allocates net bufs
	 * क्रम recv packets since it bridges that HIF to upper layers,
	 * which expects HTC packets, we क्रमm the packets here
	 */
	packet = alloc_htc_packet_container(target);
	अगर (packet == शून्य) अणु
		status = -ENOMEM;
		जाओ मुक्त_skb;
	पूर्ण

	packet->status = 0;
	packet->endpoपूर्णांक = htc_hdr->eid;
	packet->pkt_cntxt = skb;

	/* TODO: क्रम backwards compatibility */
	packet->buf = skb_push(skb, 0) + HTC_HDR_LENGTH;
	packet->act_len = netlen - HTC_HDR_LENGTH - trailerlen;

	/*
	 * TODO: this is a hack because the driver layer will set the
	 * actual len of the skb again which will just द्विगुन the len
	 */
	skb_trim(skb, 0);

	recv_packet_completion(target, ep, packet);

	/* recover the packet container */
	मुक्त_htc_packet_container(target, packet);
	skb = शून्य;

मुक्त_skb:
	dev_kमुक्त_skb(skb);

	वापस status;
पूर्ण

अटल व्योम htc_flush_rx_queue(काष्ठा htc_target *target,
			       काष्ठा htc_endpoपूर्णांक *ep)
अणु
	काष्ठा list_head container;
	काष्ठा htc_packet *packet;

	spin_lock_bh(&target->rx_lock);

	जबतक (1) अणु
		अगर (list_empty(&ep->rx_bufq))
			अवरोध;

		packet = list_first_entry(&ep->rx_bufq,
					  काष्ठा htc_packet, list);
		list_del(&packet->list);

		spin_unlock_bh(&target->rx_lock);
		packet->status = -ECANCELED;
		packet->act_len = 0;

		ath6kl_dbg(ATH6KL_DBG_HTC,
			   "Flushing RX packet:0x%p, length:%d, ep:%d\n",
			   packet, packet->buf_len,
			   packet->endpoपूर्णांक);

		INIT_LIST_HEAD(&container);
		list_add_tail(&packet->list, &container);

		/* give the packet back */
		करो_recv_completion(ep, &container);
		spin_lock_bh(&target->rx_lock);
	पूर्ण

	spin_unlock_bh(&target->rx_lock);
पूर्ण

/* polling routine to रुको क्रम a control packet to be received */
अटल पूर्णांक htc_रुको_recv_ctrl_message(काष्ठा htc_target *target)
अणु
	पूर्णांक count = HTC_TARGET_RESPONSE_POLL_COUNT;

	जबतक (count > 0) अणु
		spin_lock_bh(&target->rx_lock);

		अगर (target->pipe.ctrl_response_valid) अणु
			target->pipe.ctrl_response_valid = false;
			spin_unlock_bh(&target->rx_lock);
			अवरोध;
		पूर्ण

		spin_unlock_bh(&target->rx_lock);

		count--;

		msleep_पूर्णांकerruptible(HTC_TARGET_RESPONSE_POLL_WAIT);
	पूर्ण

	अगर (count <= 0) अणु
		ath6kl_warn("htc pipe control receive timeout!\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम htc_rxctrl_complete(काष्ठा htc_target *context,
				काष्ठा htc_packet *packet)
अणु
	काष्ठा sk_buff *skb = packet->skb;

	अगर (packet->endpoपूर्णांक == ENDPOINT_0 &&
	    packet->status == -ECANCELED &&
	    skb != शून्य)
		dev_kमुक्त_skb(skb);
पूर्ण

/* htc pipe initialization */
अटल व्योम reset_endpoपूर्णांक_states(काष्ठा htc_target *target)
अणु
	काष्ठा htc_endpoपूर्णांक *ep;
	पूर्णांक i;

	क्रम (i = ENDPOINT_0; i < ENDPOपूर्णांक_उच्च; i++) अणु
		ep = &target->endpoपूर्णांक[i];
		ep->svc_id = 0;
		ep->len_max = 0;
		ep->max_txq_depth = 0;
		ep->eid = i;
		INIT_LIST_HEAD(&ep->txq);
		INIT_LIST_HEAD(&ep->pipe.tx_lookup_queue);
		INIT_LIST_HEAD(&ep->rx_bufq);
		ep->target = target;
		ep->pipe.tx_credit_flow_enabled = true;
	पूर्ण
पूर्ण

/* start HTC, this is called after all services are connected */
अटल पूर्णांक htc_config_target_hअगर_pipe(काष्ठा htc_target *target)
अणु
	वापस 0;
पूर्ण

/* htc service functions */
अटल u8 htc_get_credit_alloc(काष्ठा htc_target *target, u16 service_id)
अणु
	u8 allocation = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ENDPOपूर्णांक_उच्च; i++) अणु
		अगर (target->pipe.txcredit_alloc[i].service_id == service_id)
			allocation =
				target->pipe.txcredit_alloc[i].credit_alloc;
	पूर्ण

	अगर (allocation == 0) अणु
		ath6kl_dbg(ATH6KL_DBG_HTC,
			   "HTC Service TX : 0x%2.2X : allocation is zero!\n",
			   service_id);
	पूर्ण

	वापस allocation;
पूर्ण

अटल पूर्णांक ath6kl_htc_pipe_conn_service(काष्ठा htc_target *target,
		     काष्ठा htc_service_connect_req *conn_req,
		     काष्ठा htc_service_connect_resp *conn_resp)
अणु
	काष्ठा ath6kl *ar = target->dev->ar;
	काष्ठा htc_packet *packet = शून्य;
	काष्ठा htc_conn_service_resp *resp_msg;
	काष्ठा htc_conn_service_msg *conn_msg;
	क्रमागत htc_endpoपूर्णांक_id asचिन्हित_epid = ENDPOपूर्णांक_उच्च;
	bool disable_credit_flowctrl = false;
	अचिन्हित पूर्णांक max_msg_size = 0;
	काष्ठा htc_endpoपूर्णांक *ep;
	पूर्णांक length, status = 0;
	काष्ठा sk_buff *skb;
	u8 tx_alloc;
	u16 flags;

	अगर (conn_req->svc_id == 0) अणु
		WARN_ON_ONCE(1);
		status = -EINVAL;
		जाओ मुक्त_packet;
	पूर्ण

	अगर (conn_req->svc_id == HTC_CTRL_RSVD_SVC) अणु
		/* special हाल क्रम pseuकरो control service */
		asचिन्हित_epid = ENDPOINT_0;
		max_msg_size = HTC_MAX_CTRL_MSG_LEN;
		tx_alloc = 0;

	पूर्ण अन्यथा अणु
		tx_alloc = htc_get_credit_alloc(target, conn_req->svc_id);
		अगर (tx_alloc == 0) अणु
			status = -ENOMEM;
			जाओ मुक्त_packet;
		पूर्ण

		/* allocate a packet to send to the target */
		packet = htc_alloc_txctrl_packet(target);

		अगर (packet == शून्य) अणु
			WARN_ON_ONCE(1);
			status = -ENOMEM;
			जाओ मुक्त_packet;
		पूर्ण

		skb = packet->skb;
		length = माप(काष्ठा htc_conn_service_msg);

		/* assemble connect service message */
		conn_msg = skb_put(skb, length);
		अगर (conn_msg == शून्य) अणु
			WARN_ON_ONCE(1);
			status = -EINVAL;
			जाओ मुक्त_packet;
		पूर्ण

		स_रखो(conn_msg, 0,
		       माप(काष्ठा htc_conn_service_msg));
		conn_msg->msg_id = cpu_to_le16(HTC_MSG_CONN_SVC_ID);
		conn_msg->svc_id = cpu_to_le16(conn_req->svc_id);
		conn_msg->conn_flags = cpu_to_le16(conn_req->conn_flags &
					~HTC_CONN_FLGS_SET_RECV_ALLOC_MASK);

		/* tell target desired recv alloc क्रम this ep */
		flags = tx_alloc << HTC_CONN_FLGS_SET_RECV_ALLOC_SHIFT;
		conn_msg->conn_flags |= cpu_to_le16(flags);

		अगर (conn_req->conn_flags &
		    HTC_CONN_FLGS_DISABLE_CRED_FLOW_CTRL) अणु
			disable_credit_flowctrl = true;
		पूर्ण

		set_htc_pkt_info(packet, शून्य, (u8 *) conn_msg,
				 length,
				 ENDPOINT_0, HTC_SERVICE_TX_PACKET_TAG);

		status = ath6kl_htc_pipe_tx(target, packet);

		/* we करोn't own it anymore */
		packet = शून्य;
		अगर (status != 0)
			जाओ मुक्त_packet;

		/* रुको क्रम response */
		status = htc_रुको_recv_ctrl_message(target);
		अगर (status != 0)
			जाओ मुक्त_packet;

		/* we controlled the buffer creation so it has to be
		 * properly aligned
		 */
		resp_msg = (काष्ठा htc_conn_service_resp *)
		    target->pipe.ctrl_response_buf;

		अगर (resp_msg->msg_id != cpu_to_le16(HTC_MSG_CONN_SVC_RESP_ID) ||
		    (target->pipe.ctrl_response_len < माप(*resp_msg))) अणु
			/* this message is not valid */
			WARN_ON_ONCE(1);
			status = -EINVAL;
			जाओ मुक्त_packet;
		पूर्ण

		ath6kl_dbg(ATH6KL_DBG_TRC,
			   "%s: service 0x%X conn resp: status: %d ep: %d\n",
			   __func__, resp_msg->svc_id, resp_msg->status,
			   resp_msg->eid);

		conn_resp->resp_code = resp_msg->status;
		/* check response status */
		अगर (resp_msg->status != HTC_SERVICE_SUCCESS) अणु
			ath6kl_dbg(ATH6KL_DBG_HTC,
				   "Target failed service 0x%X connect request (status:%d)\n",
				   resp_msg->svc_id, resp_msg->status);
			status = -EINVAL;
			जाओ मुक्त_packet;
		पूर्ण

		asचिन्हित_epid = (क्रमागत htc_endpoपूर्णांक_id) resp_msg->eid;
		max_msg_size = le16_to_cpu(resp_msg->max_msg_sz);
	पूर्ण

	/* the rest are parameter checks so set the error status */
	status = -EINVAL;

	अगर (asचिन्हित_epid >= ENDPOपूर्णांक_उच्च) अणु
		WARN_ON_ONCE(1);
		जाओ मुक्त_packet;
	पूर्ण

	अगर (max_msg_size == 0) अणु
		WARN_ON_ONCE(1);
		जाओ मुक्त_packet;
	पूर्ण

	ep = &target->endpoपूर्णांक[asचिन्हित_epid];
	ep->eid = asचिन्हित_epid;
	अगर (ep->svc_id != 0) अणु
		/* endpoपूर्णांक alपढ़ोy in use! */
		WARN_ON_ONCE(1);
		जाओ मुक्त_packet;
	पूर्ण

	/* वापस asचिन्हित endpoपूर्णांक to caller */
	conn_resp->endpoपूर्णांक = asचिन्हित_epid;
	conn_resp->len_max = max_msg_size;

	/* setup the endpoपूर्णांक */
	ep->svc_id = conn_req->svc_id; /* this marks ep in use */
	ep->max_txq_depth = conn_req->max_txq_depth;
	ep->len_max = max_msg_size;
	ep->cred_dist.credits = tx_alloc;
	ep->cred_dist.cred_sz = target->tgt_cred_sz;
	ep->cred_dist.cred_per_msg = max_msg_size / target->tgt_cred_sz;
	अगर (max_msg_size % target->tgt_cred_sz)
		ep->cred_dist.cred_per_msg++;

	/* copy all the callbacks */
	ep->ep_cb = conn_req->ep_cb;

	/* initialize tx_drop_packet_threshold */
	ep->tx_drop_packet_threshold = MAX_HI_COOKIE_NUM;

	status = ath6kl_hअगर_pipe_map_service(ar, ep->svc_id,
					     &ep->pipe.pipeid_ul,
					     &ep->pipe.pipeid_dl);
	अगर (status != 0)
		जाओ मुक्त_packet;

	ath6kl_dbg(ATH6KL_DBG_HTC,
		   "SVC Ready: 0x%4.4X: ULpipe:%d DLpipe:%d id:%d\n",
		   ep->svc_id, ep->pipe.pipeid_ul,
		   ep->pipe.pipeid_dl, ep->eid);

	अगर (disable_credit_flowctrl && ep->pipe.tx_credit_flow_enabled) अणु
		ep->pipe.tx_credit_flow_enabled = false;
		ath6kl_dbg(ATH6KL_DBG_HTC,
			   "SVC: 0x%4.4X ep:%d TX flow control off\n",
			   ep->svc_id, asचिन्हित_epid);
	पूर्ण

मुक्त_packet:
	अगर (packet != शून्य)
		htc_मुक्त_txctrl_packet(target, packet);
	वापस status;
पूर्ण

/* htc export functions */
अटल व्योम *ath6kl_htc_pipe_create(काष्ठा ath6kl *ar)
अणु
	पूर्णांक status = 0;
	काष्ठा htc_endpoपूर्णांक *ep = शून्य;
	काष्ठा htc_target *target = शून्य;
	काष्ठा htc_packet *packet;
	पूर्णांक i;

	target = kzalloc(माप(काष्ठा htc_target), GFP_KERNEL);
	अगर (target == शून्य) अणु
		ath6kl_err("htc create unable to allocate memory\n");
		status = -ENOMEM;
		जाओ fail_htc_create;
	पूर्ण

	spin_lock_init(&target->htc_lock);
	spin_lock_init(&target->rx_lock);
	spin_lock_init(&target->tx_lock);

	reset_endpoपूर्णांक_states(target);

	क्रम (i = 0; i < HTC_PACKET_CONTAINER_ALLOCATION; i++) अणु
		packet = kzalloc(माप(काष्ठा htc_packet), GFP_KERNEL);

		अगर (packet != शून्य)
			मुक्त_htc_packet_container(target, packet);
	पूर्ण

	target->dev = kzalloc(माप(*target->dev), GFP_KERNEL);
	अगर (!target->dev) अणु
		ath6kl_err("unable to allocate memory\n");
		status = -ENOMEM;
		जाओ fail_htc_create;
	पूर्ण
	target->dev->ar = ar;
	target->dev->htc_cnxt = target;

	/* Get HIF शेष pipe क्रम HTC message exchange */
	ep = &target->endpoपूर्णांक[ENDPOINT_0];

	ath6kl_hअगर_pipe_get_शेष(ar, &ep->pipe.pipeid_ul,
				    &ep->pipe.pipeid_dl);

	वापस target;

fail_htc_create:
	अगर (status != 0) अणु
		अगर (target != शून्य)
			ath6kl_htc_pipe_cleanup(target);

		target = शून्य;
	पूर्ण
	वापस target;
पूर्ण

/* cleanup the HTC instance */
अटल व्योम ath6kl_htc_pipe_cleanup(काष्ठा htc_target *target)
अणु
	काष्ठा htc_packet *packet;

	जबतक (true) अणु
		packet = alloc_htc_packet_container(target);
		अगर (packet == शून्य)
			अवरोध;
		kमुक्त(packet);
	पूर्ण

	kमुक्त(target->dev);

	/* kमुक्त our instance */
	kमुक्त(target);
पूर्ण

अटल पूर्णांक ath6kl_htc_pipe_start(काष्ठा htc_target *target)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा htc_setup_comp_ext_msg *setup;
	काष्ठा htc_packet *packet;

	htc_config_target_hअगर_pipe(target);

	/* allocate a buffer to send */
	packet = htc_alloc_txctrl_packet(target);
	अगर (packet == शून्य) अणु
		WARN_ON_ONCE(1);
		वापस -ENOMEM;
	पूर्ण

	skb = packet->skb;

	/* assemble setup complete message */
	setup = skb_put(skb, माप(*setup));
	स_रखो(setup, 0, माप(काष्ठा htc_setup_comp_ext_msg));
	setup->msg_id = cpu_to_le16(HTC_MSG_SETUP_COMPLETE_EX_ID);

	ath6kl_dbg(ATH6KL_DBG_HTC, "HTC using TX credit flow control\n");

	set_htc_pkt_info(packet, शून्य, (u8 *) setup,
			 माप(काष्ठा htc_setup_comp_ext_msg),
			 ENDPOINT_0, HTC_SERVICE_TX_PACKET_TAG);

	target->htc_flags |= HTC_OP_STATE_SETUP_COMPLETE;

	वापस ath6kl_htc_pipe_tx(target, packet);
पूर्ण

अटल व्योम ath6kl_htc_pipe_stop(काष्ठा htc_target *target)
अणु
	पूर्णांक i;
	काष्ठा htc_endpoपूर्णांक *ep;

	/* cleanup endpoपूर्णांकs */
	क्रम (i = 0; i < ENDPOपूर्णांक_उच्च; i++) अणु
		ep = &target->endpoपूर्णांक[i];
		htc_flush_rx_queue(target, ep);
		htc_flush_tx_endpoपूर्णांक(target, ep, HTC_TX_PACKET_TAG_ALL);
	पूर्ण

	reset_endpoपूर्णांक_states(target);
	target->htc_flags &= ~HTC_OP_STATE_SETUP_COMPLETE;
पूर्ण

अटल पूर्णांक ath6kl_htc_pipe_get_rxbuf_num(काष्ठा htc_target *target,
					 क्रमागत htc_endpoपूर्णांक_id endpoपूर्णांक)
अणु
	पूर्णांक num;

	spin_lock_bh(&target->rx_lock);
	num = get_queue_depth(&(target->endpoपूर्णांक[endpoपूर्णांक].rx_bufq));
	spin_unlock_bh(&target->rx_lock);

	वापस num;
पूर्ण

अटल पूर्णांक ath6kl_htc_pipe_tx(काष्ठा htc_target *target,
			      काष्ठा htc_packet *packet)
अणु
	काष्ठा list_head queue;

	ath6kl_dbg(ATH6KL_DBG_HTC,
		   "%s: endPointId: %d, buffer: 0x%p, length: %d\n",
		   __func__, packet->endpoपूर्णांक, packet->buf,
		   packet->act_len);

	INIT_LIST_HEAD(&queue);
	list_add_tail(&packet->list, &queue);

	वापस htc_send_packets_multiple(target, &queue);
पूर्ण

अटल पूर्णांक ath6kl_htc_pipe_रुको_target(काष्ठा htc_target *target)
अणु
	काष्ठा htc_पढ़ोy_ext_msg *पढ़ोy_msg;
	काष्ठा htc_service_connect_req connect;
	काष्ठा htc_service_connect_resp resp;
	पूर्णांक status = 0;

	status = htc_रुको_recv_ctrl_message(target);

	अगर (status != 0)
		वापस status;

	अगर (target->pipe.ctrl_response_len < माप(*पढ़ोy_msg)) अणु
		ath6kl_warn("invalid htc pipe ready msg len: %d\n",
			    target->pipe.ctrl_response_len);
		वापस -ECOMM;
	पूर्ण

	पढ़ोy_msg = (काष्ठा htc_पढ़ोy_ext_msg *) target->pipe.ctrl_response_buf;

	अगर (पढ़ोy_msg->ver2_0_info.msg_id != cpu_to_le16(HTC_MSG_READY_ID)) अणु
		ath6kl_warn("invalid htc pipe ready msg: 0x%x\n",
			    पढ़ोy_msg->ver2_0_info.msg_id);
		वापस -ECOMM;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_HTC,
		   "Target Ready! : transmit resources : %d size:%d\n",
		   पढ़ोy_msg->ver2_0_info.cred_cnt,
		   पढ़ोy_msg->ver2_0_info.cred_sz);

	target->tgt_creds = le16_to_cpu(पढ़ोy_msg->ver2_0_info.cred_cnt);
	target->tgt_cred_sz = le16_to_cpu(पढ़ोy_msg->ver2_0_info.cred_sz);

	अगर ((target->tgt_creds == 0) || (target->tgt_cred_sz == 0))
		वापस -ECOMM;

	htc_setup_target_buffer_assignments(target);

	/* setup our pseuकरो HTC control endpoपूर्णांक connection */
	स_रखो(&connect, 0, माप(connect));
	स_रखो(&resp, 0, माप(resp));
	connect.ep_cb.tx_complete = htc_txctrl_complete;
	connect.ep_cb.rx = htc_rxctrl_complete;
	connect.max_txq_depth = NUM_CONTROL_TX_BUFFERS;
	connect.svc_id = HTC_CTRL_RSVD_SVC;

	/* connect fake service */
	status = ath6kl_htc_pipe_conn_service(target, &connect, &resp);

	वापस status;
पूर्ण

अटल व्योम ath6kl_htc_pipe_flush_txep(काष्ठा htc_target *target,
				       क्रमागत htc_endpoपूर्णांक_id endpoपूर्णांक, u16 tag)
अणु
	काष्ठा htc_endpoपूर्णांक *ep = &target->endpoपूर्णांक[endpoपूर्णांक];

	अगर (ep->svc_id == 0) अणु
		WARN_ON_ONCE(1);
		/* not in use.. */
		वापस;
	पूर्ण

	htc_flush_tx_endpoपूर्णांक(target, ep, tag);
पूर्ण

अटल पूर्णांक ath6kl_htc_pipe_add_rxbuf_multiple(काष्ठा htc_target *target,
					      काष्ठा list_head *pkt_queue)
अणु
	काष्ठा htc_packet *packet, *पंचांगp_pkt, *first;
	काष्ठा htc_endpoपूर्णांक *ep;
	पूर्णांक status = 0;

	अगर (list_empty(pkt_queue))
		वापस -EINVAL;

	first = list_first_entry(pkt_queue, काष्ठा htc_packet, list);

	अगर (first->endpoपूर्णांक >= ENDPOपूर्णांक_उच्च) अणु
		WARN_ON_ONCE(1);
		वापस -EINVAL;
	पूर्ण

	ath6kl_dbg(ATH6KL_DBG_HTC, "%s: epid: %d, cnt:%d, len: %d\n",
		   __func__, first->endpoपूर्णांक, get_queue_depth(pkt_queue),
		   first->buf_len);

	ep = &target->endpoपूर्णांक[first->endpoपूर्णांक];

	spin_lock_bh(&target->rx_lock);

	/* store receive packets */
	list_splice_tail_init(pkt_queue, &ep->rx_bufq);

	spin_unlock_bh(&target->rx_lock);

	अगर (status != 0) अणु
		/* walk through queue and mark each one canceled */
		list_क्रम_each_entry_safe(packet, पंचांगp_pkt, pkt_queue, list) अणु
			packet->status = -ECANCELED;
		पूर्ण

		करो_recv_completion(ep, pkt_queue);
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम ath6kl_htc_pipe_activity_changed(काष्ठा htc_target *target,
					     क्रमागत htc_endpoपूर्णांक_id ep,
					     bool active)
अणु
	/* TODO */
पूर्ण

अटल व्योम ath6kl_htc_pipe_flush_rx_buf(काष्ठा htc_target *target)
अणु
	काष्ठा htc_endpoपूर्णांक *endpoपूर्णांक;
	काष्ठा htc_packet *packet, *पंचांगp_pkt;
	पूर्णांक i;

	क्रम (i = ENDPOINT_0; i < ENDPOपूर्णांक_उच्च; i++) अणु
		endpoपूर्णांक = &target->endpoपूर्णांक[i];

		spin_lock_bh(&target->rx_lock);

		list_क्रम_each_entry_safe(packet, पंचांगp_pkt,
					 &endpoपूर्णांक->rx_bufq, list) अणु
			list_del(&packet->list);
			spin_unlock_bh(&target->rx_lock);
			ath6kl_dbg(ATH6KL_DBG_HTC,
				   "htc rx flush pkt 0x%p len %d ep %d\n",
				   packet, packet->buf_len,
				   packet->endpoपूर्णांक);
			dev_kमुक्त_skb(packet->pkt_cntxt);
			spin_lock_bh(&target->rx_lock);
		पूर्ण

		spin_unlock_bh(&target->rx_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक ath6kl_htc_pipe_credit_setup(काष्ठा htc_target *target,
					काष्ठा ath6kl_htc_credit_info *info)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ath6kl_htc_ops ath6kl_htc_pipe_ops = अणु
	.create = ath6kl_htc_pipe_create,
	.रुको_target = ath6kl_htc_pipe_रुको_target,
	.start = ath6kl_htc_pipe_start,
	.conn_service = ath6kl_htc_pipe_conn_service,
	.tx = ath6kl_htc_pipe_tx,
	.stop = ath6kl_htc_pipe_stop,
	.cleanup = ath6kl_htc_pipe_cleanup,
	.flush_txep = ath6kl_htc_pipe_flush_txep,
	.flush_rx_buf = ath6kl_htc_pipe_flush_rx_buf,
	.activity_changed = ath6kl_htc_pipe_activity_changed,
	.get_rxbuf_num = ath6kl_htc_pipe_get_rxbuf_num,
	.add_rxbuf_multiple = ath6kl_htc_pipe_add_rxbuf_multiple,
	.credit_setup = ath6kl_htc_pipe_credit_setup,
	.tx_complete = ath6kl_htc_pipe_tx_complete,
	.rx_complete = ath6kl_htc_pipe_rx_complete,
पूर्ण;

व्योम ath6kl_htc_pipe_attach(काष्ठा ath6kl *ar)
अणु
	ar->htc_ops = &ath6kl_htc_pipe_ops;
पूर्ण
