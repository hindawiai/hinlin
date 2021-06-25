<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014-2020 Broadcom
 */

#अगर_अघोषित __BCMGENET_H__
#घोषणा __BCMGENET_H__

#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/clk.h>
#समावेश <linux/mii.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/phy.h>
#समावेश <linux/dim.h>
#समावेश <linux/ethtool.h>

#समावेश "../unimac.h"

/* total number of Buffer Descriptors, same क्रम Rx/Tx */
#घोषणा TOTAL_DESC				256

/* which ring is descriptor based */
#घोषणा DESC_INDEX				16

/* Body(1500) + EH_SIZE(14) + VLANTAG(4) + BRCMTAG(6) + FCS(4) = 1528.
 * 1536 is multiple of 256 bytes
 */
#घोषणा ENET_BRCM_TAG_LEN	6
#घोषणा ENET_PAD		8
#घोषणा ENET_MAX_MTU_SIZE	(ETH_DATA_LEN + ETH_HLEN + VLAN_HLEN + \
				 ENET_BRCM_TAG_LEN + ETH_FCS_LEN + ENET_PAD)
#घोषणा DMA_MAX_BURST_LENGTH    0x10

/* misc. configuration */
#घोषणा MAX_NUM_OF_FS_RULES		16
#घोषणा CLEAR_ALL_HFB			0xFF
#घोषणा DMA_FC_THRESH_HI		(TOTAL_DESC >> 4)
#घोषणा DMA_FC_THRESH_LO		5

/* 64B receive/transmit status block */
काष्ठा status_64 अणु
	u32	length_status;		/* length and peripheral status */
	u32	ext_status;		/* Extended status*/
	u32	rx_csum;		/* partial rx checksum */
	u32	unused1[9];		/* unused */
	u32	tx_csum_info;		/* Tx checksum info. */
	u32	unused2[3];		/* unused */
पूर्ण;

/* Rx status bits */
#घोषणा STATUS_RX_EXT_MASK		0x1FFFFF
#घोषणा STATUS_RX_CSUM_MASK		0xFFFF
#घोषणा STATUS_RX_CSUM_OK		0x10000
#घोषणा STATUS_RX_CSUM_FR		0x20000
#घोषणा STATUS_RX_PROTO_TCP		0
#घोषणा STATUS_RX_PROTO_UDP		1
#घोषणा STATUS_RX_PROTO_ICMP		2
#घोषणा STATUS_RX_PROTO_OTHER		3
#घोषणा STATUS_RX_PROTO_MASK		3
#घोषणा STATUS_RX_PROTO_SHIFT		18
#घोषणा STATUS_FILTER_INDEX_MASK	0xFFFF
/* Tx status bits */
#घोषणा STATUS_TX_CSUM_START_MASK	0X7FFF
#घोषणा STATUS_TX_CSUM_START_SHIFT	16
#घोषणा STATUS_TX_CSUM_PROTO_UDP	0x8000
#घोषणा STATUS_TX_CSUM_OFFSET_MASK	0x7FFF
#घोषणा STATUS_TX_CSUM_LV		0x80000000

/* DMA Descriptor */
#घोषणा DMA_DESC_LENGTH_STATUS	0x00	/* in bytes of data in buffer */
#घोषणा DMA_DESC_ADDRESS_LO	0x04	/* lower bits of PA */
#घोषणा DMA_DESC_ADDRESS_HI	0x08	/* upper 32 bits of PA, GENETv4+ */

/* Rx/Tx common counter group */
काष्ठा bcmgenet_pkt_counters अणु
	u32	cnt_64;		/* RO Received/Transmited 64 bytes packet */
	u32	cnt_127;	/* RO Rx/Tx 127 bytes packet */
	u32	cnt_255;	/* RO Rx/Tx 65-255 bytes packet */
	u32	cnt_511;	/* RO Rx/Tx 256-511 bytes packet */
	u32	cnt_1023;	/* RO Rx/Tx 512-1023 bytes packet */
	u32	cnt_1518;	/* RO Rx/Tx 1024-1518 bytes packet */
	u32	cnt_mgv;	/* RO Rx/Tx 1519-1522 good VLAN packet */
	u32	cnt_2047;	/* RO Rx/Tx 1522-2047 bytes packet*/
	u32	cnt_4095;	/* RO Rx/Tx 2048-4095 bytes packet*/
	u32	cnt_9216;	/* RO Rx/Tx 4096-9216 bytes packet*/
पूर्ण;

/* RSV, Receive Status Vector */
काष्ठा bcmgenet_rx_counters अणु
	काष्ठा  bcmgenet_pkt_counters pkt_cnt;
	u32	pkt;		/* RO (0x428) Received pkt count*/
	u32	bytes;		/* RO Received byte count */
	u32	mca;		/* RO # of Received multicast pkt */
	u32	bca;		/* RO # of Receive broadcast pkt */
	u32	fcs;		/* RO # of Received FCS error  */
	u32	cf;		/* RO # of Received control frame pkt*/
	u32	pf;		/* RO # of Received छोड़ो frame pkt */
	u32	uo;		/* RO # of unknown op code pkt */
	u32	aln;		/* RO # of alignment error count */
	u32	flr;		/* RO # of frame length out of range count */
	u32	cde;		/* RO # of code error pkt */
	u32	fcr;		/* RO # of carrier sense error pkt */
	u32	ovr;		/* RO # of oversize pkt*/
	u32	jbr;		/* RO # of jabber count */
	u32	mtue;		/* RO # of MTU error pkt*/
	u32	pok;		/* RO # of Received good pkt */
	u32	uc;		/* RO # of unicast pkt */
	u32	ppp;		/* RO # of PPP pkt */
	u32	rcrc;		/* RO (0x470),# of CRC match pkt */
पूर्ण;

/* TSV, Transmit Status Vector */
काष्ठा bcmgenet_tx_counters अणु
	काष्ठा bcmgenet_pkt_counters pkt_cnt;
	u32	pkts;		/* RO (0x4a8) Transmited pkt */
	u32	mca;		/* RO # of xmited multicast pkt */
	u32	bca;		/* RO # of xmited broadcast pkt */
	u32	pf;		/* RO # of xmited छोड़ो frame count */
	u32	cf;		/* RO # of xmited control frame count */
	u32	fcs;		/* RO # of xmited FCS error count */
	u32	ovr;		/* RO # of xmited oversize pkt */
	u32	drf;		/* RO # of xmited deferral pkt */
	u32	edf;		/* RO # of xmited Excessive deferral pkt*/
	u32	scl;		/* RO # of xmited single collision pkt */
	u32	mcl;		/* RO # of xmited multiple collision pkt*/
	u32	lcl;		/* RO # of xmited late collision pkt */
	u32	ecl;		/* RO # of xmited excessive collision pkt*/
	u32	frg;		/* RO # of xmited fragments pkt*/
	u32	ncl;		/* RO # of xmited total collision count */
	u32	jbr;		/* RO # of xmited jabber count*/
	u32	bytes;		/* RO # of xmited byte count */
	u32	pok;		/* RO # of xmited good pkt */
	u32	uc;		/* RO (0x0x4f0)# of xmited unitcast pkt */
पूर्ण;

काष्ठा bcmgenet_mib_counters अणु
	काष्ठा bcmgenet_rx_counters rx;
	काष्ठा bcmgenet_tx_counters tx;
	u32	rx_runt_cnt;
	u32	rx_runt_fcs;
	u32	rx_runt_fcs_align;
	u32	rx_runt_bytes;
	u32	rbuf_ovflow_cnt;
	u32	rbuf_err_cnt;
	u32	mdf_err_cnt;
	u32	alloc_rx_buff_failed;
	u32	rx_dma_failed;
	u32	tx_dma_failed;
	u32	tx_पुनः_स्मृति_tsb;
	u32	tx_पुनः_स्मृति_tsb_failed;
पूर्ण;

#घोषणा UMAC_MIB_START			0x400

#घोषणा UMAC_MDIO_CMD			0x614
#घोषणा  MDIO_START_BUSY		(1 << 29)
#घोषणा  MDIO_READ_FAIL			(1 << 28)
#घोषणा  MDIO_RD			(2 << 26)
#घोषणा  MDIO_WR			(1 << 26)
#घोषणा  MDIO_PMD_SHIFT			21
#घोषणा  MDIO_PMD_MASK			0x1F
#घोषणा  MDIO_REG_SHIFT			16
#घोषणा  MDIO_REG_MASK			0x1F

#घोषणा UMAC_RBUF_OVFL_CNT_V1		0x61C
#घोषणा RBUF_OVFL_CNT_V2		0x80
#घोषणा RBUF_OVFL_CNT_V3PLUS		0x94

#घोषणा UMAC_MPD_CTRL			0x620
#घोषणा  MPD_EN				(1 << 0)
#घोषणा  MPD_PW_EN			(1 << 27)
#घोषणा  MPD_MSEQ_LEN_SHIFT		16
#घोषणा  MPD_MSEQ_LEN_MASK		0xFF

#घोषणा UMAC_MPD_PW_MS			0x624
#घोषणा UMAC_MPD_PW_LS			0x628
#घोषणा UMAC_RBUF_ERR_CNT_V1		0x634
#घोषणा RBUF_ERR_CNT_V2			0x84
#घोषणा RBUF_ERR_CNT_V3PLUS		0x98
#घोषणा UMAC_MDF_ERR_CNT		0x638
#घोषणा UMAC_MDF_CTRL			0x650
#घोषणा UMAC_MDF_ADDR			0x654
#घोषणा UMAC_MIB_CTRL			0x580
#घोषणा  MIB_RESET_RX			(1 << 0)
#घोषणा  MIB_RESET_RUNT			(1 << 1)
#घोषणा  MIB_RESET_TX			(1 << 2)

#घोषणा RBUF_CTRL			0x00
#घोषणा  RBUF_64B_EN			(1 << 0)
#घोषणा  RBUF_ALIGN_2B			(1 << 1)
#घोषणा  RBUF_BAD_DIS			(1 << 2)

#घोषणा RBUF_STATUS			0x0C
#घोषणा  RBUF_STATUS_WOL		(1 << 0)
#घोषणा  RBUF_STATUS_MPD_INTR_ACTIVE	(1 << 1)
#घोषणा  RBUF_STATUS_ACPI_INTR_ACTIVE	(1 << 2)

#घोषणा RBUF_CHK_CTRL			0x14
#घोषणा  RBUF_RXCHK_EN			(1 << 0)
#घोषणा  RBUF_SKIP_FCS			(1 << 4)
#घोषणा  RBUF_L3_PARSE_DIS		(1 << 5)

#घोषणा RBUF_ENERGY_CTRL		0x9c
#घोषणा  RBUF_EEE_EN			(1 << 0)
#घोषणा  RBUF_PM_EN			(1 << 1)

#घोषणा RBUF_TBUF_SIZE_CTRL		0xb4

#घोषणा RBUF_HFB_CTRL_V1		0x38
#घोषणा  RBUF_HFB_FILTER_EN_SHIFT	16
#घोषणा  RBUF_HFB_FILTER_EN_MASK	0xffff0000
#घोषणा  RBUF_HFB_EN			(1 << 0)
#घोषणा  RBUF_HFB_256B			(1 << 1)
#घोषणा  RBUF_ACPI_EN			(1 << 2)

#घोषणा RBUF_HFB_LEN_V1			0x3C
#घोषणा  RBUF_FLTR_LEN_MASK		0xFF
#घोषणा  RBUF_FLTR_LEN_SHIFT		8

#घोषणा TBUF_CTRL			0x00
#घोषणा  TBUF_64B_EN			(1 << 0)
#घोषणा TBUF_BP_MC			0x0C
#घोषणा TBUF_ENERGY_CTRL		0x14
#घोषणा  TBUF_EEE_EN			(1 << 0)
#घोषणा  TBUF_PM_EN			(1 << 1)

#घोषणा TBUF_CTRL_V1			0x80
#घोषणा TBUF_BP_MC_V1			0xA0

#घोषणा HFB_CTRL			0x00
#घोषणा HFB_FLT_ENABLE_V3PLUS		0x04
#घोषणा HFB_FLT_LEN_V2			0x04
#घोषणा HFB_FLT_LEN_V3PLUS		0x1C

/* uniMac पूर्णांकrl2 रेजिस्टरs */
#घोषणा INTRL2_CPU_STAT			0x00
#घोषणा INTRL2_CPU_SET			0x04
#घोषणा INTRL2_CPU_CLEAR		0x08
#घोषणा INTRL2_CPU_MASK_STATUS		0x0C
#घोषणा INTRL2_CPU_MASK_SET		0x10
#घोषणा INTRL2_CPU_MASK_CLEAR		0x14

/* INTRL2 instance 0 definitions */
#घोषणा UMAC_IRQ_SCB			(1 << 0)
#घोषणा UMAC_IRQ_EPHY			(1 << 1)
#घोषणा UMAC_IRQ_PHY_DET_R		(1 << 2)
#घोषणा UMAC_IRQ_PHY_DET_F		(1 << 3)
#घोषणा UMAC_IRQ_LINK_UP		(1 << 4)
#घोषणा UMAC_IRQ_LINK_DOWN		(1 << 5)
#घोषणा UMAC_IRQ_LINK_EVENT		(UMAC_IRQ_LINK_UP | UMAC_IRQ_LINK_DOWN)
#घोषणा UMAC_IRQ_UMAC			(1 << 6)
#घोषणा UMAC_IRQ_UMAC_TSV		(1 << 7)
#घोषणा UMAC_IRQ_TBUF_UNDERRUN		(1 << 8)
#घोषणा UMAC_IRQ_RBUF_OVERFLOW		(1 << 9)
#घोषणा UMAC_IRQ_HFB_SM			(1 << 10)
#घोषणा UMAC_IRQ_HFB_MM			(1 << 11)
#घोषणा UMAC_IRQ_MPD_R			(1 << 12)
#घोषणा UMAC_IRQ_WAKE_EVENT		(UMAC_IRQ_HFB_SM | UMAC_IRQ_HFB_MM | \
					 UMAC_IRQ_MPD_R)
#घोषणा UMAC_IRQ_RXDMA_MBDONE		(1 << 13)
#घोषणा UMAC_IRQ_RXDMA_PDONE		(1 << 14)
#घोषणा UMAC_IRQ_RXDMA_BDONE		(1 << 15)
#घोषणा UMAC_IRQ_RXDMA_DONE		UMAC_IRQ_RXDMA_MBDONE
#घोषणा UMAC_IRQ_TXDMA_MBDONE		(1 << 16)
#घोषणा UMAC_IRQ_TXDMA_PDONE		(1 << 17)
#घोषणा UMAC_IRQ_TXDMA_BDONE		(1 << 18)
#घोषणा UMAC_IRQ_TXDMA_DONE		UMAC_IRQ_TXDMA_MBDONE

/* Only valid क्रम GENETv3+ */
#घोषणा UMAC_IRQ_MDIO_DONE		(1 << 23)
#घोषणा UMAC_IRQ_MDIO_ERROR		(1 << 24)

/* INTRL2 instance 1 definitions */
#घोषणा UMAC_IRQ1_TX_INTR_MASK		0xFFFF
#घोषणा UMAC_IRQ1_RX_INTR_MASK		0xFFFF
#घोषणा UMAC_IRQ1_RX_INTR_SHIFT		16

/* Register block offsets */
#घोषणा GENET_SYS_OFF			0x0000
#घोषणा GENET_GR_BRIDGE_OFF		0x0040
#घोषणा GENET_EXT_OFF			0x0080
#घोषणा GENET_INTRL2_0_OFF		0x0200
#घोषणा GENET_INTRL2_1_OFF		0x0240
#घोषणा GENET_RBUF_OFF			0x0300
#घोषणा GENET_UMAC_OFF			0x0800

/* SYS block offsets and रेजिस्टर definitions */
#घोषणा SYS_REV_CTRL			0x00
#घोषणा SYS_PORT_CTRL			0x04
#घोषणा  PORT_MODE_INT_EPHY		0
#घोषणा  PORT_MODE_INT_GPHY		1
#घोषणा  PORT_MODE_EXT_EPHY		2
#घोषणा  PORT_MODE_EXT_GPHY		3
#घोषणा  PORT_MODE_EXT_RVMII_25		(4 | BIT(4))
#घोषणा  PORT_MODE_EXT_RVMII_50		4
#घोषणा  LED_ACT_SOURCE_MAC		(1 << 9)

#घोषणा SYS_RBUF_FLUSH_CTRL		0x08
#घोषणा SYS_TBUF_FLUSH_CTRL		0x0C
#घोषणा RBUF_FLUSH_CTRL_V1		0x04

/* Ext block रेजिस्टर offsets and definitions */
#घोषणा EXT_EXT_PWR_MGMT		0x00
#घोषणा  EXT_PWR_DOWN_BIAS		(1 << 0)
#घोषणा  EXT_PWR_DOWN_DLL		(1 << 1)
#घोषणा  EXT_PWR_DOWN_PHY		(1 << 2)
#घोषणा  EXT_PWR_DN_EN_LD		(1 << 3)
#घोषणा  EXT_ENERGY_DET			(1 << 4)
#घोषणा  EXT_IDDQ_FROM_PHY		(1 << 5)
#घोषणा  EXT_IDDQ_GLBL_PWR		(1 << 7)
#घोषणा  EXT_PHY_RESET			(1 << 8)
#घोषणा  EXT_ENERGY_DET_MASK		(1 << 12)
#घोषणा  EXT_PWR_DOWN_PHY_TX		(1 << 16)
#घोषणा  EXT_PWR_DOWN_PHY_RX		(1 << 17)
#घोषणा  EXT_PWR_DOWN_PHY_SD		(1 << 18)
#घोषणा  EXT_PWR_DOWN_PHY_RD		(1 << 19)
#घोषणा  EXT_PWR_DOWN_PHY_EN		(1 << 20)

#घोषणा EXT_RGMII_OOB_CTRL		0x0C
#घोषणा  RGMII_MODE_EN_V123		(1 << 0)
#घोषणा  RGMII_LINK			(1 << 4)
#घोषणा  OOB_DISABLE			(1 << 5)
#घोषणा  RGMII_MODE_EN			(1 << 6)
#घोषणा  ID_MODE_DIS			(1 << 16)

#घोषणा EXT_GPHY_CTRL			0x1C
#घोषणा  EXT_CFG_IDDQ_BIAS		(1 << 0)
#घोषणा  EXT_CFG_PWR_DOWN		(1 << 1)
#घोषणा  EXT_CK25_DIS			(1 << 4)
#घोषणा  EXT_GPHY_RESET			(1 << 5)

/* DMA rings size */
#घोषणा DMA_RING_SIZE			(0x40)
#घोषणा DMA_RINGS_SIZE			(DMA_RING_SIZE * (DESC_INDEX + 1))

/* DMA रेजिस्टरs common definitions */
#घोषणा DMA_RW_POINTER_MASK		0x1FF
#घोषणा DMA_P_INDEX_DISCARD_CNT_MASK	0xFFFF
#घोषणा DMA_P_INDEX_DISCARD_CNT_SHIFT	16
#घोषणा DMA_BUFFER_DONE_CNT_MASK	0xFFFF
#घोषणा DMA_BUFFER_DONE_CNT_SHIFT	16
#घोषणा DMA_P_INDEX_MASK		0xFFFF
#घोषणा DMA_C_INDEX_MASK		0xFFFF

/* DMA ring size रेजिस्टर */
#घोषणा DMA_RING_SIZE_MASK		0xFFFF
#घोषणा DMA_RING_SIZE_SHIFT		16
#घोषणा DMA_RING_BUFFER_SIZE_MASK	0xFFFF

/* DMA पूर्णांकerrupt threshold रेजिस्टर */
#घोषणा DMA_INTR_THRESHOLD_MASK		0x01FF

/* DMA XON/XOFF रेजिस्टर */
#घोषणा DMA_XON_THREHOLD_MASK		0xFFFF
#घोषणा DMA_XOFF_THRESHOLD_MASK		0xFFFF
#घोषणा DMA_XOFF_THRESHOLD_SHIFT	16

/* DMA flow period रेजिस्टर */
#घोषणा DMA_FLOW_PERIOD_MASK		0xFFFF
#घोषणा DMA_MAX_PKT_SIZE_MASK		0xFFFF
#घोषणा DMA_MAX_PKT_SIZE_SHIFT		16


/* DMA control रेजिस्टर */
#घोषणा DMA_EN				(1 << 0)
#घोषणा DMA_RING_BUF_EN_SHIFT		0x01
#घोषणा DMA_RING_BUF_EN_MASK		0xFFFF
#घोषणा DMA_TSB_SWAP_EN			(1 << 20)

/* DMA status रेजिस्टर */
#घोषणा DMA_DISABLED			(1 << 0)
#घोषणा DMA_DESC_RAM_INIT_BUSY		(1 << 1)

/* DMA SCB burst size रेजिस्टर */
#घोषणा DMA_SCB_BURST_SIZE_MASK		0x1F

/* DMA activity vector रेजिस्टर */
#घोषणा DMA_ACTIVITY_VECTOR_MASK	0x1FFFF

/* DMA backpressure mask रेजिस्टर */
#घोषणा DMA_BACKPRESSURE_MASK		0x1FFFF
#घोषणा DMA_PFC_ENABLE			(1 << 31)

/* DMA backpressure status रेजिस्टर */
#घोषणा DMA_BACKPRESSURE_STATUS_MASK	0x1FFFF

/* DMA override रेजिस्टर */
#घोषणा DMA_LITTLE_ENDIAN_MODE		(1 << 0)
#घोषणा DMA_REGISTER_MODE		(1 << 1)

/* DMA समयout रेजिस्टर */
#घोषणा DMA_TIMEOUT_MASK		0xFFFF
#घोषणा DMA_TIMEOUT_VAL			5000	/* micro seconds */

/* TDMA rate limiting control रेजिस्टर */
#घोषणा DMA_RATE_LIMIT_EN_MASK		0xFFFF

/* TDMA arbitration control रेजिस्टर */
#घोषणा DMA_ARBITER_MODE_MASK		0x03
#घोषणा DMA_RING_BUF_PRIORITY_MASK	0x1F
#घोषणा DMA_RING_BUF_PRIORITY_SHIFT	5
#घोषणा DMA_PRIO_REG_INDEX(q)		((q) / 6)
#घोषणा DMA_PRIO_REG_SHIFT(q)		(((q) % 6) * DMA_RING_BUF_PRIORITY_SHIFT)
#घोषणा DMA_RATE_ADJ_MASK		0xFF

/* Tx/Rx Dma Descriptor common bits*/
#घोषणा DMA_BUFLENGTH_MASK		0x0fff
#घोषणा DMA_BUFLENGTH_SHIFT		16
#घोषणा DMA_OWN				0x8000
#घोषणा DMA_EOP				0x4000
#घोषणा DMA_SOP				0x2000
#घोषणा DMA_WRAP			0x1000
/* Tx specअगरic Dma descriptor bits */
#घोषणा DMA_TX_UNDERRUN			0x0200
#घोषणा DMA_TX_APPEND_CRC		0x0040
#घोषणा DMA_TX_OW_CRC			0x0020
#घोषणा DMA_TX_DO_CSUM			0x0010
#घोषणा DMA_TX_QTAG_SHIFT		7

/* Rx Specअगरic Dma descriptor bits */
#घोषणा DMA_RX_CHK_V3PLUS		0x8000
#घोषणा DMA_RX_CHK_V12			0x1000
#घोषणा DMA_RX_BRDCAST			0x0040
#घोषणा DMA_RX_MULT			0x0020
#घोषणा DMA_RX_LG			0x0010
#घोषणा DMA_RX_NO			0x0008
#घोषणा DMA_RX_RXER			0x0004
#घोषणा DMA_RX_CRC_ERROR		0x0002
#घोषणा DMA_RX_OV			0x0001
#घोषणा DMA_RX_FI_MASK			0x001F
#घोषणा DMA_RX_FI_SHIFT			0x0007
#घोषणा DMA_DESC_ALLOC_MASK		0x00FF

#घोषणा DMA_ARBITER_RR			0x00
#घोषणा DMA_ARBITER_WRR			0x01
#घोषणा DMA_ARBITER_SP			0x02

काष्ठा enet_cb अणु
	काष्ठा sk_buff      *skb;
	व्योम __iomem *bd_addr;
	DEFINE_DMA_UNMAP_ADDR(dma_addr);
	DEFINE_DMA_UNMAP_LEN(dma_len);
पूर्ण;

/* घातer management mode */
क्रमागत bcmgenet_घातer_mode अणु
	GENET_POWER_CABLE_SENSE = 0,
	GENET_POWER_PASSIVE,
	GENET_POWER_WOL_MAGIC,
पूर्ण;

काष्ठा bcmgenet_priv;

/* We support both runसमय GENET detection and compile-समय
 * to optimize code-paths क्रम a given hardware
 */
क्रमागत bcmgenet_version अणु
	GENET_V1 = 1,
	GENET_V2,
	GENET_V3,
	GENET_V4,
	GENET_V5
पूर्ण;

#घोषणा GENET_IS_V1(p)	((p)->version == GENET_V1)
#घोषणा GENET_IS_V2(p)	((p)->version == GENET_V2)
#घोषणा GENET_IS_V3(p)	((p)->version == GENET_V3)
#घोषणा GENET_IS_V4(p)	((p)->version == GENET_V4)
#घोषणा GENET_IS_V5(p)	((p)->version == GENET_V5)

/* Hardware flags */
#घोषणा GENET_HAS_40BITS	(1 << 0)
#घोषणा GENET_HAS_EXT		(1 << 1)
#घोषणा GENET_HAS_MDIO_INTR	(1 << 2)
#घोषणा GENET_HAS_MOCA_LINK_DET	(1 << 3)

/* BCMGENET hardware parameters, keep this काष्ठाure nicely aligned
 * since it is going to be used in hot paths
 */
काष्ठा bcmgenet_hw_params अणु
	u8		tx_queues;
	u8		tx_bds_per_q;
	u8		rx_queues;
	u8		rx_bds_per_q;
	u8		bp_in_en_shअगरt;
	u32		bp_in_mask;
	u8		hfb_filter_cnt;
	u8		hfb_filter_size;
	u8		qtag_mask;
	u16		tbuf_offset;
	u32		hfb_offset;
	u32		hfb_reg_offset;
	u32		rdma_offset;
	u32		tdma_offset;
	u32		words_per_bd;
	u32		flags;
पूर्ण;

काष्ठा bcmgenet_skb_cb अणु
	काष्ठा enet_cb *first_cb;	/* First control block of SKB */
	काष्ठा enet_cb *last_cb;	/* Last control block of SKB */
	अचिन्हित पूर्णांक bytes_sent;	/* bytes on the wire (no TSB) */
पूर्ण;

#घोषणा GENET_CB(skb)	((काष्ठा bcmgenet_skb_cb *)((skb)->cb))

काष्ठा bcmgenet_tx_ring अणु
	spinlock_t	lock;		/* ring lock */
	काष्ठा napi_काष्ठा napi;	/* NAPI per tx queue */
	अचिन्हित दीर्घ	packets;
	अचिन्हित दीर्घ	bytes;
	अचिन्हित पूर्णांक	index;		/* ring index */
	अचिन्हित पूर्णांक	queue;		/* queue index */
	काष्ठा enet_cb	*cbs;		/* tx ring buffer control block*/
	अचिन्हित पूर्णांक	size;		/* size of each tx ring */
	अचिन्हित पूर्णांक    clean_ptr;      /* Tx ring clean poपूर्णांकer */
	अचिन्हित पूर्णांक	c_index;	/* last consumer index of each ring*/
	अचिन्हित पूर्णांक	मुक्त_bds;	/* # of मुक्त bds क्रम each ring */
	अचिन्हित पूर्णांक	ग_लिखो_ptr;	/* Tx ring ग_लिखो poपूर्णांकer SW copy */
	अचिन्हित पूर्णांक	prod_index;	/* Tx ring producer index SW copy */
	अचिन्हित पूर्णांक	cb_ptr;		/* Tx ring initial CB ptr */
	अचिन्हित पूर्णांक	end_ptr;	/* Tx ring end CB ptr */
	व्योम (*पूर्णांक_enable)(काष्ठा bcmgenet_tx_ring *);
	व्योम (*पूर्णांक_disable)(काष्ठा bcmgenet_tx_ring *);
	काष्ठा bcmgenet_priv *priv;
पूर्ण;

काष्ठा bcmgenet_net_dim अणु
	u16		use_dim;
	u16		event_ctr;
	अचिन्हित दीर्घ	packets;
	अचिन्हित दीर्घ	bytes;
	काष्ठा dim	dim;
पूर्ण;

काष्ठा bcmgenet_rx_ring अणु
	काष्ठा napi_काष्ठा napi;	/* Rx NAPI काष्ठा */
	अचिन्हित दीर्घ	bytes;
	अचिन्हित दीर्घ	packets;
	अचिन्हित दीर्घ	errors;
	अचिन्हित दीर्घ	dropped;
	अचिन्हित पूर्णांक	index;		/* Rx ring index */
	काष्ठा enet_cb	*cbs;		/* Rx ring buffer control block */
	अचिन्हित पूर्णांक	size;		/* Rx ring size */
	अचिन्हित पूर्णांक	c_index;	/* Rx last consumer index */
	अचिन्हित पूर्णांक	पढ़ो_ptr;	/* Rx ring पढ़ो poपूर्णांकer */
	अचिन्हित पूर्णांक	cb_ptr;		/* Rx ring initial CB ptr */
	अचिन्हित पूर्णांक	end_ptr;	/* Rx ring end CB ptr */
	अचिन्हित पूर्णांक	old_discards;
	काष्ठा bcmgenet_net_dim dim;
	u32		rx_max_coalesced_frames;
	u32		rx_coalesce_usecs;
	व्योम (*पूर्णांक_enable)(काष्ठा bcmgenet_rx_ring *);
	व्योम (*पूर्णांक_disable)(काष्ठा bcmgenet_rx_ring *);
	काष्ठा bcmgenet_priv *priv;
पूर्ण;

क्रमागत bcmgenet_rxnfc_state अणु
	BCMGENET_RXNFC_STATE_UNUSED = 0,
	BCMGENET_RXNFC_STATE_DISABLED,
	BCMGENET_RXNFC_STATE_ENABLED
पूर्ण;

काष्ठा bcmgenet_rxnfc_rule अणु
	काष्ठा	list_head list;
	काष्ठा ethtool_rx_flow_spec	fs;
	क्रमागत bcmgenet_rxnfc_state state;
पूर्ण;

/* device context */
काष्ठा bcmgenet_priv अणु
	व्योम __iomem *base;
	क्रमागत bcmgenet_version version;
	काष्ठा net_device *dev;

	/* transmit variables */
	व्योम __iomem *tx_bds;
	काष्ठा enet_cb *tx_cbs;
	अचिन्हित पूर्णांक num_tx_bds;

	काष्ठा bcmgenet_tx_ring tx_rings[DESC_INDEX + 1];

	/* receive variables */
	व्योम __iomem *rx_bds;
	काष्ठा enet_cb *rx_cbs;
	अचिन्हित पूर्णांक num_rx_bds;
	अचिन्हित पूर्णांक rx_buf_len;
	काष्ठा bcmgenet_rxnfc_rule rxnfc_rules[MAX_NUM_OF_FS_RULES];
	काष्ठा list_head rxnfc_list;

	काष्ठा bcmgenet_rx_ring rx_rings[DESC_INDEX + 1];

	/* other misc variables */
	काष्ठा bcmgenet_hw_params *hw_params;

	/* MDIO bus variables */
	रुको_queue_head_t wq;
	bool पूर्णांकernal_phy;
	काष्ठा device_node *phy_dn;
	काष्ठा device_node *mdio_dn;
	काष्ठा mii_bus *mii_bus;
	u16 gphy_rev;
	काष्ठा clk *clk_eee;
	bool clk_eee_enabled;

	/* PHY device variables */
	पूर्णांक old_link;
	पूर्णांक old_speed;
	पूर्णांक old_duplex;
	पूर्णांक old_छोड़ो;
	phy_पूर्णांकerface_t phy_पूर्णांकerface;
	पूर्णांक phy_addr;
	पूर्णांक ext_phy;

	/* Interrupt variables */
	काष्ठा work_काष्ठा bcmgenet_irq_work;
	पूर्णांक irq0;
	पूर्णांक irq1;
	पूर्णांक wol_irq;
	bool wol_irq_disabled;

	/* shared status */
	spinlock_t lock;
	अचिन्हित पूर्णांक irq0_stat;

	/* HW descriptors/checksum variables */
	bool crc_fwd_en;

	u32 dma_max_burst_length;

	u32 msg_enable;

	काष्ठा clk *clk;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा platक्रमm_device *mii_pdev;

	/* WOL */
	काष्ठा clk *clk_wol;
	u32 wolopts;
	u8 sopass[SOPASS_MAX];
	bool wol_active;

	काष्ठा bcmgenet_mib_counters mib;

	काष्ठा ethtool_eee eee;
पूर्ण;

#घोषणा GENET_IO_MACRO(name, offset)					\
अटल अंतरभूत u32 bcmgenet_##name##_पढ़ोl(काष्ठा bcmgenet_priv *priv,	\
					u32 off)			\
अणु									\
	/* MIPS chips strapped क्रम BE will स्वतःmagically configure the	\
	 * peripheral रेजिस्टरs क्रम CPU-native byte order.		\
	 */								\
	अगर (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN)) \
		वापस __raw_पढ़ोl(priv->base + offset + off);		\
	अन्यथा								\
		वापस पढ़ोl_relaxed(priv->base + offset + off);	\
पूर्ण									\
अटल अंतरभूत व्योम bcmgenet_##name##_ग_लिखोl(काष्ठा bcmgenet_priv *priv,	\
					u32 val, u32 off)		\
अणु									\
	अगर (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN)) \
		__raw_ग_लिखोl(val, priv->base + offset + off);		\
	अन्यथा								\
		ग_लिखोl_relaxed(val, priv->base + offset + off);		\
पूर्ण

GENET_IO_MACRO(ext, GENET_EXT_OFF);
GENET_IO_MACRO(umac, GENET_UMAC_OFF);
GENET_IO_MACRO(sys, GENET_SYS_OFF);

/* पूर्णांकerrupt l2 रेजिस्टरs accessors */
GENET_IO_MACRO(पूर्णांकrl2_0, GENET_INTRL2_0_OFF);
GENET_IO_MACRO(पूर्णांकrl2_1, GENET_INTRL2_1_OFF);

/* HFB रेजिस्टर accessors  */
GENET_IO_MACRO(hfb, priv->hw_params->hfb_offset);

/* GENET v2+ HFB control and filter len helpers */
GENET_IO_MACRO(hfb_reg, priv->hw_params->hfb_reg_offset);

/* RBUF रेजिस्टर accessors */
GENET_IO_MACRO(rbuf, GENET_RBUF_OFF);

/* MDIO routines */
पूर्णांक bcmgenet_mii_init(काष्ठा net_device *dev);
पूर्णांक bcmgenet_mii_config(काष्ठा net_device *dev, bool init);
पूर्णांक bcmgenet_mii_probe(काष्ठा net_device *dev);
व्योम bcmgenet_mii_निकास(काष्ठा net_device *dev);
व्योम bcmgenet_phy_घातer_set(काष्ठा net_device *dev, bool enable);
व्योम bcmgenet_mii_setup(काष्ठा net_device *dev);

/* Wake-on-LAN routines */
व्योम bcmgenet_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol);
पूर्णांक bcmgenet_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol);
पूर्णांक bcmgenet_wol_घातer_करोwn_cfg(काष्ठा bcmgenet_priv *priv,
				क्रमागत bcmgenet_घातer_mode mode);
व्योम bcmgenet_wol_घातer_up_cfg(काष्ठा bcmgenet_priv *priv,
			       क्रमागत bcmgenet_घातer_mode mode);

#पूर्ण_अगर /* __BCMGENET_H__ */
