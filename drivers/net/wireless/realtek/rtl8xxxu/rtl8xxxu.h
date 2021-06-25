<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014 - 2017 Jes Sorensen <Jes.Sorensen@gmail.com>
 *
 * Register definitions taken from original Realtek rtl8723au driver
 */

#समावेश <यंत्र/byteorder.h>

#घोषणा RTL8XXXU_DEBUG_REG_WRITE	0x01
#घोषणा RTL8XXXU_DEBUG_REG_READ		0x02
#घोषणा RTL8XXXU_DEBUG_RFREG_WRITE	0x04
#घोषणा RTL8XXXU_DEBUG_RFREG_READ	0x08
#घोषणा RTL8XXXU_DEBUG_CHANNEL		0x10
#घोषणा RTL8XXXU_DEBUG_TX		0x20
#घोषणा RTL8XXXU_DEBUG_TX_DUMP		0x40
#घोषणा RTL8XXXU_DEBUG_RX		0x80
#घोषणा RTL8XXXU_DEBUG_RX_DUMP		0x100
#घोषणा RTL8XXXU_DEBUG_USB		0x200
#घोषणा RTL8XXXU_DEBUG_KEY		0x400
#घोषणा RTL8XXXU_DEBUG_H2C		0x800
#घोषणा RTL8XXXU_DEBUG_ACTION		0x1000
#घोषणा RTL8XXXU_DEBUG_EFUSE		0x2000
#घोषणा RTL8XXXU_DEBUG_INTERRUPT	0x4000

#घोषणा RTW_USB_CONTROL_MSG_TIMEOUT	500
#घोषणा RTL8XXXU_MAX_REG_POLL		500
#घोषणा	USB_INTR_CONTENT_LENGTH		56

#घोषणा RTL8XXXU_OUT_ENDPOINTS		4

#घोषणा REALTEK_USB_READ		0xc0
#घोषणा REALTEK_USB_WRITE		0x40
#घोषणा REALTEK_USB_CMD_REQ		0x05
#घोषणा REALTEK_USB_CMD_IDX		0x00

#घोषणा TX_TOTAL_PAGE_NUM		0xf8
#घोषणा TX_TOTAL_PAGE_NUM_8192E		0xf3
#घोषणा TX_TOTAL_PAGE_NUM_8723B		0xf7
/* (HPQ + LPQ + NPQ + PUBQ) = TX_TOTAL_PAGE_NUM */
#घोषणा TX_PAGE_NUM_PUBQ		0xe7
#घोषणा TX_PAGE_NUM_HI_PQ		0x0c
#घोषणा TX_PAGE_NUM_LO_PQ		0x02
#घोषणा TX_PAGE_NUM_NORM_PQ		0x02

#घोषणा TX_PAGE_NUM_PUBQ_8192E		0xe7
#घोषणा TX_PAGE_NUM_HI_PQ_8192E		0x08
#घोषणा TX_PAGE_NUM_LO_PQ_8192E		0x0c
#घोषणा TX_PAGE_NUM_NORM_PQ_8192E	0x00

#घोषणा TX_PAGE_NUM_PUBQ_8723B		0xe7
#घोषणा TX_PAGE_NUM_HI_PQ_8723B		0x0c
#घोषणा TX_PAGE_NUM_LO_PQ_8723B		0x02
#घोषणा TX_PAGE_NUM_NORM_PQ_8723B	0x02

#घोषणा RTL_FW_PAGE_SIZE		4096
#घोषणा RTL8XXXU_FIRMWARE_POLL_MAX	1000

#घोषणा RTL8723A_CHANNEL_GROUPS		3
#घोषणा RTL8723A_MAX_RF_PATHS		2
#घोषणा RTL8723B_CHANNEL_GROUPS		6
#घोषणा RTL8723B_TX_COUNT		4
#घोषणा RTL8723B_MAX_RF_PATHS		4
#घोषणा RTL8XXXU_MAX_CHANNEL_GROUPS	6
#घोषणा RF6052_MAX_TX_PWR		0x3f

#घोषणा EFUSE_MAP_LEN			512
#घोषणा EFUSE_MAX_SECTION_8723A		64
#घोषणा EFUSE_REAL_CONTENT_LEN_8723A	512
#घोषणा EFUSE_BT_MAP_LEN_8723A		1024
#घोषणा EFUSE_MAX_WORD_UNIT		4

क्रमागत rtl8xxxu_rtl_chip अणु
	RTL8192S = 0x81920,
	RTL8191S = 0x81910,
	RTL8192C = 0x8192c,
	RTL8191C = 0x8191c,
	RTL8188C = 0x8188c,
	RTL8188R = 0x81889,
	RTL8192D = 0x8192d,
	RTL8723A = 0x8723a,
	RTL8188E = 0x8188e,
	RTL8812  = 0x88120,
	RTL8821  = 0x88210,
	RTL8192E = 0x8192e,
	RTL8191E = 0x8191e,
	RTL8723B = 0x8723b,
	RTL8814A = 0x8814a,
	RTL8881A = 0x8881a,
	RTL8821B = 0x8821b,
	RTL8822B = 0x8822b,
	RTL8703B = 0x8703b,
	RTL8195A = 0x8195a,
	RTL8188F = 0x8188f
पूर्ण;

क्रमागत rtl8xxxu_rx_type अणु
	RX_TYPE_DATA_PKT = 0,
	RX_TYPE_C2H = 1,
	RX_TYPE_ERROR = -1
पूर्ण;

काष्ठा rtl8xxxu_rxdesc16 अणु
#अगर_घोषित __LITTLE_ENDIAN
	u32 pktlen:14;
	u32 crc32:1;
	u32 icverr:1;
	u32 drvinfo_sz:4;
	u32 security:3;
	u32 qos:1;
	u32 shअगरt:2;
	u32 phy_stats:1;
	u32 swdec:1;
	u32 ls:1;
	u32 fs:1;
	u32 eor:1;
	u32 own:1;

	u32 macid:5;
	u32 tid:4;
	u32 hwrsvd:4;
	u32 amsdu:1;
	u32 paggr:1;
	u32 faggr:1;
	u32 a1fit:4;
	u32 a2fit:4;
	u32 pam:1;
	u32 pwr:1;
	u32 md:1;
	u32 mf:1;
	u32 type:2;
	u32 mc:1;
	u32 bc:1;

	u32 seq:12;
	u32 frag:4;
	u32 pkt_cnt:8;
	u32 reserved:6;
	u32 nextind:1;
	u32 reserved0:1;

	u32 rxmcs:6;
	u32 rxht:1;
	u32 gf:1;
	u32 splcp:1;
	u32 bw:1;
	u32 htc:1;
	u32 eosp:1;
	u32 bssidfit:2;
	u32 reserved1:16;
	u32 unicastwake:1;
	u32 magicwake:1;

	u32 pattern0match:1;
	u32 pattern1match:1;
	u32 pattern2match:1;
	u32 pattern3match:1;
	u32 pattern4match:1;
	u32 pattern5match:1;
	u32 pattern6match:1;
	u32 pattern7match:1;
	u32 pattern8match:1;
	u32 pattern9match:1;
	u32 patternamatch:1;
	u32 patternbmatch:1;
	u32 patterncmatch:1;
	u32 reserved2:19;
#अन्यथा
	u32 own:1;
	u32 eor:1;
	u32 fs:1;
	u32 ls:1;
	u32 swdec:1;
	u32 phy_stats:1;
	u32 shअगरt:2;
	u32 qos:1;
	u32 security:3;
	u32 drvinfo_sz:4;
	u32 icverr:1;
	u32 crc32:1;
	u32 pktlen:14;

	u32 bc:1;
	u32 mc:1;
	u32 type:2;
	u32 mf:1;
	u32 md:1;
	u32 pwr:1;
	u32 pam:1;
	u32 a2fit:4;
	u32 a1fit:4;
	u32 faggr:1;
	u32 paggr:1;
	u32 amsdu:1;
	u32 hwrsvd:4;
	u32 tid:4;
	u32 macid:5;

	u32 reserved0:1;
	u32 nextind:1;
	u32 reserved:6;
	u32 pkt_cnt:8;
	u32 frag:4;
	u32 seq:12;

	u32 magicwake:1;
	u32 unicastwake:1;
	u32 reserved1:16;
	u32 bssidfit:2;
	u32 eosp:1;
	u32 htc:1;
	u32 bw:1;
	u32 splcp:1;
	u32 gf:1;
	u32 rxht:1;
	u32 rxmcs:6;

	u32 reserved2:19;
	u32 patterncmatch:1;
	u32 patternbmatch:1;
	u32 patternamatch:1;
	u32 pattern9match:1;
	u32 pattern8match:1;
	u32 pattern7match:1;
	u32 pattern6match:1;
	u32 pattern5match:1;
	u32 pattern4match:1;
	u32 pattern3match:1;
	u32 pattern2match:1;
	u32 pattern1match:1;
	u32 pattern0match:1;
#पूर्ण_अगर
	u32 tsfl;
#अगर 0
	u32 bassn:12;
	u32 bavld:1;
	u32 reserved3:19;
#पूर्ण_अगर
पूर्ण;

काष्ठा rtl8xxxu_rxdesc24 अणु
#अगर_घोषित __LITTLE_ENDIAN
	u32 pktlen:14;
	u32 crc32:1;
	u32 icverr:1;
	u32 drvinfo_sz:4;
	u32 security:3;
	u32 qos:1;
	u32 shअगरt:2;
	u32 phy_stats:1;
	u32 swdec:1;
	u32 ls:1;
	u32 fs:1;
	u32 eor:1;
	u32 own:1;

	u32 macid:7;
	u32 dummy1_0:1;
	u32 tid:4;
	u32 dummy1_1:1;
	u32 amsdu:1;
	u32 rxid_match:1;
	u32 paggr:1;
	u32 a1fit:4;	/* 16 */
	u32 chkerr:1;
	u32 ipver:1;
	u32 tcpudp:1;
	u32 chkvld:1;
	u32 pam:1;
	u32 pwr:1;
	u32 more_data:1;
	u32 more_frag:1;
	u32 type:2;
	u32 mc:1;
	u32 bc:1;

	u32 seq:12;
	u32 frag:4;
	u32 rx_is_qos:1;	/* 16 */
	u32 dummy2_0:1;
	u32 wlanhd_iv_len:6;
	u32 dummy2_1:4;
	u32 rpt_sel:1;
	u32 dummy2_2:3;

	u32 rxmcs:7;
	u32 dummy3_0:3;
	u32 htc:1;
	u32 eosp:1;
	u32 bssidfit:2;
	u32 dummy3_1:2;
	u32 usb_agg_pktnum:8;	/* 16 */
	u32 dummy3_2:5;
	u32 pattern_match:1;
	u32 unicast_match:1;
	u32 magic_match:1;

	u32 splcp:1;
	u32 ldcp:1;
	u32 stbc:1;
	u32 dummy4_0:1;
	u32 bw:2;
	u32 dummy4_1:26;
#अन्यथा
	u32 own:1;
	u32 eor:1;
	u32 fs:1;
	u32 ls:1;
	u32 swdec:1;
	u32 phy_stats:1;
	u32 shअगरt:2;
	u32 qos:1;
	u32 security:3;
	u32 drvinfo_sz:4;
	u32 icverr:1;
	u32 crc32:1;
	u32 pktlen:14;

	u32 bc:1;
	u32 mc:1;
	u32 type:2;
	u32 mf:1;
	u32 md:1;
	u32 pwr:1;
	u32 pam:1;
	u32 a2fit:4;
	u32 a1fit:4;
	u32 faggr:1;
	u32 paggr:1;
	u32 amsdu:1;
	u32 hwrsvd:4;
	u32 tid:4;
	u32 macid:5;

	u32 dummy2_2:3;
	u32 rpt_sel:1;
	u32 dummy2_1:4;
	u32 wlanhd_iv_len:6;
	u32 dummy2_0:1;
	u32 rx_is_qos:1;
	u32 frag:4;		/* 16 */
	u32 seq:12;

	u32 magic_match:1;
	u32 unicast_match:1;
	u32 pattern_match:1;
	u32 dummy3_2:5;
	u32 usb_agg_pktnum:8;
	u32 dummy3_1:2;		/* 16 */
	u32 bssidfit:2;
	u32 eosp:1;
	u32 htc:1;
	u32 dummy3_0:3;
	u32 rxmcs:7;

	u32 dumm4_1:26;
	u32 bw:2;
	u32 dummy4_0:1;
	u32 stbc:1;
	u32 ldcp:1;
	u32 splcp:1;
#पूर्ण_अगर
	u32 tsfl;
पूर्ण;

काष्ठा rtl8xxxu_txdesc32 अणु
	__le16 pkt_size;
	u8 pkt_offset;
	u8 txdw0;
	__le32 txdw1;
	__le32 txdw2;
	__le32 txdw3;
	__le32 txdw4;
	__le32 txdw5;
	__le32 txdw6;
	__le16 csum;
	__le16 txdw7;
पूर्ण;

काष्ठा rtl8xxxu_txdesc40 अणु
	__le16 pkt_size;
	u8 pkt_offset;
	u8 txdw0;
	__le32 txdw1;
	__le32 txdw2;
	__le32 txdw3;
	__le32 txdw4;
	__le32 txdw5;
	__le32 txdw6;
	__le16 csum;
	__le16 txdw7;
	__le32 txdw8;
	__le32 txdw9;
पूर्ण;

/*  CCK Rates, TxHT = 0 */
#घोषणा DESC_RATE_1M			0x00
#घोषणा DESC_RATE_2M			0x01
#घोषणा DESC_RATE_5_5M			0x02
#घोषणा DESC_RATE_11M			0x03

/*  OFDM Rates, TxHT = 0 */
#घोषणा DESC_RATE_6M			0x04
#घोषणा DESC_RATE_9M			0x05
#घोषणा DESC_RATE_12M			0x06
#घोषणा DESC_RATE_18M			0x07
#घोषणा DESC_RATE_24M			0x08
#घोषणा DESC_RATE_36M			0x09
#घोषणा DESC_RATE_48M			0x0a
#घोषणा DESC_RATE_54M			0x0b

/*  MCS Rates, TxHT = 1 */
#घोषणा DESC_RATE_MCS0			0x0c
#घोषणा DESC_RATE_MCS1			0x0d
#घोषणा DESC_RATE_MCS2			0x0e
#घोषणा DESC_RATE_MCS3			0x0f
#घोषणा DESC_RATE_MCS4			0x10
#घोषणा DESC_RATE_MCS5			0x11
#घोषणा DESC_RATE_MCS6			0x12
#घोषणा DESC_RATE_MCS7			0x13
#घोषणा DESC_RATE_MCS8			0x14
#घोषणा DESC_RATE_MCS9			0x15
#घोषणा DESC_RATE_MCS10			0x16
#घोषणा DESC_RATE_MCS11			0x17
#घोषणा DESC_RATE_MCS12			0x18
#घोषणा DESC_RATE_MCS13			0x19
#घोषणा DESC_RATE_MCS14			0x1a
#घोषणा DESC_RATE_MCS15			0x1b
#घोषणा DESC_RATE_MCS15_SG		0x1c
#घोषणा DESC_RATE_MCS32			0x20

#घोषणा TXDESC_OFFSET_SZ		0
#घोषणा TXDESC_OFFSET_SHT		16
#अगर 0
#घोषणा TXDESC_BMC			BIT(24)
#घोषणा TXDESC_LSG			BIT(26)
#घोषणा TXDESC_FSG			BIT(27)
#घोषणा TXDESC_OWN			BIT(31)
#अन्यथा
#घोषणा TXDESC_BROADMULTICAST		BIT(0)
#घोषणा TXDESC_HTC			BIT(1)
#घोषणा TXDESC_LAST_SEGMENT		BIT(2)
#घोषणा TXDESC_FIRST_SEGMENT		BIT(3)
#घोषणा TXDESC_LINIP			BIT(4)
#घोषणा TXDESC_NO_ACM			BIT(5)
#घोषणा TXDESC_GF			BIT(6)
#घोषणा TXDESC_OWN			BIT(7)
#पूर्ण_अगर

/* Word 1 */
/*
 * Bits 0-7 dअगरfer dependent on chip generation. For 8723au bits 5/6 are
 * aggregation enable and अवरोध respectively. For 8723bu, bits 0-7 are macid.
 */
#घोषणा TXDESC_PKT_OFFSET_SZ		0
#घोषणा TXDESC32_AGG_ENABLE		BIT(5)
#घोषणा TXDESC32_AGG_BREAK		BIT(6)
#घोषणा TXDESC40_MACID_SHIFT		0
#घोषणा TXDESC40_MACID_MASK		0x00f0
#घोषणा TXDESC_QUEUE_SHIFT		8
#घोषणा TXDESC_QUEUE_MASK		0x1f00
#घोषणा TXDESC_QUEUE_BK			0x2
#घोषणा TXDESC_QUEUE_BE			0x0
#घोषणा TXDESC_QUEUE_VI			0x5
#घोषणा TXDESC_QUEUE_VO			0x7
#घोषणा TXDESC_QUEUE_BEACON		0x10
#घोषणा TXDESC_QUEUE_HIGH		0x11
#घोषणा TXDESC_QUEUE_MGNT		0x12
#घोषणा TXDESC_QUEUE_CMD		0x13
#घोषणा TXDESC_QUEUE_MAX		(TXDESC_QUEUE_CMD + 1)
#घोषणा TXDESC40_RDG_NAV_EXT		BIT(13)
#घोषणा TXDESC40_LSIG_TXOP_ENABLE	BIT(14)
#घोषणा TXDESC40_PIFS			BIT(15)

#घोषणा DESC_RATE_ID_SHIFT		16
#घोषणा DESC_RATE_ID_MASK		0xf
#घोषणा TXDESC_NAVUSEHDR		BIT(20)
#घोषणा TXDESC_SEC_RC4			0x00400000
#घोषणा TXDESC_SEC_AES			0x00c00000
#घोषणा TXDESC_PKT_OFFSET_SHIFT		26
#घोषणा TXDESC_AGG_EN			BIT(29)
#घोषणा TXDESC_HWPC			BIT(31)

/* Word 2 */
#घोषणा TXDESC40_PAID_SHIFT		0
#घोषणा TXDESC40_PAID_MASK		0x1ff
#घोषणा TXDESC40_CCA_RTS_SHIFT		10
#घोषणा TXDESC40_CCA_RTS_MASK		0xc00
#घोषणा TXDESC40_AGG_ENABLE		BIT(12)
#घोषणा TXDESC40_RDG_ENABLE		BIT(13)
#घोषणा TXDESC40_AGG_BREAK		BIT(16)
#घोषणा TXDESC40_MORE_FRAG		BIT(17)
#घोषणा TXDESC40_RAW			BIT(18)
#घोषणा TXDESC32_ACK_REPORT		BIT(19)
#घोषणा TXDESC40_SPE_RPT		BIT(19)
#घोषणा TXDESC_AMPDU_DENSITY_SHIFT	20
#घोषणा TXDESC40_BT_INT			BIT(23)
#घोषणा TXDESC40_GID_SHIFT		24

/* Word 3 */
#घोषणा TXDESC40_USE_DRIVER_RATE	BIT(8)
#घोषणा TXDESC40_CTS_SELF_ENABLE	BIT(11)
#घोषणा TXDESC40_RTS_CTS_ENABLE		BIT(12)
#घोषणा TXDESC40_HW_RTS_ENABLE		BIT(13)
#घोषणा TXDESC32_SEQ_SHIFT		16
#घोषणा TXDESC32_SEQ_MASK		0x0fff0000

/* Word 4 */
#घोषणा TXDESC32_RTS_RATE_SHIFT		0
#घोषणा TXDESC32_RTS_RATE_MASK		0x3f
#घोषणा TXDESC32_QOS			BIT(6)
#घोषणा TXDESC32_HW_SEQ_ENABLE		BIT(7)
#घोषणा TXDESC32_USE_DRIVER_RATE	BIT(8)
#घोषणा TXDESC_DISABLE_DATA_FB		BIT(10)
#घोषणा TXDESC32_CTS_SELF_ENABLE	BIT(11)
#घोषणा TXDESC32_RTS_CTS_ENABLE		BIT(12)
#घोषणा TXDESC32_HW_RTS_ENABLE		BIT(13)
#घोषणा TXDESC_PRIME_CH_OFF_LOWER	BIT(20)
#घोषणा TXDESC_PRIME_CH_OFF_UPPER	BIT(21)
#घोषणा TXDESC32_SHORT_PREAMBLE		BIT(24)
#घोषणा TXDESC_DATA_BW			BIT(25)
#घोषणा TXDESC_RTS_DATA_BW		BIT(27)
#घोषणा TXDESC_RTS_PRIME_CH_OFF_LOWER	BIT(28)
#घोषणा TXDESC_RTS_PRIME_CH_OFF_UPPER	BIT(29)
#घोषणा TXDESC40_DATA_RATE_FB_SHIFT	8
#घोषणा TXDESC40_DATA_RATE_FB_MASK	0x00001f00
#घोषणा TXDESC40_RETRY_LIMIT_ENABLE	BIT(17)
#घोषणा TXDESC40_RETRY_LIMIT_SHIFT	18
#घोषणा TXDESC40_RETRY_LIMIT_MASK	0x00fc0000
#घोषणा TXDESC40_RTS_RATE_SHIFT		24
#घोषणा TXDESC40_RTS_RATE_MASK		0x3f000000

/* Word 5 */
#घोषणा TXDESC40_SHORT_PREAMBLE		BIT(4)
#घोषणा TXDESC32_SHORT_GI		BIT(6)
#घोषणा TXDESC_CCX_TAG			BIT(7)
#घोषणा TXDESC32_RETRY_LIMIT_ENABLE	BIT(17)
#घोषणा TXDESC32_RETRY_LIMIT_SHIFT	18
#घोषणा TXDESC32_RETRY_LIMIT_MASK	0x00fc0000

/* Word 6 */
#घोषणा TXDESC_MAX_AGG_SHIFT		11

/* Word 8 */
#घोषणा TXDESC40_HW_SEQ_ENABLE		BIT(15)

/* Word 9 */
#घोषणा TXDESC40_SEQ_SHIFT		12
#घोषणा TXDESC40_SEQ_MASK		0x00fff000

काष्ठा phy_rx_agc_info अणु
#अगर_घोषित __LITTLE_ENDIAN
	u8	gain:7, trsw:1;
#अन्यथा
	u8	trsw:1, gain:7;
#पूर्ण_अगर
पूर्ण;

काष्ठा rtl8723au_phy_stats अणु
	काष्ठा phy_rx_agc_info path_agc[RTL8723A_MAX_RF_PATHS];
	u8	ch_corr[RTL8723A_MAX_RF_PATHS];
	u8	cck_sig_qual_ofdm_pwdb_all;
	u8	cck_agc_rpt_ofdm_cfosho_a;
	u8	cck_rpt_b_ofdm_cfosho_b;
	u8	reserved_1;
	u8	noise_घातer_db_msb;
	u8	path_cfotail[RTL8723A_MAX_RF_PATHS];
	u8	pcts_mask[RTL8723A_MAX_RF_PATHS];
	s8	stream_rxevm[RTL8723A_MAX_RF_PATHS];
	u8	path_rxsnr[RTL8723A_MAX_RF_PATHS];
	u8	noise_घातer_db_lsb;
	u8	reserved_2[3];
	u8	stream_csi[RTL8723A_MAX_RF_PATHS];
	u8	stream_target_csi[RTL8723A_MAX_RF_PATHS];
	s8	sig_evm;
	u8	reserved_3;

#अगर_घोषित __LITTLE_ENDIAN
	u8	antsel_rx_keep_2:1;	/* ex_पूर्णांकf_flg:1; */
	u8	sgi_en:1;
	u8	rxsc:2;
	u8	idle_दीर्घ:1;
	u8	r_ant_train_en:1;
	u8	antenna_select_b:1;
	u8	antenna_select:1;
#अन्यथा	/*  _BIG_ENDIAN_ */
	u8	antenna_select:1;
	u8	antenna_select_b:1;
	u8	r_ant_train_en:1;
	u8	idle_दीर्घ:1;
	u8	rxsc:2;
	u8	sgi_en:1;
	u8	antsel_rx_keep_2:1;	/* ex_पूर्णांकf_flg:1; */
#पूर्ण_अगर
पूर्ण;

/*
 * Regs to backup
 */
#घोषणा RTL8XXXU_ADDA_REGS		16
#घोषणा RTL8XXXU_MAC_REGS		4
#घोषणा RTL8XXXU_BB_REGS		9

काष्ठा rtl8xxxu_firmware_header अणु
	__le16	signature;		/*  92C0: test chip; 92C,
					    88C0: test chip;
					    88C1: MP A-cut;
					    92C1: MP A-cut */
	u8	category;		/*  AP/NIC and USB/PCI */
	u8	function;

	__le16	major_version;		/*  FW Version */
	u8	minor_version;		/*  FW Subversion, शेष 0x00 */
	u8	reserved1;

	u8	month;			/*  Release समय Month field */
	u8	date;			/*  Release समय Date field */
	u8	hour;			/*  Release समय Hour field */
	u8	minute;			/*  Release समय Minute field */

	__le16	ramcodesize;		/*  Size of RAM code */
	u16	reserved2;

	__le32	svn_idx;		/*  SVN entry index */
	u32	reserved3;

	u32	reserved4;
	u32	reserved5;

	u8	data[];
पूर्ण;

/*
 * 8723au/8192cu/8188ru required base घातer index offset tables.
 */
काष्ठा rtl8xxxu_घातer_base अणु
	u32 reg_0e00;
	u32 reg_0e04;
	u32 reg_0e08;
	u32 reg_086c;

	u32 reg_0e10;
	u32 reg_0e14;
	u32 reg_0e18;
	u32 reg_0e1c;

	u32 reg_0830;
	u32 reg_0834;
	u32 reg_0838;
	u32 reg_086c_2;

	u32 reg_083c;
	u32 reg_0848;
	u32 reg_084c;
	u32 reg_0868;
पूर्ण;

/*
 * The 8723au has 3 channel groups: 1-3, 4-9, and 10-14
 */
काष्ठा rtl8723au_idx अणु
#अगर_घोषित __LITTLE_ENDIAN
	पूर्णांक	a:4;
	पूर्णांक	b:4;
#अन्यथा
	पूर्णांक	b:4;
	पूर्णांक	a:4;
#पूर्ण_अगर
पूर्ण __attribute__((packed));

काष्ठा rtl8723au_efuse अणु
	__le16 rtl_id;
	u8 res0[0xe];
	u8 cck_tx_घातer_index_A[3];	/* 0x10 */
	u8 cck_tx_घातer_index_B[3];
	u8 ht40_1s_tx_घातer_index_A[3];	/* 0x16 */
	u8 ht40_1s_tx_घातer_index_B[3];
	/*
	 * The following entries are half-bytes split as:
	 * bits 0-3: path A, bits 4-7: path B, all values 4 bits चिन्हित
	 */
	काष्ठा rtl8723au_idx ht20_tx_घातer_index_dअगरf[3];
	काष्ठा rtl8723au_idx ofdm_tx_घातer_index_dअगरf[3];
	काष्ठा rtl8723au_idx ht40_max_घातer_offset[3];
	काष्ठा rtl8723au_idx ht20_max_घातer_offset[3];
	u8 channel_plan;		/* 0x28 */
	u8 tssi_a;
	u8 thermal_meter;
	u8 rf_regulatory;
	u8 rf_option_2;
	u8 rf_option_3;
	u8 rf_option_4;
	u8 res7;
	u8 version			/* 0x30 */;
	u8 customer_id_major;
	u8 customer_id_minor;
	u8 xtal_k;
	u8 chipset;			/* 0x34 */
	u8 res8[0x82];
	u8 vid;				/* 0xb7 */
	u8 res9;
	u8 pid;				/* 0xb9 */
	u8 res10[0x0c];
	u8 mac_addr[ETH_ALEN];		/* 0xc6 */
	u8 res11[2];
	u8 venकरोr_name[7];
	u8 res12[2];
	u8 device_name[0x29];		/* 0xd7 */
पूर्ण;

काष्ठा rtl8192cu_efuse अणु
	__le16 rtl_id;
	__le16 hpon;
	u8 res0[2];
	__le16 clk;
	__le16 testr;
	__le16 vid;
	__le16 did;
	__le16 svid;
	__le16 smid;						/* 0x10 */
	u8 res1[4];
	u8 mac_addr[ETH_ALEN];					/* 0x16 */
	u8 res2[2];
	u8 venकरोr_name[7];
	u8 res3[3];
	u8 device_name[0x14];					/* 0x28 */
	u8 res4[0x1e];						/* 0x3c */
	u8 cck_tx_घातer_index_A[3];				/* 0x5a */
	u8 cck_tx_घातer_index_B[3];
	u8 ht40_1s_tx_घातer_index_A[3];				/* 0x60 */
	u8 ht40_1s_tx_घातer_index_B[3];
	/*
	 * The following entries are half-bytes split as:
	 * bits 0-3: path A, bits 4-7: path B, all values 4 bits चिन्हित
	 */
	काष्ठा rtl8723au_idx ht40_2s_tx_घातer_index_dअगरf[3];
	काष्ठा rtl8723au_idx ht20_tx_घातer_index_dअगरf[3];	/* 0x69 */
	काष्ठा rtl8723au_idx ofdm_tx_घातer_index_dअगरf[3];
	काष्ठा rtl8723au_idx ht40_max_घातer_offset[3];		/* 0x6f */
	काष्ठा rtl8723au_idx ht20_max_घातer_offset[3];
	u8 channel_plan;					/* 0x75 */
	u8 tssi_a;
	u8 tssi_b;
	u8 thermal_meter;	/* xtal_k */			/* 0x78 */
	u8 rf_regulatory;
	u8 rf_option_2;
	u8 rf_option_3;
	u8 rf_option_4;
	u8 res5[1];						/* 0x7d */
	u8 version;
	u8 customer_id;
पूर्ण;

काष्ठा rtl8723bu_pwr_idx अणु
#अगर_घोषित __LITTLE_ENDIAN
	पूर्णांक	ht20:4;
	पूर्णांक	ht40:4;
	पूर्णांक	ofdm:4;
	पूर्णांक	cck:4;
#अन्यथा
	पूर्णांक	cck:4;
	पूर्णांक	ofdm:4;
	पूर्णांक	ht40:4;
	पूर्णांक	ht20:4;
#पूर्ण_अगर
पूर्ण __attribute__((packed));

काष्ठा rtl8723bu_efuse_tx_घातer अणु
	u8 cck_base[6];
	u8 ht40_base[5];
	काष्ठा rtl8723au_idx ht20_ofdm_1s_dअगरf;
	काष्ठा rtl8723bu_pwr_idx pwr_dअगरf[3];
	u8 dummy5g[24]; /* max channel group (14) + घातer dअगरf offset (10) */
पूर्ण;

काष्ठा rtl8723bu_efuse अणु
	__le16 rtl_id;
	u8 res0[0x0e];
	काष्ठा rtl8723bu_efuse_tx_घातer tx_घातer_index_A;	/* 0x10 */
	काष्ठा rtl8723bu_efuse_tx_घातer tx_घातer_index_B;	/* 0x3a */
	काष्ठा rtl8723bu_efuse_tx_घातer tx_घातer_index_C;	/* 0x64 */
	काष्ठा rtl8723bu_efuse_tx_घातer tx_घातer_index_D;	/* 0x8e */
	u8 channel_plan;		/* 0xb8 */
	u8 xtal_k;
	u8 thermal_meter;
	u8 iqk_lck;
	u8 pa_type;			/* 0xbc */
	u8 lna_type_2g;			/* 0xbd */
	u8 res2[3];
	u8 rf_board_option;
	u8 rf_feature_option;
	u8 rf_bt_setting;
	u8 eeprom_version;
	u8 eeprom_customer_id;
	u8 res3[2];
	u8 tx_pwr_calibrate_rate;
	u8 rf_antenna_option;		/* 0xc9 */
	u8 rfe_option;
	u8 res4[9];
	u8 usb_optional_function;
	u8 res5[0x1e];
	u8 res6[2];
	u8 serial[0x0b];		/* 0xf5 */
	u8 vid;				/* 0x100 */
	u8 res7;
	u8 pid;
	u8 res8[4];
	u8 mac_addr[ETH_ALEN];		/* 0x107 */
	u8 res9[2];
	u8 venकरोr_name[0x07];
	u8 res10[2];
	u8 device_name[0x14];
	u8 res11[0xcf];
	u8 package_type;		/* 0x1fb */
	u8 res12[0x4];
पूर्ण;

काष्ठा rtl8192eu_efuse_tx_घातer अणु
	u8 cck_base[6];
	u8 ht40_base[5];
	काष्ठा rtl8723au_idx ht20_ofdm_1s_dअगरf;
	काष्ठा rtl8723bu_pwr_idx pwr_dअगरf[3];
	u8 dummy5g[24]; /* max channel group (14) + घातer dअगरf offset (10) */
पूर्ण;

काष्ठा rtl8192eu_efuse अणु
	__le16 rtl_id;
	u8 res0[0x0e];
	काष्ठा rtl8192eu_efuse_tx_घातer tx_घातer_index_A;	/* 0x10 */
	काष्ठा rtl8192eu_efuse_tx_घातer tx_घातer_index_B;	/* 0x3a */
	u8 res2[0x54];
	u8 channel_plan;		/* 0xb8 */
	u8 xtal_k;
	u8 thermal_meter;
	u8 iqk_lck;
	u8 pa_type;			/* 0xbc */
	u8 lna_type_2g;			/* 0xbd */
	u8 res3[1];
	u8 lna_type_5g;			/* 0xbf */
	u8 res4[1];
	u8 rf_board_option;
	u8 rf_feature_option;
	u8 rf_bt_setting;
	u8 eeprom_version;
	u8 eeprom_customer_id;
	u8 res5[3];
	u8 rf_antenna_option;		/* 0xc9 */
	u8 res6[6];
	u8 vid;				/* 0xd0 */
	u8 res7[1];
	u8 pid;				/* 0xd2 */
	u8 res8[1];
	u8 usb_optional_function;
	u8 res9[2];
	u8 mac_addr[ETH_ALEN];		/* 0xd7 */
	u8 res10[2];
	u8 venकरोr_name[7];
	u8 res11[2];
	u8 device_name[0x0b];		/* 0xe8 */
	u8 res12[2];
	u8 serial[0x0b];		/* 0xf5 */
	u8 res13[0x30];
	u8 unknown[0x0d];		/* 0x130 */
	u8 res14[0xc3];
पूर्ण;

काष्ठा rtl8xxxu_reg8val अणु
	u16 reg;
	u8 val;
पूर्ण;

काष्ठा rtl8xxxu_reg32val अणु
	u16 reg;
	u32 val;
पूर्ण;

काष्ठा rtl8xxxu_rfregval अणु
	u8 reg;
	u32 val;
पूर्ण;

क्रमागत rtl8xxxu_rfpath अणु
	RF_A = 0,
	RF_B = 1,
पूर्ण;

काष्ठा rtl8xxxu_rfregs अणु
	u16 hssiparm1;
	u16 hssiparm2;
	u16 lssiparm;
	u16 hspiपढ़ो;
	u16 lssiपढ़ो;
	u16 rf_sw_ctrl;
पूर्ण;

#घोषणा H2C_MAX_MBOX			4
#घोषणा H2C_EXT				BIT(7)
#घोषणा  H2C_JOIN_BSS_DISCONNECT	0
#घोषणा  H2C_JOIN_BSS_CONNECT		1

/*
 * H2C (firmware) commands dअगरfer between the older generation chips
 * 8188[cr]u, 819[12]cu, and 8723au, and the more recent chips 8723bu,
 * 8192[de]u, 8192eu, and 8812.
 */
क्रमागत h2c_cmd_8723a अणु
	H2C_SET_POWER_MODE = 1,
	H2C_JOIN_BSS_REPORT = 2,
	H2C_SET_RSSI = 5,
	H2C_SET_RATE_MASK = (6 | H2C_EXT),
पूर्ण;

क्रमागत h2c_cmd_8723b अणु
	/*
	 * Common Class: 000
	 */
	H2C_8723B_RSVD_PAGE = 0x00,
	H2C_8723B_MEDIA_STATUS_RPT = 0x01,
	H2C_8723B_SCAN_ENABLE = 0x02,
	H2C_8723B_KEEP_ALIVE = 0x03,
	H2C_8723B_DISCON_DECISION = 0x04,
	H2C_8723B_PSD_OFFLOAD = 0x05,
	H2C_8723B_AP_OFFLOAD = 0x08,
	H2C_8723B_BCN_RSVDPAGE = 0x09,
	H2C_8723B_PROBERSP_RSVDPAGE = 0x0A,
	H2C_8723B_FCS_RSVDPAGE = 0x10,
	H2C_8723B_FCS_INFO = 0x11,
	H2C_8723B_AP_WOW_GPIO_CTRL = 0x13,

	/*
	 * PoweSave Class: 001
	 */
	H2C_8723B_SET_PWR_MODE = 0x20,
	H2C_8723B_PS_TUNING_PARA = 0x21,
	H2C_8723B_PS_TUNING_PARA2 = 0x22,
	H2C_8723B_P2P_LPS_PARAM = 0x23,
	H2C_8723B_P2P_PS_OFFLOAD = 0x24,
	H2C_8723B_PS_SCAN_ENABLE = 0x25,
	H2C_8723B_SAP_PS_ = 0x26,
	H2C_8723B_INACTIVE_PS_ = 0x27,
	H2C_8723B_FWLPS_IN_IPS_ = 0x28,

	/*
	 * Dynamic Mechanism Class: 010
	 */
	H2C_8723B_MACID_CFG_RAID = 0x40,
	H2C_8723B_TXBF = 0x41,
	H2C_8723B_RSSI_SETTING = 0x42,
	H2C_8723B_AP_REQ_TXRPT = 0x43,
	H2C_8723B_INIT_RATE_COLLECT = 0x44,

	/*
	 * BT Class: 011
	 */
	H2C_8723B_B_TYPE_TDMA = 0x60,
	H2C_8723B_BT_INFO = 0x61,
	H2C_8723B_FORCE_BT_TXPWR = 0x62,
	H2C_8723B_BT_IGNORE_WLANACT = 0x63,
	H2C_8723B_DAC_SWING_VALUE = 0x64,
	H2C_8723B_ANT_SEL_RSV = 0x65,
	H2C_8723B_WL_OPMODE = 0x66,
	H2C_8723B_BT_MP_OPER = 0x67,
	H2C_8723B_BT_CONTROL = 0x68,
	H2C_8723B_BT_WIFI_CTRL = 0x69,
	H2C_8723B_BT_FW_PATCH = 0x6a,
	H2C_8723B_BT_WLAN_CALIBRATION = 0x6d,
	H2C_8723B_BT_GRANT = 0x6e,

	/*
	 * WOWLAN Class: 100
	 */
	H2C_8723B_WOWLAN = 0x80,
	H2C_8723B_REMOTE_WAKE_CTRL = 0x81,
	H2C_8723B_AOAC_GLOBAL_INFO = 0x82,
	H2C_8723B_AOAC_RSVD_PAGE = 0x83,
	H2C_8723B_AOAC_RSVD_PAGE2 = 0x84,
	H2C_8723B_D0_SCAN_OFFLOAD_CTRL = 0x85,
	H2C_8723B_D0_SCAN_OFFLOAD_INFO = 0x86,
	H2C_8723B_CHNL_SWITCH_OFFLOAD = 0x87,

	H2C_8723B_RESET_TSF = 0xC0,
पूर्ण;


काष्ठा h2c_cmd अणु
	जोड़ अणु
		काष्ठा अणु
			u8 cmd;
			u8 data[7];
		पूर्ण __packed cmd;
		काष्ठा अणु
			__le32 data;
			__le16 ext;
		पूर्ण __packed raw;
		काष्ठा अणु
			__le32 data;
			__le32 ext;
		पूर्ण __packed raw_wide;
		काष्ठा अणु
			u8 cmd;
			u8 data;
		पूर्ण __packed joinbss;
		काष्ठा अणु
			u8 cmd;
			__le16 mask_hi;
			u8 arg;
			__le16 mask_lo;
		पूर्ण __packed ramask;
		काष्ठा अणु
			u8 cmd;
			u8 parm;
			u8 macid;
			u8 macid_end;
		पूर्ण __packed media_status_rpt;
		काष्ठा अणु
			u8 cmd;
			u8 macid;
			/*
			 * [0:4] - RAID
			 * [7]   - SGI
			 */
			u8 data1;
			/*
			 * [0:1] - Bandwidth
			 * [3]   - No Update
			 * [4:5] - VHT enable
			 * [6]   - DISPT
			 * [7]   - DISRA
			 */
			u8 data2;
			u8 ramask0;
			u8 ramask1;
			u8 ramask2;
			u8 ramask3;
		पूर्ण __packed b_macid_cfg;
		काष्ठा अणु
			u8 cmd;
			u8 data1;
			u8 data2;
			u8 data3;
			u8 data4;
			u8 data5;
		पूर्ण __packed b_type_dma;
		काष्ठा अणु
			u8 cmd;
			u8 data;
		पूर्ण __packed bt_info;
		काष्ठा अणु
			u8 cmd;
			u8 operreq;
			u8 opcode;
			u8 data;
			u8 addr;
		पूर्ण __packed bt_mp_oper;
		काष्ठा अणु
			u8 cmd;
			u8 data;
		पूर्ण __packed bt_wlan_calibration;
		काष्ठा अणु
			u8 cmd;
			u8 data;
		पूर्ण __packed ignore_wlan;
		काष्ठा अणु
			u8 cmd;
			u8 ant_inverse;
			u8 पूर्णांक_चयन_type;
		पूर्ण __packed ant_sel_rsv;
		काष्ठा अणु
			u8 cmd;
			u8 data;
		पूर्ण __packed bt_grant;
	पूर्ण;
पूर्ण;

क्रमागत c2h_evt_8723b अणु
	C2H_8723B_DEBUG = 0,
	C2H_8723B_TSF = 1,
	C2H_8723B_AP_RPT_RSP = 2,
	C2H_8723B_CCX_TX_RPT = 3,
	C2H_8723B_BT_RSSI = 4,
	C2H_8723B_BT_OP_MODE = 5,
	C2H_8723B_EXT_RA_RPT = 6,
	C2H_8723B_BT_INFO = 9,
	C2H_8723B_HW_INFO_EXCH = 0x0a,
	C2H_8723B_BT_MP_INFO = 0x0b,
	C2H_8723B_RA_REPORT = 0x0c,
	C2H_8723B_FW_DEBUG = 0xff,
पूर्ण;

क्रमागत bt_info_src_8723b अणु
	BT_INFO_SRC_8723B_WIFI_FW = 0x0,
        BT_INFO_SRC_8723B_BT_RSP = 0x1,
        BT_INFO_SRC_8723B_BT_ACTIVE_SEND = 0x2,
पूर्ण;

क्रमागत bt_mp_oper_opcode_8723b अणु
	BT_MP_OP_GET_BT_VERSION	= 0x00,
	BT_MP_OP_RESET = 0x01,
	BT_MP_OP_TEST_CTRL = 0x02,
	BT_MP_OP_SET_BT_MODE = 0x03,
	BT_MP_OP_SET_CHNL_TX_GAIN = 0x04,
	BT_MP_OP_SET_PKT_TYPE_LEN = 0x05,
	BT_MP_OP_SET_PKT_CNT_L_PL_TYPE = 0x06,
	BT_MP_OP_SET_PKT_CNT_H_PKT_INTV = 0x07,
	BT_MP_OP_SET_PKT_HEADER = 0x08,
	BT_MP_OP_SET_WHITENCOEFF = 0x09,
	BT_MP_OP_SET_BD_ADDR_L = 0x0a,
	BT_MP_OP_SET_BD_ADDR_H = 0x0b,
	BT_MP_OP_WRITE_REG_ADDR = 0x0c,
	BT_MP_OP_WRITE_REG_VALUE = 0x0d,
	BT_MP_OP_GET_BT_STATUS = 0x0e,
	BT_MP_OP_GET_BD_ADDR_L = 0x0f,
	BT_MP_OP_GET_BD_ADDR_H = 0x10,
	BT_MP_OP_READ_REG = 0x11,
	BT_MP_OP_SET_TARGET_BD_ADDR_L = 0x12,
	BT_MP_OP_SET_TARGET_BD_ADDR_H = 0x13,
	BT_MP_OP_SET_TX_POWER_CALIBRATION = 0x14,
	BT_MP_OP_GET_RX_PKT_CNT_L = 0x15,
	BT_MP_OP_GET_RX_PKT_CNT_H = 0x16,
	BT_MP_OP_GET_RX_ERROR_BITS_L = 0x17,
	BT_MP_OP_GET_RX_ERROR_BITS_H = 0x18,
	BT_MP_OP_GET_RSSI = 0x19,
	BT_MP_OP_GET_CFO_HDR_QUALITY_L = 0x1a,
	BT_MP_OP_GET_CFO_HDR_QUALITY_H = 0x1b,
	BT_MP_OP_GET_TARGET_BD_ADDR_L = 0x1c,
	BT_MP_OP_GET_TARGET_BD_ADDR_H = 0x1d,
	BT_MP_OP_GET_AFH_MAP_L = 0x1e,
	BT_MP_OP_GET_AFH_MAP_M = 0x1f,
	BT_MP_OP_GET_AFH_MAP_H = 0x20,
	BT_MP_OP_GET_AFH_STATUS = 0x21,
	BT_MP_OP_SET_TRACKING_INTERVAL = 0x22,
	BT_MP_OP_SET_THERMAL_METER = 0x23,
	BT_MP_OP_ENABLE_CFO_TRACKING = 0x24,
पूर्ण;

क्रमागत rtl8xxxu_bw_mode अणु
	RTL8XXXU_CHANNEL_WIDTH_20 = 0,
	RTL8XXXU_CHANNEL_WIDTH_40 = 1,
	RTL8XXXU_CHANNEL_WIDTH_80 = 2,
	RTL8XXXU_CHANNEL_WIDTH_160 = 3,
	RTL8XXXU_CHANNEL_WIDTH_80_80 = 4,
	RTL8XXXU_CHANNEL_WIDTH_MAX = 5,
पूर्ण;

काष्ठा rtl8723bu_c2h अणु
	u8 id;
	u8 seq;
	जोड़ अणु
		काष्ठा अणु
			u8 payload[0];
		पूर्ण __packed raw;
		काष्ठा अणु
			u8 ext_id;
			u8 status:4;
			u8 retlen:4;
			u8 opcode_ver:4;
			u8 req_num:4;
			u8 payload[2];
		पूर्ण __packed bt_mp_info;
		काष्ठा अणु
			u8 response_source:4;
			u8 dummy0_0:4;

			u8 bt_info;

			u8 retry_count:4;
			u8 dummy2_0:1;
			u8 bt_page:1;
			u8 tx_rx_mask:1;
			u8 dummy2_2:1;

			u8 rssi;

			u8 basic_rate:1;
			u8 bt_has_reset:1;
			u8 dummy4_1:1;
			u8 ignore_wlan:1;
			u8 स्वतः_report:1;
			u8 dummy4_2:3;

			u8 a4;
			u8 a5;
		पूर्ण __packed bt_info;
		काष्ठा अणु
			u8 rate:7;
			u8 sgi:1;
			u8 macid;
			u8 ldpc:1;
			u8 txbf:1;
			u8 noisy_state:1;
			u8 dummy2_0:5;
			u8 dummy3_0;
			u8 dummy4_0;
			u8 dummy5_0;
			u8 bw;
		पूर्ण __packed ra_report;
	पूर्ण;
पूर्ण;

काष्ठा rtl8xxxu_fileops;

/*mlme related.*/
क्रमागत wireless_mode अणु
	WIRELESS_MODE_UNKNOWN = 0,
	/* Sub-Element */
	WIRELESS_MODE_B = BIT(0),
	WIRELESS_MODE_G = BIT(1),
	WIRELESS_MODE_A = BIT(2),
	WIRELESS_MODE_N_24G = BIT(3),
	WIRELESS_MODE_N_5G = BIT(4),
	WIRELESS_AUTO = BIT(5),
	WIRELESS_MODE_AC = BIT(6),
	WIRELESS_MODE_MAX = 0x7F,
पूर्ण;

/* from rtlwअगरi/wअगरi.h */
क्रमागत ratr_table_mode_new अणु
	RATEID_IDX_BGN_40M_2SS = 0,
	RATEID_IDX_BGN_40M_1SS = 1,
	RATEID_IDX_BGN_20M_2SS_BN = 2,
	RATEID_IDX_BGN_20M_1SS_BN = 3,
	RATEID_IDX_GN_N2SS = 4,
	RATEID_IDX_GN_N1SS = 5,
	RATEID_IDX_BG = 6,
	RATEID_IDX_G = 7,
	RATEID_IDX_B = 8,
	RATEID_IDX_VHT_2SS = 9,
	RATEID_IDX_VHT_1SS = 10,
	RATEID_IDX_MIX1 = 11,
	RATEID_IDX_MIX2 = 12,
	RATEID_IDX_VHT_3SS = 13,
	RATEID_IDX_BGN_3SS = 14,
पूर्ण;

#घोषणा BT_INFO_8723B_1ANT_B_FTP		BIT(7)
#घोषणा BT_INFO_8723B_1ANT_B_A2DP		BIT(6)
#घोषणा BT_INFO_8723B_1ANT_B_HID		BIT(5)
#घोषणा BT_INFO_8723B_1ANT_B_SCO_BUSY		BIT(4)
#घोषणा BT_INFO_8723B_1ANT_B_ACL_BUSY		BIT(3)
#घोषणा BT_INFO_8723B_1ANT_B_INQ_PAGE		BIT(2)
#घोषणा BT_INFO_8723B_1ANT_B_SCO_ESCO		BIT(1)
#घोषणा BT_INFO_8723B_1ANT_B_CONNECTION	BIT(0)

क्रमागत _BT_8723B_1ANT_STATUS अणु
	BT_8723B_1ANT_STATUS_NON_CONNECTED_IDLE      = 0x0,
	BT_8723B_1ANT_STATUS_CONNECTED_IDLE          = 0x1,
	BT_8723B_1ANT_STATUS_INQ_PAGE                = 0x2,
	BT_8723B_1ANT_STATUS_ACL_BUSY                = 0x3,
	BT_8723B_1ANT_STATUS_SCO_BUSY                = 0x4,
	BT_8723B_1ANT_STATUS_ACL_SCO_BUSY            = 0x5,
	BT_8723B_1ANT_STATUS_MAX
पूर्ण;

काष्ठा rtl8xxxu_btcoex अणु
	u8      bt_status;
	bool	bt_busy;
	bool	has_sco;
	bool	has_a2dp;
	bool    has_hid;
	bool    has_pan;
	bool	hid_only;
	bool	a2dp_only;
	bool    c2h_bt_inquiry;
पूर्ण;

#घोषणा RTL8XXXU_RATR_STA_INIT 0
#घोषणा RTL8XXXU_RATR_STA_HIGH 1
#घोषणा RTL8XXXU_RATR_STA_MID  2
#घोषणा RTL8XXXU_RATR_STA_LOW  3

#घोषणा RTL8XXXU_NOISE_FLOOR_MIN	-100
#घोषणा RTL8XXXU_SNR_THRESH_HIGH	50
#घोषणा RTL8XXXU_SNR_THRESH_LOW	20

काष्ठा rtl8xxxu_ra_report अणु
	काष्ठा rate_info txrate;
	u32 bit_rate;
	u8 desc_rate;
पूर्ण;

काष्ठा rtl8xxxu_priv अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा usb_device *udev;
	काष्ठा rtl8xxxu_fileops *fops;

	spinlock_t tx_urb_lock;
	काष्ठा list_head tx_urb_मुक्त_list;
	पूर्णांक tx_urb_मुक्त_count;
	bool tx_stopped;

	spinlock_t rx_urb_lock;
	काष्ठा list_head rx_urb_pending_list;
	पूर्णांक rx_urb_pending_count;
	bool shutकरोwn;
	काष्ठा work_काष्ठा rx_urb_wq;

	u8 mac_addr[ETH_ALEN];
	अक्षर chip_name[8];
	अक्षर chip_venकरोr[8];
	u8 cck_tx_घातer_index_A[RTL8XXXU_MAX_CHANNEL_GROUPS];
	u8 cck_tx_घातer_index_B[RTL8XXXU_MAX_CHANNEL_GROUPS];
	u8 ht40_1s_tx_घातer_index_A[RTL8XXXU_MAX_CHANNEL_GROUPS];
	u8 ht40_1s_tx_घातer_index_B[RTL8XXXU_MAX_CHANNEL_GROUPS];
	/*
	 * The following entries are half-bytes split as:
	 * bits 0-3: path A, bits 4-7: path B, all values 4 bits चिन्हित
	 */
	काष्ठा rtl8723au_idx ht40_2s_tx_घातer_index_dअगरf[
		RTL8723A_CHANNEL_GROUPS];
	काष्ठा rtl8723au_idx ht20_tx_घातer_index_dअगरf[RTL8723A_CHANNEL_GROUPS];
	काष्ठा rtl8723au_idx ofdm_tx_घातer_index_dअगरf[RTL8723A_CHANNEL_GROUPS];
	काष्ठा rtl8723au_idx ht40_max_घातer_offset[RTL8723A_CHANNEL_GROUPS];
	काष्ठा rtl8723au_idx ht20_max_घातer_offset[RTL8723A_CHANNEL_GROUPS];
	/*
	 * Newer generation chips only keep घातer dअगरfs per TX count,
	 * not per channel group.
	 */
	काष्ठा rtl8723au_idx ofdm_tx_घातer_dअगरf[RTL8723B_TX_COUNT];
	काष्ठा rtl8723au_idx ht20_tx_घातer_dअगरf[RTL8723B_TX_COUNT];
	काष्ठा rtl8723au_idx ht40_tx_घातer_dअगरf[RTL8723B_TX_COUNT];
	काष्ठा rtl8xxxu_घातer_base *घातer_base;
	u32 chip_cut:4;
	u32 rom_rev:4;
	u32 is_multi_func:1;
	u32 has_wअगरi:1;
	u32 has_bluetooth:1;
	u32 enable_bluetooth:1;
	u32 has_gps:1;
	u32 hi_pa:1;
	u32 venकरोr_umc:1;
	u32 venकरोr_smic:1;
	u32 has_polarity_ctrl:1;
	u32 has_eeprom:1;
	u32 boot_eeprom:1;
	u32 usb_पूर्णांकerrupts:1;
	u32 ep_tx_high_queue:1;
	u32 ep_tx_normal_queue:1;
	u32 ep_tx_low_queue:1;
	u32 has_xtalk:1;
	u32 rx_buf_aggregation:1;
	u8 xtalk;
	अचिन्हित पूर्णांक pipe_पूर्णांकerrupt;
	अचिन्हित पूर्णांक pipe_in;
	अचिन्हित पूर्णांक pipe_out[TXDESC_QUEUE_MAX];
	u8 out_ep[RTL8XXXU_OUT_ENDPOINTS];
	u8 ep_tx_count;
	u8 rf_paths;
	u8 rx_paths;
	u8 tx_paths;
	u32 rege94;
	u32 rege9c;
	u32 regeb4;
	u32 regebc;
	पूर्णांक next_mbox;
	पूर्णांक nr_out_eps;

	काष्ठा mutex h2c_mutex;

	काष्ठा usb_anchor rx_anchor;
	काष्ठा usb_anchor tx_anchor;
	काष्ठा usb_anchor पूर्णांक_anchor;
	काष्ठा rtl8xxxu_firmware_header *fw_data;
	माप_प्रकार fw_size;
	काष्ठा mutex usb_buf_mutex;
	जोड़ अणु
		__le32 val32;
		__le16 val16;
		u8 val8;
	पूर्ण usb_buf;
	जोड़ अणु
		u8 raw[EFUSE_MAP_LEN];
		काष्ठा rtl8723au_efuse efuse8723;
		काष्ठा rtl8723bu_efuse efuse8723bu;
		काष्ठा rtl8192cu_efuse efuse8192;
		काष्ठा rtl8192eu_efuse efuse8192eu;
	पूर्ण efuse_wअगरi;
	u32 adda_backup[RTL8XXXU_ADDA_REGS];
	u32 mac_backup[RTL8XXXU_MAC_REGS];
	u32 bb_backup[RTL8XXXU_BB_REGS];
	u32 bb_recovery_backup[RTL8XXXU_BB_REGS];
	क्रमागत rtl8xxxu_rtl_chip rtl_chip;
	u8 pi_enabled:1;
	u8 no_pape:1;
	u8 पूर्णांक_buf[USB_INTR_CONTENT_LENGTH];
	u8 rssi_level;
	/*
	 * Only one भव पूर्णांकerface permitted because only STA mode
	 * is supported and no अगरace_combinations are provided.
	 */
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा delayed_work ra_watchकरोg;
	काष्ठा work_काष्ठा c2hcmd_work;
	काष्ठा sk_buff_head c2hcmd_queue;
	काष्ठा rtl8xxxu_btcoex bt_coex;
	काष्ठा rtl8xxxu_ra_report ra_report;
पूर्ण;

काष्ठा rtl8xxxu_rx_urb अणु
	काष्ठा urb urb;
	काष्ठा ieee80211_hw *hw;
	काष्ठा list_head list;
पूर्ण;

काष्ठा rtl8xxxu_tx_urb अणु
	काष्ठा urb urb;
	काष्ठा ieee80211_hw *hw;
	काष्ठा list_head list;
पूर्ण;

काष्ठा rtl8xxxu_fileops अणु
	पूर्णांक (*parse_efuse) (काष्ठा rtl8xxxu_priv *priv);
	पूर्णांक (*load_firmware) (काष्ठा rtl8xxxu_priv *priv);
	पूर्णांक (*घातer_on) (काष्ठा rtl8xxxu_priv *priv);
	व्योम (*घातer_off) (काष्ठा rtl8xxxu_priv *priv);
	व्योम (*reset_8051) (काष्ठा rtl8xxxu_priv *priv);
	पूर्णांक (*llt_init) (काष्ठा rtl8xxxu_priv *priv);
	व्योम (*init_phy_bb) (काष्ठा rtl8xxxu_priv *priv);
	पूर्णांक (*init_phy_rf) (काष्ठा rtl8xxxu_priv *priv);
	व्योम (*phy_init_antenna_selection) (काष्ठा rtl8xxxu_priv *priv);
	व्योम (*phy_iq_calibrate) (काष्ठा rtl8xxxu_priv *priv);
	व्योम (*config_channel) (काष्ठा ieee80211_hw *hw);
	पूर्णांक (*parse_rx_desc) (काष्ठा rtl8xxxu_priv *priv, काष्ठा sk_buff *skb);
	व्योम (*init_aggregation) (काष्ठा rtl8xxxu_priv *priv);
	व्योम (*init_statistics) (काष्ठा rtl8xxxu_priv *priv);
	व्योम (*enable_rf) (काष्ठा rtl8xxxu_priv *priv);
	व्योम (*disable_rf) (काष्ठा rtl8xxxu_priv *priv);
	व्योम (*usb_quirks) (काष्ठा rtl8xxxu_priv *priv);
	व्योम (*set_tx_घातer) (काष्ठा rtl8xxxu_priv *priv, पूर्णांक channel,
			      bool ht40);
	व्योम (*update_rate_mask) (काष्ठा rtl8xxxu_priv *priv,
				  u32 ramask, u8 rateid, पूर्णांक sgi);
	व्योम (*report_connect) (काष्ठा rtl8xxxu_priv *priv,
				u8 macid, bool connect);
	व्योम (*fill_txdesc) (काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_hdr *hdr,
			     काष्ठा ieee80211_tx_info *tx_info,
			     काष्ठा rtl8xxxu_txdesc32 *tx_desc, bool sgi,
			     bool लघु_preamble, bool ampdu_enable,
			     u32 rts_rate);
	पूर्णांक ग_लिखोN_block_size;
	पूर्णांक rx_agg_buf_size;
	अक्षर tx_desc_size;
	अक्षर rx_desc_size;
	u8 has_s0s1:1;
	u8 has_tx_report:1;
	u8 gen2_thermal_meter:1;
	u8 needs_full_init:1;
	u32 adda_1t_init;
	u32 adda_1t_path_on;
	u32 adda_2t_path_on_a;
	u32 adda_2t_path_on_b;
	u16 trxff_boundary;
	u8 pbp_rx;
	u8 pbp_tx;
	काष्ठा rtl8xxxu_reg8val *mactable;
	u8 total_page_num;
	u8 page_num_hi;
	u8 page_num_lo;
	u8 page_num_norm;
पूर्ण;

बाह्य पूर्णांक rtl8xxxu_debug;

बाह्य काष्ठा rtl8xxxu_reg8val rtl8xxxu_gen1_mac_init_table[];
बाह्य स्थिर u32 rtl8xxxu_iqk_phy_iq_bb_reg[];
u8 rtl8xxxu_पढ़ो8(काष्ठा rtl8xxxu_priv *priv, u16 addr);
u16 rtl8xxxu_पढ़ो16(काष्ठा rtl8xxxu_priv *priv, u16 addr);
u32 rtl8xxxu_पढ़ो32(काष्ठा rtl8xxxu_priv *priv, u16 addr);
पूर्णांक rtl8xxxu_ग_लिखो8(काष्ठा rtl8xxxu_priv *priv, u16 addr, u8 val);
पूर्णांक rtl8xxxu_ग_लिखो16(काष्ठा rtl8xxxu_priv *priv, u16 addr, u16 val);
पूर्णांक rtl8xxxu_ग_लिखो32(काष्ठा rtl8xxxu_priv *priv, u16 addr, u32 val);
u32 rtl8xxxu_पढ़ो_rfreg(काष्ठा rtl8xxxu_priv *priv,
			क्रमागत rtl8xxxu_rfpath path, u8 reg);
पूर्णांक rtl8xxxu_ग_लिखो_rfreg(काष्ठा rtl8xxxu_priv *priv,
			 क्रमागत rtl8xxxu_rfpath path, u8 reg, u32 data);
व्योम rtl8xxxu_save_regs(काष्ठा rtl8xxxu_priv *priv, स्थिर u32 *regs,
			u32 *backup, पूर्णांक count);
व्योम rtl8xxxu_restore_regs(काष्ठा rtl8xxxu_priv *priv, स्थिर u32 *regs,
			   u32 *backup, पूर्णांक count);
व्योम rtl8xxxu_save_mac_regs(काष्ठा rtl8xxxu_priv *priv,
			    स्थिर u32 *reg, u32 *backup);
व्योम rtl8xxxu_restore_mac_regs(काष्ठा rtl8xxxu_priv *priv,
			       स्थिर u32 *reg, u32 *backup);
व्योम rtl8xxxu_path_adda_on(काष्ठा rtl8xxxu_priv *priv, स्थिर u32 *regs,
			   bool path_a_on);
व्योम rtl8xxxu_mac_calibration(काष्ठा rtl8xxxu_priv *priv,
			      स्थिर u32 *regs, u32 *backup);
व्योम rtl8xxxu_fill_iqk_matrix_a(काष्ठा rtl8xxxu_priv *priv, bool iqk_ok,
				पूर्णांक result[][8], पूर्णांक candidate, bool tx_only);
व्योम rtl8xxxu_fill_iqk_matrix_b(काष्ठा rtl8xxxu_priv *priv, bool iqk_ok,
				पूर्णांक result[][8], पूर्णांक candidate, bool tx_only);
पूर्णांक rtl8xxxu_init_phy_rf(काष्ठा rtl8xxxu_priv *priv,
			 काष्ठा rtl8xxxu_rfregval *table,
			 क्रमागत rtl8xxxu_rfpath path);
पूर्णांक rtl8xxxu_init_phy_regs(काष्ठा rtl8xxxu_priv *priv,
			   काष्ठा rtl8xxxu_reg32val *array);
पूर्णांक rtl8xxxu_load_firmware(काष्ठा rtl8xxxu_priv *priv, अक्षर *fw_name);
व्योम rtl8xxxu_firmware_self_reset(काष्ठा rtl8xxxu_priv *priv);
व्योम rtl8xxxu_घातer_off(काष्ठा rtl8xxxu_priv *priv);
व्योम rtl8xxxu_reset_8051(काष्ठा rtl8xxxu_priv *priv);
पूर्णांक rtl8xxxu_स्वतः_llt_table(काष्ठा rtl8xxxu_priv *priv);
व्योम rtl8xxxu_gen2_prepare_calibrate(काष्ठा rtl8xxxu_priv *priv, u8 start);
पूर्णांक rtl8xxxu_flush_fअगरo(काष्ठा rtl8xxxu_priv *priv);
पूर्णांक rtl8xxxu_gen2_h2c_cmd(काष्ठा rtl8xxxu_priv *priv,
			  काष्ठा h2c_cmd *h2c, पूर्णांक len);
पूर्णांक rtl8xxxu_active_to_lps(काष्ठा rtl8xxxu_priv *priv);
व्योम rtl8xxxu_disabled_to_emu(काष्ठा rtl8xxxu_priv *priv);
पूर्णांक rtl8xxxu_init_llt_table(काष्ठा rtl8xxxu_priv *priv);
व्योम rtl8xxxu_gen1_phy_iq_calibrate(काष्ठा rtl8xxxu_priv *priv);
व्योम rtl8xxxu_gen1_init_phy_bb(काष्ठा rtl8xxxu_priv *priv);
व्योम rtl8xxxu_gen1_set_tx_घातer(काष्ठा rtl8xxxu_priv *priv,
				पूर्णांक channel, bool ht40);
व्योम rtl8xxxu_gen1_config_channel(काष्ठा ieee80211_hw *hw);
व्योम rtl8xxxu_gen2_config_channel(काष्ठा ieee80211_hw *hw);
व्योम rtl8xxxu_gen1_usb_quirks(काष्ठा rtl8xxxu_priv *priv);
व्योम rtl8xxxu_gen2_usb_quirks(काष्ठा rtl8xxxu_priv *priv);
व्योम rtl8xxxu_update_rate_mask(काष्ठा rtl8xxxu_priv *priv,
			       u32 ramask, u8 rateid, पूर्णांक sgi);
व्योम rtl8xxxu_gen2_update_rate_mask(काष्ठा rtl8xxxu_priv *priv,
				    u32 ramask, u8 rateid, पूर्णांक sgi);
व्योम rtl8xxxu_gen1_report_connect(काष्ठा rtl8xxxu_priv *priv,
				  u8 macid, bool connect);
व्योम rtl8xxxu_gen2_report_connect(काष्ठा rtl8xxxu_priv *priv,
				  u8 macid, bool connect);
व्योम rtl8xxxu_gen1_init_aggregation(काष्ठा rtl8xxxu_priv *priv);
व्योम rtl8xxxu_gen1_enable_rf(काष्ठा rtl8xxxu_priv *priv);
व्योम rtl8xxxu_gen1_disable_rf(काष्ठा rtl8xxxu_priv *priv);
व्योम rtl8xxxu_gen2_disable_rf(काष्ठा rtl8xxxu_priv *priv);
पूर्णांक rtl8xxxu_parse_rxdesc16(काष्ठा rtl8xxxu_priv *priv, काष्ठा sk_buff *skb);
पूर्णांक rtl8xxxu_parse_rxdesc24(काष्ठा rtl8xxxu_priv *priv, काष्ठा sk_buff *skb);
पूर्णांक rtl8xxxu_gen2_channel_to_group(पूर्णांक channel);
bool rtl8xxxu_gen2_simularity_compare(काष्ठा rtl8xxxu_priv *priv,
				      पूर्णांक result[][8], पूर्णांक c1, पूर्णांक c2);
व्योम rtl8xxxu_fill_txdesc_v1(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_hdr *hdr,
			     काष्ठा ieee80211_tx_info *tx_info,
			     काष्ठा rtl8xxxu_txdesc32 *tx_desc, bool sgi,
			     bool लघु_preamble, bool ampdu_enable,
			     u32 rts_rate);
व्योम rtl8xxxu_fill_txdesc_v2(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_hdr *hdr,
			     काष्ठा ieee80211_tx_info *tx_info,
			     काष्ठा rtl8xxxu_txdesc32 *tx_desc32, bool sgi,
			     bool लघु_preamble, bool ampdu_enable,
			     u32 rts_rate);
व्योम rtl8723bu_set_ps_tdma(काष्ठा rtl8xxxu_priv *priv,
			   u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5);

बाह्य काष्ठा rtl8xxxu_fileops rtl8192cu_fops;
बाह्य काष्ठा rtl8xxxu_fileops rtl8192eu_fops;
बाह्य काष्ठा rtl8xxxu_fileops rtl8723au_fops;
बाह्य काष्ठा rtl8xxxu_fileops rtl8723bu_fops;
