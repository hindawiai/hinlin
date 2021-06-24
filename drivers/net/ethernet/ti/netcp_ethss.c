<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Keystone GBE and XGBE subप्रणाली code
 *
 * Copyright (C) 2014 Texas Instruments Incorporated
 * Authors:	Sandeep Nair <sandeep_n@ti.com>
 *		Sandeep Paulraj <s-paulraj@ti.com>
 *		Cyril Chemparathy <cyril@ti.com>
 *		Santosh Shilimkar <santosh.shilimkar@ti.com>
 *		Wingman Kwok <w-kwok2@ti.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/of_address.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ptp_classअगरy.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/ethtool.h>

#समावेश "cpsw.h"
#समावेश "cpsw_ale.h"
#समावेश "netcp.h"
#समावेश "cpts.h"

#घोषणा NETCP_DRIVER_NAME		"TI KeyStone Ethernet Driver"
#घोषणा NETCP_DRIVER_VERSION		"v1.0"

#घोषणा GBE_IDENT(reg)			((reg >> 16) & 0xffff)
#घोषणा GBE_MAJOR_VERSION(reg)		(reg >> 8 & 0x7)
#घोषणा GBE_MINOR_VERSION(reg)		(reg & 0xff)
#घोषणा GBE_RTL_VERSION(reg)		((reg >> 11) & 0x1f)

/* 1G Ethernet SS defines */
#घोषणा GBE_MODULE_NAME			"netcp-gbe"
#घोषणा GBE_SS_VERSION_14		0x4ed2

#घोषणा GBE_SS_REG_INDEX		0
#घोषणा GBE_SGMII34_REG_INDEX		1
#घोषणा GBE_SM_REG_INDEX		2
/* offset relative to base of GBE_SS_REG_INDEX */
#घोषणा GBE13_SGMII_MODULE_OFFSET	0x100
/* offset relative to base of GBE_SM_REG_INDEX */
#घोषणा GBE13_HOST_PORT_OFFSET		0x34
#घोषणा GBE13_SLAVE_PORT_OFFSET		0x60
#घोषणा GBE13_EMAC_OFFSET		0x100
#घोषणा GBE13_SLAVE_PORT2_OFFSET	0x200
#घोषणा GBE13_HW_STATS_OFFSET		0x300
#घोषणा GBE13_CPTS_OFFSET		0x500
#घोषणा GBE13_ALE_OFFSET		0x600
#घोषणा GBE13_HOST_PORT_NUM		0

/* 1G Ethernet NU SS defines */
#घोषणा GBENU_MODULE_NAME		"netcp-gbenu"
#घोषणा GBE_SS_ID_NU			0x4ee6
#घोषणा GBE_SS_ID_2U			0x4ee8

#घोषणा IS_SS_ID_MU(d) \
	((GBE_IDENT((d)->ss_version) == GBE_SS_ID_NU) || \
	 (GBE_IDENT((d)->ss_version) == GBE_SS_ID_2U))

#घोषणा IS_SS_ID_NU(d) \
	(GBE_IDENT((d)->ss_version) == GBE_SS_ID_NU)

#घोषणा IS_SS_ID_VER_14(d) \
	(GBE_IDENT((d)->ss_version) == GBE_SS_VERSION_14)
#घोषणा IS_SS_ID_2U(d) \
	(GBE_IDENT((d)->ss_version) == GBE_SS_ID_2U)

#घोषणा GBENU_SS_REG_INDEX		0
#घोषणा GBENU_SM_REG_INDEX		1
#घोषणा GBENU_SGMII_MODULE_OFFSET	0x100
#घोषणा GBENU_HOST_PORT_OFFSET		0x1000
#घोषणा GBENU_SLAVE_PORT_OFFSET		0x2000
#घोषणा GBENU_EMAC_OFFSET		0x2330
#घोषणा GBENU_HW_STATS_OFFSET		0x1a000
#घोषणा GBENU_CPTS_OFFSET		0x1d000
#घोषणा GBENU_ALE_OFFSET		0x1e000
#घोषणा GBENU_HOST_PORT_NUM		0
#घोषणा GBENU_SGMII_MODULE_SIZE		0x100

/* 10G Ethernet SS defines */
#घोषणा XGBE_MODULE_NAME		"netcp-xgbe"
#घोषणा XGBE_SS_VERSION_10		0x4ee4

#घोषणा XGBE_SS_REG_INDEX		0
#घोषणा XGBE_SM_REG_INDEX		1
#घोषणा XGBE_SERDES_REG_INDEX		2

/* offset relative to base of XGBE_SS_REG_INDEX */
#घोषणा XGBE10_SGMII_MODULE_OFFSET	0x100
#घोषणा IS_SS_ID_XGBE(d)		((d)->ss_version == XGBE_SS_VERSION_10)
/* offset relative to base of XGBE_SM_REG_INDEX */
#घोषणा XGBE10_HOST_PORT_OFFSET		0x34
#घोषणा XGBE10_SLAVE_PORT_OFFSET	0x64
#घोषणा XGBE10_EMAC_OFFSET		0x400
#घोषणा XGBE10_CPTS_OFFSET		0x600
#घोषणा XGBE10_ALE_OFFSET		0x700
#घोषणा XGBE10_HW_STATS_OFFSET		0x800
#घोषणा XGBE10_HOST_PORT_NUM		0

#घोषणा	GBE_TIMER_INTERVAL			(HZ / 2)

/* Soft reset रेजिस्टर values */
#घोषणा SOFT_RESET_MASK				BIT(0)
#घोषणा SOFT_RESET				BIT(0)
#घोषणा DEVICE_EMACSL_RESET_POLL_COUNT		100
#घोषणा GMACSL_RET_WARN_RESET_INCOMPLETE	-2

#घोषणा MACSL_RX_ENABLE_CSF			BIT(23)
#घोषणा MACSL_ENABLE_EXT_CTL			BIT(18)
#घोषणा MACSL_XGMII_ENABLE			BIT(13)
#घोषणा MACSL_XGIG_MODE				BIT(8)
#घोषणा MACSL_GIG_MODE				BIT(7)
#घोषणा MACSL_GMII_ENABLE			BIT(5)
#घोषणा MACSL_FULLDUPLEX			BIT(0)

#घोषणा GBE_CTL_P0_ENABLE			BIT(2)
#घोषणा ETH_SW_CTL_P0_TX_CRC_REMOVE		BIT(13)
#घोषणा GBE13_REG_VAL_STAT_ENABLE_ALL		0xff
#घोषणा XGBE_REG_VAL_STAT_ENABLE_ALL		0xf
#घोषणा GBE_STATS_CD_SEL			BIT(28)

#घोषणा GBE_PORT_MASK(x)			(BIT(x) - 1)
#घोषणा GBE_MASK_NO_PORTS			0

#घोषणा GBE_DEF_1G_MAC_CONTROL					\
		(MACSL_GIG_MODE | MACSL_GMII_ENABLE |		\
		 MACSL_ENABLE_EXT_CTL |	MACSL_RX_ENABLE_CSF)

#घोषणा GBE_DEF_10G_MAC_CONTROL				\
		(MACSL_XGIG_MODE | MACSL_XGMII_ENABLE |		\
		 MACSL_ENABLE_EXT_CTL |	MACSL_RX_ENABLE_CSF)

#घोषणा GBE_STATSA_MODULE			0
#घोषणा GBE_STATSB_MODULE			1
#घोषणा GBE_STATSC_MODULE			2
#घोषणा GBE_STATSD_MODULE			3

#घोषणा GBENU_STATS0_MODULE			0
#घोषणा GBENU_STATS1_MODULE			1
#घोषणा GBENU_STATS2_MODULE			2
#घोषणा GBENU_STATS3_MODULE			3
#घोषणा GBENU_STATS4_MODULE			4
#घोषणा GBENU_STATS5_MODULE			5
#घोषणा GBENU_STATS6_MODULE			6
#घोषणा GBENU_STATS7_MODULE			7
#घोषणा GBENU_STATS8_MODULE			8

#घोषणा XGBE_STATS0_MODULE			0
#घोषणा XGBE_STATS1_MODULE			1
#घोषणा XGBE_STATS2_MODULE			2

/* s: 0-based slave_port */
#घोषणा SGMII_BASE(d, s) \
	(((s) < 2) ? (d)->sgmii_port_regs : (d)->sgmii_port34_regs)

#घोषणा GBE_TX_QUEUE				648
#घोषणा	GBE_TXHOOK_ORDER			0
#घोषणा	GBE_RXHOOK_ORDER			0
#घोषणा GBE_DEFAULT_ALE_AGEOUT			30
#घोषणा SLAVE_LINK_IS_XGMII(s) ((s)->link_पूर्णांकerface >= XGMII_LINK_MAC_PHY)
#घोषणा SLAVE_LINK_IS_RGMII(s) \
	(((s)->link_पूर्णांकerface >= RGMII_LINK_MAC_PHY) && \
	 ((s)->link_पूर्णांकerface <= RGMII_LINK_MAC_PHY_NO_MDIO))
#घोषणा SLAVE_LINK_IS_SGMII(s) \
	((s)->link_पूर्णांकerface <= SGMII_LINK_MAC_PHY_NO_MDIO)
#घोषणा NETCP_LINK_STATE_INVALID		-1

#घोषणा GBE_SET_REG_OFS(p, rb, rn) p->rb##_ofs.rn = \
		दुरत्व(काष्ठा gbe##_##rb, rn)
#घोषणा GBENU_SET_REG_OFS(p, rb, rn) p->rb##_ofs.rn = \
		दुरत्व(काष्ठा gbenu##_##rb, rn)
#घोषणा XGBE_SET_REG_OFS(p, rb, rn) p->rb##_ofs.rn = \
		दुरत्व(काष्ठा xgbe##_##rb, rn)
#घोषणा GBE_REG_ADDR(p, rb, rn) (p->rb + p->rb##_ofs.rn)

#घोषणा HOST_TX_PRI_MAP_DEFAULT			0x00000000

#अगर IS_ENABLED(CONFIG_TI_CPTS)
/* Px_TS_CTL रेजिस्टर fields */
#घोषणा TS_RX_ANX_F_EN				BIT(0)
#घोषणा TS_RX_VLAN_LT1_EN			BIT(1)
#घोषणा TS_RX_VLAN_LT2_EN			BIT(2)
#घोषणा TS_RX_ANX_D_EN				BIT(3)
#घोषणा TS_TX_ANX_F_EN				BIT(4)
#घोषणा TS_TX_VLAN_LT1_EN			BIT(5)
#घोषणा TS_TX_VLAN_LT2_EN			BIT(6)
#घोषणा TS_TX_ANX_D_EN				BIT(7)
#घोषणा TS_LT2_EN				BIT(8)
#घोषणा TS_RX_ANX_E_EN				BIT(9)
#घोषणा TS_TX_ANX_E_EN				BIT(10)
#घोषणा TS_MSG_TYPE_EN_SHIFT			16
#घोषणा TS_MSG_TYPE_EN_MASK			0xffff

/* Px_TS_SEQ_LTYPE रेजिस्टर fields */
#घोषणा TS_SEQ_ID_OFS_SHIFT			16
#घोषणा TS_SEQ_ID_OFS_MASK			0x3f

/* Px_TS_CTL_LTYPE2 रेजिस्टर fields */
#घोषणा TS_107					BIT(16)
#घोषणा TS_129					BIT(17)
#घोषणा TS_130					BIT(18)
#घोषणा TS_131					BIT(19)
#घोषणा TS_132					BIT(20)
#घोषणा TS_319					BIT(21)
#घोषणा TS_320					BIT(22)
#घोषणा TS_TTL_NONZERO				BIT(23)
#घोषणा TS_UNI_EN				BIT(24)
#घोषणा TS_UNI_EN_SHIFT				24

#घोषणा TS_TX_ANX_ALL_EN	 \
	(TS_TX_ANX_D_EN	| TS_TX_ANX_E_EN | TS_TX_ANX_F_EN)

#घोषणा TS_RX_ANX_ALL_EN	 \
	(TS_RX_ANX_D_EN	| TS_RX_ANX_E_EN | TS_RX_ANX_F_EN)

#घोषणा TS_CTL_DST_PORT				TS_319
#घोषणा TS_CTL_DST_PORT_SHIFT			21

#घोषणा TS_CTL_MADDR_ALL	\
	(TS_107 | TS_129 | TS_130 | TS_131 | TS_132)

#घोषणा TS_CTL_MADDR_SHIFT			16

/* The PTP event messages - Sync, Delay_Req, Pdelay_Req, and Pdelay_Resp. */
#घोषणा EVENT_MSG_BITS (BIT(0) | BIT(1) | BIT(2) | BIT(3))
#पूर्ण_अगर /* CONFIG_TI_CPTS */

काष्ठा xgbe_ss_regs अणु
	u32	id_ver;
	u32	synce_count;
	u32	synce_mux;
	u32	control;
पूर्ण;

काष्ठा xgbe_चयन_regs अणु
	u32	id_ver;
	u32	control;
	u32	emcontrol;
	u32	stat_port_en;
	u32	ptype;
	u32	soft_idle;
	u32	thru_rate;
	u32	gap_thresh;
	u32	tx_start_wds;
	u32	flow_control;
	u32	cppi_thresh;
पूर्ण;

काष्ठा xgbe_port_regs अणु
	u32	blk_cnt;
	u32	port_vlan;
	u32	tx_pri_map;
	u32	sa_lo;
	u32	sa_hi;
	u32	ts_ctl;
	u32	ts_seq_ltype;
	u32	ts_vlan;
	u32	ts_ctl_ltype2;
	u32	ts_ctl2;
	u32	control;
पूर्ण;

काष्ठा xgbe_host_port_regs अणु
	u32	blk_cnt;
	u32	port_vlan;
	u32	tx_pri_map;
	u32	src_id;
	u32	rx_pri_map;
	u32	rx_maxlen;
पूर्ण;

काष्ठा xgbe_emac_regs अणु
	u32	id_ver;
	u32	mac_control;
	u32	mac_status;
	u32	soft_reset;
	u32	rx_maxlen;
	u32	__reserved_0;
	u32	rx_छोड़ो;
	u32	tx_छोड़ो;
	u32	em_control;
	u32	__reserved_1;
	u32	tx_gap;
	u32	rsvd[4];
पूर्ण;

काष्ठा xgbe_host_hw_stats अणु
	u32	rx_good_frames;
	u32	rx_broadcast_frames;
	u32	rx_multicast_frames;
	u32	__rsvd_0[3];
	u32	rx_oversized_frames;
	u32	__rsvd_1;
	u32	rx_undersized_frames;
	u32	__rsvd_2;
	u32	overrun_type4;
	u32	overrun_type5;
	u32	rx_bytes;
	u32	tx_good_frames;
	u32	tx_broadcast_frames;
	u32	tx_multicast_frames;
	u32	__rsvd_3[9];
	u32	tx_bytes;
	u32	tx_64byte_frames;
	u32	tx_65_to_127byte_frames;
	u32	tx_128_to_255byte_frames;
	u32	tx_256_to_511byte_frames;
	u32	tx_512_to_1023byte_frames;
	u32	tx_1024byte_frames;
	u32	net_bytes;
	u32	rx_sof_overruns;
	u32	rx_mof_overruns;
	u32	rx_dma_overruns;
पूर्ण;

काष्ठा xgbe_hw_stats अणु
	u32	rx_good_frames;
	u32	rx_broadcast_frames;
	u32	rx_multicast_frames;
	u32	rx_छोड़ो_frames;
	u32	rx_crc_errors;
	u32	rx_align_code_errors;
	u32	rx_oversized_frames;
	u32	rx_jabber_frames;
	u32	rx_undersized_frames;
	u32	rx_fragments;
	u32	overrun_type4;
	u32	overrun_type5;
	u32	rx_bytes;
	u32	tx_good_frames;
	u32	tx_broadcast_frames;
	u32	tx_multicast_frames;
	u32	tx_छोड़ो_frames;
	u32	tx_deferred_frames;
	u32	tx_collision_frames;
	u32	tx_single_coll_frames;
	u32	tx_mult_coll_frames;
	u32	tx_excessive_collisions;
	u32	tx_late_collisions;
	u32	tx_underrun;
	u32	tx_carrier_sense_errors;
	u32	tx_bytes;
	u32	tx_64byte_frames;
	u32	tx_65_to_127byte_frames;
	u32	tx_128_to_255byte_frames;
	u32	tx_256_to_511byte_frames;
	u32	tx_512_to_1023byte_frames;
	u32	tx_1024byte_frames;
	u32	net_bytes;
	u32	rx_sof_overruns;
	u32	rx_mof_overruns;
	u32	rx_dma_overruns;
पूर्ण;

काष्ठा gbenu_ss_regs अणु
	u32	id_ver;
	u32	synce_count;		/* NU */
	u32	synce_mux;		/* NU */
	u32	control;		/* 2U */
	u32	__rsvd_0[2];		/* 2U */
	u32	rgmii_status;		/* 2U */
	u32	ss_status;		/* 2U */
पूर्ण;

काष्ठा gbenu_चयन_regs अणु
	u32	id_ver;
	u32	control;
	u32	__rsvd_0[2];
	u32	emcontrol;
	u32	stat_port_en;
	u32	ptype;			/* NU */
	u32	soft_idle;
	u32	thru_rate;		/* NU */
	u32	gap_thresh;		/* NU */
	u32	tx_start_wds;		/* NU */
	u32	eee_prescale;		/* 2U */
	u32	tx_g_oflow_thresh_set;	/* NU */
	u32	tx_g_oflow_thresh_clr;	/* NU */
	u32	tx_g_buf_thresh_set_l;	/* NU */
	u32	tx_g_buf_thresh_set_h;	/* NU */
	u32	tx_g_buf_thresh_clr_l;	/* NU */
	u32	tx_g_buf_thresh_clr_h;	/* NU */
पूर्ण;

काष्ठा gbenu_port_regs अणु
	u32	__rsvd_0;
	u32	control;
	u32	max_blks;		/* 2U */
	u32	mem_align1;
	u32	blk_cnt;
	u32	port_vlan;
	u32	tx_pri_map;		/* NU */
	u32	pri_ctl;		/* 2U */
	u32	rx_pri_map;
	u32	rx_maxlen;
	u32	tx_blks_pri;		/* NU */
	u32	__rsvd_1;
	u32	idle2lpi;		/* 2U */
	u32	lpi2idle;		/* 2U */
	u32	eee_status;		/* 2U */
	u32	__rsvd_2;
	u32	__rsvd_3[176];		/* NU: more to add */
	u32	__rsvd_4[2];
	u32	sa_lo;
	u32	sa_hi;
	u32	ts_ctl;
	u32	ts_seq_ltype;
	u32	ts_vlan;
	u32	ts_ctl_ltype2;
	u32	ts_ctl2;
पूर्ण;

काष्ठा gbenu_host_port_regs अणु
	u32	__rsvd_0;
	u32	control;
	u32	flow_id_offset;		/* 2U */
	u32	__rsvd_1;
	u32	blk_cnt;
	u32	port_vlan;
	u32	tx_pri_map;		/* NU */
	u32	pri_ctl;
	u32	rx_pri_map;
	u32	rx_maxlen;
	u32	tx_blks_pri;		/* NU */
	u32	__rsvd_2;
	u32	idle2lpi;		/* 2U */
	u32	lpi2wake;		/* 2U */
	u32	eee_status;		/* 2U */
	u32	__rsvd_3;
	u32	__rsvd_4[184];		/* NU */
	u32	host_blks_pri;		/* NU */
पूर्ण;

काष्ठा gbenu_emac_regs अणु
	u32	mac_control;
	u32	mac_status;
	u32	soft_reset;
	u32	boff_test;
	u32	rx_छोड़ो;
	u32	__rsvd_0[11];		/* NU */
	u32	tx_छोड़ो;
	u32	__rsvd_1[11];		/* NU */
	u32	em_control;
	u32	tx_gap;
पूर्ण;

/* Some hw stat regs are applicable to slave port only.
 * This is handled by gbenu_et_stats काष्ठा.  Also some
 * are क्रम SS version NU and some are क्रम 2U.
 */
काष्ठा gbenu_hw_stats अणु
	u32	rx_good_frames;
	u32	rx_broadcast_frames;
	u32	rx_multicast_frames;
	u32	rx_छोड़ो_frames;		/* slave */
	u32	rx_crc_errors;
	u32	rx_align_code_errors;		/* slave */
	u32	rx_oversized_frames;
	u32	rx_jabber_frames;		/* slave */
	u32	rx_undersized_frames;
	u32	rx_fragments;			/* slave */
	u32	ale_drop;
	u32	ale_overrun_drop;
	u32	rx_bytes;
	u32	tx_good_frames;
	u32	tx_broadcast_frames;
	u32	tx_multicast_frames;
	u32	tx_छोड़ो_frames;		/* slave */
	u32	tx_deferred_frames;		/* slave */
	u32	tx_collision_frames;		/* slave */
	u32	tx_single_coll_frames;		/* slave */
	u32	tx_mult_coll_frames;		/* slave */
	u32	tx_excessive_collisions;	/* slave */
	u32	tx_late_collisions;		/* slave */
	u32	rx_ipg_error;			/* slave 10G only */
	u32	tx_carrier_sense_errors;	/* slave */
	u32	tx_bytes;
	u32	tx_64B_frames;
	u32	tx_65_to_127B_frames;
	u32	tx_128_to_255B_frames;
	u32	tx_256_to_511B_frames;
	u32	tx_512_to_1023B_frames;
	u32	tx_1024B_frames;
	u32	net_bytes;
	u32	rx_bottom_fअगरo_drop;
	u32	rx_port_mask_drop;
	u32	rx_top_fअगरo_drop;
	u32	ale_rate_limit_drop;
	u32	ale_vid_ingress_drop;
	u32	ale_da_eq_sa_drop;
	u32	__rsvd_0[3];
	u32	ale_unknown_ucast;
	u32	ale_unknown_ucast_bytes;
	u32	ale_unknown_mcast;
	u32	ale_unknown_mcast_bytes;
	u32	ale_unknown_bcast;
	u32	ale_unknown_bcast_bytes;
	u32	ale_pol_match;
	u32	ale_pol_match_red;		/* NU */
	u32	ale_pol_match_yellow;		/* NU */
	u32	__rsvd_1[44];
	u32	tx_mem_protect_err;
	/* following NU only */
	u32	tx_pri0;
	u32	tx_pri1;
	u32	tx_pri2;
	u32	tx_pri3;
	u32	tx_pri4;
	u32	tx_pri5;
	u32	tx_pri6;
	u32	tx_pri7;
	u32	tx_pri0_bcnt;
	u32	tx_pri1_bcnt;
	u32	tx_pri2_bcnt;
	u32	tx_pri3_bcnt;
	u32	tx_pri4_bcnt;
	u32	tx_pri5_bcnt;
	u32	tx_pri6_bcnt;
	u32	tx_pri7_bcnt;
	u32	tx_pri0_drop;
	u32	tx_pri1_drop;
	u32	tx_pri2_drop;
	u32	tx_pri3_drop;
	u32	tx_pri4_drop;
	u32	tx_pri5_drop;
	u32	tx_pri6_drop;
	u32	tx_pri7_drop;
	u32	tx_pri0_drop_bcnt;
	u32	tx_pri1_drop_bcnt;
	u32	tx_pri2_drop_bcnt;
	u32	tx_pri3_drop_bcnt;
	u32	tx_pri4_drop_bcnt;
	u32	tx_pri5_drop_bcnt;
	u32	tx_pri6_drop_bcnt;
	u32	tx_pri7_drop_bcnt;
पूर्ण;

#घोषणा GBENU_HW_STATS_REG_MAP_SZ	0x200

काष्ठा gbe_ss_regs अणु
	u32	id_ver;
	u32	synce_count;
	u32	synce_mux;
पूर्ण;

काष्ठा gbe_ss_regs_ofs अणु
	u16	id_ver;
	u16	control;
	u16	rgmii_status; /* 2U */
पूर्ण;

काष्ठा gbe_चयन_regs अणु
	u32	id_ver;
	u32	control;
	u32	soft_reset;
	u32	stat_port_en;
	u32	ptype;
	u32	soft_idle;
	u32	thru_rate;
	u32	gap_thresh;
	u32	tx_start_wds;
	u32	flow_control;
पूर्ण;

काष्ठा gbe_चयन_regs_ofs अणु
	u16	id_ver;
	u16	control;
	u16	soft_reset;
	u16	emcontrol;
	u16	stat_port_en;
	u16	ptype;
	u16	flow_control;
पूर्ण;

काष्ठा gbe_port_regs अणु
	u32	max_blks;
	u32	blk_cnt;
	u32	port_vlan;
	u32	tx_pri_map;
	u32	sa_lo;
	u32	sa_hi;
	u32	ts_ctl;
	u32	ts_seq_ltype;
	u32	ts_vlan;
	u32	ts_ctl_ltype2;
	u32	ts_ctl2;
पूर्ण;

काष्ठा gbe_port_regs_ofs अणु
	u16	port_vlan;
	u16	tx_pri_map;
	u16     rx_pri_map;
	u16	sa_lo;
	u16	sa_hi;
	u16	ts_ctl;
	u16	ts_seq_ltype;
	u16	ts_vlan;
	u16	ts_ctl_ltype2;
	u16	ts_ctl2;
	u16	rx_maxlen;	/* 2U, NU */
पूर्ण;

काष्ठा gbe_host_port_regs अणु
	u32	src_id;
	u32	port_vlan;
	u32	rx_pri_map;
	u32	rx_maxlen;
पूर्ण;

काष्ठा gbe_host_port_regs_ofs अणु
	u16	port_vlan;
	u16	tx_pri_map;
	u16	rx_maxlen;
पूर्ण;

काष्ठा gbe_emac_regs अणु
	u32	id_ver;
	u32	mac_control;
	u32	mac_status;
	u32	soft_reset;
	u32	rx_maxlen;
	u32	__reserved_0;
	u32	rx_छोड़ो;
	u32	tx_छोड़ो;
	u32	__reserved_1;
	u32	rx_pri_map;
	u32	rsvd[6];
पूर्ण;

काष्ठा gbe_emac_regs_ofs अणु
	u16	mac_control;
	u16	soft_reset;
	u16	rx_maxlen;
पूर्ण;

काष्ठा gbe_hw_stats अणु
	u32	rx_good_frames;
	u32	rx_broadcast_frames;
	u32	rx_multicast_frames;
	u32	rx_छोड़ो_frames;
	u32	rx_crc_errors;
	u32	rx_align_code_errors;
	u32	rx_oversized_frames;
	u32	rx_jabber_frames;
	u32	rx_undersized_frames;
	u32	rx_fragments;
	u32	__pad_0[2];
	u32	rx_bytes;
	u32	tx_good_frames;
	u32	tx_broadcast_frames;
	u32	tx_multicast_frames;
	u32	tx_छोड़ो_frames;
	u32	tx_deferred_frames;
	u32	tx_collision_frames;
	u32	tx_single_coll_frames;
	u32	tx_mult_coll_frames;
	u32	tx_excessive_collisions;
	u32	tx_late_collisions;
	u32	tx_underrun;
	u32	tx_carrier_sense_errors;
	u32	tx_bytes;
	u32	tx_64byte_frames;
	u32	tx_65_to_127byte_frames;
	u32	tx_128_to_255byte_frames;
	u32	tx_256_to_511byte_frames;
	u32	tx_512_to_1023byte_frames;
	u32	tx_1024byte_frames;
	u32	net_bytes;
	u32	rx_sof_overruns;
	u32	rx_mof_overruns;
	u32	rx_dma_overruns;
पूर्ण;

#घोषणा GBE_MAX_HW_STAT_MODS			9
#घोषणा GBE_HW_STATS_REG_MAP_SZ			0x100

काष्ठा ts_ctl अणु
	पूर्णांक     uni;
	u8      dst_port_map;
	u8      maddr_map;
	u8      ts_mcast_type;
पूर्ण;

काष्ठा gbe_slave अणु
	व्योम __iomem			*port_regs;
	व्योम __iomem			*emac_regs;
	काष्ठा gbe_port_regs_ofs	port_regs_ofs;
	काष्ठा gbe_emac_regs_ofs	emac_regs_ofs;
	पूर्णांक				slave_num; /* 0 based logical number */
	पूर्णांक				port_num;  /* actual port number */
	atomic_t			link_state;
	bool				खोलो;
	काष्ठा phy_device		*phy;
	u32				link_पूर्णांकerface;
	u32				mac_control;
	u8				phy_port_t;
	काष्ठा device_node		*node;
	काष्ठा device_node		*phy_node;
	काष्ठा ts_ctl                   ts_ctl;
	काष्ठा list_head		slave_list;
पूर्ण;

काष्ठा gbe_priv अणु
	काष्ठा device			*dev;
	काष्ठा netcp_device		*netcp_device;
	काष्ठा समयr_list		समयr;
	u32				num_slaves;
	u32				ale_ports;
	bool				enable_ale;
	u8				max_num_slaves;
	u8				max_num_ports; /* max_num_slaves + 1 */
	u8				num_stats_mods;
	काष्ठा netcp_tx_pipe		tx_pipe;

	पूर्णांक				host_port;
	u32				rx_packet_max;
	u32				ss_version;
	u32				stats_en_mask;

	व्योम __iomem			*ss_regs;
	व्योम __iomem			*चयन_regs;
	व्योम __iomem			*host_port_regs;
	व्योम __iomem			*ale_reg;
	व्योम __iomem                    *cpts_reg;
	व्योम __iomem			*sgmii_port_regs;
	व्योम __iomem			*sgmii_port34_regs;
	व्योम __iomem			*xgbe_serdes_regs;
	व्योम __iomem			*hw_stats_regs[GBE_MAX_HW_STAT_MODS];

	काष्ठा gbe_ss_regs_ofs		ss_regs_ofs;
	काष्ठा gbe_चयन_regs_ofs	चयन_regs_ofs;
	काष्ठा gbe_host_port_regs_ofs	host_port_regs_ofs;

	काष्ठा cpsw_ale			*ale;
	अचिन्हित पूर्णांक			tx_queue_id;
	स्थिर अक्षर			*dma_chan_name;

	काष्ठा list_head		gbe_पूर्णांकf_head;
	काष्ठा list_head		secondary_slaves;
	काष्ठा net_device		*dummy_ndev;

	u64				*hw_stats;
	u32				*hw_stats_prev;
	स्थिर काष्ठा netcp_ethtool_stat *et_stats;
	पूर्णांक				num_et_stats;
	/*  Lock क्रम updating the hwstats */
	spinlock_t			hw_stats_lock;

	पूर्णांक                             cpts_रेजिस्टरed;
	काष्ठा cpts                     *cpts;
	पूर्णांक				rx_ts_enabled;
	पूर्णांक				tx_ts_enabled;
पूर्ण;

काष्ठा gbe_पूर्णांकf अणु
	काष्ठा net_device	*ndev;
	काष्ठा device		*dev;
	काष्ठा gbe_priv		*gbe_dev;
	काष्ठा netcp_tx_pipe	tx_pipe;
	काष्ठा gbe_slave	*slave;
	काष्ठा list_head	gbe_पूर्णांकf_list;
	अचिन्हित दीर्घ		active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
पूर्ण;

अटल काष्ठा netcp_module gbe_module;
अटल काष्ठा netcp_module xgbe_module;

/* Statistic management */
काष्ठा netcp_ethtool_stat अणु
	अक्षर desc[ETH_GSTRING_LEN];
	पूर्णांक type;
	u32 size;
	पूर्णांक offset;
पूर्ण;

#घोषणा GBE_STATSA_INFO(field)						\
अणु									\
	"GBE_A:"#field, GBE_STATSA_MODULE,				\
	माप_field(काष्ठा gbe_hw_stats, field),			\
	दुरत्व(काष्ठा gbe_hw_stats, field)				\
पूर्ण

#घोषणा GBE_STATSB_INFO(field)						\
अणु									\
	"GBE_B:"#field, GBE_STATSB_MODULE,				\
	माप_field(काष्ठा gbe_hw_stats, field),			\
	दुरत्व(काष्ठा gbe_hw_stats, field)				\
पूर्ण

#घोषणा GBE_STATSC_INFO(field)						\
अणु									\
	"GBE_C:"#field, GBE_STATSC_MODULE,				\
	माप_field(काष्ठा gbe_hw_stats, field),			\
	दुरत्व(काष्ठा gbe_hw_stats, field)				\
पूर्ण

#घोषणा GBE_STATSD_INFO(field)						\
अणु									\
	"GBE_D:"#field, GBE_STATSD_MODULE,				\
	माप_field(काष्ठा gbe_hw_stats, field),			\
	दुरत्व(काष्ठा gbe_hw_stats, field)				\
पूर्ण

अटल स्थिर काष्ठा netcp_ethtool_stat gbe13_et_stats[] = अणु
	/* GBE module A */
	GBE_STATSA_INFO(rx_good_frames),
	GBE_STATSA_INFO(rx_broadcast_frames),
	GBE_STATSA_INFO(rx_multicast_frames),
	GBE_STATSA_INFO(rx_छोड़ो_frames),
	GBE_STATSA_INFO(rx_crc_errors),
	GBE_STATSA_INFO(rx_align_code_errors),
	GBE_STATSA_INFO(rx_oversized_frames),
	GBE_STATSA_INFO(rx_jabber_frames),
	GBE_STATSA_INFO(rx_undersized_frames),
	GBE_STATSA_INFO(rx_fragments),
	GBE_STATSA_INFO(rx_bytes),
	GBE_STATSA_INFO(tx_good_frames),
	GBE_STATSA_INFO(tx_broadcast_frames),
	GBE_STATSA_INFO(tx_multicast_frames),
	GBE_STATSA_INFO(tx_छोड़ो_frames),
	GBE_STATSA_INFO(tx_deferred_frames),
	GBE_STATSA_INFO(tx_collision_frames),
	GBE_STATSA_INFO(tx_single_coll_frames),
	GBE_STATSA_INFO(tx_mult_coll_frames),
	GBE_STATSA_INFO(tx_excessive_collisions),
	GBE_STATSA_INFO(tx_late_collisions),
	GBE_STATSA_INFO(tx_underrun),
	GBE_STATSA_INFO(tx_carrier_sense_errors),
	GBE_STATSA_INFO(tx_bytes),
	GBE_STATSA_INFO(tx_64byte_frames),
	GBE_STATSA_INFO(tx_65_to_127byte_frames),
	GBE_STATSA_INFO(tx_128_to_255byte_frames),
	GBE_STATSA_INFO(tx_256_to_511byte_frames),
	GBE_STATSA_INFO(tx_512_to_1023byte_frames),
	GBE_STATSA_INFO(tx_1024byte_frames),
	GBE_STATSA_INFO(net_bytes),
	GBE_STATSA_INFO(rx_sof_overruns),
	GBE_STATSA_INFO(rx_mof_overruns),
	GBE_STATSA_INFO(rx_dma_overruns),
	/* GBE module B */
	GBE_STATSB_INFO(rx_good_frames),
	GBE_STATSB_INFO(rx_broadcast_frames),
	GBE_STATSB_INFO(rx_multicast_frames),
	GBE_STATSB_INFO(rx_छोड़ो_frames),
	GBE_STATSB_INFO(rx_crc_errors),
	GBE_STATSB_INFO(rx_align_code_errors),
	GBE_STATSB_INFO(rx_oversized_frames),
	GBE_STATSB_INFO(rx_jabber_frames),
	GBE_STATSB_INFO(rx_undersized_frames),
	GBE_STATSB_INFO(rx_fragments),
	GBE_STATSB_INFO(rx_bytes),
	GBE_STATSB_INFO(tx_good_frames),
	GBE_STATSB_INFO(tx_broadcast_frames),
	GBE_STATSB_INFO(tx_multicast_frames),
	GBE_STATSB_INFO(tx_छोड़ो_frames),
	GBE_STATSB_INFO(tx_deferred_frames),
	GBE_STATSB_INFO(tx_collision_frames),
	GBE_STATSB_INFO(tx_single_coll_frames),
	GBE_STATSB_INFO(tx_mult_coll_frames),
	GBE_STATSB_INFO(tx_excessive_collisions),
	GBE_STATSB_INFO(tx_late_collisions),
	GBE_STATSB_INFO(tx_underrun),
	GBE_STATSB_INFO(tx_carrier_sense_errors),
	GBE_STATSB_INFO(tx_bytes),
	GBE_STATSB_INFO(tx_64byte_frames),
	GBE_STATSB_INFO(tx_65_to_127byte_frames),
	GBE_STATSB_INFO(tx_128_to_255byte_frames),
	GBE_STATSB_INFO(tx_256_to_511byte_frames),
	GBE_STATSB_INFO(tx_512_to_1023byte_frames),
	GBE_STATSB_INFO(tx_1024byte_frames),
	GBE_STATSB_INFO(net_bytes),
	GBE_STATSB_INFO(rx_sof_overruns),
	GBE_STATSB_INFO(rx_mof_overruns),
	GBE_STATSB_INFO(rx_dma_overruns),
	/* GBE module C */
	GBE_STATSC_INFO(rx_good_frames),
	GBE_STATSC_INFO(rx_broadcast_frames),
	GBE_STATSC_INFO(rx_multicast_frames),
	GBE_STATSC_INFO(rx_छोड़ो_frames),
	GBE_STATSC_INFO(rx_crc_errors),
	GBE_STATSC_INFO(rx_align_code_errors),
	GBE_STATSC_INFO(rx_oversized_frames),
	GBE_STATSC_INFO(rx_jabber_frames),
	GBE_STATSC_INFO(rx_undersized_frames),
	GBE_STATSC_INFO(rx_fragments),
	GBE_STATSC_INFO(rx_bytes),
	GBE_STATSC_INFO(tx_good_frames),
	GBE_STATSC_INFO(tx_broadcast_frames),
	GBE_STATSC_INFO(tx_multicast_frames),
	GBE_STATSC_INFO(tx_छोड़ो_frames),
	GBE_STATSC_INFO(tx_deferred_frames),
	GBE_STATSC_INFO(tx_collision_frames),
	GBE_STATSC_INFO(tx_single_coll_frames),
	GBE_STATSC_INFO(tx_mult_coll_frames),
	GBE_STATSC_INFO(tx_excessive_collisions),
	GBE_STATSC_INFO(tx_late_collisions),
	GBE_STATSC_INFO(tx_underrun),
	GBE_STATSC_INFO(tx_carrier_sense_errors),
	GBE_STATSC_INFO(tx_bytes),
	GBE_STATSC_INFO(tx_64byte_frames),
	GBE_STATSC_INFO(tx_65_to_127byte_frames),
	GBE_STATSC_INFO(tx_128_to_255byte_frames),
	GBE_STATSC_INFO(tx_256_to_511byte_frames),
	GBE_STATSC_INFO(tx_512_to_1023byte_frames),
	GBE_STATSC_INFO(tx_1024byte_frames),
	GBE_STATSC_INFO(net_bytes),
	GBE_STATSC_INFO(rx_sof_overruns),
	GBE_STATSC_INFO(rx_mof_overruns),
	GBE_STATSC_INFO(rx_dma_overruns),
	/* GBE module D */
	GBE_STATSD_INFO(rx_good_frames),
	GBE_STATSD_INFO(rx_broadcast_frames),
	GBE_STATSD_INFO(rx_multicast_frames),
	GBE_STATSD_INFO(rx_छोड़ो_frames),
	GBE_STATSD_INFO(rx_crc_errors),
	GBE_STATSD_INFO(rx_align_code_errors),
	GBE_STATSD_INFO(rx_oversized_frames),
	GBE_STATSD_INFO(rx_jabber_frames),
	GBE_STATSD_INFO(rx_undersized_frames),
	GBE_STATSD_INFO(rx_fragments),
	GBE_STATSD_INFO(rx_bytes),
	GBE_STATSD_INFO(tx_good_frames),
	GBE_STATSD_INFO(tx_broadcast_frames),
	GBE_STATSD_INFO(tx_multicast_frames),
	GBE_STATSD_INFO(tx_छोड़ो_frames),
	GBE_STATSD_INFO(tx_deferred_frames),
	GBE_STATSD_INFO(tx_collision_frames),
	GBE_STATSD_INFO(tx_single_coll_frames),
	GBE_STATSD_INFO(tx_mult_coll_frames),
	GBE_STATSD_INFO(tx_excessive_collisions),
	GBE_STATSD_INFO(tx_late_collisions),
	GBE_STATSD_INFO(tx_underrun),
	GBE_STATSD_INFO(tx_carrier_sense_errors),
	GBE_STATSD_INFO(tx_bytes),
	GBE_STATSD_INFO(tx_64byte_frames),
	GBE_STATSD_INFO(tx_65_to_127byte_frames),
	GBE_STATSD_INFO(tx_128_to_255byte_frames),
	GBE_STATSD_INFO(tx_256_to_511byte_frames),
	GBE_STATSD_INFO(tx_512_to_1023byte_frames),
	GBE_STATSD_INFO(tx_1024byte_frames),
	GBE_STATSD_INFO(net_bytes),
	GBE_STATSD_INFO(rx_sof_overruns),
	GBE_STATSD_INFO(rx_mof_overruns),
	GBE_STATSD_INFO(rx_dma_overruns),
पूर्ण;

/* This is the size of entries in GBENU_STATS_HOST */
#घोषणा GBENU_ET_STATS_HOST_SIZE	52

#घोषणा GBENU_STATS_HOST(field)					\
अणु								\
	"GBE_HOST:"#field, GBENU_STATS0_MODULE,			\
	माप_field(काष्ठा gbenu_hw_stats, field),		\
	दुरत्व(काष्ठा gbenu_hw_stats, field)			\
पूर्ण

/* This is the size of entries in GBENU_STATS_PORT */
#घोषणा GBENU_ET_STATS_PORT_SIZE	65

#घोषणा GBENU_STATS_P1(field)					\
अणु								\
	"GBE_P1:"#field, GBENU_STATS1_MODULE,			\
	माप_field(काष्ठा gbenu_hw_stats, field),		\
	दुरत्व(काष्ठा gbenu_hw_stats, field)			\
पूर्ण

#घोषणा GBENU_STATS_P2(field)					\
अणु								\
	"GBE_P2:"#field, GBENU_STATS2_MODULE,			\
	माप_field(काष्ठा gbenu_hw_stats, field),		\
	दुरत्व(काष्ठा gbenu_hw_stats, field)			\
पूर्ण

#घोषणा GBENU_STATS_P3(field)					\
अणु								\
	"GBE_P3:"#field, GBENU_STATS3_MODULE,			\
	माप_field(काष्ठा gbenu_hw_stats, field),		\
	दुरत्व(काष्ठा gbenu_hw_stats, field)			\
पूर्ण

#घोषणा GBENU_STATS_P4(field)					\
अणु								\
	"GBE_P4:"#field, GBENU_STATS4_MODULE,			\
	माप_field(काष्ठा gbenu_hw_stats, field),		\
	दुरत्व(काष्ठा gbenu_hw_stats, field)			\
पूर्ण

#घोषणा GBENU_STATS_P5(field)					\
अणु								\
	"GBE_P5:"#field, GBENU_STATS5_MODULE,			\
	माप_field(काष्ठा gbenu_hw_stats, field),		\
	दुरत्व(काष्ठा gbenu_hw_stats, field)			\
पूर्ण

#घोषणा GBENU_STATS_P6(field)					\
अणु								\
	"GBE_P6:"#field, GBENU_STATS6_MODULE,			\
	माप_field(काष्ठा gbenu_hw_stats, field),		\
	दुरत्व(काष्ठा gbenu_hw_stats, field)			\
पूर्ण

#घोषणा GBENU_STATS_P7(field)					\
अणु								\
	"GBE_P7:"#field, GBENU_STATS7_MODULE,			\
	माप_field(काष्ठा gbenu_hw_stats, field),		\
	दुरत्व(काष्ठा gbenu_hw_stats, field)			\
पूर्ण

#घोषणा GBENU_STATS_P8(field)					\
अणु								\
	"GBE_P8:"#field, GBENU_STATS8_MODULE,			\
	माप_field(काष्ठा gbenu_hw_stats, field),		\
	दुरत्व(काष्ठा gbenu_hw_stats, field)			\
पूर्ण

अटल स्थिर काष्ठा netcp_ethtool_stat gbenu_et_stats[] = अणु
	/* GBENU Host Module */
	GBENU_STATS_HOST(rx_good_frames),
	GBENU_STATS_HOST(rx_broadcast_frames),
	GBENU_STATS_HOST(rx_multicast_frames),
	GBENU_STATS_HOST(rx_crc_errors),
	GBENU_STATS_HOST(rx_oversized_frames),
	GBENU_STATS_HOST(rx_undersized_frames),
	GBENU_STATS_HOST(ale_drop),
	GBENU_STATS_HOST(ale_overrun_drop),
	GBENU_STATS_HOST(rx_bytes),
	GBENU_STATS_HOST(tx_good_frames),
	GBENU_STATS_HOST(tx_broadcast_frames),
	GBENU_STATS_HOST(tx_multicast_frames),
	GBENU_STATS_HOST(tx_bytes),
	GBENU_STATS_HOST(tx_64B_frames),
	GBENU_STATS_HOST(tx_65_to_127B_frames),
	GBENU_STATS_HOST(tx_128_to_255B_frames),
	GBENU_STATS_HOST(tx_256_to_511B_frames),
	GBENU_STATS_HOST(tx_512_to_1023B_frames),
	GBENU_STATS_HOST(tx_1024B_frames),
	GBENU_STATS_HOST(net_bytes),
	GBENU_STATS_HOST(rx_bottom_fअगरo_drop),
	GBENU_STATS_HOST(rx_port_mask_drop),
	GBENU_STATS_HOST(rx_top_fअगरo_drop),
	GBENU_STATS_HOST(ale_rate_limit_drop),
	GBENU_STATS_HOST(ale_vid_ingress_drop),
	GBENU_STATS_HOST(ale_da_eq_sa_drop),
	GBENU_STATS_HOST(ale_unknown_ucast),
	GBENU_STATS_HOST(ale_unknown_ucast_bytes),
	GBENU_STATS_HOST(ale_unknown_mcast),
	GBENU_STATS_HOST(ale_unknown_mcast_bytes),
	GBENU_STATS_HOST(ale_unknown_bcast),
	GBENU_STATS_HOST(ale_unknown_bcast_bytes),
	GBENU_STATS_HOST(ale_pol_match),
	GBENU_STATS_HOST(ale_pol_match_red),
	GBENU_STATS_HOST(ale_pol_match_yellow),
	GBENU_STATS_HOST(tx_mem_protect_err),
	GBENU_STATS_HOST(tx_pri0_drop),
	GBENU_STATS_HOST(tx_pri1_drop),
	GBENU_STATS_HOST(tx_pri2_drop),
	GBENU_STATS_HOST(tx_pri3_drop),
	GBENU_STATS_HOST(tx_pri4_drop),
	GBENU_STATS_HOST(tx_pri5_drop),
	GBENU_STATS_HOST(tx_pri6_drop),
	GBENU_STATS_HOST(tx_pri7_drop),
	GBENU_STATS_HOST(tx_pri0_drop_bcnt),
	GBENU_STATS_HOST(tx_pri1_drop_bcnt),
	GBENU_STATS_HOST(tx_pri2_drop_bcnt),
	GBENU_STATS_HOST(tx_pri3_drop_bcnt),
	GBENU_STATS_HOST(tx_pri4_drop_bcnt),
	GBENU_STATS_HOST(tx_pri5_drop_bcnt),
	GBENU_STATS_HOST(tx_pri6_drop_bcnt),
	GBENU_STATS_HOST(tx_pri7_drop_bcnt),
	/* GBENU Module 1 */
	GBENU_STATS_P1(rx_good_frames),
	GBENU_STATS_P1(rx_broadcast_frames),
	GBENU_STATS_P1(rx_multicast_frames),
	GBENU_STATS_P1(rx_छोड़ो_frames),
	GBENU_STATS_P1(rx_crc_errors),
	GBENU_STATS_P1(rx_align_code_errors),
	GBENU_STATS_P1(rx_oversized_frames),
	GBENU_STATS_P1(rx_jabber_frames),
	GBENU_STATS_P1(rx_undersized_frames),
	GBENU_STATS_P1(rx_fragments),
	GBENU_STATS_P1(ale_drop),
	GBENU_STATS_P1(ale_overrun_drop),
	GBENU_STATS_P1(rx_bytes),
	GBENU_STATS_P1(tx_good_frames),
	GBENU_STATS_P1(tx_broadcast_frames),
	GBENU_STATS_P1(tx_multicast_frames),
	GBENU_STATS_P1(tx_छोड़ो_frames),
	GBENU_STATS_P1(tx_deferred_frames),
	GBENU_STATS_P1(tx_collision_frames),
	GBENU_STATS_P1(tx_single_coll_frames),
	GBENU_STATS_P1(tx_mult_coll_frames),
	GBENU_STATS_P1(tx_excessive_collisions),
	GBENU_STATS_P1(tx_late_collisions),
	GBENU_STATS_P1(rx_ipg_error),
	GBENU_STATS_P1(tx_carrier_sense_errors),
	GBENU_STATS_P1(tx_bytes),
	GBENU_STATS_P1(tx_64B_frames),
	GBENU_STATS_P1(tx_65_to_127B_frames),
	GBENU_STATS_P1(tx_128_to_255B_frames),
	GBENU_STATS_P1(tx_256_to_511B_frames),
	GBENU_STATS_P1(tx_512_to_1023B_frames),
	GBENU_STATS_P1(tx_1024B_frames),
	GBENU_STATS_P1(net_bytes),
	GBENU_STATS_P1(rx_bottom_fअगरo_drop),
	GBENU_STATS_P1(rx_port_mask_drop),
	GBENU_STATS_P1(rx_top_fअगरo_drop),
	GBENU_STATS_P1(ale_rate_limit_drop),
	GBENU_STATS_P1(ale_vid_ingress_drop),
	GBENU_STATS_P1(ale_da_eq_sa_drop),
	GBENU_STATS_P1(ale_unknown_ucast),
	GBENU_STATS_P1(ale_unknown_ucast_bytes),
	GBENU_STATS_P1(ale_unknown_mcast),
	GBENU_STATS_P1(ale_unknown_mcast_bytes),
	GBENU_STATS_P1(ale_unknown_bcast),
	GBENU_STATS_P1(ale_unknown_bcast_bytes),
	GBENU_STATS_P1(ale_pol_match),
	GBENU_STATS_P1(ale_pol_match_red),
	GBENU_STATS_P1(ale_pol_match_yellow),
	GBENU_STATS_P1(tx_mem_protect_err),
	GBENU_STATS_P1(tx_pri0_drop),
	GBENU_STATS_P1(tx_pri1_drop),
	GBENU_STATS_P1(tx_pri2_drop),
	GBENU_STATS_P1(tx_pri3_drop),
	GBENU_STATS_P1(tx_pri4_drop),
	GBENU_STATS_P1(tx_pri5_drop),
	GBENU_STATS_P1(tx_pri6_drop),
	GBENU_STATS_P1(tx_pri7_drop),
	GBENU_STATS_P1(tx_pri0_drop_bcnt),
	GBENU_STATS_P1(tx_pri1_drop_bcnt),
	GBENU_STATS_P1(tx_pri2_drop_bcnt),
	GBENU_STATS_P1(tx_pri3_drop_bcnt),
	GBENU_STATS_P1(tx_pri4_drop_bcnt),
	GBENU_STATS_P1(tx_pri5_drop_bcnt),
	GBENU_STATS_P1(tx_pri6_drop_bcnt),
	GBENU_STATS_P1(tx_pri7_drop_bcnt),
	/* GBENU Module 2 */
	GBENU_STATS_P2(rx_good_frames),
	GBENU_STATS_P2(rx_broadcast_frames),
	GBENU_STATS_P2(rx_multicast_frames),
	GBENU_STATS_P2(rx_छोड़ो_frames),
	GBENU_STATS_P2(rx_crc_errors),
	GBENU_STATS_P2(rx_align_code_errors),
	GBENU_STATS_P2(rx_oversized_frames),
	GBENU_STATS_P2(rx_jabber_frames),
	GBENU_STATS_P2(rx_undersized_frames),
	GBENU_STATS_P2(rx_fragments),
	GBENU_STATS_P2(ale_drop),
	GBENU_STATS_P2(ale_overrun_drop),
	GBENU_STATS_P2(rx_bytes),
	GBENU_STATS_P2(tx_good_frames),
	GBENU_STATS_P2(tx_broadcast_frames),
	GBENU_STATS_P2(tx_multicast_frames),
	GBENU_STATS_P2(tx_छोड़ो_frames),
	GBENU_STATS_P2(tx_deferred_frames),
	GBENU_STATS_P2(tx_collision_frames),
	GBENU_STATS_P2(tx_single_coll_frames),
	GBENU_STATS_P2(tx_mult_coll_frames),
	GBENU_STATS_P2(tx_excessive_collisions),
	GBENU_STATS_P2(tx_late_collisions),
	GBENU_STATS_P2(rx_ipg_error),
	GBENU_STATS_P2(tx_carrier_sense_errors),
	GBENU_STATS_P2(tx_bytes),
	GBENU_STATS_P2(tx_64B_frames),
	GBENU_STATS_P2(tx_65_to_127B_frames),
	GBENU_STATS_P2(tx_128_to_255B_frames),
	GBENU_STATS_P2(tx_256_to_511B_frames),
	GBENU_STATS_P2(tx_512_to_1023B_frames),
	GBENU_STATS_P2(tx_1024B_frames),
	GBENU_STATS_P2(net_bytes),
	GBENU_STATS_P2(rx_bottom_fअगरo_drop),
	GBENU_STATS_P2(rx_port_mask_drop),
	GBENU_STATS_P2(rx_top_fअगरo_drop),
	GBENU_STATS_P2(ale_rate_limit_drop),
	GBENU_STATS_P2(ale_vid_ingress_drop),
	GBENU_STATS_P2(ale_da_eq_sa_drop),
	GBENU_STATS_P2(ale_unknown_ucast),
	GBENU_STATS_P2(ale_unknown_ucast_bytes),
	GBENU_STATS_P2(ale_unknown_mcast),
	GBENU_STATS_P2(ale_unknown_mcast_bytes),
	GBENU_STATS_P2(ale_unknown_bcast),
	GBENU_STATS_P2(ale_unknown_bcast_bytes),
	GBENU_STATS_P2(ale_pol_match),
	GBENU_STATS_P2(ale_pol_match_red),
	GBENU_STATS_P2(ale_pol_match_yellow),
	GBENU_STATS_P2(tx_mem_protect_err),
	GBENU_STATS_P2(tx_pri0_drop),
	GBENU_STATS_P2(tx_pri1_drop),
	GBENU_STATS_P2(tx_pri2_drop),
	GBENU_STATS_P2(tx_pri3_drop),
	GBENU_STATS_P2(tx_pri4_drop),
	GBENU_STATS_P2(tx_pri5_drop),
	GBENU_STATS_P2(tx_pri6_drop),
	GBENU_STATS_P2(tx_pri7_drop),
	GBENU_STATS_P2(tx_pri0_drop_bcnt),
	GBENU_STATS_P2(tx_pri1_drop_bcnt),
	GBENU_STATS_P2(tx_pri2_drop_bcnt),
	GBENU_STATS_P2(tx_pri3_drop_bcnt),
	GBENU_STATS_P2(tx_pri4_drop_bcnt),
	GBENU_STATS_P2(tx_pri5_drop_bcnt),
	GBENU_STATS_P2(tx_pri6_drop_bcnt),
	GBENU_STATS_P2(tx_pri7_drop_bcnt),
	/* GBENU Module 3 */
	GBENU_STATS_P3(rx_good_frames),
	GBENU_STATS_P3(rx_broadcast_frames),
	GBENU_STATS_P3(rx_multicast_frames),
	GBENU_STATS_P3(rx_छोड़ो_frames),
	GBENU_STATS_P3(rx_crc_errors),
	GBENU_STATS_P3(rx_align_code_errors),
	GBENU_STATS_P3(rx_oversized_frames),
	GBENU_STATS_P3(rx_jabber_frames),
	GBENU_STATS_P3(rx_undersized_frames),
	GBENU_STATS_P3(rx_fragments),
	GBENU_STATS_P3(ale_drop),
	GBENU_STATS_P3(ale_overrun_drop),
	GBENU_STATS_P3(rx_bytes),
	GBENU_STATS_P3(tx_good_frames),
	GBENU_STATS_P3(tx_broadcast_frames),
	GBENU_STATS_P3(tx_multicast_frames),
	GBENU_STATS_P3(tx_छोड़ो_frames),
	GBENU_STATS_P3(tx_deferred_frames),
	GBENU_STATS_P3(tx_collision_frames),
	GBENU_STATS_P3(tx_single_coll_frames),
	GBENU_STATS_P3(tx_mult_coll_frames),
	GBENU_STATS_P3(tx_excessive_collisions),
	GBENU_STATS_P3(tx_late_collisions),
	GBENU_STATS_P3(rx_ipg_error),
	GBENU_STATS_P3(tx_carrier_sense_errors),
	GBENU_STATS_P3(tx_bytes),
	GBENU_STATS_P3(tx_64B_frames),
	GBENU_STATS_P3(tx_65_to_127B_frames),
	GBENU_STATS_P3(tx_128_to_255B_frames),
	GBENU_STATS_P3(tx_256_to_511B_frames),
	GBENU_STATS_P3(tx_512_to_1023B_frames),
	GBENU_STATS_P3(tx_1024B_frames),
	GBENU_STATS_P3(net_bytes),
	GBENU_STATS_P3(rx_bottom_fअगरo_drop),
	GBENU_STATS_P3(rx_port_mask_drop),
	GBENU_STATS_P3(rx_top_fअगरo_drop),
	GBENU_STATS_P3(ale_rate_limit_drop),
	GBENU_STATS_P3(ale_vid_ingress_drop),
	GBENU_STATS_P3(ale_da_eq_sa_drop),
	GBENU_STATS_P3(ale_unknown_ucast),
	GBENU_STATS_P3(ale_unknown_ucast_bytes),
	GBENU_STATS_P3(ale_unknown_mcast),
	GBENU_STATS_P3(ale_unknown_mcast_bytes),
	GBENU_STATS_P3(ale_unknown_bcast),
	GBENU_STATS_P3(ale_unknown_bcast_bytes),
	GBENU_STATS_P3(ale_pol_match),
	GBENU_STATS_P3(ale_pol_match_red),
	GBENU_STATS_P3(ale_pol_match_yellow),
	GBENU_STATS_P3(tx_mem_protect_err),
	GBENU_STATS_P3(tx_pri0_drop),
	GBENU_STATS_P3(tx_pri1_drop),
	GBENU_STATS_P3(tx_pri2_drop),
	GBENU_STATS_P3(tx_pri3_drop),
	GBENU_STATS_P3(tx_pri4_drop),
	GBENU_STATS_P3(tx_pri5_drop),
	GBENU_STATS_P3(tx_pri6_drop),
	GBENU_STATS_P3(tx_pri7_drop),
	GBENU_STATS_P3(tx_pri0_drop_bcnt),
	GBENU_STATS_P3(tx_pri1_drop_bcnt),
	GBENU_STATS_P3(tx_pri2_drop_bcnt),
	GBENU_STATS_P3(tx_pri3_drop_bcnt),
	GBENU_STATS_P3(tx_pri4_drop_bcnt),
	GBENU_STATS_P3(tx_pri5_drop_bcnt),
	GBENU_STATS_P3(tx_pri6_drop_bcnt),
	GBENU_STATS_P3(tx_pri7_drop_bcnt),
	/* GBENU Module 4 */
	GBENU_STATS_P4(rx_good_frames),
	GBENU_STATS_P4(rx_broadcast_frames),
	GBENU_STATS_P4(rx_multicast_frames),
	GBENU_STATS_P4(rx_छोड़ो_frames),
	GBENU_STATS_P4(rx_crc_errors),
	GBENU_STATS_P4(rx_align_code_errors),
	GBENU_STATS_P4(rx_oversized_frames),
	GBENU_STATS_P4(rx_jabber_frames),
	GBENU_STATS_P4(rx_undersized_frames),
	GBENU_STATS_P4(rx_fragments),
	GBENU_STATS_P4(ale_drop),
	GBENU_STATS_P4(ale_overrun_drop),
	GBENU_STATS_P4(rx_bytes),
	GBENU_STATS_P4(tx_good_frames),
	GBENU_STATS_P4(tx_broadcast_frames),
	GBENU_STATS_P4(tx_multicast_frames),
	GBENU_STATS_P4(tx_छोड़ो_frames),
	GBENU_STATS_P4(tx_deferred_frames),
	GBENU_STATS_P4(tx_collision_frames),
	GBENU_STATS_P4(tx_single_coll_frames),
	GBENU_STATS_P4(tx_mult_coll_frames),
	GBENU_STATS_P4(tx_excessive_collisions),
	GBENU_STATS_P4(tx_late_collisions),
	GBENU_STATS_P4(rx_ipg_error),
	GBENU_STATS_P4(tx_carrier_sense_errors),
	GBENU_STATS_P4(tx_bytes),
	GBENU_STATS_P4(tx_64B_frames),
	GBENU_STATS_P4(tx_65_to_127B_frames),
	GBENU_STATS_P4(tx_128_to_255B_frames),
	GBENU_STATS_P4(tx_256_to_511B_frames),
	GBENU_STATS_P4(tx_512_to_1023B_frames),
	GBENU_STATS_P4(tx_1024B_frames),
	GBENU_STATS_P4(net_bytes),
	GBENU_STATS_P4(rx_bottom_fअगरo_drop),
	GBENU_STATS_P4(rx_port_mask_drop),
	GBENU_STATS_P4(rx_top_fअगरo_drop),
	GBENU_STATS_P4(ale_rate_limit_drop),
	GBENU_STATS_P4(ale_vid_ingress_drop),
	GBENU_STATS_P4(ale_da_eq_sa_drop),
	GBENU_STATS_P4(ale_unknown_ucast),
	GBENU_STATS_P4(ale_unknown_ucast_bytes),
	GBENU_STATS_P4(ale_unknown_mcast),
	GBENU_STATS_P4(ale_unknown_mcast_bytes),
	GBENU_STATS_P4(ale_unknown_bcast),
	GBENU_STATS_P4(ale_unknown_bcast_bytes),
	GBENU_STATS_P4(ale_pol_match),
	GBENU_STATS_P4(ale_pol_match_red),
	GBENU_STATS_P4(ale_pol_match_yellow),
	GBENU_STATS_P4(tx_mem_protect_err),
	GBENU_STATS_P4(tx_pri0_drop),
	GBENU_STATS_P4(tx_pri1_drop),
	GBENU_STATS_P4(tx_pri2_drop),
	GBENU_STATS_P4(tx_pri3_drop),
	GBENU_STATS_P4(tx_pri4_drop),
	GBENU_STATS_P4(tx_pri5_drop),
	GBENU_STATS_P4(tx_pri6_drop),
	GBENU_STATS_P4(tx_pri7_drop),
	GBENU_STATS_P4(tx_pri0_drop_bcnt),
	GBENU_STATS_P4(tx_pri1_drop_bcnt),
	GBENU_STATS_P4(tx_pri2_drop_bcnt),
	GBENU_STATS_P4(tx_pri3_drop_bcnt),
	GBENU_STATS_P4(tx_pri4_drop_bcnt),
	GBENU_STATS_P4(tx_pri5_drop_bcnt),
	GBENU_STATS_P4(tx_pri6_drop_bcnt),
	GBENU_STATS_P4(tx_pri7_drop_bcnt),
	/* GBENU Module 5 */
	GBENU_STATS_P5(rx_good_frames),
	GBENU_STATS_P5(rx_broadcast_frames),
	GBENU_STATS_P5(rx_multicast_frames),
	GBENU_STATS_P5(rx_छोड़ो_frames),
	GBENU_STATS_P5(rx_crc_errors),
	GBENU_STATS_P5(rx_align_code_errors),
	GBENU_STATS_P5(rx_oversized_frames),
	GBENU_STATS_P5(rx_jabber_frames),
	GBENU_STATS_P5(rx_undersized_frames),
	GBENU_STATS_P5(rx_fragments),
	GBENU_STATS_P5(ale_drop),
	GBENU_STATS_P5(ale_overrun_drop),
	GBENU_STATS_P5(rx_bytes),
	GBENU_STATS_P5(tx_good_frames),
	GBENU_STATS_P5(tx_broadcast_frames),
	GBENU_STATS_P5(tx_multicast_frames),
	GBENU_STATS_P5(tx_छोड़ो_frames),
	GBENU_STATS_P5(tx_deferred_frames),
	GBENU_STATS_P5(tx_collision_frames),
	GBENU_STATS_P5(tx_single_coll_frames),
	GBENU_STATS_P5(tx_mult_coll_frames),
	GBENU_STATS_P5(tx_excessive_collisions),
	GBENU_STATS_P5(tx_late_collisions),
	GBENU_STATS_P5(rx_ipg_error),
	GBENU_STATS_P5(tx_carrier_sense_errors),
	GBENU_STATS_P5(tx_bytes),
	GBENU_STATS_P5(tx_64B_frames),
	GBENU_STATS_P5(tx_65_to_127B_frames),
	GBENU_STATS_P5(tx_128_to_255B_frames),
	GBENU_STATS_P5(tx_256_to_511B_frames),
	GBENU_STATS_P5(tx_512_to_1023B_frames),
	GBENU_STATS_P5(tx_1024B_frames),
	GBENU_STATS_P5(net_bytes),
	GBENU_STATS_P5(rx_bottom_fअगरo_drop),
	GBENU_STATS_P5(rx_port_mask_drop),
	GBENU_STATS_P5(rx_top_fअगरo_drop),
	GBENU_STATS_P5(ale_rate_limit_drop),
	GBENU_STATS_P5(ale_vid_ingress_drop),
	GBENU_STATS_P5(ale_da_eq_sa_drop),
	GBENU_STATS_P5(ale_unknown_ucast),
	GBENU_STATS_P5(ale_unknown_ucast_bytes),
	GBENU_STATS_P5(ale_unknown_mcast),
	GBENU_STATS_P5(ale_unknown_mcast_bytes),
	GBENU_STATS_P5(ale_unknown_bcast),
	GBENU_STATS_P5(ale_unknown_bcast_bytes),
	GBENU_STATS_P5(ale_pol_match),
	GBENU_STATS_P5(ale_pol_match_red),
	GBENU_STATS_P5(ale_pol_match_yellow),
	GBENU_STATS_P5(tx_mem_protect_err),
	GBENU_STATS_P5(tx_pri0_drop),
	GBENU_STATS_P5(tx_pri1_drop),
	GBENU_STATS_P5(tx_pri2_drop),
	GBENU_STATS_P5(tx_pri3_drop),
	GBENU_STATS_P5(tx_pri4_drop),
	GBENU_STATS_P5(tx_pri5_drop),
	GBENU_STATS_P5(tx_pri6_drop),
	GBENU_STATS_P5(tx_pri7_drop),
	GBENU_STATS_P5(tx_pri0_drop_bcnt),
	GBENU_STATS_P5(tx_pri1_drop_bcnt),
	GBENU_STATS_P5(tx_pri2_drop_bcnt),
	GBENU_STATS_P5(tx_pri3_drop_bcnt),
	GBENU_STATS_P5(tx_pri4_drop_bcnt),
	GBENU_STATS_P5(tx_pri5_drop_bcnt),
	GBENU_STATS_P5(tx_pri6_drop_bcnt),
	GBENU_STATS_P5(tx_pri7_drop_bcnt),
	/* GBENU Module 6 */
	GBENU_STATS_P6(rx_good_frames),
	GBENU_STATS_P6(rx_broadcast_frames),
	GBENU_STATS_P6(rx_multicast_frames),
	GBENU_STATS_P6(rx_छोड़ो_frames),
	GBENU_STATS_P6(rx_crc_errors),
	GBENU_STATS_P6(rx_align_code_errors),
	GBENU_STATS_P6(rx_oversized_frames),
	GBENU_STATS_P6(rx_jabber_frames),
	GBENU_STATS_P6(rx_undersized_frames),
	GBENU_STATS_P6(rx_fragments),
	GBENU_STATS_P6(ale_drop),
	GBENU_STATS_P6(ale_overrun_drop),
	GBENU_STATS_P6(rx_bytes),
	GBENU_STATS_P6(tx_good_frames),
	GBENU_STATS_P6(tx_broadcast_frames),
	GBENU_STATS_P6(tx_multicast_frames),
	GBENU_STATS_P6(tx_छोड़ो_frames),
	GBENU_STATS_P6(tx_deferred_frames),
	GBENU_STATS_P6(tx_collision_frames),
	GBENU_STATS_P6(tx_single_coll_frames),
	GBENU_STATS_P6(tx_mult_coll_frames),
	GBENU_STATS_P6(tx_excessive_collisions),
	GBENU_STATS_P6(tx_late_collisions),
	GBENU_STATS_P6(rx_ipg_error),
	GBENU_STATS_P6(tx_carrier_sense_errors),
	GBENU_STATS_P6(tx_bytes),
	GBENU_STATS_P6(tx_64B_frames),
	GBENU_STATS_P6(tx_65_to_127B_frames),
	GBENU_STATS_P6(tx_128_to_255B_frames),
	GBENU_STATS_P6(tx_256_to_511B_frames),
	GBENU_STATS_P6(tx_512_to_1023B_frames),
	GBENU_STATS_P6(tx_1024B_frames),
	GBENU_STATS_P6(net_bytes),
	GBENU_STATS_P6(rx_bottom_fअगरo_drop),
	GBENU_STATS_P6(rx_port_mask_drop),
	GBENU_STATS_P6(rx_top_fअगरo_drop),
	GBENU_STATS_P6(ale_rate_limit_drop),
	GBENU_STATS_P6(ale_vid_ingress_drop),
	GBENU_STATS_P6(ale_da_eq_sa_drop),
	GBENU_STATS_P6(ale_unknown_ucast),
	GBENU_STATS_P6(ale_unknown_ucast_bytes),
	GBENU_STATS_P6(ale_unknown_mcast),
	GBENU_STATS_P6(ale_unknown_mcast_bytes),
	GBENU_STATS_P6(ale_unknown_bcast),
	GBENU_STATS_P6(ale_unknown_bcast_bytes),
	GBENU_STATS_P6(ale_pol_match),
	GBENU_STATS_P6(ale_pol_match_red),
	GBENU_STATS_P6(ale_pol_match_yellow),
	GBENU_STATS_P6(tx_mem_protect_err),
	GBENU_STATS_P6(tx_pri0_drop),
	GBENU_STATS_P6(tx_pri1_drop),
	GBENU_STATS_P6(tx_pri2_drop),
	GBENU_STATS_P6(tx_pri3_drop),
	GBENU_STATS_P6(tx_pri4_drop),
	GBENU_STATS_P6(tx_pri5_drop),
	GBENU_STATS_P6(tx_pri6_drop),
	GBENU_STATS_P6(tx_pri7_drop),
	GBENU_STATS_P6(tx_pri0_drop_bcnt),
	GBENU_STATS_P6(tx_pri1_drop_bcnt),
	GBENU_STATS_P6(tx_pri2_drop_bcnt),
	GBENU_STATS_P6(tx_pri3_drop_bcnt),
	GBENU_STATS_P6(tx_pri4_drop_bcnt),
	GBENU_STATS_P6(tx_pri5_drop_bcnt),
	GBENU_STATS_P6(tx_pri6_drop_bcnt),
	GBENU_STATS_P6(tx_pri7_drop_bcnt),
	/* GBENU Module 7 */
	GBENU_STATS_P7(rx_good_frames),
	GBENU_STATS_P7(rx_broadcast_frames),
	GBENU_STATS_P7(rx_multicast_frames),
	GBENU_STATS_P7(rx_छोड़ो_frames),
	GBENU_STATS_P7(rx_crc_errors),
	GBENU_STATS_P7(rx_align_code_errors),
	GBENU_STATS_P7(rx_oversized_frames),
	GBENU_STATS_P7(rx_jabber_frames),
	GBENU_STATS_P7(rx_undersized_frames),
	GBENU_STATS_P7(rx_fragments),
	GBENU_STATS_P7(ale_drop),
	GBENU_STATS_P7(ale_overrun_drop),
	GBENU_STATS_P7(rx_bytes),
	GBENU_STATS_P7(tx_good_frames),
	GBENU_STATS_P7(tx_broadcast_frames),
	GBENU_STATS_P7(tx_multicast_frames),
	GBENU_STATS_P7(tx_छोड़ो_frames),
	GBENU_STATS_P7(tx_deferred_frames),
	GBENU_STATS_P7(tx_collision_frames),
	GBENU_STATS_P7(tx_single_coll_frames),
	GBENU_STATS_P7(tx_mult_coll_frames),
	GBENU_STATS_P7(tx_excessive_collisions),
	GBENU_STATS_P7(tx_late_collisions),
	GBENU_STATS_P7(rx_ipg_error),
	GBENU_STATS_P7(tx_carrier_sense_errors),
	GBENU_STATS_P7(tx_bytes),
	GBENU_STATS_P7(tx_64B_frames),
	GBENU_STATS_P7(tx_65_to_127B_frames),
	GBENU_STATS_P7(tx_128_to_255B_frames),
	GBENU_STATS_P7(tx_256_to_511B_frames),
	GBENU_STATS_P7(tx_512_to_1023B_frames),
	GBENU_STATS_P7(tx_1024B_frames),
	GBENU_STATS_P7(net_bytes),
	GBENU_STATS_P7(rx_bottom_fअगरo_drop),
	GBENU_STATS_P7(rx_port_mask_drop),
	GBENU_STATS_P7(rx_top_fअगरo_drop),
	GBENU_STATS_P7(ale_rate_limit_drop),
	GBENU_STATS_P7(ale_vid_ingress_drop),
	GBENU_STATS_P7(ale_da_eq_sa_drop),
	GBENU_STATS_P7(ale_unknown_ucast),
	GBENU_STATS_P7(ale_unknown_ucast_bytes),
	GBENU_STATS_P7(ale_unknown_mcast),
	GBENU_STATS_P7(ale_unknown_mcast_bytes),
	GBENU_STATS_P7(ale_unknown_bcast),
	GBENU_STATS_P7(ale_unknown_bcast_bytes),
	GBENU_STATS_P7(ale_pol_match),
	GBENU_STATS_P7(ale_pol_match_red),
	GBENU_STATS_P7(ale_pol_match_yellow),
	GBENU_STATS_P7(tx_mem_protect_err),
	GBENU_STATS_P7(tx_pri0_drop),
	GBENU_STATS_P7(tx_pri1_drop),
	GBENU_STATS_P7(tx_pri2_drop),
	GBENU_STATS_P7(tx_pri3_drop),
	GBENU_STATS_P7(tx_pri4_drop),
	GBENU_STATS_P7(tx_pri5_drop),
	GBENU_STATS_P7(tx_pri6_drop),
	GBENU_STATS_P7(tx_pri7_drop),
	GBENU_STATS_P7(tx_pri0_drop_bcnt),
	GBENU_STATS_P7(tx_pri1_drop_bcnt),
	GBENU_STATS_P7(tx_pri2_drop_bcnt),
	GBENU_STATS_P7(tx_pri3_drop_bcnt),
	GBENU_STATS_P7(tx_pri4_drop_bcnt),
	GBENU_STATS_P7(tx_pri5_drop_bcnt),
	GBENU_STATS_P7(tx_pri6_drop_bcnt),
	GBENU_STATS_P7(tx_pri7_drop_bcnt),
	/* GBENU Module 8 */
	GBENU_STATS_P8(rx_good_frames),
	GBENU_STATS_P8(rx_broadcast_frames),
	GBENU_STATS_P8(rx_multicast_frames),
	GBENU_STATS_P8(rx_छोड़ो_frames),
	GBENU_STATS_P8(rx_crc_errors),
	GBENU_STATS_P8(rx_align_code_errors),
	GBENU_STATS_P8(rx_oversized_frames),
	GBENU_STATS_P8(rx_jabber_frames),
	GBENU_STATS_P8(rx_undersized_frames),
	GBENU_STATS_P8(rx_fragments),
	GBENU_STATS_P8(ale_drop),
	GBENU_STATS_P8(ale_overrun_drop),
	GBENU_STATS_P8(rx_bytes),
	GBENU_STATS_P8(tx_good_frames),
	GBENU_STATS_P8(tx_broadcast_frames),
	GBENU_STATS_P8(tx_multicast_frames),
	GBENU_STATS_P8(tx_छोड़ो_frames),
	GBENU_STATS_P8(tx_deferred_frames),
	GBENU_STATS_P8(tx_collision_frames),
	GBENU_STATS_P8(tx_single_coll_frames),
	GBENU_STATS_P8(tx_mult_coll_frames),
	GBENU_STATS_P8(tx_excessive_collisions),
	GBENU_STATS_P8(tx_late_collisions),
	GBENU_STATS_P8(rx_ipg_error),
	GBENU_STATS_P8(tx_carrier_sense_errors),
	GBENU_STATS_P8(tx_bytes),
	GBENU_STATS_P8(tx_64B_frames),
	GBENU_STATS_P8(tx_65_to_127B_frames),
	GBENU_STATS_P8(tx_128_to_255B_frames),
	GBENU_STATS_P8(tx_256_to_511B_frames),
	GBENU_STATS_P8(tx_512_to_1023B_frames),
	GBENU_STATS_P8(tx_1024B_frames),
	GBENU_STATS_P8(net_bytes),
	GBENU_STATS_P8(rx_bottom_fअगरo_drop),
	GBENU_STATS_P8(rx_port_mask_drop),
	GBENU_STATS_P8(rx_top_fअगरo_drop),
	GBENU_STATS_P8(ale_rate_limit_drop),
	GBENU_STATS_P8(ale_vid_ingress_drop),
	GBENU_STATS_P8(ale_da_eq_sa_drop),
	GBENU_STATS_P8(ale_unknown_ucast),
	GBENU_STATS_P8(ale_unknown_ucast_bytes),
	GBENU_STATS_P8(ale_unknown_mcast),
	GBENU_STATS_P8(ale_unknown_mcast_bytes),
	GBENU_STATS_P8(ale_unknown_bcast),
	GBENU_STATS_P8(ale_unknown_bcast_bytes),
	GBENU_STATS_P8(ale_pol_match),
	GBENU_STATS_P8(ale_pol_match_red),
	GBENU_STATS_P8(ale_pol_match_yellow),
	GBENU_STATS_P8(tx_mem_protect_err),
	GBENU_STATS_P8(tx_pri0_drop),
	GBENU_STATS_P8(tx_pri1_drop),
	GBENU_STATS_P8(tx_pri2_drop),
	GBENU_STATS_P8(tx_pri3_drop),
	GBENU_STATS_P8(tx_pri4_drop),
	GBENU_STATS_P8(tx_pri5_drop),
	GBENU_STATS_P8(tx_pri6_drop),
	GBENU_STATS_P8(tx_pri7_drop),
	GBENU_STATS_P8(tx_pri0_drop_bcnt),
	GBENU_STATS_P8(tx_pri1_drop_bcnt),
	GBENU_STATS_P8(tx_pri2_drop_bcnt),
	GBENU_STATS_P8(tx_pri3_drop_bcnt),
	GBENU_STATS_P8(tx_pri4_drop_bcnt),
	GBENU_STATS_P8(tx_pri5_drop_bcnt),
	GBENU_STATS_P8(tx_pri6_drop_bcnt),
	GBENU_STATS_P8(tx_pri7_drop_bcnt),
पूर्ण;

#घोषणा XGBE_STATS0_INFO(field)				\
अणु							\
	"GBE_0:"#field, XGBE_STATS0_MODULE,		\
	माप_field(काष्ठा xgbe_hw_stats, field),	\
	दुरत्व(काष्ठा xgbe_hw_stats, field)		\
पूर्ण

#घोषणा XGBE_STATS1_INFO(field)				\
अणु							\
	"GBE_1:"#field, XGBE_STATS1_MODULE,		\
	माप_field(काष्ठा xgbe_hw_stats, field),	\
	दुरत्व(काष्ठा xgbe_hw_stats, field)		\
पूर्ण

#घोषणा XGBE_STATS2_INFO(field)				\
अणु							\
	"GBE_2:"#field, XGBE_STATS2_MODULE,		\
	माप_field(काष्ठा xgbe_hw_stats, field),	\
	दुरत्व(काष्ठा xgbe_hw_stats, field)		\
पूर्ण

अटल स्थिर काष्ठा netcp_ethtool_stat xgbe10_et_stats[] = अणु
	/* GBE module 0 */
	XGBE_STATS0_INFO(rx_good_frames),
	XGBE_STATS0_INFO(rx_broadcast_frames),
	XGBE_STATS0_INFO(rx_multicast_frames),
	XGBE_STATS0_INFO(rx_oversized_frames),
	XGBE_STATS0_INFO(rx_undersized_frames),
	XGBE_STATS0_INFO(overrun_type4),
	XGBE_STATS0_INFO(overrun_type5),
	XGBE_STATS0_INFO(rx_bytes),
	XGBE_STATS0_INFO(tx_good_frames),
	XGBE_STATS0_INFO(tx_broadcast_frames),
	XGBE_STATS0_INFO(tx_multicast_frames),
	XGBE_STATS0_INFO(tx_bytes),
	XGBE_STATS0_INFO(tx_64byte_frames),
	XGBE_STATS0_INFO(tx_65_to_127byte_frames),
	XGBE_STATS0_INFO(tx_128_to_255byte_frames),
	XGBE_STATS0_INFO(tx_256_to_511byte_frames),
	XGBE_STATS0_INFO(tx_512_to_1023byte_frames),
	XGBE_STATS0_INFO(tx_1024byte_frames),
	XGBE_STATS0_INFO(net_bytes),
	XGBE_STATS0_INFO(rx_sof_overruns),
	XGBE_STATS0_INFO(rx_mof_overruns),
	XGBE_STATS0_INFO(rx_dma_overruns),
	/* XGBE module 1 */
	XGBE_STATS1_INFO(rx_good_frames),
	XGBE_STATS1_INFO(rx_broadcast_frames),
	XGBE_STATS1_INFO(rx_multicast_frames),
	XGBE_STATS1_INFO(rx_छोड़ो_frames),
	XGBE_STATS1_INFO(rx_crc_errors),
	XGBE_STATS1_INFO(rx_align_code_errors),
	XGBE_STATS1_INFO(rx_oversized_frames),
	XGBE_STATS1_INFO(rx_jabber_frames),
	XGBE_STATS1_INFO(rx_undersized_frames),
	XGBE_STATS1_INFO(rx_fragments),
	XGBE_STATS1_INFO(overrun_type4),
	XGBE_STATS1_INFO(overrun_type5),
	XGBE_STATS1_INFO(rx_bytes),
	XGBE_STATS1_INFO(tx_good_frames),
	XGBE_STATS1_INFO(tx_broadcast_frames),
	XGBE_STATS1_INFO(tx_multicast_frames),
	XGBE_STATS1_INFO(tx_छोड़ो_frames),
	XGBE_STATS1_INFO(tx_deferred_frames),
	XGBE_STATS1_INFO(tx_collision_frames),
	XGBE_STATS1_INFO(tx_single_coll_frames),
	XGBE_STATS1_INFO(tx_mult_coll_frames),
	XGBE_STATS1_INFO(tx_excessive_collisions),
	XGBE_STATS1_INFO(tx_late_collisions),
	XGBE_STATS1_INFO(tx_underrun),
	XGBE_STATS1_INFO(tx_carrier_sense_errors),
	XGBE_STATS1_INFO(tx_bytes),
	XGBE_STATS1_INFO(tx_64byte_frames),
	XGBE_STATS1_INFO(tx_65_to_127byte_frames),
	XGBE_STATS1_INFO(tx_128_to_255byte_frames),
	XGBE_STATS1_INFO(tx_256_to_511byte_frames),
	XGBE_STATS1_INFO(tx_512_to_1023byte_frames),
	XGBE_STATS1_INFO(tx_1024byte_frames),
	XGBE_STATS1_INFO(net_bytes),
	XGBE_STATS1_INFO(rx_sof_overruns),
	XGBE_STATS1_INFO(rx_mof_overruns),
	XGBE_STATS1_INFO(rx_dma_overruns),
	/* XGBE module 2 */
	XGBE_STATS2_INFO(rx_good_frames),
	XGBE_STATS2_INFO(rx_broadcast_frames),
	XGBE_STATS2_INFO(rx_multicast_frames),
	XGBE_STATS2_INFO(rx_छोड़ो_frames),
	XGBE_STATS2_INFO(rx_crc_errors),
	XGBE_STATS2_INFO(rx_align_code_errors),
	XGBE_STATS2_INFO(rx_oversized_frames),
	XGBE_STATS2_INFO(rx_jabber_frames),
	XGBE_STATS2_INFO(rx_undersized_frames),
	XGBE_STATS2_INFO(rx_fragments),
	XGBE_STATS2_INFO(overrun_type4),
	XGBE_STATS2_INFO(overrun_type5),
	XGBE_STATS2_INFO(rx_bytes),
	XGBE_STATS2_INFO(tx_good_frames),
	XGBE_STATS2_INFO(tx_broadcast_frames),
	XGBE_STATS2_INFO(tx_multicast_frames),
	XGBE_STATS2_INFO(tx_छोड़ो_frames),
	XGBE_STATS2_INFO(tx_deferred_frames),
	XGBE_STATS2_INFO(tx_collision_frames),
	XGBE_STATS2_INFO(tx_single_coll_frames),
	XGBE_STATS2_INFO(tx_mult_coll_frames),
	XGBE_STATS2_INFO(tx_excessive_collisions),
	XGBE_STATS2_INFO(tx_late_collisions),
	XGBE_STATS2_INFO(tx_underrun),
	XGBE_STATS2_INFO(tx_carrier_sense_errors),
	XGBE_STATS2_INFO(tx_bytes),
	XGBE_STATS2_INFO(tx_64byte_frames),
	XGBE_STATS2_INFO(tx_65_to_127byte_frames),
	XGBE_STATS2_INFO(tx_128_to_255byte_frames),
	XGBE_STATS2_INFO(tx_256_to_511byte_frames),
	XGBE_STATS2_INFO(tx_512_to_1023byte_frames),
	XGBE_STATS2_INFO(tx_1024byte_frames),
	XGBE_STATS2_INFO(net_bytes),
	XGBE_STATS2_INFO(rx_sof_overruns),
	XGBE_STATS2_INFO(rx_mof_overruns),
	XGBE_STATS2_INFO(rx_dma_overruns),
पूर्ण;

#घोषणा क्रम_each_पूर्णांकf(i, priv) \
	list_क्रम_each_entry((i), &(priv)->gbe_पूर्णांकf_head, gbe_पूर्णांकf_list)

#घोषणा क्रम_each_sec_slave(slave, priv) \
	list_क्रम_each_entry((slave), &(priv)->secondary_slaves, slave_list)

#घोषणा first_sec_slave(priv)					\
	list_first_entry(&priv->secondary_slaves, \
			काष्ठा gbe_slave, slave_list)

अटल व्योम keystone_get_drvinfo(काष्ठा net_device *ndev,
				 काष्ठा ethtool_drvinfo *info)
अणु
	म_नकलन(info->driver, NETCP_DRIVER_NAME, माप(info->driver));
	म_नकलन(info->version, NETCP_DRIVER_VERSION, माप(info->version));
पूर्ण

अटल u32 keystone_get_msglevel(काष्ठा net_device *ndev)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);

	वापस netcp->msg_enable;
पूर्ण

अटल व्योम keystone_set_msglevel(काष्ठा net_device *ndev, u32 value)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);

	netcp->msg_enable = value;
पूर्ण

अटल काष्ठा gbe_पूर्णांकf *keystone_get_पूर्णांकf_data(काष्ठा netcp_पूर्णांकf *netcp)
अणु
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf;

	gbe_पूर्णांकf = netcp_module_get_पूर्णांकf_data(&gbe_module, netcp);
	अगर (!gbe_पूर्णांकf)
		gbe_पूर्णांकf = netcp_module_get_पूर्णांकf_data(&xgbe_module, netcp);

	वापस gbe_पूर्णांकf;
पूर्ण

अटल व्योम keystone_get_stat_strings(काष्ठा net_device *ndev,
				      uपूर्णांक32_t stringset, uपूर्णांक8_t *data)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf;
	काष्ठा gbe_priv *gbe_dev;
	पूर्णांक i;

	gbe_पूर्णांकf = keystone_get_पूर्णांकf_data(netcp);
	अगर (!gbe_पूर्णांकf)
		वापस;
	gbe_dev = gbe_पूर्णांकf->gbe_dev;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < gbe_dev->num_et_stats; i++) अणु
			स_नकल(data, gbe_dev->et_stats[i].desc,
			       ETH_GSTRING_LEN);
			data += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	हाल ETH_SS_TEST:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक keystone_get_sset_count(काष्ठा net_device *ndev, पूर्णांक stringset)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf;
	काष्ठा gbe_priv *gbe_dev;

	gbe_पूर्णांकf = keystone_get_पूर्णांकf_data(netcp);
	अगर (!gbe_पूर्णांकf)
		वापस -EINVAL;
	gbe_dev = gbe_पूर्णांकf->gbe_dev;

	चयन (stringset) अणु
	हाल ETH_SS_TEST:
		वापस 0;
	हाल ETH_SS_STATS:
		वापस gbe_dev->num_et_stats;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम gbe_reset_mod_stats(काष्ठा gbe_priv *gbe_dev, पूर्णांक stats_mod)
अणु
	व्योम __iomem *base = gbe_dev->hw_stats_regs[stats_mod];
	u32  __iomem *p_stats_entry;
	पूर्णांक i;

	क्रम (i = 0; i < gbe_dev->num_et_stats; i++) अणु
		अगर (gbe_dev->et_stats[i].type == stats_mod) अणु
			p_stats_entry = base + gbe_dev->et_stats[i].offset;
			gbe_dev->hw_stats[i] = 0;
			gbe_dev->hw_stats_prev[i] = पढ़ोl(p_stats_entry);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम gbe_update_hw_stats_entry(काष्ठा gbe_priv *gbe_dev,
					     पूर्णांक et_stats_entry)
अणु
	व्योम __iomem *base = शून्य;
	u32  __iomem *p_stats_entry;
	u32 curr, delta;

	/* The hw_stats_regs poपूर्णांकers are alपढ़ोy
	 * properly set to poपूर्णांक to the right base:
	 */
	base = gbe_dev->hw_stats_regs[gbe_dev->et_stats[et_stats_entry].type];
	p_stats_entry = base + gbe_dev->et_stats[et_stats_entry].offset;
	curr = पढ़ोl(p_stats_entry);
	delta = curr - gbe_dev->hw_stats_prev[et_stats_entry];
	gbe_dev->hw_stats_prev[et_stats_entry] = curr;
	gbe_dev->hw_stats[et_stats_entry] += delta;
पूर्ण

अटल व्योम gbe_update_stats(काष्ठा gbe_priv *gbe_dev, uपूर्णांक64_t *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < gbe_dev->num_et_stats; i++) अणु
		gbe_update_hw_stats_entry(gbe_dev, i);

		अगर (data)
			data[i] = gbe_dev->hw_stats[i];
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम gbe_stats_mod_visible_ver14(काष्ठा gbe_priv *gbe_dev,
					       पूर्णांक stats_mod)
अणु
	u32 val;

	val = पढ़ोl(GBE_REG_ADDR(gbe_dev, चयन_regs, stat_port_en));

	चयन (stats_mod) अणु
	हाल GBE_STATSA_MODULE:
	हाल GBE_STATSB_MODULE:
		val &= ~GBE_STATS_CD_SEL;
		अवरोध;
	हाल GBE_STATSC_MODULE:
	हाल GBE_STATSD_MODULE:
		val |= GBE_STATS_CD_SEL;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	/* make the stat module visible */
	ग_लिखोl(val, GBE_REG_ADDR(gbe_dev, चयन_regs, stat_port_en));
पूर्ण

अटल व्योम gbe_reset_mod_stats_ver14(काष्ठा gbe_priv *gbe_dev, पूर्णांक stats_mod)
अणु
	gbe_stats_mod_visible_ver14(gbe_dev, stats_mod);
	gbe_reset_mod_stats(gbe_dev, stats_mod);
पूर्ण

अटल व्योम gbe_update_stats_ver14(काष्ठा gbe_priv *gbe_dev, uपूर्णांक64_t *data)
अणु
	u32 half_num_et_stats = (gbe_dev->num_et_stats / 2);
	पूर्णांक et_entry, j, pair;

	क्रम (pair = 0; pair < 2; pair++) अणु
		gbe_stats_mod_visible_ver14(gbe_dev, (pair ?
						      GBE_STATSC_MODULE :
						      GBE_STATSA_MODULE));

		क्रम (j = 0; j < half_num_et_stats; j++) अणु
			et_entry = pair * half_num_et_stats + j;
			gbe_update_hw_stats_entry(gbe_dev, et_entry);

			अगर (data)
				data[et_entry] = gbe_dev->hw_stats[et_entry];
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम keystone_get_ethtool_stats(काष्ठा net_device *ndev,
				       काष्ठा ethtool_stats *stats,
				       uपूर्णांक64_t *data)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf;
	काष्ठा gbe_priv *gbe_dev;

	gbe_पूर्णांकf = keystone_get_पूर्णांकf_data(netcp);
	अगर (!gbe_पूर्णांकf)
		वापस;

	gbe_dev = gbe_पूर्णांकf->gbe_dev;
	spin_lock_bh(&gbe_dev->hw_stats_lock);
	अगर (IS_SS_ID_VER_14(gbe_dev))
		gbe_update_stats_ver14(gbe_dev, data);
	अन्यथा
		gbe_update_stats(gbe_dev, data);
	spin_unlock_bh(&gbe_dev->hw_stats_lock);
पूर्ण

अटल पूर्णांक keystone_get_link_ksettings(काष्ठा net_device *ndev,
				       काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	काष्ठा phy_device *phy = ndev->phydev;
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf;

	अगर (!phy)
		वापस -EINVAL;

	gbe_पूर्णांकf = keystone_get_पूर्णांकf_data(netcp);
	अगर (!gbe_पूर्णांकf)
		वापस -EINVAL;

	अगर (!gbe_पूर्णांकf->slave)
		वापस -EINVAL;

	phy_ethtool_ksettings_get(phy, cmd);
	cmd->base.port = gbe_पूर्णांकf->slave->phy_port_t;

	वापस 0;
पूर्ण

अटल पूर्णांक keystone_set_link_ksettings(काष्ठा net_device *ndev,
				       स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	काष्ठा phy_device *phy = ndev->phydev;
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf;
	u8 port = cmd->base.port;
	u32 advertising, supported;
	u32 features;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);
	ethtool_convert_link_mode_to_legacy_u32(&supported,
						cmd->link_modes.supported);
	features = advertising & supported;

	अगर (!phy)
		वापस -EINVAL;

	gbe_पूर्णांकf = keystone_get_पूर्णांकf_data(netcp);
	अगर (!gbe_पूर्णांकf)
		वापस -EINVAL;

	अगर (!gbe_पूर्णांकf->slave)
		वापस -EINVAL;

	अगर (port != gbe_पूर्णांकf->slave->phy_port_t) अणु
		अगर ((port == PORT_TP) && !(features & ADVERTISED_TP))
			वापस -EINVAL;

		अगर ((port == PORT_AUI) && !(features & ADVERTISED_AUI))
			वापस -EINVAL;

		अगर ((port == PORT_BNC) && !(features & ADVERTISED_BNC))
			वापस -EINVAL;

		अगर ((port == PORT_MII) && !(features & ADVERTISED_MII))
			वापस -EINVAL;

		अगर ((port == PORT_FIBRE) && !(features & ADVERTISED_FIBRE))
			वापस -EINVAL;
	पूर्ण

	gbe_पूर्णांकf->slave->phy_port_t = port;
	वापस phy_ethtool_ksettings_set(phy, cmd);
पूर्ण

#अगर IS_ENABLED(CONFIG_TI_CPTS)
अटल पूर्णांक keystone_get_ts_info(काष्ठा net_device *ndev,
				काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf;

	gbe_पूर्णांकf = netcp_module_get_पूर्णांकf_data(&gbe_module, netcp);
	अगर (!gbe_पूर्णांकf || !gbe_पूर्णांकf->gbe_dev->cpts)
		वापस -EINVAL;

	info->so_बारtamping =
		SOF_TIMESTAMPING_TX_HARDWARE |
		SOF_TIMESTAMPING_TX_SOFTWARE |
		SOF_TIMESTAMPING_RX_HARDWARE |
		SOF_TIMESTAMPING_RX_SOFTWARE |
		SOF_TIMESTAMPING_SOFTWARE |
		SOF_TIMESTAMPING_RAW_HARDWARE;
	info->phc_index = gbe_पूर्णांकf->gbe_dev->cpts->phc_index;
	info->tx_types =
		(1 << HWTSTAMP_TX_OFF) |
		(1 << HWTSTAMP_TX_ON);
	info->rx_filters =
		(1 << HWTSTAMP_FILTER_NONE) |
		(1 << HWTSTAMP_FILTER_PTP_V1_L4_EVENT) |
		(1 << HWTSTAMP_FILTER_PTP_V2_EVENT);
	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक keystone_get_ts_info(काष्ठा net_device *ndev,
				काष्ठा ethtool_ts_info *info)
अणु
	info->so_बारtamping =
		SOF_TIMESTAMPING_TX_SOFTWARE |
		SOF_TIMESTAMPING_RX_SOFTWARE |
		SOF_TIMESTAMPING_SOFTWARE;
	info->phc_index = -1;
	info->tx_types = 0;
	info->rx_filters = 0;
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_TI_CPTS */

अटल स्थिर काष्ठा ethtool_ops keystone_ethtool_ops = अणु
	.get_drvinfo		= keystone_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_msglevel		= keystone_get_msglevel,
	.set_msglevel		= keystone_set_msglevel,
	.get_strings		= keystone_get_stat_strings,
	.get_sset_count		= keystone_get_sset_count,
	.get_ethtool_stats	= keystone_get_ethtool_stats,
	.get_link_ksettings	= keystone_get_link_ksettings,
	.set_link_ksettings	= keystone_set_link_ksettings,
	.get_ts_info		= keystone_get_ts_info,
पूर्ण;

अटल व्योम gbe_set_slave_mac(काष्ठा gbe_slave *slave,
			      काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf)
अणु
	काष्ठा net_device *ndev = gbe_पूर्णांकf->ndev;

	ग_लिखोl(mac_hi(ndev->dev_addr), GBE_REG_ADDR(slave, port_regs, sa_hi));
	ग_लिखोl(mac_lo(ndev->dev_addr), GBE_REG_ADDR(slave, port_regs, sa_lo));
पूर्ण

अटल पूर्णांक gbe_get_slave_port(काष्ठा gbe_priv *priv, u32 slave_num)
अणु
	अगर (priv->host_port == 0)
		वापस slave_num + 1;

	वापस slave_num;
पूर्ण

अटल व्योम netcp_ethss_link_state_action(काष्ठा gbe_priv *gbe_dev,
					  काष्ठा net_device *ndev,
					  काष्ठा gbe_slave *slave,
					  पूर्णांक up)
अणु
	काष्ठा phy_device *phy = slave->phy;
	u32 mac_control = 0;

	अगर (up) अणु
		mac_control = slave->mac_control;
		अगर (phy && (phy->speed == SPEED_1000)) अणु
			mac_control |= MACSL_GIG_MODE;
			mac_control &= ~MACSL_XGIG_MODE;
		पूर्ण अन्यथा अगर (phy && (phy->speed == SPEED_10000)) अणु
			mac_control |= MACSL_XGIG_MODE;
			mac_control &= ~MACSL_GIG_MODE;
		पूर्ण

		ग_लिखोl(mac_control, GBE_REG_ADDR(slave, emac_regs,
						 mac_control));

		cpsw_ale_control_set(gbe_dev->ale, slave->port_num,
				     ALE_PORT_STATE,
				     ALE_PORT_STATE_FORWARD);

		अगर (ndev && slave->खोलो &&
		    ((slave->link_पूर्णांकerface != SGMII_LINK_MAC_PHY) &&
		    (slave->link_पूर्णांकerface != RGMII_LINK_MAC_PHY) &&
		    (slave->link_पूर्णांकerface != XGMII_LINK_MAC_PHY)))
			netअगर_carrier_on(ndev);
	पूर्ण अन्यथा अणु
		ग_लिखोl(mac_control, GBE_REG_ADDR(slave, emac_regs,
						 mac_control));
		cpsw_ale_control_set(gbe_dev->ale, slave->port_num,
				     ALE_PORT_STATE,
				     ALE_PORT_STATE_DISABLE);
		अगर (ndev &&
		    ((slave->link_पूर्णांकerface != SGMII_LINK_MAC_PHY) &&
		    (slave->link_पूर्णांकerface != RGMII_LINK_MAC_PHY) &&
		    (slave->link_पूर्णांकerface != XGMII_LINK_MAC_PHY)))
			netअगर_carrier_off(ndev);
	पूर्ण

	अगर (phy)
		phy_prपूर्णांक_status(phy);
पूर्ण

अटल bool gbe_phy_link_status(काष्ठा gbe_slave *slave)
अणु
	 वापस !slave->phy || slave->phy->link;
पूर्ण

#घोषणा RGMII_REG_STATUS_LINK	BIT(0)

अटल व्योम netcp_2u_rgmii_get_port_link(काष्ठा gbe_priv *gbe_dev, bool *status)
अणु
	u32 val = 0;

	val = पढ़ोl(GBE_REG_ADDR(gbe_dev, ss_regs, rgmii_status));
	*status = !!(val & RGMII_REG_STATUS_LINK);
पूर्ण

अटल व्योम netcp_ethss_update_link_state(काष्ठा gbe_priv *gbe_dev,
					  काष्ठा gbe_slave *slave,
					  काष्ठा net_device *ndev)
अणु
	bool sw_link_state = true, phy_link_state;
	पूर्णांक sp = slave->slave_num, link_state;

	अगर (!slave->खोलो)
		वापस;

	अगर (SLAVE_LINK_IS_RGMII(slave))
		netcp_2u_rgmii_get_port_link(gbe_dev,
					     &sw_link_state);
	अगर (SLAVE_LINK_IS_SGMII(slave))
		sw_link_state =
		netcp_sgmii_get_port_link(SGMII_BASE(gbe_dev, sp), sp);

	phy_link_state = gbe_phy_link_status(slave);
	link_state = phy_link_state & sw_link_state;

	अगर (atomic_xchg(&slave->link_state, link_state) != link_state)
		netcp_ethss_link_state_action(gbe_dev, ndev, slave,
					      link_state);
पूर्ण

अटल व्योम xgbe_adjust_link(काष्ठा net_device *ndev)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf;

	gbe_पूर्णांकf = netcp_module_get_पूर्णांकf_data(&xgbe_module, netcp);
	अगर (!gbe_पूर्णांकf)
		वापस;

	netcp_ethss_update_link_state(gbe_पूर्णांकf->gbe_dev, gbe_पूर्णांकf->slave,
				      ndev);
पूर्ण

अटल व्योम gbe_adjust_link(काष्ठा net_device *ndev)
अणु
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf;

	gbe_पूर्णांकf = netcp_module_get_पूर्णांकf_data(&gbe_module, netcp);
	अगर (!gbe_पूर्णांकf)
		वापस;

	netcp_ethss_update_link_state(gbe_पूर्णांकf->gbe_dev, gbe_पूर्णांकf->slave,
				      ndev);
पूर्ण

अटल व्योम gbe_adjust_link_sec_slaves(काष्ठा net_device *ndev)
अणु
	काष्ठा gbe_priv *gbe_dev = netdev_priv(ndev);
	काष्ठा gbe_slave *slave;

	क्रम_each_sec_slave(slave, gbe_dev)
		netcp_ethss_update_link_state(gbe_dev, slave, शून्य);
पूर्ण

/* Reset EMAC
 * Soft reset is set and polled until clear, or until a समयout occurs
 */
अटल पूर्णांक gbe_port_reset(काष्ठा gbe_slave *slave)
अणु
	u32 i, v;

	/* Set the soft reset bit */
	ग_लिखोl(SOFT_RESET, GBE_REG_ADDR(slave, emac_regs, soft_reset));

	/* Wait क्रम the bit to clear */
	क्रम (i = 0; i < DEVICE_EMACSL_RESET_POLL_COUNT; i++) अणु
		v = पढ़ोl(GBE_REG_ADDR(slave, emac_regs, soft_reset));
		अगर ((v & SOFT_RESET_MASK) != SOFT_RESET)
			वापस 0;
	पूर्ण

	/* Timeout on the reset */
	वापस GMACSL_RET_WARN_RESET_INCOMPLETE;
पूर्ण

/* Configure EMAC */
अटल व्योम gbe_port_config(काष्ठा gbe_priv *gbe_dev, काष्ठा gbe_slave *slave,
			    पूर्णांक max_rx_len)
अणु
	व्योम __iomem *rx_maxlen_reg;
	u32 xgmii_mode;

	अगर (max_rx_len > NETCP_MAX_FRAME_SIZE)
		max_rx_len = NETCP_MAX_FRAME_SIZE;

	/* Enable correct MII mode at SS level */
	अगर (IS_SS_ID_XGBE(gbe_dev) &&
	    (slave->link_पूर्णांकerface >= XGMII_LINK_MAC_PHY)) अणु
		xgmii_mode = पढ़ोl(GBE_REG_ADDR(gbe_dev, ss_regs, control));
		xgmii_mode |= (1 << slave->slave_num);
		ग_लिखोl(xgmii_mode, GBE_REG_ADDR(gbe_dev, ss_regs, control));
	पूर्ण

	अगर (IS_SS_ID_MU(gbe_dev))
		rx_maxlen_reg = GBE_REG_ADDR(slave, port_regs, rx_maxlen);
	अन्यथा
		rx_maxlen_reg = GBE_REG_ADDR(slave, emac_regs, rx_maxlen);

	ग_लिखोl(max_rx_len, rx_maxlen_reg);
	ग_लिखोl(slave->mac_control, GBE_REG_ADDR(slave, emac_regs, mac_control));
पूर्ण

अटल व्योम gbe_sgmii_rtreset(काष्ठा gbe_priv *priv,
			      काष्ठा gbe_slave *slave, bool set)
अणु
	अगर (SLAVE_LINK_IS_XGMII(slave))
		वापस;

	netcp_sgmii_rtreset(SGMII_BASE(priv, slave->slave_num),
			    slave->slave_num, set);
पूर्ण

अटल व्योम gbe_slave_stop(काष्ठा gbe_पूर्णांकf *पूर्णांकf)
अणु
	काष्ठा gbe_priv *gbe_dev = पूर्णांकf->gbe_dev;
	काष्ठा gbe_slave *slave = पूर्णांकf->slave;

	अगर (!IS_SS_ID_2U(gbe_dev))
		gbe_sgmii_rtreset(gbe_dev, slave, true);
	gbe_port_reset(slave);
	/* Disable क्रमwarding */
	cpsw_ale_control_set(gbe_dev->ale, slave->port_num,
			     ALE_PORT_STATE, ALE_PORT_STATE_DISABLE);
	cpsw_ale_del_mcast(gbe_dev->ale, पूर्णांकf->ndev->broadcast,
			   1 << slave->port_num, 0, 0);

	अगर (!slave->phy)
		वापस;

	phy_stop(slave->phy);
	phy_disconnect(slave->phy);
	slave->phy = शून्य;
पूर्ण

अटल व्योम gbe_sgmii_config(काष्ठा gbe_priv *priv, काष्ठा gbe_slave *slave)
अणु
	अगर (SLAVE_LINK_IS_XGMII(slave))
		वापस;

	netcp_sgmii_reset(SGMII_BASE(priv, slave->slave_num), slave->slave_num);
	netcp_sgmii_config(SGMII_BASE(priv, slave->slave_num), slave->slave_num,
			   slave->link_पूर्णांकerface);
पूर्ण

अटल पूर्णांक gbe_slave_खोलो(काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf)
अणु
	काष्ठा gbe_priv *priv = gbe_पूर्णांकf->gbe_dev;
	काष्ठा gbe_slave *slave = gbe_पूर्णांकf->slave;
	phy_पूर्णांकerface_t phy_mode;
	bool has_phy = false;
	पूर्णांक err;

	व्योम (*hndlr)(काष्ठा net_device *) = gbe_adjust_link;

	अगर (!IS_SS_ID_2U(priv))
		gbe_sgmii_config(priv, slave);
	gbe_port_reset(slave);
	अगर (!IS_SS_ID_2U(priv))
		gbe_sgmii_rtreset(priv, slave, false);
	gbe_port_config(priv, slave, priv->rx_packet_max);
	gbe_set_slave_mac(slave, gbe_पूर्णांकf);
	/* For NU & 2U चयन, map the vlan priorities to zero
	 * as we only configure to use priority 0
	 */
	अगर (IS_SS_ID_MU(priv))
		ग_लिखोl(HOST_TX_PRI_MAP_DEFAULT,
		       GBE_REG_ADDR(slave, port_regs, rx_pri_map));

	/* enable क्रमwarding */
	cpsw_ale_control_set(priv->ale, slave->port_num,
			     ALE_PORT_STATE, ALE_PORT_STATE_FORWARD);
	cpsw_ale_add_mcast(priv->ale, gbe_पूर्णांकf->ndev->broadcast,
			   1 << slave->port_num, 0, 0, ALE_MCAST_FWD_2);

	अगर (slave->link_पूर्णांकerface == SGMII_LINK_MAC_PHY) अणु
		has_phy = true;
		phy_mode = PHY_INTERFACE_MODE_SGMII;
		slave->phy_port_t = PORT_MII;
	पूर्ण अन्यथा अगर (slave->link_पूर्णांकerface == RGMII_LINK_MAC_PHY) अणु
		has_phy = true;
		err = of_get_phy_mode(slave->node, &phy_mode);
		/* अगर phy-mode is not present, शेष to
		 * PHY_INTERFACE_MODE_RGMII
		 */
		अगर (err)
			phy_mode = PHY_INTERFACE_MODE_RGMII;

		अगर (!phy_पूर्णांकerface_mode_is_rgmii(phy_mode)) अणु
			dev_err(priv->dev,
				"Unsupported phy mode %d\n", phy_mode);
			वापस -EINVAL;
		पूर्ण
		slave->phy_port_t = PORT_MII;
	पूर्ण अन्यथा अगर (slave->link_पूर्णांकerface == XGMII_LINK_MAC_PHY) अणु
		has_phy = true;
		phy_mode = PHY_INTERFACE_MODE_NA;
		slave->phy_port_t = PORT_FIBRE;
	पूर्ण

	अगर (has_phy) अणु
		अगर (IS_SS_ID_XGBE(priv))
			hndlr = xgbe_adjust_link;

		slave->phy = of_phy_connect(gbe_पूर्णांकf->ndev,
					    slave->phy_node,
					    hndlr, 0,
					    phy_mode);
		अगर (!slave->phy) अणु
			dev_err(priv->dev, "phy not found on slave %d\n",
				slave->slave_num);
			वापस -ENODEV;
		पूर्ण
		dev_dbg(priv->dev, "phy found: id is: 0x%s\n",
			phydev_name(slave->phy));
		phy_start(slave->phy);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम gbe_init_host_port(काष्ठा gbe_priv *priv)
अणु
	पूर्णांक bypass_en = 1;

	/* Host Tx Pri */
	अगर (IS_SS_ID_NU(priv) || IS_SS_ID_XGBE(priv))
		ग_लिखोl(HOST_TX_PRI_MAP_DEFAULT,
		       GBE_REG_ADDR(priv, host_port_regs, tx_pri_map));

	/* Max length रेजिस्टर */
	ग_लिखोl(NETCP_MAX_FRAME_SIZE, GBE_REG_ADDR(priv, host_port_regs,
						  rx_maxlen));

	cpsw_ale_start(priv->ale);

	अगर (priv->enable_ale)
		bypass_en = 0;

	cpsw_ale_control_set(priv->ale, 0, ALE_BYPASS, bypass_en);

	cpsw_ale_control_set(priv->ale, 0, ALE_NO_PORT_VLAN, 1);

	cpsw_ale_control_set(priv->ale, priv->host_port,
			     ALE_PORT_STATE, ALE_PORT_STATE_FORWARD);

	cpsw_ale_control_set(priv->ale, 0,
			     ALE_PORT_UNKNOWN_VLAN_MEMBER,
			     GBE_PORT_MASK(priv->ale_ports));

	cpsw_ale_control_set(priv->ale, 0,
			     ALE_PORT_UNKNOWN_MCAST_FLOOD,
			     GBE_PORT_MASK(priv->ale_ports - 1));

	cpsw_ale_control_set(priv->ale, 0,
			     ALE_PORT_UNKNOWN_REG_MCAST_FLOOD,
			     GBE_PORT_MASK(priv->ale_ports));

	cpsw_ale_control_set(priv->ale, 0,
			     ALE_PORT_UNTAGGED_EGRESS,
			     GBE_PORT_MASK(priv->ale_ports));
पूर्ण

अटल व्योम gbe_add_mcast_addr(काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf, u8 *addr)
अणु
	काष्ठा gbe_priv *gbe_dev = gbe_पूर्णांकf->gbe_dev;
	u16 vlan_id;

	cpsw_ale_add_mcast(gbe_dev->ale, addr,
			   GBE_PORT_MASK(gbe_dev->ale_ports), 0, 0,
			   ALE_MCAST_FWD_2);
	क्रम_each_set_bit(vlan_id, gbe_पूर्णांकf->active_vlans, VLAN_N_VID) अणु
		cpsw_ale_add_mcast(gbe_dev->ale, addr,
				   GBE_PORT_MASK(gbe_dev->ale_ports),
				   ALE_VLAN, vlan_id, ALE_MCAST_FWD_2);
	पूर्ण
पूर्ण

अटल व्योम gbe_add_ucast_addr(काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf, u8 *addr)
अणु
	काष्ठा gbe_priv *gbe_dev = gbe_पूर्णांकf->gbe_dev;
	u16 vlan_id;

	cpsw_ale_add_ucast(gbe_dev->ale, addr, gbe_dev->host_port, 0, 0);

	क्रम_each_set_bit(vlan_id, gbe_पूर्णांकf->active_vlans, VLAN_N_VID)
		cpsw_ale_add_ucast(gbe_dev->ale, addr, gbe_dev->host_port,
				   ALE_VLAN, vlan_id);
पूर्ण

अटल व्योम gbe_del_mcast_addr(काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf, u8 *addr)
अणु
	काष्ठा gbe_priv *gbe_dev = gbe_पूर्णांकf->gbe_dev;
	u16 vlan_id;

	cpsw_ale_del_mcast(gbe_dev->ale, addr, 0, 0, 0);

	क्रम_each_set_bit(vlan_id, gbe_पूर्णांकf->active_vlans, VLAN_N_VID) अणु
		cpsw_ale_del_mcast(gbe_dev->ale, addr, 0, ALE_VLAN, vlan_id);
	पूर्ण
पूर्ण

अटल व्योम gbe_del_ucast_addr(काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf, u8 *addr)
अणु
	काष्ठा gbe_priv *gbe_dev = gbe_पूर्णांकf->gbe_dev;
	u16 vlan_id;

	cpsw_ale_del_ucast(gbe_dev->ale, addr, gbe_dev->host_port, 0, 0);

	क्रम_each_set_bit(vlan_id, gbe_पूर्णांकf->active_vlans, VLAN_N_VID) अणु
		cpsw_ale_del_ucast(gbe_dev->ale, addr, gbe_dev->host_port,
				   ALE_VLAN, vlan_id);
	पूर्ण
पूर्ण

अटल पूर्णांक gbe_add_addr(व्योम *पूर्णांकf_priv, काष्ठा netcp_addr *naddr)
अणु
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf = पूर्णांकf_priv;
	काष्ठा gbe_priv *gbe_dev = gbe_पूर्णांकf->gbe_dev;

	dev_dbg(gbe_dev->dev, "ethss adding address %pM, type %d\n",
		naddr->addr, naddr->type);

	चयन (naddr->type) अणु
	हाल ADDR_MCAST:
	हाल ADDR_BCAST:
		gbe_add_mcast_addr(gbe_पूर्णांकf, naddr->addr);
		अवरोध;
	हाल ADDR_UCAST:
	हाल ADDR_DEV:
		gbe_add_ucast_addr(gbe_पूर्णांकf, naddr->addr);
		अवरोध;
	हाल ADDR_ANY:
		/* nothing to करो क्रम promiscuous */
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gbe_del_addr(व्योम *पूर्णांकf_priv, काष्ठा netcp_addr *naddr)
अणु
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf = पूर्णांकf_priv;
	काष्ठा gbe_priv *gbe_dev = gbe_पूर्णांकf->gbe_dev;

	dev_dbg(gbe_dev->dev, "ethss deleting address %pM, type %d\n",
		naddr->addr, naddr->type);

	चयन (naddr->type) अणु
	हाल ADDR_MCAST:
	हाल ADDR_BCAST:
		gbe_del_mcast_addr(gbe_पूर्णांकf, naddr->addr);
		अवरोध;
	हाल ADDR_UCAST:
	हाल ADDR_DEV:
		gbe_del_ucast_addr(gbe_पूर्णांकf, naddr->addr);
		अवरोध;
	हाल ADDR_ANY:
		/* nothing to करो क्रम promiscuous */
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gbe_add_vid(व्योम *पूर्णांकf_priv, पूर्णांक vid)
अणु
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf = पूर्णांकf_priv;
	काष्ठा gbe_priv *gbe_dev = gbe_पूर्णांकf->gbe_dev;

	set_bit(vid, gbe_पूर्णांकf->active_vlans);

	cpsw_ale_add_vlan(gbe_dev->ale, vid,
			  GBE_PORT_MASK(gbe_dev->ale_ports),
			  GBE_MASK_NO_PORTS,
			  GBE_PORT_MASK(gbe_dev->ale_ports),
			  GBE_PORT_MASK(gbe_dev->ale_ports - 1));

	वापस 0;
पूर्ण

अटल पूर्णांक gbe_del_vid(व्योम *पूर्णांकf_priv, पूर्णांक vid)
अणु
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf = पूर्णांकf_priv;
	काष्ठा gbe_priv *gbe_dev = gbe_पूर्णांकf->gbe_dev;

	cpsw_ale_del_vlan(gbe_dev->ale, vid, 0);
	clear_bit(vid, gbe_पूर्णांकf->active_vlans);
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_TI_CPTS)

अटल व्योम gbe_txtstamp(व्योम *context, काष्ठा sk_buff *skb)
अणु
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf = context;
	काष्ठा gbe_priv *gbe_dev = gbe_पूर्णांकf->gbe_dev;

	cpts_tx_बारtamp(gbe_dev->cpts, skb);
पूर्ण

अटल bool gbe_need_txtstamp(काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf,
			      स्थिर काष्ठा netcp_packet *p_info)
अणु
	काष्ठा sk_buff *skb = p_info->skb;

	वापस cpts_can_बारtamp(gbe_पूर्णांकf->gbe_dev->cpts, skb);
पूर्ण

अटल पूर्णांक gbe_txtstamp_mark_pkt(काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf,
				 काष्ठा netcp_packet *p_info)
अणु
	काष्ठा phy_device *phydev = p_info->skb->dev->phydev;
	काष्ठा gbe_priv *gbe_dev = gbe_पूर्णांकf->gbe_dev;

	अगर (!(skb_shinfo(p_info->skb)->tx_flags & SKBTX_HW_TSTAMP) ||
	    !gbe_dev->tx_ts_enabled)
		वापस 0;

	/* If phy has the txtstamp api, assume it will करो it.
	 * We mark it here because skb_tx_बारtamp() is called
	 * after all the txhooks are called.
	 */
	अगर (phy_has_txtstamp(phydev)) अणु
		skb_shinfo(p_info->skb)->tx_flags |= SKBTX_IN_PROGRESS;
		वापस 0;
	पूर्ण

	अगर (gbe_need_txtstamp(gbe_पूर्णांकf, p_info)) अणु
		p_info->txtstamp = gbe_txtstamp;
		p_info->ts_context = (व्योम *)gbe_पूर्णांकf;
		skb_shinfo(p_info->skb)->tx_flags |= SKBTX_IN_PROGRESS;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gbe_rxtstamp(काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf, काष्ठा netcp_packet *p_info)
अणु
	काष्ठा phy_device *phydev = p_info->skb->dev->phydev;
	काष्ठा gbe_priv *gbe_dev = gbe_पूर्णांकf->gbe_dev;

	अगर (p_info->rxtstamp_complete)
		वापस 0;

	अगर (phy_has_rxtstamp(phydev)) अणु
		p_info->rxtstamp_complete = true;
		वापस 0;
	पूर्ण

	अगर (gbe_dev->rx_ts_enabled)
		cpts_rx_बारtamp(gbe_dev->cpts, p_info->skb);

	p_info->rxtstamp_complete = true;

	वापस 0;
पूर्ण

अटल पूर्णांक gbe_hwtstamp_get(काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा gbe_priv *gbe_dev = gbe_पूर्णांकf->gbe_dev;
	काष्ठा cpts *cpts = gbe_dev->cpts;
	काष्ठा hwtstamp_config cfg;

	अगर (!cpts)
		वापस -EOPNOTSUPP;

	cfg.flags = 0;
	cfg.tx_type = gbe_dev->tx_ts_enabled ? HWTSTAMP_TX_ON : HWTSTAMP_TX_OFF;
	cfg.rx_filter = gbe_dev->rx_ts_enabled;

	वापस copy_to_user(अगरr->अगरr_data, &cfg, माप(cfg)) ? -EFAULT : 0;
पूर्ण

अटल व्योम gbe_hwtstamp(काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf)
अणु
	काष्ठा gbe_priv *gbe_dev = gbe_पूर्णांकf->gbe_dev;
	काष्ठा gbe_slave *slave = gbe_पूर्णांकf->slave;
	u32 ts_en, seq_id, ctl;

	अगर (!gbe_dev->rx_ts_enabled &&
	    !gbe_dev->tx_ts_enabled) अणु
		ग_लिखोl(0, GBE_REG_ADDR(slave, port_regs, ts_ctl));
		वापस;
	पूर्ण

	seq_id = (30 << TS_SEQ_ID_OFS_SHIFT) | ETH_P_1588;
	ts_en = EVENT_MSG_BITS << TS_MSG_TYPE_EN_SHIFT;
	ctl = ETH_P_1588 | TS_TTL_NONZERO |
		(slave->ts_ctl.dst_port_map << TS_CTL_DST_PORT_SHIFT) |
		(slave->ts_ctl.uni ?  TS_UNI_EN :
			slave->ts_ctl.maddr_map << TS_CTL_MADDR_SHIFT);

	अगर (gbe_dev->tx_ts_enabled)
		ts_en |= (TS_TX_ANX_ALL_EN | TS_TX_VLAN_LT1_EN);

	अगर (gbe_dev->rx_ts_enabled)
		ts_en |= (TS_RX_ANX_ALL_EN | TS_RX_VLAN_LT1_EN);

	ग_लिखोl(ts_en,  GBE_REG_ADDR(slave, port_regs, ts_ctl));
	ग_लिखोl(seq_id, GBE_REG_ADDR(slave, port_regs, ts_seq_ltype));
	ग_लिखोl(ctl,    GBE_REG_ADDR(slave, port_regs, ts_ctl_ltype2));
पूर्ण

अटल पूर्णांक gbe_hwtstamp_set(काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा gbe_priv *gbe_dev = gbe_पूर्णांकf->gbe_dev;
	काष्ठा cpts *cpts = gbe_dev->cpts;
	काष्ठा hwtstamp_config cfg;

	अगर (!cpts)
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&cfg, अगरr->अगरr_data, माप(cfg)))
		वापस -EFAULT;

	/* reserved क्रम future extensions */
	अगर (cfg.flags)
		वापस -EINVAL;

	चयन (cfg.tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		gbe_dev->tx_ts_enabled = 0;
		अवरोध;
	हाल HWTSTAMP_TX_ON:
		gbe_dev->tx_ts_enabled = 1;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (cfg.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		gbe_dev->rx_ts_enabled = HWTSTAMP_FILTER_NONE;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		gbe_dev->rx_ts_enabled = HWTSTAMP_FILTER_PTP_V1_L4_EVENT;
		cfg.rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_EVENT;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		gbe_dev->rx_ts_enabled = HWTSTAMP_FILTER_PTP_V2_EVENT;
		cfg.rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	gbe_hwtstamp(gbe_पूर्णांकf);

	वापस copy_to_user(अगरr->अगरr_data, &cfg, माप(cfg)) ? -EFAULT : 0;
पूर्ण

अटल व्योम gbe_रेजिस्टर_cpts(काष्ठा gbe_priv *gbe_dev)
अणु
	अगर (!gbe_dev->cpts)
		वापस;

	अगर (gbe_dev->cpts_रेजिस्टरed > 0)
		जाओ करोne;

	अगर (cpts_रेजिस्टर(gbe_dev->cpts)) अणु
		dev_err(gbe_dev->dev, "error registering cpts device\n");
		वापस;
	पूर्ण

करोne:
	++gbe_dev->cpts_रेजिस्टरed;
पूर्ण

अटल व्योम gbe_unरेजिस्टर_cpts(काष्ठा gbe_priv *gbe_dev)
अणु
	अगर (!gbe_dev->cpts || (gbe_dev->cpts_रेजिस्टरed <= 0))
		वापस;

	अगर (--gbe_dev->cpts_रेजिस्टरed)
		वापस;

	cpts_unरेजिस्टर(gbe_dev->cpts);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक gbe_txtstamp_mark_pkt(काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf,
					काष्ठा netcp_packet *p_info)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक gbe_rxtstamp(काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf,
			       काष्ठा netcp_packet *p_info)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक gbe_hwtstamp(काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf,
			       काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम gbe_रेजिस्टर_cpts(काष्ठा gbe_priv *gbe_dev)
अणु
पूर्ण

अटल अंतरभूत व्योम gbe_unरेजिस्टर_cpts(काष्ठा gbe_priv *gbe_dev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक gbe_hwtstamp_get(काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf, काष्ठा अगरreq *req)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक gbe_hwtstamp_set(काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf, काष्ठा अगरreq *req)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर /* CONFIG_TI_CPTS */

अटल पूर्णांक gbe_set_rx_mode(व्योम *पूर्णांकf_priv, bool promisc)
अणु
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf = पूर्णांकf_priv;
	काष्ठा gbe_priv *gbe_dev = gbe_पूर्णांकf->gbe_dev;
	काष्ठा cpsw_ale *ale = gbe_dev->ale;
	अचिन्हित दीर्घ समयout;
	पूर्णांक i, ret = -ETIMEDOUT;

	/* Disable(1)/Enable(0) Learn क्रम all ports (host is port 0 and
	 * slaves are port 1 and up
	 */
	क्रम (i = 0; i <= gbe_dev->num_slaves; i++) अणु
		cpsw_ale_control_set(ale, i,
				     ALE_PORT_NOLEARN, !!promisc);
		cpsw_ale_control_set(ale, i,
				     ALE_PORT_NO_SA_UPDATE, !!promisc);
	पूर्ण

	अगर (!promisc) अणु
		/* Don't Flood All Unicast Packets to Host port */
		cpsw_ale_control_set(ale, 0, ALE_P0_UNI_FLOOD, 0);
		dev_vdbg(gbe_dev->dev, "promiscuous mode disabled\n");
		वापस 0;
	पूर्ण

	समयout = jअगरfies + HZ;

	/* Clear All Untouched entries */
	cpsw_ale_control_set(ale, 0, ALE_AGEOUT, 1);
	करो अणु
		cpu_relax();
		अगर (cpsw_ale_control_get(ale, 0, ALE_AGEOUT)) अणु
			ret = 0;
			अवरोध;
		पूर्ण

	पूर्ण जबतक (समय_after(समयout, jअगरfies));

	/* Make sure it is not a false समयout */
	अगर (ret && !cpsw_ale_control_get(ale, 0, ALE_AGEOUT))
		वापस ret;

	cpsw_ale_control_set(ale, 0, ALE_AGEOUT, 1);

	/* Clear all mcast from ALE */
	cpsw_ale_flush_multicast(ale,
				 GBE_PORT_MASK(gbe_dev->ale_ports),
				 -1);

	/* Flood All Unicast Packets to Host port */
	cpsw_ale_control_set(ale, 0, ALE_P0_UNI_FLOOD, 1);
	dev_vdbg(gbe_dev->dev, "promiscuous mode enabled\n");
	वापस ret;
पूर्ण

अटल पूर्णांक gbe_ioctl(व्योम *पूर्णांकf_priv, काष्ठा अगरreq *req, पूर्णांक cmd)
अणु
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf = पूर्णांकf_priv;
	काष्ठा phy_device *phy = gbe_पूर्णांकf->slave->phy;

	अगर (!phy_has_hwtstamp(phy)) अणु
		चयन (cmd) अणु
		हाल SIOCGHWTSTAMP:
			वापस gbe_hwtstamp_get(gbe_पूर्णांकf, req);
		हाल SIOCSHWTSTAMP:
			वापस gbe_hwtstamp_set(gbe_पूर्णांकf, req);
		पूर्ण
	पूर्ण

	अगर (phy)
		वापस phy_mii_ioctl(phy, req, cmd);

	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम netcp_ethss_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा gbe_priv *gbe_dev = from_समयr(gbe_dev, t, समयr);
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf;
	काष्ठा gbe_slave *slave;

	/* Check & update SGMII link state of पूर्णांकerfaces */
	क्रम_each_पूर्णांकf(gbe_पूर्णांकf, gbe_dev) अणु
		अगर (!gbe_पूर्णांकf->slave->खोलो)
			जारी;
		netcp_ethss_update_link_state(gbe_dev, gbe_पूर्णांकf->slave,
					      gbe_पूर्णांकf->ndev);
	पूर्ण

	/* Check & update SGMII link state of secondary ports */
	क्रम_each_sec_slave(slave, gbe_dev) अणु
		netcp_ethss_update_link_state(gbe_dev, slave, शून्य);
	पूर्ण

	/* A समयr runs as a BH, no need to block them */
	spin_lock(&gbe_dev->hw_stats_lock);

	अगर (IS_SS_ID_VER_14(gbe_dev))
		gbe_update_stats_ver14(gbe_dev, शून्य);
	अन्यथा
		gbe_update_stats(gbe_dev, शून्य);

	spin_unlock(&gbe_dev->hw_stats_lock);

	gbe_dev->समयr.expires	= jअगरfies + GBE_TIMER_INTERVAL;
	add_समयr(&gbe_dev->समयr);
पूर्ण

अटल पूर्णांक gbe_txhook(पूर्णांक order, व्योम *data, काष्ठा netcp_packet *p_info)
अणु
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf = data;

	p_info->tx_pipe = &gbe_पूर्णांकf->tx_pipe;

	वापस gbe_txtstamp_mark_pkt(gbe_पूर्णांकf, p_info);
पूर्ण

अटल पूर्णांक gbe_rxhook(पूर्णांक order, व्योम *data, काष्ठा netcp_packet *p_info)
अणु
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf = data;

	वापस gbe_rxtstamp(gbe_पूर्णांकf, p_info);
पूर्ण

अटल पूर्णांक gbe_खोलो(व्योम *पूर्णांकf_priv, काष्ठा net_device *ndev)
अणु
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf = पूर्णांकf_priv;
	काष्ठा gbe_priv *gbe_dev = gbe_पूर्णांकf->gbe_dev;
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	काष्ठा gbe_slave *slave = gbe_पूर्णांकf->slave;
	पूर्णांक port_num = slave->port_num;
	u32 reg, val;
	पूर्णांक ret;

	reg = पढ़ोl(GBE_REG_ADDR(gbe_dev, चयन_regs, id_ver));
	dev_dbg(gbe_dev->dev, "initializing gbe version %d.%d (%d) GBE identification value 0x%x\n",
		GBE_MAJOR_VERSION(reg), GBE_MINOR_VERSION(reg),
		GBE_RTL_VERSION(reg), GBE_IDENT(reg));

	/* For 10G and on NetCP 1.5, use directed to port */
	अगर (IS_SS_ID_XGBE(gbe_dev) || IS_SS_ID_MU(gbe_dev))
		gbe_पूर्णांकf->tx_pipe.flags = SWITCH_TO_PORT_IN_TAGINFO;

	अगर (gbe_dev->enable_ale)
		gbe_पूर्णांकf->tx_pipe.चयन_to_port = 0;
	अन्यथा
		gbe_पूर्णांकf->tx_pipe.चयन_to_port = port_num;

	dev_dbg(gbe_dev->dev,
		"opened TX channel %s: %p with to port %d, flags %d\n",
		gbe_पूर्णांकf->tx_pipe.dma_chan_name,
		gbe_पूर्णांकf->tx_pipe.dma_channel,
		gbe_पूर्णांकf->tx_pipe.चयन_to_port,
		gbe_पूर्णांकf->tx_pipe.flags);

	gbe_slave_stop(gbe_पूर्णांकf);

	/* disable priority elevation and enable statistics on all ports */
	ग_लिखोl(0, GBE_REG_ADDR(gbe_dev, चयन_regs, ptype));

	/* Control रेजिस्टर */
	val = GBE_CTL_P0_ENABLE;
	अगर (IS_SS_ID_MU(gbe_dev)) अणु
		val |= ETH_SW_CTL_P0_TX_CRC_REMOVE;
		netcp->hw_cap = ETH_SW_CAN_REMOVE_ETH_FCS;
	पूर्ण
	ग_लिखोl(val, GBE_REG_ADDR(gbe_dev, चयन_regs, control));

	/* All statistics enabled and STAT AB visible by शेष */
	ग_लिखोl(gbe_dev->stats_en_mask, GBE_REG_ADDR(gbe_dev, चयन_regs,
						    stat_port_en));

	ret = gbe_slave_खोलो(gbe_पूर्णांकf);
	अगर (ret)
		जाओ fail;

	netcp_रेजिस्टर_txhook(netcp, GBE_TXHOOK_ORDER, gbe_txhook, gbe_पूर्णांकf);
	netcp_रेजिस्टर_rxhook(netcp, GBE_RXHOOK_ORDER, gbe_rxhook, gbe_पूर्णांकf);

	slave->खोलो = true;
	netcp_ethss_update_link_state(gbe_dev, slave, ndev);

	gbe_रेजिस्टर_cpts(gbe_dev);

	वापस 0;

fail:
	gbe_slave_stop(gbe_पूर्णांकf);
	वापस ret;
पूर्ण

अटल पूर्णांक gbe_बंद(व्योम *पूर्णांकf_priv, काष्ठा net_device *ndev)
अणु
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf = पूर्णांकf_priv;
	काष्ठा netcp_पूर्णांकf *netcp = netdev_priv(ndev);
	काष्ठा gbe_priv *gbe_dev = gbe_पूर्णांकf->gbe_dev;

	gbe_unरेजिस्टर_cpts(gbe_dev);

	gbe_slave_stop(gbe_पूर्णांकf);

	netcp_unरेजिस्टर_rxhook(netcp, GBE_RXHOOK_ORDER, gbe_rxhook, gbe_पूर्णांकf);
	netcp_unरेजिस्टर_txhook(netcp, GBE_TXHOOK_ORDER, gbe_txhook, gbe_पूर्णांकf);

	gbe_पूर्णांकf->slave->खोलो = false;
	atomic_set(&gbe_पूर्णांकf->slave->link_state, NETCP_LINK_STATE_INVALID);
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_TI_CPTS)
अटल व्योम init_slave_ts_ctl(काष्ठा gbe_slave *slave)
अणु
	slave->ts_ctl.uni = 1;
	slave->ts_ctl.dst_port_map =
		(TS_CTL_DST_PORT >> TS_CTL_DST_PORT_SHIFT) & 0x3;
	slave->ts_ctl.maddr_map =
		(TS_CTL_MADDR_ALL >> TS_CTL_MADDR_SHIFT) & 0x1f;
पूर्ण

#अन्यथा
अटल व्योम init_slave_ts_ctl(काष्ठा gbe_slave *slave)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_TI_CPTS */

अटल पूर्णांक init_slave(काष्ठा gbe_priv *gbe_dev, काष्ठा gbe_slave *slave,
		      काष्ठा device_node *node)
अणु
	पूर्णांक port_reg_num;
	u32 port_reg_ofs, emac_reg_ofs;
	u32 port_reg_blk_sz, emac_reg_blk_sz;

	अगर (of_property_पढ़ो_u32(node, "slave-port", &slave->slave_num)) अणु
		dev_err(gbe_dev->dev, "missing slave-port parameter\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "link-interface",
				 &slave->link_पूर्णांकerface)) अणु
		dev_warn(gbe_dev->dev,
			 "missing link-interface value defaulting to 1G mac-phy link\n");
		slave->link_पूर्णांकerface = SGMII_LINK_MAC_PHY;
	पूर्ण

	slave->node = node;
	slave->खोलो = false;
	अगर ((slave->link_पूर्णांकerface == SGMII_LINK_MAC_PHY) ||
	    (slave->link_पूर्णांकerface == RGMII_LINK_MAC_PHY) ||
	    (slave->link_पूर्णांकerface == XGMII_LINK_MAC_PHY))
		slave->phy_node = of_parse_phandle(node, "phy-handle", 0);
	slave->port_num = gbe_get_slave_port(gbe_dev, slave->slave_num);

	अगर (slave->link_पूर्णांकerface >= XGMII_LINK_MAC_PHY)
		slave->mac_control = GBE_DEF_10G_MAC_CONTROL;
	अन्यथा
		slave->mac_control = GBE_DEF_1G_MAC_CONTROL;

	/* Emac regs memmap are contiguous but port regs are not */
	port_reg_num = slave->slave_num;
	अगर (IS_SS_ID_VER_14(gbe_dev)) अणु
		अगर (slave->slave_num > 1) अणु
			port_reg_ofs = GBE13_SLAVE_PORT2_OFFSET;
			port_reg_num -= 2;
		पूर्ण अन्यथा अणु
			port_reg_ofs = GBE13_SLAVE_PORT_OFFSET;
		पूर्ण
		emac_reg_ofs = GBE13_EMAC_OFFSET;
		port_reg_blk_sz = 0x30;
		emac_reg_blk_sz = 0x40;
	पूर्ण अन्यथा अगर (IS_SS_ID_MU(gbe_dev)) अणु
		port_reg_ofs = GBENU_SLAVE_PORT_OFFSET;
		emac_reg_ofs = GBENU_EMAC_OFFSET;
		port_reg_blk_sz = 0x1000;
		emac_reg_blk_sz = 0x1000;
	पूर्ण अन्यथा अगर (IS_SS_ID_XGBE(gbe_dev)) अणु
		port_reg_ofs = XGBE10_SLAVE_PORT_OFFSET;
		emac_reg_ofs = XGBE10_EMAC_OFFSET;
		port_reg_blk_sz = 0x30;
		emac_reg_blk_sz = 0x40;
	पूर्ण अन्यथा अणु
		dev_err(gbe_dev->dev, "unknown ethss(0x%x)\n",
			gbe_dev->ss_version);
		वापस -EINVAL;
	पूर्ण

	slave->port_regs = gbe_dev->चयन_regs + port_reg_ofs +
				(port_reg_blk_sz * port_reg_num);
	slave->emac_regs = gbe_dev->चयन_regs + emac_reg_ofs +
				(emac_reg_blk_sz * slave->slave_num);

	अगर (IS_SS_ID_VER_14(gbe_dev)) अणु
		/* Initialize  slave port रेजिस्टर offsets */
		GBE_SET_REG_OFS(slave, port_regs, port_vlan);
		GBE_SET_REG_OFS(slave, port_regs, tx_pri_map);
		GBE_SET_REG_OFS(slave, port_regs, sa_lo);
		GBE_SET_REG_OFS(slave, port_regs, sa_hi);
		GBE_SET_REG_OFS(slave, port_regs, ts_ctl);
		GBE_SET_REG_OFS(slave, port_regs, ts_seq_ltype);
		GBE_SET_REG_OFS(slave, port_regs, ts_vlan);
		GBE_SET_REG_OFS(slave, port_regs, ts_ctl_ltype2);
		GBE_SET_REG_OFS(slave, port_regs, ts_ctl2);

		/* Initialize EMAC रेजिस्टर offsets */
		GBE_SET_REG_OFS(slave, emac_regs, mac_control);
		GBE_SET_REG_OFS(slave, emac_regs, soft_reset);
		GBE_SET_REG_OFS(slave, emac_regs, rx_maxlen);

	पूर्ण अन्यथा अगर (IS_SS_ID_MU(gbe_dev)) अणु
		/* Initialize  slave port रेजिस्टर offsets */
		GBENU_SET_REG_OFS(slave, port_regs, port_vlan);
		GBENU_SET_REG_OFS(slave, port_regs, tx_pri_map);
		GBENU_SET_REG_OFS(slave, port_regs, rx_pri_map);
		GBENU_SET_REG_OFS(slave, port_regs, sa_lo);
		GBENU_SET_REG_OFS(slave, port_regs, sa_hi);
		GBENU_SET_REG_OFS(slave, port_regs, ts_ctl);
		GBENU_SET_REG_OFS(slave, port_regs, ts_seq_ltype);
		GBENU_SET_REG_OFS(slave, port_regs, ts_vlan);
		GBENU_SET_REG_OFS(slave, port_regs, ts_ctl_ltype2);
		GBENU_SET_REG_OFS(slave, port_regs, ts_ctl2);
		GBENU_SET_REG_OFS(slave, port_regs, rx_maxlen);

		/* Initialize EMAC रेजिस्टर offsets */
		GBENU_SET_REG_OFS(slave, emac_regs, mac_control);
		GBENU_SET_REG_OFS(slave, emac_regs, soft_reset);

	पूर्ण अन्यथा अगर (IS_SS_ID_XGBE(gbe_dev)) अणु
		/* Initialize  slave port रेजिस्टर offsets */
		XGBE_SET_REG_OFS(slave, port_regs, port_vlan);
		XGBE_SET_REG_OFS(slave, port_regs, tx_pri_map);
		XGBE_SET_REG_OFS(slave, port_regs, sa_lo);
		XGBE_SET_REG_OFS(slave, port_regs, sa_hi);
		XGBE_SET_REG_OFS(slave, port_regs, ts_ctl);
		XGBE_SET_REG_OFS(slave, port_regs, ts_seq_ltype);
		XGBE_SET_REG_OFS(slave, port_regs, ts_vlan);
		XGBE_SET_REG_OFS(slave, port_regs, ts_ctl_ltype2);
		XGBE_SET_REG_OFS(slave, port_regs, ts_ctl2);

		/* Initialize EMAC रेजिस्टर offsets */
		XGBE_SET_REG_OFS(slave, emac_regs, mac_control);
		XGBE_SET_REG_OFS(slave, emac_regs, soft_reset);
		XGBE_SET_REG_OFS(slave, emac_regs, rx_maxlen);
	पूर्ण

	atomic_set(&slave->link_state, NETCP_LINK_STATE_INVALID);

	init_slave_ts_ctl(slave);
	वापस 0;
पूर्ण

अटल व्योम init_secondary_ports(काष्ठा gbe_priv *gbe_dev,
				 काष्ठा device_node *node)
अणु
	काष्ठा device *dev = gbe_dev->dev;
	phy_पूर्णांकerface_t phy_mode;
	काष्ठा gbe_priv **priv;
	काष्ठा device_node *port;
	काष्ठा gbe_slave *slave;
	bool mac_phy_link = false;

	क्रम_each_child_of_node(node, port) अणु
		slave = devm_kzalloc(dev, माप(*slave), GFP_KERNEL);
		अगर (!slave) अणु
			dev_err(dev, "memory alloc failed for secondary port(%pOFn), skipping...\n",
				port);
			जारी;
		पूर्ण

		अगर (init_slave(gbe_dev, slave, port)) अणु
			dev_err(dev,
				"Failed to initialize secondary port(%pOFn), skipping...\n",
				port);
			devm_kमुक्त(dev, slave);
			जारी;
		पूर्ण

		अगर (!IS_SS_ID_2U(gbe_dev))
			gbe_sgmii_config(gbe_dev, slave);
		gbe_port_reset(slave);
		gbe_port_config(gbe_dev, slave, gbe_dev->rx_packet_max);
		list_add_tail(&slave->slave_list, &gbe_dev->secondary_slaves);
		gbe_dev->num_slaves++;
		अगर ((slave->link_पूर्णांकerface == SGMII_LINK_MAC_PHY) ||
		    (slave->link_पूर्णांकerface == XGMII_LINK_MAC_PHY))
			mac_phy_link = true;

		slave->खोलो = true;
		अगर (gbe_dev->num_slaves >= gbe_dev->max_num_slaves) अणु
			of_node_put(port);
			अवरोध;
		पूर्ण
	पूर्ण

	/* of_phy_connect() is needed only क्रम MAC-PHY पूर्णांकerface */
	अगर (!mac_phy_link)
		वापस;

	/* Allocate dummy netdev device क्रम attaching to phy device */
	gbe_dev->dummy_ndev = alloc_netdev(माप(gbe_dev), "dummy",
					NET_NAME_UNKNOWN, ether_setup);
	अगर (!gbe_dev->dummy_ndev) अणु
		dev_err(dev,
			"Failed to allocate dummy netdev for secondary ports, skipping phy_connect()...\n");
		वापस;
	पूर्ण
	priv = netdev_priv(gbe_dev->dummy_ndev);
	*priv = gbe_dev;

	अगर (slave->link_पूर्णांकerface == SGMII_LINK_MAC_PHY) अणु
		phy_mode = PHY_INTERFACE_MODE_SGMII;
		slave->phy_port_t = PORT_MII;
	पूर्ण अन्यथा अगर (slave->link_पूर्णांकerface == RGMII_LINK_MAC_PHY) अणु
		phy_mode = PHY_INTERFACE_MODE_RGMII;
		slave->phy_port_t = PORT_MII;
	पूर्ण अन्यथा अणु
		phy_mode = PHY_INTERFACE_MODE_NA;
		slave->phy_port_t = PORT_FIBRE;
	पूर्ण

	क्रम_each_sec_slave(slave, gbe_dev) अणु
		अगर ((slave->link_पूर्णांकerface != SGMII_LINK_MAC_PHY) &&
		    (slave->link_पूर्णांकerface != RGMII_LINK_MAC_PHY) &&
		    (slave->link_पूर्णांकerface != XGMII_LINK_MAC_PHY))
			जारी;
		slave->phy =
			of_phy_connect(gbe_dev->dummy_ndev,
				       slave->phy_node,
				       gbe_adjust_link_sec_slaves,
				       0, phy_mode);
		अगर (!slave->phy) अणु
			dev_err(dev, "phy not found for slave %d\n",
				slave->slave_num);
		पूर्ण अन्यथा अणु
			dev_dbg(dev, "phy found: id is: 0x%s\n",
				phydev_name(slave->phy));
			phy_start(slave->phy);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम मुक्त_secondary_ports(काष्ठा gbe_priv *gbe_dev)
अणु
	काष्ठा gbe_slave *slave;

	जबतक (!list_empty(&gbe_dev->secondary_slaves)) अणु
		slave = first_sec_slave(gbe_dev);

		अगर (slave->phy)
			phy_disconnect(slave->phy);
		list_del(&slave->slave_list);
	पूर्ण
	अगर (gbe_dev->dummy_ndev)
		मुक्त_netdev(gbe_dev->dummy_ndev);
पूर्ण

अटल पूर्णांक set_xgbe_ethss10_priv(काष्ठा gbe_priv *gbe_dev,
				 काष्ठा device_node *node)
अणु
	काष्ठा resource res;
	व्योम __iomem *regs;
	पूर्णांक ret, i;

	ret = of_address_to_resource(node, XGBE_SS_REG_INDEX, &res);
	अगर (ret) अणु
		dev_err(gbe_dev->dev,
			"Can't xlate xgbe of node(%pOFn) ss address at %d\n",
			node, XGBE_SS_REG_INDEX);
		वापस ret;
	पूर्ण

	regs = devm_ioremap_resource(gbe_dev->dev, &res);
	अगर (IS_ERR(regs)) अणु
		dev_err(gbe_dev->dev, "Failed to map xgbe ss register base\n");
		वापस PTR_ERR(regs);
	पूर्ण
	gbe_dev->ss_regs = regs;

	ret = of_address_to_resource(node, XGBE_SM_REG_INDEX, &res);
	अगर (ret) अणु
		dev_err(gbe_dev->dev,
			"Can't xlate xgbe of node(%pOFn) sm address at %d\n",
			node, XGBE_SM_REG_INDEX);
		वापस ret;
	पूर्ण

	regs = devm_ioremap_resource(gbe_dev->dev, &res);
	अगर (IS_ERR(regs)) अणु
		dev_err(gbe_dev->dev, "Failed to map xgbe sm register base\n");
		वापस PTR_ERR(regs);
	पूर्ण
	gbe_dev->चयन_regs = regs;

	ret = of_address_to_resource(node, XGBE_SERDES_REG_INDEX, &res);
	अगर (ret) अणु
		dev_err(gbe_dev->dev,
			"Can't xlate xgbe serdes of node(%pOFn) address at %d\n",
			node, XGBE_SERDES_REG_INDEX);
		वापस ret;
	पूर्ण

	regs = devm_ioremap_resource(gbe_dev->dev, &res);
	अगर (IS_ERR(regs)) अणु
		dev_err(gbe_dev->dev, "Failed to map xgbe serdes register base\n");
		वापस PTR_ERR(regs);
	पूर्ण
	gbe_dev->xgbe_serdes_regs = regs;

	gbe_dev->num_stats_mods = gbe_dev->max_num_ports;
	gbe_dev->et_stats = xgbe10_et_stats;
	gbe_dev->num_et_stats = ARRAY_SIZE(xgbe10_et_stats);

	gbe_dev->hw_stats = devm_kसुस्मृति(gbe_dev->dev,
					 gbe_dev->num_et_stats, माप(u64),
					 GFP_KERNEL);
	अगर (!gbe_dev->hw_stats) अणु
		dev_err(gbe_dev->dev, "hw_stats memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	gbe_dev->hw_stats_prev =
		devm_kसुस्मृति(gbe_dev->dev,
			     gbe_dev->num_et_stats, माप(u32),
			     GFP_KERNEL);
	अगर (!gbe_dev->hw_stats_prev) अणु
		dev_err(gbe_dev->dev,
			"hw_stats_prev memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	gbe_dev->ss_version = XGBE_SS_VERSION_10;
	gbe_dev->sgmii_port_regs = gbe_dev->ss_regs +
					XGBE10_SGMII_MODULE_OFFSET;
	gbe_dev->host_port_regs = gbe_dev->ss_regs + XGBE10_HOST_PORT_OFFSET;

	क्रम (i = 0; i < gbe_dev->max_num_ports; i++)
		gbe_dev->hw_stats_regs[i] = gbe_dev->चयन_regs +
			XGBE10_HW_STATS_OFFSET + (GBE_HW_STATS_REG_MAP_SZ * i);

	gbe_dev->ale_reg = gbe_dev->चयन_regs + XGBE10_ALE_OFFSET;
	gbe_dev->cpts_reg = gbe_dev->चयन_regs + XGBE10_CPTS_OFFSET;
	gbe_dev->ale_ports = gbe_dev->max_num_ports;
	gbe_dev->host_port = XGBE10_HOST_PORT_NUM;
	gbe_dev->stats_en_mask = (1 << (gbe_dev->max_num_ports)) - 1;

	/* Subप्रणाली रेजिस्टरs */
	XGBE_SET_REG_OFS(gbe_dev, ss_regs, id_ver);
	XGBE_SET_REG_OFS(gbe_dev, ss_regs, control);

	/* Switch module रेजिस्टरs */
	XGBE_SET_REG_OFS(gbe_dev, चयन_regs, id_ver);
	XGBE_SET_REG_OFS(gbe_dev, चयन_regs, control);
	XGBE_SET_REG_OFS(gbe_dev, चयन_regs, ptype);
	XGBE_SET_REG_OFS(gbe_dev, चयन_regs, stat_port_en);
	XGBE_SET_REG_OFS(gbe_dev, चयन_regs, flow_control);

	/* Host port रेजिस्टरs */
	XGBE_SET_REG_OFS(gbe_dev, host_port_regs, port_vlan);
	XGBE_SET_REG_OFS(gbe_dev, host_port_regs, tx_pri_map);
	XGBE_SET_REG_OFS(gbe_dev, host_port_regs, rx_maxlen);
	वापस 0;
पूर्ण

अटल पूर्णांक get_gbe_resource_version(काष्ठा gbe_priv *gbe_dev,
				    काष्ठा device_node *node)
अणु
	काष्ठा resource res;
	व्योम __iomem *regs;
	पूर्णांक ret;

	ret = of_address_to_resource(node, GBE_SS_REG_INDEX, &res);
	अगर (ret) अणु
		dev_err(gbe_dev->dev,
			"Can't translate of node(%pOFn) of gbe ss address at %d\n",
			node, GBE_SS_REG_INDEX);
		वापस ret;
	पूर्ण

	regs = devm_ioremap_resource(gbe_dev->dev, &res);
	अगर (IS_ERR(regs)) अणु
		dev_err(gbe_dev->dev, "Failed to map gbe register base\n");
		वापस PTR_ERR(regs);
	पूर्ण
	gbe_dev->ss_regs = regs;
	gbe_dev->ss_version = पढ़ोl(gbe_dev->ss_regs);
	वापस 0;
पूर्ण

अटल पूर्णांक set_gbe_ethss14_priv(काष्ठा gbe_priv *gbe_dev,
				काष्ठा device_node *node)
अणु
	काष्ठा resource res;
	व्योम __iomem *regs;
	पूर्णांक i, ret;

	ret = of_address_to_resource(node, GBE_SGMII34_REG_INDEX, &res);
	अगर (ret) अणु
		dev_err(gbe_dev->dev,
			"Can't translate of gbe node(%pOFn) address at index %d\n",
			node, GBE_SGMII34_REG_INDEX);
		वापस ret;
	पूर्ण

	regs = devm_ioremap_resource(gbe_dev->dev, &res);
	अगर (IS_ERR(regs)) अणु
		dev_err(gbe_dev->dev,
			"Failed to map gbe sgmii port34 register base\n");
		वापस PTR_ERR(regs);
	पूर्ण
	gbe_dev->sgmii_port34_regs = regs;

	ret = of_address_to_resource(node, GBE_SM_REG_INDEX, &res);
	अगर (ret) अणु
		dev_err(gbe_dev->dev,
			"Can't translate of gbe node(%pOFn) address at index %d\n",
			node, GBE_SM_REG_INDEX);
		वापस ret;
	पूर्ण

	regs = devm_ioremap_resource(gbe_dev->dev, &res);
	अगर (IS_ERR(regs)) अणु
		dev_err(gbe_dev->dev,
			"Failed to map gbe switch module register base\n");
		वापस PTR_ERR(regs);
	पूर्ण
	gbe_dev->चयन_regs = regs;

	gbe_dev->num_stats_mods = gbe_dev->max_num_slaves;
	gbe_dev->et_stats = gbe13_et_stats;
	gbe_dev->num_et_stats = ARRAY_SIZE(gbe13_et_stats);

	gbe_dev->hw_stats = devm_kसुस्मृति(gbe_dev->dev,
					 gbe_dev->num_et_stats, माप(u64),
					 GFP_KERNEL);
	अगर (!gbe_dev->hw_stats) अणु
		dev_err(gbe_dev->dev, "hw_stats memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	gbe_dev->hw_stats_prev =
		devm_kसुस्मृति(gbe_dev->dev,
			     gbe_dev->num_et_stats, माप(u32),
			     GFP_KERNEL);
	अगर (!gbe_dev->hw_stats_prev) अणु
		dev_err(gbe_dev->dev,
			"hw_stats_prev memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	gbe_dev->sgmii_port_regs = gbe_dev->ss_regs + GBE13_SGMII_MODULE_OFFSET;
	gbe_dev->host_port_regs = gbe_dev->चयन_regs + GBE13_HOST_PORT_OFFSET;

	/* K2HK has only 2 hw stats modules visible at a समय, so
	 * module 0 & 2 poपूर्णांकs to one base and
	 * module 1 & 3 poपूर्णांकs to the other base
	 */
	क्रम (i = 0; i < gbe_dev->max_num_slaves; i++) अणु
		gbe_dev->hw_stats_regs[i] =
			gbe_dev->चयन_regs + GBE13_HW_STATS_OFFSET +
			(GBE_HW_STATS_REG_MAP_SZ * (i & 0x1));
	पूर्ण

	gbe_dev->cpts_reg = gbe_dev->चयन_regs + GBE13_CPTS_OFFSET;
	gbe_dev->ale_reg = gbe_dev->चयन_regs + GBE13_ALE_OFFSET;
	gbe_dev->ale_ports = gbe_dev->max_num_ports;
	gbe_dev->host_port = GBE13_HOST_PORT_NUM;
	gbe_dev->stats_en_mask = GBE13_REG_VAL_STAT_ENABLE_ALL;

	/* Subप्रणाली रेजिस्टरs */
	GBE_SET_REG_OFS(gbe_dev, ss_regs, id_ver);

	/* Switch module रेजिस्टरs */
	GBE_SET_REG_OFS(gbe_dev, चयन_regs, id_ver);
	GBE_SET_REG_OFS(gbe_dev, चयन_regs, control);
	GBE_SET_REG_OFS(gbe_dev, चयन_regs, soft_reset);
	GBE_SET_REG_OFS(gbe_dev, चयन_regs, stat_port_en);
	GBE_SET_REG_OFS(gbe_dev, चयन_regs, ptype);
	GBE_SET_REG_OFS(gbe_dev, चयन_regs, flow_control);

	/* Host port रेजिस्टरs */
	GBE_SET_REG_OFS(gbe_dev, host_port_regs, port_vlan);
	GBE_SET_REG_OFS(gbe_dev, host_port_regs, rx_maxlen);
	वापस 0;
पूर्ण

अटल पूर्णांक set_gbenu_ethss_priv(काष्ठा gbe_priv *gbe_dev,
				काष्ठा device_node *node)
अणु
	काष्ठा resource res;
	व्योम __iomem *regs;
	पूर्णांक i, ret;

	gbe_dev->num_stats_mods = gbe_dev->max_num_ports;
	gbe_dev->et_stats = gbenu_et_stats;

	अगर (IS_SS_ID_MU(gbe_dev))
		gbe_dev->num_et_stats = GBENU_ET_STATS_HOST_SIZE +
			(gbe_dev->max_num_slaves * GBENU_ET_STATS_PORT_SIZE);
	अन्यथा
		gbe_dev->num_et_stats = GBENU_ET_STATS_HOST_SIZE +
					GBENU_ET_STATS_PORT_SIZE;

	gbe_dev->hw_stats = devm_kसुस्मृति(gbe_dev->dev,
					 gbe_dev->num_et_stats, माप(u64),
					 GFP_KERNEL);
	अगर (!gbe_dev->hw_stats) अणु
		dev_err(gbe_dev->dev, "hw_stats memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	gbe_dev->hw_stats_prev =
		devm_kसुस्मृति(gbe_dev->dev,
			     gbe_dev->num_et_stats, माप(u32),
			     GFP_KERNEL);
	अगर (!gbe_dev->hw_stats_prev) अणु
		dev_err(gbe_dev->dev,
			"hw_stats_prev memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	ret = of_address_to_resource(node, GBENU_SM_REG_INDEX, &res);
	अगर (ret) अणु
		dev_err(gbe_dev->dev,
			"Can't translate of gbenu node(%pOFn) addr at index %d\n",
			node, GBENU_SM_REG_INDEX);
		वापस ret;
	पूर्ण

	regs = devm_ioremap_resource(gbe_dev->dev, &res);
	अगर (IS_ERR(regs)) अणु
		dev_err(gbe_dev->dev,
			"Failed to map gbenu switch module register base\n");
		वापस PTR_ERR(regs);
	पूर्ण
	gbe_dev->चयन_regs = regs;

	अगर (!IS_SS_ID_2U(gbe_dev))
		gbe_dev->sgmii_port_regs =
		       gbe_dev->ss_regs + GBENU_SGMII_MODULE_OFFSET;

	/* Although sgmii modules are mem mapped to one contiguous
	 * region on GBENU devices, setting sgmii_port34_regs allows
	 * consistent code when accessing sgmii api
	 */
	gbe_dev->sgmii_port34_regs = gbe_dev->sgmii_port_regs +
				     (2 * GBENU_SGMII_MODULE_SIZE);

	gbe_dev->host_port_regs = gbe_dev->चयन_regs + GBENU_HOST_PORT_OFFSET;

	क्रम (i = 0; i < (gbe_dev->max_num_ports); i++)
		gbe_dev->hw_stats_regs[i] = gbe_dev->चयन_regs +
			GBENU_HW_STATS_OFFSET + (GBENU_HW_STATS_REG_MAP_SZ * i);

	gbe_dev->cpts_reg = gbe_dev->चयन_regs + GBENU_CPTS_OFFSET;
	gbe_dev->ale_reg = gbe_dev->चयन_regs + GBENU_ALE_OFFSET;
	gbe_dev->ale_ports = gbe_dev->max_num_ports;
	gbe_dev->host_port = GBENU_HOST_PORT_NUM;
	gbe_dev->stats_en_mask = (1 << (gbe_dev->max_num_ports)) - 1;

	/* Subप्रणाली रेजिस्टरs */
	GBENU_SET_REG_OFS(gbe_dev, ss_regs, id_ver);
	/* ok to set क्रम MU, but used by 2U only */
	GBENU_SET_REG_OFS(gbe_dev, ss_regs, rgmii_status);

	/* Switch module रेजिस्टरs */
	GBENU_SET_REG_OFS(gbe_dev, चयन_regs, id_ver);
	GBENU_SET_REG_OFS(gbe_dev, चयन_regs, control);
	GBENU_SET_REG_OFS(gbe_dev, चयन_regs, stat_port_en);
	GBENU_SET_REG_OFS(gbe_dev, चयन_regs, ptype);

	/* Host port रेजिस्टरs */
	GBENU_SET_REG_OFS(gbe_dev, host_port_regs, port_vlan);
	GBENU_SET_REG_OFS(gbe_dev, host_port_regs, rx_maxlen);

	/* For NU only.  2U करोes not need tx_pri_map.
	 * NU cppi port 0 tx pkt streaming पूर्णांकerface has (n-1)*8 egress thपढ़ोs
	 * जबतक 2U has only 1 such thपढ़ो
	 */
	GBENU_SET_REG_OFS(gbe_dev, host_port_regs, tx_pri_map);
	वापस 0;
पूर्ण

अटल पूर्णांक gbe_probe(काष्ठा netcp_device *netcp_device, काष्ठा device *dev,
		     काष्ठा device_node *node, व्योम **inst_priv)
अणु
	काष्ठा device_node *पूर्णांकerfaces, *पूर्णांकerface, *cpts_node;
	काष्ठा device_node *secondary_ports;
	काष्ठा cpsw_ale_params ale_params;
	काष्ठा gbe_priv *gbe_dev;
	u32 slave_num;
	पूर्णांक i, ret = 0;

	अगर (!node) अणु
		dev_err(dev, "device tree info unavailable\n");
		वापस -ENODEV;
	पूर्ण

	gbe_dev = devm_kzalloc(dev, माप(काष्ठा gbe_priv), GFP_KERNEL);
	अगर (!gbe_dev)
		वापस -ENOMEM;

	अगर (of_device_is_compatible(node, "ti,netcp-gbe-5") ||
	    of_device_is_compatible(node, "ti,netcp-gbe")) अणु
		gbe_dev->max_num_slaves = 4;
	पूर्ण अन्यथा अगर (of_device_is_compatible(node, "ti,netcp-gbe-9")) अणु
		gbe_dev->max_num_slaves = 8;
	पूर्ण अन्यथा अगर (of_device_is_compatible(node, "ti,netcp-gbe-2")) अणु
		gbe_dev->max_num_slaves = 1;
		gbe_module.set_rx_mode = gbe_set_rx_mode;
	पूर्ण अन्यथा अगर (of_device_is_compatible(node, "ti,netcp-xgbe")) अणु
		gbe_dev->max_num_slaves = 2;
	पूर्ण अन्यथा अणु
		dev_err(dev, "device tree node for unknown device\n");
		वापस -EINVAL;
	पूर्ण
	gbe_dev->max_num_ports = gbe_dev->max_num_slaves + 1;

	gbe_dev->dev = dev;
	gbe_dev->netcp_device = netcp_device;
	gbe_dev->rx_packet_max = NETCP_MAX_FRAME_SIZE;

	/* init the hw stats lock */
	spin_lock_init(&gbe_dev->hw_stats_lock);

	अगर (of_find_property(node, "enable-ale", शून्य)) अणु
		gbe_dev->enable_ale = true;
		dev_info(dev, "ALE enabled\n");
	पूर्ण अन्यथा अणु
		gbe_dev->enable_ale = false;
		dev_dbg(dev, "ALE bypass enabled*\n");
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "tx-queue",
				   &gbe_dev->tx_queue_id);
	अगर (ret < 0) अणु
		dev_err(dev, "missing tx_queue parameter\n");
		gbe_dev->tx_queue_id = GBE_TX_QUEUE;
	पूर्ण

	ret = of_property_पढ़ो_string(node, "tx-channel",
				      &gbe_dev->dma_chan_name);
	अगर (ret < 0) अणु
		dev_err(dev, "missing \"tx-channel\" parameter\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_node_name_eq(node, "gbe")) अणु
		ret = get_gbe_resource_version(gbe_dev, node);
		अगर (ret)
			वापस ret;

		dev_dbg(dev, "ss_version: 0x%08x\n", gbe_dev->ss_version);

		अगर (IS_SS_ID_VER_14(gbe_dev))
			ret = set_gbe_ethss14_priv(gbe_dev, node);
		अन्यथा अगर (IS_SS_ID_MU(gbe_dev))
			ret = set_gbenu_ethss_priv(gbe_dev, node);
		अन्यथा
			ret = -ENODEV;

	पूर्ण अन्यथा अगर (of_node_name_eq(node, "xgbe")) अणु
		ret = set_xgbe_ethss10_priv(gbe_dev, node);
		अगर (ret)
			वापस ret;
		ret = netcp_xgbe_serdes_init(gbe_dev->xgbe_serdes_regs,
					     gbe_dev->ss_regs);
	पूर्ण अन्यथा अणु
		dev_err(dev, "unknown GBE node(%pOFn)\n", node);
		ret = -ENODEV;
	पूर्ण

	अगर (ret)
		वापस ret;

	पूर्णांकerfaces = of_get_child_by_name(node, "interfaces");
	अगर (!पूर्णांकerfaces)
		dev_err(dev, "could not find interfaces\n");

	ret = netcp_txpipe_init(&gbe_dev->tx_pipe, netcp_device,
				gbe_dev->dma_chan_name, gbe_dev->tx_queue_id);
	अगर (ret) अणु
		of_node_put(पूर्णांकerfaces);
		वापस ret;
	पूर्ण

	ret = netcp_txpipe_खोलो(&gbe_dev->tx_pipe);
	अगर (ret) अणु
		of_node_put(पूर्णांकerfaces);
		वापस ret;
	पूर्ण

	/* Create network पूर्णांकerfaces */
	INIT_LIST_HEAD(&gbe_dev->gbe_पूर्णांकf_head);
	क्रम_each_child_of_node(पूर्णांकerfaces, पूर्णांकerface) अणु
		ret = of_property_पढ़ो_u32(पूर्णांकerface, "slave-port", &slave_num);
		अगर (ret) अणु
			dev_err(dev, "missing slave-port parameter, skipping interface configuration for %pOFn\n",
				पूर्णांकerface);
			जारी;
		पूर्ण
		gbe_dev->num_slaves++;
		अगर (gbe_dev->num_slaves >= gbe_dev->max_num_slaves) अणु
			of_node_put(पूर्णांकerface);
			अवरोध;
		पूर्ण
	पूर्ण
	of_node_put(पूर्णांकerfaces);

	अगर (!gbe_dev->num_slaves)
		dev_warn(dev, "No network interface configured\n");

	/* Initialize Secondary slave ports */
	secondary_ports = of_get_child_by_name(node, "secondary-slave-ports");
	INIT_LIST_HEAD(&gbe_dev->secondary_slaves);
	अगर (secondary_ports && (gbe_dev->num_slaves <  gbe_dev->max_num_slaves))
		init_secondary_ports(gbe_dev, secondary_ports);
	of_node_put(secondary_ports);

	अगर (!gbe_dev->num_slaves) अणु
		dev_err(dev,
			"No network interface or secondary ports configured\n");
		ret = -ENODEV;
		जाओ मुक्त_sec_ports;
	पूर्ण

	स_रखो(&ale_params, 0, माप(ale_params));
	ale_params.dev		= gbe_dev->dev;
	ale_params.ale_regs	= gbe_dev->ale_reg;
	ale_params.ale_ageout	= GBE_DEFAULT_ALE_AGEOUT;
	ale_params.ale_ports	= gbe_dev->ale_ports;
	ale_params.dev_id	= "cpsw";
	अगर (IS_SS_ID_NU(gbe_dev))
		ale_params.dev_id = "66ak2el";
	अन्यथा अगर (IS_SS_ID_2U(gbe_dev))
		ale_params.dev_id = "66ak2g";
	अन्यथा अगर (IS_SS_ID_XGBE(gbe_dev))
		ale_params.dev_id = "66ak2h-xgbe";

	gbe_dev->ale = cpsw_ale_create(&ale_params);
	अगर (IS_ERR(gbe_dev->ale)) अणु
		dev_err(gbe_dev->dev, "error initializing ale engine\n");
		ret = PTR_ERR(gbe_dev->ale);
		जाओ मुक्त_sec_ports;
	पूर्ण अन्यथा अणु
		dev_dbg(gbe_dev->dev, "Created a gbe ale engine\n");
	पूर्ण

	cpts_node = of_get_child_by_name(node, "cpts");
	अगर (!cpts_node)
		cpts_node = of_node_get(node);

	gbe_dev->cpts = cpts_create(gbe_dev->dev, gbe_dev->cpts_reg,
				    cpts_node, 0);
	of_node_put(cpts_node);
	अगर (IS_ENABLED(CONFIG_TI_CPTS) && IS_ERR(gbe_dev->cpts)) अणु
		ret = PTR_ERR(gbe_dev->cpts);
		जाओ मुक्त_sec_ports;
	पूर्ण

	/* initialize host port */
	gbe_init_host_port(gbe_dev);

	spin_lock_bh(&gbe_dev->hw_stats_lock);
	क्रम (i = 0; i < gbe_dev->num_stats_mods; i++) अणु
		अगर (IS_SS_ID_VER_14(gbe_dev))
			gbe_reset_mod_stats_ver14(gbe_dev, i);
		अन्यथा
			gbe_reset_mod_stats(gbe_dev, i);
	पूर्ण
	spin_unlock_bh(&gbe_dev->hw_stats_lock);

	समयr_setup(&gbe_dev->समयr, netcp_ethss_समयr, 0);
	gbe_dev->समयr.expires	 = jअगरfies + GBE_TIMER_INTERVAL;
	add_समयr(&gbe_dev->समयr);
	*inst_priv = gbe_dev;
	वापस 0;

मुक्त_sec_ports:
	मुक्त_secondary_ports(gbe_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक gbe_attach(व्योम *inst_priv, काष्ठा net_device *ndev,
		      काष्ठा device_node *node, व्योम **पूर्णांकf_priv)
अणु
	काष्ठा gbe_priv *gbe_dev = inst_priv;
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf;
	पूर्णांक ret;

	अगर (!node) अणु
		dev_err(gbe_dev->dev, "interface node not available\n");
		वापस -ENODEV;
	पूर्ण

	gbe_पूर्णांकf = devm_kzalloc(gbe_dev->dev, माप(*gbe_पूर्णांकf), GFP_KERNEL);
	अगर (!gbe_पूर्णांकf)
		वापस -ENOMEM;

	gbe_पूर्णांकf->ndev = ndev;
	gbe_पूर्णांकf->dev = gbe_dev->dev;
	gbe_पूर्णांकf->gbe_dev = gbe_dev;

	gbe_पूर्णांकf->slave = devm_kzalloc(gbe_dev->dev,
					माप(*gbe_पूर्णांकf->slave),
					GFP_KERNEL);
	अगर (!gbe_पूर्णांकf->slave) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	अगर (init_slave(gbe_dev, gbe_पूर्णांकf->slave, node)) अणु
		ret = -ENODEV;
		जाओ fail;
	पूर्ण

	gbe_पूर्णांकf->tx_pipe = gbe_dev->tx_pipe;
	ndev->ethtool_ops = &keystone_ethtool_ops;
	list_add_tail(&gbe_पूर्णांकf->gbe_पूर्णांकf_list, &gbe_dev->gbe_पूर्णांकf_head);
	*पूर्णांकf_priv = gbe_पूर्णांकf;
	वापस 0;

fail:
	अगर (gbe_पूर्णांकf->slave)
		devm_kमुक्त(gbe_dev->dev, gbe_पूर्णांकf->slave);
	अगर (gbe_पूर्णांकf)
		devm_kमुक्त(gbe_dev->dev, gbe_पूर्णांकf);
	वापस ret;
पूर्ण

अटल पूर्णांक gbe_release(व्योम *पूर्णांकf_priv)
अणु
	काष्ठा gbe_पूर्णांकf *gbe_पूर्णांकf = पूर्णांकf_priv;

	gbe_पूर्णांकf->ndev->ethtool_ops = शून्य;
	list_del(&gbe_पूर्णांकf->gbe_पूर्णांकf_list);
	devm_kमुक्त(gbe_पूर्णांकf->dev, gbe_पूर्णांकf->slave);
	devm_kमुक्त(gbe_पूर्णांकf->dev, gbe_पूर्णांकf);
	वापस 0;
पूर्ण

अटल पूर्णांक gbe_हटाओ(काष्ठा netcp_device *netcp_device, व्योम *inst_priv)
अणु
	काष्ठा gbe_priv *gbe_dev = inst_priv;

	del_समयr_sync(&gbe_dev->समयr);
	cpts_release(gbe_dev->cpts);
	cpsw_ale_stop(gbe_dev->ale);
	netcp_txpipe_बंद(&gbe_dev->tx_pipe);
	मुक्त_secondary_ports(gbe_dev);

	अगर (!list_empty(&gbe_dev->gbe_पूर्णांकf_head))
		dev_alert(gbe_dev->dev,
			  "unreleased ethss interfaces present\n");

	वापस 0;
पूर्ण

अटल काष्ठा netcp_module gbe_module = अणु
	.name		= GBE_MODULE_NAME,
	.owner		= THIS_MODULE,
	.primary	= true,
	.probe		= gbe_probe,
	.खोलो		= gbe_खोलो,
	.बंद		= gbe_बंद,
	.हटाओ		= gbe_हटाओ,
	.attach		= gbe_attach,
	.release	= gbe_release,
	.add_addr	= gbe_add_addr,
	.del_addr	= gbe_del_addr,
	.add_vid	= gbe_add_vid,
	.del_vid	= gbe_del_vid,
	.ioctl		= gbe_ioctl,
पूर्ण;

अटल काष्ठा netcp_module xgbe_module = अणु
	.name		= XGBE_MODULE_NAME,
	.owner		= THIS_MODULE,
	.primary	= true,
	.probe		= gbe_probe,
	.खोलो		= gbe_खोलो,
	.बंद		= gbe_बंद,
	.हटाओ		= gbe_हटाओ,
	.attach		= gbe_attach,
	.release	= gbe_release,
	.add_addr	= gbe_add_addr,
	.del_addr	= gbe_del_addr,
	.add_vid	= gbe_add_vid,
	.del_vid	= gbe_del_vid,
	.ioctl		= gbe_ioctl,
पूर्ण;

अटल पूर्णांक __init keystone_gbe_init(व्योम)
अणु
	पूर्णांक ret;

	ret = netcp_रेजिस्टर_module(&gbe_module);
	अगर (ret)
		वापस ret;

	ret = netcp_रेजिस्टर_module(&xgbe_module);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण
module_init(keystone_gbe_init);

अटल व्योम __निकास keystone_gbe_निकास(व्योम)
अणु
	netcp_unरेजिस्टर_module(&gbe_module);
	netcp_unरेजिस्टर_module(&xgbe_module);
पूर्ण
module_निकास(keystone_gbe_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("TI NETCP ETHSS driver for Keystone SOCs");
MODULE_AUTHOR("Sandeep Nair <sandeep_n@ti.com");
