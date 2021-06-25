<शैली गुरु>
/*
 *
 * BRIEF MODULE DESCRIPTION
 *	Include file क्रम Alchemy Semiconductor's Au1k CPU.
 *
 * Copyright 2004 Embedded Edge, LLC
 *	dan@embeddededge.com
 *
 *  This program is मुक्त software; you can redistribute  it and/or modअगरy it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT, INसूचीECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License aदीर्घ
 *  with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */

/* Specअगरics क्रम the Au1xxx Programmable Serial Controllers, first
 * seen in the AU1550 part.
 */
#अगर_अघोषित _AU1000_PSC_H_
#घोषणा _AU1000_PSC_H_

/*
 * The PSC select and control रेजिस्टरs are common to all protocols.
 */
#घोषणा PSC_SEL_OFFSET		0x00000000
#घोषणा PSC_CTRL_OFFSET		0x00000004

#घोषणा PSC_SEL_CLK_MASK	(3 << 4)
#घोषणा PSC_SEL_CLK_INTCLK	(0 << 4)
#घोषणा PSC_SEL_CLK_EXTCLK	(1 << 4)
#घोषणा PSC_SEL_CLK_SERCLK	(2 << 4)

#घोषणा PSC_SEL_PS_MASK		0x00000007
#घोषणा PSC_SEL_PS_DISABLED	0
#घोषणा PSC_SEL_PS_SPIMODE	2
#घोषणा PSC_SEL_PS_I2SMODE	3
#घोषणा PSC_SEL_PS_AC97MODE	4
#घोषणा PSC_SEL_PS_SMBUSMODE	5

#घोषणा PSC_CTRL_DISABLE	0
#घोषणा PSC_CTRL_SUSPEND	2
#घोषणा PSC_CTRL_ENABLE		3

/* AC97 Registers. */
#घोषणा PSC_AC97CFG_OFFSET	0x00000008
#घोषणा PSC_AC97MSK_OFFSET	0x0000000c
#घोषणा PSC_AC97PCR_OFFSET	0x00000010
#घोषणा PSC_AC97STAT_OFFSET	0x00000014
#घोषणा PSC_AC97EVNT_OFFSET	0x00000018
#घोषणा PSC_AC97TXRX_OFFSET	0x0000001c
#घोषणा PSC_AC97CDC_OFFSET	0x00000020
#घोषणा PSC_AC97RST_OFFSET	0x00000024
#घोषणा PSC_AC97GPO_OFFSET	0x00000028
#घोषणा PSC_AC97GPI_OFFSET	0x0000002c

/* AC97 Config Register. */
#घोषणा PSC_AC97CFG_RT_MASK	(3 << 30)
#घोषणा PSC_AC97CFG_RT_FIFO1	(0 << 30)
#घोषणा PSC_AC97CFG_RT_FIFO2	(1 << 30)
#घोषणा PSC_AC97CFG_RT_FIFO4	(2 << 30)
#घोषणा PSC_AC97CFG_RT_FIFO8	(3 << 30)

#घोषणा PSC_AC97CFG_TT_MASK	(3 << 28)
#घोषणा PSC_AC97CFG_TT_FIFO1	(0 << 28)
#घोषणा PSC_AC97CFG_TT_FIFO2	(1 << 28)
#घोषणा PSC_AC97CFG_TT_FIFO4	(2 << 28)
#घोषणा PSC_AC97CFG_TT_FIFO8	(3 << 28)

#घोषणा PSC_AC97CFG_DD_DISABLE	(1 << 27)
#घोषणा PSC_AC97CFG_DE_ENABLE	(1 << 26)
#घोषणा PSC_AC97CFG_SE_ENABLE	(1 << 25)

#घोषणा PSC_AC97CFG_LEN_MASK	(0xf << 21)
#घोषणा PSC_AC97CFG_TXSLOT_MASK (0x3ff << 11)
#घोषणा PSC_AC97CFG_RXSLOT_MASK (0x3ff << 1)
#घोषणा PSC_AC97CFG_GE_ENABLE	(1)

/* Enable slots 3-12. */
#घोषणा PSC_AC97CFG_TXSLOT_ENA(x)	(1 << (((x) - 3) + 11))
#घोषणा PSC_AC97CFG_RXSLOT_ENA(x)	(1 << (((x) - 3) + 1))

/*
 * The word length equation is ((x) * 2) + 2, so choose 'x' appropriately.
 * The only sensible numbers are 7, 9, or possibly 11.	Nah, just करो the
 * arithmetic in the macro.
 */
#घोषणा PSC_AC97CFG_SET_LEN(x)	(((((x) - 2) / 2) & 0xf) << 21)
#घोषणा PSC_AC97CFG_GET_LEN(x)	(((((x) >> 21) & 0xf) * 2) + 2)

/* AC97 Mask Register. */
#घोषणा PSC_AC97MSK_GR		(1 << 25)
#घोषणा PSC_AC97MSK_CD		(1 << 24)
#घोषणा PSC_AC97MSK_RR		(1 << 13)
#घोषणा PSC_AC97MSK_RO		(1 << 12)
#घोषणा PSC_AC97MSK_RU		(1 << 11)
#घोषणा PSC_AC97MSK_TR		(1 << 10)
#घोषणा PSC_AC97MSK_TO		(1 << 9)
#घोषणा PSC_AC97MSK_TU		(1 << 8)
#घोषणा PSC_AC97MSK_RD		(1 << 5)
#घोषणा PSC_AC97MSK_TD		(1 << 4)
#घोषणा PSC_AC97MSK_ALLMASK	(PSC_AC97MSK_GR | PSC_AC97MSK_CD | \
				 PSC_AC97MSK_RR | PSC_AC97MSK_RO | \
				 PSC_AC97MSK_RU | PSC_AC97MSK_TR | \
				 PSC_AC97MSK_TO | PSC_AC97MSK_TU | \
				 PSC_AC97MSK_RD | PSC_AC97MSK_TD)

/* AC97 Protocol Control Register. */
#घोषणा PSC_AC97PCR_RC		(1 << 6)
#घोषणा PSC_AC97PCR_RP		(1 << 5)
#घोषणा PSC_AC97PCR_RS		(1 << 4)
#घोषणा PSC_AC97PCR_TC		(1 << 2)
#घोषणा PSC_AC97PCR_TP		(1 << 1)
#घोषणा PSC_AC97PCR_TS		(1 << 0)

/* AC97 Status रेजिस्टर (पढ़ो only). */
#घोषणा PSC_AC97STAT_CB		(1 << 26)
#घोषणा PSC_AC97STAT_CP		(1 << 25)
#घोषणा PSC_AC97STAT_CR		(1 << 24)
#घोषणा PSC_AC97STAT_RF		(1 << 13)
#घोषणा PSC_AC97STAT_RE		(1 << 12)
#घोषणा PSC_AC97STAT_RR		(1 << 11)
#घोषणा PSC_AC97STAT_TF		(1 << 10)
#घोषणा PSC_AC97STAT_TE		(1 << 9)
#घोषणा PSC_AC97STAT_TR		(1 << 8)
#घोषणा PSC_AC97STAT_RB		(1 << 5)
#घोषणा PSC_AC97STAT_TB		(1 << 4)
#घोषणा PSC_AC97STAT_DI		(1 << 2)
#घोषणा PSC_AC97STAT_DR		(1 << 1)
#घोषणा PSC_AC97STAT_SR		(1 << 0)

/* AC97 Event Register. */
#घोषणा PSC_AC97EVNT_GR		(1 << 25)
#घोषणा PSC_AC97EVNT_CD		(1 << 24)
#घोषणा PSC_AC97EVNT_RR		(1 << 13)
#घोषणा PSC_AC97EVNT_RO		(1 << 12)
#घोषणा PSC_AC97EVNT_RU		(1 << 11)
#घोषणा PSC_AC97EVNT_TR		(1 << 10)
#घोषणा PSC_AC97EVNT_TO		(1 << 9)
#घोषणा PSC_AC97EVNT_TU		(1 << 8)
#घोषणा PSC_AC97EVNT_RD		(1 << 5)
#घोषणा PSC_AC97EVNT_TD		(1 << 4)

/* CODEC Command Register. */
#घोषणा PSC_AC97CDC_RD		(1 << 25)
#घोषणा PSC_AC97CDC_ID_MASK	(3 << 23)
#घोषणा PSC_AC97CDC_INDX_MASK	(0x7f << 16)
#घोषणा PSC_AC97CDC_ID(x)	(((x) & 0x03) << 23)
#घोषणा PSC_AC97CDC_INDX(x)	(((x) & 0x7f) << 16)

/* AC97 Reset Control Register. */
#घोषणा PSC_AC97RST_RST		(1 << 1)
#घोषणा PSC_AC97RST_SNC		(1 << 0)

/* PSC in I2S Mode. */
प्रकार काष्ठा	psc_i2s अणु
	u32	psc_sel;
	u32	psc_ctrl;
	u32	psc_i2scfg;
	u32	psc_i2smsk;
	u32	psc_i2spcr;
	u32	psc_i2sstat;
	u32	psc_i2sevent;
	u32	psc_i2stxrx;
	u32	psc_i2sudf;
पूर्ण psc_i2s_t;

#घोषणा PSC_I2SCFG_OFFSET	0x08
#घोषणा PSC_I2SMASK_OFFSET	0x0C
#घोषणा PSC_I2SPCR_OFFSET	0x10
#घोषणा PSC_I2SSTAT_OFFSET	0x14
#घोषणा PSC_I2SEVENT_OFFSET	0x18
#घोषणा PSC_I2SRXTX_OFFSET	0x1C
#घोषणा PSC_I2SUDF_OFFSET	0x20

/* I2S Config Register. */
#घोषणा PSC_I2SCFG_RT_MASK	(3 << 30)
#घोषणा PSC_I2SCFG_RT_FIFO1	(0 << 30)
#घोषणा PSC_I2SCFG_RT_FIFO2	(1 << 30)
#घोषणा PSC_I2SCFG_RT_FIFO4	(2 << 30)
#घोषणा PSC_I2SCFG_RT_FIFO8	(3 << 30)

#घोषणा PSC_I2SCFG_TT_MASK	(3 << 28)
#घोषणा PSC_I2SCFG_TT_FIFO1	(0 << 28)
#घोषणा PSC_I2SCFG_TT_FIFO2	(1 << 28)
#घोषणा PSC_I2SCFG_TT_FIFO4	(2 << 28)
#घोषणा PSC_I2SCFG_TT_FIFO8	(3 << 28)

#घोषणा PSC_I2SCFG_DD_DISABLE	(1 << 27)
#घोषणा PSC_I2SCFG_DE_ENABLE	(1 << 26)
#घोषणा PSC_I2SCFG_SET_WS(x)	(((((x) / 2) - 1) & 0x7f) << 16)
#घोषणा PSC_I2SCFG_WS(n)	((n & 0xFF) << 16)
#घोषणा PSC_I2SCFG_WS_MASK	(PSC_I2SCFG_WS(0x3F))
#घोषणा PSC_I2SCFG_WI		(1 << 15)

#घोषणा PSC_I2SCFG_DIV_MASK	(3 << 13)
#घोषणा PSC_I2SCFG_DIV2		(0 << 13)
#घोषणा PSC_I2SCFG_DIV4		(1 << 13)
#घोषणा PSC_I2SCFG_DIV8		(2 << 13)
#घोषणा PSC_I2SCFG_DIV16	(3 << 13)

#घोषणा PSC_I2SCFG_BI		(1 << 12)
#घोषणा PSC_I2SCFG_BUF		(1 << 11)
#घोषणा PSC_I2SCFG_MLJ		(1 << 10)
#घोषणा PSC_I2SCFG_XM		(1 << 9)

/* The word length equation is simply LEN+1. */
#घोषणा PSC_I2SCFG_SET_LEN(x)	((((x) - 1) & 0x1f) << 4)
#घोषणा PSC_I2SCFG_GET_LEN(x)	((((x) >> 4) & 0x1f) + 1)

#घोषणा PSC_I2SCFG_LB		(1 << 2)
#घोषणा PSC_I2SCFG_MLF		(1 << 1)
#घोषणा PSC_I2SCFG_MS		(1 << 0)

/* I2S Mask Register. */
#घोषणा PSC_I2SMSK_RR		(1 << 13)
#घोषणा PSC_I2SMSK_RO		(1 << 12)
#घोषणा PSC_I2SMSK_RU		(1 << 11)
#घोषणा PSC_I2SMSK_TR		(1 << 10)
#घोषणा PSC_I2SMSK_TO		(1 << 9)
#घोषणा PSC_I2SMSK_TU		(1 << 8)
#घोषणा PSC_I2SMSK_RD		(1 << 5)
#घोषणा PSC_I2SMSK_TD		(1 << 4)
#घोषणा PSC_I2SMSK_ALLMASK	(PSC_I2SMSK_RR | PSC_I2SMSK_RO | \
				 PSC_I2SMSK_RU | PSC_I2SMSK_TR | \
				 PSC_I2SMSK_TO | PSC_I2SMSK_TU | \
				 PSC_I2SMSK_RD | PSC_I2SMSK_TD)

/* I2S Protocol Control Register. */
#घोषणा PSC_I2SPCR_RC		(1 << 6)
#घोषणा PSC_I2SPCR_RP		(1 << 5)
#घोषणा PSC_I2SPCR_RS		(1 << 4)
#घोषणा PSC_I2SPCR_TC		(1 << 2)
#घोषणा PSC_I2SPCR_TP		(1 << 1)
#घोषणा PSC_I2SPCR_TS		(1 << 0)

/* I2S Status रेजिस्टर (पढ़ो only). */
#घोषणा PSC_I2SSTAT_RF		(1 << 13)
#घोषणा PSC_I2SSTAT_RE		(1 << 12)
#घोषणा PSC_I2SSTAT_RR		(1 << 11)
#घोषणा PSC_I2SSTAT_TF		(1 << 10)
#घोषणा PSC_I2SSTAT_TE		(1 << 9)
#घोषणा PSC_I2SSTAT_TR		(1 << 8)
#घोषणा PSC_I2SSTAT_RB		(1 << 5)
#घोषणा PSC_I2SSTAT_TB		(1 << 4)
#घोषणा PSC_I2SSTAT_DI		(1 << 2)
#घोषणा PSC_I2SSTAT_DR		(1 << 1)
#घोषणा PSC_I2SSTAT_SR		(1 << 0)

/* I2S Event Register. */
#घोषणा PSC_I2SEVNT_RR		(1 << 13)
#घोषणा PSC_I2SEVNT_RO		(1 << 12)
#घोषणा PSC_I2SEVNT_RU		(1 << 11)
#घोषणा PSC_I2SEVNT_TR		(1 << 10)
#घोषणा PSC_I2SEVNT_TO		(1 << 9)
#घोषणा PSC_I2SEVNT_TU		(1 << 8)
#घोषणा PSC_I2SEVNT_RD		(1 << 5)
#घोषणा PSC_I2SEVNT_TD		(1 << 4)

/* PSC in SPI Mode. */
प्रकार काष्ठा	psc_spi अणु
	u32	psc_sel;
	u32	psc_ctrl;
	u32	psc_spicfg;
	u32	psc_spimsk;
	u32	psc_spipcr;
	u32	psc_spistat;
	u32	psc_spievent;
	u32	psc_spitxrx;
पूर्ण psc_spi_t;

/* SPI Config Register. */
#घोषणा PSC_SPICFG_RT_MASK	(3 << 30)
#घोषणा PSC_SPICFG_RT_FIFO1	(0 << 30)
#घोषणा PSC_SPICFG_RT_FIFO2	(1 << 30)
#घोषणा PSC_SPICFG_RT_FIFO4	(2 << 30)
#घोषणा PSC_SPICFG_RT_FIFO8	(3 << 30)

#घोषणा PSC_SPICFG_TT_MASK	(3 << 28)
#घोषणा PSC_SPICFG_TT_FIFO1	(0 << 28)
#घोषणा PSC_SPICFG_TT_FIFO2	(1 << 28)
#घोषणा PSC_SPICFG_TT_FIFO4	(2 << 28)
#घोषणा PSC_SPICFG_TT_FIFO8	(3 << 28)

#घोषणा PSC_SPICFG_DD_DISABLE	(1 << 27)
#घोषणा PSC_SPICFG_DE_ENABLE	(1 << 26)
#घोषणा PSC_SPICFG_CLR_BAUD(x)	((x) & ~((0x3f) << 15))
#घोषणा PSC_SPICFG_SET_BAUD(x)	(((x) & 0x3f) << 15)

#घोषणा PSC_SPICFG_SET_DIV(x)	(((x) & 0x03) << 13)
#घोषणा PSC_SPICFG_DIV2		0
#घोषणा PSC_SPICFG_DIV4		1
#घोषणा PSC_SPICFG_DIV8		2
#घोषणा PSC_SPICFG_DIV16	3

#घोषणा PSC_SPICFG_BI		(1 << 12)
#घोषणा PSC_SPICFG_PSE		(1 << 11)
#घोषणा PSC_SPICFG_CGE		(1 << 10)
#घोषणा PSC_SPICFG_CDE		(1 << 9)

#घोषणा PSC_SPICFG_CLR_LEN(x)	((x) & ~((0x1f) << 4))
#घोषणा PSC_SPICFG_SET_LEN(x)	(((x-1) & 0x1f) << 4)

#घोषणा PSC_SPICFG_LB		(1 << 3)
#घोषणा PSC_SPICFG_MLF		(1 << 1)
#घोषणा PSC_SPICFG_MO		(1 << 0)

/* SPI Mask Register. */
#घोषणा PSC_SPIMSK_MM		(1 << 16)
#घोषणा PSC_SPIMSK_RR		(1 << 13)
#घोषणा PSC_SPIMSK_RO		(1 << 12)
#घोषणा PSC_SPIMSK_RU		(1 << 11)
#घोषणा PSC_SPIMSK_TR		(1 << 10)
#घोषणा PSC_SPIMSK_TO		(1 << 9)
#घोषणा PSC_SPIMSK_TU		(1 << 8)
#घोषणा PSC_SPIMSK_SD		(1 << 5)
#घोषणा PSC_SPIMSK_MD		(1 << 4)
#घोषणा PSC_SPIMSK_ALLMASK	(PSC_SPIMSK_MM | PSC_SPIMSK_RR | \
				 PSC_SPIMSK_RO | PSC_SPIMSK_TO | \
				 PSC_SPIMSK_TU | PSC_SPIMSK_SD | \
				 PSC_SPIMSK_MD)

/* SPI Protocol Control Register. */
#घोषणा PSC_SPIPCR_RC		(1 << 6)
#घोषणा PSC_SPIPCR_SP		(1 << 5)
#घोषणा PSC_SPIPCR_SS		(1 << 4)
#घोषणा PSC_SPIPCR_TC		(1 << 2)
#घोषणा PSC_SPIPCR_MS		(1 << 0)

/* SPI Status रेजिस्टर (पढ़ो only). */
#घोषणा PSC_SPISTAT_RF		(1 << 13)
#घोषणा PSC_SPISTAT_RE		(1 << 12)
#घोषणा PSC_SPISTAT_RR		(1 << 11)
#घोषणा PSC_SPISTAT_TF		(1 << 10)
#घोषणा PSC_SPISTAT_TE		(1 << 9)
#घोषणा PSC_SPISTAT_TR		(1 << 8)
#घोषणा PSC_SPISTAT_SB		(1 << 5)
#घोषणा PSC_SPISTAT_MB		(1 << 4)
#घोषणा PSC_SPISTAT_DI		(1 << 2)
#घोषणा PSC_SPISTAT_DR		(1 << 1)
#घोषणा PSC_SPISTAT_SR		(1 << 0)

/* SPI Event Register. */
#घोषणा PSC_SPIEVNT_MM		(1 << 16)
#घोषणा PSC_SPIEVNT_RR		(1 << 13)
#घोषणा PSC_SPIEVNT_RO		(1 << 12)
#घोषणा PSC_SPIEVNT_RU		(1 << 11)
#घोषणा PSC_SPIEVNT_TR		(1 << 10)
#घोषणा PSC_SPIEVNT_TO		(1 << 9)
#घोषणा PSC_SPIEVNT_TU		(1 << 8)
#घोषणा PSC_SPIEVNT_SD		(1 << 5)
#घोषणा PSC_SPIEVNT_MD		(1 << 4)

/* Transmit रेजिस्टर control. */
#घोषणा PSC_SPITXRX_LC		(1 << 29)
#घोषणा PSC_SPITXRX_SR		(1 << 28)

/* SMBus Config Register. */
#घोषणा PSC_SMBCFG_RT_MASK	(3 << 30)
#घोषणा PSC_SMBCFG_RT_FIFO1	(0 << 30)
#घोषणा PSC_SMBCFG_RT_FIFO2	(1 << 30)
#घोषणा PSC_SMBCFG_RT_FIFO4	(2 << 30)
#घोषणा PSC_SMBCFG_RT_FIFO8	(3 << 30)

#घोषणा PSC_SMBCFG_TT_MASK	(3 << 28)
#घोषणा PSC_SMBCFG_TT_FIFO1	(0 << 28)
#घोषणा PSC_SMBCFG_TT_FIFO2	(1 << 28)
#घोषणा PSC_SMBCFG_TT_FIFO4	(2 << 28)
#घोषणा PSC_SMBCFG_TT_FIFO8	(3 << 28)

#घोषणा PSC_SMBCFG_DD_DISABLE	(1 << 27)
#घोषणा PSC_SMBCFG_DE_ENABLE	(1 << 26)

#घोषणा PSC_SMBCFG_SET_DIV(x)	(((x) & 0x03) << 13)
#घोषणा PSC_SMBCFG_DIV2		0
#घोषणा PSC_SMBCFG_DIV4		1
#घोषणा PSC_SMBCFG_DIV8		2
#घोषणा PSC_SMBCFG_DIV16	3

#घोषणा PSC_SMBCFG_GCE		(1 << 9)
#घोषणा PSC_SMBCFG_SFM		(1 << 8)

#घोषणा PSC_SMBCFG_SET_SLV(x)	(((x) & 0x7f) << 1)

/* SMBus Mask Register. */
#घोषणा PSC_SMBMSK_DN		(1 << 30)
#घोषणा PSC_SMBMSK_AN		(1 << 29)
#घोषणा PSC_SMBMSK_AL		(1 << 28)
#घोषणा PSC_SMBMSK_RR		(1 << 13)
#घोषणा PSC_SMBMSK_RO		(1 << 12)
#घोषणा PSC_SMBMSK_RU		(1 << 11)
#घोषणा PSC_SMBMSK_TR		(1 << 10)
#घोषणा PSC_SMBMSK_TO		(1 << 9)
#घोषणा PSC_SMBMSK_TU		(1 << 8)
#घोषणा PSC_SMBMSK_SD		(1 << 5)
#घोषणा PSC_SMBMSK_MD		(1 << 4)
#घोषणा PSC_SMBMSK_ALLMASK	(PSC_SMBMSK_DN | PSC_SMBMSK_AN | \
				 PSC_SMBMSK_AL | PSC_SMBMSK_RR | \
				 PSC_SMBMSK_RO | PSC_SMBMSK_TO | \
				 PSC_SMBMSK_TU | PSC_SMBMSK_SD | \
				 PSC_SMBMSK_MD)

/* SMBus Protocol Control Register. */
#घोषणा PSC_SMBPCR_DC		(1 << 2)
#घोषणा PSC_SMBPCR_MS		(1 << 0)

/* SMBus Status रेजिस्टर (पढ़ो only). */
#घोषणा PSC_SMBSTAT_BB		(1 << 28)
#घोषणा PSC_SMBSTAT_RF		(1 << 13)
#घोषणा PSC_SMBSTAT_RE		(1 << 12)
#घोषणा PSC_SMBSTAT_RR		(1 << 11)
#घोषणा PSC_SMBSTAT_TF		(1 << 10)
#घोषणा PSC_SMBSTAT_TE		(1 << 9)
#घोषणा PSC_SMBSTAT_TR		(1 << 8)
#घोषणा PSC_SMBSTAT_SB		(1 << 5)
#घोषणा PSC_SMBSTAT_MB		(1 << 4)
#घोषणा PSC_SMBSTAT_DI		(1 << 2)
#घोषणा PSC_SMBSTAT_DR		(1 << 1)
#घोषणा PSC_SMBSTAT_SR		(1 << 0)

/* SMBus Event Register. */
#घोषणा PSC_SMBEVNT_DN		(1 << 30)
#घोषणा PSC_SMBEVNT_AN		(1 << 29)
#घोषणा PSC_SMBEVNT_AL		(1 << 28)
#घोषणा PSC_SMBEVNT_RR		(1 << 13)
#घोषणा PSC_SMBEVNT_RO		(1 << 12)
#घोषणा PSC_SMBEVNT_RU		(1 << 11)
#घोषणा PSC_SMBEVNT_TR		(1 << 10)
#घोषणा PSC_SMBEVNT_TO		(1 << 9)
#घोषणा PSC_SMBEVNT_TU		(1 << 8)
#घोषणा PSC_SMBEVNT_SD		(1 << 5)
#घोषणा PSC_SMBEVNT_MD		(1 << 4)
#घोषणा PSC_SMBEVNT_ALLCLR	(PSC_SMBEVNT_DN | PSC_SMBEVNT_AN | \
				 PSC_SMBEVNT_AL | PSC_SMBEVNT_RR | \
				 PSC_SMBEVNT_RO | PSC_SMBEVNT_TO | \
				 PSC_SMBEVNT_TU | PSC_SMBEVNT_SD | \
				 PSC_SMBEVNT_MD)

/* Transmit रेजिस्टर control. */
#घोषणा PSC_SMBTXRX_RSR		(1 << 28)
#घोषणा PSC_SMBTXRX_STP		(1 << 29)
#घोषणा PSC_SMBTXRX_DATAMASK	0xff

/* SMBus protocol समयrs रेजिस्टर. */
#घोषणा PSC_SMBTMR_SET_TH(x)	(((x) & 0x03) << 30)
#घोषणा PSC_SMBTMR_SET_PS(x)	(((x) & 0x1f) << 25)
#घोषणा PSC_SMBTMR_SET_PU(x)	(((x) & 0x1f) << 20)
#घोषणा PSC_SMBTMR_SET_SH(x)	(((x) & 0x1f) << 15)
#घोषणा PSC_SMBTMR_SET_SU(x)	(((x) & 0x1f) << 10)
#घोषणा PSC_SMBTMR_SET_CL(x)	(((x) & 0x1f) << 5)
#घोषणा PSC_SMBTMR_SET_CH(x)	(((x) & 0x1f) << 0)

#पूर्ण_अगर /* _AU1000_PSC_H_ */
