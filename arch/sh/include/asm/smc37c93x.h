<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_SMC37C93X_H
#घोषणा __ASM_SH_SMC37C93X_H

/*
 * linux/include/यंत्र-sh/smc37c93x.h
 *
 * Copyright (C) 2000  Kazumoto Kojima
 *
 * SMSC 37C93x Super IO Chip support
 */

/* Default base I/O address */
#घोषणा FDC_PRIMARY_BASE	0x3f0
#घोषणा IDE1_PRIMARY_BASE	0x1f0
#घोषणा IDE1_SECONDARY_BASE	0x170
#घोषणा PARPORT_PRIMARY_BASE	0x378
#घोषणा COM1_PRIMARY_BASE	0x2f8
#घोषणा COM2_PRIMARY_BASE	0x3f8
#घोषणा RTC_PRIMARY_BASE	0x070
#घोषणा KBC_PRIMARY_BASE	0x060
#घोषणा AUXIO_PRIMARY_BASE	0x000	/* XXX */

/* Logical device number */
#घोषणा LDN_FDC			0
#घोषणा LDN_IDE1		1
#घोषणा LDN_IDE2		2
#घोषणा LDN_PARPORT		3
#घोषणा LDN_COM1		4
#घोषणा LDN_COM2		5
#घोषणा LDN_RTC			6
#घोषणा LDN_KBC			7
#घोषणा LDN_AUXIO		8

/* Configuration port and key */
#घोषणा CONFIG_PORT		0x3f0
#घोषणा INDEX_PORT		CONFIG_PORT
#घोषणा DATA_PORT		0x3f1
#घोषणा CONFIG_ENTER		0x55
#घोषणा CONFIG_EXIT		0xaa

/* Configuration index */
#घोषणा CURRENT_LDN_INDEX	0x07
#घोषणा POWER_CONTROL_INDEX	0x22
#घोषणा ACTIVATE_INDEX		0x30
#घोषणा IO_BASE_HI_INDEX	0x60
#घोषणा IO_BASE_LO_INDEX	0x61
#घोषणा IRQ_SELECT_INDEX	0x70
#घोषणा DMA_SELECT_INDEX	0x74

#घोषणा GPIO46_INDEX		0xc6
#घोषणा GPIO47_INDEX		0xc7

/* UART stuff. Only क्रम debugging.  */
/* UART Register */

#घोषणा UART_RBR	0x0	/* Receiver Buffer Register (Read Only) */
#घोषणा UART_THR	0x0	/* Transmitter Holding Register (Write Only) */
#घोषणा UART_IER	0x2	/* Interrupt Enable Register */
#घोषणा UART_IIR	0x4	/* Interrupt Ident Register (Read Only) */
#घोषणा UART_FCR	0x4	/* FIFO Control Register (Write Only) */
#घोषणा UART_LCR	0x6	/* Line Control Register */
#घोषणा UART_MCR	0x8	/* MODEM Control Register */
#घोषणा UART_LSR	0xa	/* Line Status Register */
#घोषणा UART_MSR	0xc	/* MODEM Status Register */
#घोषणा UART_SCR	0xe	/* Scratch Register */
#घोषणा UART_DLL	0x0	/* Divisor Latch (LS) */
#घोषणा UART_DLM	0x2	/* Divisor Latch (MS) */

#अगर_अघोषित __ASSEMBLY__
प्रकार काष्ठा uart_reg अणु
	अस्थिर __u16 rbr;
	अस्थिर __u16 ier;
	अस्थिर __u16 iir;
	अस्थिर __u16 lcr;
	अस्थिर __u16 mcr;
	अस्थिर __u16 lsr;
	अस्थिर __u16 msr;
	अस्थिर __u16 scr;
पूर्ण uart_reg;
#पूर्ण_अगर /* ! __ASSEMBLY__ */

/* Alias क्रम Write Only Register */

#घोषणा thr	rbr
#घोषणा tcr	iir

/* Alias क्रम Divisor Latch Register */

#घोषणा dll	rbr
#घोषणा dlm	ier
#घोषणा fcr	iir

/* Interrupt Enable Register */

#घोषणा IER_ERDAI	0x0100	/* Enable Received Data Available Interrupt */
#घोषणा IER_ETHREI	0x0200	/* Enable Transmitter Holding Register Empty Interrupt */
#घोषणा IER_ELSI	0x0400	/* Enable Receiver Line Status Interrupt */
#घोषणा IER_EMSI	0x0800	/* Enable MODEM Status Interrupt */

/* Interrupt Ident Register */

#घोषणा IIR_IP		0x0100	/* "0" अगर Interrupt Pending */
#घोषणा IIR_IIB0	0x0200	/* Interrupt ID Bit 0 */
#घोषणा IIR_IIB1	0x0400	/* Interrupt ID Bit 1 */
#घोषणा IIR_IIB2	0x0800	/* Interrupt ID Bit 2 */
#घोषणा IIR_FIFO	0xc000	/* FIFOs enabled */

/* FIFO Control Register */

#घोषणा FCR_FEN		0x0100	/* FIFO enable */
#घोषणा FCR_RFRES	0x0200	/* Receiver FIFO reset */
#घोषणा FCR_TFRES	0x0400	/* Transmitter FIFO reset */
#घोषणा FCR_DMA		0x0800	/* DMA mode select */
#घोषणा FCR_RTL		0x4000	/* Receiver trigger (LSB) */
#घोषणा FCR_RTM		0x8000	/* Receiver trigger (MSB) */

/* Line Control Register */

#घोषणा LCR_WLS0	0x0100	/* Word Length Select Bit 0 */
#घोषणा LCR_WLS1	0x0200	/* Word Length Select Bit 1 */
#घोषणा LCR_STB		0x0400	/* Number of Stop Bits */
#घोषणा LCR_PEN		0x0800	/* Parity Enable */
#घोषणा LCR_EPS		0x1000	/* Even Parity Select */
#घोषणा LCR_SP		0x2000	/* Stick Parity */
#घोषणा LCR_SB		0x4000	/* Set Break */
#घोषणा LCR_DLAB	0x8000	/* Divisor Latch Access Bit */

/* MODEM Control Register */

#घोषणा MCR_DTR		0x0100	/* Data Terminal Ready */
#घोषणा MCR_RTS		0x0200	/* Request to Send */
#घोषणा MCR_OUT1	0x0400	/* Out 1 */
#घोषणा MCR_IRQEN	0x0800	/* IRQ Enable */
#घोषणा MCR_LOOP	0x1000	/* Loop */

/* Line Status Register */

#घोषणा LSR_DR		0x0100	/* Data Ready */
#घोषणा LSR_OE		0x0200	/* Overrun Error */
#घोषणा LSR_PE		0x0400	/* Parity Error */
#घोषणा LSR_FE		0x0800	/* Framing Error */
#घोषणा LSR_BI		0x1000	/* Break Interrupt */
#घोषणा LSR_THRE	0x2000	/* Transmitter Holding Register Empty */
#घोषणा LSR_TEMT	0x4000	/* Transmitter Empty */
#घोषणा LSR_FIFOE	0x8000	/* Receiver FIFO error */

/* MODEM Status Register */

#घोषणा MSR_DCTS	0x0100	/* Delta Clear to Send */
#घोषणा MSR_DDSR	0x0200	/* Delta Data Set Ready */
#घोषणा MSR_TERI	0x0400	/* Trailing Edge Ring Indicator */
#घोषणा MSR_DDCD	0x0800	/* Delta Data Carrier Detect */
#घोषणा MSR_CTS		0x1000	/* Clear to Send */
#घोषणा MSR_DSR		0x2000	/* Data Set Ready */
#घोषणा MSR_RI		0x4000	/* Ring Indicator */
#घोषणा MSR_DCD		0x8000	/* Data Carrier Detect */

/* Baud Rate Divisor */

#घोषणा UART_CLK	(1843200)	/* 1.8432 MHz */
#घोषणा UART_BAUD(x)	(UART_CLK / (16 * (x)))

/* RTC रेजिस्टर definition */
#घोषणा RTC_SECONDS             0
#घोषणा RTC_SECONDS_ALARM       1
#घोषणा RTC_MINUTES             2
#घोषणा RTC_MINUTES_ALARM       3
#घोषणा RTC_HOURS               4
#घोषणा RTC_HOURS_ALARM         5
#घोषणा RTC_DAY_OF_WEEK         6
#घोषणा RTC_DAY_OF_MONTH        7
#घोषणा RTC_MONTH               8
#घोषणा RTC_YEAR                9
#घोषणा RTC_FREQ_SELECT		10
# define RTC_UIP 0x80
# define RTC_DIV_CTL 0x70
/* This RTC can work under 32.768KHz घड़ी only.  */
# define RTC_OSC_ENABLE 0x20
# define RTC_OSC_DISABLE 0x00
#घोषणा RTC_CONTROL     	11
# define RTC_SET 0x80
# define RTC_PIE 0x40
# define RTC_AIE 0x20
# define RTC_UIE 0x10
# define RTC_SQWE 0x08
# define RTC_DM_BINARY 0x04
# define RTC_24H 0x02
# define RTC_DST_EN 0x01

#पूर्ण_अगर  /* __ASM_SH_SMC37C93X_H */
