<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) Maxime Coquelin 2015
 * Copyright (C) STMicroelectronics SA 2017
 * Authors:  Maxime Coquelin <mcoquelin.sपंचांग32@gmail.com>
 *	     Gerald Baeza <gerald.baeza@foss.st.com>
 *	     Erwan Le Ray <erwan.leray@foss.st.com>
 *
 * Inspired by st-asc.c from STMicroelectronics (c)
 */

#समावेश <linux/clk.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/tty.h>

#समावेश "serial_mctrl_gpio.h"
#समावेश "stm32-usart.h"

अटल व्योम sपंचांग32_usart_stop_tx(काष्ठा uart_port *port);
अटल व्योम sपंचांग32_usart_transmit_अक्षरs(काष्ठा uart_port *port);

अटल अंतरभूत काष्ठा sपंचांग32_port *to_sपंचांग32_port(काष्ठा uart_port *port)
अणु
	वापस container_of(port, काष्ठा sपंचांग32_port, port);
पूर्ण

अटल व्योम sपंचांग32_usart_set_bits(काष्ठा uart_port *port, u32 reg, u32 bits)
अणु
	u32 val;

	val = पढ़ोl_relaxed(port->membase + reg);
	val |= bits;
	ग_लिखोl_relaxed(val, port->membase + reg);
पूर्ण

अटल व्योम sपंचांग32_usart_clr_bits(काष्ठा uart_port *port, u32 reg, u32 bits)
अणु
	u32 val;

	val = पढ़ोl_relaxed(port->membase + reg);
	val &= ~bits;
	ग_लिखोl_relaxed(val, port->membase + reg);
पूर्ण

अटल व्योम sपंचांग32_usart_config_reg_rs485(u32 *cr1, u32 *cr3, u32 delay_ADE,
					 u32 delay_DDE, u32 baud)
अणु
	u32 rs485_deat_dedt;
	u32 rs485_deat_dedt_max = (USART_CR1_DEAT_MASK >> USART_CR1_DEAT_SHIFT);
	bool over8;

	*cr3 |= USART_CR3_DEM;
	over8 = *cr1 & USART_CR1_OVER8;

	अगर (over8)
		rs485_deat_dedt = delay_ADE * baud * 8;
	अन्यथा
		rs485_deat_dedt = delay_ADE * baud * 16;

	rs485_deat_dedt = DIV_ROUND_CLOSEST(rs485_deat_dedt, 1000);
	rs485_deat_dedt = rs485_deat_dedt > rs485_deat_dedt_max ?
			  rs485_deat_dedt_max : rs485_deat_dedt;
	rs485_deat_dedt = (rs485_deat_dedt << USART_CR1_DEAT_SHIFT) &
			   USART_CR1_DEAT_MASK;
	*cr1 |= rs485_deat_dedt;

	अगर (over8)
		rs485_deat_dedt = delay_DDE * baud * 8;
	अन्यथा
		rs485_deat_dedt = delay_DDE * baud * 16;

	rs485_deat_dedt = DIV_ROUND_CLOSEST(rs485_deat_dedt, 1000);
	rs485_deat_dedt = rs485_deat_dedt > rs485_deat_dedt_max ?
			  rs485_deat_dedt_max : rs485_deat_dedt;
	rs485_deat_dedt = (rs485_deat_dedt << USART_CR1_DEDT_SHIFT) &
			   USART_CR1_DEDT_MASK;
	*cr1 |= rs485_deat_dedt;
पूर्ण

अटल पूर्णांक sपंचांग32_usart_config_rs485(काष्ठा uart_port *port,
				    काष्ठा serial_rs485 *rs485conf)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;
	स्थिर काष्ठा sपंचांग32_usart_config *cfg = &sपंचांग32_port->info->cfg;
	u32 usartभाग, baud, cr1, cr3;
	bool over8;

	sपंचांग32_usart_clr_bits(port, ofs->cr1, BIT(cfg->uart_enable_bit));

	port->rs485 = *rs485conf;

	rs485conf->flags |= SER_RS485_RX_DURING_TX;

	अगर (rs485conf->flags & SER_RS485_ENABLED) अणु
		cr1 = पढ़ोl_relaxed(port->membase + ofs->cr1);
		cr3 = पढ़ोl_relaxed(port->membase + ofs->cr3);
		usartभाग = पढ़ोl_relaxed(port->membase + ofs->brr);
		usartभाग = usartभाग & GENMASK(15, 0);
		over8 = cr1 & USART_CR1_OVER8;

		अगर (over8)
			usartभाग = usartभाग | (usartभाग & GENMASK(4, 0))
				   << USART_BRR_04_R_SHIFT;

		baud = DIV_ROUND_CLOSEST(port->uartclk, usartभाग);
		sपंचांग32_usart_config_reg_rs485(&cr1, &cr3,
					     rs485conf->delay_rts_beक्रमe_send,
					     rs485conf->delay_rts_after_send,
					     baud);

		अगर (rs485conf->flags & SER_RS485_RTS_ON_SEND) अणु
			cr3 &= ~USART_CR3_DEP;
			rs485conf->flags &= ~SER_RS485_RTS_AFTER_SEND;
		पूर्ण अन्यथा अणु
			cr3 |= USART_CR3_DEP;
			rs485conf->flags |= SER_RS485_RTS_AFTER_SEND;
		पूर्ण

		ग_लिखोl_relaxed(cr3, port->membase + ofs->cr3);
		ग_लिखोl_relaxed(cr1, port->membase + ofs->cr1);
	पूर्ण अन्यथा अणु
		sपंचांग32_usart_clr_bits(port, ofs->cr3,
				     USART_CR3_DEM | USART_CR3_DEP);
		sपंचांग32_usart_clr_bits(port, ofs->cr1,
				     USART_CR1_DEDT_MASK | USART_CR1_DEAT_MASK);
	पूर्ण

	sपंचांग32_usart_set_bits(port, ofs->cr1, BIT(cfg->uart_enable_bit));

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_usart_init_rs485(काष्ठा uart_port *port,
				  काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा serial_rs485 *rs485conf = &port->rs485;

	rs485conf->flags = 0;
	rs485conf->delay_rts_beक्रमe_send = 0;
	rs485conf->delay_rts_after_send = 0;

	अगर (!pdev->dev.of_node)
		वापस -ENODEV;

	वापस uart_get_rs485_mode(port);
पूर्ण

अटल पूर्णांक sपंचांग32_usart_pending_rx(काष्ठा uart_port *port, u32 *sr,
				  पूर्णांक *last_res, bool thपढ़ोed)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;
	क्रमागत dma_status status;
	काष्ठा dma_tx_state state;

	*sr = पढ़ोl_relaxed(port->membase + ofs->isr);

	अगर (thपढ़ोed && sपंचांग32_port->rx_ch) अणु
		status = dmaengine_tx_status(sपंचांग32_port->rx_ch,
					     sपंचांग32_port->rx_ch->cookie,
					     &state);
		अगर (status == DMA_IN_PROGRESS && (*last_res != state.residue))
			वापस 1;
		अन्यथा
			वापस 0;
	पूर्ण अन्यथा अगर (*sr & USART_SR_RXNE) अणु
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ sपंचांग32_usart_get_अक्षर(काष्ठा uart_port *port, u32 *sr,
					  पूर्णांक *last_res)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;
	अचिन्हित दीर्घ c;

	अगर (sपंचांग32_port->rx_ch) अणु
		c = sपंचांग32_port->rx_buf[RX_BUF_L - (*last_res)--];
		अगर ((*last_res) == 0)
			*last_res = RX_BUF_L;
	पूर्ण अन्यथा अणु
		c = पढ़ोl_relaxed(port->membase + ofs->rdr);
		/* apply RDR data mask */
		c &= sपंचांग32_port->rdr_mask;
	पूर्ण

	वापस c;
पूर्ण

अटल व्योम sपंचांग32_usart_receive_अक्षरs(काष्ठा uart_port *port, bool thपढ़ोed)
अणु
	काष्ठा tty_port *tport = &port->state->port;
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;
	अचिन्हित दीर्घ c;
	u32 sr;
	अक्षर flag;

	spin_lock(&port->lock);

	जबतक (sपंचांग32_usart_pending_rx(port, &sr, &sपंचांग32_port->last_res,
				      thपढ़ोed)) अणु
		sr |= USART_SR_DUMMY_RX;
		flag = TTY_NORMAL;

		/*
		 * Status bits has to be cleared beक्रमe पढ़ोing the RDR:
		 * In FIFO mode, पढ़ोing the RDR will pop the next data
		 * (अगर any) aदीर्घ with its status bits पूर्णांकo the SR.
		 * Not करोing so leads to misalignement between RDR and SR,
		 * and clear status bits of the next rx data.
		 *
		 * Clear errors flags क्रम sपंचांग32f7 and sपंचांग32h7 compatible
		 * devices. On sपंचांग32f4 compatible devices, the error bit is
		 * cleared by the sequence [पढ़ो SR - पढ़ो DR].
		 */
		अगर ((sr & USART_SR_ERR_MASK) && ofs->icr != UNDEF_REG)
			ग_लिखोl_relaxed(sr & USART_SR_ERR_MASK,
				       port->membase + ofs->icr);

		c = sपंचांग32_usart_get_अक्षर(port, &sr, &sपंचांग32_port->last_res);
		port->icount.rx++;
		अगर (sr & USART_SR_ERR_MASK) अणु
			अगर (sr & USART_SR_ORE) अणु
				port->icount.overrun++;
			पूर्ण अन्यथा अगर (sr & USART_SR_PE) अणु
				port->icount.parity++;
			पूर्ण अन्यथा अगर (sr & USART_SR_FE) अणु
				/* Break detection अगर अक्षरacter is null */
				अगर (!c) अणु
					port->icount.brk++;
					अगर (uart_handle_अवरोध(port))
						जारी;
				पूर्ण अन्यथा अणु
					port->icount.frame++;
				पूर्ण
			पूर्ण

			sr &= port->पढ़ो_status_mask;

			अगर (sr & USART_SR_PE) अणु
				flag = TTY_PARITY;
			पूर्ण अन्यथा अगर (sr & USART_SR_FE) अणु
				अगर (!c)
					flag = TTY_BREAK;
				अन्यथा
					flag = TTY_FRAME;
			पूर्ण
		पूर्ण

		अगर (uart_prepare_sysrq_अक्षर(port, c))
			जारी;
		uart_insert_अक्षर(port, sr, USART_SR_ORE, c, flag);
	पूर्ण

	uart_unlock_and_check_sysrq(port);

	tty_flip_buffer_push(tport);
पूर्ण

अटल व्योम sपंचांग32_usart_tx_dma_complete(व्योम *arg)
अणु
	काष्ठा uart_port *port = arg;
	काष्ठा sपंचांग32_port *sपंचांग32port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32port->info->ofs;
	अचिन्हित दीर्घ flags;

	dmaengine_terminate_async(sपंचांग32port->tx_ch);
	sपंचांग32_usart_clr_bits(port, ofs->cr3, USART_CR3_DMAT);
	sपंचांग32port->tx_dma_busy = false;

	/* Let's see अगर we have pending data to send */
	spin_lock_irqsave(&port->lock, flags);
	sपंचांग32_usart_transmit_अक्षरs(port);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम sपंचांग32_usart_tx_पूर्णांकerrupt_enable(काष्ठा uart_port *port)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;

	/*
	 * Enables TX FIFO threashold irq when FIFO is enabled,
	 * or TX empty irq when FIFO is disabled
	 */
	अगर (sपंचांग32_port->fअगरoen && sपंचांग32_port->txftcfg >= 0)
		sपंचांग32_usart_set_bits(port, ofs->cr3, USART_CR3_TXFTIE);
	अन्यथा
		sपंचांग32_usart_set_bits(port, ofs->cr1, USART_CR1_TXEIE);
पूर्ण

अटल व्योम sपंचांग32_usart_tx_पूर्णांकerrupt_disable(काष्ठा uart_port *port)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;

	अगर (sपंचांग32_port->fअगरoen && sपंचांग32_port->txftcfg >= 0)
		sपंचांग32_usart_clr_bits(port, ofs->cr3, USART_CR3_TXFTIE);
	अन्यथा
		sपंचांग32_usart_clr_bits(port, ofs->cr1, USART_CR1_TXEIE);
पूर्ण

अटल व्योम sपंचांग32_usart_transmit_अक्षरs_pio(काष्ठा uart_port *port)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;
	काष्ठा circ_buf *xmit = &port->state->xmit;

	अगर (sपंचांग32_port->tx_dma_busy) अणु
		sपंचांग32_usart_clr_bits(port, ofs->cr3, USART_CR3_DMAT);
		sपंचांग32_port->tx_dma_busy = false;
	पूर्ण

	जबतक (!uart_circ_empty(xmit)) अणु
		/* Check that TDR is empty beक्रमe filling FIFO */
		अगर (!(पढ़ोl_relaxed(port->membase + ofs->isr) & USART_SR_TXE))
			अवरोध;
		ग_लिखोl_relaxed(xmit->buf[xmit->tail], port->membase + ofs->tdr);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
	पूर्ण

	/* rely on TXE irq (mask or unmask) क्रम sending reमुख्यing data */
	अगर (uart_circ_empty(xmit))
		sपंचांग32_usart_tx_पूर्णांकerrupt_disable(port);
	अन्यथा
		sपंचांग32_usart_tx_पूर्णांकerrupt_enable(port);
पूर्ण

अटल व्योम sपंचांग32_usart_transmit_अक्षरs_dma(काष्ठा uart_port *port)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32port->info->ofs;
	काष्ठा circ_buf *xmit = &port->state->xmit;
	काष्ठा dma_async_tx_descriptor *desc = शून्य;
	अचिन्हित पूर्णांक count, i;

	अगर (sपंचांग32port->tx_dma_busy)
		वापस;

	sपंचांग32port->tx_dma_busy = true;

	count = uart_circ_अक्षरs_pending(xmit);

	अगर (count > TX_BUF_L)
		count = TX_BUF_L;

	अगर (xmit->tail < xmit->head) अणु
		स_नकल(&sपंचांग32port->tx_buf[0], &xmit->buf[xmit->tail], count);
	पूर्ण अन्यथा अणु
		माप_प्रकार one = UART_XMIT_SIZE - xmit->tail;
		माप_प्रकार two;

		अगर (one > count)
			one = count;
		two = count - one;

		स_नकल(&sपंचांग32port->tx_buf[0], &xmit->buf[xmit->tail], one);
		अगर (two)
			स_नकल(&sपंचांग32port->tx_buf[one], &xmit->buf[0], two);
	पूर्ण

	desc = dmaengine_prep_slave_single(sपंचांग32port->tx_ch,
					   sपंचांग32port->tx_dma_buf,
					   count,
					   DMA_MEM_TO_DEV,
					   DMA_PREP_INTERRUPT);

	अगर (!desc)
		जाओ fallback_err;

	desc->callback = sपंचांग32_usart_tx_dma_complete;
	desc->callback_param = port;

	/* Push current DMA TX transaction in the pending queue */
	अगर (dma_submit_error(dmaengine_submit(desc))) अणु
		/* dma no yet started, safe to मुक्त resources */
		dmaengine_terminate_async(sपंचांग32port->tx_ch);
		जाओ fallback_err;
	पूर्ण

	/* Issue pending DMA TX requests */
	dma_async_issue_pending(sपंचांग32port->tx_ch);

	sपंचांग32_usart_set_bits(port, ofs->cr3, USART_CR3_DMAT);

	xmit->tail = (xmit->tail + count) & (UART_XMIT_SIZE - 1);
	port->icount.tx += count;
	वापस;

fallback_err:
	क्रम (i = count; i > 0; i--)
		sपंचांग32_usart_transmit_अक्षरs_pio(port);
पूर्ण

अटल व्योम sपंचांग32_usart_transmit_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;
	काष्ठा circ_buf *xmit = &port->state->xmit;

	अगर (port->x_अक्षर) अणु
		अगर (sपंचांग32_port->tx_dma_busy)
			sपंचांग32_usart_clr_bits(port, ofs->cr3, USART_CR3_DMAT);
		ग_लिखोl_relaxed(port->x_अक्षर, port->membase + ofs->tdr);
		port->x_अक्षर = 0;
		port->icount.tx++;
		अगर (sपंचांग32_port->tx_dma_busy)
			sपंचांग32_usart_set_bits(port, ofs->cr3, USART_CR3_DMAT);
		वापस;
	पूर्ण

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port)) अणु
		sपंचांग32_usart_tx_पूर्णांकerrupt_disable(port);
		वापस;
	पूर्ण

	अगर (ofs->icr == UNDEF_REG)
		sपंचांग32_usart_clr_bits(port, ofs->isr, USART_SR_TC);
	अन्यथा
		ग_लिखोl_relaxed(USART_ICR_TCCF, port->membase + ofs->icr);

	अगर (sपंचांग32_port->tx_ch)
		sपंचांग32_usart_transmit_अक्षरs_dma(port);
	अन्यथा
		sपंचांग32_usart_transmit_अक्षरs_pio(port);

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (uart_circ_empty(xmit))
		sपंचांग32_usart_tx_पूर्णांकerrupt_disable(port);
पूर्ण

अटल irqवापस_t sपंचांग32_usart_पूर्णांकerrupt(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा uart_port *port = ptr;
	काष्ठा tty_port *tport = &port->state->port;
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;
	u32 sr;

	sr = पढ़ोl_relaxed(port->membase + ofs->isr);

	अगर ((sr & USART_SR_RTOF) && ofs->icr != UNDEF_REG)
		ग_लिखोl_relaxed(USART_ICR_RTOCF,
			       port->membase + ofs->icr);

	अगर ((sr & USART_SR_WUF) && ofs->icr != UNDEF_REG) अणु
		/* Clear wake up flag and disable wake up पूर्णांकerrupt */
		ग_लिखोl_relaxed(USART_ICR_WUCF,
			       port->membase + ofs->icr);
		sपंचांग32_usart_clr_bits(port, ofs->cr3, USART_CR3_WUFIE);
		अगर (irqd_is_wakeup_set(irq_get_irq_data(port->irq)))
			pm_wakeup_event(tport->tty->dev, 0);
	पूर्ण

	अगर ((sr & USART_SR_RXNE) && !(sपंचांग32_port->rx_ch))
		sपंचांग32_usart_receive_अक्षरs(port, false);

	अगर ((sr & USART_SR_TXE) && !(sपंचांग32_port->tx_ch)) अणु
		spin_lock(&port->lock);
		sपंचांग32_usart_transmit_अक्षरs(port);
		spin_unlock(&port->lock);
	पूर्ण

	अगर (sपंचांग32_port->rx_ch)
		वापस IRQ_WAKE_THREAD;
	अन्यथा
		वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sपंचांग32_usart_thपढ़ोed_पूर्णांकerrupt(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा uart_port *port = ptr;
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);

	अगर (sपंचांग32_port->rx_ch)
		sपंचांग32_usart_receive_अक्षरs(port, true);

	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित पूर्णांक sपंचांग32_usart_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;

	अगर (पढ़ोl_relaxed(port->membase + ofs->isr) & USART_SR_TC)
		वापस TIOCSER_TEMT;

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_usart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;

	अगर ((mctrl & TIOCM_RTS) && (port->status & UPSTAT_AUTORTS))
		sपंचांग32_usart_set_bits(port, ofs->cr3, USART_CR3_RTSE);
	अन्यथा
		sपंचांग32_usart_clr_bits(port, ofs->cr3, USART_CR3_RTSE);

	mctrl_gpio_set(sपंचांग32_port->gpios, mctrl);
पूर्ण

अटल अचिन्हित पूर्णांक sपंचांग32_usart_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	अचिन्हित पूर्णांक ret;

	/* This routine is used to get संकेतs of: DCD, DSR, RI, and CTS */
	ret = TIOCM_CAR | TIOCM_DSR | TIOCM_CTS;

	वापस mctrl_gpio_get(sपंचांग32_port->gpios, &ret);
पूर्ण

अटल व्योम sपंचांग32_usart_enable_ms(काष्ठा uart_port *port)
अणु
	mctrl_gpio_enable_ms(to_sपंचांग32_port(port)->gpios);
पूर्ण

अटल व्योम sपंचांग32_usart_disable_ms(काष्ठा uart_port *port)
अणु
	mctrl_gpio_disable_ms(to_sपंचांग32_port(port)->gpios);
पूर्ण

/* Transmit stop */
अटल व्योम sपंचांग32_usart_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	काष्ठा serial_rs485 *rs485conf = &port->rs485;

	sपंचांग32_usart_tx_पूर्णांकerrupt_disable(port);

	अगर (rs485conf->flags & SER_RS485_ENABLED) अणु
		अगर (rs485conf->flags & SER_RS485_RTS_ON_SEND) अणु
			mctrl_gpio_set(sपंचांग32_port->gpios,
					sपंचांग32_port->port.mctrl & ~TIOCM_RTS);
		पूर्ण अन्यथा अणु
			mctrl_gpio_set(sपंचांग32_port->gpios,
					sपंचांग32_port->port.mctrl | TIOCM_RTS);
		पूर्ण
	पूर्ण
पूर्ण

/* There are probably अक्षरacters रुकोing to be transmitted. */
अटल व्योम sपंचांग32_usart_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	काष्ठा serial_rs485 *rs485conf = &port->rs485;
	काष्ठा circ_buf *xmit = &port->state->xmit;

	अगर (uart_circ_empty(xmit))
		वापस;

	अगर (rs485conf->flags & SER_RS485_ENABLED) अणु
		अगर (rs485conf->flags & SER_RS485_RTS_ON_SEND) अणु
			mctrl_gpio_set(sपंचांग32_port->gpios,
					sपंचांग32_port->port.mctrl | TIOCM_RTS);
		पूर्ण अन्यथा अणु
			mctrl_gpio_set(sपंचांग32_port->gpios,
					sपंचांग32_port->port.mctrl & ~TIOCM_RTS);
		पूर्ण
	पूर्ण

	sपंचांग32_usart_transmit_अक्षरs(port);
पूर्ण

/* Flush the transmit buffer. */
अटल व्योम sपंचांग32_usart_flush_buffer(काष्ठा uart_port *port)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;

	अगर (sपंचांग32_port->tx_ch) अणु
		dmaengine_terminate_async(sपंचांग32_port->tx_ch);
		sपंचांग32_usart_clr_bits(port, ofs->cr3, USART_CR3_DMAT);
		sपंचांग32_port->tx_dma_busy = false;
	पूर्ण
पूर्ण

/* Throttle the remote when input buffer is about to overflow. */
अटल व्योम sपंचांग32_usart_throttle(काष्ठा uart_port *port)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	sपंचांग32_usart_clr_bits(port, ofs->cr1, sपंचांग32_port->cr1_irq);
	अगर (sपंचांग32_port->cr3_irq)
		sपंचांग32_usart_clr_bits(port, ofs->cr3, sपंचांग32_port->cr3_irq);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

/* Unthrottle the remote, the input buffer can now accept data. */
अटल व्योम sपंचांग32_usart_unthrottle(काष्ठा uart_port *port)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	sपंचांग32_usart_set_bits(port, ofs->cr1, sपंचांग32_port->cr1_irq);
	अगर (sपंचांग32_port->cr3_irq)
		sपंचांग32_usart_set_bits(port, ofs->cr3, sपंचांग32_port->cr3_irq);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

/* Receive stop */
अटल व्योम sपंचांग32_usart_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;

	sपंचांग32_usart_clr_bits(port, ofs->cr1, sपंचांग32_port->cr1_irq);
	अगर (sपंचांग32_port->cr3_irq)
		sपंचांग32_usart_clr_bits(port, ofs->cr3, sपंचांग32_port->cr3_irq);
पूर्ण

/* Handle अवरोधs - ignored by us */
अटल व्योम sपंचांग32_usart_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
पूर्ण

अटल पूर्णांक sपंचांग32_usart_startup(काष्ठा uart_port *port)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;
	स्थिर काष्ठा sपंचांग32_usart_config *cfg = &sपंचांग32_port->info->cfg;
	स्थिर अक्षर *name = to_platक्रमm_device(port->dev)->name;
	u32 val;
	पूर्णांक ret;

	ret = request_thपढ़ोed_irq(port->irq, sपंचांग32_usart_पूर्णांकerrupt,
				   sपंचांग32_usart_thपढ़ोed_पूर्णांकerrupt,
				   IRQF_ONESHOT | IRQF_NO_SUSPEND,
				   name, port);
	अगर (ret)
		वापस ret;

	अगर (sपंचांग32_port->swap) अणु
		val = पढ़ोl_relaxed(port->membase + ofs->cr2);
		val |= USART_CR2_SWAP;
		ग_लिखोl_relaxed(val, port->membase + ofs->cr2);
	पूर्ण

	/* RX FIFO Flush */
	अगर (ofs->rqr != UNDEF_REG)
		ग_लिखोl_relaxed(USART_RQR_RXFRQ, port->membase + ofs->rqr);

	/* RX enabling */
	val = sपंचांग32_port->cr1_irq | USART_CR1_RE | BIT(cfg->uart_enable_bit);
	sपंचांग32_usart_set_bits(port, ofs->cr1, val);

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_usart_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;
	स्थिर काष्ठा sपंचांग32_usart_config *cfg = &sपंचांग32_port->info->cfg;
	u32 val, isr;
	पूर्णांक ret;

	/* Disable modem control पूर्णांकerrupts */
	sपंचांग32_usart_disable_ms(port);

	val = USART_CR1_TXEIE | USART_CR1_TE;
	val |= sपंचांग32_port->cr1_irq | USART_CR1_RE;
	val |= BIT(cfg->uart_enable_bit);
	अगर (sपंचांग32_port->fअगरoen)
		val |= USART_CR1_FIFOEN;

	ret = पढ़ोl_relaxed_poll_समयout(port->membase + ofs->isr,
					 isr, (isr & USART_SR_TC),
					 10, 100000);

	/* Send the TC error message only when ISR_TC is not set */
	अगर (ret)
		dev_err(port->dev, "Transmission is not complete\n");

	/* flush RX & TX FIFO */
	अगर (ofs->rqr != UNDEF_REG)
		ग_लिखोl_relaxed(USART_RQR_TXFRQ | USART_RQR_RXFRQ,
			       port->membase + ofs->rqr);

	sपंचांग32_usart_clr_bits(port, ofs->cr1, val);

	मुक्त_irq(port->irq, port);
पूर्ण

अटल अचिन्हित पूर्णांक sपंचांग32_usart_get_databits(काष्ठा ktermios *termios)
अणु
	अचिन्हित पूर्णांक bits;

	tcflag_t cflag = termios->c_cflag;

	चयन (cflag & CSIZE) अणु
	/*
	 * CSIZE settings are not necessarily supported in hardware.
	 * CSIZE unsupported configurations are handled here to set word length
	 * to 8 bits word as शेष configuration and to prपूर्णांक debug message.
	 */
	हाल CS5:
		bits = 5;
		अवरोध;
	हाल CS6:
		bits = 6;
		अवरोध;
	हाल CS7:
		bits = 7;
		अवरोध;
	/* शेष including CS8 */
	शेष:
		bits = 8;
		अवरोध;
	पूर्ण

	वापस bits;
पूर्ण

अटल व्योम sपंचांग32_usart_set_termios(काष्ठा uart_port *port,
				    काष्ठा ktermios *termios,
				    काष्ठा ktermios *old)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;
	स्थिर काष्ठा sपंचांग32_usart_config *cfg = &sपंचांग32_port->info->cfg;
	काष्ठा serial_rs485 *rs485conf = &port->rs485;
	अचिन्हित पूर्णांक baud, bits;
	u32 usartभाग, mantissa, fraction, oversampling;
	tcflag_t cflag = termios->c_cflag;
	u32 cr1, cr2, cr3, isr;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!sपंचांग32_port->hw_flow_control)
		cflag &= ~CRTSCTS;

	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk / 8);

	spin_lock_irqsave(&port->lock, flags);

	ret = पढ़ोl_relaxed_poll_समयout_atomic(port->membase + ofs->isr,
						isr,
						(isr & USART_SR_TC),
						10, 100000);

	/* Send the TC error message only when ISR_TC is not set. */
	अगर (ret)
		dev_err(port->dev, "Transmission is not complete\n");

	/* Stop serial port and reset value */
	ग_लिखोl_relaxed(0, port->membase + ofs->cr1);

	/* flush RX & TX FIFO */
	अगर (ofs->rqr != UNDEF_REG)
		ग_लिखोl_relaxed(USART_RQR_TXFRQ | USART_RQR_RXFRQ,
			       port->membase + ofs->rqr);

	cr1 = USART_CR1_TE | USART_CR1_RE;
	अगर (sपंचांग32_port->fअगरoen)
		cr1 |= USART_CR1_FIFOEN;
	cr2 = sपंचांग32_port->swap ? USART_CR2_SWAP : 0;

	/* Tx and RX FIFO configuration */
	cr3 = पढ़ोl_relaxed(port->membase + ofs->cr3);
	cr3 &= USART_CR3_TXFTIE | USART_CR3_RXFTIE;
	अगर (sपंचांग32_port->fअगरoen) अणु
		अगर (sपंचांग32_port->txftcfg >= 0)
			cr3 |= sपंचांग32_port->txftcfg << USART_CR3_TXFTCFG_SHIFT;
		अगर (sपंचांग32_port->rxftcfg >= 0)
			cr3 |= sपंचांग32_port->rxftcfg << USART_CR3_RXFTCFG_SHIFT;
	पूर्ण

	अगर (cflag & CSTOPB)
		cr2 |= USART_CR2_STOP_2B;

	bits = sपंचांग32_usart_get_databits(termios);
	sपंचांग32_port->rdr_mask = (BIT(bits) - 1);

	अगर (cflag & PARENB) अणु
		bits++;
		cr1 |= USART_CR1_PCE;
	पूर्ण

	/*
	 * Word length configuration:
	 * CS8 + parity, 9 bits word aka [M1:M0] = 0b01
	 * CS7 or (CS6 + parity), 7 bits word aka [M1:M0] = 0b10
	 * CS8 or (CS7 + parity), 8 bits word aka [M1:M0] = 0b00
	 * M0 and M1 alपढ़ोy cleared by cr1 initialization.
	 */
	अगर (bits == 9)
		cr1 |= USART_CR1_M0;
	अन्यथा अगर ((bits == 7) && cfg->has_7bits_data)
		cr1 |= USART_CR1_M1;
	अन्यथा अगर (bits != 8)
		dev_dbg(port->dev, "Unsupported data bits config: %u bits\n"
			, bits);

	अगर (ofs->rtor != UNDEF_REG && (sपंचांग32_port->rx_ch ||
				       (sपंचांग32_port->fअगरoen &&
					sपंचांग32_port->rxftcfg >= 0))) अणु
		अगर (cflag & CSTOPB)
			bits = bits + 3; /* 1 start bit + 2 stop bits */
		अन्यथा
			bits = bits + 2; /* 1 start bit + 1 stop bit */

		/* RX समयout irq to occur after last stop bit + bits */
		sपंचांग32_port->cr1_irq = USART_CR1_RTOIE;
		ग_लिखोl_relaxed(bits, port->membase + ofs->rtor);
		cr2 |= USART_CR2_RTOEN;
		/* Not using dma, enable fअगरo threshold irq */
		अगर (!sपंचांग32_port->rx_ch)
			sपंचांग32_port->cr3_irq =  USART_CR3_RXFTIE;
	पूर्ण

	cr1 |= sपंचांग32_port->cr1_irq;
	cr3 |= sपंचांग32_port->cr3_irq;

	अगर (cflag & PARODD)
		cr1 |= USART_CR1_PS;

	port->status &= ~(UPSTAT_AUTOCTS | UPSTAT_AUTORTS);
	अगर (cflag & CRTSCTS) अणु
		port->status |= UPSTAT_AUTOCTS | UPSTAT_AUTORTS;
		cr3 |= USART_CR3_CTSE | USART_CR3_RTSE;
	पूर्ण

	usartभाग = DIV_ROUND_CLOSEST(port->uartclk, baud);

	/*
	 * The USART supports 16 or 8 बार oversampling.
	 * By शेष we prefer 16 बार oversampling, so that the receiver
	 * has a better tolerance to घड़ी deviations.
	 * 8 बार oversampling is only used to achieve higher speeds.
	 */
	अगर (usartभाग < 16) अणु
		oversampling = 8;
		cr1 |= USART_CR1_OVER8;
		sपंचांग32_usart_set_bits(port, ofs->cr1, USART_CR1_OVER8);
	पूर्ण अन्यथा अणु
		oversampling = 16;
		cr1 &= ~USART_CR1_OVER8;
		sपंचांग32_usart_clr_bits(port, ofs->cr1, USART_CR1_OVER8);
	पूर्ण

	mantissa = (usartभाग / oversampling) << USART_BRR_DIV_M_SHIFT;
	fraction = usartभाग % oversampling;
	ग_लिखोl_relaxed(mantissa | fraction, port->membase + ofs->brr);

	uart_update_समयout(port, cflag, baud);

	port->पढ़ो_status_mask = USART_SR_ORE;
	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= USART_SR_PE | USART_SR_FE;
	अगर (termios->c_अगरlag & (IGNBRK | BRKINT | PARMRK))
		port->पढ़ो_status_mask |= USART_SR_FE;

	/* Characters to ignore */
	port->ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		port->ignore_status_mask = USART_SR_PE | USART_SR_FE;
	अगर (termios->c_अगरlag & IGNBRK) अणु
		port->ignore_status_mask |= USART_SR_FE;
		/*
		 * If we're ignoring parity and अवरोध indicators,
		 * ignore overruns too (क्रम real raw support).
		 */
		अगर (termios->c_अगरlag & IGNPAR)
			port->ignore_status_mask |= USART_SR_ORE;
	पूर्ण

	/* Ignore all अक्षरacters अगर CREAD is not set */
	अगर ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= USART_SR_DUMMY_RX;

	अगर (sपंचांग32_port->rx_ch)
		cr3 |= USART_CR3_DMAR;

	अगर (rs485conf->flags & SER_RS485_ENABLED) अणु
		sपंचांग32_usart_config_reg_rs485(&cr1, &cr3,
					     rs485conf->delay_rts_beक्रमe_send,
					     rs485conf->delay_rts_after_send,
					     baud);
		अगर (rs485conf->flags & SER_RS485_RTS_ON_SEND) अणु
			cr3 &= ~USART_CR3_DEP;
			rs485conf->flags &= ~SER_RS485_RTS_AFTER_SEND;
		पूर्ण अन्यथा अणु
			cr3 |= USART_CR3_DEP;
			rs485conf->flags |= SER_RS485_RTS_AFTER_SEND;
		पूर्ण

	पूर्ण अन्यथा अणु
		cr3 &= ~(USART_CR3_DEM | USART_CR3_DEP);
		cr1 &= ~(USART_CR1_DEDT_MASK | USART_CR1_DEAT_MASK);
	पूर्ण

	/* Configure wake up from low घातer on start bit detection */
	अगर (sपंचांग32_port->wakeup_src) अणु
		cr3 &= ~USART_CR3_WUS_MASK;
		cr3 |= USART_CR3_WUS_START_BIT;
	पूर्ण

	ग_लिखोl_relaxed(cr3, port->membase + ofs->cr3);
	ग_लिखोl_relaxed(cr2, port->membase + ofs->cr2);
	ग_लिखोl_relaxed(cr1, port->membase + ofs->cr1);

	sपंचांग32_usart_set_bits(port, ofs->cr1, BIT(cfg->uart_enable_bit));
	spin_unlock_irqrestore(&port->lock, flags);

	/* Handle modem control पूर्णांकerrupts */
	अगर (UART_ENABLE_MS(port, termios->c_cflag))
		sपंचांग32_usart_enable_ms(port);
	अन्यथा
		sपंचांग32_usart_disable_ms(port);
पूर्ण

अटल स्थिर अक्षर *sपंचांग32_usart_type(काष्ठा uart_port *port)
अणु
	वापस (port->type == PORT_STM32) ? DRIVER_NAME : शून्य;
पूर्ण

अटल व्योम sपंचांग32_usart_release_port(काष्ठा uart_port *port)
अणु
पूर्ण

अटल पूर्णांक sपंचांग32_usart_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_usart_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE)
		port->type = PORT_STM32;
पूर्ण

अटल पूर्णांक
sपंचांग32_usart_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	/* No user changeable parameters */
	वापस -EINVAL;
पूर्ण

अटल व्योम sपंचांग32_usart_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state,
			   अचिन्हित पूर्णांक oldstate)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32port = container_of(port,
			काष्ठा sपंचांग32_port, port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32port->info->ofs;
	स्थिर काष्ठा sपंचांग32_usart_config *cfg = &sपंचांग32port->info->cfg;
	अचिन्हित दीर्घ flags = 0;

	चयन (state) अणु
	हाल UART_PM_STATE_ON:
		pm_runसमय_get_sync(port->dev);
		अवरोध;
	हाल UART_PM_STATE_OFF:
		spin_lock_irqsave(&port->lock, flags);
		sपंचांग32_usart_clr_bits(port, ofs->cr1, BIT(cfg->uart_enable_bit));
		spin_unlock_irqrestore(&port->lock, flags);
		pm_runसमय_put_sync(port->dev);
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा uart_ops sपंचांग32_uart_ops = अणु
	.tx_empty	= sपंचांग32_usart_tx_empty,
	.set_mctrl	= sपंचांग32_usart_set_mctrl,
	.get_mctrl	= sपंचांग32_usart_get_mctrl,
	.stop_tx	= sपंचांग32_usart_stop_tx,
	.start_tx	= sपंचांग32_usart_start_tx,
	.throttle	= sपंचांग32_usart_throttle,
	.unthrottle	= sपंचांग32_usart_unthrottle,
	.stop_rx	= sपंचांग32_usart_stop_rx,
	.enable_ms	= sपंचांग32_usart_enable_ms,
	.अवरोध_ctl	= sपंचांग32_usart_अवरोध_ctl,
	.startup	= sपंचांग32_usart_startup,
	.shutकरोwn	= sपंचांग32_usart_shutकरोwn,
	.flush_buffer	= sपंचांग32_usart_flush_buffer,
	.set_termios	= sपंचांग32_usart_set_termios,
	.pm		= sपंचांग32_usart_pm,
	.type		= sपंचांग32_usart_type,
	.release_port	= sपंचांग32_usart_release_port,
	.request_port	= sपंचांग32_usart_request_port,
	.config_port	= sपंचांग32_usart_config_port,
	.verअगरy_port	= sपंचांग32_usart_verअगरy_port,
पूर्ण;

/*
 * STM32H7 RX & TX FIFO threshold configuration (CR3 RXFTCFG / TXFTCFG)
 * Note: 1 isn't a valid value in RXFTCFG / TXFTCFG. In this हाल,
 * RXNEIE / TXEIE can be used instead of threshold irqs: RXFTIE / TXFTIE.
 * So, RXFTCFG / TXFTCFG bitfields values are encoded as array index + 1.
 */
अटल स्थिर u32 sपंचांग32h7_usart_fअगरo_thresh_cfg[] = अणु 1, 2, 4, 8, 12, 14, 16 पूर्ण;

अटल व्योम sपंचांग32_usart_get_ftcfg(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *p,
				  पूर्णांक *ftcfg)
अणु
	u32 bytes, i;

	/* DT option to get RX & TX FIFO threshold (शेष to 8 bytes) */
	अगर (of_property_पढ़ो_u32(pdev->dev.of_node, p, &bytes))
		bytes = 8;

	क्रम (i = 0; i < ARRAY_SIZE(sपंचांग32h7_usart_fअगरo_thresh_cfg); i++)
		अगर (sपंचांग32h7_usart_fअगरo_thresh_cfg[i] >= bytes)
			अवरोध;
	अगर (i >= ARRAY_SIZE(sपंचांग32h7_usart_fअगरo_thresh_cfg))
		i = ARRAY_SIZE(sपंचांग32h7_usart_fअगरo_thresh_cfg) - 1;

	dev_dbg(&pdev->dev, "%s set to %d bytes\n", p,
		sपंचांग32h7_usart_fअगरo_thresh_cfg[i]);

	/* Provide FIFO threshold ftcfg (1 is invalid: threshold irq unused) */
	अगर (i)
		*ftcfg = i - 1;
	अन्यथा
		*ftcfg = -EINVAL;
पूर्ण

अटल व्योम sपंचांग32_usart_deinit_port(काष्ठा sपंचांग32_port *sपंचांग32port)
अणु
	clk_disable_unprepare(sपंचांग32port->clk);
पूर्ण

अटल पूर्णांक sपंचांग32_usart_init_port(काष्ठा sपंचांग32_port *sपंचांग32port,
				 काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port = &sपंचांग32port->port;
	काष्ठा resource *res;
	पूर्णांक ret, irq;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस irq ? : -ENODEV;

	port->iotype	= UPIO_MEM;
	port->flags	= UPF_BOOT_AUTOCONF;
	port->ops	= &sपंचांग32_uart_ops;
	port->dev	= &pdev->dev;
	port->fअगरosize	= sपंचांग32port->info->cfg.fअगरosize;
	port->has_sysrq = IS_ENABLED(CONFIG_SERIAL_STM32_CONSOLE);
	port->irq = irq;
	port->rs485_config = sपंचांग32_usart_config_rs485;

	ret = sपंचांग32_usart_init_rs485(port, pdev);
	अगर (ret)
		वापस ret;

	sपंचांग32port->wakeup_src = sपंचांग32port->info->cfg.has_wakeup &&
		of_property_पढ़ो_bool(pdev->dev.of_node, "wakeup-source");

	sपंचांग32port->swap = sपंचांग32port->info->cfg.has_swap &&
		of_property_पढ़ो_bool(pdev->dev.of_node, "rx-tx-swap");

	sपंचांग32port->fअगरoen = sपंचांग32port->info->cfg.has_fअगरo;
	अगर (sपंचांग32port->fअगरoen) अणु
		sपंचांग32_usart_get_ftcfg(pdev, "rx-threshold",
				      &sपंचांग32port->rxftcfg);
		sपंचांग32_usart_get_ftcfg(pdev, "tx-threshold",
				      &sपंचांग32port->txftcfg);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	port->membase = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(port->membase))
		वापस PTR_ERR(port->membase);
	port->mapbase = res->start;

	spin_lock_init(&port->lock);

	sपंचांग32port->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(sपंचांग32port->clk))
		वापस PTR_ERR(sपंचांग32port->clk);

	/* Ensure that clk rate is correct by enabling the clk */
	ret = clk_prepare_enable(sपंचांग32port->clk);
	अगर (ret)
		वापस ret;

	sपंचांग32port->port.uartclk = clk_get_rate(sपंचांग32port->clk);
	अगर (!sपंचांग32port->port.uartclk) अणु
		ret = -EINVAL;
		जाओ err_clk;
	पूर्ण

	sपंचांग32port->gpios = mctrl_gpio_init(&sपंचांग32port->port, 0);
	अगर (IS_ERR(sपंचांग32port->gpios)) अणु
		ret = PTR_ERR(sपंचांग32port->gpios);
		जाओ err_clk;
	पूर्ण

	/*
	 * Both CTS/RTS gpios and "st,hw-flow-ctrl" (deprecated) or "uart-has-rtscts"
	 * properties should not be specअगरied.
	 */
	अगर (sपंचांग32port->hw_flow_control) अणु
		अगर (mctrl_gpio_to_gpiod(sपंचांग32port->gpios, UART_GPIO_CTS) ||
		    mctrl_gpio_to_gpiod(sपंचांग32port->gpios, UART_GPIO_RTS)) अणु
			dev_err(&pdev->dev, "Conflicting RTS/CTS config\n");
			ret = -EINVAL;
			जाओ err_clk;
		पूर्ण
	पूर्ण

	वापस ret;

err_clk:
	clk_disable_unprepare(sपंचांग32port->clk);

	वापस ret;
पूर्ण

अटल काष्ठा sपंचांग32_port *sपंचांग32_usart_of_get_port(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक id;

	अगर (!np)
		वापस शून्य;

	id = of_alias_get_id(np, "serial");
	अगर (id < 0) अणु
		dev_err(&pdev->dev, "failed to get alias id, errno %d\n", id);
		वापस शून्य;
	पूर्ण

	अगर (WARN_ON(id >= STM32_MAX_PORTS))
		वापस शून्य;

	sपंचांग32_ports[id].hw_flow_control =
		of_property_पढ़ो_bool (np, "st,hw-flow-ctrl") /*deprecated*/ ||
		of_property_पढ़ो_bool (np, "uart-has-rtscts");
	sपंचांग32_ports[id].port.line = id;
	sपंचांग32_ports[id].cr1_irq = USART_CR1_RXNEIE;
	sपंचांग32_ports[id].cr3_irq = 0;
	sपंचांग32_ports[id].last_res = RX_BUF_L;
	वापस &sपंचांग32_ports[id];
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id sपंचांग32_match[] = अणु
	अणु .compatible = "st,stm32-uart", .data = &sपंचांग32f4_infoपूर्ण,
	अणु .compatible = "st,stm32f7-uart", .data = &sपंचांग32f7_infoपूर्ण,
	अणु .compatible = "st,stm32h7-uart", .data = &sपंचांग32h7_infoपूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, sपंचांग32_match);
#पूर्ण_अगर

अटल पूर्णांक sपंचांग32_usart_of_dma_rx_probe(काष्ठा sपंचांग32_port *sपंचांग32port,
				       काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32port->info->ofs;
	काष्ठा uart_port *port = &sपंचांग32port->port;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dma_slave_config config;
	काष्ठा dma_async_tx_descriptor *desc = शून्य;
	पूर्णांक ret;

	/*
	 * Using DMA and thपढ़ोed handler क्रम the console could lead to
	 * deadlocks.
	 */
	अगर (uart_console(port))
		वापस -ENODEV;

	/* Request DMA RX channel */
	sपंचांग32port->rx_ch = dma_request_slave_channel(dev, "rx");
	अगर (!sपंचांग32port->rx_ch) अणु
		dev_info(dev, "rx dma alloc failed\n");
		वापस -ENODEV;
	पूर्ण
	sपंचांग32port->rx_buf = dma_alloc_coherent(&pdev->dev, RX_BUF_L,
					       &sपंचांग32port->rx_dma_buf,
					       GFP_KERNEL);
	अगर (!sपंचांग32port->rx_buf) अणु
		ret = -ENOMEM;
		जाओ alloc_err;
	पूर्ण

	/* Configure DMA channel */
	स_रखो(&config, 0, माप(config));
	config.src_addr = port->mapbase + ofs->rdr;
	config.src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;

	ret = dmaengine_slave_config(sपंचांग32port->rx_ch, &config);
	अगर (ret < 0) अणु
		dev_err(dev, "rx dma channel config failed\n");
		ret = -ENODEV;
		जाओ config_err;
	पूर्ण

	/* Prepare a DMA cyclic transaction */
	desc = dmaengine_prep_dma_cyclic(sपंचांग32port->rx_ch,
					 sपंचांग32port->rx_dma_buf,
					 RX_BUF_L, RX_BUF_P, DMA_DEV_TO_MEM,
					 DMA_PREP_INTERRUPT);
	अगर (!desc) अणु
		dev_err(dev, "rx dma prep cyclic failed\n");
		ret = -ENODEV;
		जाओ config_err;
	पूर्ण

	/* No callback as dma buffer is drained on usart पूर्णांकerrupt */
	desc->callback = शून्य;
	desc->callback_param = शून्य;

	/* Push current DMA transaction in the pending queue */
	ret = dma_submit_error(dmaengine_submit(desc));
	अगर (ret) अणु
		dmaengine_terminate_sync(sपंचांग32port->rx_ch);
		जाओ config_err;
	पूर्ण

	/* Issue pending DMA requests */
	dma_async_issue_pending(sपंचांग32port->rx_ch);

	वापस 0;

config_err:
	dma_मुक्त_coherent(&pdev->dev,
			  RX_BUF_L, sपंचांग32port->rx_buf,
			  sपंचांग32port->rx_dma_buf);

alloc_err:
	dma_release_channel(sपंचांग32port->rx_ch);
	sपंचांग32port->rx_ch = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_usart_of_dma_tx_probe(काष्ठा sपंचांग32_port *sपंचांग32port,
				       काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32port->info->ofs;
	काष्ठा uart_port *port = &sपंचांग32port->port;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dma_slave_config config;
	पूर्णांक ret;

	sपंचांग32port->tx_dma_busy = false;

	/* Request DMA TX channel */
	sपंचांग32port->tx_ch = dma_request_slave_channel(dev, "tx");
	अगर (!sपंचांग32port->tx_ch) अणु
		dev_info(dev, "tx dma alloc failed\n");
		वापस -ENODEV;
	पूर्ण
	sपंचांग32port->tx_buf = dma_alloc_coherent(&pdev->dev, TX_BUF_L,
					       &sपंचांग32port->tx_dma_buf,
					       GFP_KERNEL);
	अगर (!sपंचांग32port->tx_buf) अणु
		ret = -ENOMEM;
		जाओ alloc_err;
	पूर्ण

	/* Configure DMA channel */
	स_रखो(&config, 0, माप(config));
	config.dst_addr = port->mapbase + ofs->tdr;
	config.dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;

	ret = dmaengine_slave_config(sपंचांग32port->tx_ch, &config);
	अगर (ret < 0) अणु
		dev_err(dev, "tx dma channel config failed\n");
		ret = -ENODEV;
		जाओ config_err;
	पूर्ण

	वापस 0;

config_err:
	dma_मुक्त_coherent(&pdev->dev,
			  TX_BUF_L, sपंचांग32port->tx_buf,
			  sपंचांग32port->tx_dma_buf);

alloc_err:
	dma_release_channel(sपंचांग32port->tx_ch);
	sपंचांग32port->tx_ch = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_usart_serial_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32port;
	पूर्णांक ret;

	sपंचांग32port = sपंचांग32_usart_of_get_port(pdev);
	अगर (!sपंचांग32port)
		वापस -ENODEV;

	sपंचांग32port->info = of_device_get_match_data(&pdev->dev);
	अगर (!sपंचांग32port->info)
		वापस -EINVAL;

	ret = sपंचांग32_usart_init_port(sपंचांग32port, pdev);
	अगर (ret)
		वापस ret;

	अगर (sपंचांग32port->wakeup_src) अणु
		device_set_wakeup_capable(&pdev->dev, true);
		ret = dev_pm_set_wake_irq(&pdev->dev, sपंचांग32port->port.irq);
		अगर (ret)
			जाओ err_nowup;
	पूर्ण

	ret = sपंचांग32_usart_of_dma_rx_probe(sपंचांग32port, pdev);
	अगर (ret)
		dev_info(&pdev->dev, "interrupt mode used for rx (no dma)\n");

	ret = sपंचांग32_usart_of_dma_tx_probe(sपंचांग32port, pdev);
	अगर (ret)
		dev_info(&pdev->dev, "interrupt mode used for tx (no dma)\n");

	platक्रमm_set_drvdata(pdev, &sपंचांग32port->port);

	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	ret = uart_add_one_port(&sपंचांग32_usart_driver, &sपंचांग32port->port);
	अगर (ret)
		जाओ err_port;

	pm_runसमय_put_sync(&pdev->dev);

	वापस 0;

err_port:
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);

	अगर (sपंचांग32port->rx_ch) अणु
		dmaengine_terminate_async(sपंचांग32port->rx_ch);
		dma_release_channel(sपंचांग32port->rx_ch);
	पूर्ण

	अगर (sपंचांग32port->rx_dma_buf)
		dma_मुक्त_coherent(&pdev->dev,
				  RX_BUF_L, sपंचांग32port->rx_buf,
				  sपंचांग32port->rx_dma_buf);

	अगर (sपंचांग32port->tx_ch) अणु
		dmaengine_terminate_async(sपंचांग32port->tx_ch);
		dma_release_channel(sपंचांग32port->tx_ch);
	पूर्ण

	अगर (sपंचांग32port->tx_dma_buf)
		dma_मुक्त_coherent(&pdev->dev,
				  TX_BUF_L, sपंचांग32port->tx_buf,
				  sपंचांग32port->tx_dma_buf);

	अगर (sपंचांग32port->wakeup_src)
		dev_pm_clear_wake_irq(&pdev->dev);

err_nowup:
	अगर (sपंचांग32port->wakeup_src)
		device_set_wakeup_capable(&pdev->dev, false);

	sपंचांग32_usart_deinit_port(sपंचांग32port);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_usart_serial_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port = platक्रमm_get_drvdata(pdev);
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;
	पूर्णांक err;

	pm_runसमय_get_sync(&pdev->dev);
	err = uart_हटाओ_one_port(&sपंचांग32_usart_driver, port);
	अगर (err)
		वापस(err);

	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_put_noidle(&pdev->dev);

	sपंचांग32_usart_clr_bits(port, ofs->cr3, USART_CR3_DMAR);

	अगर (sपंचांग32_port->rx_ch) अणु
		dmaengine_terminate_async(sपंचांग32_port->rx_ch);
		dma_release_channel(sपंचांग32_port->rx_ch);
	पूर्ण

	अगर (sपंचांग32_port->rx_dma_buf)
		dma_मुक्त_coherent(&pdev->dev,
				  RX_BUF_L, sपंचांग32_port->rx_buf,
				  sपंचांग32_port->rx_dma_buf);

	sपंचांग32_usart_clr_bits(port, ofs->cr3, USART_CR3_DMAT);

	अगर (sपंचांग32_port->tx_ch) अणु
		dmaengine_terminate_async(sपंचांग32_port->tx_ch);
		dma_release_channel(sपंचांग32_port->tx_ch);
	पूर्ण

	अगर (sपंचांग32_port->tx_dma_buf)
		dma_मुक्त_coherent(&pdev->dev,
				  TX_BUF_L, sपंचांग32_port->tx_buf,
				  sपंचांग32_port->tx_dma_buf);

	अगर (sपंचांग32_port->wakeup_src) अणु
		dev_pm_clear_wake_irq(&pdev->dev);
		device_init_wakeup(&pdev->dev, false);
	पूर्ण

	sपंचांग32_usart_deinit_port(sपंचांग32_port);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SERIAL_STM32_CONSOLE
अटल व्योम sपंचांग32_usart_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;

	जबतक (!(पढ़ोl_relaxed(port->membase + ofs->isr) & USART_SR_TXE))
		cpu_relax();

	ग_लिखोl_relaxed(ch, port->membase + ofs->tdr);
पूर्ण

अटल व्योम sपंचांग32_usart_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				      अचिन्हित पूर्णांक cnt)
अणु
	काष्ठा uart_port *port = &sपंचांग32_ports[co->index].port;
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;
	स्थिर काष्ठा sपंचांग32_usart_config *cfg = &sपंचांग32_port->info->cfg;
	अचिन्हित दीर्घ flags;
	u32 old_cr1, new_cr1;
	पूर्णांक locked = 1;

	अगर (oops_in_progress)
		locked = spin_trylock_irqsave(&port->lock, flags);
	अन्यथा
		spin_lock_irqsave(&port->lock, flags);

	/* Save and disable पूर्णांकerrupts, enable the transmitter */
	old_cr1 = पढ़ोl_relaxed(port->membase + ofs->cr1);
	new_cr1 = old_cr1 & ~USART_CR1_IE_MASK;
	new_cr1 |=  USART_CR1_TE | BIT(cfg->uart_enable_bit);
	ग_लिखोl_relaxed(new_cr1, port->membase + ofs->cr1);

	uart_console_ग_लिखो(port, s, cnt, sपंचांग32_usart_console_अक्षर_दो);

	/* Restore पूर्णांकerrupt state */
	ग_लिखोl_relaxed(old_cr1, port->membase + ofs->cr1);

	अगर (locked)
		spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल पूर्णांक sपंचांग32_usart_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32port;
	पूर्णांक baud = 9600;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (co->index >= STM32_MAX_PORTS)
		वापस -ENODEV;

	sपंचांग32port = &sपंचांग32_ports[co->index];

	/*
	 * This driver करोes not support early console initialization
	 * (use ARM early prपूर्णांकk support instead), so we only expect
	 * this to be called during the uart port registration when the
	 * driver माला_लो probed and the port should be mapped at that poपूर्णांक.
	 */
	अगर (sपंचांग32port->port.mapbase == 0 || !sपंचांग32port->port.membase)
		वापस -ENXIO;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(&sपंचांग32port->port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा console sपंचांग32_console = अणु
	.name		= STM32_SERIAL_NAME,
	.device		= uart_console_device,
	.ग_लिखो		= sपंचांग32_usart_console_ग_लिखो,
	.setup		= sपंचांग32_usart_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &sपंचांग32_usart_driver,
पूर्ण;

#घोषणा STM32_SERIAL_CONSOLE (&sपंचांग32_console)

#अन्यथा
#घोषणा STM32_SERIAL_CONSOLE शून्य
#पूर्ण_अगर /* CONFIG_SERIAL_STM32_CONSOLE */

अटल काष्ठा uart_driver sपंचांग32_usart_driver = अणु
	.driver_name	= DRIVER_NAME,
	.dev_name	= STM32_SERIAL_NAME,
	.major		= 0,
	.minor		= 0,
	.nr		= STM32_MAX_PORTS,
	.cons		= STM32_SERIAL_CONSOLE,
पूर्ण;

अटल व्योम __maybe_unused sपंचांग32_usart_serial_en_wakeup(काष्ठा uart_port *port,
							bool enable)
अणु
	काष्ठा sपंचांग32_port *sपंचांग32_port = to_sपंचांग32_port(port);
	स्थिर काष्ठा sपंचांग32_usart_offsets *ofs = &sपंचांग32_port->info->ofs;

	अगर (!sपंचांग32_port->wakeup_src)
		वापस;

	/*
	 * Enable low-घातer wake-up and wake-up irq अगर argument is set to
	 * "enable", disable low-घातer wake-up and wake-up irq otherwise
	 */
	अगर (enable) अणु
		sपंचांग32_usart_set_bits(port, ofs->cr1, USART_CR1_UESM);
		sपंचांग32_usart_set_bits(port, ofs->cr3, USART_CR3_WUFIE);
	पूर्ण अन्यथा अणु
		sपंचांग32_usart_clr_bits(port, ofs->cr1, USART_CR1_UESM);
		sपंचांग32_usart_clr_bits(port, ofs->cr3, USART_CR3_WUFIE);
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_usart_serial_suspend(काष्ठा device *dev)
अणु
	काष्ठा uart_port *port = dev_get_drvdata(dev);

	uart_suspend_port(&sपंचांग32_usart_driver, port);

	अगर (device_may_wakeup(dev) || device_wakeup_path(dev))
		sपंचांग32_usart_serial_en_wakeup(port, true);

	/*
	 * When "no_console_suspend" is enabled, keep the pinctrl शेष state
	 * and rely on bootloader stage to restore this state upon resume.
	 * Otherwise, apply the idle or sleep states depending on wakeup
	 * capabilities.
	 */
	अगर (console_suspend_enabled || !uart_console(port)) अणु
		अगर (device_may_wakeup(dev) || device_wakeup_path(dev))
			pinctrl_pm_select_idle_state(dev);
		अन्यथा
			pinctrl_pm_select_sleep_state(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_usart_serial_resume(काष्ठा device *dev)
अणु
	काष्ठा uart_port *port = dev_get_drvdata(dev);

	pinctrl_pm_select_शेष_state(dev);

	अगर (device_may_wakeup(dev) || device_wakeup_path(dev))
		sपंचांग32_usart_serial_en_wakeup(port, false);

	वापस uart_resume_port(&sपंचांग32_usart_driver, port);
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_usart_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा uart_port *port = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_port *sपंचांग32port = container_of(port,
			काष्ठा sपंचांग32_port, port);

	clk_disable_unprepare(sपंचांग32port->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_usart_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा uart_port *port = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_port *sपंचांग32port = container_of(port,
			काष्ठा sपंचांग32_port, port);

	वापस clk_prepare_enable(sपंचांग32port->clk);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_serial_pm_ops = अणु
	SET_RUNTIME_PM_OPS(sपंचांग32_usart_runसमय_suspend,
			   sपंचांग32_usart_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(sपंचांग32_usart_serial_suspend,
				sपंचांग32_usart_serial_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver sपंचांग32_serial_driver = अणु
	.probe		= sपंचांग32_usart_serial_probe,
	.हटाओ		= sपंचांग32_usart_serial_हटाओ,
	.driver	= अणु
		.name	= DRIVER_NAME,
		.pm	= &sपंचांग32_serial_pm_ops,
		.of_match_table = of_match_ptr(sपंचांग32_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sपंचांग32_usart_init(व्योम)
अणु
	अटल अक्षर banner[] __initdata = "STM32 USART driver initialized";
	पूर्णांक ret;

	pr_info("%s\n", banner);

	ret = uart_रेजिस्टर_driver(&sपंचांग32_usart_driver);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&sपंचांग32_serial_driver);
	अगर (ret)
		uart_unरेजिस्टर_driver(&sपंचांग32_usart_driver);

	वापस ret;
पूर्ण

अटल व्योम __निकास sपंचांग32_usart_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sपंचांग32_serial_driver);
	uart_unरेजिस्टर_driver(&sपंचांग32_usart_driver);
पूर्ण

module_init(sपंचांग32_usart_init);
module_निकास(sपंचांग32_usart_निकास);

MODULE_ALIAS("platform:" DRIVER_NAME);
MODULE_DESCRIPTION("STMicroelectronics STM32 serial port driver");
MODULE_LICENSE("GPL v2");
