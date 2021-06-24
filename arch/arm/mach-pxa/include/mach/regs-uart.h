<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARCH_REGS_UART_H
#घोषणा __ASM_ARCH_REGS_UART_H

/*
 * UARTs
 */

/* Full Function UART (FFUART) */
#घोषणा FFUART		FFRBR
#घोषणा FFRBR		__REG(0x40100000)  /* Receive Buffer Register (पढ़ो only) */
#घोषणा FFTHR		__REG(0x40100000)  /* Transmit Holding Register (ग_लिखो only) */
#घोषणा FFIER		__REG(0x40100004)  /* Interrupt Enable Register (पढ़ो/ग_लिखो) */
#घोषणा FFIIR		__REG(0x40100008)  /* Interrupt ID Register (पढ़ो only) */
#घोषणा FFFCR		__REG(0x40100008)  /* FIFO Control Register (ग_लिखो only) */
#घोषणा FFLCR		__REG(0x4010000C)  /* Line Control Register (पढ़ो/ग_लिखो) */
#घोषणा FFMCR		__REG(0x40100010)  /* Modem Control Register (पढ़ो/ग_लिखो) */
#घोषणा FFLSR		__REG(0x40100014)  /* Line Status Register (पढ़ो only) */
#घोषणा FFMSR		__REG(0x40100018)  /* Modem Status Register (पढ़ो only) */
#घोषणा FFSPR		__REG(0x4010001C)  /* Scratch Pad Register (पढ़ो/ग_लिखो) */
#घोषणा FFISR		__REG(0x40100020)  /* Infrared Selection Register (पढ़ो/ग_लिखो) */
#घोषणा FFDLL		__REG(0x40100000)  /* Divisor Latch Low Register (DLAB = 1) (पढ़ो/ग_लिखो) */
#घोषणा FFDLH		__REG(0x40100004)  /* Divisor Latch High Register (DLAB = 1) (पढ़ो/ग_लिखो) */

/* Bluetooth UART (BTUART) */
#घोषणा BTUART		BTRBR
#घोषणा BTRBR		__REG(0x40200000)  /* Receive Buffer Register (पढ़ो only) */
#घोषणा BTTHR		__REG(0x40200000)  /* Transmit Holding Register (ग_लिखो only) */
#घोषणा BTIER		__REG(0x40200004)  /* Interrupt Enable Register (पढ़ो/ग_लिखो) */
#घोषणा BTIIR		__REG(0x40200008)  /* Interrupt ID Register (पढ़ो only) */
#घोषणा BTFCR		__REG(0x40200008)  /* FIFO Control Register (ग_लिखो only) */
#घोषणा BTLCR		__REG(0x4020000C)  /* Line Control Register (पढ़ो/ग_लिखो) */
#घोषणा BTMCR		__REG(0x40200010)  /* Modem Control Register (पढ़ो/ग_लिखो) */
#घोषणा BTLSR		__REG(0x40200014)  /* Line Status Register (पढ़ो only) */
#घोषणा BTMSR		__REG(0x40200018)  /* Modem Status Register (पढ़ो only) */
#घोषणा BTSPR		__REG(0x4020001C)  /* Scratch Pad Register (पढ़ो/ग_लिखो) */
#घोषणा BTISR		__REG(0x40200020)  /* Infrared Selection Register (पढ़ो/ग_लिखो) */
#घोषणा BTDLL		__REG(0x40200000)  /* Divisor Latch Low Register (DLAB = 1) (पढ़ो/ग_लिखो) */
#घोषणा BTDLH		__REG(0x40200004)  /* Divisor Latch High Register (DLAB = 1) (पढ़ो/ग_लिखो) */

/* Standard UART (STUART) */
#घोषणा STUART		STRBR
#घोषणा STRBR		__REG(0x40700000)  /* Receive Buffer Register (पढ़ो only) */
#घोषणा STTHR		__REG(0x40700000)  /* Transmit Holding Register (ग_लिखो only) */
#घोषणा STIER		__REG(0x40700004)  /* Interrupt Enable Register (पढ़ो/ग_लिखो) */
#घोषणा STIIR		__REG(0x40700008)  /* Interrupt ID Register (पढ़ो only) */
#घोषणा STFCR		__REG(0x40700008)  /* FIFO Control Register (ग_लिखो only) */
#घोषणा STLCR		__REG(0x4070000C)  /* Line Control Register (पढ़ो/ग_लिखो) */
#घोषणा STMCR		__REG(0x40700010)  /* Modem Control Register (पढ़ो/ग_लिखो) */
#घोषणा STLSR		__REG(0x40700014)  /* Line Status Register (पढ़ो only) */
#घोषणा STMSR		__REG(0x40700018)  /* Reserved */
#घोषणा STSPR		__REG(0x4070001C)  /* Scratch Pad Register (पढ़ो/ग_लिखो) */
#घोषणा STISR		__REG(0x40700020)  /* Infrared Selection Register (पढ़ो/ग_लिखो) */
#घोषणा STDLL		__REG(0x40700000)  /* Divisor Latch Low Register (DLAB = 1) (पढ़ो/ग_लिखो) */
#घोषणा STDLH		__REG(0x40700004)  /* Divisor Latch High Register (DLAB = 1) (पढ़ो/ग_लिखो) */

/* Hardware UART (HWUART) */
#घोषणा HWUART		HWRBR
#घोषणा HWRBR		__REG(0x41600000)  /* Receive Buffer Register (पढ़ो only) */
#घोषणा HWTHR		__REG(0x41600000)  /* Transmit Holding Register (ग_लिखो only) */
#घोषणा HWIER		__REG(0x41600004)  /* Interrupt Enable Register (पढ़ो/ग_लिखो) */
#घोषणा HWIIR		__REG(0x41600008)  /* Interrupt ID Register (पढ़ो only) */
#घोषणा HWFCR		__REG(0x41600008)  /* FIFO Control Register (ग_लिखो only) */
#घोषणा HWLCR		__REG(0x4160000C)  /* Line Control Register (पढ़ो/ग_लिखो) */
#घोषणा HWMCR		__REG(0x41600010)  /* Modem Control Register (पढ़ो/ग_लिखो) */
#घोषणा HWLSR		__REG(0x41600014)  /* Line Status Register (पढ़ो only) */
#घोषणा HWMSR		__REG(0x41600018)  /* Modem Status Register (पढ़ो only) */
#घोषणा HWSPR		__REG(0x4160001C)  /* Scratch Pad Register (पढ़ो/ग_लिखो) */
#घोषणा HWISR		__REG(0x41600020)  /* Infrared Selection Register (पढ़ो/ग_लिखो) */
#घोषणा HWFOR		__REG(0x41600024)  /* Receive FIFO Occupancy Register (पढ़ो only) */
#घोषणा HWABR		__REG(0x41600028)  /* Auto-Baud Control Register (पढ़ो/ग_लिखो) */
#घोषणा HWACR		__REG(0x4160002C)  /* Auto-Baud Count Register (पढ़ो only) */
#घोषणा HWDLL		__REG(0x41600000)  /* Divisor Latch Low Register (DLAB = 1) (पढ़ो/ग_लिखो) */
#घोषणा HWDLH		__REG(0x41600004)  /* Divisor Latch High Register (DLAB = 1) (पढ़ो/ग_लिखो) */

#घोषणा IER_DMAE	(1 << 7)	/* DMA Requests Enable */
#घोषणा IER_UUE		(1 << 6)	/* UART Unit Enable */
#घोषणा IER_NRZE	(1 << 5)	/* NRZ coding Enable */
#घोषणा IER_RTIOE	(1 << 4)	/* Receiver Time Out Interrupt Enable */
#घोषणा IER_MIE		(1 << 3)	/* Modem Interrupt Enable */
#घोषणा IER_RLSE	(1 << 2)	/* Receiver Line Status Interrupt Enable */
#घोषणा IER_TIE		(1 << 1)	/* Transmit Data request Interrupt Enable */
#घोषणा IER_RAVIE	(1 << 0)	/* Receiver Data Available Interrupt Enable */

#घोषणा IIR_FIFOES1	(1 << 7)	/* FIFO Mode Enable Status */
#घोषणा IIR_FIFOES0	(1 << 6)	/* FIFO Mode Enable Status */
#घोषणा IIR_TOD		(1 << 3)	/* Time Out Detected */
#घोषणा IIR_IID2	(1 << 2)	/* Interrupt Source Encoded */
#घोषणा IIR_IID1	(1 << 1)	/* Interrupt Source Encoded */
#घोषणा IIR_IP		(1 << 0)	/* Interrupt Pending (active low) */

#घोषणा FCR_ITL2	(1 << 7)	/* Interrupt Trigger Level */
#घोषणा FCR_ITL1	(1 << 6)	/* Interrupt Trigger Level */
#घोषणा FCR_RESETTF	(1 << 2)	/* Reset Transmitter FIFO */
#घोषणा FCR_RESETRF	(1 << 1)	/* Reset Receiver FIFO */
#घोषणा FCR_TRFIFOE	(1 << 0)	/* Transmit and Receive FIFO Enable */
#घोषणा FCR_ITL_1	(0)
#घोषणा FCR_ITL_8	(FCR_ITL1)
#घोषणा FCR_ITL_16	(FCR_ITL2)
#घोषणा FCR_ITL_32	(FCR_ITL2|FCR_ITL1)

#घोषणा LCR_DLAB	(1 << 7)	/* Divisor Latch Access Bit */
#घोषणा LCR_SB		(1 << 6)	/* Set Break */
#घोषणा LCR_STKYP	(1 << 5)	/* Sticky Parity */
#घोषणा LCR_EPS		(1 << 4)	/* Even Parity Select */
#घोषणा LCR_PEN		(1 << 3)	/* Parity Enable */
#घोषणा LCR_STB		(1 << 2)	/* Stop Bit */
#घोषणा LCR_WLS1	(1 << 1)	/* Word Length Select */
#घोषणा LCR_WLS0	(1 << 0)	/* Word Length Select */

#घोषणा LSR_FIFOE	(1 << 7)	/* FIFO Error Status */
#घोषणा LSR_TEMT	(1 << 6)	/* Transmitter Empty */
#घोषणा LSR_TDRQ	(1 << 5)	/* Transmit Data Request */
#घोषणा LSR_BI		(1 << 4)	/* Break Interrupt */
#घोषणा LSR_FE		(1 << 3)	/* Framing Error */
#घोषणा LSR_PE		(1 << 2)	/* Parity Error */
#घोषणा LSR_OE		(1 << 1)	/* Overrun Error */
#घोषणा LSR_DR		(1 << 0)	/* Data Ready */

#घोषणा MCR_LOOP	(1 << 4)
#घोषणा MCR_OUT2	(1 << 3)	/* क्रमce MSR_DCD in loopback mode */
#घोषणा MCR_OUT1	(1 << 2)	/* क्रमce MSR_RI in loopback mode */
#घोषणा MCR_RTS		(1 << 1)	/* Request to Send */
#घोषणा MCR_DTR		(1 << 0)	/* Data Terminal Ready */

#घोषणा MSR_DCD		(1 << 7)	/* Data Carrier Detect */
#घोषणा MSR_RI		(1 << 6)	/* Ring Indicator */
#घोषणा MSR_DSR		(1 << 5)	/* Data Set Ready */
#घोषणा MSR_CTS		(1 << 4)	/* Clear To Send */
#घोषणा MSR_DDCD	(1 << 3)	/* Delta Data Carrier Detect */
#घोषणा MSR_TERI	(1 << 2)	/* Trailing Edge Ring Indicator */
#घोषणा MSR_DDSR	(1 << 1)	/* Delta Data Set Ready */
#घोषणा MSR_DCTS	(1 << 0)	/* Delta Clear To Send */

/*
 * IrSR (Infrared Selection Register)
 */
#घोषणा STISR_RXPL      (1 << 4)        /* Receive Data Polarity */
#घोषणा STISR_TXPL      (1 << 3)        /* Transmit Data Polarity */
#घोषणा STISR_XMODE     (1 << 2)        /* Transmit Pulse Width Select */
#घोषणा STISR_RCVEIR    (1 << 1)        /* Receiver SIR Enable */
#घोषणा STISR_XMITIR    (1 << 0)        /* Transmitter SIR Enable */

#पूर्ण_अगर /* __ASM_ARCH_REGS_UART_H */
