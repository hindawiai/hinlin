<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश "iwl-trans.h"
#समावेश "mvm.h"
#समावेश "fw-api.h"

/*
 * iwl_mvm_rx_rx_phy_cmd - REPLY_RX_PHY_CMD handler
 *
 * Copies the phy inक्रमmation in mvm->last_phy_info, it will be used when the
 * actual data will come from the fw in the next packet.
 */
व्योम iwl_mvm_rx_rx_phy_cmd(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	अचिन्हित पूर्णांक pkt_len = iwl_rx_packet_payload_len(pkt);

	अगर (unlikely(pkt_len < माप(mvm->last_phy_info)))
		वापस;

	स_नकल(&mvm->last_phy_info, pkt->data, माप(mvm->last_phy_info));
	mvm->ampdu_ref++;

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	अगर (mvm->last_phy_info.phy_flags & cpu_to_le16(RX_RES_PHY_FLAGS_AGG)) अणु
		spin_lock(&mvm->drv_stats_lock);
		mvm->drv_rx_stats.ampdu_count++;
		spin_unlock(&mvm->drv_stats_lock);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * iwl_mvm_pass_packet_to_mac80211 - builds the packet क्रम mac80211
 *
 * Adds the rxb to a new skb and give it to mac80211
 */
अटल व्योम iwl_mvm_pass_packet_to_mac80211(काष्ठा iwl_mvm *mvm,
					    काष्ठा ieee80211_sta *sta,
					    काष्ठा napi_काष्ठा *napi,
					    काष्ठा sk_buff *skb,
					    काष्ठा ieee80211_hdr *hdr, u16 len,
					    u8 crypt_len,
					    काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	अचिन्हित पूर्णांक hdrlen = ieee80211_hdrlen(hdr->frame_control);
	अचिन्हित पूर्णांक fraglen;

	/*
	 * The 'hdrlen' (plus the 8 bytes क्रम the SNAP and the crypt_len,
	 * but those are all multiples of 4 दीर्घ) all goes away, but we
	 * want the *end* of it, which is going to be the start of the IP
	 * header, to be aligned when it माला_लो pulled in.
	 * The beginning of the skb->data is aligned on at least a 4-byte
	 * boundary after allocation. Everything here is aligned at least
	 * on a 2-byte boundary so we can just take hdrlen & 3 and pad by
	 * the result.
	 */
	skb_reserve(skb, hdrlen & 3);

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
	hdrlen = (len <= skb_tailroom(skb)) ? len : hdrlen + crypt_len + 8;

	skb_put_data(skb, hdr, hdrlen);
	fraglen = len - hdrlen;

	अगर (fraglen) अणु
		पूर्णांक offset = (व्योम *)hdr + hdrlen -
			     rxb_addr(rxb) + rxb_offset(rxb);

		skb_add_rx_frag(skb, 0, rxb_steal_page(rxb), offset,
				fraglen, rxb->truesize);
	पूर्ण

	ieee80211_rx_napi(mvm->hw, sta, skb, napi);
पूर्ण

/*
 * iwl_mvm_get_संकेत_strength - use new rx PHY INFO API
 * values are reported by the fw as positive values - need to negate
 * to obtain their dBM.  Account क्रम missing antennas by replacing 0
 * values by -256dBm: practically 0 घातer and a non-feasible 8 bit value.
 */
अटल व्योम iwl_mvm_get_संकेत_strength(काष्ठा iwl_mvm *mvm,
					काष्ठा iwl_rx_phy_info *phy_info,
					काष्ठा ieee80211_rx_status *rx_status)
अणु
	पूर्णांक energy_a, energy_b, energy_c, max_energy;
	u32 val;

	val =
	    le32_to_cpu(phy_info->non_cfg_phy[IWL_RX_INFO_ENERGY_ANT_ABC_IDX]);
	energy_a = (val & IWL_RX_INFO_ENERGY_ANT_A_MSK) >>
						IWL_RX_INFO_ENERGY_ANT_A_POS;
	energy_a = energy_a ? -energy_a : S8_MIN;
	energy_b = (val & IWL_RX_INFO_ENERGY_ANT_B_MSK) >>
						IWL_RX_INFO_ENERGY_ANT_B_POS;
	energy_b = energy_b ? -energy_b : S8_MIN;
	energy_c = (val & IWL_RX_INFO_ENERGY_ANT_C_MSK) >>
						IWL_RX_INFO_ENERGY_ANT_C_POS;
	energy_c = energy_c ? -energy_c : S8_MIN;
	max_energy = max(energy_a, energy_b);
	max_energy = max(max_energy, energy_c);

	IWL_DEBUG_STATS(mvm, "energy In A %d B %d C %d , and max %d\n",
			energy_a, energy_b, energy_c, max_energy);

	rx_status->संकेत = max_energy;
	rx_status->chains = (le16_to_cpu(phy_info->phy_flags) &
				RX_RES_PHY_FLAGS_ANTENNA)
					>> RX_RES_PHY_FLAGS_ANTENNA_POS;
	rx_status->chain_संकेत[0] = energy_a;
	rx_status->chain_संकेत[1] = energy_b;
	rx_status->chain_संकेत[2] = energy_c;
पूर्ण

/*
 * iwl_mvm_set_mac80211_rx_flag - translate fw status to mac80211 क्रमmat
 * @mvm: the mvm object
 * @hdr: 80211 header
 * @stats: status in mac80211's क्रमmat
 * @rx_pkt_status: status coming from fw
 *
 * वापसs non 0 value अगर the packet should be dropped
 */
अटल u32 iwl_mvm_set_mac80211_rx_flag(काष्ठा iwl_mvm *mvm,
					काष्ठा ieee80211_hdr *hdr,
					काष्ठा ieee80211_rx_status *stats,
					u32 rx_pkt_status,
					u8 *crypt_len)
अणु
	अगर (!ieee80211_has_रक्षित(hdr->frame_control) ||
	    (rx_pkt_status & RX_MPDU_RES_STATUS_SEC_ENC_MSK) ==
			     RX_MPDU_RES_STATUS_SEC_NO_ENC)
		वापस 0;

	/* packet was encrypted with unknown alg */
	अगर ((rx_pkt_status & RX_MPDU_RES_STATUS_SEC_ENC_MSK) ==
					RX_MPDU_RES_STATUS_SEC_ENC_ERR)
		वापस 0;

	चयन (rx_pkt_status & RX_MPDU_RES_STATUS_SEC_ENC_MSK) अणु
	हाल RX_MPDU_RES_STATUS_SEC_CCM_ENC:
		/* alg is CCM: check MIC only */
		अगर (!(rx_pkt_status & RX_MPDU_RES_STATUS_MIC_OK))
			वापस -1;

		stats->flag |= RX_FLAG_DECRYPTED;
		*crypt_len = IEEE80211_CCMP_HDR_LEN;
		वापस 0;

	हाल RX_MPDU_RES_STATUS_SEC_TKIP_ENC:
		/* Don't drop the frame and decrypt it in SW */
		अगर (!fw_has_api(&mvm->fw->ucode_capa,
				IWL_UCODE_TLV_API_DEPRECATE_TTAK) &&
		    !(rx_pkt_status & RX_MPDU_RES_STATUS_TTAK_OK))
			वापस 0;
		*crypt_len = IEEE80211_TKIP_IV_LEN;
		fallthrough;

	हाल RX_MPDU_RES_STATUS_SEC_WEP_ENC:
		अगर (!(rx_pkt_status & RX_MPDU_RES_STATUS_ICV_OK))
			वापस -1;

		stats->flag |= RX_FLAG_DECRYPTED;
		अगर ((rx_pkt_status & RX_MPDU_RES_STATUS_SEC_ENC_MSK) ==
				RX_MPDU_RES_STATUS_SEC_WEP_ENC)
			*crypt_len = IEEE80211_WEP_IV_LEN;
		वापस 0;

	हाल RX_MPDU_RES_STATUS_SEC_EXT_ENC:
		अगर (!(rx_pkt_status & RX_MPDU_RES_STATUS_MIC_OK))
			वापस -1;
		stats->flag |= RX_FLAG_DECRYPTED;
		वापस 0;

	शेष:
		/* Expected in monitor (not having the keys) */
		अगर (!mvm->monitor_on)
			IWL_ERR(mvm, "Unhandled alg: 0x%x\n", rx_pkt_status);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iwl_mvm_rx_handle_tcm(काष्ठा iwl_mvm *mvm,
				  काष्ठा ieee80211_sta *sta,
				  काष्ठा ieee80211_hdr *hdr, u32 len,
				  काष्ठा iwl_rx_phy_info *phy_info,
				  u32 rate_n_flags)
अणु
	काष्ठा iwl_mvm_sta *mvmsta;
	काष्ठा iwl_mvm_tcm_mac *mdata;
	पूर्णांक mac;
	पूर्णांक ac = IEEE80211_AC_BE; /* treat non-QoS as BE */
	काष्ठा iwl_mvm_vअगर *mvmvअगर;
	/* expected throughput in 100Kbps, single stream, 20 MHz */
	अटल स्थिर u8 thresh_tpt[] = अणु
		9, 18, 30, 42, 60, 78, 90, 96, 120, 135,
	पूर्ण;
	u16 thr;

	अगर (ieee80211_is_data_qos(hdr->frame_control))
		ac = tid_to_mac80211_ac[ieee80211_get_tid(hdr)];

	mvmsta = iwl_mvm_sta_from_mac80211(sta);
	mac = mvmsta->mac_id_n_color & FW_CTXT_ID_MSK;

	अगर (समय_after(jअगरfies, mvm->tcm.ts + MVM_TCM_PERIOD))
		schedule_delayed_work(&mvm->tcm.work, 0);
	mdata = &mvm->tcm.data[mac];
	mdata->rx.pkts[ac]++;

	/* count the airसमय only once क्रम each ampdu */
	अगर (mdata->rx.last_ampdu_ref != mvm->ampdu_ref) अणु
		mdata->rx.last_ampdu_ref = mvm->ampdu_ref;
		mdata->rx.airसमय += le16_to_cpu(phy_info->frame_समय);
	पूर्ण

	अगर (!(rate_n_flags & (RATE_MCS_HT_MSK | RATE_MCS_VHT_MSK)))
		वापस;

	mvmvअगर = iwl_mvm_vअगर_from_mac80211(mvmsta->vअगर);

	अगर (mdata->खोलोed_rx_ba_sessions ||
	    mdata->uapsd_nonagg_detect.detected ||
	    (!mvmvअगर->queue_params[IEEE80211_AC_VO].uapsd &&
	     !mvmvअगर->queue_params[IEEE80211_AC_VI].uapsd &&
	     !mvmvअगर->queue_params[IEEE80211_AC_BE].uapsd &&
	     !mvmvअगर->queue_params[IEEE80211_AC_BK].uapsd) ||
	    mvmsta->sta_id != mvmvअगर->ap_sta_id)
		वापस;

	अगर (rate_n_flags & RATE_MCS_HT_MSK) अणु
		thr = thresh_tpt[rate_n_flags & RATE_HT_MCS_RATE_CODE_MSK];
		thr *= 1 + ((rate_n_flags & RATE_HT_MCS_NSS_MSK) >>
					RATE_HT_MCS_NSS_POS);
	पूर्ण अन्यथा अणु
		अगर (WARN_ON((rate_n_flags & RATE_VHT_MCS_RATE_CODE_MSK) >=
				ARRAY_SIZE(thresh_tpt)))
			वापस;
		thr = thresh_tpt[rate_n_flags & RATE_VHT_MCS_RATE_CODE_MSK];
		thr *= 1 + ((rate_n_flags & RATE_VHT_MCS_NSS_MSK) >>
					RATE_VHT_MCS_NSS_POS);
	पूर्ण

	thr <<= ((rate_n_flags & RATE_MCS_CHAN_WIDTH_MSK) >>
				RATE_MCS_CHAN_WIDTH_POS);

	mdata->uapsd_nonagg_detect.rx_bytes += len;
	ewma_rate_add(&mdata->uapsd_nonagg_detect.rate, thr);
पूर्ण

अटल व्योम iwl_mvm_rx_csum(काष्ठा ieee80211_sta *sta,
			    काष्ठा sk_buff *skb,
			    u32 status)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(mvmsta->vअगर);

	अगर (mvmvअगर->features & NETIF_F_RXCSUM &&
	    status & RX_MPDU_RES_STATUS_CSUM_DONE &&
	    status & RX_MPDU_RES_STATUS_CSUM_OK)
		skb->ip_summed = CHECKSUM_UNNECESSARY;
पूर्ण

/*
 * iwl_mvm_rx_rx_mpdu - REPLY_RX_MPDU_CMD handler
 *
 * Handles the actual data of the Rx packet from the fw
 */
व्योम iwl_mvm_rx_rx_mpdu(काष्ठा iwl_mvm *mvm, काष्ठा napi_काष्ठा *napi,
			काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ieee80211_rx_status *rx_status;
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_rx_phy_info *phy_info;
	काष्ठा iwl_rx_mpdu_res_start *rx_res;
	काष्ठा ieee80211_sta *sta = शून्य;
	काष्ठा sk_buff *skb;
	u32 len, pkt_len = iwl_rx_packet_payload_len(pkt);
	u32 rate_n_flags;
	u32 rx_pkt_status;
	u8 crypt_len = 0;

	अगर (unlikely(pkt_len < माप(*rx_res))) अणु
		IWL_DEBUG_DROP(mvm, "Bad REPLY_RX_MPDU_CMD size\n");
		वापस;
	पूर्ण

	phy_info = &mvm->last_phy_info;
	rx_res = (काष्ठा iwl_rx_mpdu_res_start *)pkt->data;
	hdr = (काष्ठा ieee80211_hdr *)(pkt->data + माप(*rx_res));
	len = le16_to_cpu(rx_res->byte_count);

	अगर (unlikely(len + माप(*rx_res) + माप(__le32) > pkt_len)) अणु
		IWL_DEBUG_DROP(mvm, "FW lied about packet len\n");
		वापस;
	पूर्ण

	rx_pkt_status = get_unaligned_le32((__le32 *)
		(pkt->data + माप(*rx_res) + len));

	/* Dont use dev_alloc_skb(), we'll have enough headroom once
	 * ieee80211_hdr pulled.
	 */
	skb = alloc_skb(128, GFP_ATOMIC);
	अगर (!skb) अणु
		IWL_ERR(mvm, "alloc_skb failed\n");
		वापस;
	पूर्ण

	rx_status = IEEE80211_SKB_RXCB(skb);

	/*
	 * drop the packet अगर it has failed being decrypted by HW
	 */
	अगर (iwl_mvm_set_mac80211_rx_flag(mvm, hdr, rx_status, rx_pkt_status,
					 &crypt_len)) अणु
		IWL_DEBUG_DROP(mvm, "Bad decryption results 0x%08x\n",
			       rx_pkt_status);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	/*
	 * Keep packets with CRC errors (and with overrun) क्रम monitor mode
	 * (otherwise the firmware discards them) but mark them as bad.
	 */
	अगर (!(rx_pkt_status & RX_MPDU_RES_STATUS_CRC_OK) ||
	    !(rx_pkt_status & RX_MPDU_RES_STATUS_OVERRUN_OK)) अणु
		IWL_DEBUG_RX(mvm, "Bad CRC or FIFO: 0x%08X.\n", rx_pkt_status);
		rx_status->flag |= RX_FLAG_FAILED_FCS_CRC;
	पूर्ण

	/* This will be used in several places later */
	rate_n_flags = le32_to_cpu(phy_info->rate_n_flags);

	/* rx_status carries inक्रमmation about the packet to mac80211 */
	rx_status->maस_समय = le64_to_cpu(phy_info->बारtamp);
	rx_status->device_बारtamp = le32_to_cpu(phy_info->प्रणाली_बारtamp);
	rx_status->band =
		(phy_info->phy_flags & cpu_to_le16(RX_RES_PHY_FLAGS_BAND_24)) ?
				NL80211_BAND_2GHZ : NL80211_BAND_5GHZ;
	rx_status->freq =
		ieee80211_channel_to_frequency(le16_to_cpu(phy_info->channel),
					       rx_status->band);

	/* TSF as indicated by the firmware  is at INA समय */
	rx_status->flag |= RX_FLAG_MACTIME_PLCP_START;

	iwl_mvm_get_संकेत_strength(mvm, phy_info, rx_status);

	IWL_DEBUG_STATS_LIMIT(mvm, "Rssi %d, TSF %llu\n", rx_status->संकेत,
			      (अचिन्हित दीर्घ दीर्घ)rx_status->maस_समय);

	rcu_पढ़ो_lock();
	अगर (rx_pkt_status & RX_MPDU_RES_STATUS_SRC_STA_FOUND) अणु
		u32 id = rx_pkt_status & RX_MPDU_RES_STATUS_STA_ID_MSK;

		id >>= RX_MDPU_RES_STATUS_STA_ID_SHIFT;

		अगर (!WARN_ON_ONCE(id >= mvm->fw->ucode_capa.num_stations)) अणु
			sta = rcu_dereference(mvm->fw_id_to_mac_id[id]);
			अगर (IS_ERR(sta))
				sta = शून्य;
		पूर्ण
	पूर्ण अन्यथा अगर (!is_multicast_ether_addr(hdr->addr2)) अणु
		/* This is fine since we prevent two stations with the same
		 * address from being added.
		 */
		sta = ieee80211_find_sta_by_अगरaddr(mvm->hw, hdr->addr2, शून्य);
	पूर्ण

	अगर (sta) अणु
		काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
		काष्ठा ieee80211_vअगर *tx_blocked_vअगर =
			rcu_dereference(mvm->csa_tx_blocked_vअगर);
		काष्ठा iwl_fw_dbg_trigger_tlv *trig;
		काष्ठा ieee80211_vअगर *vअगर = mvmsta->vअगर;

		/* We have tx blocked stations (with CS bit). If we heard
		 * frames from a blocked station on a new channel we can
		 * TX to it again.
		 */
		अगर (unlikely(tx_blocked_vअगर) && vअगर == tx_blocked_vअगर) अणु
			काष्ठा iwl_mvm_vअगर *mvmvअगर =
				iwl_mvm_vअगर_from_mac80211(tx_blocked_vअगर);

			अगर (mvmvअगर->csa_target_freq == rx_status->freq)
				iwl_mvm_sta_modअगरy_disable_tx_ap(mvm, sta,
								 false);
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

		अगर (!mvm->tcm.छोड़ोd && len >= माप(*hdr) &&
		    !is_multicast_ether_addr(hdr->addr1) &&
		    ieee80211_is_data(hdr->frame_control))
			iwl_mvm_rx_handle_tcm(mvm, sta, hdr, len, phy_info,
					      rate_n_flags);

		अगर (ieee80211_is_data(hdr->frame_control))
			iwl_mvm_rx_csum(sta, skb, rx_pkt_status);
	पूर्ण
	rcu_पढ़ो_unlock();

	/* set the preamble flag अगर appropriate */
	अगर (phy_info->phy_flags & cpu_to_le16(RX_RES_PHY_FLAGS_SHORT_PREAMBLE))
		rx_status->enc_flags |= RX_ENC_FLAG_SHORTPRE;

	अगर (phy_info->phy_flags & cpu_to_le16(RX_RES_PHY_FLAGS_AGG)) अणु
		/*
		 * We know which subframes of an A-MPDU beदीर्घ
		 * together since we get a single PHY response
		 * from the firmware क्रम all of them
		 */
		rx_status->flag |= RX_FLAG_AMPDU_DETAILS;
		rx_status->ampdu_reference = mvm->ampdu_ref;
	पूर्ण

	/* Set up the HT phy flags */
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
	पूर्ण अन्यथा अणु
		पूर्णांक rate = iwl_mvm_legacy_rate_to_mac80211_idx(rate_n_flags,
							       rx_status->band);

		अगर (WARN(rate < 0 || rate > 0xFF,
			 "Invalid rate flags 0x%x, band %d,\n",
			 rate_n_flags, rx_status->band)) अणु
			kमुक्त_skb(skb);
			वापस;
		पूर्ण
		rx_status->rate_idx = rate;
	पूर्ण

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	iwl_mvm_update_frame_stats(mvm, rate_n_flags,
				   rx_status->flag & RX_FLAG_AMPDU_DETAILS);
#पूर्ण_अगर

	अगर (unlikely((ieee80211_is_beacon(hdr->frame_control) ||
		      ieee80211_is_probe_resp(hdr->frame_control)) &&
		     mvm->sched_scan_pass_all == SCHED_SCAN_PASS_ALL_ENABLED))
		mvm->sched_scan_pass_all = SCHED_SCAN_PASS_ALL_FOUND;

	अगर (unlikely(ieee80211_is_beacon(hdr->frame_control) ||
		     ieee80211_is_probe_resp(hdr->frame_control)))
		rx_status->bootसमय_ns = kसमय_get_bootसमय_ns();

	iwl_mvm_pass_packet_to_mac80211(mvm, sta, napi, skb, hdr, len,
					crypt_len, rxb);
पूर्ण

काष्ठा iwl_mvm_stat_data अणु
	काष्ठा iwl_mvm *mvm;
	__le32 flags;
	__le32 mac_id;
	u8 beacon_filter_average_energy;
	__le32 *beacon_counter;
	u8 *beacon_average_energy;
पूर्ण;

अटल व्योम iwl_mvm_stat_iterator(व्योम *_data, u8 *mac,
				  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_mvm_stat_data *data = _data;
	काष्ठा iwl_mvm *mvm = data->mvm;
	पूर्णांक sig = -data->beacon_filter_average_energy;
	पूर्णांक last_event;
	पूर्णांक thold = vअगर->bss_conf.cqm_rssi_thold;
	पूर्णांक hyst = vअगर->bss_conf.cqm_rssi_hyst;
	u16 id = le32_to_cpu(data->mac_id);
	काष्ठा iwl_mvm_vअगर *mvmvअगर = iwl_mvm_vअगर_from_mac80211(vअगर);
	u16 vअगर_id = mvmvअगर->id;

	/* This करोesn't need the MAC ID check since it's not taking the
	 * data copied पूर्णांकo the "data" काष्ठा, but rather the data from
	 * the notअगरication directly.
	 */
	mvmvअगर->beacon_stats.num_beacons =
		le32_to_cpu(data->beacon_counter[vअगर_id]);
	mvmvअगर->beacon_stats.avg_संकेत =
		-data->beacon_average_energy[vअगर_id];

	/* make sure that beacon statistics करोn't go backwards with TCM
	 * request to clear statistics
	 */
	अगर (le32_to_cpu(data->flags) & IWL_STATISTICS_REPLY_FLG_CLEAR)
		mvmvअगर->beacon_stats.accu_num_beacons +=
			mvmvअगर->beacon_stats.num_beacons;

	अगर (mvmvअगर->id != id)
		वापस;

	अगर (vअगर->type != NL80211_IFTYPE_STATION)
		वापस;

	अगर (sig == 0) अणु
		IWL_DEBUG_RX(mvm, "RSSI is 0 - skip signal based decision\n");
		वापस;
	पूर्ण

	mvmvअगर->bf_data.ave_beacon_संकेत = sig;

	/* BT Coex */
	अगर (mvmvअगर->bf_data.bt_coex_min_thold !=
	    mvmvअगर->bf_data.bt_coex_max_thold) अणु
		last_event = mvmvअगर->bf_data.last_bt_coex_event;
		अगर (sig > mvmvअगर->bf_data.bt_coex_max_thold &&
		    (last_event <= mvmvअगर->bf_data.bt_coex_min_thold ||
		     last_event == 0)) अणु
			mvmvअगर->bf_data.last_bt_coex_event = sig;
			IWL_DEBUG_RX(mvm, "cqm_iterator bt coex high %d\n",
				     sig);
			iwl_mvm_bt_rssi_event(mvm, vअगर, RSSI_EVENT_HIGH);
		पूर्ण अन्यथा अगर (sig < mvmvअगर->bf_data.bt_coex_min_thold &&
			   (last_event >= mvmvअगर->bf_data.bt_coex_max_thold ||
			    last_event == 0)) अणु
			mvmvअगर->bf_data.last_bt_coex_event = sig;
			IWL_DEBUG_RX(mvm, "cqm_iterator bt coex low %d\n",
				     sig);
			iwl_mvm_bt_rssi_event(mvm, vअगर, RSSI_EVENT_LOW);
		पूर्ण
	पूर्ण

	अगर (!(vअगर->driver_flags & IEEE80211_VIF_SUPPORTS_CQM_RSSI))
		वापस;

	/* CQM Notअगरication */
	last_event = mvmvअगर->bf_data.last_cqm_event;
	अगर (thold && sig < thold && (last_event == 0 ||
				     sig < last_event - hyst)) अणु
		mvmvअगर->bf_data.last_cqm_event = sig;
		IWL_DEBUG_RX(mvm, "cqm_iterator cqm low %d\n",
			     sig);
		ieee80211_cqm_rssi_notअगरy(
			vअगर,
			NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW,
			sig,
			GFP_KERNEL);
	पूर्ण अन्यथा अगर (sig > thold &&
		   (last_event == 0 || sig > last_event + hyst)) अणु
		mvmvअगर->bf_data.last_cqm_event = sig;
		IWL_DEBUG_RX(mvm, "cqm_iterator cqm high %d\n",
			     sig);
		ieee80211_cqm_rssi_notअगरy(
			vअगर,
			NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH,
			sig,
			GFP_KERNEL);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
iwl_mvm_rx_stats_check_trigger(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_packet *pkt)
अणु
	काष्ठा iwl_fw_dbg_trigger_tlv *trig;
	काष्ठा iwl_fw_dbg_trigger_stats *trig_stats;
	u32 trig_offset, trig_thold;

	trig = iwl_fw_dbg_trigger_on(&mvm->fwrt, शून्य, FW_DBG_TRIGGER_STATS);
	अगर (!trig)
		वापस;

	trig_stats = (व्योम *)trig->data;

	trig_offset = le32_to_cpu(trig_stats->stop_offset);
	trig_thold = le32_to_cpu(trig_stats->stop_threshold);

	अगर (WARN_ON_ONCE(trig_offset >= iwl_rx_packet_payload_len(pkt)))
		वापस;

	अगर (le32_to_cpup((__le32 *) (pkt->data + trig_offset)) < trig_thold)
		वापस;

	iwl_fw_dbg_collect_trig(&mvm->fwrt, trig, शून्य);
पूर्ण

अटल व्योम iwl_mvm_stats_energy_iter(व्योम *_data,
				      काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	u8 *energy = _data;
	u32 sta_id = mvmsta->sta_id;

	अगर (WARN_ONCE(sta_id >= IWL_MVM_STATION_COUNT_MAX, "sta_id %d >= %d",
		      sta_id, IWL_MVM_STATION_COUNT_MAX))
		वापस;

	अगर (energy[sta_id])
		mvmsta->avg_energy = energy[sta_id];

पूर्ण

अटल व्योम
iwl_mvm_update_tcm_from_stats(काष्ठा iwl_mvm *mvm, __le32 *air_समय_le,
			      __le32 *rx_bytes_le)
अणु
	पूर्णांक i;

	spin_lock(&mvm->tcm.lock);
	क्रम (i = 0; i < NUM_MAC_INDEX_DRIVER; i++) अणु
		काष्ठा iwl_mvm_tcm_mac *mdata = &mvm->tcm.data[i];
		u32 rx_bytes = le32_to_cpu(rx_bytes_le[i]);
		u32 airसमय = le32_to_cpu(air_समय_le[i]);

		mdata->rx.airसमय += airसमय;
		mdata->uapsd_nonagg_detect.rx_bytes += rx_bytes;
		अगर (airसमय) अणु
			/* re-init every समय to store rate from FW */
			ewma_rate_init(&mdata->uapsd_nonagg_detect.rate);
			ewma_rate_add(&mdata->uapsd_nonagg_detect.rate,
				      rx_bytes * 8 / airसमय);
		पूर्ण
	पूर्ण
	spin_unlock(&mvm->tcm.lock);
पूर्ण

अटल व्योम
iwl_mvm_handle_rx_statistics_tlv(काष्ठा iwl_mvm *mvm,
				 काष्ठा iwl_rx_packet *pkt)
अणु
	काष्ठा iwl_mvm_stat_data data = अणु
		.mvm = mvm,
	पूर्ण;
	u8 beacon_average_energy[MAC_INDEX_AUX];
	u8 average_energy[IWL_MVM_STATION_COUNT_MAX];
	काष्ठा iwl_statistics_operational_ntfy *stats;
	पूर्णांक expected_size;
	__le32 flags;
	पूर्णांक i;

	expected_size = माप(*stats);
	अगर (WARN_ONCE(iwl_rx_packet_payload_len(pkt) < expected_size,
		      "received invalid statistics size (%d)!, expected_size: %d\n",
		      iwl_rx_packet_payload_len(pkt), expected_size))
		वापस;

	stats = (व्योम *)&pkt->data;

	अगर (WARN_ONCE(stats->hdr.type != FW_STATISTICS_OPERATIONAL ||
		      stats->hdr.version !=
		      iwl_fw_lookup_notअगर_ver(mvm->fw, LONG_GROUP, STATISTICS_CMD, 0),
		      "received unsupported hdr type %d, version %d\n",
		      stats->hdr.type, stats->hdr.version))
		वापस;

	flags = stats->flags;
	mvm->radio_stats.rx_समय = le64_to_cpu(stats->rx_समय);
	mvm->radio_stats.tx_समय = le64_to_cpu(stats->tx_समय);
	mvm->radio_stats.on_समय_rf = le64_to_cpu(stats->on_समय_rf);
	mvm->radio_stats.on_समय_scan = le64_to_cpu(stats->on_समय_scan);

	iwl_mvm_rx_stats_check_trigger(mvm, pkt);

	data.mac_id = stats->mac_id;
	data.beacon_filter_average_energy =
		le32_to_cpu(stats->beacon_filter_average_energy);
	data.flags = flags;
	data.beacon_counter = stats->beacon_counter;
	क्रम (i = 0; i < ARRAY_SIZE(beacon_average_energy); i++)
		beacon_average_energy[i] =
			le32_to_cpu(stats->beacon_average_energy[i]);

	data.beacon_average_energy = beacon_average_energy;

	ieee80211_iterate_active_पूर्णांकerfaces(mvm->hw,
					    IEEE80211_IFACE_ITER_NORMAL,
					    iwl_mvm_stat_iterator,
					    &data);

	क्रम (i = 0; i < ARRAY_SIZE(average_energy); i++)
		average_energy[i] = le32_to_cpu(stats->average_energy[i]);
	ieee80211_iterate_stations_atomic(mvm->hw, iwl_mvm_stats_energy_iter,
					  average_energy);
	/*
	 * Don't update in हाल the statistics are not cleared, since
	 * we will end up counting twice the same airसमय, once in TCM
	 * request and once in statistics notअगरication.
	 */
	अगर (le32_to_cpu(flags) & IWL_STATISTICS_REPLY_FLG_CLEAR)
		iwl_mvm_update_tcm_from_stats(mvm, stats->air_समय,
					      stats->rx_bytes);
पूर्ण

व्योम iwl_mvm_handle_rx_statistics(काष्ठा iwl_mvm *mvm,
				  काष्ठा iwl_rx_packet *pkt)
अणु
	काष्ठा iwl_mvm_stat_data data = अणु
		.mvm = mvm,
	पूर्ण;
	__le32 *bytes, *air_समय, flags;
	पूर्णांक expected_size;
	u8 *energy;

	/* From ver 14 and up we use TLV statistics क्रमmat */
	अगर (iwl_fw_lookup_notअगर_ver(mvm->fw, LONG_GROUP,
				    STATISTICS_CMD, 0) >= 14)
		वापस iwl_mvm_handle_rx_statistics_tlv(mvm, pkt);

	अगर (!iwl_mvm_has_new_rx_stats_api(mvm)) अणु
		अगर (iwl_mvm_has_new_rx_api(mvm))
			expected_size = माप(काष्ठा iwl_notअगर_statistics_v11);
		अन्यथा
			expected_size = माप(काष्ठा iwl_notअगर_statistics_v10);
	पूर्ण अन्यथा अणु
		expected_size = माप(काष्ठा iwl_notअगर_statistics);
	पूर्ण

	अगर (WARN_ONCE(iwl_rx_packet_payload_len(pkt) != expected_size,
		      "received invalid statistics size (%d)!\n",
		      iwl_rx_packet_payload_len(pkt)))
		वापस;

	अगर (!iwl_mvm_has_new_rx_stats_api(mvm)) अणु
		काष्ठा iwl_notअगर_statistics_v11 *stats = (व्योम *)&pkt->data;

		data.mac_id = stats->rx.general.mac_id;
		data.beacon_filter_average_energy =
			stats->general.common.beacon_filter_average_energy;

		mvm->rx_stats_v3 = stats->rx;

		mvm->radio_stats.rx_समय =
			le64_to_cpu(stats->general.common.rx_समय);
		mvm->radio_stats.tx_समय =
			le64_to_cpu(stats->general.common.tx_समय);
		mvm->radio_stats.on_समय_rf =
			le64_to_cpu(stats->general.common.on_समय_rf);
		mvm->radio_stats.on_समय_scan =
			le64_to_cpu(stats->general.common.on_समय_scan);

		data.beacon_counter = stats->general.beacon_counter;
		data.beacon_average_energy =
			stats->general.beacon_average_energy;
		flags = stats->flag;
	पूर्ण अन्यथा अणु
		काष्ठा iwl_notअगर_statistics *stats = (व्योम *)&pkt->data;

		data.mac_id = stats->rx.general.mac_id;
		data.beacon_filter_average_energy =
			stats->general.common.beacon_filter_average_energy;

		mvm->rx_stats = stats->rx;

		mvm->radio_stats.rx_समय =
			le64_to_cpu(stats->general.common.rx_समय);
		mvm->radio_stats.tx_समय =
			le64_to_cpu(stats->general.common.tx_समय);
		mvm->radio_stats.on_समय_rf =
			le64_to_cpu(stats->general.common.on_समय_rf);
		mvm->radio_stats.on_समय_scan =
			le64_to_cpu(stats->general.common.on_समय_scan);

		data.beacon_counter = stats->general.beacon_counter;
		data.beacon_average_energy =
			stats->general.beacon_average_energy;
		flags = stats->flag;
	पूर्ण
	data.flags = flags;

	iwl_mvm_rx_stats_check_trigger(mvm, pkt);

	ieee80211_iterate_active_पूर्णांकerfaces(mvm->hw,
					    IEEE80211_IFACE_ITER_NORMAL,
					    iwl_mvm_stat_iterator,
					    &data);

	अगर (!iwl_mvm_has_new_rx_api(mvm))
		वापस;

	अगर (!iwl_mvm_has_new_rx_stats_api(mvm)) अणु
		काष्ठा iwl_notअगर_statistics_v11 *v11 = (व्योम *)&pkt->data;

		energy = (व्योम *)&v11->load_stats.avg_energy;
		bytes = (व्योम *)&v11->load_stats.byte_count;
		air_समय = (व्योम *)&v11->load_stats.air_समय;
	पूर्ण अन्यथा अणु
		काष्ठा iwl_notअगर_statistics *stats = (व्योम *)&pkt->data;

		energy = (व्योम *)&stats->load_stats.avg_energy;
		bytes = (व्योम *)&stats->load_stats.byte_count;
		air_समय = (व्योम *)&stats->load_stats.air_समय;
	पूर्ण
	ieee80211_iterate_stations_atomic(mvm->hw, iwl_mvm_stats_energy_iter,
					  energy);

	/*
	 * Don't update in हाल the statistics are not cleared, since
	 * we will end up counting twice the same airसमय, once in TCM
	 * request and once in statistics notअगरication.
	 */
	अगर (le32_to_cpu(flags) & IWL_STATISTICS_REPLY_FLG_CLEAR)
		iwl_mvm_update_tcm_from_stats(mvm, air_समय, bytes);

पूर्ण

व्योम iwl_mvm_rx_statistics(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	iwl_mvm_handle_rx_statistics(mvm, rxb_addr(rxb));
पूर्ण

व्योम iwl_mvm_winकरोw_status_notअगर(काष्ठा iwl_mvm *mvm,
				 काष्ठा iwl_rx_cmd_buffer *rxb)
अणु
	काष्ठा iwl_rx_packet *pkt = rxb_addr(rxb);
	काष्ठा iwl_ba_winकरोw_status_notअगर *notअगर = (व्योम *)pkt->data;
	पूर्णांक i;

	BUILD_BUG_ON(ARRAY_SIZE(notअगर->ra_tid) != BA_WINDOW_STREAMS_MAX);
	BUILD_BUG_ON(ARRAY_SIZE(notअगर->mpdu_rx_count) != BA_WINDOW_STREAMS_MAX);
	BUILD_BUG_ON(ARRAY_SIZE(notअगर->biपंचांगap) != BA_WINDOW_STREAMS_MAX);
	BUILD_BUG_ON(ARRAY_SIZE(notअगर->start_seq_num) != BA_WINDOW_STREAMS_MAX);

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < BA_WINDOW_STREAMS_MAX; i++) अणु
		काष्ठा ieee80211_sta *sta;
		u8 sta_id, tid;
		u64 biपंचांगap;
		u32 ssn;
		u16 ratid;
		u16 received_mpdu;

		ratid = le16_to_cpu(notअगर->ra_tid[i]);
		/* check that this TID is valid */
		अगर (!(ratid & BA_WINDOW_STATUS_VALID_MSK))
			जारी;

		received_mpdu = le16_to_cpu(notअगर->mpdu_rx_count[i]);
		अगर (received_mpdu == 0)
			जारी;

		tid = ratid & BA_WINDOW_STATUS_TID_MSK;
		/* get the station */
		sta_id = (ratid & BA_WINDOW_STATUS_STA_ID_MSK)
			 >> BA_WINDOW_STATUS_STA_ID_POS;
		sta = rcu_dereference(mvm->fw_id_to_mac_id[sta_id]);
		अगर (IS_ERR_OR_शून्य(sta))
			जारी;
		biपंचांगap = le64_to_cpu(notअगर->biपंचांगap[i]);
		ssn = le32_to_cpu(notअगर->start_seq_num[i]);

		/* update mac80211 with the biपंचांगap क्रम the reordering buffer */
		ieee80211_mark_rx_ba_filtered_frames(sta, tid, ssn, biपंचांगap,
						     received_mpdu);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण
