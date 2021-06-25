<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Dave DNET Ethernet Controller driver
 *
 * Copyright (C) 2008 Dave S.r.l. <www.dave.eu>
 */
#अगर_अघोषित _DNET_H
#घोषणा _DNET_H

#घोषणा DRV_NAME		"dnet"
#घोषणा PFX				DRV_NAME ": "

/* Register access macros */
#घोषणा dnet_ग_लिखोl(port, value, reg)	\
	ग_लिखोl((value), (port)->regs + DNET_##reg)
#घोषणा dnet_पढ़ोl(port, reg)	पढ़ोl((port)->regs + DNET_##reg)

/* ALL DNET FIFO REGISTERS */
#घोषणा DNET_RX_LEN_FIFO		0x000	/* RX_LEN_FIFO */
#घोषणा DNET_RX_DATA_FIFO		0x004	/* RX_DATA_FIFO */
#घोषणा DNET_TX_LEN_FIFO		0x008	/* TX_LEN_FIFO */
#घोषणा DNET_TX_DATA_FIFO		0x00C	/* TX_DATA_FIFO */

/* ALL DNET CONTROL/STATUS REGISTERS OFFSETS */
#घोषणा DNET_VERCAPS			0x100	/* VERCAPS */
#घोषणा DNET_INTR_SRC			0x104	/* INTR_SRC */
#घोषणा DNET_INTR_ENB			0x108	/* INTR_ENB */
#घोषणा DNET_RX_STATUS			0x10C	/* RX_STATUS */
#घोषणा DNET_TX_STATUS			0x110	/* TX_STATUS */
#घोषणा DNET_RX_FRAMES_CNT		0x114	/* RX_FRAMES_CNT */
#घोषणा DNET_TX_FRAMES_CNT		0x118	/* TX_FRAMES_CNT */
#घोषणा DNET_RX_FIFO_TH			0x11C	/* RX_FIFO_TH */
#घोषणा DNET_TX_FIFO_TH			0x120	/* TX_FIFO_TH */
#घोषणा DNET_SYS_CTL			0x124	/* SYS_CTL */
#घोषणा DNET_PAUSE_TMR			0x128	/* PAUSE_TMR */
#घोषणा DNET_RX_FIFO_WCNT		0x12C	/* RX_FIFO_WCNT */
#घोषणा DNET_TX_FIFO_WCNT		0x130	/* TX_FIFO_WCNT */

/* ALL DNET MAC REGISTERS */
#घोषणा DNET_MACREG_DATA		0x200	/* Mac-Reg Data */
#घोषणा DNET_MACREG_ADDR		0x204	/* Mac-Reg Addr  */

/* ALL DNET RX STATISTICS COUNTERS  */
#घोषणा DNET_RX_PKT_IGNR_CNT		0x300
#घोषणा DNET_RX_LEN_CHK_ERR_CNT		0x304
#घोषणा DNET_RX_LNG_FRM_CNT		0x308
#घोषणा DNET_RX_SHRT_FRM_CNT		0x30C
#घोषणा DNET_RX_IPG_VIOL_CNT		0x310
#घोषणा DNET_RX_CRC_ERR_CNT		0x314
#घोषणा DNET_RX_OK_PKT_CNT		0x318
#घोषणा DNET_RX_CTL_FRM_CNT		0x31C
#घोषणा DNET_RX_PAUSE_FRM_CNT		0x320
#घोषणा DNET_RX_MULTICAST_CNT		0x324
#घोषणा DNET_RX_BROADCAST_CNT		0x328
#घोषणा DNET_RX_VLAN_TAG_CNT		0x32C
#घोषणा DNET_RX_PRE_SHRINK_CNT		0x330
#घोषणा DNET_RX_DRIB_NIB_CNT		0x334
#घोषणा DNET_RX_UNSUP_OPCD_CNT		0x338
#घोषणा DNET_RX_BYTE_CNT		0x33C

/* DNET TX STATISTICS COUNTERS */
#घोषणा DNET_TX_UNICAST_CNT		0x400
#घोषणा DNET_TX_PAUSE_FRM_CNT		0x404
#घोषणा DNET_TX_MULTICAST_CNT		0x408
#घोषणा DNET_TX_BRDCAST_CNT		0x40C
#घोषणा DNET_TX_VLAN_TAG_CNT		0x410
#घोषणा DNET_TX_BAD_FCS_CNT		0x414
#घोषणा DNET_TX_JUMBO_CNT		0x418
#घोषणा DNET_TX_BYTE_CNT		0x41C

/* SOME INTERNAL MAC-CORE REGISTER */
#घोषणा DNET_INTERNAL_MODE_REG		0x0
#घोषणा DNET_INTERNAL_RXTX_CONTROL_REG	0x2
#घोषणा DNET_INTERNAL_MAX_PKT_SIZE_REG	0x4
#घोषणा DNET_INTERNAL_IGP_REG		0x8
#घोषणा DNET_INTERNAL_MAC_ADDR_0_REG	0xa
#घोषणा DNET_INTERNAL_MAC_ADDR_1_REG	0xc
#घोषणा DNET_INTERNAL_MAC_ADDR_2_REG	0xe
#घोषणा DNET_INTERNAL_TX_RX_STS_REG	0x12
#घोषणा DNET_INTERNAL_GMII_MNG_CTL_REG	0x14
#घोषणा DNET_INTERNAL_GMII_MNG_DAT_REG	0x16

#घोषणा DNET_INTERNAL_GMII_MNG_CMD_FIN	(1 << 14)

#घोषणा DNET_INTERNAL_WRITE		(1 << 31)

/* MAC-CORE REGISTER FIELDS */

/* MAC-CORE MODE REGISTER FIELDS */
#घोषणा DNET_INTERNAL_MODE_GBITEN			(1 << 0)
#घोषणा DNET_INTERNAL_MODE_FCEN				(1 << 1)
#घोषणा DNET_INTERNAL_MODE_RXEN				(1 << 2)
#घोषणा DNET_INTERNAL_MODE_TXEN				(1 << 3)

/* MAC-CORE RXTX CONTROL REGISTER FIELDS */
#घोषणा DNET_INTERNAL_RXTX_CONTROL_RXSHORTFRAME		(1 << 8)
#घोषणा DNET_INTERNAL_RXTX_CONTROL_RXBROADCAST		(1 << 7)
#घोषणा DNET_INTERNAL_RXTX_CONTROL_RXMULTICAST		(1 << 4)
#घोषणा DNET_INTERNAL_RXTX_CONTROL_RXPAUSE		(1 << 3)
#घोषणा DNET_INTERNAL_RXTX_CONTROL_DISTXFCS		(1 << 2)
#घोषणा DNET_INTERNAL_RXTX_CONTROL_DISCFXFCS		(1 << 1)
#घोषणा DNET_INTERNAL_RXTX_CONTROL_ENPROMISC		(1 << 0)
#घोषणा DNET_INTERNAL_RXTX_CONTROL_DROPCONTROL		(1 << 6)
#घोषणा DNET_INTERNAL_RXTX_CONTROL_ENABLEHALFDUP	(1 << 5)

/* SYSTEM CONTROL REGISTER FIELDS */
#घोषणा DNET_SYS_CTL_IGNORENEXTPKT			(1 << 0)
#घोषणा DNET_SYS_CTL_SENDPAUSE				(1 << 2)
#घोषणा DNET_SYS_CTL_RXFIFOFLUSH			(1 << 3)
#घोषणा DNET_SYS_CTL_TXFIFOFLUSH			(1 << 4)

/* TX STATUS REGISTER FIELDS */
#घोषणा DNET_TX_STATUS_FIFO_ALMOST_EMPTY		(1 << 2)
#घोषणा DNET_TX_STATUS_FIFO_ALMOST_FULL			(1 << 1)

/* INTERRUPT SOURCE REGISTER FIELDS */
#घोषणा DNET_INTR_SRC_TX_PKTSENT			(1 << 0)
#घोषणा DNET_INTR_SRC_TX_FIFOAF				(1 << 1)
#घोषणा DNET_INTR_SRC_TX_FIFOAE				(1 << 2)
#घोषणा DNET_INTR_SRC_TX_DISCFRM			(1 << 3)
#घोषणा DNET_INTR_SRC_TX_FIFOFULL			(1 << 4)
#घोषणा DNET_INTR_SRC_RX_CMDFIFOAF			(1 << 8)
#घोषणा DNET_INTR_SRC_RX_CMDFIFOFF			(1 << 9)
#घोषणा DNET_INTR_SRC_RX_DATAFIFOFF			(1 << 10)
#घोषणा DNET_INTR_SRC_TX_SUMMARY			(1 << 16)
#घोषणा DNET_INTR_SRC_RX_SUMMARY			(1 << 17)
#घोषणा DNET_INTR_SRC_PHY				(1 << 19)

/* INTERRUPT ENABLE REGISTER FIELDS */
#घोषणा DNET_INTR_ENB_TX_PKTSENT			(1 << 0)
#घोषणा DNET_INTR_ENB_TX_FIFOAF				(1 << 1)
#घोषणा DNET_INTR_ENB_TX_FIFOAE				(1 << 2)
#घोषणा DNET_INTR_ENB_TX_DISCFRM			(1 << 3)
#घोषणा DNET_INTR_ENB_TX_FIFOFULL			(1 << 4)
#घोषणा DNET_INTR_ENB_RX_PKTRDY				(1 << 8)
#घोषणा DNET_INTR_ENB_RX_FIFOAF				(1 << 9)
#घोषणा DNET_INTR_ENB_RX_FIFOERR			(1 << 10)
#घोषणा DNET_INTR_ENB_RX_ERROR				(1 << 11)
#घोषणा DNET_INTR_ENB_RX_FIFOFULL			(1 << 12)
#घोषणा DNET_INTR_ENB_RX_FIFOAE				(1 << 13)
#घोषणा DNET_INTR_ENB_TX_SUMMARY			(1 << 16)
#घोषणा DNET_INTR_ENB_RX_SUMMARY			(1 << 17)
#घोषणा DNET_INTR_ENB_GLOBAL_ENABLE			(1 << 18)

/* शेष values:
 * almost empty = less than one full sized ethernet frame (no jumbo) inside
 * the fअगरo almost full = can ग_लिखो less than one full sized ethernet frame
 * (no jumbo) inside the fअगरo
 */
#घोषणा DNET_CFG_TX_FIFO_FULL_THRES	25
#घोषणा DNET_CFG_RX_FIFO_FULL_THRES	20

/*
 * Capabilities. Used by the driver to know the capabilities that the ethernet
 * controller inside the FPGA have.
 */

#घोषणा DNET_HAS_MDIO		(1 << 0)
#घोषणा DNET_HAS_IRQ		(1 << 1)
#घोषणा DNET_HAS_GIGABIT	(1 << 2)
#घोषणा DNET_HAS_DMA		(1 << 3)

#घोषणा DNET_HAS_MII		(1 << 4) /* or GMII */
#घोषणा DNET_HAS_RMII		(1 << 5) /* or RGMII */

#घोषणा DNET_CAPS_MASK		0xFFFF

#घोषणा DNET_FIFO_SIZE		1024 /* 1K x 32 bit */
#घोषणा DNET_FIFO_TX_DATA_AF_TH	(DNET_FIFO_SIZE - 384) /* 384 = 1536 / 4 */
#घोषणा DNET_FIFO_TX_DATA_AE_TH	384

#घोषणा DNET_FIFO_RX_CMD_AF_TH	(1 << 16) /* just one frame inside the FIFO */

/*
 * Hardware-collected statistics.
 */
काष्ठा dnet_stats अणु
	u32 rx_pkt_ignr;
	u32 rx_len_chk_err;
	u32 rx_lng_frm;
	u32 rx_shrt_frm;
	u32 rx_ipg_viol;
	u32 rx_crc_err;
	u32 rx_ok_pkt;
	u32 rx_ctl_frm;
	u32 rx_छोड़ो_frm;
	u32 rx_multicast;
	u32 rx_broadcast;
	u32 rx_vlan_tag;
	u32 rx_pre_shrink;
	u32 rx_drib_nib;
	u32 rx_unsup_opcd;
	u32 rx_byte;
	u32 tx_unicast;
	u32 tx_छोड़ो_frm;
	u32 tx_multicast;
	u32 tx_brdcast;
	u32 tx_vlan_tag;
	u32 tx_bad_fcs;
	u32 tx_jumbo;
	u32 tx_byte;
पूर्ण;

काष्ठा dnet अणु
	व्योम __iomem			*regs;
	spinlock_t			lock;
	काष्ठा platक्रमm_device		*pdev;
	काष्ठा net_device		*dev;
	काष्ठा dnet_stats		hw_stats;
	अचिन्हित पूर्णांक			capabilities; /* पढ़ो from FPGA */
	काष्ठा napi_काष्ठा		napi;

	/* PHY stuff */
	काष्ठा mii_bus			*mii_bus;
	अचिन्हित पूर्णांक			link;
	अचिन्हित पूर्णांक			speed;
	अचिन्हित पूर्णांक			duplex;
पूर्ण;

#पूर्ण_अगर /* _DNET_H */
