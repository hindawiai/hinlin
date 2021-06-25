<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  linux/drivers/अक्षर/serial_core.h
 *
 *  Copyright (C) 2000 Deep Blue Solutions Ltd.
 */
#अगर_अघोषित LINUX_SERIAL_CORE_H
#घोषणा LINUX_SERIAL_CORE_H

#समावेश <linux/bitops.h>
#समावेश <linux/compiler.h>
#समावेश <linux/console.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sched.h>
#समावेश <linux/tty.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sysrq.h>
#समावेश <uapi/linux/serial_core.h>

#अगर_घोषित CONFIG_SERIAL_CORE_CONSOLE
#घोषणा uart_console(port) \
	((port)->cons && (port)->cons->index == (port)->line)
#अन्यथा
#घोषणा uart_console(port)      (अणु (व्योम)port; 0; पूर्ण)
#पूर्ण_अगर

काष्ठा uart_port;
काष्ठा serial_काष्ठा;
काष्ठा device;
काष्ठा gpio_desc;

/*
 * This काष्ठाure describes all the operations that can be करोne on the
 * physical hardware.  See Documentation/driver-api/serial/driver.rst क्रम details.
 */
काष्ठा uart_ops अणु
	अचिन्हित पूर्णांक	(*tx_empty)(काष्ठा uart_port *);
	व्योम		(*set_mctrl)(काष्ठा uart_port *, अचिन्हित पूर्णांक mctrl);
	अचिन्हित पूर्णांक	(*get_mctrl)(काष्ठा uart_port *);
	व्योम		(*stop_tx)(काष्ठा uart_port *);
	व्योम		(*start_tx)(काष्ठा uart_port *);
	व्योम		(*throttle)(काष्ठा uart_port *);
	व्योम		(*unthrottle)(काष्ठा uart_port *);
	व्योम		(*send_xअक्षर)(काष्ठा uart_port *, अक्षर ch);
	व्योम		(*stop_rx)(काष्ठा uart_port *);
	व्योम		(*enable_ms)(काष्ठा uart_port *);
	व्योम		(*अवरोध_ctl)(काष्ठा uart_port *, पूर्णांक ctl);
	पूर्णांक		(*startup)(काष्ठा uart_port *);
	व्योम		(*shutकरोwn)(काष्ठा uart_port *);
	व्योम		(*flush_buffer)(काष्ठा uart_port *);
	व्योम		(*set_termios)(काष्ठा uart_port *, काष्ठा ktermios *new,
				       काष्ठा ktermios *old);
	व्योम		(*set_ldisc)(काष्ठा uart_port *, काष्ठा ktermios *);
	व्योम		(*pm)(काष्ठा uart_port *, अचिन्हित पूर्णांक state,
			      अचिन्हित पूर्णांक oldstate);

	/*
	 * Return a string describing the type of the port
	 */
	स्थिर अक्षर	*(*type)(काष्ठा uart_port *);

	/*
	 * Release IO and memory resources used by the port.
	 * This includes iounmap अगर necessary.
	 */
	व्योम		(*release_port)(काष्ठा uart_port *);

	/*
	 * Request IO and memory resources used by the port.
	 * This includes iomapping the port अगर necessary.
	 */
	पूर्णांक		(*request_port)(काष्ठा uart_port *);
	व्योम		(*config_port)(काष्ठा uart_port *, पूर्णांक);
	पूर्णांक		(*verअगरy_port)(काष्ठा uart_port *, काष्ठा serial_काष्ठा *);
	पूर्णांक		(*ioctl)(काष्ठा uart_port *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
#अगर_घोषित CONFIG_CONSOLE_POLL
	पूर्णांक		(*poll_init)(काष्ठा uart_port *);
	व्योम		(*poll_put_अक्षर)(काष्ठा uart_port *, अचिन्हित अक्षर);
	पूर्णांक		(*poll_get_अक्षर)(काष्ठा uart_port *);
#पूर्ण_अगर
पूर्ण;

#घोषणा NO_POLL_CHAR		0x00ff0000
#घोषणा UART_CONFIG_TYPE	(1 << 0)
#घोषणा UART_CONFIG_IRQ		(1 << 1)

काष्ठा uart_icount अणु
	__u32	cts;
	__u32	dsr;
	__u32	rng;
	__u32	dcd;
	__u32	rx;
	__u32	tx;
	__u32	frame;
	__u32	overrun;
	__u32	parity;
	__u32	brk;
	__u32	buf_overrun;
पूर्ण;

प्रकार अचिन्हित पूर्णांक __bitwise upf_t;
प्रकार अचिन्हित पूर्णांक __bitwise upstat_t;

काष्ठा uart_port अणु
	spinlock_t		lock;			/* port lock */
	अचिन्हित दीर्घ		iobase;			/* in/out[bwl] */
	अचिन्हित अक्षर __iomem	*membase;		/* पढ़ो/ग_लिखो[bwl] */
	अचिन्हित पूर्णांक		(*serial_in)(काष्ठा uart_port *, पूर्णांक);
	व्योम			(*serial_out)(काष्ठा uart_port *, पूर्णांक, पूर्णांक);
	व्योम			(*set_termios)(काष्ठा uart_port *,
				               काष्ठा ktermios *new,
				               काष्ठा ktermios *old);
	व्योम			(*set_ldisc)(काष्ठा uart_port *,
					     काष्ठा ktermios *);
	अचिन्हित पूर्णांक		(*get_mctrl)(काष्ठा uart_port *);
	व्योम			(*set_mctrl)(काष्ठा uart_port *, अचिन्हित पूर्णांक);
	अचिन्हित पूर्णांक		(*get_भागisor)(काष्ठा uart_port *,
					       अचिन्हित पूर्णांक baud,
					       अचिन्हित पूर्णांक *frac);
	व्योम			(*set_भागisor)(काष्ठा uart_port *,
					       अचिन्हित पूर्णांक baud,
					       अचिन्हित पूर्णांक quot,
					       अचिन्हित पूर्णांक quot_frac);
	पूर्णांक			(*startup)(काष्ठा uart_port *port);
	व्योम			(*shutकरोwn)(काष्ठा uart_port *port);
	व्योम			(*throttle)(काष्ठा uart_port *port);
	व्योम			(*unthrottle)(काष्ठा uart_port *port);
	पूर्णांक			(*handle_irq)(काष्ठा uart_port *);
	व्योम			(*pm)(काष्ठा uart_port *, अचिन्हित पूर्णांक state,
				      अचिन्हित पूर्णांक old);
	व्योम			(*handle_अवरोध)(काष्ठा uart_port *);
	पूर्णांक			(*rs485_config)(काष्ठा uart_port *,
						काष्ठा serial_rs485 *rs485);
	पूर्णांक			(*iso7816_config)(काष्ठा uart_port *,
						  काष्ठा serial_iso7816 *iso7816);
	अचिन्हित पूर्णांक		irq;			/* irq number */
	अचिन्हित दीर्घ		irqflags;		/* irq flags  */
	अचिन्हित पूर्णांक		uartclk;		/* base uart घड़ी */
	अचिन्हित पूर्णांक		fअगरosize;		/* tx fअगरo size */
	अचिन्हित अक्षर		x_अक्षर;			/* xon/xoff अक्षर */
	अचिन्हित अक्षर		regshअगरt;		/* reg offset shअगरt */
	अचिन्हित अक्षर		iotype;			/* io access style */
	अचिन्हित अक्षर		quirks;			/* पूर्णांकernal quirks */

#घोषणा UPIO_PORT		(SERIAL_IO_PORT)	/* 8b I/O port access */
#घोषणा UPIO_HUB6		(SERIAL_IO_HUB6)	/* Hub6 ISA card */
#घोषणा UPIO_MEM		(SERIAL_IO_MEM)		/* driver-specअगरic */
#घोषणा UPIO_MEM32		(SERIAL_IO_MEM32)	/* 32b little endian */
#घोषणा UPIO_AU			(SERIAL_IO_AU)		/* Au1x00 and RT288x type IO */
#घोषणा UPIO_TSI		(SERIAL_IO_TSI)		/* Tsi108/109 type IO */
#घोषणा UPIO_MEM32BE		(SERIAL_IO_MEM32BE)	/* 32b big endian */
#घोषणा UPIO_MEM16		(SERIAL_IO_MEM16)	/* 16b little endian */

	/* quirks must be updated जबतक holding port mutex */
#घोषणा UPQ_NO_TXEN_TEST	BIT(0)

	अचिन्हित पूर्णांक		पढ़ो_status_mask;	/* driver specअगरic */
	अचिन्हित पूर्णांक		ignore_status_mask;	/* driver specअगरic */
	काष्ठा uart_state	*state;			/* poपूर्णांकer to parent state */
	काष्ठा uart_icount	icount;			/* statistics */

	काष्ठा console		*cons;			/* काष्ठा console, अगर any */
	/* flags must be updated जबतक holding port mutex */
	upf_t			flags;

	/*
	 * These flags must be equivalent to the flags defined in
	 * include/uapi/linux/tty_flags.h which are the userspace definitions
	 * asचिन्हित from the serial_काष्ठा flags in uart_set_info()
	 * [क्रम bit definitions in the UPF_CHANGE_MASK]
	 *
	 * Bits [0..UPF_LAST_USER] are userspace defined/visible/changeable
	 * The reमुख्यing bits are serial-core specअगरic and not modअगरiable by
	 * userspace.
	 */
#घोषणा UPF_FOURPORT		((__क्रमce upf_t) ASYNC_FOURPORT       /* 1  */ )
#घोषणा UPF_SAK			((__क्रमce upf_t) ASYNC_SAK            /* 2  */ )
#घोषणा UPF_SPD_HI		((__क्रमce upf_t) ASYNC_SPD_HI         /* 4  */ )
#घोषणा UPF_SPD_VHI		((__क्रमce upf_t) ASYNC_SPD_VHI        /* 5  */ )
#घोषणा UPF_SPD_CUST		((__क्रमce upf_t) ASYNC_SPD_CUST   /* 0x0030 */ )
#घोषणा UPF_SPD_WARP		((__क्रमce upf_t) ASYNC_SPD_WARP   /* 0x1010 */ )
#घोषणा UPF_SPD_MASK		((__क्रमce upf_t) ASYNC_SPD_MASK   /* 0x1030 */ )
#घोषणा UPF_SKIP_TEST		((__क्रमce upf_t) ASYNC_SKIP_TEST      /* 6  */ )
#घोषणा UPF_AUTO_IRQ		((__क्रमce upf_t) ASYNC_AUTO_IRQ       /* 7  */ )
#घोषणा UPF_HARDPPS_CD		((__क्रमce upf_t) ASYNC_HARDPPS_CD     /* 11 */ )
#घोषणा UPF_SPD_SHI		((__क्रमce upf_t) ASYNC_SPD_SHI        /* 12 */ )
#घोषणा UPF_LOW_LATENCY		((__क्रमce upf_t) ASYNC_LOW_LATENCY    /* 13 */ )
#घोषणा UPF_BUGGY_UART		((__क्रमce upf_t) ASYNC_BUGGY_UART     /* 14 */ )
#घोषणा UPF_MAGIC_MULTIPLIER	((__क्रमce upf_t) ASYNC_MAGIC_MULTIPLIER /* 16 */ )

#घोषणा UPF_NO_THRE_TEST	((__क्रमce upf_t) (1 << 19))
/* Port has hardware-assisted h/w flow control */
#घोषणा UPF_AUTO_CTS		((__क्रमce upf_t) (1 << 20))
#घोषणा UPF_AUTO_RTS		((__क्रमce upf_t) (1 << 21))
#घोषणा UPF_HARD_FLOW		((__क्रमce upf_t) (UPF_AUTO_CTS | UPF_AUTO_RTS))
/* Port has hardware-assisted s/w flow control */
#घोषणा UPF_SOFT_FLOW		((__क्रमce upf_t) (1 << 22))
#घोषणा UPF_CONS_FLOW		((__क्रमce upf_t) (1 << 23))
#घोषणा UPF_SHARE_IRQ		((__क्रमce upf_t) (1 << 24))
#घोषणा UPF_EXAR_EFR		((__क्रमce upf_t) (1 << 25))
#घोषणा UPF_BUG_THRE		((__क्रमce upf_t) (1 << 26))
/* The exact UART type is known and should not be probed.  */
#घोषणा UPF_FIXED_TYPE		((__क्रमce upf_t) (1 << 27))
#घोषणा UPF_BOOT_AUTOCONF	((__क्रमce upf_t) (1 << 28))
#घोषणा UPF_FIXED_PORT		((__क्रमce upf_t) (1 << 29))
#घोषणा UPF_DEAD		((__क्रमce upf_t) (1 << 30))
#घोषणा UPF_IOREMAP		((__क्रमce upf_t) (1 << 31))

#घोषणा __UPF_CHANGE_MASK	0x17fff
#घोषणा UPF_CHANGE_MASK		((__क्रमce upf_t) __UPF_CHANGE_MASK)
#घोषणा UPF_USR_MASK		((__क्रमce upf_t) (UPF_SPD_MASK|UPF_LOW_LATENCY))

#अगर __UPF_CHANGE_MASK > ASYNC_FLAGS
#त्रुटि Change mask not equivalent to userspace-visible bit defines
#पूर्ण_अगर

	/*
	 * Must hold termios_rwsem, port mutex and port lock to change;
	 * can hold any one lock to पढ़ो.
	 */
	upstat_t		status;

#घोषणा UPSTAT_CTS_ENABLE	((__क्रमce upstat_t) (1 << 0))
#घोषणा UPSTAT_DCD_ENABLE	((__क्रमce upstat_t) (1 << 1))
#घोषणा UPSTAT_AUTORTS		((__क्रमce upstat_t) (1 << 2))
#घोषणा UPSTAT_AUTOCTS		((__क्रमce upstat_t) (1 << 3))
#घोषणा UPSTAT_AUTOXOFF		((__क्रमce upstat_t) (1 << 4))
#घोषणा UPSTAT_SYNC_FIFO	((__क्रमce upstat_t) (1 << 5))

	पूर्णांक			hw_stopped;		/* sw-assisted CTS flow state */
	अचिन्हित पूर्णांक		mctrl;			/* current modem ctrl settings */
	अचिन्हित पूर्णांक		समयout;		/* अक्षरacter-based समयout */
	अचिन्हित पूर्णांक		type;			/* port type */
	स्थिर काष्ठा uart_ops	*ops;
	अचिन्हित पूर्णांक		custom_भागisor;
	अचिन्हित पूर्णांक		line;			/* port index */
	अचिन्हित पूर्णांक		minor;
	resource_माप_प्रकार		mapbase;		/* क्रम ioremap */
	resource_माप_प्रकार		mapsize;
	काष्ठा device		*dev;			/* parent device */

	अचिन्हित दीर्घ		sysrq;			/* sysrq समयout */
	अचिन्हित पूर्णांक		sysrq_ch;		/* अक्षर क्रम sysrq */
	अचिन्हित अक्षर		has_sysrq;
	अचिन्हित अक्षर		sysrq_seq;		/* index in sysrq_toggle_seq */

	अचिन्हित अक्षर		hub6;			/* this should be in the 8250 driver */
	अचिन्हित अक्षर		suspended;
	अचिन्हित अक्षर		console_reinit;
	स्थिर अक्षर		*name;			/* port name */
	काष्ठा attribute_group	*attr_group;		/* port specअगरic attributes */
	स्थिर काष्ठा attribute_group **tty_groups;	/* all attributes (serial core use only) */
	काष्ठा serial_rs485     rs485;
	काष्ठा gpio_desc	*rs485_term_gpio;	/* enable RS485 bus termination */
	काष्ठा serial_iso7816   iso7816;
	व्योम			*निजी_data;		/* generic platक्रमm data poपूर्णांकer */
पूर्ण;

अटल अंतरभूत पूर्णांक serial_port_in(काष्ठा uart_port *up, पूर्णांक offset)
अणु
	वापस up->serial_in(up, offset);
पूर्ण

अटल अंतरभूत व्योम serial_port_out(काष्ठा uart_port *up, पूर्णांक offset, पूर्णांक value)
अणु
	up->serial_out(up, offset, value);
पूर्ण

/**
 * क्रमागत uart_pm_state - घातer states क्रम UARTs
 * @UART_PM_STATE_ON: UART is घातered, up and operational
 * @UART_PM_STATE_OFF: UART is घातered off
 * @UART_PM_STATE_UNDEFINED: sentinel
 */
क्रमागत uart_pm_state अणु
	UART_PM_STATE_ON = 0,
	UART_PM_STATE_OFF = 3, /* number taken from ACPI */
	UART_PM_STATE_UNDEFINED,
पूर्ण;

/*
 * This is the state inक्रमmation which is persistent across खोलोs.
 */
काष्ठा uart_state अणु
	काष्ठा tty_port		port;

	क्रमागत uart_pm_state	pm_state;
	काष्ठा circ_buf		xmit;

	atomic_t		refcount;
	रुको_queue_head_t	हटाओ_रुको;
	काष्ठा uart_port	*uart_port;
पूर्ण;

#घोषणा UART_XMIT_SIZE	PAGE_SIZE


/* number of अक्षरacters left in xmit buffer beक्रमe we ask क्रम more */
#घोषणा WAKEUP_CHARS		256

काष्ठा module;
काष्ठा tty_driver;

काष्ठा uart_driver अणु
	काष्ठा module		*owner;
	स्थिर अक्षर		*driver_name;
	स्थिर अक्षर		*dev_name;
	पूर्णांक			 major;
	पूर्णांक			 minor;
	पूर्णांक			 nr;
	काष्ठा console		*cons;

	/*
	 * these are निजी; the low level driver should not
	 * touch these; they should be initialised to शून्य
	 */
	काष्ठा uart_state	*state;
	काष्ठा tty_driver	*tty_driver;
पूर्ण;

व्योम uart_ग_लिखो_wakeup(काष्ठा uart_port *port);

/*
 * Baud rate helpers.
 */
व्योम uart_update_समयout(काष्ठा uart_port *port, अचिन्हित पूर्णांक cflag,
			 अचिन्हित पूर्णांक baud);
अचिन्हित पूर्णांक uart_get_baud_rate(काष्ठा uart_port *port, काष्ठा ktermios *termios,
				काष्ठा ktermios *old, अचिन्हित पूर्णांक min,
				अचिन्हित पूर्णांक max);
अचिन्हित पूर्णांक uart_get_भागisor(काष्ठा uart_port *port, अचिन्हित पूर्णांक baud);

/* Base समयr पूर्णांकerval क्रम polling */
अटल अंतरभूत पूर्णांक uart_poll_समयout(काष्ठा uart_port *port)
अणु
	पूर्णांक समयout = port->समयout;

	वापस समयout > 6 ? (समयout / 2 - 2) : 1;
पूर्ण

/*
 * Console helpers.
 */
काष्ठा earlycon_device अणु
	काष्ठा console *con;
	काष्ठा uart_port port;
	अक्षर options[16];		/* e.g., 115200n8 */
	अचिन्हित पूर्णांक baud;
पूर्ण;

काष्ठा earlycon_id अणु
	अक्षर	name[15];
	अक्षर	name_term;	/* In हाल compiler didn't '\0' term name */
	अक्षर	compatible[128];
	पूर्णांक	(*setup)(काष्ठा earlycon_device *, स्थिर अक्षर *options);
पूर्ण;

बाह्य स्थिर काष्ठा earlycon_id __earlycon_table[];
बाह्य स्थिर काष्ठा earlycon_id __earlycon_table_end[];

#अगर defined(CONFIG_SERIAL_EARLYCON) && !defined(MODULE)
#घोषणा EARLYCON_USED_OR_UNUSED	__used
#अन्यथा
#घोषणा EARLYCON_USED_OR_UNUSED	__maybe_unused
#पूर्ण_अगर

#घोषणा OF_EARLYCON_DECLARE(_name, compat, fn)				\
	अटल स्थिर काष्ठा earlycon_id __UNIQUE_ID(__earlycon_##_name) \
		EARLYCON_USED_OR_UNUSED  __section("__earlycon_table")  \
		__aligned(__alignof__(काष्ठा earlycon_id))		\
		= अणु .name = __stringअगरy(_name),				\
		    .compatible = compat,				\
		    .setup = fn पूर्ण

#घोषणा EARLYCON_DECLARE(_name, fn)	OF_EARLYCON_DECLARE(_name, "", fn)

बाह्य पूर्णांक of_setup_earlycon(स्थिर काष्ठा earlycon_id *match,
			     अचिन्हित दीर्घ node,
			     स्थिर अक्षर *options);

#अगर_घोषित CONFIG_SERIAL_EARLYCON
बाह्य bool earlycon_acpi_spcr_enable __initdata;
पूर्णांक setup_earlycon(अक्षर *buf);
#अन्यथा
अटल स्थिर bool earlycon_acpi_spcr_enable EARLYCON_USED_OR_UNUSED;
अटल अंतरभूत पूर्णांक setup_earlycon(अक्षर *buf) अणु वापस 0; पूर्ण
#पूर्ण_अगर

काष्ठा uart_port *uart_get_console(काष्ठा uart_port *ports, पूर्णांक nr,
				   काष्ठा console *c);
पूर्णांक uart_parse_earlycon(अक्षर *p, अचिन्हित अक्षर *iotype, resource_माप_प्रकार *addr,
			अक्षर **options);
व्योम uart_parse_options(स्थिर अक्षर *options, पूर्णांक *baud, पूर्णांक *parity, पूर्णांक *bits,
			पूर्णांक *flow);
पूर्णांक uart_set_options(काष्ठा uart_port *port, काष्ठा console *co, पूर्णांक baud,
		     पूर्णांक parity, पूर्णांक bits, पूर्णांक flow);
काष्ठा tty_driver *uart_console_device(काष्ठा console *co, पूर्णांक *index);
व्योम uart_console_ग_लिखो(काष्ठा uart_port *port, स्थिर अक्षर *s,
			अचिन्हित पूर्णांक count,
			व्योम (*अक्षर_दो)(काष्ठा uart_port *, पूर्णांक));

/*
 * Port/driver registration/removal
 */
पूर्णांक uart_रेजिस्टर_driver(काष्ठा uart_driver *uart);
व्योम uart_unरेजिस्टर_driver(काष्ठा uart_driver *uart);
पूर्णांक uart_add_one_port(काष्ठा uart_driver *reg, काष्ठा uart_port *port);
पूर्णांक uart_हटाओ_one_port(काष्ठा uart_driver *reg, काष्ठा uart_port *port);
पूर्णांक uart_match_port(काष्ठा uart_port *port1, काष्ठा uart_port *port2);

/*
 * Power Management
 */
पूर्णांक uart_suspend_port(काष्ठा uart_driver *reg, काष्ठा uart_port *port);
पूर्णांक uart_resume_port(काष्ठा uart_driver *reg, काष्ठा uart_port *port);

#घोषणा uart_circ_empty(circ)		((circ)->head == (circ)->tail)
#घोषणा uart_circ_clear(circ)		((circ)->head = (circ)->tail = 0)

#घोषणा uart_circ_अक्षरs_pending(circ)	\
	(CIRC_CNT((circ)->head, (circ)->tail, UART_XMIT_SIZE))

#घोषणा uart_circ_अक्षरs_मुक्त(circ)	\
	(CIRC_SPACE((circ)->head, (circ)->tail, UART_XMIT_SIZE))

अटल अंतरभूत पूर्णांक uart_tx_stopped(काष्ठा uart_port *port)
अणु
	काष्ठा tty_काष्ठा *tty = port->state->port.tty;
	अगर ((tty && tty->stopped) || port->hw_stopped)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत bool uart_cts_enabled(काष्ठा uart_port *uport)
अणु
	वापस !!(uport->status & UPSTAT_CTS_ENABLE);
पूर्ण

अटल अंतरभूत bool uart_softcts_mode(काष्ठा uart_port *uport)
अणु
	upstat_t mask = UPSTAT_CTS_ENABLE | UPSTAT_AUTOCTS;

	वापस ((uport->status & mask) == UPSTAT_CTS_ENABLE);
पूर्ण

/*
 * The following are helper functions क्रम the low level drivers.
 */

बाह्य व्योम uart_handle_dcd_change(काष्ठा uart_port *uport,
		अचिन्हित पूर्णांक status);
बाह्य व्योम uart_handle_cts_change(काष्ठा uart_port *uport,
		अचिन्हित पूर्णांक status);

बाह्य व्योम uart_insert_अक्षर(काष्ठा uart_port *port, अचिन्हित पूर्णांक status,
		 अचिन्हित पूर्णांक overrun, अचिन्हित पूर्णांक ch, अचिन्हित पूर्णांक flag);

#अगर_घोषित CONFIG_MAGIC_SYSRQ_SERIAL
#घोषणा SYSRQ_TIMEOUT	(HZ * 5)

bool uart_try_toggle_sysrq(काष्ठा uart_port *port, अचिन्हित पूर्णांक ch);

अटल अंतरभूत पूर्णांक uart_handle_sysrq_अक्षर(काष्ठा uart_port *port, अचिन्हित पूर्णांक ch)
अणु
	अगर (!port->sysrq)
		वापस 0;

	अगर (ch && समय_beक्रमe(jअगरfies, port->sysrq)) अणु
		अगर (sysrq_mask()) अणु
			handle_sysrq(ch);
			port->sysrq = 0;
			वापस 1;
		पूर्ण
		अगर (uart_try_toggle_sysrq(port, ch))
			वापस 1;
	पूर्ण
	port->sysrq = 0;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक uart_prepare_sysrq_अक्षर(काष्ठा uart_port *port, अचिन्हित पूर्णांक ch)
अणु
	अगर (!port->sysrq)
		वापस 0;

	अगर (ch && समय_beक्रमe(jअगरfies, port->sysrq)) अणु
		अगर (sysrq_mask()) अणु
			port->sysrq_ch = ch;
			port->sysrq = 0;
			वापस 1;
		पूर्ण
		अगर (uart_try_toggle_sysrq(port, ch))
			वापस 1;
	पूर्ण
	port->sysrq = 0;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम uart_unlock_and_check_sysrq(काष्ठा uart_port *port)
अणु
	पूर्णांक sysrq_ch;

	अगर (!port->has_sysrq) अणु
		spin_unlock(&port->lock);
		वापस;
	पूर्ण

	sysrq_ch = port->sysrq_ch;
	port->sysrq_ch = 0;

	spin_unlock(&port->lock);

	अगर (sysrq_ch)
		handle_sysrq(sysrq_ch);
पूर्ण
#अन्यथा	/* CONFIG_MAGIC_SYSRQ_SERIAL */
अटल अंतरभूत पूर्णांक uart_handle_sysrq_अक्षर(काष्ठा uart_port *port, अचिन्हित पूर्णांक ch)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक uart_prepare_sysrq_अक्षर(काष्ठा uart_port *port, अचिन्हित पूर्णांक ch)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम uart_unlock_and_check_sysrq(काष्ठा uart_port *port)
अणु
	spin_unlock(&port->lock);
पूर्ण
#पूर्ण_अगर	/* CONFIG_MAGIC_SYSRQ_SERIAL */

/*
 * We करो the SysRQ and SAK checking like this...
 */
अटल अंतरभूत पूर्णांक uart_handle_अवरोध(काष्ठा uart_port *port)
अणु
	काष्ठा uart_state *state = port->state;

	अगर (port->handle_अवरोध)
		port->handle_अवरोध(port);

#अगर_घोषित CONFIG_MAGIC_SYSRQ_SERIAL
	अगर (port->has_sysrq && uart_console(port)) अणु
		अगर (!port->sysrq) अणु
			port->sysrq = jअगरfies + SYSRQ_TIMEOUT;
			वापस 1;
		पूर्ण
		port->sysrq = 0;
	पूर्ण
#पूर्ण_अगर
	अगर (port->flags & UPF_SAK)
		करो_SAK(state->port.tty);
	वापस 0;
पूर्ण

/*
 *	UART_ENABLE_MS - determine अगर port should enable modem status irqs
 */
#घोषणा UART_ENABLE_MS(port,cflag)	((port)->flags & UPF_HARDPPS_CD || \
					 (cflag) & CRTSCTS || \
					 !((cflag) & CLOCAL))

पूर्णांक uart_get_rs485_mode(काष्ठा uart_port *port);
#पूर्ण_अगर /* LINUX_SERIAL_CORE_H */
