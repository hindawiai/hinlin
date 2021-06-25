<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Derived from many drivers using generic_serial पूर्णांकerface,
 * especially serial_tx3912.c by Steven J. Hill and r39xx_serial.c
 * (was in Linux/VR tree) by Jim Pick.
 *
 *  Copyright (C) 1999 Harald Koerfgen
 *  Copyright (C) 2000 Jim Pick <jim@jimpick.com>
 *  Copyright (C) 2001 Steven J. Hill (sjhill@realitydiluted.com)
 *  Copyright (C) 2000-2002 Toshiba Corporation
 *
 *  Serial driver क्रम TX3927/TX4927/TX4925/TX4938 पूर्णांकernal SIO controller
 */

#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>

#समावेश <यंत्र/पन.स>

अटल अक्षर *serial_version = "1.11";
अटल अक्षर *serial_name = "TX39/49 Serial driver";

#घोषणा PASS_LIMIT	256

#अगर !defined(CONFIG_SERIAL_TXX9_STDSERIAL)
/* "ttyS" is used क्रम standard serial driver */
#घोषणा TXX9_TTY_NAME "ttyTX"
#घोषणा TXX9_TTY_MINOR_START	196
#घोषणा TXX9_TTY_MAJOR	204
#अन्यथा
/* acts like standard serial driver */
#घोषणा TXX9_TTY_NAME "ttyS"
#घोषणा TXX9_TTY_MINOR_START	64
#घोषणा TXX9_TTY_MAJOR	TTY_MAJOR
#पूर्ण_अगर

/* flag aliases */
#घोषणा UPF_TXX9_HAVE_CTS_LINE	UPF_BUGGY_UART
#घोषणा UPF_TXX9_USE_SCLK	UPF_MAGIC_MULTIPLIER

#अगर_घोषित CONFIG_PCI
/* support क्रम Toshiba TC86C001 SIO */
#घोषणा ENABLE_SERIAL_TXX9_PCI
#पूर्ण_अगर

/*
 * Number of serial ports
 */
#घोषणा UART_NR  CONFIG_SERIAL_TXX9_NR_UARTS

काष्ठा uart_txx9_port अणु
	काष्ठा uart_port	port;
	/* No additional info क्रम now */
पूर्ण;

#घोषणा TXX9_REGION_SIZE	0x24

/* TXX9 Serial Registers */
#घोषणा TXX9_SILCR	0x00
#घोषणा TXX9_SIDICR	0x04
#घोषणा TXX9_SIDISR	0x08
#घोषणा TXX9_SICISR	0x0c
#घोषणा TXX9_SIFCR	0x10
#घोषणा TXX9_SIFLCR	0x14
#घोषणा TXX9_SIBGR	0x18
#घोषणा TXX9_SITFIFO	0x1c
#घोषणा TXX9_SIRFIFO	0x20

/* SILCR : Line Control */
#घोषणा TXX9_SILCR_SCS_MASK	0x00000060
#घोषणा TXX9_SILCR_SCS_IMCLK	0x00000000
#घोषणा TXX9_SILCR_SCS_IMCLK_BG	0x00000020
#घोषणा TXX9_SILCR_SCS_SCLK	0x00000040
#घोषणा TXX9_SILCR_SCS_SCLK_BG	0x00000060
#घोषणा TXX9_SILCR_UEPS	0x00000010
#घोषणा TXX9_SILCR_UPEN	0x00000008
#घोषणा TXX9_SILCR_USBL_MASK	0x00000004
#घोषणा TXX9_SILCR_USBL_1BIT	0x00000000
#घोषणा TXX9_SILCR_USBL_2BIT	0x00000004
#घोषणा TXX9_SILCR_UMODE_MASK	0x00000003
#घोषणा TXX9_SILCR_UMODE_8BIT	0x00000000
#घोषणा TXX9_SILCR_UMODE_7BIT	0x00000001

/* SIDICR : DMA/Int. Control */
#घोषणा TXX9_SIDICR_TDE	0x00008000
#घोषणा TXX9_SIDICR_RDE	0x00004000
#घोषणा TXX9_SIDICR_TIE	0x00002000
#घोषणा TXX9_SIDICR_RIE	0x00001000
#घोषणा TXX9_SIDICR_SPIE	0x00000800
#घोषणा TXX9_SIDICR_CTSAC	0x00000600
#घोषणा TXX9_SIDICR_STIE_MASK	0x0000003f
#घोषणा TXX9_SIDICR_STIE_OERS		0x00000020
#घोषणा TXX9_SIDICR_STIE_CTSS		0x00000010
#घोषणा TXX9_SIDICR_STIE_RBRKD	0x00000008
#घोषणा TXX9_SIDICR_STIE_TRDY		0x00000004
#घोषणा TXX9_SIDICR_STIE_TXALS	0x00000002
#घोषणा TXX9_SIDICR_STIE_UBRKD	0x00000001

/* SIDISR : DMA/Int. Status */
#घोषणा TXX9_SIDISR_UBRK	0x00008000
#घोषणा TXX9_SIDISR_UVALID	0x00004000
#घोषणा TXX9_SIDISR_UFER	0x00002000
#घोषणा TXX9_SIDISR_UPER	0x00001000
#घोषणा TXX9_SIDISR_UOER	0x00000800
#घोषणा TXX9_SIDISR_ERI	0x00000400
#घोषणा TXX9_SIDISR_TOUT	0x00000200
#घोषणा TXX9_SIDISR_TDIS	0x00000100
#घोषणा TXX9_SIDISR_RDIS	0x00000080
#घोषणा TXX9_SIDISR_STIS	0x00000040
#घोषणा TXX9_SIDISR_RFDN_MASK	0x0000001f

/* SICISR : Change Int. Status */
#घोषणा TXX9_SICISR_OERS	0x00000020
#घोषणा TXX9_SICISR_CTSS	0x00000010
#घोषणा TXX9_SICISR_RBRKD	0x00000008
#घोषणा TXX9_SICISR_TRDY	0x00000004
#घोषणा TXX9_SICISR_TXALS	0x00000002
#घोषणा TXX9_SICISR_UBRKD	0x00000001

/* SIFCR : FIFO Control */
#घोषणा TXX9_SIFCR_SWRST	0x00008000
#घोषणा TXX9_SIFCR_RDIL_MASK	0x00000180
#घोषणा TXX9_SIFCR_RDIL_1	0x00000000
#घोषणा TXX9_SIFCR_RDIL_4	0x00000080
#घोषणा TXX9_SIFCR_RDIL_8	0x00000100
#घोषणा TXX9_SIFCR_RDIL_12	0x00000180
#घोषणा TXX9_SIFCR_RDIL_MAX	0x00000180
#घोषणा TXX9_SIFCR_TDIL_MASK	0x00000018
#घोषणा TXX9_SIFCR_TDIL_1	0x00000000
#घोषणा TXX9_SIFCR_TDIL_4	0x00000001
#घोषणा TXX9_SIFCR_TDIL_8	0x00000010
#घोषणा TXX9_SIFCR_TDIL_MAX	0x00000010
#घोषणा TXX9_SIFCR_TFRST	0x00000004
#घोषणा TXX9_SIFCR_RFRST	0x00000002
#घोषणा TXX9_SIFCR_FRSTE	0x00000001
#घोषणा TXX9_SIO_TX_FIFO	8
#घोषणा TXX9_SIO_RX_FIFO	16

/* SIFLCR : Flow Control */
#घोषणा TXX9_SIFLCR_RCS	0x00001000
#घोषणा TXX9_SIFLCR_TES	0x00000800
#घोषणा TXX9_SIFLCR_RTSSC	0x00000200
#घोषणा TXX9_SIFLCR_RSDE	0x00000100
#घोषणा TXX9_SIFLCR_TSDE	0x00000080
#घोषणा TXX9_SIFLCR_RTSTL_MASK	0x0000001e
#घोषणा TXX9_SIFLCR_RTSTL_MAX	0x0000001e
#घोषणा TXX9_SIFLCR_TBRK	0x00000001

/* SIBGR : Baudrate Control */
#घोषणा TXX9_SIBGR_BCLK_MASK	0x00000300
#घोषणा TXX9_SIBGR_BCLK_T0	0x00000000
#घोषणा TXX9_SIBGR_BCLK_T2	0x00000100
#घोषणा TXX9_SIBGR_BCLK_T4	0x00000200
#घोषणा TXX9_SIBGR_BCLK_T6	0x00000300
#घोषणा TXX9_SIBGR_BRD_MASK	0x000000ff

अटल अंतरभूत अचिन्हित पूर्णांक sio_in(काष्ठा uart_txx9_port *up, पूर्णांक offset)
अणु
	चयन (up->port.iotype) अणु
	शेष:
		वापस __raw_पढ़ोl(up->port.membase + offset);
	हाल UPIO_PORT:
		वापस inl(up->port.iobase + offset);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
sio_out(काष्ठा uart_txx9_port *up, पूर्णांक offset, पूर्णांक value)
अणु
	चयन (up->port.iotype) अणु
	शेष:
		__raw_ग_लिखोl(value, up->port.membase + offset);
		अवरोध;
	हाल UPIO_PORT:
		outl(value, up->port.iobase + offset);
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
sio_mask(काष्ठा uart_txx9_port *up, पूर्णांक offset, अचिन्हित पूर्णांक value)
अणु
	sio_out(up, offset, sio_in(up, offset) & ~value);
पूर्ण
अटल अंतरभूत व्योम
sio_set(काष्ठा uart_txx9_port *up, पूर्णांक offset, अचिन्हित पूर्णांक value)
अणु
	sio_out(up, offset, sio_in(up, offset) | value);
पूर्ण

अटल अंतरभूत व्योम
sio_quot_set(काष्ठा uart_txx9_port *up, पूर्णांक quot)
अणु
	quot >>= 1;
	अगर (quot < 256)
		sio_out(up, TXX9_SIBGR, quot | TXX9_SIBGR_BCLK_T0);
	अन्यथा अगर (quot < (256 << 2))
		sio_out(up, TXX9_SIBGR, (quot >> 2) | TXX9_SIBGR_BCLK_T2);
	अन्यथा अगर (quot < (256 << 4))
		sio_out(up, TXX9_SIBGR, (quot >> 4) | TXX9_SIBGR_BCLK_T4);
	अन्यथा अगर (quot < (256 << 6))
		sio_out(up, TXX9_SIBGR, (quot >> 6) | TXX9_SIBGR_BCLK_T6);
	अन्यथा
		sio_out(up, TXX9_SIBGR, 0xff | TXX9_SIBGR_BCLK_T6);
पूर्ण

अटल काष्ठा uart_txx9_port *to_uart_txx9_port(काष्ठा uart_port *port)
अणु
	वापस container_of(port, काष्ठा uart_txx9_port, port);
पूर्ण

अटल व्योम serial_txx9_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_txx9_port *up = to_uart_txx9_port(port);
	sio_mask(up, TXX9_SIDICR, TXX9_SIDICR_TIE);
पूर्ण

अटल व्योम serial_txx9_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_txx9_port *up = to_uart_txx9_port(port);
	sio_set(up, TXX9_SIDICR, TXX9_SIDICR_TIE);
पूर्ण

अटल व्योम serial_txx9_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा uart_txx9_port *up = to_uart_txx9_port(port);
	up->port.पढ़ो_status_mask &= ~TXX9_SIDISR_RDIS;
पूर्ण

अटल व्योम serial_txx9_initialize(काष्ठा uart_port *port)
अणु
	काष्ठा uart_txx9_port *up = to_uart_txx9_port(port);
	अचिन्हित पूर्णांक पंचांगout = 10000;

	sio_out(up, TXX9_SIFCR, TXX9_SIFCR_SWRST);
	/* TX4925 BUG WORKAROUND.  Accessing SIOC रेजिस्टर
	 * immediately after soft reset causes bus error. */
	udelay(1);
	जबतक ((sio_in(up, TXX9_SIFCR) & TXX9_SIFCR_SWRST) && --पंचांगout)
		udelay(1);
	/* TX Int by FIFO Empty, RX Int by Receiving 1 अक्षर. */
	sio_set(up, TXX9_SIFCR,
		TXX9_SIFCR_TDIL_MAX | TXX9_SIFCR_RDIL_1);
	/* initial settings */
	sio_out(up, TXX9_SILCR,
		TXX9_SILCR_UMODE_8BIT | TXX9_SILCR_USBL_1BIT |
		((up->port.flags & UPF_TXX9_USE_SCLK) ?
		 TXX9_SILCR_SCS_SCLK_BG : TXX9_SILCR_SCS_IMCLK_BG));
	sio_quot_set(up, uart_get_भागisor(port, 9600));
	sio_out(up, TXX9_SIFLCR, TXX9_SIFLCR_RTSTL_MAX /* 15 */);
	sio_out(up, TXX9_SIDICR, 0);
पूर्ण

अटल अंतरभूत व्योम
receive_अक्षरs(काष्ठा uart_txx9_port *up, अचिन्हित पूर्णांक *status)
अणु
	अचिन्हित अक्षर ch;
	अचिन्हित पूर्णांक disr = *status;
	पूर्णांक max_count = 256;
	अक्षर flag;
	अचिन्हित पूर्णांक next_ignore_status_mask;

	करो अणु
		ch = sio_in(up, TXX9_SIRFIFO);
		flag = TTY_NORMAL;
		up->port.icount.rx++;

		/* mask out RFDN_MASK bit added by previous overrun */
		next_ignore_status_mask =
			up->port.ignore_status_mask & ~TXX9_SIDISR_RFDN_MASK;
		अगर (unlikely(disr & (TXX9_SIDISR_UBRK | TXX9_SIDISR_UPER |
				     TXX9_SIDISR_UFER | TXX9_SIDISR_UOER))) अणु
			/*
			 * For statistics only
			 */
			अगर (disr & TXX9_SIDISR_UBRK) अणु
				disr &= ~(TXX9_SIDISR_UFER | TXX9_SIDISR_UPER);
				up->port.icount.brk++;
				/*
				 * We करो the SysRQ and SAK checking
				 * here because otherwise the अवरोध
				 * may get masked by ignore_status_mask
				 * or पढ़ो_status_mask.
				 */
				अगर (uart_handle_अवरोध(&up->port))
					जाओ ignore_अक्षर;
			पूर्ण अन्यथा अगर (disr & TXX9_SIDISR_UPER)
				up->port.icount.parity++;
			अन्यथा अगर (disr & TXX9_SIDISR_UFER)
				up->port.icount.frame++;
			अगर (disr & TXX9_SIDISR_UOER) अणु
				up->port.icount.overrun++;
				/*
				 * The receiver पढ़ो buffer still hold
				 * a अक्षर which caused overrun.
				 * Ignore next अक्षर by adding RFDN_MASK
				 * to ignore_status_mask temporarily.
				 */
				next_ignore_status_mask |=
					TXX9_SIDISR_RFDN_MASK;
			पूर्ण

			/*
			 * Mask off conditions which should be ingored.
			 */
			disr &= up->port.पढ़ो_status_mask;

			अगर (disr & TXX9_SIDISR_UBRK) अणु
				flag = TTY_BREAK;
			पूर्ण अन्यथा अगर (disr & TXX9_SIDISR_UPER)
				flag = TTY_PARITY;
			अन्यथा अगर (disr & TXX9_SIDISR_UFER)
				flag = TTY_FRAME;
		पूर्ण
		अगर (uart_handle_sysrq_अक्षर(&up->port, ch))
			जाओ ignore_अक्षर;

		uart_insert_अक्षर(&up->port, disr, TXX9_SIDISR_UOER, ch, flag);

	ignore_अक्षर:
		up->port.ignore_status_mask = next_ignore_status_mask;
		disr = sio_in(up, TXX9_SIDISR);
	पूर्ण जबतक (!(disr & TXX9_SIDISR_UVALID) && (max_count-- > 0));

	tty_flip_buffer_push(&up->port.state->port);

	*status = disr;
पूर्ण

अटल अंतरभूत व्योम transmit_अक्षरs(काष्ठा uart_txx9_port *up)
अणु
	काष्ठा circ_buf *xmit = &up->port.state->xmit;
	पूर्णांक count;

	अगर (up->port.x_अक्षर) अणु
		sio_out(up, TXX9_SITFIFO, up->port.x_अक्षर);
		up->port.icount.tx++;
		up->port.x_अक्षर = 0;
		वापस;
	पूर्ण
	अगर (uart_circ_empty(xmit) || uart_tx_stopped(&up->port)) अणु
		serial_txx9_stop_tx(&up->port);
		वापस;
	पूर्ण

	count = TXX9_SIO_TX_FIFO;
	करो अणु
		sio_out(up, TXX9_SITFIFO, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		up->port.icount.tx++;
		अगर (uart_circ_empty(xmit))
			अवरोध;
	पूर्ण जबतक (--count > 0);

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&up->port);

	अगर (uart_circ_empty(xmit))
		serial_txx9_stop_tx(&up->port);
पूर्ण

अटल irqवापस_t serial_txx9_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक pass_counter = 0;
	काष्ठा uart_txx9_port *up = dev_id;
	अचिन्हित पूर्णांक status;

	जबतक (1) अणु
		spin_lock(&up->port.lock);
		status = sio_in(up, TXX9_SIDISR);
		अगर (!(sio_in(up, TXX9_SIDICR) & TXX9_SIDICR_TIE))
			status &= ~TXX9_SIDISR_TDIS;
		अगर (!(status & (TXX9_SIDISR_TDIS | TXX9_SIDISR_RDIS |
				TXX9_SIDISR_TOUT))) अणु
			spin_unlock(&up->port.lock);
			अवरोध;
		पूर्ण

		अगर (status & TXX9_SIDISR_RDIS)
			receive_अक्षरs(up, &status);
		अगर (status & TXX9_SIDISR_TDIS)
			transmit_अक्षरs(up);
		/* Clear TX/RX Int. Status */
		sio_mask(up, TXX9_SIDISR,
			 TXX9_SIDISR_TDIS | TXX9_SIDISR_RDIS |
			 TXX9_SIDISR_TOUT);
		spin_unlock(&up->port.lock);

		अगर (pass_counter++ > PASS_LIMIT)
			अवरोध;
	पूर्ण

	वापस pass_counter ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल अचिन्हित पूर्णांक serial_txx9_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा uart_txx9_port *up = to_uart_txx9_port(port);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ret;

	spin_lock_irqsave(&up->port.lock, flags);
	ret = (sio_in(up, TXX9_SICISR) & TXX9_SICISR_TXALS) ? TIOCSER_TEMT : 0;
	spin_unlock_irqrestore(&up->port.lock, flags);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक serial_txx9_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा uart_txx9_port *up = to_uart_txx9_port(port);
	अचिन्हित पूर्णांक ret;

	/* no modem control lines */
	ret = TIOCM_CAR | TIOCM_DSR;
	ret |= (sio_in(up, TXX9_SIFLCR) & TXX9_SIFLCR_RTSSC) ? 0 : TIOCM_RTS;
	ret |= (sio_in(up, TXX9_SICISR) & TXX9_SICISR_CTSS) ? 0 : TIOCM_CTS;

	वापस ret;
पूर्ण

अटल व्योम serial_txx9_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा uart_txx9_port *up = to_uart_txx9_port(port);

	अगर (mctrl & TIOCM_RTS)
		sio_mask(up, TXX9_SIFLCR, TXX9_SIFLCR_RTSSC);
	अन्यथा
		sio_set(up, TXX9_SIFLCR, TXX9_SIFLCR_RTSSC);
पूर्ण

अटल व्योम serial_txx9_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	काष्ठा uart_txx9_port *up = to_uart_txx9_port(port);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&up->port.lock, flags);
	अगर (अवरोध_state == -1)
		sio_set(up, TXX9_SIFLCR, TXX9_SIFLCR_TBRK);
	अन्यथा
		sio_mask(up, TXX9_SIFLCR, TXX9_SIFLCR_TBRK);
	spin_unlock_irqrestore(&up->port.lock, flags);
पूर्ण

#अगर defined(CONFIG_SERIAL_TXX9_CONSOLE) || defined(CONFIG_CONSOLE_POLL)
/*
 *	Wait क्रम transmitter & holding रेजिस्टर to empty
 */
अटल व्योम रुको_क्रम_xmitr(काष्ठा uart_txx9_port *up)
अणु
	अचिन्हित पूर्णांक पंचांगout = 10000;

	/* Wait up to 10ms क्रम the अक्षरacter(s) to be sent. */
	जबतक (--पंचांगout &&
	       !(sio_in(up, TXX9_SICISR) & TXX9_SICISR_TXALS))
		udelay(1);

	/* Wait up to 1s क्रम flow control अगर necessary */
	अगर (up->port.flags & UPF_CONS_FLOW) अणु
		पंचांगout = 1000000;
		जबतक (--पंचांगout &&
		       (sio_in(up, TXX9_SICISR) & TXX9_SICISR_CTSS))
			udelay(1);
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_CONSOLE_POLL
/*
 * Console polling routines क्रम writing and पढ़ोing from the uart जबतक
 * in an पूर्णांकerrupt or debug context.
 */

अटल पूर्णांक serial_txx9_get_poll_अक्षर(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक ier;
	अचिन्हित अक्षर c;
	काष्ठा uart_txx9_port *up = to_uart_txx9_port(port);

	/*
	 *	First save the IER then disable the पूर्णांकerrupts
	 */
	ier = sio_in(up, TXX9_SIDICR);
	sio_out(up, TXX9_SIDICR, 0);

	जबतक (sio_in(up, TXX9_SIDISR) & TXX9_SIDISR_UVALID)
		;

	c = sio_in(up, TXX9_SIRFIFO);

	/*
	 *	Finally, clear RX पूर्णांकerrupt status
	 *	and restore the IER
	 */
	sio_mask(up, TXX9_SIDISR, TXX9_SIDISR_RDIS);
	sio_out(up, TXX9_SIDICR, ier);
	वापस c;
पूर्ण


अटल व्योम serial_txx9_put_poll_अक्षर(काष्ठा uart_port *port, अचिन्हित अक्षर c)
अणु
	अचिन्हित पूर्णांक ier;
	काष्ठा uart_txx9_port *up = to_uart_txx9_port(port);

	/*
	 *	First save the IER then disable the पूर्णांकerrupts
	 */
	ier = sio_in(up, TXX9_SIDICR);
	sio_out(up, TXX9_SIDICR, 0);

	रुको_क्रम_xmitr(up);
	/*
	 *	Send the अक्षरacter out.
	 */
	sio_out(up, TXX9_SITFIFO, c);

	/*
	 *	Finally, रुको क्रम transmitter to become empty
	 *	and restore the IER
	 */
	रुको_क्रम_xmitr(up);
	sio_out(up, TXX9_SIDICR, ier);
पूर्ण

#पूर्ण_अगर /* CONFIG_CONSOLE_POLL */

अटल पूर्णांक serial_txx9_startup(काष्ठा uart_port *port)
अणु
	काष्ठा uart_txx9_port *up = to_uart_txx9_port(port);
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	/*
	 * Clear the FIFO buffers and disable them.
	 * (they will be reenabled in set_termios())
	 */
	sio_set(up, TXX9_SIFCR,
		TXX9_SIFCR_TFRST | TXX9_SIFCR_RFRST | TXX9_SIFCR_FRSTE);
	/* clear reset */
	sio_mask(up, TXX9_SIFCR,
		 TXX9_SIFCR_TFRST | TXX9_SIFCR_RFRST | TXX9_SIFCR_FRSTE);
	sio_out(up, TXX9_SIDICR, 0);

	/*
	 * Clear the पूर्णांकerrupt रेजिस्टरs.
	 */
	sio_out(up, TXX9_SIDISR, 0);

	retval = request_irq(up->port.irq, serial_txx9_पूर्णांकerrupt,
			     IRQF_SHARED, "serial_txx9", up);
	अगर (retval)
		वापस retval;

	/*
	 * Now, initialize the UART
	 */
	spin_lock_irqsave(&up->port.lock, flags);
	serial_txx9_set_mctrl(&up->port, up->port.mctrl);
	spin_unlock_irqrestore(&up->port.lock, flags);

	/* Enable RX/TX */
	sio_mask(up, TXX9_SIFLCR, TXX9_SIFLCR_RSDE | TXX9_SIFLCR_TSDE);

	/*
	 * Finally, enable पूर्णांकerrupts.
	 */
	sio_set(up, TXX9_SIDICR, TXX9_SIDICR_RIE);

	वापस 0;
पूर्ण

अटल व्योम serial_txx9_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा uart_txx9_port *up = to_uart_txx9_port(port);
	अचिन्हित दीर्घ flags;

	/*
	 * Disable पूर्णांकerrupts from this port
	 */
	sio_out(up, TXX9_SIDICR, 0);	/* disable all पूर्णांकrs */

	spin_lock_irqsave(&up->port.lock, flags);
	serial_txx9_set_mctrl(&up->port, up->port.mctrl);
	spin_unlock_irqrestore(&up->port.lock, flags);

	/*
	 * Disable अवरोध condition
	 */
	sio_mask(up, TXX9_SIFLCR, TXX9_SIFLCR_TBRK);

#अगर_घोषित CONFIG_SERIAL_TXX9_CONSOLE
	अगर (up->port.cons && up->port.line == up->port.cons->index) अणु
		मुक्त_irq(up->port.irq, up);
		वापस;
	पूर्ण
#पूर्ण_अगर
	/* reset FIFOs */
	sio_set(up, TXX9_SIFCR,
		TXX9_SIFCR_TFRST | TXX9_SIFCR_RFRST | TXX9_SIFCR_FRSTE);
	/* clear reset */
	sio_mask(up, TXX9_SIFCR,
		 TXX9_SIFCR_TFRST | TXX9_SIFCR_RFRST | TXX9_SIFCR_FRSTE);

	/* Disable RX/TX */
	sio_set(up, TXX9_SIFLCR, TXX9_SIFLCR_RSDE | TXX9_SIFLCR_TSDE);

	मुक्त_irq(up->port.irq, up);
पूर्ण

अटल व्योम
serial_txx9_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
		       काष्ठा ktermios *old)
अणु
	काष्ठा uart_txx9_port *up = to_uart_txx9_port(port);
	अचिन्हित पूर्णांक cval, fcr = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक baud, quot;

	/*
	 * We करोn't support modem control lines.
	 */
	termios->c_cflag &= ~(HUPCL | CMSPAR);
	termios->c_cflag |= CLOCAL;

	cval = sio_in(up, TXX9_SILCR);
	/* byte size and parity */
	cval &= ~TXX9_SILCR_UMODE_MASK;
	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS7:
		cval |= TXX9_SILCR_UMODE_7BIT;
		अवरोध;
	शेष:
	हाल CS5:	/* not supported */
	हाल CS6:	/* not supported */
	हाल CS8:
		cval |= TXX9_SILCR_UMODE_8BIT;
		अवरोध;
	पूर्ण

	cval &= ~TXX9_SILCR_USBL_MASK;
	अगर (termios->c_cflag & CSTOPB)
		cval |= TXX9_SILCR_USBL_2BIT;
	अन्यथा
		cval |= TXX9_SILCR_USBL_1BIT;
	cval &= ~(TXX9_SILCR_UPEN | TXX9_SILCR_UEPS);
	अगर (termios->c_cflag & PARENB)
		cval |= TXX9_SILCR_UPEN;
	अगर (!(termios->c_cflag & PARODD))
		cval |= TXX9_SILCR_UEPS;

	/*
	 * Ask the core to calculate the भागisor क्रम us.
	 */
	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk/16/2);
	quot = uart_get_भागisor(port, baud);

	/* Set up FIFOs */
	/* TX Int by FIFO Empty, RX Int by Receiving 1 अक्षर. */
	fcr = TXX9_SIFCR_TDIL_MAX | TXX9_SIFCR_RDIL_1;

	/*
	 * Ok, we're now changing the port state.  Do it with
	 * पूर्णांकerrupts disabled.
	 */
	spin_lock_irqsave(&up->port.lock, flags);

	/*
	 * Update the per-port समयout.
	 */
	uart_update_समयout(port, termios->c_cflag, baud);

	up->port.पढ़ो_status_mask = TXX9_SIDISR_UOER |
		TXX9_SIDISR_TDIS | TXX9_SIDISR_RDIS;
	अगर (termios->c_अगरlag & INPCK)
		up->port.पढ़ो_status_mask |= TXX9_SIDISR_UFER | TXX9_SIDISR_UPER;
	अगर (termios->c_अगरlag & (IGNBRK | BRKINT | PARMRK))
		up->port.पढ़ो_status_mask |= TXX9_SIDISR_UBRK;

	/*
	 * Characteres to ignore
	 */
	up->port.ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNPAR)
		up->port.ignore_status_mask |= TXX9_SIDISR_UPER | TXX9_SIDISR_UFER;
	अगर (termios->c_अगरlag & IGNBRK) अणु
		up->port.ignore_status_mask |= TXX9_SIDISR_UBRK;
		/*
		 * If we're ignoring parity and अवरोध indicators,
		 * ignore overruns too (क्रम real raw support).
		 */
		अगर (termios->c_अगरlag & IGNPAR)
			up->port.ignore_status_mask |= TXX9_SIDISR_UOER;
	पूर्ण

	/*
	 * ignore all अक्षरacters अगर CREAD is not set
	 */
	अगर ((termios->c_cflag & CREAD) == 0)
		up->port.ignore_status_mask |= TXX9_SIDISR_RDIS;

	/* CTS flow control flag */
	अगर ((termios->c_cflag & CRTSCTS) &&
	    (up->port.flags & UPF_TXX9_HAVE_CTS_LINE)) अणु
		sio_set(up, TXX9_SIFLCR,
			TXX9_SIFLCR_RCS | TXX9_SIFLCR_TES);
	पूर्ण अन्यथा अणु
		sio_mask(up, TXX9_SIFLCR,
			 TXX9_SIFLCR_RCS | TXX9_SIFLCR_TES);
	पूर्ण

	sio_out(up, TXX9_SILCR, cval);
	sio_quot_set(up, quot);
	sio_out(up, TXX9_SIFCR, fcr);

	serial_txx9_set_mctrl(&up->port, up->port.mctrl);
	spin_unlock_irqrestore(&up->port.lock, flags);
पूर्ण

अटल व्योम
serial_txx9_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state,
	      अचिन्हित पूर्णांक oldstate)
अणु
	/*
	 * If oldstate was -1 this is called from
	 * uart_configure_port().  In this हाल करो not initialize the
	 * port now, because the port was alपढ़ोy initialized (क्रम
	 * non-console port) or should not be initialized here (क्रम
	 * console port).  If we initialized the port here we lose
	 * serial console settings.
	 */
	अगर (state == 0 && oldstate != -1)
		serial_txx9_initialize(port);
पूर्ण

अटल पूर्णांक serial_txx9_request_resource(काष्ठा uart_txx9_port *up)
अणु
	अचिन्हित पूर्णांक size = TXX9_REGION_SIZE;
	पूर्णांक ret = 0;

	चयन (up->port.iotype) अणु
	शेष:
		अगर (!up->port.mapbase)
			अवरोध;

		अगर (!request_mem_region(up->port.mapbase, size, "serial_txx9")) अणु
			ret = -EBUSY;
			अवरोध;
		पूर्ण

		अगर (up->port.flags & UPF_IOREMAP) अणु
			up->port.membase = ioremap(up->port.mapbase, size);
			अगर (!up->port.membase) अणु
				release_mem_region(up->port.mapbase, size);
				ret = -ENOMEM;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल UPIO_PORT:
		अगर (!request_region(up->port.iobase, size, "serial_txx9"))
			ret = -EBUSY;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम serial_txx9_release_resource(काष्ठा uart_txx9_port *up)
अणु
	अचिन्हित पूर्णांक size = TXX9_REGION_SIZE;

	चयन (up->port.iotype) अणु
	शेष:
		अगर (!up->port.mapbase)
			अवरोध;

		अगर (up->port.flags & UPF_IOREMAP) अणु
			iounmap(up->port.membase);
			up->port.membase = शून्य;
		पूर्ण

		release_mem_region(up->port.mapbase, size);
		अवरोध;

	हाल UPIO_PORT:
		release_region(up->port.iobase, size);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम serial_txx9_release_port(काष्ठा uart_port *port)
अणु
	काष्ठा uart_txx9_port *up = to_uart_txx9_port(port);
	serial_txx9_release_resource(up);
पूर्ण

अटल पूर्णांक serial_txx9_request_port(काष्ठा uart_port *port)
अणु
	काष्ठा uart_txx9_port *up = to_uart_txx9_port(port);
	वापस serial_txx9_request_resource(up);
पूर्ण

अटल व्योम serial_txx9_config_port(काष्ठा uart_port *port, पूर्णांक uflags)
अणु
	काष्ठा uart_txx9_port *up = to_uart_txx9_port(port);
	पूर्णांक ret;

	/*
	 * Find the region that we can probe क्रम.  This in turn
	 * tells us whether we can probe क्रम the type of port.
	 */
	ret = serial_txx9_request_resource(up);
	अगर (ret < 0)
		वापस;
	port->type = PORT_TXX9;
	up->port.fअगरosize = TXX9_SIO_TX_FIFO;

#अगर_घोषित CONFIG_SERIAL_TXX9_CONSOLE
	अगर (up->port.line == up->port.cons->index)
		वापस;
#पूर्ण_अगर
	serial_txx9_initialize(port);
पूर्ण

अटल स्थिर अक्षर *
serial_txx9_type(काष्ठा uart_port *port)
अणु
	वापस "txx9";
पूर्ण

अटल स्थिर काष्ठा uart_ops serial_txx9_pops = अणु
	.tx_empty	= serial_txx9_tx_empty,
	.set_mctrl	= serial_txx9_set_mctrl,
	.get_mctrl	= serial_txx9_get_mctrl,
	.stop_tx	= serial_txx9_stop_tx,
	.start_tx	= serial_txx9_start_tx,
	.stop_rx	= serial_txx9_stop_rx,
	.अवरोध_ctl	= serial_txx9_अवरोध_ctl,
	.startup	= serial_txx9_startup,
	.shutकरोwn	= serial_txx9_shutकरोwn,
	.set_termios	= serial_txx9_set_termios,
	.pm		= serial_txx9_pm,
	.type		= serial_txx9_type,
	.release_port	= serial_txx9_release_port,
	.request_port	= serial_txx9_request_port,
	.config_port	= serial_txx9_config_port,
#अगर_घोषित CONFIG_CONSOLE_POLL
	.poll_get_अक्षर	= serial_txx9_get_poll_अक्षर,
	.poll_put_अक्षर	= serial_txx9_put_poll_अक्षर,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा uart_txx9_port serial_txx9_ports[UART_NR];

अटल व्योम __init serial_txx9_रेजिस्टर_ports(काष्ठा uart_driver *drv,
					      काष्ठा device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < UART_NR; i++) अणु
		काष्ठा uart_txx9_port *up = &serial_txx9_ports[i];

		up->port.line = i;
		up->port.ops = &serial_txx9_pops;
		up->port.dev = dev;
		अगर (up->port.iobase || up->port.mapbase)
			uart_add_one_port(drv, &up->port);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SERIAL_TXX9_CONSOLE

अटल व्योम serial_txx9_console_अक्षर_दो(काष्ठा uart_port *port, पूर्णांक ch)
अणु
	काष्ठा uart_txx9_port *up = to_uart_txx9_port(port);

	रुको_क्रम_xmitr(up);
	sio_out(up, TXX9_SITFIFO, ch);
पूर्ण

/*
 *	Prपूर्णांक a string to the serial port trying not to disturb
 *	any possible real use of the port...
 *
 *	The console_lock must be held when we get here.
 */
अटल व्योम
serial_txx9_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, अचिन्हित पूर्णांक count)
अणु
	काष्ठा uart_txx9_port *up = &serial_txx9_ports[co->index];
	अचिन्हित पूर्णांक ier, flcr;

	/*
	 *	First save the UER then disable the पूर्णांकerrupts
	 */
	ier = sio_in(up, TXX9_SIDICR);
	sio_out(up, TXX9_SIDICR, 0);
	/*
	 *	Disable flow-control अगर enabled (and unnecessary)
	 */
	flcr = sio_in(up, TXX9_SIFLCR);
	अगर (!(up->port.flags & UPF_CONS_FLOW) && (flcr & TXX9_SIFLCR_TES))
		sio_out(up, TXX9_SIFLCR, flcr & ~TXX9_SIFLCR_TES);

	uart_console_ग_लिखो(&up->port, s, count, serial_txx9_console_अक्षर_दो);

	/*
	 *	Finally, रुको क्रम transmitter to become empty
	 *	and restore the IER
	 */
	रुको_क्रम_xmitr(up);
	sio_out(up, TXX9_SIFLCR, flcr);
	sio_out(up, TXX9_SIDICR, ier);
पूर्ण

अटल पूर्णांक __init serial_txx9_console_setup(काष्ठा console *co, अक्षर *options)
अणु
	काष्ठा uart_port *port;
	काष्ठा uart_txx9_port *up;
	पूर्णांक baud = 9600;
	पूर्णांक bits = 8;
	पूर्णांक parity = 'n';
	पूर्णांक flow = 'n';

	/*
	 * Check whether an invalid uart number has been specअगरied, and
	 * अगर so, search क्रम the first available port that करोes have
	 * console support.
	 */
	अगर (co->index >= UART_NR)
		co->index = 0;
	up = &serial_txx9_ports[co->index];
	port = &up->port;
	अगर (!port->ops)
		वापस -ENODEV;

	serial_txx9_initialize(&up->port);

	अगर (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);

	वापस uart_set_options(port, co, baud, parity, bits, flow);
पूर्ण

अटल काष्ठा uart_driver serial_txx9_reg;
अटल काष्ठा console serial_txx9_console = अणु
	.name		= TXX9_TTY_NAME,
	.ग_लिखो		= serial_txx9_console_ग_लिखो,
	.device		= uart_console_device,
	.setup		= serial_txx9_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &serial_txx9_reg,
पूर्ण;

अटल पूर्णांक __init serial_txx9_console_init(व्योम)
अणु
	रेजिस्टर_console(&serial_txx9_console);
	वापस 0;
पूर्ण
console_initcall(serial_txx9_console_init);

#घोषणा SERIAL_TXX9_CONSOLE	&serial_txx9_console
#अन्यथा
#घोषणा SERIAL_TXX9_CONSOLE	शून्य
#पूर्ण_अगर

अटल काष्ठा uart_driver serial_txx9_reg = अणु
	.owner			= THIS_MODULE,
	.driver_name		= "serial_txx9",
	.dev_name		= TXX9_TTY_NAME,
	.major			= TXX9_TTY_MAJOR,
	.minor			= TXX9_TTY_MINOR_START,
	.nr			= UART_NR,
	.cons			= SERIAL_TXX9_CONSOLE,
पूर्ण;

पूर्णांक __init early_serial_txx9_setup(काष्ठा uart_port *port)
अणु
	अगर (port->line >= ARRAY_SIZE(serial_txx9_ports))
		वापस -ENODEV;

	serial_txx9_ports[port->line].port = *port;
	serial_txx9_ports[port->line].port.ops = &serial_txx9_pops;
	serial_txx9_ports[port->line].port.flags |=
		UPF_BOOT_AUTOCONF | UPF_FIXED_PORT;
	वापस 0;
पूर्ण

अटल DEFINE_MUTEX(serial_txx9_mutex);

/**
 *	serial_txx9_रेजिस्टर_port - रेजिस्टर a serial port
 *	@port: serial port ढाँचा
 *
 *	Configure the serial port specअगरied by the request.
 *
 *	The port is then probed and अगर necessary the IRQ is स्वतःdetected
 *	If this fails an error is वापसed.
 *
 *	On success the port is पढ़ोy to use and the line number is वापसed.
 */
अटल पूर्णांक serial_txx9_रेजिस्टर_port(काष्ठा uart_port *port)
अणु
	पूर्णांक i;
	काष्ठा uart_txx9_port *uart;
	पूर्णांक ret = -ENOSPC;

	mutex_lock(&serial_txx9_mutex);
	क्रम (i = 0; i < UART_NR; i++) अणु
		uart = &serial_txx9_ports[i];
		अगर (uart_match_port(&uart->port, port)) अणु
			uart_हटाओ_one_port(&serial_txx9_reg, &uart->port);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == UART_NR) अणु
		/* Find unused port */
		क्रम (i = 0; i < UART_NR; i++) अणु
			uart = &serial_txx9_ports[i];
			अगर (!(uart->port.iobase || uart->port.mapbase))
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (i < UART_NR) अणु
		uart->port.iobase = port->iobase;
		uart->port.membase = port->membase;
		uart->port.irq      = port->irq;
		uart->port.uartclk  = port->uartclk;
		uart->port.iotype   = port->iotype;
		uart->port.flags    = port->flags
			| UPF_BOOT_AUTOCONF | UPF_FIXED_PORT;
		uart->port.mapbase  = port->mapbase;
		अगर (port->dev)
			uart->port.dev = port->dev;
		ret = uart_add_one_port(&serial_txx9_reg, &uart->port);
		अगर (ret == 0)
			ret = uart->port.line;
	पूर्ण
	mutex_unlock(&serial_txx9_mutex);
	वापस ret;
पूर्ण

/**
 *	serial_txx9_unरेजिस्टर_port - हटाओ a txx9 serial port at runसमय
 *	@line: serial line number
 *
 *	Remove one serial port.  This may not be called from पूर्णांकerrupt
 *	context.  We hand the port back to the our control.
 */
अटल व्योम serial_txx9_unरेजिस्टर_port(पूर्णांक line)
अणु
	काष्ठा uart_txx9_port *uart = &serial_txx9_ports[line];

	mutex_lock(&serial_txx9_mutex);
	uart_हटाओ_one_port(&serial_txx9_reg, &uart->port);
	uart->port.flags = 0;
	uart->port.type = PORT_UNKNOWN;
	uart->port.iobase = 0;
	uart->port.mapbase = 0;
	uart->port.membase = शून्य;
	uart->port.dev = शून्य;
	mutex_unlock(&serial_txx9_mutex);
पूर्ण

/*
 * Register a set of serial devices attached to a platक्रमm device.
 */
अटल पूर्णांक serial_txx9_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा uart_port *p = dev_get_platdata(&dev->dev);
	काष्ठा uart_port port;
	पूर्णांक ret, i;

	स_रखो(&port, 0, माप(काष्ठा uart_port));
	क्रम (i = 0; p && p->uartclk != 0; p++, i++) अणु
		port.iobase	= p->iobase;
		port.membase	= p->membase;
		port.irq	= p->irq;
		port.uartclk	= p->uartclk;
		port.iotype	= p->iotype;
		port.flags	= p->flags;
		port.mapbase	= p->mapbase;
		port.dev	= &dev->dev;
		port.has_sysrq	= IS_ENABLED(CONFIG_SERIAL_TXX9_CONSOLE);
		ret = serial_txx9_रेजिस्टर_port(&port);
		अगर (ret < 0) अणु
			dev_err(&dev->dev, "unable to register port at index %d "
				"(IO%lx MEM%llx IRQ%d): %d\n", i,
				p->iobase, (अचिन्हित दीर्घ दीर्घ)p->mapbase,
				p->irq, ret);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Remove serial ports रेजिस्टरed against a platक्रमm device.
 */
अटल पूर्णांक serial_txx9_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < UART_NR; i++) अणु
		काष्ठा uart_txx9_port *up = &serial_txx9_ports[i];

		अगर (up->port.dev == &dev->dev)
			serial_txx9_unरेजिस्टर_port(i);
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक serial_txx9_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < UART_NR; i++) अणु
		काष्ठा uart_txx9_port *up = &serial_txx9_ports[i];

		अगर (up->port.type != PORT_UNKNOWN && up->port.dev == &dev->dev)
			uart_suspend_port(&serial_txx9_reg, &up->port);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक serial_txx9_resume(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < UART_NR; i++) अणु
		काष्ठा uart_txx9_port *up = &serial_txx9_ports[i];

		अगर (up->port.type != PORT_UNKNOWN && up->port.dev == &dev->dev)
			uart_resume_port(&serial_txx9_reg, &up->port);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver serial_txx9_plat_driver = अणु
	.probe		= serial_txx9_probe,
	.हटाओ		= serial_txx9_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= serial_txx9_suspend,
	.resume		= serial_txx9_resume,
#पूर्ण_अगर
	.driver		= अणु
		.name	= "serial_txx9",
	पूर्ण,
पूर्ण;

#अगर_घोषित ENABLE_SERIAL_TXX9_PCI
/*
 * Probe one serial board.  Unक्रमtunately, there is no rhyme nor reason
 * to the arrangement of serial ports on a PCI card.
 */
अटल पूर्णांक
pciserial_txx9_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा uart_port port;
	पूर्णांक line;
	पूर्णांक rc;

	rc = pci_enable_device(dev);
	अगर (rc)
		वापस rc;

	स_रखो(&port, 0, माप(port));
	port.ops = &serial_txx9_pops;
	port.flags |= UPF_TXX9_HAVE_CTS_LINE;
	port.uartclk = 66670000;
	port.irq = dev->irq;
	port.iotype = UPIO_PORT;
	port.iobase = pci_resource_start(dev, 1);
	port.dev = &dev->dev;
	line = serial_txx9_रेजिस्टर_port(&port);
	अगर (line < 0) अणु
		prपूर्णांकk(KERN_WARNING "Couldn't register serial port %s: %d\n", pci_name(dev), line);
		pci_disable_device(dev);
		वापस line;
	पूर्ण
	pci_set_drvdata(dev, &serial_txx9_ports[line]);

	वापस 0;
पूर्ण

अटल व्योम pciserial_txx9_हटाओ_one(काष्ठा pci_dev *dev)
अणु
	काष्ठा uart_txx9_port *up = pci_get_drvdata(dev);

	अगर (up) अणु
		serial_txx9_unरेजिस्टर_port(up->port.line);
		pci_disable_device(dev);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक pciserial_txx9_suspend_one(काष्ठा pci_dev *dev, pm_message_t state)
अणु
	काष्ठा uart_txx9_port *up = pci_get_drvdata(dev);

	अगर (up)
		uart_suspend_port(&serial_txx9_reg, &up->port);
	pci_save_state(dev);
	pci_set_घातer_state(dev, pci_choose_state(dev, state));
	वापस 0;
पूर्ण

अटल पूर्णांक pciserial_txx9_resume_one(काष्ठा pci_dev *dev)
अणु
	काष्ठा uart_txx9_port *up = pci_get_drvdata(dev);

	pci_set_घातer_state(dev, PCI_D0);
	pci_restore_state(dev);
	अगर (up)
		uart_resume_port(&serial_txx9_reg, &up->port);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id serial_txx9_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_TOSHIBA_2, PCI_DEVICE_ID_TOSHIBA_TC86C001_MISC) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा pci_driver serial_txx9_pci_driver = अणु
	.name		= "serial_txx9",
	.probe		= pciserial_txx9_init_one,
	.हटाओ		= pciserial_txx9_हटाओ_one,
#अगर_घोषित CONFIG_PM
	.suspend	= pciserial_txx9_suspend_one,
	.resume		= pciserial_txx9_resume_one,
#पूर्ण_अगर
	.id_table	= serial_txx9_pci_tbl,
पूर्ण;

MODULE_DEVICE_TABLE(pci, serial_txx9_pci_tbl);
#पूर्ण_अगर /* ENABLE_SERIAL_TXX9_PCI */

अटल काष्ठा platक्रमm_device *serial_txx9_plat_devs;

अटल पूर्णांक __init serial_txx9_init(व्योम)
अणु
	पूर्णांक ret;

 	prपूर्णांकk(KERN_INFO "%s version %s\n", serial_name, serial_version);

	ret = uart_रेजिस्टर_driver(&serial_txx9_reg);
	अगर (ret)
		जाओ out;

	serial_txx9_plat_devs = platक्रमm_device_alloc("serial_txx9", -1);
	अगर (!serial_txx9_plat_devs) अणु
		ret = -ENOMEM;
		जाओ unreg_uart_drv;
	पूर्ण

	ret = platक्रमm_device_add(serial_txx9_plat_devs);
	अगर (ret)
		जाओ put_dev;

	serial_txx9_रेजिस्टर_ports(&serial_txx9_reg,
				   &serial_txx9_plat_devs->dev);

	ret = platक्रमm_driver_रेजिस्टर(&serial_txx9_plat_driver);
	अगर (ret)
		जाओ del_dev;

#अगर_घोषित ENABLE_SERIAL_TXX9_PCI
	ret = pci_रेजिस्टर_driver(&serial_txx9_pci_driver);
	अगर (ret) अणु
		platक्रमm_driver_unरेजिस्टर(&serial_txx9_plat_driver);
	पूर्ण
#पूर्ण_अगर
	अगर (ret == 0)
		जाओ out;

 del_dev:
	platक्रमm_device_del(serial_txx9_plat_devs);
 put_dev:
	platक्रमm_device_put(serial_txx9_plat_devs);
 unreg_uart_drv:
	uart_unरेजिस्टर_driver(&serial_txx9_reg);
 out:
	वापस ret;
पूर्ण

अटल व्योम __निकास serial_txx9_निकास(व्योम)
अणु
	पूर्णांक i;

#अगर_घोषित ENABLE_SERIAL_TXX9_PCI
	pci_unरेजिस्टर_driver(&serial_txx9_pci_driver);
#पूर्ण_अगर
	platक्रमm_driver_unरेजिस्टर(&serial_txx9_plat_driver);
	platक्रमm_device_unरेजिस्टर(serial_txx9_plat_devs);
	क्रम (i = 0; i < UART_NR; i++) अणु
		काष्ठा uart_txx9_port *up = &serial_txx9_ports[i];
		अगर (up->port.iobase || up->port.mapbase)
			uart_हटाओ_one_port(&serial_txx9_reg, &up->port);
	पूर्ण

	uart_unरेजिस्टर_driver(&serial_txx9_reg);
पूर्ण

module_init(serial_txx9_init);
module_निकास(serial_txx9_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("TX39/49 serial driver");

MODULE_ALIAS_CHARDEV_MAJOR(TXX9_TTY_MAJOR);
