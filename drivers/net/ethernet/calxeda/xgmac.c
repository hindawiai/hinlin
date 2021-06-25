<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2010-2011 Calxeda, Inc.
 */
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/kernel.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर.h>
#समावेश <linux/crc32.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>

/* XGMAC Register definitions */
#घोषणा XGMAC_CONTROL		0x00000000	/* MAC Configuration */
#घोषणा XGMAC_FRAME_FILTER	0x00000004	/* MAC Frame Filter */
#घोषणा XGMAC_FLOW_CTRL		0x00000018	/* MAC Flow Control */
#घोषणा XGMAC_VLAN_TAG		0x0000001C	/* VLAN Tags */
#घोषणा XGMAC_VERSION		0x00000020	/* Version */
#घोषणा XGMAC_VLAN_INCL		0x00000024	/* VLAN tag क्रम tx frames */
#घोषणा XGMAC_LPI_CTRL		0x00000028	/* LPI Control and Status */
#घोषणा XGMAC_LPI_TIMER		0x0000002C	/* LPI Timers Control */
#घोषणा XGMAC_TX_PACE		0x00000030	/* Transmit Pace and Stretch */
#घोषणा XGMAC_VLAN_HASH		0x00000034	/* VLAN Hash Table */
#घोषणा XGMAC_DEBUG		0x00000038	/* Debug */
#घोषणा XGMAC_INT_STAT		0x0000003C	/* Interrupt and Control */
#घोषणा XGMAC_ADDR_HIGH(reg)	(0x00000040 + ((reg) * 8))
#घोषणा XGMAC_ADDR_LOW(reg)	(0x00000044 + ((reg) * 8))
#घोषणा XGMAC_HASH(n)		(0x00000300 + (n) * 4) /* HASH table regs */
#घोषणा XGMAC_NUM_HASH		16
#घोषणा XGMAC_OMR		0x00000400
#घोषणा XGMAC_REMOTE_WAKE	0x00000700	/* Remote Wake-Up Frm Filter */
#घोषणा XGMAC_PMT		0x00000704	/* PMT Control and Status */
#घोषणा XGMAC_MMC_CTRL		0x00000800	/* XGMAC MMC Control */
#घोषणा XGMAC_MMC_INTR_RX	0x00000804	/* Receive Interrupt */
#घोषणा XGMAC_MMC_INTR_TX	0x00000808	/* Transmit Interrupt */
#घोषणा XGMAC_MMC_INTR_MASK_RX	0x0000080c	/* Receive Interrupt Mask */
#घोषणा XGMAC_MMC_INTR_MASK_TX	0x00000810	/* Transmit Interrupt Mask */

/* Hardware TX Statistics Counters */
#घोषणा XGMAC_MMC_TXOCTET_GB_LO	0x00000814
#घोषणा XGMAC_MMC_TXOCTET_GB_HI	0x00000818
#घोषणा XGMAC_MMC_TXFRAME_GB_LO	0x0000081C
#घोषणा XGMAC_MMC_TXFRAME_GB_HI	0x00000820
#घोषणा XGMAC_MMC_TXBCFRAME_G	0x00000824
#घोषणा XGMAC_MMC_TXMCFRAME_G	0x0000082C
#घोषणा XGMAC_MMC_TXUCFRAME_GB	0x00000864
#घोषणा XGMAC_MMC_TXMCFRAME_GB	0x0000086C
#घोषणा XGMAC_MMC_TXBCFRAME_GB	0x00000874
#घोषणा XGMAC_MMC_TXUNDERFLOW	0x0000087C
#घोषणा XGMAC_MMC_TXOCTET_G_LO	0x00000884
#घोषणा XGMAC_MMC_TXOCTET_G_HI	0x00000888
#घोषणा XGMAC_MMC_TXFRAME_G_LO	0x0000088C
#घोषणा XGMAC_MMC_TXFRAME_G_HI	0x00000890
#घोषणा XGMAC_MMC_TXPAUSEFRAME	0x00000894
#घोषणा XGMAC_MMC_TXVLANFRAME	0x0000089C

/* Hardware RX Statistics Counters */
#घोषणा XGMAC_MMC_RXFRAME_GB_LO	0x00000900
#घोषणा XGMAC_MMC_RXFRAME_GB_HI	0x00000904
#घोषणा XGMAC_MMC_RXOCTET_GB_LO	0x00000908
#घोषणा XGMAC_MMC_RXOCTET_GB_HI	0x0000090C
#घोषणा XGMAC_MMC_RXOCTET_G_LO	0x00000910
#घोषणा XGMAC_MMC_RXOCTET_G_HI	0x00000914
#घोषणा XGMAC_MMC_RXBCFRAME_G	0x00000918
#घोषणा XGMAC_MMC_RXMCFRAME_G	0x00000920
#घोषणा XGMAC_MMC_RXCRCERR	0x00000928
#घोषणा XGMAC_MMC_RXRUNT	0x00000930
#घोषणा XGMAC_MMC_RXJABBER	0x00000934
#घोषणा XGMAC_MMC_RXUCFRAME_G	0x00000970
#घोषणा XGMAC_MMC_RXLENGTHERR	0x00000978
#घोषणा XGMAC_MMC_RXPAUSEFRAME	0x00000988
#घोषणा XGMAC_MMC_RXOVERFLOW	0x00000990
#घोषणा XGMAC_MMC_RXVLANFRAME	0x00000998
#घोषणा XGMAC_MMC_RXWATCHDOG	0x000009a0

/* DMA Control and Status Registers */
#घोषणा XGMAC_DMA_BUS_MODE	0x00000f00	/* Bus Mode */
#घोषणा XGMAC_DMA_TX_POLL	0x00000f04	/* Transmit Poll Demand */
#घोषणा XGMAC_DMA_RX_POLL	0x00000f08	/* Received Poll Demand */
#घोषणा XGMAC_DMA_RX_BASE_ADDR	0x00000f0c	/* Receive List Base */
#घोषणा XGMAC_DMA_TX_BASE_ADDR	0x00000f10	/* Transmit List Base */
#घोषणा XGMAC_DMA_STATUS	0x00000f14	/* Status Register */
#घोषणा XGMAC_DMA_CONTROL	0x00000f18	/* Ctrl (Operational Mode) */
#घोषणा XGMAC_DMA_INTR_ENA	0x00000f1c	/* Interrupt Enable */
#घोषणा XGMAC_DMA_MISS_FRAME_CTR 0x00000f20	/* Missed Frame Counter */
#घोषणा XGMAC_DMA_RI_WDOG_TIMER	0x00000f24	/* RX Intr Watchकरोg Timer */
#घोषणा XGMAC_DMA_AXI_BUS	0x00000f28	/* AXI Bus Mode */
#घोषणा XGMAC_DMA_AXI_STATUS	0x00000f2C	/* AXI Status */
#घोषणा XGMAC_DMA_HW_FEATURE	0x00000f58	/* Enabled Hardware Features */

#घोषणा XGMAC_ADDR_AE		0x80000000

/* PMT Control and Status */
#घोषणा XGMAC_PMT_POINTER_RESET	0x80000000
#घोषणा XGMAC_PMT_GLBL_UNICAST	0x00000200
#घोषणा XGMAC_PMT_WAKEUP_RX_FRM	0x00000040
#घोषणा XGMAC_PMT_MAGIC_PKT	0x00000020
#घोषणा XGMAC_PMT_WAKEUP_FRM_EN	0x00000004
#घोषणा XGMAC_PMT_MAGIC_PKT_EN	0x00000002
#घोषणा XGMAC_PMT_POWERDOWN	0x00000001

#घोषणा XGMAC_CONTROL_SPD	0x40000000	/* Speed control */
#घोषणा XGMAC_CONTROL_SPD_MASK	0x60000000
#घोषणा XGMAC_CONTROL_SPD_1G	0x60000000
#घोषणा XGMAC_CONTROL_SPD_2_5G	0x40000000
#घोषणा XGMAC_CONTROL_SPD_10G	0x00000000
#घोषणा XGMAC_CONTROL_SARC	0x10000000	/* Source Addr Insert/Replace */
#घोषणा XGMAC_CONTROL_SARK_MASK	0x18000000
#घोषणा XGMAC_CONTROL_CAR	0x04000000	/* CRC Addition/Replacement */
#घोषणा XGMAC_CONTROL_CAR_MASK	0x06000000
#घोषणा XGMAC_CONTROL_DP	0x01000000	/* Disable Padding */
#घोषणा XGMAC_CONTROL_WD	0x00800000	/* Disable Watchकरोg on rx */
#घोषणा XGMAC_CONTROL_JD	0x00400000	/* Jabber disable */
#घोषणा XGMAC_CONTROL_JE	0x00100000	/* Jumbo frame */
#घोषणा XGMAC_CONTROL_LM	0x00001000	/* Loop-back mode */
#घोषणा XGMAC_CONTROL_IPC	0x00000400	/* Checksum Offload */
#घोषणा XGMAC_CONTROL_ACS	0x00000080	/* Automatic Pad/FCS Strip */
#घोषणा XGMAC_CONTROL_DDIC	0x00000010	/* Disable Deficit Idle Count */
#घोषणा XGMAC_CONTROL_TE	0x00000008	/* Transmitter Enable */
#घोषणा XGMAC_CONTROL_RE	0x00000004	/* Receiver Enable */

/* XGMAC Frame Filter defines */
#घोषणा XGMAC_FRAME_FILTER_PR	0x00000001	/* Promiscuous Mode */
#घोषणा XGMAC_FRAME_FILTER_HUC	0x00000002	/* Hash Unicast */
#घोषणा XGMAC_FRAME_FILTER_HMC	0x00000004	/* Hash Multicast */
#घोषणा XGMAC_FRAME_FILTER_DAIF	0x00000008	/* DA Inverse Filtering */
#घोषणा XGMAC_FRAME_FILTER_PM	0x00000010	/* Pass all multicast */
#घोषणा XGMAC_FRAME_FILTER_DBF	0x00000020	/* Disable Broadcast frames */
#घोषणा XGMAC_FRAME_FILTER_SAIF	0x00000100	/* Inverse Filtering */
#घोषणा XGMAC_FRAME_FILTER_SAF	0x00000200	/* Source Address Filter */
#घोषणा XGMAC_FRAME_FILTER_HPF	0x00000400	/* Hash or perfect Filter */
#घोषणा XGMAC_FRAME_FILTER_VHF	0x00000800	/* VLAN Hash Filter */
#घोषणा XGMAC_FRAME_FILTER_VPF	0x00001000	/* VLAN Perfect Filter */
#घोषणा XGMAC_FRAME_FILTER_RA	0x80000000	/* Receive all mode */

/* XGMAC FLOW CTRL defines */
#घोषणा XGMAC_FLOW_CTRL_PT_MASK	0xffff0000	/* Pause Time Mask */
#घोषणा XGMAC_FLOW_CTRL_PT_SHIFT	16
#घोषणा XGMAC_FLOW_CTRL_DZQP	0x00000080	/* Disable Zero-Quanta Phase */
#घोषणा XGMAC_FLOW_CTRL_PLT	0x00000020	/* Pause Low Threshold */
#घोषणा XGMAC_FLOW_CTRL_PLT_MASK 0x00000030	/* PLT MASK */
#घोषणा XGMAC_FLOW_CTRL_UP	0x00000008	/* Unicast Pause Frame Detect */
#घोषणा XGMAC_FLOW_CTRL_RFE	0x00000004	/* Rx Flow Control Enable */
#घोषणा XGMAC_FLOW_CTRL_TFE	0x00000002	/* Tx Flow Control Enable */
#घोषणा XGMAC_FLOW_CTRL_FCB_BPA	0x00000001	/* Flow Control Busy ... */

/* XGMAC_INT_STAT reg */
#घोषणा XGMAC_INT_STAT_PMTIM	0x00800000	/* PMT Interrupt Mask */
#घोषणा XGMAC_INT_STAT_PMT	0x0080		/* PMT Interrupt Status */
#घोषणा XGMAC_INT_STAT_LPI	0x0040		/* LPI Interrupt Status */

/* DMA Bus Mode रेजिस्टर defines */
#घोषणा DMA_BUS_MODE_SFT_RESET	0x00000001	/* Software Reset */
#घोषणा DMA_BUS_MODE_DSL_MASK	0x0000007c	/* Descriptor Skip Length */
#घोषणा DMA_BUS_MODE_DSL_SHIFT	2		/* (in DWORDS) */
#घोषणा DMA_BUS_MODE_ATDS	0x00000080	/* Alternate Descriptor Size */

/* Programmable burst length */
#घोषणा DMA_BUS_MODE_PBL_MASK	0x00003f00	/* Programmable Burst Len */
#घोषणा DMA_BUS_MODE_PBL_SHIFT	8
#घोषणा DMA_BUS_MODE_FB		0x00010000	/* Fixed burst */
#घोषणा DMA_BUS_MODE_RPBL_MASK	0x003e0000	/* Rx-Programmable Burst Len */
#घोषणा DMA_BUS_MODE_RPBL_SHIFT	17
#घोषणा DMA_BUS_MODE_USP	0x00800000
#घोषणा DMA_BUS_MODE_8PBL	0x01000000
#घोषणा DMA_BUS_MODE_AAL	0x02000000

/* DMA Bus Mode रेजिस्टर defines */
#घोषणा DMA_BUS_PR_RATIO_MASK	0x0000c000	/* Rx/Tx priority ratio */
#घोषणा DMA_BUS_PR_RATIO_SHIFT	14
#घोषणा DMA_BUS_FB		0x00010000	/* Fixed Burst */

/* DMA Control रेजिस्टर defines */
#घोषणा DMA_CONTROL_ST		0x00002000	/* Start/Stop Transmission */
#घोषणा DMA_CONTROL_SR		0x00000002	/* Start/Stop Receive */
#घोषणा DMA_CONTROL_DFF		0x01000000	/* Disable flush of rx frames */
#घोषणा DMA_CONTROL_OSF		0x00000004	/* Operate on 2nd tx frame */

/* DMA Normal पूर्णांकerrupt */
#घोषणा DMA_INTR_ENA_NIE	0x00010000	/* Normal Summary */
#घोषणा DMA_INTR_ENA_AIE	0x00008000	/* Abnormal Summary */
#घोषणा DMA_INTR_ENA_ERE	0x00004000	/* Early Receive */
#घोषणा DMA_INTR_ENA_FBE	0x00002000	/* Fatal Bus Error */
#घोषणा DMA_INTR_ENA_ETE	0x00000400	/* Early Transmit */
#घोषणा DMA_INTR_ENA_RWE	0x00000200	/* Receive Watchकरोg */
#घोषणा DMA_INTR_ENA_RSE	0x00000100	/* Receive Stopped */
#घोषणा DMA_INTR_ENA_RUE	0x00000080	/* Receive Buffer Unavailable */
#घोषणा DMA_INTR_ENA_RIE	0x00000040	/* Receive Interrupt */
#घोषणा DMA_INTR_ENA_UNE	0x00000020	/* Tx Underflow */
#घोषणा DMA_INTR_ENA_OVE	0x00000010	/* Receive Overflow */
#घोषणा DMA_INTR_ENA_TJE	0x00000008	/* Transmit Jabber */
#घोषणा DMA_INTR_ENA_TUE	0x00000004	/* Transmit Buffer Unavail */
#घोषणा DMA_INTR_ENA_TSE	0x00000002	/* Transmit Stopped */
#घोषणा DMA_INTR_ENA_TIE	0x00000001	/* Transmit Interrupt */

#घोषणा DMA_INTR_NORMAL		(DMA_INTR_ENA_NIE | DMA_INTR_ENA_RIE | \
				 DMA_INTR_ENA_TUE | DMA_INTR_ENA_TIE)

#घोषणा DMA_INTR_ABNORMAL	(DMA_INTR_ENA_AIE | DMA_INTR_ENA_FBE | \
				 DMA_INTR_ENA_RWE | DMA_INTR_ENA_RSE | \
				 DMA_INTR_ENA_RUE | DMA_INTR_ENA_UNE | \
				 DMA_INTR_ENA_OVE | DMA_INTR_ENA_TJE | \
				 DMA_INTR_ENA_TSE)

/* DMA शेष पूर्णांकerrupt mask */
#घोषणा DMA_INTR_DEFAULT_MASK	(DMA_INTR_NORMAL | DMA_INTR_ABNORMAL)

/* DMA Status रेजिस्टर defines */
#घोषणा DMA_STATUS_GMI		0x08000000	/* MMC पूर्णांकerrupt */
#घोषणा DMA_STATUS_GLI		0x04000000	/* GMAC Line पूर्णांकerface पूर्णांक */
#घोषणा DMA_STATUS_EB_MASK	0x00380000	/* Error Bits Mask */
#घोषणा DMA_STATUS_EB_TX_ABORT	0x00080000	/* Error Bits - TX Abort */
#घोषणा DMA_STATUS_EB_RX_ABORT	0x00100000	/* Error Bits - RX Abort */
#घोषणा DMA_STATUS_TS_MASK	0x00700000	/* Transmit Process State */
#घोषणा DMA_STATUS_TS_SHIFT	20
#घोषणा DMA_STATUS_RS_MASK	0x000e0000	/* Receive Process State */
#घोषणा DMA_STATUS_RS_SHIFT	17
#घोषणा DMA_STATUS_NIS		0x00010000	/* Normal Interrupt Summary */
#घोषणा DMA_STATUS_AIS		0x00008000	/* Abnormal Interrupt Summary */
#घोषणा DMA_STATUS_ERI		0x00004000	/* Early Receive Interrupt */
#घोषणा DMA_STATUS_FBI		0x00002000	/* Fatal Bus Error Interrupt */
#घोषणा DMA_STATUS_ETI		0x00000400	/* Early Transmit Interrupt */
#घोषणा DMA_STATUS_RWT		0x00000200	/* Receive Watchकरोg Timeout */
#घोषणा DMA_STATUS_RPS		0x00000100	/* Receive Process Stopped */
#घोषणा DMA_STATUS_RU		0x00000080	/* Receive Buffer Unavailable */
#घोषणा DMA_STATUS_RI		0x00000040	/* Receive Interrupt */
#घोषणा DMA_STATUS_UNF		0x00000020	/* Transmit Underflow */
#घोषणा DMA_STATUS_OVF		0x00000010	/* Receive Overflow */
#घोषणा DMA_STATUS_TJT		0x00000008	/* Transmit Jabber Timeout */
#घोषणा DMA_STATUS_TU		0x00000004	/* Transmit Buffer Unavail */
#घोषणा DMA_STATUS_TPS		0x00000002	/* Transmit Process Stopped */
#घोषणा DMA_STATUS_TI		0x00000001	/* Transmit Interrupt */

/* Common MAC defines */
#घोषणा MAC_ENABLE_TX		0x00000008	/* Transmitter Enable */
#घोषणा MAC_ENABLE_RX		0x00000004	/* Receiver Enable */

/* XGMAC Operation Mode Register */
#घोषणा XGMAC_OMR_TSF		0x00200000	/* TX FIFO Store and Forward */
#घोषणा XGMAC_OMR_FTF		0x00100000	/* Flush Transmit FIFO */
#घोषणा XGMAC_OMR_TTC		0x00020000	/* Transmit Threshold Ctrl */
#घोषणा XGMAC_OMR_TTC_MASK	0x00030000
#घोषणा XGMAC_OMR_RFD		0x00006000	/* FC Deactivation Threshold */
#घोषणा XGMAC_OMR_RFD_MASK	0x00007000	/* FC Deact Threshold MASK */
#घोषणा XGMAC_OMR_RFA		0x00000600	/* FC Activation Threshold */
#घोषणा XGMAC_OMR_RFA_MASK	0x00000E00	/* FC Act Threshold MASK */
#घोषणा XGMAC_OMR_EFC		0x00000100	/* Enable Hardware FC */
#घोषणा XGMAC_OMR_FEF		0x00000080	/* Forward Error Frames */
#घोषणा XGMAC_OMR_DT		0x00000040	/* Drop TCP/IP csum Errors */
#घोषणा XGMAC_OMR_RSF		0x00000020	/* RX FIFO Store and Forward */
#घोषणा XGMAC_OMR_RTC_256	0x00000018	/* RX Threshold Ctrl */
#घोषणा XGMAC_OMR_RTC_MASK	0x00000018	/* RX Threshold Ctrl MASK */

/* XGMAC HW Features Register */
#घोषणा DMA_HW_FEAT_TXCOESEL	0x00010000	/* TX Checksum offload */

#घोषणा XGMAC_MMC_CTRL_CNT_FRZ	0x00000008

/* XGMAC Descriptor Defines */
#घोषणा MAX_DESC_BUF_SZ		(0x2000 - 8)

#घोषणा RXDESC_EXT_STATUS	0x00000001
#घोषणा RXDESC_CRC_ERR		0x00000002
#घोषणा RXDESC_RX_ERR		0x00000008
#घोषणा RXDESC_RX_WDOG		0x00000010
#घोषणा RXDESC_FRAME_TYPE	0x00000020
#घोषणा RXDESC_GIANT_FRAME	0x00000080
#घोषणा RXDESC_LAST_SEG		0x00000100
#घोषणा RXDESC_FIRST_SEG	0x00000200
#घोषणा RXDESC_VLAN_FRAME	0x00000400
#घोषणा RXDESC_OVERFLOW_ERR	0x00000800
#घोषणा RXDESC_LENGTH_ERR	0x00001000
#घोषणा RXDESC_SA_FILTER_FAIL	0x00002000
#घोषणा RXDESC_DESCRIPTOR_ERR	0x00004000
#घोषणा RXDESC_ERROR_SUMMARY	0x00008000
#घोषणा RXDESC_FRAME_LEN_OFFSET	16
#घोषणा RXDESC_FRAME_LEN_MASK	0x3fff0000
#घोषणा RXDESC_DA_FILTER_FAIL	0x40000000

#घोषणा RXDESC1_END_RING	0x00008000

#घोषणा RXDESC_IP_PAYLOAD_MASK	0x00000003
#घोषणा RXDESC_IP_PAYLOAD_UDP	0x00000001
#घोषणा RXDESC_IP_PAYLOAD_TCP	0x00000002
#घोषणा RXDESC_IP_PAYLOAD_ICMP	0x00000003
#घोषणा RXDESC_IP_HEADER_ERR	0x00000008
#घोषणा RXDESC_IP_PAYLOAD_ERR	0x00000010
#घोषणा RXDESC_IPV4_PACKET	0x00000040
#घोषणा RXDESC_IPV6_PACKET	0x00000080
#घोषणा TXDESC_UNDERFLOW_ERR	0x00000001
#घोषणा TXDESC_JABBER_TIMEOUT	0x00000002
#घोषणा TXDESC_LOCAL_FAULT	0x00000004
#घोषणा TXDESC_REMOTE_FAULT	0x00000008
#घोषणा TXDESC_VLAN_FRAME	0x00000010
#घोषणा TXDESC_FRAME_FLUSHED	0x00000020
#घोषणा TXDESC_IP_HEADER_ERR	0x00000040
#घोषणा TXDESC_PAYLOAD_CSUM_ERR	0x00000080
#घोषणा TXDESC_ERROR_SUMMARY	0x00008000
#घोषणा TXDESC_SA_CTRL_INSERT	0x00040000
#घोषणा TXDESC_SA_CTRL_REPLACE	0x00080000
#घोषणा TXDESC_2ND_ADDR_CHAINED	0x00100000
#घोषणा TXDESC_END_RING		0x00200000
#घोषणा TXDESC_CSUM_IP		0x00400000
#घोषणा TXDESC_CSUM_IP_PAYLD	0x00800000
#घोषणा TXDESC_CSUM_ALL		0x00C00000
#घोषणा TXDESC_CRC_EN_REPLACE	0x01000000
#घोषणा TXDESC_CRC_EN_APPEND	0x02000000
#घोषणा TXDESC_DISABLE_PAD	0x04000000
#घोषणा TXDESC_FIRST_SEG	0x10000000
#घोषणा TXDESC_LAST_SEG		0x20000000
#घोषणा TXDESC_INTERRUPT	0x40000000

#घोषणा DESC_OWN		0x80000000
#घोषणा DESC_BUFFER1_SZ_MASK	0x00001fff
#घोषणा DESC_BUFFER2_SZ_MASK	0x1fff0000
#घोषणा DESC_BUFFER2_SZ_OFFSET	16

काष्ठा xgmac_dma_desc अणु
	__le32 flags;
	__le32 buf_size;
	__le32 buf1_addr;		/* Buffer 1 Address Poपूर्णांकer */
	__le32 buf2_addr;		/* Buffer 2 Address Poपूर्णांकer */
	__le32 ext_status;
	__le32 res[3];
पूर्ण;

काष्ठा xgmac_extra_stats अणु
	/* Transmit errors */
	अचिन्हित दीर्घ tx_jabber;
	अचिन्हित दीर्घ tx_frame_flushed;
	अचिन्हित दीर्घ tx_payload_error;
	अचिन्हित दीर्घ tx_ip_header_error;
	अचिन्हित दीर्घ tx_local_fault;
	अचिन्हित दीर्घ tx_remote_fault;
	/* Receive errors */
	अचिन्हित दीर्घ rx_watchकरोg;
	अचिन्हित दीर्घ rx_da_filter_fail;
	अचिन्हित दीर्घ rx_payload_error;
	अचिन्हित दीर्घ rx_ip_header_error;
	/* Tx/Rx IRQ errors */
	अचिन्हित दीर्घ tx_process_stopped;
	अचिन्हित दीर्घ rx_buf_unav;
	अचिन्हित दीर्घ rx_process_stopped;
	अचिन्हित दीर्घ tx_early;
	अचिन्हित दीर्घ fatal_bus_error;
पूर्ण;

काष्ठा xgmac_priv अणु
	काष्ठा xgmac_dma_desc *dma_rx;
	काष्ठा sk_buff **rx_skbuff;
	अचिन्हित पूर्णांक rx_tail;
	अचिन्हित पूर्णांक rx_head;

	काष्ठा xgmac_dma_desc *dma_tx;
	काष्ठा sk_buff **tx_skbuff;
	अचिन्हित पूर्णांक tx_head;
	अचिन्हित पूर्णांक tx_tail;
	पूर्णांक tx_irq_cnt;

	व्योम __iomem *base;
	अचिन्हित पूर्णांक dma_buf_sz;
	dma_addr_t dma_rx_phy;
	dma_addr_t dma_tx_phy;

	काष्ठा net_device *dev;
	काष्ठा device *device;
	काष्ठा napi_काष्ठा napi;

	पूर्णांक max_macs;
	काष्ठा xgmac_extra_stats xstats;

	spinlock_t stats_lock;
	पूर्णांक pmt_irq;
	अक्षर rx_छोड़ो;
	अक्षर tx_छोड़ो;
	पूर्णांक wolopts;
	काष्ठा work_काष्ठा tx_समयout_work;
पूर्ण;

/* XGMAC Configuration Settings */
#घोषणा XGMAC_MAX_MTU		9000
#घोषणा PAUSE_TIME		0x400

#घोषणा DMA_RX_RING_SZ		256
#घोषणा DMA_TX_RING_SZ		128
/* minimum number of मुक्त TX descriptors required to wake up TX process */
#घोषणा TX_THRESH		(DMA_TX_RING_SZ/4)

/* DMA descriptor ring helpers */
#घोषणा dma_ring_incr(n, s)	(((n) + 1) & ((s) - 1))
#घोषणा dma_ring_space(h, t, s)	CIRC_SPACE(h, t, s)
#घोषणा dma_ring_cnt(h, t, s)	CIRC_CNT(h, t, s)

#घोषणा tx_dma_ring_space(p) \
	dma_ring_space((p)->tx_head, (p)->tx_tail, DMA_TX_RING_SZ)

/* XGMAC Descriptor Access Helpers */
अटल अंतरभूत व्योम desc_set_buf_len(काष्ठा xgmac_dma_desc *p, u32 buf_sz)
अणु
	अगर (buf_sz > MAX_DESC_BUF_SZ)
		p->buf_size = cpu_to_le32(MAX_DESC_BUF_SZ |
			(buf_sz - MAX_DESC_BUF_SZ) << DESC_BUFFER2_SZ_OFFSET);
	अन्यथा
		p->buf_size = cpu_to_le32(buf_sz);
पूर्ण

अटल अंतरभूत पूर्णांक desc_get_buf_len(काष्ठा xgmac_dma_desc *p)
अणु
	u32 len = le32_to_cpu(p->buf_size);
	वापस (len & DESC_BUFFER1_SZ_MASK) +
		((len & DESC_BUFFER2_SZ_MASK) >> DESC_BUFFER2_SZ_OFFSET);
पूर्ण

अटल अंतरभूत व्योम desc_init_rx_desc(काष्ठा xgmac_dma_desc *p, पूर्णांक ring_size,
				     पूर्णांक buf_sz)
अणु
	काष्ठा xgmac_dma_desc *end = p + ring_size - 1;

	स_रखो(p, 0, माप(*p) * ring_size);

	क्रम (; p <= end; p++)
		desc_set_buf_len(p, buf_sz);

	end->buf_size |= cpu_to_le32(RXDESC1_END_RING);
पूर्ण

अटल अंतरभूत व्योम desc_init_tx_desc(काष्ठा xgmac_dma_desc *p, u32 ring_size)
अणु
	स_रखो(p, 0, माप(*p) * ring_size);
	p[ring_size - 1].flags = cpu_to_le32(TXDESC_END_RING);
पूर्ण

अटल अंतरभूत पूर्णांक desc_get_owner(काष्ठा xgmac_dma_desc *p)
अणु
	वापस le32_to_cpu(p->flags) & DESC_OWN;
पूर्ण

अटल अंतरभूत व्योम desc_set_rx_owner(काष्ठा xgmac_dma_desc *p)
अणु
	/* Clear all fields and set the owner */
	p->flags = cpu_to_le32(DESC_OWN);
पूर्ण

अटल अंतरभूत व्योम desc_set_tx_owner(काष्ठा xgmac_dma_desc *p, u32 flags)
अणु
	u32 पंचांगpflags = le32_to_cpu(p->flags);
	पंचांगpflags &= TXDESC_END_RING;
	पंचांगpflags |= flags | DESC_OWN;
	p->flags = cpu_to_le32(पंचांगpflags);
पूर्ण

अटल अंतरभूत व्योम desc_clear_tx_owner(काष्ठा xgmac_dma_desc *p)
अणु
	u32 पंचांगpflags = le32_to_cpu(p->flags);
	पंचांगpflags &= TXDESC_END_RING;
	p->flags = cpu_to_le32(पंचांगpflags);
पूर्ण

अटल अंतरभूत पूर्णांक desc_get_tx_ls(काष्ठा xgmac_dma_desc *p)
अणु
	वापस le32_to_cpu(p->flags) & TXDESC_LAST_SEG;
पूर्ण

अटल अंतरभूत पूर्णांक desc_get_tx_fs(काष्ठा xgmac_dma_desc *p)
अणु
	वापस le32_to_cpu(p->flags) & TXDESC_FIRST_SEG;
पूर्ण

अटल अंतरभूत u32 desc_get_buf_addr(काष्ठा xgmac_dma_desc *p)
अणु
	वापस le32_to_cpu(p->buf1_addr);
पूर्ण

अटल अंतरभूत व्योम desc_set_buf_addr(काष्ठा xgmac_dma_desc *p,
				     u32 paddr, पूर्णांक len)
अणु
	p->buf1_addr = cpu_to_le32(paddr);
	अगर (len > MAX_DESC_BUF_SZ)
		p->buf2_addr = cpu_to_le32(paddr + MAX_DESC_BUF_SZ);
पूर्ण

अटल अंतरभूत व्योम desc_set_buf_addr_and_size(काष्ठा xgmac_dma_desc *p,
					      u32 paddr, पूर्णांक len)
अणु
	desc_set_buf_len(p, len);
	desc_set_buf_addr(p, paddr, len);
पूर्ण

अटल अंतरभूत पूर्णांक desc_get_rx_frame_len(काष्ठा xgmac_dma_desc *p)
अणु
	u32 data = le32_to_cpu(p->flags);
	u32 len = (data & RXDESC_FRAME_LEN_MASK) >> RXDESC_FRAME_LEN_OFFSET;
	अगर (data & RXDESC_FRAME_TYPE)
		len -= ETH_FCS_LEN;

	वापस len;
पूर्ण

अटल व्योम xgmac_dma_flush_tx_fअगरo(व्योम __iomem *ioaddr)
अणु
	पूर्णांक समयout = 1000;
	u32 reg = पढ़ोl(ioaddr + XGMAC_OMR);
	ग_लिखोl(reg | XGMAC_OMR_FTF, ioaddr + XGMAC_OMR);

	जबतक ((समयout-- > 0) && पढ़ोl(ioaddr + XGMAC_OMR) & XGMAC_OMR_FTF)
		udelay(1);
पूर्ण

अटल पूर्णांक desc_get_tx_status(काष्ठा xgmac_priv *priv, काष्ठा xgmac_dma_desc *p)
अणु
	काष्ठा xgmac_extra_stats *x = &priv->xstats;
	u32 status = le32_to_cpu(p->flags);

	अगर (!(status & TXDESC_ERROR_SUMMARY))
		वापस 0;

	netdev_dbg(priv->dev, "tx desc error = 0x%08x\n", status);
	अगर (status & TXDESC_JABBER_TIMEOUT)
		x->tx_jabber++;
	अगर (status & TXDESC_FRAME_FLUSHED)
		x->tx_frame_flushed++;
	अगर (status & TXDESC_UNDERFLOW_ERR)
		xgmac_dma_flush_tx_fअगरo(priv->base);
	अगर (status & TXDESC_IP_HEADER_ERR)
		x->tx_ip_header_error++;
	अगर (status & TXDESC_LOCAL_FAULT)
		x->tx_local_fault++;
	अगर (status & TXDESC_REMOTE_FAULT)
		x->tx_remote_fault++;
	अगर (status & TXDESC_PAYLOAD_CSUM_ERR)
		x->tx_payload_error++;

	वापस -1;
पूर्ण

अटल पूर्णांक desc_get_rx_status(काष्ठा xgmac_priv *priv, काष्ठा xgmac_dma_desc *p)
अणु
	काष्ठा xgmac_extra_stats *x = &priv->xstats;
	पूर्णांक ret = CHECKSUM_UNNECESSARY;
	u32 status = le32_to_cpu(p->flags);
	u32 ext_status = le32_to_cpu(p->ext_status);

	अगर (status & RXDESC_DA_FILTER_FAIL) अणु
		netdev_dbg(priv->dev, "XGMAC RX : Dest Address filter fail\n");
		x->rx_da_filter_fail++;
		वापस -1;
	पूर्ण

	/* All frames should fit पूर्णांकo a single buffer */
	अगर (!(status & RXDESC_FIRST_SEG) || !(status & RXDESC_LAST_SEG))
		वापस -1;

	/* Check अगर packet has checksum alपढ़ोy */
	अगर ((status & RXDESC_FRAME_TYPE) && (status & RXDESC_EXT_STATUS) &&
		!(ext_status & RXDESC_IP_PAYLOAD_MASK))
		ret = CHECKSUM_NONE;

	netdev_dbg(priv->dev, "rx status - frame type=%d, csum = %d, ext stat %08x\n",
		   (status & RXDESC_FRAME_TYPE) ? 1 : 0, ret, ext_status);

	अगर (!(status & RXDESC_ERROR_SUMMARY))
		वापस ret;

	/* Handle any errors */
	अगर (status & (RXDESC_DESCRIPTOR_ERR | RXDESC_OVERFLOW_ERR |
		RXDESC_GIANT_FRAME | RXDESC_LENGTH_ERR | RXDESC_CRC_ERR))
		वापस -1;

	अगर (status & RXDESC_EXT_STATUS) अणु
		अगर (ext_status & RXDESC_IP_HEADER_ERR)
			x->rx_ip_header_error++;
		अगर (ext_status & RXDESC_IP_PAYLOAD_ERR)
			x->rx_payload_error++;
		netdev_dbg(priv->dev, "IP checksum error - stat %08x\n",
			   ext_status);
		वापस CHECKSUM_NONE;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम xgmac_mac_enable(व्योम __iomem *ioaddr)
अणु
	u32 value = पढ़ोl(ioaddr + XGMAC_CONTROL);
	value |= MAC_ENABLE_RX | MAC_ENABLE_TX;
	ग_लिखोl(value, ioaddr + XGMAC_CONTROL);

	value = पढ़ोl(ioaddr + XGMAC_DMA_CONTROL);
	value |= DMA_CONTROL_ST | DMA_CONTROL_SR;
	ग_लिखोl(value, ioaddr + XGMAC_DMA_CONTROL);
पूर्ण

अटल अंतरभूत व्योम xgmac_mac_disable(व्योम __iomem *ioaddr)
अणु
	u32 value = पढ़ोl(ioaddr + XGMAC_DMA_CONTROL);
	value &= ~(DMA_CONTROL_ST | DMA_CONTROL_SR);
	ग_लिखोl(value, ioaddr + XGMAC_DMA_CONTROL);

	value = पढ़ोl(ioaddr + XGMAC_CONTROL);
	value &= ~(MAC_ENABLE_TX | MAC_ENABLE_RX);
	ग_लिखोl(value, ioaddr + XGMAC_CONTROL);
पूर्ण

अटल व्योम xgmac_set_mac_addr(व्योम __iomem *ioaddr, अचिन्हित अक्षर *addr,
			       पूर्णांक num)
अणु
	u32 data;

	अगर (addr) अणु
		data = (addr[5] << 8) | addr[4] | (num ? XGMAC_ADDR_AE : 0);
		ग_लिखोl(data, ioaddr + XGMAC_ADDR_HIGH(num));
		data = (addr[3] << 24) | (addr[2] << 16) | (addr[1] << 8) | addr[0];
		ग_लिखोl(data, ioaddr + XGMAC_ADDR_LOW(num));
	पूर्ण अन्यथा अणु
		ग_लिखोl(0, ioaddr + XGMAC_ADDR_HIGH(num));
		ग_लिखोl(0, ioaddr + XGMAC_ADDR_LOW(num));
	पूर्ण
पूर्ण

अटल व्योम xgmac_get_mac_addr(व्योम __iomem *ioaddr, अचिन्हित अक्षर *addr,
			       पूर्णांक num)
अणु
	u32 hi_addr, lo_addr;

	/* Read the MAC address from the hardware */
	hi_addr = पढ़ोl(ioaddr + XGMAC_ADDR_HIGH(num));
	lo_addr = पढ़ोl(ioaddr + XGMAC_ADDR_LOW(num));

	/* Extract the MAC address from the high and low words */
	addr[0] = lo_addr & 0xff;
	addr[1] = (lo_addr >> 8) & 0xff;
	addr[2] = (lo_addr >> 16) & 0xff;
	addr[3] = (lo_addr >> 24) & 0xff;
	addr[4] = hi_addr & 0xff;
	addr[5] = (hi_addr >> 8) & 0xff;
पूर्ण

अटल पूर्णांक xgmac_set_flow_ctrl(काष्ठा xgmac_priv *priv, पूर्णांक rx, पूर्णांक tx)
अणु
	u32 reg;
	अचिन्हित पूर्णांक flow = 0;

	priv->rx_छोड़ो = rx;
	priv->tx_छोड़ो = tx;

	अगर (rx || tx) अणु
		अगर (rx)
			flow |= XGMAC_FLOW_CTRL_RFE;
		अगर (tx)
			flow |= XGMAC_FLOW_CTRL_TFE;

		flow |= XGMAC_FLOW_CTRL_PLT | XGMAC_FLOW_CTRL_UP;
		flow |= (PAUSE_TIME << XGMAC_FLOW_CTRL_PT_SHIFT);

		ग_लिखोl(flow, priv->base + XGMAC_FLOW_CTRL);

		reg = पढ़ोl(priv->base + XGMAC_OMR);
		reg |= XGMAC_OMR_EFC;
		ग_लिखोl(reg, priv->base + XGMAC_OMR);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0, priv->base + XGMAC_FLOW_CTRL);

		reg = पढ़ोl(priv->base + XGMAC_OMR);
		reg &= ~XGMAC_OMR_EFC;
		ग_लिखोl(reg, priv->base + XGMAC_OMR);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xgmac_rx_refill(काष्ठा xgmac_priv *priv)
अणु
	काष्ठा xgmac_dma_desc *p;
	dma_addr_t paddr;
	पूर्णांक bufsz = priv->dev->mtu + ETH_HLEN + ETH_FCS_LEN;

	जबतक (dma_ring_space(priv->rx_head, priv->rx_tail, DMA_RX_RING_SZ) > 1) अणु
		पूर्णांक entry = priv->rx_head;
		काष्ठा sk_buff *skb;

		p = priv->dma_rx + entry;

		अगर (priv->rx_skbuff[entry] == शून्य) अणु
			skb = netdev_alloc_skb_ip_align(priv->dev, bufsz);
			अगर (unlikely(skb == शून्य))
				अवरोध;

			paddr = dma_map_single(priv->device, skb->data,
					       priv->dma_buf_sz - NET_IP_ALIGN,
					       DMA_FROM_DEVICE);
			अगर (dma_mapping_error(priv->device, paddr)) अणु
				dev_kमुक्त_skb_any(skb);
				अवरोध;
			पूर्ण
			priv->rx_skbuff[entry] = skb;
			desc_set_buf_addr(p, paddr, priv->dma_buf_sz);
		पूर्ण

		netdev_dbg(priv->dev, "rx ring: head %d, tail %d\n",
			priv->rx_head, priv->rx_tail);

		priv->rx_head = dma_ring_incr(priv->rx_head, DMA_RX_RING_SZ);
		desc_set_rx_owner(p);
	पूर्ण
पूर्ण

/**
 * init_xgmac_dma_desc_rings - init the RX/TX descriptor rings
 * @dev: net device काष्ठाure
 * Description:  this function initializes the DMA RX/TX descriptors
 * and allocates the socket buffers.
 */
अटल पूर्णांक xgmac_dma_desc_rings_init(काष्ठा net_device *dev)
अणु
	काष्ठा xgmac_priv *priv = netdev_priv(dev);
	अचिन्हित पूर्णांक bfsize;

	/* Set the Buffer size according to the MTU;
	 * The total buffer size including any IP offset must be a multiple
	 * of 8 bytes.
	 */
	bfsize = ALIGN(dev->mtu + ETH_HLEN + ETH_FCS_LEN + NET_IP_ALIGN, 8);

	netdev_dbg(priv->dev, "mtu [%d] bfsize [%d]\n", dev->mtu, bfsize);

	priv->rx_skbuff = kसुस्मृति(DMA_RX_RING_SZ, माप(काष्ठा sk_buff *),
				  GFP_KERNEL);
	अगर (!priv->rx_skbuff)
		वापस -ENOMEM;

	priv->dma_rx = dma_alloc_coherent(priv->device,
					  DMA_RX_RING_SZ *
					  माप(काष्ठा xgmac_dma_desc),
					  &priv->dma_rx_phy,
					  GFP_KERNEL);
	अगर (!priv->dma_rx)
		जाओ err_dma_rx;

	priv->tx_skbuff = kसुस्मृति(DMA_TX_RING_SZ, माप(काष्ठा sk_buff *),
				  GFP_KERNEL);
	अगर (!priv->tx_skbuff)
		जाओ err_tx_skb;

	priv->dma_tx = dma_alloc_coherent(priv->device,
					  DMA_TX_RING_SZ *
					  माप(काष्ठा xgmac_dma_desc),
					  &priv->dma_tx_phy,
					  GFP_KERNEL);
	अगर (!priv->dma_tx)
		जाओ err_dma_tx;

	netdev_dbg(priv->dev, "DMA desc rings: virt addr (Rx %p, "
	    "Tx %p)\n\tDMA phy addr (Rx 0x%08x, Tx 0x%08x)\n",
	    priv->dma_rx, priv->dma_tx,
	    (अचिन्हित पूर्णांक)priv->dma_rx_phy, (अचिन्हित पूर्णांक)priv->dma_tx_phy);

	priv->rx_tail = 0;
	priv->rx_head = 0;
	priv->dma_buf_sz = bfsize;
	desc_init_rx_desc(priv->dma_rx, DMA_RX_RING_SZ, priv->dma_buf_sz);
	xgmac_rx_refill(priv);

	priv->tx_tail = 0;
	priv->tx_head = 0;
	desc_init_tx_desc(priv->dma_tx, DMA_TX_RING_SZ);

	ग_लिखोl(priv->dma_tx_phy, priv->base + XGMAC_DMA_TX_BASE_ADDR);
	ग_लिखोl(priv->dma_rx_phy, priv->base + XGMAC_DMA_RX_BASE_ADDR);

	वापस 0;

err_dma_tx:
	kमुक्त(priv->tx_skbuff);
err_tx_skb:
	dma_मुक्त_coherent(priv->device,
			  DMA_RX_RING_SZ * माप(काष्ठा xgmac_dma_desc),
			  priv->dma_rx, priv->dma_rx_phy);
err_dma_rx:
	kमुक्त(priv->rx_skbuff);
	वापस -ENOMEM;
पूर्ण

अटल व्योम xgmac_मुक्त_rx_skbufs(काष्ठा xgmac_priv *priv)
अणु
	पूर्णांक i;
	काष्ठा xgmac_dma_desc *p;

	अगर (!priv->rx_skbuff)
		वापस;

	क्रम (i = 0; i < DMA_RX_RING_SZ; i++) अणु
		काष्ठा sk_buff *skb = priv->rx_skbuff[i];
		अगर (skb == शून्य)
			जारी;

		p = priv->dma_rx + i;
		dma_unmap_single(priv->device, desc_get_buf_addr(p),
				 priv->dma_buf_sz - NET_IP_ALIGN, DMA_FROM_DEVICE);
		dev_kमुक्त_skb_any(skb);
		priv->rx_skbuff[i] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम xgmac_मुक्त_tx_skbufs(काष्ठा xgmac_priv *priv)
अणु
	पूर्णांक i;
	काष्ठा xgmac_dma_desc *p;

	अगर (!priv->tx_skbuff)
		वापस;

	क्रम (i = 0; i < DMA_TX_RING_SZ; i++) अणु
		अगर (priv->tx_skbuff[i] == शून्य)
			जारी;

		p = priv->dma_tx + i;
		अगर (desc_get_tx_fs(p))
			dma_unmap_single(priv->device, desc_get_buf_addr(p),
					 desc_get_buf_len(p), DMA_TO_DEVICE);
		अन्यथा
			dma_unmap_page(priv->device, desc_get_buf_addr(p),
				       desc_get_buf_len(p), DMA_TO_DEVICE);

		अगर (desc_get_tx_ls(p))
			dev_kमुक्त_skb_any(priv->tx_skbuff[i]);
		priv->tx_skbuff[i] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम xgmac_मुक्त_dma_desc_rings(काष्ठा xgmac_priv *priv)
अणु
	/* Release the DMA TX/RX socket buffers */
	xgmac_मुक्त_rx_skbufs(priv);
	xgmac_मुक्त_tx_skbufs(priv);

	/* Free the consistent memory allocated क्रम descriptor rings */
	अगर (priv->dma_tx) अणु
		dma_मुक्त_coherent(priv->device,
				  DMA_TX_RING_SZ * माप(काष्ठा xgmac_dma_desc),
				  priv->dma_tx, priv->dma_tx_phy);
		priv->dma_tx = शून्य;
	पूर्ण
	अगर (priv->dma_rx) अणु
		dma_मुक्त_coherent(priv->device,
				  DMA_RX_RING_SZ * माप(काष्ठा xgmac_dma_desc),
				  priv->dma_rx, priv->dma_rx_phy);
		priv->dma_rx = शून्य;
	पूर्ण
	kमुक्त(priv->rx_skbuff);
	priv->rx_skbuff = शून्य;
	kमुक्त(priv->tx_skbuff);
	priv->tx_skbuff = शून्य;
पूर्ण

/**
 * xgmac_tx:
 * @priv: निजी driver काष्ठाure
 * Description: it reclaims resources after transmission completes.
 */
अटल व्योम xgmac_tx_complete(काष्ठा xgmac_priv *priv)
अणु
	जबतक (dma_ring_cnt(priv->tx_head, priv->tx_tail, DMA_TX_RING_SZ)) अणु
		अचिन्हित पूर्णांक entry = priv->tx_tail;
		काष्ठा sk_buff *skb = priv->tx_skbuff[entry];
		काष्ठा xgmac_dma_desc *p = priv->dma_tx + entry;

		/* Check अगर the descriptor is owned by the DMA. */
		अगर (desc_get_owner(p))
			अवरोध;

		netdev_dbg(priv->dev, "tx ring: curr %d, dirty %d\n",
			priv->tx_head, priv->tx_tail);

		अगर (desc_get_tx_fs(p))
			dma_unmap_single(priv->device, desc_get_buf_addr(p),
					 desc_get_buf_len(p), DMA_TO_DEVICE);
		अन्यथा
			dma_unmap_page(priv->device, desc_get_buf_addr(p),
				       desc_get_buf_len(p), DMA_TO_DEVICE);

		/* Check tx error on the last segment */
		अगर (desc_get_tx_ls(p)) अणु
			desc_get_tx_status(priv, p);
			dev_consume_skb_any(skb);
		पूर्ण

		priv->tx_skbuff[entry] = शून्य;
		priv->tx_tail = dma_ring_incr(entry, DMA_TX_RING_SZ);
	पूर्ण

	/* Ensure tx_tail is visible to xgmac_xmit */
	smp_mb();
	अगर (unlikely(netअगर_queue_stopped(priv->dev) &&
	    (tx_dma_ring_space(priv) > MAX_SKB_FRAGS)))
		netअगर_wake_queue(priv->dev);
पूर्ण

अटल व्योम xgmac_tx_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	u32 reg, value;
	काष्ठा xgmac_priv *priv =
		container_of(work, काष्ठा xgmac_priv, tx_समयout_work);

	napi_disable(&priv->napi);

	ग_लिखोl(0, priv->base + XGMAC_DMA_INTR_ENA);

	netअगर_tx_lock(priv->dev);

	reg = पढ़ोl(priv->base + XGMAC_DMA_CONTROL);
	ग_लिखोl(reg & ~DMA_CONTROL_ST, priv->base + XGMAC_DMA_CONTROL);
	करो अणु
		value = पढ़ोl(priv->base + XGMAC_DMA_STATUS) & 0x700000;
	पूर्ण जबतक (value && (value != 0x600000));

	xgmac_मुक्त_tx_skbufs(priv);
	desc_init_tx_desc(priv->dma_tx, DMA_TX_RING_SZ);
	priv->tx_tail = 0;
	priv->tx_head = 0;
	ग_लिखोl(priv->dma_tx_phy, priv->base + XGMAC_DMA_TX_BASE_ADDR);
	ग_लिखोl(reg | DMA_CONTROL_ST, priv->base + XGMAC_DMA_CONTROL);

	ग_लिखोl(DMA_STATUS_TU | DMA_STATUS_TPS | DMA_STATUS_NIS | DMA_STATUS_AIS,
		priv->base + XGMAC_DMA_STATUS);

	netअगर_tx_unlock(priv->dev);
	netअगर_wake_queue(priv->dev);

	napi_enable(&priv->napi);

	/* Enable पूर्णांकerrupts */
	ग_लिखोl(DMA_INTR_DEFAULT_MASK, priv->base + XGMAC_DMA_STATUS);
	ग_लिखोl(DMA_INTR_DEFAULT_MASK, priv->base + XGMAC_DMA_INTR_ENA);
पूर्ण

अटल पूर्णांक xgmac_hw_init(काष्ठा net_device *dev)
अणु
	u32 value, ctrl;
	पूर्णांक limit;
	काष्ठा xgmac_priv *priv = netdev_priv(dev);
	व्योम __iomem *ioaddr = priv->base;

	/* Save the ctrl रेजिस्टर value */
	ctrl = पढ़ोl(ioaddr + XGMAC_CONTROL) & XGMAC_CONTROL_SPD_MASK;

	/* SW reset */
	value = DMA_BUS_MODE_SFT_RESET;
	ग_लिखोl(value, ioaddr + XGMAC_DMA_BUS_MODE);
	limit = 15000;
	जबतक (limit-- &&
		(पढ़ोl(ioaddr + XGMAC_DMA_BUS_MODE) & DMA_BUS_MODE_SFT_RESET))
		cpu_relax();
	अगर (limit < 0)
		वापस -EBUSY;

	value = (0x10 << DMA_BUS_MODE_PBL_SHIFT) |
		(0x10 << DMA_BUS_MODE_RPBL_SHIFT) |
		DMA_BUS_MODE_FB | DMA_BUS_MODE_ATDS | DMA_BUS_MODE_AAL;
	ग_लिखोl(value, ioaddr + XGMAC_DMA_BUS_MODE);

	ग_लिखोl(0, ioaddr + XGMAC_DMA_INTR_ENA);

	/* Mask घातer mgt पूर्णांकerrupt */
	ग_लिखोl(XGMAC_INT_STAT_PMTIM, ioaddr + XGMAC_INT_STAT);

	/* XGMAC requires AXI bus init. This is a 'magic number' क्रम now */
	ग_लिखोl(0x0077000E, ioaddr + XGMAC_DMA_AXI_BUS);

	ctrl |= XGMAC_CONTROL_DDIC | XGMAC_CONTROL_JE | XGMAC_CONTROL_ACS |
		XGMAC_CONTROL_CAR;
	अगर (dev->features & NETIF_F_RXCSUM)
		ctrl |= XGMAC_CONTROL_IPC;
	ग_लिखोl(ctrl, ioaddr + XGMAC_CONTROL);

	ग_लिखोl(DMA_CONTROL_OSF, ioaddr + XGMAC_DMA_CONTROL);

	/* Set the HW DMA mode and the COE */
	ग_लिखोl(XGMAC_OMR_TSF | XGMAC_OMR_RFD | XGMAC_OMR_RFA |
		XGMAC_OMR_RTC_256,
		ioaddr + XGMAC_OMR);

	/* Reset the MMC counters */
	ग_लिखोl(1, ioaddr + XGMAC_MMC_CTRL);
	वापस 0;
पूर्ण

/**
 *  xgmac_खोलो - खोलो entry poपूर्णांक of the driver
 *  @dev : poपूर्णांकer to the device काष्ठाure.
 *  Description:
 *  This function is the खोलो entry poपूर्णांक of the driver.
 *  Return value:
 *  0 on success and an appropriate (-)ve पूर्णांकeger as defined in त्रुटिसं.स
 *  file on failure.
 */
अटल पूर्णांक xgmac_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक ret;
	काष्ठा xgmac_priv *priv = netdev_priv(dev);
	व्योम __iomem *ioaddr = priv->base;

	/* Check that the MAC address is valid.  If its not, refuse
	 * to bring the device up. The user must specअगरy an
	 * address using the following linux command:
	 *      अगरconfig eth0 hw ether xx:xx:xx:xx:xx:xx  */
	अगर (!is_valid_ether_addr(dev->dev_addr)) अणु
		eth_hw_addr_अक्रमom(dev);
		netdev_dbg(priv->dev, "generated random MAC address %pM\n",
			dev->dev_addr);
	पूर्ण

	स_रखो(&priv->xstats, 0, माप(काष्ठा xgmac_extra_stats));

	/* Initialize the XGMAC and descriptors */
	xgmac_hw_init(dev);
	xgmac_set_mac_addr(ioaddr, dev->dev_addr, 0);
	xgmac_set_flow_ctrl(priv, priv->rx_छोड़ो, priv->tx_छोड़ो);

	ret = xgmac_dma_desc_rings_init(dev);
	अगर (ret < 0)
		वापस ret;

	/* Enable the MAC Rx/Tx */
	xgmac_mac_enable(ioaddr);

	napi_enable(&priv->napi);
	netअगर_start_queue(dev);

	/* Enable पूर्णांकerrupts */
	ग_लिखोl(DMA_INTR_DEFAULT_MASK, ioaddr + XGMAC_DMA_STATUS);
	ग_लिखोl(DMA_INTR_DEFAULT_MASK, ioaddr + XGMAC_DMA_INTR_ENA);

	वापस 0;
पूर्ण

/**
 *  xgmac_release - बंद entry poपूर्णांक of the driver
 *  @dev : device poपूर्णांकer.
 *  Description:
 *  This is the stop entry poपूर्णांक of the driver.
 */
अटल पूर्णांक xgmac_stop(काष्ठा net_device *dev)
अणु
	काष्ठा xgmac_priv *priv = netdev_priv(dev);

	अगर (पढ़ोl(priv->base + XGMAC_DMA_INTR_ENA))
		napi_disable(&priv->napi);

	ग_लिखोl(0, priv->base + XGMAC_DMA_INTR_ENA);

	netअगर_tx_disable(dev);

	/* Disable the MAC core */
	xgmac_mac_disable(priv->base);

	/* Release and मुक्त the Rx/Tx resources */
	xgmac_मुक्त_dma_desc_rings(priv);

	वापस 0;
पूर्ण

/**
 *  xgmac_xmit:
 *  @skb : the socket buffer
 *  @dev : device poपूर्णांकer
 *  Description : Tx entry poपूर्णांक of the driver.
 */
अटल netdev_tx_t xgmac_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा xgmac_priv *priv = netdev_priv(dev);
	अचिन्हित पूर्णांक entry;
	पूर्णांक i;
	u32 irq_flag;
	पूर्णांक nfrags = skb_shinfo(skb)->nr_frags;
	काष्ठा xgmac_dma_desc *desc, *first;
	अचिन्हित पूर्णांक desc_flags;
	अचिन्हित पूर्णांक len;
	dma_addr_t paddr;

	priv->tx_irq_cnt = (priv->tx_irq_cnt + 1) & (DMA_TX_RING_SZ/4 - 1);
	irq_flag = priv->tx_irq_cnt ? 0 : TXDESC_INTERRUPT;

	desc_flags = (skb->ip_summed == CHECKSUM_PARTIAL) ?
		TXDESC_CSUM_ALL : 0;
	entry = priv->tx_head;
	desc = priv->dma_tx + entry;
	first = desc;

	len = skb_headlen(skb);
	paddr = dma_map_single(priv->device, skb->data, len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(priv->device, paddr)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
	priv->tx_skbuff[entry] = skb;
	desc_set_buf_addr_and_size(desc, paddr, len);

	क्रम (i = 0; i < nfrags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		len = skb_frag_size(frag);

		paddr = skb_frag_dma_map(priv->device, frag, 0, len,
					 DMA_TO_DEVICE);
		अगर (dma_mapping_error(priv->device, paddr))
			जाओ dma_err;

		entry = dma_ring_incr(entry, DMA_TX_RING_SZ);
		desc = priv->dma_tx + entry;
		priv->tx_skbuff[entry] = skb;

		desc_set_buf_addr_and_size(desc, paddr, len);
		अगर (i < (nfrags - 1))
			desc_set_tx_owner(desc, desc_flags);
	पूर्ण

	/* Interrupt on completition only क्रम the latest segment */
	अगर (desc != first)
		desc_set_tx_owner(desc, desc_flags |
			TXDESC_LAST_SEG | irq_flag);
	अन्यथा
		desc_flags |= TXDESC_LAST_SEG | irq_flag;

	/* Set owner on first desc last to aव्योम race condition */
	wmb();
	desc_set_tx_owner(first, desc_flags | TXDESC_FIRST_SEG);

	ग_लिखोl(1, priv->base + XGMAC_DMA_TX_POLL);

	priv->tx_head = dma_ring_incr(entry, DMA_TX_RING_SZ);

	/* Ensure tx_head update is visible to tx completion */
	smp_mb();
	अगर (unlikely(tx_dma_ring_space(priv) <= MAX_SKB_FRAGS)) अणु
		netअगर_stop_queue(dev);
		/* Ensure netअगर_stop_queue is visible to tx completion */
		smp_mb();
		अगर (tx_dma_ring_space(priv) > MAX_SKB_FRAGS)
			netअगर_start_queue(dev);
	पूर्ण
	वापस NETDEV_TX_OK;

dma_err:
	entry = priv->tx_head;
	क्रम ( ; i > 0; i--) अणु
		entry = dma_ring_incr(entry, DMA_TX_RING_SZ);
		desc = priv->dma_tx + entry;
		priv->tx_skbuff[entry] = शून्य;
		dma_unmap_page(priv->device, desc_get_buf_addr(desc),
			       desc_get_buf_len(desc), DMA_TO_DEVICE);
		desc_clear_tx_owner(desc);
	पूर्ण
	desc = first;
	dma_unmap_single(priv->device, desc_get_buf_addr(desc),
			 desc_get_buf_len(desc), DMA_TO_DEVICE);
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक xgmac_rx(काष्ठा xgmac_priv *priv, पूर्णांक limit)
अणु
	अचिन्हित पूर्णांक entry;
	अचिन्हित पूर्णांक count = 0;
	काष्ठा xgmac_dma_desc *p;

	जबतक (count < limit) अणु
		पूर्णांक ip_checksum;
		काष्ठा sk_buff *skb;
		पूर्णांक frame_len;

		अगर (!dma_ring_cnt(priv->rx_head, priv->rx_tail, DMA_RX_RING_SZ))
			अवरोध;

		entry = priv->rx_tail;
		p = priv->dma_rx + entry;
		अगर (desc_get_owner(p))
			अवरोध;

		count++;
		priv->rx_tail = dma_ring_incr(priv->rx_tail, DMA_RX_RING_SZ);

		/* पढ़ो the status of the incoming frame */
		ip_checksum = desc_get_rx_status(priv, p);
		अगर (ip_checksum < 0)
			जारी;

		skb = priv->rx_skbuff[entry];
		अगर (unlikely(!skb)) अणु
			netdev_err(priv->dev, "Inconsistent Rx descriptor chain\n");
			अवरोध;
		पूर्ण
		priv->rx_skbuff[entry] = शून्य;

		frame_len = desc_get_rx_frame_len(p);
		netdev_dbg(priv->dev, "RX frame size %d, COE status: %d\n",
			frame_len, ip_checksum);

		skb_put(skb, frame_len);
		dma_unmap_single(priv->device, desc_get_buf_addr(p),
				 priv->dma_buf_sz - NET_IP_ALIGN, DMA_FROM_DEVICE);

		skb->protocol = eth_type_trans(skb, priv->dev);
		skb->ip_summed = ip_checksum;
		अगर (ip_checksum == CHECKSUM_NONE)
			netअगर_receive_skb(skb);
		अन्यथा
			napi_gro_receive(&priv->napi, skb);
	पूर्ण

	xgmac_rx_refill(priv);

	वापस count;
पूर्ण

/**
 *  xgmac_poll - xgmac poll method (NAPI)
 *  @napi : poपूर्णांकer to the napi काष्ठाure.
 *  @budget : maximum number of packets that the current CPU can receive from
 *	      all पूर्णांकerfaces.
 *  Description :
 *   This function implements the the reception process.
 *   Also it runs the TX completion thपढ़ो
 */
अटल पूर्णांक xgmac_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा xgmac_priv *priv = container_of(napi,
				       काष्ठा xgmac_priv, napi);
	पूर्णांक work_करोne = 0;

	xgmac_tx_complete(priv);
	work_करोne = xgmac_rx(priv, budget);

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		__raw_ग_लिखोl(DMA_INTR_DEFAULT_MASK, priv->base + XGMAC_DMA_INTR_ENA);
	पूर्ण
	वापस work_करोne;
पूर्ण

/**
 *  xgmac_tx_समयout
 *  @dev : Poपूर्णांकer to net device काष्ठाure
 *  @txqueue: index of the hung transmit queue
 *
 *  Description: this function is called when a packet transmission fails to
 *   complete within a reasonable पंचांगrate. The driver will mark the error in the
 *   netdev काष्ठाure and arrange क्रम the device to be reset to a sane state
 *   in order to transmit a new packet.
 */
अटल व्योम xgmac_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा xgmac_priv *priv = netdev_priv(dev);
	schedule_work(&priv->tx_समयout_work);
पूर्ण

/**
 *  xgmac_set_rx_mode - entry poपूर्णांक क्रम multicast addressing
 *  @dev : poपूर्णांकer to the device काष्ठाure
 *  Description:
 *  This function is a driver entry poपूर्णांक which माला_लो called by the kernel
 *  whenever multicast addresses must be enabled/disabled.
 *  Return value:
 *  व्योम.
 */
अटल व्योम xgmac_set_rx_mode(काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	काष्ठा xgmac_priv *priv = netdev_priv(dev);
	व्योम __iomem *ioaddr = priv->base;
	अचिन्हित पूर्णांक value = 0;
	u32 hash_filter[XGMAC_NUM_HASH];
	पूर्णांक reg = 1;
	काष्ठा netdev_hw_addr *ha;
	bool use_hash = false;

	netdev_dbg(priv->dev, "# mcasts %d, # unicast %d\n",
		 netdev_mc_count(dev), netdev_uc_count(dev));

	अगर (dev->flags & IFF_PROMISC)
		value |= XGMAC_FRAME_FILTER_PR;

	स_रखो(hash_filter, 0, माप(hash_filter));

	अगर (netdev_uc_count(dev) > priv->max_macs) अणु
		use_hash = true;
		value |= XGMAC_FRAME_FILTER_HUC | XGMAC_FRAME_FILTER_HPF;
	पूर्ण
	netdev_क्रम_each_uc_addr(ha, dev) अणु
		अगर (use_hash) अणु
			u32 bit_nr = ~ether_crc(ETH_ALEN, ha->addr) >> 23;

			/* The most signअगरicant 4 bits determine the रेजिस्टर to
			 * use (H/L) जबतक the other 5 bits determine the bit
			 * within the रेजिस्टर. */
			hash_filter[bit_nr >> 5] |= 1 << (bit_nr & 31);
		पूर्ण अन्यथा अणु
			xgmac_set_mac_addr(ioaddr, ha->addr, reg);
			reg++;
		पूर्ण
	पूर्ण

	अगर (dev->flags & IFF_ALLMULTI) अणु
		value |= XGMAC_FRAME_FILTER_PM;
		जाओ out;
	पूर्ण

	अगर ((netdev_mc_count(dev) + reg - 1) > priv->max_macs) अणु
		use_hash = true;
		value |= XGMAC_FRAME_FILTER_HMC | XGMAC_FRAME_FILTER_HPF;
	पूर्ण अन्यथा अणु
		use_hash = false;
	पूर्ण
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		अगर (use_hash) अणु
			u32 bit_nr = ~ether_crc(ETH_ALEN, ha->addr) >> 23;

			/* The most signअगरicant 4 bits determine the रेजिस्टर to
			 * use (H/L) जबतक the other 5 bits determine the bit
			 * within the रेजिस्टर. */
			hash_filter[bit_nr >> 5] |= 1 << (bit_nr & 31);
		पूर्ण अन्यथा अणु
			xgmac_set_mac_addr(ioaddr, ha->addr, reg);
			reg++;
		पूर्ण
	पूर्ण

out:
	क्रम (i = reg; i <= priv->max_macs; i++)
		xgmac_set_mac_addr(ioaddr, शून्य, i);
	क्रम (i = 0; i < XGMAC_NUM_HASH; i++)
		ग_लिखोl(hash_filter[i], ioaddr + XGMAC_HASH(i));

	ग_लिखोl(value, ioaddr + XGMAC_FRAME_FILTER);
पूर्ण

/**
 *  xgmac_change_mtu - entry poपूर्णांक to change MTU size क्रम the device.
 *  @dev : device poपूर्णांकer.
 *  @new_mtu : the new MTU size क्रम the device.
 *  Description: the Maximum Transfer Unit (MTU) is used by the network layer
 *  to drive packet transmission. Ethernet has an MTU of 1500 octets
 *  (ETH_DATA_LEN). This value can be changed with अगरconfig.
 *  Return value:
 *  0 on success and an appropriate (-)ve पूर्णांकeger as defined in त्रुटिसं.स
 *  file on failure.
 */
अटल पूर्णांक xgmac_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	/* Stop everything, get पढ़ोy to change the MTU */
	अगर (!netअगर_running(dev))
		वापस 0;

	/* Bring पूर्णांकerface करोwn, change mtu and bring पूर्णांकerface back up */
	xgmac_stop(dev);
	dev->mtu = new_mtu;
	वापस xgmac_खोलो(dev);
पूर्ण

अटल irqवापस_t xgmac_pmt_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 पूर्णांकr_status;
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा xgmac_priv *priv = netdev_priv(dev);
	व्योम __iomem *ioaddr = priv->base;

	पूर्णांकr_status = __raw_पढ़ोl(ioaddr + XGMAC_INT_STAT);
	अगर (पूर्णांकr_status & XGMAC_INT_STAT_PMT) अणु
		netdev_dbg(priv->dev, "received Magic frame\n");
		/* clear the PMT bits 5 and 6 by पढ़ोing the PMT */
		पढ़ोl(ioaddr + XGMAC_PMT);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t xgmac_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 पूर्णांकr_status;
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा xgmac_priv *priv = netdev_priv(dev);
	काष्ठा xgmac_extra_stats *x = &priv->xstats;

	/* पढ़ो the status रेजिस्टर (CSR5) */
	पूर्णांकr_status = __raw_पढ़ोl(priv->base + XGMAC_DMA_STATUS);
	पूर्णांकr_status &= __raw_पढ़ोl(priv->base + XGMAC_DMA_INTR_ENA);
	__raw_ग_लिखोl(पूर्णांकr_status, priv->base + XGMAC_DMA_STATUS);

	/* It displays the DMA process states (CSR5 रेजिस्टर) */
	/* ABNORMAL पूर्णांकerrupts */
	अगर (unlikely(पूर्णांकr_status & DMA_STATUS_AIS)) अणु
		अगर (पूर्णांकr_status & DMA_STATUS_TJT) अणु
			netdev_err(priv->dev, "transmit jabber\n");
			x->tx_jabber++;
		पूर्ण
		अगर (पूर्णांकr_status & DMA_STATUS_RU)
			x->rx_buf_unav++;
		अगर (पूर्णांकr_status & DMA_STATUS_RPS) अणु
			netdev_err(priv->dev, "receive process stopped\n");
			x->rx_process_stopped++;
		पूर्ण
		अगर (पूर्णांकr_status & DMA_STATUS_ETI) अणु
			netdev_err(priv->dev, "transmit early interrupt\n");
			x->tx_early++;
		पूर्ण
		अगर (पूर्णांकr_status & DMA_STATUS_TPS) अणु
			netdev_err(priv->dev, "transmit process stopped\n");
			x->tx_process_stopped++;
			schedule_work(&priv->tx_समयout_work);
		पूर्ण
		अगर (पूर्णांकr_status & DMA_STATUS_FBI) अणु
			netdev_err(priv->dev, "fatal bus error\n");
			x->fatal_bus_error++;
		पूर्ण
	पूर्ण

	/* TX/RX NORMAL पूर्णांकerrupts */
	अगर (पूर्णांकr_status & (DMA_STATUS_RI | DMA_STATUS_TU | DMA_STATUS_TI)) अणु
		__raw_ग_लिखोl(DMA_INTR_ABNORMAL, priv->base + XGMAC_DMA_INTR_ENA);
		napi_schedule(&priv->napi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/* Polling receive - used by NETCONSOLE and other diagnostic tools
 * to allow network I/O with पूर्णांकerrupts disabled. */
अटल व्योम xgmac_poll_controller(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	xgmac_पूर्णांकerrupt(dev->irq, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

अटल व्योम
xgmac_get_stats64(काष्ठा net_device *dev,
		  काष्ठा rtnl_link_stats64 *storage)
अणु
	काष्ठा xgmac_priv *priv = netdev_priv(dev);
	व्योम __iomem *base = priv->base;
	u32 count;

	spin_lock_bh(&priv->stats_lock);
	ग_लिखोl(XGMAC_MMC_CTRL_CNT_FRZ, base + XGMAC_MMC_CTRL);

	storage->rx_bytes = पढ़ोl(base + XGMAC_MMC_RXOCTET_G_LO);
	storage->rx_bytes |= (u64)(पढ़ोl(base + XGMAC_MMC_RXOCTET_G_HI)) << 32;

	storage->rx_packets = पढ़ोl(base + XGMAC_MMC_RXFRAME_GB_LO);
	storage->multicast = पढ़ोl(base + XGMAC_MMC_RXMCFRAME_G);
	storage->rx_crc_errors = पढ़ोl(base + XGMAC_MMC_RXCRCERR);
	storage->rx_length_errors = पढ़ोl(base + XGMAC_MMC_RXLENGTHERR);
	storage->rx_missed_errors = पढ़ोl(base + XGMAC_MMC_RXOVERFLOW);

	storage->tx_bytes = पढ़ोl(base + XGMAC_MMC_TXOCTET_G_LO);
	storage->tx_bytes |= (u64)(पढ़ोl(base + XGMAC_MMC_TXOCTET_G_HI)) << 32;

	count = पढ़ोl(base + XGMAC_MMC_TXFRAME_GB_LO);
	storage->tx_errors = count - पढ़ोl(base + XGMAC_MMC_TXFRAME_G_LO);
	storage->tx_packets = count;
	storage->tx_fअगरo_errors = पढ़ोl(base + XGMAC_MMC_TXUNDERFLOW);

	ग_लिखोl(0, base + XGMAC_MMC_CTRL);
	spin_unlock_bh(&priv->stats_lock);
पूर्ण

अटल पूर्णांक xgmac_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा xgmac_priv *priv = netdev_priv(dev);
	व्योम __iomem *ioaddr = priv->base;
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);

	xgmac_set_mac_addr(ioaddr, dev->dev_addr, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक xgmac_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	u32 ctrl;
	काष्ठा xgmac_priv *priv = netdev_priv(dev);
	व्योम __iomem *ioaddr = priv->base;
	netdev_features_t changed = dev->features ^ features;

	अगर (!(changed & NETIF_F_RXCSUM))
		वापस 0;

	ctrl = पढ़ोl(ioaddr + XGMAC_CONTROL);
	अगर (features & NETIF_F_RXCSUM)
		ctrl |= XGMAC_CONTROL_IPC;
	अन्यथा
		ctrl &= ~XGMAC_CONTROL_IPC;
	ग_लिखोl(ctrl, ioaddr + XGMAC_CONTROL);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops xgmac_netdev_ops = अणु
	.nकरो_खोलो = xgmac_खोलो,
	.nकरो_start_xmit = xgmac_xmit,
	.nकरो_stop = xgmac_stop,
	.nकरो_change_mtu = xgmac_change_mtu,
	.nकरो_set_rx_mode = xgmac_set_rx_mode,
	.nकरो_tx_समयout = xgmac_tx_समयout,
	.nकरो_get_stats64 = xgmac_get_stats64,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller = xgmac_poll_controller,
#पूर्ण_अगर
	.nकरो_set_mac_address = xgmac_set_mac_address,
	.nकरो_set_features = xgmac_set_features,
पूर्ण;

अटल पूर्णांक xgmac_ethtool_get_link_ksettings(काष्ठा net_device *dev,
					    काष्ठा ethtool_link_ksettings *cmd)
अणु
	cmd->base.स्वतःneg = 0;
	cmd->base.duplex = DUPLEX_FULL;
	cmd->base.speed = 10000;
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported, 0);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising, 0);
	वापस 0;
पूर्ण

अटल व्योम xgmac_get_छोड़ोparam(काष्ठा net_device *netdev,
				      काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा xgmac_priv *priv = netdev_priv(netdev);

	छोड़ो->rx_छोड़ो = priv->rx_छोड़ो;
	छोड़ो->tx_छोड़ो = priv->tx_छोड़ो;
पूर्ण

अटल पूर्णांक xgmac_set_छोड़ोparam(काष्ठा net_device *netdev,
				     काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा xgmac_priv *priv = netdev_priv(netdev);

	अगर (छोड़ो->स्वतःneg)
		वापस -EINVAL;

	वापस xgmac_set_flow_ctrl(priv, छोड़ो->rx_छोड़ो, छोड़ो->tx_छोड़ो);
पूर्ण

काष्ठा xgmac_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक stat_offset;
	bool is_reg;
पूर्ण;

#घोषणा XGMAC_STAT(m)	\
	अणु #m, दुरत्व(काष्ठा xgmac_priv, xstats.m), false पूर्ण
#घोषणा XGMAC_HW_STAT(m, reg_offset)	\
	अणु #m, reg_offset, true पूर्ण

अटल स्थिर काष्ठा xgmac_stats xgmac_gstrings_stats[] = अणु
	XGMAC_STAT(tx_frame_flushed),
	XGMAC_STAT(tx_payload_error),
	XGMAC_STAT(tx_ip_header_error),
	XGMAC_STAT(tx_local_fault),
	XGMAC_STAT(tx_remote_fault),
	XGMAC_STAT(tx_early),
	XGMAC_STAT(tx_process_stopped),
	XGMAC_STAT(tx_jabber),
	XGMAC_STAT(rx_buf_unav),
	XGMAC_STAT(rx_process_stopped),
	XGMAC_STAT(rx_payload_error),
	XGMAC_STAT(rx_ip_header_error),
	XGMAC_STAT(rx_da_filter_fail),
	XGMAC_STAT(fatal_bus_error),
	XGMAC_HW_STAT(rx_watchकरोg, XGMAC_MMC_RXWATCHDOG),
	XGMAC_HW_STAT(tx_vlan, XGMAC_MMC_TXVLANFRAME),
	XGMAC_HW_STAT(rx_vlan, XGMAC_MMC_RXVLANFRAME),
	XGMAC_HW_STAT(tx_छोड़ो, XGMAC_MMC_TXPAUSEFRAME),
	XGMAC_HW_STAT(rx_छोड़ो, XGMAC_MMC_RXPAUSEFRAME),
पूर्ण;
#घोषणा XGMAC_STATS_LEN ARRAY_SIZE(xgmac_gstrings_stats)

अटल व्योम xgmac_get_ethtool_stats(काष्ठा net_device *dev,
					 काष्ठा ethtool_stats *dummy,
					 u64 *data)
अणु
	काष्ठा xgmac_priv *priv = netdev_priv(dev);
	व्योम *p = priv;
	पूर्णांक i;

	क्रम (i = 0; i < XGMAC_STATS_LEN; i++) अणु
		अगर (xgmac_gstrings_stats[i].is_reg)
			*data++ = पढ़ोl(priv->base +
				xgmac_gstrings_stats[i].stat_offset);
		अन्यथा
			*data++ = *(u32 *)(p +
				xgmac_gstrings_stats[i].stat_offset);
	पूर्ण
पूर्ण

अटल पूर्णांक xgmac_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस XGMAC_STATS_LEN;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम xgmac_get_strings(काष्ठा net_device *dev, u32 stringset,
				   u8 *data)
अणु
	पूर्णांक i;
	u8 *p = data;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < XGMAC_STATS_LEN; i++) अणु
			स_नकल(p, xgmac_gstrings_stats[i].stat_string,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम xgmac_get_wol(काष्ठा net_device *dev,
			       काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा xgmac_priv *priv = netdev_priv(dev);

	अगर (device_can_wakeup(priv->device)) अणु
		wol->supported = WAKE_MAGIC | WAKE_UCAST;
		wol->wolopts = priv->wolopts;
	पूर्ण
पूर्ण

अटल पूर्णांक xgmac_set_wol(काष्ठा net_device *dev,
			      काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा xgmac_priv *priv = netdev_priv(dev);
	u32 support = WAKE_MAGIC | WAKE_UCAST;

	अगर (!device_can_wakeup(priv->device))
		वापस -ENOTSUPP;

	अगर (wol->wolopts & ~support)
		वापस -EINVAL;

	priv->wolopts = wol->wolopts;

	अगर (wol->wolopts) अणु
		device_set_wakeup_enable(priv->device, 1);
		enable_irq_wake(dev->irq);
	पूर्ण अन्यथा अणु
		device_set_wakeup_enable(priv->device, 0);
		disable_irq_wake(dev->irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops xgmac_ethtool_ops = अणु
	.get_link = ethtool_op_get_link,
	.get_छोड़ोparam = xgmac_get_छोड़ोparam,
	.set_छोड़ोparam = xgmac_set_छोड़ोparam,
	.get_ethtool_stats = xgmac_get_ethtool_stats,
	.get_strings = xgmac_get_strings,
	.get_wol = xgmac_get_wol,
	.set_wol = xgmac_set_wol,
	.get_sset_count = xgmac_get_sset_count,
	.get_link_ksettings = xgmac_ethtool_get_link_ksettings,
पूर्ण;

/**
 * xgmac_probe
 * @pdev: platक्रमm device poपूर्णांकer
 * Description: the driver is initialized through platक्रमm_device.
 */
अटल पूर्णांक xgmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	काष्ठा resource *res;
	काष्ठा net_device *ndev = शून्य;
	काष्ठा xgmac_priv *priv = शून्य;
	u32 uid;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	अगर (!request_mem_region(res->start, resource_size(res), pdev->name))
		वापस -EBUSY;

	ndev = alloc_etherdev(माप(काष्ठा xgmac_priv));
	अगर (!ndev) अणु
		ret = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	SET_NETDEV_DEV(ndev, &pdev->dev);
	priv = netdev_priv(ndev);
	platक्रमm_set_drvdata(pdev, ndev);
	ndev->netdev_ops = &xgmac_netdev_ops;
	ndev->ethtool_ops = &xgmac_ethtool_ops;
	spin_lock_init(&priv->stats_lock);
	INIT_WORK(&priv->tx_समयout_work, xgmac_tx_समयout_work);

	priv->device = &pdev->dev;
	priv->dev = ndev;
	priv->rx_छोड़ो = 1;
	priv->tx_छोड़ो = 1;

	priv->base = ioremap(res->start, resource_size(res));
	अगर (!priv->base) अणु
		netdev_err(ndev, "ioremap failed\n");
		ret = -ENOMEM;
		जाओ err_io;
	पूर्ण

	uid = पढ़ोl(priv->base + XGMAC_VERSION);
	netdev_info(ndev, "h/w version is 0x%x\n", uid);

	/* Figure out how many valid mac address filter रेजिस्टरs we have */
	ग_लिखोl(1, priv->base + XGMAC_ADDR_HIGH(31));
	अगर (पढ़ोl(priv->base + XGMAC_ADDR_HIGH(31)) == 1)
		priv->max_macs = 31;
	अन्यथा
		priv->max_macs = 7;

	ग_लिखोl(0, priv->base + XGMAC_DMA_INTR_ENA);
	ndev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (ndev->irq == -ENXIO) अणु
		netdev_err(ndev, "No irq resource\n");
		ret = ndev->irq;
		जाओ err_irq;
	पूर्ण

	ret = request_irq(ndev->irq, xgmac_पूर्णांकerrupt, 0,
			  dev_name(&pdev->dev), ndev);
	अगर (ret < 0) अणु
		netdev_err(ndev, "Could not request irq %d - ret %d)\n",
			ndev->irq, ret);
		जाओ err_irq;
	पूर्ण

	priv->pmt_irq = platक्रमm_get_irq(pdev, 1);
	अगर (priv->pmt_irq == -ENXIO) अणु
		netdev_err(ndev, "No pmt irq resource\n");
		ret = priv->pmt_irq;
		जाओ err_pmt_irq;
	पूर्ण

	ret = request_irq(priv->pmt_irq, xgmac_pmt_पूर्णांकerrupt, 0,
			  dev_name(&pdev->dev), ndev);
	अगर (ret < 0) अणु
		netdev_err(ndev, "Could not request irq %d - ret %d)\n",
			priv->pmt_irq, ret);
		जाओ err_pmt_irq;
	पूर्ण

	device_set_wakeup_capable(&pdev->dev, 1);
	अगर (device_can_wakeup(priv->device))
		priv->wolopts = WAKE_MAGIC;	/* Magic Frame as शेष */

	ndev->hw_features = NETIF_F_SG | NETIF_F_HIGHDMA;
	अगर (पढ़ोl(priv->base + XGMAC_DMA_HW_FEATURE) & DMA_HW_FEAT_TXCOESEL)
		ndev->hw_features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
				     NETIF_F_RXCSUM;
	ndev->features |= ndev->hw_features;
	ndev->priv_flags |= IFF_UNICAST_FLT;

	/* MTU range: 46 - 9000 */
	ndev->min_mtu = ETH_ZLEN - ETH_HLEN;
	ndev->max_mtu = XGMAC_MAX_MTU;

	/* Get the MAC address */
	xgmac_get_mac_addr(priv->base, ndev->dev_addr, 0);
	अगर (!is_valid_ether_addr(ndev->dev_addr))
		netdev_warn(ndev, "MAC address %pM not valid",
			 ndev->dev_addr);

	netअगर_napi_add(ndev, &priv->napi, xgmac_poll, 64);
	ret = रेजिस्टर_netdev(ndev);
	अगर (ret)
		जाओ err_reg;

	वापस 0;

err_reg:
	netअगर_napi_del(&priv->napi);
	मुक्त_irq(priv->pmt_irq, ndev);
err_pmt_irq:
	मुक्त_irq(ndev->irq, ndev);
err_irq:
	iounmap(priv->base);
err_io:
	मुक्त_netdev(ndev);
err_alloc:
	release_mem_region(res->start, resource_size(res));
	वापस ret;
पूर्ण

/**
 * xgmac_dvr_हटाओ
 * @pdev: platक्रमm device poपूर्णांकer
 * Description: this function resets the TX/RX processes, disables the MAC RX/TX
 * changes the link status, releases the DMA descriptor rings,
 * unरेजिस्टरs the MDIO bus and unmaps the allocated memory.
 */
अटल पूर्णांक xgmac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा xgmac_priv *priv = netdev_priv(ndev);
	काष्ठा resource *res;

	xgmac_mac_disable(priv->base);

	/* Free the IRQ lines */
	मुक्त_irq(ndev->irq, ndev);
	मुक्त_irq(priv->pmt_irq, ndev);

	unरेजिस्टर_netdev(ndev);
	netअगर_napi_del(&priv->napi);

	iounmap(priv->base);
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, resource_size(res));

	मुक्त_netdev(ndev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम xgmac_pmt(व्योम __iomem *ioaddr, अचिन्हित दीर्घ mode)
अणु
	अचिन्हित पूर्णांक pmt = 0;

	अगर (mode & WAKE_MAGIC)
		pmt |= XGMAC_PMT_POWERDOWN | XGMAC_PMT_MAGIC_PKT_EN;
	अगर (mode & WAKE_UCAST)
		pmt |= XGMAC_PMT_POWERDOWN | XGMAC_PMT_GLBL_UNICAST;

	ग_लिखोl(pmt, ioaddr + XGMAC_PMT);
पूर्ण

अटल पूर्णांक xgmac_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा xgmac_priv *priv = netdev_priv(ndev);
	u32 value;

	अगर (!ndev || !netअगर_running(ndev))
		वापस 0;

	netअगर_device_detach(ndev);
	napi_disable(&priv->napi);
	ग_लिखोl(0, priv->base + XGMAC_DMA_INTR_ENA);

	अगर (device_may_wakeup(priv->device)) अणु
		/* Stop TX/RX DMA Only */
		value = पढ़ोl(priv->base + XGMAC_DMA_CONTROL);
		value &= ~(DMA_CONTROL_ST | DMA_CONTROL_SR);
		ग_लिखोl(value, priv->base + XGMAC_DMA_CONTROL);

		xgmac_pmt(priv->base, priv->wolopts);
	पूर्ण अन्यथा
		xgmac_mac_disable(priv->base);

	वापस 0;
पूर्ण

अटल पूर्णांक xgmac_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा xgmac_priv *priv = netdev_priv(ndev);
	व्योम __iomem *ioaddr = priv->base;

	अगर (!netअगर_running(ndev))
		वापस 0;

	xgmac_pmt(ioaddr, 0);

	/* Enable the MAC and DMA */
	xgmac_mac_enable(ioaddr);
	ग_लिखोl(DMA_INTR_DEFAULT_MASK, ioaddr + XGMAC_DMA_STATUS);
	ग_लिखोl(DMA_INTR_DEFAULT_MASK, ioaddr + XGMAC_DMA_INTR_ENA);

	netअगर_device_attach(ndev);
	napi_enable(&priv->napi);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(xgmac_pm_ops, xgmac_suspend, xgmac_resume);

अटल स्थिर काष्ठा of_device_id xgmac_of_match[] = अणु
	अणु .compatible = "calxeda,hb-xgmac", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xgmac_of_match);

अटल काष्ठा platक्रमm_driver xgmac_driver = अणु
	.driver = अणु
		.name = "calxedaxgmac",
		.of_match_table = xgmac_of_match,
		.pm = &xgmac_pm_ops,
	पूर्ण,
	.probe = xgmac_probe,
	.हटाओ = xgmac_हटाओ,
पूर्ण;

module_platक्रमm_driver(xgmac_driver);

MODULE_AUTHOR("Calxeda, Inc.");
MODULE_DESCRIPTION("Calxeda 10G XGMAC driver");
MODULE_LICENSE("GPL v2");
