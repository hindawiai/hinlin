<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 *  Driver क्रम 8250/16550-type serial ports
 *
 *  Based on drivers/अक्षर/serial.c, by Linus Torvalds, Theoकरोre Ts'o.
 *
 *  Copyright (C) 2001 Russell King.
 */

#समावेश <linux/bits.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/dmaengine.h>

#समावेश "../serial_mctrl_gpio.h"

काष्ठा uart_8250_dma अणु
	पूर्णांक (*tx_dma)(काष्ठा uart_8250_port *p);
	पूर्णांक (*rx_dma)(काष्ठा uart_8250_port *p);

	/* Filter function */
	dma_filter_fn		fn;
	/* Parameter to the filter function */
	व्योम			*rx_param;
	व्योम			*tx_param;

	काष्ठा dma_slave_config	rxconf;
	काष्ठा dma_slave_config	txconf;

	काष्ठा dma_chan		*rxchan;
	काष्ठा dma_chan		*txchan;

	/* Device address base क्रम DMA operations */
	phys_addr_t		rx_dma_addr;
	phys_addr_t		tx_dma_addr;

	/* DMA address of the buffer in memory */
	dma_addr_t		rx_addr;
	dma_addr_t		tx_addr;

	dma_cookie_t		rx_cookie;
	dma_cookie_t		tx_cookie;

	व्योम			*rx_buf;

	माप_प्रकार			rx_size;
	माप_प्रकार			tx_size;

	अचिन्हित अक्षर		tx_running;
	अचिन्हित अक्षर		tx_err;
	अचिन्हित अक्षर		rx_running;
पूर्ण;

काष्ठा old_serial_port अणु
	अचिन्हित पूर्णांक uart;
	अचिन्हित पूर्णांक baud_base;
	अचिन्हित पूर्णांक port;
	अचिन्हित पूर्णांक irq;
	upf_t        flags;
	अचिन्हित अक्षर io_type;
	अचिन्हित अक्षर __iomem *iomem_base;
	अचिन्हित लघु iomem_reg_shअगरt;
पूर्ण;

काष्ठा serial8250_config अणु
	स्थिर अक्षर	*name;
	अचिन्हित लघु	fअगरo_size;
	अचिन्हित लघु	tx_loadsz;
	अचिन्हित अक्षर	fcr;
	अचिन्हित अक्षर	rxtrig_bytes[UART_FCR_R_TRIG_MAX_STATE];
	अचिन्हित पूर्णांक	flags;
पूर्ण;

#घोषणा UART_CAP_FIFO	BIT(8)	/* UART has FIFO */
#घोषणा UART_CAP_EFR	BIT(9)	/* UART has EFR */
#घोषणा UART_CAP_SLEEP	BIT(10)	/* UART has IER sleep */
#घोषणा UART_CAP_AFE	BIT(11)	/* MCR-based hw flow control */
#घोषणा UART_CAP_UUE	BIT(12)	/* UART needs IER bit 6 set (Xscale) */
#घोषणा UART_CAP_RTOIE	BIT(13)	/* UART needs IER bit 4 set (Xscale, Tegra) */
#घोषणा UART_CAP_HFIFO	BIT(14)	/* UART has a "hidden" FIFO */
#घोषणा UART_CAP_RPM	BIT(15)	/* Runसमय PM is active जबतक idle */
#घोषणा UART_CAP_IRDA	BIT(16)	/* UART supports IrDA line discipline */
#घोषणा UART_CAP_MINI	BIT(17)	/* Mini UART on BCM283X family lacks:
					 * STOP PARITY EPAR SPAR WLEN5 WLEN6
					 */

#घोषणा UART_BUG_QUOT	BIT(0)	/* UART has buggy quot LSB */
#घोषणा UART_BUG_TXEN	BIT(1)	/* UART has buggy TX IIR status */
#घोषणा UART_BUG_NOMSR	BIT(2)	/* UART has buggy MSR status bits (Au1x00) */
#घोषणा UART_BUG_THRE	BIT(3)	/* UART has buggy THRE reनिश्चितion */
#घोषणा UART_BUG_PARITY	BIT(4)	/* UART mishandles parity अगर FIFO enabled */
#घोषणा UART_BUG_TXRACE	BIT(5)	/* UART Tx fails to set remote DR */


#अगर_घोषित CONFIG_SERIAL_8250_SHARE_IRQ
#घोषणा SERIAL8250_SHARE_IRQS 1
#अन्यथा
#घोषणा SERIAL8250_SHARE_IRQS 0
#पूर्ण_अगर

#घोषणा SERIAL8250_PORT_FLAGS(_base, _irq, _flags)		\
	अणु							\
		.iobase		= _base,			\
		.irq		= _irq,				\
		.uartclk	= 1843200,			\
		.iotype		= UPIO_PORT,			\
		.flags		= UPF_BOOT_AUTOCONF | (_flags),	\
	पूर्ण

#घोषणा SERIAL8250_PORT(_base, _irq) SERIAL8250_PORT_FLAGS(_base, _irq, 0)


अटल अंतरभूत पूर्णांक serial_in(काष्ठा uart_8250_port *up, पूर्णांक offset)
अणु
	वापस up->port.serial_in(&up->port, offset);
पूर्ण

अटल अंतरभूत व्योम serial_out(काष्ठा uart_8250_port *up, पूर्णांक offset, पूर्णांक value)
अणु
	up->port.serial_out(&up->port, offset, value);
पूर्ण

व्योम serial8250_clear_and_reinit_fअगरos(काष्ठा uart_8250_port *p);

अटल अंतरभूत पूर्णांक serial_dl_पढ़ो(काष्ठा uart_8250_port *up)
अणु
	वापस up->dl_पढ़ो(up);
पूर्ण

अटल अंतरभूत व्योम serial_dl_ग_लिखो(काष्ठा uart_8250_port *up, पूर्णांक value)
अणु
	up->dl_ग_लिखो(up, value);
पूर्ण

अटल अंतरभूत bool serial8250_set_THRI(काष्ठा uart_8250_port *up)
अणु
	अगर (up->ier & UART_IER_THRI)
		वापस false;
	up->ier |= UART_IER_THRI;
	serial_out(up, UART_IER, up->ier);
	वापस true;
पूर्ण

अटल अंतरभूत bool serial8250_clear_THRI(काष्ठा uart_8250_port *up)
अणु
	अगर (!(up->ier & UART_IER_THRI))
		वापस false;
	up->ier &= ~UART_IER_THRI;
	serial_out(up, UART_IER, up->ier);
	वापस true;
पूर्ण

काष्ठा uart_8250_port *serial8250_get_port(पूर्णांक line);

व्योम serial8250_rpm_get(काष्ठा uart_8250_port *p);
व्योम serial8250_rpm_put(काष्ठा uart_8250_port *p);

व्योम serial8250_rpm_get_tx(काष्ठा uart_8250_port *p);
व्योम serial8250_rpm_put_tx(काष्ठा uart_8250_port *p);

पूर्णांक serial8250_em485_config(काष्ठा uart_port *port, काष्ठा serial_rs485 *rs485);
व्योम serial8250_em485_start_tx(काष्ठा uart_8250_port *p);
व्योम serial8250_em485_stop_tx(काष्ठा uart_8250_port *p);
व्योम serial8250_em485_destroy(काष्ठा uart_8250_port *p);

/* MCR <-> TIOCM conversion */
अटल अंतरभूत पूर्णांक serial8250_TIOCM_to_MCR(पूर्णांक tiocm)
अणु
	पूर्णांक mcr = 0;

	अगर (tiocm & TIOCM_RTS)
		mcr |= UART_MCR_RTS;
	अगर (tiocm & TIOCM_DTR)
		mcr |= UART_MCR_DTR;
	अगर (tiocm & TIOCM_OUT1)
		mcr |= UART_MCR_OUT1;
	अगर (tiocm & TIOCM_OUT2)
		mcr |= UART_MCR_OUT2;
	अगर (tiocm & TIOCM_LOOP)
		mcr |= UART_MCR_LOOP;

	वापस mcr;
पूर्ण

अटल अंतरभूत पूर्णांक serial8250_MCR_to_TIOCM(पूर्णांक mcr)
अणु
	पूर्णांक tiocm = 0;

	अगर (mcr & UART_MCR_RTS)
		tiocm |= TIOCM_RTS;
	अगर (mcr & UART_MCR_DTR)
		tiocm |= TIOCM_DTR;
	अगर (mcr & UART_MCR_OUT1)
		tiocm |= TIOCM_OUT1;
	अगर (mcr & UART_MCR_OUT2)
		tiocm |= TIOCM_OUT2;
	अगर (mcr & UART_MCR_LOOP)
		tiocm |= TIOCM_LOOP;

	वापस tiocm;
पूर्ण

/* MSR <-> TIOCM conversion */
अटल अंतरभूत पूर्णांक serial8250_MSR_to_TIOCM(पूर्णांक msr)
अणु
	पूर्णांक tiocm = 0;

	अगर (msr & UART_MSR_DCD)
		tiocm |= TIOCM_CAR;
	अगर (msr & UART_MSR_RI)
		tiocm |= TIOCM_RNG;
	अगर (msr & UART_MSR_DSR)
		tiocm |= TIOCM_DSR;
	अगर (msr & UART_MSR_CTS)
		tiocm |= TIOCM_CTS;

	वापस tiocm;
पूर्ण

अटल अंतरभूत व्योम serial8250_out_MCR(काष्ठा uart_8250_port *up, पूर्णांक value)
अणु
	serial_out(up, UART_MCR, value);

	अगर (up->gpios)
		mctrl_gpio_set(up->gpios, serial8250_MCR_to_TIOCM(value));
पूर्ण

अटल अंतरभूत पूर्णांक serial8250_in_MCR(काष्ठा uart_8250_port *up)
अणु
	पूर्णांक mctrl;

	mctrl = serial_in(up, UART_MCR);

	अगर (up->gpios) अणु
		अचिन्हित पूर्णांक mctrl_gpio = 0;

		mctrl_gpio = mctrl_gpio_get_outमाला_दो(up->gpios, &mctrl_gpio);
		mctrl |= serial8250_TIOCM_to_MCR(mctrl_gpio);
	पूर्ण

	वापस mctrl;
पूर्ण

#अगर defined(__alpha__) && !defined(CONFIG_PCI)
/*
 * Digital did something really horribly wrong with the OUT1 and OUT2
 * lines on at least some ALPHA's.  The failure mode is that अगर either
 * is cleared, the machine locks up with endless पूर्णांकerrupts.
 */
#घोषणा ALPHA_KLUDGE_MCR  (UART_MCR_OUT2 | UART_MCR_OUT1)
#अन्यथा
#घोषणा ALPHA_KLUDGE_MCR 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_SERIAL_8250_PNP
पूर्णांक serial8250_pnp_init(व्योम);
व्योम serial8250_pnp_निकास(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक serial8250_pnp_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम serial8250_pnp_निकास(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SERIAL_8250_FINTEK
पूर्णांक fपूर्णांकek_8250_probe(काष्ठा uart_8250_port *uart);
#अन्यथा
अटल अंतरभूत पूर्णांक fपूर्णांकek_8250_probe(काष्ठा uart_8250_port *uart) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP1
अटल अंतरभूत पूर्णांक is_omap1_8250(काष्ठा uart_8250_port *pt)
अणु
	पूर्णांक res;

	चयन (pt->port.mapbase) अणु
	हाल OMAP1_UART1_BASE:
	हाल OMAP1_UART2_BASE:
	हाल OMAP1_UART3_BASE:
		res = 1;
		अवरोध;
	शेष:
		res = 0;
		अवरोध;
	पूर्ण

	वापस res;
पूर्ण

अटल अंतरभूत पूर्णांक is_omap1510_8250(काष्ठा uart_8250_port *pt)
अणु
	अगर (!cpu_is_omap1510())
		वापस 0;

	वापस is_omap1_8250(pt);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक is_omap1_8250(काष्ठा uart_8250_port *pt)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक is_omap1510_8250(काष्ठा uart_8250_port *pt)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SERIAL_8250_DMA
बाह्य पूर्णांक serial8250_tx_dma(काष्ठा uart_8250_port *);
बाह्य पूर्णांक serial8250_rx_dma(काष्ठा uart_8250_port *);
बाह्य व्योम serial8250_rx_dma_flush(काष्ठा uart_8250_port *);
बाह्य पूर्णांक serial8250_request_dma(काष्ठा uart_8250_port *);
बाह्य व्योम serial8250_release_dma(काष्ठा uart_8250_port *);
#अन्यथा
अटल अंतरभूत पूर्णांक serial8250_tx_dma(काष्ठा uart_8250_port *p)
अणु
	वापस -1;
पूर्ण
अटल अंतरभूत पूर्णांक serial8250_rx_dma(काष्ठा uart_8250_port *p)
अणु
	वापस -1;
पूर्ण
अटल अंतरभूत व्योम serial8250_rx_dma_flush(काष्ठा uart_8250_port *p) अणु पूर्ण
अटल अंतरभूत पूर्णांक serial8250_request_dma(काष्ठा uart_8250_port *p)
अणु
	वापस -1;
पूर्ण
अटल अंतरभूत व्योम serial8250_release_dma(काष्ठा uart_8250_port *p) अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक ns16550a_जाओ_highspeed(काष्ठा uart_8250_port *up)
अणु
	अचिन्हित अक्षर status;

	status = serial_in(up, 0x04); /* EXCR2 */
#घोषणा PRESL(x) ((x) & 0x30)
	अगर (PRESL(status) == 0x10) अणु
		/* alपढ़ोy in high speed mode */
		वापस 0;
	पूर्ण अन्यथा अणु
		status &= ~0xB0; /* Disable LOCK, mask out PRESL[01] */
		status |= 0x10;  /* 1.625 भागisor क्रम baud_base --> 921600 */
		serial_out(up, 0x04, status);
	पूर्ण
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक serial_index(काष्ठा uart_port *port)
अणु
	वापस port->minor - 64;
पूर्ण
