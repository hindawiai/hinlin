<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Comtrol RocketPort EXPRESS/अनन्त cards
 *
 * Copyright (C) 2012 Kevin Cernekee <cernekee@gmail.com>
 *
 * Inspired by, and loosely based on:
 *
 *   ar933x_uart.c
 *     Copyright (C) 2011 Gabor Juhos <juhosg@खोलोwrt.org>
 *
 *   rocketport_infinity_express-linux-1.20.tar.gz
 *     Copyright (C) 2004-2011 Comtrol, Inc.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/compiler.h>
#समावेश <linux/completion.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/types.h>

#घोषणा DRV_NAME			"rp2"

#घोषणा RP2_FW_NAME			"rp2.fw"
#घोषणा RP2_UCODE_BYTES			0x3f

#घोषणा PORTS_PER_ASIC			16
#घोषणा ALL_PORTS_MASK			(BIT(PORTS_PER_ASIC) - 1)

#घोषणा UART_CLOCK			44236800
#घोषणा DEFAULT_BAUD_DIV		(UART_CLOCK / (9600 * 16))
#घोषणा FIFO_SIZE			512

/* BAR0 रेजिस्टरs */
#घोषणा RP2_FPGA_CTL0			0x110
#घोषणा RP2_FPGA_CTL1			0x11c
#घोषणा RP2_IRQ_MASK			0x1ec
#घोषणा RP2_IRQ_MASK_EN_m		BIT(0)
#घोषणा RP2_IRQ_STATUS			0x1f0

/* BAR1 रेजिस्टरs */
#घोषणा RP2_ASIC_SPACING		0x1000
#घोषणा RP2_ASIC_OFFSET(i)		((i) << ilog2(RP2_ASIC_SPACING))

#घोषणा RP2_PORT_BASE			0x000
#घोषणा RP2_PORT_SPACING		0x040

#घोषणा RP2_UCODE_BASE			0x400
#घोषणा RP2_UCODE_SPACING		0x80

#घोषणा RP2_CLK_PRESCALER		0xc00
#घोषणा RP2_CH_IRQ_STAT			0xc04
#घोषणा RP2_CH_IRQ_MASK			0xc08
#घोषणा RP2_ASIC_IRQ			0xd00
#घोषणा RP2_ASIC_IRQ_EN_m		BIT(20)
#घोषणा RP2_GLOBAL_CMD			0xd0c
#घोषणा RP2_ASIC_CFG			0xd04

/* port रेजिस्टरs */
#घोषणा RP2_DATA_DWORD			0x000

#घोषणा RP2_DATA_BYTE			0x008
#घोषणा RP2_DATA_BYTE_ERR_PARITY_m	BIT(8)
#घोषणा RP2_DATA_BYTE_ERR_OVERRUN_m	BIT(9)
#घोषणा RP2_DATA_BYTE_ERR_FRAMING_m	BIT(10)
#घोषणा RP2_DATA_BYTE_BREAK_m		BIT(11)

/* This lets uart_insert_अक्षर() drop bytes received on a !CREAD port */
#घोषणा RP2_DUMMY_READ			BIT(16)

#घोषणा RP2_DATA_BYTE_EXCEPTION_MASK	(RP2_DATA_BYTE_ERR_PARITY_m | \
					 RP2_DATA_BYTE_ERR_OVERRUN_m | \
					 RP2_DATA_BYTE_ERR_FRAMING_m | \
					 RP2_DATA_BYTE_BREAK_m)

#घोषणा RP2_RX_FIFO_COUNT		0x00c
#घोषणा RP2_TX_FIFO_COUNT		0x00e

#घोषणा RP2_CHAN_STAT			0x010
#घोषणा RP2_CHAN_STAT_RXDATA_m		BIT(0)
#घोषणा RP2_CHAN_STAT_DCD_m		BIT(3)
#घोषणा RP2_CHAN_STAT_DSR_m		BIT(4)
#घोषणा RP2_CHAN_STAT_CTS_m		BIT(5)
#घोषणा RP2_CHAN_STAT_RI_m		BIT(6)
#घोषणा RP2_CHAN_STAT_OVERRUN_m		BIT(13)
#घोषणा RP2_CHAN_STAT_DSR_CHANGED_m	BIT(16)
#घोषणा RP2_CHAN_STAT_CTS_CHANGED_m	BIT(17)
#घोषणा RP2_CHAN_STAT_CD_CHANGED_m	BIT(18)
#घोषणा RP2_CHAN_STAT_RI_CHANGED_m	BIT(22)
#घोषणा RP2_CHAN_STAT_TXEMPTY_m		BIT(25)

#घोषणा RP2_CHAN_STAT_MS_CHANGED_MASK	(RP2_CHAN_STAT_DSR_CHANGED_m | \
					 RP2_CHAN_STAT_CTS_CHANGED_m | \
					 RP2_CHAN_STAT_CD_CHANGED_m | \
					 RP2_CHAN_STAT_RI_CHANGED_m)

#घोषणा RP2_TXRX_CTL			0x014
#घोषणा RP2_TXRX_CTL_MSRIRQ_m		BIT(0)
#घोषणा RP2_TXRX_CTL_RXIRQ_m		BIT(2)
#घोषणा RP2_TXRX_CTL_RX_TRIG_s		3
#घोषणा RP2_TXRX_CTL_RX_TRIG_m		(0x3 << RP2_TXRX_CTL_RX_TRIG_s)
#घोषणा RP2_TXRX_CTL_RX_TRIG_1		(0x1 << RP2_TXRX_CTL_RX_TRIG_s)
#घोषणा RP2_TXRX_CTL_RX_TRIG_256	(0x2 << RP2_TXRX_CTL_RX_TRIG_s)
#घोषणा RP2_TXRX_CTL_RX_TRIG_448	(0x3 << RP2_TXRX_CTL_RX_TRIG_s)
#घोषणा RP2_TXRX_CTL_RX_EN_m		BIT(5)
#घोषणा RP2_TXRX_CTL_RTSFLOW_m		BIT(6)
#घोषणा RP2_TXRX_CTL_DTRFLOW_m		BIT(7)
#घोषणा RP2_TXRX_CTL_TX_TRIG_s		16
#घोषणा RP2_TXRX_CTL_TX_TRIG_m		(0x3 << RP2_TXRX_CTL_RX_TRIG_s)
#घोषणा RP2_TXRX_CTL_DSRFLOW_m		BIT(18)
#घोषणा RP2_TXRX_CTL_TXIRQ_m		BIT(19)
#घोषणा RP2_TXRX_CTL_CTSFLOW_m		BIT(23)
#घोषणा RP2_TXRX_CTL_TX_EN_m		BIT(24)
#घोषणा RP2_TXRX_CTL_RTS_m		BIT(25)
#घोषणा RP2_TXRX_CTL_DTR_m		BIT(26)
#घोषणा RP2_TXRX_CTL_LOOP_m		BIT(27)
#घोषणा RP2_TXRX_CTL_BREAK_m		BIT(28)
#घोषणा RP2_TXRX_CTL_CMSPAR_m		BIT(29)
#घोषणा RP2_TXRX_CTL_nPARODD_m		BIT(30)
#घोषणा RP2_TXRX_CTL_PARENB_m		BIT(31)

#घोषणा RP2_UART_CTL			0x018
#घोषणा RP2_UART_CTL_MODE_s		0
#घोषणा RP2_UART_CTL_MODE_m		(0x7 << RP2_UART_CTL_MODE_s)
#घोषणा RP2_UART_CTL_MODE_rs232		(0x1 << RP2_UART_CTL_MODE_s)
#घोषणा RP2_UART_CTL_FLUSH_RX_m		BIT(3)
#घोषणा RP2_UART_CTL_FLUSH_TX_m		BIT(4)
#घोषणा RP2_UART_CTL_RESET_CH_m		BIT(5)
#घोषणा RP2_UART_CTL_XMIT_EN_m		BIT(6)
#घोषणा RP2_UART_CTL_DATABITS_s		8
#घोषणा RP2_UART_CTL_DATABITS_m		(0x3 << RP2_UART_CTL_DATABITS_s)
#घोषणा RP2_UART_CTL_DATABITS_8		(0x3 << RP2_UART_CTL_DATABITS_s)
#घोषणा RP2_UART_CTL_DATABITS_7		(0x2 << RP2_UART_CTL_DATABITS_s)
#घोषणा RP2_UART_CTL_DATABITS_6		(0x1 << RP2_UART_CTL_DATABITS_s)
#घोषणा RP2_UART_CTL_DATABITS_5		(0x0 << RP2_UART_CTL_DATABITS_s)
#घोषणा RP2_UART_CTL_STOPBITS_m		BIT(10)

#घोषणा RP2_BAUD			0x01c

/* ucode रेजिस्टरs */
#घोषणा RP2_TX_SWFLOW			0x02
#घोषणा RP2_TX_SWFLOW_ena		0x81
#घोषणा RP2_TX_SWFLOW_dis		0x9d

#घोषणा RP2_RX_SWFLOW			0x0c
#घोषणा RP2_RX_SWFLOW_ena		0x81
#घोषणा RP2_RX_SWFLOW_dis		0x8d

#घोषणा RP2_RX_FIFO			0x37
#घोषणा RP2_RX_FIFO_ena			0x08
#घोषणा RP2_RX_FIFO_dis			0x81

अटल काष्ठा uart_driver rp2_uart_driver = अणु
	.owner				= THIS_MODULE,
	.driver_name			= DRV_NAME,
	.dev_name			= "ttyRP",
	.nr				= CONFIG_SERIAL_RP2_NR_UARTS,
पूर्ण;

काष्ठा rp2_card;

काष्ठा rp2_uart_port अणु
	काष्ठा uart_port		port;
	पूर्णांक				idx;
	पूर्णांक				ignore_rx;
	काष्ठा rp2_card			*card;
	व्योम __iomem			*asic_base;
	व्योम __iomem			*base;
	व्योम __iomem			*ucode;
पूर्ण;

काष्ठा rp2_card अणु
	काष्ठा pci_dev			*pdev;
	काष्ठा rp2_uart_port		*ports;
	पूर्णांक				n_ports;
	पूर्णांक				initialized_ports;
	पूर्णांक				minor_start;
	पूर्णांक				smpte;
	व्योम __iomem			*bar0;
	व्योम __iomem			*bar1;
	spinlock_t			card_lock;
पूर्ण;

#घोषणा RP_ID(prod) PCI_VDEVICE(RP, (prod))
#घोषणा RP_CAP(ports, smpte) (((ports) << 8) | ((smpte) << 0))

अटल अंतरभूत व्योम rp2_decode_cap(स्थिर काष्ठा pci_device_id *id,
				  पूर्णांक *ports, पूर्णांक *smpte)
अणु
	*ports = id->driver_data >> 8;
	*smpte = id->driver_data & 0xff;
पूर्ण

अटल DEFINE_SPINLOCK(rp2_minor_lock);
अटल पूर्णांक rp2_minor_next;

अटल पूर्णांक rp2_alloc_ports(पूर्णांक n_ports)
अणु
	पूर्णांक ret = -ENOSPC;

	spin_lock(&rp2_minor_lock);
	अगर (rp2_minor_next + n_ports <= CONFIG_SERIAL_RP2_NR_UARTS) अणु
		/* sorry, no support क्रम hot unplugging inभागidual cards */
		ret = rp2_minor_next;
		rp2_minor_next += n_ports;
	पूर्ण
	spin_unlock(&rp2_minor_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत काष्ठा rp2_uart_port *port_to_up(काष्ठा uart_port *port)
अणु
	वापस container_of(port, काष्ठा rp2_uart_port, port);
पूर्ण

अटल व्योम rp2_rmw(काष्ठा rp2_uart_port *up, पूर्णांक reg,
		    u32 clr_bits, u32 set_bits)
अणु
	u32 पंचांगp = पढ़ोl(up->base + reg);
	पंचांगp &= ~clr_bits;
	पंचांगp |= set_bits;
	ग_लिखोl(पंचांगp, up->base + reg);
पूर्ण

अटल व्योम rp2_rmw_clr(काष्ठा rp2_uart_port *up, पूर्णांक reg, u32 val)
अणु
	rp2_rmw(up, reg, val, 0);
पूर्ण

अटल व्योम rp2_rmw_set(काष्ठा rp2_uart_port *up, पूर्णांक reg, u32 val)
अणु
	rp2_rmw(up, reg, 0, val);
पूर्ण

अटल व्योम rp2_mask_ch_irq(काष्ठा rp2_uart_port *up, पूर्णांक ch_num,
			    पूर्णांक is_enabled)
अणु
	अचिन्हित दीर्घ flags, irq_mask;

	spin_lock_irqsave(&up->card->card_lock, flags);

	irq_mask = पढ़ोl(up->asic_base + RP2_CH_IRQ_MASK);
	अगर (is_enabled)
		irq_mask &= ~BIT(ch_num);
	अन्यथा
		irq_mask |= BIT(ch_num);
	ग_लिखोl(irq_mask, up->asic_base + RP2_CH_IRQ_MASK);

	spin_unlock_irqrestore(&up->card->card_lock, flags);
पूर्ण

अटल अचिन्हित पूर्णांक rp2_uart_tx_empty(काष्ठा uart_port *port)
अणु
	काष्ठा rp2_uart_port *up = port_to_up(port);
	अचिन्हित दीर्घ tx_fअगरo_bytes, flags;

	/*
	 * This should probably check the transmitter, not the FIFO.
	 * But the TXEMPTY bit करोesn't seem to work unless the TX IRQ is
	 * enabled.
	 */
	spin_lock_irqsave(&up->port.lock, flags);
	tx_fअगरo_bytes = पढ़ोw(up->base + RP2_TX_FIFO_COUNT);
	spin_unlock_irqrestore(&up->port.lock, flags);

	वापस tx_fअगरo_bytes ? 0 : TIOCSER_TEMT;
पूर्ण

अटल अचिन्हित पूर्णांक rp2_uart_get_mctrl(काष्ठा uart_port *port)
अणु
	काष्ठा rp2_uart_port *up = port_to_up(port);
	u32 status;

	status = पढ़ोl(up->base + RP2_CHAN_STAT);
	वापस ((status & RP2_CHAN_STAT_DCD_m) ? TIOCM_CAR : 0) |
	       ((status & RP2_CHAN_STAT_DSR_m) ? TIOCM_DSR : 0) |
	       ((status & RP2_CHAN_STAT_CTS_m) ? TIOCM_CTS : 0) |
	       ((status & RP2_CHAN_STAT_RI_m) ? TIOCM_RI : 0);
पूर्ण

अटल व्योम rp2_uart_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	rp2_rmw(port_to_up(port), RP2_TXRX_CTL,
		RP2_TXRX_CTL_DTR_m | RP2_TXRX_CTL_RTS_m | RP2_TXRX_CTL_LOOP_m,
		((mctrl & TIOCM_DTR) ? RP2_TXRX_CTL_DTR_m : 0) |
		((mctrl & TIOCM_RTS) ? RP2_TXRX_CTL_RTS_m : 0) |
		((mctrl & TIOCM_LOOP) ? RP2_TXRX_CTL_LOOP_m : 0));
पूर्ण

अटल व्योम rp2_uart_start_tx(काष्ठा uart_port *port)
अणु
	rp2_rmw_set(port_to_up(port), RP2_TXRX_CTL, RP2_TXRX_CTL_TXIRQ_m);
पूर्ण

अटल व्योम rp2_uart_stop_tx(काष्ठा uart_port *port)
अणु
	rp2_rmw_clr(port_to_up(port), RP2_TXRX_CTL, RP2_TXRX_CTL_TXIRQ_m);
पूर्ण

अटल व्योम rp2_uart_stop_rx(काष्ठा uart_port *port)
अणु
	rp2_rmw_clr(port_to_up(port), RP2_TXRX_CTL, RP2_TXRX_CTL_RXIRQ_m);
पूर्ण

अटल व्योम rp2_uart_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&port->lock, flags);
	rp2_rmw(port_to_up(port), RP2_TXRX_CTL, RP2_TXRX_CTL_BREAK_m,
		अवरोध_state ? RP2_TXRX_CTL_BREAK_m : 0);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम rp2_uart_enable_ms(काष्ठा uart_port *port)
अणु
	rp2_rmw_set(port_to_up(port), RP2_TXRX_CTL, RP2_TXRX_CTL_MSRIRQ_m);
पूर्ण

अटल व्योम __rp2_uart_set_termios(काष्ठा rp2_uart_port *up,
				   अचिन्हित दीर्घ cfl,
				   अचिन्हित दीर्घ अगरl,
				   अचिन्हित पूर्णांक baud_भाग)
अणु
	/* baud rate भागisor (calculated अन्यथाwhere).  0 = भागide-by-1 */
	ग_लिखोw(baud_भाग - 1, up->base + RP2_BAUD);

	/* data bits and stop bits */
	rp2_rmw(up, RP2_UART_CTL,
		RP2_UART_CTL_STOPBITS_m | RP2_UART_CTL_DATABITS_m,
		((cfl & CSTOPB) ? RP2_UART_CTL_STOPBITS_m : 0) |
		(((cfl & CSIZE) == CS8) ? RP2_UART_CTL_DATABITS_8 : 0) |
		(((cfl & CSIZE) == CS7) ? RP2_UART_CTL_DATABITS_7 : 0) |
		(((cfl & CSIZE) == CS6) ? RP2_UART_CTL_DATABITS_6 : 0) |
		(((cfl & CSIZE) == CS5) ? RP2_UART_CTL_DATABITS_5 : 0));

	/* parity and hardware flow control */
	rp2_rmw(up, RP2_TXRX_CTL,
		RP2_TXRX_CTL_PARENB_m | RP2_TXRX_CTL_nPARODD_m |
		RP2_TXRX_CTL_CMSPAR_m | RP2_TXRX_CTL_DTRFLOW_m |
		RP2_TXRX_CTL_DSRFLOW_m | RP2_TXRX_CTL_RTSFLOW_m |
		RP2_TXRX_CTL_CTSFLOW_m,
		((cfl & PARENB) ? RP2_TXRX_CTL_PARENB_m : 0) |
		((cfl & PARODD) ? 0 : RP2_TXRX_CTL_nPARODD_m) |
		((cfl & CMSPAR) ? RP2_TXRX_CTL_CMSPAR_m : 0) |
		((cfl & CRTSCTS) ? (RP2_TXRX_CTL_RTSFLOW_m |
				    RP2_TXRX_CTL_CTSFLOW_m) : 0));

	/* XON/XOFF software flow control */
	ग_लिखोb((अगरl & IXON) ? RP2_TX_SWFLOW_ena : RP2_TX_SWFLOW_dis,
	       up->ucode + RP2_TX_SWFLOW);
	ग_लिखोb((अगरl & IXOFF) ? RP2_RX_SWFLOW_ena : RP2_RX_SWFLOW_dis,
	       up->ucode + RP2_RX_SWFLOW);
पूर्ण

अटल व्योम rp2_uart_set_termios(काष्ठा uart_port *port,
				 काष्ठा ktermios *new,
				 काष्ठा ktermios *old)
अणु
	काष्ठा rp2_uart_port *up = port_to_up(port);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक baud, baud_भाग;

	baud = uart_get_baud_rate(port, new, old, 0, port->uartclk / 16);
	baud_भाग = uart_get_भागisor(port, baud);

	अगर (tty_termios_baud_rate(new))
		tty_termios_encode_baud_rate(new, baud, baud);

	spin_lock_irqsave(&port->lock, flags);

	/* ignore all अक्षरacters अगर CREAD is not set */
	port->ignore_status_mask = (new->c_cflag & CREAD) ? 0 : RP2_DUMMY_READ;

	__rp2_uart_set_termios(up, new->c_cflag, new->c_अगरlag, baud_भाग);
	uart_update_समयout(port, new->c_cflag, baud);

	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल व्योम rp2_rx_अक्षरs(काष्ठा rp2_uart_port *up)
अणु
	u16 bytes = पढ़ोw(up->base + RP2_RX_FIFO_COUNT);
	काष्ठा tty_port *port = &up->port.state->port;

	क्रम (; bytes != 0; bytes--) अणु
		u32 byte = पढ़ोw(up->base + RP2_DATA_BYTE) | RP2_DUMMY_READ;
		अक्षर ch = byte & 0xff;

		अगर (likely(!(byte & RP2_DATA_BYTE_EXCEPTION_MASK))) अणु
			अगर (!uart_handle_sysrq_अक्षर(&up->port, ch))
				uart_insert_अक्षर(&up->port, byte, 0, ch,
						 TTY_NORMAL);
		पूर्ण अन्यथा अणु
			अक्षर flag = TTY_NORMAL;

			अगर (byte & RP2_DATA_BYTE_BREAK_m)
				flag = TTY_BREAK;
			अन्यथा अगर (byte & RP2_DATA_BYTE_ERR_FRAMING_m)
				flag = TTY_FRAME;
			अन्यथा अगर (byte & RP2_DATA_BYTE_ERR_PARITY_m)
				flag = TTY_PARITY;
			uart_insert_अक्षर(&up->port, byte,
					 RP2_DATA_BYTE_ERR_OVERRUN_m, ch, flag);
		पूर्ण
		up->port.icount.rx++;
	पूर्ण

	tty_flip_buffer_push(port);
पूर्ण

अटल व्योम rp2_tx_अक्षरs(काष्ठा rp2_uart_port *up)
अणु
	u16 max_tx = FIFO_SIZE - पढ़ोw(up->base + RP2_TX_FIFO_COUNT);
	काष्ठा circ_buf *xmit = &up->port.state->xmit;

	अगर (uart_tx_stopped(&up->port)) अणु
		rp2_uart_stop_tx(&up->port);
		वापस;
	पूर्ण

	क्रम (; max_tx != 0; max_tx--) अणु
		अगर (up->port.x_अक्षर) अणु
			ग_लिखोb(up->port.x_अक्षर, up->base + RP2_DATA_BYTE);
			up->port.x_अक्षर = 0;
			up->port.icount.tx++;
			जारी;
		पूर्ण
		अगर (uart_circ_empty(xmit)) अणु
			rp2_uart_stop_tx(&up->port);
			अवरोध;
		पूर्ण
		ग_लिखोb(xmit->buf[xmit->tail], up->base + RP2_DATA_BYTE);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		up->port.icount.tx++;
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(&up->port);
पूर्ण

अटल व्योम rp2_ch_पूर्णांकerrupt(काष्ठा rp2_uart_port *up)
अणु
	u32 status;

	spin_lock(&up->port.lock);

	/*
	 * The IRQ status bits are clear-on-ग_लिखो.  Other status bits in
	 * this रेजिस्टर aren't, so it's harmless to ग_लिखो to them.
	 */
	status = पढ़ोl(up->base + RP2_CHAN_STAT);
	ग_लिखोl(status, up->base + RP2_CHAN_STAT);

	अगर (status & RP2_CHAN_STAT_RXDATA_m)
		rp2_rx_अक्षरs(up);
	अगर (status & RP2_CHAN_STAT_TXEMPTY_m)
		rp2_tx_अक्षरs(up);
	अगर (status & RP2_CHAN_STAT_MS_CHANGED_MASK)
		wake_up_पूर्णांकerruptible(&up->port.state->port.delta_msr_रुको);

	spin_unlock(&up->port.lock);
पूर्ण

अटल पूर्णांक rp2_asic_पूर्णांकerrupt(काष्ठा rp2_card *card, अचिन्हित पूर्णांक asic_id)
अणु
	व्योम __iomem *base = card->bar1 + RP2_ASIC_OFFSET(asic_id);
	पूर्णांक ch, handled = 0;
	अचिन्हित दीर्घ status = पढ़ोl(base + RP2_CH_IRQ_STAT) &
			       ~पढ़ोl(base + RP2_CH_IRQ_MASK);

	क्रम_each_set_bit(ch, &status, PORTS_PER_ASIC) अणु
		rp2_ch_पूर्णांकerrupt(&card->ports[ch]);
		handled++;
	पूर्ण
	वापस handled;
पूर्ण

अटल irqवापस_t rp2_uart_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rp2_card *card = dev_id;
	पूर्णांक handled;

	handled = rp2_asic_पूर्णांकerrupt(card, 0);
	अगर (card->n_ports >= PORTS_PER_ASIC)
		handled += rp2_asic_पूर्णांकerrupt(card, 1);

	वापस handled ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल अंतरभूत व्योम rp2_flush_fअगरos(काष्ठा rp2_uart_port *up)
अणु
	rp2_rmw_set(up, RP2_UART_CTL,
		    RP2_UART_CTL_FLUSH_RX_m | RP2_UART_CTL_FLUSH_TX_m);
	पढ़ोl(up->base + RP2_UART_CTL);
	udelay(10);
	rp2_rmw_clr(up, RP2_UART_CTL,
		    RP2_UART_CTL_FLUSH_RX_m | RP2_UART_CTL_FLUSH_TX_m);
पूर्ण

अटल पूर्णांक rp2_uart_startup(काष्ठा uart_port *port)
अणु
	काष्ठा rp2_uart_port *up = port_to_up(port);

	rp2_flush_fअगरos(up);
	rp2_rmw(up, RP2_TXRX_CTL, RP2_TXRX_CTL_MSRIRQ_m, RP2_TXRX_CTL_RXIRQ_m);
	rp2_rmw(up, RP2_TXRX_CTL, RP2_TXRX_CTL_RX_TRIG_m,
		RP2_TXRX_CTL_RX_TRIG_1);
	rp2_rmw(up, RP2_CHAN_STAT, 0, 0);
	rp2_mask_ch_irq(up, up->idx, 1);

	वापस 0;
पूर्ण

अटल व्योम rp2_uart_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा rp2_uart_port *up = port_to_up(port);
	अचिन्हित दीर्घ flags;

	rp2_uart_अवरोध_ctl(port, 0);

	spin_lock_irqsave(&port->lock, flags);
	rp2_mask_ch_irq(up, up->idx, 0);
	rp2_rmw(up, RP2_CHAN_STAT, 0, 0);
	spin_unlock_irqrestore(&port->lock, flags);
पूर्ण

अटल स्थिर अक्षर *rp2_uart_type(काष्ठा uart_port *port)
अणु
	वापस (port->type == PORT_RP2) ? "RocketPort 2 UART" : शून्य;
पूर्ण

अटल व्योम rp2_uart_release_port(काष्ठा uart_port *port)
अणु
	/* Nothing to release ... */
पूर्ण

अटल पूर्णांक rp2_uart_request_port(काष्ठा uart_port *port)
अणु
	/* UARTs always present */
	वापस 0;
पूर्ण

अटल व्योम rp2_uart_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE)
		port->type = PORT_RP2;
पूर्ण

अटल पूर्णांक rp2_uart_verअगरy_port(काष्ठा uart_port *port,
				   काष्ठा serial_काष्ठा *ser)
अणु
	अगर (ser->type != PORT_UNKNOWN && ser->type != PORT_RP2)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा uart_ops rp2_uart_ops = अणु
	.tx_empty	= rp2_uart_tx_empty,
	.set_mctrl	= rp2_uart_set_mctrl,
	.get_mctrl	= rp2_uart_get_mctrl,
	.stop_tx	= rp2_uart_stop_tx,
	.start_tx	= rp2_uart_start_tx,
	.stop_rx	= rp2_uart_stop_rx,
	.enable_ms	= rp2_uart_enable_ms,
	.अवरोध_ctl	= rp2_uart_अवरोध_ctl,
	.startup	= rp2_uart_startup,
	.shutकरोwn	= rp2_uart_shutकरोwn,
	.set_termios	= rp2_uart_set_termios,
	.type		= rp2_uart_type,
	.release_port	= rp2_uart_release_port,
	.request_port	= rp2_uart_request_port,
	.config_port	= rp2_uart_config_port,
	.verअगरy_port	= rp2_uart_verअगरy_port,
पूर्ण;

अटल व्योम rp2_reset_asic(काष्ठा rp2_card *card, अचिन्हित पूर्णांक asic_id)
अणु
	व्योम __iomem *base = card->bar1 + RP2_ASIC_OFFSET(asic_id);
	u32 clk_cfg;

	ग_लिखोw(1, base + RP2_GLOBAL_CMD);
	पढ़ोw(base + RP2_GLOBAL_CMD);
	msleep(100);
	ग_लिखोl(0, base + RP2_CLK_PRESCALER);

	/* TDM घड़ी configuration */
	clk_cfg = पढ़ोw(base + RP2_ASIC_CFG);
	clk_cfg = (clk_cfg & ~BIT(8)) | BIT(9);
	ग_लिखोw(clk_cfg, base + RP2_ASIC_CFG);

	/* IRQ routing */
	ग_लिखोl(ALL_PORTS_MASK, base + RP2_CH_IRQ_MASK);
	ग_लिखोl(RP2_ASIC_IRQ_EN_m, base + RP2_ASIC_IRQ);
पूर्ण

अटल व्योम rp2_init_card(काष्ठा rp2_card *card)
अणु
	ग_लिखोl(4, card->bar0 + RP2_FPGA_CTL0);
	ग_लिखोl(0, card->bar0 + RP2_FPGA_CTL1);

	rp2_reset_asic(card, 0);
	अगर (card->n_ports >= PORTS_PER_ASIC)
		rp2_reset_asic(card, 1);

	ग_लिखोl(RP2_IRQ_MASK_EN_m, card->bar0 + RP2_IRQ_MASK);
पूर्ण

अटल व्योम rp2_init_port(काष्ठा rp2_uart_port *up, स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक i;

	ग_लिखोl(RP2_UART_CTL_RESET_CH_m, up->base + RP2_UART_CTL);
	पढ़ोl(up->base + RP2_UART_CTL);
	udelay(1);

	ग_लिखोl(0, up->base + RP2_TXRX_CTL);
	ग_लिखोl(0, up->base + RP2_UART_CTL);
	पढ़ोl(up->base + RP2_UART_CTL);
	udelay(1);

	rp2_flush_fअगरos(up);

	क्रम (i = 0; i < min_t(पूर्णांक, fw->size, RP2_UCODE_BYTES); i++)
		ग_लिखोb(fw->data[i], up->ucode + i);

	__rp2_uart_set_termios(up, CS8 | CREAD | CLOCAL, 0, DEFAULT_BAUD_DIV);
	rp2_uart_set_mctrl(&up->port, 0);

	ग_लिखोb(RP2_RX_FIFO_ena, up->ucode + RP2_RX_FIFO);
	rp2_rmw(up, RP2_UART_CTL, RP2_UART_CTL_MODE_m,
		RP2_UART_CTL_XMIT_EN_m | RP2_UART_CTL_MODE_rs232);
	rp2_rmw_set(up, RP2_TXRX_CTL,
		    RP2_TXRX_CTL_TX_EN_m | RP2_TXRX_CTL_RX_EN_m);
पूर्ण

अटल व्योम rp2_हटाओ_ports(काष्ठा rp2_card *card)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < card->initialized_ports; i++)
		uart_हटाओ_one_port(&rp2_uart_driver, &card->ports[i].port);
	card->initialized_ports = 0;
पूर्ण

अटल पूर्णांक rp2_load_firmware(काष्ठा rp2_card *card, स्थिर काष्ठा firmware *fw)
अणु
	resource_माप_प्रकार phys_base;
	पूर्णांक i, rc = 0;

	phys_base = pci_resource_start(card->pdev, 1);

	क्रम (i = 0; i < card->n_ports; i++) अणु
		काष्ठा rp2_uart_port *rp = &card->ports[i];
		काष्ठा uart_port *p;
		पूर्णांक j = (अचिन्हित)i % PORTS_PER_ASIC;

		rp->asic_base = card->bar1;
		rp->base = card->bar1 + RP2_PORT_BASE + j*RP2_PORT_SPACING;
		rp->ucode = card->bar1 + RP2_UCODE_BASE + j*RP2_UCODE_SPACING;
		rp->card = card;
		rp->idx = j;

		p = &rp->port;
		p->line = card->minor_start + i;
		p->dev = &card->pdev->dev;
		p->type = PORT_RP2;
		p->iotype = UPIO_MEM32;
		p->uartclk = UART_CLOCK;
		p->regshअगरt = 2;
		p->fअगरosize = FIFO_SIZE;
		p->ops = &rp2_uart_ops;
		p->irq = card->pdev->irq;
		p->membase = rp->base;
		p->mapbase = phys_base + RP2_PORT_BASE + j*RP2_PORT_SPACING;

		अगर (i >= PORTS_PER_ASIC) अणु
			rp->asic_base += RP2_ASIC_SPACING;
			rp->base += RP2_ASIC_SPACING;
			rp->ucode += RP2_ASIC_SPACING;
			p->mapbase += RP2_ASIC_SPACING;
		पूर्ण

		rp2_init_port(rp, fw);
		rc = uart_add_one_port(&rp2_uart_driver, p);
		अगर (rc) अणु
			dev_err(&card->pdev->dev,
				"error registering port %d: %d\n", i, rc);
			rp2_हटाओ_ports(card);
			अवरोध;
		पूर्ण
		card->initialized_ports++;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक rp2_probe(काष्ठा pci_dev *pdev,
				   स्थिर काष्ठा pci_device_id *id)
अणु
	स्थिर काष्ठा firmware *fw;
	काष्ठा rp2_card *card;
	काष्ठा rp2_uart_port *ports;
	व्योम __iomem * स्थिर *bars;
	पूर्णांक rc;

	card = devm_kzalloc(&pdev->dev, माप(*card), GFP_KERNEL);
	अगर (!card)
		वापस -ENOMEM;
	pci_set_drvdata(pdev, card);
	spin_lock_init(&card->card_lock);

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	rc = pcim_iomap_regions_request_all(pdev, 0x03, DRV_NAME);
	अगर (rc)
		वापस rc;

	bars = pcim_iomap_table(pdev);
	card->bar0 = bars[0];
	card->bar1 = bars[1];
	card->pdev = pdev;

	rp2_decode_cap(id, &card->n_ports, &card->smpte);
	dev_info(&pdev->dev, "found new card with %d ports\n", card->n_ports);

	card->minor_start = rp2_alloc_ports(card->n_ports);
	अगर (card->minor_start < 0) अणु
		dev_err(&pdev->dev,
			"too many ports (try increasing CONFIG_SERIAL_RP2_NR_UARTS)\n");
		वापस -EINVAL;
	पूर्ण

	rp2_init_card(card);

	ports = devm_kसुस्मृति(&pdev->dev, card->n_ports, माप(*ports),
			     GFP_KERNEL);
	अगर (!ports)
		वापस -ENOMEM;
	card->ports = ports;

	rc = request_firmware(&fw, RP2_FW_NAME, &pdev->dev);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "cannot find '%s' firmware image\n",
			RP2_FW_NAME);
		वापस rc;
	पूर्ण

	rc = rp2_load_firmware(card, fw);

	release_firmware(fw);
	अगर (rc < 0)
		वापस rc;

	rc = devm_request_irq(&pdev->dev, pdev->irq, rp2_uart_पूर्णांकerrupt,
			      IRQF_SHARED, DRV_NAME, card);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल व्योम rp2_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा rp2_card *card = pci_get_drvdata(pdev);

	rp2_हटाओ_ports(card);
पूर्ण

अटल स्थिर काष्ठा pci_device_id rp2_pci_tbl[] = अणु

	/* RocketPort अनन्त cards */

	अणु RP_ID(0x0040), RP_CAP(8,  0) पूर्ण, /* INF Octa, RJ45, selectable */
	अणु RP_ID(0x0041), RP_CAP(32, 0) पूर्ण, /* INF 32, ext पूर्णांकerface */
	अणु RP_ID(0x0042), RP_CAP(8,  0) पूर्ण, /* INF Octa, ext पूर्णांकerface */
	अणु RP_ID(0x0043), RP_CAP(16, 0) पूर्ण, /* INF 16, ext पूर्णांकerface */
	अणु RP_ID(0x0044), RP_CAP(4,  0) पूर्ण, /* INF Quad, DB, selectable */
	अणु RP_ID(0x0045), RP_CAP(8,  0) पूर्ण, /* INF Octa, DB, selectable */
	अणु RP_ID(0x0046), RP_CAP(4,  0) पूर्ण, /* INF Quad, ext पूर्णांकerface */
	अणु RP_ID(0x0047), RP_CAP(4,  0) पूर्ण, /* INF Quad, RJ45 */
	अणु RP_ID(0x004a), RP_CAP(4,  0) पूर्ण, /* INF Plus, Quad */
	अणु RP_ID(0x004b), RP_CAP(8,  0) पूर्ण, /* INF Plus, Octa */
	अणु RP_ID(0x004c), RP_CAP(8,  0) पूर्ण, /* INF III, Octa */
	अणु RP_ID(0x004d), RP_CAP(4,  0) पूर्ण, /* INF III, Quad */
	अणु RP_ID(0x004e), RP_CAP(2,  0) पूर्ण, /* INF Plus, 2, RS232 */
	अणु RP_ID(0x004f), RP_CAP(2,  1) पूर्ण, /* INF Plus, 2, SMPTE */
	अणु RP_ID(0x0050), RP_CAP(4,  0) पूर्ण, /* INF Plus, Quad, RJ45 */
	अणु RP_ID(0x0051), RP_CAP(8,  0) पूर्ण, /* INF Plus, Octa, RJ45 */
	अणु RP_ID(0x0052), RP_CAP(8,  1) पूर्ण, /* INF Octa, SMPTE */

	/* RocketPort EXPRESS cards */

	अणु RP_ID(0x0060), RP_CAP(8,  0) पूर्ण, /* EXP Octa, RJ45, selectable */
	अणु RP_ID(0x0061), RP_CAP(32, 0) पूर्ण, /* EXP 32, ext पूर्णांकerface */
	अणु RP_ID(0x0062), RP_CAP(8,  0) पूर्ण, /* EXP Octa, ext पूर्णांकerface */
	अणु RP_ID(0x0063), RP_CAP(16, 0) पूर्ण, /* EXP 16, ext पूर्णांकerface */
	अणु RP_ID(0x0064), RP_CAP(4,  0) पूर्ण, /* EXP Quad, DB, selectable */
	अणु RP_ID(0x0065), RP_CAP(8,  0) पूर्ण, /* EXP Octa, DB, selectable */
	अणु RP_ID(0x0066), RP_CAP(4,  0) पूर्ण, /* EXP Quad, ext पूर्णांकerface */
	अणु RP_ID(0x0067), RP_CAP(4,  0) पूर्ण, /* EXP Quad, RJ45 */
	अणु RP_ID(0x0068), RP_CAP(8,  0) पूर्ण, /* EXP Octa, RJ11 */
	अणु RP_ID(0x0072), RP_CAP(8,  1) पूर्ण, /* EXP Octa, SMPTE */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, rp2_pci_tbl);

अटल काष्ठा pci_driver rp2_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= rp2_pci_tbl,
	.probe		= rp2_probe,
	.हटाओ		= rp2_हटाओ,
पूर्ण;

अटल पूर्णांक __init rp2_uart_init(व्योम)
अणु
	पूर्णांक rc;

	rc = uart_रेजिस्टर_driver(&rp2_uart_driver);
	अगर (rc)
		वापस rc;

	rc = pci_रेजिस्टर_driver(&rp2_pci_driver);
	अगर (rc) अणु
		uart_unरेजिस्टर_driver(&rp2_uart_driver);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास rp2_uart_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&rp2_pci_driver);
	uart_unरेजिस्टर_driver(&rp2_uart_driver);
पूर्ण

module_init(rp2_uart_init);
module_निकास(rp2_uart_निकास);

MODULE_DESCRIPTION("Comtrol RocketPort EXPRESS/INFINITY driver");
MODULE_AUTHOR("Kevin Cernekee <cernekee@gmail.com>");
MODULE_LICENSE("GPL v2");
MODULE_FIRMWARE(RP2_FW_NAME);
