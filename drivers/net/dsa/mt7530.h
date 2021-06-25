<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2017 Sean Wang <sean.wang@mediatek.com>
 */

#अगर_अघोषित __MT7530_H
#घोषणा __MT7530_H

#घोषणा MT7530_NUM_PORTS		7
#घोषणा MT7530_CPU_PORT			6
#घोषणा MT7530_NUM_FDB_RECORDS		2048
#घोषणा MT7530_ALL_MEMBERS		0xff

#घोषणा MTK_HDR_LEN	4
#घोषणा MT7530_MAX_MTU	(15 * 1024 - ETH_HLEN - ETH_FCS_LEN - MTK_HDR_LEN)

क्रमागत mt753x_id अणु
	ID_MT7530 = 0,
	ID_MT7621 = 1,
	ID_MT7531 = 2,
पूर्ण;

#घोषणा	NUM_TRGMII_CTRL			5

#घोषणा TRGMII_BASE(x)			(0x10000 + (x))

/* Registers to ethsys access */
#घोषणा ETHSYS_CLKCFG0			0x2c
#घोषणा  ETHSYS_TRGMII_CLK_SEL362_5	BIT(11)

#घोषणा SYSC_REG_RSTCTRL		0x34
#घोषणा  RESET_MCM			BIT(2)

/* Registers to mac क्रमward control क्रम unknown frames */
#घोषणा MT7530_MFC			0x10
#घोषणा  BC_FFP(x)			(((x) & 0xff) << 24)
#घोषणा  BC_FFP_MASK			BC_FFP(~0)
#घोषणा  UNM_FFP(x)			(((x) & 0xff) << 16)
#घोषणा  UNM_FFP_MASK			UNM_FFP(~0)
#घोषणा  UNU_FFP(x)			(((x) & 0xff) << 8)
#घोषणा  UNU_FFP_MASK			UNU_FFP(~0)
#घोषणा  CPU_EN				BIT(7)
#घोषणा  CPU_PORT(x)			((x) << 4)
#घोषणा  CPU_MASK			(0xf << 4)
#घोषणा  MIRROR_EN			BIT(3)
#घोषणा  MIRROR_PORT(x)			((x) & 0x7)
#घोषणा  MIRROR_MASK			0x7

/* Registers क्रम CPU क्रमward control */
#घोषणा MT7531_CFC			0x4
#घोषणा  MT7531_MIRROR_EN		BIT(19)
#घोषणा  MT7531_MIRROR_MASK		(MIRROR_MASK << 16)
#घोषणा  MT7531_MIRROR_PORT_GET(x)	(((x) >> 16) & MIRROR_MASK)
#घोषणा  MT7531_MIRROR_PORT_SET(x)	(((x) & MIRROR_MASK) << 16)
#घोषणा  MT7531_CPU_PMAP_MASK		GENMASK(7, 0)

#घोषणा MT753X_MIRROR_REG(id)		(((id) == ID_MT7531) ? \
					 MT7531_CFC : MT7530_MFC)
#घोषणा MT753X_MIRROR_EN(id)		(((id) == ID_MT7531) ? \
					 MT7531_MIRROR_EN : MIRROR_EN)
#घोषणा MT753X_MIRROR_MASK(id)		(((id) == ID_MT7531) ? \
					 MT7531_MIRROR_MASK : MIRROR_MASK)

/* Registers क्रम BPDU and PAE frame control*/
#घोषणा MT753X_BPC			0x24
#घोषणा  MT753X_BPDU_PORT_FW_MASK	GENMASK(2, 0)

क्रमागत mt753x_bpdu_port_fw अणु
	MT753X_BPDU_FOLLOW_MFC,
	MT753X_BPDU_CPU_EXCLUDE = 4,
	MT753X_BPDU_CPU_INCLUDE = 5,
	MT753X_BPDU_CPU_ONLY = 6,
	MT753X_BPDU_DROP = 7,
पूर्ण;

/* Registers क्रम address table access */
#घोषणा MT7530_ATA1			0x74
#घोषणा  STATIC_EMP			0
#घोषणा  STATIC_ENT			3
#घोषणा MT7530_ATA2			0x78

/* Register क्रम address table ग_लिखो data */
#घोषणा MT7530_ATWD			0x7c

/* Register क्रम address table control */
#घोषणा MT7530_ATC			0x80
#घोषणा  ATC_HASH			(((x) & 0xfff) << 16)
#घोषणा  ATC_BUSY			BIT(15)
#घोषणा  ATC_SRCH_END			BIT(14)
#घोषणा  ATC_SRCH_HIT			BIT(13)
#घोषणा  ATC_INVALID			BIT(12)
#घोषणा  ATC_MAT(x)			(((x) & 0xf) << 8)
#घोषणा  ATC_MAT_MACTAB			ATC_MAT(0)

क्रमागत mt7530_fdb_cmd अणु
	MT7530_FDB_READ	= 0,
	MT7530_FDB_WRITE = 1,
	MT7530_FDB_FLUSH = 2,
	MT7530_FDB_START = 4,
	MT7530_FDB_NEXT = 5,
पूर्ण;

/* Registers क्रम table search पढ़ो address */
#घोषणा MT7530_TSRA1			0x84
#घोषणा  MAC_BYTE_0			24
#घोषणा  MAC_BYTE_1			16
#घोषणा  MAC_BYTE_2			8
#घोषणा  MAC_BYTE_3			0
#घोषणा  MAC_BYTE_MASK			0xff

#घोषणा MT7530_TSRA2			0x88
#घोषणा  MAC_BYTE_4			24
#घोषणा  MAC_BYTE_5			16
#घोषणा  CVID				0
#घोषणा  CVID_MASK			0xfff

#घोषणा MT7530_ATRD			0x8C
#घोषणा	 AGE_TIMER			24
#घोषणा  AGE_TIMER_MASK			0xff
#घोषणा  PORT_MAP			4
#घोषणा  PORT_MAP_MASK			0xff
#घोषणा  ENT_STATUS			2
#घोषणा  ENT_STATUS_MASK		0x3

/* Register क्रम vlan table control */
#घोषणा MT7530_VTCR			0x90
#घोषणा  VTCR_BUSY			BIT(31)
#घोषणा  VTCR_INVALID			BIT(16)
#घोषणा  VTCR_FUNC(x)			(((x) & 0xf) << 12)
#घोषणा  VTCR_VID			((x) & 0xfff)

क्रमागत mt7530_vlan_cmd अणु
	/* Read/Write the specअगरied VID entry from VAWD रेजिस्टर based
	 * on VID.
	 */
	MT7530_VTCR_RD_VID = 0,
	MT7530_VTCR_WR_VID = 1,
पूर्ण;

/* Register क्रम setup vlan and acl ग_लिखो data */
#घोषणा MT7530_VAWD1			0x94
#घोषणा  PORT_STAG			BIT(31)
/* Independent VLAN Learning */
#घोषणा  IVL_MAC			BIT(30)
/* Per VLAN Egress Tag Control */
#घोषणा  VTAG_EN			BIT(28)
/* VLAN Member Control */
#घोषणा  PORT_MEM(x)			(((x) & 0xff) << 16)
/* VLAN Entry Valid */
#घोषणा  VLAN_VALID			BIT(0)
#घोषणा  PORT_MEM_SHFT			16
#घोषणा  PORT_MEM_MASK			0xff

#घोषणा MT7530_VAWD2			0x98
/* Egress Tag Control */
#घोषणा  ETAG_CTRL_P(p, x)		(((x) & 0x3) << ((p) << 1))
#घोषणा  ETAG_CTRL_P_MASK(p)		ETAG_CTRL_P(p, 3)

क्रमागत mt7530_vlan_egress_attr अणु
	MT7530_VLAN_EGRESS_UNTAG = 0,
	MT7530_VLAN_EGRESS_TAG = 2,
	MT7530_VLAN_EGRESS_STACK = 3,
पूर्ण;

/* Register क्रम address age control */
#घोषणा MT7530_AAC			0xa0
/* Disable ageing */
#घोषणा  AGE_DIS			BIT(20)
/* Age count */
#घोषणा  AGE_CNT_MASK			GENMASK(19, 12)
#घोषणा  AGE_CNT_MAX			0xff
#घोषणा  AGE_CNT(x)			(AGE_CNT_MASK & ((x) << 12))
/* Age unit */
#घोषणा  AGE_UNIT_MASK			GENMASK(11, 0)
#घोषणा  AGE_UNIT_MAX			0xfff
#घोषणा  AGE_UNIT(x)			(AGE_UNIT_MASK & (x))

/* Register क्रम port STP state control */
#घोषणा MT7530_SSP_P(x)			(0x2000 + ((x) * 0x100))
#घोषणा  FID_PST(x)			((x) & 0x3)
#घोषणा  FID_PST_MASK			FID_PST(0x3)

क्रमागत mt7530_stp_state अणु
	MT7530_STP_DISABLED = 0,
	MT7530_STP_BLOCKING = 1,
	MT7530_STP_LISTENING = 1,
	MT7530_STP_LEARNING = 2,
	MT7530_STP_FORWARDING  = 3
पूर्ण;

/* Register क्रम port control */
#घोषणा MT7530_PCR_P(x)			(0x2004 + ((x) * 0x100))
#घोषणा  PORT_TX_MIR			BIT(9)
#घोषणा  PORT_RX_MIR			BIT(8)
#घोषणा  PORT_VLAN(x)			((x) & 0x3)

क्रमागत mt7530_port_mode अणु
	/* Port Matrix Mode: Frames are क्रमwarded by the PCR_MATRIX members. */
	MT7530_PORT_MATRIX_MODE = PORT_VLAN(0),

	/* Fallback Mode: Forward received frames with ingress ports that करो
	 * not beदीर्घ to the VLAN member. Frames whose VID is not listed on
	 * the VLAN table are क्रमwarded by the PCR_MATRIX members.
	 */
	MT7530_PORT_FALLBACK_MODE = PORT_VLAN(1),

	/* Security Mode: Discard any frame due to ingress membership
	 * violation or VID missed on the VLAN table.
	 */
	MT7530_PORT_SECURITY_MODE = PORT_VLAN(3),
पूर्ण;

#घोषणा  PCR_MATRIX(x)			(((x) & 0xff) << 16)
#घोषणा  PORT_PRI(x)			(((x) & 0x7) << 24)
#घोषणा  EG_TAG(x)			(((x) & 0x3) << 28)
#घोषणा  PCR_MATRIX_MASK		PCR_MATRIX(0xff)
#घोषणा  PCR_MATRIX_CLR			PCR_MATRIX(0)
#घोषणा  PCR_PORT_VLAN_MASK		PORT_VLAN(3)

/* Register क्रम port security control */
#घोषणा MT7530_PSC_P(x)			(0x200c + ((x) * 0x100))
#घोषणा  SA_DIS				BIT(4)

/* Register क्रम port vlan control */
#घोषणा MT7530_PVC_P(x)			(0x2010 + ((x) * 0x100))
#घोषणा  PORT_SPEC_TAG			BIT(5)
#घोषणा  PVC_EG_TAG(x)			(((x) & 0x7) << 8)
#घोषणा  PVC_EG_TAG_MASK		PVC_EG_TAG(7)
#घोषणा  VLAN_ATTR(x)			(((x) & 0x3) << 6)
#घोषणा  VLAN_ATTR_MASK			VLAN_ATTR(3)

क्रमागत mt7530_vlan_port_eg_tag अणु
	MT7530_VLAN_EG_DISABLED = 0,
	MT7530_VLAN_EG_CONSISTENT = 1,
पूर्ण;

क्रमागत mt7530_vlan_port_attr अणु
	MT7530_VLAN_USER = 0,
	MT7530_VLAN_TRANSPARENT = 3,
पूर्ण;

#घोषणा  STAG_VPID			(((x) & 0xffff) << 16)

/* Register क्रम port port-and-protocol based vlan 1 control */
#घोषणा MT7530_PPBV1_P(x)		(0x2014 + ((x) * 0x100))
#घोषणा  G0_PORT_VID(x)			(((x) & 0xfff) << 0)
#घोषणा  G0_PORT_VID_MASK		G0_PORT_VID(0xfff)
#घोषणा  G0_PORT_VID_DEF		G0_PORT_VID(1)

/* Register क्रम port MAC control रेजिस्टर */
#घोषणा MT7530_PMCR_P(x)		(0x3000 + ((x) * 0x100))
#घोषणा  PMCR_IFG_XMIT(x)		(((x) & 0x3) << 18)
#घोषणा  PMCR_EXT_PHY			BIT(17)
#घोषणा  PMCR_MAC_MODE			BIT(16)
#घोषणा  PMCR_FORCE_MODE		BIT(15)
#घोषणा  PMCR_TX_EN			BIT(14)
#घोषणा  PMCR_RX_EN			BIT(13)
#घोषणा  PMCR_BACKOFF_EN		BIT(9)
#घोषणा  PMCR_BACKPR_EN			BIT(8)
#घोषणा  PMCR_FORCE_EEE1G		BIT(7)
#घोषणा  PMCR_FORCE_EEE100		BIT(6)
#घोषणा  PMCR_TX_FC_EN			BIT(5)
#घोषणा  PMCR_RX_FC_EN			BIT(4)
#घोषणा  PMCR_FORCE_SPEED_1000		BIT(3)
#घोषणा  PMCR_FORCE_SPEED_100		BIT(2)
#घोषणा  PMCR_FORCE_FDX			BIT(1)
#घोषणा  PMCR_FORCE_LNK			BIT(0)
#घोषणा  PMCR_SPEED_MASK		(PMCR_FORCE_SPEED_100 | \
					 PMCR_FORCE_SPEED_1000)
#घोषणा  MT7531_FORCE_LNK		BIT(31)
#घोषणा  MT7531_FORCE_SPD		BIT(30)
#घोषणा  MT7531_FORCE_DPX		BIT(29)
#घोषणा  MT7531_FORCE_RX_FC		BIT(28)
#घोषणा  MT7531_FORCE_TX_FC		BIT(27)
#घोषणा  MT7531_FORCE_MODE		(MT7531_FORCE_LNK | \
					 MT7531_FORCE_SPD | \
					 MT7531_FORCE_DPX | \
					 MT7531_FORCE_RX_FC | \
					 MT7531_FORCE_TX_FC)
#घोषणा  PMCR_FORCE_MODE_ID(id)		(((id) == ID_MT7531) ? \
					 MT7531_FORCE_MODE : \
					 PMCR_FORCE_MODE)
#घोषणा  PMCR_LINK_SETTINGS_MASK	(PMCR_TX_EN | PMCR_FORCE_SPEED_1000 | \
					 PMCR_RX_EN | PMCR_FORCE_SPEED_100 | \
					 PMCR_TX_FC_EN | PMCR_RX_FC_EN | \
					 PMCR_FORCE_FDX | PMCR_FORCE_LNK | \
					 PMCR_FORCE_EEE1G | PMCR_FORCE_EEE100)
#घोषणा  PMCR_CPU_PORT_SETTING(id)	(PMCR_FORCE_MODE_ID((id)) | \
					 PMCR_IFG_XMIT(1) | PMCR_MAC_MODE | \
					 PMCR_BACKOFF_EN | PMCR_BACKPR_EN | \
					 PMCR_TX_EN | PMCR_RX_EN | \
					 PMCR_TX_FC_EN | PMCR_RX_FC_EN | \
					 PMCR_FORCE_SPEED_1000 | \
					 PMCR_FORCE_FDX | PMCR_FORCE_LNK)

#घोषणा MT7530_PMEEECR_P(x)		(0x3004 + (x) * 0x100)
#घोषणा  WAKEUP_TIME_1000(x)		(((x) & 0xFF) << 24)
#घोषणा  WAKEUP_TIME_100(x)		(((x) & 0xFF) << 16)
#घोषणा  LPI_THRESH_MASK		GENMASK(15, 4)
#घोषणा  LPI_THRESH_SHT			4
#घोषणा  SET_LPI_THRESH(x)		(((x) << LPI_THRESH_SHT) & LPI_THRESH_MASK)
#घोषणा  GET_LPI_THRESH(x)		(((x) & LPI_THRESH_MASK) >> LPI_THRESH_SHT)
#घोषणा  LPI_MODE_EN			BIT(0)

#घोषणा MT7530_PMSR_P(x)		(0x3008 + (x) * 0x100)
#घोषणा  PMSR_EEE1G			BIT(7)
#घोषणा  PMSR_EEE100M			BIT(6)
#घोषणा  PMSR_RX_FC			BIT(5)
#घोषणा  PMSR_TX_FC			BIT(4)
#घोषणा  PMSR_SPEED_1000		BIT(3)
#घोषणा  PMSR_SPEED_100			BIT(2)
#घोषणा  PMSR_SPEED_10			0x00
#घोषणा  PMSR_SPEED_MASK		(PMSR_SPEED_100 | PMSR_SPEED_1000)
#घोषणा  PMSR_DPX			BIT(1)
#घोषणा  PMSR_LINK			BIT(0)

/* Register क्रम port debug count */
#घोषणा MT7531_DBG_CNT(x)		(0x3018 + (x) * 0x100)
#घोषणा  MT7531_DIS_CLR			BIT(31)

#घोषणा MT7530_GMACCR			0x30e0
#घोषणा  MAX_RX_JUMBO(x)		((x) << 2)
#घोषणा  MAX_RX_JUMBO_MASK		GENMASK(5, 2)
#घोषणा  MAX_RX_PKT_LEN_MASK		GENMASK(1, 0)
#घोषणा  MAX_RX_PKT_LEN_1522		0x0
#घोषणा  MAX_RX_PKT_LEN_1536		0x1
#घोषणा  MAX_RX_PKT_LEN_1552		0x2
#घोषणा  MAX_RX_PKT_LEN_JUMBO		0x3

/* Register क्रम MIB */
#घोषणा MT7530_PORT_MIB_COUNTER(x)	(0x4000 + (x) * 0x100)
#घोषणा MT7530_MIB_CCR			0x4fe0
#घोषणा  CCR_MIB_ENABLE			BIT(31)
#घोषणा  CCR_RX_OCT_CNT_GOOD		BIT(7)
#घोषणा  CCR_RX_OCT_CNT_BAD		BIT(6)
#घोषणा  CCR_TX_OCT_CNT_GOOD		BIT(5)
#घोषणा  CCR_TX_OCT_CNT_BAD		BIT(4)
#घोषणा  CCR_MIB_FLUSH			(CCR_RX_OCT_CNT_GOOD | \
					 CCR_RX_OCT_CNT_BAD | \
					 CCR_TX_OCT_CNT_GOOD | \
					 CCR_TX_OCT_CNT_BAD)
#घोषणा  CCR_MIB_ACTIVATE		(CCR_MIB_ENABLE | \
					 CCR_RX_OCT_CNT_GOOD | \
					 CCR_RX_OCT_CNT_BAD | \
					 CCR_TX_OCT_CNT_GOOD | \
					 CCR_TX_OCT_CNT_BAD)

/* MT7531 SGMII रेजिस्टर group */
#घोषणा MT7531_SGMII_REG_BASE		0x5000
#घोषणा MT7531_SGMII_REG(p, r)		(MT7531_SGMII_REG_BASE + \
					((p) - 5) * 0x1000 + (r))

/* Register क्रमSGMII PCS_CONTROL_1 */
#घोषणा MT7531_PCS_CONTROL_1(p)		MT7531_SGMII_REG(p, 0x00)
#घोषणा  MT7531_SGMII_LINK_STATUS	BIT(18)
#घोषणा  MT7531_SGMII_AN_ENABLE		BIT(12)
#घोषणा  MT7531_SGMII_AN_RESTART	BIT(9)

/* Register क्रम SGMII PCS_SPPED_ABILITY */
#घोषणा MT7531_PCS_SPEED_ABILITY(p)	MT7531_SGMII_REG(p, 0x08)
#घोषणा  MT7531_SGMII_TX_CONFIG_MASK	GENMASK(15, 0)
#घोषणा  MT7531_SGMII_TX_CONFIG		BIT(0)

/* Register क्रम SGMII_MODE */
#घोषणा MT7531_SGMII_MODE(p)		MT7531_SGMII_REG(p, 0x20)
#घोषणा  MT7531_SGMII_REMOTE_FAULT_DIS	BIT(8)
#घोषणा  MT7531_SGMII_IF_MODE_MASK	GENMASK(5, 1)
#घोषणा  MT7531_SGMII_FORCE_DUPLEX	BIT(4)
#घोषणा  MT7531_SGMII_FORCE_SPEED_MASK	GENMASK(3, 2)
#घोषणा  MT7531_SGMII_FORCE_SPEED_1000	BIT(3)
#घोषणा  MT7531_SGMII_FORCE_SPEED_100	BIT(2)
#घोषणा  MT7531_SGMII_FORCE_SPEED_10	0
#घोषणा  MT7531_SGMII_SPEED_DUPLEX_AN	BIT(1)

क्रमागत mt7531_sgmii_क्रमce_duplex अणु
	MT7531_SGMII_FORCE_FULL_DUPLEX = 0,
	MT7531_SGMII_FORCE_HALF_DUPLEX = 0x10,
पूर्ण;

/* Fields of QPHY_PWR_STATE_CTRL */
#घोषणा MT7531_QPHY_PWR_STATE_CTRL(p)	MT7531_SGMII_REG(p, 0xe8)
#घोषणा  MT7531_SGMII_PHYA_PWD		BIT(4)

/* Values of SGMII SPEED */
#घोषणा MT7531_PHYA_CTRL_SIGNAL3(p)	MT7531_SGMII_REG(p, 0x128)
#घोषणा  MT7531_RG_TPHY_SPEED_MASK	(BIT(2) | BIT(3))
#घोषणा  MT7531_RG_TPHY_SPEED_1_25G	0x0
#घोषणा  MT7531_RG_TPHY_SPEED_3_125G	BIT(2)

/* Register क्रम प्रणाली reset */
#घोषणा MT7530_SYS_CTRL			0x7000
#घोषणा  SYS_CTRL_PHY_RST		BIT(2)
#घोषणा  SYS_CTRL_SW_RST		BIT(1)
#घोषणा  SYS_CTRL_REG_RST		BIT(0)

/* Register क्रम PHY Indirect Access Control */
#घोषणा MT7531_PHY_IAC			0x701C
#घोषणा  MT7531_PHY_ACS_ST		BIT(31)
#घोषणा  MT7531_MDIO_REG_ADDR_MASK	(0x1f << 25)
#घोषणा  MT7531_MDIO_PHY_ADDR_MASK	(0x1f << 20)
#घोषणा  MT7531_MDIO_CMD_MASK		(0x3 << 18)
#घोषणा  MT7531_MDIO_ST_MASK		(0x3 << 16)
#घोषणा  MT7531_MDIO_RW_DATA_MASK	(0xffff)
#घोषणा  MT7531_MDIO_REG_ADDR(x)	(((x) & 0x1f) << 25)
#घोषणा  MT7531_MDIO_DEV_ADDR(x)	(((x) & 0x1f) << 25)
#घोषणा  MT7531_MDIO_PHY_ADDR(x)	(((x) & 0x1f) << 20)
#घोषणा  MT7531_MDIO_CMD(x)		(((x) & 0x3) << 18)
#घोषणा  MT7531_MDIO_ST(x)		(((x) & 0x3) << 16)

क्रमागत mt7531_phy_iac_cmd अणु
	MT7531_MDIO_ADDR = 0,
	MT7531_MDIO_WRITE = 1,
	MT7531_MDIO_READ = 2,
	MT7531_MDIO_READ_CL45 = 3,
पूर्ण;

/* MDIO_ST: MDIO start field */
क्रमागत mt7531_mdio_st अणु
	MT7531_MDIO_ST_CL45 = 0,
	MT7531_MDIO_ST_CL22 = 1,
पूर्ण;

#घोषणा  MT7531_MDIO_CL22_READ		(MT7531_MDIO_ST(MT7531_MDIO_ST_CL22) | \
					 MT7531_MDIO_CMD(MT7531_MDIO_READ))
#घोषणा  MT7531_MDIO_CL22_WRITE		(MT7531_MDIO_ST(MT7531_MDIO_ST_CL22) | \
					 MT7531_MDIO_CMD(MT7531_MDIO_WRITE))
#घोषणा  MT7531_MDIO_CL45_ADDR		(MT7531_MDIO_ST(MT7531_MDIO_ST_CL45) | \
					 MT7531_MDIO_CMD(MT7531_MDIO_ADDR))
#घोषणा  MT7531_MDIO_CL45_READ		(MT7531_MDIO_ST(MT7531_MDIO_ST_CL45) | \
					 MT7531_MDIO_CMD(MT7531_MDIO_READ))
#घोषणा  MT7531_MDIO_CL45_WRITE		(MT7531_MDIO_ST(MT7531_MDIO_ST_CL45) | \
					 MT7531_MDIO_CMD(MT7531_MDIO_WRITE))

/* Register क्रम RGMII घड़ी phase */
#घोषणा MT7531_CLKGEN_CTRL		0x7500
#घोषणा  CLK_SKEW_OUT(x)		(((x) & 0x3) << 8)
#घोषणा  CLK_SKEW_OUT_MASK		GENMASK(9, 8)
#घोषणा  CLK_SKEW_IN(x)			(((x) & 0x3) << 6)
#घोषणा  CLK_SKEW_IN_MASK		GENMASK(7, 6)
#घोषणा  RXCLK_NO_DELAY			BIT(5)
#घोषणा  TXCLK_NO_REVERSE		BIT(4)
#घोषणा  GP_MODE(x)			(((x) & 0x3) << 1)
#घोषणा  GP_MODE_MASK			GENMASK(2, 1)
#घोषणा  GP_CLK_EN			BIT(0)

क्रमागत mt7531_gp_mode अणु
	MT7531_GP_MODE_RGMII = 0,
	MT7531_GP_MODE_MII = 1,
	MT7531_GP_MODE_REV_MII = 2
पूर्ण;

क्रमागत mt7531_clk_skew अणु
	MT7531_CLK_SKEW_NO_CHG = 0,
	MT7531_CLK_SKEW_DLY_100PPS = 1,
	MT7531_CLK_SKEW_DLY_200PPS = 2,
	MT7531_CLK_SKEW_REVERSE = 3,
पूर्ण;

/* Register क्रम hw trap status */
#घोषणा MT7530_HWTRAP			0x7800
#घोषणा  HWTRAP_XTAL_MASK		(BIT(10) | BIT(9))
#घोषणा  HWTRAP_XTAL_25MHZ		(BIT(10) | BIT(9))
#घोषणा  HWTRAP_XTAL_40MHZ		(BIT(10))
#घोषणा  HWTRAP_XTAL_20MHZ		(BIT(9))

#घोषणा MT7531_HWTRAP			0x7800
#घोषणा  HWTRAP_XTAL_FSEL_MASK		BIT(7)
#घोषणा  HWTRAP_XTAL_FSEL_25MHZ		BIT(7)
#घोषणा  HWTRAP_XTAL_FSEL_40MHZ		0
/* Unique fields of (M)HWSTRAP क्रम MT7531 */
#घोषणा  XTAL_FSEL_S			7
#घोषणा  XTAL_FSEL_M			BIT(7)
#घोषणा  PHY_EN				BIT(6)
#घोषणा  CHG_STRAP			BIT(8)

/* Register क्रम hw trap modअगरication */
#घोषणा MT7530_MHWTRAP			0x7804
#घोषणा  MHWTRAP_PHY0_SEL		BIT(20)
#घोषणा  MHWTRAP_MANUAL			BIT(16)
#घोषणा  MHWTRAP_P5_MAC_SEL		BIT(13)
#घोषणा  MHWTRAP_P6_DIS			BIT(8)
#घोषणा  MHWTRAP_P5_RGMII_MODE		BIT(7)
#घोषणा  MHWTRAP_P5_DIS			BIT(6)
#घोषणा  MHWTRAP_PHY_ACCESS		BIT(5)

/* Register क्रम TOP संकेत control */
#घोषणा MT7530_TOP_SIG_CTRL		0x7808
#घोषणा  TOP_SIG_CTRL_NORMAL		(BIT(17) | BIT(16))

#घोषणा MT7531_TOP_SIG_SR		0x780c
#घोषणा  PAD_DUAL_SGMII_EN		BIT(1)
#घोषणा  PAD_MCM_SMI_EN			BIT(0)

#घोषणा MT7530_IO_DRV_CR		0x7810
#घोषणा  P5_IO_CLK_DRV(x)		((x) & 0x3)
#घोषणा  P5_IO_DATA_DRV(x)		(((x) & 0x3) << 4)

#घोषणा MT7531_CHIP_REV			0x781C

#घोषणा MT7531_PLLGP_EN			0x7820
#घोषणा  EN_COREPLL			BIT(2)
#घोषणा  SW_CLKSW			BIT(1)
#घोषणा  SW_PLLGP			BIT(0)

#घोषणा MT7530_P6ECR			0x7830
#घोषणा  P6_INTF_MODE_MASK		0x3
#घोषणा  P6_INTF_MODE(x)		((x) & 0x3)

#घोषणा MT7531_PLLGP_CR0		0x78a8
#घोषणा  RG_COREPLL_EN			BIT(22)
#घोषणा  RG_COREPLL_POSDIV_S		23
#घोषणा  RG_COREPLL_POSDIV_M		0x3800000
#घोषणा  RG_COREPLL_SDM_PCW_S		1
#घोषणा  RG_COREPLL_SDM_PCW_M		0x3ffffe
#घोषणा  RG_COREPLL_SDM_PCW_CHG		BIT(0)

/* Registers क्रम RGMII and SGMII PLL घड़ी */
#घोषणा MT7531_ANA_PLLGP_CR2		0x78b0
#घोषणा MT7531_ANA_PLLGP_CR5		0x78bc

/* Registers क्रम TRGMII on the both side */
#घोषणा MT7530_TRGMII_RCK_CTRL		0x7a00
#घोषणा  RX_RST				BIT(31)
#घोषणा  RXC_DQSISEL			BIT(30)
#घोषणा  DQSI1_TAP_MASK			(0x7f << 8)
#घोषणा  DQSI0_TAP_MASK			0x7f
#घोषणा  DQSI1_TAP(x)			(((x) & 0x7f) << 8)
#घोषणा  DQSI0_TAP(x)			((x) & 0x7f)

#घोषणा MT7530_TRGMII_RCK_RTT		0x7a04
#घोषणा  DQS1_GATE			BIT(31)
#घोषणा  DQS0_GATE			BIT(30)

#घोषणा MT7530_TRGMII_RD(x)		(0x7a10 + (x) * 8)
#घोषणा  BSLIP_EN			BIT(31)
#घोषणा  EDGE_CHK			BIT(30)
#घोषणा  RD_TAP_MASK			0x7f
#घोषणा  RD_TAP(x)			((x) & 0x7f)

#घोषणा MT7530_TRGMII_TXCTRL		0x7a40
#घोषणा  TRAIN_TXEN			BIT(31)
#घोषणा  TXC_INV			BIT(30)
#घोषणा  TX_RST				BIT(28)

#घोषणा MT7530_TRGMII_TD_ODT(i)		(0x7a54 + 8 * (i))
#घोषणा  TD_DM_DRVP(x)			((x) & 0xf)
#घोषणा  TD_DM_DRVN(x)			(((x) & 0xf) << 4)

#घोषणा MT7530_TRGMII_TCK_CTRL		0x7a78
#घोषणा  TCK_TAP(x)			(((x) & 0xf) << 8)

#घोषणा MT7530_P5RGMIIRXCR		0x7b00
#घोषणा  CSR_RGMII_EDGE_ALIGN		BIT(8)
#घोषणा  CSR_RGMII_RXC_0DEG_CFG(x)	((x) & 0xf)

#घोषणा MT7530_P5RGMIITXCR		0x7b04
#घोषणा  CSR_RGMII_TXC_CFG(x)		((x) & 0x1f)

/* Registers क्रम GPIO mode */
#घोषणा MT7531_GPIO_MODE0		0x7c0c
#घोषणा  MT7531_GPIO0_MASK		GENMASK(3, 0)
#घोषणा  MT7531_GPIO0_INTERRUPT		1

#घोषणा MT7531_GPIO_MODE1		0x7c10
#घोषणा  MT7531_GPIO11_RG_RXD2_MASK	GENMASK(15, 12)
#घोषणा  MT7531_EXT_P_MDC_11		(2 << 12)
#घोषणा  MT7531_GPIO12_RG_RXD3_MASK	GENMASK(19, 16)
#घोषणा  MT7531_EXT_P_MDIO_12		(2 << 16)

/* Registers क्रम LED GPIO control (MT7530 only)
 * All रेजिस्टरs follow this pattern:
 * [ 2: 0]  port 0
 * [ 6: 4]  port 1
 * [10: 8]  port 2
 * [14:12]  port 3
 * [18:16]  port 4
 */

/* LED enable, 0: Disable, 1: Enable (Default) */
#घोषणा MT7530_LED_EN			0x7d00
/* LED mode, 0: GPIO mode, 1: PHY mode (Default) */
#घोषणा MT7530_LED_IO_MODE		0x7d04
/* GPIO direction, 0: Input, 1: Output */
#घोषणा MT7530_LED_GPIO_सूची		0x7d10
/* GPIO output enable, 0: Disable, 1: Enable */
#घोषणा MT7530_LED_GPIO_OE		0x7d14
/* GPIO value, 0: Low, 1: High */
#घोषणा MT7530_LED_GPIO_DATA		0x7d18

#घोषणा MT7530_CREV			0x7ffc
#घोषणा  CHIP_NAME_SHIFT		16
#घोषणा  MT7530_ID			0x7530

#घोषणा MT7531_CREV			0x781C
#घोषणा  CHIP_REV_M			0x0f
#घोषणा  MT7531_ID			0x7531

/* Registers क्रम core PLL access through mmd indirect */
#घोषणा CORE_PLL_GROUP2			0x401
#घोषणा  RG_SYSPLL_EN_NORMAL		BIT(15)
#घोषणा  RG_SYSPLL_VODEN		BIT(14)
#घोषणा  RG_SYSPLL_LF			BIT(13)
#घोषणा  RG_SYSPLL_RST_DLY(x)		(((x) & 0x3) << 12)
#घोषणा  RG_SYSPLL_LVROD_EN		BIT(10)
#घोषणा  RG_SYSPLL_PREDIV(x)		(((x) & 0x3) << 8)
#घोषणा  RG_SYSPLL_POSDIV(x)		(((x) & 0x3) << 5)
#घोषणा  RG_SYSPLL_FBKSEL		BIT(4)
#घोषणा  RT_SYSPLL_EN_AFE_OLT		BIT(0)

#घोषणा CORE_PLL_GROUP4			0x403
#घोषणा  RG_SYSPLL_DDSFBK_EN		BIT(12)
#घोषणा  RG_SYSPLL_BIAS_EN		BIT(11)
#घोषणा  RG_SYSPLL_BIAS_LPF_EN		BIT(10)
#घोषणा  MT7531_PHY_PLL_OFF		BIT(5)
#घोषणा  MT7531_PHY_PLL_BYPASS_MODE	BIT(4)

#घोषणा MT753X_CTRL_PHY_ADDR		0

#घोषणा CORE_PLL_GROUP5			0x404
#घोषणा  RG_LCDDS_PCW_NCPO1(x)		((x) & 0xffff)

#घोषणा CORE_PLL_GROUP6			0x405
#घोषणा  RG_LCDDS_PCW_NCPO0(x)		((x) & 0xffff)

#घोषणा CORE_PLL_GROUP7			0x406
#घोषणा  RG_LCDDS_PWDB			BIT(15)
#घोषणा  RG_LCDDS_ISO_EN		BIT(13)
#घोषणा  RG_LCCDS_C(x)			(((x) & 0x7) << 4)
#घोषणा  RG_LCDDS_PCW_NCPO_CHG		BIT(3)

#घोषणा CORE_PLL_GROUP10		0x409
#घोषणा  RG_LCDDS_SSC_DELTA(x)		((x) & 0xfff)

#घोषणा CORE_PLL_GROUP11		0x40a
#घोषणा  RG_LCDDS_SSC_DELTA1(x)		((x) & 0xfff)

#घोषणा CORE_GSWPLL_GRP1		0x40d
#घोषणा  RG_GSWPLL_PREDIV(x)		(((x) & 0x3) << 14)
#घोषणा  RG_GSWPLL_POSDIV_200M(x)	(((x) & 0x3) << 12)
#घोषणा  RG_GSWPLL_EN_PRE		BIT(11)
#घोषणा  RG_GSWPLL_FBKSEL		BIT(10)
#घोषणा  RG_GSWPLL_BP			BIT(9)
#घोषणा  RG_GSWPLL_BR			BIT(8)
#घोषणा  RG_GSWPLL_FBKDIV_200M(x)	((x) & 0xff)

#घोषणा CORE_GSWPLL_GRP2		0x40e
#घोषणा  RG_GSWPLL_POSDIV_500M(x)	(((x) & 0x3) << 8)
#घोषणा  RG_GSWPLL_FBKDIV_500M(x)	((x) & 0xff)

#घोषणा CORE_TRGMII_GSW_CLK_CG		0x410
#घोषणा  REG_GSWCK_EN			BIT(0)
#घोषणा  REG_TRGMIICK_EN		BIT(1)

#घोषणा MIB_DESC(_s, _o, _n)	\
	अणु			\
		.size = (_s),	\
		.offset = (_o),	\
		.name = (_n),	\
	पूर्ण

काष्ठा mt7530_mib_desc अणु
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक offset;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा mt7530_fdb अणु
	u16 vid;
	u8 port_mask;
	u8 aging;
	u8 mac[6];
	bool noarp;
पूर्ण;

/* काष्ठा mt7530_port -	This is the मुख्य data काष्ठाure क्रम holding the state
 *			of the port.
 * @enable:	The status used क्रम show port is enabled or not.
 * @pm:		The matrix used to show all connections with the port.
 * @pvid:	The VLAN specअगरied is to be considered a PVID at ingress.  Any
 *		untagged frames will be asचिन्हित to the related VLAN.
 * @vlan_filtering: The flags indicating whether the port that can recognize
 *		    VLAN-tagged frames.
 */
काष्ठा mt7530_port अणु
	bool enable;
	u32 pm;
	u16 pvid;
पूर्ण;

/* Port 5 पूर्णांकerface select definitions */
क्रमागत p5_पूर्णांकerface_select अणु
	P5_DISABLED = 0,
	P5_INTF_SEL_PHY_P0,
	P5_INTF_SEL_PHY_P4,
	P5_INTF_SEL_GMAC5,
	P5_INTF_SEL_GMAC5_SGMII,
पूर्ण;

अटल स्थिर अक्षर *p5_पूर्णांकf_modes(अचिन्हित पूर्णांक p5_पूर्णांकerface)
अणु
	चयन (p5_पूर्णांकerface) अणु
	हाल P5_DISABLED:
		वापस "DISABLED";
	हाल P5_INTF_SEL_PHY_P0:
		वापस "PHY P0";
	हाल P5_INTF_SEL_PHY_P4:
		वापस "PHY P4";
	हाल P5_INTF_SEL_GMAC5:
		वापस "GMAC5";
	हाल P5_INTF_SEL_GMAC5_SGMII:
		वापस "GMAC5_SGMII";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

/* काष्ठा mt753x_info -	This is the मुख्य data काष्ठाure क्रम holding the specअगरic
 *			part क्रम each supported device
 * @sw_setup:		Holding the handler to a device initialization
 * @phy_पढ़ो:		Holding the way पढ़ोing PHY port
 * @phy_ग_लिखो:		Holding the way writing PHY port
 * @pad_setup:		Holding the way setting up the bus pad क्रम a certain
 *			MAC port
 * @phy_mode_supported:	Check अगर the PHY type is being supported on a certain
 *			port
 * @mac_port_validate:	Holding the way to set addition validate type क्रम a
 *			certan MAC port
 * @mac_port_get_state: Holding the way getting the MAC/PCS state क्रम a certain
 *			MAC port
 * @mac_port_config:	Holding the way setting up the PHY attribute to a
 *			certain MAC port
 * @mac_pcs_an_restart	Holding the way restarting PCS स्वतःnegotiation क्रम a
 *			certain MAC port
 * @mac_pcs_link_up:	Holding the way setting up the PHY attribute to the pcs
 *			of the certain MAC port
 */
काष्ठा mt753x_info अणु
	क्रमागत mt753x_id id;

	पूर्णांक (*sw_setup)(काष्ठा dsa_चयन *ds);
	पूर्णांक (*phy_पढ़ो)(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक regnum);
	पूर्णांक (*phy_ग_लिखो)(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक regnum, u16 val);
	पूर्णांक (*pad_setup)(काष्ठा dsa_चयन *ds, phy_पूर्णांकerface_t पूर्णांकerface);
	पूर्णांक (*cpu_port_config)(काष्ठा dsa_चयन *ds, पूर्णांक port);
	bool (*phy_mode_supported)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   स्थिर काष्ठा phylink_link_state *state);
	व्योम (*mac_port_validate)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  अचिन्हित दीर्घ *supported);
	पूर्णांक (*mac_port_get_state)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  काष्ठा phylink_link_state *state);
	पूर्णांक (*mac_port_config)(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       अचिन्हित पूर्णांक mode,
			       phy_पूर्णांकerface_t पूर्णांकerface);
	व्योम (*mac_pcs_an_restart)(काष्ठा dsa_चयन *ds, पूर्णांक port);
	व्योम (*mac_pcs_link_up)(काष्ठा dsa_चयन *ds, पूर्णांक port,
				अचिन्हित पूर्णांक mode, phy_पूर्णांकerface_t पूर्णांकerface,
				पूर्णांक speed, पूर्णांक duplex);
पूर्ण;

/* काष्ठा mt7530_priv -	This is the मुख्य data काष्ठाure क्रम holding the state
 *			of the driver
 * @dev:		The device poपूर्णांकer
 * @ds:			The poपूर्णांकer to the dsa core काष्ठाure
 * @bus:		The bus used क्रम the device and built-in PHY
 * @rstc:		The poपूर्णांकer to reset control used by MCM
 * @core_pwr:		The घातer supplied पूर्णांकo the core
 * @io_pwr:		The घातer supplied पूर्णांकo the I/O
 * @reset:		The descriptor क्रम GPIO line tied to its reset pin
 * @mcm:		Flag क्रम distinguishing अगर standalone IC or module
 *			coupling
 * @ports:		Holding the state among ports
 * @reg_mutex:		The lock क्रम protecting among process accessing
 *			रेजिस्टरs
 * @p6_पूर्णांकerface	Holding the current port 6 पूर्णांकerface
 * @p5_पूर्णांकf_sel:	Holding the current port 5 पूर्णांकerface select
 */
काष्ठा mt7530_priv अणु
	काष्ठा device		*dev;
	काष्ठा dsa_चयन	*ds;
	काष्ठा mii_bus		*bus;
	काष्ठा reset_control	*rstc;
	काष्ठा regulator	*core_pwr;
	काष्ठा regulator	*io_pwr;
	काष्ठा gpio_desc	*reset;
	स्थिर काष्ठा mt753x_info *info;
	अचिन्हित पूर्णांक		id;
	bool			mcm;
	phy_पूर्णांकerface_t		p6_पूर्णांकerface;
	phy_पूर्णांकerface_t		p5_पूर्णांकerface;
	अचिन्हित पूर्णांक		p5_पूर्णांकf_sel;
	u8			mirror_rx;
	u8			mirror_tx;

	काष्ठा mt7530_port	ports[MT7530_NUM_PORTS];
	/* protect among processes क्रम रेजिस्टरs access*/
	काष्ठा mutex reg_mutex;
पूर्ण;

काष्ठा mt7530_hw_vlan_entry अणु
	पूर्णांक port;
	u8  old_members;
	bool untagged;
पूर्ण;

अटल अंतरभूत व्योम mt7530_hw_vlan_entry_init(काष्ठा mt7530_hw_vlan_entry *e,
					     पूर्णांक port, bool untagged)
अणु
	e->port = port;
	e->untagged = untagged;
पूर्ण

प्रकार व्योम (*mt7530_vlan_op)(काष्ठा mt7530_priv *,
			       काष्ठा mt7530_hw_vlan_entry *);

काष्ठा mt7530_hw_stats अणु
	स्थिर अक्षर	*string;
	u16		reg;
	u8		माप_stat;
पूर्ण;

काष्ठा mt7530_dummy_poll अणु
	काष्ठा mt7530_priv *priv;
	u32 reg;
पूर्ण;

अटल अंतरभूत व्योम INIT_MT7530_DUMMY_POLL(काष्ठा mt7530_dummy_poll *p,
					  काष्ठा mt7530_priv *priv, u32 reg)
अणु
	p->priv = priv;
	p->reg = reg;
पूर्ण

#पूर्ण_अगर /* __MT7530_H */
