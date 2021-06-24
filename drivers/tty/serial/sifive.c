<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * SiFive UART driver
 * Copyright (C) 2018 Paul Walmsley <paul@pwsan.com>
 * Copyright (C) 2018-2019 SiFive
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * Based partially on:
 * - drivers/tty/serial/pxa.c
 * - drivers/tty/serial/amba-pl011.c
 * - drivers/tty/serial/uartlite.c
 * - drivers/tty/serial/omap-serial.c
 * - drivers/pwm/pwm-sअगरive.c
 *
 * See the following sources क्रम further करोcumentation:
 * - Chapter 19 "Universal Asynchronous Receiver/Transmitter (UART)" of
 *   SiFive FE310-G000 v2p3
 * - The tree/master/src/मुख्य/scala/devices/uart directory of
 *   https://github.com/sअगरive/sअगरive-blocks/
 *
 * The SiFive UART design is not 8250-compatible.  The following common
 * features are not supported:
 * - Word lengths other than 8 bits
 * - Break handling
 * - Parity
 * - Flow control
 * - Modem संकेतs (DSR, RI, etc.)
 * On the other hand, the design is मुक्त from the baggage of the 8250
 * programming model.
 */

#समावेश <linux/clk.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>

/*
 * Register offsets
 */

/* TXDATA */
#घोषणा SIFIVE_SERIAL_TXDATA_OFFS		0x0
#घोषणा SIFIVE_SERIAL_TXDATA_FULL_SHIFT		31
#घोषणा SIFIVE_SERIAL_TXDATA_FULL_MASK		(1 << SIFIVE_SERIAL_TXDATA_FULL_SHIFT)
#घोषणा SIFIVE_SERIAL_TXDATA_DATA_SHIFT		0
#घोषणा SIFIVE_SERIAL_TXDATA_DATA_MASK		(0xff << SIFIVE_SERIAL_TXDATA_DATA_SHIFT)

/* RXDATA */
#घोषणा SIFIVE_SERIAL_RXDATA_OFFS		0x4
#घोषणा SIFIVE_SERIAL_RXDATA_EMPTY_SHIFT	31
#घोषणा SIFIVE_SERIAL_RXDATA_EMPTY_MASK		(1 << SIFIVE_SERIAL_RXDATA_EMPTY_SHIFT)
#घोषणा SIFIVE_SERIAL_RXDATA_DATA_SHIFT		0
#घोषणा SIFIVE_SERIAL_RXDATA_DATA_MASK		(0xff << SIFIVE_SERIAL_RXDATA_DATA_SHIFT)

/* TXCTRL */
#घोषणा SIFIVE_SERIAL_TXCTRL_OFFS		0x8
#घोषणा SIFIVE_SERIAL_TXCTRL_TXCNT_SHIFT	16
#घोषणा SIFIVE_SERIAL_TXCTRL_TXCNT_MASK		(0x7 << SIFIVE_SERIAL_TXCTRL_TXCNT_SHIFT)
#घोषणा SIFIVE_SERIAL_TXCTRL_NSTOP_SHIFT	1
#घोषणा SIFIVE_SERIAL_TXCTRL_NSTOP_MASK		(1 << SIFIVE_SERIAL_TXCTRL_NSTOP_SHIFT)
#घोषणा SIFIVE_SERIAL_TXCTRL_TXEN_SHIFT		0
#घोषणा SIFIVE_SERIAL_TXCTRL_TXEN_MASK		(1 << SIFIVE_SERIAL_TXCTRL_TXEN_SHIFT)

/* RXCTRL */
#घोषणा SIFIVE_SERIAL_RXCTRL_OFFS		0xC
#घोषणा SIFIVE_SERIAL_RXCTRL_RXCNT_SHIFT	16
#घोषणा SIFIVE_SERIAL_RXCTRL_RXCNT_MASK		(0x7 << SIFIVE_SERIAL_TXCTRL_TXCNT_SHIFT)
#घोषणा SIFIVE_SERIAL_RXCTRL_RXEN_SHIFT		0
#घोषणा SIFIVE_SERIAL_RXCTRL_RXEN_MASK		(1 << SIFIVE_SERIAL_RXCTRL_RXEN_SHIFT)

/* IE */
#घोषणा SIFIVE_SERIAL_IE_OFFS			0x10
#घोषणा SIFIVE_SERIAL_IE_RXWM_SHIFT		1
#घोषणा SIFIVE_SERIAL_IE_RXWM_MASK		(1 << SIFIVE_SERIAL_IE_RXWM_SHIFT)
#घोषणा SIFIVE_SERIAL_IE_TXWM_SHIFT		0
#घोषणा SIFIVE_SERIAL_IE_TXWM_MASK		(1 << SIFIVE_SERIAL_IE_TXWM_SHIFT)

/* IP */
#घोषणा SIFIVE_SERIAL_IP_OFFS			0x14
#घोषणा SIFIVE_SERIAL_IP_RXWM_SHIFT		1
#घोषणा SIFIVE_SERIAL_IP_RXWM_MASK		(1 << SIFIVE_SERIAL_IP_RXWM_SHIFT)
#घोषणा SIFIVE_SERIAL_IP_TXWM_SHIFT		0
#घोषणा SIFIVE_SERIAL_IP_TXWM_MASK		(1 << SIFIVE_SERIAL_IP_TXWM_SHIFT)

/* DIV */
#घोषणा SIFIVE_SERIAL_DIV_OFFS			0x18
#घोषणा SIFIVE_SERIAL_DIV_DIV_SHIFT		0
#घोषणा SIFIVE_SERIAL_DIV_DIV_MASK		(0xffff << SIFIVE_SERIAL_IP_DIV_SHIFT)

/*
 * Config macros
 */

/*
 * SIFIVE_SERIAL_MAX_PORTS: maximum number of UARTs on a device that can
 *                          host a serial console
 */
#घोषणा SIFIVE_SERIAL_MAX_PORTS			8

/*
 * SIFIVE_DEFAULT_BAUD_RATE: शेष baud rate that the driver should
 *                           configure itself to use
 */
#घोषणा SIFIVE_DEFAULT_BAUD_RATE		115200

/* SIFIVE_SERIAL_NAME: our driver's name that we pass to the operating प्रणाली */
#घोषणा SIFIVE_SERIAL_NAME			"sifive-serial"

/* SIFIVE_TTY_PREFIX: tty name prefix क्रम SiFive serial ports */
#घोषणा SIFIVE_TTY_PREFIX			"ttySIF"

/* SIFIVE_TX_FIFO_DEPTH: depth of the TX FIFO (in bytes) */
#घोषणा SIFIVE_TX_FIFO_DEPTH			8

/* SIFIVE_RX_FIFO_DEPTH: depth of the TX FIFO (in bytes) */
#घोषणा SIFIVE_RX_FIFO_DEPTH			8

#अगर (SIFIVE_TX_FIFO_DEPTH != SIFIVE_RX_FIFO_DEPTH)
#त्रुटि Driver करोes not support configurations with dअगरferent TX, RX FIFO sizes
#पूर्ण_अगर

/*
 *
 */

/**
 * काष्ठा sअगरive_serial_port - driver-specअगरic data extension to काष्ठा uart_port
 * @port: काष्ठा uart_port embedded in this काष्ठा
 * @dev: काष्ठा device *
 * @ier: shaकरोwed copy of the पूर्णांकerrupt enable रेजिस्टर
 * @clkin_rate: input घड़ी to the UART IP block.
 * @baud_rate: UART serial line rate (e.g., 115200 baud)
 * @clk: reference to this device's घड़ी
 * @clk_notअगरier: घड़ी rate change notअगरier क्रम upstream घड़ी changes
 *
 * Configuration data specअगरic to this SiFive UART.
 */
काष्ठा sअगरive_serial_port अणु
	काष्ठा uart_port	port;
	काष्ठा device		*dev;
	अचिन्हित अक्षर		ier;
	अचिन्हित दीर्घ		clkin_rate;
	अचिन्हित दीर्घ		baud_rate;
	काष्ठा clk		*clk;
	काष्ठा notअगरier_block	clk_notअगरier;
पूर्ण;

/*
 * Structure container-of macros
 */

#घोषणा port_to_sअगरive_serial_port(p) (container_of((p), \
						    काष्ठा sअगरive_serial_port, \
						    port))

#घोषणा notअगरier_to_sअगरive_serial_port(nb) (container_of((nb), \
							 काष्ठा sअगरive_serial_port, \
							 clk_notअगरier))

/*
 * Forward declarations
 */
अटल व्योम sअगरive_serial_stop_tx(काष्ठा uart_port *port);

/*
 * Internal functions
 */

/**
 * __ssp_early_ग_लिखोl() - ग_लिखो to a SiFive serial port रेजिस्टर (early)
 * @port: poपूर्णांकer to a काष्ठा uart_port record
 * @offs: रेजिस्टर address offset from the IP block base address
 * @v: value to ग_लिखो to the रेजिस्टर
 *
 * Given a poपूर्णांकer @port to a काष्ठा uart_port record, ग_लिखो the value
 * @v to the IP block रेजिस्टर address offset @offs.  This function is
 * पूर्णांकended क्रम early console use.
 *
 * Context: Intended to be used only by the earlyconsole code.
 */
अटल व्योम __ssp_early_ग_लिखोl(u32 v, u16 offs, काष्ठा uart_port *port)
अणु
	ग_लिखोl_relaxed(v, port->membase + offs);
पूर्ण

/**
 * __ssp_early_पढ़ोl() - पढ़ो from a SiFive serial port रेजिस्टर (early)
 * @port: poपूर्णांकer to a काष्ठा uart_port record
 * @offs: रेजिस्टर address offset from the IP block base address
 *
 * Given a poपूर्णांकer @port to a काष्ठा uart_port record, पढ़ो the
 * contents of the IP block रेजिस्टर located at offset @offs from the
 * IP block base and वापस it.  This function is पूर्णांकended क्रम early
 * console use.
 *
 * Context: Intended to be called only by the earlyconsole code or by
 *          __ssp_पढ़ोl() or __ssp_ग_लिखोl() (in this driver)
 *
 * Returns: the रेजिस्टर value पढ़ो from the UART.
 */
अटल u32 __ssp_early_पढ़ोl(काष्ठा uart_port *port, u16 offs)
अणु
	वापस पढ़ोl_relaxed(port->membase + offs);
पूर्ण

/**
 * __ssp_ग_लिखोl() - ग_लिखो to a SiFive serial port रेजिस्टर
 * @v: value to ग_लिखो to the रेजिस्टर
 * @offs: रेजिस्टर address offset from the IP block base address
 * @ssp: poपूर्णांकer to a काष्ठा sअगरive_serial_port record
 *
 * Write the value @v to the IP block रेजिस्टर located at offset @offs from the
 * IP block base, given a poपूर्णांकer @ssp to a काष्ठा sअगरive_serial_port record.
 *
 * Context: Any context.
 */
अटल व्योम __ssp_ग_लिखोl(u32 v, u16 offs, काष्ठा sअगरive_serial_port *ssp)
अणु
	__ssp_early_ग_लिखोl(v, offs, &ssp->port);
पूर्ण

/**
 * __ssp_पढ़ोl() - पढ़ो from a SiFive serial port रेजिस्टर
 * @ssp: poपूर्णांकer to a काष्ठा sअगरive_serial_port record
 * @offs: रेजिस्टर address offset from the IP block base address
 *
 * Read the contents of the IP block रेजिस्टर located at offset @offs from the
 * IP block base, given a poपूर्णांकer @ssp to a काष्ठा sअगरive_serial_port record.
 *
 * Context: Any context.
 *
 * Returns: the value of the UART रेजिस्टर
 */
अटल u32 __ssp_पढ़ोl(काष्ठा sअगरive_serial_port *ssp, u16 offs)
अणु
	वापस __ssp_early_पढ़ोl(&ssp->port, offs);
पूर्ण

/**
 * sअगरive_serial_is_txfअगरo_full() - is the TXFIFO full?
 * @ssp: poपूर्णांकer to a काष्ठा sअगरive_serial_port
 *
 * Read the transmit FIFO "full" bit, वापसing a non-zero value अगर the
 * TX FIFO is full, or zero अगर space reमुख्यs.  Intended to be used to prevent
 * ग_लिखोs to the TX FIFO when it's full.
 *
 * Returns: SIFIVE_SERIAL_TXDATA_FULL_MASK (non-zero) अगर the transmit FIFO
 * is full, or 0 अगर space reमुख्यs.
 */
अटल पूर्णांक sअगरive_serial_is_txfअगरo_full(काष्ठा sअगरive_serial_port *ssp)
अणु
	वापस __ssp_पढ़ोl(ssp, SIFIVE_SERIAL_TXDATA_OFFS) &
		SIFIVE_SERIAL_TXDATA_FULL_MASK;
पूर्ण

/**
 * __ssp_transmit_अक्षर() - enqueue a byte to transmit onto the TX FIFO
 * @ssp: poपूर्णांकer to a काष्ठा sअगरive_serial_port
 * @ch: अक्षरacter to transmit
 *
 * Enqueue a byte @ch onto the transmit FIFO, given a poपूर्णांकer @ssp to the
 * काष्ठा sअगरive_serial_port * to transmit on.  Caller should first check to
 * ensure that the TXFIFO has space; see sअगरive_serial_is_txfअगरo_full().
 *
 * Context: Any context.
 */
अटल व्योम __ssp_transmit_अक्षर(काष्ठा sअगरive_serial_port *ssp, पूर्णांक ch)
अणु
	__ssp_ग_लिखोl(ch, SIFIVE_SERIAL_TXDATA_OFFS, ssp);
पूर्ण

/**
 * __ssp_transmit_अक्षरs() - enqueue multiple bytes onto the TX FIFO
 * @ssp: poपूर्णांकer to a काष्ठा sअगरive_serial_port
 *
 * Transfer up to a TX FIFO size's worth of अक्षरacters from the Linux serial
 * transmit buffer to the SiFive UART TX FIFO.
 *
 * Context: Any context.  Expects @ssp->port.lock to be held by caller.
 */
अटल व्योम __ssp_transmit_अक्षरs(काष्ठा sअगरive_serial_port *ssp)
अणु
	काष्ठा circ_buf *xmit = &ssp->port.state->xmit;
	पूर्णांक count;

	अगर (ssp->port.x_अक्षर) अणु
		__ssp_transmit_अक्षर(ssp, ssp->port.x_अक्षर);
		ssp->port.icount.tx++;
		ssp->port.x_अक्षर = 0;
		वापस;
	पूर्ण
	अगर (uart_circ_empty(xmit) || uart_tx_stopped(&ssp->port)) अणु
		sअगरive_serial_stop_tx(&ssp->port);
		वापस;
	पूर्ण
	count = SIFIVE_TX_FIFO_DEPTH;
	करो अणु
		__ssp_transmit_अक्षर(ssp, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		ssp->port.icount.tx++;
		अगर (uart_circ_empty(xmit))
			अवरोध;
	पूर्ण जबतक (--count > 0);

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&ssp->port);

	अगर (uart_circ_empty(xmit))
		sअगरive_serial_stop_tx(&ssp->port);
पूर्ण

/**
 * __ssp_enable_txwm() - enable transmit watermark पूर्णांकerrupts
 * @ssp: poपूर्णांकer to a काष्ठा sअगरive_serial_port
 *
 * Enable पूर्णांकerrupt generation when the transmit FIFO watermark is reached
 * on the SiFive UART referred to by @ssp.
 */
अटल व्योम __ssp_enable_txwm(काष्ठा sअगरive_serial_port *ssp)
अणु
	अगर (ssp->ier & SIFIVE_SERIAL_IE_TXWM_MASK)
		वापस;

	ssp->ier |= SIFIVE_SERIAL_IE_TXWM_MASK;
	__ssp_ग_लिखोl(ssp->ier, SIFIVE_SERIAL_IE_OFFS, ssp);
पूर्ण

/**
 * __ssp_enable_rxwm() - enable receive watermark पूर्णांकerrupts
 * @ssp: poपूर्णांकer to a काष्ठा sअगरive_serial_port
 *
 * Enable पूर्णांकerrupt generation when the receive FIFO watermark is reached
 * on the SiFive UART referred to by @ssp.
 */
अटल व्योम __ssp_enable_rxwm(काष्ठा sअगरive_serial_port *ssp)
अणु
	अगर (ssp->ier & SIFIVE_SERIAL_IE_RXWM_MASK)
		वापस;

	ssp->ier |= SIFIVE_SERIAL_IE_RXWM_MASK;
	__ssp_ग_लिखोl(ssp->ier, SIFIVE_SERIAL_IE_OFFS, ssp);
पूर्ण

/**
 * __ssp_disable_txwm() - disable transmit watermark पूर्णांकerrupts
 * @ssp: poपूर्णांकer to a काष्ठा sअगरive_serial_port
 *
 * Disable पूर्णांकerrupt generation when the transmit FIFO watermark is reached
 * on the UART referred to by @ssp.
 */
अटल व्योम __ssp_disable_txwm(काष्ठा sअगरive_serial_port *ssp)
अणु
	अगर (!(ssp->ier & SIFIVE_SERIAL_IE_TXWM_MASK))
		वापस;

	ssp->ier &= ~SIFIVE_SERIAL_IE_TXWM_MASK;
	__ssp_ग_लिखोl(ssp->ier, SIFIVE_SERIAL_IE_OFFS, ssp);
पूर्ण

/**
 * __ssp_disable_rxwm() - disable receive watermark पूर्णांकerrupts
 * @ssp: poपूर्णांकer to a काष्ठा sअगरive_serial_port
 *
 * Disable पूर्णांकerrupt generation when the receive FIFO watermark is reached
 * on the UART referred to by @ssp.
 */
अटल व्योम __ssp_disable_rxwm(काष्ठा sअगरive_serial_port *ssp)
अणु
	अगर (!(ssp->ier & SIFIVE_SERIAL_IE_RXWM_MASK))
		वापस;

	ssp->ier &= ~SIFIVE_SERIAL_IE_RXWM_MASK;
	__ssp_ग_लिखोl(ssp->ier, SIFIVE_SERIAL_IE_OFFS, ssp);
पूर्ण

/**
 * __ssp_receive_अक्षर() - receive a byte from the UART
 * @ssp: poपूर्णांकer to a काष्ठा sअगरive_serial_port
 * @is_empty: अक्षर poपूर्णांकer to वापस whether the RX FIFO is empty
 *
 * Try to पढ़ो a byte from the SiFive UART RX FIFO, referenced by
 * @ssp, and to वापस it.  Also वापसs the RX FIFO empty bit in
 * the अक्षर poपूर्णांकed to by @ch.  The caller must pass the byte back to the
 * Linux serial layer अगर needed.
 *
 * Returns: the byte पढ़ो from the UART RX FIFO.
 */
अटल अक्षर __ssp_receive_अक्षर(काष्ठा sअगरive_serial_port *ssp, अक्षर *is_empty)
अणु
	u32 v;
	u8 ch;

	v = __ssp_पढ़ोl(ssp, SIFIVE_SERIAL_RXDATA_OFFS);

	अगर (!is_empty)
		WARN_ON(1);
	अन्यथा
		*is_empty = (v & SIFIVE_SERIAL_RXDATA_EMPTY_MASK) >>
			SIFIVE_SERIAL_RXDATA_EMPTY_SHIFT;

	ch = (v & SIFIVE_SERIAL_RXDATA_DATA_MASK) >>
		SIFIVE_SERIAL_RXDATA_DATA_SHIFT;

	वापस ch;
पूर्ण

/**
 * __ssp_receive_अक्षरs() - receive multiple bytes from the UART
 * @ssp: poपूर्णांकer to a काष्ठा sअगरive_serial_port
 *
 * Receive up to an RX FIFO's worth of bytes from the SiFive UART referred
 * to by @ssp and pass them up to the Linux serial layer.
 *
 * Context: Expects ssp->port.lock to be held by caller.
 */
अटल व्योम __ssp_receive_अक्षरs(काष्ठा sअगरive_serial_port *ssp)
अणु
	अचिन्हित अक्षर ch;
	अक्षर is_empty;
	पूर्णांक c;

	क्रम (c = SIFIVE_RX_FIFO_DEPTH; c > 0; --c) अणु
		ch = __ssp_receive_अक्षर(ssp, &is_empty);
		अगर (is_empty)
			अवरोध;

		ssp->port.icount.rx++;
		uart_insert_अक्षर(&ssp->port, 0, 0, ch, TTY_NORMAL);
	पूर्ण

	tty_flip_buffer_push(&ssp->port.state->port);
पूर्ण

/**
 * __ssp_update_भाग() - calculate the भागisor setting by the line rate
 * @ssp: poपूर्णांकer to a काष्ठा sअगरive_serial_port
 *
 * Calculate the appropriate value of the घड़ी भागisor क्रम the UART
 * and target line rate referred to by @ssp and ग_लिखो it पूर्णांकo the
 * hardware.
 */
अटल व्योम __ssp_update_भाग(काष्ठा sअगरive_serial_port *ssp)
अणु
	u16 भाग;

	भाग = DIV_ROUND_UP(ssp->clkin_rate, ssp->baud_rate) - 1;

	__ssp_ग_लिखोl(भाग, SIFIVE_SERIAL_DIV_OFFS, ssp);
पूर्ण

/**
 * __ssp_update_baud_rate() - set the UART "baud rate"
 * @ssp: poपूर्णांकer to a काष्ठा sअगरive_serial_port
 * @rate: new target bit rate
 *
 * Calculate the UART भागisor value क्रम the target bit rate @rate क्रम the
 * SiFive UART described by @ssp and program it पूर्णांकo the UART.  There may
 * be some error between the target bit rate and the actual bit rate implemented
 * by the UART due to घड़ी ratio granularity.
 */
अटल व्योम __ssp_update_baud_rate(काष्ठा sअगरive_serial_port *ssp,
				   अचिन्हित पूर्णांक rate)
अणु
	अगर (ssp->baud_rate == rate)
		वापस;

	ssp->baud_rate = rate;
	__ssp_update_भाग(ssp);
पूर्ण

/**
 * __ssp_set_stop_bits() - set the number of stop bits
 * @ssp: poपूर्णांकer to a काष्ठा sअगरive_serial_port
 * @nstop: 1 or 2 (stop bits)
 *
 * Program the SiFive UART referred to by @ssp to use @nstop stop bits.
 */
अटल व्योम __ssp_set_stop_bits(काष्ठा sअगरive_serial_port *ssp, अक्षर nstop)
अणु
	u32 v;

	अगर (nstop < 1 || nstop > 2) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	v = __ssp_पढ़ोl(ssp, SIFIVE_SERIAL_TXCTRL_OFFS);
	v &= ~SIFIVE_SERIAL_TXCTRL_NSTOP_MASK;
	v |= (nstop - 1) << SIFIVE_SERIAL_TXCTRL_NSTOP_SHIFT;
	__ssp_ग_लिखोl(v, SIFIVE_SERIAL_TXCTRL_OFFS, ssp);
पूर्ण

/**
 * __ssp_रुको_क्रम_xmitr() - रुको क्रम an empty slot on the TX FIFO
 * @ssp: poपूर्णांकer to a काष्ठा sअगरive_serial_port
 *
 * Delay जबतक the UART TX FIFO referred to by @ssp is marked as full.
 *
 * Context: Any context.
 */
अटल व्योम __maybe_unused __ssp_रुको_क्रम_xmitr(काष्ठा sअगरive_serial_port *ssp)
अणु
	जबतक (sअगरive_serial_is_txfअगरo_full(ssp))
		udelay(1); /* XXX Could probably be more पूर्णांकelligent here */
पूर्ण

/*
 * Linux serial API functions
 */

अटल व्योम sअगरive_serial_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा sअगरive_serial_port *ssp = port_to_sअगरive_serial_port(port);

	__ssp_disable_txwm(ssp);
पूर्ण

अटल व्योम sअगरive_serial_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा sअगरive_serial_port *ssp = port_to_sअगरive_serial_port(port);

	__ssp_disable_rxwm(ssp);
पूर्ण

अटल व्योम sअगरive_serial_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा sअगरive_serial_port *ssp = port_to_sअगरive_serial_port(port);

	__ssp_enable_txwm(ssp);
पूर्ण

अटल irqवापस_t sअगरive_serial_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sअगरive_serial_port *ssp = dev_id;
	u32 ip;

	spin_lock(&ssp->port.lock);

	ip = __ssp_पढ़ोl(ssp, SIFIVE_SERIAL_IP_OFFS);
	अगर (!ip) अणु
		spin_unlock(&ssp->port.lock);
		वापस IRQ_NONE;
	पूर्ण

	अगर (ip & SIFIVE_SERIAL_IP_RXWM_MASK)
		__ssp_receive_अक्षरs(ssp);
	अगर (ip & SIFIVE_SERIAL_IP_TXWM_MASK)
		__ssp_transmit_अक्षरs(ssp);

	spin_unlock(&ssp->port.lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित पूर्णांक sअगरive_serial_tx_empty(काष्ठा uart_port *port)
अणु
	वापस TIOCSER_TEMT;
पूर्ण

अटल अचिन्हित पूर्णांक sअगरive_serial_get_mctrl(काष्ठा uart_port *port)
अणु
	वापस TIOCM_CAR | TIOCM_CTS | TIOCM_DSR;
पूर्ण

अटल व्योम sअगरive_serial_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	/* IP block करोes not support these संकेतs */
पूर्ण

अटल व्योम sअगरive_serial_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	/* IP block करोes not support sending a अवरोध */
पूर्ण

अटल पूर्णांक sअगरive_serial_startup(काष्ठा uart_port *port)
अणु
	काष्ठा sअगरive_serial_port *ssp = port_to_sअगरive_serial_port(port);

	__ssp_enable_rxwm(ssp);

	वापस 0;
पूर्ण

अटल व्योम sअगरive_serial_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा sअगरive_serial_port *ssp = port_to_sअगरive_serial_port(port);

	__ssp_disable_rxwm(ssp);
	__ssp_disable_txwm(ssp);
पूर्ण

/**
 * sअगरive_serial_clk_notअगरier() - घड़ी post-rate-change notअगरier
 * @nb: poपूर्णांकer to the काष्ठा notअगरier_block, from the notअगरier code
 * @event: event mask from the notअगरier code
 * @data: poपूर्णांकer to the काष्ठा clk_notअगरier_data from the notअगरier code
 *
 * On the V0 SoC, the UART IP block is derived from the CPU घड़ी source
 * after a synchronous भागide-by-two भागider, so any CPU घड़ी rate change
 * requires the UART baud rate to be updated.  This presumably corrupts any
 * serial word currently being transmitted or received.  In order to aव्योम
 * corrupting the output data stream, we drain the transmit queue beक्रमe
 * allowing the घड़ी's rate to be changed.
 */
अटल पूर्णांक sअगरive_serial_clk_notअगरier(काष्ठा notअगरier_block *nb,
				      अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा clk_notअगरier_data *cnd = data;
	काष्ठा sअगरive_serial_port *ssp = notअगरier_to_sअगरive_serial_port(nb);

	अगर (event == PRE_RATE_CHANGE) अणु
		/*
		 * The TX watermark is always set to 1 by this driver, which
		 * means that the TX busy bit will lower when there are 0 bytes
		 * left in the TX queue -- in other words, when the TX FIFO is
		 * empty.
		 */
		__ssp_रुको_क्रम_xmitr(ssp);
		/*
		 * On the cycle the TX FIFO goes empty there is still a full
		 * UART frame left to be transmitted in the shअगरt रेजिस्टर.
		 * The UART provides no way क्रम software to directly determine
		 * when that last frame has been transmitted, so we just sleep
		 * here instead.  As we're not tracking the number of stop bits
		 * they're just worst हालd here.  The rest of the serial
		 * framing parameters aren't configurable by software.
		 */
		udelay(DIV_ROUND_UP(12 * 1000 * 1000, ssp->baud_rate));
	पूर्ण

	अगर (event == POST_RATE_CHANGE && ssp->clkin_rate != cnd->new_rate) अणु
		ssp->clkin_rate = cnd->new_rate;
		__ssp_update_भाग(ssp);
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल व्योम sअगरive_serial_set_termios(काष्ठा uart_port *port,
				      काष्ठा ktermios *termios,
				      काष्ठा ktermios *old)
अणु
	काष्ठा sअगरive_serial_port *ssp = port_to_sअगरive_serial_port(port);
	अचिन्हित दीर्घ flags;
	u32 v, old_v;
	पूर्णांक rate;
	अक्षर nstop;

	अगर ((termios->c_cflag & CSIZE) != CS8)
		dev_err_once(ssp->port.dev, "only 8-bit words supported\n");
	अगर (termios->c_अगरlag & (INPCK | PARMRK))
		dev_err_once(ssp->port.dev, "parity checking not supported\n");
	अगर (termios->c_अगरlag & BRKINT)
		dev_err_once(ssp->port.dev, "BREAK detection not supported\n");

	/* Set number of stop bits */
	nstop = (termios->c_cflag & CSTOPB) ? 2 : 1;
	__ssp_set_stop_bits(ssp, nstop);

	/* Set line rate */
	rate = uart_get_baud_rate(port, termios, old, 0, ssp->clkin_rate / 16);
	__ssp_update_baud_rate(ssp, rate);

	spin_lock_irqsave(&ssp->port.lock, flags);

	/* Update the per-port समयout */
	uart_update_समयout(port, termios->c_cflag, rate);

	ssp->port.पढ़ो_status_mask = 0;

	/* Ignore all अक्षरacters अगर CREAD is not set */
	v = __ssp_पढ़ोl(ssp, SIFIVE_SERIAL_RXCTRL_OFFS);
	old_v = v;
	अगर ((termios->c_cflag & CREAD) == 0)
		v &= SIFIVE_SERIAL_RXCTRL_RXEN_MASK;
	अन्यथा
		v |= SIFIVE_SERIAL_RXCTRL_RXEN_MASK;
	अगर (v != old_v)
		__ssp_ग_लिखोl(v, SIFIVE_SERIAL_RXCTRL_OFFS, ssp);

	spin_unlock_irqrestore(&ssp->port.lock, flags);
पूर्ण

अटल व्योम sअगरive_serial_release_port(काष्ठा uart_port *port)
अणु
पूर्ण

अटल पूर्णांक sअगरive_serial_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम sअगरive_serial_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	काष्ठा sअगरive_serial_port *ssp = port_to_sअगरive_serial_port(port);

	ssp->port.type = PORT_SIFIVE_V0;
पूर्ण

अटल पूर्णांक sअगरive_serial_verअगरy_port(काष्ठा uart_port *port,
				     काष्ठा serial_काष्ठा *ser)
अणु
	वापस -EINVAL;
पूर्ण

अटल स्थिर अक्षर *sअगरive_serial_type(काष्ठा uart_port *port)
अणु
	वापस port->type == PORT_SIFIVE_V0 ? "SiFive UART v0" : शून्य;
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL
अटल पूर्णांक sअगरive_serial_poll_get_अक्षर(काष्ठा uart_port *port)
अणु
	काष्ठा sअगरive_serial_port *ssp = port_to_sअगरive_serial_port(port);
	अक्षर is_empty, ch;

	ch = __ssp_receive_अक्षर(ssp, &is_empty);
	अगर (is_empty)
		वापस NO_POLL_CHAR;

	वापस ch;
पूर्ण

अटल व्योम sअगरive_serial_poll_put_अक्षर(काष्ठा uart_port *port,
					अचिन्हित अक्षर c)
अणु
	काष्ठा sअगरive_serial_port *ssp = port_to_sअगरive_serial_port(port);

	__ssp_रुको_क्रम_xmitr(ssp);
	__ssp_transmit_अक्षर(ssp, c);
पूर्ण
#पूर्ण_अगर /* CONFIG_CONSOLE_POLL */

/*
 * Early console support
 */

#अगर_घोषित CONFIG_SERIAL_EARLYCON
अटल व्योम early_sअगरive_serial_अ_दो(काष्ठा uart_port *port, पूर्णांक c)
अणु
	जबतक (__ssp_early_पढ़ोl(port, SIFIVE_SERIAL_TXDATA_OFFS) &
	       SIFIVE_SERIAL_TXDATA_FULL_MASK)
		cpu_relax();

	__ssp_early_ग_लिखोl(c, SIFIVE_SERIAL_TXDATA_OFFS, port);
पूर्ण

अटल व्योम early_sअगरive_serial_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s,
				      अचिन्हित पूर्णांक n)
अणु
	काष्ठा earlycon_device *dev = con->data;
	काष्ठा uart_port *port = &dev->port;

	uart_console_ग_लिखो(port, s, n, early_sअगरive_serial_अ_दो);
पूर्ण

अटल पूर्णांक __init early_sअगरive_serial_setup(काष्ठा earlycon_device *dev,
					    स्थिर अक्षर *options)
अणु
	काष्ठा uart_port *port = &dev->port;

	अगर (!port->membase)
		वापस -ENODEV;

	dev->con->ग_लिखो = early_sअगरive_serial_ग_लिखो;

	वापस 0;
पूर्ण

OF_EARLYCON_DECLARE(sअगरive, "sifive,uart0", early_sअगरive_serial_setup);
OF_EARLYCON_DECLARE(sअगरive, "sifive,fu540-c000-uart0",
		    early_sअगरive_serial_setup);
#पूर्ण_अगर /* CONFIG_SERIAL_EARLYCON */

/*
 * Linux console पूर्णांकerface
 */

#अगर_घोषित CONFIG_SERIAL_SIFIVE_CONSOLE

अटल काष्ठा sअगरive_serial_port *sअगरive_serial_console_ports[SIFIVE_SERIAL_MAX_PORTS];

अटल व्योम sअगरive_serial_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	काष्ठा sअगरive_serial_port *ssp = port_to_sअगरive_serial_port(port);

	__ssp_रुको_क्रम_xmitr(ssp);
	__ssp_transmit_अक्षर(ssp, ch);
पूर्ण

अटल व्योम sअगरive_serial_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
					अचिन्हित पूर्णांक count)
अणु
	काष्ठा sअगरive_serial_port *ssp = sअगरive_serial_console_ports[co->index];
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ier;
	पूर्णांक locked = 1;

	अगर (!ssp)
		वापस;

	local_irq_save(flags);
	अगर (ssp->port.sysrq)
		locked = 0;
	अन्यथा अगर (oops_in_progress)
		locked = spin_trylock(&ssp->port.lock);
	अन्यथा
		spin_lock(&ssp->port.lock);

	ier = __ssp_पढ़ोl(ssp, SIFIVE_SERIAL_IE_OFFS);
	__ssp_ग_लिखोl(0, SIFIVE_SERIAL_IE_OFFS, ssp);

	uart_console_ग_लिखो(&ssp->port, s, count, sअगरive_serial_console_अक्षर_दो);

	__ssp_ग_लिखोl(ier, SIFIVE_SERIAL_IE_OFFS, ssp);

	अगर (locked)
		spin_unlock(&ssp->port.lock);
	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक __init sअगरive_serial_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा sअगरive_serial_port *ssp;
	पूर्णांक baud = SIFIVE_DEFAULT_BAUD_RATE;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (co->index < 0 || co->index >= SIFIVE_SERIAL_MAX_PORTS)
		वापस -ENODEV;

	ssp = sअगरive_serial_console_ports[co->index];
	अगर (!ssp)
		वापस -ENODEV;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(&ssp->port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver sअगरive_serial_uart_driver;

अटल काष्ठा console sअगरive_serial_console = अणु
	.name		= SIFIVE_TTY_PREFIX,
	.ग_लिखो		= sअगरive_serial_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= sअगरive_serial_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &sअगरive_serial_uart_driver,
पूर्ण;

अटल पूर्णांक __init sअगरive_console_init(व्योम)
अणु
	रेजिस्टर_console(&sअगरive_serial_console);
	वापस 0;
पूर्ण

console_initcall(sअगरive_console_init);

अटल व्योम __ssp_add_console_port(काष्ठा sअगरive_serial_port *ssp)
अणु
	sअगरive_serial_console_ports[ssp->port.line] = ssp;
पूर्ण

अटल व्योम __ssp_हटाओ_console_port(काष्ठा sअगरive_serial_port *ssp)
अणु
	sअगरive_serial_console_ports[ssp->port.line] = 0;
पूर्ण

#घोषणा SIFIVE_SERIAL_CONSOLE	(&sअगरive_serial_console)

#अन्यथा

#घोषणा SIFIVE_SERIAL_CONSOLE	शून्य

अटल व्योम __ssp_add_console_port(काष्ठा sअगरive_serial_port *ssp)
अणुपूर्ण
अटल व्योम __ssp_हटाओ_console_port(काष्ठा sअगरive_serial_port *ssp)
अणुपूर्ण

#पूर्ण_अगर

अटल स्थिर काष्ठा uart_ops sअगरive_serial_uops = अणु
	.tx_empty	= sअगरive_serial_tx_empty,
	.set_mctrl	= sअगरive_serial_set_mctrl,
	.get_mctrl	= sअगरive_serial_get_mctrl,
	.stop_tx	= sअगरive_serial_stop_tx,
	.start_tx	= sअगरive_serial_start_tx,
	.stop_rx	= sअगरive_serial_stop_rx,
	.अवरोध_ctl	= sअगरive_serial_अवरोध_ctl,
	.startup	= sअगरive_serial_startup,
	.shutकरोwn	= sअगरive_serial_shutकरोwn,
	.set_termios	= sअगरive_serial_set_termios,
	.type		= sअगरive_serial_type,
	.release_port	= sअगरive_serial_release_port,
	.request_port	= sअगरive_serial_request_port,
	.config_port	= sअगरive_serial_config_port,
	.verअगरy_port	= sअगरive_serial_verअगरy_port,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_get_अक्षर	= sअगरive_serial_poll_get_अक्षर,
	.poll_put_अक्षर	= sअगरive_serial_poll_put_अक्षर,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा uart_driver sअगरive_serial_uart_driver = अणु
	.owner		= THIS_MODULE,
	.driver_name	= SIFIVE_SERIAL_NAME,
	.dev_name	= SIFIVE_TTY_PREFIX,
	.nr		= SIFIVE_SERIAL_MAX_PORTS,
	.cons		= SIFIVE_SERIAL_CONSOLE,
पूर्ण;

अटल पूर्णांक sअगरive_serial_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sअगरive_serial_port *ssp;
	काष्ठा resource *mem;
	काष्ठा clk *clk;
	व्योम __iomem *base;
	पूर्णांक irq, id, r;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -EPROBE_DEFER;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(base)) अणु
		dev_err(&pdev->dev, "could not acquire device memory\n");
		वापस PTR_ERR(base);
	पूर्ण

	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "unable to find controller clock\n");
		वापस PTR_ERR(clk);
	पूर्ण

	id = of_alias_get_id(pdev->dev.of_node, "serial");
	अगर (id < 0) अणु
		dev_err(&pdev->dev, "missing aliases entry\n");
		वापस id;
	पूर्ण

#अगर_घोषित CONFIG_SERIAL_SIFIVE_CONSOLE
	अगर (id > SIFIVE_SERIAL_MAX_PORTS) अणु
		dev_err(&pdev->dev, "too many UARTs (%d)\n", id);
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर

	ssp = devm_kzalloc(&pdev->dev, माप(*ssp), GFP_KERNEL);
	अगर (!ssp)
		वापस -ENOMEM;

	ssp->port.dev = &pdev->dev;
	ssp->port.type = PORT_SIFIVE_V0;
	ssp->port.iotype = UPIO_MEM;
	ssp->port.irq = irq;
	ssp->port.fअगरosize = SIFIVE_TX_FIFO_DEPTH;
	ssp->port.ops = &sअगरive_serial_uops;
	ssp->port.line = id;
	ssp->port.mapbase = mem->start;
	ssp->port.membase = base;
	ssp->dev = &pdev->dev;
	ssp->clk = clk;
	ssp->clk_notअगरier.notअगरier_call = sअगरive_serial_clk_notअगरier;

	r = clk_notअगरier_रेजिस्टर(ssp->clk, &ssp->clk_notअगरier);
	अगर (r) अणु
		dev_err(&pdev->dev, "could not register clock notifier: %d\n",
			r);
		जाओ probe_out1;
	पूर्ण

	/* Set up घड़ी भागider */
	ssp->clkin_rate = clk_get_rate(ssp->clk);
	ssp->baud_rate = SIFIVE_DEFAULT_BAUD_RATE;
	ssp->port.uartclk = ssp->baud_rate * 16;
	__ssp_update_भाग(ssp);

	platक्रमm_set_drvdata(pdev, ssp);

	/* Enable transmits and set the watermark level to 1 */
	__ssp_ग_लिखोl((1 << SIFIVE_SERIAL_TXCTRL_TXCNT_SHIFT) |
		     SIFIVE_SERIAL_TXCTRL_TXEN_MASK,
		     SIFIVE_SERIAL_TXCTRL_OFFS, ssp);

	/* Enable receives and set the watermark level to 0 */
	__ssp_ग_लिखोl((0 << SIFIVE_SERIAL_RXCTRL_RXCNT_SHIFT) |
		     SIFIVE_SERIAL_RXCTRL_RXEN_MASK,
		     SIFIVE_SERIAL_RXCTRL_OFFS, ssp);

	r = request_irq(ssp->port.irq, sअगरive_serial_irq, ssp->port.irqflags,
			dev_name(&pdev->dev), ssp);
	अगर (r) अणु
		dev_err(&pdev->dev, "could not attach interrupt: %d\n", r);
		जाओ probe_out2;
	पूर्ण

	__ssp_add_console_port(ssp);

	r = uart_add_one_port(&sअगरive_serial_uart_driver, &ssp->port);
	अगर (r != 0) अणु
		dev_err(&pdev->dev, "could not add uart: %d\n", r);
		जाओ probe_out3;
	पूर्ण

	वापस 0;

probe_out3:
	__ssp_हटाओ_console_port(ssp);
	मुक्त_irq(ssp->port.irq, ssp);
probe_out2:
	clk_notअगरier_unरेजिस्टर(ssp->clk, &ssp->clk_notअगरier);
probe_out1:
	वापस r;
पूर्ण

अटल पूर्णांक sअगरive_serial_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा sअगरive_serial_port *ssp = platक्रमm_get_drvdata(dev);

	__ssp_हटाओ_console_port(ssp);
	uart_हटाओ_one_port(&sअगरive_serial_uart_driver, &ssp->port);
	मुक्त_irq(ssp->port.irq, ssp);
	clk_notअगरier_unरेजिस्टर(ssp->clk, &ssp->clk_notअगरier);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sअगरive_serial_of_match[] = अणु
	अणु .compatible = "sifive,fu540-c000-uart0" पूर्ण,
	अणु .compatible = "sifive,uart0" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sअगरive_serial_of_match);

अटल काष्ठा platक्रमm_driver sअगरive_serial_platक्रमm_driver = अणु
	.probe		= sअगरive_serial_probe,
	.हटाओ		= sअगरive_serial_हटाओ,
	.driver		= अणु
		.name	= SIFIVE_SERIAL_NAME,
		.of_match_table = of_match_ptr(sअगरive_serial_of_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sअगरive_serial_init(व्योम)
अणु
	पूर्णांक r;

	r = uart_रेजिस्टर_driver(&sअगरive_serial_uart_driver);
	अगर (r)
		जाओ init_out1;

	r = platक्रमm_driver_रेजिस्टर(&sअगरive_serial_platक्रमm_driver);
	अगर (r)
		जाओ init_out2;

	वापस 0;

init_out2:
	uart_unरेजिस्टर_driver(&sअगरive_serial_uart_driver);
init_out1:
	वापस r;
पूर्ण

अटल व्योम __निकास sअगरive_serial_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sअगरive_serial_platक्रमm_driver);
	uart_unरेजिस्टर_driver(&sअगरive_serial_uart_driver);
पूर्ण

module_init(sअगरive_serial_init);
module_निकास(sअगरive_serial_निकास);

MODULE_DESCRIPTION("SiFive UART serial driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Paul Walmsley <paul@pwsan.com>");
