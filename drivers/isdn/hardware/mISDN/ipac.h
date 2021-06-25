<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * ipac.h	Defines क्रम the Infineon (क्रमmer Siemens) ISDN
 *		chip series
 *
 * Author       Karsten Keil <keil@isdn4linux.de>
 *
 * Copyright 2009  by Karsten Keil <keil@isdn4linux.de>
 */

#समावेश "iohelper.h"

काष्ठा isac_hw अणु
	काष्ठा dchannel		dch;
	u32			type;
	u32			off;		/* offset to isac regs */
	अक्षर			*name;
	spinlock_t		*hwlock;	/* lock HW access */
	पढ़ो_reg_func		*पढ़ो_reg;
	ग_लिखो_reg_func		*ग_लिखो_reg;
	fअगरo_func		*पढ़ो_fअगरo;
	fअगरo_func		*ग_लिखो_fअगरo;
	पूर्णांक			(*monitor)(व्योम *, u32, u8 *, पूर्णांक);
	व्योम			(*release)(काष्ठा isac_hw *);
	पूर्णांक			(*init)(काष्ठा isac_hw *);
	पूर्णांक			(*ctrl)(काष्ठा isac_hw *, u32, u_दीर्घ);
	पूर्णांक			(*खोलो)(काष्ठा isac_hw *, काष्ठा channel_req *);
	u8			*mon_tx;
	u8			*mon_rx;
	पूर्णांक			mon_txp;
	पूर्णांक			mon_txc;
	पूर्णांक			mon_rxp;
	काष्ठा arcofi_msg	*arcofi_list;
	काष्ठा समयr_list	arcofiसमयr;
	रुको_queue_head_t	arcofi_रुको;
	u8			arcofi_bc;
	u8			arcofi_state;
	u8			mocr;
	u8			adf2;
	u8			state;
पूर्ण;

काष्ठा ipac_hw;

काष्ठा hscx_hw अणु
	काष्ठा bchannel		bch;
	काष्ठा ipac_hw		*ip;
	u8			fअगरo_size;
	u8			off;	/* offset to ICA or ICB */
	u8			slot;
	अक्षर			log[64];
पूर्ण;

काष्ठा ipac_hw अणु
	काष्ठा isac_hw		isac;
	काष्ठा hscx_hw		hscx[2];
	अक्षर			*name;
	व्योम			*hw;
	spinlock_t		*hwlock;	/* lock HW access */
	काष्ठा module		*owner;
	u32			type;
	पढ़ो_reg_func		*पढ़ो_reg;
	ग_लिखो_reg_func		*ग_लिखो_reg;
	fअगरo_func		*पढ़ो_fअगरo;
	fअगरo_func		*ग_लिखो_fअगरo;
	व्योम			(*release)(काष्ठा ipac_hw *);
	पूर्णांक			(*init)(काष्ठा ipac_hw *);
	पूर्णांक			(*ctrl)(काष्ठा ipac_hw *, u32, u_दीर्घ);
	u8			conf;
पूर्ण;

#घोषणा IPAC_TYPE_ISAC		0x0010
#घोषणा IPAC_TYPE_IPAC		0x0020
#घोषणा IPAC_TYPE_ISACX		0x0040
#घोषणा IPAC_TYPE_IPACX		0x0080
#घोषणा IPAC_TYPE_HSCX		0x0100

#घोषणा ISAC_USE_ARCOFI		0x1000

/* Monitor functions */
#घोषणा MONITOR_RX_0		0x1000
#घोषणा MONITOR_RX_1		0x1001
#घोषणा MONITOR_TX_0		0x2000
#घोषणा MONITOR_TX_1		0x2001

/* All रेजिस्टरs original Siemens Spec  */
/* IPAC/ISAC रेजिस्टरs */
#घोषणा ISAC_ISTA		0x20
#घोषणा ISAC_MASK		0x20
#घोषणा ISAC_CMDR		0x21
#घोषणा ISAC_STAR		0x21
#घोषणा ISAC_MODE		0x22
#घोषणा ISAC_TIMR		0x23
#घोषणा ISAC_EXIR		0x24
#घोषणा ISAC_RBCL		0x25
#घोषणा ISAC_RSTA		0x27
#घोषणा ISAC_RBCH		0x2A
#घोषणा ISAC_SPCR		0x30
#घोषणा ISAC_CIR0		0x31
#घोषणा ISAC_CIX0		0x31
#घोषणा ISAC_MOR0		0x32
#घोषणा ISAC_MOX0		0x32
#घोषणा ISAC_CIR1		0x33
#घोषणा ISAC_CIX1		0x33
#घोषणा ISAC_MOR1		0x34
#घोषणा ISAC_MOX1		0x34
#घोषणा ISAC_STCR		0x37
#घोषणा ISAC_ADF1		0x38
#घोषणा ISAC_ADF2		0x39
#घोषणा ISAC_MOCR		0x3a
#घोषणा ISAC_MOSR		0x3a
#घोषणा ISAC_SQRR		0x3b
#घोषणा ISAC_SQXR		0x3b

#घोषणा ISAC_RBCH_XAC		0x80

#घोषणा IPAC_D_TIN2		0x01

/* IPAC/HSCX */
#घोषणा IPAC_ISTAB		0x20	/* RD	*/
#घोषणा IPAC_MASKB		0x20	/* WR	*/
#घोषणा IPAC_STARB		0x21	/* RD	*/
#घोषणा IPAC_CMDRB		0x21	/* WR	*/
#घोषणा IPAC_MODEB		0x22	/* R/W	*/
#घोषणा IPAC_EXIRB		0x24	/* RD	*/
#घोषणा IPAC_RBCLB		0x25	/* RD	*/
#घोषणा IPAC_RAH1		0x26	/* WR	*/
#घोषणा IPAC_RAH2		0x27	/* WR	*/
#घोषणा IPAC_RSTAB		0x27	/* RD	*/
#घोषणा IPAC_RAL1		0x28	/* R/W	*/
#घोषणा IPAC_RAL2		0x29	/* WR	*/
#घोषणा IPAC_RHCRB		0x29	/* RD	*/
#घोषणा IPAC_XBCL		0x2A	/* WR	*/
#घोषणा IPAC_CCR2		0x2C	/* R/W	*/
#घोषणा IPAC_RBCHB		0x2D	/* RD	*/
#घोषणा IPAC_XBCH		0x2D	/* WR	*/
#घोषणा HSCX_VSTR		0x2E	/* RD	*/
#घोषणा IPAC_RLCR		0x2E	/* WR	*/
#घोषणा IPAC_CCR1		0x2F	/* R/W	*/
#घोषणा IPAC_TSAX		0x30	/* WR	*/
#घोषणा IPAC_TSAR		0x31	/* WR	*/
#घोषणा IPAC_XCCR		0x32	/* WR	*/
#घोषणा IPAC_RCCR		0x33	/* WR	*/

/* IPAC_ISTAB/IPAC_MASKB bits */
#घोषणा IPAC_B_XPR		0x10
#घोषणा IPAC_B_RPF		0x40
#घोषणा IPAC_B_RME		0x80
#घोषणा IPAC_B_ON		0x2F

/* IPAC_EXIRB bits */
#घोषणा IPAC_B_RFS		0x04
#घोषणा IPAC_B_RFO		0x10
#घोषणा IPAC_B_XDU		0x40
#घोषणा IPAC_B_XMR		0x80

/* IPAC special रेजिस्टरs */
#घोषणा IPAC_CONF		0xC0	/* R/W	*/
#घोषणा IPAC_ISTA		0xC1	/* RD	*/
#घोषणा IPAC_MASK		0xC1	/* WR	*/
#घोषणा IPAC_ID			0xC2	/* RD	*/
#घोषणा IPAC_ACFG		0xC3	/* R/W	*/
#घोषणा IPAC_AOE		0xC4	/* R/W	*/
#घोषणा IPAC_ARX		0xC5	/* RD	*/
#घोषणा IPAC_ATX		0xC5	/* WR	*/
#घोषणा IPAC_PITA1		0xC6	/* R/W	*/
#घोषणा IPAC_PITA2		0xC7	/* R/W	*/
#घोषणा IPAC_POTA1		0xC8	/* R/W	*/
#घोषणा IPAC_POTA2		0xC9	/* R/W	*/
#घोषणा IPAC_PCFG		0xCA	/* R/W	*/
#घोषणा IPAC_SCFG		0xCB	/* R/W	*/
#घोषणा IPAC_TIMR2		0xCC	/* R/W	*/

/* IPAC_ISTA/_MASK bits */
#घोषणा IPAC__EXB		0x01
#घोषणा IPAC__ICB		0x02
#घोषणा IPAC__EXA		0x04
#घोषणा IPAC__ICA		0x08
#घोषणा IPAC__EXD		0x10
#घोषणा IPAC__ICD		0x20
#घोषणा IPAC__INT0		0x40
#घोषणा IPAC__INT1		0x80
#घोषणा IPAC__ON		0xC0

/* HSCX ISTA/MASK bits */
#घोषणा HSCX__EXB		0x01
#घोषणा HSCX__EXA		0x02
#घोषणा HSCX__ICA		0x04

/* ISAC/ISACX/IPAC/IPACX L1 commands */
#घोषणा ISAC_CMD_TIM		0x0
#घोषणा ISAC_CMD_RS		0x1
#घोषणा ISAC_CMD_SCZ		0x4
#घोषणा ISAC_CMD_SSZ		0x2
#घोषणा ISAC_CMD_AR8		0x8
#घोषणा ISAC_CMD_AR10		0x9
#घोषणा ISAC_CMD_ARL		0xA
#घोषणा ISAC_CMD_DUI		0xF

/* ISAC/ISACX/IPAC/IPACX L1 indications */
#घोषणा ISAC_IND_DR		0x0
#घोषणा ISAC_IND_RS		0x1
#घोषणा ISAC_IND_SD		0x2
#घोषणा ISAC_IND_DIS		0x3
#घोषणा ISAC_IND_RSY		0x4
#घोषणा ISAC_IND_DR6		0x5
#घोषणा ISAC_IND_EI		0x6
#घोषणा ISAC_IND_PU		0x7
#घोषणा ISAC_IND_ARD		0x8
#घोषणा ISAC_IND_TI		0xA
#घोषणा ISAC_IND_ATI		0xB
#घोषणा ISAC_IND_AI8		0xC
#घोषणा ISAC_IND_AI10		0xD
#घोषणा ISAC_IND_DID		0xF

/* the new ISACX / IPACX */
/* D-channel रेजिस्टरs   */
#घोषणा ISACX_RFIFOD		0x00	/* RD	*/
#घोषणा ISACX_XFIFOD		0x00	/* WR	*/
#घोषणा ISACX_ISTAD		0x20	/* RD	*/
#घोषणा ISACX_MASKD		0x20	/* WR	*/
#घोषणा ISACX_STARD		0x21	/* RD	*/
#घोषणा ISACX_CMDRD		0x21	/* WR	*/
#घोषणा ISACX_MODED		0x22	/* R/W	*/
#घोषणा ISACX_EXMD1		0x23	/* R/W	*/
#घोषणा ISACX_TIMR1		0x24	/* R/W	*/
#घोषणा ISACX_SAP1		0x25	/* WR	*/
#घोषणा ISACX_SAP2		0x26	/* WR	*/
#घोषणा ISACX_RBCLD		0x26	/* RD	*/
#घोषणा ISACX_RBCHD		0x27	/* RD	*/
#घोषणा ISACX_TEI1		0x27	/* WR	*/
#घोषणा ISACX_TEI2		0x28	/* WR	*/
#घोषणा ISACX_RSTAD		0x28	/* RD	*/
#घोषणा ISACX_TMD		0x29	/* R/W	*/
#घोषणा ISACX_CIR0		0x2E	/* RD	*/
#घोषणा ISACX_CIX0		0x2E	/* WR	*/
#घोषणा ISACX_CIR1		0x2F	/* RD	*/
#घोषणा ISACX_CIX1		0x2F	/* WR	*/

/* Transceiver रेजिस्टरs  */
#घोषणा ISACX_TR_CONF0		0x30	/* R/W	*/
#घोषणा ISACX_TR_CONF1		0x31	/* R/W	*/
#घोषणा ISACX_TR_CONF2		0x32	/* R/W	*/
#घोषणा ISACX_TR_STA		0x33	/* RD	*/
#घोषणा ISACX_TR_CMD		0x34	/* R/W	*/
#घोषणा ISACX_SQRR1		0x35	/* RD	*/
#घोषणा ISACX_SQXR1		0x35	/* WR	*/
#घोषणा ISACX_SQRR2		0x36	/* RD	*/
#घोषणा ISACX_SQXR2		0x36	/* WR	*/
#घोषणा ISACX_SQRR3		0x37	/* RD	*/
#घोषणा ISACX_SQXR3		0x37	/* WR	*/
#घोषणा ISACX_ISTATR		0x38	/* RD	*/
#घोषणा ISACX_MASKTR		0x39	/* R/W	*/
#घोषणा ISACX_TR_MODE		0x3A	/* R/W	*/
#घोषणा ISACX_ACFG1		0x3C	/* R/W	*/
#घोषणा ISACX_ACFG2		0x3D	/* R/W	*/
#घोषणा ISACX_AOE		0x3E	/* R/W	*/
#घोषणा ISACX_ARX		0x3F	/* RD	*/
#घोषणा ISACX_ATX		0x3F	/* WR	*/

/* IOM: Timeslot, DPS, CDA  */
#घोषणा ISACX_CDA10		0x40	/* R/W	*/
#घोषणा ISACX_CDA11		0x41	/* R/W	*/
#घोषणा ISACX_CDA20		0x42	/* R/W	*/
#घोषणा ISACX_CDA21		0x43	/* R/W	*/
#घोषणा ISACX_CDA_TSDP10	0x44	/* R/W	*/
#घोषणा ISACX_CDA_TSDP11	0x45	/* R/W	*/
#घोषणा ISACX_CDA_TSDP20	0x46	/* R/W	*/
#घोषणा ISACX_CDA_TSDP21	0x47	/* R/W	*/
#घोषणा ISACX_BCHA_TSDP_BC1	0x48	/* R/W	*/
#घोषणा ISACX_BCHA_TSDP_BC2	0x49	/* R/W	*/
#घोषणा ISACX_BCHB_TSDP_BC1	0x4A	/* R/W	*/
#घोषणा ISACX_BCHB_TSDP_BC2	0x4B	/* R/W	*/
#घोषणा ISACX_TR_TSDP_BC1	0x4C	/* R/W	*/
#घोषणा ISACX_TR_TSDP_BC2	0x4D	/* R/W	*/
#घोषणा ISACX_CDA1_CR		0x4E	/* R/W	*/
#घोषणा ISACX_CDA2_CR		0x4F	/* R/W	*/

/* IOM: Contol, Sync transfer, Monitor    */
#घोषणा ISACX_TR_CR		0x50	/* R/W	*/
#घोषणा ISACX_TRC_CR		0x50	/* R/W	*/
#घोषणा ISACX_BCHA_CR		0x51	/* R/W	*/
#घोषणा ISACX_BCHB_CR		0x52	/* R/W	*/
#घोषणा ISACX_DCI_CR		0x53	/* R/W	*/
#घोषणा ISACX_DCIC_CR		0x53	/* R/W	*/
#घोषणा ISACX_MON_CR		0x54	/* R/W	*/
#घोषणा ISACX_SDS1_CR		0x55	/* R/W	*/
#घोषणा ISACX_SDS2_CR		0x56	/* R/W	*/
#घोषणा ISACX_IOM_CR		0x57	/* R/W	*/
#घोषणा ISACX_STI		0x58	/* RD	*/
#घोषणा ISACX_ASTI		0x58	/* WR	*/
#घोषणा ISACX_MSTI		0x59	/* R/W	*/
#घोषणा ISACX_SDS_CONF		0x5A	/* R/W	*/
#घोषणा ISACX_MCDA		0x5B	/* RD	*/
#घोषणा ISACX_MOR		0x5C	/* RD	*/
#घोषणा ISACX_MOX		0x5C	/* WR	*/
#घोषणा ISACX_MOSR		0x5D	/* RD	*/
#घोषणा ISACX_MOCR		0x5E	/* R/W	*/
#घोषणा ISACX_MSTA		0x5F	/* RD	*/
#घोषणा ISACX_MCONF		0x5F	/* WR	*/

/* Interrupt and general रेजिस्टरs */
#घोषणा ISACX_ISTA		0x60	/* RD	*/
#घोषणा ISACX_MASK		0x60	/* WR	*/
#घोषणा ISACX_AUXI		0x61	/* RD	*/
#घोषणा ISACX_AUXM		0x61	/* WR	*/
#घोषणा ISACX_MODE1		0x62	/* R/W	*/
#घोषणा ISACX_MODE2		0x63	/* R/W	*/
#घोषणा ISACX_ID		0x64	/* RD	*/
#घोषणा ISACX_SRES		0x64	/* WR	*/
#घोषणा ISACX_TIMR2		0x65	/* R/W	*/

/* Register Bits */
/* ISACX/IPACX _ISTAD (R) and _MASKD (W) */
#घोषणा ISACX_D_XDU		0x04
#घोषणा ISACX_D_XMR		0x08
#घोषणा ISACX_D_XPR		0x10
#घोषणा ISACX_D_RFO		0x20
#घोषणा ISACX_D_RPF		0x40
#घोषणा ISACX_D_RME		0x80

/* ISACX/IPACX _ISTA (R) and _MASK (W) */
#घोषणा ISACX__ICD		0x01
#घोषणा ISACX__MOS		0x02
#घोषणा ISACX__TRAN		0x04
#घोषणा ISACX__AUX		0x08
#घोषणा ISACX__CIC		0x10
#घोषणा ISACX__ST		0x20
#घोषणा IPACX__ON		0x2C
#घोषणा IPACX__ICB		0x40
#घोषणा IPACX__ICA		0x80

/* ISACX/IPACX _CMDRD (W) */
#घोषणा ISACX_CMDRD_XRES	0x01
#घोषणा ISACX_CMDRD_XME		0x02
#घोषणा ISACX_CMDRD_XTF		0x08
#घोषणा ISACX_CMDRD_STI		0x10
#घोषणा ISACX_CMDRD_RRES	0x40
#घोषणा ISACX_CMDRD_RMC		0x80

/* ISACX/IPACX _RSTAD (R) */
#घोषणा ISACX_RSTAD_TA		0x01
#घोषणा ISACX_RSTAD_CR		0x02
#घोषणा ISACX_RSTAD_SA0		0x04
#घोषणा ISACX_RSTAD_SA1		0x08
#घोषणा ISACX_RSTAD_RAB		0x10
#घोषणा ISACX_RSTAD_CRC		0x20
#घोषणा ISACX_RSTAD_RDO		0x40
#घोषणा ISACX_RSTAD_VFR		0x80

/* ISACX/IPACX _CIR0 (R) */
#घोषणा ISACX_CIR0_BAS		0x01
#घोषणा ISACX_CIR0_SG		0x08
#घोषणा ISACX_CIR0_CIC1		0x08
#घोषणा ISACX_CIR0_CIC0		0x08

/* B-channel रेजिस्टरs */
#घोषणा IPACX_OFF_ICA		0x70
#घोषणा IPACX_OFF_ICB		0x80

/* ICA: IPACX_OFF_ICA + Reg ICB: IPACX_OFF_ICB + Reg */

#घोषणा IPACX_ISTAB		0x00    /* RD	*/
#घोषणा IPACX_MASKB		0x00	/* WR	*/
#घोषणा IPACX_STARB		0x01	/* RD	*/
#घोषणा IPACX_CMDRB		0x01	/* WR	*/
#घोषणा IPACX_MODEB		0x02	/* R/W	*/
#घोषणा IPACX_EXMB		0x03	/* R/W	*/
#घोषणा IPACX_RAH1		0x05	/* WR	*/
#घोषणा IPACX_RAH2		0x06	/* WR	*/
#घोषणा IPACX_RBCLB		0x06	/* RD	*/
#घोषणा IPACX_RBCHB		0x07	/* RD	*/
#घोषणा IPACX_RAL1		0x07	/* WR	*/
#घोषणा IPACX_RAL2		0x08	/* WR	*/
#घोषणा IPACX_RSTAB		0x08	/* RD	*/
#घोषणा IPACX_TMB		0x09	/* R/W	*/
#घोषणा IPACX_RFIFOB		0x0A	/* RD	*/
#घोषणा IPACX_XFIFOB		0x0A	/* WR	*/

/* IPACX_ISTAB / IPACX_MASKB bits */
#घोषणा IPACX_B_XDU		0x04
#घोषणा IPACX_B_XPR		0x10
#घोषणा IPACX_B_RFO		0x20
#घोषणा IPACX_B_RPF		0x40
#घोषणा IPACX_B_RME		0x80

#घोषणा IPACX_B_ON		0x0B

बाह्य पूर्णांक mISDNisac_init(काष्ठा isac_hw *, व्योम *);
बाह्य irqवापस_t mISDNisac_irq(काष्ठा isac_hw *, u8);
बाह्य u32 mISDNipac_init(काष्ठा ipac_hw *, व्योम *);
बाह्य irqवापस_t mISDNipac_irq(काष्ठा ipac_hw *, पूर्णांक);
