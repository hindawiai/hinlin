<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VHT handling
 *
 * Portions of this file
 * Copyright(c) 2015 - 2016 Intel Deutschland GmbH
 * Copyright (C) 2018 - 2020 Intel Corporation
 */

#समावेश <linux/ieee80211.h>
#समावेश <linux/export.h>
#समावेश <net/mac80211.h>
#समावेश "ieee80211_i.h"
#समावेश "rate.h"


अटल व्योम __check_vhtcap_disable(काष्ठा ieee80211_sub_अगर_data *sdata,
				   काष्ठा ieee80211_sta_vht_cap *vht_cap,
				   u32 flag)
अणु
	__le32 le_flag = cpu_to_le32(flag);

	अगर (sdata->u.mgd.vht_capa_mask.vht_cap_info & le_flag &&
	    !(sdata->u.mgd.vht_capa.vht_cap_info & le_flag))
		vht_cap->cap &= ~flag;
पूर्ण

व्योम ieee80211_apply_vhtcap_overrides(काष्ठा ieee80211_sub_अगर_data *sdata,
				      काष्ठा ieee80211_sta_vht_cap *vht_cap)
अणु
	पूर्णांक i;
	u16 rxmcs_mask, rxmcs_cap, rxmcs_n, txmcs_mask, txmcs_cap, txmcs_n;

	अगर (!vht_cap->vht_supported)
		वापस;

	अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION)
		वापस;

	__check_vhtcap_disable(sdata, vht_cap,
			       IEEE80211_VHT_CAP_RXLDPC);
	__check_vhtcap_disable(sdata, vht_cap,
			       IEEE80211_VHT_CAP_SHORT_GI_80);
	__check_vhtcap_disable(sdata, vht_cap,
			       IEEE80211_VHT_CAP_SHORT_GI_160);
	__check_vhtcap_disable(sdata, vht_cap,
			       IEEE80211_VHT_CAP_TXSTBC);
	__check_vhtcap_disable(sdata, vht_cap,
			       IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE);
	__check_vhtcap_disable(sdata, vht_cap,
			       IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE);
	__check_vhtcap_disable(sdata, vht_cap,
			       IEEE80211_VHT_CAP_RX_ANTENNA_PATTERN);
	__check_vhtcap_disable(sdata, vht_cap,
			       IEEE80211_VHT_CAP_TX_ANTENNA_PATTERN);

	/* Allow user to decrease AMPDU length exponent */
	अगर (sdata->u.mgd.vht_capa_mask.vht_cap_info &
	    cpu_to_le32(IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK)) अणु
		u32 cap, n;

		n = le32_to_cpu(sdata->u.mgd.vht_capa.vht_cap_info) &
			IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK;
		n >>= IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT;
		cap = vht_cap->cap & IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK;
		cap >>= IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT;

		अगर (n < cap) अणु
			vht_cap->cap &=
				~IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK;
			vht_cap->cap |=
				n << IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT;
		पूर्ण
	पूर्ण

	/* Allow the user to decrease MCSes */
	rxmcs_mask =
		le16_to_cpu(sdata->u.mgd.vht_capa_mask.supp_mcs.rx_mcs_map);
	rxmcs_n = le16_to_cpu(sdata->u.mgd.vht_capa.supp_mcs.rx_mcs_map);
	rxmcs_n &= rxmcs_mask;
	rxmcs_cap = le16_to_cpu(vht_cap->vht_mcs.rx_mcs_map);

	txmcs_mask =
		le16_to_cpu(sdata->u.mgd.vht_capa_mask.supp_mcs.tx_mcs_map);
	txmcs_n = le16_to_cpu(sdata->u.mgd.vht_capa.supp_mcs.tx_mcs_map);
	txmcs_n &= txmcs_mask;
	txmcs_cap = le16_to_cpu(vht_cap->vht_mcs.tx_mcs_map);
	क्रम (i = 0; i < 8; i++) अणु
		u8 m, n, c;

		m = (rxmcs_mask >> 2*i) & IEEE80211_VHT_MCS_NOT_SUPPORTED;
		n = (rxmcs_n >> 2*i) & IEEE80211_VHT_MCS_NOT_SUPPORTED;
		c = (rxmcs_cap >> 2*i) & IEEE80211_VHT_MCS_NOT_SUPPORTED;

		अगर (m && ((c != IEEE80211_VHT_MCS_NOT_SUPPORTED && n < c) ||
			  n == IEEE80211_VHT_MCS_NOT_SUPPORTED)) अणु
			rxmcs_cap &= ~(3 << 2*i);
			rxmcs_cap |= (rxmcs_n & (3 << 2*i));
		पूर्ण

		m = (txmcs_mask >> 2*i) & IEEE80211_VHT_MCS_NOT_SUPPORTED;
		n = (txmcs_n >> 2*i) & IEEE80211_VHT_MCS_NOT_SUPPORTED;
		c = (txmcs_cap >> 2*i) & IEEE80211_VHT_MCS_NOT_SUPPORTED;

		अगर (m && ((c != IEEE80211_VHT_MCS_NOT_SUPPORTED && n < c) ||
			  n == IEEE80211_VHT_MCS_NOT_SUPPORTED)) अणु
			txmcs_cap &= ~(3 << 2*i);
			txmcs_cap |= (txmcs_n & (3 << 2*i));
		पूर्ण
	पूर्ण
	vht_cap->vht_mcs.rx_mcs_map = cpu_to_le16(rxmcs_cap);
	vht_cap->vht_mcs.tx_mcs_map = cpu_to_le16(txmcs_cap);
पूर्ण

व्योम
ieee80211_vht_cap_ie_to_sta_vht_cap(काष्ठा ieee80211_sub_अगर_data *sdata,
				    काष्ठा ieee80211_supported_band *sband,
				    स्थिर काष्ठा ieee80211_vht_cap *vht_cap_ie,
				    काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sta_vht_cap *vht_cap = &sta->sta.vht_cap;
	काष्ठा ieee80211_sta_vht_cap own_cap;
	u32 cap_info, i;
	bool have_80mhz;

	स_रखो(vht_cap, 0, माप(*vht_cap));

	अगर (!sta->sta.ht_cap.ht_supported)
		वापस;

	अगर (!vht_cap_ie || !sband->vht_cap.vht_supported)
		वापस;

	/* Allow VHT अगर at least one channel on the sband supports 80 MHz */
	have_80mhz = false;
	क्रम (i = 0; i < sband->n_channels; i++) अणु
		अगर (sband->channels[i].flags & (IEEE80211_CHAN_DISABLED |
						IEEE80211_CHAN_NO_80MHZ))
			जारी;

		have_80mhz = true;
		अवरोध;
	पूर्ण

	अगर (!have_80mhz)
		वापस;

	/*
	 * A VHT STA must support 40 MHz, but अगर we verअगरy that here
	 * then we अवरोध a few things - some APs (e.g. Netgear R6300v2
	 * and others based on the BCM4360 chipset) will unset this
	 * capability bit when operating in 20 MHz.
	 */

	vht_cap->vht_supported = true;

	own_cap = sband->vht_cap;
	/*
	 * If user has specअगरied capability overrides, take care
	 * of that अगर the station we're setting up is the AP that
	 * we advertised a restricted capability set to. Override
	 * our own capabilities and then use those below.
	 */
	अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION &&
	    !test_sta_flag(sta, WLAN_STA_TDLS_PEER))
		ieee80211_apply_vhtcap_overrides(sdata, &own_cap);

	/* take some capabilities as-is */
	cap_info = le32_to_cpu(vht_cap_ie->vht_cap_info);
	vht_cap->cap = cap_info;
	vht_cap->cap &= IEEE80211_VHT_CAP_RXLDPC |
			IEEE80211_VHT_CAP_VHT_TXOP_PS |
			IEEE80211_VHT_CAP_HTC_VHT |
			IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK |
			IEEE80211_VHT_CAP_VHT_LINK_ADAPTATION_VHT_UNSOL_MFB |
			IEEE80211_VHT_CAP_VHT_LINK_ADAPTATION_VHT_MRQ_MFB |
			IEEE80211_VHT_CAP_RX_ANTENNA_PATTERN |
			IEEE80211_VHT_CAP_TX_ANTENNA_PATTERN;

	vht_cap->cap |= min_t(u32, cap_info & IEEE80211_VHT_CAP_MAX_MPDU_MASK,
			      own_cap.cap & IEEE80211_VHT_CAP_MAX_MPDU_MASK);

	/* and some based on our own capabilities */
	चयन (own_cap.cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK) अणु
	हाल IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ:
		vht_cap->cap |= cap_info &
				IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ;
		अवरोध;
	हाल IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ:
		vht_cap->cap |= cap_info &
				IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK;
		अवरोध;
	शेष:
		/* nothing */
		अवरोध;
	पूर्ण

	/* symmetric capabilities */
	vht_cap->cap |= cap_info & own_cap.cap &
			(IEEE80211_VHT_CAP_SHORT_GI_80 |
			 IEEE80211_VHT_CAP_SHORT_GI_160);

	/* reमुख्यing ones */
	अगर (own_cap.cap & IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE)
		vht_cap->cap |= cap_info &
				(IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE |
				 IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK);

	अगर (own_cap.cap & IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE)
		vht_cap->cap |= cap_info &
				(IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE |
				 IEEE80211_VHT_CAP_BEAMFORMEE_STS_MASK);

	अगर (own_cap.cap & IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE)
		vht_cap->cap |= cap_info &
				IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE;

	अगर (own_cap.cap & IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE)
		vht_cap->cap |= cap_info &
				IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE;

	अगर (own_cap.cap & IEEE80211_VHT_CAP_TXSTBC)
		vht_cap->cap |= cap_info & IEEE80211_VHT_CAP_RXSTBC_MASK;

	अगर (own_cap.cap & IEEE80211_VHT_CAP_RXSTBC_MASK)
		vht_cap->cap |= cap_info & IEEE80211_VHT_CAP_TXSTBC;

	/* Copy peer MCS info, the driver might need them. */
	स_नकल(&vht_cap->vht_mcs, &vht_cap_ie->supp_mcs,
	       माप(काष्ठा ieee80211_vht_mcs_info));

	/* copy EXT_NSS_BW Support value or हटाओ the capability */
	अगर (ieee80211_hw_check(&sdata->local->hw, SUPPORTS_VHT_EXT_NSS_BW))
		vht_cap->cap |= (cap_info & IEEE80211_VHT_CAP_EXT_NSS_BW_MASK);
	अन्यथा
		vht_cap->vht_mcs.tx_highest &=
			~cpu_to_le16(IEEE80211_VHT_EXT_NSS_BW_CAPABLE);

	/* but also restrict MCSes */
	क्रम (i = 0; i < 8; i++) अणु
		u16 own_rx, own_tx, peer_rx, peer_tx;

		own_rx = le16_to_cpu(own_cap.vht_mcs.rx_mcs_map);
		own_rx = (own_rx >> i * 2) & IEEE80211_VHT_MCS_NOT_SUPPORTED;

		own_tx = le16_to_cpu(own_cap.vht_mcs.tx_mcs_map);
		own_tx = (own_tx >> i * 2) & IEEE80211_VHT_MCS_NOT_SUPPORTED;

		peer_rx = le16_to_cpu(vht_cap->vht_mcs.rx_mcs_map);
		peer_rx = (peer_rx >> i * 2) & IEEE80211_VHT_MCS_NOT_SUPPORTED;

		peer_tx = le16_to_cpu(vht_cap->vht_mcs.tx_mcs_map);
		peer_tx = (peer_tx >> i * 2) & IEEE80211_VHT_MCS_NOT_SUPPORTED;

		अगर (peer_tx != IEEE80211_VHT_MCS_NOT_SUPPORTED) अणु
			अगर (own_rx == IEEE80211_VHT_MCS_NOT_SUPPORTED)
				peer_tx = IEEE80211_VHT_MCS_NOT_SUPPORTED;
			अन्यथा अगर (own_rx < peer_tx)
				peer_tx = own_rx;
		पूर्ण

		अगर (peer_rx != IEEE80211_VHT_MCS_NOT_SUPPORTED) अणु
			अगर (own_tx == IEEE80211_VHT_MCS_NOT_SUPPORTED)
				peer_rx = IEEE80211_VHT_MCS_NOT_SUPPORTED;
			अन्यथा अगर (own_tx < peer_rx)
				peer_rx = own_tx;
		पूर्ण

		vht_cap->vht_mcs.rx_mcs_map &=
			~cpu_to_le16(IEEE80211_VHT_MCS_NOT_SUPPORTED << i * 2);
		vht_cap->vht_mcs.rx_mcs_map |= cpu_to_le16(peer_rx << i * 2);

		vht_cap->vht_mcs.tx_mcs_map &=
			~cpu_to_le16(IEEE80211_VHT_MCS_NOT_SUPPORTED << i * 2);
		vht_cap->vht_mcs.tx_mcs_map |= cpu_to_le16(peer_tx << i * 2);
	पूर्ण

	/*
	 * This is a workaround क्रम VHT-enabled STAs which अवरोध the spec
	 * and have the VHT-MCS Rx map filled in with value 3 क्रम all eight
	 * spacial streams, an example is AR9462.
	 *
	 * As per spec, in section 22.1.1 Introduction to the VHT PHY
	 * A VHT STA shall support at least single spactial stream VHT-MCSs
	 * 0 to 7 (transmit and receive) in all supported channel widths.
	 */
	अगर (vht_cap->vht_mcs.rx_mcs_map == cpu_to_le16(0xFFFF)) अणु
		vht_cap->vht_supported = false;
		sdata_info(sdata, "Ignoring VHT IE from %pM due to invalid rx_mcs_map\n",
			   sta->addr);
		वापस;
	पूर्ण

	/* finally set up the bandwidth */
	चयन (vht_cap->cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK) अणु
	हाल IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ:
	हाल IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ:
		sta->cur_max_bandwidth = IEEE80211_STA_RX_BW_160;
		अवरोध;
	शेष:
		sta->cur_max_bandwidth = IEEE80211_STA_RX_BW_80;

		अगर (!(vht_cap->vht_mcs.tx_highest &
				cpu_to_le16(IEEE80211_VHT_EXT_NSS_BW_CAPABLE)))
			अवरोध;

		/*
		 * If this is non-zero, then it करोes support 160 MHz after all,
		 * in one क्रमm or the other. We करोn't distinguish here (or even
		 * above) between 160 and 80+80 yet.
		 */
		अगर (cap_info & IEEE80211_VHT_CAP_EXT_NSS_BW_MASK)
			sta->cur_max_bandwidth = IEEE80211_STA_RX_BW_160;
	पूर्ण

	sta->sta.bandwidth = ieee80211_sta_cur_vht_bw(sta);

	चयन (vht_cap->cap & IEEE80211_VHT_CAP_MAX_MPDU_MASK) अणु
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
पूर्ण

/* FIXME: move this to some better location - parses HE now */
क्रमागत ieee80211_sta_rx_bandwidth ieee80211_sta_cap_rx_bw(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sta_vht_cap *vht_cap = &sta->sta.vht_cap;
	काष्ठा ieee80211_sta_he_cap *he_cap = &sta->sta.he_cap;
	u32 cap_width;

	अगर (he_cap->has_he) अणु
		u8 info = he_cap->he_cap_elem.phy_cap_info[0];

		अगर (sta->sdata->vअगर.bss_conf.chandef.chan->band ==
				NL80211_BAND_2GHZ) अणु
			अगर (info & IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_40MHZ_IN_2G)
				वापस IEEE80211_STA_RX_BW_40;
			अन्यथा
				वापस IEEE80211_STA_RX_BW_20;
		पूर्ण

		अगर (info & IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G ||
		    info & IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G)
			वापस IEEE80211_STA_RX_BW_160;
		अन्यथा अगर (info & IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_40MHZ_80MHZ_IN_5G)
			वापस IEEE80211_STA_RX_BW_80;

		वापस IEEE80211_STA_RX_BW_20;
	पूर्ण

	अगर (!vht_cap->vht_supported)
		वापस sta->sta.ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40 ?
				IEEE80211_STA_RX_BW_40 :
				IEEE80211_STA_RX_BW_20;

	cap_width = vht_cap->cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK;

	अगर (cap_width == IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ ||
	    cap_width == IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ)
		वापस IEEE80211_STA_RX_BW_160;

	/*
	 * If this is non-zero, then it करोes support 160 MHz after all,
	 * in one क्रमm or the other. We करोn't distinguish here (or even
	 * above) between 160 and 80+80 yet.
	 */
	अगर (vht_cap->cap & IEEE80211_VHT_CAP_EXT_NSS_BW_MASK)
		वापस IEEE80211_STA_RX_BW_160;

	वापस IEEE80211_STA_RX_BW_80;
पूर्ण

क्रमागत nl80211_chan_width ieee80211_sta_cap_chan_bw(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sta_vht_cap *vht_cap = &sta->sta.vht_cap;
	u32 cap_width;

	अगर (!vht_cap->vht_supported) अणु
		अगर (!sta->sta.ht_cap.ht_supported)
			वापस NL80211_CHAN_WIDTH_20_NOHT;

		वापस sta->sta.ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40 ?
				NL80211_CHAN_WIDTH_40 : NL80211_CHAN_WIDTH_20;
	पूर्ण

	cap_width = vht_cap->cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK;

	अगर (cap_width == IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ)
		वापस NL80211_CHAN_WIDTH_160;
	अन्यथा अगर (cap_width == IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ)
		वापस NL80211_CHAN_WIDTH_80P80;

	वापस NL80211_CHAN_WIDTH_80;
पूर्ण

क्रमागत nl80211_chan_width
ieee80211_sta_rx_bw_to_chan_width(काष्ठा sta_info *sta)
अणु
	क्रमागत ieee80211_sta_rx_bandwidth cur_bw = sta->sta.bandwidth;
	काष्ठा ieee80211_sta_vht_cap *vht_cap = &sta->sta.vht_cap;
	u32 cap_width;

	चयन (cur_bw) अणु
	हाल IEEE80211_STA_RX_BW_20:
		अगर (!sta->sta.ht_cap.ht_supported)
			वापस NL80211_CHAN_WIDTH_20_NOHT;
		अन्यथा
			वापस NL80211_CHAN_WIDTH_20;
	हाल IEEE80211_STA_RX_BW_40:
		वापस NL80211_CHAN_WIDTH_40;
	हाल IEEE80211_STA_RX_BW_80:
		वापस NL80211_CHAN_WIDTH_80;
	हाल IEEE80211_STA_RX_BW_160:
		cap_width =
			vht_cap->cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK;

		अगर (cap_width == IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ)
			वापस NL80211_CHAN_WIDTH_160;

		वापस NL80211_CHAN_WIDTH_80P80;
	शेष:
		वापस NL80211_CHAN_WIDTH_20;
	पूर्ण
पूर्ण

क्रमागत ieee80211_sta_rx_bandwidth
ieee80211_chan_width_to_rx_bw(क्रमागत nl80211_chan_width width)
अणु
	चयन (width) अणु
	हाल NL80211_CHAN_WIDTH_20_NOHT:
	हाल NL80211_CHAN_WIDTH_20:
		वापस IEEE80211_STA_RX_BW_20;
	हाल NL80211_CHAN_WIDTH_40:
		वापस IEEE80211_STA_RX_BW_40;
	हाल NL80211_CHAN_WIDTH_80:
		वापस IEEE80211_STA_RX_BW_80;
	हाल NL80211_CHAN_WIDTH_160:
	हाल NL80211_CHAN_WIDTH_80P80:
		वापस IEEE80211_STA_RX_BW_160;
	शेष:
		WARN_ON_ONCE(1);
		वापस IEEE80211_STA_RX_BW_20;
	पूर्ण
पूर्ण

/* FIXME: नाम/move - this deals with everything not just VHT */
क्रमागत ieee80211_sta_rx_bandwidth ieee80211_sta_cur_vht_bw(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	क्रमागत ieee80211_sta_rx_bandwidth bw;
	क्रमागत nl80211_chan_width bss_width = sdata->vअगर.bss_conf.chandef.width;

	bw = ieee80211_sta_cap_rx_bw(sta);
	bw = min(bw, sta->cur_max_bandwidth);

	/* Don't consider AP's bandwidth क्रम TDLS peers, section 11.23.1 of
	 * IEEE80211-2016 specअगरication makes higher bandwidth operation
	 * possible on the TDLS link अगर the peers have wider bandwidth
	 * capability.
	 *
	 * However, in this हाल, and only अगर the TDLS peer is authorized,
	 * limit to the tdls_chandef so that the configuration here isn't
	 * wider than what's actually requested on the channel context.
	 */
	अगर (test_sta_flag(sta, WLAN_STA_TDLS_PEER) &&
	    test_sta_flag(sta, WLAN_STA_TDLS_WIDER_BW) &&
	    test_sta_flag(sta, WLAN_STA_AUTHORIZED) &&
	    sta->tdls_chandef.chan)
		bw = min(bw, ieee80211_chan_width_to_rx_bw(sta->tdls_chandef.width));
	अन्यथा
		bw = min(bw, ieee80211_chan_width_to_rx_bw(bss_width));

	वापस bw;
पूर्ण

व्योम ieee80211_sta_set_rx_nss(काष्ठा sta_info *sta)
अणु
	u8 ht_rx_nss = 0, vht_rx_nss = 0, he_rx_nss = 0, rx_nss;
	bool support_160;

	/* अगर we received a notअगरication alपढ़ोy करोn't overग_लिखो it */
	अगर (sta->sta.rx_nss)
		वापस;

	अगर (sta->sta.he_cap.has_he) अणु
		पूर्णांक i;
		u8 rx_mcs_80 = 0, rx_mcs_160 = 0;
		स्थिर काष्ठा ieee80211_sta_he_cap *he_cap = &sta->sta.he_cap;
		u16 mcs_160_map =
			le16_to_cpu(he_cap->he_mcs_nss_supp.rx_mcs_160);
		u16 mcs_80_map = le16_to_cpu(he_cap->he_mcs_nss_supp.rx_mcs_80);

		क्रम (i = 7; i >= 0; i--) अणु
			u8 mcs_160 = (mcs_160_map >> (2 * i)) & 3;

			अगर (mcs_160 != IEEE80211_VHT_MCS_NOT_SUPPORTED) अणु
				rx_mcs_160 = i + 1;
				अवरोध;
			पूर्ण
		पूर्ण
		क्रम (i = 7; i >= 0; i--) अणु
			u8 mcs_80 = (mcs_80_map >> (2 * i)) & 3;

			अगर (mcs_80 != IEEE80211_VHT_MCS_NOT_SUPPORTED) अणु
				rx_mcs_80 = i + 1;
				अवरोध;
			पूर्ण
		पूर्ण

		support_160 = he_cap->he_cap_elem.phy_cap_info[0] &
			      IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G;

		अगर (support_160)
			he_rx_nss = min(rx_mcs_80, rx_mcs_160);
		अन्यथा
			he_rx_nss = rx_mcs_80;
	पूर्ण

	अगर (sta->sta.ht_cap.ht_supported) अणु
		अगर (sta->sta.ht_cap.mcs.rx_mask[0])
			ht_rx_nss++;
		अगर (sta->sta.ht_cap.mcs.rx_mask[1])
			ht_rx_nss++;
		अगर (sta->sta.ht_cap.mcs.rx_mask[2])
			ht_rx_nss++;
		अगर (sta->sta.ht_cap.mcs.rx_mask[3])
			ht_rx_nss++;
		/* FIXME: consider rx_highest? */
	पूर्ण

	अगर (sta->sta.vht_cap.vht_supported) अणु
		पूर्णांक i;
		u16 rx_mcs_map;

		rx_mcs_map = le16_to_cpu(sta->sta.vht_cap.vht_mcs.rx_mcs_map);

		क्रम (i = 7; i >= 0; i--) अणु
			u8 mcs = (rx_mcs_map >> (2 * i)) & 3;

			अगर (mcs != IEEE80211_VHT_MCS_NOT_SUPPORTED) अणु
				vht_rx_nss = i + 1;
				अवरोध;
			पूर्ण
		पूर्ण
		/* FIXME: consider rx_highest? */
	पूर्ण

	rx_nss = max(vht_rx_nss, ht_rx_nss);
	rx_nss = max(he_rx_nss, rx_nss);
	sta->sta.rx_nss = max_t(u8, 1, rx_nss);
पूर्ण

u32 __ieee80211_vht_handle_opmode(काष्ठा ieee80211_sub_अगर_data *sdata,
				  काष्ठा sta_info *sta, u8 opmode,
				  क्रमागत nl80211_band band)
अणु
	क्रमागत ieee80211_sta_rx_bandwidth new_bw;
	काष्ठा sta_opmode_info sta_opmode = अणुपूर्ण;
	u32 changed = 0;
	u8 nss;

	/* ignore - no support क्रम BF yet */
	अगर (opmode & IEEE80211_OPMODE_NOTIF_RX_NSS_TYPE_BF)
		वापस 0;

	nss = opmode & IEEE80211_OPMODE_NOTIF_RX_NSS_MASK;
	nss >>= IEEE80211_OPMODE_NOTIF_RX_NSS_SHIFT;
	nss += 1;

	अगर (sta->sta.rx_nss != nss) अणु
		sta->sta.rx_nss = nss;
		sta_opmode.rx_nss = nss;
		changed |= IEEE80211_RC_NSS_CHANGED;
		sta_opmode.changed |= STA_OPMODE_N_SS_CHANGED;
	पूर्ण

	चयन (opmode & IEEE80211_OPMODE_NOTIF_CHANWIDTH_MASK) अणु
	हाल IEEE80211_OPMODE_NOTIF_CHANWIDTH_20MHZ:
		/* ignore IEEE80211_OPMODE_NOTIF_BW_160_80P80 must not be set */
		sta->cur_max_bandwidth = IEEE80211_STA_RX_BW_20;
		अवरोध;
	हाल IEEE80211_OPMODE_NOTIF_CHANWIDTH_40MHZ:
		/* ignore IEEE80211_OPMODE_NOTIF_BW_160_80P80 must not be set */
		sta->cur_max_bandwidth = IEEE80211_STA_RX_BW_40;
		अवरोध;
	हाल IEEE80211_OPMODE_NOTIF_CHANWIDTH_80MHZ:
		अगर (opmode & IEEE80211_OPMODE_NOTIF_BW_160_80P80)
			sta->cur_max_bandwidth = IEEE80211_STA_RX_BW_160;
		अन्यथा
			sta->cur_max_bandwidth = IEEE80211_STA_RX_BW_80;
		अवरोध;
	हाल IEEE80211_OPMODE_NOTIF_CHANWIDTH_160MHZ:
		/* legacy only, no दीर्घer used by newer spec */
		sta->cur_max_bandwidth = IEEE80211_STA_RX_BW_160;
		अवरोध;
	पूर्ण

	new_bw = ieee80211_sta_cur_vht_bw(sta);
	अगर (new_bw != sta->sta.bandwidth) अणु
		sta->sta.bandwidth = new_bw;
		sta_opmode.bw = ieee80211_sta_rx_bw_to_chan_width(sta);
		changed |= IEEE80211_RC_BW_CHANGED;
		sta_opmode.changed |= STA_OPMODE_MAX_BW_CHANGED;
	पूर्ण

	अगर (sta_opmode.changed)
		cfg80211_sta_opmode_change_notअगरy(sdata->dev, sta->addr,
						  &sta_opmode, GFP_KERNEL);

	वापस changed;
पूर्ण

व्योम ieee80211_process_mu_groups(काष्ठा ieee80211_sub_अगर_data *sdata,
				 काष्ठा ieee80211_mgmt *mgmt)
अणु
	काष्ठा ieee80211_bss_conf *bss_conf = &sdata->vअगर.bss_conf;

	अगर (!sdata->vअगर.mu_mimo_owner)
		वापस;

	अगर (!स_भेद(mgmt->u.action.u.vht_group_notअगर.position,
		    bss_conf->mu_group.position, WLAN_USER_POSITION_LEN) &&
	    !स_भेद(mgmt->u.action.u.vht_group_notअगर.membership,
		    bss_conf->mu_group.membership, WLAN_MEMBERSHIP_LEN))
		वापस;

	स_नकल(bss_conf->mu_group.membership,
	       mgmt->u.action.u.vht_group_notअगर.membership,
	       WLAN_MEMBERSHIP_LEN);
	स_नकल(bss_conf->mu_group.position,
	       mgmt->u.action.u.vht_group_notअगर.position,
	       WLAN_USER_POSITION_LEN);

	ieee80211_bss_info_change_notअगरy(sdata, BSS_CHANGED_MU_GROUPS);
पूर्ण

व्योम ieee80211_update_mu_groups(काष्ठा ieee80211_vअगर *vअगर,
				स्थिर u8 *membership, स्थिर u8 *position)
अणु
	काष्ठा ieee80211_bss_conf *bss_conf = &vअगर->bss_conf;

	अगर (WARN_ON_ONCE(!vअगर->mu_mimo_owner))
		वापस;

	स_नकल(bss_conf->mu_group.membership, membership, WLAN_MEMBERSHIP_LEN);
	स_नकल(bss_conf->mu_group.position, position, WLAN_USER_POSITION_LEN);
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_update_mu_groups);

व्योम ieee80211_vht_handle_opmode(काष्ठा ieee80211_sub_अगर_data *sdata,
				 काष्ठा sta_info *sta, u8 opmode,
				 क्रमागत nl80211_band band)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_supported_band *sband = local->hw.wiphy->bands[band];

	u32 changed = __ieee80211_vht_handle_opmode(sdata, sta, opmode, band);

	अगर (changed > 0) अणु
		ieee80211_recalc_min_chandef(sdata);
		rate_control_rate_update(local, sband, sta, changed);
	पूर्ण
पूर्ण

व्योम ieee80211_get_vht_mask_from_cap(__le16 vht_cap,
				     u16 vht_mask[NL80211_VHT_NSS_MAX])
अणु
	पूर्णांक i;
	u16 mask, cap = le16_to_cpu(vht_cap);

	क्रम (i = 0; i < NL80211_VHT_NSS_MAX; i++) अणु
		mask = (cap >> i * 2) & IEEE80211_VHT_MCS_NOT_SUPPORTED;
		चयन (mask) अणु
		हाल IEEE80211_VHT_MCS_SUPPORT_0_7:
			vht_mask[i] = 0x00FF;
			अवरोध;
		हाल IEEE80211_VHT_MCS_SUPPORT_0_8:
			vht_mask[i] = 0x01FF;
			अवरोध;
		हाल IEEE80211_VHT_MCS_SUPPORT_0_9:
			vht_mask[i] = 0x03FF;
			अवरोध;
		हाल IEEE80211_VHT_MCS_NOT_SUPPORTED:
		शेष:
			vht_mask[i] = 0;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
