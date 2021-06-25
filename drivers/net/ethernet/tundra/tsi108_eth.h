<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * (C) Copyright 2005 Tundra Semiconductor Corp.
 * Kong Lai, <kong.lai@tundra.com).
 *
 * See file CREDITS क्रम list of people who contributed to this
 * project.
 */

/*
 * net/tsi108_eth.h - definitions क्रम Tsi108 GIGE network controller.
 */

#अगर_अघोषित __TSI108_ETH_H
#घोषणा __TSI108_ETH_H

#समावेश <linux/types.h>

#घोषणा TSI_WRITE(offset, val) \
	out_be32((data->regs + (offset)), val)

#घोषणा TSI_READ(offset) \
	in_be32((data->regs + (offset)))

#घोषणा TSI_WRITE_PHY(offset, val) \
	out_be32((data->phyregs + (offset)), val)

#घोषणा TSI_READ_PHY(offset) \
	in_be32((data->phyregs + (offset)))

/*
 * TSI108 GIGE port रेजिस्टरs
 */

#घोषणा TSI108_ETH_PORT_NUM		2
#घोषणा TSI108_PBM_PORT			2
#घोषणा TSI108_SDRAM_PORT		4

#घोषणा TSI108_MAC_CFG1			(0x000)
#घोषणा TSI108_MAC_CFG1_SOFTRST		(1 << 31)
#घोषणा TSI108_MAC_CFG1_LOOPBACK	(1 << 8)
#घोषणा TSI108_MAC_CFG1_RXEN		(1 << 2)
#घोषणा TSI108_MAC_CFG1_TXEN		(1 << 0)

#घोषणा TSI108_MAC_CFG2			(0x004)
#घोषणा TSI108_MAC_CFG2_DFLT_PREAMBLE	(7 << 12)
#घोषणा TSI108_MAC_CFG2_IFACE_MASK	(3 << 8)
#घोषणा TSI108_MAC_CFG2_NOGIG		(1 << 8)
#घोषणा TSI108_MAC_CFG2_GIG		(2 << 8)
#घोषणा TSI108_MAC_CFG2_PADCRC		(1 << 2)
#घोषणा TSI108_MAC_CFG2_FULLDUPLEX	(1 << 0)

#घोषणा TSI108_MAC_MII_MGMT_CFG		(0x020)
#घोषणा TSI108_MAC_MII_MGMT_CLK		(7 << 0)
#घोषणा TSI108_MAC_MII_MGMT_RST		(1 << 31)

#घोषणा TSI108_MAC_MII_CMD		(0x024)
#घोषणा TSI108_MAC_MII_CMD_READ		(1 << 0)

#घोषणा TSI108_MAC_MII_ADDR		(0x028)
#घोषणा TSI108_MAC_MII_ADDR_REG		0
#घोषणा TSI108_MAC_MII_ADDR_PHY		8

#घोषणा TSI108_MAC_MII_DATAOUT		(0x02c)
#घोषणा TSI108_MAC_MII_DATAIN		(0x030)

#घोषणा TSI108_MAC_MII_IND		(0x034)
#घोषणा TSI108_MAC_MII_IND_NOTVALID	(1 << 2)
#घोषणा TSI108_MAC_MII_IND_SCANNING	(1 << 1)
#घोषणा TSI108_MAC_MII_IND_BUSY		(1 << 0)

#घोषणा TSI108_MAC_IFCTRL		(0x038)
#घोषणा TSI108_MAC_IFCTRL_PHYMODE	(1 << 24)

#घोषणा TSI108_MAC_ADDR1		(0x040)
#घोषणा TSI108_MAC_ADDR2		(0x044)

#घोषणा TSI108_STAT_RXBYTES		(0x06c)
#घोषणा TSI108_STAT_RXBYTES_CARRY	(1 << 24)

#घोषणा TSI108_STAT_RXPKTS		(0x070)
#घोषणा TSI108_STAT_RXPKTS_CARRY	(1 << 18)

#घोषणा TSI108_STAT_RXFCS		(0x074)
#घोषणा TSI108_STAT_RXFCS_CARRY		(1 << 12)

#घोषणा TSI108_STAT_RXMCAST		(0x078)
#घोषणा TSI108_STAT_RXMCAST_CARRY	(1 << 18)

#घोषणा TSI108_STAT_RXALIGN		(0x08c)
#घोषणा TSI108_STAT_RXALIGN_CARRY	(1 << 12)

#घोषणा TSI108_STAT_RXLENGTH		(0x090)
#घोषणा TSI108_STAT_RXLENGTH_CARRY	(1 << 12)

#घोषणा TSI108_STAT_RXRUNT		(0x09c)
#घोषणा TSI108_STAT_RXRUNT_CARRY	(1 << 12)

#घोषणा TSI108_STAT_RXJUMBO		(0x0a0)
#घोषणा TSI108_STAT_RXJUMBO_CARRY	(1 << 12)

#घोषणा TSI108_STAT_RXFRAG		(0x0a4)
#घोषणा TSI108_STAT_RXFRAG_CARRY	(1 << 12)

#घोषणा TSI108_STAT_RXJABBER		(0x0a8)
#घोषणा TSI108_STAT_RXJABBER_CARRY	(1 << 12)

#घोषणा TSI108_STAT_RXDROP		(0x0ac)
#घोषणा TSI108_STAT_RXDROP_CARRY	(1 << 12)

#घोषणा TSI108_STAT_TXBYTES		(0x0b0)
#घोषणा TSI108_STAT_TXBYTES_CARRY	(1 << 24)

#घोषणा TSI108_STAT_TXPKTS		(0x0b4)
#घोषणा TSI108_STAT_TXPKTS_CARRY	(1 << 18)

#घोषणा TSI108_STAT_TXEXDEF		(0x0c8)
#घोषणा TSI108_STAT_TXEXDEF_CARRY	(1 << 12)

#घोषणा TSI108_STAT_TXEXCOL		(0x0d8)
#घोषणा TSI108_STAT_TXEXCOL_CARRY	(1 << 12)

#घोषणा TSI108_STAT_TXTCOL		(0x0dc)
#घोषणा TSI108_STAT_TXTCOL_CARRY	(1 << 13)

#घोषणा TSI108_STAT_TXPAUSEDROP		(0x0e4)
#घोषणा TSI108_STAT_TXPAUSEDROP_CARRY	(1 << 12)

#घोषणा TSI108_STAT_CARRY1		(0x100)
#घोषणा TSI108_STAT_CARRY1_RXBYTES	(1 << 16)
#घोषणा TSI108_STAT_CARRY1_RXPKTS	(1 << 15)
#घोषणा TSI108_STAT_CARRY1_RXFCS	(1 << 14)
#घोषणा TSI108_STAT_CARRY1_RXMCAST	(1 << 13)
#घोषणा TSI108_STAT_CARRY1_RXALIGN	(1 << 8)
#घोषणा TSI108_STAT_CARRY1_RXLENGTH	(1 << 7)
#घोषणा TSI108_STAT_CARRY1_RXRUNT	(1 << 4)
#घोषणा TSI108_STAT_CARRY1_RXJUMBO	(1 << 3)
#घोषणा TSI108_STAT_CARRY1_RXFRAG	(1 << 2)
#घोषणा TSI108_STAT_CARRY1_RXJABBER	(1 << 1)
#घोषणा TSI108_STAT_CARRY1_RXDROP	(1 << 0)

#घोषणा TSI108_STAT_CARRY2		(0x104)
#घोषणा TSI108_STAT_CARRY2_TXBYTES	(1 << 13)
#घोषणा TSI108_STAT_CARRY2_TXPKTS	(1 << 12)
#घोषणा TSI108_STAT_CARRY2_TXEXDEF	(1 << 7)
#घोषणा TSI108_STAT_CARRY2_TXEXCOL	(1 << 3)
#घोषणा TSI108_STAT_CARRY2_TXTCOL	(1 << 2)
#घोषणा TSI108_STAT_CARRY2_TXPAUSE	(1 << 0)

#घोषणा TSI108_STAT_CARRYMASK1		(0x108)
#घोषणा TSI108_STAT_CARRYMASK2		(0x10c)

#घोषणा TSI108_EC_PORTCTRL		(0x200)
#घोषणा TSI108_EC_PORTCTRL_STATRST	(1 << 31)
#घोषणा TSI108_EC_PORTCTRL_STATEN	(1 << 28)
#घोषणा TSI108_EC_PORTCTRL_NOGIG	(1 << 18)
#घोषणा TSI108_EC_PORTCTRL_HALFDUPLEX	(1 << 16)

#घोषणा TSI108_EC_INTSTAT		(0x204)
#घोषणा TSI108_EC_INTMASK		(0x208)

#घोषणा TSI108_INT_ANY			(1 << 31)
#घोषणा TSI108_INT_SFN			(1 << 30)
#घोषणा TSI108_INT_RXIDLE		(1 << 29)
#घोषणा TSI108_INT_RXABORT		(1 << 28)
#घोषणा TSI108_INT_RXERROR		(1 << 27)
#घोषणा TSI108_INT_RXOVERRUN		(1 << 26)
#घोषणा TSI108_INT_RXTHRESH		(1 << 25)
#घोषणा TSI108_INT_RXWAIT		(1 << 24)
#घोषणा TSI108_INT_RXQUEUE0		(1 << 16)
#घोषणा TSI108_INT_STATCARRY		(1 << 15)
#घोषणा TSI108_INT_TXIDLE		(1 << 13)
#घोषणा TSI108_INT_TXABORT		(1 << 12)
#घोषणा TSI108_INT_TXERROR		(1 << 11)
#घोषणा TSI108_INT_TXUNDERRUN		(1 << 10)
#घोषणा TSI108_INT_TXTHRESH		(1 <<  9)
#घोषणा TSI108_INT_TXWAIT		(1 <<  8)
#घोषणा TSI108_INT_TXQUEUE0		(1 <<  0)

#घोषणा TSI108_EC_TXCFG			(0x220)
#घोषणा TSI108_EC_TXCFG_RST		(1 << 31)

#घोषणा TSI108_EC_TXCTRL		(0x224)
#घोषणा TSI108_EC_TXCTRL_IDLEINT	(1 << 31)
#घोषणा TSI108_EC_TXCTRL_ABORT		(1 << 30)
#घोषणा TSI108_EC_TXCTRL_GO		(1 << 15)
#घोषणा TSI108_EC_TXCTRL_QUEUE0		(1 <<  0)

#घोषणा TSI108_EC_TXSTAT		(0x228)
#घोषणा TSI108_EC_TXSTAT_ACTIVE		(1 << 15)
#घोषणा TSI108_EC_TXSTAT_QUEUE0		(1 << 0)

#घोषणा TSI108_EC_TXESTAT		(0x22c)
#घोषणा TSI108_EC_TXESTAT_Q0_ERR	(1 << 24)
#घोषणा TSI108_EC_TXESTAT_Q0_DESCINT	(1 << 16)
#घोषणा TSI108_EC_TXESTAT_Q0_खातापूर्ण	(1 <<  8)
#घोषणा TSI108_EC_TXESTAT_Q0_EOQ	(1 <<  0)

#घोषणा TSI108_EC_TXERR			(0x278)

#घोषणा TSI108_EC_TXQ_CFG		(0x280)
#घोषणा TSI108_EC_TXQ_CFG_DESC_INT	(1 << 20)
#घोषणा TSI108_EC_TXQ_CFG_EOQ_OWN_INT	(1 << 19)
#घोषणा TSI108_EC_TXQ_CFG_WSWP		(1 << 11)
#घोषणा TSI108_EC_TXQ_CFG_BSWP		(1 << 10)
#घोषणा TSI108_EC_TXQ_CFG_SFNPORT	0

#घोषणा TSI108_EC_TXQ_BUFCFG		(0x284)
#घोषणा TSI108_EC_TXQ_BUFCFG_BURST8	(0 << 8)
#घोषणा TSI108_EC_TXQ_BUFCFG_BURST32	(1 << 8)
#घोषणा TSI108_EC_TXQ_BUFCFG_BURST128	(2 << 8)
#घोषणा TSI108_EC_TXQ_BUFCFG_BURST256	(3 << 8)
#घोषणा TSI108_EC_TXQ_BUFCFG_WSWP	(1 << 11)
#घोषणा TSI108_EC_TXQ_BUFCFG_BSWP	(1 << 10)
#घोषणा TSI108_EC_TXQ_BUFCFG_SFNPORT	0

#घोषणा TSI108_EC_TXQ_PTRLOW		(0x288)

#घोषणा TSI108_EC_TXQ_PTRHIGH		(0x28c)
#घोषणा TSI108_EC_TXQ_PTRHIGH_VALID	(1 << 31)

#घोषणा TSI108_EC_TXTHRESH		(0x230)
#घोषणा TSI108_EC_TXTHRESH_STARTFILL	0
#घोषणा TSI108_EC_TXTHRESH_STOPFILL	16

#घोषणा TSI108_EC_RXCFG			(0x320)
#घोषणा TSI108_EC_RXCFG_RST		(1 << 31)

#घोषणा TSI108_EC_RXSTAT		(0x328)
#घोषणा TSI108_EC_RXSTAT_ACTIVE		(1 << 15)
#घोषणा TSI108_EC_RXSTAT_QUEUE0		(1 << 0)

#घोषणा TSI108_EC_RXESTAT		(0x32c)
#घोषणा TSI108_EC_RXESTAT_Q0_ERR	(1 << 24)
#घोषणा TSI108_EC_RXESTAT_Q0_DESCINT	(1 << 16)
#घोषणा TSI108_EC_RXESTAT_Q0_खातापूर्ण	(1 <<  8)
#घोषणा TSI108_EC_RXESTAT_Q0_EOQ	(1 <<  0)

#घोषणा TSI108_EC_HASHADDR		(0x360)
#घोषणा TSI108_EC_HASHADDR_AUTOINC	(1 << 31)
#घोषणा TSI108_EC_HASHADDR_DO1STREAD	(1 << 30)
#घोषणा TSI108_EC_HASHADDR_UNICAST	(0 <<  4)
#घोषणा TSI108_EC_HASHADDR_MCAST	(1 <<  4)

#घोषणा TSI108_EC_HASHDATA		(0x364)

#घोषणा TSI108_EC_RXQ_PTRLOW		(0x388)

#घोषणा TSI108_EC_RXQ_PTRHIGH		(0x38c)
#घोषणा TSI108_EC_RXQ_PTRHIGH_VALID	(1 << 31)

/* Station Enable -- accept packets destined क्रम us */
#घोषणा TSI108_EC_RXCFG_SE		(1 << 13)
/* Unicast Frame Enable -- क्रम packets not destined क्रम us */
#घोषणा TSI108_EC_RXCFG_UFE		(1 << 12)
/* Multicast Frame Enable */
#घोषणा TSI108_EC_RXCFG_MFE		(1 << 11)
/* Broadcast Frame Enable */
#घोषणा TSI108_EC_RXCFG_BFE		(1 << 10)
#घोषणा TSI108_EC_RXCFG_UC_HASH		(1 <<  9)
#घोषणा TSI108_EC_RXCFG_MC_HASH		(1 <<  8)

#घोषणा TSI108_EC_RXQ_CFG		(0x380)
#घोषणा TSI108_EC_RXQ_CFG_DESC_INT	(1 << 20)
#घोषणा TSI108_EC_RXQ_CFG_EOQ_OWN_INT	(1 << 19)
#घोषणा TSI108_EC_RXQ_CFG_WSWP		(1 << 11)
#घोषणा TSI108_EC_RXQ_CFG_BSWP		(1 << 10)
#घोषणा TSI108_EC_RXQ_CFG_SFNPORT	0

#घोषणा TSI108_EC_RXQ_BUFCFG		(0x384)
#घोषणा TSI108_EC_RXQ_BUFCFG_BURST8	(0 << 8)
#घोषणा TSI108_EC_RXQ_BUFCFG_BURST32	(1 << 8)
#घोषणा TSI108_EC_RXQ_BUFCFG_BURST128	(2 << 8)
#घोषणा TSI108_EC_RXQ_BUFCFG_BURST256	(3 << 8)
#घोषणा TSI108_EC_RXQ_BUFCFG_WSWP	(1 << 11)
#घोषणा TSI108_EC_RXQ_BUFCFG_BSWP	(1 << 10)
#घोषणा TSI108_EC_RXQ_BUFCFG_SFNPORT	0

#घोषणा TSI108_EC_RXCTRL		(0x324)
#घोषणा TSI108_EC_RXCTRL_ABORT		(1 << 30)
#घोषणा TSI108_EC_RXCTRL_GO		(1 << 15)
#घोषणा TSI108_EC_RXCTRL_QUEUE0		(1 << 0)

#घोषणा TSI108_EC_RXERR			(0x378)

#घोषणा TSI108_TX_खातापूर्ण	(1 << 0)	/* End of frame; last fragment of packet */
#घोषणा TSI108_TX_SOF	(1 << 1)	/* Start of frame; first frag. of packet */
#घोषणा TSI108_TX_VLAN	(1 << 2)	/* Per-frame VLAN: enables VLAN override */
#घोषणा TSI108_TX_HUGE	(1 << 3)	/* Huge frame enable */
#घोषणा TSI108_TX_PAD	(1 << 4)	/* Pad the packet अगर too लघु */
#घोषणा TSI108_TX_CRC	(1 << 5)	/* Generate CRC क्रम this packet */
#घोषणा TSI108_TX_INT	(1 << 14)	/* Generate an IRQ after frag. processed */
#घोषणा TSI108_TX_RETRY	(0xf << 16)	/* 4 bit field indicating num. of retries */
#घोषणा TSI108_TX_COL	(1 << 20)	/* Set अगर a collision occurred */
#घोषणा TSI108_TX_LCOL	(1 << 24)	/* Set अगर a late collision occurred */
#घोषणा TSI108_TX_UNDER	(1 << 25)	/* Set अगर a FIFO underrun occurred */
#घोषणा TSI108_TX_RLIM	(1 << 26)	/* Set अगर the retry limit was reached */
#घोषणा TSI108_TX_OK	(1 << 30)	/* Set अगर the frame TX was successful */
#घोषणा TSI108_TX_OWN	(1 << 31)	/* Set अगर the device owns the descriptor */

/* Note: the descriptor layouts assume big-endian byte order. */
प्रकार काष्ठा अणु
	u32 buf0;
	u32 buf1;		/* Base address of buffer */
	u32 next0;		/* Address of next descriptor, अगर any */
	u32 next1;
	u16 vlan;		/* VLAN, अगर override enabled क्रम this packet */
	u16 len;		/* Length of buffer in bytes */
	u32 misc;		/* See TSI108_TX_* above */
	u32 reserved0;		/*reserved0 and reserved1 are added to make the desc */
	u32 reserved1;		/* 32-byte aligned */
पूर्ण __attribute__ ((aligned(32))) tx_desc;

#घोषणा TSI108_RX_खातापूर्ण	(1 << 0)	/* End of frame; last fragment of packet */
#घोषणा TSI108_RX_SOF	(1 << 1)	/* Start of frame; first frag. of packet */
#घोषणा TSI108_RX_VLAN	(1 << 2)	/* Set on SOF अगर packet has a VLAN */
#घोषणा TSI108_RX_FTYPE	(1 << 3)	/* Length/Type field is type, not length */
#घोषणा TSI108_RX_RUNT	(1 << 4)/* Packet is less than minimum size */
#घोषणा TSI108_RX_HASH	(1 << 7)/* Hash table match */
#घोषणा TSI108_RX_BAD	(1 << 8)	/* Bad frame */
#घोषणा TSI108_RX_OVER	(1 << 9)	/* FIFO overrun occurred */
#घोषणा TSI108_RX_TRUNC	(1 << 11)	/* Packet truncated due to excess length */
#घोषणा TSI108_RX_CRC	(1 << 12)	/* Packet had a CRC error */
#घोषणा TSI108_RX_INT	(1 << 13)	/* Generate an IRQ after frag. processed */
#घोषणा TSI108_RX_OWN	(1 << 15)	/* Set अगर the device owns the descriptor */

#घोषणा TSI108_RX_SKB_SIZE 1536		/* The RX skb length */

प्रकार काष्ठा अणु
	u32 buf0;		/* Base address of buffer */
	u32 buf1;		/* Base address of buffer */
	u32 next0;		/* Address of next descriptor, अगर any */
	u32 next1;		/* Address of next descriptor, अगर any */
	u16 vlan;		/* VLAN of received packet, first frag only */
	u16 len;		/* Length of received fragment in bytes */
	u16 blen;		/* Length of buffer in bytes */
	u16 misc;		/* See TSI108_RX_* above */
	u32 reserved0;		/* reserved0 and reserved1 are added to make the desc */
	u32 reserved1;		/* 32-byte aligned */
पूर्ण __attribute__ ((aligned(32))) rx_desc;

#पूर्ण_अगर				/* __TSI108_ETH_H */
