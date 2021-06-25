<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित ATH11K_MAC_H
#घोषणा ATH11K_MAC_H

#समावेश <net/mac80211.h>
#समावेश <net/cfg80211.h>

काष्ठा ath11k;
काष्ठा ath11k_base;

काष्ठा ath11k_generic_iter अणु
	काष्ठा ath11k *ar;
	पूर्णांक ret;
पूर्ण;

/* number of failed packets (20 packets with 16 sw reties each) */
#घोषणा ATH11K_KICKOUT_THRESHOLD		(20 * 16)

/* Use insanely high numbers to make sure that the firmware implementation
 * won't start, we have the same functionality alपढ़ोy in hostapd. Unit
 * is seconds.
 */
#घोषणा ATH11K_KEEPALIVE_MIN_IDLE		3747
#घोषणा ATH11K_KEEPALIVE_MAX_IDLE		3895
#घोषणा ATH11K_KEEPALIVE_MAX_UNRESPONSIVE	3900

#घोषणा WMI_HOST_RC_DS_FLAG			0x01
#घोषणा WMI_HOST_RC_CW40_FLAG			0x02
#घोषणा WMI_HOST_RC_SGI_FLAG			0x04
#घोषणा WMI_HOST_RC_HT_FLAG			0x08
#घोषणा WMI_HOST_RC_RTSCTS_FLAG			0x10
#घोषणा WMI_HOST_RC_TX_STBC_FLAG		0x20
#घोषणा WMI_HOST_RC_RX_STBC_FLAG		0xC0
#घोषणा WMI_HOST_RC_RX_STBC_FLAG_S		6
#घोषणा WMI_HOST_RC_WEP_TKIP_FLAG		0x100
#घोषणा WMI_HOST_RC_TS_FLAG			0x200
#घोषणा WMI_HOST_RC_UAPSD_FLAG			0x400

#घोषणा WMI_HT_CAP_ENABLED			0x0001
#घोषणा WMI_HT_CAP_HT20_SGI			0x0002
#घोषणा WMI_HT_CAP_DYNAMIC_SMPS			0x0004
#घोषणा WMI_HT_CAP_TX_STBC			0x0008
#घोषणा WMI_HT_CAP_TX_STBC_MASK_SHIFT		3
#घोषणा WMI_HT_CAP_RX_STBC			0x0030
#घोषणा WMI_HT_CAP_RX_STBC_MASK_SHIFT		4
#घोषणा WMI_HT_CAP_LDPC				0x0040
#घोषणा WMI_HT_CAP_L_SIG_TXOP_PROT		0x0080
#घोषणा WMI_HT_CAP_MPDU_DENSITY			0x0700
#घोषणा WMI_HT_CAP_MPDU_DENSITY_MASK_SHIFT	8
#घोषणा WMI_HT_CAP_HT40_SGI			0x0800
#घोषणा WMI_HT_CAP_RX_LDPC			0x1000
#घोषणा WMI_HT_CAP_TX_LDPC			0x2000
#घोषणा WMI_HT_CAP_IBF_BFER			0x4000

/* These macros should be used when we wish to advertise STBC support क्रम
 * only 1SS or 2SS or 3SS.
 */
#घोषणा WMI_HT_CAP_RX_STBC_1SS			0x0010
#घोषणा WMI_HT_CAP_RX_STBC_2SS			0x0020
#घोषणा WMI_HT_CAP_RX_STBC_3SS			0x0030

#घोषणा WMI_HT_CAP_DEFAULT_ALL (WMI_HT_CAP_ENABLED    | \
				WMI_HT_CAP_HT20_SGI   | \
				WMI_HT_CAP_HT40_SGI   | \
				WMI_HT_CAP_TX_STBC    | \
				WMI_HT_CAP_RX_STBC    | \
				WMI_HT_CAP_LDPC)

#घोषणा WMI_VHT_CAP_MAX_MPDU_LEN_MASK		0x00000003
#घोषणा WMI_VHT_CAP_RX_LDPC			0x00000010
#घोषणा WMI_VHT_CAP_SGI_80MHZ			0x00000020
#घोषणा WMI_VHT_CAP_SGI_160MHZ			0x00000040
#घोषणा WMI_VHT_CAP_TX_STBC			0x00000080
#घोषणा WMI_VHT_CAP_RX_STBC_MASK		0x00000300
#घोषणा WMI_VHT_CAP_RX_STBC_MASK_SHIFT		8
#घोषणा WMI_VHT_CAP_SU_BFER			0x00000800
#घोषणा WMI_VHT_CAP_SU_BFEE			0x00001000
#घोषणा WMI_VHT_CAP_MAX_CS_ANT_MASK		0x0000E000
#घोषणा WMI_VHT_CAP_MAX_CS_ANT_MASK_SHIFT	13
#घोषणा WMI_VHT_CAP_MAX_SND_DIM_MASK		0x00070000
#घोषणा WMI_VHT_CAP_MAX_SND_DIM_MASK_SHIFT	16
#घोषणा WMI_VHT_CAP_MU_BFER			0x00080000
#घोषणा WMI_VHT_CAP_MU_BFEE			0x00100000
#घोषणा WMI_VHT_CAP_MAX_AMPDU_LEN_EXP		0x03800000
#घोषणा WMI_VHT_CAP_MAX_AMPDU_LEN_EXP_SHIT	23
#घोषणा WMI_VHT_CAP_RX_FIXED_ANT		0x10000000
#घोषणा WMI_VHT_CAP_TX_FIXED_ANT		0x20000000

#घोषणा WMI_VHT_CAP_MAX_MPDU_LEN_11454		0x00000002

/* These macros should be used when we wish to advertise STBC support क्रम
 * only 1SS or 2SS or 3SS.
 */
#घोषणा WMI_VHT_CAP_RX_STBC_1SS			0x00000100
#घोषणा WMI_VHT_CAP_RX_STBC_2SS			0x00000200
#घोषणा WMI_VHT_CAP_RX_STBC_3SS			0x00000300

#घोषणा WMI_VHT_CAP_DEFAULT_ALL (WMI_VHT_CAP_MAX_MPDU_LEN_11454  | \
				 WMI_VHT_CAP_SGI_80MHZ      |       \
				 WMI_VHT_CAP_TX_STBC        |       \
				 WMI_VHT_CAP_RX_STBC_MASK   |       \
				 WMI_VHT_CAP_RX_LDPC        |       \
				 WMI_VHT_CAP_MAX_AMPDU_LEN_EXP   |  \
				 WMI_VHT_CAP_RX_FIXED_ANT   |       \
				 WMI_VHT_CAP_TX_FIXED_ANT)

/* FIXME: should these be in ieee80211.h? */
#घोषणा IEEE80211_VHT_MCS_SUPPORT_0_11_MASK	GENMASK(23, 16)
#घोषणा IEEE80211_DISABLE_VHT_MCS_SUPPORT_0_11	BIT(24)

#घोषणा WMI_MAX_SPATIAL_STREAM			3

#घोषणा ATH11K_CHAN_WIDTH_NUM			8

#घोषणा ATH11K_OBSS_PD_MAX_THRESHOLD			-82
#घोषणा ATH11K_OBSS_PD_NON_SRG_MAX_THRESHOLD		-62
#घोषणा ATH11K_OBSS_PD_THRESHOLD_IN_DBM			BIT(29)
#घोषणा ATH11K_OBSS_PD_SRG_EN				BIT(30)
#घोषणा ATH11K_OBSS_PD_NON_SRG_EN			BIT(31)

बाह्य स्थिर काष्ठा htt_rx_ring_tlv_filter ath11k_mac_mon_status_filter_शेष;

व्योम ath11k_mac_destroy(काष्ठा ath11k_base *ab);
व्योम ath11k_mac_unरेजिस्टर(काष्ठा ath11k_base *ab);
पूर्णांक ath11k_mac_रेजिस्टर(काष्ठा ath11k_base *ab);
पूर्णांक ath11k_mac_allocate(काष्ठा ath11k_base *ab);
पूर्णांक ath11k_mac_hw_ratecode_to_legacy_rate(u8 hw_rc, u8 preamble, u8 *rateidx,
					  u16 *rate);
u8 ath11k_mac_bitrate_to_idx(स्थिर काष्ठा ieee80211_supported_band *sband,
			     u32 bitrate);
u8 ath11k_mac_hw_rate_to_idx(स्थिर काष्ठा ieee80211_supported_band *sband,
			     u8 hw_rate, bool cck);

व्योम __ath11k_mac_scan_finish(काष्ठा ath11k *ar);
व्योम ath11k_mac_scan_finish(काष्ठा ath11k *ar);

काष्ठा ath11k_vअगर *ath11k_mac_get_arvअगर(काष्ठा ath11k *ar, u32 vdev_id);
काष्ठा ath11k_vअगर *ath11k_mac_get_arvअगर_by_vdev_id(काष्ठा ath11k_base *ab,
						   u32 vdev_id);
काष्ठा ath11k *ath11k_mac_get_ar_by_vdev_id(काष्ठा ath11k_base *ab, u32 vdev_id);
काष्ठा ath11k *ath11k_mac_get_ar_by_pdev_id(काष्ठा ath11k_base *ab, u32 pdev_id);

व्योम ath11k_mac_drain_tx(काष्ठा ath11k *ar);
व्योम ath11k_mac_peer_cleanup_all(काष्ठा ath11k *ar);
पूर्णांक ath11k_mac_tx_mgmt_pending_मुक्त(पूर्णांक buf_id, व्योम *skb, व्योम *ctx);
u8 ath11k_mac_bw_to_mac80211_bw(u8 bw);
क्रमागत ath11k_supported_bw ath11k_mac_mac80211_bw_to_ath11k_bw(क्रमागत rate_info_bw bw);
क्रमागत hal_encrypt_type ath11k_dp_tx_get_encrypt_type(u32 cipher);
व्योम ath11k_mac_handle_beacon(काष्ठा ath11k *ar, काष्ठा sk_buff *skb);
व्योम ath11k_mac_handle_beacon_miss(काष्ठा ath11k *ar, u32 vdev_id);
#पूर्ण_अगर
