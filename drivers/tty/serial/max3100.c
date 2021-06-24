<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *
 *  Copyright (C) 2008 Christian Pellegrin <chripell@evolware.org>
 *
 * Notes: the MAX3100 करोesn't provide an पूर्णांकerrupt on CTS so we have
 * to use polling क्रम flow control. TX empty IRQ is unusable, since
 * writing conf clears FIFO buffer and we cannot have this पूर्णांकerrupt
 * always asking us क्रम attention.
 *
 * Example platक्रमm data:

 अटल काष्ठा plat_max3100 max3100_plat_data = अणु
 .loopback = 0,
 .crystal = 0,
 .poll_समय = 100,
 पूर्ण;

 अटल काष्ठा spi_board_info spi_board_info[] = अणु
 अणु
 .modalias	= "max3100",
 .platक्रमm_data	= &max3100_plat_data,
 .irq		= IRQ_EINT12,
 .max_speed_hz	= 5*1000*1000,
 .chip_select	= 0,
 पूर्ण,
 पूर्ण;

 * The initial minor number is 209 in the low-density serial port:
 * mknod /dev/ttyMAX0 c 204 209
 */

#घोषणा MAX3100_MAJOR 204
#घोषणा MAX3100_MINOR 209
/* 4 MAX3100s should be enough क्रम everyone */
#घोषणा MAX_MAX3100 4

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>

#समावेश <linux/serial_max3100.h>

#घोषणा MAX3100_C    (1<<14)
#घोषणा MAX3100_D    (0<<14)
#घोषणा MAX3100_W    (1<<15)
#घोषणा MAX3100_RX   (0<<15)

#घोषणा MAX3100_WC   (MAX3100_W  | MAX3100_C)
#घोषणा MAX3100_RC   (MAX3100_RX | MAX3100_C)
#घोषणा MAX3100_WD   (MAX3100_W  | MAX3100_D)
#घोषणा MAX3100_RD   (MAX3100_RX | MAX3100_D)
#घोषणा MAX3100_CMD  (3 << 14)

#घोषणा MAX3100_T    (1<<14)
#घोषणा MAX3100_R    (1<<15)

#घोषणा MAX3100_FEN  (1<<13)
#घोषणा MAX3100_SHDN (1<<12)
#घोषणा MAX3100_TM   (1<<11)
#घोषणा MAX3100_RM   (1<<10)
#घोषणा MAX3100_PM   (1<<9)
#घोषणा MAX3100_RAM  (1<<8)
#घोषणा MAX3100_IR   (1<<7)
#घोषणा MAX3100_ST   (1<<6)
#घोषणा MAX3100_PE   (1<<5)
#घोषणा MAX3100_L    (1<<4)
#घोषणा MAX3100_BAUD (0xf)

#घोषणा MAX3100_TE   (1<<10)
#घोषणा MAX3100_RAFE (1<<10)
#घोषणा MAX3100_RTS  (1<<9)
#घोषणा MAX3100_CTS  (1<<9)
#घोषणा MAX3100_PT   (1<<8)
#घोषणा MAX3100_DATA (0xff)

#घोषणा MAX3100_RT   (MAX3100_R | MAX3100_T)
#घोषणा MAX3100_RTC  (MAX3100_RT | MAX3100_CTS | MAX3100_RAFE)

/* the following simulate a status reg क्रम ignore_status_mask */
#घोषणा MAX3100_STATUS_PE 1
#घोषणा MAX3100_STATUS_FE 2
#घोषणा MAX3100_STATUS_OE 4

काष्ठा max3100_port अणु
	काष्ठा uart_port port;
	काष्ठा spi_device *spi;

	पूर्णांक cts;	        /* last CTS received क्रम flow ctrl */
	पूर्णांक tx_empty;		/* last TX empty bit */

	spinlock_t conf_lock;	/* shared data */
	पूर्णांक conf_commit;	/* need to make changes */
	पूर्णांक conf;		/* configuration क्रम the MAX31000
				 * (bits 0-7, bits 8-11 are irqs) */
	पूर्णांक rts_commit;	        /* need to change rts */
	पूर्णांक rts;		/* rts status */
	पूर्णांक baud;		/* current baud rate */

	पूर्णांक parity;		/* keeps track अगर we should send parity */
#घोषणा MAX3100_PARITY_ON 1
#घोषणा MAX3100_PARITY_ODD 2
#घोषणा MAX3100_7BIT 4
	पूर्णांक rx_enabled;	        /* अगर we should rx अक्षरs */

	पूर्णांक irq;		/* irq asचिन्हित to the max3100 */

	पूर्णांक minor;		/* minor number */
	पूर्णांक crystal;		/* 1 अगर 3.6864Mhz crystal 0 क्रम 1.8432 */
	पूर्णांक loopback;		/* 1 अगर we are in loopback mode */

	/* क्रम handling irqs: need workqueue since we करो spi_sync */
	काष्ठा workqueue_काष्ठा *workqueue;
	काष्ठा work_काष्ठा work;
	/* set to 1 to make the workhandler निकास as soon as possible */
	पूर्णांक  क्रमce_end_work;
	/* need to know we are suspending to aव्योम deadlock on workqueue */
	पूर्णांक suspending;

	/* hook क्रम suspending MAX3100 via dedicated pin */
	व्योम (*max3100_hw_suspend) (पूर्णांक suspend);

	/* poll समय (in ms) क्रम ctrl lines */
	पूर्णांक poll_समय;
	/* and its समयr */
	काष्ठा समयr_list	समयr;
पूर्ण;

अटल काष्ठा max3100_port *max3100s[MAX_MAX3100]; /* the chips */
अटल DEFINE_MUTEX(max3100s_lock);		   /* race on probe */

अटल पूर्णांक max3100_करो_parity(काष्ठा max3100_port *s, u16 c)
अणु
	पूर्णांक parity;

	अगर (s->parity & MAX3100_PARITY_ODD)
		parity = 1;
	अन्यथा
		parity = 0;

	अगर (s->parity & MAX3100_7BIT)
		c &= 0x7f;
	अन्यथा
		c &= 0xff;

	parity = parity ^ (hweight8(c) & 1);
	वापस parity;
पूर्ण

अटल पूर्णांक max3100_check_parity(काष्ठा max3100_port *s, u16 c)
अणु
	वापस max3100_करो_parity(s, c) == ((c >> 8) & 1);
पूर्ण

अटल व्योम max3100_calc_parity(काष्ठा max3100_port *s, u16 *c)
अणु
	अगर (s->parity & MAX3100_7BIT)
		*c &= 0x7f;
	अन्यथा
		*c &= 0xff;

	अगर (s->parity & MAX3100_PARITY_ON)
		*c |= max3100_करो_parity(s, *c) << 8;
पूर्ण

अटल व्योम max3100_work(काष्ठा work_काष्ठा *w);

अटल व्योम max3100_करोwork(काष्ठा max3100_port *s)
अणु
	अगर (!s->क्रमce_end_work && !मुक्तzing(current) && !s->suspending)
		queue_work(s->workqueue, &s->work);
पूर्ण

अटल व्योम max3100_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा max3100_port *s = from_समयr(s, t, समयr);

	अगर (s->port.state) अणु
		max3100_करोwork(s);
		mod_समयr(&s->समयr, jअगरfies + s->poll_समय);
	पूर्ण
पूर्ण

अटल पूर्णांक max3100_sr(काष्ठा max3100_port *s, u16 tx, u16 *rx)
अणु
	काष्ठा spi_message message;
	u16 etx, erx;
	पूर्णांक status;
	काष्ठा spi_transfer tran = अणु
		.tx_buf = &etx,
		.rx_buf = &erx,
		.len = 2,
	पूर्ण;

	etx = cpu_to_be16(tx);
	spi_message_init(&message);
	spi_message_add_tail(&tran, &message);
	status = spi_sync(s->spi, &message);
	अगर (status) अणु
		dev_warn(&s->spi->dev, "error while calling spi_sync\n");
		वापस -EIO;
	पूर्ण
	*rx = be16_to_cpu(erx);
	s->tx_empty = (*rx & MAX3100_T) > 0;
	dev_dbg(&s->spi->dev, "%04x - %04x\n", tx, *rx);
	वापस 0;
पूर्ण

अटल पूर्णांक max3100_handlerx(काष्ठा max3100_port *s, u16 rx)
अणु
	अचिन्हित पूर्णांक ch, flg, status = 0;
	पूर्णांक ret = 0, cts;

	अगर (rx & MAX3100_R && s->rx_enabled) अणु
		dev_dbg(&s->spi->dev, "%s\n", __func__);
		ch = rx & (s->parity & MAX3100_7BIT ? 0x7f : 0xff);
		अगर (rx & MAX3100_RAFE) अणु
			s->port.icount.frame++;
			flg = TTY_FRAME;
			status |= MAX3100_STATUS_FE;
		पूर्ण अन्यथा अणु
			अगर (s->parity & MAX3100_PARITY_ON) अणु
				अगर (max3100_check_parity(s, rx)) अणु
					s->port.icount.rx++;
					flg = TTY_NORMAL;
				पूर्ण अन्यथा अणु
					s->port.icount.parity++;
					flg = TTY_PARITY;
					status |= MAX3100_STATUS_PE;
				पूर्ण
			पूर्ण अन्यथा अणु
				s->port.icount.rx++;
				flg = TTY_NORMAL;
			पूर्ण
		पूर्ण
		uart_insert_अक्षर(&s->port, status, MAX3100_STATUS_OE, ch, flg);
		ret = 1;
	पूर्ण

	cts = (rx & MAX3100_CTS) > 0;
	अगर (s->cts != cts) अणु
		s->cts = cts;
		uart_handle_cts_change(&s->port, cts ? TIOCM_CTS : 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम max3100_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा max3100_port *s = container_of(w, काष्ठा max3100_port, work);
	पूर्णांक rxअक्षरs;
	u16 tx, rx;
	पूर्णांक conf, cconf, crts;
	काष्ठा circ_buf *xmit = &s->port.state->xmit;

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	rxअक्षरs = 0;
	करो अणु
		spin_lock(&s->conf_lock);
		conf = s->conf;
		cconf = s->conf_commit;
		s->conf_commit = 0;
		crts = s->rts_commit;
		s->rts_commit = 0;
		spin_unlock(&s->conf_lock);
		अगर (cconf)
			max3100_sr(s, MAX3100_WC | conf, &rx);
		अगर (crts) अणु
			max3100_sr(s, MAX3100_WD | MAX3100_TE |
				   (s->rts ? MAX3100_RTS : 0), &rx);
			rxअक्षरs += max3100_handlerx(s, rx);
		पूर्ण

		max3100_sr(s, MAX3100_RD, &rx);
		rxअक्षरs += max3100_handlerx(s, rx);

		अगर (rx & MAX3100_T) अणु
			tx = 0xffff;
			अगर (s->port.x_अक्षर) अणु
				tx = s->port.x_अक्षर;
				s->port.icount.tx++;
				s->port.x_अक्षर = 0;
			पूर्ण अन्यथा अगर (!uart_circ_empty(xmit) &&
				   !uart_tx_stopped(&s->port)) अणु
				tx = xmit->buf[xmit->tail];
				xmit->tail = (xmit->tail + 1) &
					(UART_XMIT_SIZE - 1);
				s->port.icount.tx++;
			पूर्ण
			अगर (tx != 0xffff) अणु
				max3100_calc_parity(s, &tx);
				tx |= MAX3100_WD | (s->rts ? MAX3100_RTS : 0);
				max3100_sr(s, tx, &rx);
				rxअक्षरs += max3100_handlerx(s, rx);
			पूर्ण
		पूर्ण

		अगर (rxअक्षरs > 16) अणु
			tty_flip_buffer_push(&s->port.state->port);
			rxअक्षरs = 0;
		पूर्ण
		अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
			uart_ग_लिखो_wakeup(&s->port);

	पूर्ण जबतक (!s->क्रमce_end_work &&
		 !मुक्तzing(current) &&
		 ((rx & MAX3100_R) ||
		  (!uart_circ_empty(xmit) &&
		   !uart_tx_stopped(&s->port))));

	अगर (rxअक्षरs > 0)
		tty_flip_buffer_push(&s->port.state->port);
पूर्ण

अटल irqवापस_t max3100_irq(पूर्णांक irqno, व्योम *dev_id)
अणु
	काष्ठा max3100_port *s = dev_id;

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	max3100_करोwork(s);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम max3100_enable_ms(काष्ठा uart_port *port)
अणु
	काष्ठा max3100_port *s = container_of(port,
					      काष्ठा max3100_port,
					      port);

	अगर (s->poll_समय > 0)
		mod_समयr(&s->समयr, jअगरfies);
	dev_dbg(&s->spi->dev, "%s\n", __func__);
पूर्ण

अटल व्योम max3100_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा max3100_port *s = container_of(port,
					      काष्ठा max3100_port,
					      port);

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	max3100_करोwork(s);
पूर्ण

अटल व्योम max3100_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा max3100_port *s = container_of(port,
					      काष्ठा max3100_port,
					      port);

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	s->rx_enabled = 0;
	spin_lock(&s->conf_lock);
	s->conf &= ~MAX3100_RM;
	s->conf_commit = 1;
	spin_unlock(&s->conf_lock);
	max3100_करोwork(s);
पूर्ण

अटल अचिन्हित पूर्णांक max3100_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा max3100_port *s = container_of(port,
					      काष्ठा max3100_port,
					      port);

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	/* may not be truly up-to-date */
	max3100_करोwork(s);
	वापस s->tx_empty;
पूर्ण

अटल अचिन्हित पूर्णांक max3100_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा max3100_port *s = container_of(port,
					      काष्ठा max3100_port,
					      port);

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	/* may not be truly up-to-date */
	max3100_करोwork(s);
	/* always निश्चित DCD and DSR since these lines are not wired */
	वापस (s->cts ? TIOCM_CTS : 0) | TIOCM_DSR | TIOCM_CAR;
पूर्ण

अटल व्योम max3100_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा max3100_port *s = container_of(port,
					      काष्ठा max3100_port,
					      port);
	पूर्णांक rts;

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	rts = (mctrl & TIOCM_RTS) > 0;

	spin_lock(&s->conf_lock);
	अगर (s->rts != rts) अणु
		s->rts = rts;
		s->rts_commit = 1;
		max3100_करोwork(s);
	पूर्ण
	spin_unlock(&s->conf_lock);
पूर्ण

अटल व्योम
max3100_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
		    काष्ठा ktermios *old)
अणु
	काष्ठा max3100_port *s = container_of(port,
					      काष्ठा max3100_port,
					      port);
	पूर्णांक baud = 0;
	अचिन्हित cflag;
	u32 param_new, param_mask, parity = 0;

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	cflag = termios->c_cflag;
	param_mask = 0;

	baud = tty_termios_baud_rate(termios);
	param_new = s->conf & MAX3100_BAUD;
	चयन (baud) अणु
	हाल 300:
		अगर (s->crystal)
			baud = s->baud;
		अन्यथा
			param_new = 15;
		अवरोध;
	हाल 600:
		param_new = 14 + s->crystal;
		अवरोध;
	हाल 1200:
		param_new = 13 + s->crystal;
		अवरोध;
	हाल 2400:
		param_new = 12 + s->crystal;
		अवरोध;
	हाल 4800:
		param_new = 11 + s->crystal;
		अवरोध;
	हाल 9600:
		param_new = 10 + s->crystal;
		अवरोध;
	हाल 19200:
		param_new = 9 + s->crystal;
		अवरोध;
	हाल 38400:
		param_new = 8 + s->crystal;
		अवरोध;
	हाल 57600:
		param_new = 1 + s->crystal;
		अवरोध;
	हाल 115200:
		param_new = 0 + s->crystal;
		अवरोध;
	हाल 230400:
		अगर (s->crystal)
			param_new = 0;
		अन्यथा
			baud = s->baud;
		अवरोध;
	शेष:
		baud = s->baud;
	पूर्ण
	tty_termios_encode_baud_rate(termios, baud, baud);
	s->baud = baud;
	param_mask |= MAX3100_BAUD;

	अगर ((cflag & CSIZE) == CS8) अणु
		param_new &= ~MAX3100_L;
		parity &= ~MAX3100_7BIT;
	पूर्ण अन्यथा अणु
		param_new |= MAX3100_L;
		parity |= MAX3100_7BIT;
		cflag = (cflag & ~CSIZE) | CS7;
	पूर्ण
	param_mask |= MAX3100_L;

	अगर (cflag & CSTOPB)
		param_new |= MAX3100_ST;
	अन्यथा
		param_new &= ~MAX3100_ST;
	param_mask |= MAX3100_ST;

	अगर (cflag & PARENB) अणु
		param_new |= MAX3100_PE;
		parity |= MAX3100_PARITY_ON;
	पूर्ण अन्यथा अणु
		param_new &= ~MAX3100_PE;
		parity &= ~MAX3100_PARITY_ON;
	पूर्ण
	param_mask |= MAX3100_PE;

	अगर (cflag & PARODD)
		parity |= MAX3100_PARITY_ODD;
	अन्यथा
		parity &= ~MAX3100_PARITY_ODD;

	/* mask termios capabilities we करोn't support */
	cflag &= ~CMSPAR;
	termios->c_cflag = cflag;

	s->port.ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		s->port.ignore_status_mask |=
			MAX3100_STATUS_PE | MAX3100_STATUS_FE |
			MAX3100_STATUS_OE;

	अगर (s->poll_समय > 0)
		del_समयr_sync(&s->समयr);

	uart_update_समयout(port, termios->c_cflag, baud);

	spin_lock(&s->conf_lock);
	s->conf = (s->conf & ~param_mask) | (param_new & param_mask);
	s->conf_commit = 1;
	s->parity = parity;
	spin_unlock(&s->conf_lock);
	max3100_करोwork(s);

	अगर (UART_ENABLE_MS(&s->port, termios->c_cflag))
		max3100_enable_ms(&s->port);
पूर्ण

अटल व्योम max3100_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा max3100_port *s = container_of(port,
					      काष्ठा max3100_port,
					      port);

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	अगर (s->suspending)
		वापस;

	s->क्रमce_end_work = 1;

	अगर (s->poll_समय > 0)
		del_समयr_sync(&s->समयr);

	अगर (s->workqueue) अणु
		flush_workqueue(s->workqueue);
		destroy_workqueue(s->workqueue);
		s->workqueue = शून्य;
	पूर्ण
	अगर (s->irq)
		मुक्त_irq(s->irq, s);

	/* set shutकरोwn mode to save घातer */
	अगर (s->max3100_hw_suspend)
		s->max3100_hw_suspend(1);
	अन्यथा  अणु
		u16 tx, rx;

		tx = MAX3100_WC | MAX3100_SHDN;
		max3100_sr(s, tx, &rx);
	पूर्ण
पूर्ण

अटल पूर्णांक max3100_startup(काष्ठा uart_port *port)
अणु
	काष्ठा max3100_port *s = container_of(port,
					      काष्ठा max3100_port,
					      port);
	अक्षर b[12];

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	s->conf = MAX3100_RM;
	s->baud = s->crystal ? 230400 : 115200;
	s->rx_enabled = 1;

	अगर (s->suspending)
		वापस 0;

	s->क्रमce_end_work = 0;
	s->parity = 0;
	s->rts = 0;

	प्र_लिखो(b, "max3100-%d", s->minor);
	s->workqueue = create_मुक्तzable_workqueue(b);
	अगर (!s->workqueue) अणु
		dev_warn(&s->spi->dev, "cannot create workqueue\n");
		वापस -EBUSY;
	पूर्ण
	INIT_WORK(&s->work, max3100_work);

	अगर (request_irq(s->irq, max3100_irq,
			IRQF_TRIGGER_FALLING, "max3100", s) < 0) अणु
		dev_warn(&s->spi->dev, "cannot allocate irq %d\n", s->irq);
		s->irq = 0;
		destroy_workqueue(s->workqueue);
		s->workqueue = शून्य;
		वापस -EBUSY;
	पूर्ण

	अगर (s->loopback) अणु
		u16 tx, rx;
		tx = 0x4001;
		max3100_sr(s, tx, &rx);
	पूर्ण

	अगर (s->max3100_hw_suspend)
		s->max3100_hw_suspend(0);
	s->conf_commit = 1;
	max3100_करोwork(s);
	/* रुको क्रम घड़ी to settle */
	msleep(50);

	max3100_enable_ms(&s->port);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *max3100_type(काष्ठा uart_port *port)
अणु
	काष्ठा max3100_port *s = container_of(port,
					      काष्ठा max3100_port,
					      port);

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	वापस s->port.type == PORT_MAX3100 ? "MAX3100" : शून्य;
पूर्ण

अटल व्योम max3100_release_port(काष्ठा uart_port *port)
अणु
	काष्ठा max3100_port *s = container_of(port,
					      काष्ठा max3100_port,
					      port);

	dev_dbg(&s->spi->dev, "%s\n", __func__);
पूर्ण

अटल व्योम max3100_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	काष्ठा max3100_port *s = container_of(port,
					      काष्ठा max3100_port,
					      port);

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	अगर (flags & UART_CONFIG_TYPE)
		s->port.type = PORT_MAX3100;
पूर्ण

अटल पूर्णांक max3100_verअगरy_port(काष्ठा uart_port *port,
			       काष्ठा serial_काष्ठा *ser)
अणु
	काष्ठा max3100_port *s = container_of(port,
					      काष्ठा max3100_port,
					      port);
	पूर्णांक ret = -EINVAL;

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	अगर (ser->type == PORT_UNKNOWN || ser->type == PORT_MAX3100)
		ret = 0;
	वापस ret;
पूर्ण

अटल व्योम max3100_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा max3100_port *s = container_of(port,
					      काष्ठा max3100_port,
					      port);

	dev_dbg(&s->spi->dev, "%s\n", __func__);
पूर्ण

अटल पूर्णांक max3100_request_port(काष्ठा uart_port *port)
अणु
	काष्ठा max3100_port *s = container_of(port,
					      काष्ठा max3100_port,
					      port);

	dev_dbg(&s->spi->dev, "%s\n", __func__);
	वापस 0;
पूर्ण

अटल व्योम max3100_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	काष्ठा max3100_port *s = container_of(port,
					      काष्ठा max3100_port,
					      port);

	dev_dbg(&s->spi->dev, "%s\n", __func__);
पूर्ण

अटल स्थिर काष्ठा uart_ops max3100_ops = अणु
	.tx_empty	= max3100_tx_empty,
	.set_mctrl	= max3100_set_mctrl,
	.get_mctrl	= max3100_get_mctrl,
	.stop_tx        = max3100_stop_tx,
	.start_tx	= max3100_start_tx,
	.stop_rx	= max3100_stop_rx,
	.enable_ms      = max3100_enable_ms,
	.अवरोध_ctl      = max3100_अवरोध_ctl,
	.startup	= max3100_startup,
	.shutकरोwn	= max3100_shutकरोwn,
	.set_termios	= max3100_set_termios,
	.type		= max3100_type,
	.release_port   = max3100_release_port,
	.request_port   = max3100_request_port,
	.config_port	= max3100_config_port,
	.verअगरy_port	= max3100_verअगरy_port,
पूर्ण;

अटल काष्ठा uart_driver max3100_uart_driver = अणु
	.owner          = THIS_MODULE,
	.driver_name    = "ttyMAX",
	.dev_name       = "ttyMAX",
	.major          = MAX3100_MAJOR,
	.minor          = MAX3100_MINOR,
	.nr             = MAX_MAX3100,
पूर्ण;
अटल पूर्णांक uart_driver_रेजिस्टरed;

अटल पूर्णांक max3100_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक i, retval;
	काष्ठा plat_max3100 *pdata;
	u16 tx, rx;

	mutex_lock(&max3100s_lock);

	अगर (!uart_driver_रेजिस्टरed) अणु
		uart_driver_रेजिस्टरed = 1;
		retval = uart_रेजिस्टर_driver(&max3100_uart_driver);
		अगर (retval) अणु
			prपूर्णांकk(KERN_ERR "Couldn't register max3100 uart driver\n");
			mutex_unlock(&max3100s_lock);
			वापस retval;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MAX_MAX3100; i++)
		अगर (!max3100s[i])
			अवरोध;
	अगर (i == MAX_MAX3100) अणु
		dev_warn(&spi->dev, "too many MAX3100 chips\n");
		mutex_unlock(&max3100s_lock);
		वापस -ENOMEM;
	पूर्ण

	max3100s[i] = kzalloc(माप(काष्ठा max3100_port), GFP_KERNEL);
	अगर (!max3100s[i]) अणु
		dev_warn(&spi->dev,
			 "kmalloc for max3100 structure %d failed!\n", i);
		mutex_unlock(&max3100s_lock);
		वापस -ENOMEM;
	पूर्ण
	max3100s[i]->spi = spi;
	max3100s[i]->irq = spi->irq;
	spin_lock_init(&max3100s[i]->conf_lock);
	spi_set_drvdata(spi, max3100s[i]);
	pdata = dev_get_platdata(&spi->dev);
	max3100s[i]->crystal = pdata->crystal;
	max3100s[i]->loopback = pdata->loopback;
	max3100s[i]->poll_समय = msecs_to_jअगरfies(pdata->poll_समय);
	अगर (pdata->poll_समय > 0 && max3100s[i]->poll_समय == 0)
		max3100s[i]->poll_समय = 1;
	max3100s[i]->max3100_hw_suspend = pdata->max3100_hw_suspend;
	max3100s[i]->minor = i;
	समयr_setup(&max3100s[i]->समयr, max3100_समयout, 0);

	dev_dbg(&spi->dev, "%s: adding port %d\n", __func__, i);
	max3100s[i]->port.irq = max3100s[i]->irq;
	max3100s[i]->port.uartclk = max3100s[i]->crystal ? 3686400 : 1843200;
	max3100s[i]->port.fअगरosize = 16;
	max3100s[i]->port.ops = &max3100_ops;
	max3100s[i]->port.flags = UPF_SKIP_TEST | UPF_BOOT_AUTOCONF;
	max3100s[i]->port.line = i;
	max3100s[i]->port.type = PORT_MAX3100;
	max3100s[i]->port.dev = &spi->dev;
	retval = uart_add_one_port(&max3100_uart_driver, &max3100s[i]->port);
	अगर (retval < 0)
		dev_warn(&spi->dev,
			 "uart_add_one_port failed for line %d with error %d\n",
			 i, retval);

	/* set shutकरोwn mode to save घातer. Will be woken-up on खोलो */
	अगर (max3100s[i]->max3100_hw_suspend)
		max3100s[i]->max3100_hw_suspend(1);
	अन्यथा अणु
		tx = MAX3100_WC | MAX3100_SHDN;
		max3100_sr(max3100s[i], tx, &rx);
	पूर्ण
	mutex_unlock(&max3100s_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक max3100_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा max3100_port *s = spi_get_drvdata(spi);
	पूर्णांक i;

	mutex_lock(&max3100s_lock);

	/* find out the index क्रम the chip we are removing */
	क्रम (i = 0; i < MAX_MAX3100; i++)
		अगर (max3100s[i] == s) अणु
			dev_dbg(&spi->dev, "%s: removing port %d\n", __func__, i);
			uart_हटाओ_one_port(&max3100_uart_driver, &max3100s[i]->port);
			kमुक्त(max3100s[i]);
			max3100s[i] = शून्य;
			अवरोध;
		पूर्ण

	WARN_ON(i == MAX_MAX3100);
	
	/* check अगर this is the last chip we have */
	क्रम (i = 0; i < MAX_MAX3100; i++)
		अगर (max3100s[i]) अणु
			mutex_unlock(&max3100s_lock);
			वापस 0;
		पूर्ण
	pr_debug("removing max3100 driver\n");
	uart_unरेजिस्टर_driver(&max3100_uart_driver);

	mutex_unlock(&max3100s_lock);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक max3100_suspend(काष्ठा device *dev)
अणु
	काष्ठा max3100_port *s = dev_get_drvdata(dev);

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	disable_irq(s->irq);

	s->suspending = 1;
	uart_suspend_port(&max3100_uart_driver, &s->port);

	अगर (s->max3100_hw_suspend)
		s->max3100_hw_suspend(1);
	अन्यथा अणु
		/* no HW suspend, so करो SW one */
		u16 tx, rx;

		tx = MAX3100_WC | MAX3100_SHDN;
		max3100_sr(s, tx, &rx);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक max3100_resume(काष्ठा device *dev)
अणु
	काष्ठा max3100_port *s = dev_get_drvdata(dev);

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	अगर (s->max3100_hw_suspend)
		s->max3100_hw_suspend(0);
	uart_resume_port(&max3100_uart_driver, &s->port);
	s->suspending = 0;

	enable_irq(s->irq);

	s->conf_commit = 1;
	अगर (s->workqueue)
		max3100_करोwork(s);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(max3100_pm_ops, max3100_suspend, max3100_resume);
#घोषणा MAX3100_PM_OPS (&max3100_pm_ops)

#अन्यथा
#घोषणा MAX3100_PM_OPS शून्य
#पूर्ण_अगर

अटल काष्ठा spi_driver max3100_driver = अणु
	.driver = अणु
		.name		= "max3100",
		.pm		= MAX3100_PM_OPS,
	पूर्ण,
	.probe		= max3100_probe,
	.हटाओ		= max3100_हटाओ,
पूर्ण;

module_spi_driver(max3100_driver);

MODULE_DESCRIPTION("MAX3100 driver");
MODULE_AUTHOR("Christian Pellegrin <chripell@evolware.org>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:max3100");
