<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2015-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_rx_h__
#घोषणा __iwl_fw_api_rx_h__

/* API क्रम pre-9000 hardware */

#घोषणा IWL_RX_INFO_PHY_CNT 8
#घोषणा IWL_RX_INFO_ENERGY_ANT_ABC_IDX 1
#घोषणा IWL_RX_INFO_ENERGY_ANT_A_MSK 0x000000ff
#घोषणा IWL_RX_INFO_ENERGY_ANT_B_MSK 0x0000ff00
#घोषणा IWL_RX_INFO_ENERGY_ANT_C_MSK 0x00ff0000
#घोषणा IWL_RX_INFO_ENERGY_ANT_A_POS 0
#घोषणा IWL_RX_INFO_ENERGY_ANT_B_POS 8
#घोषणा IWL_RX_INFO_ENERGY_ANT_C_POS 16

क्रमागत iwl_mac_context_info अणु
	MAC_CONTEXT_INFO_NONE,
	MAC_CONTEXT_INFO_GSCAN,
पूर्ण;

/**
 * काष्ठा iwl_rx_phy_info - phy info
 * (REPLY_RX_PHY_CMD = 0xc0)
 * @non_cfg_phy_cnt: non configurable DSP phy data byte count
 * @cfg_phy_cnt: configurable DSP phy data byte count
 * @stat_id: configurable DSP phy data set ID
 * @reserved1: reserved
 * @प्रणाली_बारtamp: GP2  at on air rise
 * @बारtamp: TSF at on air rise
 * @beacon_समय_stamp: beacon at on-air rise
 * @phy_flags: general phy flags: band, modulation, ...
 * @channel: channel number
 * @non_cfg_phy: क्रम various implementations of non_cfg_phy
 * @rate_n_flags: RATE_MCS_*
 * @byte_count: frame's byte-count
 * @frame_समय: frame's समय on the air, based on byte count and frame rate
 *	calculation
 * @mac_active_msk: what MACs were active when the frame was received
 * @mac_context_info: additional info on the context in which the frame was
 *	received as defined in &क्रमागत iwl_mac_context_info
 *
 * Beक्रमe each Rx, the device sends this data. It contains PHY inक्रमmation
 * about the reception of the packet.
 */
काष्ठा iwl_rx_phy_info अणु
	u8 non_cfg_phy_cnt;
	u8 cfg_phy_cnt;
	u8 stat_id;
	u8 reserved1;
	__le32 प्रणाली_बारtamp;
	__le64 बारtamp;
	__le32 beacon_समय_stamp;
	__le16 phy_flags;
	__le16 channel;
	__le32 non_cfg_phy[IWL_RX_INFO_PHY_CNT];
	__le32 rate_n_flags;
	__le32 byte_count;
	u8 mac_active_msk;
	u8 mac_context_info;
	__le16 frame_समय;
पूर्ण __packed;

/*
 * TCP offload Rx assist info
 *
 * bits 0:3 - reserved
 * bits 4:7 - MIC CRC length
 * bits 8:12 - MAC header length
 * bit 13 - Padding indication
 * bit 14 - A-AMSDU indication
 * bit 15 - Offload enabled
 */
क्रमागत iwl_csum_rx_assist_info अणु
	CSUM_RXA_RESERVED_MASK	= 0x000f,
	CSUM_RXA_MICSIZE_MASK	= 0x00f0,
	CSUM_RXA_HEADERLEN_MASK	= 0x1f00,
	CSUM_RXA_PADD		= BIT(13),
	CSUM_RXA_AMSDU		= BIT(14),
	CSUM_RXA_ENA		= BIT(15)
पूर्ण;

/**
 * काष्ठा iwl_rx_mpdu_res_start - phy info
 * @byte_count: byte count of the frame
 * @assist: see &क्रमागत iwl_csum_rx_assist_info
 */
काष्ठा iwl_rx_mpdu_res_start अणु
	__le16 byte_count;
	__le16 assist;
पूर्ण __packed; /* _RX_MPDU_RES_START_API_S_VER_2 */

/**
 * क्रमागत iwl_rx_phy_flags - to parse %iwl_rx_phy_info phy_flags
 * @RX_RES_PHY_FLAGS_BAND_24: true अगर the packet was received on 2.4 band
 * @RX_RES_PHY_FLAGS_MOD_CCK: modulation is CCK
 * @RX_RES_PHY_FLAGS_SHORT_PREAMBLE: true अगर packet's preamble was लघु
 * @RX_RES_PHY_FLAGS_NARROW_BAND: narrow band (<20 MHz) receive
 * @RX_RES_PHY_FLAGS_ANTENNA: antenna on which the packet was received
 * @RX_RES_PHY_FLAGS_ANTENNA_POS: antenna bit position
 * @RX_RES_PHY_FLAGS_AGG: set अगर the packet was part of an A-MPDU
 * @RX_RES_PHY_FLAGS_OFDM_HT: The frame was an HT frame
 * @RX_RES_PHY_FLAGS_OFDM_GF: The frame used GF preamble
 * @RX_RES_PHY_FLAGS_OFDM_VHT: The frame was a VHT frame
 */
क्रमागत iwl_rx_phy_flags अणु
	RX_RES_PHY_FLAGS_BAND_24	= BIT(0),
	RX_RES_PHY_FLAGS_MOD_CCK	= BIT(1),
	RX_RES_PHY_FLAGS_SHORT_PREAMBLE	= BIT(2),
	RX_RES_PHY_FLAGS_NARROW_BAND	= BIT(3),
	RX_RES_PHY_FLAGS_ANTENNA	= (0x7 << 4),
	RX_RES_PHY_FLAGS_ANTENNA_POS	= 4,
	RX_RES_PHY_FLAGS_AGG		= BIT(7),
	RX_RES_PHY_FLAGS_OFDM_HT	= BIT(8),
	RX_RES_PHY_FLAGS_OFDM_GF	= BIT(9),
	RX_RES_PHY_FLAGS_OFDM_VHT	= BIT(10),
पूर्ण;

/**
 * क्रमागत iwl_mvm_rx_status - written by fw क्रम each Rx packet
 * @RX_MPDU_RES_STATUS_CRC_OK: CRC is fine
 * @RX_MPDU_RES_STATUS_OVERRUN_OK: there was no RXE overflow
 * @RX_MPDU_RES_STATUS_SRC_STA_FOUND: station was found
 * @RX_MPDU_RES_STATUS_KEY_VALID: key was valid
 * @RX_MPDU_RES_STATUS_KEY_PARAM_OK: key parameters were usable
 * @RX_MPDU_RES_STATUS_ICV_OK: ICV is fine, अगर not, the packet is destroyed
 * @RX_MPDU_RES_STATUS_MIC_OK: used क्रम CCM alg only. TKIP MIC is checked
 *	in the driver.
 * @RX_MPDU_RES_STATUS_TTAK_OK: TTAK is fine
 * @RX_MPDU_RES_STATUS_MNG_FRAME_REPLAY_ERR:  valid क्रम alg = CCM_CMAC or
 *	alg = CCM only. Checks replay attack क्रम 11w frames. Relevant only अगर
 *	%RX_MPDU_RES_STATUS_ROBUST_MNG_FRAME is set.
 * @RX_MPDU_RES_STATUS_SEC_NO_ENC: this frame is not encrypted
 * @RX_MPDU_RES_STATUS_SEC_WEP_ENC: this frame is encrypted using WEP
 * @RX_MPDU_RES_STATUS_SEC_CCM_ENC: this frame is encrypted using CCM
 * @RX_MPDU_RES_STATUS_SEC_TKIP_ENC: this frame is encrypted using TKIP
 * @RX_MPDU_RES_STATUS_SEC_EXT_ENC: this frame is encrypted using extension
 *	algorithm
 * @RX_MPDU_RES_STATUS_SEC_CMAC_GMAC_ENC: this frame is रक्षित using
 *	CMAC or GMAC
 * @RX_MPDU_RES_STATUS_SEC_ENC_ERR: this frame couldn't be decrypted
 * @RX_MPDU_RES_STATUS_SEC_ENC_MSK: biपंचांगask of the encryption algorithm
 * @RX_MPDU_RES_STATUS_DEC_DONE: this frame has been successfully decrypted
 * @RX_MPDU_RES_STATUS_EXT_IV_BIT_CMP: extended IV (set with TKIP)
 * @RX_MPDU_RES_STATUS_KEY_ID_CMP_BIT: key ID comparison करोne
 * @RX_MPDU_RES_STATUS_ROBUST_MNG_FRAME: this frame is an 11w management frame
 * @RX_MPDU_RES_STATUS_CSUM_DONE: checksum was करोne by the hw
 * @RX_MPDU_RES_STATUS_CSUM_OK: checksum found no errors
 * @RX_MPDU_RES_STATUS_STA_ID_MSK: station ID mask
 * @RX_MDPU_RES_STATUS_STA_ID_SHIFT: station ID bit shअगरt
 */
क्रमागत iwl_mvm_rx_status अणु
	RX_MPDU_RES_STATUS_CRC_OK			= BIT(0),
	RX_MPDU_RES_STATUS_OVERRUN_OK			= BIT(1),
	RX_MPDU_RES_STATUS_SRC_STA_FOUND		= BIT(2),
	RX_MPDU_RES_STATUS_KEY_VALID			= BIT(3),
	RX_MPDU_RES_STATUS_KEY_PARAM_OK			= BIT(4),
	RX_MPDU_RES_STATUS_ICV_OK			= BIT(5),
	RX_MPDU_RES_STATUS_MIC_OK			= BIT(6),
	RX_MPDU_RES_STATUS_TTAK_OK			= BIT(7),
	RX_MPDU_RES_STATUS_MNG_FRAME_REPLAY_ERR		= BIT(7),
	RX_MPDU_RES_STATUS_SEC_NO_ENC			= (0 << 8),
	RX_MPDU_RES_STATUS_SEC_WEP_ENC			= (1 << 8),
	RX_MPDU_RES_STATUS_SEC_CCM_ENC			= (2 << 8),
	RX_MPDU_RES_STATUS_SEC_TKIP_ENC			= (3 << 8),
	RX_MPDU_RES_STATUS_SEC_EXT_ENC			= (4 << 8),
	RX_MPDU_RES_STATUS_SEC_CMAC_GMAC_ENC		= (6 << 8),
	RX_MPDU_RES_STATUS_SEC_ENC_ERR			= (7 << 8),
	RX_MPDU_RES_STATUS_SEC_ENC_MSK			= (7 << 8),
	RX_MPDU_RES_STATUS_DEC_DONE			= BIT(11),
	RX_MPDU_RES_STATUS_EXT_IV_BIT_CMP		= BIT(13),
	RX_MPDU_RES_STATUS_KEY_ID_CMP_BIT		= BIT(14),
	RX_MPDU_RES_STATUS_ROBUST_MNG_FRAME		= BIT(15),
	RX_MPDU_RES_STATUS_CSUM_DONE			= BIT(16),
	RX_MPDU_RES_STATUS_CSUM_OK			= BIT(17),
	RX_MDPU_RES_STATUS_STA_ID_SHIFT			= 24,
	RX_MPDU_RES_STATUS_STA_ID_MSK			= 0x1f << RX_MDPU_RES_STATUS_STA_ID_SHIFT,
पूर्ण;

/* 9000 series API */
क्रमागत iwl_rx_mpdu_mac_flags1 अणु
	IWL_RX_MDPU_MFLG1_ADDRTYPE_MASK		= 0x03,
	IWL_RX_MPDU_MFLG1_MIC_CRC_LEN_MASK	= 0xf0,
	/* shअगरt should be 4, but the length is measured in 2-byte
	 * words, so shअगरting only by 3 gives a byte result
	 */
	IWL_RX_MPDU_MFLG1_MIC_CRC_LEN_SHIFT	= 3,
पूर्ण;

क्रमागत iwl_rx_mpdu_mac_flags2 अणु
	/* in 2-byte words */
	IWL_RX_MPDU_MFLG2_HDR_LEN_MASK		= 0x1f,
	IWL_RX_MPDU_MFLG2_PAD			= 0x20,
	IWL_RX_MPDU_MFLG2_AMSDU			= 0x40,
पूर्ण;

क्रमागत iwl_rx_mpdu_amsdu_info अणु
	IWL_RX_MPDU_AMSDU_SUBFRAME_IDX_MASK	= 0x7f,
	IWL_RX_MPDU_AMSDU_LAST_SUBFRAME		= 0x80,
पूर्ण;

#घोषणा RX_MPDU_BAND_POS 6
#घोषणा RX_MPDU_BAND_MASK 0xC0
#घोषणा BAND_IN_RX_STATUS(_val) \
	(((_val) & RX_MPDU_BAND_MASK) >> RX_MPDU_BAND_POS)

क्रमागत iwl_rx_l3_proto_values अणु
	IWL_RX_L3_TYPE_NONE,
	IWL_RX_L3_TYPE_IPV4,
	IWL_RX_L3_TYPE_IPV4_FRAG,
	IWL_RX_L3_TYPE_IPV6_FRAG,
	IWL_RX_L3_TYPE_IPV6,
	IWL_RX_L3_TYPE_IPV6_IN_IPV4,
	IWL_RX_L3_TYPE_ARP,
	IWL_RX_L3_TYPE_EAPOL,
पूर्ण;

#घोषणा IWL_RX_L3_PROTO_POS 4

क्रमागत iwl_rx_l3l4_flags अणु
	IWL_RX_L3L4_IP_HDR_CSUM_OK		= BIT(0),
	IWL_RX_L3L4_TCP_UDP_CSUM_OK		= BIT(1),
	IWL_RX_L3L4_TCP_FIN_SYN_RST_PSH		= BIT(2),
	IWL_RX_L3L4_TCP_ACK			= BIT(3),
	IWL_RX_L3L4_L3_PROTO_MASK		= 0xf << IWL_RX_L3_PROTO_POS,
	IWL_RX_L3L4_L4_PROTO_MASK		= 0xf << 8,
	IWL_RX_L3L4_RSS_HASH_MASK		= 0xf << 12,
पूर्ण;

क्रमागत iwl_rx_mpdu_status अणु
	IWL_RX_MPDU_STATUS_CRC_OK		= BIT(0),
	IWL_RX_MPDU_STATUS_OVERRUN_OK		= BIT(1),
	IWL_RX_MPDU_STATUS_SRC_STA_FOUND	= BIT(2),
	IWL_RX_MPDU_STATUS_KEY_VALID		= BIT(3),
	IWL_RX_MPDU_STATUS_KEY_PARAM_OK		= BIT(4),
	IWL_RX_MPDU_STATUS_ICV_OK		= BIT(5),
	IWL_RX_MPDU_STATUS_MIC_OK		= BIT(6),
	IWL_RX_MPDU_RES_STATUS_TTAK_OK		= BIT(7),
	/* overlayed since IWL_UCODE_TLV_API_DEPRECATE_TTAK */
	IWL_RX_MPDU_STATUS_REPLAY_ERROR		= BIT(7),
	IWL_RX_MPDU_STATUS_SEC_MASK		= 0x7 << 8,
	IWL_RX_MPDU_STATUS_SEC_UNKNOWN		= IWL_RX_MPDU_STATUS_SEC_MASK,
	IWL_RX_MPDU_STATUS_SEC_NONE		= 0x0 << 8,
	IWL_RX_MPDU_STATUS_SEC_WEP		= 0x1 << 8,
	IWL_RX_MPDU_STATUS_SEC_CCM		= 0x2 << 8,
	IWL_RX_MPDU_STATUS_SEC_TKIP		= 0x3 << 8,
	IWL_RX_MPDU_STATUS_SEC_EXT_ENC		= 0x4 << 8,
	IWL_RX_MPDU_STATUS_SEC_GCM		= 0x5 << 8,
	IWL_RX_MPDU_STATUS_DECRYPTED		= BIT(11),
	IWL_RX_MPDU_STATUS_WEP_MATCH		= BIT(12),
	IWL_RX_MPDU_STATUS_EXT_IV_MATCH		= BIT(13),
	IWL_RX_MPDU_STATUS_KEY_ID_MATCH		= BIT(14),
	IWL_RX_MPDU_STATUS_ROBUST_MNG_FRAME	= BIT(15),

	IWL_RX_MPDU_STATUS_KEY			= 0x3f0000,
	IWL_RX_MPDU_STATUS_DUPLICATE		= BIT(22),

	IWL_RX_MPDU_STATUS_STA_ID		= 0x1f000000,
पूर्ण;

#घोषणा IWL_RX_REORDER_DATA_INVALID_BAID 0x7f

क्रमागत iwl_rx_mpdu_reorder_data अणु
	IWL_RX_MPDU_REORDER_NSSN_MASK		= 0x00000fff,
	IWL_RX_MPDU_REORDER_SN_MASK		= 0x00fff000,
	IWL_RX_MPDU_REORDER_SN_SHIFT		= 12,
	IWL_RX_MPDU_REORDER_BAID_MASK		= 0x7f000000,
	IWL_RX_MPDU_REORDER_BAID_SHIFT		= 24,
	IWL_RX_MPDU_REORDER_BA_OLD_SN		= 0x80000000,
पूर्ण;

क्रमागत iwl_rx_mpdu_phy_info अणु
	IWL_RX_MPDU_PHY_AMPDU		= BIT(5),
	IWL_RX_MPDU_PHY_AMPDU_TOGGLE	= BIT(6),
	IWL_RX_MPDU_PHY_SHORT_PREAMBLE	= BIT(7),
	/* लघु preamble is only क्रम CCK, क्रम non-CCK overridden by this */
	IWL_RX_MPDU_PHY_NCCK_ADDTL_NTFY	= BIT(7),
	IWL_RX_MPDU_PHY_TSF_OVERLOAD	= BIT(8),
पूर्ण;

क्रमागत iwl_rx_mpdu_mac_info अणु
	IWL_RX_MPDU_PHY_MAC_INDEX_MASK		= 0x0f,
	IWL_RX_MPDU_PHY_PHY_INDEX_MASK		= 0xf0,
पूर्ण;

/* TSF overload low dword */
क्रमागत iwl_rx_phy_data0 अणु
	/* info type: HE any */
	IWL_RX_PHY_DATA0_HE_BEAM_CHNG				= 0x00000001,
	IWL_RX_PHY_DATA0_HE_UPLINK				= 0x00000002,
	IWL_RX_PHY_DATA0_HE_BSS_COLOR_MASK			= 0x000000fc,
	IWL_RX_PHY_DATA0_HE_SPATIAL_REUSE_MASK			= 0x00000f00,
	/* 1 bit reserved */
	IWL_RX_PHY_DATA0_HE_TXOP_DUR_MASK			= 0x000fe000,
	IWL_RX_PHY_DATA0_HE_LDPC_EXT_SYM			= 0x00100000,
	IWL_RX_PHY_DATA0_HE_PRE_FEC_PAD_MASK			= 0x00600000,
	IWL_RX_PHY_DATA0_HE_PE_DISAMBIG				= 0x00800000,
	IWL_RX_PHY_DATA0_HE_DOPPLER				= 0x01000000,
	/* 6 bits reserved */
	IWL_RX_PHY_DATA0_HE_DELIM_खातापूर्ण				= 0x80000000,
पूर्ण;

क्रमागत iwl_rx_phy_info_type अणु
	IWL_RX_PHY_INFO_TYPE_NONE				= 0,
	IWL_RX_PHY_INFO_TYPE_CCK				= 1,
	IWL_RX_PHY_INFO_TYPE_OFDM_LGCY				= 2,
	IWL_RX_PHY_INFO_TYPE_HT					= 3,
	IWL_RX_PHY_INFO_TYPE_VHT_SU				= 4,
	IWL_RX_PHY_INFO_TYPE_VHT_MU				= 5,
	IWL_RX_PHY_INFO_TYPE_HE_SU				= 6,
	IWL_RX_PHY_INFO_TYPE_HE_MU				= 7,
	IWL_RX_PHY_INFO_TYPE_HE_TB				= 8,
	IWL_RX_PHY_INFO_TYPE_HE_MU_EXT				= 9,
	IWL_RX_PHY_INFO_TYPE_HE_TB_EXT				= 10,
पूर्ण;

/* TSF overload high dword */
क्रमागत iwl_rx_phy_data1 अणु
	/*
	 * check this first - अगर TSF overload is set,
	 * see &क्रमागत iwl_rx_phy_info_type
	 */
	IWL_RX_PHY_DATA1_INFO_TYPE_MASK				= 0xf0000000,

	/* info type: HT/VHT/HE any */
	IWL_RX_PHY_DATA1_LSIG_LEN_MASK				= 0x0fff0000,

	/* info type: HE MU/MU-EXT */
	IWL_RX_PHY_DATA1_HE_MU_SIGB_COMPRESSION			= 0x00000001,
	IWL_RX_PHY_DATA1_HE_MU_SIBG_SYM_OR_USER_NUM_MASK	= 0x0000001e,

	/* info type: HE any */
	IWL_RX_PHY_DATA1_HE_LTF_NUM_MASK			= 0x000000e0,
	IWL_RX_PHY_DATA1_HE_RU_ALLOC_SEC80			= 0x00000100,
	/* trigger encoded */
	IWL_RX_PHY_DATA1_HE_RU_ALLOC_MASK			= 0x0000fe00,

	/* info type: HE TB/TX-EXT */
	IWL_RX_PHY_DATA1_HE_TB_PILOT_TYPE			= 0x00000001,
	IWL_RX_PHY_DATA1_HE_TB_LOW_SS_MASK			= 0x0000000e,
पूर्ण;

/* goes पूर्णांकo Metadata DW 7 */
क्रमागत iwl_rx_phy_data2 अणु
	/* info type: HE MU-EXT */
	/* the a1/a2/... is what the PHY/firmware calls the values */
	IWL_RX_PHY_DATA2_HE_MU_EXT_CH1_RU0		= 0x000000ff, /* a1 */
	IWL_RX_PHY_DATA2_HE_MU_EXT_CH1_RU2		= 0x0000ff00, /* a2 */
	IWL_RX_PHY_DATA2_HE_MU_EXT_CH2_RU0		= 0x00ff0000, /* b1 */
	IWL_RX_PHY_DATA2_HE_MU_EXT_CH2_RU2		= 0xff000000, /* b2 */

	/* info type: HE TB-EXT */
	IWL_RX_PHY_DATA2_HE_TB_EXT_SPTL_REUSE1		= 0x0000000f,
	IWL_RX_PHY_DATA2_HE_TB_EXT_SPTL_REUSE2		= 0x000000f0,
	IWL_RX_PHY_DATA2_HE_TB_EXT_SPTL_REUSE3		= 0x00000f00,
	IWL_RX_PHY_DATA2_HE_TB_EXT_SPTL_REUSE4		= 0x0000f000,
पूर्ण;

/* goes पूर्णांकo Metadata DW 8 */
क्रमागत iwl_rx_phy_data3 अणु
	/* info type: HE MU-EXT */
	IWL_RX_PHY_DATA3_HE_MU_EXT_CH1_RU1		= 0x000000ff, /* c1 */
	IWL_RX_PHY_DATA3_HE_MU_EXT_CH1_RU3		= 0x0000ff00, /* c2 */
	IWL_RX_PHY_DATA3_HE_MU_EXT_CH2_RU1		= 0x00ff0000, /* d1 */
	IWL_RX_PHY_DATA3_HE_MU_EXT_CH2_RU3		= 0xff000000, /* d2 */
पूर्ण;

/* goes पूर्णांकo Metadata DW 4 high 16 bits */
क्रमागत iwl_rx_phy_data4 अणु
	/* info type: HE MU-EXT */
	IWL_RX_PHY_DATA4_HE_MU_EXT_CH1_CTR_RU			= 0x0001,
	IWL_RX_PHY_DATA4_HE_MU_EXT_CH2_CTR_RU			= 0x0002,
	IWL_RX_PHY_DATA4_HE_MU_EXT_CH1_CRC_OK			= 0x0004,
	IWL_RX_PHY_DATA4_HE_MU_EXT_CH2_CRC_OK			= 0x0008,
	IWL_RX_PHY_DATA4_HE_MU_EXT_SIGB_MCS_MASK		= 0x00f0,
	IWL_RX_PHY_DATA4_HE_MU_EXT_SIGB_DCM			= 0x0100,
	IWL_RX_PHY_DATA4_HE_MU_EXT_PREAMBLE_PUNC_TYPE_MASK	= 0x0600,
पूर्ण;

/**
 * काष्ठा iwl_rx_mpdu_desc_v1 - RX MPDU descriptor
 */
काष्ठा iwl_rx_mpdu_desc_v1 अणु
	/* DW7 - carries rss_hash only when rpa_en == 1 */
	जोड़ अणु
		/**
		 * @rss_hash: RSS hash value
		 */
		__le32 rss_hash;

		/**
		 * @phy_data2: depends on info type (see @phy_data1)
		 */
		__le32 phy_data2;
	पूर्ण;

	/* DW8 - carries filter_match only when rpa_en == 1 */
	जोड़ अणु
		/**
		 * @filter_match: filter match value
		 */
		__le32 filter_match;

		/**
		 * @phy_data3: depends on info type (see @phy_data1)
		 */
		__le32 phy_data3;
	पूर्ण;

	/* DW9 */
	/**
	 * @rate_n_flags: RX rate/flags encoding
	 */
	__le32 rate_n_flags;
	/* DW10 */
	/**
	 * @energy_a: energy chain A
	 */
	u8 energy_a;
	/**
	 * @energy_b: energy chain B
	 */
	u8 energy_b;
	/**
	 * @channel: channel number
	 */
	u8 channel;
	/**
	 * @mac_context: MAC context mask
	 */
	u8 mac_context;
	/* DW11 */
	/**
	 * @gp2_on_air_rise: GP2 समयr value on air rise (INA)
	 */
	__le32 gp2_on_air_rise;
	/* DW12 & DW13 */
	जोड़ अणु
		/**
		 * @tsf_on_air_rise:
		 * TSF value on air rise (INA), only valid अगर
		 * %IWL_RX_MPDU_PHY_TSF_OVERLOAD isn't set
		 */
		__le64 tsf_on_air_rise;

		काष्ठा अणु
			/**
			 * @phy_data0: depends on info_type, see @phy_data1
			 */
			__le32 phy_data0;
			/**
			 * @phy_data1: valid only अगर
			 * %IWL_RX_MPDU_PHY_TSF_OVERLOAD is set,
			 * see &क्रमागत iwl_rx_phy_data1.
			 */
			__le32 phy_data1;
		पूर्ण;
	पूर्ण;
पूर्ण __packed;

/**
 * काष्ठा iwl_rx_mpdu_desc_v3 - RX MPDU descriptor
 */
काष्ठा iwl_rx_mpdu_desc_v3 अणु
	/* DW7 - carries filter_match only when rpa_en == 1 */
	जोड़ अणु
		/**
		 * @filter_match: filter match value
		 */
		__le32 filter_match;

		/**
		 * @phy_data3: depends on info type (see @phy_data1)
		 */
		__le32 phy_data3;
	पूर्ण;

	/* DW8 - carries rss_hash only when rpa_en == 1 */
	जोड़ अणु
		/**
		 * @rss_hash: RSS hash value
		 */
		__le32 rss_hash;

		/**
		 * @phy_data2: depends on info type (see @phy_data1)
		 */
		__le32 phy_data2;
	पूर्ण;
	/* DW9 */
	/**
	 * @partial_hash: 31:0 ip/tcp header hash
	 *	w/o some fields (such as IP SRC addr)
	 */
	__le32 partial_hash;
	/* DW10 */
	/**
	 * @raw_xsum: raw xsum value
	 */
	__be16 raw_xsum;
	/**
	 * @reserved_xsum: reserved high bits in the raw checksum
	 */
	__le16 reserved_xsum;
	/* DW11 */
	/**
	 * @rate_n_flags: RX rate/flags encoding
	 */
	__le32 rate_n_flags;
	/* DW12 */
	/**
	 * @energy_a: energy chain A
	 */
	u8 energy_a;
	/**
	 * @energy_b: energy chain B
	 */
	u8 energy_b;
	/**
	 * @channel: channel number
	 */
	u8 channel;
	/**
	 * @mac_context: MAC context mask
	 */
	u8 mac_context;
	/* DW13 */
	/**
	 * @gp2_on_air_rise: GP2 समयr value on air rise (INA)
	 */
	__le32 gp2_on_air_rise;
	/* DW14 & DW15 */
	जोड़ अणु
		/**
		 * @tsf_on_air_rise:
		 * TSF value on air rise (INA), only valid अगर
		 * %IWL_RX_MPDU_PHY_TSF_OVERLOAD isn't set
		 */
		__le64 tsf_on_air_rise;

		काष्ठा अणु
			/**
			 * @phy_data0: depends on info_type, see @phy_data1
			 */
			__le32 phy_data0;
			/**
			 * @phy_data1: valid only अगर
			 * %IWL_RX_MPDU_PHY_TSF_OVERLOAD is set,
			 * see &क्रमागत iwl_rx_phy_data1.
			 */
			__le32 phy_data1;
		पूर्ण;
	पूर्ण;
	/* DW16 & DW17 */
	/**
	 * @reserved: reserved
	 */
	__le32 reserved[2];
पूर्ण __packed; /* RX_MPDU_RES_START_API_S_VER_3 */

/**
 * काष्ठा iwl_rx_mpdu_desc - RX MPDU descriptor
 */
काष्ठा iwl_rx_mpdu_desc अणु
	/* DW2 */
	/**
	 * @mpdu_len: MPDU length
	 */
	__le16 mpdu_len;
	/**
	 * @mac_flags1: &क्रमागत iwl_rx_mpdu_mac_flags1
	 */
	u8 mac_flags1;
	/**
	 * @mac_flags2: &क्रमागत iwl_rx_mpdu_mac_flags2
	 */
	u8 mac_flags2;
	/* DW3 */
	/**
	 * @amsdu_info: &क्रमागत iwl_rx_mpdu_amsdu_info
	 */
	u8 amsdu_info;
	/**
	 * @phy_info: &क्रमागत iwl_rx_mpdu_phy_info
	 */
	__le16 phy_info;
	/**
	 * @mac_phy_idx: MAC/PHY index
	 */
	u8 mac_phy_idx;
	/* DW4 - carries csum data only when rpa_en == 1 */
	/**
	 * @raw_csum: raw checksum (alledgedly unreliable)
	 */
	__le16 raw_csum;

	जोड़ अणु
		/**
		 * @l3l4_flags: &क्रमागत iwl_rx_l3l4_flags
		 */
		__le16 l3l4_flags;

		/**
		 * @phy_data4: depends on info type, see phy_data1
		 */
		__le16 phy_data4;
	पूर्ण;
	/* DW5 */
	/**
	 * @status: &क्रमागत iwl_rx_mpdu_status
	 */
	__le32 status;

	/* DW6 */
	/**
	 * @reorder_data: &क्रमागत iwl_rx_mpdu_reorder_data
	 */
	__le32 reorder_data;

	जोड़ अणु
		काष्ठा iwl_rx_mpdu_desc_v1 v1;
		काष्ठा iwl_rx_mpdu_desc_v3 v3;
	पूर्ण;
पूर्ण __packed; /* RX_MPDU_RES_START_API_S_VER_3 */

#घोषणा IWL_RX_DESC_SIZE_V1 दुरत्वend(काष्ठा iwl_rx_mpdu_desc, v1)

#घोषणा RX_NO_DATA_CHAIN_A_POS		0
#घोषणा RX_NO_DATA_CHAIN_A_MSK		(0xff << RX_NO_DATA_CHAIN_A_POS)
#घोषणा RX_NO_DATA_CHAIN_B_POS		8
#घोषणा RX_NO_DATA_CHAIN_B_MSK		(0xff << RX_NO_DATA_CHAIN_B_POS)
#घोषणा RX_NO_DATA_CHANNEL_POS		16
#घोषणा RX_NO_DATA_CHANNEL_MSK		(0xff << RX_NO_DATA_CHANNEL_POS)

#घोषणा RX_NO_DATA_INFO_TYPE_POS	0
#घोषणा RX_NO_DATA_INFO_TYPE_MSK	(0xff << RX_NO_DATA_INFO_TYPE_POS)
#घोषणा RX_NO_DATA_INFO_TYPE_NONE	0
#घोषणा RX_NO_DATA_INFO_TYPE_RX_ERR	1
#घोषणा RX_NO_DATA_INFO_TYPE_NDP	2
#घोषणा RX_NO_DATA_INFO_TYPE_MU_UNMATCHED	3
#घोषणा RX_NO_DATA_INFO_TYPE_HE_TB_UNMATCHED	4

#घोषणा RX_NO_DATA_INFO_ERR_POS		8
#घोषणा RX_NO_DATA_INFO_ERR_MSK		(0xff << RX_NO_DATA_INFO_ERR_POS)
#घोषणा RX_NO_DATA_INFO_ERR_NONE	0
#घोषणा RX_NO_DATA_INFO_ERR_BAD_PLCP	1
#घोषणा RX_NO_DATA_INFO_ERR_UNSUPPORTED_RATE	2
#घोषणा RX_NO_DATA_INFO_ERR_NO_DELIM		3
#घोषणा RX_NO_DATA_INFO_ERR_BAD_MAC_HDR	4

#घोषणा RX_NO_DATA_FRAME_TIME_POS	0
#घोषणा RX_NO_DATA_FRAME_TIME_MSK	(0xfffff << RX_NO_DATA_FRAME_TIME_POS)

#घोषणा RX_NO_DATA_RX_VEC0_HE_NSTS_MSK	0x03800000
#घोषणा RX_NO_DATA_RX_VEC0_VHT_NSTS_MSK	0x38000000

/**
 * काष्ठा iwl_rx_no_data - RX no data descriptor
 * @info: 7:0 frame type, 15:8 RX error type
 * @rssi: 7:0 energy chain-A,
 *	15:8 chain-B, measured at FINA समय (FINA_ENERGY), 16:23 channel
 * @on_air_rise_समय: GP2 during on air rise
 * @fr_समय: frame समय
 * @rate: rate/mcs of frame
 * @phy_info: &क्रमागत iwl_rx_phy_data0 and &क्रमागत iwl_rx_phy_info_type
 * @rx_vec: DW-12:9 raw RX vectors from DSP according to modulation type.
 *	क्रम VHT: OFDM_RX_VECTOR_SIGA1_OUT, OFDM_RX_VECTOR_SIGA2_OUT
 *	क्रम HE: OFDM_RX_VECTOR_HE_SIGA1_OUT, OFDM_RX_VECTOR_HE_SIGA2_OUT
 */
काष्ठा iwl_rx_no_data अणु
	__le32 info;
	__le32 rssi;
	__le32 on_air_rise_समय;
	__le32 fr_समय;
	__le32 rate;
	__le32 phy_info[2];
	__le32 rx_vec[2];
पूर्ण __packed; /* RX_NO_DATA_NTFY_API_S_VER_1 */

काष्ठा iwl_frame_release अणु
	u8 baid;
	u8 reserved;
	__le16 nssn;
पूर्ण;

/**
 * क्रमागत iwl_bar_frame_release_sta_tid - STA/TID inक्रमmation क्रम BAR release
 * @IWL_BAR_FRAME_RELEASE_TID_MASK: TID mask
 * @IWL_BAR_FRAME_RELEASE_STA_MASK: STA mask
 */
क्रमागत iwl_bar_frame_release_sta_tid अणु
	IWL_BAR_FRAME_RELEASE_TID_MASK = 0x0000000f,
	IWL_BAR_FRAME_RELEASE_STA_MASK = 0x000001f0,
पूर्ण;

/**
 * क्रमागत iwl_bar_frame_release_ba_info - BA inक्रमmation क्रम BAR release
 * @IWL_BAR_FRAME_RELEASE_NSSN_MASK: NSSN mask
 * @IWL_BAR_FRAME_RELEASE_SN_MASK: SN mask (ignored by driver)
 * @IWL_BAR_FRAME_RELEASE_BAID_MASK: BAID mask
 */
क्रमागत iwl_bar_frame_release_ba_info अणु
	IWL_BAR_FRAME_RELEASE_NSSN_MASK	= 0x00000fff,
	IWL_BAR_FRAME_RELEASE_SN_MASK	= 0x00fff000,
	IWL_BAR_FRAME_RELEASE_BAID_MASK	= 0x3f000000,
पूर्ण;

/**
 * काष्ठा iwl_bar_frame_release - frame release from BAR info
 * @sta_tid: STA & TID inक्रमmation, see &क्रमागत iwl_bar_frame_release_sta_tid.
 * @ba_info: BA inक्रमmation, see &क्रमागत iwl_bar_frame_release_ba_info.
 */
काष्ठा iwl_bar_frame_release अणु
	__le32 sta_tid;
	__le32 ba_info;
पूर्ण __packed; /* RX_BAR_TO_FRAME_RELEASE_API_S_VER_1 */

क्रमागत iwl_rss_hash_func_en अणु
	IWL_RSS_HASH_TYPE_IPV4_TCP,
	IWL_RSS_HASH_TYPE_IPV4_UDP,
	IWL_RSS_HASH_TYPE_IPV4_PAYLOAD,
	IWL_RSS_HASH_TYPE_IPV6_TCP,
	IWL_RSS_HASH_TYPE_IPV6_UDP,
	IWL_RSS_HASH_TYPE_IPV6_PAYLOAD,
पूर्ण;

#घोषणा IWL_RSS_HASH_KEY_CNT 10
#घोषणा IWL_RSS_INसूचीECTION_TABLE_SIZE 128
#घोषणा IWL_RSS_ENABLE 1

/**
 * काष्ठा iwl_rss_config_cmd - RSS (Receive Side Scaling) configuration
 *
 * @flags: 1 - enable, 0 - disable
 * @hash_mask: Type of RSS to use. Values are from %iwl_rss_hash_func_en
 * @reserved: reserved
 * @secret_key: 320 bit input of अक्रमom key configuration from driver
 * @indirection_table: indirection table
 */
काष्ठा iwl_rss_config_cmd अणु
	__le32 flags;
	u8 hash_mask;
	u8 reserved[3];
	__le32 secret_key[IWL_RSS_HASH_KEY_CNT];
	u8 indirection_table[IWL_RSS_INसूचीECTION_TABLE_SIZE];
पूर्ण __packed; /* RSS_CONFIG_CMD_API_S_VER_1 */

#घोषणा IWL_MULTI_QUEUE_SYNC_SENDER_POS 0
#घोषणा IWL_MULTI_QUEUE_SYNC_SENDER_MSK 0xf

/**
 * काष्ठा iwl_rxq_sync_cmd - RXQ notअगरication trigger
 *
 * @flags: flags of the notअगरication. bit 0:3 are the sender queue
 * @rxq_mask: rx queues to send the notअगरication on
 * @count: number of bytes in payload, should be DWORD aligned
 * @payload: data to send to rx queues
 */
काष्ठा iwl_rxq_sync_cmd अणु
	__le32 flags;
	__le32 rxq_mask;
	__le32 count;
	u8 payload[];
पूर्ण __packed; /* MULTI_QUEUE_DRV_SYNC_HDR_CMD_API_S_VER_1 */

/**
 * काष्ठा iwl_rxq_sync_notअगरication - Notअगरication triggered by RXQ
 * sync command
 *
 * @count: number of bytes in payload
 * @payload: data to send to rx queues
 */
काष्ठा iwl_rxq_sync_notअगरication अणु
	__le32 count;
	u8 payload[];
पूर्ण __packed; /* MULTI_QUEUE_DRV_SYNC_HDR_CMD_API_S_VER_1 */

/**
 * क्रमागत iwl_mvm_pm_event - type of station PM event
 * @IWL_MVM_PM_EVENT_AWAKE: station woke up
 * @IWL_MVM_PM_EVENT_ASLEEP: station went to sleep
 * @IWL_MVM_PM_EVENT_UAPSD: station sent uAPSD trigger
 * @IWL_MVM_PM_EVENT_PS_POLL: station sent PS-Poll
 */
क्रमागत iwl_mvm_pm_event अणु
	IWL_MVM_PM_EVENT_AWAKE,
	IWL_MVM_PM_EVENT_ASLEEP,
	IWL_MVM_PM_EVENT_UAPSD,
	IWL_MVM_PM_EVENT_PS_POLL,
पूर्ण; /* PEER_PM_NTFY_API_E_VER_1 */

/**
 * काष्ठा iwl_mvm_pm_state_notअगरication - station PM state notअगरication
 * @sta_id: station ID of the station changing state
 * @type: the new घातersave state, see &क्रमागत iwl_mvm_pm_event
 */
काष्ठा iwl_mvm_pm_state_notअगरication अणु
	u8 sta_id;
	u8 type;
	/* निजी: */
	__le16 reserved;
पूर्ण __packed; /* PEER_PM_NTFY_API_S_VER_1 */

#घोषणा BA_WINDOW_STREAMS_MAX		16
#घोषणा BA_WINDOW_STATUS_TID_MSK	0x000F
#घोषणा BA_WINDOW_STATUS_STA_ID_POS	4
#घोषणा BA_WINDOW_STATUS_STA_ID_MSK	0x01F0
#घोषणा BA_WINDOW_STATUS_VALID_MSK	BIT(9)

/**
 * काष्ठा iwl_ba_winकरोw_status_notअगर - reordering winकरोw's status notअगरication
 * @biपंचांगap: biपंचांगap of received frames [start_seq_num + 0]..[start_seq_num + 63]
 * @ra_tid: bit 3:0 - TID, bit 8:4 - STA_ID, bit 9 - valid
 * @start_seq_num: the start sequence number of the biपंचांगap
 * @mpdu_rx_count: the number of received MPDUs since entering D0i3
 */
काष्ठा iwl_ba_winकरोw_status_notअगर अणु
	__le64 biपंचांगap[BA_WINDOW_STREAMS_MAX];
	__le16 ra_tid[BA_WINDOW_STREAMS_MAX];
	__le32 start_seq_num[BA_WINDOW_STREAMS_MAX];
	__le16 mpdu_rx_count[BA_WINDOW_STREAMS_MAX];
पूर्ण __packed; /* BA_WINDOW_STATUS_NTFY_API_S_VER_1 */

/**
 * काष्ठा iwl_rfh_queue_config - RX queue configuration
 * @q_num: Q num
 * @enable: enable queue
 * @reserved: alignment
 * @urbd_stts_wrptr: DMA address of urbd_stts_wrptr
 * @fr_bd_cb: DMA address of मुक्तRB table
 * @ur_bd_cb: DMA address of used RB table
 * @fr_bd_wid: Initial index of the मुक्त table
 */
काष्ठा iwl_rfh_queue_data अणु
	u8 q_num;
	u8 enable;
	__le16 reserved;
	__le64 urbd_stts_wrptr;
	__le64 fr_bd_cb;
	__le64 ur_bd_cb;
	__le32 fr_bd_wid;
पूर्ण __packed; /* RFH_QUEUE_CONFIG_S_VER_1 */

/**
 * काष्ठा iwl_rfh_queue_config - RX queue configuration
 * @num_queues: number of queues configured
 * @reserved: alignment
 * @data: DMA addresses per-queue
 */
काष्ठा iwl_rfh_queue_config अणु
	u8 num_queues;
	u8 reserved[3];
	काष्ठा iwl_rfh_queue_data data[];
पूर्ण __packed; /* RFH_QUEUE_CONFIG_API_S_VER_1 */

#पूर्ण_अगर /* __iwl_fw_api_rx_h__ */
