<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित _RTW_HT_H_
#घोषणा _RTW_HT_H_


काष्ठा ht_priv अणु
	u8 ht_option;
	u8 ampdu_enable;/* क्रम enable Tx A-MPDU */
	u8 tx_amsdu_enable;/* क्रम enable Tx A-MSDU */
	u8 bss_coexist;/* क्रम 20/40 Bss coexist */

	/* u8 baddbareq_issued[16]; */
	u32 tx_amsdu_maxlen; /*  1: 8k, 0:4k ; शेष:8k, क्रम tx */
	u32 rx_ampdu_maxlen; /* क्रम rx reordering ctrl win_sz, updated when join_callback. */

	u8 rx_ampdu_min_spacing;

	u8 ch_offset;/* PRIME_CHNL_OFFSET */
	u8 sgi_20m;
	u8 sgi_40m;

	/* क्रम processing Tx A-MPDU */
	u8 agg_enable_biपंचांगap;
	/* u8 ADDBA_retry_count; */
	u8 candidate_tid_biपंचांगap;

	u8 ldpc_cap;
	u8 stbc_cap;
	u8 beamक्रमm_cap;

	काष्ठा ieee80211_ht_cap ht_cap;

पूर्ण;

क्रमागत अणु
	HT_AGG_SIZE_8K = 0,
	HT_AGG_SIZE_16K = 1,
	HT_AGG_SIZE_32K = 2,
	HT_AGG_SIZE_64K = 3,
	VHT_AGG_SIZE_128K = 4,
	VHT_AGG_SIZE_256K = 5,
	VHT_AGG_SIZE_512K = 6,
	VHT_AGG_SIZE_1024K = 7,
पूर्ण;

क्रमागत अणु
	RT_HT_CAP_USE_TURBO_AGGR = 0x01,
	RT_HT_CAP_USE_LONG_PREAMBLE = 0x02,
	RT_HT_CAP_USE_AMPDU = 0x04,
	RT_HT_CAP_USE_WOW = 0x8,
	RT_HT_CAP_USE_SOFTAP = 0x10,
	RT_HT_CAP_USE_92SE = 0x20,
	RT_HT_CAP_USE_88C_92C = 0x40,
	RT_HT_CAP_USE_AP_CLIENT_MODE = 0x80,	/*  AP team request to reserve this bit, by Emily */
पूर्ण;

क्रमागत अणु
	RT_HT_CAP_USE_VIDEO_CLIENT = 0x01,
	RT_HT_CAP_USE_JAGUAR_BCUT = 0x02,
	RT_HT_CAP_USE_JAGUAR_CCUT = 0x04,
पूर्ण;

#घोषणा	LDPC_HT_ENABLE_RX			BIT0
#घोषणा	LDPC_HT_ENABLE_TX			BIT1
#घोषणा	LDPC_HT_TEST_TX_ENABLE		BIT2
#घोषणा	LDPC_HT_CAP_TX				BIT3

#घोषणा	STBC_HT_ENABLE_RX			BIT0
#घोषणा	STBC_HT_ENABLE_TX			BIT1
#घोषणा	STBC_HT_TEST_TX_ENABLE		BIT2
#घोषणा	STBC_HT_CAP_TX				BIT3

#घोषणा	BEAMFORMING_HT_BEAMFORMER_ENABLE	BIT0	/*  Declare our NIC supports beamक्रमmer */
#घोषणा	BEAMFORMING_HT_BEAMFORMEE_ENABLE	BIT1	/*  Declare our NIC supports beamक्रमmee */
#घोषणा	BEAMFORMING_HT_BEAMFORMER_TEST		BIT2	/*  Transmiting Beamक्रमming no matter the target supports it or not */

/*  */
/*  The HT Control field */
/*  */
#घोषणा SET_HT_CTRL_CSI_STEERING(_pEleStart, _val)					SET_BITS_TO_LE_1BYTE((_pEleStart)+2, 6, 2, _val)
#घोषणा SET_HT_CTRL_NDP_ANNOUNCEMENT(_pEleStart, _val)			SET_BITS_TO_LE_1BYTE((_pEleStart)+3, 0, 1, _val)
#घोषणा GET_HT_CTRL_NDP_ANNOUNCEMENT(_pEleStart)					LE_BITS_TO_1BYTE((_pEleStart)+3, 0, 1)

/*  20/40 BSS Coexist */
#घोषणा SET_EXT_CAPABILITY_ELE_BSS_COEXIST(_pEleStart, _val)			SET_BITS_TO_LE_1BYTE((_pEleStart), 0, 1, _val)
#घोषणा GET_EXT_CAPABILITY_ELE_BSS_COEXIST(_pEleStart)				LE_BITS_TO_1BYTE((_pEleStart), 0, 1)


#घोषणा GET_HT_CAPABILITY_ELE_LDPC_CAP(_pEleStart)				LE_BITS_TO_1BYTE(_pEleStart, 0, 1)
#घोषणा GET_HT_CAPABILITY_ELE_TX_STBC(_pEleStart)					LE_BITS_TO_1BYTE(_pEleStart, 7, 1)

#घोषणा GET_HT_CAPABILITY_ELE_RX_STBC(_pEleStart)					LE_BITS_TO_1BYTE((_pEleStart)+1, 0, 2)

/* TXBF Capabilities */
#घोषणा SET_HT_CAP_TXBF_RECEIVE_NDP_CAP(_pEleStart, _val)					SET_BITS_TO_LE_4BYTE(((u8 *)(_pEleStart))+21, 3, 1, ((u8)_val))
#घोषणा SET_HT_CAP_TXBF_TRANSMIT_NDP_CAP(_pEleStart, _val)				SET_BITS_TO_LE_4BYTE(((u8 *)(_pEleStart))+21, 4, 1, ((u8)_val))
#घोषणा SET_HT_CAP_TXBF_EXPLICIT_COMP_STEERING_CAP(_pEleStart, _val)		SET_BITS_TO_LE_4BYTE(((u8 *)(_pEleStart))+21, 10, 1, ((u8)_val))
#घोषणा SET_HT_CAP_TXBF_EXPLICIT_COMP_FEEDBACK_CAP(_pEleStart, _val)		SET_BITS_TO_LE_4BYTE(((u8 *)(_pEleStart))+21, 15, 2, ((u8)_val))
#घोषणा SET_HT_CAP_TXBF_COMP_STEERING_NUM_ANTENNAS(_pEleStart, _val)	SET_BITS_TO_LE_4BYTE(((u8 *)(_pEleStart))+21, 23, 2, ((u8)_val))

#घोषणा GET_HT_CAP_TXBF_EXPLICIT_COMP_STEERING_CAP(_pEleStart)			LE_BITS_TO_4BYTE((_pEleStart)+21, 10, 1)
#घोषणा GET_HT_CAP_TXBF_EXPLICIT_COMP_FEEDBACK_CAP(_pEleStart)			LE_BITS_TO_4BYTE((_pEleStart)+21, 15, 2)

#पूर्ण_अगर	/* _RTL871X_HT_H_ */
