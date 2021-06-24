<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*******************************************************************************
  Copyright (C) 2007-2009  STMicroelectronics Ltd


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/
#अगर_अघोषित __DWMAC1000_H__
#घोषणा __DWMAC1000_H__

#समावेश <linux/phy.h>
#समावेश "common.h"

#घोषणा GMAC_CONTROL		0x00000000	/* Configuration */
#घोषणा GMAC_FRAME_FILTER	0x00000004	/* Frame Filter */
#घोषणा GMAC_HASH_HIGH		0x00000008	/* Multicast Hash Table High */
#घोषणा GMAC_HASH_LOW		0x0000000c	/* Multicast Hash Table Low */
#घोषणा GMAC_MII_ADDR		0x00000010	/* MII Address */
#घोषणा GMAC_MII_DATA		0x00000014	/* MII Data */
#घोषणा GMAC_FLOW_CTRL		0x00000018	/* Flow Control */
#घोषणा GMAC_VLAN_TAG		0x0000001c	/* VLAN Tag */
#घोषणा GMAC_DEBUG		0x00000024	/* GMAC debug रेजिस्टर */
#घोषणा GMAC_WAKEUP_FILTER	0x00000028	/* Wake-up Frame Filter */

#घोषणा GMAC_INT_STATUS		0x00000038	/* पूर्णांकerrupt status रेजिस्टर */
#घोषणा GMAC_INT_STATUS_PMT	BIT(3)
#घोषणा GMAC_INT_STATUS_MMCIS	BIT(4)
#घोषणा GMAC_INT_STATUS_MMCRIS	BIT(5)
#घोषणा GMAC_INT_STATUS_MMCTIS	BIT(6)
#घोषणा GMAC_INT_STATUS_MMCCSUM	BIT(7)
#घोषणा GMAC_INT_STATUS_TSTAMP	BIT(9)
#घोषणा GMAC_INT_STATUS_LPIIS	BIT(10)

/* पूर्णांकerrupt mask रेजिस्टर */
#घोषणा	GMAC_INT_MASK		0x0000003c
#घोषणा	GMAC_INT_DISABLE_RGMII		BIT(0)
#घोषणा	GMAC_INT_DISABLE_PCSLINK	BIT(1)
#घोषणा	GMAC_INT_DISABLE_PCSAN		BIT(2)
#घोषणा	GMAC_INT_DISABLE_PMT		BIT(3)
#घोषणा	GMAC_INT_DISABLE_TIMESTAMP	BIT(9)
#घोषणा	GMAC_INT_DISABLE_PCS	(GMAC_INT_DISABLE_RGMII | \
				 GMAC_INT_DISABLE_PCSLINK | \
				 GMAC_INT_DISABLE_PCSAN)
#घोषणा	GMAC_INT_DEFAULT_MASK	(GMAC_INT_DISABLE_TIMESTAMP | \
				 GMAC_INT_DISABLE_PCS)

/* PMT Control and Status */
#घोषणा GMAC_PMT		0x0000002c
क्रमागत घातer_event अणु
	poपूर्णांकer_reset = 0x80000000,
	global_unicast = 0x00000200,
	wake_up_rx_frame = 0x00000040,
	magic_frame = 0x00000020,
	wake_up_frame_en = 0x00000004,
	magic_pkt_en = 0x00000002,
	घातer_करोwn = 0x00000001,
पूर्ण;

/* Energy Efficient Ethernet (EEE)
 *
 * LPI status, समयr and control रेजिस्टर offset
 */
#घोषणा LPI_CTRL_STATUS	0x0030
#घोषणा LPI_TIMER_CTRL	0x0034

/* LPI control and status defines */
#घोषणा LPI_CTRL_STATUS_LPITXA	0x00080000	/* Enable LPI TX Automate */
#घोषणा LPI_CTRL_STATUS_PLSEN	0x00040000	/* Enable PHY Link Status */
#घोषणा LPI_CTRL_STATUS_PLS	0x00020000	/* PHY Link Status */
#घोषणा LPI_CTRL_STATUS_LPIEN	0x00010000	/* LPI Enable */
#घोषणा LPI_CTRL_STATUS_RLPIST	0x00000200	/* Receive LPI state */
#घोषणा LPI_CTRL_STATUS_TLPIST	0x00000100	/* Transmit LPI state */
#घोषणा LPI_CTRL_STATUS_RLPIEX	0x00000008	/* Receive LPI Exit */
#घोषणा LPI_CTRL_STATUS_RLPIEN	0x00000004	/* Receive LPI Entry */
#घोषणा LPI_CTRL_STATUS_TLPIEX	0x00000002	/* Transmit LPI Exit */
#घोषणा LPI_CTRL_STATUS_TLPIEN	0x00000001	/* Transmit LPI Entry */

/* GMAC HW ADDR regs */
#घोषणा GMAC_ADDR_HIGH(reg)	((reg > 15) ? 0x00000800 + (reg - 16) * 8 : \
				 0x00000040 + (reg * 8))
#घोषणा GMAC_ADDR_LOW(reg)	((reg > 15) ? 0x00000804 + (reg - 16) * 8 : \
				 0x00000044 + (reg * 8))
#घोषणा GMAC_MAX_PERFECT_ADDRESSES	1

#घोषणा GMAC_PCS_BASE		0x000000c0	/* PCS रेजिस्टर base */
#घोषणा GMAC_RGSMIIIS		0x000000d8	/* RGMII/SMII status */

/* SGMII/RGMII status रेजिस्टर */
#घोषणा GMAC_RGSMIIIS_LNKMODE		BIT(0)
#घोषणा GMAC_RGSMIIIS_SPEED		GENMASK(2, 1)
#घोषणा GMAC_RGSMIIIS_SPEED_SHIFT	1
#घोषणा GMAC_RGSMIIIS_LNKSTS		BIT(3)
#घोषणा GMAC_RGSMIIIS_JABTO		BIT(4)
#घोषणा GMAC_RGSMIIIS_FALSECARDET	BIT(5)
#घोषणा GMAC_RGSMIIIS_SMIDRXS		BIT(16)
/* LNKMOD */
#घोषणा GMAC_RGSMIIIS_LNKMOD_MASK	0x1
/* LNKSPEED */
#घोषणा GMAC_RGSMIIIS_SPEED_125		0x2
#घोषणा GMAC_RGSMIIIS_SPEED_25		0x1
#घोषणा GMAC_RGSMIIIS_SPEED_2_5		0x0

/* GMAC Configuration defines */
#घोषणा GMAC_CONTROL_2K 0x08000000	/* IEEE 802.3as 2K packets */
#घोषणा GMAC_CONTROL_TC	0x01000000	/* Transmit Conf. in RGMII/SGMII */
#घोषणा GMAC_CONTROL_WD	0x00800000	/* Disable Watchकरोg on receive */
#घोषणा GMAC_CONTROL_JD	0x00400000	/* Jabber disable */
#घोषणा GMAC_CONTROL_BE	0x00200000	/* Frame Burst Enable */
#घोषणा GMAC_CONTROL_JE	0x00100000	/* Jumbo frame */
क्रमागत पूर्णांकer_frame_gap अणु
	GMAC_CONTROL_IFG_88 = 0x00040000,
	GMAC_CONTROL_IFG_80 = 0x00020000,
	GMAC_CONTROL_IFG_40 = 0x000e0000,
पूर्ण;
#घोषणा GMAC_CONTROL_DCRS	0x00010000	/* Disable carrier sense */
#घोषणा GMAC_CONTROL_PS		0x00008000	/* Port Select 0:GMI 1:MII */
#घोषणा GMAC_CONTROL_FES	0x00004000	/* Speed 0:10 1:100 */
#घोषणा GMAC_CONTROL_DO		0x00002000	/* Disable Rx Own */
#घोषणा GMAC_CONTROL_LM		0x00001000	/* Loop-back mode */
#घोषणा GMAC_CONTROL_DM		0x00000800	/* Duplex Mode */
#घोषणा GMAC_CONTROL_IPC	0x00000400	/* Checksum Offload */
#घोषणा GMAC_CONTROL_DR		0x00000200	/* Disable Retry */
#घोषणा GMAC_CONTROL_LUD	0x00000100	/* Link up/करोwn */
#घोषणा GMAC_CONTROL_ACS	0x00000080	/* Auto Pad/FCS Stripping */
#घोषणा GMAC_CONTROL_DC		0x00000010	/* Deferral Check */
#घोषणा GMAC_CONTROL_TE		0x00000008	/* Transmitter Enable */
#घोषणा GMAC_CONTROL_RE		0x00000004	/* Receiver Enable */

#घोषणा GMAC_CORE_INIT (GMAC_CONTROL_JD | GMAC_CONTROL_PS | GMAC_CONTROL_ACS | \
			GMAC_CONTROL_BE | GMAC_CONTROL_DCRS)

/* GMAC Frame Filter defines */
#घोषणा GMAC_FRAME_FILTER_PR	0x00000001	/* Promiscuous Mode */
#घोषणा GMAC_FRAME_FILTER_HUC	0x00000002	/* Hash Unicast */
#घोषणा GMAC_FRAME_FILTER_HMC	0x00000004	/* Hash Multicast */
#घोषणा GMAC_FRAME_FILTER_DAIF	0x00000008	/* DA Inverse Filtering */
#घोषणा GMAC_FRAME_FILTER_PM	0x00000010	/* Pass all multicast */
#घोषणा GMAC_FRAME_FILTER_DBF	0x00000020	/* Disable Broadcast frames */
#घोषणा GMAC_FRAME_FILTER_PCF	0x00000080	/* Pass Control frames */
#घोषणा GMAC_FRAME_FILTER_SAIF	0x00000100	/* Inverse Filtering */
#घोषणा GMAC_FRAME_FILTER_SAF	0x00000200	/* Source Address Filter */
#घोषणा GMAC_FRAME_FILTER_HPF	0x00000400	/* Hash or perfect Filter */
#घोषणा GMAC_FRAME_FILTER_RA	0x80000000	/* Receive all mode */
/* GMII ADDR  defines */
#घोषणा GMAC_MII_ADDR_WRITE	0x00000002	/* MII Write */
#घोषणा GMAC_MII_ADDR_BUSY	0x00000001	/* MII Busy */
/* GMAC FLOW CTRL defines */
#घोषणा GMAC_FLOW_CTRL_PT_MASK	0xffff0000	/* Pause Time Mask */
#घोषणा GMAC_FLOW_CTRL_PT_SHIFT	16
#घोषणा GMAC_FLOW_CTRL_UP	0x00000008	/* Unicast छोड़ो frame enable */
#घोषणा GMAC_FLOW_CTRL_RFE	0x00000004	/* Rx Flow Control Enable */
#घोषणा GMAC_FLOW_CTRL_TFE	0x00000002	/* Tx Flow Control Enable */
#घोषणा GMAC_FLOW_CTRL_FCB_BPA	0x00000001	/* Flow Control Busy ... */

/* DEBUG Register defines */
/* MTL TxStatus FIFO */
#घोषणा GMAC_DEBUG_TXSTSFSTS	BIT(25)	/* MTL TxStatus FIFO Full Status */
#घोषणा GMAC_DEBUG_TXFSTS	BIT(24) /* MTL Tx FIFO Not Empty Status */
#घोषणा GMAC_DEBUG_TWCSTS	BIT(22) /* MTL Tx FIFO Write Controller */
/* MTL Tx FIFO Read Controller Status */
#घोषणा GMAC_DEBUG_TRCSTS_MASK	GENMASK(21, 20)
#घोषणा GMAC_DEBUG_TRCSTS_SHIFT	20
#घोषणा GMAC_DEBUG_TRCSTS_IDLE	0
#घोषणा GMAC_DEBUG_TRCSTS_READ	1
#घोषणा GMAC_DEBUG_TRCSTS_TXW	2
#घोषणा GMAC_DEBUG_TRCSTS_WRITE	3
#घोषणा GMAC_DEBUG_TXPAUSED	BIT(19) /* MAC Transmitter in PAUSE */
/* MAC Transmit Frame Controller Status */
#घोषणा GMAC_DEBUG_TFCSTS_MASK	GENMASK(18, 17)
#घोषणा GMAC_DEBUG_TFCSTS_SHIFT	17
#घोषणा GMAC_DEBUG_TFCSTS_IDLE	0
#घोषणा GMAC_DEBUG_TFCSTS_WAIT	1
#घोषणा GMAC_DEBUG_TFCSTS_GEN_PAUSE	2
#घोषणा GMAC_DEBUG_TFCSTS_XFER	3
/* MAC GMII or MII Transmit Protocol Engine Status */
#घोषणा GMAC_DEBUG_TPESTS	BIT(16)
#घोषणा GMAC_DEBUG_RXFSTS_MASK	GENMASK(9, 8) /* MTL Rx FIFO Fill-level */
#घोषणा GMAC_DEBUG_RXFSTS_SHIFT	8
#घोषणा GMAC_DEBUG_RXFSTS_EMPTY	0
#घोषणा GMAC_DEBUG_RXFSTS_BT	1
#घोषणा GMAC_DEBUG_RXFSTS_AT	2
#घोषणा GMAC_DEBUG_RXFSTS_FULL	3
#घोषणा GMAC_DEBUG_RRCSTS_MASK	GENMASK(6, 5) /* MTL Rx FIFO Read Controller */
#घोषणा GMAC_DEBUG_RRCSTS_SHIFT	5
#घोषणा GMAC_DEBUG_RRCSTS_IDLE	0
#घोषणा GMAC_DEBUG_RRCSTS_RDATA	1
#घोषणा GMAC_DEBUG_RRCSTS_RSTAT	2
#घोषणा GMAC_DEBUG_RRCSTS_FLUSH	3
#घोषणा GMAC_DEBUG_RWCSTS	BIT(4) /* MTL Rx FIFO Write Controller Active */
/* MAC Receive Frame Controller FIFO Status */
#घोषणा GMAC_DEBUG_RFCFCSTS_MASK	GENMASK(2, 1)
#घोषणा GMAC_DEBUG_RFCFCSTS_SHIFT	1
/* MAC GMII or MII Receive Protocol Engine Status */
#घोषणा GMAC_DEBUG_RPESTS	BIT(0)

/*--- DMA BLOCK defines ---*/
/* DMA Bus Mode रेजिस्टर defines */
#घोषणा DMA_BUS_MODE_DA		0x00000002	/* Arbitration scheme */
#घोषणा DMA_BUS_MODE_DSL_MASK	0x0000007c	/* Descriptor Skip Length */
#घोषणा DMA_BUS_MODE_DSL_SHIFT	2		/*   (in DWORDS)      */
/* Programmable burst length (passed thorugh platक्रमm)*/
#घोषणा DMA_BUS_MODE_PBL_MASK	0x00003f00	/* Programmable Burst Len */
#घोषणा DMA_BUS_MODE_PBL_SHIFT	8
#घोषणा DMA_BUS_MODE_ATDS	0x00000080	/* Alternate Descriptor Size */

क्रमागत rx_tx_priority_ratio अणु
	द्विगुन_ratio = 0x00004000,	/* 2:1 */
	triple_ratio = 0x00008000,	/* 3:1 */
	quadruple_ratio = 0x0000c000,	/* 4:1 */
पूर्ण;

#घोषणा DMA_BUS_MODE_FB		0x00010000	/* Fixed burst */
#घोषणा DMA_BUS_MODE_MB		0x04000000	/* Mixed burst */
#घोषणा DMA_BUS_MODE_RPBL_MASK	0x007e0000	/* Rx-Programmable Burst Len */
#घोषणा DMA_BUS_MODE_RPBL_SHIFT	17
#घोषणा DMA_BUS_MODE_USP	0x00800000
#घोषणा DMA_BUS_MODE_MAXPBL	0x01000000
#घोषणा DMA_BUS_MODE_AAL	0x02000000

/* DMA CRS Control and Status Register Mapping */
#घोषणा DMA_HOST_TX_DESC	  0x00001048	/* Current Host Tx descriptor */
#घोषणा DMA_HOST_RX_DESC	  0x0000104c	/* Current Host Rx descriptor */
/*  DMA Bus Mode रेजिस्टर defines */
#घोषणा DMA_BUS_PR_RATIO_MASK	  0x0000c000	/* Rx/Tx priority ratio */
#घोषणा DMA_BUS_PR_RATIO_SHIFT	  14
#घोषणा DMA_BUS_FB	  	  0x00010000	/* Fixed Burst */

/* DMA operation mode defines (start/stop tx/rx are placed in common header)*/
/* Disable Drop TCP/IP csum error */
#घोषणा DMA_CONTROL_DT		0x04000000
#घोषणा DMA_CONTROL_RSF		0x02000000	/* Receive Store and Forward */
#घोषणा DMA_CONTROL_DFF		0x01000000	/* Disaable flushing */
/* Threshold क्रम Activating the FC */
क्रमागत rfa अणु
	act_full_minus_1 = 0x00800000,
	act_full_minus_2 = 0x00800200,
	act_full_minus_3 = 0x00800400,
	act_full_minus_4 = 0x00800600,
पूर्ण;
/* Threshold क्रम Deactivating the FC */
क्रमागत rfd अणु
	deac_full_minus_1 = 0x00400000,
	deac_full_minus_2 = 0x00400800,
	deac_full_minus_3 = 0x00401000,
	deac_full_minus_4 = 0x00401800,
पूर्ण;
#घोषणा DMA_CONTROL_TSF	0x00200000	/* Transmit  Store and Forward */

क्रमागत ttc_control अणु
	DMA_CONTROL_TTC_64 = 0x00000000,
	DMA_CONTROL_TTC_128 = 0x00004000,
	DMA_CONTROL_TTC_192 = 0x00008000,
	DMA_CONTROL_TTC_256 = 0x0000c000,
	DMA_CONTROL_TTC_40 = 0x00010000,
	DMA_CONTROL_TTC_32 = 0x00014000,
	DMA_CONTROL_TTC_24 = 0x00018000,
	DMA_CONTROL_TTC_16 = 0x0001c000,
पूर्ण;
#घोषणा DMA_CONTROL_TC_TX_MASK	0xfffe3fff

#घोषणा DMA_CONTROL_EFC		0x00000100
#घोषणा DMA_CONTROL_FEF		0x00000080
#घोषणा DMA_CONTROL_FUF		0x00000040

/* Receive flow control activation field
 * RFA field in DMA control रेजिस्टर, bits 23,10:9
 */
#घोषणा DMA_CONTROL_RFA_MASK	0x00800600

/* Receive flow control deactivation field
 * RFD field in DMA control रेजिस्टर, bits 22,12:11
 */
#घोषणा DMA_CONTROL_RFD_MASK	0x00401800

/* RFD and RFA fields are encoded as follows
 *
 *   Bit Field
 *   0,00 - Full minus 1KB (only valid when rxfअगरo >= 4KB and EFC enabled)
 *   0,01 - Full minus 2KB (only valid when rxfअगरo >= 4KB and EFC enabled)
 *   0,10 - Full minus 3KB (only valid when rxfअगरo >= 4KB and EFC enabled)
 *   0,11 - Full minus 4KB (only valid when rxfअगरo > 4KB and EFC enabled)
 *   1,00 - Full minus 5KB (only valid when rxfअगरo > 8KB and EFC enabled)
 *   1,01 - Full minus 6KB (only valid when rxfअगरo > 8KB and EFC enabled)
 *   1,10 - Full minus 7KB (only valid when rxfअगरo > 8KB and EFC enabled)
 *   1,11 - Reserved
 *
 * RFD should always be > RFA क्रम a given FIFO size. RFD == RFA may work,
 * but packet throughput perक्रमmance may not be as expected.
 *
 * Be sure that bit 3 in GMAC Register 6 is set क्रम Unicast Pause frame
 * detection (IEEE Specअगरication Requirement, Annex 31B, 31B.1, Pause
 * Description).
 *
 * Be sure that DZPA (bit 7 in Flow Control Register, GMAC Register 6),
 * is set to 0. This allows छोड़ो frames with a quanta of 0 to be sent
 * as an XOFF message to the link peer.
 */

#घोषणा RFA_FULL_MINUS_1K	0x00000000
#घोषणा RFA_FULL_MINUS_2K	0x00000200
#घोषणा RFA_FULL_MINUS_3K	0x00000400
#घोषणा RFA_FULL_MINUS_4K	0x00000600
#घोषणा RFA_FULL_MINUS_5K	0x00800000
#घोषणा RFA_FULL_MINUS_6K	0x00800200
#घोषणा RFA_FULL_MINUS_7K	0x00800400

#घोषणा RFD_FULL_MINUS_1K	0x00000000
#घोषणा RFD_FULL_MINUS_2K	0x00000800
#घोषणा RFD_FULL_MINUS_3K	0x00001000
#घोषणा RFD_FULL_MINUS_4K	0x00001800
#घोषणा RFD_FULL_MINUS_5K	0x00400000
#घोषणा RFD_FULL_MINUS_6K	0x00400800
#घोषणा RFD_FULL_MINUS_7K	0x00401000

क्रमागत rtc_control अणु
	DMA_CONTROL_RTC_64 = 0x00000000,
	DMA_CONTROL_RTC_32 = 0x00000008,
	DMA_CONTROL_RTC_96 = 0x00000010,
	DMA_CONTROL_RTC_128 = 0x00000018,
पूर्ण;
#घोषणा DMA_CONTROL_TC_RX_MASK	0xffffffe7

#घोषणा DMA_CONTROL_OSF	0x00000004	/* Operate on second frame */

/* MMC रेजिस्टरs offset */
#घोषणा GMAC_MMC_CTRL      0x100
#घोषणा GMAC_MMC_RX_INTR   0x104
#घोषणा GMAC_MMC_TX_INTR   0x108
#घोषणा GMAC_MMC_RX_CSUM_OFFLOAD   0x208
#घोषणा GMAC_EXTHASH_BASE  0x500

बाह्य स्थिर काष्ठा sपंचांगmac_dma_ops dwmac1000_dma_ops;
#पूर्ण_अगर /* __DWMAC1000_H__ */
