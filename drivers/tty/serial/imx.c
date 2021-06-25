<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Motorola/Freescale IMX serial ports
 *
 * Based on drivers/अक्षर/serial.c, by Linus Torvalds, Theoकरोre Ts'o.
 *
 * Author: Sascha Hauer <sascha@saschahauer.de>
 * Copyright (C) 2004 Pengutronix
 */

#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/rational.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/irq.h>
#समावेश <linux/platक्रमm_data/dma-imx.h>

#समावेश "serial_mctrl_gpio.h"

/* Register definitions */
#घोषणा URXD0 0x0  /* Receiver Register */
#घोषणा URTX0 0x40 /* Transmitter Register */
#घोषणा UCR1  0x80 /* Control Register 1 */
#घोषणा UCR2  0x84 /* Control Register 2 */
#घोषणा UCR3  0x88 /* Control Register 3 */
#घोषणा UCR4  0x8c /* Control Register 4 */
#घोषणा UFCR  0x90 /* FIFO Control Register */
#घोषणा USR1  0x94 /* Status Register 1 */
#घोषणा USR2  0x98 /* Status Register 2 */
#घोषणा UESC  0x9c /* Escape Character Register */
#घोषणा UTIM  0xa0 /* Escape Timer Register */
#घोषणा UBIR  0xa4 /* BRM Incremental Register */
#घोषणा UBMR  0xa8 /* BRM Modulator Register */
#घोषणा UBRC  0xac /* Baud Rate Count Register */
#घोषणा IMX21_ONEMS 0xb0 /* One Millisecond रेजिस्टर */
#घोषणा IMX1_UTS 0xd0 /* UART Test Register on i.mx1 */
#घोषणा IMX21_UTS 0xb4 /* UART Test Register on all other i.mx*/

/* UART Control Register Bit Fields.*/
#घोषणा URXD_DUMMY_READ (1<<16)
#घोषणा URXD_CHARRDY	(1<<15)
#घोषणा URXD_ERR	(1<<14)
#घोषणा URXD_OVRRUN	(1<<13)
#घोषणा URXD_FRMERR	(1<<12)
#घोषणा URXD_BRK	(1<<11)
#घोषणा URXD_PRERR	(1<<10)
#घोषणा URXD_RX_DATA	(0xFF<<0)
#घोषणा UCR1_ADEN	(1<<15) /* Auto detect पूर्णांकerrupt */
#घोषणा UCR1_ADBR	(1<<14) /* Auto detect baud rate */
#घोषणा UCR1_TRDYEN	(1<<13) /* Transmitter पढ़ोy पूर्णांकerrupt enable */
#घोषणा UCR1_IDEN	(1<<12) /* Idle condition पूर्णांकerrupt */
#घोषणा UCR1_ICD_REG(x) (((x) & 3) << 10) /* idle condition detect */
#घोषणा UCR1_RRDYEN	(1<<9)	/* Recv पढ़ोy पूर्णांकerrupt enable */
#घोषणा UCR1_RXDMAEN	(1<<8)	/* Recv पढ़ोy DMA enable */
#घोषणा UCR1_IREN	(1<<7)	/* Infrared पूर्णांकerface enable */
#घोषणा UCR1_TXMPTYEN	(1<<6)	/* Transimitter empty पूर्णांकerrupt enable */
#घोषणा UCR1_RTSDEN	(1<<5)	/* RTS delta पूर्णांकerrupt enable */
#घोषणा UCR1_SNDBRK	(1<<4)	/* Send अवरोध */
#घोषणा UCR1_TXDMAEN	(1<<3)	/* Transmitter पढ़ोy DMA enable */
#घोषणा IMX1_UCR1_UARTCLKEN (1<<2) /* UART घड़ी enabled, i.mx1 only */
#घोषणा UCR1_ATDMAEN    (1<<2)  /* Aging DMA Timer Enable */
#घोषणा UCR1_DOZE	(1<<1)	/* Doze */
#घोषणा UCR1_UARTEN	(1<<0)	/* UART enabled */
#घोषणा UCR2_ESCI	(1<<15)	/* Escape seq पूर्णांकerrupt enable */
#घोषणा UCR2_IRTS	(1<<14)	/* Ignore RTS pin */
#घोषणा UCR2_CTSC	(1<<13)	/* CTS pin control */
#घोषणा UCR2_CTS	(1<<12)	/* Clear to send */
#घोषणा UCR2_ESCEN	(1<<11)	/* Escape enable */
#घोषणा UCR2_PREN	(1<<8)	/* Parity enable */
#घोषणा UCR2_PROE	(1<<7)	/* Parity odd/even */
#घोषणा UCR2_STPB	(1<<6)	/* Stop */
#घोषणा UCR2_WS		(1<<5)	/* Word size */
#घोषणा UCR2_RTSEN	(1<<4)	/* Request to send पूर्णांकerrupt enable */
#घोषणा UCR2_ATEN	(1<<3)	/* Aging Timer Enable */
#घोषणा UCR2_TXEN	(1<<2)	/* Transmitter enabled */
#घोषणा UCR2_RXEN	(1<<1)	/* Receiver enabled */
#घोषणा UCR2_SRST	(1<<0)	/* SW reset */
#घोषणा UCR3_DTREN	(1<<13) /* DTR पूर्णांकerrupt enable */
#घोषणा UCR3_PARERREN	(1<<12) /* Parity enable */
#घोषणा UCR3_FRAERREN	(1<<11) /* Frame error पूर्णांकerrupt enable */
#घोषणा UCR3_DSR	(1<<10) /* Data set पढ़ोy */
#घोषणा UCR3_DCD	(1<<9)	/* Data carrier detect */
#घोषणा UCR3_RI		(1<<8)	/* Ring indicator */
#घोषणा UCR3_ADNIMP	(1<<7)	/* Autobaud Detection Not Improved */
#घोषणा UCR3_RXDSEN	(1<<6)	/* Receive status पूर्णांकerrupt enable */
#घोषणा UCR3_AIRINTEN	(1<<5)	/* Async IR wake पूर्णांकerrupt enable */
#घोषणा UCR3_AWAKEN	(1<<4)	/* Async wake पूर्णांकerrupt enable */
#घोषणा UCR3_DTRDEN	(1<<3)	/* Data Terminal Ready Delta Enable. */
#घोषणा IMX21_UCR3_RXDMUXSEL	(1<<2)	/* RXD Muxed Input Select */
#घोषणा UCR3_INVT	(1<<1)	/* Inverted Infrared transmission */
#घोषणा UCR3_BPEN	(1<<0)	/* Preset रेजिस्टरs enable */
#घोषणा UCR4_CTSTL_SHF	10	/* CTS trigger level shअगरt */
#घोषणा UCR4_CTSTL_MASK	0x3F	/* CTS trigger is 6 bits wide */
#घोषणा UCR4_INVR	(1<<9)	/* Inverted infrared reception */
#घोषणा UCR4_ENIRI	(1<<8)	/* Serial infrared पूर्णांकerrupt enable */
#घोषणा UCR4_WKEN	(1<<7)	/* Wake पूर्णांकerrupt enable */
#घोषणा UCR4_REF16	(1<<6)	/* Ref freq 16 MHz */
#घोषणा UCR4_IDDMAEN    (1<<6)  /* DMA IDLE Condition Detected */
#घोषणा UCR4_IRSC	(1<<5)	/* IR special हाल */
#घोषणा UCR4_TCEN	(1<<3)	/* Transmit complete पूर्णांकerrupt enable */
#घोषणा UCR4_BKEN	(1<<2)	/* Break condition पूर्णांकerrupt enable */
#घोषणा UCR4_OREN	(1<<1)	/* Receiver overrun पूर्णांकerrupt enable */
#घोषणा UCR4_DREN	(1<<0)	/* Recv data पढ़ोy पूर्णांकerrupt enable */
#घोषणा UFCR_RXTL_SHF	0	/* Receiver trigger level shअगरt */
#घोषणा UFCR_DCEDTE	(1<<6)	/* DCE/DTE mode select */
#घोषणा UFCR_RFDIV	(7<<7)	/* Reference freq भागider mask */
#घोषणा UFCR_RFDIV_REG(x)	(((x) < 7 ? 6 - (x) : 6) << 7)
#घोषणा UFCR_TXTL_SHF	10	/* Transmitter trigger level shअगरt */
#घोषणा USR1_PARITYERR	(1<<15) /* Parity error पूर्णांकerrupt flag */
#घोषणा USR1_RTSS	(1<<14) /* RTS pin status */
#घोषणा USR1_TRDY	(1<<13) /* Transmitter पढ़ोy पूर्णांकerrupt/dma flag */
#घोषणा USR1_RTSD	(1<<12) /* RTS delta */
#घोषणा USR1_ESCF	(1<<11) /* Escape seq पूर्णांकerrupt flag */
#घोषणा USR1_FRAMERR	(1<<10) /* Frame error पूर्णांकerrupt flag */
#घोषणा USR1_RRDY	(1<<9)	 /* Receiver पढ़ोy पूर्णांकerrupt/dma flag */
#घोषणा USR1_AGTIM	(1<<8)	 /* Ageing समयr पूर्णांकerrupt flag */
#घोषणा USR1_DTRD	(1<<7)	 /* DTR Delta */
#घोषणा USR1_RXDS	 (1<<6)	 /* Receiver idle पूर्णांकerrupt flag */
#घोषणा USR1_AIRINT	 (1<<5)	 /* Async IR wake पूर्णांकerrupt flag */
#घोषणा USR1_AWAKE	 (1<<4)	 /* Aysnc wake पूर्णांकerrupt flag */
#घोषणा USR2_ADET	 (1<<15) /* Auto baud rate detect complete */
#घोषणा USR2_TXFE	 (1<<14) /* Transmit buffer FIFO empty */
#घोषणा USR2_DTRF	 (1<<13) /* DTR edge पूर्णांकerrupt flag */
#घोषणा USR2_IDLE	 (1<<12) /* Idle condition */
#घोषणा USR2_RIDELT	 (1<<10) /* Ring Interrupt Delta */
#घोषणा USR2_RIIN	 (1<<9)	 /* Ring Indicator Input */
#घोषणा USR2_IRINT	 (1<<8)	 /* Serial infrared पूर्णांकerrupt flag */
#घोषणा USR2_WAKE	 (1<<7)	 /* Wake */
#घोषणा USR2_DCDIN	 (1<<5)	 /* Data Carrier Detect Input */
#घोषणा USR2_RTSF	 (1<<4)	 /* RTS edge पूर्णांकerrupt flag */
#घोषणा USR2_TXDC	 (1<<3)	 /* Transmitter complete */
#घोषणा USR2_BRCD	 (1<<2)	 /* Break condition */
#घोषणा USR2_ORE	(1<<1)	 /* Overrun error */
#घोषणा USR2_RDR	(1<<0)	 /* Recv data पढ़ोy */
#घोषणा UTS_FRCPERR	(1<<13) /* Force parity error */
#घोषणा UTS_LOOP	(1<<12)	 /* Loop tx and rx */
#घोषणा UTS_TXEMPTY	 (1<<6)	 /* TxFIFO empty */
#घोषणा UTS_RXEMPTY	 (1<<5)	 /* RxFIFO empty */
#घोषणा UTS_TXFULL	 (1<<4)	 /* TxFIFO full */
#घोषणा UTS_RXFULL	 (1<<3)	 /* RxFIFO full */
#घोषणा UTS_SOFTRST	 (1<<0)	 /* Software reset */

/* We've been asचिन्हित a range on the "Low-density serial ports" major */
#घोषणा SERIAL_IMX_MAJOR	207
#घोषणा MINOR_START		16
#घोषणा DEV_NAME		"ttymxc"

/*
 * This determines how often we check the modem status संकेतs
 * क्रम any change.  They generally aren't connected to an IRQ
 * so we have to poll them.  We also check immediately beक्रमe
 * filling the TX fअगरo inहाल CTS has been dropped.
 */
#घोषणा MCTRL_TIMEOUT	(250*HZ/1000)

#घोषणा DRIVER_NAME "IMX-uart"

#घोषणा UART_NR 8

/* i.MX21 type uart runs on all i.mx except i.MX1 and i.MX6q */
क्रमागत imx_uart_type अणु
	IMX1_UART,
	IMX21_UART,
	IMX53_UART,
	IMX6Q_UART,
पूर्ण;

/* device type dependent stuff */
काष्ठा imx_uart_data अणु
	अचिन्हित uts_reg;
	क्रमागत imx_uart_type devtype;
पूर्ण;

क्रमागत imx_tx_state अणु
	OFF,
	WAIT_AFTER_RTS,
	SEND,
	WAIT_AFTER_SEND,
पूर्ण;

काष्ठा imx_port अणु
	काष्ठा uart_port	port;
	काष्ठा समयr_list	समयr;
	अचिन्हित पूर्णांक		old_status;
	अचिन्हित पूर्णांक		have_rtscts:1;
	अचिन्हित पूर्णांक		have_rtsgpio:1;
	अचिन्हित पूर्णांक		dte_mode:1;
	अचिन्हित पूर्णांक		inverted_tx:1;
	अचिन्हित पूर्णांक		inverted_rx:1;
	काष्ठा clk		*clk_ipg;
	काष्ठा clk		*clk_per;
	स्थिर काष्ठा imx_uart_data *devdata;

	काष्ठा mctrl_gpios *gpios;

	/* shaकरोw रेजिस्टरs */
	अचिन्हित पूर्णांक ucr1;
	अचिन्हित पूर्णांक ucr2;
	अचिन्हित पूर्णांक ucr3;
	अचिन्हित पूर्णांक ucr4;
	अचिन्हित पूर्णांक ufcr;

	/* DMA fields */
	अचिन्हित पूर्णांक		dma_is_enabled:1;
	अचिन्हित पूर्णांक		dma_is_rxing:1;
	अचिन्हित पूर्णांक		dma_is_txing:1;
	काष्ठा dma_chan		*dma_chan_rx, *dma_chan_tx;
	काष्ठा scatterlist	rx_sgl, tx_sgl[2];
	व्योम			*rx_buf;
	काष्ठा circ_buf		rx_ring;
	अचिन्हित पूर्णांक		rx_periods;
	dma_cookie_t		rx_cookie;
	अचिन्हित पूर्णांक		tx_bytes;
	अचिन्हित पूर्णांक		dma_tx_nents;
	अचिन्हित पूर्णांक            saved_reg[10];
	bool			context_saved;

	क्रमागत imx_tx_state	tx_state;
	काष्ठा hrसमयr		trigger_start_tx;
	काष्ठा hrसमयr		trigger_stop_tx;
पूर्ण;

काष्ठा imx_port_ucrs अणु
	अचिन्हित पूर्णांक	ucr1;
	अचिन्हित पूर्णांक	ucr2;
	अचिन्हित पूर्णांक	ucr3;
पूर्ण;

अटल काष्ठा imx_uart_data imx_uart_devdata[] = अणु
	[IMX1_UART] = अणु
		.uts_reg = IMX1_UTS,
		.devtype = IMX1_UART,
	पूर्ण,
	[IMX21_UART] = अणु
		.uts_reg = IMX21_UTS,
		.devtype = IMX21_UART,
	पूर्ण,
	[IMX53_UART] = अणु
		.uts_reg = IMX21_UTS,
		.devtype = IMX53_UART,
	पूर्ण,
	[IMX6Q_UART] = अणु
		.uts_reg = IMX21_UTS,
		.devtype = IMX6Q_UART,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx_uart_dt_ids[] = अणु
	अणु .compatible = "fsl,imx6q-uart", .data = &imx_uart_devdata[IMX6Q_UART], पूर्ण,
	अणु .compatible = "fsl,imx53-uart", .data = &imx_uart_devdata[IMX53_UART], पूर्ण,
	अणु .compatible = "fsl,imx1-uart", .data = &imx_uart_devdata[IMX1_UART], पूर्ण,
	अणु .compatible = "fsl,imx21-uart", .data = &imx_uart_devdata[IMX21_UART], पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_uart_dt_ids);

अटल व्योम imx_uart_ग_लिखोl(काष्ठा imx_port *sport, u32 val, u32 offset)
अणु
	चयन (offset) अणु
	हाल UCR1:
		sport->ucr1 = val;
		अवरोध;
	हाल UCR2:
		sport->ucr2 = val;
		अवरोध;
	हाल UCR3:
		sport->ucr3 = val;
		अवरोध;
	हाल UCR4:
		sport->ucr4 = val;
		अवरोध;
	हाल UFCR:
		sport->ufcr = val;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	ग_लिखोl(val, sport->port.membase + offset);
पूर्ण

अटल u32 imx_uart_पढ़ोl(काष्ठा imx_port *sport, u32 offset)
अणु
	चयन (offset) अणु
	हाल UCR1:
		वापस sport->ucr1;
		अवरोध;
	हाल UCR2:
		/*
		 * UCR2_SRST is the only bit in the cached रेजिस्टरs that might
		 * dअगरfer from the value that was last written. As it only
		 * स्वतःmatically becomes one after being cleared, reपढ़ो
		 * conditionally.
		 */
		अगर (!(sport->ucr2 & UCR2_SRST))
			sport->ucr2 = पढ़ोl(sport->port.membase + offset);
		वापस sport->ucr2;
		अवरोध;
	हाल UCR3:
		वापस sport->ucr3;
		अवरोध;
	हाल UCR4:
		वापस sport->ucr4;
		अवरोध;
	हाल UFCR:
		वापस sport->ufcr;
		अवरोध;
	शेष:
		वापस पढ़ोl(sport->port.membase + offset);
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित imx_uart_uts_reg(काष्ठा imx_port *sport)
अणु
	वापस sport->devdata->uts_reg;
पूर्ण

अटल अंतरभूत पूर्णांक imx_uart_is_imx1(काष्ठा imx_port *sport)
अणु
	वापस sport->devdata->devtype == IMX1_UART;
पूर्ण

अटल अंतरभूत पूर्णांक imx_uart_is_imx21(काष्ठा imx_port *sport)
अणु
	वापस sport->devdata->devtype == IMX21_UART;
पूर्ण

अटल अंतरभूत पूर्णांक imx_uart_is_imx53(काष्ठा imx_port *sport)
अणु
	वापस sport->devdata->devtype == IMX53_UART;
पूर्ण

अटल अंतरभूत पूर्णांक imx_uart_is_imx6q(काष्ठा imx_port *sport)
अणु
	वापस sport->devdata->devtype == IMX6Q_UART;
पूर्ण
/*
 * Save and restore functions क्रम UCR1, UCR2 and UCR3 रेजिस्टरs
 */
#अगर IS_ENABLED(CONFIG_SERIAL_IMX_CONSOLE)
अटल व्योम imx_uart_ucrs_save(काष्ठा imx_port *sport,
			       काष्ठा imx_port_ucrs *ucr)
अणु
	/* save control रेजिस्टरs */
	ucr->ucr1 = imx_uart_पढ़ोl(sport, UCR1);
	ucr->ucr2 = imx_uart_पढ़ोl(sport, UCR2);
	ucr->ucr3 = imx_uart_पढ़ोl(sport, UCR3);
पूर्ण

अटल व्योम imx_uart_ucrs_restore(काष्ठा imx_port *sport,
				  काष्ठा imx_port_ucrs *ucr)
अणु
	/* restore control रेजिस्टरs */
	imx_uart_ग_लिखोl(sport, ucr->ucr1, UCR1);
	imx_uart_ग_लिखोl(sport, ucr->ucr2, UCR2);
	imx_uart_ग_लिखोl(sport, ucr->ucr3, UCR3);
पूर्ण
#पूर्ण_अगर

/* called with port.lock taken and irqs caller dependent */
अटल व्योम imx_uart_rts_active(काष्ठा imx_port *sport, u32 *ucr2)
अणु
	*ucr2 &= ~(UCR2_CTSC | UCR2_CTS);

	sport->port.mctrl |= TIOCM_RTS;
	mctrl_gpio_set(sport->gpios, sport->port.mctrl);
पूर्ण

/* called with port.lock taken and irqs caller dependent */
अटल व्योम imx_uart_rts_inactive(काष्ठा imx_port *sport, u32 *ucr2)
अणु
	*ucr2 &= ~UCR2_CTSC;
	*ucr2 |= UCR2_CTS;

	sport->port.mctrl &= ~TIOCM_RTS;
	mctrl_gpio_set(sport->gpios, sport->port.mctrl);
पूर्ण

अटल व्योम start_hrसमयr_ms(काष्ठा hrसमयr *hrt, अचिन्हित दीर्घ msec)
अणु
       hrसमयr_start(hrt, ms_to_kसमय(msec), HRTIMER_MODE_REL);
पूर्ण

/* called with port.lock taken and irqs off */
अटल व्योम imx_uart_start_rx(काष्ठा uart_port *port)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;
	अचिन्हित पूर्णांक ucr1, ucr2;

	ucr1 = imx_uart_पढ़ोl(sport, UCR1);
	ucr2 = imx_uart_पढ़ोl(sport, UCR2);

	ucr2 |= UCR2_RXEN;

	अगर (sport->dma_is_enabled) अणु
		ucr1 |= UCR1_RXDMAEN | UCR1_ATDMAEN;
	पूर्ण अन्यथा अणु
		ucr1 |= UCR1_RRDYEN;
		ucr2 |= UCR2_ATEN;
	पूर्ण

	/* Write UCR2 first as it includes RXEN */
	imx_uart_ग_लिखोl(sport, ucr2, UCR2);
	imx_uart_ग_लिखोl(sport, ucr1, UCR1);
पूर्ण

/* called with port.lock taken and irqs off */
अटल व्योम imx_uart_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;
	u32 ucr1, ucr4, usr2;

	अगर (sport->tx_state == OFF)
		वापस;

	/*
	 * We are maybe in the SMP context, so अगर the DMA TX thपढ़ो is running
	 * on other cpu, we have to रुको क्रम it to finish.
	 */
	अगर (sport->dma_is_txing)
		वापस;

	ucr1 = imx_uart_पढ़ोl(sport, UCR1);
	imx_uart_ग_लिखोl(sport, ucr1 & ~UCR1_TRDYEN, UCR1);

	usr2 = imx_uart_पढ़ोl(sport, USR2);
	अगर (!(usr2 & USR2_TXDC)) अणु
		/* The shअगरter is still busy, so retry once TC triggers */
		वापस;
	पूर्ण

	ucr4 = imx_uart_पढ़ोl(sport, UCR4);
	ucr4 &= ~UCR4_TCEN;
	imx_uart_ग_लिखोl(sport, ucr4, UCR4);

	/* in rs485 mode disable transmitter */
	अगर (port->rs485.flags & SER_RS485_ENABLED) अणु
		अगर (sport->tx_state == SEND) अणु
			sport->tx_state = WAIT_AFTER_SEND;
			start_hrसमयr_ms(&sport->trigger_stop_tx,
					 port->rs485.delay_rts_after_send);
			वापस;
		पूर्ण

		अगर (sport->tx_state == WAIT_AFTER_RTS ||
		    sport->tx_state == WAIT_AFTER_SEND) अणु
			u32 ucr2;

			hrसमयr_try_to_cancel(&sport->trigger_start_tx);

			ucr2 = imx_uart_पढ़ोl(sport, UCR2);
			अगर (port->rs485.flags & SER_RS485_RTS_AFTER_SEND)
				imx_uart_rts_active(sport, &ucr2);
			अन्यथा
				imx_uart_rts_inactive(sport, &ucr2);
			imx_uart_ग_लिखोl(sport, ucr2, UCR2);

			imx_uart_start_rx(port);

			sport->tx_state = OFF;
		पूर्ण
	पूर्ण अन्यथा अणु
		sport->tx_state = OFF;
	पूर्ण
पूर्ण

/* called with port.lock taken and irqs off */
अटल व्योम imx_uart_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;
	u32 ucr1, ucr2;

	ucr1 = imx_uart_पढ़ोl(sport, UCR1);
	ucr2 = imx_uart_पढ़ोl(sport, UCR2);

	अगर (sport->dma_is_enabled) अणु
		ucr1 &= ~(UCR1_RXDMAEN | UCR1_ATDMAEN);
	पूर्ण अन्यथा अणु
		ucr1 &= ~UCR1_RRDYEN;
		ucr2 &= ~UCR2_ATEN;
	पूर्ण
	imx_uart_ग_लिखोl(sport, ucr1, UCR1);

	ucr2 &= ~UCR2_RXEN;
	imx_uart_ग_लिखोl(sport, ucr2, UCR2);
पूर्ण

/* called with port.lock taken and irqs off */
अटल व्योम imx_uart_enable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;

	mod_समयr(&sport->समयr, jअगरfies);

	mctrl_gpio_enable_ms(sport->gpios);
पूर्ण

अटल व्योम imx_uart_dma_tx(काष्ठा imx_port *sport);

/* called with port.lock taken and irqs off */
अटल अंतरभूत व्योम imx_uart_transmit_buffer(काष्ठा imx_port *sport)
अणु
	काष्ठा circ_buf *xmit = &sport->port.state->xmit;

	अगर (sport->port.x_अक्षर) अणु
		/* Send next अक्षर */
		imx_uart_ग_लिखोl(sport, sport->port.x_अक्षर, URTX0);
		sport->port.icount.tx++;
		sport->port.x_अक्षर = 0;
		वापस;
	पूर्ण

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(&sport->port)) अणु
		imx_uart_stop_tx(&sport->port);
		वापस;
	पूर्ण

	अगर (sport->dma_is_enabled) अणु
		u32 ucr1;
		/*
		 * We've just sent a X-अक्षर Ensure the TX DMA is enabled
		 * and the TX IRQ is disabled.
		 **/
		ucr1 = imx_uart_पढ़ोl(sport, UCR1);
		ucr1 &= ~UCR1_TRDYEN;
		अगर (sport->dma_is_txing) अणु
			ucr1 |= UCR1_TXDMAEN;
			imx_uart_ग_लिखोl(sport, ucr1, UCR1);
		पूर्ण अन्यथा अणु
			imx_uart_ग_लिखोl(sport, ucr1, UCR1);
			imx_uart_dma_tx(sport);
		पूर्ण

		वापस;
	पूर्ण

	जबतक (!uart_circ_empty(xmit) &&
	       !(imx_uart_पढ़ोl(sport, imx_uart_uts_reg(sport)) & UTS_TXFULL)) अणु
		/* send xmit->buf[xmit->tail]
		 * out the port here */
		imx_uart_ग_लिखोl(sport, xmit->buf[xmit->tail], URTX0);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		sport->port.icount.tx++;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&sport->port);

	अगर (uart_circ_empty(xmit))
		imx_uart_stop_tx(&sport->port);
पूर्ण

अटल व्योम imx_uart_dma_tx_callback(व्योम *data)
अणु
	काष्ठा imx_port *sport = data;
	काष्ठा scatterlist *sgl = &sport->tx_sgl[0];
	काष्ठा circ_buf *xmit = &sport->port.state->xmit;
	अचिन्हित दीर्घ flags;
	u32 ucr1;

	spin_lock_irqsave(&sport->port.lock, flags);

	dma_unmap_sg(sport->port.dev, sgl, sport->dma_tx_nents, DMA_TO_DEVICE);

	ucr1 = imx_uart_पढ़ोl(sport, UCR1);
	ucr1 &= ~UCR1_TXDMAEN;
	imx_uart_ग_लिखोl(sport, ucr1, UCR1);

	/* update the stat */
	xmit->tail = (xmit->tail + sport->tx_bytes) & (UART_XMIT_SIZE - 1);
	sport->port.icount.tx += sport->tx_bytes;

	dev_dbg(sport->port.dev, "we finish the TX DMA.\n");

	sport->dma_is_txing = 0;

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&sport->port);

	अगर (!uart_circ_empty(xmit) && !uart_tx_stopped(&sport->port))
		imx_uart_dma_tx(sport);
	अन्यथा अगर (sport->port.rs485.flags & SER_RS485_ENABLED) अणु
		u32 ucr4 = imx_uart_पढ़ोl(sport, UCR4);
		ucr4 |= UCR4_TCEN;
		imx_uart_ग_लिखोl(sport, ucr4, UCR4);
	पूर्ण

	spin_unlock_irqrestore(&sport->port.lock, flags);
पूर्ण

/* called with port.lock taken and irqs off */
अटल व्योम imx_uart_dma_tx(काष्ठा imx_port *sport)
अणु
	काष्ठा circ_buf *xmit = &sport->port.state->xmit;
	काष्ठा scatterlist *sgl = sport->tx_sgl;
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा dma_chan	*chan = sport->dma_chan_tx;
	काष्ठा device *dev = sport->port.dev;
	u32 ucr1, ucr4;
	पूर्णांक ret;

	अगर (sport->dma_is_txing)
		वापस;

	ucr4 = imx_uart_पढ़ोl(sport, UCR4);
	ucr4 &= ~UCR4_TCEN;
	imx_uart_ग_लिखोl(sport, ucr4, UCR4);

	sport->tx_bytes = uart_circ_अक्षरs_pending(xmit);

	अगर (xmit->tail < xmit->head || xmit->head == 0) अणु
		sport->dma_tx_nents = 1;
		sg_init_one(sgl, xmit->buf + xmit->tail, sport->tx_bytes);
	पूर्ण अन्यथा अणु
		sport->dma_tx_nents = 2;
		sg_init_table(sgl, 2);
		sg_set_buf(sgl, xmit->buf + xmit->tail,
				UART_XMIT_SIZE - xmit->tail);
		sg_set_buf(sgl + 1, xmit->buf, xmit->head);
	पूर्ण

	ret = dma_map_sg(dev, sgl, sport->dma_tx_nents, DMA_TO_DEVICE);
	अगर (ret == 0) अणु
		dev_err(dev, "DMA mapping error for TX.\n");
		वापस;
	पूर्ण
	desc = dmaengine_prep_slave_sg(chan, sgl, ret,
					DMA_MEM_TO_DEV, DMA_PREP_INTERRUPT);
	अगर (!desc) अणु
		dma_unmap_sg(dev, sgl, sport->dma_tx_nents,
			     DMA_TO_DEVICE);
		dev_err(dev, "We cannot prepare for the TX slave dma!\n");
		वापस;
	पूर्ण
	desc->callback = imx_uart_dma_tx_callback;
	desc->callback_param = sport;

	dev_dbg(dev, "TX: prepare to send %lu bytes by DMA.\n",
			uart_circ_अक्षरs_pending(xmit));

	ucr1 = imx_uart_पढ़ोl(sport, UCR1);
	ucr1 |= UCR1_TXDMAEN;
	imx_uart_ग_लिखोl(sport, ucr1, UCR1);

	/* fire it */
	sport->dma_is_txing = 1;
	dmaengine_submit(desc);
	dma_async_issue_pending(chan);
	वापस;
पूर्ण

/* called with port.lock taken and irqs off */
अटल व्योम imx_uart_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;
	u32 ucr1;

	अगर (!sport->port.x_अक्षर && uart_circ_empty(&port->state->xmit))
		वापस;

	/*
	 * We cannot simply करो nothing here अगर sport->tx_state == SEND alपढ़ोy
	 * because UCR1_TXMPTYEN might alपढ़ोy have been cleared in
	 * imx_uart_stop_tx(), but tx_state is still SEND.
	 */

	अगर (port->rs485.flags & SER_RS485_ENABLED) अणु
		अगर (sport->tx_state == OFF) अणु
			u32 ucr2 = imx_uart_पढ़ोl(sport, UCR2);
			अगर (port->rs485.flags & SER_RS485_RTS_ON_SEND)
				imx_uart_rts_active(sport, &ucr2);
			अन्यथा
				imx_uart_rts_inactive(sport, &ucr2);
			imx_uart_ग_लिखोl(sport, ucr2, UCR2);

			अगर (!(port->rs485.flags & SER_RS485_RX_DURING_TX))
				imx_uart_stop_rx(port);

			sport->tx_state = WAIT_AFTER_RTS;
			start_hrसमयr_ms(&sport->trigger_start_tx,
					 port->rs485.delay_rts_beक्रमe_send);
			वापस;
		पूर्ण

		अगर (sport->tx_state == WAIT_AFTER_SEND
		    || sport->tx_state == WAIT_AFTER_RTS) अणु

			hrसमयr_try_to_cancel(&sport->trigger_stop_tx);

			/*
			 * Enable transmitter and shअगरter empty irq only अगर DMA
			 * is off.  In the DMA हाल this is करोne in the
			 * tx-callback.
			 */
			अगर (!sport->dma_is_enabled) अणु
				u32 ucr4 = imx_uart_पढ़ोl(sport, UCR4);
				ucr4 |= UCR4_TCEN;
				imx_uart_ग_लिखोl(sport, ucr4, UCR4);
			पूर्ण

			sport->tx_state = SEND;
		पूर्ण
	पूर्ण अन्यथा अणु
		sport->tx_state = SEND;
	पूर्ण

	अगर (!sport->dma_is_enabled) अणु
		ucr1 = imx_uart_पढ़ोl(sport, UCR1);
		imx_uart_ग_लिखोl(sport, ucr1 | UCR1_TRDYEN, UCR1);
	पूर्ण

	अगर (sport->dma_is_enabled) अणु
		अगर (sport->port.x_अक्षर) अणु
			/* We have X-अक्षर to send, so enable TX IRQ and
			 * disable TX DMA to let TX पूर्णांकerrupt to send X-अक्षर */
			ucr1 = imx_uart_पढ़ोl(sport, UCR1);
			ucr1 &= ~UCR1_TXDMAEN;
			ucr1 |= UCR1_TRDYEN;
			imx_uart_ग_लिखोl(sport, ucr1, UCR1);
			वापस;
		पूर्ण

		अगर (!uart_circ_empty(&port->state->xmit) &&
		    !uart_tx_stopped(port))
			imx_uart_dma_tx(sport);
		वापस;
	पूर्ण
पूर्ण

अटल irqवापस_t __imx_uart_rtsपूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा imx_port *sport = dev_id;
	u32 usr1;

	imx_uart_ग_लिखोl(sport, USR1_RTSD, USR1);
	usr1 = imx_uart_पढ़ोl(sport, USR1) & USR1_RTSS;
	uart_handle_cts_change(&sport->port, !!usr1);
	wake_up_पूर्णांकerruptible(&sport->port.state->port.delta_msr_रुको);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t imx_uart_rtsपूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा imx_port *sport = dev_id;
	irqवापस_t ret;

	spin_lock(&sport->port.lock);

	ret = __imx_uart_rtsपूर्णांक(irq, dev_id);

	spin_unlock(&sport->port.lock);

	वापस ret;
पूर्ण

अटल irqवापस_t imx_uart_txपूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा imx_port *sport = dev_id;

	spin_lock(&sport->port.lock);
	imx_uart_transmit_buffer(sport);
	spin_unlock(&sport->port.lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t __imx_uart_rxपूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा imx_port *sport = dev_id;
	अचिन्हित पूर्णांक rx, flg, ignored = 0;
	काष्ठा tty_port *port = &sport->port.state->port;

	जबतक (imx_uart_पढ़ोl(sport, USR2) & USR2_RDR) अणु
		u32 usr2;

		flg = TTY_NORMAL;
		sport->port.icount.rx++;

		rx = imx_uart_पढ़ोl(sport, URXD0);

		usr2 = imx_uart_पढ़ोl(sport, USR2);
		अगर (usr2 & USR2_BRCD) अणु
			imx_uart_ग_लिखोl(sport, USR2_BRCD, USR2);
			अगर (uart_handle_अवरोध(&sport->port))
				जारी;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(&sport->port, (अचिन्हित अक्षर)rx))
			जारी;

		अगर (unlikely(rx & URXD_ERR)) अणु
			अगर (rx & URXD_BRK)
				sport->port.icount.brk++;
			अन्यथा अगर (rx & URXD_PRERR)
				sport->port.icount.parity++;
			अन्यथा अगर (rx & URXD_FRMERR)
				sport->port.icount.frame++;
			अगर (rx & URXD_OVRRUN)
				sport->port.icount.overrun++;

			अगर (rx & sport->port.ignore_status_mask) अणु
				अगर (++ignored > 100)
					जाओ out;
				जारी;
			पूर्ण

			rx &= (sport->port.पढ़ो_status_mask | 0xFF);

			अगर (rx & URXD_BRK)
				flg = TTY_BREAK;
			अन्यथा अगर (rx & URXD_PRERR)
				flg = TTY_PARITY;
			अन्यथा अगर (rx & URXD_FRMERR)
				flg = TTY_FRAME;
			अगर (rx & URXD_OVRRUN)
				flg = TTY_OVERRUN;

			sport->port.sysrq = 0;
		पूर्ण

		अगर (sport->port.ignore_status_mask & URXD_DUMMY_READ)
			जाओ out;

		अगर (tty_insert_flip_अक्षर(port, rx, flg) == 0)
			sport->port.icount.buf_overrun++;
	पूर्ण

out:
	tty_flip_buffer_push(port);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t imx_uart_rxपूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा imx_port *sport = dev_id;
	irqवापस_t ret;

	spin_lock(&sport->port.lock);

	ret = __imx_uart_rxपूर्णांक(irq, dev_id);

	spin_unlock(&sport->port.lock);

	वापस ret;
पूर्ण

अटल व्योम imx_uart_clear_rx_errors(काष्ठा imx_port *sport);

/*
 * We have a modem side uart, so the meanings of RTS and CTS are inverted.
 */
अटल अचिन्हित पूर्णांक imx_uart_get_hwmctrl(काष्ठा imx_port *sport)
अणु
	अचिन्हित पूर्णांक पंचांगp = TIOCM_DSR;
	अचिन्हित usr1 = imx_uart_पढ़ोl(sport, USR1);
	अचिन्हित usr2 = imx_uart_पढ़ोl(sport, USR2);

	अगर (usr1 & USR1_RTSS)
		पंचांगp |= TIOCM_CTS;

	/* in DCE mode DCDIN is always 0 */
	अगर (!(usr2 & USR2_DCDIN))
		पंचांगp |= TIOCM_CAR;

	अगर (sport->dte_mode)
		अगर (!(imx_uart_पढ़ोl(sport, USR2) & USR2_RIIN))
			पंचांगp |= TIOCM_RI;

	वापस पंचांगp;
पूर्ण

/*
 * Handle any change of modem status संकेत since we were last called.
 */
अटल व्योम imx_uart_mctrl_check(काष्ठा imx_port *sport)
अणु
	अचिन्हित पूर्णांक status, changed;

	status = imx_uart_get_hwmctrl(sport);
	changed = status ^ sport->old_status;

	अगर (changed == 0)
		वापस;

	sport->old_status = status;

	अगर (changed & TIOCM_RI && status & TIOCM_RI)
		sport->port.icount.rng++;
	अगर (changed & TIOCM_DSR)
		sport->port.icount.dsr++;
	अगर (changed & TIOCM_CAR)
		uart_handle_dcd_change(&sport->port, status & TIOCM_CAR);
	अगर (changed & TIOCM_CTS)
		uart_handle_cts_change(&sport->port, status & TIOCM_CTS);

	wake_up_पूर्णांकerruptible(&sport->port.state->port.delta_msr_रुको);
पूर्ण

अटल irqवापस_t imx_uart_पूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा imx_port *sport = dev_id;
	अचिन्हित पूर्णांक usr1, usr2, ucr1, ucr2, ucr3, ucr4;
	irqवापस_t ret = IRQ_NONE;

	spin_lock(&sport->port.lock);

	usr1 = imx_uart_पढ़ोl(sport, USR1);
	usr2 = imx_uart_पढ़ोl(sport, USR2);
	ucr1 = imx_uart_पढ़ोl(sport, UCR1);
	ucr2 = imx_uart_पढ़ोl(sport, UCR2);
	ucr3 = imx_uart_पढ़ोl(sport, UCR3);
	ucr4 = imx_uart_पढ़ोl(sport, UCR4);

	/*
	 * Even अगर a condition is true that can trigger an irq only handle it अगर
	 * the respective irq source is enabled. This prevents some undesired
	 * actions, क्रम example अगर a अक्षरacter that sits in the RX FIFO and that
	 * should be fetched via DMA is tried to be fetched using PIO. Or the
	 * receiver is currently off and so पढ़ोing from URXD0 results in an
	 * exception. So just mask the (raw) status bits क्रम disabled irqs.
	 */
	अगर ((ucr1 & UCR1_RRDYEN) == 0)
		usr1 &= ~USR1_RRDY;
	अगर ((ucr2 & UCR2_ATEN) == 0)
		usr1 &= ~USR1_AGTIM;
	अगर ((ucr1 & UCR1_TRDYEN) == 0)
		usr1 &= ~USR1_TRDY;
	अगर ((ucr4 & UCR4_TCEN) == 0)
		usr2 &= ~USR2_TXDC;
	अगर ((ucr3 & UCR3_DTRDEN) == 0)
		usr1 &= ~USR1_DTRD;
	अगर ((ucr1 & UCR1_RTSDEN) == 0)
		usr1 &= ~USR1_RTSD;
	अगर ((ucr3 & UCR3_AWAKEN) == 0)
		usr1 &= ~USR1_AWAKE;
	अगर ((ucr4 & UCR4_OREN) == 0)
		usr2 &= ~USR2_ORE;

	अगर (usr1 & (USR1_RRDY | USR1_AGTIM)) अणु
		imx_uart_ग_लिखोl(sport, USR1_AGTIM, USR1);

		__imx_uart_rxपूर्णांक(irq, dev_id);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर ((usr1 & USR1_TRDY) || (usr2 & USR2_TXDC)) अणु
		imx_uart_transmit_buffer(sport);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (usr1 & USR1_DTRD) अणु
		imx_uart_ग_लिखोl(sport, USR1_DTRD, USR1);

		imx_uart_mctrl_check(sport);

		ret = IRQ_HANDLED;
	पूर्ण

	अगर (usr1 & USR1_RTSD) अणु
		__imx_uart_rtsपूर्णांक(irq, dev_id);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (usr1 & USR1_AWAKE) अणु
		imx_uart_ग_लिखोl(sport, USR1_AWAKE, USR1);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (usr2 & USR2_ORE) अणु
		sport->port.icount.overrun++;
		imx_uart_ग_लिखोl(sport, USR2_ORE, USR2);
		ret = IRQ_HANDLED;
	पूर्ण

	spin_unlock(&sport->port.lock);

	वापस ret;
पूर्ण

/*
 * Return TIOCSER_TEMT when transmitter is not busy.
 */
अटल अचिन्हित पूर्णांक imx_uart_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;
	अचिन्हित पूर्णांक ret;

	ret = (imx_uart_पढ़ोl(sport, USR2) & USR2_TXDC) ?  TIOCSER_TEMT : 0;

	/* If the TX DMA is working, वापस 0. */
	अगर (sport->dma_is_txing)
		ret = 0;

	वापस ret;
पूर्ण

/* called with port.lock taken and irqs off */
अटल अचिन्हित पूर्णांक imx_uart_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;
	अचिन्हित पूर्णांक ret = imx_uart_get_hwmctrl(sport);

	mctrl_gpio_get(sport->gpios, &ret);

	वापस ret;
पूर्ण

/* called with port.lock taken and irqs off */
अटल व्योम imx_uart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;
	u32 ucr3, uts;

	अगर (!(port->rs485.flags & SER_RS485_ENABLED)) अणु
		u32 ucr2;

		/*
		 * Turn off स्वतःRTS अगर RTS is lowered and restore स्वतःRTS
		 * setting अगर RTS is उठाओd.
		 */
		ucr2 = imx_uart_पढ़ोl(sport, UCR2);
		ucr2 &= ~(UCR2_CTS | UCR2_CTSC);
		अगर (mctrl & TIOCM_RTS) अणु
			ucr2 |= UCR2_CTS;
			/*
			 * UCR2_IRTS is unset अगर and only अगर the port is
			 * configured क्रम CRTSCTS, so we use inverted UCR2_IRTS
			 * to get the state to restore to.
			 */
			अगर (!(ucr2 & UCR2_IRTS))
				ucr2 |= UCR2_CTSC;
		पूर्ण
		imx_uart_ग_लिखोl(sport, ucr2, UCR2);
	पूर्ण

	ucr3 = imx_uart_पढ़ोl(sport, UCR3) & ~UCR3_DSR;
	अगर (!(mctrl & TIOCM_DTR))
		ucr3 |= UCR3_DSR;
	imx_uart_ग_लिखोl(sport, ucr3, UCR3);

	uts = imx_uart_पढ़ोl(sport, imx_uart_uts_reg(sport)) & ~UTS_LOOP;
	अगर (mctrl & TIOCM_LOOP)
		uts |= UTS_LOOP;
	imx_uart_ग_लिखोl(sport, uts, imx_uart_uts_reg(sport));

	mctrl_gpio_set(sport->gpios, mctrl);
पूर्ण

/*
 * Interrupts always disabled.
 */
अटल व्योम imx_uart_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;
	अचिन्हित दीर्घ flags;
	u32 ucr1;

	spin_lock_irqsave(&sport->port.lock, flags);

	ucr1 = imx_uart_पढ़ोl(sport, UCR1) & ~UCR1_SNDBRK;

	अगर (अवरोध_state != 0)
		ucr1 |= UCR1_SNDBRK;

	imx_uart_ग_लिखोl(sport, ucr1, UCR1);

	spin_unlock_irqrestore(&sport->port.lock, flags);
पूर्ण

/*
 * This is our per-port समयout handler, क्रम checking the
 * modem status संकेतs.
 */
अटल व्योम imx_uart_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा imx_port *sport = from_समयr(sport, t, समयr);
	अचिन्हित दीर्घ flags;

	अगर (sport->port.state) अणु
		spin_lock_irqsave(&sport->port.lock, flags);
		imx_uart_mctrl_check(sport);
		spin_unlock_irqrestore(&sport->port.lock, flags);

		mod_समयr(&sport->समयr, jअगरfies + MCTRL_TIMEOUT);
	पूर्ण
पूर्ण

/*
 * There are two kinds of RX DMA पूर्णांकerrupts(such as in the MX6Q):
 *   [1] the RX DMA buffer is full.
 *   [2] the aging समयr expires
 *
 * Condition [2] is triggered when a अक्षरacter has been sitting in the FIFO
 * क्रम at least 8 byte durations.
 */
अटल व्योम imx_uart_dma_rx_callback(व्योम *data)
अणु
	काष्ठा imx_port *sport = data;
	काष्ठा dma_chan	*chan = sport->dma_chan_rx;
	काष्ठा scatterlist *sgl = &sport->rx_sgl;
	काष्ठा tty_port *port = &sport->port.state->port;
	काष्ठा dma_tx_state state;
	काष्ठा circ_buf *rx_ring = &sport->rx_ring;
	क्रमागत dma_status status;
	अचिन्हित पूर्णांक w_bytes = 0;
	अचिन्हित पूर्णांक r_bytes;
	अचिन्हित पूर्णांक bd_size;

	status = dmaengine_tx_status(chan, sport->rx_cookie, &state);

	अगर (status == DMA_ERROR) अणु
		imx_uart_clear_rx_errors(sport);
		वापस;
	पूर्ण

	अगर (!(sport->port.ignore_status_mask & URXD_DUMMY_READ)) अणु

		/*
		 * The state-residue variable represents the empty space
		 * relative to the entire buffer. Taking this in consideration
		 * the head is always calculated base on the buffer total
		 * length - DMA transaction residue. The UART script from the
		 * SDMA firmware will jump to the next buffer descriptor,
		 * once a DMA transaction अगर finalized (IMX53 RM - A.4.1.2.4).
		 * Taking this in consideration the tail is always at the
		 * beginning of the buffer descriptor that contains the head.
		 */

		/* Calculate the head */
		rx_ring->head = sg_dma_len(sgl) - state.residue;

		/* Calculate the tail. */
		bd_size = sg_dma_len(sgl) / sport->rx_periods;
		rx_ring->tail = ((rx_ring->head-1) / bd_size) * bd_size;

		अगर (rx_ring->head <= sg_dma_len(sgl) &&
		    rx_ring->head > rx_ring->tail) अणु

			/* Move data from tail to head */
			r_bytes = rx_ring->head - rx_ring->tail;

			/* CPU claims ownership of RX DMA buffer */
			dma_sync_sg_क्रम_cpu(sport->port.dev, sgl, 1,
				DMA_FROM_DEVICE);

			w_bytes = tty_insert_flip_string(port,
				sport->rx_buf + rx_ring->tail, r_bytes);

			/* UART retrieves ownership of RX DMA buffer */
			dma_sync_sg_क्रम_device(sport->port.dev, sgl, 1,
				DMA_FROM_DEVICE);

			अगर (w_bytes != r_bytes)
				sport->port.icount.buf_overrun++;

			sport->port.icount.rx += w_bytes;
		पूर्ण अन्यथा	अणु
			WARN_ON(rx_ring->head > sg_dma_len(sgl));
			WARN_ON(rx_ring->head <= rx_ring->tail);
		पूर्ण
	पूर्ण

	अगर (w_bytes) अणु
		tty_flip_buffer_push(port);
		dev_dbg(sport->port.dev, "We get %d bytes.\n", w_bytes);
	पूर्ण
पूर्ण

/* RX DMA buffer periods */
#घोषणा RX_DMA_PERIODS	16
#घोषणा RX_BUF_SIZE	(RX_DMA_PERIODS * PAGE_SIZE / 4)

अटल पूर्णांक imx_uart_start_rx_dma(काष्ठा imx_port *sport)
अणु
	काष्ठा scatterlist *sgl = &sport->rx_sgl;
	काष्ठा dma_chan	*chan = sport->dma_chan_rx;
	काष्ठा device *dev = sport->port.dev;
	काष्ठा dma_async_tx_descriptor *desc;
	पूर्णांक ret;

	sport->rx_ring.head = 0;
	sport->rx_ring.tail = 0;
	sport->rx_periods = RX_DMA_PERIODS;

	sg_init_one(sgl, sport->rx_buf, RX_BUF_SIZE);
	ret = dma_map_sg(dev, sgl, 1, DMA_FROM_DEVICE);
	अगर (ret == 0) अणु
		dev_err(dev, "DMA mapping error for RX.\n");
		वापस -EINVAL;
	पूर्ण

	desc = dmaengine_prep_dma_cyclic(chan, sg_dma_address(sgl),
		sg_dma_len(sgl), sg_dma_len(sgl) / sport->rx_periods,
		DMA_DEV_TO_MEM, DMA_PREP_INTERRUPT);

	अगर (!desc) अणु
		dma_unmap_sg(dev, sgl, 1, DMA_FROM_DEVICE);
		dev_err(dev, "We cannot prepare for the RX slave dma!\n");
		वापस -EINVAL;
	पूर्ण
	desc->callback = imx_uart_dma_rx_callback;
	desc->callback_param = sport;

	dev_dbg(dev, "RX: prepare for the DMA.\n");
	sport->dma_is_rxing = 1;
	sport->rx_cookie = dmaengine_submit(desc);
	dma_async_issue_pending(chan);
	वापस 0;
पूर्ण

अटल व्योम imx_uart_clear_rx_errors(काष्ठा imx_port *sport)
अणु
	काष्ठा tty_port *port = &sport->port.state->port;
	u32 usr1, usr2;

	usr1 = imx_uart_पढ़ोl(sport, USR1);
	usr2 = imx_uart_पढ़ोl(sport, USR2);

	अगर (usr2 & USR2_BRCD) अणु
		sport->port.icount.brk++;
		imx_uart_ग_लिखोl(sport, USR2_BRCD, USR2);
		uart_handle_अवरोध(&sport->port);
		अगर (tty_insert_flip_अक्षर(port, 0, TTY_BREAK) == 0)
			sport->port.icount.buf_overrun++;
		tty_flip_buffer_push(port);
	पूर्ण अन्यथा अणु
		अगर (usr1 & USR1_FRAMERR) अणु
			sport->port.icount.frame++;
			imx_uart_ग_लिखोl(sport, USR1_FRAMERR, USR1);
		पूर्ण अन्यथा अगर (usr1 & USR1_PARITYERR) अणु
			sport->port.icount.parity++;
			imx_uart_ग_लिखोl(sport, USR1_PARITYERR, USR1);
		पूर्ण
	पूर्ण

	अगर (usr2 & USR2_ORE) अणु
		sport->port.icount.overrun++;
		imx_uart_ग_लिखोl(sport, USR2_ORE, USR2);
	पूर्ण

पूर्ण

#घोषणा TXTL_DEFAULT 2 /* reset शेष */
#घोषणा RXTL_DEFAULT 1 /* reset शेष */
#घोषणा TXTL_DMA 8 /* DMA burst setting */
#घोषणा RXTL_DMA 9 /* DMA burst setting */

अटल व्योम imx_uart_setup_ufcr(काष्ठा imx_port *sport,
				अचिन्हित अक्षर txwl, अचिन्हित अक्षर rxwl)
अणु
	अचिन्हित पूर्णांक val;

	/* set receiver / transmitter trigger level */
	val = imx_uart_पढ़ोl(sport, UFCR) & (UFCR_RFDIV | UFCR_DCEDTE);
	val |= txwl << UFCR_TXTL_SHF | rxwl;
	imx_uart_ग_लिखोl(sport, val, UFCR);
पूर्ण

अटल व्योम imx_uart_dma_निकास(काष्ठा imx_port *sport)
अणु
	अगर (sport->dma_chan_rx) अणु
		dmaengine_terminate_sync(sport->dma_chan_rx);
		dma_release_channel(sport->dma_chan_rx);
		sport->dma_chan_rx = शून्य;
		sport->rx_cookie = -EINVAL;
		kमुक्त(sport->rx_buf);
		sport->rx_buf = शून्य;
	पूर्ण

	अगर (sport->dma_chan_tx) अणु
		dmaengine_terminate_sync(sport->dma_chan_tx);
		dma_release_channel(sport->dma_chan_tx);
		sport->dma_chan_tx = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक imx_uart_dma_init(काष्ठा imx_port *sport)
अणु
	काष्ठा dma_slave_config slave_config = अणुपूर्ण;
	काष्ठा device *dev = sport->port.dev;
	पूर्णांक ret;

	/* Prepare क्रम RX : */
	sport->dma_chan_rx = dma_request_slave_channel(dev, "rx");
	अगर (!sport->dma_chan_rx) अणु
		dev_dbg(dev, "cannot get the DMA channel.\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	slave_config.direction = DMA_DEV_TO_MEM;
	slave_config.src_addr = sport->port.mapbase + URXD0;
	slave_config.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	/* one byte less than the watermark level to enable the aging समयr */
	slave_config.src_maxburst = RXTL_DMA - 1;
	ret = dmaengine_slave_config(sport->dma_chan_rx, &slave_config);
	अगर (ret) अणु
		dev_err(dev, "error in RX dma configuration.\n");
		जाओ err;
	पूर्ण

	sport->rx_buf = kzalloc(RX_BUF_SIZE, GFP_KERNEL);
	अगर (!sport->rx_buf) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	sport->rx_ring.buf = sport->rx_buf;

	/* Prepare क्रम TX : */
	sport->dma_chan_tx = dma_request_slave_channel(dev, "tx");
	अगर (!sport->dma_chan_tx) अणु
		dev_err(dev, "cannot get the TX DMA channel!\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	slave_config.direction = DMA_MEM_TO_DEV;
	slave_config.dst_addr = sport->port.mapbase + URTX0;
	slave_config.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	slave_config.dst_maxburst = TXTL_DMA;
	ret = dmaengine_slave_config(sport->dma_chan_tx, &slave_config);
	अगर (ret) अणु
		dev_err(dev, "error in TX dma configuration.");
		जाओ err;
	पूर्ण

	वापस 0;
err:
	imx_uart_dma_निकास(sport);
	वापस ret;
पूर्ण

अटल व्योम imx_uart_enable_dma(काष्ठा imx_port *sport)
अणु
	u32 ucr1;

	imx_uart_setup_ufcr(sport, TXTL_DMA, RXTL_DMA);

	/* set UCR1 */
	ucr1 = imx_uart_पढ़ोl(sport, UCR1);
	ucr1 |= UCR1_RXDMAEN | UCR1_TXDMAEN | UCR1_ATDMAEN;
	imx_uart_ग_लिखोl(sport, ucr1, UCR1);

	sport->dma_is_enabled = 1;
पूर्ण

अटल व्योम imx_uart_disable_dma(काष्ठा imx_port *sport)
अणु
	u32 ucr1;

	/* clear UCR1 */
	ucr1 = imx_uart_पढ़ोl(sport, UCR1);
	ucr1 &= ~(UCR1_RXDMAEN | UCR1_TXDMAEN | UCR1_ATDMAEN);
	imx_uart_ग_लिखोl(sport, ucr1, UCR1);

	imx_uart_setup_ufcr(sport, TXTL_DEFAULT, RXTL_DEFAULT);

	sport->dma_is_enabled = 0;
पूर्ण

/* half the RX buffer size */
#घोषणा CTSTL 16

अटल पूर्णांक imx_uart_startup(काष्ठा uart_port *port)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;
	पूर्णांक retval, i;
	अचिन्हित दीर्घ flags;
	पूर्णांक dma_is_inited = 0;
	u32 ucr1, ucr2, ucr3, ucr4;

	retval = clk_prepare_enable(sport->clk_per);
	अगर (retval)
		वापस retval;
	retval = clk_prepare_enable(sport->clk_ipg);
	अगर (retval) अणु
		clk_disable_unprepare(sport->clk_per);
		वापस retval;
	पूर्ण

	imx_uart_setup_ufcr(sport, TXTL_DEFAULT, RXTL_DEFAULT);

	/* disable the DREN bit (Data Ready पूर्णांकerrupt enable) beक्रमe
	 * requesting IRQs
	 */
	ucr4 = imx_uart_पढ़ोl(sport, UCR4);

	/* set the trigger level क्रम CTS */
	ucr4 &= ~(UCR4_CTSTL_MASK << UCR4_CTSTL_SHF);
	ucr4 |= CTSTL << UCR4_CTSTL_SHF;

	imx_uart_ग_लिखोl(sport, ucr4 & ~UCR4_DREN, UCR4);

	/* Can we enable the DMA support? */
	अगर (!uart_console(port) && imx_uart_dma_init(sport) == 0)
		dma_is_inited = 1;

	spin_lock_irqsave(&sport->port.lock, flags);
	/* Reset fअगरo's and state machines */
	i = 100;

	ucr2 = imx_uart_पढ़ोl(sport, UCR2);
	ucr2 &= ~UCR2_SRST;
	imx_uart_ग_लिखोl(sport, ucr2, UCR2);

	जबतक (!(imx_uart_पढ़ोl(sport, UCR2) & UCR2_SRST) && (--i > 0))
		udelay(1);

	/*
	 * Finally, clear and enable पूर्णांकerrupts
	 */
	imx_uart_ग_लिखोl(sport, USR1_RTSD | USR1_DTRD, USR1);
	imx_uart_ग_लिखोl(sport, USR2_ORE, USR2);

	ucr1 = imx_uart_पढ़ोl(sport, UCR1) & ~UCR1_RRDYEN;
	ucr1 |= UCR1_UARTEN;
	अगर (sport->have_rtscts)
		ucr1 |= UCR1_RTSDEN;

	imx_uart_ग_लिखोl(sport, ucr1, UCR1);

	ucr4 = imx_uart_पढ़ोl(sport, UCR4) & ~(UCR4_OREN | UCR4_INVR);
	अगर (!sport->dma_is_enabled)
		ucr4 |= UCR4_OREN;
	अगर (sport->inverted_rx)
		ucr4 |= UCR4_INVR;
	imx_uart_ग_लिखोl(sport, ucr4, UCR4);

	ucr3 = imx_uart_पढ़ोl(sport, UCR3) & ~UCR3_INVT;
	/*
	 * configure tx polarity beक्रमe enabling tx
	 */
	अगर (sport->inverted_tx)
		ucr3 |= UCR3_INVT;

	अगर (!imx_uart_is_imx1(sport)) अणु
		ucr3 |= UCR3_DTRDEN | UCR3_RI | UCR3_DCD;

		अगर (sport->dte_mode)
			/* disable broken पूर्णांकerrupts */
			ucr3 &= ~(UCR3_RI | UCR3_DCD);
	पूर्ण
	imx_uart_ग_लिखोl(sport, ucr3, UCR3);

	ucr2 = imx_uart_पढ़ोl(sport, UCR2) & ~UCR2_ATEN;
	ucr2 |= (UCR2_RXEN | UCR2_TXEN);
	अगर (!sport->have_rtscts)
		ucr2 |= UCR2_IRTS;
	/*
	 * make sure the edge sensitive RTS-irq is disabled,
	 * we're using RTSD instead.
	 */
	अगर (!imx_uart_is_imx1(sport))
		ucr2 &= ~UCR2_RTSEN;
	imx_uart_ग_लिखोl(sport, ucr2, UCR2);

	/*
	 * Enable modem status पूर्णांकerrupts
	 */
	imx_uart_enable_ms(&sport->port);

	अगर (dma_is_inited) अणु
		imx_uart_enable_dma(sport);
		imx_uart_start_rx_dma(sport);
	पूर्ण अन्यथा अणु
		ucr1 = imx_uart_पढ़ोl(sport, UCR1);
		ucr1 |= UCR1_RRDYEN;
		imx_uart_ग_लिखोl(sport, ucr1, UCR1);

		ucr2 = imx_uart_पढ़ोl(sport, UCR2);
		ucr2 |= UCR2_ATEN;
		imx_uart_ग_लिखोl(sport, ucr2, UCR2);
	पूर्ण

	spin_unlock_irqrestore(&sport->port.lock, flags);

	वापस 0;
पूर्ण

अटल व्योम imx_uart_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;
	अचिन्हित दीर्घ flags;
	u32 ucr1, ucr2, ucr4;

	अगर (sport->dma_is_enabled) अणु
		dmaengine_terminate_sync(sport->dma_chan_tx);
		अगर (sport->dma_is_txing) अणु
			dma_unmap_sg(sport->port.dev, &sport->tx_sgl[0],
				     sport->dma_tx_nents, DMA_TO_DEVICE);
			sport->dma_is_txing = 0;
		पूर्ण
		dmaengine_terminate_sync(sport->dma_chan_rx);
		अगर (sport->dma_is_rxing) अणु
			dma_unmap_sg(sport->port.dev, &sport->rx_sgl,
				     1, DMA_FROM_DEVICE);
			sport->dma_is_rxing = 0;
		पूर्ण

		spin_lock_irqsave(&sport->port.lock, flags);
		imx_uart_stop_tx(port);
		imx_uart_stop_rx(port);
		imx_uart_disable_dma(sport);
		spin_unlock_irqrestore(&sport->port.lock, flags);
		imx_uart_dma_निकास(sport);
	पूर्ण

	mctrl_gpio_disable_ms(sport->gpios);

	spin_lock_irqsave(&sport->port.lock, flags);
	ucr2 = imx_uart_पढ़ोl(sport, UCR2);
	ucr2 &= ~(UCR2_TXEN | UCR2_ATEN);
	imx_uart_ग_लिखोl(sport, ucr2, UCR2);
	spin_unlock_irqrestore(&sport->port.lock, flags);

	/*
	 * Stop our समयr.
	 */
	del_समयr_sync(&sport->समयr);

	/*
	 * Disable all पूर्णांकerrupts, port and अवरोध condition.
	 */

	spin_lock_irqsave(&sport->port.lock, flags);

	ucr1 = imx_uart_पढ़ोl(sport, UCR1);
	ucr1 &= ~(UCR1_TRDYEN | UCR1_RRDYEN | UCR1_RTSDEN | UCR1_UARTEN | UCR1_RXDMAEN | UCR1_ATDMAEN);
	imx_uart_ग_लिखोl(sport, ucr1, UCR1);

	ucr4 = imx_uart_पढ़ोl(sport, UCR4);
	ucr4 &= ~(UCR4_OREN | UCR4_TCEN);
	imx_uart_ग_लिखोl(sport, ucr4, UCR4);

	spin_unlock_irqrestore(&sport->port.lock, flags);

	clk_disable_unprepare(sport->clk_per);
	clk_disable_unprepare(sport->clk_ipg);
पूर्ण

/* called with port.lock taken and irqs off */
अटल व्योम imx_uart_flush_buffer(काष्ठा uart_port *port)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;
	काष्ठा scatterlist *sgl = &sport->tx_sgl[0];
	u32 ucr2;
	पूर्णांक i = 100, ubir, ubmr, uts;

	अगर (!sport->dma_chan_tx)
		वापस;

	sport->tx_bytes = 0;
	dmaengine_terminate_all(sport->dma_chan_tx);
	अगर (sport->dma_is_txing) अणु
		u32 ucr1;

		dma_unmap_sg(sport->port.dev, sgl, sport->dma_tx_nents,
			     DMA_TO_DEVICE);
		ucr1 = imx_uart_पढ़ोl(sport, UCR1);
		ucr1 &= ~UCR1_TXDMAEN;
		imx_uart_ग_लिखोl(sport, ucr1, UCR1);
		sport->dma_is_txing = 0;
	पूर्ण

	/*
	 * According to the Reference Manual description of the UART SRST bit:
	 *
	 * "Reset the transmit and receive state machines,
	 * all FIFOs and रेजिस्टर USR1, USR2, UBIR, UBMR, UBRC, URXD, UTXD
	 * and UTS[6-3]".
	 *
	 * We करोn't need to restore the old values from USR1, USR2, URXD and
	 * UTXD. UBRC is पढ़ो only, so only save/restore the other three
	 * रेजिस्टरs.
	 */
	ubir = imx_uart_पढ़ोl(sport, UBIR);
	ubmr = imx_uart_पढ़ोl(sport, UBMR);
	uts = imx_uart_पढ़ोl(sport, IMX21_UTS);

	ucr2 = imx_uart_पढ़ोl(sport, UCR2);
	ucr2 &= ~UCR2_SRST;
	imx_uart_ग_लिखोl(sport, ucr2, UCR2);

	जबतक (!(imx_uart_पढ़ोl(sport, UCR2) & UCR2_SRST) && (--i > 0))
		udelay(1);

	/* Restore the रेजिस्टरs */
	imx_uart_ग_लिखोl(sport, ubir, UBIR);
	imx_uart_ग_लिखोl(sport, ubmr, UBMR);
	imx_uart_ग_लिखोl(sport, uts, IMX21_UTS);
पूर्ण

अटल व्योम
imx_uart_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
		     काष्ठा ktermios *old)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;
	अचिन्हित दीर्घ flags;
	u32 ucr2, old_ucr2, ufcr;
	अचिन्हित पूर्णांक baud, quot;
	अचिन्हित पूर्णांक old_csize = old ? old->c_cflag & CSIZE : CS8;
	अचिन्हित दीर्घ भाग;
	अचिन्हित दीर्घ num, denom, old_ubir, old_ubmr;
	uपूर्णांक64_t tभाग64;

	/*
	 * We only support CS7 and CS8.
	 */
	जबतक ((termios->c_cflag & CSIZE) != CS7 &&
	       (termios->c_cflag & CSIZE) != CS8) अणु
		termios->c_cflag &= ~CSIZE;
		termios->c_cflag |= old_csize;
		old_csize = CS8;
	पूर्ण

	del_समयr_sync(&sport->समयr);

	/*
	 * Ask the core to calculate the भागisor क्रम us.
	 */
	baud = uart_get_baud_rate(port, termios, old, 50, port->uartclk / 16);
	quot = uart_get_भागisor(port, baud);

	spin_lock_irqsave(&sport->port.lock, flags);

	/*
	 * Read current UCR2 and save it क्रम future use, then clear all the bits
	 * except those we will or may need to preserve.
	 */
	old_ucr2 = imx_uart_पढ़ोl(sport, UCR2);
	ucr2 = old_ucr2 & (UCR2_TXEN | UCR2_RXEN | UCR2_ATEN | UCR2_CTS);

	ucr2 |= UCR2_SRST | UCR2_IRTS;
	अगर ((termios->c_cflag & CSIZE) == CS8)
		ucr2 |= UCR2_WS;

	अगर (!sport->have_rtscts)
		termios->c_cflag &= ~CRTSCTS;

	अगर (port->rs485.flags & SER_RS485_ENABLED) अणु
		/*
		 * RTS is mandatory क्रम rs485 operation, so keep
		 * it under manual control and keep transmitter
		 * disabled.
		 */
		अगर (port->rs485.flags & SER_RS485_RTS_AFTER_SEND)
			imx_uart_rts_active(sport, &ucr2);
		अन्यथा
			imx_uart_rts_inactive(sport, &ucr2);

	पूर्ण अन्यथा अगर (termios->c_cflag & CRTSCTS) अणु
		/*
		 * Only let receiver control RTS output अगर we were not requested
		 * to have RTS inactive (which then should take precedence).
		 */
		अगर (ucr2 & UCR2_CTS)
			ucr2 |= UCR2_CTSC;
	पूर्ण

	अगर (termios->c_cflag & CRTSCTS)
		ucr2 &= ~UCR2_IRTS;
	अगर (termios->c_cflag & CSTOPB)
		ucr2 |= UCR2_STPB;
	अगर (termios->c_cflag & PARENB) अणु
		ucr2 |= UCR2_PREN;
		अगर (termios->c_cflag & PARODD)
			ucr2 |= UCR2_PROE;
	पूर्ण

	sport->port.पढ़ो_status_mask = 0;
	अगर (termios->c_अगरlag & INPCK)
		sport->port.पढ़ो_status_mask |= (URXD_FRMERR | URXD_PRERR);
	अगर (termios->c_अगरlag & (BRKINT | PARMRK))
		sport->port.पढ़ो_status_mask |= URXD_BRK;

	/*
	 * Characters to ignore
	 */
	sport->port.ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		sport->port.ignore_status_mask |= URXD_PRERR | URXD_FRMERR;
	अगर (termios->c_अगरlag & IGNBRK) अणु
		sport->port.ignore_status_mask |= URXD_BRK;
		/*
		 * If we're ignoring parity and अवरोध indicators,
		 * ignore overruns too (क्रम real raw support).
		 */
		अगर (termios->c_अगरlag & IGNPAR)
			sport->port.ignore_status_mask |= URXD_OVRRUN;
	पूर्ण

	अगर ((termios->c_cflag & CREAD) == 0)
		sport->port.ignore_status_mask |= URXD_DUMMY_READ;

	/*
	 * Update the per-port समयout.
	 */
	uart_update_समयout(port, termios->c_cflag, baud);

	/* custom-baudrate handling */
	भाग = sport->port.uartclk / (baud * 16);
	अगर (baud == 38400 && quot != भाग)
		baud = sport->port.uartclk / (quot * 16);

	भाग = sport->port.uartclk / (baud * 16);
	अगर (भाग > 7)
		भाग = 7;
	अगर (!भाग)
		भाग = 1;

	rational_best_approximation(16 * भाग * baud, sport->port.uartclk,
		1 << 16, 1 << 16, &num, &denom);

	tभाग64 = sport->port.uartclk;
	tभाग64 *= num;
	करो_भाग(tभाग64, denom * 16 * भाग);
	tty_termios_encode_baud_rate(termios,
				(speed_t)tभाग64, (speed_t)tभाग64);

	num -= 1;
	denom -= 1;

	ufcr = imx_uart_पढ़ोl(sport, UFCR);
	ufcr = (ufcr & (~UFCR_RFDIV)) | UFCR_RFDIV_REG(भाग);
	imx_uart_ग_लिखोl(sport, ufcr, UFCR);

	/*
	 *  Two रेजिस्टरs below should always be written both and in this
	 *  particular order. One consequence is that we need to check अगर any of
	 *  them changes and then update both. We करो need the check क्रम change
	 *  as even writing the same values seem to "restart"
	 *  transmission/receiving logic in the hardware, that leads to data
	 *  अवरोधage even when rate करोesn't in fact change. E.g., user चयनes
	 *  RTS/CTS handshake and suddenly माला_लो broken bytes.
	 */
	old_ubir = imx_uart_पढ़ोl(sport, UBIR);
	old_ubmr = imx_uart_पढ़ोl(sport, UBMR);
	अगर (old_ubir != num || old_ubmr != denom) अणु
		imx_uart_ग_लिखोl(sport, num, UBIR);
		imx_uart_ग_लिखोl(sport, denom, UBMR);
	पूर्ण

	अगर (!imx_uart_is_imx1(sport))
		imx_uart_ग_लिखोl(sport, sport->port.uartclk / भाग / 1000,
				IMX21_ONEMS);

	imx_uart_ग_लिखोl(sport, ucr2, UCR2);

	अगर (UART_ENABLE_MS(&sport->port, termios->c_cflag))
		imx_uart_enable_ms(&sport->port);

	spin_unlock_irqrestore(&sport->port.lock, flags);
पूर्ण

अटल स्थिर अक्षर *imx_uart_type(काष्ठा uart_port *port)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;

	वापस sport->port.type == PORT_IMX ? "IMX" : शून्य;
पूर्ण

/*
 * Configure/स्वतःconfigure the port.
 */
अटल व्योम imx_uart_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;

	अगर (flags & UART_CONFIG_TYPE)
		sport->port.type = PORT_IMX;
पूर्ण

/*
 * Verअगरy the new serial_काष्ठा (क्रम TIOCSSERIAL).
 * The only change we allow are to the flags and type, and
 * even then only between PORT_IMX and PORT_UNKNOWN
 */
अटल पूर्णांक
imx_uart_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;
	पूर्णांक ret = 0;

	अगर (ser->type != PORT_UNKNOWN && ser->type != PORT_IMX)
		ret = -EINVAL;
	अगर (sport->port.irq != ser->irq)
		ret = -EINVAL;
	अगर (ser->io_type != UPIO_MEM)
		ret = -EINVAL;
	अगर (sport->port.uartclk / 16 != ser->baud_base)
		ret = -EINVAL;
	अगर (sport->port.mapbase != (अचिन्हित दीर्घ)ser->iomem_base)
		ret = -EINVAL;
	अगर (sport->port.iobase != ser->port)
		ret = -EINVAL;
	अगर (ser->hub6 != 0)
		ret = -EINVAL;
	वापस ret;
पूर्ण

#अगर defined(CONFIG_CONSOLE_POLL)

अटल पूर्णांक imx_uart_poll_init(काष्ठा uart_port *port)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;
	अचिन्हित दीर्घ flags;
	u32 ucr1, ucr2;
	पूर्णांक retval;

	retval = clk_prepare_enable(sport->clk_ipg);
	अगर (retval)
		वापस retval;
	retval = clk_prepare_enable(sport->clk_per);
	अगर (retval)
		clk_disable_unprepare(sport->clk_ipg);

	imx_uart_setup_ufcr(sport, TXTL_DEFAULT, RXTL_DEFAULT);

	spin_lock_irqsave(&sport->port.lock, flags);

	/*
	 * Be careful about the order of enabling bits here. First enable the
	 * receiver (UARTEN + RXEN) and only then the corresponding irqs.
	 * This prevents that a अक्षरacter that alपढ़ोy sits in the RX fअगरo is
	 * triggering an irq but the try to fetch it from there results in an
	 * exception because UARTEN or RXEN is still off.
	 */
	ucr1 = imx_uart_पढ़ोl(sport, UCR1);
	ucr2 = imx_uart_पढ़ोl(sport, UCR2);

	अगर (imx_uart_is_imx1(sport))
		ucr1 |= IMX1_UCR1_UARTCLKEN;

	ucr1 |= UCR1_UARTEN;
	ucr1 &= ~(UCR1_TRDYEN | UCR1_RTSDEN | UCR1_RRDYEN);

	ucr2 |= UCR2_RXEN | UCR2_TXEN;
	ucr2 &= ~UCR2_ATEN;

	imx_uart_ग_लिखोl(sport, ucr1, UCR1);
	imx_uart_ग_लिखोl(sport, ucr2, UCR2);

	/* now enable irqs */
	imx_uart_ग_लिखोl(sport, ucr1 | UCR1_RRDYEN, UCR1);
	imx_uart_ग_लिखोl(sport, ucr2 | UCR2_ATEN, UCR2);

	spin_unlock_irqrestore(&sport->port.lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_uart_poll_get_अक्षर(काष्ठा uart_port *port)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;
	अगर (!(imx_uart_पढ़ोl(sport, USR2) & USR2_RDR))
		वापस NO_POLL_CHAR;

	वापस imx_uart_पढ़ोl(sport, URXD0) & URXD_RX_DATA;
पूर्ण

अटल व्योम imx_uart_poll_put_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर c)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;
	अचिन्हित पूर्णांक status;

	/* drain */
	करो अणु
		status = imx_uart_पढ़ोl(sport, USR1);
	पूर्ण जबतक (~status & USR1_TRDY);

	/* ग_लिखो */
	imx_uart_ग_लिखोl(sport, c, URTX0);

	/* flush */
	करो अणु
		status = imx_uart_पढ़ोl(sport, USR2);
	पूर्ण जबतक (~status & USR2_TXDC);
पूर्ण
#पूर्ण_अगर

/* called with port.lock taken and irqs off or from .probe without locking */
अटल पूर्णांक imx_uart_rs485_config(काष्ठा uart_port *port,
				 काष्ठा serial_rs485 *rs485conf)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;
	u32 ucr2;

	/* RTS is required to control the transmitter */
	अगर (!sport->have_rtscts && !sport->have_rtsgpio)
		rs485conf->flags &= ~SER_RS485_ENABLED;

	अगर (rs485conf->flags & SER_RS485_ENABLED) अणु
		/* Enable receiver अगर low-active RTS संकेत is requested */
		अगर (sport->have_rtscts &&  !sport->have_rtsgpio &&
		    !(rs485conf->flags & SER_RS485_RTS_ON_SEND))
			rs485conf->flags |= SER_RS485_RX_DURING_TX;

		/* disable transmitter */
		ucr2 = imx_uart_पढ़ोl(sport, UCR2);
		अगर (rs485conf->flags & SER_RS485_RTS_AFTER_SEND)
			imx_uart_rts_active(sport, &ucr2);
		अन्यथा
			imx_uart_rts_inactive(sport, &ucr2);
		imx_uart_ग_लिखोl(sport, ucr2, UCR2);
	पूर्ण

	/* Make sure Rx is enabled in हाल Tx is active with Rx disabled */
	अगर (!(rs485conf->flags & SER_RS485_ENABLED) ||
	    rs485conf->flags & SER_RS485_RX_DURING_TX)
		imx_uart_start_rx(port);

	port->rs485 = *rs485conf;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा uart_ops imx_uart_pops = अणु
	.tx_empty	= imx_uart_tx_empty,
	.set_mctrl	= imx_uart_set_mctrl,
	.get_mctrl	= imx_uart_get_mctrl,
	.stop_tx	= imx_uart_stop_tx,
	.start_tx	= imx_uart_start_tx,
	.stop_rx	= imx_uart_stop_rx,
	.enable_ms	= imx_uart_enable_ms,
	.अवरोध_ctl	= imx_uart_अवरोध_ctl,
	.startup	= imx_uart_startup,
	.shutकरोwn	= imx_uart_shutकरोwn,
	.flush_buffer	= imx_uart_flush_buffer,
	.set_termios	= imx_uart_set_termios,
	.type		= imx_uart_type,
	.config_port	= imx_uart_config_port,
	.verअगरy_port	= imx_uart_verअगरy_port,
#अगर defined(CONFIG_CONSOLE_POLL)
	.poll_init      = imx_uart_poll_init,
	.poll_get_अक्षर  = imx_uart_poll_get_अक्षर,
	.poll_put_अक्षर  = imx_uart_poll_put_अक्षर,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा imx_port *imx_uart_ports[UART_NR];

#अगर IS_ENABLED(CONFIG_SERIAL_IMX_CONSOLE)
अटल व्योम imx_uart_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	काष्ठा imx_port *sport = (काष्ठा imx_port *)port;

	जबतक (imx_uart_पढ़ोl(sport, imx_uart_uts_reg(sport)) & UTS_TXFULL)
		barrier();

	imx_uart_ग_लिखोl(sport, ch, URTX0);
पूर्ण

/*
 * Interrupts are disabled on entering
 */
अटल व्योम
imx_uart_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, अचिन्हित पूर्णांक count)
अणु
	काष्ठा imx_port *sport = imx_uart_ports[co->index];
	काष्ठा imx_port_ucrs old_ucr;
	अचिन्हित पूर्णांक ucr1;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक locked = 1;

	अगर (sport->port.sysrq)
		locked = 0;
	अन्यथा अगर (oops_in_progress)
		locked = spin_trylock_irqsave(&sport->port.lock, flags);
	अन्यथा
		spin_lock_irqsave(&sport->port.lock, flags);

	/*
	 *	First, save UCR1/2/3 and then disable पूर्णांकerrupts
	 */
	imx_uart_ucrs_save(sport, &old_ucr);
	ucr1 = old_ucr.ucr1;

	अगर (imx_uart_is_imx1(sport))
		ucr1 |= IMX1_UCR1_UARTCLKEN;
	ucr1 |= UCR1_UARTEN;
	ucr1 &= ~(UCR1_TRDYEN | UCR1_RRDYEN | UCR1_RTSDEN);

	imx_uart_ग_लिखोl(sport, ucr1, UCR1);

	imx_uart_ग_लिखोl(sport, old_ucr.ucr2 | UCR2_TXEN, UCR2);

	uart_console_ग_लिखो(&sport->port, s, count, imx_uart_console_अक्षर_दो);

	/*
	 *	Finally, रुको क्रम transmitter to become empty
	 *	and restore UCR1/2/3
	 */
	जबतक (!(imx_uart_पढ़ोl(sport, USR2) & USR2_TXDC));

	imx_uart_ucrs_restore(sport, &old_ucr);

	अगर (locked)
		spin_unlock_irqrestore(&sport->port.lock, flags);
पूर्ण

/*
 * If the port was alपढ़ोy initialised (eg, by a boot loader),
 * try to determine the current setup.
 */
अटल व्योम __init
imx_uart_console_get_options(काष्ठा imx_port *sport, पूर्णांक *baud,
			     पूर्णांक *parity, पूर्णांक *bits)
अणु

	अगर (imx_uart_पढ़ोl(sport, UCR1) & UCR1_UARTEN) अणु
		/* ok, the port was enabled */
		अचिन्हित पूर्णांक ucr2, ubir, ubmr, uartclk;
		अचिन्हित पूर्णांक baud_raw;
		अचिन्हित पूर्णांक ucfr_rfभाग;

		ucr2 = imx_uart_पढ़ोl(sport, UCR2);

		*parity = 'n';
		अगर (ucr2 & UCR2_PREN) अणु
			अगर (ucr2 & UCR2_PROE)
				*parity = 'o';
			अन्यथा
				*parity = 'e';
		पूर्ण

		अगर (ucr2 & UCR2_WS)
			*bits = 8;
		अन्यथा
			*bits = 7;

		ubir = imx_uart_पढ़ोl(sport, UBIR) & 0xffff;
		ubmr = imx_uart_पढ़ोl(sport, UBMR) & 0xffff;

		ucfr_rfभाग = (imx_uart_पढ़ोl(sport, UFCR) & UFCR_RFDIV) >> 7;
		अगर (ucfr_rfभाग == 6)
			ucfr_rfभाग = 7;
		अन्यथा
			ucfr_rfभाग = 6 - ucfr_rfभाग;

		uartclk = clk_get_rate(sport->clk_per);
		uartclk /= ucfr_rfभाग;

		अणु	/*
			 * The next code provides exact computation of
			 *   baud_raw = round(((uartclk/16) * (ubir + 1)) / (ubmr + 1))
			 * without need of भग्न support or दीर्घ दीर्घ भागision,
			 * which would be required to prevent 32bit arithmetic overflow
			 */
			अचिन्हित पूर्णांक mul = ubir + 1;
			अचिन्हित पूर्णांक भाग = 16 * (ubmr + 1);
			अचिन्हित पूर्णांक rem = uartclk % भाग;

			baud_raw = (uartclk / भाग) * mul;
			baud_raw += (rem * mul + भाग / 2) / भाग;
			*baud = (baud_raw + 50) / 100 * 100;
		पूर्ण

		अगर (*baud != baud_raw)
			dev_info(sport->port.dev, "Console IMX rounded baud rate from %d to %d\n",
				baud_raw, *baud);
	पूर्ण
पूर्ण

अटल पूर्णांक __init
imx_uart_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा imx_port *sport;
	पूर्णांक baud = 9600;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';
	पूर्णांक retval;

	/*
	 * Check whether an invalid uart number has been specअगरied, and
	 * अगर so, search क्रम the first available port that करोes have
	 * console support.
	 */
	अगर (co->index == -1 || co->index >= ARRAY_SIZE(imx_uart_ports))
		co->index = 0;
	sport = imx_uart_ports[co->index];
	अगर (sport == शून्य)
		वापस -ENODEV;

	/* For setting the रेजिस्टरs, we only need to enable the ipg घड़ी. */
	retval = clk_prepare_enable(sport->clk_ipg);
	अगर (retval)
		जाओ error_console;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	अन्यथा
		imx_uart_console_get_options(sport, &baud, &parity, &bits);

	imx_uart_setup_ufcr(sport, TXTL_DEFAULT, RXTL_DEFAULT);

	retval = uart_set_options(&sport->port, co, baud, parity, bits, flow);

	अगर (retval) अणु
		clk_disable_unprepare(sport->clk_ipg);
		जाओ error_console;
	पूर्ण

	retval = clk_prepare_enable(sport->clk_per);
	अगर (retval)
		clk_disable_unprepare(sport->clk_ipg);

error_console:
	वापस retval;
पूर्ण

अटल काष्ठा uart_driver imx_uart_uart_driver;
अटल काष्ठा console imx_uart_console = अणु
	.name		= DEV_NAME,
	.ग_लिखो		= imx_uart_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= imx_uart_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &imx_uart_uart_driver,
पूर्ण;

#घोषणा IMX_CONSOLE	&imx_uart_console

#अन्यथा
#घोषणा IMX_CONSOLE	शून्य
#पूर्ण_अगर

अटल काष्ठा uart_driver imx_uart_uart_driver = अणु
	.owner          = THIS_MODULE,
	.driver_name    = DRIVER_NAME,
	.dev_name       = DEV_NAME,
	.major          = SERIAL_IMX_MAJOR,
	.minor          = MINOR_START,
	.nr             = ARRAY_SIZE(imx_uart_ports),
	.cons           = IMX_CONSOLE,
पूर्ण;

अटल क्रमागत hrसमयr_restart imx_trigger_start_tx(काष्ठा hrसमयr *t)
अणु
	काष्ठा imx_port *sport = container_of(t, काष्ठा imx_port, trigger_start_tx);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sport->port.lock, flags);
	अगर (sport->tx_state == WAIT_AFTER_RTS)
		imx_uart_start_tx(&sport->port);
	spin_unlock_irqrestore(&sport->port.lock, flags);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल क्रमागत hrसमयr_restart imx_trigger_stop_tx(काष्ठा hrसमयr *t)
अणु
	काष्ठा imx_port *sport = container_of(t, काष्ठा imx_port, trigger_stop_tx);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sport->port.lock, flags);
	अगर (sport->tx_state == WAIT_AFTER_SEND)
		imx_uart_stop_tx(&sport->port);
	spin_unlock_irqrestore(&sport->port.lock, flags);

	वापस HRTIMER_NORESTART;
पूर्ण

अटल पूर्णांक imx_uart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा imx_port *sport;
	व्योम __iomem *base;
	पूर्णांक ret = 0;
	u32 ucr1;
	काष्ठा resource *res;
	पूर्णांक txirq, rxirq, rtsirq;

	sport = devm_kzalloc(&pdev->dev, माप(*sport), GFP_KERNEL);
	अगर (!sport)
		वापस -ENOMEM;

	sport->devdata = of_device_get_match_data(&pdev->dev);

	ret = of_alias_get_id(np, "serial");
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to get alias id, errno %d\n", ret);
		वापस ret;
	पूर्ण
	sport->port.line = ret;

	अगर (of_get_property(np, "uart-has-rtscts", शून्य) ||
	    of_get_property(np, "fsl,uart-has-rtscts", शून्य) /* deprecated */)
		sport->have_rtscts = 1;

	अगर (of_get_property(np, "fsl,dte-mode", शून्य))
		sport->dte_mode = 1;

	अगर (of_get_property(np, "rts-gpios", शून्य))
		sport->have_rtsgpio = 1;

	अगर (of_get_property(np, "fsl,inverted-tx", शून्य))
		sport->inverted_tx = 1;

	अगर (of_get_property(np, "fsl,inverted-rx", शून्य))
		sport->inverted_rx = 1;

	अगर (sport->port.line >= ARRAY_SIZE(imx_uart_ports)) अणु
		dev_err(&pdev->dev, "serial%d out of range\n",
			sport->port.line);
		वापस -EINVAL;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	rxirq = platक्रमm_get_irq(pdev, 0);
	अगर (rxirq < 0)
		वापस rxirq;
	txirq = platक्रमm_get_irq_optional(pdev, 1);
	rtsirq = platक्रमm_get_irq_optional(pdev, 2);

	sport->port.dev = &pdev->dev;
	sport->port.mapbase = res->start;
	sport->port.membase = base;
	sport->port.type = PORT_IMX;
	sport->port.iotype = UPIO_MEM;
	sport->port.irq = rxirq;
	sport->port.fअगरosize = 32;
	sport->port.has_sysrq = IS_ENABLED(CONFIG_SERIAL_IMX_CONSOLE);
	sport->port.ops = &imx_uart_pops;
	sport->port.rs485_config = imx_uart_rs485_config;
	sport->port.flags = UPF_BOOT_AUTOCONF;
	समयr_setup(&sport->समयr, imx_uart_समयout, 0);

	sport->gpios = mctrl_gpio_init(&sport->port, 0);
	अगर (IS_ERR(sport->gpios))
		वापस PTR_ERR(sport->gpios);

	sport->clk_ipg = devm_clk_get(&pdev->dev, "ipg");
	अगर (IS_ERR(sport->clk_ipg)) अणु
		ret = PTR_ERR(sport->clk_ipg);
		dev_err(&pdev->dev, "failed to get ipg clk: %d\n", ret);
		वापस ret;
	पूर्ण

	sport->clk_per = devm_clk_get(&pdev->dev, "per");
	अगर (IS_ERR(sport->clk_per)) अणु
		ret = PTR_ERR(sport->clk_per);
		dev_err(&pdev->dev, "failed to get per clk: %d\n", ret);
		वापस ret;
	पूर्ण

	sport->port.uartclk = clk_get_rate(sport->clk_per);

	/* For रेजिस्टर access, we only need to enable the ipg घड़ी. */
	ret = clk_prepare_enable(sport->clk_ipg);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable per clk: %d\n", ret);
		वापस ret;
	पूर्ण

	/* initialize shaकरोw रेजिस्टर values */
	sport->ucr1 = पढ़ोl(sport->port.membase + UCR1);
	sport->ucr2 = पढ़ोl(sport->port.membase + UCR2);
	sport->ucr3 = पढ़ोl(sport->port.membase + UCR3);
	sport->ucr4 = पढ़ोl(sport->port.membase + UCR4);
	sport->ufcr = पढ़ोl(sport->port.membase + UFCR);

	ret = uart_get_rs485_mode(&sport->port);
	अगर (ret) अणु
		clk_disable_unprepare(sport->clk_ipg);
		वापस ret;
	पूर्ण

	अगर (sport->port.rs485.flags & SER_RS485_ENABLED &&
	    (!sport->have_rtscts && !sport->have_rtsgpio))
		dev_err(&pdev->dev, "no RTS control, disabling rs485\n");

	/*
	 * If using the i.MX UART RTS/CTS control then the RTS (CTS_B)
	 * संकेत cannot be set low during transmission in हाल the
	 * receiver is off (limitation of the i.MX UART IP).
	 */
	अगर (sport->port.rs485.flags & SER_RS485_ENABLED &&
	    sport->have_rtscts && !sport->have_rtsgpio &&
	    (!(sport->port.rs485.flags & SER_RS485_RTS_ON_SEND) &&
	     !(sport->port.rs485.flags & SER_RS485_RX_DURING_TX)))
		dev_err(&pdev->dev,
			"low-active RTS not possible when receiver is off, enabling receiver\n");

	imx_uart_rs485_config(&sport->port, &sport->port.rs485);

	/* Disable पूर्णांकerrupts beक्रमe requesting them */
	ucr1 = imx_uart_पढ़ोl(sport, UCR1);
	ucr1 &= ~(UCR1_ADEN | UCR1_TRDYEN | UCR1_IDEN | UCR1_RRDYEN | UCR1_RTSDEN);
	imx_uart_ग_लिखोl(sport, ucr1, UCR1);

	अगर (!imx_uart_is_imx1(sport) && sport->dte_mode) अणु
		/*
		 * The DCEDTE bit changes the direction of DSR, DCD, DTR and RI
		 * and influences अगर UCR3_RI and UCR3_DCD changes the level of RI
		 * and DCD (when they are outमाला_दो) or enables the respective
		 * irqs. So set this bit early, i.e. beक्रमe requesting irqs.
		 */
		u32 ufcr = imx_uart_पढ़ोl(sport, UFCR);
		अगर (!(ufcr & UFCR_DCEDTE))
			imx_uart_ग_लिखोl(sport, ufcr | UFCR_DCEDTE, UFCR);

		/*
		 * Disable UCR3_RI and UCR3_DCD irqs. They are also not
		 * enabled later because they cannot be cleared
		 * (confirmed on i.MX25) which makes them unusable.
		 */
		imx_uart_ग_लिखोl(sport,
				IMX21_UCR3_RXDMUXSEL | UCR3_ADNIMP | UCR3_DSR,
				UCR3);

	पूर्ण अन्यथा अणु
		u32 ucr3 = UCR3_DSR;
		u32 ufcr = imx_uart_पढ़ोl(sport, UFCR);
		अगर (ufcr & UFCR_DCEDTE)
			imx_uart_ग_लिखोl(sport, ufcr & ~UFCR_DCEDTE, UFCR);

		अगर (!imx_uart_is_imx1(sport))
			ucr3 |= IMX21_UCR3_RXDMUXSEL | UCR3_ADNIMP;
		imx_uart_ग_लिखोl(sport, ucr3, UCR3);
	पूर्ण

	clk_disable_unprepare(sport->clk_ipg);

	hrसमयr_init(&sport->trigger_start_tx, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	hrसमयr_init(&sport->trigger_stop_tx, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	sport->trigger_start_tx.function = imx_trigger_start_tx;
	sport->trigger_stop_tx.function = imx_trigger_stop_tx;

	/*
	 * Allocate the IRQ(s) i.MX1 has three पूर्णांकerrupts whereas later
	 * chips only have one पूर्णांकerrupt.
	 */
	अगर (txirq > 0) अणु
		ret = devm_request_irq(&pdev->dev, rxirq, imx_uart_rxपूर्णांक, 0,
				       dev_name(&pdev->dev), sport);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to request rx irq: %d\n",
				ret);
			वापस ret;
		पूर्ण

		ret = devm_request_irq(&pdev->dev, txirq, imx_uart_txपूर्णांक, 0,
				       dev_name(&pdev->dev), sport);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to request tx irq: %d\n",
				ret);
			वापस ret;
		पूर्ण

		ret = devm_request_irq(&pdev->dev, rtsirq, imx_uart_rtsपूर्णांक, 0,
				       dev_name(&pdev->dev), sport);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to request rts irq: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = devm_request_irq(&pdev->dev, rxirq, imx_uart_पूर्णांक, 0,
				       dev_name(&pdev->dev), sport);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to request irq: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	imx_uart_ports[sport->port.line] = sport;

	platक्रमm_set_drvdata(pdev, sport);

	वापस uart_add_one_port(&imx_uart_uart_driver, &sport->port);
पूर्ण

अटल पूर्णांक imx_uart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_port *sport = platक्रमm_get_drvdata(pdev);

	वापस uart_हटाओ_one_port(&imx_uart_uart_driver, &sport->port);
पूर्ण

अटल व्योम imx_uart_restore_context(काष्ठा imx_port *sport)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sport->port.lock, flags);
	अगर (!sport->context_saved) अणु
		spin_unlock_irqrestore(&sport->port.lock, flags);
		वापस;
	पूर्ण

	imx_uart_ग_लिखोl(sport, sport->saved_reg[4], UFCR);
	imx_uart_ग_लिखोl(sport, sport->saved_reg[5], UESC);
	imx_uart_ग_लिखोl(sport, sport->saved_reg[6], UTIM);
	imx_uart_ग_लिखोl(sport, sport->saved_reg[7], UBIR);
	imx_uart_ग_लिखोl(sport, sport->saved_reg[8], UBMR);
	imx_uart_ग_लिखोl(sport, sport->saved_reg[9], IMX21_UTS);
	imx_uart_ग_लिखोl(sport, sport->saved_reg[0], UCR1);
	imx_uart_ग_लिखोl(sport, sport->saved_reg[1] | UCR2_SRST, UCR2);
	imx_uart_ग_लिखोl(sport, sport->saved_reg[2], UCR3);
	imx_uart_ग_लिखोl(sport, sport->saved_reg[3], UCR4);
	sport->context_saved = false;
	spin_unlock_irqrestore(&sport->port.lock, flags);
पूर्ण

अटल व्योम imx_uart_save_context(काष्ठा imx_port *sport)
अणु
	अचिन्हित दीर्घ flags;

	/* Save necessary regs */
	spin_lock_irqsave(&sport->port.lock, flags);
	sport->saved_reg[0] = imx_uart_पढ़ोl(sport, UCR1);
	sport->saved_reg[1] = imx_uart_पढ़ोl(sport, UCR2);
	sport->saved_reg[2] = imx_uart_पढ़ोl(sport, UCR3);
	sport->saved_reg[3] = imx_uart_पढ़ोl(sport, UCR4);
	sport->saved_reg[4] = imx_uart_पढ़ोl(sport, UFCR);
	sport->saved_reg[5] = imx_uart_पढ़ोl(sport, UESC);
	sport->saved_reg[6] = imx_uart_पढ़ोl(sport, UTIM);
	sport->saved_reg[7] = imx_uart_पढ़ोl(sport, UBIR);
	sport->saved_reg[8] = imx_uart_पढ़ोl(sport, UBMR);
	sport->saved_reg[9] = imx_uart_पढ़ोl(sport, IMX21_UTS);
	sport->context_saved = true;
	spin_unlock_irqrestore(&sport->port.lock, flags);
पूर्ण

अटल व्योम imx_uart_enable_wakeup(काष्ठा imx_port *sport, bool on)
अणु
	u32 ucr3;

	ucr3 = imx_uart_पढ़ोl(sport, UCR3);
	अगर (on) अणु
		imx_uart_ग_लिखोl(sport, USR1_AWAKE, USR1);
		ucr3 |= UCR3_AWAKEN;
	पूर्ण अन्यथा अणु
		ucr3 &= ~UCR3_AWAKEN;
	पूर्ण
	imx_uart_ग_लिखोl(sport, ucr3, UCR3);

	अगर (sport->have_rtscts) अणु
		u32 ucr1 = imx_uart_पढ़ोl(sport, UCR1);
		अगर (on)
			ucr1 |= UCR1_RTSDEN;
		अन्यथा
			ucr1 &= ~UCR1_RTSDEN;
		imx_uart_ग_लिखोl(sport, ucr1, UCR1);
	पूर्ण
पूर्ण

अटल पूर्णांक imx_uart_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा imx_port *sport = dev_get_drvdata(dev);

	imx_uart_save_context(sport);

	clk_disable(sport->clk_ipg);

	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_uart_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा imx_port *sport = dev_get_drvdata(dev);
	पूर्णांक ret;

	pinctrl_pm_select_शेष_state(dev);

	ret = clk_enable(sport->clk_ipg);
	अगर (ret)
		वापस ret;

	imx_uart_restore_context(sport);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_uart_suspend(काष्ठा device *dev)
अणु
	काष्ठा imx_port *sport = dev_get_drvdata(dev);
	पूर्णांक ret;

	uart_suspend_port(&imx_uart_uart_driver, &sport->port);
	disable_irq(sport->port.irq);

	ret = clk_prepare_enable(sport->clk_ipg);
	अगर (ret)
		वापस ret;

	/* enable wakeup from i.MX UART */
	imx_uart_enable_wakeup(sport, true);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_uart_resume(काष्ठा device *dev)
अणु
	काष्ठा imx_port *sport = dev_get_drvdata(dev);

	/* disable wakeup from i.MX UART */
	imx_uart_enable_wakeup(sport, false);

	uart_resume_port(&imx_uart_uart_driver, &sport->port);
	enable_irq(sport->port.irq);

	clk_disable_unprepare(sport->clk_ipg);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_uart_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा imx_port *sport = dev_get_drvdata(dev);

	uart_suspend_port(&imx_uart_uart_driver, &sport->port);

	वापस clk_prepare_enable(sport->clk_ipg);
पूर्ण

अटल पूर्णांक imx_uart_thaw(काष्ठा device *dev)
अणु
	काष्ठा imx_port *sport = dev_get_drvdata(dev);

	uart_resume_port(&imx_uart_uart_driver, &sport->port);

	clk_disable_unprepare(sport->clk_ipg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops imx_uart_pm_ops = अणु
	.suspend_noirq = imx_uart_suspend_noirq,
	.resume_noirq = imx_uart_resume_noirq,
	.मुक्तze_noirq = imx_uart_suspend_noirq,
	.restore_noirq = imx_uart_resume_noirq,
	.suspend = imx_uart_suspend,
	.resume = imx_uart_resume,
	.मुक्तze = imx_uart_मुक्तze,
	.thaw = imx_uart_thaw,
	.restore = imx_uart_thaw,
पूर्ण;

अटल काष्ठा platक्रमm_driver imx_uart_platक्रमm_driver = अणु
	.probe = imx_uart_probe,
	.हटाओ = imx_uart_हटाओ,

	.driver = अणु
		.name = "imx-uart",
		.of_match_table = imx_uart_dt_ids,
		.pm = &imx_uart_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init imx_uart_init(व्योम)
अणु
	पूर्णांक ret = uart_रेजिस्टर_driver(&imx_uart_uart_driver);

	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&imx_uart_platक्रमm_driver);
	अगर (ret != 0)
		uart_unरेजिस्टर_driver(&imx_uart_uart_driver);

	वापस ret;
पूर्ण

अटल व्योम __निकास imx_uart_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&imx_uart_platक्रमm_driver);
	uart_unरेजिस्टर_driver(&imx_uart_uart_driver);
पूर्ण

module_init(imx_uart_init);
module_निकास(imx_uart_निकास);

MODULE_AUTHOR("Sascha Hauer");
MODULE_DESCRIPTION("IMX generic serial port driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:imx-uart");
