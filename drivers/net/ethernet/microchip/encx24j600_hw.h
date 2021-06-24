<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * encx24j600_hw.h: Register definitions
 *
 */

#अगर_अघोषित _ENCX24J600_HW_H
#घोषणा _ENCX24J600_HW_H

काष्ठा encx24j600_context अणु
	काष्ठा spi_device *spi;
	काष्ठा regmap *regmap;
	काष्ठा regmap *phymap;
	काष्ठा mutex mutex; /* mutex to protect access to regmap */
	पूर्णांक bank;
पूर्ण;

व्योम devm_regmap_init_encx24j600(काष्ठा device *dev,
				 काष्ठा encx24j600_context *ctx);

/* Single-byte inकाष्ठाions */
#घोषणा BANK_SELECT(bank) (0xC0 | ((bank & (BANK_MASK >> BANK_SHIFT)) << 1))
#घोषणा B0SEL 0xC0		/* Bank 0 Select */
#घोषणा B1SEL 0xC2		/* Bank 1 Select */
#घोषणा B2SEL 0xC4		/* Bank 2 Select */
#घोषणा B3SEL 0xC6		/* Bank 3 Select */
#घोषणा SETETHRST 0xCA		/* System Reset */
#घोषणा FCDISABLE 0xE0		/* Flow Control Disable */
#घोषणा FCSINGLE 0xE2		/* Flow Control Single */
#घोषणा FCMULTIPLE 0xE4		/* Flow Control Multiple */
#घोषणा FCCLEAR 0xE6		/* Flow Control Clear */
#घोषणा SETPKTDEC 0xCC		/* Decrement Packet Counter */
#घोषणा DMASTOP 0xD2		/* DMA Stop */
#घोषणा DMACKSUM 0xD8		/* DMA Start Checksum */
#घोषणा DMACKSUMS 0xDA		/* DMA Start Checksum with Seed */
#घोषणा DMACOPY 0xDC		/* DMA Start Copy */
#घोषणा DMACOPYS 0xDE		/* DMA Start Copy and Checksum with Seed */
#घोषणा SETTXRTS 0xD4		/* Request Packet Transmission */
#घोषणा ENABLERX 0xE8		/* Enable RX */
#घोषणा DISABLERX 0xEA		/* Disable RX */
#घोषणा SETEIE 0xEC		/* Enable Interrupts */
#घोषणा CLREIE 0xEE		/* Disable Interrupts */

/* Two byte inकाष्ठाions */
#घोषणा RBSEL 0xC8		/* Read Bank Select */

/* Three byte inकाष्ठाions */
#घोषणा WGPRDPT 0x60		/* Write EGPRDPT */
#घोषणा RGPRDPT 0x62		/* Read EGPRDPT */
#घोषणा WRXRDPT 0x64		/* Write ERXRDPT */
#घोषणा RRXRDPT 0x66		/* Read ERXRDPT */
#घोषणा WUDARDPT 0x68		/* Write EUDARDPT */
#घोषणा RUDARDPT 0x6A		/* Read EUDARDPT */
#घोषणा WGPWRPT 0x6C		/* Write EGPWRPT */
#घोषणा RGPWRPT 0x6E		/* Read EGPWRPT */
#घोषणा WRXWRPT 0x70		/* Write ERXWRPT */
#घोषणा RRXWRPT 0x72		/* Read ERXWRPT */
#घोषणा WUDAWRPT 0x74		/* Write EUDAWRPT */
#घोषणा RUDAWRPT 0x76		/* Read EUDAWRPT */

/* n byte inकाष्ठाions */
#घोषणा RCRCODE 0x00
#घोषणा WCRCODE 0x40
#घोषणा BFSCODE 0x80
#घोषणा BFCCODE 0xA0
#घोषणा RCR(addr) (RCRCODE | (addr & ADDR_MASK)) /* Read Control Register */
#घोषणा WCR(addr) (WCRCODE | (addr & ADDR_MASK)) /* Write Control Register */
#घोषणा RCRU 0x20		/* Read Control Register Unbanked */
#घोषणा WCRU 0x22		/* Write Control Register Unbanked */
#घोषणा BFS(addr) (BFSCODE | (addr & ADDR_MASK)) /* Bit Field Set */
#घोषणा BFC(addr) (BFCCODE | (addr & ADDR_MASK)) /* Bit Field Clear */
#घोषणा BFSU 0x24		/* Bit Field Set Unbanked */
#घोषणा BFCU 0x26		/* Bit Field Clear Unbanked */
#घोषणा RGPDATA 0x28		/* Read EGPDATA */
#घोषणा WGPDATA 0x2A		/* Write EGPDATA */
#घोषणा RRXDATA 0x2C		/* Read ERXDATA */
#घोषणा WRXDATA 0x2E		/* Write ERXDATA */
#घोषणा RUDADATA 0x30		/* Read EUDADATA */
#घोषणा WUDADATA 0x32		/* Write EUDADATA */

#घोषणा SFR_REG_COUNT	0xA0

/* ENC424J600 Control Registers
 * Control रेजिस्टर definitions are a combination of address
 * and bank number
 * - Register address (bits 0-4)
 * - Bank number (bits 5-6)
 */
#घोषणा ADDR_MASK 0x1F
#घोषणा BANK_MASK 0x60
#घोषणा BANK_SHIFT 5

/* All-bank रेजिस्टरs */
#घोषणा EUDAST 0x16
#घोषणा EUDAND 0x18
#घोषणा ESTAT 0x1A
#घोषणा EIR 0x1C
#घोषणा ECON1 0x1E

/* Bank 0 रेजिस्टरs */
#घोषणा ETXST (0x00 | 0x00)
#घोषणा ETXLEN (0x02 | 0x00)
#घोषणा ERXST (0x04 | 0x00)
#घोषणा ERXTAIL (0x06 | 0x00)
#घोषणा ERXHEAD (0x08 | 0x00)
#घोषणा EDMAST (0x0A | 0x00)
#घोषणा EDMALEN (0x0C | 0x00)
#घोषणा EDMADST (0x0E | 0x00)
#घोषणा EDMACS (0x10 | 0x00)
#घोषणा ETXSTAT (0x12 | 0x00)
#घोषणा ETXWIRE (0x14 | 0x00)

/* Bank 1 रेजिस्टरs */
#घोषणा EHT1 (0x00 | 0x20)
#घोषणा EHT2 (0x02 | 0x20)
#घोषणा EHT3 (0x04 | 0x20)
#घोषणा EHT4 (0x06 | 0x20)
#घोषणा EPMM1 (0x08 | 0x20)
#घोषणा EPMM2 (0x0A | 0x20)
#घोषणा EPMM3 (0x0C | 0x20)
#घोषणा EPMM4 (0x0E | 0x20)
#घोषणा EPMCS (0x10 | 0x20)
#घोषणा EPMO (0x12 | 0x20)
#घोषणा ERXFCON (0x14 | 0x20)

/* Bank 2 रेजिस्टरs */
#घोषणा MACON1 (0x00 | 0x40)
#घोषणा MACON2 (0x02 | 0x40)
#घोषणा MABBIPG (0x04 | 0x40)
#घोषणा MAIPG (0x06 | 0x40)
#घोषणा MACLCON (0x08 | 0x40)
#घोषणा MAMXFL (0x0A | 0x40)
#घोषणा MICMD (0x12 | 0x40)
#घोषणा MIREGADR (0x14 | 0x40)

/* Bank 3 रेजिस्टरs */
#घोषणा MAADR3 (0x00 | 0x60)
#घोषणा MAADR2 (0x02 | 0x60)
#घोषणा MAADR1 (0x04 | 0x60)
#घोषणा MIWR (0x06 | 0x60)
#घोषणा MIRD (0x08 | 0x60)
#घोषणा MISTAT (0x0A | 0x60)
#घोषणा EPAUS (0x0C | 0x60)
#घोषणा ECON2 (0x0E | 0x60)
#घोषणा ERXWM (0x10 | 0x60)
#घोषणा EIE (0x12 | 0x60)
#घोषणा EIDLED (0x14 | 0x60)

/* Unbanked रेजिस्टरs */
#घोषणा EGPDATA (0x00 | 0x80)
#घोषणा ERXDATA (0x02 | 0x80)
#घोषणा EUDADATA (0x04 | 0x80)
#घोषणा EGPRDPT (0x06 | 0x80)
#घोषणा EGPWRPT (0x08 | 0x80)
#घोषणा ERXRDPT (0x0A | 0x80)
#घोषणा ERXWRPT (0x0C | 0x80)
#घोषणा EUDARDPT (0x0E | 0x80)
#घोषणा EUDAWRPT (0x10 | 0x80)


/* Register bit definitions */
/* ESTAT */
#घोषणा INT (1 << 15)
#घोषणा FCIDLE (1 << 14)
#घोषणा RXBUSY (1 << 13)
#घोषणा CLKRDY (1 << 12)
#घोषणा PHYDPX (1 << 10)
#घोषणा PHYLNK (1 << 8)

/* EIR */
#घोषणा CRYPTEN (1 << 15)
#घोषणा MODEXIF (1 << 14)
#घोषणा HASHIF (1 << 13)
#घोषणा AESIF (1 << 12)
#घोषणा LINKIF (1 << 11)
#घोषणा PKTIF (1 << 6)
#घोषणा DMAIF (1 << 5)
#घोषणा TXIF (1 << 3)
#घोषणा TXABTIF (1 << 2)
#घोषणा RXABTIF (1 << 1)
#घोषणा PCFULIF (1 << 0)

/* ECON1 */
#घोषणा MODEXST (1 << 15)
#घोषणा HASHEN (1 << 14)
#घोषणा HASHOP (1 << 13)
#घोषणा HASHLST (1 << 12)
#घोषणा AESST (1 << 11)
#घोषणा AESOP1 (1 << 10)
#घोषणा AESOP0 (1 << 9)
#घोषणा PKTDEC (1 << 8)
#घोषणा FCOP1 (1 << 7)
#घोषणा FCOP0 (1 << 6)
#घोषणा DMAST (1 << 5)
#घोषणा DMACPY (1 << 4)
#घोषणा DMACSSD (1 << 3)
#घोषणा DMANOCS (1 << 2)
#घोषणा TXRTS (1 << 1)
#घोषणा RXEN (1 << 0)

/* ETXSTAT */
#घोषणा LATECOL (1 << 10)
#घोषणा MAXCOL (1 << 9)
#घोषणा EXDEFER (1 << 8)
#घोषणा ETXSTATL_DEFER (1 << 7)
#घोषणा CRCBAD (1 << 4)
#घोषणा COLCNT_MASK 0xF

/* ERXFCON */
#घोषणा HTEN (1 << 15)
#घोषणा MPEN (1 << 14)
#घोषणा NOTPM (1 << 12)
#घोषणा PMEN3 (1 << 11)
#घोषणा PMEN2 (1 << 10)
#घोषणा PMEN1 (1 << 9)
#घोषणा PMEN0 (1 << 8)
#घोषणा CRCEEN (1 << 7)
#घोषणा CRCEN (1 << 6)
#घोषणा RUNTEEN (1 << 5)
#घोषणा RUNTEN (1 << 4)
#घोषणा UCEN (1 << 3)
#घोषणा NOTMEEN (1 << 2)
#घोषणा MCEN (1 << 1)
#घोषणा BCEN (1 << 0)

/* MACON1 */
#घोषणा LOOPBK (1 << 4)
#घोषणा RXPAUS (1 << 2)
#घोषणा PASSALL (1 << 1)

/* MACON2 */
#घोषणा MACON2_DEFER (1 << 14)
#घोषणा BPEN (1 << 13)
#घोषणा NOBKOFF (1 << 12)
#घोषणा PADCFG2 (1 << 7)
#घोषणा PADCFG1 (1 << 6)
#घोषणा PADCFG0 (1 << 5)
#घोषणा TXCRCEN (1 << 4)
#घोषणा PHDREN (1 << 3)
#घोषणा HFRMEN (1 << 2)
#घोषणा MACON2_RSV1 (1 << 1)
#घोषणा FULDPX (1 << 0)

/* MAIPG */
/* value of the high byte is given by the reserved bits,
 * value of the low byte is recomended setting of the
 * IPG parameter.
 */
#घोषणा MAIPGH_VAL 0x0C
#घोषणा MAIPGL_VAL 0x12

/* MIREGADRH */
#घोषणा MIREGADR_VAL (1 << 8)

/* MIREGADRL */
#घोषणा PHREG_MASK 0x1F

/* MICMD */
#घोषणा MIISCAN (1 << 1)
#घोषणा MIIRD (1 << 0)

/* MISTAT */
#घोषणा NVALID (1 << 2)
#घोषणा SCAN (1 << 1)
#घोषणा BUSY (1 << 0)

/* ECON2 */
#घोषणा ETHEN (1 << 15)
#घोषणा STRCH (1 << 14)
#घोषणा TXMAC (1 << 13)
#घोषणा SHA1MD5 (1 << 12)
#घोषणा COCON3 (1 << 11)
#घोषणा COCON2 (1 << 10)
#घोषणा COCON1 (1 << 9)
#घोषणा COCON0 (1 << 8)
#घोषणा AUTOFC (1 << 7)
#घोषणा TXRST (1 << 6)
#घोषणा RXRST (1 << 5)
#घोषणा ETHRST (1 << 4)
#घोषणा MODLEN1 (1 << 3)
#घोषणा MODLEN0 (1 << 2)
#घोषणा AESLEN1 (1 << 1)
#घोषणा AESLEN0 (1 << 0)

/* EIE */
#घोषणा INTIE (1 << 15)
#घोषणा MODEXIE (1 << 14)
#घोषणा HASHIE (1 << 13)
#घोषणा AESIE (1 << 12)
#घोषणा LINKIE (1 << 11)
#घोषणा PKTIE (1 << 6)
#घोषणा DMAIE (1 << 5)
#घोषणा TXIE (1 << 3)
#घोषणा TXABTIE (1 << 2)
#घोषणा RXABTIE (1 << 1)
#घोषणा PCFULIE (1 << 0)

/* EIDLED */
#घोषणा LACFG3 (1 << 15)
#घोषणा LACFG2 (1 << 14)
#घोषणा LACFG1 (1 << 13)
#घोषणा LACFG0 (1 << 12)
#घोषणा LBCFG3 (1 << 11)
#घोषणा LBCFG2 (1 << 10)
#घोषणा LBCFG1 (1 << 9)
#घोषणा LBCFG0 (1 << 8)
#घोषणा DEVID_SHIFT 5
#घोषणा DEVID_MASK (0x7 << DEVID_SHIFT)
#घोषणा REVID_SHIFT 0
#घोषणा REVID_MASK (0x1F << REVID_SHIFT)

/* PHY रेजिस्टरs */
#घोषणा PHCON1 0x00
#घोषणा PHSTAT1 0x01
#घोषणा PHANA 0x04
#घोषणा PHANLPA 0x05
#घोषणा PHANE 0x06
#घोषणा PHCON2 0x11
#घोषणा PHSTAT2 0x1B
#घोषणा PHSTAT3 0x1F

/* PHCON1 */
#घोषणा PRST (1 << 15)
#घोषणा PLOOPBK (1 << 14)
#घोषणा SPD100 (1 << 13)
#घोषणा ANEN (1 << 12)
#घोषणा PSLEEP (1 << 11)
#घोषणा RENEG (1 << 9)
#घोषणा PFULDPX (1 << 8)

/* PHSTAT1 */
#घोषणा FULL100 (1 << 14)
#घोषणा HALF100 (1 << 13)
#घोषणा FULL10 (1 << 12)
#घोषणा HALF10 (1 << 11)
#घोषणा ANDONE (1 << 5)
#घोषणा LRFAULT (1 << 4)
#घोषणा ANABLE (1 << 3)
#घोषणा LLSTAT (1 << 2)
#घोषणा EXTREGS (1 << 0)

/* PHSTAT2 */
#घोषणा PLRITY (1 << 4)

/* PHSTAT3 */
#घोषणा PHY3SPD100 (1 << 3)
#घोषणा PHY3DPX (1 << 4)
#घोषणा SPDDPX_SHIFT 2
#घोषणा SPDDPX_MASK (0x7 << SPDDPX_SHIFT)

/* PHANA */
/* Default value क्रम PHY initialization*/
#घोषणा PHANA_DEFAULT 0x05E1

/* PHANE */
#घोषणा PDFLT (1 << 4)
#घोषणा LPARCD (1 << 1)
#घोषणा LPANABL (1 << 0)

#घोषणा EUDAST_TEST_VAL 0x1234

#घोषणा TSV_SIZE 7

#घोषणा ENCX24J600_DEV_ID 0x1

/* Configuration */

/* Led is on when the link is present and driven low
 * temporarily when packet is TX'd or RX'd
 */
#घोषणा LED_A_SETTINGS 0xC

/* Led is on अगर the link is in 100 Mbps mode */
#घोषणा LED_B_SETTINGS 0x8

/* maximum ethernet frame length
 * Currently not used as a limit anywhere
 * (we're using the "huge frame enable" feature of
 * enc424j600).
 */
#घोषणा MAX_FRAMELEN 1518

/* Size in bytes of the receive buffer in enc424j600.
 * Must be word aligned (even).
 */
#घोषणा RX_BUFFER_SIZE (15 * MAX_FRAMELEN)

/* Start of the general purpose area in sram */
#घोषणा SRAM_GP_START 0x0

/* SRAM size */
#घोषणा SRAM_SIZE 0x6000

/* Start of the receive buffer */
#घोषणा ERXST_VAL (SRAM_SIZE - RX_BUFFER_SIZE)

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

#घोषणा RSV_RUNTFILTERMATCH	31
#घोषणा RSV_NOTMEFILTERMATCH	32
#घोषणा RSV_HASHFILTERMATCH	33
#घोषणा RSV_MAGICPKTFILTERMATCH	34
#घोषणा RSV_PTRNMTCHFILTERMATCH	35
#घोषणा RSV_UNICASTFILTERMATCH	36

#घोषणा RSV_SIZE		8
#घोषणा RSV_BITMASK(x)		(1 << ((x) - 16))
#घोषणा RSV_GETBIT(x, y)	(((x) & RSV_BITMASK(y)) ? 1 : 0)

काष्ठा rsv अणु
	u16 next_packet;
	u16 len;
	u32 rxstat;
पूर्ण;

/* Put RX buffer at 0 as suggested by the Errata datasheet */

#घोषणा RXSTART_INIT		ERXST_VAL
#घोषणा RXEND_INIT		0x5FFF

पूर्णांक regmap_encx24j600_spi_ग_लिखो(व्योम *context, u8 reg, स्थिर u8 *data,
				माप_प्रकार count);
पूर्णांक regmap_encx24j600_spi_पढ़ो(व्योम *context, u8 reg, u8 *data, माप_प्रकार count);


#पूर्ण_अगर
