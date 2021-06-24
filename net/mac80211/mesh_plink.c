<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008, 2009 खोलो80211s Ltd.
 * Copyright (C) 2019 Intel Corporation
 * Author:     Luis Carlos Cobo <luisca@cozybit.com>
 */
#समावेश <linux/gfp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/rculist.h>

#समावेश "ieee80211_i.h"
#समावेश "rate.h"
#समावेश "mesh.h"

#घोषणा PLINK_CNF_AID(mgmt) ((mgmt)->u.action.u.self_prot.variable + 2)
#घोषणा PLINK_GET_LLID(p) (p + 2)
#घोषणा PLINK_GET_PLID(p) (p + 4)

#घोषणा mod_plink_समयr(s, t) (mod_समयr(&s->mesh->plink_समयr, \
				jअगरfies + msecs_to_jअगरfies(t)))

क्रमागत plink_event अणु
	PLINK_UNDEFINED,
	OPN_ACPT,
	OPN_RJCT,
	OPN_IGNR,
	CNF_ACPT,
	CNF_RJCT,
	CNF_IGNR,
	CLS_ACPT,
	CLS_IGNR
पूर्ण;

अटल स्थिर अक्षर * स्थिर mplstates[] = अणु
	[NL80211_PLINK_LISTEN] = "LISTEN",
	[NL80211_PLINK_OPN_SNT] = "OPN-SNT",
	[NL80211_PLINK_OPN_RCVD] = "OPN-RCVD",
	[NL80211_PLINK_CNF_RCVD] = "CNF_RCVD",
	[NL80211_PLINK_ESTAB] = "ESTAB",
	[NL80211_PLINK_HOLDING] = "HOLDING",
	[NL80211_PLINK_BLOCKED] = "BLOCKED"
पूर्ण;

अटल स्थिर अक्षर * स्थिर mplevents[] = अणु
	[PLINK_UNDEFINED] = "NONE",
	[OPN_ACPT] = "OPN_ACPT",
	[OPN_RJCT] = "OPN_RJCT",
	[OPN_IGNR] = "OPN_IGNR",
	[CNF_ACPT] = "CNF_ACPT",
	[CNF_RJCT] = "CNF_RJCT",
	[CNF_IGNR] = "CNF_IGNR",
	[CLS_ACPT] = "CLS_ACPT",
	[CLS_IGNR] = "CLS_IGNR"
पूर्ण;

/* We only need a valid sta अगर user configured a minimum rssi_threshold. */
अटल bool rssi_threshold_check(काष्ठा ieee80211_sub_अगर_data *sdata,
				 काष्ठा sta_info *sta)
अणु
	s32 rssi_threshold = sdata->u.mesh.mshcfg.rssi_threshold;
	वापस rssi_threshold == 0 ||
	       (sta &&
		(s8)-ewma_संकेत_पढ़ो(&sta->rx_stats_avg.संकेत) >
						rssi_threshold);
पूर्ण

/**
 * mesh_plink_fsm_restart - restart a mesh peer link finite state machine
 *
 * @sta: mesh peer link to restart
 *
 * Locking: this function must be called holding sta->mesh->plink_lock
 */
अटल अंतरभूत व्योम mesh_plink_fsm_restart(काष्ठा sta_info *sta)
अणु
	lockdep_निश्चित_held(&sta->mesh->plink_lock);
	sta->mesh->plink_state = NL80211_PLINK_LISTEN;
	sta->mesh->llid = sta->mesh->plid = sta->mesh->reason = 0;
	sta->mesh->plink_retries = 0;
पूर्ण

/*
 * mesh_set_लघु_slot_समय - enable / disable ERP लघु slot समय.
 *
 * The standard indirectly mandates mesh STAs to turn off लघु slot समय by
 * disallowing advertising this (802.11-2012 8.4.1.4), but that करोesn't mean we
 * can't be sneaky about it. Enable लघु slot समय अगर all mesh STAs in the
 * MBSS support ERP rates.
 *
 * Returns BSS_CHANGED_ERP_SLOT or 0 क्रम no change.
 */
अटल u32 mesh_set_लघु_slot_समय(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा sta_info *sta;
	u32 erp_rates = 0, changed = 0;
	पूर्णांक i;
	bool लघु_slot = false;

	sband = ieee80211_get_sband(sdata);
	अगर (!sband)
		वापस changed;

	अगर (sband->band == NL80211_BAND_5GHZ) अणु
		/* (IEEE 802.11-2012 19.4.5) */
		लघु_slot = true;
		जाओ out;
	पूर्ण अन्यथा अगर (sband->band != NL80211_BAND_2GHZ) अणु
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < sband->n_bitrates; i++)
		अगर (sband->bitrates[i].flags & IEEE80211_RATE_ERP_G)
			erp_rates |= BIT(i);

	अगर (!erp_rates)
		जाओ out;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sta, &local->sta_list, list) अणु
		अगर (sdata != sta->sdata ||
		    sta->mesh->plink_state != NL80211_PLINK_ESTAB)
			जारी;

		लघु_slot = false;
		अगर (erp_rates & sta->sta.supp_rates[sband->band])
			लघु_slot = true;
		 अन्यथा
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

out:
	अगर (sdata->vअगर.bss_conf.use_लघु_slot != लघु_slot) अणु
		sdata->vअगर.bss_conf.use_लघु_slot = लघु_slot;
		changed = BSS_CHANGED_ERP_SLOT;
		mpl_dbg(sdata, "mesh_plink %pM: ERP short slot time %d\n",
			sdata->vअगर.addr, लघु_slot);
	पूर्ण
	वापस changed;
पूर्ण

/**
 * mesh_set_ht_prot_mode - set correct HT protection mode
 * @sdata: the (mesh) पूर्णांकerface to handle
 *
 * Section 9.23.3.5 of IEEE 80211-2012 describes the protection rules क्रम HT
 * mesh STA in a MBSS. Three HT protection modes are supported क्रम now, non-HT
 * mixed mode, 20MHz-protection and no-protection mode. non-HT mixed mode is
 * selected अगर any non-HT peers are present in our MBSS.  20MHz-protection mode
 * is selected अगर all peers in our 20/40MHz MBSS support HT and atleast one
 * HT20 peer is present. Otherwise no-protection mode is selected.
 */
अटल u32 mesh_set_ht_prot_mode(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;
	u16 ht_opmode;
	bool non_ht_sta = false, ht20_sta = false;

	चयन (sdata->vअगर.bss_conf.chandef.width) अणु
	हाल NL80211_CHAN_WIDTH_20_NOHT:
	हाल NL80211_CHAN_WIDTH_5:
	हाल NL80211_CHAN_WIDTH_10:
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sta, &local->sta_list, list) अणु
		अगर (sdata != sta->sdata ||
		    sta->mesh->plink_state != NL80211_PLINK_ESTAB)
			जारी;

		अगर (sta->sta.bandwidth > IEEE80211_STA_RX_BW_20)
			जारी;

		अगर (!sta->sta.ht_cap.ht_supported) अणु
			mpl_dbg(sdata, "nonHT sta (%pM) is present\n",
				       sta->sta.addr);
			non_ht_sta = true;
			अवरोध;
		पूर्ण

		mpl_dbg(sdata, "HT20 sta (%pM) is present\n", sta->sta.addr);
		ht20_sta = true;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (non_ht_sta)
		ht_opmode = IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED;
	अन्यथा अगर (ht20_sta &&
		 sdata->vअगर.bss_conf.chandef.width > NL80211_CHAN_WIDTH_20)
		ht_opmode = IEEE80211_HT_OP_MODE_PROTECTION_20MHZ;
	अन्यथा
		ht_opmode = IEEE80211_HT_OP_MODE_PROTECTION_NONE;

	अगर (sdata->vअगर.bss_conf.ht_operation_mode == ht_opmode)
		वापस 0;

	sdata->vअगर.bss_conf.ht_operation_mode = ht_opmode;
	sdata->u.mesh.mshcfg.ht_opmode = ht_opmode;
	mpl_dbg(sdata, "selected new HT protection mode %d\n", ht_opmode);
	वापस BSS_CHANGED_HT;
पूर्ण

अटल पूर्णांक mesh_plink_frame_tx(काष्ठा ieee80211_sub_अगर_data *sdata,
			       काष्ठा sta_info *sta,
			       क्रमागत ieee80211_self_रक्षित_actioncode action,
			       u8 *da, u16 llid, u16 plid, u16 reason)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_mgmt *mgmt;
	bool include_plid = false;
	u16 peering_proto = 0;
	u8 *pos, ie_len = 4;
	u8 ie_len_he_cap;
	पूर्णांक hdr_len = दुरत्वend(काष्ठा ieee80211_mgmt, u.action.u.self_prot);
	पूर्णांक err = -ENOMEM;

	ie_len_he_cap = ieee80211_ie_len_he_cap(sdata,
						NL80211_IFTYPE_MESH_POINT);
	skb = dev_alloc_skb(local->tx_headroom +
			    hdr_len +
			    2 + /* capability info */
			    2 + /* AID */
			    2 + 8 + /* supported rates */
			    2 + (IEEE80211_MAX_SUPP_RATES - 8) +
			    2 + sdata->u.mesh.mesh_id_len +
			    2 + माप(काष्ठा ieee80211_meshconf_ie) +
			    2 + माप(काष्ठा ieee80211_ht_cap) +
			    2 + माप(काष्ठा ieee80211_ht_operation) +
			    2 + माप(काष्ठा ieee80211_vht_cap) +
			    2 + माप(काष्ठा ieee80211_vht_operation) +
			    ie_len_he_cap +
			    2 + 1 + माप(काष्ठा ieee80211_he_operation) +
				    माप(काष्ठा ieee80211_he_6ghz_oper) +
			    2 + 1 + माप(काष्ठा ieee80211_he_6ghz_capa) +
			    2 + 8 + /* peering IE */
			    sdata->u.mesh.ie_len);
	अगर (!skb)
		वापस err;
	info = IEEE80211_SKB_CB(skb);
	skb_reserve(skb, local->tx_headroom);
	mgmt = skb_put_zero(skb, hdr_len);
	mgmt->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_ACTION);
	स_नकल(mgmt->da, da, ETH_ALEN);
	स_नकल(mgmt->sa, sdata->vअगर.addr, ETH_ALEN);
	स_नकल(mgmt->bssid, sdata->vअगर.addr, ETH_ALEN);
	mgmt->u.action.category = WLAN_CATEGORY_SELF_PROTECTED;
	mgmt->u.action.u.self_prot.action_code = action;

	अगर (action != WLAN_SP_MESH_PEERING_CLOSE) अणु
		काष्ठा ieee80211_supported_band *sband;
		क्रमागत nl80211_band band;

		sband = ieee80211_get_sband(sdata);
		अगर (!sband) अणु
			err = -EINVAL;
			जाओ मुक्त;
		पूर्ण
		band = sband->band;

		/* capability info */
		pos = skb_put_zero(skb, 2);
		अगर (action == WLAN_SP_MESH_PEERING_CONFIRM) अणु
			/* AID */
			pos = skb_put(skb, 2);
			put_unaligned_le16(sta->sta.aid, pos);
		पूर्ण
		अगर (ieee80211_add_srates_ie(sdata, skb, true, band) ||
		    ieee80211_add_ext_srates_ie(sdata, skb, true, band) ||
		    mesh_add_rsn_ie(sdata, skb) ||
		    mesh_add_meshid_ie(sdata, skb) ||
		    mesh_add_meshconf_ie(sdata, skb))
			जाओ मुक्त;
	पूर्ण अन्यथा अणु	/* WLAN_SP_MESH_PEERING_CLOSE */
		info->flags |= IEEE80211_TX_CTL_NO_ACK;
		अगर (mesh_add_meshid_ie(sdata, skb))
			जाओ मुक्त;
	पूर्ण

	/* Add Mesh Peering Management element */
	चयन (action) अणु
	हाल WLAN_SP_MESH_PEERING_OPEN:
		अवरोध;
	हाल WLAN_SP_MESH_PEERING_CONFIRM:
		ie_len += 2;
		include_plid = true;
		अवरोध;
	हाल WLAN_SP_MESH_PEERING_CLOSE:
		अगर (plid) अणु
			ie_len += 2;
			include_plid = true;
		पूर्ण
		ie_len += 2;	/* reason code */
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	अगर (WARN_ON(skb_tailroom(skb) < 2 + ie_len))
		जाओ मुक्त;

	pos = skb_put(skb, 2 + ie_len);
	*pos++ = WLAN_EID_PEER_MGMT;
	*pos++ = ie_len;
	स_नकल(pos, &peering_proto, 2);
	pos += 2;
	put_unaligned_le16(llid, pos);
	pos += 2;
	अगर (include_plid) अणु
		put_unaligned_le16(plid, pos);
		pos += 2;
	पूर्ण
	अगर (action == WLAN_SP_MESH_PEERING_CLOSE) अणु
		put_unaligned_le16(reason, pos);
		pos += 2;
	पूर्ण

	अगर (action != WLAN_SP_MESH_PEERING_CLOSE) अणु
		अगर (mesh_add_ht_cap_ie(sdata, skb) ||
		    mesh_add_ht_oper_ie(sdata, skb) ||
		    mesh_add_vht_cap_ie(sdata, skb) ||
		    mesh_add_vht_oper_ie(sdata, skb) ||
		    mesh_add_he_cap_ie(sdata, skb, ie_len_he_cap) ||
		    mesh_add_he_oper_ie(sdata, skb) ||
		    mesh_add_he_6ghz_cap_ie(sdata, skb))
			जाओ मुक्त;
	पूर्ण

	अगर (mesh_add_venकरोr_ies(sdata, skb))
		जाओ मुक्त;

	ieee80211_tx_skb(sdata, skb);
	वापस 0;
मुक्त:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

/**
 * __mesh_plink_deactivate - deactivate mesh peer link
 *
 * @sta: mesh peer link to deactivate
 *
 * Mesh paths with this peer as next hop should be flushed
 * by the caller outside of plink_lock.
 *
 * Returns beacon changed flag अगर the beacon content changed.
 *
 * Locking: the caller must hold sta->mesh->plink_lock
 */
अटल u32 __mesh_plink_deactivate(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	u32 changed = 0;

	lockdep_निश्चित_held(&sta->mesh->plink_lock);

	अगर (sta->mesh->plink_state == NL80211_PLINK_ESTAB)
		changed = mesh_plink_dec_estab_count(sdata);
	sta->mesh->plink_state = NL80211_PLINK_BLOCKED;

	ieee80211_mps_sta_status_update(sta);
	changed |= ieee80211_mps_set_sta_local_pm(sta,
			NL80211_MESH_POWER_UNKNOWN);

	वापस changed;
पूर्ण

/**
 * mesh_plink_deactivate - deactivate mesh peer link
 *
 * @sta: mesh peer link to deactivate
 *
 * All mesh paths with this peer as next hop will be flushed
 */
u32 mesh_plink_deactivate(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	u32 changed;

	spin_lock_bh(&sta->mesh->plink_lock);
	changed = __mesh_plink_deactivate(sta);

	अगर (!sdata->u.mesh.user_mpm) अणु
		sta->mesh->reason = WLAN_REASON_MESH_PEER_CANCELED;
		mesh_plink_frame_tx(sdata, sta, WLAN_SP_MESH_PEERING_CLOSE,
				    sta->sta.addr, sta->mesh->llid,
				    sta->mesh->plid, sta->mesh->reason);
	पूर्ण
	spin_unlock_bh(&sta->mesh->plink_lock);
	अगर (!sdata->u.mesh.user_mpm)
		del_समयr_sync(&sta->mesh->plink_समयr);
	mesh_path_flush_by_nexthop(sta);

	/* make sure no पढ़ोers can access nexthop sta from here on */
	synchronize_net();

	वापस changed;
पूर्ण

अटल व्योम mesh_sta_info_init(काष्ठा ieee80211_sub_अगर_data *sdata,
			       काष्ठा sta_info *sta,
			       काष्ठा ieee802_11_elems *elems)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_supported_band *sband;
	u32 rates, basic_rates = 0, changed = 0;
	क्रमागत ieee80211_sta_rx_bandwidth bw = sta->sta.bandwidth;

	sband = ieee80211_get_sband(sdata);
	अगर (!sband)
		वापस;

	rates = ieee80211_sta_get_rates(sdata, elems, sband->band,
					&basic_rates);

	spin_lock_bh(&sta->mesh->plink_lock);
	sta->rx_stats.last_rx = jअगरfies;

	/* rates and capabilities करोn't change during peering */
	अगर (sta->mesh->plink_state == NL80211_PLINK_ESTAB &&
	    sta->mesh->processed_beacon)
		जाओ out;
	sta->mesh->processed_beacon = true;

	अगर (sta->sta.supp_rates[sband->band] != rates)
		changed |= IEEE80211_RC_SUPP_RATES_CHANGED;
	sta->sta.supp_rates[sband->band] = rates;

	अगर (ieee80211_ht_cap_ie_to_sta_ht_cap(sdata, sband,
					      elems->ht_cap_elem, sta))
		changed |= IEEE80211_RC_BW_CHANGED;

	ieee80211_vht_cap_ie_to_sta_vht_cap(sdata, sband,
					    elems->vht_cap_elem, sta);

	ieee80211_he_cap_ie_to_sta_he_cap(sdata, sband, elems->he_cap,
					  elems->he_cap_len,
					  elems->he_6ghz_capa,
					  sta);

	अगर (bw != sta->sta.bandwidth)
		changed |= IEEE80211_RC_BW_CHANGED;

	/* HT peer is operating 20MHz-only */
	अगर (elems->ht_operation &&
	    !(elems->ht_operation->ht_param &
	      IEEE80211_HT_PARAM_CHAN_WIDTH_ANY)) अणु
		अगर (sta->sta.bandwidth != IEEE80211_STA_RX_BW_20)
			changed |= IEEE80211_RC_BW_CHANGED;
		sta->sta.bandwidth = IEEE80211_STA_RX_BW_20;
	पूर्ण

	अगर (!test_sta_flag(sta, WLAN_STA_RATE_CONTROL))
		rate_control_rate_init(sta);
	अन्यथा
		rate_control_rate_update(local, sband, sta, changed);
out:
	spin_unlock_bh(&sta->mesh->plink_lock);
पूर्ण

अटल पूर्णांक mesh_allocate_aid(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा sta_info *sta;
	अचिन्हित दीर्घ *aid_map;
	पूर्णांक aid;

	aid_map = kसुस्मृति(BITS_TO_LONGS(IEEE80211_MAX_AID + 1),
			  माप(*aid_map), GFP_KERNEL);
	अगर (!aid_map)
		वापस -ENOMEM;

	/* reserve aid 0 क्रम mcast indication */
	__set_bit(0, aid_map);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sta, &sdata->local->sta_list, list)
		__set_bit(sta->sta.aid, aid_map);
	rcu_पढ़ो_unlock();

	aid = find_first_zero_bit(aid_map, IEEE80211_MAX_AID + 1);
	kमुक्त(aid_map);

	अगर (aid > IEEE80211_MAX_AID)
		वापस -ENOBUFS;

	वापस aid;
पूर्ण

अटल काष्ठा sta_info *
__mesh_sta_info_alloc(काष्ठा ieee80211_sub_अगर_data *sdata, u8 *hw_addr)
अणु
	काष्ठा sta_info *sta;
	पूर्णांक aid;

	अगर (sdata->local->num_sta >= MESH_MAX_PLINKS)
		वापस शून्य;

	aid = mesh_allocate_aid(sdata);
	अगर (aid < 0)
		वापस शून्य;

	sta = sta_info_alloc(sdata, hw_addr, GFP_KERNEL);
	अगर (!sta)
		वापस शून्य;

	sta->mesh->plink_state = NL80211_PLINK_LISTEN;
	sta->sta.wme = true;
	sta->sta.aid = aid;

	sta_info_pre_move_state(sta, IEEE80211_STA_AUTH);
	sta_info_pre_move_state(sta, IEEE80211_STA_ASSOC);
	sta_info_pre_move_state(sta, IEEE80211_STA_AUTHORIZED);

	वापस sta;
पूर्ण

अटल काष्ठा sta_info *
mesh_sta_info_alloc(काष्ठा ieee80211_sub_अगर_data *sdata, u8 *addr,
		    काष्ठा ieee802_11_elems *elems,
		    काष्ठा ieee80211_rx_status *rx_status)
अणु
	काष्ठा sta_info *sta = शून्य;

	/* Userspace handles station allocation */
	अगर (sdata->u.mesh.user_mpm ||
	    sdata->u.mesh.security & IEEE80211_MESH_SEC_AUTHED) अणु
		अगर (mesh_peer_accepts_plinks(elems) &&
		    mesh_plink_availables(sdata)) अणु
			पूर्णांक sig = 0;

			अगर (ieee80211_hw_check(&sdata->local->hw, SIGNAL_DBM))
				sig = rx_status->संकेत;

			cfg80211_notअगरy_new_peer_candidate(sdata->dev, addr,
							   elems->ie_start,
							   elems->total_len,
							   sig, GFP_KERNEL);
		पूर्ण
	पूर्ण अन्यथा
		sta = __mesh_sta_info_alloc(sdata, addr);

	वापस sta;
पूर्ण

/*
 * mesh_sta_info_get - वापस mesh sta info entry क्रम @addr.
 *
 * @sdata: local meshअगर
 * @addr: peer's address
 * @elems: IEs from beacon or mesh peering frame.
 * @rx_status: rx status क्रम the frame क्रम संकेत reporting
 *
 * Return existing or newly allocated sta_info under RCU पढ़ो lock.
 * (re)initialize with given IEs.
 */
अटल काष्ठा sta_info *
mesh_sta_info_get(काष्ठा ieee80211_sub_अगर_data *sdata,
		  u8 *addr, काष्ठा ieee802_11_elems *elems,
		  काष्ठा ieee80211_rx_status *rx_status) __acquires(RCU)
अणु
	काष्ठा sta_info *sta = शून्य;

	rcu_पढ़ो_lock();
	sta = sta_info_get(sdata, addr);
	अगर (sta) अणु
		mesh_sta_info_init(sdata, sta, elems);
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_unlock();
		/* can't run atomic */
		sta = mesh_sta_info_alloc(sdata, addr, elems, rx_status);
		अगर (!sta) अणु
			rcu_पढ़ो_lock();
			वापस शून्य;
		पूर्ण

		mesh_sta_info_init(sdata, sta, elems);

		अगर (sta_info_insert_rcu(sta))
			वापस शून्य;
	पूर्ण

	वापस sta;
पूर्ण

/*
 * mesh_neighbour_update - update or initialize new mesh neighbor.
 *
 * @sdata: local meshअगर
 * @addr: peer's address
 * @elems: IEs from beacon or mesh peering frame
 * @rx_status: rx status क्रम the frame क्रम संकेत reporting
 *
 * Initiates peering अगर appropriate.
 */
व्योम mesh_neighbour_update(काष्ठा ieee80211_sub_अगर_data *sdata,
			   u8 *hw_addr,
			   काष्ठा ieee802_11_elems *elems,
			   काष्ठा ieee80211_rx_status *rx_status)
अणु
	काष्ठा sta_info *sta;
	u32 changed = 0;

	sta = mesh_sta_info_get(sdata, hw_addr, elems, rx_status);
	अगर (!sta)
		जाओ out;

	sta->mesh->connected_to_gate = elems->mesh_config->meshconf_क्रमm &
		IEEE80211_MESHCONF_FORM_CONNECTED_TO_GATE;

	अगर (mesh_peer_accepts_plinks(elems) &&
	    sta->mesh->plink_state == NL80211_PLINK_LISTEN &&
	    sdata->u.mesh.accepting_plinks &&
	    sdata->u.mesh.mshcfg.स्वतः_खोलो_plinks &&
	    rssi_threshold_check(sdata, sta))
		changed = mesh_plink_खोलो(sta);

	ieee80211_mps_frame_release(sta, elems);
out:
	rcu_पढ़ो_unlock();
	ieee80211_mbss_info_change_notअगरy(sdata, changed);
पूर्ण

व्योम mesh_plink_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा mesh_sta *mesh = from_समयr(mesh, t, plink_समयr);
	काष्ठा sta_info *sta;
	u16 reason = 0;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा mesh_config *mshcfg;
	क्रमागत ieee80211_self_रक्षित_actioncode action = 0;

	/*
	 * This STA is valid because sta_info_destroy() will
	 * del_समयr_sync() this समयr after having made sure
	 * it cannot be पढ़ोded (by deleting the plink.)
	 */
	sta = mesh->plink_sta;

	अगर (sta->sdata->local->quiescing)
		वापस;

	spin_lock_bh(&sta->mesh->plink_lock);

	/* If a समयr fires just beक्रमe a state transition on another CPU,
	 * we may have alपढ़ोy extended the समयout and changed state by the
	 * समय we've acquired the lock and arrived  here.  In that हाल,
	 * skip this समयr and रुको क्रम the new one.
	 */
	अगर (समय_beक्रमe(jअगरfies, sta->mesh->plink_समयr.expires)) अणु
		mpl_dbg(sta->sdata,
			"Ignoring timer for %pM in state %s (timer adjusted)",
			sta->sta.addr, mplstates[sta->mesh->plink_state]);
		spin_unlock_bh(&sta->mesh->plink_lock);
		वापस;
	पूर्ण

	/* del_समयr() and handler may race when entering these states */
	अगर (sta->mesh->plink_state == NL80211_PLINK_LISTEN ||
	    sta->mesh->plink_state == NL80211_PLINK_ESTAB) अणु
		mpl_dbg(sta->sdata,
			"Ignoring timer for %pM in state %s (timer deleted)",
			sta->sta.addr, mplstates[sta->mesh->plink_state]);
		spin_unlock_bh(&sta->mesh->plink_lock);
		वापस;
	पूर्ण

	mpl_dbg(sta->sdata,
		"Mesh plink timer for %pM fired on state %s\n",
		sta->sta.addr, mplstates[sta->mesh->plink_state]);
	sdata = sta->sdata;
	mshcfg = &sdata->u.mesh.mshcfg;

	चयन (sta->mesh->plink_state) अणु
	हाल NL80211_PLINK_OPN_RCVD:
	हाल NL80211_PLINK_OPN_SNT:
		/* retry समयr */
		अगर (sta->mesh->plink_retries < mshcfg->करोt11MeshMaxRetries) अणु
			u32 अक्रम;
			mpl_dbg(sta->sdata,
				"Mesh plink for %pM (retry, timeout): %d %d\n",
				sta->sta.addr, sta->mesh->plink_retries,
				sta->mesh->plink_समयout);
			get_अक्रमom_bytes(&अक्रम, माप(u32));
			sta->mesh->plink_समयout = sta->mesh->plink_समयout +
					     अक्रम % sta->mesh->plink_समयout;
			++sta->mesh->plink_retries;
			mod_plink_समयr(sta, sta->mesh->plink_समयout);
			action = WLAN_SP_MESH_PEERING_OPEN;
			अवरोध;
		पूर्ण
		reason = WLAN_REASON_MESH_MAX_RETRIES;
		fallthrough;
	हाल NL80211_PLINK_CNF_RCVD:
		/* confirm समयr */
		अगर (!reason)
			reason = WLAN_REASON_MESH_CONFIRM_TIMEOUT;
		sta->mesh->plink_state = NL80211_PLINK_HOLDING;
		mod_plink_समयr(sta, mshcfg->करोt11MeshHoldingTimeout);
		action = WLAN_SP_MESH_PEERING_CLOSE;
		अवरोध;
	हाल NL80211_PLINK_HOLDING:
		/* holding समयr */
		del_समयr(&sta->mesh->plink_समयr);
		mesh_plink_fsm_restart(sta);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	spin_unlock_bh(&sta->mesh->plink_lock);
	अगर (action)
		mesh_plink_frame_tx(sdata, sta, action, sta->sta.addr,
				    sta->mesh->llid, sta->mesh->plid, reason);
पूर्ण

अटल अंतरभूत व्योम mesh_plink_समयr_set(काष्ठा sta_info *sta, u32 समयout)
अणु
	sta->mesh->plink_समयout = समयout;
	mod_समयr(&sta->mesh->plink_समयr, jअगरfies + msecs_to_jअगरfies(समयout));
पूर्ण

अटल bool llid_in_use(काष्ठा ieee80211_sub_अगर_data *sdata,
			u16 llid)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	bool in_use = false;
	काष्ठा sta_info *sta;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sta, &local->sta_list, list) अणु
		अगर (sdata != sta->sdata)
			जारी;

		अगर (!स_भेद(&sta->mesh->llid, &llid, माप(llid))) अणु
			in_use = true;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस in_use;
पूर्ण

अटल u16 mesh_get_new_llid(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	u16 llid;

	करो अणु
		get_अक्रमom_bytes(&llid, माप(llid));
	पूर्ण जबतक (llid_in_use(sdata, llid));

	वापस llid;
पूर्ण

u32 mesh_plink_खोलो(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	u32 changed;

	अगर (!test_sta_flag(sta, WLAN_STA_AUTH))
		वापस 0;

	spin_lock_bh(&sta->mesh->plink_lock);
	sta->mesh->llid = mesh_get_new_llid(sdata);
	अगर (sta->mesh->plink_state != NL80211_PLINK_LISTEN &&
	    sta->mesh->plink_state != NL80211_PLINK_BLOCKED) अणु
		spin_unlock_bh(&sta->mesh->plink_lock);
		वापस 0;
	पूर्ण
	sta->mesh->plink_state = NL80211_PLINK_OPN_SNT;
	mesh_plink_समयr_set(sta, sdata->u.mesh.mshcfg.करोt11MeshRetryTimeout);
	spin_unlock_bh(&sta->mesh->plink_lock);
	mpl_dbg(sdata,
		"Mesh plink: starting establishment with %pM\n",
		sta->sta.addr);

	/* set the non-peer mode to active during peering */
	changed = ieee80211_mps_local_status_update(sdata);

	mesh_plink_frame_tx(sdata, sta, WLAN_SP_MESH_PEERING_OPEN,
			    sta->sta.addr, sta->mesh->llid, 0, 0);
	वापस changed;
पूर्ण

u32 mesh_plink_block(काष्ठा sta_info *sta)
अणु
	u32 changed;

	spin_lock_bh(&sta->mesh->plink_lock);
	changed = __mesh_plink_deactivate(sta);
	sta->mesh->plink_state = NL80211_PLINK_BLOCKED;
	spin_unlock_bh(&sta->mesh->plink_lock);
	mesh_path_flush_by_nexthop(sta);

	वापस changed;
पूर्ण

अटल व्योम mesh_plink_बंद(काष्ठा ieee80211_sub_अगर_data *sdata,
			     काष्ठा sta_info *sta,
			     क्रमागत plink_event event)
अणु
	काष्ठा mesh_config *mshcfg = &sdata->u.mesh.mshcfg;
	u16 reason = (event == CLS_ACPT) ?
		     WLAN_REASON_MESH_CLOSE : WLAN_REASON_MESH_CONFIG;

	sta->mesh->reason = reason;
	sta->mesh->plink_state = NL80211_PLINK_HOLDING;
	mod_plink_समयr(sta, mshcfg->करोt11MeshHoldingTimeout);
पूर्ण

अटल u32 mesh_plink_establish(काष्ठा ieee80211_sub_अगर_data *sdata,
				काष्ठा sta_info *sta)
अणु
	काष्ठा mesh_config *mshcfg = &sdata->u.mesh.mshcfg;
	u32 changed = 0;

	del_समयr(&sta->mesh->plink_समयr);
	sta->mesh->plink_state = NL80211_PLINK_ESTAB;
	changed |= mesh_plink_inc_estab_count(sdata);
	changed |= mesh_set_ht_prot_mode(sdata);
	changed |= mesh_set_लघु_slot_समय(sdata);
	mpl_dbg(sdata, "Mesh plink with %pM ESTABLISHED\n", sta->sta.addr);
	ieee80211_mps_sta_status_update(sta);
	changed |= ieee80211_mps_set_sta_local_pm(sta, mshcfg->घातer_mode);
	वापस changed;
पूर्ण

/**
 * mesh_plink_fsm - step @sta MPM based on @event
 *
 * @sdata: पूर्णांकerface
 * @sta: mesh neighbor
 * @event: peering event
 *
 * Return: changed MBSS flags
 */
अटल u32 mesh_plink_fsm(काष्ठा ieee80211_sub_अगर_data *sdata,
			  काष्ठा sta_info *sta, क्रमागत plink_event event)
अणु
	काष्ठा mesh_config *mshcfg = &sdata->u.mesh.mshcfg;
	क्रमागत ieee80211_self_रक्षित_actioncode action = 0;
	u32 changed = 0;
	bool flush = false;

	mpl_dbg(sdata, "peer %pM in state %s got event %s\n", sta->sta.addr,
		mplstates[sta->mesh->plink_state], mplevents[event]);

	spin_lock_bh(&sta->mesh->plink_lock);
	चयन (sta->mesh->plink_state) अणु
	हाल NL80211_PLINK_LISTEN:
		चयन (event) अणु
		हाल CLS_ACPT:
			mesh_plink_fsm_restart(sta);
			अवरोध;
		हाल OPN_ACPT:
			sta->mesh->plink_state = NL80211_PLINK_OPN_RCVD;
			sta->mesh->llid = mesh_get_new_llid(sdata);
			mesh_plink_समयr_set(sta,
					     mshcfg->करोt11MeshRetryTimeout);

			/* set the non-peer mode to active during peering */
			changed |= ieee80211_mps_local_status_update(sdata);
			action = WLAN_SP_MESH_PEERING_OPEN;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल NL80211_PLINK_OPN_SNT:
		चयन (event) अणु
		हाल OPN_RJCT:
		हाल CNF_RJCT:
		हाल CLS_ACPT:
			mesh_plink_बंद(sdata, sta, event);
			action = WLAN_SP_MESH_PEERING_CLOSE;
			अवरोध;
		हाल OPN_ACPT:
			/* retry समयr is left untouched */
			sta->mesh->plink_state = NL80211_PLINK_OPN_RCVD;
			action = WLAN_SP_MESH_PEERING_CONFIRM;
			अवरोध;
		हाल CNF_ACPT:
			sta->mesh->plink_state = NL80211_PLINK_CNF_RCVD;
			mod_plink_समयr(sta, mshcfg->करोt11MeshConfirmTimeout);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल NL80211_PLINK_OPN_RCVD:
		चयन (event) अणु
		हाल OPN_RJCT:
		हाल CNF_RJCT:
		हाल CLS_ACPT:
			mesh_plink_बंद(sdata, sta, event);
			action = WLAN_SP_MESH_PEERING_CLOSE;
			अवरोध;
		हाल OPN_ACPT:
			action = WLAN_SP_MESH_PEERING_CONFIRM;
			अवरोध;
		हाल CNF_ACPT:
			changed |= mesh_plink_establish(sdata, sta);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल NL80211_PLINK_CNF_RCVD:
		चयन (event) अणु
		हाल OPN_RJCT:
		हाल CNF_RJCT:
		हाल CLS_ACPT:
			mesh_plink_बंद(sdata, sta, event);
			action = WLAN_SP_MESH_PEERING_CLOSE;
			अवरोध;
		हाल OPN_ACPT:
			changed |= mesh_plink_establish(sdata, sta);
			action = WLAN_SP_MESH_PEERING_CONFIRM;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल NL80211_PLINK_ESTAB:
		चयन (event) अणु
		हाल CLS_ACPT:
			changed |= __mesh_plink_deactivate(sta);
			changed |= mesh_set_ht_prot_mode(sdata);
			changed |= mesh_set_लघु_slot_समय(sdata);
			mesh_plink_बंद(sdata, sta, event);
			action = WLAN_SP_MESH_PEERING_CLOSE;
			flush = true;
			अवरोध;
		हाल OPN_ACPT:
			action = WLAN_SP_MESH_PEERING_CONFIRM;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल NL80211_PLINK_HOLDING:
		चयन (event) अणु
		हाल CLS_ACPT:
			del_समयr(&sta->mesh->plink_समयr);
			mesh_plink_fsm_restart(sta);
			अवरोध;
		हाल OPN_ACPT:
		हाल CNF_ACPT:
		हाल OPN_RJCT:
		हाल CNF_RJCT:
			action = WLAN_SP_MESH_PEERING_CLOSE;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		/* should not get here, PLINK_BLOCKED is dealt with at the
		 * beginning of the function
		 */
		अवरोध;
	पूर्ण
	spin_unlock_bh(&sta->mesh->plink_lock);
	अगर (flush)
		mesh_path_flush_by_nexthop(sta);
	अगर (action) अणु
		mesh_plink_frame_tx(sdata, sta, action, sta->sta.addr,
				    sta->mesh->llid, sta->mesh->plid,
				    sta->mesh->reason);

		/* also send confirm in खोलो हाल */
		अगर (action == WLAN_SP_MESH_PEERING_OPEN) अणु
			mesh_plink_frame_tx(sdata, sta,
					    WLAN_SP_MESH_PEERING_CONFIRM,
					    sta->sta.addr, sta->mesh->llid,
					    sta->mesh->plid, 0);
		पूर्ण
	पूर्ण

	वापस changed;
पूर्ण

/*
 * mesh_plink_get_event - get correct MPM event
 *
 * @sdata: पूर्णांकerface
 * @sta: peer, leave शून्य अगर processing a frame from a new suitable peer
 * @elems: peering management IEs
 * @ftype: frame type
 * @llid: peer's peer link ID
 * @plid: peer's local link ID
 *
 * Return: new peering event क्रम @sta, but PLINK_UNDEFINED should be treated as
 * an error.
 */
अटल क्रमागत plink_event
mesh_plink_get_event(काष्ठा ieee80211_sub_अगर_data *sdata,
		     काष्ठा sta_info *sta,
		     काष्ठा ieee802_11_elems *elems,
		     क्रमागत ieee80211_self_रक्षित_actioncode ftype,
		     u16 llid, u16 plid)
अणु
	क्रमागत plink_event event = PLINK_UNDEFINED;
	u8 ie_len = elems->peering_len;
	bool matches_local;

	matches_local = (ftype == WLAN_SP_MESH_PEERING_CLOSE ||
			 mesh_matches_local(sdata, elems));

	/* deny खोलो request from non-matching peer */
	अगर (!matches_local && !sta) अणु
		event = OPN_RJCT;
		जाओ out;
	पूर्ण

	अगर (!sta) अणु
		अगर (ftype != WLAN_SP_MESH_PEERING_OPEN) अणु
			mpl_dbg(sdata, "Mesh plink: cls or cnf from unknown peer\n");
			जाओ out;
		पूर्ण
		/* ftype == WLAN_SP_MESH_PEERING_OPEN */
		अगर (!mesh_plink_मुक्त_count(sdata)) अणु
			mpl_dbg(sdata, "Mesh plink error: no more free plinks\n");
			जाओ out;
		पूर्ण

		/* new matching peer */
		event = OPN_ACPT;
		जाओ out;
	पूर्ण अन्यथा अणु
		अगर (!test_sta_flag(sta, WLAN_STA_AUTH)) अणु
			mpl_dbg(sdata, "Mesh plink: Action frame from non-authed peer\n");
			जाओ out;
		पूर्ण
		अगर (sta->mesh->plink_state == NL80211_PLINK_BLOCKED)
			जाओ out;
	पूर्ण

	चयन (ftype) अणु
	हाल WLAN_SP_MESH_PEERING_OPEN:
		अगर (!matches_local)
			event = OPN_RJCT;
		अगर (!mesh_plink_मुक्त_count(sdata) ||
		    (sta->mesh->plid && sta->mesh->plid != plid))
			event = OPN_IGNR;
		अन्यथा
			event = OPN_ACPT;
		अवरोध;
	हाल WLAN_SP_MESH_PEERING_CONFIRM:
		अगर (!matches_local)
			event = CNF_RJCT;
		अगर (!mesh_plink_मुक्त_count(sdata) ||
		    sta->mesh->llid != llid ||
		    (sta->mesh->plid && sta->mesh->plid != plid))
			event = CNF_IGNR;
		अन्यथा
			event = CNF_ACPT;
		अवरोध;
	हाल WLAN_SP_MESH_PEERING_CLOSE:
		अगर (sta->mesh->plink_state == NL80211_PLINK_ESTAB)
			/* Do not check क्रम llid or plid. This करोes not
			 * follow the standard but since multiple plinks
			 * per sta are not supported, it is necessary in
			 * order to aव्योम a livelock when MP A sees an
			 * establish peer link to MP B but MP B करोes not
			 * see it. This can be caused by a समयout in
			 * B's peer link establishment or B beign
			 * restarted.
			 */
			event = CLS_ACPT;
		अन्यथा अगर (sta->mesh->plid != plid)
			event = CLS_IGNR;
		अन्यथा अगर (ie_len == 8 && sta->mesh->llid != llid)
			event = CLS_IGNR;
		अन्यथा
			event = CLS_ACPT;
		अवरोध;
	शेष:
		mpl_dbg(sdata, "Mesh plink: unknown frame subtype\n");
		अवरोध;
	पूर्ण

out:
	वापस event;
पूर्ण

अटल व्योम
mesh_process_plink_frame(काष्ठा ieee80211_sub_अगर_data *sdata,
			 काष्ठा ieee80211_mgmt *mgmt,
			 काष्ठा ieee802_11_elems *elems,
			 काष्ठा ieee80211_rx_status *rx_status)
अणु

	काष्ठा sta_info *sta;
	क्रमागत plink_event event;
	क्रमागत ieee80211_self_रक्षित_actioncode ftype;
	u32 changed = 0;
	u8 ie_len = elems->peering_len;
	u16 plid, llid = 0;

	अगर (!elems->peering) अणु
		mpl_dbg(sdata,
			"Mesh plink: missing necessary peer link ie\n");
		वापस;
	पूर्ण

	अगर (elems->rsn_len &&
	    sdata->u.mesh.security == IEEE80211_MESH_SEC_NONE) अणु
		mpl_dbg(sdata,
			"Mesh plink: can't establish link with secure peer\n");
		वापस;
	पूर्ण

	ftype = mgmt->u.action.u.self_prot.action_code;
	अगर ((ftype == WLAN_SP_MESH_PEERING_OPEN && ie_len != 4) ||
	    (ftype == WLAN_SP_MESH_PEERING_CONFIRM && ie_len != 6) ||
	    (ftype == WLAN_SP_MESH_PEERING_CLOSE && ie_len != 6
							&& ie_len != 8)) अणु
		mpl_dbg(sdata,
			"Mesh plink: incorrect plink ie length %d %d\n",
			ftype, ie_len);
		वापस;
	पूर्ण

	अगर (ftype != WLAN_SP_MESH_PEERING_CLOSE &&
	    (!elems->mesh_id || !elems->mesh_config)) अणु
		mpl_dbg(sdata, "Mesh plink: missing necessary ie\n");
		वापस;
	पूर्ण
	/* Note the lines below are correct, the llid in the frame is the plid
	 * from the poपूर्णांक of view of this host.
	 */
	plid = get_unaligned_le16(PLINK_GET_LLID(elems->peering));
	अगर (ftype == WLAN_SP_MESH_PEERING_CONFIRM ||
	    (ftype == WLAN_SP_MESH_PEERING_CLOSE && ie_len == 8))
		llid = get_unaligned_le16(PLINK_GET_PLID(elems->peering));

	/* WARNING: Only क्रम sta poपूर्णांकer, is dropped & re-acquired */
	rcu_पढ़ो_lock();

	sta = sta_info_get(sdata, mgmt->sa);

	अगर (ftype == WLAN_SP_MESH_PEERING_OPEN &&
	    !rssi_threshold_check(sdata, sta)) अणु
		mpl_dbg(sdata, "Mesh plink: %pM does not meet rssi threshold\n",
			mgmt->sa);
		जाओ unlock_rcu;
	पूर्ण

	/* Now we will figure out the appropriate event... */
	event = mesh_plink_get_event(sdata, sta, elems, ftype, llid, plid);

	अगर (event == OPN_ACPT) अणु
		rcu_पढ़ो_unlock();
		/* allocate sta entry अगर necessary and update info */
		sta = mesh_sta_info_get(sdata, mgmt->sa, elems, rx_status);
		अगर (!sta) अणु
			mpl_dbg(sdata, "Mesh plink: failed to init peer!\n");
			जाओ unlock_rcu;
		पूर्ण
		sta->mesh->plid = plid;
	पूर्ण अन्यथा अगर (!sta && event == OPN_RJCT) अणु
		mesh_plink_frame_tx(sdata, शून्य, WLAN_SP_MESH_PEERING_CLOSE,
				    mgmt->sa, 0, plid,
				    WLAN_REASON_MESH_CONFIG);
		जाओ unlock_rcu;
	पूर्ण अन्यथा अगर (!sta || event == PLINK_UNDEFINED) अणु
		/* something went wrong */
		जाओ unlock_rcu;
	पूर्ण

	अगर (event == CNF_ACPT) अणु
		/* 802.11-2012 13.3.7.2 - update plid on CNF अगर not set */
		अगर (!sta->mesh->plid)
			sta->mesh->plid = plid;

		sta->mesh->aid = get_unaligned_le16(PLINK_CNF_AID(mgmt));
	पूर्ण

	changed |= mesh_plink_fsm(sdata, sta, event);

unlock_rcu:
	rcu_पढ़ो_unlock();

	अगर (changed)
		ieee80211_mbss_info_change_notअगरy(sdata, changed);
पूर्ण

व्योम mesh_rx_plink_frame(काष्ठा ieee80211_sub_अगर_data *sdata,
			 काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len,
			 काष्ठा ieee80211_rx_status *rx_status)
अणु
	काष्ठा ieee802_11_elems elems;
	माप_प्रकार baselen;
	u8 *baseaddr;

	/* need action_code, aux */
	अगर (len < IEEE80211_MIN_ACTION_SIZE + 3)
		वापस;

	अगर (sdata->u.mesh.user_mpm)
		/* userspace must रेजिस्टर क्रम these */
		वापस;

	अगर (is_multicast_ether_addr(mgmt->da)) अणु
		mpl_dbg(sdata,
			"Mesh plink: ignore frame from multicast address\n");
		वापस;
	पूर्ण

	baseaddr = mgmt->u.action.u.self_prot.variable;
	baselen = (u8 *) mgmt->u.action.u.self_prot.variable - (u8 *) mgmt;
	अगर (mgmt->u.action.u.self_prot.action_code ==
						WLAN_SP_MESH_PEERING_CONFIRM) अणु
		baseaddr += 4;
		baselen += 4;

		अगर (baselen > len)
			वापस;
	पूर्ण
	ieee802_11_parse_elems(baseaddr, len - baselen, true, &elems,
			       mgmt->bssid, शून्य);
	mesh_process_plink_frame(sdata, mgmt, &elems, rx_status);
पूर्ण
