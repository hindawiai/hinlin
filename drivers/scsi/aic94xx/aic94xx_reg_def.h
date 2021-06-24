<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Aic94xx SAS/SATA driver hardware रेजिस्टरs definitions.
 *
 * Copyright (C) 2004 Adaptec, Inc.  All rights reserved.
 * Copyright (C) 2004 David Chaw <david_chaw@adaptec.com>
 * Copyright (C) 2005 Luben Tuikov <luben_tuikov@adaptec.com>
 *
 * Luben Tuikov: Some रेजिस्टर value updates to make it work with the winकरोw
 * agnostic रेजिस्टर r/w functions.  Some रेजिस्टर corrections, sizes,
 * etc.
 *
 * $Id: //depot/aic94xx/aic94xx_reg_def.h#27 $
 */

#अगर_अघोषित _ADP94XX_REG_DEF_H_
#घोषणा _ADP94XX_REG_DEF_H_

/*
 * Common definitions.
 */
#घोषणा CSEQ_MODE_PAGE_SIZE	0x200		/* CSEQ mode page size */
#घोषणा LmSEQ_MODE_PAGE_SIZE	0x200		/* LmSEQ mode page size */
#घोषणा LmSEQ_HOST_REG_SIZE   	0x4000		/* LmSEQ Host Register size */

/********************* COM_SAS रेजिस्टरs definition *************************/

/* The base is REG_BASE_ADDR, defined in aic94xx_reg.h.
 */

/*
 * CHIM Registers, Address Range : (0x00-0xFF)
 */
#घोषणा COMBIST		(REG_BASE_ADDR + 0x00)

/* bits 31:24 */
#घोषणा		L7BLKRST		0x80000000
#घोषणा		L6BLKRST		0x40000000
#घोषणा		L5BLKRST		0x20000000
#घोषणा		L4BLKRST		0x10000000
#घोषणा		L3BLKRST		0x08000000
#घोषणा		L2BLKRST		0x04000000
#घोषणा		L1BLKRST		0x02000000
#घोषणा		L0BLKRST		0x01000000
#घोषणा		LmBLKRST		0xFF000000
#घोषणा LmBLKRST_COMBIST(phyid)		(1 << (24 + phyid))

#घोषणा		OCMBLKRST		0x00400000
#घोषणा		CTXMEMBLKRST		0x00200000
#घोषणा		CSEQBLKRST		0x00100000
#घोषणा		EXSIBLKRST		0x00040000
#घोषणा		DPIBLKRST		0x00020000
#घोषणा		DFIFBLKRST		0x00010000
#घोषणा		HARDRST			0x00000200
#घोषणा		COMBLKRST		0x00000100
#घोषणा		FRCDFPERR		0x00000080
#घोषणा		FRCCIOPERR		0x00000020
#घोषणा		FRCBISTERR		0x00000010
#घोषणा		COMBISTEN		0x00000004
#घोषणा		COMBISTDONE		0x00000002	/* ro */
#घोषणा 	COMBISTFAIL		0x00000001	/* ro */

#घोषणा COMSTAT		(REG_BASE_ADDR + 0x04)

#घोषणा		REQMBXREAD		0x00000040
#घोषणा 	RSPMBXAVAIL		0x00000020
#घोषणा 	CSBUFPERR		0x00000008
#घोषणा		OVLYERR			0x00000004
#घोषणा 	CSERR			0x00000002
#घोषणा		OVLYDMADONE		0x00000001

#घोषणा		COMSTAT_MASK		(REQMBXREAD | RSPMBXAVAIL | \
					 CSBUFPERR | OVLYERR | CSERR |\
					 OVLYDMADONE)

#घोषणा COMSTATEN	(REG_BASE_ADDR + 0x08)

#घोषणा		EN_REQMBXREAD		0x00000040
#घोषणा		EN_RSPMBXAVAIL		0x00000020
#घोषणा		EN_CSBUFPERR		0x00000008
#घोषणा		EN_OVLYERR		0x00000004
#घोषणा		EN_CSERR		0x00000002
#घोषणा		EN_OVLYDONE		0x00000001

#घोषणा SCBPRO		(REG_BASE_ADDR + 0x0C)

#घोषणा		SCBCONS_MASK		0xFFFF0000
#घोषणा		SCBPRO_MASK		0x0000FFFF

#घोषणा CHIMREQMBX	(REG_BASE_ADDR + 0x10)

#घोषणा CHIMRSPMBX	(REG_BASE_ADDR + 0x14)

#घोषणा CHIMINT		(REG_BASE_ADDR + 0x18)

#घोषणा		EXT_INT0		0x00000800
#घोषणा		EXT_INT1		0x00000400
#घोषणा		PORRSTDET		0x00000200
#घोषणा		HARDRSTDET		0x00000100
#घोषणा		DLAVAILQ		0x00000080	/* ro */
#घोषणा		HOSTERR			0x00000040
#घोषणा		INITERR			0x00000020
#घोषणा		DEVINT			0x00000010
#घोषणा		COMINT			0x00000008
#घोषणा		DEVTIMER2		0x00000004
#घोषणा		DEVTIMER1		0x00000002
#घोषणा		DLAVAIL			0x00000001

#घोषणा		CHIMINT_MASK		(HOSTERR | INITERR | DEVINT | COMINT |\
					 DEVTIMER2 | DEVTIMER1 | DLAVAIL)

#घोषणा 	DEVEXCEPT_MASK		(HOSTERR | INITERR | DEVINT | COMINT)

#घोषणा CHIMINTEN	(REG_BASE_ADDR + 0x1C)

#घोषणा		RST_EN_EXT_INT1		0x01000000
#घोषणा		RST_EN_EXT_INT0		0x00800000
#घोषणा		RST_EN_HOSTERR		0x00400000
#घोषणा		RST_EN_INITERR		0x00200000
#घोषणा		RST_EN_DEVINT		0x00100000
#घोषणा		RST_EN_COMINT		0x00080000
#घोषणा		RST_EN_DEVTIMER2	0x00040000
#घोषणा		RST_EN_DEVTIMER1	0x00020000
#घोषणा		RST_EN_DLAVAIL		0x00010000
#घोषणा		SET_EN_EXT_INT1		0x00000100
#घोषणा		SET_EN_EXT_INT0		0x00000080
#घोषणा		SET_EN_HOSTERR		0x00000040
#घोषणा		SET_EN_INITERR		0x00000020
#घोषणा		SET_EN_DEVINT		0x00000010
#घोषणा		SET_EN_COMINT		0x00000008
#घोषणा		SET_EN_DEVTIMER2	0x00000004
#घोषणा		SET_EN_DEVTIMER1	0x00000002
#घोषणा		SET_EN_DLAVAIL		0x00000001

#घोषणा		RST_CHIMINTEN		(RST_EN_HOSTERR | RST_EN_INITERR | \
					 RST_EN_DEVINT | RST_EN_COMINT | \
					 RST_EN_DEVTIMER2 | RST_EN_DEVTIMER1 |\
					 RST_EN_DLAVAIL)

#घोषणा		SET_CHIMINTEN		(SET_EN_HOSTERR | SET_EN_INITERR |\
					 SET_EN_DEVINT | SET_EN_COMINT |\
					 SET_EN_DLAVAIL)

#घोषणा OVLYDMACTL	(REG_BASE_ADDR + 0x20)

#घोषणा		OVLYADR_MASK		0x07FF0000
#घोषणा		OVLYLSEQ_MASK		0x0000FF00
#घोषणा		OVLYCSEQ		0x00000080
#घोषणा		OVLYHALTERR		0x00000040
#घोषणा		PIOCMODE		0x00000020
#घोषणा		RESETOVLYDMA		0x00000008	/* wo */
#घोषणा		STARTOVLYDMA		0x00000004
#घोषणा		STOPOVLYDMA		0x00000002	/* wo */
#घोषणा		OVLYDMAACT		0x00000001	/* ro */

#घोषणा OVLYDMACNT	(REG_BASE_ADDR + 0x24)

#घोषणा		OVLYDOMAIN1		0x20000000	/* ro */
#घोषणा		OVLYDOMAIN0		0x10000000
#घोषणा		OVLYBUFADR_MASK		0x007F0000
#घोषणा		OVLYDMACNT_MASK		0x00003FFF

#घोषणा OVLYDMAADR	(REG_BASE_ADDR + 0x28)

#घोषणा DMAERR		(REG_BASE_ADDR + 0x30)

#घोषणा		OVLYERRSTAT_MASK	0x0000FF00	/* ro */
#घोषणा		CSERRSTAT_MASK		0x000000FF	/* ro */

#घोषणा SPIODATA	(REG_BASE_ADDR + 0x34)

/* 0x38 - 0x3C are reserved  */

#घोषणा T1CNTRLR	(REG_BASE_ADDR + 0x40)

#घोषणा		T1DONE			0x00010000	/* ro */
#घोषणा		TIMER64			0x00000400
#घोषणा		T1ENABLE		0x00000200
#घोषणा		T1RELOAD		0x00000100
#घोषणा		T1PRESCALER_MASK	0x00000003

#घोषणा	T1CMPR		(REG_BASE_ADDR + 0x44)

#घोषणा T1CNTR		(REG_BASE_ADDR + 0x48)

#घोषणा T2CNTRLR	(REG_BASE_ADDR + 0x4C)

#घोषणा		T2DONE			0x00010000	/* ro */
#घोषणा		T2ENABLE		0x00000200
#घोषणा		T2RELOAD		0x00000100
#घोषणा		T2PRESCALER_MASK	0x00000003

#घोषणा	T2CMPR		(REG_BASE_ADDR + 0x50)

#घोषणा T2CNTR		(REG_BASE_ADDR + 0x54)

/* 0x58h - 0xFCh are reserved */

/*
 * DCH_SAS Registers, Address Range : (0x800-0xFFF)
 */
#घोषणा CMDCTXBASE	(REG_BASE_ADDR + 0x800)

#घोषणा DEVCTXBASE	(REG_BASE_ADDR + 0x808)

#घोषणा CTXDOMAIN	(REG_BASE_ADDR + 0x810)

#घोषणा		DEVCTXDOMAIN1		0x00000008	/* ro */
#घोषणा		DEVCTXDOMAIN0		0x00000004
#घोषणा		CMDCTXDOMAIN1		0x00000002	/* ro */
#घोषणा		CMDCTXDOMAIN0		0x00000001

#घोषणा DCHCTL		(REG_BASE_ADDR + 0x814)

#घोषणा		OCMBISTREPAIR		0x00080000
#घोषणा		OCMBISTEN		0x00040000
#घोषणा		OCMBISTDN		0x00020000	/* ro */
#घोषणा		OCMBISTFAIL		0x00010000	/* ro */
#घोषणा		DDBBISTEN		0x00004000
#घोषणा		DDBBISTDN		0x00002000	/* ro */
#घोषणा		DDBBISTFAIL		0x00001000	/* ro */
#घोषणा		SCBBISTEN		0x00000400
#घोषणा		SCBBISTDN		0x00000200	/* ro */
#घोषणा		SCBBISTFAIL		0x00000100	/* ro */

#घोषणा		MEMSEL_MASK		0x000000E0
#घोषणा		MEMSEL_CCM_LSEQ		0x00000000
#घोषणा		MEMSEL_CCM_IOP		0x00000020
#घोषणा		MEMSEL_CCM_SASCTL	0x00000040
#घोषणा		MEMSEL_DCM_LSEQ		0x00000060
#घोषणा		MEMSEL_DCM_IOP		0x00000080
#घोषणा		MEMSEL_OCM		0x000000A0

#घोषणा		FRCERR			0x00000010
#घोषणा		AUTORLS			0x00000001

#घोषणा DCHREVISION	(REG_BASE_ADDR + 0x818)

#घोषणा		DCHREVISION_MASK	0x000000FF

#घोषणा DCHSTATUS	(REG_BASE_ADDR + 0x81C)

#घोषणा		EN_CFIFTOERR		0x00020000
#घोषणा		CFIFTOERR		0x00000200
#घोषणा		CSEQINT			0x00000100	/* ro */
#घोषणा		LSEQ7INT		0x00000080	/* ro */
#घोषणा		LSEQ6INT		0x00000040	/* ro */
#घोषणा		LSEQ5INT		0x00000020	/* ro */
#घोषणा		LSEQ4INT		0x00000010	/* ro */
#घोषणा		LSEQ3INT		0x00000008	/* ro */
#घोषणा		LSEQ2INT		0x00000004	/* ro */
#घोषणा		LSEQ1INT		0x00000002	/* ro */
#घोषणा		LSEQ0INT		0x00000001	/* ro */

#घोषणा		LSEQINT_MASK		(LSEQ7INT | LSEQ6INT | LSEQ5INT |\
					 LSEQ4INT | LSEQ3INT | LSEQ2INT	|\
					 LSEQ1INT | LSEQ0INT)

#घोषणा DCHDFIFDEBUG	(REG_BASE_ADDR + 0x820)
#घोषणा		ENFAIRMST		0x00FF0000
#घोषणा		DISWRMST9		0x00000200
#घोषणा		DISWRMST8		0x00000100
#घोषणा		DISRDMST		0x000000FF

#घोषणा ATOMICSTATCTL	(REG_BASE_ADDR + 0x824)
/* 8 bit wide */
#घोषणा		AUTOINC			0x80
#घोषणा		ATOMICERR		0x04
#घोषणा		ATOMICWIN		0x02
#घोषणा		ATOMICDONE		0x01


#घोषणा ALTCIOADR	(REG_BASE_ADDR + 0x828)
/* 16 bit; bits 8:0 define CIO addr space of CSEQ */

#घोषणा ASCBPTR		(REG_BASE_ADDR + 0x82C)
/* 16 bit wide */

#घोषणा ADDBPTR		(REG_BASE_ADDR + 0x82E)
/* 16 bit wide */

#घोषणा ANEWDATA	(REG_BASE_ADDR + 0x830)
/* 16 bit */

#घोषणा AOLDDATA	(REG_BASE_ADDR + 0x834)
/* 16 bit */

#घोषणा CTXACCESS	(REG_BASE_ADDR + 0x838)
/* 32 bit */

/* 0x83Ch - 0xFFCh are reserved */

/*
 * ARP2 External Processor Registers, Address Range : (0x00-0x1F)
 */
#घोषणा ARP2CTL		0x00

#घोषणा		FRCSCRPERR		0x00040000
#घोषणा		FRCARP2PERR		0x00020000
#घोषणा		FRCARP2ILLOPC		0x00010000
#घोषणा		ENWAITTO		0x00008000
#घोषणा		PERRORDIS		0x00004000
#घोषणा		FAILDIS			0x00002000
#घोषणा		CIOPERRDIS		0x00001000
#घोषणा		BREAKEN3		0x00000800
#घोषणा		BREAKEN2		0x00000400
#घोषणा		BREAKEN1		0x00000200
#घोषणा		BREAKEN0		0x00000100
#घोषणा		EPAUSE			0x00000008
#घोषणा		PAUSED			0x00000004	/* ro */
#घोषणा		STEP			0x00000002
#घोषणा		ARP2RESET		0x00000001	/* wo */

#घोषणा ARP2INT		0x04

#घोषणा		HALTCODE_MASK		0x00FF0000	/* ro */
#घोषणा		ARP2WAITTO		0x00000100
#घोषणा		ARP2HALTC		0x00000080
#घोषणा		ARP2ILLOPC		0x00000040
#घोषणा		ARP2PERR		0x00000020
#घोषणा		ARP2CIOPERR		0x00000010
#घोषणा		ARP2BREAK3		0x00000008
#घोषणा		ARP2BREAK2		0x00000004
#घोषणा		ARP2BREAK1		0x00000002
#घोषणा		ARP2BREAK0		0x00000001

#घोषणा ARP2INTEN	0x08

#घोषणा		EN_ARP2WAITTO		0x00000100
#घोषणा		EN_ARP2HALTC		0x00000080
#घोषणा		EN_ARP2ILLOPC		0x00000040
#घोषणा		EN_ARP2PERR		0x00000020
#घोषणा		EN_ARP2CIOPERR		0x00000010
#घोषणा		EN_ARP2BREAK3		0x00000008
#घोषणा		EN_ARP2BREAK2		0x00000004
#घोषणा		EN_ARP2BREAK1		0x00000002
#घोषणा		EN_ARP2BREAK0		0x00000001

#घोषणा ARP2BREAKADR01	0x0C

#घोषणा		BREAKADR1_MASK		0x0FFF0000
#घोषणा		BREAKADR0_MASK		0x00000FFF

#घोषणा	ARP2BREAKADR23	0x10

#घोषणा		BREAKADR3_MASK		0x0FFF0000
#घोषणा		BREAKADR2_MASK		0x00000FFF

/* 0x14h - 0x1Ch are reserved */

/*
 * ARP2 Registers, Address Range : (0x00-0x1F)
 * The definitions have the same address offset क्रम CSEQ and LmSEQ
 * CIO Bus Registers.
 */
#घोषणा MODEPTR		0x00

#घोषणा		DSTMODE			0xF0
#घोषणा		SRCMODE			0x0F

#घोषणा ALTMODE		0x01

#घोषणा		ALTDMODE		0xF0
#घोषणा		ALTSMODE		0x0F

#घोषणा ATOMICXCHG	0x02

#घोषणा FLAG		0x04

#घोषणा		INTCODE_MASK		0xF0
#घोषणा		ALTMODEV2		0x04
#घोषणा		CARRY_INT		0x02
#घोषणा		CARRY			0x01

#घोषणा ARP2INTCTL	0x05

#घोषणा 	PAUSEDIS		0x80
#घोषणा		RSTINTCTL		0x40
#घोषणा		POPALTMODE		0x08
#घोषणा		ALTMODEV		0x04
#घोषणा		INTMASK			0x02
#घोषणा		IRET			0x01

#घोषणा STACK		0x06

#घोषणा FUNCTION1	0x07

#घोषणा PRGMCNT		0x08

#घोषणा ACCUM		0x0A

#घोषणा SINDEX		0x0C

#घोषणा DINDEX		0x0E

#घोषणा ALLONES		0x10

#घोषणा ALLZEROS	0x11

#घोषणा SINसूची		0x12

#घोषणा DINसूची		0x13

#घोषणा JUMLसूची		0x14

#घोषणा ARP2HALTCODE	0x15

#घोषणा CURRADDR	0x16

#घोषणा LASTADDR	0x18

#घोषणा NXTLADDR	0x1A

#घोषणा DBGPORTPTR	0x1C

#घोषणा DBGPORT		0x1D

/*
 * CIO Registers.
 * The definitions have the same address offset क्रम CSEQ and LmSEQ
 * CIO Bus Registers.
 */
#घोषणा MnSCBPTR      	0x20

#घोषणा MnDDBPTR      	0x22

#घोषणा SCRATCHPAGE	0x24

#घोषणा MnSCRATCHPAGE	0x25

#घोषणा SCRATCHPAGESV	0x26

#घोषणा MnSCRATCHPAGESV	0x27

#घोषणा MnDMAERRS	0x46

#घोषणा MnSGDMAERRS	0x47

#घोषणा MnSGBUF		0x53

#घोषणा MnSGDMASTAT	0x5b

#घोषणा MnDDMACTL	0x5c	/* RAZOR.rspec.fm rev 1.5 is wrong */

#घोषणा MnDDMASTAT	0x5d	/* RAZOR.rspec.fm rev 1.5 is wrong */

#घोषणा MnDDMAMODE	0x5e	/* RAZOR.rspec.fm rev 1.5 is wrong */

#घोषणा MnDMAENG	0x60

#घोषणा MnPIPECTL	0x61

#घोषणा MnSGBADR	0x65

#घोषणा MnSCB_SITE	0x100

#घोषणा MnDDB_SITE	0x180

/*
 * The common definitions below have the same address offset क्रम both
 * CSEQ and LmSEQ.
 */
#घोषणा BISTCTL0	0x4C

#घोषणा BISTCTL1	0x50

#घोषणा MAPPEDSCR	0x800

/*
 * CSEQ Host Register, Address Range : (0x000-0xFFC)
 */
#घोषणा CSEQ_HOST_REG_BASE_ADR		0xB8001000

#घोषणा CARP2CTL			(CSEQ_HOST_REG_BASE_ADR	+ ARP2CTL)

#घोषणा CARP2INT			(CSEQ_HOST_REG_BASE_ADR	+ ARP2INT)

#घोषणा CARP2INTEN			(CSEQ_HOST_REG_BASE_ADR	+ ARP2INTEN)

#घोषणा CARP2BREAKADR01			(CSEQ_HOST_REG_BASE_ADR+ARP2BREAKADR01)

#घोषणा CARP2BREAKADR23			(CSEQ_HOST_REG_BASE_ADR+ARP2BREAKADR23)

#घोषणा CBISTCTL			(CSEQ_HOST_REG_BASE_ADR	+ BISTCTL1)

#घोषणा		CSEQRAMBISTEN		0x00000040
#घोषणा		CSEQRAMBISTDN		0x00000020	/* ro */
#घोषणा		CSEQRAMBISTFAIL		0x00000010	/* ro */
#घोषणा		CSEQSCRBISTEN		0x00000004
#घोषणा		CSEQSCRBISTDN		0x00000002	/* ro */
#घोषणा		CSEQSCRBISTFAIL		0x00000001	/* ro */

#घोषणा CMAPPEDSCR			(CSEQ_HOST_REG_BASE_ADR	+ MAPPEDSCR)

/*
 * CSEQ CIO Bus Registers, Address Range : (0x0000-0x1FFC)
 * 16 modes, each mode is 512 bytes.
 * Unless specअगरied, the रेजिस्टर should valid क्रम all modes.
 */
#घोषणा CSEQ_CIO_REG_BASE_ADR		REG_BASE_ADDR_CSEQCIO

#घोषणा CSEQm_CIO_REG(Mode, Reg) \
		(CSEQ_CIO_REG_BASE_ADR  + \
		((u32) (Mode) * CSEQ_MODE_PAGE_SIZE) + (u32) (Reg))

#घोषणा CMODEPTR	(CSEQ_CIO_REG_BASE_ADR + MODEPTR)

#घोषणा CALTMODE	(CSEQ_CIO_REG_BASE_ADR + ALTMODE)

#घोषणा CATOMICXCHG	(CSEQ_CIO_REG_BASE_ADR + ATOMICXCHG)

#घोषणा CFLAG		(CSEQ_CIO_REG_BASE_ADR + FLAG)

#घोषणा CARP2INTCTL	(CSEQ_CIO_REG_BASE_ADR + ARP2INTCTL)

#घोषणा CSTACK		(CSEQ_CIO_REG_BASE_ADR + STACK)

#घोषणा CFUNCTION1	(CSEQ_CIO_REG_BASE_ADR + FUNCTION1)

#घोषणा CPRGMCNT	(CSEQ_CIO_REG_BASE_ADR + PRGMCNT)

#घोषणा CACCUM		(CSEQ_CIO_REG_BASE_ADR + ACCUM)

#घोषणा CSINDEX		(CSEQ_CIO_REG_BASE_ADR + SINDEX)

#घोषणा CDINDEX		(CSEQ_CIO_REG_BASE_ADR + DINDEX)

#घोषणा CALLONES	(CSEQ_CIO_REG_BASE_ADR + ALLONES)

#घोषणा CALLZEROS	(CSEQ_CIO_REG_BASE_ADR + ALLZEROS)

#घोषणा CSINसूची		(CSEQ_CIO_REG_BASE_ADR + SINसूची)

#घोषणा CDINसूची		(CSEQ_CIO_REG_BASE_ADR + DINसूची)

#घोषणा CJUMLसूची	(CSEQ_CIO_REG_BASE_ADR + JUMLसूची)

#घोषणा CARP2HALTCODE	(CSEQ_CIO_REG_BASE_ADR + ARP2HALTCODE)

#घोषणा CCURRADDR	(CSEQ_CIO_REG_BASE_ADR + CURRADDR)

#घोषणा CLASTADDR	(CSEQ_CIO_REG_BASE_ADR + LASTADDR)

#घोषणा CNXTLADDR	(CSEQ_CIO_REG_BASE_ADR + NXTLADDR)

#घोषणा CDBGPORTPTR	(CSEQ_CIO_REG_BASE_ADR + DBGPORTPTR)

#घोषणा CDBGPORT	(CSEQ_CIO_REG_BASE_ADR + DBGPORT)

#घोषणा CSCRATCHPAGE	(CSEQ_CIO_REG_BASE_ADR + SCRATCHPAGE)

#घोषणा CMnSCBPTR(Mode)       CSEQm_CIO_REG(Mode, MnSCBPTR)

#घोषणा CMnDDBPTR(Mode)       CSEQm_CIO_REG(Mode, MnDDBPTR)

#घोषणा CMnSCRATCHPAGE(Mode)		CSEQm_CIO_REG(Mode, MnSCRATCHPAGE)

#घोषणा CLINKCON	(CSEQ_CIO_REG_BASE_ADR + 0x28)

#घोषणा	CCIOAACESS	(CSEQ_CIO_REG_BASE_ADR + 0x2C)

/* mode 0-7 */
#घोषणा MnREQMBX 0x30
#घोषणा CMnREQMBX(Mode)			CSEQm_CIO_REG(Mode, 0x30)

/* mode 8 */
#घोषणा CSEQCON				CSEQm_CIO_REG(8, 0x30)

/* mode 0-7 */
#घोषणा MnRSPMBX 0x34
#घोषणा CMnRSPMBX(Mode)			CSEQm_CIO_REG(Mode, 0x34)

/* mode 8 */
#घोषणा CSEQCOMCTL			CSEQm_CIO_REG(8, 0x34)

/* mode 8 */
#घोषणा CSEQCOMSTAT			CSEQm_CIO_REG(8, 0x35)

/* mode 8 */
#घोषणा CSEQCOMINTEN			CSEQm_CIO_REG(8, 0x36)

/* mode 8 */
#घोषणा CSEQCOMDMACTL			CSEQm_CIO_REG(8, 0x37)

#घोषणा		CSHALTERR		0x10
#घोषणा		RESETCSDMA		0x08		/* wo */
#घोषणा		STARTCSDMA		0x04
#घोषणा		STOPCSDMA		0x02		/* wo */
#घोषणा		CSDMAACT		0x01		/* ro */

/* mode 0-7 */
#घोषणा MnINT 0x38
#घोषणा CMnINT(Mode)			CSEQm_CIO_REG(Mode, 0x38)

#घोषणा		CMnREQMBXE		0x02
#घोषणा		CMnRSPMBXF		0x01
#घोषणा		CMnINT_MASK		0x00000003

/* mode 8 */
#घोषणा CSEQREQMBX			CSEQm_CIO_REG(8, 0x38)

/* mode 0-7 */
#घोषणा MnINTEN 0x3C
#घोषणा CMnINTEN(Mode)			CSEQm_CIO_REG(Mode, 0x3C)

#घोषणा		EN_CMnRSPMBXF		0x01

/* mode 8 */
#घोषणा CSEQRSPMBX			CSEQm_CIO_REG(8, 0x3C)

/* mode 8 */
#घोषणा CSDMAADR			CSEQm_CIO_REG(8, 0x40)

/* mode 8 */
#घोषणा CSDMACNT			CSEQm_CIO_REG(8, 0x48)

/* mode 8 */
#घोषणा CSEQDLCTL			CSEQm_CIO_REG(8, 0x4D)

#घोषणा		DONELISTEND		0x10
#घोषणा 	DONELISTSIZE_MASK	0x0F
#घोषणा		DONELISTSIZE_8ELEM	0x01
#घोषणा		DONELISTSIZE_16ELEM	0x02
#घोषणा		DONELISTSIZE_32ELEM	0x03
#घोषणा		DONELISTSIZE_64ELEM	0x04
#घोषणा		DONELISTSIZE_128ELEM	0x05
#घोषणा		DONELISTSIZE_256ELEM	0x06
#घोषणा		DONELISTSIZE_512ELEM	0x07
#घोषणा		DONELISTSIZE_1024ELEM	0x08
#घोषणा		DONELISTSIZE_2048ELEM	0x09
#घोषणा		DONELISTSIZE_4096ELEM	0x0A
#घोषणा		DONELISTSIZE_8192ELEM	0x0B
#घोषणा		DONELISTSIZE_16384ELEM	0x0C

/* mode 8 */
#घोषणा CSEQDLOFFS			CSEQm_CIO_REG(8, 0x4E)

/* mode 11 */
#घोषणा CM11INTVEC0			CSEQm_CIO_REG(11, 0x50)

/* mode 11 */
#घोषणा CM11INTVEC1			CSEQm_CIO_REG(11, 0x52)

/* mode 11 */
#घोषणा CM11INTVEC2			CSEQm_CIO_REG(11, 0x54)

#घोषणा	CCONMSK	  			(CSEQ_CIO_REG_BASE_ADR + 0x60)

#घोषणा	CCONEXIST			(CSEQ_CIO_REG_BASE_ADR + 0x61)

#घोषणा	CCONMODE			(CSEQ_CIO_REG_BASE_ADR + 0x62)

#घोषणा CTIMERCALC			(CSEQ_CIO_REG_BASE_ADR + 0x64)

#घोषणा CINTDIS				(CSEQ_CIO_REG_BASE_ADR + 0x68)

/* mode 8, 32x32 bits, 128 bytes of mapped buffer */
#घोषणा CSBUFFER			CSEQm_CIO_REG(8, 0x80)

#घोषणा	CSCRATCH			(CSEQ_CIO_REG_BASE_ADR + 0x1C0)

/* mode 0-8 */
#घोषणा CMnSCRATCH(Mode)		CSEQm_CIO_REG(Mode, 0x1E0)

/*
 * CSEQ Mapped Inकाष्ठाion RAM Page, Address Range : (0x0000-0x1FFC)
 */
#घोषणा CSEQ_RAM_REG_BASE_ADR		0xB8004000

/*
 * The common definitions below have the same address offset क्रम all the Link
 * sequencers.
 */
#घोषणा MODECTL		0x40

#घोषणा DBGMODE		0x44

#घोषणा CONTROL		0x48
#घोषणा LEDTIMER		0x00010000
#घोषणा LEDTIMERS_10us		0x00000000
#घोषणा LEDTIMERS_1ms		0x00000800
#घोषणा LEDTIMERS_100ms		0x00001000
#घोषणा LEDMODE_TXRX		0x00000000
#घोषणा LEDMODE_CONNECTED	0x00000200
#घोषणा LEDPOL			0x00000100

#घोषणा LSEQRAM		0x1000

/*
 * LmSEQ Host Registers, Address Range : (0x0000-0x3FFC)
 */
#घोषणा LSEQ0_HOST_REG_BASE_ADR		0xB8020000
#घोषणा LSEQ1_HOST_REG_BASE_ADR		0xB8024000
#घोषणा LSEQ2_HOST_REG_BASE_ADR		0xB8028000
#घोषणा LSEQ3_HOST_REG_BASE_ADR		0xB802C000
#घोषणा LSEQ4_HOST_REG_BASE_ADR		0xB8030000
#घोषणा LSEQ5_HOST_REG_BASE_ADR		0xB8034000
#घोषणा LSEQ6_HOST_REG_BASE_ADR		0xB8038000
#घोषणा LSEQ7_HOST_REG_BASE_ADR		0xB803C000

#घोषणा LmARP2CTL(LinkNum)		(LSEQ0_HOST_REG_BASE_ADR +	  \
					((LinkNum)*LmSEQ_HOST_REG_SIZE) + \
					ARP2CTL)

#घोषणा LmARP2INT(LinkNum)		(LSEQ0_HOST_REG_BASE_ADR +	  \
					((LinkNum)*LmSEQ_HOST_REG_SIZE) + \
					ARP2INT)

#घोषणा LmARP2INTEN(LinkNum)		(LSEQ0_HOST_REG_BASE_ADR +	  \
					((LinkNum)*LmSEQ_HOST_REG_SIZE) + \
					ARP2INTEN)

#घोषणा LmDBGMODE(LinkNum)		(LSEQ0_HOST_REG_BASE_ADR +	  \
					((LinkNum)*LmSEQ_HOST_REG_SIZE) + \
					DBGMODE)

#घोषणा LmCONTROL(LinkNum)		(LSEQ0_HOST_REG_BASE_ADR +	  \
					((LinkNum)*LmSEQ_HOST_REG_SIZE) + \
					CONTROL)

#घोषणा LmARP2BREAKADR01(LinkNum)	(LSEQ0_HOST_REG_BASE_ADR +	  \
					((LinkNum)*LmSEQ_HOST_REG_SIZE) + \
					ARP2BREAKADR01)

#घोषणा LmARP2BREAKADR23(LinkNum)	(LSEQ0_HOST_REG_BASE_ADR +	  \
					((LinkNum)*LmSEQ_HOST_REG_SIZE) + \
					ARP2BREAKADR23)

#घोषणा LmMODECTL(LinkNum)		(LSEQ0_HOST_REG_BASE_ADR +	  \
					((LinkNum)*LmSEQ_HOST_REG_SIZE) + \
					MODECTL)

#घोषणा		LmAUTODISCI		0x08000000
#घोषणा		LmDSBLBITLT		0x04000000
#घोषणा		LmDSBLANTT		0x02000000
#घोषणा		LmDSBLCRTT		0x01000000
#घोषणा		LmDSBLCONT		0x00000100
#घोषणा		LmPRIMODE		0x00000080
#घोषणा		LmDSBLHOLD		0x00000040
#घोषणा		LmDISACK		0x00000020
#घोषणा		LmBLIND48		0x00000010
#घोषणा		LmRCVMODE_MASK		0x0000000C
#घोषणा		LmRCVMODE_PLD		0x00000000
#घोषणा		LmRCVMODE_HPC		0x00000004

#घोषणा LmDBGMODE(LinkNum)		(LSEQ0_HOST_REG_BASE_ADR +	  \
					((LinkNum)*LmSEQ_HOST_REG_SIZE) + \
					DBGMODE)

#घोषणा		LmFRCPERR		0x80000000
#घोषणा		LmMEMSEL_MASK		0x30000000
#घोषणा		LmFRCRBPERR		0x00000000
#घोषणा		LmFRCTBPERR		0x10000000
#घोषणा		LmFRCSGBPERR		0x20000000
#घोषणा		LmFRCARBPERR		0x30000000
#घोषणा		LmRCVIDW		0x00080000
#घोषणा		LmINVDWERR		0x00040000
#घोषणा		LmRCVDISP		0x00004000
#घोषणा		LmDISPERR		0x00002000
#घोषणा		LmDSBLDSCR		0x00000800
#घोषणा		LmDSBLSCR		0x00000400
#घोषणा		LmFRCNAK		0x00000200
#घोषणा		LmFRCROFS		0x00000100
#घोषणा		LmFRCCRC		0x00000080
#घोषणा		LmFRMTYPE_MASK		0x00000070
#घोषणा		LmSG_DATA		0x00000000
#घोषणा		LmSG_COMMAND		0x00000010
#घोषणा		LmSG_TASK		0x00000020
#घोषणा		LmSG_TGTXFER		0x00000030
#घोषणा		LmSG_RESPONSE		0x00000040
#घोषणा		LmSG_IDENADDR		0x00000050
#घोषणा		LmSG_OPENADDR		0x00000060
#घोषणा		LmDISCRCGEN		0x00000008
#घोषणा		LmDISCRCCHK		0x00000004
#घोषणा		LmSSXMTFRM		0x00000002
#घोषणा		LmSSRCVFRM		0x00000001

#घोषणा LmCONTROL(LinkNum)		(LSEQ0_HOST_REG_BASE_ADR +	  \
					((LinkNum)*LmSEQ_HOST_REG_SIZE) + \
					CONTROL)

#घोषणा		LmSTEPXMTFRM		0x00000002
#घोषणा		LmSTEPRCVFRM		0x00000001

#घोषणा LmBISTCTL0(LinkNum)		(LSEQ0_HOST_REG_BASE_ADR +	  \
					((LinkNum)*LmSEQ_HOST_REG_SIZE) + \
					BISTCTL0)

#घोषणा		ARBBISTEN		0x40000000
#घोषणा		ARBBISTDN		0x20000000	/* ro */
#घोषणा		ARBBISTFAIL		0x10000000	/* ro */
#घोषणा		TBBISTEN		0x00000400
#घोषणा		TBBISTDN		0x00000200	/* ro */
#घोषणा		TBBISTFAIL		0x00000100	/* ro */
#घोषणा		RBBISTEN		0x00000040
#घोषणा		RBBISTDN		0x00000020	/* ro */
#घोषणा		RBBISTFAIL		0x00000010	/* ro */
#घोषणा		SGBISTEN		0x00000004
#घोषणा		SGBISTDN		0x00000002	/* ro */
#घोषणा		SGBISTFAIL		0x00000001	/* ro */

#घोषणा LmBISTCTL1(LinkNum)		(LSEQ0_HOST_REG_BASE_ADR +	 \
					((LinkNum)*LmSEQ_HOST_REG_SIZE) +\
					BISTCTL1)

#घोषणा		LmRAMPAGE1		0x00000200
#घोषणा		LmRAMPAGE0		0x00000100
#घोषणा		LmIMEMBISTEN		0x00000040
#घोषणा		LmIMEMBISTDN		0x00000020	/* ro */
#घोषणा		LmIMEMBISTFAIL		0x00000010	/* ro */
#घोषणा		LmSCRBISTEN		0x00000004
#घोषणा		LmSCRBISTDN		0x00000002	/* ro */
#घोषणा		LmSCRBISTFAIL		0x00000001	/* ro */
#घोषणा		LmRAMPAGE		(LmRAMPAGE1 + LmRAMPAGE0)
#घोषणा		LmRAMPAGE_LSHIFT	0x8

#घोषणा LmSCRATCH(LinkNum)		(LSEQ0_HOST_REG_BASE_ADR +	   \
					((LinkNum) * LmSEQ_HOST_REG_SIZE) +\
					MAPPEDSCR)

#घोषणा LmSEQRAM(LinkNum)		(LSEQ0_HOST_REG_BASE_ADR +	   \
					((LinkNum) * LmSEQ_HOST_REG_SIZE) +\
					LSEQRAM)

/*
 * LmSEQ CIO Bus Register, Address Range : (0x0000-0xFFC)
 * 8 modes, each mode is 512 bytes.
 * Unless specअगरied, the रेजिस्टर should valid क्रम all modes.
 */
#घोषणा LmSEQ_CIOBUS_REG_BASE		0x2000

#घोषणा  LmSEQ_PHY_BASE(Mode, LinkNum) \
		(LSEQ0_HOST_REG_BASE_ADR + \
		(LmSEQ_HOST_REG_SIZE * (u32) (LinkNum)) + \
		LmSEQ_CIOBUS_REG_BASE + \
		((u32) (Mode) * LmSEQ_MODE_PAGE_SIZE))

#घोषणा  LmSEQ_PHY_REG(Mode, LinkNum, Reg) \
                 (LmSEQ_PHY_BASE(Mode, LinkNum) + (u32) (Reg))

#घोषणा LmMODEPTR(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, MODEPTR)

#घोषणा LmALTMODE(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, ALTMODE)

#घोषणा LmATOMICXCHG(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, ATOMICXCHG)

#घोषणा LmFLAG(LinkNum)			LmSEQ_PHY_REG(0, LinkNum, FLAG)

#घोषणा LmARP2INTCTL(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, ARP2INTCTL)

#घोषणा LmSTACK(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, STACK)

#घोषणा LmFUNCTION1(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, FUNCTION1)

#घोषणा LmPRGMCNT(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, PRGMCNT)

#घोषणा LmACCUM(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, ACCUM)

#घोषणा LmSINDEX(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, SINDEX)

#घोषणा LmDINDEX(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, DINDEX)

#घोषणा LmALLONES(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, ALLONES)

#घोषणा LmALLZEROS(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, ALLZEROS)

#घोषणा LmSINसूची(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, SINसूची)

#घोषणा LmDINसूची(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, DINसूची)

#घोषणा LmJUMLसूची(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, JUMLसूची)

#घोषणा LmARP2HALTCODE(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, ARP2HALTCODE)

#घोषणा LmCURRADDR(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, CURRADDR)

#घोषणा LmLASTADDR(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, LASTADDR)

#घोषणा LmNXTLADDR(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, NXTLADDR)

#घोषणा LmDBGPORTPTR(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, DBGPORTPTR)

#घोषणा LmDBGPORT(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, DBGPORT)

#घोषणा LmSCRATCHPAGE(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, SCRATCHPAGE)

#घोषणा LmMnSCRATCHPAGE(LinkNum, Mode)	LmSEQ_PHY_REG(Mode, LinkNum, 	\
						      MnSCRATCHPAGE)

#घोषणा LmTIMERCALC(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, 0x28)

#घोषणा LmREQMBX(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, 0x30)

#घोषणा LmRSPMBX(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, 0x34)

#घोषणा LmMnINT(LinkNum, Mode)		LmSEQ_PHY_REG(Mode, LinkNum, 0x38)

#घोषणा		CTXMEMSIZE		0x80000000	/* ro */
#घोषणा		LmACKREQ		0x08000000
#घोषणा		LmNAKREQ		0x04000000
#घोषणा		LmMnXMTERR		0x02000000
#घोषणा		LmM5OOBSVC		0x01000000
#घोषणा		LmHWTINT		0x00800000
#घोषणा		LmMnCTXDONE		0x00100000
#घोषणा		LmM2REQMBXF		0x00080000
#घोषणा		LmM2RSPMBXE		0x00040000
#घोषणा		LmMnDMAERR		0x00020000
#घोषणा		LmRCVPRIM		0x00010000
#घोषणा		LmRCVERR		0x00008000
#घोषणा		LmADDRRCV		0x00004000
#घोषणा		LmMnHDRMISS		0x00002000
#घोषणा		LmMnWAITSCB		0x00001000
#घोषणा		LmMnRLSSCB		0x00000800
#घोषणा		LmMnSAVECTX		0x00000400
#घोषणा		LmMnFETCHSG		0x00000200
#घोषणा		LmMnLOADCTX		0x00000100
#घोषणा		LmMnCFGICL		0x00000080
#घोषणा		LmMnCFGSATA		0x00000040
#घोषणा		LmMnCFGEXPSATA		0x00000020
#घोषणा		LmMnCFGCMPLT		0x00000010
#घोषणा		LmMnCFGRBUF		0x00000008
#घोषणा		LmMnSAVETTR		0x00000004
#घोषणा		LmMnCFGRDAT		0x00000002
#घोषणा		LmMnCFGHDR		0x00000001

#घोषणा LmMnINTEN(LinkNum, Mode)	LmSEQ_PHY_REG(Mode, LinkNum, 0x3C)

#घोषणा		EN_LmACKREQ		0x08000000
#घोषणा		EN_LmNAKREQ		0x04000000
#घोषणा		EN_LmMnXMTERR		0x02000000
#घोषणा		EN_LmM5OOBSVC		0x01000000
#घोषणा		EN_LmHWTINT		0x00800000
#घोषणा		EN_LmMnCTXDONE		0x00100000
#घोषणा		EN_LmM2REQMBXF		0x00080000
#घोषणा		EN_LmM2RSPMBXE		0x00040000
#घोषणा		EN_LmMnDMAERR		0x00020000
#घोषणा		EN_LmRCVPRIM		0x00010000
#घोषणा		EN_LmRCVERR		0x00008000
#घोषणा		EN_LmADDRRCV		0x00004000
#घोषणा		EN_LmMnHDRMISS		0x00002000
#घोषणा		EN_LmMnWAITSCB		0x00001000
#घोषणा		EN_LmMnRLSSCB		0x00000800
#घोषणा		EN_LmMnSAVECTX		0x00000400
#घोषणा		EN_LmMnFETCHSG		0x00000200
#घोषणा		EN_LmMnLOADCTX		0x00000100
#घोषणा		EN_LmMnCFGICL		0x00000080
#घोषणा		EN_LmMnCFGSATA		0x00000040
#घोषणा		EN_LmMnCFGEXPSATA	0x00000020
#घोषणा		EN_LmMnCFGCMPLT		0x00000010
#घोषणा		EN_LmMnCFGRBUF		0x00000008
#घोषणा		EN_LmMnSAVETTR		0x00000004
#घोषणा		EN_LmMnCFGRDAT		0x00000002
#घोषणा		EN_LmMnCFGHDR		0x00000001

#घोषणा		LmM0INTEN_MASK		(EN_LmMnCFGCMPLT | EN_LmMnCFGRBUF | \
					 EN_LmMnSAVETTR | EN_LmMnCFGRDAT | \
					 EN_LmMnCFGHDR | EN_LmRCVERR | \
					 EN_LmADDRRCV | EN_LmMnHDRMISS | \
					 EN_LmMnRLSSCB | EN_LmMnSAVECTX | \
					 EN_LmMnFETCHSG | EN_LmMnLOADCTX | \
					 EN_LmHWTINT | EN_LmMnCTXDONE | \
					 EN_LmRCVPRIM | EN_LmMnCFGSATA | \
					 EN_LmMnCFGEXPSATA | EN_LmMnDMAERR)

#घोषणा		LmM1INTEN_MASK		(EN_LmMnCFGCMPLT | EN_LmADDRRCV | \
					 EN_LmMnRLSSCB | EN_LmMnSAVECTX | \
					 EN_LmMnFETCHSG | EN_LmMnLOADCTX | \
					 EN_LmMnXMTERR | EN_LmHWTINT | \
					 EN_LmMnCTXDONE | EN_LmRCVPRIM | \
					 EN_LmRCVERR | EN_LmMnDMAERR)

#घोषणा		LmM2INTEN_MASK		(EN_LmADDRRCV | EN_LmHWTINT | \
					 EN_LmM2REQMBXF | EN_LmRCVPRIM | \
					 EN_LmRCVERR)

#घोषणा		LmM5INTEN_MASK		(EN_LmADDRRCV | EN_LmM5OOBSVC | \
					 EN_LmHWTINT | EN_LmRCVPRIM | \
					 EN_LmRCVERR)

#घोषणा LmXMTPRIMD(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, 0x40)

#घोषणा LmXMTPRIMCS(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, 0x44)

#घोषणा LmCONSTAT(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, 0x45)

#घोषणा LmMnDMAERRS(LinkNum, Mode)	LmSEQ_PHY_REG(Mode, LinkNum, 0x46)

#घोषणा LmMnSGDMAERRS(LinkNum, Mode)	LmSEQ_PHY_REG(Mode, LinkNum, 0x47)

#घोषणा LmM0EXPHDRP(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, 0x48)

#घोषणा LmM1SASALIGN(LinkNum)		LmSEQ_PHY_REG(1, LinkNum, 0x48)
#घोषणा SAS_ALIGN_DEFAULT		0xFF

#घोषणा LmM0MSKHDRP(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, 0x49)

#घोषणा LmM1STPALIGN(LinkNum)		LmSEQ_PHY_REG(1, LinkNum, 0x49)
#घोषणा STP_ALIGN_DEFAULT		0x1F

#घोषणा LmM0RCVHDRP(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, 0x4A)

#घोषणा LmM1XMTHDRP(LinkNum)		LmSEQ_PHY_REG(1, LinkNum, 0x4A)

#घोषणा LmM0ICLADR(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, 0x4B)

#घोषणा LmM1ALIGNMODE(LinkNum)		LmSEQ_PHY_REG(1, LinkNum, 0x4B)

#घोषणा		LmDISALIGN		0x20
#घोषणा		LmROTSTPALIGN		0x10
#घोषणा		LmSTPALIGN		0x08
#घोषणा		LmROTNOTIFY		0x04
#घोषणा		LmDUALALIGN		0x02
#घोषणा		LmROTALIGN		0x01

#घोषणा LmM0EXPRCVNT(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, 0x4C)

#घोषणा LmM1XMTCNT(LinkNum)		LmSEQ_PHY_REG(1, LinkNum, 0x4C)

#घोषणा LmMnBUFSTAT(LinkNum, Mode)	LmSEQ_PHY_REG(Mode, LinkNum, 0x4E)

#घोषणा		LmMnBUFPERR		0x01

/* mode 0-1 */
#घोषणा LmMnXFRLVL(LinkNum, Mode)	LmSEQ_PHY_REG(Mode, LinkNum, 0x59)

#घोषणा		LmMnXFRLVL_128		0x05
#घोषणा		LmMnXFRLVL_256		0x04
#घोषणा		LmMnXFRLVL_512		0x03
#घोषणा		LmMnXFRLVL_1024		0x02
#घोषणा		LmMnXFRLVL_1536		0x01
#घोषणा		LmMnXFRLVL_2048		0x00

 /* mode 0-1 */
#घोषणा LmMnSGDMACTL(LinkNum, Mode)	LmSEQ_PHY_REG(Mode, LinkNum, 0x5A)

#घोषणा 	LmMnRESETSG		0x04
#घोषणा 	LmMnSTOPSG		0x02
#घोषणा 	LmMnSTARTSG		0x01

/* mode 0-1 */
#घोषणा LmMnSGDMASTAT(LinkNum, Mode)	LmSEQ_PHY_REG(Mode, LinkNum, 0x5B)

/* mode 0-1 */
#घोषणा LmMnDDMACTL(LinkNum, Mode)	LmSEQ_PHY_REG(Mode, LinkNum, 0x5C)

#घोषणा 	LmMnFLUSH		0x40		/* wo */
#घोषणा 	LmMnRLSRTRY		0x20		/* wo */
#घोषणा 	LmMnDISCARD		0x10		/* wo */
#घोषणा 	LmMnRESETDAT		0x08		/* wo */
#घोषणा 	LmMnSUSDAT		0x04		/* wo */
#घोषणा 	LmMnSTOPDAT		0x02		/* wo */
#घोषणा 	LmMnSTARTDAT		0x01		/* wo */

/* mode 0-1 */
#घोषणा LmMnDDMASTAT(LinkNum, Mode)	LmSEQ_PHY_REG(Mode, LinkNum, 0x5D)

#घोषणा		LmMnDPEMPTY		0x80
#घोषणा		LmMnFLUSHING		0x40
#घोषणा		LmMnDDMAREQ		0x20
#घोषणा		LmMnHDMAREQ		0x10
#घोषणा		LmMnDATFREE		0x08
#घोषणा		LmMnDATSUS		0x04
#घोषणा		LmMnDATACT		0x02
#घोषणा		LmMnDATEN		0x01

/* mode 0-1 */
#घोषणा LmMnDDMAMODE(LinkNum, Mode)	LmSEQ_PHY_REG(Mode, LinkNum, 0x5E)

#घोषणा 	LmMnDMATYPE_NORMAL		0x0000
#घोषणा 	LmMnDMATYPE_HOST_ONLY_TX	0x0001
#घोषणा 	LmMnDMATYPE_DEVICE_ONLY_TX	0x0002
#घोषणा 	LmMnDMATYPE_INVALID		0x0003
#घोषणा 	LmMnDMATYPE_MASK	0x0003

#घोषणा 	LmMnDMAWRAP		0x0004
#घोषणा 	LmMnBITBUCKET		0x0008
#घोषणा 	LmMnDISHDR		0x0010
#घोषणा 	LmMnSTPCRC		0x0020
#घोषणा 	LmXTEST			0x0040
#घोषणा 	LmMnDISCRC		0x0080
#घोषणा 	LmMnENINTLK		0x0100
#घोषणा 	LmMnADDRFRM		0x0400
#घोषणा 	LmMnENXMTCRC		0x0800

/* mode 0-1 */
#घोषणा LmMnXFRCNT(LinkNum, Mode)	LmSEQ_PHY_REG(Mode, LinkNum, 0x70)

/* mode 0-1 */
#घोषणा LmMnDPSEL(LinkNum, Mode)	LmSEQ_PHY_REG(Mode, LinkNum, 0x7B)
#घोषणा 	LmMnDPSEL_MASK		0x07
#घोषणा 	LmMnEOLPRE		0x40
#घोषणा 	LmMnEOSPRE		0x80

/* Registers used in conjunction with LmMnDPSEL and LmMnDPACC रेजिस्टरs */
/* Receive Mode n = 0 */
#घोषणा LmMnHRADDR			0x00
#घोषणा LmMnHBYTECNT			0x01
#घोषणा LmMnHREWIND			0x02
#घोषणा LmMnDWADDR			0x03
#घोषणा LmMnDSPACECNT			0x04
#घोषणा LmMnDFRMSIZE			0x05

/* Registers used in conjunction with LmMnDPSEL and LmMnDPACC रेजिस्टरs */
/* Transmit Mode n = 1 */
#घोषणा LmMnHWADDR			0x00
#घोषणा LmMnHSPACECNT			0x01
/* #घोषणा LmMnHREWIND			0x02 */
#घोषणा LmMnDRADDR			0x03
#घोषणा LmMnDBYTECNT			0x04
/* #घोषणा LmMnDFRMSIZE			0x05 */

/* mode 0-1 */
#घोषणा LmMnDPACC(LinkNum, Mode)	LmSEQ_PHY_REG(Mode, LinkNum, 0x78)
#घोषणा 	LmMnDPACC_MASK		0x00FFFFFF

/* mode 0-1 */
#घोषणा LmMnHOLDLVL(LinkNum, Mode)	LmSEQ_PHY_REG(Mode, LinkNum, 0x7D)

#घोषणा LmPRMSTAT0(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, 0x80)
#घोषणा LmPRMSTAT0BYTE0			0x80
#घोषणा LmPRMSTAT0BYTE1			0x81
#घोषणा LmPRMSTAT0BYTE2			0x82
#घोषणा LmPRMSTAT0BYTE3			0x83

#घोषणा		LmFRAMERCVD		0x80000000
#घोषणा		LmXFRRDYRCVD		0x40000000
#घोषणा		LmUNKNOWNP		0x20000000
#घोषणा		LmBREAK			0x10000000
#घोषणा		LmDONE			0x08000000
#घोषणा		LmOPENACPT		0x04000000
#घोषणा		LmOPENRJCT		0x02000000
#घोषणा		LmOPENRTRY		0x01000000
#घोषणा		LmCLOSERV1		0x00800000
#घोषणा		LmCLOSERV0		0x00400000
#घोषणा		LmCLOSENORM		0x00200000
#घोषणा		LmCLOSECLAF		0x00100000
#घोषणा		LmNOTIFYRV2		0x00080000
#घोषणा		LmNOTIFYRV1		0x00040000
#घोषणा		LmNOTIFYRV0		0x00020000
#घोषणा		LmNOTIFYSPIN		0x00010000
#घोषणा		LmBROADRV4		0x00008000
#घोषणा		LmBROADRV3		0x00004000
#घोषणा		LmBROADRV2		0x00002000
#घोषणा		LmBROADRV1		0x00001000
#घोषणा		LmBROADSES		0x00000800
#घोषणा		LmBROADRVCH1		0x00000400
#घोषणा		LmBROADRVCH0		0x00000200
#घोषणा		LmBROADCH		0x00000100
#घोषणा		LmAIPRVWP		0x00000080
#घोषणा		LmAIPWP			0x00000040
#घोषणा		LmAIPWD			0x00000020
#घोषणा		LmAIPWC			0x00000010
#घोषणा		LmAIPRV2		0x00000008
#घोषणा		LmAIPRV1		0x00000004
#घोषणा		LmAIPRV0		0x00000002
#घोषणा		LmAIPNRML		0x00000001

#घोषणा		LmBROADCAST_MASK	(LmBROADCH | LmBROADRVCH0 | \
					 LmBROADRVCH1)

#घोषणा LmPRMSTAT1(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, 0x84)
#घोषणा LmPRMSTAT1BYTE0			0x84
#घोषणा LmPRMSTAT1BYTE1			0x85
#घोषणा LmPRMSTAT1BYTE2			0x86
#घोषणा LmPRMSTAT1BYTE3			0x87

#घोषणा		LmFRMRCVDSTAT		0x80000000
#घोषणा		LmBREAK_DET		0x04000000
#घोषणा		LmCLOSE_DET		0x02000000
#घोषणा		LmDONE_DET		0x01000000
#घोषणा		LmXRDY			0x00040000
#घोषणा 	LmSYNCSRST		0x00020000
#घोषणा 	LmSYNC			0x00010000
#घोषणा 	LmXHOLD			0x00008000
#घोषणा 	LmRRDY			0x00004000
#घोषणा 	LmHOLD			0x00002000
#घोषणा 	LmROK			0x00001000
#घोषणा 	LmRIP			0x00000800
#घोषणा 	LmCRBLK			0x00000400
#घोषणा 	LmACK			0x00000200
#घोषणा 	LmNAK			0x00000100
#घोषणा 	LmHARDRST		0x00000080
#घोषणा 	LmERROR			0x00000040
#घोषणा 	LmRERR			0x00000020
#घोषणा 	LmPMREQP		0x00000010
#घोषणा 	LmPMREQS		0x00000008
#घोषणा 	LmPMACK			0x00000004
#घोषणा 	LmPMNAK			0x00000002
#घोषणा 	LmDMAT			0x00000001

/* mode 1 */
#घोषणा	LmMnSATAFS(LinkNum, Mode)	LmSEQ_PHY_REG(Mode, LinkNum, 0x7E)
#घोषणा	LmMnXMTSIZE(LinkNum, Mode)	LmSEQ_PHY_REG(Mode, LinkNum, 0x93)

/* mode 0 */
#घोषणा LmMnFRMERR(LinkNum, Mode)	LmSEQ_PHY_REG(Mode, LinkNum, 0xB0)

#घोषणा		LmACRCERR		0x00000800
#घोषणा		LmPHYOVRN		0x00000400
#घोषणा		LmOBOVRN		0x00000200
#घोषणा 	LmMnZERODATA		0x00000100
#घोषणा		LmSATAINTLK		0x00000080
#घोषणा		LmMnCRCERR		0x00000020
#घोषणा		LmRRDYOVRN		0x00000010
#घोषणा		LmMISSSOAF		0x00000008
#घोषणा		LmMISSSOF		0x00000004
#घोषणा		LmMISSEOAF		0x00000002
#घोषणा		LmMISSखातापूर्ण		0x00000001

#घोषणा LmFRMERREN(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, 0xB4)

#घोषणा 	EN_LmACRCERR		0x00000800
#घोषणा 	EN_LmPHYOVRN		0x00000400
#घोषणा 	EN_LmOBOVRN		0x00000200
#घोषणा 	EN_LmMnZERODATA		0x00000100
#घोषणा 	EN_LmSATAINTLK		0x00000080
#घोषणा 	EN_LmFRMBAD		0x00000040
#घोषणा 	EN_LmMnCRCERR		0x00000020
#घोषणा 	EN_LmRRDYOVRN		0x00000010
#घोषणा 	EN_LmMISSSOAF		0x00000008
#घोषणा 	EN_LmMISSSOF		0x00000004
#घोषणा 	EN_LmMISSEOAF		0x00000002
#घोषणा 	EN_LmMISSखातापूर्ण		0x00000001

#घोषणा 	LmFRMERREN_MASK  	(EN_LmSATAINTLK | EN_LmMnCRCERR | \
					 EN_LmRRDYOVRN | EN_LmMISSSOF | \
					 EN_LmMISSEOAF | EN_LmMISSखातापूर्ण | \
					 EN_LmACRCERR | LmPHYOVRN | \
					 EN_LmOBOVRN | EN_LmMnZERODATA)

#घोषणा LmHWTSTATEN(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, 0xC5)

#घोषणा		EN_LmDONETO		0x80
#घोषणा		EN_LmINVDISP		0x40
#घोषणा		EN_LmINVDW		0x20
#घोषणा		EN_LmDWSEVENT		0x08
#घोषणा		EN_LmCRTTTO		0x04
#घोषणा		EN_LmANTTTO		0x02
#घोषणा		EN_LmBITLTTO		0x01

#घोषणा		LmHWTSTATEN_MASK	(EN_LmINVDISP | EN_LmINVDW | \
					 EN_LmDWSEVENT | EN_LmCRTTTO | \
					 EN_LmANTTTO | EN_LmDONETO | \
					 EN_LmBITLTTO)

#घोषणा LmHWTSTAT(LinkNum) 		LmSEQ_PHY_REG(0, LinkNum, 0xC7)

#घोषणा		LmDONETO		0x80
#घोषणा		LmINVDISP		0x40
#घोषणा		LmINVDW			0x20
#घोषणा		LmDWSEVENT		0x08
#घोषणा		LmCRTTTO		0x04
#घोषणा		LmANTTTO		0x02
#घोषणा		LmBITLTTO		0x01

#घोषणा LmMnDATABUFADR(LinkNum, Mode)	LmSEQ_PHY_REG(Mode, LinkNum, 0xC8)
#घोषणा		LmDATABUFADR_MASK	0x0FFF

#घोषणा LmMnDATABUF(LinkNum, Mode)	LmSEQ_PHY_REG(Mode, LinkNum, 0xCA)

#घोषणा	LmPRIMSTAT0EN(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, 0xE0)

#घोषणा 	EN_LmUNKNOWNP 		0x20000000
#घोषणा 	EN_LmBREAK		0x10000000
#घोषणा 	EN_LmDONE		0x08000000
#घोषणा 	EN_LmOPENACPT		0x04000000
#घोषणा 	EN_LmOPENRJCT		0x02000000
#घोषणा 	EN_LmOPENRTRY		0x01000000
#घोषणा 	EN_LmCLOSERV1		0x00800000
#घोषणा 	EN_LmCLOSERV0		0x00400000
#घोषणा 	EN_LmCLOSENORM		0x00200000
#घोषणा 	EN_LmCLOSECLAF		0x00100000
#घोषणा 	EN_LmNOTIFYRV2		0x00080000
#घोषणा 	EN_LmNOTIFYRV1		0x00040000
#घोषणा 	EN_LmNOTIFYRV0		0x00020000
#घोषणा 	EN_LmNOTIFYSPIN		0x00010000
#घोषणा 	EN_LmBROADRV4		0x00008000
#घोषणा 	EN_LmBROADRV3		0x00004000
#घोषणा 	EN_LmBROADRV2		0x00002000
#घोषणा 	EN_LmBROADRV1		0x00001000
#घोषणा 	EN_LmBROADRV0		0x00000800
#घोषणा 	EN_LmBROADRVCH1		0x00000400
#घोषणा 	EN_LmBROADRVCH0		0x00000200
#घोषणा 	EN_LmBROADCH		0x00000100
#घोषणा 	EN_LmAIPRVWP		0x00000080
#घोषणा 	EN_LmAIPWP		0x00000040
#घोषणा 	EN_LmAIPWD		0x00000020
#घोषणा 	EN_LmAIPWC		0x00000010
#घोषणा 	EN_LmAIPRV2		0x00000008
#घोषणा 	EN_LmAIPRV1		0x00000004
#घोषणा 	EN_LmAIPRV0		0x00000002
#घोषणा 	EN_LmAIPNRML		0x00000001

#घोषणा		LmPRIMSTAT0EN_MASK	(EN_LmBREAK | \
					 EN_LmDONE | EN_LmOPENACPT | \
					 EN_LmOPENRJCT | EN_LmOPENRTRY | \
					 EN_LmCLOSERV1 | EN_LmCLOSERV0 | \
					 EN_LmCLOSENORM | EN_LmCLOSECLAF | \
					 EN_LmBROADRV4 | EN_LmBROADRV3 | \
					 EN_LmBROADRV2 | EN_LmBROADRV1 | \
					 EN_LmBROADRV0 | EN_LmBROADRVCH1 | \
					 EN_LmBROADRVCH0 | EN_LmBROADCH | \
					 EN_LmAIPRVWP | EN_LmAIPWP | \
					 EN_LmAIPWD | EN_LmAIPWC | \
					 EN_LmAIPRV2 | EN_LmAIPRV1 | \
					 EN_LmAIPRV0 | EN_LmAIPNRML)

#घोषणा LmPRIMSTAT1EN(LinkNum)		LmSEQ_PHY_REG(0, LinkNum, 0xE4)

#घोषणा		EN_LmXRDY		0x00040000
#घोषणा		EN_LmSYNCSRST		0x00020000
#घोषणा		EN_LmSYNC		0x00010000
#घोषणा 	EN_LmXHOLD		0x00008000
#घोषणा 	EN_LmRRDY		0x00004000
#घोषणा 	EN_LmHOLD		0x00002000
#घोषणा 	EN_LmROK		0x00001000
#घोषणा 	EN_LmRIP		0x00000800
#घोषणा 	EN_LmCRBLK		0x00000400
#घोषणा 	EN_LmACK		0x00000200
#घोषणा 	EN_LmNAK		0x00000100
#घोषणा 	EN_LmHARDRST		0x00000080
#घोषणा 	EN_LmERROR		0x00000040
#घोषणा 	EN_LmRERR		0x00000020
#घोषणा 	EN_LmPMREQP		0x00000010
#घोषणा 	EN_LmPMREQS		0x00000008
#घोषणा 	EN_LmPMACK		0x00000004
#घोषणा 	EN_LmPMNAK		0x00000002
#घोषणा 	EN_LmDMAT		0x00000001

#घोषणा LmPRIMSTAT1EN_MASK		(EN_LmHARDRST | \
					 EN_LmSYNCSRST | \
					 EN_LmPMREQP | EN_LmPMREQS | \
					 EN_LmPMACK | EN_LmPMNAK)

#घोषणा LmSMSTATE(LinkNum) 		LmSEQ_PHY_REG(0, LinkNum, 0xE8)

#घोषणा LmSMSTATEBRK(LinkNum) 		LmSEQ_PHY_REG(0, LinkNum, 0xEC)

#घोषणा LmSMDBGCTL(LinkNum) 		LmSEQ_PHY_REG(0, LinkNum, 0xF0)


/*
 * LmSEQ CIO Bus Mode 3 Register.
 * Mode 3: Configuration and Setup, IOP Context SCB.
 */
#घोषणा LmM3SATATIMER(LinkNum) 		LmSEQ_PHY_REG(3, LinkNum, 0x48)

#घोषणा LmM3INTVEC0(LinkNum)		LmSEQ_PHY_REG(3, LinkNum, 0x90)

#घोषणा LmM3INTVEC1(LinkNum)		LmSEQ_PHY_REG(3, LinkNum, 0x92)

#घोषणा LmM3INTVEC2(LinkNum)		LmSEQ_PHY_REG(3, LinkNum, 0x94)

#घोषणा LmM3INTVEC3(LinkNum)		LmSEQ_PHY_REG(3, LinkNum, 0x96)

#घोषणा LmM3INTVEC4(LinkNum)		LmSEQ_PHY_REG(3, LinkNum, 0x98)

#घोषणा LmM3INTVEC5(LinkNum)		LmSEQ_PHY_REG(3, LinkNum, 0x9A)

#घोषणा LmM3INTVEC6(LinkNum)		LmSEQ_PHY_REG(3, LinkNum, 0x9C)

#घोषणा LmM3INTVEC7(LinkNum)		LmSEQ_PHY_REG(3, LinkNum, 0x9E)

#घोषणा LmM3INTVEC8(LinkNum)		LmSEQ_PHY_REG(3, LinkNum, 0xA4)

#घोषणा LmM3INTVEC9(LinkNum)		LmSEQ_PHY_REG(3, LinkNum, 0xA6)

#घोषणा LmM3INTVEC10(LinkNum)		LmSEQ_PHY_REG(3, LinkNum, 0xB0)

#घोषणा LmM3FRMGAP(LinkNum)		LmSEQ_PHY_REG(3, LinkNum, 0xB4)

#घोषणा LmBITL_TIMER(LinkNum) 		LmSEQ_PHY_REG(0, LinkNum, 0xA2)

#घोषणा LmWWN(LinkNum) 			LmSEQ_PHY_REG(0, LinkNum, 0xA8)


/*
 * LmSEQ CIO Bus Mode 5 Registers.
 * Mode 5: Phy/OOB Control and Status.
 */
#घोषणा LmSEQ_OOB_REG(phy_id, reg)	LmSEQ_PHY_REG(5, (phy_id), (reg))

#घोषणा OOB_BFLTR	0x100

#घोषणा		BFLTR_THR_MASK		0xF0
#घोषणा		BFLTR_TC_MASK		0x0F

#घोषणा OOB_INIT_MIN	0x102

#घोषणा OOB_INIT_MAX	0x104

#घोषणा OOB_INIT_NEG	0x106

#घोषणा	OOB_SAS_MIN	0x108

#घोषणा OOB_SAS_MAX	0x10A

#घोषणा OOB_SAS_NEG	0x10C

#घोषणा OOB_WAKE_MIN	0x10E

#घोषणा OOB_WAKE_MAX	0x110

#घोषणा OOB_WAKE_NEG	0x112

#घोषणा OOB_IDLE_MAX	0x114

#घोषणा OOB_BURST_MAX	0x116

#घोषणा OOB_DATA_KBITS	0x126

#घोषणा OOB_ALIGN_0_DATA	0x12C

#घोषणा OOB_ALIGN_1_DATA	0x130

#घोषणा D10_2_DATA_k		0x00
#घोषणा SYNC_DATA_k		0x02
#घोषणा ALIGN_1_DATA_k		0x04
#घोषणा ALIGN_0_DATA_k		0x08
#घोषणा BURST_DATA_k		0x10

#घोषणा OOB_PHY_RESET_COUNT	0x13C

#घोषणा OOB_SIG_GEN	0x140

#घोषणा		START_OOB		0x80
#घोषणा		START_DWS		0x40
#घोषणा		ALIGN_CNT3		0x30
#घोषणा 	ALIGN_CNT2		0x20
#घोषणा 	ALIGN_CNT1		0x10
#घोषणा 	ALIGN_CNT4		0x00
#घोषणा		STOP_DWS		0x08
#घोषणा		SEND_COMSAS		0x04
#घोषणा		SEND_COMINIT		0x02
#घोषणा		SEND_COMWAKE		0x01

#घोषणा OOB_XMIT	0x141

#घोषणा		TX_ENABLE		0x80
#घोषणा		XMIT_OOB_BURST		0x10
#घोषणा		XMIT_D10_2		0x08
#घोषणा		XMIT_SYNC		0x04
#घोषणा		XMIT_ALIGN_1		0x02
#घोषणा		XMIT_ALIGN_0		0x01

#घोषणा FUNCTION_MASK	0x142

#घोषणा		SAS_MODE_DIS		0x80
#घोषणा		SATA_MODE_DIS		0x40
#घोषणा		SPINUP_HOLD_DIS		0x20
#घोषणा		HOT_PLUG_DIS		0x10
#घोषणा		SATA_PS_DIS		0x08
#घोषणा		FUNCTION_MASK_DEFAULT	(SPINUP_HOLD_DIS | SATA_PS_DIS)

#घोषणा OOB_MODE	0x143

#घोषणा		SAS_MODE		0x80
#घोषणा		SATA_MODE		0x40
#घोषणा		SLOW_CLK		0x20
#घोषणा		FORCE_XMIT_15		0x08
#घोषणा		PHY_SPEED_60		0x04
#घोषणा		PHY_SPEED_30		0x02
#घोषणा		PHY_SPEED_15		0x01

#घोषणा	CURRENT_STATUS	0x144

#घोषणा		CURRENT_OOB_DONE	0x80
#घोषणा		CURRENT_LOSS_OF_SIGNAL	0x40
#घोषणा		CURRENT_SPINUP_HOLD	0x20
#घोषणा		CURRENT_HOT_PLUG_CNCT	0x10
#घोषणा		CURRENT_GTO_TIMEOUT	0x08
#घोषणा		CURRENT_OOB_TIMEOUT	0x04
#घोषणा		CURRENT_DEVICE_PRESENT	0x02
#घोषणा		CURRENT_OOB_ERROR	0x01

#घोषणा 	CURRENT_OOB1_ERROR	(CURRENT_HOT_PLUG_CNCT | \
					 CURRENT_GTO_TIMEOUT)

#घोषणा 	CURRENT_OOB2_ERROR	(CURRENT_HOT_PLUG_CNCT | \
					 CURRENT_OOB_ERROR)

#घोषणा		DEVICE_ADDED_W_CNT	(CURRENT_OOB_DONE | \
					 CURRENT_HOT_PLUG_CNCT | \
					 CURRENT_DEVICE_PRESENT)

#घोषणा		DEVICE_ADDED_WO_CNT	(CURRENT_OOB_DONE | \
					 CURRENT_DEVICE_PRESENT)

#घोषणा 	DEVICE_REMOVED		CURRENT_LOSS_OF_SIGNAL

#घोषणा		CURRENT_PHY_MASK	(CURRENT_OOB_DONE | \
					 CURRENT_LOSS_OF_SIGNAL | \
					 CURRENT_SPINUP_HOLD | \
					 CURRENT_HOT_PLUG_CNCT | \
					 CURRENT_GTO_TIMEOUT | \
					 CURRENT_DEVICE_PRESENT | \
					 CURRENT_OOB_ERROR )

#घोषणा		CURRENT_ERR_MASK	(CURRENT_LOSS_OF_SIGNAL | \
					 CURRENT_GTO_TIMEOUT | \
					 CURRENT_OOB_TIMEOUT | \
					 CURRENT_OOB_ERROR )

#घोषणा SPEED_MASK	0x145

#घोषणा		SATA_SPEED_30_DIS	0x10
#घोषणा		SATA_SPEED_15_DIS	0x08
#घोषणा		SAS_SPEED_60_DIS	0x04
#घोषणा		SAS_SPEED_30_DIS	0x02
#घोषणा		SAS_SPEED_15_DIS	0x01
#घोषणा		SAS_SPEED_MASK_DEFAULT	0x00

#घोषणा OOB_TIMER_ENABLE	0x14D

#घोषणा		HOT_PLUG_EN		0x80
#घोषणा		RCD_EN			0x40
#घोषणा 	COMTIMER_EN		0x20
#घोषणा		SNTT_EN			0x10
#घोषणा		SNLT_EN			0x04
#घोषणा		SNWT_EN			0x02
#घोषणा		ALIGN_EN		0x01

#घोषणा OOB_STATUS		0x14E

#घोषणा		OOB_DONE		0x80
#घोषणा		LOSS_OF_SIGNAL		0x40		/* ro */
#घोषणा		SPINUP_HOLD		0x20
#घोषणा		HOT_PLUG_CNCT		0x10		/* ro */
#घोषणा		GTO_TIMEOUT		0x08		/* ro */
#घोषणा		OOB_TIMEOUT		0x04		/* ro */
#घोषणा		DEVICE_PRESENT		0x02		/* ro */
#घोषणा		OOB_ERROR		0x01		/* ro */

#घोषणा		OOB_STATUS_ERROR_MASK	(LOSS_OF_SIGNAL | GTO_TIMEOUT | \
					 OOB_TIMEOUT | OOB_ERROR)

#घोषणा OOB_STATUS_CLEAR	0x14F

#घोषणा		OOB_DONE_CLR		0x80
#घोषणा		LOSS_OF_SIGNAL_CLR 	0x40
#घोषणा		SPINUP_HOLD_CLR		0x20
#घोषणा		HOT_PLUG_CNCT_CLR     	0x10
#घोषणा		GTO_TIMEOUT_CLR		0x08
#घोषणा		OOB_TIMEOUT_CLR		0x04
#घोषणा		OOB_ERROR_CLR		0x01

#घोषणा HOT_PLUG_DELAY		0x150
/* In 5 ms units. 20 = 100 ms. */
#घोषणा	HOTPLUG_DELAY_TIMEOUT		20


#घोषणा INT_ENABLE_2		0x15A

#घोषणा		OOB_DONE_EN		0x80
#घोषणा		LOSS_OF_SIGNAL_EN	0x40
#घोषणा		SPINUP_HOLD_EN		0x20
#घोषणा		HOT_PLUG_CNCT_EN	0x10
#घोषणा		GTO_TIMEOUT_EN		0x08
#घोषणा		OOB_TIMEOUT_EN		0x04
#घोषणा		DEVICE_PRESENT_EN	0x02
#घोषणा		OOB_ERROR_EN		0x01

#घोषणा PHY_CONTROL_0		0x160

#घोषणा		PHY_LOWPWREN_TX		0x80
#घोषणा		PHY_LOWPWREN_RX		0x40
#घोषणा		SPARE_REG_160_B5	0x20
#घोषणा		OFFSET_CANCEL_RX	0x10

/* bits 3:2 */
#घोषणा		PHY_RXCOMCENTER_60V	0x00
#घोषणा		PHY_RXCOMCENTER_70V	0x04
#घोषणा		PHY_RXCOMCENTER_80V	0x08
#घोषणा		PHY_RXCOMCENTER_90V	0x0C
#घोषणा 	PHY_RXCOMCENTER_MASK	0x0C

#घोषणा		PHY_RESET		0x02
#घोषणा		SAS_DEFAULT_SEL		0x01

#घोषणा PHY_CONTROL_1		0x161

/* bits 2:0 */
#घोषणा		SATA_PHY_DETLEVEL_50mv	0x00
#घोषणा		SATA_PHY_DETLEVEL_75mv	0x01
#घोषणा		SATA_PHY_DETLEVEL_100mv	0x02
#घोषणा		SATA_PHY_DETLEVEL_125mv	0x03
#घोषणा		SATA_PHY_DETLEVEL_150mv	0x04
#घोषणा		SATA_PHY_DETLEVEL_175mv	0x05
#घोषणा		SATA_PHY_DETLEVEL_200mv	0x06
#घोषणा		SATA_PHY_DETLEVEL_225mv	0x07
#घोषणा		SATA_PHY_DETLEVEL_MASK	0x07

/* bits 5:3 */
#घोषणा		SAS_PHY_DETLEVEL_50mv	0x00
#घोषणा		SAS_PHY_DETLEVEL_75mv	0x08
#घोषणा		SAS_PHY_DETLEVEL_100mv	0x10
#घोषणा		SAS_PHY_DETLEVEL_125mv	0x11
#घोषणा		SAS_PHY_DETLEVEL_150mv	0x20
#घोषणा		SAS_PHY_DETLEVEL_175mv	0x21
#घोषणा		SAS_PHY_DETLEVEL_200mv	0x30
#घोषणा		SAS_PHY_DETLEVEL_225mv	0x31
#घोषणा		SAS_PHY_DETLEVEL_MASK	0x38

#घोषणा PHY_CONTROL_2		0x162

/* bits 7:5 */
#घोषणा 	SATA_PHY_DRV_400mv	0x00
#घोषणा 	SATA_PHY_DRV_450mv	0x20
#घोषणा 	SATA_PHY_DRV_500mv	0x40
#घोषणा 	SATA_PHY_DRV_550mv	0x60
#घोषणा 	SATA_PHY_DRV_600mv	0x80
#घोषणा 	SATA_PHY_DRV_650mv	0xA0
#घोषणा 	SATA_PHY_DRV_725mv	0xC0
#घोषणा 	SATA_PHY_DRV_800mv	0xE0
#घोषणा		SATA_PHY_DRV_MASK	0xE0

/* bits 4:3 */
#घोषणा 	SATA_PREEMP_0		0x00
#घोषणा 	SATA_PREEMP_1		0x08
#घोषणा 	SATA_PREEMP_2		0x10
#घोषणा 	SATA_PREEMP_3		0x18
#घोषणा 	SATA_PREEMP_MASK	0x18

#घोषणा 	SATA_CMSH1P5		0x04

/* bits 1:0 */
#घोषणा 	SATA_SLEW_0		0x00
#घोषणा 	SATA_SLEW_1		0x01
#घोषणा 	SATA_SLEW_2		0x02
#घोषणा 	SATA_SLEW_3		0x03
#घोषणा 	SATA_SLEW_MASK		0x03

#घोषणा PHY_CONTROL_3		0x163

/* bits 7:5 */
#घोषणा 	SAS_PHY_DRV_400mv	0x00
#घोषणा 	SAS_PHY_DRV_450mv	0x20
#घोषणा 	SAS_PHY_DRV_500mv	0x40
#घोषणा 	SAS_PHY_DRV_550mv	0x60
#घोषणा 	SAS_PHY_DRV_600mv	0x80
#घोषणा 	SAS_PHY_DRV_650mv	0xA0
#घोषणा 	SAS_PHY_DRV_725mv	0xC0
#घोषणा 	SAS_PHY_DRV_800mv	0xE0
#घोषणा		SAS_PHY_DRV_MASK	0xE0

/* bits 4:3 */
#घोषणा 	SAS_PREEMP_0		0x00
#घोषणा 	SAS_PREEMP_1		0x08
#घोषणा 	SAS_PREEMP_2		0x10
#घोषणा 	SAS_PREEMP_3		0x18
#घोषणा 	SAS_PREEMP_MASK		0x18

#घोषणा 	SAS_CMSH1P5		0x04

/* bits 1:0 */
#घोषणा 	SAS_SLEW_0		0x00
#घोषणा 	SAS_SLEW_1		0x01
#घोषणा 	SAS_SLEW_2		0x02
#घोषणा 	SAS_SLEW_3		0x03
#घोषणा 	SAS_SLEW_MASK		0x03

#घोषणा PHY_CONTROL_4		0x168

#घोषणा		PHY_DONE_CAL_TX		0x80
#घोषणा		PHY_DONE_CAL_RX		0x40
#घोषणा		RX_TERM_LOAD_DIS	0x20
#घोषणा		TX_TERM_LOAD_DIS	0x10
#घोषणा		AUTO_TERM_CAL_DIS	0x08
#घोषणा		PHY_SIGDET_FLTR_EN	0x04
#घोषणा		OSC_FREQ		0x02
#घोषणा		PHY_START_CAL		0x01

/*
 * HST_PCIX2 Registers, Address Range: (0x00-0xFC)
 */
#घोषणा PCIX_REG_BASE_ADR		0xB8040000

#घोषणा PCIC_VENDOR_ID	0x00

#घोषणा PCIC_DEVICE_ID	0x02

#घोषणा PCIC_COMMAND	0x04

#घोषणा		INT_DIS			0x0400
#घोषणा		FBB_EN			0x0200		/* ro */
#घोषणा		SERR_EN			0x0100
#घोषणा		STEP_EN			0x0080		/* ro */
#घोषणा		PERR_EN			0x0040
#घोषणा		VGA_EN			0x0020		/* ro */
#घोषणा		MWI_EN			0x0010
#घोषणा		SPC_EN			0x0008
#घोषणा		MST_EN			0x0004
#घोषणा		MEM_EN			0x0002
#घोषणा		IO_EN			0x0001

#घोषणा	PCIC_STATUS	0x06

#घोषणा		PERR_DET		0x8000
#घोषणा		SERR_GEN		0x4000
#घोषणा		MABT_DET		0x2000
#घोषणा		TABT_DET		0x1000
#घोषणा		TABT_GEN		0x0800
#घोषणा		DPERR_DET		0x0100
#घोषणा		CAP_LIST		0x0010
#घोषणा		INT_STAT		0x0008

#घोषणा	PCIC_DEVREV_ID	0x08

#घोषणा	PCIC_CLASS_CODE	0x09

#घोषणा	PCIC_CACHELINE_SIZE	0x0C

#घोषणा	PCIC_MBAR0	0x10

#घोषणा 	PCIC_MBAR0_OFFSET	0

#घोषणा	PCIC_MBAR1	0x18

#घोषणा 	PCIC_MBAR1_OFFSET	2

#घोषणा	PCIC_IOBAR	0x20

#घोषणा 	PCIC_IOBAR_OFFSET	4

#घोषणा	PCIC_SUBVENDOR_ID	0x2C

#घोषणा PCIC_SUBSYTEM_ID	0x2E

#घोषणा PCIX_STATUS		0x44
#घोषणा 	RCV_SCE		0x20000000
#घोषणा 	UNEXP_SC	0x00080000
#घोषणा 	SC_DISCARD	0x00040000

#घोषणा ECC_CTRL_STAT		0x48
#घोषणा 	UNCOR_ECCERR	0x00000008

#घोषणा PCIC_PM_CSR		0x5C

#घोषणा		PWR_STATE_D0		0
#घोषणा		PWR_STATE_D1		1	/* not supported */
#घोषणा		PWR_STATE_D2		2 	/* not supported */
#घोषणा		PWR_STATE_D3		3

#घोषणा PCIC_BASE1	0x6C	/* पूर्णांकernal use only */

#घोषणा		BASE1_RSVD		0xFFFFFFF8

#घोषणा PCIC_BASEA	0x70	/* पूर्णांकernal use only */

#घोषणा		BASEA_RSVD		0xFFFFFFC0
#घोषणा 	BASEA_START		0

#घोषणा PCIC_BASEB	0x74	/* पूर्णांकernal use only */

#घोषणा		BASEB_RSVD		0xFFFFFF80
#घोषणा		BASEB_IOMAP_MASK	0x7F
#घोषणा 	BASEB_START		0x80

#घोषणा PCIC_BASEC	0x78	/* पूर्णांकernal use only */

#घोषणा		BASEC_RSVD		0xFFFFFFFC
#घोषणा 	BASEC_MASK		0x03
#घोषणा 	BASEC_START		0x58

#घोषणा PCIC_MBAR_KEY	0x7C	/* पूर्णांकernal use only */

#घोषणा 	MBAR_KEY_MASK		0xFFFFFFFF

#घोषणा PCIC_HSTPCIX_CNTRL	0xA0

#घोषणा 	REWIND_DIS		0x0800
#घोषणा		SC_TMR_DIS		0x04000000

#घोषणा PCIC_MBAR0_MASK	0xA8
#घोषणा		PCIC_MBAR0_SIZE_MASK 	0x1FFFE000
#घोषणा		PCIC_MBAR0_SIZE_SHIFT 	13
#घोषणा		PCIC_MBAR0_SIZE(val)	\
		    (((val) & PCIC_MBAR0_SIZE_MASK) >> PCIC_MBAR0_SIZE_SHIFT)

#घोषणा PCIC_FLASH_MBAR	0xB8

#घोषणा PCIC_INTRPT_STAT 0xD4

#घोषणा PCIC_TP_CTRL	0xFC

/*
 * EXSI Registers, Address Range: (0x00-0xFC)
 */
#घोषणा EXSI_REG_BASE_ADR		REG_BASE_ADDR_EXSI

#घोषणा	EXSICNFGR	(EXSI_REG_BASE_ADR + 0x00)

#घोषणा		OCMINITIALIZED		0x80000000
#घोषणा		ASIEN			0x00400000
#घोषणा		HCMODE			0x00200000
#घोषणा		PCIDEF			0x00100000
#घोषणा		COMSTOCK		0x00080000
#घोषणा		SEEPROMEND		0x00040000
#घोषणा		MSTTIMEN		0x00020000
#घोषणा		XREGEX			0x00000200
#घोषणा		NVRAMW			0x00000100
#घोषणा		NVRAMEX			0x00000080
#घोषणा		SRAMW			0x00000040
#घोषणा		SRAMEX			0x00000020
#घोषणा		FLASHW			0x00000010
#घोषणा		FLASHEX			0x00000008
#घोषणा		SEEPROMCFG		0x00000004
#घोषणा		SEEPROMTYP		0x00000002
#घोषणा		SEEPROMEX		0x00000001


#घोषणा EXSICNTRLR	(EXSI_REG_BASE_ADR + 0x04)

#घोषणा		MODINT_EN		0x00000001


#घोषणा PMSTATR		(EXSI_REG_BASE_ADR + 0x10)

#घोषणा		FLASHRST		0x00000002
#घोषणा		FLASHRDY		0x00000001


#घोषणा FLCNFGR		(EXSI_REG_BASE_ADR + 0x14)

#घोषणा		FLWEH_MASK		0x30000000
#घोषणा		FLWESU_MASK		0x0C000000
#घोषणा		FLWEPW_MASK		0x03F00000
#घोषणा		FLOEH_MASK		0x000C0000
#घोषणा 	FLOESU_MASK		0x00030000
#घोषणा 	FLOEPW_MASK		0x0000FC00
#घोषणा 	FLCSH_MASK		0x00000300
#घोषणा 	FLCSSU_MASK		0x000000C0
#घोषणा 	FLCSPW_MASK		0x0000003F

#घोषणा SRCNFGR		(EXSI_REG_BASE_ADR + 0x18)

#घोषणा		SRWEH_MASK		0x30000000
#घोषणा		SRWESU_MASK		0x0C000000
#घोषणा		SRWEPW_MASK		0x03F00000

#घोषणा		SROEH_MASK		0x000C0000
#घोषणा 	SROESU_MASK		0x00030000
#घोषणा 	SROEPW_MASK		0x0000FC00
#घोषणा		SRCSH_MASK		0x00000300
#घोषणा		SRCSSU_MASK		0x000000C0
#घोषणा		SRCSPW_MASK		0x0000003F

#घोषणा NVCNFGR		(EXSI_REG_BASE_ADR + 0x1C)

#घोषणा 	NVWEH_MASK		0x30000000
#घोषणा 	NVWESU_MASK		0x0C000000
#घोषणा 	NVWEPW_MASK		0x03F00000
#घोषणा 	NVOEH_MASK		0x000C0000
#घोषणा 	NVOESU_MASK		0x00030000
#घोषणा 	NVOEPW_MASK		0x0000FC00
#घोषणा 	NVCSH_MASK		0x00000300
#घोषणा 	NVCSSU_MASK		0x000000C0
#घोषणा 	NVCSPW_MASK		0x0000003F

#घोषणा XRCNFGR		(EXSI_REG_BASE_ADR + 0x20)

#घोषणा 	XRWEH_MASK		0x30000000
#घोषणा 	XRWESU_MASK		0x0C000000
#घोषणा 	XRWEPW_MASK		0x03F00000
#घोषणा 	XROEH_MASK		0x000C0000
#घोषणा 	XROESU_MASK		0x00030000
#घोषणा 	XROEPW_MASK		0x0000FC00
#घोषणा 	XRCSH_MASK		0x00000300
#घोषणा 	XRCSSU_MASK		0x000000C0
#घोषणा		XRCSPW_MASK		0x0000003F

#घोषणा XREGADDR	(EXSI_REG_BASE_ADR + 0x24)

#घोषणा 	XRADDRINCEN		0x80000000
#घोषणा 	XREGADD_MASK		0x007FFFFF


#घोषणा XREGDATAR	(EXSI_REG_BASE_ADR + 0x28)

#घोषणा		XREGDATA_MASK 		0x0000FFFF

#घोषणा GPIOOER		(EXSI_REG_BASE_ADR + 0x40)

#घोषणा GPIOODENR	(EXSI_REG_BASE_ADR + 0x44)

#घोषणा GPIOINVR	(EXSI_REG_BASE_ADR + 0x48)

#घोषणा GPIODATAOR	(EXSI_REG_BASE_ADR + 0x4C)

#घोषणा GPIODATAIR	(EXSI_REG_BASE_ADR + 0x50)

#घोषणा GPIOCNFGR	(EXSI_REG_BASE_ADR + 0x54)

#घोषणा		GPIO_EXTSRC		0x00000001

#घोषणा SCNTRLR		(EXSI_REG_BASE_ADR + 0xA0)

#घोषणा 	SXFERDONE		0x00000100
#घोषणा 	SXFERCNT_MASK		0x000000E0
#घोषणा 	SCMDTYP_MASK		0x0000001C
#घोषणा 	SXFERSTART		0x00000002
#घोषणा 	SXFEREN			0x00000001

#घोषणा	SRATER		(EXSI_REG_BASE_ADR + 0xA4)

#घोषणा	SADDRR		(EXSI_REG_BASE_ADR + 0xA8)

#घोषणा 	SADDR_MASK		0x0000FFFF

#घोषणा SDATAOR		(EXSI_REG_BASE_ADR + 0xAC)

#घोषणा	SDATAOR0	(EXSI_REG_BASE_ADR + 0xAC)
#घोषणा SDATAOR1	(EXSI_REG_BASE_ADR + 0xAD)
#घोषणा SDATAOR2	(EXSI_REG_BASE_ADR + 0xAE)
#घोषणा SDATAOR3	(EXSI_REG_BASE_ADR + 0xAF)

#घोषणा SDATAIR		(EXSI_REG_BASE_ADR + 0xB0)

#घोषणा SDATAIR0	(EXSI_REG_BASE_ADR + 0xB0)
#घोषणा SDATAIR1	(EXSI_REG_BASE_ADR + 0xB1)
#घोषणा SDATAIR2	(EXSI_REG_BASE_ADR + 0xB2)
#घोषणा SDATAIR3	(EXSI_REG_BASE_ADR + 0xB3)

#घोषणा ASISTAT0R	(EXSI_REG_BASE_ADR + 0xD0)
#घोषणा 	ASIFMTERR		0x00000400
#घोषणा 	ASISEECHKERR		0x00000200
#घोषणा 	ASIERR			0x00000100

#घोषणा ASISTAT1R	(EXSI_REG_BASE_ADR + 0xD4)
#घोषणा 	CHECKSUM_MASK		0x0000FFFF

#घोषणा ASIERRADDR	(EXSI_REG_BASE_ADR + 0xD8)
#घोषणा ASIERRDATAR	(EXSI_REG_BASE_ADR + 0xDC)
#घोषणा ASIERRSTATR	(EXSI_REG_BASE_ADR + 0xE0)
#घोषणा 	CPI2ASIBYTECNT_MASK	0x00070000
#घोषणा 	CPI2ASIBYTEEN_MASK      0x0000F000
#घोषणा 	CPI2ASITARGERR_MASK	0x00000F00
#घोषणा 	CPI2ASITARGMID_MASK	0x000000F0
#घोषणा 	CPI2ASIMSTERR_MASK	0x0000000F

/*
 * XSRAM, External SRAM (DWord and any BE pattern accessible)
 */
#घोषणा XSRAM_REG_BASE_ADDR             0xB8100000
#घोषणा XSRAM_SIZE                        0x100000

/*
 * NVRAM Registers, Address Range: (0x00000 - 0x3FFFF).
 */
#घोषणा		NVRAM_REG_BASE_ADR	0xBF800000
#घोषणा		NVRAM_MAX_BASE_ADR	0x003FFFFF

/* OCM base address */
#घोषणा		OCM_BASE_ADDR		0xA0000000
#घोषणा		OCM_MAX_SIZE		0x20000

/*
 * Sequencers (Central and Link) Scratch RAM page definitions.
 */

/*
 * The Central Management Sequencer (CSEQ) Scratch Memory is a 1024
 * byte memory.  It is dword accessible and has byte parity
 * protection. The CSEQ accesses it in 32 byte winकरोws, either as mode
 * dependent or mode independent memory. Each mode has 96 bytes,
 * (three 32 byte pages 0-2, not contiguous), leaving 128 bytes of
 * Mode Independent memory (four 32 byte pages 3-7). Note that mode
 * dependent scratch memory, Mode 8, page 0-3 overlaps mode
 * independent scratch memory, pages 0-3.
 * - 896 bytes of mode dependent scratch, 96 bytes per Modes 0-7, and
 * 128 bytes in mode 8,
 * - 259 bytes of mode independent scratch, common to modes 0-15.
 *
 * Sequencer scratch RAM is 1024 bytes.  This scratch memory is
 * भागided पूर्णांकo mode dependent and mode independent scratch with this
 * memory further subभागided पूर्णांकo pages of size 32 bytes. There are 5
 * pages (160 bytes) of mode independent scratch and 3 pages of
 * dependent scratch memory क्रम modes 0-7 (768 bytes). Mode 8 pages
 * 0-2 dependent scratch overlap with pages 0-2 of mode independent
 * scratch memory.
 *
 * The host accesses this scratch in a dअगरferent manner from the
 * central sequencer. The sequencer has to use CSEQ रेजिस्टरs CSCRPAGE
 * and CMnSCRPAGE to access the scratch memory. A flat mapping of the
 * scratch memory is available क्रम software convenience and to prevent
 * corruption जबतक the sequencer is running. This memory is mapped
 * onto addresses 800h - BFFh, total of 400h bytes.
 *
 * These addresses are mapped as follows:
 *
 *        800h-83Fh   Mode Dependent Scratch Mode 0 Pages 0-1
 *        840h-87Fh   Mode Dependent Scratch Mode 1 Pages 0-1
 *        880h-8BFh   Mode Dependent Scratch Mode 2 Pages 0-1
 *        8C0h-8FFh   Mode Dependent Scratch Mode 3 Pages 0-1
 *        900h-93Fh   Mode Dependent Scratch Mode 4 Pages 0-1
 *        940h-97Fh   Mode Dependent Scratch Mode 5 Pages 0-1
 *        980h-9BFh   Mode Dependent Scratch Mode 6 Pages 0-1
 *        9C0h-9FFh   Mode Dependent Scratch Mode 7 Pages 0-1
 *        A00h-A5Fh   Mode Dependent Scratch Mode 8 Pages 0-2
 *                    Mode Independent Scratch Pages 0-2
 *        A60h-A7Fh   Mode Dependent Scratch Mode 8 Page 3
 *                    Mode Independent Scratch Page 3
 *        A80h-AFFh   Mode Independent Scratch Pages 4-7
 *        B00h-B1Fh   Mode Dependent Scratch Mode 0 Page 2
 *        B20h-B3Fh   Mode Dependent Scratch Mode 1 Page 2
 *        B40h-B5Fh   Mode Dependent Scratch Mode 2 Page 2
 *        B60h-B7Fh   Mode Dependent Scratch Mode 3 Page 2
 *        B80h-B9Fh   Mode Dependent Scratch Mode 4 Page 2
 *        BA0h-BBFh   Mode Dependent Scratch Mode 5 Page 2
 *        BC0h-BDFh   Mode Dependent Scratch Mode 6 Page 2
 *        BE0h-BFFh   Mode Dependent Scratch Mode 7 Page 2
 */

/* General macros */
#घोषणा CSEQ_PAGE_SIZE			32  /* Scratch page size (in bytes) */

/* All macros start with offsets from base + 0x800 (CMAPPEDSCR).
 * Mode dependent scratch page 0, mode 0.
 * For modes 1-7 you have to करो arithmetic. */
#घोषणा CSEQ_LRM_SAVE_SINDEX		(CMAPPEDSCR + 0x0000)
#घोषणा CSEQ_LRM_SAVE_SCBPTR		(CMAPPEDSCR + 0x0002)
#घोषणा CSEQ_Q_LINK_HEAD		(CMAPPEDSCR + 0x0004)
#घोषणा CSEQ_Q_LINK_TAIL		(CMAPPEDSCR + 0x0006)
#घोषणा CSEQ_LRM_SAVE_SCRPAGE		(CMAPPEDSCR + 0x0008)

/* Mode dependent scratch page 0 mode 8 macros. */
#घोषणा CSEQ_RET_ADDR			(CMAPPEDSCR + 0x0200)
#घोषणा CSEQ_RET_SCBPTR			(CMAPPEDSCR + 0x0202)
#घोषणा CSEQ_SAVE_SCBPTR		(CMAPPEDSCR + 0x0204)
#घोषणा CSEQ_EMPTY_TRANS_CTX		(CMAPPEDSCR + 0x0206)
#घोषणा CSEQ_RESP_LEN			(CMAPPEDSCR + 0x0208)
#घोषणा CSEQ_TMF_SCBPTR			(CMAPPEDSCR + 0x020A)
#घोषणा CSEQ_GLOBAL_PREV_SCB		(CMAPPEDSCR + 0x020C)
#घोषणा CSEQ_GLOBAL_HEAD		(CMAPPEDSCR + 0x020E)
#घोषणा CSEQ_CLEAR_LU_HEAD		(CMAPPEDSCR + 0x0210)
#घोषणा CSEQ_TMF_OPCODE			(CMAPPEDSCR + 0x0212)
#घोषणा CSEQ_SCRATCH_FLAGS		(CMAPPEDSCR + 0x0213)
#घोषणा CSEQ_HSB_SITE                   (CMAPPEDSCR + 0x021A)
#घोषणा CSEQ_FIRST_INV_SCB_SITE		(CMAPPEDSCR + 0x021C)
#घोषणा CSEQ_FIRST_INV_DDB_SITE		(CMAPPEDSCR + 0x021E)

/* Mode dependent scratch page 1 mode 8 macros. */
#घोषणा CSEQ_LUN_TO_CLEAR		(CMAPPEDSCR + 0x0220)
#घोषणा CSEQ_LUN_TO_CHECK		(CMAPPEDSCR + 0x0228)

/* Mode dependent scratch page 2 mode 8 macros */
#घोषणा CSEQ_HQ_NEW_POINTER		(CMAPPEDSCR + 0x0240)
#घोषणा CSEQ_HQ_DONE_BASE		(CMAPPEDSCR + 0x0248)
#घोषणा CSEQ_HQ_DONE_POINTER		(CMAPPEDSCR + 0x0250)
#घोषणा CSEQ_HQ_DONE_PASS		(CMAPPEDSCR + 0x0254)

/* Mode independent scratch page 4 macros. */
#घोषणा CSEQ_Q_EXE_HEAD			(CMAPPEDSCR + 0x0280)
#घोषणा CSEQ_Q_EXE_TAIL			(CMAPPEDSCR + 0x0282)
#घोषणा CSEQ_Q_DONE_HEAD                (CMAPPEDSCR + 0x0284)
#घोषणा CSEQ_Q_DONE_TAIL                (CMAPPEDSCR + 0x0286)
#घोषणा CSEQ_Q_SEND_HEAD		(CMAPPEDSCR + 0x0288)
#घोषणा CSEQ_Q_SEND_TAIL		(CMAPPEDSCR + 0x028A)
#घोषणा CSEQ_Q_DMA2CHIM_HEAD		(CMAPPEDSCR + 0x028C)
#घोषणा CSEQ_Q_DMA2CHIM_TAIL		(CMAPPEDSCR + 0x028E)
#घोषणा CSEQ_Q_COPY_HEAD		(CMAPPEDSCR + 0x0290)
#घोषणा CSEQ_Q_COPY_TAIL		(CMAPPEDSCR + 0x0292)
#घोषणा CSEQ_REG0			(CMAPPEDSCR + 0x0294)
#घोषणा CSEQ_REG1			(CMAPPEDSCR + 0x0296)
#घोषणा CSEQ_REG2			(CMAPPEDSCR + 0x0298)
#घोषणा CSEQ_LINK_CTL_Q_MAP		(CMAPPEDSCR + 0x029C)
#घोषणा CSEQ_MAX_CSEQ_MODE		(CMAPPEDSCR + 0x029D)
#घोषणा CSEQ_FREE_LIST_HACK_COUNT	(CMAPPEDSCR + 0x029E)

/* Mode independent scratch page 5 macros. */
#घोषणा CSEQ_EST_NEXUS_REQ_QUEUE	(CMAPPEDSCR + 0x02A0)
#घोषणा CSEQ_EST_NEXUS_REQ_COUNT	(CMAPPEDSCR + 0x02A8)
#घोषणा CSEQ_Q_EST_NEXUS_HEAD		(CMAPPEDSCR + 0x02B0)
#घोषणा CSEQ_Q_EST_NEXUS_TAIL		(CMAPPEDSCR + 0x02B2)
#घोषणा CSEQ_NEED_EST_NEXUS_SCB		(CMAPPEDSCR + 0x02B4)
#घोषणा CSEQ_EST_NEXUS_REQ_HEAD		(CMAPPEDSCR + 0x02B6)
#घोषणा CSEQ_EST_NEXUS_REQ_TAIL		(CMAPPEDSCR + 0x02B7)
#घोषणा CSEQ_EST_NEXUS_SCB_OFFSET	(CMAPPEDSCR + 0x02B8)

/* Mode independent scratch page 6 macros. */
#घोषणा CSEQ_INT_ROUT_RET_ADDR0		(CMAPPEDSCR + 0x02C0)
#घोषणा CSEQ_INT_ROUT_RET_ADDR1		(CMAPPEDSCR + 0x02C2)
#घोषणा CSEQ_INT_ROUT_SCBPTR		(CMAPPEDSCR + 0x02C4)
#घोषणा CSEQ_INT_ROUT_MODE		(CMAPPEDSCR + 0x02C6)
#घोषणा CSEQ_ISR_SCRATCH_FLAGS		(CMAPPEDSCR + 0x02C7)
#घोषणा CSEQ_ISR_SAVE_SINDEX		(CMAPPEDSCR + 0x02C8)
#घोषणा CSEQ_ISR_SAVE_DINDEX		(CMAPPEDSCR + 0x02CA)
#घोषणा CSEQ_Q_MONIRTT_HEAD		(CMAPPEDSCR + 0x02D0)
#घोषणा CSEQ_Q_MONIRTT_TAIL		(CMAPPEDSCR + 0x02D2)
#घोषणा CSEQ_FREE_SCB_MASK		(CMAPPEDSCR + 0x02D5)
#घोषणा CSEQ_BUILTIN_FREE_SCB_HEAD	(CMAPPEDSCR + 0x02D6)
#घोषणा CSEQ_BUILTIN_FREE_SCB_TAIL	(CMAPPEDSCR + 0x02D8)
#घोषणा CSEQ_EXTENDED_FREE_SCB_HEAD	(CMAPPEDSCR + 0x02DA)
#घोषणा CSEQ_EXTENDED_FREE_SCB_TAIL	(CMAPPEDSCR + 0x02DC)

/* Mode independent scratch page 7 macros. */
#घोषणा CSEQ_EMPTY_REQ_QUEUE		(CMAPPEDSCR + 0x02E0)
#घोषणा CSEQ_EMPTY_REQ_COUNT		(CMAPPEDSCR + 0x02E8)
#घोषणा CSEQ_Q_EMPTY_HEAD		(CMAPPEDSCR + 0x02F0)
#घोषणा CSEQ_Q_EMPTY_TAIL		(CMAPPEDSCR + 0x02F2)
#घोषणा CSEQ_NEED_EMPTY_SCB		(CMAPPEDSCR + 0x02F4)
#घोषणा CSEQ_EMPTY_REQ_HEAD		(CMAPPEDSCR + 0x02F6)
#घोषणा CSEQ_EMPTY_REQ_TAIL		(CMAPPEDSCR + 0x02F7)
#घोषणा CSEQ_EMPTY_SCB_OFFSET		(CMAPPEDSCR + 0x02F8)
#घोषणा CSEQ_PRIMITIVE_DATA		(CMAPPEDSCR + 0x02FA)
#घोषणा CSEQ_TIMEOUT_CONST		(CMAPPEDSCR + 0x02FC)

/***************************************************************************
* Link m Sequencer scratch RAM is 512 bytes.
* This scratch memory is भागided पूर्णांकo mode dependent and mode
* independent scratch with this memory further subभागided पूर्णांकo
* pages of size 32 bytes. There are 4 pages (128 bytes) of
* mode independent scratch and 4 pages of dependent scratch
* memory क्रम modes 0-2 (384 bytes).
*
* The host accesses this scratch in a dअगरferent manner from the
* link sequencer. The sequencer has to use LSEQ रेजिस्टरs
* LmSCRPAGE and LmMnSCRPAGE to access the scratch memory. A flat
* mapping of the scratch memory is available क्रम software
* convenience and to prevent corruption जबतक the sequencer is
* running. This memory is mapped onto addresses 800h - 9FFh.
*
* These addresses are mapped as follows:
*
*        800h-85Fh   Mode Dependent Scratch Mode 0 Pages 0-2
*        860h-87Fh   Mode Dependent Scratch Mode 0 Page 3
*                    Mode Dependent Scratch Mode 5 Page 0
*        880h-8DFh   Mode Dependent Scratch Mode 1 Pages 0-2
*        8E0h-8FFh   Mode Dependent Scratch Mode 1 Page 3
*                    Mode Dependent Scratch Mode 5 Page 1
*        900h-95Fh   Mode Dependent Scratch Mode 2 Pages 0-2
*        960h-97Fh   Mode Dependent Scratch Mode 2 Page 3
*                    Mode Dependent Scratch Mode 5 Page 2
*        980h-9DFh   Mode Independent Scratch Pages 0-3
*        9E0h-9FFh   Mode Independent Scratch Page 3
*                    Mode Dependent Scratch Mode 5 Page 3
*
****************************************************************************/
/* General macros */
#घोषणा LSEQ_MODE_SCRATCH_SIZE		0x80 /* Size of scratch RAM per mode */
#घोषणा LSEQ_PAGE_SIZE			0x20 /* Scratch page size (in bytes) */
#घोषणा LSEQ_MODE5_PAGE0_OFFSET 	0x60

/* Common mode dependent scratch page 0 macros क्रम modes 0,1,2, and 5 */
/* Indexed using LSEQ_MODE_SCRATCH_SIZE * mode, क्रम modes 0,1,2. */
#घोषणा LmSEQ_RET_ADDR(LinkNum)		(LmSCRATCH(LinkNum) + 0x0000)
#घोषणा LmSEQ_REG0_MODE(LinkNum)	(LmSCRATCH(LinkNum) + 0x0002)
#घोषणा LmSEQ_MODE_FLAGS(LinkNum)	(LmSCRATCH(LinkNum) + 0x0004)

/* Mode flag macros (byte 0) */
#घोषणा		SAS_SAVECTX_OCCURRED		0x80
#घोषणा		SAS_OOBSVC_OCCURRED		0x40
#घोषणा		SAS_OOB_DEVICE_PRESENT		0x20
#घोषणा		SAS_CFGHDR_OCCURRED		0x10
#घोषणा		SAS_RCV_INTS_ARE_DISABLED	0x08
#घोषणा		SAS_OOB_HOT_PLUG_CNCT		0x04
#घोषणा		SAS_AWAIT_OPEN_CONNECTION	0x02
#घोषणा		SAS_CFGCMPLT_OCCURRED		0x01

/* Mode flag macros (byte 1) */
#घोषणा		SAS_RLSSCB_OCCURRED		0x80
#घोषणा		SAS_FORCED_HEADER_MISS		0x40

#घोषणा LmSEQ_RET_ADDR2(LinkNum)	(LmSCRATCH(LinkNum) + 0x0006)
#घोषणा LmSEQ_RET_ADDR1(LinkNum)	(LmSCRATCH(LinkNum) + 0x0008)
#घोषणा LmSEQ_OPCODE_TO_CSEQ(LinkNum)	(LmSCRATCH(LinkNum) + 0x000B)
#घोषणा LmSEQ_DATA_TO_CSEQ(LinkNum)	(LmSCRATCH(LinkNum) + 0x000C)

/* Mode dependent scratch page 0 macros क्रम mode 0 (non-common) */
/* Absolute offsets */
#घोषणा LmSEQ_FIRST_INV_DDB_SITE(LinkNum)	(LmSCRATCH(LinkNum) + 0x000E)
#घोषणा LmSEQ_EMPTY_TRANS_CTX(LinkNum)		(LmSCRATCH(LinkNum) + 0x0010)
#घोषणा LmSEQ_RESP_LEN(LinkNum)			(LmSCRATCH(LinkNum) + 0x0012)
#घोषणा LmSEQ_FIRST_INV_SCB_SITE(LinkNum)	(LmSCRATCH(LinkNum) + 0x0014)
#घोषणा LmSEQ_INTEN_SAVE(LinkNum)		(LmSCRATCH(LinkNum) + 0x0016)
#घोषणा LmSEQ_LINK_RST_FRM_LEN(LinkNum)		(LmSCRATCH(LinkNum) + 0x001A)
#घोषणा LmSEQ_LINK_RST_PROTOCOL(LinkNum)	(LmSCRATCH(LinkNum) + 0x001B)
#घोषणा LmSEQ_RESP_STATUS(LinkNum)		(LmSCRATCH(LinkNum) + 0x001C)
#घोषणा LmSEQ_LAST_LOADED_SGE(LinkNum)		(LmSCRATCH(LinkNum) + 0x001D)
#घोषणा LmSEQ_SAVE_SCBPTR(LinkNum)		(LmSCRATCH(LinkNum) + 0x001E)

/* Mode dependent scratch page 0 macros क्रम mode 1 (non-common) */
/* Absolute offsets */
#घोषणा LmSEQ_Q_XMIT_HEAD(LinkNum)		(LmSCRATCH(LinkNum) + 0x008E)
#घोषणा LmSEQ_M1_EMPTY_TRANS_CTX(LinkNum)	(LmSCRATCH(LinkNum) + 0x0090)
#घोषणा LmSEQ_INI_CONN_TAG(LinkNum)		(LmSCRATCH(LinkNum) + 0x0092)
#घोषणा LmSEQ_FAILED_OPEN_STATUS(LinkNum)	(LmSCRATCH(LinkNum) + 0x009A)
#घोषणा LmSEQ_XMIT_REQUEST_TYPE(LinkNum)	(LmSCRATCH(LinkNum) + 0x009B)
#घोषणा LmSEQ_M1_RESP_STATUS(LinkNum)		(LmSCRATCH(LinkNum) + 0x009C)
#घोषणा LmSEQ_M1_LAST_LOADED_SGE(LinkNum)	(LmSCRATCH(LinkNum) + 0x009D)
#घोषणा LmSEQ_M1_SAVE_SCBPTR(LinkNum)		(LmSCRATCH(LinkNum) + 0x009E)

/* Mode dependent scratch page 0 macros क्रम mode 2 (non-common) */
#घोषणा LmSEQ_PORT_COUNTER(LinkNum)		(LmSCRATCH(LinkNum) + 0x010E)
#घोषणा LmSEQ_PM_TABLE_PTR(LinkNum)		(LmSCRATCH(LinkNum) + 0x0110)
#घोषणा LmSEQ_SATA_INTERLOCK_TMR_SAVE(LinkNum)	(LmSCRATCH(LinkNum) + 0x0112)
#घोषणा LmSEQ_IP_BITL(LinkNum)			(LmSCRATCH(LinkNum) + 0x0114)
#घोषणा LmSEQ_COPY_SMP_CONN_TAG(LinkNum)	(LmSCRATCH(LinkNum) + 0x0116)
#घोषणा LmSEQ_P0M2_OFFS1AH(LinkNum)		(LmSCRATCH(LinkNum) + 0x011A)

/* Mode dependent scratch page 0 macros क्रम modes 4/5 (non-common) */
/* Absolute offsets */
#घोषणा LmSEQ_SAVED_OOB_STATUS(LinkNum)		(LmSCRATCH(LinkNum) + 0x006E)
#घोषणा LmSEQ_SAVED_OOB_MODE(LinkNum)		(LmSCRATCH(LinkNum) + 0x006F)
#घोषणा LmSEQ_Q_LINK_HEAD(LinkNum)		(LmSCRATCH(LinkNum) + 0x0070)
#घोषणा LmSEQ_LINK_RST_ERR(LinkNum)		(LmSCRATCH(LinkNum) + 0x0072)
#घोषणा LmSEQ_SAVED_OOB_SIGNALS(LinkNum)	(LmSCRATCH(LinkNum) + 0x0073)
#घोषणा LmSEQ_SAS_RESET_MODE(LinkNum)		(LmSCRATCH(LinkNum) + 0x0074)
#घोषणा LmSEQ_LINK_RESET_RETRY_COUNT(LinkNum)	(LmSCRATCH(LinkNum) + 0x0075)
#घोषणा LmSEQ_NUM_LINK_RESET_RETRIES(LinkNum)	(LmSCRATCH(LinkNum) + 0x0076)
#घोषणा LmSEQ_OOB_INT_ENABLES(LinkNum)		(LmSCRATCH(LinkNum) + 0x0078)
#घोषणा LmSEQ_NOTIFY_TIMER_DOWN_COUNT(LinkNum)	(LmSCRATCH(LinkNum) + 0x007A)
#घोषणा LmSEQ_NOTIFY_TIMER_TIMEOUT(LinkNum)	(LmSCRATCH(LinkNum) + 0x007C)
#घोषणा LmSEQ_NOTIFY_TIMER_INITIAL_COUNT(LinkNum) (LmSCRATCH(LinkNum) + 0x007E)

/* Mode dependent scratch page 1, mode 0 and mode 1 */
#घोषणा LmSEQ_SG_LIST_PTR_ADDR0(LinkNum)        (LmSCRATCH(LinkNum) + 0x0020)
#घोषणा LmSEQ_SG_LIST_PTR_ADDR1(LinkNum)        (LmSCRATCH(LinkNum) + 0x0030)
#घोषणा LmSEQ_M1_SG_LIST_PTR_ADDR0(LinkNum)     (LmSCRATCH(LinkNum) + 0x00A0)
#घोषणा LmSEQ_M1_SG_LIST_PTR_ADDR1(LinkNum)     (LmSCRATCH(LinkNum) + 0x00B0)

/* Mode dependent scratch page 1 macros क्रम mode 2 */
/* Absolute offsets */
#घोषणा LmSEQ_INVALID_DWORD_COUNT(LinkNum)	(LmSCRATCH(LinkNum) + 0x0120)
#घोषणा LmSEQ_DISPARITY_ERROR_COUNT(LinkNum) 	(LmSCRATCH(LinkNum) + 0x0124)
#घोषणा LmSEQ_LOSS_OF_SYNC_COUNT(LinkNum)	(LmSCRATCH(LinkNum) + 0x0128)

/* Mode dependent scratch page 1 macros क्रम mode 4/5 */
#घोषणा LmSEQ_FRAME_TYPE_MASK(LinkNum)	      (LmSCRATCH(LinkNum) + 0x00E0)
#घोषणा LmSEQ_HASHED_DEST_ADDR_MASK(LinkNum)  (LmSCRATCH(LinkNum) + 0x00E1)
#घोषणा LmSEQ_HASHED_SRC_ADDR_MASK_PRINT(LinkNum) (LmSCRATCH(LinkNum) + 0x00E4)
#घोषणा LmSEQ_HASHED_SRC_ADDR_MASK(LinkNum)   (LmSCRATCH(LinkNum) + 0x00E5)
#घोषणा LmSEQ_NUM_FILL_BYTES_MASK(LinkNum)    (LmSCRATCH(LinkNum) + 0x00EB)
#घोषणा LmSEQ_TAG_MASK(LinkNum)		      (LmSCRATCH(LinkNum) + 0x00F0)
#घोषणा LmSEQ_TARGET_PORT_XFER_TAG(LinkNum)   (LmSCRATCH(LinkNum) + 0x00F2)
#घोषणा LmSEQ_DATA_OFFSET(LinkNum)	      (LmSCRATCH(LinkNum) + 0x00F4)

/* Mode dependent scratch page 2 macros क्रम mode 0 */
/* Absolute offsets */
#घोषणा LmSEQ_SMP_RCV_TIMER_TERM_TS(LinkNum)	(LmSCRATCH(LinkNum) + 0x0040)
#घोषणा LmSEQ_DEVICE_BITS(LinkNum)		(LmSCRATCH(LinkNum) + 0x005B)
#घोषणा LmSEQ_SDB_DDB(LinkNum)			(LmSCRATCH(LinkNum) + 0x005C)
#घोषणा LmSEQ_SDB_NUM_TAGS(LinkNum)		(LmSCRATCH(LinkNum) + 0x005E)
#घोषणा LmSEQ_SDB_CURR_TAG(LinkNum)		(LmSCRATCH(LinkNum) + 0x005F)

/* Mode dependent scratch page 2 macros क्रम mode 1 */
/* Absolute offsets */
/* byte 0 bits 1-0 are करोमुख्य select. */
#घोषणा LmSEQ_TX_ID_ADDR_FRAME(LinkNum)		(LmSCRATCH(LinkNum) + 0x00C0)
#घोषणा LmSEQ_OPEN_TIMER_TERM_TS(LinkNum)	(LmSCRATCH(LinkNum) + 0x00C8)
#घोषणा LmSEQ_SRST_AS_TIMER_TERM_TS(LinkNum)	(LmSCRATCH(LinkNum) + 0x00CC)
#घोषणा LmSEQ_LAST_LOADED_SG_EL(LinkNum)	(LmSCRATCH(LinkNum) + 0x00D4)

/* Mode dependent scratch page 2 macros क्रम mode 2 */
/* Absolute offsets */
#घोषणा LmSEQ_STP_SHUTDOWN_TIMER_TERM_TS(LinkNum) (LmSCRATCH(LinkNum) + 0x0140)
#घोषणा LmSEQ_CLOSE_TIMER_TERM_TS(LinkNum)	(LmSCRATCH(LinkNum) + 0x0144)
#घोषणा LmSEQ_BREAK_TIMER_TERM_TS(LinkNum)	(LmSCRATCH(LinkNum) + 0x0148)
#घोषणा LmSEQ_DWS_RESET_TIMER_TERM_TS(LinkNum)	(LmSCRATCH(LinkNum) + 0x014C)
#घोषणा LmSEQ_SATA_INTERLOCK_TIMER_TERM_TS(LinkNum) \
						(LmSCRATCH(LinkNum) + 0x0150)
#घोषणा LmSEQ_MCTL_TIMER_TERM_TS(LinkNum)	(LmSCRATCH(LinkNum) + 0x0154)

/* Mode dependent scratch page 2 macros क्रम mode 5 */
#घोषणा LmSEQ_COMINIT_TIMER_TERM_TS(LinkNum)	(LmSCRATCH(LinkNum) + 0x0160)
#घोषणा LmSEQ_RCV_ID_TIMER_TERM_TS(LinkNum)	(LmSCRATCH(LinkNum) + 0x0164)
#घोषणा LmSEQ_RCV_FIS_TIMER_TERM_TS(LinkNum)	(LmSCRATCH(LinkNum) + 0x0168)
#घोषणा LmSEQ_DEV_PRES_TIMER_TERM_TS(LinkNum)	(LmSCRATCH(LinkNum) + 0x016C)

/* Mode dependent scratch page 3 macros क्रम modes 0 and 1 */
/* None defined */

/* Mode dependent scratch page 3 macros क्रम modes 2 and 5 */
/* None defined */

/* Mode Independent Scratch page 0 macros. */
#घोषणा LmSEQ_Q_TGTXFR_HEAD(LinkNum)	(LmSCRATCH(LinkNum) + 0x0180)
#घोषणा LmSEQ_Q_TGTXFR_TAIL(LinkNum)	(LmSCRATCH(LinkNum) + 0x0182)
#घोषणा LmSEQ_LINK_NUMBER(LinkNum)	(LmSCRATCH(LinkNum) + 0x0186)
#घोषणा LmSEQ_SCRATCH_FLAGS(LinkNum)	(LmSCRATCH(LinkNum) + 0x0187)
/*
 * Currently only bit 0, SAS_DWSAQD, is used.
 */
#घोषणा		SAS_DWSAQD			0x01  /*
						       * DWSSTATUS: DWSAQD
						       * bit las पढ़ो in ISR.
						       */
#घोषणा  LmSEQ_CONNECTION_STATE(LinkNum) (LmSCRATCH(LinkNum) + 0x0188)
/* Connection states (byte 0) */
#घोषणा		SAS_WE_OPENED_CS		0x01
#घोषणा		SAS_DEVICE_OPENED_CS		0x02
#घोषणा		SAS_WE_SENT_DONE_CS		0x04
#घोषणा		SAS_DEVICE_SENT_DONE_CS		0x08
#घोषणा		SAS_WE_SENT_CLOSE_CS		0x10
#घोषणा		SAS_DEVICE_SENT_CLOSE_CS	0x20
#घोषणा		SAS_WE_SENT_BREAK_CS		0x40
#घोषणा		SAS_DEVICE_SENT_BREAK_CS	0x80
/* Connection states (byte 1) */
#घोषणा		SAS_OPN_TIMEOUT_OR_OPN_RJCT_CS	0x01
#घोषणा		SAS_AIP_RECEIVED_CS		0x02
#घोषणा		SAS_CREDIT_TIMEOUT_OCCURRED_CS	0x04
#घोषणा		SAS_ACKNAK_TIMEOUT_OCCURRED_CS	0x08
#घोषणा		SAS_SMPRSP_TIMEOUT_OCCURRED_CS	0x10
#घोषणा		SAS_DONE_TIMEOUT_OCCURRED_CS	0x20
/* Connection states (byte 2) */
#घोषणा		SAS_SMP_RESPONSE_RECEIVED_CS	0x01
#घोषणा		SAS_INTLK_TIMEOUT_OCCURRED_CS	0x02
#घोषणा		SAS_DEVICE_SENT_DMAT_CS		0x04
#घोषणा		SAS_DEVICE_SENT_SYNCSRST_CS	0x08
#घोषणा		SAS_CLEARING_AFFILIATION_CS	0x20
#घोषणा		SAS_RXTASK_ACTIVE_CS		0x40
#घोषणा		SAS_TXTASK_ACTIVE_CS		0x80
/* Connection states (byte 3) */
#घोषणा		SAS_PHY_LOSS_OF_SIGNAL_CS	0x01
#घोषणा		SAS_DWS_TIMER_EXPIRED_CS	0x02
#घोषणा		SAS_LINK_RESET_NOT_COMPLETE_CS	0x04
#घोषणा		SAS_PHY_DISABLED_CS		0x08
#घोषणा		SAS_LINK_CTL_TASK_ACTIVE_CS	0x10
#घोषणा		SAS_PHY_EVENT_TASK_ACTIVE_CS	0x20
#घोषणा		SAS_DEVICE_SENT_ID_FRAME_CS	0x40
#घोषणा		SAS_DEVICE_SENT_REG_FIS_CS	0x40
#घोषणा		SAS_DEVICE_SENT_HARD_RESET_CS	0x80
#घोषणा  	SAS_PHY_IS_DOWN_FLAGS	(SAS_PHY_LOSS_OF_SIGNAL_CS|\
					 SAS_DWS_TIMER_EXPIRED_CS |\
					 SAS_LINK_RESET_NOT_COMPLETE_CS|\
					 SAS_PHY_DISABLED_CS)

#घोषणा		SAS_LINK_CTL_PHY_EVENT_FLAGS   (SAS_LINK_CTL_TASK_ACTIVE_CS |\
						SAS_PHY_EVENT_TASK_ACTIVE_CS |\
						SAS_DEVICE_SENT_ID_FRAME_CS  |\
						SAS_DEVICE_SENT_HARD_RESET_CS)

#घोषणा LmSEQ_CONCTL(LinkNum)		(LmSCRATCH(LinkNum) + 0x018C)
#घोषणा LmSEQ_CONSTAT(LinkNum)		(LmSCRATCH(LinkNum) + 0x018E)
#घोषणा LmSEQ_CONNECTION_MODES(LinkNum)	(LmSCRATCH(LinkNum) + 0x018F)
#घोषणा LmSEQ_REG1_ISR(LinkNum)		(LmSCRATCH(LinkNum) + 0x0192)
#घोषणा LmSEQ_REG2_ISR(LinkNum)		(LmSCRATCH(LinkNum) + 0x0194)
#घोषणा LmSEQ_REG3_ISR(LinkNum)		(LmSCRATCH(LinkNum) + 0x0196)
#घोषणा LmSEQ_REG0_ISR(LinkNum)		(LmSCRATCH(LinkNum) + 0x0198)

/* Mode independent scratch page 1 macros. */
#घोषणा LmSEQ_EST_NEXUS_SCBPTR0(LinkNum)	(LmSCRATCH(LinkNum) + 0x01A0)
#घोषणा LmSEQ_EST_NEXUS_SCBPTR1(LinkNum)	(LmSCRATCH(LinkNum) + 0x01A2)
#घोषणा LmSEQ_EST_NEXUS_SCBPTR2(LinkNum)	(LmSCRATCH(LinkNum) + 0x01A4)
#घोषणा LmSEQ_EST_NEXUS_SCBPTR3(LinkNum)	(LmSCRATCH(LinkNum) + 0x01A6)
#घोषणा LmSEQ_EST_NEXUS_SCB_OPCODE0(LinkNum)	(LmSCRATCH(LinkNum) + 0x01A8)
#घोषणा LmSEQ_EST_NEXUS_SCB_OPCODE1(LinkNum)	(LmSCRATCH(LinkNum) + 0x01A9)
#घोषणा LmSEQ_EST_NEXUS_SCB_OPCODE2(LinkNum)	(LmSCRATCH(LinkNum) + 0x01AA)
#घोषणा LmSEQ_EST_NEXUS_SCB_OPCODE3(LinkNum)	(LmSCRATCH(LinkNum) + 0x01AB)
#घोषणा LmSEQ_EST_NEXUS_SCB_HEAD(LinkNum)	(LmSCRATCH(LinkNum) + 0x01AC)
#घोषणा LmSEQ_EST_NEXUS_SCB_TAIL(LinkNum)	(LmSCRATCH(LinkNum) + 0x01AD)
#घोषणा LmSEQ_EST_NEXUS_BUF_AVAIL(LinkNum)	(LmSCRATCH(LinkNum) + 0x01AE)
#घोषणा LmSEQ_TIMEOUT_CONST(LinkNum)		(LmSCRATCH(LinkNum) + 0x01B8)
#घोषणा LmSEQ_ISR_SAVE_SINDEX(LinkNum)	        (LmSCRATCH(LinkNum) + 0x01BC)
#घोषणा LmSEQ_ISR_SAVE_DINDEX(LinkNum)	        (LmSCRATCH(LinkNum) + 0x01BE)

/* Mode independent scratch page 2 macros. */
#घोषणा LmSEQ_EMPTY_SCB_PTR0(LinkNum)	(LmSCRATCH(LinkNum) + 0x01C0)
#घोषणा LmSEQ_EMPTY_SCB_PTR1(LinkNum)	(LmSCRATCH(LinkNum) + 0x01C2)
#घोषणा LmSEQ_EMPTY_SCB_PTR2(LinkNum)	(LmSCRATCH(LinkNum) + 0x01C4)
#घोषणा LmSEQ_EMPTY_SCB_PTR3(LinkNum)	(LmSCRATCH(LinkNum) + 0x01C6)
#घोषणा LmSEQ_EMPTY_SCB_OPCD0(LinkNum)	(LmSCRATCH(LinkNum) + 0x01C8)
#घोषणा LmSEQ_EMPTY_SCB_OPCD1(LinkNum)	(LmSCRATCH(LinkNum) + 0x01C9)
#घोषणा LmSEQ_EMPTY_SCB_OPCD2(LinkNum)	(LmSCRATCH(LinkNum) + 0x01CA)
#घोषणा LmSEQ_EMPTY_SCB_OPCD3(LinkNum)	(LmSCRATCH(LinkNum) + 0x01CB)
#घोषणा LmSEQ_EMPTY_SCB_HEAD(LinkNum)	(LmSCRATCH(LinkNum) + 0x01CC)
#घोषणा LmSEQ_EMPTY_SCB_TAIL(LinkNum)	(LmSCRATCH(LinkNum) + 0x01CD)
#घोषणा LmSEQ_EMPTY_BUFS_AVAIL(LinkNum)	(LmSCRATCH(LinkNum) + 0x01CE)
#घोषणा LmSEQ_ATA_SCR_REGS(LinkNum)	(LmSCRATCH(LinkNum) + 0x01D4)

/* Mode independent scratch page 3 macros. */
#घोषणा LmSEQ_DEV_PRES_TMR_TOUT_CONST(LinkNum)	(LmSCRATCH(LinkNum) + 0x01E0)
#घोषणा LmSEQ_SATA_INTERLOCK_TIMEOUT(LinkNum)	(LmSCRATCH(LinkNum) + 0x01E4)
#घोषणा LmSEQ_STP_SHUTDOWN_TIMEOUT(LinkNum)	(LmSCRATCH(LinkNum) + 0x01E8)
#घोषणा LmSEQ_SRST_ASSERT_TIMEOUT(LinkNum)	(LmSCRATCH(LinkNum) + 0x01EC)
#घोषणा LmSEQ_RCV_FIS_TIMEOUT(LinkNum)		(LmSCRATCH(LinkNum) + 0x01F0)
#घोषणा LmSEQ_ONE_MILLISEC_TIMEOUT(LinkNum)	(LmSCRATCH(LinkNum) + 0x01F4)
#घोषणा LmSEQ_TEN_MS_COMINIT_TIMEOUT(LinkNum)	(LmSCRATCH(LinkNum) + 0x01F8)
#घोषणा LmSEQ_SMP_RCV_TIMEOUT(LinkNum)		(LmSCRATCH(LinkNum) + 0x01FC)

#पूर्ण_अगर
