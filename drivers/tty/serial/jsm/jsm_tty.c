<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/************************************************************************
 * Copyright 2003 Digi International (www.digi.com)
 *
 * Copyright (C) 2004 IBM Corporation. All rights reserved.
 *
 * Contact Inक्रमmation:
 * Scott H Kilau <Scott_Kilau@digi.com>
 * Ananda Venkatarman <mansarov@us.ibm.com>
 * Modअगरications:
 * 01/19/06:	changed jsm_input routine to use the dynamically allocated
 *		tty_buffer changes. Contributors: Scott Kilau and Ananda V.
 ***********************************************************************/
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/delay.h>	/* For udelay */
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश "jsm.h"

अटल DECLARE_BITMAP(linemap, MAXLINES);

अटल व्योम jsm_carrier(काष्ठा jsm_channel *ch);

अटल अंतरभूत पूर्णांक jsm_get_mstat(काष्ठा jsm_channel *ch)
अणु
	अचिन्हित अक्षर mstat;
	पूर्णांक result;

	jsm_dbg(IOCTL, &ch->ch_bd->pci_dev, "start\n");

	mstat = (ch->ch_mostat | ch->ch_mistat);

	result = 0;

	अगर (mstat & UART_MCR_DTR)
		result |= TIOCM_DTR;
	अगर (mstat & UART_MCR_RTS)
		result |= TIOCM_RTS;
	अगर (mstat & UART_MSR_CTS)
		result |= TIOCM_CTS;
	अगर (mstat & UART_MSR_DSR)
		result |= TIOCM_DSR;
	अगर (mstat & UART_MSR_RI)
		result |= TIOCM_RI;
	अगर (mstat & UART_MSR_DCD)
		result |= TIOCM_CD;

	jsm_dbg(IOCTL, &ch->ch_bd->pci_dev, "finish\n");
	वापस result;
पूर्ण

अटल अचिन्हित पूर्णांक jsm_tty_tx_empty(काष्ठा uart_port *port)
अणु
	वापस TIOCSER_TEMT;
पूर्ण

/*
 * Return modem संकेतs to ld.
 */
अटल अचिन्हित पूर्णांक jsm_tty_get_mctrl(काष्ठा uart_port *port)
अणु
	पूर्णांक result;
	काष्ठा jsm_channel *channel =
		container_of(port, काष्ठा jsm_channel, uart_port);

	jsm_dbg(IOCTL, &channel->ch_bd->pci_dev, "start\n");

	result = jsm_get_mstat(channel);

	अगर (result < 0)
		वापस -ENXIO;

	jsm_dbg(IOCTL, &channel->ch_bd->pci_dev, "finish\n");

	वापस result;
पूर्ण

/*
 * jsm_set_modem_info()
 *
 * Set modem संकेतs, called by ld.
 */
अटल व्योम jsm_tty_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा jsm_channel *channel =
		container_of(port, काष्ठा jsm_channel, uart_port);

	jsm_dbg(IOCTL, &channel->ch_bd->pci_dev, "start\n");

	अगर (mctrl & TIOCM_RTS)
		channel->ch_mostat |= UART_MCR_RTS;
	अन्यथा
		channel->ch_mostat &= ~UART_MCR_RTS;

	अगर (mctrl & TIOCM_DTR)
		channel->ch_mostat |= UART_MCR_DTR;
	अन्यथा
		channel->ch_mostat &= ~UART_MCR_DTR;

	channel->ch_bd->bd_ops->निश्चित_modem_संकेतs(channel);

	jsm_dbg(IOCTL, &channel->ch_bd->pci_dev, "finish\n");
	udelay(10);
पूर्ण

/*
 * jsm_tty_ग_लिखो()
 *
 * Take data from the user or kernel and send it out to the FEP.
 * In here exists all the Transparent Prपूर्णांक magic as well.
 */
अटल व्योम jsm_tty_ग_लिखो(काष्ठा uart_port *port)
अणु
	काष्ठा jsm_channel *channel;

	channel = container_of(port, काष्ठा jsm_channel, uart_port);
	channel->ch_bd->bd_ops->copy_data_from_queue_to_uart(channel);
पूर्ण

अटल व्योम jsm_tty_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा jsm_channel *channel =
		container_of(port, काष्ठा jsm_channel, uart_port);

	jsm_dbg(IOCTL, &channel->ch_bd->pci_dev, "start\n");

	channel->ch_flags &= ~(CH_STOP);
	jsm_tty_ग_लिखो(port);

	jsm_dbg(IOCTL, &channel->ch_bd->pci_dev, "finish\n");
पूर्ण

अटल व्योम jsm_tty_stop_tx(काष्ठा uart_port *port)
अणु
	काष्ठा jsm_channel *channel =
		container_of(port, काष्ठा jsm_channel, uart_port);

	jsm_dbg(IOCTL, &channel->ch_bd->pci_dev, "start\n");

	channel->ch_flags |= (CH_STOP);

	jsm_dbg(IOCTL, &channel->ch_bd->pci_dev, "finish\n");
पूर्ण

अटल व्योम jsm_tty_send_xअक्षर(काष्ठा uart_port *port, अक्षर ch)
अणु
	अचिन्हित दीर्घ lock_flags;
	काष्ठा jsm_channel *channel =
		container_of(port, काष्ठा jsm_channel, uart_port);
	काष्ठा ktermios *termios;

	spin_lock_irqsave(&port->lock, lock_flags);
	termios = &port->state->port.tty->termios;
	अगर (ch == termios->c_cc[VSTART])
		channel->ch_bd->bd_ops->send_start_अक्षरacter(channel);

	अगर (ch == termios->c_cc[VSTOP])
		channel->ch_bd->bd_ops->send_stop_अक्षरacter(channel);
	spin_unlock_irqrestore(&port->lock, lock_flags);
पूर्ण

अटल व्योम jsm_tty_stop_rx(काष्ठा uart_port *port)
अणु
	काष्ठा jsm_channel *channel =
		container_of(port, काष्ठा jsm_channel, uart_port);

	channel->ch_bd->bd_ops->disable_receiver(channel);
पूर्ण

अटल व्योम jsm_tty_अवरोध(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	अचिन्हित दीर्घ lock_flags;
	काष्ठा jsm_channel *channel =
		container_of(port, काष्ठा jsm_channel, uart_port);

	spin_lock_irqsave(&port->lock, lock_flags);
	अगर (अवरोध_state == -1)
		channel->ch_bd->bd_ops->send_अवरोध(channel);
	अन्यथा
		channel->ch_bd->bd_ops->clear_अवरोध(channel);

	spin_unlock_irqrestore(&port->lock, lock_flags);
पूर्ण

अटल पूर्णांक jsm_tty_खोलो(काष्ठा uart_port *port)
अणु
	काष्ठा jsm_board *brd;
	काष्ठा jsm_channel *channel =
		container_of(port, काष्ठा jsm_channel, uart_port);
	काष्ठा ktermios *termios;

	/* Get board poपूर्णांकer from our array of majors we have allocated */
	brd = channel->ch_bd;

	/*
	 * Allocate channel buffers क्रम पढ़ो/ग_लिखो/error.
	 * Set flag, so we करोn't get trounced on.
	 */
	channel->ch_flags |= (CH_OPENING);

	/* Drop locks, as दो_स्मृति with GFP_KERNEL can sleep */

	अगर (!channel->ch_rqueue) अणु
		channel->ch_rqueue = kzalloc(RQUEUESIZE, GFP_KERNEL);
		अगर (!channel->ch_rqueue) अणु
			jsm_dbg(INIT, &channel->ch_bd->pci_dev,
				"unable to allocate read queue buf\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	अगर (!channel->ch_equeue) अणु
		channel->ch_equeue = kzalloc(EQUEUESIZE, GFP_KERNEL);
		अगर (!channel->ch_equeue) अणु
			jsm_dbg(INIT, &channel->ch_bd->pci_dev,
				"unable to allocate error queue buf\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	channel->ch_flags &= ~(CH_OPENING);
	/*
	 * Initialize अगर neither terminal is खोलो.
	 */
	jsm_dbg(OPEN, &channel->ch_bd->pci_dev,
		"jsm_open: initializing channel in open...\n");

	/*
	 * Flush input queues.
	 */
	channel->ch_r_head = channel->ch_r_tail = 0;
	channel->ch_e_head = channel->ch_e_tail = 0;

	brd->bd_ops->flush_uart_ग_लिखो(channel);
	brd->bd_ops->flush_uart_पढ़ो(channel);

	channel->ch_flags = 0;
	channel->ch_cached_lsr = 0;
	channel->ch_stops_sent = 0;

	termios = &port->state->port.tty->termios;
	channel->ch_c_cflag	= termios->c_cflag;
	channel->ch_c_अगरlag	= termios->c_अगरlag;
	channel->ch_c_oflag	= termios->c_oflag;
	channel->ch_c_lflag	= termios->c_lflag;
	channel->ch_startc	= termios->c_cc[VSTART];
	channel->ch_stopc	= termios->c_cc[VSTOP];

	/* Tell UART to init itself */
	brd->bd_ops->uart_init(channel);

	/*
	 * Run param in हाल we changed anything
	 */
	brd->bd_ops->param(channel);

	jsm_carrier(channel);

	channel->ch_खोलो_count++;

	jsm_dbg(OPEN, &channel->ch_bd->pci_dev, "finish\n");
	वापस 0;
पूर्ण

अटल व्योम jsm_tty_बंद(काष्ठा uart_port *port)
अणु
	काष्ठा jsm_board *bd;
	काष्ठा jsm_channel *channel =
		container_of(port, काष्ठा jsm_channel, uart_port);

	jsm_dbg(CLOSE, &channel->ch_bd->pci_dev, "start\n");

	bd = channel->ch_bd;

	channel->ch_flags &= ~(CH_STOPI);

	channel->ch_खोलो_count--;

	/*
	 * If we have HUPCL set, lower DTR and RTS
	 */
	अगर (channel->ch_c_cflag & HUPCL) अणु
		jsm_dbg(CLOSE, &channel->ch_bd->pci_dev,
			"Close. HUPCL set, dropping DTR/RTS\n");

		/* Drop RTS/DTR */
		channel->ch_mostat &= ~(UART_MCR_DTR | UART_MCR_RTS);
		bd->bd_ops->निश्चित_modem_संकेतs(channel);
	पूर्ण

	/* Turn off UART पूर्णांकerrupts क्रम this port */
	channel->ch_bd->bd_ops->uart_off(channel);

	jsm_dbg(CLOSE, &channel->ch_bd->pci_dev, "finish\n");
पूर्ण

अटल व्योम jsm_tty_set_termios(काष्ठा uart_port *port,
				 काष्ठा ktermios *termios,
				 काष्ठा ktermios *old_termios)
अणु
	अचिन्हित दीर्घ lock_flags;
	काष्ठा jsm_channel *channel =
		container_of(port, काष्ठा jsm_channel, uart_port);

	spin_lock_irqsave(&port->lock, lock_flags);
	channel->ch_c_cflag	= termios->c_cflag;
	channel->ch_c_अगरlag	= termios->c_अगरlag;
	channel->ch_c_oflag	= termios->c_oflag;
	channel->ch_c_lflag	= termios->c_lflag;
	channel->ch_startc	= termios->c_cc[VSTART];
	channel->ch_stopc	= termios->c_cc[VSTOP];

	channel->ch_bd->bd_ops->param(channel);
	jsm_carrier(channel);
	spin_unlock_irqrestore(&port->lock, lock_flags);
पूर्ण

अटल स्थिर अक्षर *jsm_tty_type(काष्ठा uart_port *port)
अणु
	वापस "jsm";
पूर्ण

अटल व्योम jsm_tty_release_port(काष्ठा uart_port *port)
अणु
पूर्ण

अटल पूर्णांक jsm_tty_request_port(काष्ठा uart_port *port)
अणु
	वापस 0;
पूर्ण

अटल व्योम jsm_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	port->type = PORT_JSM;
पूर्ण

अटल स्थिर काष्ठा uart_ops jsm_ops = अणु
	.tx_empty	= jsm_tty_tx_empty,
	.set_mctrl	= jsm_tty_set_mctrl,
	.get_mctrl	= jsm_tty_get_mctrl,
	.stop_tx	= jsm_tty_stop_tx,
	.start_tx	= jsm_tty_start_tx,
	.send_xअक्षर	= jsm_tty_send_xअक्षर,
	.stop_rx	= jsm_tty_stop_rx,
	.अवरोध_ctl	= jsm_tty_अवरोध,
	.startup	= jsm_tty_खोलो,
	.shutकरोwn	= jsm_tty_बंद,
	.set_termios	= jsm_tty_set_termios,
	.type		= jsm_tty_type,
	.release_port	= jsm_tty_release_port,
	.request_port	= jsm_tty_request_port,
	.config_port	= jsm_config_port,
पूर्ण;

/*
 * jsm_tty_init()
 *
 * Init the tty subप्रणाली.  Called once per board after board has been
 * करोwnloaded and init'ed.
 */
पूर्णांक jsm_tty_init(काष्ठा jsm_board *brd)
अणु
	पूर्णांक i;
	व्योम __iomem *vaddr;
	काष्ठा jsm_channel *ch;

	अगर (!brd)
		वापस -ENXIO;

	jsm_dbg(INIT, &brd->pci_dev, "start\n");

	/*
	 * Initialize board काष्ठाure elements.
	 */

	brd->nasync = brd->maxports;

	/*
	 * Allocate channel memory that might not have been allocated
	 * when the driver was first loaded.
	 */
	क्रम (i = 0; i < brd->nasync; i++) अणु
		अगर (!brd->channels[i]) अणु

			/*
			 * Okay to दो_स्मृति with GFP_KERNEL, we are not at
			 * पूर्णांकerrupt context, and there are no locks held.
			 */
			brd->channels[i] = kzalloc(माप(काष्ठा jsm_channel), GFP_KERNEL);
			अगर (!brd->channels[i]) अणु
				jsm_dbg(CORE, &brd->pci_dev,
					"%s:%d Unable to allocate memory for channel struct\n",
					__खाता__, __LINE__);
			पूर्ण
		पूर्ण
	पूर्ण

	ch = brd->channels[0];
	vaddr = brd->re_map_membase;

	/* Set up channel variables */
	क्रम (i = 0; i < brd->nasync; i++, ch = brd->channels[i]) अणु

		अगर (!brd->channels[i])
			जारी;

		spin_lock_init(&ch->ch_lock);

		अगर (brd->bd_uart_offset == 0x200)
			ch->ch_neo_uart =  vaddr + (brd->bd_uart_offset * i);
		अन्यथा
			ch->ch_cls_uart =  vaddr + (brd->bd_uart_offset * i);

		ch->ch_bd = brd;
		ch->ch_portnum = i;

		/* .25 second delay */
		ch->ch_बंद_delay = 250;

		init_रुकोqueue_head(&ch->ch_flags_रुको);
	पूर्ण

	jsm_dbg(INIT, &brd->pci_dev, "finish\n");
	वापस 0;
पूर्ण

पूर्णांक jsm_uart_port_init(काष्ठा jsm_board *brd)
अणु
	पूर्णांक i, rc;
	अचिन्हित पूर्णांक line;

	अगर (!brd)
		वापस -ENXIO;

	jsm_dbg(INIT, &brd->pci_dev, "start\n");

	/*
	 * Initialize board काष्ठाure elements.
	 */

	brd->nasync = brd->maxports;

	/* Set up channel variables */
	क्रम (i = 0; i < brd->nasync; i++) अणु

		अगर (!brd->channels[i])
			जारी;

		brd->channels[i]->uart_port.irq = brd->irq;
		brd->channels[i]->uart_port.uartclk = 14745600;
		brd->channels[i]->uart_port.type = PORT_JSM;
		brd->channels[i]->uart_port.iotype = UPIO_MEM;
		brd->channels[i]->uart_port.membase = brd->re_map_membase;
		brd->channels[i]->uart_port.fअगरosize = 16;
		brd->channels[i]->uart_port.ops = &jsm_ops;
		line = find_first_zero_bit(linemap, MAXLINES);
		अगर (line >= MAXLINES) अणु
			prपूर्णांकk(KERN_INFO "jsm: linemap is full, added device failed\n");
			जारी;
		पूर्ण अन्यथा
			set_bit(line, linemap);
		brd->channels[i]->uart_port.line = line;
		rc = uart_add_one_port(&jsm_uart_driver, &brd->channels[i]->uart_port);
		अगर (rc) अणु
			prपूर्णांकk(KERN_INFO "jsm: Port %d failed. Aborting...\n", i);
			वापस rc;
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_INFO "jsm: Port %d added\n", i);
	पूर्ण

	jsm_dbg(INIT, &brd->pci_dev, "finish\n");
	वापस 0;
पूर्ण

पूर्णांक jsm_हटाओ_uart_port(काष्ठा jsm_board *brd)
अणु
	पूर्णांक i;
	काष्ठा jsm_channel *ch;

	अगर (!brd)
		वापस -ENXIO;

	jsm_dbg(INIT, &brd->pci_dev, "start\n");

	/*
	 * Initialize board काष्ठाure elements.
	 */

	brd->nasync = brd->maxports;

	/* Set up channel variables */
	क्रम (i = 0; i < brd->nasync; i++) अणु

		अगर (!brd->channels[i])
			जारी;

		ch = brd->channels[i];

		clear_bit(ch->uart_port.line, linemap);
		uart_हटाओ_one_port(&jsm_uart_driver, &brd->channels[i]->uart_port);
	पूर्ण

	jsm_dbg(INIT, &brd->pci_dev, "finish\n");
	वापस 0;
पूर्ण

व्योम jsm_input(काष्ठा jsm_channel *ch)
अणु
	काष्ठा jsm_board *bd;
	काष्ठा tty_काष्ठा *tp;
	काष्ठा tty_port *port;
	u32 rmask;
	u16 head;
	u16 tail;
	पूर्णांक data_len;
	अचिन्हित दीर्घ lock_flags;
	पूर्णांक len = 0;
	पूर्णांक s = 0;
	पूर्णांक i = 0;

	jsm_dbg(READ, &ch->ch_bd->pci_dev, "start\n");

	port = &ch->uart_port.state->port;
	tp = port->tty;

	bd = ch->ch_bd;
	अगर (!bd)
		वापस;

	spin_lock_irqsave(&ch->ch_lock, lock_flags);

	/*
	 *Figure the number of अक्षरacters in the buffer.
	 *Exit immediately अगर none.
	 */

	rmask = RQUEUEMASK;

	head = ch->ch_r_head & rmask;
	tail = ch->ch_r_tail & rmask;

	data_len = (head - tail) & rmask;
	अगर (data_len == 0) अणु
		spin_unlock_irqrestore(&ch->ch_lock, lock_flags);
		वापस;
	पूर्ण

	jsm_dbg(READ, &ch->ch_bd->pci_dev, "start\n");

	/*
	 *If the device is not खोलो, or CREAD is off, flush
	 *input data and वापस immediately.
	 */
	अगर (!tp || !C_CREAD(tp)) अणु

		jsm_dbg(READ, &ch->ch_bd->pci_dev,
			"input. dropping %d bytes on port %d...\n",
			data_len, ch->ch_portnum);
		ch->ch_r_head = tail;

		/* Force queue flow control to be released, अगर needed */
		jsm_check_queue_flow_control(ch);

		spin_unlock_irqrestore(&ch->ch_lock, lock_flags);
		वापस;
	पूर्ण

	/*
	 * If we are throttled, simply करोn't पढ़ो any data.
	 */
	अगर (ch->ch_flags & CH_STOPI) अणु
		spin_unlock_irqrestore(&ch->ch_lock, lock_flags);
		jsm_dbg(READ, &ch->ch_bd->pci_dev,
			"Port %d throttled, not reading any data. head: %x tail: %x\n",
			ch->ch_portnum, head, tail);
		वापस;
	पूर्ण

	jsm_dbg(READ, &ch->ch_bd->pci_dev, "start 2\n");

	len = tty_buffer_request_room(port, data_len);

	/*
	 * len now contains the most amount of data we can copy,
	 * bounded either by the flip buffer size or the amount
	 * of data the card actually has pending...
	 */
	जबतक (len) अणु
		s = ((head >= tail) ? head : RQUEUESIZE) - tail;
		s = min(s, len);

		अगर (s <= 0)
			अवरोध;

			/*
			 * If conditions are such that ld needs to see all
			 * UART errors, we will have to walk each अक्षरacter
			 * and error byte and send them to the buffer one at
			 * a समय.
			 */

		अगर (I_PARMRK(tp) || I_BRKINT(tp) || I_INPCK(tp)) अणु
			क्रम (i = 0; i < s; i++) अणु
				u8 chr   = ch->ch_rqueue[tail + i];
				u8 error = ch->ch_equeue[tail + i];
				अक्षर flag = TTY_NORMAL;

				/*
				 * Give the Linux ld the flags in the क्रमmat it
				 * likes.
				 */
				अगर (error & UART_LSR_BI)
					flag = TTY_BREAK;
				अन्यथा अगर (error & UART_LSR_PE)
					flag = TTY_PARITY;
				अन्यथा अगर (error & UART_LSR_FE)
					flag = TTY_FRAME;

				tty_insert_flip_अक्षर(port, chr, flag);
			पूर्ण
		पूर्ण अन्यथा अणु
			tty_insert_flip_string(port, ch->ch_rqueue + tail, s);
		पूर्ण
		tail += s;
		len -= s;
		/* Flip queue अगर needed */
		tail &= rmask;
	पूर्ण

	ch->ch_r_tail = tail & rmask;
	ch->ch_e_tail = tail & rmask;
	jsm_check_queue_flow_control(ch);
	spin_unlock_irqrestore(&ch->ch_lock, lock_flags);

	/* Tell the tty layer its okay to "eat" the data now */
	tty_flip_buffer_push(port);

	jsm_dbg(IOCTL, &ch->ch_bd->pci_dev, "finish\n");
पूर्ण

अटल व्योम jsm_carrier(काष्ठा jsm_channel *ch)
अणु
	काष्ठा jsm_board *bd;

	पूर्णांक virt_carrier = 0;
	पूर्णांक phys_carrier = 0;

	jsm_dbg(CARR, &ch->ch_bd->pci_dev, "start\n");

	bd = ch->ch_bd;
	अगर (!bd)
		वापस;

	अगर (ch->ch_mistat & UART_MSR_DCD) अणु
		jsm_dbg(CARR, &ch->ch_bd->pci_dev, "mistat: %x D_CD: %x\n",
			ch->ch_mistat, ch->ch_mistat & UART_MSR_DCD);
		phys_carrier = 1;
	पूर्ण

	अगर (ch->ch_c_cflag & CLOCAL)
		virt_carrier = 1;

	jsm_dbg(CARR, &ch->ch_bd->pci_dev, "DCD: physical: %d virt: %d\n",
		phys_carrier, virt_carrier);

	/*
	 * Test क्रम a VIRTUAL carrier transition to HIGH.
	 */
	अगर (((ch->ch_flags & CH_FCAR) == 0) && (virt_carrier == 1)) अणु

		/*
		 * When carrier rises, wake any thपढ़ोs रुकोing
		 * क्रम carrier in the खोलो routine.
		 */

		jsm_dbg(CARR, &ch->ch_bd->pci_dev, "carrier: virt DCD rose\n");

		अगर (रुकोqueue_active(&(ch->ch_flags_रुको)))
			wake_up_पूर्णांकerruptible(&ch->ch_flags_रुको);
	पूर्ण

	/*
	 * Test क्रम a PHYSICAL carrier transition to HIGH.
	 */
	अगर (((ch->ch_flags & CH_CD) == 0) && (phys_carrier == 1)) अणु

		/*
		 * When carrier rises, wake any thपढ़ोs रुकोing
		 * क्रम carrier in the खोलो routine.
		 */

		jsm_dbg(CARR, &ch->ch_bd->pci_dev,
			"carrier: physical DCD rose\n");

		अगर (रुकोqueue_active(&(ch->ch_flags_रुको)))
			wake_up_पूर्णांकerruptible(&ch->ch_flags_रुको);
	पूर्ण

	/*
	 *  Test क्रम a PHYSICAL transition to low, so दीर्घ as we aren't
	 *  currently ignoring physical transitions (which is what "भव
	 *  carrier" indicates).
	 *
	 *  The transition of the भव carrier to low really करोesn't
	 *  matter... it really only means "ignore carrier state", not
	 *  "make pretend that carrier is there".
	 */
	अगर ((virt_carrier == 0) && ((ch->ch_flags & CH_CD) != 0)
			&& (phys_carrier == 0)) अणु
		/*
		 *	When carrier drops:
		 *
		 *	Drop carrier on all खोलो units.
		 *
		 *	Flush queues, waking up any task रुकोing in the
		 *	line discipline.
		 *
		 *	Send a hangup to the control terminal.
		 *
		 *	Enable all select calls.
		 */
		अगर (रुकोqueue_active(&(ch->ch_flags_रुको)))
			wake_up_पूर्णांकerruptible(&ch->ch_flags_रुको);
	पूर्ण

	/*
	 *  Make sure that our cached values reflect the current reality.
	 */
	अगर (virt_carrier == 1)
		ch->ch_flags |= CH_FCAR;
	अन्यथा
		ch->ch_flags &= ~CH_FCAR;

	अगर (phys_carrier == 1)
		ch->ch_flags |= CH_CD;
	अन्यथा
		ch->ch_flags &= ~CH_CD;
पूर्ण


व्योम jsm_check_queue_flow_control(काष्ठा jsm_channel *ch)
अणु
	काष्ठा board_ops *bd_ops = ch->ch_bd->bd_ops;
	पूर्णांक qleft;

	/* Store how much space we have left in the queue */
	अगर ((qleft = ch->ch_r_tail - ch->ch_r_head - 1) < 0)
		qleft += RQUEUEMASK + 1;

	/*
	 * Check to see अगर we should enक्रमce flow control on our queue because
	 * the ld (or user) isn't पढ़ोing data out of our queue fast enuf.
	 *
	 * NOTE: This is करोne based on what the current flow control of the
	 * port is set क्रम.
	 *
	 * 1) HWFLOW (RTS) - Turn off the UART's Receive पूर्णांकerrupt.
	 *	This will cause the UART's FIFO to back up, and क्रमce
	 *	the RTS संकेत to be dropped.
	 * 2) SWFLOW (IXOFF) - Keep trying to send a stop अक्षरacter to
	 *	the other side, in hopes it will stop sending data to us.
	 * 3) NONE - Nothing we can करो.  We will simply drop any extra data
	 *	that माला_लो sent पूर्णांकo us when the queue fills up.
	 */
	अगर (qleft < 256) अणु
		/* HWFLOW */
		अगर (ch->ch_c_cflag & CRTSCTS) अणु
			अगर (!(ch->ch_flags & CH_RECEIVER_OFF)) अणु
				bd_ops->disable_receiver(ch);
				ch->ch_flags |= (CH_RECEIVER_OFF);
				jsm_dbg(READ, &ch->ch_bd->pci_dev,
					"Internal queue hit hilevel mark (%d)! Turning off interrupts\n",
					qleft);
			पूर्ण
		पूर्ण
		/* SWFLOW */
		अन्यथा अगर (ch->ch_c_अगरlag & IXOFF) अणु
			अगर (ch->ch_stops_sent <= MAX_STOPS_SENT) अणु
				bd_ops->send_stop_अक्षरacter(ch);
				ch->ch_stops_sent++;
				jsm_dbg(READ, &ch->ch_bd->pci_dev,
					"Sending stop char! Times sent: %x\n",
					ch->ch_stops_sent);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Check to see अगर we should unenक्रमce flow control because
	 * ld (or user) finally पढ़ो enuf data out of our queue.
	 *
	 * NOTE: This is करोne based on what the current flow control of the
	 * port is set क्रम.
	 *
	 * 1) HWFLOW (RTS) - Turn back on the UART's Receive पूर्णांकerrupt.
	 *	This will cause the UART's FIFO to उठाओ RTS back up,
	 *	which will allow the other side to start sending data again.
	 * 2) SWFLOW (IXOFF) - Send a start अक्षरacter to
	 *	the other side, so it will start sending data to us again.
	 * 3) NONE - Do nothing. Since we didn't करो anything to turn off the
	 *	other side, we करोn't need to करो anything now.
	 */
	अगर (qleft > (RQUEUESIZE / 2)) अणु
		/* HWFLOW */
		अगर (ch->ch_c_cflag & CRTSCTS) अणु
			अगर (ch->ch_flags & CH_RECEIVER_OFF) अणु
				bd_ops->enable_receiver(ch);
				ch->ch_flags &= ~(CH_RECEIVER_OFF);
				jsm_dbg(READ, &ch->ch_bd->pci_dev,
					"Internal queue hit lowlevel mark (%d)! Turning on interrupts\n",
					qleft);
			पूर्ण
		पूर्ण
		/* SWFLOW */
		अन्यथा अगर (ch->ch_c_अगरlag & IXOFF && ch->ch_stops_sent) अणु
			ch->ch_stops_sent = 0;
			bd_ops->send_start_अक्षरacter(ch);
			jsm_dbg(READ, &ch->ch_bd->pci_dev,
				"Sending start char!\n");
		पूर्ण
	पूर्ण
पूर्ण
