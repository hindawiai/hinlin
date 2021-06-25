<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _B44_H
#घोषणा _B44_H

#समावेश <linux/brcmphy.h>

/* Register layout. (These correspond to काष्ठा _bcmenettregs in bcm4400.) */
#घोषणा	B44_DEVCTRL	0x0000UL /* Device Control */
#घोषणा  DEVCTRL_MPM		0x00000040 /* Magic Packet PME Enable (B0 only) */
#घोषणा  DEVCTRL_PFE		0x00000080 /* Pattern Filtering Enable */
#घोषणा  DEVCTRL_IPP		0x00000400 /* Internal EPHY Present */
#घोषणा  DEVCTRL_EPR		0x00008000 /* EPHY Reset */
#घोषणा  DEVCTRL_PME		0x00001000 /* PHY Mode Enable */
#घोषणा  DEVCTRL_PMCE		0x00002000 /* PHY Mode Clocks Enable */
#घोषणा  DEVCTRL_PADDR		0x0007c000 /* PHY Address */
#घोषणा  DEVCTRL_PADDR_SHIFT	18
#घोषणा B44_BIST_STAT	0x000CUL /* Built-In Self-Test Status */
#घोषणा B44_WKUP_LEN	0x0010UL /* Wakeup Length */
#घोषणा  WKUP_LEN_P0_MASK	0x0000007f /* Pattern 0 */
#घोषणा  WKUP_LEN_D0		0x00000080
#घोषणा  WKUP_LEN_P1_MASK	0x00007f00 /* Pattern 1 */
#घोषणा  WKUP_LEN_P1_SHIFT	8
#घोषणा  WKUP_LEN_D1		0x00008000
#घोषणा  WKUP_LEN_P2_MASK	0x007f0000 /* Pattern 2 */
#घोषणा  WKUP_LEN_P2_SHIFT	16
#घोषणा  WKUP_LEN_D2		0x00000000
#घोषणा  WKUP_LEN_P3_MASK	0x7f000000 /* Pattern 3 */
#घोषणा  WKUP_LEN_P3_SHIFT	24
#घोषणा  WKUP_LEN_D3		0x80000000
#घोषणा  WKUP_LEN_DISABLE	0x80808080
#घोषणा  WKUP_LEN_ENABLE_TWO	0x80800000
#घोषणा  WKUP_LEN_ENABLE_THREE	0x80000000
#घोषणा B44_ISTAT	0x0020UL /* Interrupt Status */
#घोषणा  ISTAT_LS		0x00000020 /* Link Change (B0 only) */
#घोषणा  ISTAT_PME		0x00000040 /* Power Management Event */
#घोषणा  ISTAT_TO		0x00000080 /* General Purpose Timeout */
#घोषणा  ISTAT_DSCE		0x00000400 /* Descriptor Error */
#घोषणा  ISTAT_DATAE		0x00000800 /* Data Error */
#घोषणा  ISTAT_DPE		0x00001000 /* Descr. Protocol Error */
#घोषणा  ISTAT_RDU		0x00002000 /* Receive Descr. Underflow */
#घोषणा  ISTAT_RFO		0x00004000 /* Receive FIFO Overflow */
#घोषणा  ISTAT_TFU		0x00008000 /* Transmit FIFO Underflow */
#घोषणा  ISTAT_RX		0x00010000 /* RX Interrupt */
#घोषणा  ISTAT_TX		0x01000000 /* TX Interrupt */
#घोषणा  ISTAT_EMAC		0x04000000 /* EMAC Interrupt */
#घोषणा  ISTAT_MII_WRITE	0x08000000 /* MII Write Interrupt */
#घोषणा  ISTAT_MII_READ		0x10000000 /* MII Read Interrupt */
#घोषणा  ISTAT_ERRORS (ISTAT_DSCE|ISTAT_DATAE|ISTAT_DPE|ISTAT_RDU|ISTAT_RFO|ISTAT_TFU)
#घोषणा B44_IMASK	0x0024UL /* Interrupt Mask */
#घोषणा  IMASK_DEF		(ISTAT_ERRORS | ISTAT_TO | ISTAT_RX | ISTAT_TX)
#घोषणा B44_GPTIMER	0x0028UL /* General Purpose Timer */
#घोषणा B44_ADDR_LO	0x0088UL /* ENET Address Lo (B0 only) */
#घोषणा B44_ADDR_HI	0x008CUL /* ENET Address Hi (B0 only) */
#घोषणा B44_FILT_ADDR	0x0090UL /* ENET Filter Address */
#घोषणा B44_FILT_DATA	0x0094UL /* ENET Filter Data */
#घोषणा B44_TXBURST	0x00A0UL /* TX Max Burst Length */
#घोषणा B44_RXBURST	0x00A4UL /* RX Max Burst Length */
#घोषणा B44_MAC_CTRL	0x00A8UL /* MAC Control */
#घोषणा  MAC_CTRL_CRC32_ENAB	0x00000001 /* CRC32 Generation Enable */
#घोषणा  MAC_CTRL_PHY_PDOWN	0x00000004 /* Onchip EPHY Powerकरोwn */
#घोषणा  MAC_CTRL_PHY_EDET	0x00000008 /* Onchip EPHY Energy Detected */
#घोषणा  MAC_CTRL_PHY_LEDCTRL	0x000000e0 /* Onchip EPHY LED Control */
#घोषणा  MAC_CTRL_PHY_LEDCTRL_SHIFT 5
#घोषणा B44_MAC_FLOW	0x00ACUL /* MAC Flow Control */
#घोषणा  MAC_FLOW_RX_HI_WATER	0x000000ff /* Receive FIFO HI Water Mark */
#घोषणा  MAC_FLOW_PAUSE_ENAB	0x00008000 /* Enable Pause Frame Generation */
#घोषणा B44_RCV_LAZY	0x0100UL /* Lazy Interrupt Control */
#घोषणा  RCV_LAZY_TO_MASK	0x00ffffff /* Timeout */
#घोषणा  RCV_LAZY_FC_MASK	0xff000000 /* Frame Count */
#घोषणा  RCV_LAZY_FC_SHIFT	24
#घोषणा B44_DMATX_CTRL	0x0200UL /* DMA TX Control */
#घोषणा  DMATX_CTRL_ENABLE	0x00000001 /* Enable */
#घोषणा  DMATX_CTRL_SUSPEND	0x00000002 /* Suepend Request */
#घोषणा  DMATX_CTRL_LPBACK	0x00000004 /* Loopback Enable */
#घोषणा  DMATX_CTRL_FAIRPRIOR	0x00000008 /* Fair Priority */
#घोषणा  DMATX_CTRL_FLUSH	0x00000010 /* Flush Request */
#घोषणा B44_DMATX_ADDR	0x0204UL /* DMA TX Descriptor Ring Address */
#घोषणा B44_DMATX_PTR	0x0208UL /* DMA TX Last Posted Descriptor */
#घोषणा B44_DMATX_STAT	0x020CUL /* DMA TX Current Active Desc. + Status */
#घोषणा  DMATX_STAT_CDMASK	0x00000fff /* Current Descriptor Mask */
#घोषणा  DMATX_STAT_SMASK	0x0000f000 /* State Mask */
#घोषणा  DMATX_STAT_SDISABLED	0x00000000 /* State Disabled */
#घोषणा  DMATX_STAT_SACTIVE	0x00001000 /* State Active */
#घोषणा  DMATX_STAT_SIDLE	0x00002000 /* State Idle Wait */
#घोषणा  DMATX_STAT_SSTOPPED	0x00003000 /* State Stopped */
#घोषणा  DMATX_STAT_SSUSP	0x00004000 /* State Suspend Pending */
#घोषणा  DMATX_STAT_EMASK	0x000f0000 /* Error Mask */
#घोषणा  DMATX_STAT_ENONE	0x00000000 /* Error None */
#घोषणा  DMATX_STAT_EDPE	0x00010000 /* Error Desc. Protocol Error */
#घोषणा  DMATX_STAT_EDFU	0x00020000 /* Error Data FIFO Underrun */
#घोषणा  DMATX_STAT_EBEBR	0x00030000 /* Error Bus Error on Buffer Read */
#घोषणा  DMATX_STAT_EBEDA	0x00040000 /* Error Bus Error on Desc. Access */
#घोषणा  DMATX_STAT_FLUSHED	0x00100000 /* Flushed */
#घोषणा B44_DMARX_CTRL	0x0210UL /* DMA RX Control */
#घोषणा  DMARX_CTRL_ENABLE	0x00000001 /* Enable */
#घोषणा  DMARX_CTRL_ROMASK	0x000000fe /* Receive Offset Mask */
#घोषणा  DMARX_CTRL_ROSHIFT	1 	   /* Receive Offset Shअगरt */
#घोषणा B44_DMARX_ADDR	0x0214UL /* DMA RX Descriptor Ring Address */
#घोषणा B44_DMARX_PTR	0x0218UL /* DMA RX Last Posted Descriptor */
#घोषणा B44_DMARX_STAT	0x021CUL /* DMA RX Current Active Desc. + Status */
#घोषणा  DMARX_STAT_CDMASK	0x00000fff /* Current Descriptor Mask */
#घोषणा  DMARX_STAT_SMASK	0x0000f000 /* State Mask */
#घोषणा  DMARX_STAT_SDISABLED	0x00000000 /* State Disabled */
#घोषणा  DMARX_STAT_SACTIVE	0x00001000 /* State Active */
#घोषणा  DMARX_STAT_SIDLE	0x00002000 /* State Idle Wait */
#घोषणा  DMARX_STAT_SSTOPPED	0x00003000 /* State Stopped */
#घोषणा  DMARX_STAT_EMASK	0x000f0000 /* Error Mask */
#घोषणा  DMARX_STAT_ENONE	0x00000000 /* Error None */
#घोषणा  DMARX_STAT_EDPE	0x00010000 /* Error Desc. Protocol Error */
#घोषणा  DMARX_STAT_EDFO	0x00020000 /* Error Data FIFO Overflow */
#घोषणा  DMARX_STAT_EBEBW	0x00030000 /* Error Bus Error on Buffer Write */
#घोषणा  DMARX_STAT_EBEDA	0x00040000 /* Error Bus Error on Desc. Access */
#घोषणा B44_DMAFIFO_AD	0x0220UL /* DMA FIFO Diag Address */
#घोषणा  DMAFIFO_AD_OMASK	0x0000ffff /* Offset Mask */
#घोषणा  DMAFIFO_AD_SMASK	0x000f0000 /* Select Mask */
#घोषणा  DMAFIFO_AD_SXDD	0x00000000 /* Select Transmit DMA Data */
#घोषणा  DMAFIFO_AD_SXDP	0x00010000 /* Select Transmit DMA Poपूर्णांकers */
#घोषणा  DMAFIFO_AD_SRDD	0x00040000 /* Select Receive DMA Data */
#घोषणा  DMAFIFO_AD_SRDP	0x00050000 /* Select Receive DMA Poपूर्णांकers */
#घोषणा  DMAFIFO_AD_SXFD	0x00080000 /* Select Transmit FIFO Data */
#घोषणा  DMAFIFO_AD_SXFP	0x00090000 /* Select Transmit FIFO Poपूर्णांकers */
#घोषणा  DMAFIFO_AD_SRFD	0x000c0000 /* Select Receive FIFO Data */
#घोषणा  DMAFIFO_AD_SRFP	0x000c0000 /* Select Receive FIFO Poपूर्णांकers */
#घोषणा B44_DMAFIFO_LO	0x0224UL /* DMA FIFO Diag Low Data */
#घोषणा B44_DMAFIFO_HI	0x0228UL /* DMA FIFO Diag High Data */
#घोषणा B44_RXCONFIG	0x0400UL /* EMAC RX Config */
#घोषणा  RXCONFIG_DBCAST	0x00000001 /* Disable Broadcast */
#घोषणा  RXCONFIG_ALLMULTI	0x00000002 /* Accept All Multicast */
#घोषणा  RXCONFIG_NORX_WHILE_TX	0x00000004 /* Receive Disable While Transmitting */
#घोषणा  RXCONFIG_PROMISC	0x00000008 /* Promiscuous Enable */
#घोषणा  RXCONFIG_LPBACK	0x00000010 /* Loopback Enable */
#घोषणा  RXCONFIG_FLOW		0x00000020 /* Flow Control Enable */
#घोषणा  RXCONFIG_FLOW_ACCEPT	0x00000040 /* Accept Unicast Flow Control Frame */
#घोषणा  RXCONFIG_RFILT		0x00000080 /* Reject Filter */
#घोषणा  RXCONFIG_CAM_ABSENT	0x00000100 /* CAM Absent */
#घोषणा B44_RXMAXLEN	0x0404UL /* EMAC RX Max Packet Length */
#घोषणा B44_TXMAXLEN	0x0408UL /* EMAC TX Max Packet Length */
#घोषणा B44_MDIO_CTRL	0x0410UL /* EMAC MDIO Control */
#घोषणा  MDIO_CTRL_MAXF_MASK	0x0000007f /* MDC Frequency */
#घोषणा  MDIO_CTRL_PREAMBLE	0x00000080 /* MII Preamble Enable */
#घोषणा B44_MDIO_DATA	0x0414UL /* EMAC MDIO Data */
#घोषणा  MDIO_DATA_DATA		0x0000ffff /* R/W Data */
#घोषणा  MDIO_DATA_TA_MASK	0x00030000 /* Turnaround Value */
#घोषणा  MDIO_DATA_TA_SHIFT	16
#घोषणा  MDIO_TA_VALID		2
#घोषणा  MDIO_DATA_RA_MASK	0x007c0000 /* Register Address */
#घोषणा  MDIO_DATA_RA_SHIFT	18
#घोषणा  MDIO_DATA_PMD_MASK	0x0f800000 /* Physical Media Device */
#घोषणा  MDIO_DATA_PMD_SHIFT	23
#घोषणा  MDIO_DATA_OP_MASK	0x30000000 /* Opcode */
#घोषणा  MDIO_DATA_OP_SHIFT	28
#घोषणा  MDIO_OP_WRITE		1
#घोषणा  MDIO_OP_READ		2
#घोषणा  MDIO_DATA_SB_MASK	0xc0000000 /* Start Bits */
#घोषणा  MDIO_DATA_SB_SHIFT	30
#घोषणा  MDIO_DATA_SB_START	0x40000000 /* Start Of Frame */
#घोषणा B44_EMAC_IMASK	0x0418UL /* EMAC Interrupt Mask */
#घोषणा B44_EMAC_ISTAT	0x041CUL /* EMAC Interrupt Status */
#घोषणा  EMAC_INT_MII		0x00000001 /* MII MDIO Interrupt */
#घोषणा  EMAC_INT_MIB		0x00000002 /* MIB Interrupt */
#घोषणा  EMAC_INT_FLOW		0x00000003 /* Flow Control Interrupt */
#घोषणा B44_CAM_DATA_LO	0x0420UL /* EMAC CAM Data Low */
#घोषणा B44_CAM_DATA_HI	0x0424UL /* EMAC CAM Data High */
#घोषणा  CAM_DATA_HI_VALID	0x00010000 /* Valid Bit */
#घोषणा B44_CAM_CTRL	0x0428UL /* EMAC CAM Control */
#घोषणा  CAM_CTRL_ENABLE	0x00000001 /* CAM Enable */
#घोषणा  CAM_CTRL_MSEL		0x00000002 /* Mask Select */
#घोषणा  CAM_CTRL_READ		0x00000004 /* Read */
#घोषणा  CAM_CTRL_WRITE		0x00000008 /* Read */
#घोषणा  CAM_CTRL_INDEX_MASK	0x003f0000 /* Index Mask */
#घोषणा  CAM_CTRL_INDEX_SHIFT	16
#घोषणा  CAM_CTRL_BUSY		0x80000000 /* CAM Busy */
#घोषणा B44_ENET_CTRL	0x042CUL /* EMAC ENET Control */
#घोषणा  ENET_CTRL_ENABLE	0x00000001 /* EMAC Enable */
#घोषणा  ENET_CTRL_DISABLE	0x00000002 /* EMAC Disable */
#घोषणा  ENET_CTRL_SRST		0x00000004 /* EMAC Soft Reset */
#घोषणा  ENET_CTRL_EPSEL	0x00000008 /* External PHY Select */
#घोषणा B44_TX_CTRL	0x0430UL /* EMAC TX Control */
#घोषणा  TX_CTRL_DUPLEX		0x00000001 /* Full Duplex */
#घोषणा  TX_CTRL_FMODE		0x00000002 /* Flow Mode */
#घोषणा  TX_CTRL_SBENAB		0x00000004 /* Single Backoff Enable */
#घोषणा  TX_CTRL_SMALL_SLOT	0x00000008 /* Small Slotसमय */
#घोषणा B44_TX_WMARK	0x0434UL /* EMAC TX Watermark */
#घोषणा B44_MIB_CTRL	0x0438UL /* EMAC MIB Control */
#घोषणा  MIB_CTRL_CLR_ON_READ	0x00000001 /* Autoclear on Read */
#घोषणा B44_TX_GOOD_O	0x0500UL /* MIB TX Good Octets */
#घोषणा B44_TX_GOOD_P	0x0504UL /* MIB TX Good Packets */
#घोषणा B44_TX_O	0x0508UL /* MIB TX Octets */
#घोषणा B44_TX_P	0x050CUL /* MIB TX Packets */
#घोषणा B44_TX_BCAST	0x0510UL /* MIB TX Broadcast Packets */
#घोषणा B44_TX_MCAST	0x0514UL /* MIB TX Multicast Packets */
#घोषणा B44_TX_64	0x0518UL /* MIB TX <= 64 byte Packets */
#घोषणा B44_TX_65_127	0x051CUL /* MIB TX 65 to 127 byte Packets */
#घोषणा B44_TX_128_255	0x0520UL /* MIB TX 128 to 255 byte Packets */
#घोषणा B44_TX_256_511	0x0524UL /* MIB TX 256 to 511 byte Packets */
#घोषणा B44_TX_512_1023	0x0528UL /* MIB TX 512 to 1023 byte Packets */
#घोषणा B44_TX_1024_MAX	0x052CUL /* MIB TX 1024 to max byte Packets */
#घोषणा B44_TX_JABBER	0x0530UL /* MIB TX Jabber Packets */
#घोषणा B44_TX_OSIZE	0x0534UL /* MIB TX Oversize Packets */
#घोषणा B44_TX_FRAG	0x0538UL /* MIB TX Fragment Packets */
#घोषणा B44_TX_URUNS	0x053CUL /* MIB TX Underruns */
#घोषणा B44_TX_TCOLS	0x0540UL /* MIB TX Total Collisions */
#घोषणा B44_TX_SCOLS	0x0544UL /* MIB TX Single Collisions */
#घोषणा B44_TX_MCOLS	0x0548UL /* MIB TX Multiple Collisions */
#घोषणा B44_TX_ECOLS	0x054CUL /* MIB TX Excessive Collisions */
#घोषणा B44_TX_LCOLS	0x0550UL /* MIB TX Late Collisions */
#घोषणा B44_TX_DEFERED	0x0554UL /* MIB TX Defered Packets */
#घोषणा B44_TX_CLOST	0x0558UL /* MIB TX Carrier Lost */
#घोषणा B44_TX_PAUSE	0x055CUL /* MIB TX Pause Packets */
#घोषणा B44_RX_GOOD_O	0x0580UL /* MIB RX Good Octets */
#घोषणा B44_RX_GOOD_P	0x0584UL /* MIB RX Good Packets */
#घोषणा B44_RX_O	0x0588UL /* MIB RX Octets */
#घोषणा B44_RX_P	0x058CUL /* MIB RX Packets */
#घोषणा B44_RX_BCAST	0x0590UL /* MIB RX Broadcast Packets */
#घोषणा B44_RX_MCAST	0x0594UL /* MIB RX Multicast Packets */
#घोषणा B44_RX_64	0x0598UL /* MIB RX <= 64 byte Packets */
#घोषणा B44_RX_65_127	0x059CUL /* MIB RX 65 to 127 byte Packets */
#घोषणा B44_RX_128_255	0x05A0UL /* MIB RX 128 to 255 byte Packets */
#घोषणा B44_RX_256_511	0x05A4UL /* MIB RX 256 to 511 byte Packets */
#घोषणा B44_RX_512_1023	0x05A8UL /* MIB RX 512 to 1023 byte Packets */
#घोषणा B44_RX_1024_MAX	0x05ACUL /* MIB RX 1024 to max byte Packets */
#घोषणा B44_RX_JABBER	0x05B0UL /* MIB RX Jabber Packets */
#घोषणा B44_RX_OSIZE	0x05B4UL /* MIB RX Oversize Packets */
#घोषणा B44_RX_FRAG	0x05B8UL /* MIB RX Fragment Packets */
#घोषणा B44_RX_MISS	0x05BCUL /* MIB RX Missed Packets */
#घोषणा B44_RX_CRCA	0x05C0UL /* MIB RX CRC Align Errors */
#घोषणा B44_RX_USIZE	0x05C4UL /* MIB RX Undersize Packets */
#घोषणा B44_RX_CRC	0x05C8UL /* MIB RX CRC Errors */
#घोषणा B44_RX_ALIGN	0x05CCUL /* MIB RX Align Errors */
#घोषणा B44_RX_SYM	0x05D0UL /* MIB RX Symbol Errors */
#घोषणा B44_RX_PAUSE	0x05D4UL /* MIB RX Pause Packets */
#घोषणा B44_RX_NPAUSE	0x05D8UL /* MIB RX Non-Pause Packets */

/* 4400 PHY रेजिस्टरs */
#घोषणा B44_MII_AUXCTRL		24	/* Auxiliary Control */
#घोषणा  MII_AUXCTRL_DUPLEX	0x0001  /* Full Duplex */
#घोषणा  MII_AUXCTRL_SPEED	0x0002  /* 1=100Mbps, 0=10Mbps */
#घोषणा  MII_AUXCTRL_FORCED	0x0004	/* Forced 10/100 */
#घोषणा B44_MII_ALEDCTRL	26	/* Activity LED */
#घोषणा  MII_ALEDCTRL_ALLMSK	0x7fff
#घोषणा B44_MII_TLEDCTRL	27	/* Traffic Meter LED */
#घोषणा  MII_TLEDCTRL_ENABLE	0x0040

काष्ठा dma_desc अणु
	__le32	ctrl;
	__le32	addr;
पूर्ण;

/* There are only 12 bits in the DMA engine क्रम descriptor offsetting
 * so the table must be aligned on a boundary of this.
 */
#घोषणा DMA_TABLE_BYTES		4096

#घोषणा DESC_CTRL_LEN	0x00001fff
#घोषणा DESC_CTRL_CMASK	0x0ff00000 /* Core specअगरic bits */
#घोषणा DESC_CTRL_EOT	0x10000000 /* End of Table */
#घोषणा DESC_CTRL_IOC	0x20000000 /* Interrupt On Completion */
#घोषणा DESC_CTRL_खातापूर्ण	0x40000000 /* End of Frame */
#घोषणा DESC_CTRL_SOF	0x80000000 /* Start of Frame */

#घोषणा RX_COPY_THRESHOLD  	256

काष्ठा rx_header अणु
	__le16	len;
	__le16	flags;
	__le16	pad[12];
पूर्ण;
#घोषणा RX_HEADER_LEN	28

#घोषणा RX_FLAG_OFIFO	0x00000001 /* FIFO Overflow */
#घोषणा RX_FLAG_CRCERR	0x00000002 /* CRC Error */
#घोषणा RX_FLAG_SERR	0x00000004 /* Receive Symbol Error */
#घोषणा RX_FLAG_ODD	0x00000008 /* Frame has odd number of nibbles */
#घोषणा RX_FLAG_LARGE	0x00000010 /* Frame is > RX MAX Length */
#घोषणा RX_FLAG_MCAST	0x00000020 /* Dest is Multicast Address */
#घोषणा RX_FLAG_BCAST	0x00000040 /* Dest is Broadcast Address */
#घोषणा RX_FLAG_MISS	0x00000080 /* Received due to promisc mode */
#घोषणा RX_FLAG_LAST	0x00000800 /* Last buffer in frame */
#घोषणा RX_FLAG_ERRORS	(RX_FLAG_ODD | RX_FLAG_SERR | RX_FLAG_CRCERR | RX_FLAG_OFIFO)

काष्ठा ring_info अणु
	काष्ठा sk_buff		*skb;
	dma_addr_t	mapping;
पूर्ण;

#घोषणा B44_MCAST_TABLE_SIZE		32
/* no local phy regs, e.g: Broadcom चयनes pseuकरो-PHY */
#घोषणा B44_PHY_ADDR_NO_LOCAL_PHY	BRCM_PSEUDO_PHY_ADDR
/* no phy present at all */
#घोषणा B44_PHY_ADDR_NO_PHY		31
#घोषणा B44_MDC_RATIO			5000000

#घोषणा	B44_STAT_REG_DECLARE		\
	_B44(tx_good_octets)		\
	_B44(tx_good_pkts)		\
	_B44(tx_octets)			\
	_B44(tx_pkts)			\
	_B44(tx_broadcast_pkts)		\
	_B44(tx_multicast_pkts)		\
	_B44(tx_len_64)			\
	_B44(tx_len_65_to_127)		\
	_B44(tx_len_128_to_255)		\
	_B44(tx_len_256_to_511)		\
	_B44(tx_len_512_to_1023)	\
	_B44(tx_len_1024_to_max)	\
	_B44(tx_jabber_pkts)		\
	_B44(tx_oversize_pkts)		\
	_B44(tx_fragment_pkts)		\
	_B44(tx_underruns)		\
	_B44(tx_total_cols)		\
	_B44(tx_single_cols)		\
	_B44(tx_multiple_cols)		\
	_B44(tx_excessive_cols)		\
	_B44(tx_late_cols)		\
	_B44(tx_defered)		\
	_B44(tx_carrier_lost)		\
	_B44(tx_छोड़ो_pkts)		\
	_B44(rx_good_octets)		\
	_B44(rx_good_pkts)		\
	_B44(rx_octets)			\
	_B44(rx_pkts)			\
	_B44(rx_broadcast_pkts)		\
	_B44(rx_multicast_pkts)		\
	_B44(rx_len_64)			\
	_B44(rx_len_65_to_127)		\
	_B44(rx_len_128_to_255)		\
	_B44(rx_len_256_to_511)		\
	_B44(rx_len_512_to_1023)	\
	_B44(rx_len_1024_to_max)	\
	_B44(rx_jabber_pkts)		\
	_B44(rx_oversize_pkts)		\
	_B44(rx_fragment_pkts)		\
	_B44(rx_missed_pkts)		\
	_B44(rx_crc_align_errs)		\
	_B44(rx_undersize)		\
	_B44(rx_crc_errs)		\
	_B44(rx_align_errs)		\
	_B44(rx_symbol_errs)		\
	_B44(rx_छोड़ो_pkts)		\
	_B44(rx_nonछोड़ो_pkts)

/* SW copy of device statistics, kept up to date by periodic समयr
 * which probes HW values. Check b44_stats_update अगर you mess with
 * the layout
 */
काष्ठा b44_hw_stats अणु
#घोषणा _B44(x)	u64 x;
B44_STAT_REG_DECLARE
#अघोषित _B44
	काष्ठा u64_stats_sync	syncp;
पूर्ण;

#घोषणा	B44_BOARDFLAG_ROBO		0x0010  /* Board has robo चयन */
#घोषणा	B44_BOARDFLAG_ADM		0x0080  /* Board has ADMtek चयन */

काष्ठा ssb_device;

काष्ठा b44 अणु
	spinlock_t		lock;

	u32			imask, istat;

	काष्ठा dma_desc		*rx_ring, *tx_ring;

	u32			tx_prod, tx_cons;
	u32			rx_prod, rx_cons;

	काष्ठा ring_info	*rx_buffers;
	काष्ठा ring_info	*tx_buffers;

	काष्ठा napi_काष्ठा	napi;

	u32			dma_offset;
	u32			flags;
#घोषणा B44_FLAG_B0_ANDLATER	0x00000001
#घोषणा B44_FLAG_BUGGY_TXPTR	0x00000002
#घोषणा B44_FLAG_REORDER_BUG	0x00000004
#घोषणा B44_FLAG_PAUSE_AUTO	0x00008000
#घोषणा B44_FLAG_FULL_DUPLEX	0x00010000
#घोषणा B44_FLAG_100_BASE_T	0x00020000
#घोषणा B44_FLAG_TX_PAUSE	0x00040000
#घोषणा B44_FLAG_RX_PAUSE	0x00080000
#घोषणा B44_FLAG_FORCE_LINK	0x00100000
#घोषणा B44_FLAG_ADV_10HALF	0x01000000
#घोषणा B44_FLAG_ADV_10FULL	0x02000000
#घोषणा B44_FLAG_ADV_100HALF	0x04000000
#घोषणा B44_FLAG_ADV_100FULL	0x08000000
#घोषणा B44_FLAG_EXTERNAL_PHY	0x10000000
#घोषणा B44_FLAG_RX_RING_HACK	0x20000000
#घोषणा B44_FLAG_TX_RING_HACK	0x40000000
#घोषणा B44_FLAG_WOL_ENABLE	0x80000000

	u32			msg_enable;

	काष्ठा समयr_list	समयr;

	काष्ठा b44_hw_stats	hw_stats;

	काष्ठा ssb_device	*sdev;
	काष्ठा net_device	*dev;

	dma_addr_t		rx_ring_dma, tx_ring_dma;

	u32			rx_pending;
	u32			tx_pending;
	u8			phy_addr;
	u8			क्रमce_copyअवरोध;
	काष्ठा mii_bus		*mii_bus;
	पूर्णांक			old_link;
	काष्ठा mii_अगर_info	mii_अगर;
पूर्ण;

#पूर्ण_अगर /* _B44_H */
