<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *   Copyright (C) 2009-2016 John Crispin <blogic@खोलोwrt.org>
 *   Copyright (C) 2009-2016 Felix Fietkau <nbd@खोलोwrt.org>
 *   Copyright (C) 2013-2016 Michael Lee <igvtee@gmail.com>
 */

#अगर_अघोषित MTK_ETH_H
#घोषणा MTK_ETH_H

#समावेश <linux/dma-mapping.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of_net.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश <linux/refcount.h>
#समावेश <linux/phylink.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/dim.h>
#समावेश "mtk_ppe.h"

#घोषणा MTK_QDMA_PAGE_SIZE	2048
#घोषणा MTK_MAX_RX_LENGTH	1536
#घोषणा MTK_MAX_RX_LENGTH_2K	2048
#घोषणा MTK_TX_DMA_BUF_LEN	0x3fff
#घोषणा MTK_DMA_SIZE		512
#घोषणा MTK_NAPI_WEIGHT		64
#घोषणा MTK_MAC_COUNT		2
#घोषणा MTK_RX_ETH_HLEN		(ETH_HLEN + ETH_FCS_LEN)
#घोषणा MTK_RX_HLEN		(NET_SKB_PAD + MTK_RX_ETH_HLEN + NET_IP_ALIGN)
#घोषणा MTK_DMA_DUMMY_DESC	0xffffffff
#घोषणा MTK_DEFAULT_MSG_ENABLE	(NETIF_MSG_DRV | \
				 NETIF_MSG_PROBE | \
				 NETIF_MSG_LINK | \
				 NETIF_MSG_TIMER | \
				 NETIF_MSG_IFDOWN | \
				 NETIF_MSG_IFUP | \
				 NETIF_MSG_RX_ERR | \
				 NETIF_MSG_TX_ERR)
#घोषणा MTK_HW_FEATURES		(NETIF_F_IP_CSUM | \
				 NETIF_F_RXCSUM | \
				 NETIF_F_HW_VLAN_CTAG_TX | \
				 NETIF_F_HW_VLAN_CTAG_RX | \
				 NETIF_F_SG | NETIF_F_TSO | \
				 NETIF_F_TSO6 | \
				 NETIF_F_IPV6_CSUM |\
				 NETIF_F_HW_TC)
#घोषणा MTK_HW_FEATURES_MT7628	(NETIF_F_SG | NETIF_F_RXCSUM)
#घोषणा NEXT_DESP_IDX(X, Y)	(((X) + 1) & ((Y) - 1))

#घोषणा MTK_MAX_RX_RING_NUM	4
#घोषणा MTK_HW_LRO_DMA_SIZE	8

#घोषणा	MTK_MAX_LRO_RX_LENGTH		(4096 * 3)
#घोषणा	MTK_MAX_LRO_IP_CNT		2
#घोषणा	MTK_HW_LRO_TIMER_UNIT		1	/* 20 us */
#घोषणा	MTK_HW_LRO_REFRESH_TIME		50000	/* 1 sec. */
#घोषणा	MTK_HW_LRO_AGG_TIME		10	/* 200us */
#घोषणा	MTK_HW_LRO_AGE_TIME		50	/* 1ms */
#घोषणा	MTK_HW_LRO_MAX_AGG_CNT		64
#घोषणा	MTK_HW_LRO_BW_THRE		3000
#घोषणा	MTK_HW_LRO_REPLACE_DELTA	1000
#घोषणा	MTK_HW_LRO_SDL_REMAIN_ROOM	1522

/* Frame Engine Global Reset Register */
#घोषणा MTK_RST_GL		0x04
#घोषणा RST_GL_PSE		BIT(0)

/* Frame Engine Interrupt Status Register */
#घोषणा MTK_INT_STATUS2		0x08
#घोषणा MTK_GDM1_AF		BIT(28)
#घोषणा MTK_GDM2_AF		BIT(29)

/* PDMA HW LRO Alter Flow Timer Register */
#घोषणा MTK_PDMA_LRO_ALT_REFRESH_TIMER	0x1c

/* Frame Engine Interrupt Grouping Register */
#घोषणा MTK_FE_INT_GRP		0x20

/* CDMP Ingress Control Register */
#घोषणा MTK_CDMQ_IG_CTRL	0x1400
#घोषणा MTK_CDMQ_STAG_EN	BIT(0)

/* CDMP Exgress Control Register */
#घोषणा MTK_CDMP_EG_CTRL	0x404

/* GDM Exgress Control Register */
#घोषणा MTK_GDMA_FWD_CFG(x)	(0x500 + (x * 0x1000))
#घोषणा MTK_GDMA_SPECIAL_TAG	BIT(24)
#घोषणा MTK_GDMA_ICS_EN		BIT(22)
#घोषणा MTK_GDMA_TCS_EN		BIT(21)
#घोषणा MTK_GDMA_UCS_EN		BIT(20)
#घोषणा MTK_GDMA_TO_PDMA	0x0
#घोषणा MTK_GDMA_TO_PPE		0x4444
#घोषणा MTK_GDMA_DROP_ALL       0x7777

/* Unicast Filter MAC Address Register - Low */
#घोषणा MTK_GDMA_MAC_ADRL(x)	(0x508 + (x * 0x1000))

/* Unicast Filter MAC Address Register - High */
#घोषणा MTK_GDMA_MAC_ADRH(x)	(0x50C + (x * 0x1000))

/* PDMA RX Base Poपूर्णांकer Register */
#घोषणा MTK_PRX_BASE_PTR0	0x900
#घोषणा MTK_PRX_BASE_PTR_CFG(x)	(MTK_PRX_BASE_PTR0 + (x * 0x10))

/* PDMA RX Maximum Count Register */
#घोषणा MTK_PRX_MAX_CNT0	0x904
#घोषणा MTK_PRX_MAX_CNT_CFG(x)	(MTK_PRX_MAX_CNT0 + (x * 0x10))

/* PDMA RX CPU Poपूर्णांकer Register */
#घोषणा MTK_PRX_CRX_IDX0	0x908
#घोषणा MTK_PRX_CRX_IDX_CFG(x)	(MTK_PRX_CRX_IDX0 + (x * 0x10))

/* PDMA HW LRO Control Registers */
#घोषणा MTK_PDMA_LRO_CTRL_DW0	0x980
#घोषणा MTK_LRO_EN			BIT(0)
#घोषणा MTK_L3_CKS_UPD_EN		BIT(7)
#घोषणा MTK_LRO_ALT_PKT_CNT_MODE	BIT(21)
#घोषणा MTK_LRO_RING_RELINQUISH_REQ	(0x7 << 26)
#घोषणा MTK_LRO_RING_RELINQUISH_DONE	(0x7 << 29)

#घोषणा MTK_PDMA_LRO_CTRL_DW1	0x984
#घोषणा MTK_PDMA_LRO_CTRL_DW2	0x988
#घोषणा MTK_PDMA_LRO_CTRL_DW3	0x98c
#घोषणा MTK_ADMA_MODE		BIT(15)
#घोषणा MTK_LRO_MIN_RXD_SDL	(MTK_HW_LRO_SDL_REMAIN_ROOM << 16)

/* PDMA Global Configuration Register */
#घोषणा MTK_PDMA_GLO_CFG	0xa04
#घोषणा MTK_MULTI_EN		BIT(10)
#घोषणा MTK_PDMA_SIZE_8DWORDS	(1 << 4)

/* PDMA Reset Index Register */
#घोषणा MTK_PDMA_RST_IDX	0xa08
#घोषणा MTK_PST_DRX_IDX0	BIT(16)
#घोषणा MTK_PST_DRX_IDX_CFG(x)	(MTK_PST_DRX_IDX0 << (x))

/* PDMA Delay Interrupt Register */
#घोषणा MTK_PDMA_DELAY_INT		0xa0c
#घोषणा MTK_PDMA_DELAY_RX_MASK		GENMASK(15, 0)
#घोषणा MTK_PDMA_DELAY_RX_EN		BIT(15)
#घोषणा MTK_PDMA_DELAY_RX_PINT_SHIFT	8
#घोषणा MTK_PDMA_DELAY_RX_PTIME_SHIFT	0

#घोषणा MTK_PDMA_DELAY_TX_MASK		GENMASK(31, 16)
#घोषणा MTK_PDMA_DELAY_TX_EN		BIT(31)
#घोषणा MTK_PDMA_DELAY_TX_PINT_SHIFT	24
#घोषणा MTK_PDMA_DELAY_TX_PTIME_SHIFT	16

#घोषणा MTK_PDMA_DELAY_PINT_MASK	0x7f
#घोषणा MTK_PDMA_DELAY_PTIME_MASK	0xff

/* PDMA Interrupt Status Register */
#घोषणा MTK_PDMA_INT_STATUS	0xa20

/* PDMA Interrupt Mask Register */
#घोषणा MTK_PDMA_INT_MASK	0xa28

/* PDMA HW LRO Alter Flow Delta Register */
#घोषणा MTK_PDMA_LRO_ALT_SCORE_DELTA	0xa4c

/* PDMA Interrupt grouping रेजिस्टरs */
#घोषणा MTK_PDMA_INT_GRP1	0xa50
#घोषणा MTK_PDMA_INT_GRP2	0xa54

/* PDMA HW LRO IP Setting Registers */
#घोषणा MTK_LRO_RX_RING0_DIP_DW0	0xb04
#घोषणा MTK_LRO_DIP_DW0_CFG(x)		(MTK_LRO_RX_RING0_DIP_DW0 + (x * 0x40))
#घोषणा MTK_RING_MYIP_VLD		BIT(9)

/* PDMA HW LRO Ring Control Registers */
#घोषणा MTK_LRO_RX_RING0_CTRL_DW1	0xb28
#घोषणा MTK_LRO_RX_RING0_CTRL_DW2	0xb2c
#घोषणा MTK_LRO_RX_RING0_CTRL_DW3	0xb30
#घोषणा MTK_LRO_CTRL_DW1_CFG(x)		(MTK_LRO_RX_RING0_CTRL_DW1 + (x * 0x40))
#घोषणा MTK_LRO_CTRL_DW2_CFG(x)		(MTK_LRO_RX_RING0_CTRL_DW2 + (x * 0x40))
#घोषणा MTK_LRO_CTRL_DW3_CFG(x)		(MTK_LRO_RX_RING0_CTRL_DW3 + (x * 0x40))
#घोषणा MTK_RING_AGE_TIME_L		((MTK_HW_LRO_AGE_TIME & 0x3ff) << 22)
#घोषणा MTK_RING_AGE_TIME_H		((MTK_HW_LRO_AGE_TIME >> 10) & 0x3f)
#घोषणा MTK_RING_AUTO_LERAN_MODE	(3 << 6)
#घोषणा MTK_RING_VLD			BIT(8)
#घोषणा MTK_RING_MAX_AGG_TIME		((MTK_HW_LRO_AGG_TIME & 0xffff) << 10)
#घोषणा MTK_RING_MAX_AGG_CNT_L		((MTK_HW_LRO_MAX_AGG_CNT & 0x3f) << 26)
#घोषणा MTK_RING_MAX_AGG_CNT_H		((MTK_HW_LRO_MAX_AGG_CNT >> 6) & 0x3)

/* QDMA TX Queue Configuration Registers */
#घोषणा MTK_QTX_CFG(x)		(0x1800 + (x * 0x10))
#घोषणा QDMA_RES_THRES		4

/* QDMA TX Queue Scheduler Registers */
#घोषणा MTK_QTX_SCH(x)		(0x1804 + (x * 0x10))

/* QDMA RX Base Poपूर्णांकer Register */
#घोषणा MTK_QRX_BASE_PTR0	0x1900

/* QDMA RX Maximum Count Register */
#घोषणा MTK_QRX_MAX_CNT0	0x1904

/* QDMA RX CPU Poपूर्णांकer Register */
#घोषणा MTK_QRX_CRX_IDX0	0x1908

/* QDMA RX DMA Poपूर्णांकer Register */
#घोषणा MTK_QRX_DRX_IDX0	0x190C

/* QDMA Global Configuration Register */
#घोषणा MTK_QDMA_GLO_CFG	0x1A04
#घोषणा MTK_RX_2B_OFFSET	BIT(31)
#घोषणा MTK_RX_BT_32DWORDS	(3 << 11)
#घोषणा MTK_NDP_CO_PRO		BIT(10)
#घोषणा MTK_TX_WB_DDONE		BIT(6)
#घोषणा MTK_TX_BT_32DWORDS	(3 << 4)
#घोषणा MTK_RX_DMA_BUSY		BIT(3)
#घोषणा MTK_TX_DMA_BUSY		BIT(1)
#घोषणा MTK_RX_DMA_EN		BIT(2)
#घोषणा MTK_TX_DMA_EN		BIT(0)
#घोषणा MTK_DMA_BUSY_TIMEOUT_US	1000000

/* QDMA Reset Index Register */
#घोषणा MTK_QDMA_RST_IDX	0x1A08

/* QDMA Delay Interrupt Register */
#घोषणा MTK_QDMA_DELAY_INT	0x1A0C

/* QDMA Flow Control Register */
#घोषणा MTK_QDMA_FC_THRES	0x1A10
#घोषणा FC_THRES_DROP_MODE	BIT(20)
#घोषणा FC_THRES_DROP_EN	(7 << 16)
#घोषणा FC_THRES_MIN		0x4444

/* QDMA Interrupt Status Register */
#घोषणा MTK_QDMA_INT_STATUS	0x1A18
#घोषणा MTK_RX_DONE_DLY		BIT(30)
#घोषणा MTK_TX_DONE_DLY		BIT(28)
#घोषणा MTK_RX_DONE_INT3	BIT(19)
#घोषणा MTK_RX_DONE_INT2	BIT(18)
#घोषणा MTK_RX_DONE_INT1	BIT(17)
#घोषणा MTK_RX_DONE_INT0	BIT(16)
#घोषणा MTK_TX_DONE_INT3	BIT(3)
#घोषणा MTK_TX_DONE_INT2	BIT(2)
#घोषणा MTK_TX_DONE_INT1	BIT(1)
#घोषणा MTK_TX_DONE_INT0	BIT(0)
#घोषणा MTK_RX_DONE_INT		MTK_RX_DONE_DLY
#घोषणा MTK_TX_DONE_INT		MTK_TX_DONE_DLY

/* QDMA Interrupt grouping रेजिस्टरs */
#घोषणा MTK_QDMA_INT_GRP1	0x1a20
#घोषणा MTK_QDMA_INT_GRP2	0x1a24
#घोषणा MTK_RLS_DONE_INT	BIT(0)

/* QDMA Interrupt Status Register */
#घोषणा MTK_QDMA_INT_MASK	0x1A1C

/* QDMA Interrupt Mask Register */
#घोषणा MTK_QDMA_HRED2		0x1A44

/* QDMA TX Forward CPU Poपूर्णांकer Register */
#घोषणा MTK_QTX_CTX_PTR		0x1B00

/* QDMA TX Forward DMA Poपूर्णांकer Register */
#घोषणा MTK_QTX_DTX_PTR		0x1B04

/* QDMA TX Release CPU Poपूर्णांकer Register */
#घोषणा MTK_QTX_CRX_PTR		0x1B10

/* QDMA TX Release DMA Poपूर्णांकer Register */
#घोषणा MTK_QTX_DRX_PTR		0x1B14

/* QDMA FQ Head Poपूर्णांकer Register */
#घोषणा MTK_QDMA_FQ_HEAD	0x1B20

/* QDMA FQ Head Poपूर्णांकer Register */
#घोषणा MTK_QDMA_FQ_TAIL	0x1B24

/* QDMA FQ Free Page Counter Register */
#घोषणा MTK_QDMA_FQ_CNT		0x1B28

/* QDMA FQ Free Page Buffer Length Register */
#घोषणा MTK_QDMA_FQ_BLEN	0x1B2C

/* GMA1 counter / अटलs रेजिस्टर */
#घोषणा MTK_GDM1_RX_GBCNT_L	0x2400
#घोषणा MTK_GDM1_RX_GBCNT_H	0x2404
#घोषणा MTK_GDM1_RX_GPCNT	0x2408
#घोषणा MTK_GDM1_RX_OERCNT	0x2410
#घोषणा MTK_GDM1_RX_FERCNT	0x2414
#घोषणा MTK_GDM1_RX_SERCNT	0x2418
#घोषणा MTK_GDM1_RX_LENCNT	0x241c
#घोषणा MTK_GDM1_RX_CERCNT	0x2420
#घोषणा MTK_GDM1_RX_FCCNT	0x2424
#घोषणा MTK_GDM1_TX_SKIPCNT	0x2428
#घोषणा MTK_GDM1_TX_COLCNT	0x242c
#घोषणा MTK_GDM1_TX_GBCNT_L	0x2430
#घोषणा MTK_GDM1_TX_GBCNT_H	0x2434
#घोषणा MTK_GDM1_TX_GPCNT	0x2438
#घोषणा MTK_STAT_OFFSET		0x40

/* QDMA descriptor txd4 */
#घोषणा TX_DMA_CHKSUM		(0x7 << 29)
#घोषणा TX_DMA_TSO		BIT(28)
#घोषणा TX_DMA_FPORT_SHIFT	25
#घोषणा TX_DMA_FPORT_MASK	0x7
#घोषणा TX_DMA_INS_VLAN		BIT(16)

/* QDMA descriptor txd3 */
#घोषणा TX_DMA_OWNER_CPU	BIT(31)
#घोषणा TX_DMA_LS0		BIT(30)
#घोषणा TX_DMA_PLEN0(_x)	(((_x) & MTK_TX_DMA_BUF_LEN) << 16)
#घोषणा TX_DMA_PLEN1(_x)	((_x) & MTK_TX_DMA_BUF_LEN)
#घोषणा TX_DMA_SWC		BIT(14)
#घोषणा TX_DMA_SDL(_x)		(((_x) & 0x3fff) << 16)

/* PDMA on MT7628 */
#घोषणा TX_DMA_DONE		BIT(31)
#घोषणा TX_DMA_LS1		BIT(14)
#घोषणा TX_DMA_DESP2_DEF	(TX_DMA_LS0 | TX_DMA_DONE)

/* QDMA descriptor rxd2 */
#घोषणा RX_DMA_DONE		BIT(31)
#घोषणा RX_DMA_LSO		BIT(30)
#घोषणा RX_DMA_PLEN0(_x)	(((_x) & 0x3fff) << 16)
#घोषणा RX_DMA_GET_PLEN0(_x)	(((_x) >> 16) & 0x3fff)
#घोषणा RX_DMA_VTAG		BIT(15)

/* QDMA descriptor rxd3 */
#घोषणा RX_DMA_VID(_x)		((_x) & 0xfff)

/* QDMA descriptor rxd4 */
#घोषणा MTK_RXD4_FOE_ENTRY	GENMASK(13, 0)
#घोषणा MTK_RXD4_PPE_CPU_REASON	GENMASK(18, 14)
#घोषणा MTK_RXD4_SRC_PORT	GENMASK(21, 19)
#घोषणा MTK_RXD4_ALG		GENMASK(31, 22)

/* QDMA descriptor rxd4 */
#घोषणा RX_DMA_L4_VALID		BIT(24)
#घोषणा RX_DMA_L4_VALID_PDMA	BIT(30)		/* when PDMA is used */
#घोषणा RX_DMA_FPORT_SHIFT	19
#घोषणा RX_DMA_FPORT_MASK	0x7
#घोषणा RX_DMA_SPECIAL_TAG	BIT(22)

/* PHY Indirect Access Control रेजिस्टरs */
#घोषणा MTK_PHY_IAC		0x10004
#घोषणा PHY_IAC_ACCESS		BIT(31)
#घोषणा PHY_IAC_READ		BIT(19)
#घोषणा PHY_IAC_WRITE		BIT(18)
#घोषणा PHY_IAC_START		BIT(16)
#घोषणा PHY_IAC_ADDR_SHIFT	20
#घोषणा PHY_IAC_REG_SHIFT	25
#घोषणा PHY_IAC_TIMEOUT		HZ

#घोषणा MTK_MAC_MISC		0x1000c
#घोषणा MTK_MUX_TO_ESW		BIT(0)

/* Mac control रेजिस्टरs */
#घोषणा MTK_MAC_MCR(x)		(0x10100 + (x * 0x100))
#घोषणा MAC_MCR_MAX_RX_MASK	GENMASK(25, 24)
#घोषणा MAC_MCR_MAX_RX(_x)	(MAC_MCR_MAX_RX_MASK & ((_x) << 24))
#घोषणा MAC_MCR_MAX_RX_1518	0x0
#घोषणा MAC_MCR_MAX_RX_1536	0x1
#घोषणा MAC_MCR_MAX_RX_1552	0x2
#घोषणा MAC_MCR_MAX_RX_2048	0x3
#घोषणा MAC_MCR_IPG_CFG		(BIT(18) | BIT(16))
#घोषणा MAC_MCR_FORCE_MODE	BIT(15)
#घोषणा MAC_MCR_TX_EN		BIT(14)
#घोषणा MAC_MCR_RX_EN		BIT(13)
#घोषणा MAC_MCR_BACKOFF_EN	BIT(9)
#घोषणा MAC_MCR_BACKPR_EN	BIT(8)
#घोषणा MAC_MCR_FORCE_RX_FC	BIT(5)
#घोषणा MAC_MCR_FORCE_TX_FC	BIT(4)
#घोषणा MAC_MCR_SPEED_1000	BIT(3)
#घोषणा MAC_MCR_SPEED_100	BIT(2)
#घोषणा MAC_MCR_FORCE_DPX	BIT(1)
#घोषणा MAC_MCR_FORCE_LINK	BIT(0)
#घोषणा MAC_MCR_FORCE_LINK_DOWN	(MAC_MCR_FORCE_MODE)

/* Mac status रेजिस्टरs */
#घोषणा MTK_MAC_MSR(x)		(0x10108 + (x * 0x100))
#घोषणा MAC_MSR_EEE1G		BIT(7)
#घोषणा MAC_MSR_EEE100M		BIT(6)
#घोषणा MAC_MSR_RX_FC		BIT(5)
#घोषणा MAC_MSR_TX_FC		BIT(4)
#घोषणा MAC_MSR_SPEED_1000	BIT(3)
#घोषणा MAC_MSR_SPEED_100	BIT(2)
#घोषणा MAC_MSR_SPEED_MASK	(MAC_MSR_SPEED_1000 | MAC_MSR_SPEED_100)
#घोषणा MAC_MSR_DPX		BIT(1)
#घोषणा MAC_MSR_LINK		BIT(0)

/* TRGMII RXC control रेजिस्टर */
#घोषणा TRGMII_RCK_CTRL		0x10300
#घोषणा DQSI0(x)		((x << 0) & GENMASK(6, 0))
#घोषणा DQSI1(x)		((x << 8) & GENMASK(14, 8))
#घोषणा RXCTL_DMWTLAT(x)	((x << 16) & GENMASK(18, 16))
#घोषणा RXC_RST			BIT(31)
#घोषणा RXC_DQSISEL		BIT(30)
#घोषणा RCK_CTRL_RGMII_1000	(RXC_DQSISEL | RXCTL_DMWTLAT(2) | DQSI1(16))
#घोषणा RCK_CTRL_RGMII_10_100	RXCTL_DMWTLAT(2)

#घोषणा NUM_TRGMII_CTRL		5

/* TRGMII RXC control रेजिस्टर */
#घोषणा TRGMII_TCK_CTRL		0x10340
#घोषणा TXCTL_DMWTLAT(x)	((x << 16) & GENMASK(18, 16))
#घोषणा TXC_INV			BIT(30)
#घोषणा TCK_CTRL_RGMII_1000	TXCTL_DMWTLAT(2)
#घोषणा TCK_CTRL_RGMII_10_100	(TXC_INV | TXCTL_DMWTLAT(2))

/* TRGMII TX Drive Strength */
#घोषणा TRGMII_TD_ODT(i)	(0x10354 + 8 * (i))
#घोषणा  TD_DM_DRVP(x)		((x) & 0xf)
#घोषणा  TD_DM_DRVN(x)		(((x) & 0xf) << 4)

/* TRGMII Interface mode रेजिस्टर */
#घोषणा INTF_MODE		0x10390
#घोषणा TRGMII_INTF_DIS		BIT(0)
#घोषणा TRGMII_MODE		BIT(1)
#घोषणा TRGMII_CENTRAL_ALIGNED	BIT(2)
#घोषणा INTF_MODE_RGMII_1000    (TRGMII_MODE | TRGMII_CENTRAL_ALIGNED)
#घोषणा INTF_MODE_RGMII_10_100  0

/* GPIO port control रेजिस्टरs क्रम GMAC 2*/
#घोषणा GPIO_OD33_CTRL8		0x4c0
#घोषणा GPIO_BIAS_CTRL		0xed0
#घोषणा GPIO_DRV_SEL10		0xf00

/* ethernet subप्रणाली chip id रेजिस्टर */
#घोषणा ETHSYS_CHIPID0_3	0x0
#घोषणा ETHSYS_CHIPID4_7	0x4
#घोषणा MT7623_ETH		7623
#घोषणा MT7622_ETH		7622
#घोषणा MT7621_ETH		7621

/* ethernet प्रणाली control रेजिस्टर */
#घोषणा ETHSYS_SYSCFG		0x10
#घोषणा SYSCFG_DRAM_TYPE_DDR2	BIT(4)

/* ethernet subप्रणाली config रेजिस्टर */
#घोषणा ETHSYS_SYSCFG0		0x14
#घोषणा SYSCFG0_GE_MASK		0x3
#घोषणा SYSCFG0_GE_MODE(x, y)	(x << (12 + (y * 2)))
#घोषणा SYSCFG0_SGMII_MASK     GENMASK(9, 8)
#घोषणा SYSCFG0_SGMII_GMAC1    ((2 << 8) & SYSCFG0_SGMII_MASK)
#घोषणा SYSCFG0_SGMII_GMAC2    ((3 << 8) & SYSCFG0_SGMII_MASK)
#घोषणा SYSCFG0_SGMII_GMAC1_V2 BIT(9)
#घोषणा SYSCFG0_SGMII_GMAC2_V2 BIT(8)


/* ethernet subप्रणाली घड़ी रेजिस्टर */
#घोषणा ETHSYS_CLKCFG0		0x2c
#घोषणा ETHSYS_TRGMII_CLK_SEL362_5	BIT(11)
#घोषणा ETHSYS_TRGMII_MT7621_MASK	(BIT(5) | BIT(6))
#घोषणा ETHSYS_TRGMII_MT7621_APLL	BIT(6)
#घोषणा ETHSYS_TRGMII_MT7621_DDR_PLL	BIT(5)

/* ethernet reset control रेजिस्टर */
#घोषणा ETHSYS_RSTCTRL		0x34
#घोषणा RSTCTRL_FE		BIT(6)
#घोषणा RSTCTRL_PPE		BIT(31)

/* SGMII subप्रणाली config रेजिस्टरs */
/* Register to स्वतः-negotiation restart */
#घोषणा SGMSYS_PCS_CONTROL_1	0x0
#घोषणा SGMII_AN_RESTART	BIT(9)
#घोषणा SGMII_ISOLATE		BIT(10)
#घोषणा SGMII_AN_ENABLE		BIT(12)
#घोषणा SGMII_LINK_STATYS	BIT(18)
#घोषणा SGMII_AN_ABILITY	BIT(19)
#घोषणा SGMII_AN_COMPLETE	BIT(21)
#घोषणा SGMII_PCS_FAULT		BIT(23)
#घोषणा SGMII_AN_EXPANSION_CLR	BIT(30)

/* Register to programmable link समयr, the unit in 2 * 8ns */
#घोषणा SGMSYS_PCS_LINK_TIMER	0x18
#घोषणा SGMII_LINK_TIMER_DEFAULT	(0x186a0 & GENMASK(19, 0))

/* Register to control remote fault */
#घोषणा SGMSYS_SGMII_MODE		0x20
#घोषणा SGMII_IF_MODE_BIT0		BIT(0)
#घोषणा SGMII_SPEED_DUPLEX_AN		BIT(1)
#घोषणा SGMII_SPEED_10			0x0
#घोषणा SGMII_SPEED_100			BIT(2)
#घोषणा SGMII_SPEED_1000		BIT(3)
#घोषणा SGMII_DUPLEX_FULL		BIT(4)
#घोषणा SGMII_IF_MODE_BIT5		BIT(5)
#घोषणा SGMII_REMOTE_FAULT_DIS		BIT(8)
#घोषणा SGMII_CODE_SYNC_SET_VAL		BIT(9)
#घोषणा SGMII_CODE_SYNC_SET_EN		BIT(10)
#घोषणा SGMII_SEND_AN_ERROR_EN		BIT(11)
#घोषणा SGMII_IF_MODE_MASK		GENMASK(5, 1)

/* Register to set SGMII speed, ANA RG_ Control Signals III*/
#घोषणा SGMSYS_ANA_RG_CS3	0x2028
#घोषणा RG_PHY_SPEED_MASK	(BIT(2) | BIT(3))
#घोषणा RG_PHY_SPEED_1_25G	0x0
#घोषणा RG_PHY_SPEED_3_125G	BIT(2)

/* Register to घातer up QPHY */
#घोषणा SGMSYS_QPHY_PWR_STATE_CTRL 0xe8
#घोषणा	SGMII_PHYA_PWD		BIT(4)

/* Infrasys subप्रणाली config रेजिस्टरs */
#घोषणा INFRA_MISC2            0x70c
#घोषणा CO_QPHY_SEL            BIT(0)
#घोषणा GEPHY_MAC_SEL          BIT(1)

/* MT7628/88 specअगरic stuff */
#घोषणा MT7628_PDMA_OFFSET	0x0800
#घोषणा MT7628_SDM_OFFSET	0x0c00

#घोषणा MT7628_TX_BASE_PTR0	(MT7628_PDMA_OFFSET + 0x00)
#घोषणा MT7628_TX_MAX_CNT0	(MT7628_PDMA_OFFSET + 0x04)
#घोषणा MT7628_TX_CTX_IDX0	(MT7628_PDMA_OFFSET + 0x08)
#घोषणा MT7628_TX_DTX_IDX0	(MT7628_PDMA_OFFSET + 0x0c)
#घोषणा MT7628_PST_DTX_IDX0	BIT(0)

#घोषणा MT7628_SDM_MAC_ADRL	(MT7628_SDM_OFFSET + 0x0c)
#घोषणा MT7628_SDM_MAC_ADRH	(MT7628_SDM_OFFSET + 0x10)

/* Counter / stat रेजिस्टर */
#घोषणा MT7628_SDM_TPCNT	(MT7628_SDM_OFFSET + 0x100)
#घोषणा MT7628_SDM_TBCNT	(MT7628_SDM_OFFSET + 0x104)
#घोषणा MT7628_SDM_RPCNT	(MT7628_SDM_OFFSET + 0x108)
#घोषणा MT7628_SDM_RBCNT	(MT7628_SDM_OFFSET + 0x10c)
#घोषणा MT7628_SDM_CS_ERR	(MT7628_SDM_OFFSET + 0x110)

काष्ठा mtk_rx_dma अणु
	अचिन्हित पूर्णांक rxd1;
	अचिन्हित पूर्णांक rxd2;
	अचिन्हित पूर्णांक rxd3;
	अचिन्हित पूर्णांक rxd4;
पूर्ण __packed __aligned(4);

काष्ठा mtk_tx_dma अणु
	अचिन्हित पूर्णांक txd1;
	अचिन्हित पूर्णांक txd2;
	अचिन्हित पूर्णांक txd3;
	अचिन्हित पूर्णांक txd4;
पूर्ण __packed __aligned(4);

काष्ठा mtk_eth;
काष्ठा mtk_mac;

/* काष्ठा mtk_hw_stats - the काष्ठाure that holds the traffic statistics.
 * @stats_lock:		make sure that stats operations are atomic
 * @reg_offset:		the status रेजिस्टर offset of the SoC
 * @syncp:		the refcount
 *
 * All of the supported SoCs have hardware counters क्रम traffic statistics.
 * Whenever the status IRQ triggers we can पढ़ो the latest stats from these
 * counters and store them in this काष्ठा.
 */
काष्ठा mtk_hw_stats अणु
	u64 tx_bytes;
	u64 tx_packets;
	u64 tx_skip;
	u64 tx_collisions;
	u64 rx_bytes;
	u64 rx_packets;
	u64 rx_overflow;
	u64 rx_fcs_errors;
	u64 rx_लघु_errors;
	u64 rx_दीर्घ_errors;
	u64 rx_checksum_errors;
	u64 rx_flow_control_packets;

	spinlock_t		stats_lock;
	u32			reg_offset;
	काष्ठा u64_stats_sync	syncp;
पूर्ण;

क्रमागत mtk_tx_flags अणु
	/* PDMA descriptor can poपूर्णांक at 1-2 segments. This क्रमागत allows us to
	 * track how memory was allocated so that it can be मुक्तd properly.
	 */
	MTK_TX_FLAGS_SINGLE0	= 0x01,
	MTK_TX_FLAGS_PAGE0	= 0x02,

	/* MTK_TX_FLAGS_FPORTx allows tracking which port the transmitted
	 * SKB out instead of looking up through hardware TX descriptor.
	 */
	MTK_TX_FLAGS_FPORT0	= 0x04,
	MTK_TX_FLAGS_FPORT1	= 0x08,
पूर्ण;

/* This क्रमागत allows us to identअगरy how the घड़ी is defined on the array of the
 * घड़ी in the order
 */
क्रमागत mtk_clks_map अणु
	MTK_CLK_ETHIF,
	MTK_CLK_SGMIITOP,
	MTK_CLK_ESW,
	MTK_CLK_GP0,
	MTK_CLK_GP1,
	MTK_CLK_GP2,
	MTK_CLK_FE,
	MTK_CLK_TRGPLL,
	MTK_CLK_SGMII_TX_250M,
	MTK_CLK_SGMII_RX_250M,
	MTK_CLK_SGMII_CDR_REF,
	MTK_CLK_SGMII_CDR_FB,
	MTK_CLK_SGMII2_TX_250M,
	MTK_CLK_SGMII2_RX_250M,
	MTK_CLK_SGMII2_CDR_REF,
	MTK_CLK_SGMII2_CDR_FB,
	MTK_CLK_SGMII_CK,
	MTK_CLK_ETH2PLL,
	MTK_CLK_MAX
पूर्ण;

#घोषणा MT7623_CLKS_BITMAP	(BIT(MTK_CLK_ETHIF) | BIT(MTK_CLK_ESW) |  \
				 BIT(MTK_CLK_GP1) | BIT(MTK_CLK_GP2) | \
				 BIT(MTK_CLK_TRGPLL))
#घोषणा MT7622_CLKS_BITMAP	(BIT(MTK_CLK_ETHIF) | BIT(MTK_CLK_ESW) |  \
				 BIT(MTK_CLK_GP0) | BIT(MTK_CLK_GP1) | \
				 BIT(MTK_CLK_GP2) | \
				 BIT(MTK_CLK_SGMII_TX_250M) | \
				 BIT(MTK_CLK_SGMII_RX_250M) | \
				 BIT(MTK_CLK_SGMII_CDR_REF) | \
				 BIT(MTK_CLK_SGMII_CDR_FB) | \
				 BIT(MTK_CLK_SGMII_CK) | \
				 BIT(MTK_CLK_ETH2PLL))
#घोषणा MT7621_CLKS_BITMAP	(0)
#घोषणा MT7628_CLKS_BITMAP	(0)
#घोषणा MT7629_CLKS_BITMAP	(BIT(MTK_CLK_ETHIF) | BIT(MTK_CLK_ESW) |  \
				 BIT(MTK_CLK_GP0) | BIT(MTK_CLK_GP1) | \
				 BIT(MTK_CLK_GP2) | BIT(MTK_CLK_FE) | \
				 BIT(MTK_CLK_SGMII_TX_250M) | \
				 BIT(MTK_CLK_SGMII_RX_250M) | \
				 BIT(MTK_CLK_SGMII_CDR_REF) | \
				 BIT(MTK_CLK_SGMII_CDR_FB) | \
				 BIT(MTK_CLK_SGMII2_TX_250M) | \
				 BIT(MTK_CLK_SGMII2_RX_250M) | \
				 BIT(MTK_CLK_SGMII2_CDR_REF) | \
				 BIT(MTK_CLK_SGMII2_CDR_FB) | \
				 BIT(MTK_CLK_SGMII_CK) | \
				 BIT(MTK_CLK_ETH2PLL) | BIT(MTK_CLK_SGMIITOP))

क्रमागत mtk_dev_state अणु
	MTK_HW_INIT,
	MTK_RESETTING
पूर्ण;

/* काष्ठा mtk_tx_buf -	This काष्ठा holds the poपूर्णांकers to the memory poपूर्णांकed at
 *			by the TX descriptor	s
 * @skb:		The SKB poपूर्णांकer of the packet being sent
 * @dma_addr0:		The base addr of the first segment
 * @dma_len0:		The length of the first segment
 * @dma_addr1:		The base addr of the second segment
 * @dma_len1:		The length of the second segment
 */
काष्ठा mtk_tx_buf अणु
	काष्ठा sk_buff *skb;
	u32 flags;
	DEFINE_DMA_UNMAP_ADDR(dma_addr0);
	DEFINE_DMA_UNMAP_LEN(dma_len0);
	DEFINE_DMA_UNMAP_ADDR(dma_addr1);
	DEFINE_DMA_UNMAP_LEN(dma_len1);
पूर्ण;

/* काष्ठा mtk_tx_ring -	This काष्ठा holds info describing a TX ring
 * @dma:		The descriptor ring
 * @buf:		The memory poपूर्णांकed at by the ring
 * @phys:		The physical addr of tx_buf
 * @next_मुक्त:		Poपूर्णांकer to the next मुक्त descriptor
 * @last_मुक्त:		Poपूर्णांकer to the last मुक्त descriptor
 * @last_मुक्त_ptr:	Hardware poपूर्णांकer value of the last मुक्त descriptor
 * @thresh:		The threshold of minimum amount of मुक्त descriptors
 * @मुक्त_count:		QDMA uses a linked list. Track how many मुक्त descriptors
 *			are present
 */
काष्ठा mtk_tx_ring अणु
	काष्ठा mtk_tx_dma *dma;
	काष्ठा mtk_tx_buf *buf;
	dma_addr_t phys;
	काष्ठा mtk_tx_dma *next_मुक्त;
	काष्ठा mtk_tx_dma *last_मुक्त;
	u32 last_मुक्त_ptr;
	u16 thresh;
	atomic_t मुक्त_count;
	पूर्णांक dma_size;
	काष्ठा mtk_tx_dma *dma_pdma;	/* For MT7628/88 PDMA handling */
	dma_addr_t phys_pdma;
	पूर्णांक cpu_idx;
पूर्ण;

/* PDMA rx ring mode */
क्रमागत mtk_rx_flags अणु
	MTK_RX_FLAGS_NORMAL = 0,
	MTK_RX_FLAGS_HWLRO,
	MTK_RX_FLAGS_QDMA,
पूर्ण;

/* काष्ठा mtk_rx_ring -	This काष्ठा holds info describing a RX ring
 * @dma:		The descriptor ring
 * @data:		The memory poपूर्णांकed at by the ring
 * @phys:		The physical addr of rx_buf
 * @frag_size:		How big can each fragment be
 * @buf_size:		The size of each packet buffer
 * @calc_idx:		The current head of ring
 */
काष्ठा mtk_rx_ring अणु
	काष्ठा mtk_rx_dma *dma;
	u8 **data;
	dma_addr_t phys;
	u16 frag_size;
	u16 buf_size;
	u16 dma_size;
	bool calc_idx_update;
	u16 calc_idx;
	u32 crx_idx_reg;
पूर्ण;

क्रमागत mkt_eth_capabilities अणु
	MTK_RGMII_BIT = 0,
	MTK_TRGMII_BIT,
	MTK_SGMII_BIT,
	MTK_ESW_BIT,
	MTK_GEPHY_BIT,
	MTK_MUX_BIT,
	MTK_INFRA_BIT,
	MTK_SHARED_SGMII_BIT,
	MTK_HWLRO_BIT,
	MTK_SHARED_INT_BIT,
	MTK_TRGMII_MT7621_CLK_BIT,
	MTK_QDMA_BIT,
	MTK_SOC_MT7628_BIT,

	/* MUX BITS*/
	MTK_ETH_MUX_GDM1_TO_GMAC1_ESW_BIT,
	MTK_ETH_MUX_GMAC2_GMAC0_TO_GEPHY_BIT,
	MTK_ETH_MUX_U3_GMAC2_TO_QPHY_BIT,
	MTK_ETH_MUX_GMAC1_GMAC2_TO_SGMII_RGMII_BIT,
	MTK_ETH_MUX_GMAC12_TO_GEPHY_SGMII_BIT,

	/* PATH BITS */
	MTK_ETH_PATH_GMAC1_RGMII_BIT,
	MTK_ETH_PATH_GMAC1_TRGMII_BIT,
	MTK_ETH_PATH_GMAC1_SGMII_BIT,
	MTK_ETH_PATH_GMAC2_RGMII_BIT,
	MTK_ETH_PATH_GMAC2_SGMII_BIT,
	MTK_ETH_PATH_GMAC2_GEPHY_BIT,
	MTK_ETH_PATH_GDM1_ESW_BIT,
पूर्ण;

/* Supported hardware group on SoCs */
#घोषणा MTK_RGMII		BIT(MTK_RGMII_BIT)
#घोषणा MTK_TRGMII		BIT(MTK_TRGMII_BIT)
#घोषणा MTK_SGMII		BIT(MTK_SGMII_BIT)
#घोषणा MTK_ESW			BIT(MTK_ESW_BIT)
#घोषणा MTK_GEPHY		BIT(MTK_GEPHY_BIT)
#घोषणा MTK_MUX			BIT(MTK_MUX_BIT)
#घोषणा MTK_INFRA		BIT(MTK_INFRA_BIT)
#घोषणा MTK_SHARED_SGMII	BIT(MTK_SHARED_SGMII_BIT)
#घोषणा MTK_HWLRO		BIT(MTK_HWLRO_BIT)
#घोषणा MTK_SHARED_INT		BIT(MTK_SHARED_INT_BIT)
#घोषणा MTK_TRGMII_MT7621_CLK	BIT(MTK_TRGMII_MT7621_CLK_BIT)
#घोषणा MTK_QDMA		BIT(MTK_QDMA_BIT)
#घोषणा MTK_SOC_MT7628		BIT(MTK_SOC_MT7628_BIT)

#घोषणा MTK_ETH_MUX_GDM1_TO_GMAC1_ESW		\
	BIT(MTK_ETH_MUX_GDM1_TO_GMAC1_ESW_BIT)
#घोषणा MTK_ETH_MUX_GMAC2_GMAC0_TO_GEPHY	\
	BIT(MTK_ETH_MUX_GMAC2_GMAC0_TO_GEPHY_BIT)
#घोषणा MTK_ETH_MUX_U3_GMAC2_TO_QPHY		\
	BIT(MTK_ETH_MUX_U3_GMAC2_TO_QPHY_BIT)
#घोषणा MTK_ETH_MUX_GMAC1_GMAC2_TO_SGMII_RGMII	\
	BIT(MTK_ETH_MUX_GMAC1_GMAC2_TO_SGMII_RGMII_BIT)
#घोषणा MTK_ETH_MUX_GMAC12_TO_GEPHY_SGMII	\
	BIT(MTK_ETH_MUX_GMAC12_TO_GEPHY_SGMII_BIT)

/* Supported path present on SoCs */
#घोषणा MTK_ETH_PATH_GMAC1_RGMII	BIT(MTK_ETH_PATH_GMAC1_RGMII_BIT)
#घोषणा MTK_ETH_PATH_GMAC1_TRGMII	BIT(MTK_ETH_PATH_GMAC1_TRGMII_BIT)
#घोषणा MTK_ETH_PATH_GMAC1_SGMII	BIT(MTK_ETH_PATH_GMAC1_SGMII_BIT)
#घोषणा MTK_ETH_PATH_GMAC2_RGMII	BIT(MTK_ETH_PATH_GMAC2_RGMII_BIT)
#घोषणा MTK_ETH_PATH_GMAC2_SGMII	BIT(MTK_ETH_PATH_GMAC2_SGMII_BIT)
#घोषणा MTK_ETH_PATH_GMAC2_GEPHY	BIT(MTK_ETH_PATH_GMAC2_GEPHY_BIT)
#घोषणा MTK_ETH_PATH_GDM1_ESW		BIT(MTK_ETH_PATH_GDM1_ESW_BIT)

#घोषणा MTK_GMAC1_RGMII		(MTK_ETH_PATH_GMAC1_RGMII | MTK_RGMII)
#घोषणा MTK_GMAC1_TRGMII	(MTK_ETH_PATH_GMAC1_TRGMII | MTK_TRGMII)
#घोषणा MTK_GMAC1_SGMII		(MTK_ETH_PATH_GMAC1_SGMII | MTK_SGMII)
#घोषणा MTK_GMAC2_RGMII		(MTK_ETH_PATH_GMAC2_RGMII | MTK_RGMII)
#घोषणा MTK_GMAC2_SGMII		(MTK_ETH_PATH_GMAC2_SGMII | MTK_SGMII)
#घोषणा MTK_GMAC2_GEPHY		(MTK_ETH_PATH_GMAC2_GEPHY | MTK_GEPHY)
#घोषणा MTK_GDM1_ESW		(MTK_ETH_PATH_GDM1_ESW | MTK_ESW)

/* MUXes present on SoCs */
/* 0: GDM1 -> GMAC1, 1: GDM1 -> ESW */
#घोषणा MTK_MUX_GDM1_TO_GMAC1_ESW (MTK_ETH_MUX_GDM1_TO_GMAC1_ESW | MTK_MUX)

/* 0: GMAC2 -> GEPHY, 1: GMAC0 -> GePHY */
#घोषणा MTK_MUX_GMAC2_GMAC0_TO_GEPHY    \
	(MTK_ETH_MUX_GMAC2_GMAC0_TO_GEPHY | MTK_MUX | MTK_INFRA)

/* 0: U3 -> QPHY, 1: GMAC2 -> QPHY */
#घोषणा MTK_MUX_U3_GMAC2_TO_QPHY        \
	(MTK_ETH_MUX_U3_GMAC2_TO_QPHY | MTK_MUX | MTK_INFRA)

/* 2: GMAC1 -> SGMII, 3: GMAC2 -> SGMII */
#घोषणा MTK_MUX_GMAC1_GMAC2_TO_SGMII_RGMII      \
	(MTK_ETH_MUX_GMAC1_GMAC2_TO_SGMII_RGMII | MTK_MUX | \
	MTK_SHARED_SGMII)

/* 0: GMACx -> GEPHY, 1: GMACx -> SGMII where x is 1 or 2 */
#घोषणा MTK_MUX_GMAC12_TO_GEPHY_SGMII   \
	(MTK_ETH_MUX_GMAC12_TO_GEPHY_SGMII | MTK_MUX)

#घोषणा MTK_HAS_CAPS(caps, _x)		(((caps) & (_x)) == (_x))

#घोषणा MT7621_CAPS  (MTK_GMAC1_RGMII | MTK_GMAC1_TRGMII | \
		      MTK_GMAC2_RGMII | MTK_SHARED_INT | \
		      MTK_TRGMII_MT7621_CLK | MTK_QDMA)

#घोषणा MT7622_CAPS  (MTK_GMAC1_RGMII | MTK_GMAC1_SGMII | MTK_GMAC2_RGMII | \
		      MTK_GMAC2_SGMII | MTK_GDM1_ESW | \
		      MTK_MUX_GDM1_TO_GMAC1_ESW | \
		      MTK_MUX_GMAC1_GMAC2_TO_SGMII_RGMII | MTK_QDMA)

#घोषणा MT7623_CAPS  (MTK_GMAC1_RGMII | MTK_GMAC1_TRGMII | MTK_GMAC2_RGMII | \
		      MTK_QDMA)

#घोषणा MT7628_CAPS  (MTK_SHARED_INT | MTK_SOC_MT7628)

#घोषणा MT7629_CAPS  (MTK_GMAC1_SGMII | MTK_GMAC2_SGMII | MTK_GMAC2_GEPHY | \
		      MTK_GDM1_ESW | MTK_MUX_GDM1_TO_GMAC1_ESW | \
		      MTK_MUX_GMAC2_GMAC0_TO_GEPHY | \
		      MTK_MUX_U3_GMAC2_TO_QPHY | \
		      MTK_MUX_GMAC12_TO_GEPHY_SGMII | MTK_QDMA)

/* काष्ठा mtk_eth_data -	This is the काष्ठाure holding all dअगरferences
 *				among various plaक्रमms
 * @ana_rgc3:                   The offset क्रम रेजिस्टर ANA_RGC3 related to
 *				sgmiisys syscon
 * @caps			Flags shown the extra capability क्रम the SoC
 * @hw_features			Flags shown HW features
 * @required_clks		Flags shown the biपंचांगap क्रम required घड़ीs on
 *				the target SoC
 * @required_pctl		A bool value to show whether the SoC requires
 *				the extra setup क्रम those pins used by GMAC.
 */
काष्ठा mtk_soc_data अणु
	u32             ana_rgc3;
	u32		caps;
	u32		required_clks;
	bool		required_pctl;
	u8		offload_version;
	netdev_features_t hw_features;
पूर्ण;

/* currently no SoC has more than 2 macs */
#घोषणा MTK_MAX_DEVS			2

#घोषणा MTK_SGMII_PHYSPEED_AN          BIT(31)
#घोषणा MTK_SGMII_PHYSPEED_MASK        GENMASK(2, 0)
#घोषणा MTK_SGMII_PHYSPEED_1000        BIT(0)
#घोषणा MTK_SGMII_PHYSPEED_2500        BIT(1)
#घोषणा MTK_HAS_FLAGS(flags, _x)       (((flags) & (_x)) == (_x))

/* काष्ठा mtk_sgmii -  This is the काष्ठाure holding sgmii regmap and its
 *                     अक्षरacteristics
 * @regmap:            The रेजिस्टर map poपूर्णांकing at the range used to setup
 *                     SGMII modes
 * @flags:             The क्रमागत refers to which mode the sgmii wants to run on
 * @ana_rgc3:          The offset refers to रेजिस्टर ANA_RGC3 related to regmap
 */

काष्ठा mtk_sgmii अणु
	काष्ठा regmap   *regmap[MTK_MAX_DEVS];
	u32             flags[MTK_MAX_DEVS];
	u32             ana_rgc3;
पूर्ण;

/* काष्ठा mtk_eth -	This is the मुख्य datasructure क्रम holding the state
 *			of the driver
 * @dev:		The device poपूर्णांकer
 * @base:		The mapped रेजिस्टर i/o base
 * @page_lock:		Make sure that रेजिस्टर operations are atomic
 * @tx_irq__lock:	Make sure that IRQ रेजिस्टर operations are atomic
 * @rx_irq__lock:	Make sure that IRQ रेजिस्टर operations are atomic
 * @dim_lock:		Make sure that Net DIM operations are atomic
 * @dummy_dev:		we run 2 netdevs on 1 physical DMA ring and need a
 *			dummy क्रम NAPI to work
 * @netdev:		The netdev instances
 * @mac:		Each netdev is linked to a physical MAC
 * @irq:		The IRQ that we are using
 * @msg_enable:		Ethtool msg level
 * @ethsys:		The रेजिस्टर map poपूर्णांकing at the range used to setup
 *			MII modes
 * @infra:              The रेजिस्टर map poपूर्णांकing at the range used to setup
 *                      SGMII and GePHY path
 * @pctl:		The रेजिस्टर map poपूर्णांकing at the range used to setup
 *			GMAC port drive/slew values
 * @dma_refcnt:		track how many netdevs are using the DMA engine
 * @tx_ring:		Poपूर्णांकer to the memory holding info about the TX ring
 * @rx_ring:		Poपूर्णांकer to the memory holding info about the RX ring
 * @rx_ring_qdma:	Poपूर्णांकer to the memory holding info about the QDMA RX ring
 * @tx_napi:		The TX NAPI काष्ठा
 * @rx_napi:		The RX NAPI काष्ठा
 * @rx_events:		Net DIM RX event counter
 * @rx_packets:		Net DIM RX packet counter
 * @rx_bytes:		Net DIM RX byte counter
 * @rx_dim:		Net DIM RX context
 * @tx_events:		Net DIM TX event counter
 * @tx_packets:		Net DIM TX packet counter
 * @tx_bytes:		Net DIM TX byte counter
 * @tx_dim:		Net DIM TX context
 * @scratch_ring:	Newer SoCs need memory क्रम a second HW managed TX ring
 * @phy_scratch_ring:	physical address of scratch_ring
 * @scratch_head:	The scratch memory that scratch_ring poपूर्णांकs to.
 * @clks:		घड़ी array क्रम all घड़ीs required
 * @mii_bus:		If there is a bus we need to create an instance क्रम it
 * @pending_work:	The workqueue used to reset the dma ring
 * @state:		Initialization and runसमय state of the device
 * @soc:		Holding specअगरic data among vaious SoCs
 */

काष्ठा mtk_eth अणु
	काष्ठा device			*dev;
	व्योम __iomem			*base;
	spinlock_t			page_lock;
	spinlock_t			tx_irq_lock;
	spinlock_t			rx_irq_lock;
	काष्ठा net_device		dummy_dev;
	काष्ठा net_device		*netdev[MTK_MAX_DEVS];
	काष्ठा mtk_mac			*mac[MTK_MAX_DEVS];
	पूर्णांक				irq[3];
	u32				msg_enable;
	अचिन्हित दीर्घ			sysclk;
	काष्ठा regmap			*ethsys;
	काष्ठा regmap                   *infra;
	काष्ठा mtk_sgmii                *sgmii;
	काष्ठा regmap			*pctl;
	bool				hwlro;
	refcount_t			dma_refcnt;
	काष्ठा mtk_tx_ring		tx_ring;
	काष्ठा mtk_rx_ring		rx_ring[MTK_MAX_RX_RING_NUM];
	काष्ठा mtk_rx_ring		rx_ring_qdma;
	काष्ठा napi_काष्ठा		tx_napi;
	काष्ठा napi_काष्ठा		rx_napi;
	काष्ठा mtk_tx_dma		*scratch_ring;
	dma_addr_t			phy_scratch_ring;
	व्योम				*scratch_head;
	काष्ठा clk			*clks[MTK_CLK_MAX];

	काष्ठा mii_bus			*mii_bus;
	काष्ठा work_काष्ठा		pending_work;
	अचिन्हित दीर्घ			state;

	स्थिर काष्ठा mtk_soc_data	*soc;

	spinlock_t			dim_lock;

	u32				rx_events;
	u32				rx_packets;
	u32				rx_bytes;
	काष्ठा dim			rx_dim;

	u32				tx_events;
	u32				tx_packets;
	u32				tx_bytes;
	काष्ठा dim			tx_dim;

	u32				tx_पूर्णांक_mask_reg;
	u32				tx_पूर्णांक_status_reg;
	u32				rx_dma_l4_valid;
	पूर्णांक				ip_align;

	काष्ठा mtk_ppe			ppe;
	काष्ठा rhashtable		flow_table;
पूर्ण;

/* काष्ठा mtk_mac -	the काष्ठाure that holds the info about the MACs of the
 *			SoC
 * @id:			The number of the MAC
 * @पूर्णांकerface:		Interface mode kept क्रम detecting change in hw settings
 * @of_node:		Our devicetree node
 * @hw:			Backpoपूर्णांकer to our मुख्य datastruture
 * @hw_stats:		Packet statistics counter
 */
काष्ठा mtk_mac अणु
	पूर्णांक				id;
	phy_पूर्णांकerface_t			पूर्णांकerface;
	अचिन्हित पूर्णांक			mode;
	पूर्णांक				speed;
	काष्ठा device_node		*of_node;
	काष्ठा phylink			*phylink;
	काष्ठा phylink_config		phylink_config;
	काष्ठा mtk_eth			*hw;
	काष्ठा mtk_hw_stats		*hw_stats;
	__be32				hwlro_ip[MTK_MAX_LRO_IP_CNT];
	पूर्णांक				hwlro_ip_cnt;
पूर्ण;

/* the काष्ठा describing the SoC. these are declared in the soc_xyz.c files */
बाह्य स्थिर काष्ठा of_device_id of_mtk_match[];

/* पढ़ो the hardware status रेजिस्टर */
व्योम mtk_stats_update_mac(काष्ठा mtk_mac *mac);

व्योम mtk_w32(काष्ठा mtk_eth *eth, u32 val, अचिन्हित reg);
u32 mtk_r32(काष्ठा mtk_eth *eth, अचिन्हित reg);

पूर्णांक mtk_sgmii_init(काष्ठा mtk_sgmii *ss, काष्ठा device_node *np,
		   u32 ana_rgc3);
पूर्णांक mtk_sgmii_setup_mode_an(काष्ठा mtk_sgmii *ss, पूर्णांक id);
पूर्णांक mtk_sgmii_setup_mode_क्रमce(काष्ठा mtk_sgmii *ss, पूर्णांक id,
			       स्थिर काष्ठा phylink_link_state *state);
व्योम mtk_sgmii_restart_an(काष्ठा mtk_eth *eth, पूर्णांक mac_id);

पूर्णांक mtk_gmac_sgmii_path_setup(काष्ठा mtk_eth *eth, पूर्णांक mac_id);
पूर्णांक mtk_gmac_gephy_path_setup(काष्ठा mtk_eth *eth, पूर्णांक mac_id);
पूर्णांक mtk_gmac_rgmii_path_setup(काष्ठा mtk_eth *eth, पूर्णांक mac_id);

पूर्णांक mtk_eth_offload_init(काष्ठा mtk_eth *eth);
पूर्णांक mtk_eth_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
		     व्योम *type_data);


#पूर्ण_अगर /* MTK_ETH_H */
