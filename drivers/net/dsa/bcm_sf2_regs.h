<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Broadcom Starfighter 2 चयन रेजिस्टर defines
 *
 * Copyright (C) 2014, Broadcom Corporation
 */
#अगर_अघोषित __BCM_SF2_REGS_H
#घोषणा __BCM_SF2_REGS_H

/* Register set relative to 'REG' */

क्रमागत bcm_sf2_reg_offs अणु
	REG_SWITCH_CNTRL = 0,
	REG_SWITCH_STATUS,
	REG_सूची_DATA_WRITE,
	REG_सूची_DATA_READ,
	REG_SWITCH_REVISION,
	REG_PHY_REVISION,
	REG_SPHY_CNTRL,
	REG_CROSSBAR,
	REG_RGMII_0_CNTRL,
	REG_RGMII_1_CNTRL,
	REG_RGMII_2_CNTRL,
	REG_RGMII_11_CNTRL,
	REG_LED_0_CNTRL,
	REG_LED_1_CNTRL,
	REG_LED_2_CNTRL,
	REG_SWITCH_REG_MAX,
पूर्ण;

/* Relative to REG_SWITCH_CNTRL */
#घोषणा  MDIO_MASTER_SEL		(1 << 0)

/* Relative to REG_SWITCH_REVISION */
#घोषणा  SF2_REV_MASK			0xffff
#घोषणा  SWITCH_TOP_REV_SHIFT		16
#घोषणा  SWITCH_TOP_REV_MASK		0xffff

/* Relative to REG_PHY_REVISION */
#घोषणा  PHY_REVISION_MASK		0xffff

/* Relative to REG_SPHY_CNTRL */
#घोषणा  IDDQ_BIAS			(1 << 0)
#घोषणा  EXT_PWR_DOWN			(1 << 1)
#घोषणा  FORCE_DLL_EN			(1 << 2)
#घोषणा  IDDQ_GLOBAL_PWR		(1 << 3)
#घोषणा  CK25_DIS			(1 << 4)
#घोषणा  PHY_RESET			(1 << 5)
#घोषणा  PHY_PHYAD_SHIFT		8
#घोषणा  PHY_PHYAD_MASK			0x1F

/* Relative to REG_CROSSBAR */
#घोषणा CROSSBAR_BCM4908_INT_P7		0
#घोषणा CROSSBAR_BCM4908_INT_RUNNER	1
#घोषणा CROSSBAR_BCM4908_EXT_SERDES	0
#घोषणा CROSSBAR_BCM4908_EXT_GPHY4	1
#घोषणा CROSSBAR_BCM4908_EXT_RGMII	2

/* Relative to REG_RGMII_CNTRL */
#घोषणा  RGMII_MODE_EN			(1 << 0)
#घोषणा  ID_MODE_DIS			(1 << 1)
#घोषणा  PORT_MODE_SHIFT		2
#घोषणा  INT_EPHY			(0 << PORT_MODE_SHIFT)
#घोषणा  INT_GPHY			(1 << PORT_MODE_SHIFT)
#घोषणा  EXT_EPHY			(2 << PORT_MODE_SHIFT)
#घोषणा  EXT_GPHY			(3 << PORT_MODE_SHIFT)
#घोषणा  EXT_REVMII			(4 << PORT_MODE_SHIFT)
#घोषणा  PORT_MODE_MASK			0x7
#घोषणा  RVMII_REF_SEL			(1 << 5)
#घोषणा  RX_PAUSE_EN			(1 << 6)
#घोषणा  TX_PAUSE_EN			(1 << 7)
#घोषणा  TX_CLK_STOP_EN			(1 << 8)
#घोषणा  LPI_COUNT_SHIFT		9
#घोषणा  LPI_COUNT_MASK			0x3F

#घोषणा REG_LED_CNTRL(x)		(REG_LED_0_CNTRL + (x))

#घोषणा  SPDLNK_SRC_SEL			(1 << 24)

/* Register set relative to 'INTRL2_0' and 'INTRL2_1' */
#घोषणा INTRL2_CPU_STATUS		0x00
#घोषणा INTRL2_CPU_SET			0x04
#घोषणा INTRL2_CPU_CLEAR		0x08
#घोषणा INTRL2_CPU_MASK_STATUS		0x0c
#घोषणा INTRL2_CPU_MASK_SET		0x10
#घोषणा INTRL2_CPU_MASK_CLEAR		0x14

/* Shared INTRL2_0 and INTRL2_ पूर्णांकerrupt sources macros */
#घोषणा P_LINK_UP_IRQ(x)		(1 << (0 + (x)))
#घोषणा P_LINK_DOWN_IRQ(x)		(1 << (1 + (x)))
#घोषणा P_ENERGY_ON_IRQ(x)		(1 << (2 + (x)))
#घोषणा P_ENERGY_OFF_IRQ(x)		(1 << (3 + (x)))
#घोषणा P_GPHY_IRQ(x)			(1 << (4 + (x)))
#घोषणा P_NUM_IRQ			5
#घोषणा P_IRQ_MASK(x)			(P_LINK_UP_IRQ((x)) | \
					 P_LINK_DOWN_IRQ((x)) | \
					 P_ENERGY_ON_IRQ((x)) | \
					 P_ENERGY_OFF_IRQ((x)) | \
					 P_GPHY_IRQ((x)))

/* INTRL2_0 पूर्णांकerrupt sources */
#घोषणा P0_IRQ_OFF			0
#घोषणा MEM_DOUBLE_IRQ			(1 << 5)
#घोषणा EEE_LPI_IRQ			(1 << 6)
#घोषणा P5_CPU_WAKE_IRQ			(1 << 7)
#घोषणा P8_CPU_WAKE_IRQ			(1 << 8)
#घोषणा P7_CPU_WAKE_IRQ			(1 << 9)
#घोषणा IEEE1588_IRQ			(1 << 10)
#घोषणा MDIO_ERR_IRQ			(1 << 11)
#घोषणा MDIO_DONE_IRQ			(1 << 12)
#घोषणा GISB_ERR_IRQ			(1 << 13)
#घोषणा UBUS_ERR_IRQ			(1 << 14)
#घोषणा FAILOVER_ON_IRQ			(1 << 15)
#घोषणा FAILOVER_OFF_IRQ		(1 << 16)
#घोषणा TCAM_SOFT_ERR_IRQ		(1 << 17)

/* INTRL2_1 पूर्णांकerrupt sources */
#घोषणा P7_IRQ_OFF			0
#घोषणा P_IRQ_OFF(x)			((6 - (x)) * P_NUM_IRQ)

/* Register set relative to 'ACB' */
#घोषणा ACB_CONTROL			0x00
#घोषणा  ACB_EN				(1 << 0)
#घोषणा  ACB_ALGORITHM			(1 << 1)
#घोषणा  ACB_FLUSH_SHIFT		2
#घोषणा  ACB_FLUSH_MASK			0x3

#घोषणा ACB_QUEUE_0_CFG			0x08
#घोषणा  XOFF_THRESHOLD_MASK		0x7ff
#घोषणा  XON_EN				(1 << 11)
#घोषणा  TOTAL_XOFF_THRESHOLD_SHIFT	12
#घोषणा  TOTAL_XOFF_THRESHOLD_MASK	0x7ff
#घोषणा  TOTAL_XOFF_EN			(1 << 23)
#घोषणा  TOTAL_XON_EN			(1 << 24)
#घोषणा  PKTLEN_SHIFT			25
#घोषणा  PKTLEN_MASK			0x3f
#घोषणा ACB_QUEUE_CFG(x)		(ACB_QUEUE_0_CFG + ((x) * 0x4))

/* Register set relative to 'CORE' */
#घोषणा CORE_G_PCTL_PORT0		0x00000
#घोषणा CORE_G_PCTL_PORT(x)		(CORE_G_PCTL_PORT0 + (x * 0x4))
#घोषणा CORE_IMP_CTL			0x00020
#घोषणा  RX_DIS				(1 << 0)
#घोषणा  TX_DIS				(1 << 1)
#घोषणा  RX_BCST_EN			(1 << 2)
#घोषणा  RX_MCST_EN			(1 << 3)
#घोषणा  RX_UCST_EN			(1 << 4)

#घोषणा CORE_SWMODE			0x0002c
#घोषणा  SW_FWDG_MODE			(1 << 0)
#घोषणा  SW_FWDG_EN			(1 << 1)
#घोषणा  RTRY_LMT_DIS			(1 << 2)

#घोषणा CORE_STS_OVERRIDE_IMP		0x00038
#घोषणा  GMII_SPEED_UP_2G		(1 << 6)
#घोषणा  MII_SW_OR			(1 << 7)

/* Alternate layout क्रम e.g: 7278 */
#घोषणा CORE_STS_OVERRIDE_IMP2		0x39040

#घोषणा CORE_NEW_CTRL			0x00084
#घोषणा  IP_MC				(1 << 0)
#घोषणा  OUTRANGEERR_DISCARD		(1 << 1)
#घोषणा  INRANGEERR_DISCARD		(1 << 2)
#घोषणा  CABLE_DIAG_LEN			(1 << 3)
#घोषणा  OVERRIDE_AUTO_PD_WAR		(1 << 4)
#घोषणा  EN_AUTO_PD_WAR			(1 << 5)
#घोषणा  UC_FWD_EN			(1 << 6)
#घोषणा  MC_FWD_EN			(1 << 7)

#घोषणा CORE_SWITCH_CTRL		0x00088
#घोषणा  MII_DUMB_FWDG_EN		(1 << 6)

#घोषणा CORE_DIS_LEARN			0x000f0

#घोषणा CORE_SFT_LRN_CTRL		0x000f8
#घोषणा  SW_LEARN_CNTL(x)		(1 << (x))

#घोषणा CORE_STS_OVERRIDE_GMIIP_PORT(x)	(0x160 + (x) * 4)
#घोषणा CORE_STS_OVERRIDE_GMIIP2_PORT(x) (0x39000 + (x) * 8)
#घोषणा  LINK_STS			(1 << 0)
#घोषणा  DUPLX_MODE			(1 << 1)
#घोषणा  SPEED_SHIFT			2
#घोषणा  SPEED_MASK			0x3
#घोषणा  RXFLOW_CNTL			(1 << 4)
#घोषणा  TXFLOW_CNTL			(1 << 5)
#घोषणा  SW_OVERRIDE			(1 << 6)

#घोषणा CORE_WATCHDOG_CTRL		0x001e4
#घोषणा  SOFTWARE_RESET			(1 << 7)
#घोषणा  EN_CHIP_RST			(1 << 6)
#घोषणा  EN_SW_RESET			(1 << 4)

#घोषणा CORE_FAST_AGE_CTRL		0x00220
#घोषणा  EN_FAST_AGE_STATIC		(1 << 0)
#घोषणा  EN_AGE_DYNAMIC			(1 << 1)
#घोषणा  EN_AGE_PORT			(1 << 2)
#घोषणा  EN_AGE_VLAN			(1 << 3)
#घोषणा  EN_AGE_SPT			(1 << 4)
#घोषणा  EN_AGE_MCAST			(1 << 5)
#घोषणा  FAST_AGE_STR_DONE		(1 << 7)

#घोषणा CORE_FAST_AGE_PORT		0x00224
#घोषणा  AGE_PORT_MASK			0xf

#घोषणा CORE_FAST_AGE_VID		0x00228
#घोषणा  AGE_VID_MASK			0x3fff

#घोषणा CORE_LNKSTS			0x00400
#घोषणा  LNK_STS_MASK			0x1ff

#घोषणा CORE_SPDSTS			0x00410
#घोषणा  SPDSTS_10			0
#घोषणा  SPDSTS_100			1
#घोषणा  SPDSTS_1000			2
#घोषणा  SPDSTS_SHIFT			2
#घोषणा  SPDSTS_MASK			0x3

#घोषणा CORE_DUPSTS			0x00420
#घोषणा  CORE_DUPSTS_MASK		0x1ff

#घोषणा CORE_PAUSESTS			0x00428
#घोषणा  PAUSESTS_TX_PAUSE_SHIFT	9

#घोषणा CORE_GMNCFGCFG			0x0800
#घोषणा  RST_MIB_CNT			(1 << 0)
#घोषणा  RXBPDU_EN			(1 << 1)

#घोषणा CORE_IMP0_PRT_ID		0x0804

#घोषणा CORE_RST_MIB_CNT_EN		0x0950

#घोषणा CORE_ARLA_VTBL_RWCTRL		0x1600
#घोषणा  ARLA_VTBL_CMD_WRITE		0
#घोषणा  ARLA_VTBL_CMD_READ		1
#घोषणा  ARLA_VTBL_CMD_CLEAR		2
#घोषणा  ARLA_VTBL_STDN			(1 << 7)

#घोषणा CORE_ARLA_VTBL_ADDR		0x1604
#घोषणा  VTBL_ADDR_INDEX_MASK		0xfff

#घोषणा CORE_ARLA_VTBL_ENTRY		0x160c
#घोषणा  FWD_MAP_MASK			0x1ff
#घोषणा  UNTAG_MAP_MASK			0x1ff
#घोषणा  UNTAG_MAP_SHIFT		9
#घोषणा  MSTP_INDEX_MASK		0x7
#घोषणा  MSTP_INDEX_SHIFT		18
#घोषणा  FWD_MODE			(1 << 21)

#घोषणा CORE_MEM_PSM_VDD_CTRL		0x2380
#घोषणा  P_TXQ_PSM_VDD_SHIFT		2
#घोषणा  P_TXQ_PSM_VDD_MASK		0x3
#घोषणा  P_TXQ_PSM_VDD(x)		(P_TXQ_PSM_VDD_MASK << \
					((x) * P_TXQ_PSM_VDD_SHIFT))

#घोषणा CORE_PORT_TC2_QOS_MAP_PORT(x)	(0xc1c0 + ((x) * 0x10))
#घोषणा  PRT_TO_QID_MASK		0x3
#घोषणा  PRT_TO_QID_SHIFT		3

#घोषणा CORE_PORT_VLAN_CTL_PORT(x)	(0xc400 + ((x) * 0x8))
#घोषणा  PORT_VLAN_CTRL_MASK		0x1ff

#घोषणा CORE_TXQ_THD_PAUSE_QN_PORT_0	0x2c80
#घोषणा  TXQ_PAUSE_THD_MASK		0x7ff
#घोषणा CORE_TXQ_THD_PAUSE_QN_PORT(x)	(CORE_TXQ_THD_PAUSE_QN_PORT_0 + \
					(x) * 0x8)

#घोषणा CORE_DEFAULT_1Q_TAG_P(x)	(0xd040 + ((x) * 8))
#घोषणा  CFI_SHIFT			12
#घोषणा  PRI_SHIFT			13
#घोषणा  PRI_MASK			0x7

#घोषणा CORE_JOIN_ALL_VLAN_EN		0xd140

#घोषणा CORE_CFP_ACC			0x28000
#घोषणा  OP_STR_DONE			(1 << 0)
#घोषणा  OP_SEL_SHIFT			1
#घोषणा  OP_SEL_READ			(1 << OP_SEL_SHIFT)
#घोषणा  OP_SEL_WRITE			(2 << OP_SEL_SHIFT)
#घोषणा  OP_SEL_SEARCH			(4 << OP_SEL_SHIFT)
#घोषणा  OP_SEL_MASK			(7 << OP_SEL_SHIFT)
#घोषणा  CFP_RAM_CLEAR			(1 << 4)
#घोषणा  RAM_SEL_SHIFT			10
#घोषणा  TCAM_SEL			(1 << RAM_SEL_SHIFT)
#घोषणा  ACT_POL_RAM			(2 << RAM_SEL_SHIFT)
#घोषणा  RATE_METER_RAM			(4 << RAM_SEL_SHIFT)
#घोषणा  GREEN_STAT_RAM			(8 << RAM_SEL_SHIFT)
#घोषणा  YELLOW_STAT_RAM		(16 << RAM_SEL_SHIFT)
#घोषणा  RED_STAT_RAM			(24 << RAM_SEL_SHIFT)
#घोषणा  RAM_SEL_MASK			(0x1f << RAM_SEL_SHIFT)
#घोषणा  TCAM_RESET			(1 << 15)
#घोषणा  XCESS_ADDR_SHIFT		16
#घोषणा  XCESS_ADDR_MASK		0xff
#घोषणा  SEARCH_STS			(1 << 27)
#घोषणा  RD_STS_SHIFT			28
#घोषणा  RD_STS_TCAM			(1 << RD_STS_SHIFT)
#घोषणा  RD_STS_ACT_POL_RAM		(2 << RD_STS_SHIFT)
#घोषणा  RD_STS_RATE_METER_RAM		(4 << RD_STS_SHIFT)
#घोषणा  RD_STS_STAT_RAM		(8 << RD_STS_SHIFT)

#घोषणा CORE_CFP_RATE_METER_GLOBAL_CTL	0x28010

#घोषणा CORE_CFP_DATA_PORT_0		0x28040
#घोषणा CORE_CFP_DATA_PORT(x)		(CORE_CFP_DATA_PORT_0 + \
					(x) * 0x10)

/* UDF_DATA7 */
#घोषणा L3_FRAMING_SHIFT		24
#घोषणा L3_FRAMING_MASK			(0x3 << L3_FRAMING_SHIFT)
#घोषणा IPTOS_SHIFT			16
#घोषणा IPTOS_MASK			0xff
#घोषणा IPPROTO_SHIFT			8
#घोषणा IPPROTO_MASK			(0xff << IPPROTO_SHIFT)
#घोषणा IP_FRAG_SHIFT			7
#घोषणा IP_FRAG				(1 << IP_FRAG_SHIFT)

/* UDF_DATA0 */
#घोषणा  SLICE_VALID			3
#घोषणा  SLICE_NUM_SHIFT		2
#घोषणा  SLICE_NUM(x)			((x) << SLICE_NUM_SHIFT)
#घोषणा  SLICE_NUM_MASK			0x3

#घोषणा CORE_CFP_MASK_PORT_0		0x280c0

#घोषणा CORE_CFP_MASK_PORT(x)		(CORE_CFP_MASK_PORT_0 + \
					(x) * 0x10)

#घोषणा CORE_ACT_POL_DATA0		0x28140
#घोषणा  VLAN_BYP			(1 << 0)
#घोषणा  EAP_BYP			(1 << 1)
#घोषणा  STP_BYP			(1 << 2)
#घोषणा  REASON_CODE_SHIFT		3
#घोषणा  REASON_CODE_MASK		0x3f
#घोषणा  LOOP_BK_EN			(1 << 9)
#घोषणा  NEW_TC_SHIFT			10
#घोषणा  NEW_TC_MASK			0x7
#घोषणा  CHANGE_TC			(1 << 13)
#घोषणा  DST_MAP_IB_SHIFT		14
#घोषणा  DST_MAP_IB_MASK		0x1ff
#घोषणा  CHANGE_FWRD_MAP_IB_SHIFT	24
#घोषणा  CHANGE_FWRD_MAP_IB_MASK	0x3
#घोषणा  CHANGE_FWRD_MAP_IB_NO_DEST	(0 << CHANGE_FWRD_MAP_IB_SHIFT)
#घोषणा  CHANGE_FWRD_MAP_IB_REM_ARL	(1 << CHANGE_FWRD_MAP_IB_SHIFT)
#घोषणा  CHANGE_FWRD_MAP_IB_REP_ARL	(2 << CHANGE_FWRD_MAP_IB_SHIFT)
#घोषणा  CHANGE_FWRD_MAP_IB_ADD_DST	(3 << CHANGE_FWRD_MAP_IB_SHIFT)
#घोषणा  NEW_DSCP_IB_SHIFT		26
#घोषणा  NEW_DSCP_IB_MASK		0x3f

#घोषणा CORE_ACT_POL_DATA1		0x28150
#घोषणा  CHANGE_DSCP_IB			(1 << 0)
#घोषणा  DST_MAP_OB_SHIFT		1
#घोषणा  DST_MAP_OB_MASK		0x3ff
#घोषणा  CHANGE_FWRD_MAP_OB_SHIT	11
#घोषणा  CHANGE_FWRD_MAP_OB_MASK	0x3
#घोषणा  NEW_DSCP_OB_SHIFT		13
#घोषणा  NEW_DSCP_OB_MASK		0x3f
#घोषणा  CHANGE_DSCP_OB			(1 << 19)
#घोषणा  CHAIN_ID_SHIFT			20
#घोषणा  CHAIN_ID_MASK			0xff
#घोषणा  CHANGE_COLOR			(1 << 28)
#घोषणा  NEW_COLOR_SHIFT		29
#घोषणा  NEW_COLOR_MASK			0x3
#घोषणा  NEW_COLOR_GREEN		(0 << NEW_COLOR_SHIFT)
#घोषणा  NEW_COLOR_YELLOW		(1 << NEW_COLOR_SHIFT)
#घोषणा  NEW_COLOR_RED			(2 << NEW_COLOR_SHIFT)
#घोषणा  RED_DEFAULT			(1 << 31)

#घोषणा CORE_ACT_POL_DATA2		0x28160
#घोषणा  MAC_LIMIT_BYPASS		(1 << 0)
#घोषणा  CHANGE_TC_O			(1 << 1)
#घोषणा  NEW_TC_O_SHIFT			2
#घोषणा  NEW_TC_O_MASK			0x7
#घोषणा  SPCP_RMK_DISABLE		(1 << 5)
#घोषणा  CPCP_RMK_DISABLE		(1 << 6)
#घोषणा  DEI_RMK_DISABLE		(1 << 7)

#घोषणा CORE_RATE_METER0		0x28180
#घोषणा  COLOR_MODE			(1 << 0)
#घोषणा  POLICER_ACTION			(1 << 1)
#घोषणा  COUPLING_FLAG			(1 << 2)
#घोषणा  POLICER_MODE_SHIFT		3
#घोषणा  POLICER_MODE_MASK		0x3
#घोषणा  POLICER_MODE_RFC2698		(0 << POLICER_MODE_SHIFT)
#घोषणा  POLICER_MODE_RFC4115		(1 << POLICER_MODE_SHIFT)
#घोषणा  POLICER_MODE_MEF		(2 << POLICER_MODE_SHIFT)
#घोषणा  POLICER_MODE_DISABLE		(3 << POLICER_MODE_SHIFT)

#घोषणा CORE_RATE_METER1		0x28190
#घोषणा  EIR_TK_BKT_MASK		0x7fffff

#घोषणा CORE_RATE_METER2		0x281a0
#घोषणा  EIR_BKT_SIZE_MASK		0xfffff

#घोषणा CORE_RATE_METER3		0x281b0
#घोषणा  EIR_REF_CNT_MASK		0x7ffff

#घोषणा CORE_RATE_METER4		0x281c0
#घोषणा  CIR_TK_BKT_MASK		0x7fffff

#घोषणा CORE_RATE_METER5		0x281d0
#घोषणा  CIR_BKT_SIZE_MASK		0xfffff

#घोषणा CORE_RATE_METER6		0x281e0
#घोषणा  CIR_REF_CNT_MASK		0x7ffff

#घोषणा CORE_STAT_GREEN_CNTR		0x28200
#घोषणा CORE_STAT_YELLOW_CNTR		0x28210
#घोषणा CORE_STAT_RED_CNTR		0x28220

#घोषणा CORE_CFP_CTL_REG		0x28400
#घोषणा  CFP_EN_MAP_MASK		0x1ff

/* IPv4 slices, 3 of them */
#घोषणा CORE_UDF_0_A_0_8_PORT_0		0x28440
#घोषणा  CFG_UDF_OFFSET_MASK		0x1f
#घोषणा  CFG_UDF_OFFSET_BASE_SHIFT	5
#घोषणा  CFG_UDF_SOF			(0 << CFG_UDF_OFFSET_BASE_SHIFT)
#घोषणा  CFG_UDF_EOL2			(2 << CFG_UDF_OFFSET_BASE_SHIFT)
#घोषणा  CFG_UDF_EOL3			(3 << CFG_UDF_OFFSET_BASE_SHIFT)

/* IPv6 slices */
#घोषणा CORE_UDF_0_B_0_8_PORT_0		0x28500

/* IPv6 chained slices */
#घोषणा CORE_UDF_0_D_0_11_PORT_0	0x28680

/* Number of slices क्रम IPv4, IPv6 and non-IP */
#घोषणा UDF_NUM_SLICES			4
#घोषणा UDFS_PER_SLICE			9

/* Spacing between dअगरferent slices */
#घोषणा UDF_SLICE_OFFSET		0x40

#घोषणा CFP_NUM_RULES			256

/* Number of egress queues per port */
#घोषणा SF2_NUM_EGRESS_QUEUES		8

#पूर्ण_अगर /* __BCM_SF2_REGS_H */
