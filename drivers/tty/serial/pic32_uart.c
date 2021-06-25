<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * PIC32 Integrated Serial Driver.
 *
 * Copyright (C) 2015 Microchip Technology, Inc.
 *
 * Authors:
 *   Sorin-Andrei Pistirica <andrei.pistirica@microchip.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/console.h>
#समावेश <linux/clk.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/mach-pic32/pic32.h>
#समावेश "pic32_uart.h"

/* UART name and device definitions */
#घोषणा PIC32_DEV_NAME		"pic32-uart"
#घोषणा PIC32_MAX_UARTS		6
#घोषणा PIC32_SDEV_NAME		"ttyPIC"

/* pic32_sport poपूर्णांकer क्रम console use */
अटल काष्ठा pic32_sport *pic32_sports[PIC32_MAX_UARTS];

अटल अंतरभूत व्योम pic32_रुको_deplete_txbuf(काष्ठा pic32_sport *sport)
अणु
	/* रुको क्रम tx empty, otherwise अक्षरs will be lost or corrupted */
	जबतक (!(pic32_uart_पढ़ोl(sport, PIC32_UART_STA) & PIC32_UART_STA_TRMT))
		udelay(1);
पूर्ण

अटल अंतरभूत पूर्णांक pic32_enable_घड़ी(काष्ठा pic32_sport *sport)
अणु
	पूर्णांक ret = clk_prepare_enable(sport->clk);

	अगर (ret)
		वापस ret;

	sport->ref_clk++;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम pic32_disable_घड़ी(काष्ठा pic32_sport *sport)
अणु
	sport->ref_clk--;
	clk_disable_unprepare(sport->clk);
पूर्ण

/* serial core request to check अगर uart tx buffer is empty */
अटल अचिन्हित पूर्णांक pic32_uart_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा pic32_sport *sport = to_pic32_sport(port);
	u32 val = pic32_uart_पढ़ोl(sport, PIC32_UART_STA);

	वापस (val & PIC32_UART_STA_TRMT) ? 1 : 0;
पूर्ण

/* serial core request to set UART outमाला_दो */
अटल व्योम pic32_uart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा pic32_sport *sport = to_pic32_sport(port);

	/* set loopback mode */
	अगर (mctrl & TIOCM_LOOP)
		pic32_uart_ग_लिखोl(sport, PIC32_SET(PIC32_UART_MODE),
					PIC32_UART_MODE_LPBK);
	अन्यथा
		pic32_uart_ग_लिखोl(sport, PIC32_CLR(PIC32_UART_MODE),
					PIC32_UART_MODE_LPBK);
पूर्ण

/* get the state of CTS input pin क्रम this port */
अटल अचिन्हित पूर्णांक get_cts_state(काष्ठा pic32_sport *sport)
अणु
	/* पढ़ो and invert UxCTS */
	अगर (gpio_is_valid(sport->cts_gpio))
		वापस !gpio_get_value(sport->cts_gpio);

	वापस 1;
पूर्ण

/* serial core request to वापस the state of misc UART input pins */
अटल अचिन्हित पूर्णांक pic32_uart_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा pic32_sport *sport = to_pic32_sport(port);
	अचिन्हित पूर्णांक mctrl = 0;

	अगर (!sport->hw_flow_ctrl)
		mctrl |= TIOCM_CTS;
	अन्यथा अगर (get_cts_state(sport))
		mctrl |= TIOCM_CTS;

	/* DSR and CD are not supported in PIC32, so वापस 1
	 * RI is not supported in PIC32, so वापस 0
	 */
	mctrl |= TIOCM_CD;
	mctrl |= TIOCM_DSR;

	वापस mctrl;
पूर्ण

/* stop tx and start tx are not called in pairs, thereक्रमe a flag indicates
 * the status of irq to control the irq-depth.
 */
अटल अंतरभूत व्योम pic32_uart_irqtxen(काष्ठा pic32_sport *sport, u8 en)
अणु
	अगर (en && !tx_irq_enabled(sport)) अणु
		enable_irq(sport->irq_tx);
		tx_irq_enabled(sport) = 1;
	पूर्ण अन्यथा अगर (!en && tx_irq_enabled(sport)) अणु
		/* use disable_irq_nosync() and not disable_irq() to aव्योम self
		 * imposed deadlock by not रुकोing क्रम irq handler to end,
		 * since this callback is called from पूर्णांकerrupt context.
		 */
		disable_irq_nosync(sport->irq_tx);
		tx_irq_enabled(sport) = 0;
	पूर्ण
पूर्ण

/* serial core request to disable tx ASAP (used क्रम flow control) */
अटल व्योम pic32_uart_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा pic32_sport *sport = to_pic32_sport(port);

	अगर (!(pic32_uart_पढ़ोl(sport, PIC32_UART_MODE) & PIC32_UART_MODE_ON))
		वापस;

	अगर (!(pic32_uart_पढ़ोl(sport, PIC32_UART_STA) & PIC32_UART_STA_UTXEN))
		वापस;

	/* रुको क्रम tx empty */
	pic32_रुको_deplete_txbuf(sport);

	pic32_uart_ग_लिखोl(sport, PIC32_CLR(PIC32_UART_STA),
				PIC32_UART_STA_UTXEN);
	pic32_uart_irqtxen(sport, 0);
पूर्ण

/* serial core request to (re)enable tx */
अटल व्योम pic32_uart_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा pic32_sport *sport = to_pic32_sport(port);

	pic32_uart_irqtxen(sport, 1);
	pic32_uart_ग_लिखोl(sport, PIC32_SET(PIC32_UART_STA),
				PIC32_UART_STA_UTXEN);
पूर्ण

/* serial core request to stop rx, called beक्रमe port shutकरोwn */
अटल व्योम pic32_uart_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा pic32_sport *sport = to_pic32_sport(port);

	/* disable rx पूर्णांकerrupts */
	disable_irq(sport->irq_rx);

	/* receiver Enable bit OFF */
	pic32_uart_ग_लिखोl(sport, PIC32_CLR(PIC32_UART_STA),
				PIC32_UART_STA_URXEN);
पूर्ण

/* serial core request to start/stop emitting अवरोध अक्षर */
अटल व्योम pic32_uart_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक ctl)
अणु
	काष्ठा pic32_sport *sport = to_pic32_sport(port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	अगर (ctl)
		pic32_uart_ग_लिखोl(sport, PIC32_SET(PIC32_UART_STA),
					PIC32_UART_STA_UTXBRK);
	अन्यथा
		pic32_uart_ग_लिखोl(sport, PIC32_CLR(PIC32_UART_STA),
					PIC32_UART_STA_UTXBRK);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

/* get port type in string क्रमmat */
अटल स्थिर अक्षर *pic32_uart_type(काष्ठा uart_port *port)
अणु
	वापस (port->type == PORT_PIC32) ? PIC32_DEV_NAME : शून्य;
पूर्ण

/* पढ़ो all अक्षरs in rx fअगरo and send them to core */
अटल व्योम pic32_uart_करो_rx(काष्ठा uart_port *port)
अणु
	काष्ठा pic32_sport *sport = to_pic32_sport(port);
	काष्ठा tty_port *tty;
	अचिन्हित पूर्णांक max_count;

	/* limit number of अक्षर पढ़ो in पूर्णांकerrupt, should not be
	 * higher than fअगरo size anyway since we're much faster than
	 * serial port
	 */
	max_count = PIC32_UART_RX_FIFO_DEPTH;

	spin_lock(&port->lock);

	tty = &port->state->port;

	करो अणु
		u32 sta_reg, c;
		अक्षर flag;

		/* get overrun/fअगरo empty inक्रमmation from status रेजिस्टर */
		sta_reg = pic32_uart_पढ़ोl(sport, PIC32_UART_STA);
		अगर (unlikely(sta_reg & PIC32_UART_STA_OERR)) अणु

			/* fअगरo reset is required to clear पूर्णांकerrupt */
			pic32_uart_ग_लिखोl(sport, PIC32_CLR(PIC32_UART_STA),
						PIC32_UART_STA_OERR);

			port->icount.overrun++;
			tty_insert_flip_अक्षर(tty, 0, TTY_OVERRUN);
		पूर्ण

		/* Can at least one more अक्षरacter can be पढ़ो? */
		अगर (!(sta_reg & PIC32_UART_STA_URXDA))
			अवरोध;

		/* पढ़ो the अक्षरacter and increment the rx counter */
		c = pic32_uart_पढ़ोl(sport, PIC32_UART_RX);

		port->icount.rx++;
		flag = TTY_NORMAL;
		c &= 0xff;

		अगर (unlikely((sta_reg & PIC32_UART_STA_PERR) ||
			     (sta_reg & PIC32_UART_STA_FERR))) अणु

			/* करो stats first */
			अगर (sta_reg & PIC32_UART_STA_PERR)
				port->icount.parity++;
			अगर (sta_reg & PIC32_UART_STA_FERR)
				port->icount.frame++;

			/* update flag wrt पढ़ो_status_mask */
			sta_reg &= port->पढ़ो_status_mask;

			अगर (sta_reg & PIC32_UART_STA_FERR)
				flag = TTY_FRAME;
			अगर (sta_reg & PIC32_UART_STA_PERR)
				flag = TTY_PARITY;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(port, c))
			जारी;

		अगर ((sta_reg & port->ignore_status_mask) == 0)
			tty_insert_flip_अक्षर(tty, c, flag);

	पूर्ण जबतक (--max_count);

	spin_unlock(&port->lock);

	tty_flip_buffer_push(tty);
पूर्ण

/* fill tx fअगरo with अक्षरs to send, stop when fअगरo is about to be full
 * or when all अक्षरs have been sent.
 */
अटल व्योम pic32_uart_करो_tx(काष्ठा uart_port *port)
अणु
	काष्ठा pic32_sport *sport = to_pic32_sport(port);
	काष्ठा circ_buf *xmit = &port->state->xmit;
	अचिन्हित पूर्णांक max_count = PIC32_UART_TX_FIFO_DEPTH;

	अगर (port->x_अक्षर) अणु
		pic32_uart_ग_लिखोl(sport, PIC32_UART_TX, port->x_अक्षर);
		port->icount.tx++;
		port->x_अक्षर = 0;
		वापस;
	पूर्ण

	अगर (uart_tx_stopped(port)) अणु
		pic32_uart_stop_tx(port);
		वापस;
	पूर्ण

	अगर (uart_circ_empty(xmit))
		जाओ txq_empty;

	/* keep stuffing अक्षरs पूर्णांकo uart tx buffer
	 * 1) until uart fअगरo is full
	 * or
	 * 2) until the circ buffer is empty
	 * (all अक्षरs have been sent)
	 * or
	 * 3) until the max count is reached
	 * (prevents lingering here क्रम too दीर्घ in certain हालs)
	 */
	जबतक (!(PIC32_UART_STA_UTXBF &
		pic32_uart_पढ़ोl(sport, PIC32_UART_STA))) अणु
		अचिन्हित पूर्णांक c = xmit->buf[xmit->tail];

		pic32_uart_ग_लिखोl(sport, PIC32_UART_TX, c);

		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
		अगर (uart_circ_empty(xmit))
			अवरोध;
		अगर (--max_count == 0)
			अवरोध;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (uart_circ_empty(xmit))
		जाओ txq_empty;

	वापस;

txq_empty:
	pic32_uart_irqtxen(sport, 0);
पूर्ण

/* RX पूर्णांकerrupt handler */
अटल irqवापस_t pic32_uart_rx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;

	pic32_uart_करो_rx(port);

	वापस IRQ_HANDLED;
पूर्ण

/* TX पूर्णांकerrupt handler */
अटल irqवापस_t pic32_uart_tx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port = dev_id;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	pic32_uart_करो_tx(port);
	spin_unlock_irqrestore(&port->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

/* FAULT पूर्णांकerrupt handler */
अटल irqवापस_t pic32_uart_fault_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	/* करो nothing: pic32_uart_करो_rx() handles faults. */
	वापस IRQ_HANDLED;
पूर्ण

/* enable rx & tx operation on uart */
अटल व्योम pic32_uart_en_and_unmask(काष्ठा uart_port *port)
अणु
	काष्ठा pic32_sport *sport = to_pic32_sport(port);

	pic32_uart_ग_लिखोl(sport, PIC32_SET(PIC32_UART_STA),
				PIC32_UART_STA_UTXEN | PIC32_UART_STA_URXEN);
	pic32_uart_ग_लिखोl(sport, PIC32_SET(PIC32_UART_MODE),
				PIC32_UART_MODE_ON);
पूर्ण

/* disable rx & tx operation on uart */
अटल व्योम pic32_uart_dsbl_and_mask(काष्ठा uart_port *port)
अणु
	काष्ठा pic32_sport *sport = to_pic32_sport(port);

	/* रुको क्रम tx empty, otherwise अक्षरs will be lost or corrupted */
	pic32_रुको_deplete_txbuf(sport);

	pic32_uart_ग_लिखोl(sport, PIC32_CLR(PIC32_UART_STA),
				PIC32_UART_STA_UTXEN | PIC32_UART_STA_URXEN);
	pic32_uart_ग_लिखोl(sport, PIC32_CLR(PIC32_UART_MODE),
				PIC32_UART_MODE_ON);
पूर्ण

/* serial core request to initialize uart and start rx operation */
अटल पूर्णांक pic32_uart_startup(काष्ठा uart_port *port)
अणु
	काष्ठा pic32_sport *sport = to_pic32_sport(port);
	u32 dflt_baud = (port->uartclk / PIC32_UART_DFLT_BRATE / 16) - 1;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	local_irq_save(flags);

	ret = pic32_enable_घड़ी(sport);
	अगर (ret) अणु
		local_irq_restore(flags);
		जाओ out_करोne;
	पूर्ण

	/* clear status and mode रेजिस्टरs */
	pic32_uart_ग_लिखोl(sport, PIC32_UART_MODE, 0);
	pic32_uart_ग_लिखोl(sport, PIC32_UART_STA, 0);

	/* disable uart and mask all पूर्णांकerrupts */
	pic32_uart_dsbl_and_mask(port);

	/* set शेष baud */
	pic32_uart_ग_लिखोl(sport, PIC32_UART_BRG, dflt_baud);

	local_irq_restore(flags);

	/* Each UART of a PIC32 has three पूर्णांकerrupts thereक्रमe,
	 * we setup driver to रेजिस्टर the 3 irqs क्रम the device.
	 *
	 * For each irq request_irq() is called with पूर्णांकerrupt disabled.
	 * And the irq is enabled as soon as we are पढ़ोy to handle them.
	 */
	tx_irq_enabled(sport) = 0;

	sport->irq_fault_name = kaप्र_लिखो(GFP_KERNEL, "%s%d-fault",
					  pic32_uart_type(port),
					  sport->idx);
	अगर (!sport->irq_fault_name) अणु
		dev_err(port->dev, "%s: kasprintf err!", __func__);
		ret = -ENOMEM;
		जाओ out_करोne;
	पूर्ण
	irq_set_status_flags(sport->irq_fault, IRQ_NOAUTOEN);
	ret = request_irq(sport->irq_fault, pic32_uart_fault_पूर्णांकerrupt,
			  sport->irqflags_fault, sport->irq_fault_name, port);
	अगर (ret) अणु
		dev_err(port->dev, "%s: request irq(%d) err! ret:%d name:%s\n",
			__func__, sport->irq_fault, ret,
			pic32_uart_type(port));
		जाओ out_f;
	पूर्ण

	sport->irq_rx_name = kaप्र_लिखो(GFP_KERNEL, "%s%d-rx",
				       pic32_uart_type(port),
				       sport->idx);
	अगर (!sport->irq_rx_name) अणु
		dev_err(port->dev, "%s: kasprintf err!", __func__);
		ret = -ENOMEM;
		जाओ out_f;
	पूर्ण
	irq_set_status_flags(sport->irq_rx, IRQ_NOAUTOEN);
	ret = request_irq(sport->irq_rx, pic32_uart_rx_पूर्णांकerrupt,
			  sport->irqflags_rx, sport->irq_rx_name, port);
	अगर (ret) अणु
		dev_err(port->dev, "%s: request irq(%d) err! ret:%d name:%s\n",
			__func__, sport->irq_rx, ret,
			pic32_uart_type(port));
		जाओ out_r;
	पूर्ण

	sport->irq_tx_name = kaप्र_लिखो(GFP_KERNEL, "%s%d-tx",
				       pic32_uart_type(port),
				       sport->idx);
	अगर (!sport->irq_tx_name) अणु
		dev_err(port->dev, "%s: kasprintf err!", __func__);
		ret = -ENOMEM;
		जाओ out_r;
	पूर्ण
	irq_set_status_flags(sport->irq_tx, IRQ_NOAUTOEN);
	ret = request_irq(sport->irq_tx, pic32_uart_tx_पूर्णांकerrupt,
			  sport->irqflags_tx, sport->irq_tx_name, port);
	अगर (ret) अणु
		dev_err(port->dev, "%s: request irq(%d) err! ret:%d name:%s\n",
			__func__, sport->irq_tx, ret,
			pic32_uart_type(port));
		जाओ out_t;
	पूर्ण

	local_irq_save(flags);

	/* set rx पूर्णांकerrupt on first receive */
	pic32_uart_ग_लिखोl(sport, PIC32_CLR(PIC32_UART_STA),
			PIC32_UART_STA_URXISEL1 | PIC32_UART_STA_URXISEL0);

	/* set पूर्णांकerrupt on empty */
	pic32_uart_ग_लिखोl(sport, PIC32_CLR(PIC32_UART_STA),
			PIC32_UART_STA_UTXISEL1);

	/* enable all पूर्णांकerrupts and eanable uart */
	pic32_uart_en_and_unmask(port);

	enable_irq(sport->irq_rx);

	वापस 0;

out_t:
	kमुक्त(sport->irq_tx_name);
	मुक्त_irq(sport->irq_tx, port);
out_r:
	kमुक्त(sport->irq_rx_name);
	मुक्त_irq(sport->irq_rx, port);
out_f:
	kमुक्त(sport->irq_fault_name);
	मुक्त_irq(sport->irq_fault, port);
out_करोne:
	वापस ret;
पूर्ण

/* serial core request to flush & disable uart */
अटल व्योम pic32_uart_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा pic32_sport *sport = to_pic32_sport(port);
	अचिन्हित दीर्घ flags;

	/* disable uart */
	spin_lock_irqsave(&port->lock, flags);
	pic32_uart_dsbl_and_mask(port);
	spin_unlock_irqrestore(&port->lock, flags);
	pic32_disable_घड़ी(sport);

	/* मुक्त all 3 पूर्णांकerrupts क्रम this UART */
	मुक्त_irq(sport->irq_fault, port);
	मुक्त_irq(sport->irq_tx, port);
	मुक्त_irq(sport->irq_rx, port);
पूर्ण

/* serial core request to change current uart setting */
अटल व्योम pic32_uart_set_termios(काष्ठा uart_port *port,
				   काष्ठा ktermios *new,
				   काष्ठा ktermios *old)
अणु
	काष्ठा pic32_sport *sport = to_pic32_sport(port);
	अचिन्हित पूर्णांक baud;
	अचिन्हित पूर्णांक quot;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	/* disable uart and mask all पूर्णांकerrupts जबतक changing speed */
	pic32_uart_dsbl_and_mask(port);

	/* stop bit options */
	अगर (new->c_cflag & CSTOPB)
		pic32_uart_ग_लिखोl(sport, PIC32_SET(PIC32_UART_MODE),
					PIC32_UART_MODE_STSEL);
	अन्यथा
		pic32_uart_ग_लिखोl(sport, PIC32_CLR(PIC32_UART_MODE),
					PIC32_UART_MODE_STSEL);

	/* parity options */
	अगर (new->c_cflag & PARENB) अणु
		अगर (new->c_cflag & PARODD) अणु
			pic32_uart_ग_लिखोl(sport, PIC32_SET(PIC32_UART_MODE),
					PIC32_UART_MODE_PDSEL1);
			pic32_uart_ग_लिखोl(sport, PIC32_CLR(PIC32_UART_MODE),
					PIC32_UART_MODE_PDSEL0);
		पूर्ण अन्यथा अणु
			pic32_uart_ग_लिखोl(sport, PIC32_SET(PIC32_UART_MODE),
					PIC32_UART_MODE_PDSEL0);
			pic32_uart_ग_लिखोl(sport, PIC32_CLR(PIC32_UART_MODE),
					PIC32_UART_MODE_PDSEL1);
		पूर्ण
	पूर्ण अन्यथा अणु
		pic32_uart_ग_लिखोl(sport, PIC32_CLR(PIC32_UART_MODE),
					PIC32_UART_MODE_PDSEL1 |
					PIC32_UART_MODE_PDSEL0);
	पूर्ण
	/* अगर hw flow ctrl, then the pins must be specअगरied in device tree */
	अगर ((new->c_cflag & CRTSCTS) && sport->hw_flow_ctrl) अणु
		/* enable hardware flow control */
		pic32_uart_ग_लिखोl(sport, PIC32_SET(PIC32_UART_MODE),
					PIC32_UART_MODE_UEN1);
		pic32_uart_ग_लिखोl(sport, PIC32_CLR(PIC32_UART_MODE),
					PIC32_UART_MODE_UEN0);
		pic32_uart_ग_लिखोl(sport, PIC32_CLR(PIC32_UART_MODE),
					PIC32_UART_MODE_RTSMD);
	पूर्ण अन्यथा अणु
		/* disable hardware flow control */
		pic32_uart_ग_लिखोl(sport, PIC32_CLR(PIC32_UART_MODE),
					PIC32_UART_MODE_UEN1);
		pic32_uart_ग_लिखोl(sport, PIC32_CLR(PIC32_UART_MODE),
					PIC32_UART_MODE_UEN0);
		pic32_uart_ग_लिखोl(sport, PIC32_CLR(PIC32_UART_MODE),
					PIC32_UART_MODE_RTSMD);
	पूर्ण

	/* Always 8-bit */
	new->c_cflag |= CS8;

	/* Mark/Space parity is not supported */
	new->c_cflag &= ~CMSPAR;

	/* update baud */
	baud = uart_get_baud_rate(port, new, old, 0, port->uartclk / 16);
	quot = uart_get_भागisor(port, baud) - 1;
	pic32_uart_ग_लिखोl(sport, PIC32_UART_BRG, quot);
	uart_update_समयout(port, new->c_cflag, baud);

	अगर (tty_termios_baud_rate(new))
		tty_termios_encode_baud_rate(new, baud, baud);

	/* enable uart */
	pic32_uart_en_and_unmask(port);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

/* serial core request to claim uart iomem */
अटल पूर्णांक pic32_uart_request_port(काष्ठा uart_port *port)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(port->dev);
	काष्ठा resource *res_mem;

	res_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (unlikely(!res_mem))
		वापस -EINVAL;

	अगर (!request_mem_region(port->mapbase, resource_size(res_mem),
				"pic32_uart_mem"))
		वापस -EBUSY;

	port->membase = devm_ioremap(port->dev, port->mapbase,
						resource_size(res_mem));
	अगर (!port->membase) अणु
		dev_err(port->dev, "Unable to map registers\n");
		release_mem_region(port->mapbase, resource_size(res_mem));
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/* serial core request to release uart iomem */
अटल व्योम pic32_uart_release_port(काष्ठा uart_port *port)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(port->dev);
	काष्ठा resource *res_mem;
	अचिन्हित पूर्णांक res_size;

	res_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (unlikely(!res_mem))
		वापस;
	res_size = resource_size(res_mem);

	release_mem_region(port->mapbase, res_size);
पूर्ण

/* serial core request to करो any port required स्वतः-configuration */
अटल व्योम pic32_uart_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE) अणु
		अगर (pic32_uart_request_port(port))
			वापस;
		port->type = PORT_PIC32;
	पूर्ण
पूर्ण

/* serial core request to check that port inक्रमmation in serinfo are suitable */
अटल पूर्णांक pic32_uart_verअगरy_port(काष्ठा uart_port *port,
				  काष्ठा serial_काष्ठा *serinfo)
अणु
	अगर (port->type != PORT_PIC32)
		वापस -EINVAL;
	अगर (port->irq != serinfo->irq)
		वापस -EINVAL;
	अगर (port->iotype != serinfo->io_type)
		वापस -EINVAL;
	अगर (port->mapbase != (अचिन्हित दीर्घ)serinfo->iomem_base)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* serial core callbacks */
अटल स्थिर काष्ठा uart_ops pic32_uart_ops = अणु
	.tx_empty	= pic32_uart_tx_empty,
	.get_mctrl	= pic32_uart_get_mctrl,
	.set_mctrl	= pic32_uart_set_mctrl,
	.start_tx	= pic32_uart_start_tx,
	.stop_tx	= pic32_uart_stop_tx,
	.stop_rx	= pic32_uart_stop_rx,
	.अवरोध_ctl	= pic32_uart_अवरोध_ctl,
	.startup	= pic32_uart_startup,
	.shutकरोwn	= pic32_uart_shutकरोwn,
	.set_termios	= pic32_uart_set_termios,
	.type		= pic32_uart_type,
	.release_port	= pic32_uart_release_port,
	.request_port	= pic32_uart_request_port,
	.config_port	= pic32_uart_config_port,
	.verअगरy_port	= pic32_uart_verअगरy_port,
पूर्ण;

#अगर_घोषित CONFIG_SERIAL_PIC32_CONSOLE
/* output given अक्षर */
अटल व्योम pic32_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	काष्ठा pic32_sport *sport = to_pic32_sport(port);

	अगर (!(pic32_uart_पढ़ोl(sport, PIC32_UART_MODE) & PIC32_UART_MODE_ON))
		वापस;

	अगर (!(pic32_uart_पढ़ोl(sport, PIC32_UART_STA) & PIC32_UART_STA_UTXEN))
		वापस;

	/* रुको क्रम tx empty */
	pic32_रुको_deplete_txbuf(sport);

	pic32_uart_ग_लिखोl(sport, PIC32_UART_TX, ch & 0xff);
पूर्ण

/* console core request to output given string */
अटल व्योम pic32_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s,
				अचिन्हित पूर्णांक count)
अणु
	काष्ठा pic32_sport *sport = pic32_sports[co->index];
	काष्ठा uart_port *port = pic32_get_port(sport);

	/* call uart helper to deal with \ल\न */
	uart_console_ग_लिखो(port, s, count, pic32_console_अक्षर_दो);
पूर्ण

/* console core request to setup given console, find matching uart
 * port and setup it.
 */
अटल पूर्णांक pic32_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा pic32_sport *sport;
	काष्ठा uart_port *port = शून्य;
	पूर्णांक baud = 115200;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';
	पूर्णांक ret = 0;

	अगर (unlikely(co->index < 0 || co->index >= PIC32_MAX_UARTS))
		वापस -ENODEV;

	sport = pic32_sports[co->index];
	अगर (!sport)
		वापस -ENODEV;
	port = pic32_get_port(sport);

	ret = pic32_enable_घड़ी(sport);
	अगर (ret)
		वापस ret;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver pic32_uart_driver;
अटल काष्ठा console pic32_console = अणु
	.name		= PIC32_SDEV_NAME,
	.ग_लिखो		= pic32_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= pic32_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &pic32_uart_driver,
पूर्ण;
#घोषणा PIC32_SCONSOLE (&pic32_console)

अटल पूर्णांक __init pic32_console_init(व्योम)
अणु
	रेजिस्टर_console(&pic32_console);
	वापस 0;
पूर्ण
console_initcall(pic32_console_init);

/*
 * Late console initialization.
 */
अटल पूर्णांक __init pic32_late_console_init(व्योम)
अणु
	अगर (!(pic32_console.flags & CON_ENABLED))
		रेजिस्टर_console(&pic32_console);

	वापस 0;
पूर्ण

core_initcall(pic32_late_console_init);

#अन्यथा
#घोषणा PIC32_SCONSOLE शून्य
#पूर्ण_अगर

अटल काष्ठा uart_driver pic32_uart_driver = अणु
	.owner			= THIS_MODULE,
	.driver_name		= PIC32_DEV_NAME,
	.dev_name		= PIC32_SDEV_NAME,
	.nr			= PIC32_MAX_UARTS,
	.cons			= PIC32_SCONSOLE,
पूर्ण;

अटल पूर्णांक pic32_uart_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा pic32_sport *sport;
	पूर्णांक uart_idx = 0;
	काष्ठा resource *res_mem;
	काष्ठा uart_port *port;
	पूर्णांक ret;

	uart_idx = of_alias_get_id(np, "serial");
	अगर (uart_idx < 0 || uart_idx >= PIC32_MAX_UARTS)
		वापस -EINVAL;

	res_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res_mem)
		वापस -EINVAL;

	sport = devm_kzalloc(&pdev->dev, माप(*sport), GFP_KERNEL);
	अगर (!sport)
		वापस -ENOMEM;

	sport->idx		= uart_idx;
	sport->irq_fault	= irq_of_parse_and_map(np, 0);
	sport->irqflags_fault	= IRQF_NO_THREAD;
	sport->irq_rx		= irq_of_parse_and_map(np, 1);
	sport->irqflags_rx	= IRQF_NO_THREAD;
	sport->irq_tx		= irq_of_parse_and_map(np, 2);
	sport->irqflags_tx	= IRQF_NO_THREAD;
	sport->clk		= devm_clk_get(&pdev->dev, शून्य);
	sport->cts_gpio		= -EINVAL;
	sport->dev		= &pdev->dev;

	/* Hardware flow control: gpios
	 * !Note: Basically, CTS is needed क्रम पढ़ोing the status.
	 */
	sport->hw_flow_ctrl = false;
	sport->cts_gpio = of_get_named_gpio(np, "cts-gpios", 0);
	अगर (gpio_is_valid(sport->cts_gpio)) अणु
		sport->hw_flow_ctrl = true;

		ret = devm_gpio_request(sport->dev,
					sport->cts_gpio, "CTS");
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"error requesting CTS GPIO\n");
			जाओ err;
		पूर्ण

		ret = gpio_direction_input(sport->cts_gpio);
		अगर (ret) अणु
			dev_err(&pdev->dev, "error setting CTS GPIO\n");
			जाओ err;
		पूर्ण
	पूर्ण

	pic32_sports[uart_idx] = sport;
	port = &sport->port;
	स_रखो(port, 0, माप(*port));
	port->iotype	= UPIO_MEM;
	port->mapbase	= res_mem->start;
	port->ops	= &pic32_uart_ops;
	port->flags	= UPF_BOOT_AUTOCONF;
	port->dev	= &pdev->dev;
	port->fअगरosize	= PIC32_UART_TX_FIFO_DEPTH;
	port->uartclk	= clk_get_rate(sport->clk);
	port->line	= uart_idx;

	ret = uart_add_one_port(&pic32_uart_driver, port);
	अगर (ret) अणु
		port->membase = शून्य;
		dev_err(port->dev, "%s: uart add port error!\n", __func__);
		जाओ err;
	पूर्ण

#अगर_घोषित CONFIG_SERIAL_PIC32_CONSOLE
	अगर (uart_console(port) && (pic32_console.flags & CON_ENABLED)) अणु
		/* The peripheral घड़ी has been enabled by console_setup,
		 * so disable it till the port is used.
		 */
		pic32_disable_घड़ी(sport);
	पूर्ण
#पूर्ण_अगर

	platक्रमm_set_drvdata(pdev, port);

	dev_info(&pdev->dev, "%s: uart(%d) driver initialized.\n",
		 __func__, uart_idx);

	वापस 0;
err:
	/* स्वतःmatic unroll of sport and gpios */
	वापस ret;
पूर्ण

अटल पूर्णांक pic32_uart_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port = platक्रमm_get_drvdata(pdev);
	काष्ठा pic32_sport *sport = to_pic32_sport(port);

	uart_हटाओ_one_port(&pic32_uart_driver, port);
	pic32_disable_घड़ी(sport);
	platक्रमm_set_drvdata(pdev, शून्य);
	pic32_sports[sport->idx] = शून्य;

	/* स्वतःmatic unroll of sport and gpios */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pic32_serial_dt_ids[] = अणु
	अणु .compatible = "microchip,pic32mzda-uart" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pic32_serial_dt_ids);

अटल काष्ठा platक्रमm_driver pic32_uart_platक्रमm_driver = अणु
	.probe		= pic32_uart_probe,
	.हटाओ		= pic32_uart_हटाओ,
	.driver		= अणु
		.name	= PIC32_DEV_NAME,
		.of_match_table	= of_match_ptr(pic32_serial_dt_ids),
		.suppress_bind_attrs = IS_BUILTIN(CONFIG_SERIAL_PIC32),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init pic32_uart_init(व्योम)
अणु
	पूर्णांक ret;

	ret = uart_रेजिस्टर_driver(&pic32_uart_driver);
	अगर (ret) अणु
		pr_err("failed to register %s:%d\n",
		       pic32_uart_driver.driver_name, ret);
		वापस ret;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&pic32_uart_platक्रमm_driver);
	अगर (ret) अणु
		pr_err("fail to register pic32 uart\n");
		uart_unरेजिस्टर_driver(&pic32_uart_driver);
	पूर्ण

	वापस ret;
पूर्ण
arch_initcall(pic32_uart_init);

अटल व्योम __निकास pic32_uart_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_SERIAL_PIC32_CONSOLE
	unरेजिस्टर_console(&pic32_console);
#पूर्ण_अगर
	platक्रमm_driver_unरेजिस्टर(&pic32_uart_platक्रमm_driver);
	uart_unरेजिस्टर_driver(&pic32_uart_driver);
पूर्ण
module_निकास(pic32_uart_निकास);

MODULE_AUTHOR("Sorin-Andrei Pistirica <andrei.pistirica@microchip.com>");
MODULE_DESCRIPTION("Microchip PIC32 integrated serial port driver");
MODULE_LICENSE("GPL v2");
