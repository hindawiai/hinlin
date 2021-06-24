<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * st-asc.c: ST Asynchronous serial controller (ASC) driver
 *
 * Copyright (C) 2003-2013 STMicroelectronics (R&D) Limited
 */

#समावेश <linux/module.h>
#समावेश <linux/serial.h>
#समावेश <linux/console.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/clk.h>
#समावेश <linux/gpio/consumer.h>

#घोषणा DRIVER_NAME "st-asc"
#घोषणा ASC_SERIAL_NAME "ttyAS"
#घोषणा ASC_FIFO_SIZE 16
#घोषणा ASC_MAX_PORTS 8

/* Pinctrl states */
#घोषणा DEFAULT		0
#घोषणा NO_HW_FLOWCTRL	1

काष्ठा asc_port अणु
	काष्ठा uart_port port;
	काष्ठा gpio_desc *rts;
	काष्ठा clk *clk;
	काष्ठा pinctrl *pinctrl;
	काष्ठा pinctrl_state *states[2];
	अचिन्हित पूर्णांक hw_flow_control:1;
	अचिन्हित पूर्णांक क्रमce_m1:1;
पूर्ण;

अटल काष्ठा asc_port asc_ports[ASC_MAX_PORTS];
अटल काष्ठा uart_driver asc_uart_driver;

/*---- UART Register definitions ------------------------------*/

/* Register offsets */

#घोषणा ASC_BAUDRATE			0x00
#घोषणा ASC_TXBUF			0x04
#घोषणा ASC_RXBUF			0x08
#घोषणा ASC_CTL				0x0C
#घोषणा ASC_INTEN			0x10
#घोषणा ASC_STA				0x14
#घोषणा ASC_GUARDTIME			0x18
#घोषणा ASC_TIMEOUT			0x1C
#घोषणा ASC_TXRESET			0x20
#घोषणा ASC_RXRESET			0x24
#घोषणा ASC_RETRIES			0x28

/* ASC_RXBUF */
#घोषणा ASC_RXBUF_PE			0x100
#घोषणा ASC_RXBUF_FE			0x200
/**
 * Some of status comes from higher bits of the अक्षरacter and some come from
 * the status रेजिस्टर. Combining both of them in to single status using dummy
 * bits.
 */
#घोषणा ASC_RXBUF_DUMMY_RX		0x10000
#घोषणा ASC_RXBUF_DUMMY_BE		0x20000
#घोषणा ASC_RXBUF_DUMMY_OE		0x40000

/* ASC_CTL */

#घोषणा ASC_CTL_MODE_MSK		0x0007
#घोषणा  ASC_CTL_MODE_8BIT		0x0001
#घोषणा  ASC_CTL_MODE_7BIT_PAR		0x0003
#घोषणा  ASC_CTL_MODE_9BIT		0x0004
#घोषणा  ASC_CTL_MODE_8BIT_WKUP		0x0005
#घोषणा  ASC_CTL_MODE_8BIT_PAR		0x0007
#घोषणा ASC_CTL_STOP_MSK		0x0018
#घोषणा  ASC_CTL_STOP_HALFBIT		0x0000
#घोषणा  ASC_CTL_STOP_1BIT		0x0008
#घोषणा  ASC_CTL_STOP_1_HALFBIT		0x0010
#घोषणा  ASC_CTL_STOP_2BIT		0x0018
#घोषणा ASC_CTL_PARITYODD		0x0020
#घोषणा ASC_CTL_LOOPBACK		0x0040
#घोषणा ASC_CTL_RUN			0x0080
#घोषणा ASC_CTL_RXENABLE		0x0100
#घोषणा ASC_CTL_SCENABLE		0x0200
#घोषणा ASC_CTL_FIFOENABLE		0x0400
#घोषणा ASC_CTL_CTSENABLE		0x0800
#घोषणा ASC_CTL_BAUDMODE		0x1000

/* ASC_GUARDTIME */

#घोषणा ASC_GUARDTIME_MSK		0x00FF

/* ASC_INTEN */

#घोषणा ASC_INTEN_RBE			0x0001
#घोषणा ASC_INTEN_TE			0x0002
#घोषणा ASC_INTEN_THE			0x0004
#घोषणा ASC_INTEN_PE			0x0008
#घोषणा ASC_INTEN_FE			0x0010
#घोषणा ASC_INTEN_OE			0x0020
#घोषणा ASC_INTEN_TNE			0x0040
#घोषणा ASC_INTEN_TOI			0x0080
#घोषणा ASC_INTEN_RHF			0x0100

/* ASC_RETRIES */

#घोषणा ASC_RETRIES_MSK			0x00FF

/* ASC_RXBUF */

#घोषणा ASC_RXBUF_MSK			0x03FF

/* ASC_STA */

#घोषणा ASC_STA_RBF			0x0001
#घोषणा ASC_STA_TE			0x0002
#घोषणा ASC_STA_THE			0x0004
#घोषणा ASC_STA_PE			0x0008
#घोषणा ASC_STA_FE			0x0010
#घोषणा ASC_STA_OE			0x0020
#घोषणा ASC_STA_TNE			0x0040
#घोषणा ASC_STA_TOI			0x0080
#घोषणा ASC_STA_RHF			0x0100
#घोषणा ASC_STA_TF			0x0200
#घोषणा ASC_STA_NKD			0x0400

/* ASC_TIMEOUT */

#घोषणा ASC_TIMEOUT_MSK			0x00FF

/* ASC_TXBUF */

#घोषणा ASC_TXBUF_MSK			0x01FF

/*---- Inline function definitions ---------------------------*/

अटल अंतरभूत काष्ठा asc_port *to_asc_port(काष्ठा uart_port *port)
अणु
	वापस container_of(port, काष्ठा asc_port, port);
पूर्ण

अटल अंतरभूत u32 asc_in(काष्ठा uart_port *port, u32 offset)
अणु
#अगर_घोषित पढ़ोl_relaxed
	वापस पढ़ोl_relaxed(port->membase + offset);
#अन्यथा
	वापस पढ़ोl(port->membase + offset);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम asc_out(काष्ठा uart_port *port, u32 offset, u32 value)
अणु
#अगर_घोषित ग_लिखोl_relaxed
	ग_लिखोl_relaxed(value, port->membase + offset);
#अन्यथा
	ग_लिखोl(value, port->membase + offset);
#पूर्ण_अगर
पूर्ण

/*
 * Some simple utility functions to enable and disable पूर्णांकerrupts.
 * Note that these need to be called with पूर्णांकerrupts disabled.
 */
अटल अंतरभूत व्योम asc_disable_tx_पूर्णांकerrupts(काष्ठा uart_port *port)
अणु
	u32 पूर्णांकenable = asc_in(port, ASC_INTEN) & ~ASC_INTEN_THE;
	asc_out(port, ASC_INTEN, पूर्णांकenable);
	(व्योम)asc_in(port, ASC_INTEN);	/* Defeat bus ग_लिखो posting */
पूर्ण

अटल अंतरभूत व्योम asc_enable_tx_पूर्णांकerrupts(काष्ठा uart_port *port)
अणु
	u32 पूर्णांकenable = asc_in(port, ASC_INTEN) | ASC_INTEN_THE;
	asc_out(port, ASC_INTEN, पूर्णांकenable);
पूर्ण

अटल अंतरभूत व्योम asc_disable_rx_पूर्णांकerrupts(काष्ठा uart_port *port)
अणु
	u32 पूर्णांकenable = asc_in(port, ASC_INTEN) & ~ASC_INTEN_RBE;
	asc_out(port, ASC_INTEN, पूर्णांकenable);
	(व्योम)asc_in(port, ASC_INTEN);	/* Defeat bus ग_लिखो posting */
पूर्ण

अटल अंतरभूत व्योम asc_enable_rx_पूर्णांकerrupts(काष्ठा uart_port *port)
अणु
	u32 पूर्णांकenable = asc_in(port, ASC_INTEN) | ASC_INTEN_RBE;
	asc_out(port, ASC_INTEN, पूर्णांकenable);
पूर्ण

अटल अंतरभूत u32 asc_txfअगरo_is_empty(काष्ठा uart_port *port)
अणु
	वापस asc_in(port, ASC_STA) & ASC_STA_TE;
पूर्ण

अटल अंतरभूत u32 asc_txfअगरo_is_half_empty(काष्ठा uart_port *port)
अणु
	वापस asc_in(port, ASC_STA) & ASC_STA_THE;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *asc_port_name(काष्ठा uart_port *port)
अणु
	वापस to_platक्रमm_device(port->dev)->name;
पूर्ण

/*----------------------------------------------------------------------*/

/*
 * This section contains code to support the use of the ASC as a
 * generic serial port.
 */

अटल अंतरभूत अचिन्हित asc_hw_txroom(काष्ठा uart_port *port)
अणु
	u32 status = asc_in(port, ASC_STA);

	अगर (status & ASC_STA_THE)
		वापस port->fअगरosize / 2;
	अन्यथा अगर (!(status & ASC_STA_TF))
		वापस 1;

	वापस 0;
पूर्ण

/*
 * Start transmitting अक्षरs.
 * This is called from both पूर्णांकerrupt and task level.
 * Either way पूर्णांकerrupts are disabled.
 */
अटल व्योम asc_transmit_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;
	पूर्णांक txroom;
	अचिन्हित अक्षर c;

	txroom = asc_hw_txroom(port);

	अगर ((txroom != 0) && port->x_अक्षर) अणु
		c = port->x_अक्षर;
		port->x_अक्षर = 0;
		asc_out(port, ASC_TXBUF, c);
		port->icount.tx++;
		txroom = asc_hw_txroom(port);
	पूर्ण

	अगर (uart_tx_stopped(port)) अणु
		/*
		 * We should try and stop the hardware here, but I
		 * करोn't think the ASC has any way to करो that.
		 */
		asc_disable_tx_पूर्णांकerrupts(port);
		वापस;
	पूर्ण

	अगर (uart_circ_empty(xmit)) अणु
		asc_disable_tx_पूर्णांकerrupts(port);
		वापस;
	पूर्ण

	अगर (txroom == 0)
		वापस;

	करो अणु
		c = xmit->buf[xmit->tail];
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		asc_out(port, ASC_TXBUF, c);
		port->icount.tx++;
		txroom--;
	पूर्ण जबतक ((txroom > 0) && (!uart_circ_empty(xmit)));

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (uart_circ_empty(xmit))
		asc_disable_tx_पूर्णांकerrupts(port);
पूर्ण

अटल व्योम asc_receive_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा tty_port *tport = &port->state->port;
	अचिन्हित दीर्घ status, mode;
	अचिन्हित दीर्घ c = 0;
	अक्षर flag;
	bool ignore_pe = false;

	/*
	 * Datasheet states: If the MODE field selects an 8-bit frame then
	 * this [parity error] bit is undefined. Software should ignore this
	 * bit when पढ़ोing 8-bit frames.
	 */
	mode = asc_in(port, ASC_CTL) & ASC_CTL_MODE_MSK;
	अगर (mode == ASC_CTL_MODE_8BIT || mode == ASC_CTL_MODE_8BIT_PAR)
		ignore_pe = true;

	अगर (irqd_is_wakeup_set(irq_get_irq_data(port->irq)))
		pm_wakeup_event(tport->tty->dev, 0);

	जबतक ((status = asc_in(port, ASC_STA)) & ASC_STA_RBF) अणु
		c = asc_in(port, ASC_RXBUF) | ASC_RXBUF_DUMMY_RX;
		flag = TTY_NORMAL;
		port->icount.rx++;

		अगर (status & ASC_STA_OE || c & ASC_RXBUF_FE ||
		    (c & ASC_RXBUF_PE && !ignore_pe)) अणु

			अगर (c & ASC_RXBUF_FE) अणु
				अगर (c == (ASC_RXBUF_FE | ASC_RXBUF_DUMMY_RX)) अणु
					port->icount.brk++;
					अगर (uart_handle_अवरोध(port))
						जारी;
					c |= ASC_RXBUF_DUMMY_BE;
				पूर्ण अन्यथा अणु
					port->icount.frame++;
				पूर्ण
			पूर्ण अन्यथा अगर (c & ASC_RXBUF_PE) अणु
				port->icount.parity++;
			पूर्ण
			/*
			 * Reading any data from the RX FIFO clears the
			 * overflow error condition.
			 */
			अगर (status & ASC_STA_OE) अणु
				port->icount.overrun++;
				c |= ASC_RXBUF_DUMMY_OE;
			पूर्ण

			c &= port->पढ़ो_status_mask;

			अगर (c & ASC_RXBUF_DUMMY_BE)
				flag = TTY_BREAK;
			अन्यथा अगर (c & ASC_RXBUF_PE)
				flag = TTY_PARITY;
			अन्यथा अगर (c & ASC_RXBUF_FE)
				flag = TTY_FRAME;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(port, c & 0xff))
			जारी;

		uart_insert_अक्षर(port, c, ASC_RXBUF_DUMMY_OE, c & 0xff, flag);
	पूर्ण

	/* Tell the rest of the प्रणाली the news. New अक्षरacters! */
	tty_flip_buffer_push(tport);
पूर्ण

अटल irqवापस_t asc_पूर्णांकerrupt(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा uart_port *port = ptr;
	u32 status;

	spin_lock(&port->lock);

	status = asc_in(port, ASC_STA);

	अगर (status & ASC_STA_RBF) अणु
		/* Receive FIFO not empty */
		asc_receive_अक्षरs(port);
	पूर्ण

	अगर ((status & ASC_STA_THE) &&
	    (asc_in(port, ASC_INTEN) & ASC_INTEN_THE)) अणु
		/* Transmitter FIFO at least half empty */
		asc_transmit_अक्षरs(port);
	पूर्ण

	spin_unlock(&port->lock);

	वापस IRQ_HANDLED;
पूर्ण

/*----------------------------------------------------------------------*/

/*
 * UART Functions
 */

अटल अचिन्हित पूर्णांक asc_tx_empty(काष्ठा uart_port *port)
अणु
	वापस asc_txfअगरo_is_empty(port) ? TIOCSER_TEMT : 0;
पूर्ण

अटल व्योम asc_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा asc_port *ascport = to_asc_port(port);

	/*
	 * This routine is used क्रम seting संकेतs of: DTR, DCD, CTS and RTS.
	 * We use ASC's hardware क्रम CTS/RTS when hardware flow-control is
	 * enabled, however अगर the RTS line is required क्रम another purpose,
	 * commonly controlled using HUP from userspace, then we need to toggle
	 * it manually, using GPIO.
	 *
	 * Some boards also have DTR and DCD implemented using PIO pins, code to
	 * करो this should be hooked in here.
	 */

	अगर (!ascport->rts)
		वापस;

	/* If HW flow-control is enabled, we can't fiddle with the RTS line */
	अगर (asc_in(port, ASC_CTL) & ASC_CTL_CTSENABLE)
		वापस;

	gpiod_set_value(ascport->rts, mctrl & TIOCM_RTS);
पूर्ण

अटल अचिन्हित पूर्णांक asc_get_mctrl(काष्ठा uart_port *port)
अणु
	/*
	 * This routine is used क्रम geting संकेतs of: DTR, DCD, DSR, RI,
	 * and CTS/RTS
	 */
	वापस TIOCM_CAR | TIOCM_DSR | TIOCM_CTS;
पूर्ण

/* There are probably अक्षरacters रुकोing to be transmitted. */
अटल व्योम asc_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;

	अगर (!uart_circ_empty(xmit))
		asc_enable_tx_पूर्णांकerrupts(port);
पूर्ण

/* Transmit stop */
अटल व्योम asc_stop_tx(काष्ठा uart_port *port)
अणु
	asc_disable_tx_पूर्णांकerrupts(port);
पूर्ण

/* Receive stop */
अटल व्योम asc_stop_rx(काष्ठा uart_port *port)
अणु
	asc_disable_rx_पूर्णांकerrupts(port);
पूर्ण

/* Handle अवरोधs - ignored by us */
अटल व्योम asc_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	/* Nothing here yet .. */
पूर्ण

/*
 * Enable port क्रम reception.
 */
अटल पूर्णांक asc_startup(काष्ठा uart_port *port)
अणु
	अगर (request_irq(port->irq, asc_पूर्णांकerrupt, 0,
			asc_port_name(port), port)) अणु
		dev_err(port->dev, "cannot allocate irq.\n");
		वापस -ENODEV;
	पूर्ण

	asc_transmit_अक्षरs(port);
	asc_enable_rx_पूर्णांकerrupts(port);

	वापस 0;
पूर्ण

अटल व्योम asc_shutकरोwn(काष्ठा uart_port *port)
अणु
	asc_disable_tx_पूर्णांकerrupts(port);
	asc_disable_rx_पूर्णांकerrupts(port);
	मुक्त_irq(port->irq, port);
पूर्ण

अटल व्योम asc_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state,
		अचिन्हित पूर्णांक oldstate)
अणु
	काष्ठा asc_port *ascport = to_asc_port(port);
	अचिन्हित दीर्घ flags = 0;
	u32 ctl;

	चयन (state) अणु
	हाल UART_PM_STATE_ON:
		clk_prepare_enable(ascport->clk);
		अवरोध;
	हाल UART_PM_STATE_OFF:
		/*
		 * Disable the ASC baud rate generator, which is as बंद as
		 * we can come to turning it off. Note this is not called with
		 * the port spinlock held.
		 */
		spin_lock_irqsave(&port->lock, flags);
		ctl = asc_in(port, ASC_CTL) & ~ASC_CTL_RUN;
		asc_out(port, ASC_CTL, ctl);
		spin_unlock_irqrestore(&port->lock, flags);
		clk_disable_unprepare(ascport->clk);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम asc_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
			    काष्ठा ktermios *old)
अणु
	काष्ठा asc_port *ascport = to_asc_port(port);
	काष्ठा gpio_desc *gpiod;
	अचिन्हित पूर्णांक baud;
	u32 ctrl_val;
	tcflag_t cflag;
	अचिन्हित दीर्घ flags;

	/* Update termios to reflect hardware capabilities */
	termios->c_cflag &= ~(CMSPAR |
			 (ascport->hw_flow_control ? 0 : CRTSCTS));

	port->uartclk = clk_get_rate(ascport->clk);

	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk/16);
	cflag = termios->c_cflag;

	spin_lock_irqsave(&port->lock, flags);

	/* पढ़ो control रेजिस्टर */
	ctrl_val = asc_in(port, ASC_CTL);

	/* stop serial port and reset value */
	asc_out(port, ASC_CTL, (ctrl_val & ~ASC_CTL_RUN));
	ctrl_val = ASC_CTL_RXENABLE | ASC_CTL_FIFOENABLE;

	/* reset fअगरo rx & tx */
	asc_out(port, ASC_TXRESET, 1);
	asc_out(port, ASC_RXRESET, 1);

	/* set अक्षरacter length */
	अगर ((cflag & CSIZE) == CS7) अणु
		ctrl_val |= ASC_CTL_MODE_7BIT_PAR;
	पूर्ण अन्यथा अणु
		ctrl_val |= (cflag & PARENB) ?  ASC_CTL_MODE_8BIT_PAR :
						ASC_CTL_MODE_8BIT;
	पूर्ण

	/* set stop bit */
	ctrl_val |= (cflag & CSTOPB) ? ASC_CTL_STOP_2BIT : ASC_CTL_STOP_1BIT;

	/* odd parity */
	अगर (cflag & PARODD)
		ctrl_val |= ASC_CTL_PARITYODD;

	/* hardware flow control */
	अगर ((cflag & CRTSCTS)) अणु
		ctrl_val |= ASC_CTL_CTSENABLE;

		/* If flow-control selected, stop handling RTS manually */
		अगर (ascport->rts) अणु
			devm_gpiod_put(port->dev, ascport->rts);
			ascport->rts = शून्य;

			pinctrl_select_state(ascport->pinctrl,
					     ascport->states[DEFAULT]);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* If flow-control disabled, it's safe to handle RTS manually */
		अगर (!ascport->rts && ascport->states[NO_HW_FLOWCTRL]) अणु
			pinctrl_select_state(ascport->pinctrl,
					     ascport->states[NO_HW_FLOWCTRL]);

			gpiod = devm_gpiod_get(port->dev, "rts", GPIOD_OUT_LOW);
			अगर (!IS_ERR(gpiod)) अणु
				gpiod_set_consumer_name(gpiod,
						port->dev->of_node->name);
				ascport->rts = gpiod;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((baud < 19200) && !ascport->क्रमce_m1) अणु
		asc_out(port, ASC_BAUDRATE, (port->uartclk / (16 * baud)));
	पूर्ण अन्यथा अणु
		/*
		 * MODE 1: recommended क्रम high bit rates (above 19.2K)
		 *
		 *                   baudrate * 16 * 2^16
		 * ASCBaudRate =   ------------------------
		 *                          inअ_दोlock
		 *
		 * To keep maths inside 64bits, we भागide inअ_दोlock by 16.
		 */
		u64 भागidend = (u64)baud * (1 << 16);

		करो_भाग(भागidend, port->uartclk / 16);
		asc_out(port, ASC_BAUDRATE, भागidend);
		ctrl_val |= ASC_CTL_BAUDMODE;
	पूर्ण

	uart_update_समयout(port, cflag, baud);

	ascport->port.पढ़ो_status_mask = ASC_RXBUF_DUMMY_OE;
	अगर (termios->c_अगरlag & INPCK)
		ascport->port.पढ़ो_status_mask |= ASC_RXBUF_FE | ASC_RXBUF_PE;
	अगर (termios->c_अगरlag & (IGNBRK | BRKINT | PARMRK))
		ascport->port.पढ़ो_status_mask |= ASC_RXBUF_DUMMY_BE;

	/*
	 * Characters to ignore
	 */
	ascport->port.ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		ascport->port.ignore_status_mask |= ASC_RXBUF_FE | ASC_RXBUF_PE;
	अगर (termios->c_अगरlag & IGNBRK) अणु
		ascport->port.ignore_status_mask |= ASC_RXBUF_DUMMY_BE;
		/*
		 * If we're ignoring parity and अवरोध indicators,
		 * ignore overruns too (क्रम real raw support).
		 */
		अगर (termios->c_अगरlag & IGNPAR)
			ascport->port.ignore_status_mask |= ASC_RXBUF_DUMMY_OE;
	पूर्ण

	/*
	 * Ignore all अक्षरacters अगर CREAD is not set.
	 */
	अगर (!(termios->c_cflag & CREAD))
		ascport->port.ignore_status_mask |= ASC_RXBUF_DUMMY_RX;

	/* Set the समयout */
	asc_out(port, ASC_TIMEOUT, 20);

	/* ग_लिखो final value and enable port */
	asc_out(port, ASC_CTL, (ctrl_val | ASC_CTL_RUN));

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *asc_type(काष्ठा uart_port *port)
अणु
	वापस (port->type == PORT_ASC) ? DRIVER_NAME : शून्य;
पूर्ण

अटल व्योम asc_release_port(काष्ठा uart_port *port)
अणु
पूर्ण

अटल पूर्णांक asc_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

/*
 * Called when the port is खोलोed, and UPF_BOOT_AUTOCONF flag is set
 * Set type field अगर successful
 */
अटल व्योम asc_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर ((flags & UART_CONFIG_TYPE))
		port->type = PORT_ASC;
पूर्ण

अटल पूर्णांक
asc_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	/* No user changeable parameters */
	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL
/*
 * Console polling routines क्रम writing and पढ़ोing from the uart जबतक
 * in an पूर्णांकerrupt or debug context (i.e. kgdb).
 */

अटल पूर्णांक asc_get_poll_अक्षर(काष्ठा uart_port *port)
अणु
	अगर (!(asc_in(port, ASC_STA) & ASC_STA_RBF))
		वापस NO_POLL_CHAR;

	वापस asc_in(port, ASC_RXBUF);
पूर्ण

अटल व्योम asc_put_poll_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर c)
अणु
	जबतक (!asc_txfअगरo_is_half_empty(port))
		cpu_relax();
	asc_out(port, ASC_TXBUF, c);
पूर्ण

#पूर्ण_अगर /* CONFIG_CONSOLE_POLL */

/*---------------------------------------------------------------------*/

अटल स्थिर काष्ठा uart_ops asc_uart_ops = अणु
	.tx_empty	= asc_tx_empty,
	.set_mctrl	= asc_set_mctrl,
	.get_mctrl	= asc_get_mctrl,
	.start_tx	= asc_start_tx,
	.stop_tx	= asc_stop_tx,
	.stop_rx	= asc_stop_rx,
	.अवरोध_ctl	= asc_अवरोध_ctl,
	.startup	= asc_startup,
	.shutकरोwn	= asc_shutकरोwn,
	.set_termios	= asc_set_termios,
	.type		= asc_type,
	.release_port	= asc_release_port,
	.request_port	= asc_request_port,
	.config_port	= asc_config_port,
	.verअगरy_port	= asc_verअगरy_port,
	.pm		= asc_pm,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_get_अक्षर = asc_get_poll_अक्षर,
	.poll_put_अक्षर = asc_put_poll_अक्षर,
#पूर्ण_अगर /* CONFIG_CONSOLE_POLL */
पूर्ण;

अटल पूर्णांक asc_init_port(काष्ठा asc_port *ascport,
			  काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port = &ascport->port;
	काष्ठा resource *res;
	पूर्णांक ret;

	port->iotype	= UPIO_MEM;
	port->flags	= UPF_BOOT_AUTOCONF;
	port->ops	= &asc_uart_ops;
	port->fअगरosize	= ASC_FIFO_SIZE;
	port->dev	= &pdev->dev;
	port->irq	= platक्रमm_get_irq(pdev, 0);
	port->has_sysrq = IS_ENABLED(CONFIG_SERIAL_ST_ASC_CONSOLE);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	port->membase = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(port->membase))
		वापस PTR_ERR(port->membase);
	port->mapbase = res->start;

	spin_lock_init(&port->lock);

	ascport->clk = devm_clk_get(&pdev->dev, शून्य);

	अगर (WARN_ON(IS_ERR(ascport->clk)))
		वापस -EINVAL;
	/* ensure that clk rate is correct by enabling the clk */
	clk_prepare_enable(ascport->clk);
	ascport->port.uartclk = clk_get_rate(ascport->clk);
	WARN_ON(ascport->port.uartclk == 0);
	clk_disable_unprepare(ascport->clk);

	ascport->pinctrl = devm_pinctrl_get(&pdev->dev);
	अगर (IS_ERR(ascport->pinctrl)) अणु
		ret = PTR_ERR(ascport->pinctrl);
		dev_err(&pdev->dev, "Failed to get Pinctrl: %d\n", ret);
		वापस ret;
	पूर्ण

	ascport->states[DEFAULT] =
		pinctrl_lookup_state(ascport->pinctrl, "default");
	अगर (IS_ERR(ascport->states[DEFAULT])) अणु
		ret = PTR_ERR(ascport->states[DEFAULT]);
		dev_err(&pdev->dev,
			"Failed to look up Pinctrl state 'default': %d\n", ret);
		वापस ret;
	पूर्ण

	/* "no-hw-flowctrl" state is optional */
	ascport->states[NO_HW_FLOWCTRL] =
		pinctrl_lookup_state(ascport->pinctrl, "no-hw-flowctrl");
	अगर (IS_ERR(ascport->states[NO_HW_FLOWCTRL]))
		ascport->states[NO_HW_FLOWCTRL] = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा asc_port *asc_of_get_asc_port(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक id;

	अगर (!np)
		वापस शून्य;

	id = of_alias_get_id(np, "serial");
	अगर (id < 0)
		id = of_alias_get_id(np, ASC_SERIAL_NAME);

	अगर (id < 0)
		id = 0;

	अगर (WARN_ON(id >= ASC_MAX_PORTS))
		वापस शून्य;

	asc_ports[id].hw_flow_control = of_property_पढ़ो_bool(np,
							"uart-has-rtscts");
	asc_ports[id].क्रमce_m1 =  of_property_पढ़ो_bool(np, "st,force_m1");
	asc_ports[id].port.line = id;
	asc_ports[id].rts = शून्य;

	वापस &asc_ports[id];
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id asc_match[] = अणु
	अणु .compatible = "st,asc", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, asc_match);
#पूर्ण_अगर

अटल पूर्णांक asc_serial_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा asc_port *ascport;

	ascport = asc_of_get_asc_port(pdev);
	अगर (!ascport)
		वापस -ENODEV;

	ret = asc_init_port(ascport, pdev);
	अगर (ret)
		वापस ret;

	ret = uart_add_one_port(&asc_uart_driver, &ascport->port);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, &ascport->port);

	वापस 0;
पूर्ण

अटल पूर्णांक asc_serial_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port = platक्रमm_get_drvdata(pdev);

	वापस uart_हटाओ_one_port(&asc_uart_driver, port);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक asc_serial_suspend(काष्ठा device *dev)
अणु
	काष्ठा uart_port *port = dev_get_drvdata(dev);

	वापस uart_suspend_port(&asc_uart_driver, port);
पूर्ण

अटल पूर्णांक asc_serial_resume(काष्ठा device *dev)
अणु
	काष्ठा uart_port *port = dev_get_drvdata(dev);

	वापस uart_resume_port(&asc_uart_driver, port);
पूर्ण

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

/*----------------------------------------------------------------------*/

#अगर_घोषित CONFIG_SERIAL_ST_ASC_CONSOLE
अटल व्योम asc_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	अचिन्हित पूर्णांक समयout = 1000000;

	/* Wait क्रम upto 1 second in हाल flow control is stopping us. */
	जबतक (--समयout && !asc_txfअगरo_is_half_empty(port))
		udelay(1);

	asc_out(port, ASC_TXBUF, ch);
पूर्ण

/*
 *  Prपूर्णांक a string to the serial port trying not to disturb
 *  any possible real use of the port...
 */

अटल व्योम asc_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, अचिन्हित count)
अणु
	काष्ठा uart_port *port = &asc_ports[co->index].port;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ समयout = 1000000;
	पूर्णांक locked = 1;
	u32 पूर्णांकenable;

	अगर (port->sysrq)
		locked = 0; /* asc_पूर्णांकerrupt has alपढ़ोy claimed the lock */
	अन्यथा अगर (oops_in_progress)
		locked = spin_trylock_irqsave(&port->lock, flags);
	अन्यथा
		spin_lock_irqsave(&port->lock, flags);

	/*
	 * Disable पूर्णांकerrupts so we करोn't get the IRQ line bouncing
	 * up and करोwn जबतक पूर्णांकerrupts are disabled.
	 */
	पूर्णांकenable = asc_in(port, ASC_INTEN);
	asc_out(port, ASC_INTEN, 0);
	(व्योम)asc_in(port, ASC_INTEN);	/* Defeat bus ग_लिखो posting */

	uart_console_ग_लिखो(port, s, count, asc_console_अक्षर_दो);

	जबतक (--समयout && !asc_txfअगरo_is_empty(port))
		udelay(1);

	asc_out(port, ASC_INTEN, पूर्णांकenable);

	अगर (locked)
		spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल पूर्णांक asc_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा asc_port *ascport;
	पूर्णांक baud = 115200;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	अगर (co->index >= ASC_MAX_PORTS)
		वापस -ENODEV;

	ascport = &asc_ports[co->index];

	/*
	 * This driver करोes not support early console initialization
	 * (use ARM early prपूर्णांकk support instead), so we only expect
	 * this to be called during the uart port registration when the
	 * driver माला_लो probed and the port should be mapped at that poपूर्णांक.
	 */
	अगर (ascport->port.mapbase == 0 || ascport->port.membase == शून्य)
		वापस -ENXIO;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(&ascport->port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा console asc_console = अणु
	.name		= ASC_SERIAL_NAME,
	.device		= uart_console_device,
	.ग_लिखो		= asc_console_ग_लिखो,
	.setup		= asc_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &asc_uart_driver,
पूर्ण;

#घोषणा ASC_SERIAL_CONSOLE (&asc_console)

#अन्यथा
#घोषणा ASC_SERIAL_CONSOLE शून्य
#पूर्ण_अगर /* CONFIG_SERIAL_ST_ASC_CONSOLE */

अटल काष्ठा uart_driver asc_uart_driver = अणु
	.owner		= THIS_MODULE,
	.driver_name	= DRIVER_NAME,
	.dev_name	= ASC_SERIAL_NAME,
	.major		= 0,
	.minor		= 0,
	.nr		= ASC_MAX_PORTS,
	.cons		= ASC_SERIAL_CONSOLE,
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops asc_serial_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(asc_serial_suspend, asc_serial_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver asc_serial_driver = अणु
	.probe		= asc_serial_probe,
	.हटाओ		= asc_serial_हटाओ,
	.driver	= अणु
		.name	= DRIVER_NAME,
		.pm	= &asc_serial_pm_ops,
		.of_match_table = of_match_ptr(asc_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init asc_init(व्योम)
अणु
	पूर्णांक ret;
	अटल स्थिर अक्षर banner[] __initस्थिर =
		KERN_INFO "STMicroelectronics ASC driver initialized\n";

	prपूर्णांकk(banner);

	ret = uart_रेजिस्टर_driver(&asc_uart_driver);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&asc_serial_driver);
	अगर (ret)
		uart_unरेजिस्टर_driver(&asc_uart_driver);

	वापस ret;
पूर्ण

अटल व्योम __निकास asc_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&asc_serial_driver);
	uart_unरेजिस्टर_driver(&asc_uart_driver);
पूर्ण

module_init(asc_init);
module_निकास(asc_निकास);

MODULE_ALIAS("platform:" DRIVER_NAME);
MODULE_AUTHOR("STMicroelectronics (R&D) Limited");
MODULE_DESCRIPTION("STMicroelectronics ASC serial port driver");
MODULE_LICENSE("GPL");
