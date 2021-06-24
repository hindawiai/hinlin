<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ALSA SoC McASP Audio Layer क्रम TI DAVINCI processor
 *
 * MCASP related definitions
 *
 * Author: Nirmal Pandey <n-pandey@ti.com>,
 *         Suresh Rajashekara <suresh.r@ti.com>
 *         Steve Chen <schen@.mvista.com>
 *
 * Copyright:   (C) 2009 MontaVista Software, Inc., <source@mvista.com>
 * Copyright:   (C) 2009  Texas Instruments, India
 */

#अगर_अघोषित DAVINCI_MCASP_H
#घोषणा DAVINCI_MCASP_H

/*
 * McASP रेजिस्टर definitions
 */
#घोषणा DAVINCI_MCASP_PID_REG		0x00
#घोषणा DAVINCI_MCASP_PWREMUMGT_REG	0x04

#घोषणा DAVINCI_MCASP_PFUNC_REG		0x10
#घोषणा DAVINCI_MCASP_Pसूची_REG		0x14
#घोषणा DAVINCI_MCASP_PDOUT_REG		0x18
#घोषणा DAVINCI_MCASP_PDSET_REG		0x1c

#घोषणा DAVINCI_MCASP_PDCLR_REG		0x20

#घोषणा DAVINCI_MCASP_TLGC_REG		0x30
#घोषणा DAVINCI_MCASP_TLMR_REG		0x34

#घोषणा DAVINCI_MCASP_GBLCTL_REG	0x44
#घोषणा DAVINCI_MCASP_AMUTE_REG		0x48
#घोषणा DAVINCI_MCASP_LBCTL_REG		0x4c

#घोषणा DAVINCI_MCASP_TXDITCTL_REG	0x50

#घोषणा DAVINCI_MCASP_GBLCTLR_REG	0x60
#घोषणा DAVINCI_MCASP_RXMASK_REG	0x64
#घोषणा DAVINCI_MCASP_RXFMT_REG		0x68
#घोषणा DAVINCI_MCASP_RXFMCTL_REG	0x6c

#घोषणा DAVINCI_MCASP_ACLKRCTL_REG	0x70
#घोषणा DAVINCI_MCASP_AHCLKRCTL_REG	0x74
#घोषणा DAVINCI_MCASP_RXTDM_REG		0x78
#घोषणा DAVINCI_MCASP_EVTCTLR_REG	0x7c

#घोषणा DAVINCI_MCASP_RXSTAT_REG	0x80
#घोषणा DAVINCI_MCASP_RXTDMSLOT_REG	0x84
#घोषणा DAVINCI_MCASP_RXCLKCHK_REG	0x88
#घोषणा DAVINCI_MCASP_REVTCTL_REG	0x8c

#घोषणा DAVINCI_MCASP_GBLCTLX_REG	0xa0
#घोषणा DAVINCI_MCASP_TXMASK_REG	0xa4
#घोषणा DAVINCI_MCASP_TXFMT_REG		0xa8
#घोषणा DAVINCI_MCASP_TXFMCTL_REG	0xac

#घोषणा DAVINCI_MCASP_ACLKXCTL_REG	0xb0
#घोषणा DAVINCI_MCASP_AHCLKXCTL_REG	0xb4
#घोषणा DAVINCI_MCASP_TXTDM_REG		0xb8
#घोषणा DAVINCI_MCASP_EVTCTLX_REG	0xbc

#घोषणा DAVINCI_MCASP_TXSTAT_REG	0xc0
#घोषणा DAVINCI_MCASP_TXTDMSLOT_REG	0xc4
#घोषणा DAVINCI_MCASP_TXCLKCHK_REG	0xc8
#घोषणा DAVINCI_MCASP_XEVTCTL_REG	0xcc

/* Left(even TDM Slot) Channel Status Register File */
#घोषणा DAVINCI_MCASP_DITCSRA_REG	0x100
/* Right(odd TDM slot) Channel Status Register File */
#घोषणा DAVINCI_MCASP_DITCSRB_REG	0x118
/* Left(even TDM slot) User Data Register File */
#घोषणा DAVINCI_MCASP_DITUDRA_REG	0x130
/* Right(odd TDM Slot) User Data Register File */
#घोषणा DAVINCI_MCASP_DITUDRB_REG	0x148

/* Serializer n Control Register */
#घोषणा DAVINCI_MCASP_XRSRCTL_BASE_REG	0x180
#घोषणा DAVINCI_MCASP_XRSRCTL_REG(n)	(DAVINCI_MCASP_XRSRCTL_BASE_REG + \
						(n << 2))

/* Transmit Buffer क्रम Serializer n */
#घोषणा DAVINCI_MCASP_TXBUF_REG(n)	(0x200 + (n << 2))
/* Receive Buffer क्रम Serializer n */
#घोषणा DAVINCI_MCASP_RXBUF_REG(n)	(0x280 + (n << 2))

/* McASP FIFO Registers */
#घोषणा DAVINCI_MCASP_V2_AFIFO_BASE	(0x1010)
#घोषणा DAVINCI_MCASP_V3_AFIFO_BASE	(0x1000)

/* FIFO रेजिस्टर offsets from AFIFO base */
#घोषणा MCASP_WFIFOCTL_OFFSET		(0x0)
#घोषणा MCASP_WFIFOSTS_OFFSET		(0x4)
#घोषणा MCASP_RFIFOCTL_OFFSET		(0x8)
#घोषणा MCASP_RFIFOSTS_OFFSET		(0xc)

/*
 * DAVINCI_MCASP_PWREMUMGT_REG - Power Down and Emulation Management
 *     Register Bits
 */
#घोषणा MCASP_FREE	BIT(0)
#घोषणा MCASP_SOFT	BIT(1)

/*
 * DAVINCI_MCASP_PFUNC_REG - Pin Function / GPIO Enable Register Bits
 * DAVINCI_MCASP_Pसूची_REG - Pin Direction Register Bits
 * DAVINCI_MCASP_PDOUT_REG - Pin output in GPIO mode
 * DAVINCI_MCASP_PDSET_REG - Pin input in GPIO mode
 */
#घोषणा PIN_BIT_AXR(n)	(n)
#घोषणा PIN_BIT_AMUTE	25
#घोषणा PIN_BIT_ACLKX	26
#घोषणा PIN_BIT_AHCLKX	27
#घोषणा PIN_BIT_AFSX	28
#घोषणा PIN_BIT_ACLKR	29
#घोषणा PIN_BIT_AHCLKR	30
#घोषणा PIN_BIT_AFSR	31

/*
 * DAVINCI_MCASP_TXDITCTL_REG - Transmit DIT Control Register Bits
 */
#घोषणा DITEN	BIT(0)	/* Transmit DIT mode enable/disable */
#घोषणा VA	BIT(2)
#घोषणा VB	BIT(3)

/*
 * DAVINCI_MCASP_TXFMT_REG - Transmit Bitstream Format Register Bits
 */
#घोषणा TXROT(val)	(val)
#घोषणा TXSEL		BIT(3)
#घोषणा TXSSZ(val)	(val<<4)
#घोषणा TXPBIT(val)	(val<<8)
#घोषणा TXPAD(val)	(val<<13)
#घोषणा TXORD		BIT(15)
#घोषणा FSXDLY(val)	(val<<16)

/*
 * DAVINCI_MCASP_RXFMT_REG - Receive Bitstream Format Register Bits
 */
#घोषणा RXROT(val)	(val)
#घोषणा RXSEL		BIT(3)
#घोषणा RXSSZ(val)	(val<<4)
#घोषणा RXPBIT(val)	(val<<8)
#घोषणा RXPAD(val)	(val<<13)
#घोषणा RXORD		BIT(15)
#घोषणा FSRDLY(val)	(val<<16)

/*
 * DAVINCI_MCASP_TXFMCTL_REG -  Transmit Frame Control Register Bits
 */
#घोषणा FSXPOL		BIT(0)
#घोषणा AFSXE		BIT(1)
#घोषणा FSXDUR		BIT(4)
#घोषणा FSXMOD(val)	(val<<7)

/*
 * DAVINCI_MCASP_RXFMCTL_REG - Receive Frame Control Register Bits
 */
#घोषणा FSRPOL		BIT(0)
#घोषणा AFSRE		BIT(1)
#घोषणा FSRDUR		BIT(4)
#घोषणा FSRMOD(val)	(val<<7)

/*
 * DAVINCI_MCASP_ACLKXCTL_REG - Transmit Clock Control Register Bits
 */
#घोषणा ACLKXDIV(val)	(val)
#घोषणा ACLKXE		BIT(5)
#घोषणा TX_ASYNC	BIT(6)
#घोषणा ACLKXPOL	BIT(7)
#घोषणा ACLKXDIV_MASK	0x1f

/*
 * DAVINCI_MCASP_ACLKRCTL_REG Receive Clock Control Register Bits
 */
#घोषणा ACLKRDIV(val)	(val)
#घोषणा ACLKRE		BIT(5)
#घोषणा RX_ASYNC	BIT(6)
#घोषणा ACLKRPOL	BIT(7)
#घोषणा ACLKRDIV_MASK	0x1f

/*
 * DAVINCI_MCASP_AHCLKXCTL_REG - High Frequency Transmit Clock Control
 *     Register Bits
 */
#घोषणा AHCLKXDIV(val)	(val)
#घोषणा AHCLKXPOL	BIT(14)
#घोषणा AHCLKXE		BIT(15)
#घोषणा AHCLKXDIV_MASK	0xfff

/*
 * DAVINCI_MCASP_AHCLKRCTL_REG - High Frequency Receive Clock Control
 *     Register Bits
 */
#घोषणा AHCLKRDIV(val)	(val)
#घोषणा AHCLKRPOL	BIT(14)
#घोषणा AHCLKRE		BIT(15)
#घोषणा AHCLKRDIV_MASK	0xfff

/*
 * DAVINCI_MCASP_XRSRCTL_BASE_REG -  Serializer Control Register Bits
 */
#घोषणा MODE(val)	(val)
#घोषणा DISMOD_3STATE	(0x0)
#घोषणा DISMOD_LOW	(0x2 << 2)
#घोषणा DISMOD_HIGH	(0x3 << 2)
#घोषणा DISMOD_VAL(x)	((x) << 2)
#घोषणा DISMOD_MASK	DISMOD_HIGH
#घोषणा TXSTATE		BIT(4)
#घोषणा RXSTATE		BIT(5)
#घोषणा SRMOD_MASK	3
#घोषणा SRMOD_INACTIVE	0

/*
 * DAVINCI_MCASP_LBCTL_REG - Loop Back Control Register Bits
 */
#घोषणा LBEN		BIT(0)
#घोषणा LBORD		BIT(1)
#घोषणा LBGENMODE(val)	(val<<2)

/*
 * DAVINCI_MCASP_TXTDMSLOT_REG - Transmit TDM Slot Register configuration
 */
#घोषणा TXTDMS(n)	(1<<n)

/*
 * DAVINCI_MCASP_RXTDMSLOT_REG - Receive TDM Slot Register configuration
 */
#घोषणा RXTDMS(n)	(1<<n)

/*
 * DAVINCI_MCASP_GBLCTL_REG -  Global Control Register Bits
 */
#घोषणा RXCLKRST	BIT(0)	/* Receiver Clock Divider Reset */
#घोषणा RXHCLKRST	BIT(1)	/* Receiver High Frequency Clock Divider */
#घोषणा RXSERCLR	BIT(2)	/* Receiver Serializer Clear */
#घोषणा RXSMRST		BIT(3)	/* Receiver State Machine Reset */
#घोषणा RXFSRST		BIT(4)	/* Frame Sync Generator Reset */
#घोषणा TXCLKRST	BIT(8)	/* Transmitter Clock Divider Reset */
#घोषणा TXHCLKRST	BIT(9)	/* Transmitter High Frequency Clock Divider*/
#घोषणा TXSERCLR	BIT(10)	/* Transmit Serializer Clear */
#घोषणा TXSMRST		BIT(11)	/* Transmitter State Machine Reset */
#घोषणा TXFSRST		BIT(12)	/* Frame Sync Generator Reset */

/*
 * DAVINCI_MCASP_TXSTAT_REG - Transmitter Status Register Bits
 * DAVINCI_MCASP_RXSTAT_REG - Receiver Status Register Bits
 */
#घोषणा XRERR		BIT(8) /* Transmit/Receive error */
#घोषणा XRDATA		BIT(5) /* Transmit/Receive data पढ़ोy */

/*
 * DAVINCI_MCASP_AMUTE_REG -  Mute Control Register Bits
 */
#घोषणा MUTENA(val)	(val)
#घोषणा MUTEINPOL	BIT(2)
#घोषणा MUTEINENA	BIT(3)
#घोषणा MUTEIN		BIT(4)
#घोषणा MUTER		BIT(5)
#घोषणा MUTEX		BIT(6)
#घोषणा MUTEFSR		BIT(7)
#घोषणा MUTEFSX		BIT(8)
#घोषणा MUTEBADCLKR	BIT(9)
#घोषणा MUTEBADCLKX	BIT(10)
#घोषणा MUTERXDMAERR	BIT(11)
#घोषणा MUTETXDMAERR	BIT(12)

/*
 * DAVINCI_MCASP_REVTCTL_REG - Receiver DMA Event Control Register bits
 */
#घोषणा RXDATADMADIS	BIT(0)

/*
 * DAVINCI_MCASP_XEVTCTL_REG - Transmitter DMA Event Control Register bits
 */
#घोषणा TXDATADMADIS	BIT(0)

/*
 * DAVINCI_MCASP_EVTCTLR_REG - Receiver Interrupt Control Register Bits
 */
#घोषणा ROVRN		BIT(0)

/*
 * DAVINCI_MCASP_EVTCTLX_REG - Transmitter Interrupt Control Register Bits
 */
#घोषणा XUNDRN		BIT(0)

/*
 * DAVINCI_MCASP_W[R]FIFOCTL - Write/Read FIFO Control Register bits
 */
#घोषणा FIFO_ENABLE	BIT(16)
#घोषणा NUMEVT_MASK	(0xFF << 8)
#घोषणा NUMEVT(x)	(((x) & 0xFF) << 8)
#घोषणा NUMDMA_MASK	(0xFF)

/* Source of High-frequency transmit/receive घड़ी */
#घोषणा MCASP_CLK_HCLK_AHCLK		0 /* AHCLKX/R */
#घोषणा MCASP_CLK_HCLK_AUXCLK		1 /* Internal functional घड़ी */

/* घड़ी भागider IDs */
#घोषणा MCASP_CLKDIV_AUXCLK		0 /* HCLK भागider from AUXCLK */
#घोषणा MCASP_CLKDIV_BCLK		1 /* BCLK भागider from HCLK */
#घोषणा MCASP_CLKDIV_BCLK_FS_RATIO	2 /* to set BCLK FS ration */

#पूर्ण_अगर	/* DAVINCI_MCASP_H */
