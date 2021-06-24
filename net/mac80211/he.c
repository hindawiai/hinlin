<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HE handling
 *
 * Copyright(c) 2017 Intel Deutschland GmbH
 * Copyright(c) 2019 - 2020 Intel Corporation
 */

#समावेश "ieee80211_i.h"

अटल व्योम
ieee80211_update_from_he_6ghz_capa(स्थिर काष्ठा ieee80211_he_6ghz_capa *he_6ghz_capa,
				   काष्ठा sta_info *sta)
अणु
	क्रमागत ieee80211_smps_mode smps_mode;

	अगर (sta->sdata->vअगर.type == NL80211_IFTYPE_AP ||
	    sta->sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN) अणु
		चयन (le16_get_bits(he_6ghz_capa->capa,
				      IEEE80211_HE_6GHZ_CAP_SM_PS)) अणु
		हाल WLAN_HT_CAP_SM_PS_INVALID:
		हाल WLAN_HT_CAP_SM_PS_STATIC:
			smps_mode = IEEE80211_SMPS_STATIC;
			अवरोध;
		हाल WLAN_HT_CAP_SM_PS_DYNAMIC:
			smps_mode = IEEE80211_SMPS_DYNAMIC;
			अवरोध;
		हाल WLAN_HT_CAP_SM_PS_DISABLED:
			smps_mode = IEEE80211_SMPS_OFF;
			अवरोध;
		पूर्ण

		sta->sta.smps_mode = smps_mode;
	पूर्ण अन्यथा अणु
		sta->sta.smps_mode = IEEE80211_SMPS_OFF;
	पूर्ण

	चयन (le16_get_bits(he_6ghz_capa->capa,
			      IEEE80211_HE_6GHZ_CAP_MAX_MPDU_LEN)) अणु
	हाल IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454:
		sta->sta.max_amsdu_len = IEEE80211_MAX_MPDU_LEN_VHT_11454;
		अवरोध;
	हाल IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_7991:
		sta->sta.max_amsdu_len = IEEE80211_MAX_MPDU_LEN_VHT_7991;
		अवरोध;
	हाल IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_3895:
	शेष:
		sta->sta.max_amsdu_len = IEEE80211_MAX_MPDU_LEN_VHT_3895;
		अवरोध;
	पूर्ण

	sta->sta.he_6ghz_capa = *he_6ghz_capa;
पूर्ण

अटल व्योम ieee80211_he_mcs_disable(__le16 *he_mcs)
अणु
	u32 i;

	क्रम (i = 0; i < 8; i++)
		*he_mcs |= cpu_to_le16(IEEE80211_HE_MCS_NOT_SUPPORTED << i * 2);
पूर्ण

अटल व्योम ieee80211_he_mcs_पूर्णांकersection(__le16 *he_own_rx, __le16 *he_peer_rx,
					  __le16 *he_own_tx, __le16 *he_peer_tx)
अणु
	u32 i;
	u16 own_rx, own_tx, peer_rx, peer_tx;

	क्रम (i = 0; i < 8; i++) अणु
		own_rx = le16_to_cpu(*he_own_rx);
		own_rx = (own_rx >> i * 2) & IEEE80211_HE_MCS_NOT_SUPPORTED;

		own_tx = le16_to_cpu(*he_own_tx);
		own_tx = (own_tx >> i * 2) & IEEE80211_HE_MCS_NOT_SUPPORTED;

		peer_rx = le16_to_cpu(*he_peer_rx);
		peer_rx = (peer_rx >> i * 2) & IEEE80211_HE_MCS_NOT_SUPPORTED;

		peer_tx = le16_to_cpu(*he_peer_tx);
		peer_tx = (peer_tx >> i * 2) & IEEE80211_HE_MCS_NOT_SUPPORTED;

		अगर (peer_tx != IEEE80211_HE_MCS_NOT_SUPPORTED) अणु
			अगर (own_rx == IEEE80211_HE_MCS_NOT_SUPPORTED)
				peer_tx = IEEE80211_HE_MCS_NOT_SUPPORTED;
			अन्यथा अगर (own_rx < peer_tx)
				peer_tx = own_rx;
		पूर्ण

		अगर (peer_rx != IEEE80211_HE_MCS_NOT_SUPPORTED) अणु
			अगर (own_tx == IEEE80211_HE_MCS_NOT_SUPPORTED)
				peer_rx = IEEE80211_HE_MCS_NOT_SUPPORTED;
			अन्यथा अगर (own_tx < peer_rx)
				peer_rx = own_tx;
		पूर्ण

		*he_peer_rx &=
			~cpu_to_le16(IEEE80211_HE_MCS_NOT_SUPPORTED << i * 2);
		*he_peer_rx |= cpu_to_le16(peer_rx << i * 2);

		*he_peer_tx &=
			~cpu_to_le16(IEEE80211_HE_MCS_NOT_SUPPORTED << i * 2);
		*he_peer_tx |= cpu_to_le16(peer_tx << i * 2);
	पूर्ण
पूर्ण

व्योम
ieee80211_he_cap_ie_to_sta_he_cap(काष्ठा ieee80211_sub_अगर_data *sdata,
				  काष्ठा ieee80211_supported_band *sband,
				  स्थिर u8 *he_cap_ie, u8 he_cap_len,
				  स्थिर काष्ठा ieee80211_he_6ghz_capa *he_6ghz_capa,
				  काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sta_he_cap *he_cap = &sta->sta.he_cap;
	काष्ठा ieee80211_sta_he_cap own_he_cap = sband->अगरtype_data->he_cap;
	काष्ठा ieee80211_he_cap_elem *he_cap_ie_elem = (व्योम *)he_cap_ie;
	u8 he_ppe_size;
	u8 mcs_nss_size;
	u8 he_total_size;
	bool own_160, peer_160, own_80p80, peer_80p80;

	स_रखो(he_cap, 0, माप(*he_cap));

	अगर (!he_cap_ie || !ieee80211_get_he_sta_cap(sband))
		वापस;

	/* Make sure size is OK */
	mcs_nss_size = ieee80211_he_mcs_nss_size(he_cap_ie_elem);
	he_ppe_size =
		ieee80211_he_ppe_size(he_cap_ie[माप(he_cap->he_cap_elem) +
						mcs_nss_size],
				      he_cap_ie_elem->phy_cap_info);
	he_total_size = माप(he_cap->he_cap_elem) + mcs_nss_size +
			he_ppe_size;
	अगर (he_cap_len < he_total_size)
		वापस;

	स_नकल(&he_cap->he_cap_elem, he_cap_ie, माप(he_cap->he_cap_elem));

	/* HE Tx/Rx HE MCS NSS Support Field */
	स_नकल(&he_cap->he_mcs_nss_supp,
	       &he_cap_ie[माप(he_cap->he_cap_elem)], mcs_nss_size);

	/* Check अगर there are (optional) PPE Thresholds */
	अगर (he_cap->he_cap_elem.phy_cap_info[6] &
	    IEEE80211_HE_PHY_CAP6_PPE_THRESHOLD_PRESENT)
		स_नकल(he_cap->ppe_thres,
		       &he_cap_ie[माप(he_cap->he_cap_elem) + mcs_nss_size],
		       he_ppe_size);

	he_cap->has_he = true;

	sta->cur_max_bandwidth = ieee80211_sta_cap_rx_bw(sta);
	sta->sta.bandwidth = ieee80211_sta_cur_vht_bw(sta);

	अगर (sband->band == NL80211_BAND_6GHZ && he_6ghz_capa)
		ieee80211_update_from_he_6ghz_capa(he_6ghz_capa, sta);

	ieee80211_he_mcs_पूर्णांकersection(&own_he_cap.he_mcs_nss_supp.rx_mcs_80,
				      &he_cap->he_mcs_nss_supp.rx_mcs_80,
				      &own_he_cap.he_mcs_nss_supp.tx_mcs_80,
				      &he_cap->he_mcs_nss_supp.tx_mcs_80);

	own_160 = own_he_cap.he_cap_elem.phy_cap_info[0] &
		  IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G;
	peer_160 = he_cap->he_cap_elem.phy_cap_info[0] &
		   IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G;

	अगर (peer_160 && own_160) अणु
		ieee80211_he_mcs_पूर्णांकersection(&own_he_cap.he_mcs_nss_supp.rx_mcs_160,
					      &he_cap->he_mcs_nss_supp.rx_mcs_160,
					      &own_he_cap.he_mcs_nss_supp.tx_mcs_160,
					      &he_cap->he_mcs_nss_supp.tx_mcs_160);
	पूर्ण अन्यथा अगर (peer_160 && !own_160) अणु
		ieee80211_he_mcs_disable(&he_cap->he_mcs_nss_supp.rx_mcs_160);
		ieee80211_he_mcs_disable(&he_cap->he_mcs_nss_supp.tx_mcs_160);
		he_cap->he_cap_elem.phy_cap_info[0] &=
			~IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G;
	पूर्ण

	own_80p80 = own_he_cap.he_cap_elem.phy_cap_info[0] &
		    IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G;
	peer_80p80 = he_cap->he_cap_elem.phy_cap_info[0] &
		     IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G;

	अगर (peer_80p80 && own_80p80) अणु
		ieee80211_he_mcs_पूर्णांकersection(&own_he_cap.he_mcs_nss_supp.rx_mcs_80p80,
					      &he_cap->he_mcs_nss_supp.rx_mcs_80p80,
					      &own_he_cap.he_mcs_nss_supp.tx_mcs_80p80,
					      &he_cap->he_mcs_nss_supp.tx_mcs_80p80);
	पूर्ण अन्यथा अगर (peer_80p80 && !own_80p80) अणु
		ieee80211_he_mcs_disable(&he_cap->he_mcs_nss_supp.rx_mcs_80p80);
		ieee80211_he_mcs_disable(&he_cap->he_mcs_nss_supp.tx_mcs_80p80);
		he_cap->he_cap_elem.phy_cap_info[0] &=
			~IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G;
	पूर्ण
पूर्ण

व्योम
ieee80211_he_op_ie_to_bss_conf(काष्ठा ieee80211_vअगर *vअगर,
			स्थिर काष्ठा ieee80211_he_operation *he_op_ie)
अणु
	स_रखो(&vअगर->bss_conf.he_oper, 0, माप(vअगर->bss_conf.he_oper));
	अगर (!he_op_ie)
		वापस;

	vअगर->bss_conf.he_oper.params = __le32_to_cpu(he_op_ie->he_oper_params);
	vअगर->bss_conf.he_oper.nss_set = __le16_to_cpu(he_op_ie->he_mcs_nss_set);
पूर्ण

व्योम
ieee80211_he_spr_ie_to_bss_conf(काष्ठा ieee80211_vअगर *vअगर,
				स्थिर काष्ठा ieee80211_he_spr *he_spr_ie_elem)
अणु
	काष्ठा ieee80211_he_obss_pd *he_obss_pd =
					&vअगर->bss_conf.he_obss_pd;
	स्थिर u8 *data;

	स_रखो(he_obss_pd, 0, माप(*he_obss_pd));

	अगर (!he_spr_ie_elem)
		वापस;
	data = he_spr_ie_elem->optional;

	अगर (he_spr_ie_elem->he_sr_control &
	    IEEE80211_HE_SPR_NON_SRG_OFFSET_PRESENT)
		data++;
	अगर (he_spr_ie_elem->he_sr_control &
	    IEEE80211_HE_SPR_SRG_INFORMATION_PRESENT) अणु
		he_obss_pd->max_offset = *data++;
		he_obss_pd->min_offset = *data++;
		he_obss_pd->enable = true;
	पूर्ण
पूर्ण
