<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Aपंचांगel MACB Ethernet Controller driver
 *
 * Copyright (C) 2004-2006 Aपंचांगel Corporation
 */
#अगर_अघोषित _MACB_H
#घोषणा _MACB_H

#समावेश <linux/clk.h>
#समावेश <linux/phylink.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/पूर्णांकerrupt.h>

#अगर defined(CONFIG_ARCH_DMA_ADDR_T_64BIT) || defined(CONFIG_MACB_USE_HWSTAMP)
#घोषणा MACB_EXT_DESC
#पूर्ण_अगर

#घोषणा MACB_GREGS_NBR 16
#घोषणा MACB_GREGS_VERSION 2
#घोषणा MACB_MAX_QUEUES 8

/* MACB रेजिस्टर offsets */
#घोषणा MACB_NCR		0x0000 /* Network Control */
#घोषणा MACB_NCFGR		0x0004 /* Network Config */
#घोषणा MACB_NSR		0x0008 /* Network Status */
#घोषणा MACB_TAR		0x000c /* AT91RM9200 only */
#घोषणा MACB_TCR		0x0010 /* AT91RM9200 only */
#घोषणा MACB_TSR		0x0014 /* Transmit Status */
#घोषणा MACB_RBQP		0x0018 /* RX Q Base Address */
#घोषणा MACB_TBQP		0x001c /* TX Q Base Address */
#घोषणा MACB_RSR		0x0020 /* Receive Status */
#घोषणा MACB_ISR		0x0024 /* Interrupt Status */
#घोषणा MACB_IER		0x0028 /* Interrupt Enable */
#घोषणा MACB_IDR		0x002c /* Interrupt Disable */
#घोषणा MACB_IMR		0x0030 /* Interrupt Mask */
#घोषणा MACB_MAN		0x0034 /* PHY Maपूर्णांकenance */
#घोषणा MACB_PTR		0x0038
#घोषणा MACB_PFR		0x003c
#घोषणा MACB_FTO		0x0040
#घोषणा MACB_SCF		0x0044
#घोषणा MACB_MCF		0x0048
#घोषणा MACB_FRO		0x004c
#घोषणा MACB_FCSE		0x0050
#घोषणा MACB_ALE		0x0054
#घोषणा MACB_DTF		0x0058
#घोषणा MACB_LCOL		0x005c
#घोषणा MACB_EXCOL		0x0060
#घोषणा MACB_TUND		0x0064
#घोषणा MACB_CSE		0x0068
#घोषणा MACB_RRE		0x006c
#घोषणा MACB_ROVR		0x0070
#घोषणा MACB_RSE		0x0074
#घोषणा MACB_ELE		0x0078
#घोषणा MACB_RJA		0x007c
#घोषणा MACB_USF		0x0080
#घोषणा MACB_STE		0x0084
#घोषणा MACB_RLE		0x0088
#घोषणा MACB_TPF		0x008c
#घोषणा MACB_HRB		0x0090
#घोषणा MACB_HRT		0x0094
#घोषणा MACB_SA1B		0x0098
#घोषणा MACB_SA1T		0x009c
#घोषणा MACB_SA2B		0x00a0
#घोषणा MACB_SA2T		0x00a4
#घोषणा MACB_SA3B		0x00a8
#घोषणा MACB_SA3T		0x00ac
#घोषणा MACB_SA4B		0x00b0
#घोषणा MACB_SA4T		0x00b4
#घोषणा MACB_TID		0x00b8
#घोषणा MACB_TPQ		0x00bc
#घोषणा MACB_USRIO		0x00c0
#घोषणा MACB_WOL		0x00c4
#घोषणा MACB_MID		0x00fc
#घोषणा MACB_TBQPH		0x04C8
#घोषणा MACB_RBQPH		0x04D4

/* GEM रेजिस्टर offsets. */
#घोषणा GEM_NCR			0x0000 /* Network Control */
#घोषणा GEM_NCFGR		0x0004 /* Network Config */
#घोषणा GEM_USRIO		0x000c /* User IO */
#घोषणा GEM_DMACFG		0x0010 /* DMA Configuration */
#घोषणा GEM_JML			0x0048 /* Jumbo Max Length */
#घोषणा GEM_HS_MAC_CONFIG	0x0050 /* GEM high speed config */
#घोषणा GEM_HRB			0x0080 /* Hash Bottom */
#घोषणा GEM_HRT			0x0084 /* Hash Top */
#घोषणा GEM_SA1B		0x0088 /* Specअगरic1 Bottom */
#घोषणा GEM_SA1T		0x008C /* Specअगरic1 Top */
#घोषणा GEM_SA2B		0x0090 /* Specअगरic2 Bottom */
#घोषणा GEM_SA2T		0x0094 /* Specअगरic2 Top */
#घोषणा GEM_SA3B		0x0098 /* Specअगरic3 Bottom */
#घोषणा GEM_SA3T		0x009C /* Specअगरic3 Top */
#घोषणा GEM_SA4B		0x00A0 /* Specअगरic4 Bottom */
#घोषणा GEM_SA4T		0x00A4 /* Specअगरic4 Top */
#घोषणा GEM_WOL			0x00b8 /* Wake on LAN */
#घोषणा GEM_EFTSH		0x00e8 /* PTP Event Frame Transmitted Seconds Register 47:32 */
#घोषणा GEM_EFRSH		0x00ec /* PTP Event Frame Received Seconds Register 47:32 */
#घोषणा GEM_PEFTSH		0x00f0 /* PTP Peer Event Frame Transmitted Seconds Register 47:32 */
#घोषणा GEM_PEFRSH		0x00f4 /* PTP Peer Event Frame Received Seconds Register 47:32 */
#घोषणा GEM_OTX			0x0100 /* Octets transmitted */
#घोषणा GEM_OCTTXL		0x0100 /* Octets transmitted [31:0] */
#घोषणा GEM_OCTTXH		0x0104 /* Octets transmitted [47:32] */
#घोषणा GEM_TXCNT		0x0108 /* Frames Transmitted counter */
#घोषणा GEM_TXBCCNT		0x010c /* Broadcast Frames counter */
#घोषणा GEM_TXMCCNT		0x0110 /* Multicast Frames counter */
#घोषणा GEM_TXPAUSECNT		0x0114 /* Pause Frames Transmitted Counter */
#घोषणा GEM_TX64CNT		0x0118 /* 64 byte Frames TX counter */
#घोषणा GEM_TX65CNT		0x011c /* 65-127 byte Frames TX counter */
#घोषणा GEM_TX128CNT		0x0120 /* 128-255 byte Frames TX counter */
#घोषणा GEM_TX256CNT		0x0124 /* 256-511 byte Frames TX counter */
#घोषणा GEM_TX512CNT		0x0128 /* 512-1023 byte Frames TX counter */
#घोषणा GEM_TX1024CNT		0x012c /* 1024-1518 byte Frames TX counter */
#घोषणा GEM_TX1519CNT		0x0130 /* 1519+ byte Frames TX counter */
#घोषणा GEM_TXURUNCNT		0x0134 /* TX under run error counter */
#घोषणा GEM_SNGLCOLLCNT		0x0138 /* Single Collision Frame Counter */
#घोषणा GEM_MULTICOLLCNT	0x013c /* Multiple Collision Frame Counter */
#घोषणा GEM_EXCESSCOLLCNT	0x0140 /* Excessive Collision Frame Counter */
#घोषणा GEM_LATECOLLCNT		0x0144 /* Late Collision Frame Counter */
#घोषणा GEM_TXDEFERCNT		0x0148 /* Deferred Transmission Frame Counter */
#घोषणा GEM_TXCSENSECNT		0x014c /* Carrier Sense Error Counter */
#घोषणा GEM_ORX			0x0150 /* Octets received */
#घोषणा GEM_OCTRXL		0x0150 /* Octets received [31:0] */
#घोषणा GEM_OCTRXH		0x0154 /* Octets received [47:32] */
#घोषणा GEM_RXCNT		0x0158 /* Frames Received Counter */
#घोषणा GEM_RXBROADCNT		0x015c /* Broadcast Frames Received Counter */
#घोषणा GEM_RXMULTICNT		0x0160 /* Multicast Frames Received Counter */
#घोषणा GEM_RXPAUSECNT		0x0164 /* Pause Frames Received Counter */
#घोषणा GEM_RX64CNT		0x0168 /* 64 byte Frames RX Counter */
#घोषणा GEM_RX65CNT		0x016c /* 65-127 byte Frames RX Counter */
#घोषणा GEM_RX128CNT		0x0170 /* 128-255 byte Frames RX Counter */
#घोषणा GEM_RX256CNT		0x0174 /* 256-511 byte Frames RX Counter */
#घोषणा GEM_RX512CNT		0x0178 /* 512-1023 byte Frames RX Counter */
#घोषणा GEM_RX1024CNT		0x017c /* 1024-1518 byte Frames RX Counter */
#घोषणा GEM_RX1519CNT		0x0180 /* 1519+ byte Frames RX Counter */
#घोषणा GEM_RXUNDRCNT		0x0184 /* Undersize Frames Received Counter */
#घोषणा GEM_RXOVRCNT		0x0188 /* Oversize Frames Received Counter */
#घोषणा GEM_RXJABCNT		0x018c /* Jabbers Received Counter */
#घोषणा GEM_RXFCSCNT		0x0190 /* Frame Check Sequence Error Counter */
#घोषणा GEM_RXLENGTHCNT		0x0194 /* Length Field Error Counter */
#घोषणा GEM_RXSYMBCNT		0x0198 /* Symbol Error Counter */
#घोषणा GEM_RXALIGNCNT		0x019c /* Alignment Error Counter */
#घोषणा GEM_RXRESERRCNT		0x01a0 /* Receive Resource Error Counter */
#घोषणा GEM_RXORCNT		0x01a4 /* Receive Overrun Counter */
#घोषणा GEM_RXIPCCNT		0x01a8 /* IP header Checksum Error Counter */
#घोषणा GEM_RXTCPCCNT		0x01ac /* TCP Checksum Error Counter */
#घोषणा GEM_RXUDPCCNT		0x01b0 /* UDP Checksum Error Counter */
#घोषणा GEM_TISUBN		0x01bc /* 1588 Timer Increment Sub-ns */
#घोषणा GEM_TSH			0x01c0 /* 1588 Timer Seconds High */
#घोषणा GEM_TSL			0x01d0 /* 1588 Timer Seconds Low */
#घोषणा GEM_TN			0x01d4 /* 1588 Timer Nanoseconds */
#घोषणा GEM_TA			0x01d8 /* 1588 Timer Adjust */
#घोषणा GEM_TI			0x01dc /* 1588 Timer Increment */
#घोषणा GEM_EFTSL		0x01e0 /* PTP Event Frame Tx Seconds Low */
#घोषणा GEM_EFTN		0x01e4 /* PTP Event Frame Tx Nanoseconds */
#घोषणा GEM_EFRSL		0x01e8 /* PTP Event Frame Rx Seconds Low */
#घोषणा GEM_EFRN		0x01ec /* PTP Event Frame Rx Nanoseconds */
#घोषणा GEM_PEFTSL		0x01f0 /* PTP Peer Event Frame Tx Secs Low */
#घोषणा GEM_PEFTN		0x01f4 /* PTP Peer Event Frame Tx Ns */
#घोषणा GEM_PEFRSL		0x01f8 /* PTP Peer Event Frame Rx Sec Low */
#घोषणा GEM_PEFRN		0x01fc /* PTP Peer Event Frame Rx Ns */
#घोषणा GEM_PCSCNTRL		0x0200 /* PCS Control */
#घोषणा GEM_PCSSTS		0x0204 /* PCS Status */
#घोषणा GEM_PCSPHYTOPID		0x0208 /* PCS PHY Top ID */
#घोषणा GEM_PCSPHYBOTID		0x020c /* PCS PHY Bottom ID */
#घोषणा GEM_PCSANADV		0x0210 /* PCS AN Advertisement */
#घोषणा GEM_PCSANLPBASE		0x0214 /* PCS AN Link Partner Base */
#घोषणा GEM_PCSANEXP		0x0218 /* PCS AN Expansion */
#घोषणा GEM_PCSANNPTX		0x021c /* PCS AN Next Page TX */
#घोषणा GEM_PCSANNPLP		0x0220 /* PCS AN Next Page LP */
#घोषणा GEM_PCSANEXTSTS		0x023c /* PCS AN Extended Status */
#घोषणा GEM_DCFG1		0x0280 /* Design Config 1 */
#घोषणा GEM_DCFG2		0x0284 /* Design Config 2 */
#घोषणा GEM_DCFG3		0x0288 /* Design Config 3 */
#घोषणा GEM_DCFG4		0x028c /* Design Config 4 */
#घोषणा GEM_DCFG5		0x0290 /* Design Config 5 */
#घोषणा GEM_DCFG6		0x0294 /* Design Config 6 */
#घोषणा GEM_DCFG7		0x0298 /* Design Config 7 */
#घोषणा GEM_DCFG8		0x029C /* Design Config 8 */
#घोषणा GEM_DCFG10		0x02A4 /* Design Config 10 */
#घोषणा GEM_DCFG12		0x02AC /* Design Config 12 */
#घोषणा GEM_USX_CONTROL		0x0A80 /* High speed PCS control रेजिस्टर */
#घोषणा GEM_USX_STATUS		0x0A88 /* High speed PCS status रेजिस्टर */

#घोषणा GEM_TXBDCTRL	0x04cc /* TX Buffer Descriptor control रेजिस्टर */
#घोषणा GEM_RXBDCTRL	0x04d0 /* RX Buffer Descriptor control रेजिस्टर */

/* Screener Type 2 match रेजिस्टरs */
#घोषणा GEM_SCRT2		0x540

/* EtherType रेजिस्टरs */
#घोषणा GEM_ETHT		0x06E0

/* Type 2 compare रेजिस्टरs */
#घोषणा GEM_T2CMPW0		0x0700
#घोषणा GEM_T2CMPW1		0x0704
#घोषणा T2CMP_OFST(t2idx)	(t2idx * 2)

/* type 2 compare रेजिस्टरs
 * each location requires 3 compare regs
 */
#घोषणा GEM_IP4SRC_CMP(idx)		(idx * 3)
#घोषणा GEM_IP4DST_CMP(idx)		(idx * 3 + 1)
#घोषणा GEM_PORT_CMP(idx)		(idx * 3 + 2)

/* Which screening type 2 EtherType रेजिस्टर will be used (0 - 7) */
#घोषणा SCRT2_ETHT		0

#घोषणा GEM_ISR(hw_q)		(0x0400 + ((hw_q) << 2))
#घोषणा GEM_TBQP(hw_q)		(0x0440 + ((hw_q) << 2))
#घोषणा GEM_TBQPH(hw_q)		(0x04C8)
#घोषणा GEM_RBQP(hw_q)		(0x0480 + ((hw_q) << 2))
#घोषणा GEM_RBQS(hw_q)		(0x04A0 + ((hw_q) << 2))
#घोषणा GEM_RBQPH(hw_q)		(0x04D4)
#घोषणा GEM_IER(hw_q)		(0x0600 + ((hw_q) << 2))
#घोषणा GEM_IDR(hw_q)		(0x0620 + ((hw_q) << 2))
#घोषणा GEM_IMR(hw_q)		(0x0640 + ((hw_q) << 2))

/* Bitfields in NCR */
#घोषणा MACB_LB_OFFSET		0 /* reserved */
#घोषणा MACB_LB_SIZE		1
#घोषणा MACB_LLB_OFFSET		1 /* Loop back local */
#घोषणा MACB_LLB_SIZE		1
#घोषणा MACB_RE_OFFSET		2 /* Receive enable */
#घोषणा MACB_RE_SIZE		1
#घोषणा MACB_TE_OFFSET		3 /* Transmit enable */
#घोषणा MACB_TE_SIZE		1
#घोषणा MACB_MPE_OFFSET		4 /* Management port enable */
#घोषणा MACB_MPE_SIZE		1
#घोषणा MACB_CLRSTAT_OFFSET	5 /* Clear stats regs */
#घोषणा MACB_CLRSTAT_SIZE	1
#घोषणा MACB_INCSTAT_OFFSET	6 /* Incremental stats regs */
#घोषणा MACB_INCSTAT_SIZE	1
#घोषणा MACB_WESTAT_OFFSET	7 /* Write enable stats regs */
#घोषणा MACB_WESTAT_SIZE	1
#घोषणा MACB_BP_OFFSET		8 /* Back pressure */
#घोषणा MACB_BP_SIZE		1
#घोषणा MACB_TSTART_OFFSET	9 /* Start transmission */
#घोषणा MACB_TSTART_SIZE	1
#घोषणा MACB_THALT_OFFSET	10 /* Transmit halt */
#घोषणा MACB_THALT_SIZE		1
#घोषणा MACB_NCR_TPF_OFFSET	11 /* Transmit छोड़ो frame */
#घोषणा MACB_NCR_TPF_SIZE	1
#घोषणा MACB_TZQ_OFFSET		12 /* Transmit zero quantum छोड़ो frame */
#घोषणा MACB_TZQ_SIZE		1
#घोषणा MACB_SRTSM_OFFSET	15
#घोषणा MACB_OSSMODE_OFFSET 24 /* Enable One Step Synchro Mode */
#घोषणा MACB_OSSMODE_SIZE	1

/* Bitfields in NCFGR */
#घोषणा MACB_SPD_OFFSET		0 /* Speed */
#घोषणा MACB_SPD_SIZE		1
#घोषणा MACB_FD_OFFSET		1 /* Full duplex */
#घोषणा MACB_FD_SIZE		1
#घोषणा MACB_BIT_RATE_OFFSET	2 /* Discard non-VLAN frames */
#घोषणा MACB_BIT_RATE_SIZE	1
#घोषणा MACB_JFRAME_OFFSET	3 /* reserved */
#घोषणा MACB_JFRAME_SIZE	1
#घोषणा MACB_CAF_OFFSET		4 /* Copy all frames */
#घोषणा MACB_CAF_SIZE		1
#घोषणा MACB_NBC_OFFSET		5 /* No broadcast */
#घोषणा MACB_NBC_SIZE		1
#घोषणा MACB_NCFGR_MTI_OFFSET	6 /* Multicast hash enable */
#घोषणा MACB_NCFGR_MTI_SIZE	1
#घोषणा MACB_UNI_OFFSET		7 /* Unicast hash enable */
#घोषणा MACB_UNI_SIZE		1
#घोषणा MACB_BIG_OFFSET		8 /* Receive 1536 byte frames */
#घोषणा MACB_BIG_SIZE		1
#घोषणा MACB_EAE_OFFSET		9 /* External address match enable */
#घोषणा MACB_EAE_SIZE		1
#घोषणा MACB_CLK_OFFSET		10
#घोषणा MACB_CLK_SIZE		2
#घोषणा MACB_RTY_OFFSET		12 /* Retry test */
#घोषणा MACB_RTY_SIZE		1
#घोषणा MACB_PAE_OFFSET		13 /* Pause enable */
#घोषणा MACB_PAE_SIZE		1
#घोषणा MACB_RM9200_RMII_OFFSET	13 /* AT91RM9200 only */
#घोषणा MACB_RM9200_RMII_SIZE	1  /* AT91RM9200 only */
#घोषणा MACB_RBOF_OFFSET	14 /* Receive buffer offset */
#घोषणा MACB_RBOF_SIZE		2
#घोषणा MACB_RLCE_OFFSET	16 /* Length field error frame discard */
#घोषणा MACB_RLCE_SIZE		1
#घोषणा MACB_DRFCS_OFFSET	17 /* FCS हटाओ */
#घोषणा MACB_DRFCS_SIZE		1
#घोषणा MACB_EFRHD_OFFSET	18
#घोषणा MACB_EFRHD_SIZE		1
#घोषणा MACB_IRXFCS_OFFSET	19
#घोषणा MACB_IRXFCS_SIZE	1

/* GEM specअगरic NCR bitfields. */
#घोषणा GEM_ENABLE_HS_MAC_OFFSET	31
#घोषणा GEM_ENABLE_HS_MAC_SIZE		1

/* GEM specअगरic NCFGR bitfields. */
#घोषणा GEM_FD_OFFSET		1 /* Full duplex */
#घोषणा GEM_FD_SIZE		1
#घोषणा GEM_GBE_OFFSET		10 /* Gigabit mode enable */
#घोषणा GEM_GBE_SIZE		1
#घोषणा GEM_PCSSEL_OFFSET	11
#घोषणा GEM_PCSSEL_SIZE		1
#घोषणा GEM_PAE_OFFSET		13 /* Pause enable */
#घोषणा GEM_PAE_SIZE		1
#घोषणा GEM_CLK_OFFSET		18 /* MDC घड़ी भागision */
#घोषणा GEM_CLK_SIZE		3
#घोषणा GEM_DBW_OFFSET		21 /* Data bus width */
#घोषणा GEM_DBW_SIZE		2
#घोषणा GEM_RXCOEN_OFFSET	24
#घोषणा GEM_RXCOEN_SIZE		1
#घोषणा GEM_SGMIIEN_OFFSET	27
#घोषणा GEM_SGMIIEN_SIZE	1


/* Constants क्रम data bus width. */
#घोषणा GEM_DBW32		0 /* 32 bit AMBA AHB data bus width */
#घोषणा GEM_DBW64		1 /* 64 bit AMBA AHB data bus width */
#घोषणा GEM_DBW128		2 /* 128 bit AMBA AHB data bus width */

/* Bitfields in DMACFG. */
#घोषणा GEM_FBLDO_OFFSET	0 /* fixed burst length क्रम DMA */
#घोषणा GEM_FBLDO_SIZE		5
#घोषणा GEM_ENDIA_DESC_OFFSET	6 /* endian swap mode क्रम management descriptor access */
#घोषणा GEM_ENDIA_DESC_SIZE	1
#घोषणा GEM_ENDIA_PKT_OFFSET	7 /* endian swap mode क्रम packet data access */
#घोषणा GEM_ENDIA_PKT_SIZE	1
#घोषणा GEM_RXBMS_OFFSET	8 /* RX packet buffer memory size select */
#घोषणा GEM_RXBMS_SIZE		2
#घोषणा GEM_TXPBMS_OFFSET	10 /* TX packet buffer memory size select */
#घोषणा GEM_TXPBMS_SIZE		1
#घोषणा GEM_TXCOEN_OFFSET	11 /* TX IP/TCP/UDP checksum gen offload */
#घोषणा GEM_TXCOEN_SIZE		1
#घोषणा GEM_RXBS_OFFSET		16 /* DMA receive buffer size */
#घोषणा GEM_RXBS_SIZE		8
#घोषणा GEM_DDRP_OFFSET		24 /* disc_when_no_ahb */
#घोषणा GEM_DDRP_SIZE		1
#घोषणा GEM_RXEXT_OFFSET	28 /* RX extended Buffer Descriptor mode */
#घोषणा GEM_RXEXT_SIZE		1
#घोषणा GEM_TXEXT_OFFSET	29 /* TX extended Buffer Descriptor mode */
#घोषणा GEM_TXEXT_SIZE		1
#घोषणा GEM_ADDR64_OFFSET	30 /* Address bus width - 64b or 32b */
#घोषणा GEM_ADDR64_SIZE		1


/* Bitfields in NSR */
#घोषणा MACB_NSR_LINK_OFFSET	0 /* pcs_link_state */
#घोषणा MACB_NSR_LINK_SIZE	1
#घोषणा MACB_MDIO_OFFSET	1 /* status of the mdio_in pin */
#घोषणा MACB_MDIO_SIZE		1
#घोषणा MACB_IDLE_OFFSET	2 /* The PHY management logic is idle */
#घोषणा MACB_IDLE_SIZE		1

/* Bitfields in TSR */
#घोषणा MACB_UBR_OFFSET		0 /* Used bit पढ़ो */
#घोषणा MACB_UBR_SIZE		1
#घोषणा MACB_COL_OFFSET		1 /* Collision occurred */
#घोषणा MACB_COL_SIZE		1
#घोषणा MACB_TSR_RLE_OFFSET	2 /* Retry limit exceeded */
#घोषणा MACB_TSR_RLE_SIZE	1
#घोषणा MACB_TGO_OFFSET		3 /* Transmit go */
#घोषणा MACB_TGO_SIZE		1
#घोषणा MACB_BEX_OFFSET		4 /* TX frame corruption due to AHB error */
#घोषणा MACB_BEX_SIZE		1
#घोषणा MACB_RM9200_BNQ_OFFSET	4 /* AT91RM9200 only */
#घोषणा MACB_RM9200_BNQ_SIZE	1 /* AT91RM9200 only */
#घोषणा MACB_COMP_OFFSET	5 /* Trnयंत्रit complete */
#घोषणा MACB_COMP_SIZE		1
#घोषणा MACB_UND_OFFSET		6 /* Trnयंत्रit under run */
#घोषणा MACB_UND_SIZE		1

/* Bitfields in RSR */
#घोषणा MACB_BNA_OFFSET		0 /* Buffer not available */
#घोषणा MACB_BNA_SIZE		1
#घोषणा MACB_REC_OFFSET		1 /* Frame received */
#घोषणा MACB_REC_SIZE		1
#घोषणा MACB_OVR_OFFSET		2 /* Receive overrun */
#घोषणा MACB_OVR_SIZE		1

/* Bitfields in ISR/IER/IDR/IMR */
#घोषणा MACB_MFD_OFFSET		0 /* Management frame sent */
#घोषणा MACB_MFD_SIZE		1
#घोषणा MACB_RCOMP_OFFSET	1 /* Receive complete */
#घोषणा MACB_RCOMP_SIZE		1
#घोषणा MACB_RXUBR_OFFSET	2 /* RX used bit पढ़ो */
#घोषणा MACB_RXUBR_SIZE		1
#घोषणा MACB_TXUBR_OFFSET	3 /* TX used bit पढ़ो */
#घोषणा MACB_TXUBR_SIZE		1
#घोषणा MACB_ISR_TUND_OFFSET	4 /* Enable TX buffer under run पूर्णांकerrupt */
#घोषणा MACB_ISR_TUND_SIZE	1
#घोषणा MACB_ISR_RLE_OFFSET	5 /* EN retry exceeded/late coll पूर्णांकerrupt */
#घोषणा MACB_ISR_RLE_SIZE	1
#घोषणा MACB_TXERR_OFFSET	6 /* EN TX frame corrupt from error पूर्णांकerrupt */
#घोषणा MACB_TXERR_SIZE		1
#घोषणा MACB_RM9200_TBRE_OFFSET	6 /* EN may send new frame पूर्णांकerrupt (RM9200) */
#घोषणा MACB_RM9200_TBRE_SIZE	1
#घोषणा MACB_TCOMP_OFFSET	7 /* Enable transmit complete पूर्णांकerrupt */
#घोषणा MACB_TCOMP_SIZE		1
#घोषणा MACB_ISR_LINK_OFFSET	9 /* Enable link change पूर्णांकerrupt */
#घोषणा MACB_ISR_LINK_SIZE	1
#घोषणा MACB_ISR_ROVR_OFFSET	10 /* Enable receive overrun पूर्णांकerrupt */
#घोषणा MACB_ISR_ROVR_SIZE	1
#घोषणा MACB_HRESP_OFFSET	11 /* Enable hrsep not OK पूर्णांकerrupt */
#घोषणा MACB_HRESP_SIZE		1
#घोषणा MACB_PFR_OFFSET		12 /* Enable छोड़ो frame w/ quantum पूर्णांकerrupt */
#घोषणा MACB_PFR_SIZE		1
#घोषणा MACB_PTZ_OFFSET		13 /* Enable छोड़ो समय zero पूर्णांकerrupt */
#घोषणा MACB_PTZ_SIZE		1
#घोषणा MACB_WOL_OFFSET		14 /* Enable wake-on-lan पूर्णांकerrupt */
#घोषणा MACB_WOL_SIZE		1
#घोषणा MACB_DRQFR_OFFSET	18 /* PTP Delay Request Frame Received */
#घोषणा MACB_DRQFR_SIZE		1
#घोषणा MACB_SFR_OFFSET		19 /* PTP Sync Frame Received */
#घोषणा MACB_SFR_SIZE		1
#घोषणा MACB_DRQFT_OFFSET	20 /* PTP Delay Request Frame Transmitted */
#घोषणा MACB_DRQFT_SIZE		1
#घोषणा MACB_SFT_OFFSET		21 /* PTP Sync Frame Transmitted */
#घोषणा MACB_SFT_SIZE		1
#घोषणा MACB_PDRQFR_OFFSET	22 /* PDelay Request Frame Received */
#घोषणा MACB_PDRQFR_SIZE	1
#घोषणा MACB_PDRSFR_OFFSET	23 /* PDelay Response Frame Received */
#घोषणा MACB_PDRSFR_SIZE	1
#घोषणा MACB_PDRQFT_OFFSET	24 /* PDelay Request Frame Transmitted */
#घोषणा MACB_PDRQFT_SIZE	1
#घोषणा MACB_PDRSFT_OFFSET	25 /* PDelay Response Frame Transmitted */
#घोषणा MACB_PDRSFT_SIZE	1
#घोषणा MACB_SRI_OFFSET		26 /* TSU Seconds Register Increment */
#घोषणा MACB_SRI_SIZE		1
#घोषणा GEM_WOL_OFFSET		28 /* Enable wake-on-lan पूर्णांकerrupt */
#घोषणा GEM_WOL_SIZE		1

/* Timer increment fields */
#घोषणा MACB_TI_CNS_OFFSET	0
#घोषणा MACB_TI_CNS_SIZE	8
#घोषणा MACB_TI_ACNS_OFFSET	8
#घोषणा MACB_TI_ACNS_SIZE	8
#घोषणा MACB_TI_NIT_OFFSET	16
#घोषणा MACB_TI_NIT_SIZE	8

/* Bitfields in MAN */
#घोषणा MACB_DATA_OFFSET	0 /* data */
#घोषणा MACB_DATA_SIZE		16
#घोषणा MACB_CODE_OFFSET	16 /* Must be written to 10 */
#घोषणा MACB_CODE_SIZE		2
#घोषणा MACB_REGA_OFFSET	18 /* Register address */
#घोषणा MACB_REGA_SIZE		5
#घोषणा MACB_PHYA_OFFSET	23 /* PHY address */
#घोषणा MACB_PHYA_SIZE		5
#घोषणा MACB_RW_OFFSET		28 /* Operation. 10 is पढ़ो. 01 is ग_लिखो. */
#घोषणा MACB_RW_SIZE		2
#घोषणा MACB_SOF_OFFSET		30 /* Must be written to 1 क्रम Clause 22 */
#घोषणा MACB_SOF_SIZE		2

/* Bitfields in USRIO (AVR32) */
#घोषणा MACB_MII_OFFSET				0
#घोषणा MACB_MII_SIZE				1
#घोषणा MACB_EAM_OFFSET				1
#घोषणा MACB_EAM_SIZE				1
#घोषणा MACB_TX_PAUSE_OFFSET			2
#घोषणा MACB_TX_PAUSE_SIZE			1
#घोषणा MACB_TX_PAUSE_ZERO_OFFSET		3
#घोषणा MACB_TX_PAUSE_ZERO_SIZE			1

/* Bitfields in USRIO (AT91) */
#घोषणा MACB_RMII_OFFSET			0
#घोषणा MACB_RMII_SIZE				1
#घोषणा GEM_RGMII_OFFSET			0 /* GEM gigabit mode */
#घोषणा GEM_RGMII_SIZE				1
#घोषणा MACB_CLKEN_OFFSET			1
#घोषणा MACB_CLKEN_SIZE				1

/* Bitfields in WOL */
#घोषणा MACB_IP_OFFSET				0
#घोषणा MACB_IP_SIZE				16
#घोषणा MACB_MAG_OFFSET				16
#घोषणा MACB_MAG_SIZE				1
#घोषणा MACB_ARP_OFFSET				17
#घोषणा MACB_ARP_SIZE				1
#घोषणा MACB_SA1_OFFSET				18
#घोषणा MACB_SA1_SIZE				1
#घोषणा MACB_WOL_MTI_OFFSET			19
#घोषणा MACB_WOL_MTI_SIZE			1

/* Bitfields in MID */
#घोषणा MACB_IDNUM_OFFSET			16
#घोषणा MACB_IDNUM_SIZE				12
#घोषणा MACB_REV_OFFSET				0
#घोषणा MACB_REV_SIZE				16

/* Bitfield in HS_MAC_CONFIG */
#घोषणा GEM_HS_MAC_SPEED_OFFSET			0
#घोषणा GEM_HS_MAC_SPEED_SIZE			3

/* Bitfields in PCSCNTRL */
#घोषणा GEM_PCSAUTONEG_OFFSET			12
#घोषणा GEM_PCSAUTONEG_SIZE			1

/* Bitfields in DCFG1. */
#घोषणा GEM_IRQCOR_OFFSET			23
#घोषणा GEM_IRQCOR_SIZE				1
#घोषणा GEM_DBWDEF_OFFSET			25
#घोषणा GEM_DBWDEF_SIZE				3
#घोषणा GEM_NO_PCS_OFFSET			0
#घोषणा GEM_NO_PCS_SIZE				1

/* Bitfields in DCFG2. */
#घोषणा GEM_RX_PKT_BUFF_OFFSET			20
#घोषणा GEM_RX_PKT_BUFF_SIZE			1
#घोषणा GEM_TX_PKT_BUFF_OFFSET			21
#घोषणा GEM_TX_PKT_BUFF_SIZE			1


/* Bitfields in DCFG5. */
#घोषणा GEM_TSU_OFFSET				8
#घोषणा GEM_TSU_SIZE				1

/* Bitfields in DCFG6. */
#घोषणा GEM_PBUF_LSO_OFFSET			27
#घोषणा GEM_PBUF_LSO_SIZE			1
#घोषणा GEM_DAW64_OFFSET			23
#घोषणा GEM_DAW64_SIZE				1

/* Bitfields in DCFG8. */
#घोषणा GEM_T1SCR_OFFSET			24
#घोषणा GEM_T1SCR_SIZE				8
#घोषणा GEM_T2SCR_OFFSET			16
#घोषणा GEM_T2SCR_SIZE				8
#घोषणा GEM_SCR2ETH_OFFSET			8
#घोषणा GEM_SCR2ETH_SIZE			8
#घोषणा GEM_SCR2CMP_OFFSET			0
#घोषणा GEM_SCR2CMP_SIZE			8

/* Bitfields in DCFG10 */
#घोषणा GEM_TXBD_RDBUFF_OFFSET			12
#घोषणा GEM_TXBD_RDBUFF_SIZE			4
#घोषणा GEM_RXBD_RDBUFF_OFFSET			8
#घोषणा GEM_RXBD_RDBUFF_SIZE			4

/* Bitfields in DCFG12. */
#घोषणा GEM_HIGH_SPEED_OFFSET			26
#घोषणा GEM_HIGH_SPEED_SIZE			1

/* Bitfields in USX_CONTROL. */
#घोषणा GEM_USX_CTRL_SPEED_OFFSET		14
#घोषणा GEM_USX_CTRL_SPEED_SIZE			3
#घोषणा GEM_SERDES_RATE_OFFSET			12
#घोषणा GEM_SERDES_RATE_SIZE			2
#घोषणा GEM_RX_SCR_BYPASS_OFFSET		9
#घोषणा GEM_RX_SCR_BYPASS_SIZE			1
#घोषणा GEM_TX_SCR_BYPASS_OFFSET		8
#घोषणा GEM_TX_SCR_BYPASS_SIZE			1
#घोषणा GEM_TX_EN_OFFSET			1
#घोषणा GEM_TX_EN_SIZE				1
#घोषणा GEM_SIGNAL_OK_OFFSET			0
#घोषणा GEM_SIGNAL_OK_SIZE			1

/* Bitfields in USX_STATUS. */
#घोषणा GEM_USX_BLOCK_LOCK_OFFSET		0
#घोषणा GEM_USX_BLOCK_LOCK_SIZE			1

/* Bitfields in TISUBN */
#घोषणा GEM_SUBNSINCR_OFFSET			0
#घोषणा GEM_SUBNSINCRL_OFFSET			24
#घोषणा GEM_SUBNSINCRL_SIZE			8
#घोषणा GEM_SUBNSINCRH_OFFSET			0
#घोषणा GEM_SUBNSINCRH_SIZE			16
#घोषणा GEM_SUBNSINCR_SIZE			24

/* Bitfields in TI */
#घोषणा GEM_NSINCR_OFFSET			0
#घोषणा GEM_NSINCR_SIZE				8

/* Bitfields in TSH */
#घोषणा GEM_TSH_OFFSET				0 /* TSU समयr value (s). MSB [47:32] of seconds समयr count */
#घोषणा GEM_TSH_SIZE				16

/* Bitfields in TSL */
#घोषणा GEM_TSL_OFFSET				0 /* TSU समयr value (s). LSB [31:0] of seconds समयr count */
#घोषणा GEM_TSL_SIZE				32

/* Bitfields in TN */
#घोषणा GEM_TN_OFFSET				0 /* TSU समयr value (ns) */
#घोषणा GEM_TN_SIZE					30

/* Bitfields in TXBDCTRL */
#घोषणा GEM_TXTSMODE_OFFSET			4 /* TX Descriptor Timestamp Insertion mode */
#घोषणा GEM_TXTSMODE_SIZE			2

/* Bitfields in RXBDCTRL */
#घोषणा GEM_RXTSMODE_OFFSET			4 /* RX Descriptor Timestamp Insertion mode */
#घोषणा GEM_RXTSMODE_SIZE			2

/* Bitfields in SCRT2 */
#घोषणा GEM_QUEUE_OFFSET			0 /* Queue Number */
#घोषणा GEM_QUEUE_SIZE				4
#घोषणा GEM_VLANPR_OFFSET			4 /* VLAN Priority */
#घोषणा GEM_VLANPR_SIZE				3
#घोषणा GEM_VLANEN_OFFSET			8 /* VLAN Enable */
#घोषणा GEM_VLANEN_SIZE				1
#घोषणा GEM_ETHT2IDX_OFFSET			9 /* Index to screener type 2 EtherType रेजिस्टर */
#घोषणा GEM_ETHT2IDX_SIZE			3
#घोषणा GEM_ETHTEN_OFFSET			12 /* EtherType Enable */
#घोषणा GEM_ETHTEN_SIZE				1
#घोषणा GEM_CMPA_OFFSET				13 /* Compare A - Index to screener type 2 Compare रेजिस्टर */
#घोषणा GEM_CMPA_SIZE				5
#घोषणा GEM_CMPAEN_OFFSET			18 /* Compare A Enable */
#घोषणा GEM_CMPAEN_SIZE				1
#घोषणा GEM_CMPB_OFFSET				19 /* Compare B - Index to screener type 2 Compare रेजिस्टर */
#घोषणा GEM_CMPB_SIZE				5
#घोषणा GEM_CMPBEN_OFFSET			24 /* Compare B Enable */
#घोषणा GEM_CMPBEN_SIZE				1
#घोषणा GEM_CMPC_OFFSET				25 /* Compare C - Index to screener type 2 Compare रेजिस्टर */
#घोषणा GEM_CMPC_SIZE				5
#घोषणा GEM_CMPCEN_OFFSET			30 /* Compare C Enable */
#घोषणा GEM_CMPCEN_SIZE				1

/* Bitfields in ETHT */
#घोषणा GEM_ETHTCMP_OFFSET			0 /* EtherType compare value */
#घोषणा GEM_ETHTCMP_SIZE			16

/* Bitfields in T2CMPW0 */
#घोषणा GEM_T2CMP_OFFSET			16 /* 0xFFFF0000 compare value */
#घोषणा GEM_T2CMP_SIZE				16
#घोषणा GEM_T2MASK_OFFSET			0 /* 0x0000FFFF compare value or mask */
#घोषणा GEM_T2MASK_SIZE				16

/* Bitfields in T2CMPW1 */
#घोषणा GEM_T2DISMSK_OFFSET			9 /* disable mask */
#घोषणा GEM_T2DISMSK_SIZE			1
#घोषणा GEM_T2CMPOFST_OFFSET			7 /* compare offset */
#घोषणा GEM_T2CMPOFST_SIZE			2
#घोषणा GEM_T2OFST_OFFSET			0 /* offset value */
#घोषणा GEM_T2OFST_SIZE				7

/* Offset क्रम screener type 2 compare values (T2CMPOFST).
 * Note the offset is applied after the specअगरied poपूर्णांक,
 * e.g. GEM_T2COMPOFST_ETYPE denotes the EtherType field, so an offset
 * of 12 bytes from this would be the source IP address in an IP header
 */
#घोषणा GEM_T2COMPOFST_SOF		0
#घोषणा GEM_T2COMPOFST_ETYPE	1
#घोषणा GEM_T2COMPOFST_IPHDR	2
#घोषणा GEM_T2COMPOFST_TCPUDP	3

/* offset from EtherType to IP address */
#घोषणा ETYPE_SRCIP_OFFSET			12
#घोषणा ETYPE_DSTIP_OFFSET			16

/* offset from IP header to port */
#घोषणा IPHDR_SRCPORT_OFFSET		0
#घोषणा IPHDR_DSTPORT_OFFSET		2

/* Transmit DMA buffer descriptor Word 1 */
#घोषणा GEM_DMA_TXVALID_OFFSET		23 /* बारtamp has been captured in the Buffer Descriptor */
#घोषणा GEM_DMA_TXVALID_SIZE		1

/* Receive DMA buffer descriptor Word 0 */
#घोषणा GEM_DMA_RXVALID_OFFSET		2 /* indicates a valid बारtamp in the Buffer Descriptor */
#घोषणा GEM_DMA_RXVALID_SIZE		1

/* DMA buffer descriptor Word 2 (32 bit addressing) or Word 4 (64 bit addressing) */
#घोषणा GEM_DMA_SECL_OFFSET			30 /* Timestamp seconds[1:0]  */
#घोषणा GEM_DMA_SECL_SIZE			2
#घोषणा GEM_DMA_NSEC_OFFSET			0 /* Timestamp nanosecs [29:0] */
#घोषणा GEM_DMA_NSEC_SIZE			30

/* DMA buffer descriptor Word 3 (32 bit addressing) or Word 5 (64 bit addressing) */

/* New hardware supports 12 bit precision of बारtamp in DMA buffer descriptor.
 * Old hardware supports only 6 bit precision but it is enough क्रम PTP.
 * Less accuracy is used always instead of checking hardware version.
 */
#घोषणा GEM_DMA_SECH_OFFSET			0 /* Timestamp seconds[5:2] */
#घोषणा GEM_DMA_SECH_SIZE			4
#घोषणा GEM_DMA_SEC_WIDTH			(GEM_DMA_SECH_SIZE + GEM_DMA_SECL_SIZE)
#घोषणा GEM_DMA_SEC_TOP				(1 << GEM_DMA_SEC_WIDTH)
#घोषणा GEM_DMA_SEC_MASK			(GEM_DMA_SEC_TOP - 1)

/* Bitfields in ADJ */
#घोषणा GEM_ADDSUB_OFFSET			31
#घोषणा GEM_ADDSUB_SIZE				1
/* Constants क्रम CLK */
#घोषणा MACB_CLK_DIV8				0
#घोषणा MACB_CLK_DIV16				1
#घोषणा MACB_CLK_DIV32				2
#घोषणा MACB_CLK_DIV64				3

/* GEM specअगरic स्थिरants क्रम CLK. */
#घोषणा GEM_CLK_DIV8				0
#घोषणा GEM_CLK_DIV16				1
#घोषणा GEM_CLK_DIV32				2
#घोषणा GEM_CLK_DIV48				3
#घोषणा GEM_CLK_DIV64				4
#घोषणा GEM_CLK_DIV96				5

/* Constants क्रम MAN रेजिस्टर */
#घोषणा MACB_MAN_C22_SOF			1
#घोषणा MACB_MAN_C22_WRITE			1
#घोषणा MACB_MAN_C22_READ			2
#घोषणा MACB_MAN_C22_CODE			2

#घोषणा MACB_MAN_C45_SOF			0
#घोषणा MACB_MAN_C45_ADDR			0
#घोषणा MACB_MAN_C45_WRITE			1
#घोषणा MACB_MAN_C45_POST_READ_INCR		2
#घोषणा MACB_MAN_C45_READ			3
#घोषणा MACB_MAN_C45_CODE			2

/* Capability mask bits */
#घोषणा MACB_CAPS_ISR_CLEAR_ON_WRITE		0x00000001
#घोषणा MACB_CAPS_USRIO_HAS_CLKEN		0x00000002
#घोषणा MACB_CAPS_USRIO_DEFAULT_IS_MII_GMII	0x00000004
#घोषणा MACB_CAPS_NO_GIGABIT_HALF		0x00000008
#घोषणा MACB_CAPS_USRIO_DISABLED		0x00000010
#घोषणा MACB_CAPS_JUMBO				0x00000020
#घोषणा MACB_CAPS_GEM_HAS_PTP			0x00000040
#घोषणा MACB_CAPS_BD_RD_PREFETCH		0x00000080
#घोषणा MACB_CAPS_NEEDS_RSTONUBR		0x00000100
#घोषणा MACB_CAPS_CLK_HW_CHG			0x04000000
#घोषणा MACB_CAPS_MACB_IS_EMAC			0x08000000
#घोषणा MACB_CAPS_FIFO_MODE			0x10000000
#घोषणा MACB_CAPS_GIGABIT_MODE_AVAILABLE	0x20000000
#घोषणा MACB_CAPS_SG_DISABLED			0x40000000
#घोषणा MACB_CAPS_MACB_IS_GEM			0x80000000
#घोषणा MACB_CAPS_PCS				0x01000000
#घोषणा MACB_CAPS_HIGH_SPEED			0x02000000

/* LSO settings */
#घोषणा MACB_LSO_UFO_ENABLE			0x01
#घोषणा MACB_LSO_TSO_ENABLE			0x02

/* Bit manipulation macros */
#घोषणा MACB_BIT(name)					\
	(1 << MACB_##name##_OFFSET)
#घोषणा MACB_BF(name,value)				\
	(((value) & ((1 << MACB_##name##_SIZE) - 1))	\
	 << MACB_##name##_OFFSET)
#घोषणा MACB_BFEXT(name,value)\
	(((value) >> MACB_##name##_OFFSET)		\
	 & ((1 << MACB_##name##_SIZE) - 1))
#घोषणा MACB_BFINS(name,value,old)			\
	(((old) & ~(((1 << MACB_##name##_SIZE) - 1)	\
		    << MACB_##name##_OFFSET))		\
	 | MACB_BF(name,value))

#घोषणा GEM_BIT(name)					\
	(1 << GEM_##name##_OFFSET)
#घोषणा GEM_BF(name, value)				\
	(((value) & ((1 << GEM_##name##_SIZE) - 1))	\
	 << GEM_##name##_OFFSET)
#घोषणा GEM_BFEXT(name, value)\
	(((value) >> GEM_##name##_OFFSET)		\
	 & ((1 << GEM_##name##_SIZE) - 1))
#घोषणा GEM_BFINS(name, value, old)			\
	(((old) & ~(((1 << GEM_##name##_SIZE) - 1)	\
		    << GEM_##name##_OFFSET))		\
	 | GEM_BF(name, value))

/* Register access macros */
#घोषणा macb_पढ़ोl(port, reg)		(port)->macb_reg_पढ़ोl((port), MACB_##reg)
#घोषणा macb_ग_लिखोl(port, reg, value)	(port)->macb_reg_ग_लिखोl((port), MACB_##reg, (value))
#घोषणा gem_पढ़ोl(port, reg)		(port)->macb_reg_पढ़ोl((port), GEM_##reg)
#घोषणा gem_ग_लिखोl(port, reg, value)	(port)->macb_reg_ग_लिखोl((port), GEM_##reg, (value))
#घोषणा queue_पढ़ोl(queue, reg)		(queue)->bp->macb_reg_पढ़ोl((queue)->bp, (queue)->reg)
#घोषणा queue_ग_लिखोl(queue, reg, value)	(queue)->bp->macb_reg_ग_लिखोl((queue)->bp, (queue)->reg, (value))
#घोषणा gem_पढ़ोl_n(port, reg, idx)		(port)->macb_reg_पढ़ोl((port), GEM_##reg + idx * 4)
#घोषणा gem_ग_लिखोl_n(port, reg, idx, value)	(port)->macb_reg_ग_लिखोl((port), GEM_##reg + idx * 4, (value))

#घोषणा PTP_TS_BUFFER_SIZE		128 /* must be घातer of 2 */

/* Conditional GEM/MACB macros.  These perक्रमm the operation to the correct
 * रेजिस्टर dependent on whether the device is a GEM or a MACB.  For रेजिस्टरs
 * and bitfields that are common across both devices, use macb_अणुपढ़ो,ग_लिखोपूर्णl
 * to aव्योम the cost of the conditional.
 */
#घोषणा macb_or_gem_ग_लिखोl(__bp, __reg, __value) \
	(अणु \
		अगर (macb_is_gem((__bp))) \
			gem_ग_लिखोl((__bp), __reg, __value); \
		अन्यथा \
			macb_ग_लिखोl((__bp), __reg, __value); \
	पूर्ण)

#घोषणा macb_or_gem_पढ़ोl(__bp, __reg) \
	(अणु \
		u32 __v; \
		अगर (macb_is_gem((__bp))) \
			__v = gem_पढ़ोl((__bp), __reg); \
		अन्यथा \
			__v = macb_पढ़ोl((__bp), __reg); \
		__v; \
	पूर्ण)

#घोषणा MACB_READ_NSR(bp)	macb_पढ़ोl(bp, NSR)

/* काष्ठा macb_dma_desc - Hardware DMA descriptor
 * @addr: DMA address of data buffer
 * @ctrl: Control and status bits
 */
काष्ठा macb_dma_desc अणु
	u32	addr;
	u32	ctrl;
पूर्ण;

#अगर_घोषित MACB_EXT_DESC
#घोषणा HW_DMA_CAP_32B		0
#घोषणा HW_DMA_CAP_64B		(1 << 0)
#घोषणा HW_DMA_CAP_PTP		(1 << 1)
#घोषणा HW_DMA_CAP_64B_PTP	(HW_DMA_CAP_64B | HW_DMA_CAP_PTP)

काष्ठा macb_dma_desc_64 अणु
	u32 addrh;
	u32 resvd;
पूर्ण;

काष्ठा macb_dma_desc_ptp अणु
	u32	ts_1;
	u32	ts_2;
पूर्ण;

काष्ठा gem_tx_ts अणु
	काष्ठा sk_buff *skb;
	काष्ठा macb_dma_desc_ptp desc_ptp;
पूर्ण;
#पूर्ण_अगर

/* DMA descriptor bitfields */
#घोषणा MACB_RX_USED_OFFSET			0
#घोषणा MACB_RX_USED_SIZE			1
#घोषणा MACB_RX_WRAP_OFFSET			1
#घोषणा MACB_RX_WRAP_SIZE			1
#घोषणा MACB_RX_WADDR_OFFSET			2
#घोषणा MACB_RX_WADDR_SIZE			30

#घोषणा MACB_RX_FRMLEN_OFFSET			0
#घोषणा MACB_RX_FRMLEN_SIZE			12
#घोषणा MACB_RX_OFFSET_OFFSET			12
#घोषणा MACB_RX_OFFSET_SIZE			2
#घोषणा MACB_RX_SOF_OFFSET			14
#घोषणा MACB_RX_SOF_SIZE			1
#घोषणा MACB_RX_खातापूर्ण_OFFSET			15
#घोषणा MACB_RX_खातापूर्ण_SIZE			1
#घोषणा MACB_RX_CFI_OFFSET			16
#घोषणा MACB_RX_CFI_SIZE			1
#घोषणा MACB_RX_VLAN_PRI_OFFSET			17
#घोषणा MACB_RX_VLAN_PRI_SIZE			3
#घोषणा MACB_RX_PRI_TAG_OFFSET			20
#घोषणा MACB_RX_PRI_TAG_SIZE			1
#घोषणा MACB_RX_VLAN_TAG_OFFSET			21
#घोषणा MACB_RX_VLAN_TAG_SIZE			1
#घोषणा MACB_RX_TYPEID_MATCH_OFFSET		22
#घोषणा MACB_RX_TYPEID_MATCH_SIZE		1
#घोषणा MACB_RX_SA4_MATCH_OFFSET		23
#घोषणा MACB_RX_SA4_MATCH_SIZE			1
#घोषणा MACB_RX_SA3_MATCH_OFFSET		24
#घोषणा MACB_RX_SA3_MATCH_SIZE			1
#घोषणा MACB_RX_SA2_MATCH_OFFSET		25
#घोषणा MACB_RX_SA2_MATCH_SIZE			1
#घोषणा MACB_RX_SA1_MATCH_OFFSET		26
#घोषणा MACB_RX_SA1_MATCH_SIZE			1
#घोषणा MACB_RX_EXT_MATCH_OFFSET		28
#घोषणा MACB_RX_EXT_MATCH_SIZE			1
#घोषणा MACB_RX_UHASH_MATCH_OFFSET		29
#घोषणा MACB_RX_UHASH_MATCH_SIZE		1
#घोषणा MACB_RX_MHASH_MATCH_OFFSET		30
#घोषणा MACB_RX_MHASH_MATCH_SIZE		1
#घोषणा MACB_RX_BROADCAST_OFFSET		31
#घोषणा MACB_RX_BROADCAST_SIZE			1

#घोषणा MACB_RX_FRMLEN_MASK			0xFFF
#घोषणा MACB_RX_JFRMLEN_MASK			0x3FFF

/* RX checksum offload disabled: bit 24 clear in NCFGR */
#घोषणा GEM_RX_TYPEID_MATCH_OFFSET		22
#घोषणा GEM_RX_TYPEID_MATCH_SIZE		2

/* RX checksum offload enabled: bit 24 set in NCFGR */
#घोषणा GEM_RX_CSUM_OFFSET			22
#घोषणा GEM_RX_CSUM_SIZE			2

#घोषणा MACB_TX_FRMLEN_OFFSET			0
#घोषणा MACB_TX_FRMLEN_SIZE			11
#घोषणा MACB_TX_LAST_OFFSET			15
#घोषणा MACB_TX_LAST_SIZE			1
#घोषणा MACB_TX_NOCRC_OFFSET			16
#घोषणा MACB_TX_NOCRC_SIZE			1
#घोषणा MACB_MSS_MFS_OFFSET			16
#घोषणा MACB_MSS_MFS_SIZE			14
#घोषणा MACB_TX_LSO_OFFSET			17
#घोषणा MACB_TX_LSO_SIZE			2
#घोषणा MACB_TX_TCP_SEQ_SRC_OFFSET		19
#घोषणा MACB_TX_TCP_SEQ_SRC_SIZE		1
#घोषणा MACB_TX_BUF_EXHAUSTED_OFFSET		27
#घोषणा MACB_TX_BUF_EXHAUSTED_SIZE		1
#घोषणा MACB_TX_UNDERRUN_OFFSET			28
#घोषणा MACB_TX_UNDERRUN_SIZE			1
#घोषणा MACB_TX_ERROR_OFFSET			29
#घोषणा MACB_TX_ERROR_SIZE			1
#घोषणा MACB_TX_WRAP_OFFSET			30
#घोषणा MACB_TX_WRAP_SIZE			1
#घोषणा MACB_TX_USED_OFFSET			31
#घोषणा MACB_TX_USED_SIZE			1

#घोषणा GEM_TX_FRMLEN_OFFSET			0
#घोषणा GEM_TX_FRMLEN_SIZE			14

/* Buffer descriptor स्थिरants */
#घोषणा GEM_RX_CSUM_NONE			0
#घोषणा GEM_RX_CSUM_IP_ONLY			1
#घोषणा GEM_RX_CSUM_IP_TCP			2
#घोषणा GEM_RX_CSUM_IP_UDP			3

/* limit RX checksum offload to TCP and UDP packets */
#घोषणा GEM_RX_CSUM_CHECKED_MASK		2

/* Scaled PPM fraction */
#घोषणा PPM_FRACTION	16

/* काष्ठा macb_tx_skb - data about an skb which is being transmitted
 * @skb: skb currently being transmitted, only set क्रम the last buffer
 *       of the frame
 * @mapping: DMA address of the skb's fragment buffer
 * @size: size of the DMA mapped buffer
 * @mapped_as_page: true when buffer was mapped with skb_frag_dma_map(),
 *                  false when buffer was mapped with dma_map_single()
 */
काष्ठा macb_tx_skb अणु
	काष्ठा sk_buff		*skb;
	dma_addr_t		mapping;
	माप_प्रकार			size;
	bool			mapped_as_page;
पूर्ण;

/* Hardware-collected statistics. Used when updating the network
 * device stats by a periodic समयr.
 */
काष्ठा macb_stats अणु
	u32	rx_छोड़ो_frames;
	u32	tx_ok;
	u32	tx_single_cols;
	u32	tx_multiple_cols;
	u32	rx_ok;
	u32	rx_fcs_errors;
	u32	rx_align_errors;
	u32	tx_deferred;
	u32	tx_late_cols;
	u32	tx_excessive_cols;
	u32	tx_underruns;
	u32	tx_carrier_errors;
	u32	rx_resource_errors;
	u32	rx_overruns;
	u32	rx_symbol_errors;
	u32	rx_oversize_pkts;
	u32	rx_jabbers;
	u32	rx_undersize_pkts;
	u32	sqe_test_errors;
	u32	rx_length_mismatch;
	u32	tx_छोड़ो_frames;
पूर्ण;

काष्ठा gem_stats अणु
	u32	tx_octets_31_0;
	u32	tx_octets_47_32;
	u32	tx_frames;
	u32	tx_broadcast_frames;
	u32	tx_multicast_frames;
	u32	tx_छोड़ो_frames;
	u32	tx_64_byte_frames;
	u32	tx_65_127_byte_frames;
	u32	tx_128_255_byte_frames;
	u32	tx_256_511_byte_frames;
	u32	tx_512_1023_byte_frames;
	u32	tx_1024_1518_byte_frames;
	u32	tx_greater_than_1518_byte_frames;
	u32	tx_underrun;
	u32	tx_single_collision_frames;
	u32	tx_multiple_collision_frames;
	u32	tx_excessive_collisions;
	u32	tx_late_collisions;
	u32	tx_deferred_frames;
	u32	tx_carrier_sense_errors;
	u32	rx_octets_31_0;
	u32	rx_octets_47_32;
	u32	rx_frames;
	u32	rx_broadcast_frames;
	u32	rx_multicast_frames;
	u32	rx_छोड़ो_frames;
	u32	rx_64_byte_frames;
	u32	rx_65_127_byte_frames;
	u32	rx_128_255_byte_frames;
	u32	rx_256_511_byte_frames;
	u32	rx_512_1023_byte_frames;
	u32	rx_1024_1518_byte_frames;
	u32	rx_greater_than_1518_byte_frames;
	u32	rx_undersized_frames;
	u32	rx_oversize_frames;
	u32	rx_jabbers;
	u32	rx_frame_check_sequence_errors;
	u32	rx_length_field_frame_errors;
	u32	rx_symbol_errors;
	u32	rx_alignment_errors;
	u32	rx_resource_errors;
	u32	rx_overruns;
	u32	rx_ip_header_checksum_errors;
	u32	rx_tcp_checksum_errors;
	u32	rx_udp_checksum_errors;
पूर्ण;

/* Describes the name and offset of an inभागidual statistic रेजिस्टर, as
 * वापसed by `ethtool -S`. Also describes which net_device_stats statistics
 * this रेजिस्टर should contribute to.
 */
काष्ठा gem_statistic अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक offset;
	u32 stat_bits;
पूर्ण;

/* Bitfield defs क्रम net_device_stat statistics */
#घोषणा GEM_NDS_RXERR_OFFSET		0
#घोषणा GEM_NDS_RXLENERR_OFFSET		1
#घोषणा GEM_NDS_RXOVERERR_OFFSET	2
#घोषणा GEM_NDS_RXCRCERR_OFFSET		3
#घोषणा GEM_NDS_RXFRAMEERR_OFFSET	4
#घोषणा GEM_NDS_RXFIFOERR_OFFSET	5
#घोषणा GEM_NDS_TXERR_OFFSET		6
#घोषणा GEM_NDS_TXABORTEDERR_OFFSET	7
#घोषणा GEM_NDS_TXCARRIERERR_OFFSET	8
#घोषणा GEM_NDS_TXFIFOERR_OFFSET	9
#घोषणा GEM_NDS_COLLISIONS_OFFSET	10

#घोषणा GEM_STAT_TITLE(name, title) GEM_STAT_TITLE_BITS(name, title, 0)
#घोषणा GEM_STAT_TITLE_BITS(name, title, bits) अणु	\
	.stat_string = title,				\
	.offset = GEM_##name,				\
	.stat_bits = bits				\
पूर्ण

/* list of gem statistic रेजिस्टरs. The names MUST match the
 * corresponding GEM_* definitions.
 */
अटल स्थिर काष्ठा gem_statistic gem_statistics[] = अणु
	GEM_STAT_TITLE(OCTTXL, "tx_octets"), /* OCTTXH combined with OCTTXL */
	GEM_STAT_TITLE(TXCNT, "tx_frames"),
	GEM_STAT_TITLE(TXBCCNT, "tx_broadcast_frames"),
	GEM_STAT_TITLE(TXMCCNT, "tx_multicast_frames"),
	GEM_STAT_TITLE(TXPAUSECNT, "tx_pause_frames"),
	GEM_STAT_TITLE(TX64CNT, "tx_64_byte_frames"),
	GEM_STAT_TITLE(TX65CNT, "tx_65_127_byte_frames"),
	GEM_STAT_TITLE(TX128CNT, "tx_128_255_byte_frames"),
	GEM_STAT_TITLE(TX256CNT, "tx_256_511_byte_frames"),
	GEM_STAT_TITLE(TX512CNT, "tx_512_1023_byte_frames"),
	GEM_STAT_TITLE(TX1024CNT, "tx_1024_1518_byte_frames"),
	GEM_STAT_TITLE(TX1519CNT, "tx_greater_than_1518_byte_frames"),
	GEM_STAT_TITLE_BITS(TXURUNCNT, "tx_underrun",
			    GEM_BIT(NDS_TXERR)|GEM_BIT(NDS_TXFIFOERR)),
	GEM_STAT_TITLE_BITS(SNGLCOLLCNT, "tx_single_collision_frames",
			    GEM_BIT(NDS_TXERR)|GEM_BIT(NDS_COLLISIONS)),
	GEM_STAT_TITLE_BITS(MULTICOLLCNT, "tx_multiple_collision_frames",
			    GEM_BIT(NDS_TXERR)|GEM_BIT(NDS_COLLISIONS)),
	GEM_STAT_TITLE_BITS(EXCESSCOLLCNT, "tx_excessive_collisions",
			    GEM_BIT(NDS_TXERR)|
			    GEM_BIT(NDS_TXABORTEDERR)|
			    GEM_BIT(NDS_COLLISIONS)),
	GEM_STAT_TITLE_BITS(LATECOLLCNT, "tx_late_collisions",
			    GEM_BIT(NDS_TXERR)|GEM_BIT(NDS_COLLISIONS)),
	GEM_STAT_TITLE(TXDEFERCNT, "tx_deferred_frames"),
	GEM_STAT_TITLE_BITS(TXCSENSECNT, "tx_carrier_sense_errors",
			    GEM_BIT(NDS_TXERR)|GEM_BIT(NDS_COLLISIONS)),
	GEM_STAT_TITLE(OCTRXL, "rx_octets"), /* OCTRXH combined with OCTRXL */
	GEM_STAT_TITLE(RXCNT, "rx_frames"),
	GEM_STAT_TITLE(RXBROADCNT, "rx_broadcast_frames"),
	GEM_STAT_TITLE(RXMULTICNT, "rx_multicast_frames"),
	GEM_STAT_TITLE(RXPAUSECNT, "rx_pause_frames"),
	GEM_STAT_TITLE(RX64CNT, "rx_64_byte_frames"),
	GEM_STAT_TITLE(RX65CNT, "rx_65_127_byte_frames"),
	GEM_STAT_TITLE(RX128CNT, "rx_128_255_byte_frames"),
	GEM_STAT_TITLE(RX256CNT, "rx_256_511_byte_frames"),
	GEM_STAT_TITLE(RX512CNT, "rx_512_1023_byte_frames"),
	GEM_STAT_TITLE(RX1024CNT, "rx_1024_1518_byte_frames"),
	GEM_STAT_TITLE(RX1519CNT, "rx_greater_than_1518_byte_frames"),
	GEM_STAT_TITLE_BITS(RXUNDRCNT, "rx_undersized_frames",
			    GEM_BIT(NDS_RXERR)|GEM_BIT(NDS_RXLENERR)),
	GEM_STAT_TITLE_BITS(RXOVRCNT, "rx_oversize_frames",
			    GEM_BIT(NDS_RXERR)|GEM_BIT(NDS_RXLENERR)),
	GEM_STAT_TITLE_BITS(RXJABCNT, "rx_jabbers",
			    GEM_BIT(NDS_RXERR)|GEM_BIT(NDS_RXLENERR)),
	GEM_STAT_TITLE_BITS(RXFCSCNT, "rx_frame_check_sequence_errors",
			    GEM_BIT(NDS_RXERR)|GEM_BIT(NDS_RXCRCERR)),
	GEM_STAT_TITLE_BITS(RXLENGTHCNT, "rx_length_field_frame_errors",
			    GEM_BIT(NDS_RXERR)),
	GEM_STAT_TITLE_BITS(RXSYMBCNT, "rx_symbol_errors",
			    GEM_BIT(NDS_RXERR)|GEM_BIT(NDS_RXFRAMEERR)),
	GEM_STAT_TITLE_BITS(RXALIGNCNT, "rx_alignment_errors",
			    GEM_BIT(NDS_RXERR)|GEM_BIT(NDS_RXOVERERR)),
	GEM_STAT_TITLE_BITS(RXRESERRCNT, "rx_resource_errors",
			    GEM_BIT(NDS_RXERR)|GEM_BIT(NDS_RXOVERERR)),
	GEM_STAT_TITLE_BITS(RXORCNT, "rx_overruns",
			    GEM_BIT(NDS_RXERR)|GEM_BIT(NDS_RXFIFOERR)),
	GEM_STAT_TITLE_BITS(RXIPCCNT, "rx_ip_header_checksum_errors",
			    GEM_BIT(NDS_RXERR)),
	GEM_STAT_TITLE_BITS(RXTCPCCNT, "rx_tcp_checksum_errors",
			    GEM_BIT(NDS_RXERR)),
	GEM_STAT_TITLE_BITS(RXUDPCCNT, "rx_udp_checksum_errors",
			    GEM_BIT(NDS_RXERR)),
पूर्ण;

#घोषणा GEM_STATS_LEN ARRAY_SIZE(gem_statistics)

#घोषणा QUEUE_STAT_TITLE(title) अणु	\
	.stat_string = title,			\
पूर्ण

/* per queue statistics, each should be अचिन्हित दीर्घ type */
काष्ठा queue_stats अणु
	जोड़ अणु
		अचिन्हित दीर्घ first;
		अचिन्हित दीर्घ rx_packets;
	पूर्ण;
	अचिन्हित दीर्घ rx_bytes;
	अचिन्हित दीर्घ rx_dropped;
	अचिन्हित दीर्घ tx_packets;
	अचिन्हित दीर्घ tx_bytes;
	अचिन्हित दीर्घ tx_dropped;
पूर्ण;

अटल स्थिर काष्ठा gem_statistic queue_statistics[] = अणु
		QUEUE_STAT_TITLE("rx_packets"),
		QUEUE_STAT_TITLE("rx_bytes"),
		QUEUE_STAT_TITLE("rx_dropped"),
		QUEUE_STAT_TITLE("tx_packets"),
		QUEUE_STAT_TITLE("tx_bytes"),
		QUEUE_STAT_TITLE("tx_dropped"),
पूर्ण;

#घोषणा QUEUE_STATS_LEN ARRAY_SIZE(queue_statistics)

काष्ठा macb;
काष्ठा macb_queue;

काष्ठा macb_or_gem_ops अणु
	पूर्णांक	(*mog_alloc_rx_buffers)(काष्ठा macb *bp);
	व्योम	(*mog_मुक्त_rx_buffers)(काष्ठा macb *bp);
	व्योम	(*mog_init_rings)(काष्ठा macb *bp);
	पूर्णांक	(*mog_rx)(काष्ठा macb_queue *queue, काष्ठा napi_काष्ठा *napi,
			  पूर्णांक budget);
पूर्ण;

/* MACB-PTP पूर्णांकerface: adapt to platक्रमm needs. */
काष्ठा macb_ptp_info अणु
	व्योम (*ptp_init)(काष्ठा net_device *ndev);
	व्योम (*ptp_हटाओ)(काष्ठा net_device *ndev);
	s32 (*get_ptp_max_adj)(व्योम);
	अचिन्हित पूर्णांक (*get_tsu_rate)(काष्ठा macb *bp);
	पूर्णांक (*get_ts_info)(काष्ठा net_device *dev,
			   काष्ठा ethtool_ts_info *info);
	पूर्णांक (*get_hwtst)(काष्ठा net_device *netdev,
			 काष्ठा अगरreq *अगरr);
	पूर्णांक (*set_hwtst)(काष्ठा net_device *netdev,
			 काष्ठा अगरreq *अगरr, पूर्णांक cmd);
पूर्ण;

काष्ठा macb_pm_data अणु
	u32 scrt2;
	u32 usrio;
पूर्ण;

काष्ठा macb_usrio_config अणु
	u32 mii;
	u32 rmii;
	u32 rgmii;
	u32 refclk;
	u32 hdfctlen;
पूर्ण;

काष्ठा macb_config अणु
	u32			caps;
	अचिन्हित पूर्णांक		dma_burst_length;
	पूर्णांक	(*clk_init)(काष्ठा platक्रमm_device *pdev, काष्ठा clk **pclk,
			    काष्ठा clk **hclk, काष्ठा clk **tx_clk,
			    काष्ठा clk **rx_clk, काष्ठा clk **tsu_clk);
	पूर्णांक	(*init)(काष्ठा platक्रमm_device *pdev);
	पूर्णांक	jumbo_max_len;
	स्थिर काष्ठा macb_usrio_config *usrio;
पूर्ण;

काष्ठा tsu_incr अणु
	u32 sub_ns;
	u32 ns;
पूर्ण;

काष्ठा macb_queue अणु
	काष्ठा macb		*bp;
	पूर्णांक			irq;

	अचिन्हित पूर्णांक		ISR;
	अचिन्हित पूर्णांक		IER;
	अचिन्हित पूर्णांक		IDR;
	अचिन्हित पूर्णांक		IMR;
	अचिन्हित पूर्णांक		TBQP;
	अचिन्हित पूर्णांक		TBQPH;
	अचिन्हित पूर्णांक		RBQS;
	अचिन्हित पूर्णांक		RBQP;
	अचिन्हित पूर्णांक		RBQPH;

	अचिन्हित पूर्णांक		tx_head, tx_tail;
	काष्ठा macb_dma_desc	*tx_ring;
	काष्ठा macb_tx_skb	*tx_skb;
	dma_addr_t		tx_ring_dma;
	काष्ठा work_काष्ठा	tx_error_task;

	dma_addr_t		rx_ring_dma;
	dma_addr_t		rx_buffers_dma;
	अचिन्हित पूर्णांक		rx_tail;
	अचिन्हित पूर्णांक		rx_prepared_head;
	काष्ठा macb_dma_desc	*rx_ring;
	काष्ठा sk_buff		**rx_skbuff;
	व्योम			*rx_buffers;
	काष्ठा napi_काष्ठा	napi;
	काष्ठा queue_stats stats;

#अगर_घोषित CONFIG_MACB_USE_HWSTAMP
	काष्ठा work_काष्ठा	tx_ts_task;
	अचिन्हित पूर्णांक		tx_ts_head, tx_ts_tail;
	काष्ठा gem_tx_ts	tx_बारtamps[PTP_TS_BUFFER_SIZE];
#पूर्ण_अगर
पूर्ण;

काष्ठा ethtool_rx_fs_item अणु
	काष्ठा ethtool_rx_flow_spec fs;
	काष्ठा list_head list;
पूर्ण;

काष्ठा ethtool_rx_fs_list अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक count;
पूर्ण;

काष्ठा macb अणु
	व्योम __iomem		*regs;
	bool			native_io;

	/* hardware IO accessors */
	u32	(*macb_reg_पढ़ोl)(काष्ठा macb *bp, पूर्णांक offset);
	व्योम	(*macb_reg_ग_लिखोl)(काष्ठा macb *bp, पूर्णांक offset, u32 value);

	माप_प्रकार			rx_buffer_size;

	अचिन्हित पूर्णांक		rx_ring_size;
	अचिन्हित पूर्णांक		tx_ring_size;

	अचिन्हित पूर्णांक		num_queues;
	अचिन्हित पूर्णांक		queue_mask;
	काष्ठा macb_queue	queues[MACB_MAX_QUEUES];

	spinlock_t		lock;
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा clk		*pclk;
	काष्ठा clk		*hclk;
	काष्ठा clk		*tx_clk;
	काष्ठा clk		*rx_clk;
	काष्ठा clk		*tsu_clk;
	काष्ठा net_device	*dev;
	जोड़ अणु
		काष्ठा macb_stats	macb;
		काष्ठा gem_stats	gem;
	पूर्ण			hw_stats;

	काष्ठा macb_or_gem_ops	macbgem_ops;

	काष्ठा mii_bus		*mii_bus;
	काष्ठा phylink		*phylink;
	काष्ठा phylink_config	phylink_config;
	काष्ठा phylink_pcs	phylink_pcs;

	u32			caps;
	अचिन्हित पूर्णांक		dma_burst_length;

	phy_पूर्णांकerface_t		phy_पूर्णांकerface;

	/* AT91RM9200 transmit queue (1 on wire + 1 queued) */
	काष्ठा macb_tx_skb	rm9200_txq[2];
	अचिन्हित पूर्णांक		max_tx_length;

	u64			ethtool_stats[GEM_STATS_LEN + QUEUE_STATS_LEN * MACB_MAX_QUEUES];

	अचिन्हित पूर्णांक		rx_frm_len_mask;
	अचिन्हित पूर्णांक		jumbo_max_len;

	u32			wol;

	काष्ठा macb_ptp_info	*ptp_info;	/* macb-ptp पूर्णांकerface */
#अगर_घोषित MACB_EXT_DESC
	uपूर्णांक8_t hw_dma_cap;
#पूर्ण_अगर
	spinlock_t tsu_clk_lock; /* gem tsu घड़ी locking */
	अचिन्हित पूर्णांक tsu_rate;
	काष्ठा ptp_घड़ी *ptp_घड़ी;
	काष्ठा ptp_घड़ी_info ptp_घड़ी_info;
	काष्ठा tsu_incr tsu_incr;
	काष्ठा hwtstamp_config tstamp_config;

	/* RX queue filer rule set*/
	काष्ठा ethtool_rx_fs_list rx_fs_list;
	spinlock_t rx_fs_lock;
	अचिन्हित पूर्णांक max_tuples;

	काष्ठा tasklet_काष्ठा	hresp_err_tasklet;

	पूर्णांक	rx_bd_rd_prefetch;
	पूर्णांक	tx_bd_rd_prefetch;

	u32	rx_पूर्णांकr_mask;

	काष्ठा macb_pm_data pm_data;
	स्थिर काष्ठा macb_usrio_config *usrio;
पूर्ण;

#अगर_घोषित CONFIG_MACB_USE_HWSTAMP
#घोषणा GEM_TSEC_SIZE  (GEM_TSH_SIZE + GEM_TSL_SIZE)
#घोषणा TSU_SEC_MAX_VAL (((u64)1 << GEM_TSEC_SIZE) - 1)
#घोषणा TSU_NSEC_MAX_VAL ((1 << GEM_TN_SIZE) - 1)

क्रमागत macb_bd_control अणु
	TSTAMP_DISABLED,
	TSTAMP_FRAME_PTP_EVENT_ONLY,
	TSTAMP_ALL_PTP_FRAMES,
	TSTAMP_ALL_FRAMES,
पूर्ण;

व्योम gem_ptp_init(काष्ठा net_device *ndev);
व्योम gem_ptp_हटाओ(काष्ठा net_device *ndev);
पूर्णांक gem_ptp_txstamp(काष्ठा macb_queue *queue, काष्ठा sk_buff *skb, काष्ठा macb_dma_desc *des);
व्योम gem_ptp_rxstamp(काष्ठा macb *bp, काष्ठा sk_buff *skb, काष्ठा macb_dma_desc *desc);
अटल अंतरभूत पूर्णांक gem_ptp_करो_txstamp(काष्ठा macb_queue *queue, काष्ठा sk_buff *skb, काष्ठा macb_dma_desc *desc)
अणु
	अगर (queue->bp->tstamp_config.tx_type == TSTAMP_DISABLED)
		वापस -ENOTSUPP;

	वापस gem_ptp_txstamp(queue, skb, desc);
पूर्ण

अटल अंतरभूत व्योम gem_ptp_करो_rxstamp(काष्ठा macb *bp, काष्ठा sk_buff *skb, काष्ठा macb_dma_desc *desc)
अणु
	अगर (bp->tstamp_config.rx_filter == TSTAMP_DISABLED)
		वापस;

	gem_ptp_rxstamp(bp, skb, desc);
पूर्ण
पूर्णांक gem_get_hwtst(काष्ठा net_device *dev, काष्ठा अगरreq *rq);
पूर्णांक gem_set_hwtst(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);
#अन्यथा
अटल अंतरभूत व्योम gem_ptp_init(काष्ठा net_device *ndev) अणु पूर्ण
अटल अंतरभूत व्योम gem_ptp_हटाओ(काष्ठा net_device *ndev) अणु पूर्ण

अटल अंतरभूत पूर्णांक gem_ptp_करो_txstamp(काष्ठा macb_queue *queue, काष्ठा sk_buff *skb, काष्ठा macb_dma_desc *desc)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत व्योम gem_ptp_करो_rxstamp(काष्ठा macb *bp, काष्ठा sk_buff *skb, काष्ठा macb_dma_desc *desc) अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool macb_is_gem(काष्ठा macb *bp)
अणु
	वापस !!(bp->caps & MACB_CAPS_MACB_IS_GEM);
पूर्ण

अटल अंतरभूत bool gem_has_ptp(काष्ठा macb *bp)
अणु
	वापस !!(bp->caps & MACB_CAPS_GEM_HAS_PTP);
पूर्ण

/**
 * काष्ठा macb_platक्रमm_data - platक्रमm data क्रम MACB Ethernet used क्रम PCI registration
 * @pclk:		platक्रमm घड़ी
 * @hclk:		AHB घड़ी
 */
काष्ठा macb_platक्रमm_data अणु
	काष्ठा clk	*pclk;
	काष्ठा clk	*hclk;
पूर्ण;

#पूर्ण_अगर /* _MACB_H */
