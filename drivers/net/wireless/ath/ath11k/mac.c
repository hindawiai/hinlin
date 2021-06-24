<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#समावेश <net/mac80211.h>
#समावेश <linux/etherdevice.h>
#समावेश "mac.h"
#समावेश "core.h"
#समावेश "debug.h"
#समावेश "wmi.h"
#समावेश "hw.h"
#समावेश "dp_tx.h"
#समावेश "dp_rx.h"
#समावेश "testmode.h"
#समावेश "peer.h"
#समावेश "debugfs_sta.h"

#घोषणा CHAN2G(_channel, _freq, _flags) अणु \
	.band                   = NL80211_BAND_2GHZ, \
	.hw_value               = (_channel), \
	.center_freq            = (_freq), \
	.flags                  = (_flags), \
	.max_antenna_gain       = 0, \
	.max_घातer              = 30, \
पूर्ण

#घोषणा CHAN5G(_channel, _freq, _flags) अणु \
	.band                   = NL80211_BAND_5GHZ, \
	.hw_value               = (_channel), \
	.center_freq            = (_freq), \
	.flags                  = (_flags), \
	.max_antenna_gain       = 0, \
	.max_घातer              = 30, \
पूर्ण

#घोषणा CHAN6G(_channel, _freq, _flags) अणु \
	.band                   = NL80211_BAND_6GHZ, \
	.hw_value               = (_channel), \
	.center_freq            = (_freq), \
	.flags                  = (_flags), \
	.max_antenna_gain       = 0, \
	.max_घातer              = 30, \
पूर्ण

अटल स्थिर काष्ठा ieee80211_channel ath11k_2ghz_channels[] = अणु
	CHAN2G(1, 2412, 0),
	CHAN2G(2, 2417, 0),
	CHAN2G(3, 2422, 0),
	CHAN2G(4, 2427, 0),
	CHAN2G(5, 2432, 0),
	CHAN2G(6, 2437, 0),
	CHAN2G(7, 2442, 0),
	CHAN2G(8, 2447, 0),
	CHAN2G(9, 2452, 0),
	CHAN2G(10, 2457, 0),
	CHAN2G(11, 2462, 0),
	CHAN2G(12, 2467, 0),
	CHAN2G(13, 2472, 0),
	CHAN2G(14, 2484, 0),
पूर्ण;

अटल स्थिर काष्ठा ieee80211_channel ath11k_5ghz_channels[] = अणु
	CHAN5G(36, 5180, 0),
	CHAN5G(40, 5200, 0),
	CHAN5G(44, 5220, 0),
	CHAN5G(48, 5240, 0),
	CHAN5G(52, 5260, 0),
	CHAN5G(56, 5280, 0),
	CHAN5G(60, 5300, 0),
	CHAN5G(64, 5320, 0),
	CHAN5G(100, 5500, 0),
	CHAN5G(104, 5520, 0),
	CHAN5G(108, 5540, 0),
	CHAN5G(112, 5560, 0),
	CHAN5G(116, 5580, 0),
	CHAN5G(120, 5600, 0),
	CHAN5G(124, 5620, 0),
	CHAN5G(128, 5640, 0),
	CHAN5G(132, 5660, 0),
	CHAN5G(136, 5680, 0),
	CHAN5G(140, 5700, 0),
	CHAN5G(144, 5720, 0),
	CHAN5G(149, 5745, 0),
	CHAN5G(153, 5765, 0),
	CHAN5G(157, 5785, 0),
	CHAN5G(161, 5805, 0),
	CHAN5G(165, 5825, 0),
	CHAN5G(169, 5845, 0),
	CHAN5G(173, 5865, 0),
पूर्ण;

अटल स्थिर काष्ठा ieee80211_channel ath11k_6ghz_channels[] = अणु
	CHAN6G(1, 5955, 0),
	CHAN6G(5, 5975, 0),
	CHAN6G(9, 5995, 0),
	CHAN6G(13, 6015, 0),
	CHAN6G(17, 6035, 0),
	CHAN6G(21, 6055, 0),
	CHAN6G(25, 6075, 0),
	CHAN6G(29, 6095, 0),
	CHAN6G(33, 6115, 0),
	CHAN6G(37, 6135, 0),
	CHAN6G(41, 6155, 0),
	CHAN6G(45, 6175, 0),
	CHAN6G(49, 6195, 0),
	CHAN6G(53, 6215, 0),
	CHAN6G(57, 6235, 0),
	CHAN6G(61, 6255, 0),
	CHAN6G(65, 6275, 0),
	CHAN6G(69, 6295, 0),
	CHAN6G(73, 6315, 0),
	CHAN6G(77, 6335, 0),
	CHAN6G(81, 6355, 0),
	CHAN6G(85, 6375, 0),
	CHAN6G(89, 6395, 0),
	CHAN6G(93, 6415, 0),
	CHAN6G(97, 6435, 0),
	CHAN6G(101, 6455, 0),
	CHAN6G(105, 6475, 0),
	CHAN6G(109, 6495, 0),
	CHAN6G(113, 6515, 0),
	CHAN6G(117, 6535, 0),
	CHAN6G(121, 6555, 0),
	CHAN6G(125, 6575, 0),
	CHAN6G(129, 6595, 0),
	CHAN6G(133, 6615, 0),
	CHAN6G(137, 6635, 0),
	CHAN6G(141, 6655, 0),
	CHAN6G(145, 6675, 0),
	CHAN6G(149, 6695, 0),
	CHAN6G(153, 6715, 0),
	CHAN6G(157, 6735, 0),
	CHAN6G(161, 6755, 0),
	CHAN6G(165, 6775, 0),
	CHAN6G(169, 6795, 0),
	CHAN6G(173, 6815, 0),
	CHAN6G(177, 6835, 0),
	CHAN6G(181, 6855, 0),
	CHAN6G(185, 6875, 0),
	CHAN6G(189, 6895, 0),
	CHAN6G(193, 6915, 0),
	CHAN6G(197, 6935, 0),
	CHAN6G(201, 6955, 0),
	CHAN6G(205, 6975, 0),
	CHAN6G(209, 6995, 0),
	CHAN6G(213, 7015, 0),
	CHAN6G(217, 7035, 0),
	CHAN6G(221, 7055, 0),
	CHAN6G(225, 7075, 0),
	CHAN6G(229, 7095, 0),
	CHAN6G(233, 7115, 0),
पूर्ण;

अटल काष्ठा ieee80211_rate ath11k_legacy_rates[] = अणु
	अणु .bitrate = 10,
	  .hw_value = ATH11K_HW_RATE_CCK_LP_1M पूर्ण,
	अणु .bitrate = 20,
	  .hw_value = ATH11K_HW_RATE_CCK_LP_2M,
	  .hw_value_लघु = ATH11K_HW_RATE_CCK_SP_2M,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 55,
	  .hw_value = ATH11K_HW_RATE_CCK_LP_5_5M,
	  .hw_value_लघु = ATH11K_HW_RATE_CCK_SP_5_5M,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 110,
	  .hw_value = ATH11K_HW_RATE_CCK_LP_11M,
	  .hw_value_लघु = ATH11K_HW_RATE_CCK_SP_11M,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,

	अणु .bitrate = 60, .hw_value = ATH11K_HW_RATE_OFDM_6M पूर्ण,
	अणु .bitrate = 90, .hw_value = ATH11K_HW_RATE_OFDM_9M पूर्ण,
	अणु .bitrate = 120, .hw_value = ATH11K_HW_RATE_OFDM_12M पूर्ण,
	अणु .bitrate = 180, .hw_value = ATH11K_HW_RATE_OFDM_18M पूर्ण,
	अणु .bitrate = 240, .hw_value = ATH11K_HW_RATE_OFDM_24M पूर्ण,
	अणु .bitrate = 360, .hw_value = ATH11K_HW_RATE_OFDM_36M पूर्ण,
	अणु .bitrate = 480, .hw_value = ATH11K_HW_RATE_OFDM_48M पूर्ण,
	अणु .bitrate = 540, .hw_value = ATH11K_HW_RATE_OFDM_54M पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक
ath11k_phymodes[NUM_NL80211_BANDS][ATH11K_CHAN_WIDTH_NUM] = अणु
	[NL80211_BAND_2GHZ] = अणु
			[NL80211_CHAN_WIDTH_5] = MODE_UNKNOWN,
			[NL80211_CHAN_WIDTH_10] = MODE_UNKNOWN,
			[NL80211_CHAN_WIDTH_20_NOHT] = MODE_11AX_HE20_2G,
			[NL80211_CHAN_WIDTH_20] = MODE_11AX_HE20_2G,
			[NL80211_CHAN_WIDTH_40] = MODE_11AX_HE40_2G,
			[NL80211_CHAN_WIDTH_80] = MODE_11AX_HE80_2G,
			[NL80211_CHAN_WIDTH_80P80] = MODE_UNKNOWN,
			[NL80211_CHAN_WIDTH_160] = MODE_UNKNOWN,
	पूर्ण,
	[NL80211_BAND_5GHZ] = अणु
			[NL80211_CHAN_WIDTH_5] = MODE_UNKNOWN,
			[NL80211_CHAN_WIDTH_10] = MODE_UNKNOWN,
			[NL80211_CHAN_WIDTH_20_NOHT] = MODE_11AX_HE20,
			[NL80211_CHAN_WIDTH_20] = MODE_11AX_HE20,
			[NL80211_CHAN_WIDTH_40] = MODE_11AX_HE40,
			[NL80211_CHAN_WIDTH_80] = MODE_11AX_HE80,
			[NL80211_CHAN_WIDTH_160] = MODE_11AX_HE160,
			[NL80211_CHAN_WIDTH_80P80] = MODE_11AX_HE80_80,
	पूर्ण,
	[NL80211_BAND_6GHZ] = अणु
			[NL80211_CHAN_WIDTH_5] = MODE_UNKNOWN,
			[NL80211_CHAN_WIDTH_10] = MODE_UNKNOWN,
			[NL80211_CHAN_WIDTH_20_NOHT] = MODE_11AX_HE20,
			[NL80211_CHAN_WIDTH_20] = MODE_11AX_HE20,
			[NL80211_CHAN_WIDTH_40] = MODE_11AX_HE40,
			[NL80211_CHAN_WIDTH_80] = MODE_11AX_HE80,
			[NL80211_CHAN_WIDTH_160] = MODE_11AX_HE160,
			[NL80211_CHAN_WIDTH_80P80] = MODE_11AX_HE80_80,
	पूर्ण,

पूर्ण;

स्थिर काष्ठा htt_rx_ring_tlv_filter ath11k_mac_mon_status_filter_शेष = अणु
	.rx_filter = HTT_RX_FILTER_TLV_FLAGS_MPDU_START |
		     HTT_RX_FILTER_TLV_FLAGS_PPDU_END |
		     HTT_RX_FILTER_TLV_FLAGS_PPDU_END_STATUS_DONE,
	.pkt_filter_flags0 = HTT_RX_FP_MGMT_FILTER_FLAGS0,
	.pkt_filter_flags1 = HTT_RX_FP_MGMT_FILTER_FLAGS1,
	.pkt_filter_flags2 = HTT_RX_FP_CTRL_FILTER_FLASG2,
	.pkt_filter_flags3 = HTT_RX_FP_DATA_FILTER_FLASG3 |
			     HTT_RX_FP_CTRL_FILTER_FLASG3
पूर्ण;

#घोषणा ATH11K_MAC_FIRST_OFDM_RATE_IDX 4
#घोषणा ath11k_g_rates ath11k_legacy_rates
#घोषणा ath11k_g_rates_size (ARRAY_SIZE(ath11k_legacy_rates))
#घोषणा ath11k_a_rates (ath11k_legacy_rates + 4)
#घोषणा ath11k_a_rates_size (ARRAY_SIZE(ath11k_legacy_rates) - 4)

#घोषणा ATH11K_MAC_SCAN_TIMEOUT_MSECS 200 /* in msecs */

अटल स्थिर u32 ath11k_smps_map[] = अणु
	[WLAN_HT_CAP_SM_PS_STATIC] = WMI_PEER_SMPS_STATIC,
	[WLAN_HT_CAP_SM_PS_DYNAMIC] = WMI_PEER_SMPS_DYNAMIC,
	[WLAN_HT_CAP_SM_PS_INVALID] = WMI_PEER_SMPS_PS_NONE,
	[WLAN_HT_CAP_SM_PS_DISABLED] = WMI_PEER_SMPS_PS_NONE,
पूर्ण;

अटल पूर्णांक ath11k_start_vdev_delay(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर);

u8 ath11k_mac_bw_to_mac80211_bw(u8 bw)
अणु
	u8 ret = 0;

	चयन (bw) अणु
	हाल ATH11K_BW_20:
		ret = RATE_INFO_BW_20;
		अवरोध;
	हाल ATH11K_BW_40:
		ret = RATE_INFO_BW_40;
		अवरोध;
	हाल ATH11K_BW_80:
		ret = RATE_INFO_BW_80;
		अवरोध;
	हाल ATH11K_BW_160:
		ret = RATE_INFO_BW_160;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

क्रमागत ath11k_supported_bw ath11k_mac_mac80211_bw_to_ath11k_bw(क्रमागत rate_info_bw bw)
अणु
	चयन (bw) अणु
	हाल RATE_INFO_BW_20:
		वापस ATH11K_BW_20;
	हाल RATE_INFO_BW_40:
		वापस ATH11K_BW_40;
	हाल RATE_INFO_BW_80:
		वापस ATH11K_BW_80;
	हाल RATE_INFO_BW_160:
		वापस ATH11K_BW_160;
	शेष:
		वापस ATH11K_BW_20;
	पूर्ण
पूर्ण

पूर्णांक ath11k_mac_hw_ratecode_to_legacy_rate(u8 hw_rc, u8 preamble, u8 *rateidx,
					  u16 *rate)
अणु
	/* As शेष, it is OFDM rates */
	पूर्णांक i = ATH11K_MAC_FIRST_OFDM_RATE_IDX;
	पूर्णांक max_rates_idx = ath11k_g_rates_size;

	अगर (preamble == WMI_RATE_PREAMBLE_CCK) अणु
		hw_rc &= ~ATH11k_HW_RATECODE_CCK_SHORT_PREAM_MASK;
		i = 0;
		max_rates_idx = ATH11K_MAC_FIRST_OFDM_RATE_IDX;
	पूर्ण

	जबतक (i < max_rates_idx) अणु
		अगर (hw_rc == ath11k_legacy_rates[i].hw_value) अणु
			*rateidx = i;
			*rate = ath11k_legacy_rates[i].bitrate;
			वापस 0;
		पूर्ण
		i++;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक get_num_chains(u32 mask)
अणु
	पूर्णांक num_chains = 0;

	जबतक (mask) अणु
		अगर (mask & BIT(0))
			num_chains++;
		mask >>= 1;
	पूर्ण

	वापस num_chains;
पूर्ण

u8 ath11k_mac_bitrate_to_idx(स्थिर काष्ठा ieee80211_supported_band *sband,
			     u32 bitrate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sband->n_bitrates; i++)
		अगर (sband->bitrates[i].bitrate == bitrate)
			वापस i;

	वापस 0;
पूर्ण

अटल u32
ath11k_mac_max_ht_nss(स्थिर u8 ht_mcs_mask[IEEE80211_HT_MCS_MASK_LEN])
अणु
	पूर्णांक nss;

	क्रम (nss = IEEE80211_HT_MCS_MASK_LEN - 1; nss >= 0; nss--)
		अगर (ht_mcs_mask[nss])
			वापस nss + 1;

	वापस 1;
पूर्ण

अटल u32
ath11k_mac_max_vht_nss(स्थिर u16 vht_mcs_mask[NL80211_VHT_NSS_MAX])
अणु
	पूर्णांक nss;

	क्रम (nss = NL80211_VHT_NSS_MAX - 1; nss >= 0; nss--)
		अगर (vht_mcs_mask[nss])
			वापस nss + 1;

	वापस 1;
पूर्ण

अटल u8 ath11k_parse_mpdudensity(u8 mpdudensity)
अणु
/* 802.11n D2.0 defined values क्रम "Minimum MPDU Start Spacing":
 *   0 क्रम no restriction
 *   1 क्रम 1/4 us
 *   2 क्रम 1/2 us
 *   3 क्रम 1 us
 *   4 क्रम 2 us
 *   5 क्रम 4 us
 *   6 क्रम 8 us
 *   7 क्रम 16 us
 */
	चयन (mpdudensity) अणु
	हाल 0:
		वापस 0;
	हाल 1:
	हाल 2:
	हाल 3:
	/* Our lower layer calculations limit our precision to
	 * 1 microsecond
	 */
		वापस 1;
	हाल 4:
		वापस 2;
	हाल 5:
		वापस 4;
	हाल 6:
		वापस 8;
	हाल 7:
		वापस 16;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ath11k_mac_vअगर_chan(काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा cfg80211_chan_def *def)
अणु
	काष्ठा ieee80211_chanctx_conf *conf;

	rcu_पढ़ो_lock();
	conf = rcu_dereference(vअगर->chanctx_conf);
	अगर (!conf) अणु
		rcu_पढ़ो_unlock();
		वापस -ENOENT;
	पूर्ण

	*def = conf->def;
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल bool ath11k_mac_bitrate_is_cck(पूर्णांक bitrate)
अणु
	चयन (bitrate) अणु
	हाल 10:
	हाल 20:
	हाल 55:
	हाल 110:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

u8 ath11k_mac_hw_rate_to_idx(स्थिर काष्ठा ieee80211_supported_band *sband,
			     u8 hw_rate, bool cck)
अणु
	स्थिर काष्ठा ieee80211_rate *rate;
	पूर्णांक i;

	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		rate = &sband->bitrates[i];

		अगर (ath11k_mac_bitrate_is_cck(rate->bitrate) != cck)
			जारी;

		अगर (rate->hw_value == hw_rate)
			वापस i;
		अन्यथा अगर (rate->flags & IEEE80211_RATE_SHORT_PREAMBLE &&
			 rate->hw_value_लघु == hw_rate)
			वापस i;
	पूर्ण

	वापस 0;
पूर्ण

अटल u8 ath11k_mac_bitrate_to_rate(पूर्णांक bitrate)
अणु
	वापस DIV_ROUND_UP(bitrate, 5) |
	       (ath11k_mac_bitrate_is_cck(bitrate) ? BIT(7) : 0);
पूर्ण

अटल व्योम ath11k_get_arvअगर_iter(व्योम *data, u8 *mac,
				  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath11k_vअगर_iter *arvअगर_iter = data;
	काष्ठा ath11k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;

	अगर (arvअगर->vdev_id == arvअगर_iter->vdev_id)
		arvअगर_iter->arvअगर = arvअगर;
पूर्ण

काष्ठा ath11k_vअगर *ath11k_mac_get_arvअगर(काष्ठा ath11k *ar, u32 vdev_id)
अणु
	काष्ठा ath11k_vअगर_iter arvअगर_iter;
	u32 flags;

	स_रखो(&arvअगर_iter, 0, माप(काष्ठा ath11k_vअगर_iter));
	arvअगर_iter.vdev_id = vdev_id;

	flags = IEEE80211_IFACE_ITER_RESUME_ALL;
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(ar->hw,
						   flags,
						   ath11k_get_arvअगर_iter,
						   &arvअगर_iter);
	अगर (!arvअगर_iter.arvअगर) अणु
		ath11k_warn(ar->ab, "No VIF found for vdev %d\n", vdev_id);
		वापस शून्य;
	पूर्ण

	वापस arvअगर_iter.arvअगर;
पूर्ण

काष्ठा ath11k_vअगर *ath11k_mac_get_arvअगर_by_vdev_id(काष्ठा ath11k_base *ab,
						   u32 vdev_id)
अणु
	पूर्णांक i;
	काष्ठा ath11k_pdev *pdev;
	काष्ठा ath11k_vअगर *arvअगर;

	क्रम (i = 0; i < ab->num_radios; i++) अणु
		pdev = rcu_dereference(ab->pdevs_active[i]);
		अगर (pdev && pdev->ar) अणु
			arvअगर = ath11k_mac_get_arvअगर(pdev->ar, vdev_id);
			अगर (arvअगर)
				वापस arvअगर;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा ath11k *ath11k_mac_get_ar_by_vdev_id(काष्ठा ath11k_base *ab, u32 vdev_id)
अणु
	पूर्णांक i;
	काष्ठा ath11k_pdev *pdev;

	क्रम (i = 0; i < ab->num_radios; i++) अणु
		pdev = rcu_dereference(ab->pdevs_active[i]);
		अगर (pdev && pdev->ar) अणु
			अगर (pdev->ar->allocated_vdev_map & (1LL << vdev_id))
				वापस pdev->ar;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा ath11k *ath11k_mac_get_ar_by_pdev_id(काष्ठा ath11k_base *ab, u32 pdev_id)
अणु
	पूर्णांक i;
	काष्ठा ath11k_pdev *pdev;

	अगर (ab->hw_params.single_pdev_only) अणु
		pdev = rcu_dereference(ab->pdevs_active[0]);
		वापस pdev ? pdev->ar : शून्य;
	पूर्ण

	अगर (WARN_ON(pdev_id > ab->num_radios))
		वापस शून्य;

	क्रम (i = 0; i < ab->num_radios; i++) अणु
		pdev = rcu_dereference(ab->pdevs_active[i]);

		अगर (pdev && pdev->pdev_id == pdev_id)
			वापस (pdev->ar ? pdev->ar : शून्य);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम ath11k_pdev_caps_update(काष्ठा ath11k *ar)
अणु
	काष्ठा ath11k_base *ab = ar->ab;

	ar->max_tx_घातer = ab->target_caps.hw_max_tx_घातer;

	/* FIXME Set min_tx_घातer to ab->target_caps.hw_min_tx_घातer.
	 * But since the received value in svcrdy is same as hw_max_tx_घातer,
	 * we can set ar->min_tx_घातer to 0 currently until
	 * this is fixed in firmware
	 */
	ar->min_tx_घातer = 0;

	ar->txघातer_limit_2g = ar->max_tx_घातer;
	ar->txघातer_limit_5g = ar->max_tx_घातer;
	ar->txघातer_scale = WMI_HOST_TP_SCALE_MAX;
पूर्ण

अटल पूर्णांक ath11k_mac_txघातer_recalc(काष्ठा ath11k *ar)
अणु
	काष्ठा ath11k_pdev *pdev = ar->pdev;
	काष्ठा ath11k_vअगर *arvअगर;
	पूर्णांक ret, txघातer = -1;
	u32 param;

	lockdep_निश्चित_held(&ar->conf_mutex);

	list_क्रम_each_entry(arvअगर, &ar->arvअगरs, list) अणु
		अगर (arvअगर->txघातer <= 0)
			जारी;

		अगर (txघातer == -1)
			txघातer = arvअगर->txघातer;
		अन्यथा
			txघातer = min(txघातer, arvअगर->txघातer);
	पूर्ण

	अगर (txघातer == -1)
		वापस 0;

	/* txpwr is set as 2 units per dBm in FW*/
	txघातer = min_t(u32, max_t(u32, ar->min_tx_घातer, txघातer),
			ar->max_tx_घातer) * 2;

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "txpower to set in hw %d\n",
		   txघातer / 2);

	अगर ((pdev->cap.supported_bands & WMI_HOST_WLAN_2G_CAP) &&
	    ar->txघातer_limit_2g != txघातer) अणु
		param = WMI_PDEV_PARAM_TXPOWER_LIMIT2G;
		ret = ath11k_wmi_pdev_set_param(ar, param,
						txघातer, ar->pdev->pdev_id);
		अगर (ret)
			जाओ fail;
		ar->txघातer_limit_2g = txघातer;
	पूर्ण

	अगर ((pdev->cap.supported_bands & WMI_HOST_WLAN_5G_CAP) &&
	    ar->txघातer_limit_5g != txघातer) अणु
		param = WMI_PDEV_PARAM_TXPOWER_LIMIT5G;
		ret = ath11k_wmi_pdev_set_param(ar, param,
						txघातer, ar->pdev->pdev_id);
		अगर (ret)
			जाओ fail;
		ar->txघातer_limit_5g = txघातer;
	पूर्ण

	वापस 0;

fail:
	ath11k_warn(ar->ab, "failed to recalc txpower limit %d using pdev param %d: %d\n",
		    txघातer / 2, param, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_recalc_rtscts_prot(काष्ठा ath11k_vअगर *arvअगर)
अणु
	काष्ठा ath11k *ar = arvअगर->ar;
	u32 vdev_param, rts_cts = 0;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	vdev_param = WMI_VDEV_PARAM_ENABLE_RTSCTS;

	/* Enable RTS/CTS protection क्रम sw retries (when legacy stations
	 * are in BSS) or by शेष only क्रम second rate series.
	 * TODO: Check अगर we need to enable CTS 2 Self in any हाल
	 */
	rts_cts = WMI_USE_RTS_CTS;

	अगर (arvअगर->num_legacy_stations > 0)
		rts_cts |= WMI_RTSCTS_ACROSS_SW_RETRIES << 4;
	अन्यथा
		rts_cts |= WMI_RTSCTS_FOR_SECOND_RATESERIES << 4;

	/* Need not send duplicate param value to firmware */
	अगर (arvअगर->rtscts_prot_mode == rts_cts)
		वापस 0;

	arvअगर->rtscts_prot_mode = rts_cts;

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac vdev %d recalc rts/cts prot %d\n",
		   arvअगर->vdev_id, rts_cts);

	ret =  ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
					     vdev_param, rts_cts);
	अगर (ret)
		ath11k_warn(ar->ab, "failed to recalculate rts/cts prot for vdev %d: %d\n",
			    arvअगर->vdev_id, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_mac_set_kickout(काष्ठा ath11k_vअगर *arvअगर)
अणु
	काष्ठा ath11k *ar = arvअगर->ar;
	u32 param;
	पूर्णांक ret;

	ret = ath11k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_STA_KICKOUT_TH,
					ATH11K_KICKOUT_THRESHOLD,
					ar->pdev->pdev_id);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to set kickout threshold on vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	param = WMI_VDEV_PARAM_AP_KEEPALIVE_MIN_IDLE_INACTIVE_TIME_SECS;
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id, param,
					    ATH11K_KEEPALIVE_MIN_IDLE);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to set keepalive minimum idle time on vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	param = WMI_VDEV_PARAM_AP_KEEPALIVE_MAX_IDLE_INACTIVE_TIME_SECS;
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id, param,
					    ATH11K_KEEPALIVE_MAX_IDLE);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to set keepalive maximum idle time on vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	param = WMI_VDEV_PARAM_AP_KEEPALIVE_MAX_UNRESPONSIVE_TIME_SECS;
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id, param,
					    ATH11K_KEEPALIVE_MAX_UNRESPONSIVE);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to set keepalive maximum unresponsive time on vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ath11k_mac_peer_cleanup_all(काष्ठा ath11k *ar)
अणु
	काष्ठा ath11k_peer *peer, *पंचांगp;
	काष्ठा ath11k_base *ab = ar->ab;

	lockdep_निश्चित_held(&ar->conf_mutex);

	spin_lock_bh(&ab->base_lock);
	list_क्रम_each_entry_safe(peer, पंचांगp, &ab->peers, list) अणु
		ath11k_peer_rx_tid_cleanup(ar, peer);
		list_del(&peer->list);
		kमुक्त(peer);
	पूर्ण
	spin_unlock_bh(&ab->base_lock);

	ar->num_peers = 0;
	ar->num_stations = 0;
पूर्ण

अटल पूर्णांक ath11k_monitor_vdev_up(काष्ठा ath11k *ar, पूर्णांक vdev_id)
अणु
	पूर्णांक ret = 0;

	ret = ath11k_wmi_vdev_up(ar, vdev_id, 0, ar->mac_addr);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to put up monitor vdev %i: %d\n",
			    vdev_id, ret);
		वापस ret;
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac monitor vdev %i started\n",
		   vdev_id);
	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_mac_op_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	/* mac80211 requires this op to be present and that's why
	 * there's an empty function, this can be extended when
	 * required.
	 */

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_mac_setup_bcn_पंचांगpl(काष्ठा ath11k_vअगर *arvअगर)
अणु
	काष्ठा ath11k *ar = arvअगर->ar;
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ieee80211_hw *hw = ar->hw;
	काष्ठा ieee80211_vअगर *vअगर = arvअगर->vअगर;
	काष्ठा ieee80211_mutable_offsets offs = अणुपूर्ण;
	काष्ठा sk_buff *bcn;
	काष्ठा ieee80211_mgmt *mgmt;
	u8 *ies;
	पूर्णांक ret;

	अगर (arvअगर->vdev_type != WMI_VDEV_TYPE_AP)
		वापस 0;

	bcn = ieee80211_beacon_get_ढाँचा(hw, vअगर, &offs);
	अगर (!bcn) अणु
		ath11k_warn(ab, "failed to get beacon template from mac80211\n");
		वापस -EPERM;
	पूर्ण

	ies = bcn->data + ieee80211_get_hdrlen_from_skb(bcn);
	ies += माप(mgmt->u.beacon);

	अगर (cfg80211_find_ie(WLAN_EID_RSN, ies, (skb_tail_poपूर्णांकer(bcn) - ies)))
		arvअगर->rsnie_present = true;

	अगर (cfg80211_find_venकरोr_ie(WLAN_OUI_MICROSOFT,
				    WLAN_OUI_TYPE_MICROSOFT_WPA,
				    ies, (skb_tail_poपूर्णांकer(bcn) - ies)))
		arvअगर->wpaie_present = true;

	ret = ath11k_wmi_bcn_पंचांगpl(ar, arvअगर->vdev_id, &offs, bcn);

	kमुक्त_skb(bcn);

	अगर (ret)
		ath11k_warn(ab, "failed to submit beacon template command: %d\n",
			    ret);

	वापस ret;
पूर्ण

अटल व्योम ath11k_control_beaconing(काष्ठा ath11k_vअगर *arvअगर,
				     काष्ठा ieee80211_bss_conf *info)
अणु
	काष्ठा ath11k *ar = arvअगर->ar;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&arvअगर->ar->conf_mutex);

	अगर (!info->enable_beacon) अणु
		ret = ath11k_wmi_vdev_करोwn(ar, arvअगर->vdev_id);
		अगर (ret)
			ath11k_warn(ar->ab, "failed to down vdev_id %i: %d\n",
				    arvअगर->vdev_id, ret);

		arvअगर->is_up = false;
		वापस;
	पूर्ण

	/* Install the beacon ढाँचा to the FW */
	ret = ath11k_mac_setup_bcn_पंचांगpl(arvअगर);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to update bcn tmpl during vdev up: %d\n",
			    ret);
		वापस;
	पूर्ण

	arvअगर->tx_seq_no = 0x1000;

	arvअगर->aid = 0;

	ether_addr_copy(arvअगर->bssid, info->bssid);

	ret = ath11k_wmi_vdev_up(arvअगर->ar, arvअगर->vdev_id, arvअगर->aid,
				 arvअगर->bssid);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to bring up vdev %d: %i\n",
			    arvअगर->vdev_id, ret);
		वापस;
	पूर्ण

	arvअगर->is_up = true;

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac vdev %d up\n", arvअगर->vdev_id);
पूर्ण

अटल व्योम ath11k_mac_handle_beacon_iter(व्योम *data, u8 *mac,
					  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा sk_buff *skb = data;
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *)skb->data;
	काष्ठा ath11k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;

	अगर (vअगर->type != NL80211_IFTYPE_STATION)
		वापस;

	अगर (!ether_addr_equal(mgmt->bssid, vअगर->bss_conf.bssid))
		वापस;

	cancel_delayed_work(&arvअगर->connection_loss_work);
पूर्ण

व्योम ath11k_mac_handle_beacon(काष्ठा ath11k *ar, काष्ठा sk_buff *skb)
अणु
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(ar->hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   ath11k_mac_handle_beacon_iter,
						   skb);
पूर्ण

अटल व्योम ath11k_mac_handle_beacon_miss_iter(व्योम *data, u8 *mac,
					       काष्ठा ieee80211_vअगर *vअगर)
अणु
	u32 *vdev_id = data;
	काष्ठा ath11k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा ath11k *ar = arvअगर->ar;
	काष्ठा ieee80211_hw *hw = ar->hw;

	अगर (arvअगर->vdev_id != *vdev_id)
		वापस;

	अगर (!arvअगर->is_up)
		वापस;

	ieee80211_beacon_loss(vअगर);

	/* Firmware करोesn't report beacon loss events repeatedly. If AP probe
	 * (करोne by mac80211) succeeds but beacons करो not resume then it
	 * करोesn't make sense to जारी operation. Queue connection loss work
	 * which can be cancelled when beacon is received.
	 */
	ieee80211_queue_delayed_work(hw, &arvअगर->connection_loss_work,
				     ATH11K_CONNECTION_LOSS_HZ);
पूर्ण

व्योम ath11k_mac_handle_beacon_miss(काष्ठा ath11k *ar, u32 vdev_id)
अणु
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(ar->hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   ath11k_mac_handle_beacon_miss_iter,
						   &vdev_id);
पूर्ण

अटल व्योम ath11k_mac_vअगर_sta_connection_loss_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath11k_vअगर *arvअगर = container_of(work, काष्ठा ath11k_vअगर,
						connection_loss_work.work);
	काष्ठा ieee80211_vअगर *vअगर = arvअगर->vअगर;

	अगर (!arvअगर->is_up)
		वापस;

	ieee80211_connection_loss(vअगर);
पूर्ण

अटल व्योम ath11k_peer_assoc_h_basic(काष्ठा ath11k *ar,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा ieee80211_sta *sta,
				      काष्ठा peer_assoc_params *arg)
अणु
	काष्ठा ath11k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	u32 aid;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (vअगर->type == NL80211_IFTYPE_STATION)
		aid = vअगर->bss_conf.aid;
	अन्यथा
		aid = sta->aid;

	ether_addr_copy(arg->peer_mac, sta->addr);
	arg->vdev_id = arvअगर->vdev_id;
	arg->peer_associd = aid;
	arg->auth_flag = true;
	/* TODO: STA WAR in ath10k क्रम listen पूर्णांकerval required? */
	arg->peer_listen_पूर्णांकval = ar->hw->conf.listen_पूर्णांकerval;
	arg->peer_nss = 1;
	arg->peer_caps = vअगर->bss_conf.assoc_capability;
पूर्ण

अटल व्योम ath11k_peer_assoc_h_crypto(काष्ठा ath11k *ar,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_sta *sta,
				       काष्ठा peer_assoc_params *arg)
अणु
	काष्ठा ieee80211_bss_conf *info = &vअगर->bss_conf;
	काष्ठा cfg80211_chan_def def;
	काष्ठा cfg80211_bss *bss;
	काष्ठा ath11k_vअगर *arvअगर = (काष्ठा ath11k_vअगर *)vअगर->drv_priv;
	स्थिर u8 *rsnie = शून्य;
	स्थिर u8 *wpaie = शून्य;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (WARN_ON(ath11k_mac_vअगर_chan(vअगर, &def)))
		वापस;

	bss = cfg80211_get_bss(ar->hw->wiphy, def.chan, info->bssid, शून्य, 0,
			       IEEE80211_BSS_TYPE_ANY, IEEE80211_PRIVACY_ANY);

	अगर (arvअगर->rsnie_present || arvअगर->wpaie_present) अणु
		arg->need_ptk_4_way = true;
		अगर (arvअगर->wpaie_present)
			arg->need_gtk_2_way = true;
	पूर्ण अन्यथा अगर (bss) अणु
		स्थिर काष्ठा cfg80211_bss_ies *ies;

		rcu_पढ़ो_lock();
		rsnie = ieee80211_bss_get_ie(bss, WLAN_EID_RSN);

		ies = rcu_dereference(bss->ies);

		wpaie = cfg80211_find_venकरोr_ie(WLAN_OUI_MICROSOFT,
						WLAN_OUI_TYPE_MICROSOFT_WPA,
						ies->data,
						ies->len);
		rcu_पढ़ो_unlock();
		cfg80211_put_bss(ar->hw->wiphy, bss);
	पूर्ण

	/* FIXME: base on RSN IE/WPA IE is a correct idea? */
	अगर (rsnie || wpaie) अणु
		ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
			   "%s: rsn ie found\n", __func__);
		arg->need_ptk_4_way = true;
	पूर्ण

	अगर (wpaie) अणु
		ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
			   "%s: wpa ie found\n", __func__);
		arg->need_gtk_2_way = true;
	पूर्ण

	अगर (sta->mfp) अणु
		/* TODO: Need to check अगर FW supports PMF? */
		arg->is_pmf_enabled = true;
	पूर्ण

	/* TODO: safe_mode_enabled (bypass 4-way handshake) flag req? */
पूर्ण

अटल व्योम ath11k_peer_assoc_h_rates(काष्ठा ath11k *ar,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा ieee80211_sta *sta,
				      काष्ठा peer_assoc_params *arg)
अणु
	काष्ठा ath11k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा wmi_rate_set_arg *rateset = &arg->peer_legacy_rates;
	काष्ठा cfg80211_chan_def def;
	स्थिर काष्ठा ieee80211_supported_band *sband;
	स्थिर काष्ठा ieee80211_rate *rates;
	क्रमागत nl80211_band band;
	u32 ratemask;
	u8 rate;
	पूर्णांक i;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (WARN_ON(ath11k_mac_vअगर_chan(vअगर, &def)))
		वापस;

	band = def.chan->band;
	sband = ar->hw->wiphy->bands[band];
	ratemask = sta->supp_rates[band];
	ratemask &= arvअगर->bitrate_mask.control[band].legacy;
	rates = sband->bitrates;

	rateset->num_rates = 0;

	क्रम (i = 0; i < 32; i++, ratemask >>= 1, rates++) अणु
		अगर (!(ratemask & 1))
			जारी;

		rate = ath11k_mac_bitrate_to_rate(rates->bitrate);
		rateset->rates[rateset->num_rates] = rate;
		rateset->num_rates++;
	पूर्ण
पूर्ण

अटल bool
ath11k_peer_assoc_h_ht_masked(स्थिर u8 ht_mcs_mask[IEEE80211_HT_MCS_MASK_LEN])
अणु
	पूर्णांक nss;

	क्रम (nss = 0; nss < IEEE80211_HT_MCS_MASK_LEN; nss++)
		अगर (ht_mcs_mask[nss])
			वापस false;

	वापस true;
पूर्ण

अटल bool
ath11k_peer_assoc_h_vht_masked(स्थिर u16 vht_mcs_mask[NL80211_VHT_NSS_MAX])
अणु
	पूर्णांक nss;

	क्रम (nss = 0; nss < NL80211_VHT_NSS_MAX; nss++)
		अगर (vht_mcs_mask[nss])
			वापस false;

	वापस true;
पूर्ण

अटल व्योम ath11k_peer_assoc_h_ht(काष्ठा ath11k *ar,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा ieee80211_sta *sta,
				   काष्ठा peer_assoc_params *arg)
अणु
	स्थिर काष्ठा ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
	काष्ठा ath11k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा cfg80211_chan_def def;
	क्रमागत nl80211_band band;
	स्थिर u8 *ht_mcs_mask;
	पूर्णांक i, n;
	u8 max_nss;
	u32 stbc;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (WARN_ON(ath11k_mac_vअगर_chan(vअगर, &def)))
		वापस;

	अगर (!ht_cap->ht_supported)
		वापस;

	band = def.chan->band;
	ht_mcs_mask = arvअगर->bitrate_mask.control[band].ht_mcs;

	अगर (ath11k_peer_assoc_h_ht_masked(ht_mcs_mask))
		वापस;

	arg->ht_flag = true;

	arg->peer_max_mpdu = (1 << (IEEE80211_HT_MAX_AMPDU_FACTOR +
				    ht_cap->ampdu_factor)) - 1;

	arg->peer_mpdu_density =
		ath11k_parse_mpdudensity(ht_cap->ampdu_density);

	arg->peer_ht_caps = ht_cap->cap;
	arg->peer_rate_caps |= WMI_HOST_RC_HT_FLAG;

	अगर (ht_cap->cap & IEEE80211_HT_CAP_LDPC_CODING)
		arg->ldpc_flag = true;

	अगर (sta->bandwidth >= IEEE80211_STA_RX_BW_40) अणु
		arg->bw_40 = true;
		arg->peer_rate_caps |= WMI_HOST_RC_CW40_FLAG;
	पूर्ण

	अगर (arvअगर->bitrate_mask.control[band].gi != NL80211_TXRATE_FORCE_LGI) अणु
		अगर (ht_cap->cap & (IEEE80211_HT_CAP_SGI_20 |
		    IEEE80211_HT_CAP_SGI_40))
			arg->peer_rate_caps |= WMI_HOST_RC_SGI_FLAG;
	पूर्ण

	अगर (ht_cap->cap & IEEE80211_HT_CAP_TX_STBC) अणु
		arg->peer_rate_caps |= WMI_HOST_RC_TX_STBC_FLAG;
		arg->stbc_flag = true;
	पूर्ण

	अगर (ht_cap->cap & IEEE80211_HT_CAP_RX_STBC) अणु
		stbc = ht_cap->cap & IEEE80211_HT_CAP_RX_STBC;
		stbc = stbc >> IEEE80211_HT_CAP_RX_STBC_SHIFT;
		stbc = stbc << WMI_HOST_RC_RX_STBC_FLAG_S;
		arg->peer_rate_caps |= stbc;
		arg->stbc_flag = true;
	पूर्ण

	अगर (ht_cap->mcs.rx_mask[1] && ht_cap->mcs.rx_mask[2])
		arg->peer_rate_caps |= WMI_HOST_RC_TS_FLAG;
	अन्यथा अगर (ht_cap->mcs.rx_mask[1])
		arg->peer_rate_caps |= WMI_HOST_RC_DS_FLAG;

	क्रम (i = 0, n = 0, max_nss = 0; i < IEEE80211_HT_MCS_MASK_LEN * 8; i++)
		अगर ((ht_cap->mcs.rx_mask[i / 8] & BIT(i % 8)) &&
		    (ht_mcs_mask[i / 8] & BIT(i % 8))) अणु
			max_nss = (i / 8) + 1;
			arg->peer_ht_rates.rates[n++] = i;
		पूर्ण

	/* This is a workaround क्रम HT-enabled STAs which अवरोध the spec
	 * and have no HT capabilities RX mask (no HT RX MCS map).
	 *
	 * As per spec, in section 20.3.5 Modulation and coding scheme (MCS),
	 * MCS 0 through 7 are mandatory in 20MHz with 800 ns GI at all STAs.
	 *
	 * Firmware निश्चितs अगर such situation occurs.
	 */
	अगर (n == 0) अणु
		arg->peer_ht_rates.num_rates = 8;
		क्रम (i = 0; i < arg->peer_ht_rates.num_rates; i++)
			arg->peer_ht_rates.rates[i] = i;
	पूर्ण अन्यथा अणु
		arg->peer_ht_rates.num_rates = n;
		arg->peer_nss = min(sta->rx_nss, max_nss);
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac ht peer %pM mcs cnt %d nss %d\n",
		   arg->peer_mac,
		   arg->peer_ht_rates.num_rates,
		   arg->peer_nss);
पूर्ण

अटल पूर्णांक ath11k_mac_get_max_vht_mcs_map(u16 mcs_map, पूर्णांक nss)
अणु
	चयन ((mcs_map >> (2 * nss)) & 0x3) अणु
	हाल IEEE80211_VHT_MCS_SUPPORT_0_7: वापस BIT(8) - 1;
	हाल IEEE80211_VHT_MCS_SUPPORT_0_8: वापस BIT(9) - 1;
	हाल IEEE80211_VHT_MCS_SUPPORT_0_9: वापस BIT(10) - 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल u16
ath11k_peer_assoc_h_vht_limit(u16 tx_mcs_set,
			      स्थिर u16 vht_mcs_limit[NL80211_VHT_NSS_MAX])
अणु
	पूर्णांक idx_limit;
	पूर्णांक nss;
	u16 mcs_map;
	u16 mcs;

	क्रम (nss = 0; nss < NL80211_VHT_NSS_MAX; nss++) अणु
		mcs_map = ath11k_mac_get_max_vht_mcs_map(tx_mcs_set, nss) &
			  vht_mcs_limit[nss];

		अगर (mcs_map)
			idx_limit = fls(mcs_map) - 1;
		अन्यथा
			idx_limit = -1;

		चयन (idx_limit) अणु
		हाल 0:
		हाल 1:
		हाल 2:
		हाल 3:
		हाल 4:
		हाल 5:
		हाल 6:
		हाल 7:
			mcs = IEEE80211_VHT_MCS_SUPPORT_0_7;
			अवरोध;
		हाल 8:
			mcs = IEEE80211_VHT_MCS_SUPPORT_0_8;
			अवरोध;
		हाल 9:
			mcs = IEEE80211_VHT_MCS_SUPPORT_0_9;
			अवरोध;
		शेष:
			WARN_ON(1);
			fallthrough;
		हाल -1:
			mcs = IEEE80211_VHT_MCS_NOT_SUPPORTED;
			अवरोध;
		पूर्ण

		tx_mcs_set &= ~(0x3 << (nss * 2));
		tx_mcs_set |= mcs << (nss * 2);
	पूर्ण

	वापस tx_mcs_set;
पूर्ण

अटल व्योम ath11k_peer_assoc_h_vht(काष्ठा ath11k *ar,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_sta *sta,
				    काष्ठा peer_assoc_params *arg)
अणु
	स्थिर काष्ठा ieee80211_sta_vht_cap *vht_cap = &sta->vht_cap;
	काष्ठा ath11k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा cfg80211_chan_def def;
	क्रमागत nl80211_band band;
	स्थिर u16 *vht_mcs_mask;
	u8 ampdu_factor;
	u8 max_nss, vht_mcs;
	पूर्णांक i;

	अगर (WARN_ON(ath11k_mac_vअगर_chan(vअगर, &def)))
		वापस;

	अगर (!vht_cap->vht_supported)
		वापस;

	band = def.chan->band;
	vht_mcs_mask = arvअगर->bitrate_mask.control[band].vht_mcs;

	अगर (ath11k_peer_assoc_h_vht_masked(vht_mcs_mask))
		वापस;

	arg->vht_flag = true;

	/* TODO: similar flags required? */
	arg->vht_capable = true;

	अगर (def.chan->band == NL80211_BAND_2GHZ)
		arg->vht_ng_flag = true;

	arg->peer_vht_caps = vht_cap->cap;

	ampdu_factor = (vht_cap->cap &
			IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK) >>
		       IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT;

	/* Workaround: Some Netgear/Linksys 11ac APs set Rx A-MPDU factor to
	 * zero in VHT IE. Using it would result in degraded throughput.
	 * arg->peer_max_mpdu at this poपूर्णांक contains HT max_mpdu so keep
	 * it अगर VHT max_mpdu is smaller.
	 */
	arg->peer_max_mpdu = max(arg->peer_max_mpdu,
				 (1U << (IEEE80211_HT_MAX_AMPDU_FACTOR +
					ampdu_factor)) - 1);

	अगर (sta->bandwidth == IEEE80211_STA_RX_BW_80)
		arg->bw_80 = true;

	अगर (sta->bandwidth == IEEE80211_STA_RX_BW_160)
		arg->bw_160 = true;

	/* Calculate peer NSS capability from VHT capabilities अगर STA
	 * supports VHT.
	 */
	क्रम (i = 0, max_nss = 0, vht_mcs = 0; i < NL80211_VHT_NSS_MAX; i++) अणु
		vht_mcs = __le16_to_cpu(vht_cap->vht_mcs.rx_mcs_map) >>
			  (2 * i) & 3;

		अगर (vht_mcs != IEEE80211_VHT_MCS_NOT_SUPPORTED &&
		    vht_mcs_mask[i])
			max_nss = i + 1;
	पूर्ण
	arg->peer_nss = min(sta->rx_nss, max_nss);
	arg->rx_max_rate = __le16_to_cpu(vht_cap->vht_mcs.rx_highest);
	arg->rx_mcs_set = __le16_to_cpu(vht_cap->vht_mcs.rx_mcs_map);
	arg->tx_max_rate = __le16_to_cpu(vht_cap->vht_mcs.tx_highest);
	arg->tx_mcs_set = ath11k_peer_assoc_h_vht_limit(
		__le16_to_cpu(vht_cap->vht_mcs.tx_mcs_map), vht_mcs_mask);

	/* In IPQ8074 platक्रमm, VHT mcs rate 10 and 11 is enabled by शेष.
	 * VHT mcs rate 10 and 11 is not suppoerted in 11ac standard.
	 * so explicitly disable the VHT MCS rate 10 and 11 in 11ac mode.
	 */
	arg->tx_mcs_set &= ~IEEE80211_VHT_MCS_SUPPORT_0_11_MASK;
	arg->tx_mcs_set |= IEEE80211_DISABLE_VHT_MCS_SUPPORT_0_11;

	अगर ((arg->tx_mcs_set & IEEE80211_VHT_MCS_NOT_SUPPORTED) ==
			IEEE80211_VHT_MCS_NOT_SUPPORTED)
		arg->peer_vht_caps &= ~IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE;

	/* TODO:  Check */
	arg->tx_max_mcs_nss = 0xFF;

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac vht peer %pM max_mpdu %d flags 0x%x\n",
		   sta->addr, arg->peer_max_mpdu, arg->peer_flags);

	/* TODO: rxnss_override */
पूर्ण

अटल व्योम ath11k_peer_assoc_h_he(काष्ठा ath11k *ar,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा ieee80211_sta *sta,
				   काष्ठा peer_assoc_params *arg)
अणु
	स्थिर काष्ठा ieee80211_sta_he_cap *he_cap = &sta->he_cap;
	u8 ampdu_factor;
	u16 v;

	अगर (!he_cap->has_he)
		वापस;

	arg->he_flag = true;

	स_नकल(&arg->peer_he_cap_macinfo, he_cap->he_cap_elem.mac_cap_info,
	       माप(arg->peer_he_cap_macinfo));
	स_नकल(&arg->peer_he_cap_phyinfo, he_cap->he_cap_elem.phy_cap_info,
	       माप(arg->peer_he_cap_phyinfo));
	arg->peer_he_ops = vअगर->bss_conf.he_oper.params;

	/* the top most byte is used to indicate BSS color info */
	arg->peer_he_ops &= 0xffffff;

	/* As per section 26.6.1 11ax Draft5.0, अगर the Max AMPDU Exponent Extension
	 * in HE cap is zero, use the arg->peer_max_mpdu as calculated जबतक parsing
	 * VHT caps(अगर VHT caps is present) or HT caps (अगर VHT caps is not present).
	 *
	 * For non-zero value of Max AMPDU Extponent Extension in HE MAC caps,
	 * अगर a HE STA sends VHT cap and HE cap IE in assoc request then, use
	 * MAX_AMPDU_LEN_FACTOR as 20 to calculate max_ampdu length.
	 * If a HE STA that करोes not send VHT cap, but HE and HT cap in assoc
	 * request, then use MAX_AMPDU_LEN_FACTOR as 16 to calculate max_ampdu
	 * length.
	 */
	ampdu_factor = u8_get_bits(he_cap->he_cap_elem.mac_cap_info[3],
				   IEEE80211_HE_MAC_CAP3_MAX_AMPDU_LEN_EXP_MASK);

	अगर (ampdu_factor) अणु
		अगर (sta->vht_cap.vht_supported)
			arg->peer_max_mpdu = (1 << (IEEE80211_HE_VHT_MAX_AMPDU_FACTOR +
						    ampdu_factor)) - 1;
		अन्यथा अगर (sta->ht_cap.ht_supported)
			arg->peer_max_mpdu = (1 << (IEEE80211_HE_HT_MAX_AMPDU_FACTOR +
						    ampdu_factor)) - 1;
	पूर्ण

	अगर (he_cap->he_cap_elem.phy_cap_info[6] &
	    IEEE80211_HE_PHY_CAP6_PPE_THRESHOLD_PRESENT) अणु
		पूर्णांक bit = 7;
		पूर्णांक nss, ru;

		arg->peer_ppet.numss_m1 = he_cap->ppe_thres[0] &
					  IEEE80211_PPE_THRES_NSS_MASK;
		arg->peer_ppet.ru_bit_mask =
			(he_cap->ppe_thres[0] &
			 IEEE80211_PPE_THRES_RU_INDEX_BITMASK_MASK) >>
			IEEE80211_PPE_THRES_RU_INDEX_BITMASK_POS;

		क्रम (nss = 0; nss <= arg->peer_ppet.numss_m1; nss++) अणु
			क्रम (ru = 0; ru < 4; ru++) अणु
				u32 val = 0;
				पूर्णांक i;

				अगर ((arg->peer_ppet.ru_bit_mask & BIT(ru)) == 0)
					जारी;
				क्रम (i = 0; i < 6; i++) अणु
					val >>= 1;
					val |= ((he_cap->ppe_thres[bit / 8] >>
						 (bit % 8)) & 0x1) << 5;
					bit++;
				पूर्ण
				arg->peer_ppet.ppet16_ppet8_ru3_ru0[nss] |=
								val << (ru * 6);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (he_cap->he_cap_elem.mac_cap_info[0] & IEEE80211_HE_MAC_CAP0_TWT_RES)
		arg->twt_responder = true;
	अगर (he_cap->he_cap_elem.mac_cap_info[0] & IEEE80211_HE_MAC_CAP0_TWT_REQ)
		arg->twt_requester = true;

	चयन (sta->bandwidth) अणु
	हाल IEEE80211_STA_RX_BW_160:
		अगर (he_cap->he_cap_elem.phy_cap_info[0] &
		    IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G) अणु
			v = le16_to_cpu(he_cap->he_mcs_nss_supp.rx_mcs_80p80);
			arg->peer_he_rx_mcs_set[WMI_HECAP_TXRX_MCS_NSS_IDX_80_80] = v;

			v = le16_to_cpu(he_cap->he_mcs_nss_supp.tx_mcs_80p80);
			arg->peer_he_tx_mcs_set[WMI_HECAP_TXRX_MCS_NSS_IDX_80_80] = v;

			arg->peer_he_mcs_count++;
		पूर्ण
		v = le16_to_cpu(he_cap->he_mcs_nss_supp.rx_mcs_160);
		arg->peer_he_rx_mcs_set[WMI_HECAP_TXRX_MCS_NSS_IDX_160] = v;

		v = le16_to_cpu(he_cap->he_mcs_nss_supp.tx_mcs_160);
		arg->peer_he_tx_mcs_set[WMI_HECAP_TXRX_MCS_NSS_IDX_160] = v;

		arg->peer_he_mcs_count++;
		fallthrough;

	शेष:
		v = le16_to_cpu(he_cap->he_mcs_nss_supp.rx_mcs_80);
		arg->peer_he_rx_mcs_set[WMI_HECAP_TXRX_MCS_NSS_IDX_80] = v;

		v = le16_to_cpu(he_cap->he_mcs_nss_supp.tx_mcs_80);
		arg->peer_he_tx_mcs_set[WMI_HECAP_TXRX_MCS_NSS_IDX_80] = v;

		arg->peer_he_mcs_count++;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ath11k_peer_assoc_h_smps(काष्ठा ieee80211_sta *sta,
				     काष्ठा peer_assoc_params *arg)
अणु
	स्थिर काष्ठा ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
	पूर्णांक smps;

	अगर (!ht_cap->ht_supported)
		वापस;

	smps = ht_cap->cap & IEEE80211_HT_CAP_SM_PS;
	smps >>= IEEE80211_HT_CAP_SM_PS_SHIFT;

	चयन (smps) अणु
	हाल WLAN_HT_CAP_SM_PS_STATIC:
		arg->अटल_mimops_flag = true;
		अवरोध;
	हाल WLAN_HT_CAP_SM_PS_DYNAMIC:
		arg->dynamic_mimops_flag = true;
		अवरोध;
	हाल WLAN_HT_CAP_SM_PS_DISABLED:
		arg->spatial_mux_flag = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ath11k_peer_assoc_h_qos(काष्ठा ath11k *ar,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_sta *sta,
				    काष्ठा peer_assoc_params *arg)
अणु
	काष्ठा ath11k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;

	चयन (arvअगर->vdev_type) अणु
	हाल WMI_VDEV_TYPE_AP:
		अगर (sta->wme) अणु
			/* TODO: Check WME vs QoS */
			arg->is_wme_set = true;
			arg->qos_flag = true;
		पूर्ण

		अगर (sta->wme && sta->uapsd_queues) अणु
			/* TODO: Check WME vs QoS */
			arg->is_wme_set = true;
			arg->apsd_flag = true;
			arg->peer_rate_caps |= WMI_HOST_RC_UAPSD_FLAG;
		पूर्ण
		अवरोध;
	हाल WMI_VDEV_TYPE_STA:
		अगर (sta->wme) अणु
			arg->is_wme_set = true;
			arg->qos_flag = true;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac peer %pM qos %d\n",
		   sta->addr, arg->qos_flag);
पूर्ण

अटल पूर्णांक ath11k_peer_assoc_qos_ap(काष्ठा ath11k *ar,
				    काष्ठा ath11k_vअगर *arvअगर,
				    काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ap_ps_params params;
	u32 max_sp;
	u32 uapsd;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	params.vdev_id = arvअगर->vdev_id;

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac uapsd_queues 0x%x max_sp %d\n",
		   sta->uapsd_queues, sta->max_sp);

	uapsd = 0;
	अगर (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VO)
		uapsd |= WMI_AP_PS_UAPSD_AC3_DELIVERY_EN |
			 WMI_AP_PS_UAPSD_AC3_TRIGGER_EN;
	अगर (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_VI)
		uapsd |= WMI_AP_PS_UAPSD_AC2_DELIVERY_EN |
			 WMI_AP_PS_UAPSD_AC2_TRIGGER_EN;
	अगर (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BK)
		uapsd |= WMI_AP_PS_UAPSD_AC1_DELIVERY_EN |
			 WMI_AP_PS_UAPSD_AC1_TRIGGER_EN;
	अगर (sta->uapsd_queues & IEEE80211_WMM_IE_STA_QOSINFO_AC_BE)
		uapsd |= WMI_AP_PS_UAPSD_AC0_DELIVERY_EN |
			 WMI_AP_PS_UAPSD_AC0_TRIGGER_EN;

	max_sp = 0;
	अगर (sta->max_sp < MAX_WMI_AP_PS_PEER_PARAM_MAX_SP)
		max_sp = sta->max_sp;

	params.param = WMI_AP_PS_PEER_PARAM_UAPSD;
	params.value = uapsd;
	ret = ath11k_wmi_send_set_ap_ps_param_cmd(ar, sta->addr, &params);
	अगर (ret)
		जाओ err;

	params.param = WMI_AP_PS_PEER_PARAM_MAX_SP;
	params.value = max_sp;
	ret = ath11k_wmi_send_set_ap_ps_param_cmd(ar, sta->addr, &params);
	अगर (ret)
		जाओ err;

	/* TODO revisit during testing */
	params.param = WMI_AP_PS_PEER_PARAM_SIFS_RESP_FRMTYPE;
	params.value = DISABLE_SIFS_RESPONSE_TRIGGER;
	ret = ath11k_wmi_send_set_ap_ps_param_cmd(ar, sta->addr, &params);
	अगर (ret)
		जाओ err;

	params.param = WMI_AP_PS_PEER_PARAM_SIFS_RESP_UAPSD;
	params.value = DISABLE_SIFS_RESPONSE_TRIGGER;
	ret = ath11k_wmi_send_set_ap_ps_param_cmd(ar, sta->addr, &params);
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	ath11k_warn(ar->ab, "failed to set ap ps peer param %d for vdev %i: %d\n",
		    params.param, arvअगर->vdev_id, ret);
	वापस ret;
पूर्ण

अटल bool ath11k_mac_sta_has_ofdm_only(काष्ठा ieee80211_sta *sta)
अणु
	वापस sta->supp_rates[NL80211_BAND_2GHZ] >>
	       ATH11K_MAC_FIRST_OFDM_RATE_IDX;
पूर्ण

अटल क्रमागत wmi_phy_mode ath11k_mac_get_phymode_vht(काष्ठा ath11k *ar,
						    काष्ठा ieee80211_sta *sta)
अणु
	अगर (sta->bandwidth == IEEE80211_STA_RX_BW_160) अणु
		चयन (sta->vht_cap.cap &
			IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK) अणु
		हाल IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ:
			वापस MODE_11AC_VHT160;
		हाल IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ:
			वापस MODE_11AC_VHT80_80;
		शेष:
			/* not sure अगर this is a valid हाल? */
			वापस MODE_11AC_VHT160;
		पूर्ण
	पूर्ण

	अगर (sta->bandwidth == IEEE80211_STA_RX_BW_80)
		वापस MODE_11AC_VHT80;

	अगर (sta->bandwidth == IEEE80211_STA_RX_BW_40)
		वापस MODE_11AC_VHT40;

	अगर (sta->bandwidth == IEEE80211_STA_RX_BW_20)
		वापस MODE_11AC_VHT20;

	वापस MODE_UNKNOWN;
पूर्ण

अटल क्रमागत wmi_phy_mode ath11k_mac_get_phymode_he(काष्ठा ath11k *ar,
						   काष्ठा ieee80211_sta *sta)
अणु
	अगर (sta->bandwidth == IEEE80211_STA_RX_BW_160) अणु
		अगर (sta->he_cap.he_cap_elem.phy_cap_info[0] &
		     IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_160MHZ_IN_5G)
			वापस MODE_11AX_HE160;
		अन्यथा अगर (sta->he_cap.he_cap_elem.phy_cap_info[0] &
		     IEEE80211_HE_PHY_CAP0_CHANNEL_WIDTH_SET_80PLUS80_MHZ_IN_5G)
			वापस MODE_11AX_HE80_80;
		/* not sure अगर this is a valid हाल? */
		वापस MODE_11AX_HE160;
	पूर्ण

	अगर (sta->bandwidth == IEEE80211_STA_RX_BW_80)
		वापस MODE_11AX_HE80;

	अगर (sta->bandwidth == IEEE80211_STA_RX_BW_40)
		वापस MODE_11AX_HE40;

	अगर (sta->bandwidth == IEEE80211_STA_RX_BW_20)
		वापस MODE_11AX_HE20;

	वापस MODE_UNKNOWN;
पूर्ण

अटल व्योम ath11k_peer_assoc_h_phymode(काष्ठा ath11k *ar,
					काष्ठा ieee80211_vअगर *vअगर,
					काष्ठा ieee80211_sta *sta,
					काष्ठा peer_assoc_params *arg)
अणु
	काष्ठा ath11k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा cfg80211_chan_def def;
	क्रमागत nl80211_band band;
	स्थिर u8 *ht_mcs_mask;
	स्थिर u16 *vht_mcs_mask;
	क्रमागत wmi_phy_mode phymode = MODE_UNKNOWN;

	अगर (WARN_ON(ath11k_mac_vअगर_chan(vअगर, &def)))
		वापस;

	band = def.chan->band;
	ht_mcs_mask = arvअगर->bitrate_mask.control[band].ht_mcs;
	vht_mcs_mask = arvअगर->bitrate_mask.control[band].vht_mcs;

	चयन (band) अणु
	हाल NL80211_BAND_2GHZ:
		अगर (sta->he_cap.has_he) अणु
			अगर (sta->bandwidth == IEEE80211_STA_RX_BW_80)
				phymode = MODE_11AX_HE80_2G;
			अन्यथा अगर (sta->bandwidth == IEEE80211_STA_RX_BW_40)
				phymode = MODE_11AX_HE40_2G;
			अन्यथा
				phymode = MODE_11AX_HE20_2G;
		पूर्ण अन्यथा अगर (sta->vht_cap.vht_supported &&
		    !ath11k_peer_assoc_h_vht_masked(vht_mcs_mask)) अणु
			अगर (sta->bandwidth == IEEE80211_STA_RX_BW_40)
				phymode = MODE_11AC_VHT40;
			अन्यथा
				phymode = MODE_11AC_VHT20;
		पूर्ण अन्यथा अगर (sta->ht_cap.ht_supported &&
			   !ath11k_peer_assoc_h_ht_masked(ht_mcs_mask)) अणु
			अगर (sta->bandwidth == IEEE80211_STA_RX_BW_40)
				phymode = MODE_11NG_HT40;
			अन्यथा
				phymode = MODE_11NG_HT20;
		पूर्ण अन्यथा अगर (ath11k_mac_sta_has_ofdm_only(sta)) अणु
			phymode = MODE_11G;
		पूर्ण अन्यथा अणु
			phymode = MODE_11B;
		पूर्ण
		अवरोध;
	हाल NL80211_BAND_5GHZ:
	हाल NL80211_BAND_6GHZ:
		/* Check HE first */
		अगर (sta->he_cap.has_he) अणु
			phymode = ath11k_mac_get_phymode_he(ar, sta);
		पूर्ण अन्यथा अगर (sta->vht_cap.vht_supported &&
		    !ath11k_peer_assoc_h_vht_masked(vht_mcs_mask)) अणु
			phymode = ath11k_mac_get_phymode_vht(ar, sta);
		पूर्ण अन्यथा अगर (sta->ht_cap.ht_supported &&
			   !ath11k_peer_assoc_h_ht_masked(ht_mcs_mask)) अणु
			अगर (sta->bandwidth >= IEEE80211_STA_RX_BW_40)
				phymode = MODE_11NA_HT40;
			अन्यथा
				phymode = MODE_11NA_HT20;
		पूर्ण अन्यथा अणु
			phymode = MODE_11A;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac peer %pM phymode %s\n",
		   sta->addr, ath11k_wmi_phymode_str(phymode));

	arg->peer_phymode = phymode;
	WARN_ON(phymode == MODE_UNKNOWN);
पूर्ण

अटल व्योम ath11k_peer_assoc_prepare(काष्ठा ath11k *ar,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा ieee80211_sta *sta,
				      काष्ठा peer_assoc_params *arg,
				      bool reassoc)
अणु
	lockdep_निश्चित_held(&ar->conf_mutex);

	स_रखो(arg, 0, माप(*arg));

	reinit_completion(&ar->peer_assoc_करोne);

	arg->peer_new_assoc = !reassoc;
	ath11k_peer_assoc_h_basic(ar, vअगर, sta, arg);
	ath11k_peer_assoc_h_crypto(ar, vअगर, sta, arg);
	ath11k_peer_assoc_h_rates(ar, vअगर, sta, arg);
	ath11k_peer_assoc_h_ht(ar, vअगर, sta, arg);
	ath11k_peer_assoc_h_vht(ar, vअगर, sta, arg);
	ath11k_peer_assoc_h_he(ar, vअगर, sta, arg);
	ath11k_peer_assoc_h_qos(ar, vअगर, sta, arg);
	ath11k_peer_assoc_h_phymode(ar, vअगर, sta, arg);
	ath11k_peer_assoc_h_smps(sta, arg);

	/* TODO: amsdu_disable req? */
पूर्ण

अटल पूर्णांक ath11k_setup_peer_smps(काष्ठा ath11k *ar, काष्ठा ath11k_vअगर *arvअगर,
				  स्थिर u8 *addr,
				  स्थिर काष्ठा ieee80211_sta_ht_cap *ht_cap)
अणु
	पूर्णांक smps;

	अगर (!ht_cap->ht_supported)
		वापस 0;

	smps = ht_cap->cap & IEEE80211_HT_CAP_SM_PS;
	smps >>= IEEE80211_HT_CAP_SM_PS_SHIFT;

	अगर (smps >= ARRAY_SIZE(ath11k_smps_map))
		वापस -EINVAL;

	वापस ath11k_wmi_set_peer_param(ar, addr, arvअगर->vdev_id,
					 WMI_PEER_MIMO_PS_STATE,
					 ath11k_smps_map[smps]);
पूर्ण

अटल व्योम ath11k_bss_assoc(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_bss_conf *bss_conf)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ath11k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा peer_assoc_params peer_arg;
	काष्ठा ieee80211_sta *ap_sta;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac vdev %i assoc bssid %pM aid %d\n",
		   arvअगर->vdev_id, arvअगर->bssid, arvअगर->aid);

	rcu_पढ़ो_lock();

	ap_sta = ieee80211_find_sta(vअगर, bss_conf->bssid);
	अगर (!ap_sta) अणु
		ath11k_warn(ar->ab, "failed to find station entry for bss %pM vdev %i\n",
			    bss_conf->bssid, arvअगर->vdev_id);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	ath11k_peer_assoc_prepare(ar, vअगर, ap_sta, &peer_arg, false);

	rcu_पढ़ो_unlock();

	ret = ath11k_wmi_send_peer_assoc_cmd(ar, &peer_arg);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to run peer assoc for %pM vdev %i: %d\n",
			    bss_conf->bssid, arvअगर->vdev_id, ret);
		वापस;
	पूर्ण

	अगर (!रुको_क्रम_completion_समयout(&ar->peer_assoc_करोne, 1 * HZ)) अणु
		ath11k_warn(ar->ab, "failed to get peer assoc conf event for %pM vdev %i\n",
			    bss_conf->bssid, arvअगर->vdev_id);
		वापस;
	पूर्ण

	ret = ath11k_setup_peer_smps(ar, arvअगर, bss_conf->bssid,
				     &ap_sta->ht_cap);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to setup peer SMPS for vdev %d: %d\n",
			    arvअगर->vdev_id, ret);
		वापस;
	पूर्ण

	WARN_ON(arvअगर->is_up);

	arvअगर->aid = bss_conf->aid;
	ether_addr_copy(arvअगर->bssid, bss_conf->bssid);

	ret = ath11k_wmi_vdev_up(ar, arvअगर->vdev_id, arvअगर->aid, arvअगर->bssid);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to set vdev %d up: %d\n",
			    arvअगर->vdev_id, ret);
		वापस;
	पूर्ण

	arvअगर->is_up = true;

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
		   "mac vdev %d up (associated) bssid %pM aid %d\n",
		   arvअगर->vdev_id, bss_conf->bssid, bss_conf->aid);

	/* Authorize BSS Peer */
	ret = ath11k_wmi_set_peer_param(ar, arvअगर->bssid,
					arvअगर->vdev_id,
					WMI_PEER_AUTHORIZE,
					1);
	अगर (ret)
		ath11k_warn(ar->ab, "Unable to authorize BSS peer: %d\n", ret);

	ret = ath11k_wmi_send_obss_spr_cmd(ar, arvअगर->vdev_id,
					   &bss_conf->he_obss_pd);
	अगर (ret)
		ath11k_warn(ar->ab, "failed to set vdev %i OBSS PD parameters: %d\n",
			    arvअगर->vdev_id, ret);
पूर्ण

अटल व्योम ath11k_bss_disassoc(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ath11k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac vdev %i disassoc bssid %pM\n",
		   arvअगर->vdev_id, arvअगर->bssid);

	ret = ath11k_wmi_vdev_करोwn(ar, arvअगर->vdev_id);
	अगर (ret)
		ath11k_warn(ar->ab, "failed to down vdev %i: %d\n",
			    arvअगर->vdev_id, ret);

	arvअगर->is_up = false;

	cancel_delayed_work_sync(&arvअगर->connection_loss_work);
पूर्ण

अटल u32 ath11k_mac_get_rate_hw_value(पूर्णांक bitrate)
अणु
	u32 preamble;
	u16 hw_value;
	पूर्णांक rate;
	माप_प्रकार i;

	अगर (ath11k_mac_bitrate_is_cck(bitrate))
		preamble = WMI_RATE_PREAMBLE_CCK;
	अन्यथा
		preamble = WMI_RATE_PREAMBLE_OFDM;

	क्रम (i = 0; i < ARRAY_SIZE(ath11k_legacy_rates); i++) अणु
		अगर (ath11k_legacy_rates[i].bitrate != bitrate)
			जारी;

		hw_value = ath11k_legacy_rates[i].hw_value;
		rate = ATH11K_HW_RATE_CODE(hw_value, 0, preamble);

		वापस rate;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम ath11k_recalculate_mgmt_rate(काष्ठा ath11k *ar,
					 काष्ठा ieee80211_vअगर *vअगर,
					 काष्ठा cfg80211_chan_def *def)
अणु
	काष्ठा ath11k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	स्थिर काष्ठा ieee80211_supported_band *sband;
	u8 basic_rate_idx;
	पूर्णांक hw_rate_code;
	u32 vdev_param;
	u16 bitrate;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	sband = ar->hw->wiphy->bands[def->chan->band];
	basic_rate_idx = ffs(vअगर->bss_conf.basic_rates) - 1;
	bitrate = sband->bitrates[basic_rate_idx].bitrate;

	hw_rate_code = ath11k_mac_get_rate_hw_value(bitrate);
	अगर (hw_rate_code < 0) अणु
		ath11k_warn(ar->ab, "bitrate not supported %d\n", bitrate);
		वापस;
	पूर्ण

	vdev_param = WMI_VDEV_PARAM_MGMT_RATE;
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id, vdev_param,
					    hw_rate_code);
	अगर (ret)
		ath11k_warn(ar->ab, "failed to set mgmt tx rate %d\n", ret);

	vdev_param = WMI_VDEV_PARAM_BEACON_RATE;
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id, vdev_param,
					    hw_rate_code);
	अगर (ret)
		ath11k_warn(ar->ab, "failed to set beacon tx rate %d\n", ret);
पूर्ण

अटल पूर्णांक ath11k_mac_fils_discovery(काष्ठा ath11k_vअगर *arvअगर,
				     काष्ठा ieee80211_bss_conf *info)
अणु
	काष्ठा ath11k *ar = arvअगर->ar;
	काष्ठा sk_buff *पंचांगpl;
	पूर्णांक ret;
	u32 पूर्णांकerval;
	bool unsol_bcast_probe_resp_enabled = false;

	अगर (info->fils_discovery.max_पूर्णांकerval) अणु
		पूर्णांकerval = info->fils_discovery.max_पूर्णांकerval;

		पंचांगpl = ieee80211_get_fils_discovery_पंचांगpl(ar->hw, arvअगर->vअगर);
		अगर (पंचांगpl)
			ret = ath11k_wmi_fils_discovery_पंचांगpl(ar, arvअगर->vdev_id,
							     पंचांगpl);
	पूर्ण अन्यथा अगर (info->unsol_bcast_probe_resp_पूर्णांकerval) अणु
		unsol_bcast_probe_resp_enabled = 1;
		पूर्णांकerval = info->unsol_bcast_probe_resp_पूर्णांकerval;

		पंचांगpl = ieee80211_get_unsol_bcast_probe_resp_पंचांगpl(ar->hw,
								 arvअगर->vअगर);
		अगर (पंचांगpl)
			ret = ath11k_wmi_probe_resp_पंचांगpl(ar, arvअगर->vdev_id,
							 पंचांगpl);
	पूर्ण अन्यथा अणु /* Disable */
		वापस ath11k_wmi_fils_discovery(ar, arvअगर->vdev_id, 0, false);
	पूर्ण

	अगर (!पंचांगpl) अणु
		ath11k_warn(ar->ab,
			    "mac vdev %i failed to retrieve %s template\n",
			    arvअगर->vdev_id, (unsol_bcast_probe_resp_enabled ?
			    "unsolicited broadcast probe response" :
			    "FILS discovery"));
		वापस -EPERM;
	पूर्ण
	kमुक्त_skb(पंचांगpl);

	अगर (!ret)
		ret = ath11k_wmi_fils_discovery(ar, arvअगर->vdev_id, पूर्णांकerval,
						unsol_bcast_probe_resp_enabled);

	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_mac_config_obss_pd(काष्ठा ath11k *ar,
				     काष्ठा ieee80211_he_obss_pd *he_obss_pd)
अणु
	u32 biपंचांगap[2], param_id, param_val, pdev_id;
	पूर्णांक ret;
	s8 non_srg_th = 0, srg_th = 0;

	pdev_id = ar->pdev->pdev_id;

	/* Set and enable SRG/non-SRG OBSS PD Threshold */
	param_id = WMI_PDEV_PARAM_SET_CMD_OBSS_PD_THRESHOLD;
	अगर (test_bit(ATH11K_FLAG_MONITOR_ENABLED, &ar->monitor_flags)) अणु
		ret = ath11k_wmi_pdev_set_param(ar, param_id, 0, pdev_id);
		अगर (ret)
			ath11k_warn(ar->ab,
				    "failed to set obss_pd_threshold for pdev: %u\n",
				    pdev_id);
		वापस ret;
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
		   "mac obss pd sr_ctrl %x non_srg_thres %u srg_max %u\n",
		   he_obss_pd->sr_ctrl, he_obss_pd->non_srg_max_offset,
		   he_obss_pd->max_offset);

	param_val = 0;

	अगर (he_obss_pd->sr_ctrl &
	    IEEE80211_HE_SPR_NON_SRG_OBSS_PD_SR_DISALLOWED) अणु
		non_srg_th = ATH11K_OBSS_PD_MAX_THRESHOLD;
	पूर्ण अन्यथा अणु
		अगर (he_obss_pd->sr_ctrl & IEEE80211_HE_SPR_NON_SRG_OFFSET_PRESENT)
			non_srg_th = (ATH11K_OBSS_PD_MAX_THRESHOLD +
				      he_obss_pd->non_srg_max_offset);
		अन्यथा
			non_srg_th = ATH11K_OBSS_PD_NON_SRG_MAX_THRESHOLD;

		param_val |= ATH11K_OBSS_PD_NON_SRG_EN;
	पूर्ण

	अगर (he_obss_pd->sr_ctrl & IEEE80211_HE_SPR_SRG_INFORMATION_PRESENT) अणु
		srg_th = ATH11K_OBSS_PD_MAX_THRESHOLD + he_obss_pd->max_offset;
		param_val |= ATH11K_OBSS_PD_SRG_EN;
	पूर्ण

	अगर (test_bit(WMI_TLV_SERVICE_SRG_SRP_SPATIAL_REUSE_SUPPORT,
		     ar->ab->wmi_ab.svc_map)) अणु
		param_val |= ATH11K_OBSS_PD_THRESHOLD_IN_DBM;
		param_val |= FIELD_PREP(GENMASK(15, 8), srg_th);
	पूर्ण अन्यथा अणु
		non_srg_th -= ATH11K_DEFAULT_NOISE_FLOOR;
		/* SRG not supported and threshold in dB */
		param_val &= ~(ATH11K_OBSS_PD_SRG_EN |
			       ATH11K_OBSS_PD_THRESHOLD_IN_DBM);
	पूर्ण

	param_val |= (non_srg_th & GENMASK(7, 0));
	ret = ath11k_wmi_pdev_set_param(ar, param_id, param_val, pdev_id);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to set obss_pd_threshold for pdev: %u\n",
			    pdev_id);
		वापस ret;
	पूर्ण

	/* Enable OBSS PD क्रम all access category */
	param_id  = WMI_PDEV_PARAM_SET_CMD_OBSS_PD_PER_AC;
	param_val = 0xf;
	ret = ath11k_wmi_pdev_set_param(ar, param_id, param_val, pdev_id);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to set obss_pd_per_ac for pdev: %u\n",
			    pdev_id);
		वापस ret;
	पूर्ण

	/* Set SR Prohibit */
	param_id  = WMI_PDEV_PARAM_ENABLE_SR_PROHIBIT;
	param_val = !!(he_obss_pd->sr_ctrl &
		       IEEE80211_HE_SPR_HESIGA_SR_VAL15_ALLOWED);
	ret = ath11k_wmi_pdev_set_param(ar, param_id, param_val, pdev_id);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to set sr_prohibit for pdev: %u\n",
			    pdev_id);
		वापस ret;
	पूर्ण

	अगर (!test_bit(WMI_TLV_SERVICE_SRG_SRP_SPATIAL_REUSE_SUPPORT,
		      ar->ab->wmi_ab.svc_map))
		वापस 0;

	/* Set SRG BSS Color Biपंचांगap */
	स_नकल(biपंचांगap, he_obss_pd->bss_color_biपंचांगap, माप(biपंचांगap));
	ret = ath11k_wmi_pdev_set_srg_bss_color_biपंचांगap(ar, biपंचांगap);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to set bss_color_bitmap for pdev: %u\n",
			    pdev_id);
		वापस ret;
	पूर्ण

	/* Set SRG Partial BSSID Biपंचांगap */
	स_नकल(biपंचांगap, he_obss_pd->partial_bssid_biपंचांगap, माप(biपंचांगap));
	ret = ath11k_wmi_pdev_set_srg_patial_bssid_biपंचांगap(ar, biपंचांगap);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to set partial_bssid_bitmap for pdev: %u\n",
			    pdev_id);
		वापस ret;
	पूर्ण

	स_रखो(biपंचांगap, 0xff, माप(biपंचांगap));

	/* Enable all BSS Colors क्रम SRG */
	ret = ath11k_wmi_pdev_srg_obss_color_enable_biपंचांगap(ar, biपंचांगap);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to set srg_color_en_bitmap pdev: %u\n",
			    pdev_id);
		वापस ret;
	पूर्ण

	/* Enable all patial BSSID mask क्रम SRG */
	ret = ath11k_wmi_pdev_srg_obss_bssid_enable_biपंचांगap(ar, biपंचांगap);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to set srg_bssid_en_bitmap pdev: %u\n",
			    pdev_id);
		वापस ret;
	पूर्ण

	/* Enable all BSS Colors क्रम non-SRG */
	ret = ath11k_wmi_pdev_non_srg_obss_color_enable_biपंचांगap(ar, biपंचांगap);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to set non_srg_color_en_bitmap pdev: %u\n",
			    pdev_id);
		वापस ret;
	पूर्ण

	/* Enable all patial BSSID mask क्रम non-SRG */
	ret = ath11k_wmi_pdev_non_srg_obss_bssid_enable_biपंचांगap(ar, biपंचांगap);
	अगर (ret) अणु
		ath11k_warn(ar->ab,
			    "failed to set non_srg_bssid_en_bitmap pdev: %u\n",
			    pdev_id);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath11k_mac_op_bss_info_changed(काष्ठा ieee80211_hw *hw,
					   काष्ठा ieee80211_vअगर *vअगर,
					   काष्ठा ieee80211_bss_conf *info,
					   u32 changed)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ath11k_vअगर *arvअगर = ath11k_vअगर_to_arvअगर(vअगर);
	काष्ठा cfg80211_chan_def def;
	u32 param_id, param_value;
	क्रमागत nl80211_band band;
	u32 vdev_param;
	पूर्णांक mcast_rate;
	u32 preamble;
	u16 hw_value;
	u16 bitrate;
	पूर्णांक ret = 0;
	u8 rateidx;
	u32 rate;

	mutex_lock(&ar->conf_mutex);

	अगर (changed & BSS_CHANGED_BEACON_INT) अणु
		arvअगर->beacon_पूर्णांकerval = info->beacon_पूर्णांक;

		param_id = WMI_VDEV_PARAM_BEACON_INTERVAL;
		ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
						    param_id,
						    arvअगर->beacon_पूर्णांकerval);
		अगर (ret)
			ath11k_warn(ar->ab, "Failed to set beacon interval for VDEV: %d\n",
				    arvअगर->vdev_id);
		अन्यथा
			ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
				   "Beacon interval: %d set for VDEV: %d\n",
				   arvअगर->beacon_पूर्णांकerval, arvअगर->vdev_id);
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON) अणु
		param_id = WMI_PDEV_PARAM_BEACON_TX_MODE;
		param_value = WMI_BEACON_STAGGERED_MODE;
		ret = ath11k_wmi_pdev_set_param(ar, param_id,
						param_value, ar->pdev->pdev_id);
		अगर (ret)
			ath11k_warn(ar->ab, "Failed to set beacon mode for VDEV: %d\n",
				    arvअगर->vdev_id);
		अन्यथा
			ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
				   "Set staggered beacon mode for VDEV: %d\n",
				   arvअगर->vdev_id);

		ret = ath11k_mac_setup_bcn_पंचांगpl(arvअगर);
		अगर (ret)
			ath11k_warn(ar->ab, "failed to update bcn template: %d\n",
				    ret);
	पूर्ण

	अगर (changed & (BSS_CHANGED_BEACON_INFO | BSS_CHANGED_BEACON)) अणु
		arvअगर->dtim_period = info->dtim_period;

		param_id = WMI_VDEV_PARAM_DTIM_PERIOD;
		ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
						    param_id,
						    arvअगर->dtim_period);

		अगर (ret)
			ath11k_warn(ar->ab, "Failed to set dtim period for VDEV %d: %i\n",
				    arvअगर->vdev_id, ret);
		अन्यथा
			ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
				   "DTIM period: %d set for VDEV: %d\n",
				   arvअगर->dtim_period, arvअगर->vdev_id);
	पूर्ण

	अगर (changed & BSS_CHANGED_SSID &&
	    vअगर->type == NL80211_IFTYPE_AP) अणु
		arvअगर->u.ap.ssid_len = info->ssid_len;
		अगर (info->ssid_len)
			स_नकल(arvअगर->u.ap.ssid, info->ssid, info->ssid_len);
		arvअगर->u.ap.hidden_ssid = info->hidden_ssid;
	पूर्ण

	अगर (changed & BSS_CHANGED_BSSID && !is_zero_ether_addr(info->bssid))
		ether_addr_copy(arvअगर->bssid, info->bssid);

	अगर (changed & BSS_CHANGED_BEACON_ENABLED) अणु
		ath11k_control_beaconing(arvअगर, info);

		अगर (arvअगर->is_up && vअगर->bss_conf.he_support &&
		    vअगर->bss_conf.he_oper.params) अणु
			ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
							    WMI_VDEV_PARAM_BA_MODE,
							    WMI_BA_MODE_BUFFER_SIZE_256);
			अगर (ret)
				ath11k_warn(ar->ab,
					    "failed to set BA BUFFER SIZE 256 for vdev: %d\n",
					    arvअगर->vdev_id);

			param_id = WMI_VDEV_PARAM_HEOPS_0_31;
			param_value = vअगर->bss_conf.he_oper.params;
			ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
							    param_id, param_value);
			ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
				   "he oper param: %x set for VDEV: %d\n",
				   param_value, arvअगर->vdev_id);

			अगर (ret)
				ath11k_warn(ar->ab, "Failed to set he oper params %x for VDEV %d: %i\n",
					    param_value, arvअगर->vdev_id, ret);
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_CTS_PROT) अणु
		u32 cts_prot;

		cts_prot = !!(info->use_cts_prot);
		param_id = WMI_VDEV_PARAM_PROTECTION_MODE;

		अगर (arvअगर->is_started) अणु
			ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
							    param_id, cts_prot);
			अगर (ret)
				ath11k_warn(ar->ab, "Failed to set CTS prot for VDEV: %d\n",
					    arvअगर->vdev_id);
			अन्यथा
				ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "Set CTS prot: %d for VDEV: %d\n",
					   cts_prot, arvअगर->vdev_id);
		पूर्ण अन्यथा अणु
			ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "defer protection mode setup, vdev is not ready yet\n");
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		u32 slotसमय;

		अगर (info->use_लघु_slot)
			slotसमय = WMI_VDEV_SLOT_TIME_SHORT; /* 9us */

		अन्यथा
			slotसमय = WMI_VDEV_SLOT_TIME_LONG; /* 20us */

		param_id = WMI_VDEV_PARAM_SLOT_TIME;
		ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
						    param_id, slotसमय);
		अगर (ret)
			ath11k_warn(ar->ab, "Failed to set erp slot for VDEV: %d\n",
				    arvअगर->vdev_id);
		अन्यथा
			ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
				   "Set slottime: %d for VDEV: %d\n",
				   slotसमय, arvअगर->vdev_id);
	पूर्ण

	अगर (changed & BSS_CHANGED_ERP_PREAMBLE) अणु
		u32 preamble;

		अगर (info->use_लघु_preamble)
			preamble = WMI_VDEV_PREAMBLE_SHORT;
		अन्यथा
			preamble = WMI_VDEV_PREAMBLE_LONG;

		param_id = WMI_VDEV_PARAM_PREAMBLE;
		ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
						    param_id, preamble);
		अगर (ret)
			ath11k_warn(ar->ab, "Failed to set preamble for VDEV: %d\n",
				    arvअगर->vdev_id);
		अन्यथा
			ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
				   "Set preamble: %d for VDEV: %d\n",
				   preamble, arvअगर->vdev_id);
	पूर्ण

	अगर (changed & BSS_CHANGED_ASSOC) अणु
		अगर (info->assoc)
			ath11k_bss_assoc(hw, vअगर, info);
		अन्यथा
			ath11k_bss_disassoc(hw, vअगर);
	पूर्ण

	अगर (changed & BSS_CHANGED_TXPOWER) अणु
		ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac vdev_id %i txpower %d\n",
			   arvअगर->vdev_id, info->txघातer);

		arvअगर->txघातer = info->txघातer;
		ath11k_mac_txघातer_recalc(ar);
	पूर्ण

	अगर (changed & BSS_CHANGED_MCAST_RATE &&
	    !ath11k_mac_vअगर_chan(arvअगर->vअगर, &def)) अणु
		band = def.chan->band;
		mcast_rate = vअगर->bss_conf.mcast_rate[band];

		अगर (mcast_rate > 0)
			rateidx = mcast_rate - 1;
		अन्यथा
			rateidx = ffs(vअगर->bss_conf.basic_rates) - 1;

		अगर (ar->pdev->cap.supported_bands & WMI_HOST_WLAN_5G_CAP)
			rateidx += ATH11K_MAC_FIRST_OFDM_RATE_IDX;

		bitrate = ath11k_legacy_rates[rateidx].bitrate;
		hw_value = ath11k_legacy_rates[rateidx].hw_value;

		अगर (ath11k_mac_bitrate_is_cck(bitrate))
			preamble = WMI_RATE_PREAMBLE_CCK;
		अन्यथा
			preamble = WMI_RATE_PREAMBLE_OFDM;

		rate = ATH11K_HW_RATE_CODE(hw_value, 0, preamble);

		ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
			   "mac vdev %d mcast_rate %x\n",
			   arvअगर->vdev_id, rate);

		vdev_param = WMI_VDEV_PARAM_MCAST_DATA_RATE;
		ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
						    vdev_param, rate);
		अगर (ret)
			ath11k_warn(ar->ab,
				    "failed to set mcast rate on vdev %i: %d\n",
				    arvअगर->vdev_id,  ret);

		vdev_param = WMI_VDEV_PARAM_BCAST_DATA_RATE;
		ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
						    vdev_param, rate);
		अगर (ret)
			ath11k_warn(ar->ab,
				    "failed to set bcast rate on vdev %i: %d\n",
				    arvअगर->vdev_id,  ret);
	पूर्ण

	अगर (changed & BSS_CHANGED_BASIC_RATES &&
	    !ath11k_mac_vअगर_chan(arvअगर->vअगर, &def))
		ath11k_recalculate_mgmt_rate(ar, vअगर, &def);

	अगर (changed & BSS_CHANGED_TWT) अणु
		अगर (info->twt_requester || info->twt_responder)
			ath11k_wmi_send_twt_enable_cmd(ar, ar->pdev->pdev_id);
		अन्यथा
			ath11k_wmi_send_twt_disable_cmd(ar, ar->pdev->pdev_id);
	पूर्ण

	अगर (changed & BSS_CHANGED_HE_OBSS_PD)
		ath11k_mac_config_obss_pd(ar, &info->he_obss_pd);

	अगर (changed & BSS_CHANGED_HE_BSS_COLOR) अणु
		अगर (vअगर->type == NL80211_IFTYPE_AP) अणु
			ret = ath11k_wmi_send_obss_color_collision_cfg_cmd(
				ar, arvअगर->vdev_id, info->he_bss_color.color,
				ATH11K_BSS_COLOR_COLLISION_DETECTION_AP_PERIOD_MS,
				info->he_bss_color.enabled);
			अगर (ret)
				ath11k_warn(ar->ab, "failed to set bss color collision on vdev %i: %d\n",
					    arvअगर->vdev_id,  ret);
		पूर्ण अन्यथा अगर (vअगर->type == NL80211_IFTYPE_STATION) अणु
			ret = ath11k_wmi_send_bss_color_change_enable_cmd(ar,
									  arvअगर->vdev_id,
									  1);
			अगर (ret)
				ath11k_warn(ar->ab, "failed to enable bss color change on vdev %i: %d\n",
					    arvअगर->vdev_id,  ret);
			ret = ath11k_wmi_send_obss_color_collision_cfg_cmd(
				ar, arvअगर->vdev_id, 0,
				ATH11K_BSS_COLOR_COLLISION_DETECTION_STA_PERIOD_MS, 1);
			अगर (ret)
				ath11k_warn(ar->ab, "failed to set bss color collision on vdev %i: %d\n",
					    arvअगर->vdev_id,  ret);
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_FILS_DISCOVERY ||
	    changed & BSS_CHANGED_UNSOL_BCAST_PROBE_RESP)
		ath11k_mac_fils_discovery(arvअगर, info);

	mutex_unlock(&ar->conf_mutex);
पूर्ण

व्योम __ath11k_mac_scan_finish(काष्ठा ath11k *ar)
अणु
	lockdep_निश्चित_held(&ar->data_lock);

	चयन (ar->scan.state) अणु
	हाल ATH11K_SCAN_IDLE:
		अवरोध;
	हाल ATH11K_SCAN_RUNNING:
	हाल ATH11K_SCAN_ABORTING:
		अगर (!ar->scan.is_roc) अणु
			काष्ठा cfg80211_scan_info info = अणु
				.पातed = (ar->scan.state ==
					    ATH11K_SCAN_ABORTING),
			पूर्ण;

			ieee80211_scan_completed(ar->hw, &info);
		पूर्ण अन्यथा अगर (ar->scan.roc_notअगरy) अणु
			ieee80211_reमुख्य_on_channel_expired(ar->hw);
		पूर्ण
		fallthrough;
	हाल ATH11K_SCAN_STARTING:
		ar->scan.state = ATH11K_SCAN_IDLE;
		ar->scan_channel = शून्य;
		ar->scan.roc_freq = 0;
		cancel_delayed_work(&ar->scan.समयout);
		complete(&ar->scan.completed);
		अवरोध;
	पूर्ण
पूर्ण

व्योम ath11k_mac_scan_finish(काष्ठा ath11k *ar)
अणु
	spin_lock_bh(&ar->data_lock);
	__ath11k_mac_scan_finish(ar);
	spin_unlock_bh(&ar->data_lock);
पूर्ण

अटल पूर्णांक ath11k_scan_stop(काष्ठा ath11k *ar)
अणु
	काष्ठा scan_cancel_param arg = अणु
		.req_type = WLAN_SCAN_CANCEL_SINGLE,
		.scan_id = ATH11K_SCAN_ID,
	पूर्ण;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	/* TODO: Fill other STOP Params */
	arg.pdev_id = ar->pdev->pdev_id;

	ret = ath11k_wmi_send_scan_stop_cmd(ar, &arg);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to stop wmi scan: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = रुको_क्रम_completion_समयout(&ar->scan.completed, 3 * HZ);
	अगर (ret == 0) अणु
		ath11k_warn(ar->ab,
			    "failed to receive scan abort comple: timed out\n");
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अगर (ret > 0) अणु
		ret = 0;
	पूर्ण

out:
	/* Scan state should be updated upon scan completion but in हाल
	 * firmware fails to deliver the event (क्रम whatever reason) it is
	 * desired to clean up scan state anyway. Firmware may have just
	 * dropped the scan completion event delivery due to transport pipe
	 * being overflown with data and/or it can recover on its own beक्रमe
	 * next scan request is submitted.
	 */
	spin_lock_bh(&ar->data_lock);
	अगर (ar->scan.state != ATH11K_SCAN_IDLE)
		__ath11k_mac_scan_finish(ar);
	spin_unlock_bh(&ar->data_lock);

	वापस ret;
पूर्ण

अटल व्योम ath11k_scan_पात(काष्ठा ath11k *ar)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);

	चयन (ar->scan.state) अणु
	हाल ATH11K_SCAN_IDLE:
		/* This can happen अगर समयout worker kicked in and called
		 * पातion जबतक scan completion was being processed.
		 */
		अवरोध;
	हाल ATH11K_SCAN_STARTING:
	हाल ATH11K_SCAN_ABORTING:
		ath11k_warn(ar->ab, "refusing scan abortion due to invalid scan state: %d\n",
			    ar->scan.state);
		अवरोध;
	हाल ATH11K_SCAN_RUNNING:
		ar->scan.state = ATH11K_SCAN_ABORTING;
		spin_unlock_bh(&ar->data_lock);

		ret = ath11k_scan_stop(ar);
		अगर (ret)
			ath11k_warn(ar->ab, "failed to abort scan: %d\n", ret);

		spin_lock_bh(&ar->data_lock);
		अवरोध;
	पूर्ण

	spin_unlock_bh(&ar->data_lock);
पूर्ण

अटल व्योम ath11k_scan_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath11k *ar = container_of(work, काष्ठा ath11k,
					 scan.समयout.work);

	mutex_lock(&ar->conf_mutex);
	ath11k_scan_पात(ar);
	mutex_unlock(&ar->conf_mutex);
पूर्ण

अटल पूर्णांक ath11k_start_scan(काष्ठा ath11k *ar,
			     काष्ठा scan_req_params *arg)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (ath11k_spectral_get_mode(ar) == ATH11K_SPECTRAL_BACKGROUND)
		ath11k_spectral_reset_buffer(ar);

	ret = ath11k_wmi_send_scan_start_cmd(ar, arg);
	अगर (ret)
		वापस ret;

	ret = रुको_क्रम_completion_समयout(&ar->scan.started, 1 * HZ);
	अगर (ret == 0) अणु
		ret = ath11k_scan_stop(ar);
		अगर (ret)
			ath11k_warn(ar->ab, "failed to stop scan: %d\n", ret);

		वापस -ETIMEDOUT;
	पूर्ण

	/* If we failed to start the scan, वापस error code at
	 * this poपूर्णांक.  This is probably due to some issue in the
	 * firmware, but no need to wedge the driver due to that...
	 */
	spin_lock_bh(&ar->data_lock);
	अगर (ar->scan.state == ATH11K_SCAN_IDLE) अणु
		spin_unlock_bh(&ar->data_lock);
		वापस -EINVAL;
	पूर्ण
	spin_unlock_bh(&ar->data_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_mac_op_hw_scan(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_scan_request *hw_req)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ath11k_vअगर *arvअगर = ath11k_vअगर_to_arvअगर(vअगर);
	काष्ठा cfg80211_scan_request *req = &hw_req->req;
	काष्ठा scan_req_params arg;
	पूर्णांक ret = 0;
	पूर्णांक i;

	mutex_lock(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);
	चयन (ar->scan.state) अणु
	हाल ATH11K_SCAN_IDLE:
		reinit_completion(&ar->scan.started);
		reinit_completion(&ar->scan.completed);
		ar->scan.state = ATH11K_SCAN_STARTING;
		ar->scan.is_roc = false;
		ar->scan.vdev_id = arvअगर->vdev_id;
		ret = 0;
		अवरोध;
	हाल ATH11K_SCAN_STARTING:
	हाल ATH11K_SCAN_RUNNING:
	हाल ATH11K_SCAN_ABORTING:
		ret = -EBUSY;
		अवरोध;
	पूर्ण
	spin_unlock_bh(&ar->data_lock);

	अगर (ret)
		जाओ निकास;

	स_रखो(&arg, 0, माप(arg));
	ath11k_wmi_start_scan_init(ar, &arg);
	arg.vdev_id = arvअगर->vdev_id;
	arg.scan_id = ATH11K_SCAN_ID;

	अगर (req->ie_len) अणु
		arg.extraie.len = req->ie_len;
		arg.extraie.ptr = kzalloc(req->ie_len, GFP_KERNEL);
		स_नकल(arg.extraie.ptr, req->ie, req->ie_len);
	पूर्ण

	अगर (req->n_ssids) अणु
		arg.num_ssids = req->n_ssids;
		क्रम (i = 0; i < arg.num_ssids; i++) अणु
			arg.ssid[i].length  = req->ssids[i].ssid_len;
			स_नकल(&arg.ssid[i].ssid, req->ssids[i].ssid,
			       req->ssids[i].ssid_len);
		पूर्ण
	पूर्ण अन्यथा अणु
		arg.scan_flags |= WMI_SCAN_FLAG_PASSIVE;
	पूर्ण

	अगर (req->n_channels) अणु
		arg.num_chan = req->n_channels;
		क्रम (i = 0; i < arg.num_chan; i++)
			arg.chan_list[i] = req->channels[i]->center_freq;
	पूर्ण

	ret = ath11k_start_scan(ar, &arg);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to start hw scan: %d\n", ret);
		spin_lock_bh(&ar->data_lock);
		ar->scan.state = ATH11K_SCAN_IDLE;
		spin_unlock_bh(&ar->data_lock);
	पूर्ण

	/* Add a 200ms margin to account क्रम event/command processing */
	ieee80211_queue_delayed_work(ar->hw, &ar->scan.समयout,
				     msecs_to_jअगरfies(arg.max_scan_समय +
						      ATH11K_MAC_SCAN_TIMEOUT_MSECS));

निकास:
	अगर (req->ie_len)
		kमुक्त(arg.extraie.ptr);

	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल व्योम ath11k_mac_op_cancel_hw_scan(काष्ठा ieee80211_hw *hw,
					 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath11k *ar = hw->priv;

	mutex_lock(&ar->conf_mutex);
	ath11k_scan_पात(ar);
	mutex_unlock(&ar->conf_mutex);

	cancel_delayed_work_sync(&ar->scan.समयout);
पूर्ण

अटल पूर्णांक ath11k_install_key(काष्ठा ath11k_vअगर *arvअगर,
			      काष्ठा ieee80211_key_conf *key,
			      क्रमागत set_key_cmd cmd,
			      स्थिर u8 *macaddr, u32 flags)
अणु
	पूर्णांक ret;
	काष्ठा ath11k *ar = arvअगर->ar;
	काष्ठा wmi_vdev_install_key_arg arg = अणु
		.vdev_id = arvअगर->vdev_id,
		.key_idx = key->keyidx,
		.key_len = key->keylen,
		.key_data = key->key,
		.key_flags = flags,
		.macaddr = macaddr,
	पूर्ण;

	lockdep_निश्चित_held(&arvअगर->ar->conf_mutex);

	reinit_completion(&ar->install_key_करोne);

	अगर (test_bit(ATH11K_FLAG_HW_CRYPTO_DISABLED, &ar->ab->dev_flags))
		वापस 0;

	अगर (cmd == DISABLE_KEY) अणु
		/* TODO: Check अगर FW expects  value other than NONE क्रम del */
		/* arg.key_cipher = WMI_CIPHER_NONE; */
		arg.key_len = 0;
		arg.key_data = शून्य;
		जाओ install;
	पूर्ण

	चयन (key->cipher) अणु
	हाल WLAN_CIPHER_SUITE_CCMP:
		arg.key_cipher = WMI_CIPHER_AES_CCM;
		/* TODO: Re-check अगर flag is valid */
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV_MGMT;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		arg.key_cipher = WMI_CIPHER_TKIP;
		arg.key_txmic_len = 8;
		arg.key_rxmic_len = 8;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP_256:
		arg.key_cipher = WMI_CIPHER_AES_CCM;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		arg.key_cipher = WMI_CIPHER_AES_GCM;
		अवरोध;
	शेष:
		ath11k_warn(ar->ab, "cipher %d is not supported\n", key->cipher);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (test_bit(ATH11K_FLAG_RAW_MODE, &ar->ab->dev_flags))
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV |
			      IEEE80211_KEY_FLAG_RESERVE_TAILROOM;

install:
	ret = ath11k_wmi_vdev_install_key(arvअगर->ar, &arg);

	अगर (ret)
		वापस ret;

	अगर (!रुको_क्रम_completion_समयout(&ar->install_key_करोne, 1 * HZ))
		वापस -ETIMEDOUT;

	वापस ar->install_key_status ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक ath11k_clear_peer_keys(काष्ठा ath11k_vअगर *arvअगर,
				  स्थिर u8 *addr)
अणु
	काष्ठा ath11k *ar = arvअगर->ar;
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_peer *peer;
	पूर्णांक first_त्रुटि_सं = 0;
	पूर्णांक ret;
	पूर्णांक i;
	u32 flags = 0;

	lockdep_निश्चित_held(&ar->conf_mutex);

	spin_lock_bh(&ab->base_lock);
	peer = ath11k_peer_find(ab, arvअगर->vdev_id, addr);
	spin_unlock_bh(&ab->base_lock);

	अगर (!peer)
		वापस -ENOENT;

	क्रम (i = 0; i < ARRAY_SIZE(peer->keys); i++) अणु
		अगर (!peer->keys[i])
			जारी;

		/* key flags are not required to delete the key */
		ret = ath11k_install_key(arvअगर, peer->keys[i],
					 DISABLE_KEY, addr, flags);
		अगर (ret < 0 && first_त्रुटि_सं == 0)
			first_त्रुटि_सं = ret;

		अगर (ret < 0)
			ath11k_warn(ab, "failed to remove peer key %d: %d\n",
				    i, ret);

		spin_lock_bh(&ab->base_lock);
		peer->keys[i] = शून्य;
		spin_unlock_bh(&ab->base_lock);
	पूर्ण

	वापस first_त्रुटि_सं;
पूर्ण

अटल पूर्णांक ath11k_mac_op_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
				 काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
				 काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_vअगर *arvअगर = ath11k_vअगर_to_arvअगर(vअगर);
	काष्ठा ath11k_peer *peer;
	काष्ठा ath11k_sta *arsta;
	स्थिर u8 *peer_addr;
	पूर्णांक ret = 0;
	u32 flags = 0;

	/* BIP needs to be करोne in software */
	अगर (key->cipher == WLAN_CIPHER_SUITE_AES_CMAC ||
	    key->cipher == WLAN_CIPHER_SUITE_BIP_GMAC_128 ||
	    key->cipher == WLAN_CIPHER_SUITE_BIP_GMAC_256 ||
	    key->cipher == WLAN_CIPHER_SUITE_BIP_CMAC_256)
		वापस 1;

	अगर (test_bit(ATH11K_FLAG_HW_CRYPTO_DISABLED, &ar->ab->dev_flags))
		वापस 1;

	अगर (key->keyidx > WMI_MAX_KEY_INDEX)
		वापस -ENOSPC;

	mutex_lock(&ar->conf_mutex);

	अगर (sta)
		peer_addr = sta->addr;
	अन्यथा अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_STA)
		peer_addr = vअगर->bss_conf.bssid;
	अन्यथा
		peer_addr = vअगर->addr;

	key->hw_key_idx = key->keyidx;

	/* the peer should not disappear in mid-way (unless FW goes awry) since
	 * we alपढ़ोy hold conf_mutex. we just make sure its there now.
	 */
	spin_lock_bh(&ab->base_lock);
	peer = ath11k_peer_find(ab, arvअगर->vdev_id, peer_addr);

	/* flush the fragments cache during key (re)install to
	 * ensure all frags in the new frag list beदीर्घ to the same key.
	 */
	अगर (peer && cmd == SET_KEY)
		ath11k_peer_frags_flush(ar, peer);
	spin_unlock_bh(&ab->base_lock);

	अगर (!peer) अणु
		अगर (cmd == SET_KEY) अणु
			ath11k_warn(ab, "cannot install key for non-existent peer %pM\n",
				    peer_addr);
			ret = -EOPNOTSUPP;
			जाओ निकास;
		पूर्ण अन्यथा अणु
			/* अगर the peer करोesn't exist there is no key to disable
			 * anymore
			 */
			जाओ निकास;
		पूर्ण
	पूर्ण

	अगर (key->flags & IEEE80211_KEY_FLAG_PAIRWISE)
		flags |= WMI_KEY_PAIRWISE;
	अन्यथा
		flags |= WMI_KEY_GROUP;

	ret = ath11k_install_key(arvअगर, key, cmd, peer_addr, flags);
	अगर (ret) अणु
		ath11k_warn(ab, "ath11k_install_key failed (%d)\n", ret);
		जाओ निकास;
	पूर्ण

	ret = ath11k_dp_peer_rx_pn_replay_config(arvअगर, peer_addr, cmd, key);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to offload PN replay detection %d\n", ret);
		जाओ निकास;
	पूर्ण

	spin_lock_bh(&ab->base_lock);
	peer = ath11k_peer_find(ab, arvअगर->vdev_id, peer_addr);
	अगर (peer && cmd == SET_KEY) अणु
		peer->keys[key->keyidx] = key;
		अगर (key->flags & IEEE80211_KEY_FLAG_PAIRWISE) अणु
			peer->ucast_keyidx = key->keyidx;
			peer->sec_type = ath11k_dp_tx_get_encrypt_type(key->cipher);
		पूर्ण अन्यथा अणु
			peer->mcast_keyidx = key->keyidx;
			peer->sec_type_grp = ath11k_dp_tx_get_encrypt_type(key->cipher);
		पूर्ण
	पूर्ण अन्यथा अगर (peer && cmd == DISABLE_KEY) अणु
		peer->keys[key->keyidx] = शून्य;
		अगर (key->flags & IEEE80211_KEY_FLAG_PAIRWISE)
			peer->ucast_keyidx = 0;
		अन्यथा
			peer->mcast_keyidx = 0;
	पूर्ण अन्यथा अगर (!peer)
		/* impossible unless FW goes crazy */
		ath11k_warn(ab, "peer %pM disappeared!\n", peer_addr);

	अगर (sta) अणु
		arsta = (काष्ठा ath11k_sta *)sta->drv_priv;

		चयन (key->cipher) अणु
		हाल WLAN_CIPHER_SUITE_TKIP:
		हाल WLAN_CIPHER_SUITE_CCMP:
		हाल WLAN_CIPHER_SUITE_CCMP_256:
		हाल WLAN_CIPHER_SUITE_GCMP:
		हाल WLAN_CIPHER_SUITE_GCMP_256:
			अगर (cmd == SET_KEY)
				arsta->pn_type = HAL_PN_TYPE_WPA;
			अन्यथा
				arsta->pn_type = HAL_PN_TYPE_NONE;
			अवरोध;
		शेष:
			arsta->pn_type = HAL_PN_TYPE_NONE;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&ab->base_lock);

निकास:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक
ath11k_mac_bitrate_mask_num_vht_rates(काष्ठा ath11k *ar,
				      क्रमागत nl80211_band band,
				      स्थिर काष्ठा cfg80211_bitrate_mask *mask)
अणु
	पूर्णांक num_rates = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mask->control[band].vht_mcs); i++)
		num_rates += hweight16(mask->control[band].vht_mcs[i]);

	वापस num_rates;
पूर्ण

अटल पूर्णांक
ath11k_mac_set_peer_vht_fixed_rate(काष्ठा ath11k_vअगर *arvअगर,
				   काष्ठा ieee80211_sta *sta,
				   स्थिर काष्ठा cfg80211_bitrate_mask *mask,
				   क्रमागत nl80211_band band)
अणु
	काष्ठा ath11k *ar = arvअगर->ar;
	u8 vht_rate, nss;
	u32 rate_code;
	पूर्णांक ret, i;

	lockdep_निश्चित_held(&ar->conf_mutex);

	nss = 0;

	क्रम (i = 0; i < ARRAY_SIZE(mask->control[band].vht_mcs); i++) अणु
		अगर (hweight16(mask->control[band].vht_mcs[i]) == 1) अणु
			nss = i + 1;
			vht_rate = ffs(mask->control[band].vht_mcs[i]) - 1;
		पूर्ण
	पूर्ण

	अगर (!nss) अणु
		ath11k_warn(ar->ab, "No single VHT Fixed rate found to set for %pM",
			    sta->addr);
		वापस -EINVAL;
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
		   "Setting Fixed VHT Rate for peer %pM. Device will not switch to any other selected rates",
		   sta->addr);

	rate_code = ATH11K_HW_RATE_CODE(vht_rate, nss - 1,
					WMI_RATE_PREAMBLE_VHT);
	ret = ath11k_wmi_set_peer_param(ar, sta->addr,
					arvअगर->vdev_id,
					WMI_PEER_PARAM_FIXED_RATE,
					rate_code);
	अगर (ret)
		ath11k_warn(ar->ab,
			    "failed to update STA %pM Fixed Rate %d: %d\n",
			     sta->addr, rate_code, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_station_assoc(काष्ठा ath11k *ar,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा ieee80211_sta *sta,
				bool reassoc)
अणु
	काष्ठा ath11k_vअगर *arvअगर = ath11k_vअगर_to_arvअगर(vअगर);
	काष्ठा peer_assoc_params peer_arg;
	पूर्णांक ret = 0;
	काष्ठा cfg80211_chan_def def;
	क्रमागत nl80211_band band;
	काष्ठा cfg80211_bitrate_mask *mask;
	u8 num_vht_rates;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (WARN_ON(ath11k_mac_vअगर_chan(vअगर, &def)))
		वापस -EPERM;

	band = def.chan->band;
	mask = &arvअगर->bitrate_mask;

	ath11k_peer_assoc_prepare(ar, vअगर, sta, &peer_arg, reassoc);

	ret = ath11k_wmi_send_peer_assoc_cmd(ar, &peer_arg);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to run peer assoc for STA %pM vdev %i: %d\n",
			    sta->addr, arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	अगर (!रुको_क्रम_completion_समयout(&ar->peer_assoc_करोne, 1 * HZ)) अणु
		ath11k_warn(ar->ab, "failed to get peer assoc conf event for %pM vdev %i\n",
			    sta->addr, arvअगर->vdev_id);
		वापस -ETIMEDOUT;
	पूर्ण

	num_vht_rates = ath11k_mac_bitrate_mask_num_vht_rates(ar, band, mask);

	/* If single VHT rate is configured (by set_bitrate_mask()),
	 * peer_assoc will disable VHT. This is now enabled by a peer specअगरic
	 * fixed param.
	 * Note that all other rates and NSS will be disabled क्रम this peer.
	 */
	अगर (sta->vht_cap.vht_supported && num_vht_rates == 1) अणु
		ret = ath11k_mac_set_peer_vht_fixed_rate(arvअगर, sta, mask,
							 band);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Re-assoc is run only to update supported rates क्रम given station. It
	 * करोesn't make much sense to reconfigure the peer completely.
	 */
	अगर (reassoc)
		वापस 0;

	ret = ath11k_setup_peer_smps(ar, arvअगर, sta->addr,
				     &sta->ht_cap);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to setup peer SMPS for vdev %d: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण

	अगर (!sta->wme) अणु
		arvअगर->num_legacy_stations++;
		ret = ath11k_recalc_rtscts_prot(arvअगर);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (sta->wme && sta->uapsd_queues) अणु
		ret = ath11k_peer_assoc_qos_ap(ar, arvअगर, sta);
		अगर (ret) अणु
			ath11k_warn(ar->ab, "failed to set qos params for STA %pM for vdev %i: %d\n",
				    sta->addr, arvअगर->vdev_id, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_station_disassoc(काष्ठा ath11k *ar,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath11k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (!sta->wme) अणु
		arvअगर->num_legacy_stations--;
		ret = ath11k_recalc_rtscts_prot(arvअगर);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = ath11k_clear_peer_keys(arvअगर, sta->addr);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to clear all peer keys for vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ath11k_sta_rc_update_wk(काष्ठा work_काष्ठा *wk)
अणु
	काष्ठा ath11k *ar;
	काष्ठा ath11k_vअगर *arvअगर;
	काष्ठा ath11k_sta *arsta;
	काष्ठा ieee80211_sta *sta;
	काष्ठा cfg80211_chan_def def;
	क्रमागत nl80211_band band;
	स्थिर u8 *ht_mcs_mask;
	स्थिर u16 *vht_mcs_mask;
	u32 changed, bw, nss, smps;
	पूर्णांक err, num_vht_rates;
	स्थिर काष्ठा cfg80211_bitrate_mask *mask;
	काष्ठा peer_assoc_params peer_arg;

	arsta = container_of(wk, काष्ठा ath11k_sta, update_wk);
	sta = container_of((व्योम *)arsta, काष्ठा ieee80211_sta, drv_priv);
	arvअगर = arsta->arvअगर;
	ar = arvअगर->ar;

	अगर (WARN_ON(ath11k_mac_vअगर_chan(arvअगर->vअगर, &def)))
		वापस;

	band = def.chan->band;
	ht_mcs_mask = arvअगर->bitrate_mask.control[band].ht_mcs;
	vht_mcs_mask = arvअगर->bitrate_mask.control[band].vht_mcs;

	spin_lock_bh(&ar->data_lock);

	changed = arsta->changed;
	arsta->changed = 0;

	bw = arsta->bw;
	nss = arsta->nss;
	smps = arsta->smps;

	spin_unlock_bh(&ar->data_lock);

	mutex_lock(&ar->conf_mutex);

	nss = max_t(u32, 1, nss);
	nss = min(nss, max(ath11k_mac_max_ht_nss(ht_mcs_mask),
			   ath11k_mac_max_vht_nss(vht_mcs_mask)));

	अगर (changed & IEEE80211_RC_BW_CHANGED) अणु
		err = ath11k_wmi_set_peer_param(ar, sta->addr, arvअगर->vdev_id,
						WMI_PEER_CHWIDTH, bw);
		अगर (err)
			ath11k_warn(ar->ab, "failed to update STA %pM peer bw %d: %d\n",
				    sta->addr, bw, err);
	पूर्ण

	अगर (changed & IEEE80211_RC_NSS_CHANGED) अणु
		ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac update sta %pM nss %d\n",
			   sta->addr, nss);

		err = ath11k_wmi_set_peer_param(ar, sta->addr, arvअगर->vdev_id,
						WMI_PEER_NSS, nss);
		अगर (err)
			ath11k_warn(ar->ab, "failed to update STA %pM nss %d: %d\n",
				    sta->addr, nss, err);
	पूर्ण

	अगर (changed & IEEE80211_RC_SMPS_CHANGED) अणु
		ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac update sta %pM smps %d\n",
			   sta->addr, smps);

		err = ath11k_wmi_set_peer_param(ar, sta->addr, arvअगर->vdev_id,
						WMI_PEER_MIMO_PS_STATE, smps);
		अगर (err)
			ath11k_warn(ar->ab, "failed to update STA %pM smps %d: %d\n",
				    sta->addr, smps, err);
	पूर्ण

	अगर (changed & IEEE80211_RC_SUPP_RATES_CHANGED) अणु
		mask = &arvअगर->bitrate_mask;
		num_vht_rates = ath11k_mac_bitrate_mask_num_vht_rates(ar, band,
								      mask);

		/* Peer_assoc_prepare will reject vht rates in
		 * bitrate_mask अगर its not available in range क्रमmat and
		 * sets vht tx_rateset as unsupported. So multiple VHT MCS
		 * setting(eg. MCS 4,5,6) per peer is not supported here.
		 * But, Single rate in VHT mask can be set as per-peer
		 * fixed rate. But even अगर any HT rates are configured in
		 * the bitrate mask, device will not चयन to those rates
		 * when per-peer Fixed rate is set.
		 * TODO: Check RATEMASK_CMDID to support स्वतः rates selection
		 * across HT/VHT and क्रम multiple VHT MCS support.
		 */
		अगर (sta->vht_cap.vht_supported && num_vht_rates == 1) अणु
			ath11k_mac_set_peer_vht_fixed_rate(arvअगर, sta, mask,
							   band);
		पूर्ण अन्यथा अणु
			/* If the peer is non-VHT or no fixed VHT rate
			 * is provided in the new bitrate mask we set the
			 * other rates using peer_assoc command.
			 */
			ath11k_peer_assoc_prepare(ar, arvअगर->vअगर, sta,
						  &peer_arg, true);

			err = ath11k_wmi_send_peer_assoc_cmd(ar, &peer_arg);
			अगर (err)
				ath11k_warn(ar->ab, "failed to run peer assoc for STA %pM vdev %i: %d\n",
					    sta->addr, arvअगर->vdev_id, err);

			अगर (!रुको_क्रम_completion_समयout(&ar->peer_assoc_करोne, 1 * HZ))
				ath11k_warn(ar->ab, "failed to get peer assoc conf event for %pM vdev %i\n",
					    sta->addr, arvअगर->vdev_id);
		पूर्ण
	पूर्ण

	mutex_unlock(&ar->conf_mutex);
पूर्ण

अटल पूर्णांक ath11k_mac_inc_num_stations(काष्ठा ath11k_vअगर *arvअगर,
				       काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath11k *ar = arvअगर->ar;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_STA && !sta->tdls)
		वापस 0;

	अगर (ar->num_stations >= ar->max_num_stations)
		वापस -ENOBUFS;

	ar->num_stations++;

	वापस 0;
पूर्ण

अटल व्योम ath11k_mac_dec_num_stations(काष्ठा ath11k_vअगर *arvअगर,
					काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath11k *ar = arvअगर->ar;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_STA && !sta->tdls)
		वापस;

	ar->num_stations--;
पूर्ण

अटल पूर्णांक ath11k_mac_station_add(काष्ठा ath11k *ar,
				  काष्ठा ieee80211_vअगर *vअगर,
				  काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_vअगर *arvअगर = ath11k_vअगर_to_arvअगर(vअगर);
	काष्ठा ath11k_sta *arsta = (काष्ठा ath11k_sta *)sta->drv_priv;
	काष्ठा peer_create_params peer_param;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ret = ath11k_mac_inc_num_stations(arvअगर, sta);
	अगर (ret) अणु
		ath11k_warn(ab, "refusing to associate station: too many connected already (%d)\n",
			    ar->max_num_stations);
		जाओ निकास;
	पूर्ण

	arsta->rx_stats = kzalloc(माप(*arsta->rx_stats), GFP_KERNEL);
	अगर (!arsta->rx_stats) अणु
		ret = -ENOMEM;
		जाओ dec_num_station;
	पूर्ण

	peer_param.vdev_id = arvअगर->vdev_id;
	peer_param.peer_addr = sta->addr;
	peer_param.peer_type = WMI_PEER_TYPE_DEFAULT;

	ret = ath11k_peer_create(ar, arvअगर, sta, &peer_param);
	अगर (ret) अणु
		ath11k_warn(ab, "Failed to add peer: %pM for VDEV: %d\n",
			    sta->addr, arvअगर->vdev_id);
		जाओ मुक्त_rx_stats;
	पूर्ण

	ath11k_dbg(ab, ATH11K_DBG_MAC, "Added peer: %pM for VDEV: %d\n",
		   sta->addr, arvअगर->vdev_id);

	अगर (ath11k_debugfs_is_extd_tx_stats_enabled(ar)) अणु
		arsta->tx_stats = kzalloc(माप(*arsta->tx_stats), GFP_KERNEL);
		अगर (!arsta->tx_stats) अणु
			ret = -ENOMEM;
			जाओ मुक्त_peer;
		पूर्ण
	पूर्ण

	अगर (ieee80211_vअगर_is_mesh(vअगर)) अणु
		ret = ath11k_wmi_set_peer_param(ar, sta->addr,
						arvअगर->vdev_id,
						WMI_PEER_USE_4ADDR, 1);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to STA %pM 4addr capability: %d\n",
				    sta->addr, ret);
			जाओ मुक्त_tx_stats;
		पूर्ण
	पूर्ण

	ret = ath11k_dp_peer_setup(ar, arvअगर->vdev_id, sta->addr);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to setup dp for peer %pM on vdev %i (%d)\n",
			    sta->addr, arvअगर->vdev_id, ret);
		जाओ मुक्त_tx_stats;
	पूर्ण

	अगर (ab->hw_params.vdev_start_delay &&
	    !arvअगर->is_started &&
	    arvअगर->vdev_type != WMI_VDEV_TYPE_AP) अणु
		ret = ath11k_start_vdev_delay(ar->hw, vअगर);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to delay vdev start: %d\n", ret);
			जाओ मुक्त_tx_stats;
		पूर्ण
	पूर्ण

	वापस 0;

मुक्त_tx_stats:
	kमुक्त(arsta->tx_stats);
	arsta->tx_stats = शून्य;
मुक्त_peer:
	ath11k_peer_delete(ar, arvअगर->vdev_id, sta->addr);
मुक्त_rx_stats:
	kमुक्त(arsta->rx_stats);
	arsta->rx_stats = शून्य;
dec_num_station:
	ath11k_mac_dec_num_stations(arvअगर, sta);
निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_mac_op_sta_state(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा ieee80211_sta *sta,
				   क्रमागत ieee80211_sta_state old_state,
				   क्रमागत ieee80211_sta_state new_state)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ath11k_vअगर *arvअगर = ath11k_vअगर_to_arvअगर(vअगर);
	काष्ठा ath11k_sta *arsta = (काष्ठा ath11k_sta *)sta->drv_priv;
	काष्ठा ath11k_peer *peer;
	पूर्णांक ret = 0;

	/* cancel must be करोne outside the mutex to aव्योम deadlock */
	अगर ((old_state == IEEE80211_STA_NONE &&
	     new_state == IEEE80211_STA_NOTEXIST))
		cancel_work_sync(&arsta->update_wk);

	mutex_lock(&ar->conf_mutex);

	अगर (old_state == IEEE80211_STA_NOTEXIST &&
	    new_state == IEEE80211_STA_NONE) अणु
		स_रखो(arsta, 0, माप(*arsta));
		arsta->arvअगर = arvअगर;
		INIT_WORK(&arsta->update_wk, ath11k_sta_rc_update_wk);

		ret = ath11k_mac_station_add(ar, vअगर, sta);
		अगर (ret)
			ath11k_warn(ar->ab, "Failed to add station: %pM for VDEV: %d\n",
				    sta->addr, arvअगर->vdev_id);
	पूर्ण अन्यथा अगर ((old_state == IEEE80211_STA_NONE &&
		    new_state == IEEE80211_STA_NOTEXIST)) अणु
		ath11k_dp_peer_cleanup(ar, arvअगर->vdev_id, sta->addr);

		ret = ath11k_peer_delete(ar, arvअगर->vdev_id, sta->addr);
		अगर (ret)
			ath11k_warn(ar->ab, "Failed to delete peer: %pM for VDEV: %d\n",
				    sta->addr, arvअगर->vdev_id);
		अन्यथा
			ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "Removed peer: %pM for VDEV: %d\n",
				   sta->addr, arvअगर->vdev_id);

		ath11k_mac_dec_num_stations(arvअगर, sta);
		spin_lock_bh(&ar->ab->base_lock);
		peer = ath11k_peer_find(ar->ab, arvअगर->vdev_id, sta->addr);
		अगर (peer && peer->sta == sta) अणु
			ath11k_warn(ar->ab, "Found peer entry %pM n vdev %i after it was supposedly removed\n",
				    vअगर->addr, arvअगर->vdev_id);
			peer->sta = शून्य;
			list_del(&peer->list);
			kमुक्त(peer);
			ar->num_peers--;
		पूर्ण
		spin_unlock_bh(&ar->ab->base_lock);

		kमुक्त(arsta->tx_stats);
		arsta->tx_stats = शून्य;

		kमुक्त(arsta->rx_stats);
		arsta->rx_stats = शून्य;
	पूर्ण अन्यथा अगर (old_state == IEEE80211_STA_AUTH &&
		   new_state == IEEE80211_STA_ASSOC &&
		   (vअगर->type == NL80211_IFTYPE_AP ||
		    vअगर->type == NL80211_IFTYPE_MESH_POINT ||
		    vअगर->type == NL80211_IFTYPE_ADHOC)) अणु
		ret = ath11k_station_assoc(ar, vअगर, sta, false);
		अगर (ret)
			ath11k_warn(ar->ab, "Failed to associate station: %pM\n",
				    sta->addr);
	पूर्ण अन्यथा अगर (old_state == IEEE80211_STA_ASSOC &&
		   new_state == IEEE80211_STA_AUTH &&
		   (vअगर->type == NL80211_IFTYPE_AP ||
		    vअगर->type == NL80211_IFTYPE_MESH_POINT ||
		    vअगर->type == NL80211_IFTYPE_ADHOC)) अणु
		ret = ath11k_station_disassoc(ar, vअगर, sta);
		अगर (ret)
			ath11k_warn(ar->ab, "Failed to disassociate station: %pM\n",
				    sta->addr);
	पूर्ण

	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_mac_op_sta_set_txpwr(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ath11k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	पूर्णांक ret = 0;
	s16 txpwr;

	अगर (sta->txpwr.type == NL80211_TX_POWER_AUTOMATIC) अणु
		txpwr = 0;
	पूर्ण अन्यथा अणु
		txpwr = sta->txpwr.घातer;
		अगर (!txpwr)
			वापस -EINVAL;
	पूर्ण

	अगर (txpwr > ATH11K_TX_POWER_MAX_VAL || txpwr < ATH11K_TX_POWER_MIN_VAL)
		वापस -EINVAL;

	mutex_lock(&ar->conf_mutex);

	ret = ath11k_wmi_set_peer_param(ar, sta->addr, arvअगर->vdev_id,
					WMI_PEER_USE_FIXED_PWR, txpwr);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to set tx power for station ret: %d\n",
			    ret);
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल व्योम ath11k_mac_op_sta_rc_update(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_vअगर *vअगर,
					काष्ठा ieee80211_sta *sta,
					u32 changed)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ath11k_sta *arsta = (काष्ठा ath11k_sta *)sta->drv_priv;
	काष्ठा ath11k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा ath11k_peer *peer;
	u32 bw, smps;

	spin_lock_bh(&ar->ab->base_lock);

	peer = ath11k_peer_find(ar->ab, arvअगर->vdev_id, sta->addr);
	अगर (!peer) अणु
		spin_unlock_bh(&ar->ab->base_lock);
		ath11k_warn(ar->ab, "mac sta rc update failed to find peer %pM on vdev %i\n",
			    sta->addr, arvअगर->vdev_id);
		वापस;
	पूर्ण

	spin_unlock_bh(&ar->ab->base_lock);

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
		   "mac sta rc update for %pM changed %08x bw %d nss %d smps %d\n",
		   sta->addr, changed, sta->bandwidth, sta->rx_nss,
		   sta->smps_mode);

	spin_lock_bh(&ar->data_lock);

	अगर (changed & IEEE80211_RC_BW_CHANGED) अणु
		bw = WMI_PEER_CHWIDTH_20MHZ;

		चयन (sta->bandwidth) अणु
		हाल IEEE80211_STA_RX_BW_20:
			bw = WMI_PEER_CHWIDTH_20MHZ;
			अवरोध;
		हाल IEEE80211_STA_RX_BW_40:
			bw = WMI_PEER_CHWIDTH_40MHZ;
			अवरोध;
		हाल IEEE80211_STA_RX_BW_80:
			bw = WMI_PEER_CHWIDTH_80MHZ;
			अवरोध;
		हाल IEEE80211_STA_RX_BW_160:
			bw = WMI_PEER_CHWIDTH_160MHZ;
			अवरोध;
		शेष:
			ath11k_warn(ar->ab, "Invalid bandwidth %d in rc update for %pM\n",
				    sta->bandwidth, sta->addr);
			bw = WMI_PEER_CHWIDTH_20MHZ;
			अवरोध;
		पूर्ण

		arsta->bw = bw;
	पूर्ण

	अगर (changed & IEEE80211_RC_NSS_CHANGED)
		arsta->nss = sta->rx_nss;

	अगर (changed & IEEE80211_RC_SMPS_CHANGED) अणु
		smps = WMI_PEER_SMPS_PS_NONE;

		चयन (sta->smps_mode) अणु
		हाल IEEE80211_SMPS_AUTOMATIC:
		हाल IEEE80211_SMPS_OFF:
			smps = WMI_PEER_SMPS_PS_NONE;
			अवरोध;
		हाल IEEE80211_SMPS_STATIC:
			smps = WMI_PEER_SMPS_STATIC;
			अवरोध;
		हाल IEEE80211_SMPS_DYNAMIC:
			smps = WMI_PEER_SMPS_DYNAMIC;
			अवरोध;
		शेष:
			ath11k_warn(ar->ab, "Invalid smps %d in sta rc update for %pM\n",
				    sta->smps_mode, sta->addr);
			smps = WMI_PEER_SMPS_PS_NONE;
			अवरोध;
		पूर्ण

		arsta->smps = smps;
	पूर्ण

	arsta->changed |= changed;

	spin_unlock_bh(&ar->data_lock);

	ieee80211_queue_work(hw, &arsta->update_wk);
पूर्ण

अटल पूर्णांक ath11k_conf_tx_uapsd(काष्ठा ath11k *ar, काष्ठा ieee80211_vअगर *vअगर,
				u16 ac, bool enable)
अणु
	काष्ठा ath11k_vअगर *arvअगर = ath11k_vअगर_to_arvअगर(vअगर);
	u32 value = 0;
	पूर्णांक ret = 0;

	अगर (arvअगर->vdev_type != WMI_VDEV_TYPE_STA)
		वापस 0;

	चयन (ac) अणु
	हाल IEEE80211_AC_VO:
		value = WMI_STA_PS_UAPSD_AC3_DELIVERY_EN |
			WMI_STA_PS_UAPSD_AC3_TRIGGER_EN;
		अवरोध;
	हाल IEEE80211_AC_VI:
		value = WMI_STA_PS_UAPSD_AC2_DELIVERY_EN |
			WMI_STA_PS_UAPSD_AC2_TRIGGER_EN;
		अवरोध;
	हाल IEEE80211_AC_BE:
		value = WMI_STA_PS_UAPSD_AC1_DELIVERY_EN |
			WMI_STA_PS_UAPSD_AC1_TRIGGER_EN;
		अवरोध;
	हाल IEEE80211_AC_BK:
		value = WMI_STA_PS_UAPSD_AC0_DELIVERY_EN |
			WMI_STA_PS_UAPSD_AC0_TRIGGER_EN;
		अवरोध;
	पूर्ण

	अगर (enable)
		arvअगर->u.sta.uapsd |= value;
	अन्यथा
		arvअगर->u.sta.uapsd &= ~value;

	ret = ath11k_wmi_set_sta_ps_param(ar, arvअगर->vdev_id,
					  WMI_STA_PS_PARAM_UAPSD,
					  arvअगर->u.sta.uapsd);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "could not set uapsd params %d\n", ret);
		जाओ निकास;
	पूर्ण

	अगर (arvअगर->u.sta.uapsd)
		value = WMI_STA_PS_RX_WAKE_POLICY_POLL_UAPSD;
	अन्यथा
		value = WMI_STA_PS_RX_WAKE_POLICY_WAKE;

	ret = ath11k_wmi_set_sta_ps_param(ar, arvअगर->vdev_id,
					  WMI_STA_PS_PARAM_RX_WAKE_POLICY,
					  value);
	अगर (ret)
		ath11k_warn(ar->ab, "could not set rx wake param %d\n", ret);

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_mac_op_conf_tx(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर, u16 ac,
				 स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ath11k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा wmi_wmm_params_arg *p = शून्य;
	पूर्णांक ret;

	mutex_lock(&ar->conf_mutex);

	चयन (ac) अणु
	हाल IEEE80211_AC_VO:
		p = &arvअगर->wmm_params.ac_vo;
		अवरोध;
	हाल IEEE80211_AC_VI:
		p = &arvअगर->wmm_params.ac_vi;
		अवरोध;
	हाल IEEE80211_AC_BE:
		p = &arvअगर->wmm_params.ac_be;
		अवरोध;
	हाल IEEE80211_AC_BK:
		p = &arvअगर->wmm_params.ac_bk;
		अवरोध;
	पूर्ण

	अगर (WARN_ON(!p)) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	p->cwmin = params->cw_min;
	p->cwmax = params->cw_max;
	p->aअगरs = params->aअगरs;
	p->txop = params->txop;

	ret = ath11k_wmi_send_wmm_update_cmd_tlv(ar, arvअगर->vdev_id,
						 &arvअगर->wmm_params);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to set wmm params: %d\n", ret);
		जाओ निकास;
	पूर्ण

	ret = ath11k_conf_tx_uapsd(ar, vअगर, ac, params->uapsd);

	अगर (ret)
		ath11k_warn(ar->ab, "failed to set sta uapsd: %d\n", ret);

निकास:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल काष्ठा ieee80211_sta_ht_cap
ath11k_create_ht_cap(काष्ठा ath11k *ar, u32 ar_ht_cap, u32 rate_cap_rx_chainmask)
अणु
	पूर्णांक i;
	काष्ठा ieee80211_sta_ht_cap ht_cap = अणु0पूर्ण;
	u32 ar_vht_cap = ar->pdev->cap.vht_cap;

	अगर (!(ar_ht_cap & WMI_HT_CAP_ENABLED))
		वापस ht_cap;

	ht_cap.ht_supported = 1;
	ht_cap.ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K;
	ht_cap.ampdu_density = IEEE80211_HT_MPDU_DENSITY_NONE;
	ht_cap.cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40;
	ht_cap.cap |= IEEE80211_HT_CAP_DSSSCCK40;
	ht_cap.cap |= WLAN_HT_CAP_SM_PS_STATIC << IEEE80211_HT_CAP_SM_PS_SHIFT;

	अगर (ar_ht_cap & WMI_HT_CAP_HT20_SGI)
		ht_cap.cap |= IEEE80211_HT_CAP_SGI_20;

	अगर (ar_ht_cap & WMI_HT_CAP_HT40_SGI)
		ht_cap.cap |= IEEE80211_HT_CAP_SGI_40;

	अगर (ar_ht_cap & WMI_HT_CAP_DYNAMIC_SMPS) अणु
		u32 smps;

		smps   = WLAN_HT_CAP_SM_PS_DYNAMIC;
		smps <<= IEEE80211_HT_CAP_SM_PS_SHIFT;

		ht_cap.cap |= smps;
	पूर्ण

	अगर (ar_ht_cap & WMI_HT_CAP_TX_STBC)
		ht_cap.cap |= IEEE80211_HT_CAP_TX_STBC;

	अगर (ar_ht_cap & WMI_HT_CAP_RX_STBC) अणु
		u32 stbc;

		stbc   = ar_ht_cap;
		stbc  &= WMI_HT_CAP_RX_STBC;
		stbc >>= WMI_HT_CAP_RX_STBC_MASK_SHIFT;
		stbc <<= IEEE80211_HT_CAP_RX_STBC_SHIFT;
		stbc  &= IEEE80211_HT_CAP_RX_STBC;

		ht_cap.cap |= stbc;
	पूर्ण

	अगर (ar_ht_cap & WMI_HT_CAP_RX_LDPC)
		ht_cap.cap |= IEEE80211_HT_CAP_LDPC_CODING;

	अगर (ar_ht_cap & WMI_HT_CAP_L_SIG_TXOP_PROT)
		ht_cap.cap |= IEEE80211_HT_CAP_LSIG_TXOP_PROT;

	अगर (ar_vht_cap & WMI_VHT_CAP_MAX_MPDU_LEN_MASK)
		ht_cap.cap |= IEEE80211_HT_CAP_MAX_AMSDU;

	क्रम (i = 0; i < ar->num_rx_chains; i++) अणु
		अगर (rate_cap_rx_chainmask & BIT(i))
			ht_cap.mcs.rx_mask[i] = 0xFF;
	पूर्ण

	ht_cap.mcs.tx_params |= IEEE80211_HT_MCS_TX_DEFINED;

	वापस ht_cap;
पूर्ण

अटल पूर्णांक ath11k_mac_set_txbf_conf(काष्ठा ath11k_vअगर *arvअगर)
अणु
	u32 value = 0;
	काष्ठा ath11k *ar = arvअगर->ar;
	पूर्णांक nsts;
	पूर्णांक sound_dim;
	u32 vht_cap = ar->pdev->cap.vht_cap;
	u32 vdev_param = WMI_VDEV_PARAM_TXBF;

	अगर (vht_cap & (IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE)) अणु
		nsts = vht_cap & IEEE80211_VHT_CAP_BEAMFORMEE_STS_MASK;
		nsts >>= IEEE80211_VHT_CAP_BEAMFORMEE_STS_SHIFT;
		value |= SM(nsts, WMI_TXBF_STS_CAP_OFFSET);
	पूर्ण

	अगर (vht_cap & (IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE)) अणु
		sound_dim = vht_cap &
			    IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK;
		sound_dim >>= IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_SHIFT;
		अगर (sound_dim > (ar->num_tx_chains - 1))
			sound_dim = ar->num_tx_chains - 1;
		value |= SM(sound_dim, WMI_BF_SOUND_DIM_OFFSET);
	पूर्ण

	अगर (!value)
		वापस 0;

	अगर (vht_cap & IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE) अणु
		value |= WMI_VDEV_PARAM_TXBF_SU_TX_BFER;

		अगर ((vht_cap & IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE) &&
		    arvअगर->vdev_type == WMI_VDEV_TYPE_AP)
			value |= WMI_VDEV_PARAM_TXBF_MU_TX_BFER;
	पूर्ण

	/* TODO: SUBFEE not validated in HK, disable here until validated? */

	अगर (vht_cap & IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE) अणु
		value |= WMI_VDEV_PARAM_TXBF_SU_TX_BFEE;

		अगर ((vht_cap & IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE) &&
		    arvअगर->vdev_type == WMI_VDEV_TYPE_STA)
			value |= WMI_VDEV_PARAM_TXBF_MU_TX_BFEE;
	पूर्ण

	वापस ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
					     vdev_param, value);
पूर्ण

अटल व्योम ath11k_set_vht_txbf_cap(काष्ठा ath11k *ar, u32 *vht_cap)
अणु
	bool subfer, subfee;
	पूर्णांक sound_dim = 0;

	subfer = !!(*vht_cap & (IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE));
	subfee = !!(*vht_cap & (IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE));

	अगर (ar->num_tx_chains < 2) अणु
		*vht_cap &= ~(IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE);
		subfer = false;
	पूर्ण

	/* If SU Beaक्रमmer is not set, then disable MU Beamक्रमmer Capability */
	अगर (!subfer)
		*vht_cap &= ~(IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE);

	/* If SU Beaक्रमmee is not set, then disable MU Beamक्रमmee Capability */
	अगर (!subfee)
		*vht_cap &= ~(IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE);

	sound_dim = (*vht_cap & IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK);
	sound_dim >>= IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_SHIFT;
	*vht_cap &= ~IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK;

	/* TODO: Need to check invalid STS and Sound_dim values set by FW? */

	/* Enable Sounding Dimension Field only अगर SU BF is enabled */
	अगर (subfer) अणु
		अगर (sound_dim > (ar->num_tx_chains - 1))
			sound_dim = ar->num_tx_chains - 1;

		sound_dim <<= IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_SHIFT;
		sound_dim &=  IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK;
		*vht_cap |= sound_dim;
	पूर्ण

	/* Use the STS advertised by FW unless SU Beamक्रमmee is not supported*/
	अगर (!subfee)
		*vht_cap &= ~(IEEE80211_VHT_CAP_BEAMFORMEE_STS_MASK);
पूर्ण

अटल काष्ठा ieee80211_sta_vht_cap
ath11k_create_vht_cap(काष्ठा ath11k *ar, u32 rate_cap_tx_chainmask,
		      u32 rate_cap_rx_chainmask)
अणु
	काष्ठा ieee80211_sta_vht_cap vht_cap = अणु0पूर्ण;
	u16 txmcs_map, rxmcs_map;
	पूर्णांक i;

	vht_cap.vht_supported = 1;
	vht_cap.cap = ar->pdev->cap.vht_cap;

	ath11k_set_vht_txbf_cap(ar, &vht_cap.cap);

	/* TODO: Enable back VHT160 mode once association issues are fixed */
	/* Disabling VHT160 and VHT80+80 modes */
	vht_cap.cap &= ~IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK;
	vht_cap.cap &= ~IEEE80211_VHT_CAP_SHORT_GI_160;

	rxmcs_map = 0;
	txmcs_map = 0;
	क्रम (i = 0; i < 8; i++) अणु
		अगर (i < ar->num_tx_chains && rate_cap_tx_chainmask & BIT(i))
			txmcs_map |= IEEE80211_VHT_MCS_SUPPORT_0_9 << (i * 2);
		अन्यथा
			txmcs_map |= IEEE80211_VHT_MCS_NOT_SUPPORTED << (i * 2);

		अगर (i < ar->num_rx_chains && rate_cap_rx_chainmask & BIT(i))
			rxmcs_map |= IEEE80211_VHT_MCS_SUPPORT_0_9 << (i * 2);
		अन्यथा
			rxmcs_map |= IEEE80211_VHT_MCS_NOT_SUPPORTED << (i * 2);
	पूर्ण

	अगर (rate_cap_tx_chainmask <= 1)
		vht_cap.cap &= ~IEEE80211_VHT_CAP_TXSTBC;

	vht_cap.vht_mcs.rx_mcs_map = cpu_to_le16(rxmcs_map);
	vht_cap.vht_mcs.tx_mcs_map = cpu_to_le16(txmcs_map);

	वापस vht_cap;
पूर्ण

अटल व्योम ath11k_mac_setup_ht_vht_cap(काष्ठा ath11k *ar,
					काष्ठा ath11k_pdev_cap *cap,
					u32 *ht_cap_info)
अणु
	काष्ठा ieee80211_supported_band *band;
	u32 rate_cap_tx_chainmask;
	u32 rate_cap_rx_chainmask;
	u32 ht_cap;

	rate_cap_tx_chainmask = ar->cfg_tx_chainmask >> cap->tx_chain_mask_shअगरt;
	rate_cap_rx_chainmask = ar->cfg_rx_chainmask >> cap->rx_chain_mask_shअगरt;

	अगर (cap->supported_bands & WMI_HOST_WLAN_2G_CAP) अणु
		band = &ar->mac.sbands[NL80211_BAND_2GHZ];
		ht_cap = cap->band[NL80211_BAND_2GHZ].ht_cap_info;
		अगर (ht_cap_info)
			*ht_cap_info = ht_cap;
		band->ht_cap = ath11k_create_ht_cap(ar, ht_cap,
						    rate_cap_rx_chainmask);
	पूर्ण

	अगर (cap->supported_bands & WMI_HOST_WLAN_5G_CAP && !ar->supports_6ghz) अणु
		band = &ar->mac.sbands[NL80211_BAND_5GHZ];
		ht_cap = cap->band[NL80211_BAND_5GHZ].ht_cap_info;
		अगर (ht_cap_info)
			*ht_cap_info = ht_cap;
		band->ht_cap = ath11k_create_ht_cap(ar, ht_cap,
						    rate_cap_rx_chainmask);
		band->vht_cap = ath11k_create_vht_cap(ar, rate_cap_tx_chainmask,
						      rate_cap_rx_chainmask);
	पूर्ण
पूर्ण

अटल पूर्णांक ath11k_check_chain_mask(काष्ठा ath11k *ar, u32 ant, bool is_tx_ant)
अणु
	/* TODO: Check the request chainmask against the supported
	 * chainmask table which is advertised in extented_service_पढ़ोy event
	 */

	वापस 0;
पूर्ण

अटल व्योम ath11k_gen_ppe_thresh(काष्ठा ath11k_ppe_threshold *fw_ppet,
				  u8 *he_ppet)
अणु
	पूर्णांक nss, ru;
	u8 bit = 7;

	he_ppet[0] = fw_ppet->numss_m1 & IEEE80211_PPE_THRES_NSS_MASK;
	he_ppet[0] |= (fw_ppet->ru_bit_mask <<
		       IEEE80211_PPE_THRES_RU_INDEX_BITMASK_POS) &
		      IEEE80211_PPE_THRES_RU_INDEX_BITMASK_MASK;
	क्रम (nss = 0; nss <= fw_ppet->numss_m1; nss++) अणु
		क्रम (ru = 0; ru < 4; ru++) अणु
			u8 val;
			पूर्णांक i;

			अगर ((fw_ppet->ru_bit_mask & BIT(ru)) == 0)
				जारी;
			val = (fw_ppet->ppet16_ppet8_ru3_ru0[nss] >> (ru * 6)) &
			       0x3f;
			val = ((val >> 3) & 0x7) | ((val & 0x7) << 3);
			क्रम (i = 5; i >= 0; i--) अणु
				he_ppet[bit / 8] |=
					((val >> i) & 0x1) << ((bit % 8));
				bit++;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
ath11k_mac_filter_he_cap_mesh(काष्ठा ieee80211_he_cap_elem *he_cap_elem)
अणु
	u8 m;

	m = IEEE80211_HE_MAC_CAP0_TWT_RES |
	    IEEE80211_HE_MAC_CAP0_TWT_REQ;
	he_cap_elem->mac_cap_info[0] &= ~m;

	m = IEEE80211_HE_MAC_CAP2_TRS |
	    IEEE80211_HE_MAC_CAP2_BCAST_TWT |
	    IEEE80211_HE_MAC_CAP2_MU_CASCADING;
	he_cap_elem->mac_cap_info[2] &= ~m;

	m = IEEE80211_HE_MAC_CAP3_FLEX_TWT_SCHED |
	    IEEE80211_HE_MAC_CAP2_BCAST_TWT |
	    IEEE80211_HE_MAC_CAP2_MU_CASCADING;
	he_cap_elem->mac_cap_info[3] &= ~m;

	m = IEEE80211_HE_MAC_CAP4_BSRP_BQRP_A_MPDU_AGG |
	    IEEE80211_HE_MAC_CAP4_BQR;
	he_cap_elem->mac_cap_info[4] &= ~m;

	m = IEEE80211_HE_MAC_CAP5_SUBCHAN_SELECTIVE_TRANSMISSION |
	    IEEE80211_HE_MAC_CAP5_UL_2x996_TONE_RU |
	    IEEE80211_HE_MAC_CAP5_PUNCTURED_SOUNDING |
	    IEEE80211_HE_MAC_CAP5_HT_VHT_TRIG_FRAME_RX;
	he_cap_elem->mac_cap_info[5] &= ~m;

	m = IEEE80211_HE_PHY_CAP2_UL_MU_FULL_MU_MIMO |
	    IEEE80211_HE_PHY_CAP2_UL_MU_PARTIAL_MU_MIMO;
	he_cap_elem->phy_cap_info[2] &= ~m;

	m = IEEE80211_HE_PHY_CAP3_RX_PARTIAL_BW_SU_IN_20MHZ_MU |
	    IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_MASK |
	    IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_RX_MASK;
	he_cap_elem->phy_cap_info[3] &= ~m;

	m = IEEE80211_HE_PHY_CAP4_MU_BEAMFORMER;
	he_cap_elem->phy_cap_info[4] &= ~m;

	m = IEEE80211_HE_PHY_CAP5_NG16_MU_FEEDBACK;
	he_cap_elem->phy_cap_info[5] &= ~m;

	m = IEEE80211_HE_PHY_CAP6_CODEBOOK_SIZE_75_MU |
	    IEEE80211_HE_PHY_CAP6_TRIG_MU_BEAMFORMING_PARTIAL_BW_FB |
	    IEEE80211_HE_PHY_CAP6_TRIG_CQI_FB |
	    IEEE80211_HE_PHY_CAP6_PARTIAL_BANDWIDTH_DL_MUMIMO;
	he_cap_elem->phy_cap_info[6] &= ~m;

	m = IEEE80211_HE_PHY_CAP7_PSR_BASED_SR |
	    IEEE80211_HE_PHY_CAP7_POWER_BOOST_FACTOR_SUPP |
	    IEEE80211_HE_PHY_CAP7_STBC_TX_ABOVE_80MHZ |
	    IEEE80211_HE_PHY_CAP7_STBC_RX_ABOVE_80MHZ;
	he_cap_elem->phy_cap_info[7] &= ~m;

	m = IEEE80211_HE_PHY_CAP8_HE_ER_SU_PPDU_4XLTF_AND_08_US_GI |
	    IEEE80211_HE_PHY_CAP8_20MHZ_IN_40MHZ_HE_PPDU_IN_2G |
	    IEEE80211_HE_PHY_CAP8_20MHZ_IN_160MHZ_HE_PPDU |
	    IEEE80211_HE_PHY_CAP8_80MHZ_IN_160MHZ_HE_PPDU;
	he_cap_elem->phy_cap_info[8] &= ~m;

	m = IEEE80211_HE_PHY_CAP9_LONGER_THAN_16_SIGB_OFDM_SYM |
	    IEEE80211_HE_PHY_CAP9_NON_TRIGGERED_CQI_FEEDBACK |
	    IEEE80211_HE_PHY_CAP9_RX_1024_QAM_LESS_THAN_242_TONE_RU |
	    IEEE80211_HE_PHY_CAP9_TX_1024_QAM_LESS_THAN_242_TONE_RU |
	    IEEE80211_HE_PHY_CAP9_RX_FULL_BW_SU_USING_MU_WITH_COMP_SIGB |
	    IEEE80211_HE_PHY_CAP9_RX_FULL_BW_SU_USING_MU_WITH_NON_COMP_SIGB;
	he_cap_elem->phy_cap_info[9] &= ~m;
पूर्ण

अटल __le16 ath11k_mac_setup_he_6ghz_cap(काष्ठा ath11k_pdev_cap *pcap,
					   काष्ठा ath11k_band_cap *bcap)
अणु
	u8 val;

	bcap->he_6ghz_capa = IEEE80211_HT_MPDU_DENSITY_NONE;
	अगर (bcap->ht_cap_info & WMI_HT_CAP_DYNAMIC_SMPS)
		bcap->he_6ghz_capa |=
			FIELD_PREP(IEEE80211_HE_6GHZ_CAP_SM_PS,
				   WLAN_HT_CAP_SM_PS_DYNAMIC);
	अन्यथा
		bcap->he_6ghz_capa |=
			FIELD_PREP(IEEE80211_HE_6GHZ_CAP_SM_PS,
				   WLAN_HT_CAP_SM_PS_DISABLED);
	val = FIELD_GET(IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK,
			pcap->vht_cap);
	bcap->he_6ghz_capa |=
		FIELD_PREP(IEEE80211_HE_6GHZ_CAP_MAX_AMPDU_LEN_EXP, val);
	val = FIELD_GET(IEEE80211_VHT_CAP_MAX_MPDU_MASK, pcap->vht_cap);
	bcap->he_6ghz_capa |=
		FIELD_PREP(IEEE80211_HE_6GHZ_CAP_MAX_MPDU_LEN, val);
	अगर (pcap->vht_cap & IEEE80211_VHT_CAP_RX_ANTENNA_PATTERN)
		bcap->he_6ghz_capa |= IEEE80211_HE_6GHZ_CAP_RX_ANTPAT_CONS;
	अगर (pcap->vht_cap & IEEE80211_VHT_CAP_TX_ANTENNA_PATTERN)
		bcap->he_6ghz_capa |= IEEE80211_HE_6GHZ_CAP_TX_ANTPAT_CONS;

	वापस cpu_to_le16(bcap->he_6ghz_capa);
पूर्ण

अटल पूर्णांक ath11k_mac_copy_he_cap(काष्ठा ath11k *ar,
				  काष्ठा ath11k_pdev_cap *cap,
				  काष्ठा ieee80211_sband_अगरtype_data *data,
				  पूर्णांक band)
अणु
	पूर्णांक i, idx = 0;

	क्रम (i = 0; i < NUM_NL80211_IFTYPES; i++) अणु
		काष्ठा ieee80211_sta_he_cap *he_cap = &data[idx].he_cap;
		काष्ठा ath11k_band_cap *band_cap = &cap->band[band];
		काष्ठा ieee80211_he_cap_elem *he_cap_elem =
				&he_cap->he_cap_elem;

		चयन (i) अणु
		हाल NL80211_IFTYPE_STATION:
		हाल NL80211_IFTYPE_AP:
		हाल NL80211_IFTYPE_MESH_POINT:
			अवरोध;

		शेष:
			जारी;
		पूर्ण

		data[idx].types_mask = BIT(i);
		he_cap->has_he = true;
		स_नकल(he_cap_elem->mac_cap_info, band_cap->he_cap_info,
		       माप(he_cap_elem->mac_cap_info));
		स_नकल(he_cap_elem->phy_cap_info, band_cap->he_cap_phy_info,
		       माप(he_cap_elem->phy_cap_info));

		he_cap_elem->mac_cap_info[1] &=
			IEEE80211_HE_MAC_CAP1_TF_MAC_PAD_DUR_MASK;

		he_cap_elem->phy_cap_info[5] &=
			~IEEE80211_HE_PHY_CAP5_BEAMFORMEE_NUM_SND_DIM_UNDER_80MHZ_MASK;
		he_cap_elem->phy_cap_info[5] |= ar->num_tx_chains - 1;

		चयन (i) अणु
		हाल NL80211_IFTYPE_AP:
			he_cap_elem->phy_cap_info[3] &=
				~IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_MASK;
			he_cap_elem->phy_cap_info[9] |=
				IEEE80211_HE_PHY_CAP9_RX_1024_QAM_LESS_THAN_242_TONE_RU;
			अवरोध;
		हाल NL80211_IFTYPE_STATION:
			he_cap_elem->mac_cap_info[0] &=
				~IEEE80211_HE_MAC_CAP0_TWT_RES;
			he_cap_elem->mac_cap_info[0] |=
				IEEE80211_HE_MAC_CAP0_TWT_REQ;
			he_cap_elem->phy_cap_info[9] |=
				IEEE80211_HE_PHY_CAP9_TX_1024_QAM_LESS_THAN_242_TONE_RU;
			अवरोध;
		हाल NL80211_IFTYPE_MESH_POINT:
			ath11k_mac_filter_he_cap_mesh(he_cap_elem);
			अवरोध;
		पूर्ण

		he_cap->he_mcs_nss_supp.rx_mcs_80 =
			cpu_to_le16(band_cap->he_mcs & 0xffff);
		he_cap->he_mcs_nss_supp.tx_mcs_80 =
			cpu_to_le16(band_cap->he_mcs & 0xffff);
		he_cap->he_mcs_nss_supp.rx_mcs_160 =
			cpu_to_le16((band_cap->he_mcs >> 16) & 0xffff);
		he_cap->he_mcs_nss_supp.tx_mcs_160 =
			cpu_to_le16((band_cap->he_mcs >> 16) & 0xffff);
		he_cap->he_mcs_nss_supp.rx_mcs_80p80 =
			cpu_to_le16((band_cap->he_mcs >> 16) & 0xffff);
		he_cap->he_mcs_nss_supp.tx_mcs_80p80 =
			cpu_to_le16((band_cap->he_mcs >> 16) & 0xffff);

		स_रखो(he_cap->ppe_thres, 0, माप(he_cap->ppe_thres));
		अगर (he_cap_elem->phy_cap_info[6] &
		    IEEE80211_HE_PHY_CAP6_PPE_THRESHOLD_PRESENT)
			ath11k_gen_ppe_thresh(&band_cap->he_ppet,
					      he_cap->ppe_thres);

		अगर (band == NL80211_BAND_6GHZ) अणु
			data[idx].he_6ghz_capa.capa =
				ath11k_mac_setup_he_6ghz_cap(cap, band_cap);
		पूर्ण
		idx++;
	पूर्ण

	वापस idx;
पूर्ण

अटल व्योम ath11k_mac_setup_he_cap(काष्ठा ath11k *ar,
				    काष्ठा ath11k_pdev_cap *cap)
अणु
	काष्ठा ieee80211_supported_band *band;
	पूर्णांक count;

	अगर (cap->supported_bands & WMI_HOST_WLAN_2G_CAP) अणु
		count = ath11k_mac_copy_he_cap(ar, cap,
					       ar->mac.अगरtype[NL80211_BAND_2GHZ],
					       NL80211_BAND_2GHZ);
		band = &ar->mac.sbands[NL80211_BAND_2GHZ];
		band->अगरtype_data = ar->mac.अगरtype[NL80211_BAND_2GHZ];
		band->n_अगरtype_data = count;
	पूर्ण

	अगर (cap->supported_bands & WMI_HOST_WLAN_5G_CAP) अणु
		count = ath11k_mac_copy_he_cap(ar, cap,
					       ar->mac.अगरtype[NL80211_BAND_5GHZ],
					       NL80211_BAND_5GHZ);
		band = &ar->mac.sbands[NL80211_BAND_5GHZ];
		band->अगरtype_data = ar->mac.अगरtype[NL80211_BAND_5GHZ];
		band->n_अगरtype_data = count;
	पूर्ण

	अगर (cap->supported_bands & WMI_HOST_WLAN_5G_CAP &&
	    ar->supports_6ghz) अणु
		count = ath11k_mac_copy_he_cap(ar, cap,
					       ar->mac.अगरtype[NL80211_BAND_6GHZ],
					       NL80211_BAND_6GHZ);
		band = &ar->mac.sbands[NL80211_BAND_6GHZ];
		band->अगरtype_data = ar->mac.अगरtype[NL80211_BAND_6GHZ];
		band->n_अगरtype_data = count;
	पूर्ण
पूर्ण

अटल पूर्णांक __ath11k_set_antenna(काष्ठा ath11k *ar, u32 tx_ant, u32 rx_ant)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (ath11k_check_chain_mask(ar, tx_ant, true))
		वापस -EINVAL;

	अगर (ath11k_check_chain_mask(ar, rx_ant, false))
		वापस -EINVAL;

	ar->cfg_tx_chainmask = tx_ant;
	ar->cfg_rx_chainmask = rx_ant;

	अगर (ar->state != ATH11K_STATE_ON &&
	    ar->state != ATH11K_STATE_RESTARTED)
		वापस 0;

	ret = ath11k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_TX_CHAIN_MASK,
					tx_ant, ar->pdev->pdev_id);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to set tx-chainmask: %d, req 0x%x\n",
			    ret, tx_ant);
		वापस ret;
	पूर्ण

	ar->num_tx_chains = get_num_chains(tx_ant);

	ret = ath11k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_RX_CHAIN_MASK,
					rx_ant, ar->pdev->pdev_id);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to set rx-chainmask: %d, req 0x%x\n",
			    ret, rx_ant);
		वापस ret;
	पूर्ण

	ar->num_rx_chains = get_num_chains(rx_ant);

	/* Reload HT/VHT/HE capability */
	ath11k_mac_setup_ht_vht_cap(ar, &ar->pdev->cap, शून्य);
	ath11k_mac_setup_he_cap(ar, &ar->pdev->cap);

	वापस 0;
पूर्ण

पूर्णांक ath11k_mac_tx_mgmt_pending_मुक्त(पूर्णांक buf_id, व्योम *skb, व्योम *ctx)
अणु
	काष्ठा sk_buff *msdu = skb;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ath11k *ar = ctx;
	काष्ठा ath11k_base *ab = ar->ab;

	spin_lock_bh(&ar->txmgmt_idr_lock);
	idr_हटाओ(&ar->txmgmt_idr, buf_id);
	spin_unlock_bh(&ar->txmgmt_idr_lock);
	dma_unmap_single(ab->dev, ATH11K_SKB_CB(msdu)->paddr, msdu->len,
			 DMA_TO_DEVICE);

	info = IEEE80211_SKB_CB(msdu);
	स_रखो(&info->status, 0, माप(info->status));

	ieee80211_मुक्त_txskb(ar->hw, msdu);

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_mac_vअगर_txmgmt_idr_हटाओ(पूर्णांक buf_id, व्योम *skb, व्योम *ctx)
अणु
	काष्ठा ieee80211_vअगर *vअगर = ctx;
	काष्ठा ath11k_skb_cb *skb_cb = ATH11K_SKB_CB((काष्ठा sk_buff *)skb);
	काष्ठा sk_buff *msdu = skb;
	काष्ठा ath11k *ar = skb_cb->ar;
	काष्ठा ath11k_base *ab = ar->ab;

	अगर (skb_cb->vअगर == vअगर) अणु
		spin_lock_bh(&ar->txmgmt_idr_lock);
		idr_हटाओ(&ar->txmgmt_idr, buf_id);
		spin_unlock_bh(&ar->txmgmt_idr_lock);
		dma_unmap_single(ab->dev, skb_cb->paddr, msdu->len,
				 DMA_TO_DEVICE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_mac_mgmt_tx_wmi(काष्ठा ath11k *ar, काष्ठा ath11k_vअगर *arvअगर,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_tx_info *info;
	dma_addr_t paddr;
	पूर्णांक buf_id;
	पूर्णांक ret;

	spin_lock_bh(&ar->txmgmt_idr_lock);
	buf_id = idr_alloc(&ar->txmgmt_idr, skb, 0,
			   ATH11K_TX_MGMT_NUM_PENDING_MAX, GFP_ATOMIC);
	spin_unlock_bh(&ar->txmgmt_idr_lock);
	अगर (buf_id < 0)
		वापस -ENOSPC;

	info = IEEE80211_SKB_CB(skb);
	अगर (!(info->flags & IEEE80211_TX_CTL_HW_80211_ENCAP)) अणु
		अगर ((ieee80211_is_action(hdr->frame_control) ||
		     ieee80211_is_deauth(hdr->frame_control) ||
		     ieee80211_is_disassoc(hdr->frame_control)) &&
		     ieee80211_has_रक्षित(hdr->frame_control)) अणु
			skb_put(skb, IEEE80211_CCMP_MIC_LEN);
		पूर्ण
	पूर्ण

	paddr = dma_map_single(ab->dev, skb->data, skb->len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(ab->dev, paddr)) अणु
		ath11k_warn(ab, "failed to DMA map mgmt Tx buffer\n");
		ret = -EIO;
		जाओ err_मुक्त_idr;
	पूर्ण

	ATH11K_SKB_CB(skb)->paddr = paddr;

	ret = ath11k_wmi_mgmt_send(ar, arvअगर->vdev_id, buf_id, skb);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send mgmt frame: %d\n", ret);
		जाओ err_unmap_buf;
	पूर्ण

	वापस 0;

err_unmap_buf:
	dma_unmap_single(ab->dev, ATH11K_SKB_CB(skb)->paddr,
			 skb->len, DMA_TO_DEVICE);
err_मुक्त_idr:
	spin_lock_bh(&ar->txmgmt_idr_lock);
	idr_हटाओ(&ar->txmgmt_idr, buf_id);
	spin_unlock_bh(&ar->txmgmt_idr_lock);

	वापस ret;
पूर्ण

अटल व्योम ath11k_mgmt_over_wmi_tx_purge(काष्ठा ath11k *ar)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(&ar->wmi_mgmt_tx_queue)) != शून्य)
		ieee80211_मुक्त_txskb(ar->hw, skb);
पूर्ण

अटल व्योम ath11k_mgmt_over_wmi_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath11k *ar = container_of(work, काष्ठा ath11k, wmi_mgmt_tx_work);
	काष्ठा ath11k_skb_cb *skb_cb;
	काष्ठा ath11k_vअगर *arvअगर;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;

	जबतक ((skb = skb_dequeue(&ar->wmi_mgmt_tx_queue)) != शून्य) अणु
		skb_cb = ATH11K_SKB_CB(skb);
		अगर (!skb_cb->vअगर) अणु
			ath11k_warn(ar->ab, "no vif found for mgmt frame\n");
			ieee80211_मुक्त_txskb(ar->hw, skb);
			जारी;
		पूर्ण

		arvअगर = ath11k_vअगर_to_arvअगर(skb_cb->vअगर);
		अगर (ar->allocated_vdev_map & (1LL << arvअगर->vdev_id) &&
		    arvअगर->is_started) अणु
			ret = ath11k_mac_mgmt_tx_wmi(ar, arvअगर, skb);
			अगर (ret) अणु
				ath11k_warn(ar->ab, "failed to tx mgmt frame, vdev_id %d :%d\n",
					    arvअगर->vdev_id, ret);
				ieee80211_मुक्त_txskb(ar->hw, skb);
			पूर्ण अन्यथा अणु
				atomic_inc(&ar->num_pending_mgmt_tx);
			पूर्ण
		पूर्ण अन्यथा अणु
			ath11k_warn(ar->ab,
				    "dropping mgmt frame for vdev %d, is_started %d\n",
				    arvअगर->vdev_id,
				    arvअगर->is_started);
			ieee80211_मुक्त_txskb(ar->hw, skb);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ath11k_mac_mgmt_tx(काष्ठा ath11k *ar, काष्ठा sk_buff *skb,
			      bool is_prb_rsp)
अणु
	काष्ठा sk_buff_head *q = &ar->wmi_mgmt_tx_queue;

	अगर (test_bit(ATH11K_FLAG_CRASH_FLUSH, &ar->ab->dev_flags))
		वापस -ESHUTDOWN;

	/* Drop probe response packets when the pending management tx
	 * count has reached a certain threshold, so as to prioritize
	 * other mgmt packets like auth and assoc to be sent on समय
	 * क्रम establishing successful connections.
	 */
	अगर (is_prb_rsp &&
	    atomic_पढ़ो(&ar->num_pending_mgmt_tx) > ATH11K_PRB_RSP_DROP_THRESHOLD) अणु
		ath11k_warn(ar->ab,
			    "dropping probe response as pending queue is almost full\n");
		वापस -ENOSPC;
	पूर्ण

	अगर (skb_queue_len_lockless(q) >= ATH11K_TX_MGMT_NUM_PENDING_MAX) अणु
		ath11k_warn(ar->ab, "mgmt tx queue is full\n");
		वापस -ENOSPC;
	पूर्ण

	skb_queue_tail(q, skb);
	ieee80211_queue_work(ar->hw, &ar->wmi_mgmt_tx_work);

	वापस 0;
पूर्ण

अटल व्योम ath11k_mac_op_tx(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_tx_control *control,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा ath11k_skb_cb *skb_cb = ATH11K_SKB_CB(skb);
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_vअगर *vअगर = info->control.vअगर;
	काष्ठा ath11k_vअगर *arvअगर = ath11k_vअगर_to_arvअगर(vअगर);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा ieee80211_key_conf *key = info->control.hw_key;
	u32 info_flags = info->flags;
	bool is_prb_rsp;
	पूर्णांक ret;

	स_रखो(skb_cb, 0, माप(*skb_cb));
	skb_cb->vअगर = vअगर;

	अगर (key) अणु
		skb_cb->cipher = key->cipher;
		skb_cb->flags |= ATH11K_SKB_CIPHER_SET;
	पूर्ण

	अगर (info_flags & IEEE80211_TX_CTL_HW_80211_ENCAP) अणु
		skb_cb->flags |= ATH11K_SKB_HW_80211_ENCAP;
	पूर्ण अन्यथा अगर (ieee80211_is_mgmt(hdr->frame_control)) अणु
		is_prb_rsp = ieee80211_is_probe_resp(hdr->frame_control);
		ret = ath11k_mac_mgmt_tx(ar, skb, is_prb_rsp);
		अगर (ret) अणु
			ath11k_warn(ar->ab, "failed to queue management frame %d\n",
				    ret);
			ieee80211_मुक्त_txskb(ar->hw, skb);
		पूर्ण
		वापस;
	पूर्ण

	ret = ath11k_dp_tx(ar, arvअगर, skb);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to transmit frame %d\n", ret);
		ieee80211_मुक्त_txskb(ar->hw, skb);
	पूर्ण
पूर्ण

व्योम ath11k_mac_drain_tx(काष्ठा ath11k *ar)
अणु
	/* make sure rcu-रक्षित mac80211 tx path itself is drained */
	synchronize_net();

	cancel_work_sync(&ar->wmi_mgmt_tx_work);
	ath11k_mgmt_over_wmi_tx_purge(ar);
पूर्ण

अटल पूर्णांक ath11k_mac_config_mon_status_शेष(काष्ठा ath11k *ar, bool enable)
अणु
	काष्ठा htt_rx_ring_tlv_filter tlv_filter = अणु0पूर्ण;
	काष्ठा ath11k_base *ab = ar->ab;
	पूर्णांक i, ret = 0;
	u32 ring_id;

	अगर (enable) अणु
		tlv_filter = ath11k_mac_mon_status_filter_शेष;
		अगर (ath11k_debugfs_rx_filter(ar))
			tlv_filter.rx_filter = ath11k_debugfs_rx_filter(ar);
	पूर्ण

	क्रम (i = 0; i < ab->hw_params.num_rxmda_per_pdev; i++) अणु
		ring_id = ar->dp.rx_mon_status_refill_ring[i].refill_buf_ring.ring_id;
		ret = ath11k_dp_tx_htt_rx_filter_setup(ar->ab, ring_id,
						       ar->dp.mac_id + i,
						       HAL_RXDMA_MONITOR_STATUS,
						       DP_RX_BUFFER_SIZE,
						       &tlv_filter);
	पूर्ण

	अगर (enable && !ar->ab->hw_params.rxdma1_enable)
		mod_समयr(&ar->ab->mon_reap_समयr, jअगरfies +
			  msecs_to_jअगरfies(ATH11K_MON_TIMER_INTERVAL));

	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_mac_op_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_pdev *pdev = ar->pdev;
	पूर्णांक ret;

	ath11k_mac_drain_tx(ar);
	mutex_lock(&ar->conf_mutex);

	चयन (ar->state) अणु
	हाल ATH11K_STATE_OFF:
		ar->state = ATH11K_STATE_ON;
		अवरोध;
	हाल ATH11K_STATE_RESTARTING:
		ar->state = ATH11K_STATE_RESTARTED;
		अवरोध;
	हाल ATH11K_STATE_RESTARTED:
	हाल ATH11K_STATE_WEDGED:
	हाल ATH11K_STATE_ON:
		WARN_ON(1);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = ath11k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_PMF_QOS,
					1, pdev->pdev_id);

	अगर (ret) अणु
		ath11k_err(ar->ab, "failed to enable PMF QOS: (%d\n", ret);
		जाओ err;
	पूर्ण

	ret = ath11k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_DYNAMIC_BW, 1,
					pdev->pdev_id);
	अगर (ret) अणु
		ath11k_err(ar->ab, "failed to enable dynamic bw: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = ath11k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_ARP_AC_OVERRIDE,
					0, pdev->pdev_id);
	अगर (ret) अणु
		ath11k_err(ab, "failed to set ac override for ARP: %d\n",
			   ret);
		जाओ err;
	पूर्ण

	ret = ath11k_wmi_send_dfs_phyerr_offload_enable_cmd(ar, pdev->pdev_id);
	अगर (ret) अणु
		ath11k_err(ab, "failed to offload radar detection: %d\n",
			   ret);
		जाओ err;
	पूर्ण

	ret = ath11k_dp_tx_htt_h2t_ppdu_stats_req(ar,
						  HTT_PPDU_STATS_TAG_DEFAULT);
	अगर (ret) अणु
		ath11k_err(ab, "failed to req ppdu stats: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = ath11k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_MESH_MCAST_ENABLE,
					1, pdev->pdev_id);

	अगर (ret) अणु
		ath11k_err(ar->ab, "failed to enable MESH MCAST ENABLE: (%d\n", ret);
		जाओ err;
	पूर्ण

	__ath11k_set_antenna(ar, ar->cfg_tx_chainmask, ar->cfg_rx_chainmask);

	/* TODO: Do we need to enable ANI? */

	ath11k_reg_update_chan_list(ar);

	ar->num_started_vdevs = 0;
	ar->num_created_vdevs = 0;
	ar->num_peers = 0;
	ar->allocated_vdev_map = 0;

	/* Configure monitor status ring with शेष rx_filter to get rx status
	 * such as rssi, rx_duration.
	 */
	ret = ath11k_mac_config_mon_status_शेष(ar, true);
	अगर (ret) अणु
		ath11k_err(ab, "failed to configure monitor status ring with default rx_filter: (%d)\n",
			   ret);
		जाओ err;
	पूर्ण

	/* Configure the hash seed क्रम hash based reo dest ring selection */
	ath11k_wmi_pdev_lro_cfg(ar, ar->pdev->pdev_id);

	/* allow device to enter IMPS */
	अगर (ab->hw_params.idle_ps) अणु
		ret = ath11k_wmi_pdev_set_param(ar, WMI_PDEV_PARAM_IDLE_PS_CONFIG,
						1, pdev->pdev_id);
		अगर (ret) अणु
			ath11k_err(ab, "failed to enable idle ps: %d\n", ret);
			जाओ err;
		पूर्ण
	पूर्ण

	mutex_unlock(&ar->conf_mutex);

	rcu_assign_poपूर्णांकer(ab->pdevs_active[ar->pdev_idx],
			   &ab->pdevs[ar->pdev_idx]);

	वापस 0;

err:
	ar->state = ATH11K_STATE_OFF;
	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

अटल व्योम ath11k_mac_op_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा htt_ppdu_stats_info *ppdu_stats, *पंचांगp;
	पूर्णांक ret;

	ath11k_mac_drain_tx(ar);

	mutex_lock(&ar->conf_mutex);
	ret = ath11k_mac_config_mon_status_शेष(ar, false);
	अगर (ret)
		ath11k_err(ar->ab, "failed to clear rx_filter for monitor status ring: (%d)\n",
			   ret);

	clear_bit(ATH11K_CAC_RUNNING, &ar->dev_flags);
	ar->state = ATH11K_STATE_OFF;
	mutex_unlock(&ar->conf_mutex);

	cancel_delayed_work_sync(&ar->scan.समयout);
	cancel_work_sync(&ar->regd_update_work);

	spin_lock_bh(&ar->data_lock);
	list_क्रम_each_entry_safe(ppdu_stats, पंचांगp, &ar->ppdu_stats_info, list) अणु
		list_del(&ppdu_stats->list);
		kमुक्त(ppdu_stats);
	पूर्ण
	spin_unlock_bh(&ar->data_lock);

	rcu_assign_poपूर्णांकer(ar->ab->pdevs_active[ar->pdev_idx], शून्य);

	synchronize_rcu();

	atomic_set(&ar->num_pending_mgmt_tx, 0);
पूर्ण

अटल व्योम
ath11k_mac_setup_vdev_create_params(काष्ठा ath11k_vअगर *arvअगर,
				    काष्ठा vdev_create_params *params)
अणु
	काष्ठा ath11k *ar = arvअगर->ar;
	काष्ठा ath11k_pdev *pdev = ar->pdev;

	params->अगर_id = arvअगर->vdev_id;
	params->type = arvअगर->vdev_type;
	params->subtype = arvअगर->vdev_subtype;
	params->pdev_id = pdev->pdev_id;

	अगर (pdev->cap.supported_bands & WMI_HOST_WLAN_2G_CAP) अणु
		params->chains[NL80211_BAND_2GHZ].tx = ar->num_tx_chains;
		params->chains[NL80211_BAND_2GHZ].rx = ar->num_rx_chains;
	पूर्ण
	अगर (pdev->cap.supported_bands & WMI_HOST_WLAN_5G_CAP) अणु
		params->chains[NL80211_BAND_5GHZ].tx = ar->num_tx_chains;
		params->chains[NL80211_BAND_5GHZ].rx = ar->num_rx_chains;
	पूर्ण
	अगर (pdev->cap.supported_bands & WMI_HOST_WLAN_5G_CAP &&
	    ar->supports_6ghz) अणु
		params->chains[NL80211_BAND_6GHZ].tx = ar->num_tx_chains;
		params->chains[NL80211_BAND_6GHZ].rx = ar->num_rx_chains;
	पूर्ण
पूर्ण

अटल u32
ath11k_mac_prepare_he_mode(काष्ठा ath11k_pdev *pdev, u32 vअगरtype)
अणु
	काष्ठा ath11k_pdev_cap *pdev_cap = &pdev->cap;
	काष्ठा ath11k_band_cap *cap_band = शून्य;
	u32 *hecap_phy_ptr = शून्य;
	u32 hemode = 0;

	अगर (pdev->cap.supported_bands & WMI_HOST_WLAN_2G_CAP)
		cap_band = &pdev_cap->band[NL80211_BAND_2GHZ];
	अन्यथा
		cap_band = &pdev_cap->band[NL80211_BAND_5GHZ];

	hecap_phy_ptr = &cap_band->he_cap_phy_info[0];

	hemode = FIELD_PREP(HE_MODE_SU_TX_BFEE, HE_SU_BFEE_ENABLE) |
		 FIELD_PREP(HE_MODE_SU_TX_BFER, HECAP_PHY_SUBFMR_GET(hecap_phy_ptr)) |
		 FIELD_PREP(HE_MODE_UL_MUMIMO, HECAP_PHY_ULMUMIMO_GET(hecap_phy_ptr));

	/* TODO WDS and other modes */
	अगर (vअगरtype == NL80211_IFTYPE_AP) अणु
		hemode |= FIELD_PREP(HE_MODE_MU_TX_BFER,
			  HECAP_PHY_MUBFMR_GET(hecap_phy_ptr)) |
			  FIELD_PREP(HE_MODE_DL_OFDMA, HE_DL_MUOFDMA_ENABLE) |
			  FIELD_PREP(HE_MODE_UL_OFDMA, HE_UL_MUOFDMA_ENABLE);
	पूर्ण अन्यथा अणु
		hemode |= FIELD_PREP(HE_MODE_MU_TX_BFEE, HE_MU_BFEE_ENABLE);
	पूर्ण

	वापस hemode;
पूर्ण

अटल पूर्णांक ath11k_set_he_mu_sounding_mode(काष्ठा ath11k *ar,
					  काष्ठा ath11k_vअगर *arvअगर)
अणु
	u32 param_id, param_value;
	काष्ठा ath11k_base *ab = ar->ab;
	पूर्णांक ret = 0;

	param_id = WMI_VDEV_PARAM_SET_HEMU_MODE;
	param_value = ath11k_mac_prepare_he_mode(ar->pdev, arvअगर->vअगर->type);
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
					    param_id, param_value);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to set vdev %d HE MU mode: %d param_value %x\n",
			    arvअगर->vdev_id, ret, param_value);
		वापस ret;
	पूर्ण
	param_id = WMI_VDEV_PARAM_SET_HE_SOUNDING_MODE;
	param_value =
		FIELD_PREP(HE_VHT_SOUNDING_MODE, HE_VHT_SOUNDING_MODE_ENABLE) |
		FIELD_PREP(HE_TRIG_NONTRIG_SOUNDING_MODE,
			   HE_TRIG_NONTRIG_SOUNDING_MODE_ENABLE);
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
					    param_id, param_value);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to set vdev %d HE MU mode: %d\n",
			    arvअगर->vdev_id, ret);
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम ath11k_mac_op_update_vअगर_offload(काष्ठा ieee80211_hw *hw,
					     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_vअगर *arvअगर = ath11k_vअगर_to_arvअगर(vअगर);
	u32 param_id, param_value;
	पूर्णांक ret;

	param_id = WMI_VDEV_PARAM_TX_ENCAP_TYPE;
	अगर (ath11k_frame_mode != ATH11K_HW_TXRX_ETHERNET ||
	    (vअगर->type != NL80211_IFTYPE_STATION &&
	     vअगर->type != NL80211_IFTYPE_AP))
		vअगर->offload_flags &= ~IEEE80211_OFFLOAD_ENCAP_ENABLED;

	अगर (vअगर->offload_flags & IEEE80211_OFFLOAD_ENCAP_ENABLED)
		param_value = ATH11K_HW_TXRX_ETHERNET;
	अन्यथा अगर (test_bit(ATH11K_FLAG_RAW_MODE, &ab->dev_flags))
		param_value = ATH11K_HW_TXRX_RAW;
	अन्यथा
		param_value = ATH11K_HW_TXRX_NATIVE_WIFI;

	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
					    param_id, param_value);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to set vdev %d tx encap mode: %d\n",
			    arvअगर->vdev_id, ret);
		vअगर->offload_flags &= ~IEEE80211_OFFLOAD_ENCAP_ENABLED;
	पूर्ण
पूर्ण

अटल पूर्णांक ath11k_mac_op_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_vअगर *arvअगर = ath11k_vअगर_to_arvअगर(vअगर);
	काष्ठा vdev_create_params vdev_param = अणु0पूर्ण;
	काष्ठा peer_create_params peer_param;
	u32 param_id, param_value;
	u16 nss;
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक bit;

	vअगर->driver_flags |= IEEE80211_VIF_SUPPORTS_UAPSD;

	mutex_lock(&ar->conf_mutex);

	अगर (vअगर->type == NL80211_IFTYPE_AP &&
	    ar->num_peers > (ar->max_num_peers - 1)) अणु
		ath11k_warn(ab, "failed to create vdev due to insufficient peer entry resource in firmware\n");
		ret = -ENOBUFS;
		जाओ err;
	पूर्ण

	अगर (ar->num_created_vdevs > (TARGET_NUM_VDEVS - 1)) अणु
		ath11k_warn(ab, "failed to create vdev, reached max vdev limit %d\n",
			    TARGET_NUM_VDEVS);
		ret = -EBUSY;
		जाओ err;
	पूर्ण

	स_रखो(arvअगर, 0, माप(*arvअगर));

	arvअगर->ar = ar;
	arvअगर->vअगर = vअगर;

	INIT_LIST_HEAD(&arvअगर->list);
	INIT_DELAYED_WORK(&arvअगर->connection_loss_work,
			  ath11k_mac_vअगर_sta_connection_loss_work);

	क्रम (i = 0; i < ARRAY_SIZE(arvअगर->bitrate_mask.control); i++) अणु
		arvअगर->bitrate_mask.control[i].legacy = 0xffffffff;
		स_रखो(arvअगर->bitrate_mask.control[i].ht_mcs, 0xff,
		       माप(arvअगर->bitrate_mask.control[i].ht_mcs));
		स_रखो(arvअगर->bitrate_mask.control[i].vht_mcs, 0xff,
		       माप(arvअगर->bitrate_mask.control[i].vht_mcs));
	पूर्ण

	bit = __ffs64(ab->मुक्त_vdev_map);

	arvअगर->vdev_id = bit;
	arvअगर->vdev_subtype = WMI_VDEV_SUBTYPE_NONE;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_UNSPECIFIED:
	हाल NL80211_IFTYPE_STATION:
		arvअगर->vdev_type = WMI_VDEV_TYPE_STA;
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
		arvअगर->vdev_subtype = WMI_VDEV_SUBTYPE_MESH_11S;
		fallthrough;
	हाल NL80211_IFTYPE_AP:
		arvअगर->vdev_type = WMI_VDEV_TYPE_AP;
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
		arvअगर->vdev_type = WMI_VDEV_TYPE_MONITOR;
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac add interface id %d type %d subtype %d map %llx\n",
		   arvअगर->vdev_id, arvअगर->vdev_type, arvअगर->vdev_subtype,
		   ab->मुक्त_vdev_map);

	vअगर->cab_queue = arvअगर->vdev_id % (ATH11K_HW_MAX_QUEUES - 1);
	क्रम (i = 0; i < ARRAY_SIZE(vअगर->hw_queue); i++)
		vअगर->hw_queue[i] = i % (ATH11K_HW_MAX_QUEUES - 1);

	ath11k_mac_setup_vdev_create_params(arvअगर, &vdev_param);

	ret = ath11k_wmi_vdev_create(ar, vअगर->addr, &vdev_param);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to create WMI vdev %d: %d\n",
			    arvअगर->vdev_id, ret);
		जाओ err;
	पूर्ण

	ar->num_created_vdevs++;
	ath11k_dbg(ab, ATH11K_DBG_MAC, "vdev %pM created, vdev_id %d\n",
		   vअगर->addr, arvअगर->vdev_id);
	ar->allocated_vdev_map |= 1LL << arvअगर->vdev_id;
	ab->मुक्त_vdev_map &= ~(1LL << arvअगर->vdev_id);

	spin_lock_bh(&ar->data_lock);
	list_add(&arvअगर->list, &ar->arvअगरs);
	spin_unlock_bh(&ar->data_lock);

	ath11k_mac_op_update_vअगर_offload(hw, vअगर);

	nss = get_num_chains(ar->cfg_tx_chainmask) ? : 1;
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
					    WMI_VDEV_PARAM_NSS, nss);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to set vdev %d chainmask 0x%x, nss %d :%d\n",
			    arvअगर->vdev_id, ar->cfg_tx_chainmask, nss, ret);
		जाओ err_vdev_del;
	पूर्ण

	चयन (arvअगर->vdev_type) अणु
	हाल WMI_VDEV_TYPE_AP:
		peer_param.vdev_id = arvअगर->vdev_id;
		peer_param.peer_addr = vअगर->addr;
		peer_param.peer_type = WMI_PEER_TYPE_DEFAULT;
		ret = ath11k_peer_create(ar, arvअगर, शून्य, &peer_param);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to vdev %d create peer for AP: %d\n",
				    arvअगर->vdev_id, ret);
			जाओ err_vdev_del;
		पूर्ण

		ret = ath11k_mac_set_kickout(arvअगर);
		अगर (ret) अणु
			ath11k_warn(ar->ab, "failed to set vdev %i kickout parameters: %d\n",
				    arvअगर->vdev_id, ret);
			जाओ err_peer_del;
		पूर्ण
		अवरोध;
	हाल WMI_VDEV_TYPE_STA:
		param_id = WMI_STA_PS_PARAM_RX_WAKE_POLICY;
		param_value = WMI_STA_PS_RX_WAKE_POLICY_WAKE;
		ret = ath11k_wmi_set_sta_ps_param(ar, arvअगर->vdev_id,
						  param_id, param_value);
		अगर (ret) अणु
			ath11k_warn(ar->ab, "failed to set vdev %d RX wake policy: %d\n",
				    arvअगर->vdev_id, ret);
			जाओ err_peer_del;
		पूर्ण

		param_id = WMI_STA_PS_PARAM_TX_WAKE_THRESHOLD;
		param_value = WMI_STA_PS_TX_WAKE_THRESHOLD_ALWAYS;
		ret = ath11k_wmi_set_sta_ps_param(ar, arvअगर->vdev_id,
						  param_id, param_value);
		अगर (ret) अणु
			ath11k_warn(ar->ab, "failed to set vdev %d TX wake threshold: %d\n",
				    arvअगर->vdev_id, ret);
			जाओ err_peer_del;
		पूर्ण

		param_id = WMI_STA_PS_PARAM_PSPOLL_COUNT;
		param_value = WMI_STA_PS_PSPOLL_COUNT_NO_MAX;
		ret = ath11k_wmi_set_sta_ps_param(ar, arvअगर->vdev_id,
						  param_id, param_value);
		अगर (ret) अणु
			ath11k_warn(ar->ab, "failed to set vdev %d pspoll count: %d\n",
				    arvअगर->vdev_id, ret);
			जाओ err_peer_del;
		पूर्ण

		ret = ath11k_wmi_pdev_set_ps_mode(ar, arvअगर->vdev_id, false);
		अगर (ret) अणु
			ath11k_warn(ar->ab, "failed to disable vdev %d ps mode: %d\n",
				    arvअगर->vdev_id, ret);
			जाओ err_peer_del;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	arvअगर->txघातer = vअगर->bss_conf.txघातer;
	ret = ath11k_mac_txघातer_recalc(ar);
	अगर (ret)
		जाओ err_peer_del;

	param_id = WMI_VDEV_PARAM_RTS_THRESHOLD;
	param_value = ar->hw->wiphy->rts_threshold;
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
					    param_id, param_value);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to set rts threshold for vdev %d: %d\n",
			    arvअगर->vdev_id, ret);
	पूर्ण

	ath11k_dp_vdev_tx_attach(ar, arvअगर);

	mutex_unlock(&ar->conf_mutex);

	वापस 0;

err_peer_del:
	अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_AP) अणु
		reinit_completion(&ar->peer_delete_करोne);

		ret = ath11k_wmi_send_peer_delete_cmd(ar, vअगर->addr,
						      arvअगर->vdev_id);
		अगर (ret) अणु
			ath11k_warn(ar->ab, "failed to delete peer vdev_id %d addr %pM\n",
				    arvअगर->vdev_id, vअगर->addr);
			जाओ err;
		पूर्ण

		ret = ath11k_रुको_क्रम_peer_delete_करोne(ar, arvअगर->vdev_id,
						       vअगर->addr);
		अगर (ret)
			जाओ err;

		ar->num_peers--;
	पूर्ण

err_vdev_del:
	ath11k_wmi_vdev_delete(ar, arvअगर->vdev_id);
	ar->num_created_vdevs--;
	ar->allocated_vdev_map &= ~(1LL << arvअगर->vdev_id);
	ab->मुक्त_vdev_map |= 1LL << arvअगर->vdev_id;
	spin_lock_bh(&ar->data_lock);
	list_del(&arvअगर->list);
	spin_unlock_bh(&ar->data_lock);

err:
	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_mac_vअगर_unref(पूर्णांक buf_id, व्योम *skb, व्योम *ctx)
अणु
	काष्ठा ieee80211_vअगर *vअगर = (काष्ठा ieee80211_vअगर *)ctx;
	काष्ठा ath11k_skb_cb *skb_cb = ATH11K_SKB_CB((काष्ठा sk_buff *)skb);

	अगर (skb_cb->vअगर == vअगर)
		skb_cb->vअगर = शून्य;

	वापस 0;
पूर्ण

अटल व्योम ath11k_mac_op_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
					   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ath11k_vअगर *arvअगर = ath11k_vअगर_to_arvअगर(vअगर);
	काष्ठा ath11k_base *ab = ar->ab;
	अचिन्हित दीर्घ समय_left;
	पूर्णांक ret;
	पूर्णांक i;

	cancel_delayed_work_sync(&arvअगर->connection_loss_work);

	mutex_lock(&ar->conf_mutex);

	ath11k_dbg(ab, ATH11K_DBG_MAC, "mac remove interface (vdev %d)\n",
		   arvअगर->vdev_id);

	अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_AP) अणु
		ret = ath11k_peer_delete(ar, arvअगर->vdev_id, vअगर->addr);
		अगर (ret)
			ath11k_warn(ab, "failed to submit AP self-peer removal on vdev %d: %d\n",
				    arvअगर->vdev_id, ret);
	पूर्ण

	reinit_completion(&ar->vdev_delete_करोne);

	ret = ath11k_wmi_vdev_delete(ar, arvअगर->vdev_id);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to delete WMI vdev %d: %d\n",
			    arvअगर->vdev_id, ret);
		जाओ err_vdev_del;
	पूर्ण

	समय_left = रुको_क्रम_completion_समयout(&ar->vdev_delete_करोne,
						ATH11K_VDEV_DELETE_TIMEOUT_HZ);
	अगर (समय_left == 0) अणु
		ath11k_warn(ab, "Timeout in receiving vdev delete response\n");
		जाओ err_vdev_del;
	पूर्ण

	ab->मुक्त_vdev_map |= 1LL << (arvअगर->vdev_id);
	ar->allocated_vdev_map &= ~(1LL << arvअगर->vdev_id);
	ar->num_created_vdevs--;

	ath11k_dbg(ab, ATH11K_DBG_MAC, "vdev %pM deleted, vdev_id %d\n",
		   vअगर->addr, arvअगर->vdev_id);

err_vdev_del:
	spin_lock_bh(&ar->data_lock);
	list_del(&arvअगर->list);
	spin_unlock_bh(&ar->data_lock);

	ath11k_peer_cleanup(ar, arvअगर->vdev_id);

	idr_क्रम_each(&ar->txmgmt_idr,
		     ath11k_mac_vअगर_txmgmt_idr_हटाओ, vअगर);

	क्रम (i = 0; i < DP_TCL_NUM_RING_MAX; i++) अणु
		spin_lock_bh(&ab->dp.tx_ring[i].tx_idr_lock);
		idr_क्रम_each(&ab->dp.tx_ring[i].txbuf_idr,
			     ath11k_mac_vअगर_unref, vअगर);
		spin_unlock_bh(&ab->dp.tx_ring[i].tx_idr_lock);
	पूर्ण

	/* Recalc txघातer क्रम reमुख्यing vdev */
	ath11k_mac_txघातer_recalc(ar);
	clear_bit(ATH11K_FLAG_MONITOR_ENABLED, &ar->monitor_flags);

	/* TODO: recal traffic छोड़ो state based on the available vdevs */

	mutex_unlock(&ar->conf_mutex);
पूर्ण

/* FIXME: Has to be verअगरied. */
#घोषणा SUPPORTED_FILTERS			\
	(FIF_ALLMULTI |				\
	FIF_CONTROL |				\
	FIF_PSPOLL |				\
	FIF_OTHER_BSS |				\
	FIF_BCN_PRBRESP_PROMISC |		\
	FIF_PROBE_REQ |				\
	FIF_FCSFAIL)

अटल व्योम ath11k_mac_op_configure_filter(काष्ठा ieee80211_hw *hw,
					   अचिन्हित पूर्णांक changed_flags,
					   अचिन्हित पूर्णांक *total_flags,
					   u64 multicast)
अणु
	काष्ठा ath11k *ar = hw->priv;
	bool reset_flag = false;
	पूर्णांक ret = 0;

	mutex_lock(&ar->conf_mutex);

	changed_flags &= SUPPORTED_FILTERS;
	*total_flags &= SUPPORTED_FILTERS;
	ar->filter_flags = *total_flags;

	/* For monitor mode */
	reset_flag = !(ar->filter_flags & FIF_BCN_PRBRESP_PROMISC);

	ret = ath11k_dp_tx_htt_monitor_mode_ring_config(ar, reset_flag);
	अगर (!ret) अणु
		अगर (!reset_flag)
			set_bit(ATH11K_FLAG_MONITOR_ENABLED, &ar->monitor_flags);
		अन्यथा
			clear_bit(ATH11K_FLAG_MONITOR_ENABLED, &ar->monitor_flags);
	पूर्ण अन्यथा अणु
		ath11k_warn(ar->ab,
			    "fail to set monitor filter: %d\n", ret);
	पूर्ण
	ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
		   "changed_flags:0x%x, total_flags:0x%x, reset_flag:%d\n",
		   changed_flags, *total_flags, reset_flag);

	mutex_unlock(&ar->conf_mutex);
पूर्ण

अटल पूर्णांक ath11k_mac_op_get_antenna(काष्ठा ieee80211_hw *hw, u32 *tx_ant, u32 *rx_ant)
अणु
	काष्ठा ath11k *ar = hw->priv;

	mutex_lock(&ar->conf_mutex);

	*tx_ant = ar->cfg_tx_chainmask;
	*rx_ant = ar->cfg_rx_chainmask;

	mutex_unlock(&ar->conf_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_mac_op_set_antenna(काष्ठा ieee80211_hw *hw, u32 tx_ant, u32 rx_ant)
अणु
	काष्ठा ath11k *ar = hw->priv;
	पूर्णांक ret;

	mutex_lock(&ar->conf_mutex);
	ret = __ath11k_set_antenna(ar, tx_ant, rx_ant);
	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_mac_op_ampdu_action(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा ieee80211_ampdu_params *params)
अणु
	काष्ठा ath11k *ar = hw->priv;
	पूर्णांक ret = -EINVAL;

	mutex_lock(&ar->conf_mutex);

	चयन (params->action) अणु
	हाल IEEE80211_AMPDU_RX_START:
		ret = ath11k_dp_rx_ampdu_start(ar, params);
		अवरोध;
	हाल IEEE80211_AMPDU_RX_STOP:
		ret = ath11k_dp_rx_ampdu_stop(ar, params);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_START:
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		/* Tx A-MPDU aggregation offloaded to hw/fw so deny mac80211
		 * Tx aggregation requests.
		 */
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_mac_op_add_chanctx(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ath11k_base *ab = ar->ab;

	ath11k_dbg(ab, ATH11K_DBG_MAC,
		   "mac chanctx add freq %u width %d ptr %pK\n",
		   ctx->def.chan->center_freq, ctx->def.width, ctx);

	mutex_lock(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);
	/* TODO: In हाल of multiple channel context, populate rx_channel from
	 * Rx PPDU desc inक्रमmation.
	 */
	ar->rx_channel = ctx->def.chan;
	spin_unlock_bh(&ar->data_lock);

	mutex_unlock(&ar->conf_mutex);

	वापस 0;
पूर्ण

अटल व्योम ath11k_mac_op_हटाओ_chanctx(काष्ठा ieee80211_hw *hw,
					 काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ath11k_base *ab = ar->ab;

	ath11k_dbg(ab, ATH11K_DBG_MAC,
		   "mac chanctx remove freq %u width %d ptr %pK\n",
		   ctx->def.chan->center_freq, ctx->def.width, ctx);

	mutex_lock(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);
	/* TODO: In हाल of there is one more channel context left, populate
	 * rx_channel with the channel of that reमुख्यing channel context.
	 */
	ar->rx_channel = शून्य;
	spin_unlock_bh(&ar->data_lock);

	mutex_unlock(&ar->conf_mutex);
पूर्ण

अटल अंतरभूत पूर्णांक ath11k_mac_vdev_setup_sync(काष्ठा ath11k *ar)
अणु
	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (test_bit(ATH11K_FLAG_CRASH_FLUSH, &ar->ab->dev_flags))
		वापस -ESHUTDOWN;

	अगर (!रुको_क्रम_completion_समयout(&ar->vdev_setup_करोne,
					 ATH11K_VDEV_SETUP_TIMEOUT_HZ))
		वापस -ETIMEDOUT;

	वापस ar->last_wmi_vdev_start_status ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक
ath11k_mac_vdev_start_restart(काष्ठा ath11k_vअगर *arvअगर,
			      स्थिर काष्ठा cfg80211_chan_def *chandef,
			      bool restart)
अणु
	काष्ठा ath11k *ar = arvअगर->ar;
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा wmi_vdev_start_req_arg arg = अणुपूर्ण;
	पूर्णांक he_support = arvअगर->vअगर->bss_conf.he_support;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&ar->conf_mutex);

	reinit_completion(&ar->vdev_setup_करोne);

	arg.vdev_id = arvअगर->vdev_id;
	arg.dtim_period = arvअगर->dtim_period;
	arg.bcn_पूर्णांकval = arvअगर->beacon_पूर्णांकerval;

	arg.channel.freq = chandef->chan->center_freq;
	arg.channel.band_center_freq1 = chandef->center_freq1;
	arg.channel.band_center_freq2 = chandef->center_freq2;
	arg.channel.mode =
		ath11k_phymodes[chandef->chan->band][chandef->width];

	arg.channel.min_घातer = 0;
	arg.channel.max_घातer = chandef->chan->max_घातer * 2;
	arg.channel.max_reg_घातer = chandef->chan->max_reg_घातer * 2;
	arg.channel.max_antenna_gain = chandef->chan->max_antenna_gain * 2;

	arg.pref_tx_streams = ar->num_tx_chains;
	arg.pref_rx_streams = ar->num_rx_chains;

	अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_AP) अणु
		arg.ssid = arvअगर->u.ap.ssid;
		arg.ssid_len = arvअगर->u.ap.ssid_len;
		arg.hidden_ssid = arvअगर->u.ap.hidden_ssid;

		/* For now allow DFS क्रम AP mode */
		arg.channel.chan_radar =
			!!(chandef->chan->flags & IEEE80211_CHAN_RADAR);

		arg.channel.freq2_radar =
			!!(chandef->chan->flags & IEEE80211_CHAN_RADAR);

		arg.channel.passive = arg.channel.chan_radar;

		spin_lock_bh(&ab->base_lock);
		arg.regकरोमुख्य = ar->ab->dfs_region;
		spin_unlock_bh(&ab->base_lock);

		अगर (he_support) अणु
			ret = ath11k_set_he_mu_sounding_mode(ar, arvअगर);
			अगर (ret) अणु
				ath11k_warn(ar->ab, "failed to set he mode vdev %i\n",
					    arg.vdev_id);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	arg.channel.passive |= !!(chandef->chan->flags & IEEE80211_CHAN_NO_IR);

	ath11k_dbg(ab, ATH11K_DBG_MAC,
		   "mac vdev %d start center_freq %d phymode %s\n",
		   arg.vdev_id, arg.channel.freq,
		   ath11k_wmi_phymode_str(arg.channel.mode));

	ret = ath11k_wmi_vdev_start(ar, &arg, restart);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to %s WMI vdev %i\n",
			    restart ? "restart" : "start", arg.vdev_id);
		वापस ret;
	पूर्ण

	ret = ath11k_mac_vdev_setup_sync(ar);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to synchronize setup for vdev %i %s: %d\n",
			    arg.vdev_id, restart ? "restart" : "start", ret);
		वापस ret;
	पूर्ण

	ar->num_started_vdevs++;
	ath11k_dbg(ab, ATH11K_DBG_MAC,  "vdev %pM started, vdev_id %d\n",
		   arvअगर->vअगर->addr, arvअगर->vdev_id);

	/* Enable CAC Flag in the driver by checking the channel DFS cac समय,
	 * i.e dfs_cac_ms value which will be valid only क्रम radar channels
	 * and state as NL80211_DFS_USABLE which indicates CAC needs to be
	 * करोne beक्रमe channel usage. This flags is used to drop rx packets.
	 * during CAC.
	 */
	/* TODO Set the flag क्रम other पूर्णांकerface types as required */
	अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_AP &&
	    chandef->chan->dfs_cac_ms &&
	    chandef->chan->dfs_state == NL80211_DFS_USABLE) अणु
		set_bit(ATH11K_CAC_RUNNING, &ar->dev_flags);
		ath11k_dbg(ab, ATH11K_DBG_MAC,
			   "CAC Started in chan_freq %d for vdev %d\n",
			   arg.channel.freq, arg.vdev_id);
	पूर्ण

	ret = ath11k_mac_set_txbf_conf(arvअगर);
	अगर (ret)
		ath11k_warn(ab, "failed to set txbf conf for vdev %d: %d\n",
			    arvअगर->vdev_id, ret);

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_mac_vdev_stop(काष्ठा ath11k_vअगर *arvअगर)
अणु
	काष्ठा ath11k *ar = arvअगर->ar;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	reinit_completion(&ar->vdev_setup_करोne);

	ret = ath11k_wmi_vdev_stop(ar, arvअगर->vdev_id);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to stop WMI vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		जाओ err;
	पूर्ण

	ret = ath11k_mac_vdev_setup_sync(ar);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to synchronize setup for vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
		जाओ err;
	पूर्ण

	WARN_ON(ar->num_started_vdevs == 0);

	ar->num_started_vdevs--;
	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "vdev %pM stopped, vdev_id %d\n",
		   arvअगर->vअगर->addr, arvअगर->vdev_id);

	अगर (test_bit(ATH11K_CAC_RUNNING, &ar->dev_flags)) अणु
		clear_bit(ATH11K_CAC_RUNNING, &ar->dev_flags);
		ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "CAC Stopped for vdev %d\n",
			   arvअगर->vdev_id);
	पूर्ण

	वापस 0;
err:
	वापस ret;
पूर्ण

अटल पूर्णांक ath11k_mac_vdev_start(काष्ठा ath11k_vअगर *arvअगर,
				 स्थिर काष्ठा cfg80211_chan_def *chandef)
अणु
	वापस ath11k_mac_vdev_start_restart(arvअगर, chandef, false);
पूर्ण

अटल पूर्णांक ath11k_mac_vdev_restart(काष्ठा ath11k_vअगर *arvअगर,
				   स्थिर काष्ठा cfg80211_chan_def *chandef)
अणु
	वापस ath11k_mac_vdev_start_restart(arvअगर, chandef, true);
पूर्ण

काष्ठा ath11k_mac_change_chanctx_arg अणु
	काष्ठा ieee80211_chanctx_conf *ctx;
	काष्ठा ieee80211_vअगर_chanctx_चयन *vअगरs;
	पूर्णांक n_vअगरs;
	पूर्णांक next_vअगर;
पूर्ण;

अटल व्योम
ath11k_mac_change_chanctx_cnt_iter(व्योम *data, u8 *mac,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath11k_mac_change_chanctx_arg *arg = data;

	अगर (rcu_access_poपूर्णांकer(vअगर->chanctx_conf) != arg->ctx)
		वापस;

	arg->n_vअगरs++;
पूर्ण

अटल व्योम
ath11k_mac_change_chanctx_fill_iter(व्योम *data, u8 *mac,
				    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath11k_mac_change_chanctx_arg *arg = data;
	काष्ठा ieee80211_chanctx_conf *ctx;

	ctx = rcu_access_poपूर्णांकer(vअगर->chanctx_conf);
	अगर (ctx != arg->ctx)
		वापस;

	अगर (WARN_ON(arg->next_vअगर == arg->n_vअगरs))
		वापस;

	arg->vअगरs[arg->next_vअगर].vअगर = vअगर;
	arg->vअगरs[arg->next_vअगर].old_ctx = ctx;
	arg->vअगरs[arg->next_vअगर].new_ctx = ctx;
	arg->next_vअगर++;
पूर्ण

अटल व्योम
ath11k_mac_update_vअगर_chan(काष्ठा ath11k *ar,
			   काष्ठा ieee80211_vअगर_chanctx_चयन *vअगरs,
			   पूर्णांक n_vअगरs)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_vअगर *arvअगर;
	पूर्णांक ret;
	पूर्णांक i;

	lockdep_निश्चित_held(&ar->conf_mutex);

	क्रम (i = 0; i < n_vअगरs; i++) अणु
		arvअगर = (व्योम *)vअगरs[i].vअगर->drv_priv;

		ath11k_dbg(ab, ATH11K_DBG_MAC,
			   "mac chanctx switch vdev_id %i freq %u->%u width %d->%d\n",
			   arvअगर->vdev_id,
			   vअगरs[i].old_ctx->def.chan->center_freq,
			   vअगरs[i].new_ctx->def.chan->center_freq,
			   vअगरs[i].old_ctx->def.width,
			   vअगरs[i].new_ctx->def.width);

		अगर (WARN_ON(!arvअगर->is_started))
			जारी;

		अगर (WARN_ON(!arvअगर->is_up))
			जारी;

		ret = ath11k_wmi_vdev_करोwn(ar, arvअगर->vdev_id);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to down vdev %d: %d\n",
				    arvअगर->vdev_id, ret);
			जारी;
		पूर्ण
	पूर्ण

	/* All relevant vdevs are करोwned and associated channel resources
	 * should be available क्रम the channel चयन now.
	 */

	/* TODO: Update ar->rx_channel */

	क्रम (i = 0; i < n_vअगरs; i++) अणु
		arvअगर = (व्योम *)vअगरs[i].vअगर->drv_priv;

		अगर (WARN_ON(!arvअगर->is_started))
			जारी;

		अगर (WARN_ON(!arvअगर->is_up))
			जारी;

		ret = ath11k_mac_setup_bcn_पंचांगpl(arvअगर);
		अगर (ret)
			ath11k_warn(ab, "failed to update bcn tmpl during csa: %d\n",
				    ret);

		ret = ath11k_mac_vdev_restart(arvअगर, &vअगरs[i].new_ctx->def);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to restart vdev %d: %d\n",
				    arvअगर->vdev_id, ret);
			जारी;
		पूर्ण

		ret = ath11k_wmi_vdev_up(arvअगर->ar, arvअगर->vdev_id, arvअगर->aid,
					 arvअगर->bssid);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to bring vdev up %d: %d\n",
				    arvअगर->vdev_id, ret);
			जारी;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
ath11k_mac_update_active_vअगर_chan(काष्ठा ath11k *ar,
				  काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	काष्ठा ath11k_mac_change_chanctx_arg arg = अणु .ctx = ctx पूर्ण;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(ar->hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   ath11k_mac_change_chanctx_cnt_iter,
						   &arg);
	अगर (arg.n_vअगरs == 0)
		वापस;

	arg.vअगरs = kसुस्मृति(arg.n_vअगरs, माप(arg.vअगरs[0]), GFP_KERNEL);
	अगर (!arg.vअगरs)
		वापस;

	ieee80211_iterate_active_पूर्णांकerfaces_atomic(ar->hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   ath11k_mac_change_chanctx_fill_iter,
						   &arg);

	ath11k_mac_update_vअगर_chan(ar, arg.vअगरs, arg.n_vअगरs);

	kमुक्त(arg.vअगरs);
पूर्ण

अटल व्योम ath11k_mac_op_change_chanctx(काष्ठा ieee80211_hw *hw,
					 काष्ठा ieee80211_chanctx_conf *ctx,
					 u32 changed)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ath11k_base *ab = ar->ab;

	mutex_lock(&ar->conf_mutex);

	ath11k_dbg(ab, ATH11K_DBG_MAC,
		   "mac chanctx change freq %u width %d ptr %pK changed %x\n",
		   ctx->def.chan->center_freq, ctx->def.width, ctx, changed);

	/* This shouldn't really happen because channel चयनing should use
	 * चयन_vअगर_chanctx().
	 */
	अगर (WARN_ON(changed & IEEE80211_CHANCTX_CHANGE_CHANNEL))
		जाओ unlock;

	अगर (changed & IEEE80211_CHANCTX_CHANGE_WIDTH)
		ath11k_mac_update_active_vअगर_chan(ar, ctx);

	/* TODO: Recalc radar detection */

unlock:
	mutex_unlock(&ar->conf_mutex);
पूर्ण

अटल पूर्णांक ath11k_start_vdev_delay(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	पूर्णांक ret;

	अगर (WARN_ON(arvअगर->is_started))
		वापस -EBUSY;

	ret = ath11k_mac_vdev_start(arvअगर, &arvअगर->chanctx.def);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to start vdev %i addr %pM on freq %d: %d\n",
			    arvअगर->vdev_id, vअगर->addr,
			    arvअगर->chanctx.def.chan->center_freq, ret);
		वापस ret;
	पूर्ण

	अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_MONITOR) अणु
		ret = ath11k_monitor_vdev_up(ar, arvअगर->vdev_id);
		अगर (ret) अणु
			ath11k_warn(ab, "failed put monitor up: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	arvअगर->is_started = true;

	/* TODO: Setup ps and cts/rts protection */
	वापस 0;
पूर्ण

अटल पूर्णांक
ath11k_mac_op_assign_vअगर_chanctx(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	पूर्णांक ret;
	काष्ठा peer_create_params param;

	mutex_lock(&ar->conf_mutex);

	ath11k_dbg(ab, ATH11K_DBG_MAC,
		   "mac chanctx assign ptr %pK vdev_id %i\n",
		   ctx, arvअगर->vdev_id);

	/* क्रम QCA6390 bss peer must be created beक्रमe vdev_start */
	अगर (ab->hw_params.vdev_start_delay &&
	    arvअगर->vdev_type != WMI_VDEV_TYPE_AP &&
	    arvअगर->vdev_type != WMI_VDEV_TYPE_MONITOR &&
	    !ath11k_peer_find_by_vdev_id(ab, arvअगर->vdev_id)) अणु
		स_नकल(&arvअगर->chanctx, ctx, माप(*ctx));
		ret = 0;
		जाओ out;
	पूर्ण

	अगर (WARN_ON(arvअगर->is_started)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (ab->hw_params.vdev_start_delay &&
	    arvअगर->vdev_type != WMI_VDEV_TYPE_AP &&
	    arvअगर->vdev_type != WMI_VDEV_TYPE_MONITOR) अणु
		param.vdev_id = arvअगर->vdev_id;
		param.peer_type = WMI_PEER_TYPE_DEFAULT;
		param.peer_addr = ar->mac_addr;

		ret = ath11k_peer_create(ar, arvअगर, शून्य, &param);
		अगर (ret) अणु
			ath11k_warn(ab, "failed to create peer after vdev start delay: %d",
				    ret);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = ath11k_mac_vdev_start(arvअगर, &ctx->def);
	अगर (ret) अणु
		ath11k_warn(ab, "failed to start vdev %i addr %pM on freq %d: %d\n",
			    arvअगर->vdev_id, vअगर->addr,
			    ctx->def.chan->center_freq, ret);
		जाओ out;
	पूर्ण
	अगर (arvअगर->vdev_type == WMI_VDEV_TYPE_MONITOR) अणु
		ret = ath11k_monitor_vdev_up(ar, arvअगर->vdev_id);
		अगर (ret)
			जाओ out;
	पूर्ण

	arvअगर->is_started = true;

	/* TODO: Setup ps and cts/rts protection */

	ret = 0;

out:
	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

अटल व्योम
ath11k_mac_op_unassign_vअगर_chanctx(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा ieee80211_chanctx_conf *ctx)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	पूर्णांक ret;

	mutex_lock(&ar->conf_mutex);

	ath11k_dbg(ab, ATH11K_DBG_MAC,
		   "mac chanctx unassign ptr %pK vdev_id %i\n",
		   ctx, arvअगर->vdev_id);

	WARN_ON(!arvअगर->is_started);

	अगर (ab->hw_params.vdev_start_delay &&
	    arvअगर->vdev_type == WMI_VDEV_TYPE_MONITOR &&
	    ath11k_peer_find_by_addr(ab, ar->mac_addr))
		ath11k_peer_delete(ar, arvअगर->vdev_id, ar->mac_addr);

	ret = ath11k_mac_vdev_stop(arvअगर);
	अगर (ret)
		ath11k_warn(ab, "failed to stop vdev %i: %d\n",
			    arvअगर->vdev_id, ret);

	arvअगर->is_started = false;

	अगर (ab->hw_params.vdev_start_delay &&
	    arvअगर->vdev_type == WMI_VDEV_TYPE_MONITOR)
		ath11k_wmi_vdev_करोwn(ar, arvअगर->vdev_id);

	mutex_unlock(&ar->conf_mutex);
पूर्ण

अटल पूर्णांक
ath11k_mac_op_चयन_vअगर_chanctx(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर_chanctx_चयन *vअगरs,
				 पूर्णांक n_vअगरs,
				 क्रमागत ieee80211_chanctx_चयन_mode mode)
अणु
	काष्ठा ath11k *ar = hw->priv;

	mutex_lock(&ar->conf_mutex);

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
		   "mac chanctx switch n_vifs %d mode %d\n",
		   n_vअगरs, mode);
	ath11k_mac_update_vअगर_chan(ar, vअगरs, n_vअगरs);

	mutex_unlock(&ar->conf_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक
ath11k_set_vdev_param_to_all_vअगरs(काष्ठा ath11k *ar, पूर्णांक param, u32 value)
अणु
	काष्ठा ath11k_vअगर *arvअगर;
	पूर्णांक ret = 0;

	mutex_lock(&ar->conf_mutex);
	list_क्रम_each_entry(arvअगर, &ar->arvअगरs, list) अणु
		ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "setting mac vdev %d param %d value %d\n",
			   param, arvअगर->vdev_id, value);

		ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
						    param, value);
		अगर (ret) अणु
			ath11k_warn(ar->ab, "failed to set param %d for vdev %d: %d\n",
				    param, arvअगर->vdev_id, ret);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

/* mac80211 stores device specअगरic RTS/Fragmentation threshold value,
 * this is set पूर्णांकerface specअगरic to firmware from ath11k driver
 */
अटल पूर्णांक ath11k_mac_op_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 value)
अणु
	काष्ठा ath11k *ar = hw->priv;
	पूर्णांक param_id = WMI_VDEV_PARAM_RTS_THRESHOLD;

	वापस ath11k_set_vdev_param_to_all_vअगरs(ar, param_id, value);
पूर्ण

अटल पूर्णांक ath11k_mac_op_set_frag_threshold(काष्ठा ieee80211_hw *hw, u32 value)
अणु
	/* Even though there's a WMI vdev param क्रम fragmentation threshold no
	 * known firmware actually implements it. Moreover it is not possible to
	 * rely frame fragmentation to mac80211 because firmware clears the
	 * "more fragments" bit in frame control making it impossible क्रम remote
	 * devices to reassemble frames.
	 *
	 * Hence implement a dummy callback just to say fragmentation isn't
	 * supported. This effectively prevents mac80211 from करोing frame
	 * fragmentation in software.
	 */
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम ath11k_mac_op_flush(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
				u32 queues, bool drop)
अणु
	काष्ठा ath11k *ar = hw->priv;
	दीर्घ समय_left;

	अगर (drop)
		वापस;

	समय_left = रुको_event_समयout(ar->dp.tx_empty_रुकोq,
				       (atomic_पढ़ो(&ar->dp.num_tx_pending) == 0),
				       ATH11K_FLUSH_TIMEOUT);
	अगर (समय_left == 0)
		ath11k_warn(ar->ab, "failed to flush transmit queue %ld\n", समय_left);
पूर्ण

अटल पूर्णांक
ath11k_mac_bitrate_mask_num_ht_rates(काष्ठा ath11k *ar,
				     क्रमागत nl80211_band band,
				     स्थिर काष्ठा cfg80211_bitrate_mask *mask)
अणु
	पूर्णांक num_rates = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mask->control[band].ht_mcs); i++)
		num_rates += hweight16(mask->control[band].ht_mcs[i]);

	वापस num_rates;
पूर्ण

अटल bool
ath11k_mac_has_single_legacy_rate(काष्ठा ath11k *ar,
				  क्रमागत nl80211_band band,
				  स्थिर काष्ठा cfg80211_bitrate_mask *mask)
अणु
	पूर्णांक num_rates = 0;

	num_rates = hweight32(mask->control[band].legacy);

	अगर (ath11k_mac_bitrate_mask_num_ht_rates(ar, band, mask))
		वापस false;

	अगर (ath11k_mac_bitrate_mask_num_vht_rates(ar, band, mask))
		वापस false;

	वापस num_rates == 1;
पूर्ण

अटल bool
ath11k_mac_bitrate_mask_get_single_nss(काष्ठा ath11k *ar,
				       क्रमागत nl80211_band band,
				       स्थिर काष्ठा cfg80211_bitrate_mask *mask,
				       पूर्णांक *nss)
अणु
	काष्ठा ieee80211_supported_band *sband = &ar->mac.sbands[band];
	u16 vht_mcs_map = le16_to_cpu(sband->vht_cap.vht_mcs.tx_mcs_map);
	u8 ht_nss_mask = 0;
	u8 vht_nss_mask = 0;
	पूर्णांक i;

	/* No need to consider legacy here. Basic rates are always present
	 * in bitrate mask
	 */

	क्रम (i = 0; i < ARRAY_SIZE(mask->control[band].ht_mcs); i++) अणु
		अगर (mask->control[band].ht_mcs[i] == 0)
			जारी;
		अन्यथा अगर (mask->control[band].ht_mcs[i] ==
			 sband->ht_cap.mcs.rx_mask[i])
			ht_nss_mask |= BIT(i);
		अन्यथा
			वापस false;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(mask->control[band].vht_mcs); i++) अणु
		अगर (mask->control[band].vht_mcs[i] == 0)
			जारी;
		अन्यथा अगर (mask->control[band].vht_mcs[i] ==
			 ath11k_mac_get_max_vht_mcs_map(vht_mcs_map, i))
			vht_nss_mask |= BIT(i);
		अन्यथा
			वापस false;
	पूर्ण

	अगर (ht_nss_mask != vht_nss_mask)
		वापस false;

	अगर (ht_nss_mask == 0)
		वापस false;

	अगर (BIT(fls(ht_nss_mask)) - 1 != ht_nss_mask)
		वापस false;

	*nss = fls(ht_nss_mask);

	वापस true;
पूर्ण

अटल पूर्णांक
ath11k_mac_get_single_legacy_rate(काष्ठा ath11k *ar,
				  क्रमागत nl80211_band band,
				  स्थिर काष्ठा cfg80211_bitrate_mask *mask,
				  u32 *rate, u8 *nss)
अणु
	पूर्णांक rate_idx;
	u16 bitrate;
	u8 preamble;
	u8 hw_rate;

	अगर (hweight32(mask->control[band].legacy) != 1)
		वापस -EINVAL;

	rate_idx = ffs(mask->control[band].legacy) - 1;

	अगर (band == NL80211_BAND_5GHZ || band == NL80211_BAND_6GHZ)
		rate_idx += ATH11K_MAC_FIRST_OFDM_RATE_IDX;

	hw_rate = ath11k_legacy_rates[rate_idx].hw_value;
	bitrate = ath11k_legacy_rates[rate_idx].bitrate;

	अगर (ath11k_mac_bitrate_is_cck(bitrate))
		preamble = WMI_RATE_PREAMBLE_CCK;
	अन्यथा
		preamble = WMI_RATE_PREAMBLE_OFDM;

	*nss = 1;
	*rate = ATH11K_HW_RATE_CODE(hw_rate, 0, preamble);

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_mac_set_fixed_rate_params(काष्ठा ath11k_vअगर *arvअगर,
					    u32 rate, u8 nss, u8 sgi, u8 ldpc)
अणु
	काष्ठा ath11k *ar = arvअगर->ar;
	u32 vdev_param;
	पूर्णांक ret;

	lockdep_निश्चित_held(&ar->conf_mutex);

	ath11k_dbg(ar->ab, ATH11K_DBG_MAC, "mac set fixed rate params vdev %i rate 0x%02x nss %u sgi %u\n",
		   arvअगर->vdev_id, rate, nss, sgi);

	vdev_param = WMI_VDEV_PARAM_FIXED_RATE;
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
					    vdev_param, rate);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to set fixed rate param 0x%02x: %d\n",
			    rate, ret);
		वापस ret;
	पूर्ण

	vdev_param = WMI_VDEV_PARAM_NSS;
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
					    vdev_param, nss);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to set nss param %d: %d\n",
			    nss, ret);
		वापस ret;
	पूर्ण

	vdev_param = WMI_VDEV_PARAM_SGI;
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
					    vdev_param, sgi);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to set sgi param %d: %d\n",
			    sgi, ret);
		वापस ret;
	पूर्ण

	vdev_param = WMI_VDEV_PARAM_LDPC;
	ret = ath11k_wmi_vdev_set_param_cmd(ar, arvअगर->vdev_id,
					    vdev_param, ldpc);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to set ldpc param %d: %d\n",
			    ldpc, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool
ath11k_mac_vht_mcs_range_present(काष्ठा ath11k *ar,
				 क्रमागत nl80211_band band,
				 स्थिर काष्ठा cfg80211_bitrate_mask *mask)
अणु
	पूर्णांक i;
	u16 vht_mcs;

	क्रम (i = 0; i < NL80211_VHT_NSS_MAX; i++) अणु
		vht_mcs = mask->control[band].vht_mcs[i];

		चयन (vht_mcs) अणु
		हाल 0:
		हाल BIT(8) - 1:
		हाल BIT(9) - 1:
		हाल BIT(10) - 1:
			अवरोध;
		शेष:
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम ath11k_mac_set_bitrate_mask_iter(व्योम *data,
					     काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath11k_vअगर *arvअगर = data;
	काष्ठा ath11k_sta *arsta = (काष्ठा ath11k_sta *)sta->drv_priv;
	काष्ठा ath11k *ar = arvअगर->ar;

	spin_lock_bh(&ar->data_lock);
	arsta->changed |= IEEE80211_RC_SUPP_RATES_CHANGED;
	spin_unlock_bh(&ar->data_lock);

	ieee80211_queue_work(ar->hw, &arsta->update_wk);
पूर्ण

अटल व्योम ath11k_mac_disable_peer_fixed_rate(व्योम *data,
					       काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath11k_vअगर *arvअगर = data;
	काष्ठा ath11k *ar = arvअगर->ar;
	पूर्णांक ret;

	ret = ath11k_wmi_set_peer_param(ar, sta->addr,
					arvअगर->vdev_id,
					WMI_PEER_PARAM_FIXED_RATE,
					WMI_FIXED_RATE_NONE);
	अगर (ret)
		ath11k_warn(ar->ab,
			    "failed to disable peer fixed rate for STA %pM ret %d\n",
			    sta->addr, ret);
पूर्ण

अटल पूर्णांक
ath11k_mac_op_set_bitrate_mask(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर,
			       स्थिर काष्ठा cfg80211_bitrate_mask *mask)
अणु
	काष्ठा ath11k_vअगर *arvअगर = (व्योम *)vअगर->drv_priv;
	काष्ठा cfg80211_chan_def def;
	काष्ठा ath11k *ar = arvअगर->ar;
	क्रमागत nl80211_band band;
	स्थिर u8 *ht_mcs_mask;
	स्थिर u16 *vht_mcs_mask;
	u32 rate;
	u8 nss;
	u8 sgi;
	u8 ldpc;
	पूर्णांक single_nss;
	पूर्णांक ret;
	पूर्णांक num_rates;

	अगर (ath11k_mac_vअगर_chan(vअगर, &def))
		वापस -EPERM;

	band = def.chan->band;
	ht_mcs_mask = mask->control[band].ht_mcs;
	vht_mcs_mask = mask->control[band].vht_mcs;
	ldpc = !!(ar->ht_cap_info & WMI_HT_CAP_LDPC);

	sgi = mask->control[band].gi;
	अगर (sgi == NL80211_TXRATE_FORCE_LGI)
		वापस -EINVAL;

	/* mac80211 करोesn't support sending a fixed HT/VHT MCS alone, rather it
	 * requires passing atleast one of used basic rates aदीर्घ with them.
	 * Fixed rate setting across dअगरferent preambles(legacy, HT, VHT) is
	 * not supported by the FW. Hence use of FIXED_RATE vdev param is not
	 * suitable क्रम setting single HT/VHT rates.
	 * But, there could be a single basic rate passed from userspace which
	 * can be करोne through the FIXED_RATE param.
	 */
	अगर (ath11k_mac_has_single_legacy_rate(ar, band, mask)) अणु
		ret = ath11k_mac_get_single_legacy_rate(ar, band, mask, &rate,
							&nss);
		अगर (ret) अणु
			ath11k_warn(ar->ab, "failed to get single legacy rate for vdev %i: %d\n",
				    arvअगर->vdev_id, ret);
			वापस ret;
		पूर्ण
		ieee80211_iterate_stations_atomic(ar->hw,
						  ath11k_mac_disable_peer_fixed_rate,
						  arvअगर);
	पूर्ण अन्यथा अगर (ath11k_mac_bitrate_mask_get_single_nss(ar, band, mask,
							  &single_nss)) अणु
		rate = WMI_FIXED_RATE_NONE;
		nss = single_nss;
	पूर्ण अन्यथा अणु
		rate = WMI_FIXED_RATE_NONE;
		nss = min_t(u32, ar->num_tx_chains,
			    max(ath11k_mac_max_ht_nss(ht_mcs_mask),
				ath11k_mac_max_vht_nss(vht_mcs_mask)));

		/* If multiple rates across dअगरferent preambles are given
		 * we can reconfigure this info with all peers using PEER_ASSOC
		 * command with the below exception हालs.
		 * - Single VHT Rate : peer_assoc command accommodates only MCS
		 * range values i.e 0-7, 0-8, 0-9 क्रम VHT. Though mac80211
		 * mandates passing basic rates aदीर्घ with HT/VHT rates, FW
		 * करोesn't allow चयनing from VHT to Legacy. Hence instead of
		 * setting legacy and VHT rates using RATEMASK_CMD vdev cmd,
		 * we could set this VHT rate as peer fixed rate param, which
		 * will override FIXED rate and FW rate control algorithm.
		 * If single VHT rate is passed aदीर्घ with HT rates, we select
		 * the VHT rate as fixed rate क्रम vht peers.
		 * - Multiple VHT Rates : When Multiple VHT rates are given,this
		 * can be set using RATEMASK CMD which uses FW rate-ctl alg.
		 * TODO: Setting multiple VHT MCS and replacing peer_assoc with
		 * RATEMASK_CMDID can cover all use हालs of setting rates
		 * across multiple preambles and rates within same type.
		 * But requires more validation of the command at this poपूर्णांक.
		 */

		num_rates = ath11k_mac_bitrate_mask_num_vht_rates(ar, band,
								  mask);

		अगर (!ath11k_mac_vht_mcs_range_present(ar, band, mask) &&
		    num_rates > 1) अणु
			/* TODO: Handle multiple VHT MCS values setting using
			 * RATEMASK CMD
			 */
			ath11k_warn(ar->ab,
				    "Setting more than one MCS Value in bitrate mask not supported\n");
			वापस -EINVAL;
		पूर्ण

		ieee80211_iterate_stations_atomic(ar->hw,
						  ath11k_mac_disable_peer_fixed_rate,
						  arvअगर);

		mutex_lock(&ar->conf_mutex);

		arvअगर->bitrate_mask = *mask;
		ieee80211_iterate_stations_atomic(ar->hw,
						  ath11k_mac_set_bitrate_mask_iter,
						  arvअगर);

		mutex_unlock(&ar->conf_mutex);
	पूर्ण

	mutex_lock(&ar->conf_mutex);

	ret = ath11k_mac_set_fixed_rate_params(arvअगर, rate, nss, sgi, ldpc);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to set fixed rate params on vdev %i: %d\n",
			    arvअगर->vdev_id, ret);
	पूर्ण

	mutex_unlock(&ar->conf_mutex);

	वापस ret;
पूर्ण

अटल व्योम
ath11k_mac_op_reconfig_complete(काष्ठा ieee80211_hw *hw,
				क्रमागत ieee80211_reconfig_type reconfig_type)
अणु
	काष्ठा ath11k *ar = hw->priv;

	अगर (reconfig_type != IEEE80211_RECONFIG_TYPE_RESTART)
		वापस;

	mutex_lock(&ar->conf_mutex);

	अगर (ar->state == ATH11K_STATE_RESTARTED) अणु
		ath11k_warn(ar->ab, "pdev %d successfully recovered\n",
			    ar->pdev->pdev_id);
		ar->state = ATH11K_STATE_ON;
		ieee80211_wake_queues(ar->hw);
	पूर्ण

	mutex_unlock(&ar->conf_mutex);
पूर्ण

अटल व्योम
ath11k_mac_update_bss_chan_survey(काष्ठा ath11k *ar,
				  काष्ठा ieee80211_channel *channel)
अणु
	पूर्णांक ret;
	क्रमागत wmi_bss_chan_info_req_type type = WMI_BSS_SURVEY_REQ_TYPE_READ;

	lockdep_निश्चित_held(&ar->conf_mutex);

	अगर (!test_bit(WMI_TLV_SERVICE_BSS_CHANNEL_INFO_64, ar->ab->wmi_ab.svc_map) ||
	    ar->rx_channel != channel)
		वापस;

	अगर (ar->scan.state != ATH11K_SCAN_IDLE) अणु
		ath11k_dbg(ar->ab, ATH11K_DBG_MAC,
			   "ignoring bss chan info req while scanning..\n");
		वापस;
	पूर्ण

	reinit_completion(&ar->bss_survey_करोne);

	ret = ath11k_wmi_pdev_bss_chan_info_request(ar, type);
	अगर (ret) अणु
		ath11k_warn(ar->ab, "failed to send pdev bss chan info request\n");
		वापस;
	पूर्ण

	ret = रुको_क्रम_completion_समयout(&ar->bss_survey_करोne, 3 * HZ);
	अगर (ret == 0)
		ath11k_warn(ar->ab, "bss channel survey timed out\n");
पूर्ण

अटल पूर्णांक ath11k_mac_op_get_survey(काष्ठा ieee80211_hw *hw, पूर्णांक idx,
				    काष्ठा survey_info *survey)
अणु
	काष्ठा ath11k *ar = hw->priv;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा survey_info *ar_survey;
	पूर्णांक ret = 0;

	अगर (idx >= ATH11K_NUM_CHANS)
		वापस -ENOENT;

	ar_survey = &ar->survey[idx];

	mutex_lock(&ar->conf_mutex);

	sband = hw->wiphy->bands[NL80211_BAND_2GHZ];
	अगर (sband && idx >= sband->n_channels) अणु
		idx -= sband->n_channels;
		sband = शून्य;
	पूर्ण

	अगर (!sband)
		sband = hw->wiphy->bands[NL80211_BAND_5GHZ];

	अगर (!sband || idx >= sband->n_channels) अणु
		ret = -ENOENT;
		जाओ निकास;
	पूर्ण

	ath11k_mac_update_bss_chan_survey(ar, &sband->channels[idx]);

	spin_lock_bh(&ar->data_lock);
	स_नकल(survey, ar_survey, माप(*survey));
	spin_unlock_bh(&ar->data_lock);

	survey->channel = &sband->channels[idx];

	अगर (ar->rx_channel == survey->channel)
		survey->filled |= SURVEY_INFO_IN_USE;

निकास:
	mutex_unlock(&ar->conf_mutex);
	वापस ret;
पूर्ण

अटल व्योम ath11k_mac_op_sta_statistics(काष्ठा ieee80211_hw *hw,
					 काष्ठा ieee80211_vअगर *vअगर,
					 काष्ठा ieee80211_sta *sta,
					 काष्ठा station_info *sinfo)
अणु
	काष्ठा ath11k_sta *arsta = (काष्ठा ath11k_sta *)sta->drv_priv;

	sinfo->rx_duration = arsta->rx_duration;
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_DURATION);

	sinfo->tx_duration = arsta->tx_duration;
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_DURATION);

	अगर (!arsta->txrate.legacy && !arsta->txrate.nss)
		वापस;

	अगर (arsta->txrate.legacy) अणु
		sinfo->txrate.legacy = arsta->txrate.legacy;
	पूर्ण अन्यथा अणु
		sinfo->txrate.mcs = arsta->txrate.mcs;
		sinfo->txrate.nss = arsta->txrate.nss;
		sinfo->txrate.bw = arsta->txrate.bw;
		sinfo->txrate.he_gi = arsta->txrate.he_gi;
		sinfo->txrate.he_dcm = arsta->txrate.he_dcm;
		sinfo->txrate.he_ru_alloc = arsta->txrate.he_ru_alloc;
	पूर्ण
	sinfo->txrate.flags = arsta->txrate.flags;
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);

	/* TODO: Use real NF instead of शेष one. */
	sinfo->संकेत = arsta->rssi_comb + ATH11K_DEFAULT_NOISE_FLOOR;
	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL);
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops ath11k_ops = अणु
	.tx				= ath11k_mac_op_tx,
	.start                          = ath11k_mac_op_start,
	.stop                           = ath11k_mac_op_stop,
	.reconfig_complete              = ath11k_mac_op_reconfig_complete,
	.add_पूर्णांकerface                  = ath11k_mac_op_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface		= ath11k_mac_op_हटाओ_पूर्णांकerface,
	.update_vअगर_offload		= ath11k_mac_op_update_vअगर_offload,
	.config                         = ath11k_mac_op_config,
	.bss_info_changed               = ath11k_mac_op_bss_info_changed,
	.configure_filter		= ath11k_mac_op_configure_filter,
	.hw_scan                        = ath11k_mac_op_hw_scan,
	.cancel_hw_scan                 = ath11k_mac_op_cancel_hw_scan,
	.set_key                        = ath11k_mac_op_set_key,
	.sta_state                      = ath11k_mac_op_sta_state,
	.sta_set_txpwr			= ath11k_mac_op_sta_set_txpwr,
	.sta_rc_update			= ath11k_mac_op_sta_rc_update,
	.conf_tx                        = ath11k_mac_op_conf_tx,
	.set_antenna			= ath11k_mac_op_set_antenna,
	.get_antenna			= ath11k_mac_op_get_antenna,
	.ampdu_action			= ath11k_mac_op_ampdu_action,
	.add_chanctx			= ath11k_mac_op_add_chanctx,
	.हटाओ_chanctx			= ath11k_mac_op_हटाओ_chanctx,
	.change_chanctx			= ath11k_mac_op_change_chanctx,
	.assign_vअगर_chanctx		= ath11k_mac_op_assign_vअगर_chanctx,
	.unassign_vअगर_chanctx		= ath11k_mac_op_unassign_vअगर_chanctx,
	.चयन_vअगर_chanctx		= ath11k_mac_op_चयन_vअगर_chanctx,
	.set_rts_threshold		= ath11k_mac_op_set_rts_threshold,
	.set_frag_threshold		= ath11k_mac_op_set_frag_threshold,
	.set_bitrate_mask		= ath11k_mac_op_set_bitrate_mask,
	.get_survey			= ath11k_mac_op_get_survey,
	.flush				= ath11k_mac_op_flush,
	.sta_statistics			= ath11k_mac_op_sta_statistics,
	CFG80211_TESTMODE_CMD(ath11k_पंचांग_cmd)
#अगर_घोषित CONFIG_ATH11K_DEBUGFS
	.sta_add_debugfs		= ath11k_debugfs_sta_op_add,
#पूर्ण_अगर
पूर्ण;

अटल व्योम ath11k_mac_update_ch_list(काष्ठा ath11k *ar,
				      काष्ठा ieee80211_supported_band *band,
				      u32 freq_low, u32 freq_high)
अणु
	पूर्णांक i;

	अगर (!(freq_low && freq_high))
		वापस;

	क्रम (i = 0; i < band->n_channels; i++) अणु
		अगर (band->channels[i].center_freq < freq_low ||
		    band->channels[i].center_freq > freq_high)
			band->channels[i].flags |= IEEE80211_CHAN_DISABLED;
	पूर्ण
पूर्ण

अटल u32 ath11k_get_phy_id(काष्ठा ath11k *ar, u32 band)
अणु
	काष्ठा ath11k_pdev *pdev = ar->pdev;
	काष्ठा ath11k_pdev_cap *pdev_cap = &pdev->cap;

	अगर (band == WMI_HOST_WLAN_2G_CAP)
		वापस pdev_cap->band[NL80211_BAND_2GHZ].phy_id;

	अगर (band == WMI_HOST_WLAN_5G_CAP)
		वापस pdev_cap->band[NL80211_BAND_5GHZ].phy_id;

	ath11k_warn(ar->ab, "unsupported phy cap:%d\n", band);

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_mac_setup_channels_rates(काष्ठा ath11k *ar,
					   u32 supported_bands)
अणु
	काष्ठा ieee80211_supported_band *band;
	काष्ठा ath11k_hal_reg_capabilities_ext *reg_cap;
	व्योम *channels;
	u32 phy_id;

	BUILD_BUG_ON((ARRAY_SIZE(ath11k_2ghz_channels) +
		      ARRAY_SIZE(ath11k_5ghz_channels) +
		      ARRAY_SIZE(ath11k_6ghz_channels)) !=
		     ATH11K_NUM_CHANS);

	reg_cap = &ar->ab->hal_reg_cap[ar->pdev_idx];

	अगर (supported_bands & WMI_HOST_WLAN_2G_CAP) अणु
		channels = kmemdup(ath11k_2ghz_channels,
				   माप(ath11k_2ghz_channels),
				   GFP_KERNEL);
		अगर (!channels)
			वापस -ENOMEM;

		band = &ar->mac.sbands[NL80211_BAND_2GHZ];
		band->band = NL80211_BAND_2GHZ;
		band->n_channels = ARRAY_SIZE(ath11k_2ghz_channels);
		band->channels = channels;
		band->n_bitrates = ath11k_g_rates_size;
		band->bitrates = ath11k_g_rates;
		ar->hw->wiphy->bands[NL80211_BAND_2GHZ] = band;

		अगर (ar->ab->hw_params.single_pdev_only) अणु
			phy_id = ath11k_get_phy_id(ar, WMI_HOST_WLAN_2G_CAP);
			reg_cap = &ar->ab->hal_reg_cap[phy_id];
		पूर्ण
		ath11k_mac_update_ch_list(ar, band,
					  reg_cap->low_2ghz_chan,
					  reg_cap->high_2ghz_chan);
	पूर्ण

	अगर (supported_bands & WMI_HOST_WLAN_5G_CAP) अणु
		अगर (reg_cap->high_5ghz_chan >= ATH11K_MAX_6G_FREQ) अणु
			channels = kmemdup(ath11k_6ghz_channels,
					   माप(ath11k_6ghz_channels), GFP_KERNEL);
			अगर (!channels) अणु
				kमुक्त(ar->mac.sbands[NL80211_BAND_2GHZ].channels);
				वापस -ENOMEM;
			पूर्ण

			ar->supports_6ghz = true;
			band = &ar->mac.sbands[NL80211_BAND_6GHZ];
			band->band = NL80211_BAND_6GHZ;
			band->n_channels = ARRAY_SIZE(ath11k_6ghz_channels);
			band->channels = channels;
			band->n_bitrates = ath11k_a_rates_size;
			band->bitrates = ath11k_a_rates;
			ar->hw->wiphy->bands[NL80211_BAND_6GHZ] = band;
			ath11k_mac_update_ch_list(ar, band,
						  reg_cap->low_5ghz_chan,
						  reg_cap->high_5ghz_chan);
		पूर्ण

		अगर (reg_cap->low_5ghz_chan < ATH11K_MIN_6G_FREQ) अणु
			channels = kmemdup(ath11k_5ghz_channels,
					   माप(ath11k_5ghz_channels),
					   GFP_KERNEL);
			अगर (!channels) अणु
				kमुक्त(ar->mac.sbands[NL80211_BAND_2GHZ].channels);
				kमुक्त(ar->mac.sbands[NL80211_BAND_6GHZ].channels);
				वापस -ENOMEM;
			पूर्ण

			band = &ar->mac.sbands[NL80211_BAND_5GHZ];
			band->band = NL80211_BAND_5GHZ;
			band->n_channels = ARRAY_SIZE(ath11k_5ghz_channels);
			band->channels = channels;
			band->n_bitrates = ath11k_a_rates_size;
			band->bitrates = ath11k_a_rates;
			ar->hw->wiphy->bands[NL80211_BAND_5GHZ] = band;

			अगर (ar->ab->hw_params.single_pdev_only) अणु
				phy_id = ath11k_get_phy_id(ar, WMI_HOST_WLAN_5G_CAP);
				reg_cap = &ar->ab->hal_reg_cap[phy_id];
			पूर्ण

			ath11k_mac_update_ch_list(ar, band,
						  reg_cap->low_5ghz_chan,
						  reg_cap->high_5ghz_chan);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath11k_mac_setup_अगरace_combinations(काष्ठा ath11k *ar)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ieee80211_अगरace_combination *combinations;
	काष्ठा ieee80211_अगरace_limit *limits;
	पूर्णांक n_limits;

	combinations = kzalloc(माप(*combinations), GFP_KERNEL);
	अगर (!combinations)
		वापस -ENOMEM;

	n_limits = 2;

	limits = kसुस्मृति(n_limits, माप(*limits), GFP_KERNEL);
	अगर (!limits) अणु
		kमुक्त(combinations);
		वापस -ENOMEM;
	पूर्ण

	limits[0].max = 1;
	limits[0].types |= BIT(NL80211_IFTYPE_STATION);

	limits[1].max = 16;
	limits[1].types |= BIT(NL80211_IFTYPE_AP);

	अगर (IS_ENABLED(CONFIG_MAC80211_MESH) &&
	    ab->hw_params.पूर्णांकerface_modes & BIT(NL80211_IFTYPE_MESH_POINT))
		limits[1].types |= BIT(NL80211_IFTYPE_MESH_POINT);

	combinations[0].limits = limits;
	combinations[0].n_limits = n_limits;
	combinations[0].max_पूर्णांकerfaces = 16;
	combinations[0].num_dअगरferent_channels = 1;
	combinations[0].beacon_पूर्णांक_infra_match = true;
	combinations[0].beacon_पूर्णांक_min_gcd = 100;
	combinations[0].radar_detect_widths = BIT(NL80211_CHAN_WIDTH_20_NOHT) |
						BIT(NL80211_CHAN_WIDTH_20) |
						BIT(NL80211_CHAN_WIDTH_40) |
						BIT(NL80211_CHAN_WIDTH_80);

	ar->hw->wiphy->अगरace_combinations = combinations;
	ar->hw->wiphy->n_अगरace_combinations = 1;

	वापस 0;
पूर्ण

अटल स्थिर u8 ath11k_अगर_types_ext_capa[] = अणु
	[0] = WLAN_EXT_CAPA1_EXT_CHANNEL_SWITCHING,
	[7] = WLAN_EXT_CAPA8_OPMODE_NOTIF,
पूर्ण;

अटल स्थिर u8 ath11k_अगर_types_ext_capa_sta[] = अणु
	[0] = WLAN_EXT_CAPA1_EXT_CHANNEL_SWITCHING,
	[7] = WLAN_EXT_CAPA8_OPMODE_NOTIF,
	[9] = WLAN_EXT_CAPA10_TWT_REQUESTER_SUPPORT,
पूर्ण;

अटल स्थिर u8 ath11k_अगर_types_ext_capa_ap[] = अणु
	[0] = WLAN_EXT_CAPA1_EXT_CHANNEL_SWITCHING,
	[7] = WLAN_EXT_CAPA8_OPMODE_NOTIF,
	[9] = WLAN_EXT_CAPA10_TWT_RESPONDER_SUPPORT,
पूर्ण;

अटल स्थिर काष्ठा wiphy_अगरtype_ext_capab ath11k_अगरtypes_ext_capa[] = अणु
	अणु
		.extended_capabilities = ath11k_अगर_types_ext_capa,
		.extended_capabilities_mask = ath11k_अगर_types_ext_capa,
		.extended_capabilities_len = माप(ath11k_अगर_types_ext_capa),
	पूर्ण, अणु
		.अगरtype = NL80211_IFTYPE_STATION,
		.extended_capabilities = ath11k_अगर_types_ext_capa_sta,
		.extended_capabilities_mask = ath11k_अगर_types_ext_capa_sta,
		.extended_capabilities_len =
				माप(ath11k_अगर_types_ext_capa_sta),
	पूर्ण, अणु
		.अगरtype = NL80211_IFTYPE_AP,
		.extended_capabilities = ath11k_अगर_types_ext_capa_ap,
		.extended_capabilities_mask = ath11k_अगर_types_ext_capa_ap,
		.extended_capabilities_len =
				माप(ath11k_अगर_types_ext_capa_ap),
	पूर्ण,
पूर्ण;

अटल व्योम __ath11k_mac_unरेजिस्टर(काष्ठा ath11k *ar)
अणु
	cancel_work_sync(&ar->regd_update_work);

	ieee80211_unरेजिस्टर_hw(ar->hw);

	idr_क्रम_each(&ar->txmgmt_idr, ath11k_mac_tx_mgmt_pending_मुक्त, ar);
	idr_destroy(&ar->txmgmt_idr);

	kमुक्त(ar->mac.sbands[NL80211_BAND_2GHZ].channels);
	kमुक्त(ar->mac.sbands[NL80211_BAND_5GHZ].channels);
	kमुक्त(ar->mac.sbands[NL80211_BAND_6GHZ].channels);

	kमुक्त(ar->hw->wiphy->अगरace_combinations[0].limits);
	kमुक्त(ar->hw->wiphy->अगरace_combinations);

	SET_IEEE80211_DEV(ar->hw, शून्य);
पूर्ण

व्योम ath11k_mac_unरेजिस्टर(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k *ar;
	काष्ठा ath11k_pdev *pdev;
	पूर्णांक i;

	क्रम (i = 0; i < ab->num_radios; i++) अणु
		pdev = &ab->pdevs[i];
		ar = pdev->ar;
		अगर (!ar)
			जारी;

		__ath11k_mac_unरेजिस्टर(ar);
	पूर्ण
पूर्ण

अटल पूर्णांक __ath11k_mac_रेजिस्टर(काष्ठा ath11k *ar)
अणु
	काष्ठा ath11k_base *ab = ar->ab;
	काष्ठा ath11k_pdev_cap *cap = &ar->pdev->cap;
	अटल स्थिर u32 cipher_suites[] = अणु
		WLAN_CIPHER_SUITE_TKIP,
		WLAN_CIPHER_SUITE_CCMP,
		WLAN_CIPHER_SUITE_AES_CMAC,
		WLAN_CIPHER_SUITE_BIP_CMAC_256,
		WLAN_CIPHER_SUITE_BIP_GMAC_128,
		WLAN_CIPHER_SUITE_BIP_GMAC_256,
		WLAN_CIPHER_SUITE_GCMP,
		WLAN_CIPHER_SUITE_GCMP_256,
		WLAN_CIPHER_SUITE_CCMP_256,
	पूर्ण;
	पूर्णांक ret;
	u32 ht_cap = 0;

	ath11k_pdev_caps_update(ar);

	SET_IEEE80211_PERM_ADDR(ar->hw, ar->mac_addr);

	SET_IEEE80211_DEV(ar->hw, ab->dev);

	ret = ath11k_mac_setup_channels_rates(ar,
					      cap->supported_bands);
	अगर (ret)
		जाओ err;

	ath11k_mac_setup_ht_vht_cap(ar, cap, &ht_cap);
	ath11k_mac_setup_he_cap(ar, cap);

	ret = ath11k_mac_setup_अगरace_combinations(ar);
	अगर (ret) अणु
		ath11k_err(ar->ab, "failed to setup interface combinations: %d\n", ret);
		जाओ err_मुक्त_channels;
	पूर्ण

	ar->hw->wiphy->available_antennas_rx = cap->rx_chain_mask;
	ar->hw->wiphy->available_antennas_tx = cap->tx_chain_mask;

	ar->hw->wiphy->पूर्णांकerface_modes = ab->hw_params.पूर्णांकerface_modes;

	ieee80211_hw_set(ar->hw, SIGNAL_DBM);
	ieee80211_hw_set(ar->hw, SUPPORTS_PS);
	ieee80211_hw_set(ar->hw, SUPPORTS_DYNAMIC_PS);
	ieee80211_hw_set(ar->hw, MFP_CAPABLE);
	ieee80211_hw_set(ar->hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(ar->hw, HAS_RATE_CONTROL);
	ieee80211_hw_set(ar->hw, AP_LINK_PS);
	ieee80211_hw_set(ar->hw, SPECTRUM_MGMT);
	ieee80211_hw_set(ar->hw, CONNECTION_MONITOR);
	ieee80211_hw_set(ar->hw, SUPPORTS_PER_STA_GTK);
	ieee80211_hw_set(ar->hw, WANT_MONITOR_VIF);
	ieee80211_hw_set(ar->hw, CHANCTX_STA_CSA);
	ieee80211_hw_set(ar->hw, QUEUE_CONTROL);
	ieee80211_hw_set(ar->hw, SUPPORTS_TX_FRAG);
	ieee80211_hw_set(ar->hw, REPORTS_LOW_ACK);
	ieee80211_hw_set(ar->hw, SUPPORTS_TX_ENCAP_OFFLOAD);
	अगर (ht_cap & WMI_HT_CAP_ENABLED) अणु
		ieee80211_hw_set(ar->hw, AMPDU_AGGREGATION);
		ieee80211_hw_set(ar->hw, TX_AMPDU_SETUP_IN_HW);
		ieee80211_hw_set(ar->hw, SUPPORTS_REORDERING_BUFFER);
		ieee80211_hw_set(ar->hw, SUPPORTS_AMSDU_IN_AMPDU);
		ieee80211_hw_set(ar->hw, USES_RSS);
	पूर्ण

	ar->hw->wiphy->features |= NL80211_FEATURE_STATIC_SMPS;
	ar->hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN;

	/* TODO: Check अगर HT capability advertised from firmware is dअगरferent
	 * क्रम each band क्रम a dual band capable radio. It will be tricky to
	 * handle it when the ht capability dअगरferent क्रम each band.
	 */
	अगर (ht_cap & WMI_HT_CAP_DYNAMIC_SMPS)
		ar->hw->wiphy->features |= NL80211_FEATURE_DYNAMIC_SMPS;

	ar->hw->wiphy->max_scan_ssids = WLAN_SCAN_PARAMS_MAX_SSID;
	ar->hw->wiphy->max_scan_ie_len = WLAN_SCAN_PARAMS_MAX_IE_LEN;

	ar->hw->max_listen_पूर्णांकerval = ATH11K_MAX_HW_LISTEN_INTERVAL;

	ar->hw->wiphy->flags |= WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL;
	ar->hw->wiphy->flags |= WIPHY_FLAG_HAS_CHANNEL_SWITCH;
	ar->hw->wiphy->max_reमुख्य_on_channel_duration = 5000;

	ar->hw->wiphy->flags |= WIPHY_FLAG_AP_UAPSD;
	ar->hw->wiphy->features |= NL80211_FEATURE_AP_MODE_CHAN_WIDTH_CHANGE |
				   NL80211_FEATURE_AP_SCAN;

	ar->max_num_stations = TARGET_NUM_STATIONS;
	ar->max_num_peers = TARGET_NUM_PEERS_PDEV;

	ar->hw->wiphy->max_ap_assoc_sta = ar->max_num_stations;

	ar->hw->queues = ATH11K_HW_MAX_QUEUES;
	ar->hw->wiphy->tx_queue_len = ATH11K_QUEUE_LEN;
	ar->hw->offchannel_tx_hw_queue = ATH11K_HW_MAX_QUEUES - 1;
	ar->hw->max_rx_aggregation_subframes = IEEE80211_MAX_AMPDU_BUF;

	ar->hw->vअगर_data_size = माप(काष्ठा ath11k_vअगर);
	ar->hw->sta_data_size = माप(काष्ठा ath11k_sta);

	wiphy_ext_feature_set(ar->hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);
	wiphy_ext_feature_set(ar->hw->wiphy, NL80211_EXT_FEATURE_STA_TX_PWR);

	ar->hw->wiphy->cipher_suites = cipher_suites;
	ar->hw->wiphy->n_cipher_suites = ARRAY_SIZE(cipher_suites);

	ar->hw->wiphy->अगरtype_ext_capab = ath11k_अगरtypes_ext_capa;
	ar->hw->wiphy->num_अगरtype_ext_capab =
		ARRAY_SIZE(ath11k_अगरtypes_ext_capa);

	अगर (ar->supports_6ghz) अणु
		wiphy_ext_feature_set(ar->hw->wiphy,
				      NL80211_EXT_FEATURE_FILS_DISCOVERY);
		wiphy_ext_feature_set(ar->hw->wiphy,
				      NL80211_EXT_FEATURE_UNSOL_BCAST_PROBE_RESP);
	पूर्ण

	ath11k_reg_init(ar);

	अगर (!test_bit(ATH11K_FLAG_RAW_MODE, &ab->dev_flags)) अणु
		ar->hw->netdev_features = NETIF_F_HW_CSUM;
		ieee80211_hw_set(ar->hw, SW_CRYPTO_CONTROL);
		ieee80211_hw_set(ar->hw, SUPPORT_FAST_XMIT);
	पूर्ण

	ret = ieee80211_रेजिस्टर_hw(ar->hw);
	अगर (ret) अणु
		ath11k_err(ar->ab, "ieee80211 registration failed: %d\n", ret);
		जाओ err_मुक्त_अगर_combs;
	पूर्ण

	अगर (!ab->hw_params.supports_monitor)
		/* There's a race between calling ieee80211_रेजिस्टर_hw()
		 * and here where the monitor mode is enabled क्रम a little
		 * जबतक. But that समय is so लघु and in practise it make
		 * a dअगरference in real lअगरe.
		 */
		ar->hw->wiphy->पूर्णांकerface_modes &= ~BIT(NL80211_IFTYPE_MONITOR);

	/* Apply the regd received during initialization */
	ret = ath11k_regd_update(ar, true);
	अगर (ret) अणु
		ath11k_err(ar->ab, "ath11k regd update failed: %d\n", ret);
		जाओ err_unरेजिस्टर_hw;
	पूर्ण

	ret = ath11k_debugfs_रेजिस्टर(ar);
	अगर (ret) अणु
		ath11k_err(ar->ab, "debugfs registration failed: %d\n", ret);
		जाओ err_unरेजिस्टर_hw;
	पूर्ण

	वापस 0;

err_unरेजिस्टर_hw:
	ieee80211_unरेजिस्टर_hw(ar->hw);

err_मुक्त_अगर_combs:
	kमुक्त(ar->hw->wiphy->अगरace_combinations[0].limits);
	kमुक्त(ar->hw->wiphy->अगरace_combinations);

err_मुक्त_channels:
	kमुक्त(ar->mac.sbands[NL80211_BAND_2GHZ].channels);
	kमुक्त(ar->mac.sbands[NL80211_BAND_5GHZ].channels);
	kमुक्त(ar->mac.sbands[NL80211_BAND_6GHZ].channels);

err:
	SET_IEEE80211_DEV(ar->hw, शून्य);
	वापस ret;
पूर्ण

पूर्णांक ath11k_mac_रेजिस्टर(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k *ar;
	काष्ठा ath11k_pdev *pdev;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (test_bit(ATH11K_FLAG_REGISTERED, &ab->dev_flags))
		वापस 0;

	क्रम (i = 0; i < ab->num_radios; i++) अणु
		pdev = &ab->pdevs[i];
		ar = pdev->ar;
		अगर (ab->pdevs_macaddr_valid) अणु
			ether_addr_copy(ar->mac_addr, pdev->mac_addr);
		पूर्ण अन्यथा अणु
			ether_addr_copy(ar->mac_addr, ab->mac_addr);
			ar->mac_addr[4] += i;
		पूर्ण

		ret = __ath11k_mac_रेजिस्टर(ar);
		अगर (ret)
			जाओ err_cleanup;

		idr_init(&ar->txmgmt_idr);
		spin_lock_init(&ar->txmgmt_idr_lock);
	पूर्ण

	/* Initialize channel counters frequency value in hertz */
	ab->cc_freq_hz = IPQ8074_CC_FREQ_HERTZ;
	ab->मुक्त_vdev_map = (1LL << (ab->num_radios * TARGET_NUM_VDEVS)) - 1;

	वापस 0;

err_cleanup:
	क्रम (i = i - 1; i >= 0; i--) अणु
		pdev = &ab->pdevs[i];
		ar = pdev->ar;
		__ath11k_mac_unरेजिस्टर(ar);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath11k_mac_allocate(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा ath11k *ar;
	काष्ठा ath11k_pdev *pdev;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (test_bit(ATH11K_FLAG_REGISTERED, &ab->dev_flags))
		वापस 0;

	क्रम (i = 0; i < ab->num_radios; i++) अणु
		pdev = &ab->pdevs[i];
		hw = ieee80211_alloc_hw(माप(काष्ठा ath11k), &ath11k_ops);
		अगर (!hw) अणु
			ath11k_warn(ab, "failed to allocate mac80211 hw device\n");
			ret = -ENOMEM;
			जाओ err_मुक्त_mac;
		पूर्ण

		ar = hw->priv;
		ar->hw = hw;
		ar->ab = ab;
		ar->pdev = pdev;
		ar->pdev_idx = i;
		ar->lmac_id = ath11k_hw_get_mac_from_pdev_id(&ab->hw_params, i);

		ar->wmi = &ab->wmi_ab.wmi[i];
		/* FIXME wmi[0] is alपढ़ोy initialized during attach,
		 * Should we करो this again?
		 */
		ath11k_wmi_pdev_attach(ab, i);

		ar->cfg_tx_chainmask = pdev->cap.tx_chain_mask;
		ar->cfg_rx_chainmask = pdev->cap.rx_chain_mask;
		ar->num_tx_chains = get_num_chains(pdev->cap.tx_chain_mask);
		ar->num_rx_chains = get_num_chains(pdev->cap.rx_chain_mask);

		pdev->ar = ar;
		spin_lock_init(&ar->data_lock);
		INIT_LIST_HEAD(&ar->arvअगरs);
		INIT_LIST_HEAD(&ar->ppdu_stats_info);
		mutex_init(&ar->conf_mutex);
		init_completion(&ar->vdev_setup_करोne);
		init_completion(&ar->vdev_delete_करोne);
		init_completion(&ar->peer_assoc_करोne);
		init_completion(&ar->peer_delete_करोne);
		init_completion(&ar->install_key_करोne);
		init_completion(&ar->bss_survey_करोne);
		init_completion(&ar->scan.started);
		init_completion(&ar->scan.completed);
		init_completion(&ar->thermal.wmi_sync);

		INIT_DELAYED_WORK(&ar->scan.समयout, ath11k_scan_समयout_work);
		INIT_WORK(&ar->regd_update_work, ath11k_regd_update_work);

		INIT_WORK(&ar->wmi_mgmt_tx_work, ath11k_mgmt_over_wmi_tx_work);
		skb_queue_head_init(&ar->wmi_mgmt_tx_queue);
		clear_bit(ATH11K_FLAG_MONITOR_ENABLED, &ar->monitor_flags);
	पूर्ण

	वापस 0;

err_मुक्त_mac:
	ath11k_mac_destroy(ab);

	वापस ret;
पूर्ण

व्योम ath11k_mac_destroy(काष्ठा ath11k_base *ab)
अणु
	काष्ठा ath11k *ar;
	काष्ठा ath11k_pdev *pdev;
	पूर्णांक i;

	क्रम (i = 0; i < ab->num_radios; i++) अणु
		pdev = &ab->pdevs[i];
		ar = pdev->ar;
		अगर (!ar)
			जारी;

		ieee80211_मुक्त_hw(ar->hw);
		pdev->ar = शून्य;
	पूर्ण
पूर्ण
