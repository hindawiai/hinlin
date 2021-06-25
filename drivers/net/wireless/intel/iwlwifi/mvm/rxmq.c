<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2015-2017 Intel Deutschland GmbH
 */
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश "iwl-trans.h"
#समावेश "mvm.h"
#समावेश "fw-api.h"

अटल व्योम *iwl_mvm_skb_get_hdr(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_rx_status *rx_status = IEEE80211_SKB_RXCB(skb);
	u8 *data = skb->data;

	/* Alignment concerns */
	BUILD_BUG_ON(माप(काष्ठा ieee80211_radiotap_he) % 4);
	BUILD_BUG_ON(माप(काष्ठा ieee80211_radiotap_he_mu) % 4);
	BUILD_BUG_ON(माप(काष्ठा ieee80211_radiotap_lsig) % 4);
	BUILD_BUG_ON(माप(काष्ठा ieee80211_venकरोr_radiotap) % 4);

	अगर (rx_status->flag & RX_FLAG_RADIOTAP_HE)
		data += माप(काष्ठा ieee80211_radiotap_he);
	अगर (rx_status->flag & RX_FLAG_RADIOTAP_HE_MU)
		data += माप(काष्ठा ieee80211_radiotap_he_mu);
	अगर (rx_status->flag & RX_FLAG_RADIOTAP_LSIG)
		data += माप(काष्ठा ieee80211_radiotap_lsig);
	अगर (rx_status->flag & RX_FLAG_RADIOTAP_VENDOR_DATA) अणु
		काष्ठा ieee80211_venकरोr_radiotap *radiotap = (व्योम *)data;

		data += माप(*radiotap) + radiotap->len + radiotap->pad;
	पूर्ण

	वापस data;
पूर्ण

अटल अंतरभूत पूर्णांक iwl_mvm_check_pn(काष्ठा iwl_mvm *mvm, काष्ठा sk_buff *skb,
				   पूर्णांक queue, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_mvm_sta *mvmsta;
	काष्ठा ieee80211_hdr *hdr = iwl_mvm_skb_get_hdr(skb);
	काष्ठा ieee80211_rx_status *stats = IEEE80211_SKB_RXCB(skb);
	काष्ठा iwl_mvm_key_pn *ptk_pn;
	पूर्णांक res;
	u8 tid, keyidx;
	u8 pn[IEEE80211_CCMP_PN_LEN];
	u8 *extiv;

	/* करो PN checking */

	/* multicast and non-data only arrives on शेष queue */
	अगर (!ieee80211_is_data(hdr->frame_control) ||
	    is_multicast_ether_addr(hdr->addr1))
		वापस 0;

	/* करो not check PN क्रम खोलो AP */
	अगर (!(stats->flag & RX_FLAG_DECRYPTED))
		वापस 0;

	/*
	 * aव्योम checking क्रम शेष queue - we करोn't want to replicate
	 * all the logic that's necessary क्रम checking the PN on fragmented
	 * frames, leave that to mac80211
	 */
	अगर (queue == 0)
		वापस 0;

	/* अगर we are here - this क्रम sure is either CCMP or GCMP */
	अगर (IS_ERR_OR_शून्य(sta)) अणु
		IWL_ERR(mvm,
			"expected hw-decrypted unicast frame for station\n");
		वापस -1;
	पूर्ण

	mvmsta = iwl_mvm_sta_from_mac80211(sta);

	extiv = (u8 *)hdr + ieee80211_hdrlen(hdr->frame_control);
	keyidx = extiv[3] >> 6;

	ptk_pn = rcu_dereference(mvmsta->ptk_pn[keyidx]);
	अगर (!ptk_pn)
		वापस -1;

	अगर (ieee80211_is_data_qos(hdr->frame_control))
		tid = ieee80211_get_tid(hdr);
	अन्यथा
		tid = 0;

	/* we करोn't use HCCA/802.11 QoS TSPECs, so drop such frames */
	अगर (tid >= IWL_MAX_TID_COUNT)
		वापस -1;

	/* load pn */
	pn[0] = extiv[7];
	pn[1] = extiv[6];
	pn[2] = extiv[5];
	pn[3] = extiv[4];
	pn[4] = extiv[1];
	pn[5] = extiv[0];

	res = स_भेद(pn, ptk_pn->q[queue].pn[tid], IEEE80211_CCMP_PN_LEN);
	अगर (res < 0)
		वापस -1;
	अगर (!res && !(stats->flag & RX_FLAG_ALLOW_SAME_PN))
		वापस -1;

	स_नकल(ptk_pn->q[queue].pn[tid], pn, IEEE80211_CCMP_PN_LEN);
	stats->flag |= RX_FLAG_PN_VALIDATED;

	वापस 0;
पूर्ण

/* iwl_mvm_create_skb Adds the rxb to a new skb */
अटल पूर्णांक iwl_mvm_create_skb(काष्ठा iwl_mvm *mvm, काष्ठा sk_buff *skb,
			      काष्ठा ieee80211_hdr *hdr, u16 len, u8 crypt_len,
			      काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_rx_mpdu_desc *desc = (व्योम *)pkt->data;
	अचिन्हित पूर्णांक headlen, fraglen, pad_len = 0;
	अचिन्हित पूर्णांक hdrlen = ieee80211_hdrlen(hdr->frame_control);

	अगर (desc->mac_flags2 & IWL_RX_MPDU_MFLG2_PAD) अणु
		len -= 2;
		pad_len = 2;
	पूर्ण

	/* If frame is small enough to fit in skb->head, pull it completely.
	 * If not, only pull ieee80211_hdr (including crypto अगर present, and
	 * an additional 8 bytes क्रम SNAP/ethertype, see below) so that
	 * splice() or TCP coalesce are more efficient.
	 *
	 * Since, in addition, ieee80211_data_to_8023() always pull in at
	 * least 8 bytes (possibly more क्रम mesh) we can करो the same here
	 * to save the cost of करोing it later. That still करोesn't pull in
	 * the actual IP header since the typical हाल has a SNAP header.
	 * If the latter changes (there are efक्रमts in the standards group
	 * to करो so) we should revisit this and ieee80211_data_to_8023().
	 */
	headlen = (len <= skb_tailroom(skb)) ? len :
					       hdrlen + crypt_len + 8;

	/* The firmware may align the packet to DWORD.
	 * The padding is inserted after the IV.
	 * After copying the header + IV skip the padding अगर
	 * present beक्रमe copying packet data.
	 */
	hdrlen += crypt_len;

	अगर (WARN_ONCE(headlen < hdrlen,
		      "invalid packet lengths (hdrlen=%d, len=%d, crypt_len=%d)\n",
		      hdrlen, len, crypt_len)) अणु
		/*
		 * We warn and trace because we want to be able to see
		 * it in trace-cmd as well.
		 */
		IWL_DEBUG_RX(mvm,
			     "invalid packet lengths (hdrlen=%d, len=%d, crypt_len=%d)\n",
			     hdrlen, len, crypt_len);
		वापस -EINVAL;
	पूर्ण

	skb_put_data(skb, hdr, hdrlen);
	skb_put_data(skb, (u8 *)hdr + hdrlen + pad_len, headlen - hdrlen);

	/*
	 * If we did CHECKSUM_COMPLETE, the hardware only करोes it right क्रम
	 * certain हालs and starts the checksum after the SNAP. Check अगर
	 * this is the हाल - it's easier to just bail out to CHECKSUM_NONE
	 * in the हालs the hardware didn't handle, since it's rare to see
	 * such packets, even though the hardware did calculate the checksum
	 * in this हाल, just starting after the MAC header instead.
	 */
	अगर (skb->ip_summed == CHECKSUM_COMPLETE) अणु
		काष्ठा अणु
			u8 hdr[6];
			__be16 type;
		पूर्ण __packed *shdr = (व्योम *)((u8 *)hdr + hdrlen + pad_len);

		अगर (unlikely(headlen - hdrlen < माप(*shdr) ||
			     !ether_addr_equal(shdr->hdr, rfc1042_header) ||
			     (shdr->type != htons(ETH_P_IP) &&
			      shdr->type != htons(ETH_P_ARP) &&
			      shdr->type != htons(ETH_P_IPV6) &&
			      shdr->type != htons(ETH_P_8021Q) &&
			      shdr->type != htons(ETH_P_PAE) &&
			      shdr->type != htons(ETH_P_TDLS))))
			skb->ip_summed = CHECKSUM_NONE;
	पूर्ण

	fraglen = len - headlen;

	अगर (fraglen) अणु
		पूर्णांक offset = (व्योम *)hdr + headlen + pad_len -
			     rxb_addr(rxb) + rxb_offset(rxb);

		skb_add_rx_frag(skb, 0, rxb_steal_page(rxb), offset,
				fraglen, rxb->truesize);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iwl_mvm_add_rtap_snअगरfer_config(काष्ठा iwl_mvm *mvm,
					    काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_rx_status *rx_status = IEEE80211_SKB_RXCB(skb);
	काष्ठा ieee80211_venकरोr_radiotap *radiotap;
	स्थिर पूर्णांक size = माप(*radiotap) + माप(__le16);

	अगर (!mvm->cur_aid)
		वापस;

	/* ensure alignment */
	BUILD_BUG_ON((size + 2) % 4);

	radiotap = skb_put(skb, size + 2);
	radiotap->align = 1;
	/* Intel OUI */
	radiotap->oui[0] = 0xf6;
	radiotap->oui[1] = 0x54;
	radiotap->oui[2] = 0x25;
	/* radiotap snअगरfer config sub-namespace */
	radiotap->subns = 1;
	radiotap->present = 0x1;
	radiotap->len = size - माप(*radiotap);
	radiotap->pad = 2;

	/* fill the data now */
	स_नकल(radiotap->data, &mvm->cur_aid, माप(mvm->cur_aid));
	/* and clear the padding */
	स_रखो(radiotap->data + माप(__le16), 0, radiotap->pad);

	rx_status->flag |= RX_FLAG_RADIOTAP_VENDOR_DATA;
पूर्ण

/* iwl_mvm_pass_packet_to_mac80211 - passes the packet क्रम mac80211 */
अटल व्योम iwl_mvm_pass_packet_to_mac80211(काष्ठा iwl_mvm *mvm,
					    काष्ठा napi_काष्ठा *napi,
					    काष्ठा sk_buff *skb, पूर्णांक queue,
					    काष्ठा ieee80211_sta *sta,
					    bool csi)
अणु
	अगर (iwl_mvm_check_pn(mvm, skb, queue, sta))
		kमुक्त_skb(skb);
	अन्यथा
		ieee80211_rx_napi(mvm->hw, sta, skb, napi);
पूर्ण

अटल व्योम iwl_mvm_get_संकेत_strength(काष्ठा iwl_mvm *mvm,
					काष्ठा ieee80211_rx_status *rx_status,
					u32 rate_n_flags, पूर्णांक energy_a,
					पूर्णांक energy_b)
अणु
	पूर्णांक max_energy;
	u32 rate_flags = rate_n_flags;

	energy_a = energy_a ? -energy_a : S8_MIN;
	energy_b = energy_b ? -energy_b : S8_MIN;
	max_energy = max(energy_a, energy_b);

	IWL_DEBUG_STATS(mvm, "energy In A %d B %d, and max %d\n",
			energy_a, energy_b, max_energy);

	rx_status->संकेत = max_energy;
	rx_status->chains =
		(rate_flags & RATE_MCS_ANT_AB_MSK) >> RATE_MCS_ANT_POS;
	rx_status->chain_संकेत[0] = energy_a;
	rx_status->chain_संकेत[1] = energy_b;
	rx_status->chain_संकेत[2] = S8_MIN;
पूर्ण

अटल पूर्णांक iwl_mvm_rx_mgmt_prot(काष्ठा ieee80211_sta *sta,
				काष्ठा ieee80211_hdr *hdr,
				काष्ठा iwl_rx_mpdu_desc *desc,
				u32 status)
अणु
	काष्ठा iwl_mvm_sta *mvmsta;
	काष्ठा iwl_mvm_vअगर *mvmvअगर;
	u8 fwkeyid = u32_get_bits(status, IWL_RX_MPDU_STATUS_KEY);
	u8 keyid;
	काष्ठा ieee80211_key_conf *key;
	u32 len = le16_to_cpu(desc->mpdu_len);
	स्थिर u8 *frame = (व्योम *)hdr;

	अगर ((status & IWL_RX_MPDU_STATUS_SEC_MASK) == IWL_RX_MPDU_STATUS_SEC_NONE)
		वापस 0;

	/*
	 * For non-beacon, we करोn't really care. But beacons may
	 * be filtered out, and we thus need the firmware's replay
	 * detection, otherwise beacons the firmware previously
	 * filtered could be replayed, or something like that, and
	 * it can filter a lot - though usually only अगर nothing has
	 * changed.
	 */
	अगर (!ieee80211_is_beacon(hdr->frame_control))
		वापस 0;

	/* good हालs */
	अगर (likely(status & IWL_RX_MPDU_STATUS_MIC_OK &&
		   !(status & IWL_RX_MPDU_STATUS_REPLAY_ERROR)))
		वापस 0;

	अगर (!sta)
		वापस -1;

	mvmsta = iwl_mvm_sta_from_mac80211(sta);

	/* what? */
	अगर (fwkeyid != 6 && fwkeyid != 7)
		वापस -1;

	mvmvअगर = iwl_mvm_vअगर_from_mac80211(mvmsta->vअगर);

	key = rcu_dereference(mvmvअगर->bcn_prot.keys[fwkeyid - 6]);
	अगर (!key)
		वापस -1;

	अगर (len < key->icv_len + IEEE80211_GMAC_PN_LEN + 2)
		वापस -1;

	/*
	 * See अगर the key ID matches - अगर not this may be due to a
	 * चयन and the firmware may erroneously report !MIC_OK.
	 */
	keyid = frame[len - key->icv_len - IEEE80211_GMAC_PN_LEN - 2];
	अगर (keyid != fwkeyid)
		वापस -1;

	/* Report status to mac80211 */
	अगर (!(status & IWL_RX_MPDU_STATUS_MIC_OK))
		ieee80211_key_mic_failure(key);
	अन्यथा अगर (status & IWL_RX_MPDU_STATUS_REPLAY_ERROR)
		ieee80211_key_replay(key);

	वापस -1;
पूर्ण

अटल पूर्णांक iwl_mvm_rx_crypto(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
			     काष्ठा ieee80211_hdr *hdr,
			     काष्ठा ieee80211_rx_status *stats, u16 phy_info,
			     काष्ठा iwl_rx_mpdu_desc *desc,
			     u32 pkt_flags, पूर्णांक queue, u8 *crypt_len)
अणु
	u32 status = le32_to_cpu(desc->status);

	/*
	 * Drop UNKNOWN frames in aggregation, unless in monitor mode
	 * (where we करोn't have the keys).
	 * We limit this to aggregation because in TKIP this is a valid
	 * scenario, since we may not have the (correct) TTAK (phase 1
	 * key) in the firmware.
	 */
	अगर (phy_info & IWL_RX_MPDU_PHY_AMPDU &&
	    (status & IWL_RX_MPDU_STATUS_SEC_MASK) ==
	    IWL_RX_MPDU_STATUS_SEC_UNKNOWN && !mvm->monitor_on)
		वापस -1;

	अगर (unlikely(ieee80211_is_mgmt(hdr->frame_control) &&
		     !ieee80211_has_रक्षित(hdr->frame_control)))
		वापस iwl_mvm_rx_mgmt_prot(sta, hdr, desc, status);

	अगर (!ieee80211_has_रक्षित(hdr->frame_control) ||
	    (status & IWL_RX_MPDU_STATUS_SEC_MASK) ==
	    IWL_RX_MPDU_STATUS_SEC_NONE)
		वापस 0;

	/* TODO: handle packets encrypted with unknown alg */

	चयन (status & IWL_RX_MPDU_STATUS_SEC_MASK) अणु
	हाल IWL_RX_MPDU_STATUS_SEC_CCM:
	हाल IWL_RX_MPDU_STATUS_SEC_GCM:
		BUILD_BUG_ON(IEEE80211_CCMP_PN_LEN != IEEE80211_GCMP_PN_LEN);
		/* alg is CCM: check MIC only */
		अगर (!(status & IWL_RX_MPDU_STATUS_MIC_OK))
			वापस -1;

		stats->flag |= RX_FLAG_DECRYPTED;
		अगर (pkt_flags & FH_RSCSR_RADA_EN)
			stats->flag |= RX_FLAG_MIC_STRIPPED;
		*crypt_len = IEEE80211_CCMP_HDR_LEN;
		वापस 0;
	हाल IWL_RX_MPDU_STATUS_SEC_TKIP:
		/* Don't drop the frame and decrypt it in SW */
		अगर (!fw_has_api(&mvm->fw->ucode_capa,
				IWL_UCODE_TLV_API_DEPRECATE_TTAK) &&
		    !(status & IWL_RX_MPDU_RES_STATUS_TTAK_OK))
			वापस 0;

		अगर (mvm->trans->trans_cfg->gen2 &&
		    !(status & RX_MPDU_RES_STATUS_MIC_OK))
			stats->flag |= RX_FLAG_MMIC_ERROR;

		*crypt_len = IEEE80211_TKIP_IV_LEN;
		fallthrough;
	हाल IWL_RX_MPDU_STATUS_SEC_WEP:
		अगर (!(status & IWL_RX_MPDU_STATUS_ICV_OK))
			वापस -1;

		stats->flag |= RX_FLAG_DECRYPTED;
		अगर ((status & IWL_RX_MPDU_STATUS_SEC_MASK) ==
				IWL_RX_MPDU_STATUS_SEC_WEP)
			*crypt_len = IEEE80211_WEP_IV_LEN;

		अगर (pkt_flags & FH_RSCSR_RADA_EN) अणु
			stats->flag |= RX_FLAG_ICV_STRIPPED;
			अगर (mvm->trans->trans_cfg->gen2)
				stats->flag |= RX_FLAG_MMIC_STRIPPED;
		पूर्ण

		वापस 0;
	हाल IWL_RX_MPDU_STATUS_SEC_EXT_ENC:
		अगर (!(status & IWL_RX_MPDU_STATUS_MIC_OK))
			वापस -1;
		stats->flag |= RX_FLAG_DECRYPTED;
		वापस 0;
	हाल RX_MPDU_RES_STATUS_SEC_CMAC_GMAC_ENC:
		अवरोध;
	शेष:
		/*
		 * Someबार we can get frames that were not decrypted
		 * because the firmware didn't have the keys yet. This can
		 * happen after connection where we can get multicast frames
		 * beक्रमe the GTK is installed.
		 * Silently drop those frames.
		 * Also drop un-decrypted frames in monitor mode.
		 */
		अगर (!is_multicast_ether_addr(hdr->addr1) &&
		    !mvm->monitor_on && net_ratelimit())
			IWL_ERR(mvm, "Unhandled alg: 0x%x\n", status);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iwl_mvm_rx_csum(काष्ठा iwl_mvm *mvm,
			    काष्ठा ieee80211_sta *sta,
			    काष्ठा sk_buff *skb,
			    काष्ठा iwl_rx_packet *pkt)
अणु
	काष्ठा iwl_rx_mpdu_desc *desc = (व्योम *)pkt->data;

	अगर (mvm->trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210) अणु
		अगर (pkt->len_n_flags & cpu_to_le32(FH_RSCSR_RPA_EN)) अणु
			u16 hwsum = be16_to_cpu(desc->v3.raw_xsum);

			skb->ip_summed = CHECKSUM_COMPLETE;
			skb->csum = csum_unfold(~(__क्रमce __sum16)hwsum);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
		काष्ठा iwl_mvm_vअगर *mvmvअगर;
		u16 flags = le16_to_cpu(desc->l3l4_flags);
		u8 l3_prot = (u8)((flags & IWL_RX_L3L4_L3_PROTO_MASK) >>
				  IWL_RX_L3_PROTO_POS);

		mvmvअगर = iwl_mvm_vअगर_from_mac80211(mvmsta->vअगर);

		अगर (mvmvअगर->features & NETIF_F_RXCSUM &&
		    flags & IWL_RX_L3L4_TCP_UDP_CSUM_OK &&
		    (flags & IWL_RX_L3L4_IP_HDR_CSUM_OK ||
		     l3_prot == IWL_RX_L3_TYPE_IPV6 ||
		     l3_prot == IWL_RX_L3_TYPE_IPV6_FRAG))
			skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण
पूर्ण

/*
 * वापसs true अगर a packet is a duplicate and should be dropped.
 * Updates AMSDU PN tracking info
 */
अटल bool iwl_mvm_is_dup(काष्ठा ieee80211_sta *sta, पूर्णांक queue,
			   काष्ठा ieee80211_rx_status *rx_status,
			   काष्ठा ieee80211_hdr *hdr,
			   काष्ठा iwl_rx_mpdu_desc *desc)
अणु
	काष्ठा iwl_mvm_sta *mvm_sta;
	काष्ठा iwl_mvm_rxq_dup_data *dup_data;
	u8 tid, sub_frame_idx;

	अगर (WARN_ON(IS_ERR_OR_शून्य(sta)))
		वापस false;

	mvm_sta = iwl_mvm_sta_from_mac80211(sta);
	dup_data = &mvm_sta->dup_data[queue];

	/*
	 * Drop duplicate 802.11 retransmissions
	 * (IEEE 802.11-2012: 9.3.2.10 "Duplicate detection and recovery")
	 */
	अगर (ieee80211_is_ctl(hdr->frame_control) ||
	    ieee80211_is_qos_nullfunc(hdr->frame_control) ||
	    is_multicast_ether_addr(hdr->addr1)) अणु
		rx_status->flag |= RX_FLAG_DUP_VALIDATED;
		वापस false;
	पूर्ण

	अगर (ieee80211_is_data_qos(hdr->frame_control))
		/* frame has qos control */
		tid = ieee80211_get_tid(hdr);
	अन्यथा
		tid = IWL_MAX_TID_COUNT;

	/* If this wasn't a part of an A-MSDU the sub-frame index will be 0 */
	sub_frame_idx = desc->amsdu_info &
		IWL_RX_MPDU_AMSDU_SUBFRAME_IDX_MASK;

	अगर (unlikely(ieee80211_has_retry(hdr->frame_control) &&
		     dup_data->last_seq[tid] == hdr->seq_ctrl &&
		     dup_data->last_sub_frame[tid] >= sub_frame_idx))
		वापस true;

	/* Allow same PN as the first subframe क्रम following sub frames */
	अगर (dup_data->last_seq[tid] == hdr->seq_ctrl &&
	    sub_frame_idx > dup_data->last_sub_frame[tid] &&
	    desc->mac_flags2 & IWL_RX_MPDU_MFLG2_AMSDU)
		rx_status->flag |= RX_FLAG_ALLOW_SAME_PN;

	dup_data->last_seq[tid] = hdr->seq_ctrl;
	dup_data->last_sub_frame[tid] = sub_frame_idx;

	rx_status->flag |= RX_FLAG_DUP_VALIDATED;

	वापस false;
पूर्ण

/*
 * Returns true अगर sn2 - buffer_size < sn1 < sn2.
 * To be used only in order to compare reorder buffer head with NSSN.
 * We fully trust NSSN unless it is behind us due to reorder समयout.
 * Reorder समयout can only bring us up to buffer_size SNs ahead of NSSN.
 */
अटल bool iwl_mvm_is_sn_less(u16 sn1, u16 sn2, u16 buffer_size)
अणु
	वापस ieee80211_sn_less(sn1, sn2) &&
	       !ieee80211_sn_less(sn1, sn2 - buffer_size);
पूर्ण

अटल व्योम iwl_mvm_sync_nssn(काष्ठा iwl_mvm *mvm, u8 baid, u16 nssn)
अणु
	अगर (IWL_MVM_USE_NSSN_SYNC) अणु
		काष्ठा iwl_mvm_nssn_sync_data notअगर = अणु
			.baid = baid,
			.nssn = nssn,
		पूर्ण;

		iwl_mvm_sync_rx_queues_पूर्णांकernal(mvm, IWL_MVM_RXQ_NSSN_SYNC, false,
						&notअगर, माप(notअगर));
	पूर्ण
पूर्ण

#घोषणा RX_REORDER_BUF_TIMEOUT_MQ (HZ / 10)

क्रमागत iwl_mvm_release_flags अणु
	IWL_MVM_RELEASE_SEND_RSS_SYNC = BIT(0),
	IWL_MVM_RELEASE_FROM_RSS_SYNC = BIT(1),
पूर्ण;

अटल व्योम iwl_mvm_release_frames(काष्ठा iwl_mvm *mvm,
				   काष्ठा ieee80211_sta *sta,
				   काष्ठा napi_काष्ठा *napi,
				   काष्ठा iwl_mvm_baid_data *baid_data,
				   काष्ठा iwl_mvm_reorder_buffer *reorder_buf,
				   u16 nssn, u32 flags)
अणु
	काष्ठा iwl_mvm_reorder_buf_entry *entries =
		&baid_data->entries[reorder_buf->queue *
				    baid_data->entries_per_queue];
	u16 ssn = reorder_buf->head_sn;

	lockdep_निश्चित_held(&reorder_buf->lock);

	/*
	 * We keep the NSSN not too far behind, अगर we are sync'ing it and it
	 * is more than 2048 ahead of us, it must be behind us. Discard it.
	 * This can happen अगर the queue that hit the 0 / 2048 seqno was lagging
	 * behind and this queue alपढ़ोy processed packets. The next अगर
	 * would have caught हालs where this queue would have processed less
	 * than 64 packets, but it may have processed more than 64 packets.
	 */
	अगर ((flags & IWL_MVM_RELEASE_FROM_RSS_SYNC) &&
	    ieee80211_sn_less(nssn, ssn))
		जाओ set_समयr;

	/* ignore nssn smaller than head sn - this can happen due to समयout */
	अगर (iwl_mvm_is_sn_less(nssn, ssn, reorder_buf->buf_size))
		जाओ set_समयr;

	जबतक (iwl_mvm_is_sn_less(ssn, nssn, reorder_buf->buf_size)) अणु
		पूर्णांक index = ssn % reorder_buf->buf_size;
		काष्ठा sk_buff_head *skb_list = &entries[index].e.frames;
		काष्ठा sk_buff *skb;

		ssn = ieee80211_sn_inc(ssn);
		अगर ((flags & IWL_MVM_RELEASE_SEND_RSS_SYNC) &&
		    (ssn == 2048 || ssn == 0))
			iwl_mvm_sync_nssn(mvm, baid_data->baid, ssn);

		/*
		 * Empty the list. Will have more than one frame क्रम A-MSDU.
		 * Empty list is valid as well since nssn indicates frames were
		 * received.
		 */
		जबतक ((skb = __skb_dequeue(skb_list))) अणु
			iwl_mvm_pass_packet_to_mac80211(mvm, napi, skb,
							reorder_buf->queue,
							sta, false);
			reorder_buf->num_stored--;
		पूर्ण
	पूर्ण
	reorder_buf->head_sn = nssn;

set_समयr:
	अगर (reorder_buf->num_stored && !reorder_buf->हटाओd) अणु
		u16 index = reorder_buf->head_sn % reorder_buf->buf_size;

		जबतक (skb_queue_empty(&entries[index].e.frames))
			index = (index + 1) % reorder_buf->buf_size;
		/* modअगरy समयr to match next frame's expiration समय */
		mod_समयr(&reorder_buf->reorder_समयr,
			  entries[index].e.reorder_समय + 1 +
			  RX_REORDER_BUF_TIMEOUT_MQ);
	पूर्ण अन्यथा अणु
		del_समयr(&reorder_buf->reorder_समयr);
	पूर्ण
पूर्ण

व्योम iwl_mvm_reorder_समयr_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा iwl_mvm_reorder_buffer *buf = from_समयr(buf, t, reorder_समयr);
	काष्ठा iwl_mvm_baid_data *baid_data =
		iwl_mvm_baid_data_from_reorder_buf(buf);
	काष्ठा iwl_mvm_reorder_buf_entry *entries =
		&baid_data->entries[buf->queue * baid_data->entries_per_queue];
	पूर्णांक i;
	u16 sn = 0, index = 0;
	bool expired = false;
	bool cont = false;

	spin_lock(&buf->lock);

	अगर (!buf->num_stored || buf->हटाओd) अणु
		spin_unlock(&buf->lock);
		वापस;
	पूर्ण

	क्रम (i = 0; i < buf->buf_size ; i++) अणु
		index = (buf->head_sn + i) % buf->buf_size;

		अगर (skb_queue_empty(&entries[index].e.frames)) अणु
			/*
			 * If there is a hole and the next frame didn't expire
			 * we want to अवरोध and not advance SN
			 */
			cont = false;
			जारी;
		पूर्ण
		अगर (!cont &&
		    !समय_after(jअगरfies, entries[index].e.reorder_समय +
					 RX_REORDER_BUF_TIMEOUT_MQ))
			अवरोध;

		expired = true;
		/* जारी until next hole after this expired frames */
		cont = true;
		sn = ieee80211_sn_add(buf->head_sn, i + 1);
	पूर्ण

	अगर (expired) अणु
		काष्ठा ieee80211_sta *sta;
		काष्ठा iwl_mvm_sta *mvmsta;
		u8 sta_id = baid_data->sta_id;

		rcu_पढ़ो_lock();
		sta = rcu_dereference(buf->mvm->fw_id_to_mac_id[sta_id]);
		mvmsta = iwl_mvm_sta_from_mac80211(sta);

		/* SN is set to the last expired frame + 1 */
		IWL_DEBUG_HT(buf->mvm,
			     "Releasing expired frames for sta %u, sn %d\n",
			     sta_id, sn);
		iwl_mvm_event_frame_समयout_callback(buf->mvm, mvmsta->vअगर,
						     sta, baid_data->tid);
		iwl_mvm_release_frames(buf->mvm, sta, शून्य, baid_data,
				       buf, sn, IWL_MVM_RELEASE_SEND_RSS_SYNC);
		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा अणु
		/*
		 * If no frame expired and there are stored frames, index is now
		 * poपूर्णांकing to the first unexpired frame - modअगरy समयr
		 * accordingly to this frame.
		 */
		mod_समयr(&buf->reorder_समयr,
			  entries[index].e.reorder_समय +
			  1 + RX_REORDER_BUF_TIMEOUT_MQ);
	पूर्ण
	spin_unlock(&buf->lock);
पूर्ण

अटल व्योम iwl_mvm_del_ba(काष्ठा iwl_mvm *mvm, पूर्णांक queue,
			   काष्ठा iwl_mvm_delba_data *data)
अणु
	काष्ठा iwl_mvm_baid_data *ba_data;
	काष्ठा ieee80211_sta *sta;
	काष्ठा iwl_mvm_reorder_buffer *reorder_buf;
	u8 baid = data->baid;

	अगर (WARN_ONCE(baid >= IWL_MAX_BAID, "invalid BAID: %x\n", baid))
		वापस;

	rcu_पढ़ो_lock();

	ba_data = rcu_dereference(mvm->baid_map[baid]);
	अगर (WARN_ON_ONCE(!ba_data))
		जाओ out;

	sta = rcu_dereference(mvm->fw_id_to_mac_id[ba_data->sta_id]);
	अगर (WARN_ON_ONCE(IS_ERR_OR_शून्य(sta)))
		जाओ out;

	reorder_buf = &ba_data->reorder_buf[queue];

	/* release all frames that are in the reorder buffer to the stack */
	spin_lock_bh(&reorder_buf->lock);
	iwl_mvm_release_frames(mvm, sta, शून्य, ba_data, reorder_buf,
			       ieee80211_sn_add(reorder_buf->head_sn,
						reorder_buf->buf_size),
			       0);
	spin_unlock_bh(&reorder_buf->lock);
	del_समयr_sync(&reorder_buf->reorder_समयr);

out:
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम iwl_mvm_release_frames_from_notअगर(काष्ठा iwl_mvm *mvm,
					      काष्ठा napi_काष्ठा *napi,
					      u8 baid, u16 nssn, पूर्णांक queue,
					      u32 flags)
अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा iwl_mvm_reorder_buffer *reorder_buf;
	काष्ठा iwl_mvm_baid_data *ba_data;

	IWL_DEBUG_HT(mvm, "Frame release notification for BAID %u, NSSN %d\n",
		     baid, nssn);

	अगर (WARN_ON_ONCE(baid == IWL_RX_REORDER_DATA_INVALID_BAID ||
			 baid >= ARRAY_SIZE(mvm->baid_map)))
		वापस;

	rcu_पढ़ो_lock();

	ba_data = rcu_dereference(mvm->baid_map[baid]);
	अगर (WARN_ON_ONCE(!ba_data))
		जाओ out;

	sta = rcu_dereference(mvm->fw_id_to_mac_id[ba_data->sta_id]);
	अगर (WARN_ON_ONCE(IS_ERR_OR_शून्य(sta)))
		जाओ out;

	reorder_buf = &ba_data->reorder_buf[queue];

	spin_lock_bh(&reorder_buf->lock);
	iwl_mvm_release_frames(mvm, sta, napi, ba_data,
			       reorder_buf, nssn, flags);
	spin_unlock_bh(&reorder_buf->lock);

out:
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम iwl_mvm_nssn_sync(काष्ठा iwl_mvm *mvm,
			      काष्ठा napi_काष्ठा *napi, पूर्णांक queue,
			      स्थिर काष्ठा iwl_mvm_nssn_sync_data *data)
अणु
	iwl_mvm_release_frames_from_notअगर(mvm, napi, data->baid,
					  data->nssn, queue,
					  IWL_MVM_RELEASE_FROM_RSS_SYNC);
पूर्ण

व्योम iwl_mvm_rx_queue_notअगर(काष्ठा iwl_mvm *mvm, काष्ठा napi_काष्ठा *napi,
			    काष्ठा iwl_rx_cmd_buffer *rxb, पूर्णांक queue)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_rxq_sync_notअगरication *notअगर;
	काष्ठा iwl_mvm_पूर्णांकernal_rxq_notअगर *पूर्णांकernal_notअगर;
	u32 len = iwl_rx_packet_payload_len(pkt);

	notअगर = (व्योम *)pkt->data;
	पूर्णांकernal_notअगर = (व्योम *)notअगर->payload;

	अगर (WARN_ONCE(len < माप(*notअगर) + माप(*पूर्णांकernal_notअगर),
		      "invalid notification size %d (%d)",
		      len, (पूर्णांक)(माप(*notअगर) + माप(*पूर्णांकernal_notअगर))))
		वापस;
	len -= माप(*notअगर) + माप(*पूर्णांकernal_notअगर);

	अगर (पूर्णांकernal_notअगर->sync &&
	    mvm->queue_sync_cookie != पूर्णांकernal_notअगर->cookie) अणु
		WARN_ONCE(1, "Received expired RX queue sync message\n");
		वापस;
	पूर्ण

	चयन (पूर्णांकernal_notअगर->type) अणु
	हाल IWL_MVM_RXQ_EMPTY:
		WARN_ONCE(len, "invalid empty notification size %d", len);
		अवरोध;
	हाल IWL_MVM_RXQ_NOTIF_DEL_BA:
		अगर (WARN_ONCE(len != माप(काष्ठा iwl_mvm_delba_data),
			      "invalid delba notification size %d (%d)",
			      len, (पूर्णांक)माप(काष्ठा iwl_mvm_delba_data)))
			अवरोध;
		iwl_mvm_del_ba(mvm, queue, (व्योम *)पूर्णांकernal_notअगर->data);
		अवरोध;
	हाल IWL_MVM_RXQ_NSSN_SYNC:
		अगर (WARN_ONCE(len != माप(काष्ठा iwl_mvm_nssn_sync_data),
			      "invalid nssn sync notification size %d (%d)",
			      len, (पूर्णांक)माप(काष्ठा iwl_mvm_nssn_sync_data)))
			अवरोध;
		iwl_mvm_nssn_sync(mvm, napi, queue,
				  (व्योम *)पूर्णांकernal_notअगर->data);
		अवरोध;
	शेष:
		WARN_ONCE(1, "Invalid identifier %d", पूर्णांकernal_notअगर->type);
	पूर्ण

	अगर (पूर्णांकernal_notअगर->sync) अणु
		WARN_ONCE(!test_and_clear_bit(queue, &mvm->queue_sync_state),
			  "queue sync: queue %d responded a second time!\n",
			  queue);
		अगर (READ_ONCE(mvm->queue_sync_state) == 0)
			wake_up(&mvm->rx_sync_रुकोq);
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_oldsn_workaround(काष्ठा iwl_mvm *mvm,
				     काष्ठा ieee80211_sta *sta, पूर्णांक tid,
				     काष्ठा iwl_mvm_reorder_buffer *buffer,
				     u32 reorder, u32 gp2, पूर्णांक queue)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);

	अगर (gp2 != buffer->consec_oldsn_ampdu_gp2) अणु
		/* we have a new (A-)MPDU ... */

		/*
		 * reset counter to 0 अगर we didn't have any oldsn in
		 * the last A-MPDU (as detected by GP2 being identical)
		 */
		अगर (!buffer->consec_oldsn_prev_drop)
			buffer->consec_oldsn_drops = 0;

		/* either way, update our tracking state */
		buffer->consec_oldsn_ampdu_gp2 = gp2;
	पूर्ण अन्यथा अगर (buffer->consec_oldsn_prev_drop) अणु
		/*
		 * tracking state didn't change, and we had an old SN
		 * indication beक्रमe - करो nothing in this हाल, we
		 * alपढ़ोy noted this one करोwn and are रुकोing क्रम the
		 * next A-MPDU (by GP2)
		 */
		वापस;
	पूर्ण

	/* वापस unless this MPDU has old SN */
	अगर (!(reorder & IWL_RX_MPDU_REORDER_BA_OLD_SN))
		वापस;

	/* update state */
	buffer->consec_oldsn_prev_drop = 1;
	buffer->consec_oldsn_drops++;

	/* अगर limit is reached, send del BA and reset state */
	अगर (buffer->consec_oldsn_drops == IWL_MVM_AMPDU_CONSEC_DROPS_DELBA) अणु
		IWL_WARN(mvm,
			 "reached %d old SN frames from %pM on queue %d, stopping BA session on TID %d\n",
			 IWL_MVM_AMPDU_CONSEC_DROPS_DELBA,
			 sta->addr, queue, tid);
		ieee80211_stop_rx_ba_session(mvmsta->vअगर, BIT(tid), sta->addr);
		buffer->consec_oldsn_prev_drop = 0;
		buffer->consec_oldsn_drops = 0;
	पूर्ण
पूर्ण

/*
 * Returns true अगर the MPDU was buffered\dropped, false अगर it should be passed
 * to upper layer.
 */
अटल bool iwl_mvm_reorder(काष्ठा iwl_mvm *mvm,
			    काष्ठा napi_काष्ठा *napi,
			    पूर्णांक queue,
			    काष्ठा ieee80211_sta *sta,
			    काष्ठा sk_buff *skb,
			    काष्ठा iwl_rx_mpdu_desc *desc)
अणु
	काष्ठा ieee80211_rx_status *rx_status = IEEE80211_SKB_RXCB(skb);
	काष्ठा ieee80211_hdr *hdr = iwl_mvm_skb_get_hdr(skb);
	काष्ठा iwl_mvm_sta *mvm_sta;
	काष्ठा iwl_mvm_baid_data *baid_data;
	काष्ठा iwl_mvm_reorder_buffer *buffer;
	काष्ठा sk_buff *tail;
	u32 reorder = le32_to_cpu(desc->reorder_data);
	bool amsdu = desc->mac_flags2 & IWL_RX_MPDU_MFLG2_AMSDU;
	bool last_subframe =
		desc->amsdu_info & IWL_RX_MPDU_AMSDU_LAST_SUBFRAME;
	u8 tid = ieee80211_get_tid(hdr);
	u8 sub_frame_idx = desc->amsdu_info &
			   IWL_RX_MPDU_AMSDU_SUBFRAME_IDX_MASK;
	काष्ठा iwl_mvm_reorder_buf_entry *entries;
	पूर्णांक index;
	u16 nssn, sn;
	u8 baid;

	baid = (reorder & IWL_RX_MPDU_REORDER_BAID_MASK) >>
		IWL_RX_MPDU_REORDER_BAID_SHIFT;

	/*
	 * This also covers the हाल of receiving a Block Ack Request
	 * outside a BA session; we'll pass it to mac80211 and that
	 * then sends a delBA action frame.
	 * This also covers pure monitor mode, in which हाल we won't
	 * have any BA sessions.
	 */
	अगर (baid == IWL_RX_REORDER_DATA_INVALID_BAID)
		वापस false;

	/* no sta yet */
	अगर (WARN_ONCE(IS_ERR_OR_शून्य(sta),
		      "Got valid BAID without a valid station assigned\n"))
		वापस false;

	mvm_sta = iwl_mvm_sta_from_mac80211(sta);

	/* not a data packet or a bar */
	अगर (!ieee80211_is_back_req(hdr->frame_control) &&
	    (!ieee80211_is_data_qos(hdr->frame_control) ||
	     is_multicast_ether_addr(hdr->addr1)))
		वापस false;

	अगर (unlikely(!ieee80211_is_data_present(hdr->frame_control)))
		वापस false;

	baid_data = rcu_dereference(mvm->baid_map[baid]);
	अगर (!baid_data) अणु
		IWL_DEBUG_RX(mvm,
			     "Got valid BAID but no baid allocated, bypass the re-ordering buffer. Baid %d reorder 0x%x\n",
			      baid, reorder);
		वापस false;
	पूर्ण

	अगर (WARN(tid != baid_data->tid || mvm_sta->sta_id != baid_data->sta_id,
		 "baid 0x%x is mapped to sta:%d tid:%d, but was received for sta:%d tid:%d\n",
		 baid, baid_data->sta_id, baid_data->tid, mvm_sta->sta_id,
		 tid))
		वापस false;

	nssn = reorder & IWL_RX_MPDU_REORDER_NSSN_MASK;
	sn = (reorder & IWL_RX_MPDU_REORDER_SN_MASK) >>
		IWL_RX_MPDU_REORDER_SN_SHIFT;

	buffer = &baid_data->reorder_buf[queue];
	entries = &baid_data->entries[queue * baid_data->entries_per_queue];

	spin_lock_bh(&buffer->lock);

	अगर (!buffer->valid) अणु
		अगर (reorder & IWL_RX_MPDU_REORDER_BA_OLD_SN) अणु
			spin_unlock_bh(&buffer->lock);
			वापस false;
		पूर्ण
		buffer->valid = true;
	पूर्ण

	अगर (ieee80211_is_back_req(hdr->frame_control)) अणु
		iwl_mvm_release_frames(mvm, sta, napi, baid_data,
				       buffer, nssn, 0);
		जाओ drop;
	पूर्ण

	/*
	 * If there was a signअगरicant jump in the nssn - adjust.
	 * If the SN is smaller than the NSSN it might need to first go पूर्णांकo
	 * the reorder buffer, in which हाल we just release up to it and the
	 * rest of the function will take care of storing it and releasing up to
	 * the nssn.
	 * This should not happen. This queue has been lagging and it should
	 * have been updated by a IWL_MVM_RXQ_NSSN_SYNC notअगरication. Be nice
	 * and update the other queues.
	 */
	अगर (!iwl_mvm_is_sn_less(nssn, buffer->head_sn + buffer->buf_size,
				buffer->buf_size) ||
	    !ieee80211_sn_less(sn, buffer->head_sn + buffer->buf_size)) अणु
		u16 min_sn = ieee80211_sn_less(sn, nssn) ? sn : nssn;

		iwl_mvm_release_frames(mvm, sta, napi, baid_data, buffer,
				       min_sn, IWL_MVM_RELEASE_SEND_RSS_SYNC);
	पूर्ण

	iwl_mvm_oldsn_workaround(mvm, sta, tid, buffer, reorder,
				 rx_status->device_बारtamp, queue);

	/* drop any oudated packets */
	अगर (ieee80211_sn_less(sn, buffer->head_sn))
		जाओ drop;

	/* release immediately अगर allowed by nssn and no stored frames */
	अगर (!buffer->num_stored && ieee80211_sn_less(sn, nssn)) अणु
		अगर (iwl_mvm_is_sn_less(buffer->head_sn, nssn,
				       buffer->buf_size) &&
		   (!amsdu || last_subframe)) अणु
			/*
			 * If we crossed the 2048 or 0 SN, notअगरy all the
			 * queues. This is करोne in order to aव्योम having a
			 * head_sn that lags behind क्रम too दीर्घ. When that
			 * happens, we can get to a situation where the head_sn
			 * is within the पूर्णांकerval [nssn - buf_size : nssn]
			 * which will make us think that the nssn is a packet
			 * that we alपढ़ोy मुक्तd because of the reordering
			 * buffer and we will ignore it. So मुख्यtain the
			 * head_sn somewhat updated across all the queues:
			 * when it crosses 0 and 2048.
			 */
			अगर (sn == 2048 || sn == 0)
				iwl_mvm_sync_nssn(mvm, baid, sn);
			buffer->head_sn = nssn;
		पूर्ण
		/* No need to update AMSDU last SN - we are moving the head */
		spin_unlock_bh(&buffer->lock);
		वापस false;
	पूर्ण

	/*
	 * release immediately अगर there are no stored frames, and the sn is
	 * equal to the head.
	 * This can happen due to reorder समयr, where NSSN is behind head_sn.
	 * When we released everything, and we got the next frame in the
	 * sequence, according to the NSSN we can't release immediately,
	 * जबतक technically there is no hole and we can move क्रमward.
	 */
	अगर (!buffer->num_stored && sn == buffer->head_sn) अणु
		अगर (!amsdu || last_subframe) अणु
			अगर (sn == 2048 || sn == 0)
				iwl_mvm_sync_nssn(mvm, baid, sn);
			buffer->head_sn = ieee80211_sn_inc(buffer->head_sn);
		पूर्ण
		/* No need to update AMSDU last SN - we are moving the head */
		spin_unlock_bh(&buffer->lock);
		वापस false;
	पूर्ण

	index = sn % buffer->buf_size;

	/*
	 * Check अगर we alपढ़ोy stored this frame
	 * As AMSDU is either received or not as whole, logic is simple:
	 * If we have frames in that position in the buffer and the last frame
	 * originated from AMSDU had a dअगरferent SN then it is a retransmission.
	 * If it is the same SN then अगर the subframe index is incrementing it
	 * is the same AMSDU - otherwise it is a retransmission.
	 */
	tail = skb_peek_tail(&entries[index].e.frames);
	अगर (tail && !amsdu)
		जाओ drop;
	अन्यथा अगर (tail && (sn != buffer->last_amsdu ||
			  buffer->last_sub_index >= sub_frame_idx))
		जाओ drop;

	/* put in reorder buffer */
	__skb_queue_tail(&entries[index].e.frames, skb);
	buffer->num_stored++;
	entries[index].e.reorder_समय = jअगरfies;

	अगर (amsdu) अणु
		buffer->last_amsdu = sn;
		buffer->last_sub_index = sub_frame_idx;
	पूर्ण

	/*
	 * We cannot trust NSSN क्रम AMSDU sub-frames that are not the last.
	 * The reason is that NSSN advances on the first sub-frame, and may
	 * cause the reorder buffer to advance beक्रमe all the sub-frames arrive.
	 * Example: reorder buffer contains SN 0 & 2, and we receive AMSDU with
	 * SN 1. NSSN क्रम first sub frame will be 3 with the result of driver
	 * releasing SN 0,1, 2. When sub-frame 1 arrives - reorder buffer is
	 * alपढ़ोy ahead and it will be dropped.
	 * If the last sub-frame is not on this queue - we will get frame
	 * release notअगरication with up to date NSSN.
	 */
	अगर (!amsdu || last_subframe)
		iwl_mvm_release_frames(mvm, sta, napi, baid_data,
				       buffer, nssn,
				       IWL_MVM_RELEASE_SEND_RSS_SYNC);

	spin_unlock_bh(&buffer->lock);
	वापस true;

drop:
	kमुक्त_skb(skb);
	spin_unlock_bh(&buffer->lock);
	वापस true;
पूर्ण

अटल व्योम iwl_mvm_agg_rx_received(काष्ठा iwl_mvm *mvm,
				    u32 reorder_data, u8 baid)
अणु
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ समयout;
	काष्ठा iwl_mvm_baid_data *data;

	rcu_पढ़ो_lock();

	data = rcu_dereference(mvm->baid_map[baid]);
	अगर (!data) अणु
		IWL_DEBUG_RX(mvm,
			     "Got valid BAID but no baid allocated, bypass the re-ordering buffer. Baid %d reorder 0x%x\n",
			      baid, reorder_data);
		जाओ out;
	पूर्ण

	अगर (!data->समयout)
		जाओ out;

	समयout = data->समयout;
	/*
	 * Do not update last rx all the समय to aव्योम cache bouncing
	 * between the rx queues.
	 * Update it every समयout. Worst हाल is the session will
	 * expire after ~ 2 * समयout, which करोesn't matter that much.
	 */
	अगर (समय_beक्रमe(data->last_rx + TU_TO_JIFFIES(समयout), now))
		/* Update is atomic */
		data->last_rx = now;

out:
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम iwl_mvm_flip_address(u8 *addr)
अणु
	पूर्णांक i;
	u8 mac_addr[ETH_ALEN];

	क्रम (i = 0; i < ETH_ALEN; i++)
		mac_addr[i] = addr[ETH_ALEN - i - 1];
	ether_addr_copy(addr, mac_addr);
पूर्ण

काष्ठा iwl_mvm_rx_phy_data अणु
	क्रमागत iwl_rx_phy_info_type info_type;
	__le32 d0, d1, d2, d3;
	__le16 d4;
पूर्ण;

अटल व्योम iwl_mvm_decode_he_mu_ext(काष्ठा iwl_mvm *mvm,
				     काष्ठा iwl_mvm_rx_phy_data *phy_data,
				     u32 rate_n_flags,
				     काष्ठा ieee80211_radiotap_he_mu *he_mu)
अणु
	u32 phy_data2 = le32_to_cpu(phy_data->d2);
	u32 phy_data3 = le32_to_cpu(phy_data->d3);
	u16 phy_data4 = le16_to_cpu(phy_data->d4);

	अगर (FIELD_GET(IWL_RX_PHY_DATA4_HE_MU_EXT_CH1_CRC_OK, phy_data4)) अणु
		he_mu->flags1 |=
			cpu_to_le16(IEEE80211_RADIOTAP_HE_MU_FLAGS1_CH1_RU_KNOWN |
				    IEEE80211_RADIOTAP_HE_MU_FLAGS1_CH1_CTR_26T_RU_KNOWN);

		he_mu->flags1 |=
			le16_encode_bits(FIELD_GET(IWL_RX_PHY_DATA4_HE_MU_EXT_CH1_CTR_RU,
						   phy_data4),
					 IEEE80211_RADIOTAP_HE_MU_FLAGS1_CH1_CTR_26T_RU);

		he_mu->ru_ch1[0] = FIELD_GET(IWL_RX_PHY_DATA2_HE_MU_EXT_CH1_RU0,
					     phy_data2);
		he_mu->ru_ch1[1] = FIELD_GET(IWL_RX_PHY_DATA3_HE_MU_EXT_CH1_RU1,
					     phy_data3);
		he_mu->ru_ch1[2] = FIELD_GET(IWL_RX_PHY_DATA2_HE_MU_EXT_CH1_RU2,
					     phy_data2);
		he_mu->ru_ch1[3] = FIELD_GET(IWL_RX_PHY_DATA3_HE_MU_EXT_CH1_RU3,
					     phy_data3);
	पूर्ण

	अगर (FIELD_GET(IWL_RX_PHY_DATA4_HE_MU_EXT_CH2_CRC_OK, phy_data4) &&
	    (rate_n_flags & RATE_MCS_CHAN_WIDTH_MSK) != RATE_MCS_CHAN_WIDTH_20) अणु
		he_mu->flags1 |=
			cpu_to_le16(IEEE80211_RADIOTAP_HE_MU_FLAGS1_CH2_RU_KNOWN |
				    IEEE80211_RADIOTAP_HE_MU_FLAGS1_CH2_CTR_26T_RU_KNOWN);

		he_mu->flags2 |=
			le16_encode_bits(FIELD_GET(IWL_RX_PHY_DATA4_HE_MU_EXT_CH2_CTR_RU,
						   phy_data4),
					 IEEE80211_RADIOTAP_HE_MU_FLAGS2_CH2_CTR_26T_RU);

		he_mu->ru_ch2[0] = FIELD_GET(IWL_RX_PHY_DATA2_HE_MU_EXT_CH2_RU0,
					     phy_data2);
		he_mu->ru_ch2[1] = FIELD_GET(IWL_RX_PHY_DATA3_HE_MU_EXT_CH2_RU1,
					     phy_data3);
		he_mu->ru_ch2[2] = FIELD_GET(IWL_RX_PHY_DATA2_HE_MU_EXT_CH2_RU2,
					     phy_data2);
		he_mu->ru_ch2[3] = FIELD_GET(IWL_RX_PHY_DATA3_HE_MU_EXT_CH2_RU3,
					     phy_data3);
	पूर्ण
पूर्ण

अटल व्योम
iwl_mvm_decode_he_phy_ru_alloc(काष्ठा iwl_mvm_rx_phy_data *phy_data,
			       u32 rate_n_flags,
			       काष्ठा ieee80211_radiotap_he *he,
			       काष्ठा ieee80211_radiotap_he_mu *he_mu,
			       काष्ठा ieee80211_rx_status *rx_status)
अणु
	/*
	 * Unक्रमtunately, we have to leave the mac80211 data
	 * incorrect क्रम the हाल that we receive an HE-MU
	 * transmission and *करोn't* have the HE phy data (due
	 * to the bits being used क्रम TSF). This shouldn't
	 * happen though as management frames where we need
	 * the TSF/समयrs are not be transmitted in HE-MU.
	 */
	u8 ru = le32_get_bits(phy_data->d1, IWL_RX_PHY_DATA1_HE_RU_ALLOC_MASK);
	u32 he_type = rate_n_flags & RATE_MCS_HE_TYPE_MSK;
	u8 offs = 0;

	rx_status->bw = RATE_INFO_BW_HE_RU;

	he->data1 |= cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA1_BW_RU_ALLOC_KNOWN);

	चयन (ru) अणु
	हाल 0 ... 36:
		rx_status->he_ru = NL80211_RATE_INFO_HE_RU_ALLOC_26;
		offs = ru;
		अवरोध;
	हाल 37 ... 52:
		rx_status->he_ru = NL80211_RATE_INFO_HE_RU_ALLOC_52;
		offs = ru - 37;
		अवरोध;
	हाल 53 ... 60:
		rx_status->he_ru = NL80211_RATE_INFO_HE_RU_ALLOC_106;
		offs = ru - 53;
		अवरोध;
	हाल 61 ... 64:
		rx_status->he_ru = NL80211_RATE_INFO_HE_RU_ALLOC_242;
		offs = ru - 61;
		अवरोध;
	हाल 65 ... 66:
		rx_status->he_ru = NL80211_RATE_INFO_HE_RU_ALLOC_484;
		offs = ru - 65;
		अवरोध;
	हाल 67:
		rx_status->he_ru = NL80211_RATE_INFO_HE_RU_ALLOC_996;
		अवरोध;
	हाल 68:
		rx_status->he_ru = NL80211_RATE_INFO_HE_RU_ALLOC_2x996;
		अवरोध;
	पूर्ण
	he->data2 |= le16_encode_bits(offs,
				      IEEE80211_RADIOTAP_HE_DATA2_RU_OFFSET);
	he->data2 |= cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA2_PRISEC_80_KNOWN |
				 IEEE80211_RADIOTAP_HE_DATA2_RU_OFFSET_KNOWN);
	अगर (phy_data->d1 & cpu_to_le32(IWL_RX_PHY_DATA1_HE_RU_ALLOC_SEC80))
		he->data2 |=
			cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA2_PRISEC_80_SEC);

#घोषणा CHECK_BW(bw) \
	BUILD_BUG_ON(IEEE80211_RADIOTAP_HE_MU_FLAGS2_BW_FROM_SIG_A_BW_ ## bw ## MHZ != \
		     RATE_MCS_CHAN_WIDTH_##bw >> RATE_MCS_CHAN_WIDTH_POS); \
	BUILD_BUG_ON(IEEE80211_RADIOTAP_HE_DATA6_TB_PPDU_BW_ ## bw ## MHZ != \
		     RATE_MCS_CHAN_WIDTH_##bw >> RATE_MCS_CHAN_WIDTH_POS)
	CHECK_BW(20);
	CHECK_BW(40);
	CHECK_BW(80);
	CHECK_BW(160);

	अगर (he_mu)
		he_mu->flags2 |=
			le16_encode_bits(FIELD_GET(RATE_MCS_CHAN_WIDTH_MSK,
						   rate_n_flags),
					 IEEE80211_RADIOTAP_HE_MU_FLAGS2_BW_FROM_SIG_A_BW);
	अन्यथा अगर (he_type == RATE_MCS_HE_TYPE_TRIG)
		he->data6 |=
			cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA6_TB_PPDU_BW_KNOWN) |
			le16_encode_bits(FIELD_GET(RATE_MCS_CHAN_WIDTH_MSK,
						   rate_n_flags),
					 IEEE80211_RADIOTAP_HE_DATA6_TB_PPDU_BW);
पूर्ण

अटल व्योम iwl_mvm_decode_he_phy_data(काष्ठा iwl_mvm *mvm,
				       काष्ठा iwl_mvm_rx_phy_data *phy_data,
				       काष्ठा ieee80211_radiotap_he *he,
				       काष्ठा ieee80211_radiotap_he_mu *he_mu,
				       काष्ठा ieee80211_rx_status *rx_status,
				       u32 rate_n_flags, पूर्णांक queue)
अणु
	चयन (phy_data->info_type) अणु
	हाल IWL_RX_PHY_INFO_TYPE_NONE:
	हाल IWL_RX_PHY_INFO_TYPE_CCK:
	हाल IWL_RX_PHY_INFO_TYPE_OFDM_LGCY:
	हाल IWL_RX_PHY_INFO_TYPE_HT:
	हाल IWL_RX_PHY_INFO_TYPE_VHT_SU:
	हाल IWL_RX_PHY_INFO_TYPE_VHT_MU:
		वापस;
	हाल IWL_RX_PHY_INFO_TYPE_HE_TB_EXT:
		he->data1 |= cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA1_SPTL_REUSE_KNOWN |
					 IEEE80211_RADIOTAP_HE_DATA1_SPTL_REUSE2_KNOWN |
					 IEEE80211_RADIOTAP_HE_DATA1_SPTL_REUSE3_KNOWN |
					 IEEE80211_RADIOTAP_HE_DATA1_SPTL_REUSE4_KNOWN);
		he->data4 |= le16_encode_bits(le32_get_bits(phy_data->d2,
							    IWL_RX_PHY_DATA2_HE_TB_EXT_SPTL_REUSE1),
					      IEEE80211_RADIOTAP_HE_DATA4_TB_SPTL_REUSE1);
		he->data4 |= le16_encode_bits(le32_get_bits(phy_data->d2,
							    IWL_RX_PHY_DATA2_HE_TB_EXT_SPTL_REUSE2),
					      IEEE80211_RADIOTAP_HE_DATA4_TB_SPTL_REUSE2);
		he->data4 |= le16_encode_bits(le32_get_bits(phy_data->d2,
							    IWL_RX_PHY_DATA2_HE_TB_EXT_SPTL_REUSE3),
					      IEEE80211_RADIOTAP_HE_DATA4_TB_SPTL_REUSE3);
		he->data4 |= le16_encode_bits(le32_get_bits(phy_data->d2,
							    IWL_RX_PHY_DATA2_HE_TB_EXT_SPTL_REUSE4),
					      IEEE80211_RADIOTAP_HE_DATA4_TB_SPTL_REUSE4);
		fallthrough;
	हाल IWL_RX_PHY_INFO_TYPE_HE_SU:
	हाल IWL_RX_PHY_INFO_TYPE_HE_MU:
	हाल IWL_RX_PHY_INFO_TYPE_HE_MU_EXT:
	हाल IWL_RX_PHY_INFO_TYPE_HE_TB:
		/* HE common */
		he->data1 |= cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA1_LDPC_XSYMSEG_KNOWN |
					 IEEE80211_RADIOTAP_HE_DATA1_DOPPLER_KNOWN |
					 IEEE80211_RADIOTAP_HE_DATA1_BSS_COLOR_KNOWN);
		he->data2 |= cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA2_PRE_FEC_PAD_KNOWN |
					 IEEE80211_RADIOTAP_HE_DATA2_PE_DISAMBIG_KNOWN |
					 IEEE80211_RADIOTAP_HE_DATA2_TXOP_KNOWN |
					 IEEE80211_RADIOTAP_HE_DATA2_NUM_LTF_SYMS_KNOWN);
		he->data3 |= le16_encode_bits(le32_get_bits(phy_data->d0,
							    IWL_RX_PHY_DATA0_HE_BSS_COLOR_MASK),
					      IEEE80211_RADIOTAP_HE_DATA3_BSS_COLOR);
		अगर (phy_data->info_type != IWL_RX_PHY_INFO_TYPE_HE_TB &&
		    phy_data->info_type != IWL_RX_PHY_INFO_TYPE_HE_TB_EXT) अणु
			he->data1 |= cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA1_UL_DL_KNOWN);
			he->data3 |= le16_encode_bits(le32_get_bits(phy_data->d0,
							    IWL_RX_PHY_DATA0_HE_UPLINK),
						      IEEE80211_RADIOTAP_HE_DATA3_UL_DL);
		पूर्ण
		he->data3 |= le16_encode_bits(le32_get_bits(phy_data->d0,
							    IWL_RX_PHY_DATA0_HE_LDPC_EXT_SYM),
					      IEEE80211_RADIOTAP_HE_DATA3_LDPC_XSYMSEG);
		he->data5 |= le16_encode_bits(le32_get_bits(phy_data->d0,
							    IWL_RX_PHY_DATA0_HE_PRE_FEC_PAD_MASK),
					      IEEE80211_RADIOTAP_HE_DATA5_PRE_FEC_PAD);
		he->data5 |= le16_encode_bits(le32_get_bits(phy_data->d0,
							    IWL_RX_PHY_DATA0_HE_PE_DISAMBIG),
					      IEEE80211_RADIOTAP_HE_DATA5_PE_DISAMBIG);
		he->data5 |= le16_encode_bits(le32_get_bits(phy_data->d1,
							    IWL_RX_PHY_DATA1_HE_LTF_NUM_MASK),
					      IEEE80211_RADIOTAP_HE_DATA5_NUM_LTF_SYMS);
		he->data6 |= le16_encode_bits(le32_get_bits(phy_data->d0,
							    IWL_RX_PHY_DATA0_HE_TXOP_DUR_MASK),
					      IEEE80211_RADIOTAP_HE_DATA6_TXOP);
		he->data6 |= le16_encode_bits(le32_get_bits(phy_data->d0,
							    IWL_RX_PHY_DATA0_HE_DOPPLER),
					      IEEE80211_RADIOTAP_HE_DATA6_DOPPLER);
		अवरोध;
	पूर्ण

	चयन (phy_data->info_type) अणु
	हाल IWL_RX_PHY_INFO_TYPE_HE_MU_EXT:
	हाल IWL_RX_PHY_INFO_TYPE_HE_MU:
	हाल IWL_RX_PHY_INFO_TYPE_HE_SU:
		he->data1 |= cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA1_SPTL_REUSE_KNOWN);
		he->data4 |= le16_encode_bits(le32_get_bits(phy_data->d0,
							    IWL_RX_PHY_DATA0_HE_SPATIAL_REUSE_MASK),
					      IEEE80211_RADIOTAP_HE_DATA4_SU_MU_SPTL_REUSE);
		अवरोध;
	शेष:
		/* nothing here */
		अवरोध;
	पूर्ण

	चयन (phy_data->info_type) अणु
	हाल IWL_RX_PHY_INFO_TYPE_HE_MU_EXT:
		he_mu->flags1 |=
			le16_encode_bits(le16_get_bits(phy_data->d4,
						       IWL_RX_PHY_DATA4_HE_MU_EXT_SIGB_DCM),
					 IEEE80211_RADIOTAP_HE_MU_FLAGS1_SIG_B_DCM);
		he_mu->flags1 |=
			le16_encode_bits(le16_get_bits(phy_data->d4,
						       IWL_RX_PHY_DATA4_HE_MU_EXT_SIGB_MCS_MASK),
					 IEEE80211_RADIOTAP_HE_MU_FLAGS1_SIG_B_MCS);
		he_mu->flags2 |=
			le16_encode_bits(le16_get_bits(phy_data->d4,
						       IWL_RX_PHY_DATA4_HE_MU_EXT_PREAMBLE_PUNC_TYPE_MASK),
					 IEEE80211_RADIOTAP_HE_MU_FLAGS2_PUNC_FROM_SIG_A_BW);
		iwl_mvm_decode_he_mu_ext(mvm, phy_data, rate_n_flags, he_mu);
		fallthrough;
	हाल IWL_RX_PHY_INFO_TYPE_HE_MU:
		he_mu->flags2 |=
			le16_encode_bits(le32_get_bits(phy_data->d1,
						       IWL_RX_PHY_DATA1_HE_MU_SIBG_SYM_OR_USER_NUM_MASK),
					 IEEE80211_RADIOTAP_HE_MU_FLAGS2_SIG_B_SYMS_USERS);
		he_mu->flags2 |=
			le16_encode_bits(le32_get_bits(phy_data->d1,
						       IWL_RX_PHY_DATA1_HE_MU_SIGB_COMPRESSION),
					 IEEE80211_RADIOTAP_HE_MU_FLAGS2_SIG_B_COMP);
		fallthrough;
	हाल IWL_RX_PHY_INFO_TYPE_HE_TB:
	हाल IWL_RX_PHY_INFO_TYPE_HE_TB_EXT:
		iwl_mvm_decode_he_phy_ru_alloc(phy_data, rate_n_flags,
					       he, he_mu, rx_status);
		अवरोध;
	हाल IWL_RX_PHY_INFO_TYPE_HE_SU:
		he->data1 |= cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA1_BEAM_CHANGE_KNOWN);
		he->data3 |= le16_encode_bits(le32_get_bits(phy_data->d0,
							    IWL_RX_PHY_DATA0_HE_BEAM_CHNG),
					      IEEE80211_RADIOTAP_HE_DATA3_BEAM_CHANGE);
		अवरोध;
	शेष:
		/* nothing */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम iwl_mvm_rx_he(काष्ठा iwl_mvm *mvm, काष्ठा sk_buff *skb,
			  काष्ठा iwl_mvm_rx_phy_data *phy_data,
			  u32 rate_n_flags, u16 phy_info, पूर्णांक queue)
अणु
	काष्ठा ieee80211_rx_status *rx_status = IEEE80211_SKB_RXCB(skb);
	काष्ठा ieee80211_radiotap_he *he = शून्य;
	काष्ठा ieee80211_radiotap_he_mu *he_mu = शून्य;
	u32 he_type = rate_n_flags & RATE_MCS_HE_TYPE_MSK;
	u8 stbc, ltf;
	अटल स्थिर काष्ठा ieee80211_radiotap_he known = अणु
		.data1 = cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA1_DATA_MCS_KNOWN |
				     IEEE80211_RADIOTAP_HE_DATA1_DATA_DCM_KNOWN |
				     IEEE80211_RADIOTAP_HE_DATA1_STBC_KNOWN |
				     IEEE80211_RADIOTAP_HE_DATA1_CODING_KNOWN),
		.data2 = cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA2_GI_KNOWN |
				     IEEE80211_RADIOTAP_HE_DATA2_TXBF_KNOWN),
	पूर्ण;
	अटल स्थिर काष्ठा ieee80211_radiotap_he_mu mu_known = अणु
		.flags1 = cpu_to_le16(IEEE80211_RADIOTAP_HE_MU_FLAGS1_SIG_B_MCS_KNOWN |
				      IEEE80211_RADIOTAP_HE_MU_FLAGS1_SIG_B_DCM_KNOWN |
				      IEEE80211_RADIOTAP_HE_MU_FLAGS1_SIG_B_SYMS_USERS_KNOWN |
				      IEEE80211_RADIOTAP_HE_MU_FLAGS1_SIG_B_COMP_KNOWN),
		.flags2 = cpu_to_le16(IEEE80211_RADIOTAP_HE_MU_FLAGS2_PUNC_FROM_SIG_A_BW_KNOWN |
				      IEEE80211_RADIOTAP_HE_MU_FLAGS2_BW_FROM_SIG_A_BW_KNOWN),
	पूर्ण;

	he = skb_put_data(skb, &known, माप(known));
	rx_status->flag |= RX_FLAG_RADIOTAP_HE;

	अगर (phy_data->info_type == IWL_RX_PHY_INFO_TYPE_HE_MU ||
	    phy_data->info_type == IWL_RX_PHY_INFO_TYPE_HE_MU_EXT) अणु
		he_mu = skb_put_data(skb, &mu_known, माप(mu_known));
		rx_status->flag |= RX_FLAG_RADIOTAP_HE_MU;
	पूर्ण

	/* report the AMPDU-खातापूर्ण bit on single frames */
	अगर (!queue && !(phy_info & IWL_RX_MPDU_PHY_AMPDU)) अणु
		rx_status->flag |= RX_FLAG_AMPDU_DETAILS;
		rx_status->flag |= RX_FLAG_AMPDU_खातापूर्ण_BIT_KNOWN;
		अगर (phy_data->d0 & cpu_to_le32(IWL_RX_PHY_DATA0_HE_DELIM_खातापूर्ण))
			rx_status->flag |= RX_FLAG_AMPDU_खातापूर्ण_BIT;
	पूर्ण

	अगर (phy_info & IWL_RX_MPDU_PHY_TSF_OVERLOAD)
		iwl_mvm_decode_he_phy_data(mvm, phy_data, he, he_mu, rx_status,
					   rate_n_flags, queue);

	/* update aggregation data क्रम monitor sake on शेष queue */
	अगर (!queue && (phy_info & IWL_RX_MPDU_PHY_TSF_OVERLOAD) &&
	    (phy_info & IWL_RX_MPDU_PHY_AMPDU)) अणु
		bool toggle_bit = phy_info & IWL_RX_MPDU_PHY_AMPDU_TOGGLE;

		/* toggle is चयनed whenever new aggregation starts */
		अगर (toggle_bit != mvm->ampdu_toggle) अणु
			rx_status->flag |= RX_FLAG_AMPDU_खातापूर्ण_BIT_KNOWN;
			अगर (phy_data->d0 & cpu_to_le32(IWL_RX_PHY_DATA0_HE_DELIM_खातापूर्ण))
				rx_status->flag |= RX_FLAG_AMPDU_खातापूर्ण_BIT;
		पूर्ण
	पूर्ण

	अगर (he_type == RATE_MCS_HE_TYPE_EXT_SU &&
	    rate_n_flags & RATE_MCS_HE_106T_MSK) अणु
		rx_status->bw = RATE_INFO_BW_HE_RU;
		rx_status->he_ru = NL80211_RATE_INFO_HE_RU_ALLOC_106;
	पूर्ण

	/* actually data is filled in mac80211 */
	अगर (he_type == RATE_MCS_HE_TYPE_SU ||
	    he_type == RATE_MCS_HE_TYPE_EXT_SU)
		he->data1 |=
			cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA1_BW_RU_ALLOC_KNOWN);

	stbc = (rate_n_flags & RATE_MCS_STBC_MSK) >> RATE_MCS_STBC_POS;
	rx_status->nss =
		((rate_n_flags & RATE_VHT_MCS_NSS_MSK) >>
					RATE_VHT_MCS_NSS_POS) + 1;
	rx_status->rate_idx = rate_n_flags & RATE_VHT_MCS_RATE_CODE_MSK;
	rx_status->encoding = RX_ENC_HE;
	rx_status->enc_flags |= stbc << RX_ENC_FLAG_STBC_SHIFT;
	अगर (rate_n_flags & RATE_MCS_BF_MSK)
		rx_status->enc_flags |= RX_ENC_FLAG_BF;

	rx_status->he_dcm =
		!!(rate_n_flags & RATE_HE_DUAL_CARRIER_MODE_MSK);

#घोषणा CHECK_TYPE(F)							\
	BUILD_BUG_ON(IEEE80211_RADIOTAP_HE_DATA1_FORMAT_ ## F !=	\
		     (RATE_MCS_HE_TYPE_ ## F >> RATE_MCS_HE_TYPE_POS))

	CHECK_TYPE(SU);
	CHECK_TYPE(EXT_SU);
	CHECK_TYPE(MU);
	CHECK_TYPE(TRIG);

	he->data1 |= cpu_to_le16(he_type >> RATE_MCS_HE_TYPE_POS);

	अगर (rate_n_flags & RATE_MCS_BF_MSK)
		he->data5 |= cpu_to_le16(IEEE80211_RADIOTAP_HE_DATA5_TXBF);

	चयन ((rate_n_flags & RATE_MCS_HE_GI_LTF_MSK) >>
		RATE_MCS_HE_GI_LTF_POS) अणु
	हाल 0:
		अगर (he_type == RATE_MCS_HE_TYPE_TRIG)
			rx_status->he_gi = NL80211_RATE_INFO_HE_GI_1_6;
		अन्यथा
			rx_status->he_gi = NL80211_RATE_INFO_HE_GI_0_8;
		अगर (he_type == RATE_MCS_HE_TYPE_MU)
			ltf = IEEE80211_RADIOTAP_HE_DATA5_LTF_SIZE_4X;
		अन्यथा
			ltf = IEEE80211_RADIOTAP_HE_DATA5_LTF_SIZE_1X;
		अवरोध;
	हाल 1:
		अगर (he_type == RATE_MCS_HE_TYPE_TRIG)
			rx_status->he_gi = NL80211_RATE_INFO_HE_GI_1_6;
		अन्यथा
			rx_status->he_gi = NL80211_RATE_INFO_HE_GI_0_8;
		ltf = IEEE80211_RADIOTAP_HE_DATA5_LTF_SIZE_2X;
		अवरोध;
	हाल 2:
		अगर (he_type == RATE_MCS_HE_TYPE_TRIG) अणु
			rx_status->he_gi = NL80211_RATE_INFO_HE_GI_3_2;
			ltf = IEEE80211_RADIOTAP_HE_DATA5_LTF_SIZE_4X;
		पूर्ण अन्यथा अणु
			rx_status->he_gi = NL80211_RATE_INFO_HE_GI_1_6;
			ltf = IEEE80211_RADIOTAP_HE_DATA5_LTF_SIZE_2X;
		पूर्ण
		अवरोध;
	हाल 3:
		अगर ((he_type == RATE_MCS_HE_TYPE_SU ||
		     he_type == RATE_MCS_HE_TYPE_EXT_SU) &&
		    rate_n_flags & RATE_MCS_SGI_MSK)
			rx_status->he_gi = NL80211_RATE_INFO_HE_GI_0_8;
		अन्यथा
			rx_status->he_gi = NL80211_RATE_INFO_HE_GI_3_2;
		ltf = IEEE80211_RADIOTAP_HE_DATA5_LTF_SIZE_4X;
		अवरोध;
	पूर्ण

	he->data5 |= le16_encode_bits(ltf,
				      IEEE80211_RADIOTAP_HE_DATA5_LTF_SIZE);
पूर्ण

अटल व्योम iwl_mvm_decode_lsig(काष्ठा sk_buff *skb,
				काष्ठा iwl_mvm_rx_phy_data *phy_data)
अणु
	काष्ठा ieee80211_rx_status *rx_status = IEEE80211_SKB_RXCB(skb);
	काष्ठा ieee80211_radiotap_lsig *lsig;

	चयन (phy_data->info_type) अणु
	हाल IWL_RX_PHY_INFO_TYPE_HT:
	हाल IWL_RX_PHY_INFO_TYPE_VHT_SU:
	हाल IWL_RX_PHY_INFO_TYPE_VHT_MU:
	हाल IWL_RX_PHY_INFO_TYPE_HE_TB_EXT:
	हाल IWL_RX_PHY_INFO_TYPE_HE_SU:
	हाल IWL_RX_PHY_INFO_TYPE_HE_MU:
	हाल IWL_RX_PHY_INFO_TYPE_HE_MU_EXT:
	हाल IWL_RX_PHY_INFO_TYPE_HE_TB:
		lsig = skb_put(skb, माप(*lsig));
		lsig->data1 = cpu_to_le16(IEEE80211_RADIOTAP_LSIG_DATA1_LENGTH_KNOWN);
		lsig->data2 = le16_encode_bits(le32_get_bits(phy_data->d1,
							     IWL_RX_PHY_DATA1_LSIG_LEN_MASK),
					       IEEE80211_RADIOTAP_LSIG_DATA2_LENGTH);
		rx_status->flag |= RX_FLAG_RADIOTAP_LSIG;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत u8 iwl_mvm_nl80211_band_from_rx_msdu(u8 phy_band)
अणु
	चयन (phy_band) अणु
	हाल PHY_BAND_24:
		वापस NL80211_BAND_2GHZ;
	हाल PHY_BAND_5:
		वापस NL80211_BAND_5GHZ;
	हाल PHY_BAND_6:
		वापस NL80211_BAND_6GHZ;
	शेष:
		WARN_ONCE(1, "Unsupported phy band (%u)\n", phy_band);
		वापस NL80211_BAND_5GHZ;
	पूर्ण
पूर्ण

काष्ठा iwl_rx_sta_csa अणु
	bool all_sta_unblocked;
	काष्ठा ieee80211_vअगर *vअगर;
पूर्ण;

अटल व्योम iwl_mvm_rx_get_sta_block_tx(व्योम *data, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_rx_sta_csa *rx_sta_csa = data;

	अगर (mvmsta->vअगर != rx_sta_csa->vअगर)
		वापस;

	अगर (mvmsta->disable_tx)
		rx_sta_csa->all_sta_unblocked = false;
पूर्ण

व्योम iwl_mvm_rx_mpdu_mq(काष्ठा iwl_mvm *mvm, काष्ठा napi_काष्ठा *napi,
			काष्ठा iwl_rx_cmd_buffer *rxb, पूर्णांक queue)
अणु
	काष्ठा ieee80211_rx_status *rx_status;
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_rx_mpdu_desc *desc = (व्योम *)pkt->data;
	काष्ठा ieee80211_hdr *hdr;
	u32 len;
	u32 pkt_len = iwl_rx_packet_payload_len(pkt);
	u32 rate_n_flags, gp2_on_air_rise;
	u16 phy_info;
	काष्ठा ieee80211_sta *sta = शून्य;
	काष्ठा sk_buff *skb;
	u8 crypt_len = 0, channel, energy_a, energy_b;
	माप_प्रकार desc_size;
	काष्ठा iwl_mvm_rx_phy_data phy_data = अणु
		.info_type = IWL_RX_PHY_INFO_TYPE_NONE,
	पूर्ण;
	bool csi = false;

	अगर (unlikely(test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status)))
		वापस;

	अगर (mvm->trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210)
		desc_size = माप(*desc);
	अन्यथा
		desc_size = IWL_RX_DESC_SIZE_V1;

	अगर (unlikely(pkt_len < desc_size)) अणु
		IWL_DEBUG_DROP(mvm, "Bad REPLY_RX_MPDU_CMD size\n");
		वापस;
	पूर्ण

	अगर (mvm->trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_AX210) अणु
		rate_n_flags = le32_to_cpu(desc->v3.rate_n_flags);
		channel = desc->v3.channel;
		gp2_on_air_rise = le32_to_cpu(desc->v3.gp2_on_air_rise);
		energy_a = desc->v3.energy_a;
		energy_b = desc->v3.energy_b;

		phy_data.d0 = desc->v3.phy_data0;
		phy_data.d1 = desc->v3.phy_data1;
		phy_data.d2 = desc->v3.phy_data2;
		phy_data.d3 = desc->v3.phy_data3;
	पूर्ण अन्यथा अणु
		rate_n_flags = le32_to_cpu(desc->v1.rate_n_flags);
		channel = desc->v1.channel;
		gp2_on_air_rise = le32_to_cpu(desc->v1.gp2_on_air_rise);
		energy_a = desc->v1.energy_a;
		energy_b = desc->v1.energy_b;

		phy_data.d0 = desc->v1.phy_data0;
		phy_data.d1 = desc->v1.phy_data1;
		phy_data.d2 = desc->v1.phy_data2;
		phy_data.d3 = desc->v1.phy_data3;
	पूर्ण

	len = le16_to_cpu(desc->mpdu_len);

	अगर (unlikely(len + desc_size > pkt_len)) अणु
		IWL_DEBUG_DROP(mvm, "FW lied about packet len\n");
		वापस;
	पूर्ण

	phy_info = le16_to_cpu(desc->phy_info);
	phy_data.d4 = desc->phy_data4;

	अगर (phy_info & IWL_RX_MPDU_PHY_TSF_OVERLOAD)
		phy_data.info_type =
			le32_get_bits(phy_data.d1,
				      IWL_RX_PHY_DATA1_INFO_TYPE_MASK);

	hdr = (व्योम *)(pkt->data + desc_size);
	/* Dont use dev_alloc_skb(), we'll have enough headroom once
	 * ieee80211_hdr pulled.
	 */
	skb = alloc_skb(128, GFP_ATOMIC);
	अगर (!skb) अणु
		IWL_ERR(mvm, "alloc_skb failed\n");
		वापस;
	पूर्ण

	अगर (desc->mac_flags2 & IWL_RX_MPDU_MFLG2_PAD) अणु
		/*
		 * If the device inserted padding it means that (it thought)
		 * the 802.11 header wasn't a multiple of 4 bytes दीर्घ. In
		 * this हाल, reserve two bytes at the start of the SKB to
		 * align the payload properly in हाल we end up copying it.
		 */
		skb_reserve(skb, 2);
	पूर्ण

	rx_status = IEEE80211_SKB_RXCB(skb);

	/* This may be overridden by iwl_mvm_rx_he() to HE_RU */
	चयन (rate_n_flags & RATE_MCS_CHAN_WIDTH_MSK) अणु
	हाल RATE_MCS_CHAN_WIDTH_20:
		अवरोध;
	हाल RATE_MCS_CHAN_WIDTH_40:
		rx_status->bw = RATE_INFO_BW_40;
		अवरोध;
	हाल RATE_MCS_CHAN_WIDTH_80:
		rx_status->bw = RATE_INFO_BW_80;
		अवरोध;
	हाल RATE_MCS_CHAN_WIDTH_160:
		rx_status->bw = RATE_INFO_BW_160;
		अवरोध;
	पूर्ण

	अगर (rate_n_flags & RATE_MCS_HE_MSK)
		iwl_mvm_rx_he(mvm, skb, &phy_data, rate_n_flags,
			      phy_info, queue);

	iwl_mvm_decode_lsig(skb, &phy_data);

	/*
	 * Keep packets with CRC errors (and with overrun) क्रम monitor mode
	 * (otherwise the firmware discards them) but mark them as bad.
	 */
	अगर (!(desc->status & cpu_to_le32(IWL_RX_MPDU_STATUS_CRC_OK)) ||
	    !(desc->status & cpu_to_le32(IWL_RX_MPDU_STATUS_OVERRUN_OK))) अणु
		IWL_DEBUG_RX(mvm, "Bad CRC or FIFO: 0x%08X.\n",
			     le32_to_cpu(desc->status));
		rx_status->flag |= RX_FLAG_FAILED_FCS_CRC;
	पूर्ण
	/* set the preamble flag अगर appropriate */
	अगर (rate_n_flags & RATE_MCS_CCK_MSK &&
	    phy_info & IWL_RX_MPDU_PHY_SHORT_PREAMBLE)
		rx_status->enc_flags |= RX_ENC_FLAG_SHORTPRE;

	अगर (likely(!(phy_info & IWL_RX_MPDU_PHY_TSF_OVERLOAD))) अणु
		u64 tsf_on_air_rise;

		अगर (mvm->trans->trans_cfg->device_family >=
		    IWL_DEVICE_FAMILY_AX210)
			tsf_on_air_rise = le64_to_cpu(desc->v3.tsf_on_air_rise);
		अन्यथा
			tsf_on_air_rise = le64_to_cpu(desc->v1.tsf_on_air_rise);

		rx_status->maस_समय = tsf_on_air_rise;
		/* TSF as indicated by the firmware is at INA समय */
		rx_status->flag |= RX_FLAG_MACTIME_PLCP_START;
	पूर्ण

	rx_status->device_बारtamp = gp2_on_air_rise;
	अगर (iwl_mvm_is_band_in_rx_supported(mvm)) अणु
		u8 band = BAND_IN_RX_STATUS(desc->mac_phy_idx);

		rx_status->band = iwl_mvm_nl80211_band_from_rx_msdu(band);
	पूर्ण अन्यथा अणु
		rx_status->band = channel > 14 ? NL80211_BAND_5GHZ :
			NL80211_BAND_2GHZ;
	पूर्ण
	rx_status->freq = ieee80211_channel_to_frequency(channel,
							 rx_status->band);
	iwl_mvm_get_संकेत_strength(mvm, rx_status, rate_n_flags, energy_a,
				    energy_b);

	/* update aggregation data क्रम monitor sake on शेष queue */
	अगर (!queue && (phy_info & IWL_RX_MPDU_PHY_AMPDU)) अणु
		bool toggle_bit = phy_info & IWL_RX_MPDU_PHY_AMPDU_TOGGLE;

		rx_status->flag |= RX_FLAG_AMPDU_DETAILS;
		/*
		 * Toggle is चयनed whenever new aggregation starts. Make
		 * sure ampdu_reference is never 0 so we can later use it to
		 * see अगर the frame was really part of an A-MPDU or not.
		 */
		अगर (toggle_bit != mvm->ampdu_toggle) अणु
			mvm->ampdu_ref++;
			अगर (mvm->ampdu_ref == 0)
				mvm->ampdu_ref++;
			mvm->ampdu_toggle = toggle_bit;
		पूर्ण
		rx_status->ampdu_reference = mvm->ampdu_ref;
	पूर्ण

	अगर (unlikely(mvm->monitor_on))
		iwl_mvm_add_rtap_snअगरfer_config(mvm, skb);

	rcu_पढ़ो_lock();

	अगर (desc->status & cpu_to_le32(IWL_RX_MPDU_STATUS_SRC_STA_FOUND)) अणु
		u8 id = le32_get_bits(desc->status, IWL_RX_MPDU_STATUS_STA_ID);

		अगर (!WARN_ON_ONCE(id >= mvm->fw->ucode_capa.num_stations)) अणु
			sta = rcu_dereference(mvm->fw_id_to_mac_id[id]);
			अगर (IS_ERR(sta))
				sta = शून्य;
		पूर्ण
	पूर्ण अन्यथा अगर (!is_multicast_ether_addr(hdr->addr2)) अणु
		/*
		 * This is fine since we prevent two stations with the same
		 * address from being added.
		 */
		sta = ieee80211_find_sta_by_अगरaddr(mvm->hw, hdr->addr2, शून्य);
	पूर्ण

	अगर (iwl_mvm_rx_crypto(mvm, sta, hdr, rx_status, phy_info, desc,
			      le32_to_cpu(pkt->len_n_flags), queue,
			      &crypt_len)) अणु
		kमुक्त_skb(skb);
		जाओ out;
	पूर्ण

	अगर (sta) अणु
		काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
		काष्ठा ieee80211_vअगर *tx_blocked_vअगर =
			rcu_dereference(mvm->csa_tx_blocked_vअगर);
		u8 baid = (u8)((le32_to_cpu(desc->reorder_data) &
			       IWL_RX_MPDU_REORDER_BAID_MASK) >>
			       IWL_RX_MPDU_REORDER_BAID_SHIFT);
		काष्ठा iwl_fw_dbg_trigger_tlv *trig;
		काष्ठा ieee80211_vअगर *vअगर = mvmsta->vअगर;

		अगर (!mvm->tcm.छोड़ोd && len >= माप(*hdr) &&
		    !is_multicast_ether_addr(hdr->addr1) &&
		    ieee80211_is_data(hdr->frame_control) &&
		    समय_after(jअगरfies, mvm->tcm.ts + MVM_TCM_PERIOD))
			schedule_delayed_work(&mvm->tcm.work, 0);

		/*
		 * We have tx blocked stations (with CS bit). If we heard
		 * frames from a blocked station on a new channel we can
		 * TX to it again.
		 */
		अगर (unlikely(tx_blocked_vअगर) && tx_blocked_vअगर == vअगर) अणु
			काष्ठा iwl_mvm_vअगर *mvmvअगर =
				iwl_mvm_vअगर_from_mac80211(tx_blocked_vअगर);
			काष्ठा iwl_rx_sta_csa rx_sta_csa = अणु
				.all_sta_unblocked = true,
				.vअगर = tx_blocked_vअगर,
			पूर्ण;

			अगर (mvmvअगर->csa_target_freq == rx_status->freq)
				iwl_mvm_sta_modअगरy_disable_tx_ap(mvm, sta,
								 false);
			ieee80211_iterate_stations_atomic(mvm->hw,
							  iwl_mvm_rx_get_sta_block_tx,
							  &rx_sta_csa);

			अगर (rx_sta_csa.all_sta_unblocked) अणु
				RCU_INIT_POINTER(mvm->csa_tx_blocked_vअगर, शून्य);
				/* Unblock BCAST / MCAST station */
				iwl_mvm_modअगरy_all_sta_disable_tx(mvm, mvmvअगर, false);
				cancel_delayed_work_sync(&mvm->cs_tx_unblock_dwork);
			पूर्ण
		पूर्ण

		rs_update_last_rssi(mvm, mvmsta, rx_status);

		trig = iwl_fw_dbg_trigger_on(&mvm->fwrt,
					     ieee80211_vअगर_to_wdev(vअगर),
					     FW_DBG_TRIGGER_RSSI);

		अगर (trig && ieee80211_is_beacon(hdr->frame_control)) अणु
			काष्ठा iwl_fw_dbg_trigger_low_rssi *rssi_trig;
			s32 rssi;

			rssi_trig = (व्योम *)trig->data;
			rssi = le32_to_cpu(rssi_trig->rssi);

			अगर (rx_status->संकेत < rssi)
				iwl_fw_dbg_collect_trig(&mvm->fwrt, trig,
							शून्य);
		पूर्ण

		अगर (ieee80211_is_data(hdr->frame_control))
			iwl_mvm_rx_csum(mvm, sta, skb, pkt);

		अगर (iwl_mvm_is_dup(sta, queue, rx_status, hdr, desc)) अणु
			kमुक्त_skb(skb);
			जाओ out;
		पूर्ण

		/*
		 * Our hardware de-aggregates AMSDUs but copies the mac header
		 * as it to the de-aggregated MPDUs. We need to turn off the
		 * AMSDU bit in the QoS control ourselves.
		 * In addition, HW reverses addr3 and addr4 - reverse it back.
		 */
		अगर ((desc->mac_flags2 & IWL_RX_MPDU_MFLG2_AMSDU) &&
		    !WARN_ON(!ieee80211_is_data_qos(hdr->frame_control))) अणु
			u8 *qc = ieee80211_get_qos_ctl(hdr);

			*qc &= ~IEEE80211_QOS_CTL_A_MSDU_PRESENT;

			अगर (mvm->trans->trans_cfg->device_family ==
			    IWL_DEVICE_FAMILY_9000) अणु
				iwl_mvm_flip_address(hdr->addr3);

				अगर (ieee80211_has_a4(hdr->frame_control))
					iwl_mvm_flip_address(hdr->addr4);
			पूर्ण
		पूर्ण
		अगर (baid != IWL_RX_REORDER_DATA_INVALID_BAID) अणु
			u32 reorder_data = le32_to_cpu(desc->reorder_data);

			iwl_mvm_agg_rx_received(mvm, reorder_data, baid);
		पूर्ण
	पूर्ण

	अगर (!(rate_n_flags & RATE_MCS_CCK_MSK) &&
	    rate_n_flags & RATE_MCS_SGI_MSK)
		rx_status->enc_flags |= RX_ENC_FLAG_SHORT_GI;
	अगर (rate_n_flags & RATE_HT_MCS_GF_MSK)
		rx_status->enc_flags |= RX_ENC_FLAG_HT_GF;
	अगर (rate_n_flags & RATE_MCS_LDPC_MSK)
		rx_status->enc_flags |= RX_ENC_FLAG_LDPC;
	अगर (rate_n_flags & RATE_MCS_HT_MSK) अणु
		u8 stbc = (rate_n_flags & RATE_MCS_STBC_MSK) >>
				RATE_MCS_STBC_POS;
		rx_status->encoding = RX_ENC_HT;
		rx_status->rate_idx = rate_n_flags & RATE_HT_MCS_INDEX_MSK;
		rx_status->enc_flags |= stbc << RX_ENC_FLAG_STBC_SHIFT;
	पूर्ण अन्यथा अगर (rate_n_flags & RATE_MCS_VHT_MSK) अणु
		u8 stbc = (rate_n_flags & RATE_MCS_STBC_MSK) >>
				RATE_MCS_STBC_POS;
		rx_status->nss =
			((rate_n_flags & RATE_VHT_MCS_NSS_MSK) >>
						RATE_VHT_MCS_NSS_POS) + 1;
		rx_status->rate_idx = rate_n_flags & RATE_VHT_MCS_RATE_CODE_MSK;
		rx_status->encoding = RX_ENC_VHT;
		rx_status->enc_flags |= stbc << RX_ENC_FLAG_STBC_SHIFT;
		अगर (rate_n_flags & RATE_MCS_BF_MSK)
			rx_status->enc_flags |= RX_ENC_FLAG_BF;
	पूर्ण अन्यथा अगर (!(rate_n_flags & RATE_MCS_HE_MSK)) अणु
		पूर्णांक rate = iwl_mvm_legacy_rate_to_mac80211_idx(rate_n_flags,
							       rx_status->band);

		अगर (WARN(rate < 0 || rate > 0xFF,
			 "Invalid rate flags 0x%x, band %d,\n",
			 rate_n_flags, rx_status->band)) अणु
			kमुक्त_skb(skb);
			जाओ out;
		पूर्ण
		rx_status->rate_idx = rate;
	पूर्ण

	/* management stuff on शेष queue */
	अगर (!queue) अणु
		अगर (unlikely((ieee80211_is_beacon(hdr->frame_control) ||
			      ieee80211_is_probe_resp(hdr->frame_control)) &&
			     mvm->sched_scan_pass_all ==
			     SCHED_SCAN_PASS_ALL_ENABLED))
			mvm->sched_scan_pass_all = SCHED_SCAN_PASS_ALL_FOUND;

		अगर (unlikely(ieee80211_is_beacon(hdr->frame_control) ||
			     ieee80211_is_probe_resp(hdr->frame_control)))
			rx_status->bootसमय_ns = kसमय_get_bootसमय_ns();
	पूर्ण

	अगर (iwl_mvm_create_skb(mvm, skb, hdr, len, crypt_len, rxb)) अणु
		kमुक्त_skb(skb);
		जाओ out;
	पूर्ण

	अगर (!iwl_mvm_reorder(mvm, napi, queue, sta, skb, desc))
		iwl_mvm_pass_packet_to_mac80211(mvm, napi, skb, queue,
						sta, csi);
out:
	rcu_पढ़ो_unlock();
पूर्ण

व्योम iwl_mvm_rx_monitor_no_data(काष्ठा iwl_mvm *mvm, काष्ठा napi_काष्ठा *napi,
				काष्ठा iwl_rx_cmd_buffer *rxb, पूर्णांक queue)
अणु
	काष्ठा ieee80211_rx_status *rx_status;
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_rx_no_data *desc = (व्योम *)pkt->data;
	u32 rate_n_flags = le32_to_cpu(desc->rate);
	u32 gp2_on_air_rise = le32_to_cpu(desc->on_air_rise_समय);
	u32 rssi = le32_to_cpu(desc->rssi);
	u32 info_type = le32_to_cpu(desc->info) & RX_NO_DATA_INFO_TYPE_MSK;
	u16 phy_info = IWL_RX_MPDU_PHY_TSF_OVERLOAD;
	काष्ठा ieee80211_sta *sta = शून्य;
	काष्ठा sk_buff *skb;
	u8 channel, energy_a, energy_b;
	काष्ठा iwl_mvm_rx_phy_data phy_data = अणु
		.d0 = desc->phy_info[0],
		.info_type = IWL_RX_PHY_INFO_TYPE_NONE,
	पूर्ण;

	अगर (unlikely(iwl_rx_packet_payload_len(pkt) < माप(*desc)))
		वापस;

	अगर (unlikely(test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status)))
		वापस;

	energy_a = (rssi & RX_NO_DATA_CHAIN_A_MSK) >> RX_NO_DATA_CHAIN_A_POS;
	energy_b = (rssi & RX_NO_DATA_CHAIN_B_MSK) >> RX_NO_DATA_CHAIN_B_POS;
	channel = (rssi & RX_NO_DATA_CHANNEL_MSK) >> RX_NO_DATA_CHANNEL_POS;

	phy_data.info_type =
		le32_get_bits(desc->phy_info[1],
			      IWL_RX_PHY_DATA1_INFO_TYPE_MASK);

	/* Dont use dev_alloc_skb(), we'll have enough headroom once
	 * ieee80211_hdr pulled.
	 */
	skb = alloc_skb(128, GFP_ATOMIC);
	अगर (!skb) अणु
		IWL_ERR(mvm, "alloc_skb failed\n");
		वापस;
	पूर्ण

	rx_status = IEEE80211_SKB_RXCB(skb);

	/* 0-length PSDU */
	rx_status->flag |= RX_FLAG_NO_PSDU;

	चयन (info_type) अणु
	हाल RX_NO_DATA_INFO_TYPE_NDP:
		rx_status->zero_length_psdu_type =
			IEEE80211_RADIOTAP_ZERO_LEN_PSDU_SOUNDING;
		अवरोध;
	हाल RX_NO_DATA_INFO_TYPE_MU_UNMATCHED:
	हाल RX_NO_DATA_INFO_TYPE_HE_TB_UNMATCHED:
		rx_status->zero_length_psdu_type =
			IEEE80211_RADIOTAP_ZERO_LEN_PSDU_NOT_CAPTURED;
		अवरोध;
	शेष:
		rx_status->zero_length_psdu_type =
			IEEE80211_RADIOTAP_ZERO_LEN_PSDU_VENDOR;
		अवरोध;
	पूर्ण

	/* This may be overridden by iwl_mvm_rx_he() to HE_RU */
	चयन (rate_n_flags & RATE_MCS_CHAN_WIDTH_MSK) अणु
	हाल RATE_MCS_CHAN_WIDTH_20:
		अवरोध;
	हाल RATE_MCS_CHAN_WIDTH_40:
		rx_status->bw = RATE_INFO_BW_40;
		अवरोध;
	हाल RATE_MCS_CHAN_WIDTH_80:
		rx_status->bw = RATE_INFO_BW_80;
		अवरोध;
	हाल RATE_MCS_CHAN_WIDTH_160:
		rx_status->bw = RATE_INFO_BW_160;
		अवरोध;
	पूर्ण

	अगर (rate_n_flags & RATE_MCS_HE_MSK)
		iwl_mvm_rx_he(mvm, skb, &phy_data, rate_n_flags,
			      phy_info, queue);

	iwl_mvm_decode_lsig(skb, &phy_data);

	rx_status->device_बारtamp = gp2_on_air_rise;
	rx_status->band = channel > 14 ? NL80211_BAND_5GHZ :
		NL80211_BAND_2GHZ;
	rx_status->freq = ieee80211_channel_to_frequency(channel,
							 rx_status->band);
	iwl_mvm_get_संकेत_strength(mvm, rx_status, rate_n_flags, energy_a,
				    energy_b);

	rcu_पढ़ो_lock();

	अगर (!(rate_n_flags & RATE_MCS_CCK_MSK) &&
	    rate_n_flags & RATE_MCS_SGI_MSK)
		rx_status->enc_flags |= RX_ENC_FLAG_SHORT_GI;
	अगर (rate_n_flags & RATE_HT_MCS_GF_MSK)
		rx_status->enc_flags |= RX_ENC_FLAG_HT_GF;
	अगर (rate_n_flags & RATE_MCS_LDPC_MSK)
		rx_status->enc_flags |= RX_ENC_FLAG_LDPC;
	अगर (rate_n_flags & RATE_MCS_HT_MSK) अणु
		u8 stbc = (rate_n_flags & RATE_MCS_STBC_MSK) >>
				RATE_MCS_STBC_POS;
		rx_status->encoding = RX_ENC_HT;
		rx_status->rate_idx = rate_n_flags & RATE_HT_MCS_INDEX_MSK;
		rx_status->enc_flags |= stbc << RX_ENC_FLAG_STBC_SHIFT;
	पूर्ण अन्यथा अगर (rate_n_flags & RATE_MCS_VHT_MSK) अणु
		u8 stbc = (rate_n_flags & RATE_MCS_STBC_MSK) >>
				RATE_MCS_STBC_POS;
		rx_status->rate_idx = rate_n_flags & RATE_VHT_MCS_RATE_CODE_MSK;
		rx_status->encoding = RX_ENC_VHT;
		rx_status->enc_flags |= stbc << RX_ENC_FLAG_STBC_SHIFT;
		अगर (rate_n_flags & RATE_MCS_BF_MSK)
			rx_status->enc_flags |= RX_ENC_FLAG_BF;
		/*
		 * take the nss from the rx_vec since the rate_n_flags has
		 * only 2 bits क्रम the nss which gives a max of 4 ss but
		 * there may be up to 8 spatial streams
		 */
		rx_status->nss =
			le32_get_bits(desc->rx_vec[0],
				      RX_NO_DATA_RX_VEC0_VHT_NSTS_MSK) + 1;
	पूर्ण अन्यथा अगर (rate_n_flags & RATE_MCS_HE_MSK) अणु
		rx_status->nss =
			le32_get_bits(desc->rx_vec[0],
				      RX_NO_DATA_RX_VEC0_HE_NSTS_MSK) + 1;
	पूर्ण अन्यथा अणु
		पूर्णांक rate = iwl_mvm_legacy_rate_to_mac80211_idx(rate_n_flags,
							       rx_status->band);

		अगर (WARN(rate < 0 || rate > 0xFF,
			 "Invalid rate flags 0x%x, band %d,\n",
			 rate_n_flags, rx_status->band)) अणु
			kमुक्त_skb(skb);
			जाओ out;
		पूर्ण
		rx_status->rate_idx = rate;
	पूर्ण

	ieee80211_rx_napi(mvm->hw, sta, skb, napi);
out:
	rcu_पढ़ो_unlock();
पूर्ण

व्योम iwl_mvm_rx_frame_release(काष्ठा iwl_mvm *mvm, काष्ठा napi_काष्ठा *napi,
			      काष्ठा iwl_rx_cmd_buffer *rxb, पूर्णांक queue)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_frame_release *release = (व्योम *)pkt->data;

	अगर (unlikely(iwl_rx_packet_payload_len(pkt) < माप(*release)))
		वापस;

	iwl_mvm_release_frames_from_notअगर(mvm, napi, release->baid,
					  le16_to_cpu(release->nssn),
					  queue, 0);
पूर्ण

व्योम iwl_mvm_rx_bar_frame_release(काष्ठा iwl_mvm *mvm, काष्ठा napi_काष्ठा *napi,
				  काष्ठा iwl_rx_cmd_buffer *rxb, पूर्णांक queue)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_bar_frame_release *release = (व्योम *)pkt->data;
	अचिन्हित पूर्णांक baid = le32_get_bits(release->ba_info,
					  IWL_BAR_FRAME_RELEASE_BAID_MASK);
	अचिन्हित पूर्णांक nssn = le32_get_bits(release->ba_info,
					  IWL_BAR_FRAME_RELEASE_NSSN_MASK);
	अचिन्हित पूर्णांक sta_id = le32_get_bits(release->sta_tid,
					    IWL_BAR_FRAME_RELEASE_STA_MASK);
	अचिन्हित पूर्णांक tid = le32_get_bits(release->sta_tid,
					 IWL_BAR_FRAME_RELEASE_TID_MASK);
	काष्ठा iwl_mvm_baid_data *baid_data;

	अगर (unlikely(iwl_rx_packet_payload_len(pkt) < माप(*release)))
		वापस;

	अगर (WARN_ON_ONCE(baid == IWL_RX_REORDER_DATA_INVALID_BAID ||
			 baid >= ARRAY_SIZE(mvm->baid_map)))
		वापस;

	rcu_पढ़ो_lock();
	baid_data = rcu_dereference(mvm->baid_map[baid]);
	अगर (!baid_data) अणु
		IWL_DEBUG_RX(mvm,
			     "Got valid BAID %d but not allocated, invalid BAR release!\n",
			      baid);
		जाओ out;
	पूर्ण

	अगर (WARN(tid != baid_data->tid || sta_id != baid_data->sta_id,
		 "baid 0x%x is mapped to sta:%d tid:%d, but BAR release received for sta:%d tid:%d\n",
		 baid, baid_data->sta_id, baid_data->tid, sta_id,
		 tid))
		जाओ out;

	iwl_mvm_release_frames_from_notअगर(mvm, napi, baid, nssn, queue, 0);
out:
	rcu_पढ़ो_unlock();
पूर्ण
