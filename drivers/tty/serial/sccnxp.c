<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  NXP (Philips) SCC+++(SCN+++) serial driver
 *
 *  Copyright (C) 2012 Alexander Shiyan <shc_work@mail.ru>
 *
 *  Based on sc26xx.c, by Thomas Bogendथघrfer (tsbogend@alpha.franken.de)
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/device.h>
#समावेश <linux/console.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial.h>
#समावेश <linux/पन.स>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/serial-sccnxp.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा SCCNXP_NAME			"uart-sccnxp"
#घोषणा SCCNXP_MAJOR			204
#घोषणा SCCNXP_MINOR			205

#घोषणा SCCNXP_MR_REG			(0x00)
#	define MR0_BAUD_NORMAL		(0 << 0)
#	define MR0_BAUD_EXT1		(1 << 0)
#	define MR0_BAUD_EXT2		(5 << 0)
#	define MR0_FIFO			(1 << 3)
#	define MR0_TXLVL		(1 << 4)
#	define MR1_BITS_5		(0 << 0)
#	define MR1_BITS_6		(1 << 0)
#	define MR1_BITS_7		(2 << 0)
#	define MR1_BITS_8		(3 << 0)
#	define MR1_PAR_EVN		(0 << 2)
#	define MR1_PAR_ODD		(1 << 2)
#	define MR1_PAR_NO		(4 << 2)
#	define MR2_STOP1		(7 << 0)
#	define MR2_STOP2		(0xf << 0)
#घोषणा SCCNXP_SR_REG			(0x01)
#	define SR_RXRDY			(1 << 0)
#	define SR_FULL			(1 << 1)
#	define SR_TXRDY			(1 << 2)
#	define SR_TXEMT			(1 << 3)
#	define SR_OVR			(1 << 4)
#	define SR_PE			(1 << 5)
#	define SR_FE			(1 << 6)
#	define SR_BRK			(1 << 7)
#घोषणा SCCNXP_CSR_REG			(SCCNXP_SR_REG)
#	define CSR_TIMER_MODE		(0x0d)
#घोषणा SCCNXP_CR_REG			(0x02)
#	define CR_RX_ENABLE		(1 << 0)
#	define CR_RX_DISABLE		(1 << 1)
#	define CR_TX_ENABLE		(1 << 2)
#	define CR_TX_DISABLE		(1 << 3)
#	define CR_CMD_MRPTR1		(0x01 << 4)
#	define CR_CMD_RX_RESET		(0x02 << 4)
#	define CR_CMD_TX_RESET		(0x03 << 4)
#	define CR_CMD_STATUS_RESET	(0x04 << 4)
#	define CR_CMD_BREAK_RESET	(0x05 << 4)
#	define CR_CMD_START_BREAK	(0x06 << 4)
#	define CR_CMD_STOP_BREAK	(0x07 << 4)
#	define CR_CMD_MRPTR0		(0x0b << 4)
#घोषणा SCCNXP_RHR_REG			(0x03)
#घोषणा SCCNXP_THR_REG			SCCNXP_RHR_REG
#घोषणा SCCNXP_IPCR_REG			(0x04)
#घोषणा SCCNXP_ACR_REG			SCCNXP_IPCR_REG
#	define ACR_BAUD0		(0 << 7)
#	define ACR_BAUD1		(1 << 7)
#	define ACR_TIMER_MODE		(6 << 4)
#घोषणा SCCNXP_ISR_REG			(0x05)
#घोषणा SCCNXP_IMR_REG			SCCNXP_ISR_REG
#	define IMR_TXRDY		(1 << 0)
#	define IMR_RXRDY		(1 << 1)
#	define ISR_TXRDY(x)		(1 << ((x * 4) + 0))
#	define ISR_RXRDY(x)		(1 << ((x * 4) + 1))
#घोषणा SCCNXP_CTPU_REG			(0x06)
#घोषणा SCCNXP_CTPL_REG			(0x07)
#घोषणा SCCNXP_IPR_REG			(0x0d)
#घोषणा SCCNXP_OPCR_REG			SCCNXP_IPR_REG
#घोषणा SCCNXP_SOP_REG			(0x0e)
#घोषणा SCCNXP_START_COUNTER_REG	SCCNXP_SOP_REG
#घोषणा SCCNXP_ROP_REG			(0x0f)

/* Route helpers */
#घोषणा MCTRL_MASK(sig)			(0xf << (sig))
#घोषणा MCTRL_IBIT(cfg, sig)		((((cfg) >> (sig)) & 0xf) - LINE_IP0)
#घोषणा MCTRL_OBIT(cfg, sig)		((((cfg) >> (sig)) & 0xf) - LINE_OP0)

#घोषणा SCCNXP_HAVE_IO		0x00000001
#घोषणा SCCNXP_HAVE_MR0		0x00000002

काष्ठा sccnxp_chip अणु
	स्थिर अक्षर		*name;
	अचिन्हित पूर्णांक		nr;
	अचिन्हित दीर्घ		freq_min;
	अचिन्हित दीर्घ		freq_std;
	अचिन्हित दीर्घ		freq_max;
	अचिन्हित पूर्णांक		flags;
	अचिन्हित पूर्णांक		fअगरosize;
	/* Time between पढ़ो/ग_लिखो cycles */
	अचिन्हित पूर्णांक		trwd;
पूर्ण;

काष्ठा sccnxp_port अणु
	काष्ठा uart_driver	uart;
	काष्ठा uart_port	port[SCCNXP_MAX_UARTS];
	bool			खोलोed[SCCNXP_MAX_UARTS];

	पूर्णांक			irq;
	u8			imr;

	काष्ठा sccnxp_chip	*chip;

#अगर_घोषित CONFIG_SERIAL_SCCNXP_CONSOLE
	काष्ठा console		console;
#पूर्ण_अगर

	spinlock_t		lock;

	bool			poll;
	काष्ठा समयr_list	समयr;

	काष्ठा sccnxp_pdata	pdata;

	काष्ठा regulator	*regulator;
पूर्ण;

अटल स्थिर काष्ठा sccnxp_chip sc2681 = अणु
	.name		= "SC2681",
	.nr		= 2,
	.freq_min	= 1000000,
	.freq_std	= 3686400,
	.freq_max	= 4000000,
	.flags		= SCCNXP_HAVE_IO,
	.fअगरosize	= 3,
	.trwd		= 200,
पूर्ण;

अटल स्थिर काष्ठा sccnxp_chip sc2691 = अणु
	.name		= "SC2691",
	.nr		= 1,
	.freq_min	= 1000000,
	.freq_std	= 3686400,
	.freq_max	= 4000000,
	.flags		= 0,
	.fअगरosize	= 3,
	.trwd		= 150,
पूर्ण;

अटल स्थिर काष्ठा sccnxp_chip sc2692 = अणु
	.name		= "SC2692",
	.nr		= 2,
	.freq_min	= 1000000,
	.freq_std	= 3686400,
	.freq_max	= 4000000,
	.flags		= SCCNXP_HAVE_IO,
	.fअगरosize	= 3,
	.trwd		= 30,
पूर्ण;

अटल स्थिर काष्ठा sccnxp_chip sc2891 = अणु
	.name		= "SC2891",
	.nr		= 1,
	.freq_min	= 100000,
	.freq_std	= 3686400,
	.freq_max	= 8000000,
	.flags		= SCCNXP_HAVE_IO | SCCNXP_HAVE_MR0,
	.fअगरosize	= 16,
	.trwd		= 27,
पूर्ण;

अटल स्थिर काष्ठा sccnxp_chip sc2892 = अणु
	.name		= "SC2892",
	.nr		= 2,
	.freq_min	= 100000,
	.freq_std	= 3686400,
	.freq_max	= 8000000,
	.flags		= SCCNXP_HAVE_IO | SCCNXP_HAVE_MR0,
	.fअगरosize	= 16,
	.trwd		= 17,
पूर्ण;

अटल स्थिर काष्ठा sccnxp_chip sc28202 = अणु
	.name		= "SC28202",
	.nr		= 2,
	.freq_min	= 1000000,
	.freq_std	= 14745600,
	.freq_max	= 50000000,
	.flags		= SCCNXP_HAVE_IO | SCCNXP_HAVE_MR0,
	.fअगरosize	= 256,
	.trwd		= 10,
पूर्ण;

अटल स्थिर काष्ठा sccnxp_chip sc68681 = अणु
	.name		= "SC68681",
	.nr		= 2,
	.freq_min	= 1000000,
	.freq_std	= 3686400,
	.freq_max	= 4000000,
	.flags		= SCCNXP_HAVE_IO,
	.fअगरosize	= 3,
	.trwd		= 200,
पूर्ण;

अटल स्थिर काष्ठा sccnxp_chip sc68692 = अणु
	.name		= "SC68692",
	.nr		= 2,
	.freq_min	= 1000000,
	.freq_std	= 3686400,
	.freq_max	= 4000000,
	.flags		= SCCNXP_HAVE_IO,
	.fअगरosize	= 3,
	.trwd		= 200,
पूर्ण;

अटल u8 sccnxp_पढ़ो(काष्ठा uart_port *port, u8 reg)
अणु
	काष्ठा sccnxp_port *s = dev_get_drvdata(port->dev);
	u8 ret;

	ret = पढ़ोb(port->membase + (reg << port->regshअगरt));

	ndelay(s->chip->trwd);

	वापस ret;
पूर्ण

अटल व्योम sccnxp_ग_लिखो(काष्ठा uart_port *port, u8 reg, u8 v)
अणु
	काष्ठा sccnxp_port *s = dev_get_drvdata(port->dev);

	ग_लिखोb(v, port->membase + (reg << port->regshअगरt));

	ndelay(s->chip->trwd);
पूर्ण

अटल u8 sccnxp_port_पढ़ो(काष्ठा uart_port *port, u8 reg)
अणु
	वापस sccnxp_पढ़ो(port, (port->line << 3) + reg);
पूर्ण

अटल व्योम sccnxp_port_ग_लिखो(काष्ठा uart_port *port, u8 reg, u8 v)
अणु
	sccnxp_ग_लिखो(port, (port->line << 3) + reg, v);
पूर्ण

अटल पूर्णांक sccnxp_update_best_err(पूर्णांक a, पूर्णांक b, पूर्णांक *besterr)
अणु
	पूर्णांक err = असल(a - b);

	अगर (*besterr > err) अणु
		*besterr = err;
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा अणु
	u8	csr;
	u8	acr;
	u8	mr0;
	पूर्णांक	baud;
पूर्ण baud_std[] = अणु
	अणु 0,	ACR_BAUD0,	MR0_BAUD_NORMAL,	50, पूर्ण,
	अणु 0,	ACR_BAUD1,	MR0_BAUD_NORMAL,	75, पूर्ण,
	अणु 1,	ACR_BAUD0,	MR0_BAUD_NORMAL,	110, पूर्ण,
	अणु 2,	ACR_BAUD0,	MR0_BAUD_NORMAL,	134, पूर्ण,
	अणु 3,	ACR_BAUD1,	MR0_BAUD_NORMAL,	150, पूर्ण,
	अणु 3,	ACR_BAUD0,	MR0_BAUD_NORMAL,	200, पूर्ण,
	अणु 4,	ACR_BAUD0,	MR0_BAUD_NORMAL,	300, पूर्ण,
	अणु 0,	ACR_BAUD1,	MR0_BAUD_EXT1,		450, पूर्ण,
	अणु 1,	ACR_BAUD0,	MR0_BAUD_EXT2,		880, पूर्ण,
	अणु 3,	ACR_BAUD1,	MR0_BAUD_EXT1,		900, पूर्ण,
	अणु 5,	ACR_BAUD0,	MR0_BAUD_NORMAL,	600, पूर्ण,
	अणु 7,	ACR_BAUD0,	MR0_BAUD_NORMAL,	1050, पूर्ण,
	अणु 2,	ACR_BAUD0,	MR0_BAUD_EXT2,		1076, पूर्ण,
	अणु 6,	ACR_BAUD0,	MR0_BAUD_NORMAL,	1200, पूर्ण,
	अणु 10,	ACR_BAUD1,	MR0_BAUD_NORMAL,	1800, पूर्ण,
	अणु 7,	ACR_BAUD1,	MR0_BAUD_NORMAL,	2000, पूर्ण,
	अणु 8,	ACR_BAUD0,	MR0_BAUD_NORMAL,	2400, पूर्ण,
	अणु 5,	ACR_BAUD1,	MR0_BAUD_EXT1,		3600, पूर्ण,
	अणु 9,	ACR_BAUD0,	MR0_BAUD_NORMAL,	4800, पूर्ण,
	अणु 10,	ACR_BAUD0,	MR0_BAUD_NORMAL,	7200, पूर्ण,
	अणु 11,	ACR_BAUD0,	MR0_BAUD_NORMAL,	9600, पूर्ण,
	अणु 8,	ACR_BAUD0,	MR0_BAUD_EXT1,		14400, पूर्ण,
	अणु 12,	ACR_BAUD1,	MR0_BAUD_NORMAL,	19200, पूर्ण,
	अणु 9,	ACR_BAUD0,	MR0_BAUD_EXT1,		28800, पूर्ण,
	अणु 12,	ACR_BAUD0,	MR0_BAUD_NORMAL,	38400, पूर्ण,
	अणु 11,	ACR_BAUD0,	MR0_BAUD_EXT1,		57600, पूर्ण,
	अणु 12,	ACR_BAUD1,	MR0_BAUD_EXT1,		115200, पूर्ण,
	अणु 12,	ACR_BAUD0,	MR0_BAUD_EXT1,		230400, पूर्ण,
	अणु 0, 0, 0, 0 पूर्ण
पूर्ण;

अटल पूर्णांक sccnxp_set_baud(काष्ठा uart_port *port, पूर्णांक baud)
अणु
	काष्ठा sccnxp_port *s = dev_get_drvdata(port->dev);
	पूर्णांक भाग_std, पंचांगp_baud, bestbaud = पूर्णांक_उच्च, besterr = पूर्णांक_उच्च;
	काष्ठा sccnxp_chip *chip = s->chip;
	u8 i, acr = 0, csr = 0, mr0 = 0;

	/* Find भागisor to load to the समयr preset रेजिस्टरs */
	भाग_std = DIV_ROUND_CLOSEST(port->uartclk, 2 * 16 * baud);
	अगर ((भाग_std >= 2) && (भाग_std <= 0xffff)) अणु
		bestbaud = DIV_ROUND_CLOSEST(port->uartclk, 2 * 16 * भाग_std);
		sccnxp_update_best_err(baud, bestbaud, &besterr);
		csr = CSR_TIMER_MODE;
		sccnxp_port_ग_लिखो(port, SCCNXP_CTPU_REG, भाग_std >> 8);
		sccnxp_port_ग_लिखो(port, SCCNXP_CTPL_REG, भाग_std);
		/* Issue start समयr/counter command */
		sccnxp_port_पढ़ो(port, SCCNXP_START_COUNTER_REG);
	पूर्ण

	/* Find best baud from table */
	क्रम (i = 0; baud_std[i].baud && besterr; i++) अणु
		अगर (baud_std[i].mr0 && !(chip->flags & SCCNXP_HAVE_MR0))
			जारी;
		भाग_std = DIV_ROUND_CLOSEST(chip->freq_std, baud_std[i].baud);
		पंचांगp_baud = DIV_ROUND_CLOSEST(port->uartclk, भाग_std);
		अगर (!sccnxp_update_best_err(baud, पंचांगp_baud, &besterr)) अणु
			acr = baud_std[i].acr;
			csr = baud_std[i].csr;
			mr0 = baud_std[i].mr0;
			bestbaud = पंचांगp_baud;
		पूर्ण
	पूर्ण

	अगर (chip->flags & SCCNXP_HAVE_MR0) अणु
		/* Enable FIFO, set half level क्रम TX */
		mr0 |= MR0_FIFO | MR0_TXLVL;
		/* Update MR0 */
		sccnxp_port_ग_लिखो(port, SCCNXP_CR_REG, CR_CMD_MRPTR0);
		sccnxp_port_ग_लिखो(port, SCCNXP_MR_REG, mr0);
	पूर्ण

	sccnxp_port_ग_लिखो(port, SCCNXP_ACR_REG, acr | ACR_TIMER_MODE);
	sccnxp_port_ग_लिखो(port, SCCNXP_CSR_REG, (csr << 4) | csr);

	अगर (baud != bestbaud)
		dev_dbg(port->dev, "Baudrate desired: %i, calculated: %i\n",
			baud, bestbaud);

	वापस bestbaud;
पूर्ण

अटल व्योम sccnxp_enable_irq(काष्ठा uart_port *port, पूर्णांक mask)
अणु
	काष्ठा sccnxp_port *s = dev_get_drvdata(port->dev);

	s->imr |= mask << (port->line * 4);
	sccnxp_ग_लिखो(port, SCCNXP_IMR_REG, s->imr);
पूर्ण

अटल व्योम sccnxp_disable_irq(काष्ठा uart_port *port, पूर्णांक mask)
अणु
	काष्ठा sccnxp_port *s = dev_get_drvdata(port->dev);

	s->imr &= ~(mask << (port->line * 4));
	sccnxp_ग_लिखो(port, SCCNXP_IMR_REG, s->imr);
पूर्ण

अटल व्योम sccnxp_set_bit(काष्ठा uart_port *port, पूर्णांक sig, पूर्णांक state)
अणु
	u8 biपंचांगask;
	काष्ठा sccnxp_port *s = dev_get_drvdata(port->dev);

	अगर (s->pdata.mctrl_cfg[port->line] & MCTRL_MASK(sig)) अणु
		biपंचांगask = 1 << MCTRL_OBIT(s->pdata.mctrl_cfg[port->line], sig);
		अगर (state)
			sccnxp_ग_लिखो(port, SCCNXP_SOP_REG, biपंचांगask);
		अन्यथा
			sccnxp_ग_लिखो(port, SCCNXP_ROP_REG, biपंचांगask);
	पूर्ण
पूर्ण

अटल व्योम sccnxp_handle_rx(काष्ठा uart_port *port)
अणु
	u8 sr;
	अचिन्हित पूर्णांक ch, flag;

	क्रम (;;) अणु
		sr = sccnxp_port_पढ़ो(port, SCCNXP_SR_REG);
		अगर (!(sr & SR_RXRDY))
			अवरोध;
		sr &= SR_PE | SR_FE | SR_OVR | SR_BRK;

		ch = sccnxp_port_पढ़ो(port, SCCNXP_RHR_REG);

		port->icount.rx++;
		flag = TTY_NORMAL;

		अगर (unlikely(sr)) अणु
			अगर (sr & SR_BRK) अणु
				port->icount.brk++;
				sccnxp_port_ग_लिखो(port, SCCNXP_CR_REG,
						  CR_CMD_BREAK_RESET);
				अगर (uart_handle_अवरोध(port))
					जारी;
			पूर्ण अन्यथा अगर (sr & SR_PE)
				port->icount.parity++;
			अन्यथा अगर (sr & SR_FE)
				port->icount.frame++;
			अन्यथा अगर (sr & SR_OVR) अणु
				port->icount.overrun++;
				sccnxp_port_ग_लिखो(port, SCCNXP_CR_REG,
						  CR_CMD_STATUS_RESET);
			पूर्ण

			sr &= port->पढ़ो_status_mask;
			अगर (sr & SR_BRK)
				flag = TTY_BREAK;
			अन्यथा अगर (sr & SR_PE)
				flag = TTY_PARITY;
			अन्यथा अगर (sr & SR_FE)
				flag = TTY_FRAME;
			अन्यथा अगर (sr & SR_OVR)
				flag = TTY_OVERRUN;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(port, ch))
			जारी;

		अगर (sr & port->ignore_status_mask)
			जारी;

		uart_insert_अक्षर(port, sr, SR_OVR, ch, flag);
	पूर्ण

	tty_flip_buffer_push(&port->state->port);
पूर्ण

अटल व्योम sccnxp_handle_tx(काष्ठा uart_port *port)
अणु
	u8 sr;
	काष्ठा circ_buf *xmit = &port->state->xmit;
	काष्ठा sccnxp_port *s = dev_get_drvdata(port->dev);

	अगर (unlikely(port->x_अक्षर)) अणु
		sccnxp_port_ग_लिखो(port, SCCNXP_THR_REG, port->x_अक्षर);
		port->icount.tx++;
		port->x_अक्षर = 0;
		वापस;
	पूर्ण

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port)) अणु
		/* Disable TX अगर FIFO is empty */
		अगर (sccnxp_port_पढ़ो(port, SCCNXP_SR_REG) & SR_TXEMT) अणु
			sccnxp_disable_irq(port, IMR_TXRDY);

			/* Set direction to input */
			अगर (s->chip->flags & SCCNXP_HAVE_IO)
				sccnxp_set_bit(port, सूची_OP, 0);
		पूर्ण
		वापस;
	पूर्ण

	जबतक (!uart_circ_empty(xmit)) अणु
		sr = sccnxp_port_पढ़ो(port, SCCNXP_SR_REG);
		अगर (!(sr & SR_TXRDY))
			अवरोध;

		sccnxp_port_ग_लिखो(port, SCCNXP_THR_REG, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);
पूर्ण

अटल व्योम sccnxp_handle_events(काष्ठा sccnxp_port *s)
अणु
	पूर्णांक i;
	u8 isr;

	करो अणु
		isr = sccnxp_पढ़ो(&s->port[0], SCCNXP_ISR_REG);
		isr &= s->imr;
		अगर (!isr)
			अवरोध;

		क्रम (i = 0; i < s->uart.nr; i++) अणु
			अगर (s->खोलोed[i] && (isr & ISR_RXRDY(i)))
				sccnxp_handle_rx(&s->port[i]);
			अगर (s->खोलोed[i] && (isr & ISR_TXRDY(i)))
				sccnxp_handle_tx(&s->port[i]);
		पूर्ण
	पूर्ण जबतक (1);
पूर्ण

अटल व्योम sccnxp_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sccnxp_port *s = from_समयr(s, t, समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->lock, flags);
	sccnxp_handle_events(s);
	spin_unlock_irqrestore(&s->lock, flags);

	mod_समयr(&s->समयr, jअगरfies + usecs_to_jअगरfies(s->pdata.poll_समय_us));
पूर्ण

अटल irqवापस_t sccnxp_ist(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sccnxp_port *s = (काष्ठा sccnxp_port *)dev_id;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->lock, flags);
	sccnxp_handle_events(s);
	spin_unlock_irqrestore(&s->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sccnxp_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा sccnxp_port *s = dev_get_drvdata(port->dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->lock, flags);

	/* Set direction to output */
	अगर (s->chip->flags & SCCNXP_HAVE_IO)
		sccnxp_set_bit(port, सूची_OP, 1);

	sccnxp_enable_irq(port, IMR_TXRDY);

	spin_unlock_irqrestore(&s->lock, flags);
पूर्ण

अटल व्योम sccnxp_stop_tx(काष्ठा uart_port *port)
अणु
	/* Do nothing */
पूर्ण

अटल व्योम sccnxp_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा sccnxp_port *s = dev_get_drvdata(port->dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->lock, flags);
	sccnxp_port_ग_लिखो(port, SCCNXP_CR_REG, CR_RX_DISABLE);
	spin_unlock_irqrestore(&s->lock, flags);
पूर्ण

अटल अचिन्हित पूर्णांक sccnxp_tx_empty(काष्ठा uart_port *port)
अणु
	u8 val;
	अचिन्हित दीर्घ flags;
	काष्ठा sccnxp_port *s = dev_get_drvdata(port->dev);

	spin_lock_irqsave(&s->lock, flags);
	val = sccnxp_port_पढ़ो(port, SCCNXP_SR_REG);
	spin_unlock_irqrestore(&s->lock, flags);

	वापस (val & SR_TXEMT) ? TIOCSER_TEMT : 0;
पूर्ण

अटल व्योम sccnxp_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा sccnxp_port *s = dev_get_drvdata(port->dev);
	अचिन्हित दीर्घ flags;

	अगर (!(s->chip->flags & SCCNXP_HAVE_IO))
		वापस;

	spin_lock_irqsave(&s->lock, flags);

	sccnxp_set_bit(port, DTR_OP, mctrl & TIOCM_DTR);
	sccnxp_set_bit(port, RTS_OP, mctrl & TIOCM_RTS);

	spin_unlock_irqrestore(&s->lock, flags);
पूर्ण

अटल अचिन्हित पूर्णांक sccnxp_get_mctrl(काष्ठा uart_port *port)
अणु
	u8 biपंचांगask, ipr;
	अचिन्हित दीर्घ flags;
	काष्ठा sccnxp_port *s = dev_get_drvdata(port->dev);
	अचिन्हित पूर्णांक mctrl = TIOCM_DSR | TIOCM_CTS | TIOCM_CAR;

	अगर (!(s->chip->flags & SCCNXP_HAVE_IO))
		वापस mctrl;

	spin_lock_irqsave(&s->lock, flags);

	ipr = ~sccnxp_पढ़ो(port, SCCNXP_IPCR_REG);

	अगर (s->pdata.mctrl_cfg[port->line] & MCTRL_MASK(DSR_IP)) अणु
		biपंचांगask = 1 << MCTRL_IBIT(s->pdata.mctrl_cfg[port->line],
					  DSR_IP);
		mctrl &= ~TIOCM_DSR;
		mctrl |= (ipr & biपंचांगask) ? TIOCM_DSR : 0;
	पूर्ण
	अगर (s->pdata.mctrl_cfg[port->line] & MCTRL_MASK(CTS_IP)) अणु
		biपंचांगask = 1 << MCTRL_IBIT(s->pdata.mctrl_cfg[port->line],
					  CTS_IP);
		mctrl &= ~TIOCM_CTS;
		mctrl |= (ipr & biपंचांगask) ? TIOCM_CTS : 0;
	पूर्ण
	अगर (s->pdata.mctrl_cfg[port->line] & MCTRL_MASK(DCD_IP)) अणु
		biपंचांगask = 1 << MCTRL_IBIT(s->pdata.mctrl_cfg[port->line],
					  DCD_IP);
		mctrl &= ~TIOCM_CAR;
		mctrl |= (ipr & biपंचांगask) ? TIOCM_CAR : 0;
	पूर्ण
	अगर (s->pdata.mctrl_cfg[port->line] & MCTRL_MASK(RNG_IP)) अणु
		biपंचांगask = 1 << MCTRL_IBIT(s->pdata.mctrl_cfg[port->line],
					  RNG_IP);
		mctrl &= ~TIOCM_RNG;
		mctrl |= (ipr & biपंचांगask) ? TIOCM_RNG : 0;
	पूर्ण

	spin_unlock_irqrestore(&s->lock, flags);

	वापस mctrl;
पूर्ण

अटल व्योम sccnxp_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	काष्ठा sccnxp_port *s = dev_get_drvdata(port->dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->lock, flags);
	sccnxp_port_ग_लिखो(port, SCCNXP_CR_REG, अवरोध_state ?
			  CR_CMD_START_BREAK : CR_CMD_STOP_BREAK);
	spin_unlock_irqrestore(&s->lock, flags);
पूर्ण

अटल व्योम sccnxp_set_termios(काष्ठा uart_port *port,
			       काष्ठा ktermios *termios, काष्ठा ktermios *old)
अणु
	काष्ठा sccnxp_port *s = dev_get_drvdata(port->dev);
	अचिन्हित दीर्घ flags;
	u8 mr1, mr2;
	पूर्णांक baud;

	spin_lock_irqsave(&s->lock, flags);

	/* Mask termios capabilities we करोn't support */
	termios->c_cflag &= ~CMSPAR;

	/* Disable RX & TX, reset अवरोध condition, status and FIFOs */
	sccnxp_port_ग_लिखो(port, SCCNXP_CR_REG, CR_CMD_RX_RESET |
					       CR_RX_DISABLE | CR_TX_DISABLE);
	sccnxp_port_ग_लिखो(port, SCCNXP_CR_REG, CR_CMD_TX_RESET);
	sccnxp_port_ग_लिखो(port, SCCNXP_CR_REG, CR_CMD_STATUS_RESET);
	sccnxp_port_ग_लिखो(port, SCCNXP_CR_REG, CR_CMD_BREAK_RESET);

	/* Word size */
	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		mr1 = MR1_BITS_5;
		अवरोध;
	हाल CS6:
		mr1 = MR1_BITS_6;
		अवरोध;
	हाल CS7:
		mr1 = MR1_BITS_7;
		अवरोध;
	हाल CS8:
	शेष:
		mr1 = MR1_BITS_8;
		अवरोध;
	पूर्ण

	/* Parity */
	अगर (termios->c_cflag & PARENB) अणु
		अगर (termios->c_cflag & PARODD)
			mr1 |= MR1_PAR_ODD;
	पूर्ण अन्यथा
		mr1 |= MR1_PAR_NO;

	/* Stop bits */
	mr2 = (termios->c_cflag & CSTOPB) ? MR2_STOP2 : MR2_STOP1;

	/* Update desired क्रमmat */
	sccnxp_port_ग_लिखो(port, SCCNXP_CR_REG, CR_CMD_MRPTR1);
	sccnxp_port_ग_लिखो(port, SCCNXP_MR_REG, mr1);
	sccnxp_port_ग_लिखो(port, SCCNXP_MR_REG, mr2);

	/* Set पढ़ो status mask */
	port->पढ़ो_status_mask = SR_OVR;
	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= SR_PE | SR_FE;
	अगर (termios->c_अगरlag & (IGNBRK | BRKINT | PARMRK))
		port->पढ़ो_status_mask |= SR_BRK;

	/* Set status ignore mask */
	port->ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNBRK)
		port->ignore_status_mask |= SR_BRK;
	अगर (termios->c_अगरlag & IGNPAR)
		port->ignore_status_mask |= SR_PE;
	अगर (!(termios->c_cflag & CREAD))
		port->ignore_status_mask |= SR_PE | SR_OVR | SR_FE | SR_BRK;

	/* Setup baudrate */
	baud = uart_get_baud_rate(port, termios, old, 50,
				  (s->chip->flags & SCCNXP_HAVE_MR0) ?
				  230400 : 38400);
	baud = sccnxp_set_baud(port, baud);

	/* Update समयout according to new baud rate */
	uart_update_समयout(port, termios->c_cflag, baud);

	/* Report actual baudrate back to core */
	अगर (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);

	/* Enable RX & TX */
	sccnxp_port_ग_लिखो(port, SCCNXP_CR_REG, CR_RX_ENABLE | CR_TX_ENABLE);

	spin_unlock_irqrestore(&s->lock, flags);
पूर्ण

अटल पूर्णांक sccnxp_startup(काष्ठा uart_port *port)
अणु
	काष्ठा sccnxp_port *s = dev_get_drvdata(port->dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->lock, flags);

	अगर (s->chip->flags & SCCNXP_HAVE_IO) अणु
		/* Outमाला_दो are controlled manually */
		sccnxp_ग_लिखो(port, SCCNXP_OPCR_REG, 0);
	पूर्ण

	/* Reset अवरोध condition, status and FIFOs */
	sccnxp_port_ग_लिखो(port, SCCNXP_CR_REG, CR_CMD_RX_RESET);
	sccnxp_port_ग_लिखो(port, SCCNXP_CR_REG, CR_CMD_TX_RESET);
	sccnxp_port_ग_लिखो(port, SCCNXP_CR_REG, CR_CMD_STATUS_RESET);
	sccnxp_port_ग_लिखो(port, SCCNXP_CR_REG, CR_CMD_BREAK_RESET);

	/* Enable RX & TX */
	sccnxp_port_ग_लिखो(port, SCCNXP_CR_REG, CR_RX_ENABLE | CR_TX_ENABLE);

	/* Enable RX पूर्णांकerrupt */
	sccnxp_enable_irq(port, IMR_RXRDY);

	s->खोलोed[port->line] = 1;

	spin_unlock_irqrestore(&s->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम sccnxp_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा sccnxp_port *s = dev_get_drvdata(port->dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->lock, flags);

	s->खोलोed[port->line] = 0;

	/* Disable पूर्णांकerrupts */
	sccnxp_disable_irq(port, IMR_TXRDY | IMR_RXRDY);

	/* Disable TX & RX */
	sccnxp_port_ग_लिखो(port, SCCNXP_CR_REG, CR_RX_DISABLE | CR_TX_DISABLE);

	/* Leave direction to input */
	अगर (s->chip->flags & SCCNXP_HAVE_IO)
		sccnxp_set_bit(port, सूची_OP, 0);

	spin_unlock_irqrestore(&s->lock, flags);
पूर्ण

अटल स्थिर अक्षर *sccnxp_type(काष्ठा uart_port *port)
अणु
	काष्ठा sccnxp_port *s = dev_get_drvdata(port->dev);

	वापस (port->type == PORT_SC26XX) ? s->chip->name : शून्य;
पूर्ण

अटल व्योम sccnxp_release_port(काष्ठा uart_port *port)
अणु
	/* Do nothing */
पूर्ण

अटल पूर्णांक sccnxp_request_port(काष्ठा uart_port *port)
अणु
	/* Do nothing */
	वापस 0;
पूर्ण

अटल व्योम sccnxp_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE)
		port->type = PORT_SC26XX;
पूर्ण

अटल पूर्णांक sccnxp_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *s)
अणु
	अगर ((s->type == PORT_UNKNOWN) || (s->type == PORT_SC26XX))
		वापस 0;
	अगर (s->irq == port->irq)
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा uart_ops sccnxp_ops = अणु
	.tx_empty	= sccnxp_tx_empty,
	.set_mctrl	= sccnxp_set_mctrl,
	.get_mctrl	= sccnxp_get_mctrl,
	.stop_tx	= sccnxp_stop_tx,
	.start_tx	= sccnxp_start_tx,
	.stop_rx	= sccnxp_stop_rx,
	.अवरोध_ctl	= sccnxp_अवरोध_ctl,
	.startup	= sccnxp_startup,
	.shutकरोwn	= sccnxp_shutकरोwn,
	.set_termios	= sccnxp_set_termios,
	.type		= sccnxp_type,
	.release_port	= sccnxp_release_port,
	.request_port	= sccnxp_request_port,
	.config_port	= sccnxp_config_port,
	.verअगरy_port	= sccnxp_verअगरy_port,
पूर्ण;

#अगर_घोषित CONFIG_SERIAL_SCCNXP_CONSOLE
अटल व्योम sccnxp_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक c)
अणु
	पूर्णांक tryes = 100000;

	जबतक (tryes--) अणु
		अगर (sccnxp_port_पढ़ो(port, SCCNXP_SR_REG) & SR_TXRDY) अणु
			sccnxp_port_ग_लिखो(port, SCCNXP_THR_REG, c);
			अवरोध;
		पूर्ण
		barrier();
	पूर्ण
पूर्ण

अटल व्योम sccnxp_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *c, अचिन्हित n)
अणु
	काष्ठा sccnxp_port *s = (काष्ठा sccnxp_port *)co->data;
	काष्ठा uart_port *port = &s->port[co->index];
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->lock, flags);
	uart_console_ग_लिखो(port, c, n, sccnxp_console_अक्षर_दो);
	spin_unlock_irqrestore(&s->lock, flags);
पूर्ण

अटल पूर्णांक sccnxp_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा sccnxp_port *s = (काष्ठा sccnxp_port *)co->data;
	काष्ठा uart_port *port = &s->port[(co->index > 0) ? co->index : 0];
	पूर्णांक baud = 9600, bits = 8, parity = 'n', flow = 'n';

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा platक्रमm_device_id sccnxp_id_table[] = अणु
	अणु .name = "sc2681",	.driver_data = (kernel_uदीर्घ_t)&sc2681, पूर्ण,
	अणु .name = "sc2691",	.driver_data = (kernel_uदीर्घ_t)&sc2691, पूर्ण,
	अणु .name = "sc2692",	.driver_data = (kernel_uदीर्घ_t)&sc2692, पूर्ण,
	अणु .name = "sc2891",	.driver_data = (kernel_uदीर्घ_t)&sc2891, पूर्ण,
	अणु .name = "sc2892",	.driver_data = (kernel_uदीर्घ_t)&sc2892, पूर्ण,
	अणु .name = "sc28202",	.driver_data = (kernel_uदीर्घ_t)&sc28202, पूर्ण,
	अणु .name = "sc68681",	.driver_data = (kernel_uदीर्घ_t)&sc68681, पूर्ण,
	अणु .name = "sc68692",	.driver_data = (kernel_uदीर्घ_t)&sc68692, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, sccnxp_id_table);

अटल पूर्णांक sccnxp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	काष्ठा sccnxp_pdata *pdata = dev_get_platdata(&pdev->dev);
	पूर्णांक i, ret, uartclk;
	काष्ठा sccnxp_port *s;
	व्योम __iomem *membase;
	काष्ठा clk *clk;

	membase = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(membase))
		वापस PTR_ERR(membase);

	s = devm_kzalloc(&pdev->dev, माप(काष्ठा sccnxp_port), GFP_KERNEL);
	अगर (!s) अणु
		dev_err(&pdev->dev, "Error allocating port structure\n");
		वापस -ENOMEM;
	पूर्ण
	platक्रमm_set_drvdata(pdev, s);

	spin_lock_init(&s->lock);

	s->chip = (काष्ठा sccnxp_chip *)pdev->id_entry->driver_data;

	s->regulator = devm_regulator_get(&pdev->dev, "vcc");
	अगर (!IS_ERR(s->regulator)) अणु
		ret = regulator_enable(s->regulator);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"Failed to enable regulator: %i\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अगर (PTR_ERR(s->regulator) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		ret = PTR_ERR(clk);
		अगर (ret == -EPROBE_DEFER)
			जाओ err_out;
		uartclk = 0;
	पूर्ण अन्यथा अणु
		ret = clk_prepare_enable(clk);
		अगर (ret)
			जाओ err_out;

		ret = devm_add_action_or_reset(&pdev->dev,
				(व्योम(*)(व्योम *))clk_disable_unprepare,
				clk);
		अगर (ret)
			जाओ err_out;

		uartclk = clk_get_rate(clk);
	पूर्ण

	अगर (!uartclk) अणु
		dev_notice(&pdev->dev, "Using default clock frequency\n");
		uartclk = s->chip->freq_std;
	पूर्ण

	/* Check input frequency */
	अगर ((uartclk < s->chip->freq_min) || (uartclk > s->chip->freq_max)) अणु
		dev_err(&pdev->dev, "Frequency out of bounds\n");
		ret = -EINVAL;
		जाओ err_out;
	पूर्ण

	अगर (pdata)
		स_नकल(&s->pdata, pdata, माप(काष्ठा sccnxp_pdata));

	अगर (s->pdata.poll_समय_us) अणु
		dev_info(&pdev->dev, "Using poll mode, resolution %u usecs\n",
			 s->pdata.poll_समय_us);
		s->poll = 1;
	पूर्ण

	अगर (!s->poll) अणु
		s->irq = platक्रमm_get_irq(pdev, 0);
		अगर (s->irq < 0) अणु
			ret = -ENXIO;
			जाओ err_out;
		पूर्ण
	पूर्ण

	s->uart.owner		= THIS_MODULE;
	s->uart.dev_name	= "ttySC";
	s->uart.major		= SCCNXP_MAJOR;
	s->uart.minor		= SCCNXP_MINOR;
	s->uart.nr		= s->chip->nr;
#अगर_घोषित CONFIG_SERIAL_SCCNXP_CONSOLE
	s->uart.cons		= &s->console;
	s->uart.cons->device	= uart_console_device;
	s->uart.cons->ग_लिखो	= sccnxp_console_ग_लिखो;
	s->uart.cons->setup	= sccnxp_console_setup;
	s->uart.cons->flags	= CON_PRINTBUFFER;
	s->uart.cons->index	= -1;
	s->uart.cons->data	= s;
	म_नकल(s->uart.cons->name, "ttySC");
#पूर्ण_अगर
	ret = uart_रेजिस्टर_driver(&s->uart);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Registering UART driver failed\n");
		जाओ err_out;
	पूर्ण

	क्रम (i = 0; i < s->uart.nr; i++) अणु
		s->port[i].line		= i;
		s->port[i].dev		= &pdev->dev;
		s->port[i].irq		= s->irq;
		s->port[i].type		= PORT_SC26XX;
		s->port[i].fअगरosize	= s->chip->fअगरosize;
		s->port[i].flags	= UPF_SKIP_TEST | UPF_FIXED_TYPE;
		s->port[i].iotype	= UPIO_MEM;
		s->port[i].mapbase	= res->start;
		s->port[i].membase	= membase;
		s->port[i].regshअगरt	= s->pdata.reg_shअगरt;
		s->port[i].uartclk	= uartclk;
		s->port[i].ops		= &sccnxp_ops;
		s->port[i].has_sysrq = IS_ENABLED(CONFIG_SERIAL_SCCNXP_CONSOLE);
		uart_add_one_port(&s->uart, &s->port[i]);
		/* Set direction to input */
		अगर (s->chip->flags & SCCNXP_HAVE_IO)
			sccnxp_set_bit(&s->port[i], सूची_OP, 0);
	पूर्ण

	/* Disable पूर्णांकerrupts */
	s->imr = 0;
	sccnxp_ग_लिखो(&s->port[0], SCCNXP_IMR_REG, 0);

	अगर (!s->poll) अणु
		ret = devm_request_thपढ़ोed_irq(&pdev->dev, s->irq, शून्य,
						sccnxp_ist,
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						dev_name(&pdev->dev), s);
		अगर (!ret)
			वापस 0;

		dev_err(&pdev->dev, "Unable to reguest IRQ %i\n", s->irq);
	पूर्ण अन्यथा अणु
		समयr_setup(&s->समयr, sccnxp_समयr, 0);
		mod_समयr(&s->समयr, jअगरfies +
			  usecs_to_jअगरfies(s->pdata.poll_समय_us));
		वापस 0;
	पूर्ण

	uart_unरेजिस्टर_driver(&s->uart);
err_out:
	अगर (!IS_ERR(s->regulator))
		regulator_disable(s->regulator);

	वापस ret;
पूर्ण

अटल पूर्णांक sccnxp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;
	काष्ठा sccnxp_port *s = platक्रमm_get_drvdata(pdev);

	अगर (!s->poll)
		devm_मुक्त_irq(&pdev->dev, s->irq, s);
	अन्यथा
		del_समयr_sync(&s->समयr);

	क्रम (i = 0; i < s->uart.nr; i++)
		uart_हटाओ_one_port(&s->uart, &s->port[i]);

	uart_unरेजिस्टर_driver(&s->uart);

	अगर (!IS_ERR(s->regulator))
		वापस regulator_disable(s->regulator);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sccnxp_uart_driver = अणु
	.driver = अणु
		.name	= SCCNXP_NAME,
	पूर्ण,
	.probe		= sccnxp_probe,
	.हटाओ		= sccnxp_हटाओ,
	.id_table	= sccnxp_id_table,
पूर्ण;
module_platक्रमm_driver(sccnxp_uart_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Alexander Shiyan <shc_work@mail.ru>");
MODULE_DESCRIPTION("SCCNXP serial driver");
