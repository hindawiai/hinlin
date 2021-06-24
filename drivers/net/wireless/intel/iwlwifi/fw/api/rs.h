<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_rs_h__
#घोषणा __iwl_fw_api_rs_h__

#समावेश "mac.h"

/**
 * क्रमागत iwl_tlc_mng_cfg_flags_क्रमागत - options क्रम TLC config flags
 * @IWL_TLC_MNG_CFG_FLAGS_STBC_MSK: enable STBC. For HE this enables STBC क्रम
 *				    bandwidths <= 80MHz
 * @IWL_TLC_MNG_CFG_FLAGS_LDPC_MSK: enable LDPC
 * @IWL_TLC_MNG_CFG_FLAGS_HE_STBC_160MHZ_MSK: enable STBC in HE at 160MHz
 *					      bandwidth
 * @IWL_TLC_MNG_CFG_FLAGS_HE_DCM_NSS_1_MSK: enable HE Dual Carrier Modulation
 *					    क्रम BPSK (MCS 0) with 1 spatial
 *					    stream
 * @IWL_TLC_MNG_CFG_FLAGS_HE_DCM_NSS_2_MSK: enable HE Dual Carrier Modulation
 *					    क्रम BPSK (MCS 0) with 2 spatial
 *					    streams
 */
क्रमागत iwl_tlc_mng_cfg_flags अणु
	IWL_TLC_MNG_CFG_FLAGS_STBC_MSK			= BIT(0),
	IWL_TLC_MNG_CFG_FLAGS_LDPC_MSK			= BIT(1),
	IWL_TLC_MNG_CFG_FLAGS_HE_STBC_160MHZ_MSK	= BIT(2),
	IWL_TLC_MNG_CFG_FLAGS_HE_DCM_NSS_1_MSK		= BIT(3),
	IWL_TLC_MNG_CFG_FLAGS_HE_DCM_NSS_2_MSK		= BIT(4),
पूर्ण;

/**
 * क्रमागत iwl_tlc_mng_cfg_cw - channel width options
 * @IWL_TLC_MNG_CH_WIDTH_20MHZ: 20MHZ channel
 * @IWL_TLC_MNG_CH_WIDTH_40MHZ: 40MHZ channel
 * @IWL_TLC_MNG_CH_WIDTH_80MHZ: 80MHZ channel
 * @IWL_TLC_MNG_CH_WIDTH_160MHZ: 160MHZ channel
 * @IWL_TLC_MNG_CH_WIDTH_LAST: maximum value
 */
क्रमागत iwl_tlc_mng_cfg_cw अणु
	IWL_TLC_MNG_CH_WIDTH_20MHZ,
	IWL_TLC_MNG_CH_WIDTH_40MHZ,
	IWL_TLC_MNG_CH_WIDTH_80MHZ,
	IWL_TLC_MNG_CH_WIDTH_160MHZ,
	IWL_TLC_MNG_CH_WIDTH_LAST = IWL_TLC_MNG_CH_WIDTH_160MHZ,
पूर्ण;

/**
 * क्रमागत iwl_tlc_mng_cfg_chains - possible chains
 * @IWL_TLC_MNG_CHAIN_A_MSK: chain A
 * @IWL_TLC_MNG_CHAIN_B_MSK: chain B
 */
क्रमागत iwl_tlc_mng_cfg_chains अणु
	IWL_TLC_MNG_CHAIN_A_MSK = BIT(0),
	IWL_TLC_MNG_CHAIN_B_MSK = BIT(1),
पूर्ण;

/**
 * क्रमागत iwl_tlc_mng_cfg_mode - supported modes
 * @IWL_TLC_MNG_MODE_CCK: enable CCK
 * @IWL_TLC_MNG_MODE_OFDM_NON_HT: enable OFDM (non HT)
 * @IWL_TLC_MNG_MODE_NON_HT: enable non HT
 * @IWL_TLC_MNG_MODE_HT: enable HT
 * @IWL_TLC_MNG_MODE_VHT: enable VHT
 * @IWL_TLC_MNG_MODE_HE: enable HE
 * @IWL_TLC_MNG_MODE_INVALID: invalid value
 * @IWL_TLC_MNG_MODE_NUM: a count of possible modes
 */
क्रमागत iwl_tlc_mng_cfg_mode अणु
	IWL_TLC_MNG_MODE_CCK = 0,
	IWL_TLC_MNG_MODE_OFDM_NON_HT = IWL_TLC_MNG_MODE_CCK,
	IWL_TLC_MNG_MODE_NON_HT = IWL_TLC_MNG_MODE_CCK,
	IWL_TLC_MNG_MODE_HT,
	IWL_TLC_MNG_MODE_VHT,
	IWL_TLC_MNG_MODE_HE,
	IWL_TLC_MNG_MODE_INVALID,
	IWL_TLC_MNG_MODE_NUM = IWL_TLC_MNG_MODE_INVALID,
पूर्ण;

/**
 * क्रमागत iwl_tlc_mng_ht_rates - HT/VHT/HE rates
 * @IWL_TLC_MNG_HT_RATE_MCS0: index of MCS0
 * @IWL_TLC_MNG_HT_RATE_MCS1: index of MCS1
 * @IWL_TLC_MNG_HT_RATE_MCS2: index of MCS2
 * @IWL_TLC_MNG_HT_RATE_MCS3: index of MCS3
 * @IWL_TLC_MNG_HT_RATE_MCS4: index of MCS4
 * @IWL_TLC_MNG_HT_RATE_MCS5: index of MCS5
 * @IWL_TLC_MNG_HT_RATE_MCS6: index of MCS6
 * @IWL_TLC_MNG_HT_RATE_MCS7: index of MCS7
 * @IWL_TLC_MNG_HT_RATE_MCS8: index of MCS8
 * @IWL_TLC_MNG_HT_RATE_MCS9: index of MCS9
 * @IWL_TLC_MNG_HT_RATE_MCS10: index of MCS10
 * @IWL_TLC_MNG_HT_RATE_MCS11: index of MCS11
 * @IWL_TLC_MNG_HT_RATE_MAX: maximal rate क्रम HT/VHT
 */
क्रमागत iwl_tlc_mng_ht_rates अणु
	IWL_TLC_MNG_HT_RATE_MCS0 = 0,
	IWL_TLC_MNG_HT_RATE_MCS1,
	IWL_TLC_MNG_HT_RATE_MCS2,
	IWL_TLC_MNG_HT_RATE_MCS3,
	IWL_TLC_MNG_HT_RATE_MCS4,
	IWL_TLC_MNG_HT_RATE_MCS5,
	IWL_TLC_MNG_HT_RATE_MCS6,
	IWL_TLC_MNG_HT_RATE_MCS7,
	IWL_TLC_MNG_HT_RATE_MCS8,
	IWL_TLC_MNG_HT_RATE_MCS9,
	IWL_TLC_MNG_HT_RATE_MCS10,
	IWL_TLC_MNG_HT_RATE_MCS11,
	IWL_TLC_MNG_HT_RATE_MAX = IWL_TLC_MNG_HT_RATE_MCS11,
पूर्ण;

क्रमागत IWL_TLC_MNG_NSS अणु
	IWL_TLC_NSS_1,
	IWL_TLC_NSS_2,
	IWL_TLC_NSS_MAX
पूर्ण;

क्रमागत IWL_TLC_HT_BW_RATES अणु
	IWL_TLC_HT_BW_NONE_160,
	IWL_TLC_HT_BW_160,
पूर्ण;

/**
 * काष्ठा tlc_config_cmd - TLC configuration
 * @sta_id: station id
 * @reserved1: reserved
 * @max_ch_width: max supported channel width from @क्रमागत iwl_tlc_mng_cfg_cw
 * @mode: &क्रमागत iwl_tlc_mng_cfg_mode
 * @chains: biपंचांगask of &क्रमागत iwl_tlc_mng_cfg_chains
 * @amsdu: TX amsdu is supported
 * @flags: biपंचांगask of &क्रमागत iwl_tlc_mng_cfg_flags
 * @non_ht_rates: biपंचांगap of supported legacy rates
 * @ht_rates: biपंचांगap of &क्रमागत iwl_tlc_mng_ht_rates, per <nss, channel-width>
 *	      pair (0 - 80mhz width and below, 1 - 160mhz).
 * @max_mpdu_len: max MPDU length, in bytes
 * @sgi_ch_width_supp: biपंचांगap of SGI support per channel width
 *		       use BIT(@क्रमागत iwl_tlc_mng_cfg_cw)
 * @reserved2: reserved
 * @max_tx_op: max TXOP in uSecs क्रम all AC (BK, BE, VO, VI),
 *	       set zero क्रम no limit.
 */
काष्ठा iwl_tlc_config_cmd अणु
	u8 sta_id;
	u8 reserved1[3];
	u8 max_ch_width;
	u8 mode;
	u8 chains;
	u8 amsdu;
	__le16 flags;
	__le16 non_ht_rates;
	__le16 ht_rates[IWL_TLC_NSS_MAX][2];
	__le16 max_mpdu_len;
	u8 sgi_ch_width_supp;
	u8 reserved2;
	__le32 max_tx_op;
पूर्ण __packed; /* TLC_MNG_CONFIG_CMD_API_S_VER_3 */

/**
 * क्रमागत iwl_tlc_update_flags - updated fields
 * @IWL_TLC_NOTIF_FLAG_RATE: last initial rate update
 * @IWL_TLC_NOTIF_FLAG_AMSDU: umsdu parameters update
 */
क्रमागत iwl_tlc_update_flags अणु
	IWL_TLC_NOTIF_FLAG_RATE  = BIT(0),
	IWL_TLC_NOTIF_FLAG_AMSDU = BIT(1),
पूर्ण;

/**
 * काष्ठा iwl_tlc_update_notअगर - TLC notअगरication from FW
 * @sta_id: station id
 * @reserved: reserved
 * @flags: biपंचांगap of notअगरications reported
 * @rate: current initial rate
 * @amsdu_size: Max AMSDU size, in bytes
 * @amsdu_enabled: biपंचांगap क्रम per-TID AMSDU enablement
 */
काष्ठा iwl_tlc_update_notअगर अणु
	u8 sta_id;
	u8 reserved[3];
	__le32 flags;
	__le32 rate;
	__le32 amsdu_size;
	__le32 amsdu_enabled;
पूर्ण __packed; /* TLC_MNG_UPDATE_NTFY_API_S_VER_2 */

/*
 * These serve as indexes पूर्णांकo
 * काष्ठा iwl_rate_info fw_rate_idx_to_plcp[IWL_RATE_COUNT];
 * TODO: aव्योम overlap between legacy and HT rates
 */
क्रमागत अणु
	IWL_RATE_1M_INDEX = 0,
	IWL_FIRST_CCK_RATE = IWL_RATE_1M_INDEX,
	IWL_RATE_2M_INDEX,
	IWL_RATE_5M_INDEX,
	IWL_RATE_11M_INDEX,
	IWL_LAST_CCK_RATE = IWL_RATE_11M_INDEX,
	IWL_RATE_6M_INDEX,
	IWL_FIRST_OFDM_RATE = IWL_RATE_6M_INDEX,
	IWL_RATE_MCS_0_INDEX = IWL_RATE_6M_INDEX,
	IWL_FIRST_HT_RATE = IWL_RATE_MCS_0_INDEX,
	IWL_FIRST_VHT_RATE = IWL_RATE_MCS_0_INDEX,
	IWL_RATE_9M_INDEX,
	IWL_RATE_12M_INDEX,
	IWL_RATE_MCS_1_INDEX = IWL_RATE_12M_INDEX,
	IWL_RATE_18M_INDEX,
	IWL_RATE_MCS_2_INDEX = IWL_RATE_18M_INDEX,
	IWL_RATE_24M_INDEX,
	IWL_RATE_MCS_3_INDEX = IWL_RATE_24M_INDEX,
	IWL_RATE_36M_INDEX,
	IWL_RATE_MCS_4_INDEX = IWL_RATE_36M_INDEX,
	IWL_RATE_48M_INDEX,
	IWL_RATE_MCS_5_INDEX = IWL_RATE_48M_INDEX,
	IWL_RATE_54M_INDEX,
	IWL_RATE_MCS_6_INDEX = IWL_RATE_54M_INDEX,
	IWL_LAST_NON_HT_RATE = IWL_RATE_54M_INDEX,
	IWL_RATE_60M_INDEX,
	IWL_RATE_MCS_7_INDEX = IWL_RATE_60M_INDEX,
	IWL_LAST_HT_RATE = IWL_RATE_MCS_7_INDEX,
	IWL_RATE_MCS_8_INDEX,
	IWL_RATE_MCS_9_INDEX,
	IWL_LAST_VHT_RATE = IWL_RATE_MCS_9_INDEX,
	IWL_RATE_MCS_10_INDEX,
	IWL_RATE_MCS_11_INDEX,
	IWL_LAST_HE_RATE = IWL_RATE_MCS_11_INDEX,
	IWL_RATE_COUNT_LEGACY = IWL_LAST_NON_HT_RATE + 1,
	IWL_RATE_COUNT = IWL_LAST_HE_RATE + 1,
पूर्ण;

#घोषणा IWL_RATE_BIT_MSK(r) BIT(IWL_RATE_##r##M_INDEX)

/* fw API values क्रम legacy bit rates, both OFDM and CCK */
क्रमागत अणु
	IWL_RATE_6M_PLCP  = 13,
	IWL_RATE_9M_PLCP  = 15,
	IWL_RATE_12M_PLCP = 5,
	IWL_RATE_18M_PLCP = 7,
	IWL_RATE_24M_PLCP = 9,
	IWL_RATE_36M_PLCP = 11,
	IWL_RATE_48M_PLCP = 1,
	IWL_RATE_54M_PLCP = 3,
	IWL_RATE_1M_PLCP  = 10,
	IWL_RATE_2M_PLCP  = 20,
	IWL_RATE_5M_PLCP  = 55,
	IWL_RATE_11M_PLCP = 110,
	IWL_RATE_INVM_PLCP = -1,
पूर्ण;

/*
 * rate_n_flags bit fields
 *
 * The 32-bit value has dअगरferent layouts in the low 8 bites depending on the
 * क्रमmat. There are three क्रमmats, HT, VHT and legacy (11abg, with subक्रमmats
 * क्रम CCK and OFDM).
 *
 * High-throughput (HT) rate क्रमmat
 *	bit 8 is 1, bit 26 is 0, bit 9 is 0 (OFDM)
 * Very High-throughput (VHT) rate क्रमmat
 *	bit 8 is 0, bit 26 is 1, bit 9 is 0 (OFDM)
 * Legacy OFDM rate क्रमmat क्रम bits 7:0
 *	bit 8 is 0, bit 26 is 0, bit 9 is 0 (OFDM)
 * Legacy CCK rate क्रमmat क्रम bits 7:0:
 *	bit 8 is 0, bit 26 is 0, bit 9 is 1 (CCK)
 */

/* Bit 8: (1) HT क्रमmat, (0) legacy or VHT क्रमmat */
#घोषणा RATE_MCS_HT_POS 8
#घोषणा RATE_MCS_HT_MSK (1 << RATE_MCS_HT_POS)

/* Bit 9: (1) CCK, (0) OFDM.  HT (bit 8) must be "0" क्रम this bit to be valid */
#घोषणा RATE_MCS_CCK_POS 9
#घोषणा RATE_MCS_CCK_MSK (1 << RATE_MCS_CCK_POS)

/* Bit 26: (1) VHT क्रमmat, (0) legacy क्रमmat in bits 8:0 */
#घोषणा RATE_MCS_VHT_POS 26
#घोषणा RATE_MCS_VHT_MSK (1 << RATE_MCS_VHT_POS)


/*
 * High-throughput (HT) rate क्रमmat क्रम bits 7:0
 *
 *  2-0:  MCS rate base
 *        0)   6 Mbps
 *        1)  12 Mbps
 *        2)  18 Mbps
 *        3)  24 Mbps
 *        4)  36 Mbps
 *        5)  48 Mbps
 *        6)  54 Mbps
 *        7)  60 Mbps
 *  4-3:  0)  Single stream (SISO)
 *        1)  Dual stream (MIMO)
 *        2)  Triple stream (MIMO)
 *    5:  Value of 0x20 in bits 7:0 indicates 6 Mbps HT40 duplicate data
 *  (bits 7-6 are zero)
 *
 * Together the low 5 bits work out to the MCS index because we करोn't
 * support MCSes above 15/23, and 0-7 have one stream, 8-15 have two
 * streams and 16-23 have three streams. We could also support MCS 32
 * which is the duplicate 20 MHz MCS (bit 5 set, all others zero.)
 */
#घोषणा RATE_HT_MCS_RATE_CODE_MSK	0x7
#घोषणा RATE_HT_MCS_NSS_POS             3
#घोषणा RATE_HT_MCS_NSS_MSK             (3 << RATE_HT_MCS_NSS_POS)

/* Bit 10: (1) Use Green Field preamble */
#घोषणा RATE_HT_MCS_GF_POS		10
#घोषणा RATE_HT_MCS_GF_MSK		(1 << RATE_HT_MCS_GF_POS)

#घोषणा RATE_HT_MCS_INDEX_MSK		0x3f

/*
 * Very High-throughput (VHT) rate क्रमmat क्रम bits 7:0
 *
 *  3-0:  VHT MCS (0-9)
 *  5-4:  number of streams - 1:
 *        0)  Single stream (SISO)
 *        1)  Dual stream (MIMO)
 *        2)  Triple stream (MIMO)
 */

/* Bit 4-5: (0) SISO, (1) MIMO2 (2) MIMO3 */
#घोषणा RATE_VHT_MCS_RATE_CODE_MSK	0xf
#घोषणा RATE_VHT_MCS_NSS_POS		4
#घोषणा RATE_VHT_MCS_NSS_MSK		(3 << RATE_VHT_MCS_NSS_POS)

/*
 * Legacy OFDM rate क्रमmat क्रम bits 7:0
 *
 *  3-0:  0xD)   6 Mbps
 *        0xF)   9 Mbps
 *        0x5)  12 Mbps
 *        0x7)  18 Mbps
 *        0x9)  24 Mbps
 *        0xB)  36 Mbps
 *        0x1)  48 Mbps
 *        0x3)  54 Mbps
 * (bits 7-4 are 0)
 *
 * Legacy CCK rate क्रमmat क्रम bits 7:0:
 * bit 8 is 0, bit 26 is 0, bit 9 is 1 (CCK):
 *
 *  6-0:   10)  1 Mbps
 *         20)  2 Mbps
 *         55)  5.5 Mbps
 *        110)  11 Mbps
 * (bit 7 is 0)
 */
#घोषणा RATE_LEGACY_RATE_MSK 0xff

/* Bit 10 - OFDM HE */
#घोषणा RATE_MCS_HE_POS		10
#घोषणा RATE_MCS_HE_MSK		BIT(RATE_MCS_HE_POS)

/*
 * Bit 11-12: (0) 20MHz, (1) 40MHz, (2) 80MHz, (3) 160MHz
 * 0 and 1 are valid क्रम HT and VHT, 2 and 3 only क्रम VHT
 */
#घोषणा RATE_MCS_CHAN_WIDTH_POS		11
#घोषणा RATE_MCS_CHAN_WIDTH_MSK		(3 << RATE_MCS_CHAN_WIDTH_POS)
#घोषणा RATE_MCS_CHAN_WIDTH_20		(0 << RATE_MCS_CHAN_WIDTH_POS)
#घोषणा RATE_MCS_CHAN_WIDTH_40		(1 << RATE_MCS_CHAN_WIDTH_POS)
#घोषणा RATE_MCS_CHAN_WIDTH_80		(2 << RATE_MCS_CHAN_WIDTH_POS)
#घोषणा RATE_MCS_CHAN_WIDTH_160		(3 << RATE_MCS_CHAN_WIDTH_POS)

/* Bit 13: (1) Short guard पूर्णांकerval (0.4 usec), (0) normal GI (0.8 usec) */
#घोषणा RATE_MCS_SGI_POS		13
#घोषणा RATE_MCS_SGI_MSK		(1 << RATE_MCS_SGI_POS)

/* Bit 14-16: Antenna selection (1) Ant A, (2) Ant B, (4) Ant C */
#घोषणा RATE_MCS_ANT_POS		14
#घोषणा RATE_MCS_ANT_A_MSK		(1 << RATE_MCS_ANT_POS)
#घोषणा RATE_MCS_ANT_B_MSK		(2 << RATE_MCS_ANT_POS)
#घोषणा RATE_MCS_ANT_C_MSK		(4 << RATE_MCS_ANT_POS)
#घोषणा RATE_MCS_ANT_AB_MSK		(RATE_MCS_ANT_A_MSK | \
					 RATE_MCS_ANT_B_MSK)
#घोषणा RATE_MCS_ANT_ABC_MSK		(RATE_MCS_ANT_AB_MSK | \
					 RATE_MCS_ANT_C_MSK)
#घोषणा RATE_MCS_ANT_MSK		RATE_MCS_ANT_ABC_MSK

/* Bit 17: (0) SS, (1) SS*2 */
#घोषणा RATE_MCS_STBC_POS		17
#घोषणा RATE_MCS_STBC_MSK		BIT(RATE_MCS_STBC_POS)

/* Bit 18: OFDM-HE dual carrier mode */
#घोषणा RATE_HE_DUAL_CARRIER_MODE	18
#घोषणा RATE_HE_DUAL_CARRIER_MODE_MSK	BIT(RATE_HE_DUAL_CARRIER_MODE)

/* Bit 19: (0) Beamक्रमming is off, (1) Beamक्रमming is on */
#घोषणा RATE_MCS_BF_POS			19
#घोषणा RATE_MCS_BF_MSK			(1 << RATE_MCS_BF_POS)

/*
 * Bit 20-21: HE LTF type and guard पूर्णांकerval
 * HE (ext) SU:
 *	0			1xLTF+0.8us
 *	1			2xLTF+0.8us
 *	2			2xLTF+1.6us
 *	3 & SGI (bit 13) clear	4xLTF+3.2us
 *	3 & SGI (bit 13) set	4xLTF+0.8us
 * HE MU:
 *	0			4xLTF+0.8us
 *	1			2xLTF+0.8us
 *	2			2xLTF+1.6us
 *	3			4xLTF+3.2us
 * HE TRIG:
 *	0			1xLTF+1.6us
 *	1			2xLTF+1.6us
 *	2			4xLTF+3.2us
 *	3			(करोes not occur)
 */
#घोषणा RATE_MCS_HE_GI_LTF_POS		20
#घोषणा RATE_MCS_HE_GI_LTF_MSK		(3 << RATE_MCS_HE_GI_LTF_POS)

/* Bit 22-23: HE type. (0) SU, (1) SU_EXT, (2) MU, (3) trigger based */
#घोषणा RATE_MCS_HE_TYPE_POS		22
#घोषणा RATE_MCS_HE_TYPE_SU		(0 << RATE_MCS_HE_TYPE_POS)
#घोषणा RATE_MCS_HE_TYPE_EXT_SU		(1 << RATE_MCS_HE_TYPE_POS)
#घोषणा RATE_MCS_HE_TYPE_MU		(2 << RATE_MCS_HE_TYPE_POS)
#घोषणा RATE_MCS_HE_TYPE_TRIG		(3 << RATE_MCS_HE_TYPE_POS)
#घोषणा RATE_MCS_HE_TYPE_MSK		(3 << RATE_MCS_HE_TYPE_POS)

/* Bit 24-25: (0) 20MHz (no dup), (1) 2x20MHz, (2) 4x20MHz, 3 8x20MHz */
#घोषणा RATE_MCS_DUP_POS		24
#घोषणा RATE_MCS_DUP_MSK		(3 << RATE_MCS_DUP_POS)

/* Bit 27: (1) LDPC enabled, (0) LDPC disabled */
#घोषणा RATE_MCS_LDPC_POS		27
#घोषणा RATE_MCS_LDPC_MSK		(1 << RATE_MCS_LDPC_POS)

/* Bit 28: (1) 106-tone RX (8 MHz RU), (0) normal bandwidth */
#घोषणा RATE_MCS_HE_106T_POS		28
#घोषणा RATE_MCS_HE_106T_MSK		(1 << RATE_MCS_HE_106T_POS)

/* Bit 30-31: (1) RTS, (2) CTS */
#घोषणा RATE_MCS_RTS_REQUIRED_POS  (30)
#घोषणा RATE_MCS_RTS_REQUIRED_MSK  (0x1 << RATE_MCS_RTS_REQUIRED_POS)

#घोषणा RATE_MCS_CTS_REQUIRED_POS  (31)
#घोषणा RATE_MCS_CTS_REQUIRED_MSK  (0x1 << RATE_MCS_CTS_REQUIRED_POS)

/* Link Quality definitions */

/* # entries in rate scale table to support Tx retries */
#घोषणा  LQ_MAX_RETRY_NUM 16

/* Link quality command flags bit fields */

/* Bit 0: (0) Don't use RTS (1) Use RTS */
#घोषणा LQ_FLAG_USE_RTS_POS             0
#घोषणा LQ_FLAG_USE_RTS_MSK	        (1 << LQ_FLAG_USE_RTS_POS)

/* Bit 1-3: LQ command color. Used to match responses to LQ commands */
#घोषणा LQ_FLAG_COLOR_POS               1
#घोषणा LQ_FLAG_COLOR_MSK               (7 << LQ_FLAG_COLOR_POS)
#घोषणा LQ_FLAG_COLOR_GET(_f)		(((_f) & LQ_FLAG_COLOR_MSK) >>\
					 LQ_FLAG_COLOR_POS)
#घोषणा LQ_FLAGS_COLOR_INC(_c)		((((_c) + 1) << LQ_FLAG_COLOR_POS) &\
					 LQ_FLAG_COLOR_MSK)
#घोषणा LQ_FLAG_COLOR_SET(_f, _c)	((_c) | ((_f) & ~LQ_FLAG_COLOR_MSK))

/* Bit 4-5: Tx RTS BW Signalling
 * (0) No RTS BW संकेतling
 * (1) Static BW संकेतling
 * (2) Dynamic BW संकेतling
 */
#घोषणा LQ_FLAG_RTS_BW_SIG_POS          4
#घोषणा LQ_FLAG_RTS_BW_SIG_NONE         (0 << LQ_FLAG_RTS_BW_SIG_POS)
#घोषणा LQ_FLAG_RTS_BW_SIG_STATIC       (1 << LQ_FLAG_RTS_BW_SIG_POS)
#घोषणा LQ_FLAG_RTS_BW_SIG_DYNAMIC      (2 << LQ_FLAG_RTS_BW_SIG_POS)

/* Bit 6: (0) No dynamic BW selection (1) Allow dynamic BW selection
 * Dyanmic BW selection allows Tx with narrower BW then requested in rates
 */
#घोषणा LQ_FLAG_DYNAMIC_BW_POS          6
#घोषणा LQ_FLAG_DYNAMIC_BW_MSK          (1 << LQ_FLAG_DYNAMIC_BW_POS)

/* Single Stream Tx Parameters (lq_cmd->ss_params)
 * Flags to control a smart FW decision about whether BFER/STBC/SISO will be
 * used क्रम single stream Tx.
 */

/* Bit 0-1: Max STBC streams allowed. Can be 0-3.
 * (0) - No STBC allowed
 * (1) - 2x1 STBC allowed (HT/VHT)
 * (2) - 4x2 STBC allowed (HT/VHT)
 * (3) - 3x2 STBC allowed (HT only)
 * All our chips are at most 2 antennas so only (1) is valid क्रम now.
 */
#घोषणा LQ_SS_STBC_ALLOWED_POS          0
#घोषणा LQ_SS_STBC_ALLOWED_MSK		(3 << LQ_SS_STBC_ALLOWED_MSK)

/* 2x1 STBC is allowed */
#घोषणा LQ_SS_STBC_1SS_ALLOWED		(1 << LQ_SS_STBC_ALLOWED_POS)

/* Bit 2: Beamक्रमmer (VHT only) is allowed */
#घोषणा LQ_SS_BFER_ALLOWED_POS		2
#घोषणा LQ_SS_BFER_ALLOWED		(1 << LQ_SS_BFER_ALLOWED_POS)

/* Bit 3: Force BFER or STBC क्रम testing
 * If this is set:
 * If BFER is allowed then क्रमce the ucode to choose BFER अन्यथा
 * If STBC is allowed then क्रमce the ucode to choose STBC over SISO
 */
#घोषणा LQ_SS_FORCE_POS			3
#घोषणा LQ_SS_FORCE			(1 << LQ_SS_FORCE_POS)

/* Bit 31: ss_params field is valid. Used क्रम FW backward compatibility
 * with other drivers which करोn't support the ss_params API yet
 */
#घोषणा LQ_SS_PARAMS_VALID_POS		31
#घोषणा LQ_SS_PARAMS_VALID		(1 << LQ_SS_PARAMS_VALID_POS)

/**
 * काष्ठा iwl_lq_cmd - link quality command
 * @sta_id: station to update
 * @reduced_tpc: reduced transmit घातer control value
 * @control: not used
 * @flags: combination of LQ_FLAG_*
 * @mimo_delim: the first SISO index in rs_table, which separates MIMO
 *	and SISO rates
 * @single_stream_ant_msk: best antenna क्रम SISO (can be dual in CDD).
 *	Should be ANT_[ABC]
 * @dual_stream_ant_msk: best antennas क्रम MIMO, combination of ANT_[ABC]
 * @initial_rate_index: first index from rs_table per AC category
 * @agg_समय_limit: aggregation max समय threshold in usec/100, meaning
 *	value of 100 is one usec. Range is 100 to 8000
 * @agg_disable_start_th: try-count threshold क्रम starting aggregation.
 *	If a frame has higher try-count, it should not be selected क्रम
 *	starting an aggregation sequence.
 * @agg_frame_cnt_limit: max frame count in an aggregation.
 *	0: no limit
 *	1: no aggregation (one frame per aggregation)
 *	2 - 0x3f: maximal number of frames (up to 3f == 63)
 * @reserved2: reserved
 * @rs_table: array of rates क्रम each TX try, each is rate_n_flags,
 *	meaning it is a combination of RATE_MCS_* and IWL_RATE_*_PLCP
 * @ss_params: single stream features. declare whether STBC or BFER are allowed.
 */
काष्ठा iwl_lq_cmd अणु
	u8 sta_id;
	u8 reduced_tpc;
	__le16 control;
	/* LINK_QUAL_GENERAL_PARAMS_API_S_VER_1 */
	u8 flags;
	u8 mimo_delim;
	u8 single_stream_ant_msk;
	u8 dual_stream_ant_msk;
	u8 initial_rate_index[AC_NUM];
	/* LINK_QUAL_AGG_PARAMS_API_S_VER_1 */
	__le16 agg_समय_limit;
	u8 agg_disable_start_th;
	u8 agg_frame_cnt_limit;
	__le32 reserved2;
	__le32 rs_table[LQ_MAX_RETRY_NUM];
	__le32 ss_params;
पूर्ण; /* LINK_QUALITY_CMD_API_S_VER_1 */

#पूर्ण_अगर /* __iwl_fw_api_rs_h__ */
