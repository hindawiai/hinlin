<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale LINFlexD UART serial port driver
 *
 * Copyright 2012-2016 Freescale Semiconductor, Inc.
 * Copyright 2017-2019 NXP
 */

#समावेश <linux/console.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/delay.h>

/* All रेजिस्टरs are 32-bit width */

#घोषणा LINCR1	0x0000	/* LIN control रेजिस्टर				*/
#घोषणा LINIER	0x0004	/* LIN पूर्णांकerrupt enable रेजिस्टर		*/
#घोषणा LINSR	0x0008	/* LIN status रेजिस्टर				*/
#घोषणा LINESR	0x000C	/* LIN error status रेजिस्टर			*/
#घोषणा UARTCR	0x0010	/* UART mode control रेजिस्टर			*/
#घोषणा UARTSR	0x0014	/* UART mode status रेजिस्टर			*/
#घोषणा LINTCSR	0x0018	/* LIN समयout control status रेजिस्टर		*/
#घोषणा LINOCR	0x001C	/* LIN output compare रेजिस्टर			*/
#घोषणा LINTOCR	0x0020	/* LIN समयout control रेजिस्टर			*/
#घोषणा LINFBRR	0x0024	/* LIN fractional baud rate रेजिस्टर		*/
#घोषणा LINIBRR	0x0028	/* LIN पूर्णांकeger baud rate रेजिस्टर		*/
#घोषणा LINCFR	0x002C	/* LIN checksum field रेजिस्टर			*/
#घोषणा LINCR2	0x0030	/* LIN control रेजिस्टर 2			*/
#घोषणा BIDR	0x0034	/* Buffer identअगरier रेजिस्टर			*/
#घोषणा BDRL	0x0038	/* Buffer data रेजिस्टर least signअगरicant	*/
#घोषणा BDRM	0x003C	/* Buffer data रेजिस्टर most signअगरicant	*/
#घोषणा IFER	0x0040	/* Identअगरier filter enable रेजिस्टर		*/
#घोषणा IFMI	0x0044	/* Identअगरier filter match index		*/
#घोषणा IFMR	0x0048	/* Identअगरier filter mode रेजिस्टर		*/
#घोषणा GCR	0x004C	/* Global control रेजिस्टर			*/
#घोषणा UARTPTO	0x0050	/* UART preset समयout रेजिस्टर			*/
#घोषणा UARTCTO	0x0054	/* UART current समयout रेजिस्टर		*/

/*
 * Register field definitions
 */

#घोषणा LINFLEXD_LINCR1_INIT		BIT(0)
#घोषणा LINFLEXD_LINCR1_MME		BIT(4)
#घोषणा LINFLEXD_LINCR1_BF		BIT(7)

#घोषणा LINFLEXD_LINSR_LINS_INITMODE	BIT(12)
#घोषणा LINFLEXD_LINSR_LINS_MASK	(0xF << 12)

#घोषणा LINFLEXD_LINIER_SZIE		BIT(15)
#घोषणा LINFLEXD_LINIER_OCIE		BIT(14)
#घोषणा LINFLEXD_LINIER_BEIE		BIT(13)
#घोषणा LINFLEXD_LINIER_CEIE		BIT(12)
#घोषणा LINFLEXD_LINIER_HEIE		BIT(11)
#घोषणा LINFLEXD_LINIER_FEIE		BIT(8)
#घोषणा LINFLEXD_LINIER_BOIE		BIT(7)
#घोषणा LINFLEXD_LINIER_LSIE		BIT(6)
#घोषणा LINFLEXD_LINIER_WUIE		BIT(5)
#घोषणा LINFLEXD_LINIER_DBFIE		BIT(4)
#घोषणा LINFLEXD_LINIER_DBEIETOIE	BIT(3)
#घोषणा LINFLEXD_LINIER_DRIE		BIT(2)
#घोषणा LINFLEXD_LINIER_DTIE		BIT(1)
#घोषणा LINFLEXD_LINIER_HRIE		BIT(0)

#घोषणा LINFLEXD_UARTCR_OSR_MASK	(0xF << 24)
#घोषणा LINFLEXD_UARTCR_OSR(uartcr)	(((uartcr) \
					& LINFLEXD_UARTCR_OSR_MASK) >> 24)

#घोषणा LINFLEXD_UARTCR_ROSE		BIT(23)

#घोषणा LINFLEXD_UARTCR_RFBM		BIT(9)
#घोषणा LINFLEXD_UARTCR_TFBM		BIT(8)
#घोषणा LINFLEXD_UARTCR_WL1		BIT(7)
#घोषणा LINFLEXD_UARTCR_PC1		BIT(6)

#घोषणा LINFLEXD_UARTCR_RXEN		BIT(5)
#घोषणा LINFLEXD_UARTCR_TXEN		BIT(4)
#घोषणा LINFLEXD_UARTCR_PC0		BIT(3)

#घोषणा LINFLEXD_UARTCR_PCE		BIT(2)
#घोषणा LINFLEXD_UARTCR_WL0		BIT(1)
#घोषणा LINFLEXD_UARTCR_UART		BIT(0)

#घोषणा LINFLEXD_UARTSR_SZF		BIT(15)
#घोषणा LINFLEXD_UARTSR_OCF		BIT(14)
#घोषणा LINFLEXD_UARTSR_PE3		BIT(13)
#घोषणा LINFLEXD_UARTSR_PE2		BIT(12)
#घोषणा LINFLEXD_UARTSR_PE1		BIT(11)
#घोषणा LINFLEXD_UARTSR_PE0		BIT(10)
#घोषणा LINFLEXD_UARTSR_RMB		BIT(9)
#घोषणा LINFLEXD_UARTSR_FEF		BIT(8)
#घोषणा LINFLEXD_UARTSR_BOF		BIT(7)
#घोषणा LINFLEXD_UARTSR_RPS		BIT(6)
#घोषणा LINFLEXD_UARTSR_WUF		BIT(5)
#घोषणा LINFLEXD_UARTSR_4		BIT(4)

#घोषणा LINFLEXD_UARTSR_TO		BIT(3)

#घोषणा LINFLEXD_UARTSR_DRFRFE		BIT(2)
#घोषणा LINFLEXD_UARTSR_DTFTFF		BIT(1)
#घोषणा LINFLEXD_UARTSR_NF		BIT(0)
#घोषणा LINFLEXD_UARTSR_PE		(LINFLEXD_UARTSR_PE0 |\
					 LINFLEXD_UARTSR_PE1 |\
					 LINFLEXD_UARTSR_PE2 |\
					 LINFLEXD_UARTSR_PE3)

#घोषणा LINFLEX_LDIV_MULTIPLIER		(16)

#घोषणा DRIVER_NAME	"fsl-linflexuart"
#घोषणा DEV_NAME	"ttyLF"
#घोषणा UART_NR		4

#घोषणा EARLYCON_BUFFER_INITIAL_CAP	8

#घोषणा PREINIT_DELAY			2000 /* us */

अटल स्थिर काष्ठा of_device_id linflex_dt_ids[] = अणु
	अणु
		.compatible = "fsl,s32v234-linflexuart",
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, linflex_dt_ids);

#अगर_घोषित CONFIG_SERIAL_FSL_LINFLEXUART_CONSOLE
अटल काष्ठा uart_port *earlycon_port;
अटल bool linflex_earlycon_same_instance;
अटल DEFINE_SPINLOCK(init_lock);
अटल bool during_init;

अटल काष्ठा अणु
	अक्षर *content;
	अचिन्हित पूर्णांक len, cap;
पूर्ण earlycon_buf;
#पूर्ण_अगर

अटल व्योम linflex_stop_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ ier;

	ier = पढ़ोl(port->membase + LINIER);
	ier &= ~(LINFLEXD_LINIER_DTIE);
	ग_लिखोl(ier, port->membase + LINIER);
पूर्ण

अटल व्योम linflex_stop_rx(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ ier;

	ier = पढ़ोl(port->membase + LINIER);
	ग_लिखोl(ier & ~LINFLEXD_LINIER_DRIE, port->membase + LINIER);
पूर्ण

अटल अंतरभूत व्योम linflex_transmit_buffer(काष्ठा uart_port *sport)
अणु
	काष्ठा circ_buf *xmit = &sport->state->xmit;
	अचिन्हित अक्षर c;
	अचिन्हित दीर्घ status;

	जबतक (!uart_circ_empty(xmit)) अणु
		c = xmit->buf[xmit->tail];
		ग_लिखोb(c, sport->membase + BDRL);

		/* Waiting क्रम data transmission completed. */
		जबतक (((status = पढ़ोl(sport->membase + UARTSR)) &
					LINFLEXD_UARTSR_DTFTFF) !=
					LINFLEXD_UARTSR_DTFTFF)
			;

		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		sport->icount.tx++;

		ग_लिखोl(status | LINFLEXD_UARTSR_DTFTFF,
		       sport->membase + UARTSR);
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(sport);

	अगर (uart_circ_empty(xmit))
		linflex_stop_tx(sport);
पूर्ण

अटल व्योम linflex_start_tx(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ ier;

	linflex_transmit_buffer(port);
	ier = पढ़ोl(port->membase + LINIER);
	ग_लिखोl(ier | LINFLEXD_LINIER_DTIE, port->membase + LINIER);
पूर्ण

अटल irqवापस_t linflex_txपूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *sport = dev_id;
	काष्ठा circ_buf *xmit = &sport->state->xmit;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ status;

	spin_lock_irqsave(&sport->lock, flags);

	अगर (sport->x_अक्षर) अणु
		ग_लिखोb(sport->x_अक्षर, sport->membase + BDRL);

		/* रुकोing क्रम data transmission completed */
		जबतक (((status = पढ़ोl(sport->membase + UARTSR)) &
			LINFLEXD_UARTSR_DTFTFF) != LINFLEXD_UARTSR_DTFTFF)
			;

		ग_लिखोl(status | LINFLEXD_UARTSR_DTFTFF,
		       sport->membase + UARTSR);

		जाओ out;
	पूर्ण

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(sport)) अणु
		linflex_stop_tx(sport);
		जाओ out;
	पूर्ण

	linflex_transmit_buffer(sport);

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(sport);

out:
	spin_unlock_irqrestore(&sport->lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t linflex_rxपूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *sport = dev_id;
	अचिन्हित पूर्णांक flg;
	काष्ठा tty_port *port = &sport->state->port;
	अचिन्हित दीर्घ flags, status;
	अचिन्हित अक्षर rx;
	bool brk;

	spin_lock_irqsave(&sport->lock, flags);

	status = पढ़ोl(sport->membase + UARTSR);
	जबतक (status & LINFLEXD_UARTSR_RMB) अणु
		rx = पढ़ोb(sport->membase + BDRM);
		brk = false;
		flg = TTY_NORMAL;
		sport->icount.rx++;

		अगर (status & (LINFLEXD_UARTSR_BOF | LINFLEXD_UARTSR_FEF |
				LINFLEXD_UARTSR_PE)) अणु
			अगर (status & LINFLEXD_UARTSR_BOF)
				sport->icount.overrun++;
			अगर (status & LINFLEXD_UARTSR_FEF) अणु
				अगर (!rx) अणु
					brk = true;
					sport->icount.brk++;
				पूर्ण अन्यथा
					sport->icount.frame++;
			पूर्ण
			अगर (status & LINFLEXD_UARTSR_PE)
				sport->icount.parity++;
		पूर्ण

		ग_लिखोl(status, sport->membase + UARTSR);
		status = पढ़ोl(sport->membase + UARTSR);

		अगर (brk) अणु
			uart_handle_अवरोध(sport);
		पूर्ण अन्यथा अणु
			अगर (uart_handle_sysrq_अक्षर(sport, (अचिन्हित अक्षर)rx))
				जारी;
			tty_insert_flip_अक्षर(port, rx, flg);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&sport->lock, flags);

	tty_flip_buffer_push(port);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t linflex_पूर्णांक(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uart_port *sport = dev_id;
	अचिन्हित दीर्घ status;

	status = पढ़ोl(sport->membase + UARTSR);

	अगर (status & LINFLEXD_UARTSR_DRFRFE)
		linflex_rxपूर्णांक(irq, dev_id);
	अगर (status & LINFLEXD_UARTSR_DTFTFF)
		linflex_txपूर्णांक(irq, dev_id);

	वापस IRQ_HANDLED;
पूर्ण

/* वापस TIOCSER_TEMT when transmitter is not busy */
अटल अचिन्हित पूर्णांक linflex_tx_empty(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ status;

	status = पढ़ोl(port->membase + UARTSR) & LINFLEXD_UARTSR_DTFTFF;

	वापस status ? TIOCSER_TEMT : 0;
पूर्ण

अटल अचिन्हित पूर्णांक linflex_get_mctrl(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम linflex_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
पूर्ण

अटल व्योम linflex_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
पूर्ण

अटल व्योम linflex_setup_watermark(काष्ठा uart_port *sport)
अणु
	अचिन्हित दीर्घ cr, ier, cr1;

	/* Disable transmission/reception */
	ier = पढ़ोl(sport->membase + LINIER);
	ier &= ~(LINFLEXD_LINIER_DRIE | LINFLEXD_LINIER_DTIE);
	ग_लिखोl(ier, sport->membase + LINIER);

	cr = पढ़ोl(sport->membase + UARTCR);
	cr &= ~(LINFLEXD_UARTCR_RXEN | LINFLEXD_UARTCR_TXEN);
	ग_लिखोl(cr, sport->membase + UARTCR);

	/* Enter initialization mode by setting INIT bit */

	/* set the Linflex in master mode and activate by-pass filter */
	cr1 = LINFLEXD_LINCR1_BF | LINFLEXD_LINCR1_MME
	      | LINFLEXD_LINCR1_INIT;
	ग_लिखोl(cr1, sport->membase + LINCR1);

	/* रुको क्रम init mode entry */
	जबतक ((पढ़ोl(sport->membase + LINSR)
		& LINFLEXD_LINSR_LINS_MASK)
		!= LINFLEXD_LINSR_LINS_INITMODE)
		;

	/*
	 *	UART = 0x1;		- Linflex working in UART mode
	 *	TXEN = 0x1;		- Enable transmission of data now
	 *	RXEn = 0x1;		- Receiver enabled
	 *	WL0 = 0x1;		- 8 bit data
	 *	PCE = 0x0;		- No parity
	 */

	/* set UART bit to allow writing other bits */
	ग_लिखोl(LINFLEXD_UARTCR_UART, sport->membase + UARTCR);

	cr = (LINFLEXD_UARTCR_RXEN | LINFLEXD_UARTCR_TXEN |
	      LINFLEXD_UARTCR_WL0 | LINFLEXD_UARTCR_UART);

	ग_लिखोl(cr, sport->membase + UARTCR);

	cr1 &= ~(LINFLEXD_LINCR1_INIT);

	ग_लिखोl(cr1, sport->membase + LINCR1);

	ier = पढ़ोl(sport->membase + LINIER);
	ier |= LINFLEXD_LINIER_DRIE;
	ier |= LINFLEXD_LINIER_DTIE;

	ग_लिखोl(ier, sport->membase + LINIER);
पूर्ण

अटल पूर्णांक linflex_startup(काष्ठा uart_port *port)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	linflex_setup_watermark(port);

	spin_unlock_irqrestore(&port->lock, flags);

	ret = devm_request_irq(port->dev, port->irq, linflex_पूर्णांक, 0,
			       DRIVER_NAME, port);

	वापस ret;
पूर्ण

अटल व्योम linflex_shutकरोwn(काष्ठा uart_port *port)
अणु
	अचिन्हित दीर्घ ier;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);

	/* disable पूर्णांकerrupts */
	ier = पढ़ोl(port->membase + LINIER);
	ier &= ~(LINFLEXD_LINIER_DRIE | LINFLEXD_LINIER_DTIE);
	ग_लिखोl(ier, port->membase + LINIER);

	spin_unlock_irqrestore(&port->lock, flags);

	devm_मुक्त_irq(port->dev, port->irq, port);
पूर्ण

अटल व्योम
linflex_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
		    काष्ठा ktermios *old)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ cr, old_cr, cr1;
	अचिन्हित पूर्णांक old_csize = old ? old->c_cflag & CSIZE : CS8;

	cr = पढ़ोl(port->membase + UARTCR);
	old_cr = cr;

	/* Enter initialization mode by setting INIT bit */
	cr1 = पढ़ोl(port->membase + LINCR1);
	cr1 |= LINFLEXD_LINCR1_INIT;
	ग_लिखोl(cr1, port->membase + LINCR1);

	/* रुको क्रम init mode entry */
	जबतक ((पढ़ोl(port->membase + LINSR)
		& LINFLEXD_LINSR_LINS_MASK)
		!= LINFLEXD_LINSR_LINS_INITMODE)
		;

	/*
	 * only support CS8 and CS7, and क्रम CS7 must enable PE.
	 * supported mode:
	 *	- (7,e/o,1)
	 *	- (8,n,1)
	 *	- (8,e/o,1)
	 */
	/* enter the UART पूर्णांकo configuration mode */

	जबतक ((termios->c_cflag & CSIZE) != CS8 &&
	       (termios->c_cflag & CSIZE) != CS7) अणु
		termios->c_cflag &= ~CSIZE;
		termios->c_cflag |= old_csize;
		old_csize = CS8;
	पूर्ण

	अगर ((termios->c_cflag & CSIZE) == CS7) अणु
		/* Word length: WL1WL0:00 */
		cr = old_cr & ~LINFLEXD_UARTCR_WL1 & ~LINFLEXD_UARTCR_WL0;
	पूर्ण

	अगर ((termios->c_cflag & CSIZE) == CS8) अणु
		/* Word length: WL1WL0:01 */
		cr = (old_cr | LINFLEXD_UARTCR_WL0) & ~LINFLEXD_UARTCR_WL1;
	पूर्ण

	अगर (termios->c_cflag & CMSPAR) अणु
		अगर ((termios->c_cflag & CSIZE) != CS8) अणु
			termios->c_cflag &= ~CSIZE;
			termios->c_cflag |= CS8;
		पूर्ण
		/* has a space/sticky bit */
		cr |= LINFLEXD_UARTCR_WL0;
	पूर्ण

	अगर (termios->c_cflag & CSTOPB)
		termios->c_cflag &= ~CSTOPB;

	/* parity must be enabled when CS7 to match 8-bits क्रमmat */
	अगर ((termios->c_cflag & CSIZE) == CS7)
		termios->c_cflag |= PARENB;

	अगर ((termios->c_cflag & PARENB)) अणु
		cr |= LINFLEXD_UARTCR_PCE;
		अगर (termios->c_cflag & PARODD)
			cr = (cr | LINFLEXD_UARTCR_PC0) &
			     (~LINFLEXD_UARTCR_PC1);
		अन्यथा
			cr = cr & (~LINFLEXD_UARTCR_PC1 &
				   ~LINFLEXD_UARTCR_PC0);
	पूर्ण अन्यथा अणु
		cr &= ~LINFLEXD_UARTCR_PCE;
	पूर्ण

	spin_lock_irqsave(&port->lock, flags);

	port->पढ़ो_status_mask = 0;

	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |=	(LINFLEXD_UARTSR_FEF |
						 LINFLEXD_UARTSR_PE0 |
						 LINFLEXD_UARTSR_PE1 |
						 LINFLEXD_UARTSR_PE2 |
						 LINFLEXD_UARTSR_PE3);
	अगर (termios->c_अगरlag & (IGNBRK | BRKINT | PARMRK))
		port->पढ़ो_status_mask |= LINFLEXD_UARTSR_FEF;

	/* अक्षरacters to ignore */
	port->ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		port->ignore_status_mask |= LINFLEXD_UARTSR_PE;
	अगर (termios->c_अगरlag & IGNBRK) अणु
		port->ignore_status_mask |= LINFLEXD_UARTSR_PE;
		/*
		 * अगर we're ignoring parity and अवरोध indicators,
		 * ignore overruns too (क्रम real raw support).
		 */
		अगर (termios->c_अगरlag & IGNPAR)
			port->ignore_status_mask |= LINFLEXD_UARTSR_BOF;
	पूर्ण

	ग_लिखोl(cr, port->membase + UARTCR);

	cr1 &= ~(LINFLEXD_LINCR1_INIT);

	ग_लिखोl(cr1, port->membase + LINCR1);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *linflex_type(काष्ठा uart_port *port)
अणु
	वापस "FSL_LINFLEX";
पूर्ण

अटल व्योम linflex_release_port(काष्ठा uart_port *port)
अणु
	/* nothing to करो */
पूर्ण

अटल पूर्णांक linflex_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

/* configure/स्वतः-configure the port */
अटल व्योम linflex_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE)
		port->type = PORT_LINFLEXUART;
पूर्ण

अटल स्थिर काष्ठा uart_ops linflex_pops = अणु
	.tx_empty	= linflex_tx_empty,
	.set_mctrl	= linflex_set_mctrl,
	.get_mctrl	= linflex_get_mctrl,
	.stop_tx	= linflex_stop_tx,
	.start_tx	= linflex_start_tx,
	.stop_rx	= linflex_stop_rx,
	.अवरोध_ctl	= linflex_अवरोध_ctl,
	.startup	= linflex_startup,
	.shutकरोwn	= linflex_shutकरोwn,
	.set_termios	= linflex_set_termios,
	.type		= linflex_type,
	.request_port	= linflex_request_port,
	.release_port	= linflex_release_port,
	.config_port	= linflex_config_port,
पूर्ण;

अटल काष्ठा uart_port *linflex_ports[UART_NR];

#अगर_घोषित CONFIG_SERIAL_FSL_LINFLEXUART_CONSOLE
अटल व्योम linflex_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	अचिन्हित दीर्घ cr;

	cr = पढ़ोl(port->membase + UARTCR);

	ग_लिखोb(ch, port->membase + BDRL);

	अगर (!(cr & LINFLEXD_UARTCR_TFBM))
		जबतक ((पढ़ोl(port->membase + UARTSR) &
					LINFLEXD_UARTSR_DTFTFF)
				!= LINFLEXD_UARTSR_DTFTFF)
			;
	अन्यथा
		जबतक (पढ़ोl(port->membase + UARTSR) &
					LINFLEXD_UARTSR_DTFTFF)
			;

	अगर (!(cr & LINFLEXD_UARTCR_TFBM)) अणु
		ग_लिखोl((पढ़ोl(port->membase + UARTSR) |
					LINFLEXD_UARTSR_DTFTFF),
					port->membase + UARTSR);
	पूर्ण
पूर्ण

अटल व्योम linflex_earlycon_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	अचिन्हित दीर्घ flags;
	अक्षर *ret;

	अगर (!linflex_earlycon_same_instance) अणु
		linflex_console_अक्षर_दो(port, ch);
		वापस;
	पूर्ण

	spin_lock_irqsave(&init_lock, flags);
	अगर (!during_init)
		जाओ outside_init;

	अगर (earlycon_buf.len >= 1 << CONFIG_LOG_BUF_SHIFT)
		जाओ init_release;

	अगर (!earlycon_buf.cap) अणु
		earlycon_buf.content = kदो_स्मृति(EARLYCON_BUFFER_INITIAL_CAP,
					       GFP_ATOMIC);
		earlycon_buf.cap = earlycon_buf.content ?
				   EARLYCON_BUFFER_INITIAL_CAP : 0;
	पूर्ण अन्यथा अगर (earlycon_buf.len == earlycon_buf.cap) अणु
		ret = kपुनः_स्मृति(earlycon_buf.content, earlycon_buf.cap << 1,
			       GFP_ATOMIC);
		अगर (ret) अणु
			earlycon_buf.content = ret;
			earlycon_buf.cap <<= 1;
		पूर्ण
	पूर्ण

	अगर (earlycon_buf.len < earlycon_buf.cap)
		earlycon_buf.content[earlycon_buf.len++] = ch;

	जाओ init_release;

outside_init:
	linflex_console_अक्षर_दो(port, ch);
init_release:
	spin_unlock_irqrestore(&init_lock, flags);
पूर्ण

अटल व्योम linflex_string_ग_लिखो(काष्ठा uart_port *sport, स्थिर अक्षर *s,
				 अचिन्हित पूर्णांक count)
अणु
	अचिन्हित दीर्घ cr, ier = 0;

	ier = पढ़ोl(sport->membase + LINIER);
	linflex_stop_tx(sport);

	cr = पढ़ोl(sport->membase + UARTCR);
	cr |= (LINFLEXD_UARTCR_TXEN);
	ग_लिखोl(cr, sport->membase + UARTCR);

	uart_console_ग_लिखो(sport, s, count, linflex_console_अक्षर_दो);

	ग_लिखोl(ier, sport->membase + LINIER);
पूर्ण

अटल व्योम
linflex_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_port *sport = linflex_ports[co->index];
	अचिन्हित दीर्घ flags;
	पूर्णांक locked = 1;

	अगर (sport->sysrq)
		locked = 0;
	अन्यथा अगर (oops_in_progress)
		locked = spin_trylock_irqsave(&sport->lock, flags);
	अन्यथा
		spin_lock_irqsave(&sport->lock, flags);

	linflex_string_ग_लिखो(sport, s, count);

	अगर (locked)
		spin_unlock_irqrestore(&sport->lock, flags);
पूर्ण

/*
 * अगर the port was alपढ़ोy initialised (eg, by a boot loader),
 * try to determine the current setup.
 */
अटल व्योम __init
linflex_console_get_options(काष्ठा uart_port *sport, पूर्णांक *parity, पूर्णांक *bits)
अणु
	अचिन्हित दीर्घ cr;

	cr = पढ़ोl(sport->membase + UARTCR);
	cr &= LINFLEXD_UARTCR_RXEN | LINFLEXD_UARTCR_TXEN;

	अगर (!cr)
		वापस;

	/* ok, the port was enabled */

	*parity = 'n';
	अगर (cr & LINFLEXD_UARTCR_PCE) अणु
		अगर (cr & LINFLEXD_UARTCR_PC0)
			*parity = 'o';
		अन्यथा
			*parity = 'e';
	पूर्ण

	अगर ((cr & LINFLEXD_UARTCR_WL0) && ((cr & LINFLEXD_UARTCR_WL1) == 0)) अणु
		अगर (cr & LINFLEXD_UARTCR_PCE)
			*bits = 9;
		अन्यथा
			*bits = 8;
	पूर्ण
पूर्ण

अटल पूर्णांक __init linflex_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_port *sport;
	पूर्णांक baud = 115200;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';
	पूर्णांक ret;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	/*
	 * check whether an invalid uart number has been specअगरied, and
	 * अगर so, search क्रम the first available port that करोes have
	 * console support.
	 */
	अगर (co->index == -1 || co->index >= ARRAY_SIZE(linflex_ports))
		co->index = 0;

	sport = linflex_ports[co->index];
	अगर (!sport)
		वापस -ENODEV;

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	अन्यथा
		linflex_console_get_options(sport, &parity, &bits);

	अगर (earlycon_port && sport->mapbase == earlycon_port->mapbase) अणु
		linflex_earlycon_same_instance = true;

		spin_lock_irqsave(&init_lock, flags);
		during_init = true;
		spin_unlock_irqrestore(&init_lock, flags);

		/* Workaround क्रम अक्षरacter loss or output of many invalid
		 * अक्षरacters, when INIT mode is entered लघुly after a
		 * अक्षरacter has just been prपूर्णांकed.
		 */
		udelay(PREINIT_DELAY);
	पूर्ण

	linflex_setup_watermark(sport);

	ret = uart_set_options(sport, co, baud, parity, bits, flow);

	अगर (!linflex_earlycon_same_instance)
		जाओ करोne;

	spin_lock_irqsave(&init_lock, flags);

	/* Emptying buffer */
	अगर (earlycon_buf.len) अणु
		क्रम (i = 0; i < earlycon_buf.len; i++)
			linflex_console_अक्षर_दो(earlycon_port,
				earlycon_buf.content[i]);

		kमुक्त(earlycon_buf.content);
		earlycon_buf.len = 0;
	पूर्ण

	during_init = false;
	spin_unlock_irqrestore(&init_lock, flags);

करोne:
	वापस ret;
पूर्ण

अटल काष्ठा uart_driver linflex_reg;
अटल काष्ठा console linflex_console = अणु
	.name		= DEV_NAME,
	.ग_लिखो		= linflex_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= linflex_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &linflex_reg,
पूर्ण;

अटल व्योम linflex_earlycon_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s,
				   अचिन्हित पूर्णांक n)
अणु
	काष्ठा earlycon_device *dev = con->data;

	uart_console_ग_लिखो(&dev->port, s, n, linflex_earlycon_अक्षर_दो);
पूर्ण

अटल पूर्णांक __init linflex_early_console_setup(काष्ठा earlycon_device *device,
					      स्थिर अक्षर *options)
अणु
	अगर (!device->port.membase)
		वापस -ENODEV;

	device->con->ग_लिखो = linflex_earlycon_ग_लिखो;
	earlycon_port = &device->port;

	वापस 0;
पूर्ण

OF_EARLYCON_DECLARE(linflex, "fsl,s32v234-linflexuart",
		    linflex_early_console_setup);

#घोषणा LINFLEX_CONSOLE	(&linflex_console)
#अन्यथा
#घोषणा LINFLEX_CONSOLE	शून्य
#पूर्ण_अगर

अटल काष्ठा uart_driver linflex_reg = अणु
	.owner		= THIS_MODULE,
	.driver_name	= DRIVER_NAME,
	.dev_name	= DEV_NAME,
	.nr		= ARRAY_SIZE(linflex_ports),
	.cons		= LINFLEX_CONSOLE,
पूर्ण;

अटल पूर्णांक linflex_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा uart_port *sport;
	काष्ठा resource *res;
	पूर्णांक ret;

	sport = devm_kzalloc(&pdev->dev, माप(*sport), GFP_KERNEL);
	अगर (!sport)
		वापस -ENOMEM;

	ret = of_alias_get_id(np, "serial");
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to get alias id, errno %d\n", ret);
		वापस ret;
	पूर्ण
	अगर (ret >= UART_NR) अणु
		dev_err(&pdev->dev, "driver limited to %d serial ports\n",
			UART_NR);
		वापस -ENOMEM;
	पूर्ण

	sport->line = ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	sport->mapbase = res->start;
	sport->membase = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(sport->membase))
		वापस PTR_ERR(sport->membase);

	sport->dev = &pdev->dev;
	sport->type = PORT_LINFLEXUART;
	sport->iotype = UPIO_MEM;
	sport->irq = platक्रमm_get_irq(pdev, 0);
	sport->ops = &linflex_pops;
	sport->flags = UPF_BOOT_AUTOCONF;
	sport->has_sysrq = IS_ENABLED(CONFIG_SERIAL_FSL_LINFLEXUART_CONSOLE);

	linflex_ports[sport->line] = sport;

	platक्रमm_set_drvdata(pdev, sport);

	ret = uart_add_one_port(&linflex_reg, sport);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक linflex_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uart_port *sport = platक्रमm_get_drvdata(pdev);

	uart_हटाओ_one_port(&linflex_reg, sport);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक linflex_suspend(काष्ठा device *dev)
अणु
	काष्ठा uart_port *sport = dev_get_drvdata(dev);

	uart_suspend_port(&linflex_reg, sport);

	वापस 0;
पूर्ण

अटल पूर्णांक linflex_resume(काष्ठा device *dev)
अणु
	काष्ठा uart_port *sport = dev_get_drvdata(dev);

	uart_resume_port(&linflex_reg, sport);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(linflex_pm_ops, linflex_suspend, linflex_resume);

अटल काष्ठा platक्रमm_driver linflex_driver = अणु
	.probe		= linflex_probe,
	.हटाओ		= linflex_हटाओ,
	.driver		= अणु
		.name	= DRIVER_NAME,
		.of_match_table	= linflex_dt_ids,
		.pm	= &linflex_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init linflex_serial_init(व्योम)
अणु
	पूर्णांक ret;

	ret = uart_रेजिस्टर_driver(&linflex_reg);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&linflex_driver);
	अगर (ret)
		uart_unरेजिस्टर_driver(&linflex_reg);

	वापस ret;
पूर्ण

अटल व्योम __निकास linflex_serial_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&linflex_driver);
	uart_unरेजिस्टर_driver(&linflex_reg);
पूर्ण

module_init(linflex_serial_init);
module_निकास(linflex_serial_निकास);

MODULE_DESCRIPTION("Freescale LINFlexD serial port driver");
MODULE_LICENSE("GPL v2");
