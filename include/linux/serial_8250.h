<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  linux/include/linux/serial_8250.h
 *
 *  Copyright (C) 2004 Russell King
 */
#अगर_अघोषित _LINUX_SERIAL_8250_H
#घोषणा _LINUX_SERIAL_8250_H

#समावेश <linux/serial_core.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/platक्रमm_device.h>

/*
 * This is the platक्रमm device platक्रमm_data काष्ठाure
 */
काष्ठा plat_serial8250_port अणु
	अचिन्हित दीर्घ	iobase;		/* io base address */
	व्योम __iomem	*membase;	/* ioremap cookie or शून्य */
	resource_माप_प्रकार	mapbase;	/* resource base */
	अचिन्हित पूर्णांक	irq;		/* पूर्णांकerrupt number */
	अचिन्हित दीर्घ	irqflags;	/* request_irq flags */
	अचिन्हित पूर्णांक	uartclk;	/* UART घड़ी rate */
	व्योम            *निजी_data;
	अचिन्हित अक्षर	regshअगरt;	/* रेजिस्टर shअगरt */
	अचिन्हित अक्षर	iotype;		/* UPIO_* */
	अचिन्हित अक्षर	hub6;
	अचिन्हित अक्षर	has_sysrq;	/* supports magic SysRq */
	upf_t		flags;		/* UPF_* flags */
	अचिन्हित पूर्णांक	type;		/* If UPF_FIXED_TYPE */
	अचिन्हित पूर्णांक	(*serial_in)(काष्ठा uart_port *, पूर्णांक);
	व्योम		(*serial_out)(काष्ठा uart_port *, पूर्णांक, पूर्णांक);
	व्योम		(*set_termios)(काष्ठा uart_port *,
			               काष्ठा ktermios *new,
			               काष्ठा ktermios *old);
	व्योम		(*set_ldisc)(काष्ठा uart_port *,
				     काष्ठा ktermios *);
	अचिन्हित पूर्णांक	(*get_mctrl)(काष्ठा uart_port *);
	पूर्णांक		(*handle_irq)(काष्ठा uart_port *);
	व्योम		(*pm)(काष्ठा uart_port *, अचिन्हित पूर्णांक state,
			      अचिन्हित old);
	व्योम		(*handle_अवरोध)(काष्ठा uart_port *);
पूर्ण;

/*
 * Allocate 8250 platक्रमm device IDs.  Nothing is implied by
 * the numbering here, except क्रम the legacy entry being -1.
 */
क्रमागत अणु
	PLAT8250_DEV_LEGACY = -1,
	PLAT8250_DEV_PLATFORM,
	PLAT8250_DEV_PLATFORM1,
	PLAT8250_DEV_PLATFORM2,
	PLAT8250_DEV_FOURPORT,
	PLAT8250_DEV_ACCENT,
	PLAT8250_DEV_BOCA,
	PLAT8250_DEV_EXAR_ST16C554,
	PLAT8250_DEV_HUB6,
	PLAT8250_DEV_AU1X00,
	PLAT8250_DEV_SM501,
पूर्ण;

काष्ठा uart_8250_dma;
काष्ठा uart_8250_port;

/**
 * 8250 core driver operations
 *
 * @setup_irq()		Setup irq handling. The universal 8250 driver links this
 *			port to the irq chain. Other drivers may @request_irq().
 * @release_irq()	Unकरो irq handling. The universal 8250 driver unlinks
 *			the port from the irq chain.
 */
काष्ठा uart_8250_ops अणु
	पूर्णांक		(*setup_irq)(काष्ठा uart_8250_port *);
	व्योम		(*release_irq)(काष्ठा uart_8250_port *);
पूर्ण;

काष्ठा uart_8250_em485 अणु
	काष्ठा hrसमयr		start_tx_समयr; /* "rs485 start tx" समयr */
	काष्ठा hrसमयr		stop_tx_समयr;  /* "rs485 stop tx" समयr */
	काष्ठा hrसमयr		*active_समयr;  /* poपूर्णांकer to active समयr */
	काष्ठा uart_8250_port	*port;          /* क्रम hrसमयr callbacks */
	अचिन्हित पूर्णांक		tx_stopped:1;	/* tx is currently stopped */
पूर्ण;

/*
 * This should be used by drivers which want to रेजिस्टर
 * their own 8250 ports without रेजिस्टरing their own
 * platक्रमm device.  Using these will make your driver
 * dependent on the 8250 driver.
 */

काष्ठा uart_8250_port अणु
	काष्ठा uart_port	port;
	काष्ठा समयr_list	समयr;		/* "no irq" समयr */
	काष्ठा list_head	list;		/* ports on this IRQ */
	u32			capabilities;	/* port capabilities */
	अचिन्हित लघु		bugs;		/* port bugs */
	bool			fअगरo_bug;	/* min RX trigger अगर enabled */
	अचिन्हित पूर्णांक		tx_loadsz;	/* transmit fअगरo load size */
	अचिन्हित अक्षर		acr;
	अचिन्हित अक्षर		fcr;
	अचिन्हित अक्षर		ier;
	अचिन्हित अक्षर		lcr;
	अचिन्हित अक्षर		mcr;
	अचिन्हित अक्षर		mcr_mask;	/* mask of user bits */
	अचिन्हित अक्षर		mcr_क्रमce;	/* mask of क्रमced bits */
	अचिन्हित अक्षर		cur_iotype;	/* Running I/O type */
	अचिन्हित पूर्णांक		rpm_tx_active;
	अचिन्हित अक्षर		canary;		/* non-zero during प्रणाली sleep
						 *   अगर no_console_suspend
						 */
	अचिन्हित अक्षर		probe;
	काष्ठा mctrl_gpios	*gpios;
#घोषणा UART_PROBE_RSA	(1 << 0)

	/*
	 * Some bits in रेजिस्टरs are cleared on a पढ़ो, so they must
	 * be saved whenever the रेजिस्टर is पढ़ो but the bits will not
	 * be immediately processed.
	 */
#घोषणा LSR_SAVE_FLAGS UART_LSR_BRK_ERROR_BITS
	अचिन्हित अक्षर		lsr_saved_flags;
#घोषणा MSR_SAVE_FLAGS UART_MSR_ANY_DELTA
	अचिन्हित अक्षर		msr_saved_flags;

	काष्ठा uart_8250_dma	*dma;
	स्थिर काष्ठा uart_8250_ops *ops;

	/* 8250 specअगरic callbacks */
	पूर्णांक			(*dl_पढ़ो)(काष्ठा uart_8250_port *);
	व्योम			(*dl_ग_लिखो)(काष्ठा uart_8250_port *, पूर्णांक);

	काष्ठा uart_8250_em485 *em485;
	व्योम			(*rs485_start_tx)(काष्ठा uart_8250_port *);
	व्योम			(*rs485_stop_tx)(काष्ठा uart_8250_port *);

	/* Serial port overrun backoff */
	काष्ठा delayed_work overrun_backoff;
	u32 overrun_backoff_समय_ms;
पूर्ण;

अटल अंतरभूत काष्ठा uart_8250_port *up_to_u8250p(काष्ठा uart_port *up)
अणु
	वापस container_of(up, काष्ठा uart_8250_port, port);
पूर्ण

पूर्णांक serial8250_रेजिस्टर_8250_port(काष्ठा uart_8250_port *);
व्योम serial8250_unरेजिस्टर_port(पूर्णांक line);
व्योम serial8250_suspend_port(पूर्णांक line);
व्योम serial8250_resume_port(पूर्णांक line);

बाह्य पूर्णांक early_serial_setup(काष्ठा uart_port *port);

बाह्य पूर्णांक early_serial8250_setup(काष्ठा earlycon_device *device,
					 स्थिर अक्षर *options);
बाह्य व्योम serial8250_update_uartclk(काष्ठा uart_port *port,
				      अचिन्हित पूर्णांक uartclk);
बाह्य व्योम serial8250_करो_set_termios(काष्ठा uart_port *port,
		काष्ठा ktermios *termios, काष्ठा ktermios *old);
बाह्य व्योम serial8250_करो_set_ldisc(काष्ठा uart_port *port,
				    काष्ठा ktermios *termios);
बाह्य अचिन्हित पूर्णांक serial8250_करो_get_mctrl(काष्ठा uart_port *port);
बाह्य पूर्णांक serial8250_करो_startup(काष्ठा uart_port *port);
बाह्य व्योम serial8250_करो_shutकरोwn(काष्ठा uart_port *port);
बाह्य व्योम serial8250_करो_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state,
			     अचिन्हित पूर्णांक oldstate);
बाह्य व्योम serial8250_करो_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl);
बाह्य व्योम serial8250_करो_set_भागisor(काष्ठा uart_port *port, अचिन्हित पूर्णांक baud,
				      अचिन्हित पूर्णांक quot,
				      अचिन्हित पूर्णांक quot_frac);
बाह्य पूर्णांक fsl8250_handle_irq(काष्ठा uart_port *port);
पूर्णांक serial8250_handle_irq(काष्ठा uart_port *port, अचिन्हित पूर्णांक iir);
अचिन्हित अक्षर serial8250_rx_अक्षरs(काष्ठा uart_8250_port *up, अचिन्हित अक्षर lsr);
व्योम serial8250_पढ़ो_अक्षर(काष्ठा uart_8250_port *up, अचिन्हित अक्षर lsr);
व्योम serial8250_tx_अक्षरs(काष्ठा uart_8250_port *up);
अचिन्हित पूर्णांक serial8250_modem_status(काष्ठा uart_8250_port *up);
व्योम serial8250_init_port(काष्ठा uart_8250_port *up);
व्योम serial8250_set_शेषs(काष्ठा uart_8250_port *up);
व्योम serial8250_console_ग_लिखो(काष्ठा uart_8250_port *up, स्थिर अक्षर *s,
			      अचिन्हित पूर्णांक count);
पूर्णांक serial8250_console_setup(काष्ठा uart_port *port, अक्षर *options, bool probe);
पूर्णांक serial8250_console_निकास(काष्ठा uart_port *port);

बाह्य व्योम serial8250_set_isa_configurator(व्योम (*v)
					(पूर्णांक port, काष्ठा uart_port *up,
						u32 *capabilities));

#अगर_घोषित CONFIG_SERIAL_8250_RT288X
अचिन्हित पूर्णांक au_serial_in(काष्ठा uart_port *p, पूर्णांक offset);
व्योम au_serial_out(काष्ठा uart_port *p, पूर्णांक offset, पूर्णांक value);
#पूर्ण_अगर

#पूर्ण_अगर
