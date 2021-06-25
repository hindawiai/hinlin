<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-1.0+ WITH Linux-syscall-note */
/*
 * include/linux/serial_reg.h
 *
 * Copyright (C) 1992, 1994 by Theoकरोre Ts'o.
 * 
 * Redistribution of this file is permitted under the terms of the GNU 
 * Public License (GPL)
 * 
 * These are the UART port assignments, expressed as offsets from the base
 * रेजिस्टर.  These assignments should hold क्रम any serial port based on
 * a 8250, 16450, or 16550(A).
 */

#अगर_अघोषित _LINUX_SERIAL_REG_H
#घोषणा _LINUX_SERIAL_REG_H

/*
 * DLAB=0
 */
#घोषणा UART_RX		0	/* In:  Receive buffer */
#घोषणा UART_TX		0	/* Out: Transmit buffer */

#घोषणा UART_IER	1	/* Out: Interrupt Enable Register */
#घोषणा UART_IER_MSI		0x08 /* Enable Modem status पूर्णांकerrupt */
#घोषणा UART_IER_RLSI		0x04 /* Enable receiver line status पूर्णांकerrupt */
#घोषणा UART_IER_THRI		0x02 /* Enable Transmitter holding रेजिस्टर पूर्णांक. */
#घोषणा UART_IER_RDI		0x01 /* Enable receiver data पूर्णांकerrupt */
/*
 * Sleep mode क्रम ST16650 and TI16750.  For the ST16650, EFR[4]=1
 */
#घोषणा UART_IERX_SLEEP		0x10 /* Enable sleep mode */

#घोषणा UART_IIR	2	/* In:  Interrupt ID Register */
#घोषणा UART_IIR_NO_INT		0x01 /* No पूर्णांकerrupts pending */
#घोषणा UART_IIR_ID		0x0e /* Mask क्रम the पूर्णांकerrupt ID */
#घोषणा UART_IIR_MSI		0x00 /* Modem status पूर्णांकerrupt */
#घोषणा UART_IIR_THRI		0x02 /* Transmitter holding रेजिस्टर empty */
#घोषणा UART_IIR_RDI		0x04 /* Receiver data पूर्णांकerrupt */
#घोषणा UART_IIR_RLSI		0x06 /* Receiver line status पूर्णांकerrupt */

#घोषणा UART_IIR_BUSY		0x07 /* DesignWare APB Busy Detect */

#घोषणा UART_IIR_RX_TIMEOUT	0x0c /* OMAP RX Timeout पूर्णांकerrupt */
#घोषणा UART_IIR_XOFF		0x10 /* OMAP XOFF/Special Character */
#घोषणा UART_IIR_CTS_RTS_DSR	0x20 /* OMAP CTS/RTS/DSR Change */

#घोषणा UART_FCR	2	/* Out: FIFO Control Register */
#घोषणा UART_FCR_ENABLE_FIFO	0x01 /* Enable the FIFO */
#घोषणा UART_FCR_CLEAR_RCVR	0x02 /* Clear the RCVR FIFO */
#घोषणा UART_FCR_CLEAR_XMIT	0x04 /* Clear the XMIT FIFO */
#घोषणा UART_FCR_DMA_SELECT	0x08 /* For DMA applications */
/*
 * Note: The FIFO trigger levels are chip specअगरic:
 *	RX:76 = 00  01  10  11	TX:54 = 00  01  10  11
 * PC16550D:	 1   4   8  14		xx  xx  xx  xx
 * TI16C550A:	 1   4   8  14          xx  xx  xx  xx
 * TI16C550C:	 1   4   8  14          xx  xx  xx  xx
 * ST16C550:	 1   4   8  14		xx  xx  xx  xx
 * ST16C650:	 8  16  24  28		16   8  24  30	PORT_16650V2
 * NS16C552:	 1   4   8  14		xx  xx  xx  xx
 * ST16C654:	 8  16  56  60		 8  16  32  56	PORT_16654
 * TI16C750:	 1  16  32  56		xx  xx  xx  xx	PORT_16750
 * TI16C752:	 8  16  56  60		 8  16  32  56
 * Tegra:	 1   4   8  14		16   8   4   1	PORT_TEGRA
 */
#घोषणा UART_FCR_R_TRIG_00	0x00
#घोषणा UART_FCR_R_TRIG_01	0x40
#घोषणा UART_FCR_R_TRIG_10	0x80
#घोषणा UART_FCR_R_TRIG_11	0xc0
#घोषणा UART_FCR_T_TRIG_00	0x00
#घोषणा UART_FCR_T_TRIG_01	0x10
#घोषणा UART_FCR_T_TRIG_10	0x20
#घोषणा UART_FCR_T_TRIG_11	0x30

#घोषणा UART_FCR_TRIGGER_MASK	0xC0 /* Mask क्रम the FIFO trigger range */
#घोषणा UART_FCR_TRIGGER_1	0x00 /* Mask क्रम trigger set at 1 */
#घोषणा UART_FCR_TRIGGER_4	0x40 /* Mask क्रम trigger set at 4 */
#घोषणा UART_FCR_TRIGGER_8	0x80 /* Mask क्रम trigger set at 8 */
#घोषणा UART_FCR_TRIGGER_14	0xC0 /* Mask क्रम trigger set at 14 */
/* 16650 definitions */
#घोषणा UART_FCR6_R_TRIGGER_8	0x00 /* Mask क्रम receive trigger set at 1 */
#घोषणा UART_FCR6_R_TRIGGER_16	0x40 /* Mask क्रम receive trigger set at 4 */
#घोषणा UART_FCR6_R_TRIGGER_24  0x80 /* Mask क्रम receive trigger set at 8 */
#घोषणा UART_FCR6_R_TRIGGER_28	0xC0 /* Mask क्रम receive trigger set at 14 */
#घोषणा UART_FCR6_T_TRIGGER_16	0x00 /* Mask क्रम transmit trigger set at 16 */
#घोषणा UART_FCR6_T_TRIGGER_8	0x10 /* Mask क्रम transmit trigger set at 8 */
#घोषणा UART_FCR6_T_TRIGGER_24  0x20 /* Mask क्रम transmit trigger set at 24 */
#घोषणा UART_FCR6_T_TRIGGER_30	0x30 /* Mask क्रम transmit trigger set at 30 */
#घोषणा UART_FCR7_64BYTE	0x20 /* Go पूर्णांकo 64 byte mode (TI16C750 and
					some Freescale UARTs) */

#घोषणा UART_FCR_R_TRIG_SHIFT		6
#घोषणा UART_FCR_R_TRIG_BITS(x)		\
	(((x) & UART_FCR_TRIGGER_MASK) >> UART_FCR_R_TRIG_SHIFT)
#घोषणा UART_FCR_R_TRIG_MAX_STATE	4

#घोषणा UART_LCR	3	/* Out: Line Control Register */
/*
 * Note: अगर the word length is 5 bits (UART_LCR_WLEN5), then setting 
 * UART_LCR_STOP will select 1.5 stop bits, not 2 stop bits.
 */
#घोषणा UART_LCR_DLAB		0x80 /* Divisor latch access bit */
#घोषणा UART_LCR_SBC		0x40 /* Set अवरोध control */
#घोषणा UART_LCR_SPAR		0x20 /* Stick parity (?) */
#घोषणा UART_LCR_EPAR		0x10 /* Even parity select */
#घोषणा UART_LCR_PARITY		0x08 /* Parity Enable */
#घोषणा UART_LCR_STOP		0x04 /* Stop bits: 0=1 bit, 1=2 bits */
#घोषणा UART_LCR_WLEN5		0x00 /* Wordlength: 5 bits */
#घोषणा UART_LCR_WLEN6		0x01 /* Wordlength: 6 bits */
#घोषणा UART_LCR_WLEN7		0x02 /* Wordlength: 7 bits */
#घोषणा UART_LCR_WLEN8		0x03 /* Wordlength: 8 bits */

/*
 * Access to some रेजिस्टरs depends on रेजिस्टर access / configuration
 * mode.
 */
#घोषणा UART_LCR_CONF_MODE_A	UART_LCR_DLAB	/* Configutation mode A */
#घोषणा UART_LCR_CONF_MODE_B	0xBF		/* Configutation mode B */

#घोषणा UART_MCR	4	/* Out: Modem Control Register */
#घोषणा UART_MCR_CLKSEL		0x80 /* Divide घड़ी by 4 (TI16C752, EFR[4]=1) */
#घोषणा UART_MCR_TCRTLR		0x40 /* Access TCR/TLR (TI16C752, EFR[4]=1) */
#घोषणा UART_MCR_XOन_अंकY		0x20 /* Enable Xon Any (TI16C752, EFR[4]=1) */
#घोषणा UART_MCR_AFE		0x20 /* Enable स्वतः-RTS/CTS (TI16C550C/TI16C750) */
#घोषणा UART_MCR_LOOP		0x10 /* Enable loopback test mode */
#घोषणा UART_MCR_OUT2		0x08 /* Out2 complement */
#घोषणा UART_MCR_OUT1		0x04 /* Out1 complement */
#घोषणा UART_MCR_RTS		0x02 /* RTS complement */
#घोषणा UART_MCR_DTR		0x01 /* DTR complement */

#घोषणा UART_LSR	5	/* In:  Line Status Register */
#घोषणा UART_LSR_FIFOE		0x80 /* Fअगरo error */
#घोषणा UART_LSR_TEMT		0x40 /* Transmitter empty */
#घोषणा UART_LSR_THRE		0x20 /* Transmit-hold-रेजिस्टर empty */
#घोषणा UART_LSR_BI		0x10 /* Break पूर्णांकerrupt indicator */
#घोषणा UART_LSR_FE		0x08 /* Frame error indicator */
#घोषणा UART_LSR_PE		0x04 /* Parity error indicator */
#घोषणा UART_LSR_OE		0x02 /* Overrun error indicator */
#घोषणा UART_LSR_DR		0x01 /* Receiver data पढ़ोy */
#घोषणा UART_LSR_BRK_ERROR_BITS	0x1E /* BI, FE, PE, OE bits */

#घोषणा UART_MSR	6	/* In:  Modem Status Register */
#घोषणा UART_MSR_DCD		0x80 /* Data Carrier Detect */
#घोषणा UART_MSR_RI		0x40 /* Ring Indicator */
#घोषणा UART_MSR_DSR		0x20 /* Data Set Ready */
#घोषणा UART_MSR_CTS		0x10 /* Clear to Send */
#घोषणा UART_MSR_DDCD		0x08 /* Delta DCD */
#घोषणा UART_MSR_TERI		0x04 /* Trailing edge ring indicator */
#घोषणा UART_MSR_DDSR		0x02 /* Delta DSR */
#घोषणा UART_MSR_DCTS		0x01 /* Delta CTS */
#घोषणा UART_MSR_ANY_DELTA	0x0F /* Any of the delta bits! */

#घोषणा UART_SCR	7	/* I/O: Scratch Register */

/*
 * DLAB=1
 */
#घोषणा UART_DLL	0	/* Out: Divisor Latch Low */
#घोषणा UART_DLM	1	/* Out: Divisor Latch High */
#घोषणा UART_DIV_MAX	0xFFFF	/* Max भागisor value */

/*
 * LCR=0xBF (or DLAB=1 क्रम 16C660)
 */
#घोषणा UART_EFR	2	/* I/O: Extended Features Register */
#घोषणा UART_XR_EFR	9	/* I/O: Extended Features Register (XR17D15x) */
#घोषणा UART_EFR_CTS		0x80 /* CTS flow control */
#घोषणा UART_EFR_RTS		0x40 /* RTS flow control */
#घोषणा UART_EFR_SCD		0x20 /* Special अक्षरacter detect */
#घोषणा UART_EFR_ECB		0x10 /* Enhanced control bit */
/*
 * the low four bits control software flow control
 */

/*
 * LCR=0xBF, TI16C752, ST16650, ST16650A, ST16654
 */
#घोषणा UART_XON1	4	/* I/O: Xon अक्षरacter 1 */
#घोषणा UART_XON2	5	/* I/O: Xon अक्षरacter 2 */
#घोषणा UART_XOFF1	6	/* I/O: Xoff अक्षरacter 1 */
#घोषणा UART_XOFF2	7	/* I/O: Xoff अक्षरacter 2 */

/*
 * EFR[4]=1 MCR[6]=1, TI16C752
 */
#घोषणा UART_TI752_TCR	6	/* I/O: transmission control रेजिस्टर */
#घोषणा UART_TI752_TLR	7	/* I/O: trigger level रेजिस्टर */

/*
 * LCR=0xBF, XR16C85x
 */
#घोषणा UART_TRG	0	/* FCTR bit 7 selects Rx or Tx
				 * In: Fअगरo count
				 * Out: Fअगरo custom trigger levels */
/*
 * These are the definitions क्रम the Programmable Trigger Register
 */
#घोषणा UART_TRG_1		0x01
#घोषणा UART_TRG_4		0x04
#घोषणा UART_TRG_8		0x08
#घोषणा UART_TRG_16		0x10
#घोषणा UART_TRG_32		0x20
#घोषणा UART_TRG_64		0x40
#घोषणा UART_TRG_96		0x60
#घोषणा UART_TRG_120		0x78
#घोषणा UART_TRG_128		0x80

#घोषणा UART_FCTR	1	/* Feature Control Register */
#घोषणा UART_FCTR_RTS_NODELAY	0x00  /* RTS flow control delay */
#घोषणा UART_FCTR_RTS_4DELAY	0x01
#घोषणा UART_FCTR_RTS_6DELAY	0x02
#घोषणा UART_FCTR_RTS_8DELAY	0x03
#घोषणा UART_FCTR_IRDA		0x04  /* IrDa data encode select */
#घोषणा UART_FCTR_TX_INT	0x08  /* Tx पूर्णांकerrupt type select */
#घोषणा UART_FCTR_TRGA		0x00  /* Tx/Rx 550 trigger table select */
#घोषणा UART_FCTR_TRGB		0x10  /* Tx/Rx 650 trigger table select */
#घोषणा UART_FCTR_TRGC		0x20  /* Tx/Rx 654 trigger table select */
#घोषणा UART_FCTR_TRGD		0x30  /* Tx/Rx 850 programmable trigger select */
#घोषणा UART_FCTR_SCR_SWAP	0x40  /* Scratch pad रेजिस्टर swap */
#घोषणा UART_FCTR_RX		0x00  /* Programmable trigger mode select */
#घोषणा UART_FCTR_TX		0x80  /* Programmable trigger mode select */

/*
 * LCR=0xBF, FCTR[6]=1
 */
#घोषणा UART_EMSR	7	/* Extended Mode Select Register */
#घोषणा UART_EMSR_FIFO_COUNT	0x01  /* Rx/Tx select */
#घोषणा UART_EMSR_ALT_COUNT	0x02  /* Alternating count select */

/*
 * The Intel XScale on-chip UARTs define these bits
 */
#घोषणा UART_IER_DMAE	0x80	/* DMA Requests Enable */
#घोषणा UART_IER_UUE	0x40	/* UART Unit Enable */
#घोषणा UART_IER_NRZE	0x20	/* NRZ coding Enable */
#घोषणा UART_IER_RTOIE	0x10	/* Receiver Time Out Interrupt Enable */

#घोषणा UART_IIR_TOD	0x08	/* Character Timeout Indication Detected */

#घोषणा UART_FCR_PXAR1	0x00	/* receive FIFO threshold = 1 */
#घोषणा UART_FCR_PXAR8	0x40	/* receive FIFO threshold = 8 */
#घोषणा UART_FCR_PXAR16	0x80	/* receive FIFO threshold = 16 */
#घोषणा UART_FCR_PXAR32	0xc0	/* receive FIFO threshold = 32 */

/*
 * These रेजिस्टर definitions are क्रम the 16C950
 */
#घोषणा UART_ASR	0x01	/* Additional Status Register */
#घोषणा UART_RFL	0x03	/* Receiver FIFO level */
#घोषणा UART_TFL 	0x04	/* Transmitter FIFO level */
#घोषणा UART_ICR	0x05	/* Index Control Register */

/* The 16950 ICR रेजिस्टरs */
#घोषणा UART_ACR	0x00	/* Additional Control Register */
#घोषणा UART_CPR	0x01	/* Clock Prescalar Register */
#घोषणा UART_TCR	0x02	/* Times Clock Register */
#घोषणा UART_CKS	0x03	/* Clock Select Register */
#घोषणा UART_TTL	0x04	/* Transmitter Interrupt Trigger Level */
#घोषणा UART_RTL	0x05	/* Receiver Interrupt Trigger Level */
#घोषणा UART_FCL	0x06	/* Flow Control Level Lower */
#घोषणा UART_FCH	0x07	/* Flow Control Level Higher */
#घोषणा UART_ID1	0x08	/* ID #1 */
#घोषणा UART_ID2	0x09	/* ID #2 */
#घोषणा UART_ID3	0x0A	/* ID #3 */
#घोषणा UART_REV	0x0B	/* Revision */
#घोषणा UART_CSR	0x0C	/* Channel Software Reset */
#घोषणा UART_NMR	0x0D	/* Nine-bit Mode Register */
#घोषणा UART_CTR	0xFF

/*
 * The 16C950 Additional Control Register
 */
#घोषणा UART_ACR_RXDIS	0x01	/* Receiver disable */
#घोषणा UART_ACR_TXDIS	0x02	/* Transmitter disable */
#घोषणा UART_ACR_DSRFC	0x04	/* DSR Flow Control */
#घोषणा UART_ACR_TLENB	0x20	/* 950 trigger levels enable */
#घोषणा UART_ACR_ICRRD	0x40	/* ICR Read enable */
#घोषणा UART_ACR_ASREN	0x80	/* Additional status enable */



/*
 * These definitions are क्रम the RSA-DV II/S card, from
 *
 * Kiyokazu SUTO <suto@ks-and-ks.ne.jp>
 */

#घोषणा UART_RSA_BASE (-8)

#घोषणा UART_RSA_MSR ((UART_RSA_BASE) + 0) /* I/O: Mode Select Register */

#घोषणा UART_RSA_MSR_SWAP (1 << 0) /* Swap low/high 8 bytes in I/O port addr */
#घोषणा UART_RSA_MSR_FIFO (1 << 2) /* Enable the बाह्यal FIFO */
#घोषणा UART_RSA_MSR_FLOW (1 << 3) /* Enable the स्वतः RTS/CTS flow control */
#घोषणा UART_RSA_MSR_ITYP (1 << 4) /* Level (1) / Edge triger (0) */

#घोषणा UART_RSA_IER ((UART_RSA_BASE) + 1) /* I/O: Interrupt Enable Register */

#घोषणा UART_RSA_IER_Rx_FIFO_H (1 << 0) /* Enable Rx FIFO half full पूर्णांक. */
#घोषणा UART_RSA_IER_Tx_FIFO_H (1 << 1) /* Enable Tx FIFO half full पूर्णांक. */
#घोषणा UART_RSA_IER_Tx_FIFO_E (1 << 2) /* Enable Tx FIFO empty पूर्णांक. */
#घोषणा UART_RSA_IER_Rx_TOUT (1 << 3) /* Enable अक्षर receive समयout पूर्णांक */
#घोषणा UART_RSA_IER_TIMER (1 << 4) /* Enable समयr पूर्णांकerrupt */

#घोषणा UART_RSA_SRR ((UART_RSA_BASE) + 2) /* IN: Status Read Register */

#घोषणा UART_RSA_SRR_Tx_FIFO_NEMP (1 << 0) /* Tx FIFO is not empty (1) */
#घोषणा UART_RSA_SRR_Tx_FIFO_NHFL (1 << 1) /* Tx FIFO is not half full (1) */
#घोषणा UART_RSA_SRR_Tx_FIFO_NFUL (1 << 2) /* Tx FIFO is not full (1) */
#घोषणा UART_RSA_SRR_Rx_FIFO_NEMP (1 << 3) /* Rx FIFO is not empty (1) */
#घोषणा UART_RSA_SRR_Rx_FIFO_NHFL (1 << 4) /* Rx FIFO is not half full (1) */
#घोषणा UART_RSA_SRR_Rx_FIFO_NFUL (1 << 5) /* Rx FIFO is not full (1) */
#घोषणा UART_RSA_SRR_Rx_TOUT (1 << 6) /* Character reception समयout occurred (1) */
#घोषणा UART_RSA_SRR_TIMER (1 << 7) /* Timer पूर्णांकerrupt occurred */

#घोषणा UART_RSA_FRR ((UART_RSA_BASE) + 2) /* OUT: FIFO Reset Register */

#घोषणा UART_RSA_TIVSR ((UART_RSA_BASE) + 3) /* I/O: Timer Interval Value Set Register */

#घोषणा UART_RSA_TCR ((UART_RSA_BASE) + 4) /* OUT: Timer Control Register */

#घोषणा UART_RSA_TCR_SWITCH (1 << 0) /* Timer on */

/*
 * The RSA DSV/II board has two fixed घड़ी frequencies.  One is the
 * standard rate, and the other is 8 बार faster.
 */
#घोषणा SERIAL_RSA_BAUD_BASE (921600)
#घोषणा SERIAL_RSA_BAUD_BASE_LO (SERIAL_RSA_BAUD_BASE / 8)

/* Extra रेजिस्टरs क्रम TI DA8xx/66AK2x */
#घोषणा UART_DA830_PWREMU_MGMT	12

/* PWREMU_MGMT रेजिस्टर bits */
#घोषणा UART_DA830_PWREMU_MGMT_FREE	(1 << 0)  /* Free-running mode */
#घोषणा UART_DA830_PWREMU_MGMT_URRST	(1 << 13) /* Receiver reset/enable */
#घोषणा UART_DA830_PWREMU_MGMT_UTRST	(1 << 14) /* Transmitter reset/enable */

/*
 * Extra serial रेजिस्टर definitions क्रम the पूर्णांकernal UARTs
 * in TI OMAP processors.
 */
#घोषणा OMAP1_UART1_BASE	0xfffb0000
#घोषणा OMAP1_UART2_BASE	0xfffb0800
#घोषणा OMAP1_UART3_BASE	0xfffb9800
#घोषणा UART_OMAP_MDR1		0x08	/* Mode definition रेजिस्टर */
#घोषणा UART_OMAP_MDR2		0x09	/* Mode definition रेजिस्टर 2 */
#घोषणा UART_OMAP_SCR		0x10	/* Supplementary control रेजिस्टर */
#घोषणा UART_OMAP_SSR		0x11	/* Supplementary status रेजिस्टर */
#घोषणा UART_OMAP_EBLR		0x12	/* BOF length रेजिस्टर */
#घोषणा UART_OMAP_OSC_12M_SEL	0x13	/* OMAP1510 12MHz osc select */
#घोषणा UART_OMAP_MVER		0x14	/* Module version रेजिस्टर */
#घोषणा UART_OMAP_SYSC		0x15	/* System configuration रेजिस्टर */
#घोषणा UART_OMAP_SYSS		0x16	/* System status रेजिस्टर */
#घोषणा UART_OMAP_WER		0x17	/* Wake-up enable रेजिस्टर */
#घोषणा UART_OMAP_TX_LVL	0x1a	/* TX FIFO level रेजिस्टर */

/*
 * These are the definitions क्रम the MDR1 रेजिस्टर
 */
#घोषणा UART_OMAP_MDR1_16X_MODE		0x00	/* UART 16x mode */
#घोषणा UART_OMAP_MDR1_SIR_MODE		0x01	/* SIR mode */
#घोषणा UART_OMAP_MDR1_16X_ABAUD_MODE	0x02	/* UART 16x स्वतः-baud */
#घोषणा UART_OMAP_MDR1_13X_MODE		0x03	/* UART 13x mode */
#घोषणा UART_OMAP_MDR1_MIR_MODE		0x04	/* MIR mode */
#घोषणा UART_OMAP_MDR1_FIR_MODE		0x05	/* FIR mode */
#घोषणा UART_OMAP_MDR1_CIR_MODE		0x06	/* CIR mode */
#घोषणा UART_OMAP_MDR1_DISABLE		0x07	/* Disable (शेष state) */

/*
 * These are definitions क्रम the Altera ALTR_16550_F32/F64/F128
 * Normalized from 0x100 to 0x40 because of shअगरt by 2 (32 bit regs).
 */
#घोषणा UART_ALTR_AFR		0x40	/* Additional Features Register */
#घोषणा UART_ALTR_EN_TXFIFO_LW	0x01	/* Enable the TX FIFO Low Watermark */
#घोषणा UART_ALTR_TX_LOW	0x41	/* Tx FIFO Low Watermark */

#पूर्ण_अगर /* _LINUX_SERIAL_REG_H */

