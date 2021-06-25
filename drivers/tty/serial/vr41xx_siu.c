<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Driver क्रम NEC VR4100 series Serial Interface Unit.
 *
 *  Copyright (C) 2004-2008  Yoichi Yuasa <yuasa@linux-mips.org>
 *
 *  Based on drivers/serial/8250.c, by Russell King.
 */

#समावेश <linux/console.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/vr41xx/siu.h>
#समावेश <यंत्र/vr41xx/vr41xx.h>

#घोषणा SIU_BAUD_BASE	1152000
#घोषणा SIU_MAJOR	204
#घोषणा SIU_MINOR_BASE	82

#घोषणा RX_MAX_COUNT	256
#घोषणा TX_MAX_COUNT	15

#घोषणा SIUIRSEL	0x08
 #घोषणा TMICMODE	0x20
 #घोषणा TMICTX		0x10
 #घोषणा IRMSEL		0x0c
 #घोषणा IRMSEL_HP	0x08
 #घोषणा IRMSEL_TEMIC	0x04
 #घोषणा IRMSEL_SHARP	0x00
 #घोषणा IRUSESEL	0x02
 #घोषणा SIRSEL		0x01

अटल काष्ठा uart_port siu_uart_ports[SIU_PORTS_MAX] = अणु
	[0 ... SIU_PORTS_MAX-1] = अणु
		.lock	= __SPIN_LOCK_UNLOCKED(siu_uart_ports->lock),
		.irq	= 0,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_SERIAL_VR41XX_CONSOLE
अटल uपूर्णांक8_t lsr_अवरोध_flag[SIU_PORTS_MAX];
#पूर्ण_अगर

#घोषणा siu_पढ़ो(port, offset)		पढ़ोb((port)->membase + (offset))
#घोषणा siu_ग_लिखो(port, offset, value)	ग_लिखोb((value), (port)->membase + (offset))

व्योम vr41xx_select_siu_पूर्णांकerface(siu_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा uart_port *port;
	अचिन्हित दीर्घ flags;
	uपूर्णांक8_t irsel;

	port = &siu_uart_ports[0];

	spin_lock_irqsave(&port->lock, flags);

	irsel = siu_पढ़ो(port, SIUIRSEL);
	अगर (पूर्णांकerface == SIU_INTERFACE_IRDA)
		irsel |= SIRSEL;
	अन्यथा
		irsel &= ~SIRSEL;
	siu_ग_लिखो(port, SIUIRSEL, irsel);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(vr41xx_select_siu_पूर्णांकerface);

व्योम vr41xx_use_irda(irda_use_t use)
अणु
	काष्ठा uart_port *port;
	अचिन्हित दीर्घ flags;
	uपूर्णांक8_t irsel;

	port = &siu_uart_ports[0];

	spin_lock_irqsave(&port->lock, flags);

	irsel = siu_पढ़ो(port, SIUIRSEL);
	अगर (use == FIR_USE_IRDA)
		irsel |= IRUSESEL;
	अन्यथा
		irsel &= ~IRUSESEL;
	siu_ग_लिखो(port, SIUIRSEL, irsel);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(vr41xx_use_irda);

व्योम vr41xx_select_irda_module(irda_module_t module, irda_speed_t speed)
अणु
	काष्ठा uart_port *port;
	अचिन्हित दीर्घ flags;
	uपूर्णांक8_t irsel;

	port = &siu_uart_ports[0];

	spin_lock_irqsave(&port->lock, flags);

	irsel = siu_पढ़ो(port, SIUIRSEL);
	irsel &= ~(IRMSEL | TMICTX | TMICMODE);
	चयन (module) अणु
	हाल SHARP_IRDA:
		irsel |= IRMSEL_SHARP;
		अवरोध;
	हाल TEMIC_IRDA:
		irsel |= IRMSEL_TEMIC | TMICMODE;
		अगर (speed == IRDA_TX_4MBPS)
			irsel |= TMICTX;
		अवरोध;
	हाल HP_IRDA:
		irsel |= IRMSEL_HP;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	siu_ग_लिखो(port, SIUIRSEL, irsel);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(vr41xx_select_irda_module);

अटल अंतरभूत व्योम siu_clear_fअगरo(काष्ठा uart_port *port)
अणु
	siu_ग_लिखो(port, UART_FCR, UART_FCR_ENABLE_FIFO);
	siu_ग_लिखो(port, UART_FCR, UART_FCR_ENABLE_FIFO | UART_FCR_CLEAR_RCVR |
	                          UART_FCR_CLEAR_XMIT);
	siu_ग_लिखो(port, UART_FCR, 0);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ siu_port_size(काष्ठा uart_port *port)
अणु
	चयन (port->type) अणु
	हाल PORT_VR41XX_SIU:
		वापस 11UL;
	हाल PORT_VR41XX_DSIU:
		वापस 8UL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक siu_check_type(काष्ठा uart_port *port)
अणु
	अगर (port->line == 0)
		वापस PORT_VR41XX_SIU;
	अगर (port->line == 1 && port->irq)
		वापस PORT_VR41XX_DSIU;

	वापस PORT_UNKNOWN;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *siu_type_name(काष्ठा uart_port *port)
अणु
	चयन (port->type) अणु
	हाल PORT_VR41XX_SIU:
		वापस "SIU";
	हाल PORT_VR41XX_DSIU:
		वापस "DSIU";
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अचिन्हित पूर्णांक siu_tx_empty(काष्ठा uart_port *port)
अणु
	uपूर्णांक8_t lsr;

	lsr = siu_पढ़ो(port, UART_LSR);
	अगर (lsr & UART_LSR_TEMT)
		वापस TIOCSER_TEMT;

	वापस 0;
पूर्ण

अटल व्योम siu_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	uपूर्णांक8_t mcr = 0;

	अगर (mctrl & TIOCM_DTR)
		mcr |= UART_MCR_DTR;
	अगर (mctrl & TIOCM_RTS)
		mcr |= UART_MCR_RTS;
	अगर (mctrl & TIOCM_OUT1)
		mcr |= UART_MCR_OUT1;
	अगर (mctrl & TIOCM_OUT2)
		mcr |= UART_MCR_OUT2;
	अगर (mctrl & TIOCM_LOOP)
		mcr |= UART_MCR_LOOP;

	siu_ग_लिखो(port, UART_MCR, mcr);
पूर्ण

अटल अचिन्हित पूर्णांक siu_get_mctrl(काष्ठा uart_port *port)
अणु
	uपूर्णांक8_t msr;
	अचिन्हित पूर्णांक mctrl = 0;

	msr = siu_पढ़ो(port, UART_MSR);
	अगर (msr & UART_MSR_DCD)
		mctrl |= TIOCM_CAR;
	अगर (msr & UART_MSR_RI)
		mctrl |= TIOCM_RNG;
	अगर (msr & UART_MSR_DSR)
		mctrl |= TIOCM_DSR;
	अगर (msr & UART_MSR_CTS)
		mctrl |= TIOCM_CTS;

	वापस mctrl;
पूर्ण

अटल व्योम siu_stop_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक8_t ier;

	spin_lock_irqsave(&port->lock, flags);

	ier = siu_पढ़ो(port, UART_IER);
	ier &= ~UART_IER_THRI;
	siu_ग_लिखो(port, UART_IER, ier);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम siu_start_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक8_t ier;

	spin_lock_irqsave(&port->lock, flags);

	ier = siu_पढ़ो(port, UART_IER);
	ier |= UART_IER_THRI;
	siu_ग_लिखो(port, UART_IER, ier);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम siu_stop_rx(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक8_t ier;

	spin_lock_irqsave(&port->lock, flags);

	ier = siu_पढ़ो(port, UART_IER);
	ier &= ~UART_IER_RLSI;
	siu_ग_लिखो(port, UART_IER, ier);

	port->पढ़ो_status_mask &= ~UART_LSR_DR;

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम siu_enable_ms(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक8_t ier;

	spin_lock_irqsave(&port->lock, flags);

	ier = siu_पढ़ो(port, UART_IER);
	ier |= UART_IER_MSI;
	siu_ग_लिखो(port, UART_IER, ier);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम siu_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक ctl)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक8_t lcr;

	spin_lock_irqsave(&port->lock, flags);

	lcr = siu_पढ़ो(port, UART_LCR);
	अगर (ctl == -1)
		lcr |= UART_LCR_SBC;
	अन्यथा
		lcr &= ~UART_LCR_SBC;
	siu_ग_लिखो(port, UART_LCR, lcr);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल अंतरभूत व्योम receive_अक्षरs(काष्ठा uart_port *port, uपूर्णांक8_t *status)
अणु
	uपूर्णांक8_t lsr, ch;
	अक्षर flag;
	पूर्णांक max_count = RX_MAX_COUNT;

	lsr = *status;

	करो अणु
		ch = siu_पढ़ो(port, UART_RX);
		port->icount.rx++;
		flag = TTY_NORMAL;

#अगर_घोषित CONFIG_SERIAL_VR41XX_CONSOLE
		lsr |= lsr_अवरोध_flag[port->line];
		lsr_अवरोध_flag[port->line] = 0;
#पूर्ण_अगर
		अगर (unlikely(lsr & (UART_LSR_BI | UART_LSR_FE |
		                    UART_LSR_PE | UART_LSR_OE))) अणु
			अगर (lsr & UART_LSR_BI) अणु
				lsr &= ~(UART_LSR_FE | UART_LSR_PE);
				port->icount.brk++;

				अगर (uart_handle_अवरोध(port))
					जाओ ignore_अक्षर;
			पूर्ण

			अगर (lsr & UART_LSR_FE)
				port->icount.frame++;
			अगर (lsr & UART_LSR_PE)
				port->icount.parity++;
			अगर (lsr & UART_LSR_OE)
				port->icount.overrun++;

			lsr &= port->पढ़ो_status_mask;
			अगर (lsr & UART_LSR_BI)
				flag = TTY_BREAK;
			अगर (lsr & UART_LSR_FE)
				flag = TTY_FRAME;
			अगर (lsr & UART_LSR_PE)
				flag = TTY_PARITY;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(port, ch))
			जाओ ignore_अक्षर;

		uart_insert_अक्षर(port, lsr, UART_LSR_OE, ch, flag);

	ignore_अक्षर:
		lsr = siu_पढ़ो(port, UART_LSR);
	पूर्ण जबतक ((lsr & UART_LSR_DR) && (max_count-- > 0));

	tty_flip_buffer_push(&port->state->port);

	*status = lsr;
पूर्ण

अटल अंतरभूत व्योम check_modem_status(काष्ठा uart_port *port)
अणु
	uपूर्णांक8_t msr;

	msr = siu_पढ़ो(port, UART_MSR);
	अगर ((msr & UART_MSR_ANY_DELTA) == 0)
		वापस;
	अगर (msr & UART_MSR_DDCD)
		uart_handle_dcd_change(port, msr & UART_MSR_DCD);
	अगर (msr & UART_MSR_TERI)
		port->icount.rng++;
	अगर (msr & UART_MSR_DDSR)
		port->icount.dsr++;
	अगर (msr & UART_MSR_DCTS)
		uart_handle_cts_change(port, msr & UART_MSR_CTS);

	wake_up_पूर्णांकerruptible(&port->state->port.delta_msr_रुको);
पूर्ण

अटल अंतरभूत व्योम transmit_अक्षरs(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit;
	पूर्णांक max_count = TX_MAX_COUNT;

	xmit = &port->state->xmit;

	अगर (port->x_अक्षर) अणु
		siu_ग_लिखो(port, UART_TX, port->x_अक्षर);
		port->icount.tx++;
		port->x_अक्षर = 0;
		वापस;
	पूर्ण

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port)) अणु
		siu_stop_tx(port);
		वापस;
	पूर्ण

	करो अणु
		siu_ग_लिखो(port, UART_TX, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
		अगर (uart_circ_empty(xmit))
			अवरोध;
	पूर्ण जबतक (max_count-- > 0);

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (uart_circ_empty(xmit))
		siu_stop_tx(port);
पूर्ण

अटल irqवापस_t siu_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *port;
	uपूर्णांक8_t iir, lsr;

	port = (काष्ठा uart_port *)dev_id;

	iir = siu_पढ़ो(port, UART_IIR);
	अगर (iir & UART_IIR_NO_INT)
		वापस IRQ_NONE;

	lsr = siu_पढ़ो(port, UART_LSR);
	अगर (lsr & UART_LSR_DR)
		receive_अक्षरs(port, &lsr);

	check_modem_status(port);

	अगर (lsr & UART_LSR_THRE)
		transmit_अक्षरs(port);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक siu_startup(काष्ठा uart_port *port)
अणु
	पूर्णांक retval;

	अगर (port->membase == शून्य)
		वापस -ENODEV;

	siu_clear_fअगरo(port);

	(व्योम)siu_पढ़ो(port, UART_LSR);
	(व्योम)siu_पढ़ो(port, UART_RX);
	(व्योम)siu_पढ़ो(port, UART_IIR);
	(व्योम)siu_पढ़ो(port, UART_MSR);

	अगर (siu_पढ़ो(port, UART_LSR) == 0xff)
		वापस -ENODEV;

	retval = request_irq(port->irq, siu_पूर्णांकerrupt, 0, siu_type_name(port), port);
	अगर (retval)
		वापस retval;

	अगर (port->type == PORT_VR41XX_DSIU)
		vr41xx_enable_dsiuपूर्णांक(DSIUINT_ALL);

	siu_ग_लिखो(port, UART_LCR, UART_LCR_WLEN8);

	spin_lock_irq(&port->lock);
	siu_set_mctrl(port, port->mctrl);
	spin_unlock_irq(&port->lock);

	siu_ग_लिखो(port, UART_IER, UART_IER_RLSI | UART_IER_RDI);

	(व्योम)siu_पढ़ो(port, UART_LSR);
	(व्योम)siu_पढ़ो(port, UART_RX);
	(व्योम)siu_पढ़ो(port, UART_IIR);
	(व्योम)siu_पढ़ो(port, UART_MSR);

	वापस 0;
पूर्ण

अटल व्योम siu_shutकरोwn(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ flags;
	uपूर्णांक8_t lcr;

	siu_ग_लिखो(port, UART_IER, 0);

	spin_lock_irqsave(&port->lock, flags);

	port->mctrl &= ~TIOCM_OUT2;
	siu_set_mctrl(port, port->mctrl);

	spin_unlock_irqrestore(&port->lock, flags);

	lcr = siu_पढ़ो(port, UART_LCR);
	lcr &= ~UART_LCR_SBC;
	siu_ग_लिखो(port, UART_LCR, lcr);

	siu_clear_fअगरo(port);

	(व्योम)siu_पढ़ो(port, UART_RX);

	अगर (port->type == PORT_VR41XX_DSIU)
		vr41xx_disable_dsiuपूर्णांक(DSIUINT_ALL);

	मुक्त_irq(port->irq, port);
पूर्ण

अटल व्योम siu_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *new,
                            काष्ठा ktermios *old)
अणु
	tcflag_t c_cflag, c_अगरlag;
	uपूर्णांक8_t lcr, fcr, ier;
	अचिन्हित पूर्णांक baud, quot;
	अचिन्हित दीर्घ flags;

	c_cflag = new->c_cflag;
	चयन (c_cflag & CSIZE) अणु
	हाल CS5:
		lcr = UART_LCR_WLEN5;
		अवरोध;
	हाल CS6:
		lcr = UART_LCR_WLEN6;
		अवरोध;
	हाल CS7:
		lcr = UART_LCR_WLEN7;
		अवरोध;
	शेष:
		lcr = UART_LCR_WLEN8;
		अवरोध;
	पूर्ण

	अगर (c_cflag & CSTOPB)
		lcr |= UART_LCR_STOP;
	अगर (c_cflag & PARENB)
		lcr |= UART_LCR_PARITY;
	अगर ((c_cflag & PARODD) != PARODD)
		lcr |= UART_LCR_EPAR;
	अगर (c_cflag & CMSPAR)
		lcr |= UART_LCR_SPAR;

	baud = uart_get_baud_rate(port, new, old, 0, port->uartclk/16);
	quot = uart_get_भागisor(port, baud);

	fcr = UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_10;

	spin_lock_irqsave(&port->lock, flags);

	uart_update_समयout(port, c_cflag, baud);

	c_अगरlag = new->c_अगरlag;

	port->पढ़ो_status_mask = UART_LSR_THRE | UART_LSR_OE | UART_LSR_DR;
	अगर (c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= UART_LSR_FE | UART_LSR_PE;
	अगर (c_अगरlag & (IGNBRK | BRKINT | PARMRK))
		port->पढ़ो_status_mask |= UART_LSR_BI;

	port->ignore_status_mask = 0;
	अगर (c_अगरlag & IGNPAR)
		port->ignore_status_mask |= UART_LSR_FE | UART_LSR_PE;
	अगर (c_अगरlag & IGNBRK) अणु
		port->ignore_status_mask |= UART_LSR_BI;
		अगर (c_अगरlag & IGNPAR)
			port->ignore_status_mask |= UART_LSR_OE;
	पूर्ण

	अगर ((c_cflag & CREAD) == 0)
		port->ignore_status_mask |= UART_LSR_DR;

	ier = siu_पढ़ो(port, UART_IER);
	ier &= ~UART_IER_MSI;
	अगर (UART_ENABLE_MS(port, c_cflag))
		ier |= UART_IER_MSI;
	siu_ग_लिखो(port, UART_IER, ier);

	siu_ग_लिखो(port, UART_LCR, lcr | UART_LCR_DLAB);

	siu_ग_लिखो(port, UART_DLL, (uपूर्णांक8_t)quot);
	siu_ग_लिखो(port, UART_DLM, (uपूर्णांक8_t)(quot >> 8));

	siu_ग_लिखो(port, UART_LCR, lcr);

	siu_ग_लिखो(port, UART_FCR, fcr);

	siu_set_mctrl(port, port->mctrl);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम siu_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state, अचिन्हित पूर्णांक oldstate)
अणु
	चयन (state) अणु
	हाल 0:
		चयन (port->type) अणु
		हाल PORT_VR41XX_SIU:
			vr41xx_supply_घड़ी(SIU_CLOCK);
			अवरोध;
		हाल PORT_VR41XX_DSIU:
			vr41xx_supply_घड़ी(DSIU_CLOCK);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 3:
		चयन (port->type) अणु
		हाल PORT_VR41XX_SIU:
			vr41xx_mask_घड़ी(SIU_CLOCK);
			अवरोध;
		हाल PORT_VR41XX_DSIU:
			vr41xx_mask_घड़ी(DSIU_CLOCK);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *siu_type(काष्ठा uart_port *port)
अणु
	वापस siu_type_name(port);
पूर्ण

अटल व्योम siu_release_port(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ size;

	अगर (port->flags	& UPF_IOREMAP) अणु
		iounmap(port->membase);
		port->membase = शून्य;
	पूर्ण

	size = siu_port_size(port);
	release_mem_region(port->mapbase, size);
पूर्ण

अटल पूर्णांक siu_request_port(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ size;
	काष्ठा resource *res;

	size = siu_port_size(port);
	res = request_mem_region(port->mapbase, size, siu_type_name(port));
	अगर (res == शून्य)
		वापस -EBUSY;

	अगर (port->flags & UPF_IOREMAP) अणु
		port->membase = ioremap(port->mapbase, size);
		अगर (port->membase == शून्य) अणु
			release_resource(res);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम siu_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE) अणु
		port->type = siu_check_type(port);
		(व्योम)siu_request_port(port);
	पूर्ण
पूर्ण

अटल पूर्णांक siu_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *serial)
अणु
	अगर (port->type != PORT_VR41XX_SIU && port->type != PORT_VR41XX_DSIU)
		वापस -EINVAL;
	अगर (port->irq != serial->irq)
		वापस -EINVAL;
	अगर (port->iotype != serial->io_type)
		वापस -EINVAL;
	अगर (port->mapbase != (अचिन्हित दीर्घ)serial->iomem_base)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा uart_ops siu_uart_ops = अणु
	.tx_empty	= siu_tx_empty,
	.set_mctrl	= siu_set_mctrl,
	.get_mctrl	= siu_get_mctrl,
	.stop_tx	= siu_stop_tx,
	.start_tx	= siu_start_tx,
	.stop_rx	= siu_stop_rx,
	.enable_ms	= siu_enable_ms,
	.अवरोध_ctl	= siu_अवरोध_ctl,
	.startup	= siu_startup,
	.shutकरोwn	= siu_shutकरोwn,
	.set_termios	= siu_set_termios,
	.pm		= siu_pm,
	.type		= siu_type,
	.release_port	= siu_release_port,
	.request_port	= siu_request_port,
	.config_port	= siu_config_port,
	.verअगरy_port	= siu_verअगरy_port,
पूर्ण;

अटल पूर्णांक siu_init_ports(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *port;
	काष्ठा resource *res;
	पूर्णांक *type = dev_get_platdata(&pdev->dev);
	पूर्णांक i;

	अगर (!type)
		वापस 0;

	port = siu_uart_ports;
	क्रम (i = 0; i < SIU_PORTS_MAX; i++) अणु
		port->type = type[i];
		अगर (port->type == PORT_UNKNOWN)
			जारी;
		port->irq = platक्रमm_get_irq(pdev, i);
		port->uartclk = SIU_BAUD_BASE * 16;
		port->fअगरosize = 16;
		port->regshअगरt = 0;
		port->iotype = UPIO_MEM;
		port->flags = UPF_IOREMAP | UPF_BOOT_AUTOCONF;
		port->line = i;
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, i);
		port->mapbase = res->start;
		port++;
	पूर्ण

	वापस i;
पूर्ण

#अगर_घोषित CONFIG_SERIAL_VR41XX_CONSOLE

#घोषणा BOTH_EMPTY	(UART_LSR_TEMT | UART_LSR_THRE)

अटल व्योम रुको_क्रम_xmitr(काष्ठा uart_port *port)
अणु
	पूर्णांक समयout = 10000;
	uपूर्णांक8_t lsr, msr;

	करो अणु
		lsr = siu_पढ़ो(port, UART_LSR);
		अगर (lsr & UART_LSR_BI)
			lsr_अवरोध_flag[port->line] = UART_LSR_BI;

		अगर ((lsr & BOTH_EMPTY) == BOTH_EMPTY)
			अवरोध;
	पूर्ण जबतक (समयout-- > 0);

	अगर (port->flags & UPF_CONS_FLOW) अणु
		समयout = 1000000;

		करो अणु
			msr = siu_पढ़ो(port, UART_MSR);
			अगर ((msr & UART_MSR_CTS) != 0)
				अवरोध;
		पूर्ण जबतक (समयout-- > 0);
	पूर्ण
पूर्ण

अटल व्योम siu_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	रुको_क्रम_xmitr(port);
	siu_ग_लिखो(port, UART_TX, ch);
पूर्ण

अटल व्योम siu_console_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित count)
अणु
	काष्ठा uart_port *port;
	uपूर्णांक8_t ier;

	port = &siu_uart_ports[con->index];

	ier = siu_पढ़ो(port, UART_IER);
	siu_ग_लिखो(port, UART_IER, 0);

	uart_console_ग_लिखो(port, s, count, siu_console_अक्षर_दो);

	रुको_क्रम_xmitr(port);
	siu_ग_लिखो(port, UART_IER, ier);
पूर्ण

अटल पूर्णांक __init siu_console_setup(काष्ठा console *con, अक्षर *options)
अणु
	काष्ठा uart_port *port;
	पूर्णांक baud = 9600;
	पूर्णांक parity = 'n';
	पूर्णांक bits = 8;
	पूर्णांक flow = 'n';

	अगर (con->index >= SIU_PORTS_MAX)
		con->index = 0;

	port = &siu_uart_ports[con->index];
	अगर (port->membase == शून्य) अणु
		अगर (port->mapbase == 0)
			वापस -ENODEV;
		port->membase = ioremap(port->mapbase, siu_port_size(port));
	पूर्ण

	अगर (port->type == PORT_VR41XX_SIU)
		vr41xx_select_siu_पूर्णांकerface(SIU_INTERFACE_RS232C);

	अगर (options != शून्य)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(port, con, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver siu_uart_driver;

अटल काष्ठा console siu_console = अणु
	.name	= "ttyVR",
	.ग_लिखो	= siu_console_ग_लिखो,
	.device	= uart_console_device,
	.setup	= siu_console_setup,
	.flags	= CON_PRINTBUFFER,
	.index	= -1,
	.data	= &siu_uart_driver,
पूर्ण;

अटल पूर्णांक siu_console_init(व्योम)
अणु
	काष्ठा uart_port *port;
	पूर्णांक i;

	क्रम (i = 0; i < SIU_PORTS_MAX; i++) अणु
		port = &siu_uart_ports[i];
		port->ops = &siu_uart_ops;
	पूर्ण

	रेजिस्टर_console(&siu_console);

	वापस 0;
पूर्ण

console_initcall(siu_console_init);

व्योम __init vr41xx_siu_early_setup(काष्ठा uart_port *port)
अणु
	अगर (port->type == PORT_UNKNOWN)
		वापस;

	siu_uart_ports[port->line].line = port->line;
	siu_uart_ports[port->line].type = port->type;
	siu_uart_ports[port->line].uartclk = SIU_BAUD_BASE * 16;
	siu_uart_ports[port->line].mapbase = port->mapbase;
	siu_uart_ports[port->line].ops = &siu_uart_ops;
पूर्ण

#घोषणा SERIAL_VR41XX_CONSOLE	&siu_console
#अन्यथा
#घोषणा SERIAL_VR41XX_CONSOLE	शून्य
#पूर्ण_अगर

अटल काष्ठा uart_driver siu_uart_driver = अणु
	.owner		= THIS_MODULE,
	.driver_name	= "SIU",
	.dev_name	= "ttyVR",
	.major		= SIU_MAJOR,
	.minor		= SIU_MINOR_BASE,
	.cons		= SERIAL_VR41XX_CONSOLE,
पूर्ण;

अटल पूर्णांक siu_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा uart_port *port;
	पूर्णांक num, i, retval;

	num = siu_init_ports(dev);
	अगर (num <= 0)
		वापस -ENODEV;

	siu_uart_driver.nr = num;
	retval = uart_रेजिस्टर_driver(&siu_uart_driver);
	अगर (retval)
		वापस retval;

	क्रम (i = 0; i < num; i++) अणु
		port = &siu_uart_ports[i];
		port->ops = &siu_uart_ops;
		port->dev = &dev->dev;
		port->has_sysrq = IS_ENABLED(CONFIG_SERIAL_VR41XX_CONSOLE);

		retval = uart_add_one_port(&siu_uart_driver, port);
		अगर (retval < 0) अणु
			port->dev = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == 0 && retval < 0) अणु
		uart_unरेजिस्टर_driver(&siu_uart_driver);
		वापस retval;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक siu_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा uart_port *port;
	पूर्णांक i;

	क्रम (i = 0; i < siu_uart_driver.nr; i++) अणु
		port = &siu_uart_ports[i];
		अगर (port->dev == &dev->dev) अणु
			uart_हटाओ_one_port(&siu_uart_driver, port);
			port->dev = शून्य;
		पूर्ण
	पूर्ण

	uart_unरेजिस्टर_driver(&siu_uart_driver);

	वापस 0;
पूर्ण

अटल पूर्णांक siu_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	काष्ठा uart_port *port;
	पूर्णांक i;

	क्रम (i = 0; i < siu_uart_driver.nr; i++) अणु
		port = &siu_uart_ports[i];
		अगर ((port->type == PORT_VR41XX_SIU ||
		     port->type == PORT_VR41XX_DSIU) && port->dev == &dev->dev)
			uart_suspend_port(&siu_uart_driver, port);

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक siu_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा uart_port *port;
	पूर्णांक i;

	क्रम (i = 0; i < siu_uart_driver.nr; i++) अणु
		port = &siu_uart_ports[i];
		अगर ((port->type == PORT_VR41XX_SIU ||
		     port->type == PORT_VR41XX_DSIU) && port->dev == &dev->dev)
			uart_resume_port(&siu_uart_driver, port);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver siu_device_driver = अणु
	.probe		= siu_probe,
	.हटाओ		= siu_हटाओ,
	.suspend	= siu_suspend,
	.resume		= siu_resume,
	.driver		= अणु
		.name	= "SIU",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(siu_device_driver);

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:SIU");
