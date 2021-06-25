<शैली गुरु>
/*
 * NXP Wireless LAN device driver: TDLS handling
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available on the worldwide web at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#समावेश "main.h"
#समावेश "wmm.h"
#समावेश "11n.h"
#समावेश "11n_rxreorder.h"
#समावेश "11ac.h"

#घोषणा TDLS_REQ_FIX_LEN      6
#घोषणा TDLS_RESP_FIX_LEN     8
#घोषणा TDLS_CONFIRM_FIX_LEN  6
#घोषणा MWIFIEX_TDLS_WMM_INFO_SIZE 7

अटल व्योम mwअगरiex_restore_tdls_packets(काष्ठा mwअगरiex_निजी *priv,
					 स्थिर u8 *mac, u8 status)
अणु
	काष्ठा mwअगरiex_ra_list_tbl *ra_list;
	काष्ठा list_head *tid_list;
	काष्ठा sk_buff *skb, *पंचांगp;
	काष्ठा mwअगरiex_txinfo *tx_info;
	u32 tid;
	u8 tid_करोwn;

	mwअगरiex_dbg(priv->adapter, DATA, "%s: %pM\n", __func__, mac);
	spin_lock_bh(&priv->wmm.ra_list_spinlock);

	skb_queue_walk_safe(&priv->tdls_txq, skb, पंचांगp) अणु
		अगर (!ether_addr_equal(mac, skb->data))
			जारी;

		__skb_unlink(skb, &priv->tdls_txq);
		tx_info = MWIFIEX_SKB_TXCB(skb);
		tid = skb->priority;
		tid_करोwn = mwअगरiex_wmm_करोwngrade_tid(priv, tid);

		अगर (mwअगरiex_is_tdls_link_setup(status)) अणु
			ra_list = mwअगरiex_wmm_get_queue_raptr(priv, tid, mac);
			ra_list->tdls_link = true;
			tx_info->flags |= MWIFIEX_BUF_FLAG_TDLS_PKT;
		पूर्ण अन्यथा अणु
			tid_list = &priv->wmm.tid_tbl_ptr[tid_करोwn].ra_list;
			ra_list = list_first_entry_or_null(tid_list,
					काष्ठा mwअगरiex_ra_list_tbl, list);
			tx_info->flags &= ~MWIFIEX_BUF_FLAG_TDLS_PKT;
		पूर्ण

		अगर (!ra_list) अणु
			mwअगरiex_ग_लिखो_data_complete(priv->adapter, skb, 0, -1);
			जारी;
		पूर्ण

		skb_queue_tail(&ra_list->skb_head, skb);

		ra_list->ba_pkt_count++;
		ra_list->total_pkt_count++;

		अगर (atomic_पढ़ो(&priv->wmm.highest_queued_prio) <
						       tos_to_tid_inv[tid_करोwn])
			atomic_set(&priv->wmm.highest_queued_prio,
				   tos_to_tid_inv[tid_करोwn]);

		atomic_inc(&priv->wmm.tx_pkts_queued);
	पूर्ण

	spin_unlock_bh(&priv->wmm.ra_list_spinlock);
	वापस;
पूर्ण

अटल व्योम mwअगरiex_hold_tdls_packets(काष्ठा mwअगरiex_निजी *priv,
				      स्थिर u8 *mac)
अणु
	काष्ठा mwअगरiex_ra_list_tbl *ra_list;
	काष्ठा list_head *ra_list_head;
	काष्ठा sk_buff *skb, *पंचांगp;
	पूर्णांक i;

	mwअगरiex_dbg(priv->adapter, DATA, "%s: %pM\n", __func__, mac);
	spin_lock_bh(&priv->wmm.ra_list_spinlock);

	क्रम (i = 0; i < MAX_NUM_TID; i++) अणु
		अगर (!list_empty(&priv->wmm.tid_tbl_ptr[i].ra_list)) अणु
			ra_list_head = &priv->wmm.tid_tbl_ptr[i].ra_list;
			list_क्रम_each_entry(ra_list, ra_list_head, list) अणु
				skb_queue_walk_safe(&ra_list->skb_head, skb,
						    पंचांगp) अणु
					अगर (!ether_addr_equal(mac, skb->data))
						जारी;
					__skb_unlink(skb, &ra_list->skb_head);
					atomic_dec(&priv->wmm.tx_pkts_queued);
					ra_list->total_pkt_count--;
					skb_queue_tail(&priv->tdls_txq, skb);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_bh(&priv->wmm.ra_list_spinlock);
	वापस;
पूर्ण

/* This function appends rate TLV to scan config command. */
अटल पूर्णांक
mwअगरiex_tdls_append_rates_ie(काष्ठा mwअगरiex_निजी *priv,
			     काष्ठा sk_buff *skb)
अणु
	u8 rates[MWIFIEX_SUPPORTED_RATES], *pos;
	u16 rates_size, supp_rates_size, ext_rates_size;

	स_रखो(rates, 0, माप(rates));
	rates_size = mwअगरiex_get_supported_rates(priv, rates);

	supp_rates_size = min_t(u16, rates_size, MWIFIEX_TDLS_SUPPORTED_RATES);

	अगर (skb_tailroom(skb) < rates_size + 4) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Insufficient space while adding rates\n");
		वापस -ENOMEM;
	पूर्ण

	pos = skb_put(skb, supp_rates_size + 2);
	*pos++ = WLAN_EID_SUPP_RATES;
	*pos++ = supp_rates_size;
	स_नकल(pos, rates, supp_rates_size);

	अगर (rates_size > MWIFIEX_TDLS_SUPPORTED_RATES) अणु
		ext_rates_size = rates_size - MWIFIEX_TDLS_SUPPORTED_RATES;
		pos = skb_put(skb, ext_rates_size + 2);
		*pos++ = WLAN_EID_EXT_SUPP_RATES;
		*pos++ = ext_rates_size;
		स_नकल(pos, rates + MWIFIEX_TDLS_SUPPORTED_RATES,
		       ext_rates_size);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mwअगरiex_tdls_add_aid(काष्ठा mwअगरiex_निजी *priv,
				काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee_types_assoc_rsp *assoc_rsp;
	u8 *pos;

	assoc_rsp = (काष्ठा ieee_types_assoc_rsp *)&priv->assoc_rsp_buf;
	pos = skb_put(skb, 4);
	*pos++ = WLAN_EID_AID;
	*pos++ = 2;
	स_नकल(pos, &assoc_rsp->a_id, माप(assoc_rsp->a_id));

	वापस;
पूर्ण

अटल पूर्णांक mwअगरiex_tdls_add_vht_capab(काष्ठा mwअगरiex_निजी *priv,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_vht_cap vht_cap;
	u8 *pos;

	pos = skb_put(skb, माप(काष्ठा ieee80211_vht_cap) + 2);
	*pos++ = WLAN_EID_VHT_CAPABILITY;
	*pos++ = माप(काष्ठा ieee80211_vht_cap);

	स_रखो(&vht_cap, 0, माप(काष्ठा ieee80211_vht_cap));

	mwअगरiex_fill_vht_cap_tlv(priv, &vht_cap, priv->curr_bss_params.band);
	स_नकल(pos, &vht_cap, माप(vht_cap));

	वापस 0;
पूर्ण

अटल पूर्णांक
mwअगरiex_tdls_add_ht_oper(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *mac,
			 u8 vht_enabled, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_ht_operation *ht_oper;
	काष्ठा mwअगरiex_sta_node *sta_ptr;
	काष्ठा mwअगरiex_bssdescriptor *bss_desc =
					&priv->curr_bss_params.bss_descriptor;
	u8 *pos;

	sta_ptr = mwअगरiex_get_sta_entry(priv, mac);
	अगर (unlikely(!sta_ptr)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "TDLS peer station not found in list\n");
		वापस -1;
	पूर्ण

	अगर (!(le16_to_cpu(sta_ptr->tdls_cap.ht_capb.cap_info))) अणु
		mwअगरiex_dbg(priv->adapter, WARN,
			    "TDLS peer doesn't support ht capabilities\n");
		वापस 0;
	पूर्ण

	pos = skb_put(skb, माप(काष्ठा ieee80211_ht_operation) + 2);
	*pos++ = WLAN_EID_HT_OPERATION;
	*pos++ = माप(काष्ठा ieee80211_ht_operation);
	ht_oper = (व्योम *)pos;

	ht_oper->primary_chan = bss_desc->channel;

	/* follow AP's channel bandwidth */
	अगर (ISSUPP_CHANWIDTH40(priv->adapter->hw_करोt_11n_dev_cap) &&
	    bss_desc->bcn_ht_cap &&
	    ISALLOWED_CHANWIDTH40(bss_desc->bcn_ht_oper->ht_param))
		ht_oper->ht_param = bss_desc->bcn_ht_oper->ht_param;

	अगर (vht_enabled) अणु
		ht_oper->ht_param =
			  mwअगरiex_get_sec_chan_offset(bss_desc->channel);
		ht_oper->ht_param |= BIT(2);
	पूर्ण

	स_नकल(&sta_ptr->tdls_cap.ht_oper, ht_oper,
	       माप(काष्ठा ieee80211_ht_operation));

	वापस 0;
पूर्ण

अटल पूर्णांक mwअगरiex_tdls_add_vht_oper(काष्ठा mwअगरiex_निजी *priv,
				     स्थिर u8 *mac, काष्ठा sk_buff *skb)
अणु
	काष्ठा mwअगरiex_bssdescriptor *bss_desc;
	काष्ठा ieee80211_vht_operation *vht_oper;
	काष्ठा ieee80211_vht_cap *vht_cap, *ap_vht_cap = शून्य;
	काष्ठा mwअगरiex_sta_node *sta_ptr;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	u8 supp_chwd_set, peer_supp_chwd_set;
	u8 *pos, ap_supp_chwd_set, chan_bw;
	u16 mcs_map_user, mcs_map_resp, mcs_map_result;
	u16 mcs_user, mcs_resp, nss;
	u32 usr_vht_cap_info;

	bss_desc = &priv->curr_bss_params.bss_descriptor;

	sta_ptr = mwअगरiex_get_sta_entry(priv, mac);
	अगर (unlikely(!sta_ptr)) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "TDLS peer station not found in list\n");
		वापस -1;
	पूर्ण

	अगर (!(le32_to_cpu(sta_ptr->tdls_cap.vhtcap.vht_cap_info))) अणु
		mwअगरiex_dbg(adapter, WARN,
			    "TDLS peer doesn't support vht capabilities\n");
		वापस 0;
	पूर्ण

	अगर (!mwअगरiex_is_bss_in_11ac_mode(priv)) अणु
		अगर (sta_ptr->tdls_cap.extcap.ext_capab[7] &
		   WLAN_EXT_CAPA8_TDLS_WIDE_BW_ENABLED) अणु
			mwअगरiex_dbg(adapter, WARN,
				    "TDLS peer doesn't support wider bandwidth\n");
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		ap_vht_cap = bss_desc->bcn_vht_cap;
	पूर्ण

	pos = skb_put(skb, माप(काष्ठा ieee80211_vht_operation) + 2);
	*pos++ = WLAN_EID_VHT_OPERATION;
	*pos++ = माप(काष्ठा ieee80211_vht_operation);
	vht_oper = (काष्ठा ieee80211_vht_operation *)pos;

	अगर (bss_desc->bss_band & BAND_A)
		usr_vht_cap_info = adapter->usr_करोt_11ac_dev_cap_a;
	अन्यथा
		usr_vht_cap_info = adapter->usr_करोt_11ac_dev_cap_bg;

	/* find the minimum bandwidth between AP/TDLS peers */
	vht_cap = &sta_ptr->tdls_cap.vhtcap;
	supp_chwd_set = GET_VHTCAP_CHWDSET(usr_vht_cap_info);
	peer_supp_chwd_set =
			 GET_VHTCAP_CHWDSET(le32_to_cpu(vht_cap->vht_cap_info));
	supp_chwd_set = min_t(u8, supp_chwd_set, peer_supp_chwd_set);

	/* We need check AP's bandwidth when TDLS_WIDER_BANDWIDTH is off */

	अगर (ap_vht_cap && sta_ptr->tdls_cap.extcap.ext_capab[7] &
	    WLAN_EXT_CAPA8_TDLS_WIDE_BW_ENABLED) अणु
		ap_supp_chwd_set =
		      GET_VHTCAP_CHWDSET(le32_to_cpu(ap_vht_cap->vht_cap_info));
		supp_chwd_set = min_t(u8, supp_chwd_set, ap_supp_chwd_set);
	पूर्ण

	चयन (supp_chwd_set) अणु
	हाल IEEE80211_VHT_CHANWIDTH_80MHZ:
		vht_oper->chan_width = IEEE80211_VHT_CHANWIDTH_80MHZ;
		अवरोध;
	हाल IEEE80211_VHT_CHANWIDTH_160MHZ:
		vht_oper->chan_width = IEEE80211_VHT_CHANWIDTH_160MHZ;
		अवरोध;
	हाल IEEE80211_VHT_CHANWIDTH_80P80MHZ:
		vht_oper->chan_width = IEEE80211_VHT_CHANWIDTH_80P80MHZ;
		अवरोध;
	शेष:
		vht_oper->chan_width = IEEE80211_VHT_CHANWIDTH_USE_HT;
		अवरोध;
	पूर्ण

	mcs_map_user = GET_DEVRXMCSMAP(adapter->usr_करोt_11ac_mcs_support);
	mcs_map_resp = le16_to_cpu(vht_cap->supp_mcs.rx_mcs_map);
	mcs_map_result = 0;

	क्रम (nss = 1; nss <= 8; nss++) अणु
		mcs_user = GET_VHTNSSMCS(mcs_map_user, nss);
		mcs_resp = GET_VHTNSSMCS(mcs_map_resp, nss);

		अगर ((mcs_user == IEEE80211_VHT_MCS_NOT_SUPPORTED) ||
		    (mcs_resp == IEEE80211_VHT_MCS_NOT_SUPPORTED))
			SET_VHTNSSMCS(mcs_map_result, nss,
				      IEEE80211_VHT_MCS_NOT_SUPPORTED);
		अन्यथा
			SET_VHTNSSMCS(mcs_map_result, nss,
				      min_t(u16, mcs_user, mcs_resp));
	पूर्ण

	vht_oper->basic_mcs_set = cpu_to_le16(mcs_map_result);

	चयन (vht_oper->chan_width) अणु
	हाल IEEE80211_VHT_CHANWIDTH_80MHZ:
		chan_bw = IEEE80211_VHT_CHANWIDTH_80MHZ;
		अवरोध;
	हाल IEEE80211_VHT_CHANWIDTH_160MHZ:
		chan_bw = IEEE80211_VHT_CHANWIDTH_160MHZ;
		अवरोध;
	हाल IEEE80211_VHT_CHANWIDTH_80P80MHZ:
		chan_bw = IEEE80211_VHT_CHANWIDTH_80MHZ;
		अवरोध;
	शेष:
		chan_bw = IEEE80211_VHT_CHANWIDTH_USE_HT;
		अवरोध;
	पूर्ण
	vht_oper->center_freq_seg0_idx =
			mwअगरiex_get_center_freq_index(priv, BAND_AAC,
						      bss_desc->channel,
						      chan_bw);

	वापस 0;
पूर्ण

अटल व्योम mwअगरiex_tdls_add_ext_capab(काष्ठा mwअगरiex_निजी *priv,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee_types_extcap *extcap;

	extcap = skb_put(skb, माप(काष्ठा ieee_types_extcap));
	extcap->ieee_hdr.element_id = WLAN_EID_EXT_CAPABILITY;
	extcap->ieee_hdr.len = 8;
	स_रखो(extcap->ext_capab, 0, 8);
	extcap->ext_capab[4] |= WLAN_EXT_CAPA5_TDLS_ENABLED;
	extcap->ext_capab[3] |= WLAN_EXT_CAPA4_TDLS_CHAN_SWITCH;

	अगर (priv->adapter->is_hw_11ac_capable)
		extcap->ext_capab[7] |= WLAN_EXT_CAPA8_TDLS_WIDE_BW_ENABLED;
पूर्ण

अटल व्योम mwअगरiex_tdls_add_qos_capab(काष्ठा sk_buff *skb)
अणु
	u8 *pos = skb_put(skb, 3);

	*pos++ = WLAN_EID_QOS_CAPA;
	*pos++ = 1;
	*pos++ = MWIFIEX_TDLS_DEF_QOS_CAPAB;
पूर्ण

अटल व्योम
mwअगरiex_tdls_add_wmm_param_ie(काष्ठा mwअगरiex_निजी *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_wmm_param_ie *wmm;
	u8 ac_vi[] = अणु0x42, 0x43, 0x5e, 0x00पूर्ण;
	u8 ac_vo[] = अणु0x62, 0x32, 0x2f, 0x00पूर्ण;
	u8 ac_be[] = अणु0x03, 0xa4, 0x00, 0x00पूर्ण;
	u8 ac_bk[] = अणु0x27, 0xa4, 0x00, 0x00पूर्ण;

	wmm = skb_put_zero(skb, माप(*wmm));

	wmm->element_id = WLAN_EID_VENDOR_SPECIFIC;
	wmm->len = माप(*wmm) - 2;
	wmm->oui[0] = 0x00; /* Microsoft OUI 00:50:F2 */
	wmm->oui[1] = 0x50;
	wmm->oui[2] = 0xf2;
	wmm->oui_type = 2; /* WME */
	wmm->oui_subtype = 1; /* WME param */
	wmm->version = 1; /* WME ver */
	wmm->qos_info = 0; /* U-APSD not in use */

	/* use शेष WMM AC parameters क्रम TDLS link*/
	स_नकल(&wmm->ac[0], ac_be, माप(ac_be));
	स_नकल(&wmm->ac[1], ac_bk, माप(ac_bk));
	स_नकल(&wmm->ac[2], ac_vi, माप(ac_vi));
	स_नकल(&wmm->ac[3], ac_vo, माप(ac_vo));
पूर्ण

अटल व्योम
mwअगरiex_add_wmm_info_ie(काष्ठा mwअगरiex_निजी *priv, काष्ठा sk_buff *skb,
			u8 qosinfo)
अणु
	u8 *buf;

	buf = skb_put(skb,
		      MWIFIEX_TDLS_WMM_INFO_SIZE + माप(काष्ठा ieee_types_header));

	*buf++ = WLAN_EID_VENDOR_SPECIFIC;
	*buf++ = 7; /* len */
	*buf++ = 0x00; /* Microsoft OUI 00:50:F2 */
	*buf++ = 0x50;
	*buf++ = 0xf2;
	*buf++ = 2; /* WME */
	*buf++ = 0; /* WME info */
	*buf++ = 1; /* WME ver */
	*buf++ = qosinfo; /* U-APSD no in use */
पूर्ण

अटल व्योम mwअगरiex_tdls_add_bss_co_2040(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee_types_bss_co_2040 *bssco;

	bssco = skb_put(skb, माप(काष्ठा ieee_types_bss_co_2040));
	bssco->ieee_hdr.element_id = WLAN_EID_BSS_COEX_2040;
	bssco->ieee_hdr.len = माप(काष्ठा ieee_types_bss_co_2040) -
			      माप(काष्ठा ieee_types_header);
	bssco->bss_2040co = 0x01;
पूर्ण

अटल व्योम mwअगरiex_tdls_add_supported_chan(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee_types_generic *supp_chan;
	u8 chan_supp[] = अणु1, 11पूर्ण;

	supp_chan = skb_put(skb,
			    (माप(काष्ठा ieee_types_header) + माप(chan_supp)));
	supp_chan->ieee_hdr.element_id = WLAN_EID_SUPPORTED_CHANNELS;
	supp_chan->ieee_hdr.len = माप(chan_supp);
	स_नकल(supp_chan->data, chan_supp, माप(chan_supp));
पूर्ण

अटल व्योम mwअगरiex_tdls_add_oper_class(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee_types_generic *reg_class;
	u8 rc_list[] = अणु1,
		1, 2, 3, 4, 12, 22, 23, 24, 25, 27, 28, 29, 30, 32, 33पूर्ण;
	reg_class = skb_put(skb,
			    (माप(काष्ठा ieee_types_header) + माप(rc_list)));
	reg_class->ieee_hdr.element_id = WLAN_EID_SUPPORTED_REGULATORY_CLASSES;
	reg_class->ieee_hdr.len = माप(rc_list);
	स_नकल(reg_class->data, rc_list, माप(rc_list));
पूर्ण

अटल पूर्णांक mwअगरiex_prep_tdls_encap_data(काष्ठा mwअगरiex_निजी *priv,
					स्थिर u8 *peer, u8 action_code,
					u8 dialog_token,
					u16 status_code, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tdls_data *tf;
	पूर्णांक ret;
	u16 capab;
	काष्ठा ieee80211_ht_cap *ht_cap;
	u8 radio, *pos;

	capab = priv->curr_bss_params.bss_descriptor.cap_info_biपंचांगap;

	tf = skb_put(skb, दुरत्व(काष्ठा ieee80211_tdls_data, u));
	स_नकल(tf->da, peer, ETH_ALEN);
	स_नकल(tf->sa, priv->curr_addr, ETH_ALEN);
	tf->ether_type = cpu_to_be16(ETH_P_TDLS);
	tf->payload_type = WLAN_TDLS_SNAP_RFTYPE;

	चयन (action_code) अणु
	हाल WLAN_TDLS_SETUP_REQUEST:
		tf->category = WLAN_CATEGORY_TDLS;
		tf->action_code = WLAN_TDLS_SETUP_REQUEST;
		skb_put(skb, माप(tf->u.setup_req));
		tf->u.setup_req.dialog_token = dialog_token;
		tf->u.setup_req.capability = cpu_to_le16(capab);
		ret = mwअगरiex_tdls_append_rates_ie(priv, skb);
		अगर (ret) अणु
			dev_kमुक्त_skb_any(skb);
			वापस ret;
		पूर्ण

		pos = skb_put(skb, माप(काष्ठा ieee80211_ht_cap) + 2);
		*pos++ = WLAN_EID_HT_CAPABILITY;
		*pos++ = माप(काष्ठा ieee80211_ht_cap);
		ht_cap = (व्योम *)pos;
		radio = mwअगरiex_band_to_radio_type(priv->curr_bss_params.band);
		ret = mwअगरiex_fill_cap_info(priv, radio, ht_cap);
		अगर (ret) अणु
			dev_kमुक्त_skb_any(skb);
			वापस ret;
		पूर्ण

		अगर (priv->adapter->is_hw_11ac_capable) अणु
			ret = mwअगरiex_tdls_add_vht_capab(priv, skb);
			अगर (ret) अणु
				dev_kमुक्त_skb_any(skb);
				वापस ret;
			पूर्ण
			mwअगरiex_tdls_add_aid(priv, skb);
		पूर्ण

		mwअगरiex_tdls_add_ext_capab(priv, skb);
		mwअगरiex_tdls_add_bss_co_2040(skb);
		mwअगरiex_tdls_add_supported_chan(skb);
		mwअगरiex_tdls_add_oper_class(skb);
		mwअगरiex_add_wmm_info_ie(priv, skb, 0);
		अवरोध;

	हाल WLAN_TDLS_SETUP_RESPONSE:
		tf->category = WLAN_CATEGORY_TDLS;
		tf->action_code = WLAN_TDLS_SETUP_RESPONSE;
		skb_put(skb, माप(tf->u.setup_resp));
		tf->u.setup_resp.status_code = cpu_to_le16(status_code);
		tf->u.setup_resp.dialog_token = dialog_token;
		tf->u.setup_resp.capability = cpu_to_le16(capab);
		ret = mwअगरiex_tdls_append_rates_ie(priv, skb);
		अगर (ret) अणु
			dev_kमुक्त_skb_any(skb);
			वापस ret;
		पूर्ण

		pos = skb_put(skb, माप(काष्ठा ieee80211_ht_cap) + 2);
		*pos++ = WLAN_EID_HT_CAPABILITY;
		*pos++ = माप(काष्ठा ieee80211_ht_cap);
		ht_cap = (व्योम *)pos;
		radio = mwअगरiex_band_to_radio_type(priv->curr_bss_params.band);
		ret = mwअगरiex_fill_cap_info(priv, radio, ht_cap);
		अगर (ret) अणु
			dev_kमुक्त_skb_any(skb);
			वापस ret;
		पूर्ण

		अगर (priv->adapter->is_hw_11ac_capable) अणु
			ret = mwअगरiex_tdls_add_vht_capab(priv, skb);
			अगर (ret) अणु
				dev_kमुक्त_skb_any(skb);
				वापस ret;
			पूर्ण
			mwअगरiex_tdls_add_aid(priv, skb);
		पूर्ण

		mwअगरiex_tdls_add_ext_capab(priv, skb);
		mwअगरiex_tdls_add_bss_co_2040(skb);
		mwअगरiex_tdls_add_supported_chan(skb);
		mwअगरiex_tdls_add_oper_class(skb);
		mwअगरiex_add_wmm_info_ie(priv, skb, 0);
		अवरोध;

	हाल WLAN_TDLS_SETUP_CONFIRM:
		tf->category = WLAN_CATEGORY_TDLS;
		tf->action_code = WLAN_TDLS_SETUP_CONFIRM;
		skb_put(skb, माप(tf->u.setup_cfm));
		tf->u.setup_cfm.status_code = cpu_to_le16(status_code);
		tf->u.setup_cfm.dialog_token = dialog_token;

		mwअगरiex_tdls_add_wmm_param_ie(priv, skb);
		अगर (priv->adapter->is_hw_11ac_capable) अणु
			ret = mwअगरiex_tdls_add_vht_oper(priv, peer, skb);
			अगर (ret) अणु
				dev_kमुक्त_skb_any(skb);
				वापस ret;
			पूर्ण
			ret = mwअगरiex_tdls_add_ht_oper(priv, peer, 1, skb);
			अगर (ret) अणु
				dev_kमुक्त_skb_any(skb);
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = mwअगरiex_tdls_add_ht_oper(priv, peer, 0, skb);
			अगर (ret) अणु
				dev_kमुक्त_skb_any(skb);
				वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल WLAN_TDLS_TEARDOWN:
		tf->category = WLAN_CATEGORY_TDLS;
		tf->action_code = WLAN_TDLS_TEARDOWN;
		skb_put(skb, माप(tf->u.tearकरोwn));
		tf->u.tearकरोwn.reason_code = cpu_to_le16(status_code);
		अवरोध;

	हाल WLAN_TDLS_DISCOVERY_REQUEST:
		tf->category = WLAN_CATEGORY_TDLS;
		tf->action_code = WLAN_TDLS_DISCOVERY_REQUEST;
		skb_put(skb, माप(tf->u.discover_req));
		tf->u.discover_req.dialog_token = dialog_token;
		अवरोध;
	शेष:
		mwअगरiex_dbg(priv->adapter, ERROR, "Unknown TDLS frame type.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
mwअगरiex_tdls_add_link_ie(काष्ठा sk_buff *skb, स्थिर u8 *src_addr,
			 स्थिर u8 *peer, स्थिर u8 *bssid)
अणु
	काष्ठा ieee80211_tdls_lnkie *lnkid;

	lnkid = skb_put(skb, माप(काष्ठा ieee80211_tdls_lnkie));
	lnkid->ie_type = WLAN_EID_LINK_ID;
	lnkid->ie_len = माप(काष्ठा ieee80211_tdls_lnkie) -
			माप(काष्ठा ieee_types_header);

	स_नकल(lnkid->bssid, bssid, ETH_ALEN);
	स_नकल(lnkid->init_sta, src_addr, ETH_ALEN);
	स_नकल(lnkid->resp_sta, peer, ETH_ALEN);
पूर्ण

पूर्णांक mwअगरiex_send_tdls_data_frame(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *peer,
				 u8 action_code, u8 dialog_token,
				 u16 status_code, स्थिर u8 *extra_ies,
				 माप_प्रकार extra_ies_len)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा mwअगरiex_txinfo *tx_info;
	पूर्णांक ret;
	u16 skb_len;

	skb_len = MWIFIEX_MIN_DATA_HEADER_LEN +
		  max(माप(काष्ठा ieee80211_mgmt),
		      माप(काष्ठा ieee80211_tdls_data)) +
		  MWIFIEX_MGMT_FRAME_HEADER_SIZE +
		  MWIFIEX_SUPPORTED_RATES +
		  3 + /* Qos Info */
		  माप(काष्ठा ieee_types_extcap) +
		  माप(काष्ठा ieee80211_ht_cap) +
		  माप(काष्ठा ieee_types_bss_co_2040) +
		  माप(काष्ठा ieee80211_ht_operation) +
		  माप(काष्ठा ieee80211_tdls_lnkie) +
		  (2 * (माप(काष्ठा ieee_types_header))) +
		   MWIFIEX_SUPPORTED_CHANNELS +
		   MWIFIEX_OPERATING_CLASSES +
		  माप(काष्ठा ieee80211_wmm_param_ie) +
		  extra_ies_len;

	अगर (priv->adapter->is_hw_11ac_capable)
		skb_len += माप(काष्ठा ieee_types_vht_cap) +
			   माप(काष्ठा ieee_types_vht_oper) +
			   माप(काष्ठा ieee_types_aid);

	skb = dev_alloc_skb(skb_len);
	अगर (!skb) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "allocate skb failed for management frame\n");
		वापस -ENOMEM;
	पूर्ण
	skb_reserve(skb, MWIFIEX_MIN_DATA_HEADER_LEN);

	चयन (action_code) अणु
	हाल WLAN_TDLS_SETUP_REQUEST:
	हाल WLAN_TDLS_SETUP_CONFIRM:
	हाल WLAN_TDLS_TEARDOWN:
	हाल WLAN_TDLS_DISCOVERY_REQUEST:
		ret = mwअगरiex_prep_tdls_encap_data(priv, peer, action_code,
						   dialog_token, status_code,
						   skb);
		अगर (ret) अणु
			dev_kमुक्त_skb_any(skb);
			वापस ret;
		पूर्ण
		अगर (extra_ies_len)
			skb_put_data(skb, extra_ies, extra_ies_len);
		mwअगरiex_tdls_add_link_ie(skb, priv->curr_addr, peer,
					 priv->cfg_bssid);
		अवरोध;
	हाल WLAN_TDLS_SETUP_RESPONSE:
		ret = mwअगरiex_prep_tdls_encap_data(priv, peer, action_code,
						   dialog_token, status_code,
						   skb);
		अगर (ret) अणु
			dev_kमुक्त_skb_any(skb);
			वापस ret;
		पूर्ण
		अगर (extra_ies_len)
			skb_put_data(skb, extra_ies, extra_ies_len);
		mwअगरiex_tdls_add_link_ie(skb, peer, priv->curr_addr,
					 priv->cfg_bssid);
		अवरोध;
	पूर्ण

	चयन (action_code) अणु
	हाल WLAN_TDLS_SETUP_REQUEST:
	हाल WLAN_TDLS_SETUP_RESPONSE:
		skb->priority = MWIFIEX_PRIO_BK;
		अवरोध;
	शेष:
		skb->priority = MWIFIEX_PRIO_VI;
		अवरोध;
	पूर्ण

	tx_info = MWIFIEX_SKB_TXCB(skb);
	स_रखो(tx_info, 0, माप(*tx_info));
	tx_info->bss_num = priv->bss_num;
	tx_info->bss_type = priv->bss_type;

	__net_बारtamp(skb);
	mwअगरiex_queue_tx_pkt(priv, skb);

	/* Delay 10ms to make sure tdls setup confirm/tearकरोwn frame
	 * is received by peer
	*/
	अगर (action_code == WLAN_TDLS_SETUP_CONFIRM ||
	    action_code == WLAN_TDLS_TEARDOWN)
		msleep_पूर्णांकerruptible(10);

	वापस 0;
पूर्ण

अटल पूर्णांक
mwअगरiex_स्थिरruct_tdls_action_frame(काष्ठा mwअगरiex_निजी *priv,
				    स्थिर u8 *peer,
				    u8 action_code, u8 dialog_token,
				    u16 status_code, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_mgmt *mgmt;
	पूर्णांक ret;
	u16 capab;
	काष्ठा ieee80211_ht_cap *ht_cap;
	u8 radio, *pos;

	capab = priv->curr_bss_params.bss_descriptor.cap_info_biपंचांगap;

	mgmt = skb_put(skb, दुरत्व(काष्ठा ieee80211_mgmt, u));

	स_रखो(mgmt, 0, 24);
	स_नकल(mgmt->da, peer, ETH_ALEN);
	स_नकल(mgmt->sa, priv->curr_addr, ETH_ALEN);
	स_नकल(mgmt->bssid, priv->cfg_bssid, ETH_ALEN);
	mgmt->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_ACTION);

	/* add address 4 */
	pos = skb_put(skb, ETH_ALEN);

	चयन (action_code) अणु
	हाल WLAN_PUB_ACTION_TDLS_DISCOVER_RES:
		skb_put(skb, माप(mgmt->u.action.u.tdls_discover_resp) + 1);
		mgmt->u.action.category = WLAN_CATEGORY_PUBLIC;
		mgmt->u.action.u.tdls_discover_resp.action_code =
					      WLAN_PUB_ACTION_TDLS_DISCOVER_RES;
		mgmt->u.action.u.tdls_discover_resp.dialog_token =
								   dialog_token;
		mgmt->u.action.u.tdls_discover_resp.capability =
							     cpu_to_le16(capab);
		/* move back क्रम addr4 */
		स_हटाओ(pos + ETH_ALEN, &mgmt->u.action.category,
			माप(mgmt->u.action.u.tdls_discover_resp));
		/* init address 4 */
		eth_broadcast_addr(pos);

		ret = mwअगरiex_tdls_append_rates_ie(priv, skb);
		अगर (ret) अणु
			dev_kमुक्त_skb_any(skb);
			वापस ret;
		पूर्ण

		pos = skb_put(skb, माप(काष्ठा ieee80211_ht_cap) + 2);
		*pos++ = WLAN_EID_HT_CAPABILITY;
		*pos++ = माप(काष्ठा ieee80211_ht_cap);
		ht_cap = (व्योम *)pos;
		radio = mwअगरiex_band_to_radio_type(priv->curr_bss_params.band);
		ret = mwअगरiex_fill_cap_info(priv, radio, ht_cap);
		अगर (ret) अणु
			dev_kमुक्त_skb_any(skb);
			वापस ret;
		पूर्ण

		अगर (priv->adapter->is_hw_11ac_capable) अणु
			ret = mwअगरiex_tdls_add_vht_capab(priv, skb);
			अगर (ret) अणु
				dev_kमुक्त_skb_any(skb);
				वापस ret;
			पूर्ण
			mwअगरiex_tdls_add_aid(priv, skb);
		पूर्ण

		mwअगरiex_tdls_add_ext_capab(priv, skb);
		mwअगरiex_tdls_add_bss_co_2040(skb);
		mwअगरiex_tdls_add_supported_chan(skb);
		mwअगरiex_tdls_add_qos_capab(skb);
		mwअगरiex_tdls_add_oper_class(skb);
		अवरोध;
	शेष:
		mwअगरiex_dbg(priv->adapter, ERROR, "Unknown TDLS action frame type\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mwअगरiex_send_tdls_action_frame(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *peer,
				   u8 action_code, u8 dialog_token,
				   u16 status_code, स्थिर u8 *extra_ies,
				   माप_प्रकार extra_ies_len)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा mwअगरiex_txinfo *tx_info;
	u8 *pos;
	u32 pkt_type, tx_control;
	u16 pkt_len, skb_len;

	skb_len = MWIFIEX_MIN_DATA_HEADER_LEN +
		  max(माप(काष्ठा ieee80211_mgmt),
		      माप(काष्ठा ieee80211_tdls_data)) +
		  MWIFIEX_MGMT_FRAME_HEADER_SIZE +
		  MWIFIEX_SUPPORTED_RATES +
		  माप(काष्ठा ieee_types_extcap) +
		  माप(काष्ठा ieee80211_ht_cap) +
		  माप(काष्ठा ieee_types_bss_co_2040) +
		  माप(काष्ठा ieee80211_ht_operation) +
		  माप(काष्ठा ieee80211_tdls_lnkie) +
		  extra_ies_len +
		  3 + /* Qos Info */
		  ETH_ALEN; /* Address4 */

	अगर (priv->adapter->is_hw_11ac_capable)
		skb_len += माप(काष्ठा ieee_types_vht_cap) +
			   माप(काष्ठा ieee_types_vht_oper) +
			   माप(काष्ठा ieee_types_aid);

	skb = dev_alloc_skb(skb_len);
	अगर (!skb) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "allocate skb failed for management frame\n");
		वापस -ENOMEM;
	पूर्ण

	skb_reserve(skb, MWIFIEX_MIN_DATA_HEADER_LEN);

	pkt_type = PKT_TYPE_MGMT;
	tx_control = 0;
	pos = skb_put_zero(skb,
			   MWIFIEX_MGMT_FRAME_HEADER_SIZE + माप(pkt_len));
	स_नकल(pos, &pkt_type, माप(pkt_type));
	स_नकल(pos + माप(pkt_type), &tx_control, माप(tx_control));

	अगर (mwअगरiex_स्थिरruct_tdls_action_frame(priv, peer, action_code,
						dialog_token, status_code,
						skb)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस -EINVAL;
	पूर्ण

	अगर (extra_ies_len)
		skb_put_data(skb, extra_ies, extra_ies_len);

	/* the TDLS link IE is always added last we are the responder */

	mwअगरiex_tdls_add_link_ie(skb, peer, priv->curr_addr,
				 priv->cfg_bssid);

	skb->priority = MWIFIEX_PRIO_VI;

	tx_info = MWIFIEX_SKB_TXCB(skb);
	स_रखो(tx_info, 0, माप(*tx_info));
	tx_info->bss_num = priv->bss_num;
	tx_info->bss_type = priv->bss_type;
	tx_info->flags |= MWIFIEX_BUF_FLAG_TDLS_PKT;

	pkt_len = skb->len - MWIFIEX_MGMT_FRAME_HEADER_SIZE - माप(pkt_len);
	स_नकल(skb->data + MWIFIEX_MGMT_FRAME_HEADER_SIZE, &pkt_len,
	       माप(pkt_len));
	__net_बारtamp(skb);
	mwअगरiex_queue_tx_pkt(priv, skb);

	वापस 0;
पूर्ण

/* This function process tdls action frame from peer.
 * Peer capabilities are stored पूर्णांकo station node काष्ठाure.
 */
व्योम mwअगरiex_process_tdls_action_frame(काष्ठा mwअगरiex_निजी *priv,
				       u8 *buf, पूर्णांक len)
अणु
	काष्ठा mwअगरiex_sta_node *sta_ptr;
	u8 *peer, *pos, *end;
	u8 i, action, basic;
	u16 cap = 0;
	पूर्णांक ies_len = 0;

	अगर (len < (माप(काष्ठा ethhdr) + 3))
		वापस;
	अगर (*(buf + माप(काष्ठा ethhdr)) != WLAN_TDLS_SNAP_RFTYPE)
		वापस;
	अगर (*(buf + माप(काष्ठा ethhdr) + 1) != WLAN_CATEGORY_TDLS)
		वापस;

	peer = buf + ETH_ALEN;
	action = *(buf + माप(काष्ठा ethhdr) + 2);
	mwअगरiex_dbg(priv->adapter, DATA,
		    "rx:tdls action: peer=%pM, action=%d\n", peer, action);

	चयन (action) अणु
	हाल WLAN_TDLS_SETUP_REQUEST:
		अगर (len < (माप(काष्ठा ethhdr) + TDLS_REQ_FIX_LEN))
			वापस;

		pos = buf + माप(काष्ठा ethhdr) + 4;
		/* payload 1+ category 1 + action 1 + dialog 1 */
		cap = get_unaligned_le16(pos);
		ies_len = len - माप(काष्ठा ethhdr) - TDLS_REQ_FIX_LEN;
		pos += 2;
		अवरोध;

	हाल WLAN_TDLS_SETUP_RESPONSE:
		अगर (len < (माप(काष्ठा ethhdr) + TDLS_RESP_FIX_LEN))
			वापस;
		/* payload 1+ category 1 + action 1 + dialog 1 + status code 2*/
		pos = buf + माप(काष्ठा ethhdr) + 6;
		cap = get_unaligned_le16(pos);
		ies_len = len - माप(काष्ठा ethhdr) - TDLS_RESP_FIX_LEN;
		pos += 2;
		अवरोध;

	हाल WLAN_TDLS_SETUP_CONFIRM:
		अगर (len < (माप(काष्ठा ethhdr) + TDLS_CONFIRM_FIX_LEN))
			वापस;
		pos = buf + माप(काष्ठा ethhdr) + TDLS_CONFIRM_FIX_LEN;
		ies_len = len - माप(काष्ठा ethhdr) - TDLS_CONFIRM_FIX_LEN;
		अवरोध;
	शेष:
		mwअगरiex_dbg(priv->adapter, ERROR, "Unknown TDLS frame type.\n");
		वापस;
	पूर्ण

	sta_ptr = mwअगरiex_add_sta_entry(priv, peer);
	अगर (!sta_ptr)
		वापस;

	sta_ptr->tdls_cap.capab = cpu_to_le16(cap);

	क्रम (end = pos + ies_len; pos + 1 < end; pos += 2 + pos[1]) अणु
		u8 ie_len = pos[1];

		अगर (pos + 2 + ie_len > end)
			अवरोध;

		चयन (*pos) अणु
		हाल WLAN_EID_SUPP_RATES:
			अगर (ie_len > माप(sta_ptr->tdls_cap.rates))
				वापस;
			sta_ptr->tdls_cap.rates_len = ie_len;
			क्रम (i = 0; i < ie_len; i++)
				sta_ptr->tdls_cap.rates[i] = pos[i + 2];
			अवरोध;

		हाल WLAN_EID_EXT_SUPP_RATES:
			अगर (ie_len > माप(sta_ptr->tdls_cap.rates))
				वापस;
			basic = sta_ptr->tdls_cap.rates_len;
			अगर (ie_len > माप(sta_ptr->tdls_cap.rates) - basic)
				वापस;
			क्रम (i = 0; i < ie_len; i++)
				sta_ptr->tdls_cap.rates[basic + i] = pos[i + 2];
			sta_ptr->tdls_cap.rates_len += ie_len;
			अवरोध;
		हाल WLAN_EID_HT_CAPABILITY:
			अगर (ie_len != माप(काष्ठा ieee80211_ht_cap))
				वापस;
			/* copy the ie's value पूर्णांकo ht_capb*/
			स_नकल((u8 *)&sta_ptr->tdls_cap.ht_capb, pos + 2,
			       माप(काष्ठा ieee80211_ht_cap));
			sta_ptr->is_11n_enabled = 1;
			अवरोध;
		हाल WLAN_EID_HT_OPERATION:
			अगर (ie_len != माप(काष्ठा ieee80211_ht_operation))
				वापस;
			/* copy the ie's value पूर्णांकo ht_oper*/
			स_नकल(&sta_ptr->tdls_cap.ht_oper, pos + 2,
			       माप(काष्ठा ieee80211_ht_operation));
			अवरोध;
		हाल WLAN_EID_BSS_COEX_2040:
			अगर (ie_len != माप(pos[2]))
				वापस;
			sta_ptr->tdls_cap.coex_2040 = pos[2];
			अवरोध;
		हाल WLAN_EID_EXT_CAPABILITY:
			अगर (ie_len < माप(काष्ठा ieee_types_header))
				वापस;
			अगर (ie_len > 8)
				वापस;
			स_नकल((u8 *)&sta_ptr->tdls_cap.extcap, pos,
			       माप(काष्ठा ieee_types_header) +
			       min_t(u8, ie_len, 8));
			अवरोध;
		हाल WLAN_EID_RSN:
			अगर (ie_len < माप(काष्ठा ieee_types_header))
				वापस;
			अगर (ie_len > IEEE_MAX_IE_SIZE -
			    माप(काष्ठा ieee_types_header))
				वापस;
			स_नकल((u8 *)&sta_ptr->tdls_cap.rsn_ie, pos,
			       माप(काष्ठा ieee_types_header) +
			       min_t(u8, ie_len, IEEE_MAX_IE_SIZE -
				     माप(काष्ठा ieee_types_header)));
			अवरोध;
		हाल WLAN_EID_QOS_CAPA:
			अगर (ie_len != माप(pos[2]))
				वापस;
			sta_ptr->tdls_cap.qos_info = pos[2];
			अवरोध;
		हाल WLAN_EID_VHT_OPERATION:
			अगर (priv->adapter->is_hw_11ac_capable) अणु
				अगर (ie_len !=
				    माप(काष्ठा ieee80211_vht_operation))
					वापस;
				/* copy the ie's value पूर्णांकo vhtoper*/
				स_नकल(&sta_ptr->tdls_cap.vhtoper, pos + 2,
				       माप(काष्ठा ieee80211_vht_operation));
			पूर्ण
			अवरोध;
		हाल WLAN_EID_VHT_CAPABILITY:
			अगर (priv->adapter->is_hw_11ac_capable) अणु
				अगर (ie_len != माप(काष्ठा ieee80211_vht_cap))
					वापस;
				/* copy the ie's value पूर्णांकo vhtcap*/
				स_नकल((u8 *)&sta_ptr->tdls_cap.vhtcap, pos + 2,
				       माप(काष्ठा ieee80211_vht_cap));
				sta_ptr->is_11ac_enabled = 1;
			पूर्ण
			अवरोध;
		हाल WLAN_EID_AID:
			अगर (priv->adapter->is_hw_11ac_capable) अणु
				अगर (ie_len != माप(u16))
					वापस;
				sta_ptr->tdls_cap.aid =
					get_unaligned_le16((pos + 2));
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

अटल पूर्णांक
mwअगरiex_tdls_process_config_link(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *peer)
अणु
	काष्ठा mwअगरiex_sta_node *sta_ptr;
	काष्ठा mwअगरiex_ds_tdls_oper tdls_oper;

	स_रखो(&tdls_oper, 0, माप(काष्ठा mwअगरiex_ds_tdls_oper));
	sta_ptr = mwअगरiex_get_sta_entry(priv, peer);

	अगर (!sta_ptr || sta_ptr->tdls_status == TDLS_SETUP_FAILURE) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "link absent for peer %pM; cannot config\n", peer);
		वापस -EINVAL;
	पूर्ण

	स_नकल(&tdls_oper.peer_mac, peer, ETH_ALEN);
	tdls_oper.tdls_action = MWIFIEX_TDLS_CONFIG_LINK;
	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_TDLS_OPER,
				HostCmd_ACT_GEN_SET, 0, &tdls_oper, true);
पूर्ण

अटल पूर्णांक
mwअगरiex_tdls_process_create_link(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *peer)
अणु
	काष्ठा mwअगरiex_sta_node *sta_ptr;
	काष्ठा mwअगरiex_ds_tdls_oper tdls_oper;

	स_रखो(&tdls_oper, 0, माप(काष्ठा mwअगरiex_ds_tdls_oper));
	sta_ptr = mwअगरiex_get_sta_entry(priv, peer);

	अगर (sta_ptr && sta_ptr->tdls_status == TDLS_SETUP_INPROGRESS) अणु
		mwअगरiex_dbg(priv->adapter, WARN,
			    "Setup already in progress for peer %pM\n", peer);
		वापस 0;
	पूर्ण

	sta_ptr = mwअगरiex_add_sta_entry(priv, peer);
	अगर (!sta_ptr)
		वापस -ENOMEM;

	sta_ptr->tdls_status = TDLS_SETUP_INPROGRESS;
	mwअगरiex_hold_tdls_packets(priv, peer);
	स_नकल(&tdls_oper.peer_mac, peer, ETH_ALEN);
	tdls_oper.tdls_action = MWIFIEX_TDLS_CREATE_LINK;
	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_TDLS_OPER,
				HostCmd_ACT_GEN_SET, 0, &tdls_oper, true);
पूर्ण

अटल पूर्णांक
mwअगरiex_tdls_process_disable_link(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *peer)
अणु
	काष्ठा mwअगरiex_sta_node *sta_ptr;
	काष्ठा mwअगरiex_ds_tdls_oper tdls_oper;

	स_रखो(&tdls_oper, 0, माप(काष्ठा mwअगरiex_ds_tdls_oper));
	sta_ptr = mwअगरiex_get_sta_entry(priv, peer);

	अगर (sta_ptr) अणु
		अगर (sta_ptr->is_11n_enabled) अणु
			mwअगरiex_11n_cleanup_reorder_tbl(priv);
			spin_lock_bh(&priv->wmm.ra_list_spinlock);
			mwअगरiex_11n_delete_all_tx_ba_stream_tbl(priv);
			spin_unlock_bh(&priv->wmm.ra_list_spinlock);
		पूर्ण
		mwअगरiex_del_sta_entry(priv, peer);
	पूर्ण

	mwअगरiex_restore_tdls_packets(priv, peer, TDLS_LINK_TEARDOWN);
	mwअगरiex_स्वतः_tdls_update_peer_status(priv, peer, TDLS_NOT_SETUP);
	स_नकल(&tdls_oper.peer_mac, peer, ETH_ALEN);
	tdls_oper.tdls_action = MWIFIEX_TDLS_DISABLE_LINK;
	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_TDLS_OPER,
				HostCmd_ACT_GEN_SET, 0, &tdls_oper, true);
पूर्ण

अटल पूर्णांक
mwअगरiex_tdls_process_enable_link(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *peer)
अणु
	काष्ठा mwअगरiex_sta_node *sta_ptr;
	काष्ठा ieee80211_mcs_info mcs;
	पूर्णांक i;

	sta_ptr = mwअगरiex_get_sta_entry(priv, peer);

	अगर (sta_ptr && (sta_ptr->tdls_status != TDLS_SETUP_FAILURE)) अणु
		mwअगरiex_dbg(priv->adapter, MSG,
			    "tdls: enable link %pM success\n", peer);

		sta_ptr->tdls_status = TDLS_SETUP_COMPLETE;

		mcs = sta_ptr->tdls_cap.ht_capb.mcs;
		अगर (mcs.rx_mask[0] != 0xff)
			sta_ptr->is_11n_enabled = true;
		अगर (sta_ptr->is_11n_enabled) अणु
			अगर (le16_to_cpu(sta_ptr->tdls_cap.ht_capb.cap_info) &
			    IEEE80211_HT_CAP_MAX_AMSDU)
				sta_ptr->max_amsdu =
					MWIFIEX_TX_DATA_BUF_SIZE_8K;
			अन्यथा
				sta_ptr->max_amsdu =
					MWIFIEX_TX_DATA_BUF_SIZE_4K;

			क्रम (i = 0; i < MAX_NUM_TID; i++)
				sta_ptr->ampdu_sta[i] =
					      priv->aggr_prio_tbl[i].ampdu_user;
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < MAX_NUM_TID; i++)
				sta_ptr->ampdu_sta[i] = BA_STREAM_NOT_ALLOWED;
		पूर्ण
		अगर (sta_ptr->tdls_cap.extcap.ext_capab[3] &
		    WLAN_EXT_CAPA4_TDLS_CHAN_SWITCH) अणु
			mwअगरiex_config_tdls_enable(priv);
			mwअगरiex_config_tdls_cs_params(priv);
		पूर्ण

		स_रखो(sta_ptr->rx_seq, 0xff, माप(sta_ptr->rx_seq));
		mwअगरiex_restore_tdls_packets(priv, peer, TDLS_SETUP_COMPLETE);
		mwअगरiex_स्वतः_tdls_update_peer_status(priv, peer,
						     TDLS_SETUP_COMPLETE);
	पूर्ण अन्यथा अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "tdls: enable link %pM failed\n", peer);
		अगर (sta_ptr) अणु
			mwअगरiex_11n_cleanup_reorder_tbl(priv);
			spin_lock_bh(&priv->wmm.ra_list_spinlock);
			mwअगरiex_11n_delete_all_tx_ba_stream_tbl(priv);
			spin_unlock_bh(&priv->wmm.ra_list_spinlock);
			mwअगरiex_del_sta_entry(priv, peer);
		पूर्ण
		mwअगरiex_restore_tdls_packets(priv, peer, TDLS_LINK_TEARDOWN);
		mwअगरiex_स्वतः_tdls_update_peer_status(priv, peer,
						     TDLS_NOT_SETUP);

		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mwअगरiex_tdls_oper(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *peer, u8 action)
अणु
	चयन (action) अणु
	हाल MWIFIEX_TDLS_ENABLE_LINK:
		वापस mwअगरiex_tdls_process_enable_link(priv, peer);
	हाल MWIFIEX_TDLS_DISABLE_LINK:
		वापस mwअगरiex_tdls_process_disable_link(priv, peer);
	हाल MWIFIEX_TDLS_CREATE_LINK:
		वापस mwअगरiex_tdls_process_create_link(priv, peer);
	हाल MWIFIEX_TDLS_CONFIG_LINK:
		वापस mwअगरiex_tdls_process_config_link(priv, peer);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक mwअगरiex_get_tdls_link_status(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *mac)
अणु
	काष्ठा mwअगरiex_sta_node *sta_ptr;

	sta_ptr = mwअगरiex_get_sta_entry(priv, mac);
	अगर (sta_ptr)
		वापस sta_ptr->tdls_status;

	वापस TDLS_NOT_SETUP;
पूर्ण

पूर्णांक mwअगरiex_get_tdls_list(काष्ठा mwअगरiex_निजी *priv,
			  काष्ठा tdls_peer_info *buf)
अणु
	काष्ठा mwअगरiex_sta_node *sta_ptr;
	काष्ठा tdls_peer_info *peer = buf;
	पूर्णांक count = 0;

	अगर (!ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info))
		वापस 0;

	/* make sure we are in station mode and connected */
	अगर (!(priv->bss_type == MWIFIEX_BSS_TYPE_STA && priv->media_connected))
		वापस 0;

	spin_lock_bh(&priv->sta_list_spinlock);
	list_क्रम_each_entry(sta_ptr, &priv->sta_list, list) अणु
		अगर (mwअगरiex_is_tdls_link_setup(sta_ptr->tdls_status)) अणु
			ether_addr_copy(peer->peer_addr, sta_ptr->mac_addr);
			peer++;
			count++;
			अगर (count >= MWIFIEX_MAX_TDLS_PEER_SUPPORTED)
				अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&priv->sta_list_spinlock);

	वापस count;
पूर्ण

व्योम mwअगरiex_disable_all_tdls_links(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_sta_node *sta_ptr;
	काष्ठा mwअगरiex_ds_tdls_oper tdls_oper;

	अगर (list_empty(&priv->sta_list))
		वापस;

	list_क्रम_each_entry(sta_ptr, &priv->sta_list, list) अणु
		स_रखो(&tdls_oper, 0, माप(काष्ठा mwअगरiex_ds_tdls_oper));

		अगर (sta_ptr->is_11n_enabled) अणु
			mwअगरiex_11n_cleanup_reorder_tbl(priv);
			spin_lock_bh(&priv->wmm.ra_list_spinlock);
			mwअगरiex_11n_delete_all_tx_ba_stream_tbl(priv);
			spin_unlock_bh(&priv->wmm.ra_list_spinlock);
		पूर्ण

		mwअगरiex_restore_tdls_packets(priv, sta_ptr->mac_addr,
					     TDLS_LINK_TEARDOWN);
		स_नकल(&tdls_oper.peer_mac, sta_ptr->mac_addr, ETH_ALEN);
		tdls_oper.tdls_action = MWIFIEX_TDLS_DISABLE_LINK;
		अगर (mwअगरiex_send_cmd(priv, HostCmd_CMD_TDLS_OPER,
				     HostCmd_ACT_GEN_SET, 0, &tdls_oper, false))
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "Disable link failed for TDLS peer %pM",
				    sta_ptr->mac_addr);
	पूर्ण

	mwअगरiex_del_all_sta_list(priv);
पूर्ण

पूर्णांक mwअगरiex_tdls_check_tx(काष्ठा mwअगरiex_निजी *priv, काष्ठा sk_buff *skb)
अणु
	काष्ठा mwअगरiex_स्वतः_tdls_peer *peer;
	u8 mac[ETH_ALEN];

	ether_addr_copy(mac, skb->data);

	spin_lock_bh(&priv->स्वतः_tdls_lock);
	list_क्रम_each_entry(peer, &priv->स्वतः_tdls_list, list) अणु
		अगर (!स_भेद(mac, peer->mac_addr, ETH_ALEN)) अणु
			अगर (peer->rssi <= MWIFIEX_TDLS_RSSI_HIGH &&
			    peer->tdls_status == TDLS_NOT_SETUP &&
			    (peer->failure_count <
			     MWIFIEX_TDLS_MAX_FAIL_COUNT)) अणु
				peer->tdls_status = TDLS_SETUP_INPROGRESS;
				mwअगरiex_dbg(priv->adapter, INFO,
					    "setup TDLS link, peer=%pM rssi=%d\n",
					    peer->mac_addr, peer->rssi);

				cfg80211_tdls_oper_request(priv->netdev,
							   peer->mac_addr,
							   NL80211_TDLS_SETUP,
							   0, GFP_ATOMIC);
				peer->करो_setup = false;
				priv->check_tdls_tx = false;
			पूर्ण अन्यथा अगर (peer->failure_count <
				   MWIFIEX_TDLS_MAX_FAIL_COUNT &&
				   peer->करो_discover) अणु
				mwअगरiex_send_tdls_data_frame(priv,
							     peer->mac_addr,
						    WLAN_TDLS_DISCOVERY_REQUEST,
							     1, 0, शून्य, 0);
				peer->करो_discover = false;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_bh(&priv->स्वतः_tdls_lock);

	वापस 0;
पूर्ण

व्योम mwअगरiex_flush_स्वतः_tdls_list(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_स्वतः_tdls_peer *peer, *पंचांगp_node;

	spin_lock_bh(&priv->स्वतः_tdls_lock);
	list_क्रम_each_entry_safe(peer, पंचांगp_node, &priv->स्वतः_tdls_list, list) अणु
		list_del(&peer->list);
		kमुक्त(peer);
	पूर्ण

	INIT_LIST_HEAD(&priv->स्वतः_tdls_list);
	spin_unlock_bh(&priv->स्वतः_tdls_lock);
	priv->check_tdls_tx = false;
पूर्ण

व्योम mwअगरiex_add_स्वतः_tdls_peer(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *mac)
अणु
	काष्ठा mwअगरiex_स्वतः_tdls_peer *tdls_peer;

	अगर (!priv->adapter->स्वतः_tdls)
		वापस;

	spin_lock_bh(&priv->स्वतः_tdls_lock);
	list_क्रम_each_entry(tdls_peer, &priv->स्वतः_tdls_list, list) अणु
		अगर (!स_भेद(tdls_peer->mac_addr, mac, ETH_ALEN)) अणु
			tdls_peer->tdls_status = TDLS_SETUP_INPROGRESS;
			tdls_peer->rssi_jअगरfies = jअगरfies;
			spin_unlock_bh(&priv->स्वतः_tdls_lock);
			वापस;
		पूर्ण
	पूर्ण

	/* create new TDLS peer */
	tdls_peer = kzalloc(माप(*tdls_peer), GFP_ATOMIC);
	अगर (tdls_peer) अणु
		ether_addr_copy(tdls_peer->mac_addr, mac);
		tdls_peer->tdls_status = TDLS_SETUP_INPROGRESS;
		tdls_peer->rssi_jअगरfies = jअगरfies;
		INIT_LIST_HEAD(&tdls_peer->list);
		list_add_tail(&tdls_peer->list, &priv->स्वतः_tdls_list);
		mwअगरiex_dbg(priv->adapter, INFO,
			    "Add auto TDLS peer= %pM to list\n", mac);
	पूर्ण

	spin_unlock_bh(&priv->स्वतः_tdls_lock);
पूर्ण

व्योम mwअगरiex_स्वतः_tdls_update_peer_status(काष्ठा mwअगरiex_निजी *priv,
					  स्थिर u8 *mac, u8 link_status)
अणु
	काष्ठा mwअगरiex_स्वतः_tdls_peer *peer;

	अगर (!priv->adapter->स्वतः_tdls)
		वापस;

	spin_lock_bh(&priv->स्वतः_tdls_lock);
	list_क्रम_each_entry(peer, &priv->स्वतः_tdls_list, list) अणु
		अगर (!स_भेद(peer->mac_addr, mac, ETH_ALEN)) अणु
			अगर ((link_status == TDLS_NOT_SETUP) &&
			    (peer->tdls_status == TDLS_SETUP_INPROGRESS))
				peer->failure_count++;
			अन्यथा अगर (mwअगरiex_is_tdls_link_setup(link_status))
				peer->failure_count = 0;

			peer->tdls_status = link_status;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&priv->स्वतः_tdls_lock);
पूर्ण

व्योम mwअगरiex_स्वतः_tdls_update_peer_संकेत(काष्ठा mwअगरiex_निजी *priv,
					  u8 *mac, s8 snr, s8 nflr)
अणु
	काष्ठा mwअगरiex_स्वतः_tdls_peer *peer;

	अगर (!priv->adapter->स्वतः_tdls)
		वापस;

	spin_lock_bh(&priv->स्वतः_tdls_lock);
	list_क्रम_each_entry(peer, &priv->स्वतः_tdls_list, list) अणु
		अगर (!स_भेद(peer->mac_addr, mac, ETH_ALEN)) अणु
			peer->rssi = nflr - snr;
			peer->rssi_jअगरfies = jअगरfies;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&priv->स्वतः_tdls_lock);
पूर्ण

व्योम mwअगरiex_check_स्वतः_tdls(काष्ठा समयr_list *t)
अणु
	काष्ठा mwअगरiex_निजी *priv = from_समयr(priv, t, स्वतः_tdls_समयr);
	काष्ठा mwअगरiex_स्वतः_tdls_peer *tdls_peer;
	u16 reason = WLAN_REASON_TDLS_TEARDOWN_UNSPECIFIED;

	अगर (WARN_ON_ONCE(!priv || !priv->adapter)) अणु
		pr_err("mwifiex: %s: adapter or private structure is NULL\n",
		       __func__);
		वापस;
	पूर्ण

	अगर (unlikely(!priv->adapter->स्वतः_tdls))
		वापस;

	अगर (!priv->स्वतः_tdls_समयr_active) अणु
		mwअगरiex_dbg(priv->adapter, INFO,
			    "auto TDLS timer inactive; return");
		वापस;
	पूर्ण

	priv->check_tdls_tx = false;

	spin_lock_bh(&priv->स्वतः_tdls_lock);
	list_क्रम_each_entry(tdls_peer, &priv->स्वतः_tdls_list, list) अणु
		अगर ((jअगरfies - tdls_peer->rssi_jअगरfies) >
		    (MWIFIEX_AUTO_TDLS_IDLE_TIME * HZ)) अणु
			tdls_peer->rssi = 0;
			tdls_peer->करो_discover = true;
			priv->check_tdls_tx = true;
		पूर्ण

		अगर (((tdls_peer->rssi >= MWIFIEX_TDLS_RSSI_LOW) ||
		     !tdls_peer->rssi) &&
		    mwअगरiex_is_tdls_link_setup(tdls_peer->tdls_status)) अणु
			tdls_peer->tdls_status = TDLS_LINK_TEARDOWN;
			mwअगरiex_dbg(priv->adapter, MSG,
				    "teardown TDLS link,peer=%pM rssi=%d\n",
				    tdls_peer->mac_addr, -tdls_peer->rssi);
			tdls_peer->करो_discover = true;
			priv->check_tdls_tx = true;
			cfg80211_tdls_oper_request(priv->netdev,
						   tdls_peer->mac_addr,
						   NL80211_TDLS_TEARDOWN,
						   reason, GFP_ATOMIC);
		पूर्ण अन्यथा अगर (tdls_peer->rssi &&
			   tdls_peer->rssi <= MWIFIEX_TDLS_RSSI_HIGH &&
			   tdls_peer->tdls_status == TDLS_NOT_SETUP &&
			   tdls_peer->failure_count <
			   MWIFIEX_TDLS_MAX_FAIL_COUNT) अणु
				priv->check_tdls_tx = true;
				tdls_peer->करो_setup = true;
				mwअगरiex_dbg(priv->adapter, INFO,
					    "check TDLS with peer=%pM\t"
					    "rssi=%d\n", tdls_peer->mac_addr,
					    tdls_peer->rssi);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&priv->स्वतः_tdls_lock);

	mod_समयr(&priv->स्वतः_tdls_समयr,
		  jअगरfies + msecs_to_jअगरfies(MWIFIEX_TIMER_10S));
पूर्ण

व्योम mwअगरiex_setup_स्वतः_tdls_समयr(काष्ठा mwअगरiex_निजी *priv)
अणु
	समयr_setup(&priv->स्वतः_tdls_समयr, mwअगरiex_check_स्वतः_tdls, 0);
	priv->स्वतः_tdls_समयr_active = true;
	mod_समयr(&priv->स्वतः_tdls_समयr,
		  jअगरfies + msecs_to_jअगरfies(MWIFIEX_TIMER_10S));
पूर्ण

व्योम mwअगरiex_clean_स्वतः_tdls(काष्ठा mwअगरiex_निजी *priv)
अणु
	अगर (ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info) &&
	    priv->adapter->स्वतः_tdls &&
	    priv->bss_type == MWIFIEX_BSS_TYPE_STA) अणु
		priv->स्वतः_tdls_समयr_active = false;
		del_समयr(&priv->स्वतः_tdls_समयr);
		mwअगरiex_flush_स्वतः_tdls_list(priv);
	पूर्ण
पूर्ण

अटल पूर्णांक mwअगरiex_config_tdls(काष्ठा mwअगरiex_निजी *priv, u8 enable)
अणु
	काष्ठा mwअगरiex_tdls_config config;

	config.enable = cpu_to_le16(enable);
	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_TDLS_CONFIG,
				ACT_TDLS_CS_ENABLE_CONFIG, 0, &config, true);
पूर्ण

पूर्णांक mwअगरiex_config_tdls_enable(काष्ठा mwअगरiex_निजी *priv)
अणु
	वापस mwअगरiex_config_tdls(priv, true);
पूर्ण

पूर्णांक mwअगरiex_config_tdls_disable(काष्ठा mwअगरiex_निजी *priv)
अणु
	वापस mwअगरiex_config_tdls(priv, false);
पूर्ण

पूर्णांक mwअगरiex_config_tdls_cs_params(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_tdls_config_cs_params config_tdls_cs_params;

	config_tdls_cs_params.unit_समय = MWIFIEX_DEF_CS_UNIT_TIME;
	config_tdls_cs_params.thr_otherlink = MWIFIEX_DEF_CS_THR_OTHERLINK;
	config_tdls_cs_params.thr_directlink = MWIFIEX_DEF_THR_सूचीECTLINK;

	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_TDLS_CONFIG,
				ACT_TDLS_CS_PARAMS, 0,
				&config_tdls_cs_params, true);
पूर्ण

पूर्णांक mwअगरiex_stop_tdls_cs(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *peer_mac)
अणु
	काष्ठा mwअगरiex_tdls_stop_cs_params stop_tdls_cs_params;

	ether_addr_copy(stop_tdls_cs_params.peer_mac, peer_mac);

	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_TDLS_CONFIG,
				ACT_TDLS_CS_STOP, 0,
				&stop_tdls_cs_params, true);
पूर्ण

पूर्णांक mwअगरiex_start_tdls_cs(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *peer_mac,
			  u8 primary_chan, u8 second_chan_offset, u8 band)
अणु
	काष्ठा mwअगरiex_tdls_init_cs_params start_tdls_cs_params;

	ether_addr_copy(start_tdls_cs_params.peer_mac, peer_mac);
	start_tdls_cs_params.primary_chan = primary_chan;
	start_tdls_cs_params.second_chan_offset = second_chan_offset;
	start_tdls_cs_params.band = band;

	start_tdls_cs_params.चयन_समय = cpu_to_le16(MWIFIEX_DEF_CS_TIME);
	start_tdls_cs_params.चयन_समयout =
					cpu_to_le16(MWIFIEX_DEF_CS_TIMEOUT);
	start_tdls_cs_params.reg_class = MWIFIEX_DEF_CS_REG_CLASS;
	start_tdls_cs_params.periodicity = MWIFIEX_DEF_CS_PERIODICITY;

	वापस mwअगरiex_send_cmd(priv, HostCmd_CMD_TDLS_CONFIG,
				ACT_TDLS_CS_INIT, 0,
				&start_tdls_cs_params, true);
पूर्ण
