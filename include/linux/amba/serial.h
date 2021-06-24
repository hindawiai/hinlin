<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  linux/include/यंत्र-arm/hardware/serial_amba.h
 *
 *  Internal header file क्रम AMBA serial ports
 *
 *  Copyright (C) ARM Limited
 *  Copyright (C) 2000 Deep Blue Solutions Ltd.
 */
#अगर_अघोषित ASM_ARM_HARDWARE_SERIAL_AMBA_H
#घोषणा ASM_ARM_HARDWARE_SERIAL_AMBA_H

#समावेश <linux/types.h>

/* -------------------------------------------------------------------------------
 *  From AMBA UART (PL010) Block Specअगरication
 * -------------------------------------------------------------------------------
 *  UART Register Offsets.
 */
#घोषणा UART01x_DR		0x00	/* Data पढ़ो or written from the पूर्णांकerface. */
#घोषणा UART01x_RSR		0x04	/* Receive status रेजिस्टर (Read). */
#घोषणा UART01x_ECR		0x04	/* Error clear रेजिस्टर (Write). */
#घोषणा UART010_LCRH		0x08	/* Line control रेजिस्टर, high byte. */
#घोषणा ST_UART011_DMAWM	0x08    /* DMA watermark configure रेजिस्टर. */
#घोषणा UART010_LCRM		0x0C	/* Line control रेजिस्टर, middle byte. */
#घोषणा ST_UART011_TIMEOUT	0x0C    /* Timeout period रेजिस्टर. */
#घोषणा UART010_LCRL		0x10	/* Line control रेजिस्टर, low byte. */
#घोषणा UART010_CR		0x14	/* Control रेजिस्टर. */
#घोषणा UART01x_FR		0x18	/* Flag रेजिस्टर (Read only). */
#घोषणा UART010_IIR		0x1C	/* Interrupt identअगरication रेजिस्टर (Read). */
#घोषणा UART010_ICR		0x1C	/* Interrupt clear रेजिस्टर (Write). */
#घोषणा ST_UART011_LCRH_RX	0x1C    /* Rx line control रेजिस्टर. */
#घोषणा UART01x_ILPR		0x20	/* IrDA low घातer counter रेजिस्टर. */
#घोषणा UART011_IBRD		0x24	/* Integer baud rate भागisor रेजिस्टर. */
#घोषणा UART011_FBRD		0x28	/* Fractional baud rate भागisor रेजिस्टर. */
#घोषणा UART011_LCRH		0x2c	/* Line control रेजिस्टर. */
#घोषणा ST_UART011_LCRH_TX	0x2c    /* Tx Line control रेजिस्टर. */
#घोषणा UART011_CR		0x30	/* Control रेजिस्टर. */
#घोषणा UART011_IFLS		0x34	/* Interrupt fअगरo level select. */
#घोषणा UART011_IMSC		0x38	/* Interrupt mask. */
#घोषणा UART011_RIS		0x3c	/* Raw पूर्णांकerrupt status. */
#घोषणा UART011_MIS		0x40	/* Masked पूर्णांकerrupt status. */
#घोषणा UART011_ICR		0x44	/* Interrupt clear रेजिस्टर. */
#घोषणा UART011_DMACR		0x48	/* DMA control रेजिस्टर. */
#घोषणा ST_UART011_XFCR		0x50	/* XON/XOFF control रेजिस्टर. */
#घोषणा ST_UART011_XON1		0x54	/* XON1 रेजिस्टर. */
#घोषणा ST_UART011_XON2		0x58	/* XON2 रेजिस्टर. */
#घोषणा ST_UART011_XOFF1	0x5C	/* XON1 रेजिस्टर. */
#घोषणा ST_UART011_XOFF2	0x60	/* XON2 रेजिस्टर. */
#घोषणा ST_UART011_ITCR		0x80	/* Integration test control रेजिस्टर. */
#घोषणा ST_UART011_ITIP		0x84	/* Integration test input रेजिस्टर. */
#घोषणा ST_UART011_ABCR		0x100	/* Autobaud control रेजिस्टर. */
#घोषणा ST_UART011_ABIMSC	0x15C	/* Autobaud पूर्णांकerrupt mask/clear रेजिस्टर. */

/*
 * ZTE UART रेजिस्टर offsets.  This UART has a radically dअगरferent address
 * allocation from the ARM and ST variants, so we list all रेजिस्टरs here.
 * We assume unlisted रेजिस्टरs करो not exist.
 */
#घोषणा ZX_UART011_DR		0x04
#घोषणा ZX_UART011_FR		0x14
#घोषणा ZX_UART011_IBRD		0x24
#घोषणा ZX_UART011_FBRD		0x28
#घोषणा ZX_UART011_LCRH		0x30
#घोषणा ZX_UART011_CR		0x34
#घोषणा ZX_UART011_IFLS		0x38
#घोषणा ZX_UART011_IMSC		0x40
#घोषणा ZX_UART011_RIS		0x44
#घोषणा ZX_UART011_MIS		0x48
#घोषणा ZX_UART011_ICR		0x4c
#घोषणा ZX_UART011_DMACR	0x50

#घोषणा UART011_DR_OE		(1 << 11)
#घोषणा UART011_DR_BE		(1 << 10)
#घोषणा UART011_DR_PE		(1 << 9)
#घोषणा UART011_DR_FE		(1 << 8)

#घोषणा UART01x_RSR_OE 		0x08
#घोषणा UART01x_RSR_BE 		0x04
#घोषणा UART01x_RSR_PE 		0x02
#घोषणा UART01x_RSR_FE 		0x01

#घोषणा UART011_FR_RI		0x100
#घोषणा UART011_FR_TXFE		0x080
#घोषणा UART011_FR_RXFF		0x040
#घोषणा UART01x_FR_TXFF		0x020
#घोषणा UART01x_FR_RXFE		0x010
#घोषणा UART01x_FR_BUSY		0x008
#घोषणा UART01x_FR_DCD 		0x004
#घोषणा UART01x_FR_DSR 		0x002
#घोषणा UART01x_FR_CTS 		0x001
#घोषणा UART01x_FR_TMSK		(UART01x_FR_TXFF + UART01x_FR_BUSY)

/*
 * Some bits of Flag Register on ZTE device have dअगरferent position from
 * standard ones.
 */
#घोषणा ZX_UART01x_FR_BUSY	0x100
#घोषणा ZX_UART01x_FR_DSR	0x008
#घोषणा ZX_UART01x_FR_CTS	0x002
#घोषणा ZX_UART011_FR_RI	0x001

#घोषणा UART011_CR_CTSEN	0x8000	/* CTS hardware flow control */
#घोषणा UART011_CR_RTSEN	0x4000	/* RTS hardware flow control */
#घोषणा UART011_CR_OUT2		0x2000	/* OUT2 */
#घोषणा UART011_CR_OUT1		0x1000	/* OUT1 */
#घोषणा UART011_CR_RTS		0x0800	/* RTS */
#घोषणा UART011_CR_DTR		0x0400	/* DTR */
#घोषणा UART011_CR_RXE		0x0200	/* receive enable */
#घोषणा UART011_CR_TXE		0x0100	/* transmit enable */
#घोषणा UART011_CR_LBE		0x0080	/* loopback enable */
#घोषणा UART010_CR_RTIE		0x0040
#घोषणा UART010_CR_TIE 		0x0020
#घोषणा UART010_CR_RIE 		0x0010
#घोषणा UART010_CR_MSIE		0x0008
#घोषणा ST_UART011_CR_OVSFACT	0x0008	/* Oversampling factor */
#घोषणा UART01x_CR_IIRLP	0x0004	/* SIR low घातer mode */
#घोषणा UART01x_CR_SIREN	0x0002	/* SIR enable */
#घोषणा UART01x_CR_UARTEN	0x0001	/* UART enable */
 
#घोषणा UART011_LCRH_SPS	0x80
#घोषणा UART01x_LCRH_WLEN_8	0x60
#घोषणा UART01x_LCRH_WLEN_7	0x40
#घोषणा UART01x_LCRH_WLEN_6	0x20
#घोषणा UART01x_LCRH_WLEN_5	0x00
#घोषणा UART01x_LCRH_FEN	0x10
#घोषणा UART01x_LCRH_STP2	0x08
#घोषणा UART01x_LCRH_EPS	0x04
#घोषणा UART01x_LCRH_PEN	0x02
#घोषणा UART01x_LCRH_BRK	0x01

#घोषणा ST_UART011_DMAWM_RX_1	(0 << 3)
#घोषणा ST_UART011_DMAWM_RX_2	(1 << 3)
#घोषणा ST_UART011_DMAWM_RX_4	(2 << 3)
#घोषणा ST_UART011_DMAWM_RX_8	(3 << 3)
#घोषणा ST_UART011_DMAWM_RX_16	(4 << 3)
#घोषणा ST_UART011_DMAWM_RX_32	(5 << 3)
#घोषणा ST_UART011_DMAWM_RX_48	(6 << 3)
#घोषणा ST_UART011_DMAWM_TX_1	0
#घोषणा ST_UART011_DMAWM_TX_2	1
#घोषणा ST_UART011_DMAWM_TX_4	2
#घोषणा ST_UART011_DMAWM_TX_8	3
#घोषणा ST_UART011_DMAWM_TX_16	4
#घोषणा ST_UART011_DMAWM_TX_32	5
#घोषणा ST_UART011_DMAWM_TX_48	6

#घोषणा UART010_IIR_RTIS	0x08
#घोषणा UART010_IIR_TIS		0x04
#घोषणा UART010_IIR_RIS		0x02
#घोषणा UART010_IIR_MIS		0x01

#घोषणा UART011_IFLS_RX1_8	(0 << 3)
#घोषणा UART011_IFLS_RX2_8	(1 << 3)
#घोषणा UART011_IFLS_RX4_8	(2 << 3)
#घोषणा UART011_IFLS_RX6_8	(3 << 3)
#घोषणा UART011_IFLS_RX7_8	(4 << 3)
#घोषणा UART011_IFLS_TX1_8	(0 << 0)
#घोषणा UART011_IFLS_TX2_8	(1 << 0)
#घोषणा UART011_IFLS_TX4_8	(2 << 0)
#घोषणा UART011_IFLS_TX6_8	(3 << 0)
#घोषणा UART011_IFLS_TX7_8	(4 << 0)
/* special values क्रम ST venकरोr with deeper fअगरo */
#घोषणा UART011_IFLS_RX_HALF	(5 << 3)
#घोषणा UART011_IFLS_TX_HALF	(5 << 0)

#घोषणा UART011_OEIM		(1 << 10)	/* overrun error पूर्णांकerrupt mask */
#घोषणा UART011_BEIM		(1 << 9)	/* अवरोध error पूर्णांकerrupt mask */
#घोषणा UART011_PEIM		(1 << 8)	/* parity error पूर्णांकerrupt mask */
#घोषणा UART011_FEIM		(1 << 7)	/* framing error पूर्णांकerrupt mask */
#घोषणा UART011_RTIM		(1 << 6)	/* receive समयout पूर्णांकerrupt mask */
#घोषणा UART011_TXIM		(1 << 5)	/* transmit पूर्णांकerrupt mask */
#घोषणा UART011_RXIM		(1 << 4)	/* receive पूर्णांकerrupt mask */
#घोषणा UART011_DSRMIM		(1 << 3)	/* DSR पूर्णांकerrupt mask */
#घोषणा UART011_DCDMIM		(1 << 2)	/* DCD पूर्णांकerrupt mask */
#घोषणा UART011_CTSMIM		(1 << 1)	/* CTS पूर्णांकerrupt mask */
#घोषणा UART011_RIMIM		(1 << 0)	/* RI पूर्णांकerrupt mask */

#घोषणा UART011_OEIS		(1 << 10)	/* overrun error पूर्णांकerrupt status */
#घोषणा UART011_BEIS		(1 << 9)	/* अवरोध error पूर्णांकerrupt status */
#घोषणा UART011_PEIS		(1 << 8)	/* parity error पूर्णांकerrupt status */
#घोषणा UART011_FEIS		(1 << 7)	/* framing error पूर्णांकerrupt status */
#घोषणा UART011_RTIS		(1 << 6)	/* receive समयout पूर्णांकerrupt status */
#घोषणा UART011_TXIS		(1 << 5)	/* transmit पूर्णांकerrupt status */
#घोषणा UART011_RXIS		(1 << 4)	/* receive पूर्णांकerrupt status */
#घोषणा UART011_DSRMIS		(1 << 3)	/* DSR पूर्णांकerrupt status */
#घोषणा UART011_DCDMIS		(1 << 2)	/* DCD पूर्णांकerrupt status */
#घोषणा UART011_CTSMIS		(1 << 1)	/* CTS पूर्णांकerrupt status */
#घोषणा UART011_RIMIS		(1 << 0)	/* RI पूर्णांकerrupt status */

#घोषणा UART011_OEIC		(1 << 10)	/* overrun error पूर्णांकerrupt clear */
#घोषणा UART011_BEIC		(1 << 9)	/* अवरोध error पूर्णांकerrupt clear */
#घोषणा UART011_PEIC		(1 << 8)	/* parity error पूर्णांकerrupt clear */
#घोषणा UART011_FEIC		(1 << 7)	/* framing error पूर्णांकerrupt clear */
#घोषणा UART011_RTIC		(1 << 6)	/* receive समयout पूर्णांकerrupt clear */
#घोषणा UART011_TXIC		(1 << 5)	/* transmit पूर्णांकerrupt clear */
#घोषणा UART011_RXIC		(1 << 4)	/* receive पूर्णांकerrupt clear */
#घोषणा UART011_DSRMIC		(1 << 3)	/* DSR पूर्णांकerrupt clear */
#घोषणा UART011_DCDMIC		(1 << 2)	/* DCD पूर्णांकerrupt clear */
#घोषणा UART011_CTSMIC		(1 << 1)	/* CTS पूर्णांकerrupt clear */
#घोषणा UART011_RIMIC		(1 << 0)	/* RI पूर्णांकerrupt clear */

#घोषणा UART011_DMAONERR	(1 << 2)	/* disable dma on error */
#घोषणा UART011_TXDMAE		(1 << 1)	/* enable transmit dma */
#घोषणा UART011_RXDMAE		(1 << 0)	/* enable receive dma */

#घोषणा UART01x_RSR_ANY		(UART01x_RSR_OE|UART01x_RSR_BE|UART01x_RSR_PE|UART01x_RSR_FE)
#घोषणा UART01x_FR_MODEM_ANY	(UART01x_FR_DCD|UART01x_FR_DSR|UART01x_FR_CTS)

#अगर_अघोषित __ASSEMBLY__
काष्ठा amba_device; /* in uncompress this is included but amba/bus.h is not */
काष्ठा amba_pl010_data अणु
	व्योम (*set_mctrl)(काष्ठा amba_device *dev, व्योम __iomem *base, अचिन्हित पूर्णांक mctrl);
पूर्ण;

काष्ठा dma_chan;
काष्ठा amba_pl011_data अणु
	bool (*dma_filter)(काष्ठा dma_chan *chan, व्योम *filter_param);
	व्योम *dma_rx_param;
	व्योम *dma_tx_param;
	bool dma_rx_poll_enable;
	अचिन्हित पूर्णांक dma_rx_poll_rate;
	अचिन्हित पूर्णांक dma_rx_poll_समयout;
        व्योम (*init) (व्योम);
	व्योम (*निकास) (व्योम);
पूर्ण;
#पूर्ण_अगर

#पूर्ण_अगर
