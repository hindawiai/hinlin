<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
** mux.c:
**	serial driver क्रम the Mux console found in some PA-RISC servers.
**
**	(c) Copyright 2002 Ryan Bradetich
**	(c) Copyright 2002 Hewlett-Packard Company
**
** This Driver currently only supports the console (port 0) on the MUX.
** Additional work will be needed on this driver to enable the full
** functionality of the MUX.
**
*/

#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/serial.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h> /* क्रम udelay */
#समावेश <linux/device.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/parisc-device.h>

#समावेश <linux/sysrq.h>
#समावेश <linux/serial_core.h>

#घोषणा MUX_OFFSET 0x800
#घोषणा MUX_LINE_OFFSET 0x80

#घोषणा MUX_FIFO_SIZE 255
#घोषणा MUX_POLL_DELAY (30 * HZ / 1000)

#घोषणा IO_DATA_REG_OFFSET 0x3c
#घोषणा IO_DCOUNT_REG_OFFSET 0x40

#घोषणा MUX_खातापूर्णIFO(status) ((status & 0xF000) == 0xF000)
#घोषणा MUX_STATUS(status) ((status & 0xF000) == 0x8000)
#घोषणा MUX_BREAK(status) ((status & 0xF000) == 0x2000)

#घोषणा MUX_NR 256
अटल अचिन्हित पूर्णांक port_cnt __पढ़ो_mostly;
काष्ठा mux_port अणु
	काष्ठा uart_port port;
	पूर्णांक enabled;
पूर्ण;
अटल काष्ठा mux_port mux_ports[MUX_NR];

अटल काष्ठा uart_driver mux_driver = अणु
	.owner = THIS_MODULE,
	.driver_name = "ttyB",
	.dev_name = "ttyB",
	.major = MUX_MAJOR,
	.minor = 0,
	.nr = MUX_NR,
पूर्ण;

अटल काष्ठा समयr_list mux_समयr;

#घोषणा UART_PUT_CHAR(p, c) __raw_ग_लिखोl((c), (p)->membase + IO_DATA_REG_OFFSET)
#घोषणा UART_GET_FIFO_CNT(p) __raw_पढ़ोl((p)->membase + IO_DCOUNT_REG_OFFSET)

/**
 * get_mux_port_count - Get the number of available ports on the Mux.
 * @dev: The parisc device.
 *
 * This function is used to determine the number of ports the Mux
 * supports.  The IODC data reports the number of ports the Mux
 * can support, but there are हालs where not all the Mux ports
 * are connected.  This function can override the IODC and
 * वापस the true port count.
 */
अटल पूर्णांक __init get_mux_port_count(काष्ठा parisc_device *dev)
अणु
	पूर्णांक status;
	u8 iodc_data[32];
	अचिन्हित दीर्घ bytecnt;

	/* If this is the built-in Mux क्रम the K-Class (Eole CAP/MUX),
	 * we only need to allocate resources क्रम 1 port since the
	 * other 7 ports are not connected.
	 */
	अगर(dev->id.hversion == 0x15)
		वापस 1;

	status = pdc_iodc_पढ़ो(&bytecnt, dev->hpa.start, 0, iodc_data, 32);
	BUG_ON(status != PDC_OK);

	/* Return the number of ports specअगरied in the iodc data. */
	वापस ((((iodc_data)[4] & 0xf0) >> 4) * 8) + 8;
पूर्ण

/**
 * mux_tx_empty - Check अगर the transmitter fअगरo is empty.
 * @port: Ptr to the uart_port.
 *
 * This function test अगर the transmitter fअगरo क्रम the port
 * described by 'port' is empty.  If it is empty, this function
 * should वापस TIOCSER_TEMT, otherwise वापस 0.
 */
अटल अचिन्हित पूर्णांक mux_tx_empty(काष्ठा uart_port *port)
अणु
	वापस UART_GET_FIFO_CNT(port) ? 0 : TIOCSER_TEMT;
पूर्ण 

/**
 * mux_set_mctrl - Set the current state of the modem control inमाला_दो.
 * @ports: Ptr to the uart_port.
 * @mctrl: Modem control bits.
 *
 * The Serial MUX करोes not support CTS, DCD or DSR so this function
 * is ignored.
 */
अटल व्योम mux_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
पूर्ण

/**
 * mux_get_mctrl - Returns the current state of modem control inमाला_दो.
 * @port: Ptr to the uart_port.
 *
 * The Serial MUX करोes not support CTS, DCD or DSR so these lines are
 * treated as permanently active.
 */
अटल अचिन्हित पूर्णांक mux_get_mctrl(काष्ठा uart_port *port)
अणु 
	वापस TIOCM_CAR | TIOCM_DSR | TIOCM_CTS;
पूर्ण

/**
 * mux_stop_tx - Stop transmitting अक्षरacters.
 * @port: Ptr to the uart_port.
 *
 * The Serial MUX करोes not support this function.
 */
अटल व्योम mux_stop_tx(काष्ठा uart_port *port)
अणु
पूर्ण

/**
 * mux_start_tx - Start transmitting अक्षरacters.
 * @port: Ptr to the uart_port.
 *
 * The Serial Mux करोes not support this function.
 */
अटल व्योम mux_start_tx(काष्ठा uart_port *port)
अणु
पूर्ण

/**
 * mux_stop_rx - Stop receiving अक्षरacters.
 * @port: Ptr to the uart_port.
 *
 * The Serial Mux करोes not support this function.
 */
अटल व्योम mux_stop_rx(काष्ठा uart_port *port)
अणु
पूर्ण

/**
 * mux_अवरोध_ctl - Control the transmitssion of a अवरोध संकेत.
 * @port: Ptr to the uart_port.
 * @अवरोध_state: Raise/Lower the अवरोध संकेत.
 *
 * The Serial Mux करोes not support this function.
 */
अटल व्योम mux_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
पूर्ण

/**
 * mux_ग_लिखो - Write अक्षरs to the mux fअगरo.
 * @port: Ptr to the uart_port.
 *
 * This function ग_लिखोs all the data from the uart buffer to
 * the mux fअगरo.
 */
अटल व्योम mux_ग_लिखो(काष्ठा uart_port *port)
अणु
	पूर्णांक count;
	काष्ठा circ_buf *xmit = &port->state->xmit;

	अगर(port->x_अक्षर) अणु
		UART_PUT_CHAR(port, port->x_अक्षर);
		port->icount.tx++;
		port->x_अक्षर = 0;
		वापस;
	पूर्ण

	अगर(uart_circ_empty(xmit) || uart_tx_stopped(port)) अणु
		mux_stop_tx(port);
		वापस;
	पूर्ण

	count = (port->fअगरosize) - UART_GET_FIFO_CNT(port);
	करो अणु
		UART_PUT_CHAR(port, xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
		अगर(uart_circ_empty(xmit))
			अवरोध;

	पूर्ण जबतक(--count > 0);

	जबतक(UART_GET_FIFO_CNT(port)) 
		udelay(1);

	अगर(uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);

	अगर (uart_circ_empty(xmit))
		mux_stop_tx(port);
पूर्ण

/**
 * mux_पढ़ो - Read अक्षरs from the mux fअगरo.
 * @port: Ptr to the uart_port.
 *
 * This पढ़ोs all available data from the mux's fअगरo and pushes
 * the data to the tty layer.
 */
अटल व्योम mux_पढ़ो(काष्ठा uart_port *port)
अणु
	काष्ठा tty_port *tport = &port->state->port;
	पूर्णांक data;
	__u32 start_count = port->icount.rx;

	जबतक(1) अणु
		data = __raw_पढ़ोl(port->membase + IO_DATA_REG_OFFSET);

		अगर (MUX_STATUS(data))
			जारी;

		अगर (MUX_खातापूर्णIFO(data))
			अवरोध;

		port->icount.rx++;

		अगर (MUX_BREAK(data)) अणु
			port->icount.brk++;
			अगर(uart_handle_अवरोध(port))
				जारी;
		पूर्ण

		अगर (uart_handle_sysrq_अक्षर(port, data & 0xffu))
			जारी;

		tty_insert_flip_अक्षर(tport, data & 0xFF, TTY_NORMAL);
	पूर्ण
	
	अगर (start_count != port->icount.rx)
		tty_flip_buffer_push(tport);
पूर्ण

/**
 * mux_startup - Initialize the port.
 * @port: Ptr to the uart_port.
 *
 * Grab any resources needed क्रम this port and start the
 * mux समयr.
 */
अटल पूर्णांक mux_startup(काष्ठा uart_port *port)
अणु
	mux_ports[port->line].enabled = 1;
	वापस 0;
पूर्ण

/**
 * mux_shutकरोwn - Disable the port.
 * @port: Ptr to the uart_port.
 *
 * Release any resources needed क्रम the port.
 */
अटल व्योम mux_shutकरोwn(काष्ठा uart_port *port)
अणु
	mux_ports[port->line].enabled = 0;
पूर्ण

/**
 * mux_set_termios - Chane port parameters.
 * @port: Ptr to the uart_port.
 * @termios: new termios settings.
 * @old: old termios settings.
 *
 * The Serial Mux करोes not support this function.
 */
अटल व्योम
mux_set_termios(काष्ठा uart_port *port, काष्ठा ktermios *termios,
	        काष्ठा ktermios *old)
अणु
पूर्ण

/**
 * mux_type - Describe the port.
 * @port: Ptr to the uart_port.
 *
 * Return a poपूर्णांकer to a string स्थिरant describing the
 * specअगरied port.
 */
अटल स्थिर अक्षर *mux_type(काष्ठा uart_port *port)
अणु
	वापस "Mux";
पूर्ण

/**
 * mux_release_port - Release memory and IO regions.
 * @port: Ptr to the uart_port.
 * 
 * Release any memory and IO region resources currently in use by
 * the port.
 */
अटल व्योम mux_release_port(काष्ठा uart_port *port)
अणु
पूर्ण

/**
 * mux_request_port - Request memory and IO regions.
 * @port: Ptr to the uart_port.
 *
 * Request any memory and IO region resources required by the port.
 * If any fail, no resources should be रेजिस्टरed when this function
 * वापसs, and it should वापस -EBUSY on failure.
 */
अटल पूर्णांक mux_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

/**
 * mux_config_port - Perक्रमm port स्वतःconfiguration.
 * @port: Ptr to the uart_port.
 * @type: Biपंचांगask of required configurations.
 *
 * Perक्रमm any स्वतःconfiguration steps क्रम the port.  This function is
 * called अगर the UPF_BOOT_AUTOCONF flag is specअगरied क्रम the port.
 * [Note: This is required क्रम now because of a bug in the Serial core.
 *  rmk has alपढ़ोy submitted a patch to linus, should be available क्रम
 *  2.5.47.]
 */
अटल व्योम mux_config_port(काष्ठा uart_port *port, पूर्णांक type)
अणु
	port->type = PORT_MUX;
पूर्ण

/**
 * mux_verअगरy_port - Verअगरy the port inक्रमmation.
 * @port: Ptr to the uart_port.
 * @ser: Ptr to the serial inक्रमmation.
 *
 * Verअगरy the new serial port inक्रमmation contained within serinfo is
 * suitable क्रम this port type.
 */
अटल पूर्णांक mux_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *ser)
अणु
	अगर(port->membase == शून्य)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * mux_drv_poll - Mux poll function.
 * @unused: Unused variable
 *
 * This function periodically polls the Serial MUX to check क्रम new data.
 */
अटल व्योम mux_poll(काष्ठा समयr_list *unused)
अणु  
	पूर्णांक i;

	क्रम(i = 0; i < port_cnt; ++i) अणु
		अगर(!mux_ports[i].enabled)
			जारी;

		mux_पढ़ो(&mux_ports[i].port);
		mux_ग_लिखो(&mux_ports[i].port);
	पूर्ण

	mod_समयr(&mux_समयr, jअगरfies + MUX_POLL_DELAY);
पूर्ण


#अगर_घोषित CONFIG_SERIAL_MUX_CONSOLE
अटल व्योम mux_console_ग_लिखो(काष्ठा console *co, स्थिर अक्षर *s, अचिन्हित count)
अणु
	/* Wait until the FIFO drains. */
	जबतक(UART_GET_FIFO_CNT(&mux_ports[0].port))
		udelay(1);

	जबतक(count--) अणु
		अगर(*s == '\n') अणु
			UART_PUT_CHAR(&mux_ports[0].port, '\r');
		पूर्ण
		UART_PUT_CHAR(&mux_ports[0].port, *s++);
	पूर्ण

पूर्ण

अटल पूर्णांक mux_console_setup(काष्ठा console *co, अक्षर *options)
अणु
        वापस 0;
पूर्ण

अटल काष्ठा console mux_console = अणु
	.name =		"ttyB",
	.ग_लिखो =	mux_console_ग_लिखो,
	.device =	uart_console_device,
	.setup =	mux_console_setup,
	.flags =	CON_ENABLED | CON_PRINTBUFFER,
	.index =	0,
	.data =		&mux_driver,
पूर्ण;

#घोषणा MUX_CONSOLE	&mux_console
#अन्यथा
#घोषणा MUX_CONSOLE	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा uart_ops mux_pops = अणु
	.tx_empty =		mux_tx_empty,
	.set_mctrl =		mux_set_mctrl,
	.get_mctrl =		mux_get_mctrl,
	.stop_tx =		mux_stop_tx,
	.start_tx =		mux_start_tx,
	.stop_rx =		mux_stop_rx,
	.अवरोध_ctl =		mux_अवरोध_ctl,
	.startup =		mux_startup,
	.shutकरोwn =		mux_shutकरोwn,
	.set_termios =		mux_set_termios,
	.type =			mux_type,
	.release_port =		mux_release_port,
	.request_port =		mux_request_port,
	.config_port =		mux_config_port,
	.verअगरy_port =		mux_verअगरy_port,
पूर्ण;

/**
 * mux_probe - Determine अगर the Serial Mux should claim this device.
 * @dev: The parisc device.
 *
 * Deterimine अगर the Serial Mux should claim this chip (वापस 0)
 * or not (वापस 1).
 */
अटल पूर्णांक __init mux_probe(काष्ठा parisc_device *dev)
अणु
	पूर्णांक i, status;

	पूर्णांक port_count = get_mux_port_count(dev);
	prपूर्णांकk(KERN_INFO "Serial mux driver (%d ports) Revision: 0.6\n", port_count);

	dev_set_drvdata(&dev->dev, (व्योम *)(दीर्घ)port_count);
	request_mem_region(dev->hpa.start + MUX_OFFSET,
                           port_count * MUX_LINE_OFFSET, "Mux");

	अगर(!port_cnt) अणु
		mux_driver.cons = MUX_CONSOLE;

		status = uart_रेजिस्टर_driver(&mux_driver);
		अगर(status) अणु
			prपूर्णांकk(KERN_ERR "Serial mux: Unable to register driver.\n");
			वापस 1;
		पूर्ण
	पूर्ण

	क्रम(i = 0; i < port_count; ++i, ++port_cnt) अणु
		काष्ठा uart_port *port = &mux_ports[port_cnt].port;
		port->iobase	= 0;
		port->mapbase	= dev->hpa.start + MUX_OFFSET +
						(i * MUX_LINE_OFFSET);
		port->membase	= ioremap(port->mapbase, MUX_LINE_OFFSET);
		port->iotype	= UPIO_MEM;
		port->type	= PORT_MUX;
		port->irq	= 0;
		port->uartclk	= 0;
		port->fअगरosize	= MUX_FIFO_SIZE;
		port->ops	= &mux_pops;
		port->flags	= UPF_BOOT_AUTOCONF;
		port->line	= port_cnt;
		port->has_sysrq = IS_ENABLED(CONFIG_SERIAL_MUX_CONSOLE);

		/* The port->समयout needs to match what is present in
		 * uart_रुको_until_sent in serial_core.c.  Otherwise
		 * the समय spent in msleep_पूर्णांकerruptable will be very
		 * दीर्घ, causing the appearance of a console hang.
		 */
		port->समयout   = HZ / 50;
		spin_lock_init(&port->lock);

		status = uart_add_one_port(&mux_driver, port);
		BUG_ON(status);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __निकास mux_हटाओ(काष्ठा parisc_device *dev)
अणु
	पूर्णांक i, j;
	पूर्णांक port_count = (दीर्घ)dev_get_drvdata(&dev->dev);

	/* Find Port 0 क्रम this card in the mux_ports list. */
	क्रम(i = 0; i < port_cnt; ++i) अणु
		अगर(mux_ports[i].port.mapbase == dev->hpa.start + MUX_OFFSET)
			अवरोध;
	पूर्ण
	BUG_ON(i + port_count > port_cnt);

	/* Release the resources associated with each port on the device. */
	क्रम(j = 0; j < port_count; ++j, ++i) अणु
		काष्ठा uart_port *port = &mux_ports[i].port;

		uart_हटाओ_one_port(&mux_driver, port);
		अगर(port->membase)
			iounmap(port->membase);
	पूर्ण

	release_mem_region(dev->hpa.start + MUX_OFFSET, port_count * MUX_LINE_OFFSET);
	वापस 0;
पूर्ण

/* Hack.  This idea was taken from the 8250_gsc.c on how to properly order
 * the serial port detection in the proper order.   The idea is we always
 * want the builtin mux to be detected beक्रमe addin mux cards, so we
 * specअगरically probe क्रम the builtin mux cards first.
 *
 * This table only contains the parisc_device_id of known builtin mux
 * devices.  All other mux cards will be detected by the generic mux_tbl.
 */
अटल स्थिर काष्ठा parisc_device_id builtin_mux_tbl[] __initस्थिर = अणु
	अणु HPHW_A_सूचीECT, HVERSION_REV_ANY_ID, 0x15, 0x0000D पूर्ण, /* All K-class */
	अणु HPHW_A_सूचीECT, HVERSION_REV_ANY_ID, 0x44, 0x0000D पूर्ण, /* E35, E45, and E55 */
	अणु 0, पूर्ण
पूर्ण;

अटल स्थिर काष्ठा parisc_device_id mux_tbl[] __initस्थिर = अणु
	अणु HPHW_A_सूचीECT, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x0000D पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(parisc, builtin_mux_tbl);
MODULE_DEVICE_TABLE(parisc, mux_tbl);

अटल काष्ठा parisc_driver builtin_serial_mux_driver __refdata = अणु
	.name =		"builtin_serial_mux",
	.id_table =	builtin_mux_tbl,
	.probe =	mux_probe,
	.हटाओ =       __निकास_p(mux_हटाओ),
पूर्ण;

अटल काष्ठा parisc_driver serial_mux_driver __refdata = अणु
	.name =		"serial_mux",
	.id_table =	mux_tbl,
	.probe =	mux_probe,
	.हटाओ =       __निकास_p(mux_हटाओ),
पूर्ण;

/**
 * mux_init - Serial MUX initialization procedure.
 *
 * Register the Serial MUX driver.
 */
अटल पूर्णांक __init mux_init(व्योम)
अणु
	रेजिस्टर_parisc_driver(&builtin_serial_mux_driver);
	रेजिस्टर_parisc_driver(&serial_mux_driver);

	अगर(port_cnt > 0) अणु
		/* Start the Mux समयr */
		समयr_setup(&mux_समयr, mux_poll, 0);
		mod_समयr(&mux_समयr, jअगरfies + MUX_POLL_DELAY);

#अगर_घोषित CONFIG_SERIAL_MUX_CONSOLE
	        रेजिस्टर_console(&mux_console);
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mux_निकास - Serial MUX cleanup procedure.
 *
 * Unरेजिस्टर the Serial MUX driver from the tty layer.
 */
अटल व्योम __निकास mux_निकास(व्योम)
अणु
	/* Delete the Mux समयr. */
	अगर(port_cnt > 0) अणु
		del_समयr_sync(&mux_समयr);
#अगर_घोषित CONFIG_SERIAL_MUX_CONSOLE
		unरेजिस्टर_console(&mux_console);
#पूर्ण_अगर
	पूर्ण

	unरेजिस्टर_parisc_driver(&builtin_serial_mux_driver);
	unरेजिस्टर_parisc_driver(&serial_mux_driver);
	uart_unरेजिस्टर_driver(&mux_driver);
पूर्ण

module_init(mux_init);
module_निकास(mux_निकास);

MODULE_AUTHOR("Ryan Bradetich");
MODULE_DESCRIPTION("Serial MUX driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS_CHARDEV_MAJOR(MUX_MAJOR);
