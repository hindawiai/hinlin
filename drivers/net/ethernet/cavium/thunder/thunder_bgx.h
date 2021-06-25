<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Cavium, Inc.
 */

#अगर_अघोषित THUNDER_BGX_H
#घोषणा THUNDER_BGX_H

/* PCI device ID */
#घोषणा	PCI_DEVICE_ID_THUNDER_BGX		0xA026
#घोषणा	PCI_DEVICE_ID_THUNDER_RGX		0xA054

/* Subप्रणाली device IDs */
#घोषणा PCI_SUBSYS_DEVID_88XX_BGX		0xA126
#घोषणा PCI_SUBSYS_DEVID_81XX_BGX		0xA226
#घोषणा PCI_SUBSYS_DEVID_81XX_RGX		0xA254
#घोषणा PCI_SUBSYS_DEVID_83XX_BGX		0xA326

#घोषणा    MAX_BGX_THUNDER			8 /* Max 2 nodes, 4 per node */
#घोषणा    MAX_BGX_PER_CN88XX			2
#घोषणा    MAX_BGX_PER_CN81XX			3 /* 2 BGXs + 1 RGX */
#घोषणा    MAX_BGX_PER_CN83XX			4
#घोषणा    MAX_LMAC_PER_BGX			4
#घोषणा    MAX_BGX_CHANS_PER_LMAC		16
#घोषणा    MAX_DMAC_PER_LMAC			8
#घोषणा    MAX_FRAME_SIZE			9216
#घोषणा    DEFAULT_PAUSE_TIME			0xFFFF

#घोषणा	   BGX_ID_MASK				0x3
#घोषणा	   LMAC_ID_MASK				0x3

#घोषणा    MAX_DMAC_PER_LMAC_TNS_BYPASS_MODE	2

/* Registers */
#घोषणा BGX_CMRX_CFG			0x00
#घोषणा  CMR_PKT_TX_EN				BIT_ULL(13)
#घोषणा  CMR_PKT_RX_EN				BIT_ULL(14)
#घोषणा  CMR_EN					BIT_ULL(15)
#घोषणा BGX_CMR_GLOBAL_CFG		0x08
#घोषणा  CMR_GLOBAL_CFG_FCS_STRIP		BIT_ULL(6)
#घोषणा BGX_CMRX_RX_ID_MAP		0x60
#घोषणा BGX_CMRX_RX_STAT0		0x70
#घोषणा BGX_CMRX_RX_STAT1		0x78
#घोषणा BGX_CMRX_RX_STAT2		0x80
#घोषणा BGX_CMRX_RX_STAT3		0x88
#घोषणा BGX_CMRX_RX_STAT4		0x90
#घोषणा BGX_CMRX_RX_STAT5		0x98
#घोषणा BGX_CMRX_RX_STAT6		0xA0
#घोषणा BGX_CMRX_RX_STAT7		0xA8
#घोषणा BGX_CMRX_RX_STAT8		0xB0
#घोषणा BGX_CMRX_RX_STAT9		0xB8
#घोषणा BGX_CMRX_RX_STAT10		0xC0
#घोषणा BGX_CMRX_RX_BP_DROP		0xC8
#घोषणा BGX_CMRX_RX_DMAC_CTL		0x0E8
#घोषणा BGX_CMRX_RX_FIFO_LEN		0x108
#घोषणा BGX_CMR_RX_DMACX_CAM		0x200
#घोषणा  RX_DMACX_CAM_EN			BIT_ULL(48)
#घोषणा  RX_DMACX_CAM_LMACID(x)			(((u64)x) << 49)
#घोषणा  RX_DMAC_COUNT				32
#घोषणा BGX_CMR_RX_STEERING		0x300
#घोषणा  RX_TRAFFIC_STEER_RULE_COUNT		8
#घोषणा BGX_CMR_CHAN_MSK_AND		0x450
#घोषणा BGX_CMR_BIST_STATUS		0x460
#घोषणा BGX_CMR_RX_LMACS		0x468
#घोषणा BGX_CMRX_TX_FIFO_LEN		0x518
#घोषणा BGX_CMRX_TX_STAT0		0x600
#घोषणा BGX_CMRX_TX_STAT1		0x608
#घोषणा BGX_CMRX_TX_STAT2		0x610
#घोषणा BGX_CMRX_TX_STAT3		0x618
#घोषणा BGX_CMRX_TX_STAT4		0x620
#घोषणा BGX_CMRX_TX_STAT5		0x628
#घोषणा BGX_CMRX_TX_STAT6		0x630
#घोषणा BGX_CMRX_TX_STAT7		0x638
#घोषणा BGX_CMRX_TX_STAT8		0x640
#घोषणा BGX_CMRX_TX_STAT9		0x648
#घोषणा BGX_CMRX_TX_STAT10		0x650
#घोषणा BGX_CMRX_TX_STAT11		0x658
#घोषणा BGX_CMRX_TX_STAT12		0x660
#घोषणा BGX_CMRX_TX_STAT13		0x668
#घोषणा BGX_CMRX_TX_STAT14		0x670
#घोषणा BGX_CMRX_TX_STAT15		0x678
#घोषणा BGX_CMRX_TX_STAT16		0x680
#घोषणा BGX_CMRX_TX_STAT17		0x688
#घोषणा BGX_CMR_TX_LMACS		0x1000

#घोषणा BGX_SPUX_CONTROL1		0x10000
#घोषणा  SPU_CTL_LOW_POWER			BIT_ULL(11)
#घोषणा  SPU_CTL_LOOPBACK			BIT_ULL(14)
#घोषणा  SPU_CTL_RESET				BIT_ULL(15)
#घोषणा BGX_SPUX_STATUS1		0x10008
#घोषणा  SPU_STATUS1_RCV_LNK			BIT_ULL(2)
#घोषणा BGX_SPUX_STATUS2		0x10020
#घोषणा  SPU_STATUS2_RCVFLT			BIT_ULL(10)
#घोषणा BGX_SPUX_BX_STATUS		0x10028
#घोषणा  SPU_BX_STATUS_RX_ALIGN			BIT_ULL(12)
#घोषणा BGX_SPUX_BR_STATUS1		0x10030
#घोषणा  SPU_BR_STATUS_BLK_LOCK			BIT_ULL(0)
#घोषणा  SPU_BR_STATUS_RCV_LNK			BIT_ULL(12)
#घोषणा BGX_SPUX_BR_PMD_CRTL		0x10068
#घोषणा  SPU_PMD_CRTL_TRAIN_EN			BIT_ULL(1)
#घोषणा BGX_SPUX_BR_PMD_LP_CUP		0x10078
#घोषणा BGX_SPUX_BR_PMD_LD_CUP		0x10088
#घोषणा BGX_SPUX_BR_PMD_LD_REP		0x10090
#घोषणा BGX_SPUX_FEC_CONTROL		0x100A0
#घोषणा  SPU_FEC_CTL_FEC_EN			BIT_ULL(0)
#घोषणा  SPU_FEC_CTL_ERR_EN			BIT_ULL(1)
#घोषणा BGX_SPUX_AN_CONTROL		0x100C8
#घोषणा  SPU_AN_CTL_AN_EN			BIT_ULL(12)
#घोषणा  SPU_AN_CTL_XNP_EN			BIT_ULL(13)
#घोषणा BGX_SPUX_AN_ADV			0x100D8
#घोषणा BGX_SPUX_MISC_CONTROL		0x10218
#घोषणा  SPU_MISC_CTL_INTLV_RDISP		BIT_ULL(10)
#घोषणा  SPU_MISC_CTL_RX_DIS			BIT_ULL(12)
#घोषणा BGX_SPUX_INT			0x10220	/* +(0..3) << 20 */
#घोषणा BGX_SPUX_INT_W1S		0x10228
#घोषणा BGX_SPUX_INT_ENA_W1C		0x10230
#घोषणा BGX_SPUX_INT_ENA_W1S		0x10238
#घोषणा BGX_SPU_DBG_CONTROL		0x10300
#घोषणा  SPU_DBG_CTL_AN_ARB_LINK_CHK_EN		BIT_ULL(18)
#घोषणा  SPU_DBG_CTL_AN_NONCE_MCT_DIS		BIT_ULL(29)

#घोषणा BGX_SMUX_RX_INT			0x20000
#घोषणा BGX_SMUX_RX_FRM_CTL		0x20020
#घोषणा  BGX_PKT_RX_PTP_EN			BIT_ULL(12)
#घोषणा BGX_SMUX_RX_JABBER		0x20030
#घोषणा BGX_SMUX_RX_CTL			0x20048
#घोषणा  SMU_RX_CTL_STATUS			(3ull << 0)
#घोषणा BGX_SMUX_TX_APPEND		0x20100
#घोषणा  SMU_TX_APPEND_FCS_D			BIT_ULL(2)
#घोषणा BGX_SMUX_TX_PAUSE_PKT_TIME	0x20110
#घोषणा BGX_SMUX_TX_MIN_PKT		0x20118
#घोषणा BGX_SMUX_TX_PAUSE_PKT_INTERVAL	0x20120
#घोषणा BGX_SMUX_TX_PAUSE_ZERO		0x20138
#घोषणा BGX_SMUX_TX_INT			0x20140
#घोषणा BGX_SMUX_TX_CTL			0x20178
#घोषणा  SMU_TX_CTL_DIC_EN			BIT_ULL(0)
#घोषणा  SMU_TX_CTL_UNI_EN			BIT_ULL(1)
#घोषणा  SMU_TX_CTL_LNK_STATUS			(3ull << 4)
#घोषणा BGX_SMUX_TX_THRESH		0x20180
#घोषणा BGX_SMUX_CTL			0x20200
#घोषणा  SMU_CTL_RX_IDLE			BIT_ULL(0)
#घोषणा  SMU_CTL_TX_IDLE			BIT_ULL(1)
#घोषणा	BGX_SMUX_CBFC_CTL		0x20218
#घोषणा	RX_EN					BIT_ULL(0)
#घोषणा	TX_EN					BIT_ULL(1)
#घोषणा	BCK_EN					BIT_ULL(2)
#घोषणा	DRP_EN					BIT_ULL(3)

#घोषणा BGX_GMP_PCS_MRX_CTL		0x30000
#घोषणा	 PCS_MRX_CTL_RST_AN			BIT_ULL(9)
#घोषणा	 PCS_MRX_CTL_PWR_DN			BIT_ULL(11)
#घोषणा	 PCS_MRX_CTL_AN_EN			BIT_ULL(12)
#घोषणा	 PCS_MRX_CTL_LOOPBACK1			BIT_ULL(14)
#घोषणा	 PCS_MRX_CTL_RESET			BIT_ULL(15)
#घोषणा BGX_GMP_PCS_MRX_STATUS		0x30008
#घोषणा	 PCS_MRX_STATUS_LINK			BIT_ULL(2)
#घोषणा	 PCS_MRX_STATUS_AN_CPT			BIT_ULL(5)
#घोषणा BGX_GMP_PCS_ANX_ADV		0x30010
#घोषणा BGX_GMP_PCS_ANX_AN_RESULTS	0x30020
#घोषणा BGX_GMP_PCS_LINKX_TIMER		0x30040
#घोषणा PCS_LINKX_TIMER_COUNT			0x1E84
#घोषणा BGX_GMP_PCS_SGM_AN_ADV		0x30068
#घोषणा BGX_GMP_PCS_MISCX_CTL		0x30078
#घोषणा  PCS_MISC_CTL_MODE			BIT_ULL(8)
#घोषणा  PCS_MISC_CTL_DISP_EN			BIT_ULL(13)
#घोषणा  PCS_MISC_CTL_GMX_ENO			BIT_ULL(11)
#घोषणा  PCS_MISC_CTL_SAMP_PT_MASK	0x7Full
#घोषणा BGX_GMP_GMI_PRTX_CFG		0x38020
#घोषणा  GMI_PORT_CFG_SPEED			BIT_ULL(1)
#घोषणा  GMI_PORT_CFG_DUPLEX			BIT_ULL(2)
#घोषणा  GMI_PORT_CFG_SLOT_TIME			BIT_ULL(3)
#घोषणा  GMI_PORT_CFG_SPEED_MSB			BIT_ULL(8)
#घोषणा  GMI_PORT_CFG_RX_IDLE			BIT_ULL(12)
#घोषणा  GMI_PORT_CFG_TX_IDLE			BIT_ULL(13)
#घोषणा BGX_GMP_GMI_RXX_FRM_CTL		0x38028
#घोषणा BGX_GMP_GMI_RXX_JABBER		0x38038
#घोषणा BGX_GMP_GMI_TXX_THRESH		0x38210
#घोषणा BGX_GMP_GMI_TXX_APPEND		0x38218
#घोषणा BGX_GMP_GMI_TXX_SLOT		0x38220
#घोषणा BGX_GMP_GMI_TXX_BURST		0x38228
#घोषणा BGX_GMP_GMI_TXX_MIN_PKT		0x38240
#घोषणा BGX_GMP_GMI_TXX_SGMII_CTL	0x38300
#घोषणा BGX_GMP_GMI_TXX_INT		0x38500
#घोषणा BGX_GMP_GMI_TXX_INT_W1S		0x38508
#घोषणा BGX_GMP_GMI_TXX_INT_ENA_W1C	0x38510
#घोषणा BGX_GMP_GMI_TXX_INT_ENA_W1S	0x38518
#घोषणा  GMI_TXX_INT_PTP_LOST			BIT_ULL(4)
#घोषणा  GMI_TXX_INT_LATE_COL			BIT_ULL(3)
#घोषणा  GMI_TXX_INT_XSDEF			BIT_ULL(2)
#घोषणा  GMI_TXX_INT_XSCOL			BIT_ULL(1)
#घोषणा  GMI_TXX_INT_UNDFLW			BIT_ULL(0)

#घोषणा BGX_MSIX_VEC_0_29_ADDR		0x400000 /* +(0..29) << 4 */
#घोषणा BGX_MSIX_VEC_0_29_CTL		0x400008
#घोषणा BGX_MSIX_PBA_0			0x4F0000

/* MSI-X पूर्णांकerrupts */
#घोषणा BGX_MSIX_VECTORS	30
#घोषणा BGX_LMAC_VEC_OFFSET	7
#घोषणा BGX_MSIX_VEC_SHIFT	4

#घोषणा CMRX_INT		0
#घोषणा SPUX_INT		1
#घोषणा SMUX_RX_INT		2
#घोषणा SMUX_TX_INT		3
#घोषणा GMPX_PCS_INT		4
#घोषणा GMPX_GMI_RX_INT		5
#घोषणा GMPX_GMI_TX_INT		6
#घोषणा CMR_MEM_INT		28
#घोषणा SPU_MEM_INT		29

#घोषणा LMAC_INTR_LINK_UP	BIT(0)
#घोषणा LMAC_INTR_LINK_DOWN	BIT(1)

#घोषणा BGX_XCAST_BCAST_ACCEPT  BIT(0)
#घोषणा BGX_XCAST_MCAST_ACCEPT  BIT(1)
#घोषणा BGX_XCAST_MCAST_FILTER  BIT(2)

व्योम bgx_set_dmac_cam_filter(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmacid, u64 mac, u8 vf);
व्योम bgx_reset_xcast_mode(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmacid, u8 vf);
व्योम bgx_set_xcast_mode(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmacid, u8 mode);
व्योम octeon_mdiobus_क्रमce_mod_depencency(व्योम);
व्योम bgx_lmac_rx_tx_enable(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmacid, bool enable);
व्योम bgx_add_dmac_addr(u64 dmac, पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmac);
अचिन्हित bgx_get_map(पूर्णांक node);
पूर्णांक bgx_get_lmac_count(पूर्णांक node, पूर्णांक bgx);
स्थिर u8 *bgx_get_lmac_mac(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmacid);
व्योम bgx_set_lmac_mac(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmacid, स्थिर u8 *mac);
व्योम bgx_get_lmac_link_state(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmacid, व्योम *status);
व्योम bgx_lmac_पूर्णांकernal_loopback(पूर्णांक node, पूर्णांक bgx_idx,
				पूर्णांक lmac_idx, bool enable);
व्योम bgx_config_बारtamping(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmacid, bool enable);
व्योम bgx_lmac_get_pfc(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmacid, व्योम *छोड़ो);
व्योम bgx_lmac_set_pfc(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmacid, व्योम *छोड़ो);

व्योम xcv_init_hw(व्योम);
व्योम xcv_setup_link(bool link_up, पूर्णांक link_speed);

u64 bgx_get_rx_stats(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmac, पूर्णांक idx);
u64 bgx_get_tx_stats(पूर्णांक node, पूर्णांक bgx_idx, पूर्णांक lmac, पूर्णांक idx);
#घोषणा BGX_RX_STATS_COUNT 11
#घोषणा BGX_TX_STATS_COUNT 18

काष्ठा bgx_stats अणु
	u64 rx_stats[BGX_RX_STATS_COUNT];
	u64 tx_stats[BGX_TX_STATS_COUNT];
पूर्ण;

क्रमागत LMAC_TYPE अणु
	BGX_MODE_SGMII = 0, /* 1 lane, 1.250 Gbaud */
	BGX_MODE_XAUI = 1,  /* 4 lanes, 3.125 Gbaud */
	BGX_MODE_DXAUI = 1, /* 4 lanes, 6.250 Gbaud */
	BGX_MODE_RXAUI = 2, /* 2 lanes, 6.250 Gbaud */
	BGX_MODE_XFI = 3,   /* 1 lane, 10.3125 Gbaud */
	BGX_MODE_XLAUI = 4, /* 4 lanes, 10.3125 Gbaud */
	BGX_MODE_10G_KR = 3,/* 1 lane, 10.3125 Gbaud */
	BGX_MODE_40G_KR = 4,/* 4 lanes, 10.3125 Gbaud */
	BGX_MODE_RGMII = 5,
	BGX_MODE_QSGMII = 6,
	BGX_MODE_INVALID = 7,
पूर्ण;

#पूर्ण_अगर /* THUNDER_BGX_H */
