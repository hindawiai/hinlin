<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Application UART driver क्रम:
 *	Freescale STMP37XX/STMP378X
 *	Alphascale ASM9260
 *
 * Author: dmitry pervushin <dimka@embeddedalley.com>
 *
 * Copyright 2014 Oleksij Rempel <linux@rempel-privat.de>
 *	Provide Alphascale ASM9260 support.
 * Copyright 2008-2010 Freescale Semiconductor, Inc.
 * Copyright 2008 Embedded Alley Solutions, Inc All Rights Reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_driver.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/device.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/irq.h>
#समावेश "serial_mctrl_gpio.h"

#घोषणा MXS_AUART_PORTS 5
#घोषणा MXS_AUART_FIFO_SIZE		16

#घोषणा SET_REG				0x4
#घोषणा CLR_REG				0x8
#घोषणा TOG_REG				0xc

#घोषणा AUART_CTRL0			0x00000000
#घोषणा AUART_CTRL1			0x00000010
#घोषणा AUART_CTRL2			0x00000020
#घोषणा AUART_LINECTRL			0x00000030
#घोषणा AUART_LINECTRL2			0x00000040
#घोषणा AUART_INTR			0x00000050
#घोषणा AUART_DATA			0x00000060
#घोषणा AUART_STAT			0x00000070
#घोषणा AUART_DEBUG			0x00000080
#घोषणा AUART_VERSION			0x00000090
#घोषणा AUART_AUTOBAUD			0x000000a0

#घोषणा AUART_CTRL0_SFTRST			(1 << 31)
#घोषणा AUART_CTRL0_CLKGATE			(1 << 30)
#घोषणा AUART_CTRL0_RXTO_ENABLE			(1 << 27)
#घोषणा AUART_CTRL0_RXTIMEOUT(v)		(((v) & 0x7ff) << 16)
#घोषणा AUART_CTRL0_XFER_COUNT(v)		((v) & 0xffff)

#घोषणा AUART_CTRL1_XFER_COUNT(v)		((v) & 0xffff)

#घोषणा AUART_CTRL2_DMAONERR			(1 << 26)
#घोषणा AUART_CTRL2_TXDMAE			(1 << 25)
#घोषणा AUART_CTRL2_RXDMAE			(1 << 24)

#घोषणा AUART_CTRL2_CTSEN			(1 << 15)
#घोषणा AUART_CTRL2_RTSEN			(1 << 14)
#घोषणा AUART_CTRL2_RTS				(1 << 11)
#घोषणा AUART_CTRL2_RXE				(1 << 9)
#घोषणा AUART_CTRL2_TXE				(1 << 8)
#घोषणा AUART_CTRL2_UARTEN			(1 << 0)

#घोषणा AUART_LINECTRL_BAUD_DIV_MAX		0x003fffc0
#घोषणा AUART_LINECTRL_BAUD_DIV_MIN		0x000000ec
#घोषणा AUART_LINECTRL_BAUD_DIVINT_SHIFT	16
#घोषणा AUART_LINECTRL_BAUD_DIVINT_MASK		0xffff0000
#घोषणा AUART_LINECTRL_BAUD_DIVINT(v)		(((v) & 0xffff) << 16)
#घोषणा AUART_LINECTRL_BAUD_DIVFRAC_SHIFT	8
#घोषणा AUART_LINECTRL_BAUD_DIVFRAC_MASK	0x00003f00
#घोषणा AUART_LINECTRL_BAUD_DIVFRAC(v)		(((v) & 0x3f) << 8)
#घोषणा AUART_LINECTRL_SPS			(1 << 7)
#घोषणा AUART_LINECTRL_WLEN_MASK		0x00000060
#घोषणा AUART_LINECTRL_WLEN(v)			(((v) & 0x3) << 5)
#घोषणा AUART_LINECTRL_FEN			(1 << 4)
#घोषणा AUART_LINECTRL_STP2			(1 << 3)
#घोषणा AUART_LINECTRL_EPS			(1 << 2)
#घोषणा AUART_LINECTRL_PEN			(1 << 1)
#घोषणा AUART_LINECTRL_BRK			(1 << 0)

#घोषणा AUART_INTR_RTIEN			(1 << 22)
#घोषणा AUART_INTR_TXIEN			(1 << 21)
#घोषणा AUART_INTR_RXIEN			(1 << 20)
#घोषणा AUART_INTR_CTSMIEN			(1 << 17)
#घोषणा AUART_INTR_RTIS				(1 << 6)
#घोषणा AUART_INTR_TXIS				(1 << 5)
#घोषणा AUART_INTR_RXIS				(1 << 4)
#घोषणा AUART_INTR_CTSMIS			(1 << 1)

#घोषणा AUART_STAT_BUSY				(1 << 29)
#घोषणा AUART_STAT_CTS				(1 << 28)
#घोषणा AUART_STAT_TXFE				(1 << 27)
#घोषणा AUART_STAT_TXFF				(1 << 25)
#घोषणा AUART_STAT_RXFE				(1 << 24)
#घोषणा AUART_STAT_OERR				(1 << 19)
#घोषणा AUART_STAT_BERR				(1 << 18)
#घोषणा AUART_STAT_PERR				(1 << 17)
#घोषणा AUART_STAT_FERR				(1 << 16)
#घोषणा AUART_STAT_RXCOUNT_MASK			0xffff

/*
 * Start of Alphascale यंत्र9260 defines
 * This list contains only dअगरferences of existing bits
 * between imx2x and यंत्र9260
 */
#घोषणा ASM9260_HW_CTRL0			0x0000
/*
 * RW. Tell the UART to execute the RX DMA Command. The
 * UART will clear this bit at the end of receive execution.
 */
#घोषणा ASM9260_BM_CTRL0_RXDMA_RUN		BIT(28)
/* RW. 0 use FIFO क्रम status रेजिस्टर; 1 use DMA */
#घोषणा ASM9260_BM_CTRL0_RXTO_SOURCE_STATUS	BIT(25)
/*
 * RW. RX TIMEOUT Enable. Valid क्रम FIFO and DMA.
 * Warning: If this bit is set to 0, the RX समयout will not affect receive DMA
 * operation. If this bit is set to 1, a receive समयout will cause the receive
 * DMA logic to terminate by filling the reमुख्यing DMA bytes with garbage data.
 */
#घोषणा ASM9260_BM_CTRL0_RXTO_ENABLE		BIT(24)
/*
 * RW. Receive Timeout Counter Value: number of 8-bit-समय to रुको beक्रमe
 * निश्चितing समयout on the RX input. If the RXFIFO is not empty and the RX
 * input is idle, then the watchकरोg counter will decrement each bit-समय. Note
 * 7-bit-समय is added to the programmed value, so a value of zero will set
 * the counter to 7-bit-समय, a value of 0x1 gives 15-bit-समय and so on. Also
 * note that the counter is reloaded at the end of each frame, so अगर the frame
 * is 10 bits दीर्घ and the समयout counter value is zero, then समयout will
 * occur (when FIFO is not empty) even अगर the RX input is not idle. The शेष
 * value is 0x3 (31 bit-समय).
 */
#घोषणा ASM9260_BM_CTRL0_RXTO_MASK		(0xff << 16)
/* TIMEOUT = (100*7+1)*(1/BAUD) */
#घोषणा ASM9260_BM_CTRL0_DEFAULT_RXTIMEOUT	(20 << 16)

/* TX ctrl रेजिस्टर */
#घोषणा ASM9260_HW_CTRL1			0x0010
/*
 * RW. Tell the UART to execute the TX DMA Command. The
 * UART will clear this bit at the end of transmit execution.
 */
#घोषणा ASM9260_BM_CTRL1_TXDMA_RUN		BIT(28)

#घोषणा ASM9260_HW_CTRL2			0x0020
/*
 * RW. Receive Interrupt FIFO Level Select.
 * The trigger poपूर्णांकs क्रम the receive पूर्णांकerrupt are as follows:
 * ONE_EIGHTHS = 0x0 Trigger on FIFO full to at least 2 of 16 entries.
 * ONE_QUARTER = 0x1 Trigger on FIFO full to at least 4 of 16 entries.
 * ONE_HALF = 0x2 Trigger on FIFO full to at least 8 of 16 entries.
 * THREE_QUARTERS = 0x3 Trigger on FIFO full to at least 12 of 16 entries.
 * SEVEN_EIGHTHS = 0x4 Trigger on FIFO full to at least 14 of 16 entries.
 */
#घोषणा ASM9260_BM_CTRL2_RXIFLSEL		(7 << 20)
#घोषणा ASM9260_BM_CTRL2_DEFAULT_RXIFLSEL	(3 << 20)
/* RW. Same as RXIFLSEL */
#घोषणा ASM9260_BM_CTRL2_TXIFLSEL		(7 << 16)
#घोषणा ASM9260_BM_CTRL2_DEFAULT_TXIFLSEL	(2 << 16)
/* RW. Set DTR. When this bit is 1, the output is 0. */
#घोषणा ASM9260_BM_CTRL2_DTR			BIT(10)
/* RW. Loop Back Enable */
#घोषणा ASM9260_BM_CTRL2_LBE			BIT(7)
#घोषणा ASM9260_BM_CTRL2_PORT_ENABLE		BIT(0)

#घोषणा ASM9260_HW_LINECTRL			0x0030
/*
 * RW. Stick Parity Select. When bits 1, 2, and 7 of this रेजिस्टर are set, the
 * parity bit is transmitted and checked as a 0. When bits 1 and 7 are set,
 * and bit 2 is 0, the parity bit is transmitted and checked as a 1. When this
 * bit is cleared stick parity is disabled.
 */
#घोषणा ASM9260_BM_LCTRL_SPS			BIT(7)
/* RW. Word length */
#घोषणा ASM9260_BM_LCTRL_WLEN			(3 << 5)
#घोषणा ASM9260_BM_LCTRL_CHRL_5			(0 << 5)
#घोषणा ASM9260_BM_LCTRL_CHRL_6			(1 << 5)
#घोषणा ASM9260_BM_LCTRL_CHRL_7			(2 << 5)
#घोषणा ASM9260_BM_LCTRL_CHRL_8			(3 << 5)

/*
 * Interrupt रेजिस्टर.
 * contains the पूर्णांकerrupt enables and the पूर्णांकerrupt status bits
 */
#घोषणा ASM9260_HW_INTR				0x0040
/* Tx FIFO EMPTY Raw Interrupt enable */
#घोषणा ASM9260_BM_INTR_TFEIEN			BIT(27)
/* Overrun Error Interrupt Enable. */
#घोषणा ASM9260_BM_INTR_OEIEN			BIT(26)
/* Break Error Interrupt Enable. */
#घोषणा ASM9260_BM_INTR_BEIEN			BIT(25)
/* Parity Error Interrupt Enable. */
#घोषणा ASM9260_BM_INTR_PEIEN			BIT(24)
/* Framing Error Interrupt Enable. */
#घोषणा ASM9260_BM_INTR_FEIEN			BIT(23)

/* nUARTDSR Modem Interrupt Enable. */
#घोषणा ASM9260_BM_INTR_DSRMIEN			BIT(19)
/* nUARTDCD Modem Interrupt Enable. */
#घोषणा ASM9260_BM_INTR_DCDMIEN			BIT(18)
/* nUARTRI Modem Interrupt Enable. */
#घोषणा ASM9260_BM_INTR_RIMIEN			BIT(16)
/* Auto-Boud Timeout */
#घोषणा ASM9260_BM_INTR_ABTO			BIT(13)
#घोषणा ASM9260_BM_INTR_ABEO			BIT(12)
/* Tx FIFO EMPTY Raw Interrupt state */
#घोषणा ASM9260_BM_INTR_TFEIS			BIT(11)
/* Overrun Error */
#घोषणा ASM9260_BM_INTR_OEIS			BIT(10)
/* Break Error */
#घोषणा ASM9260_BM_INTR_BEIS			BIT(9)
/* Parity Error */
#घोषणा ASM9260_BM_INTR_PEIS			BIT(8)
/* Framing Error */
#घोषणा ASM9260_BM_INTR_FEIS			BIT(7)
#घोषणा ASM9260_BM_INTR_DSRMIS			BIT(3)
#घोषणा ASM9260_BM_INTR_DCDMIS			BIT(2)
#घोषणा ASM9260_BM_INTR_RIMIS			BIT(0)

/*
 * RW. In DMA mode, up to 4 Received/Transmit अक्षरacters can be accessed at a
 * समय. In PIO mode, only one अक्षरacter can be accessed at a समय. The status
 * रेजिस्टर contains the receive data flags and valid bits.
 */
#घोषणा ASM9260_HW_DATA				0x0050

#घोषणा ASM9260_HW_STAT				0x0060
/* RO. If 1, UARTAPP is present in this product. */
#घोषणा ASM9260_BM_STAT_PRESENT			BIT(31)
/* RO. If 1, HISPEED is present in this product. */
#घोषणा ASM9260_BM_STAT_HISPEED			BIT(30)
/* RO. Receive FIFO Full. */
#घोषणा ASM9260_BM_STAT_RXFULL			BIT(26)

/* RO. The UART Debug Register contains the state of the DMA संकेतs. */
#घोषणा ASM9260_HW_DEBUG			0x0070
/* DMA Command Run Status */
#घोषणा ASM9260_BM_DEBUG_TXDMARUN		BIT(5)
#घोषणा ASM9260_BM_DEBUG_RXDMARUN		BIT(4)
/* DMA Command End Status */
#घोषणा ASM9260_BM_DEBUG_TXCMDEND		BIT(3)
#घोषणा ASM9260_BM_DEBUG_RXCMDEND		BIT(2)
/* DMA Request Status */
#घोषणा ASM9260_BM_DEBUG_TXDMARQ		BIT(1)
#घोषणा ASM9260_BM_DEBUG_RXDMARQ		BIT(0)

#घोषणा ASM9260_HW_ILPR				0x0080

#घोषणा ASM9260_HW_RS485CTRL			0x0090
/*
 * RW. This bit reverses the polarity of the direction control संकेत on the RTS
 * (or DTR) pin.
 * If 0, The direction control pin will be driven to logic ै 0ै  when the
 * transmitter has data to be sent. It will be driven to logic ै 1ै  after the
 * last bit of data has been transmitted.
 */
#घोषणा ASM9260_BM_RS485CTRL_ONIV		BIT(5)
/* RW. Enable Auto Direction Control. */
#घोषणा ASM9260_BM_RS485CTRL_सूची_CTRL		BIT(4)
/*
 * RW. If 0 and सूची_CTRL = 1, pin RTS is used क्रम direction control.
 * If 1 and सूची_CTRL = 1, pin DTR is used क्रम direction control.
 */
#घोषणा ASM9260_BM_RS485CTRL_PINSEL		BIT(3)
/* RW. Enable Auto Address Detect (AAD). */
#घोषणा ASM9260_BM_RS485CTRL_AADEN		BIT(2)
/* RW. Disable receiver. */
#घोषणा ASM9260_BM_RS485CTRL_RXDIS		BIT(1)
/* RW. Enable RS-485/EIA-485 Normal Multidrop Mode (NMM) */
#घोषणा ASM9260_BM_RS485CTRL_RS485EN		BIT(0)

#घोषणा ASM9260_HW_RS485ADRMATCH		0x00a0
/* Contains the address match value. */
#घोषणा ASM9260_BM_RS485ADRMATCH_MASK		(0xff << 0)

#घोषणा ASM9260_HW_RS485DLY			0x00b0
/*
 * RW. Contains the direction control (RTS or DTR) delay value. This delay समय
 * is in periods of the baud घड़ी.
 */
#घोषणा ASM9260_BM_RS485DLY_MASK		(0xff << 0)

#घोषणा ASM9260_HW_AUTOBAUD			0x00c0
/* WO. Auto-baud समय-out पूर्णांकerrupt clear bit. */
#घोषणा ASM9260_BM_AUTOBAUD_TO_INT_CLR		BIT(9)
/* WO. End of स्वतः-baud पूर्णांकerrupt clear bit. */
#घोषणा ASM9260_BM_AUTOBAUD_EO_INT_CLR		BIT(8)
/* Restart in हाल of समयout (counter restarts at next UART Rx falling edge) */
#घोषणा ASM9260_BM_AUTOBAUD_AUTORESTART		BIT(2)
/* Auto-baud mode select bit. 0 - Mode 0, 1 - Mode 1. */
#घोषणा ASM9260_BM_AUTOBAUD_MODE		BIT(1)
/*
 * Auto-baud start (स्वतः-baud is running). Auto-baud run bit. This bit is
 * स्वतःmatically cleared after स्वतः-baud completion.
 */
#घोषणा ASM9260_BM_AUTOBAUD_START		BIT(0)

#घोषणा ASM9260_HW_CTRL3			0x00d0
#घोषणा ASM9260_BM_CTRL3_OUTCLK_DIV_MASK	(0xffff << 16)
/*
 * RW. Provide clk over OUTCLK pin. In हाल of यंत्र9260 it can be configured on
 * pins 137 and 144.
 */
#घोषणा ASM9260_BM_CTRL3_MASTERMODE		BIT(6)
/* RW. Baud Rate Mode: 1 - Enable sync mode. 0 - async mode. */
#घोषणा ASM9260_BM_CTRL3_SYNCMODE		BIT(4)
/* RW. 1 - MSB bit send frist; 0 - LSB bit frist. */
#घोषणा ASM9260_BM_CTRL3_MSBF			BIT(2)
/* RW. 1 - sample rate = 8 x Baudrate; 0 - sample rate = 16 x Baudrate. */
#घोषणा ASM9260_BM_CTRL3_BAUD8			BIT(1)
/* RW. 1 - Set word length to 9bit. 0 - use ASM9260_BM_LCTRL_WLEN */
#घोषणा ASM9260_BM_CTRL3_9BIT			BIT(0)

#घोषणा ASM9260_HW_ISO7816_CTRL			0x00e0
/* RW. Enable High Speed mode. */
#घोषणा ASM9260_BM_ISO7816CTRL_HS		BIT(12)
/* Disable Successive Receive NACK */
#घोषणा ASM9260_BM_ISO7816CTRL_DS_NACK		BIT(8)
#घोषणा ASM9260_BM_ISO7816CTRL_MAX_ITER_MASK	(0xff << 4)
/* Receive NACK Inhibit */
#घोषणा ASM9260_BM_ISO7816CTRL_INACK		BIT(3)
#घोषणा ASM9260_BM_ISO7816CTRL_NEG_DATA		BIT(2)
/* RW. 1 - ISO7816 mode; 0 - USART mode */
#घोषणा ASM9260_BM_ISO7816CTRL_ENABLE		BIT(0)

#घोषणा ASM9260_HW_ISO7816_ERRCNT		0x00f0
/* Parity error counter. Will be cleared after पढ़ोing */
#घोषणा ASM9260_BM_ISO7816_NB_ERRORS_MASK	(0xff << 0)

#घोषणा ASM9260_HW_ISO7816_STATUS		0x0100
/* Max number of Repetitions Reached */
#घोषणा ASM9260_BM_ISO7816_STAT_ITERATION	BIT(0)

/* End of Alphascale यंत्र9260 defines */

अटल काष्ठा uart_driver auart_driver;

क्रमागत mxs_auart_type अणु
	IMX23_AUART,
	IMX28_AUART,
	ASM9260_AUART,
पूर्ण;

काष्ठा venकरोr_data अणु
	स्थिर u16	*reg_offset;
पूर्ण;

क्रमागत अणु
	REG_CTRL0,
	REG_CTRL1,
	REG_CTRL2,
	REG_LINECTRL,
	REG_LINECTRL2,
	REG_INTR,
	REG_DATA,
	REG_STAT,
	REG_DEBUG,
	REG_VERSION,
	REG_AUTOBAUD,

	/* The size of the array - must be last */
	REG_ARRAY_SIZE,
पूर्ण;

अटल स्थिर u16 mxs_यंत्र9260_offsets[REG_ARRAY_SIZE] = अणु
	[REG_CTRL0] = ASM9260_HW_CTRL0,
	[REG_CTRL1] = ASM9260_HW_CTRL1,
	[REG_CTRL2] = ASM9260_HW_CTRL2,
	[REG_LINECTRL] = ASM9260_HW_LINECTRL,
	[REG_INTR] = ASM9260_HW_INTR,
	[REG_DATA] = ASM9260_HW_DATA,
	[REG_STAT] = ASM9260_HW_STAT,
	[REG_DEBUG] = ASM9260_HW_DEBUG,
	[REG_AUTOBAUD] = ASM9260_HW_AUTOBAUD,
पूर्ण;

अटल स्थिर u16 mxs_sपंचांगp37xx_offsets[REG_ARRAY_SIZE] = अणु
	[REG_CTRL0] = AUART_CTRL0,
	[REG_CTRL1] = AUART_CTRL1,
	[REG_CTRL2] = AUART_CTRL2,
	[REG_LINECTRL] = AUART_LINECTRL,
	[REG_LINECTRL2] = AUART_LINECTRL2,
	[REG_INTR] = AUART_INTR,
	[REG_DATA] = AUART_DATA,
	[REG_STAT] = AUART_STAT,
	[REG_DEBUG] = AUART_DEBUG,
	[REG_VERSION] = AUART_VERSION,
	[REG_AUTOBAUD] = AUART_AUTOBAUD,
पूर्ण;

अटल स्थिर काष्ठा venकरोr_data venकरोr_alphascale_यंत्र9260 = अणु
	.reg_offset = mxs_यंत्र9260_offsets,
पूर्ण;

अटल स्थिर काष्ठा venकरोr_data venकरोr_मुक्तscale_sपंचांगp37xx = अणु
	.reg_offset = mxs_sपंचांगp37xx_offsets,
पूर्ण;

काष्ठा mxs_auart_port अणु
	काष्ठा uart_port port;

#घोषणा MXS_AUART_DMA_ENABLED	0x2
#घोषणा MXS_AUART_DMA_TX_SYNC	2  /* bit 2 */
#घोषणा MXS_AUART_DMA_RX_READY	3  /* bit 3 */
#घोषणा MXS_AUART_RTSCTS	4  /* bit 4 */
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक mctrl_prev;
	क्रमागत mxs_auart_type devtype;
	स्थिर काष्ठा venकरोr_data *venकरोr;

	काष्ठा clk *clk;
	काष्ठा clk *clk_ahb;
	काष्ठा device *dev;

	/* क्रम DMA */
	काष्ठा scatterlist tx_sgl;
	काष्ठा dma_chan	*tx_dma_chan;
	व्योम *tx_dma_buf;

	काष्ठा scatterlist rx_sgl;
	काष्ठा dma_chan	*rx_dma_chan;
	व्योम *rx_dma_buf;

	काष्ठा mctrl_gpios	*gpios;
	पूर्णांक			gpio_irq[UART_GPIO_MAX];
	bool			ms_irq_enabled;
पूर्ण;

अटल स्थिर काष्ठा of_device_id mxs_auart_dt_ids[] = अणु
	अणु
		.compatible = "fsl,imx28-auart",
		.data = (स्थिर व्योम *)IMX28_AUART
	पूर्ण, अणु
		.compatible = "fsl,imx23-auart",
		.data = (स्थिर व्योम *)IMX23_AUART
	पूर्ण, अणु
		.compatible = "alphascale,asm9260-auart",
		.data = (स्थिर व्योम *)ASM9260_AUART
	पूर्ण, अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mxs_auart_dt_ids);

अटल अंतरभूत पूर्णांक is_imx28_auart(काष्ठा mxs_auart_port *s)
अणु
	वापस s->devtype == IMX28_AUART;
पूर्ण

अटल अंतरभूत पूर्णांक is_यंत्र9260_auart(काष्ठा mxs_auart_port *s)
अणु
	वापस s->devtype == ASM9260_AUART;
पूर्ण

अटल अंतरभूत bool auart_dma_enabled(काष्ठा mxs_auart_port *s)
अणु
	वापस s->flags & MXS_AUART_DMA_ENABLED;
पूर्ण

अटल अचिन्हित पूर्णांक mxs_reg_to_offset(स्थिर काष्ठा mxs_auart_port *uap,
				      अचिन्हित पूर्णांक reg)
अणु
	वापस uap->venकरोr->reg_offset[reg];
पूर्ण

अटल अचिन्हित पूर्णांक mxs_पढ़ो(स्थिर काष्ठा mxs_auart_port *uap,
			     अचिन्हित पूर्णांक reg)
अणु
	व्योम __iomem *addr = uap->port.membase + mxs_reg_to_offset(uap, reg);

	वापस पढ़ोl_relaxed(addr);
पूर्ण

अटल व्योम mxs_ग_लिखो(अचिन्हित पूर्णांक val, काष्ठा mxs_auart_port *uap,
		      अचिन्हित पूर्णांक reg)
अणु
	व्योम __iomem *addr = uap->port.membase + mxs_reg_to_offset(uap, reg);

	ग_लिखोl_relaxed(val, addr);
पूर्ण

अटल व्योम mxs_set(अचिन्हित पूर्णांक val, काष्ठा mxs_auart_port *uap,
		    अचिन्हित पूर्णांक reg)
अणु
	व्योम __iomem *addr = uap->port.membase + mxs_reg_to_offset(uap, reg);

	ग_लिखोl_relaxed(val, addr + SET_REG);
पूर्ण

अटल व्योम mxs_clr(अचिन्हित पूर्णांक val, काष्ठा mxs_auart_port *uap,
		    अचिन्हित पूर्णांक reg)
अणु
	व्योम __iomem *addr = uap->port.membase + mxs_reg_to_offset(uap, reg);

	ग_लिखोl_relaxed(val, addr + CLR_REG);
पूर्ण

अटल व्योम mxs_auart_stop_tx(काष्ठा uart_port *u);

#घोषणा to_auart_port(u) container_of(u, काष्ठा mxs_auart_port, port)

अटल व्योम mxs_auart_tx_अक्षरs(काष्ठा mxs_auart_port *s);

अटल व्योम dma_tx_callback(व्योम *param)
अणु
	काष्ठा mxs_auart_port *s = param;
	काष्ठा circ_buf *xmit = &s->port.state->xmit;

	dma_unmap_sg(s->dev, &s->tx_sgl, 1, DMA_TO_DEVICE);

	/* clear the bit used to serialize the DMA tx. */
	clear_bit(MXS_AUART_DMA_TX_SYNC, &s->flags);
	smp_mb__after_atomic();

	/* wake up the possible processes. */
	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&s->port);

	mxs_auart_tx_अक्षरs(s);
पूर्ण

अटल पूर्णांक mxs_auart_dma_tx(काष्ठा mxs_auart_port *s, पूर्णांक size)
अणु
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा scatterlist *sgl = &s->tx_sgl;
	काष्ठा dma_chan *channel = s->tx_dma_chan;
	u32 pio;

	/* [1] : send PIO. Note, the first pio word is CTRL1. */
	pio = AUART_CTRL1_XFER_COUNT(size);
	desc = dmaengine_prep_slave_sg(channel, (काष्ठा scatterlist *)&pio,
					1, DMA_TRANS_NONE, 0);
	अगर (!desc) अणु
		dev_err(s->dev, "step 1 error\n");
		वापस -EINVAL;
	पूर्ण

	/* [2] : set DMA buffer. */
	sg_init_one(sgl, s->tx_dma_buf, size);
	dma_map_sg(s->dev, sgl, 1, DMA_TO_DEVICE);
	desc = dmaengine_prep_slave_sg(channel, sgl,
			1, DMA_MEM_TO_DEV, DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc) अणु
		dev_err(s->dev, "step 2 error\n");
		वापस -EINVAL;
	पूर्ण

	/* [3] : submit the DMA */
	desc->callback = dma_tx_callback;
	desc->callback_param = s;
	dmaengine_submit(desc);
	dma_async_issue_pending(channel);
	वापस 0;
पूर्ण

अटल व्योम mxs_auart_tx_अक्षरs(काष्ठा mxs_auart_port *s)
अणु
	काष्ठा circ_buf *xmit = &s->port.state->xmit;

	अगर (auart_dma_enabled(s)) अणु
		u32 i = 0;
		पूर्णांक size;
		व्योम *buffer = s->tx_dma_buf;

		अगर (test_and_set_bit(MXS_AUART_DMA_TX_SYNC, &s->flags))
			वापस;

		जबतक (!uart_circ_empty(xmit) && !uart_tx_stopped(&s->port)) अणु
			size = min_t(u32, UART_XMIT_SIZE - i,
				     CIRC_CNT_TO_END(xmit->head,
						     xmit->tail,
						     UART_XMIT_SIZE));
			स_नकल(buffer + i, xmit->buf + xmit->tail, size);
			xmit->tail = (xmit->tail + size) & (UART_XMIT_SIZE - 1);

			i += size;
			अगर (i >= UART_XMIT_SIZE)
				अवरोध;
		पूर्ण

		अगर (uart_tx_stopped(&s->port))
			mxs_auart_stop_tx(&s->port);

		अगर (i) अणु
			mxs_auart_dma_tx(s, i);
		पूर्ण अन्यथा अणु
			clear_bit(MXS_AUART_DMA_TX_SYNC, &s->flags);
			smp_mb__after_atomic();
		पूर्ण
		वापस;
	पूर्ण


	जबतक (!(mxs_पढ़ो(s, REG_STAT) & AUART_STAT_TXFF)) अणु
		अगर (s->port.x_अक्षर) अणु
			s->port.icount.tx++;
			mxs_ग_लिखो(s->port.x_अक्षर, s, REG_DATA);
			s->port.x_अक्षर = 0;
			जारी;
		पूर्ण
		अगर (!uart_circ_empty(xmit) && !uart_tx_stopped(&s->port)) अणु
			s->port.icount.tx++;
			mxs_ग_लिखो(xmit->buf[xmit->tail], s, REG_DATA);
			xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण
	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&s->port);

	अगर (uart_circ_empty(&(s->port.state->xmit)))
		mxs_clr(AUART_INTR_TXIEN, s, REG_INTR);
	अन्यथा
		mxs_set(AUART_INTR_TXIEN, s, REG_INTR);

	अगर (uart_tx_stopped(&s->port))
		mxs_auart_stop_tx(&s->port);
पूर्ण

अटल व्योम mxs_auart_rx_अक्षर(काष्ठा mxs_auart_port *s)
अणु
	पूर्णांक flag;
	u32 stat;
	u8 c;

	c = mxs_पढ़ो(s, REG_DATA);
	stat = mxs_पढ़ो(s, REG_STAT);

	flag = TTY_NORMAL;
	s->port.icount.rx++;

	अगर (stat & AUART_STAT_BERR) अणु
		s->port.icount.brk++;
		अगर (uart_handle_अवरोध(&s->port))
			जाओ out;
	पूर्ण अन्यथा अगर (stat & AUART_STAT_PERR) अणु
		s->port.icount.parity++;
	पूर्ण अन्यथा अगर (stat & AUART_STAT_FERR) अणु
		s->port.icount.frame++;
	पूर्ण

	/*
	 * Mask off conditions which should be ingored.
	 */
	stat &= s->port.पढ़ो_status_mask;

	अगर (stat & AUART_STAT_BERR) अणु
		flag = TTY_BREAK;
	पूर्ण अन्यथा अगर (stat & AUART_STAT_PERR)
		flag = TTY_PARITY;
	अन्यथा अगर (stat & AUART_STAT_FERR)
		flag = TTY_FRAME;

	अगर (stat & AUART_STAT_OERR)
		s->port.icount.overrun++;

	अगर (uart_handle_sysrq_अक्षर(&s->port, c))
		जाओ out;

	uart_insert_अक्षर(&s->port, stat, AUART_STAT_OERR, c, flag);
out:
	mxs_ग_लिखो(stat, s, REG_STAT);
पूर्ण

अटल व्योम mxs_auart_rx_अक्षरs(काष्ठा mxs_auart_port *s)
अणु
	u32 stat = 0;

	क्रम (;;) अणु
		stat = mxs_पढ़ो(s, REG_STAT);
		अगर (stat & AUART_STAT_RXFE)
			अवरोध;
		mxs_auart_rx_अक्षर(s);
	पूर्ण

	mxs_ग_लिखो(stat, s, REG_STAT);
	tty_flip_buffer_push(&s->port.state->port);
पूर्ण

अटल पूर्णांक mxs_auart_request_port(काष्ठा uart_port *u)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mxs_auart_verअगरy_port(काष्ठा uart_port *u,
				    काष्ठा serial_काष्ठा *ser)
अणु
	अगर (u->type != PORT_UNKNOWN && u->type != PORT_IMX)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम mxs_auart_config_port(काष्ठा uart_port *u, पूर्णांक flags)
अणु
पूर्ण

अटल स्थिर अक्षर *mxs_auart_type(काष्ठा uart_port *u)
अणु
	काष्ठा mxs_auart_port *s = to_auart_port(u);

	वापस dev_name(s->dev);
पूर्ण

अटल व्योम mxs_auart_release_port(काष्ठा uart_port *u)
अणु
पूर्ण

अटल व्योम mxs_auart_set_mctrl(काष्ठा uart_port *u, अचिन्हित mctrl)
अणु
	काष्ठा mxs_auart_port *s = to_auart_port(u);

	u32 ctrl = mxs_पढ़ो(s, REG_CTRL2);

	ctrl &= ~(AUART_CTRL2_RTSEN | AUART_CTRL2_RTS);
	अगर (mctrl & TIOCM_RTS) अणु
		अगर (uart_cts_enabled(u))
			ctrl |= AUART_CTRL2_RTSEN;
		अन्यथा
			ctrl |= AUART_CTRL2_RTS;
	पूर्ण

	mxs_ग_लिखो(ctrl, s, REG_CTRL2);

	mctrl_gpio_set(s->gpios, mctrl);
पूर्ण

#घोषणा MCTRL_ANY_DELTA        (TIOCM_RI | TIOCM_DSR | TIOCM_CD | TIOCM_CTS)
अटल u32 mxs_auart_modem_status(काष्ठा mxs_auart_port *s, u32 mctrl)
अणु
	u32 mctrl_dअगरf;

	mctrl_dअगरf = mctrl ^ s->mctrl_prev;
	s->mctrl_prev = mctrl;
	अगर (mctrl_dअगरf & MCTRL_ANY_DELTA && s->ms_irq_enabled &&
						s->port.state != शून्य) अणु
		अगर (mctrl_dअगरf & TIOCM_RI)
			s->port.icount.rng++;
		अगर (mctrl_dअगरf & TIOCM_DSR)
			s->port.icount.dsr++;
		अगर (mctrl_dअगरf & TIOCM_CD)
			uart_handle_dcd_change(&s->port, mctrl & TIOCM_CD);
		अगर (mctrl_dअगरf & TIOCM_CTS)
			uart_handle_cts_change(&s->port, mctrl & TIOCM_CTS);

		wake_up_पूर्णांकerruptible(&s->port.state->port.delta_msr_रुको);
	पूर्ण
	वापस mctrl;
पूर्ण

अटल u32 mxs_auart_get_mctrl(काष्ठा uart_port *u)
अणु
	काष्ठा mxs_auart_port *s = to_auart_port(u);
	u32 stat = mxs_पढ़ो(s, REG_STAT);
	u32 mctrl = 0;

	अगर (stat & AUART_STAT_CTS)
		mctrl |= TIOCM_CTS;

	वापस mctrl_gpio_get(s->gpios, &mctrl);
पूर्ण

/*
 * Enable modem status पूर्णांकerrupts
 */
अटल व्योम mxs_auart_enable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा mxs_auart_port *s = to_auart_port(port);

	/*
	 * Interrupt should not be enabled twice
	 */
	अगर (s->ms_irq_enabled)
		वापस;

	s->ms_irq_enabled = true;

	अगर (s->gpio_irq[UART_GPIO_CTS] >= 0)
		enable_irq(s->gpio_irq[UART_GPIO_CTS]);
	/* TODO: enable AUART_INTR_CTSMIEN otherwise */

	अगर (s->gpio_irq[UART_GPIO_DSR] >= 0)
		enable_irq(s->gpio_irq[UART_GPIO_DSR]);

	अगर (s->gpio_irq[UART_GPIO_RI] >= 0)
		enable_irq(s->gpio_irq[UART_GPIO_RI]);

	अगर (s->gpio_irq[UART_GPIO_DCD] >= 0)
		enable_irq(s->gpio_irq[UART_GPIO_DCD]);
पूर्ण

/*
 * Disable modem status पूर्णांकerrupts
 */
अटल व्योम mxs_auart_disable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा mxs_auart_port *s = to_auart_port(port);

	/*
	 * Interrupt should not be disabled twice
	 */
	अगर (!s->ms_irq_enabled)
		वापस;

	s->ms_irq_enabled = false;

	अगर (s->gpio_irq[UART_GPIO_CTS] >= 0)
		disable_irq(s->gpio_irq[UART_GPIO_CTS]);
	/* TODO: disable AUART_INTR_CTSMIEN otherwise */

	अगर (s->gpio_irq[UART_GPIO_DSR] >= 0)
		disable_irq(s->gpio_irq[UART_GPIO_DSR]);

	अगर (s->gpio_irq[UART_GPIO_RI] >= 0)
		disable_irq(s->gpio_irq[UART_GPIO_RI]);

	अगर (s->gpio_irq[UART_GPIO_DCD] >= 0)
		disable_irq(s->gpio_irq[UART_GPIO_DCD]);
पूर्ण

अटल पूर्णांक mxs_auart_dma_prep_rx(काष्ठा mxs_auart_port *s);
अटल व्योम dma_rx_callback(व्योम *arg)
अणु
	काष्ठा mxs_auart_port *s = (काष्ठा mxs_auart_port *) arg;
	काष्ठा tty_port *port = &s->port.state->port;
	पूर्णांक count;
	u32 stat;

	dma_unmap_sg(s->dev, &s->rx_sgl, 1, DMA_FROM_DEVICE);

	stat = mxs_पढ़ो(s, REG_STAT);
	stat &= ~(AUART_STAT_OERR | AUART_STAT_BERR |
			AUART_STAT_PERR | AUART_STAT_FERR);

	count = stat & AUART_STAT_RXCOUNT_MASK;
	tty_insert_flip_string(port, s->rx_dma_buf, count);

	mxs_ग_लिखो(stat, s, REG_STAT);
	tty_flip_buffer_push(port);

	/* start the next DMA क्रम RX. */
	mxs_auart_dma_prep_rx(s);
पूर्ण

अटल पूर्णांक mxs_auart_dma_prep_rx(काष्ठा mxs_auart_port *s)
अणु
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा scatterlist *sgl = &s->rx_sgl;
	काष्ठा dma_chan *channel = s->rx_dma_chan;
	u32 pio[1];

	/* [1] : send PIO */
	pio[0] = AUART_CTRL0_RXTO_ENABLE
		| AUART_CTRL0_RXTIMEOUT(0x80)
		| AUART_CTRL0_XFER_COUNT(UART_XMIT_SIZE);
	desc = dmaengine_prep_slave_sg(channel, (काष्ठा scatterlist *)pio,
					1, DMA_TRANS_NONE, 0);
	अगर (!desc) अणु
		dev_err(s->dev, "step 1 error\n");
		वापस -EINVAL;
	पूर्ण

	/* [2] : send DMA request */
	sg_init_one(sgl, s->rx_dma_buf, UART_XMIT_SIZE);
	dma_map_sg(s->dev, sgl, 1, DMA_FROM_DEVICE);
	desc = dmaengine_prep_slave_sg(channel, sgl, 1, DMA_DEV_TO_MEM,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc) अणु
		dev_err(s->dev, "step 2 error\n");
		वापस -1;
	पूर्ण

	/* [3] : submit the DMA, but करो not issue it. */
	desc->callback = dma_rx_callback;
	desc->callback_param = s;
	dmaengine_submit(desc);
	dma_async_issue_pending(channel);
	वापस 0;
पूर्ण

अटल व्योम mxs_auart_dma_निकास_channel(काष्ठा mxs_auart_port *s)
अणु
	अगर (s->tx_dma_chan) अणु
		dma_release_channel(s->tx_dma_chan);
		s->tx_dma_chan = शून्य;
	पूर्ण
	अगर (s->rx_dma_chan) अणु
		dma_release_channel(s->rx_dma_chan);
		s->rx_dma_chan = शून्य;
	पूर्ण

	kमुक्त(s->tx_dma_buf);
	kमुक्त(s->rx_dma_buf);
	s->tx_dma_buf = शून्य;
	s->rx_dma_buf = शून्य;
पूर्ण

अटल व्योम mxs_auart_dma_निकास(काष्ठा mxs_auart_port *s)
अणु

	mxs_clr(AUART_CTRL2_TXDMAE | AUART_CTRL2_RXDMAE | AUART_CTRL2_DMAONERR,
		s, REG_CTRL2);

	mxs_auart_dma_निकास_channel(s);
	s->flags &= ~MXS_AUART_DMA_ENABLED;
	clear_bit(MXS_AUART_DMA_TX_SYNC, &s->flags);
	clear_bit(MXS_AUART_DMA_RX_READY, &s->flags);
पूर्ण

अटल पूर्णांक mxs_auart_dma_init(काष्ठा mxs_auart_port *s)
अणु
	अगर (auart_dma_enabled(s))
		वापस 0;

	/* init क्रम RX */
	s->rx_dma_chan = dma_request_slave_channel(s->dev, "rx");
	अगर (!s->rx_dma_chan)
		जाओ err_out;
	s->rx_dma_buf = kzalloc(UART_XMIT_SIZE, GFP_KERNEL | GFP_DMA);
	अगर (!s->rx_dma_buf)
		जाओ err_out;

	/* init क्रम TX */
	s->tx_dma_chan = dma_request_slave_channel(s->dev, "tx");
	अगर (!s->tx_dma_chan)
		जाओ err_out;
	s->tx_dma_buf = kzalloc(UART_XMIT_SIZE, GFP_KERNEL | GFP_DMA);
	अगर (!s->tx_dma_buf)
		जाओ err_out;

	/* set the flags */
	s->flags |= MXS_AUART_DMA_ENABLED;
	dev_dbg(s->dev, "enabled the DMA support.");

	/* The DMA buffer is now the FIFO the TTY subप्रणाली can use */
	s->port.fअगरosize = UART_XMIT_SIZE;

	वापस 0;

err_out:
	mxs_auart_dma_निकास_channel(s);
	वापस -EINVAL;

पूर्ण

#घोषणा RTS_AT_AUART()	!mctrl_gpio_to_gpiod(s->gpios, UART_GPIO_RTS)
#घोषणा CTS_AT_AUART()	!mctrl_gpio_to_gpiod(s->gpios, UART_GPIO_CTS)
अटल व्योम mxs_auart_settermios(काष्ठा uart_port *u,
				 काष्ठा ktermios *termios,
				 काष्ठा ktermios *old)
अणु
	काष्ठा mxs_auart_port *s = to_auart_port(u);
	u32 bm, ctrl, ctrl2, भाग;
	अचिन्हित पूर्णांक cflag, baud, baud_min, baud_max;

	cflag = termios->c_cflag;

	ctrl = AUART_LINECTRL_FEN;
	ctrl2 = mxs_पढ़ो(s, REG_CTRL2);

	/* byte size */
	चयन (cflag & CSIZE) अणु
	हाल CS5:
		bm = 0;
		अवरोध;
	हाल CS6:
		bm = 1;
		अवरोध;
	हाल CS7:
		bm = 2;
		अवरोध;
	हाल CS8:
		bm = 3;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	ctrl |= AUART_LINECTRL_WLEN(bm);

	/* parity */
	अगर (cflag & PARENB) अणु
		ctrl |= AUART_LINECTRL_PEN;
		अगर ((cflag & PARODD) == 0)
			ctrl |= AUART_LINECTRL_EPS;
		अगर (cflag & CMSPAR)
			ctrl |= AUART_LINECTRL_SPS;
	पूर्ण

	u->पढ़ो_status_mask = AUART_STAT_OERR;

	अगर (termios->c_अगरlag & INPCK)
		u->पढ़ो_status_mask |= AUART_STAT_PERR;
	अगर (termios->c_अगरlag & (IGNBRK | BRKINT | PARMRK))
		u->पढ़ो_status_mask |= AUART_STAT_BERR;

	/*
	 * Characters to ignore
	 */
	u->ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		u->ignore_status_mask |= AUART_STAT_PERR;
	अगर (termios->c_अगरlag & IGNBRK) अणु
		u->ignore_status_mask |= AUART_STAT_BERR;
		/*
		 * If we're ignoring parity and अवरोध indicators,
		 * ignore overruns too (क्रम real raw support).
		 */
		अगर (termios->c_अगरlag & IGNPAR)
			u->ignore_status_mask |= AUART_STAT_OERR;
	पूर्ण

	/*
	 * ignore all अक्षरacters अगर CREAD is not set
	 */
	अगर (cflag & CREAD)
		ctrl2 |= AUART_CTRL2_RXE;
	अन्यथा
		ctrl2 &= ~AUART_CTRL2_RXE;

	/* figure out the stop bits requested */
	अगर (cflag & CSTOPB)
		ctrl |= AUART_LINECTRL_STP2;

	/* figure out the hardware flow control settings */
	ctrl2 &= ~(AUART_CTRL2_CTSEN | AUART_CTRL2_RTSEN);
	अगर (cflag & CRTSCTS) अणु
		/*
		 * The DMA has a bug(see errata:2836) in mx23.
		 * So we can not implement the DMA क्रम auart in mx23,
		 * we can only implement the DMA support क्रम auart
		 * in mx28.
		 */
		अगर (is_imx28_auart(s)
				&& test_bit(MXS_AUART_RTSCTS, &s->flags)) अणु
			अगर (!mxs_auart_dma_init(s))
				/* enable DMA tranfer */
				ctrl2 |= AUART_CTRL2_TXDMAE | AUART_CTRL2_RXDMAE
				       | AUART_CTRL2_DMAONERR;
		पूर्ण
		/* Even अगर RTS is GPIO line RTSEN can be enabled because
		 * the pinctrl configuration decides about RTS pin function */
		ctrl2 |= AUART_CTRL2_RTSEN;
		अगर (CTS_AT_AUART())
			ctrl2 |= AUART_CTRL2_CTSEN;
	पूर्ण

	/* set baud rate */
	अगर (is_यंत्र9260_auart(s)) अणु
		baud = uart_get_baud_rate(u, termios, old,
					  u->uartclk * 4 / 0x3FFFFF,
					  u->uartclk / 16);
		भाग = u->uartclk * 4 / baud;
	पूर्ण अन्यथा अणु
		baud_min = DIV_ROUND_UP(u->uartclk * 32,
					AUART_LINECTRL_BAUD_DIV_MAX);
		baud_max = u->uartclk * 32 / AUART_LINECTRL_BAUD_DIV_MIN;
		baud = uart_get_baud_rate(u, termios, old, baud_min, baud_max);
		भाग = DIV_ROUND_CLOSEST(u->uartclk * 32, baud);
	पूर्ण

	ctrl |= AUART_LINECTRL_BAUD_DIVFRAC(भाग & 0x3F);
	ctrl |= AUART_LINECTRL_BAUD_DIVINT(भाग >> 6);
	mxs_ग_लिखो(ctrl, s, REG_LINECTRL);

	mxs_ग_लिखो(ctrl2, s, REG_CTRL2);

	uart_update_समयout(u, termios->c_cflag, baud);

	/* prepare क्रम the DMA RX. */
	अगर (auart_dma_enabled(s) &&
		!test_and_set_bit(MXS_AUART_DMA_RX_READY, &s->flags)) अणु
		अगर (!mxs_auart_dma_prep_rx(s)) अणु
			/* Disable the normal RX पूर्णांकerrupt. */
			mxs_clr(AUART_INTR_RXIEN | AUART_INTR_RTIEN,
				s, REG_INTR);
		पूर्ण अन्यथा अणु
			mxs_auart_dma_निकास(s);
			dev_err(s->dev, "We can not start up the DMA.\n");
		पूर्ण
	पूर्ण

	/* CTS flow-control and modem-status पूर्णांकerrupts */
	अगर (UART_ENABLE_MS(u, termios->c_cflag))
		mxs_auart_enable_ms(u);
	अन्यथा
		mxs_auart_disable_ms(u);
पूर्ण

अटल व्योम mxs_auart_set_ldisc(काष्ठा uart_port *port,
				काष्ठा ktermios *termios)
अणु
	अगर (termios->c_line == N_PPS) अणु
		port->flags |= UPF_HARDPPS_CD;
		mxs_auart_enable_ms(port);
	पूर्ण अन्यथा अणु
		port->flags &= ~UPF_HARDPPS_CD;
	पूर्ण
पूर्ण

अटल irqवापस_t mxs_auart_irq_handle(पूर्णांक irq, व्योम *context)
अणु
	u32 istat;
	काष्ठा mxs_auart_port *s = context;
	u32 mctrl_temp = s->mctrl_prev;
	u32 stat = mxs_पढ़ो(s, REG_STAT);

	istat = mxs_पढ़ो(s, REG_INTR);

	/* ack irq */
	mxs_clr(istat & (AUART_INTR_RTIS | AUART_INTR_TXIS | AUART_INTR_RXIS
		| AUART_INTR_CTSMIS), s, REG_INTR);

	/*
	 * Dealing with GPIO पूर्णांकerrupt
	 */
	अगर (irq == s->gpio_irq[UART_GPIO_CTS] ||
	    irq == s->gpio_irq[UART_GPIO_DCD] ||
	    irq == s->gpio_irq[UART_GPIO_DSR] ||
	    irq == s->gpio_irq[UART_GPIO_RI])
		mxs_auart_modem_status(s,
				mctrl_gpio_get(s->gpios, &mctrl_temp));

	अगर (istat & AUART_INTR_CTSMIS) अणु
		अगर (CTS_AT_AUART() && s->ms_irq_enabled)
			uart_handle_cts_change(&s->port,
					stat & AUART_STAT_CTS);
		mxs_clr(AUART_INTR_CTSMIS, s, REG_INTR);
		istat &= ~AUART_INTR_CTSMIS;
	पूर्ण

	अगर (istat & (AUART_INTR_RTIS | AUART_INTR_RXIS)) अणु
		अगर (!auart_dma_enabled(s))
			mxs_auart_rx_अक्षरs(s);
		istat &= ~(AUART_INTR_RTIS | AUART_INTR_RXIS);
	पूर्ण

	अगर (istat & AUART_INTR_TXIS) अणु
		mxs_auart_tx_अक्षरs(s);
		istat &= ~AUART_INTR_TXIS;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mxs_auart_reset_deनिश्चित(काष्ठा mxs_auart_port *s)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक reg;

	mxs_clr(AUART_CTRL0_SFTRST, s, REG_CTRL0);

	क्रम (i = 0; i < 10000; i++) अणु
		reg = mxs_पढ़ो(s, REG_CTRL0);
		अगर (!(reg & AUART_CTRL0_SFTRST))
			अवरोध;
		udelay(3);
	पूर्ण
	mxs_clr(AUART_CTRL0_CLKGATE, s, REG_CTRL0);
पूर्ण

अटल व्योम mxs_auart_reset_निश्चित(काष्ठा mxs_auart_port *s)
अणु
	पूर्णांक i;
	u32 reg;

	reg = mxs_पढ़ो(s, REG_CTRL0);
	/* अगर alपढ़ोy in reset state, keep it untouched */
	अगर (reg & AUART_CTRL0_SFTRST)
		वापस;

	mxs_clr(AUART_CTRL0_CLKGATE, s, REG_CTRL0);
	mxs_set(AUART_CTRL0_SFTRST, s, REG_CTRL0);

	क्रम (i = 0; i < 1000; i++) अणु
		reg = mxs_पढ़ो(s, REG_CTRL0);
		/* reset is finished when the घड़ी is gated */
		अगर (reg & AUART_CTRL0_CLKGATE)
			वापस;
		udelay(10);
	पूर्ण

	dev_err(s->dev, "Failed to reset the unit.");
पूर्ण

अटल पूर्णांक mxs_auart_startup(काष्ठा uart_port *u)
अणु
	पूर्णांक ret;
	काष्ठा mxs_auart_port *s = to_auart_port(u);

	ret = clk_prepare_enable(s->clk);
	अगर (ret)
		वापस ret;

	अगर (uart_console(u)) अणु
		mxs_clr(AUART_CTRL0_CLKGATE, s, REG_CTRL0);
	पूर्ण अन्यथा अणु
		/* reset the unit to a well known state */
		mxs_auart_reset_निश्चित(s);
		mxs_auart_reset_deनिश्चित(s);
	पूर्ण

	mxs_set(AUART_CTRL2_UARTEN, s, REG_CTRL2);

	mxs_ग_लिखो(AUART_INTR_RXIEN | AUART_INTR_RTIEN | AUART_INTR_CTSMIEN,
		  s, REG_INTR);

	/* Reset FIFO size (it could have changed अगर DMA was enabled) */
	u->fअगरosize = MXS_AUART_FIFO_SIZE;

	/*
	 * Enable fअगरo so all four bytes of a DMA word are written to
	 * output (otherwise, only the LSB is written, ie. 1 in 4 bytes)
	 */
	mxs_set(AUART_LINECTRL_FEN, s, REG_LINECTRL);

	/* get initial status of modem lines */
	mctrl_gpio_get(s->gpios, &s->mctrl_prev);

	s->ms_irq_enabled = false;
	वापस 0;
पूर्ण

अटल व्योम mxs_auart_shutकरोwn(काष्ठा uart_port *u)
अणु
	काष्ठा mxs_auart_port *s = to_auart_port(u);

	mxs_auart_disable_ms(u);

	अगर (auart_dma_enabled(s))
		mxs_auart_dma_निकास(s);

	अगर (uart_console(u)) अणु
		mxs_clr(AUART_CTRL2_UARTEN, s, REG_CTRL2);

		mxs_clr(AUART_INTR_RXIEN | AUART_INTR_RTIEN |
			AUART_INTR_CTSMIEN, s, REG_INTR);
		mxs_set(AUART_CTRL0_CLKGATE, s, REG_CTRL0);
	पूर्ण अन्यथा अणु
		mxs_auart_reset_निश्चित(s);
	पूर्ण

	clk_disable_unprepare(s->clk);
पूर्ण

अटल अचिन्हित पूर्णांक mxs_auart_tx_empty(काष्ठा uart_port *u)
अणु
	काष्ठा mxs_auart_port *s = to_auart_port(u);

	अगर ((mxs_पढ़ो(s, REG_STAT) &
		 (AUART_STAT_TXFE | AUART_STAT_BUSY)) == AUART_STAT_TXFE)
		वापस TIOCSER_TEMT;

	वापस 0;
पूर्ण

अटल व्योम mxs_auart_start_tx(काष्ठा uart_port *u)
अणु
	काष्ठा mxs_auart_port *s = to_auart_port(u);

	/* enable transmitter */
	mxs_set(AUART_CTRL2_TXE, s, REG_CTRL2);

	mxs_auart_tx_अक्षरs(s);
पूर्ण

अटल व्योम mxs_auart_stop_tx(काष्ठा uart_port *u)
अणु
	काष्ठा mxs_auart_port *s = to_auart_port(u);

	mxs_clr(AUART_CTRL2_TXE, s, REG_CTRL2);
पूर्ण

अटल व्योम mxs_auart_stop_rx(काष्ठा uart_port *u)
अणु
	काष्ठा mxs_auart_port *s = to_auart_port(u);

	mxs_clr(AUART_CTRL2_RXE, s, REG_CTRL2);
पूर्ण

अटल व्योम mxs_auart_अवरोध_ctl(काष्ठा uart_port *u, पूर्णांक ctl)
अणु
	काष्ठा mxs_auart_port *s = to_auart_port(u);

	अगर (ctl)
		mxs_set(AUART_LINECTRL_BRK, s, REG_LINECTRL);
	अन्यथा
		mxs_clr(AUART_LINECTRL_BRK, s, REG_LINECTRL);
पूर्ण

अटल स्थिर काष्ठा uart_ops mxs_auart_ops = अणु
	.tx_empty       = mxs_auart_tx_empty,
	.start_tx       = mxs_auart_start_tx,
	.stop_tx	= mxs_auart_stop_tx,
	.stop_rx	= mxs_auart_stop_rx,
	.enable_ms      = mxs_auart_enable_ms,
	.अवरोध_ctl      = mxs_auart_अवरोध_ctl,
	.set_mctrl	= mxs_auart_set_mctrl,
	.get_mctrl      = mxs_auart_get_mctrl,
	.startup	= mxs_auart_startup,
	.shutकरोwn       = mxs_auart_shutकरोwn,
	.set_termios    = mxs_auart_settermios,
	.set_ldisc      = mxs_auart_set_ldisc,
	.type	   	= mxs_auart_type,
	.release_port   = mxs_auart_release_port,
	.request_port   = mxs_auart_request_port,
	.config_port    = mxs_auart_config_port,
	.verअगरy_port    = mxs_auart_verअगरy_port,
पूर्ण;

अटल काष्ठा mxs_auart_port *auart_port[MXS_AUART_PORTS];

#अगर_घोषित CONFIG_SERIAL_MXS_AUART_CONSOLE
अटल व्योम mxs_auart_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	काष्ठा mxs_auart_port *s = to_auart_port(port);
	अचिन्हित पूर्णांक to = 1000;

	जबतक (mxs_पढ़ो(s, REG_STAT) & AUART_STAT_TXFF) अणु
		अगर (!to--)
			अवरोध;
		udelay(1);
	पूर्ण

	mxs_ग_लिखो(ch, s, REG_DATA);
पूर्ण

अटल व्योम
auart_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *str, अचिन्हित पूर्णांक count)
अणु
	काष्ठा mxs_auart_port *s;
	काष्ठा uart_port *port;
	अचिन्हित पूर्णांक old_ctrl0, old_ctrl2;
	अचिन्हित पूर्णांक to = 20000;

	अगर (co->index >= MXS_AUART_PORTS || co->index < 0)
		वापस;

	s = auart_port[co->index];
	port = &s->port;

	clk_enable(s->clk);

	/* First save the CR then disable the पूर्णांकerrupts */
	old_ctrl2 = mxs_पढ़ो(s, REG_CTRL2);
	old_ctrl0 = mxs_पढ़ो(s, REG_CTRL0);

	mxs_clr(AUART_CTRL0_CLKGATE, s, REG_CTRL0);
	mxs_set(AUART_CTRL2_UARTEN | AUART_CTRL2_TXE, s, REG_CTRL2);

	uart_console_ग_लिखो(port, str, count, mxs_auart_console_अक्षर_दो);

	/* Finally, रुको क्रम transmitter to become empty ... */
	जबतक (mxs_पढ़ो(s, REG_STAT) & AUART_STAT_BUSY) अणु
		udelay(1);
		अगर (!to--)
			अवरोध;
	पूर्ण

	/*
	 * ... and restore the TCR अगर we रुकोed दीर्घ enough क्रम the transmitter
	 * to be idle. This might keep the transmitter enabled although it is
	 * unused, but that is better than to disable it जबतक it is still
	 * transmitting.
	 */
	अगर (!(mxs_पढ़ो(s, REG_STAT) & AUART_STAT_BUSY)) अणु
		mxs_ग_लिखो(old_ctrl0, s, REG_CTRL0);
		mxs_ग_लिखो(old_ctrl2, s, REG_CTRL2);
	पूर्ण

	clk_disable(s->clk);
पूर्ण

अटल व्योम __init
auart_console_get_options(काष्ठा mxs_auart_port *s, पूर्णांक *baud,
			  पूर्णांक *parity, पूर्णांक *bits)
अणु
	काष्ठा uart_port *port = &s->port;
	अचिन्हित पूर्णांक lcr_h, quot;

	अगर (!(mxs_पढ़ो(s, REG_CTRL2) & AUART_CTRL2_UARTEN))
		वापस;

	lcr_h = mxs_पढ़ो(s, REG_LINECTRL);

	*parity = 'n';
	अगर (lcr_h & AUART_LINECTRL_PEN) अणु
		अगर (lcr_h & AUART_LINECTRL_EPS)
			*parity = 'e';
		अन्यथा
			*parity = 'o';
	पूर्ण

	अगर ((lcr_h & AUART_LINECTRL_WLEN_MASK) == AUART_LINECTRL_WLEN(2))
		*bits = 7;
	अन्यथा
		*bits = 8;

	quot = ((mxs_पढ़ो(s, REG_LINECTRL) & AUART_LINECTRL_BAUD_DIVINT_MASK))
		>> (AUART_LINECTRL_BAUD_DIVINT_SHIFT - 6);
	quot |= ((mxs_पढ़ो(s, REG_LINECTRL) & AUART_LINECTRL_BAUD_DIVFRAC_MASK))
		>> AUART_LINECTRL_BAUD_DIVFRAC_SHIFT;
	अगर (quot == 0)
		quot = 1;

	*baud = (port->uartclk << 2) / quot;
पूर्ण

अटल पूर्णांक __init
auart_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा mxs_auart_port *s;
	पूर्णांक baud = 9600;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';
	पूर्णांक ret;

	/*
	 * Check whether an invalid uart number has been specअगरied, and
	 * अगर so, search क्रम the first available port that करोes have
	 * console support.
	 */
	अगर (co->index == -1 || co->index >= ARRAY_SIZE(auart_port))
		co->index = 0;
	s = auart_port[co->index];
	अगर (!s)
		वापस -ENODEV;

	ret = clk_prepare_enable(s->clk);
	अगर (ret)
		वापस ret;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	अन्यथा
		auart_console_get_options(s, &baud, &parity, &bits);

	ret = uart_set_options(&s->port, co, baud, parity, bits, flow);

	clk_disable_unprepare(s->clk);

	वापस ret;
पूर्ण

अटल काष्ठा console auart_console = अणु
	.name		= "ttyAPP",
	.ग_लिखो		= auart_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= auart_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &auart_driver,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा uart_driver auart_driver = अणु
	.owner		= THIS_MODULE,
	.driver_name	= "ttyAPP",
	.dev_name	= "ttyAPP",
	.major		= 0,
	.minor		= 0,
	.nr		= MXS_AUART_PORTS,
#अगर_घोषित CONFIG_SERIAL_MXS_AUART_CONSOLE
	.cons =		&auart_console,
#पूर्ण_अगर
पूर्ण;

अटल व्योम mxs_init_regs(काष्ठा mxs_auart_port *s)
अणु
	अगर (is_यंत्र9260_auart(s))
		s->venकरोr = &venकरोr_alphascale_यंत्र9260;
	अन्यथा
		s->venकरोr = &venकरोr_मुक्तscale_sपंचांगp37xx;
पूर्ण

अटल पूर्णांक mxs_get_clks(काष्ठा mxs_auart_port *s,
			काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;

	अगर (!is_यंत्र9260_auart(s)) अणु
		s->clk = devm_clk_get(&pdev->dev, शून्य);
		वापस PTR_ERR_OR_ZERO(s->clk);
	पूर्ण

	s->clk = devm_clk_get(s->dev, "mod");
	अगर (IS_ERR(s->clk)) अणु
		dev_err(s->dev, "Failed to get \"mod\" clk\n");
		वापस PTR_ERR(s->clk);
	पूर्ण

	s->clk_ahb = devm_clk_get(s->dev, "ahb");
	अगर (IS_ERR(s->clk_ahb)) अणु
		dev_err(s->dev, "Failed to get \"ahb\" clk\n");
		वापस PTR_ERR(s->clk_ahb);
	पूर्ण

	err = clk_prepare_enable(s->clk_ahb);
	अगर (err) अणु
		dev_err(s->dev, "Failed to enable ahb_clk!\n");
		वापस err;
	पूर्ण

	err = clk_set_rate(s->clk, clk_get_rate(s->clk_ahb));
	अगर (err) अणु
		dev_err(s->dev, "Failed to set rate!\n");
		जाओ disable_clk_ahb;
	पूर्ण

	err = clk_prepare_enable(s->clk);
	अगर (err) अणु
		dev_err(s->dev, "Failed to enable clk!\n");
		जाओ disable_clk_ahb;
	पूर्ण

	वापस 0;

disable_clk_ahb:
	clk_disable_unprepare(s->clk_ahb);
	वापस err;
पूर्ण

अटल पूर्णांक mxs_auart_init_gpios(काष्ठा mxs_auart_port *s, काष्ठा device *dev)
अणु
	क्रमागत mctrl_gpio_idx i;
	काष्ठा gpio_desc *gpiod;

	s->gpios = mctrl_gpio_init_noस्वतः(dev, 0);
	अगर (IS_ERR(s->gpios))
		वापस PTR_ERR(s->gpios);

	/* Block (enabled beक्रमe) DMA option अगर RTS or CTS is GPIO line */
	अगर (!RTS_AT_AUART() || !CTS_AT_AUART()) अणु
		अगर (test_bit(MXS_AUART_RTSCTS, &s->flags))
			dev_warn(dev,
				 "DMA and flow control via gpio may cause some problems. DMA disabled!\n");
		clear_bit(MXS_AUART_RTSCTS, &s->flags);
	पूर्ण

	क्रम (i = 0; i < UART_GPIO_MAX; i++) अणु
		gpiod = mctrl_gpio_to_gpiod(s->gpios, i);
		अगर (gpiod && (gpiod_get_direction(gpiod) == 1))
			s->gpio_irq[i] = gpiod_to_irq(gpiod);
		अन्यथा
			s->gpio_irq[i] = -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mxs_auart_मुक्त_gpio_irq(काष्ठा mxs_auart_port *s)
अणु
	क्रमागत mctrl_gpio_idx i;

	क्रम (i = 0; i < UART_GPIO_MAX; i++)
		अगर (s->gpio_irq[i] >= 0)
			मुक्त_irq(s->gpio_irq[i], s);
पूर्ण

अटल पूर्णांक mxs_auart_request_gpio_irq(काष्ठा mxs_auart_port *s)
अणु
	पूर्णांक *irq = s->gpio_irq;
	क्रमागत mctrl_gpio_idx i;
	पूर्णांक err = 0;

	क्रम (i = 0; (i < UART_GPIO_MAX) && !err; i++) अणु
		अगर (irq[i] < 0)
			जारी;

		irq_set_status_flags(irq[i], IRQ_NOAUTOEN);
		err = request_irq(irq[i], mxs_auart_irq_handle,
				IRQ_TYPE_EDGE_BOTH, dev_name(s->dev), s);
		अगर (err)
			dev_err(s->dev, "%s - Can't get %d irq\n",
				__func__, irq[i]);
	पूर्ण

	/*
	 * If something went wrong, rollback.
	 * Be careful: i may be अचिन्हित.
	 */
	जबतक (err && (i-- > 0))
		अगर (irq[i] >= 0)
			मुक्त_irq(irq[i], s);

	वापस err;
पूर्ण

अटल पूर्णांक mxs_auart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा mxs_auart_port *s;
	u32 version;
	पूर्णांक ret, irq;
	काष्ठा resource *r;

	s = devm_kzalloc(&pdev->dev, माप(*s), GFP_KERNEL);
	अगर (!s)
		वापस -ENOMEM;

	s->port.dev = &pdev->dev;
	s->dev = &pdev->dev;

	ret = of_alias_get_id(np, "serial");
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to get alias id: %d\n", ret);
		वापस ret;
	पूर्ण
	s->port.line = ret;

	अगर (of_get_property(np, "uart-has-rtscts", शून्य) ||
	    of_get_property(np, "fsl,uart-has-rtscts", शून्य) /* deprecated */)
		set_bit(MXS_AUART_RTSCTS, &s->flags);

	अगर (s->port.line >= ARRAY_SIZE(auart_port)) अणु
		dev_err(&pdev->dev, "serial%d out of range\n", s->port.line);
		वापस -EINVAL;
	पूर्ण

	s->devtype = (क्रमागत mxs_auart_type)of_device_get_match_data(&pdev->dev);

	ret = mxs_get_clks(s, pdev);
	अगर (ret)
		वापस ret;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		ret = -ENXIO;
		जाओ out_disable_clks;
	पूर्ण

	s->port.mapbase = r->start;
	s->port.membase = ioremap(r->start, resource_size(r));
	अगर (!s->port.membase) अणु
		ret = -ENOMEM;
		जाओ out_disable_clks;
	पूर्ण
	s->port.ops = &mxs_auart_ops;
	s->port.iotype = UPIO_MEM;
	s->port.fअगरosize = MXS_AUART_FIFO_SIZE;
	s->port.uartclk = clk_get_rate(s->clk);
	s->port.type = PORT_IMX;
	s->port.has_sysrq = IS_ENABLED(CONFIG_SERIAL_MXS_AUART_CONSOLE);

	mxs_init_regs(s);

	s->mctrl_prev = 0;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ out_iounmap;
	पूर्ण

	s->port.irq = irq;
	ret = devm_request_irq(&pdev->dev, irq, mxs_auart_irq_handle, 0,
			       dev_name(&pdev->dev), s);
	अगर (ret)
		जाओ out_iounmap;

	platक्रमm_set_drvdata(pdev, s);

	ret = mxs_auart_init_gpios(s, &pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to initialize GPIOs.\n");
		जाओ out_iounmap;
	पूर्ण

	/*
	 * Get the GPIO lines IRQ
	 */
	ret = mxs_auart_request_gpio_irq(s);
	अगर (ret)
		जाओ out_iounmap;

	auart_port[s->port.line] = s;

	mxs_auart_reset_deनिश्चित(s);

	ret = uart_add_one_port(&auart_driver, &s->port);
	अगर (ret)
		जाओ out_मुक्त_qpio_irq;

	/* ASM9260 करोn't have version reg */
	अगर (is_यंत्र9260_auart(s)) अणु
		dev_info(&pdev->dev, "Found APPUART ASM9260\n");
	पूर्ण अन्यथा अणु
		version = mxs_पढ़ो(s, REG_VERSION);
		dev_info(&pdev->dev, "Found APPUART %d.%d.%d\n",
			 (version >> 24) & 0xff,
			 (version >> 16) & 0xff, version & 0xffff);
	पूर्ण

	वापस 0;

out_मुक्त_qpio_irq:
	mxs_auart_मुक्त_gpio_irq(s);
	auart_port[pdev->id] = शून्य;

out_iounmap:
	iounmap(s->port.membase);

out_disable_clks:
	अगर (is_यंत्र9260_auart(s)) अणु
		clk_disable_unprepare(s->clk);
		clk_disable_unprepare(s->clk_ahb);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक mxs_auart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mxs_auart_port *s = platक्रमm_get_drvdata(pdev);

	uart_हटाओ_one_port(&auart_driver, &s->port);
	auart_port[pdev->id] = शून्य;
	mxs_auart_मुक्त_gpio_irq(s);
	iounmap(s->port.membase);
	अगर (is_यंत्र9260_auart(s)) अणु
		clk_disable_unprepare(s->clk);
		clk_disable_unprepare(s->clk_ahb);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mxs_auart_driver = अणु
	.probe = mxs_auart_probe,
	.हटाओ = mxs_auart_हटाओ,
	.driver = अणु
		.name = "mxs-auart",
		.of_match_table = mxs_auart_dt_ids,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mxs_auart_init(व्योम)
अणु
	पूर्णांक r;

	r = uart_रेजिस्टर_driver(&auart_driver);
	अगर (r)
		जाओ out;

	r = platक्रमm_driver_रेजिस्टर(&mxs_auart_driver);
	अगर (r)
		जाओ out_err;

	वापस 0;
out_err:
	uart_unरेजिस्टर_driver(&auart_driver);
out:
	वापस r;
पूर्ण

अटल व्योम __निकास mxs_auart_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mxs_auart_driver);
	uart_unरेजिस्टर_driver(&auart_driver);
पूर्ण

module_init(mxs_auart_init);
module_निकास(mxs_auart_निकास);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Freescale MXS application uart driver");
MODULE_ALIAS("platform:mxs-auart");
