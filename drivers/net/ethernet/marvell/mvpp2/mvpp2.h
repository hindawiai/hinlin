<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions क्रम Marvell PPv2 network controller क्रम Armada 375 SoC.
 *
 * Copyright (C) 2014 Marvell
 *
 * Marcin Wojtas <mw@semihalf.com>
 */
#अगर_अघोषित _MVPP2_H_
#घोषणा _MVPP2_H_

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/phy.h>
#समावेश <linux/phylink.h>
#समावेश <net/flow_offload.h>
#समावेश <net/page_pool.h>
#समावेश <linux/bpf.h>
#समावेश <net/xdp.h>

/* The PacketOffset field is measured in units of 32 bytes and is 3 bits wide,
 * so the maximum offset is 7 * 32 = 224
 */
#घोषणा MVPP2_SKB_HEADROOM	min(max(XDP_PACKET_HEADROOM, NET_SKB_PAD), 224)

#घोषणा MVPP2_XDP_PASS		0
#घोषणा MVPP2_XDP_DROPPED	BIT(0)
#घोषणा MVPP2_XDP_TX		BIT(1)
#घोषणा MVPP2_XDP_REसूची		BIT(2)

/* Fअगरo Registers */
#घोषणा MVPP2_RX_DATA_FIFO_SIZE_REG(port)	(0x00 + 4 * (port))
#घोषणा MVPP2_RX_ATTR_FIFO_SIZE_REG(port)	(0x20 + 4 * (port))
#घोषणा MVPP2_RX_MIN_PKT_SIZE_REG		0x60
#घोषणा MVPP2_RX_FIFO_INIT_REG			0x64
#घोषणा MVPP22_TX_FIFO_THRESH_REG(port)		(0x8840 + 4 * (port))
#घोषणा MVPP22_TX_FIFO_SIZE_REG(port)		(0x8860 + 4 * (port))

/* RX DMA Top Registers */
#घोषणा MVPP2_RX_CTRL_REG(port)			(0x140 + 4 * (port))
#घोषणा     MVPP2_RX_LOW_LATENCY_PKT_SIZE(s)	(((s) & 0xfff) << 16)
#घोषणा     MVPP2_RX_USE_PSEUDO_FOR_CSUM_MASK	BIT(31)
#घोषणा MVPP2_POOL_BUF_SIZE_REG(pool)		(0x180 + 4 * (pool))
#घोषणा     MVPP2_POOL_BUF_SIZE_OFFSET		5
#घोषणा MVPP2_RXQ_CONFIG_REG(rxq)		(0x800 + 4 * (rxq))
#घोषणा     MVPP2_SNOOP_PKT_SIZE_MASK		0x1ff
#घोषणा     MVPP2_SNOOP_BUF_HDR_MASK		BIT(9)
#घोषणा     MVPP2_RXQ_POOL_SHORT_OFFS		20
#घोषणा     MVPP21_RXQ_POOL_SHORT_MASK		0x700000
#घोषणा     MVPP22_RXQ_POOL_SHORT_MASK		0xf00000
#घोषणा     MVPP2_RXQ_POOL_LONG_OFFS		24
#घोषणा     MVPP21_RXQ_POOL_LONG_MASK		0x7000000
#घोषणा     MVPP22_RXQ_POOL_LONG_MASK		0xf000000
#घोषणा     MVPP2_RXQ_PACKET_OFFSET_OFFS	28
#घोषणा     MVPP2_RXQ_PACKET_OFFSET_MASK	0x70000000
#घोषणा     MVPP2_RXQ_DISABLE_MASK		BIT(31)

/* Top Registers */
#घोषणा MVPP2_MH_REG(port)			(0x5040 + 4 * (port))
#घोषणा MVPP2_DSA_EXTENDED			BIT(5)
#घोषणा MVPP2_VER_ID_REG			0x50b0
#घोषणा MVPP2_VER_PP22				0x10
#घोषणा MVPP2_VER_PP23				0x11

/* Parser Registers */
#घोषणा MVPP2_PRS_INIT_LOOKUP_REG		0x1000
#घोषणा     MVPP2_PRS_PORT_LU_MAX		0xf
#घोषणा     MVPP2_PRS_PORT_LU_MASK(port)	(0xff << ((port) * 4))
#घोषणा     MVPP2_PRS_PORT_LU_VAL(port, val)	((val) << ((port) * 4))
#घोषणा MVPP2_PRS_INIT_OFFS_REG(port)		(0x1004 + ((port) & 4))
#घोषणा     MVPP2_PRS_INIT_OFF_MASK(port)	(0x3f << (((port) % 4) * 8))
#घोषणा     MVPP2_PRS_INIT_OFF_VAL(port, val)	((val) << (((port) % 4) * 8))
#घोषणा MVPP2_PRS_MAX_LOOP_REG(port)		(0x100c + ((port) & 4))
#घोषणा     MVPP2_PRS_MAX_LOOP_MASK(port)	(0xff << (((port) % 4) * 8))
#घोषणा     MVPP2_PRS_MAX_LOOP_VAL(port, val)	((val) << (((port) % 4) * 8))
#घोषणा MVPP2_PRS_TCAM_IDX_REG			0x1100
#घोषणा MVPP2_PRS_TCAM_DATA_REG(idx)		(0x1104 + (idx) * 4)
#घोषणा     MVPP2_PRS_TCAM_INV_MASK		BIT(31)
#घोषणा MVPP2_PRS_SRAM_IDX_REG			0x1200
#घोषणा MVPP2_PRS_SRAM_DATA_REG(idx)		(0x1204 + (idx) * 4)
#घोषणा MVPP2_PRS_TCAM_CTRL_REG			0x1230
#घोषणा     MVPP2_PRS_TCAM_EN_MASK		BIT(0)
#घोषणा MVPP2_PRS_TCAM_HIT_IDX_REG		0x1240
#घोषणा MVPP2_PRS_TCAM_HIT_CNT_REG		0x1244
#घोषणा     MVPP2_PRS_TCAM_HIT_CNT_MASK		GENMASK(15, 0)

/* RSS Registers */
#घोषणा MVPP22_RSS_INDEX			0x1500
#घोषणा     MVPP22_RSS_INDEX_TABLE_ENTRY(idx)	(idx)
#घोषणा     MVPP22_RSS_INDEX_TABLE(idx)		((idx) << 8)
#घोषणा     MVPP22_RSS_INDEX_QUEUE(idx)		((idx) << 16)
#घोषणा MVPP22_RXQ2RSS_TABLE			0x1504
#घोषणा     MVPP22_RSS_TABLE_POINTER(p)		(p)
#घोषणा MVPP22_RSS_TABLE_ENTRY			0x1508
#घोषणा MVPP22_RSS_WIDTH			0x150c

/* Classअगरier Registers */
#घोषणा MVPP2_CLS_MODE_REG			0x1800
#घोषणा     MVPP2_CLS_MODE_ACTIVE_MASK		BIT(0)
#घोषणा MVPP2_CLS_PORT_WAY_REG			0x1810
#घोषणा     MVPP2_CLS_PORT_WAY_MASK(port)	(1 << (port))
#घोषणा MVPP2_CLS_LKP_INDEX_REG			0x1814
#घोषणा     MVPP2_CLS_LKP_INDEX_WAY_OFFS	6
#घोषणा MVPP2_CLS_LKP_TBL_REG			0x1818
#घोषणा     MVPP2_CLS_LKP_TBL_RXQ_MASK		0xff
#घोषणा     MVPP2_CLS_LKP_FLOW_PTR(flow)	((flow) << 16)
#घोषणा     MVPP2_CLS_LKP_TBL_LOOKUP_EN_MASK	BIT(25)
#घोषणा MVPP2_CLS_FLOW_INDEX_REG		0x1820
#घोषणा MVPP2_CLS_FLOW_TBL0_REG			0x1824
#घोषणा     MVPP2_CLS_FLOW_TBL0_LAST		BIT(0)
#घोषणा     MVPP2_CLS_FLOW_TBL0_ENG_MASK	0x7
#घोषणा     MVPP2_CLS_FLOW_TBL0_OFFS		1
#घोषणा     MVPP2_CLS_FLOW_TBL0_ENG(x)		((x) << 1)
#घोषणा     MVPP2_CLS_FLOW_TBL0_PORT_ID_MASK	0xff
#घोषणा     MVPP2_CLS_FLOW_TBL0_PORT_ID(port)	((port) << 4)
#घोषणा     MVPP2_CLS_FLOW_TBL0_PORT_ID_SEL	BIT(23)
#घोषणा MVPP2_CLS_FLOW_TBL1_REG			0x1828
#घोषणा     MVPP2_CLS_FLOW_TBL1_N_FIELDS_MASK	0x7
#घोषणा     MVPP2_CLS_FLOW_TBL1_N_FIELDS(x)	(x)
#घोषणा     MVPP2_CLS_FLOW_TBL1_LU_TYPE(lu)	(((lu) & 0x3f) << 3)
#घोषणा     MVPP2_CLS_FLOW_TBL1_PRIO_MASK	0x3f
#घोषणा     MVPP2_CLS_FLOW_TBL1_PRIO(x)		((x) << 9)
#घोषणा     MVPP2_CLS_FLOW_TBL1_SEQ_MASK	0x7
#घोषणा     MVPP2_CLS_FLOW_TBL1_SEQ(x)		((x) << 15)
#घोषणा MVPP2_CLS_FLOW_TBL2_REG			0x182c
#घोषणा     MVPP2_CLS_FLOW_TBL2_FLD_MASK	0x3f
#घोषणा     MVPP2_CLS_FLOW_TBL2_FLD_OFFS(n)	((n) * 6)
#घोषणा     MVPP2_CLS_FLOW_TBL2_FLD(n, x)	((x) << ((n) * 6))
#घोषणा MVPP2_CLS_OVERSIZE_RXQ_LOW_REG(port)	(0x1980 + ((port) * 4))
#घोषणा     MVPP2_CLS_OVERSIZE_RXQ_LOW_BITS	3
#घोषणा     MVPP2_CLS_OVERSIZE_RXQ_LOW_MASK	0x7
#घोषणा MVPP2_CLS_SWFWD_P2HQ_REG(port)		(0x19b0 + ((port) * 4))
#घोषणा MVPP2_CLS_SWFWD_PCTRL_REG		0x19d0
#घोषणा     MVPP2_CLS_SWFWD_PCTRL_MASK(port)	(1 << (port))

/* Classअगरier C2 engine Registers */
#घोषणा MVPP22_CLS_C2_TCAM_IDX			0x1b00
#घोषणा MVPP22_CLS_C2_TCAM_DATA0		0x1b10
#घोषणा MVPP22_CLS_C2_TCAM_DATA1		0x1b14
#घोषणा MVPP22_CLS_C2_TCAM_DATA2		0x1b18
#घोषणा MVPP22_CLS_C2_TCAM_DATA3		0x1b1c
#घोषणा MVPP22_CLS_C2_TCAM_DATA4		0x1b20
#घोषणा     MVPP22_CLS_C2_LU_TYPE(lu)		((lu) & 0x3f)
#घोषणा     MVPP22_CLS_C2_PORT_ID(port)		((port) << 8)
#घोषणा     MVPP22_CLS_C2_PORT_MASK		(0xff << 8)
#घोषणा MVPP22_CLS_C2_TCAM_INV			0x1b24
#घोषणा     MVPP22_CLS_C2_TCAM_INV_BIT		BIT(31)
#घोषणा MVPP22_CLS_C2_HIT_CTR			0x1b50
#घोषणा MVPP22_CLS_C2_ACT			0x1b60
#घोषणा     MVPP22_CLS_C2_ACT_RSS_EN(act)	(((act) & 0x3) << 19)
#घोषणा     MVPP22_CLS_C2_ACT_FWD(act)		(((act) & 0x7) << 13)
#घोषणा     MVPP22_CLS_C2_ACT_QHIGH(act)	(((act) & 0x3) << 11)
#घोषणा     MVPP22_CLS_C2_ACT_QLOW(act)		(((act) & 0x3) << 9)
#घोषणा     MVPP22_CLS_C2_ACT_COLOR(act)	((act) & 0x7)
#घोषणा MVPP22_CLS_C2_ATTR0			0x1b64
#घोषणा     MVPP22_CLS_C2_ATTR0_QHIGH(qh)	(((qh) & 0x1f) << 24)
#घोषणा     MVPP22_CLS_C2_ATTR0_QHIGH_MASK	0x1f
#घोषणा     MVPP22_CLS_C2_ATTR0_QHIGH_OFFS	24
#घोषणा     MVPP22_CLS_C2_ATTR0_QLOW(ql)	(((ql) & 0x7) << 21)
#घोषणा     MVPP22_CLS_C2_ATTR0_QLOW_MASK	0x7
#घोषणा     MVPP22_CLS_C2_ATTR0_QLOW_OFFS	21
#घोषणा MVPP22_CLS_C2_ATTR1			0x1b68
#घोषणा MVPP22_CLS_C2_ATTR2			0x1b6c
#घोषणा     MVPP22_CLS_C2_ATTR2_RSS_EN		BIT(30)
#घोषणा MVPP22_CLS_C2_ATTR3			0x1b70
#घोषणा MVPP22_CLS_C2_TCAM_CTRL			0x1b90
#घोषणा     MVPP22_CLS_C2_TCAM_BYPASS_FIFO	BIT(0)

/* Descriptor Manager Top Registers */
#घोषणा MVPP2_RXQ_NUM_REG			0x2040
#घोषणा MVPP2_RXQ_DESC_ADDR_REG			0x2044
#घोषणा     MVPP22_DESC_ADDR_OFFS		8
#घोषणा MVPP2_RXQ_DESC_SIZE_REG			0x2048
#घोषणा     MVPP2_RXQ_DESC_SIZE_MASK		0x3ff0
#घोषणा MVPP2_RXQ_STATUS_UPDATE_REG(rxq)	(0x3000 + 4 * (rxq))
#घोषणा     MVPP2_RXQ_NUM_PROCESSED_OFFSET	0
#घोषणा     MVPP2_RXQ_NUM_NEW_OFFSET		16
#घोषणा MVPP2_RXQ_STATUS_REG(rxq)		(0x3400 + 4 * (rxq))
#घोषणा     MVPP2_RXQ_OCCUPIED_MASK		0x3fff
#घोषणा     MVPP2_RXQ_NON_OCCUPIED_OFFSET	16
#घोषणा     MVPP2_RXQ_NON_OCCUPIED_MASK		0x3fff0000
#घोषणा MVPP2_RXQ_THRESH_REG			0x204c
#घोषणा     MVPP2_OCCUPIED_THRESH_OFFSET	0
#घोषणा     MVPP2_OCCUPIED_THRESH_MASK		0x3fff
#घोषणा MVPP2_RXQ_INDEX_REG			0x2050
#घोषणा MVPP2_TXQ_NUM_REG			0x2080
#घोषणा MVPP2_TXQ_DESC_ADDR_REG			0x2084
#घोषणा MVPP2_TXQ_DESC_SIZE_REG			0x2088
#घोषणा     MVPP2_TXQ_DESC_SIZE_MASK		0x3ff0
#घोषणा MVPP2_TXQ_THRESH_REG			0x2094
#घोषणा	    MVPP2_TXQ_THRESH_OFFSET		16
#घोषणा	    MVPP2_TXQ_THRESH_MASK		0x3fff
#घोषणा MVPP2_AGGR_TXQ_UPDATE_REG		0x2090
#घोषणा MVPP2_TXQ_INDEX_REG			0x2098
#घोषणा MVPP2_TXQ_PREF_BUF_REG			0x209c
#घोषणा     MVPP2_PREF_BUF_PTR(desc)		((desc) & 0xfff)
#घोषणा     MVPP2_PREF_BUF_SIZE_4		(BIT(12) | BIT(13))
#घोषणा     MVPP2_PREF_BUF_SIZE_16		(BIT(12) | BIT(14))
#घोषणा     MVPP2_PREF_BUF_THRESH(val)		((val) << 17)
#घोषणा     MVPP2_TXQ_DRAIN_EN_MASK		BIT(31)
#घोषणा MVPP2_TXQ_PENDING_REG			0x20a0
#घोषणा     MVPP2_TXQ_PENDING_MASK		0x3fff
#घोषणा MVPP2_TXQ_INT_STATUS_REG		0x20a4
#घोषणा MVPP2_TXQ_SENT_REG(txq)			(0x3c00 + 4 * (txq))
#घोषणा     MVPP2_TRANSMITTED_COUNT_OFFSET	16
#घोषणा     MVPP2_TRANSMITTED_COUNT_MASK	0x3fff0000
#घोषणा MVPP2_TXQ_RSVD_REQ_REG			0x20b0
#घोषणा     MVPP2_TXQ_RSVD_REQ_Q_OFFSET		16
#घोषणा MVPP2_TXQ_RSVD_RSLT_REG			0x20b4
#घोषणा     MVPP2_TXQ_RSVD_RSLT_MASK		0x3fff
#घोषणा MVPP2_TXQ_RSVD_CLR_REG			0x20b8
#घोषणा     MVPP2_TXQ_RSVD_CLR_OFFSET		16
#घोषणा MVPP2_AGGR_TXQ_DESC_ADDR_REG(cpu)	(0x2100 + 4 * (cpu))
#घोषणा     MVPP22_AGGR_TXQ_DESC_ADDR_OFFS	8
#घोषणा MVPP2_AGGR_TXQ_DESC_SIZE_REG(cpu)	(0x2140 + 4 * (cpu))
#घोषणा     MVPP2_AGGR_TXQ_DESC_SIZE_MASK	0x3ff0
#घोषणा MVPP2_AGGR_TXQ_STATUS_REG(cpu)		(0x2180 + 4 * (cpu))
#घोषणा     MVPP2_AGGR_TXQ_PENDING_MASK		0x3fff
#घोषणा MVPP2_AGGR_TXQ_INDEX_REG(cpu)		(0x21c0 + 4 * (cpu))

/* MBUS bridge रेजिस्टरs */
#घोषणा MVPP2_WIN_BASE(w)			(0x4000 + ((w) << 2))
#घोषणा MVPP2_WIN_SIZE(w)			(0x4020 + ((w) << 2))
#घोषणा MVPP2_WIN_REMAP(w)			(0x4040 + ((w) << 2))
#घोषणा MVPP2_BASE_ADDR_ENABLE			0x4060

/* AXI Bridge Registers */
#घोषणा MVPP22_AXI_BM_WR_ATTR_REG		0x4100
#घोषणा MVPP22_AXI_BM_RD_ATTR_REG		0x4104
#घोषणा MVPP22_AXI_AGGRQ_DESCR_RD_ATTR_REG	0x4110
#घोषणा MVPP22_AXI_TXQ_DESCR_WR_ATTR_REG	0x4114
#घोषणा MVPP22_AXI_TXQ_DESCR_RD_ATTR_REG	0x4118
#घोषणा MVPP22_AXI_RXQ_DESCR_WR_ATTR_REG	0x411c
#घोषणा MVPP22_AXI_RX_DATA_WR_ATTR_REG		0x4120
#घोषणा MVPP22_AXI_TX_DATA_RD_ATTR_REG		0x4130
#घोषणा MVPP22_AXI_RD_NORMAL_CODE_REG		0x4150
#घोषणा MVPP22_AXI_RD_SNOOP_CODE_REG		0x4154
#घोषणा MVPP22_AXI_WR_NORMAL_CODE_REG		0x4160
#घोषणा MVPP22_AXI_WR_SNOOP_CODE_REG		0x4164

/* Values क्रम AXI Bridge रेजिस्टरs */
#घोषणा MVPP22_AXI_ATTR_CACHE_OFFS		0
#घोषणा MVPP22_AXI_ATTR_DOMAIN_OFFS		12

#घोषणा MVPP22_AXI_CODE_CACHE_OFFS		0
#घोषणा MVPP22_AXI_CODE_DOMAIN_OFFS		4

#घोषणा MVPP22_AXI_CODE_CACHE_NON_CACHE		0x3
#घोषणा MVPP22_AXI_CODE_CACHE_WR_CACHE		0x7
#घोषणा MVPP22_AXI_CODE_CACHE_RD_CACHE		0xb

#घोषणा MVPP22_AXI_CODE_DOMAIN_OUTER_DOM	2
#घोषणा MVPP22_AXI_CODE_DOMAIN_SYSTEM		3

/* Interrupt Cause and Mask रेजिस्टरs */
#घोषणा MVPP2_ISR_TX_THRESHOLD_REG(port)	(0x5140 + 4 * (port))
#घोषणा     MVPP2_MAX_ISR_TX_THRESHOLD		0xfffff0

#घोषणा MVPP2_ISR_RX_THRESHOLD_REG(rxq)		(0x5200 + 4 * (rxq))
#घोषणा     MVPP2_MAX_ISR_RX_THRESHOLD		0xfffff0
#घोषणा MVPP21_ISR_RXQ_GROUP_REG(port)		(0x5400 + 4 * (port))

#घोषणा MVPP22_ISR_RXQ_GROUP_INDEX_REG		0x5400
#घोषणा MVPP22_ISR_RXQ_GROUP_INDEX_SUBGROUP_MASK 0xf
#घोषणा MVPP22_ISR_RXQ_GROUP_INDEX_GROUP_MASK	0x380
#घोषणा MVPP22_ISR_RXQ_GROUP_INDEX_GROUP_OFFSET	7

#घोषणा MVPP22_ISR_RXQ_GROUP_INDEX_SUBGROUP_MASK 0xf
#घोषणा MVPP22_ISR_RXQ_GROUP_INDEX_GROUP_MASK	0x380

#घोषणा MVPP22_ISR_RXQ_SUB_GROUP_CONFIG_REG	0x5404
#घोषणा MVPP22_ISR_RXQ_SUB_GROUP_STARTQ_MASK	0x1f
#घोषणा MVPP22_ISR_RXQ_SUB_GROUP_SIZE_MASK	0xf00
#घोषणा MVPP22_ISR_RXQ_SUB_GROUP_SIZE_OFFSET	8

#घोषणा MVPP2_ISR_ENABLE_REG(port)		(0x5420 + 4 * (port))
#घोषणा     MVPP2_ISR_ENABLE_INTERRUPT(mask)	((mask) & 0xffff)
#घोषणा     MVPP2_ISR_DISABLE_INTERRUPT(mask)	(((mask) << 16) & 0xffff0000)
#घोषणा MVPP2_ISR_RX_TX_CAUSE_REG(port)		(0x5480 + 4 * (port))
#घोषणा     MVPP2_CAUSE_RXQ_OCCUP_DESC_ALL_MASK(version) \
					((version) == MVPP21 ? 0xffff : 0xff)
#घोषणा     MVPP2_CAUSE_TXQ_OCCUP_DESC_ALL_MASK	0xff0000
#घोषणा     MVPP2_CAUSE_TXQ_OCCUP_DESC_ALL_OFFSET	16
#घोषणा     MVPP2_CAUSE_RX_FIFO_OVERRUN_MASK	BIT(24)
#घोषणा     MVPP2_CAUSE_FCS_ERR_MASK		BIT(25)
#घोषणा     MVPP2_CAUSE_TX_FIFO_UNDERRUN_MASK	BIT(26)
#घोषणा     MVPP2_CAUSE_TX_EXCEPTION_SUM_MASK	BIT(29)
#घोषणा     MVPP2_CAUSE_RX_EXCEPTION_SUM_MASK	BIT(30)
#घोषणा     MVPP2_CAUSE_MISC_SUM_MASK		BIT(31)
#घोषणा MVPP2_ISR_RX_TX_MASK_REG(port)		(0x54a0 + 4 * (port))
#घोषणा MVPP2_ISR_PON_RX_TX_MASK_REG		0x54bc
#घोषणा     MVPP2_PON_CAUSE_RXQ_OCCUP_DESC_ALL_MASK	0xffff
#घोषणा     MVPP2_PON_CAUSE_TXP_OCCUP_DESC_ALL_MASK	0x3fc00000
#घोषणा     MVPP2_PON_CAUSE_MISC_SUM_MASK		BIT(31)
#घोषणा MVPP2_ISR_MISC_CAUSE_REG		0x55b0
#घोषणा MVPP2_ISR_RX_ERR_CAUSE_REG(port)	(0x5520 + 4 * (port))
#घोषणा     MVPP2_ISR_RX_ERR_CAUSE_NONOCC_MASK	0x00ff

/* Buffer Manager रेजिस्टरs */
#घोषणा MVPP2_BM_POOL_BASE_REG(pool)		(0x6000 + ((pool) * 4))
#घोषणा     MVPP2_BM_POOL_BASE_ADDR_MASK	0xfffff80
#घोषणा MVPP2_BM_POOL_SIZE_REG(pool)		(0x6040 + ((pool) * 4))
#घोषणा     MVPP2_BM_POOL_SIZE_MASK		0xfff0
#घोषणा MVPP2_BM_POOL_READ_PTR_REG(pool)	(0x6080 + ((pool) * 4))
#घोषणा     MVPP2_BM_POOL_GET_READ_PTR_MASK	0xfff0
#घोषणा MVPP2_BM_POOL_PTRS_NUM_REG(pool)	(0x60c0 + ((pool) * 4))
#घोषणा     MVPP2_BM_POOL_PTRS_NUM_MASK		0xfff0
#घोषणा MVPP2_BM_BPPI_READ_PTR_REG(pool)	(0x6100 + ((pool) * 4))
#घोषणा MVPP2_BM_BPPI_PTRS_NUM_REG(pool)	(0x6140 + ((pool) * 4))
#घोषणा     MVPP2_BM_BPPI_PTR_NUM_MASK		0x7ff
#घोषणा MVPP22_BM_POOL_PTRS_NUM_MASK		0xfff8
#घोषणा     MVPP2_BM_BPPI_PREFETCH_FULL_MASK	BIT(16)
#घोषणा MVPP2_BM_POOL_CTRL_REG(pool)		(0x6200 + ((pool) * 4))
#घोषणा     MVPP2_BM_START_MASK			BIT(0)
#घोषणा     MVPP2_BM_STOP_MASK			BIT(1)
#घोषणा     MVPP2_BM_STATE_MASK			BIT(4)
#घोषणा     MVPP2_BM_LOW_THRESH_OFFS		8
#घोषणा     MVPP2_BM_LOW_THRESH_MASK		0x7f00
#घोषणा     MVPP2_BM_LOW_THRESH_VALUE(val)	((val) << \
						MVPP2_BM_LOW_THRESH_OFFS)
#घोषणा     MVPP2_BM_HIGH_THRESH_OFFS		16
#घोषणा     MVPP2_BM_HIGH_THRESH_MASK		0x7f0000
#घोषणा     MVPP2_BM_HIGH_THRESH_VALUE(val)	((val) << \
						MVPP2_BM_HIGH_THRESH_OFFS)
#घोषणा     MVPP2_BM_BPPI_HIGH_THRESH		0x1E
#घोषणा     MVPP2_BM_BPPI_LOW_THRESH		0x1C
#घोषणा     MVPP23_BM_BPPI_HIGH_THRESH		0x34
#घोषणा     MVPP23_BM_BPPI_LOW_THRESH		0x28
#घोषणा MVPP2_BM_INTR_CAUSE_REG(pool)		(0x6240 + ((pool) * 4))
#घोषणा     MVPP2_BM_RELEASED_DELAY_MASK	BIT(0)
#घोषणा     MVPP2_BM_ALLOC_FAILED_MASK		BIT(1)
#घोषणा     MVPP2_BM_BPPE_EMPTY_MASK		BIT(2)
#घोषणा     MVPP2_BM_BPPE_FULL_MASK		BIT(3)
#घोषणा     MVPP2_BM_AVAILABLE_BP_LOW_MASK	BIT(4)
#घोषणा MVPP2_BM_INTR_MASK_REG(pool)		(0x6280 + ((pool) * 4))
#घोषणा MVPP2_BM_PHY_ALLOC_REG(pool)		(0x6400 + ((pool) * 4))
#घोषणा     MVPP2_BM_PHY_ALLOC_GRNTD_MASK	BIT(0)
#घोषणा MVPP2_BM_VIRT_ALLOC_REG			0x6440
#घोषणा MVPP22_BM_ADDR_HIGH_ALLOC		0x6444
#घोषणा     MVPP22_BM_ADDR_HIGH_PHYS_MASK	0xff
#घोषणा     MVPP22_BM_ADDR_HIGH_VIRT_MASK	0xff00
#घोषणा     MVPP22_BM_ADDR_HIGH_VIRT_SHIFT	8
#घोषणा MVPP2_BM_PHY_RLS_REG(pool)		(0x6480 + ((pool) * 4))
#घोषणा     MVPP2_BM_PHY_RLS_MC_BUFF_MASK	BIT(0)
#घोषणा     MVPP2_BM_PHY_RLS_PRIO_EN_MASK	BIT(1)
#घोषणा     MVPP2_BM_PHY_RLS_GRNTD_MASK		BIT(2)
#घोषणा MVPP2_BM_VIRT_RLS_REG			0x64c0
#घोषणा MVPP22_BM_ADDR_HIGH_RLS_REG		0x64c4
#घोषणा     MVPP22_BM_ADDR_HIGH_PHYS_RLS_MASK	0xff
#घोषणा     MVPP22_BM_ADDR_HIGH_VIRT_RLS_MASK	0xff00
#घोषणा     MVPP22_BM_ADDR_HIGH_VIRT_RLS_SHIFT	8

/* Packet Processor per-port counters */
#घोषणा MVPP2_OVERRUN_ETH_DROP			0x7000
#घोषणा MVPP2_CLS_ETH_DROP			0x7020

#घोषणा MVPP22_BM_POOL_BASE_ADDR_HIGH_REG	0x6310
#घोषणा     MVPP22_BM_POOL_BASE_ADDR_HIGH_MASK	0xff
#घोषणा     MVPP23_BM_8POOL_MODE		BIT(8)

/* Hit counters रेजिस्टरs */
#घोषणा MVPP2_CTRS_IDX				0x7040
#घोषणा     MVPP22_CTRS_TX_CTR(port, txq)	((txq) | ((port) << 3) | BIT(7))
#घोषणा MVPP2_TX_DESC_ENQ_CTR			0x7100
#घोषणा MVPP2_TX_DESC_ENQ_TO_DDR_CTR		0x7104
#घोषणा MVPP2_TX_BUFF_ENQ_TO_DDR_CTR		0x7108
#घोषणा MVPP2_TX_DESC_ENQ_HW_FWD_CTR		0x710c
#घोषणा MVPP2_RX_DESC_ENQ_CTR			0x7120
#घोषणा MVPP2_TX_PKTS_DEQ_CTR			0x7130
#घोषणा MVPP2_TX_PKTS_FULL_QUEUE_DROP_CTR	0x7200
#घोषणा MVPP2_TX_PKTS_EARLY_DROP_CTR		0x7204
#घोषणा MVPP2_TX_PKTS_BM_DROP_CTR		0x7208
#घोषणा MVPP2_TX_PKTS_BM_MC_DROP_CTR		0x720c
#घोषणा MVPP2_RX_PKTS_FULL_QUEUE_DROP_CTR	0x7220
#घोषणा MVPP2_RX_PKTS_EARLY_DROP_CTR		0x7224
#घोषणा MVPP2_RX_PKTS_BM_DROP_CTR		0x7228
#घोषणा MVPP2_CLS_DEC_TBL_HIT_CTR		0x7700
#घोषणा MVPP2_CLS_FLOW_TBL_HIT_CTR		0x7704

/* TX Scheduler रेजिस्टरs */
#घोषणा MVPP2_TXP_SCHED_PORT_INDEX_REG		0x8000
#घोषणा MVPP2_TXP_SCHED_Q_CMD_REG		0x8004
#घोषणा     MVPP2_TXP_SCHED_ENQ_MASK		0xff
#घोषणा     MVPP2_TXP_SCHED_DISQ_OFFSET		8
#घोषणा MVPP2_TXP_SCHED_CMD_1_REG		0x8010
#घोषणा MVPP2_TXP_SCHED_FIXED_PRIO_REG		0x8014
#घोषणा MVPP2_TXP_SCHED_PERIOD_REG		0x8018
#घोषणा MVPP2_TXP_SCHED_MTU_REG			0x801c
#घोषणा     MVPP2_TXP_MTU_MAX			0x7FFFF
#घोषणा MVPP2_TXP_SCHED_REFILL_REG		0x8020
#घोषणा     MVPP2_TXP_REFILL_TOKENS_ALL_MASK	0x7ffff
#घोषणा     MVPP2_TXP_REFILL_PERIOD_ALL_MASK	0x3ff00000
#घोषणा     MVPP2_TXP_REFILL_PERIOD_MASK(v)	((v) << 20)
#घोषणा MVPP2_TXP_SCHED_TOKEN_SIZE_REG		0x8024
#घोषणा     MVPP2_TXP_TOKEN_SIZE_MAX		0xffffffff
#घोषणा MVPP2_TXQ_SCHED_REFILL_REG(q)		(0x8040 + ((q) << 2))
#घोषणा     MVPP2_TXQ_REFILL_TOKENS_ALL_MASK	0x7ffff
#घोषणा     MVPP2_TXQ_REFILL_PERIOD_ALL_MASK	0x3ff00000
#घोषणा     MVPP2_TXQ_REFILL_PERIOD_MASK(v)	((v) << 20)
#घोषणा MVPP2_TXQ_SCHED_TOKEN_SIZE_REG(q)	(0x8060 + ((q) << 2))
#घोषणा     MVPP2_TXQ_TOKEN_SIZE_MAX		0x7fffffff
#घोषणा MVPP2_TXQ_SCHED_TOKEN_CNTR_REG(q)	(0x8080 + ((q) << 2))
#घोषणा     MVPP2_TXQ_TOKEN_CNTR_MAX		0xffffffff

/* TX general रेजिस्टरs */
#घोषणा MVPP2_TX_SNOOP_REG			0x8800
#घोषणा MVPP2_TX_PORT_FLUSH_REG			0x8810
#घोषणा     MVPP2_TX_PORT_FLUSH_MASK(port)	(1 << (port))

/* LMS रेजिस्टरs */
#घोषणा MVPP2_SRC_ADDR_MIDDLE			0x24
#घोषणा MVPP2_SRC_ADDR_HIGH			0x28
#घोषणा MVPP2_PHY_AN_CFG0_REG			0x34
#घोषणा     MVPP2_PHY_AN_STOP_SMI0_MASK		BIT(7)
#घोषणा MVPP2_MNG_EXTENDED_GLOBAL_CTRL_REG	0x305c
#घोषणा     MVPP2_EXT_GLOBAL_CTRL_DEFAULT	0x27

/* Per-port रेजिस्टरs */
#घोषणा MVPP2_GMAC_CTRL_0_REG			0x0
#घोषणा     MVPP2_GMAC_PORT_EN_MASK		BIT(0)
#घोषणा     MVPP2_GMAC_PORT_TYPE_MASK		BIT(1)
#घोषणा     MVPP2_GMAC_MAX_RX_SIZE_OFFS		2
#घोषणा     MVPP2_GMAC_MAX_RX_SIZE_MASK		0x7ffc
#घोषणा     MVPP2_GMAC_MIB_CNTR_EN_MASK		BIT(15)
#घोषणा MVPP2_GMAC_CTRL_1_REG			0x4
#घोषणा     MVPP2_GMAC_PERIODIC_XON_EN_MASK	BIT(1)
#घोषणा     MVPP2_GMAC_GMII_LB_EN_MASK		BIT(5)
#घोषणा     MVPP2_GMAC_PCS_LB_EN_BIT		6
#घोषणा     MVPP2_GMAC_PCS_LB_EN_MASK		BIT(6)
#घोषणा     MVPP2_GMAC_SA_LOW_OFFS		7
#घोषणा MVPP2_GMAC_CTRL_2_REG			0x8
#घोषणा     MVPP2_GMAC_INBAND_AN_MASK		BIT(0)
#घोषणा     MVPP2_GMAC_FLOW_CTRL_MASK		GENMASK(2, 1)
#घोषणा     MVPP2_GMAC_PCS_ENABLE_MASK		BIT(3)
#घोषणा     MVPP2_GMAC_INTERNAL_CLK_MASK	BIT(4)
#घोषणा     MVPP2_GMAC_DISABLE_PADDING		BIT(5)
#घोषणा     MVPP2_GMAC_PORT_RESET_MASK		BIT(6)
#घोषणा MVPP2_GMAC_AUTONEG_CONFIG		0xc
#घोषणा     MVPP2_GMAC_FORCE_LINK_DOWN		BIT(0)
#घोषणा     MVPP2_GMAC_FORCE_LINK_PASS		BIT(1)
#घोषणा     MVPP2_GMAC_IN_BAND_AUTONEG		BIT(2)
#घोषणा     MVPP2_GMAC_IN_BAND_AUTONEG_BYPASS	BIT(3)
#घोषणा     MVPP2_GMAC_IN_BAND_RESTART_AN	BIT(4)
#घोषणा     MVPP2_GMAC_CONFIG_MII_SPEED		BIT(5)
#घोषणा     MVPP2_GMAC_CONFIG_GMII_SPEED	BIT(6)
#घोषणा     MVPP2_GMAC_AN_SPEED_EN		BIT(7)
#घोषणा     MVPP2_GMAC_FC_ADV_EN		BIT(9)
#घोषणा     MVPP2_GMAC_FC_ADV_ASM_EN		BIT(10)
#घोषणा     MVPP2_GMAC_FLOW_CTRL_AUTONEG	BIT(11)
#घोषणा     MVPP2_GMAC_CONFIG_FULL_DUPLEX	BIT(12)
#घोषणा     MVPP2_GMAC_AN_DUPLEX_EN		BIT(13)
#घोषणा MVPP2_GMAC_STATUS0			0x10
#घोषणा     MVPP2_GMAC_STATUS0_LINK_UP		BIT(0)
#घोषणा     MVPP2_GMAC_STATUS0_GMII_SPEED	BIT(1)
#घोषणा     MVPP2_GMAC_STATUS0_MII_SPEED	BIT(2)
#घोषणा     MVPP2_GMAC_STATUS0_FULL_DUPLEX	BIT(3)
#घोषणा     MVPP2_GMAC_STATUS0_RX_PAUSE		BIT(4)
#घोषणा     MVPP2_GMAC_STATUS0_TX_PAUSE		BIT(5)
#घोषणा     MVPP2_GMAC_STATUS0_AN_COMPLETE	BIT(11)
#घोषणा MVPP2_GMAC_PORT_FIFO_CFG_1_REG		0x1c
#घोषणा     MVPP2_GMAC_TX_FIFO_MIN_TH_OFFS	6
#घोषणा     MVPP2_GMAC_TX_FIFO_MIN_TH_ALL_MASK	0x1fc0
#घोषणा     MVPP2_GMAC_TX_FIFO_MIN_TH_MASK(v)	(((v) << 6) & \
					MVPP2_GMAC_TX_FIFO_MIN_TH_ALL_MASK)
#घोषणा MVPP22_GMAC_INT_STAT			0x20
#घोषणा     MVPP22_GMAC_INT_STAT_LINK		BIT(1)
#घोषणा MVPP22_GMAC_INT_MASK			0x24
#घोषणा     MVPP22_GMAC_INT_MASK_LINK_STAT	BIT(1)
#घोषणा MVPP22_GMAC_CTRL_4_REG			0x90
#घोषणा     MVPP22_CTRL4_EXT_PIN_GMII_SEL	BIT(0)
#घोषणा     MVPP22_CTRL4_RX_FC_EN		BIT(3)
#घोषणा     MVPP22_CTRL4_TX_FC_EN		BIT(4)
#घोषणा     MVPP22_CTRL4_DP_CLK_SEL		BIT(5)
#घोषणा     MVPP22_CTRL4_SYNC_BYPASS_DIS	BIT(6)
#घोषणा     MVPP22_CTRL4_QSGMII_BYPASS_ACTIVE	BIT(7)
#घोषणा MVPP22_GMAC_INT_SUM_STAT		0xa0
#घोषणा	    MVPP22_GMAC_INT_SUM_STAT_INTERNAL	BIT(1)
#घोषणा	    MVPP22_GMAC_INT_SUM_STAT_PTP	BIT(2)
#घोषणा MVPP22_GMAC_INT_SUM_MASK		0xa4
#घोषणा     MVPP22_GMAC_INT_SUM_MASK_LINK_STAT	BIT(1)
#घोषणा	    MVPP22_GMAC_INT_SUM_MASK_PTP	BIT(2)

/* Per-port XGMAC रेजिस्टरs. PPv2.2 and PPv2.3, only क्रम GOP port 0,
 * relative to port->base.
 */
#घोषणा MVPP22_XLG_CTRL0_REG			0x100
#घोषणा     MVPP22_XLG_CTRL0_PORT_EN		BIT(0)
#घोषणा     MVPP22_XLG_CTRL0_MAC_RESET_DIS	BIT(1)
#घोषणा     MVPP22_XLG_CTRL0_FORCE_LINK_DOWN	BIT(2)
#घोषणा     MVPP22_XLG_CTRL0_FORCE_LINK_PASS	BIT(3)
#घोषणा     MVPP22_XLG_CTRL0_RX_FLOW_CTRL_EN	BIT(7)
#घोषणा     MVPP22_XLG_CTRL0_TX_FLOW_CTRL_EN	BIT(8)
#घोषणा     MVPP22_XLG_CTRL0_MIB_CNT_DIS	BIT(14)
#घोषणा MVPP22_XLG_CTRL1_REG			0x104
#घोषणा     MVPP22_XLG_CTRL1_FRAMESIZELIMIT_OFFS	0
#घोषणा     MVPP22_XLG_CTRL1_FRAMESIZELIMIT_MASK	0x1fff
#घोषणा MVPP22_XLG_STATUS			0x10c
#घोषणा     MVPP22_XLG_STATUS_LINK_UP		BIT(0)
#घोषणा MVPP22_XLG_INT_STAT			0x114
#घोषणा     MVPP22_XLG_INT_STAT_LINK		BIT(1)
#घोषणा MVPP22_XLG_INT_MASK			0x118
#घोषणा     MVPP22_XLG_INT_MASK_LINK		BIT(1)
#घोषणा MVPP22_XLG_CTRL3_REG			0x11c
#घोषणा     MVPP22_XLG_CTRL3_MACMODESELECT_MASK	(7 << 13)
#घोषणा     MVPP22_XLG_CTRL3_MACMODESELECT_GMAC	(0 << 13)
#घोषणा     MVPP22_XLG_CTRL3_MACMODESELECT_10G	(1 << 13)
#घोषणा MVPP22_XLG_EXT_INT_STAT			0x158
#घोषणा     MVPP22_XLG_EXT_INT_STAT_XLG		BIT(1)
#घोषणा     MVPP22_XLG_EXT_INT_STAT_PTP		BIT(7)
#घोषणा MVPP22_XLG_EXT_INT_MASK			0x15c
#घोषणा     MVPP22_XLG_EXT_INT_MASK_XLG		BIT(1)
#घोषणा     MVPP22_XLG_EXT_INT_MASK_GIG		BIT(2)
#घोषणा     MVPP22_XLG_EXT_INT_MASK_PTP		BIT(7)
#घोषणा MVPP22_XLG_CTRL4_REG			0x184
#घोषणा     MVPP22_XLG_CTRL4_FWD_FC		BIT(5)
#घोषणा     MVPP22_XLG_CTRL4_FWD_PFC		BIT(6)
#घोषणा     MVPP22_XLG_CTRL4_MACMODSELECT_GMAC	BIT(12)
#घोषणा     MVPP22_XLG_CTRL4_EN_IDLE_CHECK	BIT(14)

/* SMI रेजिस्टरs. PPv2.2 and PPv2.3, relative to priv->अगरace_base. */
#घोषणा MVPP22_SMI_MISC_CFG_REG			0x1204
#घोषणा     MVPP22_SMI_POLLING_EN		BIT(10)

/* TAI रेजिस्टरs, PPv2.2 only, relative to priv->अगरace_base */
#घोषणा MVPP22_TAI_INT_CAUSE			0x1400
#घोषणा MVPP22_TAI_INT_MASK			0x1404
#घोषणा MVPP22_TAI_CR0				0x1408
#घोषणा MVPP22_TAI_CR1				0x140c
#घोषणा MVPP22_TAI_TCFCR0			0x1410
#घोषणा MVPP22_TAI_TCFCR1			0x1414
#घोषणा MVPP22_TAI_TCFCR2			0x1418
#घोषणा MVPP22_TAI_FATWR			0x141c
#घोषणा MVPP22_TAI_TOD_STEP_न_अंकO_CR		0x1420
#घोषणा MVPP22_TAI_TOD_STEP_FRAC_HIGH		0x1424
#घोषणा MVPP22_TAI_TOD_STEP_FRAC_LOW		0x1428
#घोषणा MVPP22_TAI_TAPDC_HIGH			0x142c
#घोषणा MVPP22_TAI_TAPDC_LOW			0x1430
#घोषणा MVPP22_TAI_TGTOD_SEC_HIGH		0x1434
#घोषणा MVPP22_TAI_TGTOD_SEC_MED		0x1438
#घोषणा MVPP22_TAI_TGTOD_SEC_LOW		0x143c
#घोषणा MVPP22_TAI_TGTOD_न_अंकO_HIGH		0x1440
#घोषणा MVPP22_TAI_TGTOD_न_अंकO_LOW		0x1444
#घोषणा MVPP22_TAI_TGTOD_FRAC_HIGH		0x1448
#घोषणा MVPP22_TAI_TGTOD_FRAC_LOW		0x144c
#घोषणा MVPP22_TAI_TLV_SEC_HIGH			0x1450
#घोषणा MVPP22_TAI_TLV_SEC_MED			0x1454
#घोषणा MVPP22_TAI_TLV_SEC_LOW			0x1458
#घोषणा MVPP22_TAI_TLV_न_अंकO_HIGH		0x145c
#घोषणा MVPP22_TAI_TLV_न_अंकO_LOW			0x1460
#घोषणा MVPP22_TAI_TLV_FRAC_HIGH		0x1464
#घोषणा MVPP22_TAI_TLV_FRAC_LOW			0x1468
#घोषणा MVPP22_TAI_TCV0_SEC_HIGH		0x146c
#घोषणा MVPP22_TAI_TCV0_SEC_MED			0x1470
#घोषणा MVPP22_TAI_TCV0_SEC_LOW			0x1474
#घोषणा MVPP22_TAI_TCV0_न_अंकO_HIGH		0x1478
#घोषणा MVPP22_TAI_TCV0_न_अंकO_LOW		0x147c
#घोषणा MVPP22_TAI_TCV0_FRAC_HIGH		0x1480
#घोषणा MVPP22_TAI_TCV0_FRAC_LOW		0x1484
#घोषणा MVPP22_TAI_TCV1_SEC_HIGH		0x1488
#घोषणा MVPP22_TAI_TCV1_SEC_MED			0x148c
#घोषणा MVPP22_TAI_TCV1_SEC_LOW			0x1490
#घोषणा MVPP22_TAI_TCV1_न_अंकO_HIGH		0x1494
#घोषणा MVPP22_TAI_TCV1_न_अंकO_LOW		0x1498
#घोषणा MVPP22_TAI_TCV1_FRAC_HIGH		0x149c
#घोषणा MVPP22_TAI_TCV1_FRAC_LOW		0x14a0
#घोषणा MVPP22_TAI_TCSR				0x14a4
#घोषणा MVPP22_TAI_TUC_LSB			0x14a8
#घोषणा MVPP22_TAI_GFM_SEC_HIGH			0x14ac
#घोषणा MVPP22_TAI_GFM_SEC_MED			0x14b0
#घोषणा MVPP22_TAI_GFM_SEC_LOW			0x14b4
#घोषणा MVPP22_TAI_GFM_न_अंकO_HIGH		0x14b8
#घोषणा MVPP22_TAI_GFM_न_अंकO_LOW			0x14bc
#घोषणा MVPP22_TAI_GFM_FRAC_HIGH		0x14c0
#घोषणा MVPP22_TAI_GFM_FRAC_LOW			0x14c4
#घोषणा MVPP22_TAI_PCLK_DA_HIGH			0x14c8
#घोषणा MVPP22_TAI_PCLK_DA_LOW			0x14cc
#घोषणा MVPP22_TAI_CTCR				0x14d0
#घोषणा MVPP22_TAI_PCLK_CCC_HIGH		0x14d4
#घोषणा MVPP22_TAI_PCLK_CCC_LOW			0x14d8
#घोषणा MVPP22_TAI_DTC_HIGH			0x14dc
#घोषणा MVPP22_TAI_DTC_LOW			0x14e0
#घोषणा MVPP22_TAI_CCC_HIGH			0x14e4
#घोषणा MVPP22_TAI_CCC_LOW			0x14e8
#घोषणा MVPP22_TAI_ICICE			0x14f4
#घोषणा MVPP22_TAI_ICICC_LOW			0x14f8
#घोषणा MVPP22_TAI_TUC_MSB			0x14fc

#घोषणा MVPP22_GMAC_BASE(port)		(0x7000 + (port) * 0x1000 + 0xe00)

#घोषणा MVPP2_CAUSE_TXQ_SENT_DESC_ALL_MASK	0xff

/* Descriptor ring Macros */
#घोषणा MVPP2_QUEUE_NEXT_DESC(q, index) \
	(((index) < (q)->last_desc) ? ((index) + 1) : 0)

/* XPCS रेजिस्टरs.PPv2.2 and PPv2.3 */
#घोषणा MVPP22_MPCS_BASE(port)			(0x7000 + (port) * 0x1000)
#घोषणा MVPP22_MPCS_CTRL			0x14
#घोषणा     MVPP22_MPCS_CTRL_FWD_ERR_CONN	BIT(10)
#घोषणा MVPP22_MPCS_CLK_RESET			0x14c
#घोषणा     MAC_CLK_RESET_SD_TX			BIT(0)
#घोषणा     MAC_CLK_RESET_SD_RX			BIT(1)
#घोषणा     MAC_CLK_RESET_MAC			BIT(2)
#घोषणा     MVPP22_MPCS_CLK_RESET_DIV_RATIO(n)	((n) << 4)
#घोषणा     MVPP22_MPCS_CLK_RESET_DIV_SET	BIT(11)

/* FCA रेजिस्टरs. PPv2.2 and PPv2.3 */
#घोषणा MVPP22_FCA_BASE(port)			(0x7600 + (port) * 0x1000)
#घोषणा MVPP22_FCA_REG_SIZE			16
#घोषणा MVPP22_FCA_REG_MASK			0xFFFF
#घोषणा MVPP22_FCA_CONTROL_REG			0x0
#घोषणा MVPP22_FCA_ENABLE_PERIODIC		BIT(11)
#घोषणा MVPP22_PERIODIC_COUNTER_LSB_REG		(0x110)
#घोषणा MVPP22_PERIODIC_COUNTER_MSB_REG		(0x114)

/* XPCS रेजिस्टरs. PPv2.2 and PPv2.3 */
#घोषणा MVPP22_XPCS_BASE(port)			(0x7400 + (port) * 0x1000)
#घोषणा MVPP22_XPCS_CFG0			0x0
#घोषणा     MVPP22_XPCS_CFG0_RESET_DIS		BIT(0)
#घोषणा     MVPP22_XPCS_CFG0_PCS_MODE(n)	((n) << 3)
#घोषणा     MVPP22_XPCS_CFG0_ACTIVE_LANE(n)	((n) << 5)

/* PTP रेजिस्टरs. PPv2.2 only */
#घोषणा MVPP22_PTP_BASE(port)			(0x7800 + (port * 0x1000))
#घोषणा MVPP22_PTP_INT_CAUSE			0x00
#घोषणा     MVPP22_PTP_INT_CAUSE_QUEUE1		BIT(6)
#घोषणा     MVPP22_PTP_INT_CAUSE_QUEUE0		BIT(5)
#घोषणा MVPP22_PTP_INT_MASK			0x04
#घोषणा     MVPP22_PTP_INT_MASK_QUEUE1		BIT(6)
#घोषणा     MVPP22_PTP_INT_MASK_QUEUE0		BIT(5)
#घोषणा MVPP22_PTP_GCR				0x08
#घोषणा     MVPP22_PTP_GCR_RX_RESET		BIT(13)
#घोषणा     MVPP22_PTP_GCR_TX_RESET		BIT(1)
#घोषणा     MVPP22_PTP_GCR_TSU_ENABLE		BIT(0)
#घोषणा MVPP22_PTP_TX_Q0_R0			0x0c
#घोषणा MVPP22_PTP_TX_Q0_R1			0x10
#घोषणा MVPP22_PTP_TX_Q0_R2			0x14
#घोषणा MVPP22_PTP_TX_Q1_R0			0x18
#घोषणा MVPP22_PTP_TX_Q1_R1			0x1c
#घोषणा MVPP22_PTP_TX_Q1_R2			0x20
#घोषणा MVPP22_PTP_TPCR				0x24
#घोषणा MVPP22_PTP_V1PCR			0x28
#घोषणा MVPP22_PTP_V2PCR			0x2c
#घोषणा MVPP22_PTP_Y1731PCR			0x30
#घोषणा MVPP22_PTP_NTPTSPCR			0x34
#घोषणा MVPP22_PTP_NTPRXPCR			0x38
#घोषणा MVPP22_PTP_NTPTXPCR			0x3c
#घोषणा MVPP22_PTP_WAMPPCR			0x40
#घोषणा MVPP22_PTP_NAPCR			0x44
#घोषणा MVPP22_PTP_FAPCR			0x48
#घोषणा MVPP22_PTP_CAPCR			0x50
#घोषणा MVPP22_PTP_ATAPCR			0x54
#घोषणा MVPP22_PTP_ACTAPCR			0x58
#घोषणा MVPP22_PTP_CATAPCR			0x5c
#घोषणा MVPP22_PTP_CACTAPCR			0x60
#घोषणा MVPP22_PTP_AITAPCR			0x64
#घोषणा MVPP22_PTP_CAITAPCR			0x68
#घोषणा MVPP22_PTP_CITAPCR			0x6c
#घोषणा MVPP22_PTP_NTP_OFF_HIGH			0x70
#घोषणा MVPP22_PTP_NTP_OFF_LOW			0x74
#घोषणा MVPP22_PTP_TX_PIPE_STATUS_DELAY		0x78

/* System controller रेजिस्टरs. Accessed through a regmap. */
#घोषणा GENCONF_SOFT_RESET1				0x1108
#घोषणा     GENCONF_SOFT_RESET1_GOP			BIT(6)
#घोषणा GENCONF_PORT_CTRL0				0x1110
#घोषणा     GENCONF_PORT_CTRL0_BUS_WIDTH_SELECT		BIT(1)
#घोषणा     GENCONF_PORT_CTRL0_RX_DATA_SAMPLE		BIT(29)
#घोषणा     GENCONF_PORT_CTRL0_CLK_DIV_PHASE_CLR	BIT(31)
#घोषणा GENCONF_PORT_CTRL1				0x1114
#घोषणा     GENCONF_PORT_CTRL1_EN(p)			BIT(p)
#घोषणा     GENCONF_PORT_CTRL1_RESET(p)			(BIT(p) << 28)
#घोषणा GENCONF_CTRL0					0x1120
#घोषणा     GENCONF_CTRL0_PORT2_RGMII			BIT(0)
#घोषणा     GENCONF_CTRL0_PORT3_RGMII_MII		BIT(1)
#घोषणा     GENCONF_CTRL0_PORT3_RGMII			BIT(2)

/* Various स्थिरants */

/* Coalescing */
#घोषणा MVPP2_TXDONE_COAL_PKTS_THRESH	64
#घोषणा MVPP2_TXDONE_HRTIMER_PERIOD_NS	1000000UL
#घोषणा MVPP2_TXDONE_COAL_USEC		1000
#घोषणा MVPP2_RX_COAL_PKTS		32
#घोषणा MVPP2_RX_COAL_USEC		64

/* The two bytes Marvell header. Either contains a special value used
 * by Marvell चयनes when a specअगरic hardware mode is enabled (not
 * supported by this driver) or is filled स्वतःmatically by zeroes on
 * the RX side. Those two bytes being at the front of the Ethernet
 * header, they allow to have the IP header aligned on a 4 bytes
 * boundary स्वतःmatically: the hardware skips those two bytes on its
 * own.
 */
#घोषणा MVPP2_MH_SIZE			2
#घोषणा MVPP2_ETH_TYPE_LEN		2
#घोषणा MVPP2_PPPOE_HDR_SIZE		8
#घोषणा MVPP2_VLAN_TAG_LEN		4
#घोषणा MVPP2_VLAN_TAG_EDSA_LEN		8

/* Lbtd 802.3 type */
#घोषणा MVPP2_IP_LBDT_TYPE		0xfffa

#घोषणा MVPP2_TX_CSUM_MAX_SIZE		9800

/* Timeout स्थिरants */
#घोषणा MVPP2_TX_DISABLE_TIMEOUT_MSEC	1000
#घोषणा MVPP2_TX_PENDING_TIMEOUT_MSEC	1000

#घोषणा MVPP2_TX_MTU_MAX		0x7ffff

/* Maximum number of T-CONTs of PON port */
#घोषणा MVPP2_MAX_TCONT			16

/* Maximum number of supported ports */
#घोषणा MVPP2_MAX_PORTS			4

/* Loopback port index */
#घोषणा MVPP2_LOOPBACK_PORT_INDEX	3

/* Maximum number of TXQs used by single port */
#घोषणा MVPP2_MAX_TXQ			8

/* MVPP2_MAX_TSO_SEGS is the maximum number of fragments to allow in the GSO
 * skb. As we need a maxium of two descriptors per fragments (1 header, 1 data),
 * multiply this value by two to count the maximum number of skb descs needed.
 */
#घोषणा MVPP2_MAX_TSO_SEGS		300
#घोषणा MVPP2_MAX_SKB_DESCS		(MVPP2_MAX_TSO_SEGS * 2 + MAX_SKB_FRAGS)

/* Max number of RXQs per port */
#घोषणा MVPP2_PORT_MAX_RXQ		32

/* Max number of Rx descriptors */
#घोषणा MVPP2_MAX_RXD_MAX		2048
#घोषणा MVPP2_MAX_RXD_DFLT		1024

/* Max number of Tx descriptors */
#घोषणा MVPP2_MAX_TXD_MAX		2048
#घोषणा MVPP2_MAX_TXD_DFLT		1024

/* Amount of Tx descriptors that can be reserved at once by CPU */
#घोषणा MVPP2_CPU_DESC_CHUNK		64

/* Max number of Tx descriptors in each aggregated queue */
#घोषणा MVPP2_AGGR_TXQ_SIZE		256

/* Descriptor aligned size */
#घोषणा MVPP2_DESC_ALIGNED_SIZE		32

/* Descriptor alignment mask */
#घोषणा MVPP2_TX_DESC_ALIGN		(MVPP2_DESC_ALIGNED_SIZE - 1)

/* RX FIFO स्थिरants */
#घोषणा MVPP2_RX_FIFO_PORT_DATA_SIZE_44KB	0xb000
#घोषणा MVPP2_RX_FIFO_PORT_DATA_SIZE_32KB	0x8000
#घोषणा MVPP2_RX_FIFO_PORT_DATA_SIZE_8KB	0x2000
#घोषणा MVPP2_RX_FIFO_PORT_DATA_SIZE_4KB	0x1000
#घोषणा MVPP2_RX_FIFO_PORT_ATTR_SIZE(data_size)	((data_size) >> 6)
#घोषणा MVPP2_RX_FIFO_PORT_ATTR_SIZE_4KB	0x40
#घोषणा MVPP2_RX_FIFO_PORT_MIN_PKT		0x80

/* TX FIFO स्थिरants */
#घोषणा MVPP22_TX_FIFO_DATA_SIZE_18KB		18
#घोषणा MVPP22_TX_FIFO_DATA_SIZE_10KB		10
#घोषणा MVPP22_TX_FIFO_DATA_SIZE_1KB		1
#घोषणा MVPP2_TX_FIFO_THRESHOLD_MIN		256 /* Bytes */
#घोषणा MVPP2_TX_FIFO_THRESHOLD(kb)	\
		((kb) * 1024 - MVPP2_TX_FIFO_THRESHOLD_MIN)

/* RX FIFO threshold in 1KB granularity */
#घोषणा MVPP23_PORT0_FIFO_TRSH	(9 * 1024)
#घोषणा MVPP23_PORT1_FIFO_TRSH	(4 * 1024)
#घोषणा MVPP23_PORT2_FIFO_TRSH	(2 * 1024)

/* RX Flow Control Registers */
#घोषणा MVPP2_RX_FC_REG(port)		(0x150 + 4 * (port))
#घोषणा     MVPP2_RX_FC_EN		BIT(24)
#घोषणा     MVPP2_RX_FC_TRSH_OFFS	16
#घोषणा     MVPP2_RX_FC_TRSH_MASK	(0xFF << MVPP2_RX_FC_TRSH_OFFS)
#घोषणा     MVPP2_RX_FC_TRSH_UNIT	256

/* MSS Flow control */
#घोषणा MSS_FC_COM_REG			0
#घोषणा FLOW_CONTROL_ENABLE_BIT		BIT(0)
#घोषणा FLOW_CONTROL_UPDATE_COMMAND_BIT	BIT(31)
#घोषणा FC_QUANTA			0xFFFF
#घोषणा FC_CLK_DIVIDER			100

#घोषणा MSS_RXQ_TRESH_BASE		0x200
#घोषणा MSS_RXQ_TRESH_OFFS		4
#घोषणा MSS_RXQ_TRESH_REG(q, fq)	(MSS_RXQ_TRESH_BASE + (((q) + (fq)) \
					* MSS_RXQ_TRESH_OFFS))

#घोषणा MSS_BUF_POOL_BASE		0x40
#घोषणा MSS_BUF_POOL_OFFS		4
#घोषणा MSS_BUF_POOL_REG(id)		(MSS_BUF_POOL_BASE		\
					+ (id) * MSS_BUF_POOL_OFFS)

#घोषणा MSS_BUF_POOL_STOP_MASK		0xFFF
#घोषणा MSS_BUF_POOL_START_MASK		(0xFFF << MSS_BUF_POOL_START_OFFS)
#घोषणा MSS_BUF_POOL_START_OFFS		12
#घोषणा MSS_BUF_POOL_PORTS_MASK		(0xF << MSS_BUF_POOL_PORTS_OFFS)
#घोषणा MSS_BUF_POOL_PORTS_OFFS		24
#घोषणा MSS_BUF_POOL_PORT_OFFS(id)	(0x1 <<				\
					((id) + MSS_BUF_POOL_PORTS_OFFS))

#घोषणा MSS_RXQ_TRESH_START_MASK	0xFFFF
#घोषणा MSS_RXQ_TRESH_STOP_MASK		(0xFFFF << MSS_RXQ_TRESH_STOP_OFFS)
#घोषणा MSS_RXQ_TRESH_STOP_OFFS		16

#घोषणा MSS_RXQ_ASS_BASE	0x80
#घोषणा MSS_RXQ_ASS_OFFS	4
#घोषणा MSS_RXQ_ASS_PER_REG	4
#घोषणा MSS_RXQ_ASS_PER_OFFS	8
#घोषणा MSS_RXQ_ASS_PORTID_OFFS	0
#घोषणा MSS_RXQ_ASS_PORTID_MASK	0x3
#घोषणा MSS_RXQ_ASS_HOSTID_OFFS	2
#घोषणा MSS_RXQ_ASS_HOSTID_MASK	0x3F

#घोषणा MSS_RXQ_ASS_Q_BASE(q, fq) ((((q) + (fq)) % MSS_RXQ_ASS_PER_REG)	 \
				  * MSS_RXQ_ASS_PER_OFFS)
#घोषणा MSS_RXQ_ASS_PQ_BASE(q, fq) ((((q) + (fq)) / MSS_RXQ_ASS_PER_REG) \
				   * MSS_RXQ_ASS_OFFS)
#घोषणा MSS_RXQ_ASS_REG(q, fq) (MSS_RXQ_ASS_BASE + MSS_RXQ_ASS_PQ_BASE(q, fq))

#घोषणा MSS_THRESHOLD_STOP	768
#घोषणा MSS_THRESHOLD_START	1024
#घोषणा MSS_FC_MAX_TIMEOUT	5000

/* RX buffer स्थिरants */
#घोषणा MVPP2_SKB_SHINFO_SIZE \
	SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info))

#घोषणा MVPP2_RX_PKT_SIZE(mtu) \
	ALIGN((mtu) + MVPP2_MH_SIZE + MVPP2_VLAN_TAG_LEN + \
	      ETH_HLEN + ETH_FCS_LEN, cache_line_size())

#घोषणा MVPP2_RX_BUF_SIZE(pkt_size)	((pkt_size) + MVPP2_SKB_HEADROOM)
#घोषणा MVPP2_RX_TOTAL_SIZE(buf_size)	((buf_size) + MVPP2_SKB_SHINFO_SIZE)
#घोषणा MVPP2_RX_MAX_PKT_SIZE(total_size) \
	((total_size) - MVPP2_SKB_HEADROOM - MVPP2_SKB_SHINFO_SIZE)

#घोषणा MVPP2_MAX_RX_BUF_SIZE	(PAGE_SIZE - MVPP2_SKB_SHINFO_SIZE - MVPP2_SKB_HEADROOM)

#घोषणा MVPP2_BIT_TO_BYTE(bit)		((bit) / 8)
#घोषणा MVPP2_BIT_TO_WORD(bit)		((bit) / 32)
#घोषणा MVPP2_BIT_IN_WORD(bit)		((bit) % 32)

#घोषणा MVPP2_N_PRS_FLOWS		52
#घोषणा MVPP2_N_RFS_ENTRIES_PER_FLOW	4

/* There are 7 supported high-level flows */
#घोषणा MVPP2_N_RFS_RULES		(MVPP2_N_RFS_ENTRIES_PER_FLOW * 7)

/* RSS स्थिरants */
#घोषणा MVPP22_N_RSS_TABLES		8
#घोषणा MVPP22_RSS_TABLE_ENTRIES	32

/* IPv6 max L3 address size */
#घोषणा MVPP2_MAX_L3_ADDR_SIZE		16

/* Port flags */
#घोषणा MVPP2_F_LOOPBACK		BIT(0)
#घोषणा MVPP2_F_DT_COMPAT		BIT(1)

/* Marvell tag types */
क्रमागत mvpp2_tag_type अणु
	MVPP2_TAG_TYPE_NONE = 0,
	MVPP2_TAG_TYPE_MH   = 1,
	MVPP2_TAG_TYPE_DSA  = 2,
	MVPP2_TAG_TYPE_EDSA = 3,
	MVPP2_TAG_TYPE_VLAN = 4,
	MVPP2_TAG_TYPE_LAST = 5
पूर्ण;

/* L2 cast क्रमागत */
क्रमागत mvpp2_prs_l2_cast अणु
	MVPP2_PRS_L2_UNI_CAST,
	MVPP2_PRS_L2_MULTI_CAST,
पूर्ण;

/* L3 cast क्रमागत */
क्रमागत mvpp2_prs_l3_cast अणु
	MVPP2_PRS_L3_UNI_CAST,
	MVPP2_PRS_L3_MULTI_CAST,
	MVPP2_PRS_L3_BROAD_CAST
पूर्ण;

/* PTP descriptor स्थिरants. The low bits of the descriptor are stored
 * separately from the high bits.
 */
#घोषणा MVPP22_PTP_DESC_MASK_LOW	0xfff

/* PTPAction */
क्रमागत mvpp22_ptp_action अणु
	MVPP22_PTP_ACTION_NONE = 0,
	MVPP22_PTP_ACTION_FORWARD = 1,
	MVPP22_PTP_ACTION_CAPTURE = 3,
	/* The following have not been verअगरied */
	MVPP22_PTP_ACTION_ADDTIME = 4,
	MVPP22_PTP_ACTION_ADDCORRECTEDTIME = 5,
	MVPP22_PTP_ACTION_CAPTUREADDTIME = 6,
	MVPP22_PTP_ACTION_CAPTUREADDCORRECTEDTIME = 7,
	MVPP22_PTP_ACTION_ADDINGRESSTIME = 8,
	MVPP22_PTP_ACTION_CAPTUREADDINGRESSTIME = 9,
	MVPP22_PTP_ACTION_CAPTUREINGRESSTIME = 10,
पूर्ण;

/* PTPPacketFormat */
क्रमागत mvpp22_ptp_packet_क्रमmat अणु
	MVPP22_PTP_PKT_FMT_PTPV2 = 0,
	MVPP22_PTP_PKT_FMT_PTPV1 = 1,
	MVPP22_PTP_PKT_FMT_Y1731 = 2,
	MVPP22_PTP_PKT_FMT_NTPTS = 3,
	MVPP22_PTP_PKT_FMT_NTPRX = 4,
	MVPP22_PTP_PKT_FMT_NTPTX = 5,
	MVPP22_PTP_PKT_FMT_TWAMP = 6,
पूर्ण;

#घोषणा MVPP22_PTP_ACTION(x)		(((x) & 15) << 0)
#घोषणा MVPP22_PTP_PACKETFORMAT(x)	(((x) & 7) << 4)
#घोषणा MVPP22_PTP_MACTIMESTAMPINGEN	BIT(11)
#घोषणा MVPP22_PTP_TIMESTAMPENTRYID(x)	(((x) & 31) << 12)
#घोषणा MVPP22_PTP_TIMESTAMPQUEUESELECT	BIT(18)

/* BM स्थिरants */
#घोषणा MVPP2_BM_JUMBO_BUF_NUM		2048
#घोषणा MVPP2_BM_LONG_BUF_NUM		2048
#घोषणा MVPP2_BM_SHORT_BUF_NUM		2048
#घोषणा MVPP2_BM_POOL_SIZE_MAX		(16*1024 - MVPP2_BM_POOL_PTR_ALIGN/4)
#घोषणा MVPP2_BM_POOL_PTR_ALIGN		128
#घोषणा MVPP2_BM_MAX_POOLS		8

/* BM cookie (32 bits) definition */
#घोषणा MVPP2_BM_COOKIE_POOL_OFFS	8
#घोषणा MVPP2_BM_COOKIE_CPU_OFFS	24

#घोषणा MVPP2_BM_SHORT_FRAME_SIZE	704	/* frame size 128 */
#घोषणा MVPP2_BM_LONG_FRAME_SIZE	2240	/* frame size 1664 */
#घोषणा MVPP2_BM_JUMBO_FRAME_SIZE	10432	/* frame size 9856 */
/* BM लघु pool packet size
 * These value assure that क्रम SWF the total number
 * of bytes allocated क्रम each buffer will be 512
 */
#घोषणा MVPP2_BM_SHORT_PKT_SIZE	MVPP2_RX_MAX_PKT_SIZE(MVPP2_BM_SHORT_FRAME_SIZE)
#घोषणा MVPP2_BM_LONG_PKT_SIZE	MVPP2_RX_MAX_PKT_SIZE(MVPP2_BM_LONG_FRAME_SIZE)
#घोषणा MVPP2_BM_JUMBO_PKT_SIZE	MVPP2_RX_MAX_PKT_SIZE(MVPP2_BM_JUMBO_FRAME_SIZE)

#घोषणा MVPP21_ADDR_SPACE_SZ		0
#घोषणा MVPP22_ADDR_SPACE_SZ		SZ_64K

#घोषणा MVPP2_MAX_THREADS		9
#घोषणा MVPP2_MAX_QVECS			MVPP2_MAX_THREADS

/* GMAC MIB Counters रेजिस्टर definitions */
#घोषणा MVPP21_MIB_COUNTERS_OFFSET		0x1000
#घोषणा MVPP21_MIB_COUNTERS_PORT_SZ		0x400
#घोषणा MVPP22_MIB_COUNTERS_OFFSET		0x0
#घोषणा MVPP22_MIB_COUNTERS_PORT_SZ		0x100

#घोषणा MVPP2_MIB_GOOD_OCTETS_RCVD		0x0
#घोषणा MVPP2_MIB_BAD_OCTETS_RCVD		0x8
#घोषणा MVPP2_MIB_CRC_ERRORS_SENT		0xc
#घोषणा MVPP2_MIB_UNICAST_FRAMES_RCVD		0x10
#घोषणा MVPP2_MIB_BROADCAST_FRAMES_RCVD		0x18
#घोषणा MVPP2_MIB_MULTICAST_FRAMES_RCVD		0x1c
#घोषणा MVPP2_MIB_FRAMES_64_OCTETS		0x20
#घोषणा MVPP2_MIB_FRAMES_65_TO_127_OCTETS	0x24
#घोषणा MVPP2_MIB_FRAMES_128_TO_255_OCTETS	0x28
#घोषणा MVPP2_MIB_FRAMES_256_TO_511_OCTETS	0x2c
#घोषणा MVPP2_MIB_FRAMES_512_TO_1023_OCTETS	0x30
#घोषणा MVPP2_MIB_FRAMES_1024_TO_MAX_OCTETS	0x34
#घोषणा MVPP2_MIB_GOOD_OCTETS_SENT		0x38
#घोषणा MVPP2_MIB_UNICAST_FRAMES_SENT		0x40
#घोषणा MVPP2_MIB_MULTICAST_FRAMES_SENT		0x48
#घोषणा MVPP2_MIB_BROADCAST_FRAMES_SENT		0x4c
#घोषणा MVPP2_MIB_FC_SENT			0x54
#घोषणा MVPP2_MIB_FC_RCVD			0x58
#घोषणा MVPP2_MIB_RX_FIFO_OVERRUN		0x5c
#घोषणा MVPP2_MIB_UNDERSIZE_RCVD		0x60
#घोषणा MVPP2_MIB_FRAGMENTS_RCVD		0x64
#घोषणा MVPP2_MIB_OVERSIZE_RCVD			0x68
#घोषणा MVPP2_MIB_JABBER_RCVD			0x6c
#घोषणा MVPP2_MIB_MAC_RCV_ERROR			0x70
#घोषणा MVPP2_MIB_BAD_CRC_EVENT			0x74
#घोषणा MVPP2_MIB_COLLISION			0x78
#घोषणा MVPP2_MIB_LATE_COLLISION		0x7c

#घोषणा MVPP2_MIB_COUNTERS_STATS_DELAY		(1 * HZ)

#घोषणा MVPP2_DESC_DMA_MASK	DMA_BIT_MASK(40)

/* Buffer header info bits */
#घोषणा MVPP2_B_HDR_INFO_MC_ID_MASK	0xfff
#घोषणा MVPP2_B_HDR_INFO_MC_ID(info)	((info) & MVPP2_B_HDR_INFO_MC_ID_MASK)
#घोषणा MVPP2_B_HDR_INFO_LAST_OFFS	12
#घोषणा MVPP2_B_HDR_INFO_LAST_MASK	BIT(12)
#घोषणा MVPP2_B_HDR_INFO_IS_LAST(info) \
	   (((info) & MVPP2_B_HDR_INFO_LAST_MASK) >> MVPP2_B_HDR_INFO_LAST_OFFS)

काष्ठा mvpp2_tai;

/* Definitions */
काष्ठा mvpp2_dbgfs_entries;

काष्ठा mvpp2_rss_table अणु
	u32 indir[MVPP22_RSS_TABLE_ENTRIES];
पूर्ण;

काष्ठा mvpp2_buff_hdr अणु
	__le32 next_phys_addr;
	__le32 next_dma_addr;
	__le16 byte_count;
	__le16 info;
	__le16 reserved1;	/* bm_qset (क्रम future use, BM) */
	u8 next_phys_addr_high;
	u8 next_dma_addr_high;
	__le16 reserved2;
	__le16 reserved3;
	__le16 reserved4;
	__le16 reserved5;
पूर्ण;

/* Shared Packet Processor resources */
काष्ठा mvpp2 अणु
	/* Shared रेजिस्टरs' base addresses */
	व्योम __iomem *lms_base;
	व्योम __iomem *अगरace_base;
	व्योम __iomem *cm3_base;

	/* On PPv2.2 and PPv2.3, each "software thread" can access the base
	 * रेजिस्टर through a separate address space, each 64 KB apart
	 * from each other. Typically, such address spaces will be
	 * used per CPU.
	 */
	व्योम __iomem *swth_base[MVPP2_MAX_THREADS];

	/* On PPv2.2 and PPv2.3, some port control रेजिस्टरs are located पूर्णांकo
	 * the प्रणाली controller space. These रेजिस्टरs are accessible
	 * through a regmap.
	 */
	काष्ठा regmap *sysctrl_base;

	/* Common घड़ीs */
	काष्ठा clk *pp_clk;
	काष्ठा clk *gop_clk;
	काष्ठा clk *mg_clk;
	काष्ठा clk *mg_core_clk;
	काष्ठा clk *axi_clk;

	/* List of poपूर्णांकers to port काष्ठाures */
	पूर्णांक port_count;
	काष्ठा mvpp2_port *port_list[MVPP2_MAX_PORTS];
	/* Map of enabled ports */
	अचिन्हित दीर्घ port_map;

	काष्ठा mvpp2_tai *tai;

	/* Number of Tx thपढ़ोs used */
	अचिन्हित पूर्णांक nthपढ़ोs;
	/* Map of thपढ़ोs needing locking */
	अचिन्हित दीर्घ lock_map;

	/* Aggregated TXQs */
	काष्ठा mvpp2_tx_queue *aggr_txqs;

	/* Are we using page_pool with per-cpu pools? */
	पूर्णांक percpu_pools;

	/* BM pools */
	काष्ठा mvpp2_bm_pool *bm_pools;

	/* PRS shaकरोw table */
	काष्ठा mvpp2_prs_shaकरोw *prs_shaकरोw;
	/* PRS auxiliary table क्रम द्विगुन vlan entries control */
	bool *prs_द्विगुन_vlans;

	/* Tclk value */
	u32 tclk;

	/* HW version */
	क्रमागत अणु MVPP21, MVPP22, MVPP23 पूर्ण hw_version;

	/* Maximum number of RXQs per port */
	अचिन्हित पूर्णांक max_port_rxqs;

	/* Workqueue to gather hardware statistics */
	अक्षर queue_name[30];
	काष्ठा workqueue_काष्ठा *stats_queue;

	/* Debugfs root entry */
	काष्ठा dentry *dbgfs_dir;

	/* Debugfs entries निजी data */
	काष्ठा mvpp2_dbgfs_entries *dbgfs_entries;

	/* RSS Indirection tables */
	काष्ठा mvpp2_rss_table *rss_tables[MVPP22_N_RSS_TABLES];

	/* page_pool allocator */
	काष्ठा page_pool *page_pool[MVPP2_PORT_MAX_RXQ];

	/* Global TX Flow Control config */
	bool global_tx_fc;

	/* Spinlocks क्रम CM3 shared memory configuration */
	spinlock_t mss_spinlock;
पूर्ण;

काष्ठा mvpp2_pcpu_stats अणु
	काष्ठा	u64_stats_sync syncp;
	u64	rx_packets;
	u64	rx_bytes;
	u64	tx_packets;
	u64	tx_bytes;
	/* XDP */
	u64	xdp_redirect;
	u64	xdp_pass;
	u64	xdp_drop;
	u64	xdp_xmit;
	u64	xdp_xmit_err;
	u64	xdp_tx;
	u64	xdp_tx_err;
पूर्ण;

/* Per-CPU port control */
काष्ठा mvpp2_port_pcpu अणु
	काष्ठा hrसमयr tx_करोne_समयr;
	काष्ठा net_device *dev;
	bool समयr_scheduled;
पूर्ण;

काष्ठा mvpp2_queue_vector अणु
	पूर्णांक irq;
	काष्ठा napi_काष्ठा napi;
	क्रमागत अणु MVPP2_QUEUE_VECTOR_SHARED, MVPP2_QUEUE_VECTOR_PRIVATE पूर्ण type;
	पूर्णांक sw_thपढ़ो_id;
	u16 sw_thपढ़ो_mask;
	पूर्णांक first_rxq;
	पूर्णांक nrxqs;
	u32 pending_cause_rx;
	काष्ठा mvpp2_port *port;
	काष्ठा cpumask *mask;
पूर्ण;

/* Internal represention of a Flow Steering rule */
काष्ठा mvpp2_rfs_rule अणु
	/* Rule location inside the flow*/
	पूर्णांक loc;

	/* Flow type, such as TCP_V4_FLOW, IP6_FLOW, etc. */
	पूर्णांक flow_type;

	/* Index of the C2 TCAM entry handling this rule */
	पूर्णांक c2_index;

	/* Header fields that needs to be extracted to match this flow */
	u16 hek_fields;

	/* CLS engine : only c2 is supported क्रम now. */
	u8 engine;

	/* TCAM key and mask क्रम C2-based steering. These fields should be
	 * encapsulated in a जोड़ should we add more engines.
	 */
	u64 c2_tcam;
	u64 c2_tcam_mask;

	काष्ठा flow_rule *flow;
पूर्ण;

काष्ठा mvpp2_ethtool_fs अणु
	काष्ठा mvpp2_rfs_rule rule;
	काष्ठा ethtool_rxnfc rxnfc;
पूर्ण;

काष्ठा mvpp2_hwtstamp_queue अणु
	काष्ठा sk_buff *skb[32];
	u8 next;
पूर्ण;

काष्ठा mvpp2_port अणु
	u8 id;

	/* Index of the port from the "group of ports" complex poपूर्णांक
	 * of view. This is specअगरic to PPv2.2.
	 */
	पूर्णांक gop_id;

	पूर्णांक port_irq;

	काष्ठा mvpp2 *priv;

	/* Firmware node associated to the port */
	काष्ठा fwnode_handle *fwnode;

	/* Is a PHY always connected to the port */
	bool has_phy;

	/* Per-port रेजिस्टरs' base address */
	व्योम __iomem *base;
	व्योम __iomem *stats_base;

	काष्ठा mvpp2_rx_queue **rxqs;
	अचिन्हित पूर्णांक nrxqs;
	काष्ठा mvpp2_tx_queue **txqs;
	अचिन्हित पूर्णांक ntxqs;
	काष्ठा net_device *dev;

	काष्ठा bpf_prog *xdp_prog;

	पूर्णांक pkt_size;

	/* Per-CPU port control */
	काष्ठा mvpp2_port_pcpu __percpu *pcpu;

	/* Protect the BM refills and the Tx paths when a thपढ़ो is used on more
	 * than a single CPU.
	 */
	spinlock_t bm_lock[MVPP2_MAX_THREADS];
	spinlock_t tx_lock[MVPP2_MAX_THREADS];

	/* Flags */
	अचिन्हित दीर्घ flags;

	u16 tx_ring_size;
	u16 rx_ring_size;
	काष्ठा mvpp2_pcpu_stats __percpu *stats;
	u64 *ethtool_stats;

	अचिन्हित दीर्घ state;

	/* Per-port work and its lock to gather hardware statistics */
	काष्ठा mutex gather_stats_lock;
	काष्ठा delayed_work stats_work;

	काष्ठा device_node *of_node;

	phy_पूर्णांकerface_t phy_पूर्णांकerface;
	काष्ठा phylink *phylink;
	काष्ठा phylink_config phylink_config;
	काष्ठा phylink_pcs phylink_pcs;
	काष्ठा phy *comphy;

	काष्ठा mvpp2_bm_pool *pool_दीर्घ;
	काष्ठा mvpp2_bm_pool *pool_लघु;

	/* Index of first port's physical RXQ */
	u8 first_rxq;

	काष्ठा mvpp2_queue_vector qvecs[MVPP2_MAX_QVECS];
	अचिन्हित पूर्णांक nqvecs;
	bool has_tx_irqs;

	u32 tx_समय_coal;

	/* List of steering rules active on that port */
	काष्ठा mvpp2_ethtool_fs *rfs_rules[MVPP2_N_RFS_ENTRIES_PER_FLOW];
	पूर्णांक n_rfs_rules;

	/* Each port has its own view of the rss contexts, so that it can number
	 * them from 0
	 */
	पूर्णांक rss_ctx[MVPP22_N_RSS_TABLES];

	bool hwtstamp;
	bool rx_hwtstamp;
	क्रमागत hwtstamp_tx_types tx_hwtstamp_type;
	काष्ठा mvpp2_hwtstamp_queue tx_hwtstamp_queue[2];

	/* Firmware TX flow control */
	bool tx_fc;
पूर्ण;

/* The mvpp2_tx_desc and mvpp2_rx_desc काष्ठाures describe the
 * layout of the transmit and reception DMA descriptors, and their
 * layout is thereक्रमe defined by the hardware design
 */

#घोषणा MVPP2_TXD_L3_OFF_SHIFT		0
#घोषणा MVPP2_TXD_IP_HLEN_SHIFT		8
#घोषणा MVPP2_TXD_L4_CSUM_FRAG		BIT(13)
#घोषणा MVPP2_TXD_L4_CSUM_NOT		BIT(14)
#घोषणा MVPP2_TXD_IP_CSUM_DISABLE	BIT(15)
#घोषणा MVPP2_TXD_PADDING_DISABLE	BIT(23)
#घोषणा MVPP2_TXD_L4_UDP		BIT(24)
#घोषणा MVPP2_TXD_L3_IP6		BIT(26)
#घोषणा MVPP2_TXD_L_DESC		BIT(28)
#घोषणा MVPP2_TXD_F_DESC		BIT(29)

#घोषणा MVPP2_RXD_ERR_SUMMARY		BIT(15)
#घोषणा MVPP2_RXD_ERR_CODE_MASK		(BIT(13) | BIT(14))
#घोषणा MVPP2_RXD_ERR_CRC		0x0
#घोषणा MVPP2_RXD_ERR_OVERRUN		BIT(13)
#घोषणा MVPP2_RXD_ERR_RESOURCE		(BIT(13) | BIT(14))
#घोषणा MVPP2_RXD_BM_POOL_ID_OFFS	16
#घोषणा MVPP2_RXD_BM_POOL_ID_MASK	(BIT(16) | BIT(17) | BIT(18))
#घोषणा MVPP2_RXD_HWF_SYNC		BIT(21)
#घोषणा MVPP2_RXD_L4_CSUM_OK		BIT(22)
#घोषणा MVPP2_RXD_IP4_HEADER_ERR	BIT(24)
#घोषणा MVPP2_RXD_L4_TCP		BIT(25)
#घोषणा MVPP2_RXD_L4_UDP		BIT(26)
#घोषणा MVPP2_RXD_L3_IP4		BIT(28)
#घोषणा MVPP2_RXD_L3_IP6		BIT(30)
#घोषणा MVPP2_RXD_BUF_HDR		BIT(31)

/* HW TX descriptor क्रम PPv2.1 */
काष्ठा mvpp21_tx_desc अणु
	__le32 command;		/* Options used by HW क्रम packet transmitting.*/
	u8  packet_offset;	/* the offset from the buffer beginning	*/
	u8  phys_txq;		/* destination queue ID			*/
	__le16 data_size;	/* data size of transmitted packet in bytes */
	__le32 buf_dma_addr;	/* physical addr of transmitted buffer	*/
	__le32 buf_cookie;	/* cookie क्रम access to TX buffer in tx path */
	__le32 reserved1[3];	/* hw_cmd (क्रम future use, BM, PON, PNC) */
	__le32 reserved2;	/* reserved (क्रम future use)		*/
पूर्ण;

/* HW RX descriptor क्रम PPv2.1 */
काष्ठा mvpp21_rx_desc अणु
	__le32 status;		/* info about received packet		*/
	__le16 reserved1;	/* parser_info (क्रम future use, PnC)	*/
	__le16 data_size;	/* size of received packet in bytes	*/
	__le32 buf_dma_addr;	/* physical address of the buffer	*/
	__le32 buf_cookie;	/* cookie क्रम access to RX buffer in rx path */
	__le16 reserved2;	/* gem_port_id (क्रम future use, PON)	*/
	__le16 reserved3;	/* csum_l4 (क्रम future use, PnC)	*/
	u8  reserved4;		/* bm_qset (क्रम future use, BM)		*/
	u8  reserved5;
	__le16 reserved6;	/* classअगरy_info (क्रम future use, PnC)	*/
	__le32 reserved7;	/* flow_id (क्रम future use, PnC) */
	__le32 reserved8;
पूर्ण;

/* HW TX descriptor क्रम PPv2.2 and PPv2.3 */
काष्ठा mvpp22_tx_desc अणु
	__le32 command;
	u8  packet_offset;
	u8  phys_txq;
	__le16 data_size;
	__le32 ptp_descriptor;
	__le32 reserved2;
	__le64 buf_dma_addr_ptp;
	__le64 buf_cookie_misc;
पूर्ण;

/* HW RX descriptor क्रम PPv2.2 and PPv2.3 */
काष्ठा mvpp22_rx_desc अणु
	__le32 status;
	__le16 reserved1;
	__le16 data_size;
	__le32 reserved2;
	__le32 बारtamp;
	__le64 buf_dma_addr_key_hash;
	__le64 buf_cookie_misc;
पूर्ण;

/* Opaque type used by the driver to manipulate the HW TX and RX
 * descriptors
 */
काष्ठा mvpp2_tx_desc अणु
	जोड़ अणु
		काष्ठा mvpp21_tx_desc pp21;
		काष्ठा mvpp22_tx_desc pp22;
	पूर्ण;
पूर्ण;

काष्ठा mvpp2_rx_desc अणु
	जोड़ अणु
		काष्ठा mvpp21_rx_desc pp21;
		काष्ठा mvpp22_rx_desc pp22;
	पूर्ण;
पूर्ण;

क्रमागत mvpp2_tx_buf_type अणु
	MVPP2_TYPE_SKB,
	MVPP2_TYPE_XDP_TX,
	MVPP2_TYPE_XDP_NDO,
पूर्ण;

काष्ठा mvpp2_txq_pcpu_buf अणु
	क्रमागत mvpp2_tx_buf_type type;

	/* Transmitted SKB */
	जोड़ अणु
		काष्ठा xdp_frame *xdpf;
		काष्ठा sk_buff *skb;
	पूर्ण;

	/* Physical address of transmitted buffer */
	dma_addr_t dma;

	/* Size transmitted */
	माप_प्रकार size;
पूर्ण;

/* Per-CPU Tx queue control */
काष्ठा mvpp2_txq_pcpu अणु
	अचिन्हित पूर्णांक thपढ़ो;

	/* Number of Tx DMA descriptors in the descriptor ring */
	पूर्णांक size;

	/* Number of currently used Tx DMA descriptor in the
	 * descriptor ring
	 */
	पूर्णांक count;

	पूर्णांक wake_threshold;
	पूर्णांक stop_threshold;

	/* Number of Tx DMA descriptors reserved क्रम each CPU */
	पूर्णांक reserved_num;

	/* Infos about transmitted buffers */
	काष्ठा mvpp2_txq_pcpu_buf *buffs;

	/* Index of last TX DMA descriptor that was inserted */
	पूर्णांक txq_put_index;

	/* Index of the TX DMA descriptor to be cleaned up */
	पूर्णांक txq_get_index;

	/* DMA buffer क्रम TSO headers */
	अक्षर *tso_headers;
	dma_addr_t tso_headers_dma;
पूर्ण;

काष्ठा mvpp2_tx_queue अणु
	/* Physical number of this Tx queue */
	u8 id;

	/* Logical number of this Tx queue */
	u8 log_id;

	/* Number of Tx DMA descriptors in the descriptor ring */
	पूर्णांक size;

	/* Number of currently used Tx DMA descriptor in the descriptor ring */
	पूर्णांक count;

	/* Per-CPU control of physical Tx queues */
	काष्ठा mvpp2_txq_pcpu __percpu *pcpu;

	u32 करोne_pkts_coal;

	/* Virtual address of thex Tx DMA descriptors array */
	काष्ठा mvpp2_tx_desc *descs;

	/* DMA address of the Tx DMA descriptors array */
	dma_addr_t descs_dma;

	/* Index of the last Tx DMA descriptor */
	पूर्णांक last_desc;

	/* Index of the next Tx DMA descriptor to process */
	पूर्णांक next_desc_to_proc;
पूर्ण;

काष्ठा mvpp2_rx_queue अणु
	/* RX queue number, in the range 0-31 क्रम physical RXQs */
	u8 id;

	/* Num of rx descriptors in the rx descriptor ring */
	पूर्णांक size;

	u32 pkts_coal;
	u32 समय_coal;

	/* Virtual address of the RX DMA descriptors array */
	काष्ठा mvpp2_rx_desc *descs;

	/* DMA address of the RX DMA descriptors array */
	dma_addr_t descs_dma;

	/* Index of the last RX DMA descriptor */
	पूर्णांक last_desc;

	/* Index of the next RX DMA descriptor to process */
	पूर्णांक next_desc_to_proc;

	/* ID of port to which physical RXQ is mapped */
	पूर्णांक port;

	/* Port's logic RXQ number to which physical RXQ is mapped */
	पूर्णांक logic_rxq;

	/* XDP memory accounting */
	काष्ठा xdp_rxq_info xdp_rxq_लघु;
	काष्ठा xdp_rxq_info xdp_rxq_दीर्घ;
पूर्ण;

काष्ठा mvpp2_bm_pool अणु
	/* Pool number in the range 0-7 */
	पूर्णांक id;

	/* Buffer Poपूर्णांकers Pool External (BPPE) size */
	पूर्णांक size;
	/* BPPE size in bytes */
	पूर्णांक size_bytes;
	/* Number of buffers क्रम this pool */
	पूर्णांक buf_num;
	/* Pool buffer size */
	पूर्णांक buf_size;
	/* Packet size */
	पूर्णांक pkt_size;
	पूर्णांक frag_size;

	/* BPPE भव base address */
	u32 *virt_addr;
	/* BPPE DMA base address */
	dma_addr_t dma_addr;

	/* Ports using BM pool */
	u32 port_map;
पूर्ण;

#घोषणा IS_TSO_HEADER(txq_pcpu, addr) \
	((addr) >= (txq_pcpu)->tso_headers_dma && \
	 (addr) < (txq_pcpu)->tso_headers_dma + \
	 (txq_pcpu)->size * TSO_HEADER_SIZE)

#घोषणा MVPP2_DRIVER_NAME "mvpp2"
#घोषणा MVPP2_DRIVER_VERSION "1.0"

व्योम mvpp2_ग_लिखो(काष्ठा mvpp2 *priv, u32 offset, u32 data);
u32 mvpp2_पढ़ो(काष्ठा mvpp2 *priv, u32 offset);

व्योम mvpp2_dbgfs_init(काष्ठा mvpp2 *priv, स्थिर अक्षर *name);

व्योम mvpp2_dbgfs_cleanup(काष्ठा mvpp2 *priv);

व्योम mvpp23_rx_fअगरo_fc_en(काष्ठा mvpp2 *priv, पूर्णांक port, bool en);

#अगर_घोषित CONFIG_MVPP2_PTP
पूर्णांक mvpp22_tai_probe(काष्ठा device *dev, काष्ठा mvpp2 *priv);
व्योम mvpp22_tai_tstamp(काष्ठा mvpp2_tai *tai, u32 tstamp,
		       काष्ठा skb_shared_hwtstamps *hwtstamp);
व्योम mvpp22_tai_start(काष्ठा mvpp2_tai *tai);
व्योम mvpp22_tai_stop(काष्ठा mvpp2_tai *tai);
पूर्णांक mvpp22_tai_ptp_घड़ी_index(काष्ठा mvpp2_tai *tai);
#अन्यथा
अटल अंतरभूत पूर्णांक mvpp22_tai_probe(काष्ठा device *dev, काष्ठा mvpp2 *priv)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम mvpp22_tai_tstamp(काष्ठा mvpp2_tai *tai, u32 tstamp,
				     काष्ठा skb_shared_hwtstamps *hwtstamp)
अणु
पूर्ण
अटल अंतरभूत व्योम mvpp22_tai_start(काष्ठा mvpp2_tai *tai)
अणु
पूर्ण
अटल अंतरभूत व्योम mvpp22_tai_stop(काष्ठा mvpp2_tai *tai)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक mvpp22_tai_ptp_घड़ी_index(काष्ठा mvpp2_tai *tai)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool mvpp22_rx_hwtstamping(काष्ठा mvpp2_port *port)
अणु
	वापस IS_ENABLED(CONFIG_MVPP2_PTP) && port->rx_hwtstamp;
पूर्ण

#पूर्ण_अगर
