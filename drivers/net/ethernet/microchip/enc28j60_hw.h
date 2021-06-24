<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * enc28j60_hw.h: EDTP FrameThrower style enc28j60 रेजिस्टरs
 *
 * $Id: enc28j60_hw.h,v 1.9 2007/12/14 11:59:16 claudio Exp $
 */

#अगर_अघोषित _ENC28J60_HW_H
#घोषणा _ENC28J60_HW_H

/*
 * ENC28J60 Control Registers
 * Control रेजिस्टर definitions are a combination of address,
 * bank number, and Ethernet/MAC/PHY indicator bits.
 * - Register address	(bits 0-4)
 * - Bank number	(bits 5-6)
 * - MAC/MII indicator	(bit 7)
 */
#घोषणा ADDR_MASK	0x1F
#घोषणा BANK_MASK	0x60
#घोषणा SPRD_MASK	0x80
/* All-bank रेजिस्टरs */
#घोषणा EIE		0x1B
#घोषणा EIR		0x1C
#घोषणा ESTAT		0x1D
#घोषणा ECON2		0x1E
#घोषणा ECON1		0x1F
/* Bank 0 रेजिस्टरs */
#घोषणा ERDPTL		(0x00|0x00)
#घोषणा ERDPTH		(0x01|0x00)
#घोषणा EWRPTL		(0x02|0x00)
#घोषणा EWRPTH		(0x03|0x00)
#घोषणा ETXSTL		(0x04|0x00)
#घोषणा ETXSTH		(0x05|0x00)
#घोषणा ETXNDL		(0x06|0x00)
#घोषणा ETXNDH		(0x07|0x00)
#घोषणा ERXSTL		(0x08|0x00)
#घोषणा ERXSTH		(0x09|0x00)
#घोषणा ERXNDL		(0x0A|0x00)
#घोषणा ERXNDH		(0x0B|0x00)
#घोषणा ERXRDPTL	(0x0C|0x00)
#घोषणा ERXRDPTH	(0x0D|0x00)
#घोषणा ERXWRPTL	(0x0E|0x00)
#घोषणा ERXWRPTH	(0x0F|0x00)
#घोषणा EDMASTL		(0x10|0x00)
#घोषणा EDMASTH		(0x11|0x00)
#घोषणा EDMANDL		(0x12|0x00)
#घोषणा EDMANDH		(0x13|0x00)
#घोषणा EDMADSTL	(0x14|0x00)
#घोषणा EDMADSTH	(0x15|0x00)
#घोषणा EDMACSL		(0x16|0x00)
#घोषणा EDMACSH		(0x17|0x00)
/* Bank 1 रेजिस्टरs */
#घोषणा EHT0		(0x00|0x20)
#घोषणा EHT1		(0x01|0x20)
#घोषणा EHT2		(0x02|0x20)
#घोषणा EHT3		(0x03|0x20)
#घोषणा EHT4		(0x04|0x20)
#घोषणा EHT5		(0x05|0x20)
#घोषणा EHT6		(0x06|0x20)
#घोषणा EHT7		(0x07|0x20)
#घोषणा EPMM0		(0x08|0x20)
#घोषणा EPMM1		(0x09|0x20)
#घोषणा EPMM2		(0x0A|0x20)
#घोषणा EPMM3		(0x0B|0x20)
#घोषणा EPMM4		(0x0C|0x20)
#घोषणा EPMM5		(0x0D|0x20)
#घोषणा EPMM6		(0x0E|0x20)
#घोषणा EPMM7		(0x0F|0x20)
#घोषणा EPMCSL		(0x10|0x20)
#घोषणा EPMCSH		(0x11|0x20)
#घोषणा EPMOL		(0x14|0x20)
#घोषणा EPMOH		(0x15|0x20)
#घोषणा EWOLIE		(0x16|0x20)
#घोषणा EWOLIR		(0x17|0x20)
#घोषणा ERXFCON		(0x18|0x20)
#घोषणा EPKTCNT		(0x19|0x20)
/* Bank 2 रेजिस्टरs */
#घोषणा MACON1		(0x00|0x40|SPRD_MASK)
/* #घोषणा MACON2	(0x01|0x40|SPRD_MASK) */
#घोषणा MACON3		(0x02|0x40|SPRD_MASK)
#घोषणा MACON4		(0x03|0x40|SPRD_MASK)
#घोषणा MABBIPG		(0x04|0x40|SPRD_MASK)
#घोषणा MAIPGL		(0x06|0x40|SPRD_MASK)
#घोषणा MAIPGH		(0x07|0x40|SPRD_MASK)
#घोषणा MACLCON1	(0x08|0x40|SPRD_MASK)
#घोषणा MACLCON2	(0x09|0x40|SPRD_MASK)
#घोषणा MAMXFLL		(0x0A|0x40|SPRD_MASK)
#घोषणा MAMXFLH		(0x0B|0x40|SPRD_MASK)
#घोषणा MAPHSUP		(0x0D|0x40|SPRD_MASK)
#घोषणा MICON		(0x11|0x40|SPRD_MASK)
#घोषणा MICMD		(0x12|0x40|SPRD_MASK)
#घोषणा MIREGADR	(0x14|0x40|SPRD_MASK)
#घोषणा MIWRL		(0x16|0x40|SPRD_MASK)
#घोषणा MIWRH		(0x17|0x40|SPRD_MASK)
#घोषणा MIRDL		(0x18|0x40|SPRD_MASK)
#घोषणा MIRDH		(0x19|0x40|SPRD_MASK)
/* Bank 3 रेजिस्टरs */
#घोषणा MAADR1		(0x00|0x60|SPRD_MASK)
#घोषणा MAADR0		(0x01|0x60|SPRD_MASK)
#घोषणा MAADR3		(0x02|0x60|SPRD_MASK)
#घोषणा MAADR2		(0x03|0x60|SPRD_MASK)
#घोषणा MAADR5		(0x04|0x60|SPRD_MASK)
#घोषणा MAADR4		(0x05|0x60|SPRD_MASK)
#घोषणा EBSTSD		(0x06|0x60)
#घोषणा EBSTCON		(0x07|0x60)
#घोषणा EBSTCSL		(0x08|0x60)
#घोषणा EBSTCSH		(0x09|0x60)
#घोषणा MISTAT		(0x0A|0x60|SPRD_MASK)
#घोषणा EREVID		(0x12|0x60)
#घोषणा ECOCON		(0x15|0x60)
#घोषणा EFLOCON		(0x17|0x60)
#घोषणा EPAUSL		(0x18|0x60)
#घोषणा EPAUSH		(0x19|0x60)
/* PHY रेजिस्टरs */
#घोषणा PHCON1		0x00
#घोषणा PHSTAT1		0x01
#घोषणा PHHID1		0x02
#घोषणा PHHID2		0x03
#घोषणा PHCON2		0x10
#घोषणा PHSTAT2		0x11
#घोषणा PHIE		0x12
#घोषणा PHIR		0x13
#घोषणा PHLCON		0x14

/* ENC28J60 EIE Register Bit Definitions */
#घोषणा EIE_INTIE	0x80
#घोषणा EIE_PKTIE	0x40
#घोषणा EIE_DMAIE	0x20
#घोषणा EIE_LINKIE	0x10
#घोषणा EIE_TXIE	0x08
/* #घोषणा EIE_WOLIE	0x04 (reserved) */
#घोषणा EIE_TXERIE	0x02
#घोषणा EIE_RXERIE	0x01
/* ENC28J60 EIR Register Bit Definitions */
#घोषणा EIR_PKTIF	0x40
#घोषणा EIR_DMAIF	0x20
#घोषणा EIR_LINKIF	0x10
#घोषणा EIR_TXIF	0x08
/* #घोषणा EIR_WOLIF	0x04 (reserved) */
#घोषणा EIR_TXERIF	0x02
#घोषणा EIR_RXERIF	0x01
/* ENC28J60 ESTAT Register Bit Definitions */
#घोषणा ESTAT_INT	0x80
#घोषणा ESTAT_LATECOL	0x10
#घोषणा ESTAT_RXBUSY	0x04
#घोषणा ESTAT_TXABRT	0x02
#घोषणा ESTAT_CLKRDY	0x01
/* ENC28J60 ECON2 Register Bit Definitions */
#घोषणा ECON2_AUTOINC	0x80
#घोषणा ECON2_PKTDEC	0x40
#घोषणा ECON2_PWRSV	0x20
#घोषणा ECON2_VRPS	0x08
/* ENC28J60 ECON1 Register Bit Definitions */
#घोषणा ECON1_TXRST	0x80
#घोषणा ECON1_RXRST	0x40
#घोषणा ECON1_DMAST	0x20
#घोषणा ECON1_CSUMEN	0x10
#घोषणा ECON1_TXRTS	0x08
#घोषणा ECON1_RXEN	0x04
#घोषणा ECON1_BSEL1	0x02
#घोषणा ECON1_BSEL0	0x01
/* ENC28J60 MACON1 Register Bit Definitions */
#घोषणा MACON1_LOOPBK	0x10
#घोषणा MACON1_TXPAUS	0x08
#घोषणा MACON1_RXPAUS	0x04
#घोषणा MACON1_PASSALL	0x02
#घोषणा MACON1_MARXEN	0x01
/* ENC28J60 MACON2 Register Bit Definitions */
#घोषणा MACON2_MARST	0x80
#घोषणा MACON2_RNDRST	0x40
#घोषणा MACON2_MARXRST	0x08
#घोषणा MACON2_RFUNRST	0x04
#घोषणा MACON2_MATXRST	0x02
#घोषणा MACON2_TFUNRST	0x01
/* ENC28J60 MACON3 Register Bit Definitions */
#घोषणा MACON3_PADCFG2	0x80
#घोषणा MACON3_PADCFG1	0x40
#घोषणा MACON3_PADCFG0	0x20
#घोषणा MACON3_TXCRCEN	0x10
#घोषणा MACON3_PHDRLEN	0x08
#घोषणा MACON3_HFRMLEN	0x04
#घोषणा MACON3_FRMLNEN	0x02
#घोषणा MACON3_FULDPX	0x01
/* ENC28J60 MICMD Register Bit Definitions */
#घोषणा MICMD_MIISCAN	0x02
#घोषणा MICMD_MIIRD	0x01
/* ENC28J60 MISTAT Register Bit Definitions */
#घोषणा MISTAT_NVALID	0x04
#घोषणा MISTAT_SCAN	0x02
#घोषणा MISTAT_BUSY	0x01
/* ENC28J60 ERXFCON Register Bit Definitions */
#घोषणा ERXFCON_UCEN	0x80
#घोषणा ERXFCON_ANDOR	0x40
#घोषणा ERXFCON_CRCEN	0x20
#घोषणा ERXFCON_PMEN	0x10
#घोषणा ERXFCON_MPEN	0x08
#घोषणा ERXFCON_HTEN	0x04
#घोषणा ERXFCON_MCEN	0x02
#घोषणा ERXFCON_BCEN	0x01

/* ENC28J60 PHY PHCON1 Register Bit Definitions */
#घोषणा PHCON1_PRST	0x8000
#घोषणा PHCON1_PLOOPBK	0x4000
#घोषणा PHCON1_PPWRSV	0x0800
#घोषणा PHCON1_PDPXMD	0x0100
/* ENC28J60 PHY PHSTAT1 Register Bit Definitions */
#घोषणा PHSTAT1_PFDPX	0x1000
#घोषणा PHSTAT1_PHDPX	0x0800
#घोषणा PHSTAT1_LLSTAT	0x0004
#घोषणा PHSTAT1_JBSTAT	0x0002
/* ENC28J60 PHY PHSTAT2 Register Bit Definitions */
#घोषणा PHSTAT2_TXSTAT	(1 << 13)
#घोषणा PHSTAT2_RXSTAT	(1 << 12)
#घोषणा PHSTAT2_COLSTAT	(1 << 11)
#घोषणा PHSTAT2_LSTAT	(1 << 10)
#घोषणा PHSTAT2_DPXSTAT	(1 << 9)
#घोषणा PHSTAT2_PLRITY	(1 << 5)
/* ENC28J60 PHY PHCON2 Register Bit Definitions */
#घोषणा PHCON2_FRCLINK	0x4000
#घोषणा PHCON2_TXDIS	0x2000
#घोषणा PHCON2_JABBER	0x0400
#घोषणा PHCON2_HDLDIS	0x0100
/* ENC28J60 PHY PHIE Register Bit Definitions */
#घोषणा PHIE_PLNKIE	(1 << 4)
#घोषणा PHIE_PGEIE	(1 << 1)
/* ENC28J60 PHY PHIR Register Bit Definitions */
#घोषणा PHIR_PLNKIF	(1 << 4)
#घोषणा PHIR_PGEIF	(1 << 1)

/* ENC28J60 Packet Control Byte Bit Definitions */
#घोषणा PKTCTRL_PHUGEEN		0x08
#घोषणा PKTCTRL_PPADEN		0x04
#घोषणा PKTCTRL_PCRCEN		0x02
#घोषणा PKTCTRL_POVERRIDE	0x01

/* ENC28J60 Transmit Status Vector */
#घोषणा TSV_TXBYTECNT		0
#घोषणा TSV_TXCOLLISIONCNT	16
#घोषणा TSV_TXCRCERROR		20
#घोषणा TSV_TXLENCHKERROR	21
#घोषणा TSV_TXLENOUTOFRANGE	22
#घोषणा TSV_TXDONE		23
#घोषणा TSV_TXMULTICAST		24
#घोषणा TSV_TXBROADCAST		25
#घोषणा TSV_TXPACKETDEFER	26
#घोषणा TSV_TXEXDEFER		27
#घोषणा TSV_TXEXCOLLISION	28
#घोषणा TSV_TXLATECOLLISION	29
#घोषणा TSV_TXGIANT		30
#घोषणा TSV_TXUNDERRUN		31
#घोषणा TSV_TOTBYTETXONWIRE	32
#घोषणा TSV_TXCONTROLFRAME	48
#घोषणा TSV_TXPAUSEFRAME	49
#घोषणा TSV_BACKPRESSUREAPP	50
#घोषणा TSV_TXVLANTAGFRAME	51

#घोषणा TSV_SIZE		7
#घोषणा TSV_BYTखातापूर्ण(x)		((x) / 8)
#घोषणा TSV_BITMASK(x)		(1 << ((x) % 8))
#घोषणा TSV_GETBIT(x, y)	(((x)[TSV_BYTखातापूर्ण(y)] & TSV_BITMASK(y)) ? 1 : 0)

/* ENC28J60 Receive Status Vector */
#घोषणा RSV_RXLONGEVDROPEV	16
#घोषणा RSV_CARRIEREV		18
#घोषणा RSV_CRCERROR		20
#घोषणा RSV_LENCHECKERR		21
#घोषणा RSV_LENOUTOFRANGE	22
#घोषणा RSV_RXOK		23
#घोषणा RSV_RXMULTICAST		24
#घोषणा RSV_RXBROADCAST		25
#घोषणा RSV_DRIBBLENIBBLE	26
#घोषणा RSV_RXCONTROLFRAME	27
#घोषणा RSV_RXPAUSEFRAME	28
#घोषणा RSV_RXUNKNOWNOPCODE	29
#घोषणा RSV_RXTYPEVLAN		30

#घोषणा RSV_SIZE		6
#घोषणा RSV_BITMASK(x)		(1 << ((x) - 16))
#घोषणा RSV_GETBIT(x, y)	(((x) & RSV_BITMASK(y)) ? 1 : 0)


/* SPI operation codes */
#घोषणा ENC28J60_READ_CTRL_REG	0x00
#घोषणा ENC28J60_READ_BUF_MEM	0x3A
#घोषणा ENC28J60_WRITE_CTRL_REG 0x40
#घोषणा ENC28J60_WRITE_BUF_MEM	0x7A
#घोषणा ENC28J60_BIT_FIELD_SET	0x80
#घोषणा ENC28J60_BIT_FIELD_CLR	0xA0
#घोषणा ENC28J60_SOFT_RESET	0xFF


/* buffer boundaries applied to पूर्णांकernal 8K ram
 * entire available packet buffer space is allocated.
 * Give TX buffer space क्रम one full ethernet frame (~1500 bytes)
 * receive buffer माला_लो the rest */
#घोषणा TXSTART_INIT		0x1A00
#घोषणा TXEND_INIT		0x1FFF

/* Put RX buffer at 0 as suggested by the Errata datasheet */
#घोषणा RXSTART_INIT		0x0000
#घोषणा RXEND_INIT		0x19FF

/* maximum ethernet frame length */
#घोषणा MAX_FRAMELEN		1518

/* Preferred half duplex: LEDA: Link status LEDB: Rx/Tx activity */
#घोषणा ENC28J60_LAMPS_MODE	0x3476

#पूर्ण_अगर
