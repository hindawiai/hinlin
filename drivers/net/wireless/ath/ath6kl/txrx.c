<शैली गुरु>
/*
 * Copyright (c) 2004-2011 Atheros Communications Inc.
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

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "core.h"
#समावेश "debug.h"
#समावेश "htc-ops.h"
#समावेश "trace.h"

/*
 * tid - tid_mux0..tid_mux3
 * aid - tid_mux4..tid_mux7
 */
#घोषणा ATH6KL_TID_MASK 0xf
#घोषणा ATH6KL_AID_SHIFT 4

अटल अंतरभूत u8 ath6kl_get_tid(u8 tid_mux)
अणु
	वापस tid_mux & ATH6KL_TID_MASK;
पूर्ण

अटल अंतरभूत u8 ath6kl_get_aid(u8 tid_mux)
अणु
	वापस tid_mux >> ATH6KL_AID_SHIFT;
पूर्ण

अटल u8 ath6kl_ibss_map_epid(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			       u32 *map_no)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(dev);
	काष्ठा ethhdr *eth_hdr;
	u32 i, ep_map = -1;
	u8 *datap;

	*map_no = 0;
	datap = skb->data;
	eth_hdr = (काष्ठा ethhdr *) (datap + माप(काष्ठा wmi_data_hdr));

	अगर (is_multicast_ether_addr(eth_hdr->h_dest))
		वापस ENDPOINT_2;

	क्रम (i = 0; i < ar->node_num; i++) अणु
		अगर (स_भेद(eth_hdr->h_dest, ar->node_map[i].mac_addr,
			   ETH_ALEN) == 0) अणु
			*map_no = i + 1;
			ar->node_map[i].tx_pend++;
			वापस ar->node_map[i].ep_id;
		पूर्ण

		अगर ((ep_map == -1) && !ar->node_map[i].tx_pend)
			ep_map = i;
	पूर्ण

	अगर (ep_map == -1) अणु
		ep_map = ar->node_num;
		ar->node_num++;
		अगर (ar->node_num > MAX_NODE_NUM)
			वापस ENDPOINT_UNUSED;
	पूर्ण

	स_नकल(ar->node_map[ep_map].mac_addr, eth_hdr->h_dest, ETH_ALEN);

	क्रम (i = ENDPOINT_2; i <= ENDPOINT_5; i++) अणु
		अगर (!ar->tx_pending[i]) अणु
			ar->node_map[ep_map].ep_id = i;
			अवरोध;
		पूर्ण

		/*
		 * No मुक्त endpoपूर्णांक is available, start redistribution on
		 * the inuse endpoपूर्णांकs.
		 */
		अगर (i == ENDPOINT_5) अणु
			ar->node_map[ep_map].ep_id = ar->next_ep_id;
			ar->next_ep_id++;
			अगर (ar->next_ep_id > ENDPOINT_5)
				ar->next_ep_id = ENDPOINT_2;
		पूर्ण
	पूर्ण

	*map_no = ep_map + 1;
	ar->node_map[ep_map].tx_pend++;

	वापस ar->node_map[ep_map].ep_id;
पूर्ण

अटल bool ath6kl_process_uapsdq(काष्ठा ath6kl_sta *conn,
				काष्ठा ath6kl_vअगर *vअगर,
				काष्ठा sk_buff *skb,
				u32 *flags)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;
	bool is_apsdq_empty = false;
	काष्ठा ethhdr *datap = (काष्ठा ethhdr *) skb->data;
	u8 up = 0, traffic_class, *ip_hdr;
	u16 ether_type;
	काष्ठा ath6kl_llc_snap_hdr *llc_hdr;

	अगर (conn->sta_flags & STA_PS_APSD_TRIGGER) अणु
		/*
		 * This tx is because of a uAPSD trigger, determine
		 * more and EOSP bit. Set EOSP अगर queue is empty
		 * or sufficient frames are delivered क्रम this trigger.
		 */
		spin_lock_bh(&conn->psq_lock);
		अगर (!skb_queue_empty(&conn->apsdq))
			*flags |= WMI_DATA_HDR_FLAGS_MORE;
		अन्यथा अगर (conn->sta_flags & STA_PS_APSD_EOSP)
			*flags |= WMI_DATA_HDR_FLAGS_EOSP;
		*flags |= WMI_DATA_HDR_FLAGS_UAPSD;
		spin_unlock_bh(&conn->psq_lock);
		वापस false;
	पूर्ण अन्यथा अगर (!conn->apsd_info) अणु
		वापस false;
	पूर्ण

	अगर (test_bit(WMM_ENABLED, &vअगर->flags)) अणु
		ether_type = be16_to_cpu(datap->h_proto);
		अगर (is_ethertype(ether_type)) अणु
			/* packet is in DIX क्रमmat  */
			ip_hdr = (u8 *)(datap + 1);
		पूर्ण अन्यथा अणु
			/* packet is in 802.3 क्रमmat */
			llc_hdr = (काष्ठा ath6kl_llc_snap_hdr *)
							(datap + 1);
			ether_type = be16_to_cpu(llc_hdr->eth_type);
			ip_hdr = (u8 *)(llc_hdr + 1);
		पूर्ण

		अगर (ether_type == IP_ETHERTYPE)
			up = ath6kl_wmi_determine_user_priority(
							ip_hdr, 0);
	पूर्ण

	traffic_class = ath6kl_wmi_get_traffic_class(up);

	अगर ((conn->apsd_info & (1 << traffic_class)) == 0)
		वापस false;

	/* Queue the frames अगर the STA is sleeping */
	spin_lock_bh(&conn->psq_lock);
	is_apsdq_empty = skb_queue_empty(&conn->apsdq);
	skb_queue_tail(&conn->apsdq, skb);
	spin_unlock_bh(&conn->psq_lock);

	/*
	 * If this is the first pkt getting queued
	 * क्रम this STA, update the PVB क्रम this STA
	 */
	अगर (is_apsdq_empty) अणु
		ath6kl_wmi_set_apsd_bfrd_traf(ar->wmi,
					      vअगर->fw_vअगर_idx,
					      conn->aid, 1, 0);
	पूर्ण
	*flags |= WMI_DATA_HDR_FLAGS_UAPSD;

	वापस true;
पूर्ण

अटल bool ath6kl_process_psq(काष्ठा ath6kl_sta *conn,
				काष्ठा ath6kl_vअगर *vअगर,
				काष्ठा sk_buff *skb,
				u32 *flags)
अणु
	bool is_psq_empty = false;
	काष्ठा ath6kl *ar = vअगर->ar;

	अगर (conn->sta_flags & STA_PS_POLLED) अणु
		spin_lock_bh(&conn->psq_lock);
		अगर (!skb_queue_empty(&conn->psq))
			*flags |= WMI_DATA_HDR_FLAGS_MORE;
		spin_unlock_bh(&conn->psq_lock);
		वापस false;
	पूर्ण

	/* Queue the frames अगर the STA is sleeping */
	spin_lock_bh(&conn->psq_lock);
	is_psq_empty = skb_queue_empty(&conn->psq);
	skb_queue_tail(&conn->psq, skb);
	spin_unlock_bh(&conn->psq_lock);

	/*
	 * If this is the first pkt getting queued
	 * क्रम this STA, update the PVB क्रम this
	 * STA.
	 */
	अगर (is_psq_empty)
		ath6kl_wmi_set_pvb_cmd(ar->wmi,
				       vअगर->fw_vअगर_idx,
				       conn->aid, 1);
	वापस true;
पूर्ण

अटल bool ath6kl_घातersave_ap(काष्ठा ath6kl_vअगर *vअगर, काष्ठा sk_buff *skb,
				u32 *flags)
अणु
	काष्ठा ethhdr *datap = (काष्ठा ethhdr *) skb->data;
	काष्ठा ath6kl_sta *conn = शून्य;
	bool ps_queued = false;
	काष्ठा ath6kl *ar = vअगर->ar;

	अगर (is_multicast_ether_addr(datap->h_dest)) अणु
		u8 ctr = 0;
		bool q_mcast = false;

		क्रम (ctr = 0; ctr < AP_MAX_NUM_STA; ctr++) अणु
			अगर (ar->sta_list[ctr].sta_flags & STA_PS_SLEEP) अणु
				q_mcast = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (q_mcast) अणु
			/*
			 * If this transmit is not because of a Dtim Expiry
			 * q it.
			 */
			अगर (!test_bit(DTIM_EXPIRED, &vअगर->flags)) अणु
				bool is_mcastq_empty = false;

				spin_lock_bh(&ar->mcastpsq_lock);
				is_mcastq_empty =
					skb_queue_empty(&ar->mcastpsq);
				skb_queue_tail(&ar->mcastpsq, skb);
				spin_unlock_bh(&ar->mcastpsq_lock);

				/*
				 * If this is the first Mcast pkt getting
				 * queued indicate to the target to set the
				 * BiपंचांगapControl LSB of the TIM IE.
				 */
				अगर (is_mcastq_empty)
					ath6kl_wmi_set_pvb_cmd(ar->wmi,
							       vअगर->fw_vअगर_idx,
							       MCAST_AID, 1);

				ps_queued = true;
			पूर्ण अन्यथा अणु
				/*
				 * This transmit is because of Dtim expiry.
				 * Determine अगर MoreData bit has to be set.
				 */
				spin_lock_bh(&ar->mcastpsq_lock);
				अगर (!skb_queue_empty(&ar->mcastpsq))
					*flags |= WMI_DATA_HDR_FLAGS_MORE;
				spin_unlock_bh(&ar->mcastpsq_lock);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		conn = ath6kl_find_sta(vअगर, datap->h_dest);
		अगर (!conn) अणु
			dev_kमुक्त_skb(skb);

			/* Inक्रमm the caller that the skb is consumed */
			वापस true;
		पूर्ण

		अगर (conn->sta_flags & STA_PS_SLEEP) अणु
			ps_queued = ath6kl_process_uapsdq(conn,
						vअगर, skb, flags);
			अगर (!(*flags & WMI_DATA_HDR_FLAGS_UAPSD))
				ps_queued = ath6kl_process_psq(conn,
						vअगर, skb, flags);
		पूर्ण
	पूर्ण
	वापस ps_queued;
पूर्ण

/* Tx functions */

पूर्णांक ath6kl_control_tx(व्योम *devt, काष्ठा sk_buff *skb,
		      क्रमागत htc_endpoपूर्णांक_id eid)
अणु
	काष्ठा ath6kl *ar = devt;
	पूर्णांक status = 0;
	काष्ठा ath6kl_cookie *cookie = शून्य;

	trace_ath6kl_wmi_cmd(skb->data, skb->len);

	अगर (WARN_ON_ONCE(ar->state == ATH6KL_STATE_WOW)) अणु
		dev_kमुक्त_skb(skb);
		वापस -EACCES;
	पूर्ण

	अगर (WARN_ON_ONCE(eid == ENDPOINT_UNUSED ||
			 eid >= ENDPOपूर्णांक_उच्च)) अणु
		status = -EINVAL;
		जाओ fail_ctrl_tx;
	पूर्ण

	spin_lock_bh(&ar->lock);

	ath6kl_dbg(ATH6KL_DBG_WLAN_TX,
		   "%s: skb=0x%p, len=0x%x eid =%d\n", __func__,
		   skb, skb->len, eid);

	अगर (test_bit(WMI_CTRL_EP_FULL, &ar->flag) && (eid == ar->ctrl_ep)) अणु
		/*
		 * Control endpoपूर्णांक is full, करोn't allocate resources, we
		 * are just going to drop this packet.
		 */
		cookie = शून्य;
		ath6kl_err("wmi ctrl ep full, dropping pkt : 0x%p, len:%d\n",
			   skb, skb->len);
	पूर्ण अन्यथा अणु
		cookie = ath6kl_alloc_cookie(ar);
	पूर्ण

	अगर (cookie == शून्य) अणु
		spin_unlock_bh(&ar->lock);
		status = -ENOMEM;
		जाओ fail_ctrl_tx;
	पूर्ण

	ar->tx_pending[eid]++;

	अगर (eid != ar->ctrl_ep)
		ar->total_tx_data_pend++;

	spin_unlock_bh(&ar->lock);

	cookie->skb = skb;
	cookie->map_no = 0;
	set_htc_pkt_info(&cookie->htc_pkt, cookie, skb->data, skb->len,
			 eid, ATH6KL_CONTROL_PKT_TAG);
	cookie->htc_pkt.skb = skb;

	/*
	 * This पूर्णांकerface is asynchronous, अगर there is an error, cleanup
	 * will happen in the TX completion callback.
	 */
	ath6kl_htc_tx(ar->htc_target, &cookie->htc_pkt);

	वापस 0;

fail_ctrl_tx:
	dev_kमुक्त_skb(skb);
	वापस status;
पूर्ण

netdev_tx_t ath6kl_data_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ath6kl *ar = ath6kl_priv(dev);
	काष्ठा ath6kl_cookie *cookie = शून्य;
	क्रमागत htc_endpoपूर्णांक_id eid = ENDPOINT_UNUSED;
	काष्ठा ath6kl_vअगर *vअगर = netdev_priv(dev);
	u32 map_no = 0;
	u16 htc_tag = ATH6KL_DATA_PKT_TAG;
	u8 ac = 99; /* initialize to unmapped ac */
	bool chk_adhoc_ps_mapping = false;
	पूर्णांक ret;
	काष्ठा wmi_tx_meta_v2 meta_v2;
	व्योम *meta;
	u8 csum_start = 0, csum_dest = 0, csum = skb->ip_summed;
	u8 meta_ver = 0;
	u32 flags = 0;

	ath6kl_dbg(ATH6KL_DBG_WLAN_TX,
		   "%s: skb=0x%p, data=0x%p, len=0x%x\n", __func__,
		   skb, skb->data, skb->len);

	/* If target is not associated */
	अगर (!test_bit(CONNECTED, &vअगर->flags))
		जाओ fail_tx;

	अगर (WARN_ON_ONCE(ar->state != ATH6KL_STATE_ON))
		जाओ fail_tx;

	अगर (!test_bit(WMI_READY, &ar->flag))
		जाओ fail_tx;

	/* AP mode Power saving processing */
	अगर (vअगर->nw_type == AP_NETWORK) अणु
		अगर (ath6kl_घातersave_ap(vअगर, skb, &flags))
			वापस 0;
	पूर्ण

	अगर (test_bit(WMI_ENABLED, &ar->flag)) अणु
		अगर ((dev->features & NETIF_F_IP_CSUM) &&
		    (csum == CHECKSUM_PARTIAL)) अणु
			csum_start = skb->csum_start -
					(skb_network_header(skb) - skb->head) +
					माप(काष्ठा ath6kl_llc_snap_hdr);
			csum_dest = skb->csum_offset + csum_start;
		पूर्ण

		अगर (skb_cow_head(skb, dev->needed_headroom)) अणु
			dev->stats.tx_dropped++;
			kमुक्त_skb(skb);
			वापस 0;
		पूर्ण

		अगर (ath6kl_wmi_dix_2_करोt3(ar->wmi, skb)) अणु
			ath6kl_err("ath6kl_wmi_dix_2_dot3 failed\n");
			जाओ fail_tx;
		पूर्ण

		अगर ((dev->features & NETIF_F_IP_CSUM) &&
		    (csum == CHECKSUM_PARTIAL)) अणु
			meta_v2.csum_start = csum_start;
			meta_v2.csum_dest = csum_dest;

			/* inकाष्ठा target to calculate checksum */
			meta_v2.csum_flags = WMI_META_V2_FLAG_CSUM_OFFLOAD;
			meta_ver = WMI_META_VERSION_2;
			meta = &meta_v2;
		पूर्ण अन्यथा अणु
			meta_ver = 0;
			meta = शून्य;
		पूर्ण

		ret = ath6kl_wmi_data_hdr_add(ar->wmi, skb,
				DATA_MSGTYPE, flags, 0,
				meta_ver,
				meta, vअगर->fw_vअगर_idx);

		अगर (ret) अणु
			ath6kl_warn("failed to add wmi data header:%d\n"
				, ret);
			जाओ fail_tx;
		पूर्ण

		अगर ((vअगर->nw_type == ADHOC_NETWORK) &&
		    ar->ibss_ps_enable && test_bit(CONNECTED, &vअगर->flags))
			chk_adhoc_ps_mapping = true;
		अन्यथा अणु
			/* get the stream mapping */
			ret = ath6kl_wmi_implicit_create_pstream(ar->wmi,
				    vअगर->fw_vअगर_idx, skb,
				    0, test_bit(WMM_ENABLED, &vअगर->flags), &ac);
			अगर (ret)
				जाओ fail_tx;
		पूर्ण
	पूर्ण अन्यथा अणु
		जाओ fail_tx;
	पूर्ण

	spin_lock_bh(&ar->lock);

	अगर (chk_adhoc_ps_mapping)
		eid = ath6kl_ibss_map_epid(skb, dev, &map_no);
	अन्यथा
		eid = ar->ac2ep_map[ac];

	अगर (eid == 0 || eid == ENDPOINT_UNUSED) अणु
		ath6kl_err("eid %d is not mapped!\n", eid);
		spin_unlock_bh(&ar->lock);
		जाओ fail_tx;
	पूर्ण

	/* allocate resource क्रम this packet */
	cookie = ath6kl_alloc_cookie(ar);

	अगर (!cookie) अणु
		spin_unlock_bh(&ar->lock);
		जाओ fail_tx;
	पूर्ण

	/* update counts जबतक the lock is held */
	ar->tx_pending[eid]++;
	ar->total_tx_data_pend++;

	spin_unlock_bh(&ar->lock);

	अगर (!IS_ALIGNED((अचिन्हित दीर्घ) skb->data - HTC_HDR_LENGTH, 4) &&
	    skb_cloned(skb)) अणु
		/*
		 * We will touch (move the buffer data to align it. Since the
		 * skb buffer is cloned and not only the header is changed, we
		 * have to copy it to allow the changes. Since we are copying
		 * the data here, we may as well align it by reserving suitable
		 * headroom to aव्योम the स_हटाओ in ath6kl_htc_tx_buf_align().
		 */
		काष्ठा sk_buff *nskb;

		nskb = skb_copy_expand(skb, HTC_HDR_LENGTH, 0, GFP_ATOMIC);
		अगर (nskb == शून्य)
			जाओ fail_tx;
		kमुक्त_skb(skb);
		skb = nskb;
	पूर्ण

	cookie->skb = skb;
	cookie->map_no = map_no;
	set_htc_pkt_info(&cookie->htc_pkt, cookie, skb->data, skb->len,
			 eid, htc_tag);
	cookie->htc_pkt.skb = skb;

	ath6kl_dbg_dump(ATH6KL_DBG_RAW_BYTES, __func__, "tx ",
			skb->data, skb->len);

	/*
	 * HTC पूर्णांकerface is asynchronous, अगर this fails, cleanup will
	 * happen in the ath6kl_tx_complete callback.
	 */
	ath6kl_htc_tx(ar->htc_target, &cookie->htc_pkt);

	वापस 0;

fail_tx:
	dev_kमुक्त_skb(skb);

	dev->stats.tx_dropped++;
	dev->stats.tx_पातed_errors++;

	वापस 0;
पूर्ण

/* indicate tx activity or inactivity on a WMI stream */
व्योम ath6kl_indicate_tx_activity(व्योम *devt, u8 traffic_class, bool active)
अणु
	काष्ठा ath6kl *ar = devt;
	क्रमागत htc_endpoपूर्णांक_id eid;
	पूर्णांक i;

	eid = ar->ac2ep_map[traffic_class];

	अगर (!test_bit(WMI_ENABLED, &ar->flag))
		जाओ notअगरy_htc;

	spin_lock_bh(&ar->lock);

	ar->ac_stream_active[traffic_class] = active;

	अगर (active) अणु
		/*
		 * Keep track of the active stream with the highest
		 * priority.
		 */
		अगर (ar->ac_stream_pri_map[traffic_class] >
		    ar->hiac_stream_active_pri)
			/* set the new highest active priority */
			ar->hiac_stream_active_pri =
					ar->ac_stream_pri_map[traffic_class];

	पूर्ण अन्यथा अणु
		/*
		 * We may have to search क्रम the next active stream
		 * that is the highest priority.
		 */
		अगर (ar->hiac_stream_active_pri ==
			ar->ac_stream_pri_map[traffic_class]) अणु
			/*
			 * The highest priority stream just went inactive
			 * reset and search क्रम the "next" highest "active"
			 * priority stream.
			 */
			ar->hiac_stream_active_pri = 0;

			क्रम (i = 0; i < WMM_NUM_AC; i++) अणु
				अगर (ar->ac_stream_active[i] &&
				    (ar->ac_stream_pri_map[i] >
				     ar->hiac_stream_active_pri))
					/*
					 * Set the new highest active
					 * priority.
					 */
					ar->hiac_stream_active_pri =
						ar->ac_stream_pri_map[i];
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_bh(&ar->lock);

notअगरy_htc:
	/* notअगरy HTC, this may cause credit distribution changes */
	ath6kl_htc_activity_changed(ar->htc_target, eid, active);
पूर्ण

क्रमागत htc_send_full_action ath6kl_tx_queue_full(काष्ठा htc_target *target,
					       काष्ठा htc_packet *packet)
अणु
	काष्ठा ath6kl *ar = target->dev->ar;
	काष्ठा ath6kl_vअगर *vअगर;
	क्रमागत htc_endpoपूर्णांक_id endpoपूर्णांक = packet->endpoपूर्णांक;
	क्रमागत htc_send_full_action action = HTC_SEND_FULL_KEEP;

	अगर (endpoपूर्णांक == ar->ctrl_ep) अणु
		/*
		 * Under normal WMI अगर this is getting full, then something
		 * is running rampant the host should not be exhausting the
		 * WMI queue with too many commands the only exception to
		 * this is during testing using endpoपूर्णांकping.
		 */
		set_bit(WMI_CTRL_EP_FULL, &ar->flag);
		ath6kl_err("wmi ctrl ep is full\n");
		ath6kl_recovery_err_notअगरy(ar, ATH6KL_FW_EP_FULL);
		वापस action;
	पूर्ण

	अगर (packet->info.tx.tag == ATH6KL_CONTROL_PKT_TAG)
		वापस action;

	/*
	 * The last MAX_HI_COOKIE_NUM "batch" of cookies are reserved क्रम
	 * the highest active stream.
	 */
	अगर (ar->ac_stream_pri_map[ar->ep2ac_map[endpoपूर्णांक]] <
	    ar->hiac_stream_active_pri &&
	    ar->cookie_count <=
			target->endpoपूर्णांक[endpoपूर्णांक].tx_drop_packet_threshold)
		/*
		 * Give preference to the highest priority stream by
		 * dropping the packets which overflowed.
		 */
		action = HTC_SEND_FULL_DROP;

	/* FIXME: Locking */
	spin_lock_bh(&ar->list_lock);
	list_क्रम_each_entry(vअगर, &ar->vअगर_list, list) अणु
		अगर (vअगर->nw_type == ADHOC_NETWORK ||
		    action != HTC_SEND_FULL_DROP) अणु
			spin_unlock_bh(&ar->list_lock);

			set_bit(NETQ_STOPPED, &vअगर->flags);
			netअगर_stop_queue(vअगर->ndev);

			वापस action;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&ar->list_lock);

	वापस action;
पूर्ण

/* TODO this needs to be looked at */
अटल व्योम ath6kl_tx_clear_node_map(काष्ठा ath6kl_vअगर *vअगर,
				     क्रमागत htc_endpoपूर्णांक_id eid, u32 map_no)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;
	u32 i;

	अगर (vअगर->nw_type != ADHOC_NETWORK)
		वापस;

	अगर (!ar->ibss_ps_enable)
		वापस;

	अगर (eid == ar->ctrl_ep)
		वापस;

	अगर (map_no == 0)
		वापस;

	map_no--;
	ar->node_map[map_no].tx_pend--;

	अगर (ar->node_map[map_no].tx_pend)
		वापस;

	अगर (map_no != (ar->node_num - 1))
		वापस;

	क्रम (i = ar->node_num; i > 0; i--) अणु
		अगर (ar->node_map[i - 1].tx_pend)
			अवरोध;

		स_रखो(&ar->node_map[i - 1], 0,
		       माप(काष्ठा ath6kl_node_mapping));
		ar->node_num--;
	पूर्ण
पूर्ण

व्योम ath6kl_tx_complete(काष्ठा htc_target *target,
			काष्ठा list_head *packet_queue)
अणु
	काष्ठा ath6kl *ar = target->dev->ar;
	काष्ठा sk_buff_head skb_queue;
	काष्ठा htc_packet *packet;
	काष्ठा sk_buff *skb;
	काष्ठा ath6kl_cookie *ath6kl_cookie;
	u32 map_no = 0;
	पूर्णांक status;
	क्रमागत htc_endpoपूर्णांक_id eid;
	bool wake_event = false;
	bool flushing[ATH6KL_VIF_MAX] = अणुfalseपूर्ण;
	u8 अगर_idx;
	काष्ठा ath6kl_vअगर *vअगर;

	skb_queue_head_init(&skb_queue);

	/* lock the driver as we update पूर्णांकernal state */
	spin_lock_bh(&ar->lock);

	/* reap completed packets */
	जबतक (!list_empty(packet_queue)) अणु
		packet = list_first_entry(packet_queue, काष्ठा htc_packet,
					  list);
		list_del(&packet->list);

		अगर (WARN_ON_ONCE(packet->endpoपूर्णांक == ENDPOINT_UNUSED ||
				 packet->endpoपूर्णांक >= ENDPOपूर्णांक_उच्च))
			जारी;

		ath6kl_cookie = (काष्ठा ath6kl_cookie *)packet->pkt_cntxt;
		अगर (WARN_ON_ONCE(!ath6kl_cookie))
			जारी;

		status = packet->status;
		skb = ath6kl_cookie->skb;
		eid = packet->endpoपूर्णांक;
		map_no = ath6kl_cookie->map_no;

		अगर (WARN_ON_ONCE(!skb || !skb->data)) अणु
			dev_kमुक्त_skb(skb);
			ath6kl_मुक्त_cookie(ar, ath6kl_cookie);
			जारी;
		पूर्ण

		__skb_queue_tail(&skb_queue, skb);

		अगर (WARN_ON_ONCE(!status && (packet->act_len != skb->len))) अणु
			ath6kl_मुक्त_cookie(ar, ath6kl_cookie);
			जारी;
		पूर्ण

		ar->tx_pending[eid]--;

		अगर (eid != ar->ctrl_ep)
			ar->total_tx_data_pend--;

		अगर (eid == ar->ctrl_ep) अणु
			अगर (test_bit(WMI_CTRL_EP_FULL, &ar->flag))
				clear_bit(WMI_CTRL_EP_FULL, &ar->flag);

			अगर (ar->tx_pending[eid] == 0)
				wake_event = true;
		पूर्ण

		अगर (eid == ar->ctrl_ep) अणु
			अगर_idx = wmi_cmd_hdr_get_अगर_idx(
				(काष्ठा wmi_cmd_hdr *) packet->buf);
		पूर्ण अन्यथा अणु
			अगर_idx = wmi_data_hdr_get_अगर_idx(
				(काष्ठा wmi_data_hdr *) packet->buf);
		पूर्ण

		vअगर = ath6kl_get_vअगर_by_index(ar, अगर_idx);
		अगर (!vअगर) अणु
			ath6kl_मुक्त_cookie(ar, ath6kl_cookie);
			जारी;
		पूर्ण

		अगर (status) अणु
			अगर (status == -ECANCELED)
				/* a packet was flushed  */
				flushing[अगर_idx] = true;

			vअगर->ndev->stats.tx_errors++;

			अगर (status != -ENOSPC && status != -ECANCELED)
				ath6kl_warn("tx complete error: %d\n", status);

			ath6kl_dbg(ATH6KL_DBG_WLAN_TX,
				   "%s: skb=0x%p data=0x%p len=0x%x eid=%d %s\n",
				   __func__, skb, packet->buf, packet->act_len,
				   eid, "error!");
		पूर्ण अन्यथा अणु
			ath6kl_dbg(ATH6KL_DBG_WLAN_TX,
				   "%s: skb=0x%p data=0x%p len=0x%x eid=%d %s\n",
				   __func__, skb, packet->buf, packet->act_len,
				   eid, "OK");

			flushing[अगर_idx] = false;
			vअगर->ndev->stats.tx_packets++;
			vअगर->ndev->stats.tx_bytes += skb->len;
		पूर्ण

		ath6kl_tx_clear_node_map(vअगर, eid, map_no);

		ath6kl_मुक्त_cookie(ar, ath6kl_cookie);

		अगर (test_bit(NETQ_STOPPED, &vअगर->flags))
			clear_bit(NETQ_STOPPED, &vअगर->flags);
	पूर्ण

	spin_unlock_bh(&ar->lock);

	__skb_queue_purge(&skb_queue);

	/* FIXME: Locking */
	spin_lock_bh(&ar->list_lock);
	list_क्रम_each_entry(vअगर, &ar->vअगर_list, list) अणु
		अगर (test_bit(CONNECTED, &vअगर->flags) &&
		    !flushing[vअगर->fw_vअगर_idx]) अणु
			spin_unlock_bh(&ar->list_lock);
			netअगर_wake_queue(vअगर->ndev);
			spin_lock_bh(&ar->list_lock);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&ar->list_lock);

	अगर (wake_event)
		wake_up(&ar->event_wq);

	वापस;
पूर्ण

व्योम ath6kl_tx_data_cleanup(काष्ठा ath6kl *ar)
अणु
	पूर्णांक i;

	/* flush all the data (non-control) streams */
	क्रम (i = 0; i < WMM_NUM_AC; i++)
		ath6kl_htc_flush_txep(ar->htc_target, ar->ac2ep_map[i],
				      ATH6KL_DATA_PKT_TAG);
पूर्ण

/* Rx functions */

अटल व्योम ath6kl_deliver_frames_to_nw_stack(काष्ठा net_device *dev,
					      काष्ठा sk_buff *skb)
अणु
	अगर (!skb)
		वापस;

	skb->dev = dev;

	अगर (!(skb->dev->flags & IFF_UP)) अणु
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	skb->protocol = eth_type_trans(skb, skb->dev);

	netअगर_rx_ni(skb);
पूर्ण

अटल व्योम ath6kl_alloc_netbufs(काष्ठा sk_buff_head *q, u16 num)
अणु
	काष्ठा sk_buff *skb;

	जबतक (num) अणु
		skb = ath6kl_buf_alloc(ATH6KL_BUFFER_SIZE);
		अगर (!skb) अणु
			ath6kl_err("netbuf allocation failed\n");
			वापस;
		पूर्ण
		skb_queue_tail(q, skb);
		num--;
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *aggr_get_मुक्त_skb(काष्ठा aggr_info *p_aggr)
अणु
	काष्ठा sk_buff *skb = शून्य;

	अगर (skb_queue_len(&p_aggr->rx_amsdu_मुक्तq) <
	    (AGGR_NUM_OF_FREE_NETBUFS >> 2))
		ath6kl_alloc_netbufs(&p_aggr->rx_amsdu_मुक्तq,
				     AGGR_NUM_OF_FREE_NETBUFS);

	skb = skb_dequeue(&p_aggr->rx_amsdu_मुक्तq);

	वापस skb;
पूर्ण

व्योम ath6kl_rx_refill(काष्ठा htc_target *target, क्रमागत htc_endpoपूर्णांक_id endpoपूर्णांक)
अणु
	काष्ठा ath6kl *ar = target->dev->ar;
	काष्ठा sk_buff *skb;
	पूर्णांक rx_buf;
	पूर्णांक n_buf_refill;
	काष्ठा htc_packet *packet;
	काष्ठा list_head queue;

	n_buf_refill = ATH6KL_MAX_RX_BUFFERS -
			  ath6kl_htc_get_rxbuf_num(ar->htc_target, endpoपूर्णांक);

	अगर (n_buf_refill <= 0)
		वापस;

	INIT_LIST_HEAD(&queue);

	ath6kl_dbg(ATH6KL_DBG_WLAN_RX,
		   "%s: providing htc with %d buffers at eid=%d\n",
		   __func__, n_buf_refill, endpoपूर्णांक);

	क्रम (rx_buf = 0; rx_buf < n_buf_refill; rx_buf++) अणु
		skb = ath6kl_buf_alloc(ATH6KL_BUFFER_SIZE);
		अगर (!skb)
			अवरोध;

		packet = (काष्ठा htc_packet *) skb->head;
		अगर (!IS_ALIGNED((अचिन्हित दीर्घ) skb->data, 4)) अणु
			माप_प्रकार len = skb_headlen(skb);
			skb->data = PTR_ALIGN(skb->data - 4, 4);
			skb_set_tail_poपूर्णांकer(skb, len);
		पूर्ण
		set_htc_rxpkt_info(packet, skb, skb->data,
				   ATH6KL_BUFFER_SIZE, endpoपूर्णांक);
		packet->skb = skb;
		list_add_tail(&packet->list, &queue);
	पूर्ण

	अगर (!list_empty(&queue))
		ath6kl_htc_add_rxbuf_multiple(ar->htc_target, &queue);
पूर्ण

व्योम ath6kl_refill_amsdu_rxbufs(काष्ठा ath6kl *ar, पूर्णांक count)
अणु
	काष्ठा htc_packet *packet;
	काष्ठा sk_buff *skb;

	जबतक (count) अणु
		skb = ath6kl_buf_alloc(ATH6KL_AMSDU_BUFFER_SIZE);
		अगर (!skb)
			वापस;

		packet = (काष्ठा htc_packet *) skb->head;
		अगर (!IS_ALIGNED((अचिन्हित दीर्घ) skb->data, 4)) अणु
			माप_प्रकार len = skb_headlen(skb);
			skb->data = PTR_ALIGN(skb->data - 4, 4);
			skb_set_tail_poपूर्णांकer(skb, len);
		पूर्ण
		set_htc_rxpkt_info(packet, skb, skb->data,
				   ATH6KL_AMSDU_BUFFER_SIZE, 0);
		packet->skb = skb;

		spin_lock_bh(&ar->lock);
		list_add_tail(&packet->list, &ar->amsdu_rx_buffer_queue);
		spin_unlock_bh(&ar->lock);
		count--;
	पूर्ण
पूर्ण

/*
 * Callback to allocate a receive buffer क्रम a pending packet. We use a
 * pre-allocated list of buffers of maximum AMSDU size (4K).
 */
काष्ठा htc_packet *ath6kl_alloc_amsdu_rxbuf(काष्ठा htc_target *target,
					    क्रमागत htc_endpoपूर्णांक_id endpoपूर्णांक,
					    पूर्णांक len)
अणु
	काष्ठा ath6kl *ar = target->dev->ar;
	काष्ठा htc_packet *packet = शून्य;
	काष्ठा list_head *pkt_pos;
	पूर्णांक refill_cnt = 0, depth = 0;

	ath6kl_dbg(ATH6KL_DBG_WLAN_RX, "%s: eid=%d, len:%d\n",
		   __func__, endpoपूर्णांक, len);

	अगर ((len <= ATH6KL_BUFFER_SIZE) ||
	    (len > ATH6KL_AMSDU_BUFFER_SIZE))
		वापस शून्य;

	spin_lock_bh(&ar->lock);

	अगर (list_empty(&ar->amsdu_rx_buffer_queue)) अणु
		spin_unlock_bh(&ar->lock);
		refill_cnt = ATH6KL_MAX_AMSDU_RX_BUFFERS;
		जाओ refill_buf;
	पूर्ण

	packet = list_first_entry(&ar->amsdu_rx_buffer_queue,
				  काष्ठा htc_packet, list);
	list_del(&packet->list);
	list_क्रम_each(pkt_pos, &ar->amsdu_rx_buffer_queue)
		depth++;

	refill_cnt = ATH6KL_MAX_AMSDU_RX_BUFFERS - depth;
	spin_unlock_bh(&ar->lock);

	/* set actual endpoपूर्णांक ID */
	packet->endpoपूर्णांक = endpoपूर्णांक;

refill_buf:
	अगर (refill_cnt >= ATH6KL_AMSDU_REFILL_THRESHOLD)
		ath6kl_refill_amsdu_rxbufs(ar, refill_cnt);

	वापस packet;
पूर्ण

अटल व्योम aggr_slice_amsdu(काष्ठा aggr_info *p_aggr,
			     काष्ठा rxtid *rxtid, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *new_skb;
	काष्ठा ethhdr *hdr;
	u16 frame_8023_len, payload_8023_len, mac_hdr_len, amsdu_len;
	u8 *framep;

	mac_hdr_len = माप(काष्ठा ethhdr);
	framep = skb->data + mac_hdr_len;
	amsdu_len = skb->len - mac_hdr_len;

	जबतक (amsdu_len > mac_hdr_len) अणु
		hdr = (काष्ठा ethhdr *) framep;
		payload_8023_len = be16_to_cpu(hdr->h_proto);

		अगर (payload_8023_len < MIN_MSDU_SUBFRAME_PAYLOAD_LEN ||
		    payload_8023_len > MAX_MSDU_SUBFRAME_PAYLOAD_LEN) अणु
			ath6kl_err("802.3 AMSDU frame bound check failed. len %d\n",
				   payload_8023_len);
			अवरोध;
		पूर्ण

		frame_8023_len = payload_8023_len + mac_hdr_len;
		new_skb = aggr_get_मुक्त_skb(p_aggr);
		अगर (!new_skb) अणु
			ath6kl_err("no buffer available\n");
			अवरोध;
		पूर्ण

		स_नकल(new_skb->data, framep, frame_8023_len);
		skb_put(new_skb, frame_8023_len);
		अगर (ath6kl_wmi_करोt3_2_dix(new_skb)) अणु
			ath6kl_err("dot3_2_dix error\n");
			dev_kमुक्त_skb(new_skb);
			अवरोध;
		पूर्ण

		skb_queue_tail(&rxtid->q, new_skb);

		/* Is this the last subframe within this aggregate ? */
		अगर ((amsdu_len - frame_8023_len) == 0)
			अवरोध;

		/* Add the length of A-MSDU subframe padding bytes -
		 * Round to nearest word.
		 */
		frame_8023_len = ALIGN(frame_8023_len, 4);

		framep += frame_8023_len;
		amsdu_len -= frame_8023_len;
	पूर्ण

	dev_kमुक्त_skb(skb);
पूर्ण

अटल व्योम aggr_deque_frms(काष्ठा aggr_info_conn *agg_conn, u8 tid,
			    u16 seq_no, u8 order)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा rxtid *rxtid;
	काष्ठा skb_hold_q *node;
	u16 idx, idx_end, seq_end;
	काष्ठा rxtid_stats *stats;

	rxtid = &agg_conn->rx_tid[tid];
	stats = &agg_conn->stat[tid];

	spin_lock_bh(&rxtid->lock);
	idx = AGGR_WIN_IDX(rxtid->seq_next, rxtid->hold_q_sz);

	/*
	 * idx_end is typically the last possible frame in the winकरोw,
	 * but changes to 'the' seq_no, when BAR comes. If seq_no
	 * is non-zero, we will go up to that and stop.
	 * Note: last seq no in current winकरोw will occupy the same
	 * index position as index that is just previous to start.
	 * An imp poपूर्णांक : अगर win_sz is 7, क्रम seq_no space of 4095,
	 * then, there would be holes when sequence wrap around occurs.
	 * Target should judiciously choose the win_sz, based on
	 * this condition. For 4095, (TID_WINDOW_SZ = 2 x win_sz
	 * 2, 4, 8, 16 win_sz works fine).
	 * We must deque from "idx" to "idx_end", including both.
	 */
	seq_end = seq_no ? seq_no : rxtid->seq_next;
	idx_end = AGGR_WIN_IDX(seq_end, rxtid->hold_q_sz);

	करो अणु
		node = &rxtid->hold_q[idx];
		अगर ((order == 1) && (!node->skb))
			अवरोध;

		अगर (node->skb) अणु
			अगर (node->is_amsdu)
				aggr_slice_amsdu(agg_conn->aggr_info, rxtid,
						 node->skb);
			अन्यथा
				skb_queue_tail(&rxtid->q, node->skb);
			node->skb = शून्य;
		पूर्ण अन्यथा अणु
			stats->num_hole++;
		पूर्ण

		rxtid->seq_next = ATH6KL_NEXT_SEQ_NO(rxtid->seq_next);
		idx = AGGR_WIN_IDX(rxtid->seq_next, rxtid->hold_q_sz);
	पूर्ण जबतक (idx != idx_end);

	spin_unlock_bh(&rxtid->lock);

	stats->num_delivered += skb_queue_len(&rxtid->q);

	जबतक ((skb = skb_dequeue(&rxtid->q)))
		ath6kl_deliver_frames_to_nw_stack(agg_conn->dev, skb);
पूर्ण

अटल bool aggr_process_recv_frm(काष्ठा aggr_info_conn *agg_conn, u8 tid,
				  u16 seq_no,
				  bool is_amsdu, काष्ठा sk_buff *frame)
अणु
	काष्ठा rxtid *rxtid;
	काष्ठा rxtid_stats *stats;
	काष्ठा sk_buff *skb;
	काष्ठा skb_hold_q *node;
	u16 idx, st, cur, end;
	bool is_queued = false;
	u16 extended_end;

	rxtid = &agg_conn->rx_tid[tid];
	stats = &agg_conn->stat[tid];

	stats->num_पूर्णांकo_aggr++;

	अगर (!rxtid->aggr) अणु
		अगर (is_amsdu) अणु
			aggr_slice_amsdu(agg_conn->aggr_info, rxtid, frame);
			is_queued = true;
			stats->num_amsdu++;
			जबतक ((skb = skb_dequeue(&rxtid->q)))
				ath6kl_deliver_frames_to_nw_stack(agg_conn->dev,
								  skb);
		पूर्ण
		वापस is_queued;
	पूर्ण

	/* Check the incoming sequence no, अगर it's in the winकरोw */
	st = rxtid->seq_next;
	cur = seq_no;
	end = (st + rxtid->hold_q_sz-1) & ATH6KL_MAX_SEQ_NO;

	अगर (((st < end) && (cur < st || cur > end)) ||
	    ((st > end) && (cur > end) && (cur < st))) अणु
		extended_end = (end + rxtid->hold_q_sz - 1) &
			ATH6KL_MAX_SEQ_NO;

		अगर (((end < extended_end) &&
		     (cur < end || cur > extended_end)) ||
		    ((end > extended_end) && (cur > extended_end) &&
		     (cur < end))) अणु
			aggr_deque_frms(agg_conn, tid, 0, 0);
			spin_lock_bh(&rxtid->lock);
			अगर (cur >= rxtid->hold_q_sz - 1)
				rxtid->seq_next = cur - (rxtid->hold_q_sz - 1);
			अन्यथा
				rxtid->seq_next = ATH6KL_MAX_SEQ_NO -
						  (rxtid->hold_q_sz - 2 - cur);
			spin_unlock_bh(&rxtid->lock);
		पूर्ण अन्यथा अणु
			/*
			 * Dequeue only those frames that are outside the
			 * new shअगरted winकरोw.
			 */
			अगर (cur >= rxtid->hold_q_sz - 1)
				st = cur - (rxtid->hold_q_sz - 1);
			अन्यथा
				st = ATH6KL_MAX_SEQ_NO -
					(rxtid->hold_q_sz - 2 - cur);

			aggr_deque_frms(agg_conn, tid, st, 0);
		पूर्ण

		stats->num_oow++;
	पूर्ण

	idx = AGGR_WIN_IDX(seq_no, rxtid->hold_q_sz);

	node = &rxtid->hold_q[idx];

	spin_lock_bh(&rxtid->lock);

	/*
	 * Is the cur frame duplicate or something beyond our winकरोw(hold_q
	 * -> which is 2x, alपढ़ोy)?
	 *
	 * 1. Duplicate is easy - drop incoming frame.
	 * 2. Not falling in current sliding winकरोw.
	 *  2a. is the frame_seq_no preceding current tid_seq_no?
	 *      -> drop the frame. perhaps sender did not get our ACK.
	 *         this is taken care of above.
	 *  2b. is the frame_seq_no beyond winकरोw(st, TID_WINDOW_SZ);
	 *      -> Taken care of it above, by moving winकरोw क्रमward.
	 */
	dev_kमुक्त_skb(node->skb);
	stats->num_dups++;

	node->skb = frame;
	is_queued = true;
	node->is_amsdu = is_amsdu;
	node->seq_no = seq_no;

	अगर (node->is_amsdu)
		stats->num_amsdu++;
	अन्यथा
		stats->num_mpdu++;

	spin_unlock_bh(&rxtid->lock);

	aggr_deque_frms(agg_conn, tid, 0, 1);

	अगर (agg_conn->समयr_scheduled)
		वापस is_queued;

	spin_lock_bh(&rxtid->lock);
	क्रम (idx = 0; idx < rxtid->hold_q_sz; idx++) अणु
		अगर (rxtid->hold_q[idx].skb) अणु
			/*
			 * There is a frame in the queue and no
			 * समयr so start a समयr to ensure that
			 * the frame करोesn't reमुख्य stuck
			 * क्रमever.
			 */
			agg_conn->समयr_scheduled = true;
			mod_समयr(&agg_conn->समयr,
				  (jअगरfies + (HZ * AGGR_RX_TIMEOUT) / 1000));
			rxtid->समयr_mon = true;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&rxtid->lock);

	वापस is_queued;
पूर्ण

अटल व्योम ath6kl_uapsd_trigger_frame_rx(काष्ठा ath6kl_vअगर *vअगर,
						 काष्ठा ath6kl_sta *conn)
अणु
	काष्ठा ath6kl *ar = vअगर->ar;
	bool is_apsdq_empty, is_apsdq_empty_at_start;
	u32 num_frames_to_deliver, flags;
	काष्ठा sk_buff *skb = शून्य;

	/*
	 * If the APSD q क्रम this STA is not empty, dequeue and
	 * send a pkt from the head of the q. Also update the
	 * More data bit in the WMI_DATA_HDR अगर there are
	 * more pkts क्रम this STA in the APSD q.
	 * If there are no more pkts क्रम this STA,
	 * update the APSD biपंचांगap क्रम this STA.
	 */

	num_frames_to_deliver = (conn->apsd_info >> ATH6KL_APSD_NUM_OF_AC) &
						    ATH6KL_APSD_FRAME_MASK;
	/*
	 * Number of frames to send in a service period is
	 * indicated by the station
	 * in the QOS_INFO of the association request
	 * If it is zero, send all frames
	 */
	अगर (!num_frames_to_deliver)
		num_frames_to_deliver = ATH6KL_APSD_ALL_FRAME;

	spin_lock_bh(&conn->psq_lock);
	is_apsdq_empty = skb_queue_empty(&conn->apsdq);
	spin_unlock_bh(&conn->psq_lock);
	is_apsdq_empty_at_start = is_apsdq_empty;

	जबतक ((!is_apsdq_empty) && (num_frames_to_deliver)) अणु
		spin_lock_bh(&conn->psq_lock);
		skb = skb_dequeue(&conn->apsdq);
		is_apsdq_empty = skb_queue_empty(&conn->apsdq);
		spin_unlock_bh(&conn->psq_lock);

		/*
		 * Set the STA flag to Trigger delivery,
		 * so that the frame will go out
		 */
		conn->sta_flags |= STA_PS_APSD_TRIGGER;
		num_frames_to_deliver--;

		/* Last frame in the service period, set EOSP or queue empty */
		अगर ((is_apsdq_empty) || (!num_frames_to_deliver))
			conn->sta_flags |= STA_PS_APSD_EOSP;

		ath6kl_data_tx(skb, vअगर->ndev);
		conn->sta_flags &= ~(STA_PS_APSD_TRIGGER);
		conn->sta_flags &= ~(STA_PS_APSD_EOSP);
	पूर्ण

	अगर (is_apsdq_empty) अणु
		अगर (is_apsdq_empty_at_start)
			flags = WMI_AP_APSD_NO_DELIVERY_FRAMES;
		अन्यथा
			flags = 0;

		ath6kl_wmi_set_apsd_bfrd_traf(ar->wmi,
					      vअगर->fw_vअगर_idx,
					      conn->aid, 0, flags);
	पूर्ण

	वापस;
पूर्ण

व्योम ath6kl_rx(काष्ठा htc_target *target, काष्ठा htc_packet *packet)
अणु
	काष्ठा ath6kl *ar = target->dev->ar;
	काष्ठा sk_buff *skb = packet->pkt_cntxt;
	काष्ठा wmi_rx_meta_v2 *meta;
	काष्ठा wmi_data_hdr *dhdr;
	पूर्णांक min_hdr_len;
	u8 meta_type, करोt11_hdr = 0;
	u8 pad_beक्रमe_data_start;
	पूर्णांक status = packet->status;
	क्रमागत htc_endpoपूर्णांक_id ept = packet->endpoपूर्णांक;
	bool is_amsdu, prev_ps, ps_state = false;
	bool trig_state = false;
	काष्ठा ath6kl_sta *conn = शून्य;
	काष्ठा sk_buff *skb1 = शून्य;
	काष्ठा ethhdr *datap = शून्य;
	काष्ठा ath6kl_vअगर *vअगर;
	काष्ठा aggr_info_conn *aggr_conn;
	u16 seq_no, offset;
	u8 tid, अगर_idx;

	ath6kl_dbg(ATH6KL_DBG_WLAN_RX,
		   "%s: ar=0x%p eid=%d, skb=0x%p, data=0x%p, len=0x%x status:%d",
		   __func__, ar, ept, skb, packet->buf,
		   packet->act_len, status);

	अगर (status || packet->act_len < HTC_HDR_LENGTH) अणु
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	skb_put(skb, packet->act_len + HTC_HDR_LENGTH);
	skb_pull(skb, HTC_HDR_LENGTH);

	ath6kl_dbg_dump(ATH6KL_DBG_RAW_BYTES, __func__, "rx ",
			skb->data, skb->len);

	अगर (ept == ar->ctrl_ep) अणु
		अगर (test_bit(WMI_ENABLED, &ar->flag)) अणु
			ath6kl_check_wow_status(ar);
			ath6kl_wmi_control_rx(ar->wmi, skb);
			वापस;
		पूर्ण
		अगर_idx =
		wmi_cmd_hdr_get_अगर_idx((काष्ठा wmi_cmd_hdr *) skb->data);
	पूर्ण अन्यथा अणु
		अगर_idx =
		wmi_data_hdr_get_अगर_idx((काष्ठा wmi_data_hdr *) skb->data);
	पूर्ण

	vअगर = ath6kl_get_vअगर_by_index(ar, अगर_idx);
	अगर (!vअगर) अणु
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	/*
	 * Take lock to protect buffer counts and adaptive घातer throughput
	 * state.
	 */
	spin_lock_bh(&vअगर->अगर_lock);

	vअगर->ndev->stats.rx_packets++;
	vअगर->ndev->stats.rx_bytes += packet->act_len;

	spin_unlock_bh(&vअगर->अगर_lock);

	skb->dev = vअगर->ndev;

	अगर (!test_bit(WMI_ENABLED, &ar->flag)) अणु
		अगर (EPPING_ALIGNMENT_PAD > 0)
			skb_pull(skb, EPPING_ALIGNMENT_PAD);
		ath6kl_deliver_frames_to_nw_stack(vअगर->ndev, skb);
		वापस;
	पूर्ण

	ath6kl_check_wow_status(ar);

	min_hdr_len = माप(काष्ठा ethhdr) + माप(काष्ठा wmi_data_hdr) +
		      माप(काष्ठा ath6kl_llc_snap_hdr);

	dhdr = (काष्ठा wmi_data_hdr *) skb->data;

	/*
	 * In the हाल of AP mode we may receive शून्य data frames
	 * that करो not have LLC hdr. They are 16 bytes in size.
	 * Allow these frames in the AP mode.
	 */
	अगर (vअगर->nw_type != AP_NETWORK &&
	    ((packet->act_len < min_hdr_len) ||
	     (packet->act_len > WMI_MAX_AMSDU_RX_DATA_FRAME_LENGTH))) अणु
		ath6kl_info("frame len is too short or too long\n");
		vअगर->ndev->stats.rx_errors++;
		vअगर->ndev->stats.rx_length_errors++;
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	pad_beक्रमe_data_start =
		(le16_to_cpu(dhdr->info3) >> WMI_DATA_HDR_PAD_BEFORE_DATA_SHIFT)
			& WMI_DATA_HDR_PAD_BEFORE_DATA_MASK;

	/* Get the Power save state of the STA */
	अगर (vअगर->nw_type == AP_NETWORK) अणु
		meta_type = wmi_data_hdr_get_meta(dhdr);

		ps_state = !!((dhdr->info >> WMI_DATA_HDR_PS_SHIFT) &
			      WMI_DATA_HDR_PS_MASK);

		offset = माप(काष्ठा wmi_data_hdr) + pad_beक्रमe_data_start;
		trig_state = !!(le16_to_cpu(dhdr->info3) & WMI_DATA_HDR_TRIG);

		चयन (meta_type) अणु
		हाल 0:
			अवरोध;
		हाल WMI_META_VERSION_1:
			offset += माप(काष्ठा wmi_rx_meta_v1);
			अवरोध;
		हाल WMI_META_VERSION_2:
			offset += माप(काष्ठा wmi_rx_meta_v2);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		datap = (काष्ठा ethhdr *) (skb->data + offset);
		conn = ath6kl_find_sta(vअगर, datap->h_source);

		अगर (!conn) अणु
			dev_kमुक्त_skb(skb);
			वापस;
		पूर्ण

		/*
		 * If there is a change in PS state of the STA,
		 * take appropriate steps:
		 *
		 * 1. If Sleep-->Awake, flush the psq क्रम the STA
		 *    Clear the PVB क्रम the STA.
		 * 2. If Awake-->Sleep, Starting queueing frames
		 *    the STA.
		 */
		prev_ps = !!(conn->sta_flags & STA_PS_SLEEP);

		अगर (ps_state)
			conn->sta_flags |= STA_PS_SLEEP;
		अन्यथा
			conn->sta_flags &= ~STA_PS_SLEEP;

		/* Accept trigger only when the station is in sleep */
		अगर ((conn->sta_flags & STA_PS_SLEEP) && trig_state)
			ath6kl_uapsd_trigger_frame_rx(vअगर, conn);

		अगर (prev_ps ^ !!(conn->sta_flags & STA_PS_SLEEP)) अणु
			अगर (!(conn->sta_flags & STA_PS_SLEEP)) अणु
				काष्ठा sk_buff *skbuff = शून्य;
				bool is_apsdq_empty;
				काष्ठा ath6kl_mgmt_buff *mgmt;
				u8 idx;

				spin_lock_bh(&conn->psq_lock);
				जबतक (conn->mgmt_psq_len > 0) अणु
					mgmt = list_first_entry(
							&conn->mgmt_psq,
							काष्ठा ath6kl_mgmt_buff,
							list);
					list_del(&mgmt->list);
					conn->mgmt_psq_len--;
					spin_unlock_bh(&conn->psq_lock);
					idx = vअगर->fw_vअगर_idx;

					ath6kl_wmi_send_mgmt_cmd(ar->wmi,
								 idx,
								 mgmt->id,
								 mgmt->freq,
								 mgmt->रुको,
								 mgmt->buf,
								 mgmt->len,
								 mgmt->no_cck);

					kमुक्त(mgmt);
					spin_lock_bh(&conn->psq_lock);
				पूर्ण
				conn->mgmt_psq_len = 0;
				जबतक ((skbuff = skb_dequeue(&conn->psq))) अणु
					spin_unlock_bh(&conn->psq_lock);
					ath6kl_data_tx(skbuff, vअगर->ndev);
					spin_lock_bh(&conn->psq_lock);
				पूर्ण

				is_apsdq_empty = skb_queue_empty(&conn->apsdq);
				जबतक ((skbuff = skb_dequeue(&conn->apsdq))) अणु
					spin_unlock_bh(&conn->psq_lock);
					ath6kl_data_tx(skbuff, vअगर->ndev);
					spin_lock_bh(&conn->psq_lock);
				पूर्ण
				spin_unlock_bh(&conn->psq_lock);

				अगर (!is_apsdq_empty)
					ath6kl_wmi_set_apsd_bfrd_traf(
							ar->wmi,
							vअगर->fw_vअगर_idx,
							conn->aid, 0, 0);

				/* Clear the PVB क्रम this STA */
				ath6kl_wmi_set_pvb_cmd(ar->wmi, vअगर->fw_vअगर_idx,
						       conn->aid, 0);
			पूर्ण
		पूर्ण

		/* drop शून्य data frames here */
		अगर ((packet->act_len < min_hdr_len) ||
		    (packet->act_len >
		     WMI_MAX_AMSDU_RX_DATA_FRAME_LENGTH)) अणु
			dev_kमुक्त_skb(skb);
			वापस;
		पूर्ण
	पूर्ण

	is_amsdu = wmi_data_hdr_is_amsdu(dhdr) ? true : false;
	tid = wmi_data_hdr_get_up(dhdr);
	seq_no = wmi_data_hdr_get_seqno(dhdr);
	meta_type = wmi_data_hdr_get_meta(dhdr);
	करोt11_hdr = wmi_data_hdr_get_करोt11(dhdr);

	skb_pull(skb, माप(काष्ठा wmi_data_hdr));

	चयन (meta_type) अणु
	हाल WMI_META_VERSION_1:
		skb_pull(skb, माप(काष्ठा wmi_rx_meta_v1));
		अवरोध;
	हाल WMI_META_VERSION_2:
		meta = (काष्ठा wmi_rx_meta_v2 *) skb->data;
		अगर (meta->csum_flags & 0x1) अणु
			skb->ip_summed = CHECKSUM_COMPLETE;
			skb->csum = (__क्रमce __wsum) meta->csum;
		पूर्ण
		skb_pull(skb, माप(काष्ठा wmi_rx_meta_v2));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	skb_pull(skb, pad_beक्रमe_data_start);

	अगर (करोt11_hdr)
		status = ath6kl_wmi_करोt11_hdr_हटाओ(ar->wmi, skb);
	अन्यथा अगर (!is_amsdu)
		status = ath6kl_wmi_करोt3_2_dix(skb);

	अगर (status) अणु
		/*
		 * Drop frames that could not be processed (lack of
		 * memory, etc.)
		 */
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	अगर (!(vअगर->ndev->flags & IFF_UP)) अणु
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	अगर (vअगर->nw_type == AP_NETWORK) अणु
		datap = (काष्ठा ethhdr *) skb->data;
		अगर (is_multicast_ether_addr(datap->h_dest))
			/*
			 * Bcast/Mcast frames should be sent to the
			 * OS stack as well as on the air.
			 */
			skb1 = skb_copy(skb, GFP_ATOMIC);
		अन्यथा अणु
			/*
			 * Search क्रम a connected STA with dstMac
			 * as the Mac address. If found send the
			 * frame to it on the air अन्यथा send the
			 * frame up the stack.
			 */
			conn = ath6kl_find_sta(vअगर, datap->h_dest);

			अगर (conn && ar->पूर्णांकra_bss) अणु
				skb1 = skb;
				skb = शून्य;
			पूर्ण अन्यथा अगर (conn && !ar->पूर्णांकra_bss) अणु
				dev_kमुक्त_skb(skb);
				skb = शून्य;
			पूर्ण
		पूर्ण
		अगर (skb1)
			ath6kl_data_tx(skb1, vअगर->ndev);

		अगर (skb == शून्य) अणु
			/* nothing to deliver up the stack */
			वापस;
		पूर्ण
	पूर्ण

	datap = (काष्ठा ethhdr *) skb->data;

	अगर (is_unicast_ether_addr(datap->h_dest)) अणु
		अगर (vअगर->nw_type == AP_NETWORK) अणु
			conn = ath6kl_find_sta(vअगर, datap->h_source);
			अगर (!conn)
				वापस;
			aggr_conn = conn->aggr_conn;
		पूर्ण अन्यथा अणु
			aggr_conn = vअगर->aggr_cntxt->aggr_conn;
		पूर्ण

		अगर (aggr_process_recv_frm(aggr_conn, tid, seq_no,
					  is_amsdu, skb)) अणु
			/* aggregation code will handle the skb */
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (!is_broadcast_ether_addr(datap->h_dest)) अणु
		vअगर->ndev->stats.multicast++;
	पूर्ण

	ath6kl_deliver_frames_to_nw_stack(vअगर->ndev, skb);
पूर्ण

अटल व्योम aggr_समयout(काष्ठा समयr_list *t)
अणु
	u8 i, j;
	काष्ठा aggr_info_conn *aggr_conn = from_समयr(aggr_conn, t, समयr);
	काष्ठा rxtid *rxtid;
	काष्ठा rxtid_stats *stats;

	क्रम (i = 0; i < NUM_OF_TIDS; i++) अणु
		rxtid = &aggr_conn->rx_tid[i];
		stats = &aggr_conn->stat[i];

		अगर (!rxtid->aggr || !rxtid->समयr_mon)
			जारी;

		stats->num_समयouts++;
		ath6kl_dbg(ATH6KL_DBG_AGGR,
			   "aggr timeout (st %d end %d)\n",
			   rxtid->seq_next,
			   ((rxtid->seq_next + rxtid->hold_q_sz-1) &
			    ATH6KL_MAX_SEQ_NO));
		aggr_deque_frms(aggr_conn, i, 0, 0);
	पूर्ण

	aggr_conn->समयr_scheduled = false;

	क्रम (i = 0; i < NUM_OF_TIDS; i++) अणु
		rxtid = &aggr_conn->rx_tid[i];

		अगर (rxtid->aggr && rxtid->hold_q) अणु
			spin_lock_bh(&rxtid->lock);
			क्रम (j = 0; j < rxtid->hold_q_sz; j++) अणु
				अगर (rxtid->hold_q[j].skb) अणु
					aggr_conn->समयr_scheduled = true;
					rxtid->समयr_mon = true;
					अवरोध;
				पूर्ण
			पूर्ण
			spin_unlock_bh(&rxtid->lock);

			अगर (j >= rxtid->hold_q_sz)
				rxtid->समयr_mon = false;
		पूर्ण
	पूर्ण

	अगर (aggr_conn->समयr_scheduled)
		mod_समयr(&aggr_conn->समयr,
			  jअगरfies + msecs_to_jअगरfies(AGGR_RX_TIMEOUT));
पूर्ण

अटल व्योम aggr_delete_tid_state(काष्ठा aggr_info_conn *aggr_conn, u8 tid)
अणु
	काष्ठा rxtid *rxtid;
	काष्ठा rxtid_stats *stats;

	अगर (!aggr_conn || tid >= NUM_OF_TIDS)
		वापस;

	rxtid = &aggr_conn->rx_tid[tid];
	stats = &aggr_conn->stat[tid];

	अगर (rxtid->aggr)
		aggr_deque_frms(aggr_conn, tid, 0, 0);

	rxtid->aggr = false;
	rxtid->समयr_mon = false;
	rxtid->win_sz = 0;
	rxtid->seq_next = 0;
	rxtid->hold_q_sz = 0;

	kमुक्त(rxtid->hold_q);
	rxtid->hold_q = शून्य;

	स_रखो(stats, 0, माप(काष्ठा rxtid_stats));
पूर्ण

व्योम aggr_recv_addba_req_evt(काष्ठा ath6kl_vअगर *vअगर, u8 tid_mux, u16 seq_no,
			     u8 win_sz)
अणु
	काष्ठा ath6kl_sta *sta;
	काष्ठा aggr_info_conn *aggr_conn = शून्य;
	काष्ठा rxtid *rxtid;
	u16 hold_q_size;
	u8 tid, aid;

	अगर (vअगर->nw_type == AP_NETWORK) अणु
		aid = ath6kl_get_aid(tid_mux);
		sta = ath6kl_find_sta_by_aid(vअगर->ar, aid);
		अगर (sta)
			aggr_conn = sta->aggr_conn;
	पूर्ण अन्यथा अणु
		aggr_conn = vअगर->aggr_cntxt->aggr_conn;
	पूर्ण

	अगर (!aggr_conn)
		वापस;

	tid = ath6kl_get_tid(tid_mux);
	अगर (tid >= NUM_OF_TIDS)
		वापस;

	rxtid = &aggr_conn->rx_tid[tid];

	अगर (win_sz < AGGR_WIN_SZ_MIN || win_sz > AGGR_WIN_SZ_MAX)
		ath6kl_dbg(ATH6KL_DBG_WLAN_RX, "%s: win_sz %d, tid %d\n",
			   __func__, win_sz, tid);

	अगर (rxtid->aggr)
		aggr_delete_tid_state(aggr_conn, tid);

	rxtid->seq_next = seq_no;
	hold_q_size = TID_WINDOW_SZ(win_sz) * माप(काष्ठा skb_hold_q);
	rxtid->hold_q = kzalloc(hold_q_size, GFP_KERNEL);
	अगर (!rxtid->hold_q)
		वापस;

	rxtid->win_sz = win_sz;
	rxtid->hold_q_sz = TID_WINDOW_SZ(win_sz);
	अगर (!skb_queue_empty(&rxtid->q))
		वापस;

	rxtid->aggr = true;
पूर्ण

व्योम aggr_conn_init(काष्ठा ath6kl_vअगर *vअगर, काष्ठा aggr_info *aggr_info,
		    काष्ठा aggr_info_conn *aggr_conn)
अणु
	काष्ठा rxtid *rxtid;
	u8 i;

	aggr_conn->aggr_sz = AGGR_SZ_DEFAULT;
	aggr_conn->dev = vअगर->ndev;
	समयr_setup(&aggr_conn->समयr, aggr_समयout, 0);
	aggr_conn->aggr_info = aggr_info;

	aggr_conn->समयr_scheduled = false;

	क्रम (i = 0; i < NUM_OF_TIDS; i++) अणु
		rxtid = &aggr_conn->rx_tid[i];
		rxtid->aggr = false;
		rxtid->समयr_mon = false;
		skb_queue_head_init(&rxtid->q);
		spin_lock_init(&rxtid->lock);
	पूर्ण
पूर्ण

काष्ठा aggr_info *aggr_init(काष्ठा ath6kl_vअगर *vअगर)
अणु
	काष्ठा aggr_info *p_aggr = शून्य;

	p_aggr = kzalloc(माप(काष्ठा aggr_info), GFP_KERNEL);
	अगर (!p_aggr) अणु
		ath6kl_err("failed to alloc memory for aggr_node\n");
		वापस शून्य;
	पूर्ण

	p_aggr->aggr_conn = kzalloc(माप(काष्ठा aggr_info_conn), GFP_KERNEL);
	अगर (!p_aggr->aggr_conn) अणु
		ath6kl_err("failed to alloc memory for connection specific aggr info\n");
		kमुक्त(p_aggr);
		वापस शून्य;
	पूर्ण

	aggr_conn_init(vअगर, p_aggr, p_aggr->aggr_conn);

	skb_queue_head_init(&p_aggr->rx_amsdu_मुक्तq);
	ath6kl_alloc_netbufs(&p_aggr->rx_amsdu_मुक्तq, AGGR_NUM_OF_FREE_NETBUFS);

	वापस p_aggr;
पूर्ण

व्योम aggr_recv_delba_req_evt(काष्ठा ath6kl_vअगर *vअगर, u8 tid_mux)
अणु
	काष्ठा ath6kl_sta *sta;
	काष्ठा rxtid *rxtid;
	काष्ठा aggr_info_conn *aggr_conn = शून्य;
	u8 tid, aid;

	अगर (vअगर->nw_type == AP_NETWORK) अणु
		aid = ath6kl_get_aid(tid_mux);
		sta = ath6kl_find_sta_by_aid(vअगर->ar, aid);
		अगर (sta)
			aggr_conn = sta->aggr_conn;
	पूर्ण अन्यथा अणु
		aggr_conn = vअगर->aggr_cntxt->aggr_conn;
	पूर्ण

	अगर (!aggr_conn)
		वापस;

	tid = ath6kl_get_tid(tid_mux);
	अगर (tid >= NUM_OF_TIDS)
		वापस;

	rxtid = &aggr_conn->rx_tid[tid];

	अगर (rxtid->aggr)
		aggr_delete_tid_state(aggr_conn, tid);
पूर्ण

व्योम aggr_reset_state(काष्ठा aggr_info_conn *aggr_conn)
अणु
	u8 tid;

	अगर (!aggr_conn)
		वापस;

	अगर (aggr_conn->समयr_scheduled) अणु
		del_समयr(&aggr_conn->समयr);
		aggr_conn->समयr_scheduled = false;
	पूर्ण

	क्रम (tid = 0; tid < NUM_OF_TIDS; tid++)
		aggr_delete_tid_state(aggr_conn, tid);
पूर्ण

/* clean up our amsdu buffer list */
व्योम ath6kl_cleanup_amsdu_rxbufs(काष्ठा ath6kl *ar)
अणु
	काष्ठा htc_packet *packet, *पंचांगp_pkt;

	spin_lock_bh(&ar->lock);
	अगर (list_empty(&ar->amsdu_rx_buffer_queue)) अणु
		spin_unlock_bh(&ar->lock);
		वापस;
	पूर्ण

	list_क्रम_each_entry_safe(packet, पंचांगp_pkt, &ar->amsdu_rx_buffer_queue,
				 list) अणु
		list_del(&packet->list);
		spin_unlock_bh(&ar->lock);
		dev_kमुक्त_skb(packet->pkt_cntxt);
		spin_lock_bh(&ar->lock);
	पूर्ण

	spin_unlock_bh(&ar->lock);
पूर्ण

व्योम aggr_module_destroy(काष्ठा aggr_info *aggr_info)
अणु
	अगर (!aggr_info)
		वापस;

	aggr_reset_state(aggr_info->aggr_conn);
	skb_queue_purge(&aggr_info->rx_amsdu_मुक्तq);
	kमुक्त(aggr_info->aggr_conn);
	kमुक्त(aggr_info);
पूर्ण
